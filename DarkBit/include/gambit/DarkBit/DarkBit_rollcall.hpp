//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Rollcall header for module DarkBit
///
///  Compile-time registration of available obser-
///  vables and likelihoods, as well as their
///  dependencies.
///
///  Add to this if you want to add an observable
///  or likelihood to this module.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Christoph Weniger
///          (c.weniger@uva.nl)
///  \date 2013 Jul - 2015 May
///
///  \author Torsten Bringmann
///          (torsten.bringmann@fys.uio.no)
///  \date 2013 Jun
///  \date 2014 Mar
///
///  \author Lars A. Dal
///          (l.a.dal@fys.uio.no)
///  \date 2014 Mar, Sep, Oct
///
///  \author Christopher Savage
///          (chris@savage.name)
///  \date 2014 Oct, Dec
///  \date 2015 June
///
///  \author Antje Putze
///          (antje.putze@lapth.cnrs.fr)
///  \date 2015 Jan
///
///  \author Pat Scott
///          (pscott@imperial.ac.uk)
///  \date 2014 Mar
///  \date 2015 Mar, Aug
///        2018 Sep
///
///  \author Sebastian Wild
///          (sebastian.wild@ph.tum.de)
///  \date 2016 Aug, 2017 Oct
///
///  \author Felix Kahlhoefer
///          (felix.kahlhoefer@desy.de)
///  \date 2016 August
///
///  \author Ankit Beniwal
///          (ankit.beniwal@adelaide.edu.au)
///  \date 2016 Oct
///  \date 2018 Jan, Aug
///
/// \author Aaron Vincent
///         (aaron.vincent@cparc.ca)
/// \date 2017 Sept
///
/// \author Sanjay Bloor
///         (sanjay.bloor12@imperial.ac.uk)
/// \date 2017 Dec
/// \date 2018 Aug
/// \date 2020 Feb
///
///  \author Sebastian Hoof
///          (s.hoof15@imperial.ac.uk)
///  \date 2016 Oct
///  \date 2017 Feb, Sep, Dec
///  \date 2018 Jan, Mar, Apr
///
///  *********************************************

#ifndef __DarkBit_rollcall_hpp__
#define __DarkBit_rollcall_hpp__

#include "gambit/DarkBit/DarkBit_types.hpp"

