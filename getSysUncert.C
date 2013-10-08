///////////////////////////////////////////////////////////////////                                                  
// getSysUncert.C                                                //                                                 
// Creator : Yongsun Kim (KU), kingmking@gmail.com               //
// Function : Compare histograms in two files and returns ratio  // 
///////////////////////////////////////////////////////////////////                                                  
///////////////////////////////////////////////////////////////////                                                  

#include "commonUtilitySys.h"
#include <TRandom3.h>
#include <TFile.h>

void getSysUncert(   
		  TString fname1 = "resultHistograms.root", 
		  TString fname2 = "resultHistograms_jetEnegyScalePlus.root"
		     )
{
  cout << "===============================================================================" << endl;
  cout << " Comparing " << fname1 <<"   VS  " << fname2 << endl;
  cout << "===============================================================================" << endl;
  
  const int kPP = 1;
  const int kHIcentral =  2;
  const int kHIperipheral = 3;
  const int kPA = 4;
  const int nPtBin = 4;  
  
  TH1D* dNdJetPt[5][5][3];  // [collision] [ ptbin]  [Before/After variation]
  TH1D* dNdXjg[5][5][3];  // [collision] [ ptbin]  [Before/After variation]                                                                                 
  TH1D* meanXjg[5][3];   // [collision] [Before/After variation]
  TH1D* meanJetPt[5][3];   // [collision] [Before/After variation]
  TH1D* meanRjg[5][3];
  TFile* f; 
 
  for ( int ifile = 0 ; ifile <= 1 ; ifile++ ) { 

    if ( ifile == 0 ) 
      f = new TFile(fname1.Data());
    else 
      f = new TFile(fname2.Data());

    for ( int coll = 1 ; coll<=4 ; coll++) { 
      TString collName;
      if ( coll == kPP )  collName = "pp";
      else if ( coll == kPA )  collName = "ppb";
      else if ( coll == kHIcentral )  collName = "pbpb_centralityBin1";
      else if ( coll == kHIperipheral )  collName = "pbpb_centralityBin2";
      
      meanJetPt[coll][ifile]  =(TH1D*)f->Get(Form("meanJetPt_%s", collName.Data()));
      meanXjg[coll][ifile]  =(TH1D*)f->Get(Form("meanXjg_%s", collName.Data()));
      meanRjg[coll][ifile]  =(TH1D*)f->Get(Form("meanRjg_%s", collName.Data()) );
      
      for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) { 
	dNdJetPt[coll][ipt][ifile] = (TH1D*)f->Get(Form("dNdJetPt_IaaBin_%s_ptBin%d", collName.Data(), ipt ) );
	dNdXjg[coll][ipt][ifile] = (TH1D*)f->Get(Form("dNdXjg_%s_ptBin%d", collName.Data(), ipt ) );
	//	cout << Form("dNdXjg_%s_ptBin%d", collName.Data(), ipt )  << endl;
      }
    }
  }
  
  for ( int coll = 1 ; coll<=4 ; coll++) {   
    for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
      dNdJetPt[coll][ipt][2] = (TH1D*)dNdJetPt[coll][ipt][1]->Clone(Form("%s_uncertainty", dNdJetPt[coll][ipt][1]->GetName()));
      dNdJetPt[coll][ipt][2]->Divide( dNdJetPt[coll][ipt][0] );

      dNdXjg[coll][ipt][2] = (TH1D*)dNdXjg[coll][ipt][1]->Clone(Form("%s_uncertainty", dNdXjg[coll][ipt][1]->GetName()));
      dNdXjg[coll][ipt][2]->Divide( dNdXjg[coll][ipt][0] );
    }
    meanJetPt[coll][2] = (TH1D*)meanJetPt[coll][1]->Clone(Form("%s_uncertainty", meanJetPt[coll][1]->GetName()) );
    meanJetPt[coll][2]->Divide( meanJetPt[coll][0] );

    meanXjg[coll][2] = (TH1D*)meanXjg[coll][1]->Clone(Form("%s_uncertainty", meanXjg[coll][1]->GetName()) );
    meanXjg[coll][2]->Divide( meanXjg[coll][0] );
     
    meanRjg[coll][2] = (TH1D*)meanRjg[coll][1]->Clone(Form("%s_uncertainty", meanRjg[coll][1]->GetName() ) );
    meanRjg[coll][2]->Divide( meanRjg[coll][0] );
    
  }
  
  TString outname = fname2.ReplaceAll("resultHistograms", "relativeSys_dueTo");
  TFile * fSysResults = new TFile(outname,"recreate");

  
  for ( int coll = 1 ; coll<=4 ; coll++) {   // On Sep 30, only pp and pbpb is studied.  pA will be added very soon        
    for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
      dNdJetPt[coll][ipt][2]->Write();
      dNdXjg[coll][ipt][2]->Write();
    }
    meanJetPt[coll][2]->Write();
    meanXjg[coll][2]->Write();
    meanRjg[coll][2]->Write();
  }
  
  fSysResults->Close();
  
  
}
 
