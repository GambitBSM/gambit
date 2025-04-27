#include "gambit/cmake/cmake_variables.hpp"
#ifndef EXCLUDE_ROOT
///
///  \author Roberto Ruiz
///  \date 2023 October
///
///  *********************************************

#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>

#include "gambit/Utils/threadsafe_rng.hpp"
#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"
#include "gambit/ColliderBit/mt2_bisect.h"
#include "gambit/ColliderBit/MVA.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "HEPUtils/FastJet.h"
#include "TRandom3.h"

// #define CHECK_CUTFLOW

using namespace std;

// Renamed from: 
//        Analysis_ATLAS_13TeV_2LEP0JET_EW_139invfb

// Based on EW regions of https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/PAPERS/NA-SUSY-2019-02-PAPER.pdf
// Luminosity: 139 fb^-1
// Note that this uses the ATLAS object-based met significance

// Old Analysis Name: ATLAS_13TeV_2LEP0JET_EW_139invfb

namespace Gambit
{
  namespace ColliderBit
  {

    bool sortBypT_j(const Jet* jet1, const Jet* jet2) { return (jet1->pT() > jet2->pT()); }
    bool sortBypT_l(const Particle* lep1, const Particle* lep2) { return (lep1->pT() > lep2->pT()); }

    static void rotateXY(TMatrix &mat, TMatrix &mat_new, double phi)
    {
      double c = cos(phi);
      double s = sin(phi);
      double cc = c * c;
      double ss = s * s;
      double cs = c * s;

      mat_new(0, 0) = mat(0, 0) * cc + mat(1, 1) * ss - cs * (mat(1, 0) + mat(0, 1));
      mat_new(0, 1) = mat(0, 1) * cc - mat(1, 0) * ss + cs * (mat(0, 0) - mat(1, 1));
      mat_new(1, 0) = mat(1, 0) * cc - mat(0, 1) * ss + cs * (mat(0, 0) - mat(1, 1));
      mat_new(1, 1) = mat(0, 0) * ss + mat(1, 1) * cc + cs * (mat(1, 0) + mat(0, 1));
    }

    struct EllipseParams
    {
      // Constructor for non-degenerate ellipses:
      /*
       * Ellipse is represented algebraically by:
       * c_xx x^2 + 2 c_xy x y + c_yy y^2 + 2 c_x x + 2 c_y y + c = 0.
      */
      EllipseParams(const double c_xx2, const double c_yy2, const double c_xy2,
                    const double c_x2, const double c_y2, const double c2)
                  : c_xx(c_xx2), c_yy(c_yy2), c_xy(c_xy2), c_x(c_x2), c_y(c_y2), c(c2)
      {
        // Etayo et al REQUIRE that c_xx and c_yy are non-negative, so:
        if (c_xx < 0 || c_yy < 0)
        {
          throw "precondition violation";
        }
        setDet();
      }
      
      EllipseParams() {}
      
      void setDet()
      {
        det = (2.0 * c_x * c_xy * c_y + c * c_xx * c_yy - c_yy * c_x * c_x -
               c * c_xy * c_xy - c_xx * c_y * c_y);
      }
      
      // Consstructor for degenerate ellipse (i.e. a "dot" at (x0,y0) ).
      EllipseParams(const double x0, const double y0) : c_xx(1), c_yy(1), c_xy(0), c_x(-x0), c_y(-y0), c(x0 * x0 + y0 * y0), det(0) {}
                  
      double lesterFactor(const EllipseParams &e2) const
      {
        const EllipseParams &e1 = *this;
        const double ans =
        e1.c_xx * e1.c_yy * e2.c + 2.0 * e1.c_xy * e1.c_y * e2.c_x -
        2.0 * e1.c_x * e1.c_yy * e2.c_x + e1.c * e1.c_yy * e2.c_xx -
        2.0 * e1.c * e1.c_xy * e2.c_xy + 2.0 * e1.c_x * e1.c_y * e2.c_xy +
        2.0 * e1.c_x * e1.c_xy * e2.c_y - 2.0 * e1.c_xx * e1.c_y * e2.c_y +
        e1.c * e1.c_xx * e2.c_yy - e2.c_yy * (e1.c_x * e1.c_x) -
        e2.c * (e1.c_xy * e1.c_xy) - e2.c_xx * (e1.c_y * e1.c_y);
        return ans;
      }

      bool operator==(const EllipseParams &other) const
      {
        return c_xx == other.c_xx && c_yy == other.c_yy && c_xy == other.c_xy &&
               c_x == other.c_x && c_y == other.c_y && c == other.c;
      }

      public:
        // Data
        double c_xx;
        double c_yy;
        double c_xy; // note factor of 2 above
        double c_x;  // note factor of 2 above
        double c_y;  // note factor of 2 above
        double c;
        double det; // The determinant of the 3x3 conic matrix
    };

    // This is the interface: users should call this function:
    bool ellipsesAreDisjoint(const EllipseParams &e1, const EllipseParams &e2);

    // This is an implementation thing: users should not call it:
    bool __private_ellipsesAreDisjoint(const double coeffLamPow3, const double coeffLamPow2, const double coeffLamPow1, const double coeffLamPow0);

    bool ellipsesAreDisjoint(const EllipseParams &e1, const EllipseParams &e2)
    {
      /* We want to construct the polynomial "Det(lamdba A + B)" where A and B are
         the 3x3 matrices associated with e1 and e2, and we want to get that polynomial
         in the form lambda^3 + a lambda^2 + b lambda + c.


         Note that by default we will not have unity as the coefficient of the lambda^3
         term, however the redundancy in the parametrisation of A and B allows us to
         scale the whole ply until the first term does have a unit coefficient.
      */

      if (e1 == e2)
      {
        return false; // Probably won't catch many cases, but may as well have it here.
      }

      // first get unscaled terms:
      const double coeffLamPow3 = e1.det; // Note that this is the determinant of the symmetric matrix associated with e1.
      const double coeffLamPow2 = e1.lesterFactor(e2);
      const double coeffLamPow1 = e2.lesterFactor(e1);
      const double coeffLamPow0 = e2.det; // Note that this is the determinant of the symmetric matrix associated with e2.

      // Since question is "symmetric" and since we need to dovide by coeffLamPow3
      // ... do this the way round that involves dividing by the largest number:

      if (fabs(coeffLamPow3) >= fabs(coeffLamPow0))
      {
        return __private_ellipsesAreDisjoint(coeffLamPow3, coeffLamPow2, coeffLamPow1, coeffLamPow0); // normal order
      }
      else
      {
        return __private_ellipsesAreDisjoint(coeffLamPow0, coeffLamPow1,coeffLamPow2,coeffLamPow3); // reversed order
      }
    }

    bool __private_ellipsesAreDisjoint(const double coeffLamPow3,
                                       const double coeffLamPow2,
                                       const double coeffLamPow1,
                                       const double coeffLamPow0)
    {

      // precondition of being called:
      // assert(fabs(coeffLamPow3)>=fabs(coeffLamPow0));

      if (coeffLamPow3 == 0)
      {
        // The ellipses were singular in some way.
        // Cannot determine whether they are overlapping or not.
        throw 1;
      }

      // now scale terms to monomial form:
      const double a = coeffLamPow2 / coeffLamPow3;
      const double b = coeffLamPow1 / coeffLamPow3;
      const double c = coeffLamPow0 / coeffLamPow3;

      // Use the main result of the above paper:
      const double thing1 = -3.0 * b + a * a;
      if (thing1 <= 0) return false;
      const double thing2 = -27.0 * c * c + 18.0 * c * a * b + a * a * b * b -
                        4.0 * a * a * a * c - 4.0 * b * b * b;
      if (thing2 <= 0) return false;

      // ans true means ellipses are disjoint:
      const bool ans =
        ((a >= 0 /*&& thing1 > 0*/ &&
        3.0 * a * c + b * a * a - 4.0 * b * b < 0 /*&& thing2 > 0*/) ||
        (a < 0 /*&& thing1 > 0*/ /*&& thing2 > 0*/));
      return ans;
    }

    class asymm_mt2_lester_bisect
    {
      public:
        static const int MT2_ERROR = -1;

