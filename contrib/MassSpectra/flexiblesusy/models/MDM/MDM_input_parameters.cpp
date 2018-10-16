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

// File generated at Wed 4 Apr 2018 09:58:12

#include "MDM_input_parameters.hpp"
#include "wrappers.hpp"

#define INPUT(p) input.p

namespace flexiblesusy {

Eigen::ArrayXd MDM_input_parameters::get() const
{
   Eigen::ArrayXd pars(4);

   pars(0) = HiggsIN;
   pars(1) = YcIN;
   pars(2) = Qin;
   pars(3) = QEWSB;

   return pars;
}

void MDM_input_parameters::set(const Eigen::ArrayXd& pars)
{
   HiggsIN = pars(0);
   YcIN = pars(1);
   Qin = pars(2);
   QEWSB = pars(3);

}

std::ostream& operator<<(std::ostream& ostr, const MDM_input_parameters& input)
{
   ostr << "HiggsIN = " << INPUT(HiggsIN) << ", ";
   ostr << "YcIN = " << INPUT(YcIN) << ", ";
   ostr << "Qin = " << INPUT(Qin) << ", ";
   ostr << "QEWSB = " << INPUT(QEWSB) << ", ";

   return ostr;
}

} // namespace flexiblesusy
