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

void getSysUncert_xjg_dphi(   
        TString fname1 = "nominal_vtxCentWeighted",
        TString fname2 = "electronContamination",
        float scaleFactor= 0.25
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
    double ptBin[nPtBin+1] = {40,50,60,80,9999}; 

    TH1D* dNdJetPt[5][5][3];  // [collision] [ ptbin]  [Before/After variation] before : 0 , varied : 1, return : 2
    TH1D* dNdXjg[5][5][3];  // [collision] [ ptbin]  [Before/After variation]
    TH1D* dNdphi[5][5][3];  // [collision] [ ptbin]  [Before/After variation]
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
                dNdXjg[coll][ipt][ifile] = (TH1D*)f->Get(Form("dNdXjg_%s_ptBin%d", collName.Data(), ipt ) );
                dNdphi[coll][ipt][ifile] = (TH1D*)f->Get(Form("dNdphi_%s_ptBin%d", collName.Data(), ipt ) );
            }
        }
    }

    for ( int coll = 1 ; coll<=NCOLL ; coll++) {   
        for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
            dNdXjg[coll][ipt][2] = (TH1D*)dNdXjg[coll][ipt][1]->Clone(Form("%s_uncertainty", dNdXjg[coll][ipt][1]->GetName()));
            calUncFromFit(dNdXjg[coll][ipt][2], dNdXjg[coll][ipt][1] , dNdXjg[coll][ipt][0], scaleFactor);
            dNdphi[coll][ipt][2] = (TH1D*)dNdphi[coll][ipt][1]->Clone(Form("%s_uncertainty", dNdphi[coll][ipt][1]->GetName()));
            calUncFromFit(dNdphi[coll][ipt][2], dNdphi[coll][ipt][1] , dNdphi[coll][ipt][0], scaleFactor);         
        }
    }

    TCanvas* c1 = new TCanvas("c1","",300*nPtBin,300*NCOLL);
    c1->Divide(nPtBin,NCOLL);
    TF1* fdNdXjg[5][5];
    for ( int coll = 1 ; coll<=4 ; coll++) { 
        for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
            c1->cd( ipt + nPtBin*(coll-1) );

            dNdXjg[coll][ipt][2]->SetAxisRange(0,2,"X");
            dNdXjg[coll][ipt][2]->SetAxisRange(-.5,.5,"Y");
            dNdXjg[coll][ipt][2]->GetFunction("f1")->SetLineColor(0);
            dNdXjg[coll][ipt][2]->GetFunction("f1")->SetLineWidth(0);
            dNdXjg[coll][ipt][2]->SetStats(0);
            dNdXjg[coll][ipt][2]->Draw();
            jumSun(0,0,2,0);

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

    TCanvas* c2 = new TCanvas("c2","",300*nPtBin,300*NCOLL);
    c2->Divide(nPtBin,NCOLL);
    TF1* fdNdphi[5][5];
    for ( int coll = 1 ; coll<=4 ; coll++) {  
        for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
            c2->cd( ipt + nPtBin*(coll-1) );

            dNdphi[coll][ipt][2]->SetAxisRange(0,3.15,"X");
            dNdphi[coll][ipt][2]->SetAxisRange(-.5,.5,"Y");
            dNdphi[coll][ipt][2]->GetFunction("f1")->SetLineColor(0);
            dNdphi[coll][ipt][2]->GetFunction("f1")->SetLineWidth(0);
            dNdphi[coll][ipt][2]->SetStats(0);
            dNdphi[coll][ipt][2]->Draw();
            jumSun(0,0,3.14,0);

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
    c1->SaveAs(Form("pdf/Uncertainty_of_dndphi_by_%s.pdf",fname2.Data()));
    c2->SaveAs(Form("pdf/Uncertainty_of_dndxjg_by_%s.pdf",fname2.Data()));

    TFile * fSysResults = new TFile(Form("relativeSys/relativeSys_dueTo_%s.root",fname2.Data()),"update");
    for ( int coll = 1 ; coll<=NCOLL ; coll++) {
        for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
            dNdXjg[coll][ipt][2]->Write();
            dNdphi[coll][ipt][2]->Write();
        }
    }
    fSysResults->Close();
}

