//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Hand-written frontend header for the Pythia shim
///  (Backends/src/frontends/shims/pythia_shim.cpp).
///
///  PROTOTYPE / NOT WIRED INTO THE BUILD. This header plays the role
///  that the BOSS-generated frontend header
///  (Backends/include/gambit/Backends/frontends/Pythia_8_312.hpp)
///  plays today: it gives GAMBIT module code C++ types that look like
///  Pythia8::Pythia and the handful of other Pythia8 types ColliderBit
///  touches directly (Event, Particle, Info, Settings, ParticleData,
///  SLHAinterface/SusyLesHouches, plus the GAMBIT-authored
///  GAMBIT_hepmc_writer), backed here by dlsym'd calls into
///  libpythia_shim.so instead of BOSS-generated wrapper/abstract
///  classes.
///
///  Unlike the Rivet shim, this is NOT a single small handler class --
///  see Backends/src/frontends/shims/README.md ("Pythia shim") for why:
///  Py8Collider.hpp (the one piece of GAMBIT module code this header
///  must stay a drop-in replacement for) reads several of Pythia's
///  public *data members* directly (settings, particleData, event,
///  info, slhaInterface.slha) and uses Pythia8::Event/Particle as real
///  value/reference types throughout ColliderBit's event-conversion
///  code, not just through a handful of handler methods. Each of those
///  needed its own small wrapper class below, mirroring the layout of
///  the real Pythia8 classes closely enough that module code needs no
///  changes.
///
///  This follows the real GAMBIT LOAD_LIBRARY/BE_FUNCTION pattern (as
///  Rivet_4_1_0.hpp now does), rather than a hand-rolled dlopen/dlsym
///  loader, since that pattern is already proven to work for a shim-based
///  frontend. It has NOT been exercised through an actual GAMBIT
///  cmake configure (same caveat as Rivet_4_1_0.hpp when it was written);
///  see the README for what was and was not verified.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author The GAMBIT Collaboration
///  \date 2026 Oct
///
///  *********************************************

#ifndef EXCLUDE_HEPMC

#include "gambit/Backends/backend_types/Pythia_8_312/identification.hpp"

LOAD_LIBRARY

#include "gambit/Utils/begin_ignore_warnings_hepmc.hpp"
#include "HepMC3/GenEvent.h"
#include "gambit/Utils/end_ignore_warnings.hpp"
#include "SLHAea/slhaea.h"

#include <string>
#include <vector>

// Functions exported by libpythia_shim.so (Backends/src/frontends/shims/pythia_shim.cpp).
// Plain, unmangled names -- no "__BOSS_" symbol-name candidates needed, since
// these come from an extern "C" shim rather than a mangled C++ symbol.
BE_FUNCTION(pythia_create,                      void*,  (const char*, int),                       "pythia_create",                      "pythia_create")
BE_FUNCTION(pythia_create_from_base,            void*,  (void*, void*, int),                       "pythia_create_from_base",            "pythia_create_from_base")
BE_FUNCTION(pythia_destroy,                     void,   (void*),                                   "pythia_destroy",                     "pythia_destroy")
BE_FUNCTION(pythia_read_string,                 int,    (void*, const char*),                      "pythia_read_string",                 "pythia_read_string")
BE_FUNCTION(pythia_init,                        int,    (void*),                                   "pythia_init",                        "pythia_init")
BE_FUNCTION(pythia_next,                        int,    (void*),                                   "pythia_next",                        "pythia_next")
BE_FUNCTION(pythia_get_sigma_max_sum,           double, (void*),                                   "pythia_get_sigma_max_sum",           "pythia_get_sigma_max_sum")
BE_FUNCTION(pythia_get_settings,                void*,  (void*),                                   "pythia_get_settings",                "pythia_get_settings")
BE_FUNCTION(pythia_get_particle_data,           void*,  (void*),                                   "pythia_get_particle_data",           "pythia_get_particle_data")
BE_FUNCTION(pythia_get_event,                   void*,  (void*),                                   "pythia_get_event",                   "pythia_get_event")
BE_FUNCTION(pythia_get_info,                    void*,  (void*),                                   "pythia_get_info",                    "pythia_get_info")
BE_FUNCTION(pythia_get_slha,                    void*,  (void*),                                   "pythia_get_slha",                    "pythia_get_slha")

