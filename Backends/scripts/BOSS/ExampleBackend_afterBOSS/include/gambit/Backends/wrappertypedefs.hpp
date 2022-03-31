#include "backend_types/ExampleBackend_1_234/forward_decls_wrapper_classes.hpp"
#include "backend_types/ExampleBackend_1_234/identification.hpp"

template <typename T>
using Wrapper_ClassThree = CAT_3(BACKENDNAME,_,SAFE_VERSION)::ClassThree<T>;

typedef CAT_3(BACKENDNAME,_,SAFE_VERSION)::ClassFour Wrapper_ClassFour;

template <typename T1>
using Wrapper_ClassFive = CAT_3(BACKENDNAME,_,SAFE_VERSION)::ClassFive<T1>;

#include "gambit/Backends/backend_undefs.hpp"
