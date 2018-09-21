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

// File generated at Thu 10 May 2018 14:59:12

#include "MSSMNoFV_input_parameters.hpp"
#include "wrappers.hpp"

#define INPUT(p) input.p

namespace flexiblesusy {

Eigen::ArrayXd MSSMNoFV_input_parameters::get() const
{
   Eigen::ArrayXd pars(32);

   pars(0) = TanBeta;
   pars(1) = SignMu;
   pars(2) = Qin;
   pars(3) = M1;
   pars(4) = M2;
   pars(5) = M3;
   pars(6) = AtIN;
   pars(7) = AbIN;
   pars(8) = AtauIN;
   pars(9) = AcIN;
   pars(10) = AsIN;
   pars(11) = AmuonIN;
   pars(12) = AuIN;
   pars(13) = AdIN;
   pars(14) = AeIN;
   pars(15) = mHd2IN;
   pars(16) = mHu2IN;
   pars(17) = ml11IN;
   pars(18) = ml22IN;
   pars(19) = ml33IN;
   pars(20) = me11IN;
   pars(21) = me22IN;
   pars(22) = me33IN;
   pars(23) = mq11IN;
   pars(24) = mq22IN;
   pars(25) = mq33IN;
   pars(26) = mu11IN;
   pars(27) = mu22IN;
   pars(28) = mu33IN;
   pars(29) = md11IN;
   pars(30) = md22IN;
   pars(31) = md33IN;

   return pars;
}

void MSSMNoFV_input_parameters::set(const Eigen::ArrayXd& pars)
{
   TanBeta = pars(0);
   SignMu = pars(1);
   Qin = pars(2);
   M1 = pars(3);
   M2 = pars(4);
   M3 = pars(5);
   AtIN = pars(6);
   AbIN = pars(7);
   AtauIN = pars(8);
   AcIN = pars(9);
   AsIN = pars(10);
   AmuonIN = pars(11);
   AuIN = pars(12);
   AdIN = pars(13);
   AeIN = pars(14);
   mHd2IN = pars(15);
   mHu2IN = pars(16);
   ml11IN = pars(17);
   ml22IN = pars(18);
   ml33IN = pars(19);
   me11IN = pars(20);
   me22IN = pars(21);
   me33IN = pars(22);
   mq11IN = pars(23);
   mq22IN = pars(24);
   mq33IN = pars(25);
   mu11IN = pars(26);
   mu22IN = pars(27);
   mu33IN = pars(28);
   md11IN = pars(29);
   md22IN = pars(30);
   md33IN = pars(31);

}

std::ostream& operator<<(std::ostream& ostr, const MSSMNoFV_input_parameters& input)
{
   ostr << "TanBeta = " << INPUT(TanBeta) << ", ";
   ostr << "SignMu = " << INPUT(SignMu) << ", ";
   ostr << "Qin = " << INPUT(Qin) << ", ";
   ostr << "M1 = " << INPUT(M1) << ", ";
   ostr << "M2 = " << INPUT(M2) << ", ";
   ostr << "M3 = " << INPUT(M3) << ", ";
   ostr << "AtIN = " << INPUT(AtIN) << ", ";
   ostr << "AbIN = " << INPUT(AbIN) << ", ";
   ostr << "AtauIN = " << INPUT(AtauIN) << ", ";
   ostr << "AcIN = " << INPUT(AcIN) << ", ";
   ostr << "AsIN = " << INPUT(AsIN) << ", ";
   ostr << "AmuonIN = " << INPUT(AmuonIN) << ", ";
   ostr << "AuIN = " << INPUT(AuIN) << ", ";
   ostr << "AdIN = " << INPUT(AdIN) << ", ";
   ostr << "AeIN = " << INPUT(AeIN) << ", ";
   ostr << "mHd2IN = " << INPUT(mHd2IN) << ", ";
   ostr << "mHu2IN = " << INPUT(mHu2IN) << ", ";
   ostr << "ml11IN = " << INPUT(ml11IN) << ", ";
   ostr << "ml22IN = " << INPUT(ml22IN) << ", ";
   ostr << "ml33IN = " << INPUT(ml33IN) << ", ";
   ostr << "me11IN = " << INPUT(me11IN) << ", ";
   ostr << "me22IN = " << INPUT(me22IN) << ", ";
   ostr << "me33IN = " << INPUT(me33IN) << ", ";
   ostr << "mq11IN = " << INPUT(mq11IN) << ", ";
   ostr << "mq22IN = " << INPUT(mq22IN) << ", ";
   ostr << "mq33IN = " << INPUT(mq33IN) << ", ";
   ostr << "mu11IN = " << INPUT(mu11IN) << ", ";
   ostr << "mu22IN = " << INPUT(mu22IN) << ", ";
   ostr << "mu33IN = " << INPUT(mu33IN) << ", ";
   ostr << "md11IN = " << INPUT(md11IN) << ", ";
   ostr << "md22IN = " << INPUT(md22IN) << ", ";
   ostr << "md33IN = " << INPUT(md33IN) << ", ";

   return ostr;
}

} // namespace flexiblesusy
