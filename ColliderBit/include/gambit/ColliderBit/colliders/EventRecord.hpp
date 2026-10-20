//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  A generator-neutral event record: the information ColliderBit needs
///  from a hard-scattering event generator in order to build a
///  HEPUtils::Event (see colliders/EventConversion.hpp).
///
///  A generator plugin fills this record from its native event
///  (BaseCollider::last_event_to_record); ColliderBit's own code fills it
///  from HepMC events. The physics conventions that turn it into analysis
///  objects live in ColliderBit, so every generator is treated alike.
///
///  Part of the interface between ColliderBit and the generator plugins,
///  which are compiled outside GAMBIT; it depends only on the standard
///  library. Changing it changes the interface version in BaseCollider.hpp.
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

#include <vector>

namespace Gambit
{
  namespace ColliderBit
  {

    /// The record of one generated event.
    struct EventRecord
    {

      /// One entry of the record.
      struct Particle
      {
        /// PDG code
        int id = 0;
        /// Final-state particle
        bool is_final = false;
        /// Quark, gluon or diquark, by the generator's definition
        bool is_parton = false;
        /// Hadron, by the generator's definition
        bool is_hadron = false;
        /// Four-momentum, in GeV
        double px = 0, py = 0, pz = 0, e = 0;
        /// Mass assigned by the generator, in GeV
        double m = 0;
        /// The generator's two mother indices, if it has that notion (0 otherwise). Used only in diagnostics.
        int mother1 = 0, mother2 = 0;
        /// Indices of all mothers
        std::vector<int> mothers;
        /// Indices of all daughters
        std::vector<int> daughters;
      };

      /// The particles. Indices in mothers and daughters refer to this vector,
      /// and 0 means "none": entry 0 is never a real particle. Generators that
      /// have an entry for the event as a whole (like Pythia) put it there;
      /// otherwise it is left empty.
      std::vector<Particle> particles;

      void clear() { particles.clear(); }
      int size() const { return static_cast<int>(particles.size()); }
      const Particle& operator[](int i) const { return particles[i]; }
    };

  }
}
