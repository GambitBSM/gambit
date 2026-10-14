#ifndef __loaded_types_Pythia_8_312_hpp__
#define __loaded_types_Pythia_8_312_hpp__ 1

#ifndef EXCLUDE_HEPMC

///  Pythia's frontend is hand-written (see
///  Backends/src/frontends/shims/README.md, "Pythia shim") rather than
///  BOSS-generated, so there are no wrapper_*.h/abstract_*.h files to
///  include here.
///
///  This file -- not Backends/include/gambit/Backends/frontends/Pythia_8_312.hpp
///  -- is the single source of truth for the Pythia_8_312::Pythia8::* class
///  *definitions*, because it's reached two different ways:
///
///   1. via backend_rollcall.hpp -> frontends/Pythia_8_312.hpp, where
///      frontend_macros.hpp's BE_FUNCTION/LOAD_LIBRARY machinery is already
///      active; and
///   2. via backend_types_rollcall.hpp -> here, directly, from contexts
///      like Elements/types_rollcall.hpp that essentially every GAMBIT
///      module .cpp pulls in, regardless of whether that TU has anything
///      to do with Pythia or has its OWN backend's module macro machinery
///      active. Pulling in frontend_macros.hpp here too would call
///      MODULE_START_CAPABILITY et al a second, unwanted time and collide
///      with whatever macro state is already active there.
///
///  So the classes below call the shim's exported functions through plain
///  "extern" redeclarations of the same Gambit::Backends::Pythia_8_312
///  function-pointer variables that frontends/Pythia_8_312.hpp's BE_FUNCTION
///  lines declare -- redeclaring an extern variable with an identical type
///  is always legal in C++, so this needs no macro machinery, just the
///  plain variable declarations.
///
///  frontends/Pythia_8_312.hpp includes this file for the classes themselves
///  (after its own BE_FUNCTION declarations), so there is exactly one copy
///  of the class bodies, guarded against double-inclusion either way.

#include <string>
#include <vector>

#include "gambit/Utils/begin_ignore_warnings_hepmc.hpp"
#include "HepMC3/GenEvent.h"
#include "gambit/Utils/end_ignore_warnings.hpp"
#include "SLHAea/slhaea.h"

namespace Gambit
{
  namespace Backends
  {
    namespace Pythia_8_312
    {
      typedef void* (*pythia_create_type)(const char*, int);                                  extern const pythia_create_type pythia_create;
      typedef void* (*pythia_create_from_base_type)(void*, void*, int);                        extern const pythia_create_from_base_type pythia_create_from_base;
      typedef void  (*pythia_destroy_type)(void*);                                             extern const pythia_destroy_type pythia_destroy;
      typedef int   (*pythia_read_string_type)(void*, const char*);                             extern const pythia_read_string_type pythia_read_string;
      typedef int   (*pythia_init_type)(void*);                                                 extern const pythia_init_type pythia_init;
      typedef int   (*pythia_next_type)(void*);                                                 extern const pythia_next_type pythia_next;
      typedef double(*pythia_get_sigma_max_sum_type)(void*);                                    extern const pythia_get_sigma_max_sum_type pythia_get_sigma_max_sum;
      typedef void* (*pythia_get_settings_type)(void*);                                         extern const pythia_get_settings_type pythia_get_settings;
      typedef void* (*pythia_get_particle_data_type)(void*);                                    extern const pythia_get_particle_data_type pythia_get_particle_data;
      typedef void* (*pythia_get_event_type)(void*);                                            extern const pythia_get_event_type pythia_get_event;
      typedef void* (*pythia_get_info_type)(void*);                                             extern const pythia_get_info_type pythia_get_info;
      typedef void* (*pythia_get_slha_type)(void*);                                             extern const pythia_get_slha_type pythia_get_slha;

      typedef void  (*pythia_slha_set_slhaea_type)(void*, const SLHAea::Coll*);                 extern const pythia_slha_set_slhaea_type pythia_slha_set_slhaea;

