#!/usr/bin/env bash
cd ../../../../downloaded/
tar -xvf FlexibleSUSY-2.0.1.tar.gz
mkdir FlexibleSUSY-2.0.1/models/CMSSM
cp -r ../../Models/data/FlexibleSUSY/2.0.1/CMSSM/* ./FlexibleSUSY-2.0.1/models/CMSSM/
echo "diff -rupN FlexibleSUSY-2.0.1/models/CMSSM/module.mk ../installed/flexiblesusy/2.0.1/CMSSM/models/CMSSM/module.mk" >> patch_flexiblesusy_2.0.1_CMSSM.dif
diff -rupN FlexibleSUSY-2.0.1/models/CMSSM/module.mk ../installed/flexiblesusy/2.0.1/CMSSM/models/CMSSM/module.mk >> patch_flexiblesusy_2.0.1_CMSSM.dif
echo "diff -rupN FlexibleSUSY-2.0.1/models/CMSSM/CMSSM_slha_io.hpp ../installed/flexiblesusy/2.0.1/CMSSM/models/CMSSM/CMSSM_slha_io.hpp" >> patch_flexiblesusy_2.0.1_CMSSM.dif
diff -rupN FlexibleSUSY-2.0.1/models/CMSSM/CMSSM_slha_io.hpp ../installed/flexiblesusy/2.0.1/CMSSM/models/CMSSM/CMSSM_slha_io.hpp >> patch_flexiblesusy_2.0.1_CMSSM.dif
echo "diff -rupN FlexibleSUSY-2.0.1/models/CMSSM/CMSSM_two_scale_spectrum_generator.hpp ../installed/flexiblesusy/2.0.1/CMSSM/models/CMSSM/CMSSM_two_scale_spectrum_generator.hpp" >> patch_flexiblesusy_2.0.1_CMSSM.dif
diff -rupN FlexibleSUSY-2.0.1/models/CMSSM/CMSSM_two_scale_spectrum_generator.hpp ../installed/flexiblesusy/2.0.1/CMSSM/models/CMSSM/CMSSM_two_scale_spectrum_generator.hpp >> patch_flexiblesusy_2.0.1_CMSSM.dif
echo "diff -rupN FlexibleSUSY-2.0.1/models/CMSSM/CMSSM_two_scale_susy_scale_constraint.cpp ../installed/flexiblesusy/2.0.1/CMSSM/models/CMSSM/CMSSM_two_scale_susy_scale_constraint.cpp" >> patch_flexiblesusy_2.0.1_CMSSM.dif
diff -rupN FlexibleSUSY-2.0.1/models/CMSSM/CMSSM_two_scale_susy_scale_constraint.cpp ../installed/flexiblesusy/2.0.1/CMSSM/models/CMSSM/CMSSM_two_scale_susy_scale_constraint.cpp >> patch_flexiblesusy_2.0.1_CMSSM.dif
mv patch_flexiblesusy_2.0.1_CMSSM.dif ../patches/flexiblesusy/2.0.1/CMSSM
rm -r FlexibleSUSY-2.0.1
cd ../patches/flexiblesusy/2.0.1/CMSSM
