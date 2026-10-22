#include "gambit/ColliderBit/limits/L3GauginoLimits.hpp"

namespace Gambit {
  namespace ColliderBit {


    P2 L3CharginoAllChannelsLimitAt188pt6GeV::convertPt(double x, double y) const
    {
      return P2(45. + (x - 1171.00) / (1792.00 - 1171.00) * (100. - 45.),
                100. + (y - 23.00) / (622.00 - 23.00) * (0. - 100.));
    }

    bool L3CharginoAllChannelsLimitAt188pt6GeV::isWithinExclusionRegion(double x, double y, double mZ) const
    {
      return (y <= x and x <= 188.6 / 2. and x > mZ / 2.);
    }

    L3CharginoAllChannelsLimitAt188pt6GeV::L3CharginoAllChannelsLimitAt188pt6GeV()
    {
      ///// Limit values /////
      _limitValuesSorted.push_back(0.1);
      _limitValuesSorted.push_back(0.2);
      _limitValuesSorted.push_back(0.3);
      _limitValuesSorted.push_back(0.5);
      _limitValuesSorted.push_back(2.0);

      ///// Limit Contours /////
      Corners corners;
      ContoursPointer contoursPointer;

      ///// 0.1pb /////
      corners.clear();
      corners.push_back(convertPt(1731.00,172.00));
      corners.push_back(convertPt(1731.00,338.00));
      corners.push_back(convertPt(1712.00,339.00));
      corners.push_back(convertPt(1687.00,366.00));
      corners.push_back(convertPt(1647.00,373.00));
      corners.push_back(convertPt(1646.00,365.00));
      corners.push_back(convertPt(1643.00,300.00));
      corners.push_back(convertPt(1632.00,299.00));
      corners.push_back(convertPt(1630.00,313.00));
      corners.push_back(convertPt(1625.00,316.50));
      corners.push_back(convertPt(1597.00,316.00));
      corners.push_back(convertPt(1576.00,331.00));
      corners.push_back(convertPt(1532.00,346.00));
      corners.push_back(convertPt(1524.00,377.00));
      corners.push_back(convertPt(1520.00,378.00));
      corners.push_back(convertPt(1505.00,360.00));
      corners.push_back(convertPt(1497.00,353.00));
      corners.push_back(convertPt(1477.00,344.00));
      corners.push_back(convertPt(1454.00,326.00));
      corners.push_back(convertPt(1453.00,312.00));
      corners.push_back(convertPt(1460.00,307.00));
      corners.push_back(convertPt(1501.00,282.00));
      corners.push_back(convertPt(1559.00,249.00));
      corners.push_back(convertPt(1653.00,211.00));
      corners.push_back(convertPt(1686.00,188.00));
      corners.push_back(convertPt(1731.00,172.00));

      contoursPointer = new Contours();
      contoursPointer->resize(corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin(), makeLine);
      _limitContours.insert(LimitContourEntry(0, contoursPointer));

      ///// 0.2pb /////
      corners.clear();
      corners.push_back(convertPt(1171.00,447.00));
      corners.push_back(convertPt(1203.48,446.00));
      corners.push_back(convertPt(1205.00,402.00));
      corners.push_back(convertPt(1237.50,400.48));
      corners.push_back(convertPt(1248.00,375.00));
      corners.push_back(convertPt(1329.00,335.00));
      corners.push_back(convertPt(1344.00,328.00));
      corners.push_back(convertPt(1388.00,297.00));
      corners.push_back(convertPt(1508.00,241.00));
      corners.push_back(convertPt(1645.00,177.00));
      corners.push_back(convertPt(1672.00,164.00));
      corners.push_back(convertPt(1703.00,152.00));
      corners.push_back(convertPt(1731.00,141.00));
      corners.push_back(convertPt(1731.00,421.00));
      corners.push_back(convertPt(1710.00,422.00));
      corners.push_back(convertPt(1714.00,505.00));
      corners.push_back(convertPt(1681.00,512.00));
      corners.push_back(convertPt(1672.00,511.00));
      corners.push_back(convertPt(1645.00,500.00));
      corners.push_back(convertPt(1643.00,472.00));
      corners.push_back(convertPt(1639.00,472.00));
      corners.push_back(convertPt(1607.00,478.00));
      corners.push_back(convertPt(1552.00,506.00));
      corners.push_back(convertPt(1464.00,520.00));
      corners.push_back(convertPt(1379.00,530.00));
      corners.push_back(convertPt(1372.00,530.00));
      corners.push_back(convertPt(1341.00,518.00));
      corners.push_back(convertPt(1283.00,512.00));
      corners.push_back(convertPt(1270.00,544.00));
      corners.push_back(convertPt(1267.00,544.00));
      corners.push_back(convertPt(1252.00,502.00));
      corners.push_back(convertPt(1239.00,458.00));
      corners.push_back(convertPt(1227.00,511.00));
      corners.push_back(convertPt(1209.00,512.00));
      corners.push_back(convertPt(1171.00,525.00));
      corners.push_back(convertPt(1171.00,447.00));

      contoursPointer = new Contours();
      contoursPointer->resize(corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin(), makeLine);
      _limitContours.insert(LimitContourEntry(1, contoursPointer));

      ///// 0.3pb /////
      corners.clear();
      corners.push_back(convertPt(1171.00,411.00));
      corners.push_back(convertPt(1204.00,385.00));
      corners.push_back(convertPt(1254.00,359.00));
      corners.push_back(convertPt(1287.00,343.00));
      corners.push_back(convertPt(1294.00,340.00));
      corners.push_back(convertPt(1339.00,312.00));
      corners.push_back(convertPt(1351.00,305.00));
      corners.push_back(convertPt(1394.00,285.00));
      corners.push_back(convertPt(1430.00,268.00));
      corners.push_back(convertPt(1466.00,252.00));
      corners.push_back(convertPt(1514.00,231.00));
      corners.push_back(convertPt(1569.00,206.00));
      corners.push_back(convertPt(1633.00,177.00));
      corners.push_back(convertPt(1675.00,154.00));
      corners.push_back(convertPt(1731.00,124.00));
      corners.push_back(convertPt(1731.00,488.00));
      corners.push_back(convertPt(1716.00,494.00));
      corners.push_back(convertPt(1715.00,505.00));
      corners.push_back(convertPt(1712.00,509.00));
      corners.push_back(convertPt(1710.39,535.00));
      corners.push_back(convertPt(1706.00,537.00));
      corners.push_back(convertPt(1676.00,541.00));
      corners.push_back(convertPt(1659.00,543.00));
      corners.push_back(convertPt(1637.56,539.58));
      corners.push_back(convertPt(1633.00,540.00));
      corners.push_back(convertPt(1573.00,566.00));
      corners.push_back(convertPt(1569.00,566.00));
      corners.push_back(convertPt(1552.00,562.00));
      corners.push_back(convertPt(1531.00,556.00));
      corners.push_back(convertPt(1527.00,557.00));
      corners.push_back(convertPt(1507.00,567.00));
      corners.push_back(convertPt(1460.00,575.00));
      corners.push_back(convertPt(1432.00,579.00));
      corners.push_back(convertPt(1377.00,619.00));
      corners.push_back(convertPt(1376.00,622.00));
      corners.push_back(convertPt(1250.08,622.00));
      corners.push_back(convertPt(1246.00,529.00));
      corners.push_back(convertPt(1228.00,565.00));
      corners.push_back(convertPt(1204.22,622.00));
      corners.push_back(convertPt(1171.00,622.00));
      corners.push_back(convertPt(1171.00,411.00));

      contoursPointer = new Contours();
      contoursPointer->resize(corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin(), makeLine);
      _limitContours.insert(LimitContourEntry(2, contoursPointer));

      ///// 0.5pb /////
      corners.clear();
      corners.push_back(convertPt(1171.00,401.00));
      corners.push_back(convertPt(1236.00,357.00));
      corners.push_back(convertPt(1266.00,338.00));
      corners.push_back(convertPt(1287.00,330.00));
      corners.push_back(convertPt(1312.00,319.00));
      corners.push_back(convertPt(1364.00,296.00));
      corners.push_back(convertPt(1416.00,270.00));
      corners.push_back(convertPt(1490.00,231.00));
      corners.push_back(convertPt(1551.00,198.00));
      corners.push_back(convertPt(1610.00,166.00));
      corners.push_back(convertPt(1669.00,135.58));
      corners.push_back(convertPt(1731.00,103.00));
      corners.push_back(convertPt(1731.00,565.84));
      corners.push_back(convertPt(1710.00,585.00));
      corners.push_back(convertPt(1666.00,604.00));
      corners.push_back(convertPt(1640.00,605.00));
      corners.push_back(convertPt(1634.00,609.00));
      corners.push_back(convertPt(1633.00,622.00));
      corners.push_back(convertPt(1171.00,622.00));
      corners.push_back(convertPt(1171.00,401.00));

      contoursPointer = new Contours();
      contoursPointer->resize(corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin(), makeLine);
      _limitContours.insert(LimitContourEntry(3, contoursPointer));

      ///// 2pb /////
      corners.clear();
      corners.push_back(convertPt(1171.00,371.00));
      corners.push_back(convertPt(1188.00,360.00));
      corners.push_back(convertPt(1252.00,323.00));
      corners.push_back(convertPt(1289.00,307.00));
      corners.push_back(convertPt(1302.00,301.00));
      corners.push_back(convertPt(1380.00,266.00));
      corners.push_back(convertPt(1423.00,246.00));
      corners.push_back(convertPt(1462.00,226.00));
      corners.push_back(convertPt(1532.00,190.00));
      corners.push_back(convertPt(1637.00,137.00));
      corners.push_back(convertPt(1731.00,86.00));
      corners.push_back(convertPt(1731.00,622.00));
      corners.push_back(convertPt(1171.00,622.00));
      corners.push_back(convertPt(1171.00,371.00));

      contoursPointer = new Contours();
      contoursPointer->resize(corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin(), makeLine);
      _limitContours.insert(LimitContourEntry(4, contoursPointer));

    }



