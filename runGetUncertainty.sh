root -l -b -q 'getSysUncert.C+("resultHistograms.root","resultHistograms_electronContamination.root")'
root -l -b -q 'getSysUncert.C+("resultHistograms.root","resultHistograms_photonEnergyScaleMinus.root")'
root -l -b -q 'getSysUncert.C+("resultHistograms.root","resultHistograms_photonEnergyScalePlus.root")'

root -l -b -q 'getSysUncert.C+("resultHistograms.root","resultHistograms_jetEnegyScalePlus.root")'
root -l -b -q 'getSysUncert.C+("resultHistograms.root","resultHistograms_jetEnegyScaleMinus.root")'
root -l -b -q 'getSysUncert.C+("resultHistograms.root","resultHistograms_jetResolution.root")'
root -l -b -q 'getSysUncert.C+("resultHistograms.root","resultHistograms_jetResCorrection.root")'

root -l -b -q 'getSysUncert.C+("resultHistograms_photonPurity.root","resultHistograms_photonPurity_shifted.root")'
root -l -b -q 'getSysUncert.C+("resultHistograms_MC_genIsoPhoton.root","resultHistograms_MC_recoIsoPhoton.root")'


# change the name of the some files 
mv relativeSys_dueTo_photonPurity_shifted.root relativeSys_dueTo_photonPurity.root
mv relativeSys_dueTo_MC_recoIsoPhoton.root relativeSys_dueTo_isolation.root
