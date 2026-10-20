//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Rivet implementation of ColliderBit's AnalysisHandler interface.
///
///  This file is compiled against Rivet, as a step of the Rivet backend
///  build (cmake/backends.cmake), into librivet_plugin.so, which GAMBIT
///  loads as the Rivet backend. GAMBIT itself never sees a Rivet header: it
///  talks to Rivet only through the abstract interface in
///  ColliderBit/include/gambit/ColliderBit/AnalysisHandler.hpp, and uses
///  the functions exported here:
///
///    int gambit_analysis_handler_interface_version();
///    Gambit::ColliderBit::AnalysisHandler* gambit_create_analysis_handler();
///    int gambit_add_analysis_lib_path(const char* path);
///
///  No exception leaves this library. GAMBIT's Rivet patch turns Rivet's
///  exit() calls into exceptions precisely so that a failing analysis can
///  be reported instead of ending the scan; those exceptions are caught
///  here and reported through the false return and last_error().
///
///  See Backends/src/frontends/plugins/README.md.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author The GAMBIT Collaboration
///  \date 2026 Oct
///
///  *********************************************

#include "gambit/ColliderBit/AnalysisHandler.hpp"

#include "Rivet/AnalysisHandler.hh"
#include "Rivet/Tools/RivetPaths.hh"
#include "HepMC3/GenEvent.h"

#include <exception>
#include <ostream>
#include <string>
#include <vector>

#define GAMBIT_PLUGIN_EXPORT __attribute__((visibility("default")))

namespace
{

  /// Rivet's AnalysisHandler as a ColliderBit analysis handler.
  class RivetAnalysisHandler : public Gambit::ColliderBit::AnalysisHandler
  {
    public:

      bool add_analysis(const std::string& name) override
      {
        return guarded([&]{ handler_.addAnalysis(name); });
      }

      bool remove_analyses(const std::vector<std::string>& names) override
      {
        return guarded([&]{ handler_.removeAnalyses(names); });
      }

      std::vector<std::string> analysis_names() const override
      {
        std::vector<std::string> names;
        guarded([&]{ names = handler_.analysisNames(); });
        return names;
      }

      bool analyze(HepMC3::GenEvent& event) override
      {
        return guarded([&]{ handler_.analyze(event); });
      }

      bool finalize() override
      {
        return guarded([&]{ handler_.finalize(); });
      }

      bool write_data(const std::string& filename) override
      {
        return guarded([&]{ handler_.writeData(filename); });
      }

      bool write_data(std::ostream& os, const std::string& format) override
      {
        return guarded([&]{ handler_.writeData(os, format); });
      }

      bool merge(Gambit::ColliderBit::AnalysisHandler& other) override
      {
        RivetAnalysisHandler* other_rivet = dynamic_cast<RivetAnalysisHandler*>(&other);
        if (other_rivet == nullptr)
        {
          last_error_ = "Cannot merge: the other analysis handler is not a Rivet analysis handler.";
          return false;
        }
        return guarded([&]{ handler_.merge(other_rivet->handler_); });
      }

      std::string last_error() const override { return last_error_; }

    private:

      /// Run f, converting any exception into a false return plus a stored message.
      template <typename F>
      bool guarded(F&& f) const noexcept
      {
        try
        {
          f();
          return true;
        }
        catch (const std::exception& e) { last_error_ = e.what(); }
        catch (...) { last_error_ = "non-standard exception"; }
        return false;
      }

      Rivet::AnalysisHandler handler_;
      mutable std::string last_error_;
  };

}

extern "C"
{

  GAMBIT_PLUGIN_EXPORT int gambit_analysis_handler_interface_version()
  {
    return COLLIDERBIT_ANALYSIS_HANDLER_INTERFACE_VERSION;
  }

  GAMBIT_PLUGIN_EXPORT Gambit::ColliderBit::AnalysisHandler* gambit_create_analysis_handler()
  {
    try { return new RivetAnalysisHandler(); }
    catch (...) { return nullptr; }
  }

  /// Add a directory to Rivet's search path for analysis plugins. Returns 0 on success.
  GAMBIT_PLUGIN_EXPORT int gambit_add_analysis_lib_path(const char* path)
  {
    try
    {
      Rivet::addAnalysisLibPath(std::string(path));
      return 0;
    }
    catch (...) { return -1; }
  }

}
