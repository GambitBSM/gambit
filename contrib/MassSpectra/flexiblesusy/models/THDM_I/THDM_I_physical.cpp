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

// File generated at Tue 7 Apr 2020 02:33:58

#include "THDM_I_physical.hpp"
#include "slha_io.hpp"

#include <iostream>

#define LOCALPHYSICAL(p) p

namespace flexiblesusy {

void THDM_I_physical::clear()
{
   MVG = 0.;
   MFv = Eigen::Matrix<double,3,1>::Zero();
   Mhh = Eigen::Matrix<double,2,1>::Zero();
   ZH = Eigen::Matrix<double,2,2>::Zero();
   MAh = Eigen::Matrix<double,2,1>::Zero();
   ZA = Eigen::Matrix<double,2,2>::Zero();
   MHm = Eigen::Matrix<double,2,1>::Zero();
   ZP = Eigen::Matrix<double,2,2>::Zero();
   MFd = Eigen::Matrix<double,3,1>::Zero();
   Vd = Eigen::Matrix<std::complex<double>,3,3>::Zero();
   Ud = Eigen::Matrix<std::complex<double>,3,3>::Zero();
   MFu = Eigen::Matrix<double,3,1>::Zero();
   Vu = Eigen::Matrix<std::complex<double>,3,3>::Zero();
   Uu = Eigen::Matrix<std::complex<double>,3,3>::Zero();
   MFe = Eigen::Matrix<double,3,1>::Zero();
   Ve = Eigen::Matrix<std::complex<double>,3,3>::Zero();
   Ue = Eigen::Matrix<std::complex<double>,3,3>::Zero();
   MVWm = 0.;
   MVP = 0.;
   MVZ = 0.;

}

/**
 * Convert masses and mixing matrices to Haber-Kane convention:
 * Fermion masses are always positive and mixing matrices are allowed
 * to be complex.
 */
void THDM_I_physical::convert_to_hk()
{

}

/**
 * Convert masses and mixing matrices to SLHA convention: Fermion
 * mixing matrices are always real and fermion masses are allowed to
 * be negative.
 */
void THDM_I_physical::convert_to_slha()
{

}

Eigen::ArrayXd THDM_I_physical::get() const
{
   Eigen::ArrayXd pars(get_masses());

   pars.conservativeResize(146);

   pars(22) = ZH(0,0);
   pars(23) = ZH(0,1);
   pars(24) = ZH(1,0);
   pars(25) = ZH(1,1);
   pars(26) = ZA(0,0);
   pars(27) = ZA(0,1);
   pars(28) = ZA(1,0);
   pars(29) = ZA(1,1);
   pars(30) = ZP(0,0);
   pars(31) = ZP(0,1);
   pars(32) = ZP(1,0);
   pars(33) = ZP(1,1);
   pars(34) = Re(Vd(0,0));
   pars(35) = Im(Vd(0,0));
   pars(36) = Re(Vd(0,1));
   pars(37) = Im(Vd(0,1));
   pars(38) = Re(Vd(0,2));
   pars(39) = Im(Vd(0,2));
   pars(40) = Re(Vd(1,0));
   pars(41) = Im(Vd(1,0));
   pars(42) = Re(Vd(1,1));
   pars(43) = Im(Vd(1,1));
   pars(44) = Re(Vd(1,2));
   pars(45) = Im(Vd(1,2));
   pars(46) = Re(Vd(2,0));
   pars(47) = Im(Vd(2,0));
   pars(48) = Re(Vd(2,1));
   pars(49) = Im(Vd(2,1));
   pars(50) = Re(Vd(2,2));
   pars(51) = Im(Vd(2,2));
   pars(52) = Re(Ud(0,0));
   pars(53) = Im(Ud(0,0));
   pars(54) = Re(Ud(0,1));
   pars(55) = Im(Ud(0,1));
   pars(56) = Re(Ud(0,2));
   pars(57) = Im(Ud(0,2));
   pars(58) = Re(Ud(1,0));
   pars(59) = Im(Ud(1,0));
   pars(60) = Re(Ud(1,1));
   pars(61) = Im(Ud(1,1));
   pars(62) = Re(Ud(1,2));
   pars(63) = Im(Ud(1,2));
   pars(64) = Re(Ud(2,0));
   pars(65) = Im(Ud(2,0));
   pars(66) = Re(Ud(2,1));
   pars(67) = Im(Ud(2,1));
   pars(68) = Re(Ud(2,2));
   pars(69) = Im(Ud(2,2));
   pars(70) = Re(Vu(0,0));
   pars(71) = Im(Vu(0,0));
   pars(72) = Re(Vu(0,1));
   pars(73) = Im(Vu(0,1));
   pars(74) = Re(Vu(0,2));
   pars(75) = Im(Vu(0,2));
   pars(76) = Re(Vu(1,0));
   pars(77) = Im(Vu(1,0));
   pars(78) = Re(Vu(1,1));
   pars(79) = Im(Vu(1,1));
   pars(80) = Re(Vu(1,2));
   pars(81) = Im(Vu(1,2));
   pars(82) = Re(Vu(2,0));
   pars(83) = Im(Vu(2,0));
   pars(84) = Re(Vu(2,1));
   pars(85) = Im(Vu(2,1));
   pars(86) = Re(Vu(2,2));
   pars(87) = Im(Vu(2,2));
   pars(88) = Re(Uu(0,0));
   pars(89) = Im(Uu(0,0));
   pars(90) = Re(Uu(0,1));
   pars(91) = Im(Uu(0,1));
   pars(92) = Re(Uu(0,2));
   pars(93) = Im(Uu(0,2));
   pars(94) = Re(Uu(1,0));
   pars(95) = Im(Uu(1,0));
   pars(96) = Re(Uu(1,1));
   pars(97) = Im(Uu(1,1));
   pars(98) = Re(Uu(1,2));
   pars(99) = Im(Uu(1,2));
   pars(100) = Re(Uu(2,0));
   pars(101) = Im(Uu(2,0));
   pars(102) = Re(Uu(2,1));
   pars(103) = Im(Uu(2,1));
   pars(104) = Re(Uu(2,2));
   pars(105) = Im(Uu(2,2));
   pars(106) = Re(Ve(0,0));
   pars(107) = Im(Ve(0,0));
   pars(108) = Re(Ve(0,1));
   pars(109) = Im(Ve(0,1));
   pars(110) = Re(Ve(0,2));
   pars(111) = Im(Ve(0,2));
   pars(112) = Re(Ve(1,0));
   pars(113) = Im(Ve(1,0));
   pars(114) = Re(Ve(1,1));
   pars(115) = Im(Ve(1,1));
   pars(116) = Re(Ve(1,2));
   pars(117) = Im(Ve(1,2));
   pars(118) = Re(Ve(2,0));
   pars(119) = Im(Ve(2,0));
   pars(120) = Re(Ve(2,1));
   pars(121) = Im(Ve(2,1));
   pars(122) = Re(Ve(2,2));
   pars(123) = Im(Ve(2,2));
   pars(124) = Re(Ue(0,0));
   pars(125) = Im(Ue(0,0));
   pars(126) = Re(Ue(0,1));
   pars(127) = Im(Ue(0,1));
   pars(128) = Re(Ue(0,2));
   pars(129) = Im(Ue(0,2));
   pars(130) = Re(Ue(1,0));
   pars(131) = Im(Ue(1,0));
   pars(132) = Re(Ue(1,1));
   pars(133) = Im(Ue(1,1));
   pars(134) = Re(Ue(1,2));
   pars(135) = Im(Ue(1,2));
   pars(136) = Re(Ue(2,0));
   pars(137) = Im(Ue(2,0));
   pars(138) = Re(Ue(2,1));
   pars(139) = Im(Ue(2,1));
   pars(140) = Re(Ue(2,2));
   pars(141) = Im(Ue(2,2));
   pars(142) = ZZ(0,0);
   pars(143) = ZZ(0,1);
   pars(144) = ZZ(1,0);
   pars(145) = ZZ(1,1);


   return pars;
}

void THDM_I_physical::set(const Eigen::ArrayXd& pars)
{
   set_masses(pars);

   ZH(0,0) = pars(22);
   ZH(0,1) = pars(23);
   ZH(1,0) = pars(24);
   ZH(1,1) = pars(25);
   ZA(0,0) = pars(26);
   ZA(0,1) = pars(27);
   ZA(1,0) = pars(28);
   ZA(1,1) = pars(29);
   ZP(0,0) = pars(30);
   ZP(0,1) = pars(31);
   ZP(1,0) = pars(32);
   ZP(1,1) = pars(33);
   Vd(0,0) = std::complex<double>(pars(34), pars(35));
   Vd(0,1) = std::complex<double>(pars(36), pars(37));
   Vd(0,2) = std::complex<double>(pars(38), pars(39));
   Vd(1,0) = std::complex<double>(pars(40), pars(41));
   Vd(1,1) = std::complex<double>(pars(42), pars(43));
   Vd(1,2) = std::complex<double>(pars(44), pars(45));
   Vd(2,0) = std::complex<double>(pars(46), pars(47));
   Vd(2,1) = std::complex<double>(pars(48), pars(49));
   Vd(2,2) = std::complex<double>(pars(50), pars(51));
   Ud(0,0) = std::complex<double>(pars(52), pars(53));
   Ud(0,1) = std::complex<double>(pars(54), pars(55));
   Ud(0,2) = std::complex<double>(pars(56), pars(57));
   Ud(1,0) = std::complex<double>(pars(58), pars(59));
   Ud(1,1) = std::complex<double>(pars(60), pars(61));
   Ud(1,2) = std::complex<double>(pars(62), pars(63));
   Ud(2,0) = std::complex<double>(pars(64), pars(65));
   Ud(2,1) = std::complex<double>(pars(66), pars(67));
   Ud(2,2) = std::complex<double>(pars(68), pars(69));
   Vu(0,0) = std::complex<double>(pars(70), pars(71));
   Vu(0,1) = std::complex<double>(pars(72), pars(73));
   Vu(0,2) = std::complex<double>(pars(74), pars(75));
   Vu(1,0) = std::complex<double>(pars(76), pars(77));
   Vu(1,1) = std::complex<double>(pars(78), pars(79));
   Vu(1,2) = std::complex<double>(pars(80), pars(81));
   Vu(2,0) = std::complex<double>(pars(82), pars(83));
   Vu(2,1) = std::complex<double>(pars(84), pars(85));
   Vu(2,2) = std::complex<double>(pars(86), pars(87));
   Uu(0,0) = std::complex<double>(pars(88), pars(89));
   Uu(0,1) = std::complex<double>(pars(90), pars(91));
   Uu(0,2) = std::complex<double>(pars(92), pars(93));
   Uu(1,0) = std::complex<double>(pars(94), pars(95));
   Uu(1,1) = std::complex<double>(pars(96), pars(97));
   Uu(1,2) = std::complex<double>(pars(98), pars(99));
   Uu(2,0) = std::complex<double>(pars(100), pars(101));
   Uu(2,1) = std::complex<double>(pars(102), pars(103));
   Uu(2,2) = std::complex<double>(pars(104), pars(105));
   Ve(0,0) = std::complex<double>(pars(106), pars(107));
   Ve(0,1) = std::complex<double>(pars(108), pars(109));
   Ve(0,2) = std::complex<double>(pars(110), pars(111));
   Ve(1,0) = std::complex<double>(pars(112), pars(113));
   Ve(1,1) = std::complex<double>(pars(114), pars(115));
   Ve(1,2) = std::complex<double>(pars(116), pars(117));
   Ve(2,0) = std::complex<double>(pars(118), pars(119));
   Ve(2,1) = std::complex<double>(pars(120), pars(121));
   Ve(2,2) = std::complex<double>(pars(122), pars(123));
   Ue(0,0) = std::complex<double>(pars(124), pars(125));
   Ue(0,1) = std::complex<double>(pars(126), pars(127));
   Ue(0,2) = std::complex<double>(pars(128), pars(129));
   Ue(1,0) = std::complex<double>(pars(130), pars(131));
   Ue(1,1) = std::complex<double>(pars(132), pars(133));
   Ue(1,2) = std::complex<double>(pars(134), pars(135));
   Ue(2,0) = std::complex<double>(pars(136), pars(137));
   Ue(2,1) = std::complex<double>(pars(138), pars(139));
   Ue(2,2) = std::complex<double>(pars(140), pars(141));
   ZZ(0,0) = pars(142);
   ZZ(0,1) = pars(143);
   ZZ(1,0) = pars(144);
   ZZ(1,1) = pars(145);

}

Eigen::ArrayXd THDM_I_physical::get_masses() const
{
   Eigen::ArrayXd pars(22);

   pars(0) = MVG;
   pars(1) = MFv(0);
   pars(2) = MFv(1);
   pars(3) = MFv(2);
   pars(4) = Mhh(0);
   pars(5) = Mhh(1);
   pars(6) = MAh(0);
   pars(7) = MAh(1);
   pars(8) = MHm(0);
   pars(9) = MHm(1);
   pars(10) = MFd(0);
   pars(11) = MFd(1);
   pars(12) = MFd(2);
   pars(13) = MFu(0);
   pars(14) = MFu(1);
   pars(15) = MFu(2);
   pars(16) = MFe(0);
   pars(17) = MFe(1);
   pars(18) = MFe(2);
   pars(19) = MVWm;
   pars(20) = MVP;
   pars(21) = MVZ;

   return pars;
}

void THDM_I_physical::set_masses(const Eigen::ArrayXd& pars)
{
   MVG = pars(0);
   MFv(0) = pars(1);
   MFv(1) = pars(2);
   MFv(2) = pars(3);
   Mhh(0) = pars(4);
   Mhh(1) = pars(5);
   MAh(0) = pars(6);
   MAh(1) = pars(7);
   MHm(0) = pars(8);
   MHm(1) = pars(9);
   MFd(0) = pars(10);
   MFd(1) = pars(11);
   MFd(2) = pars(12);
   MFu(0) = pars(13);
   MFu(1) = pars(14);
   MFu(2) = pars(15);
   MFe(0) = pars(16);
   MFe(1) = pars(17);
   MFe(2) = pars(18);
   MVWm = pars(19);
   MVP = pars(20);
   MVZ = pars(21);

}

void THDM_I_physical::print(std::ostream& ostr) const
{
   ostr << "----------------------------------------\n"
           "pole masses:\n"
           "----------------------------------------\n";
   ostr << "MVG = " << MVG << '\n';
   ostr << "MFv = " << MFv.transpose() << '\n';
   ostr << "Mhh = " << Mhh.transpose() << '\n';
   ostr << "MAh = " << MAh.transpose() << '\n';
   ostr << "MHm = " << MHm.transpose() << '\n';
   ostr << "MFd = " << MFd.transpose() << '\n';
   ostr << "MFu = " << MFu.transpose() << '\n';
   ostr << "MFe = " << MFe.transpose() << '\n';
   ostr << "MVWm = " << MVWm << '\n';
   ostr << "MVP = " << MVP << '\n';
   ostr << "MVZ = " << MVZ << '\n';

   ostr << "----------------------------------------\n"
           "pole mass mixing matrices:\n"
           "----------------------------------------\n";
   ostr << "ZH = " << ZH << '\n';
   ostr << "ZA = " << ZA << '\n';
   ostr << "ZP = " << ZP << '\n';
   ostr << "Vd = " << Vd << '\n';
   ostr << "Ud = " << Ud << '\n';
   ostr << "Vu = " << Vu << '\n';
   ostr << "Uu = " << Uu << '\n';
   ostr << "Ve = " << Ve << '\n';
   ostr << "Ue = " << Ue << '\n';
   ostr << "ZZ = " << ZZ << '\n';

}

std::ostream& operator<<(std::ostream& ostr, const THDM_I_physical& phys_pars)
{
   phys_pars.print(ostr);
   return ostr;
}

} // namespace flexiblesusy