      typedef void* (*pythia_event_create_type)();                                              extern const pythia_event_create_type pythia_event_create;
      typedef void  (*pythia_event_destroy_type)(void*);                                        extern const pythia_event_destroy_type pythia_event_destroy;
      typedef void  (*pythia_event_assign_type)(void*, void*);                                  extern const pythia_event_assign_type pythia_event_assign;
      typedef void  (*pythia_event_clear_type)(void*);                                          extern const pythia_event_clear_type pythia_event_clear;
      typedef int   (*pythia_event_size_type)(void*);                                           extern const pythia_event_size_type pythia_event_size;
      typedef void* (*pythia_event_particle_type)(void*, int);                                  extern const pythia_event_particle_type pythia_event_particle;
      typedef int   (*pythia_event_daughter_list_type)(void*, int, int*, int);                  extern const pythia_event_daughter_list_type pythia_event_daughter_list;
      typedef int   (*pythia_event_list_type)(void*, int, int, int, char*, int);                extern const pythia_event_list_type pythia_event_list;

      typedef int   (*pythia_particle_id_type)(void*);                                          extern const pythia_particle_id_type pythia_particle_id;
      typedef int   (*pythia_particle_is_final_type)(void*);                                    extern const pythia_particle_is_final_type pythia_particle_is_final;
      typedef int   (*pythia_particle_is_parton_type)(void*);                                   extern const pythia_particle_is_parton_type pythia_particle_is_parton;
      typedef int   (*pythia_particle_is_hadron_type)(void*);                                   extern const pythia_particle_is_hadron_type pythia_particle_is_hadron;
      typedef int   (*pythia_particle_mother_list_type)(void*, int*, int);                      extern const pythia_particle_mother_list_type pythia_particle_mother_list;
      typedef int   (*pythia_particle_daughter_list_type)(void*, int*, int);                    extern const pythia_particle_daughter_list_type pythia_particle_daughter_list;
      typedef void  (*pythia_particle_p4_type)(void*, double*, double*, double*, double*);      extern const pythia_particle_p4_type pythia_particle_p4;
      typedef double(*pythia_particle_p_mcalc_type)(void*);                                      extern const pythia_particle_p_mcalc_type pythia_particle_p_mcalc;
      typedef int   (*pythia_particle_id_abs_type)(void*);                                       extern const pythia_particle_id_abs_type pythia_particle_id_abs;
      typedef double(*pythia_particle_eta_type)(void*);                                          extern const pythia_particle_eta_type pythia_particle_eta;
      typedef double(*pythia_particle_px_type)(void*);                                           extern const pythia_particle_px_type pythia_particle_px;
      typedef double(*pythia_particle_py_type)(void*);                                           extern const pythia_particle_py_type pythia_particle_py;
      typedef double(*pythia_particle_pz_type)(void*);                                           extern const pythia_particle_pz_type pythia_particle_pz;
      typedef double(*pythia_particle_m_type)(void*);                                            extern const pythia_particle_m_type pythia_particle_m;
      typedef int   (*pythia_particle_mother1_type)(void*);                                      extern const pythia_particle_mother1_type pythia_particle_mother1;
      typedef int   (*pythia_particle_mother2_type)(void*);                                      extern const pythia_particle_mother2_type pythia_particle_mother2;

      typedef double(*pythia_info_sigma_gen_type)(void*);                                        extern const pythia_info_sigma_gen_type pythia_info_sigma_gen;
      typedef double(*pythia_info_sigma_gen_code_type)(void*, int);                               extern const pythia_info_sigma_gen_code_type pythia_info_sigma_gen_code;
      typedef double(*pythia_info_sigma_err_type)(void*);                                        extern const pythia_info_sigma_err_type pythia_info_sigma_err;
      typedef double(*pythia_info_sigma_err_code_type)(void*, int);                               extern const pythia_info_sigma_err_code_type pythia_info_sigma_err_code;
      typedef int   (*pythia_info_code_type)(void*);                                             extern const pythia_info_code_type pythia_info_code;
      typedef int   (*pythia_info_codes_hard_type)(void*, int*, int);                            extern const pythia_info_codes_hard_type pythia_info_codes_hard;