    P2 L3CharginoLeptonicLimitAt188pt6GeV::convertPt(double x, double y) const
    {
      return P2(45. + (x - 1172.00) / (1793.00 - 1172.00) * (100. - 45.),
                100. + (y - 853.00) / (1447.00 - 853.00) * (0. - 100.));
    }

    bool L3CharginoLeptonicLimitAt188pt6GeV::isWithinExclusionRegion(double x, double y, double mZ) const
    {
      return (y <= x and x <= 188.6 / 2. and x > mZ / 2.);
    }

    L3CharginoLeptonicLimitAt188pt6GeV::L3CharginoLeptonicLimitAt188pt6GeV()
    {
      ///// Limit values /////
      _limitValuesSorted.push_back(0.18);
      _limitValuesSorted.push_back(0.3);
      _limitValuesSorted.push_back(0.6);
      _limitValuesSorted.push_back(2.0);

      ///// Limit Contours /////
      Corners corners;
      ContoursPointer contoursPointer;

      ///// 0.18pb /////
      corners.clear();
      corners.push_back(convertPt(1405.00,1447.00));
      corners.push_back(convertPt(1416.00,1314.00));
      corners.push_back(convertPt(1402.00,1200.00));
      corners.push_back(convertPt(1403.00,1185.00));
      corners.push_back(convertPt(1428.00,1145.00));
      corners.push_back(convertPt(1435.00,1139.00));
      corners.push_back(convertPt(1468.00,1137.00));
      corners.push_back(convertPt(1475.00,1128.00));
      corners.push_back(convertPt(1481.00,1115.00));
      corners.push_back(convertPt(1496.00,1107.00));
      corners.push_back(convertPt(1554.00,1074.00));
      corners.push_back(convertPt(1563.00,1082.00));
      corners.push_back(convertPt(1627.00,1063.00));
      corners.push_back(convertPt(1640.00,1075.00));
      corners.push_back(convertPt(1647.00,1075.00));
      corners.push_back(convertPt(1649.00,1066.00));
      corners.push_back(convertPt(1679.00,1049.00));
      corners.push_back(convertPt(1712.00,1014.00));
      corners.push_back(convertPt(1716.00,1289.00));
      corners.push_back(convertPt(1732.28,1293.00));
      corners.push_back(convertPt(1732.00,1397.00));
      corners.push_back(convertPt(1726.00,1398.00));
      corners.push_back(convertPt(1721.00,1400.00));
      corners.push_back(convertPt(1719.00,1408.00));
      corners.push_back(convertPt(1713.00,1447.00));
      corners.push_back(convertPt(1405.00,1447.00));

      contoursPointer = new Contours();
      contoursPointer->resize(corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin(), makeLine);
      _limitContours.insert(LimitContourEntry(0, contoursPointer));

      ///// 0.3pb /////
      corners.clear();
      corners.push_back(convertPt(1172.00,1265.00));
      corners.push_back(convertPt(1229.00,1242.00));
      corners.push_back(convertPt(1262.00,1211.00));
      corners.push_back(convertPt(1275.00,1185.00));
      corners.push_back(convertPt(1293.00,1184.00));
      corners.push_back(convertPt(1299.00,1256.00));
      corners.push_back(convertPt(1317.00,1256.00));
      corners.push_back(convertPt(1318.00,1253.00));
      corners.push_back(convertPt(1323.00,1207.00));
      corners.push_back(convertPt(1352.00,1193.00));
      corners.push_back(convertPt(1361.00,1174.00));
      corners.push_back(convertPt(1398.00,1180.00));
      corners.push_back(convertPt(1402.00,1145.00));
      corners.push_back(convertPt(1405.00,1142.00));
      corners.push_back(convertPt(1422.00,1134.00));
      corners.push_back(convertPt(1423.00,1105.00));
      corners.push_back(convertPt(1425.00,1101.53));
      corners.push_back(convertPt(1442.00,1096.00));
      corners.push_back(convertPt(1445.00,1097.00));
      corners.push_back(convertPt(1457.00,1116.00));
      corners.push_back(convertPt(1487.00,1097.00));
      corners.push_back(convertPt(1492.00,1091.00));
      corners.push_back(convertPt(1500.00,1076.00));
      corners.push_back(convertPt(1506.00,1069.00));
      corners.push_back(convertPt(1568.00,1050.00));
      corners.push_back(convertPt(1581.00,1046.00));
      corners.push_back(convertPt(1620.00,1027.00));
      corners.push_back(convertPt(1683.00,997.00 ));
      corners.push_back(convertPt(1716.00,981.00 ));
      corners.push_back(convertPt(1715.00,1005.00));
      corners.push_back(convertPt(1732.00,999.00 ));
      corners.push_back(convertPt(1732.00,1250.00));
      corners.push_back(convertPt(1717.00,1254.00));
      corners.push_back(convertPt(1717.00,1285.00));
      corners.push_back(convertPt(1732.00,1287.00));
      corners.push_back(convertPt(1732.00,1447.00));
      corners.push_back(convertPt(1172.00,1447.00));
      corners.push_back(convertPt(1172.00,1265.00));

      contoursPointer = new Contours();
      contoursPointer->resize(corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin(), makeLine);
      _limitContours.insert(LimitContourEntry(1, contoursPointer));

      ///// 0.6pb /////
      corners.clear();
      corners.push_back(convertPt(1172.00,1244.00));
      corners.push_back(convertPt(1174.00,1238.00));
      corners.push_back(convertPt(1282.00,1173.00));
      corners.push_back(convertPt(1364.00,1125.00));
      corners.push_back(convertPt(1435.00,1086.00));
      corners.push_back(convertPt(1488.00,1059.00));
      corners.push_back(convertPt(1608.00,1000.00));
      corners.push_back(convertPt(1732.00,935.00));
      corners.push_back(convertPt(1732.00,1447.00));
      corners.push_back(convertPt(1172.00,1447.00));
      corners.push_back(convertPt(1172.00,1244.00));

      contoursPointer = new Contours();
      contoursPointer->resize(corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin(), makeLine);
      _limitContours.insert(LimitContourEntry(2, contoursPointer));

      ///// 2pb /////
      corners.clear();
      corners.push_back(convertPt(1172.00,1205.00));
      corners.push_back(convertPt(1322.00,1126.00));
      corners.push_back(convertPt(1570.00,995.00));
      corners.push_back(convertPt(1732.00,911.00));
      corners.push_back(convertPt(1732.00,1447.00));
      corners.push_back(convertPt(1172.00,1447.00));
      corners.push_back(convertPt(1172.00,1205.00));

      contoursPointer = new Contours();
      contoursPointer->resize(corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin(), makeLine);
      _limitContours.insert(LimitContourEntry(3, contoursPointer));

    }



