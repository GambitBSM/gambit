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

// File generated at Wed 29 Mar 2017 15:35:53

#ifndef THDM_II_TWO_SCALE_LOW_SCALE_CONSTRAINT_H
#define THDM_II_TWO_SCALE_LOW_SCALE_CONSTRAINT_H

#include "THDM_II_low_scale_constraint.hpp"
#include "THDM_II_input_parameters.hpp"
#include "two_scale_constraint.hpp"
#include "lowe.h"
#include <Eigen/Core>

namespace flexiblesusy {

template <class T>
class THDM_II;

class Two_scale;

template<>
class THDM_II_low_scale_constraint<Two_scale> : public Constraint<Two_scale> {
public:
   THDM_II_low_scale_constraint();
   THDM_II_low_scale_constraint(THDM_II<Two_scale>*, const softsusy::QedQcd&);
   virtual ~THDM_II_low_scale_constraint();
   virtual void apply();
   virtual double get_scale() const;
   virtual void set_model(Two_scale_model*);

   void clear();
   const Eigen::Matrix<std::complex<double>,3,3>& get_ckm();
   const Eigen::Matrix<std::complex<double>,3,3>& get_pmns();
   double get_initial_scale_guess() const;
   void initialize();
   const softsusy::QedQcd& get_sm_parameters() const;
   void set_sm_parameters(const softsusy::QedQcd&);
   void set_threshold_corrections_loop_order(unsigned); ///< threshold corrections loop order

private:
   double scale;
   double initial_scale_guess;
   THDM_II<Two_scale>* model;
   softsusy::QedQcd qedqcd;
   Eigen::Matrix<std::complex<double>,3,3> ckm;
   Eigen::Matrix<std::complex<double>,3,3> pmns;
   Eigen::Matrix<double,3,3> neutrinoDRbar;
   double MWDRbar;
   double MZDRbar;
   double AlphaS;
   double EDRbar;
   double ThetaWDRbar;
   double new_g1, new_g2, new_g3;
   double self_energy_w_at_mw;
   unsigned threshold_corrections_loop_order; ///< threshold corrections loop order

   double calculate_theta_w(double);
   void calculate_threshold_corrections();
   void calculate_DRbar_gauge_couplings();
   void calculate_DRbar_yukawa_couplings();
   void calculate_Yu_DRbar();
   void calculate_Yd_DRbar();
   void calculate_Ye_DRbar();
   void calculate_MNeutrino_DRbar();
   double calculate_delta_alpha_em(double) const;
   double calculate_delta_alpha_s(double) const;
   void recalculate_mw_pole();
   void update_scale();
};

} // namespace flexiblesusy

#endif
