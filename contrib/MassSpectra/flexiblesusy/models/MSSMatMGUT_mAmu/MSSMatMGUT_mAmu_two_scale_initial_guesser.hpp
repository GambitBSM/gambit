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

// File generated at Thu 10 May 2018 14:30:15

#ifndef MSSMatMGUT_mAmu_TWO_SCALE_INITIAL_GUESSER_H
#define MSSMatMGUT_mAmu_TWO_SCALE_INITIAL_GUESSER_H

#include "MSSMatMGUT_mAmu_initial_guesser.hpp"
#include "MSSMatMGUT_mAmu_two_scale_low_scale_constraint.hpp"
#include "MSSMatMGUT_mAmu_two_scale_susy_scale_constraint.hpp"
#include "MSSMatMGUT_mAmu_two_scale_high_scale_constraint.hpp"
#include "initial_guesser.hpp"

#include <sstream>

namespace flexiblesusy {

template <class T>
class MSSMatMGUT_mAmu;

class Two_scale;

/**
 * @class MSSMatMGUT_mAmu_initial_guesser<Two_scale>
 * @brief initial guesser for the MSSMatMGUT_mAmu
 */

template<>
class MSSMatMGUT_mAmu_initial_guesser<Two_scale> : public Initial_guesser {
public:
   MSSMatMGUT_mAmu_initial_guesser(MSSMatMGUT_mAmu<Two_scale>*,
                               const softsusy::QedQcd&,
                               const MSSMatMGUT_mAmu_low_scale_constraint<Two_scale>&,
                               const MSSMatMGUT_mAmu_susy_scale_constraint<Two_scale>&,
                               const MSSMatMGUT_mAmu_high_scale_constraint<Two_scale>&);
   virtual ~MSSMatMGUT_mAmu_initial_guesser() = default;

   virtual void guess() override; ///< initial guess

   void set_running_precision(double p) { running_precision = p; }

private:
   MSSMatMGUT_mAmu<Two_scale>* model{nullptr}; ///< pointer to model class
   softsusy::QedQcd qedqcd{};       ///< Standard Model low-energy data
   double mu_guess{0.}; ///< guessed DR-bar mass of up-quark
   double mc_guess{0.}; ///< guessed DR-bar mass of charm-quark
   double mt_guess{0.}; ///< guessed DR-bar mass of top-quark
   double md_guess{0.}; ///< guessed DR-bar mass of down-quark
   double ms_guess{0.}; ///< guessed DR-bar mass of strange-quark
   double mb_guess{0.}; ///< guessed DR-bar mass of bottom-quark
   double me_guess{0.}; ///< guessed DR-bar mass of electron
   double mm_guess{0.}; ///< guessed DR-bar mass of muon
   double mtau_guess{0.}; ///< guessed DR-bar mass of tau
   double running_precision{1.0e-3}; ///< Runge-Kutta RG running precision
   MSSMatMGUT_mAmu_low_scale_constraint<Two_scale> low_constraint{};
   MSSMatMGUT_mAmu_susy_scale_constraint<Two_scale> susy_constraint{};
   MSSMatMGUT_mAmu_high_scale_constraint<Two_scale> high_constraint{};

   void guess_susy_parameters();
   void guess_soft_parameters();
   void calculate_DRbar_yukawa_couplings();
   void calculate_Yu_DRbar();
   void calculate_Yd_DRbar();
   void calculate_Ye_DRbar();
};

} // namespace flexiblesusy

#endif
