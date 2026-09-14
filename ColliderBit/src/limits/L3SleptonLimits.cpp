#include "gambit/ColliderBit/limits/L3SleptonLimits.hpp"

namespace Gambit {
  namespace ColliderBit {


    P2 L3SelectronLimitAt205GeV::convertPt(double x, double y) const
    {
      return P2(45. + (x - 159.00) / (700.00 - 159.00) * (100. - 45.),
                100. + (y - 40.50) / (610.00 - 40.50) * (0. - 100.));
    }

    /// @brief Check to see if the point is within the exclusion region
    bool L3SelectronLimitAt205GeV::isWithinExclusionRegion(double x, double y, double mZ) const
    {
      return (y <= x and x <= 205. / 2. and x > mZ / 2.);
    }

    L3SelectronLimitAt205GeV::L3SelectronLimitAt205GeV()
    {
      ///// Limit values /////
      _limitValuesSorted.push_back(0.03);
      _limitValuesSorted.push_back(0.06);
      _limitValuesSorted.push_back(0.2);

      ///// Limit Contours /////
      Corners corners;
      ContoursPointer contoursPointer;
      size_t oldSize;

      ///// 0.03pb /////
      contoursPointer = new Contours();

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(512.00,298.00));
      corners.push_back(convertPt(542.00,270.00));
      corners.push_back(convertPt(640.00,207.00));
      corners.push_back(convertPt(673.00,208.00));
      corners.push_back(convertPt(680.00,220.00));
      corners.push_back(convertPt(707.00,218.00));
      corners.push_back(convertPt(705.00,237.00));
      corners.push_back(convertPt(679.00,253.00));
      corners.push_back(convertPt(679.00,272.00));
      corners.push_back(convertPt(691.00,274.00));
      corners.push_back(convertPt(685.00,288.00));
      corners.push_back(convertPt(685.00,300.00));
      corners.push_back(convertPt(699.00,291.00));
      corners.push_back(convertPt(697.00,337.00));
      corners.push_back(convertPt(628.00,354.00));
      corners.push_back(convertPt(575.00,341.00));
      corners.push_back(convertPt(561.00,307.00));
      corners.push_back(convertPt(512.00,301.00));
      corners.push_back(convertPt(512.00,298.00));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      corners.clear();
      oldSize = contoursPointer->size();
      corners.push_back(convertPt(510.00,218.00));
      corners.push_back(convertPt(562.00,185.00));
      corners.push_back(convertPt(564.00,178.00));
      corners.push_back(convertPt(634.00,138.00));
      corners.push_back(convertPt(645.00,123.00));
      corners.push_back(convertPt(650.00,123.00));
      corners.push_back(convertPt(651.00,137.00));
      corners.push_back(convertPt(659.00,139.00));
      corners.push_back(convertPt(675.00,124.00));
      corners.push_back(convertPt(682.00,130.00));
      corners.push_back(convertPt(682.00,154.00));
      corners.push_back(convertPt(657.00,164.00));
      corners.push_back(convertPt(650.00,183.00));
      corners.push_back(convertPt(588.00,201.00));
      corners.push_back(convertPt(578.00,201.00));
      corners.push_back(convertPt(539.00,218.00));
      corners.push_back(convertPt(513.00,221.00));
      corners.push_back(convertPt(510.00,218.00));
      contoursPointer->resize(oldSize + corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin() + oldSize, makeLine);

      _limitContours.insert(LimitContourEntry(0, contoursPointer));

