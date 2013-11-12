#void getSysUncertDist (
#                       TString fname2 = "noJetResCorr",
#                       TString fname1 = "nominal",
#                       float scaleFactor= 1  // The non-unity scale factor is for electron : 0.25                                        

root -l   'getSysUncertDist.C("noJetResCorr","nominal",1)'

root -l   'getSysUncertDist.C("jetEnergyScalePlus","nominal",1)'
root -l   'getSysUncertDist.C("jetEnergyScaleMinus","nominal",1)'

root -l   'getSysUncertDist.C("jetEnergySmeared","nominal",1)'

root -l   'getSysUncertDist.C("MCrecoIso","MCgenIso",1)'

root -l   'getSysUncertDist.C("photonPurityVaried","nominal",1)'

root -l   'getSysUncertDist.C("noElectronRejection","nominal",0.25)'

root -l   'getSysUncertDist.C("photonEnergyScalePlus","nominal",1)'
root -l   'getSysUncertDist.C("photonEnergyScaleMinus","nominal",1)'


