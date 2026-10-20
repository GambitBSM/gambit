// Identify backend and set macro flags

#include "gambit/Utils/cats.hpp"

#define BACKENDNAME Pythia
#define BACKENDLANG CXX
#define VERSION 8.312
#define SAFE_VERSION 8_312
#define REFERENCE Bierlich:2022pfr

// This frontend talks to a plugin library implementing a ColliderBit
// interface rather than to BOSS-generated wrappers, so it does not use
// BOSS classloading. See Backends/src/frontends/plugins/README.md.
#undef DO_CLASSLOADING
#define DO_CLASSLOADING 0
