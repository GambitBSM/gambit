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

// File generated at Thu 10 May 2018 14:42:28

#include "SingletDMZ3_input_parameters.hpp"
#include "wrappers.hpp"

#define INPUT(p) input.p

namespace flexiblesusy {

Eigen::ArrayXd SingletDMZ3_input_parameters::get() const
{
   Eigen::ArrayXd pars(7);

   pars(0) = HiggsIN;
   pars(1) = LamSHInput;
   pars(2) = LamSInput;
   pars(3) = muSInput;
   pars(4) = mu3Input;
   pars(5) = QEWSB;
   pars(6) = Qin;

   return pars;
}

void SingletDMZ3_input_parameters::set(const Eigen::ArrayXd& pars)
{
   HiggsIN = pars(0);
   LamSHInput = pars(1);
   LamSInput = pars(2);
   muSInput = pars(3);
   mu3Input = pars(4);
   QEWSB = pars(5);
   Qin = pars(6);

}

std::ostream& operator<<(std::ostream& ostr, const SingletDMZ3_input_parameters& input)
{
   ostr << "HiggsIN = " << INPUT(HiggsIN) << ", ";
   ostr << "LamSHInput = " << INPUT(LamSHInput) << ", ";
   ostr << "LamSInput = " << INPUT(LamSInput) << ", ";
   ostr << "muSInput = " << INPUT(muSInput) << ", ";
   ostr << "mu3Input = " << INPUT(mu3Input) << ", ";
   ostr << "QEWSB = " << INPUT(QEWSB) << ", ";
   ostr << "Qin = " << INPUT(Qin) << ", ";

   return ostr;
}

} // namespace flexiblesusy
