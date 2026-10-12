//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Hand-written shim for the Pythia backend, offered as an
///  alternative to the BOSS-generated frontend for
///  Pythia8::Pythia and the handful of other Pythia8 types GAMBIT's
///  ColliderBit module touches directly.
///
///  PROTOTYPE / NOT WIRED INTO THE BUILD. See
///  Backends/src/frontends/shims/README.md ("Pythia shim") for the
///  method-by-method justification, for why this backend's shape is
///  substantially different from the Rivet shim it is modelled on, and
///  for what is required to turn this into a real build target.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author The GAMBIT Collaboration
///  \date 2026 Oct
///
///  *********************************************

#include "Pythia8/Pythia.h"
#include "Pythia8/GAMBIT_hepmc_writer.h"
#include "HepMC3/GenEvent.h"
#include "SLHAea/slhaea.h"

#include <cstdio>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

extern "C"
{

  // =====================================================================
  // Pythia (Pythia8::Pythia)
  // =====================================================================

  // --- Lifetime ---
  //
  // Two real constructors are used at Py8Collider.hpp call sites: one that
  // reads an xmldoc path (used for the first, "base" instance per thread),
  // and one that shares an existing Settings/ParticleData pair (used to
  // build the actual working instance from that base, so that re-reading
  // settings doesn't re-read Pythia's whole xmldoc tree every event-loop
  // reinitialisation). Both must be kept.

  void* pythia_create(const char* xml_dir, int print_banner)
  {
    return new Pythia8::Pythia(std::string(xml_dir), print_banner != 0);
  }

  void* pythia_create_from_base(void* settings_handle, void* particle_data_handle, int print_banner)
  {
    return new Pythia8::Pythia(*static_cast<Pythia8::Settings*>(settings_handle),
                                *static_cast<Pythia8::ParticleData*>(particle_data_handle),
                                print_banner != 0);
  }

  void pythia_destroy(void* handle)
  {
    delete static_cast<Pythia8::Pythia*>(handle);
  }

  // --- Settings / configuration ---

  int pythia_read_string(void* handle, const char* command)
  {
    return static_cast<Pythia8::Pythia*>(handle)->readString(command) ? 1 : 0;
  }

  int pythia_init(void* handle)
  {
    return static_cast<Pythia8::Pythia*>(handle)->init() ? 1 : 0;
  }

  int pythia_next(void* handle)
  {
    return static_cast<Pythia8::Pythia*>(handle)->next() ? 1 : 0;
  }

  double pythia_get_sigma_max_sum(void* handle)
  {
    return static_cast<Pythia8::Pythia*>(handle)->getSigmaMaxSum();
  }

  // --- Access to public data members ---
  //
  // Pythia8::Pythia::settings/particleData/event/info/slhaInterface are
  // plain public data members on the real class, not methods -- GAMBIT
  // module code (Py8Collider.hpp) reads them directly
  // (`_pythiaBase->settings`, `_pythiaInstance->event`, etc.), so the shim
  // must expose them too. settings/particleData are passed straight back
  // into pythia_create_from_base() and are never otherwise dereferenced
  // anywhere in GAMBIT -- see README.md -- so they only need to cross the
  // boundary as opaque, non-owning pointers (lifetime tied to the owning
  // Pythia instance; never deleted here).

  void* pythia_get_settings(void* handle)
  {
    return &static_cast<Pythia8::Pythia*>(handle)->settings;
  }

  void* pythia_get_particle_data(void* handle)
  {
    return &static_cast<Pythia8::Pythia*>(handle)->particleData;
  }

  // Non-owning pointer to Pythia's own internal Event. Used only as the
  // source of a value-copy into a separately-owned Event (see
  // pythia_event_assign below) -- mirrors `event = _pythiaInstance->event;`
  // in Py8Collider.hpp::nextEvent().
  void* pythia_get_event(void* handle)
  {
    return &static_cast<Pythia8::Pythia*>(handle)->event;
  }

  // Non-owning pointer to Pythia's own internal (const) Info.
  void* pythia_get_info(void* handle)
  {
    return const_cast<Pythia8::Info*>(&static_cast<Pythia8::Pythia*>(handle)->info);
  }

  // Non-owning pointer to Pythia's own internal SusyLesHouches object,
  // reached through slhaInterface.slha -- this is two layers of public
  // data member on the real class (Pythia::slhaInterface, then
  // SLHAinterface::slha), collapsed into a single accessor here rather
  // than giving SLHAinterface its own handle type, since nothing in
  // GAMBIT ever touches SLHAinterface for any other reason.
  void* pythia_get_slha(void* handle)
  {
    return &static_cast<Pythia8::Pythia*>(handle)->slhaInterface.slha;
  }

  // =====================================================================
  // SusyLesHouches (reached only via Pythia::slhaInterface.slha)
  // =====================================================================

  // SLHAea::Coll crosses as a real C++ pointer, exactly like HepMC3::GenEvent
  // does in the Rivet shim: GAMBIT's own SLHAea contrib library is compiled
  // once with one ABI and shared by every frontend that touches it, so a
  // raw pointer is safe without any flattening.
  void pythia_slha_set_slhaea(void* handle, const SLHAea::Coll* coll)
  {
    static_cast<Pythia8::SusyLesHouches*>(handle)->setSLHAea(coll);
  }

  // =====================================================================
  // Event (Pythia8::Event)
  // =====================================================================
  //
  // Unlike Rivet's AnalysisHandler (used only through methods on a single
  // long-lived handler object), Pythia8::Event is used by *value*
  // throughout ColliderBit: GAMBIT module code default-constructs its own
  // Event objects on the stack/thread_local storage
  // (`EventT dummy_pythia_event;`), clears and refills them every event,
  // and copy-assigns Pythia's own internal event into them
  // (`event = _pythiaInstance->event;`). A flat shim can't give the
  // GAMBIT-side wrapper real value semantics "for free" the way plain C++
  // does -- each of those operations needs its own explicit entry point
  // (create/destroy/assign), with the GAMBIT-side wrapper class providing
  // the actual copy-constructor/assignment-operator overloads module code
  // relies on implicitly.

  void* pythia_event_create()
  {
    return new Pythia8::Event();
  }

  void pythia_event_destroy(void* handle)
  {
    delete static_cast<Pythia8::Event*>(handle);
  }

  // dst = src (a real, deep copy of Pythia's particle vector and history).
  void pythia_event_assign(void* dst_handle, void* src_handle)
  {
    *static_cast<Pythia8::Event*>(dst_handle) = *static_cast<Pythia8::Event*>(src_handle);
  }

  void pythia_event_clear(void* handle)
  {
    static_cast<Pythia8::Event*>(handle)->clear();
  }

  int pythia_event_size(void* handle)
  {
    return static_cast<int>(static_cast<Pythia8::Event*>(handle)->size());
  }

  // Non-owning pointer to a Particle living inside this Event's own
  // storage (Event::operator[]) -- ownership/lifetime is the Event's, not
  // the caller's, exactly as with the real API.
  void* pythia_event_particle(void* handle, int i)
  {
    return &(*static_cast<Pythia8::Event*>(handle))[i];
  }

  // Event::daughterList(int), distinct from Particle::daughterList() below
  // -- the real API has both, with different meanings (this one walks the
  // event record from an index, independent of any single Particle
  // object). Caller-owned-buffer convention (see README.md step 5): no
  // static/shared state, safe for concurrent calls on different handles.
  int pythia_event_daughter_list(void* handle, int i, int* buf, int buflen)
  {
    std::vector<int> v = static_cast<Pythia8::Event*>(handle)->daughterList(i);
    int n = static_cast<int>(std::min<size_t>(v.size(), static_cast<size_t>(buflen)));
    for (int k = 0; k < n; ++k) buf[k] = v[k];
    return static_cast<int>(v.size());
  }

  // Caller-owned-buffer convention for the formatted event listing, used
  // by GAMBIT only to shove into its own debug log on event-generation
  // failure (`pythia_event.list(false, false, 1, ss)`), not for physics.
  //
  // Unlike a fixed-size buffer, the return value is the *true* length of
  // the listing (excluding the terminating '\0'), exactly like
  // pythia_particle_mother_list()/pythia_info_codes_hard() return the true
  // element count for a vector<int>. snprintf() itself already reports
  // this (the number of characters that *would* have been written, had
  // buflen been unlimited), so this just forwards that instead of
  // discarding it. The caller can therefore size its buffer exactly,
  // rather than guessing a fixed size up front and hoping real events
  // never exceed it -- see Pythia_8_312.hpp's Event::list() for the
  // retry-on-truncation caller side.
  int pythia_event_list(void* handle, int show_scale_and_vertex, int show_mothers_and_daughters, int precision, char* buf, int buflen)
  {
    std::ostringstream ss;
    static_cast<Pythia8::Event*>(handle)->list(show_scale_and_vertex != 0, show_mothers_and_daughters != 0, precision, ss);
    const std::string& s = ss.str();
    return std::snprintf(buf, buflen, "%s", s.c_str());
  }

  // =====================================================================
  // Particle (Pythia8::Particle) -- always reached via a non-owning
  // pointer into some Event's storage (pythia_event_particle above); the
  // shim never creates or destroys one itself.
  // =====================================================================

  int pythia_particle_id(void* handle)
  {
    return static_cast<Pythia8::Particle*>(handle)->id();
  }

  int pythia_particle_is_final(void* handle)
  {
    return static_cast<Pythia8::Particle*>(handle)->isFinal() ? 1 : 0;
  }

  int pythia_particle_is_parton(void* handle)
  {
    return static_cast<Pythia8::Particle*>(handle)->isParton() ? 1 : 0;
  }

  int pythia_particle_is_hadron(void* handle)
  {
    return static_cast<Pythia8::Particle*>(handle)->isHadron() ? 1 : 0;
  }

  int pythia_particle_mother_list(void* handle, int* buf, int buflen)
  {
    std::vector<int> v = static_cast<Pythia8::Particle*>(handle)->motherList();
    int n = static_cast<int>(std::min<size_t>(v.size(), static_cast<size_t>(buflen)));
    for (int k = 0; k < n; ++k) buf[k] = v[k];
    return static_cast<int>(v.size());
  }

  int pythia_particle_daughter_list(void* handle, int* buf, int buflen)
  {
    std::vector<int> v = static_cast<Pythia8::Particle*>(handle)->daughterList();
    int n = static_cast<int>(std::min<size_t>(v.size(), static_cast<size_t>(buflen)));
    for (int k = 0; k < n; ++k) buf[k] = v[k];
    return static_cast<int>(v.size());
  }

  // Particle::p() returns a Pythia8::Vec4 that GAMBIT's own
  // ColliderBit/colliders/Pythia8/Py8Utils.hpp immediately decomposes into
  // px/py/pz/e/mCalc() and nothing else -- so rather than giving Vec4 its
  // own handle type and four more accessor functions, this flattens it to
  // its four momentum components in one call. mCalc() (the on-shell mass
  // reconstructed from the 4-momentum) is returned separately below
  // because it needs Vec4's own internal arithmetic, not just field reads.
  void pythia_particle_p4(void* handle, double* px, double* py, double* pz, double* e)
  {
    const Pythia8::Vec4& p = static_cast<Pythia8::Particle*>(handle)->p();
    *px = p.px();
    *py = p.py();
    *pz = p.pz();
    *e  = p.e();
  }

  double pythia_particle_p_mcalc(void* handle)
  {
    return static_cast<Pythia8::Particle*>(handle)->p().mCalc();
  }

  // Direct Particle accessors used by ColliderBit/colliders/EventConversionUtils.hpp
  // and Py8EventConversions.hpp alongside p()/motherList() above -- these
  // duplicate information already reachable via p4()/motherList() in the
  // real API, but are called directly on Particle rather than via p(), so
  // need their own shim entries.
  int pythia_particle_id_abs(void* handle)
  {
    return static_cast<Pythia8::Particle*>(handle)->idAbs();
  }

  double pythia_particle_eta(void* handle)
  {
    return static_cast<Pythia8::Particle*>(handle)->eta();
  }

  double pythia_particle_px(void* handle)
  {
    return static_cast<Pythia8::Particle*>(handle)->px();
  }

  double pythia_particle_py(void* handle)
  {
    return static_cast<Pythia8::Particle*>(handle)->py();
  }

  double pythia_particle_pz(void* handle)
  {
    return static_cast<Pythia8::Particle*>(handle)->pz();
  }

  double pythia_particle_m(void* handle)
  {
    return static_cast<Pythia8::Particle*>(handle)->m();
  }

  int pythia_particle_mother1(void* handle)
  {
    return static_cast<Pythia8::Particle*>(handle)->mother1();
  }

  int pythia_particle_mother2(void* handle)
  {
    return static_cast<Pythia8::Particle*>(handle)->mother2();
  }

  // =====================================================================
  // Info (Pythia8::Info) -- always reached via pythia_get_info above.
  // =====================================================================

  double pythia_info_sigma_gen(void* handle)
  {
    return static_cast<Pythia8::Info*>(handle)->sigmaGen();
  }

  double pythia_info_sigma_gen_code(void* handle, int process_code)
  {
    return static_cast<Pythia8::Info*>(handle)->sigmaGen(process_code);
  }

  double pythia_info_sigma_err(void* handle)
  {
    return static_cast<Pythia8::Info*>(handle)->sigmaErr();
  }

  double pythia_info_sigma_err_code(void* handle, int process_code)
  {
    return static_cast<Pythia8::Info*>(handle)->sigmaErr(process_code);
  }

  int pythia_info_code(void* handle)
  {
    return static_cast<Pythia8::Info*>(handle)->code();
  }

  int pythia_info_codes_hard(void* handle, int* buf, int buflen)
  {
    std::vector<int> v = static_cast<Pythia8::Info*>(handle)->codesHard();
    int n = static_cast<int>(std::min<size_t>(v.size(), static_cast<size_t>(buflen)));
    for (int k = 0; k < n; ++k) buf[k] = v[k];
    return static_cast<int>(v.size());
  }

  // =====================================================================
  // GAMBIT_hepmc_writer -- a bespoke GAMBIT-authored class (not part of
  // Pythia's real API), patched into Pythia's own installed include tree
  // by Backends/patches/pythia/8.312/patch_pythia_8.312.dif and already
  // listed in the BOSS config's load_classes. It converts a Pythia event
  // to HepMC2/HepMC3 using Pythia's own bundled HepMC converter. Kept
  // exactly as BOSS wrapped it; only the mechanism for crossing the
  // GAMBIT/backend boundary changes.
  // =====================================================================

  void* pythia_hepmc_writer_create()
  {
    return new Pythia8::GAMBIT_hepmc_writer();
  }

  void pythia_hepmc_writer_destroy(void* handle)
  {
    delete static_cast<Pythia8::GAMBIT_hepmc_writer*>(handle);
  }

  void pythia_hepmc_writer_init(void* handle, const char* filename, int hepmc2, int hepmc3)
  {
    static_cast<Pythia8::GAMBIT_hepmc_writer*>(handle)->init(filename, hepmc2 != 0, hepmc3 != 0);
  }

  void pythia_hepmc_writer_write_event_hepmc2(void* handle, void* pythia_handle)
  {
    static_cast<Pythia8::GAMBIT_hepmc_writer*>(handle)->write_event_HepMC2(static_cast<Pythia8::Pythia*>(pythia_handle));
  }

  void pythia_hepmc_writer_write_event_hepmc3(void* handle, void* pythia_handle)
  {
    static_cast<Pythia8::GAMBIT_hepmc_writer*>(handle)->write_event_HepMC3(static_cast<Pythia8::Pythia*>(pythia_handle));
  }

  void pythia_hepmc_writer_convert_to_hepmc_event(void* handle, void* pythia_handle, HepMC3::GenEvent* event)
  {
    static_cast<Pythia8::GAMBIT_hepmc_writer*>(handle)->convert_to_HepMC_event(static_cast<Pythia8::Pythia*>(pythia_handle), *event);
  }

} // extern "C"
