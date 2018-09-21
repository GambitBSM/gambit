#pragma once
#include "gambit/ColliderBit/limits/BaseLimitContainer.hpp"

namespace Gambit
{
  namespace ColliderBit 
  {
    /// @brief A class to contain the limit data from OPAL, hep-ex/0210043, figure 5a (in colour)
    class OPALDegenerateCharginoLimitAt208GeV : public BaseLimitContainer {

      //@{
      public:

        P2 convertPt(double, double) const;

        /// @read off the csv file containting the data
        std::vector<P2> dataFromLimit(double);

        /// @brief Check to see if the point is within the exclusion region
        bool isWithinExclusionRegion(double x, double y, double) const;
      //@}

      //@{
      public:
        /// @name Construction, initializing with all necessary data from the plot
        OPALDegenerateCharginoLimitAt208GeV();
      //@}
    };

  }
}
