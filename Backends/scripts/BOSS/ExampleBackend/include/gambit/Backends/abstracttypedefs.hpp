#include "backend_types/ExampleBackend_1_234/forward_decls_abstract_classes.hpp"
#include "backend_types/ExampleBackend_1_234/identification.hpp"

typedef CAT_3(BACKENDNAME,_,SAFE_VERSION)::Abstract_Node Abstract_Node;

typedef CAT_3(BACKENDNAME,_,SAFE_VERSION)::Abstract_ClassOne Abstract_ClassOne;

namespace SomeNamespace
{
  typedef CAT_3(BACKENDNAME,_,SAFE_VERSION)::SomeNamespace::Abstract_ClassTwo Abstract_ClassTwo;
}

#include "gambit/Backends/backend_undefs.hpp"
