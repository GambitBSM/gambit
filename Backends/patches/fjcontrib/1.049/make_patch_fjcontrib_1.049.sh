cd ../../../downloaded
tar -xvf *fjcontrib*
echo "diff -rupN fjcontrib-1.049/LundPlane/EEHelpers.hh ../installed/fjcontrib/1.049/LundPlane/EEHelpers.hh" >> patch_fjcontrib_1.049.dif
diff -rupN fjcontrib-1.049/LundPlane/EEHelpers.hh ../installed/fjcontrib/1.049/LundPlane/EEHelpers.hh >> patch_fjcontrib_1.049.dif

mv patch_fjcontrib_1.049.dif ../patches/fjcontrib/1.049/
cd ../patches/fjcontrib/1.049
