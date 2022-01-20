#ifndef __loaded_types_ExampleBackend_1_234_hpp__
#define __loaded_types_ExampleBackend_1_234_hpp__ 1

#include "wrapper_Node.hpp"
#include "wrapper_ClassOne.hpp"
#include "wrapper_ClassTwo.hpp"
#include "identification.hpp"

// Indicate which types are provided by this backend, and what the symbols of their factories are.
#define ExampleBackend_1_234_all_data \
  (( /*class*/(Node),    /*constructors*/(("Factory_Node_0__BOSS_1",())) )) \
  (( /*class*/(ClassOne),    /*constructors*/(("Factory_ClassOne_0__BOSS_2",())) (("Factory_ClassOne_1__BOSS_3",(double, int))) )) \
  (( /*class*/(SomeNamespace)(ClassTwo),    /*constructors*/(("Factory_ClassTwo_0__BOSS_4",())) )) \

// If the default version has been loaded, set it as default.
#if ALREADY_LOADED(CAT_3(BACKENDNAME,_,CAT(Default_,BACKENDNAME)))
  SET_DEFAULT_VERSION_FOR_LOADING_TYPES(BACKENDNAME,SAFE_VERSION,CAT(Default_,BACKENDNAME))
#endif

// Undefine macros to avoid conflict with other backends.
#include "gambit/Backends/backend_undefs.hpp"

#endif /* __loaded_types_ExampleBackend_1_234_hpp__ */
