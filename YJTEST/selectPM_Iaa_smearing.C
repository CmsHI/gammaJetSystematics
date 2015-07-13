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

void selectPM_Iaa_smearing(TString fname1 = "photonEnergyScaleMinus",
        TString fname2 = "photonEnergyScalePlus", 
        TString fOutname = "photonEnergyScale") 
{
    cout << "===============================================================================" << endl;
    cout << " Select Plus Minus : " << fname1 <<"   VS  " << fname2 << endl;
    cout << "===============================================================================" << endl;

    const int kPP = 1;
    const int kHIcentral =  2;
    const int kHIperipheral = 3;
    const int kPA = 4;
    const int nPtBin = 4;  
    const int nfile = 2;
    const int NCOLL = 3;
    double ptBin[nPtBin+1] = {40,50,60,80,9999};

    TH1D* dNdJetPt[5][5][10];  // [collision] [ ptbin]  [Before/After variation]
    TFile* f; 

    for ( int ifile = 1 ; ifile <= nfile ; ifile++ ) { 
        if ( ifile == 1 )       f = new TFile(Form("relativeSys/relativeSys_dueTo_%s.root",fname1.Data()));
        else if ( ifile == 2 )  f = new TFile(Form("relativeSys/relativeSys_dueTo_%s.root",fname2.Data()));
        for ( int coll = 1 ; coll<=NCOLL ; coll++) { 
            TString collName;
            if ( coll == kPP )  collName = "pp";
            else if ( coll == kPA )  collName = "ppb";
            else if ( coll == kHIcentral )  collName = "pbpb_centralityBin1";
            else if ( coll == kHIperipheral )  collName = "pbpb_centralityBin2";

            for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) { 
                dNdJetPt[coll][ipt][ifile] = (TH1D*)f->Get(Form("dNdJetPt_IaaBin_%s_ptBin%d_uncertainty", collName.Data(), ipt ) );
            }//ipt
        }//coll 
    }//ifile
    TCanvas* c1 = new TCanvas("c1","",1200,900);
    c1->Divide(nPtBin,NCOLL);
    // relative uncertainty calculation
    for ( int coll = 1 ; coll<=NCOLL ; coll++) {  
        for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
            c1->cd( ipt + nPtBin*(coll-1) );
            dNdJetPt[coll][ipt][0] = (TH1D*)dNdJetPt[coll][ipt][1]->Clone(dNdJetPt[coll][ipt][1]->GetName() );
            dNdJetPt[coll][ipt][0]->Reset();
            selectLargeValue(dNdJetPt[coll][ipt][1], dNdJetPt[coll][ipt][2]);
            dNdJetPt[coll][ipt][0]->Add(dNdJetPt[coll][ipt][1]); 

            dNdJetPt[coll][ipt][0]->GetYaxis()->SetTitle("Relative Sys Uncert.");
            dNdJetPt[coll][ipt][0]->SetAxisRange(30,150,"X");
            dNdJetPt[coll][ipt][0]->GetXaxis()->SetRangeUser(30,150);
            dNdJetPt[coll][ipt][0]->SetAxisRange(-1.0,1.0,"Y");
            dNdJetPt[coll][ipt][0]->SetMarkerStyle(20);
            dNdJetPt[coll][ipt][0]->Draw("pl");
            jumSun(30,0,150,0);

            /////////////////////////////////////////////////////////////////
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
    c1->SaveAs(Form("pdf/relativeSysDist_dNdJetPt_%s.pdf",fOutname.Data())); 
    TFile * fSysResults = new TFile(Form("relativeSys/relativeSys_dueTo_%s.root",fOutname.Data()),"recreate");
    for ( int coll = 1 ; coll<=NCOLL ; coll++) { 
        for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
            dNdJetPt[coll][ipt][0]->Write();
        }
    }
    fSysResults->Close();
}
