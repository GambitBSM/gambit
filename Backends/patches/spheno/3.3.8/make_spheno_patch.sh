#!/usr/bin/env bash
cd ../../
echo "diff -rupN SPheno-3.3.8/Makefile ../installed/sphenomssm/3.3.8/Makefile" > patch_spheno_3.3.8.dif
diff -rupN ../downloaded/SPheno-3.3.8/Makefile ../installed/spheno/3.3.8/Makefile >> patch_spheno_3.3.8.dif
echo "diff -rupN SPheno-3.3.8/src/Makefile ../installed/spheno/3.3.8/src/Makefile" >> patch_spheno_3.3.8.dif
diff -rupN ../downloaded/SPheno-3.3.8/src/Makefile ../installed/spheno/3.3.8/src/Makefile >> patch_spheno_3.3.8.dif
echo "diff -rupN SPheno-3.3.8/SPheno3.f90 ../installed/spheno/3.3.8/src/SPheno3.f90" >> patch_spheno_3.3.8.dif
diff -rupN ../downloaded/SPheno-3.3.8/src/SPheno3.f90 ../installed/spheno/3.3.8/src/SPheno3.f90 >> patch_spheno_3.3.8.dif
cd spheno/3.3.8
mv ../../patch_spheno_3.3.8.dif .
