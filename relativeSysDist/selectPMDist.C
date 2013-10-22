#include "../commonUtilitySys.h"
#include <TRandom3.h>
#include <TFile.h>

void selectLargeValue(TH1D* h1=0, TH1D* h2=0)
{
    int nBins = h1 -> GetNbinsX();
    for(int j=1; j<=nBins; j++){
        float yy = abs(h1 -> GetBinContent(j));
        float xx = abs(h2 -> GetBinContent(j)); 
        if(yy>=xx) h1->SetBinContent(j,yy ) ;
        else h1->SetBinContent(j, xx );
    }
}

void selectPMDist(int option =1 ) { 
  // 1 = photon ,  2 = jet 
    cout << "hello" << endl;
    const int kPP = 1;
    const int kHIcentral =  2;
    const int kHIperipheral = 3;
    const int kPA = 4;
    const int nPtBin = 4;  
    const int nfile = 2;

    TH1D* dNdJetPt[5][5][10];  // [collision] [ ptbin]  [Before/After variation]
    TH1D* dNdXjg[5][5][10];  // [collision] [ ptbin]  [Before/After variation]
    TH1D* dNdphi[5][5][10];  // [collision] [ ptbin]  [Before/After variation]
    TFile* f; 
    
    for ( int ifile = 1 ; ifile <= nfile ; ifile++ ) { 

      if ( option == 1 ) {
	if ( ifile == 1 )       f = new TFile("relativeSys_dueTo_photonEnergyScaleMinus.root");
	else if ( ifile == 2 )  f = new TFile("relativeSys_dueTo_photonEnergyScalePlus.root");
      }
      else               {
	if ( ifile == 1 )       f = new TFile("relativeSys_dueTo_jetEnergyScaleMinus.root");
	else if ( ifile == 2 )  f = new TFile("relativeSys_dueTo_jetEnergyScalePlus.root");
      }
      for ( int coll = 1 ; coll<=4 ; coll++) {   // On Sep 30, only pp and pbpb is studied.  pA will be added very soon
	TString collName;
	if ( coll == kPP )  collName = "pp";
	else if ( coll == kPA )  collName = "ppb";
	else if ( coll == kHIcentral )  collName = "pbpb_centralityBin1";
	else if ( coll == kHIperipheral )  collName = "pbpb_centralityBin2";
	
	for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) { 
	  dNdJetPt[coll][ipt][ifile] = (TH1D*)f->Get(Form("dNdJetPt_%s_ptBin%d_uncertainty", collName.Data(), ipt ) );
	  dNdXjg[coll][ipt][ifile] = (TH1D*)f->Get(Form("dNdXjg_%s_ptBin%d_uncertainty", collName.Data(), ipt ) );
	  dNdphi[coll][ipt][ifile] = (TH1D*)f->Get(Form("dNdphi_%s_ptBin%d_uncertainty", collName.Data(), ipt ) );
	}
      }
    }
    
    // relative uncertainty calculation
    for ( int coll = 1 ; coll<=4 ; coll++) {  
      for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
            dNdJetPt[coll][ipt][0] = (TH1D*)dNdJetPt[coll][ipt][1]->Clone(dNdJetPt[coll][ipt][1]->GetName() );
            dNdJetPt[coll][ipt][0]->Reset();
            selectLargeValue(dNdJetPt[coll][ipt][1], dNdJetPt[coll][ipt][2]);
            dNdJetPt[coll][ipt][0]->Add(dNdJetPt[coll][ipt][1]); 

	    dNdXjg[coll][ipt][0] = (TH1D*)dNdXjg[coll][ipt][1]->Clone(dNdXjg[coll][ipt][1]->GetName() );
            dNdXjg[coll][ipt][0]->Reset();
            selectLargeValue(dNdXjg[coll][ipt][1], dNdXjg[coll][ipt][2]);
            dNdXjg[coll][ipt][0]->Add(dNdXjg[coll][ipt][1]);

	    dNdphi[coll][ipt][0] = (TH1D*)dNdphi[coll][ipt][1]->Clone(dNdphi[coll][ipt][1]->GetName() );
            dNdphi[coll][ipt][0]->Reset();
            selectLargeValue(dNdphi[coll][ipt][1], dNdphi[coll][ipt][2]);
            dNdphi[coll][ipt][0]->Add(dNdphi[coll][ipt][1]);

        }
    }
    
    TFile * fSysResult;
    if ( option == 1 ) 
      fSysResult = new TFile("relativeSys_dueTo_photonEnergyScale.root","recreate");
    else 
      fSysResult = new TFile("relativeSys_dueTo_jetEnergyScale.root","recreate");

    for ( int coll = 1 ; coll<=4 ; coll++) {   // On Sep 30, only pp and pbpb is studied.  pA will be added very soon        
        for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
            dNdJetPt[coll][ipt][0]->Write();
            dNdXjg[coll][ipt][0]->Write();
            dNdphi[coll][ipt][0]->Write();
        }
    }
    
    fSysResult->Close();
    
    
}


