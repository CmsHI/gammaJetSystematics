///////////////////////////////////////////////////////////////////                                                  
// getSysUncert.C                                                //                                                 
// Creator : Yongsun Kim (KU), kingmking@gmail.com               //
// Function : Compare histograms in two files and returns ratio  // 
///////////////////////////////////////////////////////////////////                                                  
///////////////////////////////////////////////////////////////////                                                  

#include "commonUtilitySys.h"
#include <TRandom3.h>
#include <TFile.h>

void calUncert  ( TH1D* h1, TH1D* h0, float scaleFactor) { 
  h1->Add(h0,-1);
  h1->Scale(scaleFactor);
  h1->Add(h0);
  h1->Divide(h0);
}

void Subtract1(TH1D* h1) {
  int nBins = h1 -> GetNbinsX();
  for(int j=1; j<=nBins; j++){
    float yy = h1 -> GetBinContent(j) - 1; 
    float yyErr = h1 -> GetBinError(j) - 1; 
    if ( yy == -1 )  {
      yy = 0;
      yyErr = 0;
    }
    
    h1->SetBinContent(j, yy);
    h1->SetBinError(j,yyErr);
    
  }
}

void fillCurve(TF1* f1, TH1D* h1) {
  int nBins = h1 -> GetNbinsX();
  for(int j=1; j<=nBins; j++){
    float xx = h1->GetBinCenter(j);
    float yy = f1->Eval(xx);
    h1->SetBinContent(j,yy);
    h1->SetBinError(j,0);
  }
}



