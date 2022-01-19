#include "backend_types/ExampleBackend_1_234/forward_decls_wrapper_classes.hpp"
#include "backend_types/ExampleBackend_1_234/identification.hpp"

typedef CAT_3(BACKENDNAME,_,SAFE_VERSION)::Node Wrapper_Node;

typedef CAT_3(BACKENDNAME,_,SAFE_VERSION)::ClassOne Wrapper_ClassOne;

namespace SomeNamespace
{
  typedef CAT_3(BACKENDNAME,_,SAFE_VERSION)::SomeNamespace::ClassTwo Wrapper_ClassTwo;
}

#include "gambit/Backends/backend_undefs.hpp"
