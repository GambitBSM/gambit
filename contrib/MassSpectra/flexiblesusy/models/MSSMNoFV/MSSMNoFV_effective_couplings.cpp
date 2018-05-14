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

// File generated at Thu 10 May 2018 15:00:14

#include "MSSMNoFV_effective_couplings.hpp"

#include "effective_couplings.hpp"
#include "wrappers.hpp"

namespace flexiblesusy {

using namespace effective_couplings;

#define INPUTPARAMETER(parameter) model.get_input().parameter
#define MODELPARAMETER(parameter) model.get_##parameter()
#define DERIVEDPARAMETER(parameter) model.##parameter()
#define PHASE(parameter) model.get_##parameter()
#define PHYSICAL(parameter) model.get_physical().parameter

MSSMNoFV_effective_couplings::MSSMNoFV_effective_couplings(
   const MSSMNoFV_mass_eigenstates& model_,
   const softsusy::QedQcd& qedqcd_,
   const Physical_input& input_)
   : model(model_), qedqcd(qedqcd_), physical_input(input_)
   , rg_improve(true), include_qcd_corrections(true)
   , ZD(MODELPARAMETER(ZD)), ZU(MODELPARAMETER(ZU)), ZE(MODELPARAMETER(ZE)), ZM
      (MODELPARAMETER(ZM)), ZTau(MODELPARAMETER(ZTau)), ZS(MODELPARAMETER(ZS)), ZC
      (MODELPARAMETER(ZC)), ZB(MODELPARAMETER(ZB)), ZT(MODELPARAMETER(ZT)), ZH(
      MODELPARAMETER(ZH)), ZA(MODELPARAMETER(ZA)), ZP(MODELPARAMETER(ZP)), ZN(
      MODELPARAMETER(ZN)), UM(MODELPARAMETER(UM)), UP(MODELPARAMETER(UP)), ZZ(
      MODELPARAMETER(ZZ))

