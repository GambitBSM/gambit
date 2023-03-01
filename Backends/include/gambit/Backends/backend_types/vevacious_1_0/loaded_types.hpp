#ifndef __loaded_types_vevacious_1_0_hpp__
#define __loaded_types_vevacious_1_0_hpp__ 1

#include "wrapper_VevaciousPlusPlus.hpp"
#include "identification.hpp"

// Indicate which types are provided by this backend, and what the symbols of their factories are.
#define vevacious_1_0_all_data \
  (( /*class*/(VevaciousPlusPlus)(VevaciousPlusPlus),    /*constructors*/(("Factory_VevaciousPlusPlus_0__BOSS_1",(const std::basic_string<char>&))) )) \

// If the default version has been loaded, set it as default.
#if ALREADY_LOADED(CAT_3(BACKENDNAME,_,CAT(Default_,BACKENDNAME)))
  SET_DEFAULT_VERSION_FOR_LOADING_TYPES(BACKENDNAME,SAFE_VERSION,CAT(Default_,BACKENDNAME))
#endif

// Undefine macros to avoid conflict with other backends.
#include "gambit/Backends/backend_undefs.hpp"

#endif /* __loaded_types_vevacious_1_0_hpp__ */
