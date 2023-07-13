///  GAMBIT: Global and Modular BSM Inference Tool
///  *********************************************
///
///  Model translation functions for the DMEFT model
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
///  \date 2021 Mar
///
///  \author Tomas Gonzalo
///          (gonzalo@physik.rwth-aachen.de)
///  \date 2021 Sep
///
///  *********************************************


#include "gambit/Models/model_macros.hpp"
#include "gambit/Models/model_helpers.hpp"
#include "gambit/Logs/logger.hpp"

#include "gambit/Models/models/DMEFT.hpp"

#define MODEL General_DMEFT
  void MODEL_NAMESPACE::General_DMEFT_to_AnnihilatingDM_general (const ModelParameters& /*myparams*/, ModelParameters &friendparams)
  {
    USE_MODEL_PIPE(AnnihilatingDM_general) // get pipe for "interpret as friend" function
    logger()<<"Running interpret_as_friend calculations for DMEFT -> AnnihilatingDM_general ..."<<EOM;

    const double k = (*Dep::wimp_sc) ? 1. : 0.5;
    const double f = *Dep::RD_fraction;

    friendparams.setValue("mass", *Dep::mwimp);
    // In AnnihilatingDM_general the parameter "sigmav" is assumed to already include
    // (RD_fraction)^2 and the factor k
    friendparams.setValue("sigmav", k*f*f*(*Dep::sigmav));
  }
#undef MODEL

#define MODEL DMEFT_3flavour
void MODEL_NAMESPACE::DMEFT_3flavour_to_General_DMEFT (const ModelParameters &myparams, ModelParameters &parentparams)
{
    parentparams.setValue("C51", myparams["C51"]);
    parentparams.setValue("C52", myparams["C52"]);
    parentparams.setValue("C61", myparams["C61"]);
    parentparams.setValue("C62", myparams["C62"]);
    parentparams.setValue("C63", myparams["C63"]);
    parentparams.setValue("C64", myparams["C64"]);
    parentparams.setValue("theta61", myparams["theta61"]);
    parentparams.setValue("theta62", myparams["theta62"]);
    parentparams.setValue("theta63", myparams["theta64"]);
    parentparams.setValue("theta64", myparams["theta64"]);
    parentparams.setValue("mchi", myparams["mchi"]);
    parentparams.setValue("Lambda", 2.);
    parentparams.setValue("C71", 0.);
    parentparams.setValue("C72", 0.);
    parentparams.setValue("C73", 0.);
    parentparams.setValue("C74", 0.);
    parentparams.setValue("C75", 0.);
    parentparams.setValue("C76", 0.);
    parentparams.setValue("C77", 0.);
    parentparams.setValue("C78", 0.);
    parentparams.setValue("C79", 0.);
    parentparams.setValue("C710", 0.);
    parentparams.setValue("mtrunIN", 170.);
}
#undef MODEL

#define MODEL DMEFT
void MODEL_NAMESPACE::DMEFT_to_General_DMEFT (const ModelParameters &myparams, ModelParameters &parentparams)
{
    parentparams.setValue("C51", myparams["C51"]);
    parentparams.setValue("C52", myparams["C52"]);
    parentparams.setValue("C61", sqrt(2)*myparams["C61"]);
    parentparams.setValue("C62", sqrt(2)*myparams["C62"]);
    parentparams.setValue("C63", sqrt(2)*myparams["C63"]);
    parentparams.setValue("C64", sqrt(2)*myparams["C64"]);
    parentparams.setValue("theta61", pi/4);
    parentparams.setValue("theta62", pi/4);
    parentparams.setValue("theta63", pi/4);
    parentparams.setValue("theta64", pi/4);
    parentparams.setValue("mchi", myparams["mchi"]);
    parentparams.setValue("Lambda", myparams["Lambda"]);
    parentparams.setValue("C71", myparams["C71"]);
    parentparams.setValue("C72", myparams["C72"]);
    parentparams.setValue("C73", myparams["C73"]);
    parentparams.setValue("C74", myparams["C74"]);
    parentparams.setValue("C75", myparams["C75"]);
    parentparams.setValue("C76", myparams["C76"]);
    parentparams.setValue("C77", myparams["C77"]);
    parentparams.setValue("C78", myparams["C78"]);
    parentparams.setValue("C79", myparams["C79"]);
    parentparams.setValue("C710", myparams["C710"]);
    parentparams.setValue("mtrunIN", myparams["mtrunIN"]);
}
#undef MODEL
