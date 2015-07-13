#####################################################################
### getSysUncert_Iaa_smearing.C have to be done after getSysUncert.C 
### TFile option :: "update"                           "recreate" 

# other systematics
root -l -b -q 'getSysUncert.C++("nominal_vtxCentWeighted","electronContamination",0.25)'
root -l -b -q 'getSysUncert.C+("nominal_vtxCentWeighted","photonEnergyScaleMinus")'
root -l -b -q 'getSysUncert.C+("nominal_vtxCentWeighted","photonEnergyScalePlus")'
root -l -b -q 'getSysUncert.C+("nominal_vtxCentWeighted","noJetResCorr")'
root -l -b -q 'getSysUncert.C+("nominal_vtxCentWeighted","photonPurityVaried")'
root -l -b -q 'getSysUncert.C+("MCgenIso","MCrecoIso")'
root -l -b -q 'getSysUncert.C+("nominal_vtxCentWeighted","jetEnergyScalePlus")'
root -l -b -q 'getSysUncert.C+("nominal_vtxCentWeighted","jetEnergyScaleMinus")'
root -l -b -q 'getSysUncert.C+("nominal_vtxCentWeighted","jetResolution")'

root -l -b -q 'selectPM.C+("photonEnergyScaleMinus","photonEnergyScalePlus","photonEnergyScale")'
mv relativeSys/relativeSys_dueTo_MCrecoIso.root relativeSys/relativeSys_dueTo_isolation.root

# smearing and scale separately
root -l -b -q 'getSysUncert_Iaa_smearing.C+("smearingNscale1.00","jetResolution")'
root -l -b -q 'getSysUncert_Iaa_smearing.C+("scale0.98","jetEnergyScaleMinus")'
root -l -b -q 'getSysUncert_Iaa_smearing.C+("scale1.02","jetEnergyScalePlus)'
root -l -b -q 'selectPM.C+("jetEnergyScaleMinus","jetEnergyScalePlus","jetEnergyScale")'
#root -l -b -q 'selectPM_Iaa_smearing.C+("scale0.98","scale1.02","jetEnergyScale")'

# smearing and scale integrated
#root -l -b -q 'getSysUncert_Iaa_smearing.C++("smearingNscale0.98")'
#root -l -b -q 'getSysUncert_Iaa_smearing.C+("smearingNscale1.02")'
#root -l -b -q 'selectPM.C++("smearingNscale0.98","smearingNscale1.02","smearingNscale")'


