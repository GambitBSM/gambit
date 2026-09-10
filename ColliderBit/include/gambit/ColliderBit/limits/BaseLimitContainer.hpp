//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Base container class for LEP limits.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Abram Krislock
///          (a.m.b.krislock@fys.uio.no)
///  \date ????
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2016 Jan
///
///  *************************************

#pragma once

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "gambit/Elements/shared_types.hpp"
#include "gambit/ColliderBit/limits/PointsAndLines.hpp"

namespace Gambit
{
  namespace ColliderBit
  {

    /// @brief Factory function for lines
    inline LineSegment makeLine(const P2& pt1, const P2& pt2) { return LineSegment(pt1, pt2); }

    /// @brief Base class for experimental limit curve interpolation
    class BaseLimitContainer
    {

      /// @name Types and Storage
      //@{

      protected:
        typedef std::vector<P2> Corners;
        typedef std::vector<LineSegment> Contours;
        typedef Contours* ContoursPointer;
        typedef std::map<unsigned, Contours*> LimitContours;
        typedef std::pair<unsigned, Contours*> LimitContourEntry;

        /// @note Inherited classes must fill the following members:
        // The collection of all limit values, sorted from min limit to max limit
        std::vector<double> _limitValuesSorted;

        // The collection of all limit contours
        LimitContours _limitContours;

        // Some point external to all limit contours
        P2 _externalPoint;

      //@}

      /// @name Construction and Destruction
      //@{

      public:

        BaseLimitContainer() {}

        virtual ~BaseLimitContainer();

      //@}

      /// @name Point interpolation, conversion, and region checks
      //@{

      public:

        /// @brief Convert a point from pixel units to axis units, creating a P2
        virtual P2 convertPt(double x, double y) const = 0;

        /// @brief Check to see if the point is within the exclusion region
        virtual bool isWithinExclusionRegion(double x, double y, double mZ) const = 0;

        /// @brief Return the limit value outside of the exclusion region
        virtual double specialLimit(double, double) const;

        /// @brief Two-pi averaging interpolator to find limits between limit curves
        double limitAverage(double x, double y, double mZ) const;

        /// @brief Dump limit average data into a file for average debugging
        void dumpPlotData(double xlow, double xhigh, double ylow, double yhigh,
                          double mZ, std::string filename, int ngrid=100) const;

        /// @brief Dump input limit contour data into a file for limit debugging
        void dumpLightPlotData(std::string filename, int nperLine=20) const;

      //@}
    };

  }
}
