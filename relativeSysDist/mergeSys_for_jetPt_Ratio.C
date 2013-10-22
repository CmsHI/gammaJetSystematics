#include "../commonUtilitySys.h"
#include <TRandom3.h>
#include <TFile.h>

void squareHist(TH1* h=0)
{
  Int_t nBins = h->GetNbinsX();
  for ( Int_t j=1; j<=nBins ;j++)
    {
      float yy = h->GetBinContent(j);
      h->SetBinContent(j, yy*yy);
      h->SetBinError  (j, 0);
    }

}

void squareRootHist(TH1* h=0)
{
  Int_t nBins = h->GetNbinsX();
  for ( Int_t j=1; j<=nBins ;j++)
    {
      float yy = h->GetBinContent(j);
      h->SetBinContent(j, sqrt(yy) );
      h->SetBinError  (j, 0.000001 );
    }
  
}

void addValueToAllBin(TH1* h=0, float val=1) 
{
  Int_t nBins = h->GetNbinsX();
  for ( Int_t j=1; j<=nBins ;j++)
    {
      float yy = h->GetBinContent(j);
      h->SetBinContent(j, yy + val);
    }

}



void mergeSys_for_jetPt_Ratio() {

  const int kPP = 1;
  const int kHIcentral =  2;
  const int kHIperipheral = 3;
  const int kPA = 4;
  const int nPtBin = 4;  
  
  TH1D* dNdJetPt[5][5][10];
  TH1D* hOutput[5][5][10];

  TFile* f; 
 
  const int nFile  = 7;
  for ( int ifile = 1 ; ifile <= nFile ; ifile++ ) { 
    
    if ( ifile == 1 )       f = new TFile("relativeSys_dueTo_noJetResCorr.root");
    else if ( ifile == 2 )  f = new TFile("relativeSys_dueTo_photonEnergyScale.root");
    else if ( ifile == 3 )  f = new TFile("relativeSys_dueTo_MCrecoIso.root");
    else if ( ifile == 4 )  f = new TFile("relativeSys_dueTo_photonPurityVaried.root");
    else if ( ifile == 5 )  f = new TFile("relativeSys_dueTo_noElectronRejection.root");
    else if ( ifile == 6 )  f = new TFile("relativeSys_dueTo_jetEnergyScale.root");
    else if ( ifile == 7 )  f = new TFile("relativeSys_dueTo_jetEnergySmeared.root");
    
    for ( int coll = 1 ; coll<=4 ; coll++) {   // On Sep 30, only pp and pbpb is studied.  pA will be added very soon
      TString collName;
      if ( coll == kPP )  collName = "pp";
      else if ( coll == kPA )  collName = "ppb";
      else if ( coll == kHIcentral )  collName = "pbpb_centralityBin1";
      else if ( coll == kHIperipheral )  collName = "pbpb_centralityBin2";
      
      
	for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) { 
	  dNdJetPt[coll][ipt][ifile] = (TH1D*)f->Get(Form("dNdJetPt_%s_ptBin%d_uncertainty", collName.Data(), ipt ) );
	  
	  
	}
    }
  }
  
  // Divide the uncertainties 
  for ( int ifile = 1 ; ifile <= nFile ; ifile++ ) {
    for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
      
      hOutput[kHIcentral][ipt][ifile] = (TH1D*)dNdJetPt[kHIcentral][ipt][ifile]->Clone(Form("dNdJetPt_ratio_centralityBin1_ptBin%d_uncertainty", ipt ) );
      hOutput[kHIperipheral][ipt][ifile] = (TH1D*)dNdJetPt[kHIperipheral][ipt][ifile]->Clone(Form("dNdJetPt_ratio_centralityBin2_ptBin%d_uncertainty", ipt ) );
      hOutput[kPP][ipt][ifile] = (TH1D*)dNdJetPt[kPP][ipt][ifile]->Clone(Form("dNdJetPt_pp_ptBin%d_uncertainty", ipt ) );
      
      // Add unity
      addValueToAllBin(hOutput[kHIcentral][ipt][ifile],    1);
      addValueToAllBin(hOutput[kHIperipheral][ipt][ifile], 1);
      addValueToAllBin(hOutput[kPP][ipt][ifile],           1);
      
      hOutput[kHIcentral][ipt][ifile]->Divide(hOutput[kPP][ipt][ifile]);
      hOutput[kHIperipheral][ipt][ifile]->Divide(hOutput[kPP][ipt][ifile]);
      addValueToAllBin(hOutput[kHIcentral][ipt][ifile],    -1);
      addValueToAllBin(hOutput[kHIperipheral][ipt][ifile], -1);


    }
  }
  
  // relative uncertainty calculation
  for ( int coll = 1 ; coll<=4 ; coll++) {   
    if   ( ( coll != kHIcentral) && ( coll != kHIperipheral ) )  
      continue;
    cout << " here 1 " << endl;
    for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
      hOutput[coll][ipt][0] = (TH1D*)hOutput[coll][ipt][1]->Clone(Form("%s_merged",hOutput[coll][ipt][1]->GetName() ) );
      hOutput[coll][ipt][0]->Reset();
      for ( int ifile = 1 ; ifile <= nFile ; ifile++ ) {
	squareHist( hOutput[coll][ipt][ifile] );
	hOutput[coll][ipt][0]->Add(hOutput[coll][ipt][ifile]);
      }
      squareRootHist(hOutput[coll][ipt][0]);
      
    cout << " here 2" << endl;
    }
  }
  TFile * fSysResults = new TFile("relativeSys_merged_for_jetPt_Ratio.root","recreate");
  
  for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
      hOutput[kHIperipheral][ipt][0]->Write();
      hOutput[kHIcentral][ipt][0]->Write();
  }
  
  fSysResults->Close();
  
  
}

