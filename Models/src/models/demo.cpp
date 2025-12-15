///  GAMBIT: Global and Modular BSM Inference Tool
///  *********************************************
///
///  Model consistency function for NormalDist
///
///  *********************************************
///
///  Authors
///  =======
///
///  (add name and date if you modify)
///
///  \author Patrick Stöcker
///          (stoecker@physik.rwth-aachen.de)
///  \date 2025 June
///
///  *********************************************


#include "gambit/Models/model_macros.hpp"
#include "gambit/Models/model_helpers.hpp"
#include "gambit/Logs/logger.hpp"

#include "gambit/Models/models/demo.hpp"

#define MODEL NormalDist
  bool MODEL_NAMESPACE::NormalDist_ensure_positive_sigma (const Gambit::ModelParameters& modelparams)
  {
    logger() << "Running model_consistency_check for NormalDist ..." << EOM;

    return modelparams["sigma"] > 0.0;
  }
#undef MODEL
