#include "gambit/ColliderBit/limits/OPALGauginoLimits.hpp"

namespace Gambit {
  namespace ColliderBit {


    P2 OPALCharginoHadronicLimitAt208GeV::convertPt(double x, double y) const
    {
      return P2(75. + (x - 179.00) / (753.00 - 179.00) * (100. - 75.),
                100. + (y - 82.00) / (688.00 - 82.00) * (0. - 100.));
    }

    bool OPALCharginoHadronicLimitAt208GeV::isWithinExclusionRegion(double x, double y, double) const
    {
      /// @note Plots only go down to 75 GeV
      return (y <= x and x <= 205. / 2. and x > 75.);
    }

    OPALCharginoHadronicLimitAt208GeV::OPALCharginoHadronicLimitAt208GeV()
    {
      ///// Limit values /////
      _limitValuesSorted.push_back(0.1);
      _limitValuesSorted.push_back(1.0);
      _limitValuesSorted.push_back(2.0);

      ///// Limit Contours /////
      Corners corners;
      ContoursPointer contoursPointer;
      size_t oldSize;

      ///// 0.1pb /////
      /// @note: This limit has multiple regions, so care must be taken below
      contoursPointer = new Contours();

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(236.00,497.00));
      corners.push_back(convertPt(236.00,473.00));
      corners.push_back(convertPt(350.00,473.00));
      corners.push_back(convertPt(350.00,497.00));
      corners.push_back(convertPt(236.00,497.00));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(236.00,449.00));
      corners.push_back(convertPt(236.00,424.00));
      corners.push_back(convertPt(350.00,424.00));
      corners.push_back(convertPt(350.00,449.00));
      corners.push_back(convertPt(465.00,449.00));
      corners.push_back(convertPt(465.00,436.00));
      corners.push_back(convertPt(580.00,436.00));
      corners.push_back(convertPt(580.00,425.00));
      corners.push_back(convertPt(465.00,425.00));
      corners.push_back(convertPt(465.00,413.00));
      corners.push_back(convertPt(350.00,413.00));
      corners.push_back(convertPt(350.00,389.00));
      corners.push_back(convertPt(465.00,389.00));
      corners.push_back(convertPt(465.00,400.00));
      corners.push_back(convertPt(580.00,400.00));
      corners.push_back(convertPt(580.00,412.00));
      corners.push_back(convertPt(694.00,412.00));
      corners.push_back(convertPt(694.00,400.00));
      corners.push_back(convertPt(775.00,400.00));
      corners.push_back(convertPt(775.00,388.00));
      corners.push_back(convertPt(809.00,388.00));
      corners.push_back(convertPt(809.00,413.00));
      corners.push_back(convertPt(695.00,413.00));
      corners.push_back(convertPt(695.00,437.00));
      corners.push_back(convertPt(580.00,437.00));
      corners.push_back(convertPt(580.00,449.00));
      corners.push_back(convertPt(465.00,449.00));
      corners.push_back(convertPt(465.00,461.00));
      corners.push_back(convertPt(350.00,461.00));
      corners.push_back(convertPt(350.00,449.00));
      corners.push_back(convertPt(236.00,449.00));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(775.00,473.00));
      corners.push_back(convertPt(775.00,460.00));
      corners.push_back(convertPt(809.00,460.00));
      corners.push_back(convertPt(809.00,473.00));
      corners.push_back(convertPt(775.00,473.00));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(775.00,269.00));
      corners.push_back(convertPt(775.00,256.00));
      corners.push_back(convertPt(809.00,256.00));
      corners.push_back(convertPt(809.00,269.00));
      corners.push_back(convertPt(775.00,269.00));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(350.00,377.00));
      corners.push_back(convertPt(350.00,364.00));
      corners.push_back(convertPt(465.00,364.00));
      corners.push_back(convertPt(465.00,340.00));
      corners.push_back(convertPt(580.00,340.00));
      corners.push_back(convertPt(580.00,353.00));
      corners.push_back(convertPt(694.00,353.00));
      corners.push_back(convertPt(694.00,329.00));
      corners.push_back(convertPt(580.00,329.00));
      corners.push_back(convertPt(580.00,292.00));
      corners.push_back(convertPt(660.00,292.00));
      corners.push_back(convertPt(660.00,304.00));
      corners.push_back(convertPt(775.00,304.00));
      corners.push_back(convertPt(775.00,293.00));
      corners.push_back(convertPt(694.00,293.00));
      corners.push_back(convertPt(694.00,280.00));
      corners.push_back(convertPt(809.00,280.00));
      corners.push_back(convertPt(809.00,365.00));
      corners.push_back(convertPt(775.00,365.00));
      corners.push_back(convertPt(775.00,353.00));
      corners.push_back(convertPt(695.00,353.00));
      corners.push_back(convertPt(695.00,377.00));
      corners.push_back(convertPt(350.00,377.00));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      _limitContours.insert(LimitContourEntry(0, contoursPointer));

      ///// 1pb /////
      corners.clear();
      corners.push_back(convertPt(179.00,269.00));
      corners.push_back(convertPt(191.00,269.00));
      corners.push_back(convertPt(191.00,257.00));
      corners.push_back(convertPt(236.00,257.00));
      corners.push_back(convertPt(236.00,245.00));
      corners.push_back(convertPt(351.00,245.00));
      corners.push_back(convertPt(351.00,209.00));
      corners.push_back(convertPt(466.00,209.00));
      corners.push_back(convertPt(466.00,185.00));
      corners.push_back(convertPt(580.00,185.00));
      corners.push_back(convertPt(580.00,161.00));
      corners.push_back(convertPt(695.00,161.00));
      corners.push_back(convertPt(695.00,149.00));
      corners.push_back(convertPt(775.00,149.00));
      corners.push_back(convertPt(775.00,161.00));
      corners.push_back(convertPt(809.00,161.00));
      corners.push_back(convertPt(809.00,89.00));
      corners.push_back(convertPt(832.00,89.00));
      corners.push_back(convertPt(832.00,125.00));
      corners.push_back(convertPt(832.00,137.00));
      corners.push_back(convertPt(821.00,137.00));
      corners.push_back(convertPt(821.00,161.00));
      corners.push_back(convertPt(832.00,161.00));
      corners.push_back(convertPt(832.00,197.00));
      corners.push_back(convertPt(843.00,197.00));
      corners.push_back(convertPt(843.00,221.00));
      corners.push_back(convertPt(832.00,221.00));
      corners.push_back(convertPt(832.00,233.00));
      corners.push_back(convertPt(843.00,233.00));
      corners.push_back(convertPt(843.00,244.00));
      corners.push_back(convertPt(832.09,248.28));
      corners.push_back(convertPt(832.00,257.00));
      corners.push_back(convertPt(843.00,257.00));
      corners.push_back(convertPt(843.00,269.00));
      corners.push_back(convertPt(832.00,269.00));
      corners.push_back(convertPt(832.00,281.00));
      corners.push_back(convertPt(843.00,281.00));
      corners.push_back(convertPt(843.00,292.00));
      corners.push_back(convertPt(832.00,292.00));
      corners.push_back(convertPt(832.00,484.00));
      corners.push_back(convertPt(832.00,653.00));
      corners.push_back(convertPt(832.00,676.00));
      corners.push_back(convertPt(809.00,676.00));
      corners.push_back(convertPt(809.00,688.00));
      corners.push_back(convertPt(179.00,688.00));
      corners.push_back(convertPt(179.00,269.00));

      contoursPointer = new Contours();
      contoursPointer->resize(corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin(), makeLine);
      _limitContours.insert(LimitContourEntry(1, contoursPointer));

      ///// 2pb /////
      corners.clear();
      corners.push_back(convertPt(179.00,269.00));
      corners.push_back(convertPt(191.00,269.00));
      corners.push_back(convertPt(191.00,257.00));
      corners.push_back(convertPt(236.00,257.00));
      corners.push_back(convertPt(236.00,245.00));
      corners.push_back(convertPt(351.00,245.00));
      corners.push_back(convertPt(351.00,209.00));
      corners.push_back(convertPt(466.00,209.00));
      corners.push_back(convertPt(466.00,185.00));
      corners.push_back(convertPt(580.00,185.00));
      corners.push_back(convertPt(580.00,161.00));
      corners.push_back(convertPt(695.00,161.00));
      corners.push_back(convertPt(695.00,149.00));
      corners.push_back(convertPt(809.00,149.00));
      corners.push_back(convertPt(809.00,89.00));
      corners.push_back(convertPt(832.00,89.00));
      corners.push_back(convertPt(832.00,125.00));
      corners.push_back(convertPt(843.00,125.00));
      corners.push_back(convertPt(843.00,484.00));
      corners.push_back(convertPt(832.00,484.00));
      corners.push_back(convertPt(832.00,653.00));
      corners.push_back(convertPt(843.00,653.00));
      corners.push_back(convertPt(843.00,676.00));
      corners.push_back(convertPt(809.00,676.00));
      corners.push_back(convertPt(809.00,688.00));
      corners.push_back(convertPt(179.00,688.00));
      corners.push_back(convertPt(179.00,269.00));

      contoursPointer = new Contours();
      contoursPointer->resize(corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin(), makeLine);
      _limitContours.insert(LimitContourEntry(2, contoursPointer));

    }



    P2 OPALCharginoSemiLeptonicLimitAt208GeV::convertPt(double x, double y) const
    {
      return P2(75. + (x - 179.00) / (753.00 - 179.00) * (100. - 75.),
                100. + (y - 95.00) / (700.00 - 95.00) * (0. - 100.));
    }

    bool OPALCharginoSemiLeptonicLimitAt208GeV::isWithinExclusionRegion(double x, double y, double) const
    {
      /// @note Plots only go down to 75 GeV
      return (y <= x and x <= 205. / 2. and x > 75.);
    }

    OPALCharginoSemiLeptonicLimitAt208GeV::OPALCharginoSemiLeptonicLimitAt208GeV()
    {
      ///// Limit values /////
      _limitValuesSorted.push_back(0.05);
      _limitValuesSorted.push_back(0.1);
      _limitValuesSorted.push_back(1.0);
      _limitValuesSorted.push_back(2.0);

      ///// Limit Contours /////
      Corners corners;
      ContoursPointer contoursPointer;
      size_t oldSize;

      ///// 0.05pb /////
      /// @note: This limit has multiple regions, so care must be taken below
      contoursPointer = new Contours();

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(798.00,293.00));
      corners.push_back(convertPt(798.00,305.00));
      corners.push_back(convertPt(775.00,305.00));
      corners.push_back(convertPt(775.00,293.00));
      corners.push_back(convertPt(798.00,293.00));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(179.00,365.00));
      corners.push_back(convertPt(236.00,365.00));
      corners.push_back(convertPt(236.00,389.00));
      corners.push_back(convertPt(179.00,389.00));
      corners.push_back(convertPt(179.00,365.00));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      _limitContours.insert(LimitContourEntry(0, contoursPointer));

      ///// 0.1pb /////
      corners.clear();
      corners.push_back(convertPt(179.00,341.00));
      corners.push_back(convertPt(236.00,341.00));
      corners.push_back(convertPt(236.00,317.00));
      corners.push_back(convertPt(350.00,317.00));
      corners.push_back(convertPt(350.00,293.00));
      corners.push_back(convertPt(465.00,293.00));
      corners.push_back(convertPt(465.00,281.00));
      corners.push_back(convertPt(580.00,281.00));
      corners.push_back(convertPt(580.00,269.00));
      corners.push_back(convertPt(694.00,269.00));
      corners.push_back(convertPt(694.00,257.00));
      corners.push_back(convertPt(810.00,257.00));
      corners.push_back(convertPt(810.00,437.00));
      corners.push_back(convertPt(798.00,437.00));
      corners.push_back(convertPt(798.00,449.00));
      corners.push_back(convertPt(809.00,449.00));
      corners.push_back(convertPt(809.00,461.00));
      corners.push_back(convertPt(694.00,461.00));
      corners.push_back(convertPt(694.00,413.00));
      corners.push_back(convertPt(660.00,413.00));
      corners.push_back(convertPt(660.00,401.00));
      corners.push_back(convertPt(581.00,401.00));
      corners.push_back(convertPt(581.00,449.00));
      corners.push_back(convertPt(465.00,449.00));
      corners.push_back(convertPt(465.00,438.00));
      corners.push_back(convertPt(351.00,438.00));
      corners.push_back(convertPt(351.00,461.00));
      corners.push_back(convertPt(179.00,461.00));
      corners.push_back(convertPt(179.00,341.00));

      contoursPointer = new Contours();
      contoursPointer->resize(corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin(), makeLine);
      _limitContours.insert(LimitContourEntry(1, contoursPointer));

      ///// 1pb /////
      corners.clear();
      corners.push_back(convertPt(810.00,700.00));
      corners.push_back(convertPt(810.00,689.00));
      corners.push_back(convertPt(833.00,689.00));
      corners.push_back(convertPt(833.00,497.00));
      corners.push_back(convertPt(844.00,497.00));
      corners.push_back(convertPt(844.00,473.00));
      corners.push_back(convertPt(833.00,473.00));
      corners.push_back(convertPt(833.00,449.00));
      corners.push_back(convertPt(844.00,449.00));
      corners.push_back(convertPt(844.00,317.00));
      corners.push_back(convertPt(833.00,317.00));
      corners.push_back(convertPt(833.00,305.00));
      corners.push_back(convertPt(844.00,305.00));
      corners.push_back(convertPt(844.00,269.00));
      corners.push_back(convertPt(833.00,269.00));
      corners.push_back(convertPt(833.00,125.00));
      corners.push_back(convertPt(821.00,125.00));
      corners.push_back(convertPt(821.00,113.00));
      corners.push_back(convertPt(810.00,113.00));
      corners.push_back(convertPt(810.00,149.00));
      corners.push_back(convertPt(695.00,149.00));
      corners.push_back(convertPt(695.00,161.00));
      corners.push_back(convertPt(581.00,161.00));
      corners.push_back(convertPt(581.00,197.00));
      corners.push_back(convertPt(466.00,197.00));
      corners.push_back(convertPt(466.00,209.00));
      corners.push_back(convertPt(374.00,209.00));
      corners.push_back(convertPt(374.00,221.00));
      corners.push_back(convertPt(351.00,221.00));
      corners.push_back(convertPt(351.00,245.00));
      corners.push_back(convertPt(259.00,245.00));
      corners.push_back(convertPt(259.00,257.00));
      corners.push_back(convertPt(225.00,257.00));
      corners.push_back(convertPt(225.00,269.00));
      corners.push_back(convertPt(191.00,269.00));
      corners.push_back(convertPt(191.00,281.00));
      corners.push_back(convertPt(179.00,281.00));
      corners.push_back(convertPt(179.00,700.00));
      corners.push_back(convertPt(810.00,700.00));

      contoursPointer = new Contours();
      contoursPointer->resize(corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin(), makeLine);
      _limitContours.insert(LimitContourEntry(2, contoursPointer));

      ///// 2pb /////
      corners.clear();
      corners.push_back(convertPt(844.00,161.00));
      corners.push_back(convertPt(833.00,161.00));
      corners.push_back(convertPt(833.00,113.00));
      corners.push_back(convertPt(810.00,113.00));
      corners.push_back(convertPt(810.00,137.00));
      corners.push_back(convertPt(603.00,137.00));
      corners.push_back(convertPt(603.00,149.00));
      corners.push_back(convertPt(695.00,149.00));
      corners.push_back(convertPt(695.00,161.00));
      corners.push_back(convertPt(581.00,161.00));
      corners.push_back(convertPt(581.00,173.00));
      corners.push_back(convertPt(489.00,173.00));
      corners.push_back(convertPt(489.00,185.00));
      corners.push_back(convertPt(466.00,185.00));
      corners.push_back(convertPt(466.00,197.00));
      corners.push_back(convertPt(420.00,197.00));
      corners.push_back(convertPt(420.00,209.00));
      corners.push_back(convertPt(374.00,209.00));
      corners.push_back(convertPt(374.00,221.00));
      corners.push_back(convertPt(351.00,221.00));
      corners.push_back(convertPt(351.00,233.00));
      corners.push_back(convertPt(305.00,233.00));
      corners.push_back(convertPt(305.00,245.00));
      corners.push_back(convertPt(259.00,245.00));
      corners.push_back(convertPt(259.00,257.00));
      corners.push_back(convertPt(225.00,257.00));
      corners.push_back(convertPt(225.00,269.00));
      corners.push_back(convertPt(191.00,269.00));
      corners.push_back(convertPt(191.00,281.00));
      corners.push_back(convertPt(179.00,281.00));
      corners.push_back(convertPt(179.00,700.00));
      corners.push_back(convertPt(844.00,700.00));
      corners.push_back(convertPt(844.00,269.00));
      corners.push_back(convertPt(833.00,269.00));
      corners.push_back(convertPt(833.00,257.00));
      corners.push_back(convertPt(844.00,257.00));
      corners.push_back(convertPt(844.00,245.00));
      corners.push_back(convertPt(833.00,245.00));
      corners.push_back(convertPt(833.00,221.00));
      corners.push_back(convertPt(844.00,221.06));
      corners.push_back(convertPt(844.00,197.06));
      corners.push_back(convertPt(833.00,197.00));
      corners.push_back(convertPt(833.00,185.00));
      corners.push_back(convertPt(844.00,185.00));
      corners.push_back(convertPt(844.00,161.00));

      contoursPointer = new Contours();
      contoursPointer->resize(corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin(), makeLine);
      _limitContours.insert(LimitContourEntry(3, contoursPointer));

    }



    P2 OPALCharginoLeptonicLimitAt208GeV::convertPt(double x, double y) const
    {
      return P2(75. + (x - 185.00) / (759.00 - 185.00) * (100. - 75.),
                100. + (y - 83.00) / (689.00 - 83.00) * (0. - 100.));
    }

    bool OPALCharginoLeptonicLimitAt208GeV::isWithinExclusionRegion(double x, double y, double) const
    {
      /// @note Plots only go down to 75 GeV
      return (y <= x and x <= 205. / 2. and x > 75.);
    }

    OPALCharginoLeptonicLimitAt208GeV::OPALCharginoLeptonicLimitAt208GeV()
    {
      ///// Limit values /////
      _limitValuesSorted.push_back(0.05);
      _limitValuesSorted.push_back(0.1);
      _limitValuesSorted.push_back(1.0);
      _limitValuesSorted.push_back(2.0);

      ///// Limit Contours /////
      Corners corners;
      ContoursPointer contoursPointer;

      ///// 0.05pb /////
      corners.clear();
      corners.push_back(convertPt(185.00,473.00));
      corners.push_back(convertPt(185.00,281.00));
      corners.push_back(convertPt(243.00,281.00));
      corners.push_back(convertPt(243.00,257.00));
      corners.push_back(convertPt(357.00,257.00));
      corners.push_back(convertPt(357.00,221.00));
      corners.push_back(convertPt(472.00,221.00));
      corners.push_back(convertPt(472.00,197.00));
      corners.push_back(convertPt(587.00,197.00));
      corners.push_back(convertPt(587.00,161.00));
      corners.push_back(convertPt(701.00,161.00));
      corners.push_back(convertPt(701.00,173.00));
      corners.push_back(convertPt(782.00,173.00));
      corners.push_back(convertPt(782.00,185.00));
      corners.push_back(convertPt(816.00,185.00));
      corners.push_back(convertPt(816.00,449.00));
      corners.push_back(convertPt(782.00,449.00));
      corners.push_back(convertPt(782.00,461.00));
      corners.push_back(convertPt(701.00,461.00));
      corners.push_back(convertPt(701.00,449.00));
      corners.push_back(convertPt(587.00,449.00));
      corners.push_back(convertPt(587.00,461.00));
      corners.push_back(convertPt(472.00,461.00));
      corners.push_back(convertPt(472.00,485.00));
      corners.push_back(convertPt(242.00,485.00));
      corners.push_back(convertPt(242.00,473.00));
      corners.push_back(convertPt(185.00,473.00));

      contoursPointer = new Contours();
      contoursPointer->resize(corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin(), makeLine);
      _limitContours.insert(LimitContourEntry(0, contoursPointer));

      ///// 0.1pb /////
      corners.clear();
      corners.push_back(convertPt(242.00,689.00));
      corners.push_back(convertPt(185.00,689.00));
      corners.push_back(convertPt(185.00,269.00));
      corners.push_back(convertPt(243.00,269.00));
      corners.push_back(convertPt(243.00,245.00));
      corners.push_back(convertPt(357.00,245.00));
      corners.push_back(convertPt(357.00,209.00));
      corners.push_back(convertPt(472.00,209.00));
      corners.push_back(convertPt(472.00,185.00));
      corners.push_back(convertPt(587.00,185.00));
      corners.push_back(convertPt(587.00,149.00));
      corners.push_back(convertPt(701.00,149.00));
      corners.push_back(convertPt(701.00,137.00));
      corners.push_back(convertPt(816.00,137.00));
      corners.push_back(convertPt(816.00,161.00));
      corners.push_back(convertPt(839.00,161.00));
      corners.push_back(convertPt(839.00,425.00));
      corners.push_back(convertPt(816.00,425.00));
      corners.push_back(convertPt(816.00,557.00));
      corners.push_back(convertPt(701.00,557.00));
      corners.push_back(convertPt(701.00,593.00));
      corners.push_back(convertPt(666.00,593.00));
      corners.push_back(convertPt(666.00,582.00));
      corners.push_back(convertPt(586.00,582.00));
      corners.push_back(convertPt(586.00,630.00));
      corners.push_back(convertPt(471.00,630.00));
      corners.push_back(convertPt(471.00,641.00));
      corners.push_back(convertPt(357.00,641.00));
      corners.push_back(convertPt(357.00,677.00));
      corners.push_back(convertPt(242.00,677.00));
      corners.push_back(convertPt(242.00,689.00));

      contoursPointer = new Contours();
      contoursPointer->resize(corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin(), makeLine);
      _limitContours.insert(LimitContourEntry(1, contoursPointer));

      ///// 1pb /////
      corners.clear();
      corners.push_back(convertPt(816.00,689.00));
      corners.push_back(convertPt(816.00,665.00));
      corners.push_back(convertPt(838.00,665.00));
      corners.push_back(convertPt(838.00,545.00));
      corners.push_back(convertPt(850.00,545.00));
      corners.push_back(convertPt(850.00,125.00));
      corners.push_back(convertPt(839.00,125.00));
      corners.push_back(convertPt(839.00,78.00));
      corners.push_back(convertPt(816.00,78.00));
      corners.push_back(convertPt(816.00,113.00));
      corners.push_back(convertPt(701.00,113.00));
      corners.push_back(convertPt(701.00,137.00));
      corners.push_back(convertPt(587.00,137.00));
      corners.push_back(convertPt(587.00,173.00));
      corners.push_back(convertPt(472.00,173.00));
      corners.push_back(convertPt(472.00,197.00));
      corners.push_back(convertPt(380.00,197.00));
      corners.push_back(convertPt(380.00,209.00));
      corners.push_back(convertPt(357.00,209.00));
      corners.push_back(convertPt(357.00,233.00));
      corners.push_back(convertPt(265.00,233.00));
      corners.push_back(convertPt(265.00,245.00));
      corners.push_back(convertPt(243.00,245.00));
      corners.push_back(convertPt(243.00,257.00));
      corners.push_back(convertPt(197.00,257.00));
      corners.push_back(convertPt(197.00,269.00));
      corners.push_back(convertPt(185.00,269.00));
      corners.push_back(convertPt(185.00,689.00));
      corners.push_back(convertPt(816.00,689.00));

      contoursPointer = new Contours();
      contoursPointer->resize(corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin(), makeLine);
      _limitContours.insert(LimitContourEntry(2, contoursPointer));

      ///// 2pb /////
      corners.clear();
      corners.push_back(convertPt(816.00,689.00));
      corners.push_back(convertPt(816.00,677.00));
      corners.push_back(convertPt(850.00,677.00));
      corners.push_back(convertPt(850.00,101.00));
      corners.push_back(convertPt(839.00,101.00));
      corners.push_back(convertPt(839.00,78.00));
      corners.push_back(convertPt(816.00,78.00));
      corners.push_back(convertPt(816.00,113.00));
      corners.push_back(convertPt(701.00,113.00));
      corners.push_back(convertPt(701.00,137.00));
      corners.push_back(convertPt(587.00,137.00));
      corners.push_back(convertPt(587.00,173.00));
      corners.push_back(convertPt(472.00,173.00));
      corners.push_back(convertPt(472.00,185.00));
      corners.push_back(convertPt(426.00,185.00));
      corners.push_back(convertPt(426.00,197.00));
      corners.push_back(convertPt(380.00,197.00));
      corners.push_back(convertPt(380.00,209.00));
      corners.push_back(convertPt(357.00,209.00));
      corners.push_back(convertPt(357.00,221.00));
      corners.push_back(convertPt(311.00,221.00));
      corners.push_back(convertPt(311.00,233.00));
      corners.push_back(convertPt(265.00,233.00));
      corners.push_back(convertPt(265.00,245.00));
      corners.push_back(convertPt(231.00,245.00));
      corners.push_back(convertPt(231.00,257.00));
      corners.push_back(convertPt(197.00,257.00));
      corners.push_back(convertPt(197.00,269.00));
      corners.push_back(convertPt(185.00,269.00));
      corners.push_back(convertPt(185.00,689.00));
      corners.push_back(convertPt(816.00,689.00));

      contoursPointer = new Contours();
      contoursPointer->resize(corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin(), makeLine);
      _limitContours.insert(LimitContourEntry(3, contoursPointer));

    }



    P2 OPALCharginoAllChannelsLimitAt208GeV::convertPt(double x, double y) const
    {
      return P2(75. + (x - 176.00) / (749.00 - 176.00) * (100. - 75.),
                100. + (y - 100.00) / (705.00 - 100.00) * (0. - 100.));
    }

    bool OPALCharginoAllChannelsLimitAt208GeV::isWithinExclusionRegion(double x, double y, double) const
    {
      /// @note Plots only go down to 75 GeV
      return (y <= x and x <= 205. / 2. and x > 75.);
    }

    OPALCharginoAllChannelsLimitAt208GeV::OPALCharginoAllChannelsLimitAt208GeV()
    {
      ///// Limit values /////
      _limitValuesSorted.push_back(0.1);
      _limitValuesSorted.push_back(1.0);
      _limitValuesSorted.push_back(2.0);

      ///// Limit Contours /////
      Corners corners;
      ContoursPointer contoursPointer;
      size_t oldSize;

      ///// 0.1pb /////
      contoursPointer = new Contours();

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(806.00,262.00));
      corners.push_back(convertPt(806.00,286.00));
      corners.push_back(convertPt(795.00,286.00));
      corners.push_back(convertPt(795.00,298.00));
      corners.push_back(convertPt(806.00,298.00));
      corners.push_back(convertPt(806.00,465.00));
      corners.push_back(convertPt(692.00,465.00));
      corners.push_back(convertPt(692.00,453.00));
      corners.push_back(convertPt(772.00,453.00));
      corners.push_back(convertPt(772.00,442.00));
      corners.push_back(convertPt(692.00,442.00));
      corners.push_back(convertPt(692.00,406.00));
      corners.push_back(convertPt(577.00,406.00));
      corners.push_back(convertPt(577.00,394.00));
      corners.push_back(convertPt(656.00,394.00));
      corners.push_back(convertPt(656.00,382.00));
      corners.push_back(convertPt(462.00,382.00));
      corners.push_back(convertPt(462.00,394.00));
      corners.push_back(convertPt(347.00,394.00));
      corners.push_back(convertPt(347.00,370.00));
      corners.push_back(convertPt(462.00,370.00));
      corners.push_back(convertPt(462.00,358.00));
      corners.push_back(convertPt(577.00,358.00));
      corners.push_back(convertPt(577.00,370.00));
      corners.push_back(convertPt(691.00,370.00));
      corners.push_back(convertPt(691.00,346.00));
      corners.push_back(convertPt(577.00,346.00));
      corners.push_back(convertPt(577.00,298.00));
      corners.push_back(convertPt(771.00,298.00));
      corners.push_back(convertPt(771.00,286.00));
      corners.push_back(convertPt(691.00,286.00));
      corners.push_back(convertPt(691.00,274.00));
      corners.push_back(convertPt(771.00,274.00));
      corners.push_back(convertPt(771.00,262.00));
      corners.push_back(convertPt(806.00,262.00));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(577.00,418.00));
      corners.push_back(convertPt(577.00,430.00));
      corners.push_back(convertPt(462.00,430.00));
      corners.push_back(convertPt(462.00,418.00));
      corners.push_back(convertPt(577.00,418.00));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(794.00,490.00));
      corners.push_back(convertPt(794.00,501.00));
      corners.push_back(convertPt(772.00,501.00));
      corners.push_back(convertPt(772.00,490.00));
      corners.push_back(convertPt(794.00,490.00));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      _limitContours.insert(LimitContourEntry(0, contoursPointer));

      ///// 1pb /////
      corners.clear();
      corners.push_back(convertPt(806.00,705.00));
      corners.push_back(convertPt(806.00,693.00));
      corners.push_back(convertPt(829.00,693.00));
      corners.push_back(convertPt(829.00,502.00));
      corners.push_back(convertPt(840.00,502.00));
      corners.push_back(convertPt(840.00,466.00));
      corners.push_back(convertPt(829.00,466.00));
      corners.push_back(convertPt(829.00,453.00));
      corners.push_back(convertPt(840.00,453.00));
      corners.push_back(convertPt(840.00,274.00));
      corners.push_back(convertPt(829.00,274.00));
      corners.push_back(convertPt(829.00,262.00));
      corners.push_back(convertPt(840.00,262.00));
      corners.push_back(convertPt(840.00,250.00));
      corners.push_back(convertPt(829.00,250.00));
      corners.push_back(convertPt(829.00,130.00));
      corners.push_back(convertPt(817.00,130.00));
      corners.push_back(convertPt(817.00,118.00));
      corners.push_back(convertPt(829.00,118.00));
      corners.push_back(convertPt(829.00,106.00));
      corners.push_back(convertPt(806.00,106.00));
      corners.push_back(convertPt(806.00,154.00));
      corners.push_back(convertPt(691.00,154.00));
      corners.push_back(convertPt(691.00,166.00));
      corners.push_back(convertPt(577.00,166.00));
      corners.push_back(convertPt(577.00,202.00));
      corners.push_back(convertPt(462.00,202.00));
      corners.push_back(convertPt(462.00,214.00));
      corners.push_back(convertPt(371.00,214.00));
      corners.push_back(convertPt(371.00,226.00));
      corners.push_back(convertPt(348.00,226.00));
      corners.push_back(convertPt(348.00,250.00));
      corners.push_back(convertPt(256.00,250.00));
      corners.push_back(convertPt(256.00,262.00));
      corners.push_back(convertPt(222.00,262.00));
      corners.push_back(convertPt(222.00,274.00));
      corners.push_back(convertPt(188.00,274.00));
      corners.push_back(convertPt(188.00,286.00));
      corners.push_back(convertPt(176.00,286.00));
      corners.push_back(convertPt(176.00,705.00));
      corners.push_back(convertPt(806.00,705.00));

      contoursPointer = new Contours();
      contoursPointer->resize(corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin(), makeLine);
      _limitContours.insert(LimitContourEntry(1, contoursPointer));

      ///// 2pb /////
      corners.clear();
      corners.push_back(convertPt(806.00,705.00));
      corners.push_back(convertPt(806.00,693.00));
      corners.push_back(convertPt(840.00,693.00));
      corners.push_back(convertPt(840.00,633.00));
      corners.push_back(convertPt(829.00,633.00));
      corners.push_back(convertPt(829.00,597.00));
      corners.push_back(convertPt(840.00,597.00));
      corners.push_back(convertPt(840.00,585.00));
      corners.push_back(convertPt(829.00,585.00));
      corners.push_back(convertPt(829.00,561.00));
      corners.push_back(convertPt(840.00,561.00));
      corners.push_back(convertPt(840.00,202.00));
      corners.push_back(convertPt(829.00,202.00));
      corners.push_back(convertPt(829.00,190.00));
      corners.push_back(convertPt(840.00,190.00));
      corners.push_back(convertPt(840.00,154.00));
      corners.push_back(convertPt(829.00,154.00));
      corners.push_back(convertPt(829.00,106.00));
      corners.push_back(convertPt(806.00,106.00));
      corners.push_back(convertPt(806.00,154.00));
      corners.push_back(convertPt(691.00,154.00));
      corners.push_back(convertPt(691.00,166.00));
      corners.push_back(convertPt(577.00,166.00));
      corners.push_back(convertPt(577.00,202.00));
      corners.push_back(convertPt(462.00,202.00));
      corners.push_back(convertPt(462.00,214.00));
      corners.push_back(convertPt(371.00,214.00));
      corners.push_back(convertPt(371.00,226.00));
      corners.push_back(convertPt(348.00,226.00));
      corners.push_back(convertPt(348.00,250.00));
      corners.push_back(convertPt(256.00,250.00));
      corners.push_back(convertPt(256.00,262.00));
      corners.push_back(convertPt(222.00,262.00));
      corners.push_back(convertPt(222.00,274.00));
      corners.push_back(convertPt(188.00,274.00));
      corners.push_back(convertPt(188.00,286.00));
      corners.push_back(convertPt(176.00,286.00));
      corners.push_back(convertPt(176.00,705.00));
      corners.push_back(convertPt(806.00,705.00));

      contoursPointer = new Contours();
      contoursPointer->resize(corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin(), makeLine);
      _limitContours.insert(LimitContourEntry(2, contoursPointer));

    }



    P2 OPALNeutralinoHadronicLimitAt208GeV::convertPt(double x, double y) const
    {
      return P2(60. + (x - 231.00) / (831.00 - 231.00) * (200. - 60.),
                100. + (y - 67.00) / (684.00 - 67.00) * (0. - 100.));
    }

    bool OPALNeutralinoHadronicLimitAt208GeV::isWithinExclusionRegion(double x, double y, double) const
    {
      /// @note Plot caption explicitly mentions 100 GeV, rather than the Z mass
      return (y <= x and x + y <= 208. and x + y > 100.);
    }

    OPALNeutralinoHadronicLimitAt208GeV::OPALNeutralinoHadronicLimitAt208GeV()
    {
      ///// Limit values /////
      _limitValuesSorted.push_back(0.051);
      _limitValuesSorted.push_back(0.15);
      _limitValuesSorted.push_back(0.5);

      ///// Limit Contours /////
      Corners corners;
      ContoursPointer contoursPointer;
      size_t oldSize;

      ///// 0.051pb /////
      contoursPointer = new Contours();

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(434.00,85.00));
      corners.push_back(convertPt(434.00,97.00));
      corners.push_back(convertPt(413.00,97.00));
      corners.push_back(convertPt(413.00,85.00));
      corners.push_back(convertPt(434.00,85.00));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(391.00,134.0));
      corners.push_back(convertPt(391.00,158.0));
      corners.push_back(convertPt(370.00,158.0));
      corners.push_back(convertPt(370.00,134.0));
      corners.push_back(convertPt(391.00,134.0));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(434.00,134.0));
      corners.push_back(convertPt(434.00,146.0));
      corners.push_back(convertPt(413.00,146.0));
      corners.push_back(convertPt(413.00,134.0));
      corners.push_back(convertPt(434.00,134.0));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(434.00,158.0));
      corners.push_back(convertPt(434.00,207.0));
      corners.push_back(convertPt(455.00,207.0));
      corners.push_back(convertPt(455.00,195.0));
      corners.push_back(convertPt(499.00,195.0));
      corners.push_back(convertPt(499.00,220.0));
      corners.push_back(convertPt(477.00,220.0));
      corners.push_back(convertPt(477.00,232.0));
      corners.push_back(convertPt(499.00,232.0));
      corners.push_back(convertPt(499.00,244.0));
      corners.push_back(convertPt(520.00,244.0));
      corners.push_back(convertPt(520.00,293.0));
      corners.push_back(convertPt(477.00,293.0));
      corners.push_back(convertPt(477.00,281.0));
      corners.push_back(convertPt(434.00,281.0));
      corners.push_back(convertPt(434.00,293.0));
      corners.push_back(convertPt(413.00,293.0));
      corners.push_back(convertPt(413.00,281.0));
      corners.push_back(convertPt(434.00,281.0));
      corners.push_back(convertPt(434.00,256.0));
      corners.push_back(convertPt(413.00,256.0));
      corners.push_back(convertPt(413.00,158.0));
      corners.push_back(convertPt(434.00,158.0));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(370.00,170.0));
      corners.push_back(convertPt(370.00,183.0));
      corners.push_back(convertPt(348.00,183.0));
      corners.push_back(convertPt(348.00,170.0));
      corners.push_back(convertPt(370.00,170.0));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(477.00,256.0));
      corners.push_back(convertPt(477.00,268.0));
      corners.push_back(convertPt(499.00,268.0));
      corners.push_back(convertPt(499.00,256.0));
      corners.push_back(convertPt(477.00,256.0));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(284.00,281.0));
      corners.push_back(convertPt(284.00,293.0));
      corners.push_back(convertPt(262.00,293.0));
      corners.push_back(convertPt(262.00,281.0));
      corners.push_back(convertPt(284.00,281.0));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(520.00,305.0));
      corners.push_back(convertPt(520.00,317.0));
      corners.push_back(convertPt(542.00,317.0));
      corners.push_back(convertPt(542.00,342.0));
      corners.push_back(convertPt(585.00,342.0));
      corners.push_back(convertPt(585.00,354.0));
      corners.push_back(convertPt(606.00,354.0));
      corners.push_back(convertPt(606.00,378.0));
      corners.push_back(convertPt(649.00,378.0));
      corners.push_back(convertPt(649.00,427.0));
      corners.push_back(convertPt(670.00,427.0));
      corners.push_back(convertPt(670.00,452.0));
      corners.push_back(convertPt(692.00,452.0));
      corners.push_back(convertPt(692.00,464.0));
      corners.push_back(convertPt(713.00,464.0));
      corners.push_back(convertPt(713.00,513.0));
      corners.push_back(convertPt(734.00,513.0));
      corners.push_back(convertPt(734.00,525.0));
      corners.push_back(convertPt(756.00,525.0));
      corners.push_back(convertPt(756.00,538.0));
      corners.push_back(convertPt(734.00,538.0));
      corners.push_back(convertPt(734.00,550.0));
      corners.push_back(convertPt(756.00,550.0));
      corners.push_back(convertPt(756.00,574.0));
      corners.push_back(convertPt(777.00,574.0));
      corners.push_back(convertPt(777.00,611.0));
      corners.push_back(convertPt(799.00,611.0));
      corners.push_back(convertPt(799.00,672.0));
      corners.push_back(convertPt(584.00,672.0));
      corners.push_back(convertPt(584.00,648.0));
      corners.push_back(convertPt(563.00,648.0));
      corners.push_back(convertPt(563.00,672.0));
      corners.push_back(convertPt(477.00,672.0));
      corners.push_back(convertPt(477.00,648.0));
      corners.push_back(convertPt(456.00,648.0));
      corners.push_back(convertPt(456.00,672.0));
      corners.push_back(convertPt(413.00,672.0));
      corners.push_back(convertPt(413.00,476.0));
      corners.push_back(convertPt(434.00,476.0));
      corners.push_back(convertPt(434.00,501.0));
      corners.push_back(convertPt(456.00,501.0));
      corners.push_back(convertPt(456.00,476.0));
      corners.push_back(convertPt(477.00,476.0));
      corners.push_back(convertPt(477.00,439.0));
      corners.push_back(convertPt(520.00,439.0));
      corners.push_back(convertPt(520.00,427.0));
      corners.push_back(convertPt(499.00,427.0));
      corners.push_back(convertPt(499.00,402.0));
      corners.push_back(convertPt(520.00,402.0));
      corners.push_back(convertPt(520.00,366.0));
      corners.push_back(convertPt(541.00,366.0));
      corners.push_back(convertPt(541.00,354.0));
      corners.push_back(convertPt(520.00,354.0));
      corners.push_back(convertPt(520.00,342.0));
      corners.push_back(convertPt(477.00,342.0));
      corners.push_back(convertPt(477.00,330.0));
      corners.push_back(convertPt(455.00,330.0));
      corners.push_back(convertPt(455.00,318.0));
      corners.push_back(convertPt(434.00,318.0));
      corners.push_back(convertPt(434.00,464.0));
      corners.push_back(convertPt(413.00,464.0));
      corners.push_back(convertPt(413.00,305.0));
      corners.push_back(convertPt(520.00,305.0));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(241.00,342.0));
      corners.push_back(convertPt(241.00,354.0));
      corners.push_back(convertPt(262.00,354.0));
      corners.push_back(convertPt(262.00,379.0));
      corners.push_back(convertPt(241.00,379.0));
      corners.push_back(convertPt(241.00,366.0));
      corners.push_back(convertPt(220.00,366.0));
      corners.push_back(convertPt(220.00,342.0));
      corners.push_back(convertPt(241.00,342.0));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(370.00,342.0));
      corners.push_back(convertPt(370.00,366.0));
      corners.push_back(convertPt(348.00,366.0));
      corners.push_back(convertPt(348.00,342.0));
      corners.push_back(convertPt(370.00,342.0));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(541.00,366.0));
      corners.push_back(convertPt(541.00,378.0));
      corners.push_back(convertPt(563.00,378.0));
      corners.push_back(convertPt(563.00,366.0));
      corners.push_back(convertPt(541.00,366.0));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(391.00,378.0));
      corners.push_back(convertPt(391.00,391.0));
      corners.push_back(convertPt(370.00,391.0));
      corners.push_back(convertPt(370.00,378.0));
      corners.push_back(convertPt(391.00,378.0));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(606.00,391.0));
      corners.push_back(convertPt(606.00,403.0));
      corners.push_back(convertPt(627.00,403.0));
      corners.push_back(convertPt(627.00,391.0));
      corners.push_back(convertPt(606.00,391.0));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(348.00,391.0));
      corners.push_back(convertPt(348.00,403.0));
      corners.push_back(convertPt(327.00,403.0));
      corners.push_back(convertPt(327.00,391.0));
      corners.push_back(convertPt(348.00,391.0));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(477.00,391.0));
      corners.push_back(convertPt(477.00,403.0));
      corners.push_back(convertPt(455.00,403.0));
      corners.push_back(convertPt(455.00,391.0));
      corners.push_back(convertPt(477.00,391.0));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(263.00,439.0));
      corners.push_back(convertPt(263.00,464.0));
      corners.push_back(convertPt(241.00,464.0));
      corners.push_back(convertPt(241.00,439.0));
      corners.push_back(convertPt(263.00,439.0));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(305.00,439.0));
      corners.push_back(convertPt(305.00,464.0));
      corners.push_back(convertPt(284.00,464.0));
      corners.push_back(convertPt(284.00,439.0));
      corners.push_back(convertPt(305.00,439.0));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(305.00,476.0));
      corners.push_back(convertPt(305.00,501.0));
      corners.push_back(convertPt(284.00,501.0));
      corners.push_back(convertPt(284.00,476.0));
      corners.push_back(convertPt(305.00,476.0));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(456.00,526.0));
      corners.push_back(convertPt(456.00,550.0));
      corners.push_back(convertPt(434.00,550.0));
      corners.push_back(convertPt(434.00,562.0));
      corners.push_back(convertPt(456.00,562.0));
      corners.push_back(convertPt(456.00,574.0));
      corners.push_back(convertPt(477.00,574.0));
      corners.push_back(convertPt(477.00,586.0));
      corners.push_back(convertPt(498.00,586.0));
      corners.push_back(convertPt(498.00,550.0));
      corners.push_back(convertPt(477.00,550.0));
      corners.push_back(convertPt(477.00,526.0));
      corners.push_back(convertPt(456.00,526.0));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(456.00,598.0));
      corners.push_back(convertPt(456.00,623.0));
      corners.push_back(convertPt(477.00,623.0));
      corners.push_back(convertPt(477.00,598.0));
      corners.push_back(convertPt(456.00,598.0));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(434.00,635.0));
      corners.push_back(convertPt(434.00,648.0));
      corners.push_back(convertPt(456.00,648.0));
      corners.push_back(convertPt(456.00,635.0));
      corners.push_back(convertPt(434.00,635.0));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      _limitContours.insert(LimitContourEntry(0, contoursPointer));

      ///// 0.15pb /////
      contoursPointer = new Contours();

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(434.00,73.00));
      corners.push_back(convertPt(434.00,97.00));
      corners.push_back(convertPt(456.00,97.00));
      corners.push_back(convertPt(456.00,109.0));
      corners.push_back(convertPt(434.00,109.0));
      corners.push_back(convertPt(434.00,122.0));
      corners.push_back(convertPt(456.00,122.0));
      corners.push_back(convertPt(456.00,171.0));
      corners.push_back(convertPt(477.00,171.0));
      corners.push_back(convertPt(477.00,158.0));
      corners.push_back(convertPt(499.00,158.0));
      corners.push_back(convertPt(499.00,182.0));
      corners.push_back(convertPt(520.00,182.0));
      corners.push_back(convertPt(520.00,219.0));
      corners.push_back(convertPt(542.00,219.0));
      corners.push_back(convertPt(542.00,243.0));
      corners.push_back(convertPt(563.00,243.0));
      corners.push_back(convertPt(563.00,281.0));
      corners.push_back(convertPt(584.00,281.0));
      corners.push_back(convertPt(584.00,305.0));
      corners.push_back(convertPt(606.00,305.0));
      corners.push_back(convertPt(606.00,342.0));
      corners.push_back(convertPt(627.00,342.0));
      corners.push_back(convertPt(627.00,366.0));
      corners.push_back(convertPt(649.00,366.0));
      corners.push_back(convertPt(649.00,403.0));
      corners.push_back(convertPt(670.00,403.0));
      corners.push_back(convertPt(670.00,427.0));
      corners.push_back(convertPt(692.00,427.0));
      corners.push_back(convertPt(692.00,464.0));
      corners.push_back(convertPt(713.00,464.0));
      corners.push_back(convertPt(713.00,489.0));
      corners.push_back(convertPt(734.00,489.0));
      corners.push_back(convertPt(734.00,525.0));
      corners.push_back(convertPt(756.00,525.0));
      corners.push_back(convertPt(756.00,550.0));
      corners.push_back(convertPt(777.00,550.0));
      corners.push_back(convertPt(777.00,599.0));
      corners.push_back(convertPt(799.00,599.0));
      corners.push_back(convertPt(799.00,611.0));
      corners.push_back(convertPt(820.00,611.0));
      corners.push_back(convertPt(820.00,647.0));
      corners.push_back(convertPt(799.00,647.0));
      corners.push_back(convertPt(799.00,672.0));
      corners.push_back(convertPt(413.00,672.0));
      corners.push_back(convertPt(413.00,647.0));
      corners.push_back(convertPt(391.00,647.0));
      corners.push_back(convertPt(391.00,635.0));
      corners.push_back(convertPt(370.00,635.0));
      corners.push_back(convertPt(370.00,623.0));
      corners.push_back(convertPt(348.00,623.0));
      corners.push_back(convertPt(348.00,586.0));
      corners.push_back(convertPt(327.00,586.0));
      corners.push_back(convertPt(327.00,562.0));
      corners.push_back(convertPt(305.00,562.0));
      corners.push_back(convertPt(305.00,525.0));
      corners.push_back(convertPt(284.00,525.0));
      corners.push_back(convertPt(284.00,501.0));
      corners.push_back(convertPt(263.00,501.0));
      corners.push_back(convertPt(263.00,464.0));
      corners.push_back(convertPt(241.00,464.0));
      corners.push_back(convertPt(241.00,439.0));
      corners.push_back(convertPt(220.00,439.0));
      corners.push_back(convertPt(220.00,342.0));
      corners.push_back(convertPt(262.00,342.0));
      corners.push_back(convertPt(262.00,281.0));
      corners.push_back(convertPt(305.00,281.0));
      corners.push_back(convertPt(305.00,244.0));
      corners.push_back(convertPt(327.00,244.0));
      corners.push_back(convertPt(327.00,220.0));
      corners.push_back(convertPt(348.00,220.0));
      corners.push_back(convertPt(348.00,207.0));
      corners.push_back(convertPt(327.00,207.0));
      corners.push_back(convertPt(327.00,195.0));
      corners.push_back(convertPt(370.00,195.0));
      corners.push_back(convertPt(370.00,220.0));
      corners.push_back(convertPt(391.00,220.0));
      corners.push_back(convertPt(391.00,256.0));
      corners.push_back(convertPt(413.00,256.0));
      corners.push_back(convertPt(413.00,158.0));
      corners.push_back(convertPt(391.00,158.0));
      corners.push_back(convertPt(391.00,183.0));
      corners.push_back(convertPt(348.00,183.0));
      corners.push_back(convertPt(348.00,158.0));
      corners.push_back(convertPt(370.00,158.0));
      corners.push_back(convertPt(370.00,134.0));
      corners.push_back(convertPt(391.00,134.0));
      corners.push_back(convertPt(391.00,146.0));
      corners.push_back(convertPt(413.00,146.0));
      corners.push_back(convertPt(413.00,134.0));
      corners.push_back(convertPt(434.00,134.0));
      corners.push_back(convertPt(434.00,122.0));
      corners.push_back(convertPt(413.00,122.0));
      corners.push_back(convertPt(413.00,73.00));
      corners.push_back(convertPt(434.00,73.00));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(413.00,146.0));
      corners.push_back(convertPt(413.00,158.0));
      corners.push_back(convertPt(434.00,158.0));
      corners.push_back(convertPt(434.00,146.0));
      corners.push_back(convertPt(413.00,146.0));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(348.00,220.0));
      corners.push_back(convertPt(348.00,244.0));
      corners.push_back(convertPt(370.00,244.0));
      corners.push_back(convertPt(370.00,220.0));
      corners.push_back(convertPt(348.00,220.0));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(327.00,244.0));
      corners.push_back(convertPt(327.00,281.0));
      corners.push_back(convertPt(348.00,281.0));
      corners.push_back(convertPt(348.00,244.0));
      corners.push_back(convertPt(327.00,244.0));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(370.00,268.0));
      corners.push_back(convertPt(370.00,293.0));
      corners.push_back(convertPt(391.00,293.0));
      corners.push_back(convertPt(391.00,281.0));
      corners.push_back(convertPt(413.00,281.0));
      corners.push_back(convertPt(413.00,268.0));
      corners.push_back(convertPt(370.00,268.0));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(541.00,281.0));
      corners.push_back(convertPt(541.00,293.0));
      corners.push_back(convertPt(563.00,293.0));
      corners.push_back(convertPt(563.00,281.0));
      corners.push_back(convertPt(541.00,281.0));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(305.00,293.0));
      corners.push_back(convertPt(305.00,305.0));
      corners.push_back(convertPt(327.00,305.0));
      corners.push_back(convertPt(327.00,293.0));
      corners.push_back(convertPt(305.00,293.0));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(391.00,317.0));
      corners.push_back(convertPt(391.00,403.0));
      corners.push_back(convertPt(370.00,403.0));
      corners.push_back(convertPt(370.00,464.0));
      corners.push_back(convertPt(391.00,464.0));
      corners.push_back(convertPt(391.00,513.0));
      corners.push_back(convertPt(370.00,513.0));
      corners.push_back(convertPt(370.00,501.0));
      corners.push_back(convertPt(348.00,501.0));
      corners.push_back(convertPt(348.00,476.0));
      corners.push_back(convertPt(327.00,476.0));
      corners.push_back(convertPt(327.00,526.0));
      corners.push_back(convertPt(348.00,526.0));
      corners.push_back(convertPt(348.00,550.0));
      corners.push_back(convertPt(370.00,550.0));
      corners.push_back(convertPt(370.00,562.0));
      corners.push_back(convertPt(391.00,562.0));
      corners.push_back(convertPt(391.00,586.0));
      corners.push_back(convertPt(370.00,586.0));
      corners.push_back(convertPt(370.00,623.0));
      corners.push_back(convertPt(413.00,623.0));
      corners.push_back(convertPt(413.00,317.0));
      corners.push_back(convertPt(391.00,317.0));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(434.00,318.0));
      corners.push_back(convertPt(434.00,330.0));
      corners.push_back(convertPt(455.00,330.0));
      corners.push_back(convertPt(455.00,318.0));
      corners.push_back(convertPt(434.00,318.0));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(262.00,379.0));
      corners.push_back(convertPt(262.00,391.0));
      corners.push_back(convertPt(284.00,391.0));
      corners.push_back(convertPt(284.00,379.0));
      corners.push_back(convertPt(262.00,379.0));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(456.00,598.0));
      corners.push_back(convertPt(456.00,611.0));
      corners.push_back(convertPt(477.00,611.0));
      corners.push_back(convertPt(477.00,598.0));
      corners.push_back(convertPt(456.00,598.0));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(434.00,635.0));
      corners.push_back(convertPt(434.00,648.0));
      corners.push_back(convertPt(456.00,648.0));
      corners.push_back(convertPt(456.00,635.0));
      corners.push_back(convertPt(434.00,635.0));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      _limitContours.insert(LimitContourEntry(1, contoursPointer));

      ///// 0.5pb /////
      corners.clear();
      corners.push_back(convertPt(434.00,73.00));
      corners.push_back(convertPt(434.00,97.00));
      corners.push_back(convertPt(456.00,97.00));
      corners.push_back(convertPt(456.00,122.0));
      corners.push_back(convertPt(477.00,122.0));
      corners.push_back(convertPt(477.00,158.0));
      corners.push_back(convertPt(499.00,158.0));
      corners.push_back(convertPt(499.00,182.0));
      corners.push_back(convertPt(520.00,182.0));
      corners.push_back(convertPt(520.00,219.0));
      corners.push_back(convertPt(542.00,219.0));
      corners.push_back(convertPt(542.00,243.0));
      corners.push_back(convertPt(563.00,243.0));
      corners.push_back(convertPt(563.00,281.0));
      corners.push_back(convertPt(584.00,281.0));
      corners.push_back(convertPt(584.00,305.0));
      corners.push_back(convertPt(606.00,305.0));
      corners.push_back(convertPt(606.00,342.0));
      corners.push_back(convertPt(627.00,342.0));
      corners.push_back(convertPt(627.00,366.0));
      corners.push_back(convertPt(649.00,366.0));
      corners.push_back(convertPt(649.00,403.0));
      corners.push_back(convertPt(670.00,403.0));
      corners.push_back(convertPt(670.00,427.0));
      corners.push_back(convertPt(692.00,427.0));
      corners.push_back(convertPt(692.00,464.0));
      corners.push_back(convertPt(713.00,464.0));
      corners.push_back(convertPt(713.00,489.0));
      corners.push_back(convertPt(734.00,489.0));
      corners.push_back(convertPt(734.00,525.0));
      corners.push_back(convertPt(756.00,525.0));
      corners.push_back(convertPt(756.00,550.0));
      corners.push_back(convertPt(777.00,550.0));
      corners.push_back(convertPt(777.00,587.0));
      corners.push_back(convertPt(799.00,587.0));
      corners.push_back(convertPt(799.00,611.0));
      corners.push_back(convertPt(820.00,611.0));
      corners.push_back(convertPt(820.00,647.0));
      corners.push_back(convertPt(799.00,647.0));
      corners.push_back(convertPt(799.00,672.0));
      corners.push_back(convertPt(413.00,672.0));
      corners.push_back(convertPt(413.00,647.0));
      corners.push_back(convertPt(370.00,647.0));
      corners.push_back(convertPt(370.00,623.0));
      corners.push_back(convertPt(348.00,623.0));
      corners.push_back(convertPt(348.00,586.0));
      corners.push_back(convertPt(327.00,586.0));
      corners.push_back(convertPt(327.00,562.0));
      corners.push_back(convertPt(305.00,562.0));
      corners.push_back(convertPt(305.00,525.0));
      corners.push_back(convertPt(284.00,525.0));
      corners.push_back(convertPt(284.00,501.0));
      corners.push_back(convertPt(263.00,501.0));
      corners.push_back(convertPt(263.00,464.0));
      corners.push_back(convertPt(241.00,464.0));
      corners.push_back(convertPt(241.00,439.0));
      corners.push_back(convertPt(220.00,439.0));
      corners.push_back(convertPt(220.00,391.0));
      corners.push_back(convertPt(198.00,391.0));
      corners.push_back(convertPt(198.00,366.0));
      corners.push_back(convertPt(220.00,366.0));
      corners.push_back(convertPt(220.00,342.0));
      corners.push_back(convertPt(262.00,342.0));
      corners.push_back(convertPt(262.00,281.0));
      corners.push_back(convertPt(305.00,281.0));
      corners.push_back(convertPt(305.00,220.0));
      corners.push_back(convertPt(348.00,220.0));
      corners.push_back(convertPt(348.00,207.0));
      corners.push_back(convertPt(327.00,207.0));
      corners.push_back(convertPt(327.00,195.0));
      corners.push_back(convertPt(348.00,195.0));
      corners.push_back(convertPt(348.00,158.0));
      corners.push_back(convertPt(370.00,158.0));
      corners.push_back(convertPt(370.00,134.0));
      corners.push_back(convertPt(391.00,134.0));
      corners.push_back(convertPt(391.00,110.0));
      corners.push_back(convertPt(413.00,110.0));
      corners.push_back(convertPt(413.00,73.00));
      corners.push_back(convertPt(434.00,73.00));

      contoursPointer = new Contours();
      contoursPointer->resize(corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin(), makeLine);
      _limitContours.insert(LimitContourEntry(2, contoursPointer));

    }



    P2 OPALNeutralinoHadronicViaZLimitAt208GeV::convertPt(double x, double y) const
    {
      return P2(60. + (x - 236.00) / (835.00 - 236.00) * (200. - 60.),
                100. + (y - 76.00) / (692.00 - 76.00) * (0. - 100.));
    }

    bool OPALNeutralinoHadronicViaZLimitAt208GeV::isWithinExclusionRegion(double x, double y, double) const
    {
      /// @note Plot caption explicitly mentions 100 GeV, rather than the Z mass
      bool inHole = false;
      P2 holeCorner1 = convertPt(396.00,168.00);
      P2 holeCorner2 = convertPt(418.00,192.00);
      inHole = (x > holeCorner1.getx() and x < holeCorner2.getx()
            and y > holeCorner2.gety() and y < holeCorner1.gety());
      return (y <= x and x + y <= 208. and x + y > 100. and !inHole);
    }

    OPALNeutralinoHadronicViaZLimitAt208GeV::OPALNeutralinoHadronicViaZLimitAt208GeV()
    {
      ///// Limit values /////
      _limitValuesSorted.push_back(0.051);
      _limitValuesSorted.push_back(0.15);
      _limitValuesSorted.push_back(0.5);

      ///// Limit Contours /////
      Corners corners;
      ContoursPointer contoursPointer;
      size_t oldSize;

      ///// 0.051pb /////
      contoursPointer = new Contours();

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(439.00,241.00));
      corners.push_back(convertPt(439.00,339.00));
      corners.push_back(convertPt(418.00,339.00));
      corners.push_back(convertPt(418.00,241.00));
      corners.push_back(convertPt(439.00,241.00));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(610.00,363.00));
      corners.push_back(convertPt(610.00,411.00));
      corners.push_back(convertPt(632.00,411.00));
      corners.push_back(convertPt(632.00,473.00));
      corners.push_back(convertPt(653.00,473.00));
      corners.push_back(convertPt(653.00,497.00));
      corners.push_back(convertPt(675.00,497.00));
      corners.push_back(convertPt(675.00,509.00));
      corners.push_back(convertPt(696.00,509.00));
      corners.push_back(convertPt(696.00,522.00));
      corners.push_back(convertPt(675.00,522.00));
      corners.push_back(convertPt(675.00,534.00));
      corners.push_back(convertPt(718.00,534.00));
      corners.push_back(convertPt(718.00,546.00));
      corners.push_back(convertPt(696.00,546.00));
      corners.push_back(convertPt(696.00,558.00));
      corners.push_back(convertPt(718.00,558.00));
      corners.push_back(convertPt(718.00,570.00));
      corners.push_back(convertPt(739.00,570.00));
      corners.push_back(convertPt(739.00,595.00));
      corners.push_back(convertPt(782.00,595.00));
      corners.push_back(convertPt(782.00,631.00));
      corners.push_back(convertPt(803.00,631.00));
      corners.push_back(convertPt(803.00,680.00));
      corners.push_back(convertPt(610.00,680.00));
      corners.push_back(convertPt(610.00,668.00));
      corners.push_back(convertPt(589.00,668.00));
      corners.push_back(convertPt(589.00,656.00));
      corners.push_back(convertPt(546.00,656.00));
      corners.push_back(convertPt(546.00,680.00));
      corners.push_back(convertPt(524.00,680.00));
      corners.push_back(convertPt(524.00,656.00));
      corners.push_back(convertPt(503.00,656.00));
      corners.push_back(convertPt(503.00,680.00));
      corners.push_back(convertPt(481.00,680.00));
      corners.push_back(convertPt(481.00,644.00));
      corners.push_back(convertPt(461.00,644.00));
      corners.push_back(convertPt(461.00,631.00));
      corners.push_back(convertPt(439.00,631.00));
      corners.push_back(convertPt(439.00,668.00));
      corners.push_back(convertPt(461.00,668.00));
      corners.push_back(convertPt(461.00,680.00));
      corners.push_back(convertPt(418.00,680.00));
      corners.push_back(convertPt(418.00,558.00));
      corners.push_back(convertPt(439.00,558.00));
      corners.push_back(convertPt(439.00,570.00));
      corners.push_back(convertPt(461.00,570.00));
      corners.push_back(convertPt(461.00,607.00));
      corners.push_back(convertPt(439.00,607.00));
      corners.push_back(convertPt(439.00,619.00));
      corners.push_back(convertPt(461.00,619.00));
      corners.push_back(convertPt(461.00,631.00));
      corners.push_back(convertPt(482.00,631.00));
      corners.push_back(convertPt(482.00,619.00));
      corners.push_back(convertPt(503.00,619.00));
      corners.push_back(convertPt(503.00,595.00));
      corners.push_back(convertPt(546.00,595.00));
      corners.push_back(convertPt(546.00,571.00));
      corners.push_back(convertPt(524.00,571.00));
      corners.push_back(convertPt(524.00,558.00));
      corners.push_back(convertPt(546.00,558.00));
      corners.push_back(convertPt(546.00,534.00));
      corners.push_back(convertPt(567.00,534.00));
      corners.push_back(convertPt(567.00,509.00));
      corners.push_back(convertPt(589.00,509.00));
      corners.push_back(convertPt(589.00,534.00));
      corners.push_back(convertPt(610.00,534.00));
      corners.push_back(convertPt(610.00,558.00));
      corners.push_back(convertPt(632.00,558.00));
      corners.push_back(convertPt(632.00,497.00));
      corners.push_back(convertPt(567.00,497.00));
      corners.push_back(convertPt(567.00,473.00));
      corners.push_back(convertPt(546.00,473.00));
      corners.push_back(convertPt(546.00,485.00));
      corners.push_back(convertPt(524.00,485.00));
      corners.push_back(convertPt(524.00,448.00));
      corners.push_back(convertPt(546.00,448.00));
      corners.push_back(convertPt(546.00,461.00));
      corners.push_back(convertPt(589.00,461.00));
      corners.push_back(convertPt(589.00,473.00));
      corners.push_back(convertPt(610.00,473.00));
      corners.push_back(convertPt(610.00,436.00));
      corners.push_back(convertPt(524.00,436.00));
      corners.push_back(convertPt(524.00,387.00));
      corners.push_back(convertPt(546.00,387.00));
      corners.push_back(convertPt(546.00,411.00));
      corners.push_back(convertPt(567.00,411.00));
      corners.push_back(convertPt(567.00,387.00));
      corners.push_back(convertPt(589.00,387.00));
      corners.push_back(convertPt(589.00,363.00));
      corners.push_back(convertPt(610.00,363.00));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(589.00,411.00));
      corners.push_back(convertPt(589.00,424.00));
      corners.push_back(convertPt(610.00,424.00));
      corners.push_back(convertPt(610.00,411.00));
      corners.push_back(convertPt(589.00,411.00));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(482.00,521.00));
      corners.push_back(convertPt(482.00,534.00));
      corners.push_back(convertPt(460.00,534.00));
      corners.push_back(convertPt(460.00,521.00));
      corners.push_back(convertPt(482.00,521.00));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(589.00,631.00));
      corners.push_back(convertPt(589.00,644.00));
      corners.push_back(convertPt(610.00,644.00));
      corners.push_back(convertPt(610.00,631.00));
      corners.push_back(convertPt(589.00,631.00));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(610.00,656.00));
      corners.push_back(convertPt(610.00,668.00));
      corners.push_back(convertPt(632.00,668.00));
      corners.push_back(convertPt(632.00,656.00));
      corners.push_back(convertPt(610.00,656.00));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      _limitContours.insert(LimitContourEntry(0, contoursPointer));

      ///// 0.15pb /////
      contoursPointer = new Contours();

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(439.00,143.00));
      corners.push_back(convertPt(439.00,155.00));
      corners.push_back(convertPt(418.00,155.00));
      corners.push_back(convertPt(418.00,143.00));
      corners.push_back(convertPt(439.00,143.00));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(396.00,155.00));
      corners.push_back(convertPt(396.00,168.00));
      corners.push_back(convertPt(375.00,168.00));
      corners.push_back(convertPt(375.00,155.00));
      corners.push_back(convertPt(396.00,155.00));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(439.00,168.00));
      corners.push_back(convertPt(439.00,192.00));
      corners.push_back(convertPt(461.00,192.00));
      corners.push_back(convertPt(461.00,180.00));
      corners.push_back(convertPt(481.00,180.00));
      corners.push_back(convertPt(481.00,192.00));
      corners.push_back(convertPt(503.00,192.00));
      corners.push_back(convertPt(503.00,204.00));
      corners.push_back(convertPt(524.00,204.00));
      corners.push_back(convertPt(524.00,228.00));
      corners.push_back(convertPt(546.00,228.00));
      corners.push_back(convertPt(546.00,241.00));
      corners.push_back(convertPt(524.00,241.00));
      corners.push_back(convertPt(524.00,253.00));
      corners.push_back(convertPt(567.00,253.00));
      corners.push_back(convertPt(567.00,290.00));
      corners.push_back(convertPt(589.00,290.00));
      corners.push_back(convertPt(589.00,314.00));
      corners.push_back(convertPt(610.00,314.00));
      corners.push_back(convertPt(610.00,326.00));
      corners.push_back(convertPt(589.00,326.00));
      corners.push_back(convertPt(589.00,351.00));
      corners.push_back(convertPt(632.00,351.00));
      corners.push_back(convertPt(632.00,387.00));
      corners.push_back(convertPt(653.00,387.00));
      corners.push_back(convertPt(653.00,411.00));
      corners.push_back(convertPt(675.00,411.00));
      corners.push_back(convertPt(675.00,448.00));
      corners.push_back(convertPt(696.00,448.00));
      corners.push_back(convertPt(696.00,473.00));
      corners.push_back(convertPt(718.00,473.00));
      corners.push_back(convertPt(718.00,497.00));
      corners.push_back(convertPt(739.00,497.00));
      corners.push_back(convertPt(739.00,534.00));
      corners.push_back(convertPt(760.00,534.00));
      corners.push_back(convertPt(760.00,558.00));
      corners.push_back(convertPt(782.00,558.00));
      corners.push_back(convertPt(782.00,607.00));
      corners.push_back(convertPt(803.00,607.00));
      corners.push_back(convertPt(803.00,631.00));
      corners.push_back(convertPt(824.00,631.00));
      corners.push_back(convertPt(824.00,656.00));
      corners.push_back(convertPt(803.00,656.00));
      corners.push_back(convertPt(803.00,680.00));
      corners.push_back(convertPt(418.00,680.00));
      corners.push_back(convertPt(418.00,656.00));
      corners.push_back(convertPt(396.00,656.00));
      corners.push_back(convertPt(396.00,644.00));
      corners.push_back(convertPt(418.00,644.00));
      corners.push_back(convertPt(418.00,168.00));
      corners.push_back(convertPt(439.00,168.00));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(461.00,192.00));
      corners.push_back(convertPt(461.00,204.00));
      corners.push_back(convertPt(481.00,204.00));
      corners.push_back(convertPt(481.00,192.00));
      corners.push_back(convertPt(461.00,192.00));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(503.00,228.00));
      corners.push_back(convertPt(503.00,241.00));
      corners.push_back(convertPt(524.00,241.00));
      corners.push_back(convertPt(524.00,228.00));
      corners.push_back(convertPt(503.00,228.00));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(482.00,241.00));
      corners.push_back(convertPt(482.00,253.00));
      corners.push_back(convertPt(503.00,253.00));
      corners.push_back(convertPt(503.00,241.00));
      corners.push_back(convertPt(482.00,241.00));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(546.00,290.00));
      corners.push_back(convertPt(546.00,302.00));
      corners.push_back(convertPt(567.00,302.00));
      corners.push_back(convertPt(567.00,290.00));
      corners.push_back(convertPt(546.00,290.00));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(546.00,314.00));
      corners.push_back(convertPt(546.00,325.00));
      corners.push_back(convertPt(567.00,325.00));
      corners.push_back(convertPt(567.00,314.00));
      corners.push_back(convertPt(546.00,314.00));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(396.00,315.00));
      corners.push_back(convertPt(396.00,326.00));
      corners.push_back(convertPt(375.00,326.00));
      corners.push_back(convertPt(375.00,315.00));
      corners.push_back(convertPt(396.00,315.00));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(439.00,326.00));
      corners.push_back(convertPt(439.00,351.00));
      corners.push_back(convertPt(460.00,351.00));
      corners.push_back(convertPt(460.00,326.00));
      corners.push_back(convertPt(439.00,326.00));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(396.00,351.00));
      corners.push_back(convertPt(396.00,412.00));
      corners.push_back(convertPt(375.00,412.00));
      corners.push_back(convertPt(375.00,387.00));
      corners.push_back(convertPt(353.00,387.00));
      corners.push_back(convertPt(353.00,412.00));
      corners.push_back(convertPt(331.00,412.00));
      corners.push_back(convertPt(331.00,387.00));
      corners.push_back(convertPt(353.00,387.00));
      corners.push_back(convertPt(353.00,351.00));
      corners.push_back(convertPt(396.00,351.00));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(267.00,363.00));
      corners.push_back(convertPt(267.00,387.00));
      corners.push_back(convertPt(246.00,387.00));
      corners.push_back(convertPt(246.00,363.00));
      corners.push_back(convertPt(267.00,363.00));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(460.00,375.00));
      corners.push_back(convertPt(460.00,387.00));
      corners.push_back(convertPt(482.00,387.00));
      corners.push_back(convertPt(482.00,375.00));
      corners.push_back(convertPt(460.00,375.00));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(267.00,424.00));
      corners.push_back(convertPt(267.00,436.00));
      corners.push_back(convertPt(311.00,436.00));
      corners.push_back(convertPt(311.00,424.00));
      corners.push_back(convertPt(331.00,424.00));
      corners.push_back(convertPt(331.00,461.00));
      corners.push_back(convertPt(310.00,461.00));
      corners.push_back(convertPt(310.00,473.00));
      corners.push_back(convertPt(331.00,473.00));
      corners.push_back(convertPt(331.00,497.00));
      corners.push_back(convertPt(310.00,497.00));
      corners.push_back(convertPt(310.00,534.00));
      corners.push_back(convertPt(289.00,534.00));
      corners.push_back(convertPt(289.00,497.00));
      corners.push_back(convertPt(268.00,497.00));
      corners.push_back(convertPt(268.00,473.00));
      corners.push_back(convertPt(246.00,473.00));
      corners.push_back(convertPt(246.00,448.00));
      corners.push_back(convertPt(225.00,448.00));
      corners.push_back(convertPt(225.00,436.00));
      corners.push_back(convertPt(246.00,436.00));
      corners.push_back(convertPt(246.00,424.00));
      corners.push_back(convertPt(267.00,424.00));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(439.00,436.00));
      corners.push_back(convertPt(439.00,449.00));
      corners.push_back(convertPt(460.00,449.00));
      corners.push_back(convertPt(460.00,473.00));
      corners.push_back(convertPt(482.00,473.00));
      corners.push_back(convertPt(482.00,436.00));
      corners.push_back(convertPt(439.00,436.00));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(439.00,485.00));
      corners.push_back(convertPt(439.00,510.00));
      corners.push_back(convertPt(460.00,510.00));
      corners.push_back(convertPt(460.00,485.00));
      corners.push_back(convertPt(439.00,485.00));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(460.00,534.00));
      corners.push_back(convertPt(460.00,546.00));
      corners.push_back(convertPt(482.00,546.00));
      corners.push_back(convertPt(482.00,534.00));
      corners.push_back(convertPt(460.00,534.00));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(482.00,583.00));
      corners.push_back(convertPt(482.00,595.00));
      corners.push_back(convertPt(503.00,595.00));
      corners.push_back(convertPt(503.00,583.00));
      corners.push_back(convertPt(482.00,583.00));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(353.00,583.00));
      corners.push_back(convertPt(353.00,595.00));
      corners.push_back(convertPt(332.00,595.00));
      corners.push_back(convertPt(332.00,583.00));
      corners.push_back(convertPt(353.00,583.00));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(461.00,607.00));
      corners.push_back(convertPt(461.00,631.00));
      corners.push_back(convertPt(482.00,631.00));
      corners.push_back(convertPt(482.00,607.00));
      corners.push_back(convertPt(461.00,607.00));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      _limitContours.insert(LimitContourEntry(1, contoursPointer));

      ///// 0.5pb /////
      corners.clear();
      corners.push_back(convertPt(439.00,82.00));
      corners.push_back(convertPt(439.00,106.0));
      corners.push_back(convertPt(460.00,106.0));
      corners.push_back(convertPt(460.00,119.0));
      corners.push_back(convertPt(439.00,119.0));
      corners.push_back(convertPt(439.00,131.0));
      corners.push_back(convertPt(481.00,131.0));
      corners.push_back(convertPt(481.00,168.0));
      corners.push_back(convertPt(503.00,168.0));
      corners.push_back(convertPt(503.00,192.0));
      corners.push_back(convertPt(524.00,192.0));
      corners.push_back(convertPt(524.00,228.0));
      corners.push_back(convertPt(546.00,228.0));
      corners.push_back(convertPt(546.00,253.0));
      corners.push_back(convertPt(567.00,253.0));
      corners.push_back(convertPt(567.00,290.0));
      corners.push_back(convertPt(589.00,290.0));
      corners.push_back(convertPt(589.00,314.0));
      corners.push_back(convertPt(610.00,314.0));
      corners.push_back(convertPt(610.00,351.0));
      corners.push_back(convertPt(632.00,351.0));
      corners.push_back(convertPt(632.00,375.0));
      corners.push_back(convertPt(653.00,375.0));
      corners.push_back(convertPt(653.00,411.0));
      corners.push_back(convertPt(675.00,411.0));
      corners.push_back(convertPt(675.00,436.0));
      corners.push_back(convertPt(696.00,436.0));
      corners.push_back(convertPt(696.00,473.0));
      corners.push_back(convertPt(718.00,473.0));
      corners.push_back(convertPt(718.00,497.0));
      corners.push_back(convertPt(739.00,497.0));
      corners.push_back(convertPt(739.00,534.0));
      corners.push_back(convertPt(760.00,534.0));
      corners.push_back(convertPt(760.00,558.0));
      corners.push_back(convertPt(782.00,558.0));
      corners.push_back(convertPt(782.00,595.0));
      corners.push_back(convertPt(803.00,595.0));
      corners.push_back(convertPt(803.00,619.0));
      corners.push_back(convertPt(824.00,619.0));
      corners.push_back(convertPt(824.00,656.0));
      corners.push_back(convertPt(803.00,656.0));
      corners.push_back(convertPt(803.00,680.0));
      corners.push_back(convertPt(418.00,680.0));
      corners.push_back(convertPt(418.00,656.0));
      corners.push_back(convertPt(375.00,656.0));
      corners.push_back(convertPt(375.00,631.0));
      corners.push_back(convertPt(353.00,631.0));
      corners.push_back(convertPt(353.00,595.0));
      corners.push_back(convertPt(332.00,595.0));
      corners.push_back(convertPt(332.00,570.0));
      corners.push_back(convertPt(310.00,570.0));
      corners.push_back(convertPt(310.00,534.0));
      corners.push_back(convertPt(289.00,534.0));
      corners.push_back(convertPt(289.00,509.0));
      corners.push_back(convertPt(268.00,509.0));
      corners.push_back(convertPt(268.00,473.0));
      corners.push_back(convertPt(246.00,473.0));
      corners.push_back(convertPt(246.00,448.0));
      corners.push_back(convertPt(225.00,448.0));
      corners.push_back(convertPt(225.00,351.0));
      corners.push_back(convertPt(267.00,351.0));
      corners.push_back(convertPt(267.00,290.0));
      corners.push_back(convertPt(311.00,290.0));
      corners.push_back(convertPt(311.00,253.0));
      corners.push_back(convertPt(332.00,253.0));
      corners.push_back(convertPt(332.00,228.0));
      corners.push_back(convertPt(353.00,228.0));
      corners.push_back(convertPt(353.00,216.0));
      corners.push_back(convertPt(332.00,216.0));
      corners.push_back(convertPt(332.00,204.0));
      corners.push_back(convertPt(353.00,204.0));
      corners.push_back(convertPt(353.00,180.0));
      corners.push_back(convertPt(375.00,180.0));
      corners.push_back(convertPt(375.00,143.0));
      corners.push_back(convertPt(396.00,143.0));
      corners.push_back(convertPt(396.00,131.0));
      corners.push_back(convertPt(418.00,131.0));
      corners.push_back(convertPt(418.00,82.00));
      corners.push_back(convertPt(439.00,82.00));

      contoursPointer = new Contours();
      contoursPointer->resize(corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin(), makeLine);
      _limitContours.insert(LimitContourEntry(2, contoursPointer));

    }

  }
}
