#include "RooMCStudy.h"

using namespace RooFit;

bool addsyst = true;
int nCPU = 1;
double initialGuess = 47.;
double ebval = 0.595;
double eberr = 0.0595;
double jsferr = 0.034;
double f_smjj_err = 0.02;

void coverage_nosyst_noroomcstudy(const char* filename="finalfitworkspace_uncorrwjets_constantjsf_0.root", int seed=-1) {
   TFile *f = new TFile(filename);
   RooWorkspace *w = (RooWorkspace*) f->Get("w");
   RooRealVar *thePoi = (RooRealVar*) w->var("xsec");
   RooDataSet *data = (RooDataSet*) w->data("data");
   if (seed>0) {
      RooRandom::randomGenerator()->SetSeed(seed);
      gRandom->SetSeed(seed);
   }

   // C r e a t e   c o n s t r a i n t   p d f 
   // -----------------------------------------

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
      w->factory("Uniform::dummy0(mjj)");
      w->factory("SUM::dummy(a0[0,1e6]*dummy0)");
      // w->factory("SIMUL::model_combined_mjj_constr0(sample, e1l4j2b=model_mjj_e1l4j2b_constr, e1l4j1b1q=model_mjj_e1l4j1b1q_constr, e1l4j2q=model_mjj_e1l4j2q_constr, mu1l4j2b=model_mjj_mu1l4j2b_constr, mu1l4j1b1q=model_mjj_mu1l4j1b1q_constr, mu1l4j2q=model_mjj_mu1l4j2q_constr, e1f4j2q=dummy, mu1f4j2q=dummy)");
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

   RooAbsPdf *model = w->pdf("model_combined_mjj");
   RooAbsPdf *modelc = w->pdf("model_combined_mjj_constr");
   w->loadSnapshot("fitresult_combined");
   thePoi->setVal(47.);
   thePoi->setConstant(kTRUE);
   modelc->fitTo(*data,NumCPU(nCPU),Minos(RooArgSet(*thePoi)),Extended()); // add minos
   thePoi->setConstant(kFALSE);
   modelc->fitTo(*data,NumCPU(nCPU),Minos(RooArgSet(*thePoi)),Extended()); // add minos
   w->var("eb")->setConstant(kTRUE);
   w->var("theta")->setConstant(kTRUE);
   w->var("jsf")->setConstant(kTRUE);
   RooArgSet *newpars = modelc->getParameters(*(w->var("mjj")));
   w->saveSnapshot("myfitresults",*newpars,kTRUE);

   int ntoys = 10;
   int nentries = data->sumEntries("sample==sample::e1l4j2b || sample==sample::e1l4j1b1q || sample==sample::e1l4j2q || sample==sample::mu1l4j2b || sample==sample::mu1l4j1b1q || sample==sample::mu1l4j2q");

   // this doesn't work!!! RooMCStudy does not store the results
   // // Instantiate MC study manager
   // RooMCStudy* mcstudy = new RooMCStudy(*modelc,RooArgSet(*w->var("mjj"),*w->cat("sample")),Extended(),Silence(),FitOptions(NumCPU(8), Extended(kTRUE),Minos(*w->var("mjj"))));//

   // // Generate and fit nSamples samples of Poisson(nData) events
   // mcstudy->generateAndFit(ntoys,data->sumEntries(),kFALSE);

   TTree *tresults = new TTree("fitresults","fit results");
   float xsec, xsecerr;
   int ngen;
   tresults->Branch("xsec",&xsec,"xsec/F");
   tresults->Branch("xsecerr",&xsecerr,"xsecerr/F");
   tresults->Branch("ngen",&ngen,"ngen/I");

   for (int itoy=0; itoy<ntoys; itoy++) {
      w->loadSnapshot("myfitresults");
      ngen = gRandom->Poisson(nentries);
      RooDataSet *dat = modelc->generate(RooArgSet(*w->var("mjj"),*w->cat("sample")),ngen);
      thePoi->setVal(47.);
      thePoi->setConstant(kTRUE);
      modelc->fitTo(*dat,NumCPU(nCPU),Minos(RooArgSet(*thePoi)),Extended()); // add minos
      thePoi->setConstant(kFALSE);
      modelc->fitTo(*dat,NumCPU(nCPU),Minos(RooArgSet(*thePoi)),Extended()); // add minos
      xsec = thePoi->getVal();
      xsecerr = thePoi->getError();
      tresults->Fill();
   }





   //___ Save toy MC to file

   TString fileName(filename);
   fileName.Remove(0,fileName.Last('/')+1);
   TFile* fSaveMCStudy = new TFile(Form("MCTOY2_%d_%s",seed,fileName.Data()),"RECREATE");
   tresults->Write();
   fSaveMCStudy->Close(); delete fSaveMCStudy;
}
