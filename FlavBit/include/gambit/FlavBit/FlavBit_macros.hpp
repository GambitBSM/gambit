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

#include "gambit/Utils/util_macros.hpp"

namespace Gambit
{

  namespace FlavBit
  {

    /// SuperIso prediction macros

    /// Macros to parse bins
    #define MAKE_BIN_BRACE(bins) BOOST_PP_SEQ_ENUM(                      \
      BOOST_PP_SEQ_TRANSFORM(MAKE_BIN_STRING_I,,                         \
      BOOST_PP_TUPLE_TO_SEQ(bins)))
    #define MAKE_BIN_STRING_I(r,data,elem)                               \
      STRINGIFY(MAKE_BIN_STRING elem)
    #define MAKE_BIN_STRING_2(_1,_2) _1##_##_2
    #define MAKE_BIN_STRING_1(_1) _1
    #define MAKE_BIN_STRING(...) VARARG(MAKE_BIN_STRING, __VA_ARGS__)

    // Rest of function
    #define THE_REST(bins)                                          \
      std::vector<str> SI_obslist =                                 \
       translate_flav_obs("FlavBit", "SuperIso", FB_obslist,        \
       bins);                                                       \
      static bool use_SM_covariance =                               \
       runOptions->getValueOrDef<bool>(false, "use_SM_covariance"); \
      static bool SM_covariance_cached = false;                     \
      SuperIso_prediction_helper(                                   \
        FB_obslist,                                                 \
        SI_obslist,                                                 \
        prediction,                                                 \
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
      flav_prediction prediction;                                        \
      static const std::vector<str> FB_obslist = {#name};                \
      THE_REST("")                                                       \
      result = prediction;                                               \
    }                                                                    \


    #define SI_SINGLE_PREDICTION_FUNCTION_BINS(name,bins)                \
    void CAT(SuperIso_prediction_,name)(flav_binned_prediction &result)  \
    {                                                                    \
      using namespace CAT(Pipes::SuperIso_prediction_,name);             \
      flav_prediction prediction;                                        \
      static const std::vector<str> FB_obslist = {#name};                \
      static const std::vector<str> vbins = {MAKE_BIN_BRACE(bins)};      \
      for(str bin: vbins)                                                \
      {                                                                  \
        THE_REST(bin)                                                    \
        result[bin] = prediction;                                        \
      }                                                                  \
    }                                                                    \

    #define SI_SINGLE_PREDICTION_FUNCTION_EXP_BINS(name,exp,bins)        \
    void CAT_4(SuperIso_prediction_,name,_,exp)(flav_binned_prediction&  \
     result)                                                             \
    {                                                                    \
      using namespace CAT_4(Pipes::SuperIso_prediction_,name,_,exp);     \
      flav_prediction prediction;                                        \
      static const std::vector<str> FB_obslist = {#name};                \
      static const std::vector<str> vbins = {MAKE_BIN_BRACE(bins)};      \
      for(str bin: vbins)                                                \
      {                                                                  \
        THE_REST(bin)                                                    \
        result[bin] = prediction;                                        \
      }                                                                  \
    }                                                                    \

    #define SI_MULTI_PREDICTION_FUNCTION(name)                           \
    void CAT(SuperIso_prediction_,name)(flav_prediction& result)         \
    {                                                                    \
      using namespace CAT(Pipes::SuperIso_prediction_,name);             \
      flav_prediction prediction;                                        \
      static const std::vector<str> FB_obslist =                         \
       Downstream::subcaps->getNames();                                  \
      if (FB_obslist.empty()) FlavBit_error().raise(LOCAL_INFO,          \
       "Missing subcapabilities for SuperIso_prediction_"#name".");      \
      THE_REST("")                                                       \
      result = prediction;                                               \
    }                                                                    \


    #define SI_MULTI_PREDICTION_FUNCTION_BINS(name,exp,bins)             \
    void CAT_4(SuperIso_prediction_,name,_,exp)(flav_binned_prediction&  \
     result)                                                             \
    {                                                                    \
      using namespace CAT_4(Pipes::SuperIso_prediction_,name,_,exp);     \
      flav_prediction prediction;                                        \
      static const std::vector<str> FB_obslist =                         \
       Downstream::subcaps->getNames();                                  \
      if (FB_obslist.empty()) FlavBit_error().raise(LOCAL_INFO,          \
       "Missing subcapabilities for SuperIso_prediction_"#name".");      \
      static const std::vector<str> vbins = {MAKE_BIN_BRACE(bins)};      \
      for(str bin: vbins)                                                \
      {                                                                  \
        THE_REST(bin)                                                    \
        result[bin] = prediction;                                        \
      }                                                                  \
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
