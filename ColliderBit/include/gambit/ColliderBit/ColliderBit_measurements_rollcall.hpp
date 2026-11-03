//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Rollcall header for ColliderBit measurments.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2019 July
///
///  \author Tomek Procter
///          (t.procter.1@research.gla.ac.uk)
///  \date 2021 July
///
///  *********************************************

#pragma once

#define MODULE ColliderBit


  /// Only activate this capability if HepMC and YODA are activated
  #ifndef EXCLUDE_HEPMC
    #ifndef EXCLUDE_YODA

      // Get measurements from Rivet
      #define CAPABILITY Rivet_measurements
      START_CAPABILITY

        #define FUNCTION Rivet_measurements
        START_FUNCTION(std::shared_ptr<std::ostringstream>)
        NEEDS_CLASSES_FROM(Rivet, default)
        DEPENDENCY(HardScatteringEvent, HepMC3::GenEvent)
        BACKEND_REQ(Contur_GetAnalyses, (libcontur), void, (std::vector<std::string>&, std::string&))
        NEEDS_MANAGER(RunMC, MCLoopInfo)
        #undef FUNCTION

      #undef CAPABILITY
    #endif
  #endif

  // Needs python backend
  #ifdef HAVE_PYBIND11

    // This capability only works if YODA is activated
    #ifndef EXCLUDE_YODA

      // Calculate the log-likelihood for LHC measurements from a YODA file
      #define CAPABILITY LHC_measurements
      START_CAPABILITY

        // Contur version, from YODA stream
        #define FUNCTION Contur_LHC_measurements_from_stream
        START_FUNCTION(Contur_output)
        DEPENDENCY(Rivet_measurements, std::shared_ptr<std::ostringstream>)
        BACKEND_REQ(Contur_Measurements, (libcontur), Contur_output, (std::shared_ptr<std::ostringstream>, std::vector<std::string>&))
        NEEDS_MANAGER(RunMC, MCLoopInfo)
        BACKEND_OPTION( (Contur), (libcontur) )
        #undef FUNCTION

        // Contur version for running multiple instances of Contur (e.g. with different settings), from YODA stream
        #define FUNCTION Multi_Contur_LHC_measurements_from_stream
        START_FUNCTION(Multi_Contur_output)
        DEPENDENCY(Rivet_measurements, std::shared_ptr<std::ostringstream>)
        BACKEND_REQ(Contur_Measurements, (libcontur), Contur_output, (std::shared_ptr<std::ostringstream>, std::vector<std::string>&))
        NEEDS_MANAGER(RunMC, MCLoopInfo)
        BACKEND_OPTION( (Contur), (libcontur) )
        #undef FUNCTION

        // Contur version, from file
        #define FUNCTION Contur_LHC_measurements_from_file
        START_FUNCTION(Contur_output)
        BACKEND_REQ(Contur_Measurements, (libcontur), Contur_output, (str &, std::vector<std::string>&))
        BACKEND_OPTION( (Contur), (libcontur) )
        #undef FUNCTION

      #undef CAPABILITY

      // The capability for getting the LLR contribution from Contur.
      #define CAPABILITY LHC_measurements_LogLike
      START_CAPABILITY
        #define FUNCTION Contur_LHC_measurements_LogLike
        START_FUNCTION(double)
        DEPENDENCY(LHC_measurements, Contur_output)
        #undef FUNCTION

        // For the case we run multiple instances of Contur, get the LLR from the FIRST as the overall contribution to ColliderBit
        #define FUNCTION Multi_Contur_LHC_measurements_LogLike_single
        START_FUNCTION(double)
        DEPENDENCY(LHC_measurements, Multi_Contur_output)
        #undef FUNCTION
      #undef CAPABILITY

      // For the case we run multiple instances of Contur, get all as Likelihood details to save.
      #define CAPABILITY LHC_measurements_LogLike_Multi
      START_CAPABILITY
        #define FUNCTION Multi_Contur_LHC_measurements_LogLike_all
        START_FUNCTION(map_str_dbl)
        DEPENDENCY(LHC_measurements, Multi_Contur_output)
        #undef FUNCTION
      #undef CAPABILITY


      // Get a map of each Contur pool and the contributed LLR
      #define CAPABILITY LHC_measurements_LogLike_perPool
      START_CAPABILITY
        #define FUNCTION Contur_LHC_measurements_LogLike_perPool
        START_FUNCTION(map_str_dbl)
        DEPENDENCY(LHC_measurements, Contur_output)
        #undef FUNCTION

        #define FUNCTION Multi_Contur_LHC_measurements_LogLike_perPool
        START_FUNCTION(map_str_dbl)
        DEPENDENCY(LHC_measurements, Multi_Contur_output)
        #undef FUNCTION
      #undef CAPABILITY

      // Get a map of each Contur pool and the name of the histograms that provide exclusions
      #define CAPABILITY LHC_measurements_histotags_perPool
      START_CAPABILITY
        #define FUNCTION Contur_LHC_measurements_histotags_perPool
        START_FUNCTION(map_str_str)
        DEPENDENCY(LHC_measurements, Contur_output)
        #undef FUNCTION

        #define FUNCTION Multi_Contur_LHC_measurements_histotags_perPool
        START_FUNCTION(map_str_str)
        DEPENDENCY(LHC_measurements, Multi_Contur_output)
        #undef FUNCTION
      #undef CAPABILITY

    #endif

  #endif

#undef MODULE