      typedef void* (*pythia_hepmc_writer_create_type)();                                        extern const pythia_hepmc_writer_create_type pythia_hepmc_writer_create;
      typedef void  (*pythia_hepmc_writer_destroy_type)(void*);                                  extern const pythia_hepmc_writer_destroy_type pythia_hepmc_writer_destroy;
      typedef void  (*pythia_hepmc_writer_init_type)(void*, const char*, int, int);               extern const pythia_hepmc_writer_init_type pythia_hepmc_writer_init;
      typedef void  (*pythia_hepmc_writer_write_event_hepmc2_type)(void*, void*);                 extern const pythia_hepmc_writer_write_event_hepmc2_type pythia_hepmc_writer_write_event_hepmc2;
      typedef void  (*pythia_hepmc_writer_write_event_hepmc3_type)(void*, void*);                 extern const pythia_hepmc_writer_write_event_hepmc3_type pythia_hepmc_writer_write_event_hepmc3;
      typedef void  (*pythia_hepmc_writer_convert_to_hepmc_event_type)(void*, void*, HepMC3::GenEvent*); extern const pythia_hepmc_writer_convert_to_hepmc_event_type pythia_hepmc_writer_convert_to_hepmc_event;
    }
  }
}

// Classes below live in the bare Pythia_8_312::Pythia8 namespace (not nested
// under Gambit::Backends) to match the convention BOSS-generated frontends
// use and that the rest of GAMBIT (module_functor_types.hpp,
// backend_functor_types.hpp, ColliderBit's Py8Collider_typedefs.hpp via
// Pythia_default) expects when referring to backend wrapper types directly.
namespace Pythia_8_312
{
  namespace Pythia8
  {
        /// Opaque, non-owning stand-in for Pythia8::Settings. Nothing in
        /// GAMBIT calls a method on this type -- it's only read off one
        /// Pythia instance and handed into another Pythia instance's
        /// constructor, so it needs no methods, just the right type identity.
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
        /// through Pythia::slhaInterface.slha. Exposes the one method
        /// ColliderBit calls on it.
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

        /// GAMBIT-side stand-in for Pythia8::SLHAinterface. Only reached
        /// through Pythia::slhaInterface, and only used for its .slha
        /// member, so no other method is wrapped.
        class SLHAinterface
        {
          public:
            explicit SLHAinterface(void* slha_handle) : slha(slha_handle) {}
            SusyLesHouches slha;
        };

        /// GAMBIT-side stand-in for Pythia8::Vec4, flattened to the four
        /// fields and one derived quantity (mCalc()) that
        /// Py8Utils.hpp actually reads -- see pythia_particle_p4() in
        /// pythia_shim.cpp.
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
        /// (Event::operator[]); never owns or frees that pointer.
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

            // Direct accessors, called on Particle directly by
            // EventConversionUtils.hpp/Py8EventConversions.hpp.
            int idAbs() const { return Gambit::Backends::Pythia_8_312::pythia_particle_id_abs(handle_); }
            double eta() const { return Gambit::Backends::Pythia_8_312::pythia_particle_eta(handle_); }
            double px() const { return Gambit::Backends::Pythia_8_312::pythia_particle_px(handle_); }
            double py() const { return Gambit::Backends::Pythia_8_312::pythia_particle_py(handle_); }
            double pz() const { return Gambit::Backends::Pythia_8_312::pythia_particle_pz(handle_); }
            double m() const { return Gambit::Backends::Pythia_8_312::pythia_particle_m(handle_); }
            int mother1() const { return Gambit::Backends::Pythia_8_312::pythia_particle_mother1(handle_); }
            int mother2() const { return Gambit::Backends::Pythia_8_312::pythia_particle_mother2(handle_); }

          private:
            template <typename Fn>
            std::vector<int> collectInts(Fn fn) const
            {
              // Generous fixed buffer; grow and retry only if it overflows.
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
        /// code default-constructs its own Events, clears/refills them
        /// every event, and copy-assigns Pythia's internal event into them.
        /// Owning instances use the default constructor/destructor;
        /// non-owning ones (wrapping a pointer into another object's
        /// storage, e.g. Pythia::event) use the private pointer+bool
        /// constructor and never call pythia_event_destroy.
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

            /// Only the 4-argument overload is ever called anywhere in
            /// GAMBIT, to dump a failed event into the debug log. Other
            /// real overloads (defaulting precision/ostream) are
            /// deliberately not wrapped.
            void list(bool show_scale_and_vertex, bool show_mothers_and_daughters, int precision, std::ostream& os) const
            {
              // pythia_event_list() returns the *true* length (like
              // snprintf), so grow and retry like motherList()/daughterList()
              // above. A real hadronic event's listing can exceed 20KB, so
              // start with a generous buffer.
              std::vector<char> buf(65536);
              int n = Gambit::Backends::Pythia_8_312::pythia_event_list(handle_, show_scale_and_vertex ? 1 : 0, show_mothers_and_daughters ? 1 : 0, precision, buf.data(), static_cast<int>(buf.size()));
              if (n >= static_cast<int>(buf.size()))
              {
                buf.resize(n + 1);
                Gambit::Backends::Pythia_8_312::pythia_event_list(handle_, show_scale_and_vertex ? 1 : 0, show_mothers_and_daughters ? 1 : 0, precision, buf.data(), static_cast<int>(buf.size()));
              }
              os << buf.data();
            }

            /// Non-owning constructor: wraps a pointer into another object's storage.
            explicit Event(void* non_owned_handle, bool /*tag*/) : handle_(non_owned_handle), owns_(false) {}

          private:
            void* handle_;
            bool owns_;
        };

