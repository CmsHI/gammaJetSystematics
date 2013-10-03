#include "../commonUtilitySys.h"
#include <TRandom3.h>
#include <Tfile.h>

void drawSys_merged() {
  const int kPPcentral = 1;
  const int kPPperipheral =2 ;
  const int kHIcentral =  3;
  const int kHIperipheral = 4;
  const int kPADATA = 5;
  const int kPAMC = 6;
  const int nPtBin = 4;  
  double ptBin[nPtBin+1] = {40, 50,60,80,9999};

  TH1D* dNdJetPt[7][5]; // [collision] [ ptbin]  [Before/After variation]
  TH1D* dNdJetPtSys[7][5]; // [collision] [ ptbin]  [Before/After variation]
  TH1D* dNdJetPtSysIaa[7][5]; // [collision] [ ptbin]  [Before/After variation]
  TH1D* meanJetPt[7];   // [collision] [Before/After variation]
  TH1D* meanJetPtSys[7];   // [collision] [Before/After variation]

  TH1D* meanRjg[7];
  TH1D* meanRjgSys[7];
  
  TFile * f = new TFile("../resultHistograms_ppSmeared10030.root");
  meanJetPt[1]  =(TH1D*)f->Get(Form("meanJetPt_pp"));
  meanRjg[1]  =(TH1D*)f->Get(Form("meanRjg_pp"));
  for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
    dNdJetPt[1][ipt] = (TH1D*)f->Get(Form("dNdJetPt_pp_ptBin%d", ipt ));
  }  

  f   = new TFile("../resultHistograms_ppSmeared13099.root");
  meanJetPt[2]  =(TH1D*)f->Get(Form("meanJetPt_pp"));
  meanRjg[2]  =(TH1D*)f->Get(Form("meanRjg_pp"));
  for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
    dNdJetPt[2][ipt] = (TH1D*)f->Get(Form("dNdJetPt_pp_ptBin%d", ipt ));
  }  
  
  // pbpb
  f =   new TFile("../resultHistograms_jetResCorrection.root");
  meanJetPt[3]  =(TH1D*)f->Get(Form("meanJetPt_pbpb_centralityBin1"));
  meanRjg[3]  =(TH1D*)f->Get(Form("meanRjg_pbpb_centralityBin1"));
  for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
    dNdJetPt[3][ipt] = (TH1D*)f->Get(Form("dNdJetPt_pbpb_centralityBin1_ptBin%d", ipt ));
  }
  meanJetPt[4]  =(TH1D*)f->Get(Form("meanJetPt_pbpb_centralityBin2"));
  meanRjg[4]  =(TH1D*)f->Get(Form("meanRjg_pbpb_centralityBin2"));
  for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
    dNdJetPt[4][ipt] = (TH1D*)f->Get(Form("dNdJetPt_pbpb_centralityBin2_ptBin%d", ipt ));
  }
  
  TFile* fSys = new TFile("../merged/relativeSys_merged.root");
  
  meanJetPtSys[1]  =(TH1D*)fSys->Get("meanJetPt_pp_uncertainty_merged");
  meanRjgSys[1]  =(TH1D*)fSys->Get(Form("meanRjg_pp_uncertainty_merged"));
  for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
    dNdJetPtSysIaa[1][ipt] = (TH1D*)fSys->Get(Form("dNdJetPt_IaaBin_pp_ptBin%d_uncertainty_merged",  ipt ));
  }
  meanJetPtSys[2] = (TH1D*)meanJetPtSys[1]->Clone(Form("%s_2",meanJetPtSys[1]->GetName()));
  meanRjgSys[2] = (TH1D*)meanRjgSys[1]->Clone(Form("%s_2",meanRjgSys[1]->GetName()));
  for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
    dNdJetPtSysIaa[2][ipt] = (TH1D*)dNdJetPtSysIaa[1][ipt]->Clone(Form("%s_2",dNdJetPtSysIaa[1][ipt]->GetName()));
  }
  meanJetPtSys[3]  =(TH1D*)fSys->Get("meanJetPt_pbpb_centralityBin1_uncertainty_merged");
  meanRjgSys[3]  =(TH1D*)fSys->Get(Form("meanRjg_pbpb_centralityBin1_uncertainty_merged"));
  for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
    dNdJetPtSysIaa[3][ipt] = (TH1D*)fSys->Get(Form("dNdJetPt_IaaBin_pbpb_centralityBin1_ptBin%d_uncertainty_merged",  ipt ));
  }
  meanJetPtSys[4]  =(TH1D*)fSys->Get("meanJetPt_pbpb_centralityBin2_uncertainty_merged");
  meanRjgSys[4]  =(TH1D*)fSys->Get(Form("meanRjg_pbpb_centralityBin2_uncertainty_merged"));
  for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
    dNdJetPtSysIaa[4][ipt] = (TH1D*)fSys->Get(Form("dNdJetPt_IaaBin_pbpb_centralityBin2_ptBin%d_uncertainty_merged",  ipt ));
  }
  
  // transplant the uncertainty  
  for ( int coll = 1 ; coll<=4 ; coll++) {
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
  

  
  // RJG!!
  TCanvas* c2 = new TCanvas("c1","",1000,500);
  c2->Divide(2,1);
  c2->cd(2);
  handsomeTH1(meanRjg[1],1);
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

  
  TCanvas* c3 = new TCanvas("c3","",1000,500);
  c3->Divide(2,1);
  c3->cd(2);
  handsomeTH1(meanJetPt[1],1);
  //  drawSys(TH1 *h,TH1 *sys, Int_t theColor= kYellow, Int_t fillStyle = -1, Int_t lineStyle = -1)                                                       
  TH1D* tempJ = new TH1D("tempJ",";p_{T}^{#gamma}; <p_T{Jet}>",100,40,130);
  tempJ->Reset();
  handsomeTH1(tempJ,0);
  tempJ->SetAxisRange(0,100,"Y");
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
    dNdJetPt[3][ipt]->Draw("same");
    if ( ipt == 1 ) {
      TLegend *ly = new TLegend(0.4484643,0.6988445,0.9140673,0.9102941,NULL,"brNDC");
      easyLeg(ly,"2.76TeV");
      ly->AddEntry(meanJetPt[1],"PbPb 0-30%","p");
      ly->AddEntry(meanJetPt[3],"pp (smeared)","p");
      ly->Draw();
    }
 

    c5->cd(ipt);
    hTempPt->DrawCopy();

    drawSys(dNdJetPt[2][ipt], dNdJetPtSys[2][ipt], kGreen);
    drawSys(dNdJetPt[4][ipt], dNdJetPtSys[4][ipt], kYellow);
    handsomeTH1(dNdJetPt[4][ipt],2);
    dNdJetPt[4][ipt]->SetMarkerStyle(24);
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
    

  
  
}

