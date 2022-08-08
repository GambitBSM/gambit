#ifndef __loaded_types_FlexibleSUSY_CMSSM_2_0_1_hpp__
#define __loaded_types_FlexibleSUSY_CMSSM_2_0_1_hpp__ 1

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include "wrapper_CMSSM_input_parameters.h"
#include "wrapper_CMSSM_scales.h"
#include "wrapper_CMSSM_slha_io.h"
#include "wrapper_Spectrum_generator_problems.h"
#include "wrapper_QedQcd.h"
#include "wrapper_Two_scale.h"
#include "wrapper_CMSSM_spectrum_generator__Two_scale.h"
#include "wrapper_Spectrum_generator_settings.h"
#include "identification.hpp"
#pragma GCC diagnostic pop

// Indicate which types are provided by this backend, and what the symbols of their factories are.
#define FlexibleSUSY_CMSSM_2_0_1_all_data \
  (( /*class*/(flexiblesusy)(CMSSM_input_parameters),    /*constructors*/(("Factory_CMSSM_input_parameters_0__BOSS_1",())) )) \
  (( /*class*/(flexiblesusy)(CMSSM_scales),    /*constructors*/(("Factory_CMSSM_scales_0__BOSS_2",())) )) \
  (( /*class*/(flexiblesusy)(CMSSM_slha_io),    /*constructors*/(("Factory_CMSSM_slha_io_0__BOSS_3",())) )) \
  (( /*class*/(flexiblesusy)(Spectrum_generator_problems),    /*constructors*/(("Factory_Spectrum_generator_problems_0__BOSS_4",())) )) \
  (( /*class*/(softsusy)(QedQcd),    /*constructors*/(("Factory_QedQcd_0__BOSS_5",())) )) \
  (( /*class*/(flexiblesusy)(Two_scale),    /*constructors*/(("Factory_Two_scale_0__BOSS_6",())) )) \
  (( /*class*/(flexiblesusy)(CMSSM_spectrum_generator__Two_scale),    /*constructors*/(("Factory_CMSSM_spectrum_generator__Two_scale_0__BOSS_7",())) )) \
  (( /*class*/(flexiblesusy)(Spectrum_generator_settings),    /*constructors*/(("Factory_Spectrum_generator_settings_0__BOSS_8",())) )) \

// If the default version has been loaded, set it as default.
#if ALREADY_LOADED(CAT_3(BACKENDNAME,_,CAT(Default_,BACKENDNAME)))
  SET_DEFAULT_VERSION_FOR_LOADING_TYPES(BACKENDNAME,SAFE_VERSION,CAT(Default_,BACKENDNAME))
    namespace Gambit
    {
        namespace FlexibleSUSY_CMSSM_default
        {
            namespace flexiblesusy
            {
                template <class T0> class CMSSM_spectrum_generator { };
                template <> class CMSSM_spectrum_generator<Two_scale>: public CMSSM_spectrum_generator__Two_scale { using CMSSM_spectrum_generator__Two_scale::CMSSM_spectrum_generator__Two_scale; };
            }
        }
    }
#endif

namespace FlexibleSUSY_CMSSM_2_0_1
{
    namespace flexiblesusy
    {
        template <class T0> class CMSSM_spectrum_generator { };
        template <> class CMSSM_spectrum_generator<Two_scale>: public CMSSM_spectrum_generator__Two_scale { using CMSSM_spectrum_generator__Two_scale::CMSSM_spectrum_generator__Two_scale; };
    }
}

// Undefine macros to avoid conflict with other backends.
#include "gambit/Backends/backend_undefs.hpp"

#endif /* __loaded_types_FlexibleSUSY_CMSSM_2_0_1_hpp__ */
