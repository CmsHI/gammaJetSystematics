#include "../commonUtilitySys.h"
#include <TFile.h>
#include <TGraphErrors.h>

void drawFinalPlot() {
    TH1::SetDefaultSumw2();
    // const int kPPcentral = 1;
    // const int kPPperipheral =2 ;
    // const int kHIcentral =  3;
    // const int kHIperipheral = 4;
    // const int kPADATA = 5;
    // const int kPAMC = 6;
    const int nPtBin = 4;
    double ptBin[nPtBin+1] = {40,50,60,80,9999};

    TH1D* dNdJetPt[8][5]; // [collision] [ ptbin]  [Before/After variation]
    TH1D* dNdJetPtSys[7][5]; // [collision] [ ptbin]  [Before/After variation]

    TH1D* hIaa[7][5]; //  pbpb/pp of jet pt [collision] [ptbin]
    TH1D* hIaa1[7][5]; //  pbpb/pp of jet pt [collision] [ptbin] //bin center is average of jet pT
    TH1D* hIaaSys[7][5]; //  pbpb/pp of jet pt

    TH1D* dNdJetPt40GeV[7]; 
    TH1D* dNdJetPtSys40GeV[7];
    TH1D* ratioJet40GeV[7]; 
    TH1D* ratioJet40GeV1[7];
    TH1D* ratioJetSys40GeV[7];


    const int nRptBin[4] = {4,4,5,5};
    double ratioPtBin[4][10] = {{30,40,50,70,150},
        {30,40,50,70,150},
        {30,40,50,70,100,150},
        {30,40,50,70,100,150}};
    double ratioPtBin1[4][10] = {{30,40,50,68,105},
        {30,40,50,68,105},
        {30,40,50,68,100,130},
        {30,40,50,68,100,130}};

    const int nRptBin40GeV = 7;
    double ratioPtBin40GeV[8] = {20,30,40,50,60,80,100,150};
    double ratioPtBin40GeV1[8] = {20,30,40,50,60,78,108,138};

    //pp smeared
    TFile * f = new TFile("../../gammaJetAnalysis/drawFigures/resultHistograms_ppSmeared10030.root");
    for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
        dNdJetPt[1][ipt] = (TH1D*)f->Get(Form("dNdJetPt_IaaBin_pp_ptBin%d", ipt ));
    }
    f   = new TFile("../../gammaJetAnalysis/drawFigures/resultHistograms_ppSmeared13099.root");
    for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
        dNdJetPt[2][ipt] = (TH1D*)f->Get(Form("dNdJetPt_IaaBin_pp_ptBin%d", ipt ));
    }

    // pbpb
    f =   new TFile("../../gammaJetAnalysis/drawFigures/resultHistograms_nominal_vtxCentWeighted.root");
    for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
        dNdJetPt[3][ipt] = (TH1D*)f->Get(Form("dNdJetPt_IaaBin_pbpb_centralityBin1_ptBin%d", ipt ));
        hIaa[3][ipt] = (TH1D*) dNdJetPt[3][ipt]->Clone(Form("Iaa_centralityBin1_ptBin%d", ipt ));
    }
    for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
        dNdJetPt[4][ipt] = (TH1D*)f->Get(Form("dNdJetPt_IaaBin_pbpb_centralityBin2_ptBin%d", ipt ));
        hIaa[4][ipt] = (TH1D*) dNdJetPt[4][ipt]->Clone(Form("Iaa_centralityBin2_ptBin%d", ipt ));
    }
    //pp unsmeared
    f =   new TFile("../../gammaJetAnalysis/drawFigures/resultHistograms_nominal_vtxCentWeighted.root");
    for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
        dNdJetPt[7][ipt] = (TH1D*)f->Get(Form("dNdJetPt_IaaBin_pp_ptBin%d", ipt ));
    }

    TFile* fSys = new TFile("relativeSys/relativeSys_merged.root");

    for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
        dNdJetPtSys[1][ipt] = (TH1D*)fSys->Get(Form("dNdJetPt_IaaBin_pp_ptBin%d_uncertainty_merged",  ipt ));
    }
    for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
        dNdJetPtSys[2][ipt] = (TH1D*)dNdJetPtSys[1][ipt]->Clone(Form("%s_2",dNdJetPtSys[1][ipt]->GetName()));
    }
    for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
        dNdJetPtSys[3][ipt] = (TH1D*)fSys->Get(Form("dNdJetPt_IaaBin_pbpb_centralityBin1_ptBin%d_uncertainty_merged",  ipt ));
        hIaaSys[3][ipt] = (TH1D*)fSys->Get(Form("dNdJetPt_ratio_centralityBin1_ptBin%d_uncertainty_merged",  ipt ));
    }
    for ( int ipt = 1 ; ipt <=nPtBin ; ipt++) {
        dNdJetPtSys[4][ipt] = (TH1D*)fSys->Get(Form("dNdJetPt_IaaBin_pbpb_centralityBin2_ptBin%d_uncertainty_merged",  ipt ));
        hIaaSys[4][ipt] = (TH1D*)fSys->Get(Form("dNdJetPt_ratio_centralityBin2_ptBin%d_uncertainty_merged",  ipt ));
    }

    // jet pt ratio distributions
    TH1D* hTempPt = new TH1D("hTemp",";p_{T}^{#gamma} (GeV);",20000,10,300);

    TCanvas* c5_ratio = new TCanvas("c5_ratio","",1200*0.8,600*0.8);
    makeMultiPanelCanvas(c5_ratio,nPtBin, 2, 0.0, 0.0, 0.25, 0.2, 0.02);
    for ( int coll = 3 ; coll<=4 ; coll++) { // 3 : centralityBin1(central), 4 : centralityBin2(peripheral)
        for ( int ipt = 1 ; ipt<=nPtBin  ; ipt++) {
            if(coll==3) c5_ratio->cd(ipt+nPtBin);
            else if(coll==4) c5_ratio->cd(ipt);
            hTempPt->SetXTitle("p_{T}^{Jet} (GeV)");
            hTempPt->SetYTitle("Jet I_{AA}");
            hTempPt->SetAxisRange(10,149.9,"X");
            hTempPt->SetAxisRange(0.001,2.9,"Y");
            hTempPt->SetLabelSize(0.06,"X");
            hTempPt->SetLabelSize(0.06,"Y");
            hTempPt->SetTitleSize(0.06,"X");
            hTempPt->SetTitleSize(0.06,"Y");
            handsomeTH1(hTempPt,0);
            //hTempPt->GetYaxis()->SetTitleOffset(2.5);
            //hTempPt->GetXaxis()->SetTitleOffset(2);
            //hTempPt->SetNdivisions(505);
            hTempPt->Draw();
            //hTempPt->DrawCopy();

            hIaa[coll][ipt]->Divide(dNdJetPt[coll-2][ipt]);
            //drawSys(hIaa[coll][ipt],hIaaSys[coll][ipt]);

            hIaa1[coll][ipt] = new TH1D(Form("%s_draw",hIaa[coll][ipt]->GetName()),"",nRptBin[ipt-1],ratioPtBin1[ipt-1]);
            for ( int ibin =1 ; ibin<=nRptBin[ipt-1] ; ibin++)  {
                hIaa1[coll][ipt]->SetBinContent(ibin, hIaa[coll][ipt]->GetBinContent(ibin));
                hIaa1[coll][ipt]->SetBinError(ibin, hIaa[coll][ipt]->GetBinError(ibin));
            }

            handsomeTH1(hIaa1[coll][ipt],2);
            if(coll==4) hIaa1[coll][ipt]->SetMarkerStyle(24);
            drawSys(hIaa1[coll][ipt], hIaaSys[coll][ipt]);
            hIaa1[coll][ipt]->Draw("same");
            jumSun(10,1,150,1);
            //gPad->RedrawAxis();

            if(coll==4){
                double dx1=0.20;
                //double dx1=0.15;
                if ( ipt == nPtBin )
                    drawText(Form("p_{T}^{#gamma} > %dGeV ", (int)ptBin[ipt-1]), 0.10+dx1+0.1,0.85,1,16);
                else
                    drawText(Form("%dGeV < p_{T}^{#gamma} < %dGeV ", (int)ptBin[ipt-1], (int)ptBin[ipt]), 0.10+dx1,0.85,1,16);
            }
            if(ipt == 1){  
                TLegend *ly = new TLegend(0.3533658,0.7018245,0.6500974,0.9867236,NULL,"brNDC");
                easyLeg(ly);
                ly->SetTextSize(16);
                if(coll==3) ly->AddEntry(hIaa1[3][1],"0-30%","p");
                else if(coll==4) ly->AddEntry(hIaa1[4][1],"30-100%","p");
                ly->Draw("same");
            }
            //if(coll==4&&ipt==4) drawCMSppPbPbDist(0.1,0.9);
        }//ipt
    }//coll
    c5_ratio->SaveAs("pdf/pT_dependence_jetPt_pp_pbpb_Ratio.pdf");
}
