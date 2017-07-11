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
double initialGuess = 47.;

// systs
double ebval = 0.595;
double eberr = 0.0595;
double jsferr = 0.034;
double f_smjj_err = 0.02;
double acc_e_val = 0.056;
double acc_e_err = 0.0014;
double acc_mu_val = 0.06;
double acc_mu_err = 0.0016;
double eff_e_val = 0.623;
double eff_e_err = 0.0249;
double eff_mu_val = 0.915;
double eff_mu_err = 0.0366;
double lumi_val = 174.5;
double lumi_err = 8.725;

void computeSignificance_PFLHC(const char *filename="finalfitworkspace_uncorrwjets_constantjsf_0.root") {
   TFile *f = TFile::Open(filename);
   RooWorkspace *w = (RooWorkspace*) f->Get("w");
   
   // the eb constraint
   RooGaussian ebconstraint("ebconstraint_pdf","ebconstraint_pdf",
         *(w->var("eb")),
         RooConst(ebval),
         RooConst(eberr)) ;
   w->import(ebconstraint);

   w->loadSnapshot("fitresult_combined");

   // other constraints
   double val = 1;

   // // Now all of the following is already in the workspace thanks to Pedro!
   // RooGaussian jsfconstraint("jsfconstraint_pdf","jsfconstraint_pdf",
   //       *(w->var("jsf")), RooConst(val), RooConst(jsferr*val)) ;
   // w->var("jsf")->setConstant(kFALSE);
   // w->import(jsfconstraint);

   // constraints on the correct/wrong fractions
   w->factory(Form("Gaussian::thetaconstraint(theta[1,0,2],theta0[1],thetaerr[%f])",f_smjj_err));

   // // lumi
   // w->factory(Form("Gaussian::lumiconstraint(lumi,lumi_0[%f],lumi_err[%f])",lumi_val,lumi_err));

   // // acceptance and efficiency
   // w->factory(Form("Gaussian::acceconstraint(acc_e,acc_e_0[%f],acc_e_err[%f])",acc_e_val,acc_e_err));
   // w->factory(Form("Gaussian::accmuconstraint(acc_mu,acc_mu_0[%f],acc_mu_err[%f])",acc_mu_val,acc_mu_err));
   // w->factory(Form("Gaussian::effeconstraint(eff_e,eff_e_0[%f],eff_e_err[%f])",eff_e_val,eff_e_err));
   // w->factory(Form("Gaussian::effmuconstraint(eff_mu,eff_mu_0[%f],eff_mu_err[%f])",eff_mu_val,eff_mu_err));

   // // now the total constraint
   // w->factory("PROD::constrProd2(constrProd,thetaconstraint)");

   // make the modified model
   w->factory("PROD::model_mjj_e1l4j2b_constr(model_mjj_e1l4j2b, constrProd)");
   w->factory("PROD::model_mjj_e1l4j1b1q_constr(model_mjj_e1l4j1b1q, constrProd)");
   w->factory("PROD::model_mjj_e1l4j2q_constr(model_mjj_e1l4j2q, constrProd)");
   w->factory("PROD::model_mjj_mu1l4j2b_constr(model_mjj_mu1l4j2b, constrProd)");
   w->factory("PROD::model_mjj_mu1l4j1b1q_constr(model_mjj_mu1l4j1b1q, constrProd)");
   w->factory("PROD::model_mjj_mu1l4j2q_constr(model_mjj_mu1l4j2q, constrProd)");
   w->factory("SIMUL::model_combined_mjj_constr(sample, e1l4j2b=model_mjj_e1l4j2b_constr, e1l4j1b1q=model_mjj_e1l4j1b1q_constr, e1l4j2q=model_mjj_e1l4j2q_constr, mu1l4j2b=model_mjj_mu1l4j2b_constr, mu1l4j1b1q=model_mjj_mu1l4j1b1q_constr, mu1l4j2q=model_mjj_mu1l4j2q_constr)");


   // w->factory("SIMUL::model_combined_mjj_constr0(sample, e1l4j2b=model_mjj_e1l4j2b_constr, e1l4j1b1q=model_mjj_e1l4j1b1q_constr, e1l4j2q=model_mjj_e1l4j2q_constr, mu1l4j2b=model_mjj_mu1l4j2b_constr, mu1l4j1b1q=model_mjj_mu1l4j1b1q_constr, mu1l4j2q=model_mjj_mu1l4j2q_constr)");
   // w->factory("EDIT::model_combined_mjj_constr1(model_combined_mjj_constr0,f_smjj_e1l4j2b=expr('f_smjj_e1l4j2b*theta',f_smjj_e1l4j2b,theta))");
   // w->factory("EDIT::model_combined_mjj_constr2(model_combined_mjj_constr1,f_smjj_e1l4j1b1q=expr('f_smjj_e1l4j1b1q*theta',f_smjj_e1l4j1b1q,theta))");
   // w->factory("EDIT::model_combined_mjj_constr3(model_combined_mjj_constr2,f_smjj_e1l4j2q=expr('f_smjj_e1l4j2q*theta',f_smjj_e1l4j2q,theta))");
   // w->factory("EDIT::model_combined_mjj_constr4(model_combined_mjj_constr3,f_smjj_mu1l4j2b=expr('f_smjj_mu1l4j2b*theta',f_smjj_mu1l4j2b,theta))");
   // w->factory("EDIT::model_combined_mjj_constr5(model_combined_mjj_constr4,f_smjj_mu1l4j1b1q=expr('f_smjj_mu1l4j1b1q*theta',f_smjj_mu1l4j1b1q,theta))");
   // w->factory("EDIT::model_combined_mjj_constr(model_combined_mjj_constr5,f_smjj_mu1l4j2q=expr('f_smjj_mu1l4j2q*theta',f_smjj_mu1l4j2q,theta))");

   RooAbsPdf *constraints_all = w->pdf("constrProd");


   RooAbsPdf *model = w->pdf("model_combined_mjj");
   RooAbsPdf *modelc = w->pdf("model_combined_mjj_constr");

   // w->Print();
   // return;

   w->var("theta")->setConstant();
   w->var("eb")->setConstant();
   w->var("jsf")->setConstant();
   w->var("acc_e")->setConstant();
   w->var("acc_mu")->setConstant();
   w->var("eff_e")->setConstant();
   w->var("eff_mu")->setConstant();
   w->var("lumi")->setConstant();

   RooDataSet *data = (RooDataSet*) w->data("data");
   RooRealVar *thePoi = (RooRealVar*) w->var("xsec");

   ///////////////////////////////////////////////////////////////////

   // // preliminary fit
   // // first, setting xsec to a reasonable value
   // thePoi->setVal(initialGuess);
   // thePoi->setConstant(kTRUE);
   // modelc->fitTo(*data,NumCPU(nCPU),Minos(RooArgSet(*thePoi)),Extended(kTRUE)); // add minos

   // // then, releasing xsec
   // thePoi->setConstant(kFALSE);
   // modelc->fitTo(*data,NumCPU(nCPU),Minos(RooArgSet(*thePoi)),Extended(kTRUE)); // add minos

   // // at last, releasing systs too
   w->var("theta")->setConstant(kFALSE);
   w->var("eb")->setConstant(kFALSE);
   w->var("jsf")->setConstant(kFALSE);
   w->var("acc_e")->setConstant(kFALSE);
   w->var("acc_mu")->setConstant(kFALSE);
   w->var("eff_e")->setConstant(kFALSE);
   w->var("eff_mu")->setConstant(kFALSE);
   w->var("lumi")->setConstant(kFALSE);

   // // but set constant the things uncorrelated to xsec
   // // w->var("fqcd_e1l4j2b")->setConstant();
   // // w->var("fqcd_e1l4j2q")->setConstant();
   // // w->var("fqcd_mu1l4j2b")->setConstant();
   // // w->var("width_wmjj_1l4j1b1q")->setConstant();


   RooFitResult *rr = modelc->fitTo(*data,NumCPU(nCPU),Minos(RooArgSet(*thePoi)),Extended(kTRUE),Strategy(2),Save()); // add minos
   // // correlation matrix
   // rr->correlationHist()->Draw("COLZ");
   // return;

   // save params
   RooArgSet *altpars = modelc->getParameters(*(w->var("mjj")));
   w->saveSnapshot("altpars",*altpars,kTRUE);
   thePoi->setVal(0);
   thePoi->setConstant(kTRUE);
   // the null fit (xsec=0)
   modelc->fitTo(*data,NumCPU(nCPU),Minos(RooArgSet(*thePoi)),Extended(kTRUE),Strategy(2)); // add minos
   RooArgSet *nullpars = modelc->getParameters(*(w->var("mjj")));
   w->saveSnapshot("nullpars",*nullpars,kTRUE);
   w->loadSnapshot("altpars");
   w->var("xsec")->setConstant(kFALSE);

   // now to the profile likelihood calculator
   ProfileLikelihoodCalculator pl2(*data,*modelc,RooArgSet(*thePoi));
   RooArgSet nuis("nuisance");
   nuis.add(*w->var("Nbkg_e1l4j1b1q"));
   nuis.add(*w->var("Nbkg_e1l4j2b"));
   nuis.add(*w->var("Nbkg_e1l4j2q"));
   nuis.add(*w->var("Nbkg_mu1l4j1b1q"));
   nuis.add(*w->var("Nbkg_mu1l4j2b"));
   nuis.add(*w->var("Nbkg_mu1l4j2q"));
   nuis.add(*w->var("acc_e"));
   nuis.add(*w->var("acc_mu"));
   nuis.add(*w->var("eb"));
   nuis.add(*w->var("eff_e"));
   nuis.add(*w->var("eff_mu"));
   nuis.add(*w->var("fqcd_e1l4j1b1q"));
   nuis.add(*w->var("fqcd_e1l4j2b"));
   nuis.add(*w->var("fqcd_e1l4j2q"));
   nuis.add(*w->var("fqcd_mu1l4j1b1q"));
   nuis.add(*w->var("fqcd_mu1l4j2b"));
   nuis.add(*w->var("fqcd_mu1l4j2q"));
   nuis.add(*w->var("jsf"));
   nuis.add(*w->var("lumi"));
   // nuis.add(*w->var("mpv_wmjj_1l4j1b1q"));
   // nuis.add(*w->var("mpv_wmjj_1l4j2b"));
   // nuis.add(*w->var("mpv_wmjj_1l4j2q"));
   // nuis.add(*w->var("width_wmjj_1l4j1b1q"));
   // nuis.add(*w->var("width_wmjj_1l4j2b"));
   // nuis.add(*w->var("width_wmjj_1l4j2q"));
   // pl2.SetNuisanceParameters(nuis);

   // RooArgSet *nullParams = new RooArgSet(*thePoi);
   // nullParams->setRealValue("xsec",0);
   pl2.SetNullParameters(*nullpars);
   pl2.SetAlternateParameters(*altpars);

   HypoTestResult *r = pl2.GetHypoTest();
   r->Print();

   cout << "Nsig for electrons:" << w->function("Nsig_e")->getVal() << " and for muons: " << w->function("Nsig_mu")->getVal() << endl;

   cout << "Best fit results:" << endl;
   rr->Print("v");

   //  //Get the interval
   // w->loadSnapshot("altpars");

   // // this doesn't work... gives a weird shape with a second minimum at ~64
   // LikelihoodInterval* plInt = pl2.GetInterval();
   // plInt->SetConfidenceLevel(0.682);
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
   // dataCanvas.SaveAs("interval.root");

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
