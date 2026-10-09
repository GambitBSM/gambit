#include "gambit/ColliderBit/limits/L3SmallDeltaMGauginoLimits.hpp"

namespace Gambit {
  namespace ColliderBit {


    P2 L3ChargedGauginoSmallDeltaMWithHeavySneutrinoLimitAt188pt6GeV::convertPt(double x, double y) const
    {
      return P2(45. + (x - 138.00) / (1014.00 - 138.00) * (95. - 45.),
                4. + (y - 56.00) / (239.00 - 56.00) * (0. - 4.));
    }

    bool L3ChargedGauginoSmallDeltaMWithHeavySneutrinoLimitAt188pt6GeV::isWithinExclusionRegion(double x, double y, double) const
    {
      return (y <= x and x <= 188.6 / 2.);
    }

    L3ChargedGauginoSmallDeltaMWithHeavySneutrinoLimitAt188pt6GeV::L3ChargedGauginoSmallDeltaMWithHeavySneutrinoLimitAt188pt6GeV() {
      ///// Limit values /////
      _limitValuesSorted.push_back(1.0);
      _limitValuesSorted.push_back(2.0);
      _limitValuesSorted.push_back(4.0);
      _limitValuesSorted.push_back(6.0);

      ///// Limit Contours /////
      Corners corners;
      ContoursPointer contoursPointer;

      ///// 1pb /////
      corners.clear();
      corners.push_back(convertPt(138.00,234.00));
      corners.push_back(convertPt(302.00,231.00));
      corners.push_back(convertPt(503.00,225.00));
      corners.push_back(convertPt(474.00,217.00));
      corners.push_back(convertPt(465.00,193.00));
      corners.push_back(convertPt(341.00,158.00));
      corners.push_back(convertPt(167.00,103.00));
      corners.push_back(convertPt(138.00,62.00));
      corners.push_back(convertPt(138.00,234.00));

      contoursPointer = new Contours();
      contoursPointer->resize(corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin(), makeLine);
      _limitContours.insert(LimitContourEntry(0, contoursPointer));

      ///// 2pb /////
      corners.clear();
      corners.push_back(convertPt(138.00,234.00));
      corners.push_back(convertPt(489.00,232.00));
      corners.push_back(convertPt(664.00,231.00));
      corners.push_back(convertPt(693.00,230.00));
      corners.push_back(convertPt(729.00,224.00));
      corners.push_back(convertPt(719.00,215.00));
      corners.push_back(convertPt(728.00,192.00));
      corners.push_back(convertPt(707.00,146.00));
      corners.push_back(convertPt(561.00,101.00));
      corners.push_back(convertPt(263.00,56.00));
      corners.push_back(convertPt(138.00,56.00));
      corners.push_back(convertPt(138.00,234.00));

      contoursPointer = new Contours();
      contoursPointer->resize(corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin(), makeLine);
      _limitContours.insert(LimitContourEntry(1, contoursPointer));

      ///// 4pb /////
      corners.clear();
      corners.push_back(convertPt(138.00,234.00));
      corners.push_back(convertPt(489.00,232.00));
      corners.push_back(convertPt(752.00,231.00));
      corners.push_back(convertPt(832.00,230.00));
      corners.push_back(convertPt(833.00,224.00));
      corners.push_back(convertPt(838.00,216.00));
      corners.push_back(convertPt(839.00,192.00));
      corners.push_back(convertPt(824.00,145.00));
      corners.push_back(convertPt(742.00,101.00));
      corners.push_back(convertPt(731.00,56.00));
      corners.push_back(convertPt(138.00,56.00));
      corners.push_back(convertPt(138.00,234.00));

      contoursPointer = new Contours();
      contoursPointer->resize(corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin(), makeLine);
      _limitContours.insert(LimitContourEntry(2, contoursPointer));

      ///// 6pb /////
      corners.clear();
      corners.push_back(convertPt(138.00,234.00));
      corners.push_back(convertPt(490.00,233.00));
      corners.push_back(convertPt(752.00,232.00));
      corners.push_back(convertPt(845.00,230.00));
      corners.push_back(convertPt(852.00,229.00));
      corners.push_back(convertPt(852.00,208.00));
      corners.push_back(convertPt(854.00,190.00));
      corners.push_back(convertPt(852.00,143.00));
      corners.push_back(convertPt(840.00,101.00));
      corners.push_back(convertPt(795.00,56.00));
      corners.push_back(convertPt(138.00,56.00));
      corners.push_back(convertPt(138.00,234.00));

      contoursPointer = new Contours();
      contoursPointer->resize(corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin(), makeLine);
      _limitContours.insert(LimitContourEntry(3, contoursPointer));

    }



