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

// File generated at Wed 4 Apr 2018 09:58:10

#ifndef MDM_soft_parameters_H
#define MDM_soft_parameters_H

#include "MDM_susy_parameters.hpp"

#include <iosfwd>

namespace flexiblesusy {

#ifdef TRACE_STRUCT_TYPE
   #undef TRACE_STRUCT_TYPE
#endif
#define TRACE_STRUCT_TYPE Soft_traces

class MDM_soft_parameters : public MDM_susy_parameters {
public:
   explicit MDM_soft_parameters(const MDM_input_parameters& input_ = MDM_input_parameters());
   MDM_soft_parameters(const MDM_susy_parameters& , double Yc_, double mu2_, double v_
);
   MDM_soft_parameters(const MDM_soft_parameters&) = default;
   MDM_soft_parameters(MDM_soft_parameters&&) = default;
   virtual ~MDM_soft_parameters() = default;
   MDM_soft_parameters& operator=(const MDM_soft_parameters&) = default;
   MDM_soft_parameters& operator=(MDM_soft_parameters&&) = default;

   virtual Eigen::ArrayXd beta() const override;
   virtual Eigen::ArrayXd get() const override;
   virtual void print(std::ostream&) const override;
   virtual void set(const Eigen::ArrayXd&) override;

   MDM_soft_parameters calc_beta() const;
   MDM_soft_parameters calc_beta(int) const;
   virtual void clear() override;

   void set_Yc(double Yc_) { Yc = Yc_; }
   void set_mu2(double mu2_) { mu2 = mu2_; }
   void set_v(double v_) { v = v_; }

   double get_Yc() const { return Yc; }
   double get_mu2() const { return mu2; }
   double get_v() const { return v; }


protected:
   double Yc{};
   double mu2{};
   double v{};


private:
   static const int numberOfParameters = 34;

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

   double calc_beta_Yc_1_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_Yc_2_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_Yc_3_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_mu2_1_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_mu2_2_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_mu2_3_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_v_1_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_v_2_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_v_3_loop(const TRACE_STRUCT_TYPE&) const;

};

std::ostream& operator<<(std::ostream&, const MDM_soft_parameters&);

} // namespace flexiblesusy

#undef TRACE_STRUCT_TYPE

#endif
