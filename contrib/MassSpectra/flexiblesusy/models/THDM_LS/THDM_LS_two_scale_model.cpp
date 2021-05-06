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

// File generated at Tue 7 Apr 2020 14:57:43

/**
 * @file THDM_LS_two_scale_model.cpp
 * @brief implementation of the THDM_LS model class
 *
 * Contains the definition of the THDM_LS model class methods
 * which solve EWSB and calculate pole masses and mixings from MSbar
 * parameters.
 *
 * This file was generated at Tue 7 Apr 2020 14:57:43 with FlexibleSUSY
 * 2.0.1 (git commit: unknown) and SARAH 4.13.0 .
 */

#include "THDM_LS_two_scale_model.hpp"

namespace flexiblesusy {

#define CLASSNAME THDM_LS<Two_scale>

CLASSNAME::THDM_LS(const THDM_LS_input_parameters& input_)
   : THDM_LS_mass_eigenstates(input_)
{
}

void CLASSNAME::calculate_spectrum()
{
   THDM_LS_mass_eigenstates::calculate_spectrum();
}

void CLASSNAME::clear_problems()
{
   THDM_LS_mass_eigenstates::clear_problems();
}

std::string CLASSNAME::name() const
{
   return THDM_LS_mass_eigenstates::name();
}

void CLASSNAME::run_to(double scale, double eps)
{
   THDM_LS_mass_eigenstates::run_to(scale, eps);
}

void CLASSNAME::print(std::ostream& out) const
{
   THDM_LS_mass_eigenstates::print(out);
}

void CLASSNAME::set_precision(double p)
{
   THDM_LS_mass_eigenstates::set_precision(p);
}

std::ostream& operator<<(std::ostream& ostr, const THDM_LS<Two_scale>& model)
{
   model.print(ostr);
   return ostr;
}

} // namespace flexiblesusy