    P2 L3ChargedGauginoSmallDeltaMAnySneutrinoLimitAt188pt6GeV::convertPt(double x, double y) const
    {
      return P2(45. + (x - 140.00) / (1017.00 - 140.00) * (95. - 45.),
                4. + (y - 415.00) / (598.00 - 415.00) * (0. - 4.));
    }

    bool L3ChargedGauginoSmallDeltaMAnySneutrinoLimitAt188pt6GeV::isWithinExclusionRegion(double x, double y, double) const
    {
      return (y <= x and x <= 188.6 / 2.);
    }

    L3ChargedGauginoSmallDeltaMAnySneutrinoLimitAt188pt6GeV::L3ChargedGauginoSmallDeltaMAnySneutrinoLimitAt188pt6GeV()
    {
      ///// Limit values /////
      _limitValuesSorted.push_back(1.0);
      _limitValuesSorted.push_back(2.0);
      _limitValuesSorted.push_back(4.0);
      _limitValuesSorted.push_back(6.0);

      ///// Limit Contours /////
      Corners corners;
      ContoursPointer contoursPointer;

      ///// 1pb /////
      corners.clear();
      corners.push_back(convertPt(140.00,415.00));
      corners.push_back(convertPt(143.00,415.00));
      corners.push_back(convertPt(168.00,461.00));
      corners.push_back(convertPt(262.00,507.00));
      corners.push_back(convertPt(372.00,552.00));
      corners.push_back(convertPt(370.00,577.00));
      corners.push_back(convertPt(376.00,584.00));
      corners.push_back(convertPt(265.00,590.00));
      corners.push_back(convertPt(140.00,598.00));
      corners.push_back(convertPt(140.00,415.00));

      contoursPointer = new Contours();
      contoursPointer->resize(corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin(), makeLine);
      _limitContours.insert(LimitContourEntry(0, contoursPointer));

      ///// 2pb /////
      corners.clear();
      corners.push_back(convertPt(140.00,415.00));
      corners.push_back(convertPt(238.00,415.00));
      corners.push_back(convertPt(412.00,458.00));
      corners.push_back(convertPt(639.00,506.00));
      corners.push_back(convertPt(650.00,550.00));
      corners.push_back(convertPt(679.00,574.00));
      corners.push_back(convertPt(630.00,588.00));
      corners.push_back(convertPt(608.00,591.00));
      corners.push_back(convertPt(526.00,593.00));
      corners.push_back(convertPt(140.00,598.00));
      corners.push_back(convertPt(140.00,415.00));

      contoursPointer = new Contours();
      contoursPointer->resize(corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin(), makeLine);
      _limitContours.insert(LimitContourEntry(1, contoursPointer));

      ///// 4pb /////
      corners.clear();
      corners.push_back(convertPt(140.00,415.00));
      corners.push_back(convertPt(469.00,415.00));
      corners.push_back(convertPt(705.00,459.00));
      corners.push_back(convertPt(785.00,506.00));
      corners.push_back(convertPt(801.00,553.00));
      corners.push_back(convertPt(800.00,583.00));
      corners.push_back(convertPt(791.00,588.00));
      corners.push_back(convertPt(699.00,596.00));
      corners.push_back(convertPt(526.00,597.00));
      corners.push_back(convertPt(140.00,598.00));
      corners.push_back(convertPt(140.00,415.00));

      contoursPointer = new Contours();
      contoursPointer->resize(corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin(), makeLine);
      _limitContours.insert(LimitContourEntry(2, contoursPointer));

      ///// 6pb /////
      corners.clear();
      corners.push_back(convertPt(140.00,415.00));
      corners.push_back(convertPt(765.00,415.00));
      corners.push_back(convertPt(773.00,428.00));
      corners.push_back(convertPt(825.00,506.00));
      corners.push_back(convertPt(835.00,548.00));
      corners.push_back(convertPt(836.00,574.00));
      corners.push_back(convertPt(829.00,588.00));
      corners.push_back(convertPt(798.00,592.00));
      corners.push_back(convertPt(745.00,595.00));
      corners.push_back(convertPt(526.00,597.00));
      corners.push_back(convertPt(140.00,598.00));
      corners.push_back(convertPt(140.00,415.00));

      contoursPointer = new Contours();
      contoursPointer->resize(corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin(), makeLine);
      _limitContours.insert(LimitContourEntry(3, contoursPointer));

    }