        // returns asymmetric mT2 (which is >=0), or returns a negative
        // number (such as MT2_ERROR) in the case of an error.
        // desiredPrecisionOnMT2 must be non-negative.  If set to zero (default) MT2 will be
        // calculated to the highest precision available on the machine (or
        // as close to that as the algorithm permits).  If set to a
        // positive value, MT2 (note that is MT2, not its square) will be
        // calculated to within +- desiredPrecisionOnMT2. Note that by
        // requesting precision of +- 0.01 GeV on an MT2 value of 100 GeV
        // can result in speedups of a factor of ...
        // If useDeciSectionsInitially is true, interval is cut at the 10% point until first
        // acceptance, which gives factor 3 increase in speed calculating
        // kinematic min, but 3% slowdown for events in the bulk.  Is on
        // (true) by default, but can be turned off by setting to false.
        static double get_mT2( const double mVis1, const double pxVis1, const double pyVis1,
                               const double mVis2, const double pxVis2, const double pyVis2,
                               const double pxMiss, const double pyMiss, const double mInvis1,
                               const double mInvis2,
                               const double desiredPrecisionOnMT2 = 0,
                               const bool useDeciSectionsInitially = true)
        {

          const double mT2_Sq = get_mT2_Sq( mVis1, pxVis1, pyVis1, mVis2, pxVis2, pyVis2, pxMiss, pyMiss, mInvis1,
                                            mInvis2, desiredPrecisionOnMT2, useDeciSectionsInitially);
          if (mT2_Sq == MT2_ERROR)
          {
            return MT2_ERROR;
          }
          return sqrt(mT2_Sq);
        }

        static void disableCopyrightMessage(const bool printIfFirst = false)
        {
          static bool first = true;
          if (first && printIfFirst)
          {
            std::cout
            << "\n\n"
            << "#=========================================================\n"
            << "# To disable this message, place a call to \n"
            << "# \n"
            << "#     asymm_mt2_lester_bisect::disableCopyrightMessage();\n"
            << "# \n"
            << "# somewhere before you begin to calculate your MT2 values.\n"
            << "#=========================================================\n"
            << "# You are calculating symmetric or asymmetric MT2 using\n"
            << "# the implementation defined in:\n"
            << "# \n"
            << "#     http://arxiv.org/abs/1411.4312\n"
            << "# \n"
            << "# Please cite the paper above if you use the MT2 values\n"
            << "# for a scholarly purpose. For the variable MT2 itself,\n"
            << "# please also cite:\n"
            << "# \n"
            << "#     http://arxiv.org/abs/hep-ph/9906349\n"
            << "#=========================================================\n"
            << "\n\n"
            << std::flush;
          }
          first = false;
        }

        // returns square of asymmetric mT2 (which is >=0), or returns a
        // negative number (such as MT2_ERROR) in the case of an error.
        // desiredPrecisionOnMT2 must be non-negative.  If set to zero (default) MT2 will be
        // calculated to the highest precision available on the machine (or
        // as close to that as the algorithm permits).  If set to a
        // positive value, MT2 (note that is MT2, not its square) will be
        // calculated to within +- desiredPrecisionOnMT2. Note that by
        // requesting precision of +- 0.01 GeV on an MT2 value of 100 GeV
        // can resJult in speedups of a factor of ..
        // If useDeciSectionsInitially is true, interval is cut at the 10% point until first
        // acceptance, which gives factor 3 increase in speed calculating
        // kinematic min, but 3% slowdown for events in the bulk.  Is on
        // (true) by default, but can be turned off by setting to false.
        static double get_mT2_Sq( const double mVis1, const double pxVis1, const double pyVis1,
                                  const double mVis2, const double pxVis2, const double pyVis2,
                                  const double pxMiss, const double pyMiss, const double mInvis1,
                                  const double mInvis2,
                                  const double desiredPrecisionOnMT2 = 0,
                                  const bool useDeciSectionsInitially = true)
        {
          // By supplying an argument to disable, we actually ask for the
          // message to be printed, if printing is not already disabled.
          // This counterintuitive function naming is to avoid the need to
          // introduce static variable initialisations ....
          disableCopyrightMessage(true);

          const double m1Min = mVis1 + mInvis1; // when parent has this mass, ellipse
                                                // 1 has smallest physical size
          const double m2Min = mVis2 + mInvis2; // when parent has this mass, ellipse
                                                // 2 has smallest physical size

          if (m1Min > m2Min)
          {
            // swap 1 and 2
            return asymm_mt2_lester_bisect::get_mT2_Sq(mVis2, pxVis2, pyVis2, mVis1, pxVis1, pyVis1,
                                                       pxMiss, pyMiss, mInvis2, mInvis1, desiredPrecisionOnMT2);
          }

          // By now, we can be sure that m1Min <= m2Min
          assert(m1Min <= m2Min);

          // when parent has this mass, both ellipses are physical, and at
          // least one has zero size.  Note that the name "min" expresses
          // that it is the minimum potential parent mass we should
          // consider, not that it is the min of m1Min and m2Min.  It is in
          // fact the MAX of them!
          const double mMin = m2Min;

          // TODO: What about rounding?  What about idiots who give us mVis values
          // that have been computed from E^2-p^2 terms that are perilously close to
          // zero, or perilously degenerate?

          const double msSq = mVis1 * mVis1;
          const double sx = pxVis1;
          const double sy = pyVis1;
          const double mpSq = mInvis1 * mInvis1;
 
          const double mtSq = mVis2 * mVis2;
          const double tx = pxVis2;
          const double ty = pyVis2;
          const double mqSq = mInvis2 * mInvis2;

          const double sSq = sx * sx + sy * sy;
          const double tSq = tx * tx + ty * ty;
          const double pMissSq = pxMiss * pxMiss + pyMiss * pyMiss;
          const double massSqSum = msSq + mtSq + mpSq + mqSq;
          const double scaleSq = (massSqSum + sSq + tSq + pMissSq) / 8.0;

          // #define LESTER_DBG 1

          // Check for an easy MT2 zero, not because we think it will speed up many
          // cases, but because it will allow us to, ever after, assume that
          // scaleSq>0.
          if (scaleSq == 0)
          {
           return 0;
          }
          const double scale = sqrt(scaleSq);

          // disjoint at mMin.  So find an mUpper at which they are not disjoint:
          double mLower = mMin;
          // since scaleSq is guaranteed to be >0 at this stage, the
          // adition of scaleSq quarantees that mUpperSq is also >0,
          // so it can be exponentially grown (later) by doubling.
          double mUpper = mMin + scale;
          unsigned int attempts = 0;
          const unsigned int maxAttempts = 10000;
          while (true)
          {
            ++attempts;

            const double mUpperSq = mUpper * mUpper;
            // see side1Coeffs in mathematica notebook
            const EllipseParams &side1 = helper(mUpperSq, msSq, -sx, -sy, mpSq, 0, 0);
            // see side2Coeffs in mathematica notebook
            const EllipseParams &side2 = helper(mUpperSq, mtSq, +tx, +ty, mqSq, pxMiss, pyMiss);

            bool disjoint;
            try
            {
              disjoint = ellipsesAreDisjoint(side1, side2);
            }
            catch (...)
            {
              return MT2_ERROR;
            }

            if (!disjoint)
            {
              break;
            }

            if (attempts >= maxAttempts)
            {
              std::cerr << "MT2 algorithm failed to find upper bound to MT2" << std::endl;
              return MT2_ERROR;
            }

            mUpper *= 2; // grow mUpper exponentially
          }

          // const double tol = relativeTolerance * sqrt(scaleSq);

          // Now begin the bisection:
          bool goLow = useDeciSectionsInitially;
          while (desiredPrecisionOnMT2 <= 0 || mUpper - mLower > desiredPrecisionOnMT2)
          {
            // worry about this not being between mUpperSq and mLowerSq! TODO
            const double trialM =
                    (goLow ? (mLower * 15 + mUpper) / 16 // bias low until evidence this is not a special case
                  : (mUpper + mLower) / 2.0); // bisect

            if (trialM <= mLower || trialM >= mUpper)
            {
              // We reached a numerical precision limit:  the interval can no longer
              // be bisected!
              return trialM * trialM;
            }
            const double trialMSq = trialM * trialM;
            // see side1Coeffs in mathematica notebook
            const EllipseParams &side1 = helper(trialMSq, msSq, -sx, -sy, mpSq, 0, 0);
            // see side2Coeffs in mathematica notebook
            const EllipseParams &side2 = helper(trialMSq, mtSq, +tx, +ty, mqSq, pxMiss, pyMiss);

            try
            {
              const bool disjoint = ellipsesAreDisjoint(side1, side2);
              if (disjoint)
              {
                mLower = trialM;
                goLow = false;
              }
              else
              {
                mUpper = trialM;
              }
            }
            catch (...)
            {
              // The test for ellipses being disjoint failed ... this means the
              // ellipses became degenerate, which can only happen right at the bottom
              // of the MT2 search range (subject to numerical precision).  So:
              return mLower * mLower;
            }
          }

          const double mAns = (mLower + mUpper) / 2.0;
          return mAns * mAns;
        };

