///  GAMBIT: Global and Modular BSM Inference Tool
///  *********************************************
///
///  MajoranaSingletDM_Z2 model source file.
///
///  *********************************************
///
///  Authors
///  =======
///
///  (add name and date if you modify)
///
///  \author Ankit Beniwal
///          (ankit.beniwal@adelaide.edu.com)
///  \date 2016 Aug, 2017 Jun
///
///  \author Sebastian Wild
///          (sebastian.wild@desy.de)
///  \date 2018, Feb
///
///  \author Sanjay Bloor
///          (sanjay.bloor12@imperial.ac.uk)
///  \date 2018 Aug
///        2020 May
///
///  *********************************************

#include <string>
#include <vector>

#include "gambit/Models/model_macros.hpp"
#include "gambit/Models/model_helpers.hpp"
#include "gambit/Logs/logger.hpp"
#include "gambit/Utils/util_functions.hpp"

#include "gambit/Models/models/MajoranaSingletDM_Z2.hpp"

using namespace Gambit::Utils;

// Translation functions
#define MODEL MajoranaSingletDM_Z2_sps
#define PARENT MajoranaSingletDM_Z2
  void MODEL_NAMESPACE::MajoranaSingletDM_Z2_sps_to_MajoranaSingletDM_Z2 (const ModelParameters &myparams, ModelParameters &parentparams)
  {
    double mX = myparams["mX"];
    double lX_s = myparams["lX_s"];
    double lX_ps = myparams["lX_ps"];
    double lX = sqrt(lX_s*lX_s + lX_ps*lX_ps);
    double xi = std::acos(lX_s/lX);
    parentparams.setValue("mX", mX);
    parentparams.setValue("lX", lX);
    parentparams.setValue("xi", xi);
  }
#undef PARENT
#undef MODEL
