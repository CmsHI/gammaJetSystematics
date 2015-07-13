###############################
# Xjg and Dphi
root -l -b -q 'fit_xjg_dphi.C++("nominal_vtxCentWeighted")'
root -l -b -q 'fit_xjg_dphi.C+("photonEnergyScaleMinus")'
root -l -b -q 'fit_xjg_dphi.C+("photonEnergyScalePlus")'
root -l -b -q 'fit_xjg_dphi.C+("noJetResCorr")'
root -l -b -q 'fit_xjg_dphi.C+("electronContamination")'
root -l -b -q 'fit_xjg_dphi.C+("MCrecoIso")'
root -l -b -q 'fit_xjg_dphi.C+("MCgenIso")'
root -l -b -q 'fit_xjg_dphi.C+("photonPurityVaried")'
root -l -b -q 'fit_xjg_dphi.C+("jetEnergyScalePlus")'
root -l -b -q 'fit_xjg_dphi.C+("jetEnergyScaleMinus")'
root -l -b -q 'fit_xjg_dphi.C+("jetResolution")'

###############################
# Jet Pt dist
# smearing and scale integrated 
#root -l -b -q 'fitJetPt_smearing_scale_integrated.C++(1.02,0)'
#root -l -b -q 'fitJetPt_smearing_scale_integrated.C+(0.98,0)'
# smearing and scale separately
root -l -b -q 'fitJetPt_smearing_scale_integrated.C++(1.02,1)'
root -l -b -q 'fitJetPt_smearing_scale_integrated.C+(0.98,1)'
root -l -b -q 'fitJetPt_smearing_scale_integrated.C+(1.00,0)'
