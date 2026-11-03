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

#include "gambit/ColliderBit/limits/BaseLimitContainer.hpp"

namespace Gambit
{
  namespace ColliderBit
  {

    BaseLimitContainer::~BaseLimitContainer()
    {
      // Clean up all the contours created when this object was constructed.
      for (auto it = _limitContours.begin(); it != _limitContours.end(); ++it)
      {
        delete it->second;
      }
    }

    double BaseLimitContainer::specialLimit(double, double) const
    {
      return std::numeric_limits<double>::infinity();
    }

    double BaseLimitContainer::limitAverage(double x, double y, double mZ) const
    {
      if (!isWithinExclusionRegion(x, y, mZ)) return specialLimit(x, y);
      const P2& point = P2(x, y);
      const LineSegment& externalLine = LineSegment(point, _externalPoint);
      P2 rayMaker;
      LineSegment ray, intersectLine;
      double r, rmin;
      double average, totalWeight, thisLimit, nextBestLimit;
      unsigned intersectCounter, index;

      // First, find the inner-most contour in which lies point.
      for (index=0; index<_limitValuesSorted.size(); index++) {
        intersectCounter = 0;
        thisLimit = _limitValuesSorted[index];
        for (auto segmentIter = _limitContours.at(index)->begin();
                  segmentIter != _limitContours.at(index)->end(); ++segmentIter)
          if (externalLine.intersectsAt(*segmentIter).r() < std::numeric_limits<double>::infinity())
            intersectCounter++;
        if (intersectCounter % 2) break;
        thisLimit = -1.;
      }

      if (thisLimit <= 0.)
        // If no such contour is found, return infinity.
        return std::numeric_limits<double>::infinity();
      else if (index == 0)
        // If the inner most contour is found, return that limit.
        return thisLimit;
      else
        // Otherwise, store the next best limit for the average.
        nextBestLimit = _limitValuesSorted[index-1];

      // Scan over all the angles around the current point to perform the average.
      average = 0.;
      totalWeight = 0.;
      for (double angle = 0.; angle < 2.*acos(-1); angle += acos(-1)/41.) {
        // Make a ray for each angle.
        rayMaker.setxy(1000. * cos(angle), 1000. * sin(angle));
        ray.init(point, point + rayMaker);

        // For each ray, look for intersections with the next best limit.
        rmin = std::numeric_limits<double>::infinity();
        for (auto segmentIter = _limitContours.at(index-1)->begin();
                  segmentIter != _limitContours.at(index-1)->end(); ++segmentIter) {
          intersectLine.init(point, ray.intersectsAt(*segmentIter));
          r = intersectLine.r();
          if (r <= rmin) rmin = r;
        }
        if (rmin == 0.) {
          totalWeight = -1.;
          average = nextBestLimit;
          break;
        } else {
          totalWeight += sqrt(1./rmin);
          average += sqrt(1./rmin) * nextBestLimit;
        }

        // For each ray, also look for intersections with the current limit.
        rmin = std::numeric_limits<double>::infinity();
        for (auto segmentIter = _limitContours.at(index)->begin();
                  segmentIter != _limitContours.at(index)->end(); ++segmentIter) {
          intersectLine.init(point, ray.intersectsAt(*segmentIter));
          r = intersectLine.r();
          if (r <= rmin) rmin = r;
        }
        if (rmin == 0.) {
          totalWeight = -1.;
          average = thisLimit;
          break;
        } else {
          totalWeight += sqrt(1./rmin);
          average += sqrt(1./rmin) * thisLimit;
        }
      }

      if (totalWeight > 0)
        return average / totalWeight;
      else
        return average;
    }

    /// @brief Dump limit average data into a file for average debugging
    void BaseLimitContainer::dumpPlotData(double xlow, double xhigh, double ylow,
                                          double yhigh, double mZ,
                                          std::string filename, int ngrid) const
    {
      double x,y;
      std::ofstream outFile(filename.c_str(), std::ofstream::trunc);
      for (int xi=0; xi<=ngrid; xi++) {
        x = xlow + (xhigh - xlow) * xi / ngrid;
        for (int yi=0; yi<=ngrid; yi++) {
          y = ylow + (yhigh - ylow) * yi / ngrid;
          outFile << x << " " << y << " " << limitAverage(x,y,mZ) << "\n";
        }
      }
      outFile.close();
    }

    /// @brief Dump input limit contour data into a file for limit debugging
    void BaseLimitContainer::dumpLightPlotData(std::string filename, int nperLine) const
    {
      P2 point;
      std::ofstream outFile(filename.c_str(), std::ofstream::trunc);
      for (auto limitIter = _limitContours.begin(); limitIter != _limitContours.end(); ++limitIter) {
        for (auto segmentIter = (*limitIter).second->begin();
                  segmentIter != (*limitIter).second->end(); ++segmentIter) {
          for (double t=0.; t<=1.; t+=1./nperLine) {
            point = (*segmentIter).getp1() * t + (*segmentIter).getp2() * (1. - t);
            outFile << point.getx() << " " << point.gety() << " "
                    << (*limitIter).first << "\n";
          }
        }
      }
      outFile.close();
    }


  }
}