        /// GAMBIT-side stand-in for Pythia8::Pythia -- a drop-in replacement
        /// for the BOSS-generated wrapper type that Py8Collider.hpp already
        /// uses. Exposes exactly the public data members and methods those
        /// call sites touch.
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
            /// GAMBIT_hepmc_writer (below) get at the underlying handle to
            /// pass back across the shim boundary.
            void* get_BEhandle() const { return handle_; }

            // Public data members, matching the real Pythia8::Pythia layout
            // that Py8Collider.hpp reads directly.
            //
            // handle_ is declared (and thus constructed) FIRST, even though
            // private and conceptually "belongs" after the public members:
            // C++ initializes members in declaration order, and each of
            // settings/particleData/slhaInterface/event/info is constructed
            // by calling a pythia_get_*(handle_) shim function on this very
            // handle. Declaring it after them compiled silently (only a
            // -Wreorder warning) but segfaulted inside pythia_get_info() on
            // first use, since those calls ran against a not-yet-initialized
            // handle_.
          private:
            void* handle_;

          public:
            Settings settings;
            ParticleData particleData;
            SLHAinterface slhaInterface;
            Event event; // non-owning view of Pythia's own internal event
            Info info;
        };

        /// GAMBIT-side stand-in for the GAMBIT-authored GAMBIT_hepmc_writer
        /// class (patched into Pythia's installed include tree; not part
        /// of Pythia's real API). See patch_pythia_8.312.dif.
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

#include "identification.hpp"

// Indicate which types this backend provides, so that
// SET_DEFAULT_VERSION_FOR_LOADING_TYPES below can typedef
// Pythia_default::Pythia8::X = Pythia_8_312::Pythia8::X for each one.
// "constructors" is left as an empty placeholder: unused for a hand-written
// frontend, which has no classloading factory dispatch to register.
#define Pythia_8_312_all_data \
  (( /*class*/(Pythia8)(GAMBIT_hepmc_writer), /*constructors*/((("",""),())) )) \
  (( /*class*/(Pythia8)(Pythia),              /*constructors*/((("",""),())) )) \
  (( /*class*/(Pythia8)(Event),                /*constructors*/((("",""),())) )) \
  (( /*class*/(Pythia8)(Particle),             /*constructors*/((("",""),())) )) \
  (( /*class*/(Pythia8)(Info),                 /*constructors*/((("",""),())) )) \
  (( /*class*/(Pythia8)(Settings),             /*constructors*/((("",""),())) )) \
  (( /*class*/(Pythia8)(ParticleData),         /*constructors*/((("",""),())) )) \
  (( /*class*/(Pythia8)(SusyLesHouches),       /*constructors*/((("",""),())) )) \
  (( /*class*/(Pythia8)(SLHAinterface),        /*constructors*/((("",""),())) )) \
  (( /*class*/(Pythia8)(Vec4),                 /*constructors*/((("",""),())) )) \

// If the default version has been loaded, set it as default.
#if ALREADY_LOADED(CAT_3(BACKENDNAME,_,CAT(Default_,BACKENDNAME)))
  SET_DEFAULT_VERSION_FOR_LOADING_TYPES(BACKENDNAME,SAFE_VERSION,CAT(Default_,BACKENDNAME))
#endif

// Undefine macros to avoid conflict with other backends.
#include "gambit/Backends/backend_undefs.hpp"

#endif

#endif /* __loaded_types_Pythia_8_312_hpp__ */
