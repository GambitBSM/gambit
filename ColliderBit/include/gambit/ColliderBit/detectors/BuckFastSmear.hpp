#pragma once

#include "gambit/ColliderBit/detectors/BaseDetector.hpp"

namespace Gambit {
  namespace ColliderBit {

    /// A base class for BuckFast simple smearing simulations within ColliderBit.
    struct BuckFastBase : BaseDetector<Pythia8::Event, HEPUtils::Event> {
      /// @name Event detection simulation.
      //@{
        bool partonOnly; ///< Chooses between parton only and full event conversion.
        double antiktR; ///< The jet radius used for the anti-kt jet clustering.
        /// A converter for a Pythia8::Event which considers all final state particles.
        /// @note Also performs the jet clustering algorithm.
        void convertPythia8ParticleEvent(const EventInType&, EventOutType&) const;
        /// A converter for a Pythia8::Event which considers only partonic final states.
        /// @note Also performs the jet clustering algorithm.
        void convertPythia8PartonEvent(const EventInType&, EventOutType&) const;
        /// Perform the BuckFast simple smearing on the next collider event by reference.
        virtual void processEvent(const EventInType&, EventOutType&) const = 0;
      //@}

      /// @name Construction, Destruction, and Recycling
      //@{
        BuckFastBase() : partonOnly(false), antiktR(0.4) { }
        virtual ~BuckFastBase() { }
      //@}

      /// @name (Re-)Initialization functions
      //@{
        /// Settings parsing and initialization for any sub-class.
        virtual void init(const std::vector<std::string>&) { };
        /// General init for any collider of this type - no settings version.
        virtual void init() { };
        /// Settings parsing and initialization for sub-classes with parton and jet radius settings only.
        void init(bool parton, double R) { partonOnly=parton; antiktR=R; };
      //@}
    };


    /// Simple ATLAS detector pseudo-simulation,
    /// applying event smearing and efficiencies.
    struct BuckFastSmearATLAS : BuckFastBase {
      /// @name Event detection simulation.
      //@{
        void processEvent(const EventInType&, EventOutType&) const;
      //@}

      /// @name Construction, Destruction, and Recycling
      //@{
        BuckFastSmearATLAS() { }
        ~BuckFastSmearATLAS() { }
      //@}
    };


    /// Simple ATLAS detector pseudo-simulation,
    /// applying only event smearing.
    struct BuckFastSmearATLASnoeff : BuckFastBase {
      /// @name Event detection simulation.
      //@{
        void processEvent(const EventInType&, EventOutType&) const;
      //@}

      /// @name Construction, Destruction, and Recycling
      //@{
        BuckFastSmearATLASnoeff() { }
        ~BuckFastSmearATLASnoeff() { }
      //@}
    };


    /// Simple CMS detector pseudo-simulation,
    /// applying event smearing and efficiencies.
    struct BuckFastSmearCMS : BuckFastBase {
      /// @name Event detection simulation.
      //@{
        void processEvent(const EventInType&, EventOutType&) const;
      //@}

      /// @name Construction, Destruction, and Recycling
      //@{
        BuckFastSmearCMS() { }
        ~BuckFastSmearCMS() { }
      //@}
    };


    /// Simple CMS detector pseudo-simulation,
    /// applying only event smearing.
    struct BuckFastSmearCMSnoeff : BuckFastBase {
      /// @name Event detection simulation.
      //@{
        void processEvent(const EventInType&, EventOutType&) const;
      //@}

      /// @name Construction, Destruction, and Recycling
      //@{
        BuckFastSmearCMSnoeff() { }
        ~BuckFastSmearCMSnoeff() { }
      //@}
    };


    /// Simple smearing functions as a detector pseudo-simulation.
    struct BuckFastIdentity : BuckFastBase {
      /// @name Event detection simulation.
      //@{
        void processEvent(const EventInType&, EventOutType&) const;
      //@}

      /// @name Construction, Destruction, and Recycling
      //@{
        BuckFastIdentity() { }
        ~BuckFastIdentity() { }
      //@}
    };

  }
}
