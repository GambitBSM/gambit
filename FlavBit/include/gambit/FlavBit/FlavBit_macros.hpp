//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Macro definition header for module FlavBit.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (pat.scott@uq.edu.au)
///  \date 2015 May, June
///  \date 2016 Aug
///  \date 2017 March
///  \date 2019 Oct
///  \date 2020 Feb
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@kit.edu)
///  \date 2022 Aug
///
///  *********************************************

#ifndef __FlavBit_macros_hpp__
#define __FlavBit_macros_hpp__

namespace Gambit
{

  namespace FlavBit
  {

    // SuperIso prediction macros
    #define THE_REST(bins)                                          \
      static const std::vector<str> SI_obslist =                    \
       translate_flav_obs("FlavBit", "SuperIso", FB_obslist,        \
       Utils::p2dot(bins));                                         \
      static bool use_SM_covariance =                               \
       runOptions->getValueOrDef<bool>(false, "use_SM_covariance"); \
      static bool SM_covariance_cached = false;                     \
      SuperIso_prediction_helper(                                   \
        FB_obslist,                                                 \
        SI_obslist,                                                 \
        result,                                                     \
        *Dep::SuperIso_modelinfo,                                   \
        *Dep::SuperIso_nuisance,                                    \
        BEreq::get_predictions_nuisance.pointer(),                  \
        BEreq::observables.pointer(),                               \
        BEreq::convert_correlation.pointer(),                       \
        BEreq::get_th_covariance_nuisance.pointer(),                \
        use_SM_covariance,                                          \
        SM_covariance_cached                                        \
    );                                                              \
    SM_covariance_cached = true;

    #define SI_SINGLE_PREDICTION_FUNCTION(name)                          \
    void CAT(SuperIso_prediction_,name)(flav_prediction& result)         \
    {                                                                    \
      using namespace CAT(Pipes::SuperIso_prediction_,name);             \
      static const std::vector<str> FB_obslist = {#name};                \
      THE_REST("")                                                       \
    }                                                                    \

    #define SI_SINGLE_PREDICTION_FUNCTION_BINS(name,bins)                \
    void CAT_3(SuperIso_prediction_,name,bins)(flav_prediction& result)  \
    {                                                                    \
      using namespace CAT_3(Pipes::SuperIso_prediction_,name,bins);      \
      static const std::vector<str> FB_obslist = {#name};                \
      THE_REST(#bins)                                                    \
    }                                                                    \

    #define SI_MULTI_PREDICTION_FUNCTION(name)                           \
    void CAT(SuperIso_prediction_,name)(flav_prediction& result)         \
    {                                                                    \
      using namespace CAT(Pipes::SuperIso_prediction_,name);             \
      static const std::vector<str> FB_obslist =                         \
       Downstream::subcaps->getNames();                                  \
      if (FB_obslist.empty()) FlavBit_error().raise(LOCAL_INFO,          \
       "Missing subcapabilities for SuperIso_prediction_"#name".");      \
      THE_REST("")                                                       \
    }                                                                    \

    #define SI_MULTI_PREDICTION_FUNCTION_BINS(name,bins,exp)             \
    void CAT_4(SuperIso_prediction_,name,bins,exp)(flav_prediction&      \
     result)                                                             \
    {                                                                    \
      using namespace CAT_4(Pipes::SuperIso_prediction_,name,bins,exp);  \
      static const std::vector<str> FB_obslist =                         \
       Downstream::subcaps->getNames();                                  \
      if (FB_obslist.empty()) FlavBit_error().raise(LOCAL_INFO,          \
       "Missing subcapabilities for SuperIso_prediction_"#name".");      \
      THE_REST(#bins)                                                    \
    }                                                                    \


    /// HEPLike single-observable likelihood
    #define HEPLIKE_GAUSSIAN_1D_LIKELIHOOD(name, file)                            \
    void CAT_3(HEPLike_,name,_LogLikelihood)(double &result)                      \
    {                                                                             \
      using namespace CAT_3(Pipes::HEPLike_,name,_LogLikelihood);                 \
      static const std::string inputfile = path_to_latest_heplike_data() + file;  \
      static HepLike_default::HL_Gaussian gaussian(inputfile);                    \
      static bool first = true;                                                   \
                                                                                  \
      if (first)                                                                  \
      {                                                                           \
        if (flav_debug) std::cout << "Debug: Reading HepLike data file: " <<      \
         inputfile << endl;                                                       \
        gaussian.Read();                                                          \
        first = false;                                                            \
      }                                                                           \
                                                                                  \
      double theory = CAT(Dep::prediction_,name)->central_values.begin()->second; \
      double theory_variance = CAT(Dep::prediction_,name)->covariance.begin()->   \
       second.begin()->second;                                                    \
      result = gaussian.GetLogLikelihood(theory, theory_variance);                \
                                                                                  \
      if (flav_debug) std::cout << "HEPLike_" << #name                            \
       << "_LogLikelihood result: " << result << std::endl;                       \
    }

  }
}

#endif
