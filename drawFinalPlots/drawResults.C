#include "../commonUtilitySys.h"
#include <TRandom3.h>
#include <TFile.h>
#include <TColor.h>

TH1D* mergeSys( TH1D* h1, TH1D* h2) {

  TH1D* hres = (TH1D*)h1->Clone(Form("%s_merged",h1->GetName()) );
  hres->Reset();
  Int_t nBins = h1->GetNbinsX();
  for ( Int_t j=1; j<=nBins ;j++)
    {
      float y1 =  h1->GetBinContent(j);
      float y2 =  h2->GetBinContent(j);
      hres->SetBinContent(j,  sqrt(  y1*y1 + y2*y2) );
      hres->SetBinError(j,  0.00001);
    }
  return hres;
}

void drawResults(bool drawSinglePanels = false) {
  // const int kPPcentral = 1;
  // const int kPPperipheral =2 ;
  // const int kHIcentral =  3;
  // const int kHIperipheral = 4;
  // const int kPADATA = 5;
  // const int kPAMC = 6;
  //const int nPtBin = 4;
  // double ptBin[nPtBin+1] = {40, 50,60,80,9999};

  TH1D* meanJetPt[8];   // [collision] [Before/After variation]
  TH1D* meanJetPtSys[8];   // [collision] [Before/After variation]

  TH1D* meanXjg[8];   // [collision] [Before/After variation]
  TH1D* meanXjgSys[8];   // [collision] [Before/After variation]

  TH1D* meanRjg[8];
  TH1D* meanRjgSys[8];

  TFile * f = new TFile("../resultHistograms/resultHistograms_ppSmeared10030.root");
  meanJetPt[1]  =(TH1D*)f->Get(Form("meanJetPt_pp"));
  meanXjg[1]    =(TH1D*)f->Get(Form("meanXjg_pp"));
  meanRjg[1]  =(TH1D*)f->Get(Form("meanRjg_pp"));

  f   = new TFile("../resultHistograms/resultHistograms_ppSmeared13099.root");
  meanJetPt[2]  =(TH1D*)f->Get(Form("meanJetPt_pp"));
  meanXjg[2]    =(TH1D*)f->Get(Form("meanXjg_pp"));
  meanRjg[2]  =(TH1D*)f->Get(Form("meanRjg_pp"));

  // pbpb
  f =   new TFile("../resultHistograms/resultHistograms_nominal_vtxCentWeighted.root");

  meanJetPt[7]  =(TH1D*)f->Get(Form("meanJetPt_pp"));
  meanXjg[7]  =(TH1D*)f->Get(Form("meanXjg_pp"));
  meanRjg[7]  =(TH1D*)f->Get(Form("meanRjg_pp"));

  meanJetPt[3]  =(TH1D*)f->Get(Form("meanJetPt_pbpb_centralityBin1"));
  meanXjg[3]  =(TH1D*)f->Get(Form("meanXjg_pbpb_centralityBin1"));
  meanRjg[3]  =(TH1D*)f->Get(Form("meanRjg_pbpb_centralityBin1"));

  meanJetPt[4]  =(TH1D*)f->Get(Form("meanJetPt_pbpb_centralityBin2"));
  meanXjg[4]  =(TH1D*)f->Get(Form("meanXjg_pbpb_centralityBin2"));
  meanRjg[4]  =(TH1D*)f->Get(Form("meanRjg_pbpb_centralityBin2"));

  // pPb
  meanJetPt[5]  =(TH1D*)f->Get(Form("meanJetPt_ppb"));
  meanXjg[5]  =(TH1D*)f->Get(Form("meanXjg_ppb"));
  meanRjg[5]  =(TH1D*)f->Get(Form("meanRjg_ppb"));

  f =   new TFile("../resultHistograms/resultHistograms_MCrecoIso_vtxCentWeighted.root"); //pythia+hijing
  meanJetPt[6]  =(TH1D*)f->Get(Form("meanJetPt_ppb"));
  meanXjg[6]  =(TH1D*)f->Get(Form("meanXjg_ppb"));
  meanRjg[6]  =(TH1D*)f->Get(Form("meanRjg_ppb"));


  TFile* fSys = new TFile("../relativeSys_merged.root");

  meanJetPtSys[1]  =(TH1D*)fSys->Get("meanJetPt_pp_uncertainty_merged");
  meanRjgSys[1]  =(TH1D*)fSys->Get(Form("meanRjg_pp_uncertainty_merged"));
  meanXjgSys[1]  =(TH1D*)fSys->Get(Form("meanXjg_pp_uncertainty_merged"));

  meanJetPtSys[2] = (TH1D*)meanJetPtSys[1]->Clone(Form("%s_2",meanJetPtSys[1]->GetName()));
  meanRjgSys[2] = (TH1D*)meanRjgSys[1]->Clone(Form("%s_2",meanRjgSys[1]->GetName()));
  meanXjgSys[2] = (TH1D*)meanXjgSys[1]->Clone(Form("%s_2",meanXjgSys[1]->GetName()));

  meanJetPtSys[3]  =(TH1D*)fSys->Get("meanJetPt_pbpb_centralityBin1_uncertainty_merged");
  meanXjgSys[3]  =(TH1D*)fSys->Get(Form("meanXjg_pbpb_centralityBin1_uncertainty_merged"));
  meanRjgSys[3]  =(TH1D*)fSys->Get(Form("meanRjg_pbpb_centralityBin1_uncertainty_merged"));

  meanJetPtSys[4]  =(TH1D*)fSys->Get("meanJetPt_pbpb_centralityBin2_uncertainty_merged");
  meanXjgSys[4]  =(TH1D*)fSys->Get(Form("meanXjg_pbpb_centralityBin2_uncertainty_merged"));
  meanRjgSys[4]  =(TH1D*)fSys->Get(Form("meanRjg_pbpb_centralityBin2_uncertainty_merged"));

  meanJetPtSys[5]  =(TH1D*)fSys->Get("meanJetPt_ppb_uncertainty_merged");
  meanXjgSys[5]  =(TH1D*)fSys->Get(Form("meanXjg_ppb_uncertainty_merged"));
  meanRjgSys[5]  =(TH1D*)fSys->Get(Form("meanRjg_ppb_uncertainty_merged"));


  // RJG!!
  TCanvas* c2; 
  //c2->Divide(3,1);
  if( !drawSinglePanels)
  {
    c2 = new TCanvas("c1","",1300,500);
    makeMultiPanelCanvas(c2,3,1,0.0,0.0, 0.15, 0.15, 0.025);
  }
  else
  {
    c2 = new TCanvas("c1","",1450,500);
    c2->Divide(3,1);
    //makeMultiPanelCanvas(c2,3,1,0.2,0.2, 0.15, 0.15, 0.025);
  }
  c2->cd(3);
  handsomeTH1(meanRjg[1],1,1,21);
  //  drawSys(TH1 *h,TH1 *sys, Int_t theColor= newYellow, Int_t fillStyle = -1, Int_t lineStyle = -1)
  TH1D* tempR = new TH1D("tempR",";p_{T}^{#gamma} (GeV);R_{J#gamma}",100000,40,130);
  tempR->Reset();
  handsomeTH1(tempR,0);
  //tempR->SetAxisRange(0,1.2,"Y");
  tempR->SetAxisRange(0,1.0,"Y");
  tempR->SetAxisRange(40.01,109.99,"X");
  tempR->GetYaxis()->SetNdivisions(505);
  tempR->Draw();
  drawSys(meanRjg[1], meanRjgSys[1], kGreen,3001);
  drawSys(meanRjg[3], meanRjgSys[3]);
  handsomeTH1(meanRjg[1],1,1,21);
  meanRjg[1]->DrawCopy("same");
  handsomeTH1(meanRjg[3],2,1,20);
  meanRjg[3]->DrawCopy("same");
  meanRjg[1]->SetFillStyle(3001);
  meanRjg[1]->SetFillColor(kGreen);
  meanRjg[3]->SetFillColor(90);
  meanRjg[3]->SetFillStyle(1001);
  meanRjg[1]->SetLineColor(0);
  meanRjg[3]->SetLineColor(0);
  if ( 1==1 ){
    TLegend *ly = new  TLegend(0.4,0.2,0.75,0.4,NULL,"brNDC");
    //easyLeg(ly,"2.76TeV");
    easyLeg(ly);
    ly->AddEntry(meanRjg[3],"PbPb 0-30%","fp");
    ly->AddEntry(meanRjg[1],"Smeared pp reference","fp");
    ly->Draw();
  }
  if(!drawSinglePanels)
    drawCMSppPbPbDist(0.04,0.9);
  else
    drawCMSppPbPbDist(0.2,0.9);


  c2->cd(2);
  tempR->Draw();
  drawSys(meanRjg[2], meanRjgSys[2], kGreen,3001);
  drawSys(meanRjg[4], meanRjgSys[4]);
  //  meanRjg[2]->SetMarkerStyle(25);
  handsomeTH1(meanRjg[2],1,1,25);
  meanRjg[2]->DrawCopy("same");
  handsomeTH1(meanRjg[4],2,1,24);
  //  meanRjg[4]->SetMarkerStyle(24);
  meanRjg[4]->DrawCopy("same");
  meanRjg[2]->SetFillStyle(3001);
  meanRjg[2]->SetFillColor(kGreen);
  meanRjg[4]->SetFillColor(90);
  meanRjg[4]->SetFillStyle(1001);
  meanRjg[2]->SetLineColor(0);
  meanRjg[4]->SetLineColor(0);
  if ( 1==1 ){
    TLegend *ly = new  TLegend(0.4,0.2,0.75,0.4,NULL,"brNDC");
    easyLeg(ly);
    ly->AddEntry(meanRjg[4],"PbPb 30-100%","fp");
    ly->AddEntry(meanRjg[2],"Smeared pp reference","fp");
    ly->Draw();
  }
  if(!drawSinglePanels)
    drawCMSppPbPbDist(0.04,0.9);
  else
    drawCMSppPbPbDist(0.2,0.9);

  c2->cd(1);
  tempR->SetAxisRange(40,109.99,"X");
  tempR->DrawCopy();
  tempR->SetAxisRange(40.01,109.99,"X");
  drawSys(meanRjg[5], meanRjgSys[5], newYellow);
  drawSys(meanRjg[7], meanRjgSys[2], kGreen, 3001);
  handsomeTH1(meanRjg[5],9,1,34);
  handsomeTH1(meanRjg[6],1,1,25);
  handsomeTH1(meanRjg[7],1,1);
  meanRjg[5]->DrawCopy("same");
  meanRjg[6]->DrawCopy("same");
  meanRjg[7]->DrawCopy("same");
  meanRjg[7]->SetFillStyle(3001);
  meanRjg[7]->SetFillColor(kGreen);
  meanRjg[5]->SetFillColor(90);
  meanRjg[5]->SetFillStyle(1001);
  meanRjg[7]->SetLineColor(0);
  meanRjg[5]->SetLineColor(0);

  if ( 1==1 ) {
    TLegend *ly = new TLegend(0.5,0.25,0.85,0.47,NULL,"brNDC");
    easyLeg(ly);
    ly->AddEntry(meanRjg[5],"pPb DATA","fp");
    ly->AddEntry(meanRjg[6],"PYTHIA+HIJING","p");
    ly->AddEntry(meanRjg[7],"pp DATA (2.76TeV)","fp");
    ly->Draw();
  }
  drawCMSpPbDist(0.2,0.9);
  
  c2->SaveAs("pT_dependence_rjg_pp_pbpb.pdf");
  //c2->SaveAs("pT_dependence_rjg_pp_pbpb.png");

  // ppPbPb meanJetPt
  TCanvas* c3 = new TCanvas("c3","",1300,500);
  if(!drawSinglePanels)
    makeMultiPanelCanvas(c3,3,1,0.0,0.0, 0.15, 0.15, 0.025);
  else
    c3->Divide(3,1);
    //makeMultiPanelCanvas(c3,3,1,0.2,0.2, 0.15, 0.15, 0.025);
  c3->cd(1);
  handsomeTH1(meanRjg[1],1);
  //  drawSys(TH1 *h,TH1 *sys, Int_t theColor= newYellow, Int_t fillStyle = -1, Int_t lineStyle = -1)
  //  tempR->Draw();
  TH1D* tempJ = new TH1D("tempJ",";p_{T}^{#gamma}; <p_{T}^{Jet}>",10000,40,130);
  tempJ->Reset();
  handsomeTH1(tempJ,0);
  tempJ->SetAxisRange(40.01,109.99,"Y");
  tempJ->SetAxisRange(40.,109.99,"X");
  tempJ->DrawCopy();
  tempJ->SetAxisRange(40.01,109.99,"X");
  drawSys(meanJetPt[5], meanJetPtSys[5], newYellow);
  drawSys(meanJetPt[7], meanJetPtSys[1], kGreen,3001);
  handsomeTH1(meanJetPt[5],9,1,34);
  handsomeTH1(meanJetPt[6],1,1,25);
  handsomeTH1(meanJetPt[7],1,1);
  meanJetPt[5]->DrawCopy("same");
  meanJetPt[6]->DrawCopy("same");
  meanJetPt[7]->DrawCopy("same");
  if ( 1==1 ) {
    TLegend *ly = new TLegend(0.53,0.18,0.88,0.4,NULL,"brNDC");
    easyLeg(ly);
    ly->AddEntry(meanJetPt[5],"pPb DATA","p");
    ly->AddEntry(meanJetPt[6],"PYTHIA+HIJING","p");
    ly->AddEntry(meanJetPt[7],"pp DATA (2.76TeV)","p");
    ly->Draw();
  }
  drawCMSpPbDist(0.2,0.9);

  
  c3->cd(3);
  handsomeTH1(meanJetPt[1],1,1,21);
  //  drawSys(TH1 *h,TH1 *sys, Int_t theColor= newYellow, Int_t fillStyle = -1, Int_t lineStyle = -1)
  tempJ->Draw();
  drawSys(meanJetPt[3], meanJetPtSys[3]);
  drawSys(meanJetPt[1], meanJetPtSys[1], kGreen,3001);
  handsomeTH1(meanJetPt[3],2 );
  meanJetPt[1]->Draw("same");
  meanJetPt[3]->Draw("same");
  if ( 1==1 ){
    TLegend *ly = new  TLegend(0.58,0.18,0.93,0.4,NULL,"brNDC");
    easyLeg(ly);
    ly->AddEntry(meanJetPt[3],"PbPb 0-30%","p");
    ly->AddEntry(meanJetPt[1],"pp (smeared)","p");
    ly->Draw();
  }
  drawCMSppPbPbDist(0.1,0.9);

  c3->cd(2);
  tempJ->Draw();
  drawSys(meanJetPt[2], meanJetPtSys[2], kGreen,3001);
  drawSys(meanJetPt[4], meanJetPtSys[4]);
  //  meanJetPt[2]->SetMarkerStyle(25);
  meanJetPt[2]->Draw("same");
  handsomeTH1(meanJetPt[4],2 );
  //  meanJetPt[4]->SetMarkerStyle(24);
  meanJetPt[4]->Draw("same");
  if ( 1==1 ){
    TLegend *ly = new  TLegend(0.58,0.18,0.93,0.4,NULL,"brNDC");
    easyLeg(ly);
    ly->AddEntry(meanJetPt[4],"PbPb 30-100%","p");
    ly->AddEntry(meanJetPt[2],"pp (smeared)","p");
    ly->Draw();
  }
  drawCMSppPbPbDist(0.1,0.9);
  c3->SaveAs("pT_dependence_jetPt_pp_pbpb.pdf");
  //c3->SaveAs("pT_dependence_jetPt_pp_pbpb.png");


  // mean xjg
  TCanvas* c7; 
  if(!drawSinglePanels)
  {
    c7 = new TCanvas("c7","",1300,500);
    makeMultiPanelCanvas(c7,3,1,0.0,0.0, 0.15, 0.15, 0.025);
  }
  else
  {
    c7 = new TCanvas("c7","",1450,500);
    c7->Divide(3,1);
    //makeMultiPanelCanvas(c7,3,1,0.2,0.2, 0.15, 0.15, 0.025);
  }
  c7->cd(3);
  handsomeTH1(meanXjg[1],1,1,24);
  //  drawSys(TH1 *h,TH1 *sys, Int_t theColor= newYellow, Int_t fillStyle = -1, Int_t lineStyle = -1)
  TH1D* tempX = new TH1D("tempX",";p_{T}^{#gamma} (GeV);<X_{J#gamma}>;",10000,40,130);
  tempX->Reset();
  handsomeTH1(tempX,0);
  tempX->SetAxisRange(0.6,1.1,"Y");
  tempX->SetAxisRange(40.01,109.99,"X");
  tempX->GetYaxis()->SetNdivisions(606);
  tempX->Draw();
  drawSys(meanXjg[3], meanXjgSys[3]);
  drawSys(meanXjg[1], meanXjgSys[1], kGreen,3001);
  //  meanXjg[1]->SetMarkerStyle(21);
  handsomeTH1(meanXjg[1],1,1,21);
  meanXjg[1]->DrawCopy("same");
  handsomeTH1(meanXjg[3],2,1,20);
  meanXjg[3]->DrawCopy("same");
  meanXjg[1]->SetFillStyle(3001);
  meanXjg[1]->SetFillColor(kGreen);
  meanXjg[3]->SetFillColor(90);
  meanXjg[3]->SetFillStyle(1001);
  meanXjg[1]->SetLineColor(0);
  meanXjg[3]->SetLineColor(0);

  Float_t xpos = 0.022;
  if(drawSinglePanels)
    xpos = 0.15;
  if ( 1==1 ){
    TLegend *ly = new TLegend(xpos,0.1861745,0.578901,0.3788434,NULL,"brNDC");
    easyLeg(ly);
    ly->AddEntry(meanXjg[3],"PbPb 0-30%","fp");
    ly->AddEntry(meanXjg[1],"Smeared pp reference","fp");
    ly->Draw();
  }
  drawCMSppPbPbDist(0.6,0.9);


  c7->cd(2);
  tempX->Draw();
  drawSys(meanXjg[4], meanXjgSys[4]);
  drawSys(meanXjg[2], meanXjgSys[2], kGreen,3001);
  //  meanXjg[2]->SetMarkerStyle(25);
  handsomeTH1(meanXjg[2],1,1,25);
  meanXjg[2]->DrawCopy("same");
  handsomeTH1(meanXjg[4],2,1,24 );
  //  meanXjg[4]->SetMarkerStyle(24);
  meanXjg[4]->DrawCopy("same");
  meanXjg[2]->SetFillStyle(3001);
  meanXjg[2]->SetFillColor(kGreen);
  meanXjg[4]->SetFillColor(90);
  meanXjg[4]->SetFillStyle(1001);
  meanXjg[2]->SetLineColor(0);
  meanXjg[4]->SetLineColor(0);

  if ( 1==1 ){
    TLegend *ly = new TLegend(xpos,0.1861745,0.578901,0.3788434,NULL,"brNDC");
    easyLeg(ly);
    ly->AddEntry(meanXjg[4],"PbPb 30-100%","fp");
    ly->AddEntry(meanXjg[2],"Smeared pp reference","fp");
    ly->Draw();
  }
  drawCMSppPbPbDist(0.6,0.9);

  c7->cd(1);
  tempX->SetAxisRange(40.0,109.99,"X");
  tempX->DrawCopy();
  tempX->SetAxisRange(40.01,109.99,"X");
  drawSys(meanXjg[5], meanXjgSys[5], newYellow);
  drawSys(meanXjg[7], meanXjgSys[2], kGreen, 3001);
  handsomeTH1(meanXjg[5],9,1,34);
  handsomeTH1(meanXjg[6],1,1,25);
  handsomeTH1(meanXjg[7],1,1);
  meanXjg[5]->DrawCopy("same");
  meanXjg[6]->DrawCopy("same");
  meanXjg[7]->DrawCopy("same");
  meanXjg[7]->SetFillStyle(3001);
  meanXjg[7]->SetFillColor(kGreen);
  meanXjg[5]->SetFillColor(90);
  meanXjg[5]->SetFillStyle(1001);
  meanXjg[7]->SetLineColor(0);
  meanXjg[5]->SetLineColor(0);

  if ( 1==1 ) {
    TLegend *ly = new TLegend(0.1722123,0.1861,0.4788343,0.3788,NULL,"brNDC");
    easyLeg(ly);
    ly->AddEntry(meanXjg[5],"pPb DATA","fp");
    ly->AddEntry(meanXjg[6],"PYTHIA+HIJING","p");
    ly->AddEntry(meanXjg[7],"pp DATA (2.76TeV)","fp");    
    ly->Draw();
  }
  drawCMSpPbDist(0.65,0.90);
  
  c7->SaveAs("pT_dependence_meanXjg_pp_pbpb.pdf");
  c7->SaveAs("pT_dependence_meanXjg_pp_pbpb.png");

  // TCanvas* c10 = new TCanvas("c10","",1200,350);
  // makeMultiPanelCanvas(c10,nPtBin,1,0.0,0.0,0.2,0.15,0.02);
  // for ( int ipt = 1 ; ipt<=nPtBin  ; ipt++) {
  //   c10->cd(ipt);

  //   hTempPt->SetAxisRange(20,200,"X");
  //   hTempPt->SetAxisRange(0,2.5,"Y");
  //   hTempPt->SetYTitle("Yield^{JeT} Ratio");
  //   handsomeTH1(hTempPt,0);
  //   hTempPt->DrawCopy();
  //   IaaRatio[4][ipt] = (TH1D*)Iaa[4][ipt]->Clone(Form("%s_ratio",Iaa[4][ipt]->GetName()) );
  //   IaaRatio[4][ipt]->Divide(Iaa[2][ipt]);
  //   IaaRatioSys[4][ipt] = mergeSys( IaaSys[2][ipt], IaaSys[4][ipt]) ;

  //   drawSys(IaaRatio[4][ipt], IaaRatioSys[4][ipt], newYellow);
  //   jumSun(20,1,200,1);
  //   handsomeTH1(IaaRatio[4][ipt],2);
  //   IaaRatio[4][ipt]->SetMarkerStyle(24);
  //   IaaRatio[4][ipt]->Draw("same");
  //   double dx1=0.15;
  //   drawText(Form("p_{T}^{#gamma} > %dGeV ", (int)ptBin[ipt-1]), 0.12+dx1+0.25,0.85,1,15);//yeonju 130823
  //   drawText(Form("(PbPb)/(pp smeared)  30-100%%"), 0.12+dx1+0.05,0.69,1,15);//yeonju 130823
  // }

  // c10->SaveAs("pT_dependence_iAA_ratio2.pdf");



}
