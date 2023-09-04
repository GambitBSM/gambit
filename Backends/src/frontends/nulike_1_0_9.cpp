//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend source for the nulike backend.
///
///  Actual implementation of nulike ini function.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (patscott@physics.mcgill.ca)
///  \date 2013 May
///  \date 2014 March
///  \date 2015 Aug
///  \date 2017 Nov
///
///  *********************************************

#include "gambit/Backends/frontend_macros.hpp"
#include "gambit/Backends/frontends/nulike_1_0_9.hpp"


BE_INI_FUNCTION
{

  // Scan-level initialisation
  static bool scan_level = true;
  if (scan_level)
  {

    // Call initialisation functions only if nulike is actually to be used for nu limits.
    if (*InUse::nulike_bounds)
    {

      // Fixed string length in nulike (from nulike fortran header nucommon.h)
      const int clen = 300;
      // Choose a log-normal or a Gaussian distribution for the systematic error on the number of neutrino events
      bool uselogNorm = true;
      // Choose whether to precompute the background p-value.
      bool BGLikePrecompute = true;

      // Define analysis cut cone in degrees around solar position, analysis handle and
      // datafiles for IceCube 22-string analysis, then initialise it.
      double phi_cut22 = 10.0;
      const char experiment_22[clen] = "IC-22";
      char eventf_22[clen], BGf_22[clen], effareaf_22[clen], edispf_22[clen];
      Utils::strcpy2f(eventf_22, clen, runOptions->getValueOrDef<str>(backendDir +
       "/../data/IceCube/likelihood2012/events_10deg_IC22.dat", "IC22_event_file"));
      Utils::strcpy2f(BGf_22, clen, runOptions->getValueOrDef<str>(backendDir +
       "/../data/IceCube/likelihood2012/BG_distributions_IC22.dat", "IC22_BG_file"));
      Utils::strcpy2f(effareaf_22, clen, runOptions->getValueOrDef<str>(backendDir +
       "/../data/IceCube/likelihood2012/nuEffArea_IC22.dat", "IC22_EffA_file"));
      Utils::strcpy2f(edispf_22, clen, runOptions->getValueOrDef<str>(backendDir +
       "/../data/IceCube/likelihood2012/energy_histograms_IC22.dat", "IC22_Edisp_file"));
      nulike_init(experiment_22[0], eventf_22[0], BGf_22[0], effareaf_22[0], edispf_22[0],
                  phi_cut22, uselogNorm, BGLikePrecompute);

      // Define analysis handle and datafiles for IceCube 79-string WH analysis,
      // then initialise it; phi_cut is ignored for 2015-type analyses.
      const char experiment_79WH[clen] = "IC-79 WH";
      char eventf_79WH[clen], BGf_79WH[clen], effareaf_79WH[clen], partiald_79WH[clen];
      Utils::strcpy2f(eventf_79WH, clen, runOptions->getValueOrDef<str>(backendDir +
       "/../data/IceCube/likelihood2015/IC79_Events_WH_llhInput_60Deg.txt", "IC79WH_event_file"));
      Utils::strcpy2f(BGf_79WH, clen, runOptions->getValueOrDef<str>(backendDir +
       "/../data/IceCube/likelihood2015/IC79_Background_distributions_WH.txt", "IC79WH_BG_file"));
      Utils::strcpy2f(effareaf_79WH, clen, runOptions->getValueOrDef<str>(backendDir +
       "/../data/IceCube/likelihood2015/IC79_Effective_Area_WH.txt", "IC79WH_effective_area_file"));
      Utils::strcpy2f(partiald_79WH, clen, runOptions->getValueOrDef<str>(backendDir +
       "/../data/IceCube/likelihood2015/IC79_Partial_Likelihoods_WH", "IC79WH_partial_like_dir"));
      nulike_init(experiment_79WH[0], eventf_79WH[0], BGf_79WH[0], effareaf_79WH[0], partiald_79WH[0],
                  phi_cut22, uselogNorm, BGLikePrecompute);

      // Define analysis handle and datafiles for IceCube 79-string WL analysis, then initialise it.
      const char experiment_79WL[clen] = "IC-79 WL";
      char eventf_79WL[clen], BGf_79WL[clen], effareaf_79WL[clen], partiald_79WL[clen];
      Utils::strcpy2f(eventf_79WL, clen, runOptions->getValueOrDef<str>(backendDir +
       "/../data/IceCube/likelihood2015/IC79_Events_WL_llhInput_60Deg.txt", "IC79WL_event_file"));
      Utils::strcpy2f(BGf_79WL, clen, runOptions->getValueOrDef<str>(backendDir +
       "/../data/IceCube/likelihood2015/IC79_Background_distributions_WL.txt", "IC79WL_BG_file"));
      Utils::strcpy2f(effareaf_79WL, clen, runOptions->getValueOrDef<str>(backendDir +
       "/../data/IceCube/likelihood2015/IC79_Effective_Area_WL.txt", "IC79WL_effective_area_file"));
      Utils::strcpy2f(partiald_79WL, clen, runOptions->getValueOrDef<str>(backendDir +
       "/../data/IceCube/likelihood2015/IC79_Partial_Likelihoods_WL", "IC79WL_partial_like_dir"));
      nulike_init(experiment_79WL[0], eventf_79WL[0], BGf_79WL[0], effareaf_79WL[0], partiald_79WL[0],
                  phi_cut22, uselogNorm, BGLikePrecompute);

      // Define analysis handle and datafiles for IceCube 79-string SL analysis, then initialise it.
      const char experiment_79SL[clen] = "IC-79 SL";
      char eventf_79SL[clen], BGf_79SL[clen], effareaf_79SL[clen], partiald_79SL[clen];
      Utils::strcpy2f(eventf_79SL, clen, runOptions->getValueOrDef<str>(backendDir +
       "/../data/IceCube/likelihood2015/IC79_Events_SL_llhInput_60Deg.txt", "IC79SL_event_file"));
      Utils::strcpy2f(BGf_79SL, clen, runOptions->getValueOrDef<str>(backendDir +
       "/../data/IceCube/likelihood2015/IC79_Background_distributions_SL.txt", "IC79SL_BG_file"));
      Utils::strcpy2f(effareaf_79SL, clen, runOptions->getValueOrDef<str>(backendDir +
       "/../data/IceCube/likelihood2015/IC79_Effective_Area_SL.txt", "IC79SL_effective_area_file"));
      Utils::strcpy2f(partiald_79SL, clen, runOptions->getValueOrDef<str>(backendDir +
       "/../data/IceCube/likelihood2015/IC79_Partial_Likelihoods_SL", "IC79SL_partial_like_dir"));
      nulike_init(experiment_79SL[0], eventf_79SL[0], BGf_79SL[0], effareaf_79SL[0], partiald_79SL[0],
                  phi_cut22, uselogNorm, BGLikePrecompute);

    }

  }
  scan_level = false;

}
END_BE_INI_FUNCTION
