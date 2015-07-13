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

void setHistStyle(TH1D* h1=0, float xmin=30.0, float xmax=150.0, bool removeFit=0)
{
    h1->GetYaxis()->SetTitle("Relative Sys Uncert.");
    h1->SetAxisRange(xmin,xmax,"X");
    h1->GetXaxis()->SetRangeUser(xmin,xmax);
    h1->SetAxisRange(-1.0,1.0,"Y");
    h1->SetMarkerStyle(20);
    if(removeFit) {
        h1->GetFunction("f1")->SetLineColor(0);
        h1->GetFunction("f1")->SetLineWidth(0);
    }
}

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


void getSysUncert(   
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
    double ptBin[nPtBin+1] = {40,50,60,80,9999}; 

    TString collName_tmp[5];
    collName_tmp[1] = "pp";
    collName_tmp[2] = "PbPb 0-30%";
    collName_tmp[3] = "PbPb 30-100%";
    collName_tmp[4] = "pPb";

    TH1D* dNdJetPt[5][5][3];  // [collision] [ ptbin]  [Before/After variation] before : 0, variated : 1, return : 2 
    TH1D* dNdXjg[5][5][3];  // [collision] [ ptbin]  [Before/After variation]
    TH1D* dNdphi[5][5][3];  // [collision] [ ptbin]  [Before/After variation]
    TH1D* meanXjg[5][3];   // [collision] [Before/After variation]
    TH1D* meanJetPt[5][3];   // [collision] [Before/After variation]
    TH1D* meanRjg[5][3];
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

            meanJetPt[coll][ifile]  =(TH1D*)f->Get(Form("meanJetPt_%s", collName.Data()));
            meanXjg[coll][ifile]  =(TH1D*)f->Get(Form("meanXjg_%s", collName.Data()));
            meanRjg[coll][ifile]  =(TH1D*)f->Get(Form("meanRjg_%s", collName.Data()) );
            for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) { 
                dNdJetPt[coll][ipt][ifile] = (TH1D*)f->Get(Form("dNdJetPt_IaaBin_%s_ptBin%d", collName.Data(), ipt ) );
                dNdXjg[coll][ipt][ifile] = (TH1D*)f->Get(Form("dNdXjg_%s_ptBin%d", collName.Data(), ipt ) );
                dNdphi[coll][ipt][ifile] = (TH1D*)f->Get(Form("dNdphi_%s_ptBin%d", collName.Data(), ipt ) );
            }
        }
    }
    for ( int coll = 1 ; coll<=NCOLL ; coll++) {   
        cout << "coll : " << coll << endl;
        meanJetPt[coll][2] = (TH1D*)meanJetPt[coll][1]->Clone(Form("%s_uncertainty", meanJetPt[coll][1]->GetName()) );
        calUncert( meanJetPt[coll][2], meanJetPt[coll][0], scaleFactor) ;
        Subtract1(meanJetPt[coll][2]);

        meanXjg[coll][2] = (TH1D*)meanXjg[coll][1]->Clone(Form("%s_uncertainty", meanXjg[coll][1]->GetName()) );
        calUncert( meanXjg[coll][2], meanXjg[coll][0], scaleFactor) ;
        Subtract1(meanXjg[coll][2]);

        meanRjg[coll][2] = (TH1D*)meanRjg[coll][1]->Clone(Form("%s_uncertainty", meanRjg[coll][1]->GetName() ) );
        calUncert( meanRjg[coll][2], meanRjg[coll][0], scaleFactor) ;
        Subtract1(meanRjg[coll][2]);

        for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
            dNdJetPt[coll][ipt][2] = (TH1D*)dNdJetPt[coll][ipt][1]->Clone(Form("%s_uncertainty", dNdJetPt[coll][ipt][1]->GetName()));
            calUncert( dNdJetPt[coll][ipt][2], dNdJetPt[coll][ipt][0] , scaleFactor); 
            Subtract1(dNdJetPt[coll][ipt][2]);

            dNdXjg[coll][ipt][2] = (TH1D*)dNdXjg[coll][ipt][1]->Clone(Form("%s_uncertainty", dNdXjg[coll][ipt][1]->GetName()));
            calUncFromFit(dNdXjg[coll][ipt][2], dNdXjg[coll][ipt][0] , dNdXjg[coll][ipt][1], scaleFactor);

            dNdphi[coll][ipt][2] = (TH1D*)dNdphi[coll][ipt][1]->Clone(Form("%s_uncertainty", dNdphi[coll][ipt][1]->GetName()));
            calUncFromFit(dNdphi[coll][ipt][2], dNdphi[coll][ipt][0] , dNdphi[coll][ipt][1], scaleFactor);
        }
    }

    /////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////
    // COSMETIC

    //dNdJetPt
    TCanvas* c1 = new TCanvas("c1","",300*nPtBin,300*NCOLL);
    c1->Divide(nPtBin,NCOLL);
    for ( int coll = 1 ; coll<=NCOLL ; coll++) {
        for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
            c1->cd( ipt + nPtBin*(coll-1) );
            setHistStyle(dNdJetPt[coll][ipt][2]);
            dNdJetPt[coll][ipt][2]->Draw("pl");
            jumSun(30,0,150,0);

            TString collName = collName_tmp[coll];
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

    //dNdXjg
    TCanvas* c2 = new TCanvas("c2","",300*nPtBin,300*NCOLL);
    c2->Divide(nPtBin,NCOLL);
    for ( int coll = 1 ; coll<=NCOLL ; coll++) {
        for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
            c2->cd( ipt + nPtBin*(coll-1) );
            setHistStyle(dNdXjg[coll][ipt][2],0,2,1);
            dNdXjg[coll][ipt][2]->Draw("pl");
            jumSun(0,0,2,0);

            TString collName = collName_tmp[coll];
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
    //dNdphi
    TCanvas* c3 = new TCanvas("c3","",300*nPtBin,300*NCOLL);
    c3->Divide(nPtBin,NCOLL);
    for ( int coll = 1 ; coll<=NCOLL ; coll++) {
        for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
            c3->cd( ipt + nPtBin*(coll-1) );
            setHistStyle(dNdphi[coll][ipt][2],0,3.14,1);
            dNdphi[coll][ipt][2]->Draw("pl");
            jumSun(0,0,3.14,0);

            TString collName = collName_tmp[coll];
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

    //meanJetPt
    TCanvas* c4 = new TCanvas("c4","",300*NCOLL,300*1);
    c4->Divide(NCOLL,1);
    for ( int coll = 1 ; coll<=NCOLL ; coll++) {
        c4->cd(coll);
        setHistStyle(meanJetPt[coll][2],30,150);
        meanJetPt[coll][2]->GetYaxis()->SetTitle("Relative Sys Uncert. of <p_{T}^{Jet}>");
        meanJetPt[coll][2]->GetXaxis()->SetRangeUser(30,120);
        meanJetPt[coll][2]->Draw("pl");
        jumSun(30,0,120,0);

        TString collName = collName_tmp[coll];
        double dx1=0.18;
        drawText(collName, 0.10+dx1, 0.7, 1, 16); //collision name
    }

    //meanXjg
    TCanvas* c5 = new TCanvas("c5","",300*NCOLL,300*1);
    c5->Divide(NCOLL,1);
    for ( int coll = 1 ; coll<=NCOLL ; coll++) {
        c5->cd(coll);
        setHistStyle(meanXjg[coll][2],30,150);
        meanXjg[coll][2]->GetYaxis()->SetTitle("Relative Sys Uncert. of <x_{J#gamma}>");
        meanXjg[coll][2]->GetXaxis()->SetRangeUser(30,120);
        meanXjg[coll][2]->Draw("pl");
        jumSun(30,0,120,0);

        TString collName = collName_tmp[coll];
        double dx1=0.18;
        drawText(collName, 0.10+dx1, 0.7, 1, 16); //collision name
    }

    //meanRjg
    TCanvas* c6 = new TCanvas("c6","",300*NCOLL,300*1);
    c6->Divide(NCOLL,1);
    for ( int coll = 1 ; coll<=NCOLL ; coll++) {
        c6->cd(coll);
        setHistStyle(meanRjg[coll][2],30,150);
        meanRjg[coll][2]->GetYaxis()->SetTitle("Relative Sys Uncert. of <R_{J#gamma}>");
        meanRjg[coll][2]->GetXaxis()->SetRangeUser(30,120);
        meanRjg[coll][2]->Draw("pl");
        jumSun(30,0,120,0);

        TString collName = collName_tmp[coll];
        double dx1=0.18;
        drawText(collName, 0.10+dx1, 0.7, 1, 16); //collision name
    }

    /////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////
    // SAVING

    c1->SaveAs(Form("pdf/Uncertainty_of_dndjetpt_by_%s.pdf",fname2.Data()));
    c2->SaveAs(Form("pdf/Uncertainty_of_dndxjg_by_%s.pdf",fname2.Data()));
    c3->SaveAs(Form("pdf/Uncertainty_of_dndphi_by_%s.pdf",fname2.Data()));
    c4->SaveAs(Form("pdf/Uncertainty_of_meanjetpt_by_%s.pdf",fname2.Data()));
    c5->SaveAs(Form("pdf/Uncertainty_of_meanxjg_by_%s.pdf",fname2.Data()));
    c6->SaveAs(Form("pdf/Uncertainty_of_r_by_%s.pdf",fname2.Data()));

    TFile * fSysResults = new TFile(Form("relativeSys/relativeSys_dueTo_%s.root",fname2.Data()),"recreate");
    for ( int coll = 1 ; coll<=NCOLL ; coll++) {
        meanJetPt[coll][2]->Write();
        meanRjg[coll][2]->Write();
        meanXjg[coll][2]->Write();
        for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
            dNdJetPt[coll][ipt][2]->Write();
            dNdXjg[coll][ipt][2]->Write();
            dNdphi[coll][ipt][2]->Write();
        }
    }
    fSysResults->Close();
}

