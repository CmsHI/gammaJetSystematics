void rootlogon()
{
  //gSystem->Load("libFWCoreFWLite.so");
  //AutoLibraryLoader::enable();
  //gInterpreter->ExecuteMacro("~/MITStyle.C");

  gStyle->SetErrorX(0);
  gStyle->SetPalette(1,0);
  gStyle->SetPadColor(0);
  gStyle->SetPadBorderSize(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetCanvasBorderSize(0);
  gStyle->SetFrameBorderMode(0);
  gStyle->SetFrameLineColor(0);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);

  //gStyle->SetTextFont(62);
  gStyle->SetTextFont(43);
  //gStyle->SetTextSize(0.02);
  gStyle->SetTextSize(15);
  
  // gStyle->SetLabelFont(42,"XYZ");
  // gStyle->SetTitleFont(42,"XYZ");
  gStyle->SetLabelFont(43,"XYZ");
  gStyle->SetLabelSize(15,"XYZ");
  gStyle->SetTitleFont(43,"XYZ");
  gStyle->SetTitleSize(15,"XYZ");

  gStyle->SetTitleColor(1,"XYZ");

  
  gStyle->SetTitleFillColor(0);
  gStyle->SetTitleBorderSize(0);
  //gStyle->SetTitleXSize(.055);
  //gStyle->SetTitleYSize(.055);
  //gStyle->SetTitleXOffset(1.25);
  //gStyle->SetTitleYOffset(1.75);
  gStyle->SetTitleOffset(1.25,"X");
  gStyle->SetTitleOffset(1.5,"Y");
  //gStyle->SetLabelSize(0.045,"XYZ");
  //gStyle->SetLabelSize(0.06,"XYZ");
  gStyle->SetLabelOffset(0.01,"X");
  gStyle->SetLabelOffset(0.01,"Y");

  gStyle->SetHistFillColor(1);
  gStyle->SetHistFillStyle(0);
  gStyle->SetHistLineColor(1);
  gStyle->SetHistLineStyle(0);
  gStyle->SetHistLineWidth(1);
  gStyle->SetEndErrorSize(0);
  gStyle->SetMarkerStyle(20);
  gStyle->SetMarkerSize(1);
  gStyle->SetOptFit(1111);
  gStyle->SetStatColor(0);
  gStyle->SetStatBorderSize(1);

  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);

  gStyle->SetPadLeftMargin(0.15);
  //gStyle->SetPadLeftMargin(0.3);
  gStyle->SetPadBottomMargin(0.15);
  //gStyle->SetPadTopMargin(0.05);
  gStyle->SetPadTopMargin(0.10);
  //gStyle->SetPadRightMargin(0.12);
  gStyle->SetPadRightMargin(0.05);

  gStyle->SetLegendBorderSize(0);
  gStyle->SetLegendFillColor(0);
  //gStyle->SetLegendFont(43);
  
  gROOT->ForceStyle();
}
