#include "commonUtilitySys.h"
#include <TRandom3.h>
#include <Tfile.h>

void getSysUncert() {
  cout << "hello" << endl;
  const int kPP = 1;
  const int kHIcentral =  2;
  const int kHIperipheral = 3;
  const int kPA = 4;
  const int nPtBin = 4;  
  
  TH1D* dNdJetPt[4][5][3];  // [collision] [ ptbin]  [Before/After variation]
  TH1D* meanJetPt[4][3];   // [collision] [Before/After variation]
  TH1D* meanRjg[4][3];
  TFile* f; 
 
  for ( int ifile = 0 ; ifile <= 1 ; ifile++ ) { 

    if ( ifile == 0 ) 
      f = new TFile("resultHistograms.root");
    else 
      f = new TFile("resultHistograms_photonEnergy_ScaledBy0.015.root");

    for ( int coll = 1 ; coll<=4 ; coll++) {   // On Sep 30, only pp and pbpb is studied.  pA will be added very soon
      TString collName;
      if ( coll == kPP )  collName = "pp";
      else if ( coll == kPA )  collName = "ppb";
      else if ( coll == kHIcentral )  collName = "pbpb_centralityBin1";
      else if ( coll == kHIperipheral )  collName = "pbpb_centralityBin2";
      
      meanJetPt[coll][ifile]  =(TH1D*)f->Get(Form("meanJetPt_%s", collName.Data()));
      meanRjg[coll][ifile]  =(TH1D*)f->Get(Form("meanRjg_%s", collName.Data()) );
      
      for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) { 
	dNdJetPt[coll][ipt][ifile] = (TH1D*)f->Get(Form("dNdJetPt_IaaBin_%s_ptBin%d", collName.Data(), ipt ) );
      }
    }
  }
  // relative uncertainty calculation
  for ( int coll = 1 ; coll<=4 ; coll++) {   // On Sep 30, only pp and pbpb is studied.  pA will be added very soon                                                
    for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
      dNdJetPt[coll][ipt][2] = (TH1D*)dNdJetPt[coll][ipt][1]->Clone(Form("%s_uncertainty", dNdJetPt[coll][ipt][1]->GetName()));
      dNdJetPt[coll][ipt][2]->Divide( dNdJetPt[coll][ipt][0] );
    }
    meanJetPt[coll][2] = (TH1D*)meanJetPt[coll][1]->Clone(Form("%s_uncertainty", meanJetPt[coll][1]->GetName()) );
    meanJetPt[coll][2]->Divide( meanJetPt[coll][0] );
     
    cout << " coll = " << coll << endl;
    cout << " name = " << meanRjg[coll][1]->GetName() << endl;
    meanRjg[coll][2] = (TH1D*)meanRjg[coll][1]->Clone(Form("%s_uncertainty", meanRjg[coll][1]->GetName() ) );
    meanRjg[coll][2]->Divide( meanRjg[coll][0] );
    
  }
  
  TFile * fSysResults = new TFile("relativeSys_dueTo_energyScalePlus.root","recreate");
  //TFile * fSysResults = new TFile("relativeSys_dueTo_energyScaleMinus.root","recreate");
  //  TFile * fSysResults = new TFile("relativeSys_dueTo_jetResolution.root","recreate");
  // TFile * fSysResults = new TFile("relativeSys_dueTo_isolation.root","recreate");

  
  for ( int coll = 1 ; coll<=4 ; coll++) {   // On Sep 30, only pp and pbpb is studied.  pA will be added very soon        
    for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
      dNdJetPt[coll][ipt][2]->Write();
    }
    meanJetPt[coll][2]->Write();
    meanRjg[coll][2]->Write();
  }
  
  fSysResults->Close();
  
  
}
 
