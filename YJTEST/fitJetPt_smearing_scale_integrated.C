#include "../../hiForestV3/hiForest.h"
#include "../../gammaJetAnalysis/CutAndBinCollection2012.h"
#include <TRandom3.h>
#include <time.h>

void fitJetPt_smearing_scale_integrated(float scaleFactor=1.02, bool onlyScale=false){
    TH1::SetDefaultSumw2();
    int seconds = time(NULL);         cout << " time = " <<seconds%10000<< endl;
    TRandom3 rand(seconds%10000);

    TString fin = "../../gammaJetAnalysis/drawFigures/resultHistograms_nominal_vtxCentWeighted_jet20GeV.root";
    cout << "===============================================================================" << endl;
    cout << "JetPt Fitting in file : " <<  fin << endl;
    cout << "===============================================================================" << endl;

    const int kPP = 1;
    const int kHIcentral =  2;
    const int kHIperipheral = 3;
    const int kPA = 4;
    const int nPtBin = 4;
    const int NCOLL = 4;
    //const int NCOLL = 3;
    double ptBin[nPtBin+1] = {40,50,60,80,9999};

    const int nRptBin[4] = {5,5,6,6}; // Iaa Binning
    double ratioPtBin[4][10] = {{20,30,40,50,70,150},
        {20,30,40,50,70,150},
        {20,30,40,50,70,100,150},
        {20,30,40,50,70,100,150}};
    double ratioPtBin1[4][10] = {{20,30,40,50,68,105},
        {20,30,40,50,68,105},
        {20,30,40,50,68,100,130},
        {20,30,40,50,68,100,130}};

    TH1D* dNdJetPt_origin[5][5];  // [collision] [ptbin]  // ptBin width 10 GeV
    TH1D* dNdJetPt_IaaBin[5][5];  // [collision] [ptbin]  // ptBin width 10 GeV
    TH1D* dNdJetPt[5][5];  // [collision] [ptbin]  // smeared dist with Iaa Binning
    TF1* fJetPt_origin[5][5];  // [collision] [ptbin] 
    TF1* fJetPt[5][5];  // [collision] [ptbin] 

    TFile* f;
    f = new TFile(fin.Data());

    for ( int coll = 1 ; coll<=NCOLL ; coll++) {
        TString collName;
        if ( coll == kPP )  collName = "pp";
        else if ( coll == kPA )  collName = "ppb";
        else if ( coll == kHIcentral )  collName = "pbpb_centralityBin1";
        else if ( coll == kHIperipheral )  collName = "pbpb_centralityBin2";

        for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
            dNdJetPt_origin[coll][ipt] = (TH1D*)f->Get(Form("dNdJetPt_%s_ptBin%d", collName.Data(), ipt ) );
            dNdJetPt_origin[coll][ipt] -> SetName(Form("dNdJetPt_%s_ptBin%d_origin", collName.Data(), ipt ));

            dNdJetPt_IaaBin[coll][ipt] = (TH1D*)dNdJetPt_origin[coll][ipt]->Rebin(nRptBin[ipt-1], Form("dNdJetPt_%s_ptBin%d_IaaBin", collName.Data(), ipt), ratioPtBin[ipt-1]);
            dNdJetPt_IaaBin[coll][ipt]->Reset(); 
            //dNdJetPt_IaaBin[coll][ipt] = (TH1D*)dNdJetPt_origin[coll][ipt]->Rebin(nRptBin[ipt-1], Form("dNdJetPt_%s_ptBin%d_IaaBin", collName.Data(), ipt), ratioPtBin[ipt-1]);
            //dNdJetPt_IaaBin[coll][ipt]->Scale( 10., "width" );
            dNdJetPt[coll][ipt] = (TH1D*)dNdJetPt_origin[coll][ipt]->Rebin(nRptBin[ipt-1], Form("dNdJetPt_%s_ptBin%d_varied", collName.Data(), ipt), ratioPtBin[ipt-1]);
            dNdJetPt[coll][ipt]->Reset();
        }
    }
    TCanvas* c1 = new TCanvas("c1", "", 1000,270*NCOLL);
    c1->Divide(4,NCOLL);

    for ( int coll = 1 ; coll<=NCOLL ; coll++) {
        for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
            c1->cd(4*(coll-1)+ipt);

            ///////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////
            // NOMINAL FITTING
            if ( ((coll==1||coll==2||coll==4)&&ipt==4) || (coll==1&&ipt==3) ){    
                fJetPt_origin[coll][ipt] = new TF1(Form("fb_coll%d_pt%d_origin",coll,ipt),"[0]*exp(-[1]*(x-[2]))*(x-[2]) + [3]*exp(-[4]*(x-30)) ",0,300);
                fJetPt_origin[coll][ipt]->SetParameter(0,0.01);
                fJetPt_origin[coll][ipt]->SetParameter(1,0.1);
                fJetPt_origin[coll][ipt]->SetParameter(2,1);
                fJetPt_origin[coll][ipt]->SetParameter(3,0.01);
                fJetPt_origin[coll][ipt]->SetParameter(4,0.02);
            }    
            else {
                fJetPt_origin[coll][ipt]= new TF1(Form("fb_coll%d_pt%d_origin",coll,ipt),"[0]*exp(-[1]*(x-[2]))*(x-[2]) ",0,300);
                if(coll==1&&ipt==1){
                    fJetPt_origin[coll][ipt]->SetParameter(0,3.65316e-03);
                    fJetPt_origin[coll][ipt]->SetParameter(1,8.13024e-02);
                    fJetPt_origin[coll][ipt]->SetParameter(2,2.09877e+01);
                }
                else {
                    fJetPt_origin[coll][ipt]->SetParameter(0,2.08328e-03);
                    fJetPt_origin[coll][ipt]->SetParameter(1,7.55718e-02);
                    fJetPt_origin[coll][ipt]->SetParameter(2,1.84665e+01);
                }       
            }

            //fJetPt[coll][ipt]->SetParameter(0,dNdJetPt[coll][ipt]->GetMaximum());
            cout << Form("***************fb_coll%d_pt%d***************",coll,ipt) << endl;
#if 1
            dNdJetPt_origin[coll][ipt]->Fit(fJetPt_origin[coll][ipt]->GetName(),"LL M","",20,300);
            dNdJetPt_origin[coll][ipt]->Fit(fJetPt_origin[coll][ipt]->GetName(),"LL M","",20,300);
            dNdJetPt_origin[coll][ipt]->Fit(fJetPt_origin[coll][ipt]->GetName(),"LL M","",20,300);
#endif
#if 0
            dNdJetPt_IaaBin[coll][ipt]->Fit(fJetPt_origin[coll][ipt]->GetName(),"LL M","",20,300);
            dNdJetPt_IaaBin[coll][ipt]->Fit(fJetPt_origin[coll][ipt]->GetName(),"LL M","",20,300);
            dNdJetPt_IaaBin[coll][ipt]->Fit(fJetPt_origin[coll][ipt]->GetName(),"LL M","",20,300);
#endif
            dNdJetPt_origin[coll][ipt]->SetMarkerStyle(20);
            dNdJetPt_origin[coll][ipt]->Draw("p");
            fJetPt_origin[coll][ipt]->Draw("same");

            /////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////
            // SMEARING
            const int NSMEAR = 1000000;
            for(int ismear = 0; ismear< NSMEAR; ismear++){
                double frand = (fJetPt_origin[coll][ipt]->GetRandom(20.0, 150.0)) ;
                dNdJetPt_IaaBin[coll][ipt]->Fill(frand);
                if(onlyScale) dNdJetPt[coll][ipt]->Fill(frand * scaleFactor);
                else dNdJetPt[coll][ipt]->Fill(frand * rand.Gaus(1, 0.1) * scaleFactor);
            }
            dNdJetPt_IaaBin[coll][ipt]->Scale( 1., "width" ); 
            dNdJetPt_IaaBin[coll][ipt]->Scale( 1./dNdJetPt_IaaBin[coll][ipt]->Integral("width") ); //so far, the area of the hist is 1.
            dNdJetPt_IaaBin[coll][ipt]->Scale( fJetPt_origin[coll][ipt]->Integral(20.0,150.0) );
            dNdJetPt[coll][ipt]->Scale( 1., "width" ); 
            dNdJetPt[coll][ipt]->Scale( 1./dNdJetPt[coll][ipt]->Integral("width") ); //so far, the area of the hist is 1.
            dNdJetPt[coll][ipt]->Scale( fJetPt_origin[coll][ipt]->Integral(20.0,150.0) );
/*
            dNdJetPt[coll][ipt]->Scale( 1., "width" ); 
            dNdJetPt[coll][ipt]->Scale( 1./dNdJetPt[coll][ipt]->Integral("width") ); //so far, the area of the hist is 1.
            dNdJetPt[coll][ipt]->Scale( dNdJetPt_IaaBin[coll][ipt]->Integral("width") );
            //cout << "dNdJetPt area : " << dNdJetPt[coll][ipt]->Integral("width") << "dNdJetPt_IaaBin area : " << dNdJetPt_IaaBin[coll][ipt]->Integral("width") << endl;
*/
            dNdJetPt[coll][ipt]->SetLineColor(4);
            dNdJetPt[coll][ipt]->SetLineWidth(2);
            dNdJetPt[coll][ipt]->Draw("same hist");
            dNdJetPt_IaaBin[coll][ipt]->SetLineColor(6);
            dNdJetPt_IaaBin[coll][ipt]->SetLineWidth(2);
            dNdJetPt_IaaBin[coll][ipt]->Draw("same hist");

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
            if(coll==1&&ipt==1) {
                TLegend* l1 = new TLegend(0.37,0.57,0.95,0.8);
                l1->SetFillColor(0);
                l1->SetFillStyle(0);
                l1->AddEntry(dNdJetPt_origin[coll][ipt], "Data", "pe");
                l1->AddEntry(fJetPt_origin[coll][ipt], "Data Fit", "l");
                l1->AddEntry(dNdJetPt_IaaBin[coll][ipt], "Data IaaBin from the fit", "l");
                l1->AddEntry(dNdJetPt[coll][ipt], "Variation IaaBin from the fit", "l");
                l1->Draw("same");
            }
        }// ipt for loop
    }//coll for loop
    if(onlyScale) c1->SaveAs(Form("pdf/Fitting_dNdJetPt_jetEnergyScale%.2f.pdf",(float)scaleFactor));
    else c1->SaveAs(Form("pdf/Fitting_dNdJetPt_jetEnergySmearingNscale%.2f.pdf",(float)scaleFactor));

    TFile * fResults;
    if(onlyScale) fResults =  new TFile(Form("/home/goyeonju/CMS/2015/gammaJetSystematics_yjTest20150610/YJTEST/resultHistograms/resultFunction_scale%.2f.root",(float)scaleFactor),"recreate");
    else fResults =  new TFile(Form("/home/goyeonju/CMS/2015/gammaJetSystematics_yjTest20150610/YJTEST/resultHistograms/resultFunction_smearingNscale%.2f.root",(float)scaleFactor),"recreate");

    fResults->cd();
    for ( int coll = 1 ; coll<=NCOLL ; coll++) {
        for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
            dNdJetPt_origin[coll][ipt]->Write();          
            dNdJetPt_IaaBin[coll][ipt]->Write();          
            dNdJetPt[coll][ipt]->Write();          
            fJetPt_origin[coll][ipt]->Write();          
        }
    }
}

