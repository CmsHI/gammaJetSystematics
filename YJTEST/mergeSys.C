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

void addValueToAllBin(TH1* h=0, float val=1)
{
  Int_t nBins = h->GetNbinsX();
  for ( Int_t j=1; j<=nBins ;j++)
    {
      float yy = h->GetBinContent(j);
      h->SetBinContent(j, yy + val);
    }

}


void mergeSys() {
    const int kPP = 1;
    const int kHIcentral =  2;
    const int kHIperipheral = 3;
    const int kPA = 4;
    const int nPtBin = 4;  
    const int NCOLL = 3;  
    double ptBin[nPtBin+1] = {40,50,60,80,9999};

    const int nRptBin[4] = {4,4,5,5};
    double ratioPtBin[4][10] = {{30,40,50,70,150},
        {30,40,50,70,150},
        {30,40,50,70,100,150},
        {30,40,50,70,100,150}};
    double ratioPtBin1[4][10] = {{30,40,50,68,105},
        {30,40,50,68,105},
        {30,40,50,68,100,130},
        {30,40,50,68,100,130}};


    TH1D* dNdJetPt_origin[5][5][10]; // [collision] [ptbin] [sys. category]
    TH1D* dNdJetPt[5][5][10];
    TH1D* hOutput[5][5][10]; //Iaa Ratio Sys
    TFile* f; 

    int nFile  = 7;
    //int nFile  = 6;
    for ( int ifile = 1 ; ifile <= nFile ; ifile++ ) { 
        if ( ifile == 1 )       f = new TFile("relativeSys/relativeSys_dueTo_photonEnergyScale.root");
        else if ( ifile == 2 )  f = new TFile("relativeSys/relativeSys_dueTo_noJetResCorr.root");
        else if ( ifile == 3 )  f = new TFile("relativeSys/relativeSys_dueTo_isolation.root");
        else if ( ifile == 4 )  f = new TFile("relativeSys/relativeSys_dueTo_electronContamination.root");
        else if ( ifile == 5 )  f = new TFile("relativeSys/relativeSys_dueTo_photonPurityVaried.root");
        //else if ( ifile == 6 )  f = new TFile("relativeSys/relativeSys_dueTo_smearingNscale.root");
        else if ( ifile == 6 )  f = new TFile("relativeSys/relativeSys_dueTo_jetEnergyScale.root");
        else if ( ifile == 7 )  f = new TFile("relativeSys/relativeSys_dueTo_jetEnergyResolution.root");
      
        for ( int coll = 1 ; coll<=NCOLL ; coll++) { 
            TString collName;
            if ( coll == kPP )  collName = "pp";
            else if ( coll == kPA )  collName = "ppb";
            else if ( coll == kHIcentral )  collName = "pbpb_centralityBin1";
            else if ( coll == kHIperipheral )  collName = "pbpb_centralityBin2";

            for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) { 
                dNdJetPt_origin[coll][ipt][ifile] = (TH1D*)f->Get(Form("dNdJetPt_IaaBin_%s_ptBin%d_uncertainty", collName.Data(), ipt ) );
                dNdJetPt_origin[coll][ipt][ifile] -> SetName(Form("dNdJetPt_IaaBin_%s_ptBin%d_uncertainty_origin", collName.Data(), ipt ) );
                dNdJetPt[coll][ipt][ifile] = (TH1D*)dNdJetPt_origin[coll][ipt][ifile] -> Rebin(nRptBin[ipt-1], Form("dNdJetPt_IaaBin_%s_ptBin%d_uncertainty", collName.Data(), ipt), ratioPtBin[ipt-1] );
            }
        }
    }
    // Divide the uncertainties
    for ( int ifile = 1 ; ifile <= nFile ; ifile++ ) {
        for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {

            hOutput[kHIcentral][ipt][ifile] = (TH1D*)dNdJetPt[kHIcentral][ipt][ifile]->Clone(Form("dNdJetPt_ratio_centralityBin1_ptBin%d_uncertainty", ipt ) );
            hOutput[kHIperipheral][ipt][ifile] = (TH1D*)dNdJetPt[kHIperipheral][ipt][ifile]->Clone(Form("dNdJetPt_ratio_centralityBin2_ptBin%d_uncertainty", ipt ) );
            hOutput[kPP][ipt][ifile] = (TH1D*)dNdJetPt[kPP][ipt][ifile]->Clone(Form("dNdJetPt_pp_ptBin%d_uncertainty", ipt ) );

            // Add unity
            addValueToAllBin(hOutput[kHIcentral][ipt][ifile],    1);
            addValueToAllBin(hOutput[kHIperipheral][ipt][ifile], 1);
            addValueToAllBin(hOutput[kPP][ipt][ifile],           1);

            hOutput[kHIcentral][ipt][ifile]->Divide(hOutput[kPP][ipt][ifile]);
            hOutput[kHIperipheral][ipt][ifile]->Divide(hOutput[kPP][ipt][ifile]);
            addValueToAllBin(hOutput[kHIcentral][ipt][ifile],    -1);
            addValueToAllBin(hOutput[kHIperipheral][ipt][ifile], -1);
        }
    }


