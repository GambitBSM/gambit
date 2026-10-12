#ifndef __loaded_types_Rivet_4_1_0_hpp__
#define __loaded_types_Rivet_4_1_0_hpp__ 1

#ifndef EXCLUDE_YODA
#ifndef EXCLUDE_HEPMC

///  Rivet's frontend is hand-written (see
///  Backends/src/frontends/shims/README.md) rather than BOSS-generated, so
///  there is no wrapper_AnalysisHandler.hh to include here.
///
///  This file -- not Backends/include/gambit/Backends/frontends/Rivet_4_1_0.hpp
///  -- is the single source of truth for the actual AnalysisHandler class
///  *definition*, for exactly the same reason this split exists for Pythia
///  (see backend_types/Pythia_8_312/loaded_types.hpp's header comment):
///  this file is reached both via backend_rollcall.hpp (a "module compile
///  unit" context with frontend_macros.hpp's BE_FUNCTION/LOAD_LIBRARY
///  machinery already active) and, directly, via backend_types_rollcall.hpp
///  from contexts (e.g. ColliderBit_measurements.cpp's `using namespace
///  Rivet_default::Rivet;`) that must not see that machinery a second,
///  unwanted time.
///
///  AnalysisHandler's methods call the shim's exported functions through
///  plain "extern" redeclarations of the exact same
///  Gambit::Backends::Rivet_4_1_0 function-pointer variables that
///  frontends/Rivet_4_1_0.hpp's BE_FUNCTION lines declare (and that
///  BackendIniBit's LOAD_LIBRARY-driven dlopen/dlsym code actually
///  populates at runtime) -- re-declaring an extern variable with an
///  identical type is always legal in C++, so this requires no macro
///  machinery at all.

#include "gambit/Utils/begin_ignore_warnings_rivet_backend.hpp"
#include "HepMC3/GenEvent.h"
#include "gambit/Utils/end_ignore_warnings.hpp"

#include <ostream>
#include <string>
#include <utility>
#include <vector>

namespace Gambit
{
  namespace Backends
  {
    namespace Rivet_4_1_0
    {
      typedef void* (*rivet_handler_create_type)();                                                  extern const rivet_handler_create_type rivet_handler_create;
      typedef void  (*rivet_handler_destroy_type)(void*);                                             extern const rivet_handler_destroy_type rivet_handler_destroy;
      typedef void  (*rivet_handler_add_analysis_type)(void*, const char*);                           extern const rivet_handler_add_analysis_type rivet_handler_add_analysis;
      typedef void  (*rivet_handler_remove_analyses_type)(void*, const char* const*, int);            extern const rivet_handler_remove_analyses_type rivet_handler_remove_analyses;
      typedef int   (*rivet_handler_num_analysis_names_type)(void*);                                  extern const rivet_handler_num_analysis_names_type rivet_handler_num_analysis_names;
      typedef void  (*rivet_handler_analysis_name_type)(void*, int, char*, int);                      extern const rivet_handler_analysis_name_type rivet_handler_analysis_name;
      typedef int   (*rivet_handler_num_std_analysis_names_type)(void*);                              extern const rivet_handler_num_std_analysis_names_type rivet_handler_num_std_analysis_names;
      typedef void  (*rivet_handler_std_analysis_name_type)(void*, int, char*, int);                  extern const rivet_handler_std_analysis_name_type rivet_handler_std_analysis_name;
      typedef double(*rivet_handler_nominal_cross_section_type)(void*);                               extern const rivet_handler_nominal_cross_section_type rivet_handler_nominal_cross_section;
      typedef void  (*rivet_handler_analyze_type)(void*, HepMC3::GenEvent*);                          extern const rivet_handler_analyze_type rivet_handler_analyze;
      typedef void  (*rivet_handler_finalize_type)(void*);                                            extern const rivet_handler_finalize_type rivet_handler_finalize;
      typedef void  (*rivet_handler_write_data_type)(void*, const char*);                             extern const rivet_handler_write_data_type rivet_handler_write_data;
      typedef int   (*rivet_handler_write_data_stream_type)(void*, const char*, char*, int);          extern const rivet_handler_write_data_stream_type rivet_handler_write_data_stream;
      typedef void  (*rivet_handler_merge_type)(void*, void*);                                        extern const rivet_handler_merge_type rivet_handler_merge;
      typedef void  (*rivet_add_analysis_lib_path_type)(const char*);                                 extern const rivet_add_analysis_lib_path_type rivet_add_analysis_lib_path;
    }
  }
}

// Lives in the bare Rivet_4_1_0::Rivet namespace (not nested under
// Gambit::Backends) to match the convention BOSS-generated frontends use
// and that ColliderBit_measurements.cpp's `using namespace
// Rivet_default::Rivet;` expects.
namespace Rivet_4_1_0
{
  namespace Rivet
  {
        /// GAMBIT-side stand-in for Rivet::AnalysisHandler, backed by the
        /// rivet_handler_* functions above instead of a BOSS-generated
        /// wrapper/abstract class pair. Exposes exactly the methods
        /// ColliderBit_measurements.cpp calls.
        class AnalysisHandler
        {
          public:
            AnalysisHandler() : handle_(Gambit::Backends::Rivet_4_1_0::rivet_handler_create()) {}

