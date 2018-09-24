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

// File generated at Thu 10 May 2018 14:38:39

#include "MSSMatMSUSYEFTHiggs_input_parameters.hpp"
#include "wrappers.hpp"

#define INPUT(p) input.p

namespace flexiblesusy {

Eigen::ArrayXd MSSMatMSUSYEFTHiggs_input_parameters::get() const
{
   Eigen::ArrayXd pars(79);

   pars(0) = SignMu;
   pars(1) = M1Input;
   pars(2) = M2Input;
   pars(3) = M3Input;
   pars(4) = mHd2IN;
   pars(5) = mHu2IN;
   pars(6) = TanBeta;
   pars(7) = mq2Input(0,0);
   pars(8) = mq2Input(0,1);
   pars(9) = mq2Input(0,2);
   pars(10) = mq2Input(1,0);
   pars(11) = mq2Input(1,1);
   pars(12) = mq2Input(1,2);
   pars(13) = mq2Input(2,0);
   pars(14) = mq2Input(2,1);
   pars(15) = mq2Input(2,2);
   pars(16) = mu2Input(0,0);
   pars(17) = mu2Input(0,1);
   pars(18) = mu2Input(0,2);
   pars(19) = mu2Input(1,0);
   pars(20) = mu2Input(1,1);
   pars(21) = mu2Input(1,2);
   pars(22) = mu2Input(2,0);
   pars(23) = mu2Input(2,1);
   pars(24) = mu2Input(2,2);
   pars(25) = md2Input(0,0);
   pars(26) = md2Input(0,1);
   pars(27) = md2Input(0,2);
   pars(28) = md2Input(1,0);
   pars(29) = md2Input(1,1);
   pars(30) = md2Input(1,2);
   pars(31) = md2Input(2,0);
   pars(32) = md2Input(2,1);
   pars(33) = md2Input(2,2);
   pars(34) = ml2Input(0,0);
   pars(35) = ml2Input(0,1);
   pars(36) = ml2Input(0,2);
   pars(37) = ml2Input(1,0);
   pars(38) = ml2Input(1,1);
   pars(39) = ml2Input(1,2);
   pars(40) = ml2Input(2,0);
   pars(41) = ml2Input(2,1);
   pars(42) = ml2Input(2,2);
   pars(43) = me2Input(0,0);
   pars(44) = me2Input(0,1);
   pars(45) = me2Input(0,2);
   pars(46) = me2Input(1,0);
   pars(47) = me2Input(1,1);
   pars(48) = me2Input(1,2);
   pars(49) = me2Input(2,0);
   pars(50) = me2Input(2,1);
   pars(51) = me2Input(2,2);
   pars(52) = AuInput(0,0);
   pars(53) = AuInput(0,1);
   pars(54) = AuInput(0,2);
   pars(55) = AuInput(1,0);
   pars(56) = AuInput(1,1);
   pars(57) = AuInput(1,2);
   pars(58) = AuInput(2,0);
   pars(59) = AuInput(2,1);
   pars(60) = AuInput(2,2);
   pars(61) = AdInput(0,0);
   pars(62) = AdInput(0,1);
   pars(63) = AdInput(0,2);
   pars(64) = AdInput(1,0);
   pars(65) = AdInput(1,1);
   pars(66) = AdInput(1,2);
   pars(67) = AdInput(2,0);
   pars(68) = AdInput(2,1);
   pars(69) = AdInput(2,2);
   pars(70) = AeInput(0,0);
   pars(71) = AeInput(0,1);
   pars(72) = AeInput(0,2);
   pars(73) = AeInput(1,0);
   pars(74) = AeInput(1,1);
   pars(75) = AeInput(1,2);
   pars(76) = AeInput(2,0);
   pars(77) = AeInput(2,1);
   pars(78) = AeInput(2,2);

   return pars;
}

void MSSMatMSUSYEFTHiggs_input_parameters::set(const Eigen::ArrayXd& pars)
{
   SignMu = pars(0);
   M1Input = pars(1);
   M2Input = pars(2);
   M3Input = pars(3);
   mHd2IN = pars(4);
   mHu2IN = pars(5);
   TanBeta = pars(6);
   mq2Input(0,0) = pars(7);
   mq2Input(0,1) = pars(8);
   mq2Input(0,2) = pars(9);
   mq2Input(1,0) = pars(10);
   mq2Input(1,1) = pars(11);
   mq2Input(1,2) = pars(12);
   mq2Input(2,0) = pars(13);
   mq2Input(2,1) = pars(14);
   mq2Input(2,2) = pars(15);
   mu2Input(0,0) = pars(16);
   mu2Input(0,1) = pars(17);
   mu2Input(0,2) = pars(18);
   mu2Input(1,0) = pars(19);
   mu2Input(1,1) = pars(20);
   mu2Input(1,2) = pars(21);
   mu2Input(2,0) = pars(22);
   mu2Input(2,1) = pars(23);
   mu2Input(2,2) = pars(24);
   md2Input(0,0) = pars(25);
   md2Input(0,1) = pars(26);
   md2Input(0,2) = pars(27);
   md2Input(1,0) = pars(28);
   md2Input(1,1) = pars(29);
   md2Input(1,2) = pars(30);
   md2Input(2,0) = pars(31);
   md2Input(2,1) = pars(32);
   md2Input(2,2) = pars(33);
   ml2Input(0,0) = pars(34);
   ml2Input(0,1) = pars(35);
   ml2Input(0,2) = pars(36);
   ml2Input(1,0) = pars(37);
   ml2Input(1,1) = pars(38);
   ml2Input(1,2) = pars(39);
   ml2Input(2,0) = pars(40);
   ml2Input(2,1) = pars(41);
   ml2Input(2,2) = pars(42);
   me2Input(0,0) = pars(43);
   me2Input(0,1) = pars(44);
   me2Input(0,2) = pars(45);
   me2Input(1,0) = pars(46);
   me2Input(1,1) = pars(47);
   me2Input(1,2) = pars(48);
   me2Input(2,0) = pars(49);
   me2Input(2,1) = pars(50);
   me2Input(2,2) = pars(51);
   AuInput(0,0) = pars(52);
   AuInput(0,1) = pars(53);
   AuInput(0,2) = pars(54);
   AuInput(1,0) = pars(55);
   AuInput(1,1) = pars(56);
   AuInput(1,2) = pars(57);
   AuInput(2,0) = pars(58);
   AuInput(2,1) = pars(59);
   AuInput(2,2) = pars(60);
   AdInput(0,0) = pars(61);
   AdInput(0,1) = pars(62);
   AdInput(0,2) = pars(63);
   AdInput(1,0) = pars(64);
   AdInput(1,1) = pars(65);
   AdInput(1,2) = pars(66);
   AdInput(2,0) = pars(67);
   AdInput(2,1) = pars(68);
   AdInput(2,2) = pars(69);
   AeInput(0,0) = pars(70);
   AeInput(0,1) = pars(71);
   AeInput(0,2) = pars(72);
   AeInput(1,0) = pars(73);
   AeInput(1,1) = pars(74);
   AeInput(1,2) = pars(75);
   AeInput(2,0) = pars(76);
   AeInput(2,1) = pars(77);
   AeInput(2,2) = pars(78);

}

std::ostream& operator<<(std::ostream& ostr, const MSSMatMSUSYEFTHiggs_input_parameters& input)
{
   ostr << "SignMu = " << INPUT(SignMu) << ", ";
   ostr << "M1Input = " << INPUT(M1Input) << ", ";
   ostr << "M2Input = " << INPUT(M2Input) << ", ";
   ostr << "M3Input = " << INPUT(M3Input) << ", ";
   ostr << "mHd2IN = " << INPUT(mHd2IN) << ", ";
   ostr << "mHu2IN = " << INPUT(mHu2IN) << ", ";
   ostr << "TanBeta = " << INPUT(TanBeta) << ", ";
   ostr << "mq2Input = " << INPUT(mq2Input) << ", ";
   ostr << "mu2Input = " << INPUT(mu2Input) << ", ";
   ostr << "md2Input = " << INPUT(md2Input) << ", ";
   ostr << "ml2Input = " << INPUT(ml2Input) << ", ";
   ostr << "me2Input = " << INPUT(me2Input) << ", ";
   ostr << "AuInput = " << INPUT(AuInput) << ", ";
   ostr << "AdInput = " << INPUT(AdInput) << ", ";
   ostr << "AeInput = " << INPUT(AeInput) << ", ";

   return ostr;
}

} // namespace flexiblesusy