BE_FUNCTION(pythia_slha_set_slhaea,             void,   (void*, const SLHAea::Coll*),              "pythia_slha_set_slhaea",             "pythia_slha_set_slhaea")

BE_FUNCTION(pythia_event_create,                void*,  (),                                        "pythia_event_create",                "pythia_event_create")
BE_FUNCTION(pythia_event_destroy,               void,   (void*),                                   "pythia_event_destroy",               "pythia_event_destroy")
BE_FUNCTION(pythia_event_assign,                void,   (void*, void*),                             "pythia_event_assign",                "pythia_event_assign")
BE_FUNCTION(pythia_event_clear,                 void,   (void*),                                   "pythia_event_clear",                 "pythia_event_clear")
BE_FUNCTION(pythia_event_size,                  int,    (void*),                                   "pythia_event_size",                  "pythia_event_size")
BE_FUNCTION(pythia_event_particle,              void*,  (void*, int),                              "pythia_event_particle",              "pythia_event_particle")
BE_FUNCTION(pythia_event_daughter_list,         int,    (void*, int, int*, int),                   "pythia_event_daughter_list",         "pythia_event_daughter_list")
BE_FUNCTION(pythia_event_list,                  void,   (void*, int, int, int, char*, int),        "pythia_event_list",                  "pythia_event_list")

BE_FUNCTION(pythia_particle_id,                 int,    (void*),                                   "pythia_particle_id",                 "pythia_particle_id")
BE_FUNCTION(pythia_particle_is_final,           int,    (void*),                                   "pythia_particle_is_final",           "pythia_particle_is_final")
BE_FUNCTION(pythia_particle_is_parton,          int,    (void*),                                   "pythia_particle_is_parton",          "pythia_particle_is_parton")
BE_FUNCTION(pythia_particle_is_hadron,          int,    (void*),                                   "pythia_particle_is_hadron",          "pythia_particle_is_hadron")
BE_FUNCTION(pythia_particle_mother_list,        int,    (void*, int*, int),                        "pythia_particle_mother_list",        "pythia_particle_mother_list")
BE_FUNCTION(pythia_particle_daughter_list,      int,    (void*, int*, int),                        "pythia_particle_daughter_list",       "pythia_particle_daughter_list")
BE_FUNCTION(pythia_particle_p4,                 void,   (void*, double*, double*, double*, double*), "pythia_particle_p4",                "pythia_particle_p4")
BE_FUNCTION(pythia_particle_p_mcalc,            double, (void*),                                   "pythia_particle_p_mcalc",             "pythia_particle_p_mcalc")

BE_FUNCTION(pythia_info_sigma_gen,              double, (void*),                                   "pythia_info_sigma_gen",              "pythia_info_sigma_gen")
BE_FUNCTION(pythia_info_sigma_gen_code,         double, (void*, int),                              "pythia_info_sigma_gen_code",         "pythia_info_sigma_gen_code")
BE_FUNCTION(pythia_info_sigma_err,              double, (void*),                                   "pythia_info_sigma_err",              "pythia_info_sigma_err")
BE_FUNCTION(pythia_info_sigma_err_code,         double, (void*, int),                              "pythia_info_sigma_err_code",         "pythia_info_sigma_err_code")
BE_FUNCTION(pythia_info_code,                   int,    (void*),                                   "pythia_info_code",                   "pythia_info_code")
BE_FUNCTION(pythia_info_codes_hard,             int,    (void*, int*, int),                        "pythia_info_codes_hard",              "pythia_info_codes_hard")

