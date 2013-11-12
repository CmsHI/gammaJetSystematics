#include "commonUtilitySys.h"
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

void selectPM() {
    cout << "hello" << endl;
    const int kPP = 1;
    const int kHIcentral =  2;
    const int kHIperipheral = 3;
    const int kPA = 4;
    const int nPtBin = 4;  
    const int nfile = 2;

    TH1D* dNdJetPt[5][5][10];  // [collision] [ ptbin]  [Before/After variation]
    TH1D* dNdXjg[5][5][10];  // [collision] [ ptbin]  [Before/After variation]
    TH1D* dNdIaa[5][5][10];  // [collision] [ ptbin]  [Before/After variation]
    TH1D* meanJetPt[5][10];   // [collision] [Before/After variation]
    TH1D* meanRjg[5][10];
    TH1D* meanXjg[5][10];
    TFile* f; 
    
    for ( int ifile = 1 ; ifile <= nfile ; ifile++ ) { 

      //      if ( ifile == 1 )       f = new TFile("relativeSys_dueTo_jetEnegyScaleMinus.root");
      // else if ( ifile == 2 )  f = new TFile("relativeSys_dueTo_jetEnegyScalePlus.root");
    
      if ( ifile == 1 )       f = new TFile("relativeSys_dueTo_photonEnergyScaleMinus.root");
      else if ( ifile == 2 )  f = new TFile("relativeSys_dueTo_photonEnergyScalePlus.root");
      
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
	  if ( coll != kPA ) dNdIaa[coll][ipt][ifile] = (TH1D*)f->Get(Form("dNdJetPt_forIaa_%s_ptBin%dAndHigher_uncertainty", collName.Data(), ipt ) );

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

	    if ( coll != kPA ) { 
	      dNdIaa[coll][ipt][0] = (TH1D*)dNdIaa[coll][ipt][1]->Clone(dNdIaa[coll][ipt][1]->GetName() );
	      dNdIaa[coll][ipt][0]->Reset();
	      selectLargeValue(dNdIaa[coll][ipt][1], dNdIaa[coll][ipt][2]);
	      dNdIaa[coll][ipt][0]->Add(dNdIaa[coll][ipt][1]); 
	    }
	    
            dNdXjg[coll][ipt][0] = (TH1D*)dNdXjg[coll][ipt][1]->Clone(dNdXjg[coll][ipt][1]->GetName() );
            dNdXjg[coll][ipt][0]->Reset();
            selectLargeValue(dNdXjg[coll][ipt][1], dNdXjg[coll][ipt][2]);
            dNdXjg[coll][ipt][0]->Add(dNdXjg[coll][ipt][1]);
        }
        meanJetPt[coll][0] = (TH1D*)meanJetPt[coll][1]->Clone(meanJetPt[coll][1]->GetName() );
        meanJetPt[coll][0]->Reset();
        selectLargeValue(meanJetPt[coll][1], meanJetPt[coll][2]);
        meanJetPt[coll][0]->Add(meanJetPt[coll][1]); 


        meanRjg[coll][0] = (TH1D*)meanRjg[coll][1]->Clone(meanRjg[coll][1]->GetName() );
        meanRjg[coll][0]->Reset();
        selectLargeValue(meanRjg[coll][1], meanRjg[coll][2]);
        meanRjg[coll][0]->Add(meanRjg[coll][1]); 


        meanXjg[coll][0] = (TH1D*)meanXjg[coll][1]->Clone(meanXjg[coll][1]->GetName() );
        meanXjg[coll][0]->Reset();
        selectLargeValue(meanXjg[coll][1], meanXjg[coll][2]);
        meanXjg[coll][0]->Add(meanXjg[coll][1]); 
    }
    
        TFile * fSysResults = new TFile("relativeSys_dueTo_photonEnergyScale.root","recreate");
    //    TFile * fSysResults = new TFile("relativeSys_dueTo_jetEnergyScale.root","recreate");

    for ( int coll = 1 ; coll<=4 ; coll++) {   // On Sep 30, only pp and pbpb is studied.  pA will be added very soon        
        for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
            dNdJetPt[coll][ipt][0]->Write();
            dNdXjg[coll][ipt][0]->Write();
	    if ( coll != kPA )  
	      dNdIaa[coll][ipt][0]->Write();

        }
        meanJetPt[coll][0]->Write();
        meanRjg[coll][0]->Write();
        meanXjg[coll][0]->Write();
    }

    fSysResults->Close();


}