      ///// 0.06pb /////
      corners.clear();
      corners.push_back(convertPt(648.00,608.00));
      corners.push_back(convertPt(629.00,589.00));
      corners.push_back(convertPt(615.00,565.00));
      corners.push_back(convertPt(601.00,536.00));
      corners.push_back(convertPt(586.00,520.00));
      corners.push_back(convertPt(584.00,504.00));
      corners.push_back(convertPt(608.00,494.00));
      corners.push_back(convertPt(584.00,485.00));
      corners.push_back(convertPt(581.00,477.00));
      corners.push_back(convertPt(551.47,475.49));
      corners.push_back(convertPt(551.47,469.00));
      corners.push_back(convertPt(600.00,436.00));
      corners.push_back(convertPt(599.00,412.00));
      corners.push_back(convertPt(563.00,407.00));
      corners.push_back(convertPt(525.00,422.00));
      corners.push_back(convertPt(518.00,398.00));
      corners.push_back(convertPt(425.00,402.00));
      corners.push_back(convertPt(392.00,403.00));
      corners.push_back(convertPt(346.00,394.00));
      corners.push_back(convertPt(370.00,371.00));
      corners.push_back(convertPt(366.00,371.00));
      corners.push_back(convertPt(317.00,389.00));
      corners.push_back(convertPt(261.00,406.00));
      corners.push_back(convertPt(235.00,403.00));
      corners.push_back(convertPt(266.00,389.00));
      corners.push_back(convertPt(270.00,375.00));
      corners.push_back(convertPt(293.00,366.00));
      corners.push_back(convertPt(315.00,355.00));
      corners.push_back(convertPt(331.00,340.00));
      corners.push_back(convertPt(384.00,318.00));
      corners.push_back(convertPt(429.00,298.00));
      corners.push_back(convertPt(451.00,285.00));
      corners.push_back(convertPt(452.00,278.00));
      corners.push_back(convertPt(450.00,275.00));
      corners.push_back(convertPt(420.00,279.00));
      corners.push_back(convertPt(414.00,295.00));
      corners.push_back(convertPt(362.00,305.00));
      corners.push_back(convertPt(325.00,324.00));
      corners.push_back(convertPt(290.00,340.00));
      corners.push_back(convertPt(260.00,347.00));
      corners.push_back(convertPt(243.00,355.00));
      corners.push_back(convertPt(454.00,229.00));
      corners.push_back(convertPt(534.00,182.00));
      corners.push_back(convertPt(598.00,139.00));
      corners.push_back(convertPt(629.00,127.00));
      corners.push_back(convertPt(672.00,106.00));
      corners.push_back(convertPt(714.00,88.00 ));
      corners.push_back(convertPt(719.00,92.00 ));
      corners.push_back(convertPt(725.00,102.00));
      corners.push_back(convertPt(726.00,108.00));
      corners.push_back(convertPt(726.00,138.00));
      corners.push_back(convertPt(716.00,164.00));
      corners.push_back(convertPt(706.38,165.42));
      corners.push_back(convertPt(703.38,169.58));
      corners.push_back(convertPt(703.00,187.00));
      corners.push_back(convertPt(722.00,190.00));
      corners.push_back(convertPt(726.00,207.00));
      corners.push_back(convertPt(727.00,256.00));
      corners.push_back(convertPt(721.00,256.00));
      corners.push_back(convertPt(720.00,380.00));
      corners.push_back(convertPt(710.00,385.00));
      corners.push_back(convertPt(713.00,422.00));
      corners.push_back(convertPt(718.00,425.00));
      corners.push_back(convertPt(719.00,429.00));
      corners.push_back(convertPt(711.00,479.00));
      corners.push_back(convertPt(710.00,515.00));
      corners.push_back(convertPt(700.00,522.00));
      corners.push_back(convertPt(689.00,508.00));
      corners.push_back(convertPt(664.00,513.00));
      corners.push_back(convertPt(655.00,563.00));
      corners.push_back(convertPt(648.00,608.00));

      contoursPointer = new Contours();
      contoursPointer->resize(corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin(), makeLine);
      _limitContours.insert(LimitContourEntry(1, contoursPointer));

