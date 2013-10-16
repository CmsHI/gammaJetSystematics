#include "TH1D.h"
#include "TString.h"
#include "stdio.h"
#include "TFile.h"
#include "TMath.h"

void makeTable(TString rootFile, TString histname)
{
  TFile *inFile = TFile::Open(rootFile);

  TH1D *histo;
  
  // const Int_t numNames = 8;
  // TString histnames[] = {
  //   //"dNdJetPt_IaaBin_pp_ptBin1_uncertainty"
  //   //"dNdJetPt_IaaBin_pp_ptBin2_uncertainty"
  //   //"dNdJetPt_IaaBin_pp_ptBin3_uncertainty"
  //   //"dNdJetPt_IaaBin_pp_ptBin4_uncertainty"
  //   "meanJetPt_pp_uncertainty",
  //   "meanRjg_pp_uncertainty",
  //   //"dNdJetPt_IaaBin_pbpb_centralityBin1_ptBin1_uncertainty"
  //   //"dNdJetPt_IaaBin_pbpb_centralityBin1_ptBin2_uncertainty"
  //   //"dNdJetPt_IaaBin_pbpb_centralityBin1_ptBin3_uncertainty"
  //   //"dNdJetPt_IaaBin_pbpb_centralityBin1_ptBin4_uncertainty"
  //   "meanJetPt_pbpb_centralityBin1_uncertainty",
  //   "meanRjg_pbpb_centralityBin1_uncertainty",
  //   //"dNdJetPt_IaaBin_pbpb_centralityBin2_ptBin1_uncertainty",
  //   //"dNdJetPt_IaaBin_pbpb_centralityBin2_ptBin2_uncertainty",
  //   //"dNdJetPt_IaaBin_pbpb_centralityBin2_ptBin3_uncertainty",
  //   //"dNdJetPt_IaaBin_pbpb_centralityBin2_ptBin4_uncertainty",
  //   "meanJetPt_pbpb_centralityBin2_uncertainty",
  //   "meanRjg_pbpb_centralityBin2_uncertainty",
  //   //"dNdJetPt_IaaBin_ppb_ptBin1_uncertainty"
  //   //"dNdJetPt_IaaBin_ppb_ptBin2_uncertainty"
  //   //"dNdJetPt_IaaBin_ppb_ptBin3_uncertainty"
  //   //"dNdJetPt_IaaBin_ppb_ptBin4_uncertainty"
  //   "meanJetPt_ppb_uncertainty",
  //   "meanRjg_ppb_uncertainty"
  // }


  //for(int i = 0; i<numNames; i++)
  //{
  //printf("%s\n",histname.Data());
  histo = (TH1D*)inFile->Get(histname);
  if(!histo)
  {
    printf("Missing table: ");
  } else {
    for(int j = 1; j <= histo->GetNbinsX(); j++)
    {
      printf("%lf &",TMath::Abs(histo->GetBinContent(j)));
    }
  }
  printf("%s",rootFile.Data());
  printf("\\\\ \\hline \n");
  //}
}

int main(int argc, char *argv[])
{
  makeTable(argv[1],argv[2]);
  return 0;
}
