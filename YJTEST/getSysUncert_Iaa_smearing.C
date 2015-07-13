///////////////////////////////////////////////////////////////////                                                  
// getSysUncert.C                                                //                                                 
// Creator : Yongsun Kim (KU), kingmking@gmail.com               //
// Function : Compare histograms in two files and returns ratio  // 
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
void getSysUncert_Iaa_smearing( 
        TString fname2 = "scale0.98",
        TString fOutName = "jetEnergyScaleMinus",
        float scaleFactor= 1.0  // The non-unity scale factor is for electron : 0.25
        )
{
    cout << "===============================================================================" << endl;
    cout << " Get Uncertainty : " << fname2 << endl;
    cout << "===============================================================================" << endl;

    const int kPP = 1;
    const int kHIcentral =  2;
    const int kHIperipheral = 3;
    const int kPA = 4;
    const int nPtBin = 4;  
    const int NCOLL = 4;  
    double ptBin[nPtBin+1] = {40,50,60,80,9999};

    TH1D* dNdJetPt_IaaBin[5][5];  // [collision] [ ptbin] 
    TH1D* dNdJetPt_varied[5][5];  // [collision] [ ptbin]
    TH1D* dNdJetPt_uncert[5][5];  // [collision] [ ptbin]
    TF1* fJetPt[5][5];  // [collision] [ ptbin]
     
    TFile* f; 
    f = new TFile( Form("resultHistograms/resultFunction_%s.root",fname2.Data()));

    for ( int coll = 1 ; coll<=NCOLL ; coll++) { 
        TString collName;
        if ( coll == kPP )  collName = "pp";
        else if ( coll == kPA )  collName = "ppb";
        else if ( coll == kHIcentral )  collName = "pbpb_centralityBin1";
        else if ( coll == kHIperipheral )  collName = "pbpb_centralityBin2";

        for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) { 
            dNdJetPt_IaaBin[coll][ipt] = (TH1D*)f->Get(Form("dNdJetPt_%s_ptBin%d_IaaBin", collName.Data(), ipt ) );
            dNdJetPt_varied[coll][ipt] = (TH1D*)f->Get(Form("dNdJetPt_%s_ptBin%d_varied", collName.Data(), ipt ) );
            fJetPt[coll][ipt] = (TF1*)f->Get(Form("fb_coll%d_pt%d_origin",coll,ipt));

            dNdJetPt_uncert[coll][ipt] = (TH1D*)dNdJetPt_varied[coll][ipt]->Clone(Form("dNdJetPt_IaaBin_%s_ptBin%d_uncertainty", collName.Data(), ipt));
        }
    }

    for ( int coll = 1 ; coll<=NCOLL ; coll++) {   
        for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
            calUncert(dNdJetPt_uncert[coll][ipt],dNdJetPt_IaaBin[coll][ipt],scaleFactor); 
            Subtract1(dNdJetPt_uncert[coll][ipt]);
        }
    }

    TCanvas* c1 = new TCanvas("c1","",300*nPtBin,300*NCOLL);
    c1->Divide(nPtBin,NCOLL);
    for ( int coll = 1 ; coll<=NCOLL ; coll++) {  
        for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
            c1->cd( ipt + nPtBin*(coll-1) );

            dNdJetPt_uncert[coll][ipt]->GetYaxis()->SetTitle("Relative Sys Uncert.");
            //dNdJetPt_uncert[coll][ipt]->SetAxisRange(0.0,2.0,"Y");
            dNdJetPt_uncert[coll][ipt]->SetAxisRange(-1.0,1.0,"Y");
            dNdJetPt_uncert[coll][ipt]->SetMarkerStyle(20);
            dNdJetPt_uncert[coll][ipt]->SetAxisRange(30,150,"X");
            dNdJetPt_uncert[coll][ipt]->GetXaxis()->SetRangeUser(30,150);
            dNdJetPt_uncert[coll][ipt]->Draw("pl");
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

        } //ipt for loop
    }//coll for loop
    c1->SaveAs(Form("pdf/Uncertainty_of_dndjetpt_by_%s.pdf",fOutName.Data()));
    //c1->SaveAs(Form("pdf/relativeSysDist_dNdJetPt_%s.pdf",fname2.Data()));
    TFile * fSysResults = new TFile(Form("relativeSys/relativeSys_dueTo_%s.root",fOutName.Data()),"update");
    for ( int coll = 1 ; coll<=NCOLL ; coll++) {
        for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
            dNdJetPt_uncert[coll][ipt]->Write();
        }
    }
    fSysResults->Close();
}

