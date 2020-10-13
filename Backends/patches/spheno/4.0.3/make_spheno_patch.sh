#!/usr/bin/env bash
cd ../../../downloaded/
tar -xvf SPheno-4.0.3.tar.gz
echo "diff -rupN SPheno-4.0.3/Makefile ../installed/spheno/4.0.3/Makefile" > patch_spheno_4.0.3.dif
diff -rupN SPheno-4.0.3/Makefile ../installed/spheno/4.0.3/Makefile >> patch_spheno_4.0.3.dif
echo "diff -rupN SPheno-4.0.3/src/Makefile ../installed/spheno/4.0.3/src/Makefile" >> patch_spheno_4.0.3.dif
diff -rupN SPheno-4.0.3/src/Makefile ../installed/spheno/4.0.3/src/Makefile >> patch_spheno_4.0.3.dif
echo "diff -rupN SPheno-4.0.3/src/SPheno4.f90 ../installed/spheno/4.0.3/src/SPheno4.f90" >> patch_spheno_4.0.3.dif
diff -rupN SPheno-4.0.3/src/SPheno4.f90 ../installed/spheno/4.0.3/src/SPheno4.f90  >> patch_spheno_4.0.3.dif
echo "diff -rupN SPheno-4.0.3/src/Control.F90 ../installed/spheno/4.0.3/src/Control.F90" >> patch_spheno_4.0.3.dif
diff -rupN SPheno-4.0.3/src/Control.F90 ../installed/spheno/4.0.3/src/Control.F90 >> patch_spheno_4.0.3.dif
mv patch_spheno_4.0.3.dif ../patches/spheno/4.0.3
rm -r SPheno-4.0.3
cd ../patches/spheno/4.0.3
