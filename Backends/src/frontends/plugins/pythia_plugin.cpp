//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Pythia 8 implementation of ColliderBit's BaseCollider interface.
///
///  This file is compiled against Pythia, as a step of the Pythia backend
///  build (cmake/backends.cmake), into libpythia_plugin.so, which GAMBIT
///  loads as the Pythia backend. GAMBIT itself never sees a Pythia header:
///  it talks to the generator only through the abstract interface in
///  ColliderBit/include/gambit/ColliderBit/colliders/BaseCollider.hpp, and
///  obtains instances through the two functions exported here:
///
///    int gambit_collider_interface_version();
///    Gambit::ColliderBit::BaseCollider* gambit_create_collider();
///
///  The plugin hands events over as ColliderBit's generator-neutral
///  EventRecord; turning them into HEPUtils events is ColliderBit's job.
///  No exception leaves this library: every method that can fail returns
///  false and stores a message for last_error().
///
///  See Backends/src/frontends/plugins/README.md.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Abram Krislock
///  \date July 2016
///
///  \author Pat Scott
///  \date Jan 2019
///
///  \author The GAMBIT Collaboration
///  \date 2026 Oct
///
///  *********************************************

#include "gambit/ColliderBit/colliders/BaseCollider.hpp"

#include "Pythia8/Pythia.h"
#include "Pythia8Plugins/HepMC3.h"
#include "HepMC3/GenEvent.h"
#include "HepMC3/WriterAscii.h"
#include "HepMC3/WriterAsciiHepMC2.h"
#include "SLHAea/slhaea.h"

#include <dlfcn.h>

#include <exception>
#include <memory>
#include <ostream>
#include <stdexcept>
#include <string>
#include <vector>

#define GAMBIT_PLUGIN_EXPORT __attribute__((visibility("default")))

extern "C"
{
  GAMBIT_PLUGIN_EXPORT int gambit_collider_interface_version();
  GAMBIT_PLUGIN_EXPORT Gambit::ColliderBit::BaseCollider* gambit_create_collider();
}

namespace
{

  /// Pythia's xmldoc directory, located relative to this library:
  /// <install>/lib/libpythia_plugin.so and <install>/share/Pythia8/xmldoc.
  std::string xmldoc_dir()
  {
    Dl_info info;
    if (dladdr(reinterpret_cast<void*>(&gambit_create_collider), &info) == 0 || info.dli_fname == nullptr)
    {
      throw std::runtime_error("Could not determine the location of the Pythia plugin library.");
    }
    const std::string path = info.dli_fname;
    const std::string::size_type slash = path.rfind('/');
    const std::string libdir = (slash == std::string::npos) ? std::string(".") : path.substr(0, slash);
    return libdir + "/../share/Pythia8/xmldoc";
  }


  /// Pythia 8 as a ColliderBit collider.
  ///
  /// Mirrors how ColliderBit has always driven Pythia: a base instance, created
  /// once from the xmldoc directory, receives the settings; for every parameter
  /// point a working instance is constructed from the base instance's settings
  /// and particle data, given the SLHA input, fed the settings again (to pick up
  /// changes to the Standard Model decay tables) and initialised.
  class PythiaCollider : public Gambit::ColliderBit::BaseCollider
  {
    public:

      PythiaCollider() = default;
      ~PythiaCollider() override = default;

      void banner() override
      {
        guarded([&]{ Pythia8::Pythia banner_instance(xmldoc_dir(), true); });
      }

      void clear() override
      {
        instance_.reset();
        has_event_ = false;
        event_number_ = -1;
        hepmc_event_number_ = -1;
        hepmc_numbered_event_ = -2;
      }

      bool init(const std::vector<std::string>& settings, const SLHAea::Coll* slha) override
      {
        has_event_ = false;
        event_number_ = -1;
        hepmc_event_number_ = -1;
        hepmc_numbered_event_ = -2;
        return guarded([&]
        {
          if (!base_) base_ = std::make_unique<Pythia8::Pythia>(xmldoc_dir(), false);
          for (const std::string& command : settings) base_->readString(command);

          // The working instance starts from the base instance's settings and particle
          // data (Pythia copies both). The banner was printed by banner() already.
          instance_ = std::make_unique<Pythia8::Pythia>(base_->settings, base_->particleData, false);
          if (slha != nullptr) instance_->slhaInterface.slha.setSLHAea(slha);

          // Read the settings again, to get the SM decay table changes from the yaml file
          for (const std::string& command : settings) instance_->readString(command);

          if (!instance_->init()) throw std::runtime_error("Pythia could not initialize.");
        });
      }

      bool next_event() override
      {
        has_event_ = false;
        if (!instance_)
        {
          last_error_ = "Pythia has not been initialised.";
          return false;
        }
        const bool ok = guarded([&]{ has_event_ = instance_->next(); });
        if (ok && has_event_) ++event_number_;
        if (ok && !has_event_) last_error_ = "Pythia could not make the next event.";
        return ok && has_event_;
      }

