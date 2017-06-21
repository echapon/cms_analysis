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
   
   RooGaussian ebconstraint("ebconstraint_pdf","ebconstraint_pdf",*(w->var("eb")),RooConst(0.59),RooConst(0.059)) ;
   // Multiply constraint with p.d.f
   RooAbsPdf *model = w->pdf("model_combined_mjj");
   RooProdPdf modelc("modelc_combined_mjj","model with constraint",RooArgSet(*model,ebconstraint)) ;
   w->import(modelc);
   RooDataSet *data = (RooDataSet*) w->data("data");
   RooRealVar *thePoi = (RooRealVar*) w->var("xsec");
   cout <<"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" << endl;
   cout << __LINE__ << endl;
   model->fitTo(*data,NumCPU(2),Minos(RooArgSet(*thePoi)),Extended(kTRUE),ExternalConstraints(RooArgSet(ebconstraint))); // add minos


   // try to set all constant
   RooArgSet allVars = w->allVars();
   TIterator* it = allVars.createIterator();
   RooRealVar *theVar = (RooRealVar*) it->Next();
   while (theVar) {
      TString tvn = theVar->GetName();
      if (tvn != "mjj" && tvn != "xsec" && tvn != "eb" && tvn != "sample") {
            theVar->setConstant(kTRUE);
      }
      theVar = (RooRealVar*) it->Next();
   }


   cout <<"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" << endl;
   cout << __LINE__ << endl;
   model->fitTo(*data,NumCPU(2),Minos(RooArgSet(*thePoi)),Extended(kTRUE)); // add minos
   cout <<"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" << endl;
   cout << __LINE__ << endl;
   // the following fail...
   modelc.fitTo(*data,NumCPU(2),Minos(RooArgSet(*thePoi)),Extended(kTRUE),Constrain(RooArgSet(*(w->var("eb"))))); // add minos
   // modelc.fitTo(*data,NumCPU(2),Minos(RooArgSet(*thePoi)),Extended(kTRUE),Constrained()); // add minos
   cout <<"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" << endl;
   cout << __LINE__ << endl;
   modelc.fitTo(*data,NumCPU(2),Minos(RooArgSet(*thePoi)),Extended(kTRUE)); // add minos
   cout << __LINE__ << endl;

}