void getSysUncert(   
		  TString fname1 = "resultHistograms_centralOct16.root",
		  TString fname2 = "relativeSys_dueTo_jetResCorrectionOct16.root",
		  float scaleFactor= 1

		  
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
  TH1D* dNdIaa[5][5][3];  // [collision] [ ptbin]  [Before/After variation]
  TH1D* dNdXjg[5][5][3];  // [collision] [ ptbin]  [Before/After variation]                                                                                 

  TH1D* dNdJetPtSmooth[5][5][3];  // [collision] [ ptbin]  [Before/After variation]
  TH1D* dNdIaaSmooth[5][5][3];  // [collision] [ ptbin]  [Before/After variation]
  TH1D* dNdXjgSmooth[5][5][3];  // [collision] [ ptbin]  [Before/After variation]                                                                                 
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
	//	dNdJetPt[coll][ipt][ifile] = (TH1D*)f->Get(Form("dNdJetPt_IaaBin_%s_ptBin%d", collName.Data(), ipt ) );
	dNdJetPt[coll][ipt][ifile] = (TH1D*)f->Get(Form("dNdJetPt_%s_ptBin%d", collName.Data(), ipt ) );
	if (  coll != kPA ) dNdIaa[coll][ipt][ifile] = (TH1D*)f->Get(Form("dNdJetPt_forIaa_%s_ptBin%dAndHigher", collName.Data(), ipt ) );
	dNdXjg[coll][ipt][ifile] = (TH1D*)f->Get(Form("dNdXjg_%s_ptBin%d", collName.Data(), ipt ) );
	//	cout << Form("dNdXjg_%s_ptBin%d", collName.Data(), ipt )  << endl;
      }
    }
  }
  
  for ( int coll = 1 ; coll<=4 ; coll++) {   
    for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
      dNdJetPt[coll][ipt][2] = (TH1D*)dNdJetPt[coll][ipt][1]->Clone(Form("%s_uncertainty", dNdJetPt[coll][ipt][1]->GetName()));
      calUncert( dNdJetPt[coll][ipt][2], dNdJetPt[coll][ipt][0] , scaleFactor); 
      
      if (  coll != kPA )  { // Iaa is only for pp and PbPb
	dNdIaa[coll][ipt][2] = (TH1D*)dNdIaa[coll][ipt][1]->Clone(Form("%s_uncertainty", dNdIaa[coll][ipt][1]->GetName()));
	calUncert( dNdIaa[coll][ipt][2], dNdIaa[coll][ipt][0], scaleFactor);
	
      }
      
      dNdXjg[coll][ipt][2] = (TH1D*)dNdXjg[coll][ipt][1]->Clone(Form("%s_uncertainty", dNdXjg[coll][ipt][1]->GetName()));
      calUncert( dNdXjg[coll][ipt][2], dNdXjg[coll][ipt][0], scaleFactor);

    }
    meanJetPt[coll][2] = (TH1D*)meanJetPt[coll][1]->Clone(Form("%s_uncertainty", meanJetPt[coll][1]->GetName()) );
    calUncert( meanJetPt[coll][2], meanJetPt[coll][0], scaleFactor) ;

    meanXjg[coll][2] = (TH1D*)meanXjg[coll][1]->Clone(Form("%s_uncertainty", meanXjg[coll][1]->GetName()) );
    calUncert( meanXjg[coll][2], meanXjg[coll][0], scaleFactor) ;
    
    meanRjg[coll][2] = (TH1D*)meanRjg[coll][1]->Clone(Form("%s_uncertainty", meanRjg[coll][1]->GetName() ) );
    calUncert( meanRjg[coll][2], meanRjg[coll][0], scaleFactor) ;
    
  }

  // Subtract 1 from each bin... So 0 = no uncertainty 
 
  for ( int coll = 1 ; coll<=4 ; coll++) {
    for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
      Subtract1(dNdJetPt[coll][ipt][2]);
      Subtract1(dNdXjg[coll][ipt][2]);
      if (  coll != kPA )
	Subtract1(dNdIaa[coll][ipt][2]);
    }
    Subtract1(meanJetPt[coll][2]);
    Subtract1(meanXjg[coll][2]);
    Subtract1(meanRjg[coll][2]);
  }
  
  /// FIT!!
  // dNdJetPt :                                                                                                                                
  TCanvas* c1 = new TCanvas("c1","",1200,1200);
  c1->Divide(nPtBin,4);
  TF1* fdNdJetPt[5][5];
  
  for ( int coll = 1 ; coll<=4 ; coll++) {   // On Sep 30, only pp and pbpb is studied.  pA will be added very soon                                                                                                                                                        
    for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
      c1->cd( ipt + nPtBin*(coll-1) );
      //      squareHist( dNdJetPt[coll][ipt]);                                                                                     
      //  squareRootHist( dNdJetPt[coll][ipt][2]);                                                                                       
      dNdJetPt[coll][ipt][2]->SetAxisRange(30,119,"X");
      dNdJetPt[coll][ipt][2]->SetAxisRange(-1,1,"Y");
      dNdJetPt[coll][ipt][2]->Draw();
  
      fdNdJetPt[coll][ipt] = new TF1(Form("%s_function",dNdJetPt[coll][ipt][2]->GetName()),"[0]+[1]*x +[2]*x*x",30,200);
      if ( ipt == 1 )
        dNdJetPt[coll][ipt][2]->Fit(fdNdJetPt[coll][ipt],"","",30,80);
      else if ( ipt == 2 )
        dNdJetPt[coll][ipt][2]->Fit(fdNdJetPt[coll][ipt],"","",30,80);
      else if ( ipt == 3 )
        dNdJetPt[coll][ipt][2]->Fit(fdNdJetPt[coll][ipt],"","",30,80);
      else
        dNdJetPt[coll][ipt][2]->Fit(fdNdJetPt[coll][ipt],"","",30,200);

      cout << "fdNdJetPt[coll][ipt]->Eval(210) = " << fdNdJetPt[coll][ipt]->Eval(210) << endl;

      dNdJetPtSmooth[coll][ipt][2] = (TH1D*)dNdJetPt[coll][ipt][2]->Clone(Form("%s_smooth",dNdJetPt[coll][ipt][2]->GetName()));
      fillCurve( fdNdJetPt[coll][ipt], dNdJetPtSmooth[coll][ipt][2] ) ;
    }
  }

  TCanvas* c2 = new TCanvas("c2","",1200,1200);
  c2->Divide(nPtBin,4);
  TF1* fdNdXjg[5][5];
  for ( int coll = 1 ; coll<=4 ; coll++) {   // On Sep 30, only pp and pbpb is studied.  pA will be added very soon       
    for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
      c2->cd( ipt + nPtBin*(coll-1) );
      //      squareHist( dNdXjg[coll][ipt]);                                                                                                  
      //      squareRootHist( dNdXjg[coll][ipt]);                                                                                              
      dNdXjg[coll][ipt][2]->SetAxisRange(0,2,"X");
      dNdXjg[coll][ipt][2]->SetAxisRange(-1,1,"Y");
      dNdXjg[coll][ipt][2]->Draw();
      fdNdXjg[coll][ipt] = new TF1(Form("%s_function",dNdXjg[coll][ipt][2]->GetName()),"[0]+[1]*x +[2]*x*x",0,2);
      if ( ipt == 1 )
        dNdXjg[coll][ipt][2]->Fit(fdNdXjg[coll][ipt],"","",.6,1.5);
      else if ( ipt == 2 )
        dNdXjg[coll][ipt][2]->Fit(fdNdXjg[coll][ipt],"","",.6,1.5);
      else if ( ipt == 3 )
        dNdXjg[coll][ipt][2]->Fit(fdNdXjg[coll][ipt],"","",.6,1.2);
      else
        dNdXjg[coll][ipt][2]->Fit(fdNdXjg[coll][ipt],"","",.6,1.2);
      cout << "fdNdXjg[coll][ipt]->Eval(210) = " << fdNdXjg[coll][ipt]->Eval(210) << endl;
      dNdXjgSmooth[coll][ipt][2] = (TH1D*)dNdXjg[coll][ipt][2]->Clone(Form("%s_smooth",dNdXjg[coll][ipt][2]->GetName()));
      fillCurve( fdNdXjg[coll][ipt], dNdXjgSmooth[coll][ipt][2] ) ;


    }
  }
  
  
  // dNIaa                                                                            
  TF1* fdNdIaa[5][5];
  TCanvas* c3 = new TCanvas("c3","",1200,1200);
  c3->Divide(nPtBin,3);
  for ( int coll = 1 ; coll<=3 ; coll++) {  
    for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
      c3->cd( ipt + nPtBin*(coll-1) );
      //      squareHist( dNdIaa[coll][ipt][2]);                                         
      //      squareRootHist( dNdIaa[coll][ipt][2]);                                     
      dNdIaa[coll][ipt][2]->SetAxisRange(30,119,"X");
      dNdIaa[coll][ipt][2]->SetAxisRange(-1,1,"Y");
      dNdIaa[coll][ipt][2]->Draw();
      fdNdIaa[coll][ipt] = new TF1(Form("%s_function",dNdIaa[coll][ipt][2]->GetName()),"[0]+[1]*x +[2]*x*x",0,2);
      if ( ipt == 1 )
        dNdIaa[coll][ipt][2]->Fit(fdNdIaa[coll][ipt],"","",30,120);
      else if ( ipt == 2 )
        dNdIaa[coll][ipt][2]->Fit(fdNdIaa[coll][ipt],"","",30,120);
      else if ( ipt == 3 )
        dNdIaa[coll][ipt][2]->Fit(fdNdIaa[coll][ipt],"","",30,120);
      else
        dNdIaa[coll][ipt][2]->Fit(fdNdIaa[coll][ipt],"","",30,120);
    
      cout << "fdNdIaa[coll][ipt]->Eval(210) = " << fdNdIaa[coll][ipt]->Eval(210) << endl;
      dNdIaaSmooth[coll][ipt][2] = (TH1D*)dNdIaa[coll][ipt][2]->Clone(Form("%s_smooth",dNdIaa[coll][ipt][2]->GetName()));
      fillCurve( fdNdIaa[coll][ipt], dNdIaaSmooth[coll][ipt][2] ) ;

    }
  }





  TString outname = fname2.ReplaceAll("resultHistograms", "relativeSys_dueTo");
  TFile * fSysResults = new TFile(outname,"recreate");
  
  
  for ( int coll = 1 ; coll<=4 ; coll++) {
    for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
      dNdJetPt[coll][ipt][2]->Write();
      dNdXjg[coll][ipt][2]->Write();
      dNdJetPtSmooth[coll][ipt][2]->Write();
      dNdXjgSmooth[coll][ipt][2]->Write();
      if (  coll != kPA ) {
	dNdIaa[coll][ipt][2]->Write();
	dNdIaaSmooth[coll][ipt][2]->Write();

      }
    }
    meanJetPt[coll][2]->Write();
    meanXjg[coll][2]->Write();
    meanRjg[coll][2]->Write();
  }
  
  fSysResults->Close();
  
  
}
 
