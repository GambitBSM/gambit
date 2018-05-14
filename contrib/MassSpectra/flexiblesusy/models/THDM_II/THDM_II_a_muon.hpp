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

// File generated at Fri 11 May 2018 14:08:42

/**
 * @file THDM_II_a_muon.hpp
 *
 * This file was generated at Fri 11 May 2018 14:08:42 with FlexibleSUSY
 * 2.1.0 and SARAH 4.12.3 .
 */

#ifndef THDM_II_A_MUON_H
#define THDM_II_A_MUON_H

namespace flexiblesusy {
class THDM_II_mass_eigenstates;

namespace THDM_II_a_muon {
/**
* @fn calculate_a_muon
* @brief Calculates \f$a_\mu = (g-2)_\mu/2\f$ of the muon.
*/
double calculate_a_muon(const THDM_II_mass_eigenstates& model);

/**
* @fn calculate_a_muon_uncertainty
* @brief Calculates \f$\Delta a_\mu\f$ of the muon.
*/
double calculate_a_muon_uncertainty(const THDM_II_mass_eigenstates& model);
} // namespace THDM_II_a_muon
} // namespace flexiblesusy

#endif
