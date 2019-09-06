//   GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///
///  \file
///  Utilities for working with Pythia8 events.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Andy Buckley
///  \author Abram Krislock
///  \author Anders Kvellestad
///
///  *********************************************


#pragma once

#include "HEPUtils/Event.h"
#include "HEPUtils/Vectors.h"
#include "HEPUtils/FastJet.h"
#include "MCUtils/PIDUtils.h"

namespace Gambit
{

  namespace ColliderBit
  {

    /// @name Converters to/from Pythia8's native 4-vector
    ///@{

    template<typename Vec4T>
    inline FJNS::PseudoJet mk_pseudojet(const Vec4T& p)
    {
      return FJNS::PseudoJet(p.px(), p.py(), p.pz(), p.e());
    }

    template<typename Vec4T>
    inline HEPUtils::P4 mk_p4(const Vec4T& p)
    {
      const double m = p.mCalc();
      if (m < -5e-3) throw std::domain_error("Negative mass vector from Pythia8");
      return HEPUtils::P4::mkXYZM(p.px(), p.py(), p.pz(), (m > 0) ? m : 0);
    }

    ///@}


    /// @name Detailed Pythia8 event record walking/mangling functions
    ///@{


    /// @todo Rewrite using the Pythia > 8.176 particle-based methods
    template<typename EventT>
    inline bool fromBottom(int n, const EventT& evt)
    {
      // Root particle is invalid
      if (n == 0) return false;
      const auto& p = evt[n];
      if (abs(p.id()) == 5 || MCUtils::PID::hasBottom(p.id())) return true;
      /// @todo What about partonic decays?
      if (p.isParton()) return false; // stop the walking at hadron level
      for (int m : p.motherList()) {
        if (fromBottom(m, evt)) return true;
      }
      return false;
    }


    /// @todo Rewrite using the Pythia > 8.176 particle-based methods
    template<typename EventT>
    inline bool fromTau(int n, const EventT& evt)
    {
      // Root particle is invalid
      if (n == 0) return false;
      const auto& p = evt[n];
      if (abs(p.id()) == 15) return true;
      if (p.isParton()) return false; // stop the walking at the end of the hadron level
      for (int m : p.motherList()) {
        if (fromTau(m, evt)) return true;
      }
      return false;
    }


    /// @todo Rewrite using the Pythia > 8.176 particle-based methods
    template<typename EventT>
    inline bool fromHadron(int n, const EventT& evt)
    {
      // Root particle is invalid
      if (n == 0) return false;
      const auto& p = evt[n];
      if (p.isHadron()) return true;
      if (p.isParton()) return false; // stop the walking at the end of the hadron level
      for (int m : p.motherList()) {
        if (fromHadron(m, evt)) return true;
      }
      return false;
    }


    template<typename EventT>
    inline bool isFinalB(int n, const EventT& evt)
    {
      // Root particle is invalid
      if (n == 0) return false;
      // *This* particle must be a b or b-hadron
      if (!MCUtils::PID::hasBottom(evt[n].id())) return false;
      // Daughters must *not* include a b or b-hadron
      for (int m : evt.daughterList(n)) {
        if (MCUtils::PID::hasBottom(evt[m].id())) return false;
      }
      return true;
    }


    template<typename EventT>
    inline bool isFinalTau(int n, const EventT& evt)
    {
      // Root particle is invalid
      if (n == 0) return false;
      // *This* particle must be a tau
      if (abs(evt[n].id()) != 15) return false;
      // Daughters must *not* include a tau
      for (int m : evt.daughterList(n)) {
        if (abs(evt[m].id()) == 15) return false;
      }
      return true;
    }


    template<typename EventT>
    inline bool isParton(int n, const EventT& evt)
    {
      // Root particle is invalid
      if (n == 0) return false;
      // This particle must be a parton (could use Py8 P::isParton() + apid == 6?)
      int apid = abs(evt[n].id());
      if (!HEPUtils::in_closed_range(apid, 1, 6) && apid != 21) return false;
      return true;
    }


    template<typename EventT>
    inline bool isFinalParton(int n, const EventT& evt)
    {
      // Root particle is invalid
      if (n == 0) return false;
      // Check if it's a parton at all & early exit
      if (!isParton(n, evt)) return false;
      // Daughters must *not* be partons
      for (int m : evt.daughterList(n)) {
        if (m == 0) continue; // 0 shouldn't be possible here, but just to be sure...
        if (isParton(m, evt)) return false;
      }
      return true;
    }


    template<typename EventT>
    inline bool isFinalPhoton(int n, const EventT& evt)
    {
      // Root particle is invalid
      if (n == 0) return false;
      const auto& p = evt[n];
      // Check if it's a photon at all & early exit
      if (p.id() != 22) return false;
      // Must have no daughters
      return evt.daughterList(n).empty();
    }


    template<typename EventT>
    inline bool isFinalLepton(int n, const EventT& evt)
    {
      // Root particle is invalid
      if (n == 0) return false;
      const auto& p = evt[n];
      // Check if it's a lepton at all (including taus and neutrinos) & early exit
      if (!HEPUtils::in_closed_range(abs(p.id()), 11, 16)) return false;
      // Must have no daughters
      return evt.daughterList(n).empty();
    }

    ///@}

  }
}
