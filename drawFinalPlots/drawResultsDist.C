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

void drawResultsDist() {
  // const int kPPcentral = 1;
  // const int kPPperipheral =2 ;
  // const int kHIcentral =  3;
  // const int kHIperipheral = 4;
  // const int kPADATA = 5;
  // const int kPAMC = 6;
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




  const int nRptBin[4] = {4,4,6,5};
  double ratioPtBin[4][7] = {{20,30,40,50,150},         
			     {20,30,40,50,150},
			     {20,30,40,50,60,80,150},
			     {20,30,50,80,100,150}};

  const int nRptBin40GeV = 7;
  double ratioPtBin40GeV[8] = {20,30,40,50,60,80,100,150};
  double ratioPtBin40GeV1[8] = {20,30,40,50,60,78,108, 138};
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
  double ratioPtBin1[4][7] = {{20,30,40,50,76},
			      {20,30,40,50,78},
			      {20,30,40,50,60,78, 108},
			      {20,30,52,78, 108, 138}};
			     


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
  
  TCanvas* c5_ratio = new TCanvas("c5_ratio","",1200,600);
  makeMultiPanelCanvas(c5_ratio,nPtBin, 2, 0.0, 0.0, 0.25, 0.2, 0.02);
  for ( int ipt = 1 ; ipt<=nPtBin  ; ipt++) {
    c5_ratio->cd(ipt+nPtBin);
    hTempPt->SetXTitle("p_{T}^{Jet} (GeV)");
    hTempPt->SetYTitle("Jet I_{AA}");
    //    hTempPt->SetYTitle("PbPb/pp of jet yield");
    hTempPt->SetAxisRange(10,150,"X");
    hTempPt->SetAxisRange(0.001,2.9,"Y");
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
    drawSys(ratioJet1[3][ipt], ratioJetSys[3][ipt] );
    ratioJet1[3][ipt]->Draw("same");
    jumSun(10,1,150,1);
    if ( ipt == 1 ) {
      TLegend *ly = new TLegend(0.2533658,0.7018245,0.5500974,0.9867236,NULL,"brNDC");
      easyLeg(ly);
      ly->AddEntry(ratioJet1[3][ipt],"PbPb 0-30%","p");
      ly->Draw();
    }
    gPad->RedrawAxis();

    c5_ratio->cd(ipt);
    hTempPt->DrawCopy();

    ratioJet[4][ipt] = (TH1D*)dNdJetPt[4][ipt]->Rebin(nRptBin[ipt-1], Form("%s_ratio",dNdJetPt[4][ipt]->GetName()), ratioPtBin[ipt-1]);
    ratioJet[2][ipt] = (TH1D*)dNdJetPt[2][ipt]->Rebin(nRptBin[ipt-1], Form("%s_ratio",dNdJetPt[2][ipt]->GetName()), ratioPtBin[ipt-1]);
    ratioJet[4][ipt]->Divide(ratioJet[2][ipt]);

    ratioJet1[4][ipt] = new TH1D(Form("%s_ratio1",dNdJetPt[4][ipt]->GetName()),"",nRptBin[ipt-1],ratioPtBin1[ipt-1]);
    for ( int ibin =1 ; ibin<=nRptBin[ipt-1] ; ibin++)  {
      ratioJet1[4][ipt]->SetBinContent(ibin, ratioJet[4][ipt]->GetBinContent(ibin));
      ratioJet1[4][ipt]->SetBinError(ibin, ratioJet[4][ipt]->GetBinError(ibin));
    }


    handsomeTH1(ratioJet1[4][ipt],2);
    ratioJet1[4][ipt]->SetMarkerStyle(24);
    drawSys(ratioJet1[4][ipt], ratioJetSys[4][ipt] );
    ratioJet1[4][ipt]->Draw("same");
    jumSun(10,1,150,1);

    if ( ipt==1 ){
      TLegend *ly = new TLegend(0.2533658,0.7018245,0.5500974,0.9867236,NULL,"brNDC");
      easyLeg(ly);
      ly->AddEntry(ratioJet1[4][ipt],"PbPb 30-100%","p");
      ly->Draw();
    }

    double dx1=0.15;
    if ( ipt == nPtBin )
      drawText(Form("p_{T}^{#gamma} > %dGeV ", (int)ptBin[ipt-1]), 0.10+dx1+0.1,0.9,1,18);
    else if ( ipt == 1)
      drawText(Form("%dGeV < p_{T}^{#gamma} < %dGeV ", (int)ptBin[ipt-1], (int)ptBin[ipt]), 0.25+dx1,0.9,1,18);
    else
      drawText(Form("%dGeV < p_{T}^{#gamma} < %dGeV ", (int)ptBin[ipt-1], (int)ptBin[ipt]), 0.10+dx1,0.9,1,18);

  }
  c5_ratio->SaveAs("pT_dependence_jetPt_pp_pbpb_Ratio.pdf");
  c5_ratio->SaveAs("pT_dependence_jetPt_pp_pbpb_Ratio.png");


  
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

  dNdJetPt40GeV[4] = (TH1D*)dNdJetPt[4][1]->Clone("dNdJetPt_pbpb_centBin1_40GeVCut");
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
    drawText("p_{T}^{#gamma} > 40GeV ", 0.10+dx1+0.1,0.9,1,18);
    
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


    c5_iaa40->SaveAs("pT_dependence_jetPt_pp_pbpb_Ratio_40GeV.pdf");
    c5_iaa40->SaveAs("pT_dependence_jetPt_pp_pbpb_Ratio_40GeV.png");


  // jet pt distributions
  // rebin last category
  Double_t jetptbins[7] = {30, 40, 60, 80, 100, 120, 140};
  for(int i = 1; i <=4; i++)
  {
    // Int_t nbins = dNdJetPt[i][nPtBin]->GetNbinsX();
    // Double_t x[nbins];
    // Double_t xbins[nbins +1];
    // Double_t err[nbins];
    // Double_t val[nbins];
    // Int_t realnbins = 0;
    // for(int j = 1; j < nbins; j+=2)
    // {
    //   Float_t xx1 = dNdJetPt[i][nPtBin]->GetBinCenter(j);
    //   if(xx1 > 150) break;
    //   Float_t xx2 = dNdJetPt[i][nPtBin]->GetBinCenter(j+1);
    //   Float_t val1 = dNdJetPt[i][nPtBin]->GetBinContent(j);
    //   Float_t val2 = dNdJetPt[i][nPtBin]->GetBinContent(j+1);
    //   x[j/2] = ((val1*xx1)+(val2*xx2))/(val1+val2);
    //   val[j/2] = (val1+val2)/2;
    //   Float_t err1 = dNdJetPt[i][nPtBin]->GetBinError(j);
    //   Float_t err2 = dNdJetPt[i][nPtBin]->GetBinError(j+1);
    //   err[j/2] = err1*TMath::Sqrt(val1/(val1+val2));
    //   realnbins++;
    // }
    // xbins[0] = 0;
    // for(int j = 0; j < realnbins-1; j++)
    // {
    //   xbins[j+1] = (x[j]+x[j+1])/2;
    // }
    // TH1D *hTemp = (TH1D*)dNdJetPt[i][nPtBin]->Rebin(realnbins, "hTemp", xbins);
    // for(int j = 1; j <= realnbins; j++)
    // {
    //   hTemp->SetBinContent(j,val[j]);
    //   hTemp->SetBinError(j, err[j]);
    // }
    // dNdJetPt[i][nPtBin] = (TH1D*)hTemp->Clone(dNdJetPt[i][nPtBin]->GetName());
    dNdJetPt[i][nPtBin] = (TH1D*)dNdJetPt[i][nPtBin]->Rebin(6,dNdJetPt[i][nPtBin]->GetName(),jetptbins);
    dNdJetPt[i][nPtBin]->Scale(1./2.);
    dNdJetPt[i][nPtBin]->SetBinContent(1,dNdJetPt[i][nPtBin]->GetBinContent(1)*2);
    dNdJetPt[i][nPtBin]->SetBinError(1,dNdJetPt[i][nPtBin]->GetBinError(1)*TMath::Sqrt(2));
  }
  
  TCanvas* c5 = new TCanvas("c5","",1200,900);
  makeMultiPanelCanvas(c5,nPtBin, 3, 0.0, 0.0, 0.25, 0.2, 0.02);

  for ( int ipt = 1 ; ipt<=nPtBin  ; ipt++) {
    c5->cd(ipt+nPtBin*2);

    hTempPt->SetXTitle("p_{T}^{Jet} (GeV)");
    hTempPt->SetYTitle("#frac{1}{N_{#gamma}} #frac{dN_{J#gamma}}{dp_{T}^{jet}}");
    hTempPt->SetAxisRange(10,150,"X");
    hTempPt->SetAxisRange(0,0.025,"Y");
    hTempPt->GetYaxis()->SetNdivisions(504);
    handsomeTH1(hTempPt,0);
    hTempPt->GetYaxis()->SetTitleOffset(4);
    hTempPt->GetXaxis()->SetTitleOffset(3);
    hTempPt->DrawCopy();

    drawSys(dNdJetPt[1][ipt], dNdJetPtSys[1][ipt], kGreen,3001,10);
    drawSys(dNdJetPt[3][ipt], dNdJetPtSys[3][ipt], newYellow,-1,10);
    handsomeTH1(dNdJetPt[3][ipt],2);
    dNdJetPt[1][ipt]->Draw("same");
    //    dNdJetPt[1][ipt]->SetMarkerStyle(21);
    dNdJetPt[3][ipt]->Draw("same");
    if ( ipt == 1 ) {
      TLegend *ly = new TLegend(0.4484643,0.6988445,0.9140673,0.9102941,NULL,"brNDC");
      easyLeg(ly);
      ly->AddEntry(dNdJetPt[3][ipt],"PbPb 0-30%","p");
      ly->AddEntry(dNdJetPt[1][ipt],"pp (smeared)","p");
      ly->Draw();
    }

    if(ipt == 4)
      drawCMSppPbPbDist(0.1,0.9);

    c5->cd(ipt+nPtBin);
    hTempPt->DrawCopy();
    //gPad->SetLogy();

    drawSys(dNdJetPt[2][ipt], dNdJetPtSys[2][ipt], kGreen,3001,10);
    drawSys(dNdJetPt[4][ipt], dNdJetPtSys[4][ipt], newYellow,-1,10);
    handsomeTH1(dNdJetPt[4][ipt],2);
    //    dNdJetPt[4][ipt]->SetMarkerStyle(24);
    //   dNdJetPt[2][ipt]->SetMarkerStyle(25);
    dNdJetPt[2][ipt]->Draw("same");
    dNdJetPt[4][ipt]->Draw("same");

    if ( ipt==1 ){
      TLegend *ly = new TLegend(0.4484643,0.6088445,0.9140673,0.85102941,NULL,"brNDC");
      easyLeg(ly);
      ly->AddEntry(dNdJetPt[4][ipt],"PbPb 30-100%","p");
      ly->AddEntry(dNdJetPt[2][ipt],"pp (smeared)","p");
      ly->Draw();
    }

    if(ipt == 4)
      drawCMSppPbPbDist(0.1,0.9);

    c5->cd(ipt);
    hTempPt->DrawCopy();

    drawSys(dNdJetPt[5][ipt], dNdJetPtSys[5][ipt], newYellow);
    drawSys(dNdJetPt[7][ipt], dNdJetPtSys[2][ipt], kGreen,3001);
    handsomeTH1(dNdJetPt[5][ipt],9,1,34);
    handsomeTH1(dNdJetPt[7][ipt],1,1);
    dNdJetPt[6][ipt]->SetMarkerStyle(25);

    dNdJetPt[6][ipt]->Draw("same");
    dNdJetPt[5][ipt]->Draw("same");
    dNdJetPt[7][ipt]->Draw("same");
    if ( ipt == 1 ) {
      TLegend *ly = new TLegend(0.4313699,0.5060255,0.8982322,0.8677549,NULL,"brNDC");
      easyLeg(ly);
      ly->AddEntry(dNdJetPt[5][ipt],"pPb Data","p");
      ly->AddEntry(dNdJetPt[6][ipt],"PYTHIA+HIJING","p");
      ly->AddEntry(dNdJetPt[7][ipt],"pp Data (2.76TeV)","p");
      ly->Draw();
    }
    if(ipt == 4)
      drawCMSpPbDist(0.1,0.7);

    double dx1=0.18;
    if ( ipt == nPtBin )
      drawText(Form("p_{T}^{#gamma} > %dGeV ", (int)ptBin[ipt-1]), 0.10+dx1+0.1,0.9,1,18);
    else if ( ipt == 1)
      drawText(Form("%dGeV < p_{T}^{#gamma} < %dGeV ", (int)ptBin[ipt-1], (int)ptBin[ipt]), 0.25+dx1,0.9,1,18);
    else
      drawText(Form("%dGeV < p_{T}^{#gamma} < %dGeV ", (int)ptBin[ipt-1], (int)ptBin[ipt]), 0.10+dx1,0.9,1,18);

  }
  c5->SaveAs("pT_dependence_jetPt_pp_pbpb_distribution.pdf");
  c5->SaveAs("pT_dependence_jetPt_pp_pbpb_distribution.png");

  

  // XJG plots
  TH1D* hTempXjg = new TH1D("hTempXjg",";p_{T}^{#gamma} (GeV);",200,0,2);
  TCanvas* c6 = new TCanvas("c6","",1200,900);
  makeMultiPanelCanvas(c6,nPtBin,3,0.0,0.0,0.25,0.20,0.02);
  for ( int ipt = 1 ; ipt<=nPtBin  ; ipt++) {
    c6->cd(ipt+2*nPtBin);
    // draw pp
    hTempXjg->SetXTitle("x_{J#gamma}");
    hTempXjg->SetYTitle("#frac{1}{N_{#gamma}} #frac{dN_{J#gamma}}{dx}");
    hTempXjg->SetAxisRange(0,2,"Y");
    if(ipt == 1)
      hTempXjg->SetAxisRange(0,2,"X");
    else
      hTempXjg->SetAxisRange(0.05,2,"X");
    hTempXjg->GetYaxis()->SetNdivisions(405);
    hTempXjg->GetXaxis()->SetNdivisions(405);
    handsomeTH1(hTempXjg,0);
    hTempXjg->GetYaxis()->SetTitleOffset(3);
    hTempXjg->GetXaxis()->SetTitleOffset(3);
    hTempXjg->DrawCopy();

    
    //    dNdXjg[1][ipt]->Scale(meanRjg[1]->GetBinContent(ipt));
    //  dNdXjg[3][ipt]->Scale(meanRjg[3]->GetBinContent(ipt));
    drawSys(dNdXjg[3][ipt], dNdXjgSys[3][ipt], newYellow);
    drawSys(dNdXjg[1][ipt], dNdXjgSys[1][ipt], kGreen,3001);
    handsomeTH1(dNdXjg[3][ipt],2);
    dNdXjg[1][ipt]->Draw("same");
    //    dNdXjg[1][ipt]->SetMarkerStyle(21);
    dNdXjg[3][ipt]->Draw("same");
    if ( ipt == 1 ) {
      TLegend *ly = new TLegend(0.351273,0.6152521,0.9997611,0.9087395,NULL,"brNDC");
      easyLeg(ly);
      ly->AddEntry(dNdXjg[3][ipt],"PbPb 0-30%","p");
      ly->AddEntry(dNdXjg[1][ipt],"pp (smeared)","p");
      ly->Draw();
    }

    if(ipt + nPtBin == 8)
      drawCMSppPbPbDist(0.4,0.9);

    gPad->RedrawAxis();

    c6->cd(ipt+nPtBin);
    hTempXjg->DrawCopy();
    //    dNdXjg[2][ipt]->Scale(dNdXjg[2][ipt]->GetBinContent(ipt));
    // dNdXjg[4][ipt]->Scale(dNdXjg[4][ipt]-->GetBinContent(ipt));
    drawSys(dNdXjg[4][ipt], dNdXjgSys[4][ipt], newYellow);
    drawSys(dNdXjg[2][ipt], dNdXjgSys[2][ipt], kGreen,3001);
    handsomeTH1(dNdXjg[4][ipt],2);
    //    dNdXjg[4][ipt]->SetMarkerStyle(24);
    //   dNdXjg[2][ipt]->SetMarkerStyle(25);
    dNdXjg[2][ipt]->Draw("same");
    dNdXjg[4][ipt]->Draw("same");
    if ( ipt==1 ){
      TLegend *ly = new TLegend(0.351273,0.6552521,0.9997611,0.9487395,NULL,"brNDC");
      easyLeg(ly);
      ly->AddEntry(dNdXjg[4][ipt],"PbPb 30-100%","p");
      ly->AddEntry(dNdXjg[2][ipt],"pp (smeared)","p");
      ly->Draw();
    }
    if(ipt + nPtBin == 8)
      drawCMSppPbPbDist(0.4,0.9);

    gPad->RedrawAxis();
    c6->cd(ipt);
    hTempXjg->DrawCopy();
    //    dNdXjg[5][ipt]->Scale(meanRjg[5]->GetBinContent(ipt));
    //  dNdXjg[6][ipt]->Scale(meanRjg[6]->GetBinContent(ipt));
    drawSys(dNdXjg[5][ipt], dNdXjgSys[5][ipt], newYellow);
    drawSys(dNdXjg[7][ipt], dNdXjgSys[2][ipt], kGreen, 3001);
    handsomeTH1(dNdXjg[5][ipt],9,1,34);
    handsomeTH1(dNdXjg[7][ipt],1,1);
 
    dNdXjg[6][ipt]->SetMarkerStyle(25);
   dNdXjg[6][ipt]->Draw("same");
    dNdXjg[5][ipt]->Draw("same");
    dNdXjg[7][ipt]->Draw("same");
    if ( ipt == 1 ) {
      TLegend *ly = new TLegend(0.351273,0.6052521,0.9997611,0.9087395,NULL,"brNDC");
      easyLeg(ly);
      ly->AddEntry(dNdXjg[5][ipt],"pPb Data","p");
      ly->AddEntry(dNdXjg[6][ipt],"PYTHIA+HIJING","p");
      ly->AddEntry(dNdXjg[7][ipt],"pp Data (2.76TeV)","p");
      ly->Draw();
    }

    if(ipt == 4)
      drawCMSpPbDist(0.4,0.8);

    double dx1=0.15;
    if ( ipt == nPtBin )
      drawText(Form("p_{T}^{#gamma} > %dGeV ", (int)ptBin[ipt-1]), 0.10+dx1+0.1,0.9,1,18);
    else if ( ipt == 1)
      drawText(Form("%dGeV < p_{T}^{#gamma} < %dGeV ", (int)ptBin[ipt-1], (int)ptBin[ipt]), 0.25+dx1,0.9,1,18);
    else
      drawText(Form("%dGeV < p_{T}^{#gamma} < %dGeV ", (int)ptBin[ipt-1], (int)ptBin[ipt]), 0.10+dx1,0.9,1,18);

    gPad->RedrawAxis();
  }

  c6->SaveAs("pT_dependence_xjg_pp_pbpb_distribution.pdf");
  c6->SaveAs("pT_dependence_xjg_pp_pbpb_distribution.png");
  
  // Dphi plots
  const Int_t nDPHIBINS = 8;
  const Double_t pi = TMath::Pi();
  Double_t DPHIBINS[nDPHIBINS+1] = {0, pi/20*5, pi/20*5*2, pi/20*5*3,
				    pi/20*16, pi/20*17, pi/20*18, pi/20*19,
				    pi};

  //rebin
  for(int sample = 1; sample <=7; sample++)
  {
    for(int ipt = 1; ipt<=nPtBin; ipt++)
    {
      dNdphi[sample][ipt] = (TH1D*)dNdphi[sample][ipt]->Rebin(nDPHIBINS,dNdphi[sample][ipt]->GetName(),DPHIBINS);
      for(int bin = 1; bin <=3; bin++)
      {
	dNdphi[sample][ipt]->SetBinContent(bin, dNdphi[sample][ipt]->GetBinContent(bin)/5.);
	dNdphi[sample][ipt]->SetBinError(bin, dNdphi[sample][ipt]->GetBinError(bin)/5.);
      }
    }
  }

  TH1D* hTempphi = new TH1D("hTempphi",";p_{T}^{#gamma} (GeV);",200,0,3.141592);
  TCanvas* cDphi = new TCanvas("cDphi","",1200,900);
  makeMultiPanelCanvas(cDphi,nPtBin,3,0.0,0.0,0.25,0.20,0.02);
  for ( int ipt = 1 ; ipt<=nPtBin  ; ipt++) {
    cDphi->cd(ipt+nPtBin*2);
    // draw pp
    hTempphi->SetXTitle("#Delta#phi");
    hTempphi->SetYTitle("#frac{1}{N_{J#gamma}} #frac{dN_{J#gamma}}{d#Delta#phi}");
    if(ipt == 1)
      hTempphi->SetAxisRange(0, TMath::Pi(),"X");
    else
      hTempphi->SetAxisRange(0.1, TMath::Pi(),"X");
    hTempphi->SetAxisRange(0.0011,2,"Y");
    handsomeTH1(hTempphi,0);
    hTempphi->GetYaxis()->SetTitleOffset(4.5);
    hTempphi->GetXaxis()->SetTitleOffset(3);
    hTempphi->DrawCopy();
    handsomeTH1(dNdphi[3][ipt],2);

    dNdphi[1][ipt]->Scale(1./dNdphi[1][ipt]->Integral());
    dNdphi[3][ipt]->Scale(1./dNdphi[3][ipt]->Integral());
    drawSys(dNdphi[1][ipt],dNdphiSys[1][ipt],kGreen,3001, -1,0.3);
    drawSys(dNdphi[3][ipt],dNdphiSys[3][ipt],newYellow, -1, -1,0.3);
    dNdphi[1][ipt]->Draw("same");
    //    dNdphi[1][ipt]->SetMarkerStyle(21);
    dNdphi[3][ipt]->Draw("same");
    gPad->SetLogy();
    if ( ipt == 1 ) {
      TLegend *ly = new TLegend(0.25,0.7556865,.9,0.99,NULL,"brNDC");
      easyLeg(ly);
      ly->AddEntry(dNdphi[3][ipt],"PbPb 0-30%","p");
      ly->AddEntry(dNdphi[1][ipt],"pp (smeared)","p");
      ly->Draw();
    }

    if(ipt+nPtBin == 8)
      drawCMSppPbPbDist(0.1,0.9);

    cDphi->cd(ipt+nPtBin);
    hTempphi->DrawCopy();
    // dNdphi[2][ipt]->Scale(dNdphi[2][ipt]->GetBinContent(ipt));
    // dNdphi[4][ipt]->Scale(dNdphi[4][ipt]-->GetBinContent(ipt));
    handsomeTH1(dNdphi[4][ipt],2);
    //    dNdphi[4][ipt]->SetMarkerStyle(24);
    //   dNdphi[2][ipt]->SetMarkerStyle(25);
    //    dNdphi[2][ipt]->SetMarkerStyle(21);
    dNdphi[2][ipt]->Scale(1./dNdphi[2][ipt]->Integral());
    dNdphi[4][ipt]->Scale(1./dNdphi[4][ipt]->Integral());

    drawSys(dNdphi[2][ipt],dNdphiSys[2][ipt],kGreen,3001,-1,0.3);
    drawSys(dNdphi[4][ipt],dNdphiSys[4][ipt],newYellow,-1,-1,0.3);

    dNdphi[2][ipt]->Draw("same");
    dNdphi[4][ipt]->Draw("same");
    gPad->SetLogy();
    if ( ipt==1 ){
      TLegend *ly = new TLegend(0.25,0.7,0.9,0.95,NULL,"brNDC");
      easyLeg(ly);
      ly->AddEntry(dNdphi[4][ipt],"PbPb 30-100%","p");
      ly->AddEntry(dNdphi[2][ipt],"pp (smeared)","p");
      ly->Draw();
    }
    if(ipt+nPtBin == 8)
      drawCMSppPbPbDist(0.1,0.9);


    cDphi->cd(ipt);
    hTempphi->DrawCopy();

    handsomeTH1(dNdphi[5][ipt],9,1,34);
    handsomeTH1(dNdphi[7][ipt],1,1,20);
    dNdphi[6][ipt]->Scale(1./dNdphi[6][ipt]->Integral());
    dNdphi[5][ipt]->Scale(1./dNdphi[5][ipt]->Integral());
    dNdphi[7][ipt]->Scale(1./dNdphi[7][ipt]->Integral());

    drawSys(dNdphi[5][ipt],dNdphiSys[5][ipt],newYellow,-1, -1,0.3);
    drawSys(dNdphi[7][ipt],dNdphiSys[2][ipt],kGreen,3001, -1,0.3);

    dNdphi[6][ipt]->SetMarkerStyle(25);

    dNdphi[6][ipt]->Draw("same");
    dNdphi[5][ipt]->Draw("same");
    dNdphi[7][ipt]->Draw("same");
    gPad->SetLogy();
    if ( ipt == 1 ) {
      TLegend *ly = new TLegend(0.251273,0.6552521,0.8997611,0.9487395,NULL,"brNDC");
      easyLeg(ly);
      ly->AddEntry(dNdphi[5][ipt],"pPb Data","p");
      ly->AddEntry(dNdphi[6][ipt],"PYTHIA+HIJING","p");
      ly->AddEntry(dNdphi[7][ipt],"pp Data (2.76TeV)","p");
      ly->Draw();
    }
    double dx1=0.16;
    if ( ipt == nPtBin )
      drawText(Form("p_{T}^{#gamma} > %dGeV ", (int)ptBin[ipt-1]), 0.10+dx1+0.1,0.9,1,18);
    else if ( ipt == 1)
      drawText(Form("%dGeV < p_{T}^{#gamma} < %dGeV ", (int)ptBin[ipt-1], (int)ptBin[ipt]), 0.25+dx1,0.9,1,18);
    else
      drawText(Form("%dGeV < p_{T}^{#gamma} < %dGeV ", (int)ptBin[ipt-1], (int)ptBin[ipt]), 0.10+dx1,0.9,1,18);

    if(ipt == 4)
      drawCMSpPbDist(0.1, 0.8);

  }
  cDphi->SaveAs("pT_dependence_dphi_pp_pbpb_figure1.pdf");
  cDphi->SaveAs("pT_dependence_dphi_pp_pbpb_figure1.png");
}
