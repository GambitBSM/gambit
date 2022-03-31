#include "backend_types/ExampleBackend_1_234/forward_decls_abstract_classes.hpp"
#include "backend_types/ExampleBackend_1_234/identification.hpp"

template <typename T>
using Abstract_ClassThree = CAT_3(BACKENDNAME,_,SAFE_VERSION)::Abstract_ClassThree<T>;

typedef CAT_3(BACKENDNAME,_,SAFE_VERSION)::Abstract_ClassFour Abstract_ClassFour;

template <typename T1>
using Abstract_ClassFive = CAT_3(BACKENDNAME,_,SAFE_VERSION)::Abstract_ClassFive<T1>;

#include "gambit/Backends/backend_undefs.hpp"