      ///// 0.2pb /////
      corners.clear();
      corners.push_back(convertPt(159.00,378.00));
      corners.push_back(convertPt(330.00,282.00));
      corners.push_back(convertPt(360.00,260.00));
      corners.push_back(convertPt(400.00,251.00));
      corners.push_back(convertPt(613.00,126.00));
      corners.push_back(convertPt(641.00,100.00));
      corners.push_back(convertPt(650.00,110.00));
      corners.push_back(convertPt(655.00,108.00));
      corners.push_back(convertPt(681.00,93.00));
      corners.push_back(convertPt(710.00,73.00));
      corners.push_back(convertPt(727.00,66.00));
      corners.push_back(convertPt(728.00,258.00));
      corners.push_back(convertPt(728.00,378.00));
      corners.push_back(convertPt(729.00,392.00));
      corners.push_back(convertPt(729.00,565.00));
      corners.push_back(convertPt(719.00,575.00));
      corners.push_back(convertPt(718.00,610.00));
      corners.push_back(convertPt(251.00,610.00));
      corners.push_back(convertPt(227.00,586.00));
      corners.push_back(convertPt(199.83,583.96));
      corners.push_back(convertPt(181.00,565.00));
      corners.push_back(convertPt(159.00,559.00));
      corners.push_back(convertPt(159.00,378.00));

      contoursPointer = new Contours();
      contoursPointer->resize(corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin(), makeLine);
      _limitContours.insert(LimitContourEntry(2, contoursPointer));

    }



    P2 L3SmuonLimitAt205GeV::convertPt(double x, double y) const
    {
      return P2(45. + (x - 1092.00) / (1633.00 - 1092.00) * (100. - 45.),
                100. + (y - 40.50) / (610.00 - 40.50) * (0. - 100.));
    }

    bool L3SmuonLimitAt205GeV::isWithinExclusionRegion(double x, double y, double mZ) const
    {
      return (y <= x and x <= 205. / 2. and x > mZ / 2.);
    }

