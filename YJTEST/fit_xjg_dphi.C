#include "../../hiForestV3/hiForest.h"
#include "../../gammaJetAnalysis/CutAndBinCollection2012.h"
#include <TRandom3.h>
#include <time.h>

void fit_xjg_dphi(TString fname1 = "nominal_vtxCentWeighted"){
    TH1::SetDefaultSumw2();
    int seconds = time(NULL);         cout << " time = " <<seconds%10000<< endl;
    TRandom3 rand(seconds%10000);

    TString fin = "../../gammaJetAnalysis/drawFigures/resultHistograms_nominal_vtxCentWeighted_jet20GeV.root";
    cout << "===============================================================================" << endl;
    cout << "Xjg and Dphi Fitting in file : " <<  fin << endl;
    cout << "===============================================================================" << endl;

    const int kPP = 1;
    const int kHIcentral =  2;
    const int kHIperipheral = 3;
    const int kPA = 4;
    const int nPtBin = 4;
    const int NCOLL = 4;
    double ptBin[nPtBin+1] = {40,50,60,80,9999};

  TH1D* dNdXjg[5][10];
  TH1D* dNdphi[5][10];

    TFile* f;
    f = new TFile(Form("../../gammaJetAnalysis/drawFigures/resultHistograms_%s.root",fname1.Data()));

    for ( int coll = 1 ; coll<=NCOLL ; coll++) {
        TString collName;
        if ( coll == kPP )  collName = "pp";
        else if ( coll == kPA )  collName = "ppb";
        else if ( coll == kHIcentral )  collName = "pbpb_centralityBin1";
        else if ( coll == kHIperipheral )  collName = "pbpb_centralityBin2";

        for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
            dNdXjg[coll][ipt] = (TH1D*)f->Get(Form("dNdXjg_%s_ptBin%d", collName.Data(), ipt ) );
            dNdphi[coll][ipt] = (TH1D*)f->Get(Form("dNdphi_%s_ptBin%d", collName.Data(), ipt ) );
            dNdXjg[coll][ipt]->SetName(Form("dNdXjg_%s_ptBin%d", collName.Data(), ipt ) );
            dNdphi[coll][ipt]->SetName(Form("dNdphi_%s_ptBin%d", collName.Data(), ipt ) );
        }
    }


    // dNdXjg

    TCanvas* c2 = new TCanvas("c2","",300*nPtBin,300*NCOLL);
    c2->Divide(nPtBin,NCOLL);
    for ( int coll = 1 ; coll<=NCOLL ; coll++) {   // On Sep 30, only pp and pbpb is studied.  pA will be added very soon
        for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
            c2->cd( ipt + nPtBin*(coll-1) );
            dNdXjg[coll][ipt]->SetAxisRange(0,3,"Y");
            dNdXjg[coll][ipt]->SetAxisRange(0,2,"X");
            dNdXjg[coll][ipt]->SetMarkerStyle(20);
            dNdXjg[coll][ipt]->Draw("pl");
            //TF1* f1= new TF1("f1","[0]*exp(-[1]*(x-[2]))*(x-[2])",0,2);
            TF1* f1= new TF1("f1","gaus",0,2);
            float rangeLow(0),  rangeHigh(2);
            if ( ipt == 1 ) {
                rangeLow = 30/50.;
                f1= new TF1("f1","[0]*exp(-[1]*(x-[2]))*(x-[2]) ",0,2);
                f1->SetParameter(0,30);
                f1->SetParameter(1,6);
                f1->SetParameter(2,0.6);

            }
            else if ( ipt == 2 ) {
                rangeLow = (float)30/60.;
                f1= new TF1("f1","[0]*exp(-[1]*(x-[2]))*(x-[2]) ",0,2);
                f1->SetParameter(0,15);
                f1->SetParameter(1,5);
                f1->SetParameter(2,0.5);
            }
            else if ( ipt == 3 ) rangeLow = 30/80.;
            else                 rangeLow = 0;

            dNdXjg[coll][ipt]->SetStats(0);
            dNdXjg[coll][ipt]->Fit("f1","LL M","",rangeLow,rangeHigh);
            dNdXjg[coll][ipt]->Fit("f1","LL M","",rangeLow,rangeHigh);
            dNdXjg[coll][ipt]->Fit("f1","LL M","",rangeLow,rangeHigh);

            /////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////
            // COSMETIC
            TString collName;
            if ( coll == kPP )  collName = "pp";
            else if ( coll == kPA )  collName = "pPb";
            else if ( coll == kHIcentral )  collName = "PbPb 0-30%";
            else if ( coll == kHIperipheral )  collName = "PbPb 30-100%";

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

    //  dphi distribution
    TCanvas* c3 = new TCanvas("c3","",300*nPtBin,300*NCOLL);
    c3->Divide(nPtBin,NCOLL);
    for ( int coll = 1 ; coll<=NCOLL ; coll++) {   // On Sep 30, only pp and pbpb is studied.  pA will be added very soon
        for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
            c3->cd( ipt + nPtBin*(coll-1) );
            dNdphi[coll][ipt]->SetAxisRange(0,3.141593,"X");
            dNdphi[coll][ipt]->Scale(1./dNdphi[coll][ipt]->Integral(3,dNdphi[coll][ipt]->GetNbinsX() ) );
            dNdphi[coll][ipt]->SetAxisRange(0.003,10,"Y");
            dNdphi[coll][ipt]->SetMarkerStyle(20);
            dNdphi[coll][ipt]->Draw("pl");
            gPad->SetLogy();
            TF1* f1= new TF1("f1","(TMath::Pi()/20.0)*exp(-(TMath::Pi()-x)/[0])/([0]*(1-exp(-TMath::Pi()/[0]))) + [1]",0,3.141592);
            f1->SetParameter(0,0.3);
            f1->SetParameter(0,0.005);

            //float rangeLow(0),  rangeHigh(3.2);
            float rangeLow(0.5),  rangeHigh(3.2);

            dNdphi[coll][ipt]->SetStats(0);
            dNdphi[coll][ipt]->Fit("f1","LL M","",rangeLow,rangeHigh);
            dNdphi[coll][ipt]->Fit("f1","LL M","",rangeLow,rangeHigh);
            dNdphi[coll][ipt]->Fit("f1","LL M","",rangeLow,rangeHigh);

            /////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////
            // COSMETIC
            TString collName;
            if ( coll == kPP )  collName = "pp";
            else if ( coll == kPA )  collName = "pPb";
            else if ( coll == kHIcentral )  collName = "PbPb 0-30%";
            else if ( coll == kHIperipheral )  collName = "PbPb 30-100%";

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

    c2->SaveAs(Form("pdf/Fitting_dNdXjg_%s.pdf",fname1.Data()));
    c3->SaveAs(Form("pdf/Fitting_dNdphi_%s.pdf",fname1.Data()));

    TFile* fresults = new TFile(Form("../../gammaJetAnalysis/drawFigures/resultHistograms_%s.root",fname1.Data()), "update");
    //TFile* fresults = new TFile(Form("./resultHistograms/resultHistograms_%s_functionAdded.root",fname1.Data()), "recreate");
    fresults->cd();
    for ( int coll = 1 ; coll<=NCOLL ; coll++) {
        for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
            dNdphi[coll][ipt]->Write();
            dNdXjg[coll][ipt]->Write();
        }
    }
}



