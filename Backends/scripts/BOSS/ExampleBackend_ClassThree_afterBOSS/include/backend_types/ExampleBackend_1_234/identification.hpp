// Identify backend and set macro flags

#include "gambit/Utils/cats.hpp"

#define BACKENDNAME ExampleBackend
#define BACKENDLANG CXX
#define VERSION 1.234
#define SAFE_VERSION 1_234
#define REFERENCE 

#undef DO_CLASSLOADING
#define DO_CLASSLOADING 1