BE_FUNCTION(pythia_hepmc_writer_create,         void*,  (),                                        "pythia_hepmc_writer_create",         "pythia_hepmc_writer_create")
BE_FUNCTION(pythia_hepmc_writer_destroy,        void,   (void*),                                   "pythia_hepmc_writer_destroy",        "pythia_hepmc_writer_destroy")
BE_FUNCTION(pythia_hepmc_writer_init,           void,   (void*, const char*, int, int),            "pythia_hepmc_writer_init",            "pythia_hepmc_writer_init")
BE_FUNCTION(pythia_hepmc_writer_write_event_hepmc2, void, (void*, void*),                           "pythia_hepmc_writer_write_event_hepmc2", "pythia_hepmc_writer_write_event_hepmc2")
BE_FUNCTION(pythia_hepmc_writer_write_event_hepmc3, void, (void*, void*),                           "pythia_hepmc_writer_write_event_hepmc3", "pythia_hepmc_writer_write_event_hepmc3")
BE_FUNCTION(pythia_hepmc_writer_convert_to_hepmc_event, void, (void*, void*, HepMC3::GenEvent*),    "pythia_hepmc_writer_convert_to_hepmc_event", "pythia_hepmc_writer_convert_to_hepmc_event")

namespace Gambit
{
  namespace Backends
  {
    namespace Pythia_8_312
    {
      namespace Pythia8
      {
        /// Opaque, non-owning stand-in for Pythia8::Settings. Nothing in
        /// GAMBIT ever calls a method on this type -- it is only ever read
        /// off one Pythia instance (Pythia::settings) and handed straight
        /// into another Pythia instance's constructor (see Py8Collider.hpp:
        /// `new PythiaT(_pythiaBase->settings, _pythiaBase->particleData)`).
        /// So, unlike every other class here, it needs no methods at all --
        /// just something with the right type identity to pass through.
        class Settings
        {
          public:
            explicit Settings(void* handle) : handle_(handle) {}
            void* get_BEhandle() const { return handle_; }
          private:
            void* handle_;
        };

        /// Opaque, non-owning stand-in for Pythia8::ParticleData. See Settings above.
        class ParticleData
        {
          public:
            explicit ParticleData(void* handle) : handle_(handle) {}
            void* get_BEhandle() const { return handle_; }
          private:
            void* handle_;
        };

        /// GAMBIT-side stand-in for Pythia8::SusyLesHouches, reached only
        /// through Pythia::slhaInterface.slha. Exposes exactly the one
        /// method ColliderBit calls on it.
        class SusyLesHouches
        {
          public:
            explicit SusyLesHouches(void* handle) : handle_(handle) {}

            void setSLHAea(const SLHAea::Coll* coll)
            {
              Gambit::Backends::Pythia_8_312::pythia_slha_set_slhaea(handle_, coll);
            }

          private:
            void* handle_;
        };

        /// GAMBIT-side stand-in for Pythia8::SLHAinterface. Only ever
        /// reached through Pythia::slhaInterface, and only ever used for
        /// its own .slha member -- no other SLHAinterface method is called
        /// anywhere in GAMBIT, so none are wrapped.
        class SLHAinterface
        {
          public:
            explicit SLHAinterface(void* slha_handle) : slha(slha_handle) {}
            SusyLesHouches slha;
        };

        /// GAMBIT-side stand-in for Pythia8::Vec4, flattened down to the
        /// four fields and one derived quantity (mCalc()) that
        /// ColliderBit/colliders/Pythia8/Py8Utils.hpp actually reads
        /// (mk_p4()/mk_pseudojet()) -- see pythia_particle_p4() in
        /// pythia_shim.cpp for why a full Vec4 handle type wasn't needed.
        class Vec4
        {
          public:
            Vec4(double px, double py, double pz, double e, double mcalc)
              : px_(px), py_(py), pz_(pz), e_(e), mcalc_(mcalc) {}

            double px() const { return px_; }
            double py() const { return py_; }
            double pz() const { return pz_; }
            double e()  const { return e_; }
            double mCalc() const { return mcalc_; }

          private:
            double px_, py_, pz_, e_, mcalc_;
        };

