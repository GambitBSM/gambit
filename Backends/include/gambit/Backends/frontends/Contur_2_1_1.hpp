//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Fronted header for the Contur backend
///
///  Compile-time registration of available
///  functions and variables from this backend.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2019 Oct, 2020 Mar
///  \date 2021 Mar
///
/// \author Tomasz Procter
///          (t.procter.1@research.gla.ac.uk)
/// \date 2021 June
///
///  *********************************************

#define BACKENDNAME Contur
#define BACKENDLANG Python3
#define VERSION 2.1.1
#define SAFE_VERSION 2_1_1
#define REFERENCE Butterworth:2016sqg

LOAD_LIBRARY

#ifdef HAVE_PYBIND11

  BE_CONV_FUNCTION(Contur_LogLike_from_stream, Contur_output, (std::shared_ptr<std::ostringstream>, std::vector<std::string>&), "Contur_Measurements")
  BE_CONV_FUNCTION(Contur_LogLike_from_file, Contur_output, (str &, std::vector<std::string>&), "Contur_Measurements")
  BE_CONV_FUNCTION(Contur_get_analyses_from_beam, void, (std::vector<std::string>&, std::string&), "Contur_GetAnalyses")

#endif

// Undefine macros to avoid conflict with other backends
#include "gambit/Backends/backend_undefs.hpp"
