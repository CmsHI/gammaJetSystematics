#include "commonUtilitySys.h"
#include <TRandom3.h>
#include <Tfile.h>

void drawSys_photonIso() {
  const int kPP = 1;
  const int kHIcentral =  2;
  const int kHIperipheral = 3;
  const int kPA = 4;
  const int nPtBin = 4;  
  
  TH1D* dNdJetPt[4][5][3];  // [collision] [ ptbin]  [Before/After variation]
  TH1D* dNdXjg[4][5][3];  // [collision] [ ptbin]  [Before/After variation]
  TH1D* meanJetPt[4][3];   // [collision] [Before/After variation]
  TH1D* meanRjg[4][3];
 
  TFile * fSysResults = new TFile("relativeSys_dueTo_isolation.root");
  
  
  for ( int coll = 1 ; coll<=4 ; coll++) {  
    TString collName;
    if ( coll == kPP )  collName = "pp";
    else if ( coll == kPA )  collName = "ppb";
    else if ( coll == kHIcentral )  collName = "pbpb_centralityBin1";
    else if ( coll == kHIperipheral )  collName = "pbpb_centralityBin2";


    meanJetPt[coll][2]  =(TH1D*)fSysResults->Get(Form("meanJetPt_%s_uncertainty", collName.Data()));
    meanRjg[coll][2]  =(TH1D*)fSysResults->Get(Form("meanRjg_%s_uncertainty", collName.Data()) );
    for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
      dNdJetPt[coll][ipt][2] = (TH1D*)fSysResults->Get(Form("dNdJetPt_IaaBin_%s_ptBin%d_uncertainty", collName.Data(), ipt ) );
      dNdXjg[coll][ipt][2] = (TH1D*)fSysResults->Get(Form("dNdXjg_%s_ptBin%d_uncertainty", collName.Data(), ipt ) );
    }
  }
  
  TCanvas* c1 = new TCanvas("c1","",1100,900);
  makeMultiPanelCanvas(c1,nPtBin,4,0.0,0.0,0.2,0.15,0.02);  
  for ( int coll = 1 ; coll<=4 ; coll++) {  
    for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
      c1->cd(nPtBin* (coll-1) + ipt );
      handsomeTH1(dNdJetPt[coll][ipt][2]);
      dNdJetPt[coll][ipt][2]->SetYTitle("Uncertainty of dN/dp_{T}^{jet}");
      dNdJetPt[coll][ipt][2]->SetAxisRange(30,150,"X");
      dNdJetPt[coll][ipt][2]->SetAxisRange(0.,2,"Y");
      dNdJetPt[coll][ipt][2]->Draw();
      jumSun(30,1,150,1);
      
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

  
  TCanvas* c2 = new TCanvas("c2","",1100,350);
  makeMultiPanelCanvas(c2,4,1,0.0,0.0,0.2,0.15,0.02);  
  for ( int coll = 1 ; coll<=4 ; coll++) {  
    c2->cd(coll);
    handsomeTH1(meanJetPt[coll][2]);
    meanJetPt[coll][2]->SetYTitle("Systematic uncertatiny of <p_{T}^{Jet}>");
    meanJetPt[coll][2]->SetAxisRange(40,125,"X");
    meanJetPt[coll][2]->SetAxisRange(0,2,"Y");
    meanJetPt[coll][2]->Draw();
    jumSun(40,1,125,1);

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
    meanRjg[coll][2]->SetAxisRange(0,2,"Y");
    meanRjg[coll][2]->Draw();
    jumSun(40,1,125,1);

    TString collName;
    if ( coll == kPP )  collName = "p+p";
    else if ( coll == kPA )  collName = "pPb";
    else if ( coll == kHIcentral )  collName = "PbPb 0-30%";
    else if ( coll == kHIperipheral )  collName = "PbPb 30-100%";
    drawText(Form("%s", collName.Data()), 0.3,0.85,1,18);

  } 

  c1->SaveAs("Uncertainty_of_dndjetpt_by_photonIso.pdf");
  c2->SaveAs("Uncertainty_of_meanjetpt_by_photonIso.pdf");
  c3->SaveAs("Uncertainty_of_r_by_photonIso.pdf");
  
}
 
