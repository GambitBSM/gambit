#!/bin/sh

# Firts compare slha file that after transforming slhea object to internally stored one to fs file from  standalone 

# slha file modified from contrib/MassSpectra/flexiblesusy/LesHouches.out.CMSSM
fs_slha_2loop="LesHouches.out.CMSSM.test_2L_RGEs.mod"
gambit_slha_2loop="../pre_verify_contents_MSSM.slha"

# strip comments
grep -o '^[^#]*' $fs_slha_2loop > fs_slha_clean
grep -o '^[^#]*' $gambit_slha_2loop > gambit_slha_clean

# note in current set pre_verify_contents gets changed when test_spec in get_CMSSM_spectrum_FS and this vreaks comparison.
numdiff --relative-tolerance 1e-8 --absolute-tolerance 1e-8 fs_slha_clean gambit_slha_clean

# compare GAMBIT slha output from initialising spectrum with FS interface vs GAMBIT output from initialising with slhafile from standalone run of FS
gamit_slha_from_fs_interface="../GAMBIT_unimproved_spectrum.slha2"
gambit_slha_from_fs_output_file="../GAMBIT_test_unimproved_spectrum.slha2"

# strip comments
grep -o '^[^#]*' $gamit_slha_from_fs_interface > gb_fs_interface_clean
grep -o '^[^#]*' $gambit_slha_from_fs_output_file > gb_fs_file_clean

numdiff --relative-tolerance 1e-8 --absolute-tolerance 1e-8 gb_fs_interface_clean gb_fs_file_clean


# changes to LseHouches.out.CMSSM.test.mod:

# delete blocks MODSEL, FlexibleSUSY and FlexibleSUSYInput
# added added DMASS blocks, and Blocks BMu, VEVs, sin(theta_W) (Dbar)
# added photon and gluon masses to MASS block.  These are added in SpectrumContents::MSSM::transformInputSLHAea
# adding fake g1 entry in gauge block, which is added by gambit in SpectrumContents::MSSM::transformInputSLHAea

# chnages to LesHHouches.out.CMSSM.mod:

# as per changes to LseHouches.out.CMSSM.test.mode
# plus chnage MW pole input to 80.385 (this has some numerical impact at < 10^-6 rel error plus signs and 0 vs 1e-15 numerical noise in mixing matrix elements
# see numdiff --relative-tolerance 1e-6 --essential LesHouches.out.CMSSM.test Leshouches.out.CMSSM.original | less in contrib/MassSpectra/flexiblesusy

# known differences

# 1) 2-loop vs 3-loop rges leads to 1e-2 effects in some entries e.g. MSUSY.
# see numdiff between pre_verify_contents_MSSM.slha and pre_verify_contents_MSSM.slha.modyaml_beta3loop or comparing FS files. 
# 2)  oneset.setPoleMmuon(sminputs.mMu); at code level is needed to get SMINPUTS block matching FlexibleSUSY.  Largets actual numerical impact is at 1e-7 relative error level on Te(2,2) ie muon soft trilnear.
# 3) oneset.setAlphaSInput(sminputs.alphaS);//tested: affects gauge couplings at 2-3e-3 level and charm yukawa at 1e-2
# 4) oneset.setAlphaEmInput(1.0 / sminputs.alphainv); //tested: 1e-4 diff typically, but 1e-3 in some mixing elements and 1e-2 in GUT scale value


# questions
# Should we just pass on the FS settings and MODSEL now we use SLHAea interface?
# How can we test the generation of the GAMBIT slha file uis correct in an automated way. i just found one bug that only shows up by comparing between the generated GAMBIT slha file and the one that is stored.  This bug was from an error in the getter maps due to an arror in the add_parameter in the contents object.