        /// GAMBIT-side stand-in for Pythia8::Particle. Always reached via a
        /// non-owning pointer into some Event's own storage
        /// (Event::operator[]) -- this class never owns or frees that
        /// pointer, exactly matching the real API's reference semantics.
        class Particle
        {
          public:
            explicit Particle(void* handle) : handle_(handle) {}

            int id() const { return Gambit::Backends::Pythia_8_312::pythia_particle_id(handle_); }
            bool isFinal() const { return Gambit::Backends::Pythia_8_312::pythia_particle_is_final(handle_) != 0; }
            bool isParton() const { return Gambit::Backends::Pythia_8_312::pythia_particle_is_parton(handle_) != 0; }
            bool isHadron() const { return Gambit::Backends::Pythia_8_312::pythia_particle_is_hadron(handle_) != 0; }

            std::vector<int> motherList() const
            {
              return collectInts(Gambit::Backends::Pythia_8_312::pythia_particle_mother_list);
            }

            std::vector<int> daughterList() const
            {
              return collectInts(Gambit::Backends::Pythia_8_312::pythia_particle_daughter_list);
            }

            Vec4 p() const
            {
              double px, py, pz, e;
              Gambit::Backends::Pythia_8_312::pythia_particle_p4(handle_, &px, &py, &pz, &e);
              double mcalc = Gambit::Backends::Pythia_8_312::pythia_particle_p_mcalc(handle_);
              return Vec4(px, py, pz, e, mcalc);
            }

          private:
            template <typename Fn>
            std::vector<int> collectInts(Fn fn) const
            {
              // First call with a generous fixed buffer; grow and retry only
              // in the (physically implausible for a single particle's
              // mother/daughter list) case that it overflows.
              std::vector<int> buf(16);
              int n = fn(handle_, buf.data(), static_cast<int>(buf.size()));
              if (n > static_cast<int>(buf.size()))
              {
                buf.resize(n);
                n = fn(handle_, buf.data(), static_cast<int>(buf.size()));
              }
              buf.resize(n);
              return buf;
            }

            void* handle_;
        };

        /// GAMBIT-side stand-in for Pythia8::Info. Always reached via
        /// Pythia::info -- never created or destroyed independently.
        class Info
        {
          public:
            explicit Info(void* handle) : handle_(handle) {}

            double sigmaGen() const { return Gambit::Backends::Pythia_8_312::pythia_info_sigma_gen(handle_); }
            double sigmaGen(int process_code) const { return Gambit::Backends::Pythia_8_312::pythia_info_sigma_gen_code(handle_, process_code); }
            double sigmaErr() const { return Gambit::Backends::Pythia_8_312::pythia_info_sigma_err(handle_); }
            double sigmaErr(int process_code) const { return Gambit::Backends::Pythia_8_312::pythia_info_sigma_err_code(handle_, process_code); }
            int code() const { return Gambit::Backends::Pythia_8_312::pythia_info_code(handle_); }

            std::vector<int> codesHard() const
            {
              std::vector<int> buf(64);
              int n = Gambit::Backends::Pythia_8_312::pythia_info_codes_hard(handle_, buf.data(), static_cast<int>(buf.size()));
              if (n > static_cast<int>(buf.size()))
              {
                buf.resize(n);
                n = Gambit::Backends::Pythia_8_312::pythia_info_codes_hard(handle_, buf.data(), static_cast<int>(buf.size()));
              }
              buf.resize(n);
              return buf;
            }

          private:
            void* handle_;
        };

        /// GAMBIT-side stand-in for Pythia8::Event. Unlike the classes
        /// above, this one needs real value semantics -- GAMBIT module
        /// code default-constructs its own Events, clears and refills them
        /// every event, and copy-assigns Pythia's own internal event into
        /// them (`event = _pythiaInstance->event;` in Py8Collider.hpp).
        /// Owning instances are created via the default constructor and
        /// destroyed in the destructor; non-owning instances (wrapping a
        /// pointer into some other object's storage, e.g. Pythia::event)
        /// are built via the private pointer+bool constructor and never
        /// call pythia_event_destroy.
        class Event
        {
          public:
            Event() : handle_(Gambit::Backends::Pythia_8_312::pythia_event_create()), owns_(true) {}

