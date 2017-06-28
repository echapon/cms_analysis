#include "RooWorkspace.h"
#include "RooGaussian.h"
#include "RooAbsPdf.h"
#include "RooProdPdf.h"
#include "RooDataSet.h"
#include "RooRealVar.h"
#include "TFile.h"
#include "RooStats/ProfileLikelihoodCalculator.h"
#include "RooStats/HypoTestResult.h"

#include <iostream>

using namespace RooFit;
using namespace RooStats;
using namespace std;

int nCPU = 4;
double initialGuess = 64.;

// systs
double ebval = 0.59;
double eberr = 0.059;
double jsferr = 0.036;
double f_smjj_err = 0.02;

void computeSignificance_PFLHC(const char *filename="finalfitworkskace_v2.root", bool addsyst=true) {
   TFile *f = TFile::Open(filename);
   RooWorkspace *w = (RooWorkspace*) f->Get("w");
   
   // the eb constraint
   RooGaussian ebconstraint("ebconstraint_pdf","ebconstraint_pdf",
         *(w->var("eb")),
         RooConst(ebval),
         RooConst(eberr)) ;
   w->import(ebconstraint);

   // other constraints
   if (addsyst) {
      double val = w->var("jsf")->getVal();
      RooGaussian jsfconstraint("jsfconstraint_pdf","jsfconstraint_pdf",
            *(w->var("jsf")), RooConst(val), RooConst(jsferr*val)) ;
      w->var("jsf")->setConstant(kFALSE);
      w->import(jsfconstraint);

      // constraints on the correct/wrong fractions
      w->factory(Form("Gaussian::thetaconstraint(theta[1,0,2],theta0[1],thetaerr[%f])",f_smjj_err));

      // now the total constraint
      w->factory("PROD::constraints_all(ebconstraint_pdf,jsfconstraint_pdf,thetaconstraint)");

      // make the modified model
      w->factory("PROD::model_mjj_e1l4j2b_constr(model_mjj_e1l4j2b, constraints_all)");
      w->factory("PROD::model_mjj_e1l4j1b1q_constr(model_mjj_e1l4j1b1q, constraints_all)");
      w->factory("PROD::model_mjj_e1l4j2q_constr(model_mjj_e1l4j2q, constraints_all)");
      w->factory("PROD::model_mjj_mu1l4j2b_constr(model_mjj_mu1l4j2b, constraints_all)");
      w->factory("PROD::model_mjj_mu1l4j1b1q_constr(model_mjj_mu1l4j1b1q, constraints_all)");
      w->factory("PROD::model_mjj_mu1l4j2q_constr(model_mjj_mu1l4j2q, constraints_all)");
      w->factory("SIMUL::model_combined_mjj_constr0(sample, e1l4j2b=model_mjj_e1l4j2b_constr, e1l4j1b1q=model_mjj_e1l4j1b1q_constr, e1l4j2q=model_mjj_e1l4j2q_constr, mu1l4j2b=model_mjj_mu1l4j2b_constr, mu1l4j1b1q=model_mjj_mu1l4j1b1q_constr, mu1l4j2q=model_mjj_mu1l4j2q_constr)");
      w->factory("EDIT::model_combined_mjj_constr1(model_combined_mjj_constr0,f_smjj_e1l4j2b=expr('f_smjj_e1l4j2b*theta',f_smjj_e1l4j2b,theta))");
      w->factory("EDIT::model_combined_mjj_constr2(model_combined_mjj_constr1,f_smjj_e1l4j1b1q=expr('f_smjj_e1l4j1b1q*theta',f_smjj_e1l4j1b1q,theta))");
      w->factory("EDIT::model_combined_mjj_constr3(model_combined_mjj_constr2,f_smjj_e1l4j2q=expr('f_smjj_e1l4j2q*theta',f_smjj_e1l4j2q,theta))");
      w->factory("EDIT::model_combined_mjj_constr4(model_combined_mjj_constr3,f_smjj_mu1l4j2b=expr('f_smjj_mu1l4j2b*theta',f_smjj_mu1l4j2b,theta))");
      w->factory("EDIT::model_combined_mjj_constr5(model_combined_mjj_constr4,f_smjj_mu1l4j1b1q=expr('f_smjj_mu1l4j1b1q*theta',f_smjj_mu1l4j1b1q,theta))");
      w->factory("EDIT::model_combined_mjj_constr(model_combined_mjj_constr5,f_smjj_mu1l4j2q=expr('f_smjj_mu1l4j2q*theta',f_smjj_mu1l4j2q,theta))");
   } else {
      w->factory("PROD::model_mjj_e1l4j2b_constr(model_mjj_e1l4j2b, ebconstraint)");
      w->factory("PROD::model_mjj_e1l4j1b1q_constr(model_mjj_e1l4j1b1q, ebconstraint)");
      w->factory("PROD::model_mjj_e1l4j2q_constr(model_mjj_e1l4j2q, ebconstraint)");
      w->factory("PROD::model_mjj_mu1l4j2b_constr(model_mjj_mu1l4j2b, ebconstraint)");
      w->factory("PROD::model_mjj_mu1l4j1b1q_constr(model_mjj_mu1l4j1b1q, ebconstraint)");
      w->factory("PROD::model_mjj_mu1l4j2q_constr(model_mjj_mu1l4j2q, ebconstraint)");
      w->factory("SIMUL::model_combined_mjj_constr(sample, e1l4j2b=model_mjj_e1l4j2b_constr, e1l4j1b1q=model_mjj_e1l4j1b1q_constr, e1l4j2q=model_mjj_e1l4j2q_constr, mu1l4j2b=model_mjj_mu1l4j2b_constr, mu1l4j1b1q=model_mjj_mu1l4j1b1q_constr, mu1l4j2q=model_mjj_mu1l4j2q_constr)");
   }

   RooAbsPdf *constraints_all = w->pdf("constraints_all");


   RooAbsPdf *model = w->pdf("model_combined_mjj");
   RooAbsPdf *modelc = w->pdf("model_combined_mjj_constr");

   // w->Print();
   // return;


   RooDataSet *data = (RooDataSet*) w->data("data");
   RooRealVar *thePoi = (RooRealVar*) w->var("xsec");

   // preliminary fit
   thePoi->setVal(initialGuess);
   thePoi->setConstant(kTRUE);
   modelc->fitTo(*data,NumCPU(nCPU),Minos(RooArgSet(*thePoi)),Extended(kTRUE)); // add minos
   thePoi->setConstant(kFALSE);
   modelc->fitTo(*data,NumCPU(nCPU),Minos(RooArgSet(*thePoi)),Extended(kTRUE)); // add minos
   RooArgSet *altpars = modelc->getParameters(*(w->var("mjj")));
   w->saveSnapshot("altpars",*altpars,kTRUE);
   thePoi->setVal(0);
   thePoi->setConstant(kTRUE);
   modelc->fitTo(*data,NumCPU(nCPU),Minos(RooArgSet(*thePoi)),Extended(kTRUE)); // add minos
   RooArgSet *nullpars = modelc->getParameters(*(w->var("mjj")));
   w->saveSnapshot("nullpars",*nullpars,kTRUE);
   w->loadSnapshot("altpars");
   w->var("xsec")->setConstant(kFALSE);

   // now to the profile likelihood calculator
   ProfileLikelihoodCalculator pl2(*data,*modelc,RooArgSet(*thePoi));
   pl2.SetNuisanceParameters(RooArgSet(*(w->var("eb"))));
   RooArgSet *nullParams = new RooArgSet(*thePoi);
   nullParams->setRealValue("xsec",0);
   pl2.SetNullParameters(*nullParams);

   HypoTestResult *r = pl2.GetHypoTest();
   r->Print();

   cout << "Nsig for electrons:" << w->function("Nsig_e")->getVal() << " and for muons: " << w->function("Nsig_mu")->getVal() << endl;

   //  //Get the interval
   // w->loadSnapshot("altpars");

   // // this doesn't work... gives a weird shape with a second minimum at ~64
   // LikelihoodInterval* plInt = pl2.GetInterval();
   // cout << "PLC interval is [" << plInt->LowerLimit(*thePoi) << ", " << 
   //    plInt->UpperLimit(*thePoi) << "]" << endl;

   // TCanvas dataCanvas("dataCanvas");

   // LikelihoodIntervalPlot plotInt((LikelihoodInterval*)plInt);
   // plotInt.SetTitle("Profile Likelihood Ratio");
   // plotInt.SetRange(0,100);
   // plotInt.SetMaximum(3.);
   // w->loadSnapshot("altpars");
   // plotInt.Draw();
   // dataCanvas.SaveAs("interval.pdf");

   // // do the scan by hand
   // RooAbsReal *nll = modelc->createNLL(*data,Extended(kTRUE),NumCPU(nCPU));

   // double x[20],nllval[20];
   // for (int i=0; i<20; i++) {
   //    x[i] = 50+i;
   //    thePoi->setVal(x[i]);
   //    thePoi->setConstant(kTRUE);
   //    RooMinuit *minuit = new RooMinuit(*nll);
   //    minuit->migrad();
   //    minuit->minos(*thePoi);
   //    nllval[i] = nll->getVal();
   // }
   // thePoi->setConstant(kFALSE);

   // for (int i=0; i<20; i++) {
   //    cout << x[i] << " " << nllval[i] << endl;
   // }
}
