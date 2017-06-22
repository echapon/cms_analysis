#include "RooWorkspace.h"
#include "RooGaussian.h"
#include "RooAbsPdf.h"
#include "RooProdPdf.h"
#include "RooDataSet.h"
#include "RooRealVar.h"
#include "myPFLHC.C"
#include "RooStats/HypoTestResult.h"
#include "TFile.h"

#include <iostream>

using namespace RooFit;
using namespace RooStats;
using namespace std;

// GLOBAL SYST ON xsec
double gGlobalSyst = 0.25;

HypoTestResult* testMyPFLHC(const char *filename="finalfitworkskace_v2.root") {
   TFile *f = TFile::Open(filename);
   RooWorkspace *w = (RooWorkspace*) f->Get("w");
   
   RooRealVar eb_nom("eb_nom","eb_nom",0.59);
   eb_nom.setConstant(kTRUE);
   RooRealVar eb_err("eb_err","eb_err",0.059);
   eb_err.setConstant(kTRUE);
   RooGaussian ebconstraint("ebconstraint_pdf","ebconstraint_pdf",*(w->var("eb")),eb_nom,eb_err) ;
   // Multiply constraint with p.d.f
   RooAbsPdf *model = w->pdf("model_combined_mjj");
   RooProdPdf modelc("modelc_combined_mjj","model with constraint",RooArgSet(*model,ebconstraint)) ;
   w->import(modelc);
   RooDataSet *data = (RooDataSet*) w->data("data");
   RooRealVar *thePoi = (RooRealVar*) w->var("xsec");

   // // without systematic uncertainty

   // model->fitTo(*data,NumCPU(2),Minos(RooArgSet(*thePoi)),Extended(kTRUE),
   //       ExternalConstraints(RooArgSet(ebconstraint)),GlobalObservables(RooArgSet(eb_nom))); // add minos

   // myPFLHC pl(*data,*model,RooArgSet(*thePoi));
   // // pl.SetGlobalObservables(RooArgSet(eb_nom));
   // pl.SetNuisanceParameters(RooArgSet(*(w->var("eb"))));
   // pl.SetMinos(true);
   // pl.SetExtended(true);
   // pl.SetNCPU(4);
   // // pl.SetConstraints(RooArgSet(ebconstraint));
   // pl.SetConstraints(new RooArgSet(*(w->function("ebconstraint"))));
   // RooArgSet *nullParams = new RooArgSet(*thePoi);
   // nullParams->setRealValue("xsec",0);
   // pl.SetNullParameters(*nullParams);
   // // pl.GetInterval();
   // HypoTestResult *r = pl.GetHypoTest();
   // r->Print();

   // including systs with a global factor

   RooRealVar syst_kappa("syst_kappa","syst_kappa",1+gGlobalSyst);
   syst_kappa.setConstant(kTRUE);
   w->import(syst_kappa);
   w->factory( "expr::alpha_syst('pow(syst_kappa,beta_syst)',syst_kappa,beta_syst[0,-5,5])" );
   w->factory( "Gaussian::constr_syst_pdf(beta_syst,glob_syst[0,-5,5],1)" );
   w->factory( "expr::constr_syst('0.5*pow((@0-@1)/1,2)',beta_syst,glob_syst)" );
   w->var("glob_syst")->setConstant(kTRUE);
   w->var("glob_syst")->setVal(0);
   w->factory("EDIT::model_combined_mjj_syst(model_combined_mjj,xsec=expr('xsec*alpha_syst',xsec,alpha_syst))");
   w->Print();

   RooArgSet *constraints_pdf = new RooArgSet(ebconstraint,*(w->pdf("constr_syst_pdf")));

   RooAbsPdf *model_syst = w->pdf("model_combined_mjj_syst");
   model_syst->fitTo(*data,NumCPU(2),Minos(RooArgSet(*thePoi)),Extended(kTRUE),
         ExternalConstraints(*constraints_pdf)); // add minos

   myPFLHC pl2(*data,*model_syst,RooArgSet(*thePoi));
   // pl.SetGlobalObservables(RooArgSet(eb_nom));
   pl2.SetNuisanceParameters(RooArgSet(*(w->var("eb"))));
   pl2.SetMinos(true);
   pl2.SetExtended(true);
   pl2.SetNCPU(4);
   // pl.SetConstraints(RooArgSet(ebconstraint));
   RooArgSet *constraints = new RooArgSet(*(w->function("ebconstraint")),*(w->function("constr_syst")));
   pl2.SetConstraints(constraints);
   RooArgSet *nullParams = new RooArgSet(*thePoi);
   nullParams->setRealValue("xsec",0);
   pl2.SetNullParameters(*nullParams);
   // pl.GetInterval();
   HypoTestResult *r = pl2.GetHypoTest();
   r->Print();

    //Get the interval
   LikelihoodInterval* plInt = pl2.GetInterval();
   cout << "PLC interval is [" << plInt->LowerLimit(*thePoi) << ", " << 
      plInt->UpperLimit(*thePoi) << "]" << endl;

   TCanvas dataCanvas("dataCanvas");

   LikelihoodIntervalPlot plotInt((LikelihoodInterval*)plInt);
   plotInt.SetTitle("Profile Likelihood Ratio");
   plotInt.SetMaximum(3.);
   plotInt.Draw();
   dataCanvas.SaveAs("interval.pdf");

   return r;
}
