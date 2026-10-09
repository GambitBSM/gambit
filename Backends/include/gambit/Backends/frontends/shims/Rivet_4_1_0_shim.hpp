//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Hand-written frontend header for the Rivet shim
///  (Backends/src/frontends/shims/rivet_shim.cpp).
///
///  PROTOTYPE / NOT WIRED INTO THE BUILD. This header plays the
///  role that a BOSS-generated frontend header
///  (Backends/include/gambit/Backends/frontends/Rivet_4_1_0.hpp)
///  plays today: it gives GAMBIT module code a C++ class that
///  looks like Rivet::AnalysisHandler, backed here by dlsym'd
///  calls into librivet_shim.so instead of BOSS-generated
///  wrapper/abstract classes.
///
///  The class below exposes exactly the methods that
///  ColliderBit_measurements.cpp calls today (constructor,
///  addAnalysis, removeAnalyses, analysisNames, stdAnalysisNames,
///  beamIds, nominalCrossSection, sqrtS, runName, analyze,
///  finalize, writeData, merge) plus the free function
///  addAnalysisLibPath, so that call site would not need to
///  change if this were ever swapped in for real. See
///  Backends/src/frontends/shims/README.md for what is
///  deliberately left out here (the real GAMBIT backend-loading
///  machinery, LOAD_LIBRARY/BE_FUNCTION integration, functor
///  plumbing) because it depends on build details this prototype
///  does not attempt to exercise.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author The GAMBIT Collaboration
///  \date 2026 Oct
///
///  *********************************************

#ifndef __RIVET_4_1_0_SHIM_HPP__
#define __RIVET_4_1_0_SHIM_HPP__

#include <dlfcn.h>

#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "HepMC3/GenEvent.h"

namespace Gambit
{
  namespace Backends
  {
    namespace Rivet_4_1_0_shim
    {

      /// Minimal dlopen/dlsym loader for the shim library.
      ///
      /// A real integration would reuse GAMBIT's existing
      /// LOAD_LIBRARY/BE_FUNCTION machinery (which already resolves
      /// backend paths and dlsyms arbitrary symbol names) instead of
      /// this hand-rolled loader; it is written out explicitly here so
      /// this file can be read and reasoned about on its own.
      class ShimLibrary
      {
        public:
          static ShimLibrary& instance()
          {
            static ShimLibrary lib;
            return lib;
          }

          template <typename FuncPtr>
          FuncPtr symbol(const char* name)
          {
            void* sym = dlsym(handle_, name);
            if (!sym)
            {
              throw std::runtime_error(std::string("Rivet shim: could not resolve symbol '") + name + "': " + dlerror());
            }
            return reinterpret_cast<FuncPtr>(sym);
          }

        private:
          ShimLibrary()
          {
            // Path left unresolved deliberately -- in a real integration this
            // would come from the same backend-location config GAMBIT already
            // uses to find e.g. librivet.so.
            handle_ = dlopen("librivet_shim.so", RTLD_NOW | RTLD_GLOBAL);
            if (!handle_)
            {
              throw std::runtime_error(std::string("Rivet shim: could not load librivet_shim.so: ") + dlerror());
            }
          }

          ~ShimLibrary()
          {
            if (handle_) dlclose(handle_);
          }

          void* handle_;
      };

      // Function pointer typedefs matching rivet_shim.cpp's extern "C" API.
      using create_t              = void* (*)();
      using destroy_t             = void  (*)(void*);
      using add_analysis_t        = void  (*)(void*, const char*);
      using remove_analyses_t     = void  (*)(void*, const char* const*, int);
      using num_names_t           = int   (*)(void*);
      using get_name_t            = void  (*)(void*, int, char*, int);
      using beam_ids_t            = void  (*)(void*, int*, int*);
      using nominal_xs_t          = double(*)(void*);
      using sqrt_s_t              = double(*)(void*);
      using run_name_t            = void  (*)(void*, char*, int);
      using analyze_t             = void  (*)(void*, const HepMC3::GenEvent*);
      using finalize_t            = void  (*)(void*);
      using write_data_t          = void  (*)(void*, const char*);
      using merge_t                = void (*)(void*, void*);
      using add_analysis_lib_path_t = void (*)(const char*);

