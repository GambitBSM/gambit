// Identify backend and set macro flags

#include "gambit/Utils/cats.hpp"

#define BACKENDNAME __BACKEND_NAME__
#define BACKENDLANG CXX
#define VERSION __BACKEND_VERSION__
#define SAFE_VERSION __BACKEND_SAFE_VERSION__
#define REFERENCE __BACKEND_REFERENCE__

#undef DO_CLASSLOADING
#define DO_CLASSLOADING 1
