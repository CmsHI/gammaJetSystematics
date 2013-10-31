#!/bin/sh

g++ makeTable.C $(root-config --cflags --libs) -Werror -Wall -g -o makeTable.exe || exit 1

#for single-pane ones
histnames="\
meanXjg_pp_uncertainty \
meanXjg_pbpb_centralityBin1_uncertainty \
meanXjg_pbpb_centralityBin2_uncertainty \
meanXjg_ppb_uncertainty \
meanRjg_ppb_uncertainty \
meanRjg_pp_uncertainty \
meanRjg_pbpb_centralityBin1_uncertainty \
meanRjg_pbpb_centralityBin2_uncertainty \
meanJetPt_pp_uncertainty \
meanJetPt_pbpb_centralityBin1_uncertainty \
meanJetPt_pbpb_centralityBin2_uncertainty \
meanJetPt_ppb_uncertainty \
"

rootfiles="\
relativeSys_dueTo_electronContamination.root \
relativeSys_dueTo_isolation.root \
relativeSys_dueTo_jetEnergyScale.root \
relativeSys_dueTo_jetResCorrection.root \
relativeSys_dueTo_jetResolution.root \
relativeSys_dueTo_photonEnergyScale.root \
relativeSys_dueTo_photonPurity.root \
relativeSys_merged.root \
"

# # # for distributions
# histnames="\
# dNdJetPt_pp_ptBin1_uncertainty \
# dNdXjg_pp_ptBin1_uncertainty \
# dNdphi_pp_ptBin1_uncertainty \
# dNdJetPt_pp_ptBin2_uncertainty \
# dNdXjg_pp_ptBin2_uncertainty \
# dNdphi_pp_ptBin2_uncertainty \
# dNdJetPt_pp_ptBin3_uncertainty \
# dNdXjg_pp_ptBin3_uncertainty \
# dNdphi_pp_ptBin3_uncertainty \
# dNdJetPt_pp_ptBin4_uncertainty \
# dNdXjg_pp_ptBin4_uncertainty \
# dNdphi_pp_ptBin4_uncertainty \
# dNdJetPt_pbpb_centralityBin1_ptBin1_uncertainty \
# dNdXjg_pbpb_centralityBin1_ptBin1_uncertainty \
# dNdphi_pbpb_centralityBin1_ptBin1_uncertainty \
# dNdJetPt_pbpb_centralityBin1_ptBin2_uncertainty \
# dNdXjg_pbpb_centralityBin1_ptBin2_uncertainty \
# dNdphi_pbpb_centralityBin1_ptBin2_uncertainty \
# dNdJetPt_pbpb_centralityBin1_ptBin3_uncertainty \
# dNdXjg_pbpb_centralityBin1_ptBin3_uncertainty \
# dNdphi_pbpb_centralityBin1_ptBin3_uncertainty \
# dNdJetPt_pbpb_centralityBin1_ptBin4_uncertainty \
# dNdXjg_pbpb_centralityBin1_ptBin4_uncertainty \
# dNdphi_pbpb_centralityBin1_ptBin4_uncertainty \
# dNdJetPt_pbpb_centralityBin2_ptBin1_uncertainty \
# dNdXjg_pbpb_centralityBin2_ptBin1_uncertainty \
# dNdphi_pbpb_centralityBin2_ptBin1_uncertainty \
# dNdJetPt_pbpb_centralityBin2_ptBin2_uncertainty \
# dNdXjg_pbpb_centralityBin2_ptBin2_uncertainty \
# dNdphi_pbpb_centralityBin2_ptBin2_uncertainty \
# dNdJetPt_pbpb_centralityBin2_ptBin3_uncertainty \
# dNdXjg_pbpb_centralityBin2_ptBin3_uncertainty \
# dNdphi_pbpb_centralityBin2_ptBin3_uncertainty \
# dNdJetPt_pbpb_centralityBin2_ptBin4_uncertainty \
# dNdXjg_pbpb_centralityBin2_ptBin4_uncertainty \
# dNdphi_pbpb_centralityBin2_ptBin4_uncertainty \
# dNdJetPt_ppb_ptBin1_uncertainty \
# dNdXjg_ppb_ptBin1_uncertainty \
# dNdphi_ppb_ptBin1_uncertainty \
# dNdJetPt_ppb_ptBin2_uncertainty \
# dNdXjg_ppb_ptBin2_uncertainty \
# dNdphi_ppb_ptBin2_uncertainty \
# dNdJetPt_ppb_ptBin3_uncertainty \
# dNdXjg_ppb_ptBin3_uncertainty \
# dNdphi_ppb_ptBin3_uncertainty \
# dNdJetPt_ppb_ptBin4_uncertainty \
# dNdXjg_ppb_ptBin4_uncertainty \
# dNdphi_ppb_ptBin4_uncertainty \
# "

