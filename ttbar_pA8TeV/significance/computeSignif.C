#include "StandardHypoTestDemo.C"
#include "RooMsgService.h"

bool addsyst = true;
int nCPU = 4;
double initialGuess = 47.;
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

void setConstant(RooWorkspace *w) {
   RooArgSet allVars = w->allVars();
   TIterator* it = allVars.createIterator();
   RooRealVar *theVar = (RooRealVar*) it->Next();
   while (theVar) {
      TString tvn = theVar->GetName();
      if (!(tvn == "mjj" || tvn == "sample" || tvn == "xsec" || tvn == "eb")) {
         theVar->setConstant(kTRUE);
      }
      theVar = (RooRealVar*) it->Next();
   }
};

void computeSignif(const char* filename = "finalfitworkspace_uncorrwjets_constantjsf_0.root",
                          int seed = -1,
                          const char* workspaceName = "w",
                          const char* modelSBName = "modelSB",
                          const char* modelBName = "modelB",
                          const char* dataName = "data",
                          int calcType = 0, /* 0 freq 1 hybrid, 2 asymptotic */
                          int testStatType = 3,   /* 0 LEP, 1 TeV, 2 LHC, 3 LHC - one sided*/
                          int ntoys = 2000,
                          bool useNC = false,
                          const char * nuisPriorName = 0)
{
   // Try to open the file
   TFile *file = TFile::Open(filename);

   // if input file was specified byt not found, quit
   if(!file ){
      cout <<"StandardRooStatsDemoMacro: Input file " << filename << " is not found" << endl;
      return;
   }



   // get the workspace out of the file
   RooWorkspace* w = (RooWorkspace*) file->Get(workspaceName);
   if(!w){
      cout <<"workspace not found" << endl;
      return;
   }

   optHT.name = filename;

   // create the models
   // load values from combined fit
   w->loadSnapshot("fitresult_combined");
   // set expected cross section
   // optHT.poiValue = 57.5;                    // change poi snapshot value for S+B model (needed for expected p0 values)

   // C r e a t e   c o n s t r a i n t   p d f 
   // -----------------------------------------

   // the eb constraint
   RooGaussian ebconstraint("ebconstraint_pdf","ebconstraint_pdf",
         *(w->var("eb")),
         RooConst(ebval),
         RooConst(eberr)) ;
   w->import(ebconstraint);

   w->loadSnapshot("fitresult_combined");

   // other constraints
   double val = w->var("jsf")->getVal();

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
   // // w->factory("PROD::constraints_all(ebconstraint_pdf,jsfconstraint_pdf,thetaconstraint)");
   w->factory("PROD::constraints_all(ebconstraint_pdf,jsfconstraint_pdf,thetaconstraint,acceconstraint,accmuconstraint,effeconstraint,effmuconstraint,lumiconstraint)");

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

   w->Print();

   // // reduce the data to exclude categories with fake leptons
   // RooDataSet *dataR = (RooDataSet*) w->data("data")->reduce("sample==sample::e1l4j2b || sample==sample::e1l4j1b1q || sample==sample::e1l4j2q || sample==sample::mu1l4j2b || sample==sample::mu1l4j1b1q || sample==sample::mu1l4j2q");
   // dataR->SetName("dataReduced");
   // w->import(*dataR);
   RooDataSet *data = (RooDataSet*) w->data("data");


   ///////////////
   // S+B model //
   ///////////////
   ModelConfig *msb = new ModelConfig(modelSBName);
   msb->SetWorkspace(*w);
   msb->SetPdf(*modelc);
   RooRealVar *thePoi = (RooRealVar*) w->var("xsec");
   msb->SetParametersOfInterest(RooArgSet(*thePoi));

   // nuisance parameters
   RooArgSet *nuis = new RooArgSet();
   nuis->add(*w->var("Nbkg_e1l4j1b1q"));
   nuis->add(*w->var("Nbkg_e1l4j2b"));
   nuis->add(*w->var("Nbkg_e1l4j2q"));
   nuis->add(*w->var("Nbkg_mu1l4j1b1q"));
   nuis->add(*w->var("Nbkg_mu1l4j2b"));
   nuis->add(*w->var("Nbkg_mu1l4j2q"));
   nuis->add(*w->var("acc_e"));
   nuis->add(*w->var("acc_mu"));
   nuis->add(*w->var("eb"));
   nuis->add(*w->var("eff_e"));
   nuis->add(*w->var("eff_mu"));
   nuis->add(*w->var("fqcd_e1l4j1b1q"));
   nuis->add(*w->var("fqcd_e1l4j2b"));
   nuis->add(*w->var("fqcd_e1l4j2q"));
   nuis->add(*w->var("fqcd_mu1l4j1b1q"));
   nuis->add(*w->var("fqcd_mu1l4j2b"));
   nuis->add(*w->var("fqcd_mu1l4j2q"));
   nuis->add(*w->var("jsf"));
   nuis->add(*w->var("lumi"));
   if (w->var("mpv_wmjj_1l4j1b1q")) {
      nuis->add(*w->var("mpv_wmjj_1l4j1b1q"));
      nuis->add(*w->var("mpv_wmjj_1l4j2b"));
      nuis->add(*w->var("mpv_wmjj_1l4j2q"));
      nuis->add(*w->var("width_wmjj_1l4j1b1q"));
      nuis->add(*w->var("width_wmjj_1l4j2b"));
      nuis->add(*w->var("width_wmjj_1l4j2q"));
   }
   RooArgSet* poiAndNuis = new RooArgSet(*nuis);
   poiAndNuis->add(*thePoi);
   msb->SetNuisanceParameters(*nuis);

   // observables
   RooArgSet *obs = new RooArgSet();
   obs->add(*(w->var("mjj")));
   RooCategory *cat = w->cat("sample");
   obs->add(*cat);
   msb->SetObservables(*obs);

   // snapshot
   // if (w->getSnapshot("fitresults_combined")) { // check if the snapshot exists
   // msb->SetSnapshot(*(RooArgSet*)(w->getSnapshot("fitresult_combined")->selectCommon(*poiAndNuis)));
   msb->SetSnapshot(*w->getSnapshot("fitresult_combined"));
   //    // setConstant(w);
   // } else { // else produce it
   //    thePoi->setVal(47.);
   //    thePoi->setConstant(kTRUE);
   //    w->var("theta")->setConstant();
   //    w->var("eb")->setConstant();
   //    w->var("jsf")->setConstant();
   //    w->var("acc_e")->setConstant();
   //    w->var("acc_mu")->setConstant();
   //    w->var("eff_e")->setConstant();
   //    w->var("eff_mu")->setConstant();
   //    w->var("lumi")->setConstant();
   //    modelc->fitTo(*data,NumCPU(nCPU),Minos(RooArgSet(*thePoi)),Extended()); // add minos
   //    thePoi->setConstant(kFALSE);
   //    modelc->fitTo(*data,NumCPU(nCPU),Minos(RooArgSet(*thePoi)),Extended()); // add minos
   //    w->var("theta")->setConstant(kFALSE);
   //    w->var("eb")->setConstant(kFALSE);
   //    w->var("jsf")->setConstant(kFALSE);
   //    w->var("acc_e")->setConstant(kFALSE);
   //    w->var("acc_mu")->setConstant(kFALSE);
   //    w->var("eff_e")->setConstant(kFALSE);
   //    w->var("eff_mu")->setConstant(kFALSE);
   //    w->var("lumi")->setConstant(kFALSE);
   //    modelc->fitTo(*data,NumCPU(nCPU),Minos(RooArgSet(*thePoi)),Extended()); // add minos
   //    // // do the fit and plot the LH profile too
   //    // RooAbsReal * pNll = msb->GetPdf()->createNLL( *dataR,NumCPU(2) );
   //    // RooMinuit(*pNll).migrad(); // minimize likelihood wrt all parameters before making plots
   //    // RooPlot *framepoi = thePoi->frame(Bins(10),Range(0.,100),Title("LL and profileLL in xsec"));
   //    // pNll->plotOn(framepoi,ShiftToZero());
   //    // RooAbsReal * pProfile = pNll->createProfile(RooArgSet(*thePoi) );
   //    // pProfile->getVal(); // this will do fit and set POI and nuisance parameters to fitted values
   //    // pProfile->plotOn(framepoi,LineColor(kRed));
   //    // framepoi->SetMinimum(0);
   //    // framepoi->SetMaximum(10);
   //    // TCanvas *cpoi = new TCanvas();
   //    // cpoi->cd(); framepoi->Draw();
   //    // cpoi->SaveAs("cpoi.pdf");
   //    RooArgSet *newpars = modelc->getParameters(*(w->var("mjj")));
   //    w->saveSnapshot("fitresults_combined",*newpars,kTRUE);
   //    // setConstant(w);
   //    // msb->SetSnapshot(*((RooArgSet*) newpars->selectByName("xsec")));
   //    msb->SetSnapshot(*newpars);
   // }
   w->import(*msb);

   // B only model
   ModelConfig *mb = new ModelConfig(modelBName);
   mb->SetWorkspace(*w);
   mb->SetPdf(*modelc);
   thePoi->setVal(0);
   mb->SetParametersOfInterest(RooArgSet(*thePoi));
   mb->SetNuisanceParameters(*nuis);
   mb->SetObservables(*obs);
   if (w->getSnapshot("fitresults_combined")) { // check if the snapshot exists
      w->loadSnapshot("fitresult_combined");
   } // else produce it
   w->var("xsec")->setVal(0);
   w->var("xsec")->setConstant(kTRUE);
   modelc->fitTo(*data,NumCPU(nCPU),Minos(RooArgSet(*thePoi)),Extended());
   w->var("xsec")->setConstant(kFALSE);
   RooArgSet *newpars = modelc->getParameters(*(w->var("mjj")));
   w->saveSnapshot("fitresults_combined_null",*newpars,kTRUE);
   mb->SetSnapshot(*((RooArgSet*) newpars->selectByName("xsec")));
   // mb->SetSnapshot(*newpars->selectCommon(*poiAndNuis));
   // mb->SetSnapshot(*(RooArgSet*) newpars->selectCommon(*poiAndNuis));
   w->import(*mb);

   w->loadSnapshot("fitresult_combined");
   w->Print();

   StandardHypoTestDemo(w, modelSBName, modelBName, dataName, calcType, testStatType, ntoys, useNC, nuisPriorName, seed);
   // StandardHypoTestDemo(w, modelSBName, "", dataName, calcType, testStatType, ntoys, useNC, nuisPriorName, seed);
};
