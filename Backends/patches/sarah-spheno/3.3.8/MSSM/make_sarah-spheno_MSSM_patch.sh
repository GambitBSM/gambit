#!/usr/bin/env bash
cd ../../../donwloaded/
#tar -xvf SPheno-3.3.8.tar.gz
echo "diff -rupN SPheno-3.3.8/Makefile ../installed/sphenomssm/3.3.8/Makefile" > patch_sphenomssm_3.3.8.dif
diff -rupN SPheno-3.3.8/Makefile ../installed/sphenomssm/3.3.8/Makefile >> patch_sphenomssm_3.3.8.dif
mkdir SPheno-3.3.8/MSSM
mv ../../Models/data/SARAH/MSSM/EWSB/SPheno/* ./SPheno-3.3.8/MSSM/
echo "diff -rupN  SPheno-3.3.8/MSSM/Makefile ../installed/sphenomssm/3.3.8/MSSM/Makefile" >> patch_sphenomssm_3.3.8.dif
diff -rupN  SPheno-3.3.8/MSSM/Makefile ../installled/sphenomssm/3.3.8/MSSM/Makefile >> patch_sphenomssm_3.3.8.dif
echo "diff -rupN  SPheno-3.3.8/src/Makefile ../installed/sphenomssm/3.3.8/src/Makefile" >> patch_sphenomssm_3.3.8.dif
diff -rupN SPheno-3.3.8/src/Makefile ../installed/sphenomssm/3.3.8/src/Makefile >> patch_sphenomssm_3.3.8.dif
echo "diff -rupN  SPheno-3.3.8/MSSM/SPhenoMSSM.f90 ../installed/sphenomssm/3,3,8/MSSM/SPhenoMSSM.f90" >> patch_sphenomssm_3.3.8.dif
diff -rupN SPheno-3.3.8/MSSM/SPhenoMSSM.f90 ../installed/sphenomssm/3.3.8/MSSM/SPhenoMSSM.f90  >> patch_sphenomssm_3.3.8.dif
mv patch_sphenomssm_3.3.8.dif ../patches/sphenomssm/3.3.8
cd ../patches/sphenomssm/3.3.8
