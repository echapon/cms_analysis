#include "tdrstyle.C"
#include "CMS_lumi.C"

void total()
{
   setTDRStyle();
//=========Macro generated from canvas: total/total
//=========  (Thu Sep  7 22:21:06 2017) by ROOT version6.02/05
  int H_ref = 800; 
  int W_ref = 800; 
  int W = W_ref;
  int H = H_ref;

  // references for T, B, L, R
  float T = 0.08*H_ref;
  float B = 0.12*H_ref; 
  float L = 0.12*W_ref;
  float R = 0.04*W_ref;

  TString totalName = "canv";

  TCanvas* total = new TCanvas(totalName,totalName,50,50,W,H);
  total->SetFillColor(0);
  total->SetBorderMode(0);
  total->SetFrameFillStyle(0);
  total->SetFrameBorderMode(0);
  total->SetLeftMargin( L/W );
  total->SetRightMargin( R/W );
  total->SetTopMargin( T/H );
  total->SetBottomMargin( B/H );
  total->SetTickx(0);
  total->SetTicky(0);
  
// ------------>Primitives in pad: pad
   TPad *pad = new TPad("pad", "pad",0,0,1,1);
   pad->Draw();
   pad->cd();
   pad->Range(20.54956,-1.170732,74.48937,8.585366);
   pad->SetFillColor(0);
   pad->SetBorderMode(0);
   pad->SetBorderSize(0);
   pad->SetLeftMargin(0.1114286);
   pad->SetRightMargin(0.03428571);
   pad->SetTopMargin(0.06);
   pad->SetBottomMargin(0.12);
   pad->SetFrameFillStyle(0);
   pad->SetFrameBorderMode(0);
   pad->SetFrameFillStyle(0);
   pad->SetFrameBorderMode(0);
   
   Double_t total_fx1[50] = {
   30.4,
   31.2,
   32,
   32.8,
   33.6,
   34.4,
   35.2,
   36,
   36.8,
   37.6,
   38.4,
   39.2,
   40,
   40.8,
   41.6,
   42.4,
   43.2,
   44,
   44.8,
   45.27517,
   45.6,
   46.4,
   47.2,
   48,
   48.8,
   49.6,
   50.4,
   51.2,
   52,
   52.8,
   53.6,
   54.4,
   55.2,
   56,
   56.8,
   57.6,
   58.4,
   59.2,
   60,
   60.8,
   61.6,
   62.4,
   63.2,
   64,
   64.8,
   65.6,
   66.4,
   67.2,
   68,
   68.8};
   Double_t total_fy1[50] = {
   4.935491,
   4.40535,
   3.905356,
   3.436429,
   2.99615,
   2.585262,
   2.202837,
   1.848512,
   1.521291,
   1.224859,
   0.9653591,
   0.740239,
   0.5483523,
   0.3878802,
   0.2570296,
   0.1545826,
   0.07901739,
   0.02910855,
   0.003817996,
   0,
   0.00197147,
   0.02269009,
   0.06447594,
   0.1269612,
   0.2091303,
   0.3102615,
   0.4292446,
   0.5658069,
   0.7186598,
   0.8879853,
   1.072373,
   1.27197,
   1.485874,
   1.713763,
   1.954772,
   2.208867,
   2.475128,
   2.753629,
   3.043539,
   3.344205,
   3.65629,
   3.978506,
   4.308592,
   4.650569,
   5.002406,
   5.363531,
   5.733358,
   6.112096,
   6.498969,
   6.894057};
   TGraph *graph = new TGraph(50,total_fx1,total_fy1);
   graph->SetName("total");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   graph->SetMarkerColor(0);
   graph->SetMarkerStyle(20);
   graph->SetMarkerSize(0.7);
   
   TH1F *Graph_total1 = new TH1F("Graph_total1","Graph",100,26.56,72.64);
   Graph_total1->SetMinimum(0);
   Graph_total1->SetMaximum(8);
   Graph_total1->SetDirectory(0);
   Graph_total1->SetStats(0);
   Graph_total1->SetLineStyle(0);
   Graph_total1->SetMarkerStyle(20);
   Graph_total1->SetMarkerSize(0.7);
   Graph_total1->GetXaxis()->SetTitle("#sigma [nb]");
   Graph_total1->GetXaxis()->SetLabelFont(42);
   Graph_total1->GetXaxis()->SetTitleSize(0.05);
   Graph_total1->GetXaxis()->SetTickLength(0.02);
   Graph_total1->GetXaxis()->SetTitleOffset(1.08);
   Graph_total1->GetXaxis()->SetTitleFont(42);
   Graph_total1->GetYaxis()->SetTitle("#minus2 ln #Lambda (#sigma)");
   Graph_total1->GetYaxis()->SetLabelFont(42);
   Graph_total1->GetYaxis()->SetLabelOffset(0.007);
   Graph_total1->GetYaxis()->SetTitleSize(0.05);
   Graph_total1->GetYaxis()->SetTickLength(0.02);
   Graph_total1->GetYaxis()->SetTitleOffset(1.028571);
   Graph_total1->GetYaxis()->SetTitleFont(42);
   Graph_total1->GetZaxis()->SetLabelFont(42);
   Graph_total1->GetZaxis()->SetLabelOffset(0.007);
   Graph_total1->GetZaxis()->SetTitleSize(0.05);
   Graph_total1->GetZaxis()->SetTickLength(0.02);
   Graph_total1->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_total1);
   
   graph->Draw("ap");
   TLine *line = new TLine(26.56,1,72.64,1);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff0000");
   line->SetLineColor(ci);
   line->Draw();
   line = new TLine(38.28651,0,38.28651,1);

   ci = TColor::GetColor("#ff0000");
   line->SetLineColor(ci);
   line->Draw();
   line = new TLine(53.29373,0,53.29373,1);

   ci = TColor::GetColor("#ff0000");
   line->SetLineColor(ci);
   line->Draw();
   line = new TLine(26.56,3.87,72.64,3.87);

   ci = TColor::GetColor("#ff0000");
   line->SetLineColor(ci);
   line->Draw();
   line = new TLine(32.05855,0,32.05855,3.87);

   ci = TColor::GetColor("#ff0000");
   line->SetLineColor(ci);
   line->Draw();
   line = new TLine(62.13278,0,62.13278,3.87);

   ci = TColor::GetColor("#ff0000");
   line->SetLineColor(ci);
   line->Draw();
   
   TGraph *splinefn01 = new TGraph(201);
    //The original function :  had originally been created by:
    //TF1 *splinefn0 = new TF1("splinefn0",,30.4,68.8,1);
