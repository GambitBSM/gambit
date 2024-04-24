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

// File generated at Tue 7 Apr 2020 02:34:05

#ifndef THDM_I_TWO_SCALE_HIGH_SCALE_CONSTRAINT_H
#define THDM_I_TWO_SCALE_HIGH_SCALE_CONSTRAINT_H

#include "THDM_I_high_scale_constraint.hpp"
#include "THDM_I_input_parameters.hpp"
#include "single_scale_constraint.hpp"

namespace flexiblesusy {

template <class T>
class THDM_I;

class Two_scale;

template<>
class THDM_I_high_scale_constraint<Two_scale> : public Single_scale_constraint {
public:
   THDM_I_high_scale_constraint() = default;
   THDM_I_high_scale_constraint(THDM_I<Two_scale>*);
   virtual ~THDM_I_high_scale_constraint() = default;
   virtual void apply() override;
   virtual double get_scale() const override;
   virtual std::string name() const override { return "THDM_I high-scale constraint"; }
   virtual void set_model(Model*) override;

   void clear();
   double get_initial_scale_guess() const;
   const THDM_I_input_parameters& get_input_parameters() const;
   THDM_I<Two_scale>* get_model() const;
   void initialize();
   void set_scale(double); ///< fix unification scale (0 = unfixed)

protected:
   void update_scale();
   bool check_non_perturbative();

private:
   double scale{0.};
   double initial_scale_guess{0.};
   THDM_I<Two_scale>* model{nullptr};

   void check_model_ptr() const;
};

} // namespace flexiblesusy

#endif