      private:
        static double lestermax(const double x, const double y)
        {
          return (x > y) ? x : y;
        }

        static const EllipseParams helper(const double mSq, // The test parent-mass value (squared)
                                          const double mtSq,
                                          const double tx,
                                          const double ty,   // The visible particle transverse momentum
                                          const double mqSq, // The mass of the invisible particle
                                          const double pxmiss,
                                          const double pymiss)
      {
        const double txSq = tx * tx;
        const double tySq = ty * ty;
        const double pxmissSq = pxmiss * pxmiss;
        const double pymissSq = pymiss * pymiss;

        const double c_xx = +4.0 * mtSq + 4.0 * tySq;

        const double c_yy = +4.0 * mtSq + 4.0 * txSq;

        const double c_xy = -4.0 * tx * ty;

        const double c_x = -4.0 * mtSq * pxmiss - 2.0 * mqSq * tx + 2.0 * mSq * tx -
                         2.0 * mtSq * tx + 4.0 * pymiss * tx * ty -
                         4.0 * pxmiss * tySq;

        const double c_y = -4.0 * mtSq * pymiss - 4.0 * pymiss * txSq -
                         2.0 * mqSq * ty + 2.0 * mSq * ty - 2.0 * mtSq * ty +
                         4.0 * pxmiss * tx * ty;

        const double c = -mqSq * mqSq + 2 * mqSq * mSq - mSq * mSq +
                       2 * mqSq * mtSq + 2 * mSq * mtSq - mtSq * mtSq +
                       4.0 * mtSq * pxmissSq + 4.0 * mtSq * pymissSq +
                       4.0 * mqSq * pxmiss * tx - 4.0 * mSq * pxmiss * tx +
                       4.0 * mtSq * pxmiss * tx + 4.0 * mqSq * txSq +
                       4.0 * pymissSq * txSq + 4.0 * mqSq * pymiss * ty -
                       4.0 * mSq * pymiss * ty + 4.0 * mtSq * pymiss * ty -
                       8.0 * pxmiss * pymiss * tx * ty + 4.0 * mqSq * tySq +
                       4.0 * pxmissSq * tySq;

        return EllipseParams(c_xx, c_yy, c_xy, c_x, c_y, c);
      }
    };

    void myversion()
    {
      std::cout << "version 5: arXiv:1411.4312v5" << std::endl;
    }

    double MT(double px1, double px2, double py1, double py2, double m1, double m2)
    {
      double E1 = sqrt(px1 * px1 + py1 * py1 + m1 * m1);
      double E2 = sqrt(px2 * px2 + py2 * py2 + m2 * m2);
      double Msq = (E1 + E2) * (E1 + E2) - (px1 + px2) * (px1 + px2) - (py1 + py2) * (py1 + py2);
      if (Msq < 0) Msq = 0;
      return sqrt(Msq);
    }

    std::pair<double, double> ben_findsols(double MT2, double px, double py,
                                           double visM, double Ma, double pxb,
                                           double pyb, double metx, double mety,
                                           double visMb, double Mb)
    {
      // Visible particle (px,py,visM)
      std::pair<double, double> sols;

      ///////
      // Find the minimizing points given MT2
      //////

      double Pt = sqrt(px * px + py * py);
      double E = sqrt(Pt * Pt + visM * visM);
      double M = MT2;
      double E2 = E * E;
      double M2 = M * M;
      double M4 = M2 * M2;
      double Ma2 = Ma * Ma;
      double Ma4 = Ma2 * Ma2;
      double px2 = px * px;
      double py2 = py * py;
      double px4 = px2 * px2;
      double py4 = py2 * py2;
      double py3 = py2 * py;
      double E4 = E2 * E2;
      double TermA = E2 * px - M2 * px + Ma2 * px - px2 * px - px * py2;
      double TermB = -2. * px * py;
      double TermSqy0 = E4 * E2 - 2. * E4 * M2 - 2. * E4 * Ma2 - 2. * E4 * px2 -
                    2. * E4 * py2 + E2 * M4 - 2. * E2 * M2 * Ma2 +
                    2. * E2 * M2 * px2 + 2. * E2 * M2 * py2 + E2 * Ma4 +
                    2. * E2 * Ma2 * px2 - 2. * E2 * Ma2 * py2 + E2 * px4 +
                    2. * E2 * px2 * py2 + E2 * py4;
      double TermSqy1 = -4. * E4 * py + 4. * E2 * M2 * py - 4. * E2 * Ma2 * py +
                    4. * E2 * px2 * py + 4. * E2 * py3;
      double TermSqy2 = -4. * E4 + 4. * E2 * px2 + 4. * E2 * py2;

      // First, determine the range.
      double myx = 0.;
      double myy = 0.;
      if (TermSqy1 * TermSqy1 - 4. * TermSqy0 * TermSqy2 < 0)
      {
        // unbalanced
      }
      else
      {
        double sol1 = (-TermSqy1 - sqrt(TermSqy1 * TermSqy1 - 4. * TermSqy0 * TermSqy2)) / (2. * TermSqy2);
        double sol2 = (-TermSqy1 + sqrt(TermSqy1 * TermSqy1 - 4. * TermSqy0 * TermSqy2)) / (2. * TermSqy2);
        double low = sol1;
        double high = sol2;
        if (low > high)
        {
          low = sol2;
          high = sol1;
        }

        double myclose = 99999999.;
        for (double metpy = low; metpy <= high; metpy += (high - low) / 10000.)
        {
          double metpx = -(TermB * metpy + TermA - sqrt(TermSqy0 + TermSqy1 * metpy + TermSqy2 * metpy * metpy)) * 0.5 / (E2 - px2);
          double metpx2 = -(TermB * metpy + TermA + sqrt(TermSqy0 + TermSqy1 * metpy + TermSqy2 * metpy * metpy)) * 0.5 / (E2 - px2);
          double mt1a = MT(px, metpx, py, metpy, visM, Ma);
          double mt1b = MT(px, metpx2, py, metpy, visM, Ma);
          double metpxb = metx - metpx;
          double metpx2b = metx - metpx2;
          double mt2a = MT(pxb, metpxb, pyb, mety - metpy, visMb, Mb);
          double mt2b = MT(pxb, metpx2b, pyb, mety - metpy, visMb, Mb);
          if (fabs(mt1a - mt2a) < myclose)
          {
            myclose = fabs(mt1a - mt2a);
            myy = metpy;
            myx = metpx;
          }
          if (fabs(mt1b - mt2b) < myclose)
          {
            myclose = fabs(mt1b - mt2b);
            myy = metpy;
            myx = metpx2;
          }
        }
      }

      sols.first = myx;
      sols.second = myy;

      return sols;
    }
        
    class Analysis_ATLAS_SUSY_2019_02 : public Analysis
    {
      private:

      #ifdef CHECK_CUTFLOW
        // Cut Flow
        vector<int> cutFlowVector;
        vector<string> cutFlowVector_str;
        int NCUTS;
      #endif
      
        std::map<std::string, MVA *> m_MVAs;
      
      public:

        // Required detector sim
        static constexpr const char* detector = "ATLAS";
      
