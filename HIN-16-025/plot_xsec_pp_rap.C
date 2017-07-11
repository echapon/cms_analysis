// helper functions
TH1F* makeHist(TH1F* hc, TH1F* he) {
   int n = hc->GetNbinsX();
   TH1F *ans = (TH1F*) hc->Clone(TString(hc->GetName()) + "_clone");
   for (int i=0; i<=n+1; i++) {
      ans->SetBinError(i,he->GetBinContent(i));
   }
   return ans;
}

TH1F* sum(TH1F* h1, TH1F* h2) {
   int n = h1->GetNbinsX();
   TH1F *ans = (TH1F*) h1->Clone(TString(h1->GetName()) + "_clone");
   for (int i=0; i<=n+1; i++) {
      int i2 = h2->FindBin(h1->GetBinCenter(i));
      ans->SetBinContent(i,h1->GetBinContent(i)+h2->GetBinContent(i2));
      ans->SetBinError(i,sqrt(pow(h1->GetBinError(i),2)+pow(h2->GetBinError(i2),2)));
   }
   return ans;
}

// main function
void plot_xsec_pp_rap() {
   // pbpb
   double raplow_024_pbpb[6] = {0,0.4,0.8,1.2,1.6,2};
   double raphigh_024_pbpb[6] = {0.4,0.8,1.2,1.6,2,2.4};
   double xsec_024_pbpb[6] = {0.589,0.586,0.573,0.518,0.460,0.381};
   double xsecstat_024_pbpb[6] = {0.006,0.005,0.005,0.004,0.004,0.005};
   double xsecsyst_024_pbpb[6] = {0.025,0.026,0.026,0.025,0.020,0.012};
   double br = 5.961e-2;
   double dy = 2./0.75; // the factor 2 is because 16-025 is |y| while 14-009 is y. But what is this 0.75???

   TGraphErrors *tgpbpb_stat = new TGraphErrors(6);
   for (int i=0; i<6; i++) {
      tgpbpb_stat->SetPoint(i,(raplow_024_pbpb[i]+raphigh_024_pbpb[i])/2.,xsec_024_pbpb[i]*br/dy);
      tgpbpb_stat->SetPointError(i,tgpbpb_stat->GetX()[i]-raplow_024_pbpb[i],xsecstat_024_pbpb[i]*br/dy);
   }
   tgpbpb_stat->SetLineWidth(3);
   tgpbpb_stat->Draw("AP");
   TGraphErrors *tgpbpb_syst = new TGraphErrors(6);
   for (int i=0; i<6; i++) {
      tgpbpb_syst->SetPoint(i,(raplow_024_pbpb[i]+raphigh_024_pbpb[i])/2.,xsec_024_pbpb[i]*br/dy);
      tgpbpb_syst->SetPointError(i,tgpbpb_syst->GetX()[i]-raplow_024_pbpb[i],xsecsyst_024_pbpb[i]*br/dy);
   }
   tgpbpb_syst->SetLineColor(kRed);
   tgpbpb_syst->Draw("P");

   // pp
   TFile *f = TFile::Open("HEPData-ins1512296-v1-Table5.root");
   TH1F *y1c = (TH1F*) f->Get("Table 5/Hist1D_y1");
   TH1F *y1stat = (TH1F*) f->Get("Table 5/Hist1D_y1_e1");
   TH1F *y1syst = (TH1F*) f->Get("Table 5/Hist1D_y1_e2");
   TH1F *y2c = (TH1F*) f->Get("Table 5/Hist1D_y2");
   TH1F *y2stat = (TH1F*) f->Get("Table 5/Hist1D_y2_e1");
   TH1F *y2syst = (TH1F*) f->Get("Table 5/Hist1D_y2_e2");

   TH1F *y1 = makeHist(y1c,y1stat);
   TH1F *y2 = makeHist(y2c,y2stat);

   TH1F *y12 = sum(y1,y2);

   y12->SetLineColor(kBlue);
   y12->SetMarkerColor(kBlue);
   y12->Draw("same");
}
