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

// File generated at Thu 10 May 2018 14:28:46

#ifndef MSSMatMGUT_mAmu_soft_parameters_H
#define MSSMatMGUT_mAmu_soft_parameters_H

#include "MSSMatMGUT_mAmu_susy_parameters.hpp"

#include <iosfwd>

namespace flexiblesusy {

#ifdef TRACE_STRUCT_TYPE
   #undef TRACE_STRUCT_TYPE
#endif
#define TRACE_STRUCT_TYPE Soft_traces

class MSSMatMGUT_mAmu_soft_parameters : public MSSMatMGUT_mAmu_susy_parameters {
public:
   explicit MSSMatMGUT_mAmu_soft_parameters(const MSSMatMGUT_mAmu_input_parameters& input_ = MSSMatMGUT_mAmu_input_parameters());
   MSSMatMGUT_mAmu_soft_parameters(const MSSMatMGUT_mAmu_susy_parameters& , const Eigen::Matrix<double,3,3>& TYd_, const Eigen::Matrix<double,3,3>&
   TYe_, const Eigen::Matrix<double,3,3>& TYu_, double BMu_, const
   Eigen::Matrix<double,3,3>& mq2_, const Eigen::Matrix<double,3,3>& ml2_,
   double mHd2_, double mHu2_, const Eigen::Matrix<double,3,3>& md2_, const
   Eigen::Matrix<double,3,3>& mu2_, const Eigen::Matrix<double,3,3>& me2_,
   double MassB_, double MassWB_, double MassG_
);
   MSSMatMGUT_mAmu_soft_parameters(const MSSMatMGUT_mAmu_soft_parameters&) = default;
   MSSMatMGUT_mAmu_soft_parameters(MSSMatMGUT_mAmu_soft_parameters&&) = default;
   virtual ~MSSMatMGUT_mAmu_soft_parameters() = default;
   MSSMatMGUT_mAmu_soft_parameters& operator=(const MSSMatMGUT_mAmu_soft_parameters&) = default;
   MSSMatMGUT_mAmu_soft_parameters& operator=(MSSMatMGUT_mAmu_soft_parameters&&) = default;

   virtual Eigen::ArrayXd beta() const override;
   virtual Eigen::ArrayXd get() const override;
   virtual void print(std::ostream&) const override;
   virtual void set(const Eigen::ArrayXd&) override;

   MSSMatMGUT_mAmu_soft_parameters calc_beta() const;
   MSSMatMGUT_mAmu_soft_parameters calc_beta(int) const;
   virtual void clear() override;

   void set_TYd(const Eigen::Matrix<double,3,3>& TYd_) { TYd = TYd_; }
   void set_TYd(int i, int k, const double& value) { TYd(i,k) = value; }
   void set_TYe(const Eigen::Matrix<double,3,3>& TYe_) { TYe = TYe_; }
   void set_TYe(int i, int k, const double& value) { TYe(i,k) = value; }
   void set_TYu(const Eigen::Matrix<double,3,3>& TYu_) { TYu = TYu_; }
   void set_TYu(int i, int k, const double& value) { TYu(i,k) = value; }
   void set_BMu(double BMu_) { BMu = BMu_; }
   void set_mq2(const Eigen::Matrix<double,3,3>& mq2_) { mq2 = mq2_; }
   void set_mq2(int i, int k, const double& value) { mq2(i,k) = value; }
   void set_ml2(const Eigen::Matrix<double,3,3>& ml2_) { ml2 = ml2_; }
   void set_ml2(int i, int k, const double& value) { ml2(i,k) = value; }
   void set_mHd2(double mHd2_) { mHd2 = mHd2_; }
   void set_mHu2(double mHu2_) { mHu2 = mHu2_; }
   void set_md2(const Eigen::Matrix<double,3,3>& md2_) { md2 = md2_; }
   void set_md2(int i, int k, const double& value) { md2(i,k) = value; }
   void set_mu2(const Eigen::Matrix<double,3,3>& mu2_) { mu2 = mu2_; }
   void set_mu2(int i, int k, const double& value) { mu2(i,k) = value; }
   void set_me2(const Eigen::Matrix<double,3,3>& me2_) { me2 = me2_; }
   void set_me2(int i, int k, const double& value) { me2(i,k) = value; }
   void set_MassB(double MassB_) { MassB = MassB_; }
   void set_MassWB(double MassWB_) { MassWB = MassWB_; }
   void set_MassG(double MassG_) { MassG = MassG_; }

