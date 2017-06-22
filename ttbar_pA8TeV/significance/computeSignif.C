#include "StandardHypoTestDemo.C"

int nCPU = 4;
double eb0 = 0.59;
double eberr = 0.059;

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

void computeSignif(const char* filename = "finalfitworkskace_v2.root",
                          int seed = -1,
                          const char* workspaceName = "w",
                          const char* modelSBName = "modelSB",
                          const char* modelBName = "modelB",
                          const char* dataName = "data",
                          int calcType = 0, /* 0 freq 1 hybrid, 2 asymptotic */
                          int testStatType = 3,   /* 0 LEP, 1 TeV, 2 LHC, 3 LHC - one sided*/
                          int ntoys = 1000,
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
   // optHT.poiValue = 56.6;                    // change poi snapshot value for S+B model (needed for expected p0 values)

   // C r e a t e   c o n s t r a i n t   p d f 
   // -----------------------------------------

   // Construct Gaussian constraint p.d.f on parameter eb at 0.59 with resolution of 0.1
   // the constraint
   w->factory(Form("Gaussian::ebconstraint_pdf(eb,eb0[%f,0,1],%f)",eb0,eberr));
   w->var("eb0")->setConstant(kTRUE);

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
   nuis->add(*(w->var("eb")));
   // RooArgSet allVars = w->allVars();
   // TIterator* it = allVars.createIterator();
   // RooRealVar *theVar = (RooRealVar*) it->Next();
   // while (theVar) {
   //    if (!(theVar->isConstant()) && (theVar->GetName() != thePoi->GetName())) {
   //       if (TString(theVar->GetName()) == "eb") 
   //          nuis->add(*theVar);
   //    }
   //    theVar = (RooRealVar*) it->Next();
   // }
   msb->SetNuisanceParameters(*nuis);

   // observables
   RooArgSet *obs = new RooArgSet();
   obs->add(*(w->var("mjj")));
   RooCategory *cat = w->cat("sample");
   obs->add(*cat);
   msb->SetObservables(*obs);

   // snapshot
   if (w->getSnapshot("fitresults_combined")) { // check if the snapshot exists
      msb->SetSnapshot(*(w->getSnapshot("fitresult_combined")));
      // setConstant(w);
   } else { // else produce it
      thePoi->setVal(54.);
      thePoi->setConstant(kTRUE);
      modelc->fitTo(*data,NumCPU(nCPU),Minos(RooArgSet(*thePoi)),Extended()); // add minos
      thePoi->setConstant(kFALSE);
      modelc->fitTo(*data,NumCPU(nCPU),Minos(RooArgSet(*thePoi)),Extended()); // add minos
      // // do the fit and plot the LH profile too
      // RooAbsReal * pNll = msb->GetPdf()->createNLL( *dataR,NumCPU(2) );
      // RooMinuit(*pNll).migrad(); // minimize likelihood wrt all parameters before making plots
      // RooPlot *framepoi = thePoi->frame(Bins(10),Range(0.,100),Title("LL and profileLL in xsec"));
      // pNll->plotOn(framepoi,ShiftToZero());
      // RooAbsReal * pProfile = pNll->createProfile(RooArgSet(*thePoi) );
      // pProfile->getVal(); // this will do fit and set POI and nuisance parameters to fitted values
      // pProfile->plotOn(framepoi,LineColor(kRed));
      // framepoi->SetMinimum(0);
      // framepoi->SetMaximum(10);
      // TCanvas *cpoi = new TCanvas();
      // cpoi->cd(); framepoi->Draw();
      // cpoi->SaveAs("cpoi.pdf");
      RooArgSet *newpars = modelc->getParameters(*(w->var("mjj")));
      w->saveSnapshot("fitresults_combined",*newpars,kTRUE);
      // setConstant(w);
      // msb->SetSnapshot(*((RooArgSet*) newpars->selectByName("xsec")));
      msb->SetSnapshot(*newpars);
   }
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
   mb->SetSnapshot(*newpars);
   // mb->SetSnapshot(*((RooArgSet*) newpars->selectByName("xsec")));
   mb->SetSnapshot(*newpars);
   w->import(*mb);

   // StandardHypoTestDemo(w, modelSBName, modelBName, dataName, calcType, testStatType, ntoys, useNC, nuisPriorName);
   StandardHypoTestDemo(w, modelSBName, "", dataName, calcType, testStatType, ntoys, useNC, nuisPriorName, seed);
};
