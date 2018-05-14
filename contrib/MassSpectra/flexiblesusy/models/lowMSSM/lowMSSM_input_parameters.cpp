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

// File generated at Thu 10 May 2018 15:06:03

#include "lowMSSM_input_parameters.hpp"
#include "wrappers.hpp"

#define INPUT(p) input.p

namespace flexiblesusy {

Eigen::ArrayXd lowMSSM_input_parameters::get() const
{
   Eigen::ArrayXd pars(78);

   pars(0) = TanBeta;
   pars(1) = MuInput;
   pars(2) = TYdInput(0,0);
   pars(3) = TYdInput(0,1);
   pars(4) = TYdInput(0,2);
   pars(5) = TYdInput(1,0);
   pars(6) = TYdInput(1,1);
   pars(7) = TYdInput(1,2);
   pars(8) = TYdInput(2,0);
   pars(9) = TYdInput(2,1);
   pars(10) = TYdInput(2,2);
   pars(11) = TYeInput(0,0);
   pars(12) = TYeInput(0,1);
   pars(13) = TYeInput(0,2);
   pars(14) = TYeInput(1,0);
   pars(15) = TYeInput(1,1);
   pars(16) = TYeInput(1,2);
   pars(17) = TYeInput(2,0);
   pars(18) = TYeInput(2,1);
   pars(19) = TYeInput(2,2);
   pars(20) = TYuInput(0,0);
   pars(21) = TYuInput(0,1);
   pars(22) = TYuInput(0,2);
   pars(23) = TYuInput(1,0);
   pars(24) = TYuInput(1,1);
   pars(25) = TYuInput(1,2);
   pars(26) = TYuInput(2,0);
   pars(27) = TYuInput(2,1);
   pars(28) = TYuInput(2,2);
   pars(29) = BMuInput;
   pars(30) = mq2Input(0,0);
   pars(31) = mq2Input(0,1);
   pars(32) = mq2Input(0,2);
   pars(33) = mq2Input(1,0);
   pars(34) = mq2Input(1,1);
   pars(35) = mq2Input(1,2);
   pars(36) = mq2Input(2,0);
   pars(37) = mq2Input(2,1);
   pars(38) = mq2Input(2,2);
   pars(39) = ml2Input(0,0);
   pars(40) = ml2Input(0,1);
   pars(41) = ml2Input(0,2);
   pars(42) = ml2Input(1,0);
   pars(43) = ml2Input(1,1);
   pars(44) = ml2Input(1,2);
   pars(45) = ml2Input(2,0);
   pars(46) = ml2Input(2,1);
   pars(47) = ml2Input(2,2);
   pars(48) = md2Input(0,0);
   pars(49) = md2Input(0,1);
   pars(50) = md2Input(0,2);
   pars(51) = md2Input(1,0);
   pars(52) = md2Input(1,1);
   pars(53) = md2Input(1,2);
   pars(54) = md2Input(2,0);
   pars(55) = md2Input(2,1);
   pars(56) = md2Input(2,2);
   pars(57) = mu2Input(0,0);
   pars(58) = mu2Input(0,1);
   pars(59) = mu2Input(0,2);
   pars(60) = mu2Input(1,0);
   pars(61) = mu2Input(1,1);
   pars(62) = mu2Input(1,2);
   pars(63) = mu2Input(2,0);
   pars(64) = mu2Input(2,1);
   pars(65) = mu2Input(2,2);
   pars(66) = me2Input(0,0);
   pars(67) = me2Input(0,1);
   pars(68) = me2Input(0,2);
   pars(69) = me2Input(1,0);
   pars(70) = me2Input(1,1);
   pars(71) = me2Input(1,2);
   pars(72) = me2Input(2,0);
   pars(73) = me2Input(2,1);
   pars(74) = me2Input(2,2);
   pars(75) = MassBInput;
   pars(76) = MassWBInput;
   pars(77) = MassGInput;

   return pars;
}

void lowMSSM_input_parameters::set(const Eigen::ArrayXd& pars)
{
   TanBeta = pars(0);
   MuInput = pars(1);
   TYdInput(0,0) = pars(2);
   TYdInput(0,1) = pars(3);
   TYdInput(0,2) = pars(4);
   TYdInput(1,0) = pars(5);
   TYdInput(1,1) = pars(6);
   TYdInput(1,2) = pars(7);
   TYdInput(2,0) = pars(8);
   TYdInput(2,1) = pars(9);
   TYdInput(2,2) = pars(10);
   TYeInput(0,0) = pars(11);
   TYeInput(0,1) = pars(12);
   TYeInput(0,2) = pars(13);
   TYeInput(1,0) = pars(14);
   TYeInput(1,1) = pars(15);
   TYeInput(1,2) = pars(16);
   TYeInput(2,0) = pars(17);
   TYeInput(2,1) = pars(18);
   TYeInput(2,2) = pars(19);
   TYuInput(0,0) = pars(20);
   TYuInput(0,1) = pars(21);
   TYuInput(0,2) = pars(22);
   TYuInput(1,0) = pars(23);
   TYuInput(1,1) = pars(24);
   TYuInput(1,2) = pars(25);
   TYuInput(2,0) = pars(26);
   TYuInput(2,1) = pars(27);
   TYuInput(2,2) = pars(28);
   BMuInput = pars(29);
   mq2Input(0,0) = pars(30);
   mq2Input(0,1) = pars(31);
   mq2Input(0,2) = pars(32);
   mq2Input(1,0) = pars(33);
   mq2Input(1,1) = pars(34);
   mq2Input(1,2) = pars(35);
   mq2Input(2,0) = pars(36);
   mq2Input(2,1) = pars(37);
   mq2Input(2,2) = pars(38);
   ml2Input(0,0) = pars(39);
   ml2Input(0,1) = pars(40);
   ml2Input(0,2) = pars(41);
   ml2Input(1,0) = pars(42);
   ml2Input(1,1) = pars(43);
   ml2Input(1,2) = pars(44);
   ml2Input(2,0) = pars(45);
   ml2Input(2,1) = pars(46);
   ml2Input(2,2) = pars(47);
   md2Input(0,0) = pars(48);
   md2Input(0,1) = pars(49);
   md2Input(0,2) = pars(50);
   md2Input(1,0) = pars(51);
   md2Input(1,1) = pars(52);
   md2Input(1,2) = pars(53);
   md2Input(2,0) = pars(54);
   md2Input(2,1) = pars(55);
   md2Input(2,2) = pars(56);
   mu2Input(0,0) = pars(57);
   mu2Input(0,1) = pars(58);
   mu2Input(0,2) = pars(59);
   mu2Input(1,0) = pars(60);
   mu2Input(1,1) = pars(61);
   mu2Input(1,2) = pars(62);
   mu2Input(2,0) = pars(63);
   mu2Input(2,1) = pars(64);
   mu2Input(2,2) = pars(65);
   me2Input(0,0) = pars(66);
   me2Input(0,1) = pars(67);
   me2Input(0,2) = pars(68);
   me2Input(1,0) = pars(69);
   me2Input(1,1) = pars(70);
   me2Input(1,2) = pars(71);
   me2Input(2,0) = pars(72);
   me2Input(2,1) = pars(73);
   me2Input(2,2) = pars(74);
   MassBInput = pars(75);
   MassWBInput = pars(76);
   MassGInput = pars(77);

}

std::ostream& operator<<(std::ostream& ostr, const lowMSSM_input_parameters& input)
{
   ostr << "TanBeta = " << INPUT(TanBeta) << ", ";
   ostr << "MuInput = " << INPUT(MuInput) << ", ";
   ostr << "TYdInput = " << INPUT(TYdInput) << ", ";
   ostr << "TYeInput = " << INPUT(TYeInput) << ", ";
   ostr << "TYuInput = " << INPUT(TYuInput) << ", ";
   ostr << "BMuInput = " << INPUT(BMuInput) << ", ";
   ostr << "mq2Input = " << INPUT(mq2Input) << ", ";
   ostr << "ml2Input = " << INPUT(ml2Input) << ", ";
   ostr << "md2Input = " << INPUT(md2Input) << ", ";
   ostr << "mu2Input = " << INPUT(mu2Input) << ", ";
   ostr << "me2Input = " << INPUT(me2Input) << ", ";
   ostr << "MassBInput = " << INPUT(MassBInput) << ", ";
   ostr << "MassWBInput = " << INPUT(MassWBInput) << ", ";
   ostr << "MassGInput = " << INPUT(MassGInput) << ", ";

   return ostr;
}

} // namespace flexiblesusy
