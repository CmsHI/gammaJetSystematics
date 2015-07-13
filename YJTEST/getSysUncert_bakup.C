///////////////////////////////////////////////////////////////////                                                  
// getSysUncert.C                                                //                                                 
// Creator : Yongsun Kim (KU), kingmking@gmail.com               //
// Function : Compare histograms in two files and returns ratio  // 
// Modifier : Yeonju Go (KU), yeonjugo@gmail.com                 // 
///////////////////////////////////////////////////////////////////                                                  
///////////////////////////////////////////////////////////////////                                                  

#include "../commonUtilitySys.h"
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
        h1->SetBinError(j,0.0001);
        //h1->SetBinError(j,yyErr);
    }
}

void getSysUncert(   
        //TString fname1 = "nominal_vtxCentWeighted",
        TString fname1 = "nominal_vtxCentWeighted_jet20GeV",
        TString fname2 = "electronContamination",
        float scaleFactor= 1.0
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
    const int NCOLL = 4;
    //const int NCOLL = 3;
    double ptBin[nPtBin+1] = {40,50,60,80,9999}; 

    TH1D* dNdJetPt[5][5][3];  // [collision] [ ptbin]  [Before/After variation]

    TFile* f; 

    for ( int ifile = 0 ; ifile <= 1 ; ifile++ ) { 
        if ( ifile == 0 ) f = new TFile(Form("../../gammaJetAnalysis/drawFigures/resultHistograms_%s.root",fname1.Data()));
        else f = new TFile(Form("../../gammaJetAnalysis/drawFigures/resultHistograms_%s.root",fname2.Data()));

        for ( int coll = 1 ; coll<=NCOLL ; coll++) { 
            TString collName;
            if ( coll == kPP )  collName = "pp";
            else if ( coll == kPA )  collName = "ppb";
            else if ( coll == kHIcentral )  collName = "pbpb_centralityBin1";
            else if ( coll == kHIperipheral )  collName = "pbpb_centralityBin2";

            for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) { 
                dNdJetPt[coll][ipt][ifile] = (TH1D*)f->Get(Form("dNdJetPt_IaaBin_%s_ptBin%d", collName.Data(), ipt ) );
            }
        }
    }
    
    for ( int coll = 1 ; coll<=NCOLL ; coll++) {   
        for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
            dNdJetPt[coll][ipt][2] = (TH1D*)dNdJetPt[coll][ipt][1]->Clone(Form("%s_uncertainty", dNdJetPt[coll][ipt][1]->GetName()));
            calUncert( dNdJetPt[coll][ipt][2], dNdJetPt[coll][ipt][0] , scaleFactor); 
            Subtract1(dNdJetPt[coll][ipt][2]);
        }
    }

    TCanvas* c1 = new TCanvas("c1","",300*nPtBin,300*nPtBin);
    c1->Divide(nPtBin,NCOLL);
    for ( int coll = 1 ; coll<=NCOLL ; coll++) { 
        for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
            c1->cd( ipt + nPtBin*(coll-1) );
            dNdJetPt[coll][ipt][2]->GetYaxis()->SetTitle("Relative Sys Uncert.");
            dNdJetPt[coll][ipt][2]->SetAxisRange(30,150,"X");
            dNdJetPt[coll][ipt][2]->GetXaxis()->SetRangeUser(30,150);
            //dNdJetPt[coll][ipt][2]->SetAxisRange(0.0,2.0,"Y");
            dNdJetPt[coll][ipt][2]->SetAxisRange(-1.0,1.0,"Y");
            dNdJetPt[coll][ipt][2]->SetMarkerStyle(20);
            dNdJetPt[coll][ipt][2]->Draw("pl");
            //jumSun(30,1,150,1);
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
       }//ipt for loop
    }//coll for loop

    //c1->SaveAs(Form("pdf/Uncertainty_of_dndjetpt_by_%s.pdf",fname2.Data()));
    c1->SaveAs(Form("pdf/relativeSysDist_dNdJetPt_%s.pdf",fname2.Data()));
    TFile * fSysResults = new TFile(Form("relativeSys/relativeSys_dueTo_%s.root",fname2.Data()),"recreate");
    for ( int coll = 1 ; coll<=NCOLL ; coll++) {
        for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
            dNdJetPt[coll][ipt][2]->Write();
        }
    }
    fSysResults->Close();
}

