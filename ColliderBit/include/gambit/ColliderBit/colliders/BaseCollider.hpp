//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  The interface between ColliderBit and a hard-scattering event generator.
///
///  BaseCollider is implemented outside GAMBIT, in a plugin library
///  compiled against the generator itself (for Pythia:
///  Backends/src/frontends/plugins/pythia_plugin.cpp). GAMBIT loads the
///  plugin as a backend and obtains instances through the backend function
///  create_collider. Nothing in GAMBIT includes a generator header, so
///  GAMBIT and ColliderBit build without the generator being present.
///
///  The generator's job ends at handing over its event as a generator-
///  neutral EventRecord (colliders/EventRecord.hpp). Turning that into a
///  HEPUtils::Event, with ColliderBit's conventions for prompt particles,
///  jets and tagging, is ColliderBit's job (colliders/EventConversion.hpp),
///  so that every generator is treated alike.
///
///  Rules for this header: it is compiled both by GAMBIT and by the
///  plugins, so it may only include the standard library, EventRecord.hpp
///  and the GAMBIT contrib headers SLHAea and HepMC3. Any change to the
///  class, or to EventRecord, must be accompanied by a bump of
///  COLLIDERBIT_COLLIDER_INTERFACE_VERSION: a plugin reports the version
///  it was built with, and GAMBIT refuses a mismatch at startup.
///
///  Error handling: no exception may cross the plugin boundary. Methods
///  that can fail return false and leave a description in last_error().
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

#pragma once

#include <ostream>
#include <string>
#include <vector>

#include "SLHAea/slhaea.h"
#include "gambit/ColliderBit/colliders/EventRecord.hpp"

// No forward declaration of HepMC3::GenEvent here: GAMBIT's type harvester
// cannot cope with foreign namespaces in a type header, so the real header
// is included instead. In a GAMBIT build without HepMC the HepMC-related
// method is absent; no generator plugin exists in that case.
#ifndef EXCLUDE_HEPMC
  #include "HepMC3/GenEvent.h"
#endif

/// Version of the BaseCollider interface (including EventRecord); see the file comment.
#define COLLIDERBIT_COLLIDER_INTERFACE_VERSION 3

namespace Gambit
{
  namespace ColliderBit
  {

    /// An abstract base class for collider simulators within ColliderBit.
    class BaseCollider
    {
      public:

        virtual ~BaseCollider() {}

        /// @name Initialisation
        ///@{

        /// Print the generator's banner.
        virtual void banner() = 0;

        /// Discard the current working instance, keeping whatever can be reused for the next init.
        virtual void clear() = 0;

        /// Initialise for a new parameter point, with the given generator settings
        /// and, optionally, an SLHAea object holding the spectrum and decays (may be
        /// nullptr). Returns false if the generator could not initialise.
        virtual bool init(const std::vector<std::string>& settings, const SLHAea::Coll* slha) = 0;

        ///@}

        /// @name Event generation
        ///@{

        /// Generate the next event. Returns false if generation failed; the failed
        /// record can still be printed with list_last_event.
        virtual bool next_event() = 0;

        /// Fill a generator-neutral record of the most recently generated event.
        virtual bool last_event_to_record(EventRecord& record) const = 0;

        #ifndef EXCLUDE_HEPMC
          /// Convert the most recently generated event to a HepMC3 event.
          virtual bool last_event_to_HepMC(HepMC3::GenEvent& event) const = 0;
        #endif

        /// Print the record of the most recently generated event (for debugging).
        virtual void list_last_event(std::ostream& os) const = 0;

        /// Open HepMC output files (filename plus "2" and/or "3") for write_last_event_to_HepMC_files.
        virtual bool open_HepMC_files(const std::string& filename, bool hepmc2, bool hepmc3) = 0;

        /// Append the most recently generated event to the open HepMC output files.
        virtual bool write_last_event_to_HepMC_files() = 0;

        /// Flush and close the HepMC output files, writing their footers. Safe to call when no files are open.
        virtual bool close_HepMC_files() = 0;

        ///@}

        /// @name Cross sections and process codes
        ///@{

        /// Upper estimate of the total cross section (in fb), available after init.
        virtual double max_xsec_fb() const = 0;

        /// Report the total or process-specific cross section (in fb or pb).
        virtual double xsec_fb() const = 0;
        virtual double xsec_fb(int) const = 0;
        virtual double xsec_pb() const = 0;
        virtual double xsec_pb(int) const = 0;

        /// Report the uncertainty in the total or process-specific cross section (in fb or pb).
        virtual double xsecErr_fb() const = 0;
        virtual double xsecErr_fb(int) const = 0;
        virtual double xsecErr_pb() const = 0;
        virtual double xsecErr_pb(int) const = 0;

        /// Report an integer process code for the last generated event
        virtual int process_code() const = 0;

        /// Report the list of all active process codes
        virtual std::vector<int> all_active_process_codes() const = 0;

        ///@}

        /// Description of the most recent failure.
        virtual std::string last_error() const = 0;
    };

  }
}