        Analysis_ATLAS_SUSY_2019_02()
        {

          set_analysis_name("ATLAS_SUSY_2019_02");
          set_luminosity(139.0);

          // Slepton regions
          _counters["SR0j_100_infty"] = EventCounter("SR0j_100_infty");
          _counters["SR0j_110_infty"] = EventCounter("SR0j_110_infty");
          _counters["SR0j_120_infty"] = EventCounter("SR0j_120_infty");
          _counters["SR0j_130_infty"] = EventCounter("SR0j_130_infty");
          _counters["SR0j_140_infty"] = EventCounter("SR0j_140_infty");
          //_counters["SR0j_100_105"] = EventCounter("SR0j_100_105");
          //_counters["SR0j_105_110"] = EventCounter("SR0j_105_110");
          //_counters["SR0j_110_115"] = EventCounter("SR0j_110_115");
          //_counters["SR0j_115_120"] = EventCounter("SR0j_115_120");
          //_counters["SR0j_120_125"] = EventCounter("SR0j_120_125");
          //_counters["SR0j_125_130"] = EventCounter("SR0j_125_130");
          //_counters["SR0j_130_140"] = EventCounter("SR0j_130_140");
          _counters["SR1j_100_infty"] = EventCounter("SR1j_100_infty");
          _counters["SR1j_110_infty"] = EventCounter("SR1j_110_infty");
          _counters["SR1j_120_infty"] = EventCounter("SR1j_120_infty");
          _counters["SR1j_130_infty"] = EventCounter("SR1j_130_infty");
          _counters["SR1j_140_infty"] = EventCounter("SR1j_140_infty");
          //_counters["SR1j_100_105"] = EventCounter("SR1j_100_105");
          //_counters["SR1j_105_110"] = EventCounter("SR1j_105_110");
          //_counters["SR1j_110_115"] = EventCounter("SR1j_110_115");
          //_counters["SR1j_115_120"] = EventCounter("SR1j_115_120");
          //_counters["SR1j_120_125"] = EventCounter("SR1j_120_125");
          //_counters["SR1j_125_130"] = EventCounter("SR1j_125_130");
          //_counters["SR1j_130_140"] = EventCounter("SR1j_130_140");

          // Chargino regions
          _counters["SR_DF_81_inc"] = EventCounter("SR_DF_81_inc");
          //_counters["SR_DF_81_8125"] = EventCounter("SR_DF_81_8125");
          //_counters["SR_DF_8125_815"] = EventCounter("SR_DF_8125_815");
          //_counters["SR_DF_815_8175"] = EventCounter("SR_DF_815_8175");
          //_counters["SR_DF_8175_82"] = EventCounter("SR_DF_8175_82");
          //_counters["SR_DF_82_8225"] = EventCounter("SR_DF_82_8225");
          //_counters["SR_DF_8225_825"] = EventCounter("SR_DF_8225_825");
          //_counters["SR_DF_825_8275"] = EventCounter("SR_DF_825_8275");
          //_counters["SR_DF_8275_83"] = EventCounter("SR_DF_8275_83");
          //_counters["SR_DF_83_8325"] = EventCounter("SR_DF_83_8325");
          //_counters["SR_DF_8325_835"] = EventCounter("SR_DF_8325_835");
          //_counters["SR_DF_835_8375"] = EventCounter("SR_DF_835_8375");
          //_counters["SR_DF_8375_84"] = EventCounter("SR_DF_8375_84");
          //_counters["SR_DF_84_845"] = EventCounter("SR_DF_84_845");
          //_counters["SR_DF_845_85"] = EventCounter("SR_DF_845_85");
          //_counters["SR_DF_85_86"] = EventCounter("SR_DF_85_86");
          //_counters["SR_DF_86_inc"] = EventCounter("SR_DF_86_inc");
          _counters["SR_SF_77_inc"] = EventCounter("SR_SF_77_inc");
          //_counters["SR_SF_77_775"] = EventCounter("SR_SF_77_775");
          //_counters["SR_SF_775_78"] = EventCounter("SR_SF_775_78");
          //_counters["SR_SF_78_785"] = EventCounter("SR_SF_78_785");
          //_counters["SR_SF_785_79"] = EventCounter("SR_SF_785_79");
          //_counters["SR_SF_79_795"] = EventCounter("SR_SF_79_795");
          //_counters["SR_SF_795_80"] = EventCounter("SR_SF_795_80");
          //_counters["SR_SF_80_81"] = EventCounter("SR_SF_80_81");
          _counters["SR_SF_81_inc"] = EventCounter("SR_SF_81_inc");
          //_counters["SR_inc"] = EventCounter("SR_inc");
          _counters["SR_DF_82_inc"] = EventCounter("SR_DF_82_inc");
          _counters["SR_DF_83_inc"] = EventCounter("SR_DF_83_inc");
          _counters["SR_DF_84_inc"] = EventCounter("SR_DF_84_inc");
          _counters["SR_DF_85_inc"] = EventCounter("SR_DF_85_inc");
          _counters["SR_SF_78_inc"] = EventCounter("SR_SF_78_inc");
          _counters["SR_SF_79_inc"] = EventCounter("SR_SF_79_inc");
          _counters["SR_SF_80_inc"] = EventCounter("SR_SF_80_inc");

          #ifdef CHECK_CUTFLOW
          // Cut flows
          NCUTS = 54;

          for(int i = 0; i < NCUTS; i++)
          {
            cutFlowVector.push_back(0);
            cutFlowVector_str.push_back("");
          }
          #endif

          // Instances for BDT
          #pragma omp critical (init_ATLAS_SUSY_2019_02)
          {
            addMVABDT("lgbm_DF", GAMBIT_DIR "/ColliderBit/data/BDT_data/ANA-SUSY-2019-02_DF0J_trained_odd.root", GAMBIT_DIR "/ColliderBit/data/BDT_data/ANA-SUSY-2019-02_DF0J_trained_even.root");
            addMVABDT("lgbm_SF", GAMBIT_DIR "/ColliderBit/data/BDT_data/ANA-SUSY-2019-02_SF0J_trained_odd.root", GAMBIT_DIR "/ColliderBit/data/BDT_data/ANA-SUSY-2019-02_SF0J_trained_even.root");
          }
        }

        void addMVABDT(const std::string &name, const std::string &fname1, const std::string &fname2)
        {
          if (m_MVAs.find(name) != m_MVAs.end()) throw std::runtime_error("Duplicate MVA name");
          m_MVAs[name] = new MVAUtilsReader(name, fname1, fname2);
          // Assuming MVAUtilsReader returns a pointer to MVA
        }

        virtual MVA *getMVA(const std::string &name)
        {
          if (m_MVAs.find(name) == m_MVAs.end()) throw std::runtime_error("Unknown MVA name");
          return m_MVAs[name];
        }
      
        // Assuming Particle and Particles are correct type names.
        vector<const Particle*> filterLeptons(vector<const Particle*> &cands, float ptCut, float etaCut)
        {
      
          vector<const Particle*> reducedList;
          for (const auto &cand : cands)
          {
            if ((cand->pT() >= ptCut) && (cand->abseta() < etaCut)) reducedList.push_back(cand);
          }
          return reducedList;
        }
      
        // Assuming Particle and Particles are correct type names.
        vector<const Jet*> filterJets(vector<const Jet*> &cands, float ptCut, float etaCut)
        {
          vector<const Jet*> reducedList;
          for (const auto &cand : cands)
          {
            if ((cand->pT() >= ptCut) && (cand->abseta() < etaCut)) reducedList.push_back(cand);
          }
          return reducedList;
        }
      
        struct pt_sort
        {
          bool operator()(const Particle* p1, const Particle* p2) const
          {
            return p1->pT() > p2->pT();
          }
        };
      
        void sortObjectsByPt(vector<const Particle*> &cands)
        {
          return std::sort(cands.begin(), cands.end(), pt_sort());
        }

        int countObjects(vector<const Particle*> &cands, float ptCut, float etaCut)
        {
          int count = 0;
          for (const auto &cand : cands)
          {
            if (cand->pT() >= ptCut && cand->abseta() < etaCut) count++;
          }
          return count;
        }

        int countObjects(vector<const Jet*> &cands, float ptCut, float etaCut)
        {
          int count = 0;
          for (const auto &cand : cands)
          {
            if (cand->pT() >= ptCut && cand->abseta() < etaCut) count++;
          }
          return count;
        }