    L3SmuonLimitAt205GeV::L3SmuonLimitAt205GeV()
    {
      ///// Limit values /////
      _limitValuesSorted.push_back(0.04);
      _limitValuesSorted.push_back(0.07);
      _limitValuesSorted.push_back(0.15);

      ///// Limit Contours /////
      Corners corners;
      ContoursPointer contoursPointer;

      ///// 0.04pb /////
      corners.clear();
      corners.push_back(convertPt(1226.00,351.00));
      corners.push_back(convertPt(1414.00,235.00));
      corners.push_back(convertPt(1531.00,175.00));
      corners.push_back(convertPt(1620.00,134.00));
      corners.push_back(convertPt(1630.00,137.00));
      corners.push_back(convertPt(1647.00,128.00));
      corners.push_back(convertPt(1659.00,117.00));
      corners.push_back(convertPt(1663.00,167.00));
      corners.push_back(convertPt(1655.00,172.00));
      corners.push_back(convertPt(1654.00,198.00));
      corners.push_back(convertPt(1644.00,199.00));
      corners.push_back(convertPt(1643.00,248.00));
      corners.push_back(convertPt(1595.00,277.00));
      corners.push_back(convertPt(1592.61,297.00));
      corners.push_back(convertPt(1595.00,360.00));
      corners.push_back(convertPt(1578.00,378.00));
      corners.push_back(convertPt(1469.00,374.00));
      corners.push_back(convertPt(1450.00,380.00));
      corners.push_back(convertPt(1445.00,380.00));
      corners.push_back(convertPt(1447.00,368.00));
      corners.push_back(convertPt(1508.00,334.00));
      corners.push_back(convertPt(1535.00,329.00));
      corners.push_back(convertPt(1549.00,322.00));
      corners.push_back(convertPt(1520.00,322.00));
      corners.push_back(convertPt(1488.00,330.00));
      corners.push_back(convertPt(1455.00,331.00));
      corners.push_back(convertPt(1426.00,329.00));
      corners.push_back(convertPt(1337.00,360.00));
      corners.push_back(convertPt(1328.00,360.00));
      corners.push_back(convertPt(1326.00,353.00));
      corners.push_back(convertPt(1340.00,333.00));
      corners.push_back(convertPt(1324.00,335.00));
      corners.push_back(convertPt(1311.00,343.00));
      corners.push_back(convertPt(1291.00,351.00));
      corners.push_back(convertPt(1265.00,358.00));
      corners.push_back(convertPt(1233.00,357.00));
      corners.push_back(convertPt(1226.00,354.00));
      corners.push_back(convertPt(1226.00,351.00));

      contoursPointer = new Contours();
      contoursPointer->resize(corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin(), makeLine);
      _limitContours.insert(LimitContourEntry(0, contoursPointer));

      ///// 0.07pb /////
      corners.clear();
      corners.push_back(convertPt(1094.00,444.00));
      corners.push_back(convertPt(1152.00,363.00));
      corners.push_back(convertPt(1171.00,362.00));
      corners.push_back(convertPt(1241.00,318.00));
      corners.push_back(convertPt(1258.00,317.00));
      corners.push_back(convertPt(1298.00,294.00));
      corners.push_back(convertPt(1299.00,285.00));
      corners.push_back(convertPt(1384.00,238.00));
      corners.push_back(convertPt(1397.00,238.00));
      corners.push_back(convertPt(1402.00,236.00));
      corners.push_back(convertPt(1447.00,202.00));
      corners.push_back(convertPt(1463.00,193.00));
      corners.push_back(convertPt(1505.00,167.00));
      corners.push_back(convertPt(1621.00,95.00 ));
      corners.push_back(convertPt(1629.00,104.00));
      corners.push_back(convertPt(1656.00,84.00 ));
      corners.push_back(convertPt(1664.00,111.00));
      corners.push_back(convertPt(1672.00,111.00));
      corners.push_back(convertPt(1662.50,363.00));
      corners.push_back(convertPt(1658.00,395.00));
      corners.push_back(convertPt(1623.00,399.00));
      corners.push_back(convertPt(1620.00,395.00));
      corners.push_back(convertPt(1618.00,382.00));
      corners.push_back(convertPt(1615.00,382.00));
      corners.push_back(convertPt(1598.00,392.00));
      corners.push_back(convertPt(1596.00,435.00));
      corners.push_back(convertPt(1593.00,552.00));
      corners.push_back(convertPt(1576.00,553.00));
      corners.push_back(convertPt(1562.00,553.00));
      corners.push_back(convertPt(1543.00,530.00));
      corners.push_back(convertPt(1529.00,510.00));
      corners.push_back(convertPt(1567.00,476.00));
      corners.push_back(convertPt(1567.00,465.00));
      corners.push_back(convertPt(1563.00,464.00));
      corners.push_back(convertPt(1551.00,466.00));
      corners.push_back(convertPt(1424.00,459.00));
      corners.push_back(convertPt(1360.00,470.00));
      corners.push_back(convertPt(1349.00,464.00));
      corners.push_back(convertPt(1325.00,464.00));
      corners.push_back(convertPt(1306.00,473.00));
      corners.push_back(convertPt(1251.00,476.00));
      corners.push_back(convertPt(1245.00,477.00));
      corners.push_back(convertPt(1226.00,474.00));
      corners.push_back(convertPt(1210.00,481.00));
      corners.push_back(convertPt(1173.00,474.00));
      corners.push_back(convertPt(1146.00,486.00));
      corners.push_back(convertPt(1135.00,472.00));
      corners.push_back(convertPt(1123.00,463.00));
      corners.push_back(convertPt(1126.00,459.00));
      corners.push_back(convertPt(1149.00,452.00));
      corners.push_back(convertPt(1172.00,442.00));
      corners.push_back(convertPt(1150.00,439.00));
      corners.push_back(convertPt(1134.00,435.00));
      corners.push_back(convertPt(1123.00,440.00));
      corners.push_back(convertPt(1112.00,439.00));
      corners.push_back(convertPt(1101.00,446.00));
      corners.push_back(convertPt(1094.00,444.00));

      contoursPointer = new Contours();
      contoursPointer->resize(corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin(), makeLine);
      _limitContours.insert(LimitContourEntry(1, contoursPointer));

      ///// 0.15pb /////
      corners.clear();
      corners.push_back(convertPt(1672.00,610.0));
      corners.push_back(convertPt(1092.00,610.0));
      corners.push_back(convertPt(1092.00,369.0));
      corners.push_back(convertPt(1159.00,330.0));
      corners.push_back(convertPt(1168.00,340.0));
      corners.push_back(convertPt(1196.00,328.0));
      corners.push_back(convertPt(1203.00,306.0));
      corners.push_back(convertPt(1590.00,88.00));
      corners.push_back(convertPt(1599.00,96.00));
      corners.push_back(convertPt(1638.00,71.00));
      corners.push_back(convertPt(1666.00,60.00));
      corners.push_back(convertPt(1672.00,61.00));
      corners.push_back(convertPt(1672.00,610.0));

      contoursPointer = new Contours();
      contoursPointer->resize(corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin(), makeLine);
      _limitContours.insert(LimitContourEntry(2, contoursPointer));

    }



