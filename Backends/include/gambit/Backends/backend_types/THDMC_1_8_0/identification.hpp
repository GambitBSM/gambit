// Identify backend and set macro flags

#include "gambit/Utils/cats.hpp"

#define BACKENDNAME THDMC
#define BACKENDLANG CXX
#define VERSION 1.8.0
#define SAFE_VERSION 1_8_0

#undef DO_CLASSLOADING
#define DO_CLASSLOADING 1