            ~Event()
            {
              if (owns_) Gambit::Backends::Pythia_8_312::pythia_event_destroy(handle_);
            }

            Event(const Event& other) : handle_(Gambit::Backends::Pythia_8_312::pythia_event_create()), owns_(true)
            {
              Gambit::Backends::Pythia_8_312::pythia_event_assign(handle_, other.handle_);
            }

            Event& operator=(const Event& other)
            {
              Gambit::Backends::Pythia_8_312::pythia_event_assign(handle_, other.handle_);
              return *this;
            }

            void clear() { Gambit::Backends::Pythia_8_312::pythia_event_clear(handle_); }

            int size() const { return Gambit::Backends::Pythia_8_312::pythia_event_size(handle_); }

            Particle operator[](int i) const
            {
              return Particle(Gambit::Backends::Pythia_8_312::pythia_event_particle(handle_, i));
            }

            std::vector<int> daughterList(int i) const
            {
              std::vector<int> buf(16);
              int n = Gambit::Backends::Pythia_8_312::pythia_event_daughter_list(handle_, i, buf.data(), static_cast<int>(buf.size()));
              if (n > static_cast<int>(buf.size()))
              {
                buf.resize(n);
                n = Gambit::Backends::Pythia_8_312::pythia_event_daughter_list(handle_, i, buf.data(), static_cast<int>(buf.size()));
              }
              buf.resize(n);
              return buf;
            }

            /// Only the 4-argument overload (showScaleAndVertex,
            /// showMothersAndDaughters, precision, ostream&) is ever called
            /// anywhere in GAMBIT -- see generateEventPy8Collider.hpp and
            /// PerformInitialCrossSection_Pythia(), both only using it to
            /// dump a failed event into the debug log. Other real overloads
            /// (defaulting precision/ostream) are deliberately not wrapped.
            void list(bool show_scale_and_vertex, bool show_mothers_and_daughters, int precision, std::ostream& os) const
            {
              char buf[8192];
              Gambit::Backends::Pythia_8_312::pythia_event_list(handle_, show_scale_and_vertex ? 1 : 0, show_mothers_and_daughters ? 1 : 0, precision, buf, sizeof(buf));
              os << buf;
            }

            /// Non-owning constructor: wraps a pointer into another object's
            /// storage (e.g. Pythia::event) without taking ownership of it.
            explicit Event(void* non_owned_handle, bool /*tag*/) : handle_(non_owned_handle), owns_(false) {}

          private:
            void* handle_;
            bool owns_;
        };

        /// GAMBIT-side stand-in for Pythia8::Pythia -- a drop-in replacement
        /// for the BOSS-generated wrapper type that Py8Collider.hpp (and the
        /// macros in getPy8Collider.hpp/generateEventPy8Collider.hpp that
        /// instantiate it) already use. Exposes exactly the public data
        /// members and methods those call sites touch.
        class Pythia
        {
          public:
            Pythia(const std::string& xml_dir, bool print_banner = true)
              : handle_(Gambit::Backends::Pythia_8_312::pythia_create(xml_dir.c_str(), print_banner ? 1 : 0)),
                settings(Gambit::Backends::Pythia_8_312::pythia_get_settings(handle_)),
                particleData(Gambit::Backends::Pythia_8_312::pythia_get_particle_data(handle_)),
                slhaInterface(Gambit::Backends::Pythia_8_312::pythia_get_slha(handle_)),
                event(Gambit::Backends::Pythia_8_312::pythia_get_event(handle_), true),
                info(Gambit::Backends::Pythia_8_312::pythia_get_info(handle_))
            {}

