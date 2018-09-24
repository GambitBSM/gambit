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

// File generated at Thu 10 May 2018 14:43:17

#ifndef SSM_soft_parameters_H
#define SSM_soft_parameters_H

#include "SSM_susy_parameters.hpp"

#include <iosfwd>

namespace flexiblesusy {

#ifdef TRACE_STRUCT_TYPE
   #undef TRACE_STRUCT_TYPE
#endif
#define TRACE_STRUCT_TYPE Soft_traces

class SSM_soft_parameters : public SSM_susy_parameters {
public:
   explicit SSM_soft_parameters(const SSM_input_parameters& input_ = SSM_input_parameters());
   SSM_soft_parameters(const SSM_susy_parameters& , double Kappa_, double K1_, double MS_, double mu2_, double v_, double vS_
);
   SSM_soft_parameters(const SSM_soft_parameters&) = default;
   SSM_soft_parameters(SSM_soft_parameters&&) = default;
   virtual ~SSM_soft_parameters() = default;
   SSM_soft_parameters& operator=(const SSM_soft_parameters&) = default;
   SSM_soft_parameters& operator=(SSM_soft_parameters&&) = default;

   virtual Eigen::ArrayXd beta() const override;
   virtual Eigen::ArrayXd get() const override;
   virtual void print(std::ostream&) const override;
   virtual void set(const Eigen::ArrayXd&) override;

   SSM_soft_parameters calc_beta() const;
   SSM_soft_parameters calc_beta(int) const;
   virtual void clear() override;

   void set_Kappa(double Kappa_) { Kappa = Kappa_; }
   void set_K1(double K1_) { K1 = K1_; }
   void set_MS(double MS_) { MS = MS_; }
   void set_mu2(double mu2_) { mu2 = mu2_; }
   void set_v(double v_) { v = v_; }
   void set_vS(double vS_) { vS = vS_; }

   double get_Kappa() const { return Kappa; }
   double get_K1() const { return K1; }
   double get_MS() const { return MS; }
   double get_mu2() const { return mu2; }
   double get_v() const { return v; }
   double get_vS() const { return vS; }


protected:
   double Kappa{};
   double K1{};
   double MS{};
   double mu2{};
   double v{};
   double vS{};


private:
   static const int numberOfParameters = 39;

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

   double calc_beta_Kappa_1_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_Kappa_2_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_Kappa_3_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_K1_1_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_K1_2_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_K1_3_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_MS_1_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_MS_2_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_MS_3_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_mu2_1_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_mu2_2_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_mu2_3_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_v_1_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_v_2_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_v_3_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_vS_1_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_vS_2_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_vS_3_loop(const TRACE_STRUCT_TYPE&) const;

};

std::ostream& operator<<(std::ostream&, const SSM_soft_parameters&);

} // namespace flexiblesusy

#undef TRACE_STRUCT_TYPE

#endif
