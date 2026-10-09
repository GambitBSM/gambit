//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Hand-written shim for the Rivet backend, offered as an
///  alternative to the BOSS-generated frontend for
///  Rivet::AnalysisHandler.
///
///  PROTOTYPE / NOT WIRED INTO THE BUILD. This file demonstrates
///  the "thin C-linkage shim" alternative to BOSS discussed for
///  the Rivet backend. It is compiled directly against the real
///  Rivet/HepMC3 headers (ordinary C++, nothing special), and
///  exports a small, flat, unmangled API covering only the
///  AnalysisHandler methods GAMBIT's ColliderBit module actually
///  calls (see Backends/src/frontends/shims/README.md for the
///  method-by-method justification and for what is required to
///  turn this into a real build target).
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author The GAMBIT Collaboration
///  \date 2026 Oct
///
///  *********************************************

#include "Rivet/AnalysisHandler.hh"
#include "Rivet/Tools/RivetPaths.hh"
#include "HepMC3/GenEvent.h"

#include <cstdio>
#include <string>
#include <vector>

extern "C"
{

  // --- Lifetime ---

  void* rivet_handler_create()
  {
    return new Rivet::AnalysisHandler();
  }

  void rivet_handler_destroy(void* handle)
  {
    delete static_cast<Rivet::AnalysisHandler*>(handle);
  }

  // --- Analysis selection ---

  void rivet_handler_add_analysis(void* handle, const char* name)
  {
    static_cast<Rivet::AnalysisHandler*>(handle)->addAnalysis(name);
  }

  void rivet_handler_remove_analyses(void* handle, const char* const* names, int n)
  {
    std::vector<std::string> v(names, names + n);
    static_cast<Rivet::AnalysisHandler*>(handle)->removeAnalyses(v);
  }

  // Returning collections of strings across an extern "C" boundary needs an
  // explicit, caller-owned-buffer convention: there is no shared/static
  // temporary here, so this is safe to call concurrently from different
  // threads on different AnalysisHandler instances (as ColliderBit does, one
  // handler per OpenMP thread). See README.md for why that matters.

  int rivet_handler_num_analysis_names(void* handle)
  {
    return static_cast<int>(static_cast<Rivet::AnalysisHandler*>(handle)->analysisNames().size());
  }

  void rivet_handler_analysis_name(void* handle, int i, char* buf, int buflen)
  {
    const std::string& name = static_cast<Rivet::AnalysisHandler*>(handle)->analysisNames().at(i);
    std::snprintf(buf, buflen, "%s", name.c_str());
  }

  int rivet_handler_num_std_analysis_names(void* handle)
  {
    return static_cast<int>(static_cast<Rivet::AnalysisHandler*>(handle)->stdAnalysisNames().size());
  }

  void rivet_handler_std_analysis_name(void* handle, int i, char* buf, int buflen)
  {
    const std::string& name = static_cast<Rivet::AnalysisHandler*>(handle)->stdAnalysisNames().at(i);
    std::snprintf(buf, buflen, "%s", name.c_str());
  }

  // --- Run metadata ---

  void rivet_handler_beam_ids(void* handle, int* id1, int* id2)
  {
    std::pair<int,int> ids = static_cast<Rivet::AnalysisHandler*>(handle)->beamIds();
    *id1 = ids.first;
    *id2 = ids.second;
  }

  double rivet_handler_nominal_cross_section(void* handle)
  {
    return static_cast<Rivet::AnalysisHandler*>(handle)->nominalCrossSection();
  }

  double rivet_handler_sqrt_s(void* handle)
  {
    return static_cast<Rivet::AnalysisHandler*>(handle)->sqrtS();
  }

  void rivet_handler_run_name(void* handle, char* buf, int buflen)
  {
    std::snprintf(buf, buflen, "%s", static_cast<Rivet::AnalysisHandler*>(handle)->runName().c_str());
  }

  // --- Event processing ---

  // HepMC3::GenEvent crosses the boundary as a real C++ pointer, not a
  // flattened/opaque type: this is safe only because the shim and every
  // other GAMBIT frontend that produces/consumes HepMC3::GenEvent (e.g. the
  // Pythia frontend) are built against the same compiled HepMC3, with the
  // same compiler/ABI, which GAMBIT already requires for its contrib libs.
  void rivet_handler_analyze(void* handle, const HepMC3::GenEvent* ge)
  {
    static_cast<Rivet::AnalysisHandler*>(handle)->analyze(*ge);
  }

  // --- Finalisation / output ---

  void rivet_handler_finalize(void* handle)
  {
    static_cast<Rivet::AnalysisHandler*>(handle)->finalize();
  }

  void rivet_handler_write_data(void* handle, const char* filename)
  {
    static_cast<Rivet::AnalysisHandler*>(handle)->writeData(filename);
  }

  void rivet_handler_merge(void* dst_handle, void* src_handle)
  {
    static_cast<Rivet::AnalysisHandler*>(dst_handle)->merge(*static_cast<Rivet::AnalysisHandler*>(src_handle));
  }

  // --- Free functions ---

  void rivet_add_analysis_lib_path(const char* path)
  {
    Rivet::addAnalysisLibPath(path);
  }

} // extern "C"
