#include "RooWorkspace.h"
#include "RooGaussian.h"
#include "RooAbsPdf.h"
#include "RooProdPdf.h"
#include "RooDataSet.h"
#include "RooRealVar.h"
#include "TFile.h"

using namespace RooFit;

void test(const char *filename="finalfitworkskace_v2.root") {
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
   // model->fitTo(*data,NumCPU(2),Minos(RooArgSet(*thePoi)),Extended(kTRUE),ExternalConstraints(RooArgSet(ebconstraint))); // add minos


   // // try to set all constant
   // RooArgSet allVars = w->allVars();
   // TIterator* it = allVars.createIterator();
   // RooRealVar *theVar = (RooRealVar*) it->Next();
   // while (theVar) {
   //    TString tvn = theVar->GetName();
   //    if (tvn != "mjj" && tvn != "xsec" && tvn != "eb" && tvn != "sample") {
   //          theVar->setConstant(kTRUE);
   //    }
   //    theVar = (RooRealVar*) it->Next();
   // }


   // model->fitTo(*data,NumCPU(2),Minos(RooArgSet(*thePoi)),Extended(kTRUE)); // add minos
   // // the following fail...
   // modelc->fitTo(*data,NumCPU(2),Minos(RooArgSet(*thePoi)),Extended(kTRUE),Constrain(RooArgSet(*(w->var("eb"))))); // add minos
   // // modelc.fitTo(*data,NumCPU(2),Minos(RooArgSet(*thePoi)),Extended(kTRUE),Constrained()); // add minos
   modelc->fitTo(*data,NumCPU(2),Minos(RooArgSet(*thePoi)),Extended(kTRUE)); // add minos

}
