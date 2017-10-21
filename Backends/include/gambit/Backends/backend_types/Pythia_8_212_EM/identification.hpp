// Identify backend and set macro flags

#include "gambit/Utils/cats.hpp"

#define BACKENDNAME Pythia
#define BACKENDLANG CXX
#define VERSION 8.212.EM
#define SAFE_VERSION 8_212_EM

#undef DO_CLASSLOADING
#define DO_CLASSLOADING 1