    P2 L3NeutralinoAllChannelsLimitAt188pt6GeV::convertPt(double x, double y) const
    {
      return P2(0. + (x - 248.00) / (868.00 - 248.00) * (200. - 0.),
                100. + (y - 36.00) / (637.00 - 36.00) * (0. - 100.));
    }

    bool L3NeutralinoAllChannelsLimitAt188pt6GeV::isWithinExclusionRegion(double x, double y, double mZ) const
    {
      return (y <= x and x + y <= 188.6 and x + y > mZ);
    }

    L3NeutralinoAllChannelsLimitAt188pt6GeV::L3NeutralinoAllChannelsLimitAt188pt6GeV()
    {
      ///// Limit values /////
      _limitValuesSorted.push_back(0.1);
      _limitValuesSorted.push_back(0.2);
      _limitValuesSorted.push_back(0.3);
      _limitValuesSorted.push_back(0.5);
      _limitValuesSorted.push_back(0.7);
      _limitValuesSorted.push_back(2.0);

      ///// Limit Contours /////
      Corners corners;
      ContoursPointer contoursPointer;

      ///// 0.1pb /////
      corners.clear();
      corners.push_back(convertPt(466.00,510.00));
      corners.push_back(convertPt(436.34,453.04));
      corners.push_back(convertPt(439.00,436.00));
      corners.push_back(convertPt(458.00,395.00));
      corners.push_back(convertPt(484.00,361.00));
      corners.push_back(convertPt(493.00,333.00));
      corners.push_back(convertPt(513.00,288.00));
      corners.push_back(convertPt(531.00,281.00));
      corners.push_back(convertPt(548.00,270.00));
      corners.push_back(convertPt(548.00,257.00));
      corners.push_back(convertPt(561.14,235.02));
      corners.push_back(convertPt(579.00,213.00));
      corners.push_back(convertPt(581.20,202.79));
      corners.push_back(convertPt(585.00,191.00));
      corners.push_back(convertPt(597.00,182.00));
      corners.push_back(convertPt(666.00,314.53));
      corners.push_back(convertPt(666.00,325.00));
      corners.push_back(convertPt(635.00,351.00));
      corners.push_back(convertPt(633.00,351.00));
      corners.push_back(convertPt(611.00,374.50));
      corners.push_back(convertPt(583.00,413.00));
      corners.push_back(convertPt(580.50,444.00));
      corners.push_back(convertPt(555.00,467.00));
      corners.push_back(convertPt(542.00,495.00));
      corners.push_back(convertPt(534.00,524.00));
      corners.push_back(convertPt(504.02,521.57));
      corners.push_back(convertPt(496.00,515.00));
      corners.push_back(convertPt(495.00,493.00));
      corners.push_back(convertPt(488.00,479.00));
      corners.push_back(convertPt(481.00,494.00));
      corners.push_back(convertPt(466.00,510.00));

      contoursPointer = new Contours();
      contoursPointer->resize(corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin(), makeLine);
      _limitContours.insert(LimitContourEntry(0, contoursPointer));

      ///// 0.2pb /////
      corners.clear();
      corners.push_back(convertPt(531.00,637.00));
      corners.push_back(convertPt(419.66,420.63));
      corners.push_back(convertPt(449.00,359.00));
      corners.push_back(convertPt(463.00,339.00));
      corners.push_back(convertPt(472.00,308.00));
      corners.push_back(convertPt(504.00,250.00));
      corners.push_back(convertPt(521.00,216.00));
      corners.push_back(convertPt(549.00,192.00));
      corners.push_back(convertPt(556.00,163.00));
      corners.push_back(convertPt(573.00,136.00));
      corners.push_back(convertPt(709.00,397.00));
      corners.push_back(convertPt(706.00,399.00));
      corners.push_back(convertPt(706.00,410.00));
      corners.push_back(convertPt(694.00,432.00));
      corners.push_back(convertPt(677.00,432.00));
      corners.push_back(convertPt(656.00,460.00));
      corners.push_back(convertPt(654.00,515.00));
      corners.push_back(convertPt(636.00,531.00));
      corners.push_back(convertPt(630.00,567.00));
      corners.push_back(convertPt(630.00,602.00));
      corners.push_back(convertPt(621.39,637.00));
      corners.push_back(convertPt(531.00,637.00));

      contoursPointer = new Contours();
      contoursPointer->resize(corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin(), makeLine);
      _limitContours.insert(LimitContourEntry(1, contoursPointer));

      ///// 0.3pb /////
      corners.clear();
      corners.push_back(convertPt(531.00,637.00));
      corners.push_back(convertPt(414.20,411.00));
      corners.push_back(convertPt(422.00,383.00));
      corners.push_back(convertPt(437.00,356.00));
      corners.push_back(convertPt(449.00,338.00));
      corners.push_back(convertPt(459.00,309.00));
      corners.push_back(convertPt(500.43,237.00));
      corners.push_back(convertPt(524.00,194.00));
      corners.push_back(convertPt(532.00,180.00));
      corners.push_back(convertPt(571.72,133.90));
      corners.push_back(convertPt(782.00,537.00));
      corners.push_back(convertPt(759.00,538.00));
      corners.push_back(convertPt(743.00,483.00));
      corners.push_back(convertPt(726.00,480.00));
      corners.push_back(convertPt(719.00,510.00));
      corners.push_back(convertPt(714.00,540.00));
      corners.push_back(convertPt(694.00,634.00));
      corners.push_back(convertPt(694.00,637.00));
      corners.push_back(convertPt(531.00,637.00));

      contoursPointer = new Contours();
      contoursPointer->resize(corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin(), makeLine);
      _limitContours.insert(LimitContourEntry(2, contoursPointer));

      ///// 0.5pb /////
      corners.clear();
      corners.push_back(convertPt(531.00,637.00));
      corners.push_back(convertPt(834.00,637.00));
      corners.push_back(convertPt(563.48,119.00));
      corners.push_back(convertPt(546.00,147.00));
      corners.push_back(convertPt(542.00,156.00));
      corners.push_back(convertPt(527.02,179.19));
      corners.push_back(convertPt(511.00,208.00));
      corners.push_back(convertPt(465.00,288.00));
      corners.push_back(convertPt(435.00,339.00));
      corners.push_back(convertPt(434.00,359.00));
      corners.push_back(convertPt(417.00,385.00));
      corners.push_back(convertPt(409.00,398.00));
      corners.push_back(convertPt(531.00,637.00));

      contoursPointer = new Contours();
      contoursPointer->resize(corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin(), makeLine);
      _limitContours.insert(LimitContourEntry(3, contoursPointer));

      ///// 0.7pb /////
      corners.clear();
      corners.push_back(convertPt(402.00,386.00));
      corners.push_back(convertPt(432.66,342.00));
      corners.push_back(convertPt(435.00,313.00));
      corners.push_back(convertPt(461.00,274.00));
      corners.push_back(convertPt(473.00,247.00));
      corners.push_back(convertPt(505.00,198.00));
      corners.push_back(convertPt(541.00,141.00));
      corners.push_back(convertPt(560.00,112.00));
      corners.push_back(convertPt(833.00,637.00));
      corners.push_back(convertPt(531.00,637.00));
      corners.push_back(convertPt(402.00,386.00));

      contoursPointer = new Contours();
      contoursPointer->resize(corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin(), makeLine);
      _limitContours.insert(LimitContourEntry(4, contoursPointer));

      ///// 2pb /////
      corners.clear();
      corners.push_back(convertPt(531.00,637.00));
      corners.push_back(convertPt(392.00,368.00));
      corners.push_back(convertPt(409.00,340.00));
      corners.push_back(convertPt(445.00,270.00));
      corners.push_back(convertPt(468.00,222.00));
      corners.push_back(convertPt(503.00,163.00));
      corners.push_back(convertPt(547.00,86.00));
      corners.push_back(convertPt(834.00,637.00));
      corners.push_back(convertPt(531.00,637.00));

      contoursPointer = new Contours();
      contoursPointer->resize(corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin(), makeLine);
      _limitContours.insert(LimitContourEntry(5, contoursPointer));

    }



