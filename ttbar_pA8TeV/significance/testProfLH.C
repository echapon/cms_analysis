#include "RooWorkspace.h"
#include "RooGaussian.h"
#include "RooAbsPdf.h"
#include "RooProdPdf.h"
#include "RooDataSet.h"
#include "RooRealVar.h"
#include "RooStats/ProfileLikelihoodCalculator.h"
#include "RooStats/HypoTestResult.h"
#include "TFile.h"

using namespace RooFit;
using namespace RooStats;

HypoTestResult* testProfLH(const char *filename="finalfitworkskace_v2.root") {
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

   model->fitTo(*data,NumCPU(2),Minos(RooArgSet(*thePoi)),Extended(kTRUE),
         ExternalConstraints(RooArgSet(ebconstraint)),GlobalObservables(RooArgSet(eb_nom))); // add minos
   cout << __LINE__ << endl;
   ProfileLikelihoodCalculator pl(*data,modelc,RooArgSet(*thePoi));
   // pl.SetGlobalObservables(RooArgSet(eb_nom));
   pl.SetNuisanceParameters(RooArgSet(*(w->var("eb"))));
   cout << __LINE__ << endl;
   pl.GetInterval();
   cout << __LINE__ << endl;
   HypoTestResult *r = pl.GetHypoTest();
   cout << __LINE__ << endl;
   r->Print();
   cout << __LINE__ << endl;
   return r;
}
