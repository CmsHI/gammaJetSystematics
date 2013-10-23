#include "../commonUtilitySys.h"
#include <TRandom3.h>
#include <TFile.h>

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
  const int nRptBin[4] = {4,4,6,5};
  double ratioPtBin[4][7] = {{20,30,40,50,150},         
			     {20,30,40,50,150},
			     {20,30,40,50,60,80,150},
			     {20,30,50,80,100,150}};

  /* mean of each bins are  = {{25,35,45, 63},
			      {25,35,45, 64},
			      {25,35,45,55,69,93},
			      {25,41,65, 93, 123}};  // two 93's are coincidence  
  */
  double ratioPtBin1[4][7] = {{20,30,40,50,76},
			      {20,30,40,50,78},
			      {20,30,40,50,60,78, 108},
			      {20,30,52,78, 108, 130}};


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

  // jet pt distributions
  TH1D* hTempPt = new TH1D("hTemp",";p_{T}^{#gamma} (GeV);",200,10,300);
  TCanvas* c5 = new TCanvas("c5","",1200,900);
  makeMultiPanelCanvas(c5,nPtBin, 3, 0.0, 0.0, 0.25, 0.2, 0.02);
  //c5->Divide(nPtBin, 2, 0.0, 0.0);
  //c5->cd(0);
  //drawCMSppPbPb(0.1,0.975);
  for ( int ipt = 1 ; ipt<=nPtBin  ; ipt++) {
    c5->cd(ipt+nPtBin*2);
    // draw pp
    hTempPt->SetXTitle("p_{T}^{Jet} (GeV)");
    hTempPt->SetYTitle("#frac{dN_{j #gamma}}{dp_{T}^{jet}} #frac{1}{N_{#gamma}}");
    hTempPt->SetAxisRange(10,150,"X");
    hTempPt->SetAxisRange(0,0.025,"Y");
    //hTempPt->SetAxisRange(0.000001,2.,"Y");
    hTempPt->GetYaxis()->SetNdivisions(504);
    handsomeTH1(hTempPt,0);
    hTempPt->GetYaxis()->SetTitleOffset(4);
    hTempPt->GetXaxis()->SetTitleOffset(3);
    hTempPt->DrawCopy();
    //gPad->SetLogy();

    drawSys(dNdJetPt[1][ipt], dNdJetPtSys[1][ipt], kGreen,3001);
    drawSys(dNdJetPt[3][ipt], dNdJetPtSys[3][ipt], kYellow);
    handsomeTH1(dNdJetPt[3][ipt],2);
    dNdJetPt[1][ipt]->Draw("same");
    dNdJetPt[1][ipt]->SetMarkerStyle(21);
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

    drawSys(dNdJetPt[2][ipt], dNdJetPtSys[2][ipt], kGreen,3001);
    drawSys(dNdJetPt[4][ipt], dNdJetPtSys[4][ipt], kYellow);
    handsomeTH1(dNdJetPt[4][ipt],2);
    dNdJetPt[4][ipt]->SetMarkerStyle(24);
    dNdJetPt[2][ipt]->SetMarkerStyle(25);
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


        // draw pp
    c5->cd(ipt);
    // hTempPt->SetXTitle("p_{T}^{Jet} (GeV)");
    // hTempPt->SetYTitle("#frac{dN}{dp_{T}} #frac{1}{N}");
    // hTempPt->SetAxisRange(10,150,"X");
    // hTempPt->SetAxisRange(0,0.025,"Y");
    // handsomeTH1(hTempPt,0);
    // hTempPt->GetYaxis()->SetTitleOffset(1.5);
    // hTempPt->GetXaxis()->SetTitleOffset(1.25);
    hTempPt->DrawCopy();
    //gPad->SetLogy();

    drawSys(dNdJetPt[5][ipt], dNdJetPtSys[5][ipt], kYellow);
    drawSys(dNdJetPt[7][ipt], dNdJetPtSys[2][ipt], kGreen,3001);
    handsomeTH1(dNdJetPt[5][ipt],9);
    handsomeTH1(dNdJetPt[7][ipt],1,1,24);
    dNdJetPt[6][ipt]->Draw("same");
    dNdJetPt[5][ipt]->Draw("same");
    dNdJetPt[7][ipt]->Draw("same");
    if ( ipt == 1 ) {
      TLegend *ly = new TLegend(0.4855983,0.5529059,0.9512013,0.7645899,NULL,"brNDC");
      easyLeg(ly);
      ly->AddEntry(dNdJetPt[5][ipt],"pPb Data","p");
      ly->AddEntry(dNdJetPt[6][ipt],"PYTHIA+HIJING","p");
      ly->AddEntry(dNdJetPt[7][ipt],"pp Data","p");
      ly->Draw();
    }
    if(ipt == 4)
      drawCMSpPbDist(0.1,0.7);

    double dx1=0.18;
    if ( ipt == nPtBin )
      drawText(Form("p_{T}^{#gamma} > %dGeV ", (int)ptBin[ipt-1]), 0.12+dx1+0.25,0.8,1,18);//yeonju 130823
    else
      drawText(Form("%dGeV < p_{T}^{#gamma} < %dGeV ", (int)ptBin[ipt-1], (int)ptBin[ipt]), 0.12+dx1,0.8,1,18);//yeonju 130823



  }
  c5->SaveAs("pT_dependence_jetPt_pp_pbpb_distribution.pdf");


  // jet pt distributions
  TCanvas* c5_ratio = new TCanvas("c5_ratio","",1200,600);
  // c5_ratio->Divide(nPtBin, 2, 0.0, 0.0);
  // c5_ratio->cd(0);
  // drawCMSppPbPb(0.1,0.975);
  makeMultiPanelCanvas(c5_ratio,nPtBin, 2, 0.0, 0.0, 0.25, 0.2, 0.02);
  for ( int ipt = 1 ; ipt<=nPtBin  ; ipt++) {
    c5_ratio->cd(ipt+nPtBin);
    hTempPt->SetXTitle("p_{T}^{Jet} (GeV)");
    hTempPt->SetYTitle("PbPb/pp of jet yield");
    hTempPt->SetAxisRange(10,150,"X");
    hTempPt->SetAxisRange(0,2.9,"Y");
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
      ly->AddEntry(dNdJetPt[3][ipt],"PbPb 0-30%","p");
      //ly->AddEntry(dNdJetPt[1][ipt],"pp (smeared)","p");
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
      ly->AddEntry(dNdJetPt[4][ipt],"PbPb 30-100%","p");
      //ly->AddEntry(dNdJetPt[2][ipt],"pp (smeared)","p");
      ly->Draw();
    }

    double dx1=0.15;
    if ( ipt == nPtBin )
      drawText(Form("p_{T}^{#gamma} > %dGeV ", (int)ptBin[ipt-1]), 0.12+dx1+0.25,0.85,1,18);//yeonju 130823
    else
          drawText(Form("%dGeV < p_{T}^{#gamma} < %dGeV ", (int)ptBin[ipt-1], (int)ptBin[ipt]), 0.12+dx1,0.85,1,18);//yeonju 130823
  }
  c5_ratio->SaveAs("pT_dependence_jetPt_pp_pbpb_Ratio.pdf");


  // TCanvas* c5pa = new TCanvas("c5pa","",1200,350);
  // makeMultiPanelCanvas(c5pa,nPtBin,1,0.0,0.0,0.25,0.2,0.02);
  // //c5pa->Divide(nPtBin,1,0.0,0.0);
  // //c5pa->cd(0);
  // //drawCMSpPb(0.1,0.95);

  // for ( int ipt = 1 ; ipt<=nPtBin  ; ipt++) {
  //   c5pa->cd(ipt);
  //   // draw pp
  //   hTempPt->SetXTitle("p_{T}^{Jet} (GeV)");
  //   hTempPt->SetYTitle("#frac{dN}{dp_{T}} #frac{1}{N}");
  //   hTempPt->SetAxisRange(10,150,"X");
  //   hTempPt->SetAxisRange(0,0.025,"Y");
  //   handsomeTH1(hTempPt,0);
  //   hTempPt->GetYaxis()->SetTitleOffset(1.5);
  //   hTempPt->GetXaxis()->SetTitleOffset(1.25);
  //   hTempPt->DrawCopy();

  //   drawSys(dNdJetPt[5][ipt], dNdJetPtSys[5][ipt], kYellow);
  //   handsomeTH1(dNdJetPt[5][ipt],2);
  //   dNdJetPt[6][ipt]->Draw("same");
  //   dNdJetPt[5][ipt]->Draw("same");
  //   if ( ipt == 1 ) {
  //     TLegend *ly = new TLegend(0.4855983,0.5529059,0.9512013,0.7645899,NULL,"brNDC");
  //     easyLeg(ly);
  //     ly->AddEntry(dNdJetPt[5][ipt],"Data","p");
  //     ly->AddEntry(dNdJetPt[6][ipt],"PYTHIA+HIJING","p");
  //     ly->Draw();
  //     //drawCMSpPb(0.1,0.95);
  //   }
  //   double dx1=0.15;
  //   if ( ipt == nPtBin )
  //     drawText(Form("p_{T}^{#gamma} > %dGeV ", (int)ptBin[ipt-1]), 0.12+dx1+0.25,0.85,1,18);//yeonju 130823
  //   else
  //     drawText(Form("%dGeV < p_{T}^{#gamma} < %dGeV ", (int)ptBin[ipt-1], (int)ptBin[ipt]), 0.12+dx1,0.85,1,18);//yeonju 130823

  //   if(ipt == 4)
  //     drawCMSpPbDist(0.1,0.7);


  // }
  // c5pa->SaveAs("pT_dependence_jetPt_pA_distribution.pdf");



  // XJG plots
  TH1D* hTempXjg = new TH1D("hTempXjg",";p_{T}^{#gamma} (GeV);",200,0,2);
  TCanvas* c6 = new TCanvas("c6","",1200,900);
  makeMultiPanelCanvas(c6,nPtBin,3,0.0,0.0,0.25,0.20,0.02);
  //c6->Divide(nPtBin,2,0.0,0.0);
  //c6->cd(0);
  //drawCMSppPbPb(0.1,0.975);

  for ( int ipt = 1 ; ipt<=nPtBin  ; ipt++) {
    c6->cd(ipt+2*nPtBin);
    // draw pp
    hTempXjg->SetXTitle("x_{j#gamma}");
    hTempXjg->SetYTitle("#frac{dN_{j #gamma}}{dx} #frac{1}{N_{j #gamma}}");
    hTempXjg->SetAxisRange(0,2,"X");
    //        hTempXjg->SetAxisRange(0,0.025,"Y");
    //hTempXjg->SetAxisRange(-.2,3,"Y");
    hTempXjg->SetAxisRange(0,2,"Y");
    hTempXjg->GetYaxis()->SetNdivisions(405);
    hTempXjg->GetXaxis()->SetNdivisions(405);
    handsomeTH1(hTempXjg,0);
    hTempXjg->GetYaxis()->SetTitleOffset(3);
    hTempXjg->GetXaxis()->SetTitleOffset(3);
    hTempXjg->DrawCopy();
    //onSun(0,0,2,0);
    //    dNdXjg[1][ipt]->Scale(meanRjg[1]->GetBinContent(ipt));
    //  dNdXjg[3][ipt]->Scale(meanRjg[3]->GetBinContent(ipt));
    drawSys(dNdXjg[3][ipt], dNdXjgSys[3][ipt], kYellow);
    drawSys(dNdXjg[1][ipt], dNdXjgSys[1][ipt], kGreen,3001);
    handsomeTH1(dNdXjg[3][ipt],2);
    dNdXjg[1][ipt]->Draw("same");
    dNdXjg[1][ipt]->SetMarkerStyle(21);
    dNdXjg[3][ipt]->Draw("same");
    if ( ipt == 1 ) {
      TLegend *ly = new TLegend(0.351273,0.6152521,0.9997611,0.9087395,NULL,"brNDC");
      easyLeg(ly);
      ly->AddEntry(dNdXjg[3][ipt],"PbPb 0-30%","p");
      ly->AddEntry(dNdXjg[1][ipt],"pp (smeared)","p");
      ly->Draw();
      //drawCMSppPbPb(0.1,0.95);
    }

    if(ipt + nPtBin == 8)
      drawCMSppPbPbDist(0.5,0.9);

    gPad->RedrawAxis();

    c6->cd(ipt+nPtBin);
    hTempXjg->DrawCopy();
    //onSun(0,0,2,0);

    //    dNdXjg[2][ipt]->Scale(dNdXjg[2][ipt]->GetBinContent(ipt));
    // dNdXjg[4][ipt]->Scale(dNdXjg[4][ipt]-->GetBinContent(ipt));
    drawSys(dNdXjg[4][ipt], dNdXjgSys[4][ipt], kYellow);
    drawSys(dNdXjg[2][ipt], dNdXjgSys[2][ipt], kGreen,3001);
    handsomeTH1(dNdXjg[4][ipt],2);
    dNdXjg[4][ipt]->SetMarkerStyle(24);
    dNdXjg[2][ipt]->SetMarkerStyle(25);
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
      drawCMSppPbPbDist(0.5,0.9);


    c6->cd(ipt);
    hTempXjg->DrawCopy();
    //onSun(0,0,2,0);

    //    dNdXjg[5][ipt]->Scale(meanRjg[5]->GetBinContent(ipt));
    //  dNdXjg[6][ipt]->Scale(meanRjg[6]->GetBinContent(ipt));
    drawSys(dNdXjg[5][ipt], dNdXjgSys[5][ipt], kYellow);
    drawSys(dNdXjg[7][ipt], dNdXjgSys[2][ipt], kGreen, 3001);
    handsomeTH1(dNdXjg[5][ipt],9);
    handsomeTH1(dNdXjg[7][ipt],1,1,24);
    dNdXjg[6][ipt]->Draw("same");
    dNdXjg[5][ipt]->Draw("same");
    dNdXjg[7][ipt]->Draw("same");
    if ( ipt == 1 ) {
      TLegend *ly = new TLegend(0.351273,0.6552521,0.9997611,0.9487395,NULL,"brNDC");
      easyLeg(ly);
      ly->AddEntry(dNdXjg[5][ipt],"pPb Data","p");
      ly->AddEntry(dNdXjg[6][ipt],"PYTHIA+HIJING","p");
      ly->AddEntry(dNdXjg[7][ipt],"pp Data","p");
      ly->Draw();
      //drawCMSpPb(0.1,0.95);
    }

    if(ipt == 4)
      drawCMSpPbDist(0.1,0.8);

    double dx1=0.15;
    if ( ipt == nPtBin )
      drawText(Form("p_{T}^{#gamma} > %dGeV ", (int)ptBin[ipt-1]), 0.12+dx1+0.25,0.9,1,18);//yeonju 130823
    else
      drawText(Form("%dGeV < p_{T}^{#gamma} < %dGeV ", (int)ptBin[ipt-1], (int)ptBin[ipt]), 0.12+dx1,0.9,1,18);//yeonju 130823
    gPad->RedrawAxis();
  }

  c6->SaveAs("pT_dependence_xjg_pp_pbpb_distribution.pdf");


  // TCanvas* c6pa = new TCanvas("c6pa","",1200,350);
  // makeMultiPanelCanvas(c6pa,nPtBin,1,0.0,0.0,0.25,0.2,0.02);
  // //c6pa->Divide(nPtBin,1,0.0,0.0);
  // //c6pa->cd(0);
  // //drawCMSpPb(0.1,0.95);

  // for ( int ipt = 1 ; ipt<=nPtBin  ; ipt++) {
  //   c6pa->cd(ipt);

  //   hTempXjg->GetYaxis()->SetTitleOffset(1.5);
  //   hTempXjg->GetXaxis()->SetTitleOffset(1.25);
  //   hTempXjg->DrawCopy();
  //   //onSun(0,0,2,0);

  //   //    dNdXjg[5][ipt]->Scale(meanRjg[5]->GetBinContent(ipt));
  //   //  dNdXjg[6][ipt]->Scale(meanRjg[6]->GetBinContent(ipt));
  //   drawSys(dNdXjg[5][ipt], dNdXjgSys[5][ipt], kYellow);
  //   handsomeTH1(dNdXjg[5][ipt],2);
  //   dNdXjg[6][ipt]->Draw("same");
  //   dNdXjg[5][ipt]->Draw("same");
  //   if ( ipt == 1 ) {
  //     TLegend *ly = new TLegend(0.351273,0.6552521,0.9997611,0.9487395,NULL,"brNDC");
  //     easyLeg(ly);
  //     ly->AddEntry(dNdXjg[5][ipt],"Data","p");
  //     ly->AddEntry(dNdXjg[6][ipt],"PYTHIA+HIJING","p");
  //     ly->Draw();
  //     //drawCMSpPb(0.1,0.95);
  //   }
  //   double dx1=0.15;
  //   if ( ipt == nPtBin )
  //     drawText(Form("p_{T}^{#gamma} > %dGeV ", (int)ptBin[ipt-1]), 0.12+dx1+0.25,0.9,1,18);
  //   else
  //     drawText(Form("%dGeV < p_{T}^{#gamma} < %dGeV ", (int)ptBin[ipt-1], (int)ptBin[ipt]), 0.12+dx1,0.9,1,18);//yeonju 130823

  //   if(ipt == 4)
  //     drawCMSpPbDist(0.1,0.8);

  // }
  // c6pa->SaveAs("pT_dependence_xjg_pA_distribution.pdf");



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
  //cDphi->Divide(nPtBin,2,0.0,0.0);
  //cDphi->cd(0);
  //drawCMSppPbPb(0.1,0.975);

  for ( int ipt = 1 ; ipt<=nPtBin  ; ipt++) {
    cDphi->cd(ipt+nPtBin*2);
    // draw pp
    hTempphi->SetXTitle("#Delta#phi");
    hTempphi->SetYTitle("#frac{dN_{j #gamma}}{d#Delta#phi} #frac{1}{N_{j #gamma}}");
    hTempphi->SetAxisRange(0, TMath::Pi(),"X");
    hTempphi->SetAxisRange(0.001,2,"Y");
    handsomeTH1(hTempphi,0);
    hTempphi->GetYaxis()->SetTitleOffset(4.5);
    hTempphi->GetXaxis()->SetTitleOffset(3);
    hTempphi->DrawCopy();
    handsomeTH1(dNdphi[3][ipt],2);

    dNdphi[1][ipt]->Scale(1./dNdphi[1][ipt]->Integral());
    dNdphi[3][ipt]->Scale(1./dNdphi[3][ipt]->Integral());
    drawSys(dNdphi[1][ipt],dNdphiSys[1][ipt],kGreen,3001, -1,0.3);
    drawSys(dNdphi[3][ipt],dNdphiSys[3][ipt],kYellow, -1, -1,0.3);
    dNdphi[1][ipt]->Draw("same");
    dNdphi[1][ipt]->SetMarkerStyle(21);
    dNdphi[3][ipt]->Draw("same");
    gPad->SetLogy();
    if ( ipt == 1 ) {
      TLegend *ly = new TLegend(0.351273,0.6152521,0.9997611,0.9087395,NULL,"brNDC");
      easyLeg(ly);
      ly->AddEntry(dNdphi[3][ipt],"PbPb 0-30%","p");
      ly->AddEntry(dNdphi[1][ipt],"pp (smeared)","p");
      ly->Draw();
      //drawCMSppPbPb(0.1,0.95);
    }

    if(ipt+nPtBin == 8)
      drawCMSppPbPbDist(0.1,0.9);

    cDphi->cd(ipt+nPtBin);
    hTempphi->DrawCopy();
    //onSun(0,0,2,0);

    // dNdphi[2][ipt]->Scale(dNdphi[2][ipt]->GetBinContent(ipt));
    // dNdphi[4][ipt]->Scale(dNdphi[4][ipt]-->GetBinContent(ipt));
    handsomeTH1(dNdphi[4][ipt],2);
    dNdphi[4][ipt]->SetMarkerStyle(24);
    dNdphi[2][ipt]->SetMarkerStyle(25);
    dNdphi[2][ipt]->Scale(1./dNdphi[2][ipt]->Integral());
    dNdphi[4][ipt]->Scale(1./dNdphi[4][ipt]->Integral());

    drawSys(dNdphi[2][ipt],dNdphiSys[2][ipt],kGreen,3001,-1,0.3);
    drawSys(dNdphi[4][ipt],dNdphiSys[4][ipt],kYellow,-1,-1,0.3);

    dNdphi[2][ipt]->Draw("same");
    dNdphi[4][ipt]->Draw("same");
    gPad->SetLogy();
    if ( ipt==1 ){
      TLegend *ly = new TLegend(0.351273,0.6552521,0.9997611,0.9487395,NULL,"brNDC");
      easyLeg(ly);
      ly->AddEntry(dNdphi[4][ipt],"PbPb 30-100%","p");
      ly->AddEntry(dNdphi[2][ipt],"pp (smeared)","p");
      ly->Draw();
    }
    if(ipt+nPtBin == 8)
      drawCMSppPbPbDist(0.1,0.9);


    cDphi->cd(ipt);
    hTempphi->DrawCopy();

    handsomeTH1(dNdphi[5][ipt],9);
    handsomeTH1(dNdphi[7][ipt],1,1,24);
    dNdphi[6][ipt]->Scale(1./dNdphi[6][ipt]->Integral());
    dNdphi[5][ipt]->Scale(1./dNdphi[5][ipt]->Integral());
    dNdphi[7][ipt]->Scale(1./dNdphi[7][ipt]->Integral());

    drawSys(dNdphi[5][ipt],dNdphiSys[5][ipt],kYellow,-1, -1,0.3);
    drawSys(dNdphi[7][ipt],dNdphiSys[2][ipt],kGreen,3001, -1,0.3);

    dNdphi[6][ipt]->Draw("same");
    dNdphi[5][ipt]->Draw("same");
    dNdphi[7][ipt]->Draw("same");
    gPad->SetLogy();
    if ( ipt == 1 ) {
      TLegend *ly = new TLegend(0.351273,0.6552521,0.9997611,0.9487395,NULL,"brNDC");
      easyLeg(ly);
      ly->AddEntry(dNdphi[5][ipt],"pPb Data","p");
      ly->AddEntry(dNdphi[6][ipt],"PYTHIA+HIJING","p");
      ly->AddEntry(dNdphi[7][ipt],"pp Data","p");
      ly->Draw();
      //drawCMSpPb(0.1,0.95);
    }
    double dx1=0.16;
    if ( ipt == nPtBin )
      drawText(Form("p_{T}^{#gamma} > %dGeV ", (int)ptBin[ipt-1]), 0.12+dx1+0.25,0.9,1,18);
    else
      drawText(Form("%dGeV < p_{T}^{#gamma} < %dGeV ", (int)ptBin[ipt-1], (int)ptBin[ipt]), 0.12+dx1,0.9,1,18);//yeonju 130823

    if(ipt == 4)
      drawCMSpPbDist(0.1, 0.8);

  }
  cDphi->SaveAs("pT_dependence_dphi_pp_pbpb_figure1.pdf");


  // TCanvas* cDphiPa = new TCanvas("cDphiPa","",1200,350);
  // makeMultiPanelCanvas(cDphiPa,nPtBin,1,0.0,0.0,0.25,0.2,0.02);
  //cDphiPa->Divide(nPtBin,1,0.0,0.0);
  //cDphiPa->cd(0);
  //drawCMSpPb(0.1,0.95);

  // for ( int ipt = 1 ; ipt<=nPtBin  ; ipt++) {
  //   cDphiPa->cd(ipt);

  //   hTempphi->GetYaxis()->SetTitleOffset(1.5);
  //   hTempphi->GetXaxis()->SetTitleOffset(1.25);
  //   hTempphi->DrawCopy();

  //   handsomeTH1(dNdphi[5][ipt],2);
  //   dNdphi[6][ipt]->Scale(1./dNdphi[6][ipt]->Integral());
  //   dNdphi[5][ipt]->Scale(1./dNdphi[5][ipt]->Integral());

  //   drawSys(dNdphi[5][ipt],dNdphiSys[5][ipt],kYellow,-1, -1,0.3);

  //   dNdphi[6][ipt]->Draw("same");
  //   dNdphi[5][ipt]->Draw("same");
  //   gPad->SetLogy();
  //   if ( ipt == 1 ) {
  //     TLegend *ly = new TLegend(0.351273,0.6552521,0.9997611,0.9487395,NULL,"brNDC");
  //     easyLeg(ly);
  //     ly->AddEntry(dNdphi[5][ipt],"Data","p");
  //     ly->AddEntry(dNdphi[6][ipt],"PYTHIA+HIJING","p");
  //     ly->Draw();
  //     //drawCMSpPb(0.1,0.95);
  //   }
  //   double dx1=0.16;
  //   if ( ipt == nPtBin )
  //     drawText(Form("p_{T}^{#gamma} > %dGeV ", (int)ptBin[ipt-1]), 0.12+dx1+0.25,0.9,1,18);
  //   else
  //     drawText(Form("%dGeV < p_{T}^{#gamma} < %dGeV ", (int)ptBin[ipt-1], (int)ptBin[ipt]), 0.12+dx1,0.9,1,18);//yeonju 130823

  //   if(ipt == 4)
  //     drawCMSpPbDist(0.1, 0.8);

  // }
  // cDphiPa->SaveAs("pT_dependence_dphi_pA_figure1.pdf");




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

  //   drawSys(IaaRatio[4][ipt], IaaRatioSys[4][ipt], kYellow);
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
