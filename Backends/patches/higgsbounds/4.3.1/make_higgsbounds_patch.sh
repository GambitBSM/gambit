#!/usr/bin/env bash
cd ../../../downloaded/
tar -xvf HiggsBounds-4.3.1.tar.gz
echo "diff -rupN HiggsBounds-4.3.1/usefulbits.f90 ../installed/higgsbounds/4.3.1/usefulbits.f90" > patch_higgsbounds_4.3.1.dif
diff -rupN HiggsBounds-4.3.1/usefulbits.f90 ../installed/higgsbounds/4.3.1/usefulbits.f90 >> patch_higgsbounds_4.3.1.dif
echo "diff -rupN HiggsBounds-4.3.1/interpolate.f90 ../installed/higgsbounds/4.3.1/interpolate.f90" >> patch_higgsbounds_4.3.1.dif
diff -rupN HiggsBounds-4.3.1/interpolate.f90 ../installed/higgsbounds/4.3.1/interpolate.f90 >> patch_higgsbounds_4.3.1.dif
mv patch_higgsbounds_4.3.1.dif ../patches/higgsbounds/4.3.1
rm -r HiggsBounds-4.3.1
cd ../patches/higgsbounds/4.3.1
