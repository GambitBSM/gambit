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

// File generated at Thu 10 May 2018 15:02:54

#include "NUHMSSM_input_parameters.hpp"
#include "wrappers.hpp"

#define INPUT(p) input.p

namespace flexiblesusy {

Eigen::ArrayXd NUHMSSM_input_parameters::get() const
{
   Eigen::ArrayXd pars(7);

   pars(0) = m0;
   pars(1) = m12;
   pars(2) = TanBeta;
   pars(3) = SignMu;
   pars(4) = Azero;
   pars(5) = mHd2In;
   pars(6) = mHu2In;

   return pars;
}

void NUHMSSM_input_parameters::set(const Eigen::ArrayXd& pars)
{
   m0 = pars(0);
   m12 = pars(1);
   TanBeta = pars(2);
   SignMu = pars(3);
   Azero = pars(4);
   mHd2In = pars(5);
   mHu2In = pars(6);

}

std::ostream& operator<<(std::ostream& ostr, const NUHMSSM_input_parameters& input)
{
   ostr << "m0 = " << INPUT(m0) << ", ";
   ostr << "m12 = " << INPUT(m12) << ", ";
   ostr << "TanBeta = " << INPUT(TanBeta) << ", ";
   ostr << "SignMu = " << INPUT(SignMu) << ", ";
   ostr << "Azero = " << INPUT(Azero) << ", ";
   ostr << "mHd2In = " << INPUT(mHd2In) << ", ";
   ostr << "mHu2In = " << INPUT(mHu2In) << ", ";

   return ostr;
}

} // namespace flexiblesusy
