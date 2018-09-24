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

// File generated at Thu 10 May 2018 14:43:24

#include "SSM_physical.hpp"
#include "slha_io.hpp"

#include <iostream>

#define LOCALPHYSICAL(p) p

namespace flexiblesusy {

void SSM_physical::clear()
{
   MVG = 0.;
   MHp = 0.;
   MFv = Eigen::Matrix<double,3,1>::Zero();
   MAh = 0.;
   Mhh = Eigen::Matrix<double,2,1>::Zero();
   ZH = Eigen::Matrix<double,2,2>::Zero();
   MFd = Eigen::Matrix<double,3,1>::Zero();
   Vd = Eigen::Matrix<std::complex<double>,3,3>::Zero();
   Ud = Eigen::Matrix<std::complex<double>,3,3>::Zero();
   MFu = Eigen::Matrix<double,3,1>::Zero();
   Vu = Eigen::Matrix<std::complex<double>,3,3>::Zero();
   Uu = Eigen::Matrix<std::complex<double>,3,3>::Zero();
   MFe = Eigen::Matrix<double,3,1>::Zero();
   Ve = Eigen::Matrix<std::complex<double>,3,3>::Zero();
   Ue = Eigen::Matrix<std::complex<double>,3,3>::Zero();
   MVWp = 0.;
   MVP = 0.;
   MVZ = 0.;

}

/**
 * Convert masses and mixing matrices to Haber-Kane convention:
 * Fermion masses are always positive and mixing matrices are allowed
 * to be complex.
 */
void SSM_physical::convert_to_hk()
{

}

/**
 * Convert masses and mixing matrices to SLHA convention: Fermion
 * mixing matrices are always real and fermion masses are allowed to
 * be negative.
 */
void SSM_physical::convert_to_slha()
{

}

Eigen::ArrayXd SSM_physical::get() const
{
   Eigen::ArrayXd pars(get_masses());

   pars.conservativeResize(136);

   pars(20) = ZH(0,0);
   pars(21) = ZH(0,1);
   pars(22) = ZH(1,0);
   pars(23) = ZH(1,1);
   pars(24) = Re(Vd(0,0));
   pars(25) = Im(Vd(0,0));
   pars(26) = Re(Vd(0,1));
   pars(27) = Im(Vd(0,1));
   pars(28) = Re(Vd(0,2));
   pars(29) = Im(Vd(0,2));
   pars(30) = Re(Vd(1,0));
   pars(31) = Im(Vd(1,0));
   pars(32) = Re(Vd(1,1));
   pars(33) = Im(Vd(1,1));
   pars(34) = Re(Vd(1,2));
   pars(35) = Im(Vd(1,2));
   pars(36) = Re(Vd(2,0));
   pars(37) = Im(Vd(2,0));
   pars(38) = Re(Vd(2,1));
   pars(39) = Im(Vd(2,1));
   pars(40) = Re(Vd(2,2));
   pars(41) = Im(Vd(2,2));
   pars(42) = Re(Ud(0,0));
   pars(43) = Im(Ud(0,0));
   pars(44) = Re(Ud(0,1));
   pars(45) = Im(Ud(0,1));
   pars(46) = Re(Ud(0,2));
   pars(47) = Im(Ud(0,2));
   pars(48) = Re(Ud(1,0));
   pars(49) = Im(Ud(1,0));
   pars(50) = Re(Ud(1,1));
   pars(51) = Im(Ud(1,1));
   pars(52) = Re(Ud(1,2));
   pars(53) = Im(Ud(1,2));
   pars(54) = Re(Ud(2,0));
   pars(55) = Im(Ud(2,0));
   pars(56) = Re(Ud(2,1));
   pars(57) = Im(Ud(2,1));
   pars(58) = Re(Ud(2,2));
   pars(59) = Im(Ud(2,2));
   pars(60) = Re(Vu(0,0));
   pars(61) = Im(Vu(0,0));
   pars(62) = Re(Vu(0,1));
   pars(63) = Im(Vu(0,1));
   pars(64) = Re(Vu(0,2));
   pars(65) = Im(Vu(0,2));
   pars(66) = Re(Vu(1,0));
   pars(67) = Im(Vu(1,0));
   pars(68) = Re(Vu(1,1));
   pars(69) = Im(Vu(1,1));
   pars(70) = Re(Vu(1,2));
   pars(71) = Im(Vu(1,2));
   pars(72) = Re(Vu(2,0));
   pars(73) = Im(Vu(2,0));
   pars(74) = Re(Vu(2,1));
   pars(75) = Im(Vu(2,1));
   pars(76) = Re(Vu(2,2));
   pars(77) = Im(Vu(2,2));
   pars(78) = Re(Uu(0,0));
   pars(79) = Im(Uu(0,0));
   pars(80) = Re(Uu(0,1));
   pars(81) = Im(Uu(0,1));
   pars(82) = Re(Uu(0,2));
   pars(83) = Im(Uu(0,2));
   pars(84) = Re(Uu(1,0));
   pars(85) = Im(Uu(1,0));
   pars(86) = Re(Uu(1,1));
   pars(87) = Im(Uu(1,1));
   pars(88) = Re(Uu(1,2));
   pars(89) = Im(Uu(1,2));
   pars(90) = Re(Uu(2,0));
   pars(91) = Im(Uu(2,0));
   pars(92) = Re(Uu(2,1));
   pars(93) = Im(Uu(2,1));
   pars(94) = Re(Uu(2,2));
   pars(95) = Im(Uu(2,2));
   pars(96) = Re(Ve(0,0));
   pars(97) = Im(Ve(0,0));
   pars(98) = Re(Ve(0,1));
   pars(99) = Im(Ve(0,1));
   pars(100) = Re(Ve(0,2));
   pars(101) = Im(Ve(0,2));
   pars(102) = Re(Ve(1,0));
   pars(103) = Im(Ve(1,0));
   pars(104) = Re(Ve(1,1));
   pars(105) = Im(Ve(1,1));
   pars(106) = Re(Ve(1,2));
   pars(107) = Im(Ve(1,2));
   pars(108) = Re(Ve(2,0));
   pars(109) = Im(Ve(2,0));
   pars(110) = Re(Ve(2,1));
   pars(111) = Im(Ve(2,1));
   pars(112) = Re(Ve(2,2));
   pars(113) = Im(Ve(2,2));
   pars(114) = Re(Ue(0,0));
   pars(115) = Im(Ue(0,0));
   pars(116) = Re(Ue(0,1));
   pars(117) = Im(Ue(0,1));
   pars(118) = Re(Ue(0,2));
   pars(119) = Im(Ue(0,2));
   pars(120) = Re(Ue(1,0));
   pars(121) = Im(Ue(1,0));
   pars(122) = Re(Ue(1,1));
   pars(123) = Im(Ue(1,1));
   pars(124) = Re(Ue(1,2));
   pars(125) = Im(Ue(1,2));
   pars(126) = Re(Ue(2,0));
   pars(127) = Im(Ue(2,0));
   pars(128) = Re(Ue(2,1));
   pars(129) = Im(Ue(2,1));
   pars(130) = Re(Ue(2,2));
   pars(131) = Im(Ue(2,2));
   pars(132) = ZZ(0,0);
   pars(133) = ZZ(0,1);
   pars(134) = ZZ(1,0);
   pars(135) = ZZ(1,1);


   return pars;
}

void SSM_physical::set(const Eigen::ArrayXd& pars)
{
   set_masses(pars);

   ZH(0,0) = pars(20);
   ZH(0,1) = pars(21);
   ZH(1,0) = pars(22);
   ZH(1,1) = pars(23);
   Vd(0,0) = std::complex<double>(pars(24), pars(25));
   Vd(0,1) = std::complex<double>(pars(26), pars(27));
   Vd(0,2) = std::complex<double>(pars(28), pars(29));
   Vd(1,0) = std::complex<double>(pars(30), pars(31));
   Vd(1,1) = std::complex<double>(pars(32), pars(33));
   Vd(1,2) = std::complex<double>(pars(34), pars(35));
   Vd(2,0) = std::complex<double>(pars(36), pars(37));
   Vd(2,1) = std::complex<double>(pars(38), pars(39));
   Vd(2,2) = std::complex<double>(pars(40), pars(41));
   Ud(0,0) = std::complex<double>(pars(42), pars(43));
   Ud(0,1) = std::complex<double>(pars(44), pars(45));
   Ud(0,2) = std::complex<double>(pars(46), pars(47));
   Ud(1,0) = std::complex<double>(pars(48), pars(49));
   Ud(1,1) = std::complex<double>(pars(50), pars(51));
   Ud(1,2) = std::complex<double>(pars(52), pars(53));
   Ud(2,0) = std::complex<double>(pars(54), pars(55));
   Ud(2,1) = std::complex<double>(pars(56), pars(57));
   Ud(2,2) = std::complex<double>(pars(58), pars(59));
   Vu(0,0) = std::complex<double>(pars(60), pars(61));
   Vu(0,1) = std::complex<double>(pars(62), pars(63));
   Vu(0,2) = std::complex<double>(pars(64), pars(65));
   Vu(1,0) = std::complex<double>(pars(66), pars(67));
   Vu(1,1) = std::complex<double>(pars(68), pars(69));
   Vu(1,2) = std::complex<double>(pars(70), pars(71));
   Vu(2,0) = std::complex<double>(pars(72), pars(73));
   Vu(2,1) = std::complex<double>(pars(74), pars(75));
   Vu(2,2) = std::complex<double>(pars(76), pars(77));
   Uu(0,0) = std::complex<double>(pars(78), pars(79));
   Uu(0,1) = std::complex<double>(pars(80), pars(81));
   Uu(0,2) = std::complex<double>(pars(82), pars(83));
   Uu(1,0) = std::complex<double>(pars(84), pars(85));
   Uu(1,1) = std::complex<double>(pars(86), pars(87));
   Uu(1,2) = std::complex<double>(pars(88), pars(89));
   Uu(2,0) = std::complex<double>(pars(90), pars(91));
   Uu(2,1) = std::complex<double>(pars(92), pars(93));
   Uu(2,2) = std::complex<double>(pars(94), pars(95));
   Ve(0,0) = std::complex<double>(pars(96), pars(97));
   Ve(0,1) = std::complex<double>(pars(98), pars(99));
   Ve(0,2) = std::complex<double>(pars(100), pars(101));
   Ve(1,0) = std::complex<double>(pars(102), pars(103));
   Ve(1,1) = std::complex<double>(pars(104), pars(105));
   Ve(1,2) = std::complex<double>(pars(106), pars(107));
   Ve(2,0) = std::complex<double>(pars(108), pars(109));
   Ve(2,1) = std::complex<double>(pars(110), pars(111));
   Ve(2,2) = std::complex<double>(pars(112), pars(113));
   Ue(0,0) = std::complex<double>(pars(114), pars(115));
   Ue(0,1) = std::complex<double>(pars(116), pars(117));
   Ue(0,2) = std::complex<double>(pars(118), pars(119));
   Ue(1,0) = std::complex<double>(pars(120), pars(121));
   Ue(1,1) = std::complex<double>(pars(122), pars(123));
   Ue(1,2) = std::complex<double>(pars(124), pars(125));
   Ue(2,0) = std::complex<double>(pars(126), pars(127));
   Ue(2,1) = std::complex<double>(pars(128), pars(129));
   Ue(2,2) = std::complex<double>(pars(130), pars(131));
   ZZ(0,0) = pars(132);
   ZZ(0,1) = pars(133);
   ZZ(1,0) = pars(134);
   ZZ(1,1) = pars(135);

}

Eigen::ArrayXd SSM_physical::get_masses() const
{
   Eigen::ArrayXd pars(20);

   pars(0) = MVG;
   pars(1) = MHp;
   pars(2) = MFv(0);
   pars(3) = MFv(1);
   pars(4) = MFv(2);
   pars(5) = MAh;
   pars(6) = Mhh(0);
   pars(7) = Mhh(1);
   pars(8) = MFd(0);
   pars(9) = MFd(1);
   pars(10) = MFd(2);
   pars(11) = MFu(0);
   pars(12) = MFu(1);
   pars(13) = MFu(2);
   pars(14) = MFe(0);
   pars(15) = MFe(1);
   pars(16) = MFe(2);
   pars(17) = MVWp;
   pars(18) = MVP;
   pars(19) = MVZ;

   return pars;
}

void SSM_physical::set_masses(const Eigen::ArrayXd& pars)
{
   MVG = pars(0);
   MHp = pars(1);
   MFv(0) = pars(2);
   MFv(1) = pars(3);
   MFv(2) = pars(4);
   MAh = pars(5);
   Mhh(0) = pars(6);
   Mhh(1) = pars(7);
   MFd(0) = pars(8);
   MFd(1) = pars(9);
   MFd(2) = pars(10);
   MFu(0) = pars(11);
   MFu(1) = pars(12);
   MFu(2) = pars(13);
   MFe(0) = pars(14);
   MFe(1) = pars(15);
   MFe(2) = pars(16);
   MVWp = pars(17);
   MVP = pars(18);
   MVZ = pars(19);

}

void SSM_physical::print(std::ostream& ostr) const
{
   ostr << "----------------------------------------\n"
           "pole masses:\n"
           "----------------------------------------\n";
   ostr << "MVG = " << MVG << '\n';
   ostr << "MHp = " << MHp << '\n';
   ostr << "MFv = " << MFv.transpose() << '\n';
   ostr << "MAh = " << MAh << '\n';
   ostr << "Mhh = " << Mhh.transpose() << '\n';
   ostr << "MFd = " << MFd.transpose() << '\n';
   ostr << "MFu = " << MFu.transpose() << '\n';
   ostr << "MFe = " << MFe.transpose() << '\n';
   ostr << "MVWp = " << MVWp << '\n';
   ostr << "MVP = " << MVP << '\n';
   ostr << "MVZ = " << MVZ << '\n';

   ostr << "----------------------------------------\n"
           "pole mass mixing matrices:\n"
           "----------------------------------------\n";
   ostr << "ZH = " << ZH << '\n';
   ostr << "Vd = " << Vd << '\n';
   ostr << "Ud = " << Ud << '\n';
   ostr << "Vu = " << Vu << '\n';
   ostr << "Uu = " << Uu << '\n';
   ostr << "Ve = " << Ve << '\n';
   ostr << "Ue = " << Ue << '\n';
   ostr << "ZZ = " << ZZ << '\n';

}

std::ostream& operator<<(std::ostream& ostr, const SSM_physical& phys_pars)
{
   phys_pars.print(ostr);
   return ostr;
}

} // namespace flexiblesusy
