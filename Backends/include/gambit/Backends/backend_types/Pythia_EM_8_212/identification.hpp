// Identify backend and set macro flags

#include "gambit/Utils/cats.hpp"

#define BACKENDNAME Pythia_EM
#define BACKENDLANG CXX
#define VERSION 8.212
#define SAFE_VERSION 8_212

#undef DO_CLASSLOADING
#define DO_CLASSLOADING 1
