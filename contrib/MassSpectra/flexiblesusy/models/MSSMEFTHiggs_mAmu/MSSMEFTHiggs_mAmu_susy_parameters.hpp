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

// File generated at Thu 10 May 2018 14:39:54

#ifndef MSSMEFTHiggs_mAmu_susy_parameters_H
#define MSSMEFTHiggs_mAmu_susy_parameters_H

#include "betafunction.hpp"
#include "MSSMEFTHiggs_mAmu_input_parameters.hpp"

#include <iosfwd>
#include <string>
#include <vector>
#include <Eigen/Core>

namespace flexiblesusy {

#ifdef TRACE_STRUCT_TYPE
   #undef TRACE_STRUCT_TYPE
#endif
#define TRACE_STRUCT_TYPE Susy_traces

class MSSMEFTHiggs_mAmu_susy_parameters : public Beta_function {
public:
   explicit MSSMEFTHiggs_mAmu_susy_parameters(const MSSMEFTHiggs_mAmu_input_parameters& input_ = MSSMEFTHiggs_mAmu_input_parameters());
   MSSMEFTHiggs_mAmu_susy_parameters(double scale_, int loops_, int thresholds_, const MSSMEFTHiggs_mAmu_input_parameters& input_, const Eigen::Matrix<double,3,3>& Yd_, const Eigen::Matrix<double,3,3>& Ye_
   , const Eigen::Matrix<double,3,3>& Yu_, double Mu_, double g1_, double g2_,
   double g3_, double vd_, double vu_
);
   MSSMEFTHiggs_mAmu_susy_parameters(const MSSMEFTHiggs_mAmu_susy_parameters&) = default;
   MSSMEFTHiggs_mAmu_susy_parameters(MSSMEFTHiggs_mAmu_susy_parameters&&) = default;
   virtual ~MSSMEFTHiggs_mAmu_susy_parameters() = default;
   MSSMEFTHiggs_mAmu_susy_parameters& operator=(const MSSMEFTHiggs_mAmu_susy_parameters&) = default;
   MSSMEFTHiggs_mAmu_susy_parameters& operator=(MSSMEFTHiggs_mAmu_susy_parameters&&) = default;

   virtual Eigen::ArrayXd beta() const override;
   virtual Eigen::ArrayXd get() const override;
   virtual void print(std::ostream&) const;
   virtual void set(const Eigen::ArrayXd&) override;
   const MSSMEFTHiggs_mAmu_input_parameters& get_input() const;
   MSSMEFTHiggs_mAmu_input_parameters& get_input();
   void set_input_parameters(const MSSMEFTHiggs_mAmu_input_parameters&);

   MSSMEFTHiggs_mAmu_susy_parameters calc_beta() const;
   MSSMEFTHiggs_mAmu_susy_parameters calc_beta(int) const;
   virtual void clear();

   void set_Yd(const Eigen::Matrix<double,3,3>& Yd_) { Yd = Yd_; }
   void set_Yd(int i, int k, const double& value) { Yd(i,k) = value; }
   void set_Ye(const Eigen::Matrix<double,3,3>& Ye_) { Ye = Ye_; }
   void set_Ye(int i, int k, const double& value) { Ye(i,k) = value; }
   void set_Yu(const Eigen::Matrix<double,3,3>& Yu_) { Yu = Yu_; }
   void set_Yu(int i, int k, const double& value) { Yu(i,k) = value; }
   void set_Mu(double Mu_) { Mu = Mu_; }
   void set_g1(double g1_) { g1 = g1_; }
   void set_g2(double g2_) { g2 = g2_; }
   void set_g3(double g3_) { g3 = g3_; }
   void set_vd(double vd_) { vd = vd_; }
   void set_vu(double vu_) { vu = vu_; }

   const Eigen::Matrix<double,3,3>& get_Yd() const { return Yd; }
   double get_Yd(int i, int k) const { return Yd(i,k); }
   const Eigen::Matrix<double,3,3>& get_Ye() const { return Ye; }
   double get_Ye(int i, int k) const { return Ye(i,k); }
   const Eigen::Matrix<double,3,3>& get_Yu() const { return Yu; }
   double get_Yu(int i, int k) const { return Yu(i,k); }
   double get_Mu() const { return Mu; }
   double get_g1() const { return g1; }
   double get_g2() const { return g2; }
   double get_g3() const { return g3; }
   double get_vd() const { return vd; }
   double get_vu() const { return vu; }

   Eigen::Matrix<double,3,3> get_SqSq() const;
   Eigen::Matrix<double,3,3> get_SlSl() const;
   double get_SHdSHd() const;
   double get_SHuSHu() const;
   Eigen::Matrix<double,3,3> get_SdRSdR() const;
   Eigen::Matrix<double,3,3> get_SuRSuR() const;
   Eigen::Matrix<double,3,3> get_SeRSeR() const;


protected:
   Eigen::Matrix<double,3,3> Yd{Eigen::Matrix<double,3,3>::Zero()};
   Eigen::Matrix<double,3,3> Ye{Eigen::Matrix<double,3,3>::Zero()};
   Eigen::Matrix<double,3,3> Yu{Eigen::Matrix<double,3,3>::Zero()};
   double Mu{};
   double g1{};
   double g2{};
   double g3{};
   double vd{};
   double vu{};

   MSSMEFTHiggs_mAmu_input_parameters input{};

private:
   static const int numberOfParameters = 33;

   struct Susy_traces {
      double traceYdAdjYd{};
      double traceYeAdjYe{};
      double traceYdAdjYdYdAdjYd{};
      double traceYdAdjYuYuAdjYd{};
      double traceYeAdjYeYeAdjYe{};
      double traceYuAdjYu{};
      double traceYuAdjYuYuAdjYu{};

   };
   Susy_traces calc_susy_traces(int) const;

   Eigen::Matrix<double,3,3> calc_beta_Yd_1_loop(const TRACE_STRUCT_TYPE&) const;
   Eigen::Matrix<double,3,3> calc_beta_Yd_2_loop(const TRACE_STRUCT_TYPE&) const;
   Eigen::Matrix<double,3,3> calc_beta_Yd_3_loop(const TRACE_STRUCT_TYPE&) const;
   Eigen::Matrix<double,3,3> calc_beta_Ye_1_loop(const TRACE_STRUCT_TYPE&) const;
   Eigen::Matrix<double,3,3> calc_beta_Ye_2_loop(const TRACE_STRUCT_TYPE&) const;
   Eigen::Matrix<double,3,3> calc_beta_Ye_3_loop(const TRACE_STRUCT_TYPE&) const;
   Eigen::Matrix<double,3,3> calc_beta_Yu_1_loop(const TRACE_STRUCT_TYPE&) const;
   Eigen::Matrix<double,3,3> calc_beta_Yu_2_loop(const TRACE_STRUCT_TYPE&) const;
   Eigen::Matrix<double,3,3> calc_beta_Yu_3_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_Mu_1_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_Mu_2_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_Mu_3_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_g1_1_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_g1_2_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_g1_3_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_g2_1_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_g2_2_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_g2_3_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_g3_1_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_g3_2_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_g3_3_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_vd_1_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_vd_2_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_vd_3_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_vu_1_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_vu_2_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_vu_3_loop(const TRACE_STRUCT_TYPE&) const;

};

std::ostream& operator<<(std::ostream&, const MSSMEFTHiggs_mAmu_susy_parameters&);

#undef TRACE_STRUCT_TYPE

} // namespace flexiblesusy

#endif