/*
  TCanvas* c1 = new TCanvas("c1","",1100,900);
  makeMultiPanelCanvas(c1,nPtBin,4,0.0,0.0,0.2,0.15,0.02);  
  for ( int coll = 1 ; coll<=4 ; coll++) {  
    for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
      c1->cd(nPtBin* (coll-1) + ipt );
      handsomeTH1(dNdJetPt[coll][ipt][2]);
      dNdJetPt[coll][ipt][2]->SetYTitle("Uncertainty of dN/dp_{T}^{jet}");
      dNdJetPt[coll][ipt][2]->SetAxisRange(30,150,"X");
      dNdJetPt[coll][ipt][2]->SetAxisRange(0.,2,"Y");
      dNdJetPt[coll][ipt][2]->Draw("hist");

      
      if ( ipt == 1 )  {
	TString collName;
	if ( coll == kPP )  collName = "p+p";
	else if ( coll == kPA )  collName = "pPb";
	else if ( coll == kHIcentral )  collName = "PbPb 0-30%";
	else if ( coll == kHIperipheral )  collName = "PbPb 30-100%";
	drawText(Form("%s", collName.Data()), 0.3,0.85,1,18);
      }
        TString ptName;
        if ( ipt == 1 )  ptName = "40-50GeV";
        if ( ipt == 2 )  ptName = "50-60GeV";
        if ( ipt == 3 )  ptName = "60-80GeV";
        if ( ipt == 4 )  ptName = ">80GeV";
        drawText(Form("%s", ptName.Data()), 0.3,0.75,1,18);

      
    }
  }

  
  TCanvas* c3 = new TCanvas("c2","",1100,350);
  makeMultiPanelCanvas(c2,4,1,0.0,0.0,0.2,0.15,0.02);  
  for ( int coll = 1 ; coll<=4 ; coll++) {  
    c2->cd(coll);
    handsomeTH1(meanJetPt[coll][2]);
    meanJetPt[coll][2]->SetYTitle("Systematic uncertatiny of <p_{T}^{Jet}>");
    meanJetPt[coll][2]->SetAxisRange(40,125,"X");
    meanJetPt[coll][2]->SetAxisRange(0,0.5,"Y");
    meanJetPt[coll][2]->Draw("hist");

    TString collName;
    if ( coll == kPP )  collName = "p+p";
    else if ( coll == kPA )  collName = "pPb";
    else if ( coll == kHIcentral )  collName = "PbPb 0-30%";
    else if ( coll == kHIperipheral )  collName = "PbPb 30-100%";
    drawText(Form("%s", collName.Data()), 0.3,0.85,1,18);
  } 

  TCanvas* c3 = new TCanvas("c3","",1100,350);
  makeMultiPanelCanvas(c3,4,1,0.0,0.0,0.2,0.15,0.02);  
  for ( int coll = 1 ; coll<=4 ; coll++) {  
    c3->cd(coll);
    handsomeTH1(meanRjg[coll][2]);
    meanRjg[coll][2]->SetYTitle("Systematic uncertatiny of R");
    meanRjg[coll][2]->SetAxisRange(40,125,"X");
    meanRjg[coll][2]->SetAxisRange(0,.5,"Y");
    meanRjg[coll][2]->Draw("hist");

    TString collName;
    if ( coll == kPP )  collName = "p+p";
    else if ( coll == kPA )  collName = "pPb";
    else if ( coll == kHIcentral )  collName = "PbPb 0-30%";
    else if ( coll == kHIperipheral )  collName = "PbPb 30-100%";
    drawText(Form("%s", collName.Data()), 0.3,0.85,1,18);

  } 

  c1->SaveAs("Uncertainty_of_dndjetpt_merged.pdf");
  c2->SaveAs("Uncertainty_of_meanjetpt_merged.pdf");
  c3->SaveAs("Uncertainty_of_r_merged.pdf");
  
}
 
*/
