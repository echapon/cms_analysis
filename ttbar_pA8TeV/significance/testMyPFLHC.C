#include "RooWorkspace.h"
#include "RooGaussian.h"
#include "RooAbsPdf.h"
#include "RooProdPdf.h"
#include "RooDataSet.h"
#include "RooRealVar.h"
#include "myPFLHC.C"
#include "RooStats/HypoTestResult.h"
#include "TFile.h"

using namespace RooFit;
using namespace RooStats;

HypoTestResult* testMyPFLHC(const char *filename="finalfitworkskace_v2.root") {
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
   myPFLHC pl(*data,*model,RooArgSet(*thePoi));
   // pl.SetGlobalObservables(RooArgSet(eb_nom));
   pl.SetNuisanceParameters(RooArgSet(*(w->var("eb"))));
   pl.SetMinos(true);
   pl.SetExtended(true);
   pl.SetNCPU(4);
   // pl.SetConstraints(RooArgSet(ebconstraint));
   pl.SetConstraints(new RooArgSet(*(w->function("ebconstraint"))));
   RooArgSet *nullParams = new RooArgSet(*thePoi);
   nullParams->setRealValue("xsec",0);
   pl.SetNullParameters(*nullParams);
   // pl.GetInterval();
   HypoTestResult *r = pl.GetHypoTest();
   r->Print();
   return r;
}
