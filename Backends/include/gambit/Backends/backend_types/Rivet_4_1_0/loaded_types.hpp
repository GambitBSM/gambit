#ifndef __loaded_types_Rivet_4_1_0_hpp__
#define __loaded_types_Rivet_4_1_0_hpp__ 1

#ifndef EXCLUDE_YODA
#ifndef EXCLUDE_HEPMC

#include "gambit/Utils/begin_ignore_warnings_rivet_backend.hpp"
#include "wrapper_AnalysisHandler.hh"
#include "identification.hpp"
#include "gambit/Utils/end_ignore_warnings.hpp"

// Indicate which types are provided by this backend, and what the symbols of their factories are.
#define Rivet_4_1_0_all_data \
  (( /*class*/(Rivet)(AnalysisHandler),    /*constructors*/((("Factory_AnalysisHandler_0__BOSS_1","_Factory_AnalysisHandler_0__BOSS_1"),())) )) \

// If the default version has been loaded, set it as default.
#if ALREADY_LOADED(CAT_3(BACKENDNAME,_,CAT(Default_,BACKENDNAME)))
  SET_DEFAULT_VERSION_FOR_LOADING_TYPES(BACKENDNAME,SAFE_VERSION,CAT(Default_,BACKENDNAME))
#endif

// Undefine macros to avoid conflict with other backends.
#include "gambit/Backends/backend_undefs.hpp"
 
#endif
#endif

#endif /* __loaded_types_Rivet_4_1_0_hpp__ */
