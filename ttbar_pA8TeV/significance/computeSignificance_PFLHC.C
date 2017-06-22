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
double initialGuess = 54.;

void computeSignificance_PFLHC(const char *filename="finalfitworkskace_v2.root") {
   TFile *f = TFile::Open(filename);
   RooWorkspace *w = (RooWorkspace*) f->Get("w");
   
   // the constraint
   RooGaussian ebconstraint("ebconstraint_pdf","ebconstraint_pdf",*(w->var("eb")),RooConst(0.59),RooConst(0.059)) ;
   w->import(ebconstraint);

   // Multiply constraint with p.d.f
   // for each component of the multi pdf
   w->factory("PROD::model_mjj_e1l4j2b_ebconstr(model_mjj_e1l4j2b, ebconstraint_pdf)");
   w->factory("PROD::model_mjj_e1l4j1b1q_ebconstr(model_mjj_e1l4j1b1q, ebconstraint_pdf)");
   w->factory("PROD::model_mjj_e1l4j2q_ebconstr(model_mjj_e1l4j2q, ebconstraint_pdf)");
   w->factory("PROD::model_mjj_mu1l4j2b_ebconstr(model_mjj_mu1l4j2b, ebconstraint_pdf)");
   w->factory("PROD::model_mjj_mu1l4j1b1q_ebconstr(model_mjj_mu1l4j1b1q, ebconstraint_pdf)");
   w->factory("PROD::model_mjj_mu1l4j2q_ebconstr(model_mjj_mu1l4j2q, ebconstraint_pdf)");
   w->factory("SIMUL::model_combined_mjj_ebconstr(sample, e1l4j2b=model_mjj_e1l4j2b_ebconstr, e1l4j1b1q=model_mjj_e1l4j1b1q_ebconstr, e1l4j2q=model_mjj_e1l4j2q_ebconstr, mu1l4j2b=model_mjj_mu1l4j2b_ebconstr, mu1l4j1b1q=model_mjj_mu1l4j1b1q_ebconstr, mu1l4j2q=model_mjj_mu1l4j2q_ebconstr)");

   RooAbsPdf *model = w->pdf("model_combined_mjj");
   RooAbsPdf *modelc = w->pdf("model_combined_mjj_ebconstr");



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

   // do the scan by hand
   RooAbsReal *nll = modelc->createNLL(*data,Extended(kTRUE),NumCPU(nCPU));

   double x[20],nllval[20];
   for (int i=0; i<20; i++) {
      x[i] = 50+i;
      thePoi->setVal(x[i]);
      thePoi->setConstant(kTRUE);
      RooMinuit *minuit = new RooMinuit(*nll);
      minuit->migrad();
      minuit->minos(*thePoi);
      nllval[i] = nll->getVal();
   }
   thePoi->setConstant(kFALSE);

   for (int i=0; i<20; i++) {
      cout << x[i] << " " << nllval[i] << endl;
   }
}
