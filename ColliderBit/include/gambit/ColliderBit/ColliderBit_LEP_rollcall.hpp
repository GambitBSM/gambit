//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Rollcall header for ColliderBit module LEP functions.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Abram Krislock
///          (a.m.b.krislock@fys.uio.no)
///
///  \author Aldo Saavedra
///
///  \author Christopher Rogan
///          (christophersrogan@gmail.com)
///  \date 2015 Apr
///
///  \author Are Raklev
///          (ahye@fys.uio.no)
///  \date 2018 Feb
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2015 Jul
///
///  \author Andy Buckley
///          (andy.buckley@cern.ch)
///  \date 2017 Jun
///
///  *********************************************

#ifndef __ColliderBit_LEP_rollcall_hpp__
#define __ColliderBit_LEP_rollcall_hpp__


#define MODULE ColliderBit

  ///////////// LEP limits ////////////////////////

  // CoM energy 207GeV
  // LEP production cross sections and uncertainties: neutralinos
  QUICK_FUNCTION(ColliderBit, LEP207_xsec_chi00_11, NEW_CAPABILITY, LEP207_SLHA1_convention_xsec_chi00_11, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))

  // CoM energy 208GeV
  // LEP production cross sections and uncertainties: selectrons
  QUICK_FUNCTION(ColliderBit, LEP208_xsec_selselbar, NEW_CAPABILITY, LEP208_SLHA1_convention_xsec_selselbar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP208_xsec_selserbar, NEW_CAPABILITY, LEP208_SLHA1_convention_xsec_selserbar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP208_xsec_serserbar, NEW_CAPABILITY, LEP208_SLHA1_convention_xsec_serserbar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP208_xsec_serselbar, NEW_CAPABILITY, LEP208_SLHA1_convention_xsec_serselbar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (LEP208_xsec_selserbar, triplet<double>))
  QUICK_FUNCTION(ColliderBit, LEP208_xsec_se1se1bar, NEW_CAPABILITY, LEP208_SLHA1_convention_xsec_se1se1bar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP208_xsec_se1se2bar, NEW_CAPABILITY, LEP208_SLHA1_convention_xsec_se1se2bar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP208_xsec_se2se2bar, NEW_CAPABILITY, LEP208_SLHA1_convention_xsec_se2se2bar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP208_xsec_se2se1bar, NEW_CAPABILITY, LEP208_SLHA1_convention_xsec_se2se1bar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (LEP208_xsec_se1se2bar, triplet<double>))
  // LEP production cross sections and uncertainties: smuons
  QUICK_FUNCTION(ColliderBit, LEP208_xsec_smulsmulbar, NEW_CAPABILITY, LEP208_SLHA1_convention_xsec_smulsmulbar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP208_xsec_smulsmurbar, NEW_CAPABILITY, LEP208_SLHA1_convention_xsec_smulsmurbar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP208_xsec_smursmurbar, NEW_CAPABILITY, LEP208_SLHA1_convention_xsec_smursmurbar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP208_xsec_smursmulbar, NEW_CAPABILITY, LEP208_SLHA1_convention_xsec_smursmulbar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (LEP208_xsec_smulsmurbar, triplet<double>))
  QUICK_FUNCTION(ColliderBit, LEP208_xsec_smu1smu1bar, NEW_CAPABILITY, LEP208_SLHA1_convention_xsec_smu1smu1bar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP208_xsec_smu1smu2bar, NEW_CAPABILITY, LEP208_SLHA1_convention_xsec_smu1smu2bar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP208_xsec_smu2smu2bar, NEW_CAPABILITY, LEP208_SLHA1_convention_xsec_smu2smu2bar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP208_xsec_smu2smu1bar, NEW_CAPABILITY, LEP208_SLHA1_convention_xsec_smu2smu1bar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (LEP208_xsec_smu1smu2bar, triplet<double>))
  // LEP production cross sections and uncertainties: staus
  QUICK_FUNCTION(ColliderBit, LEP208_xsec_staulstaulbar, NEW_CAPABILITY, LEP208_SLHA1_convention_xsec_staulstaulbar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP208_xsec_staulstaurbar, NEW_CAPABILITY, LEP208_SLHA1_convention_xsec_staulstaurbar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP208_xsec_staurstaurbar, NEW_CAPABILITY, LEP208_SLHA1_convention_xsec_staurstaurbar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP208_xsec_staurstaulbar, NEW_CAPABILITY, LEP208_SLHA1_convention_xsec_staurstaulbar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (LEP208_xsec_staulstaurbar, triplet<double>))
  QUICK_FUNCTION(ColliderBit, LEP208_xsec_stau1stau1bar, NEW_CAPABILITY, LEP208_SLHA1_convention_xsec_stau1stau1bar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP208_xsec_stau1stau2bar, NEW_CAPABILITY, LEP208_SLHA1_convention_xsec_stau1stau2bar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP208_xsec_stau2stau2bar, NEW_CAPABILITY, LEP208_SLHA1_convention_xsec_stau2stau2bar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP208_xsec_stau2stau1bar, NEW_CAPABILITY, LEP208_SLHA1_convention_xsec_stau2stau1bar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (LEP208_xsec_stau1stau2bar, triplet<double>))
  // LEP production cross sections and uncertainties: neutralinos
  QUICK_FUNCTION(ColliderBit, LEP208_xsec_chi00_11, NEW_CAPABILITY, LEP208_SLHA1_convention_xsec_chi00_11, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP208_xsec_chi00_12, NEW_CAPABILITY, LEP208_SLHA1_convention_xsec_chi00_12, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP208_xsec_chi00_13, NEW_CAPABILITY, LEP208_SLHA1_convention_xsec_chi00_13, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP208_xsec_chi00_14, NEW_CAPABILITY, LEP208_SLHA1_convention_xsec_chi00_14, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP208_xsec_chi00_22, NEW_CAPABILITY, LEP208_SLHA1_convention_xsec_chi00_22, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP208_xsec_chi00_23, NEW_CAPABILITY, LEP208_SLHA1_convention_xsec_chi00_23, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP208_xsec_chi00_24, NEW_CAPABILITY, LEP208_SLHA1_convention_xsec_chi00_24, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP208_xsec_chi00_33, NEW_CAPABILITY, LEP208_SLHA1_convention_xsec_chi00_33, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP208_xsec_chi00_34, NEW_CAPABILITY, LEP208_SLHA1_convention_xsec_chi00_34, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP208_xsec_chi00_44, NEW_CAPABILITY, LEP208_SLHA1_convention_xsec_chi00_44, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  // LEP production cross sections and uncertainties: charginos
  QUICK_FUNCTION(ColliderBit, LEP208_xsec_chipm_11, NEW_CAPABILITY, LEP208_SLHA1_convention_xsec_chipm_11, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP208_xsec_chipm_12, NEW_CAPABILITY, LEP208_SLHA1_convention_xsec_chipm_12, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP208_xsec_chipm_22, NEW_CAPABILITY, LEP208_SLHA1_convention_xsec_chipm_22, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP208_xsec_chipm_21, NEW_CAPABILITY, LEP208_SLHA1_convention_xsec_chipm_21, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (LEP208_xsec_chipm_12, triplet<double>))

  // CoM energy 205GeV
  // LEP production cross sections and uncertainties: selectrons
  QUICK_FUNCTION(ColliderBit, LEP205_xsec_selselbar, NEW_CAPABILITY, LEP205_SLHA1_convention_xsec_selselbar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP205_xsec_selserbar, NEW_CAPABILITY, LEP205_SLHA1_convention_xsec_selserbar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP205_xsec_serserbar, NEW_CAPABILITY, LEP205_SLHA1_convention_xsec_serserbar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP205_xsec_serselbar, NEW_CAPABILITY, LEP205_SLHA1_convention_xsec_serselbar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (LEP205_xsec_selserbar, triplet<double>))
  QUICK_FUNCTION(ColliderBit, LEP205_xsec_se1se1bar, NEW_CAPABILITY, LEP205_SLHA1_convention_xsec_se1se1bar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP205_xsec_se1se2bar, NEW_CAPABILITY, LEP205_SLHA1_convention_xsec_se1se2bar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP205_xsec_se2se2bar, NEW_CAPABILITY, LEP205_SLHA1_convention_xsec_se2se2bar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP205_xsec_se2se1bar, NEW_CAPABILITY, LEP205_SLHA1_convention_xsec_se2se1bar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (LEP205_xsec_se1se2bar, triplet<double>))
  // LEP production cross sections and uncertainties: smuons
  QUICK_FUNCTION(ColliderBit, LEP205_xsec_smulsmulbar, NEW_CAPABILITY, LEP205_SLHA1_convention_xsec_smulsmulbar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP205_xsec_smulsmurbar, NEW_CAPABILITY, LEP205_SLHA1_convention_xsec_smulsmurbar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP205_xsec_smursmurbar, NEW_CAPABILITY, LEP205_SLHA1_convention_xsec_smursmurbar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP205_xsec_smursmulbar, NEW_CAPABILITY, LEP205_SLHA1_convention_xsec_smursmulbar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (LEP205_xsec_smulsmurbar, triplet<double>))
  QUICK_FUNCTION(ColliderBit, LEP205_xsec_smu1smu1bar, NEW_CAPABILITY, LEP205_SLHA1_convention_xsec_smu1smu1bar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP205_xsec_smu1smu2bar, NEW_CAPABILITY, LEP205_SLHA1_convention_xsec_smu1smu2bar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP205_xsec_smu2smu2bar, NEW_CAPABILITY, LEP205_SLHA1_convention_xsec_smu2smu2bar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP205_xsec_smu2smu1bar, NEW_CAPABILITY, LEP205_SLHA1_convention_xsec_smu2smu1bar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (LEP205_xsec_smu1smu2bar, triplet<double>))
  // LEP production cross sections and uncertainties: staus
  QUICK_FUNCTION(ColliderBit, LEP205_xsec_staulstaulbar, NEW_CAPABILITY, LEP205_SLHA1_convention_xsec_staulstaulbar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP205_xsec_staulstaurbar, NEW_CAPABILITY, LEP205_SLHA1_convention_xsec_staulstaurbar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP205_xsec_staurstaurbar, NEW_CAPABILITY, LEP205_SLHA1_convention_xsec_staurstaurbar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP205_xsec_staurstaulbar, NEW_CAPABILITY, LEP205_SLHA1_convention_xsec_staurstaulbar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (LEP205_xsec_staulstaurbar, triplet<double>))
  QUICK_FUNCTION(ColliderBit, LEP205_xsec_stau1stau1bar, NEW_CAPABILITY, LEP205_SLHA1_convention_xsec_stau1stau1bar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP205_xsec_stau1stau2bar, NEW_CAPABILITY, LEP205_SLHA1_convention_xsec_stau1stau2bar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP205_xsec_stau2stau2bar, NEW_CAPABILITY, LEP205_SLHA1_convention_xsec_stau2stau2bar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP205_xsec_stau2stau1bar, NEW_CAPABILITY, LEP205_SLHA1_convention_xsec_stau2stau1bar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (LEP205_xsec_stau1stau2bar, triplet<double>))
  // LEP production cross sections and uncertainties: neutralinos
  QUICK_FUNCTION(ColliderBit, LEP205_xsec_chi00_11, NEW_CAPABILITY, LEP205_SLHA1_convention_xsec_chi00_11, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP205_xsec_chi00_12, NEW_CAPABILITY, LEP205_SLHA1_convention_xsec_chi00_12, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP205_xsec_chi00_13, NEW_CAPABILITY, LEP205_SLHA1_convention_xsec_chi00_13, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP205_xsec_chi00_14, NEW_CAPABILITY, LEP205_SLHA1_convention_xsec_chi00_14, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP205_xsec_chi00_22, NEW_CAPABILITY, LEP205_SLHA1_convention_xsec_chi00_22, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP205_xsec_chi00_23, NEW_CAPABILITY, LEP205_SLHA1_convention_xsec_chi00_23, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP205_xsec_chi00_24, NEW_CAPABILITY, LEP205_SLHA1_convention_xsec_chi00_24, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP205_xsec_chi00_33, NEW_CAPABILITY, LEP205_SLHA1_convention_xsec_chi00_33, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP205_xsec_chi00_34, NEW_CAPABILITY, LEP205_SLHA1_convention_xsec_chi00_34, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP205_xsec_chi00_44, NEW_CAPABILITY, LEP205_SLHA1_convention_xsec_chi00_44, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  // LEP production cross sections and uncertainties: charginos
  QUICK_FUNCTION(ColliderBit, LEP205_xsec_chipm_11, NEW_CAPABILITY, LEP205_SLHA1_convention_xsec_chipm_11, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP205_xsec_chipm_12, NEW_CAPABILITY, LEP205_SLHA1_convention_xsec_chipm_12, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP205_xsec_chipm_22, NEW_CAPABILITY, LEP205_SLHA1_convention_xsec_chipm_22, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP205_xsec_chipm_21, NEW_CAPABILITY, LEP205_SLHA1_convention_xsec_chipm_21, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (LEP205_xsec_chipm_12, triplet<double>))

  // CoM energy 188GeV
  // LEP production cross sections and uncertainties: selectrons
  QUICK_FUNCTION(ColliderBit, LEP188_xsec_selselbar, NEW_CAPABILITY, LEP188_SLHA1_convention_xsec_selselbar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP188_xsec_selserbar, NEW_CAPABILITY, LEP188_SLHA1_convention_xsec_selserbar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP188_xsec_serserbar, NEW_CAPABILITY, LEP188_SLHA1_convention_xsec_serserbar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP188_xsec_serselbar, NEW_CAPABILITY, LEP188_SLHA1_convention_xsec_serselbar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (LEP188_xsec_selserbar, triplet<double>))
  QUICK_FUNCTION(ColliderBit, LEP188_xsec_se1se1bar, NEW_CAPABILITY, LEP188_SLHA1_convention_xsec_se1se1bar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP188_xsec_se1se2bar, NEW_CAPABILITY, LEP188_SLHA1_convention_xsec_se1se2bar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP188_xsec_se2se2bar, NEW_CAPABILITY, LEP188_SLHA1_convention_xsec_se2se2bar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP188_xsec_se2se1bar, NEW_CAPABILITY, LEP188_SLHA1_convention_xsec_se2se1bar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (LEP188_xsec_se1se2bar, triplet<double>))
  // LEP production cross sections and uncertainties: smuons
  QUICK_FUNCTION(ColliderBit, LEP188_xsec_smulsmulbar, NEW_CAPABILITY, LEP188_SLHA1_convention_xsec_smulsmulbar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP188_xsec_smulsmurbar, NEW_CAPABILITY, LEP188_SLHA1_convention_xsec_smulsmurbar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP188_xsec_smursmurbar, NEW_CAPABILITY, LEP188_SLHA1_convention_xsec_smursmurbar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP188_xsec_smursmulbar, NEW_CAPABILITY, LEP188_SLHA1_convention_xsec_smursmulbar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (LEP188_xsec_smulsmurbar, triplet<double>))
  QUICK_FUNCTION(ColliderBit, LEP188_xsec_smu1smu1bar, NEW_CAPABILITY, LEP188_SLHA1_convention_xsec_smu1smu1bar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP188_xsec_smu1smu2bar, NEW_CAPABILITY, LEP188_SLHA1_convention_xsec_smu1smu2bar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP188_xsec_smu2smu2bar, NEW_CAPABILITY, LEP188_SLHA1_convention_xsec_smu2smu2bar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP188_xsec_smu2smu1bar, NEW_CAPABILITY, LEP188_SLHA1_convention_xsec_smu2smu1bar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (LEP188_xsec_smu1smu2bar, triplet<double>))
  // LEP production cross sections and uncertainties: staus
  QUICK_FUNCTION(ColliderBit, LEP188_xsec_staulstaulbar, NEW_CAPABILITY, LEP188_SLHA1_convention_xsec_staulstaulbar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP188_xsec_staulstaurbar, NEW_CAPABILITY, LEP188_SLHA1_convention_xsec_staulstaurbar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP188_xsec_staurstaurbar, NEW_CAPABILITY, LEP188_SLHA1_convention_xsec_staurstaurbar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP188_xsec_staurstaulbar, NEW_CAPABILITY, LEP188_SLHA1_convention_xsec_staurstaulbar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (LEP188_xsec_staulstaurbar, triplet<double>))
  QUICK_FUNCTION(ColliderBit, LEP188_xsec_stau1stau1bar, NEW_CAPABILITY, LEP188_SLHA1_convention_xsec_stau1stau1bar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP188_xsec_stau1stau2bar, NEW_CAPABILITY, LEP188_SLHA1_convention_xsec_stau1stau2bar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP188_xsec_stau2stau2bar, NEW_CAPABILITY, LEP188_SLHA1_convention_xsec_stau2stau2bar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP188_xsec_stau2stau1bar, NEW_CAPABILITY, LEP188_SLHA1_convention_xsec_stau2stau1bar, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (LEP188_xsec_stau1stau2bar, triplet<double>))
  // LEP production cross sections and uncertainties: neutralinos
  QUICK_FUNCTION(ColliderBit, LEP188_xsec_chi00_11, NEW_CAPABILITY, LEP188_SLHA1_convention_xsec_chi00_11, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP188_xsec_chi00_12, NEW_CAPABILITY, LEP188_SLHA1_convention_xsec_chi00_12, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP188_xsec_chi00_13, NEW_CAPABILITY, LEP188_SLHA1_convention_xsec_chi00_13, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP188_xsec_chi00_14, NEW_CAPABILITY, LEP188_SLHA1_convention_xsec_chi00_14, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP188_xsec_chi00_22, NEW_CAPABILITY, LEP188_SLHA1_convention_xsec_chi00_22, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP188_xsec_chi00_23, NEW_CAPABILITY, LEP188_SLHA1_convention_xsec_chi00_23, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP188_xsec_chi00_24, NEW_CAPABILITY, LEP188_SLHA1_convention_xsec_chi00_24, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP188_xsec_chi00_33, NEW_CAPABILITY, LEP188_SLHA1_convention_xsec_chi00_33, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP188_xsec_chi00_34, NEW_CAPABILITY, LEP188_SLHA1_convention_xsec_chi00_34, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP188_xsec_chi00_44, NEW_CAPABILITY, LEP188_SLHA1_convention_xsec_chi00_44, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  // LEP production cross sections and uncertainties: charginos
  QUICK_FUNCTION(ColliderBit, LEP188_xsec_chipm_11, NEW_CAPABILITY, LEP188_SLHA1_convention_xsec_chipm_11, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP188_xsec_chipm_12, NEW_CAPABILITY, LEP188_SLHA1_convention_xsec_chipm_12, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP188_xsec_chipm_22, NEW_CAPABILITY, LEP188_SLHA1_convention_xsec_chipm_22, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, LEP188_xsec_chipm_21, NEW_CAPABILITY, LEP188_SLHA1_convention_xsec_chipm_21, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (LEP188_xsec_chipm_12, triplet<double>))

  // LEP Slepton analyses
  // ALEPH
  QUICK_FUNCTION(ColliderBit, ALEPH_Selectron_LLike, NEW_CAPABILITY, ALEPH_Selectron_Conservative_LLike, double, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (LEP208_xsec_selselbar, triplet<double>), (LEP208_xsec_serserbar, triplet<double>), (selectron_l_decay_rates, DecayTable::Entry), (selectron_r_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, ALEPH_Smuon_LLike, NEW_CAPABILITY, ALEPH_Smuon_Conservative_LLike, double, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (LEP208_xsec_smulsmulbar, triplet<double>), (LEP208_xsec_smursmurbar, triplet<double>), (smuon_l_decay_rates, DecayTable::Entry), (smuon_r_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, ALEPH_Stau_LLike, NEW_CAPABILITY, ALEPH_Stau_Conservative_LLike, double, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (LEP208_xsec_stau1stau1bar, triplet<double>), (LEP208_xsec_stau2stau2bar, triplet<double>), (stau_1_decay_rates, DecayTable::Entry), (stau_2_decay_rates, DecayTable::Entry))
  // L3
  QUICK_FUNCTION(ColliderBit, L3_Selectron_LLike, NEW_CAPABILITY, L3_Selectron_Conservative_LLike, double, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (LEP205_xsec_selselbar, triplet<double>), (LEP205_xsec_serserbar, triplet<double>), (selectron_l_decay_rates, DecayTable::Entry), (selectron_r_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, L3_Smuon_LLike, NEW_CAPABILITY, L3_Smuon_Conservative_LLike, double, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (LEP205_xsec_smulsmulbar, triplet<double>), (LEP205_xsec_smursmurbar, triplet<double>), (smuon_l_decay_rates, DecayTable::Entry), (smuon_r_decay_rates, DecayTable::Entry))
  QUICK_FUNCTION(ColliderBit, L3_Stau_LLike, NEW_CAPABILITY, L3_Stau_Conservative_LLike, double, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (LEP205_xsec_stau1stau1bar, triplet<double>), (LEP205_xsec_stau2stau2bar, triplet<double>), (stau_1_decay_rates, DecayTable::Entry), (stau_2_decay_rates, DecayTable::Entry))

  // LEP Gaugino analyses
  // L3 Mass Eigeninos
  QUICK_FUNCTION(ColliderBit, L3_Neutralino_All_Channels_LLike, NEW_CAPABILITY, L3_Neutralino_All_Channels_Conservative_LLike, double, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (LEP188_xsec_chi00_12, triplet<double>), (LEP188_xsec_chi00_13, triplet<double>), (LEP188_xsec_chi00_14, triplet<double>), (decay_rates, DecayTable))
  QUICK_FUNCTION(ColliderBit, L3_Neutralino_Leptonic_LLike, NEW_CAPABILITY, L3_Neutralino_Leptonic_Conservative_LLike, double, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (LEP188_xsec_chi00_12, triplet<double>), (LEP188_xsec_chi00_13, triplet<double>), (LEP188_xsec_chi00_14, triplet<double>), (decay_rates, DecayTable))
  QUICK_FUNCTION(ColliderBit, L3_Chargino_All_Channels_LLike, NEW_CAPABILITY, L3_Chargino_All_Channels_Conservative_LLike, double, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (LEP188_xsec_chipm_11, triplet<double>), (LEP188_xsec_chipm_22, triplet<double>), (decay_rates, DecayTable))
  QUICK_FUNCTION(ColliderBit, L3_Chargino_Leptonic_LLike, NEW_CAPABILITY, L3_Chargino_Leptonic_Conservative_LLike, double, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (LEP188_xsec_chipm_11, triplet<double>), (LEP188_xsec_chipm_22, triplet<double>), (decay_rates, DecayTable))
  // OPAL Mass Eigeninos
  QUICK_FUNCTION(ColliderBit, OPAL_Chargino_Hadronic_LLike, NEW_CAPABILITY, OPAL_Chargino_Hadronic_Conservative_LLike, double, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (LEP208_xsec_chipm_11, triplet<double>), (LEP208_xsec_chipm_22, triplet<double>), (decay_rates, DecayTable))
  QUICK_FUNCTION(ColliderBit, OPAL_Chargino_SemiLeptonic_LLike, NEW_CAPABILITY, OPAL_Chargino_SemiLeptonic_Conservative_LLike, double, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (LEP208_xsec_chipm_11, triplet<double>), (LEP208_xsec_chipm_22, triplet<double>), (decay_rates, DecayTable))
  QUICK_FUNCTION(ColliderBit, OPAL_Chargino_Leptonic_LLike, NEW_CAPABILITY, OPAL_Chargino_Leptonic_Conservative_LLike, double, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (LEP208_xsec_chipm_11, triplet<double>), (LEP208_xsec_chipm_22, triplet<double>), (decay_rates, DecayTable))
  QUICK_FUNCTION(ColliderBit, OPAL_Chargino_All_Channels_LLike, NEW_CAPABILITY, OPAL_Chargino_All_Channels_Conservative_LLike, double, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (LEP208_xsec_chipm_11, triplet<double>), (LEP208_xsec_chipm_22, triplet<double>), (decay_rates, DecayTable))
  QUICK_FUNCTION(ColliderBit, OPAL_Degenerate_Chargino_LLike, NEW_CAPABILITY, OPAL_Degenerate_Chargino_Conservative_LLike, double, (MSSM30atQ, NUHM2), (MSSM_spectrum, Spectrum), (LEP208_xsec_chipm_11, triplet<double>))
  // Due to the nature of the analysis details in the OPAL paper, we can't tell
  // which of the following two limits is appropriate for our use. Thus, we will
  // be conservative and choose only the weaker of the two limits.
  QUICK_FUNCTION(ColliderBit, OPAL_Neutralino_Hadronic_LLike, NEW_CAPABILITY, OPAL_Neutralino_Hadronic_Conservative_LLike, double, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (LEP208_xsec_chi00_12, triplet<double>), (LEP208_xsec_chi00_13, triplet<double>), (LEP208_xsec_chi00_14, triplet<double>), (decay_rates, DecayTable))
  //QUICK_FUNCTION(ColliderBit, OPAL_Neutralino_Hadronic_viaZ_LLike, NEW_CAPABILITY, OPAL_Neutralino_Hadronic_viaZ_Conservative_LLike, double, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (LEP208_xsec_chi00_12, triplet<double>), (LEP208_xsec_chi00_13, triplet<double>), (LEP208_xsec_chi00_14, triplet<double>), (decay_rates, DecayTable))
  // L3 Small DeltaM Gaugino and Higgsinos involve an associated ISR photon, which we don't have a cross-section calculation for.
  //QUICK_FUNCTION(ColliderBit, L3_Charged_Gaugino_Small_DeltaM_Heavy_Sneutrino_LLike, NEW_CAPABILITY, L3_Charged_Gaugino_Small_DeltaM_Heavy_Sneutrino_Conservative_LLike, double, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (LEP188_xsec_chipm_11, triplet<double>), (charginoplus_1_decay_rates, DecayTable::Entry), (W_plus_decay_rates, DecayTable::Entry))
  //QUICK_FUNCTION(ColliderBit, L3_Charged_Gaugino_Small_DeltaM_Any_Sneutrino_LLike, NEW_CAPABILITY, L3_Charged_Gaugino_Small_DeltaM_Any_Sneutrino_Conservative_LLike, double, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (LEP188_xsec_chipm_11, triplet<double>), (charginoplus_1_decay_rates, DecayTable::Entry), (W_plus_decay_rates, DecayTable::Entry))
  //QUICK_FUNCTION(ColliderBit, L3_Charged_Higgsino_Small_DeltaM, NEW_CAPABILITY, L3_Charged_Higgsino_Small_DeltaM, double, (MSSM30atQ, MSSM30atMGUT, NUHM2), (MSSM_spectrum, Spectrum), (LEP188_xsec_chipm_11, triplet<double>), (charginoplus_1_decay_rates, DecayTable::Entry), (W_plus_decay_rates, DecayTable::Entry))

  // L3 gravitino search
  QUICK_FUNCTION(ColliderBit, L3_Gravitino_LLike, NEW_CAPABILITY, L3_Gravitino_LLike, double, (MSSM63atQ_lightgravitino, MSSM63atMGUT_lightgravitino), (MSSM_spectrum, Spectrum), (LEP207_xsec_chi00_11, triplet<double>), (decay_rates, DecayTable))

#undef MODULE

#endif /* defined __ColliderBit_LEP_rollcall_hpp__ */
