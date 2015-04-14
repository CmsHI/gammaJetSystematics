#include "../commonUtilitySys.h"
#include <TFile.h>
#include <TGraphErrors.h>

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

void drawResults_IaaOnly(bool separatepPb = false) {

  const int nPtBin = 4;
  double ptBin[nPtBin+1] = {40, 50,60,80,9999};

  TH1D* dNdJetPt[8][5]; // [collision] [ ptbin]  [Before/After variation]
  TH1D* dNdJetPtSys[7][5]; // [collision] [ ptbin]  [Before/After variation]


  TH1D* ratioJet[7][5]; //  pbpb/pp of jet pt
  TH1D* ratioJet1[7][5]; //  pbpb/pp of jet pt
  TH1D* ratioJetSys[7][5]; //  pbpb/pp of jet pt

  TH1D* dNdJetPt40GeV[7]; 
  TH1D* dNdJetPtSys40GeV[7];
  TH1D* ratioJet40GeV[7]; 
  TH1D* ratioJet40GeV1[7];
  TH1D* ratioJetSys40GeV[7];




  /*  
      const int nRptBin[4] = {4,4,6,5};
      double ratioPtBin[4][7] = {{20,30,40,50,150},          // Hard Probe bin
      {20,30,40,50,150},
      {20,30,40,50,60,80,150},
      {20,30,50,80,100,150}};     
      double ratioPtBin1[4][7] = {{20,30,40,50,76},
      {20,30,40,50,78},
      {20,30,40,50,60,78, 108},
      {20,30,52,78, 108, 138}};
  const int nRptBin40GeV = 7;
  double ratioPtBin40GeV[8] = {20,30,40,50,60,80,100,150};
  double ratioPtBin40GeV1[8] = {20,30,40,50,60,78,108, 138};
      
  */
  const int nRptBin[4] = {5,5,6,6};
  double ratioPtBin[4][10] = {{20,30,40,50,70,150},
			     {20,30,40,50,70,150},
			     {20,30,40,50,70,100,150},
			     {20,30,40,50,70,100,150}};
  double ratioPtBin1[4][10] = {{20,30,40,50,68,105},
			      {20,30,40,50,68,105},
			      {20,30,40,50,68,100,130},
			      {20,30,40,50,68,100,130}};

  
  const int nRptBin40GeV = 6;
  double ratioPtBin40GeV[10]= 			     {20,30,40,50,70,100,150};
  double ratioPtBin40GeV1[10] = 			      {20,30,40,50,68,100,130};

  

  //  double ratioPtBin40GeV1 = 25, 35,45,55,65,79, 99, 135  : Weigted mean pt
  
  /*
  const int nRptBin40GeV = 13;
  double ratioPtBin40GeV[14] = {20,30,40,50,60,70,80,90,100,110,120,130,140,150};
  double ratioPtBin40GeV1[14] = {20,30,40,50,60,70,80,90,100,110,120,130,140,150};
  */

  /* mean of each bins are  = {{25,35,45, 63},
			      {25,35,45, 64},
			      {25,35,45,55,69,93},
			      {25,41,65, 93, 123}};  // two 93's are coincidence  
  */


  //double ratioPtBin[nRptBin+1] = {20,30,40,50,80,150};


  TH1D* dNdXjg[8][5]; // [collision] [ ptbin]  [Before/After variation]
  TH1D* dNdXjgSys[7][5]; // [collision] [ ptbin]  [Before/After variation]

  TH1D* dNdphi[8][5]; // [collision] [ ptbin]  [Before/After variation]
  TH1D* dNdphiSys[7][5]; // [collision] [ ptbin]  [Before/After variation]


  TFile * f = new TFile("../resultHistograms/resultHistograms_ppSmeared10030.root");
  for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
    dNdJetPt[1][ipt] = (TH1D*)f->Get(Form("dNdJetPt_pp_ptBin%d", ipt ));
    dNdXjg[1][ipt] = (TH1D*)f->Get(Form("dNdXjg_pp_ptBin%d", ipt ));
    dNdphi[1][ipt] = (TH1D*)f->Get(Form("dNdphi_pp_ptBin%d", ipt ));
  }

  f   = new TFile("../resultHistograms/resultHistograms_ppSmeared13099.root");
  for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
    dNdJetPt[2][ipt] = (TH1D*)f->Get(Form("dNdJetPt_pp_ptBin%d", ipt ));
    dNdXjg[2][ipt] = (TH1D*)f->Get(Form("dNdXjg_pp_ptBin%d", ipt ));
    dNdphi[2][ipt] = (TH1D*)f->Get(Form("dNdphi_pp_ptBin%d", ipt ));
  }

  // pbpb
  f =   new TFile("../resultHistograms/resultHistograms_nominal_vtxCentWeighted.root");
  for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
    dNdJetPt[3][ipt] = (TH1D*)f->Get(Form("dNdJetPt_pbpb_centralityBin1_ptBin%d", ipt ));
    dNdXjg[3][ipt] = (TH1D*)f->Get(Form("dNdXjg_pbpb_centralityBin1_ptBin%d", ipt ));
    dNdphi[3][ipt] = (TH1D*)f->Get(Form("dNdphi_pbpb_centralityBin1_ptBin%d", ipt ));
  }
  for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
    dNdJetPt[4][ipt] = (TH1D*)f->Get(Form("dNdJetPt_pbpb_centralityBin2_ptBin%d", ipt ));
    dNdXjg[4][ipt] = (TH1D*)f->Get(Form("dNdXjg_pbpb_centralityBin2_ptBin%d", ipt ));
    dNdphi[4][ipt] = (TH1D*)f->Get(Form("dNdphi_pbpb_centralityBin2_ptBin%d", ipt ));
  }



  // pPb
  f =   new TFile("../resultHistograms/resultHistograms_nominal_vtxCentWeighted.root");
  for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
    dNdJetPt[5][ipt] = (TH1D*)f->Get(Form("dNdJetPt_ppb_ptBin%d", ipt ));
    dNdXjg[5][ipt] = (TH1D*)f->Get(Form("dNdXjg_ppb_ptBin%d", ipt ));
    dNdphi[5][ipt] = (TH1D*)f->Get(Form("dNdphi_ppb_ptBin%d", ipt ));
    }

  //pp unsmeared
  f =   new TFile("../resultHistograms/resultHistograms_nominal_vtxCentWeighted.root");
  for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
    dNdJetPt[7][ipt] = (TH1D*)f->Get(Form("dNdJetPt_pp_ptBin%d", ipt ));
    dNdXjg[7][ipt] = (TH1D*)f->Get(Form("dNdXjg_pp_ptBin%d", ipt ));
    dNdphi[7][ipt] = (TH1D*)f->Get(Form("dNdphi_pp_ptBin%d", ipt ));
    }


  f =   new TFile("../resultHistograms/resultHistograms_MCrecoIso_vtxCentWeighted.root");
  for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
    dNdJetPt[6][ipt] = (TH1D*)f->Get(Form("dNdJetPt_ppb_ptBin%d", ipt ));
    dNdXjg[6][ipt] = (TH1D*)f->Get(Form("dNdXjg_ppb_ptBin%d", ipt ));
    dNdphi[6][ipt] = (TH1D*)f->Get(Form("dNdphi_ppb_ptBin%d", ipt ));
  }


  TFile* fSys = new TFile("../relativeSysDist/relativeSys_merged.root");

  for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
    dNdJetPtSys[1][ipt] = (TH1D*)fSys->Get(Form("dNdJetPt_pp_ptBin%d_uncertainty_merged",  ipt ));
    dNdXjgSys[1][ipt] = (TH1D*)fSys->Get(Form("dNdXjg_pp_ptBin%d_uncertainty_merged",  ipt ));
    dNdphiSys[1][ipt] = (TH1D*)fSys->Get(Form("dNdphi_pp_ptBin%d_uncertainty_merged",  ipt ));

  }
  for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
    dNdJetPtSys[2][ipt] = (TH1D*)dNdJetPtSys[1][ipt]->Clone(Form("%s_2",dNdJetPtSys[1][ipt]->GetName()));
    dNdXjgSys[2][ipt] = (TH1D*)dNdXjgSys[1][ipt]->Clone(Form("%s_2",dNdXjgSys[1][ipt]->GetName()));
    dNdphiSys[2][ipt] = (TH1D*)dNdphiSys[1][ipt]->Clone(Form("%s_2",dNdphiSys[1][ipt]->GetName()));

  }

  for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
    dNdJetPtSys[3][ipt] = (TH1D*)fSys->Get(Form("dNdJetPt_pbpb_centralityBin1_ptBin%d_uncertainty_merged",  ipt ));
    dNdXjgSys[3][ipt] = (TH1D*)fSys->Get(Form("dNdXjg_pbpb_centralityBin1_ptBin%d_uncertainty_merged",  ipt ));
    dNdphiSys[3][ipt] = (TH1D*)fSys->Get(Form("dNdphi_pbpb_centralityBin1_ptBin%d_uncertainty_merged",  ipt ));
  }
  for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
    dNdJetPtSys[4][ipt] = (TH1D*)fSys->Get(Form("dNdJetPt_pbpb_centralityBin2_ptBin%d_uncertainty_merged",  ipt ));
    dNdXjgSys     [4][ipt] = (TH1D*)fSys->Get(Form("dNdXjg_pbpb_centralityBin2_ptBin%d_uncertainty_merged",  ipt ));
    dNdphiSys     [4][ipt] = (TH1D*)fSys->Get(Form("dNdphi_pbpb_centralityBin2_ptBin%d_uncertainty_merged",  ipt ));
  }
  for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
    dNdJetPtSys[5][ipt] = (TH1D*)fSys->Get(Form("dNdJetPt_ppb_ptBin%d_uncertainty_merged",  ipt ));
    dNdXjgSys     [5][ipt] = (TH1D*)fSys->Get(Form("dNdXjg_ppb_ptBin%d_uncertainty_merged",  ipt ));
    dNdphiSys     [5][ipt] = (TH1D*)fSys->Get(Form("dNdphi_ppb_ptBin%d_uncertainty_merged",  ipt ));
  }

  // Sys for jet ratio
  TFile* fSysRatio = new TFile("../relativeSysDist/relativeSys_merged_for_jetPt_Ratio.root");
  for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {

    TH1D* h1temp =  (TH1D*)fSysRatio->Get(Form("dNdJetPt_ratio_centralityBin1_ptBin%d_uncertainty_merged",ipt));
    ratioJetSys[3][ipt] = new TH1D(Form("rebin_cent1_ptBin%d",ipt),"", nRptBin[ipt-1], ratioPtBin1[ipt-1]);
    for ( int i=1 ; i <= ratioJetSys[3][ipt]->GetNbinsX() ; i++){
      float xx = ratioJetSys[3][ipt]->GetBinCenter(i);
      float yVal = h1temp->GetBinContent(   h1temp->FindBin(xx) );
      if (yVal >1) yVal =1;
      ratioJetSys[3][ipt]->SetBinContent(i, yVal);

    }
    h1temp =  (TH1D*)fSysRatio->Get(Form("dNdJetPt_ratio_centralityBin2_ptBin%d_uncertainty_merged",ipt));
    ratioJetSys[4][ipt] = new TH1D(Form("rebin_cent2_ptBin%d",ipt),"", nRptBin[ipt-1], ratioPtBin1[ipt-1]);
    for ( int i=1 ; i <= ratioJetSys[4][ipt]->GetNbinsX() ; i++){
      float xx = ratioJetSys[4][ipt]->GetBinCenter(i);
      float yVal = h1temp->GetBinContent(   h1temp->FindBin(xx) );
      if (yVal >1) yVal =1;
      ratioJetSys[4][ipt]->SetBinContent(i, yVal);
    }


  }



  // jet pt ratio distributions
  TH1D* hTempPt = new TH1D("hTemp",";p_{T}^{#gamma} (GeV);",200,10,300);
  
  TCanvas* c5_ratio = new TCanvas("c5_ratio","",1200,400);
  makeMultiPanelCanvas(c5_ratio,nPtBin, 1, 0.0, 0.0, 0.25, 0.2, 0.02);
  for ( int ipt = 1 ; ipt<=nPtBin  ; ipt++) {
    c5_ratio->cd(ipt);
    hTempPt->SetXTitle("p_{T}^{Jet} (GeV)");
    hTempPt->SetYTitle("Jet I_{AA}");
    hTempPt->SetAxisRange(10,150,"X");
    //    hTempPt->SetAxisRange(0.001,2.9,"Y");
    hTempPt->SetAxisRange(0.001,3,"Y");
    handsomeTH1(hTempPt,0);
    hTempPt->GetYaxis()->SetTitleOffset(2.5);
    hTempPt->GetXaxis()->SetTitleOffset(2);
    hTempPt->DrawCopy();

    ratioJet[3][ipt] = (TH1D*)dNdJetPt[3][ipt]->Rebin(nRptBin[ipt-1], Form("%s_ratio",dNdJetPt[3][ipt]->GetName()), ratioPtBin[ipt-1]);
    ratioJet[1][ipt] = (TH1D*)dNdJetPt[1][ipt]->Rebin(nRptBin[ipt-1], Form("%s_ratio",dNdJetPt[1][ipt]->GetName()), ratioPtBin[ipt-1]);
    
    ratioJet[3][ipt]->Divide(ratioJet[1][ipt]);
    ratioJet1[3][ipt] = new TH1D(Form("%s_ratio1",dNdJetPt[3][ipt]->GetName()),"",nRptBin[ipt-1],ratioPtBin1[ipt-1]);
    for ( int ibin =1 ; ibin<=nRptBin[ipt-1] ; ibin++)  {
      ratioJet1[3][ipt]->SetBinContent(ibin, ratioJet[3][ipt]->GetBinContent(ibin));
      ratioJet1[3][ipt]->SetBinError(ibin, ratioJet[3][ipt]->GetBinError(ibin));
    }

    handsomeTH1(ratioJet1[3][ipt],2);
    //    drawSys(ratioJet1[3][ipt], ratioJetSys[3][ipt] );
    ratioJet1[3][ipt]->DrawCopy("same");
    jumSun(10,1,150,1);
    if ( ipt == 1 ) {
      TLegend *ly = new TLegend(0.333658,0.7018245,0.5500974,0.9867236,NULL,"brNDC");
      easyLeg(ly);
      ratioJet1[3][ipt]->SetFillStyle(1001);
      ratioJet1[3][ipt]->SetFillColor(90);
      ratioJet1[3][ipt]->SetLineColor(0);
      ly->AddEntry(ratioJet1[3][ipt],"PbPb 0-30%","fp");
      ly->Draw();
    }
    if(ipt == 4)
      drawCMSppPbPbDist(0.4,0.85);
    gPad->RedrawAxis();

  }
  //  c5_ratio->SaveAs("pT_dependence_jetPt_pp_pbpb_Ratio.gif");


  
  TCanvas* c5_iaa40 = new TCanvas("c5_iaa40","",500,800);
  makeMultiPanelCanvas(c5_iaa40,1, 2, 0.0, 0.0, 0.15, 0.2, 0.02);
  c5_iaa40->cd(1);
  hTempPt->SetXTitle("p_{T}^{Jet} (GeV)");
  hTempPt->SetYTitle("Jet I_{AA}");
  hTempPt->SetAxisRange(10,150,"X");
  hTempPt->SetAxisRange(0.001,2.9,"Y");
  handsomeTH1(hTempPt,0);
  hTempPt->GetYaxis()->SetTitleOffset(2.5);
  hTempPt->GetXaxis()->SetTitleOffset(2);
  hTempPt->DrawCopy();
  
  // Integration :
  dNdJetPt40GeV[1] = (TH1D*)dNdJetPt[1][1]->Clone("dNdJetPt_pp_centBin1_40GeVCut");
  dNdJetPt40GeV[1]->Reset();
  dNdJetPt40GeV[1]->Add(dNdJetPt[1][1], 3895);
  dNdJetPt40GeV[1]->Add(dNdJetPt[1][2], 1633);
  dNdJetPt40GeV[1]->Add(dNdJetPt[1][3], 1006);
  dNdJetPt40GeV[1]->Add(dNdJetPt[1][4], 429);
  dNdJetPt40GeV[1]->Scale( 1./ ( 3895+1633+1006+429));

  dNdJetPt40GeV[2] = (TH1D*)dNdJetPt[2][1]->Clone("dNdJetPt_pp_centBin2_40GeVCut");
  dNdJetPt40GeV[2]->Reset();
  dNdJetPt40GeV[2]->Add(dNdJetPt[2][1], 3895);
  dNdJetPt40GeV[2]->Add(dNdJetPt[2][2], 1633);
  dNdJetPt40GeV[2]->Add(dNdJetPt[2][3], 1006);
  dNdJetPt40GeV[2]->Add(dNdJetPt[2][4], 429);
  dNdJetPt40GeV[2]->Scale( 1./ ( 3895+1633+1006+429));


  dNdJetPt40GeV[3] = (TH1D*)dNdJetPt[3][1]->Clone("dNdJetPt_pbpb_centBin1_40GeVCut");
  dNdJetPt40GeV[3]->Reset();
  dNdJetPt40GeV[3]->Add(dNdJetPt[3][1], 4319);
  dNdJetPt40GeV[3]->Add(dNdJetPt[3][2], 1799);
  dNdJetPt40GeV[3]->Add(dNdJetPt[3][3], 1154);
  dNdJetPt40GeV[3]->Add(dNdJetPt[3][4], 547);
  dNdJetPt40GeV[3]->Scale( 1./ ( 4319+1799+1154+547));

  dNdJetPt40GeV[4] = (TH1D*)dNdJetPt[4][1]->Clone("dNdJetPt_pbpb_centBin2_40GeVCut");
  dNdJetPt40GeV[4]->Reset();
  dNdJetPt40GeV[4]->Add(dNdJetPt[4][1], 1208);
  dNdJetPt40GeV[4]->Add(dNdJetPt[4][2], 493);
  dNdJetPt40GeV[4]->Add(dNdJetPt[4][3], 297);
  dNdJetPt40GeV[4]->Add(dNdJetPt[4][4], 114);
  dNdJetPt40GeV[4]->Scale( 1./ ( 1208+493+297+114));
  
  
  TFile* fSys40 = new TFile("../relativeSysDist/relativeSys_merged_for_jetPt_Ratio_40GeVCut.root");
  ratioJetSys40GeV[3] = (TH1D*)fSys40->Get("dNdJetPt_ratio_centralityBin1_ptBin1_uncertainty_merged");
  ratioJetSys40GeV[4] = (TH1D*)fSys40->Get("dNdJetPt_ratio_centralityBin2_ptBin1_uncertainty_merged");

  //here
  ratioJet40GeV[1]= (TH1D*)dNdJetPt40GeV[1]->Rebin(nRptBin40GeV, Form("%s_ratio",dNdJetPt40GeV[1]->GetName()), ratioPtBin40GeV);
  ratioJet40GeV[2]= (TH1D*)dNdJetPt40GeV[2]->Rebin(nRptBin40GeV, Form("%s_ratio",dNdJetPt40GeV[2]->GetName()), ratioPtBin40GeV);
  ratioJet40GeV[3]= (TH1D*)dNdJetPt40GeV[3]->Rebin(nRptBin40GeV, Form("%s_ratio",dNdJetPt40GeV[3]->GetName()), ratioPtBin40GeV);
  ratioJet40GeV[4]= (TH1D*)dNdJetPt40GeV[4]->Rebin(nRptBin40GeV, Form("%s_ratio",dNdJetPt40GeV[4]->GetName()), ratioPtBin40GeV);

  ratioJet40GeV[3]->Divide(ratioJet40GeV[1]);
  ratioJet40GeV[4]->Divide(ratioJet40GeV[2]);
  
  ratioJet40GeV1[3] = new TH1D(Form("%s_ratio1",ratioJet40GeV[3]->GetName()),"",nRptBin40GeV,ratioPtBin40GeV1);
  ratioJet40GeV1[4] = new TH1D(Form("%s_ratio1",ratioJet40GeV[4]->GetName()),"",nRptBin40GeV,ratioPtBin40GeV1);


  for ( int ibin =1 ; ibin<=nRptBin40GeV ; ibin++)  {
      ratioJet40GeV1[3]->SetBinContent(ibin, ratioJet40GeV[3]->GetBinContent(ibin));
      ratioJet40GeV1[3]->SetBinError(ibin, ratioJet40GeV[3]->GetBinError(ibin));
      ratioJet40GeV1[4]->SetBinContent(ibin, ratioJet40GeV[4]->GetBinContent(ibin));
      ratioJet40GeV1[4]->SetBinError(ibin, ratioJet40GeV[4]->GetBinError(ibin));
    }

    handsomeTH1(ratioJet40GeV1[3],2);
    handsomeTH1(ratioJet40GeV1[4],2);
    ratioJet40GeV1[4]->SetMarkerStyle(24);
    drawSys(ratioJet40GeV1[4], ratioJetSys40GeV[4] );
    ratioJet40GeV1[4]->Draw("same");
    jumSun(10,1,150,1);
    if ( 1==1) {
      TLegend *ly = new TLegend(0.2533658,0.7018245,0.5500974,0.9867236,NULL,"brNDC");
      easyLeg(ly);
      ly->AddEntry(ratioJet40GeV1[3],"30-100%","p");
      ly->Draw();
    }    
    double dx1=0.15;
    drawText("p_{T}^{#gamma} > 40 GeV ", 0.10+dx1+0.1,0.9,1,18);
    
    gPad->RedrawAxis();
    
    c5_iaa40->cd(2);
    hTempPt->DrawCopy();
    
    drawSys(ratioJet40GeV1[3], ratioJetSys40GeV[3] );
    ratioJet40GeV1[3]->Draw("same");
    jumSun(10,1,150,1);
    jumSun(10,1,150,1);
    if ( 1==1) {
      TLegend *ly = new TLegend(0.2533658,0.7018245,0.5500974,0.9867236,NULL,"brNDC");
      easyLeg(ly);
      ly->AddEntry(ratioJet40GeV1[3],"0-30%","p");
      ly->Draw();
    }
    gPad->RedrawAxis();
    
    
    //    c5_iaa40->SaveAs("pT_dependence_jetPt_pp_pbpb_Ratio_40GeV.pdf");


  // jet pt distributions
  // rebin last category
  Double_t jetptbins[7] = {30, 40, 60, 80, 100, 120, 140};
  /*  for(int i = 1; i <=4; i++)
  {
    dNdJetPt[i][nPtBin] = (TH1D*)dNdJetPt[i][nPtBin]->Rebin(6,dNdJetPt[i][nPtBin]->GetName(),jetptbins);
    dNdJetPt[i][nPtBin]->Scale(1./2.);
    dNdJetPt[i][nPtBin]->SetBinContent(1,dNdJetPt[i][nPtBin]->GetBinContent(1)*2);
    dNdJetPt[i][nPtBin]->SetBinError(1,dNdJetPt[i][nPtBin]->GetBinError(1)*TMath::Sqrt(2));
  }
  */

  Int_t rows = 3;
  if(separatepPb)
    rows = 2;



    /* 
       dNdJetPt40GeV[1]->Scale( 1./ ( 3895+1633+1006+429)); // pp
       dNdJetPt40GeV[3]->Scale( 1./ ( 4319+1799+1154+547)); // pbpb  0-30%
       dNdJetPt40GeV[4]->Scale( 1./ ( 1208+493+297+114));   // pbpb 30-100%
    */

  dNdJetPt[1][1]->Scale(3895);
  dNdJetPt[1][2]->Scale(1633);
  dNdJetPt[1][3]->Scale(1006);
  dNdJetPt[1][4]->Scale(429);
  dNdJetPt[2][1]->Scale(3895);
  dNdJetPt[2][2]->Scale(1633);
  dNdJetPt[2][3]->Scale(1006);
  dNdJetPt[2][4]->Scale(429);
  dNdJetPt[3][1]->Scale(4319);
  dNdJetPt[3][2]->Scale(1799);
  dNdJetPt[3][3]->Scale(1154);
  dNdJetPt[3][4]->Scale(547);
  dNdJetPt[4][1]->Scale(1208);
  dNdJetPt[4][2]->Scale(493);
  dNdJetPt[4][3]->Scale(297);
  dNdJetPt[4][4]->Scale(114);

  TCanvas* c5 = new TCanvas("c5","",1200,400);
  makeMultiPanelCanvas(c5,nPtBin, 1, 0.0, 0.0, 0.3, 0.2, 0.02);

  for ( int ipt = 1 ; ipt<=nPtBin  ; ipt++) {
    c5->cd(ipt);
    
    hTempPt->SetXTitle("p_{T}^{Jet} (GeV)");
    hTempPt->SetYTitle("#frac{1}{N_{#gamma}} #frac{dN_{J#gamma}}{dp_{T}^{Jet}} (GeV^{-1})");
    hTempPt->SetAxisRange(10,150,"X");
    hTempPt->SetAxisRange(0.001,100,"Y");
        gPad->SetLogy();

    hTempPt->GetYaxis()->SetNdivisions(504);
    handsomeTH1(hTempPt,0);
    if(!separatepPb)
    {
      hTempPt->GetYaxis()->SetTitleOffset(5);
      hTempPt->GetXaxis()->SetTitleOffset(3);
    } else {
      hTempPt->GetYaxis()->SetTitleOffset(4);
      hTempPt->GetXaxis()->SetTitleOffset(2);
    }
    hTempPt->DrawCopy();

    //    drawSys(dNdJetPt[3][ipt], dNdJetPtSys[3][ipt], newYellow,-1,10);
    //    drawSys(dNdJetPt[1][ipt], dNdJetPtSys[1][ipt], kGreen,3001,10);
    handsomeTH1(dNdJetPt[3][ipt],2);
    dNdJetPt[1][ipt]->SetMarkerStyle(21);
    dNdJetPt[1][ipt]->DrawCopy("same");
    dNdJetPt[3][ipt]->DrawCopy("same");
    if ( ipt == 1 ) {
      TLegend *ly = new TLegend(0.35,0.75,0.9,0.95,NULL,"brNDC");
      easyLeg(ly);
      dNdJetPt[3][ipt]->SetFillStyle(1001);
      dNdJetPt[3][ipt]->SetFillColor(90);
      dNdJetPt[3][ipt]->SetLineColor(0);
      dNdJetPt[1][ipt]->SetFillStyle(3001);
      dNdJetPt[1][ipt]->SetFillColor(kGreen);
      dNdJetPt[1][ipt]->SetLineColor(0);

      ly->AddEntry(dNdJetPt[3][ipt],"PbPb 0-30%","fp");
      //      ly->AddEntry(dNdJetPt[1][ipt],"Smeared pp reference","fp");
      ly->Draw();
    }

    if(ipt == 4)
      drawCMSppPbPbDist(0.1,0.9);
  }

  TCanvas* c6 = new TCanvas("c6","",800,400);
  c6->Divide(2,1);
  
  for ( int ii=1; ii<=4; ii++) {
    dNdJetPt[ii][2]->Add(dNdJetPt[ii][1],1);
    dNdJetPt[ii][3]->Add(dNdJetPt[ii][2],1);
    dNdJetPt[ii][4]->Add(dNdJetPt[ii][3],1);
 
    dNdJetPt[ii][1]->SetFillColor(16);
    dNdJetPt[ii][2]->SetFillColor(5);
    dNdJetPt[ii][3]->SetFillColor(8);
    dNdJetPt[ii][4]->SetFillColor(4);
    handsomeTH1(dNdJetPt[ii][1],16);
    handsomeTH1(dNdJetPt[ii][2],5);
    handsomeTH1(dNdJetPt[ii][3],8);
    handsomeTH1(dNdJetPt[ii][4],4);
    for ( int jj=1; jj<=4; jj++) {
      dNdJetPt[ii][jj]->SetFillStyle(1001);
    }
  }
  c6->cd(1);
  dNdJetPt[3][4]->SetAxisRange(0.001,80,"Y");
  dNdJetPt[3][4]->SetAxisRange(0.001,149,"X");
  dNdJetPt[3][4]->DrawCopy("hist");
  dNdJetPt[3][3]->DrawCopy("hist same");
  dNdJetPt[3][2]->DrawCopy("hist same");
  dNdJetPt[3][1]->DrawCopy("hist same");
  dNdJetPt[3][4]->DrawCopy("same e");

  gPad->SetLogy();
  c6->cd(2);
  dNdJetPt[3][1]->Divide(dNdJetPt[3][4]);
  dNdJetPt[3][2]->Divide(dNdJetPt[3][4]);
  dNdJetPt[3][3]->Divide(dNdJetPt[3][4]);
  dNdJetPt[3][4]->Divide(dNdJetPt[3][4]); 
  dNdJetPt[3][4]->SetAxisRange(0.0,1.1,"Y");
  dNdJetPt[3][4]->DrawCopy("hist");
  dNdJetPt[3][3]->DrawCopy("hist same");
  dNdJetPt[3][2]->DrawCopy("hist same");
  dNdJetPt[3][1]->DrawCopy("hist same");
  
  
  
  
}
