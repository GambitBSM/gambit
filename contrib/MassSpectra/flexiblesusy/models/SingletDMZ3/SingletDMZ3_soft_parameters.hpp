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

// File generated at Thu 10 May 2018 14:42:28

#ifndef SingletDMZ3_soft_parameters_H
#define SingletDMZ3_soft_parameters_H

#include "SingletDMZ3_susy_parameters.hpp"

#include <iosfwd>

namespace flexiblesusy {

#ifdef TRACE_STRUCT_TYPE
   #undef TRACE_STRUCT_TYPE
#endif
#define TRACE_STRUCT_TYPE Soft_traces

class SingletDMZ3_soft_parameters : public SingletDMZ3_susy_parameters {
public:
   explicit SingletDMZ3_soft_parameters(const SingletDMZ3_input_parameters& input_ = SingletDMZ3_input_parameters());
   SingletDMZ3_soft_parameters(const SingletDMZ3_susy_parameters& , double mu3_, double muS_, double muH_, double v_
);
   SingletDMZ3_soft_parameters(const SingletDMZ3_soft_parameters&) = default;
   SingletDMZ3_soft_parameters(SingletDMZ3_soft_parameters&&) = default;
   virtual ~SingletDMZ3_soft_parameters() = default;
   SingletDMZ3_soft_parameters& operator=(const SingletDMZ3_soft_parameters&) = default;
   SingletDMZ3_soft_parameters& operator=(SingletDMZ3_soft_parameters&&) = default;

   virtual Eigen::ArrayXd beta() const override;
   virtual Eigen::ArrayXd get() const override;
   virtual void print(std::ostream&) const override;
   virtual void set(const Eigen::ArrayXd&) override;

   SingletDMZ3_soft_parameters calc_beta() const;
   SingletDMZ3_soft_parameters calc_beta(int) const;
   virtual void clear() override;

   void set_mu3(double mu3_) { mu3 = mu3_; }
   void set_muS(double muS_) { muS = muS_; }
   void set_muH(double muH_) { muH = muH_; }
   void set_v(double v_) { v = v_; }

   double get_mu3() const { return mu3; }
   double get_muS() const { return muS; }
   double get_muH() const { return muH; }
   double get_v() const { return v; }


protected:
   double mu3{};
   double muS{};
   double muH{};
   double v{};


private:
   static const int numberOfParameters = 37;

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

   double calc_beta_mu3_1_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_mu3_2_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_mu3_3_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_muS_1_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_muS_2_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_muS_3_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_muH_1_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_muH_2_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_muH_3_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_v_1_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_v_2_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_v_3_loop(const TRACE_STRUCT_TYPE&) const;

};

std::ostream& operator<<(std::ostream&, const SingletDMZ3_soft_parameters&);

} // namespace flexiblesusy

#undef TRACE_STRUCT_TYPE

#endif
