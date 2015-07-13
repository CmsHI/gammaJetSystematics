./run_fit.sh
./run_getSysUncert.sh
root -l -b -q 'mergeSys.C++'
root -l -b -q 'drawFinalPlot.C++'
