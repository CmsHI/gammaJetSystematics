#include "TH1D.h"
#include "TString.h"
#include "stdio.h"
#include "TFile.h"
#include "TMath.h"

void makeTable(TString rootFile, TString histname)
{
  TFile *inFile = TFile::Open(rootFile);

  TH1D *histo;
  
  histo = (TH1D*)inFile->Get(histname);
  if(!histo)
  {
    printf("Missing table: ");
  } else {
    for(int j = 1; j <= histo->GetNbinsX(); j++)
    {
      Double_t err = TMath::Abs(histo->GetBinContent(j));
      if( err*100. > 0.01 )
	printf("%2.2lf%c%c & ", err*100.,'\\', '%');
      else
	printf("- & ");
    }
  }
  printf("%s",rootFile.Data());
  printf("\\\\ \\hline \n");
}

int main(int argc, char *argv[])
{
  makeTable(argv[1],argv[2]);
  return 0;
}