        /*
        // Jet overlap removal
        void JetLeptonOverlapRemoval(vector<const HEPUtils::Jet*> &jetvec, vector<const HEPUtils::Particle*> &lepvec, double DeltaRMax) {
              //Routine to do jet-lepton check
              //Discards jets if they are within DeltaRMax of a lepton

              vector<const HEPUtils::Jet*> Survivors;

              for(unsigned int itjet = 0; itjet < jetvec.size(); itjet++) {
                bool overlap = false;
                HEPUtils::P4 jetmom=jetvec.at(itjet)->mom();
                for(unsigned int itlep = 0; itlep < lepvec.size(); itlep++) {
                    HEPUtils::P4 lepmom=lepvec.at(itlep)->mom();
                    double dR;

                    dR=jetmom.deltaR_eta(lepmom);

                    if(fabs(dR) <= DeltaRMax) overlap=true;
                }
                if(overlap) continue;
                Survivors.push_back(jetvec.at(itjet));
            }
            jetvec = Survivors;

            return;
        }
      
        // Lepton overlap removal
        void LeptonJetOverlapRemoval(vector<const HEPUtils::Particle*> &lepvec, vector<const HEPUtils::Jet*> &jetvec, double DeltaRMax) {
            //Routine to do lepton-jet check
            //Discards leptons if they are within DeltaRMax of a jet

            vector<const HEPUtils::Particle*> Survivors;

            for(unsigned int itlep = 0; itlep < lepvec.size(); itlep++) {
                bool overlap = false;
                HEPUtils::P4 lepmom=lepvec.at(itlep)->mom();
                for(unsigned int itjet= 0; itjet < jetvec.size(); itjet++) {
                    HEPUtils::P4 jetmom=jetvec.at(itjet)->mom();
                    double dR;

                    dR=jetmom.deltaR_eta(lepmom);

                    if(fabs(dR) <= DeltaRMax) overlap=true;
                }
                if(overlap) continue;
                Survivors.push_back(lepvec.at(itlep));
            }
            lepvec = Survivors;

            return;
        }
        */
      
        float calcMT2(const Particle &o1, const Particle &o2, const P4 &met)
        {
          return calcAMT2(o1, o2, met, 0, 0);
        }

        float calcAMT2(const Particle &o1, const Particle &o2, const P4 &met, float m1, float m2)
        {
          asymm_mt2_lester_bisect::disableCopyrightMessage();
          return asymm_mt2_lester_bisect::get_mT2(o1.mom().m(), o1.mom().px(), o1.mom().py(), o2.mom().m(),
                                                  o2.mom().px(), o2.mom().py(), met.px(), met.py(), m1, m2);
        }

        float calcMTauTau(const Particle &o1, const Particle &o2, const P4 &met)
        {
          float determinant = o1.mom().px() * o2.mom().py() - o1.mom().py() * o2.mom().px();
          float xi_1 = (met.px() * o2.mom().py() - o2.mom().px() * met.py()) / determinant;
          float xi_2 = (met.py() * o1.mom().px() - o1.mom().py() * met.px()) / determinant;

          float MSqTauTau = (1. + xi_1) * (1. + xi_2) * 2 * o1.mom().dot(o2.mom());

          float MTauTau = 0.;
          if (MSqTauTau >= 0) MTauTau = sqrt(MSqTauTau);
          if (MSqTauTau < 0) MTauTau = -sqrt(fabs(MSqTauTau));

          return MTauTau;
        }
    
        vector<const Particle*> LeptonLeptonOverlapRemoval(vector<const Particle*> &cands, vector< const Particle*> &others,
                                                           std::function<float(const Particle* , const Particle* )> radiusFunc)
        {
          vector<const Particle*> reducedList;
          for (const auto &cand : cands)
          {
            bool overlap = false;
            for (const auto &other : others)
            {
              if (cand->mom().deltaR_eta(other->mom()) < radiusFunc(cand, other) && cand != other)
              {
                overlap = true;
                break;
              }
            }
            if (!overlap) reducedList.push_back(cand);
          }
          return reducedList;
        }

        vector<const Jet*> JetLeptonOverlapRemoval(vector<const Jet*> &cands, vector< const Particle*> &others,
                                                   std::function<float(const Jet* , const Particle* )> radiusFunc)
        {
          vector<const Jet*> reducedList;
          for (const auto &cand : cands)
          {
            bool overlap = false;
            for (const auto &other : others)
            {
              //if (cand->mom().deltaR_eta(other->mom()) < radiusFunc(cand, other) && cand != other) {
              if (cand->mom().deltaR_eta(other->mom()) < radiusFunc(cand, other))
              {
                overlap = true;
                break;
              }
            }
            if (!overlap) reducedList.push_back(cand);
          }
          return reducedList;
        }

        vector<const Particle*> LeptonJetOverlapRemoval(vector<const Particle*> &cands, vector< const Jet*> &others,
                                                        std::function<float(const Particle* , const Jet* )> radiusFunc)
        {
          vector<const Particle*> reducedList;
          for (const auto &cand : cands)
          {
            bool overlap = false;
            for (const auto &other : others)
            {
              if (cand->mom().deltaR_eta(other->mom()) < radiusFunc(cand, other))
              {
                overlap = true;
                break;
              }
            }
            if (!overlap) reducedList.push_back(cand);
          }
          return reducedList;
        }
      
        vector<const Particle*> LeptonLeptonOverlapRemoval(vector<const Particle*> &cands,
                                                           vector<const Particle*> &others,
                                                           float deltaR)
        {
          return LeptonLeptonOverlapRemoval( cands, others, [deltaR](const Particle*, const Particle*) { return deltaR; } );
        }
      
        vector<const Jet*> JetLeptonOverlapRemoval(vector<const Jet*> &cands,
                                                   vector<const Particle*> &others,
                                                   float deltaR)
        {
          return JetLeptonOverlapRemoval(cands, others,[deltaR](const Jet*, const Particle*) {return deltaR;});
        }

        vector<const Particle*> LeptonJetOverlapRemoval(vector<const Particle*> &cands,
                                                        vector<const Jet*> &others,
                                                        float deltaR)
        {
          return LeptonJetOverlapRemoval(cands, others,[deltaR](const Particle*, const Jet*) {return deltaR;});
        }
            
        double calcMETSignificance(vector<const Particle*> &electrons,
                                   vector<const Particle*> &photons,
                                   vector<const Particle*> &muons,
                                   vector<const Jet*> &jets,
                                   vector<const Particle*> &taus,
                                   HEPUtils::P4 &metVec,
                                   double met)
        {

          //auto objects = electrons + photons + muons + jets + taus;

          std::vector<const Particle*> particles;
          //std::vector<const Jet*> Jets;

          for (auto obj : electrons)
          {
            particles.push_back(obj);
          }

          for (auto obj : muons)
          {
            particles.push_back(obj);
          }

          for (auto obj : photons)
          {
            particles.push_back(obj);
          }

          for (auto obj : taus)
          {
            particles.push_back(obj);
          }

          // Process particles
          //for (const auto& particle : particles) {
            // Do something with particle
          //}

          // Process jets
          //for (auto obj : jets) {
            // Do something with jet
          //}

          auto softVec = metVec;
          //double met = metVec.Et();

          TMatrix cov_sum(2, 2);

          TMatrix particle_u(2, 2), particle_u_rot(2, 2);
          for (auto obj : particles)
          {
            softVec += obj->mom(); // soft term is everything not included in hard objects
            double pt_reso = 0.0, phi_reso = 0.0;
            //getObjectResolution(obj, pt_reso, phi_reso);
            particle_u(0, 0) = pow(pt_reso * obj->pT(), 2);
            particle_u(1, 1) = pow(phi_reso * obj->pT(), 2);
            rotateXY(particle_u, particle_u_rot, metVec.deltaPhi(obj->mom()));
            cov_sum += particle_u_rot;
          }

          for (auto obj : jets)
          {
            softVec += obj->mom(); // soft term is everything not included in hard objects
            double pt_reso = 0.0, phi_reso = 0.0;
            //getObjectResolution(obj, pt_reso, phi_reso);
            particle_u(0, 0) = pow(pt_reso * obj->pT(), 2);
            particle_u(1, 1) = pow(phi_reso * obj->pT(), 2);
            rotateXY(particle_u, particle_u_rot, metVec.deltaPhi(obj->mom()));
            cov_sum += particle_u_rot;
          }

          // add soft term resolution (fixed 10 GeV) but tunned to 12 GeV
          particle_u(0, 0) = 10 * 10;
          particle_u(1, 1) = 10 * 10;
          rotateXY(particle_u, particle_u_rot, metVec.deltaPhi(softVec));
          cov_sum += particle_u_rot;

          // calculate significance
          double varL = cov_sum(0, 0);
          double varT = cov_sum(1, 1);
          double covLT = cov_sum(0, 1);

          double significance = 0;
          double rho = 0;
          if (varL != 0)
          {
            rho = covLT / sqrt(varL * varT);
            if (fabs(rho) >= 0.9) rho = 0; // too large - ignore it
            significance = met / sqrt((varL * (1 - pow(rho, 2))));
          }
          return significance;
        }
         
