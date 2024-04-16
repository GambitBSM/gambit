//   GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  BuckFast simple smearing detector sim.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Andy Buckley
///  \author Anders Kvellestad
///  \author Pat Scott
///  \author Martin White
///
///  *********************************************

#pragma once

#include "gambit/ColliderBit/detectors/BaseDetector.hpp"

#include "HEPUtils/Event.h"
#include "HEPUtils/Particle.h"
#include "HEPUtils/Jet.h"

namespace Gambit
{

  namespace ColliderBit
  {

    /// A base class for BuckFast simple smearing simulations within ColliderBit.
    class BuckFast : public BaseDetector
    {

      public:

        /// Pointers to actual detector response functions
        /// @{
        void(*smearElectronEnergy)(std::vector<HEPUtils::Particle*>&);
        void(*smearMuonMomentum)(std::vector<HEPUtils::Particle*>&);
        void(*smearTaus)(std::vector<HEPUtils::Particle*>&);
        void(*smearJets)(std::vector<HEPUtils::Jet*>&);
        /// @}

        /// Process an event with BuckFast
        void processEvent(HEPUtils::Event&) const;

        ///@}

        /// Constructor
        BuckFast() : smearElectronEnergy(NULL)
                   , smearMuonMomentum(NULL)
                   , smearTaus(NULL)
                   , smearJets(NULL)
        {}

        /// Destructor
        virtual ~BuckFast() {}

        /// @name (Re-)Initialization functions
        ///@{

        /// Settings parsing and initialization for any sub-class.
        virtual void init(const std::vector<std::string>&) {};

        /// General init for any collider of this type.
        virtual void init() {};

        ///@}

    };

  }
}
