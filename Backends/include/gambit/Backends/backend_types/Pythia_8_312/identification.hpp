// Identify backend and set macro flags

#include "gambit/Utils/cats.hpp"

#define BACKENDNAME Pythia
#define BACKENDLANG CXX
#define VERSION 8.312
#define SAFE_VERSION 8_312
#define REFERENCE Bierlich:2022pfr

// Flipped from 1 to 0: Pythia_8_312.hpp is now a hand-written frontend
// backed by a flat extern "C" shim (Backends/src/frontends/shims/pythia_shim.cpp),
// not BOSS-generated classloading. See Backends/src/frontends/shims/README.md.
#undef DO_CLASSLOADING
#define DO_CLASSLOADING 0