//    splinefn01->SetRange(30.4,68.8);
   double xmin = 30.4;
   double xmax = 68.8;
   splinefn01->SetName("splinefn0");
   splinefn01->SetTitle("");
//    splinefn01->SetNpx(200);
   int i=0;
   splinefn01->SetPoint(0,xmin+i*(xmax-xmin)/200.,4.935491);i++;
   splinefn01->SetPoint(1,xmin+i*(xmax-xmin)/200.,4.80562);i++;
   splinefn01->SetPoint(2,xmin+i*(xmax-xmin)/200.,4.677393);i++;
   splinefn01->SetPoint(3,xmin+i*(xmax-xmin)/200.,4.550841);i++;
   splinefn01->SetPoint(4,xmin+i*(xmax-xmin)/200.,4.425992);i++;
   splinefn01->SetPoint(5,xmin+i*(xmax-xmin)/200.,4.302874);i++;
   splinefn01->SetPoint(6,xmin+i*(xmax-xmin)/200.,4.181516);i++;
   splinefn01->SetPoint(7,xmin+i*(xmax-xmin)/200.,4.061948);i++;
   splinefn01->SetPoint(8,xmin+i*(xmax-xmin)/200.,3.944198);i++;
   splinefn01->SetPoint(9,xmin+i*(xmax-xmin)/200.,3.828289);i++;
   splinefn01->SetPoint(10,xmin+i*(xmax-xmin)/200.,3.714191);i++;
   splinefn01->SetPoint(11,xmin+i*(xmax-xmin)/200.,3.601837);i++;
   splinefn01->SetPoint(12,xmin+i*(xmax-xmin)/200.,3.49116);i++;
   splinefn01->SetPoint(13,xmin+i*(xmax-xmin)/200.,3.382094);i++;
   splinefn01->SetPoint(14,xmin+i*(xmax-xmin)/200.,3.274626);i++;
   splinefn01->SetPoint(15,xmin+i*(xmax-xmin)/200.,3.168793);i++;
   splinefn01->SetPoint(16,xmin+i*(xmax-xmin)/200.,3.064636);i++;
   splinefn01->SetPoint(17,xmin+i*(xmax-xmin)/200.,2.962195);i++;
   splinefn01->SetPoint(18,xmin+i*(xmax-xmin)/200.,2.861483);i++;
   splinefn01->SetPoint(19,xmin+i*(xmax-xmin)/200.,2.762472);i++;
   splinefn01->SetPoint(20,xmin+i*(xmax-xmin)/200.,2.665129);i++;
   splinefn01->SetPoint(21,xmin+i*(xmax-xmin)/200.,2.569424);i++;
   splinefn01->SetPoint(22,xmin+i*(xmax-xmin)/200.,2.475336);i++;
   splinefn01->SetPoint(23,xmin+i*(xmax-xmin)/200.,2.382868);i++;
   splinefn01->SetPoint(24,xmin+i*(xmax-xmin)/200.,2.292033);i++;
   splinefn01->SetPoint(25,xmin+i*(xmax-xmin)/200.,2.202837);i++;
   splinefn01->SetPoint(26,xmin+i*(xmax-xmin)/200.,2.115285);i++;
   splinefn01->SetPoint(27,xmin+i*(xmax-xmin)/200.,2.029346);i++;
   splinefn01->SetPoint(28,xmin+i*(xmax-xmin)/200.,1.944986);i++;
   splinefn01->SetPoint(29,xmin+i*(xmax-xmin)/200.,1.862168);i++;
   splinefn01->SetPoint(30,xmin+i*(xmax-xmin)/200.,1.780865);i++;
   splinefn01->SetPoint(31,xmin+i*(xmax-xmin)/200.,1.701106);i++;
   splinefn01->SetPoint(32,xmin+i*(xmax-xmin)/200.,1.622941);i++;
   splinefn01->SetPoint(33,xmin+i*(xmax-xmin)/200.,1.546422);i++;
   splinefn01->SetPoint(34,xmin+i*(xmax-xmin)/200.,1.471604);i++;
   splinefn01->SetPoint(35,xmin+i*(xmax-xmin)/200.,1.398592);i++;
   splinefn01->SetPoint(36,xmin+i*(xmax-xmin)/200.,1.327522);i++;
   splinefn01->SetPoint(37,xmin+i*(xmax-xmin)/200.,1.258531);i++;
   splinefn01->SetPoint(38,xmin+i*(xmax-xmin)/200.,1.191751);i++;
   splinefn01->SetPoint(39,xmin+i*(xmax-xmin)/200.,1.127206);i++;
   splinefn01->SetPoint(40,xmin+i*(xmax-xmin)/200.,1.064812);i++;
   splinefn01->SetPoint(41,xmin+i*(xmax-xmin)/200.,1.004479);i++;
   splinefn01->SetPoint(42,xmin+i*(xmax-xmin)/200.,0.9461207);i++;
   splinefn01->SetPoint(43,xmin+i*(xmax-xmin)/200.,0.8896827);i++;
   splinefn01->SetPoint(44,xmin+i*(xmax-xmin)/200.,0.8351675);i++;
   splinefn01->SetPoint(45,xmin+i*(xmax-xmin)/200.,0.7825818);i++;
   splinefn01->SetPoint(46,xmin+i*(xmax-xmin)/200.,0.7319322);i++;
   splinefn01->SetPoint(47,xmin+i*(xmax-xmin)/200.,0.6832151);i++;
   splinefn01->SetPoint(48,xmin+i*(xmax-xmin)/200.,0.6364014);i++;
   splinefn01->SetPoint(49,xmin+i*(xmax-xmin)/200.,0.5914581);i++;
   splinefn01->SetPoint(50,xmin+i*(xmax-xmin)/200.,0.5483522);i++;
   splinefn01->SetPoint(51,xmin+i*(xmax-xmin)/200.,0.507052);i++;
   splinefn01->SetPoint(52,xmin+i*(xmax-xmin)/200.,0.4675306);i++;
   splinefn01->SetPoint(53,xmin+i*(xmax-xmin)/200.,0.429762);i++;
   splinefn01->SetPoint(54,xmin+i*(xmax-xmin)/200.,0.3937207);i++;
   splinefn01->SetPoint(55,xmin+i*(xmax-xmin)/200.,0.3593821);i++;
   splinefn01->SetPoint(56,xmin+i*(xmax-xmin)/200.,0.32673);i++;
   splinefn01->SetPoint(57,xmin+i*(xmax-xmin)/200.,0.2957517);i++;
   splinefn01->SetPoint(58,xmin+i*(xmax-xmin)/200.,0.2664347);i++;
   splinefn01->SetPoint(59,xmin+i*(xmax-xmin)/200.,0.2387656);i++;
   splinefn01->SetPoint(60,xmin+i*(xmax-xmin)/200.,0.2127243);i++;
   splinefn01->SetPoint(61,xmin+i*(xmax-xmin)/200.,0.1882865);i++;
   splinefn01->SetPoint(62,xmin+i*(xmax-xmin)/200.,0.1654277);i++;
   splinefn01->SetPoint(63,xmin+i*(xmax-xmin)/200.,0.1441235);i++;
   splinefn01->SetPoint(64,xmin+i*(xmax-xmin)/200.,0.1243539);i++;
   splinefn01->SetPoint(65,xmin+i*(xmax-xmin)/200.,0.1061031);i++;
   splinefn01->SetPoint(66,xmin+i*(xmax-xmin)/200.,0.08935529);i++;
   splinefn01->SetPoint(67,xmin+i*(xmax-xmin)/200.,0.07409489);i++;
   splinefn01->SetPoint(68,xmin+i*(xmax-xmin)/200.,0.06030667);i++;
   splinefn01->SetPoint(69,xmin+i*(xmax-xmin)/200.,0.04797618);i++;
   splinefn01->SetPoint(70,xmin+i*(xmax-xmin)/200.,0.03708901);i++;
   splinefn01->SetPoint(71,xmin+i*(xmax-xmin)/200.,0.02763076);i++;
   splinefn01->SetPoint(72,xmin+i*(xmax-xmin)/200.,0.01958744);i++;
   splinefn01->SetPoint(73,xmin+i*(xmax-xmin)/200.,0.01294608);i++;
   splinefn01->SetPoint(74,xmin+i*(xmax-xmin)/200.,0.007693862);i++;
   splinefn01->SetPoint(75,xmin+i*(xmax-xmin)/200.,0.003817968);i++;
   splinefn01->SetPoint(76,xmin+i*(xmax-xmin)/200.,0.001301522);i++;
   splinefn01->SetPoint(77,xmin+i*(xmax-xmin)/200.,0.0001114182);i++;
   splinefn01->SetPoint(78,xmin+i*(xmax-xmin)/200.,0.0002124564);i++;
   splinefn01->SetPoint(79,xmin+i*(xmax-xmin)/200.,0.001609659);i++;
   splinefn01->SetPoint(80,xmin+i*(xmax-xmin)/200.,0.004337615);i++;
   splinefn01->SetPoint(81,xmin+i*(xmax-xmin)/200.,0.008378544);i++;
   splinefn01->SetPoint(82,xmin+i*(xmax-xmin)/200.,0.01369271);i++;
   splinefn01->SetPoint(83,xmin+i*(xmax-xmin)/200.,0.02024032);i++;
   splinefn01->SetPoint(84,xmin+i*(xmax-xmin)/200.,0.02798391);i++;
   splinefn01->SetPoint(85,xmin+i*(xmax-xmin)/200.,0.03691342);i++;
   splinefn01->SetPoint(86,xmin+i*(xmax-xmin)/200.,0.04703643);i++;
   splinefn01->SetPoint(87,xmin+i*(xmax-xmin)/200.,0.0583608);i++;
   splinefn01->SetPoint(88,xmin+i*(xmax-xmin)/200.,0.07089379);i++;
   splinefn01->SetPoint(89,xmin+i*(xmax-xmin)/200.,0.08462823);i++;
   splinefn01->SetPoint(90,xmin+i*(xmax-xmin)/200.,0.09954254);i++;
   splinefn01->SetPoint(91,xmin+i*(xmax-xmin)/200.,0.1156145);i++;
   splinefn01->SetPoint(92,xmin+i*(xmax-xmin)/200.,0.1328221);i++;
   splinefn01->SetPoint(93,xmin+i*(xmax-xmin)/200.,0.1511501);i++;
   splinefn01->SetPoint(94,xmin+i*(xmax-xmin)/200.,0.1705944);i++;
   splinefn01->SetPoint(95,xmin+i*(xmax-xmin)/200.,0.1911516);i++;
   splinefn01->SetPoint(96,xmin+i*(xmax-xmin)/200.,0.2128186);i++;
   splinefn01->SetPoint(97,xmin+i*(xmax-xmin)/200.,0.2355863);i++;
   splinefn01->SetPoint(98,xmin+i*(xmax-xmin)/200.,0.2594325);i++;
   splinefn01->SetPoint(99,xmin+i*(xmax-xmin)/200.,0.2843325);i++;
   splinefn01->SetPoint(100,xmin+i*(xmax-xmin)/200.,0.3102619);i++;
   splinefn01->SetPoint(101,xmin+i*(xmax-xmin)/200.,0.3372017);i++;
   splinefn01->SetPoint(102,xmin+i*(xmax-xmin)/200.,0.3651556);i++;
   splinefn01->SetPoint(103,xmin+i*(xmax-xmin)/200.,0.3941327);i++;
   splinefn01->SetPoint(104,xmin+i*(xmax-xmin)/200.,0.424142);i++;
   splinefn01->SetPoint(105,xmin+i*(xmax-xmin)/200.,0.4551886);i++;
   splinefn01->SetPoint(106,xmin+i*(xmax-xmin)/200.,0.4872493);i++;
   splinefn01->SetPoint(107,xmin+i*(xmax-xmin)/200.,0.5202895);i++;
   splinefn01->SetPoint(108,xmin+i*(xmax-xmin)/200.,0.5542746);i++;
   splinefn01->SetPoint(109,xmin+i*(xmax-xmin)/200.,0.5891729);i++;
   splinefn01->SetPoint(110,xmin+i*(xmax-xmin)/200.,0.6249852);i++;
   splinefn01->SetPoint(111,xmin+i*(xmax-xmin)/200.,0.6617336);i++;
   splinefn01->SetPoint(112,xmin+i*(xmax-xmin)/200.,0.6994403);i++;
   splinefn01->SetPoint(113,xmin+i*(xmax-xmin)/200.,0.7381265);i++;
   splinefn01->SetPoint(114,xmin+i*(xmax-xmin)/200.,0.7777833);i++;
   splinefn01->SetPoint(115,xmin+i*(xmax-xmin)/200.,0.8183726);i++;
   splinefn01->SetPoint(116,xmin+i*(xmax-xmin)/200.,0.8598547);i++;
   splinefn01->SetPoint(117,xmin+i*(xmax-xmin)/200.,0.9021903);i++;
   splinefn01->SetPoint(118,xmin+i*(xmax-xmin)/200.,0.945362);i++;
   splinefn01->SetPoint(119,xmin+i*(xmax-xmin)/200.,0.989386);i++;
   splinefn01->SetPoint(120,xmin+i*(xmax-xmin)/200.,1.034281);i++;
   splinefn01->SetPoint(121,xmin+i*(xmax-xmin)/200.,1.080067);i++;
   splinefn01->SetPoint(122,xmin+i*(xmax-xmin)/200.,1.126751);i++;
   splinefn01->SetPoint(123,xmin+i*(xmax-xmin)/200.,1.174313);i++;
   splinefn01->SetPoint(124,xmin+i*(xmax-xmin)/200.,1.222727);i++;
   splinefn01->SetPoint(125,xmin+i*(xmax-xmin)/200.,1.27197);i++;
   splinefn01->SetPoint(126,xmin+i*(xmax-xmin)/200.,1.322021);i++;
   splinefn01->SetPoint(127,xmin+i*(xmax-xmin)/200.,1.372881);i++;
   splinefn01->SetPoint(128,xmin+i*(xmax-xmin)/200.,1.424555);i++;
   splinefn01->SetPoint(129,xmin+i*(xmax-xmin)/200.,1.477046);i++;
   splinefn01->SetPoint(130,xmin+i*(xmax-xmin)/200.,1.530359);i++;
   splinefn01->SetPoint(131,xmin+i*(xmax-xmin)/200.,1.584477);i++;
   splinefn01->SetPoint(132,xmin+i*(xmax-xmin)/200.,1.639379);i++;
   splinefn01->SetPoint(133,xmin+i*(xmax-xmin)/200.,1.695043);i++;
   splinefn01->SetPoint(134,xmin+i*(xmax-xmin)/200.,1.751449);i++;
   splinefn01->SetPoint(135,xmin+i*(xmax-xmin)/200.,1.808596);i++;
   splinefn01->SetPoint(136,xmin+i*(xmax-xmin)/200.,1.866494);i++;
   splinefn01->SetPoint(137,xmin+i*(xmax-xmin)/200.,1.925153);i++;
   splinefn01->SetPoint(138,xmin+i*(xmax-xmin)/200.,1.984586);i++;
   splinefn01->SetPoint(139,xmin+i*(xmax-xmin)/200.,2.044783);i++;
   splinefn01->SetPoint(140,xmin+i*(xmax-xmin)/200.,2.105723);i++;
   splinefn01->SetPoint(141,xmin+i*(xmax-xmin)/200.,2.167378);i++;
   splinefn01->SetPoint(142,xmin+i*(xmax-xmin)/200.,2.229726);i++;
   splinefn01->SetPoint(143,xmin+i*(xmax-xmin)/200.,2.292755);i++;
   splinefn01->SetPoint(144,xmin+i*(xmax-xmin)/200.,2.356474);i++;
   splinefn01->SetPoint(145,xmin+i*(xmax-xmin)/200.,2.420897);i++;
   splinefn01->SetPoint(146,xmin+i*(xmax-xmin)/200.,2.486035);i++;
   splinefn01->SetPoint(147,xmin+i*(xmax-xmin)/200.,2.551892);i++;
   splinefn01->SetPoint(148,xmin+i*(xmax-xmin)/200.,2.618454);i++;
   splinefn01->SetPoint(149,xmin+i*(xmax-xmin)/200.,2.685706);i++;
   splinefn01->SetPoint(150,xmin+i*(xmax-xmin)/200.,2.75363);i++;
   splinefn01->SetPoint(151,xmin+i*(xmax-xmin)/200.,2.82221);i++;
   splinefn01->SetPoint(152,xmin+i*(xmax-xmin)/200.,2.891431);i++;
   splinefn01->SetPoint(153,xmin+i*(xmax-xmin)/200.,2.961279);i++;
   splinefn01->SetPoint(154,xmin+i*(xmax-xmin)/200.,3.031738);i++;
   splinefn01->SetPoint(155,xmin+i*(xmax-xmin)/200.,3.102799);i++;
   splinefn01->SetPoint(156,xmin+i*(xmax-xmin)/200.,3.174472);i++;
   splinefn01->SetPoint(157,xmin+i*(xmax-xmin)/200.,3.246777);i++;
   splinefn01->SetPoint(158,xmin+i*(xmax-xmin)/200.,3.319737);i++;
   splinefn01->SetPoint(159,xmin+i*(xmax-xmin)/200.,3.39337);i++;
   splinefn01->SetPoint(160,xmin+i*(xmax-xmin)/200.,3.467675);i++;
   splinefn01->SetPoint(161,xmin+i*(xmax-xmin)/200.,3.54264);i++;
   splinefn01->SetPoint(162,xmin+i*(xmax-xmin)/200.,3.618249);i++;
   splinefn01->SetPoint(163,xmin+i*(xmax-xmin)/200.,3.69449);i++;
   splinefn01->SetPoint(164,xmin+i*(xmax-xmin)/200.,3.771317);i++;
   splinefn01->SetPoint(165,xmin+i*(xmax-xmin)/200.,3.848659);i++;
   splinefn01->SetPoint(166,xmin+i*(xmax-xmin)/200.,3.926442);i++;
   splinefn01->SetPoint(167,xmin+i*(xmax-xmin)/200.,4.004594);i++;
   splinefn01->SetPoint(168,xmin+i*(xmax-xmin)/200.,4.083115);i++;
   splinefn01->SetPoint(169,xmin+i*(xmax-xmin)/200.,4.162115);i++;
   splinefn01->SetPoint(170,xmin+i*(xmax-xmin)/200.,4.241715);i++;
   splinefn01->SetPoint(171,xmin+i*(xmax-xmin)/200.,4.322035);i++;
   splinefn01->SetPoint(172,xmin+i*(xmax-xmin)/200.,4.403144);i++;
   splinefn01->SetPoint(173,xmin+i*(xmax-xmin)/200.,4.484987);i++;
   splinefn01->SetPoint(174,xmin+i*(xmax-xmin)/200.,4.567488);i++;
   splinefn01->SetPoint(175,xmin+i*(xmax-xmin)/200.,4.650571);i++;
   splinefn01->SetPoint(176,xmin+i*(xmax-xmin)/200.,4.734175);i++;
   splinefn01->SetPoint(177,xmin+i*(xmax-xmin)/200.,4.8183);i++;
   splinefn01->SetPoint(178,xmin+i*(xmax-xmin)/200.,4.902955);i++;
   splinefn01->SetPoint(179,xmin+i*(xmax-xmin)/200.,4.988152);i++;
   splinefn01->SetPoint(180,xmin+i*(xmax-xmin)/200.,5.073902);i++;
   splinefn01->SetPoint(181,xmin+i*(xmax-xmin)/200.,5.160192);i++;
   splinefn01->SetPoint(182,xmin+i*(xmax-xmin)/200.,5.247004);i++;
   splinefn01->SetPoint(183,xmin+i*(xmax-xmin)/200.,5.334319);i++;
   splinefn01->SetPoint(184,xmin+i*(xmax-xmin)/200.,5.42212);i++;
   splinefn01->SetPoint(185,xmin+i*(xmax-xmin)/200.,5.510409);i++;
   splinefn01->SetPoint(186,xmin+i*(xmax-xmin)/200.,5.599199);i++;
   splinefn01->SetPoint(187,xmin+i*(xmax-xmin)/200.,5.688507);i++;
   splinefn01->SetPoint(188,xmin+i*(xmax-xmin)/200.,5.778344);i++;
   splinefn01->SetPoint(189,xmin+i*(xmax-xmin)/200.,5.868709);i++;
   splinefn01->SetPoint(190,xmin+i*(xmax-xmin)/200.,5.95958);i++;
   splinefn01->SetPoint(191,xmin+i*(xmax-xmin)/200.,6.050936);i++;
   splinefn01->SetPoint(192,xmin+i*(xmax-xmin)/200.,6.142756);i++;
   splinefn01->SetPoint(193,xmin+i*(xmax-xmin)/200.,6.235029);i++;
   splinefn01->SetPoint(194,xmin+i*(xmax-xmin)/200.,6.327759);i++;
   splinefn01->SetPoint(195,xmin+i*(xmax-xmin)/200.,6.420952);i++;
   splinefn01->SetPoint(196,xmin+i*(xmax-xmin)/200.,6.514614);i++;
   splinefn01->SetPoint(197,xmin+i*(xmax-xmin)/200.,6.608749);i++;
   splinefn01->SetPoint(198,xmin+i*(xmax-xmin)/200.,6.703364);i++;
   splinefn01->SetPoint(199,xmin+i*(xmax-xmin)/200.,6.798465);i++;
   splinefn01->SetPoint(200,xmin+i*(xmax-xmin)/200.,6.894057);i++;