      bool last_event_to_record(Gambit::ColliderBit::EventRecord& record) const override
      {
        return guarded([&]
        {
          require_event();
          const Pythia8::Event& event = instance_->event;
          record.particles.resize(event.size());
          for (int i = 0; i < event.size(); ++i)
          {
            const Pythia8::Particle& p = event[i];
            Gambit::ColliderBit::EventRecord::Particle& r = record.particles[i];
            r.id = p.id();
            r.is_final = p.isFinal();
            r.is_parton = p.isParton();
            r.is_hadron = p.isHadron();
            r.px = p.px();
            r.py = p.py();
            r.pz = p.pz();
            r.e = p.e();
            r.m = p.m();
            r.mother1 = p.mother1();
            r.mother2 = p.mother2();
            r.mothers = p.motherList();
            r.daughters = p.daughterList();
          }
        });
      }

      bool last_event_to_HepMC(HepMC3::GenEvent& event) const override
      {
        return guarded([&]
        {
          require_event();
          fill_hepmc_event(event);
        });
      }

      void list_last_event(std::ostream& os) const override
      {
        if (instance_) instance_->event.list(false, false, 1, os);
      }

      bool open_HepMC_files(const std::string& filename, bool hepmc2, bool hepmc3) override
      {
        return guarded([&]
        {
          if (hepmc2) hepmc2_file_ = std::make_unique<HepMC3::WriterAsciiHepMC2>(filename + "2");
          if (hepmc3) hepmc3_file_ = std::make_unique<HepMC3::WriterAscii>(filename + "3");
        });
      }

      bool write_last_event_to_HepMC_files() override
      {
        return guarded([&]
        {
          require_event();
          HepMC3::GenEvent event(HepMC3::Units::GEV, HepMC3::Units::MM);
          fill_hepmc_event(event);
          if (hepmc2_file_) hepmc2_file_->write_event(event);
          if (hepmc3_file_) hepmc3_file_->write_event(event);
        });
      }

      bool close_HepMC_files() override
      {
        return guarded([&]
        {
          if (hepmc2_file_) { hepmc2_file_->close(); hepmc2_file_.reset(); }
          if (hepmc3_file_) { hepmc3_file_->close(); hepmc3_file_.reset(); }
        });
      }

      double max_xsec_fb() const override { return instance_ ? instance_->getSigmaMaxSum() * 1e12 : 0.0; }

      double xsec_fb() const override { return instance_->info.sigmaGen() * 1e12; }
      double xsec_fb(int process_code) const override { return instance_->info.sigmaGen(process_code) * 1e12; }
      double xsec_pb() const override { return instance_->info.sigmaGen() * 1e9; }
      double xsec_pb(int process_code) const override { return instance_->info.sigmaGen(process_code) * 1e9; }

      double xsecErr_fb() const override { return instance_->info.sigmaErr() * 1e12; }
      double xsecErr_fb(int process_code) const override { return instance_->info.sigmaErr(process_code) * 1e12; }
      double xsecErr_pb() const override { return instance_->info.sigmaErr() * 1e9; }
      double xsecErr_pb(int process_code) const override { return instance_->info.sigmaErr(process_code) * 1e9; }

      int process_code() const override { return instance_->info.code(); }

      std::vector<int> all_active_process_codes() const override { return instance_->info.codesHard(); }

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

      void require_event() const
      {
        if (!instance_ || !has_event_) throw std::runtime_error("No event has been generated.");
      }

      void fill_hepmc_event(HepMC3::GenEvent& event) const
      {
        // HepMC event numbers count the distinct events converted since init(), starting at 0,
        // so converting the same event twice (e.g. once for Rivet and once for a HepMC file)
        // does not skip numbers.
        if (hepmc_numbered_event_ != event_number_)
        {
          hepmc_numbered_event_ = event_number_;
          ++hepmc_event_number_;
        }
        if (!hepmc_converter_.fill_next_event(instance_->event, &event, static_cast<int>(hepmc_event_number_), &instance_->info))
        {
          throw std::runtime_error("Pythia8ToHepMC3 could not convert the event.");
        }
      }

      std::unique_ptr<Pythia8::Pythia> base_;
      std::unique_ptr<Pythia8::Pythia> instance_;
      bool has_event_ = false;
      long event_number_ = -1;  // index of the last generated event since init()
      mutable long hepmc_event_number_ = -1;   // HepMC event number of the last converted event
      mutable long hepmc_numbered_event_ = -2; // event_number_ of the last converted event
      mutable HepMC3::Pythia8ToHepMC3 hepmc_converter_;
      std::unique_ptr<HepMC3::WriterAsciiHepMC2> hepmc2_file_;
      std::unique_ptr<HepMC3::WriterAscii> hepmc3_file_;
      mutable std::string last_error_;
  };

}

extern "C"
{

  int gambit_collider_interface_version()
  {
    return COLLIDERBIT_COLLIDER_INTERFACE_VERSION;
  }

  Gambit::ColliderBit::BaseCollider* gambit_create_collider()
  {
    try { return new PythiaCollider(); }
    catch (...) { return nullptr; }
  }

}
