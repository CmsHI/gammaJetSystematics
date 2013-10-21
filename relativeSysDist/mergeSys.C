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


void mergeSys() {
  cout << "hello" << endl;
  const int kPP = 1;
  const int kHIcentral =  2;
  const int kHIperipheral = 3;
  const int kPA = 4;
  const int nPtBin = 4;  
  
  TH1D* dNdJetPt[5][5][10];
  TH1D* dNdXjg[5][5][10]; 

  TFile* f; 
 
  int nFile  = 7;
    for ( int ifile = 1 ; ifile <= nFile ; ifile++ ) { 

      if ( ifile == 1 )       f = new TFile("relativeSys_dueTo_noJetResCorr.root");
      else if ( ifile == 2 )  f = new TFile("relativeSys_dueTo_photonEnergyScale.root");
      else if ( ifile == 3 )  f = new TFile("relativeSys_dueTo_MCrecoIso.root");
      else if ( ifile == 4 )  f = new TFile("relativeSys_dueTo_photonPurityVaried.root");
      else if ( ifile == 5 )  f = new TFile("relativeSys_dueTo_noElectronRejection.root");
      else if ( ifile == 6 )  f = new TFile("relativeSys_dueTo_jetEnergyScale.root");
      else if ( ifile == 7 )  f = new TFile("relativeSys_dueTo_jetEnergySmearing.root");
    
    for ( int coll = 1 ; coll<=4 ; coll++) {   // On Sep 30, only pp and pbpb is studied.  pA will be added very soon
      TString collName;
      if ( coll == kPP )  collName = "pp";
      else if ( coll == kPA )  collName = "ppb";
      else if ( coll == kHIcentral )  collName = "pbpb_centralityBin1";
      else if ( coll == kHIperipheral )  collName = "pbpb_centralityBin2";
      
      
      for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) { 
	dNdJetPt[coll][ipt][ifile] = (TH1D*)f->Get(Form("dNdJetPt_%s_ptBin%d_uncertainty", collName.Data(), ipt ) );
	dNdXjg[coll][ipt][ifile] = (TH1D*)f->Get(Form("dNdXjg_%s_ptBin%d_uncertainty", collName.Data(), ipt ) );

      }
    }
  }

  // relative uncertainty calculation
  for ( int coll = 1 ; coll<=4 ; coll++) {   
    for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
      dNdJetPt[coll][ipt][0] = (TH1D*)dNdJetPt[coll][ipt][1]->Clone(Form("%s_merged",dNdJetPt[coll][ipt][1]->GetName() ) );
      dNdJetPt[coll][ipt][0]->Reset();
      for ( int ifile = 1 ; ifile <= nFile ; ifile++ ) {
	squareHist( dNdJetPt[coll][ipt][ifile] );
	dNdJetPt[coll][ipt][0]->Add(dNdJetPt[coll][ipt][ifile]);
      }
      squareRootHist(dNdJetPt[coll][ipt][0]);

      dNdXjg[coll][ipt][0] = (TH1D*)dNdXjg[coll][ipt][1]->Clone(Form("%s_merged",dNdXjg[coll][ipt][1]->GetName() ) );
      dNdXjg[coll][ipt][0]->Reset();
      for ( int ifile = 1 ; ifile <= nFile ; ifile++ ) {
	squareHist( dNdXjg[coll][ipt][ifile] );
	dNdXjg[coll][ipt][0]->Add(dNdXjg[coll][ipt][ifile]);
      }
      squareRootHist(dNdXjg[coll][ipt][0]);


    }
  }
  TFile * fSysResults = new TFile("relativeSys_merged.root","recreate");
  
  for ( int coll = 1 ; coll<=4 ; coll++) {   // On Sep 30, only pp and pbpb is studied.  pA will be added very soon        
    for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
      dNdJetPt[coll][ipt][0]->Write();
      dNdXjg[coll][ipt][0]->Write();
    }
  }
  
  fSysResults->Close();
  
  
}
 