            ~AnalysisHandler()
            {
              Gambit::Backends::Rivet_4_1_0::rivet_handler_destroy(handle_);
            }

            AnalysisHandler(const AnalysisHandler&) = delete;
            AnalysisHandler& operator=(const AnalysisHandler&) = delete;

            void addAnalysis(const std::string& name)
            {
              Gambit::Backends::Rivet_4_1_0::rivet_handler_add_analysis(handle_, name.c_str());
            }

            void removeAnalyses(const std::vector<std::string>& names)
            {
              std::vector<const char*> c;
              c.reserve(names.size());
              for (const auto& n : names) c.push_back(n.c_str());
              Gambit::Backends::Rivet_4_1_0::rivet_handler_remove_analyses(handle_, c.data(), static_cast<int>(c.size()));
            }

            std::vector<std::string> analysisNames() const
            {
              return collectNames(Gambit::Backends::Rivet_4_1_0::rivet_handler_num_analysis_names,
                                   Gambit::Backends::Rivet_4_1_0::rivet_handler_analysis_name);
            }

            std::vector<std::string> stdAnalysisNames() const
            {
              return collectNames(Gambit::Backends::Rivet_4_1_0::rivet_handler_num_std_analysis_names,
                                   Gambit::Backends::Rivet_4_1_0::rivet_handler_std_analysis_name);
            }

            // Note: no beamIds()/sqrtS()/runName() -- see the BE_FUNCTION
            // block in frontends/Rivet_4_1_0.hpp for why.

            double nominalCrossSection() const
            {
              return Gambit::Backends::Rivet_4_1_0::rivet_handler_nominal_cross_section(handle_);
            }

            void analyze(HepMC3::GenEvent& ge)
            {
              Gambit::Backends::Rivet_4_1_0::rivet_handler_analyze(handle_, &ge);
            }

            void finalize()
            {
              Gambit::Backends::Rivet_4_1_0::rivet_handler_finalize(handle_);
            }

            void writeData(const std::string& filename)
            {
              Gambit::Backends::Rivet_4_1_0::rivet_handler_write_data(handle_, filename.c_str());
            }

            /// Stream-based overload, used by ColliderBit_measurements.cpp
            /// to collect YODA output into an in-memory ostringstream
            /// instead of a file. Grow-and-retry on the shim's reported
            /// true length, same pattern as Pythia's Event::list() -- see
            /// Backends/src/frontends/shims/README.md.
            void writeData(std::ostream& os, const std::string& fmt) const
            {
              std::vector<char> buf(65536);
              int n = Gambit::Backends::Rivet_4_1_0::rivet_handler_write_data_stream(handle_, fmt.c_str(), buf.data(), static_cast<int>(buf.size()));
              if (n >= static_cast<int>(buf.size()))
              {
                buf.resize(n + 1);
                Gambit::Backends::Rivet_4_1_0::rivet_handler_write_data_stream(handle_, fmt.c_str(), buf.data(), static_cast<int>(buf.size()));
              }
              os << buf.data();
            }

            void merge(AnalysisHandler& other)
            {
              Gambit::Backends::Rivet_4_1_0::rivet_handler_merge(handle_, other.handle_);
            }

          private:
            template <typename CountFn, typename GetFn>
            std::vector<std::string> collectNames(CountFn count_fn, GetFn get_fn) const
            {
              int n = count_fn(handle_);
              std::vector<std::string> out;
              out.reserve(n);
              char buf[256];
              for (int i = 0; i < n; ++i)
              {
                get_fn(handle_, i, buf, sizeof(buf));
                out.emplace_back(buf);
              }
              return out;
            }

            void* handle_;
        };
  }
}

#include "identification.hpp"

// Indicate which types are provided by this backend, so that
// SET_DEFAULT_VERSION_FOR_LOADING_TYPES below can typedef
// Rivet_default::Rivet::AnalysisHandler = Rivet_4_1_0::Rivet::AnalysisHandler.
// The "constructors" part of this BOSS-style entry is unused for a
// hand-written frontend (there's no classloading factory dispatch to
// register), so it's left as an empty placeholder.
#define Rivet_4_1_0_all_data \
  (( /*class*/(Rivet)(AnalysisHandler), /*constructors*/((("",""),())) )) \

// If the default version has been loaded, set it as default.
#if ALREADY_LOADED(CAT_3(BACKENDNAME,_,CAT(Default_,BACKENDNAME)))
  SET_DEFAULT_VERSION_FOR_LOADING_TYPES(BACKENDNAME,SAFE_VERSION,CAT(Default_,BACKENDNAME))
#endif

// Undefine macros to avoid conflict with other backends.
#include "gambit/Backends/backend_undefs.hpp"

#endif
#endif

#endif /* __loaded_types_Rivet_4_1_0_hpp__ */