    P2 L3NeutralinoLeptonicLimitAt188pt6GeV::convertPt(double x, double y) const
    {
      return P2(0. + (x - 251.00) / (870.00 - 251.00) * (200. - 0.),
                100. + (y - 867.00) / (1466.00 - 867.00) * (0. - 100.));
    }

    bool L3NeutralinoLeptonicLimitAt188pt6GeV::isWithinExclusionRegion(double x, double y, double mZ) const
    {
      return (y <= x and x + y <= 188.6 and x + y > mZ);
    }

    L3NeutralinoLeptonicLimitAt188pt6GeV::L3NeutralinoLeptonicLimitAt188pt6GeV()
    {
      ///// Limit values /////
      _limitValuesSorted.push_back(0.18);
      _limitValuesSorted.push_back(0.3);
      _limitValuesSorted.push_back(0.6);
      _limitValuesSorted.push_back(2.0);

      ///// Limit Contours /////
      Corners corners;
      ContoursPointer contoursPointer;

      ///// 0.18pb /////
      corners.clear();
      corners.push_back(convertPt(526.31,1451.00));
      corners.push_back(convertPt(413.77,1232.00));
      corners.push_back(convertPt(425.56,1208.64));
      corners.push_back(convertPt(450.00,1157.00));
      corners.push_back(convertPt(458.00,1141.00));
      corners.push_back(convertPt(503.00,1084.00));
      corners.push_back(convertPt(516.00,1067.00));
      corners.push_back(convertPt(551.00,1048.00));
      corners.push_back(convertPt(564.00,952.00));
      corners.push_back(convertPt(567.13,946.73));
      corners.push_back(convertPt(680.75,1165.93));
      corners.push_back(convertPt(674.00,1173.00));
      corners.push_back(convertPt(657.00,1216.00));
      corners.push_back(convertPt(652.39,1262.00));
      corners.push_back(convertPt(650.00,1263.00));
      corners.push_back(convertPt(639.00,1261.00));
      corners.push_back(convertPt(618.00,1266.00));
      corners.push_back(convertPt(609.00,1282.00));
      corners.push_back(convertPt(594.00,1312.00));
      corners.push_back(convertPt(592.00,1321.00));
      corners.push_back(convertPt(600.00,1330.00));
      corners.push_back(convertPt(580.00,1357.00));
      corners.push_back(convertPt(582.00,1373.00));
      corners.push_back(convertPt(526.31,1451.00));

      contoursPointer = new Contours();
      contoursPointer->resize(corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin(), makeLine);
      _limitContours.insert(LimitContourEntry(0, contoursPointer));

      ///// 0.3pb /////
      corners.clear();
      corners.push_back(convertPt(534.00,1466.00));
      corners.push_back(convertPt(400.57,1208.00));
      corners.push_back(convertPt(412.00,1188.00));
      corners.push_back(convertPt(481.00,1071.00));
      corners.push_back(convertPt(522.00,995.57));
      corners.push_back(convertPt(561.85,936.56));
      corners.push_back(convertPt(785.07,1367.19));
      corners.push_back(convertPt(757.00,1466.00));
      corners.push_back(convertPt(534.00,1466.00));

      contoursPointer = new Contours();
      contoursPointer->resize(corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin(), makeLine);
      _limitContours.insert(LimitContourEntry(1, contoursPointer));

      ///// 0.6pb /////
      corners.clear();
      corners.push_back(convertPt(534.00,1466.00));
      corners.push_back(convertPt(394.62,1197.00));
      corners.push_back(convertPt(461.00,1079.00));
      corners.push_back(convertPt(518.00,976.00));
      corners.push_back(convertPt(550.68,915.01));
      corners.push_back(convertPt(828.00,1450.00));
      corners.push_back(convertPt(819.95,1466.00));
      corners.push_back(convertPt(534.00,1466.00));

      contoursPointer = new Contours();
      contoursPointer->resize(corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin(), makeLine);
      _limitContours.insert(LimitContourEntry(2, contoursPointer));

      ///// 2pb /////
      corners.clear();
      corners.push_back(convertPt(534.00,1466.00));
      corners.push_back(convertPt(393.89,1196.64));
      corners.push_back(convertPt(452.00,1086.00));
      corners.push_back(convertPt(482.00,1029.00));
      corners.push_back(convertPt(546.00,906.00));
      corners.push_back(convertPt(837.00,1466.00));
      corners.push_back(convertPt(534.00,1466.00));

      contoursPointer = new Contours();
      contoursPointer->resize(corners.size() - 1);
      std::transform(corners.begin(), --corners.end(), ++corners.begin(),
                     contoursPointer->begin(), makeLine);
      _limitContours.insert(LimitContourEntry(3, contoursPointer));

    }

  }
}
