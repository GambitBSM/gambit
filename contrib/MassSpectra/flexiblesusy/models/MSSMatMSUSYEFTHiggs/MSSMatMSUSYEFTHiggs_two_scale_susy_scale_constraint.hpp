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

// File generated at Thu 10 May 2018 14:39:10

#ifndef MSSMatMSUSYEFTHiggs_TWO_SCALE_SUSY_SCALE_CONSTRAINT_H
#define MSSMatMSUSYEFTHiggs_TWO_SCALE_SUSY_SCALE_CONSTRAINT_H

#include "MSSMatMSUSYEFTHiggs_susy_scale_constraint.hpp"
#include "MSSMatMSUSYEFTHiggs_input_parameters.hpp"
#include "single_scale_constraint.hpp"
#include "lowe.h"

namespace flexiblesusy {

template <class T>
class MSSMatMSUSYEFTHiggs;

class Two_scale;

template<>
class MSSMatMSUSYEFTHiggs_susy_scale_constraint<Two_scale> : public Single_scale_constraint {
public:
   MSSMatMSUSYEFTHiggs_susy_scale_constraint() = default;
   MSSMatMSUSYEFTHiggs_susy_scale_constraint(MSSMatMSUSYEFTHiggs<Two_scale>*, const softsusy::QedQcd&);
   virtual ~MSSMatMSUSYEFTHiggs_susy_scale_constraint() = default;
   virtual void apply() override;
   virtual double get_scale() const override;
   virtual std::string name() const override { return "MSSMatMSUSYEFTHiggs SUSY-scale constraint"; }
   virtual void set_model(Model*) override;

   void clear();
   double get_initial_scale_guess() const;
   const MSSMatMSUSYEFTHiggs_input_parameters& get_input_parameters() const;
   MSSMatMSUSYEFTHiggs<Two_scale>* get_model() const;
   void initialize();
   const softsusy::QedQcd& get_sm_parameters() const;
   void set_sm_parameters(const softsusy::QedQcd&);

protected:
   void update_scale();

private:
   double scale{0.};
   double initial_scale_guess{0.};
   MSSMatMSUSYEFTHiggs<Two_scale>* model{nullptr};
   softsusy::QedQcd qedqcd{};

   void check_model_ptr() const;
};

} // namespace flexiblesusy

#endif