    P2 L3StauLimitAt205GeV::convertPt(double x, double y) const
    {
      return P2(45. + (x - 625.00) / (1166.00 - 625.00) * (100. - 45.),
                100. + (y - 948.50) / (1518.00 - 948.50) * (0. - 100.));
    }

    bool L3StauLimitAt205GeV::isWithinExclusionRegion(double x, double y, double mZ) const
    {
      return (y <= x and x <= 205. / 2. and x > mZ / 2.);
    }

    L3StauLimitAt205GeV::L3StauLimitAt205GeV()
    {
      ///// Limit values /////
      _limitValuesSorted.push_back(0.1);
      _limitValuesSorted.push_back(0.15);
      _limitValuesSorted.push_back(0.2);

      ///// Limit Contours /////
      Corners corners;
      ContoursPointer contoursPointer;

      ///// 0.1pb /////
      corners.clear();
      corners.push_back(convertPt(835.00,1216.00));
      corners.push_back(convertPt(930.00,1168.00));
      corners.push_back(convertPt(956.00,1165.00));
      corners.push_back(convertPt(955.00,1147.00));
      corners.push_back(convertPt(1030.00,1110.0));
      corners.push_back(convertPt(1044.00,1110.0));
      corners.push_back(convertPt(1086.00,1076.0));
      corners.push_back(convertPt(1107.00,1079.0));
      corners.push_back(convertPt(1116.00,1082.0));
      corners.push_back(convertPt(1122.00,1108.0));
      corners.push_back(convertPt(1150.00,1121.0));
      corners.push_back(convertPt(1126.00,1155.0));
      corners.push_back(convertPt(1122.00,1168.0));
      corners.push_back(convertPt(1139.00,1185.0));
      corners.push_back(convertPt(1154.00,1188.0));
      corners.push_back(convertPt(1159.00,1192.0));
      corners.push_back(convertPt(1153.00,1207.0));
      corners.push_back(convertPt(1152.00,1228.0));
      corners.push_back(convertPt(1123.00,1236.0));
      corners.push_back(convertPt(1119.00,1261.0));
      corners.push_back(convertPt(1094.00,1287.0));
      corners.push_back(convertPt(1064.00,1287.0));
      corners.push_back(convertPt(1044.00,1284.0));
      corners.push_back(convertPt(1044.00,1281.0));
      corners.push_back(convertPt(1073.00,1267.0));
      corners.push_back(convertPt(1062.00,1254.0));
      corners.push_back(convertPt(1036.00,1267.0));
      corners.push_back(convertPt(1003.00,1272.0));
      corners.push_back(convertPt(992.00,1278.00));
      corners.push_back(convertPt(960.00,1278.00));
      corners.push_back(convertPt(939.00,1277.00));
      corners.push_back(convertPt(957.00,1265.00));
      corners.push_back(convertPt(995.00,1243.00));
      corners.push_back(convertPt(1010.00,1232.0));
      corners.push_back(convertPt(1008.00,1212.0));
      corners.push_back(convertPt(1029.00,1203.0));
      corners.push_back(convertPt(1029.00,1189.0));
      corners.push_back(convertPt(1004.00,1202.0));
      corners.push_back(convertPt(989.00,1204.00));
      corners.push_back(convertPt(973.00,1208.00));
      corners.push_back(convertPt(958.00,1214.00));
      corners.push_back(convertPt(950.00,1214.00));
      corners.push_back(convertPt(946.00,1210.00));
      corners.push_back(convertPt(958.00,1205.00));
      corners.push_back(convertPt(993.00,1188.00));
      corners.push_back(convertPt(1008.00,1177.0));
      corners.push_back(convertPt(1016.00,1169.0));
      corners.push_back(convertPt(1026.00,1155.0));
      corners.push_back(convertPt(1026.00,1146.0));
      corners.push_back(convertPt(989.00,1167.00));
      corners.push_back(convertPt(979.00,1180.00));
      corners.push_back(convertPt(976.00,1181.00));
      corners.push_back(convertPt(963.00,1182.00));
      corners.push_back(convertPt(922.00,1211.00));
      corners.push_back(convertPt(904.00,1216.00));
      corners.push_back(convertPt(874.00,1222.00));
      corners.push_back(convertPt(843.00,1222.00));
      corners.push_back(convertPt(835.00,1216.00));

      contoursPointer = new Contours();
      contoursPointer->resize(corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin(), makeLine);
      _limitContours.insert(LimitContourEntry(0, contoursPointer));

      ///// 0.15pb /////
      corners.clear();
      corners.push_back(convertPt(764.00,1518.00));
      corners.push_back(convertPt(766.00,1510.00));
      corners.push_back(convertPt(771.00,1508.00));
      corners.push_back(convertPt(790.00,1510.00));
      corners.push_back(convertPt(794.00,1508.00));
      corners.push_back(convertPt(798.00,1459.00));
      corners.push_back(convertPt(805.00,1458.00));
      corners.push_back(convertPt(807.00,1453.00));
      corners.push_back(convertPt(804.00,1434.00));
      corners.push_back(convertPt(825.00,1424.00));
      corners.push_back(convertPt(837.00,1421.00));
      corners.push_back(convertPt(855.00,1415.00));
      corners.push_back(convertPt(866.00,1410.00));
      corners.push_back(convertPt(878.00,1409.00));
      corners.push_back(convertPt(880.00,1397.00));
      corners.push_back(convertPt(855.00,1397.00));
      corners.push_back(convertPt(855.00,1391.00));
      corners.push_back(convertPt(851.00,1387.00));
      corners.push_back(convertPt(839.00,1388.00));
      corners.push_back(convertPt(836.00,1385.00));
      corners.push_back(convertPt(840.00,1378.00));
      corners.push_back(convertPt(848.00,1372.00));
      corners.push_back(convertPt(860.00,1371.00));
      corners.push_back(convertPt(878.00,1365.00));
      corners.push_back(convertPt(862.00,1357.00));
      corners.push_back(convertPt(849.00,1356.00));
      corners.push_back(convertPt(813.00,1364.00));
      corners.push_back(convertPt(802.00,1359.00));
      corners.push_back(convertPt(784.00,1366.00));
      corners.push_back(convertPt(774.00,1373.00));
      corners.push_back(convertPt(736.00,1376.00));
      corners.push_back(convertPt(719.00,1382.00));
      corners.push_back(convertPt(688.00,1379.00));
      corners.push_back(convertPt(688.00,1376.00));
      corners.push_back(convertPt(698.00,1368.44));
      corners.push_back(convertPt(711.00,1367.00));
      corners.push_back(convertPt(713.00,1362.00));
      corners.push_back(convertPt(714.00,1358.00));
      corners.push_back(convertPt(694.00,1357.00));
      corners.push_back(convertPt(695.00,1349.00));
      corners.push_back(convertPt(714.00,1341.00));
      corners.push_back(convertPt(732.00,1343.00));
      corners.push_back(convertPt(733.00,1323.00));
      corners.push_back(convertPt(749.00,1314.00));
      corners.push_back(convertPt(757.52,1304.48));
      corners.push_back(convertPt(780.00,1294.00));
      corners.push_back(convertPt(781.00,1290.00));
      corners.push_back(convertPt(776.00,1289.00));
      corners.push_back(convertPt(752.00,1298.00));
      corners.push_back(convertPt(723.00,1306.00));
      corners.push_back(convertPt(719.00,1294.00));
      corners.push_back(convertPt(758.00,1280.00));
      corners.push_back(convertPt(762.00,1261.00));
      corners.push_back(convertPt(761.00,1255.00));
      corners.push_back(convertPt(755.00,1253.00));
      corners.push_back(convertPt(756.00,1250.00));
      corners.push_back(convertPt(790.00,1229.00));
      corners.push_back(convertPt(810.48,1226.00));
      corners.push_back(convertPt(812.00,1214.00));
      corners.push_back(convertPt(817.00,1210.00));
      corners.push_back(convertPt(867.00,1186.00));
      corners.push_back(convertPt(885.00,1183.00));
      corners.push_back(convertPt(944.00,1148.00));
      corners.push_back(convertPt(980.00,1123.00));
      corners.push_back(convertPt(1021.00,1111.0));
      corners.push_back(convertPt(1033.00,1107.0));
      corners.push_back(convertPt(1034.00,1091.0));
      corners.push_back(convertPt(1113.00,1062.0));
      corners.push_back(convertPt(1116.00,1065.0));
      corners.push_back(convertPt(1124.00,1076.0));
      corners.push_back(convertPt(1128.00,1077.0));
      corners.push_back(convertPt(1146.00,1075.0));
      corners.push_back(convertPt(1149.00,1069.0));
      corners.push_back(convertPt(1152.00,1066.0));
      corners.push_back(convertPt(1170.00,1070.0));
      corners.push_back(convertPt(1184.00,1077.0));
      corners.push_back(convertPt(1188.00,1093.0));
      corners.push_back(convertPt(1182.00,1102.0));
      corners.push_back(convertPt(1181.00,1107.0));
      corners.push_back(convertPt(1189.00,1108.0));
      corners.push_back(convertPt(1189.00,1274.0));
      corners.push_back(convertPt(1184.00,1324.0));
      corners.push_back(convertPt(1187.00,1385.0));
      corners.push_back(convertPt(1189.00,1434.0));
      corners.push_back(convertPt(1188.00,1472.0));
      corners.push_back(convertPt(1184.00,1518.0));
      corners.push_back(convertPt(764.00,1518.00));

      contoursPointer = new Contours();
      contoursPointer->resize(corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin(), makeLine);
      _limitContours.insert(LimitContourEntry(1, contoursPointer));

      ///// 0.2pb /////
      corners.clear();
      corners.push_back(convertPt(1202.00,1518.0));
      corners.push_back(convertPt(625.00,1518.00));
      corners.push_back(convertPt(625.00,1298.00));
      corners.push_back(convertPt(682.00,1266.00));
      corners.push_back(convertPt(705.00,1262.00));
      corners.push_back(convertPt(713.00,1258.00));
      corners.push_back(convertPt(758.00,1223.00));
      corners.push_back(convertPt(775.00,1218.00));
      corners.push_back(convertPt(786.00,1214.00));
      corners.push_back(convertPt(807.00,1209.00));
      corners.push_back(convertPt(816.00,1206.00));
      corners.push_back(convertPt(842.00,1186.00));
      corners.push_back(convertPt(862.00,1176.00));
      corners.push_back(convertPt(981.00,1109.00));
      corners.push_back(convertPt(998.00,1103.00));
      corners.push_back(convertPt(1039.00,1085.0));
      corners.push_back(convertPt(1081.00,1058.0));
      corners.push_back(convertPt(1113.00,1049.0));
      corners.push_back(convertPt(1156.00,1047.0));
      corners.push_back(convertPt(1190.00,1050.0));
      corners.push_back(convertPt(1194.00,1057.0));
      corners.push_back(convertPt(1199.00,1062.0));
      corners.push_back(convertPt(1206.00,1062.0));
      corners.push_back(convertPt(1205.00,1086.0));
      corners.push_back(convertPt(1198.00,1097.0));
      corners.push_back(convertPt(1197.00,1108.0));
      corners.push_back(convertPt(1196.00,1174.0));
      corners.push_back(convertPt(1198.00,1181.0));
      corners.push_back(convertPt(1206.00,1181.0));
      corners.push_back(convertPt(1206.00,1369.0));
      corners.push_back(convertPt(1202.00,1391.0));
      corners.push_back(convertPt(1202.00,1518.0));

      contoursPointer = new Contours();
      contoursPointer->resize(corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin(), makeLine);
      _limitContours.insert(LimitContourEntry(2, contoursPointer));

    }

  }
}
