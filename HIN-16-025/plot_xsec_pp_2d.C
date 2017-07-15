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
void plot_xsec_pp_2d(double rap) {
   TCanvas *c1 = new TCanvas();

   TString rap14009, rap16025;

   // pp
   double ptlow_024_pp[9] = {6.5,7.5,8.5,9.5,11,13,15,20,30};
   double pthigh_024_pp[9] = {7.5,8.5,9.5,11,13,15,20,30,50};
   double xsec_024_pp[9] = {10.034,5.219,2.829,1.443,0.595,0.247,0.074,0.011,0.001};
   double xsecstat_024_pp[9] = {0.117,0.053,0.028,0.013,0.006,0.003,0.001,0.000,0.000};
   double xsecsyst_024_pp[9] = {0.580,0.256,0.119,0.053,0.020,0.008,0.002,0.000,0.000};

   double ptlow_006_pp[5] = {6.5,8.5,9.5,11,15};
   double pthigh_006_pp[5] = {8.5,9.5,11,15,50};
   double xsec_006_pp[5] = {8.605,3.258,1.676,0.483,0.017};
   double xsecstat_006_pp[5] = {0.179,0.068,0.029,0.007,0.000};
   double xsecsyst_006_pp[5] = {0.636,0.140,0.059,0.015,0.000};

   double ptlow_0612_pp[5] = {6.5,8.5,9.5,11,15};
   double pthigh_0612_pp[5] = {8.5,9.5,11,15,50};
   double xsec_0612_pp[5] = {8.493,3.219,1.601,0.477,0.016};
   double xsecstat_0612_pp[5] = {0.143,0.061,0.026,0.006,0.000};
   double xsecsyst_0612_pp[5] = {0.565,0.138,0.058,0.016,0.001};

   double ptlow_1218_pp[6] = {6.5,7.5,8.5,9.5,11,15};
   double pthigh_1218_pp[6] = {7.5,8.5,9.5,11,15,50};
   double xsec_1218_pp[6] = {10.045,4.970,2.731,1.401,0.422,0.013};
   double xsecstat_1218_pp[6] = {0.171,0.084,0.049,0.023,0.006,0.000};
   double xsecsyst_1218_pp[6] = {0.565,0.237,0.124,0.059,0.018,0.001};

   double ptlow_1824_pp[9] = {3,4.5,5.5,6.5,7.5,8.5,9.5,11,15};
   double pthigh_1824_pp[9] = {4.5,5.5,6.5,7.5,8.5,9.5,11,15,50};
   double xsec_1824_pp[9] = {68.748,28.655,15.064,7.599,4.216,2.190,1.126,0.303,0.010};
   double xsecstat_1824_pp[9] = {1.522,0.607,0.314,0.159,0.093,0.054,0.026,0.006,0.000};
   double xsecsyst_1824_pp[9] = {6.823,1.904,0.762,0.318,0.159,0.080,0.037,0.009,0.000};

   double br = 1e-3; // nb to mub
   double dy = 2.;// d|y| vs dy

   double *ptlow_pp, *pthigh_pp, *xsec_pp, *xsecstat_pp, *xsecsyst_pp;
   int nbins;
   if (fabs(rap)<0.6) {
      ptlow_pp = ptlow_006_pp;
      pthigh_pp = pthigh_006_pp;
      xsec_pp = xsec_006_pp;
      xsecstat_pp = xsecstat_006_pp;
      xsecsyst_pp = xsecsyst_006_pp;
      nbins = 5;
      rap16025 = "|y|<0.6";
   } else if (fabs(rap)<1.2) {
      ptlow_pp = ptlow_0612_pp;
      pthigh_pp = pthigh_0612_pp;
      xsec_pp = xsec_0612_pp;
      xsecstat_pp = xsecstat_0612_pp;
      xsecsyst_pp = xsecsyst_0612_pp;
      nbins = 6;
      rap16025 = "0.6<|y|<1.2";
   } else if (fabs(rap)<1.8) {
      ptlow_pp = ptlow_1218_pp;
      pthigh_pp = pthigh_1218_pp;
      xsec_pp = xsec_1218_pp;
      xsecstat_pp = xsecstat_1218_pp;
      xsecsyst_pp = xsecsyst_1218_pp;
      nbins = 6;
      rap16025 = "1.2<|y|<1.8";
   } else {
      ptlow_pp = ptlow_1824_pp;
      pthigh_pp = pthigh_1824_pp;
      xsec_pp = xsec_1824_pp;
      xsecstat_pp = xsecstat_1824_pp;
      xsecsyst_pp = xsecsyst_1824_pp;
      nbins = 9;
      rap16025 = "1.8<|y|<2.4";
   }

   TGraphErrors *tgpp_stat = new TGraphErrors(nbins);
   for (int i=0; i<nbins; i++) {
      tgpp_stat->SetPoint(i,(ptlow_pp[i]+pthigh_pp[i])/2.,xsec_pp[i]*br/dy);
      tgpp_stat->SetPointError(i,tgpp_stat->GetX()[i]-ptlow_pp[i],xsecstat_pp[i]*br/dy);
   }
   // tgpp_stat->SetLineWidth(3);
   tgpp_stat->Draw("AP");
   TGraphErrors *tgpp_syst = new TGraphErrors(nbins);
   for (int i=0; i<nbins; i++) {
      tgpp_syst->SetPoint(i,(ptlow_pp[i]+pthigh_pp[i])/2.,xsec_pp[i]*br/dy);
      tgpp_syst->SetPointError(i,tgpp_syst->GetX()[i]-ptlow_pp[i],xsecsyst_pp[i]*br/dy);
   }
   // tgpp_syst->SetLineColor(kRed);
   tgpp_syst->SetFillStyle(0);
   tgpp_syst->Draw("2");

   // pp
   TFile *f = TFile::Open("HEPData-ins1512296-v1-Table2.root");
   TH1F *ym1c = (TH1F*) f->Get("Table 2/Hist1D_y1");
   TH1F *ym1stat = (TH1F*) f->Get("Table 2/Hist1D_y1_e1");
   TH1F *ym1syst = (TH1F*) f->Get("Table 2/Hist1D_y1_e2");
   TH1F *ym2c = (TH1F*) f->Get("Table 2/Hist1D_y2");
   TH1F *ym2stat = (TH1F*) f->Get("Table 2/Hist1D_y2_e1");
   TH1F *ym2syst = (TH1F*) f->Get("Table 2/Hist1D_y2_e2");
   TH1F *ym3c = (TH1F*) f->Get("Table 2/Hist1D_y3");
   TH1F *ym3stat = (TH1F*) f->Get("Table 2/Hist1D_y3_e1");
   TH1F *ym3syst = (TH1F*) f->Get("Table 2/Hist1D_y3_e2");
   TH1F *ym4c = (TH1F*) f->Get("Table 2/Hist1D_y4");
   TH1F *ym4stat = (TH1F*) f->Get("Table 2/Hist1D_y4_e1");
   TH1F *ym4syst = (TH1F*) f->Get("Table 2/Hist1D_y4_e2");
   TFile *f2 = TFile::Open("HEPData-ins1512296-v1-Table1.root");
   TH1F *yp1c = (TH1F*) f2->Get("Table 1/Hist1D_y1");
   TH1F *yp1stat = (TH1F*) f2->Get("Table 1/Hist1D_y1_e1");
   TH1F *yp1syst = (TH1F*) f2->Get("Table 1/Hist1D_y1_e2");
   TH1F *yp2c = (TH1F*) f2->Get("Table 1/Hist1D_y2");
   TH1F *yp2stat = (TH1F*) f2->Get("Table 1/Hist1D_y2_e1");
   TH1F *yp2syst = (TH1F*) f2->Get("Table 1/Hist1D_y2_e2");
   TH1F *yp3c = (TH1F*) f2->Get("Table 1/Hist1D_y3");
   TH1F *yp3stat = (TH1F*) f2->Get("Table 1/Hist1D_y3_e1");
   TH1F *yp3syst = (TH1F*) f2->Get("Table 1/Hist1D_y3_e2");
   TH1F *yp4c = (TH1F*) f2->Get("Table 1/Hist1D_y4");
   TH1F *yp4stat = (TH1F*) f2->Get("Table 1/Hist1D_y4_e1");
   TH1F *yp4syst = (TH1F*) f2->Get("Table 1/Hist1D_y4_e2");

   TH1F *ym1 = makeHist(ym1c,ym1stat);
   TH1F *ym2 = makeHist(ym2c,ym2stat);
   TH1F *ym3 = makeHist(ym3c,ym3stat);
   TH1F *ym4 = makeHist(ym4c,ym4stat);
   TH1F *yp1 = makeHist(yp1c,yp1stat);
   TH1F *yp2 = makeHist(yp2c,yp2stat);
   TH1F *yp3 = makeHist(yp3c,yp3stat);
   TH1F *yp4 = makeHist(yp4c,yp4stat);
   TH1F *ym1s = makeHist(ym1c,ym1syst);
   TH1F *ym2s = makeHist(ym2c,ym2syst);
   TH1F *ym3s = makeHist(ym3c,ym3syst);
   TH1F *ym4s = makeHist(ym4c,ym4syst);
   TH1F *yp1s = makeHist(yp1c,yp1syst);
   TH1F *yp2s = makeHist(yp2c,yp2syst);
   TH1F *yp3s = makeHist(yp3c,yp3syst);
   TH1F *yp4s = makeHist(yp4c,yp4syst);

   TH1F *yp, *ypsyst;
   TH1F *ym, *ymsyst;

   if (fabs(rap)<0.9) {
      yp = yp4;
      ypsyst = yp4s;
      ym = ym1;
      ymsyst = ym1s;
      rap14009 = "|y|<0.9";
   } else if (fabs(rap)<1.5) {
      yp = yp3;
      ypsyst = yp3s;
      ym = ym2;
      ymsyst = ym2s;
      rap14009 = "0.9<|y|<1.5";
   } else if (fabs(rap)<1.93) {
      yp = yp2;
      ypsyst = yp2s;
      ym = ym3;
      ymsyst = ym3s;
      rap14009 = "1.5<|y|<1.93";
   } else {
      yp = yp1;
      ypsyst = yp1s;
      ym = ym4;
      ymsyst = ym4s;
      rap14009 = "1.93<|y|<2.4";
   }

   ypsyst->SetLineColor(kBlue-2);
   ypsyst->SetMarkerColor(kBlue-2);
   ypsyst->SetFillColor(kBlue-2);
   ypsyst->SetFillStyle(0);
   ypsyst->Draw("same E2");
   yp->SetLineColor(kBlue+2);
   yp->SetMarkerColor(kBlue+2);
   yp->Draw("same");
   ymsyst->SetLineColor(kCyan-2);
   ymsyst->SetMarkerColor(kCyan-2);
   ymsyst->SetFillColor(kCyan-2);
   ymsyst->SetFillStyle(0);
   ymsyst->Draw("same E2");
   ym->SetLineColor(kCyan+2);
   ym->SetMarkerColor(kCyan+2);
   ym->Draw("same");

   // make the plot less ugly
   tgpp_stat->GetHistogram()->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   tgpp_stat->GetHistogram()->GetXaxis()->SetRangeUser(0,50);
   tgpp_stat->GetHistogram()->GetYaxis()->SetTitle("B #times d^{2}#sigma / dp_{T} dy [#mub / GeV/c]");
   tgpp_stat->GetHistogram()->GetYaxis()->SetRangeUser(1e-6,1e-1);
   TLegend *tleg = new TLegend(0.6,0.6,0.9,0.9);
   tleg->SetBorderSize(0);
   tleg->AddEntry(tgpp_stat,Form("16-025, %s",rap16025.Data()),"LP");
   tleg->AddEntry(yp,Form("14-009, %s, y>0",rap14009.Data()),"LP");
   tleg->AddEntry(ym,Form("14-009, %s, y<0",rap14009.Data()),"LP");
   tleg->Draw();

   c1->SetLogy();
   c1->SaveAs(Form("plot_pt_rap%.1f.pdf",rap));
}