        double calcMETSignificance(const HEPUtils::Event &event, bool applyOverlapRemoval)
        {
          auto electrons = getObjects(&event, "electrons", 10, 2.47);
          auto photons = getObjects(&event, "photons", 10, 2.47);
          auto muons = getObjects(&event, "muons", 10, 2.5);
          auto jets = getJets(&event, 20., 4.5);
          auto taus = getObjects(&event, "taus", 10., 2.5); 
          auto metVec = event.missingmom();
          double MET = event.met();

          // This is a default overlap removal
          if (applyOverlapRemoval)
          {
            auto radiusCalcLepton = [](const Particle* lepton, const Jet* jet) {return std::min(0.4, 0.04 + 10 / lepton->pT());};

            auto muJetSpecial = [](const Jet* jet, const Particle* muon)
            {
              if (muon->pT() / jet->pT() > 0.5) return 0.2;
              else return 0.;
            };
          
            muons = LeptonLeptonOverlapRemoval(muons, electrons, 0.01);
            electrons = LeptonLeptonOverlapRemoval(electrons, muons, 0.01);
            jets = JetLeptonOverlapRemoval(jets, electrons, 0.2);
            electrons = LeptonJetOverlapRemoval(electrons, jets, 0.2);

            jets = JetLeptonOverlapRemoval(jets, muons, muJetSpecial);
            muons = LeptonJetOverlapRemoval(muons, jets, 0.2);

            muons = LeptonJetOverlapRemoval(muons, jets, radiusCalcLepton);
            electrons = LeptonJetOverlapRemoval(electrons, jets, radiusCalcLepton);
          
          }

          return calcMETSignificance(electrons, photons, muons, jets, taus, metVec, MET);
        }
      
        vector<const Particle*> getObjects(const HEPUtils::Event* event, std::string type, double ptcut, double etacut)
        {
          vector<const Particle*> cands;

          if (type == "electrons")
          {
            // Get baseline electrons
            for (const Particle* electron : event->electrons())
            {
              if (electron->pT() > ptcut && electron->abseta() < etacut) cands.push_back(electron);
            }
          }

          if (type == "muons")
          {
            for (const Particle* muon : event->muons())
            {
              if (muon->pT() > ptcut && muon->abseta() < etacut) cands.push_back(muon);
            }
          }

          if (type == "photons")
          {
            for (const Particle* photon : event->photons())
            {
              if (photon->pT() > ptcut && photon->abseta() < etacut) cands.push_back(photon);
            }
          }

          if (type == "taus")
          {
            for (const Particle* tau : event->taus())
            {
              if (tau->pT() > ptcut && tau->abseta() < etacut) cands.push_back(tau);
            }
          }

          return cands;
        }

        vector<const Jet*> getJets(const HEPUtils::Event* event, double ptcut, double etacut)
        {
           vector<const Jet*> candJets;
           for (const Jet* jet : event->jets("antikt_R04"))
           {
             if (jet->pT() > ptcut && jet->abseta() < etacut) candJets.push_back(jet);
           }
           return candJets;       
        }


