///  GAMBIT: Global and Modular BSM Inference Tool
///  *********************************************
///
///  DiracDM model source file. 
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
///
///  *********************************************

#include <string>
#include <vector>

#include "gambit/Models/model_macros.hpp"
#include "gambit/Models/model_helpers.hpp"
#include "gambit/Logs/logger.hpp"
#include "gambit/Utils/util_functions.hpp"

#include "gambit/Models/models/DiracDM.hpp"
#include "gambit/Elements/spectrum.hpp"

using namespace Gambit::Utils;

#define MODEL DiracDM_sps
#define PARENT DiracDM
    void MODEL_NAMESPACE::DiracDM_sps_to_DiracDM (const ModelParameters &myparams, ModelParameters &parentparams)
    {
        double mF = myparams["mF"];
        double lF_s = myparams["lF_s"];
        double lF_ps = myparams["lF_ps"];
        double lF = sqrt(lF_s*lF_s + lF_ps*lF_ps);
        double xi = std::acos(lF_s/lF);
        parentparams.setValue("mF", mF);
        parentparams.setValue("lF", lF);
        parentparams.setValue("xi", xi);
    }
#undef PARENT
#undef MODEL
