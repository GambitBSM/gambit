#ifndef __loaded_types_ExampleBackendForGAMBIT_1_234_hpp__
#define __loaded_types_ExampleBackendForGAMBIT_1_234_hpp__ 1

#include "wrapper_ClassFour.hpp"
#include "wrapper_ClassFive__ClassFour.hpp"
#include "identification.hpp"

// Indicate which types are provided by this backend, and what the symbols of their factories are.
#define ExampleBackendForGAMBIT_1_234_all_data \
  (( /*class*/(ClassFour),    /*constructors*/(("Factory_ClassFour_0__BOSS_1",())) )) \
  (( /*class*/(ClassFive__ClassFour),    /*constructors*/(("Factory_ClassFive__ClassFour_0__BOSS_2",())) )) \

// If the default version has been loaded, set it as default.
#if ALREADY_LOADED(CAT_3(BACKENDNAME,_,CAT(Default_,BACKENDNAME)))
  SET_DEFAULT_VERSION_FOR_LOADING_TYPES(BACKENDNAME,SAFE_VERSION,CAT(Default_,BACKENDNAME))
  namespace Gambit
  {
    namespace ExampleBackendForGAMBIT_default
    {
      template<class T0>
      class ClassFive_T
      {};
      
      template<> class ClassFive_T<ClassFour>: public ClassFive__ClassFour { using ClassFive__ClassFour::ClassFive__ClassFour; };
      
      template <class T0> using ClassFive = typename ClassFive_T<T0>::ClassFive__ClassFour;
      
    }
  }
#endif

namespace ExampleBackendForGAMBIT_1_234
{
  template<class T0>
  class ClassFive_T
  {};
  
  template<> class ClassFive_T<ClassFour>: public ClassFive__ClassFour { using ClassFive__ClassFour::ClassFive__ClassFour; };
  
  template <class T0> using ClassFive = typename ClassFive_T<T0>::ClassFive__ClassFour;
  
}

// Undefine macros to avoid conflict with other backends.
#include "gambit/Backends/backend_undefs.hpp"

#endif /* __loaded_types_ExampleBackendForGAMBIT_1_234_hpp__ */
