// Identify backend and set macro flags

#include "gambit/Utils/cats.hpp"

#define BACKENDNAME Rivet
#define BACKENDLANG CXX
#define VERSION 4.1.0
#define SAFE_VERSION 4_1_0
#define REFERENCE Bierlich:2019rhm

// Classloading is BOSS's mechanism for dlsym-ing factory functions that
// construct wrapper objects with virtual dispatch back into the backend's
// own .so. The hand-written shim frontend doesn't use it: AnalysisHandler
// is a plain GAMBIT-side class whose methods call flat BE_FUNCTION-resolved
// symbols directly, so no factories need to be loaded.
#undef DO_CLASSLOADING
#define DO_CLASSLOADING 0