# # for distributions
# histnames="\
# dNdXjg_pp_ptBin1_uncertainty \
# dNdphi_pp_ptBin1_uncertainty \
# dNdXjg_pp_ptBin2_uncertainty \
# dNdphi_pp_ptBin2_uncertainty \
# dNdXjg_pp_ptBin3_uncertainty \
# dNdphi_pp_ptBin3_uncertainty \
# dNdXjg_pp_ptBin4_uncertainty \
# dNdphi_pp_ptBin4_uncertainty \
# dNdXjg_pbpb_centralityBin1_ptBin1_uncertainty \
# dNdphi_pbpb_centralityBin1_ptBin1_uncertainty \
# dNdXjg_pbpb_centralityBin1_ptBin2_uncertainty \
# dNdphi_pbpb_centralityBin1_ptBin2_uncertainty \
# dNdXjg_pbpb_centralityBin1_ptBin3_uncertainty \
# dNdphi_pbpb_centralityBin1_ptBin3_uncertainty \
# dNdXjg_pbpb_centralityBin1_ptBin4_uncertainty \
# dNdphi_pbpb_centralityBin1_ptBin4_uncertainty \
# dNdXjg_pbpb_centralityBin2_ptBin1_uncertainty \
# dNdphi_pbpb_centralityBin2_ptBin1_uncertainty \
# dNdXjg_pbpb_centralityBin2_ptBin2_uncertainty \
# dNdphi_pbpb_centralityBin2_ptBin2_uncertainty \
# dNdXjg_pbpb_centralityBin2_ptBin3_uncertainty \
# dNdphi_pbpb_centralityBin2_ptBin3_uncertainty \
# dNdXjg_pbpb_centralityBin2_ptBin4_uncertainty \
# dNdphi_pbpb_centralityBin2_ptBin4_uncertainty \
# dNdXjg_ppb_ptBin1_uncertainty \
# dNdphi_ppb_ptBin1_uncertainty \
# dNdXjg_ppb_ptBin2_uncertainty \
# dNdphi_ppb_ptBin2_uncertainty \
# dNdXjg_ppb_ptBin3_uncertainty \
# dNdphi_ppb_ptBin3_uncertainty \
# dNdXjg_ppb_ptBin4_uncertainty \
# dNdphi_ppb_ptBin4_uncertainty \
# "

# rootfiles="\
# relativeSysDist/relativeSys_dueTo_noElectronRejection.root \
# relativeSysDist/relativeSys_dueTo_MCrecoIso.root \
# relativeSysDist/relativeSys_dueTo_jetEnergyScale.root \
# relativeSysDist/relativeSys_dueTo_jetEnergySmeared.root \
# relativeSysDist/relativeSys_dueTo_noJetResCorr.root \
# relativeSysDist/relativeSys_dueTo_photonEnergyScale.root \
# relativeSysDist/relativeSys_dueTo_photonPurityVaried.root \
# relativeSysDist/relativeSys_merged.root \
# "

for histname in $histnames
do
    echo $histname
    for rootFile in $rootfiles
    do
	[ "$rootFile" == "relativeSys_merged.root" ] && histname="${histname}_merged" && echo "\hline"
	./makeTable.exe "$rootFile" "$histname"
    done
    echo ""
done
