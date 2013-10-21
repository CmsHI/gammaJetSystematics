#include "commonUtilitySys.h"
#include <TRandom3.h>
#include <TFile.h>

void squareHist(TH1* h=0)
{
  Int_t nBins = h->GetNbinsX();
  for ( Int_t j=1; j<=nBins ;j++)
    { 
      float yy = h->GetBinContent(j);
      float err = h->GetBinError(j);
      h->SetBinContent(j, yy*yy);
      if ( yy ==0)   h->SetBinError (j,0);
      else 	     h->SetBinError  (j, 2*fabs(yy)*err);
    }
  
}

void squareRootHist(TH1* h=0)
{
  Int_t nBins = h->GetNbinsX();
  for ( Int_t j=1; j<=nBins ;j++)
    {
      float yy = h->GetBinContent(j);
      float err = h->GetBinError(j);
      if ( yy==0)  h->SetBinContent(j, sqrt(yy) );
      else         h->SetBinError  (j, err / (2*sqrt(yy)) );
    }
  
}


void smoothSys_20GeV(TString dirName="nominal_Jet20GeV") {
  cout << "hello" << endl;
  const int kPP = 1;
  const int kHIcentral =  2;
  const int kHIperipheral = 3;
  const int kPA = 4;
  const int nPtBin = 4;  
  double ptBin[5] = {40, 50,60,80,9999};
  
  TH1D* dNdJetPt[5][10];
  TH1D* dNdIaa[5][10]; 
  TH1D* dNdXjg[5][10]; 
 
  TFile*  f = new TFile(Form("resultHistograms/resultHistograms_%s.root",dirName.Data()));
  
  for ( int coll = 1 ; coll<=4 ; coll++) {   // On Sep 30, only pp and pbpb is studied.  pA will be added very soon
      TString collName;
      if ( coll == kPP )  collName = "pp";
      else if ( coll == kPA )  collName = "ppb";
      else if ( coll == kHIcentral )  collName = "pbpb_centralityBin1";
      else if ( coll == kHIperipheral )  collName = "pbpb_centralityBin2";
      
      for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) { 
	dNdJetPt[coll][ipt] = (TH1D*)f->Get(Form("dNdJetPt_%s_ptBin%d", collName.Data(), ipt ) );
	dNdXjg[coll][ipt] = (TH1D*)f->Get(Form("dNdXjg_%s_ptBin%d", collName.Data(), ipt ) );
      }
  }
  
  // dNdJetPt : 
  TCanvas* c1 = new TCanvas("c1","",1200,1200);
  c1->Divide(nPtBin,4);
  for ( int coll = 1 ; coll<=4 ; coll++) {   // On Sep 30, only pp and pbpb is studied.  pA will be added very soon                                         
    for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
      c1->cd( ipt + nPtBin*(coll-1) );
      //      squareHist( dNdJetPt[coll][ipt]);
      //  squareRootHist( dNdJetPt[coll][ipt]);
      dNdJetPt[coll][ipt]->SetAxisRange(0,0.05,"Y");
      dNdJetPt[coll][ipt]->SetAxisRange(20,200,"X");
      dNdJetPt[coll][ipt]->Draw();
      TF1* f1;
      if ( ((ipt == 4)||(ipt == 3) ) && ( (coll==kPA) || (coll==kPP) ) )  {
	f1 = new TF1("f1","[0]*exp(-[1]*(x-[2]))*(x-[2]) + [3]*exp(-[4]*(x-30)) ",20,200); 
	f1->SetParameter(0,0.01);
	f1->SetParameter(1,0.1);
	f1->SetParameter(2,1);
	f1->SetParameter(3,0.01);
	f1->SetParameter(4,0.02);
      }
      else   {
	f1= new TF1("f1","[0]*exp(-[1]*(x-[2]))*(x-[2]) ",20,200);
	f1->SetParameter(0,0.01);
	f1->SetParameter(1,0.1);
	f1->SetParameter(2,30);
      }
      //  TF1* f1= new TF1("f1","gaus",30,200);
      dNdJetPt[coll][ipt]->SetStats(0);
      dNdJetPt[coll][ipt]->Fit("f1","LL M","",20,200);
      dNdJetPt[coll][ipt]->Fit("f1","LL M","",20,200);
      dNdJetPt[coll][ipt]->Fit("f1","LL M","",20,200);
      dNdJetPt[coll][ipt]->Fit("f1","LL M","",20,200);
      dNdJetPt[coll][ipt]->Fit("f1","LL M","",20,200);
      dNdJetPt[coll][ipt]->Fit("f1","LL M","",20,200);
      
      if ( coll == 1 )  {
	double dx1=0.15;
	if ( ipt == nPtBin )
	  drawText(Form("p_{T}^{#gamma} > %dGeV, ", (int)ptBin[ipt-1]), 0.12+dx1+0.25,0.85,1,15);
	else
	  drawText(Form("%dGeV < p_{T}^{#gamma} < %dGeV, ", (int)ptBin[ipt-1], (int)ptBin[ipt]), 0.12+dx1,0.85,1,15);
      }
    if ( ipt == 1 )  {
      double dx1=0.15;
	if ( coll == 1 ) 	drawText("pp", 0.2+dx1+0.25,0.75,1,15);
	else if ( coll == 2 ) 	drawText("PbPb 0-30%", 0.2+dx1+0.25,0.75,1,15);
	else if ( coll == 3 ) 	drawText("PbPb 30-100%", 0.2+dx1+0.25,0.75,1,15);
	else if ( coll == 4 ) 	drawText("pPb", 0.2+dx1+0.25,0.75,1,15);

    }
    
    }
    
    
  }
  
  c1->SaveAs("c1.gif");
  // dNdX
  TCanvas* c2 = new TCanvas("c2","",1200,1200);
  c2->Divide(nPtBin,4);
  for ( int coll = 1 ; coll<=4 ; coll++) {   // On Sep 30, only pp and pbpb is studied.  pA will be added very soon                                         
    for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
      c2->cd( ipt + nPtBin*(coll-1) );
      //      squareHist( dNdXjg[coll][ipt]);
      //      squareRootHist( dNdXjg[coll][ipt]);
      dNdXjg[coll][ipt]->SetAxisRange(0,3,"Y");
      dNdXjg[coll][ipt]->SetAxisRange(0,2,"X");
      dNdXjg[coll][ipt]->Draw();
      //    TF1* f1= new TF1("f1","[0]*exp(-[1]*(x-[2]))*(x-[2])",30,200);
      TF1* f1= new TF1("f1","gaus",20,200);
      float rangeLow(0),  rangeHigh(2);
      if ( ipt == 1 ) {  
	rangeLow = 20/50.;
	f1= new TF1("f1","[0]*exp(-[1]*(x-[2]))*(x-[2]) ",0,2);
	f1->SetParameter(0,30);
	f1->SetParameter(1,6);
        f1->SetParameter(2,0.6);
     
      }
      else if ( ipt == 2 ) { 
	rangeLow = 0.2;
      }
      else if ( ipt == 3 ) rangeLow = 0.2;
      else                  rangeLow = 0;
      
      dNdXjg[coll][ipt]->SetStats(0);
      dNdXjg[coll][ipt]->Fit("f1","LL M","",rangeLow,rangeHigh);
      dNdXjg[coll][ipt]->Fit("f1","LL M","",rangeLow,rangeHigh);
      dNdXjg[coll][ipt]->Fit("f1","LL M","",rangeLow,rangeHigh);
      dNdXjg[coll][ipt]->Fit("f1","LL M","",rangeLow,rangeHigh);
      dNdXjg[coll][ipt]->Fit("f1","LL M","",rangeLow,rangeHigh);
      dNdXjg[coll][ipt]->Fit("f1","LL M","",rangeLow,rangeHigh);
      
      if ( coll == 1 )  {
	double dx1=0.15;
	if ( ipt == nPtBin )
	  drawText(Form("p_{T}^{#gamma} > %dGeV, ", (int)ptBin[ipt-1]), 0.12+dx1+0.25,0.85,1,15);
	else
	  drawText(Form("%dGeV < p_{T}^{#gamma} < %dGeV, ", (int)ptBin[ipt-1], (int)ptBin[ipt]), 0.12+dx1,0.85,1,15);
      }
      
      if ( ipt == 1 )  {
	double dx1=0.15;
	if ( coll == 1 ) 	drawText("pp", 0.2+dx1+0.25,0.75,1,15);
	else if ( coll == 2 ) 	drawText("PbPb 0-30%", 0.2+dx1+0.25,0.75,1,15);
	else if ( coll == 3 ) 	drawText("PbPb 30-100%", 0.2+dx1+0.25,0.75,1,15);
	else if ( coll == 4 ) 	drawText("pPb", 0.2+dx1+0.25,0.75,1,15);
      }
      
    }
  }
  c2->SaveAs("c2.gif");
  
  TFile*  fout = new TFile(Form("resultHistograms/resultHistograms_%s_functionAdded.root",dirName.Data()), "recreate");
  for ( int coll = 1 ; coll<=4 ; coll++) { 
    for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
      dNdXjg[coll][ipt]->Write(); 
      dNdJetPt[coll][ipt]->Write(); 

      
    }
  }  
}
 

