#include "commonUtilitySys.h"
#include <TRandom3.h>
#include <Tfile.h>

void squareFromUnityHist(TH1* h=0)
{
  Int_t nBins = h->GetNbinsX();
  for ( Int_t j=1; j<=nBins ;j++)
    {
      float yy = h->GetBinContent(j);
      h->SetBinContent(j, (yy-1.)*(yy-1.) );
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


void mergeSys() {
  cout << "hello" << endl;
  const int kPP = 1;
  const int kHIcentral =  2;
  const int kHIperipheral = 3;
  const int kPA = 4;
  const int nPtBin = 4;  
  
  TH1D* dNdJetPt[5][5][10];  // [collision] [ ptbin]  [Before/After variation]
  TH1D* dNdXjg[5][5][10];  // [collision] [ ptbin]  [Before/After variation]
  TH1D* meanJetPt[5][10];   // [collision] [Before/After variation]
  TH1D* meanRjg[5][10];
  TH1D* meanXjg[5][10];
  TFile* f; 
 
  for ( int ifile = 1 ; ifile <= 7 ; ifile++ ) { 

    if ( ifile == 1 )       f = new TFile("relativeSys_dueTo_photonEnergyScaleMinus.root");
    else if ( ifile == 2 )  f = new TFile("relativeSys_dueTo_jetResolution.root");
    else if ( ifile == 3 )  f = new TFile("relativeSys_dueTo_isolation.root");
    else if ( ifile == 4 )  f = new TFile("relativeSys_dueTo_jetResCorrection.root");
    else if ( ifile == 5 )  f = new TFile("relativeSys_dueTo_jetEnegyScaleMinus.root");
    else if ( ifile == 6 )  f = new TFile("relativeSys_dueTo_electronContamination.root");
    else if ( ifile == 7 )  f = new TFile("relativeSys_dueTo_photonPurity.root");

    for ( int coll = 1 ; coll<=4 ; coll++) {   // On Sep 30, only pp and pbpb is studied.  pA will be added very soon
      TString collName;
      if ( coll == kPP )  collName = "pp";
      else if ( coll == kPA )  collName = "ppb";
      else if ( coll == kHIcentral )  collName = "pbpb_centralityBin1";
      else if ( coll == kHIperipheral )  collName = "pbpb_centralityBin2";
      
      meanJetPt[coll][ifile]  =(TH1D*)f->Get(Form("meanJetPt_%s_uncertainty", collName.Data()));
      meanRjg[coll][ifile]  =(TH1D*)f->Get(Form("meanRjg_%s_uncertainty", collName.Data()) );
      meanXjg[coll][ifile]  =(TH1D*)f->Get(Form("meanXjg_%s_uncertainty", collName.Data()) );
      
      for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) { 
	dNdJetPt[coll][ipt][ifile] = (TH1D*)f->Get(Form("dNdJetPt_IaaBin_%s_ptBin%d_uncertainty", collName.Data(), ipt ) );
	dNdXjg[coll][ipt][ifile] = (TH1D*)f->Get(Form("dNdXjg_%s_ptBin%d_uncertainty", collName.Data(), ipt ) );
      }
    }
  }

  // relative uncertainty calculation
  for ( int coll = 1 ; coll<=4 ; coll++) {   // On Sep 30, only pp and pbpb is studied.  pA will be added very soon              
    for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
      dNdJetPt[coll][ipt][0] = (TH1D*)dNdJetPt[coll][ipt][1]->Clone(Form("%s_merged",dNdJetPt[coll][ipt][1]->GetName() ) );
      dNdJetPt[coll][ipt][0]->Reset();
      for ( int ifile = 1 ; ifile <= 7 ; ifile++ ) {
	squareFromUnityHist( dNdJetPt[coll][ipt][ifile] );
	dNdJetPt[coll][ipt][0]->Add(dNdJetPt[coll][ipt][ifile]);
      }
      squareRootHist(dNdJetPt[coll][ipt][0]);

      dNdXjg[coll][ipt][0] = (TH1D*)dNdXjg[coll][ipt][1]->Clone(Form("%s_merged",dNdXjg[coll][ipt][1]->GetName() ) );
      dNdXjg[coll][ipt][0]->Reset();
      for ( int ifile = 1 ; ifile <= 7 ; ifile++ ) {
	squareFromUnityHist( dNdXjg[coll][ipt][ifile] );
	dNdXjg[coll][ipt][0]->Add(dNdXjg[coll][ipt][ifile]);
      }
      squareRootHist(dNdXjg[coll][ipt][0]);


    }
    
    meanJetPt[coll][0] = (TH1D*)meanJetPt[coll][1]->Clone(Form("%s_merged",meanJetPt[coll][1]->GetName() ) );
    meanJetPt[coll][0]->Reset();
    for ( int ifile = 1 ; ifile <= 7 ; ifile++ ) {
      squareFromUnityHist( meanJetPt[coll][ifile]);
      meanJetPt[coll][0]->Add(meanJetPt[coll][ifile]);
    }
    squareRootHist(meanJetPt[coll][0]);
    
    meanRjg[coll][0] = (TH1D*)meanRjg[coll][1]->Clone(Form("%s_merged",meanRjg[coll][1]->GetName() ) );
    meanRjg[coll][0]->Reset();
    for ( int ifile = 1 ; ifile <= 7 ; ifile++ ) {
      squareFromUnityHist( meanRjg[coll][ifile]);
      meanRjg[coll][0]->Add(meanRjg[coll][ifile]);
    }
    squareRootHist(meanRjg[coll][0]);

    meanXjg[coll][0] = (TH1D*)meanXjg[coll][1]->Clone(Form("%s_merged",meanXjg[coll][1]->GetName() ) );
    meanXjg[coll][0]->Reset();
    for ( int ifile = 1 ; ifile <= 7 ; ifile++ ) {
      squareFromUnityHist( meanXjg[coll][ifile]);
      meanXjg[coll][0]->Add(meanXjg[coll][ifile]);
    }
    squareRootHist(meanXjg[coll][0]);
    
    
  }
  TFile * fSysResults = new TFile("relativeSys_merged.root","recreate");
  
  for ( int coll = 1 ; coll<=4 ; coll++) {   // On Sep 30, only pp and pbpb is studied.  pA will be added very soon        
    for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
      dNdJetPt[coll][ipt][0]->Write();
      dNdXjg[coll][ipt][0]->Write();
    }
    meanJetPt[coll][0]->Write();
    meanRjg[coll][0]->Write();
    meanXjg[coll][0]->Write();
  }
  
  fSysResults->Close();
  
  
}
 

