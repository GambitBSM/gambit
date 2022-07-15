///  GAMBIT: Global and Modular BSM Inference Tool
///  *********************************************
///
///  Model translation functions for models holding
///  cosmological nuisance parameters.
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
///  \date 2019 Feb
///  \date 2021 Sep
///
///  \author Janina Renk
///          (janina.renk@fysik.su.se)
///   \date 2019 Feb, Jun
///
///  *********************************************

#include <string>
#include <vector>

#include "gambit/Models/model_macros.hpp"
#include "gambit/Models/model_helpers.hpp"
#include "gambit/Logs/logger.hpp"
#include "gambit/Utils/util_functions.hpp"

#include "gambit/Models/models/CosmoNuisanceModels.hpp"

/////////////// translation functions for cosmological nuisance parameter models ///////////////////////////


#define MODEL cosmo_nuisance_Pantheon
// Translation function definition
void MODEL_NAMESPACE::cosmo_nuisance_Pantheon_to_cosmo_nuisance_JLA (const ModelParameters &myP, ModelParameters &targetP)
{
  logger()<<"Running interpret_as_parent calculations for cosmo_nuisance_Pantheon --> cosmo_nuisance_JLA ..."<<LogTags::info<<EOM;

  targetP.setValue("M", myP.getValue("M"));
  // the rest (alpha, beta & Delta_M) automatically defaults to 0
}
#undef MODEL

#define MODEL cosmo_nuisance_ska1_IM_band
// Translation function definition
void MODEL_NAMESPACE::cosmo_nuisance_ska1_IM_band_to_cosmo_nuisance_ska1 (const ModelParameters &myP, ModelParameters &targetP)
{
  logger()<<"Running interpret_as_parent calculations for cosmo_nuisance_ska1_IM_band --> cosmo_nuisance_ska1 ..."<<LogTags::info<<EOM;

  targetP.setValue("sigma_NL_ska", myP.getValue("sigma_NL_ska"));
  targetP.setValue("beta_0IM", myP.getValue("beta_0IM"));
  targetP.setValue("beta_1IM", myP.getValue("beta_1IM"));
  targetP.setValue("Omega_HI0", myP.getValue("Omega_HI0"));
  targetP.setValue("alpha_HI", myP.getValue("alpha_HI"));
  // other parameters automatically defaults to 0
}
#undef MODEL

#define MODEL cosmo_nuisance_ska1_IM_band_noHI
// Translation function definition
void MODEL_NAMESPACE::cosmo_nuisance_ska1_IM_band_noHI_to_cosmo_nuisance_ska1_IM_band (const ModelParameters &myP, ModelParameters &targetP)
{
  logger()<<"Running interpret_as_parent calculations for cosmo_nuisance_ska1_IM_band_noHI --> cosmo_nuisance_ska1_IM_band ..."<<LogTags::info<<EOM;

  targetP.setValue("sigma_NL_ska", myP.getValue("sigma_NL_ska"));
  targetP.setValue("beta_0IM", myP.getValue("beta_0IM"));
  targetP.setValue("beta_1IM", myP.getValue("beta_1IM"));
  // other parameters automatically defaults to 0
}
#undef MODEL

#define MODEL cosmo_nuisance_ska1_pk
// Translation function definition
void MODEL_NAMESPACE::cosmo_nuisance_ska1_pk_to_cosmo_nuisance_ska1 (const ModelParameters &myP, ModelParameters &targetP)
{
  logger()<<"Running interpret_as_parent calculations for cosmo_nuisance_ska1_pk --> cosmo_nuisance_ska1 ..."<<LogTags::info<<EOM;

  targetP.setValue("sigma_NL_ska", myP.getValue("sigma_NL_ska"));
  targetP.setValue("beta_0SKA1", myP.getValue("beta_0SKA1"));
  targetP.setValue("beta_1SKA1", myP.getValue("beta_1SKA1"));
  // other parameters automatically defaults to 0
}
#undef MODEL

#define MODEL cosmo_nuisance_euclid_pk_noShot
// Translation function definition
void MODEL_NAMESPACE::cosmo_nuisance_euclid_pk_noShot_to_cosmo_nuisance_euclid_pk (const ModelParameters &myP, ModelParameters &targetP)
{
  logger()<<"Running interpret_as_parent calculations for cosmo_nuisance_euclid_pk_noShot --> cosmo_nuisance_euclid_pk ..."<<LogTags::info<<EOM;

  targetP.setValue("epsilon_euclid", myP.getValue("epsilon_euclid"));
  targetP.setValue("sigma_NL", myP.getValue("sigma_NL"));
  targetP.setValue("beta_0Euclid", myP.getValue("beta_0Euclid"));
  targetP.setValue("beta_1Euclid", myP.getValue("beta_1Euclid"));
  // P_shot automatically defaults to 0
}
#undef MODEL

#define MODEL cosmo_nuisance_BK14
// Translation function definition
void MODEL_NAMESPACE::cosmo_nuisance_BK14_to_cosmo_nuisance_BK15 (const ModelParameters &myP, ModelParameters &targetP)
{
  logger()<<"Running interpret_as_parent calculations for cosmo_nuisance_BK14 --> cosmo_nuisance_BK15 ..."<<LogTags::info<<EOM;

  targetP.setValue("BBbetadust", myP.getValue("BBbetadust"));
  targetP.setValue("BBbetasync", myP.getValue("BBbetasync"));
  targetP.setValue("BBdust", myP.getValue("BBdust"));
  targetP.setValue("BBsync", myP.getValue("BBsync"));
  targetP.setValue("BBalphadust", myP.getValue("BBalphadust"));
  targetP.setValue("BBTdust", myP.getValue("BBTdust"));
  targetP.setValue("BBalphasync", myP.getValue("BBalphasync"));
  targetP.setValue("BBdustsynccorr", myP.getValue("BBdustsynccorr"));
  targetP.setValue("EEtoBB_dust", myP.getValue("EEtoBB_dust"));
  targetP.setValue("EEtoBB_sync", myP.getValue("EEtoBB_sync"));
  // the rest Delta_dust,Delta_sync,gamma_corr,gamma_95,gamma_150,gamma_220 automatically defaults to 0
}
#undef MODEL

#define MODEL cosmo_nuisance_BK14priors
// Translation function definition
void MODEL_NAMESPACE::cosmo_nuisance_BK14priors_to_cosmo_nuisance_BK14 (const ModelParameters &myP, ModelParameters &targetP)
{
  logger()<<"Running interpret_as_parent calculations for cosmo_nuisance_BK14priors --> cosmo_nuisance_BK14 ..."<<LogTags::info<<EOM;

  targetP.setValue("BBbetadust", myP.getValue("BBbetadust"));
  targetP.setValue("BBbetasync", myP.getValue("BBbetasync"));
  // the rest BBdust,BBsync,BBalphadust,BBTdust,BBalphasync,BBdustsynccorr,EEtoBB_dust,EEtoBB_sync automatically defaults to 0
}
#undef MODEL

