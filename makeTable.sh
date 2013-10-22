#!/bin/sh

g++ makeTable.C $(root-config --cflags --libs) -Werror -Wall -g -o makeTable.exe || exit 1

histnames="meanJetPt_pp_uncertainty \
meanXjg_pp_uncertainty \
meanRjg_pp_uncertainty \
meanJetPt_pbpb_centralityBin1_uncertainty \
meanXjg_pbpb_centralityBin1_uncertainty \
meanRjg_pbpb_centralityBin1_uncertainty \
meanJetPt_pbpb_centralityBin2_uncertainty \
meanXjg_pbpb_centralityBin2_uncertainty \
meanRjg_pbpb_centralityBin2_uncertainty \
meanJetPt_ppb_uncertainty \
meanXjg_ppb_uncertainty \
meanRjg_ppb_uncertainty \
"

rootfiles="relativeSys_dueTo_noElectronRejection.root \
relativeSys_dueTo_MCrecoIso.root \
relativeSys_dueTo_jetEnergyScale.root \
relativeSys_dueTo_jetEnergySmearing.root \
relativeSys_dueTo_noJetResCorr.root \
relativeSys_dueTo_photonEnergyScale.root \
relativeSys_dueTo_photonPurityVaried.root \
relativeSys_merged.root \
"


for histname in $histnames
do
    echo $histname
    for rootFile in $rootfiles
    do
	[ "$rootFile" == "relativeSys_merged.root" ] && histname="${histname}_merged" && echo "\hline"
	./makeTable.exe "relativeSys/$rootFile" "$histname"
    done
    echo ""
done
