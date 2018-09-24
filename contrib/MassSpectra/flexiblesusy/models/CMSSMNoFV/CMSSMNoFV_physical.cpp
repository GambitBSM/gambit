// ====================================================================
// This file is part of FlexibleSUSY.
//
// FlexibleSUSY is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
//
// FlexibleSUSY is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with FlexibleSUSY.  If not, see
// <http://www.gnu.org/licenses/>.
// ====================================================================

// File generated at Thu 10 May 2018 14:55:59

#include "CMSSMNoFV_physical.hpp"
#include "slha_io.hpp"

#include <iostream>

#define LOCALPHYSICAL(p) p

namespace flexiblesusy {

void CMSSMNoFV_physical::clear()
{
   MVG = 0.;
   MGlu = 0.;
   MFd = 0.;
   MFs = 0.;
   MFb = 0.;
   MFu = 0.;
   MFc = 0.;
   MFt = 0.;
   MFve = 0.;
   MFvm = 0.;
   MFvt = 0.;
   MFe = 0.;
   MFm = 0.;
   MFtau = 0.;
   MSveL = 0.;
   MSvmL = 0.;
   MSvtL = 0.;
   MSd = Eigen::Matrix<double,2,1>::Zero();
   ZD = Eigen::Matrix<double,2,2>::Zero();
   MSu = Eigen::Matrix<double,2,1>::Zero();
   ZU = Eigen::Matrix<double,2,2>::Zero();
   MSe = Eigen::Matrix<double,2,1>::Zero();
   ZE = Eigen::Matrix<double,2,2>::Zero();
   MSm = Eigen::Matrix<double,2,1>::Zero();
   ZM = Eigen::Matrix<double,2,2>::Zero();
   MStau = Eigen::Matrix<double,2,1>::Zero();
   ZTau = Eigen::Matrix<double,2,2>::Zero();
   MSs = Eigen::Matrix<double,2,1>::Zero();
   ZS = Eigen::Matrix<double,2,2>::Zero();
   MSc = Eigen::Matrix<double,2,1>::Zero();
   ZC = Eigen::Matrix<double,2,2>::Zero();
   MSb = Eigen::Matrix<double,2,1>::Zero();
   ZB = Eigen::Matrix<double,2,2>::Zero();
   MSt = Eigen::Matrix<double,2,1>::Zero();
   ZT = Eigen::Matrix<double,2,2>::Zero();
   Mhh = Eigen::Matrix<double,2,1>::Zero();
   ZH = Eigen::Matrix<double,2,2>::Zero();
   MAh = Eigen::Matrix<double,2,1>::Zero();
   ZA = Eigen::Matrix<double,2,2>::Zero();
   MHpm = Eigen::Matrix<double,2,1>::Zero();
   ZP = Eigen::Matrix<double,2,2>::Zero();
   MChi = Eigen::Matrix<double,4,1>::Zero();
   ZN = Eigen::Matrix<std::complex<double>,4,4>::Zero();
   MCha = Eigen::Matrix<double,2,1>::Zero();
   UM = Eigen::Matrix<std::complex<double>,2,2>::Zero();
   UP = Eigen::Matrix<std::complex<double>,2,2>::Zero();
   MVWm = 0.;
   MVP = 0.;
   MVZ = 0.;

}

/**
 * Convert masses and mixing matrices to Haber-Kane convention:
 * Fermion masses are always positive and mixing matrices are allowed
 * to be complex.
 */
void CMSSMNoFV_physical::convert_to_hk()
{
   SLHA_io::convert_symmetric_fermion_mixings_to_hk(LOCALPHYSICAL(MChi), LOCALPHYSICAL(ZN));

}

/**
 * Convert masses and mixing matrices to SLHA convention: Fermion
 * mixing matrices are always real and fermion masses are allowed to
 * be negative.
 */
void CMSSMNoFV_physical::convert_to_slha()
{
   SLHA_io::convert_symmetric_fermion_mixings_to_slha(LOCALPHYSICAL(MChi), LOCALPHYSICAL(ZN));

}

Eigen::ArrayXd CMSSMNoFV_physical::get() const
{
   Eigen::ArrayXd pars(get_masses());

   pars.conservativeResize(150);

   pars(50) = ZD(0,0);
   pars(51) = ZD(0,1);
   pars(52) = ZD(1,0);
   pars(53) = ZD(1,1);
   pars(54) = ZU(0,0);
   pars(55) = ZU(0,1);
   pars(56) = ZU(1,0);
   pars(57) = ZU(1,1);
   pars(58) = ZE(0,0);
   pars(59) = ZE(0,1);
   pars(60) = ZE(1,0);
   pars(61) = ZE(1,1);
   pars(62) = ZM(0,0);
   pars(63) = ZM(0,1);
   pars(64) = ZM(1,0);
   pars(65) = ZM(1,1);
   pars(66) = ZTau(0,0);
   pars(67) = ZTau(0,1);
   pars(68) = ZTau(1,0);
   pars(69) = ZTau(1,1);
   pars(70) = ZS(0,0);
   pars(71) = ZS(0,1);
   pars(72) = ZS(1,0);
   pars(73) = ZS(1,1);
   pars(74) = ZC(0,0);
   pars(75) = ZC(0,1);
   pars(76) = ZC(1,0);
   pars(77) = ZC(1,1);
   pars(78) = ZB(0,0);
   pars(79) = ZB(0,1);
   pars(80) = ZB(1,0);
   pars(81) = ZB(1,1);
   pars(82) = ZT(0,0);
   pars(83) = ZT(0,1);
   pars(84) = ZT(1,0);
   pars(85) = ZT(1,1);
   pars(86) = ZH(0,0);
   pars(87) = ZH(0,1);
   pars(88) = ZH(1,0);
   pars(89) = ZH(1,1);
   pars(90) = ZA(0,0);
   pars(91) = ZA(0,1);
   pars(92) = ZA(1,0);
   pars(93) = ZA(1,1);
   pars(94) = ZP(0,0);
   pars(95) = ZP(0,1);
   pars(96) = ZP(1,0);
   pars(97) = ZP(1,1);
   pars(98) = Re(ZN(0,0));
   pars(99) = Im(ZN(0,0));
   pars(100) = Re(ZN(0,1));
   pars(101) = Im(ZN(0,1));
   pars(102) = Re(ZN(0,2));
   pars(103) = Im(ZN(0,2));
   pars(104) = Re(ZN(0,3));
   pars(105) = Im(ZN(0,3));
   pars(106) = Re(ZN(1,0));
   pars(107) = Im(ZN(1,0));
   pars(108) = Re(ZN(1,1));
   pars(109) = Im(ZN(1,1));
   pars(110) = Re(ZN(1,2));
   pars(111) = Im(ZN(1,2));
   pars(112) = Re(ZN(1,3));
   pars(113) = Im(ZN(1,3));
   pars(114) = Re(ZN(2,0));
   pars(115) = Im(ZN(2,0));
   pars(116) = Re(ZN(2,1));
   pars(117) = Im(ZN(2,1));
   pars(118) = Re(ZN(2,2));
   pars(119) = Im(ZN(2,2));
   pars(120) = Re(ZN(2,3));
   pars(121) = Im(ZN(2,3));
   pars(122) = Re(ZN(3,0));
   pars(123) = Im(ZN(3,0));
   pars(124) = Re(ZN(3,1));
   pars(125) = Im(ZN(3,1));
   pars(126) = Re(ZN(3,2));
   pars(127) = Im(ZN(3,2));
   pars(128) = Re(ZN(3,3));
   pars(129) = Im(ZN(3,3));
   pars(130) = Re(UM(0,0));
   pars(131) = Im(UM(0,0));
   pars(132) = Re(UM(0,1));
   pars(133) = Im(UM(0,1));
   pars(134) = Re(UM(1,0));
   pars(135) = Im(UM(1,0));
   pars(136) = Re(UM(1,1));
   pars(137) = Im(UM(1,1));
   pars(138) = Re(UP(0,0));
   pars(139) = Im(UP(0,0));
   pars(140) = Re(UP(0,1));
   pars(141) = Im(UP(0,1));
   pars(142) = Re(UP(1,0));
   pars(143) = Im(UP(1,0));
   pars(144) = Re(UP(1,1));
   pars(145) = Im(UP(1,1));
   pars(146) = ZZ(0,0);
   pars(147) = ZZ(0,1);
   pars(148) = ZZ(1,0);
   pars(149) = ZZ(1,1);


   return pars;
}

void CMSSMNoFV_physical::set(const Eigen::ArrayXd& pars)
{
   set_masses(pars);

   ZD(0,0) = pars(50);
   ZD(0,1) = pars(51);
   ZD(1,0) = pars(52);
   ZD(1,1) = pars(53);
   ZU(0,0) = pars(54);
   ZU(0,1) = pars(55);
   ZU(1,0) = pars(56);
   ZU(1,1) = pars(57);
   ZE(0,0) = pars(58);
   ZE(0,1) = pars(59);
   ZE(1,0) = pars(60);
   ZE(1,1) = pars(61);
   ZM(0,0) = pars(62);
   ZM(0,1) = pars(63);
   ZM(1,0) = pars(64);
   ZM(1,1) = pars(65);
   ZTau(0,0) = pars(66);
   ZTau(0,1) = pars(67);
   ZTau(1,0) = pars(68);
   ZTau(1,1) = pars(69);
   ZS(0,0) = pars(70);
   ZS(0,1) = pars(71);
   ZS(1,0) = pars(72);
   ZS(1,1) = pars(73);
   ZC(0,0) = pars(74);
   ZC(0,1) = pars(75);
   ZC(1,0) = pars(76);
   ZC(1,1) = pars(77);
   ZB(0,0) = pars(78);
   ZB(0,1) = pars(79);
   ZB(1,0) = pars(80);
   ZB(1,1) = pars(81);
   ZT(0,0) = pars(82);
   ZT(0,1) = pars(83);
   ZT(1,0) = pars(84);
   ZT(1,1) = pars(85);
   ZH(0,0) = pars(86);
   ZH(0,1) = pars(87);
   ZH(1,0) = pars(88);
   ZH(1,1) = pars(89);
   ZA(0,0) = pars(90);
   ZA(0,1) = pars(91);
   ZA(1,0) = pars(92);
   ZA(1,1) = pars(93);
   ZP(0,0) = pars(94);
   ZP(0,1) = pars(95);
   ZP(1,0) = pars(96);
   ZP(1,1) = pars(97);
   ZN(0,0) = std::complex<double>(pars(98), pars(99));
   ZN(0,1) = std::complex<double>(pars(100), pars(101));
   ZN(0,2) = std::complex<double>(pars(102), pars(103));
   ZN(0,3) = std::complex<double>(pars(104), pars(105));
   ZN(1,0) = std::complex<double>(pars(106), pars(107));
   ZN(1,1) = std::complex<double>(pars(108), pars(109));
   ZN(1,2) = std::complex<double>(pars(110), pars(111));
   ZN(1,3) = std::complex<double>(pars(112), pars(113));
   ZN(2,0) = std::complex<double>(pars(114), pars(115));
   ZN(2,1) = std::complex<double>(pars(116), pars(117));
   ZN(2,2) = std::complex<double>(pars(118), pars(119));
   ZN(2,3) = std::complex<double>(pars(120), pars(121));
   ZN(3,0) = std::complex<double>(pars(122), pars(123));
   ZN(3,1) = std::complex<double>(pars(124), pars(125));
   ZN(3,2) = std::complex<double>(pars(126), pars(127));
   ZN(3,3) = std::complex<double>(pars(128), pars(129));
   UM(0,0) = std::complex<double>(pars(130), pars(131));
   UM(0,1) = std::complex<double>(pars(132), pars(133));
   UM(1,0) = std::complex<double>(pars(134), pars(135));
   UM(1,1) = std::complex<double>(pars(136), pars(137));
   UP(0,0) = std::complex<double>(pars(138), pars(139));
   UP(0,1) = std::complex<double>(pars(140), pars(141));
   UP(1,0) = std::complex<double>(pars(142), pars(143));
   UP(1,1) = std::complex<double>(pars(144), pars(145));
   ZZ(0,0) = pars(146);
   ZZ(0,1) = pars(147);
   ZZ(1,0) = pars(148);
   ZZ(1,1) = pars(149);

}

Eigen::ArrayXd CMSSMNoFV_physical::get_masses() const
{
   Eigen::ArrayXd pars(50);

   pars(0) = MVG;
   pars(1) = MGlu;
   pars(2) = MFd;
   pars(3) = MFs;
   pars(4) = MFb;
   pars(5) = MFu;
   pars(6) = MFc;
   pars(7) = MFt;
   pars(8) = MFve;
   pars(9) = MFvm;
   pars(10) = MFvt;
   pars(11) = MFe;
   pars(12) = MFm;
   pars(13) = MFtau;
   pars(14) = MSveL;
   pars(15) = MSvmL;
   pars(16) = MSvtL;
   pars(17) = MSd(0);
   pars(18) = MSd(1);
   pars(19) = MSu(0);
   pars(20) = MSu(1);
   pars(21) = MSe(0);
   pars(22) = MSe(1);
   pars(23) = MSm(0);
   pars(24) = MSm(1);
   pars(25) = MStau(0);
   pars(26) = MStau(1);
   pars(27) = MSs(0);
   pars(28) = MSs(1);
   pars(29) = MSc(0);
   pars(30) = MSc(1);
   pars(31) = MSb(0);
   pars(32) = MSb(1);
   pars(33) = MSt(0);
   pars(34) = MSt(1);
   pars(35) = Mhh(0);
   pars(36) = Mhh(1);
   pars(37) = MAh(0);
   pars(38) = MAh(1);
   pars(39) = MHpm(0);
   pars(40) = MHpm(1);
   pars(41) = MChi(0);
   pars(42) = MChi(1);
   pars(43) = MChi(2);
   pars(44) = MChi(3);
   pars(45) = MCha(0);
   pars(46) = MCha(1);
   pars(47) = MVWm;
   pars(48) = MVP;
   pars(49) = MVZ;

   return pars;
}

void CMSSMNoFV_physical::set_masses(const Eigen::ArrayXd& pars)
{
   MVG = pars(0);
   MGlu = pars(1);
   MFd = pars(2);
   MFs = pars(3);
   MFb = pars(4);
   MFu = pars(5);
   MFc = pars(6);
   MFt = pars(7);
   MFve = pars(8);
   MFvm = pars(9);
   MFvt = pars(10);
   MFe = pars(11);
   MFm = pars(12);
   MFtau = pars(13);
   MSveL = pars(14);
   MSvmL = pars(15);
   MSvtL = pars(16);
   MSd(0) = pars(17);
   MSd(1) = pars(18);
   MSu(0) = pars(19);
   MSu(1) = pars(20);
   MSe(0) = pars(21);
   MSe(1) = pars(22);
   MSm(0) = pars(23);
   MSm(1) = pars(24);
   MStau(0) = pars(25);
   MStau(1) = pars(26);
   MSs(0) = pars(27);
   MSs(1) = pars(28);
   MSc(0) = pars(29);
   MSc(1) = pars(30);
   MSb(0) = pars(31);
   MSb(1) = pars(32);
   MSt(0) = pars(33);
   MSt(1) = pars(34);
   Mhh(0) = pars(35);
   Mhh(1) = pars(36);
   MAh(0) = pars(37);
   MAh(1) = pars(38);
   MHpm(0) = pars(39);
   MHpm(1) = pars(40);
   MChi(0) = pars(41);
   MChi(1) = pars(42);
   MChi(2) = pars(43);
   MChi(3) = pars(44);
   MCha(0) = pars(45);
   MCha(1) = pars(46);
   MVWm = pars(47);
   MVP = pars(48);
   MVZ = pars(49);

}

void CMSSMNoFV_physical::print(std::ostream& ostr) const
{
   ostr << "----------------------------------------\n"
           "pole masses:\n"
           "----------------------------------------\n";
   ostr << "MVG = " << MVG << '\n';
   ostr << "MGlu = " << MGlu << '\n';
   ostr << "MFd = " << MFd << '\n';
   ostr << "MFs = " << MFs << '\n';
   ostr << "MFb = " << MFb << '\n';
   ostr << "MFu = " << MFu << '\n';
   ostr << "MFc = " << MFc << '\n';
   ostr << "MFt = " << MFt << '\n';
   ostr << "MFve = " << MFve << '\n';
   ostr << "MFvm = " << MFvm << '\n';
   ostr << "MFvt = " << MFvt << '\n';
   ostr << "MFe = " << MFe << '\n';
   ostr << "MFm = " << MFm << '\n';
   ostr << "MFtau = " << MFtau << '\n';
   ostr << "MSveL = " << MSveL << '\n';
   ostr << "MSvmL = " << MSvmL << '\n';
   ostr << "MSvtL = " << MSvtL << '\n';
   ostr << "MSd = " << MSd.transpose() << '\n';
   ostr << "MSu = " << MSu.transpose() << '\n';
   ostr << "MSe = " << MSe.transpose() << '\n';
   ostr << "MSm = " << MSm.transpose() << '\n';
   ostr << "MStau = " << MStau.transpose() << '\n';
   ostr << "MSs = " << MSs.transpose() << '\n';
   ostr << "MSc = " << MSc.transpose() << '\n';
   ostr << "MSb = " << MSb.transpose() << '\n';
   ostr << "MSt = " << MSt.transpose() << '\n';
   ostr << "Mhh = " << Mhh.transpose() << '\n';
   ostr << "MAh = " << MAh.transpose() << '\n';
   ostr << "MHpm = " << MHpm.transpose() << '\n';
   ostr << "MChi = " << MChi.transpose() << '\n';
   ostr << "MCha = " << MCha.transpose() << '\n';
   ostr << "MVWm = " << MVWm << '\n';
   ostr << "MVP = " << MVP << '\n';
   ostr << "MVZ = " << MVZ << '\n';

   ostr << "----------------------------------------\n"
           "pole mass mixing matrices:\n"
           "----------------------------------------\n";
   ostr << "ZD = " << ZD << '\n';
   ostr << "ZU = " << ZU << '\n';
   ostr << "ZE = " << ZE << '\n';
   ostr << "ZM = " << ZM << '\n';
   ostr << "ZTau = " << ZTau << '\n';
   ostr << "ZS = " << ZS << '\n';
   ostr << "ZC = " << ZC << '\n';
   ostr << "ZB = " << ZB << '\n';
   ostr << "ZT = " << ZT << '\n';
   ostr << "ZH = " << ZH << '\n';
   ostr << "ZA = " << ZA << '\n';
   ostr << "ZP = " << ZP << '\n';
   ostr << "ZN = " << ZN << '\n';
   ostr << "UM = " << UM << '\n';
   ostr << "UP = " << UP << '\n';
   ostr << "ZZ = " << ZZ << '\n';

}

std::ostream& operator<<(std::ostream& ostr, const CMSSMNoFV_physical& phys_pars)
{
   phys_pars.print(ostr);
   return ostr;
}

} // namespace flexiblesusy
