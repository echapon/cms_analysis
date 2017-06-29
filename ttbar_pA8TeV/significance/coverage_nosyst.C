#include "RooMCStudy.h"

using namespace RooFit;

bool addsyst = true;
int nCPU = 1;
double initialGuess = 47.;
double ebval = 0.595;
double eberr = 0.0595;
double jsferr = 0.034;
double f_smjj_err = 0.02;

void coverage_nosyst(const char* filename="finalfitworkspace_uncorrwjets_constantjsf_0.root") {
   TFile *f = new TFile(filename);
   RooWorkspace *w = (RooWorkspace*) f->Get("w");
   RooRealVar *thePoi = (RooRealVar*) w->var("xsec");
   RooDataSet *data = (RooDataSet*) w->data("data");

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
      w->factory("Uniform::dummy(mjj)");
      w->factory("SIMUL::model_combined_mjj_constr0(sample, e1l4j2b=model_mjj_e1l4j2b_constr, e1l4j1b1q=model_mjj_e1l4j1b1q_constr, e1l4j2q=model_mjj_e1l4j2q_constr, mu1l4j2b=model_mjj_mu1l4j2b_constr, mu1l4j1b1q=model_mjj_mu1l4j1b1q_constr, mu1l4j2q=model_mjj_mu1l4j2q_constr, e1f4j2q=dummy, mu1f4j2q=dummy)");
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
   w->getSnapshot("fitresult_combined");
   thePoi->setVal(47.);
   thePoi->setConstant(kTRUE);
   w->var("eb")->setConstant(kTRUE);
   w->var("theta")->setConstant(kTRUE);
   w->var("jsf")->setConstant(kTRUE);
   modelc->fitTo(*data,NumCPU(nCPU),Minos(RooArgSet(*thePoi)),Extended()); // add minos
   thePoi->setConstant(kFALSE);
   modelc->fitTo(*data,NumCPU(nCPU),Minos(RooArgSet(*thePoi)),Extended()); // add minos

   double xsec = w->var("xsec")->getVal();
   double xsecErr = w->var("xsec")->getError();

   // Instantiate MC study manager
   RooMCStudy* mcstudy = new RooMCStudy(*modelc,RooArgSet(*w->var("mjj"),*w->cat("sample")),Extended(),Silence(),FitOptions(NumCPU(8), Extended(kTRUE),Minos(*w->var("mjj"))));//

   // Generate and fit nSamples samples of Poisson(nData) events
   mcstudy->generateAndFit(100,data->sumEntries(),kFALSE);

   //_____ Plot and fit Xsec distributions
   TString binName;
   TCanvas* cdistrXsec = new TCanvas(Form("cXsecDistr_%s",binName.Data()));
   const RooDataSet* jpsiDataSet = &(mcstudy->fitParDataSet());

   thePoi->setRange("FitXsecWindow",xsec-10*xsecErr,xsec+10*xsecErr);

   RooRealVar meanXsec("meanXsec","average Xsec",xsec,0,2*xsec);
   RooRealVar sigmaXsec("sigmaXsec","average sigmaXsec",xsecErr,0.1*xsecErr,10.*xsecErr);
   RooGaussian gausXsec("gausXsec","gaussian fit",*thePoi,meanXsec,sigmaXsec);
   RooFitResult* fitResultXsec = gausXsec.fitTo(*(RooAbsData*)jpsiDataSet,Range("FitXsecWindow"));

   RooRealVar meanXsecNom("meanXsecNom","average Xsec",xsec);
   RooRealVar sigmaXsecNom("sigmaXsecNom","average sigmaXsec",xsecErr);
   RooGaussian gausXsecNom("gausXsecNom","gaussian fit",*thePoi,meanXsecNom,sigmaXsecNom);

   RooPlot* frameXsec = thePoi->frame(Bins(100),Range(xsec-10*xsecErr,xsec+10*xsecErr));
   frameXsec->SetTitle(binName.Data());
   jpsiDataSet->plotOn(frameXsec);
   gausXsec.plotOn(frameXsec,LineColor(kRed), LineStyle(1), Precision(1e-4),Range(frameXsec->GetXaxis()->GetXmin(),frameXsec->GetXaxis()->GetXmax()));
   gausXsecNom.plotOn(frameXsec,LineColor(kBlue), LineStyle(1), Precision(1e-4),Range(frameXsec->GetXaxis()->GetXmin(),frameXsec->GetXaxis()->GetXmax()));
   frameXsec->Draw();

   TLatex *t = new TLatex(); t->SetNDC(); t->SetTextSize(0.036); float dy = 0.04;
   t->DrawLatex(0.45, 0.85-dy, Form("#color[4]{xsec^{nom} = %0.2f #pm %0.2f}",xsec,xsecErr)); dy+=0.050;
   t->DrawLatex(0.45, 0.85-dy, Form("#color[2]{xsec^{toy} = %0.2f(%0.2f) #pm %0.2f(%0.2f)}",meanXsec.getVal(),meanXsec.getError(),sigmaXsec.getVal(),sigmaXsec.getError())); dy+=0.050;
   t->Draw("same");

   cdistrXsec->Update();
   cdistrXsec->SaveAs(Form("cXsecDistr2_%s.pdf",binName.Data()));
   cdistrXsec->SaveAs(Form("cXsecDistr2_%s.root",binName.Data()));




   //___ Save toy MC to file
   mcstudy->SetName("MCStudy");

   TString fileName(filename);
   fileName.Remove(0,fileName.Last('/')+1);
   TFile* fSaveMCStudy = new TFile(Form("MCTOY2_%s",fileName.Data()),"RECREATE");
   mcstudy->Write();
   fSaveMCStudy->Close(); delete fSaveMCStudy;
   delete mcstudy;
}
