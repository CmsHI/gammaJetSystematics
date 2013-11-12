///////////////////////////////////////////////////////////////////                                                  
// getSysUncert.C                                                //                                                 
// Creator : Yongsun Kim (KU), kingmking@gmail.com               //
// Function : Compare histograms in two files and returns ratio  // 
///////////////////////////////////////////////////////////////////                                                  
///////////////////////////////////////////////////////////////////                                                  

#include "commonUtilitySys.h"
#include <TRandom3.h>
#include <TFile.h>

void calUncFromFit( TH1D* hReturn=0, TH1D* nominal=0, TH1D* varied=0, float scaleFactor=1) {
  TF1* fNom = nominal->GetFunction("f1");
  TF1* fVar = varied->GetFunction("f1");
  int nBins = hReturn->GetNbinsX(); 
  for ( int ibin=1; ibin<=nBins;ibin++) { 
    float xx = hReturn->GetBinCenter(ibin);
    float yNom = fNom->Eval(xx);
    float yVar = fVar->Eval(xx);
    hReturn->SetBinContent( ibin, ( yVar/yNom - 1 ) * scaleFactor );
    hReturn->SetBinError  ( ibin, 0.0001 );
  }
}


void getSysUncertDist( 
		       TString fname2 = "noJetResCorr",
		       TString fname1 = "nominal",
		       float scaleFactor= 1  // The non-unity scale factor is for electron : 0.25
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
  TH1D* dNdphi[5][5][3];  // [collision] [ ptbin]  [Before/After variation]                                                                                 
  TF1* fJetPt[5][5][3];  // [collision] [ ptbin]  [Before/After variation]
  TF1* fXjg[5][5][3];  // [collision] [ ptbin]  [Before/After variation]                                                                                 
  TF1* fphi[5][5][3];  // [collision] [ ptbin]  [Before/After variation]                                                                                 
  TFile* f; 
 
  for ( int ifile = 0 ; ifile <= 1 ; ifile++ ) { 

    if ( ifile == 0 ) 
      f = new TFile( Form("resultHistograms/resultHistograms_%s_functionAdded.root",fname1.Data()));
    else 
      f = new TFile( Form("resultHistograms/resultHistograms_%s_functionAdded.root",fname2.Data()));
    
    for ( int coll = 1 ; coll<=4 ; coll++) { 
      TString collName;
      if ( coll == kPP )  collName = "pp";
      else if ( coll == kPA )  collName = "ppb";
      else if ( coll == kHIcentral )  collName = "pbpb_centralityBin1";
      else if ( coll == kHIperipheral )  collName = "pbpb_centralityBin2";
        
      for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) { 
	dNdJetPt[coll][ipt][ifile] = (TH1D*)f->Get(Form("dNdJetPt_%s_ptBin%d", collName.Data(), ipt ) );
	dNdXjg[coll][ipt][ifile] = (TH1D*)f->Get(Form("dNdXjg_%s_ptBin%d", collName.Data(), ipt ) );
	dNdphi[coll][ipt][ifile] = (TH1D*)f->Get(Form("dNdphi_%s_ptBin%d", collName.Data(), ipt ) );
	cout << " dNdXjg[coll][ipt][ifile] = " << dNdJetPt[coll][ipt][ifile]->GetName() << endl;
      }
    }
  }
  
  for ( int coll = 1 ; coll<=4 ; coll++) {   
    for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
      dNdJetPt[coll][ipt][2] = (TH1D*)dNdJetPt[coll][ipt][1]->Clone(Form("%s_uncertainty", dNdJetPt[coll][ipt][1]->GetName()));
      calUncFromFit( dNdJetPt[coll][ipt][2], dNdJetPt[coll][ipt][1] , dNdJetPt[coll][ipt][0], scaleFactor); 
      
      dNdXjg[coll][ipt][2] = (TH1D*)dNdXjg[coll][ipt][1]->Clone(Form("%s_uncertainty", dNdXjg[coll][ipt][1]->GetName()));
      calUncFromFit(dNdXjg[coll][ipt][2], dNdXjg[coll][ipt][1] , dNdXjg[coll][ipt][0], scaleFactor); 

      dNdphi[coll][ipt][2] = (TH1D*)dNdphi[coll][ipt][1]->Clone(Form("%s_uncertainty", dNdphi[coll][ipt][1]->GetName()));
      calUncFromFit(dNdphi[coll][ipt][2], dNdphi[coll][ipt][1] , dNdphi[coll][ipt][0], scaleFactor); 


    }
  }

  TCanvas* c1 = new TCanvas("c1","",1200,1200);
  c1->Divide(nPtBin,4);
  TF1* fdNdJetPt[5][5];
  for ( int coll = 1 ; coll<=4 ; coll++) {   // On Sep 30, only pp and pbpb is studied.  pA will be added very soon       
    for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
      c1->cd( ipt + nPtBin*(coll-1) );

      dNdJetPt[coll][ipt][2]->SetAxisRange(30,200,"X");
      dNdJetPt[coll][ipt][2]->SetAxisRange(-.5,.5,"Y");
      dNdJetPt[coll][ipt][2]->GetFunction("f1")->SetLineColor(0);
      dNdJetPt[coll][ipt][2]->GetFunction("f1")->SetLineWidth(0);
      dNdJetPt[coll][ipt][2]->SetStats(0);
      dNdJetPt[coll][ipt][2]->Draw();
      jumSun(30,0,200,0);
    }
  }

  TCanvas* c2 = new TCanvas("c2","",1200,1200);
  c2->Divide(nPtBin,4);
  TF1* fdNdXjg[5][5];
  for ( int coll = 1 ; coll<=4 ; coll++) {   // On Sep 30, only pp and pbpb is studied.  pA will be added very soon       
    for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
      c2->cd( ipt + nPtBin*(coll-1) );

      dNdXjg[coll][ipt][2]->SetAxisRange(0,2,"X");
      dNdXjg[coll][ipt][2]->SetAxisRange(-.5,.5,"Y");
      dNdXjg[coll][ipt][2]->GetFunction("f1")->SetLineColor(0);
      dNdXjg[coll][ipt][2]->GetFunction("f1")->SetLineWidth(0);
      dNdXjg[coll][ipt][2]->SetStats(0);
      dNdXjg[coll][ipt][2]->Draw();
      jumSun(0,0,2,0);
    }
  }

  TCanvas* c3 = new TCanvas("c3","",1200,1200);
  c3->Divide(nPtBin,4);
  TF1* fdNdphi[5][5];
  for ( int coll = 1 ; coll<=4 ; coll++) {   // On Sep 30, only pp and pbpb is studied.  pA will be added very soon       
    for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
      c3->cd( ipt + nPtBin*(coll-1) );

      dNdphi[coll][ipt][2]->SetAxisRange(0,3.15,"X");
      dNdphi[coll][ipt][2]->SetAxisRange(-.5,.5,"Y");
      dNdphi[coll][ipt][2]->GetFunction("f1")->SetLineColor(0);
      dNdphi[coll][ipt][2]->GetFunction("f1")->SetLineWidth(0);
      dNdphi[coll][ipt][2]->SetStats(0);
      dNdphi[coll][ipt][2]->Draw();
      jumSun(0,0,2,0);
    }
  }
  
  TFile * fSysResults = new TFile(Form("relativeSysDist/relativeSys_dueTo_%s.root",fname2.Data()),"recreate");
  for ( int coll = 1 ; coll<=4 ; coll++) {
    for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
      dNdJetPt[coll][ipt][2]->Write();
      dNdXjg[coll][ipt][2]->Write();
      dNdphi[coll][ipt][2]->Write();
    }
  }
  fSysResults->Close();
}

