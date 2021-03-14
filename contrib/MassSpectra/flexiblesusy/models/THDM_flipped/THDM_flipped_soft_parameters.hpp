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

// File generated at Tue 7 Apr 2020 14:54:56

#ifndef THDM_flipped_soft_parameters_H
#define THDM_flipped_soft_parameters_H

#include "THDM_flipped_susy_parameters.hpp"

#include <iosfwd>

namespace flexiblesusy {

#ifdef TRACE_STRUCT_TYPE
   #undef TRACE_STRUCT_TYPE
#endif
#define TRACE_STRUCT_TYPE Soft_traces

class THDM_flipped_soft_parameters : public THDM_flipped_susy_parameters {
public:
   explicit THDM_flipped_soft_parameters(const THDM_flipped_input_parameters& input_ = THDM_flipped_input_parameters());
   THDM_flipped_soft_parameters(const THDM_flipped_susy_parameters& , double M122_, double M112_, double M222_, double v1_, double v2_
);
   THDM_flipped_soft_parameters(const THDM_flipped_soft_parameters&) = default;
   THDM_flipped_soft_parameters(THDM_flipped_soft_parameters&&) = default;
   virtual ~THDM_flipped_soft_parameters() = default;
   THDM_flipped_soft_parameters& operator=(const THDM_flipped_soft_parameters&) = default;
   THDM_flipped_soft_parameters& operator=(THDM_flipped_soft_parameters&&) = default;

   virtual Eigen::ArrayXd beta() const override;
   virtual Eigen::ArrayXd get() const override;
   virtual void print(std::ostream&) const override;
   virtual void set(const Eigen::ArrayXd&) override;

   THDM_flipped_soft_parameters calc_beta() const;
   THDM_flipped_soft_parameters calc_beta(int) const;
   virtual void clear() override;

   void set_M122(double M122_) { M122 = M122_; }
   void set_M112(double M112_) { M112 = M112_; }
   void set_M222(double M222_) { M222 = M222_; }
   void set_v1(double v1_) { v1 = v1_; }
   void set_v2(double v2_) { v2 = v2_; }

   double get_M122() const { return M122; }
   double get_M112() const { return M112; }
   double get_M222() const { return M222; }
   double get_v1() const { return v1; }
   double get_v2() const { return v2; }


protected:
   double M122{};
   double M112{};
   double M222{};
   double v1{};
   double v2{};


private:
   static const int numberOfParameters = 42;

   struct Soft_traces {
      double traceYdAdjYd{};
      double traceYeAdjYe{};
      double traceYuAdjYu{};
      double traceYdAdjYdYdAdjYd{};
      double traceYdAdjYuYuAdjYd{};
      double traceYeAdjYeYeAdjYe{};
      double traceYuAdjYuYuAdjYu{};

   };
   Soft_traces calc_soft_traces(int) const;

   double calc_beta_M122_1_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_M122_2_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_M122_3_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_M112_1_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_M112_2_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_M112_3_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_M222_1_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_M222_2_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_M222_3_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_v1_1_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_v1_2_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_v1_3_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_v2_1_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_v2_2_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_v2_3_loop(const TRACE_STRUCT_TYPE&) const;

};

std::ostream& operator<<(std::ostream&, const THDM_flipped_soft_parameters&);

} // namespace flexiblesusy

#undef TRACE_STRUCT_TYPE

#endif
