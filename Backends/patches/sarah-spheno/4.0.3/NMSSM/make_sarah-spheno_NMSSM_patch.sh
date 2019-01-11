#!/usr/bin/env bash
cd ../../../../downloaded/
tar -xvf SPheno-4.0.3.tar.gz
mkdir SPheno-4.0.3/NMSSM
cp -r ../../Models/data/SARAH/NMSSM/EWSB/SPheno/* ./SPheno-4.0.3/NMSSM
echo "diff -rupN SPheno-4.0.3/Makefile ../installed/sarah-spheno/4.0.3/NMSSM/Makefile" > patch_sarah-spheno_4.0.3_NMSSM.dif
diff -rupN SPheno-4.0.3/Makefile ../installed/sarah-spheno/4.0.3/NMSSM/Makefile >> patch_sarah-spheno_4.0.3_NMSSM.dif
echo "diff -rupN SPheno-4.0.3/NMSSM/Makefile ../installed/sarah-spheno/4.0.3/NMSSM/NMSSM/Makefile" >> patch_sarah-spheno_4.0.3_NMSSM.dif
diff -rupN  SPheno-4.0.3/NMSSM/Makefile ../installed/sarah-spheno/4.0.3/NMSSM/NMSSM/Makefile >> patch_sarah-spheno_4.0.3_NMSSM.dif
echo "diff -rupN SPheno-4.0.3/src/Makefile ../installed/sarah-spheno/4.0.3/NMSSM/src/Makefile" >> patch_sarah-spheno_4.0.3_NMSSM.dif
diff -rupN SPheno-4.0.3/src/Makefile ../installed/sarah-spheno/4.0.3/NMSSM/src/Makefile >> patch_sarah-spheno_4.0.3_NMSSM.dif
echo "diff -rupN SPheno-4.0.3/NMSSM/SPhenoNMSSM.f90 ../installed/sarah-spheno/4.0.3/NMSSM/NMSSM/SPhenoNMSSM.f90" >> patch_sarah-spheno_4.0.3_NMSSM.dif
diff -rupN SPheno-4.0.3/NMSSM/SPhenoNMSSM.f90 ../installed/sarah-spheno/4.0.3/NMSSM/NMSSM/SPhenoNMSSM.f90  >> patch_sarah-spheno_4.0.3_NMSSM.dif
echo "diff -rupN SPheno-4.0.3/src/Control.F90 ../installed/sarah-spheno/4.0.3/NMSSM/src/Control.F90" >> patch_sarah-spheno_4.0.3_NMSSM.dif
diff -rupN SPheno-4.0.3/src/Control.F90 ../installed/sarah-spheno/4.0.3/NMSSM/src/Control.F90 >> patch_sarah-spheno_4.0.3_NMSSM.dif
echo "diff -rupN SPheno-4.0.3/NMSSM/BranchingRatios_NMSSM.f90 ../installed/sarah-spheno/4.0.3/NMSSM/NMSSM/BranchingRatios_NMSSM.f90" >> patch_sarah-spheno_4.0.3_NMSSM.dif
diff -rupN SPheno-4.0.3/NMSSM/BranchingRatios_NMSSM.f90 ../installed/sarah-spheno/4.0.3/NMSSM/NMSSM/BranchingRatios_NMSSM.f90 >> patch_sarah-spheno_4.0.3_NMSSM.dif
echo "diff -rupN SPheno-4.0.3/NMSSM/AddLoopFunctions.f90 ../installed/sarah-spheno/4.0.3/NMSSM/NMSSM/AddLoopFunctions.f90" >> patch_sarah-spheno_4.0.3_NMSSM.dif
diff -rupN SPheno-4.0.3/NMSSM/AddLoopFunctions.f90 ../installed/sarah-spheno/4.0.3/NMSSM/NMSSM/AddLoopFunctions.f90 >> patch_sarah-spheno_4.0.3_NMSSM.dif
mv patch_sarah-spheno_4.0.3_NMSSM.dif ../patches/sarah-spheno/4.0.3/NMSSM
rm -r SPheno-4.0.3
cd ../patches/sarah-spheno/4.0.3/NMSSM
