#!/usr/bin/env bash
cd ../../../downloaded/
tar -xvf SPheno-4.0.3.tar.gz
echo "diff -rupN SPheno-4.0.3/Makefile ../installed/sphenonmssm/4.0.3/Makefile" > patch_sphenonmssm_4.0.3.dif
diff -rupN SPheno-4.0.3/Makefile ../installed/sphenonmssm/4.0.3/Makefile >> patch_sphenonmssm_4.0.3.dif
echo "diff -rupN SPheno-4.0.3/NMSSM/Makefile ../installed/sphenonmssm/4.0.3/NMSSM/Makefile" >> patch_sphenonmssm_4.0.3.dif
diff -rupN  SPheno-4.0.3/NMSSM/Makefile ../installed/sphenonmssm/4.0.3/NMSSM/Makefile >> patch_sphenonmssm_4.0.3.dif
echo "diff -rupN SPheno-4.0.3/src/Makefile ../installed/sphenonmssm/4.0.3/src/Makefile" >> patch_sphenonmssm_4.0.3.dif
diff -rupN SPheno-4.0.3/src/Makefile ../installed/sphenonmssm/4.0.3/src/Makefile >> patch_sphenonmssm_4.0.3.dif
echo "diff -rupN SPheno-4.0.3/NMSSM/SPhenoNMSSM.f90 ../installed/sphenonmssm/4.0.3/NMSSM/SPhenoNMSSM.f90" >> patch_sphenonmssm_4.0.3.dif
diff -rupN SPheno-4.0.3/NMSSM/SPhenoNMSSM.f90 ../installed/sphenonmssm/4.0.3/NMSSM/SPhenoNMSSM.f90  >> patch_sphenonmssm_4.0.3.dif
echo "diff -rupN SPheno-4.0.3/src/Control.F90 ../installed/sphenonmssm/4.0.3/src/Control.F90" >> patch_sphenonmssm_4.0.3.dif
diff -rupN SPheno-4.0.3/src/Control.F90 ../installed/sphenonmssm/4.0.3/src/Control.F90 >> patch_sphenonmssm_4.0.3.dif
echo "diff -rupN SPheno-4.0.3/NMSSM/BranchingRatios_NMSSM.f90 ../installed/sphenonmssm/4.0.3/NMSSM/BranchingRatios_NMSSM.f90" >> patch_sphenonmssm_4.0.3.dif
diff -rupN SPheno-4.0.3/NMSSM/BranchingRatios_NMSSM.f90 ../installed/sphenonmssm/4.0.3/NMSSM/BranchingRatios_NMSSM.f90 >> patch_sphenonmssm_4.0.3.dif
mv patch_sphenonmssm_4.0.3.dif ../patches/sphenonmssm/4.0.3
cd ../patches/sphenonmssm/4.0.3