/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
// dNdJetPt relative uncertainty calculation
    TCanvas* c1 = new TCanvas("c1","",1200,900);
    c1->Divide(nPtBin,NCOLL);
    for ( int coll = 1 ; coll<=NCOLL ; coll++) {   
        for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
            c1->cd( ipt + nPtBin*(coll-1) );
            dNdJetPt[coll][ipt][0] = (TH1D*)dNdJetPt[coll][ipt][1]->Clone(Form("%s_merged",dNdJetPt[coll][ipt][1]->GetName() ) );
            dNdJetPt[coll][ipt][0]->Reset();
            for ( int ifile = 1 ; ifile <= nFile ; ifile++ ) {
                squareHist( dNdJetPt[coll][ipt][ifile] );
                dNdJetPt[coll][ipt][0]->Add(dNdJetPt[coll][ipt][ifile]);
            }
            squareRootHist(dNdJetPt[coll][ipt][0]);
           
            dNdJetPt[coll][ipt][0]->GetYaxis()->SetTitle("Total Rel. Sys. Uncert.");
            dNdJetPt[coll][ipt][0]->SetAxisRange(30,150,"X");
            dNdJetPt[coll][ipt][0]->GetXaxis()->SetRangeUser(30,150);
            dNdJetPt[coll][ipt][0]->SetAxisRange(-1.0,1.0,"Y");
            dNdJetPt[coll][ipt][0]->SetMarkerStyle(20);
            dNdJetPt[coll][ipt][0]->Draw("pl");
            jumSun(30,0,150,0); 

            /////////////////////////////////////////////////////////////////
            // COSMETIC
            TString collName;
            if ( coll == kPP )  collName = "pp";
            else if ( coll == kPA )  collName = "ppb";
            else if ( coll == kHIcentral )  collName = "pbpb 0-30%";
            else if ( coll == kHIperipheral )  collName = "pbpb 30-100%";

            double dx1=0.18;
            if(coll==1){ // photon pT, drawText("text", xp, yp, color, size)
                if ( ipt == nPtBin )
                    drawText(Form("p_{T}^{#gamma} > %dGeV ", (int)ptBin[ipt-1]), 0.07+dx1+0.1,0.9,1,16);
                else if ( ipt == 1)
                    drawText(Form("%dGeV < p_{T}^{#gamma} < %dGeV ", (int)ptBin[ipt-1], (int)ptBin[ipt]), 0.10+dx1,0.9,1,16);
                else
                    drawText(Form("%dGeV < p_{T}^{#gamma} < %dGeV ", (int)ptBin[ipt-1], (int)ptBin[ipt]), 0.10+dx1,0.9,1,16);
            }
            if(ipt==1) drawText(collName, 0.10+dx1, 0.7, 1, 16); //collision name

        }
    }
    c1->SaveAs("pdf/relativeSysDist_dNdJetPt_total.pdf");

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
// Ratio(Iaa) relative uncertainty calculation

    TCanvas* c2 = new TCanvas("c2","",1200,600);
    c2->Divide(nPtBin,2);
 
    for ( int coll = 2 ; coll<=NCOLL ; coll++) {
        if   ( ( coll != kHIcentral) && ( coll != kHIperipheral ) )
            continue;
        for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
            c2->cd( ipt + nPtBin*(coll-2) );
            hOutput[coll][ipt][0] = (TH1D*)hOutput[coll][ipt][1]->Clone(Form("%s_merged",hOutput[coll][ipt][1]->GetName() ) );
            hOutput[coll][ipt][0]->Reset();
            for ( int ifile = 1 ; ifile <= nFile ; ifile++ ) {
                squareHist( hOutput[coll][ipt][ifile] );
                hOutput[coll][ipt][0]->Add(hOutput[coll][ipt][ifile]);
            }
            squareRootHist(hOutput[coll][ipt][0]);
           
            hOutput[coll][ipt][0]->GetYaxis()->SetTitle("Total Rel. Sys Uncert.");
            hOutput[coll][ipt][0]->SetAxisRange(30,150,"X");
            hOutput[coll][ipt][0]->GetXaxis()->SetRangeUser(30,150);
            hOutput[coll][ipt][0]->SetAxisRange(-1.0,1.0,"Y");
            hOutput[coll][ipt][0]->SetMarkerStyle(20);
            hOutput[coll][ipt][0]->Draw("pl");
            jumSun(30,0,150,0); 

            /////////////////////////////////////////////////////////////////
            // COSMETIC
            TString collName;
            if ( coll == kHIcentral )  collName = "pbpb/pp 0-30%";
            else if ( coll == kHIperipheral )  collName = "pbpb/pp 30-100%";

            double dx1=0.18;
            if(coll==2){ // photon pT, drawText("text", xp, yp, color, size)
                if ( ipt == nPtBin )
                    drawText(Form("p_{T}^{#gamma} > %dGeV ", (int)ptBin[ipt-1]), 0.07+dx1+0.1,0.9,1,16);
                else if ( ipt == 1)
                    drawText(Form("%dGeV < p_{T}^{#gamma} < %dGeV ", (int)ptBin[ipt-1], (int)ptBin[ipt]), 0.10+dx1,0.9,1,16);
                else
                    drawText(Form("%dGeV < p_{T}^{#gamma} < %dGeV ", (int)ptBin[ipt-1], (int)ptBin[ipt]), 0.10+dx1,0.9,1,16);
            }
            if(ipt==1) drawText(collName, 0.10+dx1, 0.7, 1, 16); //collision name
        }
    }
    c2->SaveAs("pdf/relativeSysDist_Iaa_total.pdf");

    TFile * fSysResults = new TFile("relativeSys/relativeSys_merged.root","recreate");
    for ( int coll = 1 ; coll<=NCOLL ; coll++) { 
        for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
            dNdJetPt[coll][ipt][0]->Write();
            if( ( coll == kHIcentral) || ( coll == kHIperipheral ) ) hOutput[coll][ipt][0]->Write();
        }
    }
    fSysResults->Close();
}
