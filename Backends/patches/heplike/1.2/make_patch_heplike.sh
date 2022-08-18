#!/usr/bin/env bash
cd ../../../downloaded/
unzip heplike_1.2.zip
echo "diff -rupN HEPLike-1.2/src/HL_nDimLikelihood.cc ../installed/heplike/1.2/src/HL_nDimLikelihood.cc" > patch_heplike_1.2.dif
diff -rupN HEPLike-1.2/src/HL_nDimLikelihood.cc ../installed/heplike/1.2/src/HL_nDimLikelihood.cc >> patch_heplike_1.2.dif
mv patch_heplike_1.2.dif ../patches/heplike/1.2
rm -r HEPLike-1.2/
cd ../patches/heplike/1.2
