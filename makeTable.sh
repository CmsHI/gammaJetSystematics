#!/bin/sh

histnames="meanJetPt_pp_uncertainty meanRjg_pp_uncertainty meanJetPt_pbpb_centralityBin1_uncertainty meanRjg_pbpb_centralityBin1_uncertainty meanJetPt_pbpb_centralityBin2_uncertainty meanRjg_pbpb_centralityBin2_uncertainty meanJetPt_ppb_uncertainty meanRjg_ppb_uncertainty"


for histname in $histnames
do
    echo $histname
    for rootFile in relativeSys_dueTo_*.root
    do
	./makeTable.exe "$rootFile" "$histname"
    done
    echo ""
done