#include "backend_types/ExampleBackend_1_234/forward_decls_wrapper_classes.hpp"
#include "backend_types/ExampleBackend_1_234/identification.hpp"

template <typename T>
using Wrapper_ClassThree = CAT_3(BACKENDNAME,_,SAFE_VERSION)::ClassThree<T>;

#include "gambit/Backends/backend_undefs.hpp"