   const Eigen::Matrix<double,3,3>& get_TYd() const { return TYd; }
   double get_TYd(int i, int k) const { return TYd(i,k); }
   const Eigen::Matrix<double,3,3>& get_TYe() const { return TYe; }
   double get_TYe(int i, int k) const { return TYe(i,k); }
   const Eigen::Matrix<double,3,3>& get_TYu() const { return TYu; }
   double get_TYu(int i, int k) const { return TYu(i,k); }
   double get_BMu() const { return BMu; }
   const Eigen::Matrix<double,3,3>& get_mq2() const { return mq2; }
   double get_mq2(int i, int k) const { return mq2(i,k); }
   const Eigen::Matrix<double,3,3>& get_ml2() const { return ml2; }
   double get_ml2(int i, int k) const { return ml2(i,k); }
   double get_mHd2() const { return mHd2; }
   double get_mHu2() const { return mHu2; }
   const Eigen::Matrix<double,3,3>& get_md2() const { return md2; }
   double get_md2(int i, int k) const { return md2(i,k); }
   const Eigen::Matrix<double,3,3>& get_mu2() const { return mu2; }
   double get_mu2(int i, int k) const { return mu2(i,k); }
   const Eigen::Matrix<double,3,3>& get_me2() const { return me2; }
   double get_me2(int i, int k) const { return me2(i,k); }
   double get_MassB() const { return MassB; }
   double get_MassWB() const { return MassWB; }
   double get_MassG() const { return MassG; }


protected:
   Eigen::Matrix<double,3,3> TYd{Eigen::Matrix<double,3,3>::Zero()};
   Eigen::Matrix<double,3,3> TYe{Eigen::Matrix<double,3,3>::Zero()};
   Eigen::Matrix<double,3,3> TYu{Eigen::Matrix<double,3,3>::Zero()};
   double BMu{};
   Eigen::Matrix<double,3,3> mq2{Eigen::Matrix<double,3,3>::Zero()};
   Eigen::Matrix<double,3,3> ml2{Eigen::Matrix<double,3,3>::Zero()};
   double mHd2{};
   double mHu2{};
   Eigen::Matrix<double,3,3> md2{Eigen::Matrix<double,3,3>::Zero()};
   Eigen::Matrix<double,3,3> mu2{Eigen::Matrix<double,3,3>::Zero()};
   Eigen::Matrix<double,3,3> me2{Eigen::Matrix<double,3,3>::Zero()};
   double MassB{};
   double MassWB{};
   double MassG{};


private:
   static const int numberOfParameters = 111;

