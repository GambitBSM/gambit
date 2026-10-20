//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  The interface between ColliderBit and an analysis handler in the style
///  of Rivet's, which runs a set of named measurement analyses over HepMC
///  events and writes the resulting analysis objects out in YODA format.
///
///  AnalysisHandler is implemented outside GAMBIT, in a plugin library
///  compiled against the analysis tool itself (see
///  Backends/src/frontends/plugins/rivet_plugin.cpp). GAMBIT loads the
///  plugin as a backend and obtains instances through the backend function
///  create_analysis_handler. Nothing in GAMBIT includes a Rivet header.
///
///  Rules for this header: it is compiled both by GAMBIT and by the plugins,
///  so it may only include the standard library. Any change to the class
///  must be accompanied by a bump of
///  COLLIDERBIT_ANALYSIS_HANDLER_INTERFACE_VERSION; the plugin reports the
///  version it was built with, and GAMBIT refuses a mismatch at startup.
///
///  Error handling: no exception may cross the plugin boundary. Methods
///  that can fail return false and leave a description in last_error().
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author The GAMBIT Collaboration
///  \date 2026 Oct
///
///  *********************************************

#pragma once

// The interface is only meaningful when HepMC is available (and no analysis
// plugin is built otherwise). The real HepMC3 header is included rather than
// a forward declaration, because GAMBIT's type harvester cannot cope with
// foreign namespaces in a type header.
#ifndef EXCLUDE_HEPMC

#include <ostream>
#include <string>
#include <vector>

#include "HepMC3/GenEvent.h"

/// Version of the AnalysisHandler interface; see the file comment.
#define COLLIDERBIT_ANALYSIS_HANDLER_INTERFACE_VERSION 1

namespace Gambit
{
  namespace ColliderBit
  {

    /// A handler running measurement analyses over HepMC events.
    class AnalysisHandler
    {
      public:

        virtual ~AnalysisHandler() {}

        /// Add an analysis by name (Rivet syntax, e.g. "ATLAS_2015_I1408516:LMODE=EL").
        virtual bool add_analysis(const std::string& name) = 0;

        /// Remove analyses by name.
        virtual bool remove_analyses(const std::vector<std::string>& names) = 0;

        /// Names of the analyses currently loaded.
        virtual std::vector<std::string> analysis_names() const = 0;

        /// Analyse one event. (Non-const because the analysis tool may annotate the event.)
        virtual bool analyze(HepMC3::GenEvent& event) = 0;

        /// Finalise all analyses.
        virtual bool finalize() = 0;

        /// Write the analysis objects to a file.
        virtual bool write_data(const std::string& filename) = 0;

        /// Write the analysis objects to a stream, in the given format (e.g. "yoda").
        virtual bool write_data(std::ostream& os, const std::string& format) = 0;

        /// Merge the analysis objects of another handler of the same kind into this one.
        virtual bool merge(AnalysisHandler& other) = 0;

        /// Description of the most recent failure.
        virtual std::string last_error() const = 0;
    };

  }
}

#endif // EXCLUDE_HEPMC
