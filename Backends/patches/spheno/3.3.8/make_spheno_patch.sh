#!/usr/bin/env bash
cd ../../../downloaded/
tar -xvf SPheno-3.3.8.tar.gz
echo "diff -rupN SPheno-3.3.8/Makefile ../installed/spheno/3.3.8/Makefile" > patch_spheno_3.3.8.dif
diff -rupN SPheno-3.3.8/Makefile ../installed/spheno/3.3.8/Makefile >> patch_spheno_3.3.8.dif
echo "diff -rupN SPheno-3.3.8/src/Makefile ../installed/spheno/3.3.8/src/Makefile" >> patch_spheno_3.3.8.dif
diff -rupN SPheno-3.3.8/src/Makefile ../installed/spheno/3.3.8/src/Makefile >> patch_spheno_3.3.8.dif
echo "diff -rupN SPheno-3.3.8/src/SPheno3.f90 ../installed/spheno/3.3.8/src/SPheno3.f90" >> patch_spheno_3.3.8.dif
diff -rupN SPheno-3.3.8/src/SPheno3.f90 ../installed/spheno/3.3.8/src/SPheno3.f90  >> patch_spheno_3.3.8.dif
echo "diff -rupN SPheno-3.3.8/src/Control.F90 ../installed/spheno/3.3.8/src/Control.F90" >> patch_spheno_3.3.8.dif
diff -rupN SPheno-3.3.8/src/Control.F90 ../installed/spheno/3.3.8/src/Control.F90 >> patch_spheno_3.3.8.dif
mv patch_spheno_3.3.8.dif ../patches/spheno/3.3.8
rm -r SPheno-3.3.8
cd ../patches/spheno/3.3.8