            Pythia(Settings& settings_in, ParticleData& particle_data_in, bool print_banner = true)
              : handle_(Gambit::Backends::Pythia_8_312::pythia_create_from_base(settings_in.get_BEhandle(), particle_data_in.get_BEhandle(), print_banner ? 1 : 0)),
                settings(Gambit::Backends::Pythia_8_312::pythia_get_settings(handle_)),
                particleData(Gambit::Backends::Pythia_8_312::pythia_get_particle_data(handle_)),
                slhaInterface(Gambit::Backends::Pythia_8_312::pythia_get_slha(handle_)),
                event(Gambit::Backends::Pythia_8_312::pythia_get_event(handle_), true),
                info(Gambit::Backends::Pythia_8_312::pythia_get_info(handle_))
            {}

            ~Pythia()
            {
              Gambit::Backends::Pythia_8_312::pythia_destroy(handle_);
            }

            Pythia(const Pythia&) = delete;
            Pythia& operator=(const Pythia&) = delete;

            bool readString(const std::string& command) { return Gambit::Backends::Pythia_8_312::pythia_read_string(handle_, command.c_str()) != 0; }
            bool init() { return Gambit::Backends::Pythia_8_312::pythia_init(handle_) != 0; }
            bool next() { return Gambit::Backends::Pythia_8_312::pythia_next(handle_) != 0; }
            double getSigmaMaxSum() { return Gambit::Backends::Pythia_8_312::pythia_get_sigma_max_sum(handle_); }

            /// Not part of the real Pythia8::Pythia API: lets
            /// GAMBIT_hepmc_writer (below) and anything else that needs to
            /// hand a raw Pythia* back across the shim boundary get at the
            /// underlying handle, matching the real GAMBIT_hepmc_writer
            /// methods' `Pythia8::Pythia*` parameters.
            void* get_BEhandle() const { return handle_; }

            // Public data members, matching the real Pythia8::Pythia layout
            // that Py8Collider.hpp reads directly (`_pythiaBase->settings`,
            // `_pythiaInstance->event`, `_pythiaInstance->info.sigmaGen()`,
            // `_pythiaInstance->slhaInterface.slha.setSLHAea(...)`).
            Settings settings;
            ParticleData particleData;
            SLHAinterface slhaInterface;
            Event event; // non-owning view of Pythia's own internal event
            Info info;

          private:
            void* handle_;
        };

        /// GAMBIT-side stand-in for the GAMBIT-authored GAMBIT_hepmc_writer
        /// class (patched into Pythia's own installed include tree; not
        /// part of Pythia's real API). See
        /// Backends/patches/pythia/8.312/patch_pythia_8.312.dif.
        class GAMBIT_hepmc_writer
        {
          public:
            GAMBIT_hepmc_writer() : handle_(Gambit::Backends::Pythia_8_312::pythia_hepmc_writer_create()) {}

            ~GAMBIT_hepmc_writer()
            {
              Gambit::Backends::Pythia_8_312::pythia_hepmc_writer_destroy(handle_);
            }

            GAMBIT_hepmc_writer(const GAMBIT_hepmc_writer&) = delete;
            GAMBIT_hepmc_writer& operator=(const GAMBIT_hepmc_writer&) = delete;

            void init(const std::string& filename, bool hepmc2, bool hepmc3)
            {
              Gambit::Backends::Pythia_8_312::pythia_hepmc_writer_init(handle_, filename.c_str(), hepmc2 ? 1 : 0, hepmc3 ? 1 : 0);
            }

            void write_event_HepMC2(Pythia* pythia)
            {
              Gambit::Backends::Pythia_8_312::pythia_hepmc_writer_write_event_hepmc2(handle_, pythia->get_BEhandle());
            }

            void write_event_HepMC3(Pythia* pythia)
            {
              Gambit::Backends::Pythia_8_312::pythia_hepmc_writer_write_event_hepmc3(handle_, pythia->get_BEhandle());
            }

            void convert_to_HepMC_event(Pythia* pythia, HepMC3::GenEvent& event)
            {
              Gambit::Backends::Pythia_8_312::pythia_hepmc_writer_convert_to_hepmc_event(handle_, pythia->get_BEhandle(), &event);
            }

          private:
            void* handle_;
        };
      }
    }
  }
}

// End
#include "gambit/Backends/backend_undefs.hpp"

#endif
