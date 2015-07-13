#include "../commonUtilitySys.h"
#include <TRandom3.h>
#include <TFile.h>

void setHistStyle(TH1D* h1=0, float xmin=30, float xmax=150)
{
    h1->GetYaxis()->SetTitle("Relative Sys Uncert.");
    h1->SetAxisRange(xmin,xmax,"X");
    h1->GetXaxis()->SetRangeUser(xmin,xmax);
    h1->SetAxisRange(-1.0,1.0,"Y");
    h1->SetMarkerStyle(20);
    //h1->GetFunction("f1")->SetLineWidth(0);
}


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

void selectPM(TString fname1 = "photonEnergyScaleMinus",
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
    const int NCOLL = 4;
    double ptBin[nPtBin+1] = {40,50,60,80,9999};

    TString collName_tmp[5];
    collName_tmp[1] = "pp";
    collName_tmp[2] = "PbPb 0-30%";
    collName_tmp[3] = "PbPb 30-100%";
    collName_tmp[4] = "pPb";

    TH1D* dNdJetPt[5][5][10];  // [collision] [ ptbin]  [Before/After variation]
    TH1D* dNdXjg[5][5][10];  // [collision] [ ptbin]  [Before/After variation]
    TH1D* dNdphi[5][5][10];  // [collision] [ ptbin]  [Before/After variation]
    TH1D* meanJetPt[5][10];   // [collision] [Before/After variation]
    TH1D* meanRjg[5][10];
    TH1D* meanXjg[5][10];
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

            meanJetPt[coll][ifile]  =(TH1D*)f->Get(Form("meanJetPt_%s_uncertainty", collName.Data()));
            meanRjg[coll][ifile]  =(TH1D*)f->Get(Form("meanRjg_%s_uncertainty", collName.Data()) );
            meanXjg[coll][ifile]  =(TH1D*)f->Get(Form("meanXjg_%s_uncertainty", collName.Data()) );
            for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) { 
                dNdJetPt[coll][ipt][ifile] = (TH1D*)f->Get(Form("dNdJetPt_IaaBin_%s_ptBin%d_uncertainty", collName.Data(), ipt ) );
                dNdXjg[coll][ipt][ifile] = (TH1D*)f->Get(Form("dNdXjg_%s_ptBin%d_uncertainty", collName.Data(), ipt ) );
                dNdphi[coll][ipt][ifile] = (TH1D*)f->Get(Form("dNdphi_%s_ptBin%d_uncertainty", collName.Data(), ipt ) );
            }//ipt
        }//coll 
    }//ifile

    ///////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////
    //// relative uncertainty calculation

    for ( int coll = 1 ; coll<=NCOLL ; coll++) {  
        meanJetPt[coll][0] = (TH1D*)meanJetPt[coll][1]->Clone(meanJetPt[coll][1]->GetName() );
        meanJetPt[coll][0]->Reset();
        selectLargeValue(meanJetPt[coll][1], meanJetPt[coll][2]);
        meanJetPt[coll][0]->Add(meanJetPt[coll][1]);


        meanRjg[coll][0] = (TH1D*)meanRjg[coll][1]->Clone(meanRjg[coll][1]->GetName() );
        meanRjg[coll][0]->Reset();
        selectLargeValue(meanRjg[coll][1], meanRjg[coll][2]);
        meanRjg[coll][0]->Add(meanRjg[coll][1]);


        meanXjg[coll][0] = (TH1D*)meanXjg[coll][1]->Clone(meanXjg[coll][1]->GetName() );
        meanXjg[coll][0]->Reset();
        selectLargeValue(meanXjg[coll][1], meanXjg[coll][2]);
        meanXjg[coll][0]->Add(meanXjg[coll][1]);
        for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
            dNdJetPt[coll][ipt][0] = (TH1D*)dNdJetPt[coll][ipt][1]->Clone(dNdJetPt[coll][ipt][1]->GetName() );
            dNdJetPt[coll][ipt][0]->Reset();
            selectLargeValue(dNdJetPt[coll][ipt][1], dNdJetPt[coll][ipt][2]);
            dNdJetPt[coll][ipt][0]->Add(dNdJetPt[coll][ipt][1]); 

            dNdXjg[coll][ipt][0] = (TH1D*)dNdXjg[coll][ipt][1]->Clone(dNdXjg[coll][ipt][1]->GetName() );
            dNdXjg[coll][ipt][0]->Reset();
            selectLargeValue(dNdXjg[coll][ipt][1], dNdXjg[coll][ipt][2]);
            dNdXjg[coll][ipt][0]->Add(dNdXjg[coll][ipt][1]);

            dNdphi[coll][ipt][0] = (TH1D*)dNdphi[coll][ipt][1]->Clone(dNdphi[coll][ipt][1]->GetName() );
            dNdphi[coll][ipt][0]->Reset();
            selectLargeValue(dNdphi[coll][ipt][1], dNdphi[coll][ipt][2]);
            dNdphi[coll][ipt][0]->Add(dNdphi[coll][ipt][1]);

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
            setHistStyle(dNdJetPt[coll][ipt][0]);
            dNdJetPt[coll][ipt][0]->Draw("pl");
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
            setHistStyle(dNdXjg[coll][ipt][0],0,2);
            dNdXjg[coll][ipt][0]->Draw("pl");
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
            setHistStyle(dNdphi[coll][ipt][0]);
            dNdphi[coll][ipt][0]->Draw("pl");
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
        setHistStyle(meanJetPt[coll][0]);
        meanJetPt[coll][0]->Draw("pl");
        meanJetPt[coll][0]->GetYaxis()->SetTitle("Relative Sys Uncert. of <p_{T}^{Jet}>");
        meanJetPt[coll][0]->GetXaxis()->SetRangeUser(30,120);
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
        setHistStyle(meanXjg[coll][0]);
        meanXjg[coll][0]->Draw("pl");
        meanXjg[coll][0]->GetYaxis()->SetTitle("Relative Sys Uncert. of <x_{J#gamma}>");
        meanXjg[coll][0]->GetXaxis()->SetRangeUser(30,120);
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
        setHistStyle(meanRjg[coll][0]);
        meanRjg[coll][0]->Draw("pl");
        meanRjg[coll][0]->GetYaxis()->SetTitle("Relative Sys Uncert. of <R_{J#gamma}>");
        meanRjg[coll][0]->GetXaxis()->SetRangeUser(30,120);
        jumSun(30,0,120,0);

        TString collName = collName_tmp[coll];
        double dx1=0.18;
        drawText(collName, 0.10+dx1, 0.7, 1, 16); //collision name
    }

    /////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////
    // SAVING

    c1->SaveAs(Form("pdf/Uncertainty_of_dndjetpt_by_%s.pdf",fOutname.Data())); 
    c2->SaveAs(Form("pdf/Uncertainty_of_dndxjg_by_%s.pdf",fOutname.Data())); 
    c3->SaveAs(Form("pdf/Uncertainty_of_dndphi_by_%s.pdf",fOutname.Data())); 
    c4->SaveAs(Form("pdf/Uncertainty_of_meanjetpt_by_%s.pdf",fOutname.Data())); 
    c5->SaveAs(Form("pdf/Uncertainty_of_meanxjg_by_%s.pdf",fOutname.Data())); 
    c6->SaveAs(Form("pdf/Uncertainty_of_r_by_%s.pdf",fOutname.Data())); 

    TFile * fSysResults = new TFile(Form("relativeSys/relativeSys_dueTo_%s.root",fOutname.Data()),"recreate");
    for ( int coll = 1 ; coll<=NCOLL ; coll++) { 
        meanJetPt[coll][0]->Write();
        meanRjg[coll][0]->Write();
        meanXjg[coll][0]->Write();
        for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
            dNdJetPt[coll][ipt][0]->Write();
            dNdXjg[coll][ipt][0]->Write();
            dNdphi[coll][ipt][0]->Write();
        }
    }
    fSysResults->Close();
}
