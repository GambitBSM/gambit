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

// File generated at Sat 26 May 2018 14:35:47

/**
 * @file ScalarSingletDM_Z3_two_scale_model.cpp
 * @brief implementation of the ScalarSingletDM_Z3 model class
 *
 * Contains the definition of the ScalarSingletDM_Z3 model class methods
 * which solve EWSB and calculate pole masses and mixings from MSbar
 * parameters.
 *
 * This file was generated at Sat 26 May 2018 14:35:47 with FlexibleSUSY
 * 2.0.1 (git commit: unknown) and SARAH 4.12.2 .
 */

#include "ScalarSingletDM_Z3_two_scale_model.hpp"

namespace flexiblesusy {

#define CLASSNAME ScalarSingletDM_Z3<Two_scale>

CLASSNAME::ScalarSingletDM_Z3(const ScalarSingletDM_Z3_input_parameters& input_)
   : ScalarSingletDM_Z3_mass_eigenstates(input_)
{
}

void CLASSNAME::calculate_spectrum()
{
   ScalarSingletDM_Z3_mass_eigenstates::calculate_spectrum();
}

void CLASSNAME::clear_problems()
{
   ScalarSingletDM_Z3_mass_eigenstates::clear_problems();
}

std::string CLASSNAME::name() const
{
   return ScalarSingletDM_Z3_mass_eigenstates::name();
}

void CLASSNAME::run_to(double scale, double eps)
{
   ScalarSingletDM_Z3_mass_eigenstates::run_to(scale, eps);
}

void CLASSNAME::print(std::ostream& out) const
{
   ScalarSingletDM_Z3_mass_eigenstates::print(out);
}

void CLASSNAME::set_precision(double p)
{
   ScalarSingletDM_Z3_mass_eigenstates::set_precision(p);
}

std::ostream& operator<<(std::ostream& ostr, const ScalarSingletDM_Z3<Two_scale>& model)
{
   model.print(ostr);
   return ostr;
}

} // namespace flexiblesusy
