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
///
///  \author Chirs Chang
///  \date 2026 Jun
///
///  *********************************************

#ifndef __ColliderBit_LEP_rollcall_hpp__
#define __ColliderBit_LEP_rollcall_hpp__


#define MODULE ColliderBit

  ///////////// LEP limits ////////////////////////

  #define MSSM30etal (MSSM30atQ, MSSM30atMGUT, NUHM2, MSSM63atQ_mG, MSSM63atMGUT_mG)

  // All LEP slepton and gaugino likelihoods are computed by a single function
  // (calc_LEP_LogLikes), which returns a map of the individual per-analysis
  // log-likelihoods. The required LEP production cross sections are computed
  // internally (via the get_sigma_ee_* helpers in lep_mssm_xsecs.hpp) rather
  // than being exposed as separate capabilities. This keeps the yaml entries
  // for the LEP likelihoods down to a single list and greatly reduces the
  // number of module-function template instantiations (and hence compile time).

  // Per-analysis LEP log-likelihoods (named breakdown).
  // The set of analyses included can be controlled with the "analyses" option;
  // the default is the standard non-overlapping set of LEP limits.
  #define CAPABILITY LEP_LogLikes
  START_CAPABILITY
    #define FUNCTION calc_LEP_LogLikes
    START_FUNCTION(map_str_dbl)
    ALLOW_MODELS(MSSM30atQ, MSSM30atMGUT, NUHM2, MSSM63atQ_mG, MSSM63atMGUT_mG)
    DEPENDENCY(MSSM_spectrum, Spectrum)
    DEPENDENCY(Z_decay_rates, DecayTable::Entry)
    DEPENDENCY(selectron_l_decay_rates, DecayTable::Entry)
    DEPENDENCY(selectron_r_decay_rates, DecayTable::Entry)
    DEPENDENCY(smuon_l_decay_rates, DecayTable::Entry)
    DEPENDENCY(smuon_r_decay_rates, DecayTable::Entry)
    DEPENDENCY(stau_1_decay_rates, DecayTable::Entry)
    DEPENDENCY(stau_2_decay_rates, DecayTable::Entry)
    DEPENDENCY(decay_rates, DecayTable)
    #undef FUNCTION
  #undef CAPABILITY

  // Combined LEP log-likelihood (single scalar, the sum of the per-analysis
  // log-likelihoods in LEP_LogLikes). This is the capability to list in the
  // yaml ObsLikes section.
  #define CAPABILITY LEP_Combined_LogLike
  START_CAPABILITY
    #define FUNCTION calc_LEP_Combined_LogLike
    START_FUNCTION(double)
    DEPENDENCY(LEP_LogLikes, map_str_dbl)
    #undef FUNCTION
  #undef CAPABILITY

  // L3 gravitino search.
  // Kept as a separate capability because it requires the gravitino mass, which
  // is only available in the MSSM63*_mG models, so it cannot share the broad
  // model/dependency set of the combined LEP likelihood above.
  QUICK_FUNCTION(ColliderBit, L3_Gravitino_LLike, NEW_CAPABILITY, L3_Gravitino_LLike, double, (MSSM63atQ_mG, MSSM63atMGUT_mG), (MSSM_spectrum, Spectrum), (Z_decay_rates, DecayTable::Entry), (decay_rates, DecayTable))

#undef MODULE

#endif /* defined __ColliderBit_LEP_rollcall_hpp__ */
