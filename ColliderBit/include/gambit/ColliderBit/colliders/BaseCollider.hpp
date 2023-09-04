//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  The BaseCollider class.
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
///  *********************************************

#pragma once

#include <string>
#include <vector>

namespace Gambit
{
  namespace ColliderBit
  {

    /// An abstract base class for collider simulators within ColliderBit.
    class BaseCollider
    {

      public:

        /// Constructor
        BaseCollider() : partonOnly(false), antiktR(0.4) {}
        /// Destructor
        virtual ~BaseCollider() {}
        /// Reset this instance for reuse, avoiding the need for "new" or "delete".
        virtual void clear() {}

        /// @name Event generation and cross section functions:
        ///@{
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

        /// @name (Re-)Initialization functions:
        ///@{
        /// General init for any collider of this type.
        virtual void init(const std::vector<std::string>&) {}
        /// General init for any collider of this type - no settings version.
        virtual void init() {}
        ///@}

        /// Flag indicating if events from this collider should be processed as parton-only or full events
        bool partonOnly;
        ///The jet radius used for the anti-kt jet clustering.
        double antiktR;

    };

  }
}
