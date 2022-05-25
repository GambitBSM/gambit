// Identify backend and set macro flags

#include "gambit/Utils/cats.hpp"

#define BACKENDNAME HepLike
#define BACKENDLANG CXX
#define VERSION 1.2
#define SAFE_VERSION 1_2

#undef DO_CLASSLOADING
#define DO_CLASSLOADING 1
