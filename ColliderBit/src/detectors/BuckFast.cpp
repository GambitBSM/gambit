//   GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  BuckFast smearing functions.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Andy Buckley
///  \author Abram Krislock
///  \author Anders Kvellestad
///  \author Pat Scott
///  \author Martin White
///
///  *********************************************

#include "gambit/ColliderBit/detectors/BuckFast.hpp"

namespace Gambit
{

  namespace ColliderBit
  {

    /// Process an event with BuckFast
    void BuckFast::processEvent(HEPUtils::Event& event) const
    {
      // Electron smearing
      /// @todo Run-dependence?
      if (smearElectronEnergy != NULL) smearElectronEnergy(event.electrons());

      // Muon smearing
      /// @todo Run-dependence?
      if (smearMuonMomentum != NULL) smearMuonMomentum(event.muons());

      // Smear taus
      if (smearTaus != NULL) smearTaus(event.taus());

      // Smear jet momenta
      if (smearJets != NULL) smearJets(event.jets());

      // Unset b-tags outside |eta|=2.5
      for (HEPUtils::Jet* j : event.jets())
      {
        if (j->abseta() > 2.5) j->set_btag(false);
      }
    }

  }

}
