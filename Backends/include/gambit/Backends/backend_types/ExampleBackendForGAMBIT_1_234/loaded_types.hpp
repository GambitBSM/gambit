#ifndef __loaded_types_ExampleBackendForGAMBIT_1_234_hpp__
#define __loaded_types_ExampleBackendForGAMBIT_1_234_hpp__ 1

#include "wrapper_ClassThree__double.hpp"
#include "wrapper_ClassThree__int.hpp"
#include "wrapper_ClassFour.hpp"
#include "wrapper_ClassFive__ClassFour.hpp"
#include "identification.hpp"

// Indicate which types are provided by this backend, and what the symbols of their factories are.
#define ExampleBackendForGAMBIT_1_234_all_data \
  (( /*class*/(ClassThree__double),    /*constructors*/(("Factory_ClassThree__double_0_double__BOSS_1",())) )) \
  (( /*class*/(ClassThree__int),    /*constructors*/(("Factory_ClassThree__int_0_int__BOSS_2",())) )) \
  (( /*class*/(ClassFour),    /*constructors*/(("Factory_ClassFour_0__BOSS_3",())) )) \
  (( /*class*/(ClassFive__ClassFour),    /*constructors*/(("Factory_ClassFive__ClassFour_0__BOSS_4",())) )) \

// If the default version has been loaded, set it as default.
#if ALREADY_LOADED(CAT_3(BACKENDNAME,_,CAT(Default_,BACKENDNAME)))
  SET_DEFAULT_VERSION_FOR_LOADING_TYPES(BACKENDNAME,SAFE_VERSION,CAT(Default_,BACKENDNAME))
  namespace Gambit
  {
    namespace ExampleBackendForGAMBIT_default
    {
      template <typename T> class ClassThree { };
      template <> class ClassThree<double>: public ClassThree__double { using ClassThree__double::ClassThree__double; };
      template <> class ClassThree<int>: public ClassThree__int { using ClassThree__int::ClassThree__int; };
      template <class T0> class ClassFive { };
      template <> class ClassFive<ClassFour>: public ClassFive__ClassFour { using ClassFive__ClassFour::ClassFive__ClassFour; };
    }
  }
#endif

namespace ExampleBackendForGAMBIT_1_234
{
  template <typename T> class ClassThree { };
  template <> class ClassThree<double>: public ClassThree__double { using ClassThree__double::ClassThree__double; };
  template <> class ClassThree<int>: public ClassThree__int { using ClassThree__int::ClassThree__int; };
  template <class T0> class ClassFive { };
  template <> class ClassFive<ClassFour>: public ClassFive__ClassFour { using ClassFive__ClassFour::ClassFive__ClassFour; };
}

// Undefine macros to avoid conflict with other backends.
#include "gambit/Backends/backend_undefs.hpp"

#endif /* __loaded_types_ExampleBackendForGAMBIT_1_234_hpp__ */
