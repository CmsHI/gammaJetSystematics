/////////////////////////////////////////////////////////////////// 
// forest2yskim.C                                                //
// Creator : Yongsun Kim (KU), jazzitup@korea.ac.kr              //
// Function : Transform hiForest files into yskim file           //
// yskims for MinBias1, Minbias2 and photon jet skims            //
///////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////// 
#include "commonUtilitySys.h"
#include <TRandom3.h>
#include <TFile.h>


void systematicsByJetEnergy(int option = 1) { 
  // option : 1 = energy scale +2%,   2 = energy scale -2%,   3 = energy smearing 10% 
  
  cout << "hello" << endl;
  int nLoop = 1000000;
  
  TRandom3 rGaus;
  /*  TCanvas* cg=  new TCanvas("cg","",500,500);
  TH1D* htest= new TH1D("htest","",200,0,2);
  for (int ii=0;ii<=100000;ii++)  htest->Fill(rGaus.Gaus(1,0.1));
  htest->Draw();*/

  const int kPP = 1;
  const int kHIcentral =  2;
  const int kHIperipheral = 3;
  const int kPA = 4;
  const int nPtBin = 4;  
  double ptBin[5] = {40, 50,60,80,9999};
  
  TH1D* dNdJetPt[5][10][4];   //[coll][pt][vari]   vari : 0 = Original,   1 : Fit histogram,  2: after variation,  3: Ratio
  TH1D* dNdXjg[5][10][4]; 
  TF1* fJetPt[5][10]; 
  TF1* fXjg[5][10]; 
 
  TFile*  f = new TFile("resultHistograms/resultHistograms_nominal_Jet20GeV_functionAdded.root");
  
  for ( int coll = 1 ; coll<=4 ; coll++) {   // On Sep 30, only pp and pbpb is studied.  pA will be added very soon
    TString collName;
    if ( coll == kPP )  collName = "pp";
    else if ( coll == kPA )  collName = "ppb";
    else if ( coll == kHIcentral )  collName = "pbpb_centralityBin1";
    else if ( coll == kHIperipheral )  collName = "pbpb_centralityBin2";
    
    for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) { 
      dNdJetPt[coll][ipt][0] = (TH1D*)f->Get(Form("dNdJetPt_%s_ptBin%d", collName.Data(), ipt ) );
      dNdXjg[coll][ipt][0] = (TH1D*)f->Get(Form("dNdXjg_%s_ptBin%d", collName.Data(), ipt ) );
      fJetPt[coll][ipt] = (TF1*)dNdJetPt[coll][ipt][0]->GetFunction("f1");
      fXjg[coll][ipt] = (TF1*)dNdXjg[coll][ipt][0]->GetFunction("f1");
    }
  }
  
  // dNdJetPt : 
  TCanvas* c1 = new TCanvas("c1","",1200,1200);
  c1->Divide(nPtBin,4);
  for ( int coll = 1 ; coll<=4 ; coll++) {   // On Sep 30, only pp and pbpb is studied.  pA will be added very soon                                         
    for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
      c1->cd( ipt + nPtBin*(coll-1) );
      
      
      dNdJetPt[coll][ipt][1] = (TH1D*)dNdJetPt[coll][ipt][0]->Clone(Form("%s_fitHist",dNdJetPt[coll][ipt][0]->GetName()));
      dNdJetPt[coll][ipt][2] = (TH1D*)dNdJetPt[coll][ipt][0]->Clone(Form("%s_energyShifted",dNdJetPt[coll][ipt][0]->GetName()));
      dNdJetPt[coll][ipt][1]->Reset();
      dNdJetPt[coll][ipt][2]->Reset();
      for ( int i=0;i<=nLoop;i++) {
	float newVal = fJetPt[coll][ipt]->GetRandom(); 
	dNdJetPt[coll][ipt][1]->Fill (  newVal );
	if ( option == 1) {
	  dNdJetPt[coll][ipt][2]->Fill (  newVal * 1.02 ); // No variation
	}
	else if  (option ==2 ) {
	  dNdJetPt[coll][ipt][2]->Fill (  newVal * 0.98 ); // No variation
	}
	else if  (option ==3 ) {
	  dNdJetPt[coll][ipt][2]->Fill (  newVal * rGaus.Gaus( 1 , 0.1 ) ); // No variation
	}


      }	
      float xx = dNdJetPt[coll][ipt][1]->GetBinCenter(8);
      dNdJetPt[coll][ipt][1]->Scale( fJetPt[coll][ipt]->Eval(xx) / dNdJetPt[coll][ipt][1]->GetBinContent(8));
      dNdJetPt[coll][ipt][2]->Scale( fJetPt[coll][ipt]->Eval(xx) / dNdJetPt[coll][ipt][2]->GetBinContent(8));
      dNdJetPt[coll][ipt][1]->SetAxisRange(0,0.05,"Y");
      dNdJetPt[coll][ipt][1]->Draw();
      handsomeTH1(dNdJetPt[coll][ipt][2],4);
      dNdJetPt[coll][ipt][2]->Draw("same");
      
      dNdJetPt[coll][ipt][3] = (TH1D*)dNdJetPt[coll][ipt][2]->Clone(Form("%s_uncertainty",dNdJetPt[coll][ipt][0]->GetName()));
      dNdJetPt[coll][ipt][3]->Add( dNdJetPt[coll][ipt][1], -1 );
      dNdJetPt[coll][ipt][3]->Divide( dNdJetPt[coll][ipt][1]);
    }
  }
  
  
  
  
  TCanvas* c2 = new TCanvas("c2","",1200,1200);
  c2->Divide(nPtBin,4);
  for ( int coll = 1 ; coll<=4 ; coll++) {   
    for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
      c2->cd( ipt + nPtBin*(coll-1) );

      dNdXjg[coll][ipt][1] = (TH1D*)dNdXjg[coll][ipt][0]->Clone(Form("%s_fitHist",dNdXjg[coll][ipt][0]->GetName()));
      dNdXjg[coll][ipt][2] = (TH1D*)dNdXjg[coll][ipt][0]->Clone(Form("%s_energyShifted",dNdXjg[coll][ipt][0]->GetName()));
      dNdXjg[coll][ipt][1]->Reset();
      dNdXjg[coll][ipt][2]->Reset();
      for ( int i=0;i<=nLoop;i++) {
	float newVal = fXjg[coll][ipt]->GetRandom(); 
	dNdXjg[coll][ipt][1]->Fill (  newVal );
	if ( option == 1) {
	  dNdXjg[coll][ipt][2]->Fill (  newVal * 1.02 ); // No variation
	}
	else if  (option ==2 ) {
	  dNdXjg[coll][ipt][2]->Fill (  newVal * 0.98 ); // No variation
	}
	else if  (option ==3 ) {
	  dNdXjg[coll][ipt][2]->Fill (  newVal * rGaus.Gaus( 1 , 0.1 ) ); // No variation
	}

      }	
      
      float xx = dNdXjg[coll][ipt][1]->GetBinCenter(8);
      dNdXjg[coll][ipt][1]->Scale( fXjg[coll][ipt]->Eval(xx) / dNdXjg[coll][ipt][1]->GetBinContent(8));
      dNdXjg[coll][ipt][2]->Scale( fXjg[coll][ipt]->Eval(xx) / dNdXjg[coll][ipt][2]->GetBinContent(8));
      dNdXjg[coll][ipt][1]->SetAxisRange(0,3,"Y");
      dNdXjg[coll][ipt][1]->Draw();
      fXjg[coll][ipt]->SetLineColor(1);
      fXjg[coll][ipt]->Draw("same");
      handsomeTH1(dNdXjg[coll][ipt][2],4);
      dNdXjg[coll][ipt][2]->Draw("same");

      dNdXjg[coll][ipt][3] = (TH1D*)dNdXjg[coll][ipt][2]->Clone(Form("%s_uncertainty",dNdXjg[coll][ipt][0]->GetName()));
      dNdXjg[coll][ipt][3]->Add( dNdXjg[coll][ipt][1], -1 );
      dNdXjg[coll][ipt][3]->Divide( dNdXjg[coll][ipt][1]);

    }
  }
  
  TFile* fout;
  if ( option == 1 ) 
    fout = new TFile("relativeSys/relativeSys_dueTo_jetEnergyScalePlus.root","recreate");
  else if ( option == 2 ) 
    fout = new TFile("relativeSys/relativeSys_dueTo_jetEnergyScaleMinus.root","recreate");
  else if ( option == 3 ) 
    fout = new TFile("relativeSys/relativeSys_dueTo_jetEnergySmearing.root","recreate");
  
  
  for ( int coll = 1 ; 
	coll<=4 ; coll++) {
    for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
      dNdXjg[coll][ipt][3]->Write();
      dNdJetPt[coll][ipt][3]->Write();

    }
  }  
  cout << " Simulation is done.   Calculating variation for option "  << option << "." << endl;
  fout->Close();
  
}