   struct Soft_traces {
      double traceAdjYdTYd{};
      double traceAdjYeTYe{};
      double traceYdAdjYd{};
      double traceYeAdjYe{};
      double traceYdAdjYdTYdAdjYd{};
      double traceYdAdjYuTYuAdjYd{};
      double traceYeAdjYeTYeAdjYe{};
      double traceYuAdjYdTYdAdjYu{};
      double traceAdjYuTYu{};
      double traceYuAdjYu{};
      double traceYdAdjYdYdAdjYd{};
      double traceYdAdjYuYuAdjYd{};
      double traceYeAdjYeYeAdjYe{};
      double traceAdjYdYd{};
      double traceAdjYeYe{};
      double traceAdjYuYu{};
      double traceTYdAdjYd{};
      double traceTYeAdjYe{};
      double traceTYuAdjYu{};
      double traceAdjYdYdAdjYdYd{};
      double traceAdjYdTYdAdjYdYd{};
      double traceAdjYeYeAdjYeYe{};
      double traceAdjYeTYeAdjYeYe{};
      double traceAdjYuYuAdjYdYd{};
      double traceAdjYuYuAdjYuYu{};
      double traceAdjYuTYuAdjYdYd{};
      double traceAdjYuTYuAdjYuYu{};
      double traceTYdAdjYuYuAdjYd{};
      double traceAdjYdYdAdjYdYdAdjYdYd{};
      double traceAdjYdYdAdjYdTYdAdjYdYd{};
      double traceAdjYeYeAdjYeYeAdjYeYe{};
      double traceAdjYeYeAdjYeTYeAdjYeYe{};
      double traceAdjYuYuAdjYuYuAdjYdYd{};
      double traceAdjYuYuAdjYuTYuAdjYdYd{};
      double traceAdjYuTYuAdjYuYuAdjYdYd{};
      double traceTYdAdjYuYuAdjYuYuAdjYd{};
      double traceYuAdjYuTYuAdjYu{};
      double traceYuAdjYuYuAdjYu{};
      double traceAdjYdYdAdjYuYuAdjYdYd{};
      double traceAdjYdYdAdjYuTYuAdjYdYd{};
      double traceAdjYdTYdAdjYuYuAdjYdYd{};
      double traceAdjYuYuAdjYdTYdAdjYdYd{};
      double traceAdjYuYuAdjYuYuAdjYuYu{};
      double traceAdjYuYuAdjYuTYuAdjYuYu{};
      double traceAdjYdYdAdjYdTYd{};
      double traceAdjYeYeAdjYeTYe{};
      double traceAdjYuYuAdjYdTYd{};
      double traceAdjYuYuAdjYuTYu{};
      double traceAdjYdYdAdjYdYdAdjYdTYd{};
      double traceAdjYdYdAdjYuYuAdjYdTYd{};
      double traceAdjYdTYdAdjYdYdAdjYdYd{};
      double traceAdjYeYeAdjYeYeAdjYeTYe{};
      double traceAdjYeTYeAdjYeYeAdjYeYe{};
      double traceAdjYuYuAdjYuYuAdjYdTYd{};
      double traceAdjYuYuAdjYuYuAdjYuTYu{};
      double traceAdjYuTYuAdjYuYuAdjYuYu{};
      double traceconjTYdTpTYd{};
      double traceconjTYeTpTYe{};
      double tracemd2YdAdjYd{};
      double traceme2YeAdjYe{};
      double traceml2AdjYeYe{};
      double tracemq2AdjYdYd{};
      double traceconjTYdTpYd{};
      double traceconjTYeTpYe{};
      double traceconjTYuTpTYu{};
      double tracemq2AdjYuYu{};
      double tracemu2YuAdjYu{};
      double traceconjTYuTpYu{};
      double tracemd2{};
      double traceme2{};
      double traceml2{};
      double tracemq2{};
      double tracemu2{};
      double traceAdjTYdYd{};
      double traceAdjTYeYe{};
      double traceAdjTYuYu{};
      double traceTYdAdjTYd{};
      double traceTYeAdjTYe{};
      double traceTYuAdjTYu{};
      double traceYdAdjYdmd2{};
      double traceYeAdjYeme2{};
      double traceYuAdjYumu2{};
      double traceAdjYdYdmq2{};
      double traceAdjYeYeml2{};
      double traceAdjYuYumq2{};
      double traceAdjYuYuAdjTYdYd{};
      double traceAdjYuYuAdjTYuYu{};
      double traceAdjYuTYuAdjTYdYd{};
      double traceAdjYuTYuAdjTYuYu{};
      double traceAdjTYdTYdAdjYuYu{};
      double traceAdjTYuYuAdjYdYd{};
      double traceAdjYdYdAdjTYdYd{};
      double traceAdjYeYeAdjTYeYe{};
      double traceAdjTYuTYuAdjYdYd{};
      double traceAdjTYuTYuAdjYuYu{};
      double traceTYdAdjTYuYuAdjYd{};
      double traceYdAdjYuYuAdjYdmd2{};
      double traceYuAdjYdYdAdjYumu2{};
      double traceYuAdjYuYuAdjYumu2{};
      double traceAdjYdYdAdjYuYumq2{};
      double traceAdjYuYuAdjYdYdmq2{};
      double traceAdjYdTYdAdjTYdYd{};
      double traceAdjYeTYeAdjTYeYe{};
      double traceAdjTYdTYdAdjYdYd{};
      double traceAdjTYeTYeAdjYeYe{};
      double traceYdAdjYdYdAdjYdmd2{};
      double traceYeAdjYeYeAdjYeme2{};
      double traceAdjYdYdAdjYdYdmq2{};
      double traceAdjYeYeAdjYeYeml2{};
      double traceAdjYuYuAdjYuYumq2{};
      double traceYdAdjYdTYdAdjTYd{};
      double traceYdAdjYuTYuAdjTYd{};
      double traceYdAdjTYdTYdAdjYd{};
      double traceYdAdjTYuTYuAdjYd{};
      double traceYeAdjYeTYeAdjTYe{};
      double traceYeAdjTYeTYeAdjYe{};
      double traceYuAdjYdTYdAdjTYu{};
      double traceYuAdjTYdTYdAdjYu{};
      double tracemd2YdAdjYdYdAdjYd{};
      double tracemd2YdAdjYuYuAdjYd{};
      double traceme2YeAdjYeYeAdjYe{};
      double traceml2AdjYeYeAdjYeYe{};
      double tracemq2AdjYdYdAdjYdYd{};
      double tracemq2AdjYdYdAdjYuYu{};
      double tracemq2AdjYuYuAdjYdYd{};
      double tracemu2YuAdjYdYdAdjYu{};
      double traceAdjYdYdAdjYdTYdAdjTYdYd{};
      double traceAdjYdYdAdjTYdTYdAdjYdYd{};
      double traceAdjYdTYdAdjYdYdAdjTYdYd{};
      double traceAdjYeYeAdjYeTYeAdjTYeYe{};
      double traceAdjYeYeAdjTYeTYeAdjYeYe{};
      double traceAdjYeTYeAdjYeYeAdjTYeYe{};
      double traceAdjYuYuAdjYuTYuAdjTYdYd{};
      double traceAdjYuYuAdjTYdTYdAdjYuYu{};
      double traceAdjYuYuAdjTYuTYuAdjYdYd{};
      double traceAdjYuTYuAdjYuYuAdjTYdYd{};
      double traceAdjYuTYuAdjTYuYuAdjYdYd{};
      double traceAdjTYuYuAdjYuTYuAdjYdYd{};
      double traceAdjTYuTYuAdjYuYuAdjYdYd{};
      double traceTYdAdjYuYuAdjTYuYuAdjYd{};
      double traceTYdAdjTYuYuAdjYuYuAdjYd{};
      double traceYdAdjYdYdAdjYdYdAdjYdmd2{};
      double traceYdAdjYuYuAdjYuYuAdjYdmd2{};
      double traceYeAdjYeYeAdjYeYeAdjYeme2{};
      double traceYuAdjYdYdAdjYuYuAdjYumu2{};
      double traceYuAdjYuYuAdjYdYdAdjYumu2{};
      double traceAdjYdYdAdjYdYdAdjYdYdmq2{};
      double traceAdjYdYdAdjYuYuAdjYuYumq2{};
      double traceAdjYeYeAdjYeYeAdjYeYeml2{};
      double traceAdjYuYuAdjYdYdAdjYuYumq2{};
      double traceAdjYuYuAdjYuYuAdjYdYdmq2{};
      double traceYuAdjYuTYuAdjTYu{};
      double traceYuAdjTYuTYuAdjYu{};
      double tracemq2AdjYuYuAdjYuYu{};
      double tracemu2YuAdjYuYuAdjYu{};
      double traceAdjYdYdAdjYuTYuAdjTYdYd{};
      double traceAdjYdYdAdjTYuTYuAdjYdYd{};
      double traceAdjYdTYdAdjYuYuAdjTYdYd{};
      double traceAdjYdTYdAdjTYuYuAdjYdYd{};
      double traceAdjYuYuAdjYdTYdAdjTYdYd{};
      double traceAdjYuYuAdjYuTYuAdjTYuYu{};
      double traceAdjYuYuAdjTYdTYdAdjYdYd{};
      double traceAdjYuYuAdjTYuTYuAdjYuYu{};
      double traceAdjYuTYuAdjYdYdAdjTYdYd{};
      double traceAdjYuTYuAdjYuYuAdjTYuYu{};
      double traceAdjTYdTYdAdjYuYuAdjYdYd{};
      double traceAdjTYuYuAdjYdTYdAdjYdYd{};
      double traceYdAdjYdYdAdjYuYuAdjYdmd2{};
      double traceYdAdjYuYuAdjYdYdAdjYdmd2{};
      double traceYuAdjYdYdAdjYdYdAdjYumu2{};
      double traceYuAdjYuYuAdjYuYuAdjYumu2{};
      double traceAdjYdYdAdjYdYdAdjYuYumq2{};
      double traceAdjYdYdAdjYuYuAdjYdYdmq2{};
      double traceAdjYuYuAdjYdYdAdjYdYdmq2{};
      double traceAdjYuYuAdjYuYuAdjYuYumq2{};
      double Tr11{};
      double Tr2U111{};
      double Tr31{};
      double Tr22{};
      double Tr23{};

   };
   Soft_traces calc_soft_traces(int) const;

