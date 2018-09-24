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

// File generated at Thu 10 May 2018 14:34:50

#include "MSSMatMGUTEFTHiggs_mAmu_standard_model_matching.hpp"
#include "wrappers.hpp"
#include "single_scale_matching.hpp"
#include "loop_corrections.hpp"
#include "standard_model.hpp"
#include "MSSMatMGUTEFTHiggs_mAmu_mass_eigenstates.hpp"
#include "MSSMatMGUTEFTHiggs_mAmu_info.hpp"
#include "config.h"
#include "global_thread_pool.hpp"
#include <cmath>

using namespace flexiblesusy::standard_model;

namespace flexiblesusy {
namespace MSSMatMGUTEFTHiggs_mAmu_standard_model_matching {

#define MODELPARAMETER(p) model.get_##p()
#define EXTRAPARAMETER(parameter) model.get_##parameter()
#define SMPARAMETER(p) sm.get_##p()
#define INPUTPARAMETER(p) model.get_input().p
#define PHASE(p) model.get_##p()
#define LowEnergyConstant(p) Electroweak_constants::p
#define Pole(p) model.get_physical().p
#define SCALE model.get_scale()

namespace {

/**
 * Returns SM parameters with tree-level lambda.  The tree-level
 * lambda is calculated from the tree-level MSSMatMGUTEFTHiggs_mAmu parameters.
 *
 * @param sm SM parameters
 * @param model_0l MSSMatMGUTEFTHiggs_mAmu tree-level parameters
 * @param idx Index of SM-like Higgs in the Higgs multiplet
 *
 * @return SM tree-level parameters
 */
Standard_model calculate_SM_tree_level(
   const Standard_model& sm,
   const MSSMatMGUTEFTHiggs_mAmu_mass_eigenstates& model_0l,
   int idx)
{
   auto sm_0l = sm;
   sm_0l.get_problems().clear();
   sm_0l.set_Lambdax(Sqr(model_0l.get_Mhh(idx)/sm.get_v()));
   sm_0l.set_pole_mass_loop_order(0);
   sm_0l.set_ewsb_loop_order(0);
   sm_0l.solve_ewsb_tree_level();
   sm_0l.calculate_DRbar_masses();

   return sm_0l;
}

/**
 * Calculates MSSMatMGUTEFTHiggs_mAmu tree-level parameters (g1, g2, g3, Yu, Yd,
 * Ye, v) by performing a tree-level matching from the SM to the
 * MSSMatMGUTEFTHiggs_mAmu.
 *
 * @param model MSSMatMGUTEFTHiggs_mAmu parameters
 * @param sm SM parameters
 *
 * @return MSSMatMGUTEFTHiggs_mAmu with tree-level parameters
 */
MSSMatMGUTEFTHiggs_mAmu_mass_eigenstates calculate_MSSMatMGUTEFTHiggs_mAmu_tree_level(
   const MSSMatMGUTEFTHiggs_mAmu_mass_eigenstates& model,
   const Standard_model& sm)
{
   auto model_0l = model;
   model_0l.get_problems().clear();
   model_0l.set_pole_mass_loop_order(0);
   model_0l.set_ewsb_loop_order(0);
   model_0l.solve_ewsb_tree_level();
   model_0l.calculate_DRbar_masses();

   match_low_to_high_scale_model_tree_level(model_0l, sm);

   return model_0l;
}

/**
 * Calculates squared Higgs pole mass in the SM,
 * \f$(M_h^{\text{SM}})^2\f$.
 *
 * @param sm_0l SM parameters with tree-level lambda
 *
 * @return squared Higgs pole mass in the SM
 */
double calculate_Mh2_pole(const Standard_model& sm_0l)
{
   const double p = sm_0l.get_Mhh();
   const double self_energy = Re(sm_0l.self_energy_hh_1loop(p));
   const double tadpole = Re(sm_0l.tadpole_hh_1loop() / sm_0l.get_v());
   const double mh2_tree = Sqr(sm_0l.get_Mhh());
   const double Mh2_pole = mh2_tree - self_energy + tadpole;

   return Mh2_pole;
}

/**
 * Calculates tadpoles over vevs (at given fixed loop order)
 *
 * @param model model parameters
 * @param loop_order loop order
 *
 * @return tadpole at loop order
 */
Eigen::Matrix<double,2,1> calculate_tadpole_over_vevs(
   MSSMatMGUTEFTHiggs_mAmu_mass_eigenstates model, int loop_order)
{
   if (loop_order == 0) {
      model.set_ewsb_loop_order(loop_order);
      return model.tadpole_equations_over_vevs();
   }

   model.set_ewsb_loop_order(loop_order);
   const auto tadpole_lo = model.tadpole_equations_over_vevs(); // nL

   model.set_ewsb_loop_order(loop_order - 1);
   const auto tadpole_lom1 = model.tadpole_equations_over_vevs(); // (n-1)L

   return (tadpole_lo - tadpole_lom1).eval();
}

/**
 * Calculates tree-level Higgs mass matrix in the MSSMatMGUTEFTHiggs_mAmu without
 * including tadpoles implicitly.  This is achieved by solving the
 * EWSB equations at tree-level in order to avoid the inclusion of
 * loop tadpoles.
 *
 * @param model MSSMatMGUTEFTHiggs_mAmu parameters
 * @return tree-level Higgs mass matrix in the MSSMatMGUTEFTHiggs_mAmu w/o tadpoles
 */
auto calculate_mh2_tree_level(MSSMatMGUTEFTHiggs_mAmu_mass_eigenstates model) -> decltype(model.get_mass_matrix_hh())
{
   model.solve_ewsb_tree_level();
   return model.get_mass_matrix_hh();
}

/**
 * Calculates squared Higgs pole mass in the MSSMatMGUTEFTHiggs_mAmu,
 * \f$(M_h^{\text{MSSMatMGUTEFTHiggs_mAmu}})^2\f$.
 *
 * @param model_0l tree-level MSSMatMGUTEFTHiggs_mAmu parameters
 * @param model_1l 1-loop MSSMatMGUTEFTHiggs_mAmu parameters
 * @param idx Higgs index (in mass ordered Higgs multiplet)
 *
 * @return squared Higgs pole mass in the MSSMatMGUTEFTHiggs_mAmu
 */
double calculate_Mh2_pole(
   const MSSMatMGUTEFTHiggs_mAmu_mass_eigenstates& model_0l,
   const MSSMatMGUTEFTHiggs_mAmu_mass_eigenstates& model_1l,
   int idx)
{
   // calculate tree-level mass matrix
   const auto mh2_tree = calculate_mh2_tree_level(model_1l);

   // calculate 1L self-energy using tree-level parameters
   const double p = model_0l.get_Mhh(idx);
   const auto self_energy = Re(model_0l.self_energy_hh_1loop(p));

   // calculate 1L tadpoles using tree-level parameters
   const auto tadpole = calculate_tadpole_over_vevs(model_0l, 1);

   double Mh2_pole = 0.;

   const auto M_loop = (mh2_tree - self_energy - Eigen::Matrix<double,2,2>(tadpole.asDiagonal())).eval();

   Eigen::Array<double,2,1> M_pole;
   fs_diagonalize_hermitian(M_loop, M_pole);

   Mh2_pole = M_pole(idx);

   return Mh2_pole;
}

/**
 * Calculates \f$\lambda(Q)\f$ at the current loop level from the
 * lightest CP-even Higgs boson mass of the MSSMatMGUTEFTHiggs_mAmu by requiring
 * that the Higgs pole masses are equal in both models.
 *
 * @param sm Standard Model
 * @param model_1l MSSMatMGUTEFTHiggs_mAmu parameters
 * @param idx Higgs index (in mass ordered Higgs multiplet)
 */
void match_high_to_low_scale_model_1loop(
   Standard_model& sm,
   const MSSMatMGUTEFTHiggs_mAmu_mass_eigenstates& model_1l,
   int idx)
{
   // tree-level MSSMatMGUTEFTHiggs_mAmu parameters
   const auto model_0l = calculate_MSSMatMGUTEFTHiggs_mAmu_tree_level(model_1l, sm);
   const auto sm_0l = calculate_SM_tree_level(sm, model_0l, idx);

   const double mh2_sm = Sqr(sm_0l.get_Mhh());
   const double Mh2_sm = calculate_Mh2_pole(sm_0l);
   const double Mh2_bsm = calculate_Mh2_pole(model_0l, model_1l, idx);

   sm.set_Lambdax((Mh2_bsm - Mh2_sm + mh2_sm)/Sqr(sm.get_v()));
}

double calculate_delta_alpha_em(double alpha_em, const MSSMatMGUTEFTHiggs_mAmu_mass_eigenstates& model)
{
   const double currentScale = model.get_scale();
   double delta_alpha_em = 0.;

   const auto MCha = MODELPARAMETER(MCha);
   const auto MHpm = MODELPARAMETER(MHpm);
   const auto MSd = MODELPARAMETER(MSd);
   const auto MSe = MODELPARAMETER(MSe);
   const auto MSu = MODELPARAMETER(MSu);

   delta_alpha_em += alpha_em/(2.*Pi)*(0.3333333333333333 - 1.3333333333333333*
      FiniteLog(Abs(MCha(0)/currentScale)) - 1.3333333333333333*FiniteLog(Abs(MCha
      (1)/currentScale)) - 0.3333333333333333*FiniteLog(Abs(MHpm(1)/currentScale))
      - 0.1111111111111111*FiniteLog(Abs(MSd(0)/currentScale)) -
      0.1111111111111111*FiniteLog(Abs(MSd(1)/currentScale)) - 0.1111111111111111*
      FiniteLog(Abs(MSd(2)/currentScale)) - 0.1111111111111111*FiniteLog(Abs(MSd(3
      )/currentScale)) - 0.1111111111111111*FiniteLog(Abs(MSd(4)/currentScale)) -
      0.1111111111111111*FiniteLog(Abs(MSd(5)/currentScale)) - 0.3333333333333333*
      FiniteLog(Abs(MSe(0)/currentScale)) - 0.3333333333333333*FiniteLog(Abs(MSe(1
      )/currentScale)) - 0.3333333333333333*FiniteLog(Abs(MSe(2)/currentScale)) -
      0.3333333333333333*FiniteLog(Abs(MSe(3)/currentScale)) - 0.3333333333333333*
      FiniteLog(Abs(MSe(4)/currentScale)) - 0.3333333333333333*FiniteLog(Abs(MSe(5
      )/currentScale)) - 0.4444444444444444*FiniteLog(Abs(MSu(0)/currentScale)) -
      0.4444444444444444*FiniteLog(Abs(MSu(1)/currentScale)) - 0.4444444444444444*
      FiniteLog(Abs(MSu(2)/currentScale)) - 0.4444444444444444*FiniteLog(Abs(MSu(3
      )/currentScale)) - 0.4444444444444444*FiniteLog(Abs(MSu(4)/currentScale)) -
      0.4444444444444444*FiniteLog(Abs(MSu(5)/currentScale)));


   return delta_alpha_em;
}

double calculate_delta_alpha_s(double alpha_s, const MSSMatMGUTEFTHiggs_mAmu_mass_eigenstates& model)
{
   const double currentScale = model.get_scale();
   double delta_alpha_s = 0.;

   const auto MSd = MODELPARAMETER(MSd);
   const auto MSu = MODELPARAMETER(MSu);
   const auto MGlu = MODELPARAMETER(MGlu);

   delta_alpha_s += alpha_s/(2.*Pi)*(0.5 - 2*FiniteLog(Abs(MGlu/currentScale))
      - 0.16666666666666666*FiniteLog(Abs(MSd(0)/currentScale)) -
      0.16666666666666666*FiniteLog(Abs(MSd(1)/currentScale)) -
      0.16666666666666666*FiniteLog(Abs(MSd(2)/currentScale)) -
      0.16666666666666666*FiniteLog(Abs(MSd(3)/currentScale)) -
      0.16666666666666666*FiniteLog(Abs(MSd(4)/currentScale)) -
      0.16666666666666666*FiniteLog(Abs(MSd(5)/currentScale)) -
      0.16666666666666666*FiniteLog(Abs(MSu(0)/currentScale)) -
      0.16666666666666666*FiniteLog(Abs(MSu(1)/currentScale)) -
      0.16666666666666666*FiniteLog(Abs(MSu(2)/currentScale)) -
      0.16666666666666666*FiniteLog(Abs(MSu(3)/currentScale)) -
      0.16666666666666666*FiniteLog(Abs(MSu(4)/currentScale)) -
      0.16666666666666666*FiniteLog(Abs(MSu(5)/currentScale)));


   return delta_alpha_s;
}

Eigen::Matrix<double,3,3> calculate_MFu_DRbar_tree_level(const MSSMatMGUTEFTHiggs_mAmu_mass_eigenstates& model)
{
   Eigen::Matrix<double,3,3> mf = ZEROMATRIX(3,3);

   mf(0,0) = model.get_MFu(0);
   mf(1,1) = model.get_MFu(1);
   mf(2,2) = model.get_MFu(2);


   return mf;
}

Eigen::Matrix<double,3,3> calculate_MFd_DRbar_tree_level(const MSSMatMGUTEFTHiggs_mAmu_mass_eigenstates& model)
{
   Eigen::Matrix<double,3,3> mf = ZEROMATRIX(3,3);

   mf(0,0) = model.get_MFd(0);
   mf(1,1) = model.get_MFd(1);
   mf(2,2) = model.get_MFd(2);


   return mf;
}

Eigen::Matrix<double,3,3> calculate_MFe_DRbar_tree_level(const MSSMatMGUTEFTHiggs_mAmu_mass_eigenstates& model)
{
   Eigen::Matrix<double,3,3> mf = ZEROMATRIX(3,3);

   mf(0,0) = model.get_MFe(0);
   mf(1,1) = model.get_MFe(1);
   mf(2,2) = model.get_MFe(2);


   return mf;
}

double calculate_MFu_pole_1loop(
   int i,
   const Standard_model& sm_0l)
{
   const double p = sm_0l.get_MFu(i);
   const auto self_energy_1  = Re(sm_0l.self_energy_Fu_1loop_1(p));
   const auto self_energy_PL = Re(sm_0l.self_energy_Fu_1loop_PL(p));
   const auto self_energy_PR = Re(sm_0l.self_energy_Fu_1loop_PR(p));
   const auto M_tree = sm_0l.get_mass_matrix_Fu();
   const auto M_loop = (M_tree - self_energy_PR * M_tree
                        - M_tree * self_energy_PL - self_energy_1).eval();

   Eigen::Array<double,3,1> MFu_pole;
   fs_svd(M_loop, MFu_pole);

   return MFu_pole(i);
}

double calculate_MFd_pole_1loop(
   int i,
   const Standard_model& sm_0l)
{
   const double p = sm_0l.get_MFd(i);
   const auto self_energy_1  = Re(sm_0l.self_energy_Fd_1loop_1(p));
   const auto self_energy_PL = Re(sm_0l.self_energy_Fd_1loop_PL(p));
   const auto self_energy_PR = Re(sm_0l.self_energy_Fd_1loop_PR(p));
   const auto M_tree = sm_0l.get_mass_matrix_Fd();
   const auto M_loop = (M_tree - self_energy_PR * M_tree
                        - M_tree * self_energy_PL - self_energy_1).eval();

   Eigen::Array<double,3,1> MFd_pole;
   fs_svd(M_loop, MFd_pole);

   return MFd_pole(i);
}

double calculate_MFe_pole_1loop(
   int i,
   const Standard_model& sm_0l)
{
   const double p = sm_0l.get_MFe(i);
   const auto self_energy_1  = Re(sm_0l.self_energy_Fe_1loop_1(p));
   const auto self_energy_PL = Re(sm_0l.self_energy_Fe_1loop_PL(p));
   const auto self_energy_PR = Re(sm_0l.self_energy_Fe_1loop_PR(p));
   const auto M_tree = sm_0l.get_mass_matrix_Fe();
   const auto M_loop = (M_tree - self_energy_PR * M_tree
                        - M_tree * self_energy_PL - self_energy_1).eval();

   Eigen::Array<double,3,1> MFe_pole;
   fs_svd(M_loop, MFe_pole);

   return MFe_pole(i);
}

double calculate_MFu_pole_1loop(
   int i,
   const MSSMatMGUTEFTHiggs_mAmu_mass_eigenstates& model_0l)
{
   double m_pole = 0.;

   const double p = model_0l.get_MFu(i);
   const auto self_energy_1  = Re(model_0l.self_energy_Fu_1loop_1(p));
   const auto self_energy_PL = Re(model_0l.self_energy_Fu_1loop_PL(p));
   const auto self_energy_PR = Re(model_0l.self_energy_Fu_1loop_PR(p));
   const auto M_tree = model_0l.get_mass_matrix_Fu();
   const auto M_loop = (M_tree - self_energy_PR * M_tree
                        - M_tree * self_energy_PL - self_energy_1).eval();

   Eigen::Array<double,3,1> M_pole;
   fs_svd(M_loop, M_pole);

   m_pole = M_pole(i);

   return m_pole;
}

double calculate_MFd_pole_1loop(
   int i,
   const MSSMatMGUTEFTHiggs_mAmu_mass_eigenstates& model_0l)
{
   double m_pole = 0.;

   const double p = model_0l.get_MFd(i);
   const auto self_energy_1  = Re(model_0l.self_energy_Fd_1loop_1(p));
   const auto self_energy_PL = Re(model_0l.self_energy_Fd_1loop_PL(p));
   const auto self_energy_PR = Re(model_0l.self_energy_Fd_1loop_PR(p));
   const auto M_tree = model_0l.get_mass_matrix_Fd();
   const auto M_loop = (M_tree - self_energy_PR * M_tree
                        - M_tree * self_energy_PL - self_energy_1).eval();

   Eigen::Array<double,3,1> M_pole;
   fs_svd(M_loop, M_pole);

   m_pole = M_pole(i);

   return m_pole;
}

double calculate_MFe_pole_1loop(
   int i,
   const MSSMatMGUTEFTHiggs_mAmu_mass_eigenstates& model_0l)
{
   double m_pole = 0.;

   const double p = model_0l.get_MFe(i);
   const auto self_energy_1  = Re(model_0l.self_energy_Fe_1loop_1(p));
   const auto self_energy_PL = Re(model_0l.self_energy_Fe_1loop_PL(p));
   const auto self_energy_PR = Re(model_0l.self_energy_Fe_1loop_PR(p));
   const auto M_tree = model_0l.get_mass_matrix_Fe();
   const auto M_loop = (M_tree - self_energy_PR * M_tree
                        - M_tree * self_energy_PL - self_energy_1).eval();

   Eigen::Array<double,3,1> M_pole;
   fs_svd(M_loop, M_pole);

   m_pole = M_pole(i);

   return m_pole;
}

Eigen::Matrix<double,3,3> calculate_MFu_pole_1loop(const Standard_model& sm_0l)
{
   Eigen::Matrix<double,3,1> M_pole;

#ifdef ENABLE_THREADS
   auto M_0 = global_thread_pool().run_packaged_task([&sm_0l]{ return calculate_MFu_pole_1loop(0, sm_0l); });
   auto M_1 = global_thread_pool().run_packaged_task([&sm_0l]{ return calculate_MFu_pole_1loop(1, sm_0l); });
   auto M_2 = global_thread_pool().run_packaged_task([&sm_0l]{ return calculate_MFu_pole_1loop(2, sm_0l); });
   M_pole << M_0.get(), M_1.get(), M_2.get();
#else
   M_pole << calculate_MFu_pole_1loop(0, sm_0l),
             calculate_MFu_pole_1loop(1, sm_0l),
             calculate_MFu_pole_1loop(2, sm_0l);
#endif

   return M_pole.asDiagonal();
}

Eigen::Matrix<double,3,3> calculate_MFd_pole_1loop(const Standard_model& sm_0l)
{
   Eigen::Matrix<double,3,1> M_pole;

#ifdef ENABLE_THREADS
   auto M_0 = global_thread_pool().run_packaged_task([&sm_0l]{ return calculate_MFd_pole_1loop(0, sm_0l); });
   auto M_1 = global_thread_pool().run_packaged_task([&sm_0l]{ return calculate_MFd_pole_1loop(1, sm_0l); });
   auto M_2 = global_thread_pool().run_packaged_task([&sm_0l]{ return calculate_MFd_pole_1loop(2, sm_0l); });
   M_pole << M_0.get(), M_1.get(), M_2.get();
#else
   M_pole << calculate_MFd_pole_1loop(0, sm_0l),
             calculate_MFd_pole_1loop(1, sm_0l),
             calculate_MFd_pole_1loop(2, sm_0l);
#endif

   return M_pole.asDiagonal();
}

Eigen::Matrix<double,3,3> calculate_MFe_pole_1loop(const Standard_model& sm_0l)
{
   Eigen::Matrix<double,3,1> M_pole;

#ifdef ENABLE_THREADS
   auto M_0 = global_thread_pool().run_packaged_task([&sm_0l]{ return calculate_MFe_pole_1loop(0, sm_0l); });
   auto M_1 = global_thread_pool().run_packaged_task([&sm_0l]{ return calculate_MFe_pole_1loop(1, sm_0l); });
   auto M_2 = global_thread_pool().run_packaged_task([&sm_0l]{ return calculate_MFe_pole_1loop(2, sm_0l); });
   M_pole << M_0.get(), M_1.get(), M_2.get();
#else
   M_pole << calculate_MFe_pole_1loop(0, sm_0l),
             calculate_MFe_pole_1loop(1, sm_0l),
             calculate_MFe_pole_1loop(2, sm_0l);
#endif

   return M_pole.asDiagonal();
}

Eigen::Matrix<double,3,3> calculate_MFu_pole_1loop(
   const MSSMatMGUTEFTHiggs_mAmu_mass_eigenstates& model_0l)
{
   Eigen::Matrix<double,3,1> M_pole;

#ifdef ENABLE_THREADS
   auto M_0 = global_thread_pool().run_packaged_task([&model_0l]{ return calculate_MFu_pole_1loop(0, model_0l); });
   auto M_1 = global_thread_pool().run_packaged_task([&model_0l]{ return calculate_MFu_pole_1loop(1, model_0l); });
   auto M_2 = global_thread_pool().run_packaged_task([&model_0l]{ return calculate_MFu_pole_1loop(2, model_0l); });
   M_pole << M_0.get(), M_1.get(), M_2.get();
#else
   M_pole << calculate_MFu_pole_1loop(0, model_0l),
             calculate_MFu_pole_1loop(1, model_0l),
             calculate_MFu_pole_1loop(2, model_0l);
#endif

   return M_pole.asDiagonal();
}

Eigen::Matrix<double,3,3> calculate_MFd_pole_1loop(
   const MSSMatMGUTEFTHiggs_mAmu_mass_eigenstates& model_0l)
{
   Eigen::Matrix<double,3,1> M_pole;

#ifdef ENABLE_THREADS
   auto M_0 = global_thread_pool().run_packaged_task([&model_0l]{ return calculate_MFd_pole_1loop(0, model_0l); });
   auto M_1 = global_thread_pool().run_packaged_task([&model_0l]{ return calculate_MFd_pole_1loop(1, model_0l); });
   auto M_2 = global_thread_pool().run_packaged_task([&model_0l]{ return calculate_MFd_pole_1loop(2, model_0l); });
   M_pole << M_0.get(), M_1.get(), M_2.get();
#else
   M_pole << calculate_MFd_pole_1loop(0, model_0l),
             calculate_MFd_pole_1loop(1, model_0l),
             calculate_MFd_pole_1loop(2, model_0l);
#endif

   return M_pole.asDiagonal();
}

Eigen::Matrix<double,3,3> calculate_MFe_pole_1loop(
   const MSSMatMGUTEFTHiggs_mAmu_mass_eigenstates& model_0l)
{
   Eigen::Matrix<double,3,1> M_pole;

#ifdef ENABLE_THREADS
   auto M_0 = global_thread_pool().run_packaged_task([&model_0l]{ return calculate_MFe_pole_1loop(0, model_0l); });
   auto M_1 = global_thread_pool().run_packaged_task([&model_0l]{ return calculate_MFe_pole_1loop(1, model_0l); });
   auto M_2 = global_thread_pool().run_packaged_task([&model_0l]{ return calculate_MFe_pole_1loop(2, model_0l); });
   M_pole << M_0.get(), M_1.get(), M_2.get();
#else
   M_pole << calculate_MFe_pole_1loop(0, model_0l),
             calculate_MFe_pole_1loop(1, model_0l),
             calculate_MFe_pole_1loop(2, model_0l);
#endif

   return M_pole.asDiagonal();
}

Eigen::Matrix<double,3,3> calculate_MFu_DRbar_1loop(
   const Standard_model& sm_0l,
   const MSSMatMGUTEFTHiggs_mAmu_mass_eigenstates& model_0l)
{
   Eigen::Matrix<double,3,3> mf_sm = ZEROMATRIX(3,3);

   const auto Mf_sm  = calculate_MFu_pole_1loop(sm_0l);
   const auto Mf_bsm = calculate_MFu_pole_1loop(model_0l);
   const auto mf_bsm = calculate_MFu_DRbar_tree_level(model_0l);

   mf_sm = mf_bsm - Mf_bsm + Mf_sm;

   return Abs(mf_sm);
}

Eigen::Matrix<double,3,3> calculate_MFd_DRbar_1loop(
   const Standard_model& sm_0l,
   const MSSMatMGUTEFTHiggs_mAmu_mass_eigenstates& model_0l)
{
   Eigen::Matrix<double,3,3> mf_sm = ZEROMATRIX(3,3);

   const auto Mf_sm  = calculate_MFd_pole_1loop(sm_0l);
   const auto Mf_bsm = calculate_MFd_pole_1loop(model_0l);
   const auto mf_bsm = calculate_MFd_DRbar_tree_level(model_0l);

   mf_sm = mf_bsm - Mf_bsm + Mf_sm;

   return Abs(mf_sm);
}

Eigen::Matrix<double,3,3> calculate_MFe_DRbar_1loop(
   const Standard_model& sm_0l,
   const MSSMatMGUTEFTHiggs_mAmu_mass_eigenstates& model_0l)
{
   Eigen::Matrix<double,3,3> mf_sm = ZEROMATRIX(3,3);

   const auto Mf_sm  = calculate_MFe_pole_1loop(sm_0l);
   const auto Mf_bsm = calculate_MFe_pole_1loop(model_0l);
   const auto mf_bsm = calculate_MFe_DRbar_tree_level(model_0l);

   mf_sm = mf_bsm - Mf_bsm + Mf_sm;

   return Abs(mf_sm);
}

double calculate_MW_pole_1loop(const Standard_model& sm_0l)
{
   const double mw = sm_0l.get_MVWp();
   const double p = sm_0l.get_MVWp();
   const double self_energy = Re(sm_0l.self_energy_VWp_1loop(p));
   const double M_loop = Sqr(mw) - self_energy;

   return SignedAbsSqrt(M_loop);
}

double calculate_MW_pole_1loop(const MSSMatMGUTEFTHiggs_mAmu_mass_eigenstates& model_0l)
{
   const double mw = model_0l.get_MVWm();
   const double p = model_0l.get_MVWm();
   const double self_energy = Re(model_0l.self_energy_VWm_1loop(p));
   const double M_loop = Sqr(mw) - self_energy;

   return SignedAbsSqrt(M_loop);
}

double calculate_MZ_pole_1loop(const Standard_model& sm_0l)
{
   const double mz = sm_0l.get_MVZ();
   const double p = sm_0l.get_MVZ();
   const double self_energy = Re(sm_0l.self_energy_VZ_1loop(p));
   const double M_loop = Sqr(mz) - self_energy;

   return SignedAbsSqrt(M_loop);
}

double calculate_MZ_pole_1loop(const MSSMatMGUTEFTHiggs_mAmu_mass_eigenstates& model_0l)
{
   const double mz = model_0l.get_MVZ();
   const double p = model_0l.get_MVZ();
   const double self_energy = Re(model_0l.self_energy_VZ_1loop(p));
   const double M_loop = Sqr(mz) - self_energy;

   return SignedAbsSqrt(M_loop);
}

double calculate_MW_DRbar_1loop(
   const Standard_model& sm_0l,
   const MSSMatMGUTEFTHiggs_mAmu_mass_eigenstates& model_0l)
{
   const double MW_sm = calculate_MW_pole_1loop(sm_0l);
   const double MW_bsm = calculate_MW_pole_1loop(model_0l);
   const double mw2 = Sqr(MW_sm) - Sqr(MW_bsm) + Sqr(model_0l.get_MVWm());

   return AbsSqrt(mw2);
}

double calculate_MZ_DRbar_1loop(
   const Standard_model& sm_0l,
   const MSSMatMGUTEFTHiggs_mAmu_mass_eigenstates& model_0l)
{
   const double MZ_sm = calculate_MZ_pole_1loop(sm_0l);
   const double MZ_bsm = calculate_MZ_pole_1loop(model_0l);
   const double mz2 = Sqr(MZ_sm) - Sqr(MZ_bsm) + Sqr(model_0l.get_MVZ());

   return AbsSqrt(mz2);
}

/**
 * Calculates MSSMatMGUTEFTHiggs_mAmu parameters at 1-loop level by performing a
 * 1-loop matching.
 *
 * @param sm_0l SM parameters (lambda is at tree-level)
 * @param sm_1l SM parameters (level is at 1-loop level)
 * @param model_0l MSSMatMGUTEFTHiggs_mAmu parameters at tree-level
 * @param model_1l MSSMatMGUTEFTHiggs_mAmu parameters at 1-loop level
 *
 * @return MSSMatMGUTEFTHiggs_mAmu 1-loop parameters
 */
MSSMatMGUTEFTHiggs_mAmu_mass_eigenstates calculate_MSSMatMGUTEFTHiggs_mAmu_1loop(
   const Standard_model& sm_0l,
   const Standard_model& sm_1l,
   const MSSMatMGUTEFTHiggs_mAmu_mass_eigenstates& model_0l,
   const MSSMatMGUTEFTHiggs_mAmu_mass_eigenstates& model_1l)
{
   auto model = model_1l;
   auto sm = sm_1l;

   model.calculate_DRbar_masses();
   model.solve_ewsb();

   sm.calculate_DRbar_masses();
   sm.solve_ewsb();

   const double alpha_em = Sqr(sm_0l.get_g1() * sm_0l.get_g2() * standard_model_info::normalization_g1 * standard_model_info::normalization_g2)
            /(4. * Pi * (Sqr(sm_0l.get_g1()*standard_model_info::normalization_g1) + Sqr(sm_0l.get_g2()*standard_model_info::normalization_g2)));
   const double alpha_s  = Sqr(sm_0l.get_g3() * standard_model_info::normalization_g3)/(4. * Pi);
   const double delta_alpha_em = calculate_delta_alpha_em(alpha_em, model_0l);
   const double delta_alpha_s = calculate_delta_alpha_s(alpha_s, model_0l);

   // running MSSMatMGUTEFTHiggs_mAmu W, Z masses (via 1L matching)
   const double mW2_1L = Sqr(calculate_MW_DRbar_1loop(sm_0l, model_0l));
   const double mZ2_1L = Sqr(calculate_MZ_DRbar_1loop(sm_0l, model_0l));

   // running MSSMatMGUTEFTHiggs_mAmu quark and lepton masses (via 1L matching)
   const Eigen::Matrix<double, 3, 3> upQuarksDRbar    = calculate_MFu_DRbar_1loop(sm_0l, model_0l);
   const Eigen::Matrix<double, 3, 3> downQuarksDRbar  = calculate_MFd_DRbar_1loop(sm_0l, model_0l);
   const Eigen::Matrix<double, 3, 3> downLeptonsDRbar = calculate_MFe_DRbar_1loop(sm_0l, model_0l);

   // running MSSMatMGUTEFTHiggs_mAmu gauge couplings (via 1L matching)
   const double g1_1L = AbsSqrt(4. * Pi * alpha_em * (1. + delta_alpha_em) * mZ2_1L / mW2_1L) / MSSMatMGUTEFTHiggs_mAmu_info::normalization_g1;
   const double g2_1L = AbsSqrt(4. * Pi * alpha_em * (1. + delta_alpha_em) / (1. - mW2_1L/mZ2_1L)) / MSSMatMGUTEFTHiggs_mAmu_info::normalization_g2;
   const double g3_1L = AbsSqrt(4. * Pi * alpha_s * (1. + delta_alpha_s)) / MSSMatMGUTEFTHiggs_mAmu_info::normalization_g3;

   model.set_g1(g1_1L);
   model.set_g2(g2_1L);
   model.set_g3(g3_1L);

   {
      auto MODEL = &model;
      const double VEV = 2. * AbsSqrt(mZ2_1L/(Sqr(g1_1L*MSSMatMGUTEFTHiggs_mAmu_info::normalization_g1) + Sqr(g2_1L*MSSMatMGUTEFTHiggs_mAmu_info::normalization_g2)));

      const auto vd = MODELPARAMETER(vd);
      const auto vu = MODELPARAMETER(vu);

      MODEL->set_vu(Re((VEV*vu)/(vd*Sqrt(1 + Sqr(vu)/Sqr(vd)))));
      MODEL->set_vd(Re(VEV/Sqrt(1 + Sqr(vu)/Sqr(vd))));

   }

   const auto vu = MODELPARAMETER(vu);
   const auto vd = MODELPARAMETER(vd);
   model.set_Yu(((1.4142135623730951*upQuarksDRbar)/vu).transpose());
   model.set_Yd(((1.4142135623730951*downQuarksDRbar)/vd).transpose());
   model.set_Ye(((1.4142135623730951*downLeptonsDRbar)/vd).transpose());


   return model;
}

/**
 * Calculates the gauge and Yukawa couplings and the SM-like VEV in
 * the MSSMatMGUTEFTHiggs_mAmu at the necessary loop level from the known Standard
 * Model couplings and the SM vev.
 *
 * @param model MSSMatMGUTEFTHiggs_mAmu parameters (to be set)
 * @param sm SM parameters
 * @param idx Higgs index (in mass ordered Higgs multiplet)
 */
void match_low_to_high_scale_model_1loop(
   MSSMatMGUTEFTHiggs_mAmu_mass_eigenstates& model,
   const Standard_model& sm,
   int idx)
{
   // tree-level MSSMatMGUTEFTHiggs_mAmu parameters
   const auto model_0l = calculate_MSSMatMGUTEFTHiggs_mAmu_tree_level(model, sm);
   const auto sm_0l = calculate_SM_tree_level(sm, model_0l, idx);

   // 1-loop parameters
   const auto model_1l = calculate_MSSMatMGUTEFTHiggs_mAmu_1loop(sm_0l, sm, model_0l, model);

   model.set_g1(model_1l.get_g1());
   model.set_g2(model_1l.get_g2());
   model.set_g3(model_0l.get_g3());
   model.set_vd(model_1l.get_vd());
   model.set_vu(model_1l.get_vu());
   model.set_Yd(model_0l.get_Yd());
   model.set_Ye(model_0l.get_Ye());
   model.set_Yu(model_0l.get_Yu());

}

} // anonymous namespace

/**
 * Calculates \f$\lambda(Q)\f$ at the tree level from the lightest
 * CP-even Higgs boson mass of the MSSMatMGUTEFTHiggs_mAmu.
 *
 * @param sm Standard Model parameters
 * @param model MSSMatMGUTEFTHiggs_mAmu parameters
 * @param idx Higgs index (in mass ordered Higgs multiplet)
 */
void match_high_to_low_scale_model_tree_level(
   Standard_model& sm, const MSSMatMGUTEFTHiggs_mAmu_mass_eigenstates& model, int idx)
{
   auto model_tmp = model;
   model_tmp.calculate_DRbar_masses();
   sm.set_Lambdax(Sqr(model_tmp.get_Mhh(idx)/sm.get_v()));
   sm.calculate_DRbar_masses();
}

/**
 * Calculates the gauge and Yukawa couplings and the SM-like VEV in
 * the MSSMatMGUTEFTHiggs_mAmu at the tree level from the known Standard Model
 * couplings and the SM vev.
 */
void match_low_to_high_scale_model_tree_level(
   MSSMatMGUTEFTHiggs_mAmu_mass_eigenstates& model, const Standard_model& sm_input)
{
   auto sm = sm_input;
   sm.calculate_DRbar_masses();

   model.set_g1(sm.get_g1()*standard_model_info::normalization_g1/MSSMatMGUTEFTHiggs_mAmu_info::normalization_g1);
   model.set_g2(sm.get_g2()*standard_model_info::normalization_g2/MSSMatMGUTEFTHiggs_mAmu_info::normalization_g2);
   model.set_g3(sm.get_g3()*standard_model_info::normalization_g3/MSSMatMGUTEFTHiggs_mAmu_info::normalization_g3);

   {
      auto MODEL = &model;
      const double VEV = sm.get_v();

      const auto vd = MODELPARAMETER(vd);
      const auto vu = MODELPARAMETER(vu);

      MODEL->set_vu(Re((VEV*vu)/(vd*Sqrt(1 + Sqr(vu)/Sqr(vd)))));
      MODEL->set_vd(Re(VEV/Sqrt(1 + Sqr(vu)/Sqr(vd))));

   }

   Eigen::Matrix<double, 3, 3> upQuarksDRbar    = ZEROMATRIX(3,3);
   Eigen::Matrix<double, 3, 3> downQuarksDRbar  = ZEROMATRIX(3,3);
   Eigen::Matrix<double, 3, 3> downLeptonsDRbar = ZEROMATRIX(3,3);

   upQuarksDRbar.diagonal()    = sm.get_MFu();
   downQuarksDRbar.diagonal()  = sm.get_MFd();
   downLeptonsDRbar.diagonal() = sm.get_MFe();

   const auto vu = MODELPARAMETER(vu);
   const auto vd = MODELPARAMETER(vd);
   model.set_Yu(((1.4142135623730951*upQuarksDRbar)/vu).transpose());
   model.set_Yd(((1.4142135623730951*downQuarksDRbar)/vd).transpose());
   model.set_Ye(((1.4142135623730951*downLeptonsDRbar)/vd).transpose());


   model.calculate_DRbar_masses();
}

/**
 * Calculates the gauge and Yukawa couplings and the SM-like VEV in
 * the MSSMatMGUTEFTHiggs_mAmu at the 1-loop level from the known Standard Model
 * couplings and the SM vev.
 *
 * @note The \a loop_order argument is interpreted to be the loop
 * order of the "downwards matching".  The functions responsible for
 * the upwards matching will use the downwards matching loop order to
 * determine the MSSMatMGUTEFTHiggs_mAmu at the right loop order to avoid the
 * appearence of large logarithms.
 *
 * @param model MSSMatMGUTEFTHiggs_mAmu parameters
 * @param sm Standard Model
 * @param loop_order downwards matching loop order
 * @param idx Higgs index (in mass ordered Higgs multiplet)
 */
void match_low_to_high_scale_model(
   MSSMatMGUTEFTHiggs_mAmu_mass_eigenstates& model, const Standard_model& sm, int loop_order, int idx)
{
   if (loop_order == 0) {
      match_low_to_high_scale_model_tree_level(model, sm);
      return;
   }

   match_low_to_high_scale_model_1loop(model, sm, idx);
}

/**
 * Calculates \f$\lambda(Q)\f$ at the 1-loop level from the lightest
 * CP-even Higgs boson mass of the MSSMatMGUTEFTHiggs_mAmu by requiring that the
 * 1-loop Higgs pole masses are equal in both models.
 *
 * @param sm Standard Model
 * @param model MSSMatMGUTEFTHiggs_mAmu parameters
 * @param loop_order downwards matching loop order
 * @param idx Higgs index (in mass ordered Higgs multiplet)
 */
void match_high_to_low_scale_model(
   Standard_model& sm, const MSSMatMGUTEFTHiggs_mAmu_mass_eigenstates& model, int loop_order, int idx)
{
   if (loop_order == 0) {
      match_high_to_low_scale_model_tree_level(sm, model, idx);
      return;
   }

   match_high_to_low_scale_model_1loop(sm, model, idx);
}

} // namespace MSSMatMGUTEFTHiggs_mAmu_standard_model_matching
} // namespace flexiblesusy
