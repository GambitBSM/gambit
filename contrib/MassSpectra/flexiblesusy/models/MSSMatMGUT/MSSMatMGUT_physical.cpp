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

// File generated at Thu 10 May 2018 15:09:32

#include "MSSMatMGUT_physical.hpp"
#include "slha_io.hpp"

#include <iostream>

#define LOCALPHYSICAL(p) p

namespace flexiblesusy {

void MSSMatMGUT_physical::clear()
{
   MVG = 0.;
   MGlu = 0.;
   MFv = Eigen::Matrix<double,3,1>::Zero();
   MSd = Eigen::Matrix<double,6,1>::Zero();
   ZD = Eigen::Matrix<double,6,6>::Zero();
   MSv = Eigen::Matrix<double,3,1>::Zero();
   ZV = Eigen::Matrix<double,3,3>::Zero();
   MSu = Eigen::Matrix<double,6,1>::Zero();
   ZU = Eigen::Matrix<double,6,6>::Zero();
   MSe = Eigen::Matrix<double,6,1>::Zero();
   ZE = Eigen::Matrix<double,6,6>::Zero();
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
   MFe = Eigen::Matrix<double,3,1>::Zero();
   ZEL = Eigen::Matrix<std::complex<double>,3,3>::Zero();
   ZER = Eigen::Matrix<std::complex<double>,3,3>::Zero();
   MFd = Eigen::Matrix<double,3,1>::Zero();
   ZDL = Eigen::Matrix<std::complex<double>,3,3>::Zero();
   ZDR = Eigen::Matrix<std::complex<double>,3,3>::Zero();
   MFu = Eigen::Matrix<double,3,1>::Zero();
   ZUL = Eigen::Matrix<std::complex<double>,3,3>::Zero();
   ZUR = Eigen::Matrix<std::complex<double>,3,3>::Zero();
   MVWm = 0.;
   MVP = 0.;
   MVZ = 0.;

}

/**
 * Convert masses and mixing matrices to Haber-Kane convention:
 * Fermion masses are always positive and mixing matrices are allowed
 * to be complex.
 */
void MSSMatMGUT_physical::convert_to_hk()
{
   SLHA_io::convert_symmetric_fermion_mixings_to_hk(LOCALPHYSICAL(MChi), LOCALPHYSICAL(ZN));

}

/**
 * Convert masses and mixing matrices to SLHA convention: Fermion
 * mixing matrices are always real and fermion masses are allowed to
 * be negative.
 */
void MSSMatMGUT_physical::convert_to_slha()
{
   SLHA_io::convert_symmetric_fermion_mixings_to_slha(LOCALPHYSICAL(MChi), LOCALPHYSICAL(ZN));

}

Eigen::ArrayXd MSSMatMGUT_physical::get() const
{
   Eigen::ArrayXd pars(get_masses());

   pars.conservativeResize(339);

   pars(50) = ZD(0,0);
   pars(51) = ZD(0,1);
   pars(52) = ZD(0,2);
   pars(53) = ZD(0,3);
   pars(54) = ZD(0,4);
   pars(55) = ZD(0,5);
   pars(56) = ZD(1,0);
   pars(57) = ZD(1,1);
   pars(58) = ZD(1,2);
   pars(59) = ZD(1,3);
   pars(60) = ZD(1,4);
   pars(61) = ZD(1,5);
   pars(62) = ZD(2,0);
   pars(63) = ZD(2,1);
   pars(64) = ZD(2,2);
   pars(65) = ZD(2,3);
   pars(66) = ZD(2,4);
   pars(67) = ZD(2,5);
   pars(68) = ZD(3,0);
   pars(69) = ZD(3,1);
   pars(70) = ZD(3,2);
   pars(71) = ZD(3,3);
   pars(72) = ZD(3,4);
   pars(73) = ZD(3,5);
   pars(74) = ZD(4,0);
   pars(75) = ZD(4,1);
   pars(76) = ZD(4,2);
   pars(77) = ZD(4,3);
   pars(78) = ZD(4,4);
   pars(79) = ZD(4,5);
   pars(80) = ZD(5,0);
   pars(81) = ZD(5,1);
   pars(82) = ZD(5,2);
   pars(83) = ZD(5,3);
   pars(84) = ZD(5,4);
   pars(85) = ZD(5,5);
   pars(86) = ZV(0,0);
   pars(87) = ZV(0,1);
   pars(88) = ZV(0,2);
   pars(89) = ZV(1,0);
   pars(90) = ZV(1,1);
   pars(91) = ZV(1,2);
   pars(92) = ZV(2,0);
   pars(93) = ZV(2,1);
   pars(94) = ZV(2,2);
   pars(95) = ZU(0,0);
   pars(96) = ZU(0,1);
   pars(97) = ZU(0,2);
   pars(98) = ZU(0,3);
   pars(99) = ZU(0,4);
   pars(100) = ZU(0,5);
   pars(101) = ZU(1,0);
   pars(102) = ZU(1,1);
   pars(103) = ZU(1,2);
   pars(104) = ZU(1,3);
   pars(105) = ZU(1,4);
   pars(106) = ZU(1,5);
   pars(107) = ZU(2,0);
   pars(108) = ZU(2,1);
   pars(109) = ZU(2,2);
   pars(110) = ZU(2,3);
   pars(111) = ZU(2,4);
   pars(112) = ZU(2,5);
   pars(113) = ZU(3,0);
   pars(114) = ZU(3,1);
   pars(115) = ZU(3,2);
   pars(116) = ZU(3,3);
   pars(117) = ZU(3,4);
   pars(118) = ZU(3,5);
   pars(119) = ZU(4,0);
   pars(120) = ZU(4,1);
   pars(121) = ZU(4,2);
   pars(122) = ZU(4,3);
   pars(123) = ZU(4,4);
   pars(124) = ZU(4,5);
   pars(125) = ZU(5,0);
   pars(126) = ZU(5,1);
   pars(127) = ZU(5,2);
   pars(128) = ZU(5,3);
   pars(129) = ZU(5,4);
   pars(130) = ZU(5,5);
   pars(131) = ZE(0,0);
   pars(132) = ZE(0,1);
   pars(133) = ZE(0,2);
   pars(134) = ZE(0,3);
   pars(135) = ZE(0,4);
   pars(136) = ZE(0,5);
   pars(137) = ZE(1,0);
   pars(138) = ZE(1,1);
   pars(139) = ZE(1,2);
   pars(140) = ZE(1,3);
   pars(141) = ZE(1,4);
   pars(142) = ZE(1,5);
   pars(143) = ZE(2,0);
   pars(144) = ZE(2,1);
   pars(145) = ZE(2,2);
   pars(146) = ZE(2,3);
   pars(147) = ZE(2,4);
   pars(148) = ZE(2,5);
   pars(149) = ZE(3,0);
   pars(150) = ZE(3,1);
   pars(151) = ZE(3,2);
   pars(152) = ZE(3,3);
   pars(153) = ZE(3,4);
   pars(154) = ZE(3,5);
   pars(155) = ZE(4,0);
   pars(156) = ZE(4,1);
   pars(157) = ZE(4,2);
   pars(158) = ZE(4,3);
   pars(159) = ZE(4,4);
   pars(160) = ZE(4,5);
   pars(161) = ZE(5,0);
   pars(162) = ZE(5,1);
   pars(163) = ZE(5,2);
   pars(164) = ZE(5,3);
   pars(165) = ZE(5,4);
   pars(166) = ZE(5,5);
   pars(167) = ZH(0,0);
   pars(168) = ZH(0,1);
   pars(169) = ZH(1,0);
   pars(170) = ZH(1,1);
   pars(171) = ZA(0,0);
   pars(172) = ZA(0,1);
   pars(173) = ZA(1,0);
   pars(174) = ZA(1,1);
   pars(175) = ZP(0,0);
   pars(176) = ZP(0,1);
   pars(177) = ZP(1,0);
   pars(178) = ZP(1,1);
   pars(179) = Re(ZN(0,0));
   pars(180) = Im(ZN(0,0));
   pars(181) = Re(ZN(0,1));
   pars(182) = Im(ZN(0,1));
   pars(183) = Re(ZN(0,2));
   pars(184) = Im(ZN(0,2));
   pars(185) = Re(ZN(0,3));
   pars(186) = Im(ZN(0,3));
   pars(187) = Re(ZN(1,0));
   pars(188) = Im(ZN(1,0));
   pars(189) = Re(ZN(1,1));
   pars(190) = Im(ZN(1,1));
   pars(191) = Re(ZN(1,2));
   pars(192) = Im(ZN(1,2));
   pars(193) = Re(ZN(1,3));
   pars(194) = Im(ZN(1,3));
   pars(195) = Re(ZN(2,0));
   pars(196) = Im(ZN(2,0));
   pars(197) = Re(ZN(2,1));
   pars(198) = Im(ZN(2,1));
   pars(199) = Re(ZN(2,2));
   pars(200) = Im(ZN(2,2));
   pars(201) = Re(ZN(2,3));
   pars(202) = Im(ZN(2,3));
   pars(203) = Re(ZN(3,0));
   pars(204) = Im(ZN(3,0));
   pars(205) = Re(ZN(3,1));
   pars(206) = Im(ZN(3,1));
   pars(207) = Re(ZN(3,2));
   pars(208) = Im(ZN(3,2));
   pars(209) = Re(ZN(3,3));
   pars(210) = Im(ZN(3,3));
   pars(211) = Re(UM(0,0));
   pars(212) = Im(UM(0,0));
   pars(213) = Re(UM(0,1));
   pars(214) = Im(UM(0,1));
   pars(215) = Re(UM(1,0));
   pars(216) = Im(UM(1,0));
   pars(217) = Re(UM(1,1));
   pars(218) = Im(UM(1,1));
   pars(219) = Re(UP(0,0));
   pars(220) = Im(UP(0,0));
   pars(221) = Re(UP(0,1));
   pars(222) = Im(UP(0,1));
   pars(223) = Re(UP(1,0));
   pars(224) = Im(UP(1,0));
   pars(225) = Re(UP(1,1));
   pars(226) = Im(UP(1,1));
   pars(227) = Re(ZEL(0,0));
   pars(228) = Im(ZEL(0,0));
   pars(229) = Re(ZEL(0,1));
   pars(230) = Im(ZEL(0,1));
   pars(231) = Re(ZEL(0,2));
   pars(232) = Im(ZEL(0,2));
   pars(233) = Re(ZEL(1,0));
   pars(234) = Im(ZEL(1,0));
   pars(235) = Re(ZEL(1,1));
   pars(236) = Im(ZEL(1,1));
   pars(237) = Re(ZEL(1,2));
   pars(238) = Im(ZEL(1,2));
   pars(239) = Re(ZEL(2,0));
   pars(240) = Im(ZEL(2,0));
   pars(241) = Re(ZEL(2,1));
   pars(242) = Im(ZEL(2,1));
   pars(243) = Re(ZEL(2,2));
   pars(244) = Im(ZEL(2,2));
   pars(245) = Re(ZER(0,0));
   pars(246) = Im(ZER(0,0));
   pars(247) = Re(ZER(0,1));
   pars(248) = Im(ZER(0,1));
   pars(249) = Re(ZER(0,2));
   pars(250) = Im(ZER(0,2));
   pars(251) = Re(ZER(1,0));
   pars(252) = Im(ZER(1,0));
   pars(253) = Re(ZER(1,1));
   pars(254) = Im(ZER(1,1));
   pars(255) = Re(ZER(1,2));
   pars(256) = Im(ZER(1,2));
   pars(257) = Re(ZER(2,0));
   pars(258) = Im(ZER(2,0));
   pars(259) = Re(ZER(2,1));
   pars(260) = Im(ZER(2,1));
   pars(261) = Re(ZER(2,2));
   pars(262) = Im(ZER(2,2));
   pars(263) = Re(ZDL(0,0));
   pars(264) = Im(ZDL(0,0));
   pars(265) = Re(ZDL(0,1));
   pars(266) = Im(ZDL(0,1));
   pars(267) = Re(ZDL(0,2));
   pars(268) = Im(ZDL(0,2));
   pars(269) = Re(ZDL(1,0));
   pars(270) = Im(ZDL(1,0));
   pars(271) = Re(ZDL(1,1));
   pars(272) = Im(ZDL(1,1));
   pars(273) = Re(ZDL(1,2));
   pars(274) = Im(ZDL(1,2));
   pars(275) = Re(ZDL(2,0));
   pars(276) = Im(ZDL(2,0));
   pars(277) = Re(ZDL(2,1));
   pars(278) = Im(ZDL(2,1));
   pars(279) = Re(ZDL(2,2));
   pars(280) = Im(ZDL(2,2));
   pars(281) = Re(ZDR(0,0));
   pars(282) = Im(ZDR(0,0));
   pars(283) = Re(ZDR(0,1));
   pars(284) = Im(ZDR(0,1));
   pars(285) = Re(ZDR(0,2));
   pars(286) = Im(ZDR(0,2));
   pars(287) = Re(ZDR(1,0));
   pars(288) = Im(ZDR(1,0));
   pars(289) = Re(ZDR(1,1));
   pars(290) = Im(ZDR(1,1));
   pars(291) = Re(ZDR(1,2));
   pars(292) = Im(ZDR(1,2));
   pars(293) = Re(ZDR(2,0));
   pars(294) = Im(ZDR(2,0));
   pars(295) = Re(ZDR(2,1));
   pars(296) = Im(ZDR(2,1));
   pars(297) = Re(ZDR(2,2));
   pars(298) = Im(ZDR(2,2));
   pars(299) = Re(ZUL(0,0));
   pars(300) = Im(ZUL(0,0));
   pars(301) = Re(ZUL(0,1));
   pars(302) = Im(ZUL(0,1));
   pars(303) = Re(ZUL(0,2));
   pars(304) = Im(ZUL(0,2));
   pars(305) = Re(ZUL(1,0));
   pars(306) = Im(ZUL(1,0));
   pars(307) = Re(ZUL(1,1));
   pars(308) = Im(ZUL(1,1));
   pars(309) = Re(ZUL(1,2));
   pars(310) = Im(ZUL(1,2));
   pars(311) = Re(ZUL(2,0));
   pars(312) = Im(ZUL(2,0));
   pars(313) = Re(ZUL(2,1));
   pars(314) = Im(ZUL(2,1));
   pars(315) = Re(ZUL(2,2));
   pars(316) = Im(ZUL(2,2));
   pars(317) = Re(ZUR(0,0));
   pars(318) = Im(ZUR(0,0));
   pars(319) = Re(ZUR(0,1));
   pars(320) = Im(ZUR(0,1));
   pars(321) = Re(ZUR(0,2));
   pars(322) = Im(ZUR(0,2));
   pars(323) = Re(ZUR(1,0));
   pars(324) = Im(ZUR(1,0));
   pars(325) = Re(ZUR(1,1));
   pars(326) = Im(ZUR(1,1));
   pars(327) = Re(ZUR(1,2));
   pars(328) = Im(ZUR(1,2));
   pars(329) = Re(ZUR(2,0));
   pars(330) = Im(ZUR(2,0));
   pars(331) = Re(ZUR(2,1));
   pars(332) = Im(ZUR(2,1));
   pars(333) = Re(ZUR(2,2));
   pars(334) = Im(ZUR(2,2));
   pars(335) = ZZ(0,0);
   pars(336) = ZZ(0,1);
   pars(337) = ZZ(1,0);
   pars(338) = ZZ(1,1);


   return pars;
}

void MSSMatMGUT_physical::set(const Eigen::ArrayXd& pars)
{
   set_masses(pars);

   ZD(0,0) = pars(50);
   ZD(0,1) = pars(51);
   ZD(0,2) = pars(52);
   ZD(0,3) = pars(53);
   ZD(0,4) = pars(54);
   ZD(0,5) = pars(55);
   ZD(1,0) = pars(56);
   ZD(1,1) = pars(57);
   ZD(1,2) = pars(58);
   ZD(1,3) = pars(59);
   ZD(1,4) = pars(60);
   ZD(1,5) = pars(61);
   ZD(2,0) = pars(62);
   ZD(2,1) = pars(63);
   ZD(2,2) = pars(64);
   ZD(2,3) = pars(65);
   ZD(2,4) = pars(66);
   ZD(2,5) = pars(67);
   ZD(3,0) = pars(68);
   ZD(3,1) = pars(69);
   ZD(3,2) = pars(70);
   ZD(3,3) = pars(71);
   ZD(3,4) = pars(72);
   ZD(3,5) = pars(73);
   ZD(4,0) = pars(74);
   ZD(4,1) = pars(75);
   ZD(4,2) = pars(76);
   ZD(4,3) = pars(77);
   ZD(4,4) = pars(78);
   ZD(4,5) = pars(79);
   ZD(5,0) = pars(80);
   ZD(5,1) = pars(81);
   ZD(5,2) = pars(82);
   ZD(5,3) = pars(83);
   ZD(5,4) = pars(84);
   ZD(5,5) = pars(85);
   ZV(0,0) = pars(86);
   ZV(0,1) = pars(87);
   ZV(0,2) = pars(88);
   ZV(1,0) = pars(89);
   ZV(1,1) = pars(90);
   ZV(1,2) = pars(91);
   ZV(2,0) = pars(92);
   ZV(2,1) = pars(93);
   ZV(2,2) = pars(94);
   ZU(0,0) = pars(95);
   ZU(0,1) = pars(96);
   ZU(0,2) = pars(97);
   ZU(0,3) = pars(98);
   ZU(0,4) = pars(99);
   ZU(0,5) = pars(100);
   ZU(1,0) = pars(101);
   ZU(1,1) = pars(102);
   ZU(1,2) = pars(103);
   ZU(1,3) = pars(104);
   ZU(1,4) = pars(105);
   ZU(1,5) = pars(106);
   ZU(2,0) = pars(107);
   ZU(2,1) = pars(108);
   ZU(2,2) = pars(109);
   ZU(2,3) = pars(110);
   ZU(2,4) = pars(111);
   ZU(2,5) = pars(112);
   ZU(3,0) = pars(113);
   ZU(3,1) = pars(114);
   ZU(3,2) = pars(115);
   ZU(3,3) = pars(116);
   ZU(3,4) = pars(117);
   ZU(3,5) = pars(118);
   ZU(4,0) = pars(119);
   ZU(4,1) = pars(120);
   ZU(4,2) = pars(121);
   ZU(4,3) = pars(122);
   ZU(4,4) = pars(123);
   ZU(4,5) = pars(124);
   ZU(5,0) = pars(125);
   ZU(5,1) = pars(126);
   ZU(5,2) = pars(127);
   ZU(5,3) = pars(128);
   ZU(5,4) = pars(129);
   ZU(5,5) = pars(130);
   ZE(0,0) = pars(131);
   ZE(0,1) = pars(132);
   ZE(0,2) = pars(133);
   ZE(0,3) = pars(134);
   ZE(0,4) = pars(135);
   ZE(0,5) = pars(136);
   ZE(1,0) = pars(137);
   ZE(1,1) = pars(138);
   ZE(1,2) = pars(139);
   ZE(1,3) = pars(140);
   ZE(1,4) = pars(141);
   ZE(1,5) = pars(142);
   ZE(2,0) = pars(143);
   ZE(2,1) = pars(144);
   ZE(2,2) = pars(145);
   ZE(2,3) = pars(146);
   ZE(2,4) = pars(147);
   ZE(2,5) = pars(148);
   ZE(3,0) = pars(149);
   ZE(3,1) = pars(150);
   ZE(3,2) = pars(151);
   ZE(3,3) = pars(152);
   ZE(3,4) = pars(153);
   ZE(3,5) = pars(154);
   ZE(4,0) = pars(155);
   ZE(4,1) = pars(156);
   ZE(4,2) = pars(157);
   ZE(4,3) = pars(158);
   ZE(4,4) = pars(159);
   ZE(4,5) = pars(160);
   ZE(5,0) = pars(161);
   ZE(5,1) = pars(162);
   ZE(5,2) = pars(163);
   ZE(5,3) = pars(164);
   ZE(5,4) = pars(165);
   ZE(5,5) = pars(166);
   ZH(0,0) = pars(167);
   ZH(0,1) = pars(168);
   ZH(1,0) = pars(169);
   ZH(1,1) = pars(170);
   ZA(0,0) = pars(171);
   ZA(0,1) = pars(172);
   ZA(1,0) = pars(173);
   ZA(1,1) = pars(174);
   ZP(0,0) = pars(175);
   ZP(0,1) = pars(176);
   ZP(1,0) = pars(177);
   ZP(1,1) = pars(178);
   ZN(0,0) = std::complex<double>(pars(179), pars(180));
   ZN(0,1) = std::complex<double>(pars(181), pars(182));
   ZN(0,2) = std::complex<double>(pars(183), pars(184));
   ZN(0,3) = std::complex<double>(pars(185), pars(186));
   ZN(1,0) = std::complex<double>(pars(187), pars(188));
   ZN(1,1) = std::complex<double>(pars(189), pars(190));
   ZN(1,2) = std::complex<double>(pars(191), pars(192));
   ZN(1,3) = std::complex<double>(pars(193), pars(194));
   ZN(2,0) = std::complex<double>(pars(195), pars(196));
   ZN(2,1) = std::complex<double>(pars(197), pars(198));
   ZN(2,2) = std::complex<double>(pars(199), pars(200));
   ZN(2,3) = std::complex<double>(pars(201), pars(202));
   ZN(3,0) = std::complex<double>(pars(203), pars(204));
   ZN(3,1) = std::complex<double>(pars(205), pars(206));
   ZN(3,2) = std::complex<double>(pars(207), pars(208));
   ZN(3,3) = std::complex<double>(pars(209), pars(210));
   UM(0,0) = std::complex<double>(pars(211), pars(212));
   UM(0,1) = std::complex<double>(pars(213), pars(214));
   UM(1,0) = std::complex<double>(pars(215), pars(216));
   UM(1,1) = std::complex<double>(pars(217), pars(218));
   UP(0,0) = std::complex<double>(pars(219), pars(220));
   UP(0,1) = std::complex<double>(pars(221), pars(222));
   UP(1,0) = std::complex<double>(pars(223), pars(224));
   UP(1,1) = std::complex<double>(pars(225), pars(226));
   ZEL(0,0) = std::complex<double>(pars(227), pars(228));
   ZEL(0,1) = std::complex<double>(pars(229), pars(230));
   ZEL(0,2) = std::complex<double>(pars(231), pars(232));
   ZEL(1,0) = std::complex<double>(pars(233), pars(234));
   ZEL(1,1) = std::complex<double>(pars(235), pars(236));
   ZEL(1,2) = std::complex<double>(pars(237), pars(238));
   ZEL(2,0) = std::complex<double>(pars(239), pars(240));
   ZEL(2,1) = std::complex<double>(pars(241), pars(242));
   ZEL(2,2) = std::complex<double>(pars(243), pars(244));
   ZER(0,0) = std::complex<double>(pars(245), pars(246));
   ZER(0,1) = std::complex<double>(pars(247), pars(248));
   ZER(0,2) = std::complex<double>(pars(249), pars(250));
   ZER(1,0) = std::complex<double>(pars(251), pars(252));
   ZER(1,1) = std::complex<double>(pars(253), pars(254));
   ZER(1,2) = std::complex<double>(pars(255), pars(256));
   ZER(2,0) = std::complex<double>(pars(257), pars(258));
   ZER(2,1) = std::complex<double>(pars(259), pars(260));
   ZER(2,2) = std::complex<double>(pars(261), pars(262));
   ZDL(0,0) = std::complex<double>(pars(263), pars(264));
   ZDL(0,1) = std::complex<double>(pars(265), pars(266));
   ZDL(0,2) = std::complex<double>(pars(267), pars(268));
   ZDL(1,0) = std::complex<double>(pars(269), pars(270));
   ZDL(1,1) = std::complex<double>(pars(271), pars(272));
   ZDL(1,2) = std::complex<double>(pars(273), pars(274));
   ZDL(2,0) = std::complex<double>(pars(275), pars(276));
   ZDL(2,1) = std::complex<double>(pars(277), pars(278));
   ZDL(2,2) = std::complex<double>(pars(279), pars(280));
   ZDR(0,0) = std::complex<double>(pars(281), pars(282));
   ZDR(0,1) = std::complex<double>(pars(283), pars(284));
   ZDR(0,2) = std::complex<double>(pars(285), pars(286));
   ZDR(1,0) = std::complex<double>(pars(287), pars(288));
   ZDR(1,1) = std::complex<double>(pars(289), pars(290));
   ZDR(1,2) = std::complex<double>(pars(291), pars(292));
   ZDR(2,0) = std::complex<double>(pars(293), pars(294));
   ZDR(2,1) = std::complex<double>(pars(295), pars(296));
   ZDR(2,2) = std::complex<double>(pars(297), pars(298));
   ZUL(0,0) = std::complex<double>(pars(299), pars(300));
   ZUL(0,1) = std::complex<double>(pars(301), pars(302));
   ZUL(0,2) = std::complex<double>(pars(303), pars(304));
   ZUL(1,0) = std::complex<double>(pars(305), pars(306));
   ZUL(1,1) = std::complex<double>(pars(307), pars(308));
   ZUL(1,2) = std::complex<double>(pars(309), pars(310));
   ZUL(2,0) = std::complex<double>(pars(311), pars(312));
   ZUL(2,1) = std::complex<double>(pars(313), pars(314));
   ZUL(2,2) = std::complex<double>(pars(315), pars(316));
   ZUR(0,0) = std::complex<double>(pars(317), pars(318));
   ZUR(0,1) = std::complex<double>(pars(319), pars(320));
   ZUR(0,2) = std::complex<double>(pars(321), pars(322));
   ZUR(1,0) = std::complex<double>(pars(323), pars(324));
   ZUR(1,1) = std::complex<double>(pars(325), pars(326));
   ZUR(1,2) = std::complex<double>(pars(327), pars(328));
   ZUR(2,0) = std::complex<double>(pars(329), pars(330));
   ZUR(2,1) = std::complex<double>(pars(331), pars(332));
   ZUR(2,2) = std::complex<double>(pars(333), pars(334));
   ZZ(0,0) = pars(335);
   ZZ(0,1) = pars(336);
   ZZ(1,0) = pars(337);
   ZZ(1,1) = pars(338);

}

Eigen::ArrayXd MSSMatMGUT_physical::get_masses() const
{
   Eigen::ArrayXd pars(50);

   pars(0) = MVG;
   pars(1) = MGlu;
   pars(2) = MFv(0);
   pars(3) = MFv(1);
   pars(4) = MFv(2);
   pars(5) = MSd(0);
   pars(6) = MSd(1);
   pars(7) = MSd(2);
   pars(8) = MSd(3);
   pars(9) = MSd(4);
   pars(10) = MSd(5);
   pars(11) = MSv(0);
   pars(12) = MSv(1);
   pars(13) = MSv(2);
   pars(14) = MSu(0);
   pars(15) = MSu(1);
   pars(16) = MSu(2);
   pars(17) = MSu(3);
   pars(18) = MSu(4);
   pars(19) = MSu(5);
   pars(20) = MSe(0);
   pars(21) = MSe(1);
   pars(22) = MSe(2);
   pars(23) = MSe(3);
   pars(24) = MSe(4);
   pars(25) = MSe(5);
   pars(26) = Mhh(0);
   pars(27) = Mhh(1);
   pars(28) = MAh(0);
   pars(29) = MAh(1);
   pars(30) = MHpm(0);
   pars(31) = MHpm(1);
   pars(32) = MChi(0);
   pars(33) = MChi(1);
   pars(34) = MChi(2);
   pars(35) = MChi(3);
   pars(36) = MCha(0);
   pars(37) = MCha(1);
   pars(38) = MFe(0);
   pars(39) = MFe(1);
   pars(40) = MFe(2);
   pars(41) = MFd(0);
   pars(42) = MFd(1);
   pars(43) = MFd(2);
   pars(44) = MFu(0);
   pars(45) = MFu(1);
   pars(46) = MFu(2);
   pars(47) = MVWm;
   pars(48) = MVP;
   pars(49) = MVZ;

   return pars;
}

void MSSMatMGUT_physical::set_masses(const Eigen::ArrayXd& pars)
{
   MVG = pars(0);
   MGlu = pars(1);
   MFv(0) = pars(2);
   MFv(1) = pars(3);
   MFv(2) = pars(4);
   MSd(0) = pars(5);
   MSd(1) = pars(6);
   MSd(2) = pars(7);
   MSd(3) = pars(8);
   MSd(4) = pars(9);
   MSd(5) = pars(10);
   MSv(0) = pars(11);
   MSv(1) = pars(12);
   MSv(2) = pars(13);
   MSu(0) = pars(14);
   MSu(1) = pars(15);
   MSu(2) = pars(16);
   MSu(3) = pars(17);
   MSu(4) = pars(18);
   MSu(5) = pars(19);
   MSe(0) = pars(20);
   MSe(1) = pars(21);
   MSe(2) = pars(22);
   MSe(3) = pars(23);
   MSe(4) = pars(24);
   MSe(5) = pars(25);
   Mhh(0) = pars(26);
   Mhh(1) = pars(27);
   MAh(0) = pars(28);
   MAh(1) = pars(29);
   MHpm(0) = pars(30);
   MHpm(1) = pars(31);
   MChi(0) = pars(32);
   MChi(1) = pars(33);
   MChi(2) = pars(34);
   MChi(3) = pars(35);
   MCha(0) = pars(36);
   MCha(1) = pars(37);
   MFe(0) = pars(38);
   MFe(1) = pars(39);
   MFe(2) = pars(40);
   MFd(0) = pars(41);
   MFd(1) = pars(42);
   MFd(2) = pars(43);
   MFu(0) = pars(44);
   MFu(1) = pars(45);
   MFu(2) = pars(46);
   MVWm = pars(47);
   MVP = pars(48);
   MVZ = pars(49);

}

void MSSMatMGUT_physical::print(std::ostream& ostr) const
{
   ostr << "----------------------------------------\n"
           "pole masses:\n"
           "----------------------------------------\n";
   ostr << "MVG = " << MVG << '\n';
   ostr << "MGlu = " << MGlu << '\n';
   ostr << "MFv = " << MFv.transpose() << '\n';
   ostr << "MSd = " << MSd.transpose() << '\n';
   ostr << "MSv = " << MSv.transpose() << '\n';
   ostr << "MSu = " << MSu.transpose() << '\n';
   ostr << "MSe = " << MSe.transpose() << '\n';
   ostr << "Mhh = " << Mhh.transpose() << '\n';
   ostr << "MAh = " << MAh.transpose() << '\n';
   ostr << "MHpm = " << MHpm.transpose() << '\n';
   ostr << "MChi = " << MChi.transpose() << '\n';
   ostr << "MCha = " << MCha.transpose() << '\n';
   ostr << "MFe = " << MFe.transpose() << '\n';
   ostr << "MFd = " << MFd.transpose() << '\n';
   ostr << "MFu = " << MFu.transpose() << '\n';
   ostr << "MVWm = " << MVWm << '\n';
   ostr << "MVP = " << MVP << '\n';
   ostr << "MVZ = " << MVZ << '\n';

   ostr << "----------------------------------------\n"
           "pole mass mixing matrices:\n"
           "----------------------------------------\n";
   ostr << "ZD = " << ZD << '\n';
   ostr << "ZV = " << ZV << '\n';
   ostr << "ZU = " << ZU << '\n';
   ostr << "ZE = " << ZE << '\n';
   ostr << "ZH = " << ZH << '\n';
   ostr << "ZA = " << ZA << '\n';
   ostr << "ZP = " << ZP << '\n';
   ostr << "ZN = " << ZN << '\n';
   ostr << "UM = " << UM << '\n';
   ostr << "UP = " << UP << '\n';
   ostr << "ZEL = " << ZEL << '\n';
   ostr << "ZER = " << ZER << '\n';
   ostr << "ZDL = " << ZDL << '\n';
   ostr << "ZDR = " << ZDR << '\n';
   ostr << "ZUL = " << ZUL << '\n';
   ostr << "ZUR = " << ZUR << '\n';
   ostr << "ZZ = " << ZZ << '\n';

}

std::ostream& operator<<(std::ostream& ostr, const MSSMatMGUT_physical& phys_pars)
{
   phys_pars.print(ostr);
   return ostr;
}

} // namespace flexiblesusy