        /// Main Run Function
        void run(const HEPUtils::Event* event)
        {
          // Get baseline electrons
          vector<const Particle*> electrons = getObjects(event, "electrons", 9., 2.47);

          // Get baseline muons
          vector<const Particle*> muons = getObjects(event, "muons", 9., 2.6);

          // Get baseline jets
          vector<const Jet*> candJets = getJets(event, 20., 2.8);

          // Get the missing energy in the event
          double MET = event->met();
          HEPUtils::P4 METVec = event->missingmom();
          double METsig = calcMETSignificance(*event, false);   

          // Overlap removal - including with object Pt-dependent radius calculation

          // Electrons
          candJets = JetLeptonOverlapRemoval(candJets, electrons, 0.2);
          auto radiusCalcEle = [](const Particle* ele, const Jet*) -> float {return std::min(0.4, 0.04 + 10.0/ele->pT());};
          electrons = LeptonJetOverlapRemoval(electrons, candJets, radiusCalcEle);

          // Muons
          candJets = JetLeptonOverlapRemoval(candJets, muons, 0.4);
          auto radiusCalcMuon = [](const Particle* muon, const Jet*) -> float {return std::min(0.4, 0.04 + 10.0/muon->pT());};
          muons = LeptonJetOverlapRemoval(muons, candJets, radiusCalcMuon);

          // Basic filtering by pT, eta and "ID"
          auto signalJets = filterJets(candJets, 20., 2.4);
          //vector<const HEPUtils::Jet*> bjets;
          //vector<const HEPUtils::Jet*> Nonbjets;

          /*
          // Find b-jets
          double btag = 0.77; double cmisstag = 1/16.; double misstag = 1./113.;
          for (const HEPUtils::Jet* jet : signalJets) {
        
            // Tag
            if( jet->btag() && random_bool(btag) ) bjets.push_back(jet);
            // Misstag c-jet
            else if( jet->ctag() && random_bool(cmisstag) ) bjets.push_back(jet);
            // Misstag light jet
            else if( random_bool(misstag) ) bjets.push_back(jet);
            // Non b-jet
            else Nonbjets.push_back(jet);
          }
          */
          auto signalElectrons = filterLeptons(electrons, 9., 2.47);
          auto signalMuons = filterLeptons(muons, 9., 2.6);

          // Merges electrons and muons to leptons
          vector<const Particle*> signalLeptons;
          for (const Particle* electron : signalElectrons)
          {
            signalLeptons.push_back(electron);
          }
          for (const Particle* muon : signalMuons)
          {
            signalLeptons.push_back(muon);
          }

          //Put signal jets/leptons in pT order
          std::sort(signalJets.begin(), signalJets.end(), sortBypT_j);
          std::sort(signalLeptons.begin(), signalLeptons.end(), sortBypT_l);
          std::sort(signalElectrons.begin(), signalElectrons.end(), sortBypT_l);
          std::sort(signalMuons.begin(), signalMuons.end(), sortBypT_l);

          // Object counting
          int nlep = signalLeptons.size();

          // I set the number of bjets to zero to avoid issues
          // with b-tagging. At the end of the day for electroweak
          // searches does not have an effective impact both in slsl
          // and in chargino production
          int nbjet   = 0; //bjets.size();
          int njet    = countObjects(candJets, 20, 2.4);
          //int njet30  = countObjects(candJets, 30, 2.4);
          //int njet40  = countObjects(candJets, 40, 2.4);
          //int njet50  = countObjects(candJets, 50, 2.4);
          //int njet60  = countObjects(candJets, 60, 2.4);

          //cutFlowVector[0]++;

          // Preselection
          if(nlep != 2) return;
          //return this
          if(signalLeptons[1]->pT() < 9.) return;

          //this to back
          if(signalLeptons[0]->pT() < 27.) return;

          //return back this 
          if (njet > 1) return;

          bool isSF = (abs(signalLeptons[0]->pid()) == abs(signalLeptons[1]->pid()));
          bool isOS = (signalLeptons[0]->pid()*signalLeptons[1]->pid()) < 0;

          //return back this
          if (not isOS) return;

          HEPUtils::P4 lepton0 = signalLeptons.at(0)->mom();
          HEPUtils::P4 lepton1 = signalLeptons.at(1)->mom();
          double mll = (lepton0 + lepton1).m();

          //if((signalLeptons[0] + signalLeptons[1]).M() < 10.) return;
          //Back this later
          if (mll < 12.) return;

          if (METsig < 8) return;

          //Calculate MT2
          double MT2 = 0;
          double pa_a[3] = { 0, signalLeptons[0]->mom().px(), signalLeptons[0]->mom().py() };
          double pb_a[3] = { 0, signalLeptons[1]->mom().px(), signalLeptons[1]->mom().py() };
          double pmiss_a[3] = { 0, METVec.px(), METVec.py() };
          double mn_a = 0.;

          mt2_bisect::mt2 mt2_event_a;
          mt2_event_a.set_momenta(pa_a, pb_a, pmiss_a);
          mt2_event_a.set_mn(mn_a);
          MT2 = mt2_event_a.get_mt2();

          //double mll = (signalLeptons[0] + signalLeptons[1]).M();
          //double METphi = METVec.phi();
          /*
          double jet1pT = 0.0, jet1phi = 0.0, jet1eta = 0.0;
          if (signalJets.size() > 0){
            jet1pT = signalJets[0]->pT();
            jet1phi = signalJets[0]->phi();
            jet1eta = signalJets[0]->eta();
          }

          double jet2pT = 0.0, jet2phi = 0.0, jet2eta = 0.0;
          if (signalJets.size() > 1) {
            jet2pT = signalJets[1]->pT();
            jet2phi = signalJets[1]->phi();
            jet2eta = signalJets[1]->eta();
          }
         */

          //leptons
          double lep1pT = signalLeptons[0]->pT(), lep2pT = signalLeptons[1]->pT();
          //double lep1phi = signalLeptons[0]->phi(), lep2phi = signalLeptons[1]->phi();
          //double lep1eta = signalLeptons[0]->eta(), lep2eta = signalLeptons[1]->eta();

          //extra variables
          double MT2_100 = calcAMT2(signalLeptons[0], signalLeptons[1], METVec, 100., 100.); //mass of final state invis = 100
          //double MT2_200 = calcAMT2(signalLeptons[0], signalLeptons[1], METVec, 200., 200.);
          //std::cout << " MT2   "  << MT2_100 << "  " << MT2_200 << std::endl; 
       
          //double dRll = signalLeptons[0]->mom().deltaR_eta(signalLeptons[1]->mom());
          //double dRMETl1 = signalLeptons[0]->mom().deltaR_eta(METVec), dRMETl2 = signalLeptons[1]->mom().deltaR_eta(METVec);

          double dphill = std::fabs( signalLeptons[0]->mom().deltaPhi(signalLeptons[1]->mom()) );
          //double dphiMETll = std::fabs( METVec.deltaPhi(signalLeptons[0]->mom() + signalLeptons[1]->mom()) );
          double dphiMETl1 = std::fabs( METVec.deltaPhi(signalLeptons[0]->mom()) );
          double dphiMETl2 = std::fabs( METVec.deltaPhi(signalLeptons[1]->mom()) );
          //double dRMETll = METVec.deltaR_eta(signalLeptons[0]->mom() + signalLeptons[1]->mom());

          //double mtt = calcMTauTau(signalLeptons[0], signalLeptons[1], METVec);

          double pbll = (signalLeptons[0]->mom() + signalLeptons[1]->mom() + METVec).pT();

      
          /*
          double R1 = MET / pbll;

          double meff2l1j = -10;
          double R2 = -10;

          //std::cout << mtt << "  " << R1 << "  " << std::endl;

          if (signalJets.size() > 0) { 
            meff2l1j =  (signalLeptons[0]->mom() + signalLeptons[1]->mom() + METVec + signalJets[0]->mom()).pT();
            R2 = MET / meff2l1j;
          }
          */
          double DPhib = std::fabs(  METVec.deltaPhi(signalLeptons[0]->mom() + signalLeptons[1]->mom() + METVec) ) ;

          //double MllMET = (signalLeptons[0]->mom() + signalLeptons[1]->mom() + METVec).m();

          /*
          double lepflav1 = -10;
          if (signalLeptons[0]->abspid() == 11) lepflav1 = 11;
          else if (signalLeptons[0]->abspid() == 13) lepflav1 = 13;

          double lepflav2 = -10;
          if (signalLeptons[1]->abspid() == 11) lepflav2 = 11;
          else if (signalLeptons[1]->abspid() == 13) lepflav2 = 13;
          */

          /*
          int njetTruth = 0;
          for(auto jet : candJets) {
            auto truth = event->getTruthParticle(jet);
            if (truth.valid()) {
              if(truth.Pt()>20 && truth.Eta()<2.4) njetTruth++;
            }
          }
          */

          // Add additional variable for slepton analysis
          double cosTstar = std::fabs( std::tanh( 0.5*(signalLeptons[0]->eta() - signalLeptons[1]->eta()) ) );

          // Preselection
          //if(nlep == 2 && signalLeptons[0]->pT() > 27. && signalLeptons[1]->pT() > 9. && isOS && mll > 11. && METsig > 3.) {
          //} 

          //std::cout << cosTstar  << "  " << std::endl;
          //exit(0);

          /*
          ***************************************************************** SLEPTONS 0-jet
          */
          if (nbjet == 0 && njet == 0 && isSF && lep1pT > 140. && lep2pT > 20. && METsig > 7. && TMath::Abs(mll - 91.) > 15. && pbll < 5. && cosTstar < 0.2 && dphill > 2.2 && dphiMETl1 > 2.2)
          {
            if (MT2_100 >= 100.                  ) _counters.at("SR0j_100_infty").add_event(event);
            if (MT2_100 >= 110.                  ) _counters.at("SR0j_110_infty").add_event(event);
            if (MT2_100 >= 120.                  ) _counters.at("SR0j_120_infty").add_event(event);
            if (MT2_100 >= 130.                  ) _counters.at("SR0j_130_infty").add_event(event);
            if (MT2_100 >= 140.                  ) _counters.at("SR0j_140_infty").add_event(event);
            //if (MT2_100 >= 100. && MT2_100 < 105.) _counters.at("SR0j_100_105").add_event(event);
            //if (MT2_100 >= 105. && MT2_100 < 110.) _counters.at("SR0j_105_110").add_event(event);
            //if (MT2_100 >= 110. && MT2_100 < 115.) _counters.at("SR0j_110_115").add_event(event);
            //if (MT2_100 >= 115. && MT2_100 < 120.) _counters.at("SR0j_115_120").add_event(event);
            //if (MT2_100 >= 120. && MT2_100 < 125.) _counters.at("SR0j_120_125").add_event(event);
            //if (MT2_100 >= 125. && MT2_100 < 130.) _counters.at("SR0j_125_130").add_event(event);
            //if (MT2_100 >= 130. && MT2_100 < 140.) _counters.at("SR0j_130_140").add_event(event);
          }

          /*
           ***************************************************************** SLEPTONS 1-jet
          */
          if (nbjet == 0 && njet == 1 && isSF && lep1pT > 100. && lep2pT > 50. && METsig > 7. && mll > 60. && TMath::Abs(mll - 91.) > 15. && cosTstar < 0.1 && dphill > 2.8)
          {
            if (MT2_100 >= 100.                  ) _counters.at("SR1j_100_infty").add_event(event);
            if (MT2_100 >= 110.                  ) _counters.at("SR1j_110_infty").add_event(event);
            if (MT2_100 >= 120.                  ) _counters.at("SR1j_120_infty").add_event(event);
            if (MT2_100 >= 130.                  ) _counters.at("SR1j_130_infty").add_event(event);
            if (MT2_100 >= 140.                  ) _counters.at("SR1j_140_infty").add_event(event);
            //if (MT2_100 >= 100. && MT2_100 < 105.) _counters.at("SR1j_100_105").add_event(event);
            //if (MT2_100 >= 105. && MT2_100 < 110.) _counters.at("SR1j_105_110").add_event(event);
            //if (MT2_100 >= 110. && MT2_100 < 115.) _counters.at("SR1j_110_115").add_event(event);
            //if (MT2_100 >= 115. && MT2_100 < 120.) _counters.at("SR1j_115_120").add_event(event);
            //if (MT2_100 >= 120. && MT2_100 < 125.) _counters.at("SR1j_120_125").add_event(event);
            //if (MT2_100 >= 125. && MT2_100 < 130.) _counters.at("SR1j_125_130").add_event(event);
            //if (MT2_100 >= 130. && MT2_100 < 140.) _counters.at("SR1j_130_140").add_event(event);
          }

          double BDT = 0, BDTothers = 0;
          /*
          ***************************************************************** C1C1WW DF
          */

          if (!isSF && njet == 0 && nbjet == 0 && METsig > 8. && MT2 > 50.)
          {
            std::vector<double> inDF{lep1pT, lep2pT, MET, MT2, mll, DPhib, dphiMETl1, dphiMETl2, cosTstar, METsig};
            auto DF_MVA = getMVA("lgbm_DF");
            auto results = DF_MVA->evaluateMulti(inDF, 4);
            BDT = results[1];

            if (BDT > 0.81                   )
            {
              //_counters.at("SR_inc").add_event(event);
              _counters.at("SR_DF_81_inc").add_event(event);
            }
            //if (BDT > 0.81   && BDT <= 0.8125) _counters.at("SR_DF_81_8125").add_event(event);
            //if (BDT > 0.8125 && BDT <= 0.815 ) _counters.at("SR_DF_8125_815").add_event(event);
            //if (BDT > 0.815  && BDT <= 0.8175) _counters.at("SR_DF_815_8175").add_event(event);
            //if (BDT > 0.8175 && BDT <= 0.82  ) _counters.at("SR_DF_8175_82").add_event(event);
            if (BDT > 0.82                   ) _counters.at("SR_DF_82_inc").add_event(event);
            //if (BDT > 0.82   && BDT <= 0.8225) _counters.at("SR_DF_82_8225").add_event(event);
            //if (BDT > 0.8225 && BDT <= 0.825 ) _counters.at("SR_DF_8225_825").add_event(event);
            //if (BDT > 0.825  && BDT <= 0.8275) _counters.at("SR_DF_825_8275").add_event(event);
            //if (BDT > 0.8275 && BDT <= 0.83  ) _counters.at("SR_DF_8275_83").add_event(event);
            if (BDT > 0.83                   ) _counters.at("SR_DF_83_inc").add_event(event);
            //if (BDT > 0.83   && BDT <= 0.8325) _counters.at("SR_DF_83_8325").add_event(event);
            //if (BDT > 0.8325 && BDT <= 0.835 ) _counters.at("SR_DF_8325_835").add_event(event);
            //if (BDT > 0.835  && BDT <= 0.8375) _counters.at("SR_DF_835_8375").add_event(event);
            //if (BDT > 0.8375 && BDT <= 0.84  ) _counters.at("SR_DF_8375_84").add_event(event);
            if (BDT > 0.84                   ) _counters.at("SR_DF_84_inc").add_event(event);
            //if (BDT > 0.84   && BDT <= 0.845 ) _counters.at("SR_DF_84_845").add_event(event);
            //if (BDT > 0.845  && BDT <= 0.85  ) _counters.at("SR_DF_845_85").add_event(event);
            if (BDT > 0.85                   ) _counters.at("SR_DF_85_inc").add_event(event);
            //if (BDT > 0.85   && BDT <= 0.86  ) _counters.at("SR_DF_85_86").add_event(event);
            //if (BDT > 0.86) _counters.at("SR_DF_86_inc").add_event(event);
          }

          /*
          ***************************************************************** C1C1WW SF
          */
          //std::cout << isSF << "  " <<  TMath::Abs(mll - 91.) << "  " << njet << "  " << nbjet << "  " << METsig << "  " << MT2 << std::endl;
          if (isSF && TMath::Abs(mll - 91.) > 15. && njet == 0 && nbjet == 0 && METsig > 8. && MT2 > 50.)
          {
            std::vector<double> inSF{lep1pT, lep2pT, MET, MT2, mll, DPhib, dphiMETl1, dphiMETl2, cosTstar, METsig};
            auto SF_MVA = getMVA("lgbm_SF");
            auto results = SF_MVA->evaluateMulti(inSF, 4);

            BDT = results[1];
            BDTothers = results[3];

            //std::cout << BDT << "  " << BDTothers << std::endl;
            //exit(0);
            if (BDTothers < 0.01 && BDT > 0.77                 )
            {
              //_counters.at("SR_inc").add_event(event);
              _counters.at("SR_SF_77_inc").add_event(event);
            }
            //if (BDTothers < 0.01 && BDT > 0.77  && BDT <= 0.775) _counters.at("SR_SF_77_775").add_event(event);
            //if (BDTothers < 0.01 && BDT > 0.775 && BDT <= 0.78 ) _counters.at("SR_SF_775_78").add_event(event);
            if (BDTothers < 0.01 && BDT > 0.78                 ) _counters.at("SR_SF_78_inc").add_event(event);
            //if (BDTothers < 0.01 && BDT > 0.78  && BDT <= 0.785) _counters.at("SR_SF_78_785").add_event(event);
            //if (BDTothers < 0.01 && BDT > 0.785 && BDT <= 0.79 ) _counters.at("SR_SF_785_79").add_event(event);
            if (BDTothers < 0.01 && BDT > 0.79                 ) _counters.at("SR_SF_79_inc").add_event(event);
            //if (BDTothers < 0.01 && BDT > 0.79  && BDT <= 0.795) _counters.at("SR_SF_79_795").add_event(event);
            //if (BDTothers < 0.01 && BDT > 0.795 && BDT <= 0.80 ) _counters.at("SR_SF_795_80").add_event(event);
            if (BDTothers < 0.01 && BDT > 0.80                 ) _counters.at("SR_SF_80_inc").add_event(event);
            //if (BDTothers < 0.01 && BDT > 0.80  && BDT <= 0.81 ) _counters.at("SR_SF_80_81").add_event(event);
            //if (BDTothers < 0.01 && BDT > 0.81) _counters.at("SR_SF_81_inc").add_event(event);
          }

        }

