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

  TH1D* dNdJetPt[7][5]; // [collision] [ ptbin]  [Before/After variation]
  TH1D* dNdJetPtSys[7][5]; // [collision] [ ptbin]  [Before/After variation]

  TH1D* dNdXjg[7][5]; // [collision] [ ptbin]  [Before/After variation]
  TH1D* dNdXjgSys[7][5]; // [collision] [ ptbin]  [Before/After variation]

  TH1D* dNdphi[7][5]; // [collision] [ ptbin]  [Before/After variation]
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
  f =   new TFile("../resultHistograms/resultHistograms_nominal.root");
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
  f =   new TFile("../resultHistograms/resultHistograms_nominal.root");
  for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
    dNdJetPt[5][ipt] = (TH1D*)f->Get(Form("dNdJetPt_ppb_ptBin%d", ipt ));
    dNdXjg[5][ipt] = (TH1D*)f->Get(Form("dNdXjg_ppb_ptBin%d", ipt ));
    dNdphi[5][ipt] = (TH1D*)f->Get(Form("dNdphi_ppb_ptBin%d", ipt ));
    }

  f =   new TFile("../resultHistograms/resultHistograms_MCrecoIso.root");
  for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
    dNdJetPt[6][ipt] = (TH1D*)f->Get(Form("dNdJetPt_ppb_ptBin%d", ipt ));
    dNdXjg[6][ipt] = (TH1D*)f->Get(Form("dNdXjg_ppb_ptBin%d", ipt ));
    dNdphi[6][ipt] = (TH1D*)f->Get(Form("dNdphi_ppb_ptBin%d", ipt ));
  }


  TFile* fSys = new TFile("../relativeSysDist/relativeSys_merged.root");

  for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
    dNdJetPtSys[1][ipt] = (TH1D*)fSys->Get(Form("dNdJetPt_pp_ptBin%d_uncertainty_merged",  ipt ));
    dNdXjgSys[1][ipt] = (TH1D*)fSys->Get(Form("dNdXjg_pp_ptBin%d_uncertainty_merged",  ipt ));

  }
  for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
    dNdJetPtSys[2][ipt] = (TH1D*)dNdJetPtSys[1][ipt]->Clone(Form("%s_2",dNdJetPtSys[1][ipt]->GetName()));
    dNdXjgSys[2][ipt] = (TH1D*)dNdXjgSys[1][ipt]->Clone(Form("%s_2",dNdXjgSys[1][ipt]->GetName()));

  }

  for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
    dNdJetPtSys[3][ipt] = (TH1D*)fSys->Get(Form("dNdJetPt_pbpb_centralityBin1_ptBin%d_uncertainty_merged",  ipt ));
    dNdXjgSys[3][ipt] = (TH1D*)fSys->Get(Form("dNdXjg_pbpb_centralityBin1_ptBin%d_uncertainty_merged",  ipt ));
  }
  for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
    dNdJetPtSys[4][ipt] = (TH1D*)fSys->Get(Form("dNdJetPt_pbpb_centralityBin2_ptBin%d_uncertainty_merged",  ipt ));
    dNdXjgSys     [4][ipt] = (TH1D*)fSys->Get(Form("dNdXjg_pbpb_centralityBin2_ptBin%d_uncertainty_merged",  ipt ));
  }
  for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
    dNdJetPtSys[5][ipt] = (TH1D*)fSys->Get(Form("dNdJetPt_ppb_ptBin%d_uncertainty_merged",  ipt ));
    dNdXjgSys     [5][ipt] = (TH1D*)fSys->Get(Form("dNdXjg_ppb_ptBin%d_uncertainty_merged",  ipt ));
  }
  
  // jet pt distributions
  TH1D* hTempPt = new TH1D("hTemp",";p_{T}^{#gamma} (GeV);",200,10,300);
  TCanvas* c5 = new TCanvas("c5","",1200,600);
  //makeMultiPanelCanvas(c5,nPtBin, 2, 0.0, 0.0, 0.2, 0.15, 0.02);
  c5->Divide(nPtBin, 2, 0.0, 0.0);
  c5->cd(0);
  drawCMSppPbPb(0.1,0.975);
  for ( int ipt = 1 ; ipt<=nPtBin  ; ipt++) {
    c5->cd(ipt+nPtBin);
    // draw pp
    hTempPt->SetXTitle("p_{T}^{Jet} (GeV)");
    hTempPt->SetYTitle("#frac{dN}{dp_{T}} #frac{1}{N}");
    hTempPt->SetAxisRange(10,150,"X");
    //        hTempPt->SetAxisRange(0,0.025,"Y");
    hTempPt->SetAxisRange(0,0.03,"Y");
    handsomeTH1(hTempPt,0);
    hTempPt->GetYaxis()->SetTitleOffset(3);
    hTempPt->GetXaxis()->SetTitleOffset(2);
    hTempPt->DrawCopy();

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


    c5->cd(ipt);
    hTempPt->DrawCopy();

    drawSys(dNdJetPt[2][ipt], dNdJetPtSys[2][ipt], kGreen,3001);
    drawSys(dNdJetPt[4][ipt], dNdJetPtSys[4][ipt], kYellow);
    handsomeTH1(dNdJetPt[4][ipt],2);
    dNdJetPt[4][ipt]->SetMarkerStyle(24);
    dNdJetPt[2][ipt]->SetMarkerStyle(25);
    dNdJetPt[2][ipt]->Draw("same");
    dNdJetPt[4][ipt]->Draw("same");
    if ( ipt==1 ){
      TLegend *ly = new TLegend(0.4484643,0.5088445,0.9140673,0.75102941,NULL,"brNDC");
      easyLeg(ly);
      ly->AddEntry(dNdJetPt[4][ipt],"PbPb 30-100%","p");
      ly->AddEntry(dNdJetPt[2][ipt],"pp (smeared)","p");
      ly->Draw();
      //drawCMSppPbPb(0.1,0.95);
    }

    double dx1=0.15;
    if ( ipt == nPtBin )
      drawText(Form("p_{T}^{#gamma} > %dGeV ", (int)ptBin[ipt-1]), 0.12+dx1+0.25,0.85,1,15);//yeonju 130823
    else
      drawText(Form("%dGeV < p_{T}^{#gamma} < %dGeV ", (int)ptBin[ipt-1], (int)ptBin[ipt]), 0.12+dx1,0.85,1,15);//yeonju 130823


  }
  c5->SaveAs("pT_dependence_jetPt_pp_pbpb_distribution.pdf");

  TCanvas* c5pa = new TCanvas("c5pa","",1200,350);
  //makeMultiPanelCanvas(c5pa,nPtBin,1,0.0,0.0,0.2,0.15,0.02);
  c5pa->Divide(nPtBin,1,0.0,0.0);
  c5pa->cd(0);
  drawCMSpPb(0.1,0.95);

  for ( int ipt = 1 ; ipt<=nPtBin  ; ipt++) {
    c5pa->cd(ipt);
    // draw pp
    hTempPt->SetXTitle("p_{T}^{Jet} (GeV)");
    hTempPt->SetYTitle("#frac{dN}{dp_{T}} #frac{1}{N}");
    hTempPt->SetAxisRange(10,150,"X");
    //        hTempPt->SetAxisRange(0,0.025,"Y");
    hTempPt->SetAxisRange(0,0.03,"Y");
    handsomeTH1(hTempPt,0);
    hTempPt->GetYaxis()->SetTitleOffset(1.5);
    hTempPt->GetXaxis()->SetTitleOffset(1.25);
    hTempPt->DrawCopy();

    drawSys(dNdJetPt[5][ipt], dNdJetPtSys[5][ipt], kYellow);
    handsomeTH1(dNdJetPt[5][ipt],2);
    dNdJetPt[6][ipt]->Draw("same");
    dNdJetPt[5][ipt]->Draw("same");
    if ( ipt == 1 ) {
      TLegend *ly = new TLegend(0.4855983,0.5529059,0.9512013,0.7645899,NULL,"brNDC");
      easyLeg(ly);
      ly->AddEntry(dNdJetPt[5][ipt],"Data","p");
      ly->AddEntry(dNdJetPt[6][ipt],"PYTHIA+HIJING","p");
      ly->Draw();
      //drawCMSpPb(0.1,0.95);
    }
    double dx1=0.15;
    if ( ipt == nPtBin )
      drawText(Form("p_{T}^{#gamma} > %dGeV ", (int)ptBin[ipt-1]), 0.12+dx1+0.25,0.85,1,15);//yeonju 130823
    else
      drawText(Form("%dGeV < p_{T}^{#gamma} < %dGeV ", (int)ptBin[ipt-1], (int)ptBin[ipt]), 0.12+dx1,0.85,1,15);//yeonju 130823


  }
  c5pa->SaveAs("pT_dependence_jetPt_pA_distribution.pdf");



  // XJG plots
  TH1D* hTempXjg = new TH1D("hTempXjg",";p_{T}^{#gamma} (GeV);",200,0,2);
  TCanvas* c6 = new TCanvas("c6","",1200,600);
  //makeMultiPanelCanvas(c6,nPtBin,2,0.0,0.0,0.2,0.15,0.02);
  c6->Divide(nPtBin,2,0.0,0.0);
  c6->cd(0);
  drawCMSppPbPb(0.1,0.975);

  for ( int ipt = 1 ; ipt<=nPtBin  ; ipt++) {
    c6->cd(ipt+nPtBin);
    // draw pp
    hTempXjg->SetXTitle("x_{j#gamma}");
    hTempXjg->SetYTitle("#frac{dN}{dx} #frac{1}{N}");
    hTempXjg->SetAxisRange(0,2,"X");
    //        hTempXjg->SetAxisRange(0,0.025,"Y");
    //hTempXjg->SetAxisRange(-.2,3,"Y");
    hTempXjg->SetAxisRange(0,2,"Y");
    handsomeTH1(hTempXjg,0);
    hTempXjg->GetYaxis()->SetTitleOffset(3);
    hTempXjg->GetXaxis()->SetTitleOffset(2);
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
      TLegend *ly = new TLegend(0.351273,0.6552521,0.9997611,0.9487395,NULL,"brNDC");
      easyLeg(ly);
      ly->AddEntry(dNdXjg[3][ipt],"PbPb 0-30%","p");
      ly->AddEntry(dNdXjg[1][ipt],"pp (smeared)","p");
      ly->Draw();
      //drawCMSppPbPb(0.1,0.95);
    }


    c6->cd(ipt);
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

    double dx1=0.15;
    if ( ipt == nPtBin )
      drawText(Form("p_{T}^{#gamma} > %dGeV ", (int)ptBin[ipt-1]), 0.12+dx1+0.25,0.85,1,15);//yeonju 130823
    else
      drawText(Form("%dGeV < p_{T}^{#gamma} < %dGeV ", (int)ptBin[ipt-1], (int)ptBin[ipt]), 0.12+dx1,0.85,1,15);//yeonju 130823

  }
  c6->SaveAs("pT_dependence_xjg_pp_pbpb_distribution.pdf");


  TCanvas* c6pa = new TCanvas("c6pa","",1200,350);
  //makeMultiPanelCanvas(c6pa,nPtBin,1,0.0,0.0,0.2,0.15,0.02);
  c6pa->Divide(nPtBin,1,0.0,0.0);
  c6pa->cd(0);
  drawCMSpPb(0.1,0.95);

  for ( int ipt = 1 ; ipt<=nPtBin  ; ipt++) {
    c6pa->cd(ipt);

    hTempXjg->GetYaxis()->SetTitleOffset(1.5);
    hTempXjg->GetXaxis()->SetTitleOffset(1.25);
    hTempXjg->DrawCopy();
    //onSun(0,0,2,0);

    //    dNdXjg[5][ipt]->Scale(meanRjg[5]->GetBinContent(ipt));
    //  dNdXjg[6][ipt]->Scale(meanRjg[6]->GetBinContent(ipt));
    drawSys(dNdXjg[5][ipt], dNdXjgSys[5][ipt], kYellow);
    handsomeTH1(dNdXjg[5][ipt],2);
    dNdXjg[6][ipt]->Draw("same");
    dNdXjg[5][ipt]->Draw("same");
    if ( ipt == 1 ) {
      TLegend *ly = new TLegend(0.351273,0.6552521,0.9997611,0.9487395,NULL,"brNDC");
      easyLeg(ly);
      ly->AddEntry(dNdXjg[5][ipt],"Data","p");
      ly->AddEntry(dNdXjg[6][ipt],"PYTHIA+HIJING","p");
      ly->Draw();
      //drawCMSpPb(0.1,0.95);
    }
    double dx1=0.15;
    if ( ipt == nPtBin )
      drawText(Form("p_{T}^{#gamma} > %dGeV ", (int)ptBin[ipt-1]), 0.12+dx1+0.25,0.9,1,15);
    else
      drawText(Form("%dGeV < p_{T}^{#gamma} < %dGeV ", (int)ptBin[ipt-1], (int)ptBin[ipt]), 0.12+dx1,0.9,1,15);//yeonju 130823


  }
  c6pa->SaveAs("pT_dependence_xjg_pA_distribution.pdf");



  // Dphi plots
  TH1D* hTempphi = new TH1D("hTempphi",";p_{T}^{#gamma} (GeV);",200,0,3.141592);
  TCanvas* cDphi = new TCanvas("cDphi","",1200,600);
  cDphi->Divide(nPtBin,2,0.0,0.0);
  cDphi->cd(0);
  drawCMSppPbPb(0.1,0.975);

  for ( int ipt = 1 ; ipt<=nPtBin  ; ipt++) {
    cDphi->cd(ipt+nPtBin);
    // draw pp
    hTempphi->SetXTitle("#Delta#phi");
    hTempphi->SetYTitle("#frac{dN}{d#Delta#phi} #frac{1}{N}");
    hTempphi->SetAxisRange(0,3.141592,"X");
    hTempphi->SetAxisRange(0.001,2,"Y");
    handsomeTH1(hTempphi,0);
    hTempphi->GetYaxis()->SetTitleOffset(3);
    hTempphi->GetXaxis()->SetTitleOffset(2);
    hTempphi->DrawCopy();
    handsomeTH1(dNdphi[3][ipt],2);

    dNdphi[1][ipt]->Scale(1./dNdphi[1][ipt]->Integral());
    dNdphi[3][ipt]->Scale(1./dNdphi[3][ipt]->Integral());
    gPad->SetLogy();
    dNdphi[1][ipt]->Draw("same");
    dNdphi[1][ipt]->SetMarkerStyle(21);
    dNdphi[3][ipt]->Draw("same");
    if ( ipt == 1 ) {
      TLegend *ly = new TLegend(0.351273,0.6552521,0.9997611,0.9487395,NULL,"brNDC");
      easyLeg(ly);
      ly->AddEntry(dNdphi[3][ipt],"PbPb 0-30%","p");
      ly->AddEntry(dNdphi[1][ipt],"pp (smeared)","p");
      ly->Draw();
      //drawCMSppPbPb(0.1,0.95);
    }


    cDphi->cd(ipt);
    hTempphi->DrawCopy();
    //onSun(0,0,2,0);

    //    dNdphi[2][ipt]->Scale(dNdphi[2][ipt]->GetBinContent(ipt));
    // dNdphi[4][ipt]->Scale(dNdphi[4][ipt]-->GetBinContent(ipt));
    handsomeTH1(dNdphi[4][ipt],2);
    dNdphi[4][ipt]->SetMarkerStyle(24);
    dNdphi[2][ipt]->SetMarkerStyle(25);
    dNdphi[2][ipt]->Scale(1./dNdphi[2][ipt]->Integral());
    dNdphi[4][ipt]->Scale(1./dNdphi[4][ipt]->Integral());
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

    double dx1=0.15;
    if ( ipt == nPtBin )
      drawText(Form("p_{T}^{#gamma} > %dGeV ", (int)ptBin[ipt-1]), 0.12+dx1+0.25,0.85,1,15);//yeonju 130823
    else
      drawText(Form("%dGeV < p_{T}^{#gamma} < %dGeV ", (int)ptBin[ipt-1], (int)ptBin[ipt]), 0.12+dx1,0.85,1,15);//yeonju 130823

  }
  cDphi->SaveAs("pT_dependence_dphi_pp_pbpb_distribution.pdf");


  TCanvas* cDphiPa = new TCanvas("cDphiPa","",1200,350);
  //makeMultiPanelCanvas(cDphiPa,nPtBin,1,0.0,0.0,0.2,0.15,0.02);
  cDphiPa->Divide(nPtBin,1,0.0,0.0);
  cDphiPa->cd(0);
  drawCMSpPb(0.1,0.95);

  for ( int ipt = 1 ; ipt<=nPtBin  ; ipt++) {
    cDphiPa->cd(ipt);

    hTempphi->GetYaxis()->SetTitleOffset(1.5);
    hTempphi->GetXaxis()->SetTitleOffset(1.25);
    hTempphi->DrawCopy();

    handsomeTH1(dNdphi[5][ipt],2);
    dNdphi[6][ipt]->Scale(1./dNdphi[6][ipt]->Integral());
    dNdphi[5][ipt]->Scale(1./dNdphi[5][ipt]->Integral());
    dNdphi[6][ipt]->Draw("same");
    dNdphi[5][ipt]->Draw("same");
    gPad->SetLogy();
    if ( ipt == 1 ) {
      TLegend *ly = new TLegend(0.351273,0.6552521,0.9997611,0.9487395,NULL,"brNDC");
      easyLeg(ly);
      ly->AddEntry(dNdphi[5][ipt],"Data","p");
      ly->AddEntry(dNdphi[6][ipt],"PYTHIA+HIJING","p");
      ly->Draw();
      //drawCMSpPb(0.1,0.95);
    }
    double dx1=0.15;
    if ( ipt == nPtBin )
      drawText(Form("p_{T}^{#gamma} > %dGeV ", (int)ptBin[ipt-1]), 0.12+dx1+0.25,0.9,1,15);
    else
      drawText(Form("%dGeV < p_{T}^{#gamma} < %dGeV ", (int)ptBin[ipt-1], (int)ptBin[ipt]), 0.12+dx1,0.9,1,15);//yeonju 130823


  }
  cDphiPa->SaveAs("pT_dependence_dphi_pA_distribution.pdf");




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