   Eigen::Matrix<double,3,3> calc_beta_TYd_1_loop(const TRACE_STRUCT_TYPE&) const;
   Eigen::Matrix<double,3,3> calc_beta_TYd_2_loop(const TRACE_STRUCT_TYPE&) const;
   Eigen::Matrix<double,3,3> calc_beta_TYd_3_loop(const TRACE_STRUCT_TYPE&) const;
   Eigen::Matrix<double,3,3> calc_beta_TYe_1_loop(const TRACE_STRUCT_TYPE&) const;
   Eigen::Matrix<double,3,3> calc_beta_TYe_2_loop(const TRACE_STRUCT_TYPE&) const;
   Eigen::Matrix<double,3,3> calc_beta_TYe_3_loop(const TRACE_STRUCT_TYPE&) const;
   Eigen::Matrix<double,3,3> calc_beta_TYu_1_loop(const TRACE_STRUCT_TYPE&) const;
   Eigen::Matrix<double,3,3> calc_beta_TYu_2_loop(const TRACE_STRUCT_TYPE&) const;
   Eigen::Matrix<double,3,3> calc_beta_TYu_3_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_BMu_1_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_BMu_2_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_BMu_3_loop(const TRACE_STRUCT_TYPE&) const;
   Eigen::Matrix<double,3,3> calc_beta_mq2_1_loop(const TRACE_STRUCT_TYPE&) const;
   Eigen::Matrix<double,3,3> calc_beta_mq2_2_loop(const TRACE_STRUCT_TYPE&) const;
   Eigen::Matrix<double,3,3> calc_beta_mq2_3_loop(const TRACE_STRUCT_TYPE&) const;
   Eigen::Matrix<double,3,3> calc_beta_ml2_1_loop(const TRACE_STRUCT_TYPE&) const;
   Eigen::Matrix<double,3,3> calc_beta_ml2_2_loop(const TRACE_STRUCT_TYPE&) const;
   Eigen::Matrix<double,3,3> calc_beta_ml2_3_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_mHd2_1_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_mHd2_2_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_mHd2_3_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_mHu2_1_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_mHu2_2_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_mHu2_3_loop(const TRACE_STRUCT_TYPE&) const;
   Eigen::Matrix<double,3,3> calc_beta_md2_1_loop(const TRACE_STRUCT_TYPE&) const;
   Eigen::Matrix<double,3,3> calc_beta_md2_2_loop(const TRACE_STRUCT_TYPE&) const;
   Eigen::Matrix<double,3,3> calc_beta_md2_3_loop(const TRACE_STRUCT_TYPE&) const;
   Eigen::Matrix<double,3,3> calc_beta_mu2_1_loop(const TRACE_STRUCT_TYPE&) const;
   Eigen::Matrix<double,3,3> calc_beta_mu2_2_loop(const TRACE_STRUCT_TYPE&) const;
   Eigen::Matrix<double,3,3> calc_beta_mu2_3_loop(const TRACE_STRUCT_TYPE&) const;
   Eigen::Matrix<double,3,3> calc_beta_me2_1_loop(const TRACE_STRUCT_TYPE&) const;
   Eigen::Matrix<double,3,3> calc_beta_me2_2_loop(const TRACE_STRUCT_TYPE&) const;
   Eigen::Matrix<double,3,3> calc_beta_me2_3_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_MassB_1_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_MassB_2_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_MassB_3_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_MassWB_1_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_MassWB_2_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_MassWB_3_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_MassG_1_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_MassG_2_loop(const TRACE_STRUCT_TYPE&) const;
   double calc_beta_MassG_3_loop(const TRACE_STRUCT_TYPE&) const;

};

std::ostream& operator<<(std::ostream&, const MSSMatMGUT_mAmu_soft_parameters&);

} // namespace flexiblesusy

#undef TRACE_STRUCT_TYPE

#endif
