// helper functions
TH1F* makeHist(TH1F* hc, TH1F* he) {
   int n = hc->GetNbinsX();
   TH1F *ans = (TH1F*) hc->Clone(TString(hc->GetName()) + "_clone");
   for (int i=0; i<=n+1; i++) {
      ans->SetBinError(i,he->GetBinContent(i));
   }
   return ans;
}

TH1F* sum(TH1F* h1, TH1F* h2, double s1, double s2) {
   int n = h1->GetNbinsX();
   TH1F *ans = (TH1F*) h1->Clone(TString(h1->GetName()) + "_clone");
   for (int i=0; i<=n+1; i++) {
      int i2 = h2->FindBin(h1->GetBinCenter(i));
      ans->SetBinContent(i,h1->GetBinContent(i)*s1+h2->GetBinContent(i2)*s2);
      ans->SetBinError(i,sqrt(pow(h1->GetBinError(i)*s1,2)+pow(h2->GetBinError(i2)*s2,2)));
   }
   return ans;
}

// main function
void plot_xsec_pp() {
   // pbpb
   double ptlow_024_pbpb[9] = {6.5,7.5,8.5,9.5,11,13,15,20,30};
   double pthigh_024_pbpb[9] = {7.5,8.5,9.5,11,13,15,20,30,50};
   double xsec_024_pbpb[9] = {10.034,5.219,2.829,1.443,0.595,0.247,0.074,0.011,0.001};
   double xsecstat_024_pbpb[9] = {0.117,0.053,0.028,0.013,0.006,0.003,0.001,0.000,0.000};
   double xsecsyst_024_pbpb[9] = {0.580,0.256,0.119,0.053,0.020,0.008,0.002,0.000,0.000};
   double br = 1e-3; // nb to mub
   double dy = 1.;//4.8;

   TGraphErrors *tgpbpb_stat = new TGraphErrors(9);
   for (int i=0; i<9; i++) {
      tgpbpb_stat->SetPoint(i,(ptlow_024_pbpb[i]+pthigh_024_pbpb[i])/2.,xsec_024_pbpb[i]*br/dy);
      tgpbpb_stat->SetPointError(i,tgpbpb_stat->GetX()[i]-ptlow_024_pbpb[i],xsecstat_024_pbpb[i]*br/dy);
   }
   tgpbpb_stat->SetLineWidth(3);
   tgpbpb_stat->Draw("AP");
   TGraphErrors *tgpbpb_syst = new TGraphErrors(9);
   for (int i=0; i<9; i++) {
      tgpbpb_syst->SetPoint(i,(ptlow_024_pbpb[i]+pthigh_024_pbpb[i])/2.,xsec_024_pbpb[i]*br/dy);
      tgpbpb_syst->SetPointError(i,tgpbpb_syst->GetX()[i]-ptlow_024_pbpb[i],xsecsyst_024_pbpb[i]*br/dy);
   }
   tgpbpb_syst->SetLineColor(kRed);
   tgpbpb_syst->Draw("P");

   // pp
   TFile *f = TFile::Open("HEPData-ins1512296-v1-Table1.root");
   TH1F *y1c = (TH1F*) f->Get("Table 1/Hist1D_y1");
   TH1F *y1stat = (TH1F*) f->Get("Table 1/Hist1D_y1_e1");
   TH1F *y1syst = (TH1F*) f->Get("Table 1/Hist1D_y1_e2");
   TH1F *y2c = (TH1F*) f->Get("Table 1/Hist1D_y2");
   TH1F *y2stat = (TH1F*) f->Get("Table 1/Hist1D_y2_e1");
   TH1F *y2syst = (TH1F*) f->Get("Table 1/Hist1D_y2_e2");
   TH1F *y3c = (TH1F*) f->Get("Table 1/Hist1D_y3");
   TH1F *y3stat = (TH1F*) f->Get("Table 1/Hist1D_y3_e1");
   TH1F *y3syst = (TH1F*) f->Get("Table 1/Hist1D_y3_e2");
   TH1F *y4c = (TH1F*) f->Get("Table 1/Hist1D_y4");
   TH1F *y4stat = (TH1F*) f->Get("Table 1/Hist1D_y4_e1");
   TH1F *y4syst = (TH1F*) f->Get("Table 1/Hist1D_y4_e2");
   TFile *f2 = TFile::Open("HEPData-ins1512296-v1-Table2.root");
   TH1F *yp1c = (TH1F*) f->Get("Table 1/Hist1D_y1");
   TH1F *yp1stat = (TH1F*) f->Get("Table 1/Hist1D_y1_e1");
   TH1F *yp1syst = (TH1F*) f->Get("Table 1/Hist1D_y1_e2");
   TH1F *yp2c = (TH1F*) f->Get("Table 1/Hist1D_y2");
   TH1F *yp2stat = (TH1F*) f->Get("Table 1/Hist1D_y2_e1");
   TH1F *yp2syst = (TH1F*) f->Get("Table 1/Hist1D_y2_e2");
   TH1F *yp3c = (TH1F*) f->Get("Table 1/Hist1D_y3");
   TH1F *yp3stat = (TH1F*) f->Get("Table 1/Hist1D_y3_e1");
   TH1F *yp3syst = (TH1F*) f->Get("Table 1/Hist1D_y3_e2");
   TH1F *yp4c = (TH1F*) f->Get("Table 1/Hist1D_y4");
   TH1F *yp4stat = (TH1F*) f->Get("Table 1/Hist1D_y4_e1");
   TH1F *yp4syst = (TH1F*) f->Get("Table 1/Hist1D_y4_e2");

   TH1F *y1 = makeHist(y1c,y1stat);
   TH1F *y2 = makeHist(y2c,y2stat);
   TH1F *y3 = makeHist(y3c,y3stat);
   TH1F *y4 = makeHist(y4c,y4stat);
   TH1F *yp1 = makeHist(yp1c,yp1stat);
   TH1F *yp2 = makeHist(yp2c,yp2stat);
   TH1F *yp3 = makeHist(yp3c,yp3stat);
   TH1F *yp4 = makeHist(yp4c,yp4stat);

   TH1F *y12 = sum(y1,y2,2.4-1.93,1.93-1.5); // we integrate by multiplying by dy
   TH1F *y123 = sum(y12,y3,1.,1.5-0.9);
   TH1F *y1234 = sum(y123,y4,1.,0.9);
   TH1F *z1 = sum(y1234,yp1,1.,0.9);
   TH1F *z12 = sum(z1,yp2,1.,1.5-0.9);
   TH1F *z123 = sum(z12,yp3,1.,1.93-1.5);
   TH1F *z1234 = sum(z123,yp4,1.,2.4-1.93);
   z1234->Scale(1./2.4); // divide by d|y|

   z1234->SetLineColor(kBlue);
   z1234->SetMarkerColor(kBlue);
   z1234->Draw("same");
}
