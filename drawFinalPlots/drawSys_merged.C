#include "../commonUtilitySys.h"
#include <TRandom3.h>
#include <TFile.h>

void drawSys_merged() {
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
  TH1D* dNdJetPtSysIaa[7][5]; // [collision] [ ptbin]  [Before/After variation]

  TH1D* dNdXjg[7][5]; // [collision] [ ptbin]  [Before/After variation]
  TH1D* dNdXjgSys[7][5]; // [collision] [ ptbin]  [Before/After variation]
  
  TH1D* Iaa[7][5]; // [collision] [ ptbin]  [Before/After variation]
  TH1D* IaaSys[7][5]; // [collision] [ ptbin]  [Before/After variation]

  TH1D* meanJetPt[7];   // [collision] [Before/After variation]
  TH1D* meanJetPtSys[7];   // [collision] [Before/After variation]

  TH1D* meanXjg[7];   // [collision] [Before/After variation]
  TH1D* meanXjgSys[7];   // [collision] [Before/After variation]

  TH1D* meanRjg[7];
  TH1D* meanRjgSys[7];
  
  TFile * f = new TFile("../resultHistograms_ppSmeared10030.root");
  meanJetPt[1]  =(TH1D*)f->Get(Form("meanJetPt_pp"));
  meanXjg[1]    =(TH1D*)f->Get(Form("meanXjg_pp"));
  meanRjg[1]  =(TH1D*)f->Get(Form("meanRjg_pp"));
  for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
    dNdJetPt[1][ipt] = (TH1D*)f->Get(Form("dNdJetPt_pp_ptBin%d", ipt ));
    dNdXjg[1][ipt] = (TH1D*)f->Get(Form("dNdXjg_pp_ptBin%d", ipt ));
    Iaa[1][ipt] = (TH1D*)f->Get(Form("dNdJetPt_forIaa_pp_ptBin%dAndHigher", ipt ));
  }  

  f   = new TFile("../resultHistograms_ppSmeared13099.root");
  meanJetPt[2]  =(TH1D*)f->Get(Form("meanJetPt_pp"));
  meanXjg[2]    =(TH1D*)f->Get(Form("meanXjg_pp"));
  meanRjg[2]  =(TH1D*)f->Get(Form("meanRjg_pp"));
  for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
    dNdJetPt[2][ipt] = (TH1D*)f->Get(Form("dNdJetPt_pp_ptBin%d", ipt ));
    dNdXjg[2][ipt] = (TH1D*)f->Get(Form("dNdXjg_pp_ptBin%d", ipt ));
    Iaa[2][ipt] = (TH1D*)f->Get(Form("dNdJetPt_forIaa_pp_ptBin%dAndHigher", ipt ));
  }  
  
  // pbpb
  f =   new TFile("../resultHistograms_jetResCorrection.root");
  meanJetPt[3]  =(TH1D*)f->Get(Form("meanJetPt_pbpb_centralityBin1"));
  meanXjg[3]  =(TH1D*)f->Get(Form("meanXjg_pbpb_centralityBin1"));
  meanRjg[3]  =(TH1D*)f->Get(Form("meanRjg_pbpb_centralityBin1"));
  for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
    dNdJetPt[3][ipt] = (TH1D*)f->Get(Form("dNdJetPt_pbpb_centralityBin1_ptBin%d", ipt ));
    dNdXjg[3][ipt] = (TH1D*)f->Get(Form("dNdXjg_pbpb_centralityBin1_ptBin%d", ipt ));
    Iaa[3][ipt] = (TH1D*)f->Get(Form("dNdJetPt_forIaa_pbpb_centralityBin1_ptBin%dAndHigher", ipt ));
  }
  meanJetPt[4]  =(TH1D*)f->Get(Form("meanJetPt_pbpb_centralityBin2"));
  meanXjg[4]  =(TH1D*)f->Get(Form("meanXjg_pbpb_centralityBin2"));
  meanRjg[4]  =(TH1D*)f->Get(Form("meanRjg_pbpb_centralityBin2"));
  for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
    dNdJetPt[4][ipt] = (TH1D*)f->Get(Form("dNdJetPt_pbpb_centralityBin2_ptBin%d", ipt ));
    dNdXjg[4][ipt] = (TH1D*)f->Get(Form("dNdXjg_pbpb_centralityBin2_ptBin%d", ipt ));
    Iaa[4][ipt] = (TH1D*)f->Get(Form("dNdJetPt_forIaa_pbpb_centralityBin2_ptBin%dAndHigher", ipt ));
  }
  // pPb
  f =   new TFile("../resultHistograms_jetResCorrection.root");
  meanJetPt[5]  =(TH1D*)f->Get(Form("meanJetPt_ppb"));
  meanXjg[5]  =(TH1D*)f->Get(Form("meanXjg_ppb"));
  meanRjg[5]  =(TH1D*)f->Get(Form("meanRjg_ppb"));
  for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
    dNdJetPt[5][ipt] = (TH1D*)f->Get(Form("dNdJetPt_ppb_ptBin%d", ipt ));
    dNdXjg[5][ipt] = (TH1D*)f->Get(Form("dNdXjg_ppb_ptBin%d", ipt ));
    }
  
  f =   new TFile("../resultHistograms_MC_recoIsoPhoton.root");
  meanJetPt[6]  =(TH1D*)f->Get(Form("meanJetPt_ppb"));
  meanXjg[6]  =(TH1D*)f->Get(Form("meanXjg_ppb"));
  meanRjg[6]  =(TH1D*)f->Get(Form("meanRjg_ppb"));
  for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
    dNdJetPt[6][ipt] = (TH1D*)f->Get(Form("dNdJetPt_ppb_ptBin%d", ipt ));
    dNdXjg[6][ipt] = (TH1D*)f->Get(Form("dNdXjg_ppb_ptBin%d", ipt ));
  }  
  
  
  TFile* fSys = new TFile("../merged/relativeSys_merged.root");
  
  meanJetPtSys[1]  =(TH1D*)fSys->Get("meanJetPt_pp_uncertainty_merged");
  meanRjgSys[1]  =(TH1D*)fSys->Get(Form("meanRjg_pp_uncertainty_merged"));
  meanXjgSys[1]  =(TH1D*)fSys->Get(Form("meanXjg_pp_uncertainty_merged"));
  for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
    dNdJetPtSysIaa[1][ipt] = (TH1D*)fSys->Get(Form("dNdJetPt_IaaBin_pp_ptBin%d_uncertainty_merged",  ipt ));
    dNdXjgSys[1][ipt] = (TH1D*)fSys->Get(Form("dNdXjg_pp_ptBin%d_uncertainty_merged",  ipt ));
    IaaSys[1][ipt] = (TH1D*)fSys->Get(Form("dNdJetPt_forIaa_pp_ptBin%dAndHigher_uncertainty_merged",  ipt ));
  }
  meanJetPtSys[2] = (TH1D*)meanJetPtSys[1]->Clone(Form("%s_2",meanJetPtSys[1]->GetName()));
  meanRjgSys[2] = (TH1D*)meanRjgSys[1]->Clone(Form("%s_2",meanRjgSys[1]->GetName()));
  meanXjgSys[2] = (TH1D*)meanXjgSys[1]->Clone(Form("%s_2",meanXjgSys[1]->GetName()));
  for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
    dNdJetPtSysIaa[2][ipt] = (TH1D*)dNdJetPtSysIaa[1][ipt]->Clone(Form("%s_2",dNdJetPtSysIaa[1][ipt]->GetName()));
    dNdXjgSys[2][ipt] = (TH1D*)dNdXjgSys[1][ipt]->Clone(Form("%s_2",dNdXjgSys[1][ipt]->GetName()));
    IaaSys[2][ipt] = (TH1D*)IaaSys[1][ipt]->Clone(Form("%s_2",IaaSys[1][ipt]->GetName()));
  }
  meanJetPtSys[3]  =(TH1D*)fSys->Get("meanJetPt_pbpb_centralityBin1_uncertainty_merged");
  meanXjgSys[3]  =(TH1D*)fSys->Get(Form("meanXjg_pbpb_centralityBin1_uncertainty_merged"));
  meanRjgSys[3]  =(TH1D*)fSys->Get(Form("meanRjg_pbpb_centralityBin1_uncertainty_merged"));
  for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
    dNdJetPtSysIaa[3][ipt] = (TH1D*)fSys->Get(Form("dNdJetPt_IaaBin_pbpb_centralityBin1_ptBin%d_uncertainty_merged",  ipt ));
    dNdXjgSys[3][ipt] = (TH1D*)fSys->Get(Form("dNdXjg_pbpb_centralityBin1_ptBin%d_uncertainty_merged",  ipt ));
    IaaSys[3][ipt] = (TH1D*)fSys->Get(Form("dNdJetPt_forIaa_pbpb_centralityBin1_ptBin%dAndHigher_uncertainty_merged",  ipt ));
  }
  meanJetPtSys[4]  =(TH1D*)fSys->Get("meanJetPt_pbpb_centralityBin2_uncertainty_merged");
  meanXjgSys[4]  =(TH1D*)fSys->Get(Form("meanXjg_pbpb_centralityBin2_uncertainty_merged"));
  meanRjgSys[4]  =(TH1D*)fSys->Get(Form("meanRjg_pbpb_centralityBin2_uncertainty_merged"));
  for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
    dNdJetPtSysIaa[4][ipt] = (TH1D*)fSys->Get(Form("dNdJetPt_IaaBin_pbpb_centralityBin2_ptBin%d_uncertainty_merged",  ipt ));
    dNdXjgSys     [4][ipt] = (TH1D*)fSys->Get(Form("dNdXjg_pbpb_centralityBin2_ptBin%d_uncertainty_merged",  ipt ));
    IaaSys[4][ipt]         = (TH1D*)fSys->Get(Form("dNdJetPt_forIaa_pbpb_centralityBin2_ptBin%dAndHigher_uncertainty_merged",  ipt ));
  }
  meanJetPtSys[5]  =(TH1D*)fSys->Get("meanJetPt_ppb_uncertainty_merged");
  meanXjgSys[5]  =(TH1D*)fSys->Get(Form("meanXjg_ppb_uncertainty_merged"));
  meanRjgSys[5]  =(TH1D*)fSys->Get(Form("meanRjg_ppb_uncertainty_merged"));
  for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
    dNdJetPtSysIaa[5][ipt] = (TH1D*)fSys->Get(Form("dNdJetPt_IaaBin_ppb_ptBin%d_uncertainty_merged",  ipt ));
    dNdXjgSys     [5][ipt] = (TH1D*)fSys->Get(Form("dNdXjg_ppb_ptBin%d_uncertainty_merged",  ipt ));
  }
  
  
  // transplant the uncertainty  
  for ( int coll = 1 ; coll<=5 ; coll++) {
    for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
      dNdJetPtSys[coll][ipt] = (TH1D*) dNdJetPt[coll][ipt]->Clone(Form("dNdJetPtSys_coll%d_ipt%d",coll,ipt));
      dNdJetPtSys[coll][ipt]->Reset();
      for ( int ibin = 1 ; ibin<= dNdJetPtSys[coll][ipt]->GetNbinsX() ; ibin++) {
	float xx = dNdJetPtSys[coll][ipt]->GetBinCenter(ibin);
	float yy = dNdJetPtSysIaa[coll][ipt]->GetBinContent ( dNdJetPtSysIaa[coll][ipt]->FindBin(xx) );
	if ( yy>1 ) yy = 1;
	dNdJetPtSys[coll][ipt]->SetBinContent(ibin,yy);
	
      }
    }
  }
  
  //  Limit the uncertainty up to 1 
  for ( int coll = 1 ; coll<=5 ; coll++) {
    for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
      for ( int ibin = 1 ; ibin<= dNdXjgSys[coll][ipt]->GetNbinsX() ; ibin++) {
	float yy = dNdXjgSys[coll][ipt]->GetBinContent ( ibin) ;
	if ( yy>1 ) yy = 1;
	dNdXjgSys[coll][ipt]->SetBinContent(ibin,yy);
      }
    }
  }
  // IaaSys
  for ( int coll = 1 ; coll<=4 ; coll++) {
    for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
      for ( int ibin = 1 ; ibin<= IaaSys[coll][ipt]->GetNbinsX() ; ibin++) {
	float yy = IaaSys[coll][ipt]->GetBinContent ( ibin) ;
	if ( yy>1 ) yy = 1;
	IaaSys[coll][ipt]->SetBinContent(ibin,yy);
      }
    }
  }
  

  
  
  // RJG!!
  TCanvas* c2 = new TCanvas("c1","",1000,500);
  c2->Divide(2,1);
  c2->cd(2);
  handsomeTH1(meanRjg[1],1,1,21);
  //  drawSys(TH1 *h,TH1 *sys, Int_t theColor= kYellow, Int_t fillStyle = -1, Int_t lineStyle = -1)
  TH1D* tempR = new TH1D("tempR",";p_{T}^{#gamma};R_{j#gamma}",100,40,130);
  tempR->Reset();  
  handsomeTH1(tempR,0);
  tempR->SetAxisRange(0,1.2,"Y");
  tempR->Draw();
  drawSys(meanRjg[1], meanRjgSys[1], kGreen);
  drawSys(meanRjg[3], meanRjgSys[3]);
  meanRjg[1]->Draw("same");
  handsomeTH1(meanRjg[3],2 );
  meanRjg[3]->Draw("same");
  if ( 1==1 ){ 
    TLegend *ly = new  TLegend(0.4937249,0.262193,0.8493139,0.4740574,NULL,"brNDC");    
    easyLeg(ly,"2.76TeV");
    ly->AddEntry(meanRjg[3],"PbPb 0-30%","p");
    ly->AddEntry(meanRjg[1],"pp (smeared)","p");
    ly->Draw();
  }


  c2->cd(1);
  tempR->Draw();
  drawSys(meanRjg[2], meanRjgSys[2], kGreen);
  drawSys(meanRjg[4], meanRjgSys[4]);
  meanRjg[2]->SetMarkerStyle(25);
  meanRjg[2]->Draw("same");
  handsomeTH1(meanRjg[4],2 );
  meanRjg[4]->SetMarkerStyle(24);
  meanRjg[4]->Draw("same");
  if ( 1==1 ){ 
    TLegend *ly = new  TLegend(0.4937249,0.262193,0.8493139,0.4740574,NULL,"brNDC");    
    easyLeg(ly,"2.76TeV");
    ly->AddEntry(meanRjg[4],"PbPb 30-100%","p");
    ly->AddEntry(meanRjg[2],"pp (smeared)","p");
    ly->Draw();
  }
  c2->SaveAs("pT_depedence_rjg_pp_pbpb.pdf");

  
  TCanvas* c2pa = new TCanvas("c1pa","",500,500);
  handsomeTH1(meanRjg[1],1);
  //  drawSys(TH1 *h,TH1 *sys, Int_t theColor= kYellow, Int_t fillStyle = -1, Int_t lineStyle = -1)                         
  //  tempR->Draw();
  TH1D* tempJ = new TH1D("tempJ",";p_{T}^{#gamma}; <p_{T}^{Jet}>",100,40,130);
  tempJ->Reset();
  handsomeTH1(tempJ,0);
  tempJ->SetAxisRange(0,100,"Y");
  tempJ->Draw();
  drawSys(meanJetPt[5], meanJetPtSys[5], kYellow);
  handsomeTH1(meanJetPt[5],2);
  handsomeTH1(meanJetPt[6],1);
  meanJetPt[5]->Draw("same");
  meanJetPt[6]->Draw("same");
  if ( 1==1 ) {
    TLegend *ly = new TLegend(0.4484643,0.3088445,0.9140673,0.50102941,NULL,"brNDC");
    easyLeg(ly,"5.02TeV pPb");
    ly->AddEntry(meanJetPt[5],"DATA","p");
    ly->AddEntry(meanJetPt[6],"PYTHIA+HIJING","p");
    ly->Draw();
  }
  c2pa->SaveAs("pT_dependence_rjg_pA_figure1.pdf");

  TCanvas* c3pa = new TCanvas("c3pa","",500,500);
  tempR->Draw();
  drawSys(meanRjg[5], meanRjgSys[5], kYellow);
  handsomeTH1(meanRjg[5],2);
  handsomeTH1(meanRjg[6],1);
  meanRjg[5]->Draw("same");
  meanRjg[6]->Draw("same");
  if ( 1==1 ) {
    TLegend *ly = new TLegend(0.4484643,0.3088445,0.9140673,0.50102941,NULL,"brNDC");
    easyLeg(ly,"5.02TeV pPb");
    ly->AddEntry(meanRjg[5],"DATA","p");
    ly->AddEntry(meanRjg[6],"PYTHIA+HIJING","p");
    ly->Draw();
  }  
  c3pa->SaveAs("pT_dependence_jetPt_pA_figure2.pdf");

  TCanvas* c3 = new TCanvas("c3","",1000,500);
  c3->Divide(2,1);
  c3->cd(2);
  handsomeTH1(meanJetPt[1],1,1,21);
  //  drawSys(TH1 *h,TH1 *sys, Int_t theColor= kYellow, Int_t fillStyle = -1, Int_t lineStyle = -1)                                                       
   tempJ->Draw();
  drawSys(meanJetPt[1], meanJetPtSys[1], kGreen);
  drawSys(meanJetPt[3], meanJetPtSys[3]);
  meanJetPt[1]->Draw("same");
  handsomeTH1(meanJetPt[3],2 );
  meanJetPt[3]->Draw("same");
  if ( 1==1 ){
    TLegend *ly = new  TLegend(0.4937249,0.262193,0.8493139,0.4740574,NULL,"brNDC");
    easyLeg(ly,"2.76TeV");
    ly->AddEntry(meanJetPt[3],"PbPb 0-30%","p");
    ly->AddEntry(meanJetPt[1],"pp (smeared)","p");
    ly->Draw();
  }
  
  c3->cd(1);
  tempJ->Draw();
  drawSys(meanJetPt[2], meanJetPtSys[2], kGreen);
  drawSys(meanJetPt[4], meanJetPtSys[4]);
  meanJetPt[2]->SetMarkerStyle(25);
  meanJetPt[2]->Draw("same");
  handsomeTH1(meanJetPt[4],2 );
  meanJetPt[4]->SetMarkerStyle(24);
  meanJetPt[4]->Draw("same");
  if ( 1==1 ){
    TLegend *ly = new  TLegend(0.4937249,0.262193,0.8493139,0.4740574,NULL,"brNDC");
    easyLeg(ly,"2.76TeV");
    ly->AddEntry(meanJetPt[4],"PbPb 30-100%","p");
    ly->AddEntry(meanJetPt[2],"pp (smeared)","p");
    ly->Draw();
  }
  c3->SaveAs("pT_dependence_jetPt_pp_pbpb.pdf");
  
  TH1D* hTempPt = new TH1D("hTemp",";p_{T}^{#gamma} (GeV);",200,10,300);
  TCanvas* c5 = new TCanvas("c5","",1200,700);
  makeMultiPanelCanvas(c5,nPtBin,2,0.0,0.0,0.2,0.15,0.02);
  for ( int ipt = 1 ; ipt<=nPtBin  ; ipt++) {
    c5->cd(ipt+nPtBin);
    // draw pp                                                                                                                                           
    hTempPt->SetXTitle("p_{T}^{Jet} (GeV)");
    hTempPt->SetYTitle("#frac{dN}{dp_{T}} #frac{1}{N}");
    hTempPt->SetAxisRange(10,150,"X");
    //        hTempPt->SetAxisRange(0,0.025,"Y");                                                                                                        
    hTempPt->SetAxisRange(0,0.07,"Y");
    handsomeTH1(hTempPt,0);
    hTempPt->DrawCopy();

    drawSys(dNdJetPt[1][ipt], dNdJetPtSys[1][ipt], kGreen);
    drawSys(dNdJetPt[3][ipt], dNdJetPtSys[3][ipt], kYellow);
    handsomeTH1(dNdJetPt[3][ipt],2);
    dNdJetPt[1][ipt]->Draw("same");
    dNdJetPt[1][ipt]->SetMarkerStyle(21);
    dNdJetPt[3][ipt]->Draw("same");
    if ( ipt == 1 ) {
      TLegend *ly = new TLegend(0.4484643,0.6988445,0.9140673,0.9102941,NULL,"brNDC");
      easyLeg(ly,"2.76TeV");
      ly->AddEntry(meanJetPt[3],"PbPb 0-30%","p");
      ly->AddEntry(meanJetPt[1],"pp (smeared)","p");
      ly->Draw();
    }
 

    c5->cd(ipt);
    hTempPt->DrawCopy();

    drawSys(dNdJetPt[2][ipt], dNdJetPtSys[2][ipt], kGreen);
    drawSys(dNdJetPt[4][ipt], dNdJetPtSys[4][ipt], kYellow);
    handsomeTH1(dNdJetPt[4][ipt],2);
    dNdJetPt[4][ipt]->SetMarkerStyle(24);
    dNdJetPt[2][ipt]->SetMarkerStyle(25);
    dNdJetPt[2][ipt]->Draw("same");
    dNdJetPt[4][ipt]->Draw("same");
    if ( ipt==1 ){
      TLegend *ly = new TLegend(0.4484643,0.5088445,0.9140673,0.75102941,NULL,"brNDC");
      easyLeg(ly,"2.76TeV");
      ly->AddEntry(meanJetPt[4],"PbPb 30-100%","p");
      ly->AddEntry(meanJetPt[2],"pp (smeared)","p");
      ly->Draw();
    }

    double dx1=0.15;
    if ( ipt == nPtBin )
      drawText(Form("p_{T}^{#gamma} > %dGeV, ", (int)ptBin[ipt-1]), 0.12+dx1+0.25,0.85,1,15);//yeonju 130823                                           
    else
      drawText(Form("%dGeV < p_{T}^{#gamma} < %dGeV, ", (int)ptBin[ipt-1], (int)ptBin[ipt]), 0.12+dx1,0.85,1,15);//yeonju 130823                       

    
  }
  c5->SaveAs("pT_dependence_jetPt_pp_pbpb_distribution.pdf");

  TCanvas* c5pa = new TCanvas("c5pa","",1200,350);
  makeMultiPanelCanvas(c5pa,nPtBin,1,0.0,0.0,0.2,0.15,0.02);
  for ( int ipt = 1 ; ipt<=nPtBin  ; ipt++) {
    c5pa->cd(ipt);
    // draw pp                                                                                                                                           
    hTempPt->SetXTitle("p_{T}^{Jet} (GeV)");
    hTempPt->SetYTitle("#frac{dN}{dp_{T}} #frac{1}{N}");
    hTempPt->SetAxisRange(10,150,"X");
    //        hTempPt->SetAxisRange(0,0.025,"Y");                                                                                                        
    hTempPt->SetAxisRange(0,0.07,"Y");
    handsomeTH1(hTempPt,0);
    hTempPt->DrawCopy();

    drawSys(dNdJetPt[5][ipt], dNdJetPtSys[5][ipt], kYellow);
    handsomeTH1(dNdJetPt[5][ipt],2);
    dNdJetPt[6][ipt]->Draw("same");
    dNdJetPt[5][ipt]->Draw("same");
    if ( ipt == 1 ) {
      TLegend *ly = new TLegend(0.4855983,0.5529059,0.9512013,0.7645899,NULL,"brNDC");
      easyLeg(ly,"5.02TeV pPb");
      ly->AddEntry(meanJetPt[5],"Data","p");
      ly->AddEntry(meanJetPt[6],"PYTHIA+HIJING","p");
      ly->Draw();
    }
    double dx1=0.15;
    if ( ipt == nPtBin )
      drawText(Form("p_{T}^{#gamma} > %dGeV, ", (int)ptBin[ipt-1]), 0.12+dx1+0.25,0.85,1,15);//yeonju 130823                                           
    else
      drawText(Form("%dGeV < p_{T}^{#gamma} < %dGeV, ", (int)ptBin[ipt-1], (int)ptBin[ipt]), 0.12+dx1,0.85,1,15);//yeonju 130823                       
    
    
  }
  c5pa->SaveAs("pT_dependence_jetPt_pA_distribution.pdf");
  


  // XJG plots
  TH1D* hTempXjg = new TH1D("hTempXjg",";p_{T}^{#gamma} (GeV);",200,0,2);
  TCanvas* c6 = new TCanvas("c6","",1200,700);
  makeMultiPanelCanvas(c6,nPtBin,2,0.0,0.0,0.2,0.15,0.02);
  for ( int ipt = 1 ; ipt<=nPtBin  ; ipt++) {
    c6->cd(ipt+nPtBin);
    // draw pp                                                                                                                                           
    hTempXjg->SetXTitle("x_{j#gamma}");
    hTempXjg->SetYTitle("#frac{dN}{dx} #frac{1}{N}");
    hTempXjg->SetAxisRange(0,2,"X");
    //        hTempXjg->SetAxisRange(0,0.025,"Y");                                                                                                        
    hTempXjg->SetAxisRange(-.2,3,"Y");
    handsomeTH1(hTempXjg,0);
    hTempXjg->DrawCopy();
    onSun(0,0,2,0);
    drawSys(dNdXjg[3][ipt], dNdXjgSys[3][ipt], kYellow);
    drawSys(dNdXjg[1][ipt], dNdXjgSys[1][ipt], kGreen,3001);
    handsomeTH1(dNdXjg[3][ipt],2);
    dNdXjg[1][ipt]->Draw("same");
    dNdXjg[1][ipt]->SetMarkerStyle(21);
    dNdXjg[3][ipt]->Draw("same");
    if ( ipt == 1 ) {
      TLegend *ly = new TLegend(0.651273,0.7052521,0.9997611,0.9487395,NULL,"brNDC");
      easyLeg(ly,"2.76TeV");
      ly->AddEntry(meanJetPt[3],"PbPb 0-30%","p");
      ly->AddEntry(meanJetPt[1],"pp (smeared)","p");
      ly->Draw();
    }
 

    c6->cd(ipt);
    hTempXjg->DrawCopy();
    onSun(0,0,2,0);

    drawSys(dNdXjg[4][ipt], dNdXjgSys[4][ipt], kYellow);
    drawSys(dNdXjg[2][ipt], dNdXjgSys[2][ipt], kGreen,3001);
    handsomeTH1(dNdXjg[4][ipt],2);
    dNdXjg[4][ipt]->SetMarkerStyle(24);
    dNdXjg[2][ipt]->SetMarkerStyle(25);
    dNdXjg[2][ipt]->Draw("same");
    dNdXjg[4][ipt]->Draw("same");
    if ( ipt==1 ){
      TLegend *ly = new TLegend(0.651273,0.7052521,0.9997611,0.9487395,NULL,"brNDC");
      easyLeg(ly,"2.76TeV");
      ly->AddEntry(meanJetPt[4],"PbPb 30-100%","p");
      ly->AddEntry(meanJetPt[2],"pp (smeared)","p");
      ly->Draw();
    }

    double dx1=0.15;
    if ( ipt == nPtBin )
      drawText(Form("p_{T}^{#gamma} > %dGeV, ", (int)ptBin[ipt-1]), 0.12+dx1+0.25,0.85,1,15);//yeonju 130823                                           
    else
      drawText(Form("%dGeV < p_{T}^{#gamma} < %dGeV, ", (int)ptBin[ipt-1], (int)ptBin[ipt]), 0.12+dx1,0.85,1,15);//yeonju 130823                       
    
  }
  c6->SaveAs("pT_dependence_xjg_pp_pbpb_distribution.pdf");


  TCanvas* c6pa = new TCanvas("c6pa","",1200,350);
  makeMultiPanelCanvas(c6pa,nPtBin,1,0.0,0.0,0.2,0.15,0.02);
  for ( int ipt = 1 ; ipt<=nPtBin  ; ipt++) {
    c6pa->cd(ipt);
    // draw pp                                                                                                                                           
    hTempXjg->DrawCopy();
   onSun(0,0,2,0);

    drawSys(dNdXjg[5][ipt], dNdXjgSys[5][ipt], kYellow);
    handsomeTH1(dNdXjg[5][ipt],2);
    dNdXjg[6][ipt]->Draw("same");
    dNdXjg[5][ipt]->Draw("same");
    if ( ipt == 1 ) {
      TLegend *ly = new TLegend(0.614139,0.6919223,0.9997611,0.9036063,NULL,"brNDC");
      easyLeg(ly,"5.02TeV pPb");
      ly->AddEntry(meanJetPt[5],"Data","p");
      ly->AddEntry(meanJetPt[6],"PYTHIA+HIJING","p");
      ly->Draw();
    }
    double dx1=0.15;
    if ( ipt == nPtBin )
      drawText(Form("p_{T}^{#gamma} > %dGeV ", (int)ptBin[ipt-1]), 0.12+dx1+0.25,0.9,1,15);          
    else
      drawText(Form("%dGeV < p_{T}^{#gamma} < %dGeV ", (int)ptBin[ipt-1], (int)ptBin[ipt]), 0.12+dx1,0.9,1,15);//yeonju 130823                       
    
    
  }
  c6pa->SaveAs("pT_dependence_xjg_pA_distribution.pdf");
  

  

  // mean xjg
  TCanvas* c7 = new TCanvas("c7","",1000,500);
  c7->Divide(2,1);
  c7->cd(2);
  handsomeTH1(meanXjg[1],1,1,24);
  //  drawSys(TH1 *h,TH1 *sys, Int_t theColor= kYellow, Int_t fillStyle = -1, Int_t lineStyle = -1)
  TH1D* tempX = new TH1D("tempX",";p_{T}^{#gamma};<X_{j#gamma}>;",100,40,130);
  tempX->Reset();  
  handsomeTH1(tempX,0);
  tempX->SetAxisRange(0.6,1.2,"Y");
  tempX->Draw();
  drawSys(meanXjg[3], meanXjgSys[3]);
  drawSys(meanXjg[1], meanXjgSys[1], kGreen,3001);
  meanXjg[1]->SetMarkerStyle(21);
  meanXjg[1]->Draw("same");
  handsomeTH1(meanXjg[3],2 );
  meanXjg[3]->Draw("same");
  if ( 1==1 ){ 
    TLegend *ly = new TLegend(0.4769913,0.6383604,0.8325803,0.8502248,NULL,"brNDC");
    easyLeg(ly,"2.76TeV");
    ly->AddEntry(meanXjg[3],"PbPb 0-30%","p");
    ly->AddEntry(meanXjg[1],"pp (smeared)","p");
    ly->Draw();
  }


  c7->cd(1);
  tempX->Draw();
  drawSys(meanXjg[4], meanXjgSys[4]);
  drawSys(meanXjg[2], meanXjgSys[2], kGreen,3001);
  meanXjg[2]->SetMarkerStyle(25);
  meanXjg[2]->Draw("same");
  handsomeTH1(meanXjg[4],2 );
  meanXjg[4]->SetMarkerStyle(24);
  meanXjg[4]->Draw("same");
  if ( 1==1 ){ 
    TLegend *ly = new TLegend(0.4769913,0.6383604,0.8325803,0.8502248,NULL,"brNDC");
    easyLeg(ly,"2.76TeV");
    ly->AddEntry(meanXjg[4],"PbPb 30-100%","p");
    ly->AddEntry(meanXjg[2],"pp (smeared)","p");
    ly->Draw();
  }
  c7->SaveAs("pT_depedence_meanXjg_pp_pbpb.pdf");


  TCanvas* c7pa = new TCanvas("c7pa","",500,500);
  tempX->Draw();
  drawSys(meanXjg[5], meanXjgSys[5], kYellow);
  handsomeTH1(meanXjg[5],2);
  handsomeTH1(meanXjg[6],1);
  meanXjg[5]->Draw("same");
  meanXjg[6]->Draw("same");
  if ( 1==1 ) {
    TLegend *ly = new TLegend(0.4484643,0.6088445,0.9140673,0.80102941,NULL,"brNDC");
    easyLeg(ly,"5.02TeV pPb");
    ly->AddEntry(meanXjg[5],"DATA","p");
    ly->AddEntry(meanXjg[6],"PYTHIA+HIJING","p");
    ly->Draw();
  }  
  c7pa->SaveAs("pT_dependence_xjg_pA_figure2.pdf");



  TCanvas* c8 = new TCanvas("c8","",1200,700);
  makeMultiPanelCanvas(c8,nPtBin,2,0.0,0.0,0.2,0.15,0.02);
  for ( int ipt = 1 ; ipt<=nPtBin  ; ipt++) {
    c8->cd(ipt+nPtBin);
    // draw pp                                                                                                                                           
    hTempPt->SetXTitle("p_{T}^{Jet} (GeV)");
    hTempPt->SetYTitle("#frac{dN}{dp_{T}} #frac{1}{N}");
    hTempPt->SetAxisRange(10,150,"X");
    //        hTempPt->SetAxisRange(0,0.025,"Y");                                                                                                        
    hTempPt->SetAxisRange(0,0.035,"Y");
    handsomeTH1(hTempPt,0);
    hTempPt->DrawCopy();


    drawSys(Iaa[3][ipt], IaaSys[3][ipt], kYellow);
    drawSys(Iaa[1][ipt], IaaSys[1][ipt], kGreen,3001);
    handsomeTH1(Iaa[3][ipt],2);
    Iaa[1][ipt]->Draw("same");
    Iaa[1][ipt]->SetMarkerStyle(21);
    Iaa[3][ipt]->Draw("same");
    if ( ipt == 1 ) {
      TLegend *ly = new TLegend(0.4484643,0.6988445,0.9140673,0.9102941,NULL,"brNDC");
      easyLeg(ly,"2.76TeV");
      ly->AddEntry(meanJetPt[3],"PbPb 0-30%","p");
      ly->AddEntry(meanJetPt[1],"pp (smeared)","p");
      ly->Draw();
    }
 

    c8->cd(ipt);
    hTempPt->DrawCopy();

    drawSys(Iaa[4][ipt], IaaSys[4][ipt], kYellow);
    drawSys(Iaa[2][ipt], IaaSys[2][ipt], kGreen,3001);
    handsomeTH1(Iaa[4][ipt],2);
    Iaa[4][ipt]->SetMarkerStyle(24);
    Iaa[2][ipt]->SetMarkerStyle(25);
    Iaa[2][ipt]->Draw("same");
    Iaa[4][ipt]->Draw("same");
    if ( ipt==1 ){
      TLegend *ly = new TLegend(0.4484643,0.5088445,0.9140673,0.75102941,NULL,"brNDC");
      easyLeg(ly,"2.76TeV");
      ly->AddEntry(meanJetPt[4],"PbPb 30-100%","p");
      ly->AddEntry(meanJetPt[2],"pp (smeared)","p");
      ly->Draw();
    }

    double dx1=0.15;
    if ( ipt == nPtBin )
      drawText(Form("p_{T}^{#gamma} > %dGeV, ", (int)ptBin[ipt-1]), 0.12+dx1+0.25,0.85,1,15);//yeonju 130823                                           
    else
      drawText(Form("%dGeV < p_{T}^{#gamma} < %dGeV, ", (int)ptBin[ipt-1], (int)ptBin[ipt]), 0.12+dx1,0.85,1,15);//yeonju 130823                       

    
  }
  c8->SaveAs("pT_dependence_iAA_pp_pbpb_distribution.pdf");

}