//    splinefn01->SetPoint(201,30.4);
//    splinefn01->SetPoint(202,68.8);
   splinefn01->SetFillStyle(0);
   splinefn01->SetMarkerStyle(20);
   splinefn01->SetMarkerSize(0.7);
   splinefn01->SetLineWidth(3);
   splinefn01->GetXaxis()->SetLabelFont(42);
   splinefn01->GetXaxis()->SetTitleSize(0.05);
   splinefn01->GetXaxis()->SetTickLength(0.02);
   splinefn01->GetXaxis()->SetTitleOffset(1.08);
   splinefn01->GetXaxis()->SetTitleFont(42);
   splinefn01->GetYaxis()->SetLabelFont(42);
   splinefn01->GetYaxis()->SetLabelOffset(0.007);
   splinefn01->GetYaxis()->SetTitleSize(0.05);
   splinefn01->GetYaxis()->SetTickLength(0.02);
   splinefn01->GetYaxis()->SetTitleOffset(1.028571);
   splinefn01->GetYaxis()->SetTitleFont(42);
//    splinefn01->SetParameter(0,0);
//    splinefn01->SetParError(0,0);
//    splinefn01->SetParLimits(0,0,0);
   splinefn01->Draw("same");
   TBox *box = new TBox(26.56,5,72.64,8);
   box->SetFillColor(0);
   box->Draw();
   
   TH1F *total_copy1 = new TH1F("total_copy1","Graph",100,26.56,72.64);
   total_copy1->SetMinimum(0);
   total_copy1->SetMaximum(8);
   total_copy1->SetDirectory(0);
   total_copy1->SetStats(0);
   total_copy1->SetLineStyle(0);
   total_copy1->SetMarkerStyle(20);
   total_copy1->SetMarkerSize(0.7);
   total_copy1->GetXaxis()->SetTitle("#sigma [nb]");
   total_copy1->GetXaxis()->SetLabelFont(42);
   total_copy1->GetXaxis()->SetTitleSize(0.05);
   total_copy1->GetXaxis()->SetTickLength(0.02);
   total_copy1->GetXaxis()->SetTitleOffset(1.08);
   total_copy1->GetXaxis()->SetTitleFont(42);
   total_copy1->GetYaxis()->SetTitle("#minus2 ln #Lambda (#sigma)");
   total_copy1->GetYaxis()->SetLabelFont(42);
   total_copy1->GetYaxis()->SetLabelOffset(0.007);
   total_copy1->GetYaxis()->SetTitleSize(0.05);
   total_copy1->GetYaxis()->SetTickLength(0.02);
   total_copy1->GetYaxis()->SetTitleOffset(1.028571);
   total_copy1->GetYaxis()->SetTitleFont(42);
   total_copy1->GetZaxis()->SetLabelFont(42);
   total_copy1->GetZaxis()->SetLabelOffset(0.007);
   total_copy1->GetZaxis()->SetTitleSize(0.05);
   total_copy1->GetZaxis()->SetTickLength(0.02);
   total_copy1->GetZaxis()->SetTitleFont(42);
   total_copy1->Draw("sameaxis");
   
   TPaveText *pt = new TPaveText(0.59,0.82,0.95,0.91,"NDCNB");
   pt->SetFillColor(0);
   pt->SetTextAlign(11);
   pt->SetTextFont(42);
   pt->SetTextSize(0.06);
   TText *AText = pt->AddText("#sigma = 45{}^{#plus 8}_{#minus 7} nb");
   pt->Draw();
   TLatex *   tex;
//    tex = new TLatex(0.1498714,0.9113,"CMS");
// tex->SetNDC();
//    tex->SetTextAlign(13);
//    tex->SetTextSize(0.048);
//    tex->SetLineWidth(2);
//    tex->Draw();
//       tex = new TLatex(0.1498714,0.8537,"#it{Unpublished}");
// tex->SetNDC();
//    tex->SetTextAlign(13);
//    tex->SetTextFont(52);
//    tex->SetTextSize(0.03648);
//    tex->SetLineWidth(2);
//    tex->Draw();
//       tex = new TLatex(0.9657143,0.952,"#lower[-0.1]{174 nb^{-1} (pPb, #sqrt{s_{NN}} = 8.16 TeV)}");
// tex->SetNDC();
//    tex->SetTextAlign(31);
//    tex->SetTextFont(42);
//    tex->SetTextSize(0.036);
//    tex->SetLineWidth(2);
//    tex->Draw();
   
      // writing the lumi information and the CMS "logo"
   CMS_lumi( pad, 111, 11 );

   pad->Update();
   pad->RedrawAxis();
   pad->GetFrame()->Draw();
   pad->Modified();
   total->cd();
   total->Modified();
   total->cd();
   total->SetSelected(total);
}
