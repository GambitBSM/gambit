// Identify backend and set macro flags

#include "gambit/Utils/cats.hpp"

#define BACKENDNAME Rivet
#define BACKENDLANG CXX
#define VERSION 4.1.0
#define SAFE_VERSION 4_1_0
#define REFERENCE Bierlich:2019rhm

// This frontend talks to a plugin library implementing a ColliderBit
// interface rather than to BOSS-generated wrappers, so it does not use
// BOSS classloading. See Backends/src/frontends/plugins/README.md.
#undef DO_CLASSLOADING
#define DO_CLASSLOADING 0