#define MODULE DarkBit
START_MODULE

  // Backend point initialization --------------------------

  // Function to initialize DarkSUSY to a specific model point.
  // The generic DarkSUSY initialization is done in the backend
  // initialization; this is only necessary for other capabilities
  // that make use of model-specific DarkSUSY routines.
  #define CAPABILITY DarkSUSY_PointInit
  START_CAPABILITY
    // Function returns if point initialization is successful
    // (probably always true)
    #define FUNCTION DarkSUSY_PointInit_MSSM
      START_FUNCTION(bool)
      DEPENDENCY(MSSM_spectrum, Spectrum)
      DEPENDENCY(decay_rates, DecayTable)
      ALLOW_MODELS(MSSM63atQ,CMSSM)
      // For debugging using DarkSUSY native interface to ISASUGRA
      BACKEND_REQ(dsgive_model_isasugra, (), void, (double&,double&,double&,double&,double&))
      BACKEND_REQ(dssusy_isasugra, (), void, (int&,int&))
      // Initialize DarkSUSY with SLHA file
      BACKEND_REQ(dsSLHAread, (), void, (const char*, int&, int))
      BACKEND_REQ(dsprep, (), void, ())
      // Initialize DarkSUSY with SLHA object (convenience function)
      BACKEND_REQ(initFromSLHAeaAndDecayTable, (), int, (const SLHAstruct&, const DecayTable&))
    #undef FUNCTION
  #undef CAPABILITY

  // Function to initialize LocalHalo model in DarkSUSY
  #define CAPABILITY DarkSUSY_PointInit_LocalHalo
  START_CAPABILITY
    #define FUNCTION DarkSUSY_PointInit_LocalHalo_func
      START_FUNCTION(bool)
      DEPENDENCY(RD_fraction, double)
      DEPENDENCY(LocalHalo, LocalMaxwellianHalo)
      BACKEND_REQ(dshmcom,(),DS_HMCOM)
      BACKEND_REQ(dshmisodf,(),DS_HMISODF)
      BACKEND_REQ(dshmframevelcom,(),DS_HMFRAMEVELCOM)
      BACKEND_REQ(dshmnoclue,(),DS_HMNOCLUE)
    #undef FUNCTION
  #undef CAPABILITY

  // Relic density -----------------------------------------

  #define CAPABILITY RD_spectrum
  START_CAPABILITY
    #define FUNCTION RD_spectrum_SUSY
      START_FUNCTION(RD_spectrum_type)
      DEPENDENCY(DarkSUSY_PointInit, bool)
      BACKEND_REQ(mspctm, (), DS_MSPCTM)
      BACKEND_REQ(widths, (), DS_WIDTHS)
      BACKEND_REQ(intdof, (), DS_INTDOF)
      BACKEND_REQ(pacodes, (), DS_PACODES)
      BACKEND_REQ(particle_code, (), int, (const str&))
    #undef FUNCTION
    #define FUNCTION RD_spectrum_from_ProcessCatalog
      START_FUNCTION(RD_spectrum_type)
      DEPENDENCY(TH_ProcessCatalog, TH_ProcessCatalog)
      DEPENDENCY(DarkMatter_ID, std::string)
      ALLOW_MODELS(ScalarSingletDM_Z2, ScalarSingletDM_Z2_running,
                   ScalarSingletDM_Z3, ScalarSingletDM_Z3_running,
                   DiracSingletDM_Z2, MajoranaSingletDM_Z2, VectorSingletDM_Z2)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY RD_spectrum_ordered
  START_CAPABILITY
    #define FUNCTION RD_spectrum_ordered_func
      START_FUNCTION(RD_spectrum_type)
      DEPENDENCY(RD_spectrum, RD_spectrum_type)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY RD_eff_annrate_DSprep
  START_CAPABILITY
    #define FUNCTION RD_annrate_DSprep_func
      START_FUNCTION(int)
      DEPENDENCY(RD_spectrum, RD_spectrum_type)
      BACKEND_REQ(rdmgev, (), DS_RDMGEV)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY RD_eff_annrate
  START_CAPABILITY
    #define FUNCTION RD_eff_annrate_SUSY
      START_FUNCTION(fptr_dd)
      DEPENDENCY(RD_eff_annrate_DSprep, int)
      BACKEND_REQ(dsanwx, (), double, (double&))
    #undef FUNCTION
    #define FUNCTION RD_eff_annrate_from_ProcessCatalog
      START_FUNCTION(fptr_dd)
      DEPENDENCY(TH_ProcessCatalog, TH_ProcessCatalog)
      DEPENDENCY(DarkMatter_ID, std::string)
      ALLOW_MODELS(ScalarSingletDM_Z2, ScalarSingletDM_Z2_running,
                   DiracSingletDM_Z2, MajoranaSingletDM_Z2, VectorSingletDM_Z2)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY RD_oh2
  START_CAPABILITY

    #define FUNCTION RD_oh2_general
      START_FUNCTION(double)
      DEPENDENCY(RD_spectrum_ordered, RD_spectrum_type)
      DEPENDENCY(RD_eff_annrate, fptr_dd)
      #ifdef DARKBIT_RD_DEBUG
        DEPENDENCY(MSSM_spectrum, Spectrum)
      #endif
      BACKEND_REQ(dsrdthlim, (), void, ())
      BACKEND_REQ(dsrdtab, (), void, (double(*)(double&), double&, int&))
      BACKEND_REQ(dsrdeqn, (), void, (double(*)(double&),double&,double&,double&,double&,int&))
      BACKEND_REQ(dsrdwintp, (), double, (double&))
      BACKEND_REQ(particle_code, (), int, (const str&))
      BACKEND_REQ(widths, (), DS_WIDTHS)
      BACKEND_REQ(rdmgev, (), DS_RDMGEV)
      BACKEND_REQ(rdpth, (), DS_RDPTH)
      BACKEND_REQ(rdpars, (), DS_RDPARS)
      BACKEND_REQ(rdswitch, (), DS_RDSWITCH)
      BACKEND_REQ(rdlun, (), DS_RDLUN)
      BACKEND_REQ(rdpadd, (), DS_RDPADD)
      BACKEND_REQ(rddof, (), DS_RDDOF)
      BACKEND_REQ(rderrors, (), DS_RDERRORS)
      BACKEND_REQ(rdtime, (), DS_RDTIME)
    #undef FUNCTION

    // Routine for cross checking relic density results
    #define FUNCTION RD_oh2_DarkSUSY
      START_FUNCTION(double)
      ALLOW_MODELS(MSSM63atQ)
      DEPENDENCY(DarkSUSY_PointInit, bool)
      BACKEND_REQ(dsrdomega, (), double, (int&,int&,double&,int&,int&,int&))
      BACKEND_REQ(rderrors, (), DS_RDERRORS)
      BACKEND_REQ(rdtime, (), DS_RDTIME)
    #undef FUNCTION

    // Routine for cross checking relic density results
    #define FUNCTION RD_oh2_MicrOmegas
      START_FUNCTION(double)
      DEPENDENCY(RD_oh2_Xf, ddpair)
    #undef FUNCTION

    // Routine for axion energy density today
    #define FUNCTION RD_oh2_Axions
      START_FUNCTION(double)
        ALLOW_MODEL(GeneralALP)
        DEPENDENCY(AxionOscillationTemperature, double)
    #undef FUNCTION
  #undef CAPABILITY


  // get oh2 and Xf simultaneously
  #define CAPABILITY RD_oh2_Xf
  START_CAPABILITY
    #define FUNCTION RD_oh2_Xf_MicrOmegas
      START_FUNCTION(ddpair)
      BACKEND_REQ(oh2, (gimmemicro), double, (double*,int,double))
      BACKEND_OPTION((MicrOmegas_MSSM), (gimmemicro))
      BACKEND_OPTION((MicrOmegas_ScalarSingletDM_Z2), (gimmemicro))
      BACKEND_OPTION((MicrOmegas_ScalarSingletDM_Z3), (gimmemicro))
      BACKEND_OPTION((MicrOmegas_VectorSingletDM_Z2), (gimmemicro))
      BACKEND_OPTION((MicrOmegas_MajoranaSingletDM_Z2), (gimmemicro))
      BACKEND_OPTION((MicrOmegas_DiracSingletDM_Z2),(gimmemicro))
      ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT,
                   ScalarSingletDM_Z2, ScalarSingletDM_Z2_running,
                   ScalarSingletDM_Z3, ScalarSingletDM_Z3_running,
                   DiracSingletDM_Z2, MajoranaSingletDM_Z2, VectorSingletDM_Z2)
    #undef FUNCTION
  #undef CAPABILITY


  // Xf = m_WIMP/T_freezeout
  #define CAPABILITY Xf
  START_CAPABILITY
    #define FUNCTION Xf_MicrOmegas
      START_FUNCTION(double)
      DEPENDENCY(RD_oh2_Xf, ddpair)
    #undef FUNCTION
  #undef CAPABILITY

  // Contributions of different annihilation channels to the relic density
  #define CAPABILITY relic_density_contributions
  START_CAPABILITY
    #define FUNCTION print_channel_contributions_MicrOmegas
      START_FUNCTION(double)
      DEPENDENCY(Xf, double)
      BACKEND_REQ(momegas_print_channels, () , double,  (double, double, double, int, FILE*))
    #undef FUNCTION
  #undef CAPABILITY

  // Contributions of semi-annihilation to the relic density
  #define CAPABILITY semi_annihilation_fraction
  START_CAPABILITY
    #define FUNCTION get_semi_ann_MicrOmegas
      START_FUNCTION(double)
      DEPENDENCY(Xf, double)
      BACKEND_REQ(get_oneChannel, (gimmemicro) , double,  (double,double,char*,char*,char*,char*))
      BACKEND_OPTION((MicrOmegas_ScalarSingletDM_Z3),(gimmemicro))
    #undef FUNCTION
  #undef CAPABILITY

  // Fraction of the relic density constituted by the DM candidate under investigation
  #define CAPABILITY RD_fraction
  START_CAPABILITY
    #define FUNCTION RD_fraction_one
      START_FUNCTION(double)
    #undef FUNCTION
    #define FUNCTION RD_fraction_leq_one
      START_FUNCTION(double)
      DEPENDENCY(RD_oh2, double)
    #undef FUNCTION
    #define FUNCTION RD_fraction_rescaled
      START_FUNCTION(double)
      DEPENDENCY(RD_oh2, double)
    #undef FUNCTION
  #undef CAPABILITY


  // Cascade decays --------------------------------------------

  // Function for retrieving list of final states for cascade decays
  #define CAPABILITY cascadeMC_FinalStates
  START_CAPABILITY
    #define FUNCTION cascadeMC_FinalStates
      START_FUNCTION(std::vector<std::string>)
    #undef FUNCTION
  #undef CAPABILITY

  // Function setting up the decay table used in decay chains
  #define CAPABILITY cascadeMC_DecayTable
  START_CAPABILITY
    #define FUNCTION cascadeMC_DecayTable
      START_FUNCTION(DecayChain::DecayTable)
      DEPENDENCY(TH_ProcessCatalog, TH_ProcessCatalog)
      DEPENDENCY(SimYieldTable, SimYieldTable)
    #undef FUNCTION
  #undef CAPABILITY

  // Loop manager for cascade decays
  #define CAPABILITY cascadeMC_LoopManagement
  START_CAPABILITY
    #define FUNCTION cascadeMC_LoopManager
      START_FUNCTION(void, CAN_MANAGE_LOOPS)
      DEPENDENCY(GA_missingFinalStates, std::vector<std::string>)
    #undef FUNCTION
  #undef CAPABILITY

  // Function selecting initial state for decay chain
  #define CAPABILITY cascadeMC_InitialState
  START_CAPABILITY
    #define FUNCTION cascadeMC_InitialState
      START_FUNCTION(std::string)
      DEPENDENCY(GA_missingFinalStates, std::vector<std::string>)
      NEEDS_MANAGER(cascadeMC_LoopManagement)
    #undef FUNCTION
  #undef CAPABILITY

  // Event counter for cascade decays
  #define CAPABILITY cascadeMC_EventCount
  START_CAPABILITY
    #define FUNCTION cascadeMC_EventCount
      START_FUNCTION(stringIntMap)
      DEPENDENCY(cascadeMC_InitialState, std::string)
      NEEDS_MANAGER(cascadeMC_LoopManagement)
    #undef FUNCTION
  #undef CAPABILITY

  // Function for generating decay chains
  #define CAPABILITY cascadeMC_ChainEvent
  START_CAPABILITY
    #define FUNCTION cascadeMC_GenerateChain
      START_FUNCTION(DecayChain::ChainContainer)
      DEPENDENCY(cascadeMC_InitialState, std::string)
      DEPENDENCY(cascadeMC_DecayTable, DecayChain::DecayTable)
      NEEDS_MANAGER(cascadeMC_LoopManagement)
    #undef FUNCTION
  #undef CAPABILITY

  // Function responsible for histogramming and evaluating end conditions for event loop
  #define CAPABILITY cascadeMC_Histograms
  START_CAPABILITY
    #define FUNCTION cascadeMC_Histograms
      START_FUNCTION(simpleHistContainter)
      DEPENDENCY(cascadeMC_InitialState, std::string)
      DEPENDENCY(cascadeMC_ChainEvent, DecayChain::ChainContainer)
      DEPENDENCY(TH_ProcessCatalog, TH_ProcessCatalog)
      DEPENDENCY(SimYieldTable, SimYieldTable)
      DEPENDENCY(cascadeMC_FinalStates,std::vector<std::string>)
      NEEDS_MANAGER(cascadeMC_LoopManagement)
    #undef FUNCTION
  #undef CAPABILITY

  // Function requesting and returning gamma ray spectra from cascade decays.
  #define CAPABILITY cascadeMC_gammaSpectra
  START_CAPABILITY
    #define FUNCTION cascadeMC_gammaSpectra
      START_FUNCTION(stringFunkMap)
      DEPENDENCY(GA_missingFinalStates, std::vector<std::string>)
      DEPENDENCY(cascadeMC_FinalStates,std::vector<std::string>)
      DEPENDENCY(cascadeMC_Histograms, simpleHistContainter)
      DEPENDENCY(cascadeMC_EventCount, stringIntMap)
    #undef FUNCTION
  #undef CAPABILITY

  /*
  // Function for printing test result of cascade decays
  #define CAPABILITY cascadeMC_PrintResult
  START_CAPABILITY
    #define FUNCTION cascadeMC_PrintResult
      START_FUNCTION(bool)
      DEPENDENCY(cascadeMC_Histograms, simpleHistContainter)
      DEPENDENCY(cascadeMC_EventCount, stringIntMap)
    #undef FUNCTION
  #undef CAPABILITY
  */

  /*
  // Process catalog for testing purposes
  #define CAPABILITY cascadeMC_test_TH_ProcessCatalog
  START_CAPABILITY
    #define FUNCTION cascadeMC_test_TH_ProcessCatalog
      START_FUNCTION(TH_ProcessCatalog)
    #undef FUNCTION
  #undef CAPABILITY

  // Unit test for decay chains
  #define CAPABILITY cascadeMC_UnitTest
  START_CAPABILITY
    #define FUNCTION cascadeMC_UnitTest
      START_FUNCTION(bool)
      DEPENDENCY(cascadeMC_test_TH_ProcessCatalog, TH_ProcessCatalog)
      DEPENDENCY(SimYieldTable, SimYieldTable)
    #undef FUNCTION
  #undef CAPABILITY
  */

  // Gamma rays --------------------------------------------
  //
  #define CAPABILITY GA_missingFinalStates
  START_CAPABILITY
    #define FUNCTION GA_missingFinalStates
      START_FUNCTION(std::vector<std::string>)
      DEPENDENCY(TH_ProcessCatalog, TH_ProcessCatalog)
      DEPENDENCY(SimYieldTable, SimYieldTable)
      DEPENDENCY(DarkMatter_ID, std::string)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY GA_AnnYield
  START_CAPABILITY
    #define FUNCTION GA_AnnYield_General
      START_FUNCTION(daFunk::Funk)
      DEPENDENCY(TH_ProcessCatalog, TH_ProcessCatalog)
      DEPENDENCY(SimYieldTable, SimYieldTable)
      DEPENDENCY(cascadeMC_gammaSpectra, stringFunkMap)
      DEPENDENCY(DarkMatter_ID, std::string)
    #undef FUNCTION
  /*
    #define FUNCTION GA_AnnYield_DarkSUSY
      START_FUNCTION(daFunk::Funk)
      DEPENDENCY(TH_ProcessCatalog, TH_ProcessCatalog)
      DEPENDENCY(DarkMatter_ID, std::string)
      BACKEND_REQ(dshayield, (), double, (double&,double&,int&,int&,int&))
    #undef FUNCTION
  */
  #undef CAPABILITY

  #define CAPABILITY TH_ProcessCatalog
  START_CAPABILITY
    #define FUNCTION TH_ProcessCatalog_MSSM
      START_FUNCTION(TH_ProcessCatalog)
      //ALLOW_MODELS(MSSM63atQ)
      DEPENDENCY(DarkSUSY_PointInit, bool)
      DEPENDENCY(MSSM_spectrum, Spectrum)
      DEPENDENCY(DarkMatter_ID, std::string)
      DEPENDENCY(decay_rates,DecayTable)
      //BACKEND_REQ(mspctm, (), DS_MSPCTM)
      BACKEND_REQ(dssigmav, (), double, (int&))
      BACKEND_REQ(dsIBffdxdy, (), double, (int&, double&, double&))
      BACKEND_REQ(dsIBhhdxdy, (), double, (int&, double&, double&))
      BACKEND_REQ(dsIBwhdxdy, (), double, (int&, double&, double&))
      BACKEND_REQ(dsIBwwdxdy, (), double, (int&, double&, double&))
      BACKEND_REQ(IBintvars, (), DS_IBINTVARS)
    #undef FUNCTION
    #define FUNCTION TH_ProcessCatalog_ScalarSingletDM_Z2
      START_FUNCTION(TH_ProcessCatalog)
      DEPENDENCY(decay_rates, DecayTable)
      DEPENDENCY(ScalarSingletDM_Z2_spectrum, Spectrum)
      ALLOW_MODELS(ScalarSingletDM_Z2,ScalarSingletDM_Z2_running)
    #undef FUNCTION
    #define FUNCTION TH_ProcessCatalog_ScalarSingletDM_Z3
      START_FUNCTION(TH_ProcessCatalog)
      DEPENDENCY(decay_rates, DecayTable)
      DEPENDENCY(ScalarSingletDM_Z3_spectrum, Spectrum)
      BACKEND_REQ(calcSpectrum, (gimmemicro) , double,  (int, double*, double*, double*, double*, double*, double*, int*))
      BACKEND_REQ(vSigmaCh, (gimmemicro), MicrOmegas::aChannel*)
      FORCE_SAME_BACKEND(gimmemicro)
      ALLOW_MODELS(ScalarSingletDM_Z3,ScalarSingletDM_Z3_running)
    #undef FUNCTION
    #define FUNCTION TH_ProcessCatalog_VectorSingletDM_Z2
      START_FUNCTION(TH_ProcessCatalog)
      DEPENDENCY(VectorSingletDM_Z2_spectrum, Spectrum)
      DEPENDENCY(decay_rates, DecayTable)
      ALLOW_MODELS(VectorSingletDM_Z2)
    #undef FUNCTION
    #define FUNCTION TH_ProcessCatalog_MajoranaSingletDM_Z2
      START_FUNCTION(TH_ProcessCatalog)
      DEPENDENCY(MajoranaSingletDM_Z2_spectrum, Spectrum)
      DEPENDENCY(decay_rates, DecayTable)
      ALLOW_MODELS(MajoranaSingletDM_Z2)
    #undef FUNCTION
    #define FUNCTION TH_ProcessCatalog_DiracSingletDM_Z2
      START_FUNCTION(TH_ProcessCatalog)
      DEPENDENCY(decay_rates, DecayTable)
      DEPENDENCY(DiracSingletDM_Z2_spectrum, Spectrum)
      ALLOW_MODELS(DiracSingletDM_Z2)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY set_gamLike_GC_halo
  START_CAPABILITY
    #define FUNCTION set_gamLike_GC_halo
      START_FUNCTION(bool)
      DEPENDENCY(GalacticHalo, GalacticHaloProperties)
      BACKEND_REQ(set_halo_profile, (gamLike), void, (int, const std::vector<double> &, const std::vector<double> &, double))
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lnL_FermiLATdwarfs
  START_CAPABILITY
    #define FUNCTION lnL_FermiLATdwarfs_gamLike
      START_FUNCTION(double)
      DEPENDENCY(GA_AnnYield, daFunk::Funk)
      DEPENDENCY(RD_fraction, double)
      BACKEND_REQ(lnL, (gamLike), double, (int, const std::vector<double> &, const std::vector<double> &))
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lnL_FermiGC
  START_CAPABILITY
    #define FUNCTION lnL_FermiGC_gamLike
      START_FUNCTION(double)
      DEPENDENCY(GA_AnnYield, daFunk::Funk)
      DEPENDENCY(RD_fraction, double)
      DEPENDENCY(set_gamLike_GC_halo, bool)
      BACKEND_REQ(lnL, (gamLike), double, (int, const std::vector<double> &, const std::vector<double> &))
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lnL_CTAGC
  START_CAPABILITY
    #define FUNCTION lnL_CTAGC_gamLike
      START_FUNCTION(double)
      DEPENDENCY(GA_AnnYield, daFunk::Funk)
      DEPENDENCY(RD_fraction, double)
      //DEPENDENCY(set_gamLike_GC_halo, bool)
      BACKEND_REQ(lnL, (gamLike), double, (int, const std::vector<double> &, const std::vector<double> &))
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lnL_HESSGC
  START_CAPABILITY
    #define FUNCTION lnL_HESSGC_gamLike
      START_FUNCTION(double)
      DEPENDENCY(GA_AnnYield, daFunk::Funk)
      DEPENDENCY(RD_fraction, double)
      DEPENDENCY(set_gamLike_GC_halo, bool)
      BACKEND_REQ(lnL, (gamLike), double, (int, const std::vector<double> &, const std::vector<double> &))
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY dump_GammaSpectrum
  START_CAPABILITY
    #define FUNCTION dump_GammaSpectrum
      START_FUNCTION(double)
      DEPENDENCY(GA_AnnYield, daFunk::Funk)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lnL_oh2
  START_CAPABILITY
    #define FUNCTION lnL_oh2_Simple
      START_FUNCTION(double)
      DEPENDENCY(RD_oh2, double)
    #undef FUNCTION
    #define FUNCTION lnL_oh2_upperlimit
      START_FUNCTION(double)
      DEPENDENCY(RD_oh2, double)
    #undef FUNCTION
  #undef CAPABILITY

  // Local DM density likelihood

  #define CAPABILITY lnL_rho0
  START_CAPABILITY
    #define FUNCTION lnL_rho0_lognormal
      START_FUNCTION(double)
      DEPENDENCY(LocalHalo, LocalMaxwellianHalo)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lnL_vrot
  START_CAPABILITY
    #define FUNCTION lnL_vrot_gaussian
      START_FUNCTION(double)
      DEPENDENCY(LocalHalo, LocalMaxwellianHalo)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lnL_v0
  START_CAPABILITY
    #define FUNCTION lnL_v0_gaussian
      START_FUNCTION(double)
      DEPENDENCY(LocalHalo, LocalMaxwellianHalo)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lnL_vesc
  START_CAPABILITY
    #define FUNCTION lnL_vesc_gaussian
      START_FUNCTION(double)
      DEPENDENCY(LocalHalo, LocalMaxwellianHalo)
    #undef FUNCTION
  #undef CAPABILITY

  // Simple WIMP property extractors =======================================

  // Retrieve the DM mass in GeV for generic models
  QUICK_FUNCTION(DarkBit, mwimp, NEW_CAPABILITY, mwimp_generic, double, (),
      (TH_ProcessCatalog, TH_ProcessCatalog), (DarkMatter_ID, std::string))

  // Retrieve the total thermally-averaged annihilation cross-section for indirect detection (cm^3 / s)
  QUICK_FUNCTION(DarkBit, sigmav, NEW_CAPABILITY, sigmav_late_universe, double, (),
      (TH_ProcessCatalog, TH_ProcessCatalog), (DarkMatter_ID, std::string))


  // DIRECT DETECTION ==================================================

  // Determine the DM-nucleon couplings
  #define CAPABILITY DD_couplings
  START_CAPABILITY

    #define FUNCTION DD_couplings_DarkSUSY
      START_FUNCTION(DM_nucleon_couplings)
      DEPENDENCY(DarkSUSY_PointInit, bool)
      BACKEND_REQ(dsddgpgn, (), void, (double&, double&, double&, double&))
      BACKEND_REQ(mspctm, (), DS_MSPCTM)
      BACKEND_REQ(ddcom, (DarkSUSY), DS_DDCOM)
      ALLOW_JOINT_MODEL(nuclear_params_fnq,MSSM63atQ)
    #undef FUNCTION

    #define FUNCTION DD_couplings_MicrOmegas
      START_FUNCTION(DM_nucleon_couplings)
      BACKEND_REQ(nucleonAmplitudes, (gimmemicro), int, (double(*)(double,double,double,double), double*, double*, double*, double*))
      BACKEND_REQ(FeScLoop, (gimmemicro), double, (double, double, double, double))
      BACKEND_REQ(MOcommon, (gimmemicro), MicrOmegas::MOcommonSTR)
      ALLOW_MODEL_DEPENDENCE(nuclear_params_fnq, MSSM63atQ,
                             ScalarSingletDM_Z2, ScalarSingletDM_Z2_running,
                             ScalarSingletDM_Z3, ScalarSingletDM_Z3_running,
                             VectorSingletDM_Z2)
      MODEL_GROUP(group1, (nuclear_params_fnq))
      MODEL_GROUP(group2, (MSSM63atQ,
                           ScalarSingletDM_Z2, ScalarSingletDM_Z2_running,
                           ScalarSingletDM_Z3, ScalarSingletDM_Z3_running,
                           VectorSingletDM_Z2))
      ALLOW_MODEL_COMBINATION(group1, group2)
      BACKEND_OPTION((MicrOmegas_MSSM),(gimmemicro))
      BACKEND_OPTION((MicrOmegas_ScalarSingletDM_Z2),(gimmemicro))
      BACKEND_OPTION((MicrOmegas_ScalarSingletDM_Z3),(gimmemicro))
      BACKEND_OPTION((MicrOmegas_VectorSingletDM_Z2),(gimmemicro))
      FORCE_SAME_BACKEND(gimmemicro)
    #undef FUNCTION

    #define FUNCTION DD_couplings_ScalarSingletDM_Z2
      START_FUNCTION(DM_nucleon_couplings)
      DEPENDENCY(ScalarSingletDM_Z2_spectrum, Spectrum)
      ALLOW_MODEL_DEPENDENCE(nuclear_params_fnq, ScalarSingletDM_Z2, ScalarSingletDM_Z2_running)
      MODEL_GROUP(group1, (nuclear_params_fnq))
      MODEL_GROUP(group2, (ScalarSingletDM_Z2, ScalarSingletDM_Z2_running))
      ALLOW_MODEL_COMBINATION(group1, group2)
     #undef FUNCTION

    #define FUNCTION DD_couplings_ScalarSingletDM_Z3
      START_FUNCTION(DM_nucleon_couplings)
      DEPENDENCY(ScalarSingletDM_Z3_spectrum, Spectrum)
      ALLOW_MODEL_DEPENDENCE(nuclear_params_fnq, ScalarSingletDM_Z3, ScalarSingletDM_Z3_running)
      MODEL_GROUP(group1, (nuclear_params_fnq))
      MODEL_GROUP(group2, (ScalarSingletDM_Z3, ScalarSingletDM_Z3_running))
      ALLOW_MODEL_COMBINATION(group1, group2)
     #undef FUNCTION

     #define FUNCTION DD_couplings_VectorSingletDM_Z2
      START_FUNCTION(DM_nucleon_couplings)
      DEPENDENCY(VectorSingletDM_Z2_spectrum, Spectrum)
      ALLOW_JOINT_MODEL(nuclear_params_fnq, VectorSingletDM_Z2)
     #undef FUNCTION

  #undef CAPABILITY

  #define CAPABILITY DD_couplings_fermionic_HP
  START_CAPABILITY

     #define FUNCTION DD_couplings_MajoranaSingletDM_Z2
      START_FUNCTION(DM_nucleon_couplings_fermionic_HP)
      DEPENDENCY(MajoranaSingletDM_Z2_spectrum, Spectrum)
      ALLOW_JOINT_MODEL(nuclear_params_fnq, MajoranaSingletDM_Z2)
     #undef FUNCTION

     #define FUNCTION DD_couplings_DiracSingletDM_Z2
      START_FUNCTION(DM_nucleon_couplings_fermionic_HP)
      DEPENDENCY(DiracSingletDM_Z2_spectrum, Spectrum)
      ALLOW_JOINT_MODEL(nuclear_params_fnq, DiracSingletDM_Z2)
     #undef FUNCTION

  #undef CAPABILITY

  // Simple calculators of the spin-(in)dependent WIMP-proton and WIMP-neutron cross-sections
  QUICK_FUNCTION(DarkBit, sigma_SI_p, NEW_CAPABILITY, sigma_SI_p_simple, double, (), (DD_couplings, DM_nucleon_couplings), (mwimp, double))
  QUICK_FUNCTION(DarkBit, sigma_SI_n, NEW_CAPABILITY, sigma_SI_n_simple, double, (), (DD_couplings, DM_nucleon_couplings), (mwimp, double))
  QUICK_FUNCTION(DarkBit, sigma_SD_p, NEW_CAPABILITY, sigma_SD_p_simple, double, (), (DD_couplings, DM_nucleon_couplings), (mwimp, double))
  QUICK_FUNCTION(DarkBit, sigma_SD_n, NEW_CAPABILITY, sigma_SD_n_simple, double, (), (DD_couplings, DM_nucleon_couplings), (mwimp, double))

  // Generalized v^2n, q^2n DM-nucleon cross sections
  #define CAPABILITY sigma_SI_p
      #define FUNCTION sigma_SI_vnqn
      START_FUNCTION(map_intpair_dbl)
      DEPENDENCY(mwimp,double)
      DEPENDENCY(DD_couplings_fermionic_HP,DM_nucleon_couplings_fermionic_HP)
      ALLOW_MODELS(DiracSingletDM_Z2, MajoranaSingletDM_Z2)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY sigma_SD_p
  //Spin-dependent general v^2n q^2n cross section
      #define FUNCTION sigma_SD_vnqn
      START_FUNCTION(map_intpair_dbl)
      DEPENDENCY(mwimp,double)
      DEPENDENCY(DD_couplings_fermionic_HP,DM_nucleon_couplings_fermionic_HP)
      ALLOW_MODELS(DiracSingletDM_Z2, MajoranaSingletDM_Z2)
    #undef FUNCTION
  #undef CAPABILITY

  // Likelihoods for nuclear parameters:
  #define CAPABILITY lnL_SI_nuclear_parameters
  START_CAPABILITY
    #define FUNCTION lnL_sigmas_sigmal
      START_FUNCTION(double)
      ALLOW_MODEL(nuclear_params_sigmas_sigmal)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lnL_SD_nuclear_parameters
  START_CAPABILITY
    #define FUNCTION lnL_deltaq
      START_FUNCTION(double)
      ALLOW_MODELS(nuclear_params_fnq)
    #undef FUNCTION
  #undef CAPABILITY

  // DD rate and likelihood calculations. Don't try this one at home kids.
  #define DD_DECLARE_RESULT_FUNCTION(EXPERIMENT,TYPE,NAME)                          \
  LONG_START_CAPABILITY(MODULE, CAT_3(EXPERIMENT,_,NAME))                           \
  LONG_DECLARE_FUNCTION(MODULE, CAT_3(EXPERIMENT,_,NAME),                           \
   CAT_3(EXPERIMENT,_Get,NAME), TYPE, 0)                                            \
  LONG_DEPENDENCY(MODULE, CAT_3(EXPERIMENT,_Get,NAME),                              \
   CAT(EXPERIMENT,_Calculate), bool)                                                \
  LONG_BACKEND_REQ(MODULE, CAT_3(EXPERIMENT,_,NAME),                                \
   CAT_3(EXPERIMENT,_Get,NAME), DD_Experiment, (needs_DDCalc), int, (const str&))   \
  LONG_BACKEND_REQ(MODULE, CAT_3(EXPERIMENT,_,NAME),                                \
   CAT_3(EXPERIMENT,_Get,NAME), CAT(DD_,NAME), (needs_DDCalc), TYPE, (const int&))

  #define DD_DECLARE_BIN_FUNCTION(EXPERIMENT,TYPE,NAME)                             \
  LONG_START_CAPABILITY(MODULE, CAT_3(EXPERIMENT,_,NAME))                           \
  LONG_DECLARE_FUNCTION(MODULE, CAT_3(EXPERIMENT,_,NAME),                           \
   CAT_3(EXPERIMENT,_Get,NAME), std::vector<double>, 0)                             \
  LONG_DEPENDENCY(MODULE, CAT_3(EXPERIMENT,_Get,NAME),                              \
   CAT(EXPERIMENT,_Calculate), bool)                                                \
  LONG_BACKEND_REQ(MODULE, CAT_3(EXPERIMENT,_,NAME),                                \
   CAT_3(EXPERIMENT,_Get,NAME), DD_Experiment, (needs_DDCalc), int, (const str&))   \
  LONG_BACKEND_REQ(MODULE, CAT_3(EXPERIMENT,_,NAME),                                \
   CAT_3(EXPERIMENT,_Get,NAME), DD_Bins, (needs_DDCalc), int, (const int&))         \
  LONG_BACKEND_REQ(MODULE, CAT_3(EXPERIMENT,_,NAME),                                \
   CAT_3(EXPERIMENT,_Get,NAME), CAT(DD_,NAME), (needs_DDCalc), TYPE, (const int&,   \
   const int&))

  #define DD_DECLARE_EXPERIMENT(EXPERIMENT)                                         \
  LONG_START_CAPABILITY(MODULE, CAT(EXPERIMENT,_Calculate))                         \
  LONG_DECLARE_FUNCTION(MODULE, CAT(EXPERIMENT,_Calculate),                         \
   CAT(EXPERIMENT,_Calc), bool, 0)                                                  \
  LONG_BACKEND_REQ(MODULE, CAT(EXPERIMENT,_Calculate),                              \
   CAT(EXPERIMENT,_Calc), DD_Experiment, (needs_DDCalc), int, (const str&))         \
  LONG_BACKEND_REQ(MODULE, CAT(EXPERIMENT,_Calculate),                              \
   CAT(EXPERIMENT,_Calc), DD_CalcRates, (needs_DDCalc), void, (const int&))         \
  DD_DECLARE_RESULT_FUNCTION(EXPERIMENT,int,Events)                                 \
  DD_DECLARE_RESULT_FUNCTION(EXPERIMENT,double,Background)                          \
  DD_DECLARE_RESULT_FUNCTION(EXPERIMENT,double,Signal)                              \
  DD_DECLARE_RESULT_FUNCTION(EXPERIMENT,double,SignalSI)                            \
  DD_DECLARE_RESULT_FUNCTION(EXPERIMENT,double,SignalSD)                            \
  DD_DECLARE_RESULT_FUNCTION(EXPERIMENT,int,Bins)                                   \
  DD_DECLARE_RESULT_FUNCTION(EXPERIMENT,double,LogLikelihood)                       \
  DD_DECLARE_BIN_FUNCTION(EXPERIMENT,int,BinEvents)                                 \
  DD_DECLARE_BIN_FUNCTION(EXPERIMENT,double,BinBackground)                          \
  DD_DECLARE_BIN_FUNCTION(EXPERIMENT,double,BinSignal)                              \

  #define SET_BACKEND_OPTION(EXPERIMENT, VERSIONS)                                  \
  LONG_BACKEND_OPTION(MODULE, CAT(EXPERIMENT,_Calculate), CAT(EXPERIMENT,_Calc),    \
   VERSIONS, (needs_DDCalc))                                                        \
  LONG_BACKEND_OPTION(MODULE, CAT(EXPERIMENT,_Events), CAT(EXPERIMENT,_GetEvents),  \
   VERSIONS, (needs_DDCalc))                                                        \
  LONG_BACKEND_OPTION(MODULE, CAT(EXPERIMENT,_Background),                          \
   CAT(EXPERIMENT,_GetBackground), VERSIONS, (needs_DDCalc))                        \
  LONG_BACKEND_OPTION(MODULE, CAT(EXPERIMENT,_Signal), CAT(EXPERIMENT,_GetSignal),  \
   VERSIONS, (needs_DDCalc))                                                        \
  LONG_BACKEND_OPTION(MODULE, CAT(EXPERIMENT,_SignalSI),                            \
   CAT(EXPERIMENT,_GetSignalSI), VERSIONS, (needs_DDCalc))                          \
  LONG_BACKEND_OPTION(MODULE, CAT(EXPERIMENT,_SignalSD),                            \
   CAT(EXPERIMENT,_GetSignalSD), VERSIONS, (needs_DDCalc))                          \
  LONG_BACKEND_OPTION(MODULE, CAT(EXPERIMENT,_Bins), CAT(EXPERIMENT,_GetBins),      \
   VERSIONS, (needs_DDCalc))                                                        \
  LONG_BACKEND_OPTION(MODULE, CAT(EXPERIMENT,_LogLikelihood),                       \
   CAT(EXPERIMENT,_GetLogLikelihood), VERSIONS, (needs_DDCalc))                     \
  LONG_BACKEND_OPTION(MODULE, CAT(EXPERIMENT,_BinEvents),                           \
   CAT(EXPERIMENT,_GetBinEvents), VERSIONS, (needs_DDCalc))                         \
  LONG_BACKEND_OPTION(MODULE, CAT(EXPERIMENT,_BinBackground),                       \
   CAT(EXPERIMENT,_GetBinBackground), VERSIONS, (needs_DDCalc))                     \
  LONG_BACKEND_OPTION(MODULE, CAT(EXPERIMENT,_BinSignal),                           \
   CAT(EXPERIMENT,_GetBinSignal), VERSIONS, (needs_DDCalc))                         \



  // Declare different DD experiments that exist in DDCalc.
  DD_DECLARE_EXPERIMENT(XENON100_2012)        // Aprile et al., PRL 109, 181301 (2013) [arxiv:1207.5988]
  DD_DECLARE_EXPERIMENT(XENON1T_2017)         // Aprile et al., PRL 119, 181301 (2017) [arxiv:1705.06655]
  DD_DECLARE_EXPERIMENT(XENON1T_2018)         // Aprile et al., May 28 talk at Gran Sasso.
  DD_DECLARE_EXPERIMENT(DARWIN)               // M. Schumann et al., [arXiv:1506.08309]
  DD_DECLARE_EXPERIMENT(LUX_2013)             // Akerib et al., PRL 112, 091303 (2014) [arxiv:1310.8214]
  DD_DECLARE_EXPERIMENT(LUX_2015)             // D.S. Akerib et al., PRL 116, 161301 (2016) [arXiv:1512.03506]
  DD_DECLARE_EXPERIMENT(LUX_2016)             // D.S. Akerib et al., PRL 118, 021303 (2017) [arxiv:1608.07648]
  DD_DECLARE_EXPERIMENT(LZ)                   // LZ TDR, [arXiv:1509.02910]
  DD_DECLARE_EXPERIMENT(PandaX_2016)          // A. Tan et al., PRL 117, 121303 (2016) [arxiv:1607.07400]
  DD_DECLARE_EXPERIMENT(PandaX_2017)          // X. Cui et al., PRL 119, 181302 (2017) [arxiv:1708.06917]
  DD_DECLARE_EXPERIMENT(DarkSide_50)          // P. Agnes et al., [arXiv:1802.07198]
  DD_DECLARE_EXPERIMENT(DarkSide_50_S2)       // P. Agnes et al., [arXiv:1802.06994]
  DD_DECLARE_EXPERIMENT(CRESST_II)            // G. Angloher et al., [arXiv:1509.01515]
  DD_DECLARE_EXPERIMENT(CRESST_III)           // A. H. Abdelhameed et al., [arXiv:1904.00498]
  DD_DECLARE_EXPERIMENT(SuperCDMS_2014)       // Agnese et al., PRL 112, 241302 (2014) [arxiv:1402.7137]
  DD_DECLARE_EXPERIMENT(CDMSlite)             // Agnese et al., PRL 116, 071301 (2015) [arxiv:1509.02448]
  DD_DECLARE_EXPERIMENT(SIMPLE_2014)          // Felizardo et al., PRD 89, 072013 (2014) [arxiv:1404.4309]
  DD_DECLARE_EXPERIMENT(PICO_2L)              // C. Amole et al., PRD 93, 061101 (2016) [arXiv:1601.03729]
  DD_DECLARE_EXPERIMENT(PICO_60_F)            // C. Amole et al., PRD 93, 052014 (2016) [arXiv:1510.07754]
  DD_DECLARE_EXPERIMENT(PICO_60_I)            // C. Amole et al., PRD 93, 052014 (2016) [arXiv:1510.07754]
  DD_DECLARE_EXPERIMENT(PICO_60)              // C. Amole et al., PRD 93, 052014 (2016) [arXiv:1510.07754]
  DD_DECLARE_EXPERIMENT(PICO_60_2017)         // C. Amole et al., arXiv:1702.07666
  DD_DECLARE_EXPERIMENT(PICO_60_2019)         // C. Amole et al., arXiv:1902.04031
  DD_DECLARE_EXPERIMENT(PICO_500)             // S. Fallows, talk at TAUP 2017

  // Specify which versions of DDCalc support which experiments.
  // If an experiment does not have any entry here, any version (of any backend) is allowed.

  // Introduced in DDCalc 1.0.0 but later deleted
  SET_BACKEND_OPTION(PICO_60_F, (DDCalc, 1.0.0, 1.1.0, 1.2.0))
  SET_BACKEND_OPTION(PICO_60_I, (DDCalc, 1.0.0, 1.1.0, 1.2.0))
  // Introduced in DDCalc 1.1.0
  SET_BACKEND_OPTION(PICO_60_2017, (DDCalc, 1.1.0, 1.2.0, 2.0.0, 2.1.0, 2.2.0))
  SET_BACKEND_OPTION(XENON1T_2017, (DDCalc, 1.1.0, 1.2.0, 2.0.0, 2.1.0, 2.2.0))
  // Introduced in DDCalc 1.2.0
  SET_BACKEND_OPTION(PandaX_2017, (DDCalc, 1.2.0, 2.0.0, 2.1.0, 2.2.0))
  // Introduced in DDCalc 2.0.0
  SET_BACKEND_OPTION(XENON1T_2018, (DDCalc, 2.0.0, 2.1.0, 2.2.0))
  SET_BACKEND_OPTION(DARWIN, (DDCalc, 2.0.0, 2.1.0, 2.2.0))
  SET_BACKEND_OPTION(LZ, (DDCalc, 2.0.0, 2.1.0, 2.2.0))
  SET_BACKEND_OPTION(DarkSide_50, (DDCalc, 2.0.0, 2.1.0, 2.2.0))
  SET_BACKEND_OPTION(CRESST_II, (DDCalc, 2.0.0, 2.1.0, 2.2.0))
  SET_BACKEND_OPTION(CDMSlite, (DDCalc, 2.0.0, 2.1.0, 2.2.0))
  SET_BACKEND_OPTION(PICO_60, (DDCalc, 2.0.0, 2.1.0, 2.2.0))
  SET_BACKEND_OPTION(PICO_500, (DDCalc, 2.0.0, 2.1.0, 2.2.0))
  // Introduced in DDCalc 2.2.0
  SET_BACKEND_OPTION(CRESST_III, (DDCalc, 2.2.0))
  SET_BACKEND_OPTION(DarkSide_50_S2, (DDCalc, 2.2.0))
  SET_BACKEND_OPTION(PICO_60_2019, (DDCalc, 2.2.0))


  // INDIRECT DETECTION: NEUTRINOS =====================================

  // Solar capture ------------------------

  /// Capture rate of regular dark matter in the Sun (no v-dependent or q-dependent cross-sections) (s^-1).
  #define CAPABILITY capture_rate_Sun
  START_CAPABILITY
    #define FUNCTION capture_rate_Sun_const_xsec
      START_FUNCTION(double)
      BACKEND_REQ(cap_Sun_v0q0_isoscalar, (DarkSUSY), double, (const double&, const double&, const double&))
      DEPENDENCY(mwimp, double)
      DEPENDENCY(sigma_SI_p, double)
      DEPENDENCY(sigma_SD_p, double)
        #define CONDITIONAL_DEPENDENCY DarkSUSY_PointInit_LocalHalo
        START_CONDITIONAL_DEPENDENCY(bool)
        ACTIVATE_FOR_BACKEND(cap_Sun_v0q0_isoscalar, DarkSUSY)
        #undef CONDITIONAL_DEPENDENCY
    #undef FUNCTION

    ///Alternative function for the above: Capture rate of dark matter with a constant cross section (s^-1), using backend Captn' General
    #define FUNCTION capture_rate_Sun_const_xsec_capgen
    START_FUNCTION(double)
    BACKEND_REQ(cap_Sun_v0q0_isoscalar,(CaptnGeneral),void,(const double&,const double&,const double&,double&,double&))
    BACKEND_REQ(cap_sun_saturation,(CaptnGeneral),void,(const double&,double&))
    DEPENDENCY(mwimp,double)
    DEPENDENCY(sigma_SI_p, double)
    DEPENDENCY(sigma_SD_p, double)
    #undef FUNCTION

    ///Capture rate of dark matter with q^n or v^n cross section (s^-1), using backend Captn' General
    #define FUNCTION capture_rate_Sun_vnqn
    START_FUNCTION(double)
    BACKEND_REQ(cap_Sun_vnqn_isoscalar,(CaptnGeneral),void,(const double&,const double&,const int&,const int&,const int&,double&))
    BACKEND_REQ(cap_sun_saturation,(CaptnGeneral),void,(const double&,double&))
    DEPENDENCY(mwimp,double)
    DEPENDENCY(sigma_SD_p, map_intpair_dbl)
    DEPENDENCY(sigma_SI_p, map_intpair_dbl)
    #undef FUNCTION
  #undef CAPABILITY

  /// Equilibration time for capture and annihilation of dark matter in the Sun (s)
  #define CAPABILITY equilibration_time_Sun
  START_CAPABILITY
    #define FUNCTION equilibration_time_Sun
      START_FUNCTION(double)
      DEPENDENCY(TH_ProcessCatalog, TH_ProcessCatalog)
      DEPENDENCY(mwimp, double)
      DEPENDENCY(DarkMatter_ID, std::string)
      DEPENDENCY(capture_rate_Sun, double)
    #undef FUNCTION
  #undef CAPABILITY

  /// Annihilation rate of dark matter in the Sun (s^-1)
  #define CAPABILITY annihilation_rate_Sun
  START_CAPABILITY
    #define FUNCTION annihilation_rate_Sun
      START_FUNCTION(double)
      DEPENDENCY(equilibration_time_Sun, double)
      DEPENDENCY(capture_rate_Sun, double)
    #undef FUNCTION
  #undef CAPABILITY

  /// Neutrino yield function pointer and setup
  #define CAPABILITY nuyield_ptr
  START_CAPABILITY
    #define FUNCTION nuyield_from_DS
    START_FUNCTION(nuyield_info)
    DEPENDENCY(TH_ProcessCatalog, TH_ProcessCatalog)
    DEPENDENCY(mwimp, double)
    DEPENDENCY(sigmav, double)
    DEPENDENCY(DarkMatter_ID, std::string)
    BACKEND_REQ(nuyield_setup, (needs_DS), void, (const double(&)[29],
     const double(&)[29][3], const double(&)[15], const double(&)[3], const double&,
     const double&))
    BACKEND_REQ(nuyield, (needs_DS), double, (const double&, const int&, void*&))
    BACKEND_REQ(get_DS_neutral_h_decay_channels, (needs_DS), std::vector< std::vector<str> >, ())
    BACKEND_REQ(get_DS_charged_h_decay_channels, (needs_DS), std::vector< std::vector<str> >, ())
    BACKEND_OPTION((DarkSUSY, 5.1.1, 5.1.2, 5.1.3), (needs_DS))
    #undef FUNCTION
  #undef CAPABILITY


  // Neutrino telescope likelihoods ------------------------

  #define CAPABILITY IC22_data
  START_CAPABILITY
    #define FUNCTION IC22_full
      START_FUNCTION(nudata)
      DEPENDENCY(mwimp, double)
      DEPENDENCY(annihilation_rate_Sun, double)
      DEPENDENCY(nuyield_ptr, nuyield_info)
      BACKEND_REQ(nubounds, (), void, (const char&, const double&, const double&,
                                       nuyield_function_pointer, double&, double&, int&,
                                       double&, double&, const int&, const double&,
                                       const int&, const bool&, const double&,
                                       const double&, void*&, const bool&))
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY IC22_signal
  START_CAPABILITY
    #define FUNCTION IC22_signal
    START_FUNCTION(double)
    DEPENDENCY(IC22_data, nudata)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY IC22_bg
  START_CAPABILITY
    #define FUNCTION IC22_bg
    START_FUNCTION(double)
    DEPENDENCY(IC22_data, nudata)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY IC22_loglike
  START_CAPABILITY
    #define FUNCTION IC22_loglike
    START_FUNCTION(double)
    DEPENDENCY(IC22_data, nudata)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY IC22_bgloglike
  START_CAPABILITY
    #define FUNCTION IC22_bgloglike
    START_FUNCTION(double)
    DEPENDENCY(IC22_data, nudata)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY IC22_pvalue
  START_CAPABILITY
    #define FUNCTION IC22_pvalue
    START_FUNCTION(double)
    DEPENDENCY(IC22_data, nudata)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY IC22_nobs
  START_CAPABILITY
    #define FUNCTION IC22_nobs
    START_FUNCTION(int)
    DEPENDENCY(IC22_data, nudata)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY IC79WH_data
  START_CAPABILITY
    #define FUNCTION IC79WH_full
      START_FUNCTION(nudata)
      DEPENDENCY(mwimp, double)
      DEPENDENCY(annihilation_rate_Sun, double)
      DEPENDENCY(nuyield_ptr, nuyield_info)
      BACKEND_REQ(nubounds, (), void, (const char&, const double&, const double&,
                                       nuyield_function_pointer, double&, double&, int&,
                                       double&, double&, const int&, const double&,
                                       const int&, const bool&, const double&,
                                       const double&, void*&, const bool&))
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY IC79WH_signal
  START_CAPABILITY
    #define FUNCTION IC79WH_signal
    START_FUNCTION(double)
    DEPENDENCY(IC79WH_data, nudata)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY IC79WH_bg
  START_CAPABILITY
    #define FUNCTION IC79WH_bg
    START_FUNCTION(double)
    DEPENDENCY(IC79WH_data, nudata)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY IC79WH_loglike
  START_CAPABILITY
    #define FUNCTION IC79WH_loglike
    START_FUNCTION(double)
    DEPENDENCY(IC79WH_data, nudata)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY IC79WH_bgloglike
  START_CAPABILITY
    #define FUNCTION IC79WH_bgloglike
    START_FUNCTION(double)
    DEPENDENCY(IC79WH_data, nudata)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY IC79WH_pvalue
  START_CAPABILITY
    #define FUNCTION IC79WH_pvalue
    START_FUNCTION(double)
    DEPENDENCY(IC79WH_data, nudata)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY IC79WH_nobs
  START_CAPABILITY
    #define FUNCTION IC79WH_nobs
    START_FUNCTION(int)
    DEPENDENCY(IC79WH_data, nudata)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY IC79WL_data
  START_CAPABILITY
    #define FUNCTION IC79WL_full
      START_FUNCTION(nudata)
      DEPENDENCY(mwimp, double)
      DEPENDENCY(annihilation_rate_Sun, double)
      DEPENDENCY(nuyield_ptr, nuyield_info)
      BACKEND_REQ(nubounds, (), void, (const char&, const double&, const double&,
                                       nuyield_function_pointer, double&, double&, int&,
                                       double&, double&, const int&, const double&,
                                       const int&, const bool&, const double&,
                                       const double&, void*&, const bool&))
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY IC79WL_signal
  START_CAPABILITY
    #define FUNCTION IC79WL_signal
    START_FUNCTION(double)
    DEPENDENCY(IC79WL_data, nudata)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY IC79WL_bg
  START_CAPABILITY
    #define FUNCTION IC79WL_bg
    START_FUNCTION(double)
    DEPENDENCY(IC79WL_data, nudata)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY IC79WL_loglike
  START_CAPABILITY
    #define FUNCTION IC79WL_loglike
    START_FUNCTION(double)
    DEPENDENCY(IC79WL_data, nudata)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY IC79WL_bgloglike
  START_CAPABILITY
    #define FUNCTION IC79WL_bgloglike
    START_FUNCTION(double)
    DEPENDENCY(IC79WL_data, nudata)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY IC79WL_pvalue
  START_CAPABILITY
    #define FUNCTION IC79WL_pvalue
    START_FUNCTION(double)
    DEPENDENCY(IC79WL_data, nudata)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY IC79WL_nobs
  START_CAPABILITY
    #define FUNCTION IC79WL_nobs
    START_FUNCTION(int)
    DEPENDENCY(IC79WL_data, nudata)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY IC79SL_data
  START_CAPABILITY
    #define FUNCTION IC79SL_full
      START_FUNCTION(nudata)
      DEPENDENCY(mwimp, double)
      DEPENDENCY(annihilation_rate_Sun, double)
      DEPENDENCY(nuyield_ptr, nuyield_info)
      BACKEND_REQ(nubounds, (), void, (const char&, const double&, const double&,
                                       nuyield_function_pointer, double&, double&, int&,
                                       double&, double&, const int&, const double&,
                                       const int&, const bool&, const double&,
                                       const double&, void*&, const bool&))
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY IC79SL_signal
  START_CAPABILITY
    #define FUNCTION IC79SL_signal
    START_FUNCTION(double)
    DEPENDENCY(IC79SL_data, nudata)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY IC79SL_bg
  START_CAPABILITY
    #define FUNCTION IC79SL_bg
    START_FUNCTION(double)
    DEPENDENCY(IC79SL_data, nudata)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY IC79SL_loglike
  START_CAPABILITY
    #define FUNCTION IC79SL_loglike
    START_FUNCTION(double)
    DEPENDENCY(IC79SL_data, nudata)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY IC79SL_bgloglike
  START_CAPABILITY
    #define FUNCTION IC79SL_bgloglike
    START_FUNCTION(double)
    DEPENDENCY(IC79SL_data, nudata)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY IC79SL_pvalue
  START_CAPABILITY
    #define FUNCTION IC79SL_pvalue
    START_FUNCTION(double)
    DEPENDENCY(IC79SL_data, nudata)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY IC79SL_nobs
  START_CAPABILITY
    #define FUNCTION IC79SL_nobs
    START_FUNCTION(int)
    DEPENDENCY(IC79SL_data, nudata)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY IC79_loglike
  START_CAPABILITY
    #define FUNCTION IC79_loglike
    START_FUNCTION(double)
    DEPENDENCY(IC79WH_loglike, double)
    DEPENDENCY(IC79WL_loglike, double)
    DEPENDENCY(IC79SL_loglike, double)
    DEPENDENCY(IC79WH_bgloglike, double)
    DEPENDENCY(IC79WL_bgloglike, double)
    DEPENDENCY(IC79SL_bgloglike, double)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY IceCube_likelihood
  START_CAPABILITY
    #define FUNCTION IC_loglike
    START_FUNCTION(double)
    DEPENDENCY(IC22_loglike, double)
    DEPENDENCY(IC79WH_loglike, double)
    DEPENDENCY(IC79WL_loglike, double)
    DEPENDENCY(IC79SL_loglike, double)
    DEPENDENCY(IC22_bgloglike, double)
    DEPENDENCY(IC79WH_bgloglike, double)
    DEPENDENCY(IC79WL_bgloglike, double)
    DEPENDENCY(IC79SL_bgloglike, double)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY UnitTest_DarkBit
  START_CAPABILITY
    #define FUNCTION UnitTest_DarkBit
    START_FUNCTION(int)
    DEPENDENCY(DD_couplings, DM_nucleon_couplings)
    DEPENDENCY(RD_oh2, double)
    DEPENDENCY(GA_AnnYield, daFunk::Funk)
    DEPENDENCY(TH_ProcessCatalog, TH_ProcessCatalog)
    DEPENDENCY(DarkMatter_ID, std::string)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY SimYieldTable
  START_CAPABILITY
    #define FUNCTION SimYieldTable_DarkSUSY
    START_FUNCTION(SimYieldTable)
    BACKEND_REQ(dshayield, (), double, (double&,double&,int&,int&,int&))
    #undef FUNCTION
    #define FUNCTION SimYieldTable_MicrOmegas
    START_FUNCTION(SimYieldTable)
    BACKEND_REQ(dNdE, (), double, (double,double,int,int))
    #undef FUNCTION
    #define FUNCTION SimYieldTable_PPPC
    START_FUNCTION(SimYieldTable)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY DarkMatter_ID
  START_CAPABILITY
    #define FUNCTION DarkMatter_ID_ScalarSingletDM
    START_FUNCTION(std::string)
    ALLOW_MODELS(ScalarSingletDM_Z2, ScalarSingletDM_Z2_running, ScalarSingletDM_Z3, ScalarSingletDM_Z3_running)
    #undef FUNCTION
    #define FUNCTION DarkMatter_ID_VectorSingletDM
    START_FUNCTION(std::string)
    ALLOW_MODELS(VectorSingletDM_Z2)
    #undef FUNCTION
    #define FUNCTION DarkMatter_ID_MajoranaSingletDM
    START_FUNCTION(std::string)
    ALLOW_MODELS(MajoranaSingletDM_Z2)
    #undef FUNCTION
    #define FUNCTION DarkMatter_ID_DiracSingletDM
    START_FUNCTION(std::string)
    ALLOW_MODELS(DiracSingletDM_Z2)
    #undef FUNCTION
    #define FUNCTION DarkMatter_ID_MSSM
    START_FUNCTION(std::string)
    DEPENDENCY(MSSM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY

  // --- Functions related to the local and global properties of the DM halo ---

  #define CAPABILITY GalacticHalo
  START_CAPABILITY
    #define FUNCTION GalacticHalo_gNFW
    START_FUNCTION(GalacticHaloProperties)
    ALLOW_MODEL(Halo_gNFW)
    #undef FUNCTION
    #define FUNCTION GalacticHalo_Einasto
    START_FUNCTION(GalacticHaloProperties)
    ALLOW_MODEL(Halo_Einasto)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY LocalHalo
  START_CAPABILITY
    #define FUNCTION ExtractLocalMaxwellianHalo
    START_FUNCTION(LocalMaxwellianHalo)
    ALLOW_MODELS(Halo_gNFW, Halo_Einasto)
    #undef FUNCTION
  #undef CAPABILITY

  // Axion likelihoods and functions -----------------------

  #define CAPABILITY QCDAxion_ZeroTemperatureMass
  START_CAPABILITY
    #define FUNCTION QCDAxion_ZeroTemperatureMass_Nuisance_lnL
    START_FUNCTION(double)
    ALLOW_MODEL(QCDAxion)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY QCDAxion_TemperatureDependence
  START_CAPABILITY
    #define FUNCTION QCDAxion_TemperatureDependence_Nuisance_lnL
    START_FUNCTION(double)
    ALLOW_MODEL(QCDAxion)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY QCDAxion_AxionPhotonConstant
  START_CAPABILITY
    #define FUNCTION QCDAxion_AxionPhotonConstant_Nuisance_lnL
    START_FUNCTION(double)
    ALLOW_MODEL(QCDAxion)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY ALPS1_signal_vac
  START_CAPABILITY
    #define FUNCTION calc_ALPS1_signal_vac
    START_FUNCTION(double)
    ALLOW_MODEL(GeneralALP)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY ALPS1_signal_gas
  START_CAPABILITY
    #define FUNCTION calc_ALPS1_signal_gas
    START_FUNCTION(double)
    ALLOW_MODEL(GeneralALP)
  #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lnL_ALPS1
  START_CAPABILITY
    #define FUNCTION calc_lnL_ALPS1
    START_FUNCTION(double)
    ALLOW_MODEL(GeneralALP)
    DEPENDENCY(ALPS1_signal_vac, double)
    DEPENDENCY(ALPS1_signal_gas, double)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY CAST2007_signal_vac
  START_CAPABILITY
    #define FUNCTION calc_CAST2007_signal_vac
    START_FUNCTION(std::vector<double>)
    ALLOW_MODEL(GeneralALP)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY CAST2017_signal_vac
  START_CAPABILITY
    #define FUNCTION calc_CAST2017_signal_vac
    START_FUNCTION(std::vector<std::vector<double>>)
    ALLOW_MODEL(GeneralALP)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lnL_CAST2007
  START_CAPABILITY
    #define FUNCTION calc_lnL_CAST2007
    START_FUNCTION(double)
    ALLOW_MODEL(GeneralALP)
    DEPENDENCY(CAST2007_signal_vac, std::vector<double>)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lnL_CAST2017
  START_CAPABILITY
    #define FUNCTION calc_lnL_CAST2017
    START_FUNCTION(double)
    ALLOW_MODEL(GeneralALP)
    DEPENDENCY(CAST2017_signal_vac, std::vector<std::vector<double>>)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Haloscope_signal
  START_CAPABILITY
    #define FUNCTION calc_Haloscope_signal
    START_FUNCTION(double)
    ALLOW_MODEL(GeneralALP)
    DEPENDENCY(RD_fraction, double)
    DEPENDENCY(LocalHalo, LocalMaxwellianHalo)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lnL_Haloscope_ADMX1
  START_CAPABILITY
    #define FUNCTION calc_lnL_Haloscope_ADMX1
    START_FUNCTION(double)
    ALLOW_MODEL(GeneralALP)
    DEPENDENCY(Haloscope_signal, double)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lnL_Haloscope_ADMX2
  START_CAPABILITY
    #define FUNCTION calc_lnL_Haloscope_ADMX2
    START_FUNCTION(double)
    ALLOW_MODEL(GeneralALP)
    DEPENDENCY(Haloscope_signal, double)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lnL_Haloscope_RBF
  START_CAPABILITY
    #define FUNCTION calc_lnL_Haloscope_RBF
    START_FUNCTION(double)
    ALLOW_MODEL(GeneralALP)
    DEPENDENCY(Haloscope_signal, double)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lnL_Haloscope_UF
  START_CAPABILITY
    #define FUNCTION calc_lnL_Haloscope_UF
    START_FUNCTION(double)
    ALLOW_MODEL(GeneralALP)
    DEPENDENCY(Haloscope_signal, double)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY RParameter
  START_CAPABILITY
    #define FUNCTION calc_RParameter
    START_FUNCTION(double)
    DEPENDENCY(GeneralALP_parameters, ModelParameters)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lnL_RParameter
  START_CAPABILITY
    #define FUNCTION calc_lnL_RParameter
    START_FUNCTION(double)
    ALLOW_MODEL(GeneralALP)
    DEPENDENCY(RParameter, double)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lnL_WDVar_G117B15A
  START_CAPABILITY
    #define FUNCTION calc_lnL_WDVar_G117B15A
    START_FUNCTION(double)
    ALLOW_MODEL(GeneralALP)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lnL_WDVar_R548
  START_CAPABILITY
    #define FUNCTION calc_lnL_WDVar_R548
    START_FUNCTION(double)
    ALLOW_MODEL(GeneralALP)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lnL_WDVar_PG1351489
  START_CAPABILITY
    #define FUNCTION calc_lnL_WDVar_PG1351489
    START_FUNCTION(double)
    ALLOW_MODEL(GeneralALP)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lnL_WDVar_L192
  START_CAPABILITY
    #define FUNCTION calc_lnL_WDVar_L192
    START_FUNCTION(double)
    ALLOW_MODEL(GeneralALP)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lnL_SN1987A
  START_CAPABILITY
    #define FUNCTION calc_lnL_SN1987A
    START_FUNCTION(double)
    ALLOW_MODEL(GeneralALP)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lnL_HESS_GCMF
  START_CAPABILITY
    #define FUNCTION calc_lnL_HESS_GCMF
    START_FUNCTION(double)
    ALLOW_MODEL(GeneralALP)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY AxionOscillationTemperature
  START_CAPABILITY
    #define FUNCTION calc_AxionOscillationTemperature
    START_FUNCTION(double)
    ALLOW_MODEL(GeneralALP)
    #undef FUNCTION
  #undef CAPABILITY

#undef MODULE
#endif /* defined(__DarkBit_rollcall_hpp__) */
