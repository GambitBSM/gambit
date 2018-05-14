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

// File generated at Thu 10 May 2018 14:47:55

#include "HSSUSY_two_scale_high_scale_constraint.hpp"
#include "HSSUSY_two_scale_model.hpp"
#include "HSSUSY_info.hpp"
#include "wrappers.hpp"
#include "logger.hpp"
#include "ew_input.hpp"
#include "gsl_utils.hpp"
#include "minimizer.hpp"
#include "raii.hpp"
#include "root_finder.hpp"
#include "threshold_loop_functions.hpp"
#include "numerics2.hpp"

#include <cmath>
#include <cerrno>
#include <cstring>

namespace flexiblesusy {

#define DERIVEDPARAMETER(p) model->p()
#define EXTRAPARAMETER(p) model->get_##p()
#define INPUTPARAMETER(p) model->get_input().p
#define MODELPARAMETER(p) model->get_##p()
#define PHASE(p) model->get_##p()
#define BETAPARAMETER(p) beta_functions.get_##p()
#define BETAPARAMETER1(l,p) beta_functions_##l##L.get_##p()
#define BETA(p) beta_##p
#define BETA1(l,p) beta_##l##L_##p
#define LowEnergyConstant(p) Electroweak_constants::p
#define MZPole Electroweak_constants::MZ
#define STANDARDDEVIATION(p) Electroweak_constants::Error_##p
#define Pole(p) model->get_physical().p
#define SCALE model->get_scale()
#define THRESHOLD static_cast<int>(model->get_thresholds())
#define MODEL model
#define MODELCLASSNAME HSSUSY<Two_scale>

HSSUSY_high_scale_constraint<Two_scale>::HSSUSY_high_scale_constraint(
   HSSUSY<Two_scale>* model_)
   : model(model_)
{
   initialize();
}

void HSSUSY_high_scale_constraint<Two_scale>::apply()
{
   check_model_ptr();



   update_scale();

   const auto TanBeta = INPUTPARAMETER(TanBeta);
   const auto TwoLoopAbAs = INPUTPARAMETER(TwoLoopAbAs);
   const auto M3Input = INPUTPARAMETER(M3Input);
   const auto AbInput = INPUTPARAMETER(AbInput);
   const auto MuInput = INPUTPARAMETER(MuInput);
   const auto mAInput = INPUTPARAMETER(mAInput);
   const auto AtInput = INPUTPARAMETER(AtInput);
   const auto TwoLoopAtAb = INPUTPARAMETER(TwoLoopAtAb);
   const auto TwoLoopAtAs = INPUTPARAMETER(TwoLoopAtAs);
   const auto TwoLoopAtAt = INPUTPARAMETER(TwoLoopAtAt);
   const auto TwoLoopAtauAtau = INPUTPARAMETER(TwoLoopAtauAtau);
   const auto AtauInput = INPUTPARAMETER(AtauInput);
   const auto LambdaLoopOrder = INPUTPARAMETER(LambdaLoopOrder);
   const auto DeltaEFT = INPUTPARAMETER(DeltaEFT);
   const auto M2Input = INPUTPARAMETER(M2Input);
   const auto M1Input = INPUTPARAMETER(M1Input);
   const auto msu2 = INPUTPARAMETER(msu2);
   const auto msq2 = INPUTPARAMETER(msq2);
   const auto msd2 = INPUTPARAMETER(msd2);
   const auto mse2 = INPUTPARAMETER(mse2);
   const auto msl2 = INPUTPARAMETER(msl2);
   const auto g1 = MODELPARAMETER(g1);
   const auto g2 = MODELPARAMETER(g2);
   const auto g3 = MODELPARAMETER(g3);
   const auto v = MODELPARAMETER(v);
   const auto Yd = MODELPARAMETER(Yd);
   const auto Yu = MODELPARAMETER(Yu);
   const auto Ye = MODELPARAMETER(Ye);

   MODEL->set_Lambdax(Re(0.25*(0.6*Sqr(g1) + Sqr(g2))*Sqr(Cos(2*ArcTan(TanBeta)
      )) + (IF(TwoLoopAbAs >= 1, WHICH(IsCloseRel(msu2(2,2),msq2(2,2),0.01) &&
      IsCloseRel(Sqrt(msu2(2,2)),M3Input,0.01), (0.00390625*Quad(Yd(2,2))*Sqr(g3)*
      (32*Log(msq2(2,2)) - 32*Log(Sqr(SCALE)) + 32*Log(msq2(2,2))*Log(Sqr(SCALE))
      + (5.333333333333333*Cube(AbInput - MuInput*TanBeta))/Power3(Sqrt(msq2(2,2))
      ) - (10.666666666666666*Cube(AbInput - MuInput*TanBeta)*Log(msq2(2,2)))
      /Power3(Sqrt(msq2(2,2))) + (10.666666666666666*Cube(AbInput - MuInput*
      TanBeta)*Log(Sqr(SCALE)))/Power3(Sqrt(msq2(2,2))) - (32*(AbInput - MuInput*
      TanBeta))/Sqrt(msq2(2,2)) + (32*(AbInput - MuInput*TanBeta)*Log(msq2(2,2)))
      /Sqrt(msq2(2,2)) - (32*(AbInput - MuInput*TanBeta)*Log(Sqr(SCALE)))/Sqrt(
      msq2(2,2)) + (16*Sqr(AbInput - MuInput*TanBeta))/msq2(2,2) - (32*Log(msq2(2,
      2))*Sqr(AbInput - MuInput*TanBeta))/msq2(2,2) + (32*Log(Sqr(SCALE))*Sqr(
      AbInput - MuInput*TanBeta))/msq2(2,2) - 16*Sqr(Log(Sqr(SCALE))) - 16*Sqr(Log
      (msq2(2,2))) - (1.3333333333333333*Quad(AbInput - MuInput*TanBeta))/Sqr(msq2
      (2,2))))/(Quad(3.141592653589793)*Quad(1 + (0.0625*(1 + Sqr(TanBeta))*(0.25*
      Log(Sqr(MuInput)/Sqr(SCALE)) + (0.125*(-1 + 2*Log(Sqr(mAInput)/Sqr(SCALE))))
      /(1 + Sqr(TanBeta)) + ((-1 + Log(Sqr(mAInput)/Sqr(SCALE)))*Sqr(TanBeta))/(1
      + Sqr(TanBeta)))*Sqr(Yu(2,2)))/(Sqr(3.141592653589793)*Sqr(TanBeta)) + 0.5*(
      (-0.03125*Sqr(AbInput - MuInput*TanBeta)*Sqr(Yd(2,2))*TCF(5)(Sqrt(Abs(msq2(2
      ,2)/msd2(2,2)))))/(Sqrt(Abs(msd2(2,2)*msq2(2,2)))*Sqr(3.141592653589793)) -
      (0.03125*Sqr(AtInput - MuInput/TanBeta)*Sqr(Yu(2,2))*TCF(5)(Sqrt(Abs(msq2(2,
      2)/msu2(2,2)))))/(Sqrt(Abs(msq2(2,2)*msu2(2,2)))*Sqr(3.141592653589793))) +
      (0.0625*(1 + Sqr(TanBeta))*Sqr(Yd(2,2))*(0.75*Log(Sqr(MuInput)/Sqr(SCALE)) +
      (0.375*(-1 + 2*Log(Sqr(mAInput)/Sqr(SCALE)))*Sqr(TanBeta))/(1 + Sqr(TanBeta
      )) + 0.5*TCF(6)(Sqrt(msd2(2,2))/MuInput) + TCF(6)(Sqrt(msq2(2,2))/MuInput)))
      /Sqr(3.141592653589793) + (0.08333333333333333*Sqr(g3)*(1 + Log(Sqr(M3Input)
      /Sqr(SCALE)) + TCF(6)(Sqrt(msd2(2,2))/M3Input) + TCF(6)(Sqrt(msq2(2,2))
      /M3Input) - ((AbInput - MuInput*TanBeta)*TCF(9)(Sqrt(msq2(2,2))/M3Input,Sqrt
      (msd2(2,2))/M3Input))/M3Input))/Sqr(3.141592653589793) + (0.0625*(1 + Sqr(
      TanBeta))*Sqr(Yu(2,2))*(0.5*TCF(6)(Sqrt(msu2(2,2))/MuInput) + (0.5*(AtInput
      - MuInput/TanBeta)*TanBeta*TCF(9)(Sqrt(msq2(2,2))/MuInput,Sqrt(msu2(2,2))
      /MuInput))/MuInput))/(Sqr(3.141592653589793)*Sqr(TanBeta)))), IsCloseRel(
      msq2(2,2),msu2(2,2),0.01), (-0.010416666666666666*Quad(Yd(2,2))*Sqr(g3)*(24*
      Cube(msq2(2,2))*PolyLog(2,1 - Sqr(M3Input)/msq2(2,2))*((-2*M3Input*(AbInput
      - MuInput*TanBeta))/Abs(M3Input) + Sqrt(Sqr(M3Input)))*Power3(Sqrt(Sqr(
      M3Input))) + 6*Cube(msq2(2,2))*Sqr(Log(msq2(2,2)))*(3*Quad(M3Input) - 2*msq2
      (2,2)*Sqr(M3Input) - (4*M3Input*(AbInput - MuInput*TanBeta)*Power3(Sqrt(Sqr(
      M3Input))))/Abs(M3Input) + Sqr(msq2(2,2))) + Log(Sqr(M3Input))*Power3(Sqrt(
      Sqr(M3Input)))*(-12*Cube(msq2(2,2))*(Log(msq2(2,2)) - Log(Sqr(SCALE)))*((-2*
      M3Input*(AbInput - MuInput*TanBeta))/Abs(M3Input) + Sqrt(Sqr(M3Input))) + (4
      *M3Input*Cube(AbInput - MuInput*TanBeta)*msq2(2,2)*(-2*msq2(2,2) + Sqr(
      M3Input)))/Abs(M3Input) + Quad(AbInput - MuInput*TanBeta)*Sqrt(Sqr(M3Input))
      *(-3*msq2(2,2) + 2*Sqr(M3Input)) - 12*msq2(2,2)*Sqrt(Sqr(M3Input))*(-2*msq2(
      2,2) + Sqr(M3Input))*Sqr(AbInput - MuInput*TanBeta) - (24*M3Input*(AbInput -
      MuInput*TanBeta)*(msq2(2,2) + Sqr(M3Input))*Sqr(msq2(2,2)))/Abs(M3Input) +
      6*Sqrt(Sqr(M3Input))*(msq2(2,2) + 2*Sqr(M3Input))*Sqr(msq2(2,2))) + Log(msq2
      (2,2))*msq2(2,2)*(12*msq2(2,2)*(-2*msq2(2,2) + Sqr(M3Input))*(-msq2(2,2) + 2
      *Sqr(M3Input))*Sqr(AbInput - MuInput*TanBeta) + Quad(AbInput - MuInput*
      TanBeta)*(-3*Quad(M3Input) + 6*msq2(2,2)*Sqr(M3Input) - 2*Sqr(msq2(2,2))) +
      (4*M3Input*Cube(AbInput - MuInput*TanBeta)*Sqrt(Sqr(M3Input))*Sqr(msq2(2,2))
      )/Abs(M3Input) + (48*M3Input*(AbInput - MuInput*TanBeta)*Power3(Sqrt(Sqr(
      M3Input)))*Sqr(msq2(2,2)))/Abs(M3Input) - 18*Sqr(msq2(2,2))*(2*Quad(M3Input)
      - 2*msq2(2,2)*Sqr(M3Input) + Sqr(msq2(2,2))) - 12*Log(Sqr(SCALE))*Sqr(msq2(
      2,2))*(2*Quad(M3Input) - 2*msq2(2,2)*Sqr(M3Input) - (2*M3Input*(AbInput -
      MuInput*TanBeta)*Power3(Sqrt(Sqr(M3Input))))/Abs(M3Input) + Sqr(msq2(2,2))))
      - (-msq2(2,2) + Sqr(M3Input))*((4*M3Input*Cube(AbInput - MuInput*TanBeta)*
      msq2(2,2)*Sqrt(Sqr(M3Input))*(-2*msq2(2,2) + Sqr(M3Input)))/Abs(M3Input) + (
      24*M3Input*(AbInput - MuInput*TanBeta)*(msq2(2,2) - Sqr(M3Input))*Sqrt(Sqr(
      M3Input))*Sqr(msq2(2,2)))/Abs(M3Input) + Quad(AbInput - MuInput*TanBeta)*(2*
      Quad(M3Input) - 4*msq2(2,2)*Sqr(M3Input) + Sqr(msq2(2,2))) - 12*msq2(2,2)*
      Sqr(AbInput - MuInput*TanBeta)*(Quad(M3Input) - 3*msq2(2,2)*Sqr(M3Input) +
      Sqr(msq2(2,2))) + 3*Sqr(msq2(2,2))*(4*Quad(M3Input) - 9*msq2(2,2)*Sqr(
      M3Input) + 3*Sqr(msq2(2,2))) + 2*Log(Sqr(SCALE))*(3*Cube(msq2(2,2))*Log(Sqr(
      SCALE))*(msq2(2,2) - Sqr(M3Input)) + (2*M3Input*Cube(AbInput - MuInput*
      TanBeta)*msq2(2,2)*Sqrt(Sqr(M3Input))*(-msq2(2,2) + Sqr(M3Input)))/Abs(
      M3Input) - 6*msq2(2,2)*(-2*msq2(2,2) + Sqr(M3Input))*(-msq2(2,2) + Sqr(
      M3Input))*Sqr(AbInput - MuInput*TanBeta) + Quad(AbInput - MuInput*TanBeta)*
      Sqr(Sqr(M3Input) - msq2(2,2)) - (12*M3Input*(AbInput - MuInput*TanBeta)*
      Power3(Sqrt(Sqr(M3Input)))*Sqr(msq2(2,2)))/Abs(M3Input) + 3*Sqr(msq2(2,2))*(
      2*Quad(M3Input) - 3*msq2(2,2)*Sqr(M3Input) + 3*Sqr(msq2(2,2)))))))/(Cube(
      msq2(2,2))*Quad(3.141592653589793)*Quad(1 + (0.0625*(1 + Sqr(TanBeta))*(0.25
      *Log(Sqr(MuInput)/Sqr(SCALE)) + (0.125*(-1 + 2*Log(Sqr(mAInput)/Sqr(SCALE)))
      )/(1 + Sqr(TanBeta)) + ((-1 + Log(Sqr(mAInput)/Sqr(SCALE)))*Sqr(TanBeta))/(1
      + Sqr(TanBeta)))*Sqr(Yu(2,2)))/(Sqr(3.141592653589793)*Sqr(TanBeta)) + 0.5*
      ((-0.03125*Sqr(AbInput - MuInput*TanBeta)*Sqr(Yd(2,2))*TCF(5)(Sqrt(Abs(msq2(
      2,2)/msd2(2,2)))))/(Sqrt(Abs(msd2(2,2)*msq2(2,2)))*Sqr(3.141592653589793)) -
      (0.03125*Sqr(AtInput - MuInput/TanBeta)*Sqr(Yu(2,2))*TCF(5)(Sqrt(Abs(msq2(2
      ,2)/msu2(2,2)))))/(Sqrt(Abs(msq2(2,2)*msu2(2,2)))*Sqr(3.141592653589793))) +
      (0.0625*(1 + Sqr(TanBeta))*Sqr(Yd(2,2))*(0.75*Log(Sqr(MuInput)/Sqr(SCALE))
      + (0.375*(-1 + 2*Log(Sqr(mAInput)/Sqr(SCALE)))*Sqr(TanBeta))/(1 + Sqr(
      TanBeta)) + 0.5*TCF(6)(Sqrt(msd2(2,2))/MuInput) + TCF(6)(Sqrt(msq2(2,2))
      /MuInput)))/Sqr(3.141592653589793) + (0.08333333333333333*Sqr(g3)*(1 + Log(
      Sqr(M3Input)/Sqr(SCALE)) + TCF(6)(Sqrt(msd2(2,2))/M3Input) + TCF(6)(Sqrt(
      msq2(2,2))/M3Input) - ((AbInput - MuInput*TanBeta)*TCF(9)(Sqrt(msq2(2,2))
      /M3Input,Sqrt(msd2(2,2))/M3Input))/M3Input))/Sqr(3.141592653589793) + (
      0.0625*(1 + Sqr(TanBeta))*Sqr(Yu(2,2))*(0.5*TCF(6)(Sqrt(msu2(2,2))/MuInput)
      + (0.5*(AtInput - MuInput/TanBeta)*TanBeta*TCF(9)(Sqrt(msq2(2,2))/MuInput,
      Sqrt(msu2(2,2))/MuInput))/MuInput))/(Sqr(3.141592653589793)*Sqr(TanBeta)))*
      Sqr(-msq2(2,2) + Sqr(M3Input))), True, (0.00390625*Quad(Yd(2,2))*Sqr(g3)*(
      -16*Sqr(Log(Sqr(SCALE))) + (AbInput - MuInput*TanBeta)*((64*M3Input*Log(
      0.985*msd2(2,2))*Sqrt(Sqr(M3Input)))/(Abs(M3Input)*(-0.985*msd2(2,2) + 1.02*
      msq2(2,2))) - (64*M3Input*Log(0.985*msd2(2,2))*Log(Sqr(SCALE))*Power3(Sqrt(
      Sqr(M3Input))))/(Abs(M3Input)*(0.985*msd2(2,2) - 1.02*msq2(2,2))*(-0.985*
      msd2(2,2) + Sqr(M3Input))) + (128*M3Input*PolyLog(2,1 - (1.015228426395939*
      Sqr(M3Input))/msd2(2,2))*Power3(Sqrt(Sqr(M3Input))))/(Abs(M3Input)*(0.985*
      msd2(2,2) - 1.02*msq2(2,2))*(-0.985*msd2(2,2) + Sqr(M3Input))) + (128*
      M3Input*PolyLog(2,1 - (0.9803921568627451*Sqr(M3Input))/msq2(2,2))*Power3(
      Sqrt(Sqr(M3Input))))/(Abs(M3Input)*(-0.985*msd2(2,2) + 1.02*msq2(2,2))*(
      -1.02*msq2(2,2) + Sqr(M3Input))) + Log(1.02*msq2(2,2))*((-64*M3Input*Sqrt(
      Sqr(M3Input)))/(Abs(M3Input)*(-0.985*msd2(2,2) + 1.02*msq2(2,2))) - (64*
      M3Input*Log(Sqr(SCALE))*Power3(Sqrt(Sqr(M3Input))))/(Abs(M3Input)*(-0.985*
      msd2(2,2) + 1.02*msq2(2,2))*(-1.02*msq2(2,2) + Sqr(M3Input)))) + Log(Sqr(
      M3Input))*((-64*M3Input*Log(0.985*msd2(2,2))*Power3(Sqrt(Sqr(M3Input))))/(
      Abs(M3Input)*(0.985*msd2(2,2) - 1.02*msq2(2,2))*(-0.985*msd2(2,2) + Sqr(
      M3Input))) - (64*M3Input*Log(1.02*msq2(2,2))*Power3(Sqrt(Sqr(M3Input))))/(
      Abs(M3Input)*(-0.985*msd2(2,2) + 1.02*msq2(2,2))*(-1.02*msq2(2,2) + Sqr(
      M3Input))) + (64*M3Input*Log(Sqr(SCALE))*Power3(Sqrt(Sqr(M3Input))))/(Abs(
      M3Input)*(-0.985*msd2(2,2) + Sqr(M3Input))*(-1.02*msq2(2,2) + Sqr(M3Input)))
      ) + (64*M3Input*Power3(Sqrt(Sqr(M3Input)))*Sqr(Log(0.985*msd2(2,2))))/(Abs(
      M3Input)*(0.985*msd2(2,2) - 1.02*msq2(2,2))*(-0.985*msd2(2,2) + Sqr(M3Input)
      )) + (64*M3Input*Power3(Sqrt(Sqr(M3Input)))*Sqr(Log(1.02*msq2(2,2))))/(Abs(
      M3Input)*(-0.985*msd2(2,2) + 1.02*msq2(2,2))*(-1.02*msq2(2,2) + Sqr(M3Input)
      ))) + (7.962575893301484*(2*(0.985*msd2(2,2) + 1.02*msq2(2,2))*Power6(
      M3Input) + 6.0282*msd2(2,2)*msq2(2,2)*(0.985*msd2(2,2) + 1.02*msq2(2,2))*Sqr
      (M3Input) - 3.02826627*Sqr(msd2(2,2))*Sqr(msq2(2,2)) - Quad(M3Input)*(9.0423
      *msd2(2,2)*msq2(2,2) + 1.94045*Sqr(msd2(2,2)) + 2.0808*Sqr(msq2(2,2)))))/(
      msd2(2,2)*msq2(2,2)*(-0.985*msd2(2,2) + Sqr(M3Input))*(-1.02*msq2(2,2) + Sqr
      (M3Input))) + Cube(AbInput - MuInput*TanBeta)*(Log(1.02*msq2(2,2))*((64*
      M3Input*Log(Sqr(SCALE))*(0.985*msd2(2,2) + 1.02*msq2(2,2))*Sqrt(Sqr(M3Input)
      ))/(Abs(M3Input)*Cube(-0.985*msd2(2,2) + 1.02*msq2(2,2))) + (64*M3Input*(
      0.985*msd2(2,2) + 3.06*msq2(2,2))*Sqrt(Sqr(M3Input)))/(Abs(M3Input)*Cube(
      -0.985*msd2(2,2) + 1.02*msq2(2,2)))) - (64*M3Input*Log(0.985*msd2(2,2))*(
      2.955*msd2(2,2) + 1.02*msq2(2,2))*Sqrt(Sqr(M3Input)))/(Abs(M3Input)*Cube(
      -0.985*msd2(2,2) + 1.02*msq2(2,2))) + (64*M3Input*PolyLog(2,1 - (
      1.015228426395939*Sqr(M3Input))/msd2(2,2))*Sqrt(Sqr(M3Input))*(-0.985*msd2(2
      ,2) - 1.02*msq2(2,2) + 2*Sqr(M3Input)))/(Abs(M3Input)*Cube(0.985*msd2(2,2) -
      1.02*msq2(2,2))) + (64*M3Input*PolyLog(2,1 - (0.9803921568627451*Sqr(
      M3Input))/msq2(2,2))*Sqrt(Sqr(M3Input))*(-0.985*msd2(2,2) - 1.02*msq2(2,2) +
      2*Sqr(M3Input)))/(Abs(M3Input)*Cube(-0.985*msd2(2,2) + 1.02*msq2(2,2))) +
      Log(Sqr(M3Input))*((128*M3Input*Log(0.985*msd2(2,2))*Power3(Sqrt(Sqr(M3Input
      ))))/(Abs(M3Input)*Cube(-0.985*msd2(2,2) + 1.02*msq2(2,2))) - (128*M3Input*
      Log(1.02*msq2(2,2))*Power3(Sqrt(Sqr(M3Input))))/(Abs(M3Input)*Cube(-0.985*
      msd2(2,2) + 1.02*msq2(2,2)))) + (32*M3Input*Sqrt(Sqr(M3Input))*(-0.985*msd2(
      2,2) - 1.02*msq2(2,2) + 2*Sqr(M3Input))*Sqr(Log(0.985*msd2(2,2))))/(Abs(
      M3Input)*Cube(0.985*msd2(2,2) - 1.02*msq2(2,2))) + (32*M3Input*Sqrt(Sqr(
      M3Input))*(-0.985*msd2(2,2) - 1.02*msq2(2,2) + 2*Sqr(M3Input))*Sqr(Log(1.02*
      msq2(2,2))))/(Abs(M3Input)*Cube(-0.985*msd2(2,2) + 1.02*msq2(2,2))) + Log(
      Sqr(SCALE))*((-64*M3Input*Log(0.985*msd2(2,2))*(0.985*msd2(2,2) + 1.02*msq2(
      2,2))*Sqrt(Sqr(M3Input)))/(Abs(M3Input)*Cube(-0.985*msd2(2,2) + 1.02*msq2(2,
      2))) - (128*M3Input*Sqrt(Sqr(M3Input)))/(Abs(M3Input)*Sqr(-0.985*msd2(2,2) +
      1.02*msq2(2,2)))) - (256*M3Input*Sqrt(Sqr(M3Input)))/(Abs(M3Input)*Sqr(
      -0.985*msd2(2,2) + 1.02*msq2(2,2)))) + Sqr(AbInput - MuInput*TanBeta)*((
      -31.850303573205935*Sqr(M3Input))/(msd2(2,2)*msq2(2,2)) + (
      31.850303573205935*Log(Sqr(M3Input))*Quad(M3Input)*(-0.985*msd2(2,2) - 1.02*
      msq2(2,2) + Sqr(M3Input)))/(msd2(2,2)*msq2(2,2)*(-0.985*msd2(2,2) + Sqr(
      M3Input))*(-1.02*msq2(2,2) + Sqr(M3Input))) + (32*Log(0.985*msd2(2,2))*(
      -1.97*msd2(2,2) + 3*Sqr(M3Input)))/((0.985*msd2(2,2) - 1.02*msq2(2,2))*(
      -0.985*msd2(2,2) + Sqr(M3Input))) + Log(Sqr(SCALE))*((-64*Log(0.985*msd2(2,2
      )))/(-0.985*msd2(2,2) + 1.02*msq2(2,2)) - (31.850303573205935*Sqr(M3Input))/
      (msd2(2,2)*msq2(2,2))) + Log(1.02*msq2(2,2))*((64*Log(Sqr(SCALE)))/(-0.985*
      msd2(2,2) + 1.02*msq2(2,2)) + (32*(-2.04*msq2(2,2) + 3*Sqr(M3Input)))/((
      -0.985*msd2(2,2) + 1.02*msq2(2,2))*(-1.02*msq2(2,2) + Sqr(M3Input))) + (32*
      Log(0.985*msd2(2,2))*(0.985*msd2(2,2) + 1.02*msq2(2,2)))/Sqr(-0.985*msd2(2,2
      ) + 1.02*msq2(2,2))) + (16*(-2.955*msd2(2,2) + 1.02*msq2(2,2))*Sqr(Log(0.985
      *msd2(2,2))))/Sqr(-0.985*msd2(2,2) + 1.02*msq2(2,2)) + (16*(0.985*msd2(2,2)
      - 3.06*msq2(2,2))*Sqr(Log(1.02*msq2(2,2))))/Sqr(-0.985*msd2(2,2) + 1.02*msq2
      (2,2))) + Quad(AbInput - MuInput*TanBeta)*((16*PolyLog(2,1 - (
      1.015228426395939*Sqr(M3Input))/msd2(2,2))*(0.985*msd2(2,2) + 1.02*msq2(2,2)
      - 2*Sqr(M3Input)))/Cube(-0.985*msd2(2,2) + 1.02*msq2(2,2)) + (16*PolyLog(2,
      1 - (0.9803921568627451*Sqr(M3Input))/msq2(2,2))*(-0.985*msd2(2,2) - 1.02*
      msq2(2,2) + 2*Sqr(M3Input)))/Cube(-0.985*msd2(2,2) + 1.02*msq2(2,2)) + (16*
      Log(0.985*msd2(2,2))*(6.895*msd2(2,2) + 3.06*msq2(2,2) + 2*Sqr(M3Input)))
      /Cube(-0.985*msd2(2,2) + 1.02*msq2(2,2)) + (16*(1.97*msd2(2,2)*(0.985*msd2(2
      ,2) + 1.02*msq2(2,2)) + (0.985*msd2(2,2) - 1.02*msq2(2,2))*Sqr(M3Input))*Sqr
      (Log(0.985*msd2(2,2))))/Quad(-0.985*msd2(2,2) + 1.02*msq2(2,2)) + (16*(2.04*
      msq2(2,2)*(0.985*msd2(2,2) + 1.02*msq2(2,2)) + (-0.985*msd2(2,2) + 1.02*msq2
      (2,2))*Sqr(M3Input))*Sqr(Log(1.02*msq2(2,2))))/Quad(-0.985*msd2(2,2) + 1.02*
      msq2(2,2)) + Log(Sqr(SCALE))*((32*Log(0.985*msd2(2,2))*(0.985*msd2(2,2) +
      1.02*msq2(2,2) + Sqr(M3Input)))/Cube(-0.985*msd2(2,2) + 1.02*msq2(2,2)) + (
      15.925151786602967*(4.0188*msd2(2,2)*msq2(2,2) + (0.985*msd2(2,2) + 1.02*
      msq2(2,2))*Sqr(M3Input)))/(msd2(2,2)*msq2(2,2)*Sqr(-0.985*msd2(2,2) + 1.02*
      msq2(2,2)))) - (15.925151786602967*Log(Sqr(M3Input))*(0.985*msd2(2,2) + 1.02
      *msq2(2,2))*Sqr(M3Input))/(msd2(2,2)*msq2(2,2)*Sqr(-0.985*msd2(2,2) + 1.02*
      msq2(2,2))) + (15.925151786602967*(6.0282*msd2(2,2)*msq2(2,2) + (0.985*msd2(
      2,2) + 1.02*msq2(2,2))*Sqr(M3Input)))/(msd2(2,2)*msq2(2,2)*Sqr(-0.985*msd2(2
      ,2) + 1.02*msq2(2,2))) + Log(1.02*msq2(2,2))*((-32*Log(Sqr(SCALE))*(0.985*
      msd2(2,2) + 1.02*msq2(2,2) + Sqr(M3Input)))/Cube(-0.985*msd2(2,2) + 1.02*
      msq2(2,2)) - (16*(2.955*msd2(2,2) + 7.140000000000001*msq2(2,2) + 2*Sqr(
      M3Input)))/Cube(-0.985*msd2(2,2) + 1.02*msq2(2,2)) - (32*Log(0.985*msd2(2,2)
      )*Sqr(0.985*msd2(2,2) + 1.02*msq2(2,2)))/Quad(-0.985*msd2(2,2) + 1.02*msq2(2
      ,2)))) + Log(Sqr(SCALE))*((15.925151786602967*((0.985*msd2(2,2) + 1.02*msq2(
      2,2))*Power6(M3Input) + 3.0141*msd2(2,2)*msq2(2,2)*(0.985*msd2(2,2) + 1.02*
      msq2(2,2))*Sqr(M3Input) - 3.02826627*Sqr(msd2(2,2))*Sqr(msq2(2,2)) - Quad(
      M3Input)*(3.0141*msd2(2,2)*msq2(2,2) + 0.970225*Sqr(msd2(2,2)) + 1.0404*Sqr(
      msq2(2,2)))))/(msd2(2,2)*msq2(2,2)*(-0.985*msd2(2,2) + Sqr(M3Input))*(-1.02*
      msq2(2,2) + Sqr(M3Input))) + (16*Log(0.985*msd2(2,2))*(2*Quad(M3Input) -
      1.97*msd2(2,2)*Sqr(M3Input) + 0.970225*Sqr(msd2(2,2))))/Sqr(-0.985*msd2(2,2)
      + Sqr(M3Input))) - (32*PolyLog(2,1 - (1.015228426395939*Sqr(M3Input))/msd2(
      2,2))*Quad(M3Input))/Sqr(-0.985*msd2(2,2) + Sqr(M3Input)) + (24*Log(0.985*
      msd2(2,2))*(2*Quad(M3Input) - 1.97*msd2(2,2)*Sqr(M3Input) + 0.970225*Sqr(
      msd2(2,2))))/Sqr(-0.985*msd2(2,2) + Sqr(M3Input)) - (8*Sqr(Log(0.985*msd2(2,
      2)))*(3*Quad(M3Input) - 1.97*msd2(2,2)*Sqr(M3Input) + 0.970225*Sqr(msd2(2,2)
      )))/Sqr(-0.985*msd2(2,2) + Sqr(M3Input)) + Log(1.02*msq2(2,2))*((24*(2*Quad(
      M3Input) - 2.04*msq2(2,2)*Sqr(M3Input) + 1.0404*Sqr(msq2(2,2))))/Sqr(-1.02*
      msq2(2,2) + Sqr(M3Input)) + (16*Log(Sqr(SCALE))*(2*Quad(M3Input) - 2.04*msq2
      (2,2)*Sqr(M3Input) + 1.0404*Sqr(msq2(2,2))))/Sqr(-1.02*msq2(2,2) + Sqr(
      M3Input))) + Log(Sqr(M3Input))*((16*Log(0.985*msd2(2,2))*Quad(M3Input))/Sqr(
      -0.985*msd2(2,2) + Sqr(M3Input)) + (16*Log(1.02*msq2(2,2))*Quad(M3Input))
      /Sqr(-1.02*msq2(2,2) + Sqr(M3Input)) - (16*Log(Sqr(SCALE))*Quad(M3Input)*(2*
      Quad(M3Input) - 2*(0.985*msd2(2,2) + 1.02*msq2(2,2))*Sqr(M3Input) + 0.970225
      *Sqr(msd2(2,2)) + 1.0404*Sqr(msq2(2,2))))/(Sqr(-0.985*msd2(2,2) + Sqr(
      M3Input))*Sqr(-1.02*msq2(2,2) + Sqr(M3Input))) - (7.962575893301484*Quad(
      M3Input)*(2*(0.985*msd2(2,2) + 1.02*msq2(2,2))*Power6(M3Input) + Quad(
      M3Input)*(2.0094*msd2(2,2)*msq2(2,2) - 3.8809*Sqr(msd2(2,2)) - 4.1616*Sqr(
      msq2(2,2))) + 1.0047*msd2(2,2)*msq2(2,2)*(0.970225*Sqr(msd2(2,2)) + 1.0404*
      Sqr(msq2(2,2))) + 2*(0.985*msd2(2,2) + 1.02*msq2(2,2))*Sqr(M3Input)*Sqr(
      -0.985*msd2(2,2) + 1.02*msq2(2,2))))/(msd2(2,2)*msq2(2,2)*Sqr(-0.985*msd2(2,
      2) + Sqr(M3Input))*Sqr(-1.02*msq2(2,2) + Sqr(M3Input)))) - (32*PolyLog(2,1 -
      (0.9803921568627451*Sqr(M3Input))/msq2(2,2))*Quad(M3Input))/Sqr(-1.02*msq2(
      2,2) + Sqr(M3Input)) - (8*Sqr(Log(1.02*msq2(2,2)))*(3*Quad(M3Input) - 2.04*
      msq2(2,2)*Sqr(M3Input) + 1.0404*Sqr(msq2(2,2))))/Sqr(-1.02*msq2(2,2) + Sqr(
      M3Input))))/(Quad(3.141592653589793)*Quad(1 + (0.0625*(1 + Sqr(TanBeta))*(
      0.25*Log(Sqr(MuInput)/Sqr(SCALE)) + (0.125*(-1 + 2*Log(Sqr(mAInput)/Sqr(
      SCALE))))/(1 + Sqr(TanBeta)) + ((-1 + Log(Sqr(mAInput)/Sqr(SCALE)))*Sqr(
      TanBeta))/(1 + Sqr(TanBeta)))*Sqr(Yu(2,2)))/(Sqr(3.141592653589793)*Sqr(
      TanBeta)) + 0.5*((-0.03125*Sqr(AbInput - MuInput*TanBeta)*Sqr(Yd(2,2))*TCF(5
      )(Sqrt(Abs(msq2(2,2)/msd2(2,2)))))/(Sqrt(Abs(msd2(2,2)*msq2(2,2)))*Sqr(
      3.141592653589793)) - (0.03125*Sqr(AtInput - MuInput/TanBeta)*Sqr(Yu(2,2))*
      TCF(5)(Sqrt(Abs(msq2(2,2)/msu2(2,2)))))/(Sqrt(Abs(msq2(2,2)*msu2(2,2)))*Sqr(
      3.141592653589793))) + (0.0625*(1 + Sqr(TanBeta))*Sqr(Yd(2,2))*(0.75*Log(Sqr
      (MuInput)/Sqr(SCALE)) + (0.375*(-1 + 2*Log(Sqr(mAInput)/Sqr(SCALE)))*Sqr(
      TanBeta))/(1 + Sqr(TanBeta)) + 0.5*TCF(6)(Sqrt(msd2(2,2))/MuInput) + TCF(6)(
      Sqrt(msq2(2,2))/MuInput)))/Sqr(3.141592653589793) + (0.08333333333333333*Sqr
      (g3)*(1 + Log(Sqr(M3Input)/Sqr(SCALE)) + TCF(6)(Sqrt(msd2(2,2))/M3Input) +
      TCF(6)(Sqrt(msq2(2,2))/M3Input) - ((AbInput - MuInput*TanBeta)*TCF(9)(Sqrt(
      msq2(2,2))/M3Input,Sqrt(msd2(2,2))/M3Input))/M3Input))/Sqr(3.141592653589793
      ) + (0.0625*(1 + Sqr(TanBeta))*Sqr(Yu(2,2))*(0.5*TCF(6)(Sqrt(msu2(2,2))
      /MuInput) + (0.5*(AtInput - MuInput/TanBeta)*TanBeta*TCF(9)(Sqrt(msq2(2,2))
      /MuInput,Sqrt(msu2(2,2))/MuInput))/MuInput))/(Sqr(3.141592653589793)*Sqr(
      TanBeta))))), 0) + IF(TwoLoopAtAb >= 1, WHICH(IsCloseRel(Sqr(SCALE),msq2(2,2
      ),0.01) && IsCloseRel(Sqr(SCALE),msu2(2,2),0.01) && IsCloseRel(Sqr(SCALE),
      msd2(2,2),0.01) && IsCloseRel(SCALE,mAInput,0.01) && IsCloseRel(SCALE,Abs(
      MuInput),0.01), (0.00390625*((Power6(Yd(2,2))*(15 - Power6(AbInput - MuInput
      *TanBeta)/Power3(Sqrt(msq2(2,2)*msu2(2,2))) + (10.5*Quad(AbInput - MuInput*
      TanBeta))/(msq2(2,2)*msu2(2,2)) - (42*Sqr(AbInput - MuInput*TanBeta))/Sqrt(
      msq2(2,2)*msu2(2,2)) + (1 + Sqr(TanBeta))*(12 + (3*Quad(AbInput - MuInput*
      TanBeta))/(msq2(2,2)*msu2(2,2)) - (6*Sqr(AbInput - MuInput*TanBeta))/Sqrt(
      msq2(2,2)*msu2(2,2))) + Sqr(TanBeta)*(-10.049794796731925 + (
      2.6243712000000006*(AbInput + MuInput/TanBeta)*Cube(AbInput - MuInput*
      TanBeta))/(msq2(2,2)*msu2(2,2)) + (1.5025151999999977*(AbInput +
      MuInput/TanBeta)*(AbInput - MuInput*TanBeta))/Sqrt(msq2(2,2)*msu2(2,2)) + (
      0.37562879999999943*Sqr(AbInput + MuInput/TanBeta))/Sqrt(msq2(2,2)*msu2(2,2)
      ) + Quad(AbInput - MuInput*TanBeta)*(-1.5/(msq2(2,2)*msu2(2,2)) - (
      0.06218560000000006*Sqr(AbInput + MuInput/TanBeta))/Power3(Sqrt(msq2(2,2)*
      msu2(2,2)))) + (8.063443199999998/Sqrt(msq2(2,2)*msu2(2,2)) - (
      0.06344319999999826*Sqr(AbInput + MuInput/TanBeta))/(msq2(2,2)*msu2(2,2)))*
      Sqr(AbInput - MuInput*TanBeta))))/Power6(1 + (0.0625*(1 + Sqr(TanBeta))*(
      0.25*Log(Sqr(MuInput)/Sqr(SCALE)) + (0.125*(-1 + 2*Log(Sqr(mAInput)/Sqr(
      SCALE))))/(1 + Sqr(TanBeta)) + ((-1 + Log(Sqr(mAInput)/Sqr(SCALE)))*Sqr(
      TanBeta))/(1 + Sqr(TanBeta)))*Sqr(Yu(2,2)))/(Sqr(3.141592653589793)*Sqr(
      TanBeta)) + 0.5*((-0.03125*Sqr(AbInput - MuInput*TanBeta)*Sqr(Yd(2,2))*TCF(5
      )(Sqrt(Abs(msq2(2,2)/msd2(2,2)))))/(Sqrt(Abs(msd2(2,2)*msq2(2,2)))*Sqr(
      3.141592653589793)) - (0.03125*Sqr(AtInput - MuInput/TanBeta)*Sqr(Yu(2,2))*
      TCF(5)(Sqrt(Abs(msq2(2,2)/msu2(2,2)))))/(Sqrt(Abs(msq2(2,2)*msu2(2,2)))*Sqr(
      3.141592653589793))) + (0.0625*(1 + Sqr(TanBeta))*Sqr(Yd(2,2))*(0.75*Log(Sqr
      (MuInput)/Sqr(SCALE)) + (0.375*(-1 + 2*Log(Sqr(mAInput)/Sqr(SCALE)))*Sqr(
      TanBeta))/(1 + Sqr(TanBeta)) + 0.5*TCF(6)(Sqrt(msd2(2,2))/MuInput) + TCF(6)(
      Sqrt(msq2(2,2))/MuInput)))/Sqr(3.141592653589793) + (0.08333333333333333*Sqr
      (g3)*(1 + Log(Sqr(M3Input)/Sqr(SCALE)) + TCF(6)(Sqrt(msd2(2,2))/M3Input) +
      TCF(6)(Sqrt(msq2(2,2))/M3Input) - ((AbInput - MuInput*TanBeta)*TCF(9)(Sqrt(
      msq2(2,2))/M3Input,Sqrt(msd2(2,2))/M3Input))/M3Input))/Sqr(3.141592653589793
      ) + (0.0625*(1 + Sqr(TanBeta))*Sqr(Yu(2,2))*(0.5*TCF(6)(Sqrt(msu2(2,2))
      /MuInput) + (0.5*(AtInput - MuInput/TanBeta)*TanBeta*TCF(9)(Sqrt(msq2(2,2))
      /MuInput,Sqrt(msu2(2,2))/MuInput))/MuInput))/(Sqr(3.141592653589793)*Sqr(
      TanBeta))) + (Quad(Yd(2,2))*(8.35153120435743 - (0.4585429333333333*(AbInput
      + MuInput/TanBeta)*Cube(AbInput - MuInput*TanBeta))/(msq2(2,2)*msu2(2,2)) +
      (6.751257599999999*(AbInput + MuInput/TanBeta)*(AbInput - MuInput*TanBeta))
      /Sqrt(msq2(2,2)*msu2(2,2)) + (AtInput + MuInput*TanBeta)*((
      -0.4585429333333333*Cube(AbInput - MuInput*TanBeta))/(msq2(2,2)*msu2(2,2)) +
      (6.751257599999999*(AbInput - MuInput*TanBeta))/Sqrt(msq2(2,2)*msu2(2,2)))
      + (0.5*Quad(AbInput - MuInput*TanBeta))/(msq2(2,2)*msu2(2,2)) + ((-2*MuInput
      *Cube(AbInput - MuInput*TanBeta))/(Abs(MuInput)*Power3(Sqrt(Sqrt(msq2(2,2)*
      msu2(2,2))))) + (12*MuInput*(AtInput - MuInput/TanBeta))/(Abs(MuInput)*Sqrt(
      Sqrt(msq2(2,2)*msu2(2,2)))))/(Sqrt(1/(1 + Sqr(TanBeta)))*Sqrt(Sqr(TanBeta)/(
      1 + Sqr(TanBeta)))) - (11.248742400000001*Sqr(AbInput - MuInput*TanBeta))
      /Sqrt(msq2(2,2)*msu2(2,2)) + Sqr(AtInput - MuInput/TanBeta)*(12/Sqrt(msq2(2,
      2)*msu2(2,2)) + Quad(AbInput - MuInput*TanBeta)/Power3(Sqrt(msq2(2,2)*msu2(2
      ,2))) - (9*Sqr(AbInput - MuInput*TanBeta))/(msq2(2,2)*msu2(2,2))) + (1 + Sqr
      (TanBeta))*(-24 - (3*Sqr(AbInput - MuInput*TanBeta))/Sqrt(msq2(2,2)*msu2(2,2
      )) + Sqr(AtInput - MuInput/TanBeta)*(-3/Sqrt(msq2(2,2)*msu2(2,2)) + (1.5*Sqr
      (AbInput - MuInput*TanBeta))/(msq2(2,2)*msu2(2,2)))) + (AtInput -
      MuInput/TanBeta)*((-9.3756288*(AbInput + MuInput/TanBeta))/Sqrt(msq2(2,2)*
      msu2(2,2)) - (9.3756288*(AbInput - MuInput*TanBeta))/Sqrt(msq2(2,2)*msu2(2,2
      )) + (2*(AbInput + MuInput/TanBeta)*Sqr(AbInput - MuInput*TanBeta))/(msq2(2,
      2)*msu2(2,2)) + (AtInput + MuInput*TanBeta)*((4*(AbInput + MuInput/TanBeta)*
      (AbInput - MuInput*TanBeta))/(msq2(2,2)*msu2(2,2)) - (0.819514311111111*(
      AbInput + MuInput/TanBeta)*Cube(AbInput - MuInput*TanBeta))/Power3(Sqrt(msq2
      (2,2)*msu2(2,2))) - 9.3756288/Sqrt(msq2(2,2)*msu2(2,2)) + (2*Sqr(AbInput -
      MuInput*TanBeta))/(msq2(2,2)*msu2(2,2)))) + Sqr(TanBeta)*(
      -14.063443199999998 - (9.3756288*(AbInput + MuInput/TanBeta)*(AbInput -
      MuInput*TanBeta))/Sqrt(msq2(2,2)*msu2(2,2)) - (4.6878144*Sqr(AbInput +
      MuInput/TanBeta))/Sqrt(msq2(2,2)*msu2(2,2)) + (1.6878143999999997/Sqrt(msq2(
      2,2)*msu2(2,2)) + Sqr(AbInput + MuInput/TanBeta)/(msq2(2,2)*msu2(2,2)))*Sqr(
      AbInput - MuInput*TanBeta) + (AtInput - MuInput/TanBeta)*((-9.3756288*(
      AbInput + MuInput/TanBeta))/Sqrt(msq2(2,2)*msu2(2,2)) - (9.3756288*(AbInput
      - MuInput*TanBeta))/Sqrt(msq2(2,2)*msu2(2,2)) + (2*(AbInput +
      MuInput/TanBeta)*Sqr(AbInput - MuInput*TanBeta))/(msq2(2,2)*msu2(2,2))) +
      Sqr(AtInput - MuInput/TanBeta)*((2*(AbInput + MuInput/TanBeta)*(AbInput -
      MuInput*TanBeta))/(msq2(2,2)*msu2(2,2)) + 1.6878143999999997/Sqrt(msq2(2,2)*
      msu2(2,2)) + Sqr(AbInput + MuInput/TanBeta)/(msq2(2,2)*msu2(2,2)) - (
      0.2707285333333336*Sqr(AbInput + MuInput/TanBeta)*Sqr(AbInput - MuInput*
      TanBeta))/Power3(Sqrt(msq2(2,2)*msu2(2,2))))) + ((1 + Sqr(TanBeta))*(12 + (
      0.5*Quad(AbInput - MuInput*TanBeta))/(msq2(2,2)*msu2(2,2)) + (
      1.3378828010893575 + (AtInput + MuInput*TanBeta)*((-0.4585429333333333*Cube(
      AbInput - MuInput*TanBeta))/(msq2(2,2)*msu2(2,2)) + (6.751257599999999*(
      AbInput - MuInput*TanBeta))/Sqrt(msq2(2,2)*msu2(2,2))) - (0.5*Quad(AbInput -
      MuInput*TanBeta))/(msq2(2,2)*msu2(2,2)) + (4.6878144*Sqr(AbInput - MuInput*
      TanBeta))/Sqrt(msq2(2,2)*msu2(2,2)) + (1.6878143999999997/Sqrt(msq2(2,2)*
      msu2(2,2)) + (0.069514311111111*Quad(AbInput - MuInput*TanBeta))/Power3(Sqrt
      (msq2(2,2)*msu2(2,2))) - (0.6878143999999999*Sqr(AbInput - MuInput*TanBeta))
      /(msq2(2,2)*msu2(2,2)))*Sqr(AtInput + MuInput*TanBeta))/(1 + Sqr(TanBeta))))
      /Sqr(TanBeta))*Sqr(Yu(2,2)))/Quad(1 + (0.0625*(1 + Sqr(TanBeta))*(0.25*Log(
      Sqr(MuInput)/Sqr(SCALE)) + (0.125*(-1 + 2*Log(Sqr(mAInput)/Sqr(SCALE))))/(1
      + Sqr(TanBeta)) + ((-1 + Log(Sqr(mAInput)/Sqr(SCALE)))*Sqr(TanBeta))/(1 +
      Sqr(TanBeta)))*Sqr(Yu(2,2)))/(Sqr(3.141592653589793)*Sqr(TanBeta)) + 0.5*((
      -0.03125*Sqr(AbInput - MuInput*TanBeta)*Sqr(Yd(2,2))*TCF(5)(Sqrt(Abs(msq2(2,
      2)/msd2(2,2)))))/(Sqrt(Abs(msd2(2,2)*msq2(2,2)))*Sqr(3.141592653589793)) - (
      0.03125*Sqr(AtInput - MuInput/TanBeta)*Sqr(Yu(2,2))*TCF(5)(Sqrt(Abs(msq2(2,2
      )/msu2(2,2)))))/(Sqrt(Abs(msq2(2,2)*msu2(2,2)))*Sqr(3.141592653589793))) + (
      0.0625*(1 + Sqr(TanBeta))*Sqr(Yd(2,2))*(0.75*Log(Sqr(MuInput)/Sqr(SCALE)) +
      (0.375*(-1 + 2*Log(Sqr(mAInput)/Sqr(SCALE)))*Sqr(TanBeta))/(1 + Sqr(TanBeta)
      ) + 0.5*TCF(6)(Sqrt(msd2(2,2))/MuInput) + TCF(6)(Sqrt(msq2(2,2))/MuInput)))
      /Sqr(3.141592653589793) + (0.08333333333333333*Sqr(g3)*(1 + Log(Sqr(M3Input)
      /Sqr(SCALE)) + TCF(6)(Sqrt(msd2(2,2))/M3Input) + TCF(6)(Sqrt(msq2(2,2))
      /M3Input) - ((AbInput - MuInput*TanBeta)*TCF(9)(Sqrt(msq2(2,2))/M3Input,Sqrt
      (msd2(2,2))/M3Input))/M3Input))/Sqr(3.141592653589793) + (0.0625*(1 + Sqr(
      TanBeta))*Sqr(Yu(2,2))*(0.5*TCF(6)(Sqrt(msu2(2,2))/MuInput) + (0.5*(AtInput
      - MuInput/TanBeta)*TanBeta*TCF(9)(Sqrt(msq2(2,2))/MuInput,Sqrt(msu2(2,2))
      /MuInput))/MuInput))/(Sqr(3.141592653589793)*Sqr(TanBeta))) + (Quad(Yu(2,2))
      *(8.35153120435743 - (9.3756288*(AbInput + MuInput/TanBeta)*(AbInput -
      MuInput*TanBeta))/Sqrt(msq2(2,2)*msu2(2,2)) - (9.3756288*(AbInput - MuInput*
      TanBeta)*(AtInput + MuInput*TanBeta))/Sqrt(msq2(2,2)*msu2(2,2)) + Cube(
      AtInput - MuInput/TanBeta)*((-0.4585429333333333*(AbInput + MuInput/TanBeta)
      )/(msq2(2,2)*msu2(2,2)) + (AtInput + MuInput*TanBeta)*(-0.4585429333333333/(
      msq2(2,2)*msu2(2,2)) - (0.819514311111111*(AbInput + MuInput/TanBeta)*(
      AbInput - MuInput*TanBeta))/Power3(Sqrt(msq2(2,2)*msu2(2,2))))) + (AtInput -
      MuInput/TanBeta)*((6.751257599999999*(AbInput + MuInput/TanBeta))/Sqrt(msq2
      (2,2)*msu2(2,2)) - (9.3756288*(AbInput - MuInput*TanBeta))/Sqrt(msq2(2,2)*
      msu2(2,2)) + (AtInput + MuInput*TanBeta)*((4*(AbInput + MuInput/TanBeta)*(
      AbInput - MuInput*TanBeta))/(msq2(2,2)*msu2(2,2)) + 6.751257599999999/Sqrt(
      msq2(2,2)*msu2(2,2)))) + (1.3378828010893575 - (0.4585429333333333*(AbInput
      + MuInput/TanBeta)*Cube(AtInput - MuInput/TanBeta))/(msq2(2,2)*msu2(2,2)) +
      (6.751257599999999*(AtInput - MuInput/TanBeta)*(AbInput + MuInput/TanBeta))
      /Sqrt(msq2(2,2)*msu2(2,2)) + (1.6878143999999997*Sqr(AbInput +
      MuInput/TanBeta))/Sqrt(msq2(2,2)*msu2(2,2)) + Sqr(AtInput - MuInput/TanBeta)
      *(7.6878144/Sqrt(msq2(2,2)*msu2(2,2)) - (0.6878143999999999*Sqr(AbInput +
      MuInput/TanBeta))/(msq2(2,2)*msu2(2,2))) + Quad(AtInput - MuInput/TanBeta)*(
      -0.75/(msq2(2,2)*msu2(2,2)) + (0.069514311111111*Sqr(AbInput +
      MuInput/TanBeta))/Power3(Sqrt(msq2(2,2)*msu2(2,2)))))*Sqr(TanBeta) + ((-2*
      MuInput*Cube(AtInput - MuInput/TanBeta))/(Abs(MuInput)*Power3(Sqrt(Sqrt(msq2
      (2,2)*msu2(2,2))))) + (12*MuInput*(AbInput - MuInput*TanBeta))/(Abs(MuInput)
      *Sqrt(Sqrt(msq2(2,2)*msu2(2,2)))) + (MuInput*(AbInput - MuInput*TanBeta)*
      Quad(AtInput - MuInput/TanBeta))/(Abs(MuInput)*Power5(Sqrt(Sqrt(msq2(2,2)*
      msu2(2,2))))) - (12*MuInput*(AbInput - MuInput*TanBeta)*Sqr(AtInput -
      MuInput/TanBeta))/(Abs(MuInput)*Power3(Sqrt(Sqrt(msq2(2,2)*msu2(2,2))))))/(
      Sqrt(1/(1 + Sqr(TanBeta)))*Sqrt(Sqr(TanBeta)/(1 + Sqr(TanBeta)))) + (12 + (
      0.5*Quad(AtInput - MuInput/TanBeta))/(msq2(2,2)*msu2(2,2)))*(1 + Sqr(TanBeta
      )) + (12*Sqr(AbInput - MuInput*TanBeta))/Sqrt(msq2(2,2)*msu2(2,2)) + Sqr(
      AtInput - MuInput/TanBeta)*((2*(AbInput + MuInput/TanBeta)*(AbInput -
      MuInput*TanBeta))/(msq2(2,2)*msu2(2,2)) + (2*(AbInput - MuInput*TanBeta)*(
      AtInput + MuInput*TanBeta))/(msq2(2,2)*msu2(2,2)) + 12.751257599999999/Sqrt(
      msq2(2,2)*msu2(2,2)) - (3*Sqr(AbInput - MuInput*TanBeta))/(msq2(2,2)*msu2(2,
      2))) + Quad(AtInput - MuInput/TanBeta)*(-1.5/(msq2(2,2)*msu2(2,2)) + (0.5*
      Sqr(AbInput - MuInput*TanBeta))/Power3(Sqrt(msq2(2,2)*msu2(2,2)))) + ((1 +
      Sqr(TanBeta))*(-24 - (3*Sqr(AbInput - MuInput*TanBeta))/Sqrt(msq2(2,2)*msu2(
      2,2)) + Sqr(AtInput - MuInput/TanBeta)*(-3/Sqrt(msq2(2,2)*msu2(2,2)) + (1.5*
      Sqr(AbInput - MuInput*TanBeta))/(msq2(2,2)*msu2(2,2))) + (
      -14.063443199999998 - (9.3756288*(AbInput - MuInput*TanBeta)*(AtInput +
      MuInput*TanBeta))/Sqrt(msq2(2,2)*msu2(2,2)) + (1.6878143999999997*Sqr(
      AbInput - MuInput*TanBeta))/Sqrt(msq2(2,2)*msu2(2,2)) + (AtInput -
      MuInput/TanBeta)*((-9.3756288*(AbInput - MuInput*TanBeta))/Sqrt(msq2(2,2)*
      msu2(2,2)) + (AtInput + MuInput*TanBeta)*(-9.3756288/Sqrt(msq2(2,2)*msu2(2,2
      )) + (2*Sqr(AbInput - MuInput*TanBeta))/(msq2(2,2)*msu2(2,2)))) + (
      -4.6878144/Sqrt(msq2(2,2)*msu2(2,2)) + Sqr(AbInput - MuInput*TanBeta)/(msq2(
      2,2)*msu2(2,2)))*Sqr(AtInput + MuInput*TanBeta) + Sqr(AtInput -
      MuInput/TanBeta)*((2*(AbInput - MuInput*TanBeta)*(AtInput + MuInput*TanBeta)
      )/(msq2(2,2)*msu2(2,2)) + 1.6878143999999997/Sqrt(msq2(2,2)*msu2(2,2)) + (1/
      (msq2(2,2)*msu2(2,2)) - (0.2707285333333336*Sqr(AbInput - MuInput*TanBeta))
      /Power3(Sqrt(msq2(2,2)*msu2(2,2))))*Sqr(AtInput + MuInput*TanBeta)))/(1 +
      Sqr(TanBeta))))/Sqr(TanBeta))*Sqr(Yd(2,2)))/Sqr(1 + (0.006332573977646111*(1
      + Sqr(TanBeta))*(0.25*Log(Sqr(MuInput)/Sqr(SCALE)) + (0.125*(-1 + 2*Log(Sqr
      (mAInput)/Sqr(SCALE))))/(1 + Sqr(TanBeta)) + ((-1 + Log(Sqr(mAInput)/Sqr(
      SCALE)))*Sqr(TanBeta))/(1 + Sqr(TanBeta)))*Sqr(Yu(2,2)))/Sqr(TanBeta) + 0.5*
      ((-0.0031662869888230555*Sqr(AbInput - MuInput*TanBeta)*Sqr(Yd(2,2))*TCF(5)(
      Sqrt(Abs(msq2(2,2)/msd2(2,2)))))/Sqrt(Abs(msd2(2,2)*msq2(2,2))) - (
      0.0031662869888230555*Sqr(AtInput - MuInput/TanBeta)*Sqr(Yu(2,2))*TCF(5)(
      Sqrt(Abs(msq2(2,2)/msu2(2,2)))))/Sqrt(Abs(msq2(2,2)*msu2(2,2)))) +
      0.006332573977646111*(1 + Sqr(TanBeta))*Sqr(Yd(2,2))*(0.75*Log(Sqr(MuInput)
      /Sqr(SCALE)) + (0.375*(-1 + 2*Log(Sqr(mAInput)/Sqr(SCALE)))*Sqr(TanBeta))/(1
      + Sqr(TanBeta)) + 0.5*TCF(6)(Sqrt(msd2(2,2))/MuInput) + TCF(6)(Sqrt(msq2(2,
      2))/MuInput)) + 0.008443431970194815*Sqr(g3)*(1 + Log(Sqr(M3Input)/Sqr(SCALE
      )) + TCF(6)(Sqrt(msd2(2,2))/M3Input) + TCF(6)(Sqrt(msq2(2,2))/M3Input) - ((
      AbInput - MuInput*TanBeta)*TCF(9)(Sqrt(msq2(2,2))/M3Input,Sqrt(msd2(2,2))
      /M3Input))/M3Input) + (0.006332573977646111*(1 + Sqr(TanBeta))*Sqr(Yu(2,2))*
      (0.5*TCF(6)(Sqrt(msu2(2,2))/MuInput) + (0.5*(AtInput - MuInput/TanBeta)*
      TanBeta*TCF(9)(Sqrt(msq2(2,2))/MuInput,Sqrt(msu2(2,2))/MuInput))/MuInput))
      /Sqr(TanBeta))))/Quad(3.141592653589793), True, (0.00390625*((Power6(Yd(2,2)
      )*(3*(5 + Log(1.02*msq2(2,2))*(-6 - 6*Log(Sqr(SCALE))) + Log(0.96*msd2(2,2))
      *(-4 - 4*Log(Sqr(SCALE))) + 10*Log(Sqr(SCALE)) + 5*Sqr(Log(Sqr(SCALE))) + 2*
      Sqr(Log(0.96*msd2(2,2))) + 3*Sqr(Log(1.02*msq2(2,2)))) + Power6(AbInput -
      MuInput*TanBeta)*(9*((-2*(0.96*msd2(2,2) + 1.02*msq2(2,2)))/Quad(0.96*msd2(2
      ,2) - 1.02*msq2(2,2)) - (1.9584*msd2(2,2)*msq2(2,2)*(0.96*msd2(2,2) + 1.02*
      msq2(2,2))*Sqr(Log(0.96*msd2(2,2))))/Power6(0.96*msd2(2,2) - 1.02*msq2(2,2))
      - (1.9584*msd2(2,2)*msq2(2,2)*(0.96*msd2(2,2) + 1.02*msq2(2,2))*Sqr(Log(
      1.02*msq2(2,2))))/Power6(0.96*msd2(2,2) - 1.02*msq2(2,2)) - (Log(1.02*msq2(2
      ,2))*(5.8751999999999995*msd2(2,2)*msq2(2,2) + 0.9216*Sqr(msd2(2,2)) +
      1.0404*Sqr(msq2(2,2))))/Power5(0.96*msd2(2,2) - 1.02*msq2(2,2)) + Log(0.96*
      msd2(2,2))*((3.9168*Log(1.02*msq2(2,2))*msd2(2,2)*msq2(2,2)*(0.96*msd2(2,2)
      + 1.02*msq2(2,2)))/Power6(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (
      5.8751999999999995*msd2(2,2)*msq2(2,2) + 0.9216*Sqr(msd2(2,2)) + 1.0404*Sqr(
      msq2(2,2)))/Power5(0.96*msd2(2,2) - 1.02*msq2(2,2)))) + 3*((6*PolyLog(2,1 -
      (0.9411764705882352*msd2(2,2))/msq2(2,2)))/Cube(-0.96*msd2(2,2) + 1.02*msq2(
      2,2)) + Log(0.96*msd2(2,2))*((-6.12*Log(Sqr(SCALE))*msq2(2,2))/Quad(0.96*
      msd2(2,2) - 1.02*msq2(2,2)) + (0.9803921568627451*(0.96*msd2(2,2) - 5.1*msq2
      (2,2))*(0.96*msd2(2,2) + 2.04*msq2(2,2)))/(msq2(2,2)*Quad(0.96*msd2(2,2) -
      1.02*msq2(2,2))) + (2*Log(1.02*msq2(2,2))*(5.76*msd2(2,2) + 5.1*msq2(2,2)))
      /Quad(0.96*msd2(2,2) - 1.02*msq2(2,2))) - (2*(2.88*msd2(2,2) + 1.02*msq2(2,2
      ))*Sqr(Log(0.96*msd2(2,2))))/Quad(0.96*msd2(2,2) - 1.02*msq2(2,2)) - (2*(
      2.88*msd2(2,2) + 4.08*msq2(2,2))*Sqr(Log(1.02*msq2(2,2))))/Quad(0.96*msd2(2,
      2) - 1.02*msq2(2,2)) + (1.0212418300653596*Log(Sqr(SCALE))*(4.896*msd2(2,2)*
      msq2(2,2) - 0.9216*Sqr(msd2(2,2)) + 2.0808*Sqr(msq2(2,2))))/(Cube(0.96*msd2(
      2,2) - 1.02*msq2(2,2))*msd2(2,2)*msq2(2,2)) + (1.0212418300653596*(10.7712*
      msd2(2,2)*msq2(2,2) - 0.9216*Sqr(msd2(2,2)) + 2.0808*Sqr(msq2(2,2))))/(Cube(
      0.96*msd2(2,2) - 1.02*msq2(2,2))*msd2(2,2)*msq2(2,2)) + Log(1.02*msq2(2,2))*
      ((6.12*Log(Sqr(SCALE))*msq2(2,2))/Quad(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (
      1.0416666666666667*(12.7296*msd2(2,2)*msq2(2,2) - 2.7648*Sqr(msd2(2,2)) +
      2.0808*Sqr(msq2(2,2))))/(msd2(2,2)*Quad(0.96*msd2(2,2) - 1.02*msq2(2,2))))))
      + Quad(AbInput - MuInput*TanBeta)*(9*((2*Log(1.02*msq2(2,2))*(0.96*msd2(2,2
      ) + 1.02*msq2(2,2)))/Cube(0.96*msd2(2,2) - 1.02*msq2(2,2)) + Log(0.96*msd2(2
      ,2))*((-2*(0.96*msd2(2,2) + 1.02*msq2(2,2)))/Cube(0.96*msd2(2,2) - 1.02*msq2
      (2,2)) - (7.8336*Log(1.02*msq2(2,2))*msd2(2,2)*msq2(2,2))/Quad(0.96*msd2(2,2
      ) - 1.02*msq2(2,2))) + (3.9168*msd2(2,2)*msq2(2,2)*Sqr(Log(0.96*msd2(2,2))))
      /Quad(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (3.9168*msd2(2,2)*msq2(2,2)*Sqr(Log
      (1.02*msq2(2,2))))/Quad(0.96*msd2(2,2) - 1.02*msq2(2,2))) + 3*((-2*(0.96*
      msd2(2,2) + 3.06*msq2(2,2))*Sqr(Log(0.96*msd2(2,2))))/Cube(0.96*msd2(2,2) -
      1.02*msq2(2,2)) + (4*(2.88*msd2(2,2) + 1.02*msq2(2,2))*Sqr(Log(1.02*msq2(2,2
      ))))/Cube(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (6*PolyLog(2,1 - (
      0.9411764705882352*msd2(2,2))/msq2(2,2)))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2
      )) + (2.0424836601307192*(-26.438399999999998*msd2(2,2)*msq2(2,2) + 0.9216*
      Sqr(msd2(2,2)) + 2.0808*Sqr(msq2(2,2))))/(msd2(2,2)*msq2(2,2)*Sqr(0.96*msd2(
      2,2) - 1.02*msq2(2,2))) + (2.0424836601307192*Log(Sqr(SCALE))*(
      -14.687999999999999*msd2(2,2)*msq2(2,2) + 0.9216*Sqr(msd2(2,2)) + 2.0808*Sqr
      (msq2(2,2))))/(msd2(2,2)*msq2(2,2)*Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))) +
      Log(1.02*msq2(2,2))*((-2*Log(Sqr(SCALE))*(6.72*msd2(2,2) + 5.1*msq2(2,2)))
      /Cube(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (4.166666666666667*(-9.792*msd2(2,2
      )*msq2(2,2) - 2.7648*Sqr(msd2(2,2)) + 1.0404*Sqr(msq2(2,2))))/(Cube(0.96*
      msd2(2,2) - 1.02*msq2(2,2))*msd2(2,2))) + Log(0.96*msd2(2,2))*((2*Log(1.02*
      msq2(2,2))*(-4.8*msd2(2,2) + 1.02*msq2(2,2)))/Cube(0.96*msd2(2,2) - 1.02*
      msq2(2,2)) + (2*Log(Sqr(SCALE))*(6.72*msd2(2,2) + 5.1*msq2(2,2)))/Cube(0.96*
      msd2(2,2) - 1.02*msq2(2,2)) + (0.9803921568627451*(43.0848*msd2(2,2)*msq2(2,
      2) - 1.8432*Sqr(msd2(2,2)) + 6.2424*Sqr(msq2(2,2))))/(Cube(0.96*msd2(2,2) -
      1.02*msq2(2,2))*msq2(2,2))))) + Sqr(AbInput - MuInput*TanBeta)*(9*((1.9584*
      msd2(2,2)*msq2(2,2)*Sqr(Log(0.96*msd2(2,2))))/Cube(0.96*msd2(2,2) - 1.02*
      msq2(2,2)) - (1.9584*msd2(2,2)*msq2(2,2)*Sqr(Log(1.02*msq2(2,2))))/Cube(0.96
      *msd2(2,2) - 1.02*msq2(2,2)) + Log(0.96*msd2(2,2))*((-3.9168*Log(Sqr(SCALE))
      *msd2(2,2)*msq2(2,2))/Cube(0.96*msd2(2,2) - 1.02*msq2(2,2)) - (0.96*msd2(2,2
      ) + 1.02*msq2(2,2))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))) + Log(1.02*msq2(2,
      2))*((3.9168*Log(Sqr(SCALE))*msd2(2,2)*msq2(2,2))/Cube(0.96*msd2(2,2) - 1.02
      *msq2(2,2)) - (0.96*msd2(2,2) + 1.02*msq2(2,2))/Sqr(0.96*msd2(2,2) - 1.02*
      msq2(2,2))) + (2*Log(Sqr(SCALE))*(0.96*msd2(2,2) + 1.02*msq2(2,2)))/Sqr(0.96
      *msd2(2,2) - 1.02*msq2(2,2))) + 3*(-2.0833333333333335/msd2(2,2) + Log(Sqr(
      SCALE))*(-2.0833333333333335/msd2(2,2) + 2/(0.96*msd2(2,2) - 1.02*msq2(2,2))
      - 0.9803921568627451/msq2(2,2)) + 4/(0.96*msd2(2,2) - 1.02*msq2(2,2)) -
      0.9803921568627451/msq2(2,2) + (6*PolyLog(2,1 - (0.9411764705882352*msd2(2,2
      ))/msq2(2,2)))/(-0.96*msd2(2,2) + 1.02*msq2(2,2)) + (6*Sqr(Log(0.96*msd2(2,2
      ))))/(0.96*msd2(2,2) - 1.02*msq2(2,2)) - (2*(5.76*msd2(2,2) - 5.1*msq2(2,2))
      *Sqr(Log(1.02*msq2(2,2))))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) + Log(1.02*
      msq2(2,2))*((2*Log(Sqr(SCALE))*(8.64*msd2(2,2) - 8.16*msq2(2,2)))/Sqr(0.96*
      msd2(2,2) - 1.02*msq2(2,2)) + (1.0416666666666667*(-16.6464*msd2(2,2)*msq2(2
      ,2) + 17.5104*Sqr(msd2(2,2)) + 2.0808*Sqr(msq2(2,2))))/(msd2(2,2)*Sqr(0.96*
      msd2(2,2) - 1.02*msq2(2,2)))) + Log(0.96*msd2(2,2))*((-2*Log(Sqr(SCALE))*(
      8.64*msd2(2,2) - 8.16*msq2(2,2)))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (
      Log(1.02*msq2(2,2))*(5.76*msd2(2,2) - 4.08*msq2(2,2)))/Sqr(0.96*msd2(2,2) -
      1.02*msq2(2,2)) + (0.9803921568627451*(-20.563200000000002*msd2(2,2)*msq2(2,
      2) + 0.9216*Sqr(msd2(2,2)) + 16.6464*Sqr(msq2(2,2))))/(msq2(2,2)*Sqr(0.96*
      msd2(2,2) - 1.02*msq2(2,2)))))) + (1 + Sqr(TanBeta))*(Sqr(AbInput - MuInput*
      TanBeta)*(9*(Log(1.02*msq2(2,2))*(4/(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (4*
      Log(Sqr(SCALE)))/(0.96*msd2(2,2) - 1.02*msq2(2,2))) + Log(0.96*msd2(2,2))*(
      4/(-0.96*msd2(2,2) + 1.02*msq2(2,2)) + (4*Log(Sqr(SCALE)))/(-0.96*msd2(2,2)
      + 1.02*msq2(2,2)) - (4*Log(1.02*msq2(2,2))*(0.96*msd2(2,2) + 1.02*msq2(2,2))
      )/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))) + (3.84*msd2(2,2)*Sqr(Log(0.96*msd2(
      2,2))))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (4.08*msq2(2,2)*Sqr(Log(1.02*
      msq2(2,2))))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))) + 3*(4.12*Log(1.03*Sqr(
      MuInput))*Sqr(MuInput)*((1.0416666666666667*(0.9803921568627451/msq2(2,2) +
      1/(-0.96*msd2(2,2) + 1.02*msq2(2,2))))/msd2(2,2) + 1/((0.96*msd2(2,2) - 1.03
      *Sqr(MuInput))*(-1.02*msq2(2,2) + 1.03*Sqr(MuInput)))) + (2.0424836601307192
      *Log(Sqr(SCALE))*(-1.92*msd2(2,2)*(1.02*msq2(2,2) + 1.03*Sqr(MuInput)) +
      2.04*msq2(2,2)*(-1.02*msq2(2,2) + 2.06*Sqr(MuInput)) + 0.9216*Sqr(msd2(2,2))
      ))/(msd2(2,2)*(0.96*msd2(2,2) - 1.02*msq2(2,2))*msq2(2,2)) + Log(0.96*msd2(2
      ,2))*(-1.9607843137254901/msq2(2,2) - (2*Log(1.02*msq2(2,2))*(1.92*msd2(2,2)
      + 3.06*msq2(2,2)))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (Log(Sqr(SCALE))*
      (10.2*msq2(2,2) - 4*(0.96*msd2(2,2) + 1.03*Sqr(MuInput))))/Sqr(0.96*msd2(2,2
      ) - 1.02*msq2(2,2)) - (4*(0.96*msd2(2,2)*(-3.06*msq2(2,2) + 1.03*Sqr(MuInput
      )) - 1.03*Sqr(MuInput)*(-2.04*msq2(2,2) + 1.03*Sqr(MuInput)) + 0.9216*Sqr(
      msd2(2,2))))/((0.96*msd2(2,2) - 1.03*Sqr(MuInput))*Sqr(0.96*msd2(2,2) - 1.02
      *msq2(2,2)))) + (4*PolyLog(2,1 - (1.0098039215686274*Sqr(MuInput))/msq2(2,2)
      )*(1.02*msq2(2,2) - 1.03*Sqr(MuInput)))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))
      + (4*PolyLog(2,1 - (1.0729166666666667*Sqr(MuInput))/msd2(2,2))*(-1.02*msq2
      (2,2) + 1.03*Sqr(MuInput)))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (2*(1.92*
      msd2(2,2) - 1.02*msq2(2,2) + 1.03*Sqr(MuInput))*Sqr(Log(0.96*msd2(2,2))))
      /Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) + ((8.16*msq2(2,2) - 2.06*Sqr(MuInput)
      )*Sqr(Log(1.02*msq2(2,2))))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (
      -5.8751999999999995*msd2(2,2)*msq2(2,2) - 3.9552*msd2(2,2)*Sqr(MuInput) +
      8.4048*msq2(2,2)*Sqr(MuInput) + 1.8432*Sqr(msd2(2,2)) - 4.1616*Sqr(msq2(2,2)
      ))/(0.940032*msq2(2,2)*Sqr(msd2(2,2)) - 0.998784*msd2(2,2)*Sqr(msq2(2,2))) +
      Log(1.02*msq2(2,2))*((Log(Sqr(SCALE))*(-10.2*msq2(2,2) + 4*(0.96*msd2(2,2)
      + 1.03*Sqr(MuInput))))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (
      1.0416666666666667*(-4.244832*Cube(msq2(2,2)) - 1.9776*msd2(2,2)*Sqr(MuInput
      )*(0.96*msd2(2,2) + 2.06*Sqr(MuInput)) + 1.9584*msd2(2,2)*msq2(2,2)*(2.88*
      msd2(2,2) + 5.15*Sqr(MuInput)) + 2.0808*(-4.8*msd2(2,2) + 2.06*Sqr(MuInput))
      *Sqr(msq2(2,2))))/(msd2(2,2)*(1.02*msq2(2,2) - 1.03*Sqr(MuInput))*Sqr(0.96*
      msd2(2,2) - 1.02*msq2(2,2)))))) + Quad(AbInput - MuInput*TanBeta)*(3*((
      PolyLog(2,1 - (1.0729166666666667*Sqr(MuInput))/msd2(2,2))*(3.9168*msd2(2,2)
      *msq2(2,2) + 6.365399999999999*Quad(MuInput) + 4.08*msq2(2,2)*(1.02*msq2(2,2
      ) - 3.09*Sqr(MuInput)) - 1.8432*Sqr(msd2(2,2))))/Quad(0.96*msd2(2,2) - 1.02*
      msq2(2,2)) + Log(1.03*Sqr(MuInput))*((6.365399999999999*Log(1.02*msq2(2,2))*
      Quad(MuInput))/Quad(0.96*msd2(2,2) - 1.02*msq2(2,2)) - (2.103758169934641*
      Sqr(MuInput)*(-1.9584*msd2(2,2)*msq2(2,2) + 0.9216*Sqr(msd2(2,2)) - 2.0808*
      Sqr(msq2(2,2))))/(Cube(0.96*msd2(2,2) - 1.02*msq2(2,2))*msd2(2,2)*msq2(2,2))
      ) + (Sqr(Log(1.02*msq2(2,2)))*(-7.8336*msd2(2,2)*msq2(2,2) -
      3.1826999999999996*Quad(MuInput) + 6.303599999999999*msq2(2,2)*Sqr(MuInput)
      + 0.9216*Sqr(msd2(2,2)) - 10.404*Sqr(msq2(2,2))))/Quad(0.96*msd2(2,2) - 1.02
      *msq2(2,2)) + (2*PolyLog(2,1 - (1.0098039215686274*Sqr(MuInput))/msq2(2,2))*
      (-1.9584*msd2(2,2)*msq2(2,2) - 3.1826999999999996*Quad(MuInput) +
      6.303599999999999*msq2(2,2)*Sqr(MuInput) + 0.9216*Sqr(msd2(2,2)) - 2.0808*
      Sqr(msq2(2,2))))/Quad(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (Sqr(Log(0.96*msd2(
      2,2)))*(3.1826999999999996*Quad(MuInput) - 2.04*msq2(2,2)*(0.96*msd2(2,2) +
      3.09*Sqr(MuInput)) - 4.608*Sqr(msd2(2,2)) + 2.0808*Sqr(msq2(2,2))))/Quad(
      0.96*msd2(2,2) - 1.02*msq2(2,2)) + (1.0212418300653596*(-0.884736*Cube(msd2(
      2,2)) + 0.9792*msd2(2,2)*msq2(2,2)*(27.54*msq2(2,2) - 16.48*Sqr(MuInput)) +
      1.8432*(-5.1*msq2(2,2) + 1.03*Sqr(MuInput))*Sqr(msd2(2,2)) + 2.0808*(1.02*
      msq2(2,2) - 2.06*Sqr(MuInput))*Sqr(msq2(2,2))))/(Cube(0.96*msd2(2,2) - 1.02*
      msq2(2,2))*msd2(2,2)*msq2(2,2)) + (1.0212418300653596*Log(Sqr(SCALE))*(
      -0.884736*Cube(msd2(2,2)) + 0.9792*msd2(2,2)*msq2(2,2)*(19.38*msq2(2,2) -
      10.3*Sqr(MuInput)) + 1.8432*(-4.08*msq2(2,2) + 1.03*Sqr(MuInput))*Sqr(msd2(2
      ,2)) + 2.0808*(1.02*msq2(2,2) - 2.06*Sqr(MuInput))*Sqr(msq2(2,2))))/(Cube(
      0.96*msd2(2,2) - 1.02*msq2(2,2))*msd2(2,2)*msq2(2,2)) + Log(1.02*msq2(2,2))*
      ((-6*Log(Sqr(SCALE))*(-0.9792*msd2(2,2)*msq2(2,2) + 2.04*msq2(2,2)*(-1.02*
      msq2(2,2) + 1.03*Sqr(MuInput)) + 0.9216*Sqr(msd2(2,2))))/Quad(0.96*msd2(2,2)
      - 1.02*msq2(2,2)) + (1.0416666666666667*(-6.1931519999999995*Cube(msd2(2,2)
      ) + 2.122416*Cube(msq2(2,2)) - 5.8751999999999995*msd2(2,2)*msq2(2,2)*(0.96*
      msd2(2,2) + 3.09*Sqr(MuInput)) + 28.964736*msd2(2,2)*Sqr(msq2(2,2))))/(msd2(
      2,2)*Quad(0.96*msd2(2,2) - 1.02*msq2(2,2)))) + Log(0.96*msd2(2,2))*((
      -6.365399999999999*Log(1.03*Sqr(MuInput))*Quad(MuInput))/Quad(0.96*msd2(2,2)
      - 1.02*msq2(2,2)) + (6*Log(Sqr(SCALE))*(-0.9792*msd2(2,2)*msq2(2,2) + 2.04*
      msq2(2,2)*(-1.02*msq2(2,2) + 1.03*Sqr(MuInput)) + 0.9216*Sqr(msd2(2,2))))
      /Quad(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (2*Log(1.02*msq2(2,2))*(4.896*msd2(
      2,2)*msq2(2,2) + 1.8432*Sqr(msd2(2,2)) + 4.1616*Sqr(msq2(2,2))))/Quad(0.96*
      msd2(2,2) - 1.02*msq2(2,2)) + (0.9803921568627451*(0.884736*Cube(msd2(2,2))
      + 2.9375999999999998*msd2(2,2)*msq2(2,2)*(-7.140000000000001*msq2(2,2) +
      2.06*Sqr(MuInput)) + 13.160447999999999*msq2(2,2)*Sqr(msd2(2,2)) + 12.4848*(
      -1.02*msq2(2,2) + 1.03*Sqr(MuInput))*Sqr(msq2(2,2))))/(msq2(2,2)*Quad(0.96*
      msd2(2,2) - 1.02*msq2(2,2))))) + 9*(Log(1.02*msq2(2,2))*((-4*Log(Sqr(SCALE))
      *(0.96*msd2(2,2) + 1.02*msq2(2,2)))/Cube(0.96*msd2(2,2) - 1.02*msq2(2,2)) -
      (4*(0.96*msd2(2,2) + 3.06*msq2(2,2)))/Cube(0.96*msd2(2,2) - 1.02*msq2(2,2)))
      - (3.84*msd2(2,2)*(0.96*msd2(2,2) + 1.02*msq2(2,2))*Sqr(Log(0.96*msd2(2,2))
      ))/Quad(0.96*msd2(2,2) - 1.02*msq2(2,2)) - (4.08*msq2(2,2)*(0.96*msd2(2,2) +
      1.02*msq2(2,2))*Sqr(Log(1.02*msq2(2,2))))/Quad(0.96*msd2(2,2) - 1.02*msq2(2
      ,2)) - 8/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) - (8*Log(Sqr(SCALE)))/Sqr(0.96
      *msd2(2,2) - 1.02*msq2(2,2)) + Log(0.96*msd2(2,2))*((4*Log(Sqr(SCALE))*(0.96
      *msd2(2,2) + 1.02*msq2(2,2)))/Cube(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (4*(
      2.88*msd2(2,2) + 1.02*msq2(2,2)))/Cube(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (4
      *Log(1.02*msq2(2,2))*Sqr(0.96*msd2(2,2) + 1.02*msq2(2,2)))/Quad(0.96*msd2(2,
      2) - 1.02*msq2(2,2))))) + 3*(-2.5 + 0.96*msd2(2,2)*(-0.9803921568627451/msq2
      (2,2) + 1/(0.96*msd2(2,2) - 1.03*Sqr(MuInput))) + 2.06*(
      0.9803921568627451/msq2(2,2) + 1/(1.02*msq2(2,2) - 1.03*Sqr(MuInput)))*Sqr(
      MuInput) + (1.0416666666666667*(-2.04*msq2(2,2) + 4.12*Sqr(MuInput)))/msd2(2
      ,2) + Log(Sqr(SCALE))*(2 - (2.125*msq2(2,2))/msd2(2,2) - (0.9803921568627451
      *(0.96*msd2(2,2) - 2.06*Sqr(MuInput)))/msq2(2,2) + (4.291666666666667*Sqr(
      MuInput))/msd2(2,2) + (1.92*msd2(2,2))/(-0.96*msd2(2,2) + 1.03*Sqr(MuInput))
      + (4.12*Sqr(MuInput))/(-1.02*msq2(2,2) + 1.03*Sqr(MuInput))) + 4*Sqr(Log(
      Sqr(SCALE))) + Log(0.96*msd2(2,2))*(2*Log(1.02*msq2(2,2)) + (
      0.9411764705882352*msd2(2,2))/msq2(2,2) + (2.1218*Log(1.03*Sqr(MuInput))*
      Quad(MuInput))/Sqr(0.96*msd2(2,2) - 1.03*Sqr(MuInput)) + (2.1218*Quad(
      MuInput) + 1.9776*msd2(2,2)*Sqr(MuInput) - 0.9216*Sqr(msd2(2,2)))/Sqr(0.96*
      msd2(2,2) - 1.03*Sqr(MuInput)) - (2*Log(Sqr(SCALE))*(1.0609*Quad(MuInput) -
      3.9552*msd2(2,2)*Sqr(MuInput) + 1.8432*Sqr(msd2(2,2))))/Sqr(0.96*msd2(2,2) -
      1.03*Sqr(MuInput))) + (2*PolyLog(2,1 - (1.0729166666666667*Sqr(MuInput))
      /msd2(2,2))*(-1.0609*Quad(MuInput) - 1.9776*msd2(2,2)*Sqr(MuInput) + 0.9216*
      Sqr(msd2(2,2))))/Sqr(0.96*msd2(2,2) - 1.03*Sqr(MuInput)) + (Sqr(Log(0.96*
      msd2(2,2)))*(-1.0609*Quad(MuInput) - 1.9776*msd2(2,2)*Sqr(MuInput) + 0.9216*
      Sqr(msd2(2,2))))/Sqr(0.96*msd2(2,2) - 1.03*Sqr(MuInput)) + PolyLog(2,1 - (
      1.0098039215686274*Sqr(MuInput))/msq2(2,2))*(2 - (8.4872*Quad(MuInput))/Sqr(
      -1.02*msq2(2,2) + 1.03*Sqr(MuInput))) + Sqr(Log(1.02*msq2(2,2)))*(1 - (
      4.2436*Quad(MuInput))/Sqr(-1.02*msq2(2,2) + 1.03*Sqr(MuInput))) + Log(1.03*
      Sqr(MuInput))*(2.1218*Log(Sqr(SCALE))*Quad(MuInput)*(-(1/Sqr(0.96*msd2(2,2)
      - 1.03*Sqr(MuInput))) - 2/Sqr(-1.02*msq2(2,2) + 1.03*Sqr(MuInput))) + 1.03*
      Sqr(MuInput)*(-1.9607843137254901/msq2(2,2) + (1.0416666666666667*(-4.2436*
      Quad(MuInput) + 2.9664*msd2(2,2)*Sqr(MuInput) - 1.8432*Sqr(msd2(2,2))))/(
      msd2(2,2)*Sqr(0.96*msd2(2,2) - 1.03*Sqr(MuInput))) - (6.18*Sqr(MuInput))/Sqr
      (-1.02*msq2(2,2) + 1.03*Sqr(MuInput))) + (4.2436*Log(1.02*msq2(2,2))*Quad(
      MuInput))/Sqr(-1.02*msq2(2,2) + 1.03*Sqr(MuInput))) + Log(1.02*msq2(2,2))*((
      2.125*msq2(2,2))/msd2(2,2) + Log(Sqr(SCALE))*(-4 + (4.2436*Quad(MuInput))
      /Sqr(-1.02*msq2(2,2) + 1.03*Sqr(MuInput))) + (3.1826999999999996*Quad(
      MuInput) + 2.1012*msq2(2,2)*Sqr(MuInput) + 1.0404*Sqr(msq2(2,2)))/Sqr(-1.02*
      msq2(2,2) + 1.03*Sqr(MuInput))))) + Sqr(TanBeta)*(3*Sqr(AbInput +
      MuInput/TanBeta)*(-2.0833333333333335/msd2(2,2) + Log(Sqr(SCALE))*(
      -2.0833333333333335/msd2(2,2) - 0.9803921568627451/msq2(2,2)) -
      0.9803921568627451/msq2(2,2) + (0.5106209150326798*Log(0.96*msd2(2,2))*(
      0.9411919999999999*Power6(mAInput) + 0.9603999999999999*(-4.8*msd2(2,2) +
      1.02*msq2(2,2))*Quad(mAInput) + 4.9*Sqr(mAInput)*(-1.9584*msd2(2,2)*msq2(2,2
      ) + 0.9216*Sqr(msd2(2,2)) - 1.0404*Sqr(msq2(2,2))) - (0.96*msd2(2,2) - 1.02*
      msq2(2,2))*(-5.8751999999999995*msd2(2,2)*msq2(2,2) + 0.9216*Sqr(msd2(2,2))
      + 3.1212*Sqr(msq2(2,2))) - (-2.88*msd2(2,2) + 3.06*msq2(2,2) + 0.98*Sqr(
      mAInput))*TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2))))/(msd2(2,
      2)*msq2(2,2)*TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2))) - (
      0.5425347222222222*Log(1.02*msq2(2,2))*(-1.8823839999999998*Power6(mAInput)
      + 0.9603999999999999*(6.72*msd2(2,2) + 6.12*msq2(2,2))*Quad(mAInput) + (0.96
      *msd2(2,2) - 1.02*msq2(2,2))*(2.9375999999999998*msd2(2,2)*msq2(2,2) +
      0.9216*Sqr(msd2(2,2)) - 2.0808*Sqr(msq2(2,2))) - 1.96*Sqr(mAInput)*(0.9792*
      msd2(2,2)*msq2(2,2) + 0.9216*Sqr(msd2(2,2)) + 3.1212*Sqr(msq2(2,2))) + (
      -2.88*msd2(2,2) - 2.04*msq2(2,2) + 1.96*Sqr(mAInput))*TDelta(0.98*Sqr(
      mAInput),1.02*msq2(2,2),0.96*msd2(2,2))))/(Sqr(msd2(2,2))*TDelta(0.98*Sqr(
      mAInput),1.02*msq2(2,2),0.96*msd2(2,2))) + (0.5318967864923747*Log(0.98*Sqr(
      mAInput))*(-0.9411919999999999*(0.96*msd2(2,2) + 2.04*msq2(2,2))*Power6(
      mAInput) + Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))*(-3.9168*msd2(2,2)*msq2(2,2)
      + 0.9216*Sqr(msd2(2,2)) + 2.0808*Sqr(msq2(2,2))) + 0.9603999999999999*Quad(
      mAInput)*(5.8751999999999995*msd2(2,2)*msq2(2,2) + 4.608*Sqr(msd2(2,2)) +
      6.2424*Sqr(msq2(2,2))) + 0.98*Sqr(mAInput)*(-4.42368*Cube(msd2(2,2)) -
      6.367248*Cube(msq2(2,2)) + 7.520256*msq2(2,2)*Sqr(msd2(2,2)) + 2.996352*msd2
      (2,2)*Sqr(msq2(2,2))) + (0.96*msd2(2,2)*(-0.96*msd2(2,2) + 0.98*Sqr(mAInput)
      ) + 2.04*msq2(2,2)*(1.92*msd2(2,2) + 0.98*Sqr(mAInput)) - 2.0808*Sqr(msq2(2,
      2)))*TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2))))/(msq2(2,2)*
      Sqr(msd2(2,2))*TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2))) + (
      0.5651403356481481*(-7.529535999999999*(0.96*msd2(2,2) + 1.02*msq2(2,2))*
      Power6(mAInput) + 1.8447363199999998*Power8(mAInput) - 1.96*(0.96*msd2(2,2)
      - 1.02*msq2(2,2))*Sqr(mAInput)*(2.7648*Sqr(msd2(2,2)) - 4.1616*Sqr(msq2(2,2)
      )) + Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))*(-3.9168*msd2(2,2)*msq2(2,2) +
      0.9216*Sqr(msd2(2,2)) + 2.0808*Sqr(msq2(2,2))) + 0.9603999999999999*Quad(
      mAInput)*(7.8336*msd2(2,2)*msq2(2,2) + 6.4512*Sqr(msd2(2,2)) + 12.4848*Sqr(
      msq2(2,2))) + TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2))*(
      11.750399999999999*msd2(2,2)*msq2(2,2) - 5.7623999999999995*Quad(mAInput) +
      11.76*(0.96*msd2(2,2) + 1.02*msq2(2,2))*Sqr(mAInput) - 4.608*Sqr(msd2(2,2))
      - 6.2424*Sqr(msq2(2,2)) + 4*TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*
      msd2(2,2))))*TPhi(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2)))/(Cube(
      msd2(2,2))*TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2)))) + 3*(
      1.5 + Log(1.02*msq2(2,2))*(-6 - 6*Log(Sqr(SCALE))) + Log(0.96*msd2(2,2))*(-4
      - 4*Log(Sqr(SCALE))) + Sqr(3.141592653589793) - (2.041666666666667*Sqr(
      mAInput))/msd2(2,2) - (0.9607843137254901*Sqr(mAInput))/msq2(2,2) + Log(Sqr(
      SCALE))*(3 - 0.98*(2.0833333333333335/msd2(2,2) + 0.9803921568627451/msq2(2,
      2))*Sqr(mAInput)) + Log(0.98*Sqr(mAInput))*(7 - 6*Log(Sqr(SCALE)) + 0.98*(
      2.0833333333333335/msd2(2,2) + 0.9803921568627451/msq2(2,2))*Sqr(mAInput)) +
      3*Sqr(Log(0.98*Sqr(mAInput))) + 8*Sqr(Log(Sqr(SCALE))) + 2*Sqr(Log(0.96*
      msd2(2,2))) + 3*Sqr(Log(1.02*msq2(2,2))) + (1.0850694444444444*(
      0.9603999999999999*Quad(mAInput) - 5.6448*msd2(2,2)*Sqr(mAInput) - TDelta(
      0.98*Sqr(mAInput),0.96*msd2(2,2),0.96*msd2(2,2)))*TPhi(0.98*Sqr(mAInput),
      0.96*msd2(2,2),0.96*msd2(2,2)))/Sqr(msd2(2,2)) + (0.9611687812379854*(
      1.9207999999999998*Quad(mAInput) - 10.9956*msq2(2,2)*Sqr(mAInput) - 2*TDelta
      (0.98*Sqr(mAInput),1.02*msq2(2,2),1.02*msq2(2,2)))*TPhi(0.98*Sqr(mAInput),
      1.02*msq2(2,2),1.02*msq2(2,2)))/Sqr(msq2(2,2))) + 3*(AbInput +
      MuInput/TanBeta)*(AbInput - MuInput*TanBeta)*(Log(1.02*msq2(2,2))*(12/(0.96*
      msd2(2,2) - 1.02*msq2(2,2)) + (12*Log(Sqr(SCALE)))/(0.96*msd2(2,2) - 1.02*
      msq2(2,2))) + Log(0.98*Sqr(mAInput))*((2*Log(0.96*msd2(2,2)))/(0.96*msd2(2,2
      ) - 1.02*msq2(2,2)) + (2*Log(1.02*msq2(2,2)))/(-0.96*msd2(2,2) + 1.02*msq2(2
      ,2))) + Log(0.96*msd2(2,2))*((2*Log(1.02*msq2(2,2)))/(0.96*msd2(2,2) - 1.02*
      msq2(2,2)) + 12/(-0.96*msd2(2,2) + 1.02*msq2(2,2)) + (12*Log(Sqr(SCALE)))/(
      -0.96*msd2(2,2) + 1.02*msq2(2,2))) + (4*Sqr(Log(0.96*msd2(2,2))))/(0.96*msd2
      (2,2) - 1.02*msq2(2,2)) + (6*Sqr(Log(1.02*msq2(2,2))))/(-0.96*msd2(2,2) +
      1.02*msq2(2,2)) - (2.170138888888889*(-0.98*(-5.76*msd2(2,2) + 0.98*Sqr(
      mAInput))*Sqr(mAInput) + TDelta(0.98*Sqr(mAInput),0.96*msd2(2,2),0.96*msd2(2
      ,2)))*TPhi(0.98*Sqr(mAInput),0.96*msd2(2,2),0.96*msd2(2,2)))/((0.96*msd2(2,2
      ) - 1.02*msq2(2,2))*Sqr(msd2(2,2))) + (2.170138888888889*(
      -2.9375999999999998*msd2(2,2)*msq2(2,2) + 0.9603999999999999*Quad(mAInput) -
      2.8224*msd2(2,2)*Sqr(mAInput) - 1.9992*msq2(2,2)*Sqr(mAInput) + 1.8432*Sqr(
      msd2(2,2)) + 1.0404*Sqr(msq2(2,2)) - TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2)
      ,0.96*msd2(2,2)))*TPhi(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2)))/((
      0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(msd2(2,2))) + (0.9611687812379854*(
      -3.8415999999999997*Quad(mAInput) + 21.9912*msq2(2,2)*Sqr(mAInput) + 4*
      TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),1.02*msq2(2,2)))*TPhi(0.98*Sqr(
      mAInput),1.02*msq2(2,2),1.02*msq2(2,2)))/((0.96*msd2(2,2) - 1.02*msq2(2,2))*
      Sqr(msq2(2,2)))) + 3*(AbInput + MuInput/TanBeta)*Cube(AbInput - MuInput*
      TanBeta)*(Log(1.02*msq2(2,2))*((-12*Log(Sqr(SCALE))*(0.96*msd2(2,2) + 1.02*
      msq2(2,2)))/Cube(0.96*msd2(2,2) - 1.02*msq2(2,2)) - (12*(0.96*msd2(2,2) +
      3.06*msq2(2,2)))/Cube(0.96*msd2(2,2) - 1.02*msq2(2,2))) + Log(0.96*msd2(2,2)
      )*((12*Log(Sqr(SCALE))*(0.96*msd2(2,2) + 1.02*msq2(2,2)))/Cube(0.96*msd2(2,2
      ) - 1.02*msq2(2,2)) + (12*(2.88*msd2(2,2) + 1.02*msq2(2,2)))/Cube(0.96*msd2(
      2,2) - 1.02*msq2(2,2)) - (2*Log(1.02*msq2(2,2))*(0.96*msd2(2,2) + 3.06*msq2(
      2,2) - 1.96*Sqr(mAInput)))/Cube(0.96*msd2(2,2) - 1.02*msq2(2,2))) + Log(0.98
      *Sqr(mAInput))*((-2*Log(0.96*msd2(2,2))*(0.96*msd2(2,2) - 1.02*msq2(2,2) +
      5.88*Sqr(mAInput)))/Cube(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (2*Log(1.02*msq2
      (2,2))*(0.96*msd2(2,2) - 1.02*msq2(2,2) + 5.88*Sqr(mAInput)))/Cube(0.96*msd2
      (2,2) - 1.02*msq2(2,2))) + (4*(-0.96*msd2(2,2) - 1.02*msq2(2,2) + 0.98*Sqr(
      mAInput))*Sqr(Log(0.96*msd2(2,2))))/Cube(0.96*msd2(2,2) - 1.02*msq2(2,2)) +
      (2*(2.88*msd2(2,2) + 5.1*msq2(2,2) - 3.92*Sqr(mAInput))*Sqr(Log(1.02*msq2(2,
      2))))/Cube(0.96*msd2(2,2) - 1.02*msq2(2,2)) - 48/Sqr(0.96*msd2(2,2) - 1.02*
      msq2(2,2)) - (24*Log(Sqr(SCALE)))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (
      2.170138888888889*(0.98*(0.96*msd2(2,2) - 1.02*msq2(2,2))*(-5.76*msd2(2,2) +
      0.98*Sqr(mAInput))*Sqr(mAInput) + (-2.88*msd2(2,2) + 1.02*msq2(2,2))*TDelta
      (0.98*Sqr(mAInput),0.96*msd2(2,2),0.96*msd2(2,2)))*TPhi(0.98*Sqr(mAInput),
      0.96*msd2(2,2),0.96*msd2(2,2)))/(Cube(0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(
      msd2(2,2))) + (2.170138888888889*((0.96*msd2(2,2) - 1.02*msq2(2,2))*(
      -2.9375999999999998*msd2(2,2)*msq2(2,2) + 0.9603999999999999*Quad(mAInput) -
      2.8224*msd2(2,2)*Sqr(mAInput) - 1.9992*msq2(2,2)*Sqr(mAInput) + 1.8432*Sqr(
      msd2(2,2)) + 1.0404*Sqr(msq2(2,2))) + (-2.88*msd2(2,2) + 1.02*msq2(2,2))*
      TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2)))*TPhi(0.98*Sqr(
      mAInput),1.02*msq2(2,2),0.96*msd2(2,2)))/(Cube(0.96*msd2(2,2) - 1.02*msq2(2,
      2))*Sqr(msd2(2,2))) + (0.9611687812379854*(1.96*(0.96*msd2(2,2) - 1.02*msq2(
      2,2))*Sqr(mAInput)*(-11.22*msq2(2,2) + 1.96*Sqr(mAInput)) - 4*(0.96*msd2(2,2
      ) - 3.06*msq2(2,2))*TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),1.02*msq2(2,2)))
      *TPhi(0.98*Sqr(mAInput),1.02*msq2(2,2),1.02*msq2(2,2)))/(Cube(0.96*msd2(2,2)
      - 1.02*msq2(2,2))*Sqr(msq2(2,2)))) + Quad(AbInput - MuInput*TanBeta)*(3*(
      Log(0.96*msd2(2,2))*((-5.9976*msq2(2,2)*Sqr(mAInput))/Quad(0.96*msd2(2,2) -
      1.02*msq2(2,2)) - (5.9976*Log(Sqr(SCALE))*msq2(2,2)*Sqr(mAInput))/Quad(0.96*
      msd2(2,2) - 1.02*msq2(2,2))) + Log(1.02*msq2(2,2))*((5.9976*msq2(2,2)*Sqr(
      mAInput))/Quad(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (5.9976*Log(Sqr(SCALE))*
      msq2(2,2)*Sqr(mAInput))/Quad(0.96*msd2(2,2) - 1.02*msq2(2,2))) + Log(0.98*
      Sqr(mAInput))*((5.9976*Log(0.96*msd2(2,2))*msq2(2,2)*Sqr(mAInput))/Quad(0.96
      *msd2(2,2) - 1.02*msq2(2,2)) - (5.9976*Log(1.02*msq2(2,2))*msq2(2,2)*Sqr(
      mAInput))/Quad(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (1.0008169934640525*Sqr(
      mAInput)*(-4.896*msd2(2,2)*msq2(2,2) + 0.9216*Sqr(msd2(2,2)) - 2.0808*Sqr(
      msq2(2,2))))/(Cube(0.96*msd2(2,2) - 1.02*msq2(2,2))*msd2(2,2)*msq2(2,2))) +
      (1.0008169934640525*Sqr(mAInput)*(4.896*msd2(2,2)*msq2(2,2) - 0.9216*Sqr(
      msd2(2,2)) + 2.0808*Sqr(msq2(2,2))))/(Cube(0.96*msd2(2,2) - 1.02*msq2(2,2))*
      msd2(2,2)*msq2(2,2)) + (1.0008169934640525*Log(Sqr(SCALE))*Sqr(mAInput)*(
      4.896*msd2(2,2)*msq2(2,2) - 0.9216*Sqr(msd2(2,2)) + 2.0808*Sqr(msq2(2,2))))/
      (Cube(0.96*msd2(2,2) - 1.02*msq2(2,2))*msd2(2,2)*msq2(2,2))) + 3*Sqr(AbInput
      + MuInput/TanBeta)*((-2*(2.88*msd2(2,2) + 1.02*msq2(2,2) - 1.96*Sqr(mAInput
      ))*Sqr(Log(0.96*msd2(2,2))))/Quad(0.96*msd2(2,2) - 1.02*msq2(2,2)) + ((-2.88
      *msd2(2,2) - 11.22*msq2(2,2) + 6.859999999999999*Sqr(mAInput))*Sqr(Log(1.02*
      msq2(2,2))))/Quad(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (1.0212418300653596*Log
      (Sqr(SCALE))*(4.896*msd2(2,2)*msq2(2,2) - 0.9216*Sqr(msd2(2,2)) + 2.0808*Sqr
      (msq2(2,2))))/(Cube(0.96*msd2(2,2) - 1.02*msq2(2,2))*msd2(2,2)*msq2(2,2)) +
      (1.0212418300653596*(10.7712*msd2(2,2)*msq2(2,2) - 0.9216*Sqr(msd2(2,2)) +
      2.0808*Sqr(msq2(2,2))))/(Cube(0.96*msd2(2,2) - 1.02*msq2(2,2))*msd2(2,2)*
      msq2(2,2)) + Log(0.98*Sqr(mAInput))*((3*Log(0.96*msd2(2,2))*(0.96*msd2(2,2)
      - 1.02*msq2(2,2) + 0.98*Sqr(mAInput)))/Quad(0.96*msd2(2,2) - 1.02*msq2(2,2))
      - (3*Log(1.02*msq2(2,2))*(0.96*msd2(2,2) - 1.02*msq2(2,2) + 0.98*Sqr(
      mAInput)))/Quad(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (0.5318967864923747*(
      0.9411919999999999*(0.96*msd2(2,2) - 2.04*msq2(2,2))*Power6(mAInput) - Sqr(
      0.96*msd2(2,2) - 1.02*msq2(2,2))*(3.9168*msd2(2,2)*msq2(2,2) + 2.7648*Sqr(
      msd2(2,2)) - 2.0808*Sqr(msq2(2,2))) + 0.9603999999999999*Quad(mAInput)*(
      1.9584*msd2(2,2)*msq2(2,2) - 2.7648*Sqr(msd2(2,2)) + 6.2424*Sqr(msq2(2,2)))
      + 0.98*(0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(mAInput)*(0.9792*msd2(2,2)*msq2
      (2,2) + 4.608*Sqr(msd2(2,2)) + 6.2424*Sqr(msq2(2,2))) + (3.9168*msd2(2,2)*
      msq2(2,2) - 0.9408*msd2(2,2)*Sqr(mAInput) + 1.9992*msq2(2,2)*Sqr(mAInput) +
      2.7648*Sqr(msd2(2,2)) - 2.0808*Sqr(msq2(2,2)))*TDelta(0.98*Sqr(mAInput),1.02
      *msq2(2,2),0.96*msd2(2,2))))/(msq2(2,2)*Sqr(msd2(2,2))*Sqr(0.96*msd2(2,2) -
      1.02*msq2(2,2))*TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2)))) +
      Log(1.02*msq2(2,2))*((6.12*Log(Sqr(SCALE))*msq2(2,2))/Quad(0.96*msd2(2,2) -
      1.02*msq2(2,2)) + (0.5425347222222222*(Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))*
      (1.8823839999999998*Power6(mAInput) - 2.8811999999999998*(2.88*msd2(2,2) +
      2.04*msq2(2,2))*Quad(mAInput) - (0.96*msd2(2,2) - 1.02*msq2(2,2))*(0.9792*
      msd2(2,2)*msq2(2,2) + 10.137599999999999*Sqr(msd2(2,2)) - 2.0808*Sqr(msq2(2,
      2))) + 1.96*Sqr(mAInput)*(2.9375999999999998*msd2(2,2)*msq2(2,2) + 6.4512*
      Sqr(msd2(2,2)) + 3.1212*Sqr(msq2(2,2)))) + (4.42368*Cube(msd2(2,2)) +
      2.122416*Cube(msq2(2,2)) + 15.040512*msq2(2,2)*Sqr(msd2(2,2)) - 1.96*Sqr(
      mAInput)*Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) + 0.998784*msd2(2,2)*Sqr(msq2(
      2,2)))*TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2))))/(Quad(0.96*
      msd2(2,2) - 1.02*msq2(2,2))*Sqr(msd2(2,2))*TDelta(0.98*Sqr(mAInput),1.02*
      msq2(2,2),0.96*msd2(2,2)))) + Log(0.96*msd2(2,2))*((-6.12*Log(Sqr(SCALE))*
      msq2(2,2))/Quad(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (Log(1.02*msq2(2,2))*(
      8.64*msd2(2,2) + 13.26*msq2(2,2) - 10.78*Sqr(mAInput)))/Quad(0.96*msd2(2,2)
      - 1.02*msq2(2,2)) + (0.5106209150326798*(Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)
      )*(-0.9411919999999999*Power6(mAInput) + 0.9603999999999999*(2.88*msd2(2,2)
      + 7.140000000000001*msq2(2,2))*Quad(mAInput) + (0.96*msd2(2,2) - 1.02*msq2(2
      ,2))*(11.750399999999999*msd2(2,2)*msq2(2,2) + 2.7648*Sqr(msd2(2,2)) - 5.202
      *Sqr(msq2(2,2))) - 0.98*Sqr(mAInput)*(9.792*msd2(2,2)*msq2(2,2) + 4.608*Sqr(
      msd2(2,2)) + 11.4444*Sqr(msq2(2,2)))) - (0.884736*Cube(msd2(2,2)) +
      5.306039999999999*Cube(msq2(2,2)) + 14.10048*msq2(2,2)*Sqr(msd2(2,2)) - 0.98
      *Sqr(mAInput)*Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) + 2.996352*msd2(2,2)*Sqr(
      msq2(2,2)))*TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2))))/(msd2(
      2,2)*msq2(2,2)*Quad(0.96*msd2(2,2) - 1.02*msq2(2,2))*TDelta(0.98*Sqr(mAInput
      ),1.02*msq2(2,2),0.96*msd2(2,2)))) + (1.0850694444444444*(0.98*(0.96*msd2(2,
      2) - 1.02*msq2(2,2))*(-5.76*msd2(2,2) + 0.98*Sqr(mAInput))*Sqr(mAInput) + (
      -4.8*msd2(2,2) + 1.02*msq2(2,2))*TDelta(0.98*Sqr(mAInput),0.96*msd2(2,2),
      0.96*msd2(2,2)))*TPhi(0.98*Sqr(mAInput),0.96*msd2(2,2),0.96*msd2(2,2)))/(
      Quad(0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(msd2(2,2))) + (0.5651403356481481*
      (Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))*(-7.529535999999999*(0.96*msd2(2,2) +
      1.02*msq2(2,2))*Power6(mAInput) + 1.8447363199999998*Power8(mAInput) - 1.96*
      (0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(mAInput)*(2.7648*Sqr(msd2(2,2)) -
      4.1616*Sqr(msq2(2,2))) - Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))*(3.9168*msd2(2
      ,2)*msq2(2,2) + 2.7648*Sqr(msd2(2,2)) - 2.0808*Sqr(msq2(2,2))) +
      0.9603999999999999*Quad(mAInput)*(7.8336*msd2(2,2)*msq2(2,2) +
      10.137599999999999*Sqr(msd2(2,2)) + 12.4848*Sqr(msq2(2,2)))) + 2*(
      -8.812800000000001*msd2(2,2)*msq2(2,2) + 16.5888*Sqr(msd2(2,2)) + 2.0808*Sqr
      (msq2(2,2)))*Sqr(TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2))) -
      (0.96*msd2(2,2) - 1.02*msq2(2,2))*(1.9207999999999998*(7.68*msd2(2,2) - 3.06
      *msq2(2,2))*Quad(mAInput) - 3.92*Sqr(mAInput)*(4.896*msd2(2,2)*msq2(2,2) +
      8.2944*Sqr(msd2(2,2)) - 3.1212*Sqr(msq2(2,2))) + (0.96*msd2(2,2) - 1.02*msq2
      (2,2))*(-21.542399999999997*msd2(2,2)*msq2(2,2) + 24.8832*Sqr(msd2(2,2)) +
      6.2424*Sqr(msq2(2,2))))*TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,
      2)))*TPhi(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2)))/(Cube(msd2(2,2))
      *Quad(0.96*msd2(2,2) - 1.02*msq2(2,2))*TDelta(0.98*Sqr(mAInput),1.02*msq2(2,
      2),0.96*msd2(2,2))) + (0.9611687812379854*(0.98*(-0.96*msd2(2,2) + 1.02*msq2
      (2,2))*Sqr(mAInput)*(-11.22*msq2(2,2) + 1.96*Sqr(mAInput)) + (1.92*msd2(2,2)
      - 9.18*msq2(2,2))*TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),1.02*msq2(2,2)))*
      TPhi(0.98*Sqr(mAInput),1.02*msq2(2,2),1.02*msq2(2,2)))/(Quad(0.96*msd2(2,2)
      - 1.02*msq2(2,2))*Sqr(msq2(2,2))))) + Sqr(AbInput - MuInput*TanBeta)*(3*Sqr(
      AbInput + MuInput/TanBeta)*((2*Sqr(Log(0.96*msd2(2,2))))/Sqr(0.96*msd2(2,2)
      - 1.02*msq2(2,2)) + (3*Sqr(Log(1.02*msq2(2,2))))/Sqr(0.96*msd2(2,2) - 1.02*
      msq2(2,2)) + (1.92*msd2(2,2) - 4.08*msq2(2,2))/(0.940032*msq2(2,2)*Sqr(msd2(
      2,2)) - 0.998784*msd2(2,2)*Sqr(msq2(2,2))) + (Log(Sqr(SCALE))*(1.92*msd2(2,2
      ) - 4.08*msq2(2,2)))/(0.940032*msq2(2,2)*Sqr(msd2(2,2)) - 0.998784*msd2(2,2)
      *Sqr(msq2(2,2))) + Log(0.98*Sqr(mAInput))*(-(Log(0.96*msd2(2,2))/Sqr(0.96*
      msd2(2,2) - 1.02*msq2(2,2))) + Log(1.02*msq2(2,2))/Sqr(0.96*msd2(2,2) - 1.02
      *msq2(2,2)) - (1.0637935729847494*((0.96*msd2(2,2) - 1.02*msq2(2,2) + 0.98*
      Sqr(mAInput))*(1.9592159999999998*msq2(2,2)*Quad(mAInput) + 0.98*Sqr(mAInput
      )*(-5.8751999999999995*msd2(2,2)*msq2(2,2) + 0.9216*Sqr(msd2(2,2)) - 4.1616*
      Sqr(msq2(2,2))) - (0.96*msd2(2,2) - 1.02*msq2(2,2))*(-3.9168*msd2(2,2)*msq2(
      2,2) + 0.9216*Sqr(msd2(2,2)) + 2.0808*Sqr(msq2(2,2)))) + (-3.9168*msd2(2,2)*
      msq2(2,2) + 2.04*msq2(2,2)*(1.02*msq2(2,2) - 0.98*Sqr(mAInput)) + 0.9216*Sqr
      (msd2(2,2)))*TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2))))/((
      0.96*msd2(2,2) - 1.02*msq2(2,2))*msq2(2,2)*Sqr(msd2(2,2))*TDelta(0.98*Sqr(
      mAInput),1.02*msq2(2,2),0.96*msd2(2,2)))) + Log(0.96*msd2(2,2))*((-5*Log(
      1.02*msq2(2,2)))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (2*Log(Sqr(SCALE)))
      /Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (1.0212418300653596*((0.96*msd2(2,2)
      - 1.02*msq2(2,2))*(0.9603999999999999*(0.96*msd2(2,2) + 4.08*msq2(2,2))*
      Quad(mAInput) - 1.9992*msq2(2,2)*(6.72*msd2(2,2) + 4.08*msq2(2,2))*Sqr(
      mAInput) - (0.96*msd2(2,2) - 1.02*msq2(2,2))*(-6.8544*msd2(2,2)*msq2(2,2) +
      0.9216*Sqr(msd2(2,2)) + 4.1616*Sqr(msq2(2,2)))) - (0.9792*msd2(2,2)*msq2(2,2
      ) + 0.9216*Sqr(msd2(2,2)) - 4.1616*Sqr(msq2(2,2)))*TDelta(0.98*Sqr(mAInput),
      1.02*msq2(2,2),0.96*msd2(2,2))))/(msd2(2,2)*msq2(2,2)*Sqr(0.96*msd2(2,2) -
      1.02*msq2(2,2))*TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2)))) +
      Log(1.02*msq2(2,2))*((-2*Log(Sqr(SCALE)))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2
      )) + (1.0850694444444444*(-2*(0.96*msd2(2,2) - 1.02*msq2(2,2))*(0.884736*
      Cube(msd2(2,2)) + 1.061208*Cube(msq2(2,2)) - 0.9411919999999999*Power6(
      mAInput) + 0.9603999999999999*(3.84*msd2(2,2) + 3.06*msq2(2,2))*Quad(mAInput
      ) - 1.997568*msd2(2,2)*Sqr(msq2(2,2)) - 0.98*Sqr(mAInput)*(1.9584*msd2(2,2)*
      msq2(2,2) + 5.5296*Sqr(msd2(2,2)) + 3.1212*Sqr(msq2(2,2)))) - 2*(0.9792*msd2
      (2,2)*msq2(2,2) + 0.98*(0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(mAInput) -
      0.9216*Sqr(msd2(2,2)) + 1.0404*Sqr(msq2(2,2)))*TDelta(0.98*Sqr(mAInput),1.02
      *msq2(2,2),0.96*msd2(2,2))))/(Sqr(msd2(2,2))*Sqr(0.96*msd2(2,2) - 1.02*msq2(
      2,2))*TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2)))) + (
      1.0850694444444444*(0.98*(-5.76*msd2(2,2) + 0.98*Sqr(mAInput))*Sqr(mAInput)
      - TDelta(0.98*Sqr(mAInput),0.96*msd2(2,2),0.96*msd2(2,2)))*TPhi(0.98*Sqr(
      mAInput),0.96*msd2(2,2),0.96*msd2(2,2)))/(Sqr(msd2(2,2))*Sqr(0.96*msd2(2,2)
      - 1.02*msq2(2,2))) + (1.1302806712962963*((0.96*msd2(2,2) - 1.02*msq2(2,2))*
      (-7.529535999999999*(0.96*msd2(2,2) + 1.02*msq2(2,2))*Power6(mAInput) +
      1.8447363199999998*Power8(mAInput) - 1.96*(0.96*msd2(2,2) - 2.04*msq2(2,2))*
      (0.96*msd2(2,2) - 1.02*msq2(2,2))*(0.96*msd2(2,2) + 2.04*msq2(2,2))*Sqr(
      mAInput) + Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))*(-3.9168*msd2(2,2)*msq2(2,2)
      + 0.9216*Sqr(msd2(2,2)) + 2.0808*Sqr(msq2(2,2))) + 0.9603999999999999*Quad(
      mAInput)*(7.8336*msd2(2,2)*msq2(2,2) + 10.137599999999999*Sqr(msd2(2,2)) +
      12.4848*Sqr(msq2(2,2)))) + TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2
      (2,2))*(0.9603999999999999*(-8.64*msd2(2,2) + 6.12*msq2(2,2))*Quad(mAInput)
      - 3*(2.88*msd2(2,2) - 2.04*msq2(2,2))*Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) +
      0.98*Sqr(mAInput)*(5.8751999999999995*msd2(2,2)*msq2(2,2) + 21.1968*Sqr(
      msd2(2,2)) - 12.4848*Sqr(msq2(2,2))) + (6.72*msd2(2,2) - 4.08*msq2(2,2))*
      TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2))))*TPhi(0.98*Sqr(
      mAInput),1.02*msq2(2,2),0.96*msd2(2,2)))/(Cube(msd2(2,2))*Sqr(0.96*msd2(2,2)
      - 1.02*msq2(2,2))*TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2)))
      + (0.9611687812379854*(0.98*Sqr(mAInput)*(-11.22*msq2(2,2) + 1.96*Sqr(
      mAInput)) - 2*TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),1.02*msq2(2,2)))*TPhi(
      0.98*Sqr(mAInput),1.02*msq2(2,2),1.02*msq2(2,2)))/(Sqr(0.96*msd2(2,2) - 1.02
      *msq2(2,2))*Sqr(msq2(2,2)))) + 3*((2*Sqr(Log(0.96*msd2(2,2))))/(0.96*msd2(2,
      2) - 1.02*msq2(2,2)) + Log(0.98*Sqr(mAInput))*((-2.001633986928105*(0.96*
      msd2(2,2) - 2.04*msq2(2,2))*Sqr(mAInput))/(msd2(2,2)*(0.96*msd2(2,2) - 1.02*
      msq2(2,2))*msq2(2,2)) - (Log(0.96*msd2(2,2))*(-0.96*msd2(2,2) + 1.02*msq2(2,
      2) + 0.98*Sqr(mAInput)))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (Log(1.02*
      msq2(2,2))*(-0.96*msd2(2,2) + 1.02*msq2(2,2) + 0.98*Sqr(mAInput)))/Sqr(0.96*
      msd2(2,2) - 1.02*msq2(2,2))) + Log(1.02*msq2(2,2))*((-2*(-2.88*msd2(2,2) +
      1.02*msq2(2,2) + 0.98*Sqr(mAInput)))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) -
      (2*Log(Sqr(SCALE))*(-2.88*msd2(2,2) + 2.04*msq2(2,2) + 0.98*Sqr(mAInput)))
      /Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))) + Log(0.96*msd2(2,2))*((Log(1.02*msq2
      (2,2))*(0.96*msd2(2,2) + 1.02*msq2(2,2) - 0.98*Sqr(mAInput)))/Sqr(0.96*msd2(
      2,2) - 1.02*msq2(2,2)) + (2*(-3.84*msd2(2,2) + 2.04*msq2(2,2) + 0.98*Sqr(
      mAInput)))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (2*Log(Sqr(SCALE))*(-2.88*
      msd2(2,2) + 2.04*msq2(2,2) + 0.98*Sqr(mAInput)))/Sqr(0.96*msd2(2,2) - 1.02*
      msq2(2,2))) + ((-2.88*msd2(2,2) + 1.02*msq2(2,2) + 0.98*Sqr(mAInput))*Sqr(
      Log(1.02*msq2(2,2))))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (Log(Sqr(SCALE)
      )*(1.9584*msd2(2,2)*msq2(2,2) + 1.8816*msd2(2,2)*Sqr(mAInput) - 3.9984*msq2(
      2,2)*Sqr(mAInput)))/(0.940032*msq2(2,2)*Sqr(msd2(2,2)) - 0.998784*msd2(2,2)*
      Sqr(msq2(2,2))) + (3.9168*msd2(2,2)*msq2(2,2) + 1.8816*msd2(2,2)*Sqr(mAInput
      ) - 3.9984*msq2(2,2)*Sqr(mAInput))/(0.940032*msq2(2,2)*Sqr(msd2(2,2)) -
      0.998784*msd2(2,2)*Sqr(msq2(2,2))) + (1.0850694444444444*(0.98*(-5.76*msd2(2
      ,2) + 0.98*Sqr(mAInput))*Sqr(mAInput) - TDelta(0.98*Sqr(mAInput),0.96*msd2(2
      ,2),0.96*msd2(2,2)))*TPhi(0.98*Sqr(mAInput),0.96*msd2(2,2),0.96*msd2(2,2)))/
      ((0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(msd2(2,2))) + (1.0416666666666667*
      TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2))*TPhi(0.98*Sqr(
      mAInput),1.02*msq2(2,2),0.96*msd2(2,2)))/(msd2(2,2)*Sqr(0.96*msd2(2,2) -
      1.02*msq2(2,2))) + (0.9611687812379854*(0.98*(-0.96*msd2(2,2) + 1.02*msq2(2,
      2))*Sqr(mAInput)*(-11.22*msq2(2,2) + 1.96*Sqr(mAInput)) + (1.92*msd2(2,2) -
      3.06*msq2(2,2))*TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),1.02*msq2(2,2)))*
      TPhi(0.98*Sqr(mAInput),1.02*msq2(2,2),1.02*msq2(2,2)))/(Sqr(0.96*msd2(2,2) -
      1.02*msq2(2,2))*Sqr(msq2(2,2))))))))/Power6(1 + (0.0625*(1 + Sqr(TanBeta))*
      (0.25*Log(Sqr(MuInput)/Sqr(SCALE)) + (0.125*(-1 + 2*Log(Sqr(mAInput)/Sqr(
      SCALE))))/(1 + Sqr(TanBeta)) + ((-1 + Log(Sqr(mAInput)/Sqr(SCALE)))*Sqr(
      TanBeta))/(1 + Sqr(TanBeta)))*Sqr(Yu(2,2)))/(Sqr(3.141592653589793)*Sqr(
      TanBeta)) + 0.5*((-0.03125*Sqr(AbInput - MuInput*TanBeta)*Sqr(Yd(2,2))*TCF(5
      )(Sqrt(Abs(msq2(2,2)/msd2(2,2)))))/(Sqrt(Abs(msd2(2,2)*msq2(2,2)))*Sqr(
      3.141592653589793)) - (0.03125*Sqr(AtInput - MuInput/TanBeta)*Sqr(Yu(2,2))*
      TCF(5)(Sqrt(Abs(msq2(2,2)/msu2(2,2)))))/(Sqrt(Abs(msq2(2,2)*msu2(2,2)))*Sqr(
      3.141592653589793))) + (0.0625*(1 + Sqr(TanBeta))*Sqr(Yd(2,2))*(0.75*Log(Sqr
      (MuInput)/Sqr(SCALE)) + (0.375*(-1 + 2*Log(Sqr(mAInput)/Sqr(SCALE)))*Sqr(
      TanBeta))/(1 + Sqr(TanBeta)) + 0.5*TCF(6)(Sqrt(msd2(2,2))/MuInput) + TCF(6)(
      Sqrt(msq2(2,2))/MuInput)))/Sqr(3.141592653589793) + (0.08333333333333333*Sqr
      (g3)*(1 + Log(Sqr(M3Input)/Sqr(SCALE)) + TCF(6)(Sqrt(msd2(2,2))/M3Input) +
      TCF(6)(Sqrt(msq2(2,2))/M3Input) - ((AbInput - MuInput*TanBeta)*TCF(9)(Sqrt(
      msq2(2,2))/M3Input,Sqrt(msd2(2,2))/M3Input))/M3Input))/Sqr(3.141592653589793
      ) + (0.0625*(1 + Sqr(TanBeta))*Sqr(Yu(2,2))*(0.5*TCF(6)(Sqrt(msu2(2,2))
      /MuInput) + (0.5*(AtInput - MuInput/TanBeta)*TanBeta*TCF(9)(Sqrt(msq2(2,2))
      /MuInput,Sqrt(msu2(2,2))/MuInput))/MuInput))/(Sqr(3.141592653589793)*Sqr(
      TanBeta))) + (Quad(Yd(2,2))*Sqr(Yu(2,2))*((3*(AbInput - MuInput*TanBeta)*(
      Log(0.96*msd2(2,2))*((8.119113252073776*MuInput*Sqrt(Sqr(MuInput)))/(Abs(
      MuInput)*(0.96*msd2(2,2) - 1.02*msq2(2,2))) + (8.119113252073776*MuInput*Log
      (Sqr(SCALE))*Sqrt(Sqr(MuInput)))/(Abs(MuInput)*(0.96*msd2(2,2) - 1.02*msq2(2
      ,2)))) + Log(1.02*msq2(2,2))*((8.119113252073776*MuInput*Sqrt(Sqr(MuInput)))
      /(Abs(MuInput)*(-0.96*msd2(2,2) + 1.02*msq2(2,2))) + (8.119113252073776*
      MuInput*Log(Sqr(SCALE))*Sqrt(Sqr(MuInput)))/(Abs(MuInput)*(-0.96*msd2(2,2) +
      1.02*msq2(2,2)))) + (8.119113252073776*MuInput*PolyLog(2,1 - (
      1.0729166666666667*Sqr(MuInput))/msd2(2,2))*Sqrt(Sqr(MuInput)))/(Abs(MuInput
      )*(-0.96*msd2(2,2) + 1.02*msq2(2,2))) + (8.119113252073776*MuInput*PolyLog(2
      ,1 - (1.0098039215686274*Sqr(MuInput))/msq2(2,2))*Sqrt(Sqr(MuInput)))/(Abs(
      MuInput)*(0.96*msd2(2,2) - 1.02*msq2(2,2))) + (4.059556626036888*MuInput*
      Sqrt(Sqr(MuInput))*Sqr(Log(0.96*msd2(2,2))))/(Abs(MuInput)*(-0.96*msd2(2,2)
      + 1.02*msq2(2,2))) + (4.059556626036888*MuInput*Sqrt(Sqr(MuInput))*Sqr(Log(
      1.02*msq2(2,2))))/(Abs(MuInput)*(0.96*msd2(2,2) - 1.02*msq2(2,2)))) + 3*(
      AtInput - MuInput/TanBeta)*((8.281495517115252*MuInput*Log(1.02*msq2(2,2))*
      Log(Sqr(SCALE))*msq2(2,2)*Sqrt(Sqr(MuInput)))/(Abs(MuInput)*(1.02*msq2(2,2)
      - 0.98*msu2(2,2))*(-1.02*msq2(2,2) + 1.03*Sqr(MuInput))) + (
      8.119113252073776*MuInput*PolyLog(2,1 - (1.0098039215686274*Sqr(MuInput))
      /msq2(2,2))*Sqrt(Sqr(MuInput))*(1.02*msq2(2,2) + 1.03*Sqr(MuInput)))/(Abs(
      MuInput)*(-1.02*msq2(2,2) + 0.98*msu2(2,2))*(-1.02*msq2(2,2) + 1.03*Sqr(
      MuInput))) + (7.9567309870323*MuInput*Log(0.98*msu2(2,2))*Log(Sqr(SCALE))*
      msu2(2,2)*Sqrt(Sqr(MuInput)))/(Abs(MuInput)*(-1.02*msq2(2,2) + 0.98*msu2(2,2
      ))*(-0.98*msu2(2,2) + 1.03*Sqr(MuInput))) - (8.119113252073776*MuInput*
      PolyLog(2,1 - (1.0510204081632653*Sqr(MuInput))/msu2(2,2))*Sqrt(Sqr(MuInput)
      )*(0.98*msu2(2,2) + 1.03*Sqr(MuInput)))/(Abs(MuInput)*(-1.02*msq2(2,2) +
      0.98*msu2(2,2))*(-0.98*msu2(2,2) + 1.03*Sqr(MuInput))) + Log(1.03*Sqr(
      MuInput))*((8.36268664963599*MuInput*Log(1.02*msq2(2,2))*Power3(Sqrt(Sqr(
      MuInput))))/(Abs(MuInput)*(1.02*msq2(2,2) - 0.98*msu2(2,2))*(-1.02*msq2(2,2)
      + 1.03*Sqr(MuInput))) + (8.36268664963599*MuInput*Log(Sqr(SCALE))*Power3(
      Sqrt(Sqr(MuInput))))/(Abs(MuInput)*(0.98*msu2(2,2) - 1.03*Sqr(MuInput))*(
      -1.02*msq2(2,2) + 1.03*Sqr(MuInput))) + (8.36268664963599*MuInput*Log(0.98*
      msu2(2,2))*Power3(Sqrt(Sqr(MuInput))))/(Abs(MuInput)*(-1.02*msq2(2,2) + 0.98
      *msu2(2,2))*(-0.98*msu2(2,2) + 1.03*Sqr(MuInput)))) + (4.059556626036888*
      MuInput*Sqrt(Sqr(MuInput))*(1.02*msq2(2,2) + 1.03*Sqr(MuInput))*Sqr(Log(1.02
      *msq2(2,2))))/(Abs(MuInput)*(-1.02*msq2(2,2) + 0.98*msu2(2,2))*(-1.02*msq2(2
      ,2) + 1.03*Sqr(MuInput))) - (4.059556626036888*MuInput*Sqrt(Sqr(MuInput))*(
      0.98*msu2(2,2) + 1.03*Sqr(MuInput))*Sqr(Log(0.98*msu2(2,2))))/(Abs(MuInput)*
      (-1.02*msq2(2,2) + 0.98*msu2(2,2))*(-0.98*msu2(2,2) + 1.03*Sqr(MuInput)))) +
      3*Cube(AbInput - MuInput*TanBeta)*(Log(1.02*msq2(2,2))*((8.119113252073776*
      MuInput*Log(Sqr(SCALE))*(0.96*msd2(2,2) + 1.02*msq2(2,2))*Sqrt(Sqr(MuInput))
      )/(Abs(MuInput)*Cube(0.96*msd2(2,2) - 1.02*msq2(2,2))) + (8.119113252073776*
      MuInput*(0.96*msd2(2,2) + 3.06*msq2(2,2))*Sqrt(Sqr(MuInput)))/(Abs(MuInput)*
      Cube(0.96*msd2(2,2) - 1.02*msq2(2,2)))) + (8.119113252073776*MuInput*PolyLog
      (2,1 - (1.0729166666666667*Sqr(MuInput))/msd2(2,2))*(0.96*msd2(2,2) + 1.02*
      msq2(2,2) - 2.06*Sqr(MuInput))*Sqrt(Sqr(MuInput)))/(Abs(MuInput)*Cube(0.96*
      msd2(2,2) - 1.02*msq2(2,2))) - (8.119113252073776*MuInput*PolyLog(2,1 - (
      1.0098039215686274*Sqr(MuInput))/msq2(2,2))*(0.96*msd2(2,2) + 1.02*msq2(2,2)
      - 2.06*Sqr(MuInput))*Sqrt(Sqr(MuInput)))/(Abs(MuInput)*Cube(0.96*msd2(2,2)
      - 1.02*msq2(2,2))) + (16.72537329927198*MuInput*Log(1.02*msq2(2,2))*Log(1.03
      *Sqr(MuInput))*Power3(Sqrt(Sqr(MuInput))))/(Abs(MuInput)*Cube(-0.96*msd2(2,2
      ) + 1.02*msq2(2,2))) + Log(0.96*msd2(2,2))*((-8.119113252073776*MuInput*Log(
      Sqr(SCALE))*(0.96*msd2(2,2) + 1.02*msq2(2,2))*Sqrt(Sqr(MuInput)))/(Abs(
      MuInput)*Cube(0.96*msd2(2,2) - 1.02*msq2(2,2))) + (8.119113252073776*MuInput
      *(2.88*msd2(2,2) + 1.02*msq2(2,2))*Sqrt(Sqr(MuInput)))/(Abs(MuInput)*Cube(
      -0.96*msd2(2,2) + 1.02*msq2(2,2))) + (16.72537329927198*MuInput*Log(1.03*Sqr
      (MuInput))*Power3(Sqrt(Sqr(MuInput))))/(Abs(MuInput)*Cube(0.96*msd2(2,2) -
      1.02*msq2(2,2)))) + (4.059556626036888*MuInput*(0.96*msd2(2,2) + 1.02*msq2(2
      ,2) - 2.06*Sqr(MuInput))*Sqrt(Sqr(MuInput))*Sqr(Log(0.96*msd2(2,2))))/(Abs(
      MuInput)*Cube(0.96*msd2(2,2) - 1.02*msq2(2,2))) - (4.059556626036888*MuInput
      *(0.96*msd2(2,2) + 1.02*msq2(2,2) - 2.06*Sqr(MuInput))*Sqrt(Sqr(MuInput))*
      Sqr(Log(1.02*msq2(2,2))))/(Abs(MuInput)*Cube(0.96*msd2(2,2) - 1.02*msq2(2,2)
      )) + (32.4764530082951*MuInput*Sqrt(Sqr(MuInput)))/(Abs(MuInput)*Sqr(0.96*
      msd2(2,2) - 1.02*msq2(2,2))) + (16.23822650414755*MuInput*Log(Sqr(SCALE))*
      Sqrt(Sqr(MuInput)))/(Abs(MuInput)*Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)))))/(
      Sqrt(1/(1 + Sqr(TanBeta)))*Sqrt(Sqr(TanBeta)/(1 + Sqr(TanBeta)))) + 3*Quad(
      AbInput - MuInput*TanBeta)*(Log(0.96*msd2(2,2))*((4*Log(1.02*msq2(2,2))*(
      0.96*msd2(2,2) + 1.02*msq2(2,2)))/Cube(0.96*msd2(2,2) - 1.02*msq2(2,2)) - (4
      *Log(Sqr(SCALE))*(0.96*msd2(2,2) + 1.02*msq2(2,2)))/Cube(0.96*msd2(2,2) -
      1.02*msq2(2,2)) - (2*(6.72*msd2(2,2) + 1.02*msq2(2,2)))/Cube(0.96*msd2(2,2)
      - 1.02*msq2(2,2))) + Log(1.02*msq2(2,2))*((4*Log(Sqr(SCALE))*(0.96*msd2(2,2)
      + 1.02*msq2(2,2)))/Cube(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (2*(2.88*msd2(2,
      2) + 5.1*msq2(2,2)))/Cube(0.96*msd2(2,2) - 1.02*msq2(2,2))) - (4*(0.96*msd2(
      2,2) + 1.02*msq2(2,2))*Sqr(Log(1.02*msq2(2,2))))/Cube(0.96*msd2(2,2) - 1.02*
      msq2(2,2)) + 16/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (8*Log(Sqr(SCALE)))
      /Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) - (6*PolyLog(2,1 - (0.9411764705882352
      *msd2(2,2))/msq2(2,2)))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))) + (1 + Sqr(
      TanBeta))*(3*(-4*PolyLog(2,1 - (1.0729166666666667*Sqr(MuInput))/msd2(2,2))
      - 4*PolyLog(2,1 - (1.0098039215686274*Sqr(MuInput))/msq2(2,2)) + 4.12*Log(
      1.03*Sqr(MuInput))*(1/(0.96*msd2(2,2) - 1.03*Sqr(MuInput)) + 1/(1.02*msq2(2,
      2) - 1.03*Sqr(MuInput)))*Sqr(MuInput) + Log(0.96*msd2(2,2))*(2*Log(1.02*msq2
      (2,2)) + 2*Log(Sqr(SCALE)) + (4.12*Sqr(MuInput))/(-0.96*msd2(2,2) + 1.03*Sqr
      (MuInput))) + Log(1.02*msq2(2,2))*(2*Log(Sqr(SCALE)) + (4.12*Sqr(MuInput))/(
      -1.02*msq2(2,2) + 1.03*Sqr(MuInput))) - 2*Sqr(Log(Sqr(SCALE))) - 2*Sqr(Log(
      0.96*msd2(2,2))) - 2*Sqr(Log(1.02*msq2(2,2)))) + 3*Sqr(AbInput - MuInput*
      TanBeta)*(4/(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (2*Log(Sqr(SCALE)))/(0.96*
      msd2(2,2) - 1.02*msq2(2,2)) + (4.12*Log(1.03*Sqr(MuInput))*Sqr(MuInput))/((
      0.96*msd2(2,2) - 1.02*msq2(2,2))*(0.96*msd2(2,2) - 1.03*Sqr(MuInput))) + Log
      (1.02*msq2(2,2))*((2.04*Log(Sqr(SCALE))*msq2(2,2))/Sqr(0.96*msd2(2,2) - 1.02
      *msq2(2,2)) + (2*(0.96*msd2(2,2) + 1.02*msq2(2,2)))/Sqr(0.96*msd2(2,2) -
      1.02*msq2(2,2))) + Log(0.96*msd2(2,2))*((-2.04*Log(1.02*msq2(2,2))*msq2(2,2)
      )/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) - (2.04*Log(Sqr(SCALE))*msq2(2,2))
      /Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) - (4*(-1.0506*msq2(2,2)*Sqr(MuInput) +
      0.9216*Sqr(msd2(2,2))))/((0.96*msd2(2,2) - 1.03*Sqr(MuInput))*Sqr(0.96*msd2
      (2,2) - 1.02*msq2(2,2)))) + (4.08*msq2(2,2)*PolyLog(2,1 - (
      1.0729166666666667*Sqr(MuInput))/msd2(2,2)))/Sqr(0.96*msd2(2,2) - 1.02*msq2(
      2,2)) - (4.08*msq2(2,2)*PolyLog(2,1 - (1.0098039215686274*Sqr(MuInput))/msq2
      (2,2)))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (2.04*msq2(2,2)*Sqr(Log(0.96*
      msd2(2,2))))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))) + Sqr(AtInput -
      MuInput/TanBeta)*(3*(4/(1.02*msq2(2,2) - 0.98*msu2(2,2)) + (4.12*Log(1.03*
      Sqr(MuInput))*Sqr(MuInput))/((-1.02*msq2(2,2) + 0.98*msu2(2,2))*(-1.02*msq2(
      2,2) + 1.03*Sqr(MuInput))) + Log(Sqr(SCALE))*(2/(1.02*msq2(2,2) - 0.98*msu2(
      2,2)) + (1.96*Log(0.98*msu2(2,2))*msu2(2,2))/Sqr(1.02*msq2(2,2) - 0.98*msu2(
      2,2))) + Log(0.96*msd2(2,2))*(2/(1.02*msq2(2,2) - 0.98*msu2(2,2)) - (1.96*
      Log(1.02*msq2(2,2))*msu2(2,2))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)) + (1.96*
      Log(0.98*msu2(2,2))*msu2(2,2))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) + Log(
      1.02*msq2(2,2))*((-1.96*Log(Sqr(SCALE))*msu2(2,2))/Sqr(1.02*msq2(2,2) - 0.98
      *msu2(2,2)) + (4*(-1.0094*msu2(2,2)*Sqr(MuInput) + 1.0404*Sqr(msq2(2,2))))/(
      (-1.02*msq2(2,2) + 1.03*Sqr(MuInput))*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))))
      + (3.92*Log(0.98*msu2(2,2))*msu2(2,2))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))
      + (3.92*msu2(2,2)*PolyLog(2,1 - (1.0098039215686274*Sqr(MuInput))/msq2(2,2)
      ))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)) - (3.92*msu2(2,2)*PolyLog(2,1 - (
      1.0510204081632653*Sqr(MuInput))/msu2(2,2)))/Sqr(1.02*msq2(2,2) - 0.98*msu2(
      2,2)) + (1.96*msu2(2,2)*Sqr(Log(1.02*msq2(2,2))))/Sqr(1.02*msq2(2,2) - 0.98*
      msu2(2,2)) - (1.96*msu2(2,2)*Sqr(Log(0.98*msu2(2,2))))/Sqr(1.02*msq2(2,2) -
      0.98*msu2(2,2))) + 3*Sqr(AbInput - MuInput*TanBeta)*(2/((0.96*msd2(2,2) -
      1.02*msq2(2,2))*(1.02*msq2(2,2) - 0.98*msu2(2,2))) + Log(0.96*msd2(2,2))*((
      2.04*msq2(2,2))/((-1.02*msq2(2,2) + 0.98*msu2(2,2))*Sqr(0.96*msd2(2,2) -
      1.02*msq2(2,2))) + (1.9992*Log(1.02*msq2(2,2))*msq2(2,2)*msu2(2,2))/(Sqr(
      0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) - (
      1.9992*Log(0.98*msu2(2,2))*msq2(2,2)*msu2(2,2))/(Sqr(0.96*msd2(2,2) - 1.02*
      msq2(2,2))*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)))) + Log(1.02*msq2(2,2))*((
      1.9992*Log(0.98*msu2(2,2))*msq2(2,2)*msu2(2,2))/(Sqr(0.96*msd2(2,2) - 1.02*
      msq2(2,2))*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) + (2*(-0.9408*msd2(2,2)*
      msu2(2,2) + 1.0404*Sqr(msq2(2,2))))/(Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))*
      Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)))) + (1.96*Log(0.98*msu2(2,2))*msu2(2,2)
      )/((0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) -
      (1.9992*msq2(2,2)*msu2(2,2)*Sqr(Log(1.02*msq2(2,2))))/(Sqr(0.96*msd2(2,2) -
      1.02*msq2(2,2))*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)))))) + Sqr(AtInput -
      MuInput/TanBeta)*(9*((1.9992*msq2(2,2)*msu2(2,2)*Sqr(Log(1.02*msq2(2,2))))
      /Cube(1.02*msq2(2,2) - 0.98*msu2(2,2)) + Log(0.96*msd2(2,2))*((1.9992*Log(
      1.02*msq2(2,2))*msq2(2,2)*msu2(2,2))/Cube(1.02*msq2(2,2) - 0.98*msu2(2,2)) -
      (1.9992*Log(0.98*msu2(2,2))*msq2(2,2)*msu2(2,2))/Cube(1.02*msq2(2,2) - 0.98
      *msu2(2,2)) - (1.02*msq2(2,2) + 0.98*msu2(2,2))/Sqr(1.02*msq2(2,2) - 0.98*
      msu2(2,2))) + Log(1.02*msq2(2,2))*((-1.9992*Log(0.98*msu2(2,2))*msq2(2,2)*
      msu2(2,2))/Cube(1.02*msq2(2,2) - 0.98*msu2(2,2)) - (3.9984*Log(Sqr(SCALE))*
      msq2(2,2)*msu2(2,2))/Cube(1.02*msq2(2,2) - 0.98*msu2(2,2)) - (1.02*msq2(2,2)
      + 0.98*msu2(2,2))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) + Log(Sqr(SCALE))*(
      (3.9984*Log(0.98*msu2(2,2))*msq2(2,2)*msu2(2,2))/Cube(1.02*msq2(2,2) - 0.98*
      msu2(2,2)) + (2*(1.02*msq2(2,2) + 0.98*msu2(2,2)))/Sqr(1.02*msq2(2,2) - 0.98
      *msu2(2,2)))) + 3*((6*PolyLog(2,1 - (1.0408163265306123*msq2(2,2))/msu2(2,2)
      ))/(-1.02*msq2(2,2) + 0.98*msu2(2,2)) + (3*Sqr(Log(0.98*msu2(2,2))))/(-1.02*
      msq2(2,2) + 0.98*msu2(2,2)) + (-5.1*msq2(2,2) + 0.98*msu2(2,2))/(-0.9996*
      msq2(2,2)*msu2(2,2) + 1.0404*Sqr(msq2(2,2))) + Log(Sqr(SCALE))*((-3.06*msq2(
      2,2) + 0.98*msu2(2,2))/(-0.9996*msq2(2,2)*msu2(2,2) + 1.0404*Sqr(msq2(2,2)))
      - (1.96*Log(0.98*msu2(2,2))*msu2(2,2))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))
      ) + Log(1.02*msq2(2,2))*((Log(0.98*msu2(2,2))*(6.12*msq2(2,2) - 3.92*msu2(2,
      2)))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)) + (3.06*msq2(2,2) + 0.98*msu2(2,2)
      )/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)) + (1.96*Log(Sqr(SCALE))*msu2(2,2))
      /Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) + (0.9607843137254901*Log(0.98*msu2(2
      ,2))*(-5.1*msq2(2,2) + 0.98*msu2(2,2))*msu2(2,2))/(msq2(2,2)*Sqr(1.02*msq2(2
      ,2) - 0.98*msu2(2,2))) + ((-3.06*msq2(2,2) + 0.98*msu2(2,2))*Sqr(Log(1.02*
      msq2(2,2))))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) + Sqr(AbInput - MuInput*
      TanBeta)*(9*((3.9984*msq2(2,2)*msu2(2,2)*Sqr(Log(1.02*msq2(2,2))))/(Cube(
      1.02*msq2(2,2) - 0.98*msu2(2,2))*(-0.96*msd2(2,2) + 1.02*msq2(2,2))) + Log(
      1.02*msq2(2,2))*((3.9984*Log(0.98*msu2(2,2))*msq2(2,2)*msu2(2,2))/(Cube(1.02
      *msq2(2,2) - 0.98*msu2(2,2))*(0.96*msd2(2,2) - 1.02*msq2(2,2))) + (2*(1.02*
      msq2(2,2) + 0.98*msu2(2,2)))/((0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(1.02*
      msq2(2,2) - 0.98*msu2(2,2)))) + Log(0.96*msd2(2,2))*((3.9984*Log(1.02*msq2(2
      ,2))*msq2(2,2)*msu2(2,2))/(Cube(1.02*msq2(2,2) - 0.98*msu2(2,2))*(0.96*msd2(
      2,2) - 1.02*msq2(2,2))) + (3.9984*Log(0.98*msu2(2,2))*msq2(2,2)*msu2(2,2))/(
      Cube(1.02*msq2(2,2) - 0.98*msu2(2,2))*(-0.96*msd2(2,2) + 1.02*msq2(2,2))) +
      (2*(1.02*msq2(2,2) + 0.98*msu2(2,2)))/((-0.96*msd2(2,2) + 1.02*msq2(2,2))*
      Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))))) + 3*((1.9215686274509802*Log(0.98*
      msu2(2,2))*msu2(2,2))/((0.96*msd2(2,2) - 1.02*msq2(2,2))*msq2(2,2)*(1.02*
      msq2(2,2) - 0.98*msu2(2,2))) + ((11.52*msd2(2,2) - 6*(1.02*msq2(2,2) + 0.98*
      msu2(2,2)))*PolyLog(2,1 - (1.0408163265306123*msq2(2,2))/msu2(2,2)))/((1.02*
      msq2(2,2) - 0.98*msu2(2,2))*Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))) + 2/(
      0.9792*msd2(2,2)*msq2(2,2) - 1.0404*Sqr(msq2(2,2))) + (2*Log(Sqr(SCALE)))/(
      0.9792*msd2(2,2)*msq2(2,2) - 1.0404*Sqr(msq2(2,2))) + (6*(0.96*msd2(2,2) +
      1.02*msq2(2,2) - 1.96*msu2(2,2))*PolyLog(2,1 - (0.9411764705882352*msd2(2,2)
      )/msq2(2,2)))/((0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(1.02*msq2(2,2) - 0.98*
      msu2(2,2))) - (3*Sqr(Log(0.98*msu2(2,2))))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,
      2)) + (Sqr(Log(1.02*msq2(2,2)))*(5.8751999999999995*msd2(2,2)*msq2(2,2) -
      7.5264*msd2(2,2)*msu2(2,2) + 3.9984*msq2(2,2)*msu2(2,2) + 2.7648*Sqr(msd2(2,
      2)) - 5.202*Sqr(msq2(2,2))))/(Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(1.02*
      msq2(2,2) - 0.98*msu2(2,2))) - (6*PolyLog(2,1 - (0.9795918367346939*msd2(2,2
      ))/msu2(2,2))*Sqr(0.96*msd2(2,2) - 0.98*msu2(2,2)))/(Sqr(0.96*msd2(2,2) -
      1.02*msq2(2,2))*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) + Log(0.96*msd2(2,2))*
      ((-2*Log(Sqr(SCALE)))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (2*(0.96*msd2(2
      ,2) - 0.98*msu2(2,2)))/((-1.02*msq2(2,2) + 0.98*msu2(2,2))*Sqr(0.96*msd2(2,2
      ) - 1.02*msq2(2,2))) + (Log(1.02*msq2(2,2))*(2.04*msq2(2,2)*(1.02*msq2(2,2)
      - 1.96*msu2(2,2)) + 7.5264*msd2(2,2)*msu2(2,2) - 5.5296*Sqr(msd2(2,2))))/(
      Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) +
      (2*Log(0.98*msu2(2,2))*(-3.7632*msd2(2,2)*msu2(2,2) + 2.7648*Sqr(msd2(2,2))
      + 0.9603999999999999*Sqr(msu2(2,2))))/(Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))
      *Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)))) + Log(1.02*msq2(2,2))*(2/Sqr(0.96*
      msd2(2,2) - 1.02*msq2(2,2)) + (2*Log(Sqr(SCALE)))/Sqr(0.96*msd2(2,2) - 1.02*
      msq2(2,2)) - (2*Log(0.98*msu2(2,2))*(5.8751999999999995*msd2(2,2)*msq2(2,2)
      - 3.7632*msd2(2,2)*msu2(2,2) - 3.1212*Sqr(msq2(2,2)) + 0.9603999999999999*
      Sqr(msu2(2,2))))/(Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(1.02*msq2(2,2) -
      0.98*msu2(2,2)))))) + Quad(AbInput - MuInput*TanBeta)*(3*((
      0.9803921568627451*Log(Sqr(SCALE))*(0.96*msd2(2,2) + 5.1*msq2(2,2)))/(Cube(
      -0.96*msd2(2,2) + 1.02*msq2(2,2))*msq2(2,2)) + (0.9803921568627451*(0.96*
      msd2(2,2) + 11.22*msq2(2,2)))/(Cube(-0.96*msd2(2,2) + 1.02*msq2(2,2))*msq2(2
      ,2)) + (0.9607843137254901*Log(0.98*msu2(2,2))*msu2(2,2))/(msq2(2,2)*(-1.02*
      msq2(2,2) + 0.98*msu2(2,2))*Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))) + (6*
      PolyLog(2,1 - (0.9411764705882352*msd2(2,2))/msq2(2,2)))/((-1.02*msq2(2,2) +
      0.98*msu2(2,2))*Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))) + (6*PolyLog(2,1 - (
      0.9795918367346939*msd2(2,2))/msu2(2,2))*Sqr(0.96*msd2(2,2) - 0.98*msu2(2,2)
      ))/((1.02*msq2(2,2) - 0.98*msu2(2,2))*Quad(0.96*msd2(2,2) - 1.02*msq2(2,2)))
      - (6*PolyLog(2,1 - (1.0408163265306123*msq2(2,2))/msu2(2,2))*Sqr(0.96*msd2(
      2,2) - 0.98*msu2(2,2)))/((1.02*msq2(2,2) - 0.98*msu2(2,2))*Quad(0.96*msd2(2,
      2) - 1.02*msq2(2,2))) + Log(1.02*msq2(2,2))*((-2*Log(Sqr(SCALE))*(1.92*msd2(
      2,2) + 1.02*msq2(2,2)))/Quad(0.96*msd2(2,2) - 1.02*msq2(2,2)) - (4*(0.96*
      msd2(2,2) + 2.04*msq2(2,2)))/Quad(0.96*msd2(2,2) - 1.02*msq2(2,2)) + 3/((
      1.02*msq2(2,2) - 0.98*msu2(2,2))*Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))) - (2*
      Log(0.98*msu2(2,2))*(0.96*msd2(2,2) - 0.98*msu2(2,2))*(-2.9375999999999998*
      msd2(2,2)*msq2(2,2) + 1.8816*msd2(2,2)*msu2(2,2) + 0.9996*msq2(2,2)*msu2(2,2
      )))/(Quad(0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,
      2)))) + Log(0.96*msd2(2,2))*((2*Log(Sqr(SCALE))*(1.92*msd2(2,2) + 1.02*msq2(
      2,2)))/Quad(0.96*msd2(2,2) - 1.02*msq2(2,2)) - (2*(-6.8544*msd2(2,2)*msq2(2,
      2) + 4.704*msd2(2,2)*msu2(2,2) + 0.9996*msq2(2,2)*msu2(2,2) + 0.9216*Sqr(
      msd2(2,2))))/((1.02*msq2(2,2) - 0.98*msu2(2,2))*Quad(0.96*msd2(2,2) - 1.02*
      msq2(2,2))) + (Log(1.02*msq2(2,2))*(2.04*msq2(2,2)*(2.88*msd2(2,2) + 1.02*
      msq2(2,2)) - 3.92*(0.96*msd2(2,2) + 1.02*msq2(2,2))*msu2(2,2)))/(Cube(0.96*
      msd2(2,2) - 1.02*msq2(2,2))*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) + (2*Log(
      0.98*msu2(2,2))*(0.96*msd2(2,2) - 0.98*msu2(2,2))*(-2.9375999999999998*msd2(
      2,2)*msq2(2,2) + 1.8816*msd2(2,2)*msu2(2,2) + 0.9996*msq2(2,2)*msu2(2,2)))/(
      Quad(0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))))
      + ((-2.04*msq2(2,2)*(2.88*msd2(2,2) + 1.02*msq2(2,2)) + 3.92*(0.96*msd2(2,2
      ) + 1.02*msq2(2,2))*msu2(2,2))*Sqr(Log(1.02*msq2(2,2))))/(Cube(0.96*msd2(2,2
      ) - 1.02*msq2(2,2))*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)))) + 9*((1.9992*msq2
      (2,2)*(0.96*msd2(2,2) + 1.02*msq2(2,2))*msu2(2,2)*Sqr(Log(1.02*msq2(2,2))))/
      (Cube(0.96*msd2(2,2) - 1.02*msq2(2,2))*Cube(1.02*msq2(2,2) - 0.98*msu2(2,2))
      ) - (3.9984*Log(0.98*msu2(2,2))*msq2(2,2)*msu2(2,2))/(Cube(1.02*msq2(2,2) -
      0.98*msu2(2,2))*Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))) + Log(0.96*msd2(2,2))*
      ((1.9992*Log(1.02*msq2(2,2))*msq2(2,2)*(0.96*msd2(2,2) + 1.02*msq2(2,2))*
      msu2(2,2))/(Cube(-0.96*msd2(2,2) + 1.02*msq2(2,2))*Cube(1.02*msq2(2,2) -
      0.98*msu2(2,2))) + (1.9992*Log(0.98*msu2(2,2))*msq2(2,2)*(0.96*msd2(2,2) +
      1.02*msq2(2,2))*msu2(2,2))/(Cube(0.96*msd2(2,2) - 1.02*msq2(2,2))*Cube(1.02*
      msq2(2,2) - 0.98*msu2(2,2))) + ((0.96*msd2(2,2) + 1.02*msq2(2,2))*(1.02*msq2
      (2,2) + 0.98*msu2(2,2)))/(Cube(0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(1.02*
      msq2(2,2) - 0.98*msu2(2,2)))) - (2*(1.02*msq2(2,2) + 0.98*msu2(2,2)))/(Sqr(
      0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) + Log
      (1.02*msq2(2,2))*((1.9992*Log(0.98*msu2(2,2))*msq2(2,2)*(0.96*msd2(2,2) +
      1.02*msq2(2,2))*msu2(2,2))/(Cube(-0.96*msd2(2,2) + 1.02*msq2(2,2))*Cube(1.02
      *msq2(2,2) - 0.98*msu2(2,2))) + (3.9984*(0.96*msd2(2,2) - 1.02*msq2(2,2))*
      msq2(2,2)*msu2(2,2) - 1.0404*(0.96*msd2(2,2) + 1.02*msq2(2,2))*Sqr(msq2(2,2)
      ) + 0.9603999999999999*(0.96*msd2(2,2) + 1.02*msq2(2,2))*Sqr(msu2(2,2)))/(
      Cube(0.96*msd2(2,2) - 1.02*msq2(2,2))*Cube(1.02*msq2(2,2) - 0.98*msu2(2,2)))
      )))) + 3*(AbInput + MuInput/TanBeta)*(AbInput - MuInput*TanBeta)*(Log(1.02*
      msq2(2,2))*(4/(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (4*Log(Sqr(SCALE)))/(0.96*
      msd2(2,2) - 1.02*msq2(2,2))) + Log(0.98*Sqr(mAInput))*((2*Log(0.96*msd2(2,2)
      ))/(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (2*Log(1.02*msq2(2,2)))/(-0.96*msd2(2
      ,2) + 1.02*msq2(2,2))) + Log(0.96*msd2(2,2))*((2*Log(1.02*msq2(2,2)))/(0.96*
      msd2(2,2) - 1.02*msq2(2,2)) + 4/(-0.96*msd2(2,2) + 1.02*msq2(2,2)) + (4*Log(
      Sqr(SCALE)))/(-0.96*msd2(2,2) + 1.02*msq2(2,2))) + (2*Sqr(Log(1.02*msq2(2,2)
      )))/(-0.96*msd2(2,2) + 1.02*msq2(2,2)) + (2.170138888888889*(
      -2.9375999999999998*msd2(2,2)*msq2(2,2) + 0.9603999999999999*Quad(mAInput) -
      2.8224*msd2(2,2)*Sqr(mAInput) - 1.9992*msq2(2,2)*Sqr(mAInput) + 1.8432*Sqr(
      msd2(2,2)) + 1.0404*Sqr(msq2(2,2)) - TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2)
      ,0.96*msd2(2,2)))*TPhi(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2)))/((
      0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(msd2(2,2))) + (1.9223375624759709*(
      -0.98*(-5.1*msq2(2,2) + 0.98*Sqr(mAInput))*Sqr(mAInput) + TDelta(0.98*Sqr(
      mAInput),1.02*msq2(2,2),1.02*msq2(2,2)))*TPhi(0.98*Sqr(mAInput),1.02*msq2(2,
      2),1.02*msq2(2,2)))/((0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(msq2(2,2)))) + 3*
      (AbInput + MuInput/TanBeta)*Cube(AbInput - MuInput*TanBeta)*(Log(1.02*msq2(2
      ,2))*((-4*Log(Sqr(SCALE))*(0.96*msd2(2,2) + 1.02*msq2(2,2)))/Cube(0.96*msd2(
      2,2) - 1.02*msq2(2,2)) - (4*(0.96*msd2(2,2) + 3.06*msq2(2,2)))/Cube(0.96*
      msd2(2,2) - 1.02*msq2(2,2))) + Log(0.96*msd2(2,2))*((4*Log(Sqr(SCALE))*(0.96
      *msd2(2,2) + 1.02*msq2(2,2)))/Cube(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (4*(
      2.88*msd2(2,2) + 1.02*msq2(2,2)))/Cube(0.96*msd2(2,2) - 1.02*msq2(2,2)) - (2
      *Log(1.02*msq2(2,2))*(0.96*msd2(2,2) + 3.06*msq2(2,2) - 1.96*Sqr(mAInput)))
      /Cube(0.96*msd2(2,2) - 1.02*msq2(2,2))) + Log(0.98*Sqr(mAInput))*((-2*Log(
      0.96*msd2(2,2))*(0.96*msd2(2,2) - 1.02*msq2(2,2) + 1.96*Sqr(mAInput)))/Cube(
      0.96*msd2(2,2) - 1.02*msq2(2,2)) + (2*Log(1.02*msq2(2,2))*(0.96*msd2(2,2) -
      1.02*msq2(2,2) + 1.96*Sqr(mAInput)))/Cube(0.96*msd2(2,2) - 1.02*msq2(2,2)))
      + (2*(0.96*msd2(2,2) + 3.06*msq2(2,2) - 1.96*Sqr(mAInput))*Sqr(Log(1.02*msq2
      (2,2))))/Cube(0.96*msd2(2,2) - 1.02*msq2(2,2)) - 16/Sqr(0.96*msd2(2,2) -
      1.02*msq2(2,2)) - (8*Log(Sqr(SCALE)))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) +
      (2.170138888888889*((0.96*msd2(2,2) - 1.02*msq2(2,2))*(-2.9375999999999998*
      msd2(2,2)*msq2(2,2) + 0.9603999999999999*Quad(mAInput) - 2.8224*msd2(2,2)*
      Sqr(mAInput) - 1.9992*msq2(2,2)*Sqr(mAInput) + 1.8432*Sqr(msd2(2,2)) +
      1.0404*Sqr(msq2(2,2))) + (-2.88*msd2(2,2) + 1.02*msq2(2,2))*TDelta(0.98*Sqr(
      mAInput),1.02*msq2(2,2),0.96*msd2(2,2)))*TPhi(0.98*Sqr(mAInput),1.02*msq2(2,
      2),0.96*msd2(2,2)))/(Cube(0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(msd2(2,2))) +
      (1.9223375624759709*(0.98*(0.96*msd2(2,2) - 1.02*msq2(2,2))*(-5.1*msq2(2,2)
      + 0.98*Sqr(mAInput))*Sqr(mAInput) - (0.96*msd2(2,2) - 3.06*msq2(2,2))*
      TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),1.02*msq2(2,2)))*TPhi(0.98*Sqr(
      mAInput),1.02*msq2(2,2),1.02*msq2(2,2)))/(Cube(0.96*msd2(2,2) - 1.02*msq2(2,
      2))*Sqr(msq2(2,2)))) + 3*(-1 + Log(0.98*Sqr(mAInput))*(2*Log(0.96*msd2(2,2))
      - 2*Log(0.98*msu2(2,2)) - 8*Log(Sqr(SCALE))) + Log(0.96*msd2(2,2))*(-4 + 2*
      Log(0.98*msu2(2,2)) - 4*Log(Sqr(SCALE))) + Log(1.02*msq2(2,2))*(-2 - 2*Log(
      Sqr(SCALE))) + 6*Log(Sqr(SCALE)) + 1.3333333333333333*Sqr(3.141592653589793)
      + 4*Sqr(Log(0.98*Sqr(mAInput))) + 7*Sqr(Log(Sqr(SCALE))) + Sqr(Log(1.02*
      msq2(2,2))) - (1.9223375624759709*(-0.98*(-5.1*msq2(2,2) + 0.98*Sqr(mAInput)
      )*Sqr(mAInput) + TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),1.02*msq2(2,2)))*
      TPhi(0.98*Sqr(mAInput),1.02*msq2(2,2),1.02*msq2(2,2)))/Sqr(msq2(2,2)) + (
      2.170138888888889*(-2.8224*msd2(2,2)*msu2(2,2) + 0.9603999999999999*Quad(
      mAInput) - 2.8224*msd2(2,2)*Sqr(mAInput) - 1.9207999999999998*msu2(2,2)*Sqr(
      mAInput) + 1.8432*Sqr(msd2(2,2)) + 0.9603999999999999*Sqr(msu2(2,2)) -
      TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),0.96*msd2(2,2)))*TPhi(0.98*Sqr(
      mAInput),0.98*msu2(2,2),0.96*msd2(2,2)))/Sqr(msd2(2,2))) + 3*Sqr(AbInput -
      MuInput*TanBeta)*(8/(-0.96*msd2(2,2) + 1.02*msq2(2,2)) + (4*Log(Sqr(SCALE)))
      /(-0.96*msd2(2,2) + 1.02*msq2(2,2)) + (12*PolyLog(2,1 - (0.9411764705882352*
      msd2(2,2))/msq2(2,2)))/(0.96*msd2(2,2) - 1.02*msq2(2,2)) + Log(0.98*Sqr(
      mAInput))*((2*Log(0.96*msd2(2,2))*(0.96*msd2(2,2) - 2.04*msq2(2,2) + 0.98*
      msu2(2,2)))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) - (2*Log(1.02*msq2(2,2))*(
      0.96*msd2(2,2) - 2.04*msq2(2,2) + 0.98*msu2(2,2)))/Sqr(0.96*msd2(2,2) - 1.02
      *msq2(2,2))) + Log(1.02*msq2(2,2))*((-3.84*Log(Sqr(SCALE))*msd2(2,2))/Sqr(
      0.96*msd2(2,2) - 1.02*msq2(2,2)) - (2*(0.96*msd2(2,2) + 3.06*msq2(2,2)))/Sqr
      (0.96*msd2(2,2) - 1.02*msq2(2,2)) + (2*Log(0.98*msu2(2,2))*(1.02*msq2(2,2) +
      0.98*msu2(2,2) - 0.98*Sqr(mAInput)))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)))
      + Log(0.96*msd2(2,2))*((3.84*Log(Sqr(SCALE))*msd2(2,2))/Sqr(0.96*msd2(2,2) -
      1.02*msq2(2,2)) + (2*(2.88*msd2(2,2) + 1.02*msq2(2,2)))/Sqr(0.96*msd2(2,2)
      - 1.02*msq2(2,2)) - (2*Log(0.98*msu2(2,2))*(1.02*msq2(2,2) + 0.98*msu2(2,2)
      - 0.98*Sqr(mAInput)))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) - (2*Log(1.02*
      msq2(2,2))*(2.88*msd2(2,2) - 3.06*msq2(2,2) + 0.98*Sqr(mAInput)))/Sqr(0.96*
      msd2(2,2) - 1.02*msq2(2,2))) + (2*(2.88*msd2(2,2) - 3.06*msq2(2,2) + 0.98*
      Sqr(mAInput))*Sqr(Log(1.02*msq2(2,2))))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))
      + (2.0833333333333335*TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2
      ))*TPhi(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2)))/(msd2(2,2)*Sqr(
      0.96*msd2(2,2) - 1.02*msq2(2,2))) + (1.9223375624759709*(0.98*(-0.96*msd2(2,
      2) + 1.02*msq2(2,2))*(-5.1*msq2(2,2) + 0.98*Sqr(mAInput))*Sqr(mAInput) + (
      0.96*msd2(2,2) - 2.04*msq2(2,2))*TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),
      1.02*msq2(2,2)))*TPhi(0.98*Sqr(mAInput),1.02*msq2(2,2),1.02*msq2(2,2)))/(Sqr
      (0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(msq2(2,2))) + (2.170138888888889*((
      0.96*msd2(2,2) - 1.02*msq2(2,2))*(-2.8224*msd2(2,2)*msu2(2,2) +
      0.9603999999999999*Quad(mAInput) - 2.8224*msd2(2,2)*Sqr(mAInput) -
      1.9207999999999998*msu2(2,2)*Sqr(mAInput) + 1.8432*Sqr(msd2(2,2)) +
      0.9603999999999999*Sqr(msu2(2,2))) + (-1.92*msd2(2,2) + 1.02*msq2(2,2))*
      TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),0.96*msd2(2,2)))*TPhi(0.98*Sqr(
      mAInput),0.98*msu2(2,2),0.96*msd2(2,2)))/(Sqr(msd2(2,2))*Sqr(0.96*msd2(2,2)
      - 1.02*msq2(2,2))) + (1.9607843137254901*TDelta(0.98*Sqr(mAInput),0.98*msu2(
      2,2),1.02*msq2(2,2))*TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2)))/
      (msq2(2,2)*Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)))) + (AtInput + MuInput*
      TanBeta)*(3*(AbInput - MuInput*TanBeta)*(Log(0.98*Sqr(mAInput))*((2*Log(0.96
      *msd2(2,2)))/(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (2*Log(1.02*msq2(2,2)))/(
      -0.96*msd2(2,2) + 1.02*msq2(2,2))) + Log(1.02*msq2(2,2))*(4/(0.96*msd2(2,2)
      - 1.02*msq2(2,2)) + (4*Log(Sqr(SCALE)))/(0.96*msd2(2,2) - 1.02*msq2(2,2)) +
      (2*Log(0.98*msu2(2,2)))/(-0.96*msd2(2,2) + 1.02*msq2(2,2))) + Log(0.96*msd2(
      2,2))*((2*Log(0.98*msu2(2,2)))/(0.96*msd2(2,2) - 1.02*msq2(2,2)) + 4/(-0.96*
      msd2(2,2) + 1.02*msq2(2,2)) + (4*Log(Sqr(SCALE)))/(-0.96*msd2(2,2) + 1.02*
      msq2(2,2))) + (2.170138888888889*(-2.8224*msd2(2,2)*msu2(2,2) +
      0.9603999999999999*Quad(mAInput) - 2.8224*msd2(2,2)*Sqr(mAInput) -
      1.9207999999999998*msu2(2,2)*Sqr(mAInput) + 1.8432*Sqr(msd2(2,2)) +
      0.9603999999999999*Sqr(msu2(2,2)) - TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),
      0.96*msd2(2,2)))*TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),0.96*msd2(2,2)))/((
      0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(msd2(2,2))) - (1.9223375624759709*(
      -2.9988*msq2(2,2)*msu2(2,2) + 0.9603999999999999*Quad(mAInput) - 2.9988*msq2
      (2,2)*Sqr(mAInput) - 1.9207999999999998*msu2(2,2)*Sqr(mAInput) + 2.0808*Sqr(
      msq2(2,2)) + 0.9603999999999999*Sqr(msu2(2,2)) - TDelta(0.98*Sqr(mAInput),
      0.98*msu2(2,2),1.02*msq2(2,2)))*TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*
      msq2(2,2)))/((0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(msq2(2,2)))) + 3*Cube(
      AbInput - MuInput*TanBeta)*(Log(0.96*msd2(2,2))*((4*Log(Sqr(SCALE))*(0.96*
      msd2(2,2) + 1.02*msq2(2,2)))/Cube(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (4*(
      2.88*msd2(2,2) + 1.02*msq2(2,2)))/Cube(0.96*msd2(2,2) - 1.02*msq2(2,2)) - (2
      *Log(0.98*msu2(2,2))*(0.96*msd2(2,2) + 1.02*msq2(2,2) + 1.96*msu2(2,2) -
      1.96*Sqr(mAInput)))/Cube(0.96*msd2(2,2) - 1.02*msq2(2,2))) + Log(1.02*msq2(2
      ,2))*((-4*Log(Sqr(SCALE))*(0.96*msd2(2,2) + 1.02*msq2(2,2)))/Cube(0.96*msd2(
      2,2) - 1.02*msq2(2,2)) - (4*(0.96*msd2(2,2) + 3.06*msq2(2,2)))/Cube(0.96*
      msd2(2,2) - 1.02*msq2(2,2)) + (2*Log(0.98*msu2(2,2))*(0.96*msd2(2,2) + 1.02*
      msq2(2,2) + 1.96*msu2(2,2) - 1.96*Sqr(mAInput)))/Cube(0.96*msd2(2,2) - 1.02*
      msq2(2,2))) + Log(0.98*Sqr(mAInput))*((-2*Log(0.96*msd2(2,2))*(0.96*msd2(2,2
      ) + 1.02*msq2(2,2) - 1.96*msu2(2,2) + 1.96*Sqr(mAInput)))/Cube(0.96*msd2(2,2
      ) - 1.02*msq2(2,2)) + (2*Log(1.02*msq2(2,2))*(0.96*msd2(2,2) + 1.02*msq2(2,2
      ) - 1.96*msu2(2,2) + 1.96*Sqr(mAInput)))/Cube(0.96*msd2(2,2) - 1.02*msq2(2,2
      ))) - 16/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) - (8*Log(Sqr(SCALE)))/Sqr(0.96
      *msd2(2,2) - 1.02*msq2(2,2)) + (2.170138888888889*((0.96*msd2(2,2) - 1.02*
      msq2(2,2))*(-2.8224*msd2(2,2)*msu2(2,2) + 0.9603999999999999*Quad(mAInput) -
      2.8224*msd2(2,2)*Sqr(mAInput) - 1.9207999999999998*msu2(2,2)*Sqr(mAInput) +
      1.8432*Sqr(msd2(2,2)) + 0.9603999999999999*Sqr(msu2(2,2))) + (-2.88*msd2(2,
      2) + 1.02*msq2(2,2))*TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),0.96*msd2(2,2))
      )*TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),0.96*msd2(2,2)))/(Cube(0.96*msd2(2,2
      ) - 1.02*msq2(2,2))*Sqr(msd2(2,2))) + (1.9223375624759709*((0.96*msd2(2,2) -
      1.02*msq2(2,2))*(-2.9988*msq2(2,2)*msu2(2,2) + 0.9603999999999999*Quad(
      mAInput) - 2.9988*msq2(2,2)*Sqr(mAInput) - 1.9207999999999998*msu2(2,2)*Sqr(
      mAInput) + 2.0808*Sqr(msq2(2,2)) + 0.9603999999999999*Sqr(msu2(2,2))) - (
      0.96*msd2(2,2) - 3.06*msq2(2,2))*TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),
      1.02*msq2(2,2)))*TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2)))/(
      Cube(0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(msq2(2,2))))) + Sqr(TanBeta)*(3*
      Sqr(AbInput + MuInput/TanBeta)*((-2*Log(0.96*msd2(2,2))*(0.96*msd2(2,2) -
      1.02*msq2(2,2) + 0.98*Sqr(mAInput)))/TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2)
      ,0.96*msd2(2,2)) + (1.0416666666666667*Log(0.98*Sqr(mAInput))*(Sqr(0.98*Sqr(
      mAInput) + 0.96*msd2(2,2) - 1.02*msq2(2,2)) - TDelta(0.98*Sqr(mAInput),1.02*
      msq2(2,2),0.96*msd2(2,2))))/(msd2(2,2)*TDelta(0.98*Sqr(mAInput),1.02*msq2(2,
      2),0.96*msd2(2,2))) + (1.0416666666666667*Log(1.02*msq2(2,2))*(
      -0.9603999999999999*Quad(mAInput) + 1.9992*msq2(2,2)*Sqr(mAInput) + 0.9216*
      Sqr(msd2(2,2)) - 1.0404*Sqr(msq2(2,2)) + TDelta(0.98*Sqr(mAInput),1.02*msq2(
      2,2),0.96*msd2(2,2))))/(msd2(2,2)*TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),
      0.96*msd2(2,2))) + (1.0850694444444444*(-1.02*msq2(2,2) + 0.98*Sqr(mAInput)
      + ((0.96*msd2(2,2) - 1.02*msq2(2,2) + 0.98*Sqr(mAInput))*(1.02*(0.96*msd2(2,
      2) - 1.02*msq2(2,2))*msq2(2,2) - 0.9603999999999999*Quad(mAInput) + 0.98*(
      0.96*msd2(2,2) + 2.04*msq2(2,2))*Sqr(mAInput)))/TDelta(0.98*Sqr(mAInput),
      1.02*msq2(2,2),0.96*msd2(2,2)))*TPhi(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*
      msd2(2,2)))/Sqr(msd2(2,2))) + 3*(AbInput + MuInput/TanBeta)*(AbInput -
      MuInput*TanBeta)*((2*Log(0.96*msd2(2,2))*Log(1.02*msq2(2,2)))/(0.96*msd2(2,2
      ) - 1.02*msq2(2,2)) + Log(0.98*Sqr(mAInput))*((2*Log(1.02*msq2(2,2)))/(0.96*
      msd2(2,2) - 1.02*msq2(2,2)) + (2*Log(0.96*msd2(2,2)))/(-0.96*msd2(2,2) +
      1.02*msq2(2,2))) + (2*Sqr(Log(1.02*msq2(2,2))))/(-0.96*msd2(2,2) + 1.02*msq2
      (2,2)) - (2.0833333333333335*(0.96*msd2(2,2) - 1.02*msq2(2,2) + 0.98*Sqr(
      mAInput))*TPhi(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2)))/(msd2(2,2)*
      (0.96*msd2(2,2) - 1.02*msq2(2,2))) + (1.9215686274509802*Sqr(mAInput)*TPhi(
      0.98*Sqr(mAInput),1.02*msq2(2,2),1.02*msq2(2,2)))/((0.96*msd2(2,2) - 1.02*
      msq2(2,2))*msq2(2,2))) + 3*((4 + Log(0.96*msd2(2,2)) - Log(0.98*msu2(2,2)))*
      Log(0.98*Sqr(mAInput)) + Log(1.02*msq2(2,2))*(-2 - 2*Log(Sqr(SCALE))) + Log(
      0.96*msd2(2,2))*(-2 + Log(0.98*msu2(2,2)) - 2*Log(Sqr(SCALE))) + 2*Sqr(Log(
      Sqr(SCALE))) + Sqr(Log(1.02*msq2(2,2))) - (0.9607843137254901*Sqr(mAInput)*
      TPhi(0.98*Sqr(mAInput),1.02*msq2(2,2),1.02*msq2(2,2)))/msq2(2,2) + (
      1.0850694444444444*(-2.8224*msd2(2,2)*msu2(2,2) + 0.9603999999999999*Quad(
      mAInput) - 2.8224*msd2(2,2)*Sqr(mAInput) - 1.9207999999999998*msu2(2,2)*Sqr(
      mAInput) + 1.8432*Sqr(msd2(2,2)) + 0.9603999999999999*Sqr(msu2(2,2)) -
      TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),0.96*msd2(2,2)))*TPhi(0.98*Sqr(
      mAInput),0.98*msu2(2,2),0.96*msd2(2,2)))/Sqr(msd2(2,2))) + Sqr(AbInput -
      MuInput*TanBeta)*(3*Sqr(AbInput + MuInput/TanBeta)*(Sqr(Log(1.02*msq2(2,2)))
      /Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) + Log(0.96*msd2(2,2))*(-(Log(1.02*msq2
      (2,2))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))) - (2*(0.96*msd2(2,2) - 1.02*
      msq2(2,2) + 0.98*Sqr(mAInput)))/((0.96*msd2(2,2) - 1.02*msq2(2,2))*TDelta(
      0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2)))) + Log(0.98*Sqr(mAInput))*
      (Log(0.96*msd2(2,2))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) - Log(1.02*msq2(2,
      2))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (1.0416666666666667*(Sqr(0.98*Sqr
      (mAInput) + 0.96*msd2(2,2) - 1.02*msq2(2,2)) - TDelta(0.98*Sqr(mAInput),1.02
      *msq2(2,2),0.96*msd2(2,2))))/(msd2(2,2)*(0.96*msd2(2,2) - 1.02*msq2(2,2))*
      TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2)))) + (
      1.0416666666666667*Log(1.02*msq2(2,2))*(-0.9603999999999999*Quad(mAInput) +
      1.9992*msq2(2,2)*Sqr(mAInput) + 0.9216*Sqr(msd2(2,2)) - 1.0404*Sqr(msq2(2,2)
      ) + TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2))))/(msd2(2,2)*(
      0.96*msd2(2,2) - 1.02*msq2(2,2))*TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),
      0.96*msd2(2,2))) + (1.0850694444444444*((0.96*msd2(2,2) - 1.02*msq2(2,2))*(
      0.96*msd2(2,2) - 1.02*msq2(2,2) + 0.98*Sqr(mAInput))*(1.02*(0.96*msd2(2,2) -
      1.02*msq2(2,2))*msq2(2,2) - 0.9603999999999999*Quad(mAInput) + 0.98*(0.96*
      msd2(2,2) + 2.04*msq2(2,2))*Sqr(mAInput)) + (0.98*(1.92*msd2(2,2) - 1.02*
      msq2(2,2))*Sqr(mAInput) + Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)))*TDelta(0.98*
      Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2)))*TPhi(0.98*Sqr(mAInput),1.02*
      msq2(2,2),0.96*msd2(2,2)))/(Sqr(msd2(2,2))*Sqr(0.96*msd2(2,2) - 1.02*msq2(2,
      2))*TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2))) - (
      0.9607843137254901*Sqr(mAInput)*TPhi(0.98*Sqr(mAInput),1.02*msq2(2,2),1.02*
      msq2(2,2)))/(msq2(2,2)*Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)))) + 3*(4/(-0.96*
      msd2(2,2) + 1.02*msq2(2,2)) + (2*Log(Sqr(SCALE)))/(-0.96*msd2(2,2) + 1.02*
      msq2(2,2)) + Log(0.96*msd2(2,2))*((2.04*Log(Sqr(SCALE))*msq2(2,2))/Sqr(0.96*
      msd2(2,2) - 1.02*msq2(2,2)) + (2*(0.96*msd2(2,2) + 1.02*msq2(2,2)))/Sqr(0.96
      *msd2(2,2) - 1.02*msq2(2,2)) - (Log(0.98*msu2(2,2))*(1.02*msq2(2,2) + 0.98*
      msu2(2,2) - 0.98*Sqr(mAInput)))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))) + Log(
      1.02*msq2(2,2))*((-4.08*msq2(2,2))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) - (
      2.04*Log(Sqr(SCALE))*msq2(2,2))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (Log(
      0.98*msu2(2,2))*(1.02*msq2(2,2) + 0.98*msu2(2,2) - 0.98*Sqr(mAInput)))/Sqr(
      0.96*msd2(2,2) - 1.02*msq2(2,2))) + Log(0.98*Sqr(mAInput))*(-((Log(0.96*msd2
      (2,2))*(1.02*msq2(2,2) - 0.98*msu2(2,2) + 0.98*Sqr(mAInput)))/Sqr(0.96*msd2(
      2,2) - 1.02*msq2(2,2))) + (Log(1.02*msq2(2,2))*(1.02*msq2(2,2) - 0.98*msu2(2
      ,2) + 0.98*Sqr(mAInput)))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))) + (
      1.0850694444444444*((0.96*msd2(2,2) - 1.02*msq2(2,2))*(-2.8224*msd2(2,2)*
      msu2(2,2) + 0.9603999999999999*Quad(mAInput) - 2.8224*msd2(2,2)*Sqr(mAInput)
      - 1.9207999999999998*msu2(2,2)*Sqr(mAInput) + 1.8432*Sqr(msd2(2,2)) +
      0.9603999999999999*Sqr(msu2(2,2))) + (-1.92*msd2(2,2) + 1.02*msq2(2,2))*
      TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),0.96*msd2(2,2)))*TPhi(0.98*Sqr(
      mAInput),0.98*msu2(2,2),0.96*msd2(2,2)))/(Sqr(msd2(2,2))*Sqr(0.96*msd2(2,2)
      - 1.02*msq2(2,2))) + (0.9803921568627451*TDelta(0.98*Sqr(mAInput),0.98*msu2(
      2,2),1.02*msq2(2,2))*TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2)))/
      (msq2(2,2)*Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))))) + (AtInput -
      MuInput/TanBeta)*(3*(AbInput + MuInput/TanBeta)*(Log(0.98*Sqr(mAInput))*((2*
      Log(0.98*msu2(2,2)))/(1.02*msq2(2,2) - 0.98*msu2(2,2)) + (2*Log(1.02*msq2(2,
      2)))/(-1.02*msq2(2,2) + 0.98*msu2(2,2))) + Log(0.96*msd2(2,2))*((2*Log(1.02*
      msq2(2,2)))/(1.02*msq2(2,2) - 0.98*msu2(2,2)) + (2*Log(0.98*msu2(2,2)))/(
      -1.02*msq2(2,2) + 0.98*msu2(2,2))) + (2.170138888888889*(-2.9375999999999998
      *msd2(2,2)*msq2(2,2) + 0.9603999999999999*Quad(mAInput) - 2.8224*msd2(2,2)*
      Sqr(mAInput) - 1.9992*msq2(2,2)*Sqr(mAInput) + 1.8432*Sqr(msd2(2,2)) +
      1.0404*Sqr(msq2(2,2)) - TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,
      2)))*TPhi(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2)))/((1.02*msq2(2,2)
      - 0.98*msu2(2,2))*Sqr(msd2(2,2))) - (2.170138888888889*(-2.8224*msd2(2,2)*
      msu2(2,2) + 0.9603999999999999*Quad(mAInput) - 2.8224*msd2(2,2)*Sqr(mAInput)
      - 1.9207999999999998*msu2(2,2)*Sqr(mAInput) + 1.8432*Sqr(msd2(2,2)) +
      0.9603999999999999*Sqr(msu2(2,2)) - TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),
      0.96*msd2(2,2)))*TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),0.96*msd2(2,2)))/((
      1.02*msq2(2,2) - 0.98*msu2(2,2))*Sqr(msd2(2,2)))) + 3*(AbInput - MuInput*
      TanBeta)*(Log(0.98*Sqr(mAInput))*((2*Log(0.96*msd2(2,2)))/(-0.96*msd2(2,2) +
      1.02*msq2(2,2)) + 2*Log(1.02*msq2(2,2))*(1/(0.96*msd2(2,2) - 1.02*msq2(2,2)
      ) + 1/(-1.02*msq2(2,2) + 0.98*msu2(2,2))) + (2*Log(0.98*msu2(2,2)))/(1.02*
      msq2(2,2) - 0.98*msu2(2,2))) + Log(0.96*msd2(2,2))*((2*Log(1.02*msq2(2,2))*(
      0.96*msd2(2,2) + 1.02*msq2(2,2) - 0.98*Sqr(mAInput)))/((0.96*msd2(2,2) -
      1.02*msq2(2,2))*(1.02*msq2(2,2) - 0.98*msu2(2,2))) - (2*Log(0.98*msu2(2,2))*
      (0.96*msd2(2,2) + 0.98*msu2(2,2) - 0.98*Sqr(mAInput)))/((0.96*msd2(2,2) -
      1.02*msq2(2,2))*(1.02*msq2(2,2) - 0.98*msu2(2,2)))) + (2*Log(1.02*msq2(2,2))
      *Log(0.98*msu2(2,2))*(1.02*msq2(2,2) + 0.98*msu2(2,2) - 0.98*Sqr(mAInput)))/
      ((0.96*msd2(2,2) - 1.02*msq2(2,2))*(1.02*msq2(2,2) - 0.98*msu2(2,2))) + (2*(
      -2.04*msq2(2,2) + 0.98*Sqr(mAInput))*Sqr(Log(1.02*msq2(2,2))))/((0.96*msd2(2
      ,2) - 1.02*msq2(2,2))*(1.02*msq2(2,2) - 0.98*msu2(2,2))) + (2*TDelta(0.98*
      Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2))*TPhi(0.98*Sqr(mAInput),1.02*msq2
      (2,2),0.96*msd2(2,2)))/((1.02*msq2(2,2) - 0.98*msu2(2,2))*(-0.9792*msd2(2,2)
      *msq2(2,2) + 0.9216*Sqr(msd2(2,2)))) - (1.9607843137254901*TDelta(0.98*Sqr(
      mAInput),1.02*msq2(2,2),1.02*msq2(2,2))*TPhi(0.98*Sqr(mAInput),1.02*msq2(2,2
      ),1.02*msq2(2,2)))/((0.96*msd2(2,2) - 1.02*msq2(2,2))*msq2(2,2)*(1.02*msq2(2
      ,2) - 0.98*msu2(2,2))) - (2*TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),0.96*
      msd2(2,2))*TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),0.96*msd2(2,2)))/((1.02*
      msq2(2,2) - 0.98*msu2(2,2))*(-0.9792*msd2(2,2)*msq2(2,2) + 0.9216*Sqr(msd2(2
      ,2)))) + (1.9607843137254901*TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*
      msq2(2,2))*TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2)))/((0.96*
      msd2(2,2) - 1.02*msq2(2,2))*msq2(2,2)*(1.02*msq2(2,2) - 0.98*msu2(2,2)))) +
      3*(AbInput + MuInput/TanBeta)*Sqr(AbInput - MuInput*TanBeta)*(Log(0.98*Sqr(
      mAInput))*((2*Log(0.96*msd2(2,2)))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) - (2
      *Log(1.02*msq2(2,2)))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))) + Log(0.96*msd2(
      2,2))*((2*Log(0.98*msu2(2,2))*(1.02*msq2(2,2) + 0.98*msu2(2,2) - 0.98*Sqr(
      mAInput)))/((1.02*msq2(2,2) - 0.98*msu2(2,2))*Sqr(0.96*msd2(2,2) - 1.02*msq2
      (2,2))) + (2*Log(1.02*msq2(2,2))*(-2.04*msq2(2,2) + 0.98*Sqr(mAInput)))/((
      1.02*msq2(2,2) - 0.98*msu2(2,2))*Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)))) - (2
      *Log(1.02*msq2(2,2))*Log(0.98*msu2(2,2))*(1.02*msq2(2,2) + 0.98*msu2(2,2) -
      0.98*Sqr(mAInput)))/((1.02*msq2(2,2) - 0.98*msu2(2,2))*Sqr(0.96*msd2(2,2) -
      1.02*msq2(2,2))) + ((4.08*msq2(2,2) - 1.96*Sqr(mAInput))*Sqr(Log(1.02*msq2(2
      ,2))))/((1.02*msq2(2,2) - 0.98*msu2(2,2))*Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2
      ))) + (2.170138888888889*((0.96*msd2(2,2) - 1.02*msq2(2,2))*(
      -2.9375999999999998*msd2(2,2)*msq2(2,2) + 0.9603999999999999*Quad(mAInput) -
      2.8224*msd2(2,2)*Sqr(mAInput) - 1.9992*msq2(2,2)*Sqr(mAInput) + 1.8432*Sqr(
      msd2(2,2)) + 1.0404*Sqr(msq2(2,2))) + (-1.92*msd2(2,2) + 1.02*msq2(2,2))*
      TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2)))*TPhi(0.98*Sqr(
      mAInput),1.02*msq2(2,2),0.96*msd2(2,2)))/((1.02*msq2(2,2) - 0.98*msu2(2,2))*
      Sqr(msd2(2,2))*Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))) + (1.9607843137254901*
      TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),1.02*msq2(2,2))*TPhi(0.98*Sqr(
      mAInput),1.02*msq2(2,2),1.02*msq2(2,2)))/(msq2(2,2)*(1.02*msq2(2,2) - 0.98*
      msu2(2,2))*Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))) - (2.170138888888889*((0.96
      *msd2(2,2) - 1.02*msq2(2,2))*(-2.8224*msd2(2,2)*msu2(2,2) +
      0.9603999999999999*Quad(mAInput) - 2.8224*msd2(2,2)*Sqr(mAInput) -
      1.9207999999999998*msu2(2,2)*Sqr(mAInput) + 1.8432*Sqr(msd2(2,2)) +
      0.9603999999999999*Sqr(msu2(2,2))) + (-1.92*msd2(2,2) + 1.02*msq2(2,2))*
      TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),0.96*msd2(2,2)))*TPhi(0.98*Sqr(
      mAInput),0.98*msu2(2,2),0.96*msd2(2,2)))/((1.02*msq2(2,2) - 0.98*msu2(2,2))*
      Sqr(msd2(2,2))*Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))) - (1.9607843137254901*
      TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2))*TPhi(0.98*Sqr(
      mAInput),0.98*msu2(2,2),1.02*msq2(2,2)))/(msq2(2,2)*(1.02*msq2(2,2) - 0.98*
      msu2(2,2))*Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))))) + Sqr(AtInput -
      MuInput/TanBeta)*(3*Sqr(AbInput + MuInput/TanBeta)*(Log(0.96*msd2(2,2))*(-(
      Log(1.02*msq2(2,2))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) + Log(0.98*msu2(2,
      2))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)) - (2*(0.96*msd2(2,2) - 1.02*msq2(2,
      2) + 0.98*Sqr(mAInput)))/((1.02*msq2(2,2) - 0.98*msu2(2,2))*TDelta(0.98*Sqr(
      mAInput),1.02*msq2(2,2),0.96*msd2(2,2)))) + Log(0.98*Sqr(mAInput))*(Log(1.02
      *msq2(2,2))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)) - Log(0.98*msu2(2,2))/Sqr(
      1.02*msq2(2,2) - 0.98*msu2(2,2)) + (1.0416666666666667*(Sqr(0.98*Sqr(mAInput
      ) + 0.96*msd2(2,2) - 1.02*msq2(2,2)) - TDelta(0.98*Sqr(mAInput),1.02*msq2(2,
      2),0.96*msd2(2,2))))/(msd2(2,2)*(1.02*msq2(2,2) - 0.98*msu2(2,2))*TDelta(
      0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2)))) + (1.0416666666666667*Log
      (1.02*msq2(2,2))*(-0.9603999999999999*Quad(mAInput) + 1.9992*msq2(2,2)*Sqr(
      mAInput) + 0.9216*Sqr(msd2(2,2)) - 1.0404*Sqr(msq2(2,2)) + TDelta(0.98*Sqr(
      mAInput),1.02*msq2(2,2),0.96*msd2(2,2))))/(msd2(2,2)*(1.02*msq2(2,2) - 0.98*
      msu2(2,2))*TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2))) + (
      1.0850694444444444*(-((1.02*msq2(2,2) - 0.98*msu2(2,2))*(0.96*msd2(2,2) -
      1.02*msq2(2,2) + 0.98*Sqr(mAInput))*(1.02*msq2(2,2)*(-0.96*msd2(2,2) + 1.02*
      msq2(2,2)) + 0.9603999999999999*Quad(mAInput) - 0.98*(0.96*msd2(2,2) + 2.04*
      msq2(2,2))*Sqr(mAInput))) + TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*
      msd2(2,2))*(2.9375999999999998*msd2(2,2)*msq2(2,2) + 1.02*msq2(2,2)*(-2.04*
      msq2(2,2) + 0.98*msu2(2,2)) - 0.9603999999999999*Quad(mAInput) + 2.94*(0.96*
      msd2(2,2) + 1.02*msq2(2,2))*Sqr(mAInput) - 0.9603999999999999*msu2(2,2)*Sqr(
      mAInput) - 1.8432*Sqr(msd2(2,2)) + TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),
      0.96*msd2(2,2))))*TPhi(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2)))/(
      Sqr(msd2(2,2))*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))*TDelta(0.98*Sqr(mAInput)
      ,1.02*msq2(2,2),0.96*msd2(2,2))) + (1.0850694444444444*(-2.8224*msd2(2,2)*
      msu2(2,2) + 0.9603999999999999*Quad(mAInput) - 2.8224*msd2(2,2)*Sqr(mAInput)
      - 1.9207999999999998*msu2(2,2)*Sqr(mAInput) + 1.8432*Sqr(msd2(2,2)) +
      0.9603999999999999*Sqr(msu2(2,2)) - TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),
      0.96*msd2(2,2)))*TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),0.96*msd2(2,2)))/(Sqr
      (msd2(2,2))*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)))) + 3*(4/(-1.02*msq2(2,2) +
      0.98*msu2(2,2)) + Log(Sqr(SCALE))*(2/(-1.02*msq2(2,2) + 0.98*msu2(2,2)) - (
      1.96*Log(0.98*msu2(2,2))*msu2(2,2))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) +
      Log(1.02*msq2(2,2))*((2*(1.02*msq2(2,2) + 0.98*msu2(2,2)))/Sqr(1.02*msq2(2,2
      ) - 0.98*msu2(2,2)) + (1.96*Log(Sqr(SCALE))*msu2(2,2))/Sqr(1.02*msq2(2,2) -
      0.98*msu2(2,2)) + (Log(0.98*msu2(2,2))*(1.02*msq2(2,2) + 0.98*msu2(2,2) -
      0.98*Sqr(mAInput)))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) + Log(0.98*Sqr(
      mAInput))*(-((Log(1.02*msq2(2,2))*(-1.02*msq2(2,2) + 0.98*msu2(2,2) + 0.98*
      Sqr(mAInput)))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) + (Log(0.98*msu2(2,2))*
      (-1.02*msq2(2,2) + 0.98*msu2(2,2) + 0.98*Sqr(mAInput)))/Sqr(1.02*msq2(2,2) -
      0.98*msu2(2,2))) - (3.92*Log(0.98*msu2(2,2))*msu2(2,2))/Sqr(1.02*msq2(2,2)
      - 0.98*msu2(2,2)) - ((1.02*msq2(2,2) + 0.98*msu2(2,2) - 0.98*Sqr(mAInput))*
      Sqr(Log(1.02*msq2(2,2))))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)) - (
      0.9803921568627451*(0.98*(1.02*msq2(2,2) - 0.98*msu2(2,2))*Sqr(mAInput) +
      TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),1.02*msq2(2,2)))*TPhi(0.98*Sqr(
      mAInput),1.02*msq2(2,2),1.02*msq2(2,2)))/(msq2(2,2)*Sqr(1.02*msq2(2,2) -
      0.98*msu2(2,2))) + (0.9803921568627451*TDelta(0.98*Sqr(mAInput),0.98*msu2(2,
      2),1.02*msq2(2,2))*TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2)))/(
      msq2(2,2)*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)))) + 3*(AbInput +
      MuInput/TanBeta)*(AbInput - MuInput*TanBeta)*(Log(0.98*Sqr(mAInput))*((2*Log
      (1.02*msq2(2,2)))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)) - (2*Log(0.98*msu2(2,
      2)))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) + Log(0.96*msd2(2,2))*((-2*Log(
      1.02*msq2(2,2))*(0.96*msd2(2,2) + 0.98*msu2(2,2) - 0.98*Sqr(mAInput)))/((
      0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) + (2*
      Log(0.98*msu2(2,2))*(0.96*msd2(2,2) + 0.98*msu2(2,2) - 0.98*Sqr(mAInput)))/(
      (0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)))) - (
      2*Log(1.02*msq2(2,2))*Log(0.98*msu2(2,2))*(1.02*msq2(2,2) + 0.98*msu2(2,2) -
      0.98*Sqr(mAInput)))/((0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(1.02*msq2(2,2) -
      0.98*msu2(2,2))) + (2*(1.02*msq2(2,2) + 0.98*msu2(2,2) - 0.98*Sqr(mAInput))
      *Sqr(Log(1.02*msq2(2,2))))/((0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(1.02*msq2(
      2,2) - 0.98*msu2(2,2))) - (2.0833333333333335*((1.02*msq2(2,2) - 0.98*msu2(2
      ,2))*(0.96*msd2(2,2) - 1.02*msq2(2,2) + 0.98*Sqr(mAInput)) + TDelta(0.98*Sqr
      (mAInput),1.02*msq2(2,2),0.96*msd2(2,2)))*TPhi(0.98*Sqr(mAInput),1.02*msq2(2
      ,2),0.96*msd2(2,2)))/(msd2(2,2)*(0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(1.02*
      msq2(2,2) - 0.98*msu2(2,2))) + (1.9607843137254901*(0.98*(1.02*msq2(2,2) -
      0.98*msu2(2,2))*Sqr(mAInput) + TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),1.02*
      msq2(2,2)))*TPhi(0.98*Sqr(mAInput),1.02*msq2(2,2),1.02*msq2(2,2)))/((0.96*
      msd2(2,2) - 1.02*msq2(2,2))*msq2(2,2)*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)))
      + (2.0833333333333335*TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),0.96*msd2(2,2)
      )*TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),0.96*msd2(2,2)))/(msd2(2,2)*(0.96*
      msd2(2,2) - 1.02*msq2(2,2))*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) - (
      1.9607843137254901*TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2))*
      TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2)))/((0.96*msd2(2,2) -
      1.02*msq2(2,2))*msq2(2,2)*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)))) + 3*Sqr(
      AbInput + MuInput/TanBeta)*Sqr(AbInput - MuInput*TanBeta)*(-(((1.02*msq2(2,2
      ) + 0.98*msu2(2,2) - 0.98*Sqr(mAInput))*Sqr(Log(1.02*msq2(2,2))))/(Sqr(0.96*
      msd2(2,2) - 1.02*msq2(2,2))*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)))) + Log(
      0.96*msd2(2,2))*((Log(1.02*msq2(2,2))*(1.02*msq2(2,2) + 0.98*msu2(2,2) -
      0.98*Sqr(mAInput)))/(Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(1.02*msq2(2,2)
      - 0.98*msu2(2,2))) - (Log(0.98*msu2(2,2))*(1.02*msq2(2,2) + 0.98*msu2(2,2)
      - 0.98*Sqr(mAInput)))/(Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(1.02*msq2(2,
      2) - 0.98*msu2(2,2))) - (2*(0.96*msd2(2,2) - 1.02*msq2(2,2) + 0.98*Sqr(
      mAInput)))/((0.96*msd2(2,2) - 1.02*msq2(2,2))*(1.02*msq2(2,2) - 0.98*msu2(2,
      2))*TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2)))) + (
      1.0416666666666667*Log(0.98*Sqr(mAInput))*(Sqr(0.98*Sqr(mAInput) + 0.96*msd2
      (2,2) - 1.02*msq2(2,2)) - TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(
      2,2))))/(msd2(2,2)*(0.96*msd2(2,2) - 1.02*msq2(2,2))*(1.02*msq2(2,2) - 0.98*
      msu2(2,2))*TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2))) + Log(
      1.02*msq2(2,2))*((Log(0.98*msu2(2,2))*(1.02*msq2(2,2) + 0.98*msu2(2,2) -
      0.98*Sqr(mAInput)))/(Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(1.02*msq2(2,2)
      - 0.98*msu2(2,2))) + (-0.9603999999999999*Quad(mAInput) + 1.9992*msq2(2,2)*
      Sqr(mAInput) + 0.9216*Sqr(msd2(2,2)) - 1.0404*Sqr(msq2(2,2)) + TDelta(0.98*
      Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2)))/((1.02*msq2(2,2) - 0.98*msu2(2,
      2))*(-0.9792*msd2(2,2)*msq2(2,2) + 0.9216*Sqr(msd2(2,2)))*TDelta(0.98*Sqr(
      mAInput),1.02*msq2(2,2),0.96*msd2(2,2)))) + (1.0850694444444444*((0.96*msd2(
      2,2) - 1.02*msq2(2,2))*(1.02*msq2(2,2) - 0.98*msu2(2,2))*(0.96*msd2(2,2) -
      1.02*msq2(2,2) + 0.98*Sqr(mAInput))*(1.02*(0.96*msd2(2,2) - 1.02*msq2(2,2))*
      msq2(2,2) - 0.9603999999999999*Quad(mAInput) + 0.98*(0.96*msd2(2,2) + 2.04*
      msq2(2,2))*Sqr(mAInput)) + TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2
      (2,2))*(0.9603999999999999*(-0.96*msd2(2,2) + 1.02*msq2(2,2))*Quad(mAInput)
      + 0.98*Sqr(mAInput)*(0.96*msd2(2,2)*(1.02*msq2(2,2) - 1.96*msu2(2,2)) + 1.02
      *msq2(2,2)*(-3.06*msq2(2,2) + 0.98*msu2(2,2)) + 2.7648*Sqr(msd2(2,2))) - (
      1.92*msd2(2,2) - 2.04*msq2(2,2) + 0.98*msu2(2,2))*Sqr(0.96*msd2(2,2) - 1.02*
      msq2(2,2)) + (1.92*msd2(2,2) - 1.02*msq2(2,2))*TDelta(0.98*Sqr(mAInput),1.02
      *msq2(2,2),0.96*msd2(2,2))))*TPhi(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2
      (2,2)))/(Sqr(msd2(2,2))*Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(1.02*msq2(2
      ,2) - 0.98*msu2(2,2))*TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2)
      )) - (0.9803921568627451*(0.98*(1.02*msq2(2,2) - 0.98*msu2(2,2))*Sqr(mAInput
      ) + TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),1.02*msq2(2,2)))*TPhi(0.98*Sqr(
      mAInput),1.02*msq2(2,2),1.02*msq2(2,2)))/(msq2(2,2)*Sqr(0.96*msd2(2,2) -
      1.02*msq2(2,2))*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) + (1.0850694444444444*
      ((0.96*msd2(2,2) - 1.02*msq2(2,2))*(-2.8224*msd2(2,2)*msu2(2,2) +
      0.9603999999999999*Quad(mAInput) - 2.8224*msd2(2,2)*Sqr(mAInput) -
      1.9207999999999998*msu2(2,2)*Sqr(mAInput) + 1.8432*Sqr(msd2(2,2)) +
      0.9603999999999999*Sqr(msu2(2,2))) + (-1.92*msd2(2,2) + 1.02*msq2(2,2))*
      TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),0.96*msd2(2,2)))*TPhi(0.98*Sqr(
      mAInput),0.98*msu2(2,2),0.96*msd2(2,2)))/(Sqr(msd2(2,2))*Sqr(0.96*msd2(2,2)
      - 1.02*msq2(2,2))*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) + (
      0.9803921568627451*TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2))*
      TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2)))/(msq2(2,2)*Sqr(0.96*
      msd2(2,2) - 1.02*msq2(2,2))*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)))))) + (
      AtInput - MuInput/TanBeta)*(3*(AbInput + MuInput/TanBeta)*(Log(0.98*Sqr(
      mAInput))*((2*Log(0.98*msu2(2,2)))/(1.02*msq2(2,2) - 0.98*msu2(2,2)) + (2*
      Log(1.02*msq2(2,2)))/(-1.02*msq2(2,2) + 0.98*msu2(2,2))) + Log(0.96*msd2(2,2
      ))*((2*Log(1.02*msq2(2,2)))/(1.02*msq2(2,2) - 0.98*msu2(2,2)) + (2*Log(0.98*
      msu2(2,2)))/(-1.02*msq2(2,2) + 0.98*msu2(2,2))) + (2.170138888888889*(
      -2.9375999999999998*msd2(2,2)*msq2(2,2) + 0.9603999999999999*Quad(mAInput) -
      2.8224*msd2(2,2)*Sqr(mAInput) - 1.9992*msq2(2,2)*Sqr(mAInput) + 1.8432*Sqr(
      msd2(2,2)) + 1.0404*Sqr(msq2(2,2)) - TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2)
      ,0.96*msd2(2,2)))*TPhi(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2)))/((
      1.02*msq2(2,2) - 0.98*msu2(2,2))*Sqr(msd2(2,2))) - (2.170138888888889*(
      -2.8224*msd2(2,2)*msu2(2,2) + 0.9603999999999999*Quad(mAInput) - 2.8224*msd2
      (2,2)*Sqr(mAInput) - 1.9207999999999998*msu2(2,2)*Sqr(mAInput) + 1.8432*Sqr(
      msd2(2,2)) + 0.9603999999999999*Sqr(msu2(2,2)) - TDelta(0.98*Sqr(mAInput),
      0.98*msu2(2,2),0.96*msd2(2,2)))*TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),0.96*
      msd2(2,2)))/((1.02*msq2(2,2) - 0.98*msu2(2,2))*Sqr(msd2(2,2)))) + 3*(AbInput
      - MuInput*TanBeta)*(Log(0.98*Sqr(mAInput))*((2*Log(0.96*msd2(2,2)))/(-0.96*
      msd2(2,2) + 1.02*msq2(2,2)) + 2*Log(1.02*msq2(2,2))*(1/(0.96*msd2(2,2) -
      1.02*msq2(2,2)) + 1/(-1.02*msq2(2,2) + 0.98*msu2(2,2))) + (2*Log(0.98*msu2(2
      ,2)))/(1.02*msq2(2,2) - 0.98*msu2(2,2))) + Log(0.96*msd2(2,2))*((2*Log(1.02*
      msq2(2,2))*(0.96*msd2(2,2) + 1.02*msq2(2,2) - 0.98*Sqr(mAInput)))/((0.96*
      msd2(2,2) - 1.02*msq2(2,2))*(1.02*msq2(2,2) - 0.98*msu2(2,2))) - (2*Log(0.98
      *msu2(2,2))*(0.96*msd2(2,2) + 0.98*msu2(2,2) - 0.98*Sqr(mAInput)))/((0.96*
      msd2(2,2) - 1.02*msq2(2,2))*(1.02*msq2(2,2) - 0.98*msu2(2,2)))) + (2*Log(
      1.02*msq2(2,2))*Log(0.98*msu2(2,2))*(1.02*msq2(2,2) + 0.98*msu2(2,2) - 0.98*
      Sqr(mAInput)))/((0.96*msd2(2,2) - 1.02*msq2(2,2))*(1.02*msq2(2,2) - 0.98*
      msu2(2,2))) + (2*(-2.04*msq2(2,2) + 0.98*Sqr(mAInput))*Sqr(Log(1.02*msq2(2,2
      ))))/((0.96*msd2(2,2) - 1.02*msq2(2,2))*(1.02*msq2(2,2) - 0.98*msu2(2,2))) +
      (2*TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2))*TPhi(0.98*Sqr(
      mAInput),1.02*msq2(2,2),0.96*msd2(2,2)))/((1.02*msq2(2,2) - 0.98*msu2(2,2))*
      (-0.9792*msd2(2,2)*msq2(2,2) + 0.9216*Sqr(msd2(2,2)))) - (1.9607843137254901
      *TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),1.02*msq2(2,2))*TPhi(0.98*Sqr(
      mAInput),1.02*msq2(2,2),1.02*msq2(2,2)))/((0.96*msd2(2,2) - 1.02*msq2(2,2))*
      msq2(2,2)*(1.02*msq2(2,2) - 0.98*msu2(2,2))) - (2*TDelta(0.98*Sqr(mAInput),
      0.98*msu2(2,2),0.96*msd2(2,2))*TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),0.96*
      msd2(2,2)))/((1.02*msq2(2,2) - 0.98*msu2(2,2))*(-0.9792*msd2(2,2)*msq2(2,2)
      + 0.9216*Sqr(msd2(2,2)))) + (1.9607843137254901*TDelta(0.98*Sqr(mAInput),
      0.98*msu2(2,2),1.02*msq2(2,2))*TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*
      msq2(2,2)))/((0.96*msd2(2,2) - 1.02*msq2(2,2))*msq2(2,2)*(1.02*msq2(2,2) -
      0.98*msu2(2,2)))) + 3*(AbInput + MuInput/TanBeta)*Sqr(AbInput - MuInput*
      TanBeta)*(Log(0.98*Sqr(mAInput))*((2*Log(0.96*msd2(2,2)))/Sqr(0.96*msd2(2,2)
      - 1.02*msq2(2,2)) - (2*Log(1.02*msq2(2,2)))/Sqr(0.96*msd2(2,2) - 1.02*msq2(
      2,2))) + Log(0.96*msd2(2,2))*((2*Log(0.98*msu2(2,2))*(1.02*msq2(2,2) + 0.98*
      msu2(2,2) - 0.98*Sqr(mAInput)))/((1.02*msq2(2,2) - 0.98*msu2(2,2))*Sqr(0.96*
      msd2(2,2) - 1.02*msq2(2,2))) + (2*Log(1.02*msq2(2,2))*(-2.04*msq2(2,2) +
      0.98*Sqr(mAInput)))/((1.02*msq2(2,2) - 0.98*msu2(2,2))*Sqr(0.96*msd2(2,2) -
      1.02*msq2(2,2)))) - (2*Log(1.02*msq2(2,2))*Log(0.98*msu2(2,2))*(1.02*msq2(2,
      2) + 0.98*msu2(2,2) - 0.98*Sqr(mAInput)))/((1.02*msq2(2,2) - 0.98*msu2(2,2))
      *Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))) + ((4.08*msq2(2,2) - 1.96*Sqr(mAInput
      ))*Sqr(Log(1.02*msq2(2,2))))/((1.02*msq2(2,2) - 0.98*msu2(2,2))*Sqr(0.96*
      msd2(2,2) - 1.02*msq2(2,2))) + (2.170138888888889*((0.96*msd2(2,2) - 1.02*
      msq2(2,2))*(-2.9375999999999998*msd2(2,2)*msq2(2,2) + 0.9603999999999999*
      Quad(mAInput) - 2.8224*msd2(2,2)*Sqr(mAInput) - 1.9992*msq2(2,2)*Sqr(mAInput
      ) + 1.8432*Sqr(msd2(2,2)) + 1.0404*Sqr(msq2(2,2))) + (-1.92*msd2(2,2) + 1.02
      *msq2(2,2))*TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2)))*TPhi(
      0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2)))/((1.02*msq2(2,2) - 0.98*
      msu2(2,2))*Sqr(msd2(2,2))*Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))) + (
      1.9607843137254901*TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),1.02*msq2(2,2))*
      TPhi(0.98*Sqr(mAInput),1.02*msq2(2,2),1.02*msq2(2,2)))/(msq2(2,2)*(1.02*msq2
      (2,2) - 0.98*msu2(2,2))*Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))) - (
      2.170138888888889*((0.96*msd2(2,2) - 1.02*msq2(2,2))*(-2.8224*msd2(2,2)*msu2
      (2,2) + 0.9603999999999999*Quad(mAInput) - 2.8224*msd2(2,2)*Sqr(mAInput) -
      1.9207999999999998*msu2(2,2)*Sqr(mAInput) + 1.8432*Sqr(msd2(2,2)) +
      0.9603999999999999*Sqr(msu2(2,2))) + (-1.92*msd2(2,2) + 1.02*msq2(2,2))*
      TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),0.96*msd2(2,2)))*TPhi(0.98*Sqr(
      mAInput),0.98*msu2(2,2),0.96*msd2(2,2)))/((1.02*msq2(2,2) - 0.98*msu2(2,2))*
      Sqr(msd2(2,2))*Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))) - (1.9607843137254901*
      TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2))*TPhi(0.98*Sqr(
      mAInput),0.98*msu2(2,2),1.02*msq2(2,2)))/(msq2(2,2)*(1.02*msq2(2,2) - 0.98*
      msu2(2,2))*Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)))) + (AtInput + MuInput*
      TanBeta)*(3*(Log(0.98*Sqr(mAInput))*((2*Log(0.98*msu2(2,2)))/(1.02*msq2(2,2)
      - 0.98*msu2(2,2)) + (2*Log(1.02*msq2(2,2)))/(-1.02*msq2(2,2) + 0.98*msu2(2,
      2))) + (2*Log(1.02*msq2(2,2))*Log(0.98*msu2(2,2)))/(-1.02*msq2(2,2) + 0.98*
      msu2(2,2)) + (2*Sqr(Log(1.02*msq2(2,2))))/(1.02*msq2(2,2) - 0.98*msu2(2,2))
      - (1.9223375624759709*(-0.98*(-5.1*msq2(2,2) + 0.98*Sqr(mAInput))*Sqr(
      mAInput) + TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),1.02*msq2(2,2)))*TPhi(
      0.98*Sqr(mAInput),1.02*msq2(2,2),1.02*msq2(2,2)))/((1.02*msq2(2,2) - 0.98*
      msu2(2,2))*Sqr(msq2(2,2))) - (1.9223375624759709*(-2.9988*msq2(2,2)*msu2(2,2
      ) + 0.9603999999999999*Quad(mAInput) - 2.9988*msq2(2,2)*Sqr(mAInput) -
      1.9207999999999998*msu2(2,2)*Sqr(mAInput) + 2.0808*Sqr(msq2(2,2)) +
      0.9603999999999999*Sqr(msu2(2,2)) - TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),
      1.02*msq2(2,2)))*TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2)))/((
      1.02*msq2(2,2) - 0.98*msu2(2,2))*Sqr(msq2(2,2)))) + 3*(AbInput +
      MuInput/TanBeta)*(AbInput - MuInput*TanBeta)*(Log(0.96*msd2(2,2))*((2*Log(
      1.02*msq2(2,2)))/((0.96*msd2(2,2) - 1.02*msq2(2,2))*(1.02*msq2(2,2) - 0.98*
      msu2(2,2))) + (2*Log(0.98*msu2(2,2)))/((0.96*msd2(2,2) - 1.02*msq2(2,2))*(
      -1.02*msq2(2,2) + 0.98*msu2(2,2)))) + (2*Log(1.02*msq2(2,2))*Log(0.98*msu2(2
      ,2)))/((0.96*msd2(2,2) - 1.02*msq2(2,2))*(1.02*msq2(2,2) - 0.98*msu2(2,2)))
      + (2*Sqr(Log(1.02*msq2(2,2))))/((0.96*msd2(2,2) - 1.02*msq2(2,2))*(-1.02*
      msq2(2,2) + 0.98*msu2(2,2))) + (2.170138888888889*(-2.9375999999999998*msd2(
      2,2)*msq2(2,2) + 0.9603999999999999*Quad(mAInput) - 2.8224*msd2(2,2)*Sqr(
      mAInput) - 1.9992*msq2(2,2)*Sqr(mAInput) + 1.8432*Sqr(msd2(2,2)) + 1.0404*
      Sqr(msq2(2,2)) - TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2)))*
      TPhi(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2)))/((0.96*msd2(2,2) -
      1.02*msq2(2,2))*(1.02*msq2(2,2) - 0.98*msu2(2,2))*Sqr(msd2(2,2))) + (
      1.9223375624759709*(-0.98*(-5.1*msq2(2,2) + 0.98*Sqr(mAInput))*Sqr(mAInput)
      + TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),1.02*msq2(2,2)))*TPhi(0.98*Sqr(
      mAInput),1.02*msq2(2,2),1.02*msq2(2,2)))/((0.96*msd2(2,2) - 1.02*msq2(2,2))*
      (1.02*msq2(2,2) - 0.98*msu2(2,2))*Sqr(msq2(2,2))) - (2.170138888888889*(
      -2.8224*msd2(2,2)*msu2(2,2) + 0.9603999999999999*Quad(mAInput) - 2.8224*msd2
      (2,2)*Sqr(mAInput) - 1.9207999999999998*msu2(2,2)*Sqr(mAInput) + 1.8432*Sqr(
      msd2(2,2)) + 0.9603999999999999*Sqr(msu2(2,2)) - TDelta(0.98*Sqr(mAInput),
      0.98*msu2(2,2),0.96*msd2(2,2)))*TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),0.96*
      msd2(2,2)))/((0.96*msd2(2,2) - 1.02*msq2(2,2))*(1.02*msq2(2,2) - 0.98*msu2(2
      ,2))*Sqr(msd2(2,2))) + (1.9223375624759709*(-2.9988*msq2(2,2)*msu2(2,2) +
      0.9603999999999999*Quad(mAInput) - 2.9988*msq2(2,2)*Sqr(mAInput) -
      1.9207999999999998*msu2(2,2)*Sqr(mAInput) + 2.0808*Sqr(msq2(2,2)) +
      0.9603999999999999*Sqr(msu2(2,2)) - TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),
      1.02*msq2(2,2)))*TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2)))/((
      0.96*msd2(2,2) - 1.02*msq2(2,2))*(1.02*msq2(2,2) - 0.98*msu2(2,2))*Sqr(msq2(
      2,2)))) + 3*(AbInput + MuInput/TanBeta)*Cube(AbInput - MuInput*TanBeta)*(((4
      *Log(0.96*msd2(2,2)))/Cube(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (4*Log(1.02*
      msq2(2,2)))/Cube(-0.96*msd2(2,2) + 1.02*msq2(2,2)))*Log(0.98*Sqr(mAInput)) +
      Log(0.96*msd2(2,2))*((2*Log(1.02*msq2(2,2))*(0.96*msd2(2,2) + 3.06*msq2(2,2
      ) - 1.96*Sqr(mAInput)))/(Cube(0.96*msd2(2,2) - 1.02*msq2(2,2))*(-1.02*msq2(2
      ,2) + 0.98*msu2(2,2))) + (2*Log(0.98*msu2(2,2))*(0.96*msd2(2,2) + 1.02*msq2(
      2,2) + 1.96*msu2(2,2) - 1.96*Sqr(mAInput)))/(Cube(0.96*msd2(2,2) - 1.02*msq2
      (2,2))*(1.02*msq2(2,2) - 0.98*msu2(2,2)))) - (2*Log(1.02*msq2(2,2))*Log(0.98
      *msu2(2,2))*(0.96*msd2(2,2) + 1.02*msq2(2,2) + 1.96*msu2(2,2) - 1.96*Sqr(
      mAInput)))/(Cube(0.96*msd2(2,2) - 1.02*msq2(2,2))*(1.02*msq2(2,2) - 0.98*
      msu2(2,2))) + (2*(0.96*msd2(2,2) + 3.06*msq2(2,2) - 1.96*Sqr(mAInput))*Sqr(
      Log(1.02*msq2(2,2))))/(Cube(0.96*msd2(2,2) - 1.02*msq2(2,2))*(1.02*msq2(2,2)
      - 0.98*msu2(2,2))) + (2.170138888888889*((0.96*msd2(2,2) - 1.02*msq2(2,2))*
      (-2.9375999999999998*msd2(2,2)*msq2(2,2) + 0.9603999999999999*Quad(mAInput)
      - 2.8224*msd2(2,2)*Sqr(mAInput) - 1.9992*msq2(2,2)*Sqr(mAInput) + 1.8432*Sqr
      (msd2(2,2)) + 1.0404*Sqr(msq2(2,2))) + (-2.88*msd2(2,2) + 1.02*msq2(2,2))*
      TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2)))*TPhi(0.98*Sqr(
      mAInput),1.02*msq2(2,2),0.96*msd2(2,2)))/(Cube(0.96*msd2(2,2) - 1.02*msq2(2,
      2))*(1.02*msq2(2,2) - 0.98*msu2(2,2))*Sqr(msd2(2,2))) + (1.9223375624759709*
      (0.98*(0.96*msd2(2,2) - 1.02*msq2(2,2))*(-5.1*msq2(2,2) + 0.98*Sqr(mAInput))
      *Sqr(mAInput) - (0.96*msd2(2,2) - 3.06*msq2(2,2))*TDelta(0.98*Sqr(mAInput),
      1.02*msq2(2,2),1.02*msq2(2,2)))*TPhi(0.98*Sqr(mAInput),1.02*msq2(2,2),1.02*
      msq2(2,2)))/(Cube(0.96*msd2(2,2) - 1.02*msq2(2,2))*(1.02*msq2(2,2) - 0.98*
      msu2(2,2))*Sqr(msq2(2,2))) - (2.170138888888889*((0.96*msd2(2,2) - 1.02*msq2
      (2,2))*(-2.8224*msd2(2,2)*msu2(2,2) + 0.9603999999999999*Quad(mAInput) -
      2.8224*msd2(2,2)*Sqr(mAInput) - 1.9207999999999998*msu2(2,2)*Sqr(mAInput) +
      1.8432*Sqr(msd2(2,2)) + 0.9603999999999999*Sqr(msu2(2,2))) + (-2.88*msd2(2,2
      ) + 1.02*msq2(2,2))*TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),0.96*msd2(2,2)))
      *TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),0.96*msd2(2,2)))/(Cube(0.96*msd2(2,2)
      - 1.02*msq2(2,2))*(1.02*msq2(2,2) - 0.98*msu2(2,2))*Sqr(msd2(2,2))) + (
      1.9223375624759709*(-((0.96*msd2(2,2) - 1.02*msq2(2,2))*(-2.9988*msq2(2,2)*
      msu2(2,2) + 0.9603999999999999*Quad(mAInput) - 2.9988*msq2(2,2)*Sqr(mAInput)
      - 1.9207999999999998*msu2(2,2)*Sqr(mAInput) + 2.0808*Sqr(msq2(2,2)) +
      0.9603999999999999*Sqr(msu2(2,2)))) + (0.96*msd2(2,2) - 3.06*msq2(2,2))*
      TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2)))*TPhi(0.98*Sqr(
      mAInput),0.98*msu2(2,2),1.02*msq2(2,2)))/(Cube(0.96*msd2(2,2) - 1.02*msq2(2,
      2))*(1.02*msq2(2,2) - 0.98*msu2(2,2))*Sqr(msq2(2,2)))) + 3*Sqr(AbInput -
      MuInput*TanBeta)*(Log(0.98*Sqr(mAInput))*((-2*Log(0.96*msd2(2,2)))/Sqr(0.96*
      msd2(2,2) - 1.02*msq2(2,2)) + (2*Log(1.02*msq2(2,2)))/Sqr(0.96*msd2(2,2) -
      1.02*msq2(2,2))) + Log(0.96*msd2(2,2))*((2*Log(1.02*msq2(2,2))*(0.96*msd2(2,
      2) + 1.02*msq2(2,2) - 0.98*Sqr(mAInput)))/((1.02*msq2(2,2) - 0.98*msu2(2,2))
      *Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))) - (2*Log(0.98*msu2(2,2))*(0.96*msd2(2
      ,2) + 0.98*msu2(2,2) - 0.98*Sqr(mAInput)))/((1.02*msq2(2,2) - 0.98*msu2(2,2)
      )*Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)))) + (2*Log(1.02*msq2(2,2))*Log(0.98*
      msu2(2,2))*(0.96*msd2(2,2) + 0.98*msu2(2,2) - 0.98*Sqr(mAInput)))/((1.02*
      msq2(2,2) - 0.98*msu2(2,2))*Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))) + (2*(
      -0.96*msd2(2,2) - 1.02*msq2(2,2) + 0.98*Sqr(mAInput))*Sqr(Log(1.02*msq2(2,2)
      )))/((1.02*msq2(2,2) - 0.98*msu2(2,2))*Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)))
      + (2.0833333333333335*TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2
      ))*TPhi(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2)))/(msd2(2,2)*(1.02*
      msq2(2,2) - 0.98*msu2(2,2))*Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))) + (
      1.9223375624759709*(0.98*(-0.96*msd2(2,2) + 1.02*msq2(2,2))*(-5.1*msq2(2,2)
      + 0.98*Sqr(mAInput))*Sqr(mAInput) + (0.96*msd2(2,2) - 2.04*msq2(2,2))*TDelta
      (0.98*Sqr(mAInput),1.02*msq2(2,2),1.02*msq2(2,2)))*TPhi(0.98*Sqr(mAInput),
      1.02*msq2(2,2),1.02*msq2(2,2)))/((1.02*msq2(2,2) - 0.98*msu2(2,2))*Sqr(0.96*
      msd2(2,2) - 1.02*msq2(2,2))*Sqr(msq2(2,2))) - (2.0833333333333335*TDelta(
      0.98*Sqr(mAInput),0.98*msu2(2,2),0.96*msd2(2,2))*TPhi(0.98*Sqr(mAInput),0.98
      *msu2(2,2),0.96*msd2(2,2)))/(msd2(2,2)*(1.02*msq2(2,2) - 0.98*msu2(2,2))*Sqr
      (0.96*msd2(2,2) - 1.02*msq2(2,2))) + (1.9223375624759709*((0.96*msd2(2,2) -
      1.02*msq2(2,2))*(-2.9988*msq2(2,2)*msu2(2,2) + 0.9603999999999999*Quad(
      mAInput) - 2.9988*msq2(2,2)*Sqr(mAInput) - 1.9207999999999998*msu2(2,2)*Sqr(
      mAInput) + 2.0808*Sqr(msq2(2,2)) + 0.9603999999999999*Sqr(msu2(2,2))) - (
      0.96*msd2(2,2) - 2.04*msq2(2,2))*TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),
      1.02*msq2(2,2)))*TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2)))/((
      1.02*msq2(2,2) - 0.98*msu2(2,2))*Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(
      msq2(2,2)))))) + ((1 + Sqr(TanBeta))*(3*Quad(AbInput - MuInput*TanBeta)*((
      0.9607843137254901*Log(0.98*msu2(2,2))*(0.96*msd2(2,2) + 5.1*msq2(2,2))*msu2
      (2,2))/(Cube(0.96*msd2(2,2) - 1.02*msq2(2,2))*msq2(2,2)) + (
      0.9803921568627451*Log(Sqr(SCALE))*(1.02*msq2(2,2)*(1.02*msq2(2,2) + 4.9*
      msu2(2,2) - 10.3*Sqr(MuInput)) + 0.96*msd2(2,2)*(5.1*msq2(2,2) + 0.98*msu2(2
      ,2) - 2.06*Sqr(MuInput))))/(Cube(-0.96*msd2(2,2) + 1.02*msq2(2,2))*msq2(2,2)
      ) + (0.9803921568627451*(1.02*msq2(2,2)*(3.06*msq2(2,2) + 4.9*msu2(2,2) -
      16.48*Sqr(MuInput)) + 0.96*msd2(2,2)*(9.18*msq2(2,2) + 0.98*msu2(2,2) - 2.06
      *Sqr(MuInput))))/(Cube(-0.96*msd2(2,2) + 1.02*msq2(2,2))*msq2(2,2)) - (2*
      PolyLog(2,1 - (1.0729166666666667*Sqr(MuInput))/msd2(2,2))*(0.96*msd2(2,2) +
      2.04*msq2(2,2) - 3.09*Sqr(MuInput))*(0.96*msd2(2,2) - 1.03*Sqr(MuInput)))
      /Quad(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (2*PolyLog(2,1 - (
      1.0098039215686274*Sqr(MuInput))/msq2(2,2))*(0.96*msd2(2,2) + 2.04*msq2(2,2)
      - 3.09*Sqr(MuInput))*(0.96*msd2(2,2) - 1.03*Sqr(MuInput)))/Quad(0.96*msd2(2
      ,2) - 1.02*msq2(2,2)) + Log(1.03*Sqr(MuInput))*((-6.365399999999999*Log(1.02
      *msq2(2,2))*Quad(MuInput))/Quad(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (
      2.019607843137255*(0.96*msd2(2,2) + 2.04*msq2(2,2))*Sqr(MuInput))/(Cube(
      -0.96*msd2(2,2) + 1.02*msq2(2,2))*msq2(2,2))) + ((0.96*msd2(2,2) + 2.04*msq2
      (2,2) - 3.09*Sqr(MuInput))*(-0.96*msd2(2,2) + 1.03*Sqr(MuInput))*Sqr(Log(
      0.96*msd2(2,2))))/Quad(0.96*msd2(2,2) - 1.02*msq2(2,2)) + ((0.96*msd2(2,2) +
      2.04*msq2(2,2) - 3.09*Sqr(MuInput))*(0.96*msd2(2,2) - 1.03*Sqr(MuInput))*
      Sqr(Log(1.02*msq2(2,2))))/Quad(0.96*msd2(2,2) - 1.02*msq2(2,2)) + Log(1.02*
      msq2(2,2))*((1.96*Log(0.98*msu2(2,2))*(1.92*msd2(2,2) + 1.02*msq2(2,2))*msu2
      (2,2))/Quad(0.96*msd2(2,2) - 1.02*msq2(2,2)) - (1.02*msq2(2,2)*(1.02*msq2(2,
      2) + 1.96*msu2(2,2) - 10.3*Sqr(MuInput)) + 0.96*msd2(2,2)*(10.2*msq2(2,2) +
      3.92*msu2(2,2) - 8.24*Sqr(MuInput)) + 0.9216*Sqr(msd2(2,2)))/Quad(0.96*msd2(
      2,2) - 1.02*msq2(2,2)) - (2*Log(Sqr(SCALE))*(1.02*msq2(2,2)*(0.98*msu2(2,2)
      - 2.06*Sqr(MuInput)) + 1.92*msd2(2,2)*(1.02*msq2(2,2) + 0.98*msu2(2,2) -
      2.06*Sqr(MuInput)) + 0.9216*Sqr(msd2(2,2))))/Quad(0.96*msd2(2,2) - 1.02*msq2
      (2,2))) + Log(0.96*msd2(2,2))*((-1.96*Log(0.98*msu2(2,2))*(1.92*msd2(2,2) +
      1.02*msq2(2,2))*msu2(2,2))/Quad(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (
      6.365399999999999*Log(1.03*Sqr(MuInput))*Quad(MuInput))/Quad(0.96*msd2(2,2)
      - 1.02*msq2(2,2)) + (2*Log(Sqr(SCALE))*(1.02*msq2(2,2)*(0.98*msu2(2,2) -
      2.06*Sqr(MuInput)) + 1.92*msd2(2,2)*(1.02*msq2(2,2) + 0.98*msu2(2,2) - 2.06*
      Sqr(MuInput)) + 0.9216*Sqr(msd2(2,2))))/Quad(0.96*msd2(2,2) - 1.02*msq2(2,2)
      ) + (2*(0.96*msd2(2,2)*(3.06*msq2(2,2) + 1.96*msu2(2,2) - 7.21*Sqr(MuInput))
      + 1.02*msq2(2,2)*(0.98*msu2(2,2) - 2.06*Sqr(MuInput)) + 2.7648*Sqr(msd2(2,2
      ))))/Quad(0.96*msd2(2,2) - 1.02*msq2(2,2)))) + 3*Sqr(AbInput - MuInput*
      TanBeta)*((1.9215686274509802*Log(0.98*msu2(2,2))*msu2(2,2))/(msq2(2,2)*(
      -0.96*msd2(2,2) + 1.02*msq2(2,2))) + (1.9607843137254901*Log(Sqr(SCALE))*(
      2.04*msq2(2,2) + 0.98*msu2(2,2) - 2.06*Sqr(MuInput)))/((0.96*msd2(2,2) -
      1.02*msq2(2,2))*msq2(2,2)) + (1.9607843137254901*(3.06*msq2(2,2) + 0.98*msu2
      (2,2) - 2.06*Sqr(MuInput)))/((0.96*msd2(2,2) - 1.02*msq2(2,2))*msq2(2,2)) +
      Log(0.96*msd2(2,2))*((1.96*Log(0.98*msu2(2,2))*msu2(2,2))/Sqr(0.96*msd2(2,2)
      - 1.02*msq2(2,2)) - (2*Log(Sqr(SCALE))*(1.92*msd2(2,2) + 0.98*msu2(2,2) -
      2.06*Sqr(MuInput)))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) - (2*(2.88*msd2(2,2
      ) + 0.98*msu2(2,2) - 2.06*Sqr(MuInput)))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)
      )) + Log(1.02*msq2(2,2))*((-1.96*Log(0.98*msu2(2,2))*msu2(2,2))/Sqr(0.96*
      msd2(2,2) - 1.02*msq2(2,2)) + (2*Log(Sqr(SCALE))*(1.92*msd2(2,2) + 0.98*msu2
      (2,2) - 2.06*Sqr(MuInput)))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (2*(0.96*
      msd2(2,2) + 2.04*msq2(2,2) + 0.98*msu2(2,2) - 2.06*Sqr(MuInput)))/Sqr(0.96*
      msd2(2,2) - 1.02*msq2(2,2))) + (4*PolyLog(2,1 - (1.0729166666666667*Sqr(
      MuInput))/msd2(2,2))*(0.96*msd2(2,2) - 1.03*Sqr(MuInput)))/Sqr(0.96*msd2(2,2
      ) - 1.02*msq2(2,2)) - (4*PolyLog(2,1 - (1.0098039215686274*Sqr(MuInput))
      /msq2(2,2))*(0.96*msd2(2,2) - 1.03*Sqr(MuInput)))/Sqr(0.96*msd2(2,2) - 1.02*
      msq2(2,2)) + (2*(0.96*msd2(2,2) - 1.03*Sqr(MuInput))*Sqr(Log(0.96*msd2(2,2))
      ))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) - (2*(0.96*msd2(2,2) - 1.03*Sqr(
      MuInput))*Sqr(Log(1.02*msq2(2,2))))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (
      4.12*Log(1.03*Sqr(MuInput))*Sqr(MuInput))/(0.9792*msd2(2,2)*msq2(2,2) -
      1.0404*Sqr(msq2(2,2)))) + 3*(-0.5 + Log(1.02*msq2(2,2))*(-1 - 2*Log(Sqr(
      SCALE))) - (0.9607843137254901*msu2(2,2))/msq2(2,2) + 2*PolyLog(2,1 - (
      1.0098039215686274*Sqr(MuInput))/msq2(2,2)) + 1.03*(1.9607843137254901/msq2(
      2,2) + 1/(0.98*msu2(2,2) - 1.03*Sqr(MuInput)))*Sqr(MuInput) + 2*Sqr(Log(Sqr(
      SCALE))) + Sqr(Log(1.02*msq2(2,2))) + Log(Sqr(SCALE))*((0.9803921568627451*(
      -3.0282*msu2(2,2)*Sqr(MuInput) + 2.06*Sqr(MuInput)*(1.02*msq2(2,2) + 1.03*
      Sqr(MuInput)) + 0.9603999999999999*Sqr(msu2(2,2))))/(msq2(2,2)*(-0.98*msu2(2
      ,2) + 1.03*Sqr(MuInput))) + Log(0.98*msu2(2,2))*(-2 + (2.1218*Quad(MuInput))
      /Sqr(-0.98*msu2(2,2) + 1.03*Sqr(MuInput)))) + PolyLog(2,1 - (
      1.0510204081632653*Sqr(MuInput))/msu2(2,2))*(2 - (4.2436*Quad(MuInput))/Sqr(
      -0.98*msu2(2,2) + 1.03*Sqr(MuInput))) + Sqr(Log(0.98*msu2(2,2)))*(1 - (
      2.1218*Quad(MuInput))/Sqr(-0.98*msu2(2,2) + 1.03*Sqr(MuInput))) + Log(1.03*
      Sqr(MuInput))*((2.1218*Log(0.98*msu2(2,2))*Quad(MuInput))/Sqr(-0.98*msu2(2,2
      ) + 1.03*Sqr(MuInput)) - (2.1218*Log(Sqr(SCALE))*Quad(MuInput))/Sqr(-0.98*
      msu2(2,2) + 1.03*Sqr(MuInput)) - (1.0098039215686274*Sqr(MuInput)*(1.96*(
      1.02*msq2(2,2) + 0.98*msu2(2,2))*msu2(2,2) + 2.1218*Quad(MuInput) + 1.03*(
      1.02*msq2(2,2) - 3.92*msu2(2,2))*Sqr(MuInput)))/(msq2(2,2)*Sqr(-0.98*msu2(2,
      2) + 1.03*Sqr(MuInput)))) + (0.9607843137254901*Log(0.98*msu2(2,2))*msu2(2,2
      )*(0.98*(1.02*msq2(2,2) + 0.98*msu2(2,2))*msu2(2,2) + 1.0609*Quad(MuInput) +
      2.06*(1.02*msq2(2,2) - 0.98*msu2(2,2))*Sqr(MuInput)))/(msq2(2,2)*Sqr(-0.98*
      msu2(2,2) + 1.03*Sqr(MuInput)))) + (3*Quad(AbInput - MuInput*TanBeta)*((
      0.9607843137254901*(0.96*msd2(2,2) + 5.1*msq2(2,2))*Sqr(mAInput))/(Cube(
      -0.96*msd2(2,2) + 1.02*msq2(2,2))*msq2(2,2)) + (0.9607843137254901*Log(Sqr(
      SCALE))*(0.96*msd2(2,2) + 5.1*msq2(2,2))*Sqr(mAInput))/(Cube(-0.96*msd2(2,2)
      + 1.02*msq2(2,2))*msq2(2,2)) + Log(0.98*Sqr(mAInput))*((0.9607843137254901*
      (0.96*msd2(2,2) + 5.1*msq2(2,2))*Sqr(mAInput))/(Cube(0.96*msd2(2,2) - 1.02*
      msq2(2,2))*msq2(2,2)) - (1.96*Log(0.96*msd2(2,2))*(1.92*msd2(2,2) + 1.02*
      msq2(2,2))*Sqr(mAInput))/Quad(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (1.96*Log(
      1.02*msq2(2,2))*(1.92*msd2(2,2) + 1.02*msq2(2,2))*Sqr(mAInput))/Quad(0.96*
      msd2(2,2) - 1.02*msq2(2,2))) + Log(1.02*msq2(2,2))*((-1.96*(1.92*msd2(2,2) +
      1.02*msq2(2,2))*Sqr(mAInput))/Quad(0.96*msd2(2,2) - 1.02*msq2(2,2)) - (1.96
      *Log(Sqr(SCALE))*(1.92*msd2(2,2) + 1.02*msq2(2,2))*Sqr(mAInput))/Quad(0.96*
      msd2(2,2) - 1.02*msq2(2,2))) + Log(0.96*msd2(2,2))*((1.96*(1.92*msd2(2,2) +
      1.02*msq2(2,2))*Sqr(mAInput))/Quad(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (1.96*
      Log(Sqr(SCALE))*(1.92*msd2(2,2) + 1.02*msq2(2,2))*Sqr(mAInput))/Quad(0.96*
      msd2(2,2) - 1.02*msq2(2,2)))) + 3*(0.5 + Log(0.96*msd2(2,2))*(-2 + Log(0.98*
      msu2(2,2)) - 2*Log(Sqr(SCALE))) + 0.3333333333333333*Sqr(3.141592653589793)
      + Log(0.98*Sqr(mAInput))*(Log(0.96*msd2(2,2)) - Log(0.98*msu2(2,2)) - 2*Log(
      Sqr(SCALE)) + (0.9803921568627451*(1.02*msq2(2,2) + 0.98*Sqr(mAInput)))/msq2
      (2,2)) - (0.9607843137254901*Sqr(mAInput))/msq2(2,2) + Log(Sqr(SCALE))*(1 -
      (0.9607843137254901*Sqr(mAInput))/msq2(2,2)) + Sqr(Log(0.98*Sqr(mAInput))) +
      2*Sqr(Log(Sqr(SCALE))) + (1.0850694444444444*(-2.8224*msd2(2,2)*msu2(2,2) +
      0.9603999999999999*Quad(mAInput) - 2.8224*msd2(2,2)*Sqr(mAInput) -
      1.9207999999999998*msu2(2,2)*Sqr(mAInput) + 1.8432*Sqr(msd2(2,2)) +
      0.9603999999999999*Sqr(msu2(2,2)) - TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),
      0.96*msd2(2,2)))*TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),0.96*msd2(2,2)))/Sqr(
      msd2(2,2))) + 3*Sqr(AbInput - MuInput*TanBeta)*((1.9607843137254901*(-2.04*
      msq2(2,2) + 0.98*Sqr(mAInput)))/((0.96*msd2(2,2) - 1.02*msq2(2,2))*msq2(2,2)
      ) + (1.9607843137254901*Log(Sqr(SCALE))*(-1.02*msq2(2,2) + 0.98*Sqr(mAInput)
      ))/((0.96*msd2(2,2) - 1.02*msq2(2,2))*msq2(2,2)) + Log(0.96*msd2(2,2))*((2*(
      0.96*msd2(2,2) + 1.02*msq2(2,2) - 0.98*Sqr(mAInput)))/Sqr(0.96*msd2(2,2) -
      1.02*msq2(2,2)) - (Log(0.98*msu2(2,2))*(1.02*msq2(2,2) + 0.98*msu2(2,2) -
      0.98*Sqr(mAInput)))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) - (2*Log(Sqr(SCALE)
      )*(-1.02*msq2(2,2) + 0.98*Sqr(mAInput)))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)
      )) + Log(1.02*msq2(2,2))*((Log(0.98*msu2(2,2))*(1.02*msq2(2,2) + 0.98*msu2(2
      ,2) - 0.98*Sqr(mAInput)))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (2*(-2.04*
      msq2(2,2) + 0.98*Sqr(mAInput)))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (2*
      Log(Sqr(SCALE))*(-1.02*msq2(2,2) + 0.98*Sqr(mAInput)))/Sqr(0.96*msd2(2,2) -
      1.02*msq2(2,2))) + Log(0.98*Sqr(mAInput))*((1.9215686274509802*Sqr(mAInput))
      /(msq2(2,2)*(-0.96*msd2(2,2) + 1.02*msq2(2,2))) + (Log(0.96*msd2(2,2))*(
      -1.02*msq2(2,2) + 0.98*msu2(2,2) + 0.98*Sqr(mAInput)))/Sqr(0.96*msd2(2,2) -
      1.02*msq2(2,2)) - (Log(1.02*msq2(2,2))*(-1.02*msq2(2,2) + 0.98*msu2(2,2) +
      0.98*Sqr(mAInput)))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))) + (
      1.0850694444444444*((0.96*msd2(2,2) - 1.02*msq2(2,2))*(-2.8224*msd2(2,2)*
      msu2(2,2) + 0.9603999999999999*Quad(mAInput) - 2.8224*msd2(2,2)*Sqr(mAInput)
      - 1.9207999999999998*msu2(2,2)*Sqr(mAInput) + 1.8432*Sqr(msd2(2,2)) +
      0.9603999999999999*Sqr(msu2(2,2))) + (-1.92*msd2(2,2) + 1.02*msq2(2,2))*
      TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),0.96*msd2(2,2)))*TPhi(0.98*Sqr(
      mAInput),0.98*msu2(2,2),0.96*msd2(2,2)))/(Sqr(msd2(2,2))*Sqr(0.96*msd2(2,2)
      - 1.02*msq2(2,2))) + (0.9803921568627451*TDelta(0.98*Sqr(mAInput),0.98*msu2(
      2,2),1.02*msq2(2,2))*TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2)))/
      (msq2(2,2)*Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)))) + (AtInput + MuInput*
      TanBeta)*(3*(AbInput - MuInput*TanBeta)*(Log(0.98*Sqr(mAInput))*((2*Log(0.96
      *msd2(2,2)))/(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (2*Log(1.02*msq2(2,2)))/(
      -0.96*msd2(2,2) + 1.02*msq2(2,2))) + Log(1.02*msq2(2,2))*(4/(0.96*msd2(2,2)
      - 1.02*msq2(2,2)) + (4*Log(Sqr(SCALE)))/(0.96*msd2(2,2) - 1.02*msq2(2,2)) +
      (2*Log(0.98*msu2(2,2)))/(-0.96*msd2(2,2) + 1.02*msq2(2,2))) + Log(0.96*msd2(
      2,2))*((2*Log(0.98*msu2(2,2)))/(0.96*msd2(2,2) - 1.02*msq2(2,2)) + 4/(-0.96*
      msd2(2,2) + 1.02*msq2(2,2)) + (4*Log(Sqr(SCALE)))/(-0.96*msd2(2,2) + 1.02*
      msq2(2,2))) + (2.170138888888889*(-2.8224*msd2(2,2)*msu2(2,2) +
      0.9603999999999999*Quad(mAInput) - 2.8224*msd2(2,2)*Sqr(mAInput) -
      1.9207999999999998*msu2(2,2)*Sqr(mAInput) + 1.8432*Sqr(msd2(2,2)) +
      0.9603999999999999*Sqr(msu2(2,2)) - TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),
      0.96*msd2(2,2)))*TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),0.96*msd2(2,2)))/((
      0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(msd2(2,2))) - (1.9223375624759709*(
      -2.9988*msq2(2,2)*msu2(2,2) + 0.9603999999999999*Quad(mAInput) - 2.9988*msq2
      (2,2)*Sqr(mAInput) - 1.9207999999999998*msu2(2,2)*Sqr(mAInput) + 2.0808*Sqr(
      msq2(2,2)) + 0.9603999999999999*Sqr(msu2(2,2)) - TDelta(0.98*Sqr(mAInput),
      0.98*msu2(2,2),1.02*msq2(2,2)))*TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*
      msq2(2,2)))/((0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(msq2(2,2)))) + 3*Cube(
      AbInput - MuInput*TanBeta)*(Log(0.96*msd2(2,2))*((4*Log(Sqr(SCALE))*(0.96*
      msd2(2,2) + 1.02*msq2(2,2)))/Cube(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (4*(
      2.88*msd2(2,2) + 1.02*msq2(2,2)))/Cube(0.96*msd2(2,2) - 1.02*msq2(2,2)) - (2
      *Log(0.98*msu2(2,2))*(0.96*msd2(2,2) + 1.02*msq2(2,2) + 1.96*msu2(2,2) -
      1.96*Sqr(mAInput)))/Cube(0.96*msd2(2,2) - 1.02*msq2(2,2))) + Log(1.02*msq2(2
      ,2))*((-4*Log(Sqr(SCALE))*(0.96*msd2(2,2) + 1.02*msq2(2,2)))/Cube(0.96*msd2(
      2,2) - 1.02*msq2(2,2)) - (4*(0.96*msd2(2,2) + 3.06*msq2(2,2)))/Cube(0.96*
      msd2(2,2) - 1.02*msq2(2,2)) + (2*Log(0.98*msu2(2,2))*(0.96*msd2(2,2) + 1.02*
      msq2(2,2) + 1.96*msu2(2,2) - 1.96*Sqr(mAInput)))/Cube(0.96*msd2(2,2) - 1.02*
      msq2(2,2))) + Log(0.98*Sqr(mAInput))*((-2*Log(0.96*msd2(2,2))*(0.96*msd2(2,2
      ) + 1.02*msq2(2,2) - 1.96*msu2(2,2) + 1.96*Sqr(mAInput)))/Cube(0.96*msd2(2,2
      ) - 1.02*msq2(2,2)) + (2*Log(1.02*msq2(2,2))*(0.96*msd2(2,2) + 1.02*msq2(2,2
      ) - 1.96*msu2(2,2) + 1.96*Sqr(mAInput)))/Cube(0.96*msd2(2,2) - 1.02*msq2(2,2
      ))) - 16/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) - (8*Log(Sqr(SCALE)))/Sqr(0.96
      *msd2(2,2) - 1.02*msq2(2,2)) + (2.170138888888889*((0.96*msd2(2,2) - 1.02*
      msq2(2,2))*(-2.8224*msd2(2,2)*msu2(2,2) + 0.9603999999999999*Quad(mAInput) -
      2.8224*msd2(2,2)*Sqr(mAInput) - 1.9207999999999998*msu2(2,2)*Sqr(mAInput) +
      1.8432*Sqr(msd2(2,2)) + 0.9603999999999999*Sqr(msu2(2,2))) + (-2.88*msd2(2,
      2) + 1.02*msq2(2,2))*TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),0.96*msd2(2,2))
      )*TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),0.96*msd2(2,2)))/(Cube(0.96*msd2(2,2
      ) - 1.02*msq2(2,2))*Sqr(msd2(2,2))) + (1.9223375624759709*(-((0.96*msd2(2,2)
      - 1.02*msq2(2,2))*(-2.9988*msq2(2,2)*msu2(2,2) + 0.9603999999999999*Quad(
      mAInput) - 2.9988*msq2(2,2)*Sqr(mAInput) - 1.9207999999999998*msu2(2,2)*Sqr(
      mAInput) + 2.0808*Sqr(msq2(2,2)) + 0.9603999999999999*Sqr(msu2(2,2)))) + (
      0.96*msd2(2,2) - 3.06*msq2(2,2))*TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),
      1.02*msq2(2,2)))*TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2)))/(
      Cube(-0.96*msd2(2,2) + 1.02*msq2(2,2))*Sqr(msq2(2,2))))) + Sqr(AtInput +
      MuInput*TanBeta)*(3*Quad(AbInput - MuInput*TanBeta)*((0.9803921568627451*Log
      (Sqr(SCALE))*(0.96*msd2(2,2) + 5.1*msq2(2,2)))/(Cube(-0.96*msd2(2,2) + 1.02*
      msq2(2,2))*msq2(2,2)) + (0.9803921568627451*(0.96*msd2(2,2) + 11.22*msq2(2,2
      )))/(Cube(-0.96*msd2(2,2) + 1.02*msq2(2,2))*msq2(2,2)) + Log(0.96*msd2(2,2))
      *((2*Log(Sqr(SCALE))*(1.92*msd2(2,2) + 1.02*msq2(2,2)))/Quad(0.96*msd2(2,2)
      - 1.02*msq2(2,2)) + (2*(4.8*msd2(2,2) + 1.02*msq2(2,2)))/Quad(0.96*msd2(2,2)
      - 1.02*msq2(2,2)) - (Log(0.98*msu2(2,2))*(1.92*msd2(2,2) + 1.02*msq2(2,2) +
      2.94*msu2(2,2) - 2.94*Sqr(mAInput)))/Quad(0.96*msd2(2,2) - 1.02*msq2(2,2)))
      + Log(1.02*msq2(2,2))*((-2*Log(Sqr(SCALE))*(1.92*msd2(2,2) + 1.02*msq2(2,2)
      ))/Quad(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (Log(0.98*msu2(2,2))*(1.92*msd2(2
      ,2) + 1.02*msq2(2,2) + 2.94*msu2(2,2) - 2.94*Sqr(mAInput)))/Quad(0.96*msd2(2
      ,2) - 1.02*msq2(2,2)) - (0.9803921568627451*(1.9584*msd2(2,2)*msq2(2,2) +
      0.9216*Sqr(msd2(2,2)) + 9.3636*Sqr(msq2(2,2)) - (Sqr(0.96*msd2(2,2) - 1.02*
      msq2(2,2))*(-2.9988*msq2(2,2)*msu2(2,2) + 0.9603999999999999*Quad(mAInput) -
      2.9988*msq2(2,2)*Sqr(mAInput) - 1.9207999999999998*msu2(2,2)*Sqr(mAInput) +
      2.0808*Sqr(msq2(2,2)) + 0.9603999999999999*Sqr(msu2(2,2))))/TDelta(0.98*Sqr
      (mAInput),0.98*msu2(2,2),1.02*msq2(2,2))))/(msq2(2,2)*Quad(0.96*msd2(2,2) -
      1.02*msq2(2,2)))) + (0.4805843906189927*Log(0.98*msu2(2,2))*((-1.02*msq2(2,2
      ) - 0.98*msu2(2,2) + 0.98*Sqr(mAInput))*(-2.9988*msq2(2,2)*msu2(2,2) +
      0.9603999999999999*Quad(mAInput) - 2.9988*msq2(2,2)*Sqr(mAInput) -
      1.9207999999999998*msu2(2,2)*Sqr(mAInput) + 2.0808*Sqr(msq2(2,2)) +
      0.9603999999999999*Sqr(msu2(2,2))) + (2.04*msq2(2,2) + 0.98*msu2(2,2) - 0.98
      *Sqr(mAInput))*TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2))))/(
      Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(msq2(2,2))*TDelta(0.98*Sqr(mAInput)
      ,0.98*msu2(2,2),1.02*msq2(2,2))) + Log(0.98*Sqr(mAInput))*(-((Log(0.96*msd2(
      2,2))*(1.92*msd2(2,2) + 1.02*msq2(2,2) - 2.94*msu2(2,2) + 2.94*Sqr(mAInput))
      )/Quad(0.96*msd2(2,2) - 1.02*msq2(2,2))) + (Log(1.02*msq2(2,2))*(1.92*msd2(2
      ,2) + 1.02*msq2(2,2) - 2.94*msu2(2,2) + 2.94*Sqr(mAInput)))/Quad(0.96*msd2(2
      ,2) - 1.02*msq2(2,2)) + (0.4805843906189927*(-((1.02*msq2(2,2) - 0.98*msu2(2
      ,2) + 0.98*Sqr(mAInput))*(-2.9988*msq2(2,2)*msu2(2,2) + 0.9603999999999999*
      Quad(mAInput) - 2.9988*msq2(2,2)*Sqr(mAInput) - 1.9207999999999998*msu2(2,2)
      *Sqr(mAInput) + 2.0808*Sqr(msq2(2,2)) + 0.9603999999999999*Sqr(msu2(2,2))))
      + (2.04*msq2(2,2) - 0.98*msu2(2,2) + 0.98*Sqr(mAInput))*TDelta(0.98*Sqr(
      mAInput),0.98*msu2(2,2),1.02*msq2(2,2))))/(Sqr(0.96*msd2(2,2) - 1.02*msq2(2,
      2))*Sqr(msq2(2,2))*TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2))))
      + (1.0850694444444444*((0.96*msd2(2,2) - 1.02*msq2(2,2))*(-2.8224*msd2(2,2)
      *msu2(2,2) + 0.9603999999999999*Quad(mAInput) - 2.8224*msd2(2,2)*Sqr(mAInput
      ) - 1.9207999999999998*msu2(2,2)*Sqr(mAInput) + 1.8432*Sqr(msd2(2,2)) +
      0.9603999999999999*Sqr(msu2(2,2))) + (-3.84*msd2(2,2) + 1.02*msq2(2,2))*
      TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),0.96*msd2(2,2)))*TPhi(0.98*Sqr(
      mAInput),0.98*msu2(2,2),0.96*msd2(2,2)))/(Quad(0.96*msd2(2,2) - 1.02*msq2(2,
      2))*Sqr(msd2(2,2))) + (0.4711611672735223*(-((0.96*msd2(2,2) - 1.02*msq2(2,2
      ))*(-5.9976*(0.96*msd2(2,2) - 3.06*msq2(2,2))*msq2(2,2)*msu2(2,2) +
      0.9603999999999999*(2.88*msd2(2,2) - 7.140000000000001*msq2(2,2))*Quad(
      mAInput) + 1.96*(-2.88*msd2(2,2)*(1.02*msq2(2,2) + 0.98*msu2(2,2)) + 1.02*
      msq2(2,2)*(9.18*msq2(2,2) + 6.859999999999999*msu2(2,2)))*Sqr(mAInput) +
      2.0808*(0.96*msd2(2,2) - 5.1*msq2(2,2))*Sqr(msq2(2,2)) + 0.9603999999999999*
      (2.88*msd2(2,2) - 7.140000000000001*msq2(2,2))*Sqr(msu2(2,2)))) + ((0.98*(
      -1.02*msq2(2,2) + 0.98*msu2(2,2))*msu2(2,2) + 0.9603999999999999*Quad(
      mAInput) - 0.98*(1.02*msq2(2,2) + 1.96*msu2(2,2))*Sqr(mAInput))*Sqr(0.96*
      msd2(2,2) - 1.02*msq2(2,2))*(-2.9988*msq2(2,2)*msu2(2,2) +
      0.9603999999999999*Quad(mAInput) - 2.9988*msq2(2,2)*Sqr(mAInput) -
      1.9207999999999998*msu2(2,2)*Sqr(mAInput) + 2.0808*Sqr(msq2(2,2)) +
      0.9603999999999999*Sqr(msu2(2,2))))/TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),
      1.02*msq2(2,2)) + 2*(-3.9168*msd2(2,2)*msq2(2,2) + 0.9216*Sqr(msd2(2,2)) +
      6.2424*Sqr(msq2(2,2)))*TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2
      )))*TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2)))/(Cube(msq2(2,2))*
      Quad(0.96*msd2(2,2) - 1.02*msq2(2,2)))) + 3*(-0.9803921568627451/msq2(2,2) -
      (0.9803921568627451*Log(Sqr(SCALE)))/msq2(2,2) + (0.9803921568627451*Log(
      1.02*msq2(2,2))*(-2.9988*msq2(2,2)*msu2(2,2) + 0.9603999999999999*Quad(
      mAInput) - 2.9988*msq2(2,2)*Sqr(mAInput) - 1.9207999999999998*msu2(2,2)*Sqr(
      mAInput) + 2.0808*Sqr(msq2(2,2)) + 0.9603999999999999*Sqr(msu2(2,2)) -
      TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2))))/(msq2(2,2)*TDelta(
      0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2))) + (0.4805843906189927*Log(
      0.98*msu2(2,2))*((-1.02*msq2(2,2) - 0.98*msu2(2,2) + 0.98*Sqr(mAInput))*(
      -2.9988*msq2(2,2)*msu2(2,2) + 0.9603999999999999*Quad(mAInput) - 2.9988*msq2
      (2,2)*Sqr(mAInput) - 1.9207999999999998*msu2(2,2)*Sqr(mAInput) + 2.0808*Sqr(
      msq2(2,2)) + 0.9603999999999999*Sqr(msu2(2,2))) + (2.04*msq2(2,2) + 0.98*
      msu2(2,2) - 0.98*Sqr(mAInput))*TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*
      msq2(2,2))))/(Sqr(msq2(2,2))*TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*
      msq2(2,2))) + (0.4805843906189927*Log(0.98*Sqr(mAInput))*(-((1.02*msq2(2,2)
      - 0.98*msu2(2,2) + 0.98*Sqr(mAInput))*(-2.9988*msq2(2,2)*msu2(2,2) +
      0.9603999999999999*Quad(mAInput) - 2.9988*msq2(2,2)*Sqr(mAInput) -
      1.9207999999999998*msu2(2,2)*Sqr(mAInput) + 2.0808*Sqr(msq2(2,2)) +
      0.9603999999999999*Sqr(msu2(2,2)))) + (2.04*msq2(2,2) - 0.98*msu2(2,2) +
      0.98*Sqr(mAInput))*TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2))))
      /(Sqr(msq2(2,2))*TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2))) +
      (0.4711611672735223*((0.98*(-1.02*msq2(2,2) + 0.98*msu2(2,2))*msu2(2,2) +
      0.9603999999999999*Quad(mAInput) - 0.98*(1.02*msq2(2,2) + 1.96*msu2(2,2))*
      Sqr(mAInput))*(-2.9988*msq2(2,2)*msu2(2,2) + 0.9603999999999999*Quad(mAInput
      ) - 2.9988*msq2(2,2)*Sqr(mAInput) - 1.9207999999999998*msu2(2,2)*Sqr(mAInput
      ) + 2.0808*Sqr(msq2(2,2)) + 0.9603999999999999*Sqr(msu2(2,2))) + TDelta(0.98
      *Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2))*(5.9976*msq2(2,2)*msu2(2,2) -
      2.8811999999999998*Quad(mAInput) + 5.88*(1.02*msq2(2,2) + 0.98*msu2(2,2))*
      Sqr(mAInput) - 2.0808*Sqr(msq2(2,2)) - 2.8811999999999998*Sqr(msu2(2,2)) + 2
      *TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2))))*TPhi(0.98*Sqr(
      mAInput),0.98*msu2(2,2),1.02*msq2(2,2)))/(Cube(msq2(2,2))*TDelta(0.98*Sqr(
      mAInput),0.98*msu2(2,2),1.02*msq2(2,2)))) + 3*Sqr(AbInput - MuInput*TanBeta)
      *(1.9607843137254901/((0.96*msd2(2,2) - 1.02*msq2(2,2))*msq2(2,2)) + Log(
      0.96*msd2(2,2))*(-2/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) + Log(0.98*msu2(2,2
      ))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) - (2*Log(Sqr(SCALE)))/Sqr(0.96*msd2(
      2,2) - 1.02*msq2(2,2))) + (2*Log(Sqr(SCALE)))/(0.9792*msd2(2,2)*msq2(2,2) -
      1.0404*Sqr(msq2(2,2))) + (0.9611687812379854*Log(0.98*msu2(2,2))*(-((-1.02*
      msq2(2,2) - 0.98*msu2(2,2) + 0.98*Sqr(mAInput))*(-2.9988*msq2(2,2)*msu2(2,2)
      + 0.9603999999999999*Quad(mAInput) - 2.9988*msq2(2,2)*Sqr(mAInput) -
      1.9207999999999998*msu2(2,2)*Sqr(mAInput) + 2.0808*Sqr(msq2(2,2)) +
      0.9603999999999999*Sqr(msu2(2,2)))) + (-2.04*msq2(2,2) - 0.98*msu2(2,2) +
      0.98*Sqr(mAInput))*TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2))))
      /((0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(msq2(2,2))*TDelta(0.98*Sqr(mAInput),
      0.98*msu2(2,2),1.02*msq2(2,2))) + Log(1.02*msq2(2,2))*(-(Log(0.98*msu2(2,2))
      /Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))) + (2*Log(Sqr(SCALE)))/Sqr(0.96*msd2(2
      ,2) - 1.02*msq2(2,2)) + (1.9607843137254901*(-((0.96*msd2(2,2) - 1.02*msq2(2
      ,2))*(-2.9988*msq2(2,2)*msu2(2,2) + 0.9603999999999999*Quad(mAInput) -
      2.9988*msq2(2,2)*Sqr(mAInput) - 1.9207999999999998*msu2(2,2)*Sqr(mAInput) +
      2.0808*Sqr(msq2(2,2)) + 0.9603999999999999*Sqr(msu2(2,2)))) + 0.96*msd2(2,2)
      *TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2))))/(msq2(2,2)*Sqr(
      0.96*msd2(2,2) - 1.02*msq2(2,2))*TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),
      1.02*msq2(2,2)))) + Log(0.98*Sqr(mAInput))*(Log(0.96*msd2(2,2))/Sqr(0.96*
      msd2(2,2) - 1.02*msq2(2,2)) - Log(1.02*msq2(2,2))/Sqr(0.96*msd2(2,2) - 1.02*
      msq2(2,2)) + (0.9611687812379854*((1.02*msq2(2,2) - 0.98*msu2(2,2) + 0.98*
      Sqr(mAInput))*(-2.9988*msq2(2,2)*msu2(2,2) + 0.9603999999999999*Quad(mAInput
      ) - 2.9988*msq2(2,2)*Sqr(mAInput) - 1.9207999999999998*msu2(2,2)*Sqr(mAInput
      ) + 2.0808*Sqr(msq2(2,2)) + 0.9603999999999999*Sqr(msu2(2,2))) + (-2.04*msq2
      (2,2) + 0.98*msu2(2,2) - 0.98*Sqr(mAInput))*TDelta(0.98*Sqr(mAInput),0.98*
      msu2(2,2),1.02*msq2(2,2))))/((0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(msq2(2,2)
      )*TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2)))) + (
      1.0850694444444444*(-2.8224*msd2(2,2)*msu2(2,2) + 0.9603999999999999*Quad(
      mAInput) - 2.8224*msd2(2,2)*Sqr(mAInput) - 1.9207999999999998*msu2(2,2)*Sqr(
      mAInput) + 1.8432*Sqr(msd2(2,2)) + 0.9603999999999999*Sqr(msu2(2,2)) -
      TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),0.96*msd2(2,2)))*TPhi(0.98*Sqr(
      mAInput),0.98*msu2(2,2),0.96*msd2(2,2)))/(Sqr(msd2(2,2))*Sqr(0.96*msd2(2,2)
      - 1.02*msq2(2,2))) + (0.9423223345470446*((0.96*msd2(2,2) - 1.02*msq2(2,2))*
      (0.98*(1.02*msq2(2,2) - 0.98*msu2(2,2))*msu2(2,2) - 0.9603999999999999*Quad(
      mAInput) + 0.98*(1.02*msq2(2,2) + 1.96*msu2(2,2))*Sqr(mAInput))*(-2.9988*
      msq2(2,2)*msu2(2,2) + 0.9603999999999999*Quad(mAInput) - 2.9988*msq2(2,2)*
      Sqr(mAInput) - 1.9207999999999998*msu2(2,2)*Sqr(mAInput) + 2.0808*Sqr(msq2(2
      ,2)) + 0.9603999999999999*Sqr(msu2(2,2))) + TDelta(0.98*Sqr(mAInput),0.98*
      msu2(2,2),1.02*msq2(2,2))*(2.9988*msq2(2,2)*(-1.92*msd2(2,2) + 3.06*msq2(2,2
      ))*msu2(2,2) + 0.9603999999999999*(2.88*msd2(2,2) - 4.08*msq2(2,2))*Quad(
      mAInput) + 0.98*(-5.76*msd2(2,2)*(1.02*msq2(2,2) + 0.98*msu2(2,2)) + 1.02*
      msq2(2,2)*(9.18*msq2(2,2) + 7.84*msu2(2,2)))*Sqr(mAInput) + 2.0808*(0.96*
      msd2(2,2) - 2.04*msq2(2,2))*Sqr(msq2(2,2)) + 0.9603999999999999*(2.88*msd2(2
      ,2) - 4.08*msq2(2,2))*Sqr(msu2(2,2)) + (-1.92*msd2(2,2) + 3.06*msq2(2,2))*
      TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2))))*TPhi(0.98*Sqr(
      mAInput),0.98*msu2(2,2),1.02*msq2(2,2)))/(Cube(msq2(2,2))*Sqr(0.96*msd2(2,2)
      - 1.02*msq2(2,2))*TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2))))
      ))/(1 + Sqr(TanBeta))))/Sqr(TanBeta)))/Quad(1 + (0.0625*(1 + Sqr(TanBeta))*(
      0.25*Log(Sqr(MuInput)/Sqr(SCALE)) + (0.125*(-1 + 2*Log(Sqr(mAInput)/Sqr(
      SCALE))))/(1 + Sqr(TanBeta)) + ((-1 + Log(Sqr(mAInput)/Sqr(SCALE)))*Sqr(
      TanBeta))/(1 + Sqr(TanBeta)))*Sqr(Yu(2,2)))/(Sqr(3.141592653589793)*Sqr(
      TanBeta)) + 0.5*((-0.03125*Sqr(AbInput - MuInput*TanBeta)*Sqr(Yd(2,2))*TCF(5
      )(Sqrt(Abs(msq2(2,2)/msd2(2,2)))))/(Sqrt(Abs(msd2(2,2)*msq2(2,2)))*Sqr(
      3.141592653589793)) - (0.03125*Sqr(AtInput - MuInput/TanBeta)*Sqr(Yu(2,2))*
      TCF(5)(Sqrt(Abs(msq2(2,2)/msu2(2,2)))))/(Sqrt(Abs(msq2(2,2)*msu2(2,2)))*Sqr(
      3.141592653589793))) + (0.0625*(1 + Sqr(TanBeta))*Sqr(Yd(2,2))*(0.75*Log(Sqr
      (MuInput)/Sqr(SCALE)) + (0.375*(-1 + 2*Log(Sqr(mAInput)/Sqr(SCALE)))*Sqr(
      TanBeta))/(1 + Sqr(TanBeta)) + 0.5*TCF(6)(Sqrt(msd2(2,2))/MuInput) + TCF(6)(
      Sqrt(msq2(2,2))/MuInput)))/Sqr(3.141592653589793) + (0.08333333333333333*Sqr
      (g3)*(1 + Log(Sqr(M3Input)/Sqr(SCALE)) + TCF(6)(Sqrt(msd2(2,2))/M3Input) +
      TCF(6)(Sqrt(msq2(2,2))/M3Input) - ((AbInput - MuInput*TanBeta)*TCF(9)(Sqrt(
      msq2(2,2))/M3Input,Sqrt(msd2(2,2))/M3Input))/M3Input))/Sqr(3.141592653589793
      ) + (0.0625*(1 + Sqr(TanBeta))*Sqr(Yu(2,2))*(0.5*TCF(6)(Sqrt(msu2(2,2))
      /MuInput) + (0.5*(AtInput - MuInput/TanBeta)*TanBeta*TCF(9)(Sqrt(msq2(2,2))
      /MuInput,Sqrt(msu2(2,2))/MuInput))/MuInput))/(Sqr(3.141592653589793)*Sqr(
      TanBeta))) + (Quad(Yu(2,2))*Sqr(Yd(2,2))*(3*Sqr(AbInput - MuInput*TanBeta)*(
      (0.9803921568627451*(0.96*msd2(2,2) - 5.1*msq2(2,2)))/(msq2(2,2)*(-0.96*msd2
      (2,2) + 1.02*msq2(2,2))) + (0.9803921568627451*Log(Sqr(SCALE))*(0.96*msd2(2,
      2) - 3.06*msq2(2,2)))/(msq2(2,2)*(-0.96*msd2(2,2) + 1.02*msq2(2,2))) + (6*
      PolyLog(2,1 - (0.9411764705882352*msd2(2,2))/msq2(2,2)))/(-0.96*msd2(2,2) +
      1.02*msq2(2,2)) + Log(0.96*msd2(2,2))*((1.92*Log(1.02*msq2(2,2))*msd2(2,2))
      /Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) - (1.92*Log(Sqr(SCALE))*msd2(2,2))/Sqr
      (0.96*msd2(2,2) - 1.02*msq2(2,2)) + (0.9411764705882352*msd2(2,2)*(0.96*msd2
      (2,2) - 5.1*msq2(2,2)))/(msq2(2,2)*Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)))) +
      Log(1.02*msq2(2,2))*((1.92*Log(Sqr(SCALE))*msd2(2,2))/Sqr(0.96*msd2(2,2) -
      1.02*msq2(2,2)) + (0.96*msd2(2,2) + 3.06*msq2(2,2))/Sqr(0.96*msd2(2,2) -
      1.02*msq2(2,2))) - (1.92*msd2(2,2)*Sqr(Log(1.02*msq2(2,2))))/Sqr(0.96*msd2(2
      ,2) - 1.02*msq2(2,2))) + (3*(AbInput - MuInput*TanBeta)*Sqr(AtInput -
      MuInput/TanBeta)*(Log(0.96*msd2(2,2))*((7.794348721990825*MuInput*Log(0.98*
      msu2(2,2))*msd2(2,2)*Sqrt(Sqr(MuInput)))/(Abs(MuInput)*(0.96*msd2(2,2) -
      1.02*msq2(2,2))*(1.02*msq2(2,2) - 0.98*msu2(2,2))*(0.96*msd2(2,2) - 1.03*Sqr
      (MuInput))) + (7.794348721990825*MuInput*Log(1.02*msq2(2,2))*msd2(2,2)*Sqrt(
      Sqr(MuInput)))/(Abs(MuInput)*(0.96*msd2(2,2) - 1.02*msq2(2,2))*(-1.02*msq2(2
      ,2) + 0.98*msu2(2,2))*(0.96*msd2(2,2) - 1.03*Sqr(MuInput)))) + (
      8.281495517115252*MuInput*Log(1.02*msq2(2,2))*Log(0.98*msu2(2,2))*msq2(2,2)*
      Sqrt(Sqr(MuInput)))/(Abs(MuInput)*(-0.96*msd2(2,2) + 1.02*msq2(2,2))*(-1.02*
      msq2(2,2) + 0.98*msu2(2,2))*(-1.02*msq2(2,2) + 1.03*Sqr(MuInput))) + Log(
      1.03*Sqr(MuInput))*((8.36268664963599*MuInput*Log(1.02*msq2(2,2))*Power3(
      Sqrt(Sqr(MuInput))))/(Abs(MuInput)*(1.02*msq2(2,2) - 0.98*msu2(2,2))*(0.96*
      msd2(2,2) - 1.03*Sqr(MuInput))*(-1.02*msq2(2,2) + 1.03*Sqr(MuInput))) + (
      8.36268664963599*MuInput*Log(0.98*msu2(2,2))*Power3(Sqrt(Sqr(MuInput))))/(
      Abs(MuInput)*(1.02*msq2(2,2) - 0.98*msu2(2,2))*(-0.96*msd2(2,2) + 1.03*Sqr(
      MuInput))*(-1.02*msq2(2,2) + 1.03*Sqr(MuInput)))) + (8.281495517115252*
      MuInput*msq2(2,2)*Sqrt(Sqr(MuInput))*Sqr(Log(1.02*msq2(2,2))))/(Abs(MuInput)
      *(-0.96*msd2(2,2) + 1.02*msq2(2,2))*(1.02*msq2(2,2) - 0.98*msu2(2,2))*(-1.02
      *msq2(2,2) + 1.03*Sqr(MuInput)))) + 3*(AbInput - MuInput*TanBeta)*((
      8.119113252073776*MuInput*PolyLog(2,1 - (1.0729166666666667*Sqr(MuInput))
      /msd2(2,2))*Sqrt(Sqr(MuInput))*(0.96*msd2(2,2) + 1.03*Sqr(MuInput)))/(Abs(
      MuInput)*(0.96*msd2(2,2) - 1.02*msq2(2,2))*(0.96*msd2(2,2) - 1.03*Sqr(
      MuInput))) + (4.140747758557626*MuInput*Log(1.02*msq2(2,2))*Log(0.98*msu2(2,
      2))*msq2(2,2)*Sqrt(Sqr(MuInput)))/(Abs(MuInput)*(-0.96*msd2(2,2) + 1.02*msq2
      (2,2))*(-1.02*msq2(2,2) + 1.03*Sqr(MuInput))) - (8.119113252073776*MuInput*
      PolyLog(2,1 - (1.0098039215686274*Sqr(MuInput))/msq2(2,2))*Sqrt(Sqr(MuInput)
      )*(1.02*msq2(2,2) + 1.03*Sqr(MuInput)))/(Abs(MuInput)*(-0.96*msd2(2,2) +
      1.02*msq2(2,2))*(-1.02*msq2(2,2) + 1.03*Sqr(MuInput))) + Log(0.96*msd2(2,2))
      *((3.8971743609954124*MuInput*Log(1.02*msq2(2,2))*msd2(2,2)*Sqrt(Sqr(MuInput
      )))/(Abs(MuInput)*(-0.96*msd2(2,2) + 1.02*msq2(2,2))*(0.96*msd2(2,2) - 1.03*
      Sqr(MuInput))) + (3.8971743609954124*MuInput*Log(0.98*msu2(2,2))*msd2(2,2)*
      Sqrt(Sqr(MuInput)))/(Abs(MuInput)*(-0.96*msd2(2,2) + 1.02*msq2(2,2))*(0.96*
      msd2(2,2) - 1.03*Sqr(MuInput))) + (8.36268664963599*MuInput*Log(1.03*Sqr(
      MuInput))*Power3(Sqrt(Sqr(MuInput))))/(Abs(MuInput)*(0.96*msd2(2,2) - 1.02*
      msq2(2,2))*(-0.96*msd2(2,2) + 1.03*Sqr(MuInput)))) + Log(1.03*Sqr(MuInput))*
      ((4.181343324817995*MuInput*Log(0.98*msu2(2,2))*Power3(Sqrt(Sqr(MuInput))))/
      (Abs(MuInput)*(0.96*msd2(2,2) - 1.03*Sqr(MuInput))*(-1.02*msq2(2,2) + 1.03*
      Sqr(MuInput))) - (4.181343324817995*MuInput*Log(1.02*msq2(2,2))*(0.96*msd2(2
      ,2) + 1.02*msq2(2,2) - 2.06*Sqr(MuInput))*Power3(Sqrt(Sqr(MuInput))))/(Abs(
      MuInput)*(0.96*msd2(2,2) - 1.02*msq2(2,2))*(0.96*msd2(2,2) - 1.03*Sqr(
      MuInput))*(-1.02*msq2(2,2) + 1.03*Sqr(MuInput)))) + (4.059556626036888*
      MuInput*Sqrt(Sqr(MuInput))*(0.96*msd2(2,2) + 1.03*Sqr(MuInput))*Sqr(Log(0.96
      *msd2(2,2))))/(Abs(MuInput)*(0.96*msd2(2,2) - 1.02*msq2(2,2))*(0.96*msd2(2,2
      ) - 1.03*Sqr(MuInput))) + (4.181343324817995*MuInput*Power3(Sqrt(Sqr(MuInput
      )))*Sqr(Log(1.02*msq2(2,2))))/(Abs(MuInput)*(0.96*msd2(2,2) - 1.02*msq2(2,2)
      )*(-1.02*msq2(2,2) + 1.03*Sqr(MuInput)))) + 3*(AtInput - MuInput/TanBeta)*(
      Log(1.02*msq2(2,2))*((8.119113252073776*MuInput*Sqrt(Sqr(MuInput)))/(Abs(
      MuInput)*(1.02*msq2(2,2) - 0.98*msu2(2,2))) + (8.119113252073776*MuInput*Log
      (Sqr(SCALE))*Sqrt(Sqr(MuInput)))/(Abs(MuInput)*(1.02*msq2(2,2) - 0.98*msu2(2
      ,2)))) + (8.119113252073776*MuInput*Log(0.98*msu2(2,2))*Sqrt(Sqr(MuInput)))/
      (Abs(MuInput)*(-1.02*msq2(2,2) + 0.98*msu2(2,2))) + (8.119113252073776*
      MuInput*Log(0.98*msu2(2,2))*Log(Sqr(SCALE))*Sqrt(Sqr(MuInput)))/(Abs(MuInput
      )*(-1.02*msq2(2,2) + 0.98*msu2(2,2))) + (8.119113252073776*MuInput*PolyLog(2
      ,1 - (1.0098039215686274*Sqr(MuInput))/msq2(2,2))*Sqrt(Sqr(MuInput)))/(Abs(
      MuInput)*(-1.02*msq2(2,2) + 0.98*msu2(2,2))) + (8.119113252073776*MuInput*
      PolyLog(2,1 - (1.0510204081632653*Sqr(MuInput))/msu2(2,2))*Sqrt(Sqr(MuInput)
      ))/(Abs(MuInput)*(1.02*msq2(2,2) - 0.98*msu2(2,2))) + (4.059556626036888*
      MuInput*Sqrt(Sqr(MuInput))*Sqr(Log(1.02*msq2(2,2))))/(Abs(MuInput)*(-1.02*
      msq2(2,2) + 0.98*msu2(2,2))) + (4.059556626036888*MuInput*Sqrt(Sqr(MuInput))
      *Sqr(Log(0.98*msu2(2,2))))/(Abs(MuInput)*(1.02*msq2(2,2) - 0.98*msu2(2,2))))
      + 3*(AbInput - MuInput*TanBeta)*Quad(AtInput - MuInput/TanBeta)*((
      -4.140747758557626*MuInput*msq2(2,2)*(1.02*msq2(2,2) + 0.98*msu2(2,2))*Sqrt(
      Sqr(MuInput))*Sqr(Log(1.02*msq2(2,2))))/(Abs(MuInput)*Cube(1.02*msq2(2,2) -
      0.98*msu2(2,2))*(-0.96*msd2(2,2) + 1.02*msq2(2,2))*(-1.02*msq2(2,2) + 1.03*
      Sqr(MuInput))) + Log(0.96*msd2(2,2))*((3.8971743609954124*MuInput*Log(1.02*
      msq2(2,2))*msd2(2,2)*(1.02*msq2(2,2) + 0.98*msu2(2,2))*Sqrt(Sqr(MuInput)))/(
      Abs(MuInput)*Cube(1.02*msq2(2,2) - 0.98*msu2(2,2))*(0.96*msd2(2,2) - 1.02*
      msq2(2,2))*(0.96*msd2(2,2) - 1.03*Sqr(MuInput))) - (3.8971743609954124*
      MuInput*Log(0.98*msu2(2,2))*msd2(2,2)*(1.02*msq2(2,2) + 0.98*msu2(2,2))*Sqrt
      (Sqr(MuInput)))/(Abs(MuInput)*Cube(1.02*msq2(2,2) - 0.98*msu2(2,2))*(0.96*
      msd2(2,2) - 1.02*msq2(2,2))*(0.96*msd2(2,2) - 1.03*Sqr(MuInput))) - (
      7.794348721990825*MuInput*msd2(2,2)*Sqrt(Sqr(MuInput)))/(Abs(MuInput)*(0.96*
      msd2(2,2) - 1.02*msq2(2,2))*(0.96*msd2(2,2) - 1.03*Sqr(MuInput))*Sqr(1.02*
      msq2(2,2) - 0.98*msu2(2,2)))) + Log(1.02*msq2(2,2))*((4.140747758557626*
      MuInput*Log(0.98*msu2(2,2))*msq2(2,2)*(1.02*msq2(2,2) + 0.98*msu2(2,2))*Sqrt
      (Sqr(MuInput)))/(Abs(MuInput)*Cube(1.02*msq2(2,2) - 0.98*msu2(2,2))*(-0.96*
      msd2(2,2) + 1.02*msq2(2,2))*(-1.02*msq2(2,2) + 1.03*Sqr(MuInput))) + (
      8.281495517115252*MuInput*msq2(2,2)*Sqrt(Sqr(MuInput)))/(Abs(MuInput)*(-0.96
      *msd2(2,2) + 1.02*msq2(2,2))*(-1.02*msq2(2,2) + 1.03*Sqr(MuInput))*Sqr(1.02*
      msq2(2,2) - 0.98*msu2(2,2)))) + Log(1.03*Sqr(MuInput))*((-4.181343324817995*
      MuInput*Log(1.02*msq2(2,2))*(1.02*msq2(2,2) + 0.98*msu2(2,2))*Power3(Sqrt(
      Sqr(MuInput))))/(Abs(MuInput)*Cube(1.02*msq2(2,2) - 0.98*msu2(2,2))*(0.96*
      msd2(2,2) - 1.03*Sqr(MuInput))*(-1.02*msq2(2,2) + 1.03*Sqr(MuInput))) + (
      4.181343324817995*MuInput*Log(0.98*msu2(2,2))*(1.02*msq2(2,2) + 0.98*msu2(2,
      2))*Power3(Sqrt(Sqr(MuInput))))/(Abs(MuInput)*Cube(1.02*msq2(2,2) - 0.98*
      msu2(2,2))*(0.96*msd2(2,2) - 1.03*Sqr(MuInput))*(-1.02*msq2(2,2) + 1.03*Sqr(
      MuInput))) + (8.36268664963599*MuInput*Power3(Sqrt(Sqr(MuInput))))/(Abs(
      MuInput)*(0.96*msd2(2,2) - 1.03*Sqr(MuInput))*(-1.02*msq2(2,2) + 1.03*Sqr(
      MuInput))*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))))) + 3*Cube(AtInput -
      MuInput/TanBeta)*(Log(1.02*msq2(2,2))*((-8.119113252073776*MuInput*Log(Sqr(
      SCALE))*(1.02*msq2(2,2) + 0.98*msu2(2,2))*Sqrt(Sqr(MuInput)))/(Abs(MuInput)*
      Cube(1.02*msq2(2,2) - 0.98*msu2(2,2))) - (8.119113252073776*MuInput*(3.06*
      msq2(2,2) + 0.98*msu2(2,2))*Sqrt(Sqr(MuInput)))/(Abs(MuInput)*Cube(1.02*msq2
      (2,2) - 0.98*msu2(2,2)))) + (8.119113252073776*MuInput*Log(0.98*msu2(2,2))*(
      1.02*msq2(2,2) + 2.94*msu2(2,2))*Sqrt(Sqr(MuInput)))/(Abs(MuInput)*Cube(1.02
      *msq2(2,2) - 0.98*msu2(2,2))) + (8.119113252073776*MuInput*PolyLog(2,1 - (
      1.0098039215686274*Sqr(MuInput))/msq2(2,2))*(1.02*msq2(2,2) + 0.98*msu2(2,2)
      - 2.06*Sqr(MuInput))*Sqrt(Sqr(MuInput)))/(Abs(MuInput)*Cube(1.02*msq2(2,2)
      - 0.98*msu2(2,2))) - (8.119113252073776*MuInput*PolyLog(2,1 - (
      1.0510204081632653*Sqr(MuInput))/msu2(2,2))*(1.02*msq2(2,2) + 0.98*msu2(2,2)
      - 2.06*Sqr(MuInput))*Sqrt(Sqr(MuInput)))/(Abs(MuInput)*Cube(1.02*msq2(2,2)
      - 0.98*msu2(2,2))) + Log(1.03*Sqr(MuInput))*((16.72537329927198*MuInput*Log(
      1.02*msq2(2,2))*Power3(Sqrt(Sqr(MuInput))))/(Abs(MuInput)*Cube(1.02*msq2(2,2
      ) - 0.98*msu2(2,2))) + (16.72537329927198*MuInput*Log(0.98*msu2(2,2))*Power3
      (Sqrt(Sqr(MuInput))))/(Abs(MuInput)*Cube(-1.02*msq2(2,2) + 0.98*msu2(2,2))))
      + (4.059556626036888*MuInput*(1.02*msq2(2,2) + 0.98*msu2(2,2) - 2.06*Sqr(
      MuInput))*Sqrt(Sqr(MuInput))*Sqr(Log(1.02*msq2(2,2))))/(Abs(MuInput)*Cube(
      1.02*msq2(2,2) - 0.98*msu2(2,2))) - (4.059556626036888*MuInput*(1.02*msq2(2,
      2) + 0.98*msu2(2,2) - 2.06*Sqr(MuInput))*Sqrt(Sqr(MuInput))*Sqr(Log(0.98*
      msu2(2,2))))/(Abs(MuInput)*Cube(1.02*msq2(2,2) - 0.98*msu2(2,2))) + Log(Sqr(
      SCALE))*((8.119113252073776*MuInput*Log(0.98*msu2(2,2))*(1.02*msq2(2,2) +
      0.98*msu2(2,2))*Sqrt(Sqr(MuInput)))/(Abs(MuInput)*Cube(1.02*msq2(2,2) - 0.98
      *msu2(2,2))) + (16.23822650414755*MuInput*Sqrt(Sqr(MuInput)))/(Abs(MuInput)*
      Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)))) + (32.4764530082951*MuInput*Sqrt(Sqr(
      MuInput)))/(Abs(MuInput)*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)))))/(Sqrt(1/(1
      + Sqr(TanBeta)))*Sqrt(Sqr(TanBeta)/(1 + Sqr(TanBeta)))) + Quad(AtInput -
      MuInput/TanBeta)*(3*((6*Log(0.98*msu2(2,2))*(1.02*msq2(2,2) + 2.94*msu2(2,2)
      ))/Cube(1.02*msq2(2,2) - 0.98*msu2(2,2)) + Log(1.02*msq2(2,2))*((2*Log(0.98*
      msu2(2,2))*(-5.1*msq2(2,2) + 0.98*msu2(2,2)))/Cube(1.02*msq2(2,2) - 0.98*
      msu2(2,2)) - (8*Log(Sqr(SCALE))*(1.02*msq2(2,2) + 0.98*msu2(2,2)))/Cube(1.02
      *msq2(2,2) - 0.98*msu2(2,2)) - (2*(7.140000000000001*msq2(2,2) + 4.9*msu2(2,
      2)))/Cube(1.02*msq2(2,2) - 0.98*msu2(2,2))) + ((7.140000000000001*msq2(2,2)
      + 0.98*msu2(2,2))*Sqr(Log(1.02*msq2(2,2))))/Cube(1.02*msq2(2,2) - 0.98*msu2(
      2,2)) + Log(0.98*Sqr(mAInput))*((4*Log(1.02*msq2(2,2))*(1.02*msq2(2,2) +
      0.98*msu2(2,2)))/Cube(1.02*msq2(2,2) - 0.98*msu2(2,2)) - (4*Log(0.98*msu2(2,
      2))*(1.02*msq2(2,2) + 0.98*msu2(2,2)))/Cube(1.02*msq2(2,2) - 0.98*msu2(2,2))
      - 8/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) + Log(Sqr(SCALE))*((8*Log(0.98*
      msu2(2,2))*(1.02*msq2(2,2) + 0.98*msu2(2,2)))/Cube(1.02*msq2(2,2) - 0.98*
      msu2(2,2)) + 16/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) + 24/Sqr(1.02*msq2(2,2
      ) - 0.98*msu2(2,2)) + (6*PolyLog(2,1 - (1.0408163265306123*msq2(2,2))/msu2(2
      ,2)))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)) + (3*Sqr(Log(0.98*msu2(2,2))))
      /Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) + 3*Sqr(AbInput - MuInput*TanBeta)*((
      0.9803921568627451*(11.22*msq2(2,2) + 0.98*msu2(2,2)))/(Cube(1.02*msq2(2,2)
      - 0.98*msu2(2,2))*msq2(2,2)) + Log(Sqr(SCALE))*((0.9803921568627451*(5.1*
      msq2(2,2) + 0.98*msu2(2,2)))/(Cube(1.02*msq2(2,2) - 0.98*msu2(2,2))*msq2(2,2
      )) + (2*Log(0.98*msu2(2,2))*(1.02*msq2(2,2) + 1.96*msu2(2,2)))/Quad(1.02*
      msq2(2,2) - 0.98*msu2(2,2))) + (2*Log(0.98*msu2(2,2))*(0.98*(
      -7.140000000000001*msq2(2,2) + 0.98*msu2(2,2))*msu2(2,2) + 0.96*msd2(2,2)*(
      1.02*msq2(2,2) + 4.9*msu2(2,2))))/((0.96*msd2(2,2) - 1.02*msq2(2,2))*Quad(
      1.02*msq2(2,2) - 0.98*msu2(2,2))) + (3*(0.96*msd2(2,2) + 1.02*msq2(2,2) -
      1.96*msu2(2,2))*Sqr(Log(0.98*msu2(2,2))))/Quad(1.02*msq2(2,2) - 0.98*msu2(2,
      2)) + (Sqr(Log(1.02*msq2(2,2)))*(-3*(0.96*msd2(2,2) + 1.02*msq2(2,2) - 1.96*
      msu2(2,2)) + (2*(1.02*msq2(2,2) - 0.98*msu2(2,2))*(0.96*msd2(2,2)*(-5.1*msq2
      (2,2) + 0.98*msu2(2,2)) + 4.1616*Sqr(msq2(2,2))))/Sqr(0.96*msd2(2,2) - 1.02*
      msq2(2,2))))/Quad(1.02*msq2(2,2) - 0.98*msu2(2,2)) - (6*PolyLog(2,1 - (
      0.9411764705882352*msd2(2,2))/msq2(2,2))*Sqr(0.96*msd2(2,2) - 0.98*msu2(2,2)
      ))/((0.96*msd2(2,2) - 1.02*msq2(2,2))*Quad(1.02*msq2(2,2) - 0.98*msu2(2,2)))
      + (6*PolyLog(2,1 - (0.9795918367346939*msd2(2,2))/msu2(2,2))*Sqr(0.96*msd2(
      2,2) - 0.98*msu2(2,2)))/((0.96*msd2(2,2) - 1.02*msq2(2,2))*Quad(1.02*msq2(2,
      2) - 0.98*msu2(2,2))) + Log(0.96*msd2(2,2))*((1.92*Log(1.02*msq2(2,2))*msd2(
      2,2)*(0.96*msd2(2,2) - 0.98*msu2(2,2))*(2.88*msd2(2,2) - 2.04*msq2(2,2) -
      0.98*msu2(2,2)))/(Quad(1.02*msq2(2,2) - 0.98*msu2(2,2))*Sqr(0.96*msd2(2,2) -
      1.02*msq2(2,2))) - (1.92*Log(0.98*msu2(2,2))*msd2(2,2)*(0.96*msd2(2,2) -
      0.98*msu2(2,2))*(2.88*msd2(2,2) - 2.04*msq2(2,2) - 0.98*msu2(2,2)))/(Quad(
      1.02*msq2(2,2) - 0.98*msu2(2,2))*Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))) + (
      0.9411764705882352*msd2(2,2))/((0.96*msd2(2,2) - 1.02*msq2(2,2))*msq2(2,2)*
      Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)))) - (6*PolyLog(2,1 - (
      1.0408163265306123*msq2(2,2))/msu2(2,2)))/((0.96*msd2(2,2) - 1.02*msq2(2,2))
      *Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) + Log(1.02*msq2(2,2))*((-2*Log(Sqr(
      SCALE))*(1.02*msq2(2,2) + 1.96*msu2(2,2)))/Quad(1.02*msq2(2,2) - 0.98*msu2(2
      ,2)) + (2*Log(0.98*msu2(2,2))*(4.896*msd2(2,2)*msq2(2,2) - 0.9408*msd2(2,2)*
      msu2(2,2) - 4.1616*Sqr(msq2(2,2))))/(Cube(1.02*msq2(2,2) - 0.98*msu2(2,2))*
      Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))) + (-3.84*msd2(2,2)*(2.04*msq2(2,2) +
      0.98*msu2(2,2)) + 9.996*msq2(2,2)*msu2(2,2) + 5.202*Sqr(msq2(2,2)) -
      2.8811999999999998*Sqr(msu2(2,2)))/((0.96*msd2(2,2) - 1.02*msq2(2,2))*Quad(
      1.02*msq2(2,2) - 0.98*msu2(2,2)))))) + (1 + Sqr(TanBeta))*(3*Sqr(AtInput -
      MuInput/TanBeta)*((1.9607843137254901*(0.96*msd2(2,2) + 3.06*msq2(2,2) -
      2.06*Sqr(MuInput)))/(msq2(2,2)*(-1.02*msq2(2,2) + 0.98*msu2(2,2))) + Log(Sqr
      (SCALE))*((1.9607843137254901*(0.96*msd2(2,2) + 2.04*msq2(2,2) - 2.06*Sqr(
      MuInput)))/(msq2(2,2)*(-1.02*msq2(2,2) + 0.98*msu2(2,2))) - (2*Log(0.98*msu2
      (2,2))*(0.96*msd2(2,2) + 1.02*msq2(2,2) + 0.98*msu2(2,2) - 2.06*Sqr(MuInput)
      ))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) + Log(1.02*msq2(2,2))*((2*Log(Sqr(
      SCALE))*(0.96*msd2(2,2) + 1.02*msq2(2,2) + 0.98*msu2(2,2) - 2.06*Sqr(MuInput
      )))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)) + (2*(0.96*msd2(2,2) + 3.06*msq2(2,
      2) - 2.06*Sqr(MuInput)) + ((-1.02*msq2(2,2) + 0.98*msu2(2,2))*(0.96*msd2(2,2
      ) + 1.03*Sqr(MuInput)))/(0.96*msd2(2,2) - 1.03*Sqr(MuInput)))/Sqr(1.02*msq2(
      2,2) - 0.98*msu2(2,2))) + (Log(0.98*msu2(2,2))*(-2*(0.96*msd2(2,2) + 3.06*
      msq2(2,2) - 2.06*Sqr(MuInput)) + ((1.02*msq2(2,2) - 0.98*msu2(2,2))*(4.8*
      msd2(2,2) - 3.09*Sqr(MuInput)))/(0.96*msd2(2,2) - 1.03*Sqr(MuInput))))/Sqr(
      1.02*msq2(2,2) - 0.98*msu2(2,2)) + (4*PolyLog(2,1 - (1.0098039215686274*Sqr(
      MuInput))/msq2(2,2))*(-0.98*msu2(2,2) + 1.03*Sqr(MuInput)))/Sqr(1.02*msq2(2,
      2) - 0.98*msu2(2,2)) - (4*PolyLog(2,1 - (1.0510204081632653*Sqr(MuInput))
      /msu2(2,2))*(-0.98*msu2(2,2) + 1.03*Sqr(MuInput)))/Sqr(1.02*msq2(2,2) - 0.98
      *msu2(2,2)) + (2*(-0.98*msu2(2,2) + 1.03*Sqr(MuInput))*Sqr(Log(1.02*msq2(2,2
      ))))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)) - (2*(-0.98*msu2(2,2) + 1.03*Sqr(
      MuInput))*Sqr(Log(0.98*msu2(2,2))))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)) +
      Log(0.96*msd2(2,2))*((1.92*msd2(2,2))/(-0.9996*msq2(2,2)*msu2(2,2) + 1.0404*
      Sqr(msq2(2,2))) + (2*Log(0.98*msu2(2,2))*(0.96*msd2(2,2) + (0.96*msd2(2,2)*(
      1.02*msq2(2,2) - 0.98*msu2(2,2))*(0.96*msd2(2,2) - 2.06*Sqr(MuInput)))/Sqr(
      0.96*msd2(2,2) - 1.03*Sqr(MuInput))))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)) +
      (1.92*Log(1.02*msq2(2,2))*msd2(2,2)*(-1 + ((-1.02*msq2(2,2) + 0.98*msu2(2,2
      ))*(0.96*msd2(2,2) - 2.06*Sqr(MuInput)))/Sqr(0.96*msd2(2,2) - 1.03*Sqr(
      MuInput))))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) + Log(1.03*Sqr(MuInput))*(
      (-4.12*Sqr(MuInput))/(-0.9996*msq2(2,2)*msu2(2,2) + 1.0404*Sqr(msq2(2,2))) +
      (2.1218*Log(0.98*msu2(2,2))*Quad(MuInput))/((1.02*msq2(2,2) - 0.98*msu2(2,2
      ))*Sqr(0.96*msd2(2,2) - 1.03*Sqr(MuInput))) + (2.1218*Log(1.02*msq2(2,2))*
      Quad(MuInput))/((-1.02*msq2(2,2) + 0.98*msu2(2,2))*Sqr(0.96*msd2(2,2) - 1.03
      *Sqr(MuInput))))) + 3*Quad(AtInput - MuInput/TanBeta)*((-2*PolyLog(2,1 - (
      1.0510204081632653*Sqr(MuInput))/msu2(2,2))*(2.04*msq2(2,2) + 0.98*msu2(2,2)
      - 3.09*Sqr(MuInput))*(0.98*msu2(2,2) - 1.03*Sqr(MuInput)))/Quad(1.02*msq2(2
      ,2) - 0.98*msu2(2,2)) + (2*PolyLog(2,1 - (1.0098039215686274*Sqr(MuInput))
      /msq2(2,2))*(-0.98*msu2(2,2) + 1.03*Sqr(MuInput))*(-2.04*msq2(2,2) - 0.98*
      msu2(2,2) + 3.09*Sqr(MuInput)))/Quad(1.02*msq2(2,2) - 0.98*msu2(2,2)) + ((
      -0.98*msu2(2,2) + 1.03*Sqr(MuInput))*(-2.04*msq2(2,2) - 0.98*msu2(2,2) +
      3.09*Sqr(MuInput))*Sqr(Log(1.02*msq2(2,2))))/Quad(1.02*msq2(2,2) - 0.98*msu2
      (2,2)) + ((0.98*msu2(2,2) - 1.03*Sqr(MuInput))*(-2.04*msq2(2,2) - 0.98*msu2(
      2,2) + 3.09*Sqr(MuInput))*Sqr(Log(0.98*msu2(2,2))))/Quad(1.02*msq2(2,2) -
      0.98*msu2(2,2)) + (0.9803921568627451*(0.96*msd2(2,2)*(4.08*msq2(2,2)*(1.02*
      msq2(2,2) + 1.96*msu2(2,2)) - 3.09*(7.140000000000001*msq2(2,2) + 0.98*msu2(
      2,2))*Sqr(MuInput)) + 2.06*Sqr(MuInput)*(-3.06*msq2(2,2)*(1.02*msq2(2,2) +
      0.98*msu2(2,2)) + 1.03*(8.16*msq2(2,2) + 0.98*msu2(2,2))*Sqr(MuInput)) +
      0.9216*(5.1*msq2(2,2) + 0.98*msu2(2,2))*Sqr(msd2(2,2))))/(Cube(1.02*msq2(2,2
      ) - 0.98*msu2(2,2))*msq2(2,2)*(0.96*msd2(2,2) - 1.03*Sqr(MuInput))) + (0.5*
      Log(0.98*msu2(2,2))*(0.96*msd2(2,2)*((1.02*msq2(2,2) + 0.98*msu2(2,2))*(1.02
      *msq2(2,2) + 10.78*msu2(2,2)) - 12.36*(1.02*msq2(2,2) + 2.94*msu2(2,2))*Sqr(
      MuInput)) + 1.03*Sqr(MuInput)*(-3*(1.02*msq2(2,2) + 0.98*msu2(2,2))*(1.02*
      msq2(2,2) + 2.94*msu2(2,2)) + 4.12*(2.04*msq2(2,2) + 6.859999999999999*msu2(
      2,2))*Sqr(MuInput)) + 3.6864*(1.02*msq2(2,2) + 1.96*msu2(2,2))*Sqr(msd2(2,2)
      )))/(Quad(1.02*msq2(2,2) - 0.98*msu2(2,2))*(0.96*msd2(2,2) - 1.03*Sqr(
      MuInput))) + Log(Sqr(SCALE))*((0.9803921568627451*(3.06*msq2(2,2)*(1.02*msq2
      (2,2) + 0.98*msu2(2,2)) + 0.96*msd2(2,2)*(5.1*msq2(2,2) + 0.98*msu2(2,2)) -
      2.06*(5.1*msq2(2,2) + 0.98*msu2(2,2))*Sqr(MuInput)))/(Cube(1.02*msq2(2,2) -
      0.98*msu2(2,2))*msq2(2,2)) + (Log(0.98*msu2(2,2))*(1.02*msq2(2,2)*(1.92*msd2
      (2,2) + 1.02*msq2(2,2) - 4.12*Sqr(MuInput)) + 3.92*msu2(2,2)*(0.96*msd2(2,2)
      + 1.02*msq2(2,2) - 2.06*Sqr(MuInput)) + 0.9603999999999999*Sqr(msu2(2,2))))
      /Quad(1.02*msq2(2,2) - 0.98*msu2(2,2))) + Log(1.02*msq2(2,2))*(-((Log(Sqr(
      SCALE))*(1.02*msq2(2,2)*(1.92*msd2(2,2) + 1.02*msq2(2,2) - 4.12*Sqr(MuInput)
      ) + 3.92*msu2(2,2)*(0.96*msd2(2,2) + 1.02*msq2(2,2) - 2.06*Sqr(MuInput)) +
      0.9603999999999999*Sqr(msu2(2,2))))/Quad(1.02*msq2(2,2) - 0.98*msu2(2,2))) +
      (0.5*(-3.92*msu2(2,2)*(1.92*msd2(2,2) + 5.1*msq2(2,2) - 4.12*Sqr(MuInput))*
      (0.96*msd2(2,2) - 1.03*Sqr(MuInput)) + 1.02*msq2(2,2)*(5.15*(1.02*msq2(2,2)
      - 4.12*Sqr(MuInput))*Sqr(MuInput) + 2.88*msd2(2,2)*(-1.02*msq2(2,2) + 8.24*
      Sqr(MuInput)) - 3.6864*Sqr(msd2(2,2))) - 0.9603999999999999*(0.96*msd2(2,2)
      + 1.03*Sqr(MuInput))*Sqr(msu2(2,2))))/(Quad(1.02*msq2(2,2) - 0.98*msu2(2,2))
      *(0.96*msd2(2,2) - 1.03*Sqr(MuInput)))) + Log(1.03*Sqr(MuInput))*((2.06*Sqr(
      MuInput)*(-3 + (0.9803921568627451*(1.02*msq2(2,2) - 0.98*msu2(2,2))*(1.0506
      *msq2(2,2)*Sqr(MuInput) + Sqr(-1.03*Sqr(MuInput) + 0.96*msd2(2,2))))/(msq2(2
      ,2)*Sqr(0.96*msd2(2,2) - 1.03*Sqr(MuInput)))))/Cube(-1.02*msq2(2,2) + 0.98*
      msu2(2,2)) + (1.0609*Log(1.02*msq2(2,2))*Quad(MuInput)*((1.02*msq2(2,2) -
      0.98*msu2(2,2))*(1.02*msq2(2,2) + 0.98*msu2(2,2)) - 6*Sqr(-1.03*Sqr(MuInput)
      + 0.96*msd2(2,2))))/(Quad(1.02*msq2(2,2) - 0.98*msu2(2,2))*Sqr(0.96*msd2(2,
      2) - 1.03*Sqr(MuInput))) + (1.0609*Log(0.98*msu2(2,2))*Quad(MuInput)*(6*Sqr(
      -1.03*Sqr(MuInput) + 0.96*msd2(2,2)) - 1.0404*Sqr(msq2(2,2)) +
      0.9603999999999999*Sqr(msu2(2,2))))/(Quad(1.02*msq2(2,2) - 0.98*msu2(2,2))*
      Sqr(0.96*msd2(2,2) - 1.03*Sqr(MuInput)))) + Log(0.96*msd2(2,2))*((0.96*msd2(
      2,2)*(6 - (0.9803921568627451*(1.02*msq2(2,2) - 0.98*msu2(2,2))*(-1.92*msd2(
      2,2)*(1.02*msq2(2,2) + 1.03*Sqr(MuInput)) + 1.03*Sqr(MuInput)*(4.08*msq2(2,2
      ) + 1.03*Sqr(MuInput)) + 0.9216*Sqr(msd2(2,2))))/(msq2(2,2)*Sqr(0.96*msd2(2,
      2) - 1.03*Sqr(MuInput)))))/Cube(-1.02*msq2(2,2) + 0.98*msu2(2,2)) + (0.96*
      Log(1.02*msq2(2,2))*msd2(2,2)*(3.92*msu2(2,2)*Sqr(-1.03*Sqr(MuInput) + 0.96*
      msd2(2,2)) + 1.02*msq2(2,2)*(1.02*msq2(2,2)*(0.96*msd2(2,2) - 2.06*Sqr(
      MuInput)) + 2*Sqr(-1.03*Sqr(MuInput) + 0.96*msd2(2,2))) - 0.9603999999999999
      *(0.96*msd2(2,2) - 2.06*Sqr(MuInput))*Sqr(msu2(2,2))))/(Quad(1.02*msq2(2,2)
      - 0.98*msu2(2,2))*Sqr(0.96*msd2(2,2) - 1.03*Sqr(MuInput))) + (0.96*Log(0.98*
      msu2(2,2))*msd2(2,2)*(1.02*msq2(2,2)*(-1.02*msq2(2,2)*(0.96*msd2(2,2) - 2.06
      *Sqr(MuInput)) - 2*Sqr(-1.03*Sqr(MuInput) + 0.96*msd2(2,2))) - 3.92*msu2(2,2
      )*Sqr(-1.03*Sqr(MuInput) + 0.96*msd2(2,2)) + 0.9603999999999999*(0.96*msd2(2
      ,2) - 2.06*Sqr(MuInput))*Sqr(msu2(2,2))))/(Quad(1.02*msq2(2,2) - 0.98*msu2(2
      ,2))*Sqr(0.96*msd2(2,2) - 1.03*Sqr(MuInput))))) + 3*(-1.5 + 2*PolyLog(2,1 -
      (1.0098039215686274*Sqr(MuInput))/msq2(2,2)) + Log(Sqr(SCALE))*(Log(0.98*
      msu2(2,2)) - (0.9803921568627451*(0.96*msd2(2,2) + 1.02*msq2(2,2) - 2.06*Sqr
      (MuInput)))/msq2(2,2)) - (0.9803921568627451*(0.96*msd2(2,2) - 2.06*Sqr(
      MuInput)))/msq2(2,2) + (0.96*msd2(2,2))/(0.96*msd2(2,2) - 1.03*Sqr(MuInput))
      + Log(0.98*msu2(2,2))*(1.5 + (0.96*msd2(2,2))/(-0.96*msd2(2,2) + 1.03*Sqr(
      MuInput))) + Log(1.02*msq2(2,2))*(0.5 - Log(Sqr(SCALE)) + (0.96*msd2(2,2))/(
      -0.96*msd2(2,2) + 1.03*Sqr(MuInput))) + Sqr(Log(1.02*msq2(2,2))) + Log(0.96*
      msd2(2,2))*(0.96*msd2(2,2)*(0.9803921568627451/msq2(2,2) + (0.96*msd2(2,2) +
      2.06*Sqr(MuInput))/Sqr(0.96*msd2(2,2) - 1.03*Sqr(MuInput))) + (2.1218*Log(
      1.03*Sqr(MuInput))*Quad(MuInput))/Sqr(0.96*msd2(2,2) - 1.03*Sqr(MuInput)) -
      (0.96*Log(1.02*msq2(2,2))*msd2(2,2)*(0.96*msd2(2,2) - 2.06*Sqr(MuInput)))
      /Sqr(0.96*msd2(2,2) - 1.03*Sqr(MuInput)) - (0.96*Log(0.98*msu2(2,2))*msd2(2,
      2)*(0.96*msd2(2,2) - 2.06*Sqr(MuInput)))/Sqr(0.96*msd2(2,2) - 1.03*Sqr(
      MuInput))) + Log(1.03*Sqr(MuInput))*((-2.019607843137255*Sqr(MuInput))/msq2(
      2,2) - (1.0609*Log(1.02*msq2(2,2))*Quad(MuInput))/Sqr(0.96*msd2(2,2) - 1.03*
      Sqr(MuInput)) - (1.0609*Log(0.98*msu2(2,2))*Quad(MuInput))/Sqr(0.96*msd2(2,2
      ) - 1.03*Sqr(MuInput)) - (1.03*Sqr(MuInput)*(1.92*msd2(2,2) + 1.03*Sqr(
      MuInput)))/Sqr(0.96*msd2(2,2) - 1.03*Sqr(MuInput))) + (2*PolyLog(2,1 - (
      1.0729166666666667*Sqr(MuInput))/msd2(2,2))*(-1.0609*Quad(MuInput) - 1.9776*
      msd2(2,2)*Sqr(MuInput) + 0.9216*Sqr(msd2(2,2))))/Sqr(0.96*msd2(2,2) - 1.03*
      Sqr(MuInput)) + (Sqr(Log(0.96*msd2(2,2)))*(-1.0609*Quad(MuInput) - 1.9776*
      msd2(2,2)*Sqr(MuInput) + 0.9216*Sqr(msd2(2,2))))/Sqr(0.96*msd2(2,2) - 1.03*
      Sqr(MuInput)))) + 3*(AbInput + MuInput/TanBeta)*(AbInput - MuInput*TanBeta)*
      ((2*Log(0.96*msd2(2,2))*Log(1.02*msq2(2,2)))/(0.96*msd2(2,2) - 1.02*msq2(2,2
      )) + Log(0.98*Sqr(mAInput))*((2*Log(1.02*msq2(2,2)))/(0.96*msd2(2,2) - 1.02*
      msq2(2,2)) + (2*Log(0.96*msd2(2,2)))/(-0.96*msd2(2,2) + 1.02*msq2(2,2))) + (
      2*Sqr(Log(1.02*msq2(2,2))))/(-0.96*msd2(2,2) + 1.02*msq2(2,2)) - (
      2.0833333333333335*(0.96*msd2(2,2) - 1.02*msq2(2,2) + 0.98*Sqr(mAInput))*
      TPhi(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2)))/(msd2(2,2)*(0.96*msd2
      (2,2) - 1.02*msq2(2,2))) + (1.9215686274509802*Sqr(mAInput)*TPhi(0.98*Sqr(
      mAInput),1.02*msq2(2,2),1.02*msq2(2,2)))/((0.96*msd2(2,2) - 1.02*msq2(2,2))*
      msq2(2,2))) + 3*(-1 + 2*Log(0.96*msd2(2,2))*Log(0.98*msu2(2,2)) + (-2*Log(
      0.96*msd2(2,2)) - 4*Log(1.02*msq2(2,2)) - 2*Log(0.98*msu2(2,2)))*Log(0.98*
      Sqr(mAInput)) - 2*Log(Sqr(SCALE)) + Log(1.02*msq2(2,2))*(2 + 2*Log(Sqr(SCALE
      ))) + 1.3333333333333333*Sqr(3.141592653589793) + 4*Sqr(Log(0.98*Sqr(mAInput
      ))) - Sqr(Log(Sqr(SCALE))) + Sqr(Log(1.02*msq2(2,2))) - (1.9215686274509802*
      Sqr(mAInput)*TPhi(0.98*Sqr(mAInput),1.02*msq2(2,2),1.02*msq2(2,2)))/msq2(2,2
      ) - (2.0833333333333335*(0.96*msd2(2,2) - 0.98*msu2(2,2) + 0.98*Sqr(mAInput)
      )*TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),0.96*msd2(2,2)))/msd2(2,2)) + Sqr(
      TanBeta)*(3*Sqr(AbInput + MuInput/TanBeta)*(-0.9803921568627451/msq2(2,2) -
      (0.9803921568627451*Log(Sqr(SCALE)))/msq2(2,2) - (Log(1.02*msq2(2,2))*(0.96*
      msd2(2,2) - 1.02*msq2(2,2) + 0.98*Sqr(mAInput)))/TDelta(0.98*Sqr(mAInput),
      1.02*msq2(2,2),0.96*msd2(2,2)) + (0.49019607843137253*Log(0.98*Sqr(mAInput))
      *(0.9603999999999999*Quad(mAInput) - Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) +
      TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2))))/(msq2(2,2)*TDelta(
      0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2))) + (0.49019607843137253*Log
      (0.96*msd2(2,2))*(-0.9603999999999999*Quad(mAInput) + 1.9992*msq2(2,2)*Sqr(
      mAInput) + 0.9216*Sqr(msd2(2,2)) - 1.0404*Sqr(msq2(2,2)) + TDelta(0.98*Sqr(
      mAInput),1.02*msq2(2,2),0.96*msd2(2,2))))/(msq2(2,2)*TDelta(0.98*Sqr(mAInput
      ),1.02*msq2(2,2),0.96*msd2(2,2))) + (0.5208333333333334*(-Sqr(0.98*Sqr(
      mAInput) + 0.96*msd2(2,2) - 1.02*msq2(2,2)) + TDelta(0.98*Sqr(mAInput),1.02*
      msq2(2,2),0.96*msd2(2,2)))*TPhi(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2
      ,2)))/(msd2(2,2)*TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2)))) +
      3*(0.5 - 1.5*Log(0.98*msu2(2,2)) + Log(0.96*msd2(2,2))*Log(0.98*msu2(2,2))
      + Log(1.02*msq2(2,2))*(0.5 + Log(Sqr(SCALE))) + 0.3333333333333333*Sqr(
      3.141592653589793) + Log(0.98*Sqr(mAInput))*(-Log(0.96*msd2(2,2)) - Log(1.02
      *msq2(2,2)) + (0.9803921568627451*(1.02*msq2(2,2) + 0.98*Sqr(mAInput)))/msq2
      (2,2)) - (0.9607843137254901*Sqr(mAInput))/msq2(2,2) + Log(Sqr(SCALE))*(-Log
      (0.98*msu2(2,2)) - (0.9607843137254901*Sqr(mAInput))/msq2(2,2)) + Sqr(Log(
      0.98*Sqr(mAInput))) - (1.0416666666666667*(0.96*msd2(2,2) - 0.98*msu2(2,2) +
      0.98*Sqr(mAInput))*TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),0.96*msd2(2,2)))
      /msd2(2,2)) + 3*(AtInput - MuInput/TanBeta)*(AbInput + MuInput/TanBeta)*(Log
      (0.96*msd2(2,2))*((2*Log(1.02*msq2(2,2)))/(1.02*msq2(2,2) - 0.98*msu2(2,2))
      + (2*Log(0.98*msu2(2,2)))/(-1.02*msq2(2,2) + 0.98*msu2(2,2))) + Log(0.98*Sqr
      (mAInput))*((2*Log(1.02*msq2(2,2)))/(1.02*msq2(2,2) - 0.98*msu2(2,2)) + (2*
      Log(0.98*msu2(2,2)))/(-1.02*msq2(2,2) + 0.98*msu2(2,2))) + Log(1.02*msq2(2,2
      ))*(4/(-1.02*msq2(2,2) + 0.98*msu2(2,2)) + (4*Log(Sqr(SCALE)))/(-1.02*msq2(2
      ,2) + 0.98*msu2(2,2))) + (4*Log(0.98*msu2(2,2)))/(1.02*msq2(2,2) - 0.98*msu2
      (2,2)) + (4*Log(0.98*msu2(2,2))*Log(Sqr(SCALE)))/(1.02*msq2(2,2) - 0.98*msu2
      (2,2)) + (2.0833333333333335*(0.96*msd2(2,2) - 1.02*msq2(2,2) + 0.98*Sqr(
      mAInput))*TPhi(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2)))/(msd2(2,2)*
      (-1.02*msq2(2,2) + 0.98*msu2(2,2))) + (2.0833333333333335*(0.96*msd2(2,2) -
      0.98*msu2(2,2) + 0.98*Sqr(mAInput))*TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),
      0.96*msd2(2,2)))/(msd2(2,2)*(1.02*msq2(2,2) - 0.98*msu2(2,2)))) + 3*(AbInput
      + MuInput/TanBeta)*Cube(AtInput - MuInput/TanBeta)*(Log(1.02*msq2(2,2))*((4
      *Log(Sqr(SCALE))*(1.02*msq2(2,2) + 0.98*msu2(2,2)))/Cube(1.02*msq2(2,2) -
      0.98*msu2(2,2)) + (4*(3.06*msq2(2,2) + 0.98*msu2(2,2)))/Cube(1.02*msq2(2,2)
      - 0.98*msu2(2,2))) - (4*Log(0.98*msu2(2,2))*(1.02*msq2(2,2) + 2.94*msu2(2,2)
      ))/Cube(1.02*msq2(2,2) - 0.98*msu2(2,2)) + Log(0.96*msd2(2,2))*((-2*Log(1.02
      *msq2(2,2))*(1.92*msd2(2,2) + 1.02*msq2(2,2) + 0.98*msu2(2,2) - 1.96*Sqr(
      mAInput)))/Cube(1.02*msq2(2,2) - 0.98*msu2(2,2)) + (2*Log(0.98*msu2(2,2))*(
      1.92*msd2(2,2) + 1.02*msq2(2,2) + 0.98*msu2(2,2) - 1.96*Sqr(mAInput)))/Cube(
      1.02*msq2(2,2) - 0.98*msu2(2,2))) + Log(0.98*Sqr(mAInput))*((-2*Log(1.02*
      msq2(2,2))*(-1.92*msd2(2,2) + 1.02*msq2(2,2) + 0.98*msu2(2,2) + 1.96*Sqr(
      mAInput)))/Cube(1.02*msq2(2,2) - 0.98*msu2(2,2)) + (2*Log(0.98*msu2(2,2))*(
      -1.92*msd2(2,2) + 1.02*msq2(2,2) + 0.98*msu2(2,2) + 1.96*Sqr(mAInput)))/Cube
      (1.02*msq2(2,2) - 0.98*msu2(2,2))) + Log(Sqr(SCALE))*((-4*Log(0.98*msu2(2,2)
      )*(1.02*msq2(2,2) + 0.98*msu2(2,2)))/Cube(1.02*msq2(2,2) - 0.98*msu2(2,2)) -
      8/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) - 16/Sqr(1.02*msq2(2,2) - 0.98*msu2
      (2,2)) - (2.0833333333333335*((1.02*msq2(2,2) - 0.98*msu2(2,2))*(0.96*msd2(2
      ,2) - 1.02*msq2(2,2) + 0.98*Sqr(mAInput)) + 2*TDelta(0.98*Sqr(mAInput),1.02*
      msq2(2,2),0.96*msd2(2,2)))*TPhi(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2
      ,2)))/(Cube(1.02*msq2(2,2) - 0.98*msu2(2,2))*msd2(2,2)) + (
      1.0416666666666667*(2*(-1.02*msq2(2,2) + 0.98*msu2(2,2))*(0.96*msd2(2,2) -
      0.98*msu2(2,2) + 0.98*Sqr(mAInput)) + 4*TDelta(0.98*Sqr(mAInput),0.98*msu2(2
      ,2),0.96*msd2(2,2)))*TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),0.96*msd2(2,2)))/
      (Cube(1.02*msq2(2,2) - 0.98*msu2(2,2))*msd2(2,2))) + Quad(AtInput -
      MuInput/TanBeta)*(3*((0.9803921568627451*(1.02*msq2(2,2)*(1.02*msq2(2,2) -
      0.98*msu2(2,2)) + 0.98*(5.1*msq2(2,2) + 0.98*msu2(2,2))*Sqr(mAInput)))/(Cube
      (1.02*msq2(2,2) - 0.98*msu2(2,2))*msq2(2,2)) + Log(Sqr(SCALE))*((
      0.9803921568627451*(2.04*msq2(2,2)*(1.02*msq2(2,2) - 0.98*msu2(2,2)) + 0.98*
      (5.1*msq2(2,2) + 0.98*msu2(2,2))*Sqr(mAInput)))/(Cube(1.02*msq2(2,2) - 0.98*
      msu2(2,2))*msq2(2,2)) + (Log(0.98*msu2(2,2))*(1.9992*msq2(2,2)*Sqr(mAInput)
      + 3.8415999999999997*msu2(2,2)*Sqr(mAInput) + 1.0404*Sqr(msq2(2,2)) -
      0.9603999999999999*Sqr(msu2(2,2))))/Quad(1.02*msq2(2,2) - 0.98*msu2(2,2))) +
      Log(0.98*Sqr(mAInput))*((0.9803921568627451*(2.04*msq2(2,2)*(-1.02*msq2(2,2
      ) + 0.98*msu2(2,2)) - 0.98*(5.1*msq2(2,2) + 0.98*msu2(2,2))*Sqr(mAInput)))/(
      Cube(1.02*msq2(2,2) - 0.98*msu2(2,2))*msq2(2,2)) + (Log(1.02*msq2(2,2))*(
      1.9992*msq2(2,2)*Sqr(mAInput) + 3.8415999999999997*msu2(2,2)*Sqr(mAInput) +
      1.0404*Sqr(msq2(2,2)) - 0.9603999999999999*Sqr(msu2(2,2))))/Quad(1.02*msq2(2
      ,2) - 0.98*msu2(2,2)) + (Log(0.98*msu2(2,2))*(-3.8415999999999997*msu2(2,2)*
      Sqr(mAInput) - 1.02*msq2(2,2)*(1.02*msq2(2,2) + 1.96*Sqr(mAInput)) +
      0.9603999999999999*Sqr(msu2(2,2))))/Quad(1.02*msq2(2,2) - 0.98*msu2(2,2))) +
      Log(1.02*msq2(2,2))*((Log(Sqr(SCALE))*(-3.8415999999999997*msu2(2,2)*Sqr(
      mAInput) - 1.02*msq2(2,2)*(1.02*msq2(2,2) + 1.96*Sqr(mAInput)) +
      0.9603999999999999*Sqr(msu2(2,2))))/Quad(1.02*msq2(2,2) - 0.98*msu2(2,2)) +
      (0.5*(-7.683199999999999*msu2(2,2)*Sqr(mAInput) - 1.02*msq2(2,2)*(1.02*msq2(
      2,2) + 3.92*Sqr(mAInput)) + 0.9603999999999999*Sqr(msu2(2,2))))/Quad(1.02*
      msq2(2,2) - 0.98*msu2(2,2))) + (0.5*Log(0.98*msu2(2,2))*(3.9984*msq2(2,2)*
      Sqr(mAInput) + 7.683199999999999*msu2(2,2)*Sqr(mAInput) + 1.0404*Sqr(msq2(2,
      2)) - 0.9603999999999999*Sqr(msu2(2,2))))/Quad(1.02*msq2(2,2) - 0.98*msu2(2,
      2))) + 3*Sqr(AbInput + MuInput/TanBeta)*((0.9803921568627451*(11.22*msq2(2,2
      ) + 0.98*msu2(2,2)))/(Cube(1.02*msq2(2,2) - 0.98*msu2(2,2))*msq2(2,2)) + Log
      (Sqr(SCALE))*((0.9803921568627451*(5.1*msq2(2,2) + 0.98*msu2(2,2)))/(Cube(
      1.02*msq2(2,2) - 0.98*msu2(2,2))*msq2(2,2)) + (2*Log(0.98*msu2(2,2))*(1.02*
      msq2(2,2) + 1.96*msu2(2,2)))/Quad(1.02*msq2(2,2) - 0.98*msu2(2,2))) + (2*Log
      (0.98*msu2(2,2))*(1.02*msq2(2,2) + 4.9*msu2(2,2)))/Quad(1.02*msq2(2,2) -
      0.98*msu2(2,2)) + Log(1.02*msq2(2,2))*((-4*(2.04*msq2(2,2) + 0.98*msu2(2,2))
      )/Quad(1.02*msq2(2,2) - 0.98*msu2(2,2)) - (2*Log(Sqr(SCALE))*(1.02*msq2(2,2)
      + 1.96*msu2(2,2)))/Quad(1.02*msq2(2,2) - 0.98*msu2(2,2)) - (0.96*msd2(2,2)
      - 1.02*msq2(2,2) + 0.98*Sqr(mAInput))/(Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))*
      TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2)))) + Log(0.98*Sqr(
      mAInput))*((Log(1.02*msq2(2,2))*(-2.88*msd2(2,2) + 1.02*msq2(2,2) + 1.96*
      msu2(2,2) + 2.94*Sqr(mAInput)))/Quad(1.02*msq2(2,2) - 0.98*msu2(2,2)) - (Log
      (0.98*msu2(2,2))*(-2.88*msd2(2,2) + 1.02*msq2(2,2) + 1.96*msu2(2,2) + 2.94*
      Sqr(mAInput)))/Quad(1.02*msq2(2,2) - 0.98*msu2(2,2)) + (0.49019607843137253*
      (0.9603999999999999*Quad(mAInput) - Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) +
      TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2))))/(msq2(2,2)*Sqr(
      1.02*msq2(2,2) - 0.98*msu2(2,2))*TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),
      0.96*msd2(2,2)))) + Log(0.96*msd2(2,2))*((Log(1.02*msq2(2,2))*(2.88*msd2(2,2
      ) + 1.02*msq2(2,2) + 1.96*msu2(2,2) - 2.94*Sqr(mAInput)))/Quad(1.02*msq2(2,2
      ) - 0.98*msu2(2,2)) - (Log(0.98*msu2(2,2))*(2.88*msd2(2,2) + 1.02*msq2(2,2)
      + 1.96*msu2(2,2) - 2.94*Sqr(mAInput)))/Quad(1.02*msq2(2,2) - 0.98*msu2(2,2))
      + (0.49019607843137253*(-0.9603999999999999*Quad(mAInput) + 1.9992*msq2(2,2
      )*Sqr(mAInput) + 0.9216*Sqr(msd2(2,2)) - 1.0404*Sqr(msq2(2,2)) + TDelta(0.98
      *Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2))))/(msq2(2,2)*Sqr(1.02*msq2(2,2)
      - 0.98*msu2(2,2))*TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2))))
      + (0.5208333333333334*(-(Sqr(0.98*Sqr(mAInput) + 0.96*msd2(2,2) - 1.02*msq2
      (2,2))*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) + 6*Sqr(TDelta(0.98*Sqr(mAInput
      ),1.02*msq2(2,2),0.96*msd2(2,2))) + (1.02*msq2(2,2) - 0.98*msu2(2,2))*(3.84*
      msd2(2,2) - 3.06*msq2(2,2) - 0.98*msu2(2,2) + 3.92*Sqr(mAInput))*TDelta(0.98
      *Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2)))*TPhi(0.98*Sqr(mAInput),1.02*
      msq2(2,2),0.96*msd2(2,2)))/(msd2(2,2)*Quad(1.02*msq2(2,2) - 0.98*msu2(2,2))*
      TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2))) + (
      1.0416666666666667*((1.02*msq2(2,2) - 0.98*msu2(2,2))*(0.96*msd2(2,2) - 0.98
      *msu2(2,2) + 0.98*Sqr(mAInput)) - 3*TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),
      0.96*msd2(2,2)))*TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),0.96*msd2(2,2)))/(
      msd2(2,2)*Quad(1.02*msq2(2,2) - 0.98*msu2(2,2))))) + Sqr(AtInput -
      MuInput/TanBeta)*(3*Sqr(AbInput + MuInput/TanBeta)*(-2/(-0.9996*msq2(2,2)*
      msu2(2,2) + 1.0404*Sqr(msq2(2,2))) + Log(Sqr(SCALE))*(-2/(-0.9996*msq2(2,2)*
      msu2(2,2) + 1.0404*Sqr(msq2(2,2))) - (2*Log(0.98*msu2(2,2)))/Sqr(1.02*msq2(2
      ,2) - 0.98*msu2(2,2))) - (2*Log(0.98*msu2(2,2)))/Sqr(1.02*msq2(2,2) - 0.98*
      msu2(2,2)) + Log(1.02*msq2(2,2))*((2*Log(Sqr(SCALE)))/Sqr(1.02*msq2(2,2) -
      0.98*msu2(2,2)) + (2*((-1.02*msq2(2,2) + 0.98*msu2(2,2))*(0.96*msd2(2,2) -
      1.02*msq2(2,2) + 0.98*Sqr(mAInput)) + TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2
      ),0.96*msd2(2,2))))/(Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))*TDelta(0.98*Sqr(
      mAInput),1.02*msq2(2,2),0.96*msd2(2,2)))) + Log(0.98*Sqr(mAInput))*(-(Log(
      1.02*msq2(2,2))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) + Log(0.98*msu2(2,2))
      /Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)) + (0.9803921568627451*(
      0.9603999999999999*Quad(mAInput) - Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) +
      TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2))))/(msq2(2,2)*(1.02*
      msq2(2,2) - 0.98*msu2(2,2))*TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*
      msd2(2,2)))) + Log(0.96*msd2(2,2))*(-(Log(1.02*msq2(2,2))/Sqr(1.02*msq2(2,2)
      - 0.98*msu2(2,2))) + Log(0.98*msu2(2,2))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2
      )) + (0.9803921568627451*(-0.9603999999999999*Quad(mAInput) + 1.9992*msq2(2,
      2)*Sqr(mAInput) + 0.9216*Sqr(msd2(2,2)) - 1.0404*Sqr(msq2(2,2)) + TDelta(
      0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2))))/(msq2(2,2)*(1.02*msq2(2,2
      ) - 0.98*msu2(2,2))*TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2)))
      ) + (1.0416666666666667*(-((1.02*msq2(2,2) - 0.98*msu2(2,2))*Sqr(0.98*Sqr(
      mAInput) + 0.96*msd2(2,2) - 1.02*msq2(2,2))) + (0.96*msd2(2,2) - 0.98*msu2(2
      ,2) + 0.98*Sqr(mAInput))*TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2
      ,2)))*TPhi(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2)))/(msd2(2,2)*Sqr(
      1.02*msq2(2,2) - 0.98*msu2(2,2))*TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),
      0.96*msd2(2,2))) - (1.0416666666666667*(0.96*msd2(2,2) - 0.98*msu2(2,2) +
      0.98*Sqr(mAInput))*TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),0.96*msd2(2,2)))/(
      msd2(2,2)*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)))) + 3*((0.9803921568627451*(
      4.08*msq2(2,2) - 1.96*Sqr(mAInput)))/(msq2(2,2)*(1.02*msq2(2,2) - 0.98*msu2(
      2,2))) + Log(0.96*msd2(2,2))*((Log(1.02*msq2(2,2))*(0.96*msd2(2,2) + 1.02*
      msq2(2,2) - 0.98*Sqr(mAInput)))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)) - (Log(
      0.98*msu2(2,2))*(0.96*msd2(2,2) + 1.02*msq2(2,2) - 0.98*Sqr(mAInput)))/Sqr(
      1.02*msq2(2,2) - 0.98*msu2(2,2))) + Log(0.98*Sqr(mAInput))*((1.96*Sqr(
      mAInput))/(-0.9996*msq2(2,2)*msu2(2,2) + 1.0404*Sqr(msq2(2,2))) - (Log(1.02*
      msq2(2,2))*(0.96*msd2(2,2) + 1.02*msq2(2,2) - 1.96*msu2(2,2) + 0.98*Sqr(
      mAInput)))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)) + (Log(0.98*msu2(2,2))*(0.96
      *msd2(2,2) + 1.02*msq2(2,2) - 1.96*msu2(2,2) + 0.98*Sqr(mAInput)))/Sqr(1.02*
      msq2(2,2) - 0.98*msu2(2,2))) + Log(Sqr(SCALE))*((1.9607843137254901*(1.02*
      msq2(2,2) - 0.98*Sqr(mAInput)))/(msq2(2,2)*(1.02*msq2(2,2) - 0.98*msu2(2,2))
      ) - (2*Log(0.98*msu2(2,2))*(-0.98*msu2(2,2) + 0.98*Sqr(mAInput)))/Sqr(1.02*
      msq2(2,2) - 0.98*msu2(2,2))) + Log(1.02*msq2(2,2))*(-((3.06*msq2(2,2) + 0.98
      *msu2(2,2) - 1.96*Sqr(mAInput))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) + (2*
      Log(Sqr(SCALE))*(-0.98*msu2(2,2) + 0.98*Sqr(mAInput)))/Sqr(1.02*msq2(2,2) -
      0.98*msu2(2,2))) + (Log(0.98*msu2(2,2))*(1.02*msq2(2,2) + 2.94*msu2(2,2) -
      1.96*Sqr(mAInput)))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)) + (
      1.0416666666666667*TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2))*
      TPhi(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2)))/(msd2(2,2)*Sqr(1.02*
      msq2(2,2) - 0.98*msu2(2,2))) + (1.0416666666666667*((1.02*msq2(2,2) - 0.98*
      msu2(2,2))*(0.96*msd2(2,2) - 0.98*msu2(2,2) + 0.98*Sqr(mAInput)) - TDelta(
      0.98*Sqr(mAInput),0.98*msu2(2,2),0.96*msd2(2,2)))*TPhi(0.98*Sqr(mAInput),
      0.98*msu2(2,2),0.96*msd2(2,2)))/(msd2(2,2)*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,
      2)))))) + 3*(AbInput - MuInput*TanBeta)*(AtInput + MuInput*TanBeta)*((2*Log(
      0.96*msd2(2,2))*Log(0.98*msu2(2,2)))/(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (2*
      Log(1.02*msq2(2,2))*Log(0.98*msu2(2,2)))/(-0.96*msd2(2,2) + 1.02*msq2(2,2))
      + Log(0.98*Sqr(mAInput))*((2*Log(1.02*msq2(2,2)))/(0.96*msd2(2,2) - 1.02*
      msq2(2,2)) + (2*Log(0.96*msd2(2,2)))/(-0.96*msd2(2,2) + 1.02*msq2(2,2))) - (
      2.0833333333333335*(0.96*msd2(2,2) - 0.98*msu2(2,2) + 0.98*Sqr(mAInput))*
      TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),0.96*msd2(2,2)))/(msd2(2,2)*(0.96*msd2
      (2,2) - 1.02*msq2(2,2))) + (1.9607843137254901*(1.02*msq2(2,2) - 0.98*msu2(2
      ,2) + 0.98*Sqr(mAInput))*TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2
      )))/((0.96*msd2(2,2) - 1.02*msq2(2,2))*msq2(2,2))) + Sqr(AtInput -
      MuInput/TanBeta)*(3*Sqr(AbInput - MuInput*TanBeta)*((6*(-1.92*msd2(2,2) +
      1.02*msq2(2,2) + 0.98*msu2(2,2))*PolyLog(2,1 - (1.0408163265306123*msq2(2,2)
      )/msu2(2,2)))/((1.02*msq2(2,2) - 0.98*msu2(2,2))*Sqr(0.96*msd2(2,2) - 1.02*
      msq2(2,2))) - 2/(-0.9996*msq2(2,2)*msu2(2,2) + 1.0404*Sqr(msq2(2,2))) + Log(
      Sqr(SCALE))*(-2/(-0.9996*msq2(2,2)*msu2(2,2) + 1.0404*Sqr(msq2(2,2))) - (2*
      Log(0.98*msu2(2,2)))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) + Log(0.96*msd2(2
      ,2))*((1.8823529411764703*msd2(2,2))/((0.96*msd2(2,2) - 1.02*msq2(2,2))*msq2
      (2,2)*(1.02*msq2(2,2) - 0.98*msu2(2,2))) + (3.84*Log(1.02*msq2(2,2))*msd2(2,
      2)*(0.96*msd2(2,2) - 0.98*msu2(2,2)))/(Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))*
      Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) + (3.84*Log(0.98*msu2(2,2))*msd2(2,2)*
      (-0.96*msd2(2,2) + 0.98*msu2(2,2)))/(Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))*
      Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)))) + Log(1.02*msq2(2,2))*(2/Sqr(1.02*
      msq2(2,2) - 0.98*msu2(2,2)) + (2*Log(Sqr(SCALE)))/Sqr(1.02*msq2(2,2) - 0.98*
      msu2(2,2)) + (Log(0.98*msu2(2,2))*(7.8336*msd2(2,2)*msq2(2,2) - 3.7632*msd2(
      2,2)*msu2(2,2) - 4.1616*Sqr(msq2(2,2))))/(Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2
      ))*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)))) - (2*Log(0.98*msu2(2,2))*(0.96*
      msd2(2,2) - 0.98*msu2(2,2)))/((0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(1.02*
      msq2(2,2) - 0.98*msu2(2,2))) + (6*(0.96*msd2(2,2) + 1.02*msq2(2,2) - 1.96*
      msu2(2,2))*PolyLog(2,1 - (0.9411764705882352*msd2(2,2))/msq2(2,2)))/((-0.96*
      msd2(2,2) + 1.02*msq2(2,2))*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) + (3*Sqr(
      Log(0.98*msu2(2,2))))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)) + (Sqr(Log(1.02*
      msq2(2,2)))*(-1.9584*msd2(2,2)*msq2(2,2) + 3.7632*msd2(2,2)*msu2(2,2) -
      2.7648*Sqr(msd2(2,2)) + 1.0404*Sqr(msq2(2,2))))/(Sqr(0.96*msd2(2,2) - 1.02*
      msq2(2,2))*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) + (6*PolyLog(2,1 - (
      0.9795918367346939*msd2(2,2))/msu2(2,2))*Sqr(0.96*msd2(2,2) - 0.98*msu2(2,2)
      ))/(Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)
      ))) + 3*(8/(1.02*msq2(2,2) - 0.98*msu2(2,2)) + (12*PolyLog(2,1 - (
      1.0408163265306123*msq2(2,2))/msu2(2,2)))/(1.02*msq2(2,2) - 0.98*msu2(2,2))
      + (6*Sqr(Log(0.98*msu2(2,2))))/(1.02*msq2(2,2) - 0.98*msu2(2,2)) + Log(0.98*
      Sqr(mAInput))*((-2*Log(1.02*msq2(2,2))*(0.96*msd2(2,2) + 2.04*msq2(2,2) -
      2.94*msu2(2,2)))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)) + (2*Log(0.98*msu2(2,2
      ))*(0.96*msd2(2,2) + 2.04*msq2(2,2) - 2.94*msu2(2,2)))/Sqr(1.02*msq2(2,2) -
      0.98*msu2(2,2))) + Log(Sqr(SCALE))*(4/(1.02*msq2(2,2) - 0.98*msu2(2,2)) + (
      Log(0.98*msu2(2,2))*(-8.16*msq2(2,2) + 11.76*msu2(2,2)))/Sqr(1.02*msq2(2,2)
      - 0.98*msu2(2,2))) + Log(0.96*msd2(2,2))*((2*Log(1.02*msq2(2,2))*(0.96*msd2(
      2,2) + 1.02*msq2(2,2) - 0.98*Sqr(mAInput)))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2
      ,2)) + (2*Log(0.98*msu2(2,2))*(-0.96*msd2(2,2) - 1.02*msq2(2,2) + 0.98*Sqr(
      mAInput)))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) + Log(1.02*msq2(2,2))*((2*(
      1.02*msq2(2,2) - 4.9*msu2(2,2)))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)) + (4*
      Log(Sqr(SCALE))*(2.04*msq2(2,2) - 2.94*msu2(2,2)))/Sqr(1.02*msq2(2,2) - 0.98
      *msu2(2,2)) - (2*Log(0.98*msu2(2,2))*(3.06*msq2(2,2) - 2.94*msu2(2,2) + 0.98
      *Sqr(mAInput)))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) + (Log(0.98*msu2(2,2))
      *(-6.12*msq2(2,2) + 13.719999999999999*msu2(2,2)))/Sqr(1.02*msq2(2,2) - 0.98
      *msu2(2,2)) + (1.96*Sqr(mAInput)*Sqr(Log(1.02*msq2(2,2))))/Sqr(1.02*msq2(2,2
      ) - 0.98*msu2(2,2)) + (2.0833333333333335*TDelta(0.98*Sqr(mAInput),1.02*msq2
      (2,2),0.96*msd2(2,2))*TPhi(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2)))
      /(msd2(2,2)*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) - (1.9607843137254901*(
      0.98*(1.02*msq2(2,2) - 0.98*msu2(2,2))*Sqr(mAInput) + TDelta(0.98*Sqr(
      mAInput),1.02*msq2(2,2),1.02*msq2(2,2)))*TPhi(0.98*Sqr(mAInput),1.02*msq2(2,
      2),1.02*msq2(2,2)))/(msq2(2,2)*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) + (
      2.0833333333333335*((1.02*msq2(2,2) - 0.98*msu2(2,2))*(0.96*msd2(2,2) - 0.98
      *msu2(2,2) + 0.98*Sqr(mAInput)) - TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),
      0.96*msd2(2,2)))*TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),0.96*msd2(2,2)))/(
      msd2(2,2)*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) + (1.9607843137254901*TDelta
      (0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2))*TPhi(0.98*Sqr(mAInput),
      0.98*msu2(2,2),1.02*msq2(2,2)))/(msq2(2,2)*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,
      2)))) + 3*(AbInput + MuInput/TanBeta)*(AbInput - MuInput*TanBeta)*(Log(0.98*
      Sqr(mAInput))*((2*Log(1.02*msq2(2,2)))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))
      - (2*Log(0.98*msu2(2,2)))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) + Log(0.96*
      msd2(2,2))*((-2*Log(1.02*msq2(2,2))*(0.96*msd2(2,2) + 0.98*msu2(2,2) - 0.98*
      Sqr(mAInput)))/((0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(1.02*msq2(2,2) - 0.98*
      msu2(2,2))) + (2*Log(0.98*msu2(2,2))*(0.96*msd2(2,2) + 0.98*msu2(2,2) - 0.98
      *Sqr(mAInput)))/((0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(1.02*msq2(2,2) - 0.98
      *msu2(2,2)))) - (2*Log(1.02*msq2(2,2))*Log(0.98*msu2(2,2))*(1.02*msq2(2,2) +
      0.98*msu2(2,2) - 0.98*Sqr(mAInput)))/((0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr
      (1.02*msq2(2,2) - 0.98*msu2(2,2))) + (2*(1.02*msq2(2,2) + 0.98*msu2(2,2) -
      0.98*Sqr(mAInput))*Sqr(Log(1.02*msq2(2,2))))/((0.96*msd2(2,2) - 1.02*msq2(2,
      2))*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) - (2.0833333333333335*((1.02*msq2(
      2,2) - 0.98*msu2(2,2))*(0.96*msd2(2,2) - 1.02*msq2(2,2) + 0.98*Sqr(mAInput))
      + TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2)))*TPhi(0.98*Sqr(
      mAInput),1.02*msq2(2,2),0.96*msd2(2,2)))/(msd2(2,2)*(0.96*msd2(2,2) - 1.02*
      msq2(2,2))*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) + (1.9607843137254901*(0.98
      *(1.02*msq2(2,2) - 0.98*msu2(2,2))*Sqr(mAInput) + TDelta(0.98*Sqr(mAInput),
      1.02*msq2(2,2),1.02*msq2(2,2)))*TPhi(0.98*Sqr(mAInput),1.02*msq2(2,2),1.02*
      msq2(2,2)))/((0.96*msd2(2,2) - 1.02*msq2(2,2))*msq2(2,2)*Sqr(1.02*msq2(2,2)
      - 0.98*msu2(2,2))) + (2.0833333333333335*TDelta(0.98*Sqr(mAInput),0.98*msu2(
      2,2),0.96*msd2(2,2))*TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),0.96*msd2(2,2)))/
      (msd2(2,2)*(0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(1.02*msq2(2,2) - 0.98*msu2(
      2,2))) - (1.9607843137254901*TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*
      msq2(2,2))*TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2)))/((0.96*
      msd2(2,2) - 1.02*msq2(2,2))*msq2(2,2)*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))))
      + 3*(AbInput - MuInput*TanBeta)*(AtInput + MuInput*TanBeta)*(Log(0.98*Sqr(
      mAInput))*((-2*Log(1.02*msq2(2,2)))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)) + (
      2*Log(0.98*msu2(2,2)))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) + Log(0.96*msd2
      (2,2))*((2*Log(1.02*msq2(2,2))*(0.96*msd2(2,2) + 1.02*msq2(2,2) - 0.98*Sqr(
      mAInput)))/((0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(1.02*msq2(2,2) - 0.98*msu2
      (2,2))) + (2*Log(0.98*msu2(2,2))*(-0.96*msd2(2,2) - 1.02*msq2(2,2) + 0.98*
      Sqr(mAInput)))/((0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(1.02*msq2(2,2) - 0.98*
      msu2(2,2)))) + (2*Log(1.02*msq2(2,2))*Log(0.98*msu2(2,2))*(-2.04*msq2(2,2) +
      0.98*Sqr(mAInput)))/((-0.96*msd2(2,2) + 1.02*msq2(2,2))*Sqr(1.02*msq2(2,2)
      - 0.98*msu2(2,2))) + (2*(-2.04*msq2(2,2) + 0.98*Sqr(mAInput))*Sqr(Log(1.02*
      msq2(2,2))))/((0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(1.02*msq2(2,2) - 0.98*
      msu2(2,2))) + (2.0833333333333335*TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),
      0.96*msd2(2,2))*TPhi(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2)))/(msd2
      (2,2)*(0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))
      ) - (1.9607843137254901*TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),1.02*msq2(2,
      2))*TPhi(0.98*Sqr(mAInput),1.02*msq2(2,2),1.02*msq2(2,2)))/((0.96*msd2(2,2)
      - 1.02*msq2(2,2))*msq2(2,2)*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) + (
      2.0833333333333335*((1.02*msq2(2,2) - 0.98*msu2(2,2))*(0.96*msd2(2,2) - 0.98
      *msu2(2,2) + 0.98*Sqr(mAInput)) - TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),
      0.96*msd2(2,2)))*TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),0.96*msd2(2,2)))/(
      msd2(2,2)*(0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(1.02*msq2(2,2) - 0.98*msu2(2
      ,2))) + (0.9803921568627451*(-2*(1.02*msq2(2,2) - 0.98*msu2(2,2))*(1.02*msq2
      (2,2) - 0.98*msu2(2,2) + 0.98*Sqr(mAInput)) + 2*TDelta(0.98*Sqr(mAInput),
      0.98*msu2(2,2),1.02*msq2(2,2)))*TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*
      msq2(2,2)))/((0.96*msd2(2,2) - 1.02*msq2(2,2))*msq2(2,2)*Sqr(1.02*msq2(2,2)
      - 0.98*msu2(2,2))))) + (AtInput - MuInput/TanBeta)*(3*(AbInput +
      MuInput/TanBeta)*(Log(0.96*msd2(2,2))*((2*Log(1.02*msq2(2,2)))/(1.02*msq2(2,
      2) - 0.98*msu2(2,2)) + (2*Log(0.98*msu2(2,2)))/(-1.02*msq2(2,2) + 0.98*msu2(
      2,2))) + Log(0.98*Sqr(mAInput))*((2*Log(1.02*msq2(2,2)))/(1.02*msq2(2,2) -
      0.98*msu2(2,2)) + (2*Log(0.98*msu2(2,2)))/(-1.02*msq2(2,2) + 0.98*msu2(2,2))
      ) + Log(1.02*msq2(2,2))*(4/(-1.02*msq2(2,2) + 0.98*msu2(2,2)) + (4*Log(Sqr(
      SCALE)))/(-1.02*msq2(2,2) + 0.98*msu2(2,2))) + (4*Log(0.98*msu2(2,2)))/(1.02
      *msq2(2,2) - 0.98*msu2(2,2)) + (4*Log(0.98*msu2(2,2))*Log(Sqr(SCALE)))/(1.02
      *msq2(2,2) - 0.98*msu2(2,2)) + (2.0833333333333335*(0.96*msd2(2,2) - 1.02*
      msq2(2,2) + 0.98*Sqr(mAInput))*TPhi(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*
      msd2(2,2)))/(msd2(2,2)*(-1.02*msq2(2,2) + 0.98*msu2(2,2))) + (
      2.0833333333333335*(0.96*msd2(2,2) - 0.98*msu2(2,2) + 0.98*Sqr(mAInput))*
      TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),0.96*msd2(2,2)))/(msd2(2,2)*(1.02*msq2
      (2,2) - 0.98*msu2(2,2)))) + 3*(AbInput - MuInput*TanBeta)*(Log(0.98*Sqr(
      mAInput))*((2*Log(0.96*msd2(2,2)))/(-0.96*msd2(2,2) + 1.02*msq2(2,2)) + 2*
      Log(1.02*msq2(2,2))*(1/(0.96*msd2(2,2) - 1.02*msq2(2,2)) + 1/(-1.02*msq2(2,2
      ) + 0.98*msu2(2,2))) + (2*Log(0.98*msu2(2,2)))/(1.02*msq2(2,2) - 0.98*msu2(2
      ,2))) + Log(0.96*msd2(2,2))*((2*Log(1.02*msq2(2,2))*(0.96*msd2(2,2) + 1.02*
      msq2(2,2) - 0.98*Sqr(mAInput)))/((0.96*msd2(2,2) - 1.02*msq2(2,2))*(1.02*
      msq2(2,2) - 0.98*msu2(2,2))) - (2*Log(0.98*msu2(2,2))*(0.96*msd2(2,2) + 0.98
      *msu2(2,2) - 0.98*Sqr(mAInput)))/((0.96*msd2(2,2) - 1.02*msq2(2,2))*(1.02*
      msq2(2,2) - 0.98*msu2(2,2)))) + (2*Log(1.02*msq2(2,2))*Log(0.98*msu2(2,2))*(
      1.02*msq2(2,2) + 0.98*msu2(2,2) - 0.98*Sqr(mAInput)))/((0.96*msd2(2,2) -
      1.02*msq2(2,2))*(1.02*msq2(2,2) - 0.98*msu2(2,2))) + (2*(-2.04*msq2(2,2) +
      0.98*Sqr(mAInput))*Sqr(Log(1.02*msq2(2,2))))/((0.96*msd2(2,2) - 1.02*msq2(2,
      2))*(1.02*msq2(2,2) - 0.98*msu2(2,2))) + (2*TDelta(0.98*Sqr(mAInput),1.02*
      msq2(2,2),0.96*msd2(2,2))*TPhi(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,
      2)))/((1.02*msq2(2,2) - 0.98*msu2(2,2))*(-0.9792*msd2(2,2)*msq2(2,2) +
      0.9216*Sqr(msd2(2,2)))) - (1.9607843137254901*TDelta(0.98*Sqr(mAInput),1.02*
      msq2(2,2),1.02*msq2(2,2))*TPhi(0.98*Sqr(mAInput),1.02*msq2(2,2),1.02*msq2(2,
      2)))/((0.96*msd2(2,2) - 1.02*msq2(2,2))*msq2(2,2)*(1.02*msq2(2,2) - 0.98*
      msu2(2,2))) - (2*TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),0.96*msd2(2,2))*
      TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),0.96*msd2(2,2)))/((1.02*msq2(2,2) -
      0.98*msu2(2,2))*(-0.9792*msd2(2,2)*msq2(2,2) + 0.9216*Sqr(msd2(2,2)))) + (
      1.9607843137254901*TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2))*
      TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2)))/((0.96*msd2(2,2) -
      1.02*msq2(2,2))*msq2(2,2)*(1.02*msq2(2,2) - 0.98*msu2(2,2)))) + (AtInput +
      MuInput*TanBeta)*(3*(Log(0.98*Sqr(mAInput))*((2*Log(1.02*msq2(2,2)))/(1.02*
      msq2(2,2) - 0.98*msu2(2,2)) + (2*Log(0.98*msu2(2,2)))/(-1.02*msq2(2,2) +
      0.98*msu2(2,2))) + Log(1.02*msq2(2,2))*(4/(-1.02*msq2(2,2) + 0.98*msu2(2,2))
      + (2*Log(0.98*msu2(2,2)))/(-1.02*msq2(2,2) + 0.98*msu2(2,2)) + (4*Log(Sqr(
      SCALE)))/(-1.02*msq2(2,2) + 0.98*msu2(2,2))) + (4*Log(0.98*msu2(2,2)))/(1.02
      *msq2(2,2) - 0.98*msu2(2,2)) + (4*Log(0.98*msu2(2,2))*Log(Sqr(SCALE)))/(1.02
      *msq2(2,2) - 0.98*msu2(2,2)) + (2*Sqr(Log(1.02*msq2(2,2))))/(1.02*msq2(2,2)
      - 0.98*msu2(2,2)) - (1.96*Sqr(mAInput)*TPhi(0.98*Sqr(mAInput),1.02*msq2(2,2)
      ,1.02*msq2(2,2)))/(-0.9996*msq2(2,2)*msu2(2,2) + 1.0404*Sqr(msq2(2,2))) + (
      1.9607843137254901*(1.02*msq2(2,2) - 0.98*msu2(2,2) + 0.98*Sqr(mAInput))*
      TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2)))/(msq2(2,2)*(1.02*msq2
      (2,2) - 0.98*msu2(2,2)))) + 3*(AbInput + MuInput/TanBeta)*(AbInput - MuInput
      *TanBeta)*(Log(0.96*msd2(2,2))*((2*Log(1.02*msq2(2,2)))/((0.96*msd2(2,2) -
      1.02*msq2(2,2))*(1.02*msq2(2,2) - 0.98*msu2(2,2))) + (2*Log(0.98*msu2(2,2)))
      /((0.96*msd2(2,2) - 1.02*msq2(2,2))*(-1.02*msq2(2,2) + 0.98*msu2(2,2)))) + (
      2*Log(1.02*msq2(2,2))*Log(0.98*msu2(2,2)))/((0.96*msd2(2,2) - 1.02*msq2(2,2)
      )*(1.02*msq2(2,2) - 0.98*msu2(2,2))) + (2*Sqr(Log(1.02*msq2(2,2))))/((0.96*
      msd2(2,2) - 1.02*msq2(2,2))*(-1.02*msq2(2,2) + 0.98*msu2(2,2))) - (2*(0.96*
      msd2(2,2) - 1.02*msq2(2,2) + 0.98*Sqr(mAInput))*TPhi(0.98*Sqr(mAInput),1.02*
      msq2(2,2),0.96*msd2(2,2)))/((1.02*msq2(2,2) - 0.98*msu2(2,2))*(-0.9792*msd2(
      2,2)*msq2(2,2) + 0.9216*Sqr(msd2(2,2)))) + (1.9215686274509802*Sqr(mAInput)*
      TPhi(0.98*Sqr(mAInput),1.02*msq2(2,2),1.02*msq2(2,2)))/((0.96*msd2(2,2) -
      1.02*msq2(2,2))*msq2(2,2)*(1.02*msq2(2,2) - 0.98*msu2(2,2))) + (
      2.0833333333333335*(0.96*msd2(2,2) - 0.98*msu2(2,2) + 0.98*Sqr(mAInput))*
      TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),0.96*msd2(2,2)))/(msd2(2,2)*(0.96*msd2
      (2,2) - 1.02*msq2(2,2))*(1.02*msq2(2,2) - 0.98*msu2(2,2))) + (
      1.9607843137254901*(1.02*msq2(2,2) - 0.98*msu2(2,2) + 0.98*Sqr(mAInput))*
      TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2)))/(msq2(2,2)*(-0.96*
      msd2(2,2) + 1.02*msq2(2,2))*(1.02*msq2(2,2) - 0.98*msu2(2,2)))))) + Cube(
      AtInput - MuInput/TanBeta)*(3*(AbInput + MuInput/TanBeta)*(Log(1.02*msq2(2,2
      ))*((4*Log(Sqr(SCALE))*(1.02*msq2(2,2) + 0.98*msu2(2,2)))/Cube(1.02*msq2(2,2
      ) - 0.98*msu2(2,2)) + (4*(3.06*msq2(2,2) + 0.98*msu2(2,2)))/Cube(1.02*msq2(2
      ,2) - 0.98*msu2(2,2))) - (4*Log(0.98*msu2(2,2))*(1.02*msq2(2,2) + 2.94*msu2(
      2,2)))/Cube(1.02*msq2(2,2) - 0.98*msu2(2,2)) + Log(0.96*msd2(2,2))*((-2*Log(
      1.02*msq2(2,2))*(1.92*msd2(2,2) + 1.02*msq2(2,2) + 0.98*msu2(2,2) - 1.96*Sqr
      (mAInput)))/Cube(1.02*msq2(2,2) - 0.98*msu2(2,2)) + (2*Log(0.98*msu2(2,2))*(
      1.92*msd2(2,2) + 1.02*msq2(2,2) + 0.98*msu2(2,2) - 1.96*Sqr(mAInput)))/Cube(
      1.02*msq2(2,2) - 0.98*msu2(2,2))) + Log(0.98*Sqr(mAInput))*((-2*Log(1.02*
      msq2(2,2))*(-1.92*msd2(2,2) + 1.02*msq2(2,2) + 0.98*msu2(2,2) + 1.96*Sqr(
      mAInput)))/Cube(1.02*msq2(2,2) - 0.98*msu2(2,2)) + (2*Log(0.98*msu2(2,2))*(
      -1.92*msd2(2,2) + 1.02*msq2(2,2) + 0.98*msu2(2,2) + 1.96*Sqr(mAInput)))/Cube
      (1.02*msq2(2,2) - 0.98*msu2(2,2))) + Log(Sqr(SCALE))*((-4*Log(0.98*msu2(2,2)
      )*(1.02*msq2(2,2) + 0.98*msu2(2,2)))/Cube(1.02*msq2(2,2) - 0.98*msu2(2,2)) -
      8/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) - 16/Sqr(1.02*msq2(2,2) - 0.98*msu2
      (2,2)) - (2.0833333333333335*((1.02*msq2(2,2) - 0.98*msu2(2,2))*(0.96*msd2(2
      ,2) - 1.02*msq2(2,2) + 0.98*Sqr(mAInput)) + 2*TDelta(0.98*Sqr(mAInput),1.02*
      msq2(2,2),0.96*msd2(2,2)))*TPhi(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2
      ,2)))/(Cube(1.02*msq2(2,2) - 0.98*msu2(2,2))*msd2(2,2)) + (
      1.0416666666666667*(2*(-1.02*msq2(2,2) + 0.98*msu2(2,2))*(0.96*msd2(2,2) -
      0.98*msu2(2,2) + 0.98*Sqr(mAInput)) + 4*TDelta(0.98*Sqr(mAInput),0.98*msu2(2
      ,2),0.96*msd2(2,2)))*TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),0.96*msd2(2,2)))/
      (Cube(1.02*msq2(2,2) - 0.98*msu2(2,2))*msd2(2,2))) + (AtInput + MuInput*
      TanBeta)*(3*(AbInput + MuInput/TanBeta)*(AbInput - MuInput*TanBeta)*(((4*Log
      (1.02*msq2(2,2)))/Cube(1.02*msq2(2,2) - 0.98*msu2(2,2)) + (4*Log(0.98*msu2(2
      ,2)))/Cube(-1.02*msq2(2,2) + 0.98*msu2(2,2)))*Log(0.98*Sqr(mAInput)) + Log(
      0.96*msd2(2,2))*((-2*Log(1.02*msq2(2,2))*(1.92*msd2(2,2) + 1.02*msq2(2,2) +
      0.98*msu2(2,2) - 1.96*Sqr(mAInput)))/(Cube(1.02*msq2(2,2) - 0.98*msu2(2,2))*
      (0.96*msd2(2,2) - 1.02*msq2(2,2))) + (2*Log(0.98*msu2(2,2))*(1.92*msd2(2,2)
      + 1.02*msq2(2,2) + 0.98*msu2(2,2) - 1.96*Sqr(mAInput)))/(Cube(1.02*msq2(2,2)
      - 0.98*msu2(2,2))*(0.96*msd2(2,2) - 1.02*msq2(2,2)))) - (2*Log(1.02*msq2(2,
      2))*Log(0.98*msu2(2,2))*(3.06*msq2(2,2) + 0.98*msu2(2,2) - 1.96*Sqr(mAInput)
      ))/(Cube(1.02*msq2(2,2) - 0.98*msu2(2,2))*(0.96*msd2(2,2) - 1.02*msq2(2,2)))
      + (2*(3.06*msq2(2,2) + 0.98*msu2(2,2) - 1.96*Sqr(mAInput))*Sqr(Log(1.02*
      msq2(2,2))))/(Cube(1.02*msq2(2,2) - 0.98*msu2(2,2))*(0.96*msd2(2,2) - 1.02*
      msq2(2,2))) - (2.0833333333333335*((1.02*msq2(2,2) - 0.98*msu2(2,2))*(0.96*
      msd2(2,2) - 1.02*msq2(2,2) + 0.98*Sqr(mAInput)) + 2*TDelta(0.98*Sqr(mAInput)
      ,1.02*msq2(2,2),0.96*msd2(2,2)))*TPhi(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*
      msd2(2,2)))/(Cube(1.02*msq2(2,2) - 0.98*msu2(2,2))*msd2(2,2)*(0.96*msd2(2,2)
      - 1.02*msq2(2,2))) + (1.9607843137254901*(0.98*(1.02*msq2(2,2) - 0.98*msu2(
      2,2))*Sqr(mAInput) + 2*TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),1.02*msq2(2,2
      )))*TPhi(0.98*Sqr(mAInput),1.02*msq2(2,2),1.02*msq2(2,2)))/(Cube(1.02*msq2(2
      ,2) - 0.98*msu2(2,2))*(0.96*msd2(2,2) - 1.02*msq2(2,2))*msq2(2,2)) + (
      1.0416666666666667*(2*(-1.02*msq2(2,2) + 0.98*msu2(2,2))*(0.96*msd2(2,2) -
      0.98*msu2(2,2) + 0.98*Sqr(mAInput)) + 4*TDelta(0.98*Sqr(mAInput),0.98*msu2(2
      ,2),0.96*msd2(2,2)))*TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),0.96*msd2(2,2)))/
      (Cube(1.02*msq2(2,2) - 0.98*msu2(2,2))*msd2(2,2)*(0.96*msd2(2,2) - 1.02*msq2
      (2,2))) + (1.9607843137254901*((1.02*msq2(2,2) - 0.98*msu2(2,2))*(1.02*msq2(
      2,2) - 0.98*msu2(2,2) + 0.98*Sqr(mAInput)) - 2*TDelta(0.98*Sqr(mAInput),0.98
      *msu2(2,2),1.02*msq2(2,2)))*TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(
      2,2)))/(Cube(1.02*msq2(2,2) - 0.98*msu2(2,2))*(0.96*msd2(2,2) - 1.02*msq2(2,
      2))*msq2(2,2))) + 3*((-4*Log(0.98*msu2(2,2))*(1.02*msq2(2,2) + 2.94*msu2(2,2
      )))/Cube(1.02*msq2(2,2) - 0.98*msu2(2,2)) + Log(1.02*msq2(2,2))*((4*Log(Sqr(
      SCALE))*(1.02*msq2(2,2) + 0.98*msu2(2,2)))/Cube(1.02*msq2(2,2) - 0.98*msu2(2
      ,2)) + (4*(3.06*msq2(2,2) + 0.98*msu2(2,2)))/Cube(1.02*msq2(2,2) - 0.98*msu2
      (2,2)) + (2*Log(0.98*msu2(2,2))*(3.06*msq2(2,2) + 0.98*msu2(2,2) - 1.96*Sqr(
      mAInput)))/Cube(1.02*msq2(2,2) - 0.98*msu2(2,2))) + Log(0.98*Sqr(mAInput))*(
      (2*Log(1.02*msq2(2,2))*(1.02*msq2(2,2) - 0.98*msu2(2,2) - 1.96*Sqr(mAInput))
      )/Cube(1.02*msq2(2,2) - 0.98*msu2(2,2)) + (2*Log(0.98*msu2(2,2))*(-1.02*msq2
      (2,2) + 0.98*msu2(2,2) + 1.96*Sqr(mAInput)))/Cube(1.02*msq2(2,2) - 0.98*msu2
      (2,2))) - (2*(3.06*msq2(2,2) + 0.98*msu2(2,2) - 1.96*Sqr(mAInput))*Sqr(Log(
      1.02*msq2(2,2))))/Cube(1.02*msq2(2,2) - 0.98*msu2(2,2)) + Log(Sqr(SCALE))*((
      -4*Log(0.98*msu2(2,2))*(1.02*msq2(2,2) + 0.98*msu2(2,2)))/Cube(1.02*msq2(2,2
      ) - 0.98*msu2(2,2)) - 8/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) - 16/Sqr(1.02*
      msq2(2,2) - 0.98*msu2(2,2)) - (1.9607843137254901*(0.98*(1.02*msq2(2,2) -
      0.98*msu2(2,2))*Sqr(mAInput) + 2*TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),
      1.02*msq2(2,2)))*TPhi(0.98*Sqr(mAInput),1.02*msq2(2,2),1.02*msq2(2,2)))/(
      Cube(1.02*msq2(2,2) - 0.98*msu2(2,2))*msq2(2,2)) + (0.9803921568627451*(-2*(
      1.02*msq2(2,2) - 0.98*msu2(2,2))*(1.02*msq2(2,2) - 0.98*msu2(2,2) + 0.98*Sqr
      (mAInput)) + 4*TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2)))*TPhi
      (0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2)))/(Cube(1.02*msq2(2,2) -
      0.98*msu2(2,2))*msq2(2,2))))) + ((1 + Sqr(TanBeta))*(3*(2*Log(0.98*msu2(2,2)
      )*Log(Sqr(SCALE)) - 4*PolyLog(2,1 - (1.0098039215686274*Sqr(MuInput))/msq2(2
      ,2)) - 4*PolyLog(2,1 - (1.0510204081632653*Sqr(MuInput))/msu2(2,2)) + 4.12*
      Log(1.03*Sqr(MuInput))*(1/(1.02*msq2(2,2) - 1.03*Sqr(MuInput)) + 1/(0.98*
      msu2(2,2) - 1.03*Sqr(MuInput)))*Sqr(MuInput) + (4.12*Log(0.98*msu2(2,2))*Sqr
      (MuInput))/(-0.98*msu2(2,2) + 1.03*Sqr(MuInput)) + Log(1.02*msq2(2,2))*(2*
      Log(0.98*msu2(2,2)) + 2*Log(Sqr(SCALE)) + (4.12*Sqr(MuInput))/(-1.02*msq2(2,
      2) + 1.03*Sqr(MuInput))) - 2*Sqr(Log(Sqr(SCALE))) - 2*Sqr(Log(1.02*msq2(2,2)
      )) - 2*Sqr(Log(0.98*msu2(2,2)))) + 3*Sqr(AbInput - MuInput*TanBeta)*(4/(
      -0.96*msd2(2,2) + 1.02*msq2(2,2)) + (2*Log(0.98*msu2(2,2)))/(-0.96*msd2(2,2)
      + 1.02*msq2(2,2)) + (2*Log(Sqr(SCALE)))/(-0.96*msd2(2,2) + 1.02*msq2(2,2))
      + (4.12*Log(1.03*Sqr(MuInput))*Sqr(MuInput))/((0.96*msd2(2,2) - 1.02*msq2(2,
      2))*(-1.02*msq2(2,2) + 1.03*Sqr(MuInput))) + Log(0.96*msd2(2,2))*((3.84*msd2
      (2,2))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (1.92*Log(0.98*msu2(2,2))*msd2
      (2,2))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (1.92*Log(Sqr(SCALE))*msd2(2,2
      ))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))) - (3.84*msd2(2,2)*PolyLog(2,1 - (
      1.0729166666666667*Sqr(MuInput))/msd2(2,2)))/Sqr(0.96*msd2(2,2) - 1.02*msq2(
      2,2)) + (3.84*msd2(2,2)*PolyLog(2,1 - (1.0098039215686274*Sqr(MuInput))/msq2
      (2,2)))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) - (1.92*msd2(2,2)*Sqr(Log(0.96*
      msd2(2,2))))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (1.92*msd2(2,2)*Sqr(Log(
      1.02*msq2(2,2))))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) + Log(1.02*msq2(2,2))
      *((-1.92*Log(0.98*msu2(2,2))*msd2(2,2))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))
      - (1.92*Log(Sqr(SCALE))*msd2(2,2))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (
      4*(0.9888*msd2(2,2)*Sqr(MuInput) - 1.0404*Sqr(msq2(2,2))))/((1.02*msq2(2,2)
      - 1.03*Sqr(MuInput))*Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))))) + Sqr(AtInput -
      MuInput/TanBeta)*(3*Sqr(AbInput - MuInput*TanBeta)*(2/((0.96*msd2(2,2) -
      1.02*msq2(2,2))*(1.02*msq2(2,2) - 0.98*msu2(2,2))) + Log(0.96*msd2(2,2))*((
      1.92*msd2(2,2))/((-1.02*msq2(2,2) + 0.98*msu2(2,2))*Sqr(0.96*msd2(2,2) -
      1.02*msq2(2,2))) + (1.9584*Log(1.02*msq2(2,2))*msd2(2,2)*msq2(2,2))/(Sqr(
      0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) - (
      1.9584*Log(0.98*msu2(2,2))*msd2(2,2)*msq2(2,2))/(Sqr(0.96*msd2(2,2) - 1.02*
      msq2(2,2))*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)))) + Log(1.02*msq2(2,2))*((
      1.9584*Log(0.98*msu2(2,2))*msd2(2,2)*msq2(2,2))/(Sqr(0.96*msd2(2,2) - 1.02*
      msq2(2,2))*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) + (2*(-0.9408*msd2(2,2)*
      msu2(2,2) + 1.0404*Sqr(msq2(2,2))))/(Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))*
      Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)))) + (2.04*Log(0.98*msu2(2,2))*msq2(2,2)
      )/((0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) -
      (1.9584*msd2(2,2)*msq2(2,2)*Sqr(Log(1.02*msq2(2,2))))/(Sqr(0.96*msd2(2,2) -
      1.02*msq2(2,2))*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)))) + 3*(4/(-1.02*msq2(2
      ,2) + 0.98*msu2(2,2)) + (4.12*Log(1.03*Sqr(MuInput))*Sqr(MuInput))/((1.02*
      msq2(2,2) - 0.98*msu2(2,2))*(-0.98*msu2(2,2) + 1.03*Sqr(MuInput))) + Log(Sqr
      (SCALE))*(2/(-1.02*msq2(2,2) + 0.98*msu2(2,2)) - (2.04*Log(0.98*msu2(2,2))*
      msq2(2,2))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) + Log(1.02*msq2(2,2))*((
      -2.04*Log(0.98*msu2(2,2))*msq2(2,2))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)) +
      (2.04*Log(Sqr(SCALE))*msq2(2,2))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)) + (2*(
      1.02*msq2(2,2) + 0.98*msu2(2,2)))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) - (
      4.08*msq2(2,2)*PolyLog(2,1 - (1.0098039215686274*Sqr(MuInput))/msq2(2,2)))
      /Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)) + (4.08*msq2(2,2)*PolyLog(2,1 - (
      1.0510204081632653*Sqr(MuInput))/msu2(2,2)))/Sqr(1.02*msq2(2,2) - 0.98*msu2(
      2,2)) + (2.04*msq2(2,2)*Sqr(Log(0.98*msu2(2,2))))/Sqr(1.02*msq2(2,2) - 0.98*
      msu2(2,2)) + (Log(0.98*msu2(2,2))*(-4.2024*msq2(2,2)*Sqr(MuInput) +
      3.8415999999999997*Sqr(msu2(2,2))))/((-0.98*msu2(2,2) + 1.03*Sqr(MuInput))*
      Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))))) + (3*Sqr(AbInput - MuInput*TanBeta)*
      (4/(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (2*Log(Sqr(SCALE)))/(0.96*msd2(2,2) -
      1.02*msq2(2,2)) + Log(1.02*msq2(2,2))*((1.92*Log(Sqr(SCALE))*msd2(2,2))/Sqr
      (0.96*msd2(2,2) - 1.02*msq2(2,2)) + (2*(0.96*msd2(2,2) + 1.02*msq2(2,2)))
      /Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))) + Log(0.96*msd2(2,2))*((-3.84*msd2(2,
      2))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) - (1.92*Log(Sqr(SCALE))*msd2(2,2))
      /Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (Log(1.02*msq2(2,2))*(0.96*msd2(2,2)
      + 1.02*msq2(2,2) - 0.98*Sqr(mAInput)))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))
      ) + Log(0.98*Sqr(mAInput))*((Log(0.96*msd2(2,2))*(0.96*msd2(2,2) - 1.02*msq2
      (2,2) + 0.98*Sqr(mAInput)))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) - (Log(1.02
      *msq2(2,2))*(0.96*msd2(2,2) - 1.02*msq2(2,2) + 0.98*Sqr(mAInput)))/Sqr(0.96*
      msd2(2,2) - 1.02*msq2(2,2))) - ((0.96*msd2(2,2) + 1.02*msq2(2,2) - 0.98*Sqr(
      mAInput))*Sqr(Log(1.02*msq2(2,2))))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (
      1.0416666666666667*TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2))*
      TPhi(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2)))/(msd2(2,2)*Sqr(0.96*
      msd2(2,2) - 1.02*msq2(2,2))) + (0.9611687812379854*(0.98*(-0.96*msd2(2,2) +
      1.02*msq2(2,2))*(-5.1*msq2(2,2) + 0.98*Sqr(mAInput))*Sqr(mAInput) + (0.96*
      msd2(2,2) - 2.04*msq2(2,2))*TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),1.02*
      msq2(2,2)))*TPhi(0.98*Sqr(mAInput),1.02*msq2(2,2),1.02*msq2(2,2)))/(Sqr(0.96
      *msd2(2,2) - 1.02*msq2(2,2))*Sqr(msq2(2,2)))) + 3*(-2*Log(0.98*msu2(2,2)) +
      Log(0.96*msd2(2,2))*Log(0.98*msu2(2,2)) + (4 - Log(0.96*msd2(2,2)) + Log(
      0.98*msu2(2,2)))*Log(0.98*Sqr(mAInput)) + Log(1.02*msq2(2,2))*(-2 - 2*Log(
      Sqr(SCALE))) - 2*Log(0.98*msu2(2,2))*Log(Sqr(SCALE)) + 2*Sqr(Log(Sqr(SCALE))
      ) + Sqr(Log(1.02*msq2(2,2))) + (0.9611687812379854*(0.9603999999999999*Quad(
      mAInput) - 4.998*msq2(2,2)*Sqr(mAInput) - TDelta(0.98*Sqr(mAInput),1.02*msq2
      (2,2),1.02*msq2(2,2)))*TPhi(0.98*Sqr(mAInput),1.02*msq2(2,2),1.02*msq2(2,2))
      )/Sqr(msq2(2,2)) - (1.0416666666666667*(0.96*msd2(2,2) - 0.98*msu2(2,2) +
      0.98*Sqr(mAInput))*TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),0.96*msd2(2,2)))
      /msd2(2,2)) + 3*(AbInput - MuInput*TanBeta)*(AtInput + MuInput*TanBeta)*((2*
      Log(0.96*msd2(2,2))*Log(0.98*msu2(2,2)))/(0.96*msd2(2,2) - 1.02*msq2(2,2)) +
      (2*Log(1.02*msq2(2,2))*Log(0.98*msu2(2,2)))/(-0.96*msd2(2,2) + 1.02*msq2(2,
      2)) + Log(0.98*Sqr(mAInput))*((2*Log(1.02*msq2(2,2)))/(0.96*msd2(2,2) - 1.02
      *msq2(2,2)) + (2*Log(0.96*msd2(2,2)))/(-0.96*msd2(2,2) + 1.02*msq2(2,2))) -
      (2.0833333333333335*(0.96*msd2(2,2) - 0.98*msu2(2,2) + 0.98*Sqr(mAInput))*
      TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),0.96*msd2(2,2)))/(msd2(2,2)*(0.96*msd2
      (2,2) - 1.02*msq2(2,2))) + (1.9607843137254901*(1.02*msq2(2,2) - 0.98*msu2(2
      ,2) + 0.98*Sqr(mAInput))*TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2
      )))/((0.96*msd2(2,2) - 1.02*msq2(2,2))*msq2(2,2))) + Sqr(AtInput + MuInput*
      TanBeta)*(3*((-2*Log(1.02*msq2(2,2))*(1.02*msq2(2,2) - 0.98*msu2(2,2) + 0.98
      *Sqr(mAInput)))/TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2)) + (
      0.9803921568627451*Log(0.98*Sqr(mAInput))*(Sqr(0.98*Sqr(mAInput) + 1.02*msq2
      (2,2) - 0.98*msu2(2,2)) - TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(
      2,2))))/(msq2(2,2)*TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2)))
      + (0.9803921568627451*Log(0.98*msu2(2,2))*(-0.9603999999999999*Quad(mAInput)
      + 1.9207999999999998*msu2(2,2)*Sqr(mAInput) + 1.0404*Sqr(msq2(2,2)) -
      0.9603999999999999*Sqr(msu2(2,2)) + TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),
      1.02*msq2(2,2))))/(msq2(2,2)*TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*
      msq2(2,2))) + (0.9611687812379854*(-0.98*msu2(2,2) + 0.98*Sqr(mAInput) + ((
      1.02*msq2(2,2) - 0.98*msu2(2,2) + 0.98*Sqr(mAInput))*(0.98*(1.02*msq2(2,2) -
      0.98*msu2(2,2))*msu2(2,2) - 0.9603999999999999*Quad(mAInput) + 0.98*(1.02*
      msq2(2,2) + 1.96*msu2(2,2))*Sqr(mAInput)))/TDelta(0.98*Sqr(mAInput),0.98*
      msu2(2,2),1.02*msq2(2,2)))*TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2
      ,2)))/Sqr(msq2(2,2))) + 3*Sqr(AbInput - MuInput*TanBeta)*((Log(0.96*msd2(2,2
      ))*Log(0.98*msu2(2,2)))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) + Log(1.02*msq2
      (2,2))*(-(Log(0.98*msu2(2,2))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))) + (2*(
      1.02*msq2(2,2) - 0.98*msu2(2,2) + 0.98*Sqr(mAInput)))/((0.96*msd2(2,2) -
      1.02*msq2(2,2))*TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2)))) +
      (0.9803921568627451*Log(0.98*msu2(2,2))*(-0.9603999999999999*Quad(mAInput) +
      1.9207999999999998*msu2(2,2)*Sqr(mAInput) + 1.0404*Sqr(msq2(2,2)) -
      0.9603999999999999*Sqr(msu2(2,2)) + TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),
      1.02*msq2(2,2))))/(msq2(2,2)*(-0.96*msd2(2,2) + 1.02*msq2(2,2))*TDelta(0.98*
      Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2))) + Log(0.98*Sqr(mAInput))*(-(Log
      (0.96*msd2(2,2))/Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))) + Log(1.02*msq2(2,2))
      /Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2)) + (0.9803921568627451*(-Sqr(0.98*Sqr(
      mAInput) + 1.02*msq2(2,2) - 0.98*msu2(2,2)) + TDelta(0.98*Sqr(mAInput),0.98*
      msu2(2,2),1.02*msq2(2,2))))/((0.96*msd2(2,2) - 1.02*msq2(2,2))*msq2(2,2)*
      TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2)))) - (
      1.0416666666666667*(0.96*msd2(2,2) - 0.98*msu2(2,2) + 0.98*Sqr(mAInput))*
      TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),0.96*msd2(2,2)))/(msd2(2,2)*Sqr(0.96*
      msd2(2,2) - 1.02*msq2(2,2))) + (0.9611687812379854*((0.96*msd2(2,2) - 1.02*
      msq2(2,2))*(1.02*msq2(2,2) - 0.98*msu2(2,2) + 0.98*Sqr(mAInput))*(0.98*(
      -1.02*msq2(2,2) + 0.98*msu2(2,2))*msu2(2,2) + 0.9603999999999999*Quad(
      mAInput) - 0.98*(1.02*msq2(2,2) + 1.96*msu2(2,2))*Sqr(mAInput)) + (0.9408*
      msd2(2,2)*msu2(2,2) - 1.9992*msq2(2,2)*msu2(2,2) - 0.9408*msd2(2,2)*Sqr(
      mAInput) + 1.9992*msq2(2,2)*Sqr(mAInput) + 1.0404*Sqr(msq2(2,2)))*TDelta(
      0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2)))*TPhi(0.98*Sqr(mAInput),
      0.98*msu2(2,2),1.02*msq2(2,2)))/(Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(
      msq2(2,2))*TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2))))) + (
      AtInput - MuInput/TanBeta)*(3*(AbInput - MuInput*TanBeta)*(Log(0.98*Sqr(
      mAInput))*((2*Log(0.96*msd2(2,2)))/(-0.96*msd2(2,2) + 1.02*msq2(2,2)) + 2*
      Log(1.02*msq2(2,2))*(1/(0.96*msd2(2,2) - 1.02*msq2(2,2)) + 1/(-1.02*msq2(2,2
      ) + 0.98*msu2(2,2))) + (2*Log(0.98*msu2(2,2)))/(1.02*msq2(2,2) - 0.98*msu2(2
      ,2))) + Log(0.96*msd2(2,2))*((2*Log(1.02*msq2(2,2))*(0.96*msd2(2,2) + 1.02*
      msq2(2,2) - 0.98*Sqr(mAInput)))/((0.96*msd2(2,2) - 1.02*msq2(2,2))*(1.02*
      msq2(2,2) - 0.98*msu2(2,2))) - (2*Log(0.98*msu2(2,2))*(0.96*msd2(2,2) + 0.98
      *msu2(2,2) - 0.98*Sqr(mAInput)))/((0.96*msd2(2,2) - 1.02*msq2(2,2))*(1.02*
      msq2(2,2) - 0.98*msu2(2,2)))) + (2*Log(1.02*msq2(2,2))*Log(0.98*msu2(2,2))*(
      1.02*msq2(2,2) + 0.98*msu2(2,2) - 0.98*Sqr(mAInput)))/((0.96*msd2(2,2) -
      1.02*msq2(2,2))*(1.02*msq2(2,2) - 0.98*msu2(2,2))) + (2*(-2.04*msq2(2,2) +
      0.98*Sqr(mAInput))*Sqr(Log(1.02*msq2(2,2))))/((0.96*msd2(2,2) - 1.02*msq2(2,
      2))*(1.02*msq2(2,2) - 0.98*msu2(2,2))) + (2*TDelta(0.98*Sqr(mAInput),1.02*
      msq2(2,2),0.96*msd2(2,2))*TPhi(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,
      2)))/((1.02*msq2(2,2) - 0.98*msu2(2,2))*(-0.9792*msd2(2,2)*msq2(2,2) +
      0.9216*Sqr(msd2(2,2)))) - (1.9607843137254901*TDelta(0.98*Sqr(mAInput),1.02*
      msq2(2,2),1.02*msq2(2,2))*TPhi(0.98*Sqr(mAInput),1.02*msq2(2,2),1.02*msq2(2,
      2)))/((0.96*msd2(2,2) - 1.02*msq2(2,2))*msq2(2,2)*(1.02*msq2(2,2) - 0.98*
      msu2(2,2))) - (2*TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),0.96*msd2(2,2))*
      TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),0.96*msd2(2,2)))/((1.02*msq2(2,2) -
      0.98*msu2(2,2))*(-0.9792*msd2(2,2)*msq2(2,2) + 0.9216*Sqr(msd2(2,2)))) + (
      1.9607843137254901*TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2))*
      TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2)))/((0.96*msd2(2,2) -
      1.02*msq2(2,2))*msq2(2,2)*(1.02*msq2(2,2) - 0.98*msu2(2,2)))) + (AtInput +
      MuInput*TanBeta)*(3*(Log(0.98*Sqr(mAInput))*((2*Log(0.98*msu2(2,2)))/(1.02*
      msq2(2,2) - 0.98*msu2(2,2)) + (2*Log(1.02*msq2(2,2)))/(-1.02*msq2(2,2) +
      0.98*msu2(2,2))) + (2*Log(1.02*msq2(2,2))*Log(0.98*msu2(2,2)))/(-1.02*msq2(2
      ,2) + 0.98*msu2(2,2)) + (2*Sqr(Log(1.02*msq2(2,2))))/(1.02*msq2(2,2) - 0.98*
      msu2(2,2)) - (1.9223375624759709*(-0.98*(-5.1*msq2(2,2) + 0.98*Sqr(mAInput))
      *Sqr(mAInput) + TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),1.02*msq2(2,2)))*
      TPhi(0.98*Sqr(mAInput),1.02*msq2(2,2),1.02*msq2(2,2)))/((1.02*msq2(2,2) -
      0.98*msu2(2,2))*Sqr(msq2(2,2))) - (1.9223375624759709*(-2.9988*msq2(2,2)*
      msu2(2,2) + 0.9603999999999999*Quad(mAInput) - 2.9988*msq2(2,2)*Sqr(mAInput)
      - 1.9207999999999998*msu2(2,2)*Sqr(mAInput) + 2.0808*Sqr(msq2(2,2)) +
      0.9603999999999999*Sqr(msu2(2,2)) - TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),
      1.02*msq2(2,2)))*TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2)))/((
      1.02*msq2(2,2) - 0.98*msu2(2,2))*Sqr(msq2(2,2)))) + 3*Sqr(AbInput - MuInput*
      TanBeta)*(Log(0.98*Sqr(mAInput))*((-2*Log(0.96*msd2(2,2)))/Sqr(0.96*msd2(2,2
      ) - 1.02*msq2(2,2)) + (2*Log(1.02*msq2(2,2)))/Sqr(0.96*msd2(2,2) - 1.02*msq2
      (2,2))) + Log(0.96*msd2(2,2))*((2*Log(1.02*msq2(2,2))*(0.96*msd2(2,2) + 1.02
      *msq2(2,2) - 0.98*Sqr(mAInput)))/((1.02*msq2(2,2) - 0.98*msu2(2,2))*Sqr(0.96
      *msd2(2,2) - 1.02*msq2(2,2))) - (2*Log(0.98*msu2(2,2))*(0.96*msd2(2,2) +
      0.98*msu2(2,2) - 0.98*Sqr(mAInput)))/((1.02*msq2(2,2) - 0.98*msu2(2,2))*Sqr(
      0.96*msd2(2,2) - 1.02*msq2(2,2)))) + (2*Log(1.02*msq2(2,2))*Log(0.98*msu2(2,
      2))*(0.96*msd2(2,2) + 0.98*msu2(2,2) - 0.98*Sqr(mAInput)))/((1.02*msq2(2,2)
      - 0.98*msu2(2,2))*Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))) + (2*(-0.96*msd2(2,2
      ) - 1.02*msq2(2,2) + 0.98*Sqr(mAInput))*Sqr(Log(1.02*msq2(2,2))))/((1.02*
      msq2(2,2) - 0.98*msu2(2,2))*Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))) + (
      2.0833333333333335*TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2))*
      TPhi(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2)))/(msd2(2,2)*(1.02*msq2
      (2,2) - 0.98*msu2(2,2))*Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))) + (
      1.9223375624759709*(0.98*(-0.96*msd2(2,2) + 1.02*msq2(2,2))*(-5.1*msq2(2,2)
      + 0.98*Sqr(mAInput))*Sqr(mAInput) + (0.96*msd2(2,2) - 2.04*msq2(2,2))*TDelta
      (0.98*Sqr(mAInput),1.02*msq2(2,2),1.02*msq2(2,2)))*TPhi(0.98*Sqr(mAInput),
      1.02*msq2(2,2),1.02*msq2(2,2)))/((1.02*msq2(2,2) - 0.98*msu2(2,2))*Sqr(0.96*
      msd2(2,2) - 1.02*msq2(2,2))*Sqr(msq2(2,2))) - (2.0833333333333335*TDelta(
      0.98*Sqr(mAInput),0.98*msu2(2,2),0.96*msd2(2,2))*TPhi(0.98*Sqr(mAInput),0.98
      *msu2(2,2),0.96*msd2(2,2)))/(msd2(2,2)*(1.02*msq2(2,2) - 0.98*msu2(2,2))*Sqr
      (0.96*msd2(2,2) - 1.02*msq2(2,2))) + (1.9223375624759709*((0.96*msd2(2,2) -
      1.02*msq2(2,2))*(-2.9988*msq2(2,2)*msu2(2,2) + 0.9603999999999999*Quad(
      mAInput) - 2.9988*msq2(2,2)*Sqr(mAInput) - 1.9207999999999998*msu2(2,2)*Sqr(
      mAInput) + 2.0808*Sqr(msq2(2,2)) + 0.9603999999999999*Sqr(msu2(2,2))) - (
      0.96*msd2(2,2) - 2.04*msq2(2,2))*TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),
      1.02*msq2(2,2)))*TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2)))/((
      1.02*msq2(2,2) - 0.98*msu2(2,2))*Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(
      msq2(2,2)))))) + Sqr(AtInput - MuInput/TanBeta)*(3*(4/(1.02*msq2(2,2) - 0.98
      *msu2(2,2)) + Log(Sqr(SCALE))*(2/(1.02*msq2(2,2) - 0.98*msu2(2,2)) + (2.04*
      Log(0.98*msu2(2,2))*msq2(2,2))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) + Log(
      1.02*msq2(2,2))*((-4.08*msq2(2,2))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)) - (
      2.04*Log(Sqr(SCALE))*msq2(2,2))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) + Log(
      0.96*msd2(2,2))*((Log(1.02*msq2(2,2))*(0.96*msd2(2,2) + 1.02*msq2(2,2) -
      0.98*Sqr(mAInput)))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)) - (Log(0.98*msu2(2,
      2))*(0.96*msd2(2,2) + 1.02*msq2(2,2) - 0.98*Sqr(mAInput)))/Sqr(1.02*msq2(2,2
      ) - 0.98*msu2(2,2))) + Log(0.98*Sqr(mAInput))*((Log(1.02*msq2(2,2))*(-0.96*
      msd2(2,2) + 1.02*msq2(2,2) + 0.98*Sqr(mAInput)))/Sqr(1.02*msq2(2,2) - 0.98*
      msu2(2,2)) - (Log(0.98*msu2(2,2))*(-0.96*msd2(2,2) + 1.02*msq2(2,2) + 0.98*
      Sqr(mAInput)))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) + (2*Log(0.98*msu2(2,2)
      )*(1.02*msq2(2,2) + 0.98*msu2(2,2)))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)) +
      (1.0416666666666667*TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2))*
      TPhi(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2)))/(msd2(2,2)*Sqr(1.02*
      msq2(2,2) - 0.98*msu2(2,2))) + (1.0416666666666667*((1.02*msq2(2,2) - 0.98*
      msu2(2,2))*(0.96*msd2(2,2) - 0.98*msu2(2,2) + 0.98*Sqr(mAInput)) - TDelta(
      0.98*Sqr(mAInput),0.98*msu2(2,2),0.96*msd2(2,2)))*TPhi(0.98*Sqr(mAInput),
      0.98*msu2(2,2),0.96*msd2(2,2)))/(msd2(2,2)*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,
      2)))) + 3*(AbInput - MuInput*TanBeta)*(AtInput + MuInput*TanBeta)*(Log(0.98*
      Sqr(mAInput))*((-2*Log(1.02*msq2(2,2)))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))
      + (2*Log(0.98*msu2(2,2)))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) + Log(0.96*
      msd2(2,2))*((2*Log(1.02*msq2(2,2))*(0.96*msd2(2,2) + 1.02*msq2(2,2) - 0.98*
      Sqr(mAInput)))/((0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(1.02*msq2(2,2) - 0.98*
      msu2(2,2))) + (2*Log(0.98*msu2(2,2))*(-0.96*msd2(2,2) - 1.02*msq2(2,2) +
      0.98*Sqr(mAInput)))/((0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(1.02*msq2(2,2) -
      0.98*msu2(2,2)))) + (2*Log(1.02*msq2(2,2))*Log(0.98*msu2(2,2))*(-2.04*msq2(2
      ,2) + 0.98*Sqr(mAInput)))/((-0.96*msd2(2,2) + 1.02*msq2(2,2))*Sqr(1.02*msq2(
      2,2) - 0.98*msu2(2,2))) + (2*(-2.04*msq2(2,2) + 0.98*Sqr(mAInput))*Sqr(Log(
      1.02*msq2(2,2))))/((0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(1.02*msq2(2,2) -
      0.98*msu2(2,2))) + (2.0833333333333335*TDelta(0.98*Sqr(mAInput),1.02*msq2(2,
      2),0.96*msd2(2,2))*TPhi(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2)))/(
      msd2(2,2)*(0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(1.02*msq2(2,2) - 0.98*msu2(2
      ,2))) - (1.9607843137254901*TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),1.02*
      msq2(2,2))*TPhi(0.98*Sqr(mAInput),1.02*msq2(2,2),1.02*msq2(2,2)))/((0.96*
      msd2(2,2) - 1.02*msq2(2,2))*msq2(2,2)*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)))
      + (2.0833333333333335*((1.02*msq2(2,2) - 0.98*msu2(2,2))*(0.96*msd2(2,2) -
      0.98*msu2(2,2) + 0.98*Sqr(mAInput)) - TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2
      ),0.96*msd2(2,2)))*TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),0.96*msd2(2,2)))/(
      msd2(2,2)*(0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(1.02*msq2(2,2) - 0.98*msu2(2
      ,2))) + (0.9803921568627451*(-2*(1.02*msq2(2,2) - 0.98*msu2(2,2))*(1.02*msq2
      (2,2) - 0.98*msu2(2,2) + 0.98*Sqr(mAInput)) + 2*TDelta(0.98*Sqr(mAInput),
      0.98*msu2(2,2),1.02*msq2(2,2)))*TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*
      msq2(2,2)))/((0.96*msd2(2,2) - 1.02*msq2(2,2))*msq2(2,2)*Sqr(1.02*msq2(2,2)
      - 0.98*msu2(2,2)))) + Sqr(AtInput + MuInput*TanBeta)*(3*(Sqr(Log(1.02*msq2(2
      ,2)))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)) + Log(1.02*msq2(2,2))*(-(Log(0.98
      *msu2(2,2))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) + (2*(1.02*msq2(2,2) -
      0.98*msu2(2,2) + 0.98*Sqr(mAInput)))/((1.02*msq2(2,2) - 0.98*msu2(2,2))*
      TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2)))) + (
      0.9803921568627451*Log(0.98*msu2(2,2))*(0.9603999999999999*Quad(mAInput) -
      1.9207999999999998*msu2(2,2)*Sqr(mAInput) - 1.0404*Sqr(msq2(2,2)) +
      0.9603999999999999*Sqr(msu2(2,2)) - TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),
      1.02*msq2(2,2))))/(msq2(2,2)*(1.02*msq2(2,2) - 0.98*msu2(2,2))*TDelta(0.98*
      Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2))) + Log(0.98*Sqr(mAInput))*(-(Log
      (1.02*msq2(2,2))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) + Log(0.98*msu2(2,2))
      /Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)) + (0.9803921568627451*(-Sqr(0.98*Sqr(
      mAInput) + 1.02*msq2(2,2) - 0.98*msu2(2,2)) + TDelta(0.98*Sqr(mAInput),0.98*
      msu2(2,2),1.02*msq2(2,2))))/(msq2(2,2)*(1.02*msq2(2,2) - 0.98*msu2(2,2))*
      TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2)))) + (
      0.9611687812379854*(0.98*(-5.1*msq2(2,2) + 0.98*Sqr(mAInput))*Sqr(mAInput) -
      TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),1.02*msq2(2,2)))*TPhi(0.98*Sqr(
      mAInput),1.02*msq2(2,2),1.02*msq2(2,2)))/(Sqr(msq2(2,2))*Sqr(1.02*msq2(2,2)
      - 0.98*msu2(2,2))) + (0.9611687812379854*((1.02*msq2(2,2) - 0.98*msu2(2,2))*
      (1.02*msq2(2,2) - 0.98*msu2(2,2) + 0.98*Sqr(mAInput))*(0.98*(-1.02*msq2(2,2)
      + 0.98*msu2(2,2))*msu2(2,2) + 0.9603999999999999*Quad(mAInput) - 0.98*(1.02
      *msq2(2,2) + 1.96*msu2(2,2))*Sqr(mAInput)) + TDelta(0.98*Sqr(mAInput),0.98*
      msu2(2,2),1.02*msq2(2,2))*(-0.9603999999999999*Quad(mAInput) + 0.98*(2.04*
      msq2(2,2) + 2.94*msu2(2,2))*Sqr(mAInput) - 2*Sqr(1.02*msq2(2,2) - 0.98*msu2(
      2,2)) + TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2))))*TPhi(0.98*
      Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2)))/(Sqr(msq2(2,2))*Sqr(1.02*msq2(2
      ,2) - 0.98*msu2(2,2))*TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2)
      ))) + 3*Sqr(AbInput - MuInput*TanBeta)*(Log(0.96*msd2(2,2))*((Log(1.02*msq2(
      2,2))*(0.96*msd2(2,2) + 1.02*msq2(2,2) - 0.98*Sqr(mAInput)))/(Sqr(0.96*msd2(
      2,2) - 1.02*msq2(2,2))*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) - (Log(0.98*
      msu2(2,2))*(0.96*msd2(2,2) + 1.02*msq2(2,2) - 0.98*Sqr(mAInput)))/(Sqr(0.96*
      msd2(2,2) - 1.02*msq2(2,2))*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)))) - ((0.96*
      msd2(2,2) + 1.02*msq2(2,2) - 0.98*Sqr(mAInput))*Sqr(Log(1.02*msq2(2,2))))/(
      Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) +
      Log(1.02*msq2(2,2))*((Log(0.98*msu2(2,2))*(0.96*msd2(2,2) + 1.02*msq2(2,2)
      - 0.98*Sqr(mAInput)))/(Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(1.02*msq2(2,
      2) - 0.98*msu2(2,2))) + (2*(1.02*msq2(2,2) - 0.98*msu2(2,2) + 0.98*Sqr(
      mAInput)))/((-0.96*msd2(2,2) + 1.02*msq2(2,2))*(1.02*msq2(2,2) - 0.98*msu2(2
      ,2))*TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2)))) + (
      0.9803921568627451*Log(0.98*msu2(2,2))*(0.9603999999999999*Quad(mAInput) -
      1.9207999999999998*msu2(2,2)*Sqr(mAInput) - 1.0404*Sqr(msq2(2,2)) +
      0.9603999999999999*Sqr(msu2(2,2)) - TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),
      1.02*msq2(2,2))))/(msq2(2,2)*(-0.96*msd2(2,2) + 1.02*msq2(2,2))*(1.02*msq2(2
      ,2) - 0.98*msu2(2,2))*TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2)
      )) + (0.9803921568627451*Log(0.98*Sqr(mAInput))*(-Sqr(0.98*Sqr(mAInput) +
      1.02*msq2(2,2) - 0.98*msu2(2,2)) + TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),
      1.02*msq2(2,2))))/(msq2(2,2)*(-0.96*msd2(2,2) + 1.02*msq2(2,2))*(1.02*msq2(2
      ,2) - 0.98*msu2(2,2))*TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2)
      )) + (1.0416666666666667*TDelta(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2
      ,2))*TPhi(0.98*Sqr(mAInput),1.02*msq2(2,2),0.96*msd2(2,2)))/(msd2(2,2)*Sqr(
      0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) + (
      0.9611687812379854*(0.98*(-0.96*msd2(2,2) + 1.02*msq2(2,2))*(-5.1*msq2(2,2)
      + 0.98*Sqr(mAInput))*Sqr(mAInput) + (0.96*msd2(2,2) - 2.04*msq2(2,2))*TDelta
      (0.98*Sqr(mAInput),1.02*msq2(2,2),1.02*msq2(2,2)))*TPhi(0.98*Sqr(mAInput),
      1.02*msq2(2,2),1.02*msq2(2,2)))/(Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(
      msq2(2,2))*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) + (1.0416666666666667*((
      1.02*msq2(2,2) - 0.98*msu2(2,2))*(0.96*msd2(2,2) - 0.98*msu2(2,2) + 0.98*Sqr
      (mAInput)) - TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),0.96*msd2(2,2)))*TPhi(
      0.98*Sqr(mAInput),0.98*msu2(2,2),0.96*msd2(2,2)))/(msd2(2,2)*Sqr(0.96*msd2(2
      ,2) - 1.02*msq2(2,2))*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) + (
      0.9611687812379854*((0.96*msd2(2,2) - 1.02*msq2(2,2))*(1.02*msq2(2,2) - 0.98
      *msu2(2,2))*(1.02*msq2(2,2) - 0.98*msu2(2,2) + 0.98*Sqr(mAInput))*(0.98*(
      1.02*msq2(2,2) - 0.98*msu2(2,2))*msu2(2,2) - 0.9603999999999999*Quad(mAInput
      ) + 0.98*(1.02*msq2(2,2) + 1.96*msu2(2,2))*Sqr(mAInput)) + TDelta(0.98*Sqr(
      mAInput),0.98*msu2(2,2),1.02*msq2(2,2))*(0.9603999999999999*(0.96*msd2(2,2)
      - 1.02*msq2(2,2))*Quad(mAInput) + 0.98*Sqr(mAInput)*(-1.9584*msd2(2,2)*msq2(
      2,2) - 2.8224*msd2(2,2)*msu2(2,2) + 3.9984*msq2(2,2)*msu2(2,2) + 1.0404*Sqr(
      msq2(2,2))) + (1.92*msd2(2,2) - 3.06*msq2(2,2))*Sqr(1.02*msq2(2,2) - 0.98*
      msu2(2,2)) - (0.96*msd2(2,2) - 2.04*msq2(2,2))*TDelta(0.98*Sqr(mAInput),0.98
      *msu2(2,2),1.02*msq2(2,2))))*TPhi(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2
      (2,2)))/(Sqr(0.96*msd2(2,2) - 1.02*msq2(2,2))*Sqr(msq2(2,2))*Sqr(1.02*msq2(2
      ,2) - 0.98*msu2(2,2))*TDelta(0.98*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2)
      ))))))/(1 + Sqr(TanBeta))))/Sqr(TanBeta)))/Sqr(1 + (0.006332573977646111*(1
      + Sqr(TanBeta))*(0.25*Log(Sqr(MuInput)/Sqr(SCALE)) + (0.125*(-1 + 2*Log(Sqr(
      mAInput)/Sqr(SCALE))))/(1 + Sqr(TanBeta)) + ((-1 + Log(Sqr(mAInput)/Sqr(
      SCALE)))*Sqr(TanBeta))/(1 + Sqr(TanBeta)))*Sqr(Yu(2,2)))/Sqr(TanBeta) + 0.5*
      ((-0.0031662869888230555*Sqr(AbInput - MuInput*TanBeta)*Sqr(Yd(2,2))*TCF(5)(
      Sqrt(Abs(msq2(2,2)/msd2(2,2)))))/Sqrt(Abs(msd2(2,2)*msq2(2,2))) - (
      0.0031662869888230555*Sqr(AtInput - MuInput/TanBeta)*Sqr(Yu(2,2))*TCF(5)(
      Sqrt(Abs(msq2(2,2)/msu2(2,2)))))/Sqrt(Abs(msq2(2,2)*msu2(2,2)))) +
      0.006332573977646111*(1 + Sqr(TanBeta))*Sqr(Yd(2,2))*(0.75*Log(Sqr(MuInput)
      /Sqr(SCALE)) + (0.375*(-1 + 2*Log(Sqr(mAInput)/Sqr(SCALE)))*Sqr(TanBeta))/(1
      + Sqr(TanBeta)) + 0.5*TCF(6)(Sqrt(msd2(2,2))/MuInput) + TCF(6)(Sqrt(msq2(2,
      2))/MuInput)) + 0.008443431970194815*Sqr(g3)*(1 + Log(Sqr(M3Input)/Sqr(SCALE
      )) + TCF(6)(Sqrt(msd2(2,2))/M3Input) + TCF(6)(Sqrt(msq2(2,2))/M3Input) - ((
      AbInput - MuInput*TanBeta)*TCF(9)(Sqrt(msq2(2,2))/M3Input,Sqrt(msd2(2,2))
      /M3Input))/M3Input) + (0.006332573977646111*(1 + Sqr(TanBeta))*Sqr(Yu(2,2))*
      (0.5*TCF(6)(Sqrt(msu2(2,2))/MuInput) + (0.5*(AtInput - MuInput/TanBeta)*
      TanBeta*TCF(9)(Sqrt(msq2(2,2))/MuInput,Sqrt(msu2(2,2))/MuInput))/MuInput))
      /Sqr(TanBeta))))/Quad(3.141592653589793)), 0) + IF(TwoLoopAtAs >= 1, WHICH(
      IsCloseRel(Sqr(SCALE),msq2(2,2),0.01) && IsCloseRel(Sqr(SCALE),msu2(2,2),
      0.01) && IsCloseRel(SCALE,M3Input,0.01), (0.010416666666666666*Quad(Yu(2,2))
      *Sqr(g3)*((-12*(AtInput - MuInput/TanBeta))/SCALE + (14*Cube(AtInput -
      MuInput/TanBeta))/Cube(SCALE) - Power5(AtInput - MuInput/TanBeta)/Power5(
      SCALE) + (0.5*Quad(AtInput - MuInput/TanBeta))/Quad(SCALE) - (6*Sqr(AtInput
      - MuInput/TanBeta))/Sqr(SCALE)))/Quad(3.141592653589793), IsCloseRel(Sqr(
      M3Input),msq2(2,2),0.01) && IsCloseRel(Sqr(M3Input),msu2(2,2),0.01), (
      -0.005208333333333333*Quad(Yu(2,2))*Sqr(g3)*(((AtInput - MuInput/TanBeta)*(
      24 + (12*(AtInput - MuInput/TanBeta))/M3Input - Cube(AtInput -
      MuInput/TanBeta)/Cube(M3Input) + (2*Quad(AtInput - MuInput/TanBeta))/Quad(
      M3Input) - (28*Sqr(AtInput - MuInput/TanBeta))/Sqr(M3Input)))/M3Input - (2*(
      AtInput - MuInput/TanBeta)*Log(Sqr(M3Input)/Sqr(SCALE))*(24 - (24*(AtInput -
      MuInput/TanBeta))/M3Input + Cube(AtInput - MuInput/TanBeta)/Cube(M3Input) -
      (4*Sqr(AtInput - MuInput/TanBeta))/Sqr(M3Input)))/M3Input + 36*Sqr(Log(Sqr(
      M3Input)/Sqr(SCALE)))))/Quad(3.141592653589793), IsCloseRel(Sqr(M3Input),
      msq2(2,2),0.01), (-0.015625*Quad(Yu(2,2))*Sqr(g3)*Sqr(M3Input)*(4 - (32*(
      AtInput - MuInput/TanBeta)*msu2(2,2))/Cube(M3Input) + (24*(AtInput -
      MuInput/TanBeta)*Log(msu2(2,2)/Sqr(M3Input))*msu2(2,2))/Cube(M3Input) - (64*
      Cube(AtInput - MuInput/TanBeta)*msu2(2,2))/Power5(M3Input) - (32*Cube(
      AtInput - MuInput/TanBeta)*Log(msu2(2,2)/Sqr(M3Input))*msu2(2,2))/Power5(
      M3Input) + (16*Cube(msu2(2,2))*Power5(AtInput - MuInput/TanBeta))/Power11(
      M3Input) - (24*Cube(msu2(2,2))*Log(msu2(2,2)/Sqr(M3Input))*Power5(AtInput -
      MuInput/TanBeta))/Power11(M3Input) - (21*Power5(msu2(2,2)))/Power10(M3Input)
      + (17*Log(msu2(2,2)/Sqr(M3Input))*Power5(msu2(2,2)))/Power10(M3Input) - (32
      *(AtInput - MuInput/TanBeta)*Power5(msu2(2,2)))/Power11(M3Input) + (24*(
      AtInput - MuInput/TanBeta)*Log(msu2(2,2)/Sqr(M3Input))*Power5(msu2(2,2)))
      /Power11(M3Input) - (82*Cube(msu2(2,2)))/Power6(M3Input) + (60*Cube(msu2(2,2
      ))*Log(msu2(2,2)/Sqr(M3Input)))/Power6(M3Input) + (3*Power6(msu2(2,2)))
      /Power12(M3Input) - (3*Log(msu2(2,2)/Sqr(M3Input))*Power6(msu2(2,2)))
      /Power12(M3Input) - (192*(AtInput - MuInput/TanBeta)*Cube(msu2(2,2)))/Power7
      (M3Input) + (144*(AtInput - MuInput/TanBeta)*Cube(msu2(2,2))*Log(msu2(2,2)
      /Sqr(M3Input)))/Power7(M3Input) + (16*msu2(2,2)*Power5(AtInput -
      MuInput/TanBeta))/Power7(M3Input) + (8*Log(msu2(2,2)/Sqr(M3Input))*msu2(2,2)
      *Power5(AtInput - MuInput/TanBeta))/Power7(M3Input) - (192*Cube(AtInput -
      MuInput/TanBeta)*Cube(msu2(2,2)))/Power9(M3Input) + (32*Cube(AtInput -
      MuInput/TanBeta)*Cube(msu2(2,2))*Log(msu2(2,2)/Sqr(M3Input)))/Power9(M3Input
      ) + (66*Cube(msu2(2,2))*Quad(AtInput - MuInput/TanBeta))/Power10(M3Input) -
      (47*Cube(msu2(2,2))*Log(msu2(2,2)/Sqr(M3Input))*Quad(AtInput -
      MuInput/TanBeta))/Power10(M3Input) + (14*msu2(2,2)*Quad(AtInput -
      MuInput/TanBeta))/Power6(M3Input) + (19*Log(msu2(2,2)/Sqr(M3Input))*msu2(2,2
      )*Quad(AtInput - MuInput/TanBeta))/Power6(M3Input) + (4*Quad(AtInput -
      MuInput/TanBeta))/Quad(M3Input) + (64*Cube(AtInput - MuInput/TanBeta)*Quad(
      msu2(2,2)))/Power11(M3Input) - (32*Cube(AtInput - MuInput/TanBeta)*Log(msu2(
      2,2)/Sqr(M3Input))*Quad(msu2(2,2)))/Power11(M3Input) + (58*Quad(msu2(2,2)))
      /Power8(M3Input) - (44*Log(msu2(2,2)/Sqr(M3Input))*Quad(msu2(2,2)))/Power8(
      M3Input) + (128*(AtInput - MuInput/TanBeta)*Quad(msu2(2,2)))/Power9(M3Input)
      - (96*(AtInput - MuInput/TanBeta)*Log(msu2(2,2)/Sqr(M3Input))*Quad(msu2(2,2
      )))/Power9(M3Input) - (22*Quad(AtInput - MuInput/TanBeta)*Quad(msu2(2,2)))
      /Power12(M3Input) + (29*Log(msu2(2,2)/Sqr(M3Input))*Quad(AtInput -
      MuInput/TanBeta)*Quad(msu2(2,2)))/Power12(M3Input) - (25*msu2(2,2))/Sqr(
      M3Input) + (11*Log(msu2(2,2)/Sqr(M3Input))*msu2(2,2))/Sqr(M3Input) + (4*Cube
      (-1 + msu2(2,2)/Sqr(M3Input))*msu2(2,2)*PolyLog(2,((-1 + msu2(2,2)/Sqr(
      M3Input))*Sqr(M3Input))/msu2(2,2))*(2 + (8*(AtInput - MuInput/TanBeta))
      /M3Input + (4*Cube(AtInput - MuInput/TanBeta))/Cube(M3Input) + Quad(AtInput
      - MuInput/TanBeta)/Quad(M3Input)))/Sqr(M3Input) - (10*Log(msu2(2,2)/Sqr(
      M3Input))*Power5(msu2(2,2))*Sqr(AtInput - MuInput/TanBeta))/Power12(M3Input)
      + (32*Cube(msu2(2,2))*Sqr(AtInput - MuInput/TanBeta))/Power8(M3Input) - (96
      *Cube(msu2(2,2))*Log(msu2(2,2)/Sqr(M3Input))*Sqr(AtInput - MuInput/TanBeta))
      /Power8(M3Input) + (32*msu2(2,2)*Sqr(AtInput - MuInput/TanBeta))/Quad(
      M3Input) - (22*Log(msu2(2,2)/Sqr(M3Input))*msu2(2,2)*Sqr(AtInput -
      MuInput/TanBeta))/Quad(M3Input) - (8*Quad(msu2(2,2))*Sqr(AtInput -
      MuInput/TanBeta))/Power10(M3Input) + (52*Log(msu2(2,2)/Sqr(M3Input))*Quad(
      msu2(2,2))*Sqr(AtInput - MuInput/TanBeta))/Power10(M3Input) - (8*Sqr(AtInput
      - MuInput/TanBeta))/Sqr(M3Input) - (16*(AtInput - MuInput/TanBeta)*msu2(2,2
      )*Sqr(Log(msu2(2,2)/Sqr(M3Input))))/Cube(M3Input) - (8*Cube(AtInput -
      MuInput/TanBeta)*msu2(2,2)*Sqr(Log(msu2(2,2)/Sqr(M3Input))))/Power5(M3Input)
      + (8*Cube(msu2(2,2))*Power5(AtInput - MuInput/TanBeta)*Sqr(Log(msu2(2,2)
      /Sqr(M3Input))))/Power11(M3Input) - (20*Power5(msu2(2,2))*Sqr(Log(msu2(2,2)
      /Sqr(M3Input))))/Power10(M3Input) - (8*(AtInput - MuInput/TanBeta)*Power5(
      msu2(2,2))*Sqr(Log(msu2(2,2)/Sqr(M3Input))))/Power11(M3Input) - (46*Cube(
      msu2(2,2))*Sqr(Log(msu2(2,2)/Sqr(M3Input))))/Power6(M3Input) + (4*Power6(
      msu2(2,2))*Sqr(Log(msu2(2,2)/Sqr(M3Input))))/Power12(M3Input) - (72*(AtInput
      - MuInput/TanBeta)*Cube(msu2(2,2))*Sqr(Log(msu2(2,2)/Sqr(M3Input))))/Power7
      (M3Input) + (8*Cube(AtInput - MuInput/TanBeta)*Cube(msu2(2,2))*Sqr(Log(msu2(
      2,2)/Sqr(M3Input))))/Power9(M3Input) - (2*Cube(msu2(2,2))*Quad(AtInput -
      MuInput/TanBeta)*Sqr(Log(msu2(2,2)/Sqr(M3Input))))/Power10(M3Input) - (4*
      msu2(2,2)*Quad(AtInput - MuInput/TanBeta)*Sqr(Log(msu2(2,2)/Sqr(M3Input))))
      /Power6(M3Input) - (8*Cube(AtInput - MuInput/TanBeta)*Quad(msu2(2,2))*Sqr(
      Log(msu2(2,2)/Sqr(M3Input))))/Power11(M3Input) + (42*Quad(msu2(2,2))*Sqr(Log
      (msu2(2,2)/Sqr(M3Input))))/Power8(M3Input) + (40*(AtInput - MuInput/TanBeta)
      *Quad(msu2(2,2))*Sqr(Log(msu2(2,2)/Sqr(M3Input))))/Power9(M3Input) - (10*
      Quad(AtInput - MuInput/TanBeta)*Quad(msu2(2,2))*Sqr(Log(msu2(2,2)/Sqr(
      M3Input))))/Power12(M3Input) - (6*msu2(2,2)*Sqr(Log(msu2(2,2)/Sqr(M3Input)))
      )/Sqr(M3Input) + (16*Power5(msu2(2,2))*Sqr(AtInput - MuInput/TanBeta)*Sqr(
      Log(msu2(2,2)/Sqr(M3Input))))/Power12(M3Input) + (68*Cube(msu2(2,2))*Sqr(
      AtInput - MuInput/TanBeta)*Sqr(Log(msu2(2,2)/Sqr(M3Input))))/Power8(M3Input)
      + (4*msu2(2,2)*Sqr(AtInput - MuInput/TanBeta)*Sqr(Log(msu2(2,2)/Sqr(M3Input
      ))))/Quad(M3Input) - (56*Quad(msu2(2,2))*Sqr(AtInput - MuInput/TanBeta)*Sqr(
      Log(msu2(2,2)/Sqr(M3Input))))/Power10(M3Input) + (12*msu2(2,2)*Power5(-1 +
      msu2(2,2)/Sqr(M3Input))*Sqr(Log(Sqr(M3Input)/Sqr(SCALE))))/Sqr(M3Input) + (
      128*(AtInput - MuInput/TanBeta)*Sqr(msu2(2,2)))/Power5(M3Input) - (96*(
      AtInput - MuInput/TanBeta)*Log(msu2(2,2)/Sqr(M3Input))*Sqr(msu2(2,2)))
      /Power5(M3Input) + (192*Cube(AtInput - MuInput/TanBeta)*Sqr(msu2(2,2)))
      /Power7(M3Input) + (32*Cube(AtInput - MuInput/TanBeta)*Log(msu2(2,2)/Sqr(
      M3Input))*Sqr(msu2(2,2)))/Power7(M3Input) - (32*Power5(AtInput -
      MuInput/TanBeta)*Sqr(msu2(2,2)))/Power9(M3Input) + (16*Log(msu2(2,2)/Sqr(
      M3Input))*Power5(AtInput - MuInput/TanBeta)*Sqr(msu2(2,2)))/Power9(M3Input)
      + (63*Sqr(msu2(2,2)))/Quad(M3Input) - (41*Log(msu2(2,2)/Sqr(M3Input))*Sqr(
      msu2(2,2)))/Quad(M3Input) - (62*Quad(AtInput - MuInput/TanBeta)*Sqr(msu2(2,2
      )))/Power8(M3Input) - (Log(msu2(2,2)/Sqr(M3Input))*Quad(AtInput -
      MuInput/TanBeta)*Sqr(msu2(2,2)))/Power8(M3Input) - (48*Sqr(AtInput -
      MuInput/TanBeta)*Sqr(msu2(2,2)))/Power6(M3Input) + (76*Log(msu2(2,2)/Sqr(
      M3Input))*Sqr(AtInput - MuInput/TanBeta)*Sqr(msu2(2,2)))/Power6(M3Input) + (
      56*(AtInput - MuInput/TanBeta)*Sqr(Log(msu2(2,2)/Sqr(M3Input)))*Sqr(msu2(2,2
      )))/Power5(M3Input) + (8*Cube(AtInput - MuInput/TanBeta)*Sqr(Log(msu2(2,2)
      /Sqr(M3Input)))*Sqr(msu2(2,2)))/Power7(M3Input) + (8*Power5(AtInput -
      MuInput/TanBeta)*Sqr(Log(msu2(2,2)/Sqr(M3Input)))*Sqr(msu2(2,2)))/Power9(
      M3Input) + (26*Sqr(Log(msu2(2,2)/Sqr(M3Input)))*Sqr(msu2(2,2)))/Quad(M3Input
      ) + (20*Quad(AtInput - MuInput/TanBeta)*Sqr(Log(msu2(2,2)/Sqr(M3Input)))*Sqr
      (msu2(2,2)))/Power8(M3Input) - (32*Sqr(AtInput - MuInput/TanBeta)*Sqr(Log(
      msu2(2,2)/Sqr(M3Input)))*Sqr(msu2(2,2)))/Power6(M3Input) + 4*Log(Sqr(M3Input
      )/Sqr(SCALE))*(-(Quad(msu2(2,2))/Power8(M3Input)) + (msu2(2,2)*(4 + (8*Cube(
      AtInput - MuInput/TanBeta))/Cube(M3Input) - (6*Quad(AtInput -
      MuInput/TanBeta))/Quad(M3Input) - (6*Sqr(AtInput - MuInput/TanBeta))/Sqr(
      M3Input)))/Sqr(M3Input) - (2*Cube(msu2(2,2))*(-2 + Sqr(AtInput -
      MuInput/TanBeta)/Sqr(M3Input)))/Power6(M3Input) + ((-6 - (8*Cube(AtInput -
      MuInput/TanBeta))/Cube(M3Input) + (7*Quad(AtInput - MuInput/TanBeta))/Quad(
      M3Input) + (6*Sqr(AtInput - MuInput/TanBeta))/Sqr(M3Input))*Sqr(msu2(2,2)))
      /Quad(M3Input) + (Log(msu2(2,2)/Sqr(M3Input))*msu2(2,2)*(-3 - (4*(AtInput -
      MuInput/TanBeta))/M3Input + (4*Cube(AtInput - MuInput/TanBeta))/Cube(M3Input
      ) + (3*Cube(msu2(2,2)))/Power6(M3Input) - (5*Quad(AtInput - MuInput/TanBeta)
      )/Quad(M3Input) + (6*Sqr(AtInput - MuInput/TanBeta))/Sqr(M3Input) + (msu2(2,
      2)*(9 + (8*(AtInput - MuInput/TanBeta))/M3Input + (4*Cube(AtInput -
      MuInput/TanBeta))/Cube(M3Input) - (3*Quad(AtInput - MuInput/TanBeta))/Quad(
      M3Input) - (12*Sqr(AtInput - MuInput/TanBeta))/Sqr(M3Input)))/Sqr(M3Input) +
      ((-9 - (4*(AtInput - MuInput/TanBeta))/M3Input + (6*Sqr(AtInput -
      MuInput/TanBeta))/Sqr(M3Input))*Sqr(msu2(2,2)))/Quad(M3Input)))/Sqr(M3Input)
      - Sqr(-1 + Sqr(AtInput - MuInput/TanBeta)/Sqr(M3Input)))*Sqr(-1 + msu2(2,2)
      /Sqr(M3Input))))/(msu2(2,2)*Power5(-1 + msu2(2,2)/Sqr(M3Input))*Quad(
      3.141592653589793)), IsCloseRel(Sqr(M3Input),msu2(2,2),0.01), (-0.015625*
      Quad(Yu(2,2))*Sqr(g3)*Sqr(M3Input)*(4 - (32*(AtInput - MuInput/TanBeta)*msq2
      (2,2))/Cube(M3Input) + (24*(AtInput - MuInput/TanBeta)*Log(msq2(2,2)/Sqr(
      M3Input))*msq2(2,2))/Cube(M3Input) - (64*Cube(AtInput - MuInput/TanBeta)*
      msq2(2,2))/Power5(M3Input) - (32*Cube(AtInput - MuInput/TanBeta)*Log(msq2(2,
      2)/Sqr(M3Input))*msq2(2,2))/Power5(M3Input) + (16*Cube(msq2(2,2))*Power5(
      AtInput - MuInput/TanBeta))/Power11(M3Input) - (24*Cube(msq2(2,2))*Log(msq2(
      2,2)/Sqr(M3Input))*Power5(AtInput - MuInput/TanBeta))/Power11(M3Input) - (21
      *Power5(msq2(2,2)))/Power10(M3Input) + (17*Log(msq2(2,2)/Sqr(M3Input))*
      Power5(msq2(2,2)))/Power10(M3Input) - (32*(AtInput - MuInput/TanBeta)*Power5
      (msq2(2,2)))/Power11(M3Input) + (24*(AtInput - MuInput/TanBeta)*Log(msq2(2,2
      )/Sqr(M3Input))*Power5(msq2(2,2)))/Power11(M3Input) - (82*Cube(msq2(2,2)))
      /Power6(M3Input) + (60*Cube(msq2(2,2))*Log(msq2(2,2)/Sqr(M3Input)))/Power6(
      M3Input) + (3*Power6(msq2(2,2)))/Power12(M3Input) - (3*Log(msq2(2,2)/Sqr(
      M3Input))*Power6(msq2(2,2)))/Power12(M3Input) - (192*(AtInput -
      MuInput/TanBeta)*Cube(msq2(2,2)))/Power7(M3Input) + (144*(AtInput -
      MuInput/TanBeta)*Cube(msq2(2,2))*Log(msq2(2,2)/Sqr(M3Input)))/Power7(M3Input
      ) + (16*msq2(2,2)*Power5(AtInput - MuInput/TanBeta))/Power7(M3Input) + (8*
      Log(msq2(2,2)/Sqr(M3Input))*msq2(2,2)*Power5(AtInput - MuInput/TanBeta))
      /Power7(M3Input) - (192*Cube(AtInput - MuInput/TanBeta)*Cube(msq2(2,2)))
      /Power9(M3Input) + (32*Cube(AtInput - MuInput/TanBeta)*Cube(msq2(2,2))*Log(
      msq2(2,2)/Sqr(M3Input)))/Power9(M3Input) + (66*Cube(msq2(2,2))*Quad(AtInput
      - MuInput/TanBeta))/Power10(M3Input) - (47*Cube(msq2(2,2))*Log(msq2(2,2)/Sqr
      (M3Input))*Quad(AtInput - MuInput/TanBeta))/Power10(M3Input) + (14*msq2(2,2)
      *Quad(AtInput - MuInput/TanBeta))/Power6(M3Input) + (19*Log(msq2(2,2)/Sqr(
      M3Input))*msq2(2,2)*Quad(AtInput - MuInput/TanBeta))/Power6(M3Input) + (4*
      Quad(AtInput - MuInput/TanBeta))/Quad(M3Input) + (64*Cube(AtInput -
      MuInput/TanBeta)*Quad(msq2(2,2)))/Power11(M3Input) - (32*Cube(AtInput -
      MuInput/TanBeta)*Log(msq2(2,2)/Sqr(M3Input))*Quad(msq2(2,2)))/Power11(
      M3Input) + (58*Quad(msq2(2,2)))/Power8(M3Input) - (44*Log(msq2(2,2)/Sqr(
      M3Input))*Quad(msq2(2,2)))/Power8(M3Input) + (128*(AtInput - MuInput/TanBeta
      )*Quad(msq2(2,2)))/Power9(M3Input) - (96*(AtInput - MuInput/TanBeta)*Log(
      msq2(2,2)/Sqr(M3Input))*Quad(msq2(2,2)))/Power9(M3Input) - (22*Quad(AtInput
      - MuInput/TanBeta)*Quad(msq2(2,2)))/Power12(M3Input) + (29*Log(msq2(2,2)/Sqr
      (M3Input))*Quad(AtInput - MuInput/TanBeta)*Quad(msq2(2,2)))/Power12(M3Input)
      - (25*msq2(2,2))/Sqr(M3Input) + (11*Log(msq2(2,2)/Sqr(M3Input))*msq2(2,2))
      /Sqr(M3Input) + (4*Cube(-1 + msq2(2,2)/Sqr(M3Input))*msq2(2,2)*PolyLog(2,((
      -1 + msq2(2,2)/Sqr(M3Input))*Sqr(M3Input))/msq2(2,2))*(2 + (8*(AtInput -
      MuInput/TanBeta))/M3Input + (4*Cube(AtInput - MuInput/TanBeta))/Cube(M3Input
      ) + Quad(AtInput - MuInput/TanBeta)/Quad(M3Input)))/Sqr(M3Input) - (10*Log(
      msq2(2,2)/Sqr(M3Input))*Power5(msq2(2,2))*Sqr(AtInput - MuInput/TanBeta))
      /Power12(M3Input) + (32*Cube(msq2(2,2))*Sqr(AtInput - MuInput/TanBeta))
      /Power8(M3Input) - (96*Cube(msq2(2,2))*Log(msq2(2,2)/Sqr(M3Input))*Sqr(
      AtInput - MuInput/TanBeta))/Power8(M3Input) + (32*msq2(2,2)*Sqr(AtInput -
      MuInput/TanBeta))/Quad(M3Input) - (22*Log(msq2(2,2)/Sqr(M3Input))*msq2(2,2)*
      Sqr(AtInput - MuInput/TanBeta))/Quad(M3Input) - (8*Quad(msq2(2,2))*Sqr(
      AtInput - MuInput/TanBeta))/Power10(M3Input) + (52*Log(msq2(2,2)/Sqr(M3Input
      ))*Quad(msq2(2,2))*Sqr(AtInput - MuInput/TanBeta))/Power10(M3Input) - (8*Sqr
      (AtInput - MuInput/TanBeta))/Sqr(M3Input) - (16*(AtInput - MuInput/TanBeta)*
      msq2(2,2)*Sqr(Log(msq2(2,2)/Sqr(M3Input))))/Cube(M3Input) - (8*Cube(AtInput
      - MuInput/TanBeta)*msq2(2,2)*Sqr(Log(msq2(2,2)/Sqr(M3Input))))/Power5(
      M3Input) + (8*Cube(msq2(2,2))*Power5(AtInput - MuInput/TanBeta)*Sqr(Log(msq2
      (2,2)/Sqr(M3Input))))/Power11(M3Input) - (20*Power5(msq2(2,2))*Sqr(Log(msq2(
      2,2)/Sqr(M3Input))))/Power10(M3Input) - (8*(AtInput - MuInput/TanBeta)*
      Power5(msq2(2,2))*Sqr(Log(msq2(2,2)/Sqr(M3Input))))/Power11(M3Input) - (46*
      Cube(msq2(2,2))*Sqr(Log(msq2(2,2)/Sqr(M3Input))))/Power6(M3Input) + (4*
      Power6(msq2(2,2))*Sqr(Log(msq2(2,2)/Sqr(M3Input))))/Power12(M3Input) - (72*(
      AtInput - MuInput/TanBeta)*Cube(msq2(2,2))*Sqr(Log(msq2(2,2)/Sqr(M3Input))))
      /Power7(M3Input) + (8*Cube(AtInput - MuInput/TanBeta)*Cube(msq2(2,2))*Sqr(
      Log(msq2(2,2)/Sqr(M3Input))))/Power9(M3Input) - (2*Cube(msq2(2,2))*Quad(
      AtInput - MuInput/TanBeta)*Sqr(Log(msq2(2,2)/Sqr(M3Input))))/Power10(M3Input
      ) - (4*msq2(2,2)*Quad(AtInput - MuInput/TanBeta)*Sqr(Log(msq2(2,2)/Sqr(
      M3Input))))/Power6(M3Input) - (8*Cube(AtInput - MuInput/TanBeta)*Quad(msq2(2
      ,2))*Sqr(Log(msq2(2,2)/Sqr(M3Input))))/Power11(M3Input) + (42*Quad(msq2(2,2)
      )*Sqr(Log(msq2(2,2)/Sqr(M3Input))))/Power8(M3Input) + (40*(AtInput -
      MuInput/TanBeta)*Quad(msq2(2,2))*Sqr(Log(msq2(2,2)/Sqr(M3Input))))/Power9(
      M3Input) - (10*Quad(AtInput - MuInput/TanBeta)*Quad(msq2(2,2))*Sqr(Log(msq2(
      2,2)/Sqr(M3Input))))/Power12(M3Input) - (6*msq2(2,2)*Sqr(Log(msq2(2,2)/Sqr(
      M3Input))))/Sqr(M3Input) + (16*Power5(msq2(2,2))*Sqr(AtInput -
      MuInput/TanBeta)*Sqr(Log(msq2(2,2)/Sqr(M3Input))))/Power12(M3Input) + (68*
      Cube(msq2(2,2))*Sqr(AtInput - MuInput/TanBeta)*Sqr(Log(msq2(2,2)/Sqr(M3Input
      ))))/Power8(M3Input) + (4*msq2(2,2)*Sqr(AtInput - MuInput/TanBeta)*Sqr(Log(
      msq2(2,2)/Sqr(M3Input))))/Quad(M3Input) - (56*Quad(msq2(2,2))*Sqr(AtInput -
      MuInput/TanBeta)*Sqr(Log(msq2(2,2)/Sqr(M3Input))))/Power10(M3Input) + (12*
      msq2(2,2)*Power5(-1 + msq2(2,2)/Sqr(M3Input))*Sqr(Log(Sqr(M3Input)/Sqr(SCALE
      ))))/Sqr(M3Input) + (128*(AtInput - MuInput/TanBeta)*Sqr(msq2(2,2)))/Power5(
      M3Input) - (96*(AtInput - MuInput/TanBeta)*Log(msq2(2,2)/Sqr(M3Input))*Sqr(
      msq2(2,2)))/Power5(M3Input) + (192*Cube(AtInput - MuInput/TanBeta)*Sqr(msq2(
      2,2)))/Power7(M3Input) + (32*Cube(AtInput - MuInput/TanBeta)*Log(msq2(2,2)
      /Sqr(M3Input))*Sqr(msq2(2,2)))/Power7(M3Input) - (32*Power5(AtInput -
      MuInput/TanBeta)*Sqr(msq2(2,2)))/Power9(M3Input) + (16*Log(msq2(2,2)/Sqr(
      M3Input))*Power5(AtInput - MuInput/TanBeta)*Sqr(msq2(2,2)))/Power9(M3Input)
      + (63*Sqr(msq2(2,2)))/Quad(M3Input) - (41*Log(msq2(2,2)/Sqr(M3Input))*Sqr(
      msq2(2,2)))/Quad(M3Input) - (62*Quad(AtInput - MuInput/TanBeta)*Sqr(msq2(2,2
      )))/Power8(M3Input) - (Log(msq2(2,2)/Sqr(M3Input))*Quad(AtInput -
      MuInput/TanBeta)*Sqr(msq2(2,2)))/Power8(M3Input) - (48*Sqr(AtInput -
      MuInput/TanBeta)*Sqr(msq2(2,2)))/Power6(M3Input) + (76*Log(msq2(2,2)/Sqr(
      M3Input))*Sqr(AtInput - MuInput/TanBeta)*Sqr(msq2(2,2)))/Power6(M3Input) + (
      56*(AtInput - MuInput/TanBeta)*Sqr(Log(msq2(2,2)/Sqr(M3Input)))*Sqr(msq2(2,2
      )))/Power5(M3Input) + (8*Cube(AtInput - MuInput/TanBeta)*Sqr(Log(msq2(2,2)
      /Sqr(M3Input)))*Sqr(msq2(2,2)))/Power7(M3Input) + (8*Power5(AtInput -
      MuInput/TanBeta)*Sqr(Log(msq2(2,2)/Sqr(M3Input)))*Sqr(msq2(2,2)))/Power9(
      M3Input) + (26*Sqr(Log(msq2(2,2)/Sqr(M3Input)))*Sqr(msq2(2,2)))/Quad(M3Input
      ) + (20*Quad(AtInput - MuInput/TanBeta)*Sqr(Log(msq2(2,2)/Sqr(M3Input)))*Sqr
      (msq2(2,2)))/Power8(M3Input) - (32*Sqr(AtInput - MuInput/TanBeta)*Sqr(Log(
      msq2(2,2)/Sqr(M3Input)))*Sqr(msq2(2,2)))/Power6(M3Input) + 4*Log(Sqr(M3Input
      )/Sqr(SCALE))*(-(Quad(msq2(2,2))/Power8(M3Input)) + (msq2(2,2)*(4 + (8*Cube(
      AtInput - MuInput/TanBeta))/Cube(M3Input) - (6*Quad(AtInput -
      MuInput/TanBeta))/Quad(M3Input) - (6*Sqr(AtInput - MuInput/TanBeta))/Sqr(
      M3Input)))/Sqr(M3Input) - (2*Cube(msq2(2,2))*(-2 + Sqr(AtInput -
      MuInput/TanBeta)/Sqr(M3Input)))/Power6(M3Input) + ((-6 - (8*Cube(AtInput -
      MuInput/TanBeta))/Cube(M3Input) + (7*Quad(AtInput - MuInput/TanBeta))/Quad(
      M3Input) + (6*Sqr(AtInput - MuInput/TanBeta))/Sqr(M3Input))*Sqr(msq2(2,2)))
      /Quad(M3Input) + (Log(msq2(2,2)/Sqr(M3Input))*msq2(2,2)*(-3 - (4*(AtInput -
      MuInput/TanBeta))/M3Input + (4*Cube(AtInput - MuInput/TanBeta))/Cube(M3Input
      ) + (3*Cube(msq2(2,2)))/Power6(M3Input) - (5*Quad(AtInput - MuInput/TanBeta)
      )/Quad(M3Input) + (6*Sqr(AtInput - MuInput/TanBeta))/Sqr(M3Input) + (msq2(2,
      2)*(9 + (8*(AtInput - MuInput/TanBeta))/M3Input + (4*Cube(AtInput -
      MuInput/TanBeta))/Cube(M3Input) - (3*Quad(AtInput - MuInput/TanBeta))/Quad(
      M3Input) - (12*Sqr(AtInput - MuInput/TanBeta))/Sqr(M3Input)))/Sqr(M3Input) +
      ((-9 - (4*(AtInput - MuInput/TanBeta))/M3Input + (6*Sqr(AtInput -
      MuInput/TanBeta))/Sqr(M3Input))*Sqr(msq2(2,2)))/Quad(M3Input)))/Sqr(M3Input)
      - Sqr(-1 + Sqr(AtInput - MuInput/TanBeta)/Sqr(M3Input)))*Sqr(-1 + msq2(2,2)
      /Sqr(M3Input))))/(msq2(2,2)*Power5(-1 + msq2(2,2)/Sqr(M3Input))*Quad(
      3.141592653589793)), !IsClose(Sqr(M3Input),0) && IsCloseRel(msu2(2,2)/Sqr(
      M3Input),msq2(2,2)/Sqr(M3Input),0.01), (0.005208333333333333*Power6(M3Input)
      *Quad(Yu(2,2))*Sqr(g3)*((32*Cube(AtInput - MuInput/TanBeta)*Log(msu2(2,2)
      /Sqr(M3Input)))/Cube(M3Input) + (32*Cube(AtInput - MuInput/TanBeta)*Log(1 -
      ((-1 + msu2(2,2)/Sqr(M3Input))*Sqr(M3Input))/msu2(2,2)))/Cube(M3Input) + (8*
      Cube(AtInput - MuInput/TanBeta)*msu2(2,2))/Power5(M3Input) - (72*Cube(
      AtInput - MuInput/TanBeta)*Log(msu2(2,2)/Sqr(M3Input))*msu2(2,2))/Power5(
      M3Input) - (8*Cube(AtInput - MuInput/TanBeta)*Log(Sqr(M3Input))*msu2(2,2))
      /Power5(M3Input) - (72*Cube(AtInput - MuInput/TanBeta)*Log(1 - ((-1 + msu2(2
      ,2)/Sqr(M3Input))*Sqr(M3Input))/msu2(2,2))*msu2(2,2))/Power5(M3Input) + (8*
      Cube(AtInput - MuInput/TanBeta)*Log(Sqr(SCALE))*msu2(2,2))/Power5(M3Input) -
      (18*Power5(msu2(2,2)))/Power10(M3Input) + (24*Log(msu2(2,2)/Sqr(M3Input))*
      Power5(msu2(2,2)))/Power10(M3Input) + (24*Log(Sqr(M3Input))*Power5(msu2(2,2)
      ))/Power10(M3Input) - (72*Log(msu2(2,2)/Sqr(M3Input))*Log(Sqr(M3Input))*
      Power5(msu2(2,2)))/Power10(M3Input) - (24*Log(Sqr(SCALE))*Power5(msu2(2,2)))
      /Power10(M3Input) + (72*Log(msu2(2,2)/Sqr(M3Input))*Log(Sqr(SCALE))*Power5(
      msu2(2,2)))/Power10(M3Input) + (72*Log(Sqr(M3Input))*Log(Sqr(SCALE))*Power5(
      msu2(2,2)))/Power10(M3Input) - (78*Cube(msu2(2,2)))/Power6(M3Input) + (84*
      Cube(msu2(2,2))*Log(msu2(2,2)/Sqr(M3Input)))/Power6(M3Input) + (72*Cube(msu2
      (2,2))*Log(Sqr(M3Input)))/Power6(M3Input) - (72*Cube(msu2(2,2))*Log(msu2(2,2
      )/Sqr(M3Input))*Log(Sqr(M3Input)))/Power6(M3Input) - (72*Cube(msu2(2,2))*Log
      (Sqr(SCALE)))/Power6(M3Input) + (72*Cube(msu2(2,2))*Log(msu2(2,2)/Sqr(
      M3Input))*Log(Sqr(SCALE)))/Power6(M3Input) + (72*Cube(msu2(2,2))*Log(Sqr(
      M3Input))*Log(Sqr(SCALE)))/Power6(M3Input) - (48*Cube(msu2(2,2))*PolyLog(2,(
      (-1 + msu2(2,2)/Sqr(M3Input))*Sqr(M3Input))/msu2(2,2)))/Power6(M3Input) + (
      96*(AtInput - MuInput/TanBeta)*Cube(msu2(2,2)))/Power7(M3Input) - (144*(
      AtInput - MuInput/TanBeta)*Cube(msu2(2,2))*Log(msu2(2,2)/Sqr(M3Input)))
      /Power7(M3Input) - (96*(AtInput - MuInput/TanBeta)*Cube(msu2(2,2))*Log(Sqr(
      M3Input)))/Power7(M3Input) + (96*(AtInput - MuInput/TanBeta)*Cube(msu2(2,2))
      *Log(Sqr(SCALE)))/Power7(M3Input) + (96*(AtInput - MuInput/TanBeta)*Cube(
      msu2(2,2))*PolyLog(2,((-1 + msu2(2,2)/Sqr(M3Input))*Sqr(M3Input))/msu2(2,2))
      )/Power7(M3Input) + (4*msu2(2,2)*Power5(AtInput - MuInput/TanBeta))/Power7(
      M3Input) + (4*Log(msu2(2,2)/Sqr(M3Input))*msu2(2,2)*Power5(AtInput -
      MuInput/TanBeta))/Power7(M3Input) + (64*Cube(AtInput - MuInput/TanBeta)*Cube
      (msu2(2,2)))/Power9(M3Input) - (8*Cube(AtInput - MuInput/TanBeta)*Cube(msu2(
      2,2))*Log(msu2(2,2)/Sqr(M3Input)))/Power9(M3Input) - (8*Cube(AtInput -
      MuInput/TanBeta)*Cube(msu2(2,2))*Log(Sqr(M3Input)))/Power9(M3Input) + (8*
      Cube(AtInput - MuInput/TanBeta)*Cube(msu2(2,2))*Log(Sqr(SCALE)))/Power9(
      M3Input) - (Cube(msu2(2,2))*Quad(AtInput - MuInput/TanBeta))/Power10(M3Input
      ) + (6*Cube(msu2(2,2))*Log(msu2(2,2)/Sqr(M3Input))*Quad(AtInput -
      MuInput/TanBeta))/Power10(M3Input) + (6*Cube(msu2(2,2))*Log(Sqr(M3Input))*
      Quad(AtInput - MuInput/TanBeta))/Power10(M3Input) - (6*Cube(msu2(2,2))*Log(
      Sqr(SCALE))*Quad(AtInput - MuInput/TanBeta))/Power10(M3Input) - (13*msu2(2,2
      )*Quad(AtInput - MuInput/TanBeta))/Power6(M3Input) - (12*Log(msu2(2,2)/Sqr(
      M3Input))*msu2(2,2)*Quad(AtInput - MuInput/TanBeta))/Power6(M3Input) + (14*
      Log(Sqr(M3Input))*msu2(2,2)*Quad(AtInput - MuInput/TanBeta))/Power6(M3Input)
      - (18*Log(1 - ((-1 + msu2(2,2)/Sqr(M3Input))*Sqr(M3Input))/msu2(2,2))*msu2(
      2,2)*Quad(AtInput - MuInput/TanBeta))/Power6(M3Input) - (14*Log(Sqr(SCALE))*
      msu2(2,2)*Quad(AtInput - MuInput/TanBeta))/Power6(M3Input) + (4*Quad(AtInput
      - MuInput/TanBeta))/Quad(M3Input) + (8*Log(msu2(2,2)/Sqr(M3Input))*Quad(
      AtInput - MuInput/TanBeta))/Quad(M3Input) - (4*Log(Sqr(M3Input))*Quad(
      AtInput - MuInput/TanBeta))/Quad(M3Input) + (8*Log(1 - ((-1 + msu2(2,2)/Sqr(
      M3Input))*Sqr(M3Input))/msu2(2,2))*Quad(AtInput - MuInput/TanBeta))/Quad(
      M3Input) + (4*Log(Sqr(SCALE))*Quad(AtInput - MuInput/TanBeta))/Quad(M3Input)
      + (72*Quad(msu2(2,2)))/Power8(M3Input) - (72*Log(msu2(2,2)/Sqr(M3Input))*
      Quad(msu2(2,2)))/Power8(M3Input) - (72*Log(Sqr(M3Input))*Quad(msu2(2,2)))
      /Power8(M3Input) + (144*Log(msu2(2,2)/Sqr(M3Input))*Log(Sqr(M3Input))*Quad(
      msu2(2,2)))/Power8(M3Input) + (72*Log(Sqr(SCALE))*Quad(msu2(2,2)))/Power8(
      M3Input) - (144*Log(msu2(2,2)/Sqr(M3Input))*Log(Sqr(SCALE))*Quad(msu2(2,2)))
      /Power8(M3Input) - (144*Log(Sqr(M3Input))*Log(Sqr(SCALE))*Quad(msu2(2,2)))
      /Power8(M3Input) - (48*(AtInput - MuInput/TanBeta)*Quad(msu2(2,2)))/Power9(
      M3Input) + (48*(AtInput - MuInput/TanBeta)*Log(msu2(2,2)/Sqr(M3Input))*Quad(
      msu2(2,2)))/Power9(M3Input) + (48*(AtInput - MuInput/TanBeta)*Log(Sqr(
      M3Input))*Quad(msu2(2,2)))/Power9(M3Input) - (48*(AtInput - MuInput/TanBeta)
      *Log(Sqr(SCALE))*Quad(msu2(2,2)))/Power9(M3Input) - (96*Cube(msu2(2,2))*Sqr(
      AtInput - MuInput/TanBeta))/Power8(M3Input) + (168*Cube(msu2(2,2))*Log(msu2(
      2,2)/Sqr(M3Input))*Sqr(AtInput - MuInput/TanBeta))/Power8(M3Input) + (168*
      Cube(msu2(2,2))*Log(Sqr(M3Input))*Sqr(AtInput - MuInput/TanBeta))/Power8(
      M3Input) - (168*Cube(msu2(2,2))*Log(Sqr(SCALE))*Sqr(AtInput -
      MuInput/TanBeta))/Power8(M3Input) - (24*msu2(2,2)*Sqr(AtInput -
      MuInput/TanBeta))/Quad(M3Input) + (24*Log(Sqr(M3Input))*msu2(2,2)*Sqr(
      AtInput - MuInput/TanBeta))/Quad(M3Input) - (24*Log(Sqr(SCALE))*msu2(2,2)*
      Sqr(AtInput - MuInput/TanBeta))/Quad(M3Input) + (12*Quad(msu2(2,2))*Sqr(
      AtInput - MuInput/TanBeta))/Power10(M3Input) - (72*Log(msu2(2,2)/Sqr(M3Input
      ))*Quad(msu2(2,2))*Sqr(AtInput - MuInput/TanBeta))/Power10(M3Input) - (72*
      Log(Sqr(M3Input))*Quad(msu2(2,2))*Sqr(AtInput - MuInput/TanBeta))/Power10(
      M3Input) + (72*Log(Sqr(SCALE))*Quad(msu2(2,2))*Sqr(AtInput - MuInput/TanBeta
      ))/Power10(M3Input) - (36*Power5(msu2(2,2))*Sqr(Log(Sqr(M3Input))))/Power10(
      M3Input) - (36*Cube(msu2(2,2))*Sqr(Log(Sqr(M3Input))))/Power6(M3Input) + (72
      *Quad(msu2(2,2))*Sqr(Log(Sqr(M3Input))))/Power8(M3Input) - (36*Power5(msu2(2
      ,2))*Sqr(Log(Sqr(SCALE))))/Power10(M3Input) - (36*Cube(msu2(2,2))*Sqr(Log(
      Sqr(SCALE))))/Power6(M3Input) + (72*Quad(msu2(2,2))*Sqr(Log(Sqr(SCALE))))
      /Power8(M3Input) - (36*Power5(msu2(2,2))*Sqr(Log(msu2(2,2)/Sqr(M3Input))))
      /Power10(M3Input) - (36*Cube(msu2(2,2))*Sqr(Log(msu2(2,2)/Sqr(M3Input))))
      /Power6(M3Input) + (72*Quad(msu2(2,2))*Sqr(Log(msu2(2,2)/Sqr(M3Input))))
      /Power8(M3Input) - (48*(AtInput - MuInput/TanBeta)*Sqr(msu2(2,2)))/Power5(
      M3Input) + (96*(AtInput - MuInput/TanBeta)*Log(msu2(2,2)/Sqr(M3Input))*Sqr(
      msu2(2,2)))/Power5(M3Input) + (48*(AtInput - MuInput/TanBeta)*Log(Sqr(
      M3Input))*Sqr(msu2(2,2)))/Power5(M3Input) + (96*(AtInput - MuInput/TanBeta)*
      Log(1 - ((-1 + msu2(2,2)/Sqr(M3Input))*Sqr(M3Input))/msu2(2,2))*Sqr(msu2(2,2
      )))/Power5(M3Input) - (48*(AtInput - MuInput/TanBeta)*Log(Sqr(SCALE))*Sqr(
      msu2(2,2)))/Power5(M3Input) - (72*Cube(AtInput - MuInput/TanBeta)*Sqr(msu2(2
      ,2)))/Power7(M3Input) + (16*Cube(AtInput - MuInput/TanBeta)*Log(Sqr(M3Input)
      )*Sqr(msu2(2,2)))/Power7(M3Input) + (48*Cube(AtInput - MuInput/TanBeta)*Log(
      1 - ((-1 + msu2(2,2)/Sqr(M3Input))*Sqr(M3Input))/msu2(2,2))*Sqr(msu2(2,2)))
      /Power7(M3Input) - (16*Cube(AtInput - MuInput/TanBeta)*Log(Sqr(SCALE))*Sqr(
      msu2(2,2)))/Power7(M3Input) - (4*Power5(AtInput - MuInput/TanBeta)*Sqr(msu2(
      2,2)))/Power9(M3Input) + (24*Sqr(msu2(2,2)))/Quad(M3Input) - (24*Log(Sqr(
      M3Input))*Sqr(msu2(2,2)))/Quad(M3Input) + (24*Log(Sqr(SCALE))*Sqr(msu2(2,2))
      )/Quad(M3Input) + (10*Quad(AtInput - MuInput/TanBeta)*Sqr(msu2(2,2)))/Power8
      (M3Input) - (4*Log(msu2(2,2)/Sqr(M3Input))*Quad(AtInput - MuInput/TanBeta)*
      Sqr(msu2(2,2)))/Power8(M3Input) - (16*Log(Sqr(M3Input))*Quad(AtInput -
      MuInput/TanBeta)*Sqr(msu2(2,2)))/Power8(M3Input) + (12*Log(1 - ((-1 + msu2(2
      ,2)/Sqr(M3Input))*Sqr(M3Input))/msu2(2,2))*Quad(AtInput - MuInput/TanBeta)*
      Sqr(msu2(2,2)))/Power8(M3Input) + (16*Log(Sqr(SCALE))*Quad(AtInput -
      MuInput/TanBeta)*Sqr(msu2(2,2)))/Power8(M3Input) + (108*Sqr(AtInput -
      MuInput/TanBeta)*Sqr(msu2(2,2)))/Power6(M3Input) - (48*Log(msu2(2,2)/Sqr(
      M3Input))*Sqr(AtInput - MuInput/TanBeta)*Sqr(msu2(2,2)))/Power6(M3Input) - (
      120*Log(Sqr(M3Input))*Sqr(AtInput - MuInput/TanBeta)*Sqr(msu2(2,2)))/Power6(
      M3Input) + (120*Log(Sqr(SCALE))*Sqr(AtInput - MuInput/TanBeta)*Sqr(msu2(2,2)
      ))/Power6(M3Input)))/(Cube(msu2(2,2))*Quad(3.141592653589793)*Sqr(-1 + msu2(
      2,2)/Sqr(M3Input))), True, (0.015625*Quad(Yu(2,2))*Sqr(g3)*(Log(Sqr(M3Input)
      /Sqr(SCALE))*(8 - 12*Log((0.9930129810249694*msq2(2,2))/Sqr(M3Input)) - 12*
      Log((1.01007550314386*msu2(2,2))/Sqr(M3Input)) - (4.028144723618089*Sqr(
      M3Input))/msq2(2,2) - (3.9601*Sqr(M3Input))/msu2(2,2)) + ((AtInput -
      MuInput/TanBeta)*(Log(Sqr(M3Input)/Sqr(SCALE))*((16*Log((0.9930129810249694*
      msq2(2,2))/Sqr(M3Input)))/((0.9930129810249694*msq2(2,2))/Sqr(M3Input) - (
      1.01007550314386*msu2(2,2))/Sqr(M3Input)) - (16*Log((1.01007550314386*msu2(2
      ,2))/Sqr(M3Input)))/((0.9930129810249694*msq2(2,2))/Sqr(M3Input) - (
      1.01007550314386*msu2(2,2))/Sqr(M3Input))) + Log((0.9930129810249694*msq2(2,
      2))/Sqr(M3Input))*(-16/((0.9930129810249694*msq2(2,2))/Sqr(M3Input) - (
      1.01007550314386*msu2(2,2))/Sqr(M3Input)) - (8*Log((1.01007550314386*msu2(2,
      2))/Sqr(M3Input)))/((-1 + (0.9930129810249694*msq2(2,2))/Sqr(M3Input))*(-1 +
      (1.01007550314386*msu2(2,2))/Sqr(M3Input)))) + (16*Log((1.01007550314386*
      msu2(2,2))/Sqr(M3Input)))/((0.9930129810249694*msq2(2,2))/Sqr(M3Input) - (
      1.01007550314386*msu2(2,2))/Sqr(M3Input)) + (32*(PolyLog(2,(0.990025*(-1 + (
      1.01007550314386*msu2(2,2))/Sqr(M3Input))*Sqr(M3Input))/msu2(2,2))*(-1 + (
      0.9930129810249694*msq2(2,2))/Sqr(M3Input)) - PolyLog(2,(1.0070361809045223*
      (-1 + (0.9930129810249694*msq2(2,2))/Sqr(M3Input))*Sqr(M3Input))/msq2(2,2))*
      (-1 + (1.01007550314386*msu2(2,2))/Sqr(M3Input))))/((-1 + (
      0.9930129810249694*msq2(2,2))/Sqr(M3Input))*((0.9930129810249694*msq2(2,2))
      /Sqr(M3Input) - (1.01007550314386*msu2(2,2))/Sqr(M3Input))*(-1 + (
      1.01007550314386*msu2(2,2))/Sqr(M3Input))) + (8*(-2 + (0.9930129810249694*
      msq2(2,2))/Sqr(M3Input))*Sqr(Log((0.9930129810249694*msq2(2,2))/Sqr(M3Input)
      )))/((-1 + (0.9930129810249694*msq2(2,2))/Sqr(M3Input))*((0.9930129810249694
      *msq2(2,2))/Sqr(M3Input) - (1.01007550314386*msu2(2,2))/Sqr(M3Input))) - (8*
      (-2 + (1.01007550314386*msu2(2,2))/Sqr(M3Input))*Sqr(Log((1.01007550314386*
      msu2(2,2))/Sqr(M3Input))))/(((0.9930129810249694*msq2(2,2))/Sqr(M3Input) - (
      1.01007550314386*msu2(2,2))/Sqr(M3Input))*(-1 + (1.01007550314386*msu2(2,2))
      /Sqr(M3Input)))))/M3Input + (Power5(AtInput - MuInput/TanBeta)*(Log((
      0.9930129810249694*msq2(2,2))/Sqr(M3Input))*((8*Log((1.01007550314386*msu2(2
      ,2))/Sqr(M3Input))*((0.9930129810249694*msq2(2,2))/Sqr(M3Input) + (
      1.01007550314386*msu2(2,2))/Sqr(M3Input))*((-1.01007550314386*msu2(2,2))/Sqr
      (M3Input) + (0.9930129810249694*msq2(2,2)*(-1 + (2.02015100628772*msu2(2,2))
      /Sqr(M3Input)))/Sqr(M3Input)))/(Quad((0.9930129810249694*msq2(2,2))/Sqr(
      M3Input) - (1.01007550314386*msu2(2,2))/Sqr(M3Input))*(-1 + (
      0.9930129810249694*msq2(2,2))/Sqr(M3Input))*(-1 + (1.01007550314386*msu2(2,2
      ))/Sqr(M3Input))) + (15.88820769639951*msq2(2,2))/(Cube((0.9930129810249694*
      msq2(2,2))/Sqr(M3Input) - (1.01007550314386*msu2(2,2))/Sqr(M3Input))*(-1 + (
      0.9930129810249694*msq2(2,2))/Sqr(M3Input))*Sqr(M3Input))) + (
      16.16120805030176*Log((1.01007550314386*msu2(2,2))/Sqr(M3Input))*msu2(2,2))/
      (Cube((-0.9930129810249694*msq2(2,2))/Sqr(M3Input) + (1.01007550314386*msu2(
      2,2))/Sqr(M3Input))*(-1 + (1.01007550314386*msu2(2,2))/Sqr(M3Input))*Sqr(
      M3Input)) - (7.944103848199755*msq2(2,2)*((0.9930129810249694*msq2(2,2))/Sqr
      (M3Input) + (1.01007550314386*msu2(2,2))/Sqr(M3Input))*Sqr(Log((
      0.9930129810249694*msq2(2,2))/Sqr(M3Input))))/(Quad((0.9930129810249694*msq2
      (2,2))/Sqr(M3Input) - (1.01007550314386*msu2(2,2))/Sqr(M3Input))*(-1 + (
      0.9930129810249694*msq2(2,2))/Sqr(M3Input))*Sqr(M3Input)) - (
      8.08060402515088*msu2(2,2)*((0.9930129810249694*msq2(2,2))/Sqr(M3Input) + (
      1.01007550314386*msu2(2,2))/Sqr(M3Input))*Sqr(Log((1.01007550314386*msu2(2,2
      ))/Sqr(M3Input))))/(Quad((0.9930129810249694*msq2(2,2))/Sqr(M3Input) - (
      1.01007550314386*msu2(2,2))/Sqr(M3Input))*(-1 + (1.01007550314386*msu2(2,2))
      /Sqr(M3Input))*Sqr(M3Input))))/Power5(M3Input) - 12*Sqr(Log(Sqr(M3Input)/Sqr
      (SCALE))) + (Sqr(Log((0.9930129810249694*msq2(2,2))/Sqr(M3Input)))*(-6 + (
      7.944103848199755*msq2(2,2))/Sqr(M3Input) - (3.9442991219363845*Sqr(msq2(2,2
      )))/Quad(M3Input)))/Sqr(-1 + (0.9930129810249694*msq2(2,2))/Sqr(M3Input)) +
      (Cube(AtInput - MuInput/TanBeta)*((-16*(4*((0.9930129810249694*msq2(2,2))
      /Sqr(M3Input) - (1.01007550314386*msu2(2,2))/Sqr(M3Input)) + PolyLog(2,(
      1.0070361809045223*(-1 + (0.9930129810249694*msq2(2,2))/Sqr(M3Input))*Sqr(
      M3Input))/msq2(2,2))*(-2 + (0.9930129810249694*msq2(2,2))/Sqr(M3Input) + (
      1.01007550314386*msu2(2,2))/Sqr(M3Input)) - PolyLog(2,(0.990025*(-1 + (
      1.01007550314386*msu2(2,2))/Sqr(M3Input))*Sqr(M3Input))/msu2(2,2))*(-2 + (
      0.9930129810249694*msq2(2,2))/Sqr(M3Input) + (1.01007550314386*msu2(2,2))
      /Sqr(M3Input))))/Cube((0.9930129810249694*msq2(2,2))/Sqr(M3Input) - (
      1.01007550314386*msu2(2,2))/Sqr(M3Input)) - (16*Log((1.01007550314386*msu2(2
      ,2))/Sqr(M3Input))*((0.9930129810249694*msq2(2,2))/Sqr(M3Input) + (
      3.03022650943158*msu2(2,2))/Sqr(M3Input)))/Cube((0.9930129810249694*msq2(2,2
      ))/Sqr(M3Input) - (1.01007550314386*msu2(2,2))/Sqr(M3Input)) + (8*Sqr(Log((
      0.9930129810249694*msq2(2,2))/Sqr(M3Input)))*(-2 + (1.01007550314386*msu2(2,
      2))/Sqr(M3Input) - (2.979038943074908*msq2(2,2)*(-1 + (1.01007550314386*msu2
      (2,2))/Sqr(M3Input)))/Sqr(M3Input) + (0.9860747804840961*Sqr(msq2(2,2)))
      /Quad(M3Input)))/(Cube((0.9930129810249694*msq2(2,2))/Sqr(M3Input) - (
      1.01007550314386*msu2(2,2))/Sqr(M3Input))*(-1 + (0.9930129810249694*msq2(2,2
      ))/Sqr(M3Input))) + (8*Sqr(Log((1.01007550314386*msu2(2,2))/Sqr(M3Input)))*(
      -2 - (3.0090542593115406*msq2(2,2)*msu2(2,2))/Quad(M3Input) + (
      0.9930129810249694*msq2(2,2))/Sqr(M3Input) + (3.03022650943158*msu2(2,2))
      /Sqr(M3Input) + (1.0202525220513219*Sqr(msu2(2,2)))/Quad(M3Input)))/(Cube((
      -0.9930129810249694*msq2(2,2))/Sqr(M3Input) + (1.01007550314386*msu2(2,2))
      /Sqr(M3Input))*(-1 + (1.01007550314386*msu2(2,2))/Sqr(M3Input))) + Log(Sqr(
      M3Input)/Sqr(SCALE))*((-16*Log((0.9930129810249694*msq2(2,2))/Sqr(M3Input))*
      ((0.9930129810249694*msq2(2,2))/Sqr(M3Input) + (1.01007550314386*msu2(2,2))
      /Sqr(M3Input)))/Cube((0.9930129810249694*msq2(2,2))/Sqr(M3Input) - (
      1.01007550314386*msu2(2,2))/Sqr(M3Input)) + (16*Log((1.01007550314386*msu2(2
      ,2))/Sqr(M3Input))*((0.9930129810249694*msq2(2,2))/Sqr(M3Input) + (
      1.01007550314386*msu2(2,2))/Sqr(M3Input)))/Cube((0.9930129810249694*msq2(2,2
      ))/Sqr(M3Input) - (1.01007550314386*msu2(2,2))/Sqr(M3Input)) + 32/Sqr((
      0.9930129810249694*msq2(2,2))/Sqr(M3Input) - (1.01007550314386*msu2(2,2))
      /Sqr(M3Input))) + Log((0.9930129810249694*msq2(2,2))/Sqr(M3Input))*((16*((
      2.979038943074908*msq2(2,2))/Sqr(M3Input) + (1.01007550314386*msu2(2,2))/Sqr
      (M3Input)))/Cube((0.9930129810249694*msq2(2,2))/Sqr(M3Input) - (
      1.01007550314386*msu2(2,2))/Sqr(M3Input)) + (16*Log((1.01007550314386*msu2(2
      ,2))/Sqr(M3Input))*((-2.0060361728743605*msq2(2,2)*msu2(2,2))/Quad(M3Input)
      + (0.9930129810249694*msq2(2,2))/Sqr(M3Input) + (1.01007550314386*msu2(2,2))
      /Sqr(M3Input)))/((-1 + (0.9930129810249694*msq2(2,2))/Sqr(M3Input))*(-1 + (
      1.01007550314386*msu2(2,2))/Sqr(M3Input))*Sqr((0.9930129810249694*msq2(2,2))
      /Sqr(M3Input) - (1.01007550314386*msu2(2,2))/Sqr(M3Input))))))/Cube(M3Input)
      + Log((0.9930129810249694*msq2(2,2))/Sqr(M3Input))*((2*(-7 + (
      6.06045301886316*msu2(2,2))/Sqr(M3Input) + (0.9930129810249694*msq2(2,2)*(7
      - (5.050377515719299*msu2(2,2))/Sqr(M3Input)))/Sqr(M3Input) + (
      0.9860747804840961*(-3 + (2.02015100628772*msu2(2,2))/Sqr(M3Input))*Sqr(msq2
      (2,2)))/Quad(M3Input)))/((-1 + (1.01007550314386*msu2(2,2))/Sqr(M3Input))*
      Sqr(-1 + (0.9930129810249694*msq2(2,2))/Sqr(M3Input))) - (2*Log((
      1.01007550314386*msu2(2,2))/Sqr(M3Input))*((1.01007550314386*msu2(2,2)*(-2 +
      (1.01007550314386*msu2(2,2))/Sqr(M3Input)))/Sqr(M3Input) + (
      0.9930129810249694*msq2(2,2)*(-2 + (8.08060402515088*msu2(2,2))/Sqr(M3Input)
      - (4.0810100882052875*Sqr(msu2(2,2)))/Quad(M3Input)))/Sqr(M3Input) + (
      0.9860747804840961*Sqr(msq2(2,2))*(1 - (4.04030201257544*msu2(2,2))/Sqr(
      M3Input) + (2.0405050441026438*Sqr(msu2(2,2)))/Quad(M3Input)))/Quad(M3Input)
      ))/(Sqr(-1 + (0.9930129810249694*msq2(2,2))/Sqr(M3Input))*Sqr(-1 + (
      1.01007550314386*msu2(2,2))/Sqr(M3Input)))) + (Sqr(AtInput - MuInput/TanBeta
      )*((-7.975927959999997*Quad(M3Input))/(msq2(2,2)*msu2(2,2)) + Log(Sqr(
      M3Input)/Sqr(SCALE))*((7.975927959999997*Quad(M3Input))/(msq2(2,2)*msu2(2,2)
      ) - (24*Log((0.9930129810249694*msq2(2,2))/Sqr(M3Input)))/((
      0.9930129810249694*msq2(2,2))/Sqr(M3Input) - (1.01007550314386*msu2(2,2))
      /Sqr(M3Input)) + (24*Log((1.01007550314386*msu2(2,2))/Sqr(M3Input)))/((
      0.9930129810249694*msq2(2,2))/Sqr(M3Input) - (1.01007550314386*msu2(2,2))
      /Sqr(M3Input))) - (4*Log((1.01007550314386*msu2(2,2))/Sqr(M3Input))*(7 - (
      4.04030201257544*msu2(2,2))/Sqr(M3Input) + (2.979038943074908*msq2(2,2)*(-2
      + (1.01007550314386*msu2(2,2))/Sqr(M3Input)))/Sqr(M3Input)))/((-1 + (
      0.9930129810249694*msq2(2,2))/Sqr(M3Input))*((0.9930129810249694*msq2(2,2))
      /Sqr(M3Input) - (1.01007550314386*msu2(2,2))/Sqr(M3Input))*(-1 + (
      1.01007550314386*msu2(2,2))/Sqr(M3Input))) - (4*Sqr(Log((0.9930129810249694*
      msq2(2,2))/Sqr(M3Input)))*((3.9167402291282185*Cube(msq2(2,2)))/Power6(
      M3Input) - (1.01007550314386*msu2(2,2))/Sqr(M3Input) + (0.9930129810249694*
      msq2(2,2)*(3 + (4.04030201257544*msu2(2,2))/Sqr(M3Input)))/Sqr(M3Input) - (
      1.9721495609681923*(4 + (1.01007550314386*msu2(2,2))/Sqr(M3Input))*Sqr(msq2(
      2,2)))/Quad(M3Input)))/(Sqr(-1 + (0.9930129810249694*msq2(2,2))/Sqr(M3Input)
      )*Sqr((0.9930129810249694*msq2(2,2))/Sqr(M3Input) - (1.01007550314386*msu2(2
      ,2))/Sqr(M3Input))) + Log((0.9930129810249694*msq2(2,2))/Sqr(M3Input))*((4*(
      7 - (6.06045301886316*msu2(2,2))/Sqr(M3Input) + (0.9930129810249694*msq2(2,2
      )*(-4 + (3.03022650943158*msu2(2,2))/Sqr(M3Input)))/Sqr(M3Input)))/((-1 + (
      0.9930129810249694*msq2(2,2))/Sqr(M3Input))*((0.9930129810249694*msq2(2,2))
      /Sqr(M3Input) - (1.01007550314386*msu2(2,2))/Sqr(M3Input))*(-1 + (
      1.01007550314386*msu2(2,2))/Sqr(M3Input))) + (4*Log((1.01007550314386*msu2(2
      ,2))/Sqr(M3Input))*(2*((0.9930129810249694*msq2(2,2))/Sqr(M3Input) + (
      1.01007550314386*msu2(2,2))/Sqr(M3Input)) + (0.9930129810249694*msq2(2,2)*(
      -2 + (0.9930129810249694*msq2(2,2))/Sqr(M3Input))*((0.9930129810249694*msq2(
      2,2))/Sqr(M3Input) - (1.01007550314386*msu2(2,2))/Sqr(M3Input)))/(Sqr(
      M3Input)*Sqr(-1 + (0.9930129810249694*msq2(2,2))/Sqr(M3Input))) + (
      1.01007550314386*msu2(2,2)*(-2 + (1.01007550314386*msu2(2,2))/Sqr(M3Input))*
      ((-0.9930129810249694*msq2(2,2))/Sqr(M3Input) + (1.01007550314386*msu2(2,2))
      /Sqr(M3Input)))/(Sqr(M3Input)*Sqr(-1 + (1.01007550314386*msu2(2,2))/Sqr(
      M3Input)))))/Sqr((0.9930129810249694*msq2(2,2))/Sqr(M3Input) - (
      1.01007550314386*msu2(2,2))/Sqr(M3Input))) + (4*Sqr(Log((1.01007550314386*
      msu2(2,2))/Sqr(M3Input)))*((1.01007550314386*msu2(2,2)*(-3 + (
      8.08060402515088*msu2(2,2))/Sqr(M3Input) - (4.0810100882052875*Sqr(msu2(2,2)
      ))/Quad(M3Input)))/Sqr(M3Input) + (0.9930129810249694*msq2(2,2)*(1 - (
      4.04030201257544*msu2(2,2))/Sqr(M3Input) + (2.0405050441026438*Sqr(msu2(2,2)
      ))/Quad(M3Input)))/Sqr(M3Input)))/(Sqr((0.9930129810249694*msq2(2,2))/Sqr(
      M3Input) - (1.01007550314386*msu2(2,2))/Sqr(M3Input))*Sqr(-1 + (
      1.01007550314386*msu2(2,2))/Sqr(M3Input)))))/Sqr(M3Input) + (Sqr(Log((
      1.01007550314386*msu2(2,2))/Sqr(M3Input)))*(-6 + (8.08060402515088*msu2(2,2)
      )/Sqr(M3Input) - (4.0810100882052875*Sqr(msu2(2,2)))/Quad(M3Input)))/Sqr(-1
      + (1.01007550314386*msu2(2,2))/Sqr(M3Input)) + (2*Log((1.01007550314386*msu2
      (2,2))/Sqr(M3Input))*(-7 + (7.07052852200702*msu2(2,2))/Sqr(M3Input) - (
      3.0607575661539657*Sqr(msu2(2,2)))/Quad(M3Input) + (0.9930129810249694*msq2(
      2,2)*(6 - (5.050377515719299*msu2(2,2))/Sqr(M3Input) + (2.0405050441026438*
      Sqr(msu2(2,2)))/Quad(M3Input)))/Sqr(M3Input)))/((-1 + (0.9930129810249694*
      msq2(2,2))/Sqr(M3Input))*Sqr(-1 + (1.01007550314386*msu2(2,2))/Sqr(M3Input))
      ) - (1.9939819899999993*Quad(M3Input)*((-1 + (0.9930129810249694*msq2(2,2))
      /Sqr(M3Input))*((4.012072345748721*msq2(2,2)*msu2(2,2)*PolyLog(2,(0.990025*(
      -1 + (1.01007550314386*msu2(2,2))/Sqr(M3Input))*Sqr(M3Input))/msu2(2,2))*(-1
      + (0.9930129810249694*msq2(2,2))/Sqr(M3Input)))/Quad(M3Input) + (-1 + (
      1.01007550314386*msu2(2,2))/Sqr(M3Input))*((2.02015100628772*msu2(2,2)*(-1 +
      (1.01007550314386*msu2(2,2))/Sqr(M3Input)))/Sqr(M3Input) + (
      0.9930129810249694*msq2(2,2)*(-2 + (9.09067952829474*msu2(2,2))/Sqr(M3Input)
      - (6.121515132307931*Sqr(msu2(2,2)))/Quad(M3Input)))/Sqr(M3Input) + (
      0.9860747804840961*Sqr(msq2(2,2))*(2 - (6.06045301886316*msu2(2,2))/Sqr(
      M3Input) + (3.0607575661539657*Sqr(msu2(2,2)))/Quad(M3Input)))/Quad(M3Input)
      )) + (4.012072345748721*msq2(2,2)*msu2(2,2)*PolyLog(2,(1.0070361809045223*(
      -1 + (0.9930129810249694*msq2(2,2))/Sqr(M3Input))*Sqr(M3Input))/msq2(2,2))*
      Sqr(-1 + (1.01007550314386*msu2(2,2))/Sqr(M3Input)))/Quad(M3Input)))/(msq2(2
      ,2)*msu2(2,2)*Sqr(-1 + (0.9930129810249694*msq2(2,2))/Sqr(M3Input))*Sqr(-1 +
      (1.01007550314386*msu2(2,2))/Sqr(M3Input))) + (Quad(AtInput -
      MuInput/TanBeta)*((-3.9879639799999986*Quad(M3Input)*((0.9791850572820546*
      Cube(msq2(2,2)))/Power6(M3Input) - (1.030532079544781*Cube(msu2(2,2)))
      /Power6(M3Input) - (5.116658661753119*Cube(msu2(2,2))*msq2(2,2))/Power8(
      M3Input) + (4.945254197025603*Cube(msq2(2,2))*msu2(2,2))/Power8(M3Input) + (
      1.0030180864371803*msq2(2,2)*msu2(2,2)*PolyLog(2,(1.0070361809045223*(-1 + (
      0.9930129810249694*msq2(2,2))/Sqr(M3Input))*Sqr(M3Input))/msq2(2,2))*(-1 + (
      0.9930129810249694*msq2(2,2))/Sqr(M3Input))*(-1 + (1.01007550314386*msu2(2,2
      ))/Sqr(M3Input))*(-2 + (0.9930129810249694*msq2(2,2))/Sqr(M3Input) + (
      1.01007550314386*msu2(2,2))/Sqr(M3Input)))/Quad(M3Input) - (
      1.0030180864371803*msq2(2,2)*msu2(2,2)*PolyLog(2,(0.990025*(-1 + (
      1.01007550314386*msu2(2,2))/Sqr(M3Input))*Sqr(M3Input))/msu2(2,2))*(-1 + (
      0.9930129810249694*msq2(2,2))/Sqr(M3Input))*(-1 + (1.01007550314386*msu2(2,2
      ))/Sqr(M3Input))*(-2 + (0.9930129810249694*msq2(2,2))/Sqr(M3Input) + (
      1.01007550314386*msu2(2,2))/Sqr(M3Input)))/Quad(M3Input) + (
      5.080908470594695*Cube(msu2(2,2))*Sqr(msq2(2,2)))/Power10(M3Input) - (
      5.976059880209667*msu2(2,2)*Sqr(msq2(2,2)))/Power6(M3Input) - (
      0.9860747804840961*Sqr(msq2(2,2)))/Quad(M3Input) - (4.995080121234921*Cube(
      msq2(2,2))*Sqr(msu2(2,2)))/Power10(M3Input) + (6.078743989922559*msq2(2,2)*
      Sqr(msu2(2,2)))/Power6(M3Input) + (1.0202525220513219*Sqr(msu2(2,2)))/Quad(
      M3Input)))/(Cube((0.9930129810249694*msq2(2,2))/Sqr(M3Input) - (
      1.01007550314386*msu2(2,2))/Sqr(M3Input))*msq2(2,2)*msu2(2,2)*(-1 + (
      0.9930129810249694*msq2(2,2))/Sqr(M3Input))*(-1 + (1.01007550314386*msu2(2,2
      ))/Sqr(M3Input))) + (2*Sqr(Log((0.9930129810249694*msq2(2,2))/Sqr(M3Input)))
      *((4.861717363533792*Quad(msq2(2,2)))/Power8(M3Input) + (3.9167402291282185*
      Cube(msq2(2,2))*(-2 + (1.01007550314386*msu2(2,2))/Sqr(M3Input)))/Power6(
      M3Input) - (2.02015100628772*msu2(2,2))/Sqr(M3Input) - (0.9960099800349447*
      msu2(2,2)*(10 + (1.01007550314386*msu2(2,2))/Sqr(M3Input))*Sqr(msq2(2,2)))
      /Power6(M3Input) + (1.9860259620499388*msq2(2,2)*(1 + (4.04030201257544*msu2
      (2,2))/Sqr(M3Input) + (1.0202525220513219*Sqr(msu2(2,2)))/Quad(M3Input)))
      /Sqr(M3Input)))/(Quad((0.9930129810249694*msq2(2,2))/Sqr(M3Input) - (
      1.01007550314386*msu2(2,2))/Sqr(M3Input))*Sqr(-1 + (0.9930129810249694*msq2(
      2,2))/Sqr(M3Input))) + Log(Sqr(M3Input)/Sqr(SCALE))*((4*Log((
      0.9930129810249694*msq2(2,2))/Sqr(M3Input))*(2 + (2.979038943074908*msq2(2,2
      ))/Sqr(M3Input) + (3.03022650943158*msu2(2,2))/Sqr(M3Input)))/Cube((
      0.9930129810249694*msq2(2,2))/Sqr(M3Input) - (1.01007550314386*msu2(2,2))
      /Sqr(M3Input)) - (4*Log((1.01007550314386*msu2(2,2))/Sqr(M3Input))*(2 + (
      2.979038943074908*msq2(2,2))/Sqr(M3Input) + (3.03022650943158*msu2(2,2))/Sqr
      (M3Input)))/Cube((0.9930129810249694*msq2(2,2))/Sqr(M3Input) - (
      1.01007550314386*msu2(2,2))/Sqr(M3Input)) - (3.9879639799999986*Quad(M3Input
      )*((6.018108518623082*msq2(2,2)*msu2(2,2))/Quad(M3Input) + (
      0.9930129810249694*msq2(2,2))/Sqr(M3Input) + (1.01007550314386*msu2(2,2))
      /Sqr(M3Input)))/(msq2(2,2)*msu2(2,2)*Sqr((0.9930129810249694*msq2(2,2))/Sqr(
      M3Input) - (1.01007550314386*msu2(2,2))/Sqr(M3Input)))) + Log((
      0.9930129810249694*msq2(2,2))/Sqr(M3Input))*((2*(4 + (0.9791850572820546*
      Cube(msq2(2,2))*(16 - (15.1511325471579*msu2(2,2))/Sqr(M3Input)))/Power6(
      M3Input) + (3.03022650943158*msu2(2,2))/Sqr(M3Input) - (6.121515132307931*
      Sqr(msu2(2,2)))/Quad(M3Input) + (0.9860747804840961*Sqr(msq2(2,2))*(-29 + (
      31.31234059745966*msu2(2,2))/Sqr(M3Input) - (3.0607575661539657*Sqr(msu2(2,2
      )))/Quad(M3Input)))/Quad(M3Input) + (0.9930129810249694*msq2(2,2)*(7 - (
      15.1511325471579*msu2(2,2))/Sqr(M3Input) + (7.141767654359253*Sqr(msu2(2,2))
      )/Quad(M3Input)))/Sqr(M3Input)))/(Cube((0.9930129810249694*msq2(2,2))/Sqr(
      M3Input) - (1.01007550314386*msu2(2,2))/Sqr(M3Input))*(-1 + (
      1.01007550314386*msu2(2,2))/Sqr(M3Input))*Sqr(-1 + (0.9930129810249694*msq2(
      2,2))/Sqr(M3Input))) + (2*Log((1.01007550314386*msu2(2,2))/Sqr(M3Input))*((
      -8.024144691497442*msq2(2,2)*msu2(2,2))/Quad(M3Input) - (3.9442991219363845*
      Sqr(msq2(2,2)))/Quad(M3Input) - (0.9930129810249694*msq2(2,2)*(-2 + (
      0.9930129810249694*msq2(2,2))/Sqr(M3Input))*((0.9930129810249694*msq2(2,2))
      /Sqr(M3Input) - (1.01007550314386*msu2(2,2))/Sqr(M3Input))*((
      0.9930129810249694*msq2(2,2))/Sqr(M3Input) + (1.01007550314386*msu2(2,2))
      /Sqr(M3Input)))/(Sqr(M3Input)*Sqr(-1 + (0.9930129810249694*msq2(2,2))/Sqr(
      M3Input))) - (4.0810100882052875*Sqr(msu2(2,2)))/Quad(M3Input) - (
      1.01007550314386*msu2(2,2)*(-2 + (1.01007550314386*msu2(2,2))/Sqr(M3Input))*
      ((-0.9930129810249694*msq2(2,2))/Sqr(M3Input) + (1.01007550314386*msu2(2,2))
      /Sqr(M3Input))*((0.9930129810249694*msq2(2,2))/Sqr(M3Input) + (
      1.01007550314386*msu2(2,2))/Sqr(M3Input)))/(Sqr(M3Input)*Sqr(-1 + (
      1.01007550314386*msu2(2,2))/Sqr(M3Input)))))/Quad((0.9930129810249694*msq2(2
      ,2))/Sqr(M3Input) - (1.01007550314386*msu2(2,2))/Sqr(M3Input))) + (2*Log((
      1.01007550314386*msu2(2,2))/Sqr(M3Input))*(-4 - (16.488513272716496*Cube(
      msu2(2,2)))/Power6(M3Input) - (7.07052852200702*msu2(2,2))/Sqr(M3Input) + (
      29.587323139488333*Sqr(msu2(2,2)))/Quad(M3Input) + (0.9930129810249694*msq2(
      2,2)*(-3 + (15.457981193171715*Cube(msu2(2,2)))/Power6(M3Input) + (
      15.1511325471579*msu2(2,2))/Sqr(M3Input) - (31.627828183590978*Sqr(msu2(2,2)
      ))/Quad(M3Input)))/Sqr(M3Input) + (0.9860747804840961*Sqr(msq2(2,2))*(6 - (
      7.07052852200702*msu2(2,2))/Sqr(M3Input) + (3.0607575661539657*Sqr(msu2(2,2)
      ))/Quad(M3Input)))/Quad(M3Input)))/(Cube((0.9930129810249694*msq2(2,2))/Sqr(
      M3Input) - (1.01007550314386*msu2(2,2))/Sqr(M3Input))*(-1 + (
      0.9930129810249694*msq2(2,2))/Sqr(M3Input))*Sqr(-1 + (1.01007550314386*msu2(
      2,2))/Sqr(M3Input))) - (2*Sqr(Log((1.01007550314386*msu2(2,2))/Sqr(M3Input))
      )*((8.244256636358248*Cube(msu2(2,2)))/Power6(M3Input) - (5.204576043760415*
      Quad(msu2(2,2)))/Power8(M3Input) - (2.02015100628772*msu2(2,2))/Sqr(M3Input)
      + (0.9960099800349447*msu2(2,2)*(-2 + (1.01007550314386*msu2(2,2))/Sqr(
      M3Input))*Sqr(msq2(2,2)))/Power6(M3Input) - (1.9860259620499388*msq2(2,2)*(
      -1 + (2.02015100628772*msu2(2,2))/Sqr(M3Input))*Sqr(-1 + (1.01007550314386*
      msu2(2,2))/Sqr(M3Input)))/Sqr(M3Input)))/(Quad((0.9930129810249694*msq2(2,2)
      )/Sqr(M3Input) - (1.01007550314386*msu2(2,2))/Sqr(M3Input))*Sqr(-1 + (
      1.01007550314386*msu2(2,2))/Sqr(M3Input)))))/Quad(M3Input)))/Quad(
      3.141592653589793)), 0) + IF(TwoLoopAtAt >= 1, WHICH(IsCloseRel(msu2(2,2),
      msq2(2,2),0.01) && IsCloseRel(Sqr(mAInput),msu2(2,2),0.01), (0.01171875*
      Power6(Yu(2,2))*(1 + Sqr(TanBeta))*(0.5 - 8*IF(Abs(-1 + Sqr(MuInput)/Sqrt(
      msq2(2,2)*msu2(2,2))) < 0.00001, -1, (Log(Sqr(MuInput)/Sqrt(msq2(2,2)*msu2(2
      ,2)))*Sqr(MuInput))/(Sqrt(msq2(2,2)*msu2(2,2))*(1 - Sqr(MuInput)/Sqrt(msq2(2
      ,2)*msu2(2,2))))) + 4*IF(Abs(-1 + Sqr(MuInput)/Sqrt(msq2(2,2)*msu2(2,2))) <
      0.00001, -2.25, Re(((-1 + (2*Quad(MuInput))/(msq2(2,2)*msu2(2,2)) + (2*Sqr(
      MuInput))/Sqrt(msq2(2,2)*msu2(2,2)))*(Log(Abs(1 - Sqr(MuInput)/Sqrt(msq2(2,2
      )*msu2(2,2))))*Log(Sqr(MuInput)/Sqrt(msq2(2,2)*msu2(2,2))) + PolyLog(2,Sqr(
      MuInput)/Sqrt(msq2(2,2)*msu2(2,2))) - 0.16666666666666666*Sqr(
      3.141592653589793) - (Log(Sqr(MuInput)/Sqrt(msq2(2,2)*msu2(2,2)))*Sqr(
      MuInput))/Sqrt(msq2(2,2)*msu2(2,2))))/Sqr(Abs(1 - Sqr(MuInput)/Sqrt(msq2(2,2
      )*msu2(2,2)))))) - 4*Log(Sqrt(msq2(2,2)*msu2(2,2))/Sqr(SCALE)) + (6*Sqr(
      MuInput))/Sqrt(msq2(2,2)*msu2(2,2)) - (2*IF(Abs(-1 + Sqr(MuInput)/Sqrt(msq2(
      2,2)*msu2(2,2))) < 0.00001, -1, (Log(Sqr(MuInput)/Sqrt(msq2(2,2)*msu2(2,2)))
      *Sqr(MuInput))/(Sqrt(msq2(2,2)*msu2(2,2))*(1 - Sqr(MuInput)/Sqrt(msq2(2,2)*
      msu2(2,2)))))*Sqr(MuInput))/Sqrt(msq2(2,2)*msu2(2,2)) + (3*IF(Abs(-1 + Sqr(
      MuInput)/Sqrt(msq2(2,2)*msu2(2,2))) < 0.00001, 0.5, (1 + (Log(Sqr(MuInput)
      /Sqrt(msq2(2,2)*msu2(2,2)))*Sqr(MuInput))/(Sqrt(msq2(2,2)*msu2(2,2))*(1 -
      Sqr(MuInput)/Sqrt(msq2(2,2)*msu2(2,2)))))/(1 - Sqr(MuInput)/Sqrt(msq2(2,2)*
      msu2(2,2))))*Sqr(MuInput))/Sqrt(msq2(2,2)*msu2(2,2)) - (6*Log(Sqrt(msq2(2,2)
      *msu2(2,2))/Sqr(SCALE))*Sqr(MuInput))/Sqrt(msq2(2,2)*msu2(2,2)) -
      8.34993159891064/(1 + Sqr(TanBeta)) + (13*Log(Sqrt(msq2(2,2)*msu2(2,2))/Sqr(
      SCALE)))/(1 + Sqr(TanBeta)) + (Power6(AtInput - MuInput/TanBeta)*(-0.5 + 0.5
      *Log(Sqrt(msq2(2,2)*msu2(2,2))/Sqr(SCALE)) + (0.5 - 0.5*Log(Sqrt(msq2(2,2)*
      msu2(2,2))/Sqr(SCALE)))/(1 + Sqr(TanBeta))))/Power3(Sqrt(msq2(2,2)*msu2(2,2)
      )) + (Cube(AtInput - MuInput/TanBeta)*((AtInput - MuInput/TanBeta)/Sqrt(Sqrt
      (msq2(2,2)*msu2(2,2))) + (2*MuInput*Csc(2*ArcTan(TanBeta)))/Sqrt(Sqrt(msq2(2
      ,2)*msu2(2,2))))*(0.8747904000000002/(1 + Sqr(TanBeta)) - (2*Log(Sqrt(msq2(2
      ,2)*msu2(2,2))/Sqr(SCALE)))/(1 + Sqr(TanBeta))))/Power3(Sqrt(Sqrt(msq2(2,2)*
      msu2(2,2)))) + ((AtInput - MuInput/TanBeta)*((AtInput - MuInput/TanBeta)
      /Sqrt(Sqrt(msq2(2,2)*msu2(2,2))) + (2*MuInput*Csc(2*ArcTan(TanBeta)))/Sqrt(
      Sqrt(msq2(2,2)*msu2(2,2))))*(0.5008383999999992/(1 + Sqr(TanBeta)) + (12*Log
      (Sqrt(msq2(2,2)*msu2(2,2))/Sqr(SCALE)))/(1 + Sqr(TanBeta))))/Sqrt(Sqrt(msq2(
      2,2)*msu2(2,2))) + 3*Sqr(Log(Sqrt(msq2(2,2)*msu2(2,2))/Sqr(SCALE))) - (3*Sqr
      (Log(Sqrt(msq2(2,2)*msu2(2,2))/Sqr(SCALE))))/(1 + Sqr(TanBeta)) + (
      0.1252095999999998/(1 + Sqr(TanBeta)) + (3*Log(Sqrt(msq2(2,2)*msu2(2,2))/Sqr
      (SCALE)))/(1 + Sqr(TanBeta)))*Sqr((AtInput - MuInput/TanBeta)/Sqrt(Sqrt(msq2
      (2,2)*msu2(2,2))) + (2*MuInput*Csc(2*ArcTan(TanBeta)))/Sqrt(Sqrt(msq2(2,2)*
      msu2(2,2)))) + (Sqr(AtInput - MuInput/TanBeta)*(-7 + 4*IF(Abs(-1 + Sqr(
      MuInput)/Sqrt(msq2(2,2)*msu2(2,2))) < 0.00001, -1, (Log(Sqr(MuInput)/Sqrt(
      msq2(2,2)*msu2(2,2)))*Sqr(MuInput))/(Sqrt(msq2(2,2)*msu2(2,2))*(1 - Sqr(
      MuInput)/Sqrt(msq2(2,2)*msu2(2,2))))) - 4*IF(Abs(-1 + Sqr(MuInput)/Sqrt(msq2
      (2,2)*msu2(2,2))) < 0.00001, 0.5, (1 + (Log(Sqr(MuInput)/Sqrt(msq2(2,2)*msu2
      (2,2)))*Sqr(MuInput))/(Sqrt(msq2(2,2)*msu2(2,2))*(1 - Sqr(MuInput)/Sqrt(msq2
      (2,2)*msu2(2,2)))))/(1 - Sqr(MuInput)/Sqrt(msq2(2,2)*msu2(2,2)))) + 27*Log(
      Sqrt(msq2(2,2)*msu2(2,2))/Sqr(SCALE)) - (6*Sqr(MuInput))/Sqrt(msq2(2,2)*msu2
      (2,2)) - (6*IF(Abs(-1 + Sqr(MuInput)/Sqrt(msq2(2,2)*msu2(2,2))) < 0.00001,
      -1, (Log(Sqr(MuInput)/Sqrt(msq2(2,2)*msu2(2,2)))*Sqr(MuInput))/(Sqrt(msq2(2,
      2)*msu2(2,2))*(1 - Sqr(MuInput)/Sqrt(msq2(2,2)*msu2(2,2)))))*Sqr(MuInput))
      /Sqrt(msq2(2,2)*msu2(2,2)) - (6*IF(Abs(-1 + Sqr(MuInput)/Sqrt(msq2(2,2)*msu2
      (2,2))) < 0.00001, 0.5, (1 + (Log(Sqr(MuInput)/Sqrt(msq2(2,2)*msu2(2,2)))*
      Sqr(MuInput))/(Sqrt(msq2(2,2)*msu2(2,2))*(1 - Sqr(MuInput)/Sqrt(msq2(2,2)*
      msu2(2,2)))))/(1 - Sqr(MuInput)/Sqrt(msq2(2,2)*msu2(2,2))))*Sqr(MuInput))
      /Sqrt(msq2(2,2)*msu2(2,2)) + (6*Log(Sqrt(msq2(2,2)*msu2(2,2))/Sqr(SCALE))*
      Sqr(MuInput))/Sqrt(msq2(2,2)*msu2(2,2)) + 19.6878144/(1 + Sqr(TanBeta)) - (
      24*Log(Sqrt(msq2(2,2)*msu2(2,2))/Sqr(SCALE)))/(1 + Sqr(TanBeta)) + (
      -0.021147733333332752/(1 + Sqr(TanBeta)) - (3*Log(Sqrt(msq2(2,2)*msu2(2,2))
      /Sqr(SCALE)))/(1 + Sqr(TanBeta)))*Sqr((AtInput - MuInput/TanBeta)/Sqrt(Sqrt(
      msq2(2,2)*msu2(2,2))) + (2*MuInput*Csc(2*ArcTan(TanBeta)))/Sqrt(Sqrt(msq2(2,
      2)*msu2(2,2))))))/Sqrt(msq2(2,2)*msu2(2,2)) + (Quad(AtInput -
      MuInput/TanBeta)*(5.5 - 0.5*IF(Abs(-1 + Sqr(MuInput)/Sqrt(msq2(2,2)*msu2(2,2
      ))) < 0.00001, -1, (Log(Sqr(MuInput)/Sqrt(msq2(2,2)*msu2(2,2)))*Sqr(MuInput)
      )/(Sqrt(msq2(2,2)*msu2(2,2))*(1 - Sqr(MuInput)/Sqrt(msq2(2,2)*msu2(2,2)))))
      + 0.5*IF(Abs(-1 + Sqr(MuInput)/Sqrt(msq2(2,2)*msu2(2,2))) < 0.00001, 0.5, (1
      + (Log(Sqr(MuInput)/Sqrt(msq2(2,2)*msu2(2,2)))*Sqr(MuInput))/(Sqrt(msq2(2,2
      )*msu2(2,2))*(1 - Sqr(MuInput)/Sqrt(msq2(2,2)*msu2(2,2)))))/(1 - Sqr(MuInput
      )/Sqrt(msq2(2,2)*msu2(2,2)))) - 6.5*Log(Sqrt(msq2(2,2)*msu2(2,2))/Sqr(SCALE)
      ) + Sqr(MuInput)/Sqrt(msq2(2,2)*msu2(2,2)) + (IF(Abs(-1 + Sqr(MuInput)/Sqrt(
      msq2(2,2)*msu2(2,2))) < 0.00001, -1, (Log(Sqr(MuInput)/Sqrt(msq2(2,2)*msu2(2
      ,2)))*Sqr(MuInput))/(Sqrt(msq2(2,2)*msu2(2,2))*(1 - Sqr(MuInput)/Sqrt(msq2(2
      ,2)*msu2(2,2)))))*Sqr(MuInput))/Sqrt(msq2(2,2)*msu2(2,2)) + (0.5*IF(Abs(-1 +
      Sqr(MuInput)/Sqrt(msq2(2,2)*msu2(2,2))) < 0.00001, 0.5, (1 + (Log(Sqr(
      MuInput)/Sqrt(msq2(2,2)*msu2(2,2)))*Sqr(MuInput))/(Sqrt(msq2(2,2)*msu2(2,2))
      *(1 - Sqr(MuInput)/Sqrt(msq2(2,2)*msu2(2,2)))))/(1 - Sqr(MuInput)/Sqrt(msq2(
      2,2)*msu2(2,2))))*Sqr(MuInput))/Sqrt(msq2(2,2)*msu2(2,2)) - (Log(Sqrt(msq2(2
      ,2)*msu2(2,2))/Sqr(SCALE))*Sqr(MuInput))/Sqrt(msq2(2,2)*msu2(2,2)) - 6.25/(1
      + Sqr(TanBeta)) + (6*Log(Sqrt(msq2(2,2)*msu2(2,2))/Sqr(SCALE)))/(1 + Sqr(
      TanBeta)) + (-0.020728533333333354/(1 + Sqr(TanBeta)) + (0.5*Log(Sqrt(msq2(2
      ,2)*msu2(2,2))/Sqr(SCALE)))/(1 + Sqr(TanBeta)))*Sqr((AtInput -
      MuInput/TanBeta)/Sqrt(Sqrt(msq2(2,2)*msu2(2,2))) + (2*MuInput*Csc(2*ArcTan(
      TanBeta)))/Sqrt(Sqrt(msq2(2,2)*msu2(2,2))))))/(msq2(2,2)*msu2(2,2))))/(Quad(
      3.141592653589793)*Sqr(TanBeta)), True, (0.00390625*Power6(Yu(2,2))*(3*(5 -
      4*Log(0.98*msu2(2,2)) + Log(1.02*msq2(2,2))*(-6 - 6*Log(Sqr(SCALE))) + (10 -
      4*Log(0.98*msu2(2,2)))*Log(Sqr(SCALE)) + 5*Sqr(Log(Sqr(SCALE))) + 3*Sqr(Log
      (1.02*msq2(2,2))) + 2*Sqr(Log(0.98*msu2(2,2)))) + 3*Power6(AtInput -
      MuInput/TanBeta)*((-2*PolyLog(2,1 - (1.0408163265306123*msq2(2,2))/msu2(2,2)
      ))/Cube(1.02*msq2(2,2) - 0.98*msu2(2,2)) + (4*PolyLog(2,(0.9803921568627451*
      (1.02*msq2(2,2) - 0.98*msu2(2,2)))/msq2(2,2)))/Cube(1.02*msq2(2,2) - 0.98*
      msu2(2,2)) + ((-9.18*msq2(2,2) - 4.9*msu2(2,2))*Sqr(Log(1.02*msq2(2,2))))
      /Quad(1.02*msq2(2,2) - 0.98*msu2(2,2)) + ((-3.06*msq2(2,2) - 4.9*msu2(2,2))*
      Sqr(Log(0.98*msu2(2,2))))/Quad(1.02*msq2(2,2) - 0.98*msu2(2,2)) + Log(1.02*
      msq2(2,2))*((6.12*Log(Sqr(SCALE))*msq2(2,2))/Quad(1.02*msq2(2,2) - 0.98*msu2
      (2,2)) + (2*Log(0.98*msu2(2,2))*(6.12*msq2(2,2) + 4.9*msu2(2,2)))/Quad(1.02*
      msq2(2,2) - 0.98*msu2(2,2)) + (1.0204081632653061*(12.994800000000001*msq2(2
      ,2)*msu2(2,2) + 2.0808*Sqr(msq2(2,2)) - 2.8811999999999998*Sqr(msu2(2,2))))/
      (msu2(2,2)*Quad(1.02*msq2(2,2) - 0.98*msu2(2,2)))) + Log(Sqr(SCALE))*((-6.12
      *Log(0.98*msu2(2,2))*msq2(2,2))/Quad(1.02*msq2(2,2) - 0.98*msu2(2,2)) + (
      1.0004001600640255*(-4.998*msq2(2,2)*msu2(2,2) - 2.0808*Sqr(msq2(2,2)) +
      0.9603999999999999*Sqr(msu2(2,2))))/(Cube(1.02*msq2(2,2) - 0.98*msu2(2,2))*
      msq2(2,2)*msu2(2,2))) + (0.9803921568627451*Log(0.98*msu2(2,2))*(-2.9988*
      msq2(2,2)*msu2(2,2) - 10.404*Sqr(msq2(2,2)) + 0.9603999999999999*Sqr(msu2(2,
      2))))/(msq2(2,2)*Quad(1.02*msq2(2,2) - 0.98*msu2(2,2))) + (
      1.0004001600640255*(-10.9956*msq2(2,2)*msu2(2,2) - 2.0808*Sqr(msq2(2,2)) +
      0.9603999999999999*Sqr(msu2(2,2))))/(Cube(1.02*msq2(2,2) - 0.98*msu2(2,2))*
      msq2(2,2)*msu2(2,2))) + 3*Quad(AtInput - MuInput/TanBeta)*(((
      -7.140000000000001*msq2(2,2) - 8.82*msu2(2,2))*Sqr(Log(1.02*msq2(2,2))))
      /Cube(1.02*msq2(2,2) - 0.98*msu2(2,2)) + ((3.06*msq2(2,2) + 4.9*msu2(2,2))*
      Sqr(Log(0.98*msu2(2,2))))/Cube(1.02*msq2(2,2) - 0.98*msu2(2,2)) - (6*PolyLog
      (2,1 - (1.0408163265306123*msq2(2,2))/msu2(2,2)))/Sqr(1.02*msq2(2,2) - 0.98*
      msu2(2,2)) + Log(1.02*msq2(2,2))*((4*Log(0.98*msu2(2,2))*(1.02*msq2(2,2) +
      0.98*msu2(2,2)))/Cube(1.02*msq2(2,2) - 0.98*msu2(2,2)) + (2*Log(Sqr(SCALE))*
      (5.1*msq2(2,2) + 6.859999999999999*msu2(2,2)))/Cube(1.02*msq2(2,2) - 0.98*
      msu2(2,2)) - (4.081632653061225*(-9.996*msq2(2,2)*msu2(2,2) + 1.0404*Sqr(
      msq2(2,2)) - 2.8811999999999998*Sqr(msu2(2,2))))/(Cube(1.02*msq2(2,2) - 0.98
      *msu2(2,2))*msu2(2,2))) + Log(Sqr(SCALE))*((-2*Log(0.98*msu2(2,2))*(5.1*msq2
      (2,2) + 6.859999999999999*msu2(2,2)))/Cube(1.02*msq2(2,2) - 0.98*msu2(2,2))
      + (2.000800320128051*(-14.994*msq2(2,2)*msu2(2,2) + 2.0808*Sqr(msq2(2,2)) +
      0.9603999999999999*Sqr(msu2(2,2))))/(msq2(2,2)*msu2(2,2)*Sqr(1.02*msq2(2,2)
      - 0.98*msu2(2,2)))) + (2.000800320128051*(-26.9892*msq2(2,2)*msu2(2,2) +
      2.0808*Sqr(msq2(2,2)) + 0.9603999999999999*Sqr(msu2(2,2))))/(msq2(2,2)*msu2(
      2,2)*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) + (0.9803921568627451*Log(0.98*
      msu2(2,2))*(-43.9824*msq2(2,2)*msu2(2,2) - 6.2424*Sqr(msq2(2,2)) +
      1.9207999999999998*Sqr(msu2(2,2))))/(Cube(1.02*msq2(2,2) - 0.98*msu2(2,2))*
      msq2(2,2))) + 3*Sqr(AtInput - MuInput/TanBeta)*((-6*PolyLog(2,1 - (
      1.0408163265306123*msq2(2,2))/msu2(2,2)))/(1.02*msq2(2,2) - 0.98*msu2(2,2))
      - (9*Sqr(Log(0.98*msu2(2,2))))/(1.02*msq2(2,2) - 0.98*msu2(2,2)) + ((
      7.140000000000001*msq2(2,2) - 8.82*msu2(2,2))*Sqr(Log(1.02*msq2(2,2))))/Sqr(
      1.02*msq2(2,2) - 0.98*msu2(2,2)) + Log(Sqr(SCALE))*((2*Log(0.98*msu2(2,2))*(
      8.16*msq2(2,2) - 8.82*msu2(2,2)))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)) + (
      1.0004001600640255*(-0.9996*msq2(2,2)*msu2(2,2) - 2.0808*Sqr(msq2(2,2)) +
      0.9603999999999999*Sqr(msu2(2,2))))/(msq2(2,2)*(1.02*msq2(2,2) - 0.98*msu2(2
      ,2))*msu2(2,2))) + (1.0004001600640255*(-2.9988*msq2(2,2)*msu2(2,2) - 2.0808
      *Sqr(msq2(2,2)) + 0.9603999999999999*Sqr(msu2(2,2))))/(msq2(2,2)*(1.02*msq2(
      2,2) - 0.98*msu2(2,2))*msu2(2,2)) + (0.9803921568627451*Log(0.98*msu2(2,2))*
      (-20.9916*msq2(2,2)*msu2(2,2) + 16.6464*Sqr(msq2(2,2)) + 0.9603999999999999*
      Sqr(msu2(2,2))))/(msq2(2,2)*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) + Log(1.02
      *msq2(2,2))*((2.04*Log(0.98*msu2(2,2))*msq2(2,2))/Sqr(1.02*msq2(2,2) - 0.98*
      msu2(2,2)) - (2*Log(Sqr(SCALE))*(8.16*msq2(2,2) - 8.82*msu2(2,2)))/Sqr(1.02*
      msq2(2,2) - 0.98*msu2(2,2)) + (1.0204081632653061*(-16.9932*msq2(2,2)*msu2(2
      ,2) + 2.0808*Sqr(msq2(2,2)) + 18.2476*Sqr(msu2(2,2))))/(msu2(2,2)*Sqr(1.02*
      msq2(2,2) - 0.98*msu2(2,2))))) + ((1 + Sqr(TanBeta))*(Sqr(AtInput -
      MuInput/TanBeta)*(9*((4*Log(0.98*msu2(2,2)))/(1.02*msq2(2,2) - 0.98*msu2(2,2
      )) + (4*Log(0.98*msu2(2,2))*Log(Sqr(SCALE)))/(1.02*msq2(2,2) - 0.98*msu2(2,2
      )) + Log(1.02*msq2(2,2))*(-4/(1.02*msq2(2,2) - 0.98*msu2(2,2)) - (4*Log(Sqr(
      SCALE)))/(1.02*msq2(2,2) - 0.98*msu2(2,2)) - (4*Log(0.98*msu2(2,2))*(1.02*
      msq2(2,2) + 0.98*msu2(2,2)))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) + (4.08*
      msq2(2,2)*Sqr(Log(1.02*msq2(2,2))))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)) + (
      3.92*msu2(2,2)*Sqr(Log(0.98*msu2(2,2))))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)
      )) + 3*((-4*PolyLog(2,1 - (0.9702970297029703*msu2(2,2))/Sqr(MuInput))*(
      -1.02*msq2(2,2) + 1.01*Sqr(MuInput)))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)) +
      (4*PolyLog(2,(0.9900990099009901*(-1.02*msq2(2,2) + 1.01*Sqr(MuInput)))/Sqr
      (MuInput))*(-1.02*msq2(2,2) + 1.01*Sqr(MuInput)))/Sqr(1.02*msq2(2,2) - 0.98*
      msu2(2,2)) + Log(Sqr(SCALE))*((2*Log(0.98*msu2(2,2))*(2.04*msq2(2,2) + 0.98*
      msu2(2,2) - 2.02*Sqr(MuInput)))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)) + (
      1.0004001600640255*(3.9984*msq2(2,2)*msu2(2,2) - 8.2416*msq2(2,2)*Sqr(
      MuInput) + 3.9592*msu2(2,2)*Sqr(MuInput) + 4.1616*Sqr(msq2(2,2)) -
      1.9207999999999998*Sqr(msu2(2,2))))/(msq2(2,2)*(1.02*msq2(2,2) - 0.98*msu2(2
      ,2))*msu2(2,2))) + (1.0004001600640255*(5.9976*msq2(2,2)*msu2(2,2) - 8.2416*
      msq2(2,2)*Sqr(MuInput) + 3.9592*msu2(2,2)*Sqr(MuInput) + 4.1616*Sqr(msq2(2,2
      )) - 1.9207999999999998*Sqr(msu2(2,2))))/(msq2(2,2)*(1.02*msq2(2,2) - 0.98*
      msu2(2,2))*msu2(2,2)) + (0.9803921568627451*Log(0.98*msu2(2,2))*(-4.20362808
      *msq2(2,2)*Power6(MuInput) + 1.0201*Quad(MuInput)*(16.9932*msq2(2,2)*msu2(2,
      2) + 1.0404*Sqr(msq2(2,2)) - 1.9207999999999998*Sqr(msu2(2,2))) + 0.9996*
      msq2(2,2)*msu2(2,2)*(2.9988*msq2(2,2)*msu2(2,2) + 7.2828*Sqr(msq2(2,2)) -
      1.9207999999999998*Sqr(msu2(2,2))) - 1.01*Sqr(MuInput)*(1.061208*Cube(msq2(2
      ,2)) - 1.8823839999999998*Cube(msu2(2,2)) + 16.313472*msu2(2,2)*Sqr(msq2(2,2
      )) + 4.89804*msq2(2,2)*Sqr(msu2(2,2)))))/(msq2(2,2)*(-1.02*msq2(2,2) + 1.01*
      Sqr(MuInput))*(-0.98*msu2(2,2) + 1.01*Sqr(MuInput))*Sqr(1.02*msq2(2,2) -
      0.98*msu2(2,2))) + (2.04*msq2(2,2)*(1.02*msq2(2,2)*(1.02*msq2(2,2) + 1.96*
      msu2(2,2)) + 3.0603*Quad(MuInput) - 2.02*(1.02*msq2(2,2) + 1.96*msu2(2,2))*
      Sqr(MuInput))*Sqr(Log(1.02*msq2(2,2))))/(Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)
      )*Sqr(-1.02*msq2(2,2) + 1.01*Sqr(MuInput))) + Log(1.02*msq2(2,2))*((-2*Log(
      Sqr(SCALE))*(2.04*msq2(2,2) + 0.98*msu2(2,2) - 2.02*Sqr(MuInput)))/Sqr(1.02*
      msq2(2,2) - 0.98*msu2(2,2)) + (1.0204081632653061*(4.03877992*msu2(2,2)*
      Power6(MuInput) + 0.9996*msq2(2,2)*msu2(2,2)*(-6.997199999999999*msq2(2,2)*
      msu2(2,2) - 4.1616*Sqr(msq2(2,2)) + 2.8811999999999998*Sqr(msu2(2,2))) -
      1.0201*Quad(MuInput)*(0.9996*msq2(2,2)*msu2(2,2) + 4.1616*Sqr(msq2(2,2)) +
      10.5644*Sqr(msu2(2,2))) + 1.01*Sqr(MuInput)*(4.244832*Cube(msq2(2,2)) +
      4.705959999999999*Cube(msu2(2,2)) + 9.176328*msu2(2,2)*Sqr(msq2(2,2)) +
      1.9592159999999998*msq2(2,2)*Sqr(msu2(2,2)))))/(msu2(2,2)*(-1.02*msq2(2,2) +
      1.01*Sqr(MuInput))*(-0.98*msu2(2,2) + 1.01*Sqr(MuInput))*Sqr(1.02*msq2(2,2)
      - 0.98*msu2(2,2))) + Log(0.98*msu2(2,2))*((-6.12*msq2(2,2))/Sqr(1.02*msq2(2
      ,2) - 0.98*msu2(2,2)) - (3.92*msu2(2,2))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)
      ) + (4.08*msq2(2,2)*(1.02*msq2(2,2) - 2.02*Sqr(MuInput)))/((1.02*msq2(2,2) -
      0.98*msu2(2,2))*Sqr(-1.02*msq2(2,2) + 1.01*Sqr(MuInput))) + (1.96*msu2(2,2)
      *(0.98*msu2(2,2) - 2.02*Sqr(MuInput)))/((-1.02*msq2(2,2) + 0.98*msu2(2,2))*
      Sqr(-0.98*msu2(2,2) + 1.01*Sqr(MuInput))))) + Log(1.01*Sqr(MuInput))*((
      4.041616646658663*Sqr(MuInput)*(1.0201*(2.04*msq2(2,2) - 0.98*msu2(2,2))*
      Quad(MuInput) + 1.019592*msu2(2,2)*Sqr(msq2(2,2)) + 1.01*Sqr(MuInput)*(
      -0.9996*msq2(2,2)*msu2(2,2) - 2.0808*Sqr(msq2(2,2)) + 0.9603999999999999*Sqr
      (msu2(2,2)))))/(msq2(2,2)*(1.02*msq2(2,2) - 0.98*msu2(2,2))*msu2(2,2)*(-1.02
      *msq2(2,2) + 1.01*Sqr(MuInput))*(-0.98*msu2(2,2) + 1.01*Sqr(MuInput))) + (2*
      Log(0.98*msu2(2,2))*(2.1020201002*Power10(MuInput) - 1.04060401*(3.06*msq2(2
      ,2) + 6.859999999999999*msu2(2,2))*Power8(MuInput) + 2.05957584*msu2(2,2)*(
      2.04*msq2(2,2) + 2.94*msu2(2,2))*Sqr(MuInput)*Sqr(msq2(2,2)) -
      2.0383683263999997*Cube(msq2(2,2))*Sqr(msu2(2,2)) + 2.060602*Power6(MuInput)
      *(4.998*msq2(2,2)*msu2(2,2) + 2.0808*Sqr(msq2(2,2)) + 2.8811999999999998*Sqr
      (msu2(2,2))) - 1.0201*Quad(MuInput)*(1.061208*Cube(msq2(2,2)) +
      1.8823839999999998*Cube(msu2(2,2)) + 13.254696000000001*msu2(2,2)*Sqr(msq2(2
      ,2)) + 3.9184319999999997*msq2(2,2)*Sqr(msu2(2,2)))))/(Sqr(1.02*msq2(2,2) -
      0.98*msu2(2,2))*Sqr(-1.02*msq2(2,2) + 1.01*Sqr(MuInput))*Sqr(-0.98*msu2(2,2)
      + 1.01*Sqr(MuInput))) + (2*Log(1.02*msq2(2,2))*(-2.1020201002*Power10(
      MuInput) + 1.04060401*(3.06*msq2(2,2) + 6.859999999999999*msu2(2,2))*Power8(
      MuInput) - 2.05957584*msu2(2,2)*(2.04*msq2(2,2) + 2.94*msu2(2,2))*Sqr(
      MuInput)*Sqr(msq2(2,2)) + 2.0383683263999997*Cube(msq2(2,2))*Sqr(msu2(2,2))
      - 2.060602*Power6(MuInput)*(4.998*msq2(2,2)*msu2(2,2) + 2.0808*Sqr(msq2(2,2)
      ) + 2.8811999999999998*Sqr(msu2(2,2))) + 1.0201*Quad(MuInput)*(1.061208*Cube
      (msq2(2,2)) + 1.8823839999999998*Cube(msu2(2,2)) + 13.254696000000001*msu2(2
      ,2)*Sqr(msq2(2,2)) + 3.9184319999999997*msq2(2,2)*Sqr(msu2(2,2)))))/(Sqr(
      1.02*msq2(2,2) - 0.98*msu2(2,2))*Sqr(-1.02*msq2(2,2) + 1.01*Sqr(MuInput))*
      Sqr(-0.98*msu2(2,2) + 1.01*Sqr(MuInput)))) + (1.96*msu2(2,2)*(0.98*(1.02*
      msq2(2,2) + 0.98*msu2(2,2))*msu2(2,2) + 2.0402*Quad(MuInput) - 2.02*(1.02*
      msq2(2,2) + 0.98*msu2(2,2))*Sqr(MuInput))*Sqr(Log(0.98*msu2(2,2))))/(Sqr(
      1.02*msq2(2,2) - 0.98*msu2(2,2))*Sqr(-0.98*msu2(2,2) + 1.01*Sqr(MuInput)))))
      + Quad(AtInput - MuInput/TanBeta)*(9*((-4*Log(0.98*msu2(2,2))*(1.02*msq2(2,
      2) + 2.94*msu2(2,2)))/Cube(1.02*msq2(2,2) - 0.98*msu2(2,2)) - (4.08*msq2(2,2
      )*(1.02*msq2(2,2) + 0.98*msu2(2,2))*Sqr(Log(1.02*msq2(2,2))))/Quad(1.02*msq2
      (2,2) - 0.98*msu2(2,2)) - (3.92*(1.02*msq2(2,2) + 0.98*msu2(2,2))*msu2(2,2)*
      Sqr(Log(0.98*msu2(2,2))))/Quad(1.02*msq2(2,2) - 0.98*msu2(2,2)) + Log(Sqr(
      SCALE))*((-4*Log(0.98*msu2(2,2))*(1.02*msq2(2,2) + 0.98*msu2(2,2)))/Cube(
      1.02*msq2(2,2) - 0.98*msu2(2,2)) - 8/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) -
      8/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)) + Log(1.02*msq2(2,2))*((4*Log(Sqr(
      SCALE))*(1.02*msq2(2,2) + 0.98*msu2(2,2)))/Cube(1.02*msq2(2,2) - 0.98*msu2(2
      ,2)) + (4*(3.06*msq2(2,2) + 0.98*msu2(2,2)))/Cube(1.02*msq2(2,2) - 0.98*msu2
      (2,2)) + (4*Log(0.98*msu2(2,2))*Sqr(1.02*msq2(2,2) + 0.98*msu2(2,2)))/Quad(
      1.02*msq2(2,2) - 0.98*msu2(2,2)))) + 3*((2*PolyLog(2,(0.9900990099009901*(
      -1.02*msq2(2,2) + 1.01*Sqr(MuInput)))/Sqr(MuInput))*(1.9992*msq2(2,2)*msu2(2
      ,2) + 3.0603*Quad(MuInput) - 6.1812000000000005*msq2(2,2)*Sqr(MuInput) +
      2.0808*Sqr(msq2(2,2)) - 0.9603999999999999*Sqr(msu2(2,2))))/Quad(1.02*msq2(2
      ,2) - 0.98*msu2(2,2)) + (2*PolyLog(2,1 - (0.9702970297029703*msu2(2,2))/Sqr(
      MuInput))*(-1.9992*msq2(2,2)*msu2(2,2) - 3.0603*Quad(MuInput) +
      6.1812000000000005*msq2(2,2)*Sqr(MuInput) - 2.0808*Sqr(msq2(2,2)) +
      0.9603999999999999*Sqr(msu2(2,2))))/Quad(1.02*msq2(2,2) - 0.98*msu2(2,2)) +
      Log(Sqr(SCALE))*((3*Log(0.98*msu2(2,2))*(-1.9992*msq2(2,2)*msu2(2,2) +
      4.1208*msq2(2,2)*Sqr(MuInput) - 3.1212*Sqr(msq2(2,2)) + 0.9603999999999999*
      Sqr(msu2(2,2))))/Quad(1.02*msq2(2,2) - 0.98*msu2(2,2)) + (1.0004001600640255
      *(-2.122416*Cube(msq2(2,2)) + 0.9411919999999999*Cube(msu2(2,2)) -
      13.254696000000001*msu2(2,2)*Sqr(msq2(2,2)) + 2.02*Sqr(MuInput)*(4.998*msq2(
      2,2)*msu2(2,2) + 2.0808*Sqr(msq2(2,2)) - 0.9603999999999999*Sqr(msu2(2,2)))
      + 1.9592159999999998*msq2(2,2)*Sqr(msu2(2,2))))/(Cube(1.02*msq2(2,2) - 0.98*
      msu2(2,2))*msq2(2,2)*msu2(2,2))) + (1.0004001600640255*(2.060602*Power6(
      MuInput)*(7.9968*msq2(2,2)*msu2(2,2) + 2.0808*Sqr(msq2(2,2)) -
      0.9603999999999999*Sqr(msu2(2,2))) + 0.9996*msq2(2,2)*msu2(2,2)*(-2.122416*
      Cube(msq2(2,2)) + 0.9411919999999999*Cube(msu2(2,2)) - 24.470208*msu2(2,2)*
      Sqr(msq2(2,2)) + 6.857256*msq2(2,2)*Sqr(msu2(2,2))) - 1.0201*Quad(MuInput)*(
      6.367248*Cube(msq2(2,2)) - 2.8235759999999996*Cube(msu2(2,2)) +
      38.744496000000005*msu2(2,2)*Sqr(msq2(2,2)) + 12.734903999999998*msq2(2,2)*
      Sqr(msu2(2,2))) + 1.01*Sqr(MuInput)*(-5.7600950399999995*Cube(msu2(2,2))*
      msq2(2,2) + 29.119547519999998*Cube(msq2(2,2))*msu2(2,2) + 2.16486432*Quad(
      msq2(2,2)) - 0.9223681599999999*Quad(msu2(2,2)) + 30.975204959999996*Sqr(
      msq2(2,2))*Sqr(msu2(2,2)))))/(Cube(1.02*msq2(2,2) - 0.98*msu2(2,2))*msq2(2,2
      )*msu2(2,2)*(-1.02*msq2(2,2) + 1.01*Sqr(MuInput))*(-0.98*msu2(2,2) + 1.01*
      Sqr(MuInput))) - (2.04*msq2(2,2)*Sqr(Log(1.02*msq2(2,2)))*(1.0201*(4.08*msq2
      (2,2) + 2.94*msu2(2,2))*Quad(MuInput) + 1.02*msq2(2,2)*(2.9988*msq2(2,2)*
      msu2(2,2) + 3.1212*Sqr(msq2(2,2)) + 0.9603999999999999*Sqr(msu2(2,2))) -
      2.02*Sqr(MuInput)*(2.9988*msq2(2,2)*msu2(2,2) + 3.1212*Sqr(msq2(2,2)) +
      0.9603999999999999*Sqr(msu2(2,2)))))/(Quad(1.02*msq2(2,2) - 0.98*msu2(2,2))*
      Sqr(-1.02*msq2(2,2) + 1.01*Sqr(MuInput))) + Log(1.02*msq2(2,2))*((-3*Log(Sqr
      (SCALE))*(-1.9992*msq2(2,2)*msu2(2,2) + 4.1208*msq2(2,2)*Sqr(MuInput) -
      3.1212*Sqr(msq2(2,2)) + 0.9603999999999999*Sqr(msu2(2,2))))/Quad(1.02*msq2(2
      ,2) - 0.98*msu2(2,2)) + (0.5102040816326531*(-37.446759662256*msq2(2,2)*msu2
      (2,2)*Power8(MuInput) - 1.019592*msu2(2,2)*Sqr(msq2(2,2))*(4.244832*Cube(
      msq2(2,2)) - 17.882648*Cube(msu2(2,2)) + 47.920824*msu2(2,2)*Sqr(msq2(2,2))
      + 3.9184319999999997*msq2(2,2)*Sqr(msu2(2,2))) + 1.030301*Power6(MuInput)*(
      4.244832*Cube(msq2(2,2)) - 4.705959999999999*Cube(msu2(2,2)) + 123.370632*
      msu2(2,2)*Sqr(msq2(2,2)) + 23.510592*msq2(2,2)*Sqr(msu2(2,2))) + 1.0201*Quad
      (MuInput)*(40.32066528*Cube(msu2(2,2))*msq2(2,2) - 131.03796384*Cube(msq2(2,
      2))*msu2(2,2) - 8.65945728*Quad(msq2(2,2)) + 6.4565771199999995*Quad(msu2(2,
      2)) - 130.89522096*Sqr(msq2(2,2))*Sqr(msu2(2,2))) + 1.0302*msq2(2,2)*Sqr(
      MuInput)*(-8.64014256*Cube(msu2(2,2))*msq2(2,2) + 55.119143519999994*Cube(
      msq2(2,2))*msu2(2,2) + 4.32972864*Quad(msq2(2,2)) - 31.360517439999995*Quad(
      msu2(2,2)) + 129.89602079999997*Sqr(msq2(2,2))*Sqr(msu2(2,2)))))/(msu2(2,2)*
      Quad(1.02*msq2(2,2) - 0.98*msu2(2,2))*(-0.98*msu2(2,2) + 1.01*Sqr(MuInput))*
      Sqr(-1.02*msq2(2,2) + 1.01*Sqr(MuInput))) + Log(0.98*msu2(2,2))*((10.2*msq2(
      2,2))/Cube(1.02*msq2(2,2) - 0.98*msu2(2,2)) + (5.88*msu2(2,2))/Cube(-1.02*
      msq2(2,2) + 0.98*msu2(2,2)) + (21.9912*msq2(2,2)*msu2(2,2))/Quad(1.02*msq2(2
      ,2) - 0.98*msu2(2,2)) - 2/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)) + (2.04*msq2(
      2,2)*(1.02*msq2(2,2) + 0.98*msu2(2,2))*(-1.02*msq2(2,2) + 2.02*Sqr(MuInput))
      )/(Cube(1.02*msq2(2,2) - 0.98*msu2(2,2))*Sqr(-1.02*msq2(2,2) + 1.01*Sqr(
      MuInput))) + (0.98*(1.02*msq2(2,2) + 0.98*msu2(2,2))*msu2(2,2)*(-0.98*msu2(2
      ,2) + 2.02*Sqr(MuInput)))/(Cube(-1.02*msq2(2,2) + 0.98*msu2(2,2))*Sqr(-0.98*
      msu2(2,2) + 1.01*Sqr(MuInput))))) + Log(1.01*Sqr(MuInput))*((Log(1.02*msq2(2
      ,2))*(12.864363013223999*msq2(2,2)*Power10(MuInput) - 1.04060401*Power8(
      MuInput)*(27.9888*msq2(2,2)*msu2(2,2) + 26.009999999999998*Sqr(msq2(2,2)) +
      0.9603999999999999*Sqr(msu2(2,2))) + 1.9984003199999998*Sqr(msq2(2,2))*(
      -1.9992*msq2(2,2)*msu2(2,2) - 2.0808*Sqr(msq2(2,2)) + 0.9603999999999999*Sqr
      (msu2(2,2)))*Sqr(msu2(2,2)) + 6.3054421199999995*msq2(2,2)*Power6(MuInput)*(
      9.996*msq2(2,2)*msu2(2,2) + 3.1212*Sqr(msq2(2,2)) + 2.8811999999999998*Sqr(
      msu2(2,2))) + 4.038384*msq2(2,2)*msu2(2,2)*Sqr(MuInput)*(2.122416*Cube(msq2(
      2,2)) - 0.9411919999999999*Cube(msu2(2,2)) + 7.137144*msu2(2,2)*Sqr(msq2(2,2
      )) + 0.9796079999999999*msq2(2,2)*Sqr(msu2(2,2))) - 1.040502*msq2(2,2)*Quad(
      MuInput)*(3.183624*Cube(msq2(2,2)) - 3.7647679999999997*Cube(msu2(2,2)) +
      44.862048*msu2(2,2)*Sqr(msq2(2,2)) + 40.163928*msq2(2,2)*Sqr(msu2(2,2)))))/(
      Quad(1.02*msq2(2,2) - 0.98*msu2(2,2))*Sqr(-1.02*msq2(2,2) + 1.01*Sqr(MuInput
      ))*Sqr(-0.98*msu2(2,2) + 1.01*Sqr(MuInput))) + (Log(0.98*msu2(2,2))*(
      -12.864363013223999*msq2(2,2)*Power10(MuInput) + 1.04060401*Power8(MuInput)*
      (27.9888*msq2(2,2)*msu2(2,2) + 26.009999999999998*Sqr(msq2(2,2)) +
      0.9603999999999999*Sqr(msu2(2,2))) + 1.9984003199999998*Sqr(msq2(2,2))*(
      1.9992*msq2(2,2)*msu2(2,2) + 2.0808*Sqr(msq2(2,2)) - 0.9603999999999999*Sqr(
      msu2(2,2)))*Sqr(msu2(2,2)) - 6.3054421199999995*msq2(2,2)*Power6(MuInput)*(
      9.996*msq2(2,2)*msu2(2,2) + 3.1212*Sqr(msq2(2,2)) + 2.8811999999999998*Sqr(
      msu2(2,2))) - 4.038384*msq2(2,2)*msu2(2,2)*Sqr(MuInput)*(2.122416*Cube(msq2(
      2,2)) - 0.9411919999999999*Cube(msu2(2,2)) + 7.137144*msu2(2,2)*Sqr(msq2(2,2
      )) + 0.9796079999999999*msq2(2,2)*Sqr(msu2(2,2))) + 1.040502*msq2(2,2)*Quad(
      MuInput)*(3.183624*Cube(msq2(2,2)) - 3.7647679999999997*Cube(msu2(2,2)) +
      44.862048*msu2(2,2)*Sqr(msq2(2,2)) + 40.163928*msq2(2,2)*Sqr(msu2(2,2)))))/(
      Quad(1.02*msq2(2,2) - 0.98*msu2(2,2))*Sqr(-1.02*msq2(2,2) + 1.01*Sqr(MuInput
      ))*Sqr(-0.98*msu2(2,2) + 1.01*Sqr(MuInput))) - (2.0208083233293315*Sqr(
      MuInput)*(-3.1511510352*Cube(msq2(2,2))*msu2(2,2)*(1.02*msq2(2,2) + 2.94*
      msu2(2,2))*Sqr(MuInput) + 1.04060401*Power8(MuInput)*(1.9992*msq2(2,2)*msu2(
      2,2) + 2.0808*Sqr(msq2(2,2)) - 0.9603999999999999*Sqr(msu2(2,2))) +
      0.9992001599999999*Sqr(msq2(2,2))*(1.9992*msq2(2,2)*msu2(2,2) + 2.0808*Sqr(
      msq2(2,2)) - 0.9603999999999999*Sqr(msu2(2,2)))*Sqr(msu2(2,2)) - 1.030301*
      Power6(MuInput)*(4.244832*Cube(msq2(2,2)) - 1.8823839999999998*Cube(msu2(2,2
      )) + 5.0979600000000005*msu2(2,2)*Sqr(msq2(2,2)) + 4.89804*msq2(2,2)*Sqr(
      msu2(2,2))) + 1.0201*Quad(MuInput)*(1.92003168*Cube(msu2(2,2))*msq2(2,2) +
      8.319870719999999*Cube(msq2(2,2))*msu2(2,2) + 2.16486432*Quad(msq2(2,2)) -
      0.9223681599999999*Quad(msu2(2,2)) + 6.994401119999999*Sqr(msq2(2,2))*Sqr(
      msu2(2,2)))))/(Cube(1.02*msq2(2,2) - 0.98*msu2(2,2))*msq2(2,2)*msu2(2,2)*Sqr
      (-1.02*msq2(2,2) + 1.01*Sqr(MuInput))*Sqr(-0.98*msu2(2,2) + 1.01*Sqr(MuInput
      )))) - (0.98*(1.02*msq2(2,2) + 0.98*msu2(2,2))*msu2(2,2)*(0.98*msu2(2,2)*(
      1.02*msq2(2,2) + 2.94*msu2(2,2)) + 4.0804*Quad(MuInput) - 2.02*(1.02*msq2(2,
      2) + 2.94*msu2(2,2))*Sqr(MuInput))*Sqr(Log(0.98*msu2(2,2))))/(Quad(1.02*msq2
      (2,2) - 0.98*msu2(2,2))*Sqr(-0.98*msu2(2,2) + 1.01*Sqr(MuInput))) + (
      0.49019607843137253*Log(0.98*msu2(2,2))*(12.736993082400001*msq2(2,2)*(2.04*
      msq2(2,2) + 0.98*msu2(2,2))*Power8(MuInput) + 0.9796079999999999*msq2(2,2)*
      Sqr(msu2(2,2))*(26.530199999999997*Cube(msq2(2,2)) - 1.8823839999999998*Cube
      (msu2(2,2)) + 34.666128*msu2(2,2)*Sqr(msq2(2,2)) - 20.571768*msq2(2,2)*Sqr(
      msu2(2,2))) - 1.030301*Power6(MuInput)*(41.387111999999995*Cube(msq2(2,2)) -
      1.8823839999999998*Cube(msu2(2,2)) + 103.998384*msu2(2,2)*Sqr(msq2(2,2)) +
      4.89804*msq2(2,2)*Sqr(msu2(2,2))) + 0.9898*msu2(2,2)*Sqr(MuInput)*(
      20.16033264*Cube(msu2(2,2))*msq2(2,2) - 117.51817391999998*Cube(msq2(2,2))*
      msu2(2,2) - 51.95674368*Quad(msq2(2,2)) + 1.8447363199999998*Quad(msu2(2,2))
      - 5.995200959999999*Sqr(msq2(2,2))*Sqr(msu2(2,2))) + 1.0201*Quad(MuInput)*(
      -21.12034848*Cube(msu2(2,2))*msq2(2,2) + 135.1978992*Cube(msq2(2,2))*msu2(2,
      2) + 20.56621104*Quad(msq2(2,2)) - 3.6894726399999995*Quad(msu2(2,2)) +
      92.92561487999998*Sqr(msq2(2,2))*Sqr(msu2(2,2)))))/(msq2(2,2)*Quad(1.02*msq2
      (2,2) - 0.98*msu2(2,2))*(-1.02*msq2(2,2) + 1.01*Sqr(MuInput))*Sqr(-0.98*msu2
      (2,2) + 1.01*Sqr(MuInput))))) + 3*(Log(Sqr(SCALE))*(Log(0.98*msu2(2,2)) - (
      1.0004001600640255*(2.04*msq2(2,2) + 0.98*msu2(2,2))*(1.02*msq2(2,2) + 0.98*
      msu2(2,2) - 2.02*Sqr(MuInput)))/(msq2(2,2)*msu2(2,2))) - 2*Sqr(Log(Sqr(SCALE
      ))) + (0.5002000800320128*(4.121204*(2.04*msq2(2,2) + 0.98*msu2(2,2))*Power6
      (MuInput) - 0.9996*msq2(2,2)*msu2(2,2)*(2.9988*msq2(2,2)*msu2(2,2) + 4.1616*
      Sqr(msq2(2,2)) + 1.9207999999999998*Sqr(msu2(2,2))) - 3.0603*Quad(MuInput)*(
      6.9972*msq2(2,2)*msu2(2,2) + 4.1616*Sqr(msq2(2,2)) + 1.9207999999999998*Sqr(
      msu2(2,2))) + 1.01*Sqr(MuInput)*(4.244832*Cube(msq2(2,2)) +
      1.8823839999999998*Cube(msu2(2,2)) + 17.333064*msu2(2,2)*Sqr(msq2(2,2)) +
      12.734903999999998*msq2(2,2)*Sqr(msu2(2,2)))))/(msq2(2,2)*msu2(2,2)*(-1.02*
      msq2(2,2) + 1.01*Sqr(MuInput))*(-0.98*msu2(2,2) + 1.01*Sqr(MuInput))) + (
      4.0804*PolyLog(2,(0.9900990099009901*(-1.02*msq2(2,2) + 1.01*Sqr(MuInput)))
      /Sqr(MuInput))*Quad(MuInput))/Sqr(-1.02*msq2(2,2) + 1.01*Sqr(MuInput)) + (
      2.04*msq2(2,2)*(-1.02*msq2(2,2) + 2.02*Sqr(MuInput))*Sqr(Log(1.02*msq2(2,2))
      ))/Sqr(-1.02*msq2(2,2) + 1.01*Sqr(MuInput)) + (2*PolyLog(2,1 - (
      1.00990099009901*msq2(2,2))/Sqr(MuInput))*(1.0201*Quad(MuInput) + 2.0604*
      msq2(2,2)*Sqr(MuInput) - 1.0404*Sqr(msq2(2,2))))/Sqr(-1.02*msq2(2,2) + 1.01*
      Sqr(MuInput)) + Log(1.02*msq2(2,2))*(3*Log(Sqr(SCALE)) + (0.5102040816326531
      *(1.030301*(4.08*msq2(2,2) + 14.7*msu2(2,2))*Power6(MuInput) - 1.019592*msu2
      (2,2)*(4.08*msq2(2,2) + 4.9*msu2(2,2))*Sqr(msq2(2,2)) + 1.0302*msq2(2,2)*Sqr
      (MuInput)*(14.994*msq2(2,2)*msu2(2,2) + 4.1616*Sqr(msq2(2,2)) +
      5.7623999999999995*Sqr(msu2(2,2))) - 1.0201*Quad(MuInput)*(13.9944*msq2(2,2)
      *msu2(2,2) + 8.3232*Sqr(msq2(2,2)) + 12.485199999999999*Sqr(msu2(2,2)))))/(
      msu2(2,2)*(-0.98*msu2(2,2) + 1.01*Sqr(MuInput))*Sqr(-1.02*msq2(2,2) + 1.01*
      Sqr(MuInput))) + (Log(0.98*msu2(2,2))*(-2.01938996*msu2(2,2)*Power6(MuInput)
      + 2.08120802*Power8(MuInput) + 0.999698*(-4.08*msq2(2,2) + 0.98*msu2(2,2))*
      msu2(2,2)*Quad(MuInput) + 2.019192*msq2(2,2)*(1.02*msq2(2,2) + 0.98*msu2(2,2
      ))*msu2(2,2)*Sqr(MuInput) - 0.9992001599999999*Sqr(msq2(2,2))*Sqr(msu2(2,2))
      ))/(Sqr(-1.02*msq2(2,2) + 1.01*Sqr(MuInput))*Sqr(-0.98*msu2(2,2) + 1.01*Sqr(
      MuInput)))) + Log(1.01*Sqr(MuInput))*((Log(0.98*msu2(2,2))*(2.10181404*msq2(
      2,2)*Power6(MuInput) - 3.12181203*Power8(MuInput) - 1.040502*msq2(2,2)*(1.02
      *msq2(2,2) - 7.84*msu2(2,2))*Quad(MuInput) - 4.038384*msq2(2,2)*(1.02*msq2(2
      ,2) + 0.98*msu2(2,2))*msu2(2,2)*Sqr(MuInput) + 1.9984003199999998*Sqr(msq2(2
      ,2))*Sqr(msu2(2,2))))/(Sqr(-1.02*msq2(2,2) + 1.01*Sqr(MuInput))*Sqr(-0.98*
      msu2(2,2) + 1.01*Sqr(MuInput))) + (Log(1.02*msq2(2,2))*(-2.060602*(1.02*msq2
      (2,2) - 3.92*msu2(2,2))*Power6(MuInput) - 5.20302005*Power8(MuInput) -
      4.038384*msq2(2,2)*(1.02*msq2(2,2) + 0.98*msu2(2,2))*msu2(2,2)*Sqr(MuInput)
      + 1.0201*Quad(MuInput)*(7.9968*msq2(2,2)*msu2(2,2) + 1.0404*Sqr(msq2(2,2)) -
      3.8415999999999997*Sqr(msu2(2,2))) + 1.9984003199999998*Sqr(msq2(2,2))*Sqr(
      msu2(2,2))))/(Sqr(-1.02*msq2(2,2) + 1.01*Sqr(MuInput))*Sqr(-0.98*msu2(2,2) +
      1.01*Sqr(MuInput))) + (1.0104041616646657*Sqr(MuInput)*(-2.08120802*(2.04*
      msq2(2,2) + 0.98*msu2(2,2))*Power8(MuInput) + 1.009596*msq2(2,2)*msu2(2,2)*
      Sqr(MuInput)*(7.9968*msq2(2,2)*msu2(2,2) + 3.1212*Sqr(msq2(2,2)) -
      1.9207999999999998*Sqr(msu2(2,2))) - 1.9984003199999998*(1.02*msq2(2,2) +
      0.98*msu2(2,2))*Sqr(msq2(2,2))*Sqr(msu2(2,2)) + 1.030301*Power6(MuInput)*(
      0.9996*msq2(2,2)*msu2(2,2) + 8.3232*Sqr(msq2(2,2)) + 3.8415999999999997*Sqr(
      msu2(2,2))) - 2.0402*Quad(MuInput)*(2.122416*Cube(msq2(2,2)) +
      0.9411919999999999*Cube(msu2(2,2)) + 4.078368*msu2(2,2)*Sqr(msq2(2,2)) -
      0.9796079999999999*msq2(2,2)*Sqr(msu2(2,2)))))/(msq2(2,2)*msu2(2,2)*Sqr(
      -1.02*msq2(2,2) + 1.01*Sqr(MuInput))*Sqr(-0.98*msu2(2,2) + 1.01*Sqr(MuInput)
      ))) + (0.98*msu2(2,2)*(-0.98*msu2(2,2) + 2.02*Sqr(MuInput))*Sqr(Log(0.98*
      msu2(2,2))))/Sqr(-0.98*msu2(2,2) + 1.01*Sqr(MuInput)) + (2*PolyLog(2,1 - (
      0.9702970297029703*msu2(2,2))/Sqr(MuInput))*(1.0201*Quad(MuInput) + 1.9796*
      msu2(2,2)*Sqr(MuInput) - 0.9603999999999999*Sqr(msu2(2,2))))/Sqr(-0.98*msu2(
      2,2) + 1.01*Sqr(MuInput)) + (0.49019607843137253*Log(0.98*msu2(2,2))*(
      1.030301*(13.26*msq2(2,2) + 1.96*msu2(2,2))*Power6(MuInput) -
      0.9796079999999999*msq2(2,2)*(1.02*msq2(2,2) + 1.96*msu2(2,2))*Sqr(msu2(2,2)
      ) + 0.9898*msu2(2,2)*Sqr(MuInput)*(8.996400000000001*msq2(2,2)*msu2(2,2) +
      4.1616*Sqr(msq2(2,2)) + 1.9207999999999998*Sqr(msu2(2,2))) - 1.0201*Quad(
      MuInput)*(13.9944*msq2(2,2)*msu2(2,2) + 9.3636*Sqr(msq2(2,2)) +
      3.8415999999999997*Sqr(msu2(2,2)))))/(msq2(2,2)*(-1.02*msq2(2,2) + 1.01*Sqr(
      MuInput))*Sqr(-0.98*msu2(2,2) + 1.01*Sqr(MuInput))) + (Sqr(Log(1.01*Sqr(
      MuInput)))*(-4.03877992*msu2(2,2)*Power6(MuInput) + 4.16241604*Power8(
      MuInput) + 1.999396*(-4.08*msq2(2,2) + 0.98*msu2(2,2))*msu2(2,2)*Quad(
      MuInput) + 4.038384*msq2(2,2)*(1.02*msq2(2,2) + 0.98*msu2(2,2))*msu2(2,2)*
      Sqr(MuInput) - 1.9984003199999998*Sqr(msq2(2,2))*Sqr(msu2(2,2))))/(Sqr(-1.02
      *msq2(2,2) + 1.01*Sqr(MuInput))*Sqr(-0.98*msu2(2,2) + 1.01*Sqr(MuInput)))) +
      (3*Sqr(AtInput + MuInput*TanBeta)*(-0.9803921568627451/msq2(2,2) + Log(Sqr(
      SCALE))*(-0.9803921568627451/msq2(2,2) - 2.0408163265306123/msu2(2,2)) -
      2.0408163265306123/msu2(2,2) + (0.5206164098292378*Log(1.02*msq2(2,2))*((
      -Cube(1.02*msq2(2,2) - 0.98*msu2(2,2)) + 0.9702989999999999*Power6(mAInput)
      - 2.9402999999999997*(1.02*msq2(2,2) + 0.98*msu2(2,2))*Quad(mAInput) +
      2.9699999999999998*Sqr(mAInput)*(1.0404*Sqr(msq2(2,2)) - 0.9603999999999999*
      Sqr(msu2(2,2))))*TDelta(0.99*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2)) +
      TDelta(0.99*Sqr(mAInput),1.02*msq2(2,2),0.98*msu2(2,2))*(-0.98*msu2(2,2)*(
      0.9801*Quad(mAInput) - 1.9404*msu2(2,2)*Sqr(mAInput) - 1.0404*Sqr(msq2(2,2))
      + 0.9603999999999999*Sqr(msu2(2,2))) + (1.02*msq2(2,2) + 1.96*msu2(2,2) -
      0.99*Sqr(mAInput))*TDelta(0.99*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2))))
      )/(Sqr(msu2(2,2))*TDelta(0.99*Sqr(mAInput),1.02*msq2(2,2),0.98*msu2(2,2))*
      TDelta(0.99*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2))) + (
      0.5002000800320128*Log(0.98*msu2(2,2))*((Cube(1.02*msq2(2,2) - 0.98*msu2(2,2
      )) + 0.9702989999999999*Power6(mAInput) - 0.9801*(1.02*msq2(2,2) + 4.9*msu2(
      2,2))*Quad(mAInput) - 0.99*Sqr(mAInput)*(3.9984*msq2(2,2)*msu2(2,2) + 1.0404
      *Sqr(msq2(2,2)) - 4.802*Sqr(msu2(2,2))))*TDelta(0.99*Sqr(mAInput),0.98*msu2(
      2,2),1.02*msq2(2,2)) - TDelta(0.99*Sqr(mAInput),1.02*msq2(2,2),0.98*msu2(2,2
      ))*(1.9992*msq2(2,2)*msu2(2,2)*(1.02*msq2(2,2) - 0.98*msu2(2,2) + 0.99*Sqr(
      mAInput)) + (1.02*msq2(2,2) - 2.94*msu2(2,2) + 0.99*Sqr(mAInput))*TDelta(
      0.99*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2)))))/(msq2(2,2)*msu2(2,2)*
      TDelta(0.99*Sqr(mAInput),1.02*msq2(2,2),0.98*msu2(2,2))*TDelta(0.99*Sqr(
      mAInput),0.98*msu2(2,2),1.02*msq2(2,2))) + (0.5104082449306253*Log(0.99*Sqr(
      mAInput))*((-0.9702989999999999*(1.02*msq2(2,2) + 0.98*msu2(2,2))*Power6(
      mAInput) + Quad(1.02*msq2(2,2) - 0.98*msu2(2,2)) - 0.99*(3.06*msq2(2,2) +
      4.9*msu2(2,2))*Sqr(mAInput)*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)) + 0.9801*
      Quad(mAInput)*(3.9984*msq2(2,2)*msu2(2,2) + 3.1212*Sqr(msq2(2,2)) + 4.802*
      Sqr(msu2(2,2))))*TDelta(0.99*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2)) +
      TDelta(0.99*Sqr(mAInput),1.02*msq2(2,2),0.98*msu2(2,2))*(-0.9996*msq2(2,2)*
      msu2(2,2)*(-0.9801*Quad(mAInput) + Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) + (
      2.9988*msq2(2,2)*msu2(2,2) + 0.99*(1.02*msq2(2,2) + 0.98*msu2(2,2))*Sqr(
      mAInput) - 1.0404*Sqr(msq2(2,2)) - 0.9603999999999999*Sqr(msu2(2,2)))*TDelta
      (0.99*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2)))))/(msq2(2,2)*Sqr(msu2(2,2
      ))*TDelta(0.99*Sqr(mAInput),1.02*msq2(2,2),0.98*msu2(2,2))*TDelta(0.99*Sqr(
      mAInput),0.98*msu2(2,2),1.02*msq2(2,2))) + (0.5312412345196305*(
      -3.8811959999999996*(1.02*msq2(2,2) + 0.98*msu2(2,2))*Power6(mAInput) +
      0.96059601*Power8(mAInput) + Quad(1.02*msq2(2,2) - 0.98*msu2(2,2)) - 3.96*(
      1.02*msq2(2,2) + 0.98*msu2(2,2))*Sqr(mAInput)*Sqr(1.02*msq2(2,2) - 0.98*msu2
      (2,2)) + 1.9602*Quad(mAInput)*(1.9992*msq2(2,2)*msu2(2,2) + 3.1212*Sqr(msq2(
      2,2)) + 0.9603999999999999*Sqr(msu2(2,2))) + 2*Sqr(TDelta(0.99*Sqr(mAInput),
      1.02*msq2(2,2),0.98*msu2(2,2))) - 3*(0.9801*Quad(mAInput) - 1.98*(1.02*msq2(
      2,2) + 0.98*msu2(2,2))*Sqr(mAInput) + Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)))*
      TDelta(0.99*Sqr(mAInput),1.02*msq2(2,2),0.98*msu2(2,2)))*TPhi(0.99*Sqr(
      mAInput),1.02*msq2(2,2),0.98*msu2(2,2)))/(Cube(msu2(2,2))*TDelta(0.99*Sqr(
      mAInput),1.02*msq2(2,2),0.98*msu2(2,2))) + (0.49019607843137253*(-Sqr(0.99*
      Sqr(mAInput) + 1.02*msq2(2,2) - 0.98*msu2(2,2)) + TDelta(0.99*Sqr(mAInput),
      0.98*msu2(2,2),1.02*msq2(2,2)))*TPhi(0.99*Sqr(mAInput),0.98*msu2(2,2),1.02*
      msq2(2,2)))/(msq2(2,2)*TDelta(0.99*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2
      )))) + 3*(1.5 - 2.5*Log(0.98*msu2(2,2)) + Log(1.02*msq2(2,2))*(-4.5 - 3*Log(
      Sqr(SCALE))) + Sqr(3.141592653589793) - (0.9705882352941176*Sqr(mAInput))
      /msq2(2,2) - (2.0204081632653064*Sqr(mAInput))/msu2(2,2) + Log(0.99*Sqr(
      mAInput))*(7 - 3*Log(1.02*msq2(2,2)) - 3*Log(0.98*msu2(2,2)) + 0.99*(
      0.9803921568627451/msq2(2,2) + 2.0408163265306123/msu2(2,2))*Sqr(mAInput)) +
      Log(Sqr(SCALE))*(-Log(0.98*msu2(2,2)) - (0.9903961584633852*(2.04*msq2(2,2)
      + 0.98*msu2(2,2))*Sqr(mAInput))/(msq2(2,2)*msu2(2,2))) + 3*Sqr(Log(0.99*Sqr
      (mAInput))) + 2*Sqr(Log(Sqr(SCALE))) + 3*Sqr(Log(1.02*msq2(2,2))) + 2*Sqr(
      Log(0.98*msu2(2,2))) + (0.9611687812379854*(0.9801*Quad(mAInput) - 7.0686*
      msq2(2,2)*Sqr(mAInput) - TDelta(0.99*Sqr(mAInput),1.02*msq2(2,2),1.02*msq2(2
      ,2)))*TPhi(0.99*Sqr(mAInput),1.02*msq2(2,2),1.02*msq2(2,2)))/Sqr(msq2(2,2))
      + (1.0412328196584757*(0.9801*Quad(mAInput) - 5.8212*msu2(2,2)*Sqr(mAInput)
      - TDelta(0.99*Sqr(mAInput),0.98*msu2(2,2),0.98*msu2(2,2)))*TPhi(0.99*Sqr(
      mAInput),0.98*msu2(2,2),0.98*msu2(2,2)))/Sqr(msu2(2,2))) + 3*(AtInput -
      MuInput/TanBeta)*(AtInput + MuInput*TanBeta)*(Log(0.99*Sqr(mAInput))*((2*Log
      (1.02*msq2(2,2)))/(1.02*msq2(2,2) - 0.98*msu2(2,2)) - (2*Log(0.98*msu2(2,2))
      )/(1.02*msq2(2,2) - 0.98*msu2(2,2))) + Log(1.02*msq2(2,2))*(-12/(1.02*msq2(2
      ,2) - 0.98*msu2(2,2)) - (2*Log(0.98*msu2(2,2)))/(1.02*msq2(2,2) - 0.98*msu2(
      2,2)) - (12*Log(Sqr(SCALE)))/(1.02*msq2(2,2) - 0.98*msu2(2,2))) + (12*Log(
      0.98*msu2(2,2)))/(1.02*msq2(2,2) - 0.98*msu2(2,2)) + (12*Log(0.98*msu2(2,2))
      *Log(Sqr(SCALE)))/(1.02*msq2(2,2) - 0.98*msu2(2,2)) + (6*Sqr(Log(1.02*msq2(2
      ,2))))/(1.02*msq2(2,2) - 0.98*msu2(2,2)) - (4*Sqr(Log(0.98*msu2(2,2))))/(
      1.02*msq2(2,2) - 0.98*msu2(2,2)) - (1.9223375624759709*(-0.99*(
      -7.140000000000001*msq2(2,2) + 0.99*Sqr(mAInput))*Sqr(mAInput) + TDelta(0.99
      *Sqr(mAInput),1.02*msq2(2,2),1.02*msq2(2,2)))*TPhi(0.99*Sqr(mAInput),1.02*
      msq2(2,2),1.02*msq2(2,2)))/((1.02*msq2(2,2) - 0.98*msu2(2,2))*Sqr(msq2(2,2))
      ) + (1.9607843137254901*(1.02*msq2(2,2) - 0.98*msu2(2,2) + 0.99*Sqr(mAInput)
      )*TPhi(0.99*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2)))/(msq2(2,2)*(1.02*
      msq2(2,2) - 0.98*msu2(2,2))) + (2.0824656393169514*(-0.99*(-5.88*msu2(2,2) +
      0.99*Sqr(mAInput))*Sqr(mAInput) + TDelta(0.99*Sqr(mAInput),0.98*msu2(2,2),
      0.98*msu2(2,2)))*TPhi(0.99*Sqr(mAInput),0.98*msu2(2,2),0.98*msu2(2,2)))/((
      1.02*msq2(2,2) - 0.98*msu2(2,2))*Sqr(msu2(2,2)))) + 3*(AtInput + MuInput*
      TanBeta)*Cube(AtInput - MuInput/TanBeta)*((-12*Log(0.98*msu2(2,2))*(1.02*
      msq2(2,2) + 2.94*msu2(2,2)))/Cube(1.02*msq2(2,2) - 0.98*msu2(2,2)) + Log(
      1.02*msq2(2,2))*((12*Log(Sqr(SCALE))*(1.02*msq2(2,2) + 0.98*msu2(2,2)))/Cube
      (1.02*msq2(2,2) - 0.98*msu2(2,2)) + (12*(3.06*msq2(2,2) + 0.98*msu2(2,2)))
      /Cube(1.02*msq2(2,2) - 0.98*msu2(2,2)) + (2*Log(0.98*msu2(2,2))*(3.06*msq2(2
      ,2) + 0.98*msu2(2,2) - 1.98*Sqr(mAInput)))/Cube(1.02*msq2(2,2) - 0.98*msu2(2
      ,2))) + Log(0.99*Sqr(mAInput))*((2*Log(1.02*msq2(2,2))*(1.02*msq2(2,2) -
      0.98*msu2(2,2) - 5.9399999999999995*Sqr(mAInput)))/Cube(1.02*msq2(2,2) -
      0.98*msu2(2,2)) + (2*Log(0.98*msu2(2,2))*(-1.02*msq2(2,2) + 0.98*msu2(2,2) +
      5.9399999999999995*Sqr(mAInput)))/Cube(1.02*msq2(2,2) - 0.98*msu2(2,2))) +
      (2*(-5.1*msq2(2,2) - 2.94*msu2(2,2) + 3.96*Sqr(mAInput))*Sqr(Log(1.02*msq2(2
      ,2))))/Cube(1.02*msq2(2,2) - 0.98*msu2(2,2)) + (4*(1.02*msq2(2,2) + 0.98*
      msu2(2,2) - 0.99*Sqr(mAInput))*Sqr(Log(0.98*msu2(2,2))))/Cube(1.02*msq2(2,2)
      - 0.98*msu2(2,2)) + Log(Sqr(SCALE))*((-12*Log(0.98*msu2(2,2))*(1.02*msq2(2,
      2) + 0.98*msu2(2,2)))/Cube(1.02*msq2(2,2) - 0.98*msu2(2,2)) - 24/Sqr(1.02*
      msq2(2,2) - 0.98*msu2(2,2))) - 48/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)) + (
      1.9223375624759709*(0.99*(1.02*msq2(2,2) - 0.98*msu2(2,2))*(
      -7.140000000000001*msq2(2,2) + 0.99*Sqr(mAInput))*Sqr(mAInput) + (-5.1*msq2(
      2,2) + 0.98*msu2(2,2))*TDelta(0.99*Sqr(mAInput),1.02*msq2(2,2),1.02*msq2(2,2
      )))*TPhi(0.99*Sqr(mAInput),1.02*msq2(2,2),1.02*msq2(2,2)))/(Cube(1.02*msq2(2
      ,2) - 0.98*msu2(2,2))*Sqr(msq2(2,2))) - (1.9607843137254901*((1.02*msq2(2,2)
      - 0.98*msu2(2,2))*(1.02*msq2(2,2) - 0.98*msu2(2,2) + 0.99*Sqr(mAInput)) - 2
      *TDelta(0.99*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2)))*TPhi(0.99*Sqr(
      mAInput),0.98*msu2(2,2),1.02*msq2(2,2)))/(Cube(1.02*msq2(2,2) - 0.98*msu2(2,
      2))*msq2(2,2)) + (2.0824656393169514*(0.99*(1.02*msq2(2,2) - 0.98*msu2(2,2))
      *(-5.88*msu2(2,2) + 0.99*Sqr(mAInput))*Sqr(mAInput) - (1.02*msq2(2,2) - 2.94
      *msu2(2,2))*TDelta(0.99*Sqr(mAInput),0.98*msu2(2,2),0.98*msu2(2,2)))*TPhi(
      0.99*Sqr(mAInput),0.98*msu2(2,2),0.98*msu2(2,2)))/(Cube(1.02*msq2(2,2) -
      0.98*msu2(2,2))*Sqr(msu2(2,2)))) + Sqr(AtInput - MuInput/TanBeta)*(3*Sqr(
      AtInput + MuInput*TanBeta)*((3*Sqr(Log(1.02*msq2(2,2))))/Sqr(1.02*msq2(2,2)
      - 0.98*msu2(2,2)) + (2*Sqr(Log(0.98*msu2(2,2))))/Sqr(1.02*msq2(2,2) - 0.98*
      msu2(2,2)) + (4.08*msq2(2,2) - 1.96*msu2(2,2))/(1.019592*msu2(2,2)*Sqr(msq2(
      2,2)) - 0.9796079999999999*msq2(2,2)*Sqr(msu2(2,2))) + Log(Sqr(SCALE))*((2*
      Log(0.98*msu2(2,2)))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)) + (4.08*msq2(2,2)
      - 1.96*msu2(2,2))/(1.019592*msu2(2,2)*Sqr(msq2(2,2)) - 0.9796079999999999*
      msq2(2,2)*Sqr(msu2(2,2)))) + (1.0004001600640255*Log(0.98*msu2(2,2))*(-((
      1.02*msq2(2,2) - 0.98*msu2(2,2))*(0.9801*(2.04*msq2(2,2) + 0.98*msu2(2,2))*
      Quad(mAInput) - 4.0392*msq2(2,2)*(1.02*msq2(2,2) + 1.96*msu2(2,2))*Sqr(
      mAInput) + (2.04*msq2(2,2) - 0.98*msu2(2,2))*Sqr(1.02*msq2(2,2) - 0.98*msu2(
      2,2)))*TDelta(0.99*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2))) + TDelta(
      0.99*Sqr(mAInput),1.02*msq2(2,2),0.98*msu2(2,2))*(1.9992*msq2(2,2)*(1.02*
      msq2(2,2) - 0.98*msu2(2,2))*msu2(2,2)*(1.02*msq2(2,2) - 0.98*msu2(2,2) +
      0.99*Sqr(mAInput)) + (0.9996*msq2(2,2)*msu2(2,2) + 2.0808*Sqr(msq2(2,2)) -
      0.9603999999999999*Sqr(msu2(2,2)))*TDelta(0.99*Sqr(mAInput),0.98*msu2(2,2),
      1.02*msq2(2,2)))))/(msq2(2,2)*msu2(2,2)*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))
      *TDelta(0.99*Sqr(mAInput),1.02*msq2(2,2),0.98*msu2(2,2))*TDelta(0.99*Sqr(
      mAInput),0.98*msu2(2,2),1.02*msq2(2,2))) + Log(1.02*msq2(2,2))*((-5*Log(0.98
      *msu2(2,2)))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)) - (2*Log(Sqr(SCALE)))/Sqr(
      1.02*msq2(2,2) - 0.98*msu2(2,2)) + (1.0412328196584757*((1.02*msq2(2,2) -
      0.98*msu2(2,2))*(-0.9702989999999999*Power6(mAInput) + 0.9801*(3.06*msq2(2,2
      ) + 3.92*msu2(2,2))*Quad(mAInput) + 1.02*msq2(2,2)*Sqr(1.02*msq2(2,2) - 0.98
      *msu2(2,2)) - 0.99*Sqr(mAInput)*(1.9992*msq2(2,2)*msu2(2,2) + 3.1212*Sqr(
      msq2(2,2)) + 6.722799999999999*Sqr(msu2(2,2))))*TDelta(0.99*Sqr(mAInput),
      0.98*msu2(2,2),1.02*msq2(2,2)) + TDelta(0.99*Sqr(mAInput),1.02*msq2(2,2),
      0.98*msu2(2,2))*(-0.98*(1.02*msq2(2,2) - 0.98*msu2(2,2))*msu2(2,2)*(-0.9801*
      Quad(mAInput) + 1.9404*msu2(2,2)*Sqr(mAInput) + 1.0404*Sqr(msq2(2,2)) -
      0.9603999999999999*Sqr(msu2(2,2))) + (-1.9992*msq2(2,2)*msu2(2,2) + 0.99*(
      1.02*msq2(2,2) - 0.98*msu2(2,2))*Sqr(mAInput) - 1.0404*Sqr(msq2(2,2)) +
      0.9603999999999999*Sqr(msu2(2,2)))*TDelta(0.99*Sqr(mAInput),0.98*msu2(2,2),
      1.02*msq2(2,2)))))/(Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))*Sqr(msu2(2,2))*
      TDelta(0.99*Sqr(mAInput),1.02*msq2(2,2),0.98*msu2(2,2))*TDelta(0.99*Sqr(
      mAInput),0.98*msu2(2,2),1.02*msq2(2,2)))) + Log(0.99*Sqr(mAInput))*(Log(1.02
      *msq2(2,2))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)) - Log(0.98*msu2(2,2))/Sqr(
      1.02*msq2(2,2) - 0.98*msu2(2,2)) + (1.0208164898612506*((0.98970498*msq2(2,2
      )*Power6(mAInput) - Quad(1.02*msq2(2,2) - 0.98*msu2(2,2)) + 1.0098*msq2(2,2)
      *Sqr(mAInput)*(-1.9992*msq2(2,2)*msu2(2,2) + 3.1212*Sqr(msq2(2,2)) -
      0.9603999999999999*Sqr(msu2(2,2))) + 0.9801*Quad(mAInput)*(-1.9992*msq2(2,2)
      *msu2(2,2) - 3.1212*Sqr(msq2(2,2)) + 0.9603999999999999*Sqr(msu2(2,2))))*
      TDelta(0.99*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2)) + TDelta(0.99*Sqr(
      mAInput),1.02*msq2(2,2),0.98*msu2(2,2))*(0.9996*msq2(2,2)*msu2(2,2)*(-0.9801
      *Quad(mAInput) + Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) + (-2.9988*msq2(2,2)*
      msu2(2,2) - 1.0098*msq2(2,2)*Sqr(mAInput) + 1.0404*Sqr(msq2(2,2)) +
      0.9603999999999999*Sqr(msu2(2,2)))*TDelta(0.99*Sqr(mAInput),0.98*msu2(2,2),
      1.02*msq2(2,2)))))/(msq2(2,2)*(1.02*msq2(2,2) - 0.98*msu2(2,2))*Sqr(msu2(2,2
      ))*TDelta(0.99*Sqr(mAInput),1.02*msq2(2,2),0.98*msu2(2,2))*TDelta(0.99*Sqr(
      mAInput),0.98*msu2(2,2),1.02*msq2(2,2)))) + (0.9611687812379854*(0.99*(
      -7.140000000000001*msq2(2,2) + 0.99*Sqr(mAInput))*Sqr(mAInput) - TDelta(0.99
      *Sqr(mAInput),1.02*msq2(2,2),1.02*msq2(2,2)))*TPhi(0.99*Sqr(mAInput),1.02*
      msq2(2,2),1.02*msq2(2,2)))/(Sqr(msq2(2,2))*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,
      2))) + (1.062482469039261*(-((1.02*msq2(2,2) - 0.98*msu2(2,2))*(
      -3.8811959999999996*(1.02*msq2(2,2) + 0.98*msu2(2,2))*Power6(mAInput) +
      0.96059601*Power8(mAInput) + Quad(1.02*msq2(2,2) - 0.98*msu2(2,2)) -
      4.119984*(1.02*msq2(2,2) - 0.98*msu2(2,2))*Sqr(mAInput)*Sqr(msq2(2,2)) +
      0.9801*Quad(mAInput)*(3.9984*msq2(2,2)*msu2(2,2) + 6.2424*Sqr(msq2(2,2)) +
      5.7623999999999995*Sqr(msu2(2,2))))) - 2*(1.02*msq2(2,2) - 1.96*msu2(2,2))*
      Sqr(TDelta(0.99*Sqr(mAInput),1.02*msq2(2,2),0.98*msu2(2,2))) + (0.9801*(3.06
      *msq2(2,2) - 4.9*msu2(2,2))*Quad(mAInput) + (3.06*msq2(2,2) - 4.9*msu2(2,2))
      *Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)) + 0.99*Sqr(mAInput)*(3.9984*msq2(2,2)*
      msu2(2,2) - 6.2424*Sqr(msq2(2,2)) + 13.445599999999999*Sqr(msu2(2,2))))*
      TDelta(0.99*Sqr(mAInput),1.02*msq2(2,2),0.98*msu2(2,2)))*TPhi(0.99*Sqr(
      mAInput),1.02*msq2(2,2),0.98*msu2(2,2)))/(Cube(msu2(2,2))*Sqr(1.02*msq2(2,2)
      - 0.98*msu2(2,2))*TDelta(0.99*Sqr(mAInput),1.02*msq2(2,2),0.98*msu2(2,2)))
      + (0.9803921568627451*((1.02*msq2(2,2) - 0.98*msu2(2,2))*Sqr(0.99*Sqr(
      mAInput) + 1.02*msq2(2,2) - 0.98*msu2(2,2)) + 0.99*Sqr(mAInput)*TDelta(0.99*
      Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2)))*TPhi(0.99*Sqr(mAInput),0.98*
      msu2(2,2),1.02*msq2(2,2)))/(msq2(2,2)*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))*
      TDelta(0.99*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2))) + (
      1.0412328196584757*(0.99*(-5.88*msu2(2,2) + 0.99*Sqr(mAInput))*Sqr(mAInput)
      - TDelta(0.99*Sqr(mAInput),0.98*msu2(2,2),0.98*msu2(2,2)))*TPhi(0.99*Sqr(
      mAInput),0.98*msu2(2,2),0.98*msu2(2,2)))/(Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2
      ))*Sqr(msu2(2,2)))) + 3*((-2*Sqr(Log(0.98*msu2(2,2))))/(1.02*msq2(2,2) -
      0.98*msu2(2,2)) + Log(1.02*msq2(2,2))*((1.02*msq2(2,2) + 2.94*msu2(2,2) -
      1.98*Sqr(mAInput))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)) + (Log(0.98*msu2(2,2
      ))*(1.02*msq2(2,2) + 0.98*msu2(2,2) - 0.99*Sqr(mAInput)))/Sqr(1.02*msq2(2,2)
      - 0.98*msu2(2,2)) - (2*Log(Sqr(SCALE))*(-1.02*msq2(2,2) + 0.99*Sqr(mAInput)
      ))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) + Log(0.99*Sqr(mAInput))*((
      1.9807923169267705*(-2.04*msq2(2,2) + 0.98*msu2(2,2))*Sqr(mAInput))/(msq2(2,
      2)*(1.02*msq2(2,2) - 0.98*msu2(2,2))*msu2(2,2)) + (Log(1.02*msq2(2,2))*(-5.1
      *msq2(2,2) + 4.9*msu2(2,2) + 0.99*Sqr(mAInput)))/Sqr(1.02*msq2(2,2) - 0.98*
      msu2(2,2)) - (Log(0.98*msu2(2,2))*(-5.1*msq2(2,2) + 4.9*msu2(2,2) + 0.99*Sqr
      (mAInput)))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) + (Log(0.98*msu2(2,2))*(
      1.02*msq2(2,2) - 4.9*msu2(2,2) + 1.98*Sqr(mAInput)))/Sqr(1.02*msq2(2,2) -
      0.98*msu2(2,2)) + ((1.02*msq2(2,2) - 2.94*msu2(2,2) + 0.99*Sqr(mAInput))*Sqr
      (Log(1.02*msq2(2,2))))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)) + (-3.9984*msq2(
      2,2)*msu2(2,2) + 4.0392*msq2(2,2)*Sqr(mAInput) - 1.9404*msu2(2,2)*Sqr(
      mAInput))/(1.019592*msu2(2,2)*Sqr(msq2(2,2)) - 0.9796079999999999*msq2(2,2)*
      Sqr(msu2(2,2))) + Log(Sqr(SCALE))*((2*Log(0.98*msu2(2,2))*(-1.02*msq2(2,2) +
      0.99*Sqr(mAInput)))/Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)) + (-1.9992*msq2(2,
      2)*msu2(2,2) + 4.0392*msq2(2,2)*Sqr(mAInput) - 1.9404*msu2(2,2)*Sqr(mAInput)
      )/(1.019592*msu2(2,2)*Sqr(msq2(2,2)) - 0.9796079999999999*msq2(2,2)*Sqr(msu2
      (2,2)))) + (0.9611687812379854*(0.99*(1.02*msq2(2,2) - 0.98*msu2(2,2))*(
      -7.140000000000001*msq2(2,2) + 0.99*Sqr(mAInput))*Sqr(mAInput) + (-2.04*msq2
      (2,2) + 0.98*msu2(2,2))*TDelta(0.99*Sqr(mAInput),1.02*msq2(2,2),1.02*msq2(2,
      2)))*TPhi(0.99*Sqr(mAInput),1.02*msq2(2,2),1.02*msq2(2,2)))/(Sqr(msq2(2,2))*
      Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) + (0.9803921568627451*TDelta(0.99*Sqr(
      mAInput),0.98*msu2(2,2),1.02*msq2(2,2))*TPhi(0.99*Sqr(mAInput),0.98*msu2(2,2
      ),1.02*msq2(2,2)))/(msq2(2,2)*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) + (
      1.0412328196584757*(-0.99*(-5.88*msu2(2,2) + 0.99*Sqr(mAInput))*Sqr(mAInput)
      + TDelta(0.99*Sqr(mAInput),0.98*msu2(2,2),0.98*msu2(2,2)))*TPhi(0.99*Sqr(
      mAInput),0.98*msu2(2,2),0.98*msu2(2,2)))/((1.02*msq2(2,2) - 0.98*msu2(2,2))*
      Sqr(msu2(2,2))))) + Quad(AtInput - MuInput/TanBeta)*(3*(Log(Sqr(SCALE))*((
      1.0004001600640255*(5.9976*msq2(2,2)*(1.02*msq2(2,2) - 0.98*msu2(2,2))*msu2(
      2,2) + 0.99*Sqr(mAInput)*(-4.998*msq2(2,2)*msu2(2,2) - 2.0808*Sqr(msq2(2,2))
      + 0.9603999999999999*Sqr(msu2(2,2)))))/(Cube(1.02*msq2(2,2) - 0.98*msu2(2,2
      ))*msq2(2,2)*msu2(2,2)) + (3*Log(0.98*msu2(2,2))*(-2.0196*msq2(2,2)*Sqr(
      mAInput) + 1.0404*Sqr(msq2(2,2)) - 0.9603999999999999*Sqr(msu2(2,2))))/Quad(
      1.02*msq2(2,2) - 0.98*msu2(2,2))) + (1.0004001600640255*(2.9988*msq2(2,2)*(
      1.02*msq2(2,2) - 0.98*msu2(2,2))*msu2(2,2) + 0.99*Sqr(mAInput)*(-4.998*msq2(
      2,2)*msu2(2,2) - 2.0808*Sqr(msq2(2,2)) + 0.9603999999999999*Sqr(msu2(2,2))))
      )/(Cube(1.02*msq2(2,2) - 0.98*msu2(2,2))*msq2(2,2)*msu2(2,2)) + Log(0.99*Sqr
      (mAInput))*((1.0004001600640255*(5.9976*msq2(2,2)*(-1.02*msq2(2,2) + 0.98*
      msu2(2,2))*msu2(2,2) + 0.99*Sqr(mAInput)*(4.998*msq2(2,2)*msu2(2,2) + 2.0808
      *Sqr(msq2(2,2)) - 0.9603999999999999*Sqr(msu2(2,2)))))/(Cube(1.02*msq2(2,2)
      - 0.98*msu2(2,2))*msq2(2,2)*msu2(2,2)) + (3*Log(1.02*msq2(2,2))*(-2.0196*
      msq2(2,2)*Sqr(mAInput) + 1.0404*Sqr(msq2(2,2)) - 0.9603999999999999*Sqr(msu2
      (2,2))))/Quad(1.02*msq2(2,2) - 0.98*msu2(2,2)) + (3*Log(0.98*msu2(2,2))*(
      2.0196*msq2(2,2)*Sqr(mAInput) - 1.0404*Sqr(msq2(2,2)) + 0.9603999999999999*
      Sqr(msu2(2,2))))/Quad(1.02*msq2(2,2) - 0.98*msu2(2,2))) + Log(1.02*msq2(2,2)
      )*((3*Log(Sqr(SCALE))*(2.0196*msq2(2,2)*Sqr(mAInput) - 1.0404*Sqr(msq2(2,2))
      + 0.9603999999999999*Sqr(msu2(2,2))))/Quad(1.02*msq2(2,2) - 0.98*msu2(2,2))
      + (1.5*(4.0392*msq2(2,2)*Sqr(mAInput) - 1.0404*Sqr(msq2(2,2)) +
      0.9603999999999999*Sqr(msu2(2,2))))/Quad(1.02*msq2(2,2) - 0.98*msu2(2,2))) +
      (1.5*Log(0.98*msu2(2,2))*(-4.0392*msq2(2,2)*Sqr(mAInput) + 1.0404*Sqr(msq2(
      2,2)) - 0.9603999999999999*Sqr(msu2(2,2))))/Quad(1.02*msq2(2,2) - 0.98*msu2(
      2,2))) + 3*Sqr(AtInput + MuInput*TanBeta)*(((-11.22*msq2(2,2) - 2.94*msu2(2,
      2) + 6.93*Sqr(mAInput))*Sqr(Log(1.02*msq2(2,2))))/Quad(1.02*msq2(2,2) - 0.98
      *msu2(2,2)) - (2*(1.02*msq2(2,2) + 2.94*msu2(2,2) - 1.98*Sqr(mAInput))*Sqr(
      Log(0.98*msu2(2,2))))/Quad(1.02*msq2(2,2) - 0.98*msu2(2,2)) + Log(Sqr(SCALE)
      )*((-6.12*Log(0.98*msu2(2,2))*msq2(2,2))/Quad(1.02*msq2(2,2) - 0.98*msu2(2,2
      )) + (1.0004001600640255*(-4.998*msq2(2,2)*msu2(2,2) - 2.0808*Sqr(msq2(2,2))
      + 0.9603999999999999*Sqr(msu2(2,2))))/(Cube(1.02*msq2(2,2) - 0.98*msu2(2,2)
      )*msq2(2,2)*msu2(2,2))) + (1.0004001600640255*(-10.9956*msq2(2,2)*msu2(2,2)
      - 2.0808*Sqr(msq2(2,2)) + 0.9603999999999999*Sqr(msu2(2,2))))/(Cube(1.02*
      msq2(2,2) - 0.98*msu2(2,2))*msq2(2,2)*msu2(2,2)) - (0.5002000800320128*Log(
      0.98*msu2(2,2))*(Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))*(-3.183624*Cube(msq2(2
      ,2)) - 2.8235759999999996*Cube(msu2(2,2)) + 0.9702989999999999*Power6(
      mAInput) - 0.9801*(5.1*msq2(2,2) + 2.94*msu2(2,2))*Quad(mAInput) + 11.215512
      *msu2(2,2)*Sqr(msq2(2,2)) - 4.89804*msq2(2,2)*Sqr(msu2(2,2)) + 0.99*Sqr(
      mAInput)*(3.9984*msq2(2,2)*msu2(2,2) + 7.2828*Sqr(msq2(2,2)) + 4.802*Sqr(
      msu2(2,2))))*TDelta(0.99*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2)) +
      TDelta(0.99*Sqr(mAInput),1.02*msq2(2,2),0.98*msu2(2,2))*(1.9992*msq2(2,2)*
      msu2(2,2)*(1.02*msq2(2,2) - 0.98*msu2(2,2) + 0.99*Sqr(mAInput))*Sqr(1.02*
      msq2(2,2) - 0.98*msu2(2,2)) + (3.183624*Cube(msq2(2,2)) + 0.9411919999999999
      *Cube(msu2(2,2)) + 7.137144*msu2(2,2)*Sqr(msq2(2,2)) - 0.99*Sqr(mAInput)*Sqr
      (1.02*msq2(2,2) - 0.98*msu2(2,2)) + 12.734903999999998*msq2(2,2)*Sqr(msu2(2,
      2)))*TDelta(0.99*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2)))))/(msq2(2,2)*
      msu2(2,2)*Quad(1.02*msq2(2,2) - 0.98*msu2(2,2))*TDelta(0.99*Sqr(mAInput),
      1.02*msq2(2,2),0.98*msu2(2,2))*TDelta(0.99*Sqr(mAInput),0.98*msu2(2,2),1.02*
      msq2(2,2))) + Log(0.99*Sqr(mAInput))*((-3*Log(1.02*msq2(2,2))*(-1.02*msq2(2,
      2) + 0.98*msu2(2,2) + 0.99*Sqr(mAInput)))/Quad(1.02*msq2(2,2) - 0.98*msu2(2,
      2)) + (3*Log(0.98*msu2(2,2))*(-1.02*msq2(2,2) + 0.98*msu2(2,2) + 0.99*Sqr(
      mAInput)))/Quad(1.02*msq2(2,2) - 0.98*msu2(2,2)) + (0.5104082449306253*((
      1.02*msq2(2,2) - 0.98*msu2(2,2))*(1.061208*Cube(msq2(2,2)) +
      2.8235759999999996*Cube(msu2(2,2)) - 0.9702989999999999*Power6(mAInput) +
      2.9402999999999997*(1.02*msq2(2,2) + 0.98*msu2(2,2))*Quad(mAInput) -
      3.058776*msu2(2,2)*Sqr(msq2(2,2)) - 0.9796079999999999*msq2(2,2)*Sqr(msu2(2,
      2)) - 0.99*Sqr(mAInput)*(3.1212*Sqr(msq2(2,2)) + 4.802*Sqr(msu2(2,2))))*
      TDelta(0.99*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2)) + TDelta(0.99*Sqr(
      mAInput),1.02*msq2(2,2),0.98*msu2(2,2))*(-0.9996*msq2(2,2)*msu2(2,2)*(
      -0.9801*Quad(mAInput) + Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))) + (2.9988*msq2
      (2,2)*msu2(2,2) + 0.99*(1.02*msq2(2,2) - 0.98*msu2(2,2))*Sqr(mAInput) -
      1.0404*Sqr(msq2(2,2)) + 2.8811999999999998*Sqr(msu2(2,2)))*TDelta(0.99*Sqr(
      mAInput),0.98*msu2(2,2),1.02*msq2(2,2)))))/(msq2(2,2)*Sqr(1.02*msq2(2,2) -
      0.98*msu2(2,2))*Sqr(msu2(2,2))*TDelta(0.99*Sqr(mAInput),1.02*msq2(2,2),0.98*
      msu2(2,2))*TDelta(0.99*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2)))) + Log(
      1.02*msq2(2,2))*((6.12*Log(Sqr(SCALE))*msq2(2,2))/Quad(1.02*msq2(2,2) - 0.98
      *msu2(2,2)) + (Log(0.98*msu2(2,2))*(13.26*msq2(2,2) + 8.82*msu2(2,2) - 10.89
      *Sqr(mAInput)))/Quad(1.02*msq2(2,2) - 0.98*msu2(2,2)) + (0.5206164098292378*
      (Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))*(-1.061208*Cube(msq2(2,2)) - 8.470728*
      Cube(msu2(2,2)) + 0.9702989999999999*Power6(mAInput) - 0.9801*(3.06*msq2(2,2
      ) + 4.9*msu2(2,2))*Quad(mAInput) + 1.019592*msu2(2,2)*Sqr(msq2(2,2)) +
      8.816472*msq2(2,2)*Sqr(msu2(2,2)) + 0.99*Sqr(mAInput)*(3.9984*msq2(2,2)*msu2
      (2,2) + 3.1212*Sqr(msq2(2,2)) + 8.6436*Sqr(msu2(2,2))))*TDelta(0.99*Sqr(
      mAInput),0.98*msu2(2,2),1.02*msq2(2,2)) + TDelta(0.99*Sqr(mAInput),1.02*msq2
      (2,2),0.98*msu2(2,2))*(0.98*msu2(2,2)*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))*(
      -0.9801*Quad(mAInput) + 1.9404*msu2(2,2)*Sqr(mAInput) + 1.0404*Sqr(msq2(2,2)
      ) - 0.9603999999999999*Sqr(msu2(2,2))) + (1.061208*Cube(msq2(2,2)) +
      3.7647679999999997*Cube(msu2(2,2)) + 2.039184*msu2(2,2)*Sqr(msq2(2,2)) -
      0.99*Sqr(mAInput)*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)) + 16.653336*msq2(2,2)
      *Sqr(msu2(2,2)))*TDelta(0.99*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2)))))/
      (Quad(1.02*msq2(2,2) - 0.98*msu2(2,2))*Sqr(msu2(2,2))*TDelta(0.99*Sqr(
      mAInput),1.02*msq2(2,2),0.98*msu2(2,2))*TDelta(0.99*Sqr(mAInput),0.98*msu2(2
      ,2),1.02*msq2(2,2)))) + (0.9611687812379854*(0.99*(1.02*msq2(2,2) - 0.98*
      msu2(2,2))*(-7.140000000000001*msq2(2,2) + 0.99*Sqr(mAInput))*Sqr(mAInput) +
      (-8.16*msq2(2,2) + 0.98*msu2(2,2))*TDelta(0.99*Sqr(mAInput),1.02*msq2(2,2),
      1.02*msq2(2,2)))*TPhi(0.99*Sqr(mAInput),1.02*msq2(2,2),1.02*msq2(2,2)))/(
      Quad(1.02*msq2(2,2) - 0.98*msu2(2,2))*Sqr(msq2(2,2))) + (0.5312412345196305*
      (Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))*(-3.8811959999999996*(1.02*msq2(2,2) +
      0.98*msu2(2,2))*Power6(mAInput) + 0.96059601*Power8(mAInput) - 3.96*(1.02*
      msq2(2,2) + 0.98*msu2(2,2))*Sqr(mAInput)*Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2)
      ) + Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))*(-1.9992*msq2(2,2)*msu2(2,2) +
      1.0404*Sqr(msq2(2,2)) - 2.8811999999999998*Sqr(msu2(2,2))) + 0.9801*Quad(
      mAInput)*(3.9984*msq2(2,2)*msu2(2,2) + 6.2424*Sqr(msq2(2,2)) +
      5.7623999999999995*Sqr(msu2(2,2)))) + 2*(-4.998*msq2(2,2)*msu2(2,2) + 1.0404
      *Sqr(msq2(2,2)) + 11.524799999999999*Sqr(msu2(2,2)))*Sqr(TDelta(0.99*Sqr(
      mAInput),1.02*msq2(2,2),0.98*msu2(2,2))) - (1.02*msq2(2,2) - 0.98*msu2(2,2))
      *(3.183624*Cube(msq2(2,2)) - 16.000263999999998*Cube(msu2(2,2)) +
      2.9402999999999997*(1.02*msq2(2,2) - 2.94*msu2(2,2))*Quad(mAInput) -
      15.29388*msu2(2,2)*Sqr(msq2(2,2)) - 5.9399999999999995*Sqr(mAInput)*(-1.9992
      *msq2(2,2)*msu2(2,2) + 1.0404*Sqr(msq2(2,2)) - 2.8811999999999998*Sqr(msu2(2
      ,2))) + 28.408631999999997*msq2(2,2)*Sqr(msu2(2,2)))*TDelta(0.99*Sqr(mAInput
      ),1.02*msq2(2,2),0.98*msu2(2,2)))*TPhi(0.99*Sqr(mAInput),1.02*msq2(2,2),0.98
      *msu2(2,2)))/(Cube(msu2(2,2))*Quad(1.02*msq2(2,2) - 0.98*msu2(2,2))*TDelta(
      0.99*Sqr(mAInput),1.02*msq2(2,2),0.98*msu2(2,2))) - (0.49019607843137253*(
      Sqr(1.02*msq2(2,2) - 0.98*msu2(2,2))*Sqr(0.99*Sqr(mAInput) + 1.02*msq2(2,2)
      - 0.98*msu2(2,2)) - 6*Sqr(TDelta(0.99*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(
      2,2))) + (1.02*msq2(2,2) - 0.98*msu2(2,2))*(3.06*msq2(2,2) - 2.94*msu2(2,2)
      + 3.96*Sqr(mAInput))*TDelta(0.99*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2))
      )*TPhi(0.99*Sqr(mAInput),0.98*msu2(2,2),1.02*msq2(2,2)))/(msq2(2,2)*Quad(
      1.02*msq2(2,2) - 0.98*msu2(2,2))*TDelta(0.99*Sqr(mAInput),0.98*msu2(2,2),
      1.02*msq2(2,2))) + (1.0412328196584757*(0.99*(-1.02*msq2(2,2) + 0.98*msu2(2,
      2))*(-5.88*msu2(2,2) + 0.99*Sqr(mAInput))*Sqr(mAInput) + (1.02*msq2(2,2) -
      4.9*msu2(2,2))*TDelta(0.99*Sqr(mAInput),0.98*msu2(2,2),0.98*msu2(2,2)))*TPhi
      (0.99*Sqr(mAInput),0.98*msu2(2,2),0.98*msu2(2,2)))/(Quad(1.02*msq2(2,2) -
      0.98*msu2(2,2))*Sqr(msu2(2,2))))))/(1 + Sqr(TanBeta))))/Sqr(TanBeta)))/Quad(
      3.141592653589793)), 0) + IF(TwoLoopAtauAtau >= 1, (0.01171875*(((AtauInput
      - MuInput*TanBeta)*Quad(Yd(2,2))*((AbInput - MuInput*TanBeta)*(Log(1.03*msq2
      (2,2))*(4/(0.97*msd2(2,2) - 1.03*msq2(2,2)) + (4.04*Log(1.01*mse2(2,2))*mse2
      (2,2))/((-1.01*mse2(2,2) + 0.99*msl2(2,2))*(0.97*msd2(2,2) - 1.03*msq2(2,2))
      )) + (4*Log(1.03*msq2(2,2))*Log(Sqr(SCALE)))/(0.97*msd2(2,2) - 1.03*msq2(2,2
      )) + (3.96*Log(0.99*msl2(2,2))*Log(1.03*msq2(2,2))*msl2(2,2))/((1.01*mse2(2,
      2) - 0.99*msl2(2,2))*(0.97*msd2(2,2) - 1.03*msq2(2,2))) + Log(0.97*msd2(2,2)
      )*((4.04*Log(1.01*mse2(2,2))*mse2(2,2))/((1.01*mse2(2,2) - 0.99*msl2(2,2))*(
      0.97*msd2(2,2) - 1.03*msq2(2,2))) + (3.96*Log(0.99*msl2(2,2))*msl2(2,2))/((
      -1.01*mse2(2,2) + 0.99*msl2(2,2))*(0.97*msd2(2,2) - 1.03*msq2(2,2))) + 4/(
      -0.97*msd2(2,2) + 1.03*msq2(2,2)) + (4*Log(Sqr(SCALE)))/(-0.97*msd2(2,2) +
      1.03*msq2(2,2)))) + Cube(AbInput - MuInput*TanBeta)*(Log(1.03*msq2(2,2))*((
      -4*(0.97*msd2(2,2) + 1.03*msq2(2,2)))/Cube(0.97*msd2(2,2) - 1.03*msq2(2,2))
      - (4.04*Log(1.01*mse2(2,2))*mse2(2,2)*(0.97*msd2(2,2) + 1.03*msq2(2,2)))/(
      Cube(0.97*msd2(2,2) - 1.03*msq2(2,2))*(-1.01*mse2(2,2) + 0.99*msl2(2,2)))) +
      Log(0.97*msd2(2,2))*((4*(0.97*msd2(2,2) + 1.03*msq2(2,2)))/Cube(0.97*msd2(2
      ,2) - 1.03*msq2(2,2)) + (4*Log(Sqr(SCALE))*(0.97*msd2(2,2) + 1.03*msq2(2,2))
      )/Cube(0.97*msd2(2,2) - 1.03*msq2(2,2)) + (4.04*Log(1.01*mse2(2,2))*mse2(2,2
      )*(0.97*msd2(2,2) + 1.03*msq2(2,2)))/(Cube(0.97*msd2(2,2) - 1.03*msq2(2,2))*
      (-1.01*mse2(2,2) + 0.99*msl2(2,2))) + (3.96*Log(0.99*msl2(2,2))*msl2(2,2)*(
      0.97*msd2(2,2) + 1.03*msq2(2,2)))/(Cube(0.97*msd2(2,2) - 1.03*msq2(2,2))*(
      1.01*mse2(2,2) - 0.99*msl2(2,2)))) + Log(Sqr(SCALE))*((-4*Log(1.03*msq2(2,2)
      )*(0.97*msd2(2,2) + 1.03*msq2(2,2)))/Cube(0.97*msd2(2,2) - 1.03*msq2(2,2)) -
      8/Sqr(0.97*msd2(2,2) - 1.03*msq2(2,2))) + Log(0.99*msl2(2,2))*((3.96*Log(
      1.03*msq2(2,2))*msl2(2,2)*(0.97*msd2(2,2) + 1.03*msq2(2,2)))/(Cube(0.97*msd2
      (2,2) - 1.03*msq2(2,2))*(-1.01*mse2(2,2) + 0.99*msl2(2,2))) + (7.92*msl2(2,2
      ))/((-1.01*mse2(2,2) + 0.99*msl2(2,2))*Sqr(0.97*msd2(2,2) - 1.03*msq2(2,2)))
      ) - 8/Sqr(0.97*msd2(2,2) - 1.03*msq2(2,2)) + (8.08*Log(1.01*mse2(2,2))*mse2(
      2,2))/((1.01*mse2(2,2) - 0.99*msl2(2,2))*Sqr(0.97*msd2(2,2) - 1.03*msq2(2,2)
      ))))*Sqr(Ye(2,2)))/(Quad(1 + (0.0625*(1 + Sqr(TanBeta))*(0.25*Log(Sqr(
      MuInput)/Sqr(SCALE)) + (0.125*(-1 + 2*Log(Sqr(mAInput)/Sqr(SCALE))))/(1 +
      Sqr(TanBeta)) + ((-1 + Log(Sqr(mAInput)/Sqr(SCALE)))*Sqr(TanBeta))/(1 + Sqr(
      TanBeta)))*Sqr(Yu(2,2)))/(Sqr(3.141592653589793)*Sqr(TanBeta)) + 0.5*((
      -0.03125*Sqr(AbInput - MuInput*TanBeta)*Sqr(Yd(2,2))*TCF(5)(Sqrt(Abs(msq2(2,
      2)/msd2(2,2)))))/(Sqrt(Abs(msd2(2,2)*msq2(2,2)))*Sqr(3.141592653589793)) - (
      0.03125*Sqr(AtInput - MuInput/TanBeta)*Sqr(Yu(2,2))*TCF(5)(Sqrt(Abs(msq2(2,2
      )/msu2(2,2)))))/(Sqrt(Abs(msq2(2,2)*msu2(2,2)))*Sqr(3.141592653589793))) + (
      0.0625*(1 + Sqr(TanBeta))*Sqr(Yd(2,2))*(0.75*Log(Sqr(MuInput)/Sqr(SCALE)) +
      (0.375*(-1 + 2*Log(Sqr(mAInput)/Sqr(SCALE)))*Sqr(TanBeta))/(1 + Sqr(TanBeta)
      ) + 0.5*TCF(6)(Sqrt(msd2(2,2))/MuInput) + TCF(6)(Sqrt(msq2(2,2))/MuInput)))
      /Sqr(3.141592653589793) + (0.08333333333333333*Sqr(g3)*(1 + Log(Sqr(M3Input)
      /Sqr(SCALE)) + TCF(6)(Sqrt(msd2(2,2))/M3Input) + TCF(6)(Sqrt(msq2(2,2))
      /M3Input) - ((AbInput - MuInput*TanBeta)*TCF(9)(Sqrt(msq2(2,2))/M3Input,Sqrt
      (msd2(2,2))/M3Input))/M3Input))/Sqr(3.141592653589793) + (0.0625*(1 + Sqr(
      TanBeta))*Sqr(Yu(2,2))*(0.5*TCF(6)(Sqrt(msu2(2,2))/MuInput) + (0.5*(AtInput
      - MuInput/TanBeta)*TanBeta*TCF(9)(Sqrt(msq2(2,2))/MuInput,Sqrt(msu2(2,2))
      /MuInput))/MuInput))/(Sqr(3.141592653589793)*Sqr(TanBeta)))*Sqrt(1/(1 + Sqr(
      TanBeta)))*Sqrt(Sqr(TanBeta)/(1 + Sqr(TanBeta)))) + (Quad(Ye(2,2))*((AbInput
      - MuInput*TanBeta)*(AtauInput - MuInput*TanBeta)*((4*Log(1.01*mse2(2,2)))/(
      -1.01*mse2(2,2) + 0.99*msl2(2,2)) + (4*Log(1.01*mse2(2,2))*Log(Sqr(SCALE)))/
      (-1.01*mse2(2,2) + 0.99*msl2(2,2)) + Log(0.97*msd2(2,2))*((3.88*Log(1.01*
      mse2(2,2))*msd2(2,2))/((1.01*mse2(2,2) - 0.99*msl2(2,2))*(0.97*msd2(2,2) -
      1.03*msq2(2,2))) + (3.88*Log(0.99*msl2(2,2))*msd2(2,2))/((-1.01*mse2(2,2) +
      0.99*msl2(2,2))*(0.97*msd2(2,2) - 1.03*msq2(2,2)))) + (4.12*Log(1.01*mse2(2,
      2))*Log(1.03*msq2(2,2))*msq2(2,2))/((-1.01*mse2(2,2) + 0.99*msl2(2,2))*(0.97
      *msd2(2,2) - 1.03*msq2(2,2))) + Log(0.99*msl2(2,2))*(4/(1.01*mse2(2,2) -
      0.99*msl2(2,2)) + (4*Log(Sqr(SCALE)))/(1.01*mse2(2,2) - 0.99*msl2(2,2)) + (
      4.12*Log(1.03*msq2(2,2))*msq2(2,2))/((-1.01*mse2(2,2) + 0.99*msl2(2,2))*(
      -0.97*msd2(2,2) + 1.03*msq2(2,2))))) + (AbInput - MuInput*TanBeta)*Cube(
      AtauInput - MuInput*TanBeta)*((-4*Log(1.01*mse2(2,2))*(1.01*mse2(2,2) + 0.99
      *msl2(2,2)))/Cube(-1.01*mse2(2,2) + 0.99*msl2(2,2)) + Log(0.99*msl2(2,2))*((
      4*(1.01*mse2(2,2) + 0.99*msl2(2,2)))/Cube(-1.01*mse2(2,2) + 0.99*msl2(2,2))
      + (4*Log(Sqr(SCALE))*(1.01*mse2(2,2) + 0.99*msl2(2,2)))/Cube(-1.01*mse2(2,2)
      + 0.99*msl2(2,2)) + (4.12*Log(1.03*msq2(2,2))*(1.01*mse2(2,2) + 0.99*msl2(2
      ,2))*msq2(2,2))/(Cube(-1.01*mse2(2,2) + 0.99*msl2(2,2))*(0.97*msd2(2,2) -
      1.03*msq2(2,2)))) + Log(Sqr(SCALE))*((-4*Log(1.01*mse2(2,2))*(1.01*mse2(2,2)
      + 0.99*msl2(2,2)))/Cube(-1.01*mse2(2,2) + 0.99*msl2(2,2)) - 8/Sqr(-1.01*
      mse2(2,2) + 0.99*msl2(2,2))) + Log(0.97*msd2(2,2))*((3.88*Log(1.01*mse2(2,2)
      )*msd2(2,2)*(1.01*mse2(2,2) + 0.99*msl2(2,2)))/(Cube(-1.01*mse2(2,2) + 0.99*
      msl2(2,2))*(0.97*msd2(2,2) - 1.03*msq2(2,2))) - (3.88*Log(0.99*msl2(2,2))*
      msd2(2,2)*(1.01*mse2(2,2) + 0.99*msl2(2,2)))/(Cube(-1.01*mse2(2,2) + 0.99*
      msl2(2,2))*(0.97*msd2(2,2) - 1.03*msq2(2,2))) + (7.76*msd2(2,2))/((0.97*msd2
      (2,2) - 1.03*msq2(2,2))*Sqr(-1.01*mse2(2,2) + 0.99*msl2(2,2)))) + Log(1.03*
      msq2(2,2))*((-4.12*Log(1.01*mse2(2,2))*(1.01*mse2(2,2) + 0.99*msl2(2,2))*
      msq2(2,2))/(Cube(-1.01*mse2(2,2) + 0.99*msl2(2,2))*(0.97*msd2(2,2) - 1.03*
      msq2(2,2))) + (8.24*msq2(2,2))/((-0.97*msd2(2,2) + 1.03*msq2(2,2))*Sqr(-1.01
      *mse2(2,2) + 0.99*msl2(2,2)))) - 8/Sqr(-1.01*mse2(2,2) + 0.99*msl2(2,2))))*
      Sqr(Yd(2,2)))/(Sqrt(1/(1 + Sqr(TanBeta)))*Sqrt(Sqr(TanBeta)/(1 + Sqr(TanBeta
      )))*Sqr(1 + (0.006332573977646111*(1 + Sqr(TanBeta))*(0.25*Log(Sqr(MuInput)
      /Sqr(SCALE)) + (0.125*(-1 + 2*Log(Sqr(mAInput)/Sqr(SCALE))))/(1 + Sqr(
      TanBeta)) + ((-1 + Log(Sqr(mAInput)/Sqr(SCALE)))*Sqr(TanBeta))/(1 + Sqr(
      TanBeta)))*Sqr(Yu(2,2)))/Sqr(TanBeta) + 0.5*((-0.0031662869888230555*Sqr(
      AbInput - MuInput*TanBeta)*Sqr(Yd(2,2))*TCF(5)(Sqrt(Abs(msq2(2,2)/msd2(2,2))
      )))/Sqrt(Abs(msd2(2,2)*msq2(2,2))) - (0.0031662869888230555*Sqr(AtInput -
      MuInput/TanBeta)*Sqr(Yu(2,2))*TCF(5)(Sqrt(Abs(msq2(2,2)/msu2(2,2)))))/Sqrt(
      Abs(msq2(2,2)*msu2(2,2)))) + 0.006332573977646111*(1 + Sqr(TanBeta))*Sqr(Yd(
      2,2))*(0.75*Log(Sqr(MuInput)/Sqr(SCALE)) + (0.375*(-1 + 2*Log(Sqr(mAInput)
      /Sqr(SCALE)))*Sqr(TanBeta))/(1 + Sqr(TanBeta)) + 0.5*TCF(6)(Sqrt(msd2(2,2))
      /MuInput) + TCF(6)(Sqrt(msq2(2,2))/MuInput)) + 0.008443431970194815*Sqr(g3)*
      (1 + Log(Sqr(M3Input)/Sqr(SCALE)) + TCF(6)(Sqrt(msd2(2,2))/M3Input) + TCF(6)
      (Sqrt(msq2(2,2))/M3Input) - ((AbInput - MuInput*TanBeta)*TCF(9)(Sqrt(msq2(2,
      2))/M3Input,Sqrt(msd2(2,2))/M3Input))/M3Input) + (0.006332573977646111*(1 +
      Sqr(TanBeta))*Sqr(Yu(2,2))*(0.5*TCF(6)(Sqrt(msu2(2,2))/MuInput) + (0.5*(
      AtInput - MuInput/TanBeta)*TanBeta*TCF(9)(Sqrt(msq2(2,2))/MuInput,Sqrt(msu2(
      2,2))/MuInput))/MuInput))/Sqr(TanBeta)))))/Quad(3.141592653589793) + (
      0.00390625*Power6(Ye(2,2))*(5 - 4*Log(1.01*mse2(2,2)) + Log(0.99*msl2(2,2))*
      (-6 - 6*Log(Sqr(SCALE))) + (10 - 4*Log(1.01*mse2(2,2)))*Log(Sqr(SCALE)) + 5*
      Sqr(Log(Sqr(SCALE))) + 2*Sqr(Log(1.01*mse2(2,2))) + 3*Sqr(Log(0.99*msl2(2,2)
      )) + Power6(AtauInput - MuInput*TanBeta)*((4*PolyLog(2,(1.0101010101010102*(
      -1.01*mse2(2,2) + 0.99*msl2(2,2)))/msl2(2,2)))/Cube(-1.01*mse2(2,2) + 0.99*
      msl2(2,2)) - (2*PolyLog(2,1 - (0.9801980198019802*msl2(2,2))/mse2(2,2)))
      /Cube(-1.01*mse2(2,2) + 0.99*msl2(2,2)) + ((-5.05*mse2(2,2) -
      2.9699999999999998*msl2(2,2))*Sqr(Log(1.01*mse2(2,2))))/Quad(-1.01*mse2(2,2)
      + 0.99*msl2(2,2)) + ((-5.05*mse2(2,2) - 8.91*msl2(2,2))*Sqr(Log(0.99*msl2(2
      ,2))))/Quad(-1.01*mse2(2,2) + 0.99*msl2(2,2)) + Log(Sqr(SCALE))*((
      -5.9399999999999995*Log(1.01*mse2(2,2))*msl2(2,2))/Quad(-1.01*mse2(2,2) +
      0.99*msl2(2,2)) + (1.000100010001*(-4.9995*mse2(2,2)*msl2(2,2) + 1.0201*Sqr(
      mse2(2,2)) - 1.9602*Sqr(msl2(2,2))))/(Cube(-1.01*mse2(2,2) + 0.99*msl2(2,2))
      *mse2(2,2)*msl2(2,2))) + (1.0101010101010102*Log(1.01*mse2(2,2))*(-2.9997*
      mse2(2,2)*msl2(2,2) + 1.0201*Sqr(mse2(2,2)) - 9.801*Sqr(msl2(2,2))))/(msl2(2
      ,2)*Quad(-1.01*mse2(2,2) + 0.99*msl2(2,2))) + (1.000100010001*(-10.9989*mse2
      (2,2)*msl2(2,2) + 1.0201*Sqr(mse2(2,2)) - 1.9602*Sqr(msl2(2,2))))/(Cube(
      -1.01*mse2(2,2) + 0.99*msl2(2,2))*mse2(2,2)*msl2(2,2)) + Log(0.99*msl2(2,2))
      *((5.9399999999999995*Log(Sqr(SCALE))*msl2(2,2))/Quad(-1.01*mse2(2,2) + 0.99
      *msl2(2,2)) + (2*Log(1.01*mse2(2,2))*(5.05*mse2(2,2) + 5.9399999999999995*
      msl2(2,2)))/Quad(-1.01*mse2(2,2) + 0.99*msl2(2,2)) + (0.9900990099009901*(
      12.9987*mse2(2,2)*msl2(2,2) - 3.0603*Sqr(mse2(2,2)) + 1.9602*Sqr(msl2(2,2)))
      )/(mse2(2,2)*Quad(-1.01*mse2(2,2) + 0.99*msl2(2,2))))) + Quad(AtauInput -
      MuInput*TanBeta)*(((5.05*mse2(2,2) + 2.9699999999999998*msl2(2,2))*Sqr(Log(
      1.01*mse2(2,2))))/Cube(-1.01*mse2(2,2) + 0.99*msl2(2,2)) + ((-9.09*mse2(2,2)
      - 6.93*msl2(2,2))*Sqr(Log(0.99*msl2(2,2))))/Cube(-1.01*mse2(2,2) + 0.99*
      msl2(2,2)) - (6*PolyLog(2,1 - (0.9801980198019802*msl2(2,2))/mse2(2,2)))/Sqr
      (-1.01*mse2(2,2) + 0.99*msl2(2,2)) + Log(0.99*msl2(2,2))*((4*Log(1.01*mse2(2
      ,2))*(1.01*mse2(2,2) + 0.99*msl2(2,2)))/Cube(-1.01*mse2(2,2) + 0.99*msl2(2,2
      )) + (2*Log(Sqr(SCALE))*(7.07*mse2(2,2) + 4.95*msl2(2,2)))/Cube(-1.01*mse2(2
      ,2) + 0.99*msl2(2,2)) - (3.9603960396039604*(-9.999*mse2(2,2)*msl2(2,2) -
      3.0603*Sqr(mse2(2,2)) + 0.9801*Sqr(msl2(2,2))))/(Cube(-1.01*mse2(2,2) + 0.99
      *msl2(2,2))*mse2(2,2))) + (1.0101010101010102*Log(1.01*mse2(2,2))*(-43.9956*
      mse2(2,2)*msl2(2,2) + 2.0402*Sqr(mse2(2,2)) - 5.880599999999999*Sqr(msl2(2,2
      ))))/(Cube(-1.01*mse2(2,2) + 0.99*msl2(2,2))*msl2(2,2)) + (2.000200020002*(
      -26.9973*mse2(2,2)*msl2(2,2) + 1.0201*Sqr(mse2(2,2)) + 1.9602*Sqr(msl2(2,2))
      ))/(mse2(2,2)*msl2(2,2)*Sqr(-1.01*mse2(2,2) + 0.99*msl2(2,2))) + Log(Sqr(
      SCALE))*((-2*Log(1.01*mse2(2,2))*(7.07*mse2(2,2) + 4.95*msl2(2,2)))/Cube(
      -1.01*mse2(2,2) + 0.99*msl2(2,2)) + (2.000200020002*(-14.9985*mse2(2,2)*msl2
      (2,2) + 1.0201*Sqr(mse2(2,2)) + 1.9602*Sqr(msl2(2,2))))/(mse2(2,2)*msl2(2,2)
      *Sqr(-1.01*mse2(2,2) + 0.99*msl2(2,2))))) + Sqr(AtauInput - MuInput*TanBeta)
      *((-6*PolyLog(2,1 - (0.9801980198019802*msl2(2,2))/mse2(2,2)))/(-1.01*mse2(2
      ,2) + 0.99*msl2(2,2)) - (9*Sqr(Log(1.01*mse2(2,2))))/(-1.01*mse2(2,2) + 0.99
      *msl2(2,2)) + ((-9.09*mse2(2,2) + 6.93*msl2(2,2))*Sqr(Log(0.99*msl2(2,2))))
      /Sqr(-1.01*mse2(2,2) + 0.99*msl2(2,2)) + Log(Sqr(SCALE))*((2*Log(1.01*mse2(2
      ,2))*(-9.09*mse2(2,2) + 7.92*msl2(2,2)))/Sqr(-1.01*mse2(2,2) + 0.99*msl2(2,2
      )) + (1.000100010001*(-0.9999*mse2(2,2)*msl2(2,2) + 1.0201*Sqr(mse2(2,2)) -
      1.9602*Sqr(msl2(2,2))))/(mse2(2,2)*(-1.01*mse2(2,2) + 0.99*msl2(2,2))*msl2(2
      ,2))) + (1.000100010001*(-2.9997*mse2(2,2)*msl2(2,2) + 1.0201*Sqr(mse2(2,2))
      - 1.9602*Sqr(msl2(2,2))))/(mse2(2,2)*(-1.01*mse2(2,2) + 0.99*msl2(2,2))*
      msl2(2,2)) + (1.0101010101010102*Log(1.01*mse2(2,2))*(-20.997899999999998*
      mse2(2,2)*msl2(2,2) + 1.0201*Sqr(mse2(2,2)) + 15.6816*Sqr(msl2(2,2))))/(msl2
      (2,2)*Sqr(-1.01*mse2(2,2) + 0.99*msl2(2,2))) + Log(0.99*msl2(2,2))*((1.98*
      Log(1.01*mse2(2,2))*msl2(2,2))/Sqr(-1.01*mse2(2,2) + 0.99*msl2(2,2)) - (2*
      Log(Sqr(SCALE))*(-9.09*mse2(2,2) + 7.92*msl2(2,2)))/Sqr(-1.01*mse2(2,2) +
      0.99*msl2(2,2)) + (0.9900990099009901*(-16.998299999999997*mse2(2,2)*msl2(2,
      2) + 19.3819*Sqr(mse2(2,2)) + 1.9602*Sqr(msl2(2,2))))/(mse2(2,2)*Sqr(-1.01*
      mse2(2,2) + 0.99*msl2(2,2))))) + (1 + Sqr(TanBeta))*(Log(Sqr(SCALE))*(Log(
      1.01*mse2(2,2)) - (1.000100010001*(1.01*mse2(2,2) + 1.98*msl2(2,2))*(1.01*
      mse2(2,2) + 0.99*msl2(2,2) - 1.9*Sqr(MuInput)))/(mse2(2,2)*msl2(2,2))) - 2*
      Sqr(Log(Sqr(SCALE))) + (0.5000500050005*(3.4294999999999995*(1.01*mse2(2,2)
      + 1.98*msl2(2,2))*Power6(MuInput) - 0.9999*mse2(2,2)*msl2(2,2)*(2.9997*mse2(
      2,2)*msl2(2,2) + 2.0402*Sqr(mse2(2,2)) + 3.9204*Sqr(msl2(2,2))) - 2.7075*
      Quad(MuInput)*(6.9993*mse2(2,2)*msl2(2,2) + 2.0402*Sqr(mse2(2,2)) + 3.9204*
      Sqr(msl2(2,2))) + 0.95*Sqr(MuInput)*(2.060602*Cube(mse2(2,2)) +
      3.8811959999999996*Cube(msl2(2,2)) + 13.128687000000001*msl2(2,2)*Sqr(mse2(2
      ,2)) + 16.828317000000002*mse2(2,2)*Sqr(msl2(2,2)))))/(mse2(2,2)*msl2(2,2)*(
      -1.01*mse2(2,2) + 0.95*Sqr(MuInput))*(-0.99*msl2(2,2) + 0.95*Sqr(MuInput)))
      + (3.61*PolyLog(2,(1.0526315789473684*(-0.99*msl2(2,2) + 0.95*Sqr(MuInput)))
      /Sqr(MuInput))*Quad(MuInput))/Sqr(0.99*msl2(2,2) - 0.95*Sqr(MuInput)) - (
      1.98*msl2(2,2)*(0.99*msl2(2,2) - 1.9*Sqr(MuInput))*Sqr(Log(0.99*msl2(2,2))))
      /Sqr(0.99*msl2(2,2) - 0.95*Sqr(MuInput)) + (2*PolyLog(2,1 - (
      1.0421052631578946*msl2(2,2))/Sqr(MuInput))*(0.9025*Quad(MuInput) + 1.881*
      msl2(2,2)*Sqr(MuInput) - 0.9801*Sqr(msl2(2,2))))/Sqr(0.99*msl2(2,2) - 0.95*
      Sqr(MuInput)) + Sqr(AtauInput - MuInput*TanBeta)*((4*PolyLog(2,1 - (
      1.063157894736842*mse2(2,2))/Sqr(MuInput))*(0.99*msl2(2,2) - 0.95*Sqr(
      MuInput)))/Sqr(-1.01*mse2(2,2) + 0.99*msl2(2,2)) + (4*PolyLog(2,(
      1.0526315789473684*(-0.99*msl2(2,2) + 0.95*Sqr(MuInput)))/Sqr(MuInput))*(
      -0.99*msl2(2,2) + 0.95*Sqr(MuInput)))/Sqr(-1.01*mse2(2,2) + 0.99*msl2(2,2))
      + (5.9994*mse2(2,2)*msl2(2,2) + 3.8379999999999996*mse2(2,2)*Sqr(MuInput) -
      7.524*msl2(2,2)*Sqr(MuInput) - 2.0402*Sqr(mse2(2,2)) + 3.9204*Sqr(msl2(2,2))
      )/(-1.009899*msl2(2,2)*Sqr(mse2(2,2)) + 0.989901*mse2(2,2)*Sqr(msl2(2,2))) +
      (1.0101010101010102*Log(1.01*mse2(2,2))*(0.9702989999999999*Cube(msl2(2,2))
      *(-11.11*mse2(2,2) + 4.75*Sqr(MuInput)) + 1.9381899999999999*(-1.01*mse2(2,2
      ) + 0.95*Sqr(MuInput))*Sqr(MuInput)*Sqr(mse2(2,2)) + 0.99*msl2(2,2)*(
      2.060602*Cube(mse2(2,2)) + 3.4294999999999995*Power6(MuInput) - 11.849825*
      mse2(2,2)*Quad(MuInput) + 0.9690949999999999*Sqr(MuInput)*Sqr(mse2(2,2))) +
      0.9801*(-4.5125*Quad(MuInput) + 15.351999999999999*mse2(2,2)*Sqr(MuInput) +
      1.0201*Sqr(mse2(2,2)))*Sqr(msl2(2,2))))/(msl2(2,2)*(0.99*msl2(2,2) - 0.95*
      Sqr(MuInput))*(-1.01*mse2(2,2) + 0.95*Sqr(MuInput))*Sqr(-1.01*mse2(2,2) +
      0.99*msl2(2,2))) + Log(Sqr(SCALE))*((Log(1.01*mse2(2,2))*(7.92*msl2(2,2) - 2
      *(1.01*mse2(2,2) + 1.9*Sqr(MuInput))))/Sqr(-1.01*mse2(2,2) + 0.99*msl2(2,2))
      + (3.9996*mse2(2,2)*msl2(2,2) + 3.8379999999999996*mse2(2,2)*Sqr(MuInput) -
      7.524*msl2(2,2)*Sqr(MuInput) - 2.0402*Sqr(mse2(2,2)) + 3.9204*Sqr(msl2(2,2)
      ))/(-1.009899*msl2(2,2)*Sqr(mse2(2,2)) + 0.989901*mse2(2,2)*Sqr(msl2(2,2))))
      + (1.98*msl2(2,2)*Sqr(Log(0.99*msl2(2,2)))*(1.9998*mse2(2,2)*msl2(2,2) +
      4.5125*Quad(MuInput) - 3.8379999999999996*mse2(2,2)*Sqr(MuInput) -
      5.642999999999999*msl2(2,2)*Sqr(MuInput) + 2.9402999999999997*Sqr(msl2(2,2))
      ))/(Sqr(-1.01*mse2(2,2) + 0.99*msl2(2,2))*Sqr(0.99*msl2(2,2) - 0.95*Sqr(
      MuInput))) + Log(0.95*Sqr(MuInput))*((3.8003800380037998*Sqr(MuInput)*(
      0.9405*msl2(2,2)*(1.01*mse2(2,2) - 1.9*Sqr(MuInput))*Sqr(MuInput) +
      0.9594999999999999*mse2(2,2)*(-1.01*mse2(2,2) + 0.95*Sqr(MuInput))*Sqr(
      MuInput) + 0.9801*(-1.01*mse2(2,2) + 1.9*Sqr(MuInput))*Sqr(msl2(2,2))))/(
      mse2(2,2)*(-1.01*mse2(2,2) + 0.99*msl2(2,2))*msl2(2,2)*(0.99*msl2(2,2) -
      0.95*Sqr(MuInput))*(-1.01*mse2(2,2) + 0.95*Sqr(MuInput))) + (2*Log(1.01*mse2
      (2,2))*(1.547561875*Power10(MuInput) - 0.81450625*(7.07*mse2(2,2) +
      2.9699999999999998*msl2(2,2))*Power8(MuInput) - 1.9796040197999998*Cube(msl2
      (2,2))*Sqr(mse2(2,2)) + 1.8808118999999999*mse2(2,2)*(3.0300000000000002*
      mse2(2,2) + 1.98*msl2(2,2))*Sqr(MuInput)*Sqr(msl2(2,2)) + 1.7147499999999998
      *Power6(MuInput)*(4.9995*mse2(2,2)*msl2(2,2) + 3.0603*Sqr(mse2(2,2)) +
      1.9602*Sqr(msl2(2,2))) - 0.9025*Quad(MuInput)*(2.060602*Cube(mse2(2,2)) +
      0.9702989999999999*Cube(msl2(2,2)) + 4.039596*msl2(2,2)*Sqr(mse2(2,2)) +
      12.868713*mse2(2,2)*Sqr(msl2(2,2)))))/(Sqr(-1.01*mse2(2,2) + 0.99*msl2(2,2))
      *Sqr(0.99*msl2(2,2) - 0.95*Sqr(MuInput))*Sqr(-1.01*mse2(2,2) + 0.95*Sqr(
      MuInput)))) + Log(0.99*msl2(2,2))*((Log(Sqr(SCALE))*(2.02*mse2(2,2) - 7.92*
      msl2(2,2) + 3.8*Sqr(MuInput)))/Sqr(-1.01*mse2(2,2) + 0.99*msl2(2,2)) + (
      0.9900990099009901*(-3.8811959999999996*Cube(msl2(2,2))*(-1.01*mse2(2,2) +
      0.95*Sqr(MuInput)) + 0.9999*mse2(2,2)*msl2(2,2)*(4.5125*Quad(MuInput) -
      1.9189999999999998*mse2(2,2)*Sqr(MuInput) - 7.1407*Sqr(mse2(2,2))) -
      0.9594999999999999*mse2(2,2)*Sqr(MuInput)*(3.61*Quad(MuInput) - 6.7165*mse2(
      2,2)*Sqr(MuInput) + 1.0201*Sqr(mse2(2,2))) + 0.9801*(3.61*Quad(MuInput) -
      12.4735*mse2(2,2)*Sqr(MuInput) + 11.2211*Sqr(mse2(2,2)))*Sqr(msl2(2,2))))/(
      mse2(2,2)*(0.99*msl2(2,2) - 0.95*Sqr(MuInput))*(-1.01*mse2(2,2) + 0.95*Sqr(
      MuInput))*Sqr(-1.01*mse2(2,2) + 0.99*msl2(2,2))) + Log(1.01*mse2(2,2))*((
      -4.04*mse2(2,2))/Sqr(-1.01*mse2(2,2) + 0.99*msl2(2,2)) - (4*(1.01*mse2(2,2)
      + 0.99*msl2(2,2)))/Sqr(-1.01*mse2(2,2) + 0.99*msl2(2,2)) - (
      5.9399999999999995*msl2(2,2))/Sqr(-1.01*mse2(2,2) + 0.99*msl2(2,2)) + (3.96*
      msl2(2,2)*(0.99*msl2(2,2) - 1.9*Sqr(MuInput)))/((-1.01*mse2(2,2) + 0.99*msl2
      (2,2))*Sqr(0.99*msl2(2,2) - 0.95*Sqr(MuInput))) + (2.02*mse2(2,2)*(1.01*mse2
      (2,2) - 1.9*Sqr(MuInput)))/((1.01*mse2(2,2) - 0.99*msl2(2,2))*Sqr(-1.01*mse2
      (2,2) + 0.95*Sqr(MuInput)))) + (2*Log(0.95*Sqr(MuInput))*(-1.547561875*
      Power10(MuInput) + 0.81450625*(7.07*mse2(2,2) + 2.9699999999999998*msl2(2,2)
      )*Power8(MuInput) + 1.9796040197999998*Cube(msl2(2,2))*Sqr(mse2(2,2)) -
      1.8808118999999999*mse2(2,2)*(3.0300000000000002*mse2(2,2) + 1.98*msl2(2,2))
      *Sqr(MuInput)*Sqr(msl2(2,2)) - 1.7147499999999998*Power6(MuInput)*(4.9995*
      mse2(2,2)*msl2(2,2) + 3.0603*Sqr(mse2(2,2)) + 1.9602*Sqr(msl2(2,2))) +
      0.9025*Quad(MuInput)*(2.060602*Cube(mse2(2,2)) + 0.9702989999999999*Cube(
      msl2(2,2)) + 4.039596*msl2(2,2)*Sqr(mse2(2,2)) + 12.868713*mse2(2,2)*Sqr(
      msl2(2,2)))))/(Sqr(-1.01*mse2(2,2) + 0.99*msl2(2,2))*Sqr(0.99*msl2(2,2) -
      0.95*Sqr(MuInput))*Sqr(-1.01*mse2(2,2) + 0.95*Sqr(MuInput)))) + (2.02*mse2(2
      ,2)*Sqr(Log(1.01*mse2(2,2)))*(3.61*Quad(MuInput) + 0.99*msl2(2,2)*(1.01*mse2
      (2,2) - 1.9*Sqr(MuInput)) - 5.757*mse2(2,2)*Sqr(MuInput) + 3.0603*Sqr(mse2(2
      ,2))))/(Sqr(-1.01*mse2(2,2) + 0.99*msl2(2,2))*Sqr(-1.01*mse2(2,2) + 0.95*Sqr
      (MuInput)))) + Quad(AtauInput - MuInput*TanBeta)*((2*PolyLog(2,1 - (
      1.063157894736842*mse2(2,2))/Sqr(MuInput))*(-1.9998*mse2(2,2)*msl2(2,2) -
      2.7075*Quad(MuInput) + 5.643*msl2(2,2)*Sqr(MuInput) + 1.0201*Sqr(mse2(2,2))
      - 1.9602*Sqr(msl2(2,2))))/Quad(-1.01*mse2(2,2) + 0.99*msl2(2,2)) + (PolyLog(
      2,(1.0526315789473684*(-0.99*msl2(2,2) + 0.95*Sqr(MuInput)))/Sqr(MuInput))*(
      5.415*Quad(MuInput) + 3.96*msl2(2,2)*(1.01*mse2(2,2) - 2.8499999999999996*
      Sqr(MuInput)) - 2.0402*Sqr(mse2(2,2)) + 3.9204*Sqr(msl2(2,2))))/Quad(-1.01*
      mse2(2,2) + 0.99*msl2(2,2)) + (1.000100010001*(-1.92119202*Quad(msl2(2,2))*(
      -1.01*mse2(2,2) + 0.95*Sqr(MuInput)) + 0.9690949999999999*Sqr(MuInput)*Sqr(
      mse2(2,2))*(1.805*Quad(MuInput) - 2.8785*mse2(2,2)*Sqr(MuInput) + 1.0201*Sqr
      (mse2(2,2))) + 0.9702989999999999*Cube(msl2(2,2))*(5.415*Quad(MuInput) -
      34.541999999999994*mse2(2,2)*Sqr(MuInput) + 32.6432*Sqr(mse2(2,2))) - 0.9999
      *mse2(2,2)*msl2(2,2)*(1.030301*Cube(mse2(2,2)) + 13.717999999999998*Power6(
      MuInput) - 4.557625*mse2(2,2)*Quad(MuInput) - 13.567329999999998*Sqr(MuInput
      )*Sqr(mse2(2,2))) - 0.9801*(15.454514999999999*Cube(mse2(2,2)) +
      3.4294999999999995*Power6(MuInput) - 41.93015*mse2(2,2)*Quad(MuInput) +
      30.041945*Sqr(MuInput)*Sqr(mse2(2,2)))*Sqr(msl2(2,2))))/(Cube(-1.01*mse2(2,2
      ) + 0.99*msl2(2,2))*mse2(2,2)*msl2(2,2)*(0.99*msl2(2,2) - 0.95*Sqr(MuInput))
      *(-1.01*mse2(2,2) + 0.95*Sqr(MuInput))) + Log(Sqr(SCALE))*((Log(1.01*mse2(2,
      2))*(-5.9994*mse2(2,2)*msl2(2,2) + 11.286*msl2(2,2)*Sqr(MuInput) + 7.1407*
      Sqr(mse2(2,2)) - 12.741299999999999*Sqr(msl2(2,2))))/Quad(-1.01*mse2(2,2) +
      0.99*msl2(2,2)) + (1.000100010001*(-1.9405979999999998*Cube(msl2(2,2)) +
      9.999*mse2(2,2)*msl2(2,2)*(1.01*mse2(2,2) + 0.95*Sqr(MuInput)) + 1.0201*(
      1.01*mse2(2,2) - 1.9*Sqr(MuInput))*Sqr(mse2(2,2)) + 0.9801*(-21.21*mse2(2,2)
      + 3.8*Sqr(MuInput))*Sqr(msl2(2,2))))/(Cube(-1.01*mse2(2,2) + 0.99*msl2(2,2)
      )*mse2(2,2)*msl2(2,2))) - (1.98*msl2(2,2)*Sqr(Log(0.99*msl2(2,2)))*(4.851495
      *Cube(msl2(2,2)) + 0.9594999999999999*mse2(2,2)*Sqr(MuInput)*(-2.02*mse2(2,2
      ) + 4.75*Sqr(MuInput)) + 0.99*msl2(2,2)*(5.415*Quad(MuInput) - 9.595*mse2(2,
      2)*Sqr(MuInput) + 1.0201*Sqr(mse2(2,2))) + 4.9005*(1.01*mse2(2,2) - 1.9*Sqr(
      MuInput))*Sqr(msl2(2,2))))/(Quad(-1.01*mse2(2,2) + 0.99*msl2(2,2))*Sqr(0.99*
      msl2(2,2) - 0.95*Sqr(MuInput))) + Log(0.99*msl2(2,2))*((Log(Sqr(SCALE))*(
      5.9399999999999995*msl2(2,2)*(1.01*mse2(2,2) - 1.9*Sqr(MuInput)) - 7.1407*
      Sqr(mse2(2,2)) + 12.741299999999999*Sqr(msl2(2,2))))/Quad(-1.01*mse2(2,2) +
      0.99*msl2(2,2)) + (0.49504950495049505*(0.9298466524999999*Cube(mse2(2,2))*
      Quad(MuInput)*(15.15*mse2(2,2) - 12.35*Sqr(MuInput)) + 3.8039601995999996*
      Power5(msl2(2,2))*(-1.01*mse2(2,2) + 0.95*Sqr(MuInput)) + 0.96059601*Quad(
      msl2(2,2))*(-7.22*Quad(MuInput) + 73.88149999999999*mse2(2,2)*Sqr(MuInput) -
      72.4271*Sqr(mse2(2,2))) + 1.89981*mse2(2,2)*msl2(2,2)*Sqr(MuInput)*(
      -25.757524999999998*Cube(mse2(2,2)) - 15.432749999999999*Power6(MuInput) +
      3.6461*mse2(2,2)*Quad(MuInput) + 35.856514999999995*Sqr(MuInput)*Sqr(mse2(2,
      2))) + 1.9405979999999998*Cube(msl2(2,2))*(6.181806*Cube(mse2(2,2)) +
      1.7147499999999998*Power6(MuInput) - 79.302675*mse2(2,2)*Quad(MuInput) +
      78.49669499999999*Sqr(MuInput)*Sqr(mse2(2,2))) + 0.989901*mse2(2,2)*(
      27.818126999999997*Cube(mse2(2,2)) + 124.31937499999998*Power6(MuInput) -
      112.11757499999999*mse2(2,2)*Quad(MuInput) - 47.485654999999994*Sqr(MuInput)
      *Sqr(mse2(2,2)))*Sqr(msl2(2,2))))/(mse2(2,2)*Quad(-1.01*mse2(2,2) + 0.99*
      msl2(2,2))*(-1.01*mse2(2,2) + 0.95*Sqr(MuInput))*Sqr(0.99*msl2(2,2) - 0.95*
      Sqr(MuInput))) + Log(1.01*mse2(2,2))*((6.0600000000000005*mse2(2,2))/Cube(
      1.01*mse2(2,2) - 0.99*msl2(2,2)) + (9.9*msl2(2,2))/Cube(-1.01*mse2(2,2) +
      0.99*msl2(2,2)) + (21.9978*mse2(2,2)*msl2(2,2))/Quad(-1.01*mse2(2,2) + 0.99*
      msl2(2,2)) - 2/Sqr(-1.01*mse2(2,2) + 0.99*msl2(2,2)) + (4*Sqr(1.01*mse2(2,2)
      + 0.99*msl2(2,2)))/Quad(-1.01*mse2(2,2) + 0.99*msl2(2,2)) - (1.98*(1.01*
      mse2(2,2) + 0.99*msl2(2,2))*msl2(2,2)*(0.99*msl2(2,2) - 1.9*Sqr(MuInput)))/(
      Cube(-1.01*mse2(2,2) + 0.99*msl2(2,2))*Sqr(0.99*msl2(2,2) - 0.95*Sqr(MuInput
      ))) + (1.01*mse2(2,2)*(1.01*mse2(2,2) + 0.99*msl2(2,2))*(-1.01*mse2(2,2) +
      1.9*Sqr(MuInput)))/(Cube(1.01*mse2(2,2) - 0.99*msl2(2,2))*Sqr(-1.01*mse2(2,2
      ) + 0.95*Sqr(MuInput)))) + (Log(0.95*Sqr(MuInput))*(9.192517537499999*msl2(2
      ,2)*Power10(MuInput) + 1.99960002*Sqr(mse2(2,2))*(-1.9998*mse2(2,2)*msl2(2,2
      ) + 1.0201*Sqr(mse2(2,2)) - 1.9602*Sqr(msl2(2,2)))*Sqr(msl2(2,2)) +
      5.092807499999999*msl2(2,2)*Power6(MuInput)*(9.999*mse2(2,2)*msl2(2,2) +
      3.0603*Sqr(mse2(2,2)) + 2.9402999999999997*Sqr(msl2(2,2))) - 0.81450625*
      Power8(MuInput)*(27.9972*mse2(2,2)*msl2(2,2) + 1.0201*Sqr(mse2(2,2)) +
      24.502499999999998*Sqr(msl2(2,2))) + 3.79962*mse2(2,2)*msl2(2,2)*Sqr(MuInput
      )*(-1.030301*Cube(mse2(2,2)) + 1.9405979999999998*Cube(msl2(2,2)) + 1.009899
      *msl2(2,2)*Sqr(mse2(2,2)) + 6.9293070000000005*mse2(2,2)*Sqr(msl2(2,2))) -
      0.8934749999999999*msl2(2,2)*Quad(MuInput)*(-4.121204*Cube(mse2(2,2)) +
      2.910897*Cube(msl2(2,2)) + 41.40585900000001*msl2(2,2)*Sqr(mse2(2,2)) +
      43.555644*mse2(2,2)*Sqr(msl2(2,2)))))/(Quad(-1.01*mse2(2,2) + 0.99*msl2(2,2)
      )*Sqr(0.99*msl2(2,2) - 0.95*Sqr(MuInput))*Sqr(-1.01*mse2(2,2) + 0.95*Sqr(
      MuInput)))) + Log(0.95*Sqr(MuInput))*((-1.9001900190018999*Sqr(MuInput)*(
      -0.9206402499999999*Quad(MuInput)*Sqr(0.95*Sqr(MuInput) - 1.01*mse2(2,2))*
      Sqr(mse2(2,2)) + 0.9024097499999999*mse2(2,2)*msl2(2,2)*Quad(MuInput)*(1.805
      *Quad(MuInput) - 4.7975*mse2(2,2)*Sqr(MuInput) + 2.0402*Sqr(mse2(2,2))) +
      0.96059601*Quad(msl2(2,2))*(1.805*Quad(MuInput) - 2.8785*mse2(2,2)*Sqr(
      MuInput) + 2.0402*Sqr(mse2(2,2))) + 0.9702989999999999*Cube(msl2(2,2))*(
      2.060602*Cube(mse2(2,2)) - 3.4294999999999995*Power6(MuInput) + 7.2922*mse2(
      2,2)*Quad(MuInput) - 8.721855*Sqr(MuInput)*Sqr(mse2(2,2))) + 0.9801*(
      -4.32974375*mse2(2,2)*Power6(MuInput) + 1.6290125*Power8(MuInput) -
      1.04060401*Quad(mse2(2,2)) + 6.44448175*Quad(MuInput)*Sqr(mse2(2,2)))*Sqr(
      msl2(2,2))))/(Cube(-1.01*mse2(2,2) + 0.99*msl2(2,2))*mse2(2,2)*msl2(2,2)*Sqr
      (0.99*msl2(2,2) - 0.95*Sqr(MuInput))*Sqr(-1.01*mse2(2,2) + 0.95*Sqr(MuInput)
      )) + (Log(1.01*mse2(2,2))*(-9.1925175375*msl2(2,2)*Power10(MuInput) +
      1.99960002*Sqr(mse2(2,2))*Sqr(msl2(2,2))*(1.9998*mse2(2,2)*msl2(2,2) -
      1.0201*Sqr(mse2(2,2)) + 1.9602*Sqr(msl2(2,2))) - 5.092807499999999*msl2(2,2)
      *Power6(MuInput)*(9.999*mse2(2,2)*msl2(2,2) + 3.0603*Sqr(mse2(2,2)) +
      2.9402999999999997*Sqr(msl2(2,2))) + 0.81450625*Power8(MuInput)*(27.9972*
      mse2(2,2)*msl2(2,2) + 1.0201*Sqr(mse2(2,2)) + 24.502499999999998*Sqr(msl2(2,
      2))) - 3.79962*mse2(2,2)*msl2(2,2)*Sqr(MuInput)*(-1.030301*Cube(mse2(2,2)) +
      1.9405979999999998*Cube(msl2(2,2)) + 1.009899*msl2(2,2)*Sqr(mse2(2,2)) +
      6.9293070000000005*mse2(2,2)*Sqr(msl2(2,2))) + 0.8934749999999999*msl2(2,2)*
      Quad(MuInput)*(-4.121204*Cube(mse2(2,2)) + 2.910897*Cube(msl2(2,2)) +
      41.40585900000001*msl2(2,2)*Sqr(mse2(2,2)) + 43.555644*mse2(2,2)*Sqr(msl2(2,
      2)))))/(Quad(-1.01*mse2(2,2) + 0.99*msl2(2,2))*Sqr(0.99*msl2(2,2) - 0.95*Sqr
      (MuInput))*Sqr(-1.01*mse2(2,2) + 0.95*Sqr(MuInput)))) - (1.01*mse2(2,2)*(
      1.01*mse2(2,2) + 0.99*msl2(2,2))*Sqr(Log(1.01*mse2(2,2)))*(7.22*Quad(MuInput
      ) + 0.99*msl2(2,2)*(1.01*mse2(2,2) - 1.9*Sqr(MuInput)) - 13.433*mse2(2,2)*
      Sqr(MuInput) + 7.1407*Sqr(mse2(2,2))))/(Quad(-1.01*mse2(2,2) + 0.99*msl2(2,2
      ))*Sqr(-1.01*mse2(2,2) + 0.95*Sqr(MuInput))) + (0.5050505050505051*Log(1.01*
      mse2(2,2))*(-1.9575718999999998*Cube(mse2(2,2))*Sqr(MuInput)*Sqr(0.95*Sqr(
      MuInput) - 1.01*mse2(2,2)) + 0.96059601*Quad(msl2(2,2))*(-24.3675*Quad(
      MuInput) + 61.407999999999994*mse2(2,2)*Sqr(MuInput) - 33.6633*Sqr(mse2(2,2)
      )) + 0.9999*mse2(2,2)*msl2(2,2)*(-16.453026249999997*mse2(2,2)*Power6(
      MuInput) - 9.774075*Power8(MuInput) + 2.08120802*Quad(mse2(2,2)) -
      44.04536775*Cube(mse2(2,2))*Sqr(MuInput) + 64.4448175*Quad(MuInput)*Sqr(mse2
      (2,2))) + 0.9702989999999999*Cube(msl2(2,2))*(-51.515049999999995*Cube(mse2(
      2,2)) + 40.29662499999999*Power6(MuInput) - 147.66705*mse2(2,2)*Quad(MuInput
      ) + 148.271535*Sqr(MuInput)*Sqr(mse2(2,2))) + 0.9801*(102.1819525*mse2(2,2)*
      Power6(MuInput) - 19.54815*Power8(MuInput) + 46.82718045*Quad(mse2(2,2)) -
      25.448434699999996*Cube(mse2(2,2))*Sqr(MuInput) - 92.98466525*Quad(MuInput)*
      Sqr(mse2(2,2)))*Sqr(msl2(2,2))))/(msl2(2,2)*Quad(-1.01*mse2(2,2) + 0.99*msl2
      (2,2))*(0.99*msl2(2,2) - 0.95*Sqr(MuInput))*Sqr(-1.01*mse2(2,2) + 0.95*Sqr(
      MuInput)))) + Log(0.99*msl2(2,2))*(3*Log(Sqr(SCALE)) + (0.49504950495049505*
      (3.8811959999999996*Cube(msl2(2,2))*(-1.01*mse2(2,2) + 0.95*Sqr(MuInput)) +
      0.911525*mse2(2,2)*Quad(MuInput)*(-13.13*mse2(2,2) + 14.25*Sqr(MuInput)) +
      1.881*msl2(2,2)*Sqr(MuInput)*(1.805*Quad(MuInput) - 6.7165*mse2(2,2)*Sqr(
      MuInput) + 3.0603*Sqr(mse2(2,2))) + 0.9801*(-7.22*Quad(MuInput) +
      14.392499999999998*mse2(2,2)*Sqr(MuInput) - 5.1005*Sqr(mse2(2,2)))*Sqr(msl2(
      2,2))))/(mse2(2,2)*(-1.01*mse2(2,2) + 0.95*Sqr(MuInput))*Sqr(0.99*msl2(2,2)
      - 0.95*Sqr(MuInput))) + (Log(1.01*mse2(2,2))*(-1.7318974999999999*mse2(2,2)*
      Power6(MuInput) + 1.6290125*Power8(MuInput) + 0.911525*mse2(2,2)*(1.01*mse2(
      2,2) - 3.96*msl2(2,2))*Quad(MuInput) + 1.89981*mse2(2,2)*(1.01*mse2(2,2) +
      0.99*msl2(2,2))*msl2(2,2)*Sqr(MuInput) - 0.99980001*Sqr(mse2(2,2))*Sqr(msl2(
      2,2))))/(Sqr(0.99*msl2(2,2) - 0.95*Sqr(MuInput))*Sqr(-1.01*mse2(2,2) + 0.95*
      Sqr(MuInput))) + (Log(0.95*Sqr(MuInput))*(-1.7147499999999998*(-4.04*mse2(2,
      2) + 0.99*msl2(2,2))*Power6(MuInput) - 4.07253125*Power8(MuInput) - 3.79962*
      mse2(2,2)*(1.01*mse2(2,2) + 0.99*msl2(2,2))*msl2(2,2)*Sqr(MuInput) + 0.9025*
      Quad(MuInput)*(7.9992*mse2(2,2)*msl2(2,2) - 4.0804*Sqr(mse2(2,2)) + 0.9801*
      Sqr(msl2(2,2))) + 1.99960002*Sqr(mse2(2,2))*Sqr(msl2(2,2))))/(Sqr(0.99*msl2(
      2,2) - 0.95*Sqr(MuInput))*Sqr(-1.01*mse2(2,2) + 0.95*Sqr(MuInput)))) + Log(
      0.95*Sqr(MuInput))*((Log(1.01*mse2(2,2))*(1.6976024999999997*msl2(2,2)*
      Power6(MuInput) - 2.44351875*Power8(MuInput) - 0.8934749999999999*(-8.08*
      mse2(2,2) + 0.99*msl2(2,2))*msl2(2,2)*Quad(MuInput) - 3.79962*mse2(2,2)*(
      1.01*mse2(2,2) + 0.99*msl2(2,2))*msl2(2,2)*Sqr(MuInput) + 1.99960002*Sqr(
      mse2(2,2))*Sqr(msl2(2,2))))/(Sqr(0.99*msl2(2,2) - 0.95*Sqr(MuInput))*Sqr(
      -1.01*mse2(2,2) + 0.95*Sqr(MuInput))) + (0.9500950095009499*Sqr(MuInput)*(
      -1.6290125*(1.01*mse2(2,2) + 1.98*msl2(2,2))*Power8(MuInput) - 1.99960002*(
      1.01*mse2(2,2) + 0.99*msl2(2,2))*Sqr(mse2(2,2))*Sqr(msl2(2,2)) + 0.949905*
      mse2(2,2)*msl2(2,2)*Sqr(MuInput)*(7.9992*mse2(2,2)*msl2(2,2) - 2.0402*Sqr(
      mse2(2,2)) + 2.9402999999999997*Sqr(msl2(2,2))) + 0.8573749999999999*Power6(
      MuInput)*(0.9999*mse2(2,2)*msl2(2,2) + 4.0804*Sqr(mse2(2,2)) + 7.8408*Sqr(
      msl2(2,2))) - 1.805*Quad(MuInput)*(1.030301*Cube(mse2(2,2)) +
      1.9405979999999998*Cube(msl2(2,2)) - 1.009899*msl2(2,2)*Sqr(mse2(2,2)) +
      3.959604*mse2(2,2)*Sqr(msl2(2,2)))))/(mse2(2,2)*msl2(2,2)*Sqr(0.99*msl2(2,2)
      - 0.95*Sqr(MuInput))*Sqr(-1.01*mse2(2,2) + 0.95*Sqr(MuInput)))) + (1.01*
      mse2(2,2)*(-1.01*mse2(2,2) + 1.9*Sqr(MuInput))*Sqr(Log(1.01*mse2(2,2))))/Sqr
      (-1.01*mse2(2,2) + 0.95*Sqr(MuInput)) + (2*PolyLog(2,1 - (1.063157894736842*
      mse2(2,2))/Sqr(MuInput))*(0.9025*Quad(MuInput) + 1.9189999999999998*mse2(2,2
      )*Sqr(MuInput) - 1.0201*Sqr(mse2(2,2))))/Sqr(-1.01*mse2(2,2) + 0.95*Sqr(
      MuInput)) + (0.5050505050505051*Log(1.01*mse2(2,2))*(-1.9189999999999998*
      mse2(2,2)*Sqr(MuInput)*Sqr(0.95*Sqr(MuInput) - 1.01*mse2(2,2)) + 0.99*msl2(2
      ,2)*(2.060602*Cube(mse2(2,2)) - 11.145874999999998*Power6(MuInput) +
      12.76135*mse2(2,2)*Quad(MuInput) - 8.721855*Sqr(MuInput)*Sqr(mse2(2,2))) +
      0.9801*(8.1225*Quad(MuInput) - 3.8379999999999996*mse2(2,2)*Sqr(MuInput) +
      1.0201*Sqr(mse2(2,2)))*Sqr(msl2(2,2))))/(msl2(2,2)*(0.99*msl2(2,2) - 0.95*
      Sqr(MuInput))*Sqr(-1.01*mse2(2,2) + 0.95*Sqr(MuInput))) + (Sqr(Log(0.95*Sqr(
      MuInput)))*(-3.4637949999999997*mse2(2,2)*Power6(MuInput) + 3.258025*Power8(
      MuInput) + 1.82305*mse2(2,2)*(1.01*mse2(2,2) - 3.96*msl2(2,2))*Quad(MuInput)
      + 3.79962*mse2(2,2)*(1.01*mse2(2,2) + 0.99*msl2(2,2))*msl2(2,2)*Sqr(MuInput
      ) - 1.99960002*Sqr(mse2(2,2))*Sqr(msl2(2,2))))/(Sqr(0.99*msl2(2,2) - 0.95*
      Sqr(MuInput))*Sqr(-1.01*mse2(2,2) + 0.95*Sqr(MuInput)))) + Sqr(TanBeta)*(1.5
      - 2.5*Log(1.01*mse2(2,2)) + Log(0.99*msl2(2,2))*(-4.5 - 3*Log(Sqr(SCALE)))
      + Sqr(3.141592653589793) - (1.9504950495049505*Sqr(mAInput))/mse2(2,2) - (
      0.994949494949495*Sqr(mAInput))/msl2(2,2) + Log(0.985*Sqr(mAInput))*(7 - 3*
      Log(1.01*mse2(2,2)) - 3*Log(0.99*msl2(2,2)) + 0.985*(1.9801980198019802/mse2
      (2,2) + 1.0101010101010102/msl2(2,2))*Sqr(mAInput)) + Log(Sqr(SCALE))*(-Log(
      1.01*mse2(2,2)) - (0.985098509850985*(1.01*mse2(2,2) + 1.98*msl2(2,2))*Sqr(
      mAInput))/(mse2(2,2)*msl2(2,2))) + 3*Sqr(Log(0.985*Sqr(mAInput))) + 2*Sqr(
      Log(Sqr(SCALE))) + 2*Sqr(Log(1.01*mse2(2,2))) + 3*Sqr(Log(0.99*msl2(2,2))) +
      (0.9802960494069208*(0.970225*Quad(mAInput) - 5.9691*mse2(2,2)*Sqr(mAInput)
      - TDelta(0.985*Sqr(mAInput),1.01*mse2(2,2),1.01*mse2(2,2)))*TPhi(0.985*Sqr(
      mAInput),1.01*mse2(2,2),1.01*mse2(2,2)))/Sqr(mse2(2,2)) + Sqr(AtauInput +
      MuInput/TanBeta)*(-1.9801980198019802/mse2(2,2) + Log(Sqr(SCALE))*(
      -1.9801980198019802/mse2(2,2) - 1.0101010101010102/msl2(2,2)) -
      1.0101010101010102/msl2(2,2) + (0.4901480247034604*Log(0.99*msl2(2,2))*((
      -Cube(-1.01*mse2(2,2) + 0.99*msl2(2,2)) + 0.955671625*Power6(mAInput) -
      2.910675*(1.01*mse2(2,2) + 0.99*msl2(2,2))*Quad(mAInput) + 2.955*Sqr(mAInput
      )*(-1.0201*Sqr(mse2(2,2)) + 0.9801*Sqr(msl2(2,2))))*TDelta(0.985*Sqr(mAInput
      ),1.01*mse2(2,2),0.99*msl2(2,2)) + (-1.01*mse2(2,2)*(0.970225*Quad(mAInput)
      - 1.9897*mse2(2,2)*Sqr(mAInput) + 1.0201*Sqr(mse2(2,2)) - 0.9801*Sqr(msl2(2,
      2))) + (2.02*mse2(2,2) + 0.99*msl2(2,2) - 0.985*Sqr(mAInput))*TDelta(0.985*
      Sqr(mAInput),1.01*mse2(2,2),0.99*msl2(2,2)))*TDelta(0.985*Sqr(mAInput),0.99*
      msl2(2,2),1.01*mse2(2,2))))/(Sqr(mse2(2,2))*TDelta(0.985*Sqr(mAInput),1.01*
      mse2(2,2),0.99*msl2(2,2))*TDelta(0.985*Sqr(mAInput),0.99*msl2(2,2),1.01*mse2
      (2,2))) + (0.5000500050005*Log(1.01*mse2(2,2))*((Cube(-1.01*mse2(2,2) + 0.99
      *msl2(2,2)) + 0.955671625*Power6(mAInput) - 0.970225*(5.05*mse2(2,2) + 0.99*
      msl2(2,2))*Quad(mAInput) - 0.985*Sqr(mAInput)*(3.9996*mse2(2,2)*msl2(2,2) -
      5.1005*Sqr(mse2(2,2)) + 0.9801*Sqr(msl2(2,2))))*TDelta(0.985*Sqr(mAInput),
      1.01*mse2(2,2),0.99*msl2(2,2)) - (1.9998*mse2(2,2)*msl2(2,2)*(-1.01*mse2(2,2
      ) + 0.99*msl2(2,2) + 0.985*Sqr(mAInput)) + (-3.0300000000000002*mse2(2,2) +
      0.99*msl2(2,2) + 0.985*Sqr(mAInput))*TDelta(0.985*Sqr(mAInput),1.01*mse2(2,2
      ),0.99*msl2(2,2)))*TDelta(0.985*Sqr(mAInput),0.99*msl2(2,2),1.01*mse2(2,2)))
      )/(mse2(2,2)*msl2(2,2)*TDelta(0.985*Sqr(mAInput),1.01*mse2(2,2),0.99*msl2(2,
      2))*TDelta(0.985*Sqr(mAInput),0.99*msl2(2,2),1.01*mse2(2,2))) + (
      0.4950990148519802*Log(0.985*Sqr(mAInput))*((-0.955671625*(1.01*mse2(2,2) +
      0.99*msl2(2,2))*Power6(mAInput) + Quad(-1.01*mse2(2,2) + 0.99*msl2(2,2)) -
      0.985*(5.05*mse2(2,2) + 2.9699999999999998*msl2(2,2))*Sqr(mAInput)*Sqr(-1.01
      *mse2(2,2) + 0.99*msl2(2,2)) + 0.970225*Quad(mAInput)*(3.9996*mse2(2,2)*msl2
      (2,2) + 5.1005*Sqr(mse2(2,2)) + 2.9402999999999997*Sqr(msl2(2,2))))*TDelta(
      0.985*Sqr(mAInput),1.01*mse2(2,2),0.99*msl2(2,2)) + (-0.9999*mse2(2,2)*msl2(
      2,2)*(-0.970225*Quad(mAInput) + Sqr(-1.01*mse2(2,2) + 0.99*msl2(2,2))) + (
      2.9997*mse2(2,2)*msl2(2,2) + 0.985*(1.01*mse2(2,2) + 0.99*msl2(2,2))*Sqr(
      mAInput) - 1.0201*Sqr(mse2(2,2)) - 0.9801*Sqr(msl2(2,2)))*TDelta(0.985*Sqr(
      mAInput),1.01*mse2(2,2),0.99*msl2(2,2)))*TDelta(0.985*Sqr(mAInput),0.99*msl2
      (2,2),1.01*mse2(2,2))))/(msl2(2,2)*Sqr(mse2(2,2))*TDelta(0.985*Sqr(mAInput),
      1.01*mse2(2,2),0.99*msl2(2,2))*TDelta(0.985*Sqr(mAInput),0.99*msl2(2,2),1.01
      *mse2(2,2))) + (0.5050505050505051*(-Sqr(0.985*Sqr(mAInput) - 1.01*mse2(2,2)
      + 0.99*msl2(2,2)) + TDelta(0.985*Sqr(mAInput),1.01*mse2(2,2),0.99*msl2(2,2)
      ))*TPhi(0.985*Sqr(mAInput),1.01*mse2(2,2),0.99*msl2(2,2)))/(msl2(2,2)*TDelta
      (0.985*Sqr(mAInput),1.01*mse2(2,2),0.99*msl2(2,2))) + (0.48529507396382227*(
      -3.8226865*(1.01*mse2(2,2) + 0.99*msl2(2,2))*Power6(mAInput) +
      0.941336550625*Power8(mAInput) + Quad(-1.01*mse2(2,2) + 0.99*msl2(2,2)) -
      3.94*(1.01*mse2(2,2) + 0.99*msl2(2,2))*Sqr(mAInput)*Sqr(-1.01*mse2(2,2) +
      0.99*msl2(2,2)) + 1.94045*Quad(mAInput)*(1.9998*mse2(2,2)*msl2(2,2) + 1.0201
      *Sqr(mse2(2,2)) + 2.9402999999999997*Sqr(msl2(2,2))) + 2*Sqr(TDelta(0.985*
      Sqr(mAInput),0.99*msl2(2,2),1.01*mse2(2,2))) - 3*(0.970225*Quad(mAInput) -
      1.97*(1.01*mse2(2,2) + 0.99*msl2(2,2))*Sqr(mAInput) + Sqr(-1.01*mse2(2,2) +
      0.99*msl2(2,2)))*TDelta(0.985*Sqr(mAInput),0.99*msl2(2,2),1.01*mse2(2,2)))*
      TPhi(0.985*Sqr(mAInput),0.99*msl2(2,2),1.01*mse2(2,2)))/(Cube(mse2(2,2))*
      TDelta(0.985*Sqr(mAInput),0.99*msl2(2,2),1.01*mse2(2,2)))) + (
      1.0203040506070808*(0.970225*Quad(mAInput) - 6.8260499999999995*msl2(2,2)*
      Sqr(mAInput) - TDelta(0.985*Sqr(mAInput),0.99*msl2(2,2),0.99*msl2(2,2)))*
      TPhi(0.985*Sqr(mAInput),0.99*msl2(2,2),0.99*msl2(2,2)))/Sqr(msl2(2,2)) + (
      AtauInput + MuInput/TanBeta)*(AtauInput - MuInput*TanBeta)*(Log(0.985*Sqr(
      mAInput))*((-2*Log(1.01*mse2(2,2)))/(-1.01*mse2(2,2) + 0.99*msl2(2,2)) + (2*
      Log(0.99*msl2(2,2)))/(-1.01*mse2(2,2) + 0.99*msl2(2,2))) + Log(0.99*msl2(2,2
      ))*(-12/(-1.01*mse2(2,2) + 0.99*msl2(2,2)) - (2*Log(1.01*mse2(2,2)))/(-1.01*
      mse2(2,2) + 0.99*msl2(2,2)) - (12*Log(Sqr(SCALE)))/(-1.01*mse2(2,2) + 0.99*
      msl2(2,2))) + (12*Log(1.01*mse2(2,2)))/(-1.01*mse2(2,2) + 0.99*msl2(2,2)) +
      (12*Log(1.01*mse2(2,2))*Log(Sqr(SCALE)))/(-1.01*mse2(2,2) + 0.99*msl2(2,2))
      - (4*Sqr(Log(1.01*mse2(2,2))))/(-1.01*mse2(2,2) + 0.99*msl2(2,2)) + (6*Sqr(
      Log(0.99*msl2(2,2))))/(-1.01*mse2(2,2) + 0.99*msl2(2,2)) + (
      1.9605920988138417*(-0.985*(-6.0600000000000005*mse2(2,2) + 0.985*Sqr(
      mAInput))*Sqr(mAInput) + TDelta(0.985*Sqr(mAInput),1.01*mse2(2,2),1.01*mse2(
      2,2)))*TPhi(0.985*Sqr(mAInput),1.01*mse2(2,2),1.01*mse2(2,2)))/((-1.01*mse2(
      2,2) + 0.99*msl2(2,2))*Sqr(mse2(2,2))) + (2.0202020202020203*(-1.01*mse2(2,2
      ) + 0.99*msl2(2,2) + 0.985*Sqr(mAInput))*TPhi(0.985*Sqr(mAInput),1.01*mse2(2
      ,2),0.99*msl2(2,2)))/((-1.01*mse2(2,2) + 0.99*msl2(2,2))*msl2(2,2)) - (
      2.0406081012141617*(-0.985*(-6.93*msl2(2,2) + 0.985*Sqr(mAInput))*Sqr(
      mAInput) + TDelta(0.985*Sqr(mAInput),0.99*msl2(2,2),0.99*msl2(2,2)))*TPhi(
      0.985*Sqr(mAInput),0.99*msl2(2,2),0.99*msl2(2,2)))/((-1.01*mse2(2,2) + 0.99*
      msl2(2,2))*Sqr(msl2(2,2)))) + (AtauInput + MuInput/TanBeta)*Cube(AtauInput -
      MuInput*TanBeta)*((-12*Log(1.01*mse2(2,2))*(3.0300000000000002*mse2(2,2) +
      0.99*msl2(2,2)))/Cube(-1.01*mse2(2,2) + 0.99*msl2(2,2)) + Log(0.99*msl2(2,2)
      )*((12*Log(Sqr(SCALE))*(1.01*mse2(2,2) + 0.99*msl2(2,2)))/Cube(-1.01*mse2(2,
      2) + 0.99*msl2(2,2)) + (12*(1.01*mse2(2,2) + 2.9699999999999998*msl2(2,2)))
      /Cube(-1.01*mse2(2,2) + 0.99*msl2(2,2)) + (2*Log(1.01*mse2(2,2))*(1.01*mse2(
      2,2) + 2.9699999999999998*msl2(2,2) - 1.97*Sqr(mAInput)))/Cube(-1.01*mse2(2,
      2) + 0.99*msl2(2,2))) + Log(0.985*Sqr(mAInput))*((2*Log(0.99*msl2(2,2))*(
      -1.01*mse2(2,2) + 0.99*msl2(2,2) - 5.91*Sqr(mAInput)))/Cube(-1.01*mse2(2,2)
      + 0.99*msl2(2,2)) + (2*Log(1.01*mse2(2,2))*(1.01*mse2(2,2) - 0.99*msl2(2,2)
      + 5.91*Sqr(mAInput)))/Cube(-1.01*mse2(2,2) + 0.99*msl2(2,2))) + (4*(1.01*
      mse2(2,2) + 0.99*msl2(2,2) - 0.985*Sqr(mAInput))*Sqr(Log(1.01*mse2(2,2))))
      /Cube(-1.01*mse2(2,2) + 0.99*msl2(2,2)) + (2*(-3.0300000000000002*mse2(2,2)
      - 4.95*msl2(2,2) + 3.94*Sqr(mAInput))*Sqr(Log(0.99*msl2(2,2))))/Cube(-1.01*
      mse2(2,2) + 0.99*msl2(2,2)) + Log(Sqr(SCALE))*((-12*Log(1.01*mse2(2,2))*(
      1.01*mse2(2,2) + 0.99*msl2(2,2)))/Cube(-1.01*mse2(2,2) + 0.99*msl2(2,2)) -
      24/Sqr(-1.01*mse2(2,2) + 0.99*msl2(2,2))) - 48/Sqr(-1.01*mse2(2,2) + 0.99*
      msl2(2,2)) + (1.9605920988138417*(0.985*(-1.01*mse2(2,2) + 0.99*msl2(2,2))*(
      -6.0600000000000005*mse2(2,2) + 0.985*Sqr(mAInput))*Sqr(mAInput) - (
      -3.0300000000000002*mse2(2,2) + 0.99*msl2(2,2))*TDelta(0.985*Sqr(mAInput),
      1.01*mse2(2,2),1.01*mse2(2,2)))*TPhi(0.985*Sqr(mAInput),1.01*mse2(2,2),1.01*
      mse2(2,2)))/(Cube(-1.01*mse2(2,2) + 0.99*msl2(2,2))*Sqr(mse2(2,2))) - (
      2.0202020202020203*((-1.01*mse2(2,2) + 0.99*msl2(2,2))*(-1.01*mse2(2,2) +
      0.99*msl2(2,2) + 0.985*Sqr(mAInput)) - 2*TDelta(0.985*Sqr(mAInput),1.01*mse2
      (2,2),0.99*msl2(2,2)))*TPhi(0.985*Sqr(mAInput),1.01*mse2(2,2),0.99*msl2(2,2)
      ))/(Cube(-1.01*mse2(2,2) + 0.99*msl2(2,2))*msl2(2,2)) + (2.0406081012141617*
      (0.985*(-1.01*mse2(2,2) + 0.99*msl2(2,2))*(-6.93*msl2(2,2) + 0.985*Sqr(
      mAInput))*Sqr(mAInput) + (1.01*mse2(2,2) - 4.95*msl2(2,2))*TDelta(0.985*Sqr(
      mAInput),0.99*msl2(2,2),0.99*msl2(2,2)))*TPhi(0.985*Sqr(mAInput),0.99*msl2(2
      ,2),0.99*msl2(2,2)))/(Cube(-1.01*mse2(2,2) + 0.99*msl2(2,2))*Sqr(msl2(2,2)))
      ) + Sqr(AtauInput - MuInput*TanBeta)*((-2*Sqr(Log(1.01*mse2(2,2))))/(-1.01*
      mse2(2,2) + 0.99*msl2(2,2)) + Log(0.985*Sqr(mAInput))*((1.97019701970197*(
      1.01*mse2(2,2) - 1.98*msl2(2,2))*Sqr(mAInput))/(mse2(2,2)*(-1.01*mse2(2,2) +
      0.99*msl2(2,2))*msl2(2,2)) - (Log(1.01*mse2(2,2))*(5.05*mse2(2,2) - 4.95*
      msl2(2,2) + 0.985*Sqr(mAInput)))/Sqr(-1.01*mse2(2,2) + 0.99*msl2(2,2)) + (
      Log(0.99*msl2(2,2))*(5.05*mse2(2,2) - 4.95*msl2(2,2) + 0.985*Sqr(mAInput)))
      /Sqr(-1.01*mse2(2,2) + 0.99*msl2(2,2))) + Log(0.99*msl2(2,2))*((
      3.0300000000000002*mse2(2,2) + 0.99*msl2(2,2) - 1.97*Sqr(mAInput))/Sqr(-1.01
      *mse2(2,2) + 0.99*msl2(2,2)) + (Log(1.01*mse2(2,2))*(1.01*mse2(2,2) + 0.99*
      msl2(2,2) - 0.985*Sqr(mAInput)))/Sqr(-1.01*mse2(2,2) + 0.99*msl2(2,2)) - (2*
      Log(Sqr(SCALE))*(-0.99*msl2(2,2) + 0.985*Sqr(mAInput)))/Sqr(-1.01*mse2(2,2)
      + 0.99*msl2(2,2))) + (Log(1.01*mse2(2,2))*(-5.05*mse2(2,2) + 0.99*msl2(2,2)
      + 1.97*Sqr(mAInput)))/Sqr(-1.01*mse2(2,2) + 0.99*msl2(2,2)) + ((
      -3.0300000000000002*mse2(2,2) + 0.99*msl2(2,2) + 0.985*Sqr(mAInput))*Sqr(Log
      (0.99*msl2(2,2))))/Sqr(-1.01*mse2(2,2) + 0.99*msl2(2,2)) + (-3.9996*mse2(2,2
      )*msl2(2,2) - 1.9897*mse2(2,2)*Sqr(mAInput) + 3.9006*msl2(2,2)*Sqr(mAInput))
      /(-1.009899*msl2(2,2)*Sqr(mse2(2,2)) + 0.989901*mse2(2,2)*Sqr(msl2(2,2))) +
      Log(Sqr(SCALE))*((2*Log(1.01*mse2(2,2))*(-0.99*msl2(2,2) + 0.985*Sqr(mAInput
      )))/Sqr(-1.01*mse2(2,2) + 0.99*msl2(2,2)) + (-1.9998*mse2(2,2)*msl2(2,2) -
      1.9897*mse2(2,2)*Sqr(mAInput) + 3.9006*msl2(2,2)*Sqr(mAInput))/(-1.009899*
      msl2(2,2)*Sqr(mse2(2,2)) + 0.989901*mse2(2,2)*Sqr(msl2(2,2)))) + (
      0.9802960494069208*(-0.985*(-6.0600000000000005*mse2(2,2) + 0.985*Sqr(
      mAInput))*Sqr(mAInput) + TDelta(0.985*Sqr(mAInput),1.01*mse2(2,2),1.01*mse2(
      2,2)))*TPhi(0.985*Sqr(mAInput),1.01*mse2(2,2),1.01*mse2(2,2)))/((-1.01*mse2(
      2,2) + 0.99*msl2(2,2))*Sqr(mse2(2,2))) + (1.0101010101010102*TDelta(0.985*
      Sqr(mAInput),1.01*mse2(2,2),0.99*msl2(2,2))*TPhi(0.985*Sqr(mAInput),1.01*
      mse2(2,2),0.99*msl2(2,2)))/(msl2(2,2)*Sqr(-1.01*mse2(2,2) + 0.99*msl2(2,2)))
      + (1.0203040506070808*(0.985*(-1.01*mse2(2,2) + 0.99*msl2(2,2))*(-6.93*msl2
      (2,2) + 0.985*Sqr(mAInput))*Sqr(mAInput) + (1.01*mse2(2,2) - 1.98*msl2(2,2))
      *TDelta(0.985*Sqr(mAInput),0.99*msl2(2,2),0.99*msl2(2,2)))*TPhi(0.985*Sqr(
      mAInput),0.99*msl2(2,2),0.99*msl2(2,2)))/(Sqr(-1.01*mse2(2,2) + 0.99*msl2(2,
      2))*Sqr(msl2(2,2))) + Sqr(AtauInput + MuInput/TanBeta)*((2*Sqr(Log(1.01*mse2
      (2,2))))/Sqr(-1.01*mse2(2,2) + 0.99*msl2(2,2)) + (3*Sqr(Log(0.99*msl2(2,2)))
      )/Sqr(-1.01*mse2(2,2) + 0.99*msl2(2,2)) + (-2.02*mse2(2,2) + 3.96*msl2(2,2))
      /(-1.009899*msl2(2,2)*Sqr(mse2(2,2)) + 0.989901*mse2(2,2)*Sqr(msl2(2,2))) +
      Log(Sqr(SCALE))*((2*Log(1.01*mse2(2,2)))/Sqr(-1.01*mse2(2,2) + 0.99*msl2(2,2
      )) + (-2.02*mse2(2,2) + 3.96*msl2(2,2))/(-1.009899*msl2(2,2)*Sqr(mse2(2,2))
      + 0.989901*mse2(2,2)*Sqr(msl2(2,2)))) + (1.000100010001*Log(1.01*mse2(2,2))*
      (-((-1.01*mse2(2,2) + 0.99*msl2(2,2))*(0.970225*(1.01*mse2(2,2) + 1.98*msl2(
      2,2))*Quad(mAInput) - 3.9006*(2.02*mse2(2,2) + 0.99*msl2(2,2))*msl2(2,2)*Sqr
      (mAInput) + (-1.01*mse2(2,2) + 1.98*msl2(2,2))*Sqr(-1.01*mse2(2,2) + 0.99*
      msl2(2,2)))*TDelta(0.985*Sqr(mAInput),1.01*mse2(2,2),0.99*msl2(2,2))) + (
      1.9998*mse2(2,2)*(-1.01*mse2(2,2) + 0.99*msl2(2,2))*msl2(2,2)*(-1.01*mse2(2,
      2) + 0.99*msl2(2,2) + 0.985*Sqr(mAInput)) + (0.9999*mse2(2,2)*msl2(2,2) -
      1.0201*Sqr(mse2(2,2)) + 1.9602*Sqr(msl2(2,2)))*TDelta(0.985*Sqr(mAInput),
      1.01*mse2(2,2),0.99*msl2(2,2)))*TDelta(0.985*Sqr(mAInput),0.99*msl2(2,2),
      1.01*mse2(2,2))))/(mse2(2,2)*msl2(2,2)*Sqr(-1.01*mse2(2,2) + 0.99*msl2(2,2))
      *TDelta(0.985*Sqr(mAInput),1.01*mse2(2,2),0.99*msl2(2,2))*TDelta(0.985*Sqr(
      mAInput),0.99*msl2(2,2),1.01*mse2(2,2))) + Log(0.99*msl2(2,2))*((-5*Log(1.01
      *mse2(2,2)))/Sqr(-1.01*mse2(2,2) + 0.99*msl2(2,2)) - (2*Log(Sqr(SCALE)))/Sqr
      (-1.01*mse2(2,2) + 0.99*msl2(2,2)) + (0.9802960494069208*((-1.01*mse2(2,2) +
      0.99*msl2(2,2))*(-0.955671625*Power6(mAInput) + 0.970225*(4.04*mse2(2,2) +
      2.9699999999999998*msl2(2,2))*Quad(mAInput) + 0.99*msl2(2,2)*Sqr(-1.01*mse2(
      2,2) + 0.99*msl2(2,2)) - 0.985*Sqr(mAInput)*(1.9998*mse2(2,2)*msl2(2,2) +
      7.1407*Sqr(mse2(2,2)) + 2.9402999999999997*Sqr(msl2(2,2))))*TDelta(0.985*Sqr
      (mAInput),1.01*mse2(2,2),0.99*msl2(2,2)) + (-1.01*mse2(2,2)*(-1.01*mse2(2,2)
      + 0.99*msl2(2,2))*(-0.970225*Quad(mAInput) + 1.9897*mse2(2,2)*Sqr(mAInput)
      - 1.0201*Sqr(mse2(2,2)) + 0.9801*Sqr(msl2(2,2))) + (-1.9998*mse2(2,2)*msl2(2
      ,2) + 0.985*(-1.01*mse2(2,2) + 0.99*msl2(2,2))*Sqr(mAInput) + 1.0201*Sqr(
      mse2(2,2)) - 0.9801*Sqr(msl2(2,2)))*TDelta(0.985*Sqr(mAInput),1.01*mse2(2,2)
      ,0.99*msl2(2,2)))*TDelta(0.985*Sqr(mAInput),0.99*msl2(2,2),1.01*mse2(2,2))))
      /(Sqr(mse2(2,2))*Sqr(-1.01*mse2(2,2) + 0.99*msl2(2,2))*TDelta(0.985*Sqr(
      mAInput),1.01*mse2(2,2),0.99*msl2(2,2))*TDelta(0.985*Sqr(mAInput),0.99*msl2(
      2,2),1.01*mse2(2,2)))) + Log(0.985*Sqr(mAInput))*(-(Log(1.01*mse2(2,2))/Sqr(
      -1.01*mse2(2,2) + 0.99*msl2(2,2))) + Log(0.99*msl2(2,2))/Sqr(-1.01*mse2(2,2)
      + 0.99*msl2(2,2)) + (0.9901980297039604*((0.94611490875*msl2(2,2)*Power6(
      mAInput) - Quad(-1.01*mse2(2,2) + 0.99*msl2(2,2)) + 0.970225*Quad(mAInput)*(
      -1.9998*mse2(2,2)*msl2(2,2) + 1.0201*Sqr(mse2(2,2)) - 2.9402999999999997*Sqr
      (msl2(2,2))) + 0.97515*msl2(2,2)*Sqr(mAInput)*(-1.9998*mse2(2,2)*msl2(2,2) -
      1.0201*Sqr(mse2(2,2)) + 2.9402999999999997*Sqr(msl2(2,2))))*TDelta(0.985*
      Sqr(mAInput),1.01*mse2(2,2),0.99*msl2(2,2)) + (0.9999*mse2(2,2)*msl2(2,2)*(
      -0.970225*Quad(mAInput) + Sqr(-1.01*mse2(2,2) + 0.99*msl2(2,2))) + (-2.9997*
      mse2(2,2)*msl2(2,2) - 0.97515*msl2(2,2)*Sqr(mAInput) + 1.0201*Sqr(mse2(2,2))
      + 0.9801*Sqr(msl2(2,2)))*TDelta(0.985*Sqr(mAInput),1.01*mse2(2,2),0.99*msl2
      (2,2)))*TDelta(0.985*Sqr(mAInput),0.99*msl2(2,2),1.01*mse2(2,2))))/((-1.01*
      mse2(2,2) + 0.99*msl2(2,2))*msl2(2,2)*Sqr(mse2(2,2))*TDelta(0.985*Sqr(
      mAInput),1.01*mse2(2,2),0.99*msl2(2,2))*TDelta(0.985*Sqr(mAInput),0.99*msl2(
      2,2),1.01*mse2(2,2)))) + (0.9802960494069208*(0.985*(-6.0600000000000005*
      mse2(2,2) + 0.985*Sqr(mAInput))*Sqr(mAInput) - TDelta(0.985*Sqr(mAInput),
      1.01*mse2(2,2),1.01*mse2(2,2)))*TPhi(0.985*Sqr(mAInput),1.01*mse2(2,2),1.01*
      mse2(2,2)))/(Sqr(mse2(2,2))*Sqr(-1.01*mse2(2,2) + 0.99*msl2(2,2))) + (
      1.0101010101010102*((-1.01*mse2(2,2) + 0.99*msl2(2,2))*Sqr(0.985*Sqr(mAInput
      ) - 1.01*mse2(2,2) + 0.99*msl2(2,2)) + 0.985*Sqr(mAInput)*TDelta(0.985*Sqr(
      mAInput),1.01*mse2(2,2),0.99*msl2(2,2)))*TPhi(0.985*Sqr(mAInput),1.01*mse2(2
      ,2),0.99*msl2(2,2)))/(msl2(2,2)*Sqr(-1.01*mse2(2,2) + 0.99*msl2(2,2))*TDelta
      (0.985*Sqr(mAInput),1.01*mse2(2,2),0.99*msl2(2,2))) + (0.9705901479276445*(-
      ((-1.01*mse2(2,2) + 0.99*msl2(2,2))*(-3.8226865*(1.01*mse2(2,2) + 0.99*msl2(
      2,2))*Power6(mAInput) + 0.941336550625*Power8(mAInput) + Quad(-1.01*mse2(2,2
      ) + 0.99*msl2(2,2)) - 3.8615939999999997*(-1.01*mse2(2,2) + 0.99*msl2(2,2))*
      Sqr(mAInput)*Sqr(msl2(2,2)) + 0.970225*Quad(mAInput)*(3.9996*mse2(2,2)*msl2(
      2,2) + 6.1206*Sqr(mse2(2,2)) + 5.880599999999999*Sqr(msl2(2,2))))) - 2*(
      -2.02*mse2(2,2) + 0.99*msl2(2,2))*Sqr(TDelta(0.985*Sqr(mAInput),0.99*msl2(2,
      2),1.01*mse2(2,2))) + (0.970225*(-5.05*mse2(2,2) + 2.9699999999999998*msl2(2
      ,2))*Quad(mAInput) + (-5.05*mse2(2,2) + 2.9699999999999998*msl2(2,2))*Sqr(
      -1.01*mse2(2,2) + 0.99*msl2(2,2)) + 0.985*Sqr(mAInput)*(3.9996*mse2(2,2)*
      msl2(2,2) + 14.2814*Sqr(mse2(2,2)) - 5.880599999999999*Sqr(msl2(2,2))))*
      TDelta(0.985*Sqr(mAInput),0.99*msl2(2,2),1.01*mse2(2,2)))*TPhi(0.985*Sqr(
      mAInput),0.99*msl2(2,2),1.01*mse2(2,2)))/(Cube(mse2(2,2))*Sqr(-1.01*mse2(2,2
      ) + 0.99*msl2(2,2))*TDelta(0.985*Sqr(mAInput),0.99*msl2(2,2),1.01*mse2(2,2))
      ) + (1.0203040506070808*(0.985*(-6.93*msl2(2,2) + 0.985*Sqr(mAInput))*Sqr(
      mAInput) - TDelta(0.985*Sqr(mAInput),0.99*msl2(2,2),0.99*msl2(2,2)))*TPhi(
      0.985*Sqr(mAInput),0.99*msl2(2,2),0.99*msl2(2,2)))/(Sqr(-1.01*mse2(2,2) +
      0.99*msl2(2,2))*Sqr(msl2(2,2))))) + Quad(AtauInput - MuInput*TanBeta)*((
      1.000100010001*(2.9997*mse2(2,2)*(-1.01*mse2(2,2) + 0.99*msl2(2,2))*msl2(2,2
      ) + 0.985*Sqr(mAInput)*(-4.9995*mse2(2,2)*msl2(2,2) + 1.0201*Sqr(mse2(2,2))
      - 1.9602*Sqr(msl2(2,2)))))/(Cube(-1.01*mse2(2,2) + 0.99*msl2(2,2))*mse2(2,2)
      *msl2(2,2)) + Log(0.99*msl2(2,2))*((3*Log(Sqr(SCALE))*(1.9503*msl2(2,2)*Sqr(
      mAInput) + 1.0201*Sqr(mse2(2,2)) - 0.9801*Sqr(msl2(2,2))))/Quad(-1.01*mse2(2
      ,2) + 0.99*msl2(2,2)) + (1.5*(3.9006*msl2(2,2)*Sqr(mAInput) + 1.0201*Sqr(
      mse2(2,2)) - 0.9801*Sqr(msl2(2,2))))/Quad(-1.01*mse2(2,2) + 0.99*msl2(2,2)))
      + Log(Sqr(SCALE))*((1.000100010001*(5.9994*mse2(2,2)*(-1.01*mse2(2,2) +
      0.99*msl2(2,2))*msl2(2,2) + 0.985*Sqr(mAInput)*(-4.9995*mse2(2,2)*msl2(2,2)
      + 1.0201*Sqr(mse2(2,2)) - 1.9602*Sqr(msl2(2,2)))))/(Cube(-1.01*mse2(2,2) +
      0.99*msl2(2,2))*mse2(2,2)*msl2(2,2)) + (3*Log(1.01*mse2(2,2))*(-1.9503*msl2(
      2,2)*Sqr(mAInput) - 1.0201*Sqr(mse2(2,2)) + 0.9801*Sqr(msl2(2,2))))/Quad(
      -1.01*mse2(2,2) + 0.99*msl2(2,2))) + (1.5*Log(1.01*mse2(2,2))*(-3.9006*msl2(
      2,2)*Sqr(mAInput) - 1.0201*Sqr(mse2(2,2)) + 0.9801*Sqr(msl2(2,2))))/Quad(
      -1.01*mse2(2,2) + 0.99*msl2(2,2)) + Log(0.985*Sqr(mAInput))*((3*Log(1.01*
      mse2(2,2))*(1.9503*msl2(2,2)*Sqr(mAInput) + 1.0201*Sqr(mse2(2,2)) - 0.9801*
      Sqr(msl2(2,2))))/Quad(-1.01*mse2(2,2) + 0.99*msl2(2,2)) + (3*Log(0.99*msl2(2
      ,2))*(-1.9503*msl2(2,2)*Sqr(mAInput) - 1.0201*Sqr(mse2(2,2)) + 0.9801*Sqr(
      msl2(2,2))))/Quad(-1.01*mse2(2,2) + 0.99*msl2(2,2)) + (1.000100010001*(
      5.9994*mse2(2,2)*(1.01*mse2(2,2) - 0.99*msl2(2,2))*msl2(2,2) + 0.985*Sqr(
      mAInput)*(4.9995*mse2(2,2)*msl2(2,2) - 1.0201*Sqr(mse2(2,2)) + 1.9602*Sqr(
      msl2(2,2)))))/(Cube(-1.01*mse2(2,2) + 0.99*msl2(2,2))*mse2(2,2)*msl2(2,2)))
      + Sqr(AtauInput + MuInput/TanBeta)*((-2*(3.0300000000000002*mse2(2,2) + 0.99
      *msl2(2,2) - 1.97*Sqr(mAInput))*Sqr(Log(1.01*mse2(2,2))))/Quad(-1.01*mse2(2,
      2) + 0.99*msl2(2,2)) + ((-3.0300000000000002*mse2(2,2) - 10.89*msl2(2,2) +
      6.895*Sqr(mAInput))*Sqr(Log(0.99*msl2(2,2))))/Quad(-1.01*mse2(2,2) + 0.99*
      msl2(2,2)) + Log(Sqr(SCALE))*((-5.9399999999999995*Log(1.01*mse2(2,2))*msl2(
      2,2))/Quad(-1.01*mse2(2,2) + 0.99*msl2(2,2)) + (1.000100010001*(-4.9995*mse2
      (2,2)*msl2(2,2) + 1.0201*Sqr(mse2(2,2)) - 1.9602*Sqr(msl2(2,2))))/(Cube(
      -1.01*mse2(2,2) + 0.99*msl2(2,2))*mse2(2,2)*msl2(2,2))) + (1.000100010001*(
      -10.9989*mse2(2,2)*msl2(2,2) + 1.0201*Sqr(mse2(2,2)) - 1.9602*Sqr(msl2(2,2))
      ))/(Cube(-1.01*mse2(2,2) + 0.99*msl2(2,2))*mse2(2,2)*msl2(2,2)) - (
      0.5000500050005*Log(1.01*mse2(2,2))*(Sqr(-1.01*mse2(2,2) + 0.99*msl2(2,2))*(
      -3.090903*Cube(mse2(2,2)) - 2.910897*Cube(msl2(2,2)) + 0.955671625*Power6(
      mAInput) - 0.970225*(3.0300000000000002*mse2(2,2) + 4.95*msl2(2,2))*Quad(
      mAInput) - 5.049495*msl2(2,2)*Sqr(mse2(2,2)) + 10.888911*mse2(2,2)*Sqr(msl2(
      2,2)) + 0.985*Sqr(mAInput)*(3.9996*mse2(2,2)*msl2(2,2) + 5.1005*Sqr(mse2(2,2
      )) + 6.8607*Sqr(msl2(2,2))))*TDelta(0.985*Sqr(mAInput),1.01*mse2(2,2),0.99*
      msl2(2,2)) + (1.9998*mse2(2,2)*msl2(2,2)*(-1.01*mse2(2,2) + 0.99*msl2(2,2) +
      0.985*Sqr(mAInput))*Sqr(-1.01*mse2(2,2) + 0.99*msl2(2,2)) + (1.030301*Cube(
      mse2(2,2)) + 2.910897*Cube(msl2(2,2)) + 13.128687000000001*msl2(2,2)*Sqr(
      mse2(2,2)) - 0.985*Sqr(mAInput)*Sqr(-1.01*mse2(2,2) + 0.99*msl2(2,2)) +
      6.9293070000000005*mse2(2,2)*Sqr(msl2(2,2)))*TDelta(0.985*Sqr(mAInput),1.01*
      mse2(2,2),0.99*msl2(2,2)))*TDelta(0.985*Sqr(mAInput),0.99*msl2(2,2),1.01*
      mse2(2,2))))/(mse2(2,2)*msl2(2,2)*Quad(-1.01*mse2(2,2) + 0.99*msl2(2,2))*
      TDelta(0.985*Sqr(mAInput),1.01*mse2(2,2),0.99*msl2(2,2))*TDelta(0.985*Sqr(
      mAInput),0.99*msl2(2,2),1.01*mse2(2,2))) + Log(0.985*Sqr(mAInput))*((3*Log(
      1.01*mse2(2,2))*(1.01*mse2(2,2) - 0.99*msl2(2,2) + 0.985*Sqr(mAInput)))/Quad
      (-1.01*mse2(2,2) + 0.99*msl2(2,2)) - (3*Log(0.99*msl2(2,2))*(1.01*mse2(2,2)
      - 0.99*msl2(2,2) + 0.985*Sqr(mAInput)))/Quad(-1.01*mse2(2,2) + 0.99*msl2(2,2
      )) + (0.4950990148519802*((-1.01*mse2(2,2) + 0.99*msl2(2,2))*(3.090903*Cube(
      mse2(2,2)) + 0.9702989999999999*Cube(msl2(2,2)) - 0.955671625*Power6(mAInput
      ) + 2.910675*(1.01*mse2(2,2) + 0.99*msl2(2,2))*Quad(mAInput) - 1.009899*msl2
      (2,2)*Sqr(mse2(2,2)) - 2.9697029999999995*mse2(2,2)*Sqr(msl2(2,2)) - 0.985*
      Sqr(mAInput)*(5.1005*Sqr(mse2(2,2)) + 2.9402999999999997*Sqr(msl2(2,2))))*
      TDelta(0.985*Sqr(mAInput),1.01*mse2(2,2),0.99*msl2(2,2)) + (-0.9999*mse2(2,2
      )*msl2(2,2)*(-0.970225*Quad(mAInput) + Sqr(-1.01*mse2(2,2) + 0.99*msl2(2,2))
      ) + (2.9997*mse2(2,2)*msl2(2,2) + 0.985*(-1.01*mse2(2,2) + 0.99*msl2(2,2))*
      Sqr(mAInput) + 3.0603*Sqr(mse2(2,2)) - 0.9801*Sqr(msl2(2,2)))*TDelta(0.985*
      Sqr(mAInput),1.01*mse2(2,2),0.99*msl2(2,2)))*TDelta(0.985*Sqr(mAInput),0.99*
      msl2(2,2),1.01*mse2(2,2))))/(msl2(2,2)*Sqr(mse2(2,2))*Sqr(-1.01*mse2(2,2) +
      0.99*msl2(2,2))*TDelta(0.985*Sqr(mAInput),1.01*mse2(2,2),0.99*msl2(2,2))*
      TDelta(0.985*Sqr(mAInput),0.99*msl2(2,2),1.01*mse2(2,2)))) + Log(0.99*msl2(2
      ,2))*((5.9399999999999995*Log(Sqr(SCALE))*msl2(2,2))/Quad(-1.01*mse2(2,2) +
      0.99*msl2(2,2)) + (Log(1.01*mse2(2,2))*(9.09*mse2(2,2) + 12.87*msl2(2,2) -
      10.834999999999999*Sqr(mAInput)))/Quad(-1.01*mse2(2,2) + 0.99*msl2(2,2)) + (
      0.4901480247034604*(Sqr(-1.01*mse2(2,2) + 0.99*msl2(2,2))*(
      -9.272708999999999*Cube(mse2(2,2)) - 0.9702989999999999*Cube(msl2(2,2)) +
      0.955671625*Power6(mAInput) - 0.970225*(5.05*mse2(2,2) + 2.9699999999999998*
      msl2(2,2))*Quad(mAInput) + 9.089091000000002*msl2(2,2)*Sqr(mse2(2,2)) +
      0.989901*mse2(2,2)*Sqr(msl2(2,2)) + 0.985*Sqr(mAInput)*(3.9996*mse2(2,2)*
      msl2(2,2) + 9.1809*Sqr(mse2(2,2)) + 2.9402999999999997*Sqr(msl2(2,2))))*
      TDelta(0.985*Sqr(mAInput),1.01*mse2(2,2),0.99*msl2(2,2)) + (1.01*mse2(2,2)*
      Sqr(-1.01*mse2(2,2) + 0.99*msl2(2,2))*(-0.970225*Quad(mAInput) + 1.9897*mse2
      (2,2)*Sqr(mAInput) - 1.0201*Sqr(mse2(2,2)) + 0.9801*Sqr(msl2(2,2))) + (
      4.121204*Cube(mse2(2,2)) + 0.9702989999999999*Cube(msl2(2,2)) +
      17.168283000000002*msl2(2,2)*Sqr(mse2(2,2)) - 0.985*Sqr(mAInput)*Sqr(-1.01*
      mse2(2,2) + 0.99*msl2(2,2)) + 1.979802*mse2(2,2)*Sqr(msl2(2,2)))*TDelta(
      0.985*Sqr(mAInput),1.01*mse2(2,2),0.99*msl2(2,2)))*TDelta(0.985*Sqr(mAInput)
      ,0.99*msl2(2,2),1.01*mse2(2,2))))/(Quad(-1.01*mse2(2,2) + 0.99*msl2(2,2))*
      Sqr(mse2(2,2))*TDelta(0.985*Sqr(mAInput),1.01*mse2(2,2),0.99*msl2(2,2))*
      TDelta(0.985*Sqr(mAInput),0.99*msl2(2,2),1.01*mse2(2,2)))) + (
      0.9802960494069208*(0.985*(1.01*mse2(2,2) - 0.99*msl2(2,2))*(
      -6.0600000000000005*mse2(2,2) + 0.985*Sqr(mAInput))*Sqr(mAInput) + (-5.05*
      mse2(2,2) + 0.99*msl2(2,2))*TDelta(0.985*Sqr(mAInput),1.01*mse2(2,2),1.01*
      mse2(2,2)))*TPhi(0.985*Sqr(mAInput),1.01*mse2(2,2),1.01*mse2(2,2)))/(Quad(
      -1.01*mse2(2,2) + 0.99*msl2(2,2))*Sqr(mse2(2,2))) - (0.5050505050505051*(Sqr
      (-1.01*mse2(2,2) + 0.99*msl2(2,2))*Sqr(0.985*Sqr(mAInput) - 1.01*mse2(2,2) +
      0.99*msl2(2,2)) - 6*Sqr(TDelta(0.985*Sqr(mAInput),1.01*mse2(2,2),0.99*msl2(
      2,2))) + (-1.01*mse2(2,2) + 0.99*msl2(2,2))*(-3.0300000000000002*mse2(2,2) +
      2.9699999999999998*msl2(2,2) + 3.94*Sqr(mAInput))*TDelta(0.985*Sqr(mAInput)
      ,1.01*mse2(2,2),0.99*msl2(2,2)))*TPhi(0.985*Sqr(mAInput),1.01*mse2(2,2),0.99
      *msl2(2,2)))/(msl2(2,2)*Quad(-1.01*mse2(2,2) + 0.99*msl2(2,2))*TDelta(0.985*
      Sqr(mAInput),1.01*mse2(2,2),0.99*msl2(2,2))) + (0.48529507396382227*(Sqr(
      -1.01*mse2(2,2) + 0.99*msl2(2,2))*(-3.8226865*(1.01*mse2(2,2) + 0.99*msl2(2,
      2))*Power6(mAInput) + 0.941336550625*Power8(mAInput) - 3.94*(1.01*mse2(2,2)
      + 0.99*msl2(2,2))*Sqr(mAInput)*Sqr(-1.01*mse2(2,2) + 0.99*msl2(2,2)) + Sqr(
      -1.01*mse2(2,2) + 0.99*msl2(2,2))*(-1.9998*mse2(2,2)*msl2(2,2) - 3.0603*Sqr(
      mse2(2,2)) + 0.9801*Sqr(msl2(2,2))) + 0.970225*Quad(mAInput)*(3.9996*mse2(2,
      2)*msl2(2,2) + 6.1206*Sqr(mse2(2,2)) + 5.880599999999999*Sqr(msl2(2,2)))) +
      2*(-4.9995*mse2(2,2)*msl2(2,2) + 12.2412*Sqr(mse2(2,2)) + 0.9801*Sqr(msl2(2,
      2)))*Sqr(TDelta(0.985*Sqr(mAInput),0.99*msl2(2,2),1.01*mse2(2,2))) - (-1.01*
      mse2(2,2) + 0.99*msl2(2,2))*(-17.515117*Cube(mse2(2,2)) + 2.910897*Cube(msl2
      (2,2)) + 2.910675*(-3.0300000000000002*mse2(2,2) + 0.99*msl2(2,2))*Quad(
      mAInput) + 29.287071000000005*msl2(2,2)*Sqr(mse2(2,2)) - 5.91*Sqr(mAInput)*(
      -1.9998*mse2(2,2)*msl2(2,2) - 3.0603*Sqr(mse2(2,2)) + 0.9801*Sqr(msl2(2,2)))
      - 14.848514999999999*mse2(2,2)*Sqr(msl2(2,2)))*TDelta(0.985*Sqr(mAInput),
      0.99*msl2(2,2),1.01*mse2(2,2)))*TPhi(0.985*Sqr(mAInput),0.99*msl2(2,2),1.01*
      mse2(2,2)))/(Cube(mse2(2,2))*Quad(-1.01*mse2(2,2) + 0.99*msl2(2,2))*TDelta(
      0.985*Sqr(mAInput),0.99*msl2(2,2),1.01*mse2(2,2))) + (1.0203040506070808*(
      0.985*(-1.01*mse2(2,2) + 0.99*msl2(2,2))*(-6.93*msl2(2,2) + 0.985*Sqr(
      mAInput))*Sqr(mAInput) + (1.01*mse2(2,2) - 7.92*msl2(2,2))*TDelta(0.985*Sqr(
      mAInput),0.99*msl2(2,2),0.99*msl2(2,2)))*TPhi(0.985*Sqr(mAInput),0.99*msl2(2
      ,2),0.99*msl2(2,2)))/(Quad(-1.01*mse2(2,2) + 0.99*msl2(2,2))*Sqr(msl2(2,2)))
      )))))/Quad(3.141592653589793), 0))*UnitStep(-2 + LambdaLoopOrder) + UnitStep
      (-1 + LambdaLoopOrder)*(0.006332573977646111*(-0.09*Quad(g1) - 0.3*Sqr(g1)*
      Sqr(g2) - Quad(g2)*(0.75 - 0.16666666666666666*Sqr(Cos(2*ArcTan(TanBeta)))))
      - 0.0010554289962743518*(2*Log(Sqr(M2Input)/Sqr(SCALE))*Quad(g2)*(1 + (
      DeltaEFT*Sqr(v))/Sqr(M2Input)) + Log(Sqr(MuInput)/Sqr(SCALE))*(0.36*Quad(g1)
      + Quad(g2))*(1 + (DeltaEFT*Sqr(v))/Sqr(MuInput)))*Sqr(Cos(2*ArcTan(TanBeta)
      )) + 0.006332573977646111*(0.5*Log(Sqr(MuInput)/Sqr(SCALE))*(1 + (DeltaEFT*
      Sqr(v))/Sqr(MuInput))*(-2*(Sqr(g2)/(1 + Sqr(TanBeta)) + (0.6*Sqr(g1)*Sqr(
      TanBeta))/(1 + Sqr(TanBeta)))*((0.6*Sqr(g1))/(1 + Sqr(TanBeta)) + (Sqr(g2)*
      Sqr(TanBeta))/(1 + Sqr(TanBeta))) + 0.5*(0.6*Sqr(g1) + Sqr(g2))*((0.6*Sqr(g1
      ))/(1 + Sqr(TanBeta)) + (3*Sqr(g2))/(1 + Sqr(TanBeta)) + (0.6*Sqr(g1)*Sqr(
      TanBeta))/(1 + Sqr(TanBeta)) + (3*Sqr(g2)*Sqr(TanBeta))/(1 + Sqr(TanBeta)))*
      Sqr(Cos(2*ArcTan(TanBeta))) - (0.36*Quad(g1))/Sqr(1 + Sqr(TanBeta)) - (5*
      Quad(g2))/Sqr(1 + Sqr(TanBeta)) - (0.36*Quad(g1)*Quad(TanBeta))/Sqr(1 + Sqr(
      TanBeta)) - (5*Quad(g2)*Quad(TanBeta))/Sqr(1 + Sqr(TanBeta)) - (2.4*Sqr(g1)*
      Sqr(g2)*Sqr(TanBeta))/Sqr(1 + Sqr(TanBeta))) + (0.4*TanBeta*Sqr(g1)*(1 + (
      DeltaEFT*Sqr(v))/Min(Sqr(M1Input),Sqr(MuInput)))*(-2*((0.6*Sqr(g1))/(1 + Sqr
      (TanBeta)) + (0.6*Sqr(g1)*Sqr(TanBeta))/(1 + Sqr(TanBeta))) + 0.25*(0.6*Sqr(
      g1) + Sqr(g2))*Sqr(Cos(2*ArcTan(TanBeta))))*TCf0(M1Input/MuInput))/(1 + Sqr(
      TanBeta)) + (2*TanBeta*Sqr(g2)*(1 + (DeltaEFT*Sqr(v))/Min(Sqr(M2Input),Sqr(
      MuInput)))*(-2*(Sqr(g2)/(1 + Sqr(TanBeta)) + (Sqr(g2)*Sqr(TanBeta))/(1 + Sqr
      (TanBeta))) + 0.25*(0.6*Sqr(g1) + Sqr(g2))*Sqr(Cos(2*ArcTan(TanBeta))))*TCf0
      (M2Input/MuInput))/(1 + Sqr(TanBeta)) + 0.08333333333333333*(0.6*Sqr(g1) +
      Sqr(g2))*((0.6*Sqr(g1))/(1 + Sqr(TanBeta)) + (0.6*Sqr(g1)*Sqr(TanBeta))/(1 +
      Sqr(TanBeta)))*(1 + (DeltaEFT*Sqr(v))/Min(Sqr(M1Input),Sqr(MuInput)))*Sqr(
      Cos(2*ArcTan(TanBeta)))*TCg0(M1Input/MuInput) + 0.25*(0.6*Sqr(g1) + Sqr(g2))
      *(Sqr(g2)/(1 + Sqr(TanBeta)) + (Sqr(g2)*Sqr(TanBeta))/(1 + Sqr(TanBeta)))*(1
      + (DeltaEFT*Sqr(v))/Min(Sqr(M2Input),Sqr(MuInput)))*Sqr(Cos(2*ArcTan(
      TanBeta)))*TCg0(M2Input/MuInput) - 0.5833333333333334*(1 + (DeltaEFT*Sqr(v))
      /Min(Sqr(M1Input),Sqr(MuInput)))*((0.36*Quad(g1))/Sqr(1 + Sqr(TanBeta)) + (
      0.36*Quad(g1)*Quad(TanBeta))/Sqr(1 + Sqr(TanBeta)))*TCf(1)(M1Input/MuInput)
      - 2.25*(1 + (DeltaEFT*Sqr(v))/Min(Sqr(M2Input),Sqr(MuInput)))*(Quad(g2)/Sqr(
      1 + Sqr(TanBeta)) + (Quad(g2)*Quad(TanBeta))/Sqr(1 + Sqr(TanBeta)))*TCf(2)(
      M2Input/MuInput) - (0.54*Quad(g1)*Sqr(TanBeta)*(1 + (DeltaEFT*Sqr(v))/Min(
      Sqr(M1Input),Sqr(MuInput)))*TCf(3)(M1Input/MuInput))/Sqr(1 + Sqr(TanBeta)) -
      (3.5*Quad(g2)*Sqr(TanBeta)*(1 + (DeltaEFT*Sqr(v))/Min(Sqr(M2Input),Sqr(
      MuInput)))*TCf(4)(M2Input/MuInput))/Sqr(1 + Sqr(TanBeta)) - (1.6*Sqr(g1)*Sqr
      (g2)*Sqr(TanBeta)*(1 + (DeltaEFT*Sqr(v))/Min(Sqr(M1Input),Sqr(M2Input),Sqr(
      MuInput)))*TCf(5)(M1Input/MuInput,M2Input/MuInput))/Sqr(1 + Sqr(TanBeta)) -
      1.1666666666666667*(1 + (DeltaEFT*Sqr(v))/Min(Sqr(M1Input),Sqr(M2Input),Sqr(
      MuInput)))*((0.6*Sqr(g1)*Sqr(g2))/Sqr(1 + Sqr(TanBeta)) + (0.6*Quad(TanBeta)
      *Sqr(g1)*Sqr(g2))/Sqr(1 + Sqr(TanBeta)))*TCf(6)(M1Input/MuInput,
      M2Input/MuInput) - (0.2*Sqr(g1)*Sqr(g2)*Sqr(TanBeta)*(1 + (DeltaEFT*Sqr(v))
      /Min(Sqr(M1Input),Sqr(M2Input),Sqr(MuInput)))*TCf(7)(M1Input/MuInput,
      M2Input/MuInput))/Sqr(1 + Sqr(TanBeta)) - (2.065591117977289*g1*g2*TanBeta*(
      (0.7745966692414834*g1*g2)/(1 + Sqr(TanBeta)) + (0.7745966692414834*g1*g2*
      Sqr(TanBeta))/(1 + Sqr(TanBeta)))*(1 + (DeltaEFT*Sqr(v))/Min(Sqr(M1Input),
      Sqr(M2Input),Sqr(MuInput)))*TCf(8)(M1Input/MuInput,M2Input/MuInput))/(1 +
      Sqr(TanBeta))) + 0.006332573977646111*(1 + (DeltaEFT*Sqr(v))/Min(Abs(mse2(2,
      2)),Abs(msl2(2,2)),Sqr(MuInput)))*(Log(mse2(2,2)/Sqr(SCALE))*Sqr(Ye(2,2))*(
      -0.6*Cos(2*ArcTan(TanBeta))*Sqr(g1) + Sqr(Ye(2,2))) + Log(msl2(2,2)/Sqr(
      SCALE))*Sqr(Ye(2,2))*(-0.5*Cos(2*ArcTan(TanBeta))*(-0.6*Sqr(g1) + Sqr(g2)) +
      Sqr(Ye(2,2))) + (2*Quad(Ye(2,2))*Sqr(AtauInput - MuInput*TanBeta)*(TCF(1)(
      Sqrt(Abs(msl2(2,2)/mse2(2,2)))) - (0.08333333333333333*Sqr(AtauInput -
      MuInput*TanBeta)*TCF(2)(Sqrt(Abs(msl2(2,2)/mse2(2,2)))))/Sqrt(Abs(mse2(2,2)*
      msl2(2,2)))))/Sqrt(Abs(mse2(2,2)*msl2(2,2))) + (0.25*Cos(2*ArcTan(TanBeta))*
      Sqr(AtauInput - MuInput*TanBeta)*Sqr(Ye(2,2))*(-0.9*Sqr(g1)*TCF(3)(Sqrt(Abs(
      msl2(2,2)/mse2(2,2)))) + (0.3*Sqr(g1) - Sqr(g2))*TCF(4)(Sqrt(Abs(msl2(2,2)
      /mse2(2,2))))))/Sqrt(Abs(mse2(2,2)*msl2(2,2))) - (0.08333333333333333*(0.6*
      Sqr(g1) + Sqr(g2))*Sqr(AtauInput - MuInput*TanBeta)*Sqr(Cos(2*ArcTan(TanBeta
      )))*Sqr(Ye(2,2))*TCF(5)(Sqrt(Abs(msl2(2,2)/mse2(2,2)))))/Sqrt(Abs(mse2(2,2)*
      msl2(2,2)))) + 0.006332573977646111*(1 + (DeltaEFT*Sqr(v))/Min(Abs(msd2(2,2)
      ),Abs(msq2(2,2)),Abs(msu2(2,2)),Sqr(M3Input),Sqr(MuInput)))*((3*Log(msd2(2,2
      )/Sqr(SCALE))*Sqr(Yd(2,2))*(-0.2*Cos(2*ArcTan(TanBeta))*Sqr(g1) + Sqr(Yd(2,2
      ))/Sqr(1 + (0.006332573977646111*(1 + Sqr(TanBeta))*(0.25*Log(Sqr(MuInput)
      /Sqr(SCALE)) + (0.125*(-1 + 2*Log(Sqr(mAInput)/Sqr(SCALE))))/(1 + Sqr(
      TanBeta)) + ((-1 + Log(Sqr(mAInput)/Sqr(SCALE)))*Sqr(TanBeta))/(1 + Sqr(
      TanBeta)))*Sqr(Yu(2,2)))/Sqr(TanBeta) + 0.5*((-0.0031662869888230555*Sqr(
      AbInput - MuInput*TanBeta)*Sqr(Yd(2,2))*TCF(5)(Sqrt(Abs(msq2(2,2)/msd2(2,2))
      )))/Sqrt(Abs(msd2(2,2)*msq2(2,2))) - (0.0031662869888230555*Sqr(AtInput -
      MuInput/TanBeta)*Sqr(Yu(2,2))*TCF(5)(Sqrt(Abs(msq2(2,2)/msu2(2,2)))))/Sqrt(
      Abs(msq2(2,2)*msu2(2,2)))) + 0.006332573977646111*(1 + Sqr(TanBeta))*Sqr(Yd(
      2,2))*(0.75*Log(Sqr(MuInput)/Sqr(SCALE)) + (0.375*(-1 + 2*Log(Sqr(mAInput)
      /Sqr(SCALE)))*Sqr(TanBeta))/(1 + Sqr(TanBeta)) + 0.5*TCF(6)(Sqrt(msd2(2,2))
      /MuInput) + TCF(6)(Sqrt(msq2(2,2))/MuInput)) + 0.008443431970194815*Sqr(g3)*
      (1 + Log(Sqr(M3Input)/Sqr(SCALE)) + TCF(6)(Sqrt(msd2(2,2))/M3Input) + TCF(6)
      (Sqrt(msq2(2,2))/M3Input) - ((AbInput - MuInput*TanBeta)*TCF(9)(Sqrt(msq2(2,
      2))/M3Input,Sqrt(msd2(2,2))/M3Input))/M3Input) + (0.006332573977646111*(1 +
      Sqr(TanBeta))*Sqr(Yu(2,2))*(0.5*TCF(6)(Sqrt(msu2(2,2))/MuInput) + (0.5*(
      AtInput - MuInput/TanBeta)*TanBeta*TCF(9)(Sqrt(msq2(2,2))/MuInput,Sqrt(msu2(
      2,2))/MuInput))/MuInput))/Sqr(TanBeta))))/Sqr(1 + (0.006332573977646111*(1 +
      Sqr(TanBeta))*(0.25*Log(Sqr(MuInput)/Sqr(SCALE)) + (0.125*(-1 + 2*Log(Sqr(
      mAInput)/Sqr(SCALE))))/(1 + Sqr(TanBeta)) + ((-1 + Log(Sqr(mAInput)/Sqr(
      SCALE)))*Sqr(TanBeta))/(1 + Sqr(TanBeta)))*Sqr(Yu(2,2)))/Sqr(TanBeta) + 0.5*
      ((-0.0031662869888230555*Sqr(AbInput - MuInput*TanBeta)*Sqr(Yd(2,2))*TCF(5)(
      Sqrt(Abs(msq2(2,2)/msd2(2,2)))))/Sqrt(Abs(msd2(2,2)*msq2(2,2))) - (
      0.0031662869888230555*Sqr(AtInput - MuInput/TanBeta)*Sqr(Yu(2,2))*TCF(5)(
      Sqrt(Abs(msq2(2,2)/msu2(2,2)))))/Sqrt(Abs(msq2(2,2)*msu2(2,2)))) +
      0.006332573977646111*(1 + Sqr(TanBeta))*Sqr(Yd(2,2))*(0.75*Log(Sqr(MuInput)
      /Sqr(SCALE)) + (0.375*(-1 + 2*Log(Sqr(mAInput)/Sqr(SCALE)))*Sqr(TanBeta))/(1
      + Sqr(TanBeta)) + 0.5*TCF(6)(Sqrt(msd2(2,2))/MuInput) + TCF(6)(Sqrt(msq2(2,
      2))/MuInput)) + 0.008443431970194815*Sqr(g3)*(1 + Log(Sqr(M3Input)/Sqr(SCALE
      )) + TCF(6)(Sqrt(msd2(2,2))/M3Input) + TCF(6)(Sqrt(msq2(2,2))/M3Input) - ((
      AbInput - MuInput*TanBeta)*TCF(9)(Sqrt(msq2(2,2))/M3Input,Sqrt(msd2(2,2))
      /M3Input))/M3Input) + (0.006332573977646111*(1 + Sqr(TanBeta))*Sqr(Yu(2,2))*
      (0.5*TCF(6)(Sqrt(msu2(2,2))/MuInput) + (0.5*(AtInput - MuInput/TanBeta)*
      TanBeta*TCF(9)(Sqrt(msq2(2,2))/MuInput,Sqrt(msu2(2,2))/MuInput))/MuInput))
      /Sqr(TanBeta)) + (3*Log(msq2(2,2)/Sqr(SCALE))*Sqr(Yd(2,2))*(-0.5*Cos(2*
      ArcTan(TanBeta))*(0.2*Sqr(g1) + Sqr(g2)) + Sqr(Yd(2,2))/Sqr(1 + (
      0.006332573977646111*(1 + Sqr(TanBeta))*(0.25*Log(Sqr(MuInput)/Sqr(SCALE)) +
      (0.125*(-1 + 2*Log(Sqr(mAInput)/Sqr(SCALE))))/(1 + Sqr(TanBeta)) + ((-1 +
      Log(Sqr(mAInput)/Sqr(SCALE)))*Sqr(TanBeta))/(1 + Sqr(TanBeta)))*Sqr(Yu(2,2))
      )/Sqr(TanBeta) + 0.5*((-0.0031662869888230555*Sqr(AbInput - MuInput*TanBeta)
      *Sqr(Yd(2,2))*TCF(5)(Sqrt(Abs(msq2(2,2)/msd2(2,2)))))/Sqrt(Abs(msd2(2,2)*
      msq2(2,2))) - (0.0031662869888230555*Sqr(AtInput - MuInput/TanBeta)*Sqr(Yu(2
      ,2))*TCF(5)(Sqrt(Abs(msq2(2,2)/msu2(2,2)))))/Sqrt(Abs(msq2(2,2)*msu2(2,2))))
      + 0.006332573977646111*(1 + Sqr(TanBeta))*Sqr(Yd(2,2))*(0.75*Log(Sqr(
      MuInput)/Sqr(SCALE)) + (0.375*(-1 + 2*Log(Sqr(mAInput)/Sqr(SCALE)))*Sqr(
      TanBeta))/(1 + Sqr(TanBeta)) + 0.5*TCF(6)(Sqrt(msd2(2,2))/MuInput) + TCF(6)(
      Sqrt(msq2(2,2))/MuInput)) + 0.008443431970194815*Sqr(g3)*(1 + Log(Sqr(
      M3Input)/Sqr(SCALE)) + TCF(6)(Sqrt(msd2(2,2))/M3Input) + TCF(6)(Sqrt(msq2(2,
      2))/M3Input) - ((AbInput - MuInput*TanBeta)*TCF(9)(Sqrt(msq2(2,2))/M3Input,
      Sqrt(msd2(2,2))/M3Input))/M3Input) + (0.006332573977646111*(1 + Sqr(TanBeta)
      )*Sqr(Yu(2,2))*(0.5*TCF(6)(Sqrt(msu2(2,2))/MuInput) + (0.5*(AtInput -
      MuInput/TanBeta)*TanBeta*TCF(9)(Sqrt(msq2(2,2))/MuInput,Sqrt(msu2(2,2))
      /MuInput))/MuInput))/Sqr(TanBeta))))/Sqr(1 + (0.006332573977646111*(1 + Sqr(
      TanBeta))*(0.25*Log(Sqr(MuInput)/Sqr(SCALE)) + (0.125*(-1 + 2*Log(Sqr(
      mAInput)/Sqr(SCALE))))/(1 + Sqr(TanBeta)) + ((-1 + Log(Sqr(mAInput)/Sqr(
      SCALE)))*Sqr(TanBeta))/(1 + Sqr(TanBeta)))*Sqr(Yu(2,2)))/Sqr(TanBeta) + 0.5*
      ((-0.0031662869888230555*Sqr(AbInput - MuInput*TanBeta)*Sqr(Yd(2,2))*TCF(5)(
      Sqrt(Abs(msq2(2,2)/msd2(2,2)))))/Sqrt(Abs(msd2(2,2)*msq2(2,2))) - (
      0.0031662869888230555*Sqr(AtInput - MuInput/TanBeta)*Sqr(Yu(2,2))*TCF(5)(
      Sqrt(Abs(msq2(2,2)/msu2(2,2)))))/Sqrt(Abs(msq2(2,2)*msu2(2,2)))) +
      0.006332573977646111*(1 + Sqr(TanBeta))*Sqr(Yd(2,2))*(0.75*Log(Sqr(MuInput)
      /Sqr(SCALE)) + (0.375*(-1 + 2*Log(Sqr(mAInput)/Sqr(SCALE)))*Sqr(TanBeta))/(1
      + Sqr(TanBeta)) + 0.5*TCF(6)(Sqrt(msd2(2,2))/MuInput) + TCF(6)(Sqrt(msq2(2,
      2))/MuInput)) + 0.008443431970194815*Sqr(g3)*(1 + Log(Sqr(M3Input)/Sqr(SCALE
      )) + TCF(6)(Sqrt(msd2(2,2))/M3Input) + TCF(6)(Sqrt(msq2(2,2))/M3Input) - ((
      AbInput - MuInput*TanBeta)*TCF(9)(Sqrt(msq2(2,2))/M3Input,Sqrt(msd2(2,2))
      /M3Input))/M3Input) + (0.006332573977646111*(1 + Sqr(TanBeta))*Sqr(Yu(2,2))*
      (0.5*TCF(6)(Sqrt(msu2(2,2))/MuInput) + (0.5*(AtInput - MuInput/TanBeta)*
      TanBeta*TCF(9)(Sqrt(msq2(2,2))/MuInput,Sqrt(msu2(2,2))/MuInput))/MuInput))
      /Sqr(TanBeta)) + (6*Quad(Yd(2,2))*Sqr(AbInput - MuInput*TanBeta)*(TCF(1)(
      Sqrt(Abs(msq2(2,2)/msd2(2,2)))) - (0.08333333333333333*Sqr(AbInput - MuInput
      *TanBeta)*TCF(2)(Sqrt(Abs(msq2(2,2)/msd2(2,2)))))/Sqrt(Abs(msd2(2,2)*msq2(2,
      2)))))/(Sqrt(Abs(msd2(2,2)*msq2(2,2)))*Quad(1 + (0.006332573977646111*(1 +
      Sqr(TanBeta))*(0.25*Log(Sqr(MuInput)/Sqr(SCALE)) + (0.125*(-1 + 2*Log(Sqr(
      mAInput)/Sqr(SCALE))))/(1 + Sqr(TanBeta)) + ((-1 + Log(Sqr(mAInput)/Sqr(
      SCALE)))*Sqr(TanBeta))/(1 + Sqr(TanBeta)))*Sqr(Yu(2,2)))/Sqr(TanBeta) + 0.5*
      ((-0.0031662869888230555*Sqr(AbInput - MuInput*TanBeta)*Sqr(Yd(2,2))*TCF(5)(
      Sqrt(Abs(msq2(2,2)/msd2(2,2)))))/Sqrt(Abs(msd2(2,2)*msq2(2,2))) - (
      0.0031662869888230555*Sqr(AtInput - MuInput/TanBeta)*Sqr(Yu(2,2))*TCF(5)(
      Sqrt(Abs(msq2(2,2)/msu2(2,2)))))/Sqrt(Abs(msq2(2,2)*msu2(2,2)))) +
      0.006332573977646111*(1 + Sqr(TanBeta))*Sqr(Yd(2,2))*(0.75*Log(Sqr(MuInput)
      /Sqr(SCALE)) + (0.375*(-1 + 2*Log(Sqr(mAInput)/Sqr(SCALE)))*Sqr(TanBeta))/(1
      + Sqr(TanBeta)) + 0.5*TCF(6)(Sqrt(msd2(2,2))/MuInput) + TCF(6)(Sqrt(msq2(2,
      2))/MuInput)) + 0.008443431970194815*Sqr(g3)*(1 + Log(Sqr(M3Input)/Sqr(SCALE
      )) + TCF(6)(Sqrt(msd2(2,2))/M3Input) + TCF(6)(Sqrt(msq2(2,2))/M3Input) - ((
      AbInput - MuInput*TanBeta)*TCF(9)(Sqrt(msq2(2,2))/M3Input,Sqrt(msd2(2,2))
      /M3Input))/M3Input) + (0.006332573977646111*(1 + Sqr(TanBeta))*Sqr(Yu(2,2))*
      (0.5*TCF(6)(Sqrt(msu2(2,2))/MuInput) + (0.5*(AtInput - MuInput/TanBeta)*
      TanBeta*TCF(9)(Sqrt(msq2(2,2))/MuInput,Sqrt(msu2(2,2))/MuInput))/MuInput))
      /Sqr(TanBeta))) + (0.75*Cos(2*ArcTan(TanBeta))*Sqr(AbInput - MuInput*TanBeta
      )*Sqr(Yd(2,2))*(-0.3*Sqr(g1)*TCF(3)(Sqrt(Abs(msq2(2,2)/msd2(2,2)))) + (-0.3*
      Sqr(g1) - Sqr(g2))*TCF(4)(Sqrt(Abs(msq2(2,2)/msd2(2,2))))))/(Sqrt(Abs(msd2(2
      ,2)*msq2(2,2)))*Sqr(1 + (0.006332573977646111*(1 + Sqr(TanBeta))*(0.25*Log(
      Sqr(MuInput)/Sqr(SCALE)) + (0.125*(-1 + 2*Log(Sqr(mAInput)/Sqr(SCALE))))/(1
      + Sqr(TanBeta)) + ((-1 + Log(Sqr(mAInput)/Sqr(SCALE)))*Sqr(TanBeta))/(1 +
      Sqr(TanBeta)))*Sqr(Yu(2,2)))/Sqr(TanBeta) + 0.5*((-0.0031662869888230555*Sqr
      (AbInput - MuInput*TanBeta)*Sqr(Yd(2,2))*TCF(5)(Sqrt(Abs(msq2(2,2)/msd2(2,2)
      ))))/Sqrt(Abs(msd2(2,2)*msq2(2,2))) - (0.0031662869888230555*Sqr(AtInput -
      MuInput/TanBeta)*Sqr(Yu(2,2))*TCF(5)(Sqrt(Abs(msq2(2,2)/msu2(2,2)))))/Sqrt(
      Abs(msq2(2,2)*msu2(2,2)))) + 0.006332573977646111*(1 + Sqr(TanBeta))*Sqr(Yd(
      2,2))*(0.75*Log(Sqr(MuInput)/Sqr(SCALE)) + (0.375*(-1 + 2*Log(Sqr(mAInput)
      /Sqr(SCALE)))*Sqr(TanBeta))/(1 + Sqr(TanBeta)) + 0.5*TCF(6)(Sqrt(msd2(2,2))
      /MuInput) + TCF(6)(Sqrt(msq2(2,2))/MuInput)) + 0.008443431970194815*Sqr(g3)*
      (1 + Log(Sqr(M3Input)/Sqr(SCALE)) + TCF(6)(Sqrt(msd2(2,2))/M3Input) + TCF(6)
      (Sqrt(msq2(2,2))/M3Input) - ((AbInput - MuInput*TanBeta)*TCF(9)(Sqrt(msq2(2,
      2))/M3Input,Sqrt(msd2(2,2))/M3Input))/M3Input) + (0.006332573977646111*(1 +
      Sqr(TanBeta))*Sqr(Yu(2,2))*(0.5*TCF(6)(Sqrt(msu2(2,2))/MuInput) + (0.5*(
      AtInput - MuInput/TanBeta)*TanBeta*TCF(9)(Sqrt(msq2(2,2))/MuInput,Sqrt(msu2(
      2,2))/MuInput))/MuInput))/Sqr(TanBeta))) - (0.25*(0.6*Sqr(g1) + Sqr(g2))*Sqr
      (AbInput - MuInput*TanBeta)*Sqr(Cos(2*ArcTan(TanBeta)))*Sqr(Yd(2,2))*TCF(5)(
      Sqrt(Abs(msq2(2,2)/msd2(2,2)))))/(Sqrt(Abs(msd2(2,2)*msq2(2,2)))*Sqr(1 + (
      0.006332573977646111*(1 + Sqr(TanBeta))*(0.25*Log(Sqr(MuInput)/Sqr(SCALE)) +
      (0.125*(-1 + 2*Log(Sqr(mAInput)/Sqr(SCALE))))/(1 + Sqr(TanBeta)) + ((-1 +
      Log(Sqr(mAInput)/Sqr(SCALE)))*Sqr(TanBeta))/(1 + Sqr(TanBeta)))*Sqr(Yu(2,2))
      )/Sqr(TanBeta) + 0.5*((-0.0031662869888230555*Sqr(AbInput - MuInput*TanBeta)
      *Sqr(Yd(2,2))*TCF(5)(Sqrt(Abs(msq2(2,2)/msd2(2,2)))))/Sqrt(Abs(msd2(2,2)*
      msq2(2,2))) - (0.0031662869888230555*Sqr(AtInput - MuInput/TanBeta)*Sqr(Yu(2
      ,2))*TCF(5)(Sqrt(Abs(msq2(2,2)/msu2(2,2)))))/Sqrt(Abs(msq2(2,2)*msu2(2,2))))
      + 0.006332573977646111*(1 + Sqr(TanBeta))*Sqr(Yd(2,2))*(0.75*Log(Sqr(
      MuInput)/Sqr(SCALE)) + (0.375*(-1 + 2*Log(Sqr(mAInput)/Sqr(SCALE)))*Sqr(
      TanBeta))/(1 + Sqr(TanBeta)) + 0.5*TCF(6)(Sqrt(msd2(2,2))/MuInput) + TCF(6)(
      Sqrt(msq2(2,2))/MuInput)) + 0.008443431970194815*Sqr(g3)*(1 + Log(Sqr(
      M3Input)/Sqr(SCALE)) + TCF(6)(Sqrt(msd2(2,2))/M3Input) + TCF(6)(Sqrt(msq2(2,
      2))/M3Input) - ((AbInput - MuInput*TanBeta)*TCF(9)(Sqrt(msq2(2,2))/M3Input,
      Sqrt(msd2(2,2))/M3Input))/M3Input) + (0.006332573977646111*(1 + Sqr(TanBeta)
      )*Sqr(Yu(2,2))*(0.5*TCF(6)(Sqrt(msu2(2,2))/MuInput) + (0.5*(AtInput -
      MuInput/TanBeta)*TanBeta*TCF(9)(Sqrt(msq2(2,2))/MuInput,Sqrt(msu2(2,2))
      /MuInput))/MuInput))/Sqr(TanBeta)))) + 0.006332573977646111*(
      0.0033333333333333335*(6*Quad(g1)*(Log(msd2(0,0)/Sqr(SCALE))*(1 + (DeltaEFT*
      Sqr(v))/Abs(msd2(0,0))) + Log(msd2(1,1)/Sqr(SCALE))*(1 + (DeltaEFT*Sqr(v))
      /Abs(msd2(1,1))) + Log(msd2(2,2)/Sqr(SCALE))*(1 + (DeltaEFT*Sqr(v))/Abs(msd2
      (2,2)))) + 18*Quad(g1)*(Log(mse2(0,0)/Sqr(SCALE))*(1 + (DeltaEFT*Sqr(v))/Abs
      (mse2(0,0))) + Log(mse2(1,1)/Sqr(SCALE))*(1 + (DeltaEFT*Sqr(v))/Abs(mse2(1,1
      ))) + Log(mse2(2,2)/Sqr(SCALE))*(1 + (DeltaEFT*Sqr(v))/Abs(mse2(2,2)))) + (9
      *Quad(g1) + 25*Quad(g2))*(Log(msl2(0,0)/Sqr(SCALE))*(1 + (DeltaEFT*Sqr(v))
      /Abs(msl2(0,0))) + Log(msl2(1,1)/Sqr(SCALE))*(1 + (DeltaEFT*Sqr(v))/Abs(msl2
      (1,1))) + Log(msl2(2,2)/Sqr(SCALE))*(1 + (DeltaEFT*Sqr(v))/Abs(msl2(2,2))))
      + 3*(Quad(g1) + 25*Quad(g2))*(Log(msq2(0,0)/Sqr(SCALE))*(1 + (DeltaEFT*Sqr(v
      ))/Abs(msq2(0,0))) + Log(msq2(1,1)/Sqr(SCALE))*(1 + (DeltaEFT*Sqr(v))/Abs(
      msq2(1,1))) + Log(msq2(2,2)/Sqr(SCALE))*(1 + (DeltaEFT*Sqr(v))/Abs(msq2(2,2)
      ))) + 24*Quad(g1)*(Log(msu2(0,0)/Sqr(SCALE))*(1 + (DeltaEFT*Sqr(v))/Abs(msu2
      (0,0))) + Log(msu2(1,1)/Sqr(SCALE))*(1 + (DeltaEFT*Sqr(v))/Abs(msu2(1,1))) +
      Log(msu2(2,2)/Sqr(SCALE))*(1 + (DeltaEFT*Sqr(v))/Abs(msu2(2,2)))))*Sqr(Cos(
      2*ArcTan(TanBeta))) + (1 + (DeltaEFT*Sqr(v))/Sqr(mAInput))*(
      0.00020833333333333335*Log(Sqr(mAInput)/Sqr(SCALE))*(261*Quad(g1) + 1325*
      Quad(g2) + 630*Sqr(g1)*Sqr(g2) - 4*Cos(4*ArcTan(TanBeta))*(9*Quad(g1) + 175*
      Quad(g2) + 90*Sqr(g1)*Sqr(g2)) - 9*Cos(8*ArcTan(TanBeta))*Sqr(3*Sqr(g1) + 5*
      Sqr(g2))) - 0.1875*Sqr(0.6*Sqr(g1) + Sqr(g2))*Sqr(Sin(4*ArcTan(TanBeta)))) +
      3*Log(msu2(2,2)/Sqr(SCALE))*(1 + (DeltaEFT*Sqr(v))/Abs(msu2(2,2)))*Sqr(Yu(2
      ,2))*(0.4*Cos(2*ArcTan(TanBeta))*Sqr(g1) + Sqr(Yu(2,2))) + 3*Log(msq2(2,2)
      /Sqr(SCALE))*(1 + (DeltaEFT*Sqr(v))/Abs(msq2(2,2)))*Sqr(Yu(2,2))*(0.5*Cos(2*
      ArcTan(TanBeta))*(-0.2*Sqr(g1) + Sqr(g2)) + Sqr(Yu(2,2))) + (1 + (DeltaEFT*
      Sqr(v))/Min(Abs(msq2(2,2)),Abs(msu2(2,2))))*((6*Quad(Yu(2,2))*Sqr(AtInput -
      MuInput/TanBeta)*(TCF(1)(Sqrt(Abs(msq2(2,2)/msu2(2,2)))) - (
      0.08333333333333333*Sqr(AtInput - MuInput/TanBeta)*TCF(2)(Sqrt(Abs(msq2(2,2)
      /msu2(2,2)))))/Sqrt(Abs(msq2(2,2)*msu2(2,2)))))/Sqrt(Abs(msq2(2,2)*msu2(2,2)
      )) + (0.75*Cos(2*ArcTan(TanBeta))*Sqr(AtInput - MuInput/TanBeta)*Sqr(Yu(2,2)
      )*(0.6*Sqr(g1)*TCF(3)(Sqrt(Abs(msq2(2,2)/msu2(2,2)))) + Sqr(g2)*TCF(4)(Sqrt(
      Abs(msq2(2,2)/msu2(2,2))))))/Sqrt(Abs(msq2(2,2)*msu2(2,2))) - (0.25*(0.6*Sqr
      (g1) + Sqr(g2))*Sqr(AtInput - MuInput/TanBeta)*Sqr(Cos(2*ArcTan(TanBeta)))*
      Sqr(Yu(2,2))*TCF(5)(Sqrt(Abs(msq2(2,2)/msu2(2,2)))))/Sqrt(Abs(msq2(2,2)*msu2
      (2,2))))))));


   check_non_perturbative();
}

bool HSSUSY_high_scale_constraint<Two_scale>::check_non_perturbative()
{
   bool problem = false;

   const auto g1 = MODELPARAMETER(g1);
   const auto g2 = MODELPARAMETER(g2);
   const auto g3 = MODELPARAMETER(g3);
   const auto Lambdax = MODELPARAMETER(Lambdax);
   const auto Yu = MODELPARAMETER(Yu);
   const auto Yd = MODELPARAMETER(Yd);
   const auto Ye = MODELPARAMETER(Ye);

   if (MaxAbsValue(g1) > 3.5449077018110318) {
      problem = true;
      model->get_problems().flag_non_perturbative_parameter(HSSUSY_info::g1, MaxAbsValue(g1), model->get_scale(), 3.5449077018110318);
   } else {
      model->get_problems().unflag_non_perturbative_parameter(HSSUSY_info::g1);
   }
   if (MaxAbsValue(g2) > 3.5449077018110318) {
      problem = true;
      model->get_problems().flag_non_perturbative_parameter(HSSUSY_info::g2, MaxAbsValue(g2), model->get_scale(), 3.5449077018110318);
   } else {
      model->get_problems().unflag_non_perturbative_parameter(HSSUSY_info::g2);
   }
   if (MaxAbsValue(g3) > 3.5449077018110318) {
      problem = true;
      model->get_problems().flag_non_perturbative_parameter(HSSUSY_info::g3, MaxAbsValue(g3), model->get_scale(), 3.5449077018110318);
   } else {
      model->get_problems().unflag_non_perturbative_parameter(HSSUSY_info::g3);
   }
   if (MaxAbsValue(Lambdax) > 3.5449077018110318) {
      problem = true;
      model->get_problems().flag_non_perturbative_parameter(HSSUSY_info::Lambdax, MaxAbsValue(Lambdax), model->get_scale(), 3.5449077018110318);
   } else {
      model->get_problems().unflag_non_perturbative_parameter(HSSUSY_info::Lambdax);
   }
   if (MaxAbsValue(Yu(0,0)) > 3.5449077018110318) {
      problem = true;
      model->get_problems().flag_non_perturbative_parameter(HSSUSY_info::Yu0_0, MaxAbsValue(Yu(0,0)), model->get_scale(), 3.5449077018110318);
   } else {
      model->get_problems().unflag_non_perturbative_parameter(HSSUSY_info::Yu0_0);
   }

   if (MaxAbsValue(Yu(0,1)) > 3.5449077018110318) {
      problem = true;
      model->get_problems().flag_non_perturbative_parameter(HSSUSY_info::Yu0_1, MaxAbsValue(Yu(0,1)), model->get_scale(), 3.5449077018110318);
   } else {
      model->get_problems().unflag_non_perturbative_parameter(HSSUSY_info::Yu0_1);
   }

   if (MaxAbsValue(Yu(0,2)) > 3.5449077018110318) {
      problem = true;
      model->get_problems().flag_non_perturbative_parameter(HSSUSY_info::Yu0_2, MaxAbsValue(Yu(0,2)), model->get_scale(), 3.5449077018110318);
   } else {
      model->get_problems().unflag_non_perturbative_parameter(HSSUSY_info::Yu0_2);
   }

   if (MaxAbsValue(Yu(1,0)) > 3.5449077018110318) {
      problem = true;
      model->get_problems().flag_non_perturbative_parameter(HSSUSY_info::Yu1_0, MaxAbsValue(Yu(1,0)), model->get_scale(), 3.5449077018110318);
   } else {
      model->get_problems().unflag_non_perturbative_parameter(HSSUSY_info::Yu1_0);
   }

   if (MaxAbsValue(Yu(1,1)) > 3.5449077018110318) {
      problem = true;
      model->get_problems().flag_non_perturbative_parameter(HSSUSY_info::Yu1_1, MaxAbsValue(Yu(1,1)), model->get_scale(), 3.5449077018110318);
   } else {
      model->get_problems().unflag_non_perturbative_parameter(HSSUSY_info::Yu1_1);
   }

   if (MaxAbsValue(Yu(1,2)) > 3.5449077018110318) {
      problem = true;
      model->get_problems().flag_non_perturbative_parameter(HSSUSY_info::Yu1_2, MaxAbsValue(Yu(1,2)), model->get_scale(), 3.5449077018110318);
   } else {
      model->get_problems().unflag_non_perturbative_parameter(HSSUSY_info::Yu1_2);
   }

   if (MaxAbsValue(Yu(2,0)) > 3.5449077018110318) {
      problem = true;
      model->get_problems().flag_non_perturbative_parameter(HSSUSY_info::Yu2_0, MaxAbsValue(Yu(2,0)), model->get_scale(), 3.5449077018110318);
   } else {
      model->get_problems().unflag_non_perturbative_parameter(HSSUSY_info::Yu2_0);
   }

   if (MaxAbsValue(Yu(2,1)) > 3.5449077018110318) {
      problem = true;
      model->get_problems().flag_non_perturbative_parameter(HSSUSY_info::Yu2_1, MaxAbsValue(Yu(2,1)), model->get_scale(), 3.5449077018110318);
   } else {
      model->get_problems().unflag_non_perturbative_parameter(HSSUSY_info::Yu2_1);
   }

   if (MaxAbsValue(Yu(2,2)) > 3.5449077018110318) {
      problem = true;
      model->get_problems().flag_non_perturbative_parameter(HSSUSY_info::Yu2_2, MaxAbsValue(Yu(2,2)), model->get_scale(), 3.5449077018110318);
   } else {
      model->get_problems().unflag_non_perturbative_parameter(HSSUSY_info::Yu2_2);
   }
   if (MaxAbsValue(Yd(0,0)) > 3.5449077018110318) {
      problem = true;
      model->get_problems().flag_non_perturbative_parameter(HSSUSY_info::Yd0_0, MaxAbsValue(Yd(0,0)), model->get_scale(), 3.5449077018110318);
   } else {
      model->get_problems().unflag_non_perturbative_parameter(HSSUSY_info::Yd0_0);
   }

   if (MaxAbsValue(Yd(0,1)) > 3.5449077018110318) {
      problem = true;
      model->get_problems().flag_non_perturbative_parameter(HSSUSY_info::Yd0_1, MaxAbsValue(Yd(0,1)), model->get_scale(), 3.5449077018110318);
   } else {
      model->get_problems().unflag_non_perturbative_parameter(HSSUSY_info::Yd0_1);
   }

   if (MaxAbsValue(Yd(0,2)) > 3.5449077018110318) {
      problem = true;
      model->get_problems().flag_non_perturbative_parameter(HSSUSY_info::Yd0_2, MaxAbsValue(Yd(0,2)), model->get_scale(), 3.5449077018110318);
   } else {
      model->get_problems().unflag_non_perturbative_parameter(HSSUSY_info::Yd0_2);
   }

   if (MaxAbsValue(Yd(1,0)) > 3.5449077018110318) {
      problem = true;
      model->get_problems().flag_non_perturbative_parameter(HSSUSY_info::Yd1_0, MaxAbsValue(Yd(1,0)), model->get_scale(), 3.5449077018110318);
   } else {
      model->get_problems().unflag_non_perturbative_parameter(HSSUSY_info::Yd1_0);
   }

   if (MaxAbsValue(Yd(1,1)) > 3.5449077018110318) {
      problem = true;
      model->get_problems().flag_non_perturbative_parameter(HSSUSY_info::Yd1_1, MaxAbsValue(Yd(1,1)), model->get_scale(), 3.5449077018110318);
   } else {
      model->get_problems().unflag_non_perturbative_parameter(HSSUSY_info::Yd1_1);
   }

   if (MaxAbsValue(Yd(1,2)) > 3.5449077018110318) {
      problem = true;
      model->get_problems().flag_non_perturbative_parameter(HSSUSY_info::Yd1_2, MaxAbsValue(Yd(1,2)), model->get_scale(), 3.5449077018110318);
   } else {
      model->get_problems().unflag_non_perturbative_parameter(HSSUSY_info::Yd1_2);
   }

   if (MaxAbsValue(Yd(2,0)) > 3.5449077018110318) {
      problem = true;
      model->get_problems().flag_non_perturbative_parameter(HSSUSY_info::Yd2_0, MaxAbsValue(Yd(2,0)), model->get_scale(), 3.5449077018110318);
   } else {
      model->get_problems().unflag_non_perturbative_parameter(HSSUSY_info::Yd2_0);
   }

   if (MaxAbsValue(Yd(2,1)) > 3.5449077018110318) {
      problem = true;
      model->get_problems().flag_non_perturbative_parameter(HSSUSY_info::Yd2_1, MaxAbsValue(Yd(2,1)), model->get_scale(), 3.5449077018110318);
   } else {
      model->get_problems().unflag_non_perturbative_parameter(HSSUSY_info::Yd2_1);
   }

   if (MaxAbsValue(Yd(2,2)) > 3.5449077018110318) {
      problem = true;
      model->get_problems().flag_non_perturbative_parameter(HSSUSY_info::Yd2_2, MaxAbsValue(Yd(2,2)), model->get_scale(), 3.5449077018110318);
   } else {
      model->get_problems().unflag_non_perturbative_parameter(HSSUSY_info::Yd2_2);
   }
   if (MaxAbsValue(Ye(0,0)) > 3.5449077018110318) {
      problem = true;
      model->get_problems().flag_non_perturbative_parameter(HSSUSY_info::Ye0_0, MaxAbsValue(Ye(0,0)), model->get_scale(), 3.5449077018110318);
   } else {
      model->get_problems().unflag_non_perturbative_parameter(HSSUSY_info::Ye0_0);
   }

   if (MaxAbsValue(Ye(0,1)) > 3.5449077018110318) {
      problem = true;
      model->get_problems().flag_non_perturbative_parameter(HSSUSY_info::Ye0_1, MaxAbsValue(Ye(0,1)), model->get_scale(), 3.5449077018110318);
   } else {
      model->get_problems().unflag_non_perturbative_parameter(HSSUSY_info::Ye0_1);
   }

   if (MaxAbsValue(Ye(0,2)) > 3.5449077018110318) {
      problem = true;
      model->get_problems().flag_non_perturbative_parameter(HSSUSY_info::Ye0_2, MaxAbsValue(Ye(0,2)), model->get_scale(), 3.5449077018110318);
   } else {
      model->get_problems().unflag_non_perturbative_parameter(HSSUSY_info::Ye0_2);
   }

   if (MaxAbsValue(Ye(1,0)) > 3.5449077018110318) {
      problem = true;
      model->get_problems().flag_non_perturbative_parameter(HSSUSY_info::Ye1_0, MaxAbsValue(Ye(1,0)), model->get_scale(), 3.5449077018110318);
   } else {
      model->get_problems().unflag_non_perturbative_parameter(HSSUSY_info::Ye1_0);
   }

   if (MaxAbsValue(Ye(1,1)) > 3.5449077018110318) {
      problem = true;
      model->get_problems().flag_non_perturbative_parameter(HSSUSY_info::Ye1_1, MaxAbsValue(Ye(1,1)), model->get_scale(), 3.5449077018110318);
   } else {
      model->get_problems().unflag_non_perturbative_parameter(HSSUSY_info::Ye1_1);
   }

   if (MaxAbsValue(Ye(1,2)) > 3.5449077018110318) {
      problem = true;
      model->get_problems().flag_non_perturbative_parameter(HSSUSY_info::Ye1_2, MaxAbsValue(Ye(1,2)), model->get_scale(), 3.5449077018110318);
   } else {
      model->get_problems().unflag_non_perturbative_parameter(HSSUSY_info::Ye1_2);
   }

   if (MaxAbsValue(Ye(2,0)) > 3.5449077018110318) {
      problem = true;
      model->get_problems().flag_non_perturbative_parameter(HSSUSY_info::Ye2_0, MaxAbsValue(Ye(2,0)), model->get_scale(), 3.5449077018110318);
   } else {
      model->get_problems().unflag_non_perturbative_parameter(HSSUSY_info::Ye2_0);
   }

   if (MaxAbsValue(Ye(2,1)) > 3.5449077018110318) {
      problem = true;
      model->get_problems().flag_non_perturbative_parameter(HSSUSY_info::Ye2_1, MaxAbsValue(Ye(2,1)), model->get_scale(), 3.5449077018110318);
   } else {
      model->get_problems().unflag_non_perturbative_parameter(HSSUSY_info::Ye2_1);
   }

   if (MaxAbsValue(Ye(2,2)) > 3.5449077018110318) {
      problem = true;
      model->get_problems().flag_non_perturbative_parameter(HSSUSY_info::Ye2_2, MaxAbsValue(Ye(2,2)), model->get_scale(), 3.5449077018110318);
   } else {
      model->get_problems().unflag_non_perturbative_parameter(HSSUSY_info::Ye2_2);
   }


   return problem;
}

double HSSUSY_high_scale_constraint<Two_scale>::get_scale() const
{
   return scale;
}

double HSSUSY_high_scale_constraint<Two_scale>::get_initial_scale_guess() const
{
   return initial_scale_guess;
}

const HSSUSY_input_parameters& HSSUSY_high_scale_constraint<Two_scale>::get_input_parameters() const
{
   return model->get_input();
}

HSSUSY<Two_scale>* HSSUSY_high_scale_constraint<Two_scale>::get_model() const
{
   return model;
}

void HSSUSY_high_scale_constraint<Two_scale>::set_model(Model* model_)
{
   model = cast_model<HSSUSY<Two_scale>*>(model_);
}

void HSSUSY_high_scale_constraint<Two_scale>::set_scale(double s)
{
   scale = s;
}

void HSSUSY_high_scale_constraint<Two_scale>::clear()
{
   scale = 0.;
   initial_scale_guess = 0.;
   model = nullptr;
}

void HSSUSY_high_scale_constraint<Two_scale>::initialize()
{
   check_model_ptr();

   const auto MSUSY = INPUTPARAMETER(MSUSY);

   initial_scale_guess = MSUSY;

   scale = initial_scale_guess;
}

void HSSUSY_high_scale_constraint<Two_scale>::update_scale()
{
   check_model_ptr();

   const auto MSUSY = INPUTPARAMETER(MSUSY);

   scale = MSUSY;


}

void HSSUSY_high_scale_constraint<Two_scale>::check_model_ptr() const
{
   if (!model)
      throw SetupError("HSSUSY_high_scale_constraint<Two_scale>: "
                       "model pointer is zero!");
}

} // namespace flexiblesusy