      /// GAMBIT-side stand-in for Rivet::AnalysisHandler, backed by the shim.
      ///
      /// Deliberately presents the same method names/signatures that
      /// ColliderBit_measurements.cpp already calls on the BOSS-generated
      /// wrapper type, so no module-side code would need to change.
      class AnalysisHandler
      {
        public:
          AnalysisHandler()
            : handle_(ShimLibrary::instance().symbol<create_t>("rivet_handler_create")())
          {}

          ~AnalysisHandler()
          {
            ShimLibrary::instance().symbol<destroy_t>("rivet_handler_destroy")(handle_);
          }

          AnalysisHandler(const AnalysisHandler&) = delete;
          AnalysisHandler& operator=(const AnalysisHandler&) = delete;

          void addAnalysis(const std::string& name)
          {
            ShimLibrary::instance().symbol<add_analysis_t>("rivet_handler_add_analysis")(handle_, name.c_str());
          }

          void removeAnalyses(const std::vector<std::string>& names)
          {
            std::vector<const char*> c;
            c.reserve(names.size());
            for (const auto& n : names) c.push_back(n.c_str());
            ShimLibrary::instance().symbol<remove_analyses_t>("rivet_handler_remove_analyses")(handle_, c.data(), static_cast<int>(c.size()));
          }

          std::vector<std::string> analysisNames() const
          {
            return collectNames("rivet_handler_num_analysis_names", "rivet_handler_analysis_name");
          }

          std::vector<std::string> stdAnalysisNames() const
          {
            return collectNames("rivet_handler_num_std_analysis_names", "rivet_handler_std_analysis_name");
          }

          std::pair<int,int> beamIds() const
          {
            int a = 0, b = 0;
            ShimLibrary::instance().symbol<beam_ids_t>("rivet_handler_beam_ids")(handle_, &a, &b);
            return {a, b};
          }

          double nominalCrossSection() const
          {
            return ShimLibrary::instance().symbol<nominal_xs_t>("rivet_handler_nominal_cross_section")(handle_);
          }

          double sqrtS() const
          {
            return ShimLibrary::instance().symbol<sqrt_s_t>("rivet_handler_sqrt_s")(handle_);
          }

          std::string runName() const
          {
            char buf[256];
            ShimLibrary::instance().symbol<run_name_t>("rivet_handler_run_name")(handle_, buf, sizeof(buf));
            return std::string(buf);
          }

          void analyze(const HepMC3::GenEvent& ge)
          {
            ShimLibrary::instance().symbol<analyze_t>("rivet_handler_analyze")(handle_, &ge);
          }

          void finalize()
          {
            ShimLibrary::instance().symbol<finalize_t>("rivet_handler_finalize")(handle_);
          }

          void writeData(const std::string& filename)
          {
            ShimLibrary::instance().symbol<write_data_t>("rivet_handler_write_data")(handle_, filename.c_str());
          }

          void merge(AnalysisHandler& other)
          {
            ShimLibrary::instance().symbol<merge_t>("rivet_handler_merge")(handle_, other.handle_);
          }

        private:
          std::vector<std::string> collectNames(const char* count_symbol, const char* get_symbol) const
          {
            int n = ShimLibrary::instance().symbol<num_names_t>(count_symbol)(handle_);
            auto get = ShimLibrary::instance().symbol<get_name_t>(get_symbol);
            std::vector<std::string> out;
            out.reserve(n);
            char buf[256];
            for (int i = 0; i < n; ++i)
            {
              get(handle_, i, buf, sizeof(buf));
              out.emplace_back(buf);
            }
            return out;
          }

          void* handle_;
      };

      inline void addAnalysisLibPath(const std::string& path)
      {
        ShimLibrary::instance().symbol<add_analysis_lib_path_t>("rivet_add_analysis_lib_path")(path.c_str());
      }

    } // namespace Rivet_4_1_0_shim
  } // namespace Backends
} // namespace Gambit

#endif // __RIVET_4_1_0_SHIM_HPP__
