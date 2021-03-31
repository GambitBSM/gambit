#ifndef __loaded_types_THDMC_1_8_0_hpp__
#define __loaded_types_THDMC_1_8_0_hpp__ 1

#include "wrapper_SM.h"
#include "wrapper_THDM.h"
#include "wrapper_DecayTableTHDM.h"
#include "wrapper_Constraints.h"
#include "identification.hpp"

// Indicate which types are provided by this backend, and what the symbols of their factories are.
#define THDMC_1_8_0_all_data \
  (( /*class*/(SM),    /*constructors*/(("Factory_SM_0__BOSS_1",())) )) \
  (( /*class*/(THDM),    /*constructors*/(("Factory_THDM_0__BOSS_2",())) )) \
  (( /*class*/(DecayTableTHDM),    /*constructors*/(("Factory_DecayTableTHDM_0__BOSS_3",(my_ns::THDM*))) )) \
  (( /*class*/(Constraints),    /*constructors*/(("Factory_Constraints_0__BOSS_4",())) (("Factory_Constraints_1__BOSS_5",(my_ns::THDM*))) )) \

// If the default version has been loaded, set it as default.
#if ALREADY_LOADED(CAT_3(BACKENDNAME,_,CAT(Default_,BACKENDNAME)))
  SET_DEFAULT_VERSION_FOR_LOADING_TYPES(BACKENDNAME,SAFE_VERSION,CAT(Default_,BACKENDNAME))
#endif

// Undefine macros to avoid conflict with other backends.
#include "gambit/Backends/backend_undefs.hpp"

#endif /* __loaded_types_THDMC_1_8_0_hpp__ */