   , eff_CphhVPVP(Eigen::Array<std::complex<double>,2,1>::Zero()), eff_CphhVGVG
      (Eigen::Array<std::complex<double>,2,1>::Zero()), eff_CpAhVPVP(Eigen::Array<
      std::complex<double>,2,1>::Zero()), eff_CpAhVGVG(Eigen::Array<std::complex<
      double>,2,1>::Zero())

{
}

void MSSMNoFV_effective_couplings::calculate_effective_couplings()
{
   const standard_model::Standard_model sm(initialise_SM());

   const double scale = model.get_scale();
   const Eigen::ArrayXd saved_parameters(model.get());

   const double saved_mt = PHYSICAL(MFt);
   PHYSICAL(MFt) = qedqcd.displayPoleMt();

   const auto Mhh = PHYSICAL(Mhh);
   for (int gO1 = 0; gO1 < 2; ++gO1) {
      if (rg_improve && scale > Mhh(gO1)) {
         model.run_to(Mhh(gO1));
      }
      model.calculate_DRbar_masses();
      copy_mixing_matrices_from_model();
      run_SM_strong_coupling_to(sm, 0.5 * Mhh(gO1));
      calculate_eff_CphhVPVP(gO1);
      run_SM_strong_coupling_to(sm, Mhh(gO1));
      calculate_eff_CphhVGVG(gO1);
   }

   const auto MAh = PHYSICAL(MAh);
   for (int gO1 = 1; gO1 < 2; ++gO1) {
      if (rg_improve && scale > MAh(gO1)) {
         model.run_to(MAh(gO1));
      }
      model.calculate_DRbar_masses();
      copy_mixing_matrices_from_model();
      run_SM_strong_coupling_to(sm, 0.5 * MAh(gO1));
      calculate_eff_CpAhVPVP(gO1);
      run_SM_strong_coupling_to(sm, MAh(gO1));
      calculate_eff_CpAhVGVG(gO1);
   }

   PHYSICAL(MFt) = saved_mt;
   model.set_scale(scale);
   model.set(saved_parameters);

}

void MSSMNoFV_effective_couplings::set_model(const MSSMNoFV_mass_eigenstates& model_)
{
   model = model_;
   copy_mixing_matrices_from_model();
}

void MSSMNoFV_effective_couplings::copy_mixing_matrices_from_model()
{
   ZD = MODELPARAMETER(ZD);
   ZU = MODELPARAMETER(ZU);
   ZE = MODELPARAMETER(ZE);
   ZM = MODELPARAMETER(ZM);
   ZTau = MODELPARAMETER(ZTau);
   ZS = MODELPARAMETER(ZS);
   ZC = MODELPARAMETER(ZC);
   ZB = MODELPARAMETER(ZB);
   ZT = MODELPARAMETER(ZT);
   ZH = MODELPARAMETER(ZH);
   ZA = MODELPARAMETER(ZA);
   ZP = MODELPARAMETER(ZP);
   ZN = MODELPARAMETER(ZN);
   UM = MODELPARAMETER(UM);
   UP = MODELPARAMETER(UP);
   ZZ = MODELPARAMETER(ZZ);

}

standard_model::Standard_model MSSMNoFV_effective_couplings::initialise_SM() const
{
   standard_model::Standard_model sm;

   sm.set_loops(2);
   sm.set_thresholds(2);
   sm.set_physical_input(physical_input);

   sm.initialise_from_input(qedqcd);

   return sm;
}

void MSSMNoFV_effective_couplings::run_SM_strong_coupling_to(standard_model::Standard_model sm, double m)
{
   sm.run_to(m);

   model.set_g3(sm.get_g3());

}

std::complex<double> MSSMNoFV_effective_couplings::scalar_scalar_qcd_factor(double m_decay, double m_loop) const
{
   std::complex<double> result(1.0, 0.0);

   if (include_qcd_corrections) {
      const auto g3 = MODELPARAMETER(g3);
      if (m_loop > m_decay) {
         result = 1 + 0.06754745576155852*Sqr(g3);
      }

   }

   return result;
}

std::complex<double> MSSMNoFV_effective_couplings::scalar_fermion_qcd_factor(double m_decay, double m_loop) const
{
   std::complex<double> result(1.0, 0.0);

   if (include_qcd_corrections) {
      const auto g3 = MODELPARAMETER(g3);
      result = 1.0 + 0.025330295910584444*Sqr(g3) *
         scalar_diphoton_fermion_loop(m_decay, m_loop);

   }

   return result;
}

std::complex<double> MSSMNoFV_effective_couplings::pseudoscalar_fermion_qcd_factor(double m_decay, double m_loop) const
{
   std::complex<double> result(1.0, 0.0);

   if (include_qcd_corrections) {
      const auto g3 = MODELPARAMETER(g3);
      result = 1.0 + 0.025330295910584444*Sqr(g3) *
         pseudoscalar_diphoton_fermion_loop(m_decay, m_loop);

   }

   return result;
}

double MSSMNoFV_effective_couplings::number_of_active_flavours(double m) const
{
   if (m < qedqcd.displayMbMb()) {
      return 4.0;
   } else if (m < qedqcd.displayPoleMt()) {
      return 5.0;
   } else {
      return 6.0;
   }
}

double MSSMNoFV_effective_couplings::scalar_scaling_factor(double m) const
{
   const double Nf = number_of_active_flavours(m);
   const double mtpole = qedqcd.displayPoleMt();
   const double l = Log(Sqr(m) / Sqr(mtpole));

   const auto g3 = MODELPARAMETER(g3);

   const double nlo_qcd = 0.025330295910584444*(23.75 - 1.1666666666666667*Nf)*
      Sqr(g3);
   const double nnlo_qcd = 0.000641623890917771*Quad(g3)*(370.1956513893174 +
      2.375*l + (-47.18640261449638 + 0.6666666666666666*l)*Nf +
      0.9017702481178881*Sqr(Nf));
   const double nnnlo_qcd = 0.000016252523020247696*Power6(g3)*(467.683620788 +
      122.440972222*l + 10.9409722222*Sqr(l));

   return Sqrt(1.0 + nlo_qcd + nnlo_qcd + nnnlo_qcd);
}

double MSSMNoFV_effective_couplings::pseudoscalar_scaling_factor(double m) const
{
   const double Nf = number_of_active_flavours(m);
   const double mtpole = qedqcd.displayPoleMt();
   const double l = Log(Sqr(m) / Sqr(mtpole));

   const auto g3 = MODELPARAMETER(g3);

   const double nlo_qcd = 0.025330295910584444*(24.25 - 1.1666666666666667*Nf)*
      Sqr(g3);
   const double nnlo_qcd = 0.000641623890917771*(171.54400563089382 + 5*l)*Quad
      (g3);
   const double nnnlo_qcd = 0;

   return Sqrt(1.0 + nlo_qcd + nnlo_qcd + nnnlo_qcd);
}

double MSSMNoFV_effective_couplings::get_hhVPVP_partial_width(int gO1) const
{
   const double mass = PHYSICAL(Mhh)(gO1);
   return 0.0049735919716217296 * Power(mass, 3.0) * AbsSqr(eff_CphhVPVP(gO1));
}

double MSSMNoFV_effective_couplings::get_hhVGVG_partial_width(int gO1) const
{
   const double mass = PHYSICAL(Mhh)(gO1);
   return 0.039788735772973836 * Power(mass, 3.0) * AbsSqr(eff_CphhVGVG(gO1));
}

double MSSMNoFV_effective_couplings::get_AhVPVP_partial_width(int gO1) const
{
   const double mass = PHYSICAL(MAh)(gO1);
   return 0.0049735919716217296 * Power(mass, 3.0) * AbsSqr(eff_CpAhVPVP(gO1));
}

double MSSMNoFV_effective_couplings::get_AhVGVG_partial_width(int gO1) const
{
   const double mass = PHYSICAL(MAh)(gO1);
   return 0.039788735772973836 * Power(mass, 3.0) * AbsSqr(eff_CpAhVGVG(gO1));
}

std::complex<double> MSSMNoFV_effective_couplings::CphhconjVWmVWm(int gI2) const
{
   const auto g2 = MODELPARAMETER(g2);
   const auto vd = MODELPARAMETER(vd);
   const auto vu = MODELPARAMETER(vu);

   const std::complex<double> result = 0.5*Sqr(g2)*(vd*ZH(gI2,0) + vu*ZH(gI2,1)
      );

   return result;
}

std::complex<double> MSSMNoFV_effective_couplings::CpbarFdFdhhPL(int gI1) const
{
   const auto Yd = MODELPARAMETER(Yd);

   const std::complex<double> result = -0.7071067811865475*Yd(0,0)*ZH(gI1,0);

   return result;
}

std::complex<double> MSSMNoFV_effective_couplings::CpbarFdFdAhPL(int gI2) const
{
   const auto Yd = MODELPARAMETER(Yd);

   const std::complex<double> result = std::complex<double>(0.,
      -0.7071067811865475)*Yd(0,0)*ZA(gI2,0);

   return result;
}

std::complex<double> MSSMNoFV_effective_couplings::CpbarFsFshhPL(int gI1) const
{
   const auto Yd = MODELPARAMETER(Yd);

   const std::complex<double> result = -0.7071067811865475*Yd(1,1)*ZH(gI1,0);

   return result;
}

std::complex<double> MSSMNoFV_effective_couplings::CpbarFsFsAhPL(int gI2) const
{
   const auto Yd = MODELPARAMETER(Yd);

   const std::complex<double> result = std::complex<double>(0.,
      -0.7071067811865475)*Yd(1,1)*ZA(gI2,0);

   return result;
}

std::complex<double> MSSMNoFV_effective_couplings::CpbarFbFbhhPL(int gI1) const
{
   const auto Yd = MODELPARAMETER(Yd);

   const std::complex<double> result = -0.7071067811865475*Yd(2,2)*ZH(gI1,0);

   return result;
}

std::complex<double> MSSMNoFV_effective_couplings::CpbarFbFbAhPL(int gI2) const
{
   const auto Yd = MODELPARAMETER(Yd);

   const std::complex<double> result = std::complex<double>(0.,
      -0.7071067811865475)*Yd(2,2)*ZA(gI2,0);

   return result;
}

std::complex<double> MSSMNoFV_effective_couplings::CpbarFuFuhhPL(int gI1) const
{
   const auto Yu = MODELPARAMETER(Yu);

   const std::complex<double> result = -0.7071067811865475*Yu(0,0)*ZH(gI1,1);

   return result;
}

std::complex<double> MSSMNoFV_effective_couplings::CpbarFuFuAhPL(int gI2) const
{
   const auto Yu = MODELPARAMETER(Yu);

   const std::complex<double> result = std::complex<double>(0.,
      -0.7071067811865475)*Yu(0,0)*ZA(gI2,1);

   return result;
}

std::complex<double> MSSMNoFV_effective_couplings::CpbarFcFchhPL(int gI1) const
{
   const auto Yu = MODELPARAMETER(Yu);

   const std::complex<double> result = -0.7071067811865475*Yu(1,1)*ZH(gI1,1);

   return result;
}

std::complex<double> MSSMNoFV_effective_couplings::CpbarFcFcAhPL(int gI2) const
{
   const auto Yu = MODELPARAMETER(Yu);

   const std::complex<double> result = std::complex<double>(0.,
      -0.7071067811865475)*Yu(1,1)*ZA(gI2,1);

   return result;
}

std::complex<double> MSSMNoFV_effective_couplings::CpbarFtFthhPL(int gI1) const
{
   const auto Yu = MODELPARAMETER(Yu);

   const std::complex<double> result = -0.7071067811865475*Yu(2,2)*ZH(gI1,1);

   return result;
}

std::complex<double> MSSMNoFV_effective_couplings::CpbarFtFtAhPL(int gI2) const
{
   const auto Yu = MODELPARAMETER(Yu);

   const std::complex<double> result = std::complex<double>(0.,
      -0.7071067811865475)*Yu(2,2)*ZA(gI2,1);

   return result;
}

std::complex<double> MSSMNoFV_effective_couplings::CpbarFeFehhPL(int gI1) const
{
   const auto Ye = MODELPARAMETER(Ye);

   const std::complex<double> result = -0.7071067811865475*Ye(0,0)*ZH(gI1,0);

   return result;
}

std::complex<double> MSSMNoFV_effective_couplings::CpbarFeFeAhPL(int gI2) const
{
   const auto Ye = MODELPARAMETER(Ye);

   const std::complex<double> result = std::complex<double>(0.,
      -0.7071067811865475)*Ye(0,0)*ZA(gI2,0);

   return result;
}

std::complex<double> MSSMNoFV_effective_couplings::CpbarFmFmhhPL(int gI1) const
{
   const auto Ye = MODELPARAMETER(Ye);

   const std::complex<double> result = -0.7071067811865475*Ye(1,1)*ZH(gI1,0);

   return result;
}

std::complex<double> MSSMNoFV_effective_couplings::CpbarFmFmAhPL(int gI2) const
{
   const auto Ye = MODELPARAMETER(Ye);

   const std::complex<double> result = std::complex<double>(0.,
      -0.7071067811865475)*Ye(1,1)*ZA(gI2,0);

   return result;
}

std::complex<double> MSSMNoFV_effective_couplings::CpbarFtauFtauhhPL(int gI1) const
{
   const auto Ye = MODELPARAMETER(Ye);

   const std::complex<double> result = -0.7071067811865475*Ye(2,2)*ZH(gI1,0);

   return result;
}

std::complex<double> MSSMNoFV_effective_couplings::CpbarFtauFtauAhPL(int gI2) const
{
   const auto Ye = MODELPARAMETER(Ye);

   const std::complex<double> result = std::complex<double>(0.,
      -0.7071067811865475)*Ye(2,2)*ZA(gI2,0);

   return result;
}

std::complex<double> MSSMNoFV_effective_couplings::CphhSdconjSd(int gt1, int gt2, int gt3) const
{
   const auto TYd = MODELPARAMETER(TYd);
   const auto g1 = MODELPARAMETER(g1);
   const auto g2 = MODELPARAMETER(g2);
   const auto vd = MODELPARAMETER(vd);
   const auto vu = MODELPARAMETER(vu);
   const auto Yd = MODELPARAMETER(Yd);
   const auto Mu = MODELPARAMETER(Mu);

   const std::complex<double> result = 0.05*(-2*Conj(ZD(gt2,1))*(
      7.0710678118654755*Conj(TYd(0,0))*ZD(gt3,0)*ZH(gt1,0) - 7.0710678118654755*
      Conj(Yd(0,0))*Mu*ZD(gt3,0)*ZH(gt1,1) + ZD(gt3,1)*(-(vd*(-10*AbsSqr(Yd(0,0))
      + Sqr(g1))*ZH(gt1,0)) + vu*Sqr(g1)*ZH(gt1,1))) + Conj(ZD(gt2,0))*(ZD(gt3,0)*
      (vd*(-20*AbsSqr(Yd(0,0)) + Sqr(g1) + 5*Sqr(g2))*ZH(gt1,0) - vu*(Sqr(g1) + 5*
      Sqr(g2))*ZH(gt1,1)) + 14.142135623730951*ZD(gt3,1)*(Conj(Mu)*Yd(0,0)*ZH(gt1,
      1) - ZH(gt1,0)*TYd(0,0))));

   return result;
}

std::complex<double> MSSMNoFV_effective_couplings::CphhSuconjSu(int gt1, int gt2, int gt3) const
{
   const auto TYu = MODELPARAMETER(TYu);
   const auto g1 = MODELPARAMETER(g1);
   const auto g2 = MODELPARAMETER(g2);
   const auto vd = MODELPARAMETER(vd);
   const auto vu = MODELPARAMETER(vu);
   const auto Yu = MODELPARAMETER(Yu);
   const auto Mu = MODELPARAMETER(Mu);

   const std::complex<double> result = 0.05*(2*Conj(ZU(gt2,1))*(
      -7.0710678118654755*Conj(TYu(0,0))*ZH(gt1,1)*ZU(gt3,0) + 2*Sqr(g1)*(-(vd*ZH(
      gt1,0)) + vu*ZH(gt1,1))*ZU(gt3,1) + 5*Conj(Yu(0,0))*(1.4142135623730951*Mu*
      ZH(gt1,0)*ZU(gt3,0) - 2*vu*Yu(0,0)*ZH(gt1,1)*ZU(gt3,1))) + Conj(ZU(gt2,0))*(
      ZH(gt1,0)*(vd*(Sqr(g1) - 5*Sqr(g2))*ZU(gt3,0) + 14.142135623730951*Conj(Mu)*
      Yu(0,0)*ZU(gt3,1)) - ZH(gt1,1)*(vu*(20*AbsSqr(Yu(0,0)) + Sqr(g1) - 5*Sqr(g2)
      )*ZU(gt3,0) + 14.142135623730951*ZU(gt3,1)*TYu(0,0))));

   return result;
}

std::complex<double> MSSMNoFV_effective_couplings::CphhSeconjSe(int gt1, int gt2, int gt3) const
{
   const auto TYe = MODELPARAMETER(TYe);
   const auto g1 = MODELPARAMETER(g1);
   const auto g2 = MODELPARAMETER(g2);
   const auto vd = MODELPARAMETER(vd);
   const auto vu = MODELPARAMETER(vu);
   const auto Ye = MODELPARAMETER(Ye);
   const auto Mu = MODELPARAMETER(Mu);

   const std::complex<double> result = 0.05*(-2*Conj(ZE(gt2,1))*(
      7.0710678118654755*Conj(TYe(0,0))*ZE(gt3,0)*ZH(gt1,0) - 7.0710678118654755*
      Conj(Ye(0,0))*Mu*ZE(gt3,0)*ZH(gt1,1) + ZE(gt3,1)*((10*vd*AbsSqr(Ye(0,0)) - 3
      *vd*Sqr(g1))*ZH(gt1,0) + 3*vu*Sqr(g1)*ZH(gt1,1))) + Conj(ZE(gt2,0))*(ZE(gt3,
      0)*(vd*(-20*AbsSqr(Ye(0,0)) - 3*Sqr(g1) + 5*Sqr(g2))*ZH(gt1,0) + vu*(3*Sqr(
      g1) - 5*Sqr(g2))*ZH(gt1,1)) + 14.142135623730951*ZE(gt3,1)*(Conj(Mu)*Ye(0,0)
      *ZH(gt1,1) - ZH(gt1,0)*TYe(0,0))));

   return result;
}

std::complex<double> MSSMNoFV_effective_couplings::CphhSmconjSm(int gt1, int gt2, int gt3) const
{
   const auto TYe = MODELPARAMETER(TYe);
   const auto g1 = MODELPARAMETER(g1);
   const auto g2 = MODELPARAMETER(g2);
   const auto vd = MODELPARAMETER(vd);
   const auto vu = MODELPARAMETER(vu);
   const auto Ye = MODELPARAMETER(Ye);
   const auto Mu = MODELPARAMETER(Mu);

   const std::complex<double> result = 0.25*(-2*Conj(ZM(gt2,1))*(
      1.4142135623730951*Conj(TYe(1,1))*ZH(gt1,0)*ZM(gt3,0) + 0.6*Sqr(g1)*(-(vd*ZH
      (gt1,0)) + vu*ZH(gt1,1))*ZM(gt3,1) + Conj(Ye(1,1))*(-1.4142135623730951*Mu*
      ZH(gt1,1)*ZM(gt3,0) + 2*vd*Ye(1,1)*ZH(gt1,0)*ZM(gt3,1))) + Conj(ZM(gt2,0))*(
      ZH(gt1,1)*(vu*(0.6*Sqr(g1) - Sqr(g2))*ZM(gt3,0) + 2.8284271247461903*Conj(Mu
      )*Ye(1,1)*ZM(gt3,1)) - ZH(gt1,0)*(vd*(4*AbsSqr(Ye(1,1)) + 0.6*Sqr(g1) - Sqr(
      g2))*ZM(gt3,0) + 2.8284271247461903*ZM(gt3,1)*TYe(1,1))));

   return result;
}

std::complex<double> MSSMNoFV_effective_couplings::CphhStauconjStau(int gt1, int gt2, int gt3) const
{
   const auto TYe = MODELPARAMETER(TYe);
   const auto g1 = MODELPARAMETER(g1);
   const auto g2 = MODELPARAMETER(g2);
   const auto vd = MODELPARAMETER(vd);
   const auto vu = MODELPARAMETER(vu);
   const auto Ye = MODELPARAMETER(Ye);
   const auto Mu = MODELPARAMETER(Mu);

   const std::complex<double> result = 0.25*(-2*Conj(ZTau(gt2,1))*(
      1.4142135623730951*Conj(TYe(2,2))*ZH(gt1,0)*ZTau(gt3,0) + 0.6*Sqr(g1)*(-(vd*
      ZH(gt1,0)) + vu*ZH(gt1,1))*ZTau(gt3,1) + Conj(Ye(2,2))*(-1.4142135623730951*
      Mu*ZH(gt1,1)*ZTau(gt3,0) + 2*vd*Ye(2,2)*ZH(gt1,0)*ZTau(gt3,1))) + Conj(ZTau(
      gt2,0))*(ZH(gt1,1)*(vu*(0.6*Sqr(g1) - Sqr(g2))*ZTau(gt3,0) +
      2.8284271247461903*Conj(Mu)*Ye(2,2)*ZTau(gt3,1)) - ZH(gt1,0)*(vd*(4*AbsSqr(
      Ye(2,2)) + 0.6*Sqr(g1) - Sqr(g2))*ZTau(gt3,0) + 2.8284271247461903*ZTau(gt3,
      1)*TYe(2,2))));

   return result;
}

std::complex<double> MSSMNoFV_effective_couplings::CphhSsconjSs(int gt1, int gt2, int gt3) const
{
   const auto TYd = MODELPARAMETER(TYd);
   const auto g1 = MODELPARAMETER(g1);
   const auto g2 = MODELPARAMETER(g2);
   const auto vd = MODELPARAMETER(vd);
   const auto vu = MODELPARAMETER(vu);
   const auto Yd = MODELPARAMETER(Yd);
   const auto Mu = MODELPARAMETER(Mu);

   const std::complex<double> result = 0.05*(-2*Conj(ZS(gt2,1))*(
      7.0710678118654755*Conj(TYd(1,1))*ZH(gt1,0)*ZS(gt3,0) + Sqr(g1)*(-(vd*ZH(gt1
      ,0)) + vu*ZH(gt1,1))*ZS(gt3,1) - 5*Conj(Yd(1,1))*(1.4142135623730951*Mu*ZH(
      gt1,1)*ZS(gt3,0) - 2*vd*Yd(1,1)*ZH(gt1,0)*ZS(gt3,1))) + Conj(ZS(gt2,0))*(-(
      ZH(gt1,1)*(vu*(Sqr(g1) + 5*Sqr(g2))*ZS(gt3,0) - 14.142135623730951*Conj(Mu)*
      Yd(1,1)*ZS(gt3,1))) + ZH(gt1,0)*(vd*(-20*AbsSqr(Yd(1,1)) + Sqr(g1) + 5*Sqr(
      g2))*ZS(gt3,0) - 14.142135623730951*ZS(gt3,1)*TYd(1,1))));

   return result;
}

std::complex<double> MSSMNoFV_effective_couplings::CphhScconjSc(int gt1, int gt2, int gt3) const
{
   const auto TYu = MODELPARAMETER(TYu);
   const auto g1 = MODELPARAMETER(g1);
   const auto g2 = MODELPARAMETER(g2);
   const auto vd = MODELPARAMETER(vd);
   const auto vu = MODELPARAMETER(vu);
   const auto Yu = MODELPARAMETER(Yu);
   const auto Mu = MODELPARAMETER(Mu);

   const std::complex<double> result = 0.05*(2*Conj(ZC(gt2,1))*(
      -7.0710678118654755*Conj(TYu(1,1))*ZC(gt3,0)*ZH(gt1,1) + 2*Sqr(g1)*ZC(gt3,1)
      *(-(vd*ZH(gt1,0)) + vu*ZH(gt1,1)) + 5*Conj(Yu(1,1))*(1.4142135623730951*Mu*
      ZC(gt3,0)*ZH(gt1,0) - 2*vu*Yu(1,1)*ZC(gt3,1)*ZH(gt1,1))) + Conj(ZC(gt2,0))*(
      ZC(gt3,0)*(vd*(Sqr(g1) - 5*Sqr(g2))*ZH(gt1,0) - vu*(20*AbsSqr(Yu(1,1)) + Sqr
      (g1) - 5*Sqr(g2))*ZH(gt1,1)) + 14.142135623730951*ZC(gt3,1)*(Conj(Mu)*Yu(1,1
      )*ZH(gt1,0) - ZH(gt1,1)*TYu(1,1))));

   return result;
}

std::complex<double> MSSMNoFV_effective_couplings::CphhSbconjSb(int gt1, int gt2, int gt3) const
{
   const auto TYd = MODELPARAMETER(TYd);
   const auto g1 = MODELPARAMETER(g1);
   const auto g2 = MODELPARAMETER(g2);
   const auto vd = MODELPARAMETER(vd);
   const auto vu = MODELPARAMETER(vu);
   const auto Yd = MODELPARAMETER(Yd);
   const auto Mu = MODELPARAMETER(Mu);

   const std::complex<double> result = 0.05*(-2*Conj(ZB(gt2,1))*(
      7.0710678118654755*Conj(TYd(2,2))*ZB(gt3,0)*ZH(gt1,0) - 7.0710678118654755*
      Conj(Yd(2,2))*Mu*ZB(gt3,0)*ZH(gt1,1) + ZB(gt3,1)*(-(vd*(-10*AbsSqr(Yd(2,2))
      + Sqr(g1))*ZH(gt1,0)) + vu*Sqr(g1)*ZH(gt1,1))) + Conj(ZB(gt2,0))*(ZB(gt3,0)*
      (vd*(-20*AbsSqr(Yd(2,2)) + Sqr(g1) + 5*Sqr(g2))*ZH(gt1,0) - vu*(Sqr(g1) + 5*
      Sqr(g2))*ZH(gt1,1)) + 14.142135623730951*ZB(gt3,1)*(Conj(Mu)*Yd(2,2)*ZH(gt1,
      1) - ZH(gt1,0)*TYd(2,2))));

   return result;
}

std::complex<double> MSSMNoFV_effective_couplings::CphhStconjSt(int gt1, int gt2, int gt3) const
{
   const auto TYu = MODELPARAMETER(TYu);
   const auto g1 = MODELPARAMETER(g1);
   const auto g2 = MODELPARAMETER(g2);
   const auto vd = MODELPARAMETER(vd);
   const auto vu = MODELPARAMETER(vu);
   const auto Yu = MODELPARAMETER(Yu);
   const auto Mu = MODELPARAMETER(Mu);

   const std::complex<double> result = 0.05*(2*Conj(ZT(gt2,1))*(
      -7.0710678118654755*Conj(TYu(2,2))*ZH(gt1,1)*ZT(gt3,0) + 2*Sqr(g1)*(-(vd*ZH(
      gt1,0)) + vu*ZH(gt1,1))*ZT(gt3,1) + 5*Conj(Yu(2,2))*(1.4142135623730951*Mu*
      ZH(gt1,0)*ZT(gt3,0) - 2*vu*Yu(2,2)*ZH(gt1,1)*ZT(gt3,1))) + Conj(ZT(gt2,0))*(
      ZH(gt1,0)*(vd*(Sqr(g1) - 5*Sqr(g2))*ZT(gt3,0) + 14.142135623730951*Conj(Mu)*
      Yu(2,2)*ZT(gt3,1)) - ZH(gt1,1)*(vu*(20*AbsSqr(Yu(2,2)) + Sqr(g1) - 5*Sqr(g2)
      )*ZT(gt3,0) + 14.142135623730951*ZT(gt3,1)*TYu(2,2))));

   return result;
}

std::complex<double> MSSMNoFV_effective_couplings::CphhHpmconjHpm(int gt1, int gt2, int gt3) const
{
   const auto g1 = MODELPARAMETER(g1);
   const auto g2 = MODELPARAMETER(g2);
   const auto vd = MODELPARAMETER(vd);
   const auto vu = MODELPARAMETER(vu);

   const std::complex<double> result = 0.25*(-(ZH(gt1,0)*(ZP(gt2,0)*(vd*(0.6*
      Sqr(g1) + Sqr(g2))*ZP(gt3,0) + vu*Sqr(g2)*ZP(gt3,1)) + ZP(gt2,1)*(vu*Sqr(g2)
      *ZP(gt3,0) + vd*(-0.6*Sqr(g1) + Sqr(g2))*ZP(gt3,1)))) + ZH(gt1,1)*(ZP(gt2,0)
      *(vu*(0.6*Sqr(g1) - Sqr(g2))*ZP(gt3,0) - vd*Sqr(g2)*ZP(gt3,1)) - ZP(gt2,1)*(
      vd*Sqr(g2)*ZP(gt3,0) + vu*(0.6*Sqr(g1) + Sqr(g2))*ZP(gt3,1))));

   return result;
}

std::complex<double> MSSMNoFV_effective_couplings::CpbarChaChahhPL(int gt3, int gt1, int gt2) const
{
   const auto g2 = MODELPARAMETER(g2);

   const std::complex<double> result = -0.7071067811865475*g2*(Conj(UM(gt1,1))*
      Conj(UP(gt3,0))*ZH(gt2,0) + Conj(UM(gt1,0))*Conj(UP(gt3,1))*ZH(gt2,1));

   return result;
}

std::complex<double> MSSMNoFV_effective_couplings::CpAhSdconjSd(int gt1, int gt2, int gt3) const
{
   const auto TYd = MODELPARAMETER(TYd);
   const auto Yd = MODELPARAMETER(Yd);
   const auto Mu = MODELPARAMETER(Mu);

   const std::complex<double> result = std::complex<double>(0.,
      0.7071067811865475)*(Conj(ZD(gt2,1))*(Conj(TYd(0,0))*ZA(gt1,0) + Conj(Yd(0,0
      ))*Mu*ZA(gt1,1))*ZD(gt3,0) - Conj(ZD(gt2,0))*ZD(gt3,1)*(Conj(Mu)*Yd(0,0)*ZA(
      gt1,1) + ZA(gt1,0)*TYd(0,0)));

   return result;
}

std::complex<double> MSSMNoFV_effective_couplings::CpAhSuconjSu(int gt1, int gt2, int gt3) const
{
   const auto TYu = MODELPARAMETER(TYu);
   const auto Yu = MODELPARAMETER(Yu);
   const auto Mu = MODELPARAMETER(Mu);

   const std::complex<double> result = std::complex<double>(0.,
      0.7071067811865475)*(Conj(Yu(0,0))*Conj(ZU(gt2,1))*Mu*ZA(gt1,0)*ZU(gt3,0) +
      Conj(ZU(gt2,1))*Conj(TYu(0,0))*ZA(gt1,1)*ZU(gt3,0) - Conj(ZU(gt2,0))*ZU(gt3,
      1)*(Conj(Mu)*Yu(0,0)*ZA(gt1,0) + ZA(gt1,1)*TYu(0,0)));

   return result;
}

std::complex<double> MSSMNoFV_effective_couplings::CpAhSeconjSe(int gt1, int gt2, int gt3) const
{
   const auto TYe = MODELPARAMETER(TYe);
   const auto Ye = MODELPARAMETER(Ye);
   const auto Mu = MODELPARAMETER(Mu);

   const std::complex<double> result = std::complex<double>(0.,
      0.7071067811865475)*(Conj(ZE(gt2,1))*(Conj(TYe(0,0))*ZA(gt1,0) + Conj(Ye(0,0
      ))*Mu*ZA(gt1,1))*ZE(gt3,0) - Conj(ZE(gt2,0))*ZE(gt3,1)*(Conj(Mu)*Ye(0,0)*ZA(
      gt1,1) + ZA(gt1,0)*TYe(0,0)));

   return result;
}

std::complex<double> MSSMNoFV_effective_couplings::CpAhSmconjSm(int gt1, int gt2, int gt3) const
{
   const auto TYe = MODELPARAMETER(TYe);
   const auto Ye = MODELPARAMETER(Ye);
   const auto Mu = MODELPARAMETER(Mu);

   const std::complex<double> result = std::complex<double>(0.,
      0.7071067811865475)*(Conj(ZM(gt2,1))*(Conj(TYe(1,1))*ZA(gt1,0) + Conj(Ye(1,1
      ))*Mu*ZA(gt1,1))*ZM(gt3,0) - Conj(ZM(gt2,0))*ZM(gt3,1)*(Conj(Mu)*Ye(1,1)*ZA(
      gt1,1) + ZA(gt1,0)*TYe(1,1)));

   return result;
}

std::complex<double> MSSMNoFV_effective_couplings::CpAhStauconjStau(int gt1, int gt2, int gt3) const
{
   const auto TYe = MODELPARAMETER(TYe);
   const auto Ye = MODELPARAMETER(Ye);
   const auto Mu = MODELPARAMETER(Mu);

   const std::complex<double> result = std::complex<double>(0.,
      0.7071067811865475)*(Conj(ZTau(gt2,1))*(Conj(TYe(2,2))*ZA(gt1,0) + Conj(Ye(2
      ,2))*Mu*ZA(gt1,1))*ZTau(gt3,0) - Conj(ZTau(gt2,0))*ZTau(gt3,1)*(Conj(Mu)*Ye(
      2,2)*ZA(gt1,1) + ZA(gt1,0)*TYe(2,2)));

   return result;
}

std::complex<double> MSSMNoFV_effective_couplings::CpAhSsconjSs(int gt1, int gt2, int gt3) const
{
   const auto TYd = MODELPARAMETER(TYd);
   const auto Yd = MODELPARAMETER(Yd);
   const auto Mu = MODELPARAMETER(Mu);

   const std::complex<double> result = std::complex<double>(0.,
      0.7071067811865475)*(Conj(ZS(gt2,1))*(Conj(TYd(1,1))*ZA(gt1,0) + Conj(Yd(1,1
      ))*Mu*ZA(gt1,1))*ZS(gt3,0) - Conj(ZS(gt2,0))*ZS(gt3,1)*(Conj(Mu)*Yd(1,1)*ZA(
      gt1,1) + ZA(gt1,0)*TYd(1,1)));

   return result;
}

std::complex<double> MSSMNoFV_effective_couplings::CpAhScconjSc(int gt1, int gt2, int gt3) const
{
   const auto TYu = MODELPARAMETER(TYu);
   const auto Yu = MODELPARAMETER(Yu);
   const auto Mu = MODELPARAMETER(Mu);

   const std::complex<double> result = std::complex<double>(0.,
      0.7071067811865475)*(Conj(Yu(1,1))*Conj(ZC(gt2,1))*Mu*ZA(gt1,0)*ZC(gt3,0) +
      Conj(ZC(gt2,1))*Conj(TYu(1,1))*ZA(gt1,1)*ZC(gt3,0) - Conj(ZC(gt2,0))*ZC(gt3,
      1)*(Conj(Mu)*Yu(1,1)*ZA(gt1,0) + ZA(gt1,1)*TYu(1,1)));

   return result;
}

std::complex<double> MSSMNoFV_effective_couplings::CpAhSbconjSb(int gt1, int gt2, int gt3) const
{
   const auto TYd = MODELPARAMETER(TYd);
   const auto Yd = MODELPARAMETER(Yd);
   const auto Mu = MODELPARAMETER(Mu);

   const std::complex<double> result = std::complex<double>(0.,
      0.7071067811865475)*(Conj(ZB(gt2,1))*(Conj(TYd(2,2))*ZA(gt1,0) + Conj(Yd(2,2
      ))*Mu*ZA(gt1,1))*ZB(gt3,0) - Conj(ZB(gt2,0))*ZB(gt3,1)*(Conj(Mu)*Yd(2,2)*ZA(
      gt1,1) + ZA(gt1,0)*TYd(2,2)));

   return result;
}

std::complex<double> MSSMNoFV_effective_couplings::CpAhStconjSt(int gt1, int gt2, int gt3) const
{
   const auto TYu = MODELPARAMETER(TYu);
   const auto Yu = MODELPARAMETER(Yu);
   const auto Mu = MODELPARAMETER(Mu);

   const std::complex<double> result = std::complex<double>(0.,
      0.7071067811865475)*(Conj(Yu(2,2))*Conj(ZT(gt2,1))*Mu*ZA(gt1,0)*ZT(gt3,0) +
      Conj(ZT(gt2,1))*Conj(TYu(2,2))*ZA(gt1,1)*ZT(gt3,0) - Conj(ZT(gt2,0))*ZT(gt3,
      1)*(Conj(Mu)*Yu(2,2)*ZA(gt1,0) + ZA(gt1,1)*TYu(2,2)));

   return result;
}

std::complex<double> MSSMNoFV_effective_couplings::CpAhHpmconjHpm(int gt1, int gt2, int gt3) const
{
   const auto g2 = MODELPARAMETER(g2);
   const auto vd = MODELPARAMETER(vd);
   const auto vu = MODELPARAMETER(vu);

   const std::complex<double> result = std::complex<double>(0,-0.25)*Sqr(g2)*(
      vu*ZA(gt1,0) + vd*ZA(gt1,1))*(ZP(gt2,1)*ZP(gt3,0) - ZP(gt2,0)*ZP(gt3,1));

   return result;
}

std::complex<double> MSSMNoFV_effective_couplings::CpbarChaChaAhPL(int gt3, int gt2, int gt1) const
{
   const auto g2 = MODELPARAMETER(g2);

   const std::complex<double> result = std::complex<double>(0.,
      0.7071067811865475)*g2*(Conj(UM(gt2,1))*Conj(UP(gt3,0))*ZA(gt1,0) + Conj(UM(
      gt2,0))*Conj(UP(gt3,1))*ZA(gt1,1));

   return result;
}

void MSSMNoFV_effective_couplings::calculate_eff_CphhVPVP(int gO1)
{
   const auto vd = MODELPARAMETER(vd);
   const auto vu = MODELPARAMETER(vu);
   const auto MFd = MODELPARAMETER(MFd);
   const auto MFs = MODELPARAMETER(MFs);
   const auto MFb = MODELPARAMETER(MFb);
   const auto MFu = MODELPARAMETER(MFu);
   const auto MFc = MODELPARAMETER(MFc);
   const auto MFt = MODELPARAMETER(MFt);
   const auto MFe = MODELPARAMETER(MFe);
   const auto MFm = MODELPARAMETER(MFm);
   const auto MFtau = MODELPARAMETER(MFtau);
   const auto MSd = MODELPARAMETER(MSd);
   const auto MSu = MODELPARAMETER(MSu);
   const auto MSe = MODELPARAMETER(MSe);
   const auto MSm = MODELPARAMETER(MSm);
   const auto MStau = MODELPARAMETER(MStau);
   const auto MSs = MODELPARAMETER(MSs);
   const auto MSc = MODELPARAMETER(MSc);
   const auto MSb = MODELPARAMETER(MSb);
   const auto MSt = MODELPARAMETER(MSt);
   const auto MHpm = MODELPARAMETER(MHpm);
   const auto MCha = MODELPARAMETER(MCha);
   const auto MVWm = MODELPARAMETER(MVWm);
   const auto decay_mass = PHYSICAL(Mhh)(gO1);
   const auto decay_scale = 0.25 * Sqr(decay_mass);
   const auto saved_ZH = ZH;
   ZH = PHYSICAL(ZH);

   const auto vev = Sqrt(Sqr(vd) + Sqr(vu));

   std::complex<double> result = 0;
   result += 0.3333333333333333 * scalar_fermion_qcd_factor(decay_mass, MFd) *
      CpbarFdFdhhPL(gO1) * vev * AS12(decay_scale / Sqr(MFd)) / MFd;
   result += 0.3333333333333333 * scalar_fermion_qcd_factor(decay_mass, MFs) *
      CpbarFsFshhPL(gO1) * vev * AS12(decay_scale / Sqr(MFs)) / MFs;
   result += 0.3333333333333333 * scalar_fermion_qcd_factor(decay_mass, MFb) *
      CpbarFbFbhhPL(gO1) * vev * AS12(decay_scale / Sqr(MFb)) / MFb;
   result += 1.3333333333333333 * scalar_fermion_qcd_factor(decay_mass, MFu) *
      CpbarFuFuhhPL(gO1) * vev * AS12(decay_scale / Sqr(MFu)) / MFu;
   result += 1.3333333333333333 * scalar_fermion_qcd_factor(decay_mass, MFc) *
      CpbarFcFchhPL(gO1) * vev * AS12(decay_scale / Sqr(MFc)) / MFc;
   result += 1.3333333333333333 * scalar_fermion_qcd_factor(decay_mass, MFt) *
      CpbarFtFthhPL(gO1) * vev * AS12(decay_scale / Sqr(MFt)) / MFt;
   result += CpbarFeFehhPL(gO1) * vev * AS12(decay_scale / Sqr(MFe)) / MFe;
   result += CpbarFmFmhhPL(gO1) * vev * AS12(decay_scale / Sqr(MFm)) / MFm;
   result += CpbarFtauFtauhhPL(gO1) * vev * AS12(decay_scale / Sqr(MFtau)) /
      MFtau;
   for (int gI1 = 0; gI1 < 2; ++gI1) {
      result += 0.16666666666666666 * scalar_scalar_qcd_factor(decay_mass,
         MSd(gI1)) * CphhSdconjSd(gO1, gI1, gI1) * vev * AS0(decay_scale / Sqr(MSd
         (gI1))) / Sqr(MSd(gI1));
   }
   for (int gI1 = 0; gI1 < 2; ++gI1) {
      result += 0.6666666666666666 * scalar_scalar_qcd_factor(decay_mass,
         MSu(gI1)) * CphhSuconjSu(gO1, gI1, gI1) * vev * AS0(decay_scale / Sqr(MSu
         (gI1))) / Sqr(MSu(gI1));
   }
   for (int gI1 = 0; gI1 < 2; ++gI1) {
      result += 0.5 * CphhSeconjSe(gO1, gI1, gI1) * vev * AS0(decay_scale /
         Sqr(MSe(gI1))) / Sqr(MSe(gI1));
   }
   for (int gI1 = 0; gI1 < 2; ++gI1) {
      result += 0.5 * CphhSmconjSm(gO1, gI1, gI1) * vev * AS0(decay_scale /
         Sqr(MSm(gI1))) / Sqr(MSm(gI1));
   }
   for (int gI1 = 0; gI1 < 2; ++gI1) {
      result += 0.5 * CphhStauconjStau(gO1, gI1, gI1) * vev * AS0(
         decay_scale / Sqr(MStau(gI1))) / Sqr(MStau(gI1));
   }
   for (int gI1 = 0; gI1 < 2; ++gI1) {
      result += 0.16666666666666666 * scalar_scalar_qcd_factor(decay_mass,
         MSs(gI1)) * CphhSsconjSs(gO1, gI1, gI1) * vev * AS0(decay_scale / Sqr(MSs
         (gI1))) / Sqr(MSs(gI1));
   }
   for (int gI1 = 0; gI1 < 2; ++gI1) {
      result += 0.6666666666666666 * scalar_scalar_qcd_factor(decay_mass,
         MSc(gI1)) * CphhScconjSc(gO1, gI1, gI1) * vev * AS0(decay_scale / Sqr(MSc
         (gI1))) / Sqr(MSc(gI1));
   }
   for (int gI1 = 0; gI1 < 2; ++gI1) {
      result += 0.16666666666666666 * scalar_scalar_qcd_factor(decay_mass,
         MSb(gI1)) * CphhSbconjSb(gO1, gI1, gI1) * vev * AS0(decay_scale / Sqr(MSb
         (gI1))) / Sqr(MSb(gI1));
   }
   for (int gI1 = 0; gI1 < 2; ++gI1) {
      result += 0.6666666666666666 * scalar_scalar_qcd_factor(decay_mass,
         MSt(gI1)) * CphhStconjSt(gO1, gI1, gI1) * vev * AS0(decay_scale / Sqr(MSt
         (gI1))) / Sqr(MSt(gI1));
   }
   for (int gI1 = 1; gI1 < 2; ++gI1) {
      result += 0.5 * CphhHpmconjHpm(gO1, gI1, gI1) * vev * AS0(decay_scale
         / Sqr(MHpm(gI1))) / Sqr(MHpm(gI1));
   }
   for (int gI1 = 0; gI1 < 2; ++gI1) {
      result += CpbarChaChahhPL(gI1, gI1, gO1) * vev * AS12(decay_scale /
         Sqr(MCha(gI1))) / MCha(gI1);
   }
   result += -0.5 * CphhconjVWmVWm(gO1) * vev * AS1(decay_scale / Sqr(MVWm)) /
      Sqr(MVWm);

   result *= 0.1892681907127351 * physical_input.get(Physical_input::alpha_em_0
      ) * Sqrt(qedqcd.displayFermiConstant());

   ZH = saved_ZH;
   eff_CphhVPVP(gO1) = result;

}

void MSSMNoFV_effective_couplings::calculate_eff_CphhVGVG(int gO1)
{
   const auto vd = MODELPARAMETER(vd);
   const auto vu = MODELPARAMETER(vu);
   const auto g3 = MODELPARAMETER(g3);
   const auto MFd = MODELPARAMETER(MFd);
   const auto MFs = MODELPARAMETER(MFs);
   const auto MFb = MODELPARAMETER(MFb);
   const auto MFu = MODELPARAMETER(MFu);
   const auto MFc = MODELPARAMETER(MFc);
   const auto MFt = MODELPARAMETER(MFt);
   const auto MSd = MODELPARAMETER(MSd);
   const auto MSu = MODELPARAMETER(MSu);
   const auto MSs = MODELPARAMETER(MSs);
   const auto MSc = MODELPARAMETER(MSc);
   const auto MSb = MODELPARAMETER(MSb);
   const auto MSt = MODELPARAMETER(MSt);
   const double alpha_s = 0.07957747154594767*Sqr(g3);
   const auto decay_mass = PHYSICAL(Mhh)(gO1);
   const auto decay_scale = 0.25 * Sqr(decay_mass);
   const auto saved_ZH = ZH;
   ZH = PHYSICAL(ZH);

   const auto vev = Sqrt(Sqr(vd) + Sqr(vu));

   std::complex<double> result = 0;
   result += CpbarFdFdhhPL(gO1) * vev * AS12(decay_scale / Sqr(MFd)) / MFd;
   result += CpbarFsFshhPL(gO1) * vev * AS12(decay_scale / Sqr(MFs)) / MFs;
   result += CpbarFbFbhhPL(gO1) * vev * AS12(decay_scale / Sqr(MFb)) / MFb;
   result += CpbarFuFuhhPL(gO1) * vev * AS12(decay_scale / Sqr(MFu)) / MFu;
   result += CpbarFcFchhPL(gO1) * vev * AS12(decay_scale / Sqr(MFc)) / MFc;
   result += CpbarFtFthhPL(gO1) * vev * AS12(decay_scale / Sqr(MFt)) / MFt;
   for (int gI1 = 0; gI1 < 2; ++gI1) {
      result += 0.5 * CphhSdconjSd(gO1, gI1, gI1) * vev * AS0(decay_scale /
         Sqr(MSd(gI1))) / Sqr(MSd(gI1));
   }
   for (int gI1 = 0; gI1 < 2; ++gI1) {
      result += 0.5 * CphhSuconjSu(gO1, gI1, gI1) * vev * AS0(decay_scale /
         Sqr(MSu(gI1))) / Sqr(MSu(gI1));
   }
   for (int gI1 = 0; gI1 < 2; ++gI1) {
      result += 0.5 * CphhSsconjSs(gO1, gI1, gI1) * vev * AS0(decay_scale /
         Sqr(MSs(gI1))) / Sqr(MSs(gI1));
   }
   for (int gI1 = 0; gI1 < 2; ++gI1) {
      result += 0.5 * CphhScconjSc(gO1, gI1, gI1) * vev * AS0(decay_scale /
         Sqr(MSc(gI1))) / Sqr(MSc(gI1));
   }
   for (int gI1 = 0; gI1 < 2; ++gI1) {
      result += 0.5 * CphhSbconjSb(gO1, gI1, gI1) * vev * AS0(decay_scale /
         Sqr(MSb(gI1))) / Sqr(MSb(gI1));
   }
   for (int gI1 = 0; gI1 < 2; ++gI1) {
      result += 0.5 * CphhStconjSt(gO1, gI1, gI1) * vev * AS0(decay_scale /
         Sqr(MSt(gI1))) / Sqr(MSt(gI1));
   }
   result *= 0.75;

   if (include_qcd_corrections) {
      result *= scalar_scaling_factor(decay_mass);
   }

   result *= 0.12617879380849006 * alpha_s * Sqrt(qedqcd.displayFermiConstant()
      );

   ZH = saved_ZH;
   eff_CphhVGVG(gO1) = result;

}

void MSSMNoFV_effective_couplings::calculate_eff_CpAhVPVP(int gO1)
{
   const auto vd = MODELPARAMETER(vd);
   const auto vu = MODELPARAMETER(vu);
   const auto MFd = MODELPARAMETER(MFd);
   const auto MFs = MODELPARAMETER(MFs);
   const auto MFb = MODELPARAMETER(MFb);
   const auto MFu = MODELPARAMETER(MFu);
   const auto MFc = MODELPARAMETER(MFc);
   const auto MFt = MODELPARAMETER(MFt);
   const auto MFe = MODELPARAMETER(MFe);
   const auto MFm = MODELPARAMETER(MFm);
   const auto MFtau = MODELPARAMETER(MFtau);
   const auto MCha = MODELPARAMETER(MCha);
   const auto decay_mass = PHYSICAL(MAh)(gO1);
   const auto decay_scale = 0.25 * Sqr(decay_mass);
   const auto saved_ZA = ZA;
   ZA = PHYSICAL(ZA);

   const auto vev = Sqrt(Sqr(vd) + Sqr(vu));

   std::complex<double> result = 0;
   result += 0.3333333333333333 * pseudoscalar_fermion_qcd_factor(decay_mass,
      MFd) * CpbarFdFdAhPL(gO1) * vev * AP12(decay_scale / Sqr(MFd)) / MFd;
   result += 0.3333333333333333 * pseudoscalar_fermion_qcd_factor(decay_mass,
      MFs) * CpbarFsFsAhPL(gO1) * vev * AP12(decay_scale / Sqr(MFs)) / MFs;
   result += 0.3333333333333333 * pseudoscalar_fermion_qcd_factor(decay_mass,
      MFb) * CpbarFbFbAhPL(gO1) * vev * AP12(decay_scale / Sqr(MFb)) / MFb;
   result += 1.3333333333333333 * pseudoscalar_fermion_qcd_factor(decay_mass,
      MFu) * CpbarFuFuAhPL(gO1) * vev * AP12(decay_scale / Sqr(MFu)) / MFu;
   result += 1.3333333333333333 * pseudoscalar_fermion_qcd_factor(decay_mass,
      MFc) * CpbarFcFcAhPL(gO1) * vev * AP12(decay_scale / Sqr(MFc)) / MFc;
   result += 1.3333333333333333 * pseudoscalar_fermion_qcd_factor(decay_mass,
      MFt) * CpbarFtFtAhPL(gO1) * vev * AP12(decay_scale / Sqr(MFt)) / MFt;
   result += CpbarFeFeAhPL(gO1) * vev * AP12(decay_scale / Sqr(MFe)) / MFe;
   result += CpbarFmFmAhPL(gO1) * vev * AP12(decay_scale / Sqr(MFm)) / MFm;
   result += CpbarFtauFtauAhPL(gO1) * vev * AP12(decay_scale / Sqr(MFtau)) /
      MFtau;
   for (int gI1 = 0; gI1 < 2; ++gI1) {
      result += CpbarChaChaAhPL(gI1, gI1, gO1) * vev * AP12(decay_scale /
         Sqr(MCha(gI1))) / MCha(gI1);
   }
   result *= 2.0;

   result *= 0.1892681907127351 * physical_input.get(Physical_input::alpha_em_0
      ) * Sqrt(qedqcd.displayFermiConstant());

   ZA = saved_ZA;
   eff_CpAhVPVP(gO1) = result;

}

void MSSMNoFV_effective_couplings::calculate_eff_CpAhVGVG(int gO1)
{
   const auto vd = MODELPARAMETER(vd);
   const auto vu = MODELPARAMETER(vu);
   const auto g3 = MODELPARAMETER(g3);
   const auto MFd = MODELPARAMETER(MFd);
   const auto MFs = MODELPARAMETER(MFs);
   const auto MFb = MODELPARAMETER(MFb);
   const auto MFu = MODELPARAMETER(MFu);
   const auto MFc = MODELPARAMETER(MFc);
   const auto MFt = MODELPARAMETER(MFt);
   const double alpha_s = 0.07957747154594767*Sqr(g3);
   const auto decay_mass = PHYSICAL(MAh)(gO1);
   const auto decay_scale = 0.25 * Sqr(decay_mass);
   const auto saved_ZA = ZA;
   ZA = PHYSICAL(ZA);

   const auto vev = Sqrt(Sqr(vd) + Sqr(vu));

   std::complex<double> result = 0;
   result += CpbarFdFdAhPL(gO1) * vev * AP12(decay_scale / Sqr(MFd)) / MFd;
   result += CpbarFsFsAhPL(gO1) * vev * AP12(decay_scale / Sqr(MFs)) / MFs;
   result += CpbarFbFbAhPL(gO1) * vev * AP12(decay_scale / Sqr(MFb)) / MFb;
   result += CpbarFuFuAhPL(gO1) * vev * AP12(decay_scale / Sqr(MFu)) / MFu;
   result += CpbarFcFcAhPL(gO1) * vev * AP12(decay_scale / Sqr(MFc)) / MFc;
   result += CpbarFtFtAhPL(gO1) * vev * AP12(decay_scale / Sqr(MFt)) / MFt;
   result *= 1.5;

   if (include_qcd_corrections) {
      result *= pseudoscalar_scaling_factor(decay_mass);
   }

   result *= 0.12617879380849006 * alpha_s * Sqrt(qedqcd.displayFermiConstant()
      );

   ZA = saved_ZA;
   eff_CpAhVGVG(gO1) = result;

}


} // namespace flexiblesusy