    P2 L3ChargedHiggsinoSmallDeltaMLimitAt188pt6GeV::convertPt(double x, double y) const
    {
      return P2(45. + (x - 141.00) / (1018.00 - 141.00) * (95. - 45.),
                4. + (y - 772.00) / (956.00 - 772.00) * (0. - 4.));
    }

    bool L3ChargedHiggsinoSmallDeltaMLimitAt188pt6GeV::isWithinExclusionRegion(double x, double y, double) const
    {
      return (y <= x and x <= 188.6 / 2.);
    }

    L3ChargedHiggsinoSmallDeltaMLimitAt188pt6GeV::L3ChargedHiggsinoSmallDeltaMLimitAt188pt6GeV()
    {
      ///// Limit values /////
      _limitValuesSorted.push_back(1.0);
      _limitValuesSorted.push_back(2.0);
      _limitValuesSorted.push_back(4.0);
      _limitValuesSorted.push_back(6.0);

      ///// Limit Contours /////
      Corners corners;
      ContoursPointer contoursPointer;

      ///// 1pb /////
      corners.clear();
      corners.push_back(convertPt(141.00,820.00));
      corners.push_back(convertPt(223.00,865.00));
      corners.push_back(convertPt(394.00,910.00));
      corners.push_back(convertPt(404.00,943.00));
      corners.push_back(convertPt(141.00,950.00));
      corners.push_back(convertPt(141.00,820.00));

      contoursPointer = new Contours();
      contoursPointer->resize(corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin(), makeLine);
      _limitContours.insert(LimitContourEntry(0, contoursPointer));

      ///// 2pb /////
      corners.clear();
      corners.push_back(convertPt(141.00,772.00));
      corners.push_back(convertPt(181.00,772.00));
      corners.push_back(convertPt(551.00,817.00));
      corners.push_back(convertPt(692.00,863.00));
      corners.push_back(convertPt(720.00,910.00));
      corners.push_back(convertPt(712.00,933.00));
      corners.push_back(convertPt(727.00,942.00));
      corners.push_back(convertPt(684.00,947.00));
      corners.push_back(convertPt(653.00,948.00));
      corners.push_back(convertPt(141.00,950.00));
      corners.push_back(convertPt(141.00,772.00));

      contoursPointer = new Contours();
      contoursPointer->resize(corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin(), makeLine);
      _limitContours.insert(LimitContourEntry(1, contoursPointer));

      ///// 4pb /////
      corners.clear();
      corners.push_back(convertPt(141.00,772.00));
      corners.push_back(convertPt(728.00,772.00));
      corners.push_back(convertPt(737.00,817.00));
      corners.push_back(convertPt(821.00,863.00));
      corners.push_back(convertPt(835.00,907.00));
      corners.push_back(convertPt(837.00,931.00));
      corners.push_back(convertPt(827.00,947.00));
      corners.push_back(convertPt(783.00,948.00));
      corners.push_back(convertPt(735.00,948.00));
      corners.push_back(convertPt(141.00,950.00));
      corners.push_back(convertPt(141.00,772.00));

      contoursPointer = new Contours();
      contoursPointer->resize(corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin(), makeLine);
      _limitContours.insert(LimitContourEntry(2, contoursPointer));

      ///// 6pb /////
      corners.clear();
      corners.push_back(convertPt(141.00,772.00));
      corners.push_back(convertPt(790.00,772.00));
      corners.push_back(convertPt(841.00,816.00));
      corners.push_back(convertPt(860.00,862.00));
      corners.push_back(convertPt(862.00,905.00));
      corners.push_back(convertPt(859.00,939.00));
      corners.push_back(convertPt(861.00,946.00));
      corners.push_back(convertPt(850.00,948.00));
      corners.push_back(convertPt(787.00,949.00));
      corners.push_back(convertPt(141.00,950.00));
      corners.push_back(convertPt(141.00,772.00));

      contoursPointer = new Contours();
      contoursPointer->resize(corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin(), makeLine);
      _limitContours.insert(LimitContourEntry(3, contoursPointer));

    }

  }
}
