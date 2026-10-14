//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Hand-written shim for the Rivet backend, offered as an alternative to
///  the BOSS-generated frontend for Rivet::AnalysisHandler.
///
///  Compiled directly against the real Rivet/HepMC3 headers by an
///  ExternalProject_Add_Step in cmake/backends.cmake, into
///  librivet_shim.so, exporting a small, flat, unmangled API covering
///  only the AnalysisHandler methods ColliderBit actually calls -- see
///  Backends/src/frontends/shims/README.md for the method-by-method
///  justification.
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
#include <sstream>
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

  // Caller-owned-buffer convention for returning collections of strings
  // across the extern "C" boundary: safe for concurrent calls on different
  // AnalysisHandler instances (one per OpenMP thread). See README.md.

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

  // Note: no beamIds()/sqrtS()/runName() -- these were only called from dead
  // code (guarded by a never-defined COLLIDERBIT_DEBUG) in
  // ColliderBit_measurements.cpp; see README.md.

  double rivet_handler_nominal_cross_section(void* handle)
  {
    return static_cast<Rivet::AnalysisHandler*>(handle)->nominalCrossSection();
  }

  // --- Event processing ---

  // HepMC3::GenEvent crosses as a real C++ pointer, not a flattened type:
  // safe because every frontend that touches it is built against the same
  // compiled HepMC3. Takes non-const GenEvent& since Rivet mutates it.
  void rivet_handler_analyze(void* handle, HepMC3::GenEvent* ge)
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

  // Stream-based overload (writeData(ostream&, fmt)), used to collect YODA
  // output into an in-memory ostringstream. Caller-owned-buffer convention
  // like pythia_event_list(): returns the true length via snprintf, so the
  // caller can grow and retry.
  int rivet_handler_write_data_stream(void* handle, const char* fmt, char* buf, int buflen)
  {
    std::ostringstream ss;
    static_cast<Rivet::AnalysisHandler*>(handle)->writeData(ss, fmt);
    const std::string& s = ss.str();
    return std::snprintf(buf, buflen, "%s", s.c_str());
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
