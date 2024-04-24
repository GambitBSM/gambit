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

// File generated at Wed 29 Mar 2017 15:35:50

#include "THDM_II_input_parameters.hpp"
#include "wrappers.hpp"

#define INPUT(p) input.p

namespace flexiblesusy {

Eigen::ArrayXd THDM_II_input_parameters::get() const
{
   Eigen::ArrayXd pars(11);

   pars(0) = Lambda1IN;
   pars(1) = Lambda2IN;
   pars(2) = Lambda3IN;
   pars(3) = Lambda4IN;
   pars(4) = Lambda5IN;
   pars(5) = Lambda6IN;
   pars(6) = Lambda7IN;
   pars(7) = M122IN;
   pars(8) = TanBeta;
   pars(9) = Qin;
   pars(10) = QEWSB;

   return pars;
}

void THDM_II_input_parameters::set(const Eigen::ArrayXd& pars)
{
   Lambda1IN = pars(0);
   Lambda2IN = pars(1);
   Lambda3IN = pars(2);
   Lambda4IN = pars(3);
   Lambda5IN = pars(4);
   Lambda6IN = pars(5);
   Lambda7IN = pars(6);
   M122IN = pars(7);
   TanBeta = pars(8);
   Qin = pars(9);
   QEWSB = pars(10);

}

std::ostream& operator<<(std::ostream& ostr, const THDM_II_input_parameters& input)
{
   ostr << "Lambda1IN = " << INPUT(Lambda1IN) << ", ";
   ostr << "Lambda2IN = " << INPUT(Lambda2IN) << ", ";
   ostr << "Lambda3IN = " << INPUT(Lambda3IN) << ", ";
   ostr << "Lambda4IN = " << INPUT(Lambda4IN) << ", ";
   ostr << "Lambda5IN = " << INPUT(Lambda5IN) << ", ";
   ostr << "Lambda6IN = " << INPUT(Lambda6IN) << ", ";
   ostr << "Lambda7IN = " << INPUT(Lambda7IN) << ", ";
   ostr << "M122IN = " << INPUT(M122IN) << ", ";
   ostr << "TanBeta = " << INPUT(TanBeta) << ", ";
   ostr << "Qin = " << INPUT(Qin) << ", ";
   ostr << "QEWSB = " << INPUT(QEWSB) << ", ";

   return ostr;
}

} // namespace flexiblesusy