        /// Register results objects with the results for each SR; obs & bkg numbers from the CONF note
        void collect_results()
        {

          // Slepton regions
          add_result(SignalRegionData(_counters.at("SR0j_100_infty"), 58, {89., 63.}));
          add_result(SignalRegionData(_counters.at("SR0j_110_infty"), 39, {69., 47.}));
          add_result(SignalRegionData(_counters.at("SR0j_120_infty"), 30, {48., 32.}));
          add_result(SignalRegionData(_counters.at("SR0j_130_infty"), 23, {30., 18.}));
          add_result(SignalRegionData(_counters.at("SR0j_140_infty"), 7, {12.6, 5.8}));
          add_result(SignalRegionData(_counters.at("SR1j_100_infty"), 82, {91., 65.}));
          add_result(SignalRegionData(_counters.at("SR1j_110_infty"), 39, {67., 33.}));
          add_result(SignalRegionData(_counters.at("SR1j_120_infty"), 12, {21., 11.}));
          add_result(SignalRegionData(_counters.at("SR1j_130_infty"), 2, {9.7, 4.1}));
          add_result(SignalRegionData(_counters.at("SR1j_140_infty"), 0, {4., 0.8}));
          // Chargino regions
          add_result(SignalRegionData(_counters.at("SR_DF_81_inc"), 477, {520, 420})); 
          add_result(SignalRegionData(_counters.at("SR_SF_77_inc"), 143, {199, 135})); 
          add_result(SignalRegionData(_counters.at("SR_DF_82_inc"), 340, {390, 310}));
          add_result(SignalRegionData(_counters.at("SR_DF_83_inc"), 222, {257, 205})); 
          add_result(SignalRegionData(_counters.at("SR_DF_84_inc"), 130, {141, 111})); 
          add_result(SignalRegionData(_counters.at("SR_DF_85_inc"), 69, {75, 55})); 
          add_result(SignalRegionData(_counters.at("SR_SF_78_inc"), 86, {131, 85})); 
          add_result(SignalRegionData(_counters.at("SR_SF_79_inc"), 47, {73, 43})); 
          add_result(SignalRegionData(_counters.at("SR_SF_80_inc"), 22, {36, 20})); 
        }

      protected:

        void analysis_specific_reset()
        {
          for (auto& pair : _counters) { pair.second.reset(); }
        }
      
    };

    DEFINE_ANALYSIS_FACTORY(ATLAS_SUSY_2019_02)
      
  }
}

#endif
