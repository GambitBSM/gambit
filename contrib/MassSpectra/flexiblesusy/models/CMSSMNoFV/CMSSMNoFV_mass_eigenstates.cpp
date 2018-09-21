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

// File generated at Thu 10 May 2018 14:55:59

/**
 * @file CMSSMNoFV_mass_eigenstates.cpp
 * @brief implementation of the CMSSMNoFV model class
 *
 * Contains the definition of the CMSSMNoFV model class methods
 * which solve EWSB and calculate pole masses and mixings from DRbar
 * parameters.
 *
 * This file was generated at Thu 10 May 2018 14:55:59 with FlexibleSUSY
 * 2.0.1 (git commit: unknown) and SARAH 4.12.2 .
 */

#include "CMSSMNoFV_mass_eigenstates.hpp"
#include "CMSSMNoFV_ewsb_solver_interface.hpp"
#include "eigen_utils.hpp"
#include "ewsb_solver.hpp"
#include "wrappers.hpp"
#include "linalg2.hpp"
#include "numerics2.hpp"
#include "logger.hpp"
#include "error.hpp"
#include "pv.hpp"
#include "raii.hpp"
#include "thread_pool.hpp"
#include "functors.hpp"

#include "config.h"

#ifdef ENABLE_TWO_SCALE_SOLVER
#include "CMSSMNoFV_two_scale_ewsb_solver.hpp"
#endif

#include "sfermions.hpp"
#include "mssm_twoloophiggs.hpp"




#include <array>
#include <cmath>
#include <functional>
#include <iostream>
#include <memory>
#include <algorithm>
#include <stdexcept>

namespace flexiblesusy {

#define CLASSNAME CMSSMNoFV_mass_eigenstates

#define PHYSICAL(parameter) physical.parameter
#define INPUT(parameter) model.get_input().parameter
#define LOCALINPUT(parameter) input.parameter
#define MODELPARAMETER(parameter) model.get_##parameter()
#define EXTRAPARAMETER(parameter) model.get_##parameter()

#define HIGGS_2LOOP_CORRECTION_AT_AS     loop_corrections.higgs_at_as
#define HIGGS_2LOOP_CORRECTION_AB_AS     loop_corrections.higgs_ab_as
#define HIGGS_2LOOP_CORRECTION_AT_AT     loop_corrections.higgs_at_at
#define HIGGS_2LOOP_CORRECTION_ATAU_ATAU loop_corrections.higgs_atau_atau
#define TOP_POLE_QCD_CORRECTION          loop_corrections.top_qcd
#define HIGGS_3LOOP_CORRECTION_AT_AS_AS  loop_corrections.higgs_at_as_as
#define HIGGS_3LOOP_CORRECTION_AB_AS_AS  loop_corrections.higgs_ab_as_as
#define HIGGS_3LOOP_MDR_SCHEME           loop_corrections.higgs_3L_mdr_scheme
#define HIGGS_3LOOP_CORRECTION_AT_AT_AS  loop_corrections.higgs_at_at_as
#define HIGGS_3LOOP_CORRECTION_AT_AT_AT  loop_corrections.higgs_at_at_at

CLASSNAME::CMSSMNoFV_mass_eigenstates(const CMSSMNoFV_input_parameters& input_)
   : CMSSMNoFV_soft_parameters(input_)
#if defined(ENABLE_TWO_SCALE_SOLVER)
   , ewsb_solver(new CMSSMNoFV_ewsb_solver<Two_scale>())
#endif
{
}

void CLASSNAME::do_calculate_sm_pole_masses(bool flag)
{
   calculate_sm_pole_masses = flag;
}

bool CLASSNAME::do_calculate_sm_pole_masses() const
{
   return calculate_sm_pole_masses;
}

void CLASSNAME::do_calculate_bsm_pole_masses(bool flag)
{
   calculate_bsm_pole_masses = flag;
}

bool CLASSNAME::do_calculate_bsm_pole_masses() const
{
   return calculate_bsm_pole_masses;
}

void CLASSNAME::do_force_output(bool flag)
{
   force_output = flag;
}

bool CLASSNAME::do_force_output() const
{
   return force_output;
}

void CLASSNAME::set_ewsb_loop_order(int loop_order)
{
   ewsb_loop_order = loop_order;
   if (ewsb_solver) {
      ewsb_solver->set_loop_order(ewsb_loop_order);
   }
}

void CLASSNAME::set_loop_corrections(const Loop_corrections& loop_corrections_)
{
   loop_corrections = loop_corrections_;
}

const Loop_corrections& CLASSNAME::get_loop_corrections() const
{
   return loop_corrections;
}

void CLASSNAME::set_threshold_corrections(const Threshold_corrections& tc)
{
   threshold_corrections = tc;
}

const Threshold_corrections& CLASSNAME::get_threshold_corrections() const
{
   return threshold_corrections;
}

int CLASSNAME::get_number_of_ewsb_iterations() const
{
   return static_cast<int>(std::abs(-log10(ewsb_iteration_precision) * 10));
}

int CLASSNAME::get_number_of_mass_iterations() const
{
   return static_cast<int>(std::abs(-log10(precision) * 10));
}

void CLASSNAME::set_precision(double precision_)
{
   precision = precision_;
   ewsb_iteration_precision = precision_;
   if (ewsb_solver) {
      ewsb_solver->set_precision(precision_);
   }
}

void CLASSNAME::set_pole_mass_loop_order(int loop_order)
{
   pole_mass_loop_order = loop_order;
}

int CLASSNAME::get_pole_mass_loop_order() const
{
   return pole_mass_loop_order;
}

void CLASSNAME::set_ewsb_iteration_precision(double precision)
{
   ewsb_iteration_precision = precision;
   if (ewsb_solver) {
      ewsb_solver->set_precision(precision);
   }
}

double CLASSNAME::get_ewsb_iteration_precision() const
{
   return ewsb_iteration_precision;
}

double CLASSNAME::get_precision() const
{
   return precision;
}

double CLASSNAME::get_ewsb_loop_order() const
{
   return ewsb_loop_order;
}

const CMSSMNoFV_physical& CLASSNAME::get_physical() const
{
   return physical;
}

CMSSMNoFV_physical& CLASSNAME::get_physical()
{
   return physical;
}

void CLASSNAME::set_physical(const CMSSMNoFV_physical& physical_)
{
   physical = physical_;
}

const Problems& CLASSNAME::get_problems() const
{
   return problems;
}

Problems& CLASSNAME::get_problems()
{
   return problems;
}

void CLASSNAME::set_ewsb_solver(const std::shared_ptr<CMSSMNoFV_ewsb_solver_interface>& solver)
{
   ewsb_solver = solver;
}

/**
 * Method which calculates the tadpoles at the current loop order.
 *
 * @param tadpole array of tadpole
 */
void CLASSNAME::tadpole_equations(double tadpole[number_of_ewsb_equations]) const
{
   const auto tadpole_(tadpole_equations());
   std::copy(tadpole_.data(), tadpole_.data() + number_of_ewsb_equations, tadpole);
}

/**
 * Method which calculates the tadpoles at the current loop order.
 *
 * @return array of tadpoles
 */
Eigen::Matrix<double,CLASSNAME::number_of_ewsb_equations,1> CLASSNAME::tadpole_equations() const
{
   Eigen::Matrix<double,number_of_ewsb_equations,1> tadpole(
      Eigen::Matrix<double,number_of_ewsb_equations,1>::Zero());

   tadpole[0] = get_ewsb_eq_hh_1();
   tadpole[1] = get_ewsb_eq_hh_2();

   if (ewsb_loop_order > 0) {
      tadpole[0] -= Re(tadpole_hh_1loop(0));
      tadpole[1] -= Re(tadpole_hh_1loop(1));

      if (ewsb_loop_order > 1) {
         const auto tadpole_2l(tadpole_hh_2loop());
         tadpole[0] -= tadpole_2l(0);
         tadpole[1] -= tadpole_2l(1);

      }
   }

   return tadpole;
}

/**
 * This function returns the vector of tadpoles, each divided by the
 * corresponding VEV.  Thus, the returned tadpoles have the dimension
 * GeV^2 each.
 *
 * @return vector of tadpoles
 */
Eigen::Matrix<double,CLASSNAME::number_of_ewsb_equations,1> CLASSNAME::tadpole_equations_over_vevs() const
{
   auto tadpole = tadpole_equations();

   tadpole[0] /= vd;
   tadpole[1] /= vu;


   return tadpole;
}

int CLASSNAME::solve_ewsb_tree_level_custom()
{
   int error = EWSB_solver::SUCCESS;

   const double old_mHd2 = mHd2;
   const double old_mHu2 = mHu2;

   mHd2 = Re((0.025*(-40*vd*AbsSqr(Mu) + 20*vu*BMu + 20*vu*Conj(BMu) - 3*Cube(
      vd)*Sqr(g1) - 5*Cube(vd)*Sqr(g2) + 3*vd*Sqr(g1)*Sqr(vu) + 5*vd*Sqr(g2)*Sqr(
      vu)))/vd);
   mHu2 = Re((0.025*(-40*vu*AbsSqr(Mu) + 20*vd*BMu + 20*vd*Conj(BMu) - 3*Cube(
      vu)*Sqr(g1) - 5*Cube(vu)*Sqr(g2) + 3*vu*Sqr(g1)*Sqr(vd) + 5*vu*Sqr(g2)*Sqr(
      vd)))/vu);

   const bool is_finite = IsFinite(mHd2) && IsFinite(mHu2);

   if (!is_finite) {
      mHd2 = old_mHd2;
      mHu2 = old_mHu2;
      error = EWSB_solver::FAIL;
   }


   return error;
}

int CLASSNAME::solve_ewsb_tree_level()
{
   if (!ewsb_solver) {
      throw SetupError("CMSSMNoFV_mass_eigenstates::solve_ewsb_tree_level: "
                       "no EWSB solver set");
   }

   const int old_loop_order = ewsb_solver->get_loop_order();
   const auto save_loop_order = make_raii_guard(
      [this, old_loop_order] () {
         this->ewsb_solver->set_loop_order(old_loop_order);
      });

   const int old_iterations = ewsb_solver->get_number_of_iterations();
   const auto save_iterations = make_raii_guard(
      [this, old_iterations] () {
         this->ewsb_solver->set_number_of_iterations(old_iterations);
      });

   const double old_precision = ewsb_solver->get_precision();
   const auto save_precision = make_raii_guard(
      [this, old_precision] () {
         this->ewsb_solver->set_precision(old_precision);
      });

   ewsb_solver->set_loop_order(0);
   ewsb_solver->set_number_of_iterations(get_number_of_ewsb_iterations());
   ewsb_solver->set_precision(ewsb_iteration_precision);

   return ewsb_solver->solve(*this);
}

int CLASSNAME::solve_ewsb_one_loop()
{
   if (!ewsb_solver) {
      throw SetupError("CMSSMNoFV_mass_eigenstates::solve_ewsb_one_loop: "
                       "no EWSB solver set");
   }

   const int old_loop_order = ewsb_solver->get_loop_order();
   const auto save_loop_order = make_raii_guard(
      [this, old_loop_order] () {
         this->ewsb_solver->set_loop_order(old_loop_order);
      });

   const int old_iterations = ewsb_solver->get_number_of_iterations();
   const auto save_iterations = make_raii_guard(
      [this, old_iterations] () {
         this->ewsb_solver->set_number_of_iterations(old_iterations);
      });

   const double old_precision = ewsb_solver->get_precision();
   const auto save_precision = make_raii_guard(
      [this, old_precision] () {
         this->ewsb_solver->set_precision(old_precision);
      });

   ewsb_solver->set_loop_order(1);
   ewsb_solver->set_number_of_iterations(get_number_of_ewsb_iterations());
   ewsb_solver->set_precision(ewsb_iteration_precision);

   return ewsb_solver->solve(*this);
}

int CLASSNAME::solve_ewsb()
{
   if (!ewsb_solver) {
      throw SetupError("CMSSMNoFV_mass_eigenstates::solve_ewsb: "
                       "no EWSB solver set");
   }

   VERBOSE_MSG("\t\tSolving CMSSMNoFV EWSB at " << ewsb_loop_order << "-loop order");

   const int old_loop_order = ewsb_solver->get_loop_order();
   const auto save_loop_order = make_raii_guard(
      [this, old_loop_order] () {
         this->ewsb_solver->set_loop_order(old_loop_order);
      });

   const int old_iterations = ewsb_solver->get_number_of_iterations();
   const auto save_iterations = make_raii_guard(
      [this, old_iterations] () {
         this->ewsb_solver->set_number_of_iterations(old_iterations);
      });

   const double old_precision = ewsb_solver->get_precision();
   const auto save_precision = make_raii_guard(
      [this, old_precision] () {
         this->ewsb_solver->set_precision(old_precision);
      });

   ewsb_solver->set_loop_order(ewsb_loop_order);
   ewsb_solver->set_number_of_iterations(get_number_of_ewsb_iterations());
   ewsb_solver->set_precision(ewsb_iteration_precision);

   return ewsb_solver->solve(*this);
}

void CLASSNAME::print(std::ostream& ostr) const
{
   ostr << "========================================\n"
           "CMSSMNoFV\n"
           "========================================\n";
   CMSSMNoFV_soft_parameters::print(ostr);
   ostr << "----------------------------------------\n"
           "tree-level DRbar masses:\n"
           "----------------------------------------\n";
   ostr << "MVG = " << MVG << '\n';
   ostr << "MGlu = " << MGlu << '\n';
   ostr << "MFd = " << MFd << '\n';
   ostr << "MFs = " << MFs << '\n';
   ostr << "MFb = " << MFb << '\n';
   ostr << "MFu = " << MFu << '\n';
   ostr << "MFc = " << MFc << '\n';
   ostr << "MFt = " << MFt << '\n';
   ostr << "MFve = " << MFve << '\n';
   ostr << "MFvm = " << MFvm << '\n';
   ostr << "MFvt = " << MFvt << '\n';
   ostr << "MFe = " << MFe << '\n';
   ostr << "MFm = " << MFm << '\n';
   ostr << "MFtau = " << MFtau << '\n';
   ostr << "MSveL = " << MSveL << '\n';
   ostr << "MSvmL = " << MSvmL << '\n';
   ostr << "MSvtL = " << MSvtL << '\n';
   ostr << "MSd = " << MSd.transpose() << '\n';
   ostr << "MSu = " << MSu.transpose() << '\n';
   ostr << "MSe = " << MSe.transpose() << '\n';
   ostr << "MSm = " << MSm.transpose() << '\n';
   ostr << "MStau = " << MStau.transpose() << '\n';
   ostr << "MSs = " << MSs.transpose() << '\n';
   ostr << "MSc = " << MSc.transpose() << '\n';
   ostr << "MSb = " << MSb.transpose() << '\n';
   ostr << "MSt = " << MSt.transpose() << '\n';
   ostr << "Mhh = " << Mhh.transpose() << '\n';
   ostr << "MAh = " << MAh.transpose() << '\n';
   ostr << "MHpm = " << MHpm.transpose() << '\n';
   ostr << "MChi = " << MChi.transpose() << '\n';
   ostr << "MCha = " << MCha.transpose() << '\n';
   ostr << "MVWm = " << MVWm << '\n';
   ostr << "MVP = " << MVP << '\n';
   ostr << "MVZ = " << MVZ << '\n';

   ostr << "----------------------------------------\n"
           "tree-level DRbar mixing matrices:\n"
           "----------------------------------------\n";
   ostr << "ZD = " << ZD << '\n';
   ostr << "ZU = " << ZU << '\n';
   ostr << "ZE = " << ZE << '\n';
   ostr << "ZM = " << ZM << '\n';
   ostr << "ZTau = " << ZTau << '\n';
   ostr << "ZS = " << ZS << '\n';
   ostr << "ZC = " << ZC << '\n';
   ostr << "ZB = " << ZB << '\n';
   ostr << "ZT = " << ZT << '\n';
   ostr << "ZH = " << ZH << '\n';
   ostr << "ZA = " << ZA << '\n';
   ostr << "ZP = " << ZP << '\n';
   ostr << "ZN = " << ZN << '\n';
   ostr << "UM = " << UM << '\n';
   ostr << "UP = " << UP << '\n';
   ostr << "ZZ = " << ZZ << '\n';

   physical.print(ostr);
}

/**
 * wrapper routines for passarino Veltman functions
 * @note: They take squared arguments!
 */

double CLASSNAME::A0(double m) const noexcept
{
   return passarino_veltman::ReA0(m, Sqr(get_scale()));
}

double CLASSNAME::B0(double p, double m1, double m2) const noexcept
{
   return passarino_veltman::ReB0(p, m1, m2, Sqr(get_scale()));
}

double CLASSNAME::B1(double p, double m1, double m2) const noexcept
{
   return passarino_veltman::ReB1(p, m1, m2, Sqr(get_scale()));
}

double CLASSNAME::B00(double p, double m1, double m2) const noexcept
{
   return passarino_veltman::ReB00(p, m1, m2, Sqr(get_scale()));
}

double CLASSNAME::B22(double p, double m1, double m2) const noexcept
{
   return passarino_veltman::ReB22(p, m1, m2, Sqr(get_scale()));
}

double CLASSNAME::H0(double p, double m1, double m2) const noexcept
{
   return passarino_veltman::ReH0(p, m1, m2, Sqr(get_scale()));
}

double CLASSNAME::F0(double p, double m1, double m2) const noexcept
{
   return passarino_veltman::ReF0(p, m1, m2, Sqr(get_scale()));
}

double CLASSNAME::G0(double p, double m1, double m2) const noexcept
{
   return passarino_veltman::ReG0(p, m1, m2, Sqr(get_scale()));
}

/**
 * routine which finds the DRbar mass eigenstates and mixings.
 */
void CLASSNAME::calculate_DRbar_masses()
{
   const auto save_mHd2_raii = make_raii_save(mHd2);
   const auto save_mHu2_raii = make_raii_save(mHu2);

   solve_ewsb_tree_level_custom();

   calculate_MVPVZ();
   calculate_MVWm();
   calculate_MCha();
   calculate_MChi();
   calculate_MHpm();
   calculate_MAh();
   calculate_Mhh();
   calculate_MSt();
   calculate_MSb();
   calculate_MSc();
   calculate_MSs();
   calculate_MStau();
   calculate_MSm();
   calculate_MSe();
   calculate_MSu();
   calculate_MSd();
   calculate_MSvtL();
   calculate_MSvmL();
   calculate_MSveL();
   calculate_MFtau();
   calculate_MFm();
   calculate_MFe();
   calculate_MFvt();
   calculate_MFvm();
   calculate_MFve();
   calculate_MFt();
   calculate_MFc();
   calculate_MFu();
   calculate_MFb();
   calculate_MFs();
   calculate_MFd();
   calculate_MGlu();
   calculate_MVG();

}

/**
 * routine which finds the pole mass eigenstates and mixings.
 */
void CLASSNAME::calculate_pole_masses()
{
#ifdef ENABLE_THREADS
   Thread_pool tp(std::min(std::thread::hardware_concurrency(), 34u));

   if (calculate_bsm_pole_masses) {
      tp.run_task([this] () { calculate_MAh_pole(); });
      tp.run_task([this] () { calculate_MCha_pole(); });
      tp.run_task([this] () { calculate_MChi_pole(); });
      tp.run_task([this] () { calculate_MGlu_pole(); });
      tp.run_task([this] () { calculate_Mhh_pole(); });
      tp.run_task([this] () { calculate_MHpm_pole(); });
      tp.run_task([this] () { calculate_MSb_pole(); });
      tp.run_task([this] () { calculate_MSc_pole(); });
      tp.run_task([this] () { calculate_MSd_pole(); });
      tp.run_task([this] () { calculate_MSe_pole(); });
      tp.run_task([this] () { calculate_MSm_pole(); });
      tp.run_task([this] () { calculate_MSs_pole(); });
      tp.run_task([this] () { calculate_MSt_pole(); });
      tp.run_task([this] () { calculate_MStau_pole(); });
      tp.run_task([this] () { calculate_MSu_pole(); });
      tp.run_task([this] () { calculate_MSveL_pole(); });
      tp.run_task([this] () { calculate_MSvmL_pole(); });
      tp.run_task([this] () { calculate_MSvtL_pole(); });
   }

   if (calculate_sm_pole_masses) {
      tp.run_task([this] () { calculate_MVG_pole(); });
      tp.run_task([this] () { calculate_MVP_pole(); });
      tp.run_task([this] () { calculate_MVZ_pole(); });
      tp.run_task([this] () { calculate_MFd_pole(); });
      tp.run_task([this] () { calculate_MFs_pole(); });
      tp.run_task([this] () { calculate_MFb_pole(); });
      tp.run_task([this] () { calculate_MFu_pole(); });
      tp.run_task([this] () { calculate_MFc_pole(); });
      tp.run_task([this] () { calculate_MFt_pole(); });
      tp.run_task([this] () { calculate_MFve_pole(); });
      tp.run_task([this] () { calculate_MFvm_pole(); });
      tp.run_task([this] () { calculate_MFvt_pole(); });
      tp.run_task([this] () { calculate_MFe_pole(); });
      tp.run_task([this] () { calculate_MFm_pole(); });
      tp.run_task([this] () { calculate_MFtau_pole(); });
      tp.run_task([this] () { calculate_MVWm_pole(); });
   }

#else
   if (calculate_bsm_pole_masses) {
      calculate_MAh_pole();
      calculate_MCha_pole();
      calculate_MChi_pole();
      calculate_MGlu_pole();
      calculate_Mhh_pole();
      calculate_MHpm_pole();
      calculate_MSb_pole();
      calculate_MSc_pole();
      calculate_MSd_pole();
      calculate_MSe_pole();
      calculate_MSm_pole();
      calculate_MSs_pole();
      calculate_MSt_pole();
      calculate_MStau_pole();
      calculate_MSu_pole();
      calculate_MSveL_pole();
      calculate_MSvmL_pole();
      calculate_MSvtL_pole();
   }

   if (calculate_sm_pole_masses) {
      calculate_MVG_pole();
      calculate_MVP_pole();
      calculate_MVZ_pole();
      calculate_MFd_pole();
      calculate_MFs_pole();
      calculate_MFb_pole();
      calculate_MFu_pole();
      calculate_MFc_pole();
      calculate_MFt_pole();
      calculate_MFve_pole();
      calculate_MFvm_pole();
      calculate_MFvt_pole();
      calculate_MFe_pole();
      calculate_MFm_pole();
      calculate_MFtau_pole();
      calculate_MVWm_pole();
   }

#endif
}

void CLASSNAME::copy_DRbar_masses_to_pole_masses()
{
   PHYSICAL(MVG) = MVG;
   PHYSICAL(MGlu) = MGlu;
   PHYSICAL(MFd) = MFd;
   PHYSICAL(MFs) = MFs;
   PHYSICAL(MFb) = MFb;
   PHYSICAL(MFu) = MFu;
   PHYSICAL(MFc) = MFc;
   PHYSICAL(MFt) = MFt;
   PHYSICAL(MFve) = MFve;
   PHYSICAL(MFvm) = MFvm;
   PHYSICAL(MFvt) = MFvt;
   PHYSICAL(MFe) = MFe;
   PHYSICAL(MFm) = MFm;
   PHYSICAL(MFtau) = MFtau;
   PHYSICAL(MSveL) = MSveL;
   PHYSICAL(MSvmL) = MSvmL;
   PHYSICAL(MSvtL) = MSvtL;
   PHYSICAL(MSd) = MSd;
   PHYSICAL(ZD) = ZD;
   PHYSICAL(MSu) = MSu;
   PHYSICAL(ZU) = ZU;
   PHYSICAL(MSe) = MSe;
   PHYSICAL(ZE) = ZE;
   PHYSICAL(MSm) = MSm;
   PHYSICAL(ZM) = ZM;
   PHYSICAL(MStau) = MStau;
   PHYSICAL(ZTau) = ZTau;
   PHYSICAL(MSs) = MSs;
   PHYSICAL(ZS) = ZS;
   PHYSICAL(MSc) = MSc;
   PHYSICAL(ZC) = ZC;
   PHYSICAL(MSb) = MSb;
   PHYSICAL(ZB) = ZB;
   PHYSICAL(MSt) = MSt;
   PHYSICAL(ZT) = ZT;
   PHYSICAL(Mhh) = Mhh;
   PHYSICAL(ZH) = ZH;
   PHYSICAL(MAh) = MAh;
   PHYSICAL(ZA) = ZA;
   PHYSICAL(MHpm) = MHpm;
   PHYSICAL(ZP) = ZP;
   PHYSICAL(MChi) = MChi;
   PHYSICAL(ZN) = ZN;
   PHYSICAL(MCha) = MCha;
   PHYSICAL(UM) = UM;
   PHYSICAL(UP) = UP;
   PHYSICAL(MVWm) = MVWm;
   PHYSICAL(MVP) = MVP;
   PHYSICAL(MVZ) = MVZ;

}

/**
 * reorders DRbar masses so that golstones are placed at the index
 * specified in the model files definition of the associated
 * gauge boson (see Z-boson definition in default particles.m file
 * in the Models directory of your SARAH distribution for example)
 */
void CLASSNAME::reorder_DRbar_masses()
{
   move_goldstone_to(0, MVZ, MAh, ZA);
   move_goldstone_to(0, MVWm, MHpm, ZP);

}

/**
 * reorders pole masses so that golstones are placed at the index
 * specified in the model files definition of the associated
 * gauge boson (see Z-boson definition in default particles.m file
 * in the Models directory of your SARAH distribution for example)
 */
void CLASSNAME::reorder_pole_masses()
{
   move_goldstone_to(0, MVZ, PHYSICAL(MAh), PHYSICAL(ZA));
   move_goldstone_to(0, MVWm, PHYSICAL(MHpm), PHYSICAL(ZP));

}

/**
 * Checks the pole masses for tachyons
 */
void CLASSNAME::check_pole_masses_for_tachyons()
{
   if (PHYSICAL(MSveL) < 0.) problems.flag_pole_tachyon(CMSSMNoFV_info::SveL);
   if (PHYSICAL(MSvmL) < 0.) problems.flag_pole_tachyon(CMSSMNoFV_info::SvmL);
   if (PHYSICAL(MSvtL) < 0.) problems.flag_pole_tachyon(CMSSMNoFV_info::SvtL);
   if (PHYSICAL(MSd).tail<2>().minCoeff() < 0.) problems.flag_pole_tachyon(CMSSMNoFV_info::Sd);
   if (PHYSICAL(MSu).tail<2>().minCoeff() < 0.) problems.flag_pole_tachyon(CMSSMNoFV_info::Su);
   if (PHYSICAL(MSe).tail<2>().minCoeff() < 0.) problems.flag_pole_tachyon(CMSSMNoFV_info::Se);
   if (PHYSICAL(MSm).tail<2>().minCoeff() < 0.) problems.flag_pole_tachyon(CMSSMNoFV_info::Sm);
   if (PHYSICAL(MStau).tail<2>().minCoeff() < 0.) problems.flag_pole_tachyon(CMSSMNoFV_info::Stau);
   if (PHYSICAL(MSs).tail<2>().minCoeff() < 0.) problems.flag_pole_tachyon(CMSSMNoFV_info::Ss);
   if (PHYSICAL(MSc).tail<2>().minCoeff() < 0.) problems.flag_pole_tachyon(CMSSMNoFV_info::Sc);
   if (PHYSICAL(MSb).tail<2>().minCoeff() < 0.) problems.flag_pole_tachyon(CMSSMNoFV_info::Sb);
   if (PHYSICAL(MSt).tail<2>().minCoeff() < 0.) problems.flag_pole_tachyon(CMSSMNoFV_info::St);
   if (PHYSICAL(Mhh).tail<2>().minCoeff() < 0.) problems.flag_pole_tachyon(CMSSMNoFV_info::hh);
   if (PHYSICAL(MAh).tail<1>().minCoeff() < 0.) problems.flag_pole_tachyon(CMSSMNoFV_info::Ah);
   if (PHYSICAL(MHpm).tail<1>().minCoeff() < 0.) problems.flag_pole_tachyon(CMSSMNoFV_info::Hpm);

}

/**
 * calculates spectrum for model once the DRbar parameters at
 * at low energies are known
 */
void CLASSNAME::calculate_spectrum()
{
   calculate_DRbar_masses();
   if (pole_mass_loop_order > 0)
      calculate_pole_masses();

   // move goldstone bosons to the front
   reorder_DRbar_masses();
   if (pole_mass_loop_order == 0)
      copy_DRbar_masses_to_pole_masses();
   else
      reorder_pole_masses();

   check_pole_masses_for_tachyons();

   if (problems.have_problem() && !force_output) {
      clear_DRbar_parameters();
      physical.clear();
   }
}

void CLASSNAME::clear_DRbar_parameters()
{
   MVG = 0.;
   MGlu = 0.;
   MFd = 0.;
   MFs = 0.;
   MFb = 0.;
   MFu = 0.;
   MFc = 0.;
   MFt = 0.;
   MFve = 0.;
   MFvm = 0.;
   MFvt = 0.;
   MFe = 0.;
   MFm = 0.;
   MFtau = 0.;
   MSveL = 0.;
   MSvmL = 0.;
   MSvtL = 0.;
   MSd = Eigen::Matrix<double,2,1>::Zero();
   ZD = Eigen::Matrix<double,2,2>::Zero();
   MSu = Eigen::Matrix<double,2,1>::Zero();
   ZU = Eigen::Matrix<double,2,2>::Zero();
   MSe = Eigen::Matrix<double,2,1>::Zero();
   ZE = Eigen::Matrix<double,2,2>::Zero();
   MSm = Eigen::Matrix<double,2,1>::Zero();
   ZM = Eigen::Matrix<double,2,2>::Zero();
   MStau = Eigen::Matrix<double,2,1>::Zero();
   ZTau = Eigen::Matrix<double,2,2>::Zero();
   MSs = Eigen::Matrix<double,2,1>::Zero();
   ZS = Eigen::Matrix<double,2,2>::Zero();
   MSc = Eigen::Matrix<double,2,1>::Zero();
   ZC = Eigen::Matrix<double,2,2>::Zero();
   MSb = Eigen::Matrix<double,2,1>::Zero();
   ZB = Eigen::Matrix<double,2,2>::Zero();
   MSt = Eigen::Matrix<double,2,1>::Zero();
   ZT = Eigen::Matrix<double,2,2>::Zero();
   Mhh = Eigen::Matrix<double,2,1>::Zero();
   ZH = Eigen::Matrix<double,2,2>::Zero();
   MAh = Eigen::Matrix<double,2,1>::Zero();
   ZA = Eigen::Matrix<double,2,2>::Zero();
   MHpm = Eigen::Matrix<double,2,1>::Zero();
   ZP = Eigen::Matrix<double,2,2>::Zero();
   MChi = Eigen::Matrix<double,4,1>::Zero();
   ZN = Eigen::Matrix<std::complex<double>,4,4>::Zero();
   MCha = Eigen::Matrix<double,2,1>::Zero();
   UM = Eigen::Matrix<std::complex<double>,2,2>::Zero();
   UP = Eigen::Matrix<std::complex<double>,2,2>::Zero();
   MVWm = 0.;
   MVP = 0.;
   MVZ = 0.;

   PhaseGlu = std::complex<double>(1.,0.);


}

void CLASSNAME::clear_problems()
{
   problems.clear();
}

void CLASSNAME::clear()
{
   CMSSMNoFV_soft_parameters::clear();
   clear_DRbar_parameters();
   physical.clear();
   problems.clear();
}

void CLASSNAME::set_DRbar_masses(const Eigen::ArrayXd& pars)
{
   MVG = pars(0);
   MGlu = pars(1);
   MFd = pars(2);
   MFs = pars(3);
   MFb = pars(4);
   MFu = pars(5);
   MFc = pars(6);
   MFt = pars(7);
   MFve = pars(8);
   MFvm = pars(9);
   MFvt = pars(10);
   MFe = pars(11);
   MFm = pars(12);
   MFtau = pars(13);
   MSveL = pars(14);
   MSvmL = pars(15);
   MSvtL = pars(16);
   MSd(0) = pars(17);
   MSd(1) = pars(18);
   MSu(0) = pars(19);
   MSu(1) = pars(20);
   MSe(0) = pars(21);
   MSe(1) = pars(22);
   MSm(0) = pars(23);
   MSm(1) = pars(24);
   MStau(0) = pars(25);
   MStau(1) = pars(26);
   MSs(0) = pars(27);
   MSs(1) = pars(28);
   MSc(0) = pars(29);
   MSc(1) = pars(30);
   MSb(0) = pars(31);
   MSb(1) = pars(32);
   MSt(0) = pars(33);
   MSt(1) = pars(34);
   Mhh(0) = pars(35);
   Mhh(1) = pars(36);
   MAh(0) = pars(37);
   MAh(1) = pars(38);
   MHpm(0) = pars(39);
   MHpm(1) = pars(40);
   MChi(0) = pars(41);
   MChi(1) = pars(42);
   MChi(2) = pars(43);
   MChi(3) = pars(44);
   MCha(0) = pars(45);
   MCha(1) = pars(46);
   MVWm = pars(47);
   MVP = pars(48);
   MVZ = pars(49);

}

Eigen::ArrayXd CLASSNAME::get_DRbar_masses() const
{
   Eigen::ArrayXd pars(50);

   pars(0) = MVG;
   pars(1) = MGlu;
   pars(2) = MFd;
   pars(3) = MFs;
   pars(4) = MFb;
   pars(5) = MFu;
   pars(6) = MFc;
   pars(7) = MFt;
   pars(8) = MFve;
   pars(9) = MFvm;
   pars(10) = MFvt;
   pars(11) = MFe;
   pars(12) = MFm;
   pars(13) = MFtau;
   pars(14) = MSveL;
   pars(15) = MSvmL;
   pars(16) = MSvtL;
   pars(17) = MSd(0);
   pars(18) = MSd(1);
   pars(19) = MSu(0);
   pars(20) = MSu(1);
   pars(21) = MSe(0);
   pars(22) = MSe(1);
   pars(23) = MSm(0);
   pars(24) = MSm(1);
   pars(25) = MStau(0);
   pars(26) = MStau(1);
   pars(27) = MSs(0);
   pars(28) = MSs(1);
   pars(29) = MSc(0);
   pars(30) = MSc(1);
   pars(31) = MSb(0);
   pars(32) = MSb(1);
   pars(33) = MSt(0);
   pars(34) = MSt(1);
   pars(35) = Mhh(0);
   pars(36) = Mhh(1);
   pars(37) = MAh(0);
   pars(38) = MAh(1);
   pars(39) = MHpm(0);
   pars(40) = MHpm(1);
   pars(41) = MChi(0);
   pars(42) = MChi(1);
   pars(43) = MChi(2);
   pars(44) = MChi(3);
   pars(45) = MCha(0);
   pars(46) = MCha(1);
   pars(47) = MVWm;
   pars(48) = MVP;
   pars(49) = MVZ;

   return pars;
}

void CLASSNAME::set_DRbar_masses_and_mixings(const Eigen::ArrayXd& pars)
{
   set_DRbar_masses(pars);

   ZD(0,0) = pars(50);
   ZD(0,1) = pars(51);
   ZD(1,0) = pars(52);
   ZD(1,1) = pars(53);
   ZU(0,0) = pars(54);
   ZU(0,1) = pars(55);
   ZU(1,0) = pars(56);
   ZU(1,1) = pars(57);
   ZE(0,0) = pars(58);
   ZE(0,1) = pars(59);
   ZE(1,0) = pars(60);
   ZE(1,1) = pars(61);
   ZM(0,0) = pars(62);
   ZM(0,1) = pars(63);
   ZM(1,0) = pars(64);
   ZM(1,1) = pars(65);
   ZTau(0,0) = pars(66);
   ZTau(0,1) = pars(67);
   ZTau(1,0) = pars(68);
   ZTau(1,1) = pars(69);
   ZS(0,0) = pars(70);
   ZS(0,1) = pars(71);
   ZS(1,0) = pars(72);
   ZS(1,1) = pars(73);
   ZC(0,0) = pars(74);
   ZC(0,1) = pars(75);
   ZC(1,0) = pars(76);
   ZC(1,1) = pars(77);
   ZB(0,0) = pars(78);
   ZB(0,1) = pars(79);
   ZB(1,0) = pars(80);
   ZB(1,1) = pars(81);
   ZT(0,0) = pars(82);
   ZT(0,1) = pars(83);
   ZT(1,0) = pars(84);
   ZT(1,1) = pars(85);
   ZH(0,0) = pars(86);
   ZH(0,1) = pars(87);
   ZH(1,0) = pars(88);
   ZH(1,1) = pars(89);
   ZA(0,0) = pars(90);
   ZA(0,1) = pars(91);
   ZA(1,0) = pars(92);
   ZA(1,1) = pars(93);
   ZP(0,0) = pars(94);
   ZP(0,1) = pars(95);
   ZP(1,0) = pars(96);
   ZP(1,1) = pars(97);
   ZN(0,0) = std::complex<double>(pars(98), pars(99));
   ZN(0,1) = std::complex<double>(pars(100), pars(101));
   ZN(0,2) = std::complex<double>(pars(102), pars(103));
   ZN(0,3) = std::complex<double>(pars(104), pars(105));
   ZN(1,0) = std::complex<double>(pars(106), pars(107));
   ZN(1,1) = std::complex<double>(pars(108), pars(109));
   ZN(1,2) = std::complex<double>(pars(110), pars(111));
   ZN(1,3) = std::complex<double>(pars(112), pars(113));
   ZN(2,0) = std::complex<double>(pars(114), pars(115));
   ZN(2,1) = std::complex<double>(pars(116), pars(117));
   ZN(2,2) = std::complex<double>(pars(118), pars(119));
   ZN(2,3) = std::complex<double>(pars(120), pars(121));
   ZN(3,0) = std::complex<double>(pars(122), pars(123));
   ZN(3,1) = std::complex<double>(pars(124), pars(125));
   ZN(3,2) = std::complex<double>(pars(126), pars(127));
   ZN(3,3) = std::complex<double>(pars(128), pars(129));
   UM(0,0) = std::complex<double>(pars(130), pars(131));
   UM(0,1) = std::complex<double>(pars(132), pars(133));
   UM(1,0) = std::complex<double>(pars(134), pars(135));
   UM(1,1) = std::complex<double>(pars(136), pars(137));
   UP(0,0) = std::complex<double>(pars(138), pars(139));
   UP(0,1) = std::complex<double>(pars(140), pars(141));
   UP(1,0) = std::complex<double>(pars(142), pars(143));
   UP(1,1) = std::complex<double>(pars(144), pars(145));
   ZZ(0,0) = pars(146);
   ZZ(0,1) = pars(147);
   ZZ(1,0) = pars(148);
   ZZ(1,1) = pars(149);

}

Eigen::ArrayXd CLASSNAME::get_DRbar_masses_and_mixings() const
{
   Eigen::ArrayXd pars(get_DRbar_masses());

   pars.conservativeResize(150);

   pars(50) = ZD(0,0);
   pars(51) = ZD(0,1);
   pars(52) = ZD(1,0);
   pars(53) = ZD(1,1);
   pars(54) = ZU(0,0);
   pars(55) = ZU(0,1);
   pars(56) = ZU(1,0);
   pars(57) = ZU(1,1);
   pars(58) = ZE(0,0);
   pars(59) = ZE(0,1);
   pars(60) = ZE(1,0);
   pars(61) = ZE(1,1);
   pars(62) = ZM(0,0);
   pars(63) = ZM(0,1);
   pars(64) = ZM(1,0);
   pars(65) = ZM(1,1);
   pars(66) = ZTau(0,0);
   pars(67) = ZTau(0,1);
   pars(68) = ZTau(1,0);
   pars(69) = ZTau(1,1);
   pars(70) = ZS(0,0);
   pars(71) = ZS(0,1);
   pars(72) = ZS(1,0);
   pars(73) = ZS(1,1);
   pars(74) = ZC(0,0);
   pars(75) = ZC(0,1);
   pars(76) = ZC(1,0);
   pars(77) = ZC(1,1);
   pars(78) = ZB(0,0);
   pars(79) = ZB(0,1);
   pars(80) = ZB(1,0);
   pars(81) = ZB(1,1);
   pars(82) = ZT(0,0);
   pars(83) = ZT(0,1);
   pars(84) = ZT(1,0);
   pars(85) = ZT(1,1);
   pars(86) = ZH(0,0);
   pars(87) = ZH(0,1);
   pars(88) = ZH(1,0);
   pars(89) = ZH(1,1);
   pars(90) = ZA(0,0);
   pars(91) = ZA(0,1);
   pars(92) = ZA(1,0);
   pars(93) = ZA(1,1);
   pars(94) = ZP(0,0);
   pars(95) = ZP(0,1);
   pars(96) = ZP(1,0);
   pars(97) = ZP(1,1);
   pars(98) = Re(ZN(0,0));
   pars(99) = Im(ZN(0,0));
   pars(100) = Re(ZN(0,1));
   pars(101) = Im(ZN(0,1));
   pars(102) = Re(ZN(0,2));
   pars(103) = Im(ZN(0,2));
   pars(104) = Re(ZN(0,3));
   pars(105) = Im(ZN(0,3));
   pars(106) = Re(ZN(1,0));
   pars(107) = Im(ZN(1,0));
   pars(108) = Re(ZN(1,1));
   pars(109) = Im(ZN(1,1));
   pars(110) = Re(ZN(1,2));
   pars(111) = Im(ZN(1,2));
   pars(112) = Re(ZN(1,3));
   pars(113) = Im(ZN(1,3));
   pars(114) = Re(ZN(2,0));
   pars(115) = Im(ZN(2,0));
   pars(116) = Re(ZN(2,1));
   pars(117) = Im(ZN(2,1));
   pars(118) = Re(ZN(2,2));
   pars(119) = Im(ZN(2,2));
   pars(120) = Re(ZN(2,3));
   pars(121) = Im(ZN(2,3));
   pars(122) = Re(ZN(3,0));
   pars(123) = Im(ZN(3,0));
   pars(124) = Re(ZN(3,1));
   pars(125) = Im(ZN(3,1));
   pars(126) = Re(ZN(3,2));
   pars(127) = Im(ZN(3,2));
   pars(128) = Re(ZN(3,3));
   pars(129) = Im(ZN(3,3));
   pars(130) = Re(UM(0,0));
   pars(131) = Im(UM(0,0));
   pars(132) = Re(UM(0,1));
   pars(133) = Im(UM(0,1));
   pars(134) = Re(UM(1,0));
   pars(135) = Im(UM(1,0));
   pars(136) = Re(UM(1,1));
   pars(137) = Im(UM(1,1));
   pars(138) = Re(UP(0,0));
   pars(139) = Im(UP(0,0));
   pars(140) = Re(UP(0,1));
   pars(141) = Im(UP(0,1));
   pars(142) = Re(UP(1,0));
   pars(143) = Im(UP(1,0));
   pars(144) = Re(UP(1,1));
   pars(145) = Im(UP(1,1));
   pars(146) = ZZ(0,0);
   pars(147) = ZZ(0,1);
   pars(148) = ZZ(1,0);
   pars(149) = ZZ(1,1);


   return pars;
}

void CLASSNAME::set_extra_parameters(const Eigen::ArrayXd& pars)
{

}

Eigen::ArrayXd CLASSNAME::get_extra_parameters() const
{
   return Eigen::ArrayXd();

}

std::string CLASSNAME::name() const
{
   return "CMSSMNoFV";
}

void CLASSNAME::run_to(double scale, double eps)
{
   if (eps < 0.0)
      eps = precision;
   CMSSMNoFV_soft_parameters::run_to(scale, eps);
}


Eigen::Array<double,1,1> CLASSNAME::get_MChargedHiggs() const
{
   Eigen::Array<double,1,1> MHpm_goldstone;
   MHpm_goldstone(0) = MVWm;

   return remove_if_equal(MHpm, MHpm_goldstone);
}

Eigen::Array<double,1,1> CLASSNAME::get_MPseudoscalarHiggs() const
{
   Eigen::Array<double,1,1> MAh_goldstone;
   MAh_goldstone(0) = MVZ;

   return remove_if_equal(MAh, MAh_goldstone);
}


/**
 * @brief finds the LSP and returns it's mass
 *
 * This function finds the lightest supersymmetric particle (LSP) and
 * returns it's mass.  The corresponding particle type is retured in
 * the reference parameter.  The list of potential LSPs is set in the
 * model file varible PotentialLSPParticles.  For this model it is set
 * to:
 * {Chi, SveL, SvmL, SvtL, Su, Sd, Sc, Ss, St, Sb, Se, Sm, Stau, Cha, Glu}
 *
 * @param particle_type particle type
 * @return mass of LSP
 */
double CLASSNAME::get_lsp(CMSSMNoFV_info::Particles& particle_type) const
{
   double lsp_mass = std::numeric_limits<double>::max();
   double tmp_mass;
   particle_type = CMSSMNoFV_info::NUMBER_OF_PARTICLES;

   tmp_mass = Abs(PHYSICAL(MChi(0)));
   if (tmp_mass < lsp_mass) {
      lsp_mass = tmp_mass;
      particle_type = CMSSMNoFV_info::Chi;
   }

   tmp_mass = Abs(PHYSICAL(MSveL));
   if (tmp_mass < lsp_mass) {
      lsp_mass = tmp_mass;
      particle_type = CMSSMNoFV_info::SveL;
   }

   tmp_mass = Abs(PHYSICAL(MSvmL));
   if (tmp_mass < lsp_mass) {
      lsp_mass = tmp_mass;
      particle_type = CMSSMNoFV_info::SvmL;
   }

   tmp_mass = Abs(PHYSICAL(MSvtL));
   if (tmp_mass < lsp_mass) {
      lsp_mass = tmp_mass;
      particle_type = CMSSMNoFV_info::SvtL;
   }

   tmp_mass = Abs(PHYSICAL(MSu(0)));
   if (tmp_mass < lsp_mass) {
      lsp_mass = tmp_mass;
      particle_type = CMSSMNoFV_info::Su;
   }

   tmp_mass = Abs(PHYSICAL(MSd(0)));
   if (tmp_mass < lsp_mass) {
      lsp_mass = tmp_mass;
      particle_type = CMSSMNoFV_info::Sd;
   }

   tmp_mass = Abs(PHYSICAL(MSc(0)));
   if (tmp_mass < lsp_mass) {
      lsp_mass = tmp_mass;
      particle_type = CMSSMNoFV_info::Sc;
   }

   tmp_mass = Abs(PHYSICAL(MSs(0)));
   if (tmp_mass < lsp_mass) {
      lsp_mass = tmp_mass;
      particle_type = CMSSMNoFV_info::Ss;
   }

   tmp_mass = Abs(PHYSICAL(MSt(0)));
   if (tmp_mass < lsp_mass) {
      lsp_mass = tmp_mass;
      particle_type = CMSSMNoFV_info::St;
   }

   tmp_mass = Abs(PHYSICAL(MSb(0)));
   if (tmp_mass < lsp_mass) {
      lsp_mass = tmp_mass;
      particle_type = CMSSMNoFV_info::Sb;
   }

   tmp_mass = Abs(PHYSICAL(MSe(0)));
   if (tmp_mass < lsp_mass) {
      lsp_mass = tmp_mass;
      particle_type = CMSSMNoFV_info::Se;
   }

   tmp_mass = Abs(PHYSICAL(MSm(0)));
   if (tmp_mass < lsp_mass) {
      lsp_mass = tmp_mass;
      particle_type = CMSSMNoFV_info::Sm;
   }

   tmp_mass = Abs(PHYSICAL(MStau(0)));
   if (tmp_mass < lsp_mass) {
      lsp_mass = tmp_mass;
      particle_type = CMSSMNoFV_info::Stau;
   }

   tmp_mass = Abs(PHYSICAL(MCha(0)));
   if (tmp_mass < lsp_mass) {
      lsp_mass = tmp_mass;
      particle_type = CMSSMNoFV_info::Cha;
   }

   tmp_mass = Abs(PHYSICAL(MGlu));
   if (tmp_mass < lsp_mass) {
      lsp_mass = tmp_mass;
      particle_type = CMSSMNoFV_info::Glu;
   }

   return lsp_mass;
}


double CLASSNAME::get_mass_matrix_VG() const
{
   const double mass_matrix_VG = Re(0);

   return mass_matrix_VG;
}

void CLASSNAME::calculate_MVG()
{
   const auto mass_matrix_VG = get_mass_matrix_VG();
   MVG = mass_matrix_VG;
}

double CLASSNAME::get_mass_matrix_Glu() const
{
   const double mass_matrix_Glu = Re(MassG);

   return mass_matrix_Glu;
}

void CLASSNAME::calculate_MGlu()
{
   const auto mass_matrix_Glu = get_mass_matrix_Glu();
   MGlu = calculate_majorana_singlet_mass(mass_matrix_Glu, PhaseGlu);
}

double CLASSNAME::get_mass_matrix_Fd() const
{
   const double mass_matrix_Fd = Re(0.7071067811865475*vd*Yd(0,0));

   return mass_matrix_Fd;
}

void CLASSNAME::calculate_MFd()
{
   const auto mass_matrix_Fd = get_mass_matrix_Fd();
   MFd = calculate_singlet_mass(mass_matrix_Fd);
}

double CLASSNAME::get_mass_matrix_Fs() const
{
   const double mass_matrix_Fs = Re(0.7071067811865475*vd*Yd(1,1));

   return mass_matrix_Fs;
}

void CLASSNAME::calculate_MFs()
{
   const auto mass_matrix_Fs = get_mass_matrix_Fs();
   MFs = calculate_singlet_mass(mass_matrix_Fs);
}

double CLASSNAME::get_mass_matrix_Fb() const
{
   const double mass_matrix_Fb = Re(0.7071067811865475*vd*Yd(2,2));

   return mass_matrix_Fb;
}

void CLASSNAME::calculate_MFb()
{
   const auto mass_matrix_Fb = get_mass_matrix_Fb();
   MFb = calculate_singlet_mass(mass_matrix_Fb);
}

double CLASSNAME::get_mass_matrix_Fu() const
{
   const double mass_matrix_Fu = Re(0.7071067811865475*vu*Yu(0,0));

   return mass_matrix_Fu;
}

void CLASSNAME::calculate_MFu()
{
   const auto mass_matrix_Fu = get_mass_matrix_Fu();
   MFu = calculate_singlet_mass(mass_matrix_Fu);
}

double CLASSNAME::get_mass_matrix_Fc() const
{
   const double mass_matrix_Fc = Re(0.7071067811865475*vu*Yu(1,1));

   return mass_matrix_Fc;
}

void CLASSNAME::calculate_MFc()
{
   const auto mass_matrix_Fc = get_mass_matrix_Fc();
   MFc = calculate_singlet_mass(mass_matrix_Fc);
}

double CLASSNAME::get_mass_matrix_Ft() const
{
   const double mass_matrix_Ft = Re(0.7071067811865475*vu*Yu(2,2));

   return mass_matrix_Ft;
}

void CLASSNAME::calculate_MFt()
{
   const auto mass_matrix_Ft = get_mass_matrix_Ft();
   MFt = calculate_singlet_mass(mass_matrix_Ft);
}

double CLASSNAME::get_mass_matrix_Fve() const
{
   const double mass_matrix_Fve = Re(0);

   return mass_matrix_Fve;
}

void CLASSNAME::calculate_MFve()
{
   const auto mass_matrix_Fve = get_mass_matrix_Fve();
   MFve = calculate_singlet_mass(mass_matrix_Fve);
}

double CLASSNAME::get_mass_matrix_Fvm() const
{
   const double mass_matrix_Fvm = Re(0);

   return mass_matrix_Fvm;
}

void CLASSNAME::calculate_MFvm()
{
   const auto mass_matrix_Fvm = get_mass_matrix_Fvm();
   MFvm = calculate_singlet_mass(mass_matrix_Fvm);
}

double CLASSNAME::get_mass_matrix_Fvt() const
{
   const double mass_matrix_Fvt = Re(0);

   return mass_matrix_Fvt;
}

void CLASSNAME::calculate_MFvt()
{
   const auto mass_matrix_Fvt = get_mass_matrix_Fvt();
   MFvt = calculate_singlet_mass(mass_matrix_Fvt);
}

double CLASSNAME::get_mass_matrix_Fe() const
{
   const double mass_matrix_Fe = Re(0.7071067811865475*vd*Ye(0,0));

   return mass_matrix_Fe;
}

void CLASSNAME::calculate_MFe()
{
   const auto mass_matrix_Fe = get_mass_matrix_Fe();
   MFe = calculate_singlet_mass(mass_matrix_Fe);
}

double CLASSNAME::get_mass_matrix_Fm() const
{
   const double mass_matrix_Fm = Re(0.7071067811865475*vd*Ye(1,1));

   return mass_matrix_Fm;
}

void CLASSNAME::calculate_MFm()
{
   const auto mass_matrix_Fm = get_mass_matrix_Fm();
   MFm = calculate_singlet_mass(mass_matrix_Fm);
}

double CLASSNAME::get_mass_matrix_Ftau() const
{
   const double mass_matrix_Ftau = Re(0.7071067811865475*vd*Ye(2,2));

   return mass_matrix_Ftau;
}

void CLASSNAME::calculate_MFtau()
{
   const auto mass_matrix_Ftau = get_mass_matrix_Ftau();
   MFtau = calculate_singlet_mass(mass_matrix_Ftau);
}

double CLASSNAME::get_mass_matrix_SveL() const
{
   const double mass_matrix_SveL = Re(0.125*(8*ml2(0,0) - 0.6*Sqr(g1)*(
      -Sqr(vd) + Sqr(vu)) - Sqr(g2)*(-Sqr(vd) + Sqr(vu))));

   return mass_matrix_SveL;
}

void CLASSNAME::calculate_MSveL()
{
   const auto mass_matrix_SveL = get_mass_matrix_SveL();
   MSveL = mass_matrix_SveL;

   if (MSveL < 0.) {
      problems.flag_running_tachyon(CMSSMNoFV_info::SveL);
   }

   MSveL = AbsSqrt(MSveL);
}

double CLASSNAME::get_mass_matrix_SvmL() const
{
   const double mass_matrix_SvmL = Re(0.125*(8*ml2(1,1) - 0.6*Sqr(g1)*(
      -Sqr(vd) + Sqr(vu)) - Sqr(g2)*(-Sqr(vd) + Sqr(vu))));

   return mass_matrix_SvmL;
}

void CLASSNAME::calculate_MSvmL()
{
   const auto mass_matrix_SvmL = get_mass_matrix_SvmL();
   MSvmL = mass_matrix_SvmL;

   if (MSvmL < 0.) {
      problems.flag_running_tachyon(CMSSMNoFV_info::SvmL);
   }

   MSvmL = AbsSqrt(MSvmL);
}

double CLASSNAME::get_mass_matrix_SvtL() const
{
   const double mass_matrix_SvtL = Re(0.125*(8*ml2(2,2) - 0.6*Sqr(g1)*(
      -Sqr(vd) + Sqr(vu)) - Sqr(g2)*(-Sqr(vd) + Sqr(vu))));

   return mass_matrix_SvtL;
}

void CLASSNAME::calculate_MSvtL()
{
   const auto mass_matrix_SvtL = get_mass_matrix_SvtL();
   MSvtL = mass_matrix_SvtL;

   if (MSvtL < 0.) {
      problems.flag_running_tachyon(CMSSMNoFV_info::SvtL);
   }

   MSvtL = AbsSqrt(MSvtL);
}

Eigen::Matrix<double,2,2> CLASSNAME::get_mass_matrix_Sd() const
{
   Eigen::Matrix<double,2,2> mass_matrix_Sd;

   mass_matrix_Sd(0,0) = mq2(0,0) + 0.5*AbsSqr(Yd(0,0))*Sqr(vd) - 0.025*
      Sqr(g1)*Sqr(vd) - 0.125*Sqr(g2)*Sqr(vd) + 0.025*Sqr(g1)*Sqr(vu) + 0.125*
      Sqr(g2)*Sqr(vu);
   mass_matrix_Sd(0,1) = 0.7071067811865475*vd*Conj(TYd(0,0)) -
      0.7071067811865475*vu*Conj(Yd(0,0))*Mu;
   mass_matrix_Sd(1,1) = md2(0,0) + 0.5*AbsSqr(Yd(0,0))*Sqr(vd) - 0.05*
      Sqr(g1)*Sqr(vd) + 0.05*Sqr(g1)*Sqr(vu);

   Hermitianize(mass_matrix_Sd);

   return mass_matrix_Sd;
}

void CLASSNAME::calculate_MSd()
{
   const auto mass_matrix_Sd(get_mass_matrix_Sd());


#ifdef CHECK_EIGENVALUE_ERROR
   double eigenvalue_error;
   fs_diagonalize_hermitian(mass_matrix_Sd, MSd, ZD, eigenvalue_error);
   problems.flag_bad_mass(CMSSMNoFV_info::Sd, eigenvalue_error >
      precision * Abs(MSd(0)));
#else
   fs_diagonalize_hermitian(mass_matrix_Sd, MSd, ZD);
#endif
   normalize_to_interval(ZD);


   if (MSd.minCoeff() < 0.) {
      problems.flag_running_tachyon(CMSSMNoFV_info::Sd);
   }

   MSd = AbsSqrt(MSd);
}

Eigen::Matrix<double,2,2> CLASSNAME::get_mass_matrix_Su() const
{
   Eigen::Matrix<double,2,2> mass_matrix_Su;

   mass_matrix_Su(0,0) = mq2(0,0) - 0.025*Sqr(g1)*Sqr(vd) + 0.125*Sqr(g2)
      *Sqr(vd) + 0.5*AbsSqr(Yu(0,0))*Sqr(vu) + 0.025*Sqr(g1)*Sqr(vu) - 0.125*
      Sqr(g2)*Sqr(vu);
   mass_matrix_Su(0,1) = 0.7071067811865475*vu*Conj(TYu(0,0)) -
      0.7071067811865475*vd*Conj(Yu(0,0))*Mu;
   mass_matrix_Su(1,1) = mu2(0,0) + 0.1*Sqr(g1)*Sqr(vd) + 0.5*AbsSqr(Yu(0
      ,0))*Sqr(vu) - 0.1*Sqr(g1)*Sqr(vu);

   Hermitianize(mass_matrix_Su);

   return mass_matrix_Su;
}

void CLASSNAME::calculate_MSu()
{
   const auto mass_matrix_Su(get_mass_matrix_Su());


#ifdef CHECK_EIGENVALUE_ERROR
   double eigenvalue_error;
   fs_diagonalize_hermitian(mass_matrix_Su, MSu, ZU, eigenvalue_error);
   problems.flag_bad_mass(CMSSMNoFV_info::Su, eigenvalue_error >
      precision * Abs(MSu(0)));
#else
   fs_diagonalize_hermitian(mass_matrix_Su, MSu, ZU);
#endif
   normalize_to_interval(ZU);


   if (MSu.minCoeff() < 0.) {
      problems.flag_running_tachyon(CMSSMNoFV_info::Su);
   }

   MSu = AbsSqrt(MSu);
}

Eigen::Matrix<double,2,2> CLASSNAME::get_mass_matrix_Se() const
{
   Eigen::Matrix<double,2,2> mass_matrix_Se;

   mass_matrix_Se(0,0) = ml2(0,0) + 0.5*AbsSqr(Ye(0,0))*Sqr(vd) + 0.075*
      Sqr(g1)*Sqr(vd) - 0.125*Sqr(g2)*Sqr(vd) - 0.075*Sqr(g1)*Sqr(vu) + 0.125*
      Sqr(g2)*Sqr(vu);
   mass_matrix_Se(0,1) = 0.7071067811865475*vd*Conj(TYe(0,0)) -
      0.7071067811865475*vu*Conj(Ye(0,0))*Mu;
   mass_matrix_Se(1,1) = me2(0,0) + 0.5*AbsSqr(Ye(0,0))*Sqr(vd) - 0.15*
      Sqr(g1)*Sqr(vd) + 0.15*Sqr(g1)*Sqr(vu);

   Hermitianize(mass_matrix_Se);

   return mass_matrix_Se;
}

void CLASSNAME::calculate_MSe()
{
   const auto mass_matrix_Se(get_mass_matrix_Se());


#ifdef CHECK_EIGENVALUE_ERROR
   double eigenvalue_error;
   fs_diagonalize_hermitian(mass_matrix_Se, MSe, ZE, eigenvalue_error);
   problems.flag_bad_mass(CMSSMNoFV_info::Se, eigenvalue_error >
      precision * Abs(MSe(0)));
#else
   fs_diagonalize_hermitian(mass_matrix_Se, MSe, ZE);
#endif
   normalize_to_interval(ZE);


   if (MSe.minCoeff() < 0.) {
      problems.flag_running_tachyon(CMSSMNoFV_info::Se);
   }

   MSe = AbsSqrt(MSe);
}

Eigen::Matrix<double,2,2> CLASSNAME::get_mass_matrix_Sm() const
{
   Eigen::Matrix<double,2,2> mass_matrix_Sm;

   mass_matrix_Sm(0,0) = ml2(1,1) + 0.5*AbsSqr(Ye(1,1))*Sqr(vd) + 0.075*
      Sqr(g1)*Sqr(vd) - 0.125*Sqr(g2)*Sqr(vd) - 0.075*Sqr(g1)*Sqr(vu) + 0.125*
      Sqr(g2)*Sqr(vu);
   mass_matrix_Sm(0,1) = 0.7071067811865475*vd*Conj(TYe(1,1)) -
      0.7071067811865475*vu*Conj(Ye(1,1))*Mu;
   mass_matrix_Sm(1,1) = me2(1,1) + 0.5*AbsSqr(Ye(1,1))*Sqr(vd) - 0.15*
      Sqr(g1)*Sqr(vd) + 0.15*Sqr(g1)*Sqr(vu);

   Hermitianize(mass_matrix_Sm);

   return mass_matrix_Sm;
}

void CLASSNAME::calculate_MSm()
{
   const auto mass_matrix_Sm(get_mass_matrix_Sm());


#ifdef CHECK_EIGENVALUE_ERROR
   double eigenvalue_error;
   fs_diagonalize_hermitian(mass_matrix_Sm, MSm, ZM, eigenvalue_error);
   problems.flag_bad_mass(CMSSMNoFV_info::Sm, eigenvalue_error >
      precision * Abs(MSm(0)));
#else
   fs_diagonalize_hermitian(mass_matrix_Sm, MSm, ZM);
#endif
   normalize_to_interval(ZM);


   if (MSm.minCoeff() < 0.) {
      problems.flag_running_tachyon(CMSSMNoFV_info::Sm);
   }

   MSm = AbsSqrt(MSm);
}

Eigen::Matrix<double,2,2> CLASSNAME::get_mass_matrix_Stau() const
{
   Eigen::Matrix<double,2,2> mass_matrix_Stau;

   mass_matrix_Stau(0,0) = ml2(2,2) + 0.5*AbsSqr(Ye(2,2))*Sqr(vd) + 0.075
      *Sqr(g1)*Sqr(vd) - 0.125*Sqr(g2)*Sqr(vd) - 0.075*Sqr(g1)*Sqr(vu) + 0.125*
      Sqr(g2)*Sqr(vu);
   mass_matrix_Stau(0,1) = 0.7071067811865475*vd*Conj(TYe(2,2)) -
      0.7071067811865475*vu*Conj(Ye(2,2))*Mu;
   mass_matrix_Stau(1,1) = me2(2,2) + 0.5*AbsSqr(Ye(2,2))*Sqr(vd) - 0.15*
      Sqr(g1)*Sqr(vd) + 0.15*Sqr(g1)*Sqr(vu);

   Hermitianize(mass_matrix_Stau);

   return mass_matrix_Stau;
}

void CLASSNAME::calculate_MStau()
{
   const auto mass_matrix_Stau(get_mass_matrix_Stau());


#ifdef CHECK_EIGENVALUE_ERROR
   double eigenvalue_error;
   fs_diagonalize_hermitian(mass_matrix_Stau, MStau, ZTau,
      eigenvalue_error);
   problems.flag_bad_mass(CMSSMNoFV_info::Stau, eigenvalue_error >
      precision * Abs(MStau(0)));
#else
   fs_diagonalize_hermitian(mass_matrix_Stau, MStau, ZTau);
#endif
   normalize_to_interval(ZTau);


   if (MStau.minCoeff() < 0.) {
      problems.flag_running_tachyon(CMSSMNoFV_info::Stau);
   }

   MStau = AbsSqrt(MStau);
}

Eigen::Matrix<double,2,2> CLASSNAME::get_mass_matrix_Ss() const
{
   Eigen::Matrix<double,2,2> mass_matrix_Ss;

   mass_matrix_Ss(0,0) = mq2(1,1) + 0.5*AbsSqr(Yd(1,1))*Sqr(vd) - 0.025*
      Sqr(g1)*Sqr(vd) - 0.125*Sqr(g2)*Sqr(vd) + 0.025*Sqr(g1)*Sqr(vu) + 0.125*
      Sqr(g2)*Sqr(vu);
   mass_matrix_Ss(0,1) = 0.7071067811865475*vd*Conj(TYd(1,1)) -
      0.7071067811865475*vu*Conj(Yd(1,1))*Mu;
   mass_matrix_Ss(1,1) = md2(1,1) + 0.5*AbsSqr(Yd(1,1))*Sqr(vd) - 0.05*
      Sqr(g1)*Sqr(vd) + 0.05*Sqr(g1)*Sqr(vu);

   Hermitianize(mass_matrix_Ss);

   return mass_matrix_Ss;
}

void CLASSNAME::calculate_MSs()
{
   const auto mass_matrix_Ss(get_mass_matrix_Ss());


#ifdef CHECK_EIGENVALUE_ERROR
   double eigenvalue_error;
   fs_diagonalize_hermitian(mass_matrix_Ss, MSs, ZS, eigenvalue_error);
   problems.flag_bad_mass(CMSSMNoFV_info::Ss, eigenvalue_error >
      precision * Abs(MSs(0)));
#else
   fs_diagonalize_hermitian(mass_matrix_Ss, MSs, ZS);
#endif
   normalize_to_interval(ZS);


   if (MSs.minCoeff() < 0.) {
      problems.flag_running_tachyon(CMSSMNoFV_info::Ss);
   }

   MSs = AbsSqrt(MSs);
}

Eigen::Matrix<double,2,2> CLASSNAME::get_mass_matrix_Sc() const
{
   Eigen::Matrix<double,2,2> mass_matrix_Sc;

   mass_matrix_Sc(0,0) = mq2(1,1) - 0.025*Sqr(g1)*Sqr(vd) + 0.125*Sqr(g2)
      *Sqr(vd) + 0.5*AbsSqr(Yu(1,1))*Sqr(vu) + 0.025*Sqr(g1)*Sqr(vu) - 0.125*
      Sqr(g2)*Sqr(vu);
   mass_matrix_Sc(0,1) = 0.7071067811865475*vu*Conj(TYu(1,1)) -
      0.7071067811865475*vd*Conj(Yu(1,1))*Mu;
   mass_matrix_Sc(1,1) = mu2(1,1) + 0.1*Sqr(g1)*Sqr(vd) + 0.5*AbsSqr(Yu(1
      ,1))*Sqr(vu) - 0.1*Sqr(g1)*Sqr(vu);

   Hermitianize(mass_matrix_Sc);

   return mass_matrix_Sc;
}

void CLASSNAME::calculate_MSc()
{
   const auto mass_matrix_Sc(get_mass_matrix_Sc());


#ifdef CHECK_EIGENVALUE_ERROR
   double eigenvalue_error;
   fs_diagonalize_hermitian(mass_matrix_Sc, MSc, ZC, eigenvalue_error);
   problems.flag_bad_mass(CMSSMNoFV_info::Sc, eigenvalue_error >
      precision * Abs(MSc(0)));
#else
   fs_diagonalize_hermitian(mass_matrix_Sc, MSc, ZC);
#endif
   normalize_to_interval(ZC);


   if (MSc.minCoeff() < 0.) {
      problems.flag_running_tachyon(CMSSMNoFV_info::Sc);
   }

   MSc = AbsSqrt(MSc);
}

Eigen::Matrix<double,2,2> CLASSNAME::get_mass_matrix_Sb() const
{
   Eigen::Matrix<double,2,2> mass_matrix_Sb;

   mass_matrix_Sb(0,0) = mq2(2,2) + 0.5*AbsSqr(Yd(2,2))*Sqr(vd) - 0.025*
      Sqr(g1)*Sqr(vd) - 0.125*Sqr(g2)*Sqr(vd) + 0.025*Sqr(g1)*Sqr(vu) + 0.125*
      Sqr(g2)*Sqr(vu);
   mass_matrix_Sb(0,1) = 0.7071067811865475*vd*Conj(TYd(2,2)) -
      0.7071067811865475*vu*Conj(Yd(2,2))*Mu;
   mass_matrix_Sb(1,1) = md2(2,2) + 0.5*AbsSqr(Yd(2,2))*Sqr(vd) - 0.05*
      Sqr(g1)*Sqr(vd) + 0.05*Sqr(g1)*Sqr(vu);

   Hermitianize(mass_matrix_Sb);

   return mass_matrix_Sb;
}

void CLASSNAME::calculate_MSb()
{
   const auto mass_matrix_Sb(get_mass_matrix_Sb());


#ifdef CHECK_EIGENVALUE_ERROR
   double eigenvalue_error;
   fs_diagonalize_hermitian(mass_matrix_Sb, MSb, ZB, eigenvalue_error);
   problems.flag_bad_mass(CMSSMNoFV_info::Sb, eigenvalue_error >
      precision * Abs(MSb(0)));
#else
   fs_diagonalize_hermitian(mass_matrix_Sb, MSb, ZB);
#endif
   normalize_to_interval(ZB);


   if (MSb.minCoeff() < 0.) {
      problems.flag_running_tachyon(CMSSMNoFV_info::Sb);
   }

   MSb = AbsSqrt(MSb);
}

Eigen::Matrix<double,2,2> CLASSNAME::get_mass_matrix_St() const
{
   Eigen::Matrix<double,2,2> mass_matrix_St;

   mass_matrix_St(0,0) = mq2(2,2) - 0.025*Sqr(g1)*Sqr(vd) + 0.125*Sqr(g2)
      *Sqr(vd) + 0.5*AbsSqr(Yu(2,2))*Sqr(vu) + 0.025*Sqr(g1)*Sqr(vu) - 0.125*
      Sqr(g2)*Sqr(vu);
   mass_matrix_St(0,1) = 0.7071067811865475*vu*Conj(TYu(2,2)) -
      0.7071067811865475*vd*Conj(Yu(2,2))*Mu;
   mass_matrix_St(1,1) = mu2(2,2) + 0.1*Sqr(g1)*Sqr(vd) + 0.5*AbsSqr(Yu(2
      ,2))*Sqr(vu) - 0.1*Sqr(g1)*Sqr(vu);

   Hermitianize(mass_matrix_St);

   return mass_matrix_St;
}

void CLASSNAME::calculate_MSt()
{
   const auto mass_matrix_St(get_mass_matrix_St());


#ifdef CHECK_EIGENVALUE_ERROR
   double eigenvalue_error;
   fs_diagonalize_hermitian(mass_matrix_St, MSt, ZT, eigenvalue_error);
   problems.flag_bad_mass(CMSSMNoFV_info::St, eigenvalue_error >
      precision * Abs(MSt(0)));
#else
   fs_diagonalize_hermitian(mass_matrix_St, MSt, ZT);
#endif
   normalize_to_interval(ZT);


   if (MSt.minCoeff() < 0.) {
      problems.flag_running_tachyon(CMSSMNoFV_info::St);
   }

   MSt = AbsSqrt(MSt);
}

Eigen::Matrix<double,2,2> CLASSNAME::get_mass_matrix_hh() const
{
   Eigen::Matrix<double,2,2> mass_matrix_hh;

   mass_matrix_hh(0,0) = mHd2 + AbsSqr(Mu) + 0.225*Sqr(g1)*Sqr(vd) +
      0.375*Sqr(g2)*Sqr(vd) - 0.075*Sqr(g1)*Sqr(vu) - 0.125*Sqr(g2)*Sqr(vu);
   mass_matrix_hh(0,1) = -0.5*BMu - 0.5*Conj(BMu) - 0.15*vd*vu*Sqr(g1) -
      0.25*vd*vu*Sqr(g2);
   mass_matrix_hh(1,1) = mHu2 + AbsSqr(Mu) - 0.075*Sqr(g1)*Sqr(vd) -
      0.125*Sqr(g2)*Sqr(vd) + 0.225*Sqr(g1)*Sqr(vu) + 0.375*Sqr(g2)*Sqr(vu);

   Symmetrize(mass_matrix_hh);

   return mass_matrix_hh;
}

void CLASSNAME::calculate_Mhh()
{
   const auto mass_matrix_hh(get_mass_matrix_hh());


#ifdef CHECK_EIGENVALUE_ERROR
   double eigenvalue_error;
   fs_diagonalize_hermitian(mass_matrix_hh, Mhh, ZH, eigenvalue_error);
   problems.flag_bad_mass(CMSSMNoFV_info::hh, eigenvalue_error >
      precision * Abs(Mhh(0)));
#else
   fs_diagonalize_hermitian(mass_matrix_hh, Mhh, ZH);
#endif
   normalize_to_interval(ZH);


   if (Mhh.minCoeff() < 0.) {
      problems.flag_running_tachyon(CMSSMNoFV_info::hh);
   }

   Mhh = AbsSqrt(Mhh);
}

Eigen::Matrix<double,2,2> CLASSNAME::get_mass_matrix_Ah() const
{
   Eigen::Matrix<double,2,2> mass_matrix_Ah;

   mass_matrix_Ah(0,0) = mHd2 + AbsSqr(Mu) + 0.3872983346207417*g1*g2*Cos
      (ThetaW())*Sin(ThetaW())*Sqr(vd) + 0.075*Sqr(g1)*Sqr(vd) + 0.125*Sqr(g2)*
      Sqr(vd) - 0.075*Sqr(g1)*Sqr(vu) - 0.125*Sqr(g2)*Sqr(vu) + 0.25*Sqr(g2)*
      Sqr(vd)*Sqr(Cos(ThetaW())) + 0.15*Sqr(g1)*Sqr(vd)*Sqr(Sin(ThetaW()));
   mass_matrix_Ah(0,1) = 0.5*BMu + 0.5*Conj(BMu) - 0.3872983346207417*g1*
      g2*vd*vu*Cos(ThetaW())*Sin(ThetaW()) - 0.25*vd*vu*Sqr(g2)*Sqr(Cos(ThetaW(
      ))) - 0.15*vd*vu*Sqr(g1)*Sqr(Sin(ThetaW()));
   mass_matrix_Ah(1,1) = mHu2 + AbsSqr(Mu) - 0.075*Sqr(g1)*Sqr(vd) -
      0.125*Sqr(g2)*Sqr(vd) + 0.3872983346207417*g1*g2*Cos(ThetaW())*Sin(ThetaW
      ())*Sqr(vu) + 0.075*Sqr(g1)*Sqr(vu) + 0.125*Sqr(g2)*Sqr(vu) + 0.25*Sqr(g2
      )*Sqr(vu)*Sqr(Cos(ThetaW())) + 0.15*Sqr(g1)*Sqr(vu)*Sqr(Sin(ThetaW()));

   Symmetrize(mass_matrix_Ah);

   return mass_matrix_Ah;
}

void CLASSNAME::calculate_MAh()
{
   const auto mass_matrix_Ah(get_mass_matrix_Ah());


#ifdef CHECK_EIGENVALUE_ERROR
   double eigenvalue_error;
   fs_diagonalize_hermitian(mass_matrix_Ah, MAh, ZA, eigenvalue_error);
   problems.flag_bad_mass(CMSSMNoFV_info::Ah, eigenvalue_error >
      precision * Abs(MAh(0)));
#else
   fs_diagonalize_hermitian(mass_matrix_Ah, MAh, ZA);
#endif
   normalize_to_interval(ZA);


   if (MAh.minCoeff() < 0.) {
      problems.flag_running_tachyon(CMSSMNoFV_info::Ah);
   }

   MAh = AbsSqrt(MAh);
}

Eigen::Matrix<double,2,2> CLASSNAME::get_mass_matrix_Hpm() const
{
   Eigen::Matrix<double,2,2> mass_matrix_Hpm;

   mass_matrix_Hpm(0,0) = mHd2 + AbsSqr(Mu) + 0.075*Sqr(g1)*Sqr(vd) +
      0.375*Sqr(g2)*Sqr(vd) - 0.075*Sqr(g1)*Sqr(vu) + 0.125*Sqr(g2)*Sqr(vu);
   mass_matrix_Hpm(0,1) = Conj(BMu);
   mass_matrix_Hpm(1,1) = mHu2 + AbsSqr(Mu) - 0.075*Sqr(g1)*Sqr(vd) +
      0.125*Sqr(g2)*Sqr(vd) + 0.075*Sqr(g1)*Sqr(vu) + 0.375*Sqr(g2)*Sqr(vu);

   Hermitianize(mass_matrix_Hpm);

   return mass_matrix_Hpm;
}

void CLASSNAME::calculate_MHpm()
{
   const auto mass_matrix_Hpm(get_mass_matrix_Hpm());


#ifdef CHECK_EIGENVALUE_ERROR
   double eigenvalue_error;
   fs_diagonalize_hermitian(mass_matrix_Hpm, MHpm, ZP, eigenvalue_error);
   problems.flag_bad_mass(CMSSMNoFV_info::Hpm, eigenvalue_error >
      precision * Abs(MHpm(0)));
#else
   fs_diagonalize_hermitian(mass_matrix_Hpm, MHpm, ZP);
#endif
   normalize_to_interval(ZP);


   if (MHpm.minCoeff() < 0.) {
      problems.flag_running_tachyon(CMSSMNoFV_info::Hpm);
   }

   MHpm = AbsSqrt(MHpm);
}

Eigen::Matrix<double,4,4> CLASSNAME::get_mass_matrix_Chi() const
{
   Eigen::Matrix<double,4,4> mass_matrix_Chi;

   mass_matrix_Chi(0,0) = MassB;
   mass_matrix_Chi(0,1) = 0;
   mass_matrix_Chi(0,2) = -0.3872983346207417*g1*vd;
   mass_matrix_Chi(0,3) = 0.3872983346207417*g1*vu;
   mass_matrix_Chi(1,1) = MassWB;
   mass_matrix_Chi(1,2) = 0.5*g2*vd;
   mass_matrix_Chi(1,3) = -0.5*g2*vu;
   mass_matrix_Chi(2,2) = 0;
   mass_matrix_Chi(2,3) = -Mu;
   mass_matrix_Chi(3,3) = 0;

   Symmetrize(mass_matrix_Chi);

   return mass_matrix_Chi;
}

void CLASSNAME::calculate_MChi()
{
   const auto mass_matrix_Chi(get_mass_matrix_Chi());


#ifdef CHECK_EIGENVALUE_ERROR
   double eigenvalue_error;
   fs_diagonalize_symmetric(mass_matrix_Chi, MChi, ZN, eigenvalue_error);
   problems.flag_bad_mass(CMSSMNoFV_info::Chi, eigenvalue_error >
      precision * Abs(MChi(0)));
#else
   fs_diagonalize_symmetric(mass_matrix_Chi, MChi, ZN);
#endif
   normalize_to_interval(ZN);

}

Eigen::Matrix<double,2,2> CLASSNAME::get_mass_matrix_Cha() const
{
   Eigen::Matrix<double,2,2> mass_matrix_Cha;

   mass_matrix_Cha(0,0) = MassWB;
   mass_matrix_Cha(0,1) = 0.7071067811865475*g2*vu;
   mass_matrix_Cha(1,0) = 0.7071067811865475*g2*vd;
   mass_matrix_Cha(1,1) = Mu;

   return mass_matrix_Cha;
}

void CLASSNAME::calculate_MCha()
{
   const auto mass_matrix_Cha(get_mass_matrix_Cha());


#ifdef CHECK_EIGENVALUE_ERROR
   double eigenvalue_error;
   fs_svd(mass_matrix_Cha, MCha, UM, UP, eigenvalue_error);
   problems.flag_bad_mass(CMSSMNoFV_info::Cha, eigenvalue_error >
      precision * Abs(MCha(0)));
#else
   fs_svd(mass_matrix_Cha, MCha, UM, UP);
#endif

}

double CLASSNAME::get_mass_matrix_VWm() const
{
   const double mass_matrix_VWm = Re(0.25*Sqr(g2)*(Sqr(vd) + Sqr(vu)));

   return mass_matrix_VWm;
}

void CLASSNAME::calculate_MVWm()
{
   const auto mass_matrix_VWm = get_mass_matrix_VWm();
   MVWm = mass_matrix_VWm;

   if (MVWm < 0.) {
      problems.flag_running_tachyon(CMSSMNoFV_info::VWm);
   }

   MVWm = AbsSqrt(MVWm);
}

Eigen::Matrix<double,2,2> CLASSNAME::get_mass_matrix_VPVZ() const
{
   Eigen::Matrix<double,2,2> mass_matrix_VPVZ;

   mass_matrix_VPVZ(0,0) = 0.15*Sqr(g1)*Sqr(vd) + 0.15*Sqr(g1)*Sqr(vu);
   mass_matrix_VPVZ(0,1) = -0.19364916731037085*g1*g2*Sqr(vd) -
      0.19364916731037085*g1*g2*Sqr(vu);
   mass_matrix_VPVZ(1,1) = 0.25*Sqr(g2)*Sqr(vd) + 0.25*Sqr(g2)*Sqr(vu);

   Symmetrize(mass_matrix_VPVZ);

   return mass_matrix_VPVZ;
}

void CLASSNAME::calculate_MVPVZ()
{
   const auto mass_matrix_VPVZ(get_mass_matrix_VPVZ());
   Eigen::Array<double,2,1> MVPVZ;


#ifdef CHECK_EIGENVALUE_ERROR
   double eigenvalue_error;
   fs_diagonalize_hermitian(mass_matrix_VPVZ, MVPVZ, ZZ, eigenvalue_error
      );
#else
   fs_diagonalize_hermitian(mass_matrix_VPVZ, MVPVZ, ZZ);
#endif
   ZZ.transposeInPlace();
   normalize_to_interval(ZZ);


   MVPVZ = AbsSqrt(MVPVZ);

   MVP = 0.;
   MVZ = MVPVZ(1);
}


double CLASSNAME::get_ewsb_eq_hh_1() const
{
   double result = Re(mHd2*vd + vd*AbsSqr(Mu) - 0.5*vu*BMu - 0.5*vu*Conj(BMu) +
      0.075*Cube(vd)*Sqr(g1) + 0.125*Cube(vd)*Sqr(g2) - 0.075*vd*Sqr(g1)*Sqr(vu)
      - 0.125*vd*Sqr(g2)*Sqr(vu));

   return result;
}

double CLASSNAME::get_ewsb_eq_hh_2() const
{
   double result = Re(mHu2*vu + vu*AbsSqr(Mu) - 0.5*vd*BMu - 0.5*vd*Conj(BMu) +
      0.075*Cube(vu)*Sqr(g1) + 0.125*Cube(vu)*Sqr(g2) - 0.075*vu*Sqr(g1)*Sqr(vd)
      - 0.125*vu*Sqr(g2)*Sqr(vd));

   return result;
}



std::complex<double> CLASSNAME::CpSveLUSdconjSveLconjUSd(int gO1, int gO2) const
{
   const std::complex<double> result = 0.05*(2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*Sqr(g1) + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*
      (Sqr(g1) + 5*Sqr(g2)));

   return result;
}

std::complex<double> CLASSNAME::CpSvmLUSdconjSvmLconjUSd(int gO1, int gO2) const
{
   const std::complex<double> result = 0.05*(2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*Sqr(g1) + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*
      (Sqr(g1) + 5*Sqr(g2)));

   return result;
}

std::complex<double> CLASSNAME::CpSvtLUSdconjSvtLconjUSd(int gO1, int gO2) const
{
   const std::complex<double> result = 0.05*(2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*Sqr(g1) + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*
      (Sqr(g1) + 5*Sqr(g2)));

   return result;
}

std::complex<double> CLASSNAME::CpUSdconjUSdVZVZ(int gO1, int gO2) const
{
   const std::complex<double> result = 0.03333333333333333*(KroneckerDelta(0,
      gO1)*KroneckerDelta(0,gO2)*(g1*Sin(ThetaW())*(7.745966692414834*g2*Cos(
      ThetaW()) + g1*Sin(ThetaW())) + 15*Sqr(g2)*Sqr(Cos(ThetaW()))) + 4*
      KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2)*Sqr(g1)*Sqr(Sin(ThetaW())));

   return result;
}

double CLASSNAME::CpUSdconjUSdconjVWmVWm(int gO1, int gO2) const
{
   const double result = 0.5*KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*Sqr(g2
      );

   return result;
}

std::complex<double> CLASSNAME::CpAhAhUSdconjUSd(int gI1, int gI2, int gO1, int gO2) const
{
   const std::complex<double> result = 0.05*(2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*((-10*AbsSqr(Yd(0,0)) + Sqr(g1))*ZA(gI1,0)*ZA(gI2,0) -
      Sqr(g1)*ZA(gI1,1)*ZA(gI2,1)) + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*
      ((-20*AbsSqr(Yd(0,0)) + Sqr(g1) + 5*Sqr(g2))*ZA(gI1,0)*ZA(gI2,0) - (Sqr(g1)
      + 5*Sqr(g2))*ZA(gI1,1)*ZA(gI2,1)));

   return result;
}

std::complex<double> CLASSNAME::CphhhhUSdconjUSd(int gI1, int gI2, int gO1, int gO2) const
{
   const std::complex<double> result = 0.05*(2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*((-10*AbsSqr(Yd(0,0)) + Sqr(g1))*ZH(gI1,0)*ZH(gI2,0) -
      Sqr(g1)*ZH(gI1,1)*ZH(gI2,1)) + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*
      ((-20*AbsSqr(Yd(0,0)) + Sqr(g1) + 5*Sqr(g2))*ZH(gI1,0)*ZH(gI2,0) - (Sqr(g1)
      + 5*Sqr(g2))*ZH(gI1,1)*ZH(gI2,1)));

   return result;
}

std::complex<double> CLASSNAME::CpHpmUSdconjHpmconjUSd(int gI1, int gO1, int gI2, int gO2) const
{
   const std::complex<double> result = 0.05*(2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*((-10*AbsSqr(Yd(0,0)) + Sqr(g1))*ZP(gI1,0)*ZP(gI2,0) -
      Sqr(g1)*ZP(gI1,1)*ZP(gI2,1)) + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*
      ((Sqr(g1) - 5*Sqr(g2))*ZP(gI1,0)*ZP(gI2,0) - (20*AbsSqr(Yu(0,0)) + Sqr(g1) -
      5*Sqr(g2))*ZP(gI1,1)*ZP(gI2,1)));

   return result;
}

std::complex<double> CLASSNAME::CpUSdconjUSdconjSbSb(int gO1, int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(-2*Conj(ZB(gI2,1))*(30*Conj(Yd(2,2
      ))*KroneckerDelta(0,gO1)*KroneckerDelta(1,gO2)*Yd(0,0)*ZB(gI1,0) + (
      KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2) + 2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2))*Sqr(g1)*ZB(gI1,1)) - Conj(ZB(gI2,0))*(KroneckerDelta(
      0,gO1)*KroneckerDelta(0,gO2)*(Sqr(g1) + 15*Sqr(g2))*ZB(gI1,0) + 2*
      KroneckerDelta(1,gO1)*(KroneckerDelta(1,gO2)*Sqr(g1)*ZB(gI1,0) + 30*Conj(Yd(
      0,0))*KroneckerDelta(0,gO2)*Yd(2,2)*ZB(gI1,1))));

   return result;
}

std::complex<double> CLASSNAME::CpUSdconjUSdconjScSc(int gO1, int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(-(Conj(ZC(gI2,0))*(2*
      KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2)*Sqr(g1) + KroneckerDelta(0,gO1)*
      KroneckerDelta(0,gO2)*(Sqr(g1) - 15*Sqr(g2)))*ZC(gI1,0)) + 4*Conj(ZC(gI2,1))
      *(KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2) + 2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2))*Sqr(g1)*ZC(gI1,1));

   return result;
}

std::complex<double> CLASSNAME::CpUSdconjUSdconjSdSd(int gO1, int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = 0.03333333333333333*(-(Conj(ZD(gI2,1))*(
      8*KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2)*(Sqr(g1) + 5*Sqr(g3))*ZD(gI1,1
      ) + KroneckerDelta(0,gO1)*(KroneckerDelta(1,gO2)*(90*AbsSqr(Yd(0,0)) + Sqr(
      g1) - 40*Sqr(g3))*ZD(gI1,0) + 3*KroneckerDelta(0,gO2)*(10*AbsSqr(Yd(0,0)) +
      Sqr(g1))*ZD(gI1,1)))) - Conj(ZD(gI2,0))*(2*KroneckerDelta(0,gO1)*
      KroneckerDelta(0,gO2)*(Sqr(g1) + 15*Sqr(g2) + 20*Sqr(g3))*ZD(gI1,0) +
      KroneckerDelta(1,gO1)*(3*KroneckerDelta(1,gO2)*(10*AbsSqr(Yd(0,0)) + Sqr(g1)
      )*ZD(gI1,0) + KroneckerDelta(0,gO2)*(90*AbsSqr(Yd(0,0)) + Sqr(g1) - 40*Sqr(
      g3))*ZD(gI1,1))));

   return result;
}

std::complex<double> CLASSNAME::CpUSdconjUSdconjSsSs(int gO1, int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(-2*Conj(ZS(gI2,1))*(30*Conj(Yd(1,1
      ))*KroneckerDelta(0,gO1)*KroneckerDelta(1,gO2)*Yd(0,0)*ZS(gI1,0) + (
      KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2) + 2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2))*Sqr(g1)*ZS(gI1,1)) - Conj(ZS(gI2,0))*(KroneckerDelta(
      0,gO1)*KroneckerDelta(0,gO2)*(Sqr(g1) + 15*Sqr(g2))*ZS(gI1,0) + 2*
      KroneckerDelta(1,gO1)*(KroneckerDelta(1,gO2)*Sqr(g1)*ZS(gI1,0) + 30*Conj(Yd(
      0,0))*KroneckerDelta(0,gO2)*Yd(1,1)*ZS(gI1,1))));

   return result;
}

std::complex<double> CLASSNAME::CpUSdconjUSdconjStSt(int gO1, int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(-(Conj(ZT(gI2,0))*(2*
      KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2)*Sqr(g1) + KroneckerDelta(0,gO1)*
      KroneckerDelta(0,gO2)*(Sqr(g1) - 15*Sqr(g2)))*ZT(gI1,0)) + 4*Conj(ZT(gI2,1))
      *(KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2) + 2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2))*Sqr(g1)*ZT(gI1,1));

   return result;
}

std::complex<double> CLASSNAME::CpUSdconjUSdconjSuSu(int gO1, int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(-(Conj(ZU(gI2,0))*(2*
      KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2)*(10*AbsSqr(Yd(0,0)) + Sqr(g1)) +
      KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*(Sqr(g1) - 5*Sqr(g2)))*ZU(gI1,0
      )) + 4*Conj(ZU(gI2,1))*(2*KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2)*Sqr(g1
      ) + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*(-5*AbsSqr(Yu(0,0)) + Sqr(g1
      )))*ZU(gI1,1));

   return result;
}

std::complex<double> CLASSNAME::CpUSdSeconjUSdconjSe(int gO1, int gI1, int gO2, int gI2) const
{
   const std::complex<double> result = 0.05*(-2*Conj(ZE(gI1,1))*(10*Conj(Ye(0,0
      ))*KroneckerDelta(0,gO1)*KroneckerDelta(1,gO2)*Yd(0,0)*ZE(gI2,0) + (
      KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2) + 2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2))*Sqr(g1)*ZE(gI2,1)) + Conj(ZE(gI1,0))*(KroneckerDelta(
      0,gO1)*KroneckerDelta(0,gO2)*(Sqr(g1) - 5*Sqr(g2))*ZE(gI2,0) + 2*
      KroneckerDelta(1,gO1)*(KroneckerDelta(1,gO2)*Sqr(g1)*ZE(gI2,0) - 10*Conj(Yd(
      0,0))*KroneckerDelta(0,gO2)*Ye(0,0)*ZE(gI2,1))));

   return result;
}

std::complex<double> CLASSNAME::CpUSdSmconjUSdconjSm(int gO1, int gI1, int gO2, int gI2) const
{
   const std::complex<double> result = 0.05*(-2*Conj(ZM(gI1,1))*(10*Conj(Ye(1,1
      ))*KroneckerDelta(0,gO1)*KroneckerDelta(1,gO2)*Yd(0,0)*ZM(gI2,0) + (
      KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2) + 2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2))*Sqr(g1)*ZM(gI2,1)) + Conj(ZM(gI1,0))*(KroneckerDelta(
      0,gO1)*KroneckerDelta(0,gO2)*(Sqr(g1) - 5*Sqr(g2))*ZM(gI2,0) + 2*
      KroneckerDelta(1,gO1)*(KroneckerDelta(1,gO2)*Sqr(g1)*ZM(gI2,0) - 10*Conj(Yd(
      0,0))*KroneckerDelta(0,gO2)*Ye(1,1)*ZM(gI2,1))));

   return result;
}

std::complex<double> CLASSNAME::CpUSdStauconjUSdconjStau(int gO1, int gI1, int gO2, int gI2) const
{
   const std::complex<double> result = 0.05*(-2*Conj(ZTau(gI1,1))*(10*Conj(Ye(2
      ,2))*KroneckerDelta(0,gO1)*KroneckerDelta(1,gO2)*Yd(0,0)*ZTau(gI2,0) + (
      KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2) + 2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2))*Sqr(g1)*ZTau(gI2,1)) + Conj(ZTau(gI1,0))*(
      KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*(Sqr(g1) - 5*Sqr(g2))*ZTau(gI2,0
      ) + 2*KroneckerDelta(1,gO1)*(KroneckerDelta(1,gO2)*Sqr(g1)*ZTau(gI2,0) - 10*
      Conj(Yd(0,0))*KroneckerDelta(0,gO2)*Ye(2,2)*ZTau(gI2,1))));

   return result;
}

std::complex<double> CLASSNAME::CpAhSdconjUSd(int gI2, int gI1, int gO2) const
{
   const std::complex<double> result = std::complex<double>(0.,
      0.7071067811865475)*(Conj(ZD(gI1,1))*KroneckerDelta(0,gO2)*(Conj(TYd(0,0))*
      ZA(gI2,0) + Conj(Yd(0,0))*Mu*ZA(gI2,1)) - Conj(ZD(gI1,0))*KroneckerDelta(1,
      gO2)*(Conj(Mu)*Yd(0,0)*ZA(gI2,1) + ZA(gI2,0)*TYd(0,0)));

   return result;
}

std::complex<double> CLASSNAME::CphhSdconjUSd(int gI2, int gI1, int gO2) const
{
   const std::complex<double> result = 0.05*(-2*Conj(ZD(gI1,1))*(
      7.0710678118654755*Conj(TYd(0,0))*KroneckerDelta(0,gO2)*ZH(gI2,0) -
      7.0710678118654755*Conj(Yd(0,0))*KroneckerDelta(0,gO2)*Mu*ZH(gI2,1) +
      KroneckerDelta(1,gO2)*(-(vd*(-10*AbsSqr(Yd(0,0)) + Sqr(g1))*ZH(gI2,0)) + vu*
      Sqr(g1)*ZH(gI2,1))) + Conj(ZD(gI1,0))*(KroneckerDelta(0,gO2)*(vd*(-20*AbsSqr
      (Yd(0,0)) + Sqr(g1) + 5*Sqr(g2))*ZH(gI2,0) - vu*(Sqr(g1) + 5*Sqr(g2))*ZH(gI2
      ,1)) + 14.142135623730951*KroneckerDelta(1,gO2)*(Conj(Mu)*Yd(0,0)*ZH(gI2,1)
      - ZH(gI2,0)*TYd(0,0))));

   return result;
}

std::complex<double> CLASSNAME::CpHpmSuconjUSd(int gI2, int gI1, int gO2) const
{
   const std::complex<double> result = 0.5*Conj(ZU(gI1,1))*(2*Conj(TYu(0,0))*
      KroneckerDelta(0,gO2)*ZP(gI2,1) + Conj(Yu(0,0))*(2*KroneckerDelta(0,gO2)*Mu*
      ZP(gI2,0) + 1.4142135623730951*KroneckerDelta(1,gO2)*Yd(0,0)*(vu*ZP(gI2,0) +
      vd*ZP(gI2,1)))) - 0.25*Conj(ZU(gI1,0))*(1.4142135623730951*KroneckerDelta(0
      ,gO2)*(vd*(-2*AbsSqr(Yd(0,0)) + Sqr(g2))*ZP(gI2,0) + vu*(-2*AbsSqr(Yu(0,0))
      + Sqr(g2))*ZP(gI2,1)) - 4*KroneckerDelta(1,gO2)*(Conj(Mu)*Yd(0,0)*ZP(gI2,1)
      + ZP(gI2,0)*TYd(0,0)));

   return result;
}

std::complex<double> CLASSNAME::CpSdconjUSdVG(int gI2, int gO2) const
{
   const std::complex<double> result = IF(gI2 < 2,g3*Conj(ZD(gI2,gO2)),0);

   return result;
}

std::complex<double> CLASSNAME::CpSdconjUSdVP(int gI2, int gO2) const
{
   const std::complex<double> result = 0.03333333333333333*(-7.745966692414834*
      g1*Conj(ZD(gI2,1))*Cos(ThetaW())*KroneckerDelta(1,gO2) + Conj(ZD(gI2,0))*
      KroneckerDelta(0,gO2)*(3.872983346207417*g1*Cos(ThetaW()) - 15*g2*Sin(ThetaW
      ())));

   return result;
}

std::complex<double> CLASSNAME::CpSdconjUSdVZ(int gI2, int gO2) const
{
   const std::complex<double> result = 0.2581988897471611*g1*Conj(ZD(gI2,1))*
      KroneckerDelta(1,gO2)*Sin(ThetaW()) - 0.03333333333333333*Conj(ZD(gI2,0))*
      KroneckerDelta(0,gO2)*(15*g2*Cos(ThetaW()) + 3.872983346207417*g1*Sin(ThetaW
      ()));

   return result;
}

std::complex<double> CLASSNAME::CpSuconjUSdVWm(int gI2, int gO2) const
{
   const std::complex<double> result = 0.7071067811865475*g2*Conj(ZU(gI2,0))*
      KroneckerDelta(0,gO2);

   return result;
}

std::complex<double> CLASSNAME::CpFuChaconjUSdPR(int gI2, int gO2) const
{
   const std::complex<double> result = Conj(Yu(0,0))*KroneckerDelta(0,gO2)*UP(
      gI2,1);

   return result;
}

std::complex<double> CLASSNAME::CpFuChaconjUSdPL(int gI2, int gO1) const
{
   const std::complex<double> result = -(g2*Conj(UM(gI2,0))*KroneckerDelta(0,
      gO1)) + Conj(UM(gI2,1))*KroneckerDelta(1,gO1)*Yd(0,0);

   return result;
}

std::complex<double> CLASSNAME::CpChiFdconjUSdPR(int gI2, int gO2) const
{
   const std::complex<double> result = -0.3651483716701107*g1*KroneckerDelta(1,
      gO2)*ZN(gI2,0) - Conj(Yd(0,0))*KroneckerDelta(0,gO2)*ZN(gI2,2);

   return result;
}

std::complex<double> CLASSNAME::CpChiFdconjUSdPL(int gI2, int gO1) const
{
   const std::complex<double> result = -0.18257418583505536*g1*Conj(ZN(gI2,0))*
      KroneckerDelta(0,gO1) + 0.7071067811865475*g2*Conj(ZN(gI2,1))*KroneckerDelta
      (0,gO1) - Conj(ZN(gI2,2))*KroneckerDelta(1,gO1)*Yd(0,0);

   return result;
}

std::complex<double> CLASSNAME::CpGluFdconjUSdPR(int gO2) const
{
   const std::complex<double> result = 1.4142135623730951*g3*Conj(PhaseGlu)*
      KroneckerDelta(1,gO2);

   return result;
}

std::complex<double> CLASSNAME::CpGluFdconjUSdPL(int gO1) const
{
   const std::complex<double> result = -1.4142135623730951*g3*PhaseGlu*
      KroneckerDelta(0,gO1);

   return result;
}

std::complex<double> CLASSNAME::CpSveLUSuconjSveLconjUSu(int gO1, int gO2) const
{
   const std::complex<double> result = 0.05*(-4*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*Sqr(g1) + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*
      (Sqr(g1) - 5*Sqr(g2)));

   return result;
}

std::complex<double> CLASSNAME::CpSvmLUSuconjSvmLconjUSu(int gO1, int gO2) const
{
   const std::complex<double> result = 0.05*(-4*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*Sqr(g1) + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*
      (Sqr(g1) - 5*Sqr(g2)));

   return result;
}

std::complex<double> CLASSNAME::CpSvtLUSuconjSvtLconjUSu(int gO1, int gO2) const
{
   const std::complex<double> result = 0.05*(-4*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*Sqr(g1) + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*
      (Sqr(g1) - 5*Sqr(g2)));

   return result;
}

std::complex<double> CLASSNAME::CpUSuconjUSuVZVZ(int gO1, int gO2) const
{
   const std::complex<double> result = 0.03333333333333333*(16*KroneckerDelta(1
      ,gO1)*KroneckerDelta(1,gO2)*Sqr(g1)*Sqr(Sin(ThetaW())) + KroneckerDelta(0,
      gO1)*KroneckerDelta(0,gO2)*(-7.745966692414834*g1*g2*Cos(ThetaW())*Sin(
      ThetaW()) + 15*Sqr(g2)*Sqr(Cos(ThetaW())) + Sqr(g1)*Sqr(Sin(ThetaW()))));

   return result;
}

double CLASSNAME::CpUSuconjUSuconjVWmVWm(int gO1, int gO2) const
{
   const double result = 0.5*KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*Sqr(g2
      );

   return result;
}

std::complex<double> CLASSNAME::CpAhAhUSuconjUSu(int gI1, int gI2, int gO1, int gO2) const
{
   const std::complex<double> result = 0.05*(-4*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*(Sqr(g1)*ZA(gI1,0)*ZA(gI2,0) - (-5*AbsSqr(Yu(0,0)) +
      Sqr(g1))*ZA(gI1,1)*ZA(gI2,1)) + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*
      ((Sqr(g1) - 5*Sqr(g2))*ZA(gI1,0)*ZA(gI2,0) - (20*AbsSqr(Yu(0,0)) + Sqr(g1) -
      5*Sqr(g2))*ZA(gI1,1)*ZA(gI2,1)));

   return result;
}

std::complex<double> CLASSNAME::CphhhhUSuconjUSu(int gI1, int gI2, int gO1, int gO2) const
{
   const std::complex<double> result = 0.05*(-4*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*(Sqr(g1)*ZH(gI1,0)*ZH(gI2,0) - (-5*AbsSqr(Yu(0,0)) +
      Sqr(g1))*ZH(gI1,1)*ZH(gI2,1)) + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*
      ((Sqr(g1) - 5*Sqr(g2))*ZH(gI1,0)*ZH(gI2,0) - (20*AbsSqr(Yu(0,0)) + Sqr(g1) -
      5*Sqr(g2))*ZH(gI1,1)*ZH(gI2,1)));

   return result;
}

std::complex<double> CLASSNAME::CpHpmUSuconjHpmconjUSu(int gI1, int gO1, int gI2, int gO2) const
{
   const std::complex<double> result = 0.05*(-4*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*(Sqr(g1)*ZP(gI1,0)*ZP(gI2,0) - (-5*AbsSqr(Yu(0,0)) +
      Sqr(g1))*ZP(gI1,1)*ZP(gI2,1)) + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*
      ((-20*AbsSqr(Yd(0,0)) + Sqr(g1) + 5*Sqr(g2))*ZP(gI1,0)*ZP(gI2,0) - (Sqr(g1)
      + 5*Sqr(g2))*ZP(gI1,1)*ZP(gI2,1)));

   return result;
}

std::complex<double> CLASSNAME::CpSeUSuconjSeconjUSu(int gI1, int gO1, int gI2, int gO2) const
{
   const std::complex<double> result = 0.05*(Conj(ZE(gI1,0))*(-4*KroneckerDelta
      (1,gO1)*KroneckerDelta(1,gO2)*Sqr(g1) + KroneckerDelta(0,gO1)*KroneckerDelta
      (0,gO2)*(Sqr(g1) + 5*Sqr(g2)))*ZE(gI2,0) - 2*Conj(ZE(gI1,1))*(KroneckerDelta
      (0,gO1)*KroneckerDelta(0,gO2) - 4*KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2
      ))*Sqr(g1)*ZE(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpSmUSuconjSmconjUSu(int gI1, int gO1, int gI2, int gO2) const
{
   const std::complex<double> result = 0.05*(Conj(ZM(gI1,0))*(-4*KroneckerDelta
      (1,gO1)*KroneckerDelta(1,gO2)*Sqr(g1) + KroneckerDelta(0,gO1)*KroneckerDelta
      (0,gO2)*(Sqr(g1) + 5*Sqr(g2)))*ZM(gI2,0) - 2*Conj(ZM(gI1,1))*(KroneckerDelta
      (0,gO1)*KroneckerDelta(0,gO2) - 4*KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2
      ))*Sqr(g1)*ZM(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpStauUSuconjStauconjUSu(int gI1, int gO1, int gI2, int gO2) const
{
   const std::complex<double> result = 0.05*(Conj(ZTau(gI1,0))*(-4*
      KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2)*Sqr(g1) + KroneckerDelta(0,gO1)*
      KroneckerDelta(0,gO2)*(Sqr(g1) + 5*Sqr(g2)))*ZTau(gI2,0) - 2*Conj(ZTau(gI1,1
      ))*(KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2) - 4*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2))*Sqr(g1)*ZTau(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpUSuconjUSuconjSbSb(int gO1, int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZB(gI2,0))*(4*KroneckerDelta(
      1,gO1)*KroneckerDelta(1,gO2)*Sqr(g1) - KroneckerDelta(0,gO1)*KroneckerDelta(
      0,gO2)*(Sqr(g1) - 15*Sqr(g2)))*ZB(gI1,0) - 2*Conj(ZB(gI2,1))*(KroneckerDelta
      (0,gO1)*KroneckerDelta(0,gO2) - 4*KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2
      ))*Sqr(g1)*ZB(gI1,1));

   return result;
}

std::complex<double> CLASSNAME::CpUSuconjUSuconjScSc(int gO1, int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(4*Conj(ZC(gI2,1))*(-15*Conj(Yu(1,1
      ))*KroneckerDelta(0,gO1)*KroneckerDelta(1,gO2)*Yu(0,0)*ZC(gI1,0) + (
      KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2) - 4*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2))*Sqr(g1)*ZC(gI1,1)) - Conj(ZC(gI2,0))*(KroneckerDelta(
      0,gO1)*KroneckerDelta(0,gO2)*(Sqr(g1) + 15*Sqr(g2))*ZC(gI1,0) - 4*
      KroneckerDelta(1,gO1)*(KroneckerDelta(1,gO2)*Sqr(g1)*ZC(gI1,0) - 15*Conj(Yu(
      0,0))*KroneckerDelta(0,gO2)*Yu(1,1)*ZC(gI1,1))));

   return result;
}

std::complex<double> CLASSNAME::CpUSuconjUSuconjSdSd(int gO1, int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZD(gI2,0))*(4*KroneckerDelta(
      1,gO1)*KroneckerDelta(1,gO2)*(-5*AbsSqr(Yu(0,0)) + Sqr(g1)) - KroneckerDelta
      (0,gO1)*KroneckerDelta(0,gO2)*(Sqr(g1) - 5*Sqr(g2)))*ZD(gI1,0) - 2*Conj(ZD(
      gI2,1))*(-4*KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2)*Sqr(g1) +
      KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*(10*AbsSqr(Yd(0,0)) + Sqr(g1)))*
      ZD(gI1,1));

   return result;
}

std::complex<double> CLASSNAME::CpUSuconjUSuconjSsSs(int gO1, int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZS(gI2,0))*(4*KroneckerDelta(
      1,gO1)*KroneckerDelta(1,gO2)*Sqr(g1) - KroneckerDelta(0,gO1)*KroneckerDelta(
      0,gO2)*(Sqr(g1) - 15*Sqr(g2)))*ZS(gI1,0) - 2*Conj(ZS(gI2,1))*(KroneckerDelta
      (0,gO1)*KroneckerDelta(0,gO2) - 4*KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2
      ))*Sqr(g1)*ZS(gI1,1));

   return result;
}

std::complex<double> CLASSNAME::CpUSuconjUSuconjStSt(int gO1, int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(4*Conj(ZT(gI2,1))*(-15*Conj(Yu(2,2
      ))*KroneckerDelta(0,gO1)*KroneckerDelta(1,gO2)*Yu(0,0)*ZT(gI1,0) + (
      KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2) - 4*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2))*Sqr(g1)*ZT(gI1,1)) - Conj(ZT(gI2,0))*(KroneckerDelta(
      0,gO1)*KroneckerDelta(0,gO2)*(Sqr(g1) + 15*Sqr(g2))*ZT(gI1,0) - 4*
      KroneckerDelta(1,gO1)*(KroneckerDelta(1,gO2)*Sqr(g1)*ZT(gI1,0) - 15*Conj(Yu(
      0,0))*KroneckerDelta(0,gO2)*Yu(2,2)*ZT(gI1,1))));

   return result;
}

std::complex<double> CLASSNAME::CpUSuconjUSuconjSuSu(int gO1, int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = 0.06666666666666667*(Conj(ZU(gI2,1))*(-4
      *KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2)*(4*Sqr(g1) + 5*Sqr(g3))*ZU(gI1,
      1) + KroneckerDelta(0,gO1)*(KroneckerDelta(1,gO2)*(-45*AbsSqr(Yu(0,0)) + Sqr
      (g1) + 20*Sqr(g3))*ZU(gI1,0) + 3*KroneckerDelta(0,gO2)*(-5*AbsSqr(Yu(0,0)) +
      Sqr(g1))*ZU(gI1,1))) - Conj(ZU(gI2,0))*(KroneckerDelta(0,gO1)*
      KroneckerDelta(0,gO2)*(Sqr(g1) + 15*Sqr(g2) + 20*Sqr(g3))*ZU(gI1,0) -
      KroneckerDelta(1,gO1)*(3*KroneckerDelta(1,gO2)*(-5*AbsSqr(Yu(0,0)) + Sqr(g1)
      )*ZU(gI1,0) + KroneckerDelta(0,gO2)*(-45*AbsSqr(Yu(0,0)) + Sqr(g1) + 20*Sqr(
      g3))*ZU(gI1,1))));

   return result;
}

std::complex<double> CLASSNAME::CpAhSuconjUSu(int gI2, int gI1, int gO2) const
{
   const std::complex<double> result = std::complex<double>(0.,
      0.7071067811865475)*(Conj(Yu(0,0))*Conj(ZU(gI1,1))*KroneckerDelta(0,gO2)*Mu*
      ZA(gI2,0) - Conj(Mu)*Conj(ZU(gI1,0))*KroneckerDelta(1,gO2)*Yu(0,0)*ZA(gI2,0)
      + ZA(gI2,1)*(Conj(ZU(gI1,1))*Conj(TYu(0,0))*KroneckerDelta(0,gO2) - Conj(ZU
      (gI1,0))*KroneckerDelta(1,gO2)*TYu(0,0)));

   return result;
}

std::complex<double> CLASSNAME::CphhSuconjUSu(int gI2, int gI1, int gO2) const
{
   const std::complex<double> result = 0.05*(2*Conj(ZU(gI1,1))*(
      -7.0710678118654755*Conj(TYu(0,0))*KroneckerDelta(0,gO2)*ZH(gI2,1) + 2*
      KroneckerDelta(1,gO2)*Sqr(g1)*(-(vd*ZH(gI2,0)) + vu*ZH(gI2,1)) + 5*Conj(Yu(0
      ,0))*(1.4142135623730951*KroneckerDelta(0,gO2)*Mu*ZH(gI2,0) - 2*vu*
      KroneckerDelta(1,gO2)*Yu(0,0)*ZH(gI2,1))) + Conj(ZU(gI1,0))*(KroneckerDelta(
      0,gO2)*(vd*(Sqr(g1) - 5*Sqr(g2))*ZH(gI2,0) - vu*(20*AbsSqr(Yu(0,0)) + Sqr(g1
      ) - 5*Sqr(g2))*ZH(gI2,1)) + 14.142135623730951*KroneckerDelta(1,gO2)*(Conj(
      Mu)*Yu(0,0)*ZH(gI2,0) - ZH(gI2,1)*TYu(0,0))));

   return result;
}

std::complex<double> CLASSNAME::CpSdconjHpmconjUSu(int gI2, int gI1, int gO2) const
{
   const std::complex<double> result = 0.5*Conj(ZD(gI2,1))*(2*Conj(TYd(0,0))*
      KroneckerDelta(0,gO2)*ZP(gI1,0) + Conj(Yd(0,0))*(2*KroneckerDelta(0,gO2)*Mu*
      ZP(gI1,1) + 1.4142135623730951*KroneckerDelta(1,gO2)*Yu(0,0)*(vu*ZP(gI1,0) +
      vd*ZP(gI1,1)))) - 0.25*Conj(ZD(gI2,0))*(1.4142135623730951*KroneckerDelta(0
      ,gO2)*(vd*(-2*AbsSqr(Yd(0,0)) + Sqr(g2))*ZP(gI1,0) + vu*(-2*AbsSqr(Yu(0,0))
      + Sqr(g2))*ZP(gI1,1)) - 4*KroneckerDelta(1,gO2)*(Conj(Mu)*Yu(0,0)*ZP(gI1,0)
      + ZP(gI1,1)*TYu(0,0)));

   return result;
}

std::complex<double> CLASSNAME::CpbarChaFdconjUSuPR(int gI1, int gO2) const
{
   const std::complex<double> result = Conj(Yd(0,0))*KroneckerDelta(0,gO2)*UM(
      gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpbarChaFdconjUSuPL(int gI1, int gO1) const
{
   const std::complex<double> result = -(g2*Conj(UP(gI1,0))*KroneckerDelta(0,
      gO1)) + Conj(UP(gI1,1))*KroneckerDelta(1,gO1)*Yu(0,0);

   return result;
}

std::complex<double> CLASSNAME::CpSdconjUSuconjVWm(int gI2, int gO2) const
{
   const std::complex<double> result = 0.7071067811865475*g2*Conj(ZD(gI2,0))*
      KroneckerDelta(0,gO2);

   return result;
}

std::complex<double> CLASSNAME::CpSuconjUSuVG(int gI2, int gO2) const
{
   const std::complex<double> result = IF(gI2 < 2,g3*Conj(ZU(gI2,gO2)),0);

   return result;
}

std::complex<double> CLASSNAME::CpSuconjUSuVP(int gI2, int gO2) const
{
   const std::complex<double> result = 0.03333333333333333*(15.491933384829668*
      g1*Conj(ZU(gI2,1))*Cos(ThetaW())*KroneckerDelta(1,gO2) + Conj(ZU(gI2,0))*
      KroneckerDelta(0,gO2)*(3.872983346207417*g1*Cos(ThetaW()) + 15*g2*Sin(ThetaW
      ())));

   return result;
}

std::complex<double> CLASSNAME::CpSuconjUSuVZ(int gI2, int gO2) const
{
   const std::complex<double> result = 0.03333333333333333*(-15.491933384829668
      *g1*Conj(ZU(gI2,1))*KroneckerDelta(1,gO2)*Sin(ThetaW()) + Conj(ZU(gI2,0))*
      KroneckerDelta(0,gO2)*(15*g2*Cos(ThetaW()) - 3.872983346207417*g1*Sin(ThetaW
      ())));

   return result;
}

std::complex<double> CLASSNAME::CpChiFuconjUSuPR(int gI2, int gO2) const
{
   const std::complex<double> result = 0.7302967433402214*g1*KroneckerDelta(1,
      gO2)*ZN(gI2,0) - Conj(Yu(0,0))*KroneckerDelta(0,gO2)*ZN(gI2,3);

   return result;
}

std::complex<double> CLASSNAME::CpChiFuconjUSuPL(int gI2, int gO1) const
{
   const std::complex<double> result = -0.18257418583505536*g1*Conj(ZN(gI2,0))*
      KroneckerDelta(0,gO1) - 0.7071067811865475*g2*Conj(ZN(gI2,1))*KroneckerDelta
      (0,gO1) - Conj(ZN(gI2,3))*KroneckerDelta(1,gO1)*Yu(0,0);

   return result;
}

std::complex<double> CLASSNAME::CpGluFuconjUSuPR(int gO2) const
{
   const std::complex<double> result = 1.4142135623730951*g3*Conj(PhaseGlu)*
      KroneckerDelta(1,gO2);

   return result;
}

std::complex<double> CLASSNAME::CpGluFuconjUSuPL(int gO1) const
{
   const std::complex<double> result = -1.4142135623730951*g3*PhaseGlu*
      KroneckerDelta(0,gO1);

   return result;
}

std::complex<double> CLASSNAME::CpSveLUSeconjSveLconjUSe(int gO1, int gO2) const
{
   const std::complex<double> result = 0.05*(2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*(-10*AbsSqr(Ye(0,0)) + 3*Sqr(g1)) - KroneckerDelta(0,
      gO1)*KroneckerDelta(0,gO2)*(3*Sqr(g1) + 5*Sqr(g2)));

   return result;
}

std::complex<double> CLASSNAME::CpSvmLUSeconjSvmLconjUSe(int gO1, int gO2) const
{
   const std::complex<double> result = 0.05*(6*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*Sqr(g1) + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*
      (-3*Sqr(g1) + 5*Sqr(g2)));

   return result;
}

std::complex<double> CLASSNAME::CpSvtLUSeconjSvtLconjUSe(int gO1, int gO2) const
{
   const std::complex<double> result = 0.05*(6*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*Sqr(g1) + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*
      (-3*Sqr(g1) + 5*Sqr(g2)));

   return result;
}

std::complex<double> CLASSNAME::CpUSeconjUSeVZVZ(int gO1, int gO2) const
{
   const std::complex<double> result = 0.1*(12*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*Sqr(g1)*Sqr(Sin(ThetaW())) + KroneckerDelta(0,gO1)*
      KroneckerDelta(0,gO2)*(-7.745966692414834*g1*g2*Cos(ThetaW())*Sin(ThetaW())
      + 5*Sqr(g2)*Sqr(Cos(ThetaW())) + 3*Sqr(g1)*Sqr(Sin(ThetaW()))));

   return result;
}

double CLASSNAME::CpUSeconjUSeconjVWmVWm(int gO1, int gO2) const
{
   const double result = 0.5*KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*Sqr(g2
      );

   return result;
}

double CLASSNAME::CpSveLconjUSeVWm(int gO2) const
{
   const double result = 0.7071067811865475*g2*KroneckerDelta(0,gO2);

   return result;
}

std::complex<double> CLASSNAME::CpAhAhUSeconjUSe(int gI1, int gI2, int gO1, int gO2) const
{
   const std::complex<double> result = 0.05*(2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*((-10*AbsSqr(Ye(0,0)) + 3*Sqr(g1))*ZA(gI1,0)*ZA(gI2,0)
      - 3*Sqr(g1)*ZA(gI1,1)*ZA(gI2,1)) + KroneckerDelta(0,gO1)*KroneckerDelta(0,
      gO2)*((-20*AbsSqr(Ye(0,0)) - 3*Sqr(g1) + 5*Sqr(g2))*ZA(gI1,0)*ZA(gI2,0) + (3
      *Sqr(g1) - 5*Sqr(g2))*ZA(gI1,1)*ZA(gI2,1)));

   return result;
}

std::complex<double> CLASSNAME::CphhhhUSeconjUSe(int gI1, int gI2, int gO1, int gO2) const
{
   const std::complex<double> result = 0.05*(2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*((-10*AbsSqr(Ye(0,0)) + 3*Sqr(g1))*ZH(gI1,0)*ZH(gI2,0)
      - 3*Sqr(g1)*ZH(gI1,1)*ZH(gI2,1)) + KroneckerDelta(0,gO1)*KroneckerDelta(0,
      gO2)*((-20*AbsSqr(Ye(0,0)) - 3*Sqr(g1) + 5*Sqr(g2))*ZH(gI1,0)*ZH(gI2,0) + (3
      *Sqr(g1) - 5*Sqr(g2))*ZH(gI1,1)*ZH(gI2,1)));

   return result;
}

std::complex<double> CLASSNAME::CpHpmUSeconjHpmconjUSe(int gI1, int gO1, int gI2, int gO2) const
{
   const std::complex<double> result = 0.05*(-(KroneckerDelta(0,gO1)*
      KroneckerDelta(0,gO2)*(3*Sqr(g1) + 5*Sqr(g2))*(ZP(gI1,0)*ZP(gI2,0) - ZP(gI1,
      1)*ZP(gI2,1))) + 2*KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2)*((-10*AbsSqr(
      Ye(0,0)) + 3*Sqr(g1))*ZP(gI1,0)*ZP(gI2,0) - 3*Sqr(g1)*ZP(gI1,1)*ZP(gI2,1)));

   return result;
}

std::complex<double> CLASSNAME::CpSbUSeconjSbconjUSe(int gI1, int gO1, int gI2, int gO2) const
{
   const std::complex<double> result = 0.05*(2*Conj(ZB(gI1,1))*(-10*Conj(Yd(2,2
      ))*KroneckerDelta(0,gO1)*KroneckerDelta(1,gO2)*Ye(0,0)*ZB(gI2,0) + (
      KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2) - 2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2))*Sqr(g1)*ZB(gI2,1)) + Conj(ZB(gI1,0))*(KroneckerDelta(
      0,gO1)*KroneckerDelta(0,gO2)*(Sqr(g1) - 5*Sqr(g2))*ZB(gI2,0) - 2*
      KroneckerDelta(1,gO1)*(KroneckerDelta(1,gO2)*Sqr(g1)*ZB(gI2,0) + 10*Conj(Ye(
      0,0))*KroneckerDelta(0,gO2)*Yd(2,2)*ZB(gI2,1))));

   return result;
}

std::complex<double> CLASSNAME::CpScUSeconjScconjUSe(int gI1, int gO1, int gI2, int gO2) const
{
   const std::complex<double> result = 0.05*(Conj(ZC(gI1,0))*(-2*KroneckerDelta
      (1,gO1)*KroneckerDelta(1,gO2)*Sqr(g1) + KroneckerDelta(0,gO1)*KroneckerDelta
      (0,gO2)*(Sqr(g1) + 5*Sqr(g2)))*ZC(gI2,0) - 4*Conj(ZC(gI1,1))*(KroneckerDelta
      (0,gO1)*KroneckerDelta(0,gO2) - 2*KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2
      ))*Sqr(g1)*ZC(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpSdUSeconjSdconjUSe(int gI1, int gO1, int gI2, int gO2) const
{
   const std::complex<double> result = 0.05*(2*Conj(ZD(gI1,1))*(-10*Conj(Yd(0,0
      ))*KroneckerDelta(0,gO1)*KroneckerDelta(1,gO2)*Ye(0,0)*ZD(gI2,0) + (
      KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2) - 2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2))*Sqr(g1)*ZD(gI2,1)) + Conj(ZD(gI1,0))*(KroneckerDelta(
      0,gO1)*KroneckerDelta(0,gO2)*(Sqr(g1) - 5*Sqr(g2))*ZD(gI2,0) - 2*
      KroneckerDelta(1,gO1)*(KroneckerDelta(1,gO2)*Sqr(g1)*ZD(gI2,0) + 10*Conj(Ye(
      0,0))*KroneckerDelta(0,gO2)*Yd(0,0)*ZD(gI2,1))));

   return result;
}

std::complex<double> CLASSNAME::CpSeUSeconjSeconjUSe(int gI1, int gO1, int gI2, int gO2) const
{
   const std::complex<double> result = 0.1*(Conj(ZE(gI1,1))*(-12*KroneckerDelta
      (1,gO1)*KroneckerDelta(1,gO2)*Sqr(g1)*ZE(gI2,1) + KroneckerDelta(0,gO1)*(-10
      *AbsSqr(Ye(0,0)) + 3*Sqr(g1))*(KroneckerDelta(1,gO2)*ZE(gI2,0) +
      KroneckerDelta(0,gO2)*ZE(gI2,1))) - Conj(ZE(gI1,0))*(KroneckerDelta(0,gO1)*
      KroneckerDelta(0,gO2)*(3*Sqr(g1) + 5*Sqr(g2))*ZE(gI2,0) - KroneckerDelta(1,
      gO1)*(-10*AbsSqr(Ye(0,0)) + 3*Sqr(g1))*(KroneckerDelta(1,gO2)*ZE(gI2,0) +
      KroneckerDelta(0,gO2)*ZE(gI2,1))));

   return result;
}

std::complex<double> CLASSNAME::CpUSeSmconjUSeconjSm(int gO1, int gI1, int gO2, int gI2) const
{
   const std::complex<double> result = 0.05*(-2*Conj(ZM(gI1,1))*(10*Conj(Ye(1,1
      ))*KroneckerDelta(0,gO1)*KroneckerDelta(1,gO2)*Ye(0,0)*ZM(gI2,0) - 3*(
      KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2) - 2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2))*Sqr(g1)*ZM(gI2,1)) - Conj(ZM(gI1,0))*(KroneckerDelta(
      0,gO1)*KroneckerDelta(0,gO2)*(3*Sqr(g1) + 5*Sqr(g2))*ZM(gI2,0) + 2*
      KroneckerDelta(1,gO1)*(-3*KroneckerDelta(1,gO2)*Sqr(g1)*ZM(gI2,0) + 10*Conj(
      Ye(0,0))*KroneckerDelta(0,gO2)*Ye(1,1)*ZM(gI2,1))));

   return result;
}

std::complex<double> CLASSNAME::CpUSeSsconjUSeconjSs(int gO1, int gI1, int gO2, int gI2) const
{
   const std::complex<double> result = 0.05*(2*Conj(ZS(gI1,1))*(-10*Conj(Yd(1,1
      ))*KroneckerDelta(0,gO1)*KroneckerDelta(1,gO2)*Ye(0,0)*ZS(gI2,0) + (
      KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2) - 2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2))*Sqr(g1)*ZS(gI2,1)) + Conj(ZS(gI1,0))*(KroneckerDelta(
      0,gO1)*KroneckerDelta(0,gO2)*(Sqr(g1) - 5*Sqr(g2))*ZS(gI2,0) - 2*
      KroneckerDelta(1,gO1)*(KroneckerDelta(1,gO2)*Sqr(g1)*ZS(gI2,0) + 10*Conj(Ye(
      0,0))*KroneckerDelta(0,gO2)*Yd(1,1)*ZS(gI2,1))));

   return result;
}

std::complex<double> CLASSNAME::CpUSeStconjUSeconjSt(int gO1, int gI1, int gO2, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZT(gI1,0))*(-2*KroneckerDelta
      (1,gO1)*KroneckerDelta(1,gO2)*Sqr(g1) + KroneckerDelta(0,gO1)*KroneckerDelta
      (0,gO2)*(Sqr(g1) + 5*Sqr(g2)))*ZT(gI2,0) - 4*Conj(ZT(gI1,1))*(KroneckerDelta
      (0,gO1)*KroneckerDelta(0,gO2) - 2*KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2
      ))*Sqr(g1)*ZT(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpUSeStauconjUSeconjStau(int gO1, int gI1, int gO2, int gI2) const
{
   const std::complex<double> result = 0.05*(-2*Conj(ZTau(gI1,1))*(10*Conj(Ye(2
      ,2))*KroneckerDelta(0,gO1)*KroneckerDelta(1,gO2)*Ye(0,0)*ZTau(gI2,0) - 3*(
      KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2) - 2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2))*Sqr(g1)*ZTau(gI2,1)) - Conj(ZTau(gI1,0))*(
      KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*(3*Sqr(g1) + 5*Sqr(g2))*ZTau(gI2
      ,0) + 2*KroneckerDelta(1,gO1)*(-3*KroneckerDelta(1,gO2)*Sqr(g1)*ZTau(gI2,0)
      + 10*Conj(Ye(0,0))*KroneckerDelta(0,gO2)*Ye(2,2)*ZTau(gI2,1))));

   return result;
}

std::complex<double> CLASSNAME::CpUSeSuconjUSeconjSu(int gO1, int gI1, int gO2, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZU(gI1,0))*(-2*KroneckerDelta
      (1,gO1)*KroneckerDelta(1,gO2)*Sqr(g1) + KroneckerDelta(0,gO1)*KroneckerDelta
      (0,gO2)*(Sqr(g1) + 5*Sqr(g2)))*ZU(gI2,0) - 4*Conj(ZU(gI1,1))*(KroneckerDelta
      (0,gO1)*KroneckerDelta(0,gO2) - 2*KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2
      ))*Sqr(g1)*ZU(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpAhSeconjUSe(int gI2, int gI1, int gO2) const
{
   const std::complex<double> result = std::complex<double>(0.,
      0.7071067811865475)*(Conj(ZE(gI1,1))*KroneckerDelta(0,gO2)*(Conj(TYe(0,0))*
      ZA(gI2,0) + Conj(Ye(0,0))*Mu*ZA(gI2,1)) - Conj(ZE(gI1,0))*KroneckerDelta(1,
      gO2)*(Conj(Mu)*Ye(0,0)*ZA(gI2,1) + ZA(gI2,0)*TYe(0,0)));

   return result;
}

std::complex<double> CLASSNAME::CphhSeconjUSe(int gI2, int gI1, int gO2) const
{
   const std::complex<double> result = 0.05*(-2*Conj(ZE(gI1,1))*(
      7.0710678118654755*Conj(TYe(0,0))*KroneckerDelta(0,gO2)*ZH(gI2,0) -
      7.0710678118654755*Conj(Ye(0,0))*KroneckerDelta(0,gO2)*Mu*ZH(gI2,1) +
      KroneckerDelta(1,gO2)*((10*vd*AbsSqr(Ye(0,0)) - 3*vd*Sqr(g1))*ZH(gI2,0) + 3*
      vu*Sqr(g1)*ZH(gI2,1))) + Conj(ZE(gI1,0))*(KroneckerDelta(0,gO2)*(vd*(-20*
      AbsSqr(Ye(0,0)) - 3*Sqr(g1) + 5*Sqr(g2))*ZH(gI2,0) + vu*(3*Sqr(g1) - 5*Sqr(
      g2))*ZH(gI2,1)) + 14.142135623730951*KroneckerDelta(1,gO2)*(Conj(Mu)*Ye(0,0)
      *ZH(gI2,1) - ZH(gI2,0)*TYe(0,0))));

   return result;
}

std::complex<double> CLASSNAME::CpSveLHpmconjUSe(int gI2, int gO2) const
{
   const std::complex<double> result = -0.35355339059327373*KroneckerDelta(0,
      gO2)*(vd*(-2*AbsSqr(Ye(0,0)) + Sqr(g2))*ZP(gI2,0) + vu*Sqr(g2)*ZP(gI2,1)) +
      KroneckerDelta(1,gO2)*(Conj(Mu)*Ye(0,0)*ZP(gI2,1) + ZP(gI2,0)*TYe(0,0));

   return result;
}

std::complex<double> CLASSNAME::CpSeconjUSeVP(int gI2, int gO2) const
{
   const std::complex<double> result = -0.7745966692414834*g1*Conj(ZE(gI2,1))*
      Cos(ThetaW())*KroneckerDelta(1,gO2) - 0.1*Conj(ZE(gI2,0))*KroneckerDelta(0,
      gO2)*(3.872983346207417*g1*Cos(ThetaW()) + 5*g2*Sin(ThetaW()));

   return result;
}

std::complex<double> CLASSNAME::CpSeconjUSeVZ(int gI2, int gO2) const
{
   const std::complex<double> result = 0.7745966692414834*g1*Conj(ZE(gI2,1))*
      KroneckerDelta(1,gO2)*Sin(ThetaW()) - 0.1*Conj(ZE(gI2,0))*KroneckerDelta(0,
      gO2)*(5*g2*Cos(ThetaW()) - 3.872983346207417*g1*Sin(ThetaW()));

   return result;
}

double CLASSNAME::CpFveChaconjUSePR(int , int ) const
{
   const double result = 0;

   return result;
}

std::complex<double> CLASSNAME::CpFveChaconjUSePL(int gI2, int gO1) const
{
   const std::complex<double> result = -(g2*Conj(UM(gI2,0))*KroneckerDelta(0,
      gO1)) + Conj(UM(gI2,1))*KroneckerDelta(1,gO1)*Ye(0,0);

   return result;
}

std::complex<double> CLASSNAME::CpChiFeconjUSePR(int gI2, int gO2) const
{
   const std::complex<double> result = -1.0954451150103321*g1*KroneckerDelta(1,
      gO2)*ZN(gI2,0) - Conj(Ye(0,0))*KroneckerDelta(0,gO2)*ZN(gI2,2);

   return result;
}

std::complex<double> CLASSNAME::CpChiFeconjUSePL(int gI2, int gO1) const
{
   const std::complex<double> result = 0.5477225575051661*g1*Conj(ZN(gI2,0))*
      KroneckerDelta(0,gO1) + 0.7071067811865475*g2*Conj(ZN(gI2,1))*KroneckerDelta
      (0,gO1) - Conj(ZN(gI2,2))*KroneckerDelta(1,gO1)*Ye(0,0);

   return result;
}

std::complex<double> CLASSNAME::CpSveLUSmconjSveLconjUSm(int gO1, int gO2) const
{
   const std::complex<double> result = 0.05*(6*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*Sqr(g1) + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*
      (-3*Sqr(g1) + 5*Sqr(g2)));

   return result;
}

std::complex<double> CLASSNAME::CpSvmLUSmconjSvmLconjUSm(int gO1, int gO2) const
{
   const std::complex<double> result = 0.05*(2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*(-10*AbsSqr(Ye(1,1)) + 3*Sqr(g1)) - KroneckerDelta(0,
      gO1)*KroneckerDelta(0,gO2)*(3*Sqr(g1) + 5*Sqr(g2)));

   return result;
}

std::complex<double> CLASSNAME::CpSvtLUSmconjSvtLconjUSm(int gO1, int gO2) const
{
   const std::complex<double> result = 0.05*(6*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*Sqr(g1) + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*
      (-3*Sqr(g1) + 5*Sqr(g2)));

   return result;
}

std::complex<double> CLASSNAME::CpUSmconjUSmVZVZ(int gO1, int gO2) const
{
   const std::complex<double> result = 0.1*(12*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*Sqr(g1)*Sqr(Sin(ThetaW())) + KroneckerDelta(0,gO1)*
      KroneckerDelta(0,gO2)*(-7.745966692414834*g1*g2*Cos(ThetaW())*Sin(ThetaW())
      + 5*Sqr(g2)*Sqr(Cos(ThetaW())) + 3*Sqr(g1)*Sqr(Sin(ThetaW()))));

   return result;
}

double CLASSNAME::CpUSmconjUSmconjVWmVWm(int gO1, int gO2) const
{
   const double result = 0.5*KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*Sqr(g2
      );

   return result;
}

double CLASSNAME::CpSvmLconjUSmVWm(int gO2) const
{
   const double result = 0.7071067811865475*g2*KroneckerDelta(0,gO2);

   return result;
}

std::complex<double> CLASSNAME::CpAhAhUSmconjUSm(int gI1, int gI2, int gO1, int gO2) const
{
   const std::complex<double> result = 0.05*(2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*((-10*AbsSqr(Ye(1,1)) + 3*Sqr(g1))*ZA(gI1,0)*ZA(gI2,0)
      - 3*Sqr(g1)*ZA(gI1,1)*ZA(gI2,1)) + KroneckerDelta(0,gO1)*KroneckerDelta(0,
      gO2)*((-20*AbsSqr(Ye(1,1)) - 3*Sqr(g1) + 5*Sqr(g2))*ZA(gI1,0)*ZA(gI2,0) + (3
      *Sqr(g1) - 5*Sqr(g2))*ZA(gI1,1)*ZA(gI2,1)));

   return result;
}

std::complex<double> CLASSNAME::CphhhhUSmconjUSm(int gI1, int gI2, int gO1, int gO2) const
{
   const std::complex<double> result = 0.05*(2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*((-10*AbsSqr(Ye(1,1)) + 3*Sqr(g1))*ZH(gI1,0)*ZH(gI2,0)
      - 3*Sqr(g1)*ZH(gI1,1)*ZH(gI2,1)) + KroneckerDelta(0,gO1)*KroneckerDelta(0,
      gO2)*((-20*AbsSqr(Ye(1,1)) - 3*Sqr(g1) + 5*Sqr(g2))*ZH(gI1,0)*ZH(gI2,0) + (3
      *Sqr(g1) - 5*Sqr(g2))*ZH(gI1,1)*ZH(gI2,1)));

   return result;
}

std::complex<double> CLASSNAME::CpHpmUSmconjHpmconjUSm(int gI1, int gO1, int gI2, int gO2) const
{
   const std::complex<double> result = 0.05*(-(KroneckerDelta(0,gO1)*
      KroneckerDelta(0,gO2)*(3*Sqr(g1) + 5*Sqr(g2))*(ZP(gI1,0)*ZP(gI2,0) - ZP(gI1,
      1)*ZP(gI2,1))) + 2*KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2)*((-10*AbsSqr(
      Ye(1,1)) + 3*Sqr(g1))*ZP(gI1,0)*ZP(gI2,0) - 3*Sqr(g1)*ZP(gI1,1)*ZP(gI2,1)));

   return result;
}

std::complex<double> CLASSNAME::CpSbUSmconjSbconjUSm(int gI1, int gO1, int gI2, int gO2) const
{
   const std::complex<double> result = 0.05*(2*Conj(ZB(gI1,1))*(-10*Conj(Yd(2,2
      ))*KroneckerDelta(0,gO1)*KroneckerDelta(1,gO2)*Ye(1,1)*ZB(gI2,0) + (
      KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2) - 2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2))*Sqr(g1)*ZB(gI2,1)) + Conj(ZB(gI1,0))*(KroneckerDelta(
      0,gO1)*KroneckerDelta(0,gO2)*(Sqr(g1) - 5*Sqr(g2))*ZB(gI2,0) - 2*
      KroneckerDelta(1,gO1)*(KroneckerDelta(1,gO2)*Sqr(g1)*ZB(gI2,0) + 10*Conj(Ye(
      1,1))*KroneckerDelta(0,gO2)*Yd(2,2)*ZB(gI2,1))));

   return result;
}

std::complex<double> CLASSNAME::CpScUSmconjScconjUSm(int gI1, int gO1, int gI2, int gO2) const
{
   const std::complex<double> result = 0.05*(Conj(ZC(gI1,0))*(-2*KroneckerDelta
      (1,gO1)*KroneckerDelta(1,gO2)*Sqr(g1) + KroneckerDelta(0,gO1)*KroneckerDelta
      (0,gO2)*(Sqr(g1) + 5*Sqr(g2)))*ZC(gI2,0) - 4*Conj(ZC(gI1,1))*(KroneckerDelta
      (0,gO1)*KroneckerDelta(0,gO2) - 2*KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2
      ))*Sqr(g1)*ZC(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpSdUSmconjSdconjUSm(int gI1, int gO1, int gI2, int gO2) const
{
   const std::complex<double> result = 0.05*(2*Conj(ZD(gI1,1))*(-10*Conj(Yd(0,0
      ))*KroneckerDelta(0,gO1)*KroneckerDelta(1,gO2)*Ye(1,1)*ZD(gI2,0) + (
      KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2) - 2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2))*Sqr(g1)*ZD(gI2,1)) + Conj(ZD(gI1,0))*(KroneckerDelta(
      0,gO1)*KroneckerDelta(0,gO2)*(Sqr(g1) - 5*Sqr(g2))*ZD(gI2,0) - 2*
      KroneckerDelta(1,gO1)*(KroneckerDelta(1,gO2)*Sqr(g1)*ZD(gI2,0) + 10*Conj(Ye(
      1,1))*KroneckerDelta(0,gO2)*Yd(0,0)*ZD(gI2,1))));

   return result;
}

std::complex<double> CLASSNAME::CpSeUSmconjSeconjUSm(int gI1, int gO1, int gI2, int gO2) const
{
   const std::complex<double> result = 0.05*(-2*Conj(ZE(gI1,1))*(10*Conj(Ye(0,0
      ))*KroneckerDelta(0,gO1)*KroneckerDelta(1,gO2)*Ye(1,1)*ZE(gI2,0) - 3*(
      KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2) - 2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2))*Sqr(g1)*ZE(gI2,1)) - Conj(ZE(gI1,0))*(KroneckerDelta(
      0,gO1)*KroneckerDelta(0,gO2)*(3*Sqr(g1) + 5*Sqr(g2))*ZE(gI2,0) + 2*
      KroneckerDelta(1,gO1)*(-3*KroneckerDelta(1,gO2)*Sqr(g1)*ZE(gI2,0) + 10*Conj(
      Ye(1,1))*KroneckerDelta(0,gO2)*Ye(0,0)*ZE(gI2,1))));

   return result;
}

std::complex<double> CLASSNAME::CpSmUSmconjSmconjUSm(int gI1, int gO1, int gI2, int gO2) const
{
   const std::complex<double> result = 0.1*(Conj(ZM(gI1,1))*(-12*KroneckerDelta
      (1,gO1)*KroneckerDelta(1,gO2)*Sqr(g1)*ZM(gI2,1) + KroneckerDelta(0,gO1)*(-10
      *AbsSqr(Ye(1,1)) + 3*Sqr(g1))*(KroneckerDelta(1,gO2)*ZM(gI2,0) +
      KroneckerDelta(0,gO2)*ZM(gI2,1))) - Conj(ZM(gI1,0))*(KroneckerDelta(0,gO1)*
      KroneckerDelta(0,gO2)*(3*Sqr(g1) + 5*Sqr(g2))*ZM(gI2,0) - KroneckerDelta(1,
      gO1)*(-10*AbsSqr(Ye(1,1)) + 3*Sqr(g1))*(KroneckerDelta(1,gO2)*ZM(gI2,0) +
      KroneckerDelta(0,gO2)*ZM(gI2,1))));

   return result;
}

std::complex<double> CLASSNAME::CpUSmSsconjUSmconjSs(int gO1, int gI1, int gO2, int gI2) const
{
   const std::complex<double> result = 0.05*(2*Conj(ZS(gI1,1))*(-10*Conj(Yd(1,1
      ))*KroneckerDelta(0,gO1)*KroneckerDelta(1,gO2)*Ye(1,1)*ZS(gI2,0) + (
      KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2) - 2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2))*Sqr(g1)*ZS(gI2,1)) + Conj(ZS(gI1,0))*(KroneckerDelta(
      0,gO1)*KroneckerDelta(0,gO2)*(Sqr(g1) - 5*Sqr(g2))*ZS(gI2,0) - 2*
      KroneckerDelta(1,gO1)*(KroneckerDelta(1,gO2)*Sqr(g1)*ZS(gI2,0) + 10*Conj(Ye(
      1,1))*KroneckerDelta(0,gO2)*Yd(1,1)*ZS(gI2,1))));

   return result;
}

std::complex<double> CLASSNAME::CpUSmStconjUSmconjSt(int gO1, int gI1, int gO2, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZT(gI1,0))*(-2*KroneckerDelta
      (1,gO1)*KroneckerDelta(1,gO2)*Sqr(g1) + KroneckerDelta(0,gO1)*KroneckerDelta
      (0,gO2)*(Sqr(g1) + 5*Sqr(g2)))*ZT(gI2,0) - 4*Conj(ZT(gI1,1))*(KroneckerDelta
      (0,gO1)*KroneckerDelta(0,gO2) - 2*KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2
      ))*Sqr(g1)*ZT(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpUSmStauconjUSmconjStau(int gO1, int gI1, int gO2, int gI2) const
{
   const std::complex<double> result = 0.05*(-2*Conj(ZTau(gI1,1))*(10*Conj(Ye(2
      ,2))*KroneckerDelta(0,gO1)*KroneckerDelta(1,gO2)*Ye(1,1)*ZTau(gI2,0) - 3*(
      KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2) - 2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2))*Sqr(g1)*ZTau(gI2,1)) - Conj(ZTau(gI1,0))*(
      KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*(3*Sqr(g1) + 5*Sqr(g2))*ZTau(gI2
      ,0) + 2*KroneckerDelta(1,gO1)*(-3*KroneckerDelta(1,gO2)*Sqr(g1)*ZTau(gI2,0)
      + 10*Conj(Ye(1,1))*KroneckerDelta(0,gO2)*Ye(2,2)*ZTau(gI2,1))));

   return result;
}

std::complex<double> CLASSNAME::CpUSmSuconjUSmconjSu(int gO1, int gI1, int gO2, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZU(gI1,0))*(-2*KroneckerDelta
      (1,gO1)*KroneckerDelta(1,gO2)*Sqr(g1) + KroneckerDelta(0,gO1)*KroneckerDelta
      (0,gO2)*(Sqr(g1) + 5*Sqr(g2)))*ZU(gI2,0) - 4*Conj(ZU(gI1,1))*(KroneckerDelta
      (0,gO1)*KroneckerDelta(0,gO2) - 2*KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2
      ))*Sqr(g1)*ZU(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpAhSmconjUSm(int gI2, int gI1, int gO2) const
{
   const std::complex<double> result = std::complex<double>(0.,
      0.7071067811865475)*(Conj(ZM(gI1,1))*KroneckerDelta(0,gO2)*(Conj(TYe(1,1))*
      ZA(gI2,0) + Conj(Ye(1,1))*Mu*ZA(gI2,1)) - Conj(ZM(gI1,0))*KroneckerDelta(1,
      gO2)*(Conj(Mu)*Ye(1,1)*ZA(gI2,1) + ZA(gI2,0)*TYe(1,1)));

   return result;
}

std::complex<double> CLASSNAME::CphhSmconjUSm(int gI2, int gI1, int gO2) const
{
   const std::complex<double> result = 0.05*(-2*Conj(ZM(gI1,1))*(
      7.0710678118654755*Conj(TYe(1,1))*KroneckerDelta(0,gO2)*ZH(gI2,0) -
      7.0710678118654755*Conj(Ye(1,1))*KroneckerDelta(0,gO2)*Mu*ZH(gI2,1) +
      KroneckerDelta(1,gO2)*((10*vd*AbsSqr(Ye(1,1)) - 3*vd*Sqr(g1))*ZH(gI2,0) + 3*
      vu*Sqr(g1)*ZH(gI2,1))) + Conj(ZM(gI1,0))*(KroneckerDelta(0,gO2)*(vd*(-20*
      AbsSqr(Ye(1,1)) - 3*Sqr(g1) + 5*Sqr(g2))*ZH(gI2,0) + vu*(3*Sqr(g1) - 5*Sqr(
      g2))*ZH(gI2,1)) + 14.142135623730951*KroneckerDelta(1,gO2)*(Conj(Mu)*Ye(1,1)
      *ZH(gI2,1) - ZH(gI2,0)*TYe(1,1))));

   return result;
}

std::complex<double> CLASSNAME::CpSvmLHpmconjUSm(int gI2, int gO2) const
{
   const std::complex<double> result = -0.35355339059327373*KroneckerDelta(0,
      gO2)*(vd*(-2*AbsSqr(Ye(1,1)) + Sqr(g2))*ZP(gI2,0) + vu*Sqr(g2)*ZP(gI2,1)) +
      KroneckerDelta(1,gO2)*(Conj(Mu)*Ye(1,1)*ZP(gI2,1) + ZP(gI2,0)*TYe(1,1));

   return result;
}

std::complex<double> CLASSNAME::CpSmconjUSmVP(int gI2, int gO2) const
{
   const std::complex<double> result = -0.7745966692414834*g1*Conj(ZM(gI2,1))*
      Cos(ThetaW())*KroneckerDelta(1,gO2) - 0.1*Conj(ZM(gI2,0))*KroneckerDelta(0,
      gO2)*(3.872983346207417*g1*Cos(ThetaW()) + 5*g2*Sin(ThetaW()));

   return result;
}

std::complex<double> CLASSNAME::CpSmconjUSmVZ(int gI2, int gO2) const
{
   const std::complex<double> result = 0.7745966692414834*g1*Conj(ZM(gI2,1))*
      KroneckerDelta(1,gO2)*Sin(ThetaW()) - 0.1*Conj(ZM(gI2,0))*KroneckerDelta(0,
      gO2)*(5*g2*Cos(ThetaW()) - 3.872983346207417*g1*Sin(ThetaW()));

   return result;
}

double CLASSNAME::CpFvmChaconjUSmPR(int , int ) const
{
   const double result = 0;

   return result;
}

std::complex<double> CLASSNAME::CpFvmChaconjUSmPL(int gI2, int gO1) const
{
   const std::complex<double> result = -(g2*Conj(UM(gI2,0))*KroneckerDelta(0,
      gO1)) + Conj(UM(gI2,1))*KroneckerDelta(1,gO1)*Ye(1,1);

   return result;
}

std::complex<double> CLASSNAME::CpChiFmconjUSmPR(int gI2, int gO2) const
{
   const std::complex<double> result = -1.0954451150103321*g1*KroneckerDelta(1,
      gO2)*ZN(gI2,0) - Conj(Ye(1,1))*KroneckerDelta(0,gO2)*ZN(gI2,2);

   return result;
}

std::complex<double> CLASSNAME::CpChiFmconjUSmPL(int gI2, int gO1) const
{
   const std::complex<double> result = 0.5477225575051661*g1*Conj(ZN(gI2,0))*
      KroneckerDelta(0,gO1) + 0.7071067811865475*g2*Conj(ZN(gI2,1))*KroneckerDelta
      (0,gO1) - Conj(ZN(gI2,2))*KroneckerDelta(1,gO1)*Ye(1,1);

   return result;
}

std::complex<double> CLASSNAME::CpSveLUStauconjSveLconjUStau(int gO1, int gO2) const
{
   const std::complex<double> result = 0.05*(6*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*Sqr(g1) + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*
      (-3*Sqr(g1) + 5*Sqr(g2)));

   return result;
}

std::complex<double> CLASSNAME::CpSvmLUStauconjSvmLconjUStau(int gO1, int gO2) const
{
   const std::complex<double> result = 0.05*(6*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*Sqr(g1) + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*
      (-3*Sqr(g1) + 5*Sqr(g2)));

   return result;
}

std::complex<double> CLASSNAME::CpSvtLUStauconjSvtLconjUStau(int gO1, int gO2) const
{
   const std::complex<double> result = 0.05*(2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*(-10*AbsSqr(Ye(2,2)) + 3*Sqr(g1)) - KroneckerDelta(0,
      gO1)*KroneckerDelta(0,gO2)*(3*Sqr(g1) + 5*Sqr(g2)));

   return result;
}

std::complex<double> CLASSNAME::CpUStauconjUStauVZVZ(int gO1, int gO2) const
{
   const std::complex<double> result = 0.1*(12*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*Sqr(g1)*Sqr(Sin(ThetaW())) + KroneckerDelta(0,gO1)*
      KroneckerDelta(0,gO2)*(-7.745966692414834*g1*g2*Cos(ThetaW())*Sin(ThetaW())
      + 5*Sqr(g2)*Sqr(Cos(ThetaW())) + 3*Sqr(g1)*Sqr(Sin(ThetaW()))));

   return result;
}

double CLASSNAME::CpUStauconjUStauconjVWmVWm(int gO1, int gO2) const
{
   const double result = 0.5*KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*Sqr(g2
      );

   return result;
}

double CLASSNAME::CpSvtLconjUStauVWm(int gO2) const
{
   const double result = 0.7071067811865475*g2*KroneckerDelta(0,gO2);

   return result;
}

std::complex<double> CLASSNAME::CpAhAhUStauconjUStau(int gI1, int gI2, int gO1, int gO2) const
{
   const std::complex<double> result = 0.05*(2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*((-10*AbsSqr(Ye(2,2)) + 3*Sqr(g1))*ZA(gI1,0)*ZA(gI2,0)
      - 3*Sqr(g1)*ZA(gI1,1)*ZA(gI2,1)) + KroneckerDelta(0,gO1)*KroneckerDelta(0,
      gO2)*((-20*AbsSqr(Ye(2,2)) - 3*Sqr(g1) + 5*Sqr(g2))*ZA(gI1,0)*ZA(gI2,0) + (3
      *Sqr(g1) - 5*Sqr(g2))*ZA(gI1,1)*ZA(gI2,1)));

   return result;
}

std::complex<double> CLASSNAME::CphhhhUStauconjUStau(int gI1, int gI2, int gO1, int gO2) const
{
   const std::complex<double> result = 0.05*(2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*((-10*AbsSqr(Ye(2,2)) + 3*Sqr(g1))*ZH(gI1,0)*ZH(gI2,0)
      - 3*Sqr(g1)*ZH(gI1,1)*ZH(gI2,1)) + KroneckerDelta(0,gO1)*KroneckerDelta(0,
      gO2)*((-20*AbsSqr(Ye(2,2)) - 3*Sqr(g1) + 5*Sqr(g2))*ZH(gI1,0)*ZH(gI2,0) + (3
      *Sqr(g1) - 5*Sqr(g2))*ZH(gI1,1)*ZH(gI2,1)));

   return result;
}

std::complex<double> CLASSNAME::CpHpmUStauconjHpmconjUStau(int gI1, int gO1, int gI2, int gO2) const
{
   const std::complex<double> result = 0.05*(-(KroneckerDelta(0,gO1)*
      KroneckerDelta(0,gO2)*(3*Sqr(g1) + 5*Sqr(g2))*(ZP(gI1,0)*ZP(gI2,0) - ZP(gI1,
      1)*ZP(gI2,1))) + 2*KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2)*((-10*AbsSqr(
      Ye(2,2)) + 3*Sqr(g1))*ZP(gI1,0)*ZP(gI2,0) - 3*Sqr(g1)*ZP(gI1,1)*ZP(gI2,1)));

   return result;
}

std::complex<double> CLASSNAME::CpSbUStauconjSbconjUStau(int gI1, int gO1, int gI2, int gO2) const
{
   const std::complex<double> result = 0.05*(2*Conj(ZB(gI1,1))*(-10*Conj(Yd(2,2
      ))*KroneckerDelta(0,gO1)*KroneckerDelta(1,gO2)*Ye(2,2)*ZB(gI2,0) + (
      KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2) - 2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2))*Sqr(g1)*ZB(gI2,1)) + Conj(ZB(gI1,0))*(KroneckerDelta(
      0,gO1)*KroneckerDelta(0,gO2)*(Sqr(g1) - 5*Sqr(g2))*ZB(gI2,0) - 2*
      KroneckerDelta(1,gO1)*(KroneckerDelta(1,gO2)*Sqr(g1)*ZB(gI2,0) + 10*Conj(Ye(
      2,2))*KroneckerDelta(0,gO2)*Yd(2,2)*ZB(gI2,1))));

   return result;
}

std::complex<double> CLASSNAME::CpScUStauconjScconjUStau(int gI1, int gO1, int gI2, int gO2) const
{
   const std::complex<double> result = 0.05*(Conj(ZC(gI1,0))*(-2*KroneckerDelta
      (1,gO1)*KroneckerDelta(1,gO2)*Sqr(g1) + KroneckerDelta(0,gO1)*KroneckerDelta
      (0,gO2)*(Sqr(g1) + 5*Sqr(g2)))*ZC(gI2,0) - 4*Conj(ZC(gI1,1))*(KroneckerDelta
      (0,gO1)*KroneckerDelta(0,gO2) - 2*KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2
      ))*Sqr(g1)*ZC(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpSdUStauconjSdconjUStau(int gI1, int gO1, int gI2, int gO2) const
{
   const std::complex<double> result = 0.05*(2*Conj(ZD(gI1,1))*(-10*Conj(Yd(0,0
      ))*KroneckerDelta(0,gO1)*KroneckerDelta(1,gO2)*Ye(2,2)*ZD(gI2,0) + (
      KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2) - 2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2))*Sqr(g1)*ZD(gI2,1)) + Conj(ZD(gI1,0))*(KroneckerDelta(
      0,gO1)*KroneckerDelta(0,gO2)*(Sqr(g1) - 5*Sqr(g2))*ZD(gI2,0) - 2*
      KroneckerDelta(1,gO1)*(KroneckerDelta(1,gO2)*Sqr(g1)*ZD(gI2,0) + 10*Conj(Ye(
      2,2))*KroneckerDelta(0,gO2)*Yd(0,0)*ZD(gI2,1))));

   return result;
}

std::complex<double> CLASSNAME::CpSeUStauconjSeconjUStau(int gI1, int gO1, int gI2, int gO2) const
{
   const std::complex<double> result = 0.05*(-2*Conj(ZE(gI1,1))*(10*Conj(Ye(0,0
      ))*KroneckerDelta(0,gO1)*KroneckerDelta(1,gO2)*Ye(2,2)*ZE(gI2,0) - 3*(
      KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2) - 2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2))*Sqr(g1)*ZE(gI2,1)) - Conj(ZE(gI1,0))*(KroneckerDelta(
      0,gO1)*KroneckerDelta(0,gO2)*(3*Sqr(g1) + 5*Sqr(g2))*ZE(gI2,0) + 2*
      KroneckerDelta(1,gO1)*(-3*KroneckerDelta(1,gO2)*Sqr(g1)*ZE(gI2,0) + 10*Conj(
      Ye(2,2))*KroneckerDelta(0,gO2)*Ye(0,0)*ZE(gI2,1))));

   return result;
}

std::complex<double> CLASSNAME::CpSmUStauconjSmconjUStau(int gI1, int gO1, int gI2, int gO2) const
{
   const std::complex<double> result = 0.05*(-2*Conj(ZM(gI1,1))*(10*Conj(Ye(1,1
      ))*KroneckerDelta(0,gO1)*KroneckerDelta(1,gO2)*Ye(2,2)*ZM(gI2,0) - 3*(
      KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2) - 2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2))*Sqr(g1)*ZM(gI2,1)) - Conj(ZM(gI1,0))*(KroneckerDelta(
      0,gO1)*KroneckerDelta(0,gO2)*(3*Sqr(g1) + 5*Sqr(g2))*ZM(gI2,0) + 2*
      KroneckerDelta(1,gO1)*(-3*KroneckerDelta(1,gO2)*Sqr(g1)*ZM(gI2,0) + 10*Conj(
      Ye(2,2))*KroneckerDelta(0,gO2)*Ye(1,1)*ZM(gI2,1))));

   return result;
}

std::complex<double> CLASSNAME::CpSsUStauconjSsconjUStau(int gI1, int gO1, int gI2, int gO2) const
{
   const std::complex<double> result = 0.05*(2*Conj(ZS(gI1,1))*(-10*Conj(Yd(1,1
      ))*KroneckerDelta(0,gO1)*KroneckerDelta(1,gO2)*Ye(2,2)*ZS(gI2,0) + (
      KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2) - 2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2))*Sqr(g1)*ZS(gI2,1)) + Conj(ZS(gI1,0))*(KroneckerDelta(
      0,gO1)*KroneckerDelta(0,gO2)*(Sqr(g1) - 5*Sqr(g2))*ZS(gI2,0) - 2*
      KroneckerDelta(1,gO1)*(KroneckerDelta(1,gO2)*Sqr(g1)*ZS(gI2,0) + 10*Conj(Ye(
      2,2))*KroneckerDelta(0,gO2)*Yd(1,1)*ZS(gI2,1))));

   return result;
}

std::complex<double> CLASSNAME::CpStUStauconjStconjUStau(int gI1, int gO1, int gI2, int gO2) const
{
   const std::complex<double> result = 0.05*(Conj(ZT(gI1,0))*(-2*KroneckerDelta
      (1,gO1)*KroneckerDelta(1,gO2)*Sqr(g1) + KroneckerDelta(0,gO1)*KroneckerDelta
      (0,gO2)*(Sqr(g1) + 5*Sqr(g2)))*ZT(gI2,0) - 4*Conj(ZT(gI1,1))*(KroneckerDelta
      (0,gO1)*KroneckerDelta(0,gO2) - 2*KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2
      ))*Sqr(g1)*ZT(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpStauUStauconjStauconjUStau(int gI1, int gO1, int gI2, int gO2) const
{
   const std::complex<double> result = 0.1*(Conj(ZTau(gI1,1))*(-12*
      KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2)*Sqr(g1)*ZTau(gI2,1) +
      KroneckerDelta(0,gO1)*(-10*AbsSqr(Ye(2,2)) + 3*Sqr(g1))*(KroneckerDelta(1,
      gO2)*ZTau(gI2,0) + KroneckerDelta(0,gO2)*ZTau(gI2,1))) - Conj(ZTau(gI1,0))*(
      KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*(3*Sqr(g1) + 5*Sqr(g2))*ZTau(gI2
      ,0) - KroneckerDelta(1,gO1)*(-10*AbsSqr(Ye(2,2)) + 3*Sqr(g1))*(
      KroneckerDelta(1,gO2)*ZTau(gI2,0) + KroneckerDelta(0,gO2)*ZTau(gI2,1))));

   return result;
}

std::complex<double> CLASSNAME::CpUStauSuconjUStauconjSu(int gO1, int gI1, int gO2, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZU(gI1,0))*(-2*KroneckerDelta
      (1,gO1)*KroneckerDelta(1,gO2)*Sqr(g1) + KroneckerDelta(0,gO1)*KroneckerDelta
      (0,gO2)*(Sqr(g1) + 5*Sqr(g2)))*ZU(gI2,0) - 4*Conj(ZU(gI1,1))*(KroneckerDelta
      (0,gO1)*KroneckerDelta(0,gO2) - 2*KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2
      ))*Sqr(g1)*ZU(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpAhStauconjUStau(int gI2, int gI1, int gO2) const
{
   const std::complex<double> result = std::complex<double>(0.,
      0.7071067811865475)*(Conj(ZTau(gI1,1))*KroneckerDelta(0,gO2)*(Conj(TYe(2,2))
      *ZA(gI2,0) + Conj(Ye(2,2))*Mu*ZA(gI2,1)) - Conj(ZTau(gI1,0))*KroneckerDelta(
      1,gO2)*(Conj(Mu)*Ye(2,2)*ZA(gI2,1) + ZA(gI2,0)*TYe(2,2)));

   return result;
}

std::complex<double> CLASSNAME::CphhStauconjUStau(int gI2, int gI1, int gO2) const
{
   const std::complex<double> result = 0.05*(-2*Conj(ZTau(gI1,1))*(
      7.0710678118654755*Conj(TYe(2,2))*KroneckerDelta(0,gO2)*ZH(gI2,0) -
      7.0710678118654755*Conj(Ye(2,2))*KroneckerDelta(0,gO2)*Mu*ZH(gI2,1) +
      KroneckerDelta(1,gO2)*((10*vd*AbsSqr(Ye(2,2)) - 3*vd*Sqr(g1))*ZH(gI2,0) + 3*
      vu*Sqr(g1)*ZH(gI2,1))) + Conj(ZTau(gI1,0))*(KroneckerDelta(0,gO2)*(vd*(-20*
      AbsSqr(Ye(2,2)) - 3*Sqr(g1) + 5*Sqr(g2))*ZH(gI2,0) + vu*(3*Sqr(g1) - 5*Sqr(
      g2))*ZH(gI2,1)) + 14.142135623730951*KroneckerDelta(1,gO2)*(Conj(Mu)*Ye(2,2)
      *ZH(gI2,1) - ZH(gI2,0)*TYe(2,2))));

   return result;
}

std::complex<double> CLASSNAME::CpSvtLHpmconjUStau(int gI2, int gO2) const
{
   const std::complex<double> result = -0.35355339059327373*KroneckerDelta(0,
      gO2)*(vd*(-2*AbsSqr(Ye(2,2)) + Sqr(g2))*ZP(gI2,0) + vu*Sqr(g2)*ZP(gI2,1)) +
      KroneckerDelta(1,gO2)*(Conj(Mu)*Ye(2,2)*ZP(gI2,1) + ZP(gI2,0)*TYe(2,2));

   return result;
}

std::complex<double> CLASSNAME::CpStauconjUStauVP(int gI2, int gO2) const
{
   const std::complex<double> result = -0.7745966692414834*g1*Conj(ZTau(gI2,1))
      *Cos(ThetaW())*KroneckerDelta(1,gO2) - 0.1*Conj(ZTau(gI2,0))*KroneckerDelta(
      0,gO2)*(3.872983346207417*g1*Cos(ThetaW()) + 5*g2*Sin(ThetaW()));

   return result;
}

std::complex<double> CLASSNAME::CpStauconjUStauVZ(int gI2, int gO2) const
{
   const std::complex<double> result = 0.7745966692414834*g1*Conj(ZTau(gI2,1))*
      KroneckerDelta(1,gO2)*Sin(ThetaW()) - 0.1*Conj(ZTau(gI2,0))*KroneckerDelta(0
      ,gO2)*(5*g2*Cos(ThetaW()) - 3.872983346207417*g1*Sin(ThetaW()));

   return result;
}

double CLASSNAME::CpFvtChaconjUStauPR(int , int ) const
{
   const double result = 0;

   return result;
}

std::complex<double> CLASSNAME::CpFvtChaconjUStauPL(int gI2, int gO1) const
{
   const std::complex<double> result = -(g2*Conj(UM(gI2,0))*KroneckerDelta(0,
      gO1)) + Conj(UM(gI2,1))*KroneckerDelta(1,gO1)*Ye(2,2);

   return result;
}

std::complex<double> CLASSNAME::CpChiFtauconjUStauPR(int gI2, int gO2) const
{
   const std::complex<double> result = -1.0954451150103321*g1*KroneckerDelta(1,
      gO2)*ZN(gI2,0) - Conj(Ye(2,2))*KroneckerDelta(0,gO2)*ZN(gI2,2);

   return result;
}

std::complex<double> CLASSNAME::CpChiFtauconjUStauPL(int gI2, int gO1) const
{
   const std::complex<double> result = 0.5477225575051661*g1*Conj(ZN(gI2,0))*
      KroneckerDelta(0,gO1) + 0.7071067811865475*g2*Conj(ZN(gI2,1))*KroneckerDelta
      (0,gO1) - Conj(ZN(gI2,2))*KroneckerDelta(1,gO1)*Ye(2,2);

   return result;
}

std::complex<double> CLASSNAME::CpSveLUSsconjSveLconjUSs(int gO1, int gO2) const
{
   const std::complex<double> result = 0.05*(2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*Sqr(g1) + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*
      (Sqr(g1) + 5*Sqr(g2)));

   return result;
}

std::complex<double> CLASSNAME::CpSvmLUSsconjSvmLconjUSs(int gO1, int gO2) const
{
   const std::complex<double> result = 0.05*(2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*Sqr(g1) + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*
      (Sqr(g1) + 5*Sqr(g2)));

   return result;
}

std::complex<double> CLASSNAME::CpSvtLUSsconjSvtLconjUSs(int gO1, int gO2) const
{
   const std::complex<double> result = 0.05*(2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*Sqr(g1) + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*
      (Sqr(g1) + 5*Sqr(g2)));

   return result;
}

std::complex<double> CLASSNAME::CpUSsconjUSsVZVZ(int gO1, int gO2) const
{
   const std::complex<double> result = 0.03333333333333333*(KroneckerDelta(0,
      gO1)*KroneckerDelta(0,gO2)*(g1*Sin(ThetaW())*(7.745966692414834*g2*Cos(
      ThetaW()) + g1*Sin(ThetaW())) + 15*Sqr(g2)*Sqr(Cos(ThetaW()))) + 4*
      KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2)*Sqr(g1)*Sqr(Sin(ThetaW())));

   return result;
}

double CLASSNAME::CpUSsconjUSsconjVWmVWm(int gO1, int gO2) const
{
   const double result = 0.5*KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*Sqr(g2
      );

   return result;
}

std::complex<double> CLASSNAME::CpAhAhUSsconjUSs(int gI1, int gI2, int gO1, int gO2) const
{
   const std::complex<double> result = 0.05*(2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*((-10*AbsSqr(Yd(1,1)) + Sqr(g1))*ZA(gI1,0)*ZA(gI2,0) -
      Sqr(g1)*ZA(gI1,1)*ZA(gI2,1)) + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*
      ((-20*AbsSqr(Yd(1,1)) + Sqr(g1) + 5*Sqr(g2))*ZA(gI1,0)*ZA(gI2,0) - (Sqr(g1)
      + 5*Sqr(g2))*ZA(gI1,1)*ZA(gI2,1)));

   return result;
}

std::complex<double> CLASSNAME::CphhhhUSsconjUSs(int gI1, int gI2, int gO1, int gO2) const
{
   const std::complex<double> result = 0.05*(2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*((-10*AbsSqr(Yd(1,1)) + Sqr(g1))*ZH(gI1,0)*ZH(gI2,0) -
      Sqr(g1)*ZH(gI1,1)*ZH(gI2,1)) + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*
      ((-20*AbsSqr(Yd(1,1)) + Sqr(g1) + 5*Sqr(g2))*ZH(gI1,0)*ZH(gI2,0) - (Sqr(g1)
      + 5*Sqr(g2))*ZH(gI1,1)*ZH(gI2,1)));

   return result;
}

std::complex<double> CLASSNAME::CpHpmUSsconjHpmconjUSs(int gI1, int gO1, int gI2, int gO2) const
{
   const std::complex<double> result = 0.05*(2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*((-10*AbsSqr(Yd(1,1)) + Sqr(g1))*ZP(gI1,0)*ZP(gI2,0) -
      Sqr(g1)*ZP(gI1,1)*ZP(gI2,1)) + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*
      ((Sqr(g1) - 5*Sqr(g2))*ZP(gI1,0)*ZP(gI2,0) - (20*AbsSqr(Yu(1,1)) + Sqr(g1) -
      5*Sqr(g2))*ZP(gI1,1)*ZP(gI2,1)));

   return result;
}

std::complex<double> CLASSNAME::CpSeUSsconjSeconjUSs(int gI1, int gO1, int gI2, int gO2) const
{
   const std::complex<double> result = 0.05*(-2*Conj(ZE(gI1,1))*(10*Conj(Ye(0,0
      ))*KroneckerDelta(0,gO1)*KroneckerDelta(1,gO2)*Yd(1,1)*ZE(gI2,0) + (
      KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2) + 2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2))*Sqr(g1)*ZE(gI2,1)) + Conj(ZE(gI1,0))*(KroneckerDelta(
      0,gO1)*KroneckerDelta(0,gO2)*(Sqr(g1) - 5*Sqr(g2))*ZE(gI2,0) + 2*
      KroneckerDelta(1,gO1)*(KroneckerDelta(1,gO2)*Sqr(g1)*ZE(gI2,0) - 10*Conj(Yd(
      1,1))*KroneckerDelta(0,gO2)*Ye(0,0)*ZE(gI2,1))));

   return result;
}

std::complex<double> CLASSNAME::CpSmUSsconjSmconjUSs(int gI1, int gO1, int gI2, int gO2) const
{
   const std::complex<double> result = 0.05*(-2*Conj(ZM(gI1,1))*(10*Conj(Ye(1,1
      ))*KroneckerDelta(0,gO1)*KroneckerDelta(1,gO2)*Yd(1,1)*ZM(gI2,0) + (
      KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2) + 2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2))*Sqr(g1)*ZM(gI2,1)) + Conj(ZM(gI1,0))*(KroneckerDelta(
      0,gO1)*KroneckerDelta(0,gO2)*(Sqr(g1) - 5*Sqr(g2))*ZM(gI2,0) + 2*
      KroneckerDelta(1,gO1)*(KroneckerDelta(1,gO2)*Sqr(g1)*ZM(gI2,0) - 10*Conj(Yd(
      1,1))*KroneckerDelta(0,gO2)*Ye(1,1)*ZM(gI2,1))));

   return result;
}

std::complex<double> CLASSNAME::CpUSsconjUSsconjSbSb(int gO1, int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(-2*Conj(ZB(gI2,1))*(30*Conj(Yd(2,2
      ))*KroneckerDelta(0,gO1)*KroneckerDelta(1,gO2)*Yd(1,1)*ZB(gI1,0) + (
      KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2) + 2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2))*Sqr(g1)*ZB(gI1,1)) - Conj(ZB(gI2,0))*(KroneckerDelta(
      0,gO1)*KroneckerDelta(0,gO2)*(Sqr(g1) + 15*Sqr(g2))*ZB(gI1,0) + 2*
      KroneckerDelta(1,gO1)*(KroneckerDelta(1,gO2)*Sqr(g1)*ZB(gI1,0) + 30*Conj(Yd(
      1,1))*KroneckerDelta(0,gO2)*Yd(2,2)*ZB(gI1,1))));

   return result;
}

std::complex<double> CLASSNAME::CpUSsconjUSsconjScSc(int gO1, int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(-(Conj(ZC(gI2,0))*(2*
      KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2)*(10*AbsSqr(Yd(1,1)) + Sqr(g1)) +
      KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*(Sqr(g1) - 5*Sqr(g2)))*ZC(gI1,0
      )) + 4*Conj(ZC(gI2,1))*(2*KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2)*Sqr(g1
      ) + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*(-5*AbsSqr(Yu(1,1)) + Sqr(g1
      )))*ZC(gI1,1));

   return result;
}

std::complex<double> CLASSNAME::CpUSsconjUSsconjSdSd(int gO1, int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(-2*Conj(ZD(gI2,1))*(30*Conj(Yd(0,0
      ))*KroneckerDelta(0,gO1)*KroneckerDelta(1,gO2)*Yd(1,1)*ZD(gI1,0) + (
      KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2) + 2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2))*Sqr(g1)*ZD(gI1,1)) - Conj(ZD(gI2,0))*(KroneckerDelta(
      0,gO1)*KroneckerDelta(0,gO2)*(Sqr(g1) + 15*Sqr(g2))*ZD(gI1,0) + 2*
      KroneckerDelta(1,gO1)*(KroneckerDelta(1,gO2)*Sqr(g1)*ZD(gI1,0) + 30*Conj(Yd(
      1,1))*KroneckerDelta(0,gO2)*Yd(0,0)*ZD(gI1,1))));

   return result;
}

std::complex<double> CLASSNAME::CpUSsconjUSsconjSsSs(int gO1, int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = 0.03333333333333333*(-(Conj(ZS(gI2,1))*(
      8*KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2)*(Sqr(g1) + 5*Sqr(g3))*ZS(gI1,1
      ) + KroneckerDelta(0,gO1)*(KroneckerDelta(1,gO2)*(90*AbsSqr(Yd(1,1)) + Sqr(
      g1) - 40*Sqr(g3))*ZS(gI1,0) + 3*KroneckerDelta(0,gO2)*(10*AbsSqr(Yd(1,1)) +
      Sqr(g1))*ZS(gI1,1)))) - Conj(ZS(gI2,0))*(2*KroneckerDelta(0,gO1)*
      KroneckerDelta(0,gO2)*(Sqr(g1) + 15*Sqr(g2) + 20*Sqr(g3))*ZS(gI1,0) +
      KroneckerDelta(1,gO1)*(3*KroneckerDelta(1,gO2)*(10*AbsSqr(Yd(1,1)) + Sqr(g1)
      )*ZS(gI1,0) + KroneckerDelta(0,gO2)*(90*AbsSqr(Yd(1,1)) + Sqr(g1) - 40*Sqr(
      g3))*ZS(gI1,1))));

   return result;
}

std::complex<double> CLASSNAME::CpUSsconjUSsconjStSt(int gO1, int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(-(Conj(ZT(gI2,0))*(2*
      KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2)*Sqr(g1) + KroneckerDelta(0,gO1)*
      KroneckerDelta(0,gO2)*(Sqr(g1) - 15*Sqr(g2)))*ZT(gI1,0)) + 4*Conj(ZT(gI2,1))
      *(KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2) + 2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2))*Sqr(g1)*ZT(gI1,1));

   return result;
}

std::complex<double> CLASSNAME::CpUSsconjUSsconjSuSu(int gO1, int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(-(Conj(ZU(gI2,0))*(2*
      KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2)*Sqr(g1) + KroneckerDelta(0,gO1)*
      KroneckerDelta(0,gO2)*(Sqr(g1) - 15*Sqr(g2)))*ZU(gI1,0)) + 4*Conj(ZU(gI2,1))
      *(KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2) + 2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2))*Sqr(g1)*ZU(gI1,1));

   return result;
}

std::complex<double> CLASSNAME::CpUSsStauconjUSsconjStau(int gO1, int gI1, int gO2, int gI2) const
{
   const std::complex<double> result = 0.05*(-2*Conj(ZTau(gI1,1))*(10*Conj(Ye(2
      ,2))*KroneckerDelta(0,gO1)*KroneckerDelta(1,gO2)*Yd(1,1)*ZTau(gI2,0) + (
      KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2) + 2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2))*Sqr(g1)*ZTau(gI2,1)) + Conj(ZTau(gI1,0))*(
      KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*(Sqr(g1) - 5*Sqr(g2))*ZTau(gI2,0
      ) + 2*KroneckerDelta(1,gO1)*(KroneckerDelta(1,gO2)*Sqr(g1)*ZTau(gI2,0) - 10*
      Conj(Yd(1,1))*KroneckerDelta(0,gO2)*Ye(2,2)*ZTau(gI2,1))));

   return result;
}

std::complex<double> CLASSNAME::CpAhSsconjUSs(int gI2, int gI1, int gO2) const
{
   const std::complex<double> result = std::complex<double>(0.,
      0.7071067811865475)*(Conj(ZS(gI1,1))*KroneckerDelta(0,gO2)*(Conj(TYd(1,1))*
      ZA(gI2,0) + Conj(Yd(1,1))*Mu*ZA(gI2,1)) - Conj(ZS(gI1,0))*KroneckerDelta(1,
      gO2)*(Conj(Mu)*Yd(1,1)*ZA(gI2,1) + ZA(gI2,0)*TYd(1,1)));

   return result;
}

std::complex<double> CLASSNAME::CphhSsconjUSs(int gI2, int gI1, int gO2) const
{
   const std::complex<double> result = 0.05*(-2*Conj(ZS(gI1,1))*(
      7.0710678118654755*Conj(TYd(1,1))*KroneckerDelta(0,gO2)*ZH(gI2,0) -
      7.0710678118654755*Conj(Yd(1,1))*KroneckerDelta(0,gO2)*Mu*ZH(gI2,1) +
      KroneckerDelta(1,gO2)*(-(vd*(-10*AbsSqr(Yd(1,1)) + Sqr(g1))*ZH(gI2,0)) + vu*
      Sqr(g1)*ZH(gI2,1))) + Conj(ZS(gI1,0))*(KroneckerDelta(0,gO2)*(vd*(-20*AbsSqr
      (Yd(1,1)) + Sqr(g1) + 5*Sqr(g2))*ZH(gI2,0) - vu*(Sqr(g1) + 5*Sqr(g2))*ZH(gI2
      ,1)) + 14.142135623730951*KroneckerDelta(1,gO2)*(Conj(Mu)*Yd(1,1)*ZH(gI2,1)
      - ZH(gI2,0)*TYd(1,1))));

   return result;
}

std::complex<double> CLASSNAME::CpHpmScconjUSs(int gI2, int gI1, int gO2) const
{
   const std::complex<double> result = 0.5*Conj(ZC(gI1,1))*(2*Conj(TYu(1,1))*
      KroneckerDelta(0,gO2)*ZP(gI2,1) + Conj(Yu(1,1))*(2*KroneckerDelta(0,gO2)*Mu*
      ZP(gI2,0) + 1.4142135623730951*KroneckerDelta(1,gO2)*Yd(1,1)*(vu*ZP(gI2,0) +
      vd*ZP(gI2,1)))) - 0.25*Conj(ZC(gI1,0))*(1.4142135623730951*KroneckerDelta(0
      ,gO2)*(vd*(-2*AbsSqr(Yd(1,1)) + Sqr(g2))*ZP(gI2,0) + vu*(-2*AbsSqr(Yu(1,1))
      + Sqr(g2))*ZP(gI2,1)) - 4*KroneckerDelta(1,gO2)*(Conj(Mu)*Yd(1,1)*ZP(gI2,1)
      + ZP(gI2,0)*TYd(1,1)));

   return result;
}

std::complex<double> CLASSNAME::CpScconjUSsVWm(int gI2, int gO2) const
{
   const std::complex<double> result = 0.7071067811865475*g2*Conj(ZC(gI2,0))*
      KroneckerDelta(0,gO2);

   return result;
}

std::complex<double> CLASSNAME::CpSsconjUSsVG(int gI2, int gO2) const
{
   const std::complex<double> result = IF(gI2 < 2,g3*Conj(ZS(gI2,gO2)),0);

   return result;
}

std::complex<double> CLASSNAME::CpSsconjUSsVP(int gI2, int gO2) const
{
   const std::complex<double> result = 0.03333333333333333*(-7.745966692414834*
      g1*Conj(ZS(gI2,1))*Cos(ThetaW())*KroneckerDelta(1,gO2) + Conj(ZS(gI2,0))*
      KroneckerDelta(0,gO2)*(3.872983346207417*g1*Cos(ThetaW()) - 15*g2*Sin(ThetaW
      ())));

   return result;
}

std::complex<double> CLASSNAME::CpSsconjUSsVZ(int gI2, int gO2) const
{
   const std::complex<double> result = 0.2581988897471611*g1*Conj(ZS(gI2,1))*
      KroneckerDelta(1,gO2)*Sin(ThetaW()) - 0.03333333333333333*Conj(ZS(gI2,0))*
      KroneckerDelta(0,gO2)*(15*g2*Cos(ThetaW()) + 3.872983346207417*g1*Sin(ThetaW
      ()));

   return result;
}

std::complex<double> CLASSNAME::CpFcChaconjUSsPR(int gI2, int gO2) const
{
   const std::complex<double> result = Conj(Yu(1,1))*KroneckerDelta(0,gO2)*UP(
      gI2,1);

   return result;
}

std::complex<double> CLASSNAME::CpFcChaconjUSsPL(int gI2, int gO1) const
{
   const std::complex<double> result = -(g2*Conj(UM(gI2,0))*KroneckerDelta(0,
      gO1)) + Conj(UM(gI2,1))*KroneckerDelta(1,gO1)*Yd(1,1);

   return result;
}

std::complex<double> CLASSNAME::CpChiFsconjUSsPR(int gI2, int gO2) const
{
   const std::complex<double> result = -0.3651483716701107*g1*KroneckerDelta(1,
      gO2)*ZN(gI2,0) - Conj(Yd(1,1))*KroneckerDelta(0,gO2)*ZN(gI2,2);

   return result;
}

std::complex<double> CLASSNAME::CpChiFsconjUSsPL(int gI2, int gO1) const
{
   const std::complex<double> result = -0.18257418583505536*g1*Conj(ZN(gI2,0))*
      KroneckerDelta(0,gO1) + 0.7071067811865475*g2*Conj(ZN(gI2,1))*KroneckerDelta
      (0,gO1) - Conj(ZN(gI2,2))*KroneckerDelta(1,gO1)*Yd(1,1);

   return result;
}

std::complex<double> CLASSNAME::CpGluFsconjUSsPR(int gO2) const
{
   const std::complex<double> result = 1.4142135623730951*g3*Conj(PhaseGlu)*
      KroneckerDelta(1,gO2);

   return result;
}

std::complex<double> CLASSNAME::CpGluFsconjUSsPL(int gO1) const
{
   const std::complex<double> result = -1.4142135623730951*g3*PhaseGlu*
      KroneckerDelta(0,gO1);

   return result;
}

std::complex<double> CLASSNAME::CpSveLUScconjSveLconjUSc(int gO1, int gO2) const
{
   const std::complex<double> result = 0.05*(-4*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*Sqr(g1) + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*
      (Sqr(g1) - 5*Sqr(g2)));

   return result;
}

std::complex<double> CLASSNAME::CpSvmLUScconjSvmLconjUSc(int gO1, int gO2) const
{
   const std::complex<double> result = 0.05*(-4*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*Sqr(g1) + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*
      (Sqr(g1) - 5*Sqr(g2)));

   return result;
}

std::complex<double> CLASSNAME::CpSvtLUScconjSvtLconjUSc(int gO1, int gO2) const
{
   const std::complex<double> result = 0.05*(-4*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*Sqr(g1) + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*
      (Sqr(g1) - 5*Sqr(g2)));

   return result;
}

std::complex<double> CLASSNAME::CpUScconjUScVZVZ(int gO1, int gO2) const
{
   const std::complex<double> result = 0.03333333333333333*(16*KroneckerDelta(1
      ,gO1)*KroneckerDelta(1,gO2)*Sqr(g1)*Sqr(Sin(ThetaW())) + KroneckerDelta(0,
      gO1)*KroneckerDelta(0,gO2)*(-7.745966692414834*g1*g2*Cos(ThetaW())*Sin(
      ThetaW()) + 15*Sqr(g2)*Sqr(Cos(ThetaW())) + Sqr(g1)*Sqr(Sin(ThetaW()))));

   return result;
}

double CLASSNAME::CpUScconjUScconjVWmVWm(int gO1, int gO2) const
{
   const double result = 0.5*KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*Sqr(g2
      );

   return result;
}

std::complex<double> CLASSNAME::CpAhAhUScconjUSc(int gI1, int gI2, int gO1, int gO2) const
{
   const std::complex<double> result = 0.05*(-4*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*(Sqr(g1)*ZA(gI1,0)*ZA(gI2,0) - (-5*AbsSqr(Yu(1,1)) +
      Sqr(g1))*ZA(gI1,1)*ZA(gI2,1)) + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*
      ((Sqr(g1) - 5*Sqr(g2))*ZA(gI1,0)*ZA(gI2,0) - (20*AbsSqr(Yu(1,1)) + Sqr(g1) -
      5*Sqr(g2))*ZA(gI1,1)*ZA(gI2,1)));

   return result;
}

std::complex<double> CLASSNAME::CphhhhUScconjUSc(int gI1, int gI2, int gO1, int gO2) const
{
   const std::complex<double> result = 0.05*(-4*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*(Sqr(g1)*ZH(gI1,0)*ZH(gI2,0) - (-5*AbsSqr(Yu(1,1)) +
      Sqr(g1))*ZH(gI1,1)*ZH(gI2,1)) + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*
      ((Sqr(g1) - 5*Sqr(g2))*ZH(gI1,0)*ZH(gI2,0) - (20*AbsSqr(Yu(1,1)) + Sqr(g1) -
      5*Sqr(g2))*ZH(gI1,1)*ZH(gI2,1)));

   return result;
}

std::complex<double> CLASSNAME::CpHpmUScconjHpmconjUSc(int gI1, int gO1, int gI2, int gO2) const
{
   const std::complex<double> result = 0.05*(-4*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*(Sqr(g1)*ZP(gI1,0)*ZP(gI2,0) - (-5*AbsSqr(Yu(1,1)) +
      Sqr(g1))*ZP(gI1,1)*ZP(gI2,1)) + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*
      ((-20*AbsSqr(Yd(1,1)) + Sqr(g1) + 5*Sqr(g2))*ZP(gI1,0)*ZP(gI2,0) - (Sqr(g1)
      + 5*Sqr(g2))*ZP(gI1,1)*ZP(gI2,1)));

   return result;
}

std::complex<double> CLASSNAME::CpUScconjUScconjSbSb(int gO1, int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZB(gI2,0))*(4*KroneckerDelta(
      1,gO1)*KroneckerDelta(1,gO2)*Sqr(g1) - KroneckerDelta(0,gO1)*KroneckerDelta(
      0,gO2)*(Sqr(g1) - 15*Sqr(g2)))*ZB(gI1,0) - 2*Conj(ZB(gI2,1))*(KroneckerDelta
      (0,gO1)*KroneckerDelta(0,gO2) - 4*KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2
      ))*Sqr(g1)*ZB(gI1,1));

   return result;
}

std::complex<double> CLASSNAME::CpUScconjUScconjScSc(int gO1, int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = 0.06666666666666667*(Conj(ZC(gI2,1))*(-4
      *KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2)*(4*Sqr(g1) + 5*Sqr(g3))*ZC(gI1,
      1) + KroneckerDelta(0,gO1)*(KroneckerDelta(1,gO2)*(-45*AbsSqr(Yu(1,1)) + Sqr
      (g1) + 20*Sqr(g3))*ZC(gI1,0) + 3*KroneckerDelta(0,gO2)*(-5*AbsSqr(Yu(1,1)) +
      Sqr(g1))*ZC(gI1,1))) - Conj(ZC(gI2,0))*(KroneckerDelta(0,gO1)*
      KroneckerDelta(0,gO2)*(Sqr(g1) + 15*Sqr(g2) + 20*Sqr(g3))*ZC(gI1,0) -
      KroneckerDelta(1,gO1)*(3*KroneckerDelta(1,gO2)*(-5*AbsSqr(Yu(1,1)) + Sqr(g1)
      )*ZC(gI1,0) + KroneckerDelta(0,gO2)*(-45*AbsSqr(Yu(1,1)) + Sqr(g1) + 20*Sqr(
      g3))*ZC(gI1,1))));

   return result;
}

std::complex<double> CLASSNAME::CpUScconjUScconjSdSd(int gO1, int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZD(gI2,0))*(4*KroneckerDelta(
      1,gO1)*KroneckerDelta(1,gO2)*Sqr(g1) - KroneckerDelta(0,gO1)*KroneckerDelta(
      0,gO2)*(Sqr(g1) - 15*Sqr(g2)))*ZD(gI1,0) - 2*Conj(ZD(gI2,1))*(KroneckerDelta
      (0,gO1)*KroneckerDelta(0,gO2) - 4*KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2
      ))*Sqr(g1)*ZD(gI1,1));

   return result;
}

std::complex<double> CLASSNAME::CpUScconjUScconjSsSs(int gO1, int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZS(gI2,0))*(4*KroneckerDelta(
      1,gO1)*KroneckerDelta(1,gO2)*(-5*AbsSqr(Yu(1,1)) + Sqr(g1)) - KroneckerDelta
      (0,gO1)*KroneckerDelta(0,gO2)*(Sqr(g1) - 5*Sqr(g2)))*ZS(gI1,0) - 2*Conj(ZS(
      gI2,1))*(-4*KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2)*Sqr(g1) +
      KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*(10*AbsSqr(Yd(1,1)) + Sqr(g1)))*
      ZS(gI1,1));

   return result;
}

std::complex<double> CLASSNAME::CpUScconjUScconjStSt(int gO1, int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(4*Conj(ZT(gI2,1))*(-15*Conj(Yu(2,2
      ))*KroneckerDelta(0,gO1)*KroneckerDelta(1,gO2)*Yu(1,1)*ZT(gI1,0) + (
      KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2) - 4*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2))*Sqr(g1)*ZT(gI1,1)) - Conj(ZT(gI2,0))*(KroneckerDelta(
      0,gO1)*KroneckerDelta(0,gO2)*(Sqr(g1) + 15*Sqr(g2))*ZT(gI1,0) - 4*
      KroneckerDelta(1,gO1)*(KroneckerDelta(1,gO2)*Sqr(g1)*ZT(gI1,0) - 15*Conj(Yu(
      1,1))*KroneckerDelta(0,gO2)*Yu(2,2)*ZT(gI1,1))));

   return result;
}

std::complex<double> CLASSNAME::CpUScconjUScconjSuSu(int gO1, int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(4*Conj(ZU(gI2,1))*(-15*Conj(Yu(0,0
      ))*KroneckerDelta(0,gO1)*KroneckerDelta(1,gO2)*Yu(1,1)*ZU(gI1,0) + (
      KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2) - 4*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2))*Sqr(g1)*ZU(gI1,1)) - Conj(ZU(gI2,0))*(KroneckerDelta(
      0,gO1)*KroneckerDelta(0,gO2)*(Sqr(g1) + 15*Sqr(g2))*ZU(gI1,0) - 4*
      KroneckerDelta(1,gO1)*(KroneckerDelta(1,gO2)*Sqr(g1)*ZU(gI1,0) - 15*Conj(Yu(
      1,1))*KroneckerDelta(0,gO2)*Yu(0,0)*ZU(gI1,1))));

   return result;
}

std::complex<double> CLASSNAME::CpUScSeconjUScconjSe(int gO1, int gI1, int gO2, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZE(gI1,0))*(-4*KroneckerDelta
      (1,gO1)*KroneckerDelta(1,gO2)*Sqr(g1) + KroneckerDelta(0,gO1)*KroneckerDelta
      (0,gO2)*(Sqr(g1) + 5*Sqr(g2)))*ZE(gI2,0) - 2*Conj(ZE(gI1,1))*(KroneckerDelta
      (0,gO1)*KroneckerDelta(0,gO2) - 4*KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2
      ))*Sqr(g1)*ZE(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpUScSmconjUScconjSm(int gO1, int gI1, int gO2, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZM(gI1,0))*(-4*KroneckerDelta
      (1,gO1)*KroneckerDelta(1,gO2)*Sqr(g1) + KroneckerDelta(0,gO1)*KroneckerDelta
      (0,gO2)*(Sqr(g1) + 5*Sqr(g2)))*ZM(gI2,0) - 2*Conj(ZM(gI1,1))*(KroneckerDelta
      (0,gO1)*KroneckerDelta(0,gO2) - 4*KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2
      ))*Sqr(g1)*ZM(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpUScStauconjUScconjStau(int gO1, int gI1, int gO2, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZTau(gI1,0))*(-4*
      KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2)*Sqr(g1) + KroneckerDelta(0,gO1)*
      KroneckerDelta(0,gO2)*(Sqr(g1) + 5*Sqr(g2)))*ZTau(gI2,0) - 2*Conj(ZTau(gI1,1
      ))*(KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2) - 4*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2))*Sqr(g1)*ZTau(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpAhScconjUSc(int gI2, int gI1, int gO2) const
{
   const std::complex<double> result = std::complex<double>(0.,
      0.7071067811865475)*(Conj(Yu(1,1))*Conj(ZC(gI1,1))*KroneckerDelta(0,gO2)*Mu*
      ZA(gI2,0) - Conj(Mu)*Conj(ZC(gI1,0))*KroneckerDelta(1,gO2)*Yu(1,1)*ZA(gI2,0)
      + ZA(gI2,1)*(Conj(ZC(gI1,1))*Conj(TYu(1,1))*KroneckerDelta(0,gO2) - Conj(ZC
      (gI1,0))*KroneckerDelta(1,gO2)*TYu(1,1)));

   return result;
}

std::complex<double> CLASSNAME::CphhScconjUSc(int gI2, int gI1, int gO2) const
{
   const std::complex<double> result = 0.05*(2*Conj(ZC(gI1,1))*(
      -7.0710678118654755*Conj(TYu(1,1))*KroneckerDelta(0,gO2)*ZH(gI2,1) + 2*
      KroneckerDelta(1,gO2)*Sqr(g1)*(-(vd*ZH(gI2,0)) + vu*ZH(gI2,1)) + 5*Conj(Yu(1
      ,1))*(1.4142135623730951*KroneckerDelta(0,gO2)*Mu*ZH(gI2,0) - 2*vu*
      KroneckerDelta(1,gO2)*Yu(1,1)*ZH(gI2,1))) + Conj(ZC(gI1,0))*(KroneckerDelta(
      0,gO2)*(vd*(Sqr(g1) - 5*Sqr(g2))*ZH(gI2,0) - vu*(20*AbsSqr(Yu(1,1)) + Sqr(g1
      ) - 5*Sqr(g2))*ZH(gI2,1)) + 14.142135623730951*KroneckerDelta(1,gO2)*(Conj(
      Mu)*Yu(1,1)*ZH(gI2,0) - ZH(gI2,1)*TYu(1,1))));

   return result;
}

std::complex<double> CLASSNAME::CpSsconjHpmconjUSc(int gI2, int gI1, int gO2) const
{
   const std::complex<double> result = 0.5*Conj(ZS(gI2,1))*(2*Conj(TYd(1,1))*
      KroneckerDelta(0,gO2)*ZP(gI1,0) + Conj(Yd(1,1))*(2*KroneckerDelta(0,gO2)*Mu*
      ZP(gI1,1) + 1.4142135623730951*KroneckerDelta(1,gO2)*Yu(1,1)*(vu*ZP(gI1,0) +
      vd*ZP(gI1,1)))) - 0.25*Conj(ZS(gI2,0))*(1.4142135623730951*KroneckerDelta(0
      ,gO2)*(vd*(-2*AbsSqr(Yd(1,1)) + Sqr(g2))*ZP(gI1,0) + vu*(-2*AbsSqr(Yu(1,1))
      + Sqr(g2))*ZP(gI1,1)) - 4*KroneckerDelta(1,gO2)*(Conj(Mu)*Yu(1,1)*ZP(gI1,0)
      + ZP(gI1,1)*TYu(1,1)));

   return result;
}

std::complex<double> CLASSNAME::CpbarChaFsconjUScPR(int gI1, int gO2) const
{
   const std::complex<double> result = Conj(Yd(1,1))*KroneckerDelta(0,gO2)*UM(
      gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpbarChaFsconjUScPL(int gI1, int gO1) const
{
   const std::complex<double> result = -(g2*Conj(UP(gI1,0))*KroneckerDelta(0,
      gO1)) + Conj(UP(gI1,1))*KroneckerDelta(1,gO1)*Yu(1,1);

   return result;
}

std::complex<double> CLASSNAME::CpScconjUScVG(int gI2, int gO2) const
{
   const std::complex<double> result = IF(gI2 < 2,g3*Conj(ZC(gI2,gO2)),0);

   return result;
}

std::complex<double> CLASSNAME::CpScconjUScVP(int gI2, int gO2) const
{
   const std::complex<double> result = 0.03333333333333333*(15.491933384829668*
      g1*Conj(ZC(gI2,1))*Cos(ThetaW())*KroneckerDelta(1,gO2) + Conj(ZC(gI2,0))*
      KroneckerDelta(0,gO2)*(3.872983346207417*g1*Cos(ThetaW()) + 15*g2*Sin(ThetaW
      ())));

   return result;
}

std::complex<double> CLASSNAME::CpScconjUScVZ(int gI2, int gO2) const
{
   const std::complex<double> result = 0.03333333333333333*(-15.491933384829668
      *g1*Conj(ZC(gI2,1))*KroneckerDelta(1,gO2)*Sin(ThetaW()) + Conj(ZC(gI2,0))*
      KroneckerDelta(0,gO2)*(15*g2*Cos(ThetaW()) - 3.872983346207417*g1*Sin(ThetaW
      ())));

   return result;
}

std::complex<double> CLASSNAME::CpSsconjUScconjVWm(int gI2, int gO2) const
{
   const std::complex<double> result = 0.7071067811865475*g2*Conj(ZS(gI2,0))*
      KroneckerDelta(0,gO2);

   return result;
}

std::complex<double> CLASSNAME::CpChiFcconjUScPR(int gI2, int gO2) const
{
   const std::complex<double> result = 0.7302967433402214*g1*KroneckerDelta(1,
      gO2)*ZN(gI2,0) - Conj(Yu(1,1))*KroneckerDelta(0,gO2)*ZN(gI2,3);

   return result;
}

std::complex<double> CLASSNAME::CpChiFcconjUScPL(int gI2, int gO1) const
{
   const std::complex<double> result = -0.18257418583505536*g1*Conj(ZN(gI2,0))*
      KroneckerDelta(0,gO1) - 0.7071067811865475*g2*Conj(ZN(gI2,1))*KroneckerDelta
      (0,gO1) - Conj(ZN(gI2,3))*KroneckerDelta(1,gO1)*Yu(1,1);

   return result;
}

std::complex<double> CLASSNAME::CpGluFcconjUScPR(int gO2) const
{
   const std::complex<double> result = 1.4142135623730951*g3*Conj(PhaseGlu)*
      KroneckerDelta(1,gO2);

   return result;
}

std::complex<double> CLASSNAME::CpGluFcconjUScPL(int gO1) const
{
   const std::complex<double> result = -1.4142135623730951*g3*PhaseGlu*
      KroneckerDelta(0,gO1);

   return result;
}

std::complex<double> CLASSNAME::CpSveLUSbconjSveLconjUSb(int gO1, int gO2) const
{
   const std::complex<double> result = 0.05*(2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*Sqr(g1) + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*
      (Sqr(g1) + 5*Sqr(g2)));

   return result;
}

std::complex<double> CLASSNAME::CpSvmLUSbconjSvmLconjUSb(int gO1, int gO2) const
{
   const std::complex<double> result = 0.05*(2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*Sqr(g1) + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*
      (Sqr(g1) + 5*Sqr(g2)));

   return result;
}

std::complex<double> CLASSNAME::CpSvtLUSbconjSvtLconjUSb(int gO1, int gO2) const
{
   const std::complex<double> result = 0.05*(2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*Sqr(g1) + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*
      (Sqr(g1) + 5*Sqr(g2)));

   return result;
}

std::complex<double> CLASSNAME::CpUSbconjUSbVZVZ(int gO1, int gO2) const
{
   const std::complex<double> result = 0.03333333333333333*(KroneckerDelta(0,
      gO1)*KroneckerDelta(0,gO2)*(g1*Sin(ThetaW())*(7.745966692414834*g2*Cos(
      ThetaW()) + g1*Sin(ThetaW())) + 15*Sqr(g2)*Sqr(Cos(ThetaW()))) + 4*
      KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2)*Sqr(g1)*Sqr(Sin(ThetaW())));

   return result;
}

double CLASSNAME::CpUSbconjUSbconjVWmVWm(int gO1, int gO2) const
{
   const double result = 0.5*KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*Sqr(g2
      );

   return result;
}

std::complex<double> CLASSNAME::CpAhAhUSbconjUSb(int gI1, int gI2, int gO1, int gO2) const
{
   const std::complex<double> result = 0.05*(2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*((-10*AbsSqr(Yd(2,2)) + Sqr(g1))*ZA(gI1,0)*ZA(gI2,0) -
      Sqr(g1)*ZA(gI1,1)*ZA(gI2,1)) + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*
      ((-20*AbsSqr(Yd(2,2)) + Sqr(g1) + 5*Sqr(g2))*ZA(gI1,0)*ZA(gI2,0) - (Sqr(g1)
      + 5*Sqr(g2))*ZA(gI1,1)*ZA(gI2,1)));

   return result;
}

std::complex<double> CLASSNAME::CphhhhUSbconjUSb(int gI1, int gI2, int gO1, int gO2) const
{
   const std::complex<double> result = 0.05*(2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*((-10*AbsSqr(Yd(2,2)) + Sqr(g1))*ZH(gI1,0)*ZH(gI2,0) -
      Sqr(g1)*ZH(gI1,1)*ZH(gI2,1)) + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*
      ((-20*AbsSqr(Yd(2,2)) + Sqr(g1) + 5*Sqr(g2))*ZH(gI1,0)*ZH(gI2,0) - (Sqr(g1)
      + 5*Sqr(g2))*ZH(gI1,1)*ZH(gI2,1)));

   return result;
}

std::complex<double> CLASSNAME::CpHpmUSbconjHpmconjUSb(int gI1, int gO1, int gI2, int gO2) const
{
   const std::complex<double> result = 0.05*(2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*((-10*AbsSqr(Yd(2,2)) + Sqr(g1))*ZP(gI1,0)*ZP(gI2,0) -
      Sqr(g1)*ZP(gI1,1)*ZP(gI2,1)) + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*
      ((Sqr(g1) - 5*Sqr(g2))*ZP(gI1,0)*ZP(gI2,0) - (20*AbsSqr(Yu(2,2)) + Sqr(g1) -
      5*Sqr(g2))*ZP(gI1,1)*ZP(gI2,1)));

   return result;
}

std::complex<double> CLASSNAME::CpUSbconjUSbconjSbSb(int gO1, int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = 0.03333333333333333*(-(Conj(ZB(gI2,1))*(
      8*KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2)*(Sqr(g1) + 5*Sqr(g3))*ZB(gI1,1
      ) + KroneckerDelta(0,gO1)*(KroneckerDelta(1,gO2)*(90*AbsSqr(Yd(2,2)) + Sqr(
      g1) - 40*Sqr(g3))*ZB(gI1,0) + 3*KroneckerDelta(0,gO2)*(10*AbsSqr(Yd(2,2)) +
      Sqr(g1))*ZB(gI1,1)))) - Conj(ZB(gI2,0))*(2*KroneckerDelta(0,gO1)*
      KroneckerDelta(0,gO2)*(Sqr(g1) + 15*Sqr(g2) + 20*Sqr(g3))*ZB(gI1,0) +
      KroneckerDelta(1,gO1)*(3*KroneckerDelta(1,gO2)*(10*AbsSqr(Yd(2,2)) + Sqr(g1)
      )*ZB(gI1,0) + KroneckerDelta(0,gO2)*(90*AbsSqr(Yd(2,2)) + Sqr(g1) - 40*Sqr(
      g3))*ZB(gI1,1))));

   return result;
}

std::complex<double> CLASSNAME::CpUSbconjUSbconjScSc(int gO1, int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(-(Conj(ZC(gI2,0))*(2*
      KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2)*Sqr(g1) + KroneckerDelta(0,gO1)*
      KroneckerDelta(0,gO2)*(Sqr(g1) - 15*Sqr(g2)))*ZC(gI1,0)) + 4*Conj(ZC(gI2,1))
      *(KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2) + 2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2))*Sqr(g1)*ZC(gI1,1));

   return result;
}

std::complex<double> CLASSNAME::CpUSbconjUSbconjSdSd(int gO1, int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(-2*Conj(ZD(gI2,1))*(30*Conj(Yd(0,0
      ))*KroneckerDelta(0,gO1)*KroneckerDelta(1,gO2)*Yd(2,2)*ZD(gI1,0) + (
      KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2) + 2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2))*Sqr(g1)*ZD(gI1,1)) - Conj(ZD(gI2,0))*(KroneckerDelta(
      0,gO1)*KroneckerDelta(0,gO2)*(Sqr(g1) + 15*Sqr(g2))*ZD(gI1,0) + 2*
      KroneckerDelta(1,gO1)*(KroneckerDelta(1,gO2)*Sqr(g1)*ZD(gI1,0) + 30*Conj(Yd(
      2,2))*KroneckerDelta(0,gO2)*Yd(0,0)*ZD(gI1,1))));

   return result;
}

std::complex<double> CLASSNAME::CpUSbconjUSbconjSsSs(int gO1, int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(-2*Conj(ZS(gI2,1))*(30*Conj(Yd(1,1
      ))*KroneckerDelta(0,gO1)*KroneckerDelta(1,gO2)*Yd(2,2)*ZS(gI1,0) + (
      KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2) + 2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2))*Sqr(g1)*ZS(gI1,1)) - Conj(ZS(gI2,0))*(KroneckerDelta(
      0,gO1)*KroneckerDelta(0,gO2)*(Sqr(g1) + 15*Sqr(g2))*ZS(gI1,0) + 2*
      KroneckerDelta(1,gO1)*(KroneckerDelta(1,gO2)*Sqr(g1)*ZS(gI1,0) + 30*Conj(Yd(
      2,2))*KroneckerDelta(0,gO2)*Yd(1,1)*ZS(gI1,1))));

   return result;
}

std::complex<double> CLASSNAME::CpUSbconjUSbconjStSt(int gO1, int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(-(Conj(ZT(gI2,0))*(2*
      KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2)*(10*AbsSqr(Yd(2,2)) + Sqr(g1)) +
      KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*(Sqr(g1) - 5*Sqr(g2)))*ZT(gI1,0
      )) + 4*Conj(ZT(gI2,1))*(2*KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2)*Sqr(g1
      ) + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*(-5*AbsSqr(Yu(2,2)) + Sqr(g1
      )))*ZT(gI1,1));

   return result;
}

std::complex<double> CLASSNAME::CpUSbconjUSbconjSuSu(int gO1, int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(-(Conj(ZU(gI2,0))*(2*
      KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2)*Sqr(g1) + KroneckerDelta(0,gO1)*
      KroneckerDelta(0,gO2)*(Sqr(g1) - 15*Sqr(g2)))*ZU(gI1,0)) + 4*Conj(ZU(gI2,1))
      *(KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2) + 2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2))*Sqr(g1)*ZU(gI1,1));

   return result;
}

std::complex<double> CLASSNAME::CpUSbSeconjUSbconjSe(int gO1, int gI1, int gO2, int gI2) const
{
   const std::complex<double> result = 0.05*(-2*Conj(ZE(gI1,1))*(10*Conj(Ye(0,0
      ))*KroneckerDelta(0,gO1)*KroneckerDelta(1,gO2)*Yd(2,2)*ZE(gI2,0) + (
      KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2) + 2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2))*Sqr(g1)*ZE(gI2,1)) + Conj(ZE(gI1,0))*(KroneckerDelta(
      0,gO1)*KroneckerDelta(0,gO2)*(Sqr(g1) - 5*Sqr(g2))*ZE(gI2,0) + 2*
      KroneckerDelta(1,gO1)*(KroneckerDelta(1,gO2)*Sqr(g1)*ZE(gI2,0) - 10*Conj(Yd(
      2,2))*KroneckerDelta(0,gO2)*Ye(0,0)*ZE(gI2,1))));

   return result;
}

std::complex<double> CLASSNAME::CpUSbSmconjUSbconjSm(int gO1, int gI1, int gO2, int gI2) const
{
   const std::complex<double> result = 0.05*(-2*Conj(ZM(gI1,1))*(10*Conj(Ye(1,1
      ))*KroneckerDelta(0,gO1)*KroneckerDelta(1,gO2)*Yd(2,2)*ZM(gI2,0) + (
      KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2) + 2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2))*Sqr(g1)*ZM(gI2,1)) + Conj(ZM(gI1,0))*(KroneckerDelta(
      0,gO1)*KroneckerDelta(0,gO2)*(Sqr(g1) - 5*Sqr(g2))*ZM(gI2,0) + 2*
      KroneckerDelta(1,gO1)*(KroneckerDelta(1,gO2)*Sqr(g1)*ZM(gI2,0) - 10*Conj(Yd(
      2,2))*KroneckerDelta(0,gO2)*Ye(1,1)*ZM(gI2,1))));

   return result;
}

std::complex<double> CLASSNAME::CpUSbStauconjUSbconjStau(int gO1, int gI1, int gO2, int gI2) const
{
   const std::complex<double> result = 0.05*(-2*Conj(ZTau(gI1,1))*(10*Conj(Ye(2
      ,2))*KroneckerDelta(0,gO1)*KroneckerDelta(1,gO2)*Yd(2,2)*ZTau(gI2,0) + (
      KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2) + 2*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2))*Sqr(g1)*ZTau(gI2,1)) + Conj(ZTau(gI1,0))*(
      KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*(Sqr(g1) - 5*Sqr(g2))*ZTau(gI2,0
      ) + 2*KroneckerDelta(1,gO1)*(KroneckerDelta(1,gO2)*Sqr(g1)*ZTau(gI2,0) - 10*
      Conj(Yd(2,2))*KroneckerDelta(0,gO2)*Ye(2,2)*ZTau(gI2,1))));

   return result;
}

std::complex<double> CLASSNAME::CpAhSbconjUSb(int gI2, int gI1, int gO2) const
{
   const std::complex<double> result = std::complex<double>(0.,
      0.7071067811865475)*(Conj(ZB(gI1,1))*KroneckerDelta(0,gO2)*(Conj(TYd(2,2))*
      ZA(gI2,0) + Conj(Yd(2,2))*Mu*ZA(gI2,1)) - Conj(ZB(gI1,0))*KroneckerDelta(1,
      gO2)*(Conj(Mu)*Yd(2,2)*ZA(gI2,1) + ZA(gI2,0)*TYd(2,2)));

   return result;
}

std::complex<double> CLASSNAME::CphhSbconjUSb(int gI2, int gI1, int gO2) const
{
   const std::complex<double> result = 0.05*(-2*Conj(ZB(gI1,1))*(
      7.0710678118654755*Conj(TYd(2,2))*KroneckerDelta(0,gO2)*ZH(gI2,0) -
      7.0710678118654755*Conj(Yd(2,2))*KroneckerDelta(0,gO2)*Mu*ZH(gI2,1) +
      KroneckerDelta(1,gO2)*(-(vd*(-10*AbsSqr(Yd(2,2)) + Sqr(g1))*ZH(gI2,0)) + vu*
      Sqr(g1)*ZH(gI2,1))) + Conj(ZB(gI1,0))*(KroneckerDelta(0,gO2)*(vd*(-20*AbsSqr
      (Yd(2,2)) + Sqr(g1) + 5*Sqr(g2))*ZH(gI2,0) - vu*(Sqr(g1) + 5*Sqr(g2))*ZH(gI2
      ,1)) + 14.142135623730951*KroneckerDelta(1,gO2)*(Conj(Mu)*Yd(2,2)*ZH(gI2,1)
      - ZH(gI2,0)*TYd(2,2))));

   return result;
}

std::complex<double> CLASSNAME::CpHpmStconjUSb(int gI2, int gI1, int gO2) const
{
   const std::complex<double> result = 0.5*Conj(ZT(gI1,1))*(2*Conj(TYu(2,2))*
      KroneckerDelta(0,gO2)*ZP(gI2,1) + Conj(Yu(2,2))*(2*KroneckerDelta(0,gO2)*Mu*
      ZP(gI2,0) + 1.4142135623730951*KroneckerDelta(1,gO2)*Yd(2,2)*(vu*ZP(gI2,0) +
      vd*ZP(gI2,1)))) - 0.25*Conj(ZT(gI1,0))*(1.4142135623730951*KroneckerDelta(0
      ,gO2)*(vd*(-2*AbsSqr(Yd(2,2)) + Sqr(g2))*ZP(gI2,0) + vu*(-2*AbsSqr(Yu(2,2))
      + Sqr(g2))*ZP(gI2,1)) - 4*KroneckerDelta(1,gO2)*(Conj(Mu)*Yd(2,2)*ZP(gI2,1)
      + ZP(gI2,0)*TYd(2,2)));

   return result;
}

std::complex<double> CLASSNAME::CpSbconjUSbVG(int gI2, int gO2) const
{
   const std::complex<double> result = IF(gI2 < 2,g3*Conj(ZB(gI2,gO2)),0);

   return result;
}

std::complex<double> CLASSNAME::CpSbconjUSbVP(int gI2, int gO2) const
{
   const std::complex<double> result = 0.03333333333333333*(-7.745966692414834*
      g1*Conj(ZB(gI2,1))*Cos(ThetaW())*KroneckerDelta(1,gO2) + Conj(ZB(gI2,0))*
      KroneckerDelta(0,gO2)*(3.872983346207417*g1*Cos(ThetaW()) - 15*g2*Sin(ThetaW
      ())));

   return result;
}

std::complex<double> CLASSNAME::CpSbconjUSbVZ(int gI2, int gO2) const
{
   const std::complex<double> result = 0.2581988897471611*g1*Conj(ZB(gI2,1))*
      KroneckerDelta(1,gO2)*Sin(ThetaW()) - 0.03333333333333333*Conj(ZB(gI2,0))*
      KroneckerDelta(0,gO2)*(15*g2*Cos(ThetaW()) + 3.872983346207417*g1*Sin(ThetaW
      ()));

   return result;
}

std::complex<double> CLASSNAME::CpStconjUSbVWm(int gI2, int gO2) const
{
   const std::complex<double> result = 0.7071067811865475*g2*Conj(ZT(gI2,0))*
      KroneckerDelta(0,gO2);

   return result;
}

std::complex<double> CLASSNAME::CpFtChaconjUSbPR(int gI2, int gO2) const
{
   const std::complex<double> result = Conj(Yu(2,2))*KroneckerDelta(0,gO2)*UP(
      gI2,1);

   return result;
}

std::complex<double> CLASSNAME::CpFtChaconjUSbPL(int gI2, int gO1) const
{
   const std::complex<double> result = -(g2*Conj(UM(gI2,0))*KroneckerDelta(0,
      gO1)) + Conj(UM(gI2,1))*KroneckerDelta(1,gO1)*Yd(2,2);

   return result;
}

std::complex<double> CLASSNAME::CpChiFbconjUSbPR(int gI2, int gO2) const
{
   const std::complex<double> result = -0.3651483716701107*g1*KroneckerDelta(1,
      gO2)*ZN(gI2,0) - Conj(Yd(2,2))*KroneckerDelta(0,gO2)*ZN(gI2,2);

   return result;
}

std::complex<double> CLASSNAME::CpChiFbconjUSbPL(int gI2, int gO1) const
{
   const std::complex<double> result = -0.18257418583505536*g1*Conj(ZN(gI2,0))*
      KroneckerDelta(0,gO1) + 0.7071067811865475*g2*Conj(ZN(gI2,1))*KroneckerDelta
      (0,gO1) - Conj(ZN(gI2,2))*KroneckerDelta(1,gO1)*Yd(2,2);

   return result;
}

std::complex<double> CLASSNAME::CpGluFbconjUSbPR(int gO2) const
{
   const std::complex<double> result = 1.4142135623730951*g3*Conj(PhaseGlu)*
      KroneckerDelta(1,gO2);

   return result;
}

std::complex<double> CLASSNAME::CpGluFbconjUSbPL(int gO1) const
{
   const std::complex<double> result = -1.4142135623730951*g3*PhaseGlu*
      KroneckerDelta(0,gO1);

   return result;
}

std::complex<double> CLASSNAME::CpSveLUStconjSveLconjUSt(int gO1, int gO2) const
{
   const std::complex<double> result = 0.05*(-4*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*Sqr(g1) + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*
      (Sqr(g1) - 5*Sqr(g2)));

   return result;
}

std::complex<double> CLASSNAME::CpSvmLUStconjSvmLconjUSt(int gO1, int gO2) const
{
   const std::complex<double> result = 0.05*(-4*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*Sqr(g1) + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*
      (Sqr(g1) - 5*Sqr(g2)));

   return result;
}

std::complex<double> CLASSNAME::CpSvtLUStconjSvtLconjUSt(int gO1, int gO2) const
{
   const std::complex<double> result = 0.05*(-4*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*Sqr(g1) + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*
      (Sqr(g1) - 5*Sqr(g2)));

   return result;
}

std::complex<double> CLASSNAME::CpUStconjUStVZVZ(int gO1, int gO2) const
{
   const std::complex<double> result = 0.03333333333333333*(16*KroneckerDelta(1
      ,gO1)*KroneckerDelta(1,gO2)*Sqr(g1)*Sqr(Sin(ThetaW())) + KroneckerDelta(0,
      gO1)*KroneckerDelta(0,gO2)*(-7.745966692414834*g1*g2*Cos(ThetaW())*Sin(
      ThetaW()) + 15*Sqr(g2)*Sqr(Cos(ThetaW())) + Sqr(g1)*Sqr(Sin(ThetaW()))));

   return result;
}

double CLASSNAME::CpUStconjUStconjVWmVWm(int gO1, int gO2) const
{
   const double result = 0.5*KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*Sqr(g2
      );

   return result;
}

std::complex<double> CLASSNAME::CpAhAhUStconjUSt(int gI1, int gI2, int gO1, int gO2) const
{
   const std::complex<double> result = 0.05*(-4*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*(Sqr(g1)*ZA(gI1,0)*ZA(gI2,0) - (-5*AbsSqr(Yu(2,2)) +
      Sqr(g1))*ZA(gI1,1)*ZA(gI2,1)) + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*
      ((Sqr(g1) - 5*Sqr(g2))*ZA(gI1,0)*ZA(gI2,0) - (20*AbsSqr(Yu(2,2)) + Sqr(g1) -
      5*Sqr(g2))*ZA(gI1,1)*ZA(gI2,1)));

   return result;
}

std::complex<double> CLASSNAME::CphhhhUStconjUSt(int gI1, int gI2, int gO1, int gO2) const
{
   const std::complex<double> result = 0.05*(-4*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*(Sqr(g1)*ZH(gI1,0)*ZH(gI2,0) - (-5*AbsSqr(Yu(2,2)) +
      Sqr(g1))*ZH(gI1,1)*ZH(gI2,1)) + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*
      ((Sqr(g1) - 5*Sqr(g2))*ZH(gI1,0)*ZH(gI2,0) - (20*AbsSqr(Yu(2,2)) + Sqr(g1) -
      5*Sqr(g2))*ZH(gI1,1)*ZH(gI2,1)));

   return result;
}

std::complex<double> CLASSNAME::CpHpmUStconjHpmconjUSt(int gI1, int gO1, int gI2, int gO2) const
{
   const std::complex<double> result = 0.05*(-4*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*(Sqr(g1)*ZP(gI1,0)*ZP(gI2,0) - (-5*AbsSqr(Yu(2,2)) +
      Sqr(g1))*ZP(gI1,1)*ZP(gI2,1)) + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*
      ((-20*AbsSqr(Yd(2,2)) + Sqr(g1) + 5*Sqr(g2))*ZP(gI1,0)*ZP(gI2,0) - (Sqr(g1)
      + 5*Sqr(g2))*ZP(gI1,1)*ZP(gI2,1)));

   return result;
}

std::complex<double> CLASSNAME::CpSeUStconjSeconjUSt(int gI1, int gO1, int gI2, int gO2) const
{
   const std::complex<double> result = 0.05*(Conj(ZE(gI1,0))*(-4*KroneckerDelta
      (1,gO1)*KroneckerDelta(1,gO2)*Sqr(g1) + KroneckerDelta(0,gO1)*KroneckerDelta
      (0,gO2)*(Sqr(g1) + 5*Sqr(g2)))*ZE(gI2,0) - 2*Conj(ZE(gI1,1))*(KroneckerDelta
      (0,gO1)*KroneckerDelta(0,gO2) - 4*KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2
      ))*Sqr(g1)*ZE(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpSmUStconjSmconjUSt(int gI1, int gO1, int gI2, int gO2) const
{
   const std::complex<double> result = 0.05*(Conj(ZM(gI1,0))*(-4*KroneckerDelta
      (1,gO1)*KroneckerDelta(1,gO2)*Sqr(g1) + KroneckerDelta(0,gO1)*KroneckerDelta
      (0,gO2)*(Sqr(g1) + 5*Sqr(g2)))*ZM(gI2,0) - 2*Conj(ZM(gI1,1))*(KroneckerDelta
      (0,gO1)*KroneckerDelta(0,gO2) - 4*KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2
      ))*Sqr(g1)*ZM(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpUStconjUStconjSbSb(int gO1, int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZB(gI2,0))*(4*KroneckerDelta(
      1,gO1)*KroneckerDelta(1,gO2)*(-5*AbsSqr(Yu(2,2)) + Sqr(g1)) - KroneckerDelta
      (0,gO1)*KroneckerDelta(0,gO2)*(Sqr(g1) - 5*Sqr(g2)))*ZB(gI1,0) - 2*Conj(ZB(
      gI2,1))*(-4*KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2)*Sqr(g1) +
      KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*(10*AbsSqr(Yd(2,2)) + Sqr(g1)))*
      ZB(gI1,1));

   return result;
}

std::complex<double> CLASSNAME::CpUStconjUStconjScSc(int gO1, int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(4*Conj(ZC(gI2,1))*(-15*Conj(Yu(1,1
      ))*KroneckerDelta(0,gO1)*KroneckerDelta(1,gO2)*Yu(2,2)*ZC(gI1,0) + (
      KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2) - 4*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2))*Sqr(g1)*ZC(gI1,1)) - Conj(ZC(gI2,0))*(KroneckerDelta(
      0,gO1)*KroneckerDelta(0,gO2)*(Sqr(g1) + 15*Sqr(g2))*ZC(gI1,0) - 4*
      KroneckerDelta(1,gO1)*(KroneckerDelta(1,gO2)*Sqr(g1)*ZC(gI1,0) - 15*Conj(Yu(
      2,2))*KroneckerDelta(0,gO2)*Yu(1,1)*ZC(gI1,1))));

   return result;
}

std::complex<double> CLASSNAME::CpUStconjUStconjSdSd(int gO1, int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZD(gI2,0))*(4*KroneckerDelta(
      1,gO1)*KroneckerDelta(1,gO2)*Sqr(g1) - KroneckerDelta(0,gO1)*KroneckerDelta(
      0,gO2)*(Sqr(g1) - 15*Sqr(g2)))*ZD(gI1,0) - 2*Conj(ZD(gI2,1))*(KroneckerDelta
      (0,gO1)*KroneckerDelta(0,gO2) - 4*KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2
      ))*Sqr(g1)*ZD(gI1,1));

   return result;
}

std::complex<double> CLASSNAME::CpUStconjUStconjSsSs(int gO1, int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZS(gI2,0))*(4*KroneckerDelta(
      1,gO1)*KroneckerDelta(1,gO2)*Sqr(g1) - KroneckerDelta(0,gO1)*KroneckerDelta(
      0,gO2)*(Sqr(g1) - 15*Sqr(g2)))*ZS(gI1,0) - 2*Conj(ZS(gI2,1))*(KroneckerDelta
      (0,gO1)*KroneckerDelta(0,gO2) - 4*KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2
      ))*Sqr(g1)*ZS(gI1,1));

   return result;
}

std::complex<double> CLASSNAME::CpUStconjUStconjStSt(int gO1, int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = 0.06666666666666667*(Conj(ZT(gI2,1))*(-4
      *KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2)*(4*Sqr(g1) + 5*Sqr(g3))*ZT(gI1,
      1) + KroneckerDelta(0,gO1)*(KroneckerDelta(1,gO2)*(-45*AbsSqr(Yu(2,2)) + Sqr
      (g1) + 20*Sqr(g3))*ZT(gI1,0) + 3*KroneckerDelta(0,gO2)*(-5*AbsSqr(Yu(2,2)) +
      Sqr(g1))*ZT(gI1,1))) - Conj(ZT(gI2,0))*(KroneckerDelta(0,gO1)*
      KroneckerDelta(0,gO2)*(Sqr(g1) + 15*Sqr(g2) + 20*Sqr(g3))*ZT(gI1,0) -
      KroneckerDelta(1,gO1)*(3*KroneckerDelta(1,gO2)*(-5*AbsSqr(Yu(2,2)) + Sqr(g1)
      )*ZT(gI1,0) + KroneckerDelta(0,gO2)*(-45*AbsSqr(Yu(2,2)) + Sqr(g1) + 20*Sqr(
      g3))*ZT(gI1,1))));

   return result;
}

std::complex<double> CLASSNAME::CpUStconjUStconjSuSu(int gO1, int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(4*Conj(ZU(gI2,1))*(-15*Conj(Yu(0,0
      ))*KroneckerDelta(0,gO1)*KroneckerDelta(1,gO2)*Yu(2,2)*ZU(gI1,0) + (
      KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2) - 4*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2))*Sqr(g1)*ZU(gI1,1)) - Conj(ZU(gI2,0))*(KroneckerDelta(
      0,gO1)*KroneckerDelta(0,gO2)*(Sqr(g1) + 15*Sqr(g2))*ZU(gI1,0) - 4*
      KroneckerDelta(1,gO1)*(KroneckerDelta(1,gO2)*Sqr(g1)*ZU(gI1,0) - 15*Conj(Yu(
      2,2))*KroneckerDelta(0,gO2)*Yu(0,0)*ZU(gI1,1))));

   return result;
}

std::complex<double> CLASSNAME::CpUStStauconjUStconjStau(int gO1, int gI1, int gO2, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZTau(gI1,0))*(-4*
      KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2)*Sqr(g1) + KroneckerDelta(0,gO1)*
      KroneckerDelta(0,gO2)*(Sqr(g1) + 5*Sqr(g2)))*ZTau(gI2,0) - 2*Conj(ZTau(gI1,1
      ))*(KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2) - 4*KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2))*Sqr(g1)*ZTau(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpAhStconjUSt(int gI2, int gI1, int gO2) const
{
   const std::complex<double> result = std::complex<double>(0.,
      0.7071067811865475)*(Conj(Yu(2,2))*Conj(ZT(gI1,1))*KroneckerDelta(0,gO2)*Mu*
      ZA(gI2,0) - Conj(Mu)*Conj(ZT(gI1,0))*KroneckerDelta(1,gO2)*Yu(2,2)*ZA(gI2,0)
      + ZA(gI2,1)*(Conj(ZT(gI1,1))*Conj(TYu(2,2))*KroneckerDelta(0,gO2) - Conj(ZT
      (gI1,0))*KroneckerDelta(1,gO2)*TYu(2,2)));

   return result;
}

std::complex<double> CLASSNAME::CphhStconjUSt(int gI2, int gI1, int gO2) const
{
   const std::complex<double> result = 0.05*(2*Conj(ZT(gI1,1))*(
      -7.0710678118654755*Conj(TYu(2,2))*KroneckerDelta(0,gO2)*ZH(gI2,1) + 2*
      KroneckerDelta(1,gO2)*Sqr(g1)*(-(vd*ZH(gI2,0)) + vu*ZH(gI2,1)) + 5*Conj(Yu(2
      ,2))*(1.4142135623730951*KroneckerDelta(0,gO2)*Mu*ZH(gI2,0) - 2*vu*
      KroneckerDelta(1,gO2)*Yu(2,2)*ZH(gI2,1))) + Conj(ZT(gI1,0))*(KroneckerDelta(
      0,gO2)*(vd*(Sqr(g1) - 5*Sqr(g2))*ZH(gI2,0) - vu*(20*AbsSqr(Yu(2,2)) + Sqr(g1
      ) - 5*Sqr(g2))*ZH(gI2,1)) + 14.142135623730951*KroneckerDelta(1,gO2)*(Conj(
      Mu)*Yu(2,2)*ZH(gI2,0) - ZH(gI2,1)*TYu(2,2))));

   return result;
}

std::complex<double> CLASSNAME::CpSbconjHpmconjUSt(int gI2, int gI1, int gO2) const
{
   const std::complex<double> result = 0.5*Conj(ZB(gI2,1))*(2*Conj(TYd(2,2))*
      KroneckerDelta(0,gO2)*ZP(gI1,0) + Conj(Yd(2,2))*(2*KroneckerDelta(0,gO2)*Mu*
      ZP(gI1,1) + 1.4142135623730951*KroneckerDelta(1,gO2)*Yu(2,2)*(vu*ZP(gI1,0) +
      vd*ZP(gI1,1)))) - 0.25*Conj(ZB(gI2,0))*(1.4142135623730951*KroneckerDelta(0
      ,gO2)*(vd*(-2*AbsSqr(Yd(2,2)) + Sqr(g2))*ZP(gI1,0) + vu*(-2*AbsSqr(Yu(2,2))
      + Sqr(g2))*ZP(gI1,1)) - 4*KroneckerDelta(1,gO2)*(Conj(Mu)*Yu(2,2)*ZP(gI1,0)
      + ZP(gI1,1)*TYu(2,2)));

   return result;
}

std::complex<double> CLASSNAME::CpbarChaFbconjUStPR(int gI1, int gO2) const
{
   const std::complex<double> result = Conj(Yd(2,2))*KroneckerDelta(0,gO2)*UM(
      gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpbarChaFbconjUStPL(int gI1, int gO1) const
{
   const std::complex<double> result = -(g2*Conj(UP(gI1,0))*KroneckerDelta(0,
      gO1)) + Conj(UP(gI1,1))*KroneckerDelta(1,gO1)*Yu(2,2);

   return result;
}

std::complex<double> CLASSNAME::CpSbconjUStconjVWm(int gI2, int gO2) const
{
   const std::complex<double> result = 0.7071067811865475*g2*Conj(ZB(gI2,0))*
      KroneckerDelta(0,gO2);

   return result;
}

std::complex<double> CLASSNAME::CpStconjUStVG(int gI2, int gO2) const
{
   const std::complex<double> result = IF(gI2 < 2,g3*Conj(ZT(gI2,gO2)),0);

   return result;
}

std::complex<double> CLASSNAME::CpStconjUStVP(int gI2, int gO2) const
{
   const std::complex<double> result = 0.03333333333333333*(15.491933384829668*
      g1*Conj(ZT(gI2,1))*Cos(ThetaW())*KroneckerDelta(1,gO2) + Conj(ZT(gI2,0))*
      KroneckerDelta(0,gO2)*(3.872983346207417*g1*Cos(ThetaW()) + 15*g2*Sin(ThetaW
      ())));

   return result;
}

std::complex<double> CLASSNAME::CpStconjUStVZ(int gI2, int gO2) const
{
   const std::complex<double> result = 0.03333333333333333*(-15.491933384829668
      *g1*Conj(ZT(gI2,1))*KroneckerDelta(1,gO2)*Sin(ThetaW()) + Conj(ZT(gI2,0))*
      KroneckerDelta(0,gO2)*(15*g2*Cos(ThetaW()) - 3.872983346207417*g1*Sin(ThetaW
      ())));

   return result;
}

std::complex<double> CLASSNAME::CpChiFtconjUStPR(int gI2, int gO2) const
{
   const std::complex<double> result = 0.7302967433402214*g1*KroneckerDelta(1,
      gO2)*ZN(gI2,0) - Conj(Yu(2,2))*KroneckerDelta(0,gO2)*ZN(gI2,3);

   return result;
}

std::complex<double> CLASSNAME::CpChiFtconjUStPL(int gI2, int gO1) const
{
   const std::complex<double> result = -0.18257418583505536*g1*Conj(ZN(gI2,0))*
      KroneckerDelta(0,gO1) - 0.7071067811865475*g2*Conj(ZN(gI2,1))*KroneckerDelta
      (0,gO1) - Conj(ZN(gI2,3))*KroneckerDelta(1,gO1)*Yu(2,2);

   return result;
}

std::complex<double> CLASSNAME::CpGluFtconjUStPR(int gO2) const
{
   const std::complex<double> result = 1.4142135623730951*g3*Conj(PhaseGlu)*
      KroneckerDelta(1,gO2);

   return result;
}

std::complex<double> CLASSNAME::CpGluFtconjUStPL(int gO1) const
{
   const std::complex<double> result = -1.4142135623730951*g3*PhaseGlu*
      KroneckerDelta(0,gO1);

   return result;
}

std::complex<double> CLASSNAME::CpSveLUhhconjSveL(int gO2) const
{
   const std::complex<double> result = -0.05*(vd*KroneckerDelta(0,gO2) - vu*
      KroneckerDelta(1,gO2))*(3*Sqr(g1) + 5*Sqr(g2));

   return result;
}

std::complex<double> CLASSNAME::CpSvmLUhhconjSvmL(int gO2) const
{
   const std::complex<double> result = -0.05*(vd*KroneckerDelta(0,gO2) - vu*
      KroneckerDelta(1,gO2))*(3*Sqr(g1) + 5*Sqr(g2));

   return result;
}

std::complex<double> CLASSNAME::CpSvtLUhhconjSvtL(int gO2) const
{
   const std::complex<double> result = -0.05*(vd*KroneckerDelta(0,gO2) - vu*
      KroneckerDelta(1,gO2))*(3*Sqr(g1) + 5*Sqr(g2));

   return result;
}

std::complex<double> CLASSNAME::CpbargWmgWmUhh(int gO1) const
{
   const std::complex<double> result = -0.25*(vd*KroneckerDelta(0,gO1) + vu*
      KroneckerDelta(1,gO1))*Sqr(g2);

   return result;
}

std::complex<double> CLASSNAME::CpbargWmCgWmCUhh(int gO1) const
{
   const std::complex<double> result = -0.25*(vd*KroneckerDelta(0,gO1) + vu*
      KroneckerDelta(1,gO1))*Sqr(g2);

   return result;
}

std::complex<double> CLASSNAME::CpbargZgZUhh(int gO1) const
{
   const std::complex<double> result = -0.025*(vd*KroneckerDelta(0,gO1) + vu*
      KroneckerDelta(1,gO1))*(7.745966692414834*g1*g2*Sin(2*ThetaW()) + 3*Sqr(g1)
      + 5*Sqr(g2) + Cos(2*ThetaW())*(-3*Sqr(g1) + 5*Sqr(g2)));

   return result;
}

std::complex<double> CLASSNAME::CpUhhVZVZ(int gO2) const
{
   const std::complex<double> result = 0.05*(vd*KroneckerDelta(0,gO2) + vu*
      KroneckerDelta(1,gO2))*(7.745966692414834*g1*g2*Sin(2*ThetaW()) + 3*Sqr(g1)
      + 5*Sqr(g2) + Cos(2*ThetaW())*(-3*Sqr(g1) + 5*Sqr(g2)));

   return result;
}

std::complex<double> CLASSNAME::CpUhhconjVWmVWm(int gO2) const
{
   const std::complex<double> result = 0.5*(vd*KroneckerDelta(0,gO2) + vu*
      KroneckerDelta(1,gO2))*Sqr(g2);

   return result;
}

std::complex<double> CLASSNAME::CpSveLUhhUhhconjSveL(int gO1, int gO2) const
{
   const std::complex<double> result = -0.05*(KroneckerDelta(0,gO1)*
      KroneckerDelta(0,gO2) - KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2))*(3*Sqr(
      g1) + 5*Sqr(g2));

   return result;
}

std::complex<double> CLASSNAME::CpSvmLUhhUhhconjSvmL(int gO1, int gO2) const
{
   const std::complex<double> result = -0.05*(KroneckerDelta(0,gO1)*
      KroneckerDelta(0,gO2) - KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2))*(3*Sqr(
      g1) + 5*Sqr(g2));

   return result;
}

std::complex<double> CLASSNAME::CpSvtLUhhUhhconjSvtL(int gO1, int gO2) const
{
   const std::complex<double> result = -0.05*(KroneckerDelta(0,gO1)*
      KroneckerDelta(0,gO2) - KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2))*(3*Sqr(
      g1) + 5*Sqr(g2));

   return result;
}

std::complex<double> CLASSNAME::CpUhhUhhVZVZ(int gO1, int gO2) const
{
   const std::complex<double> result = 0.05*(KroneckerDelta(0,gO1)*
      KroneckerDelta(0,gO2) + KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2))*(
      7.745966692414834*g1*g2*Sin(2*ThetaW()) + 3*Sqr(g1) + 5*Sqr(g2) + Cos(2*
      ThetaW())*(-3*Sqr(g1) + 5*Sqr(g2)));

   return result;
}

std::complex<double> CLASSNAME::CpUhhUhhconjVWmVWm(int gO1, int gO2) const
{
   const std::complex<double> result = 0.5*(KroneckerDelta(0,gO1)*
      KroneckerDelta(0,gO2) + KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2))*Sqr(g2)
      ;

   return result;
}

std::complex<double> CLASSNAME::CpAhAhUhhUhh(int gI1, int gI2, int gO1, int gO2) const
{
   const std::complex<double> result = -0.05*(KroneckerDelta(0,gO1)*
      KroneckerDelta(0,gO2) - KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2))*(3*Sqr(
      g1) + 5*Sqr(g2))*(ZA(gI1,0)*ZA(gI2,0) - ZA(gI1,1)*ZA(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CphhhhUhhUhh(int gI1, int gI2, int gO1, int gO2) const
{
   const std::complex<double> result = 0.05*(3*Sqr(g1) + 5*Sqr(g2))*(
      KroneckerDelta(1,gO1)*(KroneckerDelta(0,gO2)*(ZH(gI1,1)*ZH(gI2,0) + ZH(gI1,0
      )*ZH(gI2,1)) + KroneckerDelta(1,gO2)*(ZH(gI1,0)*ZH(gI2,0) - 3*ZH(gI1,1)*ZH(
      gI2,1))) + KroneckerDelta(0,gO1)*(KroneckerDelta(1,gO2)*(ZH(gI1,1)*ZH(gI2,0)
      + ZH(gI1,0)*ZH(gI2,1)) + KroneckerDelta(0,gO2)*(-3*ZH(gI1,0)*ZH(gI2,0) + ZH
      (gI1,1)*ZH(gI2,1))));

   return result;
}

std::complex<double> CLASSNAME::CpUhhUhhHpmconjHpm(int gO1, int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(-(KroneckerDelta(0,gO1)*(5*
      KroneckerDelta(1,gO2)*Sqr(g2)*(ZP(gI1,1)*ZP(gI2,0) + ZP(gI1,0)*ZP(gI2,1)) +
      KroneckerDelta(0,gO2)*((3*Sqr(g1) + 5*Sqr(g2))*ZP(gI1,0)*ZP(gI2,0) + (-3*Sqr
      (g1) + 5*Sqr(g2))*ZP(gI1,1)*ZP(gI2,1)))) + KroneckerDelta(1,gO1)*(-5*
      KroneckerDelta(0,gO2)*Sqr(g2)*(ZP(gI1,1)*ZP(gI2,0) + ZP(gI1,0)*ZP(gI2,1)) +
      KroneckerDelta(1,gO2)*((3*Sqr(g1) - 5*Sqr(g2))*ZP(gI1,0)*ZP(gI2,0) - (3*Sqr(
      g1) + 5*Sqr(g2))*ZP(gI1,1)*ZP(gI2,1))));

   return result;
}

std::complex<double> CLASSNAME::CpUhhUhhSbconjSb(int gO1, int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZB(gI1,0))*(-(KroneckerDelta(
      1,gO1)*KroneckerDelta(1,gO2)*(Sqr(g1) + 5*Sqr(g2))) + KroneckerDelta(0,gO1)*
      KroneckerDelta(0,gO2)*(-20*AbsSqr(Yd(2,2)) + Sqr(g1) + 5*Sqr(g2)))*ZB(gI2,0)
      + 2*Conj(ZB(gI1,1))*(-(KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2)*Sqr(g1))
      + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*(-10*AbsSqr(Yd(2,2)) + Sqr(g1
      )))*ZB(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpUhhUhhScconjSc(int gO1, int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZC(gI1,0))*(KroneckerDelta(0,
      gO1)*KroneckerDelta(0,gO2)*(Sqr(g1) - 5*Sqr(g2)) - KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*(20*AbsSqr(Yu(1,1)) + Sqr(g1) - 5*Sqr(g2)))*ZC(gI2,0)
      - 4*Conj(ZC(gI1,1))*(KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*Sqr(g1) -
      KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2)*(-5*AbsSqr(Yu(1,1)) + Sqr(g1)))*
      ZC(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpUhhUhhSdconjSd(int gO1, int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZD(gI1,0))*(-(KroneckerDelta(
      1,gO1)*KroneckerDelta(1,gO2)*(Sqr(g1) + 5*Sqr(g2))) + KroneckerDelta(0,gO1)*
      KroneckerDelta(0,gO2)*(-20*AbsSqr(Yd(0,0)) + Sqr(g1) + 5*Sqr(g2)))*ZD(gI2,0)
      + 2*Conj(ZD(gI1,1))*(-(KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2)*Sqr(g1))
      + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*(-10*AbsSqr(Yd(0,0)) + Sqr(g1
      )))*ZD(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpUhhUhhSeconjSe(int gO1, int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZE(gI1,0))*(KroneckerDelta(1,
      gO1)*KroneckerDelta(1,gO2)*(3*Sqr(g1) - 5*Sqr(g2)) + KroneckerDelta(0,gO1)*
      KroneckerDelta(0,gO2)*(-20*AbsSqr(Ye(0,0)) - 3*Sqr(g1) + 5*Sqr(g2)))*ZE(gI2,
      0) + 2*Conj(ZE(gI1,1))*(-3*KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2)*Sqr(
      g1) + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*(-10*AbsSqr(Ye(0,0)) + 3*
      Sqr(g1)))*ZE(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpUhhUhhSmconjSm(int gO1, int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZM(gI1,0))*(KroneckerDelta(1,
      gO1)*KroneckerDelta(1,gO2)*(3*Sqr(g1) - 5*Sqr(g2)) + KroneckerDelta(0,gO1)*
      KroneckerDelta(0,gO2)*(-20*AbsSqr(Ye(1,1)) - 3*Sqr(g1) + 5*Sqr(g2)))*ZM(gI2,
      0) + 2*Conj(ZM(gI1,1))*(-3*KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2)*Sqr(
      g1) + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*(-10*AbsSqr(Ye(1,1)) + 3*
      Sqr(g1)))*ZM(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpUhhUhhSsconjSs(int gO1, int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZS(gI1,0))*(-(KroneckerDelta(
      1,gO1)*KroneckerDelta(1,gO2)*(Sqr(g1) + 5*Sqr(g2))) + KroneckerDelta(0,gO1)*
      KroneckerDelta(0,gO2)*(-20*AbsSqr(Yd(1,1)) + Sqr(g1) + 5*Sqr(g2)))*ZS(gI2,0)
      + 2*Conj(ZS(gI1,1))*(-(KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2)*Sqr(g1))
      + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*(-10*AbsSqr(Yd(1,1)) + Sqr(g1
      )))*ZS(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpUhhUhhStconjSt(int gO1, int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZT(gI1,0))*(KroneckerDelta(0,
      gO1)*KroneckerDelta(0,gO2)*(Sqr(g1) - 5*Sqr(g2)) - KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*(20*AbsSqr(Yu(2,2)) + Sqr(g1) - 5*Sqr(g2)))*ZT(gI2,0)
      - 4*Conj(ZT(gI1,1))*(KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*Sqr(g1) -
      KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2)*(-5*AbsSqr(Yu(2,2)) + Sqr(g1)))*
      ZT(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpUhhUhhStauconjStau(int gO1, int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZTau(gI1,0))*(KroneckerDelta(
      1,gO1)*KroneckerDelta(1,gO2)*(3*Sqr(g1) - 5*Sqr(g2)) + KroneckerDelta(0,gO1)
      *KroneckerDelta(0,gO2)*(-20*AbsSqr(Ye(2,2)) - 3*Sqr(g1) + 5*Sqr(g2)))*ZTau(
      gI2,0) + 2*Conj(ZTau(gI1,1))*(-3*KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2)
      *Sqr(g1) + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*(-10*AbsSqr(Ye(2,2))
      + 3*Sqr(g1)))*ZTau(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpUhhUhhSuconjSu(int gO1, int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZU(gI1,0))*(KroneckerDelta(0,
      gO1)*KroneckerDelta(0,gO2)*(Sqr(g1) - 5*Sqr(g2)) - KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*(20*AbsSqr(Yu(0,0)) + Sqr(g1) - 5*Sqr(g2)))*ZU(gI2,0)
      - 4*Conj(ZU(gI1,1))*(KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*Sqr(g1) -
      KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2)*(-5*AbsSqr(Yu(0,0)) + Sqr(g1)))*
      ZU(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpAhAhUhh(int gI1, int gI2, int gO2) const
{
   const std::complex<double> result = -0.05*(vd*KroneckerDelta(0,gO2) - vu*
      KroneckerDelta(1,gO2))*(3*Sqr(g1) + 5*Sqr(g2))*(ZA(gI1,0)*ZA(gI2,0) - ZA(gI1
      ,1)*ZA(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CphhhhUhh(int gI1, int gI2, int gO2) const
{
   const std::complex<double> result = 0.05*(3*Sqr(g1) + 5*Sqr(g2))*(
      KroneckerDelta(1,gO2)*(ZH(gI1,0)*(vu*ZH(gI2,0) + vd*ZH(gI2,1)) + ZH(gI1,1)*(
      vd*ZH(gI2,0) - 3*vu*ZH(gI2,1))) + KroneckerDelta(0,gO2)*(ZH(gI1,1)*(vu*ZH(
      gI2,0) + vd*ZH(gI2,1)) + ZH(gI1,0)*(-3*vd*ZH(gI2,0) + vu*ZH(gI2,1))));

   return result;
}

std::complex<double> CLASSNAME::CpUhhHpmconjHpm(int gO2, int gI2, int gI1) const
{
   const std::complex<double> result = 0.05*(-(KroneckerDelta(0,gO2)*(ZP(gI1,0)
      *(vd*(3*Sqr(g1) + 5*Sqr(g2))*ZP(gI2,0) + 5*vu*Sqr(g2)*ZP(gI2,1)) + ZP(gI1,1)
      *(5*vu*Sqr(g2)*ZP(gI2,0) + vd*(-3*Sqr(g1) + 5*Sqr(g2))*ZP(gI2,1)))) +
      KroneckerDelta(1,gO2)*(ZP(gI1,0)*(vu*(3*Sqr(g1) - 5*Sqr(g2))*ZP(gI2,0) - 5*
      vd*Sqr(g2)*ZP(gI2,1)) - ZP(gI1,1)*(5*vd*Sqr(g2)*ZP(gI2,0) + vu*(3*Sqr(g1) +
      5*Sqr(g2))*ZP(gI2,1))));

   return result;
}

std::complex<double> CLASSNAME::CpUhhSbconjSb(int gO2, int gI2, int gI1) const
{
   const std::complex<double> result = 0.05*(-2*Conj(ZB(gI2,1))*(
      7.0710678118654755*Conj(TYd(2,2))*KroneckerDelta(0,gO2)*ZB(gI1,0) + (-(vd*
      KroneckerDelta(0,gO2)) + vu*KroneckerDelta(1,gO2))*Sqr(g1)*ZB(gI1,1) - 5*
      Conj(Yd(2,2))*(1.4142135623730951*KroneckerDelta(1,gO2)*Mu*ZB(gI1,0) - 2*vd*
      KroneckerDelta(0,gO2)*Yd(2,2)*ZB(gI1,1))) + Conj(ZB(gI2,0))*(-(
      KroneckerDelta(1,gO2)*(vu*(Sqr(g1) + 5*Sqr(g2))*ZB(gI1,0) -
      14.142135623730951*Conj(Mu)*Yd(2,2)*ZB(gI1,1))) + KroneckerDelta(0,gO2)*(vd*
      (-20*AbsSqr(Yd(2,2)) + Sqr(g1) + 5*Sqr(g2))*ZB(gI1,0) - 14.142135623730951*
      ZB(gI1,1)*TYd(2,2))));

   return result;
}

std::complex<double> CLASSNAME::CpUhhScconjSc(int gO2, int gI2, int gI1) const
{
   const std::complex<double> result = 0.05*(2*Conj(ZC(gI2,1))*(
      -7.0710678118654755*Conj(TYu(1,1))*KroneckerDelta(1,gO2)*ZC(gI1,0) + 2*(-(vd
      *KroneckerDelta(0,gO2)) + vu*KroneckerDelta(1,gO2))*Sqr(g1)*ZC(gI1,1) + 5*
      Conj(Yu(1,1))*(1.4142135623730951*KroneckerDelta(0,gO2)*Mu*ZC(gI1,0) - 2*vu*
      KroneckerDelta(1,gO2)*Yu(1,1)*ZC(gI1,1))) + Conj(ZC(gI2,0))*(KroneckerDelta(
      0,gO2)*(vd*(Sqr(g1) - 5*Sqr(g2))*ZC(gI1,0) + 14.142135623730951*Conj(Mu)*Yu(
      1,1)*ZC(gI1,1)) - KroneckerDelta(1,gO2)*(vu*(20*AbsSqr(Yu(1,1)) + Sqr(g1) -
      5*Sqr(g2))*ZC(gI1,0) + 14.142135623730951*ZC(gI1,1)*TYu(1,1))));

   return result;
}

std::complex<double> CLASSNAME::CpUhhSdconjSd(int gO2, int gI2, int gI1) const
{
   const std::complex<double> result = 0.05*(-2*Conj(ZD(gI2,1))*(
      7.0710678118654755*Conj(TYd(0,0))*KroneckerDelta(0,gO2)*ZD(gI1,0) + (-(vd*
      KroneckerDelta(0,gO2)) + vu*KroneckerDelta(1,gO2))*Sqr(g1)*ZD(gI1,1) - 5*
      Conj(Yd(0,0))*(1.4142135623730951*KroneckerDelta(1,gO2)*Mu*ZD(gI1,0) - 2*vd*
      KroneckerDelta(0,gO2)*Yd(0,0)*ZD(gI1,1))) + Conj(ZD(gI2,0))*(-(
      KroneckerDelta(1,gO2)*(vu*(Sqr(g1) + 5*Sqr(g2))*ZD(gI1,0) -
      14.142135623730951*Conj(Mu)*Yd(0,0)*ZD(gI1,1))) + KroneckerDelta(0,gO2)*(vd*
      (-20*AbsSqr(Yd(0,0)) + Sqr(g1) + 5*Sqr(g2))*ZD(gI1,0) - 14.142135623730951*
      ZD(gI1,1)*TYd(0,0))));

   return result;
}

std::complex<double> CLASSNAME::CpUhhSeconjSe(int gO2, int gI2, int gI1) const
{
   const std::complex<double> result = 0.05*(-2*Conj(ZE(gI2,1))*(
      7.0710678118654755*Conj(TYe(0,0))*KroneckerDelta(0,gO2)*ZE(gI1,0) + 3*(-(vd*
      KroneckerDelta(0,gO2)) + vu*KroneckerDelta(1,gO2))*Sqr(g1)*ZE(gI1,1) - 5*
      Conj(Ye(0,0))*(1.4142135623730951*KroneckerDelta(1,gO2)*Mu*ZE(gI1,0) - 2*vd*
      KroneckerDelta(0,gO2)*Ye(0,0)*ZE(gI1,1))) + Conj(ZE(gI2,0))*(KroneckerDelta(
      1,gO2)*(vu*(3*Sqr(g1) - 5*Sqr(g2))*ZE(gI1,0) + 14.142135623730951*Conj(Mu)*
      Ye(0,0)*ZE(gI1,1)) - KroneckerDelta(0,gO2)*(vd*(20*AbsSqr(Ye(0,0)) + 3*Sqr(
      g1) - 5*Sqr(g2))*ZE(gI1,0) + 14.142135623730951*ZE(gI1,1)*TYe(0,0))));

   return result;
}

std::complex<double> CLASSNAME::CpUhhSmconjSm(int gO2, int gI2, int gI1) const
{
   const std::complex<double> result = 0.05*(-2*Conj(ZM(gI2,1))*(
      7.0710678118654755*Conj(TYe(1,1))*KroneckerDelta(0,gO2)*ZM(gI1,0) + 3*(-(vd*
      KroneckerDelta(0,gO2)) + vu*KroneckerDelta(1,gO2))*Sqr(g1)*ZM(gI1,1) - 5*
      Conj(Ye(1,1))*(1.4142135623730951*KroneckerDelta(1,gO2)*Mu*ZM(gI1,0) - 2*vd*
      KroneckerDelta(0,gO2)*Ye(1,1)*ZM(gI1,1))) + Conj(ZM(gI2,0))*(KroneckerDelta(
      1,gO2)*(vu*(3*Sqr(g1) - 5*Sqr(g2))*ZM(gI1,0) + 14.142135623730951*Conj(Mu)*
      Ye(1,1)*ZM(gI1,1)) - KroneckerDelta(0,gO2)*(vd*(20*AbsSqr(Ye(1,1)) + 3*Sqr(
      g1) - 5*Sqr(g2))*ZM(gI1,0) + 14.142135623730951*ZM(gI1,1)*TYe(1,1))));

   return result;
}

std::complex<double> CLASSNAME::CpUhhSsconjSs(int gO2, int gI2, int gI1) const
{
   const std::complex<double> result = 0.05*(-2*Conj(ZS(gI2,1))*(
      7.0710678118654755*Conj(TYd(1,1))*KroneckerDelta(0,gO2)*ZS(gI1,0) + (-(vd*
      KroneckerDelta(0,gO2)) + vu*KroneckerDelta(1,gO2))*Sqr(g1)*ZS(gI1,1) - 5*
      Conj(Yd(1,1))*(1.4142135623730951*KroneckerDelta(1,gO2)*Mu*ZS(gI1,0) - 2*vd*
      KroneckerDelta(0,gO2)*Yd(1,1)*ZS(gI1,1))) + Conj(ZS(gI2,0))*(-(
      KroneckerDelta(1,gO2)*(vu*(Sqr(g1) + 5*Sqr(g2))*ZS(gI1,0) -
      14.142135623730951*Conj(Mu)*Yd(1,1)*ZS(gI1,1))) + KroneckerDelta(0,gO2)*(vd*
      (-20*AbsSqr(Yd(1,1)) + Sqr(g1) + 5*Sqr(g2))*ZS(gI1,0) - 14.142135623730951*
      ZS(gI1,1)*TYd(1,1))));

   return result;
}

std::complex<double> CLASSNAME::CpUhhStconjSt(int gO2, int gI2, int gI1) const
{
   const std::complex<double> result = 0.05*(2*Conj(ZT(gI2,1))*(
      -7.0710678118654755*Conj(TYu(2,2))*KroneckerDelta(1,gO2)*ZT(gI1,0) + 2*(-(vd
      *KroneckerDelta(0,gO2)) + vu*KroneckerDelta(1,gO2))*Sqr(g1)*ZT(gI1,1) + 5*
      Conj(Yu(2,2))*(1.4142135623730951*KroneckerDelta(0,gO2)*Mu*ZT(gI1,0) - 2*vu*
      KroneckerDelta(1,gO2)*Yu(2,2)*ZT(gI1,1))) + Conj(ZT(gI2,0))*(KroneckerDelta(
      0,gO2)*(vd*(Sqr(g1) - 5*Sqr(g2))*ZT(gI1,0) + 14.142135623730951*Conj(Mu)*Yu(
      2,2)*ZT(gI1,1)) - KroneckerDelta(1,gO2)*(vu*(20*AbsSqr(Yu(2,2)) + Sqr(g1) -
      5*Sqr(g2))*ZT(gI1,0) + 14.142135623730951*ZT(gI1,1)*TYu(2,2))));

   return result;
}

std::complex<double> CLASSNAME::CpUhhStauconjStau(int gO2, int gI2, int gI1) const
{
   const std::complex<double> result = 0.05*(-2*Conj(ZTau(gI2,1))*(
      7.0710678118654755*Conj(TYe(2,2))*KroneckerDelta(0,gO2)*ZTau(gI1,0) + 3*(-(
      vd*KroneckerDelta(0,gO2)) + vu*KroneckerDelta(1,gO2))*Sqr(g1)*ZTau(gI1,1) -
      5*Conj(Ye(2,2))*(1.4142135623730951*KroneckerDelta(1,gO2)*Mu*ZTau(gI1,0) - 2
      *vd*KroneckerDelta(0,gO2)*Ye(2,2)*ZTau(gI1,1))) + Conj(ZTau(gI2,0))*(
      KroneckerDelta(1,gO2)*(vu*(3*Sqr(g1) - 5*Sqr(g2))*ZTau(gI1,0) +
      14.142135623730951*Conj(Mu)*Ye(2,2)*ZTau(gI1,1)) - KroneckerDelta(0,gO2)*(vd
      *(20*AbsSqr(Ye(2,2)) + 3*Sqr(g1) - 5*Sqr(g2))*ZTau(gI1,0) +
      14.142135623730951*ZTau(gI1,1)*TYe(2,2))));

   return result;
}

std::complex<double> CLASSNAME::CpUhhSuconjSu(int gO2, int gI2, int gI1) const
{
   const std::complex<double> result = 0.05*(2*Conj(ZU(gI2,1))*(
      -7.0710678118654755*Conj(TYu(0,0))*KroneckerDelta(1,gO2)*ZU(gI1,0) + 2*(-(vd
      *KroneckerDelta(0,gO2)) + vu*KroneckerDelta(1,gO2))*Sqr(g1)*ZU(gI1,1) + 5*
      Conj(Yu(0,0))*(1.4142135623730951*KroneckerDelta(0,gO2)*Mu*ZU(gI1,0) - 2*vu*
      KroneckerDelta(1,gO2)*Yu(0,0)*ZU(gI1,1))) + Conj(ZU(gI2,0))*(KroneckerDelta(
      0,gO2)*(vd*(Sqr(g1) - 5*Sqr(g2))*ZU(gI1,0) + 14.142135623730951*Conj(Mu)*Yu(
      0,0)*ZU(gI1,1)) - KroneckerDelta(1,gO2)*(vu*(20*AbsSqr(Yu(0,0)) + Sqr(g1) -
      5*Sqr(g2))*ZU(gI1,0) + 14.142135623730951*ZU(gI1,1)*TYu(0,0))));

   return result;
}

std::complex<double> CLASSNAME::CpbarChaChaUhhPR(int gI1, int gI2, int gO2) const
{
   const std::complex<double> result = -0.7071067811865475*g2*(KroneckerDelta(0
      ,gO2)*UM(gI1,1)*UP(gI2,0) + KroneckerDelta(1,gO2)*UM(gI1,0)*UP(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpbarChaChaUhhPL(int gI1, int gI2, int gO1) const
{
   const std::complex<double> result = -0.7071067811865475*g2*(Conj(UM(gI2,1))*
      Conj(UP(gI1,0))*KroneckerDelta(0,gO1) + Conj(UM(gI2,0))*Conj(UP(gI1,1))*
      KroneckerDelta(1,gO1));

   return result;
}

std::complex<double> CLASSNAME::CpChiChiUhhPR(int gI1, int gI2, int gO2) const
{
   const std::complex<double> result = 0.1*(KroneckerDelta(0,gO2)*(ZN(gI1,2)*(
      3.872983346207417*g1*ZN(gI2,0) - 5*g2*ZN(gI2,1)) + (3.872983346207417*g1*ZN(
      gI1,0) - 5*g2*ZN(gI1,1))*ZN(gI2,2)) - KroneckerDelta(1,gO2)*(ZN(gI1,3)*(
      3.872983346207417*g1*ZN(gI2,0) - 5*g2*ZN(gI2,1)) + (3.872983346207417*g1*ZN(
      gI1,0) - 5*g2*ZN(gI1,1))*ZN(gI2,3)));

   return result;
}

std::complex<double> CLASSNAME::CpChiChiUhhPL(int gI1, int gI2, int gO1) const
{
   const std::complex<double> result = 0.1*(Conj(ZN(gI1,2))*(3.872983346207417*
      g1*Conj(ZN(gI2,0)) - 5*g2*Conj(ZN(gI2,1)))*KroneckerDelta(0,gO1) - 5*g2*Conj
      (ZN(gI1,1))*Conj(ZN(gI2,2))*KroneckerDelta(0,gO1) - 3.872983346207417*g1*
      Conj(ZN(gI1,3))*Conj(ZN(gI2,0))*KroneckerDelta(1,gO1) + 5*g2*Conj(ZN(gI1,3))
      *Conj(ZN(gI2,1))*KroneckerDelta(1,gO1) + 5*g2*Conj(ZN(gI1,1))*Conj(ZN(gI2,3)
      )*KroneckerDelta(1,gO1) + 3.872983346207417*g1*Conj(ZN(gI1,0))*(Conj(ZN(gI2,
      2))*KroneckerDelta(0,gO1) - Conj(ZN(gI2,3))*KroneckerDelta(1,gO1)));

   return result;
}

std::complex<double> CLASSNAME::CpAhUhhVZ(int gI2, int gO2) const
{
   const std::complex<double> result = std::complex<double>(0,0.1)*(5*g2*Cos(
      ThetaW()) + 3.872983346207417*g1*Sin(ThetaW()))*(KroneckerDelta(0,gO2)*ZA(
      gI2,0) - KroneckerDelta(1,gO2)*ZA(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpUhhHpmconjVWm(int gO2, int gI2) const
{
   const std::complex<double> result = 0.5*(-(g2*KroneckerDelta(0,gO2)*ZP(gI2,0
      )) + g2*KroneckerDelta(1,gO2)*ZP(gI2,1));

   return result;
}

double CLASSNAME::CpbarFbFbUhhPR(int gO2) const
{
   const double result = -0.7071067811865475*Conj(Yd(2,2))*KroneckerDelta(0,gO2
      );

   return result;
}

double CLASSNAME::CpbarFbFbUhhPL(int gO1) const
{
   const double result = -0.7071067811865475*KroneckerDelta(0,gO1)*Yd(2,2);

   return result;
}

double CLASSNAME::CpbarFcFcUhhPR(int gO2) const
{
   const double result = -0.7071067811865475*Conj(Yu(1,1))*KroneckerDelta(1,gO2
      );

   return result;
}

double CLASSNAME::CpbarFcFcUhhPL(int gO1) const
{
   const double result = -0.7071067811865475*KroneckerDelta(1,gO1)*Yu(1,1);

   return result;
}

double CLASSNAME::CpbarFdFdUhhPR(int gO2) const
{
   const double result = -0.7071067811865475*Conj(Yd(0,0))*KroneckerDelta(0,gO2
      );

   return result;
}

double CLASSNAME::CpbarFdFdUhhPL(int gO1) const
{
   const double result = -0.7071067811865475*KroneckerDelta(0,gO1)*Yd(0,0);

   return result;
}

double CLASSNAME::CpbarFeFeUhhPR(int gO2) const
{
   const double result = -0.7071067811865475*Conj(Ye(0,0))*KroneckerDelta(0,gO2
      );

   return result;
}

double CLASSNAME::CpbarFeFeUhhPL(int gO1) const
{
   const double result = -0.7071067811865475*KroneckerDelta(0,gO1)*Ye(0,0);

   return result;
}

double CLASSNAME::CpbarFmFmUhhPR(int gO2) const
{
   const double result = -0.7071067811865475*Conj(Ye(1,1))*KroneckerDelta(0,gO2
      );

   return result;
}

double CLASSNAME::CpbarFmFmUhhPL(int gO1) const
{
   const double result = -0.7071067811865475*KroneckerDelta(0,gO1)*Ye(1,1);

   return result;
}

double CLASSNAME::CpbarFsFsUhhPR(int gO2) const
{
   const double result = -0.7071067811865475*Conj(Yd(1,1))*KroneckerDelta(0,gO2
      );

   return result;
}

double CLASSNAME::CpbarFsFsUhhPL(int gO1) const
{
   const double result = -0.7071067811865475*KroneckerDelta(0,gO1)*Yd(1,1);

   return result;
}

double CLASSNAME::CpbarFtFtUhhPR(int gO2) const
{
   const double result = -0.7071067811865475*Conj(Yu(2,2))*KroneckerDelta(1,gO2
      );

   return result;
}

double CLASSNAME::CpbarFtFtUhhPL(int gO1) const
{
   const double result = -0.7071067811865475*KroneckerDelta(1,gO1)*Yu(2,2);

   return result;
}

double CLASSNAME::CpbarFtauFtauUhhPR(int gO2) const
{
   const double result = -0.7071067811865475*Conj(Ye(2,2))*KroneckerDelta(0,gO2
      );

   return result;
}

double CLASSNAME::CpbarFtauFtauUhhPL(int gO1) const
{
   const double result = -0.7071067811865475*KroneckerDelta(0,gO1)*Ye(2,2);

   return result;
}

double CLASSNAME::CpbarFuFuUhhPR(int gO2) const
{
   const double result = -0.7071067811865475*Conj(Yu(0,0))*KroneckerDelta(1,gO2
      );

   return result;
}

double CLASSNAME::CpbarFuFuUhhPL(int gO1) const
{
   const double result = -0.7071067811865475*KroneckerDelta(1,gO1)*Yu(0,0);

   return result;
}

std::complex<double> CLASSNAME::CpbargWmgWmUAh(int gO1) const
{
   const std::complex<double> result = std::complex<double>(0,-0.25)*(vd*
      KroneckerDelta(0,gO1) - vu*KroneckerDelta(1,gO1))*Sqr(g2);

   return result;
}

std::complex<double> CLASSNAME::CpbargWmCgWmCUAh(int gO1) const
{
   const std::complex<double> result = std::complex<double>(0,0.25)*(vd*
      KroneckerDelta(0,gO1) - vu*KroneckerDelta(1,gO1))*Sqr(g2);

   return result;
}

std::complex<double> CLASSNAME::CpSveLUAhUAhconjSveL(int gO1, int gO2) const
{
   const std::complex<double> result = -0.05*(KroneckerDelta(0,gO1)*
      KroneckerDelta(0,gO2) - KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2))*(3*Sqr(
      g1) + 5*Sqr(g2));

   return result;
}

std::complex<double> CLASSNAME::CpSvmLUAhUAhconjSvmL(int gO1, int gO2) const
{
   const std::complex<double> result = -0.05*(KroneckerDelta(0,gO1)*
      KroneckerDelta(0,gO2) - KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2))*(3*Sqr(
      g1) + 5*Sqr(g2));

   return result;
}

std::complex<double> CLASSNAME::CpSvtLUAhUAhconjSvtL(int gO1, int gO2) const
{
   const std::complex<double> result = -0.05*(KroneckerDelta(0,gO1)*
      KroneckerDelta(0,gO2) - KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2))*(3*Sqr(
      g1) + 5*Sqr(g2));

   return result;
}

std::complex<double> CLASSNAME::CpUAhUAhVZVZ(int gO1, int gO2) const
{
   const std::complex<double> result = 0.05*(KroneckerDelta(0,gO1)*
      KroneckerDelta(0,gO2) + KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2))*(
      7.745966692414834*g1*g2*Sin(2*ThetaW()) + 3*Sqr(g1) + 5*Sqr(g2) + Cos(2*
      ThetaW())*(-3*Sqr(g1) + 5*Sqr(g2)));

   return result;
}

std::complex<double> CLASSNAME::CpUAhUAhconjVWmVWm(int gO1, int gO2) const
{
   const std::complex<double> result = 0.5*(KroneckerDelta(0,gO1)*
      KroneckerDelta(0,gO2) + KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2))*Sqr(g2)
      ;

   return result;
}

std::complex<double> CLASSNAME::CpAhAhUAhUAh(int gI1, int gI2, int gO1, int gO2) const
{
   const std::complex<double> result = 0.05*(3*Sqr(g1) + 5*Sqr(g2))*(
      KroneckerDelta(1,gO1)*(KroneckerDelta(0,gO2)*(ZA(gI1,1)*ZA(gI2,0) + ZA(gI1,0
      )*ZA(gI2,1)) + KroneckerDelta(1,gO2)*(ZA(gI1,0)*ZA(gI2,0) - 3*ZA(gI1,1)*ZA(
      gI2,1))) + KroneckerDelta(0,gO1)*(KroneckerDelta(1,gO2)*(ZA(gI1,1)*ZA(gI2,0)
      + ZA(gI1,0)*ZA(gI2,1)) + KroneckerDelta(0,gO2)*(-3*ZA(gI1,0)*ZA(gI2,0) + ZA
      (gI1,1)*ZA(gI2,1))));

   return result;
}

std::complex<double> CLASSNAME::CpUAhUAhhhhh(int gO1, int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = -0.05*(KroneckerDelta(0,gO1)*
      KroneckerDelta(0,gO2) - KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2))*(3*Sqr(
      g1) + 5*Sqr(g2))*(ZH(gI1,0)*ZH(gI2,0) - ZH(gI1,1)*ZH(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpUAhUAhHpmconjHpm(int gO1, int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(KroneckerDelta(0,gO1)*(5*
      KroneckerDelta(1,gO2)*Sqr(g2)*(ZP(gI1,1)*ZP(gI2,0) + ZP(gI1,0)*ZP(gI2,1)) -
      KroneckerDelta(0,gO2)*((3*Sqr(g1) + 5*Sqr(g2))*ZP(gI1,0)*ZP(gI2,0) + (-3*Sqr
      (g1) + 5*Sqr(g2))*ZP(gI1,1)*ZP(gI2,1))) + KroneckerDelta(1,gO1)*(5*
      KroneckerDelta(0,gO2)*Sqr(g2)*(ZP(gI1,1)*ZP(gI2,0) + ZP(gI1,0)*ZP(gI2,1)) +
      KroneckerDelta(1,gO2)*((3*Sqr(g1) - 5*Sqr(g2))*ZP(gI1,0)*ZP(gI2,0) - (3*Sqr(
      g1) + 5*Sqr(g2))*ZP(gI1,1)*ZP(gI2,1))));

   return result;
}

std::complex<double> CLASSNAME::CpUAhUAhSbconjSb(int gO1, int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZB(gI1,0))*(-(KroneckerDelta(
      1,gO1)*KroneckerDelta(1,gO2)*(Sqr(g1) + 5*Sqr(g2))) + KroneckerDelta(0,gO1)*
      KroneckerDelta(0,gO2)*(-20*AbsSqr(Yd(2,2)) + Sqr(g1) + 5*Sqr(g2)))*ZB(gI2,0)
      + 2*Conj(ZB(gI1,1))*(-(KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2)*Sqr(g1))
      + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*(-10*AbsSqr(Yd(2,2)) + Sqr(g1
      )))*ZB(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpUAhUAhScconjSc(int gO1, int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZC(gI1,0))*(KroneckerDelta(0,
      gO1)*KroneckerDelta(0,gO2)*(Sqr(g1) - 5*Sqr(g2)) - KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*(20*AbsSqr(Yu(1,1)) + Sqr(g1) - 5*Sqr(g2)))*ZC(gI2,0)
      - 4*Conj(ZC(gI1,1))*(KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*Sqr(g1) -
      KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2)*(-5*AbsSqr(Yu(1,1)) + Sqr(g1)))*
      ZC(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpUAhUAhSdconjSd(int gO1, int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZD(gI1,0))*(-(KroneckerDelta(
      1,gO1)*KroneckerDelta(1,gO2)*(Sqr(g1) + 5*Sqr(g2))) + KroneckerDelta(0,gO1)*
      KroneckerDelta(0,gO2)*(-20*AbsSqr(Yd(0,0)) + Sqr(g1) + 5*Sqr(g2)))*ZD(gI2,0)
      + 2*Conj(ZD(gI1,1))*(-(KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2)*Sqr(g1))
      + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*(-10*AbsSqr(Yd(0,0)) + Sqr(g1
      )))*ZD(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpUAhUAhSeconjSe(int gO1, int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZE(gI1,0))*(KroneckerDelta(1,
      gO1)*KroneckerDelta(1,gO2)*(3*Sqr(g1) - 5*Sqr(g2)) + KroneckerDelta(0,gO1)*
      KroneckerDelta(0,gO2)*(-20*AbsSqr(Ye(0,0)) - 3*Sqr(g1) + 5*Sqr(g2)))*ZE(gI2,
      0) + 2*Conj(ZE(gI1,1))*(-3*KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2)*Sqr(
      g1) + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*(-10*AbsSqr(Ye(0,0)) + 3*
      Sqr(g1)))*ZE(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpUAhUAhSmconjSm(int gO1, int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZM(gI1,0))*(KroneckerDelta(1,
      gO1)*KroneckerDelta(1,gO2)*(3*Sqr(g1) - 5*Sqr(g2)) + KroneckerDelta(0,gO1)*
      KroneckerDelta(0,gO2)*(-20*AbsSqr(Ye(1,1)) - 3*Sqr(g1) + 5*Sqr(g2)))*ZM(gI2,
      0) + 2*Conj(ZM(gI1,1))*(-3*KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2)*Sqr(
      g1) + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*(-10*AbsSqr(Ye(1,1)) + 3*
      Sqr(g1)))*ZM(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpUAhUAhSsconjSs(int gO1, int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZS(gI1,0))*(-(KroneckerDelta(
      1,gO1)*KroneckerDelta(1,gO2)*(Sqr(g1) + 5*Sqr(g2))) + KroneckerDelta(0,gO1)*
      KroneckerDelta(0,gO2)*(-20*AbsSqr(Yd(1,1)) + Sqr(g1) + 5*Sqr(g2)))*ZS(gI2,0)
      + 2*Conj(ZS(gI1,1))*(-(KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2)*Sqr(g1))
      + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*(-10*AbsSqr(Yd(1,1)) + Sqr(g1
      )))*ZS(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpUAhUAhStconjSt(int gO1, int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZT(gI1,0))*(KroneckerDelta(0,
      gO1)*KroneckerDelta(0,gO2)*(Sqr(g1) - 5*Sqr(g2)) - KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*(20*AbsSqr(Yu(2,2)) + Sqr(g1) - 5*Sqr(g2)))*ZT(gI2,0)
      - 4*Conj(ZT(gI1,1))*(KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*Sqr(g1) -
      KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2)*(-5*AbsSqr(Yu(2,2)) + Sqr(g1)))*
      ZT(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpUAhUAhStauconjStau(int gO1, int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZTau(gI1,0))*(KroneckerDelta(
      1,gO1)*KroneckerDelta(1,gO2)*(3*Sqr(g1) - 5*Sqr(g2)) + KroneckerDelta(0,gO1)
      *KroneckerDelta(0,gO2)*(-20*AbsSqr(Ye(2,2)) - 3*Sqr(g1) + 5*Sqr(g2)))*ZTau(
      gI2,0) + 2*Conj(ZTau(gI1,1))*(-3*KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2)
      *Sqr(g1) + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*(-10*AbsSqr(Ye(2,2))
      + 3*Sqr(g1)))*ZTau(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpUAhUAhSuconjSu(int gO1, int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZU(gI1,0))*(KroneckerDelta(0,
      gO1)*KroneckerDelta(0,gO2)*(Sqr(g1) - 5*Sqr(g2)) - KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*(20*AbsSqr(Yu(0,0)) + Sqr(g1) - 5*Sqr(g2)))*ZU(gI2,0)
      - 4*Conj(ZU(gI1,1))*(KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*Sqr(g1) -
      KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2)*(-5*AbsSqr(Yu(0,0)) + Sqr(g1)))*
      ZU(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpAhUAhhh(int gI2, int gO2, int gI1) const
{
   const std::complex<double> result = -0.05*(3*Sqr(g1) + 5*Sqr(g2))*(
      KroneckerDelta(0,gO2)*ZA(gI2,0) - KroneckerDelta(1,gO2)*ZA(gI2,1))*(vd*ZH(
      gI1,0) - vu*ZH(gI1,1));

   return result;
}

std::complex<double> CLASSNAME::CpUAhHpmconjHpm(int gO2, int gI2, int gI1) const
{
   const std::complex<double> result = std::complex<double>(0,0.25)*(vu*
      KroneckerDelta(0,gO2) + vd*KroneckerDelta(1,gO2))*Sqr(g2)*(ZP(gI1,1)*ZP(gI2,
      0) - ZP(gI1,0)*ZP(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpUAhSbconjSb(int gO2, int gI2, int gI1) const
{
   const std::complex<double> result = std::complex<double>(0.,
      0.7071067811865475)*(Conj(ZB(gI2,1))*(Conj(TYd(2,2))*KroneckerDelta(0,gO2) +
      Conj(Yd(2,2))*KroneckerDelta(1,gO2)*Mu)*ZB(gI1,0) - Conj(ZB(gI2,0))*ZB(gI1,
      1)*(Conj(Mu)*KroneckerDelta(1,gO2)*Yd(2,2) + KroneckerDelta(0,gO2)*TYd(2,2))
      );

   return result;
}

std::complex<double> CLASSNAME::CpUAhScconjSc(int gO2, int gI2, int gI1) const
{
   const std::complex<double> result = std::complex<double>(0.,
      0.7071067811865475)*(Conj(ZC(gI2,1))*Conj(TYu(1,1))*KroneckerDelta(1,gO2)*ZC
      (gI1,0) + Conj(Yu(1,1))*Conj(ZC(gI2,1))*KroneckerDelta(0,gO2)*Mu*ZC(gI1,0) -
      Conj(ZC(gI2,0))*ZC(gI1,1)*(Conj(Mu)*KroneckerDelta(0,gO2)*Yu(1,1) +
      KroneckerDelta(1,gO2)*TYu(1,1)));

   return result;
}

std::complex<double> CLASSNAME::CpUAhSdconjSd(int gO2, int gI2, int gI1) const
{
   const std::complex<double> result = std::complex<double>(0.,
      0.7071067811865475)*(Conj(ZD(gI2,1))*(Conj(TYd(0,0))*KroneckerDelta(0,gO2) +
      Conj(Yd(0,0))*KroneckerDelta(1,gO2)*Mu)*ZD(gI1,0) - Conj(ZD(gI2,0))*ZD(gI1,
      1)*(Conj(Mu)*KroneckerDelta(1,gO2)*Yd(0,0) + KroneckerDelta(0,gO2)*TYd(0,0))
      );

   return result;
}

std::complex<double> CLASSNAME::CpUAhSeconjSe(int gO2, int gI2, int gI1) const
{
   const std::complex<double> result = std::complex<double>(0.,
      0.7071067811865475)*(Conj(ZE(gI2,1))*(Conj(TYe(0,0))*KroneckerDelta(0,gO2) +
      Conj(Ye(0,0))*KroneckerDelta(1,gO2)*Mu)*ZE(gI1,0) - Conj(ZE(gI2,0))*ZE(gI1,
      1)*(Conj(Mu)*KroneckerDelta(1,gO2)*Ye(0,0) + KroneckerDelta(0,gO2)*TYe(0,0))
      );

   return result;
}

std::complex<double> CLASSNAME::CpUAhSmconjSm(int gO2, int gI2, int gI1) const
{
   const std::complex<double> result = std::complex<double>(0.,
      0.7071067811865475)*(Conj(ZM(gI2,1))*(Conj(TYe(1,1))*KroneckerDelta(0,gO2) +
      Conj(Ye(1,1))*KroneckerDelta(1,gO2)*Mu)*ZM(gI1,0) - Conj(ZM(gI2,0))*ZM(gI1,
      1)*(Conj(Mu)*KroneckerDelta(1,gO2)*Ye(1,1) + KroneckerDelta(0,gO2)*TYe(1,1))
      );

   return result;
}

std::complex<double> CLASSNAME::CpUAhSsconjSs(int gO2, int gI2, int gI1) const
{
   const std::complex<double> result = std::complex<double>(0.,
      0.7071067811865475)*(Conj(ZS(gI2,1))*(Conj(TYd(1,1))*KroneckerDelta(0,gO2) +
      Conj(Yd(1,1))*KroneckerDelta(1,gO2)*Mu)*ZS(gI1,0) - Conj(ZS(gI2,0))*ZS(gI1,
      1)*(Conj(Mu)*KroneckerDelta(1,gO2)*Yd(1,1) + KroneckerDelta(0,gO2)*TYd(1,1))
      );

   return result;
}

std::complex<double> CLASSNAME::CpUAhStconjSt(int gO2, int gI2, int gI1) const
{
   const std::complex<double> result = std::complex<double>(0.,
      0.7071067811865475)*(Conj(ZT(gI2,1))*Conj(TYu(2,2))*KroneckerDelta(1,gO2)*ZT
      (gI1,0) + Conj(Yu(2,2))*Conj(ZT(gI2,1))*KroneckerDelta(0,gO2)*Mu*ZT(gI1,0) -
      Conj(ZT(gI2,0))*ZT(gI1,1)*(Conj(Mu)*KroneckerDelta(0,gO2)*Yu(2,2) +
      KroneckerDelta(1,gO2)*TYu(2,2)));

   return result;
}

std::complex<double> CLASSNAME::CpUAhStauconjStau(int gO2, int gI2, int gI1) const
{
   const std::complex<double> result = std::complex<double>(0.,
      0.7071067811865475)*(Conj(ZTau(gI2,1))*(Conj(TYe(2,2))*KroneckerDelta(0,gO2)
      + Conj(Ye(2,2))*KroneckerDelta(1,gO2)*Mu)*ZTau(gI1,0) - Conj(ZTau(gI2,0))*
      ZTau(gI1,1)*(Conj(Mu)*KroneckerDelta(1,gO2)*Ye(2,2) + KroneckerDelta(0,gO2)*
      TYe(2,2)));

   return result;
}

std::complex<double> CLASSNAME::CpUAhSuconjSu(int gO2, int gI2, int gI1) const
{
   const std::complex<double> result = std::complex<double>(0.,
      0.7071067811865475)*(Conj(ZU(gI2,1))*Conj(TYu(0,0))*KroneckerDelta(1,gO2)*ZU
      (gI1,0) + Conj(Yu(0,0))*Conj(ZU(gI2,1))*KroneckerDelta(0,gO2)*Mu*ZU(gI1,0) -
      Conj(ZU(gI2,0))*ZU(gI1,1)*(Conj(Mu)*KroneckerDelta(0,gO2)*Yu(0,0) +
      KroneckerDelta(1,gO2)*TYu(0,0)));

   return result;
}

std::complex<double> CLASSNAME::CpbarChaChaUAhPR(int gI1, int gI2, int gO2) const
{
   const std::complex<double> result = std::complex<double>(0.,
      -0.7071067811865475)*g2*(KroneckerDelta(0,gO2)*UM(gI1,1)*UP(gI2,0) +
      KroneckerDelta(1,gO2)*UM(gI1,0)*UP(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpbarChaChaUAhPL(int gI1, int gI2, int gO1) const
{
   const std::complex<double> result = std::complex<double>(0.,
      0.7071067811865475)*g2*(Conj(UM(gI2,1))*Conj(UP(gI1,0))*KroneckerDelta(0,gO1
      ) + Conj(UM(gI2,0))*Conj(UP(gI1,1))*KroneckerDelta(1,gO1));

   return result;
}

std::complex<double> CLASSNAME::CpChiChiUAhPR(int gI1, int gI2, int gO2) const
{
   const std::complex<double> result = std::complex<double>(0,0.1)*(
      KroneckerDelta(0,gO2)*(ZN(gI1,2)*(3.872983346207417*g1*ZN(gI2,0) - 5*g2*ZN(
      gI2,1)) + (3.872983346207417*g1*ZN(gI1,0) - 5*g2*ZN(gI1,1))*ZN(gI2,2)) -
      KroneckerDelta(1,gO2)*(ZN(gI1,3)*(3.872983346207417*g1*ZN(gI2,0) - 5*g2*ZN(
      gI2,1)) + (3.872983346207417*g1*ZN(gI1,0) - 5*g2*ZN(gI1,1))*ZN(gI2,3)));

   return result;
}

std::complex<double> CLASSNAME::CpChiChiUAhPL(int gI1, int gI2, int gO1) const
{
   const std::complex<double> result = std::complex<double>(0,-0.1)*(Conj(ZN(
      gI1,2))*(3.872983346207417*g1*Conj(ZN(gI2,0)) - 5*g2*Conj(ZN(gI2,1)))*
      KroneckerDelta(0,gO1) - 5*g2*Conj(ZN(gI1,1))*Conj(ZN(gI2,2))*KroneckerDelta(
      0,gO1) - 3.872983346207417*g1*Conj(ZN(gI1,3))*Conj(ZN(gI2,0))*KroneckerDelta
      (1,gO1) + 5*g2*Conj(ZN(gI1,3))*Conj(ZN(gI2,1))*KroneckerDelta(1,gO1) + 5*g2*
      Conj(ZN(gI1,1))*Conj(ZN(gI2,3))*KroneckerDelta(1,gO1) + 3.872983346207417*g1
      *Conj(ZN(gI1,0))*(Conj(ZN(gI2,2))*KroneckerDelta(0,gO1) - Conj(ZN(gI2,3))*
      KroneckerDelta(1,gO1)));

   return result;
}

std::complex<double> CLASSNAME::CpUAhhhVZ(int gO2, int gI2) const
{
   const std::complex<double> result = std::complex<double>(0,0.1)*(5*g2*Cos(
      ThetaW()) + 3.872983346207417*g1*Sin(ThetaW()))*(KroneckerDelta(0,gO2)*ZH(
      gI2,0) - KroneckerDelta(1,gO2)*ZH(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpUAhHpmconjVWm(int gO2, int gI2) const
{
   const std::complex<double> result = std::complex<double>(0,0.5)*g2*(
      KroneckerDelta(0,gO2)*ZP(gI2,0) + KroneckerDelta(1,gO2)*ZP(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpbarFbFbUAhPR(int gO2) const
{
   const std::complex<double> result = std::complex<double>(0.,
      0.7071067811865475)*Conj(Yd(2,2))*KroneckerDelta(0,gO2);

   return result;
}

std::complex<double> CLASSNAME::CpbarFbFbUAhPL(int gO1) const
{
   const std::complex<double> result = std::complex<double>(0.,
      -0.7071067811865475)*KroneckerDelta(0,gO1)*Yd(2,2);

   return result;
}

std::complex<double> CLASSNAME::CpbarFcFcUAhPR(int gO2) const
{
   const std::complex<double> result = std::complex<double>(0.,
      0.7071067811865475)*Conj(Yu(1,1))*KroneckerDelta(1,gO2);

   return result;
}

std::complex<double> CLASSNAME::CpbarFcFcUAhPL(int gO1) const
{
   const std::complex<double> result = std::complex<double>(0.,
      -0.7071067811865475)*KroneckerDelta(1,gO1)*Yu(1,1);

   return result;
}

std::complex<double> CLASSNAME::CpbarFdFdUAhPR(int gO2) const
{
   const std::complex<double> result = std::complex<double>(0.,
      0.7071067811865475)*Conj(Yd(0,0))*KroneckerDelta(0,gO2);

   return result;
}

std::complex<double> CLASSNAME::CpbarFdFdUAhPL(int gO1) const
{
   const std::complex<double> result = std::complex<double>(0.,
      -0.7071067811865475)*KroneckerDelta(0,gO1)*Yd(0,0);

   return result;
}

std::complex<double> CLASSNAME::CpbarFeFeUAhPR(int gO2) const
{
   const std::complex<double> result = std::complex<double>(0.,
      0.7071067811865475)*Conj(Ye(0,0))*KroneckerDelta(0,gO2);

   return result;
}

std::complex<double> CLASSNAME::CpbarFeFeUAhPL(int gO1) const
{
   const std::complex<double> result = std::complex<double>(0.,
      -0.7071067811865475)*KroneckerDelta(0,gO1)*Ye(0,0);

   return result;
}

std::complex<double> CLASSNAME::CpbarFmFmUAhPR(int gO2) const
{
   const std::complex<double> result = std::complex<double>(0.,
      0.7071067811865475)*Conj(Ye(1,1))*KroneckerDelta(0,gO2);

   return result;
}

std::complex<double> CLASSNAME::CpbarFmFmUAhPL(int gO1) const
{
   const std::complex<double> result = std::complex<double>(0.,
      -0.7071067811865475)*KroneckerDelta(0,gO1)*Ye(1,1);

   return result;
}

std::complex<double> CLASSNAME::CpbarFsFsUAhPR(int gO2) const
{
   const std::complex<double> result = std::complex<double>(0.,
      0.7071067811865475)*Conj(Yd(1,1))*KroneckerDelta(0,gO2);

   return result;
}

std::complex<double> CLASSNAME::CpbarFsFsUAhPL(int gO1) const
{
   const std::complex<double> result = std::complex<double>(0.,
      -0.7071067811865475)*KroneckerDelta(0,gO1)*Yd(1,1);

   return result;
}

std::complex<double> CLASSNAME::CpbarFtFtUAhPR(int gO2) const
{
   const std::complex<double> result = std::complex<double>(0.,
      0.7071067811865475)*Conj(Yu(2,2))*KroneckerDelta(1,gO2);

   return result;
}

std::complex<double> CLASSNAME::CpbarFtFtUAhPL(int gO1) const
{
   const std::complex<double> result = std::complex<double>(0.,
      -0.7071067811865475)*KroneckerDelta(1,gO1)*Yu(2,2);

   return result;
}

std::complex<double> CLASSNAME::CpbarFtauFtauUAhPR(int gO2) const
{
   const std::complex<double> result = std::complex<double>(0.,
      0.7071067811865475)*Conj(Ye(2,2))*KroneckerDelta(0,gO2);

   return result;
}

std::complex<double> CLASSNAME::CpbarFtauFtauUAhPL(int gO1) const
{
   const std::complex<double> result = std::complex<double>(0.,
      -0.7071067811865475)*KroneckerDelta(0,gO1)*Ye(2,2);

   return result;
}

std::complex<double> CLASSNAME::CpbarFuFuUAhPR(int gO2) const
{
   const std::complex<double> result = std::complex<double>(0.,
      0.7071067811865475)*Conj(Yu(0,0))*KroneckerDelta(1,gO2);

   return result;
}

std::complex<double> CLASSNAME::CpbarFuFuUAhPL(int gO1) const
{
   const std::complex<double> result = std::complex<double>(0.,
      -0.7071067811865475)*KroneckerDelta(1,gO1)*Yu(0,0);

   return result;
}

std::complex<double> CLASSNAME::CpbargWmgZUHpm(int gO2) const
{
   const std::complex<double> result = 0.05*g2*(vd*KroneckerDelta(0,gO2) - vu*
      KroneckerDelta(1,gO2))*(5*g2*Cos(ThetaW()) - 3.872983346207417*g1*Sin(ThetaW
      ()));

   return result;
}

std::complex<double> CLASSNAME::CpbargZgWmconjUHpm(int gO1) const
{
   const std::complex<double> result = -0.05*g2*(vd*KroneckerDelta(0,gO1) - vu*
      KroneckerDelta(1,gO1))*(5*g2*Cos(ThetaW()) + 3.872983346207417*g1*Sin(ThetaW
      ()));

   return result;
}

std::complex<double> CLASSNAME::CpbargWmCgZconjUHpm(int gO1) const
{
   const std::complex<double> result = 0.05*g2*(vd*KroneckerDelta(0,gO1) - vu*
      KroneckerDelta(1,gO1))*(5*g2*Cos(ThetaW()) - 3.872983346207417*g1*Sin(ThetaW
      ()));

   return result;
}

std::complex<double> CLASSNAME::CpbargZgWmCUHpm(int gO2) const
{
   const std::complex<double> result = -0.05*g2*(vd*KroneckerDelta(0,gO2) - vu*
      KroneckerDelta(1,gO2))*(5*g2*Cos(ThetaW()) + 3.872983346207417*g1*Sin(ThetaW
      ()));

   return result;
}

std::complex<double> CLASSNAME::CpconjUHpmVPVWm(int gO2) const
{
   const std::complex<double> result = -0.3872983346207417*g1*g2*Cos(ThetaW())*
      (vd*KroneckerDelta(0,gO2) - vu*KroneckerDelta(1,gO2));

   return result;
}

std::complex<double> CLASSNAME::CpconjUHpmVWmVZ(int gO2) const
{
   const std::complex<double> result = 0.3872983346207417*g1*g2*(vd*
      KroneckerDelta(0,gO2) - vu*KroneckerDelta(1,gO2))*Sin(ThetaW());

   return result;
}

std::complex<double> CLASSNAME::CpSveLUHpmconjSveLconjUHpm(int gO1, int gO2) const
{
   const std::complex<double> result = 0.05*(KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*(3*Sqr(g1) - 5*Sqr(g2)) + KroneckerDelta(0,gO1)*
      KroneckerDelta(0,gO2)*(-20*AbsSqr(Ye(0,0)) - 3*Sqr(g1) + 5*Sqr(g2)));

   return result;
}

std::complex<double> CLASSNAME::CpSvmLUHpmconjSvmLconjUHpm(int gO1, int gO2) const
{
   const std::complex<double> result = 0.05*(KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*(3*Sqr(g1) - 5*Sqr(g2)) + KroneckerDelta(0,gO1)*
      KroneckerDelta(0,gO2)*(-20*AbsSqr(Ye(1,1)) - 3*Sqr(g1) + 5*Sqr(g2)));

   return result;
}

std::complex<double> CLASSNAME::CpSvtLUHpmconjSvtLconjUHpm(int gO1, int gO2) const
{
   const std::complex<double> result = 0.05*(KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*(3*Sqr(g1) - 5*Sqr(g2)) + KroneckerDelta(0,gO1)*
      KroneckerDelta(0,gO2)*(-20*AbsSqr(Ye(2,2)) - 3*Sqr(g1) + 5*Sqr(g2)));

   return result;
}

std::complex<double> CLASSNAME::CpUHpmconjUHpmVZVZ(int gO1, int gO2) const
{
   const std::complex<double> result = 0.05*(KroneckerDelta(0,gO1)*
      KroneckerDelta(0,gO2) + KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2))*(
      -7.745966692414834*g1*g2*Sin(2*ThetaW()) + 3*Sqr(g1) + 5*Sqr(g2) + Cos(2*
      ThetaW())*(-3*Sqr(g1) + 5*Sqr(g2)));

   return result;
}

std::complex<double> CLASSNAME::CpUHpmconjUHpmconjVWmVWm(int gO1, int gO2) const
{
   const std::complex<double> result = 0.5*(KroneckerDelta(0,gO1)*
      KroneckerDelta(0,gO2) + KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2))*Sqr(g2)
      ;

   return result;
}

std::complex<double> CLASSNAME::CpAhAhUHpmconjUHpm(int gI1, int gI2, int gO1, int gO2) const
{
   const std::complex<double> result = 0.05*(KroneckerDelta(0,gO1)*(5*
      KroneckerDelta(1,gO2)*Sqr(g2)*(ZA(gI1,1)*ZA(gI2,0) + ZA(gI1,0)*ZA(gI2,1)) -
      KroneckerDelta(0,gO2)*((3*Sqr(g1) + 5*Sqr(g2))*ZA(gI1,0)*ZA(gI2,0) + (-3*Sqr
      (g1) + 5*Sqr(g2))*ZA(gI1,1)*ZA(gI2,1))) + KroneckerDelta(1,gO1)*(5*
      KroneckerDelta(0,gO2)*Sqr(g2)*(ZA(gI1,1)*ZA(gI2,0) + ZA(gI1,0)*ZA(gI2,1)) +
      KroneckerDelta(1,gO2)*((3*Sqr(g1) - 5*Sqr(g2))*ZA(gI1,0)*ZA(gI2,0) - (3*Sqr(
      g1) + 5*Sqr(g2))*ZA(gI1,1)*ZA(gI2,1))));

   return result;
}

std::complex<double> CLASSNAME::CphhhhUHpmconjUHpm(int gI1, int gI2, int gO1, int gO2) const
{
   const std::complex<double> result = 0.05*(-(KroneckerDelta(0,gO1)*(5*
      KroneckerDelta(1,gO2)*Sqr(g2)*(ZH(gI1,1)*ZH(gI2,0) + ZH(gI1,0)*ZH(gI2,1)) +
      KroneckerDelta(0,gO2)*((3*Sqr(g1) + 5*Sqr(g2))*ZH(gI1,0)*ZH(gI2,0) + (-3*Sqr
      (g1) + 5*Sqr(g2))*ZH(gI1,1)*ZH(gI2,1)))) + KroneckerDelta(1,gO1)*(-5*
      KroneckerDelta(0,gO2)*Sqr(g2)*(ZH(gI1,1)*ZH(gI2,0) + ZH(gI1,0)*ZH(gI2,1)) +
      KroneckerDelta(1,gO2)*((3*Sqr(g1) - 5*Sqr(g2))*ZH(gI1,0)*ZH(gI2,0) - (3*Sqr(
      g1) + 5*Sqr(g2))*ZH(gI1,1)*ZH(gI2,1))));

   return result;
}

std::complex<double> CLASSNAME::CpHpmUHpmconjHpmconjUHpm(int gI1, int gO1, int gI2, int gO2) const
{
   const std::complex<double> result = 0.05*(3*Sqr(g1) + 5*Sqr(g2))*(
      KroneckerDelta(1,gO1)*(KroneckerDelta(0,gO2)*ZP(gI1,0)*ZP(gI2,1) +
      KroneckerDelta(1,gO2)*(ZP(gI1,0)*ZP(gI2,0) - 2*ZP(gI1,1)*ZP(gI2,1))) +
      KroneckerDelta(0,gO1)*(KroneckerDelta(1,gO2)*ZP(gI1,1)*ZP(gI2,0) +
      KroneckerDelta(0,gO2)*(-2*ZP(gI1,0)*ZP(gI2,0) + ZP(gI1,1)*ZP(gI2,1))));

   return result;
}

std::complex<double> CLASSNAME::CpUHpmSbconjUHpmconjSb(int gO1, int gI1, int gO2, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZB(gI1,0))*(KroneckerDelta(0,
      gO1)*KroneckerDelta(0,gO2)*(Sqr(g1) - 5*Sqr(g2)) - KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*(20*AbsSqr(Yu(2,2)) + Sqr(g1) - 5*Sqr(g2)))*ZB(gI2,0)
      + 2*Conj(ZB(gI1,1))*(-(KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2)*Sqr(g1))
      + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*(-10*AbsSqr(Yd(2,2)) + Sqr(g1)
      ))*ZB(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpUHpmScconjUHpmconjSc(int gO1, int gI1, int gO2, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZC(gI1,0))*(-(KroneckerDelta(
      1,gO1)*KroneckerDelta(1,gO2)*(Sqr(g1) + 5*Sqr(g2))) + KroneckerDelta(0,gO1)*
      KroneckerDelta(0,gO2)*(-20*AbsSqr(Yd(1,1)) + Sqr(g1) + 5*Sqr(g2)))*ZC(gI2,0)
      - 4*Conj(ZC(gI1,1))*(KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*Sqr(g1) -
      KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2)*(-5*AbsSqr(Yu(1,1)) + Sqr(g1)))*
      ZC(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpUHpmSdconjUHpmconjSd(int gO1, int gI1, int gO2, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZD(gI1,0))*(KroneckerDelta(0,
      gO1)*KroneckerDelta(0,gO2)*(Sqr(g1) - 5*Sqr(g2)) - KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*(20*AbsSqr(Yu(0,0)) + Sqr(g1) - 5*Sqr(g2)))*ZD(gI2,0)
      + 2*Conj(ZD(gI1,1))*(-(KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2)*Sqr(g1))
      + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*(-10*AbsSqr(Yd(0,0)) + Sqr(g1)
      ))*ZD(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpUHpmSeconjUHpmconjSe(int gO1, int gI1, int gO2, int gI2) const
{
   const std::complex<double> result = 0.05*(-(Conj(ZE(gI1,0))*(KroneckerDelta(
      0,gO1)*KroneckerDelta(0,gO2) - KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2))*
      (3*Sqr(g1) + 5*Sqr(g2))*ZE(gI2,0)) + 2*Conj(ZE(gI1,1))*(-3*KroneckerDelta(1,
      gO1)*KroneckerDelta(1,gO2)*Sqr(g1) + KroneckerDelta(0,gO1)*KroneckerDelta(0,
      gO2)*(-10*AbsSqr(Ye(0,0)) + 3*Sqr(g1)))*ZE(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpUHpmSmconjUHpmconjSm(int gO1, int gI1, int gO2, int gI2) const
{
   const std::complex<double> result = 0.05*(-(Conj(ZM(gI1,0))*(KroneckerDelta(
      0,gO1)*KroneckerDelta(0,gO2) - KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2))*
      (3*Sqr(g1) + 5*Sqr(g2))*ZM(gI2,0)) + 2*Conj(ZM(gI1,1))*(-3*KroneckerDelta(1,
      gO1)*KroneckerDelta(1,gO2)*Sqr(g1) + KroneckerDelta(0,gO1)*KroneckerDelta(0,
      gO2)*(-10*AbsSqr(Ye(1,1)) + 3*Sqr(g1)))*ZM(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpUHpmSsconjUHpmconjSs(int gO1, int gI1, int gO2, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZS(gI1,0))*(KroneckerDelta(0,
      gO1)*KroneckerDelta(0,gO2)*(Sqr(g1) - 5*Sqr(g2)) - KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2)*(20*AbsSqr(Yu(1,1)) + Sqr(g1) - 5*Sqr(g2)))*ZS(gI2,0)
      + 2*Conj(ZS(gI1,1))*(-(KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2)*Sqr(g1))
      + KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*(-10*AbsSqr(Yd(1,1)) + Sqr(g1)
      ))*ZS(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpUHpmStconjUHpmconjSt(int gO1, int gI1, int gO2, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZT(gI1,0))*(-(KroneckerDelta(
      1,gO1)*KroneckerDelta(1,gO2)*(Sqr(g1) + 5*Sqr(g2))) + KroneckerDelta(0,gO1)*
      KroneckerDelta(0,gO2)*(-20*AbsSqr(Yd(2,2)) + Sqr(g1) + 5*Sqr(g2)))*ZT(gI2,0)
      - 4*Conj(ZT(gI1,1))*(KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*Sqr(g1) -
      KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2)*(-5*AbsSqr(Yu(2,2)) + Sqr(g1)))*
      ZT(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpUHpmStauconjUHpmconjStau(int gO1, int gI1, int gO2, int gI2) const
{
   const std::complex<double> result = 0.05*(-(Conj(ZTau(gI1,0))*(
      KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2) - KroneckerDelta(1,gO1)*
      KroneckerDelta(1,gO2))*(3*Sqr(g1) + 5*Sqr(g2))*ZTau(gI2,0)) + 2*Conj(ZTau(
      gI1,1))*(-3*KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2)*Sqr(g1) +
      KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*(-10*AbsSqr(Ye(2,2)) + 3*Sqr(g1)
      ))*ZTau(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpUHpmSuconjUHpmconjSu(int gO1, int gI1, int gO2, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZU(gI1,0))*(-(KroneckerDelta(
      1,gO1)*KroneckerDelta(1,gO2)*(Sqr(g1) + 5*Sqr(g2))) + KroneckerDelta(0,gO1)*
      KroneckerDelta(0,gO2)*(-20*AbsSqr(Yd(0,0)) + Sqr(g1) + 5*Sqr(g2)))*ZU(gI2,0)
      - 4*Conj(ZU(gI1,1))*(KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2)*Sqr(g1) -
      KroneckerDelta(1,gO1)*KroneckerDelta(1,gO2)*(-5*AbsSqr(Yu(0,0)) + Sqr(g1)))*
      ZU(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpAhHpmconjUHpm(int gI2, int gI1, int gO2) const
{
   const std::complex<double> result = std::complex<double>(0,0.25)*Sqr(g2)*(vu
      *ZA(gI2,0) + vd*ZA(gI2,1))*(KroneckerDelta(1,gO2)*ZP(gI1,0) - KroneckerDelta
      (0,gO2)*ZP(gI1,1));

   return result;
}

std::complex<double> CLASSNAME::CphhHpmconjUHpm(int gI2, int gI1, int gO2) const
{
   const std::complex<double> result = 0.05*(-(KroneckerDelta(0,gO2)*(ZH(gI2,1)
      *((-3*vu*Sqr(g1) + 5*vu*Sqr(g2))*ZP(gI1,0) + 5*vd*Sqr(g2)*ZP(gI1,1)) + ZH(
      gI2,0)*(vd*(3*Sqr(g1) + 5*Sqr(g2))*ZP(gI1,0) + 5*vu*Sqr(g2)*ZP(gI1,1)))) -
      KroneckerDelta(1,gO2)*(ZH(gI2,0)*(5*vu*Sqr(g2)*ZP(gI1,0) + vd*(-3*Sqr(g1) +
      5*Sqr(g2))*ZP(gI1,1)) + ZH(gI2,1)*(5*vd*Sqr(g2)*ZP(gI1,0) + vu*(3*Sqr(g1) +
      5*Sqr(g2))*ZP(gI1,1))));

   return result;
}

std::complex<double> CLASSNAME::CpSbconjUHpmconjSt(int gI2, int gO2, int gI1) const
{
   const std::complex<double> result = 0.5*Conj(ZB(gI2,1))*(2*Conj(TYd(2,2))*
      KroneckerDelta(0,gO2)*ZT(gI1,0) + Conj(Yd(2,2))*(1.4142135623730951*vu*
      KroneckerDelta(0,gO2)*Yu(2,2)*ZT(gI1,1) + KroneckerDelta(1,gO2)*(2*Mu*ZT(gI1
      ,0) + 1.4142135623730951*vd*Yu(2,2)*ZT(gI1,1)))) - 0.25*Conj(ZB(gI2,0))*(
      KroneckerDelta(0,gO2)*(1.4142135623730951*vd*(-2*AbsSqr(Yd(2,2)) + Sqr(g2))*
      ZT(gI1,0) - 4*Conj(Mu)*Yu(2,2)*ZT(gI1,1)) + KroneckerDelta(1,gO2)*(
      1.4142135623730951*vu*(-2*AbsSqr(Yu(2,2)) + Sqr(g2))*ZT(gI1,0) - 4*ZT(gI1,1)
      *TYu(2,2)));

   return result;
}

std::complex<double> CLASSNAME::CpSdconjUHpmconjSu(int gI2, int gO2, int gI1) const
{
   const std::complex<double> result = 0.5*Conj(ZD(gI2,1))*(2*Conj(TYd(0,0))*
      KroneckerDelta(0,gO2)*ZU(gI1,0) + Conj(Yd(0,0))*(1.4142135623730951*vu*
      KroneckerDelta(0,gO2)*Yu(0,0)*ZU(gI1,1) + KroneckerDelta(1,gO2)*(2*Mu*ZU(gI1
      ,0) + 1.4142135623730951*vd*Yu(0,0)*ZU(gI1,1)))) - 0.25*Conj(ZD(gI2,0))*(
      KroneckerDelta(0,gO2)*(1.4142135623730951*vd*(-2*AbsSqr(Yd(0,0)) + Sqr(g2))*
      ZU(gI1,0) - 4*Conj(Mu)*Yu(0,0)*ZU(gI1,1)) + KroneckerDelta(1,gO2)*(
      1.4142135623730951*vu*(-2*AbsSqr(Yu(0,0)) + Sqr(g2))*ZU(gI1,0) - 4*ZU(gI1,1)
      *TYu(0,0)));

   return result;
}

std::complex<double> CLASSNAME::CpSsconjUHpmconjSc(int gI2, int gO2, int gI1) const
{
   const std::complex<double> result = 0.5*Conj(ZS(gI2,1))*(2*Conj(TYd(1,1))*
      KroneckerDelta(0,gO2)*ZC(gI1,0) + Conj(Yd(1,1))*(1.4142135623730951*vu*
      KroneckerDelta(0,gO2)*Yu(1,1)*ZC(gI1,1) + KroneckerDelta(1,gO2)*(2*Mu*ZC(gI1
      ,0) + 1.4142135623730951*vd*Yu(1,1)*ZC(gI1,1)))) - 0.25*Conj(ZS(gI2,0))*(
      KroneckerDelta(0,gO2)*(1.4142135623730951*vd*(-2*AbsSqr(Yd(1,1)) + Sqr(g2))*
      ZC(gI1,0) - 4*Conj(Mu)*Yu(1,1)*ZC(gI1,1)) + KroneckerDelta(1,gO2)*(
      1.4142135623730951*vu*(-2*AbsSqr(Yu(1,1)) + Sqr(g2))*ZC(gI1,0) - 4*ZC(gI1,1)
      *TYu(1,1)));

   return result;
}

std::complex<double> CLASSNAME::CpChiChaconjUHpmPR(int gI1, int gI2, int gO2) const
{
   const std::complex<double> result = -0.5*KroneckerDelta(1,gO2)*(UP(gI2,1)*(
      1.0954451150103321*g1*ZN(gI1,0) + 1.4142135623730951*g2*ZN(gI1,1)) + 2*g2*UP
      (gI2,0)*ZN(gI1,3));

   return result;
}

std::complex<double> CLASSNAME::CpChiChaconjUHpmPL(int gI1, int gI2, int gO1) const
{
   const std::complex<double> result = 0.5*(Conj(UM(gI2,1))*(1.0954451150103321
      *g1*Conj(ZN(gI1,0)) + 1.4142135623730951*g2*Conj(ZN(gI1,1))) - 2*g2*Conj(UM(
      gI2,0))*Conj(ZN(gI1,2)))*KroneckerDelta(0,gO1);

   return result;
}

std::complex<double> CLASSNAME::CpSeconjSveLconjUHpm(int gI2, int gO2) const
{
   const std::complex<double> result = Conj(ZE(gI2,1))*(Conj(TYe(0,0))*
      KroneckerDelta(0,gO2) + Conj(Ye(0,0))*KroneckerDelta(1,gO2)*Mu) -
      0.35355339059327373*Conj(ZE(gI2,0))*(vu*KroneckerDelta(1,gO2)*Sqr(g2) + vd*
      KroneckerDelta(0,gO2)*(-2*AbsSqr(Ye(0,0)) + Sqr(g2)));

   return result;
}

std::complex<double> CLASSNAME::CpSmconjSvmLconjUHpm(int gI2, int gO2) const
{
   const std::complex<double> result = Conj(ZM(gI2,1))*(Conj(TYe(1,1))*
      KroneckerDelta(0,gO2) + Conj(Ye(1,1))*KroneckerDelta(1,gO2)*Mu) -
      0.35355339059327373*Conj(ZM(gI2,0))*(vu*KroneckerDelta(1,gO2)*Sqr(g2) + vd*
      KroneckerDelta(0,gO2)*(-2*AbsSqr(Ye(1,1)) + Sqr(g2)));

   return result;
}

std::complex<double> CLASSNAME::CpStauconjSvtLconjUHpm(int gI2, int gO2) const
{
   const std::complex<double> result = Conj(ZTau(gI2,1))*(Conj(TYe(2,2))*
      KroneckerDelta(0,gO2) + Conj(Ye(2,2))*KroneckerDelta(1,gO2)*Mu) -
      0.35355339059327373*Conj(ZTau(gI2,0))*(vu*KroneckerDelta(1,gO2)*Sqr(g2) + vd
      *KroneckerDelta(0,gO2)*(-2*AbsSqr(Ye(2,2)) + Sqr(g2)));

   return result;
}

std::complex<double> CLASSNAME::CpAhconjUHpmVWm(int gI2, int gO2) const
{
   const std::complex<double> result = std::complex<double>(0,0.5)*g2*(
      KroneckerDelta(0,gO2)*ZA(gI2,0) + KroneckerDelta(1,gO2)*ZA(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CphhconjUHpmVWm(int gI2, int gO2) const
{
   const std::complex<double> result = 0.5*g2*(KroneckerDelta(0,gO2)*ZH(gI2,0)
      - KroneckerDelta(1,gO2)*ZH(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpHpmconjUHpmVP(int gI2, int gO2) const
{
   const std::complex<double> result = IF(gI2 < 2,-0.3872983346207417*g1*Cos(
      ThetaW())*ZP(gI2,gO2),0) + IF(gI2 < 2,-0.5*g2*Sin(ThetaW())*ZP(gI2,gO2),0);

   return result;
}

std::complex<double> CLASSNAME::CpHpmconjUHpmVZ(int gI2, int gO2) const
{
   const std::complex<double> result = IF(gI2 < 2,-0.5*g2*Cos(ThetaW())*ZP(gI2,
      gO2),0) + IF(gI2 < 2,0.3872983346207417*g1*Sin(ThetaW())*ZP(gI2,gO2),0);

   return result;
}

double CLASSNAME::CpbarFcFsconjUHpmPR(int gO2) const
{
   const double result = Conj(Yd(1,1))*KroneckerDelta(0,gO2);

   return result;
}

double CLASSNAME::CpbarFcFsconjUHpmPL(int gO1) const
{
   const double result = KroneckerDelta(1,gO1)*Yu(1,1);

   return result;
}

double CLASSNAME::CpbarFtFbconjUHpmPR(int gO2) const
{
   const double result = Conj(Yd(2,2))*KroneckerDelta(0,gO2);

   return result;
}

double CLASSNAME::CpbarFtFbconjUHpmPL(int gO1) const
{
   const double result = KroneckerDelta(1,gO1)*Yu(2,2);

   return result;
}

double CLASSNAME::CpbarFuFdconjUHpmPR(int gO2) const
{
   const double result = Conj(Yd(0,0))*KroneckerDelta(0,gO2);

   return result;
}

double CLASSNAME::CpbarFuFdconjUHpmPL(int gO1) const
{
   const double result = KroneckerDelta(1,gO1)*Yu(0,0);

   return result;
}

double CLASSNAME::CpbarFveFeconjUHpmPR(int gO2) const
{
   const double result = Conj(Ye(0,0))*KroneckerDelta(0,gO2);

   return result;
}

double CLASSNAME::CpbarFveFeconjUHpmPL(int ) const
{
   const double result = 0;

   return result;
}

double CLASSNAME::CpbarFvmFmconjUHpmPR(int gO2) const
{
   const double result = Conj(Ye(1,1))*KroneckerDelta(0,gO2);

   return result;
}

double CLASSNAME::CpbarFvmFmconjUHpmPL(int ) const
{
   const double result = 0;

   return result;
}

double CLASSNAME::CpbarFvtFtauconjUHpmPR(int gO2) const
{
   const double result = Conj(Ye(2,2))*KroneckerDelta(0,gO2);

   return result;
}

double CLASSNAME::CpbarFvtFtauconjUHpmPL(int ) const
{
   const double result = 0;

   return result;
}

double CLASSNAME::CpSveLSveLconjSveLconjSveL() const
{
   const double result = 0.1*(-3*Sqr(g1) - 5*Sqr(g2));

   return result;
}

double CLASSNAME::CpSveLSvmLconjSveLconjSvmL() const
{
   const double result = 0.05*(-3*Sqr(g1) - 5*Sqr(g2));

   return result;
}

double CLASSNAME::CpSveLSvtLconjSveLconjSvtL() const
{
   const double result = 0.05*(-3*Sqr(g1) - 5*Sqr(g2));

   return result;
}

std::complex<double> CLASSNAME::CpSveLconjSveLVZVZ() const
{
   const std::complex<double> result = 0.1*(g1*Sin(ThetaW())*(7.745966692414834
      *g2*Cos(ThetaW()) + 3*g1*Sin(ThetaW())) + 5*Sqr(g2)*Sqr(Cos(ThetaW())));

   return result;
}

double CLASSNAME::CpSveLconjSveLconjVWmVWm() const
{
   const double result = 0.5*Sqr(g2);

   return result;
}

double CLASSNAME::CpSveLconjSveLVZ() const
{
   const double result = 0.5*(g2*Cos(ThetaW()) + 0.7745966692414834*g1*Sin(
      ThetaW()));

   return result;
}

std::complex<double> CLASSNAME::CpSveLAhAhconjSveL(int gI1, int gI2) const
{
   const std::complex<double> result = -0.25*(0.6*Sqr(g1) + Sqr(g2))*(ZA(gI1,0)
      *ZA(gI2,0) - ZA(gI1,1)*ZA(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpSveLhhhhconjSveL(int gI1, int gI2) const
{
   const std::complex<double> result = -0.25*(0.6*Sqr(g1) + Sqr(g2))*(ZH(gI1,0)
      *ZH(gI2,0) - ZH(gI1,1)*ZH(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpSveLHpmconjSveLconjHpm(int gI1, int gI2) const
{
   const std::complex<double> result = 0.25*((-4*AbsSqr(Ye(0,0)) - 0.6*Sqr(g1)
      + Sqr(g2))*ZP(gI1,0)*ZP(gI2,0) + (0.6*Sqr(g1) - Sqr(g2))*ZP(gI1,1)*ZP(gI2,1)
      );

   return result;
}

std::complex<double> CLASSNAME::CpSveLSbconjSveLconjSb(int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZB(gI1,0))*(Sqr(g1) + 5*Sqr(
      g2))*ZB(gI2,0) + 2*Conj(ZB(gI1,1))*Sqr(g1)*ZB(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpSveLScconjSveLconjSc(int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZC(gI1,0))*(Sqr(g1) - 5*Sqr(
      g2))*ZC(gI2,0) - 4*Conj(ZC(gI1,1))*Sqr(g1)*ZC(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpSveLSdconjSveLconjSd(int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZD(gI1,0))*(Sqr(g1) + 5*Sqr(
      g2))*ZD(gI2,0) + 2*Conj(ZD(gI1,1))*Sqr(g1)*ZD(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpSveLSeconjSveLconjSe(int gI1, int gI2) const
{
   const std::complex<double> result = 0.25*(-(Conj(ZE(gI1,0))*(0.6*Sqr(g1) +
      Sqr(g2))*ZE(gI2,0)) + 2*Conj(ZE(gI1,1))*(-2*AbsSqr(Ye(0,0)) + 0.6*Sqr(g1))*
      ZE(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpSveLSmconjSveLconjSm(int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZM(gI1,0))*(-3*Sqr(g1) + 5*
      Sqr(g2))*ZM(gI2,0) + 6*Conj(ZM(gI1,1))*Sqr(g1)*ZM(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpSveLSsconjSveLconjSs(int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZS(gI1,0))*(Sqr(g1) + 5*Sqr(
      g2))*ZS(gI2,0) + 2*Conj(ZS(gI1,1))*Sqr(g1)*ZS(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpSveLStconjSveLconjSt(int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZT(gI1,0))*(Sqr(g1) - 5*Sqr(
      g2))*ZT(gI2,0) - 4*Conj(ZT(gI1,1))*Sqr(g1)*ZT(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpSveLStauconjSveLconjStau(int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZTau(gI1,0))*(-3*Sqr(g1) + 5*
      Sqr(g2))*ZTau(gI2,0) + 6*Conj(ZTau(gI1,1))*Sqr(g1)*ZTau(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpSveLSuconjSveLconjSu(int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZU(gI1,0))*(Sqr(g1) - 5*Sqr(
      g2))*ZU(gI2,0) - 4*Conj(ZU(gI1,1))*Sqr(g1)*ZU(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpSeconjSveLconjHpm(int gI2, int gI1) const
{
   const std::complex<double> result = Conj(ZE(gI2,1))*(Conj(TYe(0,0))*ZP(gI1,0
      ) + Conj(Ye(0,0))*Mu*ZP(gI1,1)) - 0.35355339059327373*Conj(ZE(gI2,0))*(vd*(
      -2*AbsSqr(Ye(0,0)) + Sqr(g2))*ZP(gI1,0) + vu*Sqr(g2)*ZP(gI1,1));

   return result;
}

std::complex<double> CLASSNAME::CpbarChaFeconjSveLPR(int gI1) const
{
   const std::complex<double> result = Conj(Ye(0,0))*UM(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpbarChaFeconjSveLPL(int gI1) const
{
   const std::complex<double> result = -(g2*Conj(UP(gI1,0)));

   return result;
}

std::complex<double> CLASSNAME::CpSveLhhconjSveL(int gI2) const
{
   const std::complex<double> result = -0.25*(0.6*Sqr(g1) + Sqr(g2))*(vd*ZH(gI2
      ,0) - vu*ZH(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpSeconjSveLconjVWm(int gI2) const
{
   const std::complex<double> result = 0.7071067811865475*g2*Conj(ZE(gI2,0));

   return result;
}

double CLASSNAME::CpChiFveconjSveLPR(int ) const
{
   const double result = 0;

   return result;
}

std::complex<double> CLASSNAME::CpChiFveconjSveLPL(int gI2) const
{
   const std::complex<double> result = 0.7071067811865475*(0.7745966692414834*
      g1*Conj(ZN(gI2,0)) - g2*Conj(ZN(gI2,1)));

   return result;
}

double CLASSNAME::CpSvmLSvmLconjSvmLconjSvmL() const
{
   const double result = 0.1*(-3*Sqr(g1) - 5*Sqr(g2));

   return result;
}

double CLASSNAME::CpSvmLSvtLconjSvmLconjSvtL() const
{
   const double result = 0.05*(-3*Sqr(g1) - 5*Sqr(g2));

   return result;
}

std::complex<double> CLASSNAME::CpSvmLconjSvmLVZVZ() const
{
   const std::complex<double> result = 0.1*(g1*Sin(ThetaW())*(7.745966692414834
      *g2*Cos(ThetaW()) + 3*g1*Sin(ThetaW())) + 5*Sqr(g2)*Sqr(Cos(ThetaW())));

   return result;
}

double CLASSNAME::CpSvmLconjSvmLconjVWmVWm() const
{
   const double result = 0.5*Sqr(g2);

   return result;
}

double CLASSNAME::CpSvmLconjSvmLVZ() const
{
   const double result = 0.5*(g2*Cos(ThetaW()) + 0.7745966692414834*g1*Sin(
      ThetaW()));

   return result;
}

std::complex<double> CLASSNAME::CpSvmLAhAhconjSvmL(int gI1, int gI2) const
{
   const std::complex<double> result = -0.25*(0.6*Sqr(g1) + Sqr(g2))*(ZA(gI1,0)
      *ZA(gI2,0) - ZA(gI1,1)*ZA(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpSvmLhhhhconjSvmL(int gI1, int gI2) const
{
   const std::complex<double> result = -0.25*(0.6*Sqr(g1) + Sqr(g2))*(ZH(gI1,0)
      *ZH(gI2,0) - ZH(gI1,1)*ZH(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpSvmLHpmconjSvmLconjHpm(int gI1, int gI2) const
{
   const std::complex<double> result = 0.25*((-4*AbsSqr(Ye(1,1)) - 0.6*Sqr(g1)
      + Sqr(g2))*ZP(gI1,0)*ZP(gI2,0) + (0.6*Sqr(g1) - Sqr(g2))*ZP(gI1,1)*ZP(gI2,1)
      );

   return result;
}

std::complex<double> CLASSNAME::CpSvmLSbconjSvmLconjSb(int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZB(gI1,0))*(Sqr(g1) + 5*Sqr(
      g2))*ZB(gI2,0) + 2*Conj(ZB(gI1,1))*Sqr(g1)*ZB(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpSvmLScconjSvmLconjSc(int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZC(gI1,0))*(Sqr(g1) - 5*Sqr(
      g2))*ZC(gI2,0) - 4*Conj(ZC(gI1,1))*Sqr(g1)*ZC(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpSvmLSdconjSvmLconjSd(int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZD(gI1,0))*(Sqr(g1) + 5*Sqr(
      g2))*ZD(gI2,0) + 2*Conj(ZD(gI1,1))*Sqr(g1)*ZD(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpSvmLSeconjSvmLconjSe(int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZE(gI1,0))*(-3*Sqr(g1) + 5*
      Sqr(g2))*ZE(gI2,0) + 6*Conj(ZE(gI1,1))*Sqr(g1)*ZE(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpSvmLSmconjSvmLconjSm(int gI1, int gI2) const
{
   const std::complex<double> result = 0.25*(-(Conj(ZM(gI1,0))*(0.6*Sqr(g1) +
      Sqr(g2))*ZM(gI2,0)) + 2*Conj(ZM(gI1,1))*(-2*AbsSqr(Ye(1,1)) + 0.6*Sqr(g1))*
      ZM(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpSvmLSsconjSvmLconjSs(int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZS(gI1,0))*(Sqr(g1) + 5*Sqr(
      g2))*ZS(gI2,0) + 2*Conj(ZS(gI1,1))*Sqr(g1)*ZS(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpSvmLStconjSvmLconjSt(int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZT(gI1,0))*(Sqr(g1) - 5*Sqr(
      g2))*ZT(gI2,0) - 4*Conj(ZT(gI1,1))*Sqr(g1)*ZT(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpSvmLStauconjSvmLconjStau(int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZTau(gI1,0))*(-3*Sqr(g1) + 5*
      Sqr(g2))*ZTau(gI2,0) + 6*Conj(ZTau(gI1,1))*Sqr(g1)*ZTau(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpSvmLSuconjSvmLconjSu(int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZU(gI1,0))*(Sqr(g1) - 5*Sqr(
      g2))*ZU(gI2,0) - 4*Conj(ZU(gI1,1))*Sqr(g1)*ZU(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpSmconjSvmLconjHpm(int gI2, int gI1) const
{
   const std::complex<double> result = Conj(ZM(gI2,1))*(Conj(TYe(1,1))*ZP(gI1,0
      ) + Conj(Ye(1,1))*Mu*ZP(gI1,1)) - 0.35355339059327373*Conj(ZM(gI2,0))*(vd*(
      -2*AbsSqr(Ye(1,1)) + Sqr(g2))*ZP(gI1,0) + vu*Sqr(g2)*ZP(gI1,1));

   return result;
}

std::complex<double> CLASSNAME::CpbarChaFmconjSvmLPR(int gI1) const
{
   const std::complex<double> result = Conj(Ye(1,1))*UM(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpbarChaFmconjSvmLPL(int gI1) const
{
   const std::complex<double> result = -(g2*Conj(UP(gI1,0)));

   return result;
}

std::complex<double> CLASSNAME::CpSvmLhhconjSvmL(int gI2) const
{
   const std::complex<double> result = -0.25*(0.6*Sqr(g1) + Sqr(g2))*(vd*ZH(gI2
      ,0) - vu*ZH(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpSmconjSvmLconjVWm(int gI2) const
{
   const std::complex<double> result = 0.7071067811865475*g2*Conj(ZM(gI2,0));

   return result;
}

double CLASSNAME::CpChiFvmconjSvmLPR(int ) const
{
   const double result = 0;

   return result;
}

std::complex<double> CLASSNAME::CpChiFvmconjSvmLPL(int gI2) const
{
   const std::complex<double> result = 0.7071067811865475*(0.7745966692414834*
      g1*Conj(ZN(gI2,0)) - g2*Conj(ZN(gI2,1)));

   return result;
}

double CLASSNAME::CpSvtLSvtLconjSvtLconjSvtL() const
{
   const double result = 0.1*(-3*Sqr(g1) - 5*Sqr(g2));

   return result;
}

std::complex<double> CLASSNAME::CpSvtLconjSvtLVZVZ() const
{
   const std::complex<double> result = 0.1*(g1*Sin(ThetaW())*(7.745966692414834
      *g2*Cos(ThetaW()) + 3*g1*Sin(ThetaW())) + 5*Sqr(g2)*Sqr(Cos(ThetaW())));

   return result;
}

double CLASSNAME::CpSvtLconjSvtLconjVWmVWm() const
{
   const double result = 0.5*Sqr(g2);

   return result;
}

double CLASSNAME::CpSvtLconjSvtLVZ() const
{
   const double result = 0.5*(g2*Cos(ThetaW()) + 0.7745966692414834*g1*Sin(
      ThetaW()));

   return result;
}

std::complex<double> CLASSNAME::CpSvtLAhAhconjSvtL(int gI1, int gI2) const
{
   const std::complex<double> result = -0.25*(0.6*Sqr(g1) + Sqr(g2))*(ZA(gI1,0)
      *ZA(gI2,0) - ZA(gI1,1)*ZA(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpSvtLhhhhconjSvtL(int gI1, int gI2) const
{
   const std::complex<double> result = -0.25*(0.6*Sqr(g1) + Sqr(g2))*(ZH(gI1,0)
      *ZH(gI2,0) - ZH(gI1,1)*ZH(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpSvtLHpmconjSvtLconjHpm(int gI1, int gI2) const
{
   const std::complex<double> result = 0.25*((-4*AbsSqr(Ye(2,2)) - 0.6*Sqr(g1)
      + Sqr(g2))*ZP(gI1,0)*ZP(gI2,0) + (0.6*Sqr(g1) - Sqr(g2))*ZP(gI1,1)*ZP(gI2,1)
      );

   return result;
}

std::complex<double> CLASSNAME::CpSvtLSbconjSvtLconjSb(int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZB(gI1,0))*(Sqr(g1) + 5*Sqr(
      g2))*ZB(gI2,0) + 2*Conj(ZB(gI1,1))*Sqr(g1)*ZB(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpSvtLScconjSvtLconjSc(int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZC(gI1,0))*(Sqr(g1) - 5*Sqr(
      g2))*ZC(gI2,0) - 4*Conj(ZC(gI1,1))*Sqr(g1)*ZC(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpSvtLSdconjSvtLconjSd(int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZD(gI1,0))*(Sqr(g1) + 5*Sqr(
      g2))*ZD(gI2,0) + 2*Conj(ZD(gI1,1))*Sqr(g1)*ZD(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpSvtLSeconjSvtLconjSe(int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZE(gI1,0))*(-3*Sqr(g1) + 5*
      Sqr(g2))*ZE(gI2,0) + 6*Conj(ZE(gI1,1))*Sqr(g1)*ZE(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpSvtLSmconjSvtLconjSm(int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZM(gI1,0))*(-3*Sqr(g1) + 5*
      Sqr(g2))*ZM(gI2,0) + 6*Conj(ZM(gI1,1))*Sqr(g1)*ZM(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpSvtLSsconjSvtLconjSs(int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZS(gI1,0))*(Sqr(g1) + 5*Sqr(
      g2))*ZS(gI2,0) + 2*Conj(ZS(gI1,1))*Sqr(g1)*ZS(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpSvtLStconjSvtLconjSt(int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZT(gI1,0))*(Sqr(g1) - 5*Sqr(
      g2))*ZT(gI2,0) - 4*Conj(ZT(gI1,1))*Sqr(g1)*ZT(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpSvtLStauconjSvtLconjStau(int gI1, int gI2) const
{
   const std::complex<double> result = 0.25*(-(Conj(ZTau(gI1,0))*(0.6*Sqr(g1) +
      Sqr(g2))*ZTau(gI2,0)) + 2*Conj(ZTau(gI1,1))*(-2*AbsSqr(Ye(2,2)) + 0.6*Sqr(
      g1))*ZTau(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpSvtLSuconjSvtLconjSu(int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(Conj(ZU(gI1,0))*(Sqr(g1) - 5*Sqr(
      g2))*ZU(gI2,0) - 4*Conj(ZU(gI1,1))*Sqr(g1)*ZU(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpStauconjSvtLconjHpm(int gI2, int gI1) const
{
   const std::complex<double> result = Conj(ZTau(gI2,1))*(Conj(TYe(2,2))*ZP(gI1
      ,0) + Conj(Ye(2,2))*Mu*ZP(gI1,1)) - 0.35355339059327373*Conj(ZTau(gI2,0))*(
      vd*(-2*AbsSqr(Ye(2,2)) + Sqr(g2))*ZP(gI1,0) + vu*Sqr(g2)*ZP(gI1,1));

   return result;
}

std::complex<double> CLASSNAME::CpbarChaFtauconjSvtLPR(int gI1) const
{
   const std::complex<double> result = Conj(Ye(2,2))*UM(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpbarChaFtauconjSvtLPL(int gI1) const
{
   const std::complex<double> result = -(g2*Conj(UP(gI1,0)));

   return result;
}

std::complex<double> CLASSNAME::CpSvtLhhconjSvtL(int gI2) const
{
   const std::complex<double> result = -0.25*(0.6*Sqr(g1) + Sqr(g2))*(vd*ZH(gI2
      ,0) - vu*ZH(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpStauconjSvtLconjVWm(int gI2) const
{
   const std::complex<double> result = 0.7071067811865475*g2*Conj(ZTau(gI2,0));

   return result;
}

double CLASSNAME::CpChiFvtconjSvtLPR(int ) const
{
   const double result = 0;

   return result;
}

std::complex<double> CLASSNAME::CpChiFvtconjSvtLPL(int gI2) const
{
   const std::complex<double> result = 0.7071067811865475*(0.7745966692414834*
      g1*Conj(ZN(gI2,0)) - g2*Conj(ZN(gI2,1)));

   return result;
}

std::complex<double> CLASSNAME::CpVGVGVG() const
{
   const std::complex<double> result = std::complex<double>(0,-1)*g3;

   return result;
}

std::complex<double> CLASSNAME::CpbargGgGVG() const
{
   const std::complex<double> result = std::complex<double>(0,-1)*g3;

   return result;
}

std::complex<double> CLASSNAME::CpSbconjSbVGVG(int gI1, int gI2) const
{
   const std::complex<double> result = 6*Sqr(g3)*(Conj(ZB(gI1,0))*ZB(gI2,0) +
      Conj(ZB(gI1,1))*ZB(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpScconjScVGVG(int gI1, int gI2) const
{
   const std::complex<double> result = 6*Sqr(g3)*(Conj(ZC(gI1,0))*ZC(gI2,0) +
      Conj(ZC(gI1,1))*ZC(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpSdconjSdVGVG(int gI1, int gI2) const
{
   const std::complex<double> result = 6*Sqr(g3)*(Conj(ZD(gI1,0))*ZD(gI2,0) +
      Conj(ZD(gI1,1))*ZD(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpSsconjSsVGVG(int gI1, int gI2) const
{
   const std::complex<double> result = 6*Sqr(g3)*(Conj(ZS(gI1,0))*ZS(gI2,0) +
      Conj(ZS(gI1,1))*ZS(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpStconjStVGVG(int gI1, int gI2) const
{
   const std::complex<double> result = 6*Sqr(g3)*(Conj(ZT(gI1,0))*ZT(gI2,0) +
      Conj(ZT(gI1,1))*ZT(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpSuconjSuVGVG(int gI1, int gI2) const
{
   const std::complex<double> result = 6*Sqr(g3)*(Conj(ZU(gI1,0))*ZU(gI2,0) +
      Conj(ZU(gI1,1))*ZU(gI2,1));

   return result;
}

double CLASSNAME::CpSbconjSbVG(int gI2, int gI1) const
{
   const double result = g3*KroneckerDelta(gI1,gI2);

   return result;
}

double CLASSNAME::CpScconjScVG(int gI2, int gI1) const
{
   const double result = g3*KroneckerDelta(gI1,gI2);

   return result;
}

double CLASSNAME::CpSdconjSdVG(int gI2, int gI1) const
{
   const double result = g3*KroneckerDelta(gI1,gI2);

   return result;
}

double CLASSNAME::CpSsconjSsVG(int gI2, int gI1) const
{
   const double result = g3*KroneckerDelta(gI1,gI2);

   return result;
}

double CLASSNAME::CpStconjStVG(int gI2, int gI1) const
{
   const double result = g3*KroneckerDelta(gI1,gI2);

   return result;
}

double CLASSNAME::CpSuconjSuVG(int gI2, int gI1) const
{
   const double result = g3*KroneckerDelta(gI1,gI2);

   return result;
}

std::complex<double> CLASSNAME::CpGluGluVGPL() const
{
   const std::complex<double> result = std::complex<double>(0,1)*g3*AbsSqr(
      PhaseGlu);

   return result;
}

std::complex<double> CLASSNAME::CpGluGluVGPR() const
{
   const std::complex<double> result = std::complex<double>(0,1)*g3*AbsSqr(
      PhaseGlu);

   return result;
}

double CLASSNAME::CpbarFbFbVGPL() const
{
   const double result = -g3;

   return result;
}

double CLASSNAME::CpbarFbFbVGPR() const
{
   const double result = -g3;

   return result;
}

double CLASSNAME::CpbarFcFcVGPL() const
{
   const double result = -g3;

   return result;
}

double CLASSNAME::CpbarFcFcVGPR() const
{
   const double result = -g3;

   return result;
}

double CLASSNAME::CpbarFdFdVGPL() const
{
   const double result = -g3;

   return result;
}

double CLASSNAME::CpbarFdFdVGPR() const
{
   const double result = -g3;

   return result;
}

double CLASSNAME::CpbarFsFsVGPL() const
{
   const double result = -g3;

   return result;
}

double CLASSNAME::CpbarFsFsVGPR() const
{
   const double result = -g3;

   return result;
}

double CLASSNAME::CpbarFtFtVGPL() const
{
   const double result = -g3;

   return result;
}

double CLASSNAME::CpbarFtFtVGPR() const
{
   const double result = -g3;

   return result;
}

double CLASSNAME::CpbarFuFuVGPL() const
{
   const double result = -g3;

   return result;
}

double CLASSNAME::CpbarFuFuVGPR() const
{
   const double result = -g3;

   return result;
}

double CLASSNAME::CpVGVGVGVG1() const
{
   const double result = -16*Sqr(g3);

   return result;
}

double CLASSNAME::CpVGVGVGVG2() const
{
   const double result = 0;

   return result;
}

double CLASSNAME::CpVGVGVGVG3() const
{
   const double result = 16*Sqr(g3);

   return result;
}

double CLASSNAME::CpbargWmgWmVP() const
{
   const double result = -(g2*Sin(ThetaW()));

   return result;
}

double CLASSNAME::CpbargWmCgWmCVP() const
{
   const double result = g2*Sin(ThetaW());

   return result;
}

double CLASSNAME::CpconjVWmVPVWm() const
{
   const double result = g2*Sin(ThetaW());

   return result;
}

double CLASSNAME::CpbarFeFeVPPL() const
{
   const double result = 0.5*(0.7745966692414834*g1*Cos(ThetaW()) + g2*Sin(
      ThetaW()));

   return result;
}

double CLASSNAME::CpbarFeFeVPPR() const
{
   const double result = 0.7745966692414834*g1*Cos(ThetaW());

   return result;
}

double CLASSNAME::CpbarFmFmVPPL() const
{
   const double result = 0.5*(0.7745966692414834*g1*Cos(ThetaW()) + g2*Sin(
      ThetaW()));

   return result;
}

double CLASSNAME::CpbarFmFmVPPR() const
{
   const double result = 0.7745966692414834*g1*Cos(ThetaW());

   return result;
}

double CLASSNAME::CpbarFtauFtauVPPL() const
{
   const double result = 0.5*(0.7745966692414834*g1*Cos(ThetaW()) + g2*Sin(
      ThetaW()));

   return result;
}

double CLASSNAME::CpbarFtauFtauVPPR() const
{
   const double result = 0.7745966692414834*g1*Cos(ThetaW());

   return result;
}

std::complex<double> CLASSNAME::CpHpmconjHpmVPVP(int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(7.745966692414834*g1*g2*Sin(2*
      ThetaW()) + 3*Sqr(g1) + Cos(2*ThetaW())*(3*Sqr(g1) - 5*Sqr(g2)) + 5*Sqr(g2))
      *(ZP(gI1,0)*ZP(gI2,0) + ZP(gI1,1)*ZP(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpSbconjSbVPVP(int gI1, int gI2) const
{
   const std::complex<double> result = 0.03333333333333333*(Conj(ZB(gI1,0))*(
      -7.745966692414834*g1*g2*Cos(ThetaW())*Sin(ThetaW()) + Sqr(g1)*Sqr(Cos(
      ThetaW())) + 15*Sqr(g2)*Sqr(Sin(ThetaW())))*ZB(gI2,0) + 4*Conj(ZB(gI1,1))*
      Sqr(g1)*Sqr(Cos(ThetaW()))*ZB(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpScconjScVPVP(int gI1, int gI2) const
{
   const std::complex<double> result = 0.03333333333333333*(Conj(ZC(gI1,0))*(g2
      *Sin(ThetaW())*(7.745966692414834*g1*Cos(ThetaW()) + 15*g2*Sin(ThetaW())) +
      Sqr(g1)*Sqr(Cos(ThetaW())))*ZC(gI2,0) + 16*Conj(ZC(gI1,1))*Sqr(g1)*Sqr(Cos(
      ThetaW()))*ZC(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpSdconjSdVPVP(int gI1, int gI2) const
{
   const std::complex<double> result = 0.03333333333333333*(Conj(ZD(gI1,0))*(
      -7.745966692414834*g1*g2*Cos(ThetaW())*Sin(ThetaW()) + Sqr(g1)*Sqr(Cos(
      ThetaW())) + 15*Sqr(g2)*Sqr(Sin(ThetaW())))*ZD(gI2,0) + 4*Conj(ZD(gI1,1))*
      Sqr(g1)*Sqr(Cos(ThetaW()))*ZD(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpSeconjSeVPVP(int gI1, int gI2) const
{
   const std::complex<double> result = 0.1*(Conj(ZE(gI1,0))*(g2*Sin(ThetaW())*(
      7.745966692414834*g1*Cos(ThetaW()) + 5*g2*Sin(ThetaW())) + 3*Sqr(g1)*Sqr(Cos
      (ThetaW())))*ZE(gI2,0) + 12*Conj(ZE(gI1,1))*Sqr(g1)*Sqr(Cos(ThetaW()))*ZE(
      gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpSmconjSmVPVP(int gI1, int gI2) const
{
   const std::complex<double> result = 0.1*(Conj(ZM(gI1,0))*(g2*Sin(ThetaW())*(
      7.745966692414834*g1*Cos(ThetaW()) + 5*g2*Sin(ThetaW())) + 3*Sqr(g1)*Sqr(Cos
      (ThetaW())))*ZM(gI2,0) + 12*Conj(ZM(gI1,1))*Sqr(g1)*Sqr(Cos(ThetaW()))*ZM(
      gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpSsconjSsVPVP(int gI1, int gI2) const
{
   const std::complex<double> result = 0.03333333333333333*(Conj(ZS(gI1,0))*(
      -7.745966692414834*g1*g2*Cos(ThetaW())*Sin(ThetaW()) + Sqr(g1)*Sqr(Cos(
      ThetaW())) + 15*Sqr(g2)*Sqr(Sin(ThetaW())))*ZS(gI2,0) + 4*Conj(ZS(gI1,1))*
      Sqr(g1)*Sqr(Cos(ThetaW()))*ZS(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpStconjStVPVP(int gI1, int gI2) const
{
   const std::complex<double> result = 0.03333333333333333*(Conj(ZT(gI1,0))*(g2
      *Sin(ThetaW())*(7.745966692414834*g1*Cos(ThetaW()) + 15*g2*Sin(ThetaW())) +
      Sqr(g1)*Sqr(Cos(ThetaW())))*ZT(gI2,0) + 16*Conj(ZT(gI1,1))*Sqr(g1)*Sqr(Cos(
      ThetaW()))*ZT(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpStauconjStauVPVP(int gI1, int gI2) const
{
   const std::complex<double> result = 0.1*(Conj(ZTau(gI1,0))*(g2*Sin(ThetaW())
      *(7.745966692414834*g1*Cos(ThetaW()) + 5*g2*Sin(ThetaW())) + 3*Sqr(g1)*Sqr(
      Cos(ThetaW())))*ZTau(gI2,0) + 12*Conj(ZTau(gI1,1))*Sqr(g1)*Sqr(Cos(ThetaW())
      )*ZTau(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpSuconjSuVPVP(int gI1, int gI2) const
{
   const std::complex<double> result = 0.03333333333333333*(Conj(ZU(gI1,0))*(g2
      *Sin(ThetaW())*(7.745966692414834*g1*Cos(ThetaW()) + 15*g2*Sin(ThetaW())) +
      Sqr(g1)*Sqr(Cos(ThetaW())))*ZU(gI2,0) + 16*Conj(ZU(gI1,1))*Sqr(g1)*Sqr(Cos(
      ThetaW()))*ZU(gI2,1));

   return result;
}

double CLASSNAME::CpHpmconjHpmVP(int gI2, int gI1) const
{
   const double result = -0.5*KroneckerDelta(gI1,gI2)*(0.7745966692414834*g1*
      Cos(ThetaW()) + g2*Sin(ThetaW()));

   return result;
}

std::complex<double> CLASSNAME::CpSbconjSbVP(int gI2, int gI1) const
{
   const std::complex<double> result = 0.16666666666666666*Conj(ZB(gI2,0))*(
      0.7745966692414834*g1*Cos(ThetaW()) - 3*g2*Sin(ThetaW()))*ZB(gI1,0) -
      0.2581988897471611*g1*Conj(ZB(gI2,1))*Cos(ThetaW())*ZB(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpScconjScVP(int gI2, int gI1) const
{
   const std::complex<double> result = 0.16666666666666666*Conj(ZC(gI2,0))*(
      0.7745966692414834*g1*Cos(ThetaW()) + 3*g2*Sin(ThetaW()))*ZC(gI1,0) +
      0.5163977794943222*g1*Conj(ZC(gI2,1))*Cos(ThetaW())*ZC(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpSdconjSdVP(int gI2, int gI1) const
{
   const std::complex<double> result = 0.16666666666666666*Conj(ZD(gI2,0))*(
      0.7745966692414834*g1*Cos(ThetaW()) - 3*g2*Sin(ThetaW()))*ZD(gI1,0) -
      0.2581988897471611*g1*Conj(ZD(gI2,1))*Cos(ThetaW())*ZD(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpSeconjSeVP(int gI2, int gI1) const
{
   const std::complex<double> result = -0.5*Conj(ZE(gI2,0))*(0.7745966692414834
      *g1*Cos(ThetaW()) + g2*Sin(ThetaW()))*ZE(gI1,0) - 0.7745966692414834*g1*Conj
      (ZE(gI2,1))*Cos(ThetaW())*ZE(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpSmconjSmVP(int gI2, int gI1) const
{
   const std::complex<double> result = -0.5*Conj(ZM(gI2,0))*(0.7745966692414834
      *g1*Cos(ThetaW()) + g2*Sin(ThetaW()))*ZM(gI1,0) - 0.7745966692414834*g1*Conj
      (ZM(gI2,1))*Cos(ThetaW())*ZM(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpSsconjSsVP(int gI2, int gI1) const
{
   const std::complex<double> result = 0.16666666666666666*Conj(ZS(gI2,0))*(
      0.7745966692414834*g1*Cos(ThetaW()) - 3*g2*Sin(ThetaW()))*ZS(gI1,0) -
      0.2581988897471611*g1*Conj(ZS(gI2,1))*Cos(ThetaW())*ZS(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpStconjStVP(int gI2, int gI1) const
{
   const std::complex<double> result = 0.16666666666666666*Conj(ZT(gI2,0))*(
      0.7745966692414834*g1*Cos(ThetaW()) + 3*g2*Sin(ThetaW()))*ZT(gI1,0) +
      0.5163977794943222*g1*Conj(ZT(gI2,1))*Cos(ThetaW())*ZT(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpStauconjStauVP(int gI2, int gI1) const
{
   const std::complex<double> result = -0.5*Conj(ZTau(gI2,0))*(
      0.7745966692414834*g1*Cos(ThetaW()) + g2*Sin(ThetaW()))*ZTau(gI1,0) -
      0.7745966692414834*g1*Conj(ZTau(gI2,1))*Cos(ThetaW())*ZTau(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpSuconjSuVP(int gI2, int gI1) const
{
   const std::complex<double> result = 0.16666666666666666*Conj(ZU(gI2,0))*(
      0.7745966692414834*g1*Cos(ThetaW()) + 3*g2*Sin(ThetaW()))*ZU(gI1,0) +
      0.5163977794943222*g1*Conj(ZU(gI2,1))*Cos(ThetaW())*ZU(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpbarChaChaVPPL(int gI1, int gI2) const
{
   const std::complex<double> result = g2*Conj(UM(gI2,0))*Sin(ThetaW())*UM(gI1,
      0) + 0.5*Conj(UM(gI2,1))*(0.7745966692414834*g1*Cos(ThetaW()) + g2*Sin(
      ThetaW()))*UM(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpbarChaChaVPPR(int gI1, int gI2) const
{
   const std::complex<double> result = g2*Conj(UP(gI1,0))*Sin(ThetaW())*UP(gI2,
      0) + 0.5*Conj(UP(gI1,1))*(0.7745966692414834*g1*Cos(ThetaW()) + g2*Sin(
      ThetaW()))*UP(gI2,1);

   return result;
}

std::complex<double> CLASSNAME::CpHpmconjVWmVP(int gI2) const
{
   const std::complex<double> result = -0.3872983346207417*g1*g2*Cos(ThetaW())*
      (vd*ZP(gI2,0) - vu*ZP(gI2,1));

   return result;
}

double CLASSNAME::CpbarFbFbVPPL() const
{
   const double result = 0.16666666666666666*(-0.7745966692414834*g1*Cos(ThetaW
      ()) + 3*g2*Sin(ThetaW()));

   return result;
}

double CLASSNAME::CpbarFbFbVPPR() const
{
   const double result = 0.2581988897471611*g1*Cos(ThetaW());

   return result;
}

double CLASSNAME::CpbarFcFcVPPL() const
{
   const double result = 0.16666666666666666*(-0.7745966692414834*g1*Cos(ThetaW
      ()) - 3*g2*Sin(ThetaW()));

   return result;
}

double CLASSNAME::CpbarFcFcVPPR() const
{
   const double result = -0.5163977794943222*g1*Cos(ThetaW());

   return result;
}

double CLASSNAME::CpbarFdFdVPPL() const
{
   const double result = 0.16666666666666666*(-0.7745966692414834*g1*Cos(ThetaW
      ()) + 3*g2*Sin(ThetaW()));

   return result;
}

double CLASSNAME::CpbarFdFdVPPR() const
{
   const double result = 0.2581988897471611*g1*Cos(ThetaW());

   return result;
}

double CLASSNAME::CpbarFsFsVPPL() const
{
   const double result = 0.16666666666666666*(-0.7745966692414834*g1*Cos(ThetaW
      ()) + 3*g2*Sin(ThetaW()));

   return result;
}

double CLASSNAME::CpbarFsFsVPPR() const
{
   const double result = 0.2581988897471611*g1*Cos(ThetaW());

   return result;
}

double CLASSNAME::CpbarFtFtVPPL() const
{
   const double result = 0.16666666666666666*(-0.7745966692414834*g1*Cos(ThetaW
      ()) - 3*g2*Sin(ThetaW()));

   return result;
}

double CLASSNAME::CpbarFtFtVPPR() const
{
   const double result = -0.5163977794943222*g1*Cos(ThetaW());

   return result;
}

double CLASSNAME::CpbarFuFuVPPL() const
{
   const double result = 0.16666666666666666*(-0.7745966692414834*g1*Cos(ThetaW
      ()) - 3*g2*Sin(ThetaW()));

   return result;
}

double CLASSNAME::CpbarFuFuVPPR() const
{
   const double result = -0.5163977794943222*g1*Cos(ThetaW());

   return result;
}

double CLASSNAME::CpconjVWmVPVPVWm1() const
{
   const double result = Sqr(g2)*Sqr(Sin(ThetaW()));

   return result;
}

double CLASSNAME::CpconjVWmVPVPVWm2() const
{
   const double result = Sqr(g2)*Sqr(Sin(ThetaW()));

   return result;
}

double CLASSNAME::CpconjVWmVPVPVWm3() const
{
   const double result = -2*Sqr(g2)*Sqr(Sin(ThetaW()));

   return result;
}

double CLASSNAME::CpbargWmgWmVZ() const
{
   const double result = -(g2*Cos(ThetaW()));

   return result;
}

double CLASSNAME::CpbargWmCgWmCVZ() const
{
   const double result = g2*Cos(ThetaW());

   return result;
}

double CLASSNAME::CpconjVWmVWmVZ() const
{
   const double result = -(g2*Cos(ThetaW()));

   return result;
}

double CLASSNAME::CpbarFeFeVZPL() const
{
   const double result = 0.5*(g2*Cos(ThetaW()) - 0.7745966692414834*g1*Sin(
      ThetaW()));

   return result;
}

double CLASSNAME::CpbarFeFeVZPR() const
{
   const double result = -0.7745966692414834*g1*Sin(ThetaW());

   return result;
}

double CLASSNAME::CpbarFmFmVZPL() const
{
   const double result = 0.5*(g2*Cos(ThetaW()) - 0.7745966692414834*g1*Sin(
      ThetaW()));

   return result;
}

double CLASSNAME::CpbarFmFmVZPR() const
{
   const double result = -0.7745966692414834*g1*Sin(ThetaW());

   return result;
}

double CLASSNAME::CpbarFtauFtauVZPL() const
{
   const double result = 0.5*(g2*Cos(ThetaW()) - 0.7745966692414834*g1*Sin(
      ThetaW()));

   return result;
}

double CLASSNAME::CpbarFtauFtauVZPR() const
{
   const double result = -0.7745966692414834*g1*Sin(ThetaW());

   return result;
}

double CLASSNAME::CpbarFveFveVZPL() const
{
   const double result = 0.1*(-5*g2*Cos(ThetaW()) - 3.872983346207417*g1*Sin(
      ThetaW()));

   return result;
}

double CLASSNAME::CpbarFveFveVZPR() const
{
   const double result = 0;

   return result;
}

double CLASSNAME::CpbarFvmFvmVZPL() const
{
   const double result = 0.1*(-5*g2*Cos(ThetaW()) - 3.872983346207417*g1*Sin(
      ThetaW()));

   return result;
}

double CLASSNAME::CpbarFvmFvmVZPR() const
{
   const double result = 0;

   return result;
}

double CLASSNAME::CpbarFvtFvtVZPL() const
{
   const double result = 0.1*(-5*g2*Cos(ThetaW()) - 3.872983346207417*g1*Sin(
      ThetaW()));

   return result;
}

double CLASSNAME::CpbarFvtFvtVZPR() const
{
   const double result = 0;

   return result;
}

std::complex<double> CLASSNAME::CpAhAhVZVZ(int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(7.745966692414834*g1*g2*Sin(2*
      ThetaW()) + 3*Sqr(g1) + 5*Sqr(g2) + Cos(2*ThetaW())*(-3*Sqr(g1) + 5*Sqr(g2))
      )*(ZA(gI1,0)*ZA(gI2,0) + ZA(gI1,1)*ZA(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CphhhhVZVZ(int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(7.745966692414834*g1*g2*Sin(2*
      ThetaW()) + 3*Sqr(g1) + 5*Sqr(g2) + Cos(2*ThetaW())*(-3*Sqr(g1) + 5*Sqr(g2))
      )*(ZH(gI1,0)*ZH(gI2,0) + ZH(gI1,1)*ZH(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpHpmconjHpmVZVZ(int gI1, int gI2) const
{
   const std::complex<double> result = 0.05*(-7.745966692414834*g1*g2*Sin(2*
      ThetaW()) + 3*Sqr(g1) + 5*Sqr(g2) + Cos(2*ThetaW())*(-3*Sqr(g1) + 5*Sqr(g2))
      )*(ZP(gI1,0)*ZP(gI2,0) + ZP(gI1,1)*ZP(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpSbconjSbVZVZ(int gI1, int gI2) const
{
   const std::complex<double> result = 0.03333333333333333*(Conj(ZB(gI1,0))*(g1
      *Sin(ThetaW())*(7.745966692414834*g2*Cos(ThetaW()) + g1*Sin(ThetaW())) + 15*
      Sqr(g2)*Sqr(Cos(ThetaW())))*ZB(gI2,0) + 4*Conj(ZB(gI1,1))*Sqr(g1)*Sqr(Sin(
      ThetaW()))*ZB(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpScconjScVZVZ(int gI1, int gI2) const
{
   const std::complex<double> result = 0.03333333333333333*(Conj(ZC(gI1,0))*(
      -7.745966692414834*g1*g2*Cos(ThetaW())*Sin(ThetaW()) + 15*Sqr(g2)*Sqr(Cos(
      ThetaW())) + Sqr(g1)*Sqr(Sin(ThetaW())))*ZC(gI2,0) + 16*Conj(ZC(gI1,1))*Sqr(
      g1)*Sqr(Sin(ThetaW()))*ZC(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpSdconjSdVZVZ(int gI1, int gI2) const
{
   const std::complex<double> result = 0.03333333333333333*(Conj(ZD(gI1,0))*(g1
      *Sin(ThetaW())*(7.745966692414834*g2*Cos(ThetaW()) + g1*Sin(ThetaW())) + 15*
      Sqr(g2)*Sqr(Cos(ThetaW())))*ZD(gI2,0) + 4*Conj(ZD(gI1,1))*Sqr(g1)*Sqr(Sin(
      ThetaW()))*ZD(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpSeconjSeVZVZ(int gI1, int gI2) const
{
   const std::complex<double> result = 0.1*(Conj(ZE(gI1,0))*(-7.745966692414834
      *g1*g2*Cos(ThetaW())*Sin(ThetaW()) + 5*Sqr(g2)*Sqr(Cos(ThetaW())) + 3*Sqr(g1
      )*Sqr(Sin(ThetaW())))*ZE(gI2,0) + 12*Conj(ZE(gI1,1))*Sqr(g1)*Sqr(Sin(ThetaW(
      )))*ZE(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpSmconjSmVZVZ(int gI1, int gI2) const
{
   const std::complex<double> result = 0.1*(Conj(ZM(gI1,0))*(-7.745966692414834
      *g1*g2*Cos(ThetaW())*Sin(ThetaW()) + 5*Sqr(g2)*Sqr(Cos(ThetaW())) + 3*Sqr(g1
      )*Sqr(Sin(ThetaW())))*ZM(gI2,0) + 12*Conj(ZM(gI1,1))*Sqr(g1)*Sqr(Sin(ThetaW(
      )))*ZM(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpSsconjSsVZVZ(int gI1, int gI2) const
{
   const std::complex<double> result = 0.03333333333333333*(Conj(ZS(gI1,0))*(g1
      *Sin(ThetaW())*(7.745966692414834*g2*Cos(ThetaW()) + g1*Sin(ThetaW())) + 15*
      Sqr(g2)*Sqr(Cos(ThetaW())))*ZS(gI2,0) + 4*Conj(ZS(gI1,1))*Sqr(g1)*Sqr(Sin(
      ThetaW()))*ZS(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpStconjStVZVZ(int gI1, int gI2) const
{
   const std::complex<double> result = 0.03333333333333333*(Conj(ZT(gI1,0))*(
      -7.745966692414834*g1*g2*Cos(ThetaW())*Sin(ThetaW()) + 15*Sqr(g2)*Sqr(Cos(
      ThetaW())) + Sqr(g1)*Sqr(Sin(ThetaW())))*ZT(gI2,0) + 16*Conj(ZT(gI1,1))*Sqr(
      g1)*Sqr(Sin(ThetaW()))*ZT(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpStauconjStauVZVZ(int gI1, int gI2) const
{
   const std::complex<double> result = 0.1*(Conj(ZTau(gI1,0))*(
      -7.745966692414834*g1*g2*Cos(ThetaW())*Sin(ThetaW()) + 5*Sqr(g2)*Sqr(Cos(
      ThetaW())) + 3*Sqr(g1)*Sqr(Sin(ThetaW())))*ZTau(gI2,0) + 12*Conj(ZTau(gI1,1)
      )*Sqr(g1)*Sqr(Sin(ThetaW()))*ZTau(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpSuconjSuVZVZ(int gI1, int gI2) const
{
   const std::complex<double> result = 0.03333333333333333*(Conj(ZU(gI1,0))*(
      -7.745966692414834*g1*g2*Cos(ThetaW())*Sin(ThetaW()) + 15*Sqr(g2)*Sqr(Cos(
      ThetaW())) + Sqr(g1)*Sqr(Sin(ThetaW())))*ZU(gI2,0) + 16*Conj(ZU(gI1,1))*Sqr(
      g1)*Sqr(Sin(ThetaW()))*ZU(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpAhhhVZ(int gI2, int gI1) const
{
   const std::complex<double> result = std::complex<double>(0,0.5)*(g2*Cos(
      ThetaW()) + 0.7745966692414834*g1*Sin(ThetaW()))*(ZA(gI2,0)*ZH(gI1,0) - ZA(
      gI2,1)*ZH(gI1,1));

   return result;
}

double CLASSNAME::CpHpmconjHpmVZ(int gI2, int gI1) const
{
   const double result = 0.1*KroneckerDelta(gI1,gI2)*(-5*g2*Cos(ThetaW()) +
      3.872983346207417*g1*Sin(ThetaW()));

   return result;
}

std::complex<double> CLASSNAME::CpSbconjSbVZ(int gI2, int gI1) const
{
   const std::complex<double> result = -0.16666666666666666*Conj(ZB(gI2,0))*(3*
      g2*Cos(ThetaW()) + 0.7745966692414834*g1*Sin(ThetaW()))*ZB(gI1,0) +
      0.2581988897471611*g1*Conj(ZB(gI2,1))*Sin(ThetaW())*ZB(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpScconjScVZ(int gI2, int gI1) const
{
   const std::complex<double> result = 0.16666666666666666*Conj(ZC(gI2,0))*(3*
      g2*Cos(ThetaW()) - 0.7745966692414834*g1*Sin(ThetaW()))*ZC(gI1,0) -
      0.5163977794943222*g1*Conj(ZC(gI2,1))*Sin(ThetaW())*ZC(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpSdconjSdVZ(int gI2, int gI1) const
{
   const std::complex<double> result = -0.16666666666666666*Conj(ZD(gI2,0))*(3*
      g2*Cos(ThetaW()) + 0.7745966692414834*g1*Sin(ThetaW()))*ZD(gI1,0) +
      0.2581988897471611*g1*Conj(ZD(gI2,1))*Sin(ThetaW())*ZD(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpSeconjSeVZ(int gI2, int gI1) const
{
   const std::complex<double> result = -0.5*Conj(ZE(gI2,0))*(g2*Cos(ThetaW()) -
      0.7745966692414834*g1*Sin(ThetaW()))*ZE(gI1,0) + 0.7745966692414834*g1*Conj
      (ZE(gI2,1))*Sin(ThetaW())*ZE(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpSmconjSmVZ(int gI2, int gI1) const
{
   const std::complex<double> result = -0.5*Conj(ZM(gI2,0))*(g2*Cos(ThetaW()) -
      0.7745966692414834*g1*Sin(ThetaW()))*ZM(gI1,0) + 0.7745966692414834*g1*Conj
      (ZM(gI2,1))*Sin(ThetaW())*ZM(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpSsconjSsVZ(int gI2, int gI1) const
{
   const std::complex<double> result = -0.16666666666666666*Conj(ZS(gI2,0))*(3*
      g2*Cos(ThetaW()) + 0.7745966692414834*g1*Sin(ThetaW()))*ZS(gI1,0) +
      0.2581988897471611*g1*Conj(ZS(gI2,1))*Sin(ThetaW())*ZS(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpStconjStVZ(int gI2, int gI1) const
{
   const std::complex<double> result = 0.16666666666666666*Conj(ZT(gI2,0))*(3*
      g2*Cos(ThetaW()) - 0.7745966692414834*g1*Sin(ThetaW()))*ZT(gI1,0) -
      0.5163977794943222*g1*Conj(ZT(gI2,1))*Sin(ThetaW())*ZT(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpStauconjStauVZ(int gI2, int gI1) const
{
   const std::complex<double> result = -0.5*Conj(ZTau(gI2,0))*(g2*Cos(ThetaW())
      - 0.7745966692414834*g1*Sin(ThetaW()))*ZTau(gI1,0) + 0.7745966692414834*g1*
      Conj(ZTau(gI2,1))*Sin(ThetaW())*ZTau(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpSuconjSuVZ(int gI2, int gI1) const
{
   const std::complex<double> result = 0.16666666666666666*Conj(ZU(gI2,0))*(3*
      g2*Cos(ThetaW()) - 0.7745966692414834*g1*Sin(ThetaW()))*ZU(gI1,0) -
      0.5163977794943222*g1*Conj(ZU(gI2,1))*Sin(ThetaW())*ZU(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpbarChaChaVZPL(int gI1, int gI2) const
{
   const std::complex<double> result = g2*Conj(UM(gI2,0))*Cos(ThetaW())*UM(gI1,
      0) + 0.5*Conj(UM(gI2,1))*(g2*Cos(ThetaW()) - 0.7745966692414834*g1*Sin(
      ThetaW()))*UM(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpbarChaChaVZPR(int gI1, int gI2) const
{
   const std::complex<double> result = g2*Conj(UP(gI1,0))*Cos(ThetaW())*UP(gI2,
      0) + 0.5*Conj(UP(gI1,1))*(g2*Cos(ThetaW()) - 0.7745966692414834*g1*Sin(
      ThetaW()))*UP(gI2,1);

   return result;
}

std::complex<double> CLASSNAME::CpChiChiVZPL(int gI1, int gI2) const
{
   const std::complex<double> result = -0.5*(g2*Cos(ThetaW()) +
      0.7745966692414834*g1*Sin(ThetaW()))*(Conj(ZN(gI2,2))*ZN(gI1,2) - Conj(ZN(
      gI2,3))*ZN(gI1,3));

   return result;
}

std::complex<double> CLASSNAME::CpChiChiVZPR(int gI1, int gI2) const
{
   const std::complex<double> result = 0.5*(g2*Cos(ThetaW()) +
      0.7745966692414834*g1*Sin(ThetaW()))*(Conj(ZN(gI1,2))*ZN(gI2,2) - Conj(ZN(
      gI1,3))*ZN(gI2,3));

   return result;
}

std::complex<double> CLASSNAME::CphhVZVZ(int gI2) const
{
   const std::complex<double> result = 0.5*Sqr(g2*Cos(ThetaW()) +
      0.7745966692414834*g1*Sin(ThetaW()))*(vd*ZH(gI2,0) + vu*ZH(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpHpmconjVWmVZ(int gI2) const
{
   const std::complex<double> result = 0.3872983346207417*g1*g2*Sin(ThetaW())*(
      vd*ZP(gI2,0) - vu*ZP(gI2,1));

   return result;
}

double CLASSNAME::CpbarFbFbVZPL() const
{
   const double result = 0.16666666666666666*(3*g2*Cos(ThetaW()) +
      0.7745966692414834*g1*Sin(ThetaW()));

   return result;
}

double CLASSNAME::CpbarFbFbVZPR() const
{
   const double result = -0.2581988897471611*g1*Sin(ThetaW());

   return result;
}

double CLASSNAME::CpbarFcFcVZPL() const
{
   const double result = 0.16666666666666666*(-3*g2*Cos(ThetaW()) +
      0.7745966692414834*g1*Sin(ThetaW()));

   return result;
}

double CLASSNAME::CpbarFcFcVZPR() const
{
   const double result = 0.5163977794943222*g1*Sin(ThetaW());

   return result;
}

double CLASSNAME::CpbarFdFdVZPL() const
{
   const double result = 0.16666666666666666*(3*g2*Cos(ThetaW()) +
      0.7745966692414834*g1*Sin(ThetaW()));

   return result;
}

double CLASSNAME::CpbarFdFdVZPR() const
{
   const double result = -0.2581988897471611*g1*Sin(ThetaW());

   return result;
}

double CLASSNAME::CpbarFsFsVZPL() const
{
   const double result = 0.16666666666666666*(3*g2*Cos(ThetaW()) +
      0.7745966692414834*g1*Sin(ThetaW()));

   return result;
}

double CLASSNAME::CpbarFsFsVZPR() const
{
   const double result = -0.2581988897471611*g1*Sin(ThetaW());

   return result;
}

double CLASSNAME::CpbarFtFtVZPL() const
{
   const double result = 0.16666666666666666*(-3*g2*Cos(ThetaW()) +
      0.7745966692414834*g1*Sin(ThetaW()));

   return result;
}

double CLASSNAME::CpbarFtFtVZPR() const
{
   const double result = 0.5163977794943222*g1*Sin(ThetaW());

   return result;
}

double CLASSNAME::CpbarFuFuVZPL() const
{
   const double result = 0.16666666666666666*(-3*g2*Cos(ThetaW()) +
      0.7745966692414834*g1*Sin(ThetaW()));

   return result;
}

double CLASSNAME::CpbarFuFuVZPR() const
{
   const double result = 0.5163977794943222*g1*Sin(ThetaW());

   return result;
}

double CLASSNAME::CpconjVWmVWmVZVZ1() const
{
   const double result = -2*Sqr(g2)*Sqr(Cos(ThetaW()));

   return result;
}

double CLASSNAME::CpconjVWmVWmVZVZ2() const
{
   const double result = Sqr(g2)*Sqr(Cos(ThetaW()));

   return result;
}

double CLASSNAME::CpconjVWmVWmVZVZ3() const
{
   const double result = Sqr(g2)*Sqr(Cos(ThetaW()));

   return result;
}

double CLASSNAME::CpbargPgWmconjVWm() const
{
   const double result = g2*Sin(ThetaW());

   return result;
}

double CLASSNAME::CpbargWmCgPconjVWm() const
{
   const double result = -(g2*Sin(ThetaW()));

   return result;
}

double CLASSNAME::CpbargWmCgZconjVWm() const
{
   const double result = -(g2*Cos(ThetaW()));

   return result;
}

double CLASSNAME::CpbargZgWmconjVWm() const
{
   const double result = g2*Cos(ThetaW());

   return result;
}

double CLASSNAME::CpbarFveFeconjVWmPL() const
{
   const double result = -0.7071067811865475*g2;

   return result;
}

double CLASSNAME::CpbarFveFeconjVWmPR() const
{
   const double result = 0;

   return result;
}

double CLASSNAME::CpbarFvmFmconjVWmPL() const
{
   const double result = -0.7071067811865475*g2;

   return result;
}

double CLASSNAME::CpbarFvmFmconjVWmPR() const
{
   const double result = 0;

   return result;
}

double CLASSNAME::CpbarFvtFtauconjVWmPL() const
{
   const double result = -0.7071067811865475*g2;

   return result;
}

double CLASSNAME::CpbarFvtFtauconjVWmPR() const
{
   const double result = 0;

   return result;
}

std::complex<double> CLASSNAME::CpAhAhconjVWmVWm(int gI1, int gI2) const
{
   const std::complex<double> result = 0.5*Sqr(g2)*(ZA(gI1,0)*ZA(gI2,0) + ZA(
      gI1,1)*ZA(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CphhhhconjVWmVWm(int gI1, int gI2) const
{
   const std::complex<double> result = 0.5*Sqr(g2)*(ZH(gI1,0)*ZH(gI2,0) + ZH(
      gI1,1)*ZH(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpHpmconjHpmconjVWmVWm(int gI1, int gI2) const
{
   const std::complex<double> result = 0.5*Sqr(g2)*(ZP(gI1,0)*ZP(gI2,0) + ZP(
      gI1,1)*ZP(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpSbconjSbconjVWmVWm(int gI1, int gI2) const
{
   const std::complex<double> result = 0.5*Conj(ZB(gI1,0))*Sqr(g2)*ZB(gI2,0);

   return result;
}

std::complex<double> CLASSNAME::CpScconjScconjVWmVWm(int gI1, int gI2) const
{
   const std::complex<double> result = 0.5*Conj(ZC(gI1,0))*Sqr(g2)*ZC(gI2,0);

   return result;
}

std::complex<double> CLASSNAME::CpSdconjSdconjVWmVWm(int gI1, int gI2) const
{
   const std::complex<double> result = 0.5*Conj(ZD(gI1,0))*Sqr(g2)*ZD(gI2,0);

   return result;
}

std::complex<double> CLASSNAME::CpSeconjSeconjVWmVWm(int gI1, int gI2) const
{
   const std::complex<double> result = 0.5*Conj(ZE(gI1,0))*Sqr(g2)*ZE(gI2,0);

   return result;
}

std::complex<double> CLASSNAME::CpSmconjSmconjVWmVWm(int gI1, int gI2) const
{
   const std::complex<double> result = 0.5*Conj(ZM(gI1,0))*Sqr(g2)*ZM(gI2,0);

   return result;
}

std::complex<double> CLASSNAME::CpSsconjSsconjVWmVWm(int gI1, int gI2) const
{
   const std::complex<double> result = 0.5*Conj(ZS(gI1,0))*Sqr(g2)*ZS(gI2,0);

   return result;
}

std::complex<double> CLASSNAME::CpStconjStconjVWmVWm(int gI1, int gI2) const
{
   const std::complex<double> result = 0.5*Conj(ZT(gI1,0))*Sqr(g2)*ZT(gI2,0);

   return result;
}

std::complex<double> CLASSNAME::CpStauconjStauconjVWmVWm(int gI1, int gI2) const
{
   const std::complex<double> result = 0.5*Conj(ZTau(gI1,0))*Sqr(g2)*ZTau(gI2,0
      );

   return result;
}

std::complex<double> CLASSNAME::CpSuconjSuconjVWmVWm(int gI1, int gI2) const
{
   const std::complex<double> result = 0.5*Conj(ZU(gI1,0))*Sqr(g2)*ZU(gI2,0);

   return result;
}

std::complex<double> CLASSNAME::CpAhHpmconjVWm(int gI2, int gI1) const
{
   const std::complex<double> result = std::complex<double>(0,0.5)*g2*(ZA(gI2,0
      )*ZP(gI1,0) + ZA(gI2,1)*ZP(gI1,1));

   return result;
}

std::complex<double> CLASSNAME::CphhHpmconjVWm(int gI2, int gI1) const
{
   const std::complex<double> result = -0.5*g2*(ZH(gI2,0)*ZP(gI1,0) - ZH(gI2,1)
      *ZP(gI1,1));

   return result;
}

std::complex<double> CLASSNAME::CpSbconjStconjVWm(int gI2, int gI1) const
{
   const std::complex<double> result = 0.7071067811865475*g2*Conj(ZB(gI2,0))*ZT
      (gI1,0);

   return result;
}

std::complex<double> CLASSNAME::CpSdconjSuconjVWm(int gI2, int gI1) const
{
   const std::complex<double> result = 0.7071067811865475*g2*Conj(ZD(gI2,0))*ZU
      (gI1,0);

   return result;
}

std::complex<double> CLASSNAME::CpSsconjScconjVWm(int gI2, int gI1) const
{
   const std::complex<double> result = 0.7071067811865475*g2*Conj(ZS(gI2,0))*ZC
      (gI1,0);

   return result;
}

std::complex<double> CLASSNAME::CpChiChaconjVWmPL(int gI1, int gI2) const
{
   const std::complex<double> result = -0.5*g2*(2*Conj(UM(gI2,0))*ZN(gI1,1) +
      1.4142135623730951*Conj(UM(gI2,1))*ZN(gI1,2));

   return result;
}

std::complex<double> CLASSNAME::CpChiChaconjVWmPR(int gI1, int gI2) const
{
   const std::complex<double> result = -(g2*Conj(ZN(gI1,1))*UP(gI2,0)) +
      0.7071067811865475*g2*Conj(ZN(gI1,3))*UP(gI2,1);

   return result;
}

std::complex<double> CLASSNAME::CphhconjVWmVWm(int gI2) const
{
   const std::complex<double> result = 0.5*Sqr(g2)*(vd*ZH(gI2,0) + vu*ZH(gI2,1)
      );

   return result;
}

double CLASSNAME::CpbarFcFsconjVWmPL() const
{
   const double result = -0.7071067811865475*g2;

   return result;
}

double CLASSNAME::CpbarFcFsconjVWmPR() const
{
   const double result = 0;

   return result;
}

double CLASSNAME::CpbarFtFbconjVWmPL() const
{
   const double result = -0.7071067811865475*g2;

   return result;
}

double CLASSNAME::CpbarFtFbconjVWmPR() const
{
   const double result = 0;

   return result;
}

double CLASSNAME::CpbarFuFdconjVWmPL() const
{
   const double result = -0.7071067811865475*g2;

   return result;
}

double CLASSNAME::CpbarFuFdconjVWmPR() const
{
   const double result = 0;

   return result;
}

double CLASSNAME::CpconjVWmconjVWmVWmVWm1() const
{
   const double result = 2*Sqr(g2);

   return result;
}

double CLASSNAME::CpconjVWmconjVWmVWmVWm2() const
{
   const double result = -Sqr(g2);

   return result;
}

double CLASSNAME::CpconjVWmconjVWmVWmVWm3() const
{
   const double result = -Sqr(g2);

   return result;
}

std::complex<double> CLASSNAME::CpbarChaUChiHpmPL(int gI1, int gO2, int gI2) const
{
   const std::complex<double> result = -0.1*(Conj(UP(gI1,1))*(5.477225575051661
      *g1*KroneckerDelta(0,gO2) + 7.0710678118654755*g2*KroneckerDelta(1,gO2)) +
      10*g2*Conj(UP(gI1,0))*KroneckerDelta(3,gO2))*ZP(gI2,1);

   return result;
}

std::complex<double> CLASSNAME::CpbarChaUChiHpmPR(int gI1, int gO1, int gI2) const
{
   const std::complex<double> result = 0.1*(-10*g2*KroneckerDelta(2,gO1)*UM(gI1
      ,0) + 1.4142135623730951*(3.872983346207417*g1*KroneckerDelta(0,gO1) + 5*g2*
      KroneckerDelta(1,gO1))*UM(gI1,1))*ZP(gI2,0);

   return result;
}

std::complex<double> CLASSNAME::CpUChiChaconjHpmPL(int gO2, int gI2, int gI1) const
{
   const std::complex<double> result = 0.1*(Conj(UM(gI2,1))*(5.477225575051661*
      g1*KroneckerDelta(0,gO2) + 7.0710678118654755*g2*KroneckerDelta(1,gO2)) - 10
      *g2*Conj(UM(gI2,0))*KroneckerDelta(2,gO2))*ZP(gI1,0);

   return result;
}

std::complex<double> CLASSNAME::CpUChiChaconjHpmPR(int gO1, int gI2, int gI1) const
{
   const std::complex<double> result = -0.1*(10*g2*KroneckerDelta(3,gO1)*UP(gI2
      ,0) + 1.4142135623730951*(3.872983346207417*g1*KroneckerDelta(0,gO1) + 5*g2*
      KroneckerDelta(1,gO1))*UP(gI2,1))*ZP(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpChiUChihhPL(int gI2, int gO2, int gI1) const
{
   const std::complex<double> result = 0.1*(Conj(ZN(gI2,2))*(3.872983346207417*
      g1*KroneckerDelta(0,gO2) - 5*g2*KroneckerDelta(1,gO2))*ZH(gI1,0) - 5*g2*Conj
      (ZN(gI2,1))*KroneckerDelta(2,gO2)*ZH(gI1,0) - 3.872983346207417*g1*Conj(ZN(
      gI2,3))*KroneckerDelta(0,gO2)*ZH(gI1,1) + 5*g2*Conj(ZN(gI2,3))*
      KroneckerDelta(1,gO2)*ZH(gI1,1) + 5*g2*Conj(ZN(gI2,1))*KroneckerDelta(3,gO2)
      *ZH(gI1,1) + 3.872983346207417*g1*Conj(ZN(gI2,0))*(KroneckerDelta(2,gO2)*ZH(
      gI1,0) - KroneckerDelta(3,gO2)*ZH(gI1,1)));

   return result;
}

std::complex<double> CLASSNAME::CpChiUChihhPR(int gI2, int gO1, int gI1) const
{
   const std::complex<double> result = 0.1*(KroneckerDelta(2,gO1)*ZH(gI1,0)*(
      3.872983346207417*g1*ZN(gI2,0) - 5*g2*ZN(gI2,1)) + KroneckerDelta(3,gO1)*ZH(
      gI1,1)*(-3.872983346207417*g1*ZN(gI2,0) + 5*g2*ZN(gI2,1)) + (
      3.872983346207417*g1*KroneckerDelta(0,gO1) - 5*g2*KroneckerDelta(1,gO1))*(ZH
      (gI1,0)*ZN(gI2,2) - ZH(gI1,1)*ZN(gI2,3)));

   return result;
}

std::complex<double> CLASSNAME::CpbarChaUChiVWmPL(int gI1, int gO2) const
{
   const std::complex<double> result = -0.5*g2*(2*KroneckerDelta(1,gO2)*UM(gI1,
      0) + 1.4142135623730951*KroneckerDelta(2,gO2)*UM(gI1,1));

   return result;
}

std::complex<double> CLASSNAME::CpbarChaUChiVWmPR(int gI1, int gO1) const
{
   const std::complex<double> result = -(g2*Conj(UP(gI1,0))*KroneckerDelta(1,
      gO1)) + 0.7071067811865475*g2*Conj(UP(gI1,1))*KroneckerDelta(3,gO1);

   return result;
}

std::complex<double> CLASSNAME::CpUChiFbconjSbPL(int gO2, int gI1) const
{
   const std::complex<double> result = -0.18257418583505536*g1*KroneckerDelta(0
      ,gO2)*ZB(gI1,0) + 0.7071067811865475*g2*KroneckerDelta(1,gO2)*ZB(gI1,0) -
      KroneckerDelta(2,gO2)*Yd(2,2)*ZB(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpUChiFbconjSbPR(int gO1, int gI1) const
{
   const std::complex<double> result = -(Conj(Yd(2,2))*KroneckerDelta(2,gO1)*ZB
      (gI1,0)) - 0.3651483716701107*g1*KroneckerDelta(0,gO1)*ZB(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpUChiFcconjScPL(int gO2, int gI1) const
{
   const std::complex<double> result = -0.18257418583505536*g1*KroneckerDelta(0
      ,gO2)*ZC(gI1,0) - 0.7071067811865475*g2*KroneckerDelta(1,gO2)*ZC(gI1,0) -
      KroneckerDelta(3,gO2)*Yu(1,1)*ZC(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpUChiFcconjScPR(int gO1, int gI1) const
{
   const std::complex<double> result = -(Conj(Yu(1,1))*KroneckerDelta(3,gO1)*ZC
      (gI1,0)) + 0.7302967433402214*g1*KroneckerDelta(0,gO1)*ZC(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpUChiFdconjSdPL(int gO2, int gI1) const
{
   const std::complex<double> result = -0.18257418583505536*g1*KroneckerDelta(0
      ,gO2)*ZD(gI1,0) + 0.7071067811865475*g2*KroneckerDelta(1,gO2)*ZD(gI1,0) -
      KroneckerDelta(2,gO2)*Yd(0,0)*ZD(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpUChiFdconjSdPR(int gO1, int gI1) const
{
   const std::complex<double> result = -(Conj(Yd(0,0))*KroneckerDelta(2,gO1)*ZD
      (gI1,0)) - 0.3651483716701107*g1*KroneckerDelta(0,gO1)*ZD(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpUChiFeconjSePL(int gO2, int gI1) const
{
   const std::complex<double> result = 0.5477225575051661*g1*KroneckerDelta(0,
      gO2)*ZE(gI1,0) + 0.7071067811865475*g2*KroneckerDelta(1,gO2)*ZE(gI1,0) -
      KroneckerDelta(2,gO2)*Ye(0,0)*ZE(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpUChiFeconjSePR(int gO1, int gI1) const
{
   const std::complex<double> result = -(Conj(Ye(0,0))*KroneckerDelta(2,gO1)*ZE
      (gI1,0)) - 1.0954451150103321*g1*KroneckerDelta(0,gO1)*ZE(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpUChiFmconjSmPL(int gO2, int gI1) const
{
   const std::complex<double> result = 0.5477225575051661*g1*KroneckerDelta(0,
      gO2)*ZM(gI1,0) + 0.7071067811865475*g2*KroneckerDelta(1,gO2)*ZM(gI1,0) -
      KroneckerDelta(2,gO2)*Ye(1,1)*ZM(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpUChiFmconjSmPR(int gO1, int gI1) const
{
   const std::complex<double> result = -(Conj(Ye(1,1))*KroneckerDelta(2,gO1)*ZM
      (gI1,0)) - 1.0954451150103321*g1*KroneckerDelta(0,gO1)*ZM(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpUChiFsconjSsPL(int gO2, int gI1) const
{
   const std::complex<double> result = -0.18257418583505536*g1*KroneckerDelta(0
      ,gO2)*ZS(gI1,0) + 0.7071067811865475*g2*KroneckerDelta(1,gO2)*ZS(gI1,0) -
      KroneckerDelta(2,gO2)*Yd(1,1)*ZS(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpUChiFsconjSsPR(int gO1, int gI1) const
{
   const std::complex<double> result = -(Conj(Yd(1,1))*KroneckerDelta(2,gO1)*ZS
      (gI1,0)) - 0.3651483716701107*g1*KroneckerDelta(0,gO1)*ZS(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpUChiFtconjStPL(int gO2, int gI1) const
{
   const std::complex<double> result = -0.18257418583505536*g1*KroneckerDelta(0
      ,gO2)*ZT(gI1,0) - 0.7071067811865475*g2*KroneckerDelta(1,gO2)*ZT(gI1,0) -
      KroneckerDelta(3,gO2)*Yu(2,2)*ZT(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpUChiFtconjStPR(int gO1, int gI1) const
{
   const std::complex<double> result = -(Conj(Yu(2,2))*KroneckerDelta(3,gO1)*ZT
      (gI1,0)) + 0.7302967433402214*g1*KroneckerDelta(0,gO1)*ZT(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpUChiFtauconjStauPL(int gO2, int gI1) const
{
   const std::complex<double> result = 0.5477225575051661*g1*KroneckerDelta(0,
      gO2)*ZTau(gI1,0) + 0.7071067811865475*g2*KroneckerDelta(1,gO2)*ZTau(gI1,0) -
      KroneckerDelta(2,gO2)*Ye(2,2)*ZTau(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpUChiFtauconjStauPR(int gO1, int gI1) const
{
   const std::complex<double> result = -(Conj(Ye(2,2))*KroneckerDelta(2,gO1)*
      ZTau(gI1,0)) - 1.0954451150103321*g1*KroneckerDelta(0,gO1)*ZTau(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpUChiFuconjSuPL(int gO2, int gI1) const
{
   const std::complex<double> result = -0.18257418583505536*g1*KroneckerDelta(0
      ,gO2)*ZU(gI1,0) - 0.7071067811865475*g2*KroneckerDelta(1,gO2)*ZU(gI1,0) -
      KroneckerDelta(3,gO2)*Yu(0,0)*ZU(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpUChiFuconjSuPR(int gO1, int gI1) const
{
   const std::complex<double> result = -(Conj(Yu(0,0))*KroneckerDelta(3,gO1)*ZU
      (gI1,0)) + 0.7302967433402214*g1*KroneckerDelta(0,gO1)*ZU(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpChiUChiAhPL(int gI1, int gO2, int gI2) const
{
   const std::complex<double> result = std::complex<double>(0,-0.1)*(Conj(ZN(
      gI1,2))*(3.872983346207417*g1*KroneckerDelta(0,gO2) - 5*g2*KroneckerDelta(1,
      gO2))*ZA(gI2,0) - 5*g2*Conj(ZN(gI1,1))*KroneckerDelta(2,gO2)*ZA(gI2,0) -
      3.872983346207417*g1*Conj(ZN(gI1,3))*KroneckerDelta(0,gO2)*ZA(gI2,1) + 5*g2*
      Conj(ZN(gI1,3))*KroneckerDelta(1,gO2)*ZA(gI2,1) + 5*g2*Conj(ZN(gI1,1))*
      KroneckerDelta(3,gO2)*ZA(gI2,1) + 3.872983346207417*g1*Conj(ZN(gI1,0))*(
      KroneckerDelta(2,gO2)*ZA(gI2,0) - KroneckerDelta(3,gO2)*ZA(gI2,1)));

   return result;
}

std::complex<double> CLASSNAME::CpChiUChiAhPR(int gI1, int gO1, int gI2) const
{
   const std::complex<double> result = std::complex<double>(0,0.1)*(
      KroneckerDelta(2,gO1)*ZA(gI2,0)*(3.872983346207417*g1*ZN(gI1,0) - 5*g2*ZN(
      gI1,1)) + KroneckerDelta(3,gO1)*ZA(gI2,1)*(-3.872983346207417*g1*ZN(gI1,0) +
      5*g2*ZN(gI1,1)) + (3.872983346207417*g1*KroneckerDelta(0,gO1) - 5*g2*
      KroneckerDelta(1,gO1))*(ZA(gI2,0)*ZN(gI1,2) - ZA(gI2,1)*ZN(gI1,3)));

   return result;
}

std::complex<double> CLASSNAME::CpbarFbUChiSbPL(int gO2, int gI2) const
{
   const std::complex<double> result = -0.3651483716701107*g1*Conj(ZB(gI2,1))*
      KroneckerDelta(0,gO2) - Conj(ZB(gI2,0))*KroneckerDelta(2,gO2)*Yd(2,2);

   return result;
}

std::complex<double> CLASSNAME::CpbarFbUChiSbPR(int gO1, int gI2) const
{
   const std::complex<double> result = Conj(ZB(gI2,0))*(-0.18257418583505536*g1
      *KroneckerDelta(0,gO1) + 0.7071067811865475*g2*KroneckerDelta(1,gO1)) - Conj
      (Yd(2,2))*Conj(ZB(gI2,1))*KroneckerDelta(2,gO1);

   return result;
}

std::complex<double> CLASSNAME::CpbarFcUChiScPL(int gO2, int gI2) const
{
   const std::complex<double> result = 0.7302967433402214*g1*Conj(ZC(gI2,1))*
      KroneckerDelta(0,gO2) - Conj(ZC(gI2,0))*KroneckerDelta(3,gO2)*Yu(1,1);

   return result;
}

std::complex<double> CLASSNAME::CpbarFcUChiScPR(int gO1, int gI2) const
{
   const std::complex<double> result = Conj(ZC(gI2,0))*(-0.18257418583505536*g1
      *KroneckerDelta(0,gO1) - 0.7071067811865475*g2*KroneckerDelta(1,gO1)) - Conj
      (Yu(1,1))*Conj(ZC(gI2,1))*KroneckerDelta(3,gO1);

   return result;
}

std::complex<double> CLASSNAME::CpbarFdUChiSdPL(int gO2, int gI2) const
{
   const std::complex<double> result = -0.3651483716701107*g1*Conj(ZD(gI2,1))*
      KroneckerDelta(0,gO2) - Conj(ZD(gI2,0))*KroneckerDelta(2,gO2)*Yd(0,0);

   return result;
}

std::complex<double> CLASSNAME::CpbarFdUChiSdPR(int gO1, int gI2) const
{
   const std::complex<double> result = Conj(ZD(gI2,0))*(-0.18257418583505536*g1
      *KroneckerDelta(0,gO1) + 0.7071067811865475*g2*KroneckerDelta(1,gO1)) - Conj
      (Yd(0,0))*Conj(ZD(gI2,1))*KroneckerDelta(2,gO1);

   return result;
}

std::complex<double> CLASSNAME::CpbarFeUChiSePL(int gO2, int gI2) const
{
   const std::complex<double> result = -1.0954451150103321*g1*Conj(ZE(gI2,1))*
      KroneckerDelta(0,gO2) - Conj(ZE(gI2,0))*KroneckerDelta(2,gO2)*Ye(0,0);

   return result;
}

std::complex<double> CLASSNAME::CpbarFeUChiSePR(int gO1, int gI2) const
{
   const std::complex<double> result = Conj(ZE(gI2,0))*(0.5477225575051661*g1*
      KroneckerDelta(0,gO1) + 0.7071067811865475*g2*KroneckerDelta(1,gO1)) - Conj(
      Ye(0,0))*Conj(ZE(gI2,1))*KroneckerDelta(2,gO1);

   return result;
}

std::complex<double> CLASSNAME::CpbarFmUChiSmPL(int gO2, int gI2) const
{
   const std::complex<double> result = -1.0954451150103321*g1*Conj(ZM(gI2,1))*
      KroneckerDelta(0,gO2) - Conj(ZM(gI2,0))*KroneckerDelta(2,gO2)*Ye(1,1);

   return result;
}

std::complex<double> CLASSNAME::CpbarFmUChiSmPR(int gO1, int gI2) const
{
   const std::complex<double> result = Conj(ZM(gI2,0))*(0.5477225575051661*g1*
      KroneckerDelta(0,gO1) + 0.7071067811865475*g2*KroneckerDelta(1,gO1)) - Conj(
      Ye(1,1))*Conj(ZM(gI2,1))*KroneckerDelta(2,gO1);

   return result;
}

std::complex<double> CLASSNAME::CpbarFsUChiSsPL(int gO2, int gI2) const
{
   const std::complex<double> result = -0.3651483716701107*g1*Conj(ZS(gI2,1))*
      KroneckerDelta(0,gO2) - Conj(ZS(gI2,0))*KroneckerDelta(2,gO2)*Yd(1,1);

   return result;
}

std::complex<double> CLASSNAME::CpbarFsUChiSsPR(int gO1, int gI2) const
{
   const std::complex<double> result = Conj(ZS(gI2,0))*(-0.18257418583505536*g1
      *KroneckerDelta(0,gO1) + 0.7071067811865475*g2*KroneckerDelta(1,gO1)) - Conj
      (Yd(1,1))*Conj(ZS(gI2,1))*KroneckerDelta(2,gO1);

   return result;
}

std::complex<double> CLASSNAME::CpbarFtUChiStPL(int gO2, int gI2) const
{
   const std::complex<double> result = 0.7302967433402214*g1*Conj(ZT(gI2,1))*
      KroneckerDelta(0,gO2) - Conj(ZT(gI2,0))*KroneckerDelta(3,gO2)*Yu(2,2);

   return result;
}

std::complex<double> CLASSNAME::CpbarFtUChiStPR(int gO1, int gI2) const
{
   const std::complex<double> result = Conj(ZT(gI2,0))*(-0.18257418583505536*g1
      *KroneckerDelta(0,gO1) - 0.7071067811865475*g2*KroneckerDelta(1,gO1)) - Conj
      (Yu(2,2))*Conj(ZT(gI2,1))*KroneckerDelta(3,gO1);

   return result;
}

std::complex<double> CLASSNAME::CpbarFtauUChiStauPL(int gO2, int gI2) const
{
   const std::complex<double> result = -1.0954451150103321*g1*Conj(ZTau(gI2,1))
      *KroneckerDelta(0,gO2) - Conj(ZTau(gI2,0))*KroneckerDelta(2,gO2)*Ye(2,2);

   return result;
}

std::complex<double> CLASSNAME::CpbarFtauUChiStauPR(int gO1, int gI2) const
{
   const std::complex<double> result = Conj(ZTau(gI2,0))*(0.5477225575051661*g1
      *KroneckerDelta(0,gO1) + 0.7071067811865475*g2*KroneckerDelta(1,gO1)) - Conj
      (Ye(2,2))*Conj(ZTau(gI2,1))*KroneckerDelta(2,gO1);

   return result;
}

std::complex<double> CLASSNAME::CpbarFuUChiSuPL(int gO2, int gI2) const
{
   const std::complex<double> result = 0.7302967433402214*g1*Conj(ZU(gI2,1))*
      KroneckerDelta(0,gO2) - Conj(ZU(gI2,0))*KroneckerDelta(3,gO2)*Yu(0,0);

   return result;
}

std::complex<double> CLASSNAME::CpbarFuUChiSuPR(int gO1, int gI2) const
{
   const std::complex<double> result = Conj(ZU(gI2,0))*(-0.18257418583505536*g1
      *KroneckerDelta(0,gO1) - 0.7071067811865475*g2*KroneckerDelta(1,gO1)) - Conj
      (Yu(0,0))*Conj(ZU(gI2,1))*KroneckerDelta(3,gO1);

   return result;
}

std::complex<double> CLASSNAME::CpUChiChaconjVWmPR(int gO2, int gI2) const
{
   const std::complex<double> result = -(g2*KroneckerDelta(1,gO2)*UP(gI2,0)) +
      0.7071067811865475*g2*KroneckerDelta(3,gO2)*UP(gI2,1);

   return result;
}

std::complex<double> CLASSNAME::CpUChiChaconjVWmPL(int gO1, int gI2) const
{
   const std::complex<double> result = -0.5*g2*(2*Conj(UM(gI2,0))*
      KroneckerDelta(1,gO1) + 1.4142135623730951*Conj(UM(gI2,1))*KroneckerDelta(2,
      gO1));

   return result;
}

std::complex<double> CLASSNAME::CpChiUChiVZPL(int gI2, int gO2) const
{
   const std::complex<double> result = -0.1*(5*g2*Cos(ThetaW()) +
      3.872983346207417*g1*Sin(ThetaW()))*(KroneckerDelta(2,gO2)*ZN(gI2,2) -
      KroneckerDelta(3,gO2)*ZN(gI2,3));

   return result;
}

std::complex<double> CLASSNAME::CpChiUChiVZPR(int gI2, int gO1) const
{
   const std::complex<double> result = 0.1*(Conj(ZN(gI2,2))*KroneckerDelta(2,
      gO1) - Conj(ZN(gI2,3))*KroneckerDelta(3,gO1))*(5*g2*Cos(ThetaW()) +
      3.872983346207417*g1*Sin(ThetaW()));

   return result;
}

double CLASSNAME::CpbarFveUChiSveLPL(int ) const
{
   const double result = 0;

   return result;
}

std::complex<double> CLASSNAME::CpbarFveUChiSveLPR(int gO1) const
{
   const std::complex<double> result = 0.5477225575051661*g1*KroneckerDelta(0,
      gO1) - 0.7071067811865475*g2*KroneckerDelta(1,gO1);

   return result;
}

double CLASSNAME::CpbarFvmUChiSvmLPL(int ) const
{
   const double result = 0;

   return result;
}

std::complex<double> CLASSNAME::CpbarFvmUChiSvmLPR(int gO1) const
{
   const std::complex<double> result = 0.5477225575051661*g1*KroneckerDelta(0,
      gO1) - 0.7071067811865475*g2*KroneckerDelta(1,gO1);

   return result;
}

double CLASSNAME::CpbarFvtUChiSvtLPL(int ) const
{
   const double result = 0;

   return result;
}

std::complex<double> CLASSNAME::CpbarFvtUChiSvtLPR(int gO1) const
{
   const std::complex<double> result = 0.5477225575051661*g1*KroneckerDelta(0,
      gO1) - 0.7071067811865475*g2*KroneckerDelta(1,gO1);

   return result;
}

std::complex<double> CLASSNAME::CpUChiFveconjSveLPL(int gO2) const
{
   const std::complex<double> result = 0.5477225575051661*g1*KroneckerDelta(0,
      gO2) - 0.7071067811865475*g2*KroneckerDelta(1,gO2);

   return result;
}

double CLASSNAME::CpUChiFveconjSveLPR(int ) const
{
   const double result = 0;

   return result;
}

std::complex<double> CLASSNAME::CpUChiFvmconjSvmLPL(int gO2) const
{
   const std::complex<double> result = 0.5477225575051661*g1*KroneckerDelta(0,
      gO2) - 0.7071067811865475*g2*KroneckerDelta(1,gO2);

   return result;
}

double CLASSNAME::CpUChiFvmconjSvmLPR(int ) const
{
   const double result = 0;

   return result;
}

std::complex<double> CLASSNAME::CpUChiFvtconjSvtLPL(int gO2) const
{
   const std::complex<double> result = 0.5477225575051661*g1*KroneckerDelta(0,
      gO2) - 0.7071067811865475*g2*KroneckerDelta(1,gO2);

   return result;
}

double CLASSNAME::CpUChiFvtconjSvtLPR(int ) const
{
   const double result = 0;

   return result;
}

std::complex<double> CLASSNAME::CpbarUChaChaAhPL(int gO2, int gI1, int gI2) const
{
   const std::complex<double> result = std::complex<double>(0.,
      0.7071067811865475)*g2*(Conj(UM(gI1,1))*KroneckerDelta(0,gO2)*ZA(gI2,0) +
      Conj(UM(gI1,0))*KroneckerDelta(1,gO2)*ZA(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpbarUChaChaAhPR(int gO1, int gI1, int gI2) const
{
   const std::complex<double> result = std::complex<double>(0.,
      -0.7071067811865475)*g2*(KroneckerDelta(1,gO1)*UP(gI1,0)*ZA(gI2,0) +
      KroneckerDelta(0,gO1)*UP(gI1,1)*ZA(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpbarUChaChahhPL(int gO2, int gI2, int gI1) const
{
   const std::complex<double> result = -0.7071067811865475*g2*(Conj(UM(gI2,1))*
      KroneckerDelta(0,gO2)*ZH(gI1,0) + Conj(UM(gI2,0))*KroneckerDelta(1,gO2)*ZH(
      gI1,1));

   return result;
}

std::complex<double> CLASSNAME::CpbarUChaChahhPR(int gO1, int gI2, int gI1) const
{
   const std::complex<double> result = -0.7071067811865475*g2*(KroneckerDelta(1
      ,gO1)*UP(gI2,0)*ZH(gI1,0) + KroneckerDelta(0,gO1)*UP(gI2,1)*ZH(gI1,1));

   return result;
}

std::complex<double> CLASSNAME::CpbarUChaChiHpmPL(int gO2, int gI2, int gI1) const
{
   const std::complex<double> result = -0.1*(10*g2*Conj(ZN(gI2,3))*
      KroneckerDelta(0,gO2) + 1.4142135623730951*(3.872983346207417*g1*Conj(ZN(gI2
      ,0)) + 5*g2*Conj(ZN(gI2,1)))*KroneckerDelta(1,gO2))*ZP(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpbarUChaChiHpmPR(int gO1, int gI2, int gI1) const
{
   const std::complex<double> result = 0.1*(KroneckerDelta(1,gO1)*(
      5.477225575051661*g1*ZN(gI2,0) + 7.0710678118654755*g2*ZN(gI2,1)) - 10*g2*
      KroneckerDelta(0,gO1)*ZN(gI2,2))*ZP(gI1,0);

   return result;
}

std::complex<double> CLASSNAME::CpbarUChaFbconjStPL(int gO2, int gI1) const
{
   const std::complex<double> result = -(g2*KroneckerDelta(0,gO2)*ZT(gI1,0)) +
      KroneckerDelta(1,gO2)*Yu(2,2)*ZT(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpbarUChaFbconjStPR(int gO1, int gI1) const
{
   const std::complex<double> result = Conj(Yd(2,2))*KroneckerDelta(1,gO1)*ZT(
      gI1,0);

   return result;
}

std::complex<double> CLASSNAME::CpbarUChaFdconjSuPL(int gO2, int gI1) const
{
   const std::complex<double> result = -(g2*KroneckerDelta(0,gO2)*ZU(gI1,0)) +
      KroneckerDelta(1,gO2)*Yu(0,0)*ZU(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpbarUChaFdconjSuPR(int gO1, int gI1) const
{
   const std::complex<double> result = Conj(Yd(0,0))*KroneckerDelta(1,gO1)*ZU(
      gI1,0);

   return result;
}

std::complex<double> CLASSNAME::CpbarUChaFsconjScPL(int gO2, int gI1) const
{
   const std::complex<double> result = -(g2*KroneckerDelta(0,gO2)*ZC(gI1,0)) +
      KroneckerDelta(1,gO2)*Yu(1,1)*ZC(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpbarUChaFsconjScPR(int gO1, int gI1) const
{
   const std::complex<double> result = Conj(Yd(1,1))*KroneckerDelta(1,gO1)*ZC(
      gI1,0);

   return result;
}

std::complex<double> CLASSNAME::CpbarFcbarUChaSsPL(int gO2, int gI2) const
{
   const std::complex<double> result = Conj(ZS(gI2,0))*KroneckerDelta(1,gO2)*Yu
      (1,1);

   return result;
}

std::complex<double> CLASSNAME::CpbarFcbarUChaSsPR(int gO1, int gI2) const
{
   const std::complex<double> result = -(g2*Conj(ZS(gI2,0))*KroneckerDelta(0,
      gO1)) + Conj(Yd(1,1))*Conj(ZS(gI2,1))*KroneckerDelta(1,gO1);

   return result;
}

std::complex<double> CLASSNAME::CpbarFtbarUChaSbPL(int gO2, int gI2) const
{
   const std::complex<double> result = Conj(ZB(gI2,0))*KroneckerDelta(1,gO2)*Yu
      (2,2);

   return result;
}

std::complex<double> CLASSNAME::CpbarFtbarUChaSbPR(int gO1, int gI2) const
{
   const std::complex<double> result = -(g2*Conj(ZB(gI2,0))*KroneckerDelta(0,
      gO1)) + Conj(Yd(2,2))*Conj(ZB(gI2,1))*KroneckerDelta(1,gO1);

   return result;
}

std::complex<double> CLASSNAME::CpbarFubarUChaSdPL(int gO2, int gI2) const
{
   const std::complex<double> result = Conj(ZD(gI2,0))*KroneckerDelta(1,gO2)*Yu
      (0,0);

   return result;
}

std::complex<double> CLASSNAME::CpbarFubarUChaSdPR(int gO1, int gI2) const
{
   const std::complex<double> result = -(g2*Conj(ZD(gI2,0))*KroneckerDelta(0,
      gO1)) + Conj(Yd(0,0))*Conj(ZD(gI2,1))*KroneckerDelta(1,gO1);

   return result;
}

double CLASSNAME::CpbarFvebarUChaSePL(int , int ) const
{
   const double result = 0;

   return result;
}

std::complex<double> CLASSNAME::CpbarFvebarUChaSePR(int gO1, int gI2) const
{
   const std::complex<double> result = -(g2*Conj(ZE(gI2,0))*KroneckerDelta(0,
      gO1)) + Conj(Ye(0,0))*Conj(ZE(gI2,1))*KroneckerDelta(1,gO1);

   return result;
}

double CLASSNAME::CpbarFvmbarUChaSmPL(int , int ) const
{
   const double result = 0;

   return result;
}

std::complex<double> CLASSNAME::CpbarFvmbarUChaSmPR(int gO1, int gI2) const
{
   const std::complex<double> result = -(g2*Conj(ZM(gI2,0))*KroneckerDelta(0,
      gO1)) + Conj(Ye(1,1))*Conj(ZM(gI2,1))*KroneckerDelta(1,gO1);

   return result;
}

double CLASSNAME::CpbarFvtbarUChaStauPL(int , int ) const
{
   const double result = 0;

   return result;
}

std::complex<double> CLASSNAME::CpbarFvtbarUChaStauPR(int gO1, int gI2) const
{
   const std::complex<double> result = -(g2*Conj(ZTau(gI2,0))*KroneckerDelta(0,
      gO1)) + Conj(Ye(2,2))*Conj(ZTau(gI2,1))*KroneckerDelta(1,gO1);

   return result;
}

std::complex<double> CLASSNAME::CpbarUChaChaVPPR(int gO2, int gI2) const
{
   const std::complex<double> result = g2*KroneckerDelta(0,gO2)*Sin(ThetaW())*
      UP(gI2,0) + 0.1*KroneckerDelta(1,gO2)*(3.872983346207417*g1*Cos(ThetaW()) +
      5*g2*Sin(ThetaW()))*UP(gI2,1);

   return result;
}

std::complex<double> CLASSNAME::CpbarUChaChaVPPL(int gO1, int gI2) const
{
   const std::complex<double> result = g2*Conj(UM(gI2,0))*KroneckerDelta(0,gO1)
      *Sin(ThetaW()) + 0.1*Conj(UM(gI2,1))*KroneckerDelta(1,gO1)*(
      3.872983346207417*g1*Cos(ThetaW()) + 5*g2*Sin(ThetaW()));

   return result;
}

std::complex<double> CLASSNAME::CpbarUChaChaVZPR(int gO2, int gI2) const
{
   const std::complex<double> result = g2*Cos(ThetaW())*KroneckerDelta(0,gO2)*
      UP(gI2,0) + 0.1*KroneckerDelta(1,gO2)*(5*g2*Cos(ThetaW()) -
      3.872983346207417*g1*Sin(ThetaW()))*UP(gI2,1);

   return result;
}

std::complex<double> CLASSNAME::CpbarUChaChaVZPL(int gO1, int gI2) const
{
   const std::complex<double> result = g2*Conj(UM(gI2,0))*Cos(ThetaW())*
      KroneckerDelta(0,gO1) + 0.1*Conj(UM(gI2,1))*KroneckerDelta(1,gO1)*(5*g2*Cos(
      ThetaW()) - 3.872983346207417*g1*Sin(ThetaW()));

   return result;
}

std::complex<double> CLASSNAME::CpbarUChaChiVWmPR(int gO2, int gI2) const
{
   const std::complex<double> result = -(g2*KroneckerDelta(0,gO2)*ZN(gI2,1)) +
      0.7071067811865475*g2*KroneckerDelta(1,gO2)*ZN(gI2,3);

   return result;
}

std::complex<double> CLASSNAME::CpbarUChaChiVWmPL(int gO1, int gI2) const
{
   const std::complex<double> result = -0.5*g2*(2*Conj(ZN(gI2,1))*
      KroneckerDelta(0,gO1) + 1.4142135623730951*Conj(ZN(gI2,2))*KroneckerDelta(1,
      gO1));

   return result;
}

double CLASSNAME::CpbarUChaFeconjSveLPL(int gO2) const
{
   const double result = -(g2*KroneckerDelta(0,gO2));

   return result;
}

double CLASSNAME::CpbarUChaFeconjSveLPR(int gO1) const
{
   const double result = Conj(Ye(0,0))*KroneckerDelta(1,gO1);

   return result;
}

double CLASSNAME::CpbarUChaFmconjSvmLPL(int gO2) const
{
   const double result = -(g2*KroneckerDelta(0,gO2));

   return result;
}

double CLASSNAME::CpbarUChaFmconjSvmLPR(int gO1) const
{
   const double result = Conj(Ye(1,1))*KroneckerDelta(1,gO1);

   return result;
}

double CLASSNAME::CpbarUChaFtauconjSvtLPL(int gO2) const
{
   const double result = -(g2*KroneckerDelta(0,gO2));

   return result;
}

double CLASSNAME::CpbarUChaFtauconjSvtLPR(int gO1) const
{
   const double result = Conj(Ye(2,2))*KroneckerDelta(1,gO1);

   return result;
}

std::complex<double> CLASSNAME::CpGluFbconjSbPL(int gI1) const
{
   const std::complex<double> result = -1.4142135623730951*g3*PhaseGlu*ZB(gI1,0
      );

   return result;
}

std::complex<double> CLASSNAME::CpGluFbconjSbPR(int gI1) const
{
   const std::complex<double> result = 1.4142135623730951*g3*Conj(PhaseGlu)*ZB(
      gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpGluFcconjScPL(int gI1) const
{
   const std::complex<double> result = -1.4142135623730951*g3*PhaseGlu*ZC(gI1,0
      );

   return result;
}

std::complex<double> CLASSNAME::CpGluFcconjScPR(int gI1) const
{
   const std::complex<double> result = 1.4142135623730951*g3*Conj(PhaseGlu)*ZC(
      gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpGluFdconjSdPL(int gI1) const
{
   const std::complex<double> result = -1.4142135623730951*g3*PhaseGlu*ZD(gI1,0
      );

   return result;
}

std::complex<double> CLASSNAME::CpGluFdconjSdPR(int gI1) const
{
   const std::complex<double> result = 1.4142135623730951*g3*Conj(PhaseGlu)*ZD(
      gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpGluFsconjSsPL(int gI1) const
{
   const std::complex<double> result = -1.4142135623730951*g3*PhaseGlu*ZS(gI1,0
      );

   return result;
}

std::complex<double> CLASSNAME::CpGluFsconjSsPR(int gI1) const
{
   const std::complex<double> result = 1.4142135623730951*g3*Conj(PhaseGlu)*ZS(
      gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpGluFtconjStPL(int gI1) const
{
   const std::complex<double> result = -1.4142135623730951*g3*PhaseGlu*ZT(gI1,0
      );

   return result;
}

std::complex<double> CLASSNAME::CpGluFtconjStPR(int gI1) const
{
   const std::complex<double> result = 1.4142135623730951*g3*Conj(PhaseGlu)*ZT(
      gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpGluFuconjSuPL(int gI1) const
{
   const std::complex<double> result = -1.4142135623730951*g3*PhaseGlu*ZU(gI1,0
      );

   return result;
}

std::complex<double> CLASSNAME::CpGluFuconjSuPR(int gI1) const
{
   const std::complex<double> result = 1.4142135623730951*g3*Conj(PhaseGlu)*ZU(
      gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpbarFbGluSbPL(int gI2) const
{
   const std::complex<double> result = 1.4142135623730951*g3*PhaseGlu*Conj(ZB(
      gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpbarFbGluSbPR(int gI2) const
{
   const std::complex<double> result = -1.4142135623730951*g3*Conj(PhaseGlu)*
      Conj(ZB(gI2,0));

   return result;
}

std::complex<double> CLASSNAME::CpbarFcGluScPL(int gI2) const
{
   const std::complex<double> result = 1.4142135623730951*g3*PhaseGlu*Conj(ZC(
      gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpbarFcGluScPR(int gI2) const
{
   const std::complex<double> result = -1.4142135623730951*g3*Conj(PhaseGlu)*
      Conj(ZC(gI2,0));

   return result;
}

std::complex<double> CLASSNAME::CpbarFdGluSdPL(int gI2) const
{
   const std::complex<double> result = 1.4142135623730951*g3*PhaseGlu*Conj(ZD(
      gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpbarFdGluSdPR(int gI2) const
{
   const std::complex<double> result = -1.4142135623730951*g3*Conj(PhaseGlu)*
      Conj(ZD(gI2,0));

   return result;
}

std::complex<double> CLASSNAME::CpbarFsGluSsPL(int gI2) const
{
   const std::complex<double> result = 1.4142135623730951*g3*PhaseGlu*Conj(ZS(
      gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpbarFsGluSsPR(int gI2) const
{
   const std::complex<double> result = -1.4142135623730951*g3*Conj(PhaseGlu)*
      Conj(ZS(gI2,0));

   return result;
}

std::complex<double> CLASSNAME::CpbarFtGluStPL(int gI2) const
{
   const std::complex<double> result = 1.4142135623730951*g3*PhaseGlu*Conj(ZT(
      gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpbarFtGluStPR(int gI2) const
{
   const std::complex<double> result = -1.4142135623730951*g3*Conj(PhaseGlu)*
      Conj(ZT(gI2,0));

   return result;
}

std::complex<double> CLASSNAME::CpbarFuGluSuPL(int gI2) const
{
   const std::complex<double> result = 1.4142135623730951*g3*PhaseGlu*Conj(ZU(
      gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpbarFuGluSuPR(int gI2) const
{
   const std::complex<double> result = -1.4142135623730951*g3*Conj(PhaseGlu)*
      Conj(ZU(gI2,0));

   return result;
}

std::complex<double> CLASSNAME::CpbarFdChaSuPL(int gI2, int gI1) const
{
   const std::complex<double> result = Conj(UM(gI2,1))*Conj(ZU(gI1,0))*Yd(0,0);

   return result;
}

std::complex<double> CLASSNAME::CpbarFdChaSuPR(int gI2, int gI1) const
{
   const std::complex<double> result = -(g2*Conj(ZU(gI1,0))*UP(gI2,0)) + Conj(
      Yu(0,0))*Conj(ZU(gI1,1))*UP(gI2,1);

   return result;
}

std::complex<double> CLASSNAME::CpbarFdChiSdPL(int gI2, int gI1) const
{
   const std::complex<double> result = -0.3651483716701107*g1*Conj(ZD(gI1,1))*
      Conj(ZN(gI2,0)) - Conj(ZD(gI1,0))*Conj(ZN(gI2,2))*Yd(0,0);

   return result;
}

std::complex<double> CLASSNAME::CpbarFdChiSdPR(int gI2, int gI1) const
{
   const std::complex<double> result = Conj(ZD(gI1,0))*(-0.18257418583505536*g1
      *ZN(gI2,0) + 0.7071067811865475*g2*ZN(gI2,1)) - Conj(Yd(0,0))*Conj(ZD(gI1,1)
      )*ZN(gI2,2);

   return result;
}

std::complex<double> CLASSNAME::CpbarFdFdhhPL(int gI1) const
{
   const std::complex<double> result = -0.7071067811865475*Yd(0,0)*ZH(gI1,0);

   return result;
}

std::complex<double> CLASSNAME::CpbarFdFdhhPR(int gI1) const
{
   const std::complex<double> result = -0.7071067811865475*Conj(Yd(0,0))*ZH(gI1
      ,0);

   return result;
}

std::complex<double> CLASSNAME::CpbarFdFuHpmPL(int gI1) const
{
   const std::complex<double> result = Yd(0,0)*ZP(gI1,0);

   return result;
}

std::complex<double> CLASSNAME::CpbarFdFuHpmPR(int gI1) const
{
   const std::complex<double> result = Conj(Yu(0,0))*ZP(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpbarFdFdAhPL(int gI2) const
{
   const std::complex<double> result = std::complex<double>(0.,
      -0.7071067811865475)*Yd(0,0)*ZA(gI2,0);

   return result;
}

std::complex<double> CLASSNAME::CpbarFdFdAhPR(int gI2) const
{
   const std::complex<double> result = std::complex<double>(0.,
      0.7071067811865475)*Conj(Yd(0,0))*ZA(gI2,0);

   return result;
}

double CLASSNAME::CpbarFdFuVWmPR() const
{
   const double result = 0;

   return result;
}

double CLASSNAME::CpbarFdFuVWmPL() const
{
   const double result = -0.7071067811865475*g2;

   return result;
}

std::complex<double> CLASSNAME::CpbarFsChaScPL(int gI2, int gI1) const
{
   const std::complex<double> result = Conj(UM(gI2,1))*Conj(ZC(gI1,0))*Yd(1,1);

   return result;
}

std::complex<double> CLASSNAME::CpbarFsChaScPR(int gI2, int gI1) const
{
   const std::complex<double> result = -(g2*Conj(ZC(gI1,0))*UP(gI2,0)) + Conj(
      Yu(1,1))*Conj(ZC(gI1,1))*UP(gI2,1);

   return result;
}

std::complex<double> CLASSNAME::CpbarFsChiSsPL(int gI2, int gI1) const
{
   const std::complex<double> result = -0.3651483716701107*g1*Conj(ZN(gI2,0))*
      Conj(ZS(gI1,1)) - Conj(ZN(gI2,2))*Conj(ZS(gI1,0))*Yd(1,1);

   return result;
}

std::complex<double> CLASSNAME::CpbarFsChiSsPR(int gI2, int gI1) const
{
   const std::complex<double> result = Conj(ZS(gI1,0))*(-0.18257418583505536*g1
      *ZN(gI2,0) + 0.7071067811865475*g2*ZN(gI2,1)) - Conj(Yd(1,1))*Conj(ZS(gI1,1)
      )*ZN(gI2,2);

   return result;
}

std::complex<double> CLASSNAME::CpbarFsFcHpmPL(int gI1) const
{
   const std::complex<double> result = Yd(1,1)*ZP(gI1,0);

   return result;
}

std::complex<double> CLASSNAME::CpbarFsFcHpmPR(int gI1) const
{
   const std::complex<double> result = Conj(Yu(1,1))*ZP(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpbarFsFshhPL(int gI1) const
{
   const std::complex<double> result = -0.7071067811865475*Yd(1,1)*ZH(gI1,0);

   return result;
}

std::complex<double> CLASSNAME::CpbarFsFshhPR(int gI1) const
{
   const std::complex<double> result = -0.7071067811865475*Conj(Yd(1,1))*ZH(gI1
      ,0);

   return result;
}

std::complex<double> CLASSNAME::CpbarFsFsAhPL(int gI2) const
{
   const std::complex<double> result = std::complex<double>(0.,
      -0.7071067811865475)*Yd(1,1)*ZA(gI2,0);

   return result;
}

std::complex<double> CLASSNAME::CpbarFsFsAhPR(int gI2) const
{
   const std::complex<double> result = std::complex<double>(0.,
      0.7071067811865475)*Conj(Yd(1,1))*ZA(gI2,0);

   return result;
}

double CLASSNAME::CpbarFsFcVWmPR() const
{
   const double result = 0;

   return result;
}

double CLASSNAME::CpbarFsFcVWmPL() const
{
   const double result = -0.7071067811865475*g2;

   return result;
}

std::complex<double> CLASSNAME::CpbarFbChaStPL(int gI2, int gI1) const
{
   const std::complex<double> result = Conj(UM(gI2,1))*Conj(ZT(gI1,0))*Yd(2,2);

   return result;
}

std::complex<double> CLASSNAME::CpbarFbChaStPR(int gI2, int gI1) const
{
   const std::complex<double> result = -(g2*Conj(ZT(gI1,0))*UP(gI2,0)) + Conj(
      Yu(2,2))*Conj(ZT(gI1,1))*UP(gI2,1);

   return result;
}

std::complex<double> CLASSNAME::CpbarFbChiSbPL(int gI2, int gI1) const
{
   const std::complex<double> result = -0.3651483716701107*g1*Conj(ZB(gI1,1))*
      Conj(ZN(gI2,0)) - Conj(ZB(gI1,0))*Conj(ZN(gI2,2))*Yd(2,2);

   return result;
}

std::complex<double> CLASSNAME::CpbarFbChiSbPR(int gI2, int gI1) const
{
   const std::complex<double> result = Conj(ZB(gI1,0))*(-0.18257418583505536*g1
      *ZN(gI2,0) + 0.7071067811865475*g2*ZN(gI2,1)) - Conj(Yd(2,2))*Conj(ZB(gI1,1)
      )*ZN(gI2,2);

   return result;
}

std::complex<double> CLASSNAME::CpbarFbFbhhPL(int gI1) const
{
   const std::complex<double> result = -0.7071067811865475*Yd(2,2)*ZH(gI1,0);

   return result;
}

std::complex<double> CLASSNAME::CpbarFbFbhhPR(int gI1) const
{
   const std::complex<double> result = -0.7071067811865475*Conj(Yd(2,2))*ZH(gI1
      ,0);

   return result;
}

std::complex<double> CLASSNAME::CpbarFbFtHpmPL(int gI1) const
{
   const std::complex<double> result = Yd(2,2)*ZP(gI1,0);

   return result;
}

std::complex<double> CLASSNAME::CpbarFbFtHpmPR(int gI1) const
{
   const std::complex<double> result = Conj(Yu(2,2))*ZP(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpbarFbFbAhPL(int gI2) const
{
   const std::complex<double> result = std::complex<double>(0.,
      -0.7071067811865475)*Yd(2,2)*ZA(gI2,0);

   return result;
}

std::complex<double> CLASSNAME::CpbarFbFbAhPR(int gI2) const
{
   const std::complex<double> result = std::complex<double>(0.,
      0.7071067811865475)*Conj(Yd(2,2))*ZA(gI2,0);

   return result;
}

double CLASSNAME::CpbarFbFtVWmPR() const
{
   const double result = 0;

   return result;
}

double CLASSNAME::CpbarFbFtVWmPL() const
{
   const double result = -0.7071067811865475*g2;

   return result;
}

std::complex<double> CLASSNAME::CpbarFubarChaSdPL(int gI1, int gI2) const
{
   const std::complex<double> result = Conj(UP(gI1,1))*Conj(ZD(gI2,0))*Yu(0,0);

   return result;
}

std::complex<double> CLASSNAME::CpbarFubarChaSdPR(int gI1, int gI2) const
{
   const std::complex<double> result = -(g2*Conj(ZD(gI2,0))*UM(gI1,0)) + Conj(
      Yd(0,0))*Conj(ZD(gI2,1))*UM(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpbarFuChiSuPL(int gI2, int gI1) const
{
   const std::complex<double> result = 0.7302967433402214*g1*Conj(ZN(gI2,0))*
      Conj(ZU(gI1,1)) - Conj(ZN(gI2,3))*Conj(ZU(gI1,0))*Yu(0,0);

   return result;
}

std::complex<double> CLASSNAME::CpbarFuChiSuPR(int gI2, int gI1) const
{
   const std::complex<double> result = Conj(ZU(gI1,0))*(-0.18257418583505536*g1
      *ZN(gI2,0) - 0.7071067811865475*g2*ZN(gI2,1)) - Conj(Yu(0,0))*Conj(ZU(gI1,1)
      )*ZN(gI2,3);

   return result;
}

std::complex<double> CLASSNAME::CpbarFuFdconjHpmPL(int gI1) const
{
   const std::complex<double> result = Yu(0,0)*ZP(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpbarFuFdconjHpmPR(int gI1) const
{
   const std::complex<double> result = Conj(Yd(0,0))*ZP(gI1,0);

   return result;
}

std::complex<double> CLASSNAME::CpbarFuFuhhPL(int gI1) const
{
   const std::complex<double> result = -0.7071067811865475*Yu(0,0)*ZH(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpbarFuFuhhPR(int gI1) const
{
   const std::complex<double> result = -0.7071067811865475*Conj(Yu(0,0))*ZH(gI1
      ,1);

   return result;
}

std::complex<double> CLASSNAME::CpbarFuFuAhPL(int gI2) const
{
   const std::complex<double> result = std::complex<double>(0.,
      -0.7071067811865475)*Yu(0,0)*ZA(gI2,1);

   return result;
}

std::complex<double> CLASSNAME::CpbarFuFuAhPR(int gI2) const
{
   const std::complex<double> result = std::complex<double>(0.,
      0.7071067811865475)*Conj(Yu(0,0))*ZA(gI2,1);

   return result;
}

std::complex<double> CLASSNAME::CpbarFcbarChaSsPL(int gI1, int gI2) const
{
   const std::complex<double> result = Conj(UP(gI1,1))*Conj(ZS(gI2,0))*Yu(1,1);

   return result;
}

std::complex<double> CLASSNAME::CpbarFcbarChaSsPR(int gI1, int gI2) const
{
   const std::complex<double> result = -(g2*Conj(ZS(gI2,0))*UM(gI1,0)) + Conj(
      Yd(1,1))*Conj(ZS(gI2,1))*UM(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpbarFcChiScPL(int gI2, int gI1) const
{
   const std::complex<double> result = 0.7302967433402214*g1*Conj(ZC(gI1,1))*
      Conj(ZN(gI2,0)) - Conj(ZC(gI1,0))*Conj(ZN(gI2,3))*Yu(1,1);

   return result;
}

std::complex<double> CLASSNAME::CpbarFcChiScPR(int gI2, int gI1) const
{
   const std::complex<double> result = Conj(ZC(gI1,0))*(-0.18257418583505536*g1
      *ZN(gI2,0) - 0.7071067811865475*g2*ZN(gI2,1)) - Conj(Yu(1,1))*Conj(ZC(gI1,1)
      )*ZN(gI2,3);

   return result;
}

std::complex<double> CLASSNAME::CpbarFcFchhPL(int gI1) const
{
   const std::complex<double> result = -0.7071067811865475*Yu(1,1)*ZH(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpbarFcFchhPR(int gI1) const
{
   const std::complex<double> result = -0.7071067811865475*Conj(Yu(1,1))*ZH(gI1
      ,1);

   return result;
}

std::complex<double> CLASSNAME::CpbarFcFsconjHpmPL(int gI1) const
{
   const std::complex<double> result = Yu(1,1)*ZP(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpbarFcFsconjHpmPR(int gI1) const
{
   const std::complex<double> result = Conj(Yd(1,1))*ZP(gI1,0);

   return result;
}

std::complex<double> CLASSNAME::CpbarFcFcAhPL(int gI2) const
{
   const std::complex<double> result = std::complex<double>(0.,
      -0.7071067811865475)*Yu(1,1)*ZA(gI2,1);

   return result;
}

std::complex<double> CLASSNAME::CpbarFcFcAhPR(int gI2) const
{
   const std::complex<double> result = std::complex<double>(0.,
      0.7071067811865475)*Conj(Yu(1,1))*ZA(gI2,1);

   return result;
}

std::complex<double> CLASSNAME::CpbarFtbarChaSbPL(int gI1, int gI2) const
{
   const std::complex<double> result = Conj(UP(gI1,1))*Conj(ZB(gI2,0))*Yu(2,2);

   return result;
}

std::complex<double> CLASSNAME::CpbarFtbarChaSbPR(int gI1, int gI2) const
{
   const std::complex<double> result = -(g2*Conj(ZB(gI2,0))*UM(gI1,0)) + Conj(
      Yd(2,2))*Conj(ZB(gI2,1))*UM(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpbarFtChiStPL(int gI2, int gI1) const
{
   const std::complex<double> result = 0.7302967433402214*g1*Conj(ZN(gI2,0))*
      Conj(ZT(gI1,1)) - Conj(ZN(gI2,3))*Conj(ZT(gI1,0))*Yu(2,2);

   return result;
}

std::complex<double> CLASSNAME::CpbarFtChiStPR(int gI2, int gI1) const
{
   const std::complex<double> result = Conj(ZT(gI1,0))*(-0.18257418583505536*g1
      *ZN(gI2,0) - 0.7071067811865475*g2*ZN(gI2,1)) - Conj(Yu(2,2))*Conj(ZT(gI1,1)
      )*ZN(gI2,3);

   return result;
}

std::complex<double> CLASSNAME::CpbarFtFbconjHpmPL(int gI1) const
{
   const std::complex<double> result = Yu(2,2)*ZP(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpbarFtFbconjHpmPR(int gI1) const
{
   const std::complex<double> result = Conj(Yd(2,2))*ZP(gI1,0);

   return result;
}

std::complex<double> CLASSNAME::CpbarFtFthhPL(int gI1) const
{
   const std::complex<double> result = -0.7071067811865475*Yu(2,2)*ZH(gI1,1);

   return result;
}

std::complex<double> CLASSNAME::CpbarFtFthhPR(int gI1) const
{
   const std::complex<double> result = -0.7071067811865475*Conj(Yu(2,2))*ZH(gI1
      ,1);

   return result;
}

std::complex<double> CLASSNAME::CpbarFtFtAhPL(int gI2) const
{
   const std::complex<double> result = std::complex<double>(0.,
      -0.7071067811865475)*Yu(2,2)*ZA(gI2,1);

   return result;
}

std::complex<double> CLASSNAME::CpbarFtFtAhPR(int gI2) const
{
   const std::complex<double> result = std::complex<double>(0.,
      0.7071067811865475)*Conj(Yu(2,2))*ZA(gI2,1);

   return result;
}

double CLASSNAME::CpbarFvebarChaSePL(int , int ) const
{
   const double result = 0;

   return result;
}

std::complex<double> CLASSNAME::CpbarFvebarChaSePR(int gI1, int gI2) const
{
   const std::complex<double> result = -(g2*Conj(ZE(gI2,0))*UM(gI1,0)) + Conj(
      Ye(0,0))*Conj(ZE(gI2,1))*UM(gI1,1);

   return result;
}

double CLASSNAME::CpbarFveFeconjHpmPL(int ) const
{
   const double result = 0;

   return result;
}

std::complex<double> CLASSNAME::CpbarFveFeconjHpmPR(int gI1) const
{
   const std::complex<double> result = Conj(Ye(0,0))*ZP(gI1,0);

   return result;
}

double CLASSNAME::CpbarFveChiSveLPL(int ) const
{
   const double result = 0;

   return result;
}

std::complex<double> CLASSNAME::CpbarFveChiSveLPR(int gI2) const
{
   const std::complex<double> result = 0.7071067811865475*(0.7745966692414834*
      g1*ZN(gI2,0) - g2*ZN(gI2,1));

   return result;
}

double CLASSNAME::CpbarFvmbarChaSmPL(int , int ) const
{
   const double result = 0;

   return result;
}

std::complex<double> CLASSNAME::CpbarFvmbarChaSmPR(int gI1, int gI2) const
{
   const std::complex<double> result = -(g2*Conj(ZM(gI2,0))*UM(gI1,0)) + Conj(
      Ye(1,1))*Conj(ZM(gI2,1))*UM(gI1,1);

   return result;
}

double CLASSNAME::CpbarFvmFmconjHpmPL(int ) const
{
   const double result = 0;

   return result;
}

std::complex<double> CLASSNAME::CpbarFvmFmconjHpmPR(int gI1) const
{
   const std::complex<double> result = Conj(Ye(1,1))*ZP(gI1,0);

   return result;
}

double CLASSNAME::CpbarFvmChiSvmLPL(int ) const
{
   const double result = 0;

   return result;
}

std::complex<double> CLASSNAME::CpbarFvmChiSvmLPR(int gI2) const
{
   const std::complex<double> result = 0.7071067811865475*(0.7745966692414834*
      g1*ZN(gI2,0) - g2*ZN(gI2,1));

   return result;
}

double CLASSNAME::CpbarFvtbarChaStauPL(int , int ) const
{
   const double result = 0;

   return result;
}

std::complex<double> CLASSNAME::CpbarFvtbarChaStauPR(int gI1, int gI2) const
{
   const std::complex<double> result = -(g2*Conj(ZTau(gI2,0))*UM(gI1,0)) + Conj
      (Ye(2,2))*Conj(ZTau(gI2,1))*UM(gI1,1);

   return result;
}

double CLASSNAME::CpbarFvtFtauconjHpmPL(int ) const
{
   const double result = 0;

   return result;
}

std::complex<double> CLASSNAME::CpbarFvtFtauconjHpmPR(int gI1) const
{
   const std::complex<double> result = Conj(Ye(2,2))*ZP(gI1,0);

   return result;
}

double CLASSNAME::CpbarFvtChiSvtLPL(int ) const
{
   const double result = 0;

   return result;
}

std::complex<double> CLASSNAME::CpbarFvtChiSvtLPR(int gI2) const
{
   const std::complex<double> result = 0.7071067811865475*(0.7745966692414834*
      g1*ZN(gI2,0) - g2*ZN(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpbarFeChiSePL(int gI2, int gI1) const
{
   const std::complex<double> result = -1.0954451150103321*g1*Conj(ZE(gI1,1))*
      Conj(ZN(gI2,0)) - Conj(ZE(gI1,0))*Conj(ZN(gI2,2))*Ye(0,0);

   return result;
}

std::complex<double> CLASSNAME::CpbarFeChiSePR(int gI2, int gI1) const
{
   const std::complex<double> result = 0.7071067811865475*Conj(ZE(gI1,0))*(
      0.7745966692414834*g1*ZN(gI2,0) + g2*ZN(gI2,1)) - Conj(Ye(0,0))*Conj(ZE(gI1,
      1))*ZN(gI2,2);

   return result;
}

std::complex<double> CLASSNAME::CpbarFeFehhPL(int gI1) const
{
   const std::complex<double> result = -0.7071067811865475*Ye(0,0)*ZH(gI1,0);

   return result;
}

std::complex<double> CLASSNAME::CpbarFeFehhPR(int gI1) const
{
   const std::complex<double> result = -0.7071067811865475*Conj(Ye(0,0))*ZH(gI1
      ,0);

   return result;
}

std::complex<double> CLASSNAME::CpbarFeFveHpmPL(int gI1) const
{
   const std::complex<double> result = Ye(0,0)*ZP(gI1,0);

   return result;
}

double CLASSNAME::CpbarFeFveHpmPR(int ) const
{
   const double result = 0;

   return result;
}

std::complex<double> CLASSNAME::CpbarFeFeAhPL(int gI2) const
{
   const std::complex<double> result = std::complex<double>(0.,
      -0.7071067811865475)*Ye(0,0)*ZA(gI2,0);

   return result;
}

std::complex<double> CLASSNAME::CpbarFeFeAhPR(int gI2) const
{
   const std::complex<double> result = std::complex<double>(0.,
      0.7071067811865475)*Conj(Ye(0,0))*ZA(gI2,0);

   return result;
}

std::complex<double> CLASSNAME::CpbarFeChaSveLPL(int gI2) const
{
   const std::complex<double> result = Conj(UM(gI2,1))*Ye(0,0);

   return result;
}

std::complex<double> CLASSNAME::CpbarFeChaSveLPR(int gI2) const
{
   const std::complex<double> result = -(g2*UP(gI2,0));

   return result;
}

double CLASSNAME::CpbarFeFveVWmPR() const
{
   const double result = 0;

   return result;
}

double CLASSNAME::CpbarFeFveVWmPL() const
{
   const double result = -0.7071067811865475*g2;

   return result;
}

std::complex<double> CLASSNAME::CpbarFmChiSmPL(int gI2, int gI1) const
{
   const std::complex<double> result = -1.0954451150103321*g1*Conj(ZM(gI1,1))*
      Conj(ZN(gI2,0)) - Conj(ZM(gI1,0))*Conj(ZN(gI2,2))*Ye(1,1);

   return result;
}

std::complex<double> CLASSNAME::CpbarFmChiSmPR(int gI2, int gI1) const
{
   const std::complex<double> result = 0.7071067811865475*Conj(ZM(gI1,0))*(
      0.7745966692414834*g1*ZN(gI2,0) + g2*ZN(gI2,1)) - Conj(Ye(1,1))*Conj(ZM(gI1,
      1))*ZN(gI2,2);

   return result;
}

std::complex<double> CLASSNAME::CpbarFmFmhhPL(int gI1) const
{
   const std::complex<double> result = -0.7071067811865475*Ye(1,1)*ZH(gI1,0);

   return result;
}

std::complex<double> CLASSNAME::CpbarFmFmhhPR(int gI1) const
{
   const std::complex<double> result = -0.7071067811865475*Conj(Ye(1,1))*ZH(gI1
      ,0);

   return result;
}

std::complex<double> CLASSNAME::CpbarFmFvmHpmPL(int gI1) const
{
   const std::complex<double> result = Ye(1,1)*ZP(gI1,0);

   return result;
}

double CLASSNAME::CpbarFmFvmHpmPR(int ) const
{
   const double result = 0;

   return result;
}

std::complex<double> CLASSNAME::CpbarFmFmAhPL(int gI2) const
{
   const std::complex<double> result = std::complex<double>(0.,
      -0.7071067811865475)*Ye(1,1)*ZA(gI2,0);

   return result;
}

std::complex<double> CLASSNAME::CpbarFmFmAhPR(int gI2) const
{
   const std::complex<double> result = std::complex<double>(0.,
      0.7071067811865475)*Conj(Ye(1,1))*ZA(gI2,0);

   return result;
}

std::complex<double> CLASSNAME::CpbarFmChaSvmLPL(int gI2) const
{
   const std::complex<double> result = Conj(UM(gI2,1))*Ye(1,1);

   return result;
}

std::complex<double> CLASSNAME::CpbarFmChaSvmLPR(int gI2) const
{
   const std::complex<double> result = -(g2*UP(gI2,0));

   return result;
}

double CLASSNAME::CpbarFmFvmVWmPR() const
{
   const double result = 0;

   return result;
}

double CLASSNAME::CpbarFmFvmVWmPL() const
{
   const double result = -0.7071067811865475*g2;

   return result;
}

std::complex<double> CLASSNAME::CpbarFtauChiStauPL(int gI2, int gI1) const
{
   const std::complex<double> result = -1.0954451150103321*g1*Conj(ZN(gI2,0))*
      Conj(ZTau(gI1,1)) - Conj(ZN(gI2,2))*Conj(ZTau(gI1,0))*Ye(2,2);

   return result;
}

std::complex<double> CLASSNAME::CpbarFtauChiStauPR(int gI2, int gI1) const
{
   const std::complex<double> result = 0.7071067811865475*Conj(ZTau(gI1,0))*(
      0.7745966692414834*g1*ZN(gI2,0) + g2*ZN(gI2,1)) - Conj(Ye(2,2))*Conj(ZTau(
      gI1,1))*ZN(gI2,2);

   return result;
}

std::complex<double> CLASSNAME::CpbarFtauFtauhhPL(int gI1) const
{
   const std::complex<double> result = -0.7071067811865475*Ye(2,2)*ZH(gI1,0);

   return result;
}

std::complex<double> CLASSNAME::CpbarFtauFtauhhPR(int gI1) const
{
   const std::complex<double> result = -0.7071067811865475*Conj(Ye(2,2))*ZH(gI1
      ,0);

   return result;
}

std::complex<double> CLASSNAME::CpbarFtauFvtHpmPL(int gI1) const
{
   const std::complex<double> result = Ye(2,2)*ZP(gI1,0);

   return result;
}

double CLASSNAME::CpbarFtauFvtHpmPR(int ) const
{
   const double result = 0;

   return result;
}

std::complex<double> CLASSNAME::CpbarFtauFtauAhPL(int gI2) const
{
   const std::complex<double> result = std::complex<double>(0.,
      -0.7071067811865475)*Ye(2,2)*ZA(gI2,0);

   return result;
}

std::complex<double> CLASSNAME::CpbarFtauFtauAhPR(int gI2) const
{
   const std::complex<double> result = std::complex<double>(0.,
      0.7071067811865475)*Conj(Ye(2,2))*ZA(gI2,0);

   return result;
}

std::complex<double> CLASSNAME::CpbarFtauChaSvtLPL(int gI2) const
{
   const std::complex<double> result = Conj(UM(gI2,1))*Ye(2,2);

   return result;
}

std::complex<double> CLASSNAME::CpbarFtauChaSvtLPR(int gI2) const
{
   const std::complex<double> result = -(g2*UP(gI2,0));

   return result;
}

double CLASSNAME::CpbarFtauFvtVWmPR() const
{
   const double result = 0;

   return result;
}

double CLASSNAME::CpbarFtauFvtVWmPL() const
{
   const double result = -0.7071067811865475*g2;

   return result;
}


std::complex<double> CLASSNAME::self_energy_Sd_1loop(double p , int gO1, int gO2) const
{
   std::complex<double> result;

   result += -(A0(Sqr(MSveL))*CpSveLUSdconjSveLconjUSd(gO1,gO2));
   result += -(A0(Sqr(MSvmL))*CpSvmLUSdconjSvmLconjUSd(gO1,gO2));
   result += -(A0(Sqr(MSvtL))*CpSvtLUSdconjSvtLconjUSd(gO1,gO2));
   result += 4*A0(Sqr(MVWm))*CpUSdconjUSdconjVWmVWm(gO1,gO2);
   result += 2*A0(Sqr(MVZ))*CpUSdconjUSdVZVZ(gO1,gO2);
   result += 1.3333333333333333*(Conj(CpGluFdconjUSdPL(gO2))*CpGluFdconjUSdPL(
      gO1) + Conj(CpGluFdconjUSdPR(gO2))*CpGluFdconjUSdPR(gO1))*G0(Sqr(p),Sqr(MGlu
      ),Sqr(MFd));
   result += -2.6666666666666665*MFd*MGlu*B0(Sqr(p),Sqr(MGlu),Sqr(MFd))*(Conj(
      CpGluFdconjUSdPR(gO2))*CpGluFdconjUSdPL(gO1) + Conj(CpGluFdconjUSdPL(gO2))*
      CpGluFdconjUSdPR(gO1));
   result += -0.5*SUM(gI1,0,1,A0(Sqr(MAh(gI1)))*CpAhAhUSdconjUSd(gI1,gI1,gO1,
      gO2));
   result += -0.5*SUM(gI1,0,1,A0(Sqr(Mhh(gI1)))*CphhhhUSdconjUSd(gI1,gI1,gO1,
      gO2));
   result += -SUM(gI1,0,1,A0(Sqr(MHpm(gI1)))*CpHpmUSdconjHpmconjUSd(gI1,gO1,gI1
      ,gO2));
   result += -SUM(gI1,0,1,A0(Sqr(MSb(gI1)))*CpUSdconjUSdconjSbSb(gO1,gO2,gI1,
      gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MSc(gI1)))*CpUSdconjUSdconjScSc(gO1,gO2,gI1,
      gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MSd(gI1)))*CpUSdconjUSdconjSdSd(gO1,gO2,gI1,
      gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MSs(gI1)))*CpUSdconjUSdconjSsSs(gO1,gO2,gI1,
      gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MSt(gI1)))*CpUSdconjUSdconjStSt(gO1,gO2,gI1,
      gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MSu(gI1)))*CpUSdconjUSdconjSuSu(gO1,gO2,gI1,
      gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MSe(gI1)))*CpUSdSeconjUSdconjSe(gO1,gI1,gO2,
      gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MSm(gI1)))*CpUSdSmconjUSdconjSm(gO1,gI1,gO2,
      gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MStau(gI1)))*CpUSdStauconjUSdconjStau(gO1,gI1,
      gO2,gI1));
   result += SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(MSd(gI1)),Sqr(MAh(gI2)))*
      Conj(CpAhSdconjUSd(gI2,gI1,gO2))*CpAhSdconjUSd(gI2,gI1,gO1)));
   result += SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(MSd(gI1)),Sqr(Mhh(gI2)))*
      Conj(CphhSdconjUSd(gI2,gI1,gO2))*CphhSdconjUSd(gI2,gI1,gO1)));
   result += SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(MSu(gI1)),Sqr(MHpm(gI2)))*
      Conj(CpHpmSuconjUSd(gI2,gI1,gO2))*CpHpmSuconjUSd(gI2,gI1,gO1)));
   result += 1.3333333333333333*SUM(gI2,0,1,Conj(CpSdconjUSdVG(gI2,gO2))*
      CpSdconjUSdVG(gI2,gO1)*F0(Sqr(p),Sqr(MSd(gI2)),0));
   result += SUM(gI2,0,1,Conj(CpSdconjUSdVP(gI2,gO2))*CpSdconjUSdVP(gI2,gO1)*F0
      (Sqr(p),Sqr(MSd(gI2)),0));
   result += SUM(gI2,0,1,Conj(CpSdconjUSdVZ(gI2,gO2))*CpSdconjUSdVZ(gI2,gO1)*F0
      (Sqr(p),Sqr(MSd(gI2)),Sqr(MVZ)));
   result += SUM(gI2,0,1,Conj(CpSuconjUSdVWm(gI2,gO2))*CpSuconjUSdVWm(gI2,gO1)*
      F0(Sqr(p),Sqr(MSu(gI2)),Sqr(MVWm)));
   result += SUM(gI2,0,1,(Conj(CpFuChaconjUSdPL(gI2,gO2))*CpFuChaconjUSdPL(gI2,
      gO1) + Conj(CpFuChaconjUSdPR(gI2,gO2))*CpFuChaconjUSdPR(gI2,gO1))*G0(Sqr(p),
      Sqr(MFu),Sqr(MCha(gI2))));
   result += -2*MFu*SUM(gI2,0,1,B0(Sqr(p),Sqr(MFu),Sqr(MCha(gI2)))*(Conj(
      CpFuChaconjUSdPR(gI2,gO2))*CpFuChaconjUSdPL(gI2,gO1) + Conj(CpFuChaconjUSdPL
      (gI2,gO2))*CpFuChaconjUSdPR(gI2,gO1))*MCha(gI2));
   result += SUM(gI2,0,3,(Conj(CpChiFdconjUSdPL(gI2,gO2))*CpChiFdconjUSdPL(gI2,
      gO1) + Conj(CpChiFdconjUSdPR(gI2,gO2))*CpChiFdconjUSdPR(gI2,gO1))*G0(Sqr(p),
      Sqr(MFd),Sqr(MChi(gI2))));
   result += -2*MFd*SUM(gI2,0,3,B0(Sqr(p),Sqr(MFd),Sqr(MChi(gI2)))*(Conj(
      CpChiFdconjUSdPR(gI2,gO2))*CpChiFdconjUSdPL(gI2,gO1) + Conj(CpChiFdconjUSdPL
      (gI2,gO2))*CpChiFdconjUSdPR(gI2,gO1))*MChi(gI2));

   return result * oneOver16PiSqr;

}

Eigen::Matrix<std::complex<double>,2,2> CLASSNAME::self_energy_Sd_1loop(double p) const
{
   Eigen::Matrix<std::complex<double>,2,2> self_energy;

   for (int i = 0; i < 2; i++)
      for (int k = i; k < 2; k++)
         self_energy(i, k) = self_energy_Sd_1loop(p, i, k);

   Hermitianize(self_energy);

   return self_energy;
}

std::complex<double> CLASSNAME::self_energy_Su_1loop(double p , int gO1, int gO2) const
{
   std::complex<double> result;

   result += -(A0(Sqr(MSveL))*CpSveLUSuconjSveLconjUSu(gO1,gO2));
   result += -(A0(Sqr(MSvmL))*CpSvmLUSuconjSvmLconjUSu(gO1,gO2));
   result += -(A0(Sqr(MSvtL))*CpSvtLUSuconjSvtLconjUSu(gO1,gO2));
   result += 4*A0(Sqr(MVWm))*CpUSuconjUSuconjVWmVWm(gO1,gO2);
   result += 2*A0(Sqr(MVZ))*CpUSuconjUSuVZVZ(gO1,gO2);
   result += 1.3333333333333333*(Conj(CpGluFuconjUSuPL(gO2))*CpGluFuconjUSuPL(
      gO1) + Conj(CpGluFuconjUSuPR(gO2))*CpGluFuconjUSuPR(gO1))*G0(Sqr(p),Sqr(MGlu
      ),Sqr(MFu));
   result += -2.6666666666666665*MFu*MGlu*B0(Sqr(p),Sqr(MGlu),Sqr(MFu))*(Conj(
      CpGluFuconjUSuPR(gO2))*CpGluFuconjUSuPL(gO1) + Conj(CpGluFuconjUSuPL(gO2))*
      CpGluFuconjUSuPR(gO1));
   result += -0.5*SUM(gI1,0,1,A0(Sqr(MAh(gI1)))*CpAhAhUSuconjUSu(gI1,gI1,gO1,
      gO2));
   result += -0.5*SUM(gI1,0,1,A0(Sqr(Mhh(gI1)))*CphhhhUSuconjUSu(gI1,gI1,gO1,
      gO2));
   result += -SUM(gI1,0,1,A0(Sqr(MHpm(gI1)))*CpHpmUSuconjHpmconjUSu(gI1,gO1,gI1
      ,gO2));
   result += -SUM(gI1,0,1,A0(Sqr(MSe(gI1)))*CpSeUSuconjSeconjUSu(gI1,gO1,gI1,
      gO2));
   result += -SUM(gI1,0,1,A0(Sqr(MSm(gI1)))*CpSmUSuconjSmconjUSu(gI1,gO1,gI1,
      gO2));
   result += -SUM(gI1,0,1,A0(Sqr(MStau(gI1)))*CpStauUSuconjStauconjUSu(gI1,gO1,
      gI1,gO2));
   result += -SUM(gI1,0,1,A0(Sqr(MSb(gI1)))*CpUSuconjUSuconjSbSb(gO1,gO2,gI1,
      gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MSc(gI1)))*CpUSuconjUSuconjScSc(gO1,gO2,gI1,
      gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MSd(gI1)))*CpUSuconjUSuconjSdSd(gO1,gO2,gI1,
      gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MSs(gI1)))*CpUSuconjUSuconjSsSs(gO1,gO2,gI1,
      gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MSt(gI1)))*CpUSuconjUSuconjStSt(gO1,gO2,gI1,
      gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MSu(gI1)))*CpUSuconjUSuconjSuSu(gO1,gO2,gI1,
      gI1));
   result += SUM(gI1,0,1,(Conj(CpbarChaFdconjUSuPL(gI1,gO2))*
      CpbarChaFdconjUSuPL(gI1,gO1) + Conj(CpbarChaFdconjUSuPR(gI1,gO2))*
      CpbarChaFdconjUSuPR(gI1,gO1))*G0(Sqr(p),Sqr(MCha(gI1)),Sqr(MFd)));
   result += -2*MFd*SUM(gI1,0,1,B0(Sqr(p),Sqr(MCha(gI1)),Sqr(MFd))*(Conj(
      CpbarChaFdconjUSuPR(gI1,gO2))*CpbarChaFdconjUSuPL(gI1,gO1) + Conj(
      CpbarChaFdconjUSuPL(gI1,gO2))*CpbarChaFdconjUSuPR(gI1,gO1))*MCha(gI1));
   result += SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(MSu(gI1)),Sqr(MAh(gI2)))*
      Conj(CpAhSuconjUSu(gI2,gI1,gO2))*CpAhSuconjUSu(gI2,gI1,gO1)));
   result += SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(MSu(gI1)),Sqr(Mhh(gI2)))*
      Conj(CphhSuconjUSu(gI2,gI1,gO2))*CphhSuconjUSu(gI2,gI1,gO1)));
   result += SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(MHpm(gI1)),Sqr(MSd(gI2)))*
      Conj(CpSdconjHpmconjUSu(gI2,gI1,gO2))*CpSdconjHpmconjUSu(gI2,gI1,gO1)));
   result += SUM(gI2,0,1,Conj(CpSdconjUSuconjVWm(gI2,gO2))*CpSdconjUSuconjVWm(
      gI2,gO1)*F0(Sqr(p),Sqr(MSd(gI2)),Sqr(MVWm)));
   result += 1.3333333333333333*SUM(gI2,0,1,Conj(CpSuconjUSuVG(gI2,gO2))*
      CpSuconjUSuVG(gI2,gO1)*F0(Sqr(p),Sqr(MSu(gI2)),0));
   result += SUM(gI2,0,1,Conj(CpSuconjUSuVP(gI2,gO2))*CpSuconjUSuVP(gI2,gO1)*F0
      (Sqr(p),Sqr(MSu(gI2)),0));
   result += SUM(gI2,0,1,Conj(CpSuconjUSuVZ(gI2,gO2))*CpSuconjUSuVZ(gI2,gO1)*F0
      (Sqr(p),Sqr(MSu(gI2)),Sqr(MVZ)));
   result += SUM(gI2,0,3,(Conj(CpChiFuconjUSuPL(gI2,gO2))*CpChiFuconjUSuPL(gI2,
      gO1) + Conj(CpChiFuconjUSuPR(gI2,gO2))*CpChiFuconjUSuPR(gI2,gO1))*G0(Sqr(p),
      Sqr(MFu),Sqr(MChi(gI2))));
   result += -2*MFu*SUM(gI2,0,3,B0(Sqr(p),Sqr(MFu),Sqr(MChi(gI2)))*(Conj(
      CpChiFuconjUSuPR(gI2,gO2))*CpChiFuconjUSuPL(gI2,gO1) + Conj(CpChiFuconjUSuPL
      (gI2,gO2))*CpChiFuconjUSuPR(gI2,gO1))*MChi(gI2));

   return result * oneOver16PiSqr;

}

Eigen::Matrix<std::complex<double>,2,2> CLASSNAME::self_energy_Su_1loop(double p) const
{
   Eigen::Matrix<std::complex<double>,2,2> self_energy;

   for (int i = 0; i < 2; i++)
      for (int k = i; k < 2; k++)
         self_energy(i, k) = self_energy_Su_1loop(p, i, k);

   Hermitianize(self_energy);

   return self_energy;
}

std::complex<double> CLASSNAME::self_energy_Se_1loop(double p , int gO1, int gO2) const
{
   std::complex<double> result;

   result += -(A0(Sqr(MSveL))*CpSveLUSeconjSveLconjUSe(gO1,gO2));
   result += -(A0(Sqr(MSvmL))*CpSvmLUSeconjSvmLconjUSe(gO1,gO2));
   result += -(A0(Sqr(MSvtL))*CpSvtLUSeconjSvtLconjUSe(gO1,gO2));
   result += 4*A0(Sqr(MVWm))*CpUSeconjUSeconjVWmVWm(gO1,gO2);
   result += 2*A0(Sqr(MVZ))*CpUSeconjUSeVZVZ(gO1,gO2);
   result += Conj(CpSveLconjUSeVWm(gO2))*CpSveLconjUSeVWm(gO1)*F0(Sqr(p),Sqr(
      MSveL),Sqr(MVWm));
   result += -0.5*SUM(gI1,0,1,A0(Sqr(MAh(gI1)))*CpAhAhUSeconjUSe(gI1,gI1,gO1,
      gO2));
   result += -0.5*SUM(gI1,0,1,A0(Sqr(Mhh(gI1)))*CphhhhUSeconjUSe(gI1,gI1,gO1,
      gO2));
   result += -SUM(gI1,0,1,A0(Sqr(MHpm(gI1)))*CpHpmUSeconjHpmconjUSe(gI1,gO1,gI1
      ,gO2));
   result += -3*SUM(gI1,0,1,A0(Sqr(MSb(gI1)))*CpSbUSeconjSbconjUSe(gI1,gO1,gI1,
      gO2));
   result += -3*SUM(gI1,0,1,A0(Sqr(MSc(gI1)))*CpScUSeconjScconjUSe(gI1,gO1,gI1,
      gO2));
   result += -3*SUM(gI1,0,1,A0(Sqr(MSd(gI1)))*CpSdUSeconjSdconjUSe(gI1,gO1,gI1,
      gO2));
   result += -SUM(gI1,0,1,A0(Sqr(MSe(gI1)))*CpSeUSeconjSeconjUSe(gI1,gO1,gI1,
      gO2));
   result += -SUM(gI1,0,1,A0(Sqr(MSm(gI1)))*CpUSeSmconjUSeconjSm(gO1,gI1,gO2,
      gI1));
   result += -3*SUM(gI1,0,1,A0(Sqr(MSs(gI1)))*CpUSeSsconjUSeconjSs(gO1,gI1,gO2,
      gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MStau(gI1)))*CpUSeStauconjUSeconjStau(gO1,gI1,
      gO2,gI1));
   result += -3*SUM(gI1,0,1,A0(Sqr(MSt(gI1)))*CpUSeStconjUSeconjSt(gO1,gI1,gO2,
      gI1));
   result += -3*SUM(gI1,0,1,A0(Sqr(MSu(gI1)))*CpUSeSuconjUSeconjSu(gO1,gI1,gO2,
      gI1));
   result += SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(MSe(gI1)),Sqr(MAh(gI2)))*
      Conj(CpAhSeconjUSe(gI2,gI1,gO2))*CpAhSeconjUSe(gI2,gI1,gO1)));
   result += SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(MSe(gI1)),Sqr(Mhh(gI2)))*
      Conj(CphhSeconjUSe(gI2,gI1,gO2))*CphhSeconjUSe(gI2,gI1,gO1)));
   result += SUM(gI2,0,1,B0(Sqr(p),Sqr(MSveL),Sqr(MHpm(gI2)))*Conj(
      CpSveLHpmconjUSe(gI2,gO2))*CpSveLHpmconjUSe(gI2,gO1));
   result += SUM(gI2,0,1,Conj(CpSeconjUSeVP(gI2,gO2))*CpSeconjUSeVP(gI2,gO1)*F0
      (Sqr(p),Sqr(MSe(gI2)),0));
   result += SUM(gI2,0,1,Conj(CpSeconjUSeVZ(gI2,gO2))*CpSeconjUSeVZ(gI2,gO1)*F0
      (Sqr(p),Sqr(MSe(gI2)),Sqr(MVZ)));
   result += SUM(gI2,0,1,(Conj(CpFveChaconjUSePL(gI2,gO2))*CpFveChaconjUSePL(
      gI2,gO1) + Conj(CpFveChaconjUSePR(gI2,gO2))*CpFveChaconjUSePR(gI2,gO1))*G0(
      Sqr(p),Sqr(MFve),Sqr(MCha(gI2))));
   result += -2*MFve*SUM(gI2,0,1,B0(Sqr(p),Sqr(MFve),Sqr(MCha(gI2)))*(Conj(
      CpFveChaconjUSePR(gI2,gO2))*CpFveChaconjUSePL(gI2,gO1) + Conj(
      CpFveChaconjUSePL(gI2,gO2))*CpFveChaconjUSePR(gI2,gO1))*MCha(gI2));
   result += SUM(gI2,0,3,(Conj(CpChiFeconjUSePL(gI2,gO2))*CpChiFeconjUSePL(gI2,
      gO1) + Conj(CpChiFeconjUSePR(gI2,gO2))*CpChiFeconjUSePR(gI2,gO1))*G0(Sqr(p),
      Sqr(MFe),Sqr(MChi(gI2))));
   result += -2*MFe*SUM(gI2,0,3,B0(Sqr(p),Sqr(MFe),Sqr(MChi(gI2)))*(Conj(
      CpChiFeconjUSePR(gI2,gO2))*CpChiFeconjUSePL(gI2,gO1) + Conj(CpChiFeconjUSePL
      (gI2,gO2))*CpChiFeconjUSePR(gI2,gO1))*MChi(gI2));

   return result * oneOver16PiSqr;

}

Eigen::Matrix<std::complex<double>,2,2> CLASSNAME::self_energy_Se_1loop(double p) const
{
   Eigen::Matrix<std::complex<double>,2,2> self_energy;

   for (int i = 0; i < 2; i++)
      for (int k = i; k < 2; k++)
         self_energy(i, k) = self_energy_Se_1loop(p, i, k);

   Hermitianize(self_energy);

   return self_energy;
}

std::complex<double> CLASSNAME::self_energy_Sm_1loop(double p , int gO1, int gO2) const
{
   std::complex<double> result;

   result += -(A0(Sqr(MSveL))*CpSveLUSmconjSveLconjUSm(gO1,gO2));
   result += -(A0(Sqr(MSvmL))*CpSvmLUSmconjSvmLconjUSm(gO1,gO2));
   result += -(A0(Sqr(MSvtL))*CpSvtLUSmconjSvtLconjUSm(gO1,gO2));
   result += 4*A0(Sqr(MVWm))*CpUSmconjUSmconjVWmVWm(gO1,gO2);
   result += 2*A0(Sqr(MVZ))*CpUSmconjUSmVZVZ(gO1,gO2);
   result += Conj(CpSvmLconjUSmVWm(gO2))*CpSvmLconjUSmVWm(gO1)*F0(Sqr(p),Sqr(
      MSvmL),Sqr(MVWm));
   result += -0.5*SUM(gI1,0,1,A0(Sqr(MAh(gI1)))*CpAhAhUSmconjUSm(gI1,gI1,gO1,
      gO2));
   result += -0.5*SUM(gI1,0,1,A0(Sqr(Mhh(gI1)))*CphhhhUSmconjUSm(gI1,gI1,gO1,
      gO2));
   result += -SUM(gI1,0,1,A0(Sqr(MHpm(gI1)))*CpHpmUSmconjHpmconjUSm(gI1,gO1,gI1
      ,gO2));
   result += -3*SUM(gI1,0,1,A0(Sqr(MSb(gI1)))*CpSbUSmconjSbconjUSm(gI1,gO1,gI1,
      gO2));
   result += -3*SUM(gI1,0,1,A0(Sqr(MSc(gI1)))*CpScUSmconjScconjUSm(gI1,gO1,gI1,
      gO2));
   result += -3*SUM(gI1,0,1,A0(Sqr(MSd(gI1)))*CpSdUSmconjSdconjUSm(gI1,gO1,gI1,
      gO2));
   result += -SUM(gI1,0,1,A0(Sqr(MSe(gI1)))*CpSeUSmconjSeconjUSm(gI1,gO1,gI1,
      gO2));
   result += -SUM(gI1,0,1,A0(Sqr(MSm(gI1)))*CpSmUSmconjSmconjUSm(gI1,gO1,gI1,
      gO2));
   result += -3*SUM(gI1,0,1,A0(Sqr(MSs(gI1)))*CpUSmSsconjUSmconjSs(gO1,gI1,gO2,
      gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MStau(gI1)))*CpUSmStauconjUSmconjStau(gO1,gI1,
      gO2,gI1));
   result += -3*SUM(gI1,0,1,A0(Sqr(MSt(gI1)))*CpUSmStconjUSmconjSt(gO1,gI1,gO2,
      gI1));
   result += -3*SUM(gI1,0,1,A0(Sqr(MSu(gI1)))*CpUSmSuconjUSmconjSu(gO1,gI1,gO2,
      gI1));
   result += SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(MSm(gI1)),Sqr(MAh(gI2)))*
      Conj(CpAhSmconjUSm(gI2,gI1,gO2))*CpAhSmconjUSm(gI2,gI1,gO1)));
   result += SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(MSm(gI1)),Sqr(Mhh(gI2)))*
      Conj(CphhSmconjUSm(gI2,gI1,gO2))*CphhSmconjUSm(gI2,gI1,gO1)));
   result += SUM(gI2,0,1,B0(Sqr(p),Sqr(MSvmL),Sqr(MHpm(gI2)))*Conj(
      CpSvmLHpmconjUSm(gI2,gO2))*CpSvmLHpmconjUSm(gI2,gO1));
   result += SUM(gI2,0,1,Conj(CpSmconjUSmVP(gI2,gO2))*CpSmconjUSmVP(gI2,gO1)*F0
      (Sqr(p),Sqr(MSm(gI2)),0));
   result += SUM(gI2,0,1,Conj(CpSmconjUSmVZ(gI2,gO2))*CpSmconjUSmVZ(gI2,gO1)*F0
      (Sqr(p),Sqr(MSm(gI2)),Sqr(MVZ)));
   result += SUM(gI2,0,1,(Conj(CpFvmChaconjUSmPL(gI2,gO2))*CpFvmChaconjUSmPL(
      gI2,gO1) + Conj(CpFvmChaconjUSmPR(gI2,gO2))*CpFvmChaconjUSmPR(gI2,gO1))*G0(
      Sqr(p),Sqr(MFvm),Sqr(MCha(gI2))));
   result += -2*MFvm*SUM(gI2,0,1,B0(Sqr(p),Sqr(MFvm),Sqr(MCha(gI2)))*(Conj(
      CpFvmChaconjUSmPR(gI2,gO2))*CpFvmChaconjUSmPL(gI2,gO1) + Conj(
      CpFvmChaconjUSmPL(gI2,gO2))*CpFvmChaconjUSmPR(gI2,gO1))*MCha(gI2));
   result += SUM(gI2,0,3,(Conj(CpChiFmconjUSmPL(gI2,gO2))*CpChiFmconjUSmPL(gI2,
      gO1) + Conj(CpChiFmconjUSmPR(gI2,gO2))*CpChiFmconjUSmPR(gI2,gO1))*G0(Sqr(p),
      Sqr(MFm),Sqr(MChi(gI2))));
   result += -2*MFm*SUM(gI2,0,3,B0(Sqr(p),Sqr(MFm),Sqr(MChi(gI2)))*(Conj(
      CpChiFmconjUSmPR(gI2,gO2))*CpChiFmconjUSmPL(gI2,gO1) + Conj(CpChiFmconjUSmPL
      (gI2,gO2))*CpChiFmconjUSmPR(gI2,gO1))*MChi(gI2));

   return result * oneOver16PiSqr;

}

Eigen::Matrix<std::complex<double>,2,2> CLASSNAME::self_energy_Sm_1loop(double p) const
{
   Eigen::Matrix<std::complex<double>,2,2> self_energy;

   for (int i = 0; i < 2; i++)
      for (int k = i; k < 2; k++)
         self_energy(i, k) = self_energy_Sm_1loop(p, i, k);

   Hermitianize(self_energy);

   return self_energy;
}

std::complex<double> CLASSNAME::self_energy_Stau_1loop(double p , int gO1, int gO2) const
{
   std::complex<double> result;

   result += -(A0(Sqr(MSveL))*CpSveLUStauconjSveLconjUStau(gO1,gO2));
   result += -(A0(Sqr(MSvmL))*CpSvmLUStauconjSvmLconjUStau(gO1,gO2));
   result += -(A0(Sqr(MSvtL))*CpSvtLUStauconjSvtLconjUStau(gO1,gO2));
   result += 4*A0(Sqr(MVWm))*CpUStauconjUStauconjVWmVWm(gO1,gO2);
   result += 2*A0(Sqr(MVZ))*CpUStauconjUStauVZVZ(gO1,gO2);
   result += Conj(CpSvtLconjUStauVWm(gO2))*CpSvtLconjUStauVWm(gO1)*F0(Sqr(p),
      Sqr(MSvtL),Sqr(MVWm));
   result += -0.5*SUM(gI1,0,1,A0(Sqr(MAh(gI1)))*CpAhAhUStauconjUStau(gI1,gI1,
      gO1,gO2));
   result += -0.5*SUM(gI1,0,1,A0(Sqr(Mhh(gI1)))*CphhhhUStauconjUStau(gI1,gI1,
      gO1,gO2));
   result += -SUM(gI1,0,1,A0(Sqr(MHpm(gI1)))*CpHpmUStauconjHpmconjUStau(gI1,gO1
      ,gI1,gO2));
   result += -3*SUM(gI1,0,1,A0(Sqr(MSb(gI1)))*CpSbUStauconjSbconjUStau(gI1,gO1,
      gI1,gO2));
   result += -3*SUM(gI1,0,1,A0(Sqr(MSc(gI1)))*CpScUStauconjScconjUStau(gI1,gO1,
      gI1,gO2));
   result += -3*SUM(gI1,0,1,A0(Sqr(MSd(gI1)))*CpSdUStauconjSdconjUStau(gI1,gO1,
      gI1,gO2));
   result += -SUM(gI1,0,1,A0(Sqr(MSe(gI1)))*CpSeUStauconjSeconjUStau(gI1,gO1,
      gI1,gO2));
   result += -SUM(gI1,0,1,A0(Sqr(MSm(gI1)))*CpSmUStauconjSmconjUStau(gI1,gO1,
      gI1,gO2));
   result += -3*SUM(gI1,0,1,A0(Sqr(MSs(gI1)))*CpSsUStauconjSsconjUStau(gI1,gO1,
      gI1,gO2));
   result += -SUM(gI1,0,1,A0(Sqr(MStau(gI1)))*CpStauUStauconjStauconjUStau(gI1,
      gO1,gI1,gO2));
   result += -3*SUM(gI1,0,1,A0(Sqr(MSt(gI1)))*CpStUStauconjStconjUStau(gI1,gO1,
      gI1,gO2));
   result += -3*SUM(gI1,0,1,A0(Sqr(MSu(gI1)))*CpUStauSuconjUStauconjSu(gO1,gI1,
      gO2,gI1));
   result += SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(MStau(gI1)),Sqr(MAh(gI2)))*
      Conj(CpAhStauconjUStau(gI2,gI1,gO2))*CpAhStauconjUStau(gI2,gI1,gO1)));
   result += SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(MStau(gI1)),Sqr(Mhh(gI2)))*
      Conj(CphhStauconjUStau(gI2,gI1,gO2))*CphhStauconjUStau(gI2,gI1,gO1)));
   result += SUM(gI2,0,1,B0(Sqr(p),Sqr(MSvtL),Sqr(MHpm(gI2)))*Conj(
      CpSvtLHpmconjUStau(gI2,gO2))*CpSvtLHpmconjUStau(gI2,gO1));
   result += SUM(gI2,0,1,Conj(CpStauconjUStauVP(gI2,gO2))*CpStauconjUStauVP(gI2
      ,gO1)*F0(Sqr(p),Sqr(MStau(gI2)),0));
   result += SUM(gI2,0,1,Conj(CpStauconjUStauVZ(gI2,gO2))*CpStauconjUStauVZ(gI2
      ,gO1)*F0(Sqr(p),Sqr(MStau(gI2)),Sqr(MVZ)));
   result += SUM(gI2,0,1,(Conj(CpFvtChaconjUStauPL(gI2,gO2))*
      CpFvtChaconjUStauPL(gI2,gO1) + Conj(CpFvtChaconjUStauPR(gI2,gO2))*
      CpFvtChaconjUStauPR(gI2,gO1))*G0(Sqr(p),Sqr(MFvt),Sqr(MCha(gI2))));
   result += -2*MFvt*SUM(gI2,0,1,B0(Sqr(p),Sqr(MFvt),Sqr(MCha(gI2)))*(Conj(
      CpFvtChaconjUStauPR(gI2,gO2))*CpFvtChaconjUStauPL(gI2,gO1) + Conj(
      CpFvtChaconjUStauPL(gI2,gO2))*CpFvtChaconjUStauPR(gI2,gO1))*MCha(gI2));
   result += SUM(gI2,0,3,(Conj(CpChiFtauconjUStauPL(gI2,gO2))*
      CpChiFtauconjUStauPL(gI2,gO1) + Conj(CpChiFtauconjUStauPR(gI2,gO2))*
      CpChiFtauconjUStauPR(gI2,gO1))*G0(Sqr(p),Sqr(MFtau),Sqr(MChi(gI2))));
   result += -2*MFtau*SUM(gI2,0,3,B0(Sqr(p),Sqr(MFtau),Sqr(MChi(gI2)))*(Conj(
      CpChiFtauconjUStauPR(gI2,gO2))*CpChiFtauconjUStauPL(gI2,gO1) + Conj(
      CpChiFtauconjUStauPL(gI2,gO2))*CpChiFtauconjUStauPR(gI2,gO1))*MChi(gI2));

   return result * oneOver16PiSqr;

}

Eigen::Matrix<std::complex<double>,2,2> CLASSNAME::self_energy_Stau_1loop(double p) const
{
   Eigen::Matrix<std::complex<double>,2,2> self_energy;

   for (int i = 0; i < 2; i++)
      for (int k = i; k < 2; k++)
         self_energy(i, k) = self_energy_Stau_1loop(p, i, k);

   Hermitianize(self_energy);

   return self_energy;
}

std::complex<double> CLASSNAME::self_energy_Ss_1loop(double p , int gO1, int gO2) const
{
   std::complex<double> result;

   result += -(A0(Sqr(MSveL))*CpSveLUSsconjSveLconjUSs(gO1,gO2));
   result += -(A0(Sqr(MSvmL))*CpSvmLUSsconjSvmLconjUSs(gO1,gO2));
   result += -(A0(Sqr(MSvtL))*CpSvtLUSsconjSvtLconjUSs(gO1,gO2));
   result += 4*A0(Sqr(MVWm))*CpUSsconjUSsconjVWmVWm(gO1,gO2);
   result += 2*A0(Sqr(MVZ))*CpUSsconjUSsVZVZ(gO1,gO2);
   result += 1.3333333333333333*(Conj(CpGluFsconjUSsPL(gO2))*CpGluFsconjUSsPL(
      gO1) + Conj(CpGluFsconjUSsPR(gO2))*CpGluFsconjUSsPR(gO1))*G0(Sqr(p),Sqr(MGlu
      ),Sqr(MFs));
   result += -2.6666666666666665*MFs*MGlu*B0(Sqr(p),Sqr(MGlu),Sqr(MFs))*(Conj(
      CpGluFsconjUSsPR(gO2))*CpGluFsconjUSsPL(gO1) + Conj(CpGluFsconjUSsPL(gO2))*
      CpGluFsconjUSsPR(gO1));
   result += -0.5*SUM(gI1,0,1,A0(Sqr(MAh(gI1)))*CpAhAhUSsconjUSs(gI1,gI1,gO1,
      gO2));
   result += -0.5*SUM(gI1,0,1,A0(Sqr(Mhh(gI1)))*CphhhhUSsconjUSs(gI1,gI1,gO1,
      gO2));
   result += -SUM(gI1,0,1,A0(Sqr(MHpm(gI1)))*CpHpmUSsconjHpmconjUSs(gI1,gO1,gI1
      ,gO2));
   result += -SUM(gI1,0,1,A0(Sqr(MSe(gI1)))*CpSeUSsconjSeconjUSs(gI1,gO1,gI1,
      gO2));
   result += -SUM(gI1,0,1,A0(Sqr(MSm(gI1)))*CpSmUSsconjSmconjUSs(gI1,gO1,gI1,
      gO2));
   result += -SUM(gI1,0,1,A0(Sqr(MSb(gI1)))*CpUSsconjUSsconjSbSb(gO1,gO2,gI1,
      gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MSc(gI1)))*CpUSsconjUSsconjScSc(gO1,gO2,gI1,
      gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MSd(gI1)))*CpUSsconjUSsconjSdSd(gO1,gO2,gI1,
      gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MSs(gI1)))*CpUSsconjUSsconjSsSs(gO1,gO2,gI1,
      gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MSt(gI1)))*CpUSsconjUSsconjStSt(gO1,gO2,gI1,
      gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MSu(gI1)))*CpUSsconjUSsconjSuSu(gO1,gO2,gI1,
      gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MStau(gI1)))*CpUSsStauconjUSsconjStau(gO1,gI1,
      gO2,gI1));
   result += SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(MSs(gI1)),Sqr(MAh(gI2)))*
      Conj(CpAhSsconjUSs(gI2,gI1,gO2))*CpAhSsconjUSs(gI2,gI1,gO1)));
   result += SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(MSs(gI1)),Sqr(Mhh(gI2)))*
      Conj(CphhSsconjUSs(gI2,gI1,gO2))*CphhSsconjUSs(gI2,gI1,gO1)));
   result += SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(MSc(gI1)),Sqr(MHpm(gI2)))*
      Conj(CpHpmScconjUSs(gI2,gI1,gO2))*CpHpmScconjUSs(gI2,gI1,gO1)));
   result += SUM(gI2,0,1,Conj(CpScconjUSsVWm(gI2,gO2))*CpScconjUSsVWm(gI2,gO1)*
      F0(Sqr(p),Sqr(MSc(gI2)),Sqr(MVWm)));
   result += 1.3333333333333333*SUM(gI2,0,1,Conj(CpSsconjUSsVG(gI2,gO2))*
      CpSsconjUSsVG(gI2,gO1)*F0(Sqr(p),Sqr(MSs(gI2)),0));
   result += SUM(gI2,0,1,Conj(CpSsconjUSsVP(gI2,gO2))*CpSsconjUSsVP(gI2,gO1)*F0
      (Sqr(p),Sqr(MSs(gI2)),0));
   result += SUM(gI2,0,1,Conj(CpSsconjUSsVZ(gI2,gO2))*CpSsconjUSsVZ(gI2,gO1)*F0
      (Sqr(p),Sqr(MSs(gI2)),Sqr(MVZ)));
   result += SUM(gI2,0,1,(Conj(CpFcChaconjUSsPL(gI2,gO2))*CpFcChaconjUSsPL(gI2,
      gO1) + Conj(CpFcChaconjUSsPR(gI2,gO2))*CpFcChaconjUSsPR(gI2,gO1))*G0(Sqr(p),
      Sqr(MFc),Sqr(MCha(gI2))));
   result += -2*MFc*SUM(gI2,0,1,B0(Sqr(p),Sqr(MFc),Sqr(MCha(gI2)))*(Conj(
      CpFcChaconjUSsPR(gI2,gO2))*CpFcChaconjUSsPL(gI2,gO1) + Conj(CpFcChaconjUSsPL
      (gI2,gO2))*CpFcChaconjUSsPR(gI2,gO1))*MCha(gI2));
   result += SUM(gI2,0,3,(Conj(CpChiFsconjUSsPL(gI2,gO2))*CpChiFsconjUSsPL(gI2,
      gO1) + Conj(CpChiFsconjUSsPR(gI2,gO2))*CpChiFsconjUSsPR(gI2,gO1))*G0(Sqr(p),
      Sqr(MFs),Sqr(MChi(gI2))));
   result += -2*MFs*SUM(gI2,0,3,B0(Sqr(p),Sqr(MFs),Sqr(MChi(gI2)))*(Conj(
      CpChiFsconjUSsPR(gI2,gO2))*CpChiFsconjUSsPL(gI2,gO1) + Conj(CpChiFsconjUSsPL
      (gI2,gO2))*CpChiFsconjUSsPR(gI2,gO1))*MChi(gI2));

   return result * oneOver16PiSqr;

}

Eigen::Matrix<std::complex<double>,2,2> CLASSNAME::self_energy_Ss_1loop(double p) const
{
   Eigen::Matrix<std::complex<double>,2,2> self_energy;

   for (int i = 0; i < 2; i++)
      for (int k = i; k < 2; k++)
         self_energy(i, k) = self_energy_Ss_1loop(p, i, k);

   Hermitianize(self_energy);

   return self_energy;
}

std::complex<double> CLASSNAME::self_energy_Sc_1loop(double p , int gO1, int gO2) const
{
   std::complex<double> result;

   result += -(A0(Sqr(MSveL))*CpSveLUScconjSveLconjUSc(gO1,gO2));
   result += -(A0(Sqr(MSvmL))*CpSvmLUScconjSvmLconjUSc(gO1,gO2));
   result += -(A0(Sqr(MSvtL))*CpSvtLUScconjSvtLconjUSc(gO1,gO2));
   result += 4*A0(Sqr(MVWm))*CpUScconjUScconjVWmVWm(gO1,gO2);
   result += 2*A0(Sqr(MVZ))*CpUScconjUScVZVZ(gO1,gO2);
   result += 1.3333333333333333*(Conj(CpGluFcconjUScPL(gO2))*CpGluFcconjUScPL(
      gO1) + Conj(CpGluFcconjUScPR(gO2))*CpGluFcconjUScPR(gO1))*G0(Sqr(p),Sqr(MGlu
      ),Sqr(MFc));
   result += -2.6666666666666665*MFc*MGlu*B0(Sqr(p),Sqr(MGlu),Sqr(MFc))*(Conj(
      CpGluFcconjUScPR(gO2))*CpGluFcconjUScPL(gO1) + Conj(CpGluFcconjUScPL(gO2))*
      CpGluFcconjUScPR(gO1));
   result += -0.5*SUM(gI1,0,1,A0(Sqr(MAh(gI1)))*CpAhAhUScconjUSc(gI1,gI1,gO1,
      gO2));
   result += -0.5*SUM(gI1,0,1,A0(Sqr(Mhh(gI1)))*CphhhhUScconjUSc(gI1,gI1,gO1,
      gO2));
   result += -SUM(gI1,0,1,A0(Sqr(MHpm(gI1)))*CpHpmUScconjHpmconjUSc(gI1,gO1,gI1
      ,gO2));
   result += -SUM(gI1,0,1,A0(Sqr(MSb(gI1)))*CpUScconjUScconjSbSb(gO1,gO2,gI1,
      gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MSc(gI1)))*CpUScconjUScconjScSc(gO1,gO2,gI1,
      gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MSd(gI1)))*CpUScconjUScconjSdSd(gO1,gO2,gI1,
      gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MSs(gI1)))*CpUScconjUScconjSsSs(gO1,gO2,gI1,
      gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MSt(gI1)))*CpUScconjUScconjStSt(gO1,gO2,gI1,
      gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MSu(gI1)))*CpUScconjUScconjSuSu(gO1,gO2,gI1,
      gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MSe(gI1)))*CpUScSeconjUScconjSe(gO1,gI1,gO2,
      gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MSm(gI1)))*CpUScSmconjUScconjSm(gO1,gI1,gO2,
      gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MStau(gI1)))*CpUScStauconjUScconjStau(gO1,gI1,
      gO2,gI1));
   result += SUM(gI1,0,1,(Conj(CpbarChaFsconjUScPL(gI1,gO2))*
      CpbarChaFsconjUScPL(gI1,gO1) + Conj(CpbarChaFsconjUScPR(gI1,gO2))*
      CpbarChaFsconjUScPR(gI1,gO1))*G0(Sqr(p),Sqr(MCha(gI1)),Sqr(MFs)));
   result += -2*MFs*SUM(gI1,0,1,B0(Sqr(p),Sqr(MCha(gI1)),Sqr(MFs))*(Conj(
      CpbarChaFsconjUScPR(gI1,gO2))*CpbarChaFsconjUScPL(gI1,gO1) + Conj(
      CpbarChaFsconjUScPL(gI1,gO2))*CpbarChaFsconjUScPR(gI1,gO1))*MCha(gI1));
   result += SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(MSc(gI1)),Sqr(MAh(gI2)))*
      Conj(CpAhScconjUSc(gI2,gI1,gO2))*CpAhScconjUSc(gI2,gI1,gO1)));
   result += SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(MSc(gI1)),Sqr(Mhh(gI2)))*
      Conj(CphhScconjUSc(gI2,gI1,gO2))*CphhScconjUSc(gI2,gI1,gO1)));
   result += SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(MHpm(gI1)),Sqr(MSs(gI2)))*
      Conj(CpSsconjHpmconjUSc(gI2,gI1,gO2))*CpSsconjHpmconjUSc(gI2,gI1,gO1)));
   result += 1.3333333333333333*SUM(gI2,0,1,Conj(CpScconjUScVG(gI2,gO2))*
      CpScconjUScVG(gI2,gO1)*F0(Sqr(p),Sqr(MSc(gI2)),0));
   result += SUM(gI2,0,1,Conj(CpScconjUScVP(gI2,gO2))*CpScconjUScVP(gI2,gO1)*F0
      (Sqr(p),Sqr(MSc(gI2)),0));
   result += SUM(gI2,0,1,Conj(CpScconjUScVZ(gI2,gO2))*CpScconjUScVZ(gI2,gO1)*F0
      (Sqr(p),Sqr(MSc(gI2)),Sqr(MVZ)));
   result += SUM(gI2,0,1,Conj(CpSsconjUScconjVWm(gI2,gO2))*CpSsconjUScconjVWm(
      gI2,gO1)*F0(Sqr(p),Sqr(MSs(gI2)),Sqr(MVWm)));
   result += SUM(gI2,0,3,(Conj(CpChiFcconjUScPL(gI2,gO2))*CpChiFcconjUScPL(gI2,
      gO1) + Conj(CpChiFcconjUScPR(gI2,gO2))*CpChiFcconjUScPR(gI2,gO1))*G0(Sqr(p),
      Sqr(MFc),Sqr(MChi(gI2))));
   result += -2*MFc*SUM(gI2,0,3,B0(Sqr(p),Sqr(MFc),Sqr(MChi(gI2)))*(Conj(
      CpChiFcconjUScPR(gI2,gO2))*CpChiFcconjUScPL(gI2,gO1) + Conj(CpChiFcconjUScPL
      (gI2,gO2))*CpChiFcconjUScPR(gI2,gO1))*MChi(gI2));

   return result * oneOver16PiSqr;

}

Eigen::Matrix<std::complex<double>,2,2> CLASSNAME::self_energy_Sc_1loop(double p) const
{
   Eigen::Matrix<std::complex<double>,2,2> self_energy;

   for (int i = 0; i < 2; i++)
      for (int k = i; k < 2; k++)
         self_energy(i, k) = self_energy_Sc_1loop(p, i, k);

   Hermitianize(self_energy);

   return self_energy;
}

std::complex<double> CLASSNAME::self_energy_Sb_1loop(double p , int gO1, int gO2) const
{
   std::complex<double> result;

   result += -(A0(Sqr(MSveL))*CpSveLUSbconjSveLconjUSb(gO1,gO2));
   result += -(A0(Sqr(MSvmL))*CpSvmLUSbconjSvmLconjUSb(gO1,gO2));
   result += -(A0(Sqr(MSvtL))*CpSvtLUSbconjSvtLconjUSb(gO1,gO2));
   result += 4*A0(Sqr(MVWm))*CpUSbconjUSbconjVWmVWm(gO1,gO2);
   result += 2*A0(Sqr(MVZ))*CpUSbconjUSbVZVZ(gO1,gO2);
   result += 1.3333333333333333*(Conj(CpGluFbconjUSbPL(gO2))*CpGluFbconjUSbPL(
      gO1) + Conj(CpGluFbconjUSbPR(gO2))*CpGluFbconjUSbPR(gO1))*G0(Sqr(p),Sqr(MGlu
      ),Sqr(MFb));
   result += -2.6666666666666665*MFb*MGlu*B0(Sqr(p),Sqr(MGlu),Sqr(MFb))*(Conj(
      CpGluFbconjUSbPR(gO2))*CpGluFbconjUSbPL(gO1) + Conj(CpGluFbconjUSbPL(gO2))*
      CpGluFbconjUSbPR(gO1));
   result += -0.5*SUM(gI1,0,1,A0(Sqr(MAh(gI1)))*CpAhAhUSbconjUSb(gI1,gI1,gO1,
      gO2));
   result += -0.5*SUM(gI1,0,1,A0(Sqr(Mhh(gI1)))*CphhhhUSbconjUSb(gI1,gI1,gO1,
      gO2));
   result += -SUM(gI1,0,1,A0(Sqr(MHpm(gI1)))*CpHpmUSbconjHpmconjUSb(gI1,gO1,gI1
      ,gO2));
   result += -SUM(gI1,0,1,A0(Sqr(MSb(gI1)))*CpUSbconjUSbconjSbSb(gO1,gO2,gI1,
      gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MSc(gI1)))*CpUSbconjUSbconjScSc(gO1,gO2,gI1,
      gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MSd(gI1)))*CpUSbconjUSbconjSdSd(gO1,gO2,gI1,
      gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MSs(gI1)))*CpUSbconjUSbconjSsSs(gO1,gO2,gI1,
      gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MSt(gI1)))*CpUSbconjUSbconjStSt(gO1,gO2,gI1,
      gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MSu(gI1)))*CpUSbconjUSbconjSuSu(gO1,gO2,gI1,
      gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MSe(gI1)))*CpUSbSeconjUSbconjSe(gO1,gI1,gO2,
      gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MSm(gI1)))*CpUSbSmconjUSbconjSm(gO1,gI1,gO2,
      gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MStau(gI1)))*CpUSbStauconjUSbconjStau(gO1,gI1,
      gO2,gI1));
   result += SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(MSb(gI1)),Sqr(MAh(gI2)))*
      Conj(CpAhSbconjUSb(gI2,gI1,gO2))*CpAhSbconjUSb(gI2,gI1,gO1)));
   result += SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(MSb(gI1)),Sqr(Mhh(gI2)))*
      Conj(CphhSbconjUSb(gI2,gI1,gO2))*CphhSbconjUSb(gI2,gI1,gO1)));
   result += SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(MSt(gI1)),Sqr(MHpm(gI2)))*
      Conj(CpHpmStconjUSb(gI2,gI1,gO2))*CpHpmStconjUSb(gI2,gI1,gO1)));
   result += 1.3333333333333333*SUM(gI2,0,1,Conj(CpSbconjUSbVG(gI2,gO2))*
      CpSbconjUSbVG(gI2,gO1)*F0(Sqr(p),Sqr(MSb(gI2)),0));
   result += SUM(gI2,0,1,Conj(CpSbconjUSbVP(gI2,gO2))*CpSbconjUSbVP(gI2,gO1)*F0
      (Sqr(p),Sqr(MSb(gI2)),0));
   result += SUM(gI2,0,1,Conj(CpSbconjUSbVZ(gI2,gO2))*CpSbconjUSbVZ(gI2,gO1)*F0
      (Sqr(p),Sqr(MSb(gI2)),Sqr(MVZ)));
   result += SUM(gI2,0,1,Conj(CpStconjUSbVWm(gI2,gO2))*CpStconjUSbVWm(gI2,gO1)*
      F0(Sqr(p),Sqr(MSt(gI2)),Sqr(MVWm)));
   result += SUM(gI2,0,1,(Conj(CpFtChaconjUSbPL(gI2,gO2))*CpFtChaconjUSbPL(gI2,
      gO1) + Conj(CpFtChaconjUSbPR(gI2,gO2))*CpFtChaconjUSbPR(gI2,gO1))*G0(Sqr(p),
      Sqr(MFt),Sqr(MCha(gI2))));
   result += -2*MFt*SUM(gI2,0,1,B0(Sqr(p),Sqr(MFt),Sqr(MCha(gI2)))*(Conj(
      CpFtChaconjUSbPR(gI2,gO2))*CpFtChaconjUSbPL(gI2,gO1) + Conj(CpFtChaconjUSbPL
      (gI2,gO2))*CpFtChaconjUSbPR(gI2,gO1))*MCha(gI2));
   result += SUM(gI2,0,3,(Conj(CpChiFbconjUSbPL(gI2,gO2))*CpChiFbconjUSbPL(gI2,
      gO1) + Conj(CpChiFbconjUSbPR(gI2,gO2))*CpChiFbconjUSbPR(gI2,gO1))*G0(Sqr(p),
      Sqr(MFb),Sqr(MChi(gI2))));
   result += -2*MFb*SUM(gI2,0,3,B0(Sqr(p),Sqr(MFb),Sqr(MChi(gI2)))*(Conj(
      CpChiFbconjUSbPR(gI2,gO2))*CpChiFbconjUSbPL(gI2,gO1) + Conj(CpChiFbconjUSbPL
      (gI2,gO2))*CpChiFbconjUSbPR(gI2,gO1))*MChi(gI2));

   return result * oneOver16PiSqr;

}

Eigen::Matrix<std::complex<double>,2,2> CLASSNAME::self_energy_Sb_1loop(double p) const
{
   Eigen::Matrix<std::complex<double>,2,2> self_energy;

   for (int i = 0; i < 2; i++)
      for (int k = i; k < 2; k++)
         self_energy(i, k) = self_energy_Sb_1loop(p, i, k);

   Hermitianize(self_energy);

   return self_energy;
}

std::complex<double> CLASSNAME::self_energy_St_1loop(double p , int gO1, int gO2) const
{
   std::complex<double> result;

   result += -(A0(Sqr(MSveL))*CpSveLUStconjSveLconjUSt(gO1,gO2));
   result += -(A0(Sqr(MSvmL))*CpSvmLUStconjSvmLconjUSt(gO1,gO2));
   result += -(A0(Sqr(MSvtL))*CpSvtLUStconjSvtLconjUSt(gO1,gO2));
   result += 4*A0(Sqr(MVWm))*CpUStconjUStconjVWmVWm(gO1,gO2);
   result += 2*A0(Sqr(MVZ))*CpUStconjUStVZVZ(gO1,gO2);
   result += 1.3333333333333333*(Conj(CpGluFtconjUStPL(gO2))*CpGluFtconjUStPL(
      gO1) + Conj(CpGluFtconjUStPR(gO2))*CpGluFtconjUStPR(gO1))*G0(Sqr(p),Sqr(MGlu
      ),Sqr(MFt));
   result += -2.6666666666666665*MFt*MGlu*B0(Sqr(p),Sqr(MGlu),Sqr(MFt))*(Conj(
      CpGluFtconjUStPR(gO2))*CpGluFtconjUStPL(gO1) + Conj(CpGluFtconjUStPL(gO2))*
      CpGluFtconjUStPR(gO1));
   result += -0.5*SUM(gI1,0,1,A0(Sqr(MAh(gI1)))*CpAhAhUStconjUSt(gI1,gI1,gO1,
      gO2));
   result += -0.5*SUM(gI1,0,1,A0(Sqr(Mhh(gI1)))*CphhhhUStconjUSt(gI1,gI1,gO1,
      gO2));
   result += -SUM(gI1,0,1,A0(Sqr(MHpm(gI1)))*CpHpmUStconjHpmconjUSt(gI1,gO1,gI1
      ,gO2));
   result += -SUM(gI1,0,1,A0(Sqr(MSe(gI1)))*CpSeUStconjSeconjUSt(gI1,gO1,gI1,
      gO2));
   result += -SUM(gI1,0,1,A0(Sqr(MSm(gI1)))*CpSmUStconjSmconjUSt(gI1,gO1,gI1,
      gO2));
   result += -SUM(gI1,0,1,A0(Sqr(MSb(gI1)))*CpUStconjUStconjSbSb(gO1,gO2,gI1,
      gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MSc(gI1)))*CpUStconjUStconjScSc(gO1,gO2,gI1,
      gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MSd(gI1)))*CpUStconjUStconjSdSd(gO1,gO2,gI1,
      gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MSs(gI1)))*CpUStconjUStconjSsSs(gO1,gO2,gI1,
      gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MSt(gI1)))*CpUStconjUStconjStSt(gO1,gO2,gI1,
      gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MSu(gI1)))*CpUStconjUStconjSuSu(gO1,gO2,gI1,
      gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MStau(gI1)))*CpUStStauconjUStconjStau(gO1,gI1,
      gO2,gI1));
   result += SUM(gI1,0,1,(Conj(CpbarChaFbconjUStPL(gI1,gO2))*
      CpbarChaFbconjUStPL(gI1,gO1) + Conj(CpbarChaFbconjUStPR(gI1,gO2))*
      CpbarChaFbconjUStPR(gI1,gO1))*G0(Sqr(p),Sqr(MCha(gI1)),Sqr(MFb)));
   result += -2*MFb*SUM(gI1,0,1,B0(Sqr(p),Sqr(MCha(gI1)),Sqr(MFb))*(Conj(
      CpbarChaFbconjUStPR(gI1,gO2))*CpbarChaFbconjUStPL(gI1,gO1) + Conj(
      CpbarChaFbconjUStPL(gI1,gO2))*CpbarChaFbconjUStPR(gI1,gO1))*MCha(gI1));
   result += SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(MSt(gI1)),Sqr(MAh(gI2)))*
      Conj(CpAhStconjUSt(gI2,gI1,gO2))*CpAhStconjUSt(gI2,gI1,gO1)));
   result += SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(MSt(gI1)),Sqr(Mhh(gI2)))*
      Conj(CphhStconjUSt(gI2,gI1,gO2))*CphhStconjUSt(gI2,gI1,gO1)));
   result += SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(MHpm(gI1)),Sqr(MSb(gI2)))*
      Conj(CpSbconjHpmconjUSt(gI2,gI1,gO2))*CpSbconjHpmconjUSt(gI2,gI1,gO1)));
   result += SUM(gI2,0,1,Conj(CpSbconjUStconjVWm(gI2,gO2))*CpSbconjUStconjVWm(
      gI2,gO1)*F0(Sqr(p),Sqr(MSb(gI2)),Sqr(MVWm)));
   result += 1.3333333333333333*SUM(gI2,0,1,Conj(CpStconjUStVG(gI2,gO2))*
      CpStconjUStVG(gI2,gO1)*F0(Sqr(p),Sqr(MSt(gI2)),0));
   result += SUM(gI2,0,1,Conj(CpStconjUStVP(gI2,gO2))*CpStconjUStVP(gI2,gO1)*F0
      (Sqr(p),Sqr(MSt(gI2)),0));
   result += SUM(gI2,0,1,Conj(CpStconjUStVZ(gI2,gO2))*CpStconjUStVZ(gI2,gO1)*F0
      (Sqr(p),Sqr(MSt(gI2)),Sqr(MVZ)));
   result += SUM(gI2,0,3,(Conj(CpChiFtconjUStPL(gI2,gO2))*CpChiFtconjUStPL(gI2,
      gO1) + Conj(CpChiFtconjUStPR(gI2,gO2))*CpChiFtconjUStPR(gI2,gO1))*G0(Sqr(p),
      Sqr(MFt),Sqr(MChi(gI2))));
   result += -2*MFt*SUM(gI2,0,3,B0(Sqr(p),Sqr(MFt),Sqr(MChi(gI2)))*(Conj(
      CpChiFtconjUStPR(gI2,gO2))*CpChiFtconjUStPL(gI2,gO1) + Conj(CpChiFtconjUStPL
      (gI2,gO2))*CpChiFtconjUStPR(gI2,gO1))*MChi(gI2));

   return result * oneOver16PiSqr;

}

Eigen::Matrix<std::complex<double>,2,2> CLASSNAME::self_energy_St_1loop(double p) const
{
   Eigen::Matrix<std::complex<double>,2,2> self_energy;

   for (int i = 0; i < 2; i++)
      for (int k = i; k < 2; k++)
         self_energy(i, k) = self_energy_St_1loop(p, i, k);

   Hermitianize(self_energy);

   return self_energy;
}

std::complex<double> CLASSNAME::self_energy_hh_1loop(double p , int gO1, int gO2) const
{
   std::complex<double> result;

   result += -(B0(Sqr(p),Sqr(MVWm),Sqr(MVWm))*CpbargWmCgWmCUhh(gO1)*
      CpbargWmCgWmCUhh(gO2));
   result += -(B0(Sqr(p),Sqr(MVWm),Sqr(MVWm))*CpbargWmgWmUhh(gO1)*
      CpbargWmgWmUhh(gO2));
   result += -(B0(Sqr(p),Sqr(MVZ),Sqr(MVZ))*CpbargZgZUhh(gO1)*CpbargZgZUhh(gO2)
      );
   result += B0(Sqr(p),Sqr(MSveL),Sqr(MSveL))*Conj(CpSveLUhhconjSveL(gO2))*
      CpSveLUhhconjSveL(gO1);
   result += -(A0(Sqr(MSveL))*CpSveLUhhUhhconjSveL(gO1,gO2));
   result += B0(Sqr(p),Sqr(MSvmL),Sqr(MSvmL))*Conj(CpSvmLUhhconjSvmL(gO2))*
      CpSvmLUhhconjSvmL(gO1);
   result += -(A0(Sqr(MSvmL))*CpSvmLUhhUhhconjSvmL(gO1,gO2));
   result += B0(Sqr(p),Sqr(MSvtL),Sqr(MSvtL))*Conj(CpSvtLUhhconjSvtL(gO2))*
      CpSvtLUhhconjSvtL(gO1);
   result += -(A0(Sqr(MSvtL))*CpSvtLUhhUhhconjSvtL(gO1,gO2));
   result += 4*B0(Sqr(p),Sqr(MVWm),Sqr(MVWm))*Conj(CpUhhconjVWmVWm(gO2))*
      CpUhhconjVWmVWm(gO1);
   result += 4*A0(Sqr(MVWm))*CpUhhUhhconjVWmVWm(gO1,gO2);
   result += 2*A0(Sqr(MVZ))*CpUhhUhhVZVZ(gO1,gO2);
   result += 2*B0(Sqr(p),Sqr(MVZ),Sqr(MVZ))*Conj(CpUhhVZVZ(gO2))*CpUhhVZVZ(gO1)
      ;
   result += 3*(Conj(CpbarFbFbUhhPL(gO2))*CpbarFbFbUhhPL(gO1) + Conj(
      CpbarFbFbUhhPR(gO2))*CpbarFbFbUhhPR(gO1))*G0(Sqr(p),Sqr(MFb),Sqr(MFb));
   result += 3*(Conj(CpbarFcFcUhhPL(gO2))*CpbarFcFcUhhPL(gO1) + Conj(
      CpbarFcFcUhhPR(gO2))*CpbarFcFcUhhPR(gO1))*G0(Sqr(p),Sqr(MFc),Sqr(MFc));
   result += 3*(Conj(CpbarFdFdUhhPL(gO2))*CpbarFdFdUhhPL(gO1) + Conj(
      CpbarFdFdUhhPR(gO2))*CpbarFdFdUhhPR(gO1))*G0(Sqr(p),Sqr(MFd),Sqr(MFd));
   result += (Conj(CpbarFeFeUhhPL(gO2))*CpbarFeFeUhhPL(gO1) + Conj(
      CpbarFeFeUhhPR(gO2))*CpbarFeFeUhhPR(gO1))*G0(Sqr(p),Sqr(MFe),Sqr(MFe));
   result += (Conj(CpbarFmFmUhhPL(gO2))*CpbarFmFmUhhPL(gO1) + Conj(
      CpbarFmFmUhhPR(gO2))*CpbarFmFmUhhPR(gO1))*G0(Sqr(p),Sqr(MFm),Sqr(MFm));
   result += 3*(Conj(CpbarFsFsUhhPL(gO2))*CpbarFsFsUhhPL(gO1) + Conj(
      CpbarFsFsUhhPR(gO2))*CpbarFsFsUhhPR(gO1))*G0(Sqr(p),Sqr(MFs),Sqr(MFs));
   result += 3*(Conj(CpbarFtFtUhhPL(gO2))*CpbarFtFtUhhPL(gO1) + Conj(
      CpbarFtFtUhhPR(gO2))*CpbarFtFtUhhPR(gO1))*G0(Sqr(p),Sqr(MFt),Sqr(MFt));
   result += (Conj(CpbarFtauFtauUhhPL(gO2))*CpbarFtauFtauUhhPL(gO1) + Conj(
      CpbarFtauFtauUhhPR(gO2))*CpbarFtauFtauUhhPR(gO1))*G0(Sqr(p),Sqr(MFtau),Sqr(
      MFtau));
   result += 3*(Conj(CpbarFuFuUhhPL(gO2))*CpbarFuFuUhhPL(gO1) + Conj(
      CpbarFuFuUhhPR(gO2))*CpbarFuFuUhhPR(gO1))*G0(Sqr(p),Sqr(MFu),Sqr(MFu));
   result += -6*B0(Sqr(p),Sqr(MFb),Sqr(MFb))*(Conj(CpbarFbFbUhhPR(gO2))*
      CpbarFbFbUhhPL(gO1) + Conj(CpbarFbFbUhhPL(gO2))*CpbarFbFbUhhPR(gO1))*Sqr(MFb
      );
   result += -6*B0(Sqr(p),Sqr(MFc),Sqr(MFc))*(Conj(CpbarFcFcUhhPR(gO2))*
      CpbarFcFcUhhPL(gO1) + Conj(CpbarFcFcUhhPL(gO2))*CpbarFcFcUhhPR(gO1))*Sqr(MFc
      );
   result += -6*B0(Sqr(p),Sqr(MFd),Sqr(MFd))*(Conj(CpbarFdFdUhhPR(gO2))*
      CpbarFdFdUhhPL(gO1) + Conj(CpbarFdFdUhhPL(gO2))*CpbarFdFdUhhPR(gO1))*Sqr(MFd
      );
   result += -2*B0(Sqr(p),Sqr(MFe),Sqr(MFe))*(Conj(CpbarFeFeUhhPR(gO2))*
      CpbarFeFeUhhPL(gO1) + Conj(CpbarFeFeUhhPL(gO2))*CpbarFeFeUhhPR(gO1))*Sqr(MFe
      );
   result += -2*B0(Sqr(p),Sqr(MFm),Sqr(MFm))*(Conj(CpbarFmFmUhhPR(gO2))*
      CpbarFmFmUhhPL(gO1) + Conj(CpbarFmFmUhhPL(gO2))*CpbarFmFmUhhPR(gO1))*Sqr(MFm
      );
   result += -6*B0(Sqr(p),Sqr(MFs),Sqr(MFs))*(Conj(CpbarFsFsUhhPR(gO2))*
      CpbarFsFsUhhPL(gO1) + Conj(CpbarFsFsUhhPL(gO2))*CpbarFsFsUhhPR(gO1))*Sqr(MFs
      );
   result += -6*B0(Sqr(p),Sqr(MFt),Sqr(MFt))*(Conj(CpbarFtFtUhhPR(gO2))*
      CpbarFtFtUhhPL(gO1) + Conj(CpbarFtFtUhhPL(gO2))*CpbarFtFtUhhPR(gO1))*Sqr(MFt
      );
   result += -2*B0(Sqr(p),Sqr(MFtau),Sqr(MFtau))*(Conj(CpbarFtauFtauUhhPR(gO2))
      *CpbarFtauFtauUhhPL(gO1) + Conj(CpbarFtauFtauUhhPL(gO2))*CpbarFtauFtauUhhPR(
      gO1))*Sqr(MFtau);
   result += -6*B0(Sqr(p),Sqr(MFu),Sqr(MFu))*(Conj(CpbarFuFuUhhPR(gO2))*
      CpbarFuFuUhhPL(gO1) + Conj(CpbarFuFuUhhPL(gO2))*CpbarFuFuUhhPR(gO1))*Sqr(MFu
      );
   result += -0.5*SUM(gI1,0,1,A0(Sqr(MAh(gI1)))*CpAhAhUhhUhh(gI1,gI1,gO1,gO2));
   result += -0.5*SUM(gI1,0,1,A0(Sqr(Mhh(gI1)))*CphhhhUhhUhh(gI1,gI1,gO1,gO2));
   result += -SUM(gI1,0,1,A0(Sqr(MHpm(gI1)))*CpUhhUhhHpmconjHpm(gO1,gO2,gI1,gI1
      ));
   result += -3*SUM(gI1,0,1,A0(Sqr(MSb(gI1)))*CpUhhUhhSbconjSb(gO1,gO2,gI1,gI1)
      );
   result += -3*SUM(gI1,0,1,A0(Sqr(MSc(gI1)))*CpUhhUhhScconjSc(gO1,gO2,gI1,gI1)
      );
   result += -3*SUM(gI1,0,1,A0(Sqr(MSd(gI1)))*CpUhhUhhSdconjSd(gO1,gO2,gI1,gI1)
      );
   result += -SUM(gI1,0,1,A0(Sqr(MSe(gI1)))*CpUhhUhhSeconjSe(gO1,gO2,gI1,gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MSm(gI1)))*CpUhhUhhSmconjSm(gO1,gO2,gI1,gI1));
   result += -3*SUM(gI1,0,1,A0(Sqr(MSs(gI1)))*CpUhhUhhSsconjSs(gO1,gO2,gI1,gI1)
      );
   result += -SUM(gI1,0,1,A0(Sqr(MStau(gI1)))*CpUhhUhhStauconjStau(gO1,gO2,gI1,
      gI1));
   result += -3*SUM(gI1,0,1,A0(Sqr(MSt(gI1)))*CpUhhUhhStconjSt(gO1,gO2,gI1,gI1)
      );
   result += -3*SUM(gI1,0,1,A0(Sqr(MSu(gI1)))*CpUhhUhhSuconjSu(gO1,gO2,gI1,gI1)
      );
   result += 0.5*SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(MAh(gI1)),Sqr(MAh(gI2)))
      *Conj(CpAhAhUhh(gI1,gI2,gO2))*CpAhAhUhh(gI1,gI2,gO1)));
   result += 0.5*SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(Mhh(gI1)),Sqr(Mhh(gI2)))
      *Conj(CphhhhUhh(gI1,gI2,gO2))*CphhhhUhh(gI1,gI2,gO1)));
   result += SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(MHpm(gI1)),Sqr(MHpm(gI2)))*
      Conj(CpUhhHpmconjHpm(gO2,gI2,gI1))*CpUhhHpmconjHpm(gO1,gI2,gI1)));
   result += 3*SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(MSb(gI1)),Sqr(MSb(gI2)))*
      Conj(CpUhhSbconjSb(gO2,gI2,gI1))*CpUhhSbconjSb(gO1,gI2,gI1)));
   result += 3*SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(MSc(gI1)),Sqr(MSc(gI2)))*
      Conj(CpUhhScconjSc(gO2,gI2,gI1))*CpUhhScconjSc(gO1,gI2,gI1)));
   result += 3*SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(MSd(gI1)),Sqr(MSd(gI2)))*
      Conj(CpUhhSdconjSd(gO2,gI2,gI1))*CpUhhSdconjSd(gO1,gI2,gI1)));
   result += SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(MSe(gI1)),Sqr(MSe(gI2)))*
      Conj(CpUhhSeconjSe(gO2,gI2,gI1))*CpUhhSeconjSe(gO1,gI2,gI1)));
   result += SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(MSm(gI1)),Sqr(MSm(gI2)))*
      Conj(CpUhhSmconjSm(gO2,gI2,gI1))*CpUhhSmconjSm(gO1,gI2,gI1)));
   result += 3*SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(MSs(gI1)),Sqr(MSs(gI2)))*
      Conj(CpUhhSsconjSs(gO2,gI2,gI1))*CpUhhSsconjSs(gO1,gI2,gI1)));
   result += SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(MStau(gI1)),Sqr(MStau(gI2)))
      *Conj(CpUhhStauconjStau(gO2,gI2,gI1))*CpUhhStauconjStau(gO1,gI2,gI1)));
   result += 3*SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(MSt(gI1)),Sqr(MSt(gI2)))*
      Conj(CpUhhStconjSt(gO2,gI2,gI1))*CpUhhStconjSt(gO1,gI2,gI1)));
   result += 3*SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(MSu(gI1)),Sqr(MSu(gI2)))*
      Conj(CpUhhSuconjSu(gO2,gI2,gI1))*CpUhhSuconjSu(gO1,gI2,gI1)));
   result += SUM(gI1,0,1,SUM(gI2,0,1,(Conj(CpbarChaChaUhhPL(gI1,gI2,gO2))*
      CpbarChaChaUhhPL(gI1,gI2,gO1) + Conj(CpbarChaChaUhhPR(gI1,gI2,gO2))*
      CpbarChaChaUhhPR(gI1,gI2,gO1))*G0(Sqr(p),Sqr(MCha(gI1)),Sqr(MCha(gI2)))));
   result += -2*SUM(gI1,0,1,MCha(gI1)*SUM(gI2,0,1,B0(Sqr(p),Sqr(MCha(gI1)),Sqr(
      MCha(gI2)))*(Conj(CpbarChaChaUhhPR(gI1,gI2,gO2))*CpbarChaChaUhhPL(gI1,gI2,
      gO1) + Conj(CpbarChaChaUhhPL(gI1,gI2,gO2))*CpbarChaChaUhhPR(gI1,gI2,gO1))*
      MCha(gI2)));
   result += 0.5*SUM(gI1,0,3,SUM(gI2,0,3,(Conj(CpChiChiUhhPL(gI1,gI2,gO2))*
      CpChiChiUhhPL(gI1,gI2,gO1) + Conj(CpChiChiUhhPR(gI1,gI2,gO2))*CpChiChiUhhPR(
      gI1,gI2,gO1))*G0(Sqr(p),Sqr(MChi(gI1)),Sqr(MChi(gI2)))));
   result += -SUM(gI1,0,3,MChi(gI1)*SUM(gI2,0,3,B0(Sqr(p),Sqr(MChi(gI1)),Sqr(
      MChi(gI2)))*(Conj(CpChiChiUhhPR(gI1,gI2,gO2))*CpChiChiUhhPL(gI1,gI2,gO1) +
      Conj(CpChiChiUhhPL(gI1,gI2,gO2))*CpChiChiUhhPR(gI1,gI2,gO1))*MChi(gI2)));
   result += SUM(gI2,0,1,Conj(CpAhUhhVZ(gI2,gO2))*CpAhUhhVZ(gI2,gO1)*F0(Sqr(p),
      Sqr(MAh(gI2)),Sqr(MVZ)));
   result += 2*SUM(gI2,0,1,Conj(CpUhhHpmconjVWm(gO2,gI2))*CpUhhHpmconjVWm(gO1,
      gI2)*F0(Sqr(p),Sqr(MHpm(gI2)),Sqr(MVWm)));

   return result * oneOver16PiSqr;

}

Eigen::Matrix<std::complex<double>,2,2> CLASSNAME::self_energy_hh_1loop(double p) const
{
   Eigen::Matrix<std::complex<double>,2,2> self_energy;

   for (int i = 0; i < 2; i++)
      for (int k = i; k < 2; k++)
         self_energy(i, k) = self_energy_hh_1loop(p, i, k);

   Hermitianize(self_energy);

   return self_energy;
}

std::complex<double> CLASSNAME::self_energy_Ah_1loop(double p , int gO1, int gO2) const
{
   std::complex<double> result;

   result += -(B0(Sqr(p),Sqr(MVWm),Sqr(MVWm))*CpbargWmCgWmCUAh(gO1)*
      CpbargWmCgWmCUAh(gO2));
   result += -(B0(Sqr(p),Sqr(MVWm),Sqr(MVWm))*CpbargWmgWmUAh(gO1)*
      CpbargWmgWmUAh(gO2));
   result += -(A0(Sqr(MSveL))*CpSveLUAhUAhconjSveL(gO1,gO2));
   result += -(A0(Sqr(MSvmL))*CpSvmLUAhUAhconjSvmL(gO1,gO2));
   result += -(A0(Sqr(MSvtL))*CpSvtLUAhUAhconjSvtL(gO1,gO2));
   result += 4*A0(Sqr(MVWm))*CpUAhUAhconjVWmVWm(gO1,gO2);
   result += 2*A0(Sqr(MVZ))*CpUAhUAhVZVZ(gO1,gO2);
   result += 3*(Conj(CpbarFbFbUAhPL(gO2))*CpbarFbFbUAhPL(gO1) + Conj(
      CpbarFbFbUAhPR(gO2))*CpbarFbFbUAhPR(gO1))*G0(Sqr(p),Sqr(MFb),Sqr(MFb));
   result += 3*(Conj(CpbarFcFcUAhPL(gO2))*CpbarFcFcUAhPL(gO1) + Conj(
      CpbarFcFcUAhPR(gO2))*CpbarFcFcUAhPR(gO1))*G0(Sqr(p),Sqr(MFc),Sqr(MFc));
   result += 3*(Conj(CpbarFdFdUAhPL(gO2))*CpbarFdFdUAhPL(gO1) + Conj(
      CpbarFdFdUAhPR(gO2))*CpbarFdFdUAhPR(gO1))*G0(Sqr(p),Sqr(MFd),Sqr(MFd));
   result += (Conj(CpbarFeFeUAhPL(gO2))*CpbarFeFeUAhPL(gO1) + Conj(
      CpbarFeFeUAhPR(gO2))*CpbarFeFeUAhPR(gO1))*G0(Sqr(p),Sqr(MFe),Sqr(MFe));
   result += (Conj(CpbarFmFmUAhPL(gO2))*CpbarFmFmUAhPL(gO1) + Conj(
      CpbarFmFmUAhPR(gO2))*CpbarFmFmUAhPR(gO1))*G0(Sqr(p),Sqr(MFm),Sqr(MFm));
   result += 3*(Conj(CpbarFsFsUAhPL(gO2))*CpbarFsFsUAhPL(gO1) + Conj(
      CpbarFsFsUAhPR(gO2))*CpbarFsFsUAhPR(gO1))*G0(Sqr(p),Sqr(MFs),Sqr(MFs));
   result += 3*(Conj(CpbarFtFtUAhPL(gO2))*CpbarFtFtUAhPL(gO1) + Conj(
      CpbarFtFtUAhPR(gO2))*CpbarFtFtUAhPR(gO1))*G0(Sqr(p),Sqr(MFt),Sqr(MFt));
   result += (Conj(CpbarFtauFtauUAhPL(gO2))*CpbarFtauFtauUAhPL(gO1) + Conj(
      CpbarFtauFtauUAhPR(gO2))*CpbarFtauFtauUAhPR(gO1))*G0(Sqr(p),Sqr(MFtau),Sqr(
      MFtau));
   result += 3*(Conj(CpbarFuFuUAhPL(gO2))*CpbarFuFuUAhPL(gO1) + Conj(
      CpbarFuFuUAhPR(gO2))*CpbarFuFuUAhPR(gO1))*G0(Sqr(p),Sqr(MFu),Sqr(MFu));
   result += -6*B0(Sqr(p),Sqr(MFb),Sqr(MFb))*(Conj(CpbarFbFbUAhPR(gO2))*
      CpbarFbFbUAhPL(gO1) + Conj(CpbarFbFbUAhPL(gO2))*CpbarFbFbUAhPR(gO1))*Sqr(MFb
      );
   result += -6*B0(Sqr(p),Sqr(MFc),Sqr(MFc))*(Conj(CpbarFcFcUAhPR(gO2))*
      CpbarFcFcUAhPL(gO1) + Conj(CpbarFcFcUAhPL(gO2))*CpbarFcFcUAhPR(gO1))*Sqr(MFc
      );
   result += -6*B0(Sqr(p),Sqr(MFd),Sqr(MFd))*(Conj(CpbarFdFdUAhPR(gO2))*
      CpbarFdFdUAhPL(gO1) + Conj(CpbarFdFdUAhPL(gO2))*CpbarFdFdUAhPR(gO1))*Sqr(MFd
      );
   result += -2*B0(Sqr(p),Sqr(MFe),Sqr(MFe))*(Conj(CpbarFeFeUAhPR(gO2))*
      CpbarFeFeUAhPL(gO1) + Conj(CpbarFeFeUAhPL(gO2))*CpbarFeFeUAhPR(gO1))*Sqr(MFe
      );
   result += -2*B0(Sqr(p),Sqr(MFm),Sqr(MFm))*(Conj(CpbarFmFmUAhPR(gO2))*
      CpbarFmFmUAhPL(gO1) + Conj(CpbarFmFmUAhPL(gO2))*CpbarFmFmUAhPR(gO1))*Sqr(MFm
      );
   result += -6*B0(Sqr(p),Sqr(MFs),Sqr(MFs))*(Conj(CpbarFsFsUAhPR(gO2))*
      CpbarFsFsUAhPL(gO1) + Conj(CpbarFsFsUAhPL(gO2))*CpbarFsFsUAhPR(gO1))*Sqr(MFs
      );
   result += -6*B0(Sqr(p),Sqr(MFt),Sqr(MFt))*(Conj(CpbarFtFtUAhPR(gO2))*
      CpbarFtFtUAhPL(gO1) + Conj(CpbarFtFtUAhPL(gO2))*CpbarFtFtUAhPR(gO1))*Sqr(MFt
      );
   result += -2*B0(Sqr(p),Sqr(MFtau),Sqr(MFtau))*(Conj(CpbarFtauFtauUAhPR(gO2))
      *CpbarFtauFtauUAhPL(gO1) + Conj(CpbarFtauFtauUAhPL(gO2))*CpbarFtauFtauUAhPR(
      gO1))*Sqr(MFtau);
   result += -6*B0(Sqr(p),Sqr(MFu),Sqr(MFu))*(Conj(CpbarFuFuUAhPR(gO2))*
      CpbarFuFuUAhPL(gO1) + Conj(CpbarFuFuUAhPL(gO2))*CpbarFuFuUAhPR(gO1))*Sqr(MFu
      );
   result += -0.5*SUM(gI1,0,1,A0(Sqr(MAh(gI1)))*CpAhAhUAhUAh(gI1,gI1,gO1,gO2));
   result += -0.5*SUM(gI1,0,1,A0(Sqr(Mhh(gI1)))*CpUAhUAhhhhh(gO1,gO2,gI1,gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MHpm(gI1)))*CpUAhUAhHpmconjHpm(gO1,gO2,gI1,gI1
      ));
   result += -3*SUM(gI1,0,1,A0(Sqr(MSb(gI1)))*CpUAhUAhSbconjSb(gO1,gO2,gI1,gI1)
      );
   result += -3*SUM(gI1,0,1,A0(Sqr(MSc(gI1)))*CpUAhUAhScconjSc(gO1,gO2,gI1,gI1)
      );
   result += -3*SUM(gI1,0,1,A0(Sqr(MSd(gI1)))*CpUAhUAhSdconjSd(gO1,gO2,gI1,gI1)
      );
   result += -SUM(gI1,0,1,A0(Sqr(MSe(gI1)))*CpUAhUAhSeconjSe(gO1,gO2,gI1,gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MSm(gI1)))*CpUAhUAhSmconjSm(gO1,gO2,gI1,gI1));
   result += -3*SUM(gI1,0,1,A0(Sqr(MSs(gI1)))*CpUAhUAhSsconjSs(gO1,gO2,gI1,gI1)
      );
   result += -SUM(gI1,0,1,A0(Sqr(MStau(gI1)))*CpUAhUAhStauconjStau(gO1,gO2,gI1,
      gI1));
   result += -3*SUM(gI1,0,1,A0(Sqr(MSt(gI1)))*CpUAhUAhStconjSt(gO1,gO2,gI1,gI1)
      );
   result += -3*SUM(gI1,0,1,A0(Sqr(MSu(gI1)))*CpUAhUAhSuconjSu(gO1,gO2,gI1,gI1)
      );
   result += SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(Mhh(gI1)),Sqr(MAh(gI2)))*
      Conj(CpAhUAhhh(gI2,gO2,gI1))*CpAhUAhhh(gI2,gO1,gI1)));
   result += SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(MHpm(gI1)),Sqr(MHpm(gI2)))*
      Conj(CpUAhHpmconjHpm(gO2,gI2,gI1))*CpUAhHpmconjHpm(gO1,gI2,gI1)));
   result += 3*SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(MSb(gI1)),Sqr(MSb(gI2)))*
      Conj(CpUAhSbconjSb(gO2,gI2,gI1))*CpUAhSbconjSb(gO1,gI2,gI1)));
   result += 3*SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(MSc(gI1)),Sqr(MSc(gI2)))*
      Conj(CpUAhScconjSc(gO2,gI2,gI1))*CpUAhScconjSc(gO1,gI2,gI1)));
   result += 3*SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(MSd(gI1)),Sqr(MSd(gI2)))*
      Conj(CpUAhSdconjSd(gO2,gI2,gI1))*CpUAhSdconjSd(gO1,gI2,gI1)));
   result += SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(MSe(gI1)),Sqr(MSe(gI2)))*
      Conj(CpUAhSeconjSe(gO2,gI2,gI1))*CpUAhSeconjSe(gO1,gI2,gI1)));
   result += SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(MSm(gI1)),Sqr(MSm(gI2)))*
      Conj(CpUAhSmconjSm(gO2,gI2,gI1))*CpUAhSmconjSm(gO1,gI2,gI1)));
   result += 3*SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(MSs(gI1)),Sqr(MSs(gI2)))*
      Conj(CpUAhSsconjSs(gO2,gI2,gI1))*CpUAhSsconjSs(gO1,gI2,gI1)));
   result += SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(MStau(gI1)),Sqr(MStau(gI2)))
      *Conj(CpUAhStauconjStau(gO2,gI2,gI1))*CpUAhStauconjStau(gO1,gI2,gI1)));
   result += 3*SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(MSt(gI1)),Sqr(MSt(gI2)))*
      Conj(CpUAhStconjSt(gO2,gI2,gI1))*CpUAhStconjSt(gO1,gI2,gI1)));
   result += 3*SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(MSu(gI1)),Sqr(MSu(gI2)))*
      Conj(CpUAhSuconjSu(gO2,gI2,gI1))*CpUAhSuconjSu(gO1,gI2,gI1)));
   result += SUM(gI1,0,1,SUM(gI2,0,1,(Conj(CpbarChaChaUAhPL(gI1,gI2,gO2))*
      CpbarChaChaUAhPL(gI1,gI2,gO1) + Conj(CpbarChaChaUAhPR(gI1,gI2,gO2))*
      CpbarChaChaUAhPR(gI1,gI2,gO1))*G0(Sqr(p),Sqr(MCha(gI1)),Sqr(MCha(gI2)))));
   result += -2*SUM(gI1,0,1,MCha(gI1)*SUM(gI2,0,1,B0(Sqr(p),Sqr(MCha(gI1)),Sqr(
      MCha(gI2)))*(Conj(CpbarChaChaUAhPR(gI1,gI2,gO2))*CpbarChaChaUAhPL(gI1,gI2,
      gO1) + Conj(CpbarChaChaUAhPL(gI1,gI2,gO2))*CpbarChaChaUAhPR(gI1,gI2,gO1))*
      MCha(gI2)));
   result += 0.5*SUM(gI1,0,3,SUM(gI2,0,3,(Conj(CpChiChiUAhPL(gI1,gI2,gO2))*
      CpChiChiUAhPL(gI1,gI2,gO1) + Conj(CpChiChiUAhPR(gI1,gI2,gO2))*CpChiChiUAhPR(
      gI1,gI2,gO1))*G0(Sqr(p),Sqr(MChi(gI1)),Sqr(MChi(gI2)))));
   result += -SUM(gI1,0,3,MChi(gI1)*SUM(gI2,0,3,B0(Sqr(p),Sqr(MChi(gI1)),Sqr(
      MChi(gI2)))*(Conj(CpChiChiUAhPR(gI1,gI2,gO2))*CpChiChiUAhPL(gI1,gI2,gO1) +
      Conj(CpChiChiUAhPL(gI1,gI2,gO2))*CpChiChiUAhPR(gI1,gI2,gO1))*MChi(gI2)));
   result += SUM(gI2,0,1,Conj(CpUAhhhVZ(gO2,gI2))*CpUAhhhVZ(gO1,gI2)*F0(Sqr(p),
      Sqr(Mhh(gI2)),Sqr(MVZ)));
   result += 2*SUM(gI2,0,1,Conj(CpUAhHpmconjVWm(gO2,gI2))*CpUAhHpmconjVWm(gO1,
      gI2)*F0(Sqr(p),Sqr(MHpm(gI2)),Sqr(MVWm)));

   return result * oneOver16PiSqr;

}

Eigen::Matrix<std::complex<double>,2,2> CLASSNAME::self_energy_Ah_1loop(double p) const
{
   Eigen::Matrix<std::complex<double>,2,2> self_energy;

   for (int i = 0; i < 2; i++)
      for (int k = i; k < 2; k++)
         self_energy(i, k) = self_energy_Ah_1loop(p, i, k);

   Hermitianize(self_energy);

   return self_energy;
}

std::complex<double> CLASSNAME::self_energy_Hpm_1loop(double p , int gO1, int gO2) const
{
   std::complex<double> result;

   result += -(B0(Sqr(p),Sqr(MVWm),Sqr(MVZ))*CpbargWmgZUHpm(gO2)*
      CpbargZgWmconjUHpm(gO1));
   result += -(B0(Sqr(p),Sqr(MVZ),Sqr(MVWm))*CpbargWmCgZconjUHpm(gO1)*
      CpbargZgWmCUHpm(gO2));
   result += 4*B0(Sqr(p),0,Sqr(MVWm))*Conj(CpconjUHpmVPVWm(gO2))*
      CpconjUHpmVPVWm(gO1);
   result += 4*B0(Sqr(p),Sqr(MVWm),Sqr(MVZ))*Conj(CpconjUHpmVWmVZ(gO2))*
      CpconjUHpmVWmVZ(gO1);
   result += -(A0(Sqr(MSveL))*CpSveLUHpmconjSveLconjUHpm(gO1,gO2));
   result += -(A0(Sqr(MSvmL))*CpSvmLUHpmconjSvmLconjUHpm(gO1,gO2));
   result += -(A0(Sqr(MSvtL))*CpSvtLUHpmconjSvtLconjUHpm(gO1,gO2));
   result += 4*A0(Sqr(MVWm))*CpUHpmconjUHpmconjVWmVWm(gO1,gO2);
   result += 2*A0(Sqr(MVZ))*CpUHpmconjUHpmVZVZ(gO1,gO2);
   result += 3*(Conj(CpbarFcFsconjUHpmPL(gO2))*CpbarFcFsconjUHpmPL(gO1) + Conj(
      CpbarFcFsconjUHpmPR(gO2))*CpbarFcFsconjUHpmPR(gO1))*G0(Sqr(p),Sqr(MFc),Sqr(
      MFs));
   result += 3*(Conj(CpbarFtFbconjUHpmPL(gO2))*CpbarFtFbconjUHpmPL(gO1) + Conj(
      CpbarFtFbconjUHpmPR(gO2))*CpbarFtFbconjUHpmPR(gO1))*G0(Sqr(p),Sqr(MFt),Sqr(
      MFb));
   result += 3*(Conj(CpbarFuFdconjUHpmPL(gO2))*CpbarFuFdconjUHpmPL(gO1) + Conj(
      CpbarFuFdconjUHpmPR(gO2))*CpbarFuFdconjUHpmPR(gO1))*G0(Sqr(p),Sqr(MFu),Sqr(
      MFd));
   result += (Conj(CpbarFveFeconjUHpmPL(gO2))*CpbarFveFeconjUHpmPL(gO1) + Conj(
      CpbarFveFeconjUHpmPR(gO2))*CpbarFveFeconjUHpmPR(gO1))*G0(Sqr(p),Sqr(MFve),
      Sqr(MFe));
   result += (Conj(CpbarFvmFmconjUHpmPL(gO2))*CpbarFvmFmconjUHpmPL(gO1) + Conj(
      CpbarFvmFmconjUHpmPR(gO2))*CpbarFvmFmconjUHpmPR(gO1))*G0(Sqr(p),Sqr(MFvm),
      Sqr(MFm));
   result += (Conj(CpbarFvtFtauconjUHpmPL(gO2))*CpbarFvtFtauconjUHpmPL(gO1) +
      Conj(CpbarFvtFtauconjUHpmPR(gO2))*CpbarFvtFtauconjUHpmPR(gO1))*G0(Sqr(p),Sqr
      (MFvt),Sqr(MFtau));
   result += -6*MFc*MFs*B0(Sqr(p),Sqr(MFc),Sqr(MFs))*(Conj(CpbarFcFsconjUHpmPR(
      gO2))*CpbarFcFsconjUHpmPL(gO1) + Conj(CpbarFcFsconjUHpmPL(gO2))*
      CpbarFcFsconjUHpmPR(gO1));
   result += -6*MFb*MFt*B0(Sqr(p),Sqr(MFt),Sqr(MFb))*(Conj(CpbarFtFbconjUHpmPR(
      gO2))*CpbarFtFbconjUHpmPL(gO1) + Conj(CpbarFtFbconjUHpmPL(gO2))*
      CpbarFtFbconjUHpmPR(gO1));
   result += -6*MFd*MFu*B0(Sqr(p),Sqr(MFu),Sqr(MFd))*(Conj(CpbarFuFdconjUHpmPR(
      gO2))*CpbarFuFdconjUHpmPL(gO1) + Conj(CpbarFuFdconjUHpmPL(gO2))*
      CpbarFuFdconjUHpmPR(gO1));
   result += -2*MFe*MFve*B0(Sqr(p),Sqr(MFve),Sqr(MFe))*(Conj(
      CpbarFveFeconjUHpmPR(gO2))*CpbarFveFeconjUHpmPL(gO1) + Conj(
      CpbarFveFeconjUHpmPL(gO2))*CpbarFveFeconjUHpmPR(gO1));
   result += -2*MFm*MFvm*B0(Sqr(p),Sqr(MFvm),Sqr(MFm))*(Conj(
      CpbarFvmFmconjUHpmPR(gO2))*CpbarFvmFmconjUHpmPL(gO1) + Conj(
      CpbarFvmFmconjUHpmPL(gO2))*CpbarFvmFmconjUHpmPR(gO1));
   result += -2*MFtau*MFvt*B0(Sqr(p),Sqr(MFvt),Sqr(MFtau))*(Conj(
      CpbarFvtFtauconjUHpmPR(gO2))*CpbarFvtFtauconjUHpmPL(gO1) + Conj(
      CpbarFvtFtauconjUHpmPL(gO2))*CpbarFvtFtauconjUHpmPR(gO1));
   result += -0.5*SUM(gI1,0,1,A0(Sqr(MAh(gI1)))*CpAhAhUHpmconjUHpm(gI1,gI1,gO1,
      gO2));
   result += -0.5*SUM(gI1,0,1,A0(Sqr(Mhh(gI1)))*CphhhhUHpmconjUHpm(gI1,gI1,gO1,
      gO2));
   result += -SUM(gI1,0,1,A0(Sqr(MHpm(gI1)))*CpHpmUHpmconjHpmconjUHpm(gI1,gO1,
      gI1,gO2));
   result += -3*SUM(gI1,0,1,A0(Sqr(MSb(gI1)))*CpUHpmSbconjUHpmconjSb(gO1,gI1,
      gO2,gI1));
   result += -3*SUM(gI1,0,1,A0(Sqr(MSc(gI1)))*CpUHpmScconjUHpmconjSc(gO1,gI1,
      gO2,gI1));
   result += -3*SUM(gI1,0,1,A0(Sqr(MSd(gI1)))*CpUHpmSdconjUHpmconjSd(gO1,gI1,
      gO2,gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MSe(gI1)))*CpUHpmSeconjUHpmconjSe(gO1,gI1,gO2,
      gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MSm(gI1)))*CpUHpmSmconjUHpmconjSm(gO1,gI1,gO2,
      gI1));
   result += -3*SUM(gI1,0,1,A0(Sqr(MSs(gI1)))*CpUHpmSsconjUHpmconjSs(gO1,gI1,
      gO2,gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MStau(gI1)))*CpUHpmStauconjUHpmconjStau(gO1,
      gI1,gO2,gI1));
   result += -3*SUM(gI1,0,1,A0(Sqr(MSt(gI1)))*CpUHpmStconjUHpmconjSt(gO1,gI1,
      gO2,gI1));
   result += -3*SUM(gI1,0,1,A0(Sqr(MSu(gI1)))*CpUHpmSuconjUHpmconjSu(gO1,gI1,
      gO2,gI1));
   result += SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(MHpm(gI1)),Sqr(MAh(gI2)))*
      Conj(CpAhHpmconjUHpm(gI2,gI1,gO2))*CpAhHpmconjUHpm(gI2,gI1,gO1)));
   result += SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(MHpm(gI1)),Sqr(Mhh(gI2)))*
      Conj(CphhHpmconjUHpm(gI2,gI1,gO2))*CphhHpmconjUHpm(gI2,gI1,gO1)));
   result += 3*SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(MSt(gI1)),Sqr(MSb(gI2)))*
      Conj(CpSbconjUHpmconjSt(gI2,gO2,gI1))*CpSbconjUHpmconjSt(gI2,gO1,gI1)));
   result += 3*SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(MSu(gI1)),Sqr(MSd(gI2)))*
      Conj(CpSdconjUHpmconjSu(gI2,gO2,gI1))*CpSdconjUHpmconjSu(gI2,gO1,gI1)));
   result += 3*SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(MSc(gI1)),Sqr(MSs(gI2)))*
      Conj(CpSsconjUHpmconjSc(gI2,gO2,gI1))*CpSsconjUHpmconjSc(gI2,gO1,gI1)));
   result += SUM(gI1,0,3,SUM(gI2,0,1,(Conj(CpChiChaconjUHpmPL(gI1,gI2,gO2))*
      CpChiChaconjUHpmPL(gI1,gI2,gO1) + Conj(CpChiChaconjUHpmPR(gI1,gI2,gO2))*
      CpChiChaconjUHpmPR(gI1,gI2,gO1))*G0(Sqr(p),Sqr(MChi(gI1)),Sqr(MCha(gI2)))));
   result += -2*SUM(gI1,0,3,MChi(gI1)*SUM(gI2,0,1,B0(Sqr(p),Sqr(MChi(gI1)),Sqr(
      MCha(gI2)))*(Conj(CpChiChaconjUHpmPR(gI1,gI2,gO2))*CpChiChaconjUHpmPL(gI1,
      gI2,gO1) + Conj(CpChiChaconjUHpmPL(gI1,gI2,gO2))*CpChiChaconjUHpmPR(gI1,gI2,
      gO1))*MCha(gI2)));
   result += SUM(gI2,0,1,B0(Sqr(p),Sqr(MSveL),Sqr(MSe(gI2)))*Conj(
      CpSeconjSveLconjUHpm(gI2,gO2))*CpSeconjSveLconjUHpm(gI2,gO1));
   result += SUM(gI2,0,1,B0(Sqr(p),Sqr(MSvmL),Sqr(MSm(gI2)))*Conj(
      CpSmconjSvmLconjUHpm(gI2,gO2))*CpSmconjSvmLconjUHpm(gI2,gO1));
   result += SUM(gI2,0,1,B0(Sqr(p),Sqr(MSvtL),Sqr(MStau(gI2)))*Conj(
      CpStauconjSvtLconjUHpm(gI2,gO2))*CpStauconjSvtLconjUHpm(gI2,gO1));
   result += SUM(gI2,0,1,Conj(CpAhconjUHpmVWm(gI2,gO2))*CpAhconjUHpmVWm(gI2,gO1
      )*F0(Sqr(p),Sqr(MAh(gI2)),Sqr(MVWm)));
   result += SUM(gI2,0,1,Conj(CphhconjUHpmVWm(gI2,gO2))*CphhconjUHpmVWm(gI2,gO1
      )*F0(Sqr(p),Sqr(Mhh(gI2)),Sqr(MVWm)));
   result += SUM(gI2,0,1,Conj(CpHpmconjUHpmVP(gI2,gO2))*CpHpmconjUHpmVP(gI2,gO1
      )*F0(Sqr(p),Sqr(MHpm(gI2)),0));
   result += SUM(gI2,0,1,Conj(CpHpmconjUHpmVZ(gI2,gO2))*CpHpmconjUHpmVZ(gI2,gO1
      )*F0(Sqr(p),Sqr(MHpm(gI2)),Sqr(MVZ)));

   return result * oneOver16PiSqr;

}

Eigen::Matrix<std::complex<double>,2,2> CLASSNAME::self_energy_Hpm_1loop(double p) const
{
   Eigen::Matrix<std::complex<double>,2,2> self_energy;

   for (int i = 0; i < 2; i++)
      for (int k = i; k < 2; k++)
         self_energy(i, k) = self_energy_Hpm_1loop(p, i, k);

   Hermitianize(self_energy);

   return self_energy;
}

std::complex<double> CLASSNAME::self_energy_SveL_1loop(double p ) const
{
   std::complex<double> result;

   result += 4*A0(Sqr(MVWm))*CpSveLconjSveLconjVWmVWm();
   result += 2*A0(Sqr(MVZ))*CpSveLconjSveLVZVZ();
   result += -(A0(Sqr(MSveL))*CpSveLSveLconjSveLconjSveL());
   result += -(A0(Sqr(MSvmL))*CpSveLSvmLconjSveLconjSvmL());
   result += -(A0(Sqr(MSvtL))*CpSveLSvtLconjSveLconjSvtL());
   result += AbsSqr(CpSveLconjSveLVZ())*F0(Sqr(p),Sqr(MSveL),Sqr(MVZ));
   result += -0.5*SUM(gI1,0,1,A0(Sqr(MAh(gI1)))*CpSveLAhAhconjSveL(gI1,gI1));
   result += -0.5*SUM(gI1,0,1,A0(Sqr(Mhh(gI1)))*CpSveLhhhhconjSveL(gI1,gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MHpm(gI1)))*CpSveLHpmconjSveLconjHpm(gI1,gI1))
      ;
   result += -3*SUM(gI1,0,1,A0(Sqr(MSb(gI1)))*CpSveLSbconjSveLconjSb(gI1,gI1));
   result += -3*SUM(gI1,0,1,A0(Sqr(MSc(gI1)))*CpSveLScconjSveLconjSc(gI1,gI1));
   result += -3*SUM(gI1,0,1,A0(Sqr(MSd(gI1)))*CpSveLSdconjSveLconjSd(gI1,gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MSe(gI1)))*CpSveLSeconjSveLconjSe(gI1,gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MSm(gI1)))*CpSveLSmconjSveLconjSm(gI1,gI1));
   result += -3*SUM(gI1,0,1,A0(Sqr(MSs(gI1)))*CpSveLSsconjSveLconjSs(gI1,gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MStau(gI1)))*CpSveLStauconjSveLconjStau(gI1,
      gI1));
   result += -3*SUM(gI1,0,1,A0(Sqr(MSt(gI1)))*CpSveLStconjSveLconjSt(gI1,gI1));
   result += -3*SUM(gI1,0,1,A0(Sqr(MSu(gI1)))*CpSveLSuconjSveLconjSu(gI1,gI1));
   result += SUM(gI1,0,1,(AbsSqr(CpbarChaFeconjSveLPL(gI1)) + AbsSqr(
      CpbarChaFeconjSveLPR(gI1)))*G0(Sqr(p),Sqr(MCha(gI1)),Sqr(MFe)));
   result += -2*MFe*SUM(gI1,0,1,B0(Sqr(p),Sqr(MCha(gI1)),Sqr(MFe))*(Conj(
      CpbarChaFeconjSveLPR(gI1))*CpbarChaFeconjSveLPL(gI1) + Conj(
      CpbarChaFeconjSveLPL(gI1))*CpbarChaFeconjSveLPR(gI1))*MCha(gI1));
   result += SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpSeconjSveLconjHpm(gI2,gI1))*B0(
      Sqr(p),Sqr(MHpm(gI1)),Sqr(MSe(gI2)))));
   result += SUM(gI2,0,1,AbsSqr(CpSveLhhconjSveL(gI2))*B0(Sqr(p),Sqr(MSveL),Sqr
      (Mhh(gI2))));
   result += SUM(gI2,0,1,AbsSqr(CpSeconjSveLconjVWm(gI2))*F0(Sqr(p),Sqr(MSe(gI2
      )),Sqr(MVWm)));
   result += SUM(gI2,0,3,(AbsSqr(CpChiFveconjSveLPL(gI2)) + AbsSqr(
      CpChiFveconjSveLPR(gI2)))*G0(Sqr(p),Sqr(MFve),Sqr(MChi(gI2))));
   result += -2*MFve*SUM(gI2,0,3,B0(Sqr(p),Sqr(MFve),Sqr(MChi(gI2)))*(Conj(
      CpChiFveconjSveLPR(gI2))*CpChiFveconjSveLPL(gI2) + Conj(CpChiFveconjSveLPL(
      gI2))*CpChiFveconjSveLPR(gI2))*MChi(gI2));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_SvmL_1loop(double p ) const
{
   std::complex<double> result;

   result += -(A0(Sqr(MSveL))*CpSveLSvmLconjSveLconjSvmL());
   result += 4*A0(Sqr(MVWm))*CpSvmLconjSvmLconjVWmVWm();
   result += 2*A0(Sqr(MVZ))*CpSvmLconjSvmLVZVZ();
   result += -(A0(Sqr(MSvmL))*CpSvmLSvmLconjSvmLconjSvmL());
   result += -(A0(Sqr(MSvtL))*CpSvmLSvtLconjSvmLconjSvtL());
   result += AbsSqr(CpSvmLconjSvmLVZ())*F0(Sqr(p),Sqr(MSvmL),Sqr(MVZ));
   result += -0.5*SUM(gI1,0,1,A0(Sqr(MAh(gI1)))*CpSvmLAhAhconjSvmL(gI1,gI1));
   result += -0.5*SUM(gI1,0,1,A0(Sqr(Mhh(gI1)))*CpSvmLhhhhconjSvmL(gI1,gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MHpm(gI1)))*CpSvmLHpmconjSvmLconjHpm(gI1,gI1))
      ;
   result += -3*SUM(gI1,0,1,A0(Sqr(MSb(gI1)))*CpSvmLSbconjSvmLconjSb(gI1,gI1));
   result += -3*SUM(gI1,0,1,A0(Sqr(MSc(gI1)))*CpSvmLScconjSvmLconjSc(gI1,gI1));
   result += -3*SUM(gI1,0,1,A0(Sqr(MSd(gI1)))*CpSvmLSdconjSvmLconjSd(gI1,gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MSe(gI1)))*CpSvmLSeconjSvmLconjSe(gI1,gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MSm(gI1)))*CpSvmLSmconjSvmLconjSm(gI1,gI1));
   result += -3*SUM(gI1,0,1,A0(Sqr(MSs(gI1)))*CpSvmLSsconjSvmLconjSs(gI1,gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MStau(gI1)))*CpSvmLStauconjSvmLconjStau(gI1,
      gI1));
   result += -3*SUM(gI1,0,1,A0(Sqr(MSt(gI1)))*CpSvmLStconjSvmLconjSt(gI1,gI1));
   result += -3*SUM(gI1,0,1,A0(Sqr(MSu(gI1)))*CpSvmLSuconjSvmLconjSu(gI1,gI1));
   result += SUM(gI1,0,1,(AbsSqr(CpbarChaFmconjSvmLPL(gI1)) + AbsSqr(
      CpbarChaFmconjSvmLPR(gI1)))*G0(Sqr(p),Sqr(MCha(gI1)),Sqr(MFm)));
   result += -2*MFm*SUM(gI1,0,1,B0(Sqr(p),Sqr(MCha(gI1)),Sqr(MFm))*(Conj(
      CpbarChaFmconjSvmLPR(gI1))*CpbarChaFmconjSvmLPL(gI1) + Conj(
      CpbarChaFmconjSvmLPL(gI1))*CpbarChaFmconjSvmLPR(gI1))*MCha(gI1));
   result += SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpSmconjSvmLconjHpm(gI2,gI1))*B0(
      Sqr(p),Sqr(MHpm(gI1)),Sqr(MSm(gI2)))));
   result += SUM(gI2,0,1,AbsSqr(CpSvmLhhconjSvmL(gI2))*B0(Sqr(p),Sqr(MSvmL),Sqr
      (Mhh(gI2))));
   result += SUM(gI2,0,1,AbsSqr(CpSmconjSvmLconjVWm(gI2))*F0(Sqr(p),Sqr(MSm(gI2
      )),Sqr(MVWm)));
   result += SUM(gI2,0,3,(AbsSqr(CpChiFvmconjSvmLPL(gI2)) + AbsSqr(
      CpChiFvmconjSvmLPR(gI2)))*G0(Sqr(p),Sqr(MFvm),Sqr(MChi(gI2))));
   result += -2*MFvm*SUM(gI2,0,3,B0(Sqr(p),Sqr(MFvm),Sqr(MChi(gI2)))*(Conj(
      CpChiFvmconjSvmLPR(gI2))*CpChiFvmconjSvmLPL(gI2) + Conj(CpChiFvmconjSvmLPL(
      gI2))*CpChiFvmconjSvmLPR(gI2))*MChi(gI2));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_SvtL_1loop(double p ) const
{
   std::complex<double> result;

   result += -(A0(Sqr(MSveL))*CpSveLSvtLconjSveLconjSvtL());
   result += -(A0(Sqr(MSvmL))*CpSvmLSvtLconjSvmLconjSvtL());
   result += 4*A0(Sqr(MVWm))*CpSvtLconjSvtLconjVWmVWm();
   result += 2*A0(Sqr(MVZ))*CpSvtLconjSvtLVZVZ();
   result += -(A0(Sqr(MSvtL))*CpSvtLSvtLconjSvtLconjSvtL());
   result += AbsSqr(CpSvtLconjSvtLVZ())*F0(Sqr(p),Sqr(MSvtL),Sqr(MVZ));
   result += -0.5*SUM(gI1,0,1,A0(Sqr(MAh(gI1)))*CpSvtLAhAhconjSvtL(gI1,gI1));
   result += -0.5*SUM(gI1,0,1,A0(Sqr(Mhh(gI1)))*CpSvtLhhhhconjSvtL(gI1,gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MHpm(gI1)))*CpSvtLHpmconjSvtLconjHpm(gI1,gI1))
      ;
   result += -3*SUM(gI1,0,1,A0(Sqr(MSb(gI1)))*CpSvtLSbconjSvtLconjSb(gI1,gI1));
   result += -3*SUM(gI1,0,1,A0(Sqr(MSc(gI1)))*CpSvtLScconjSvtLconjSc(gI1,gI1));
   result += -3*SUM(gI1,0,1,A0(Sqr(MSd(gI1)))*CpSvtLSdconjSvtLconjSd(gI1,gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MSe(gI1)))*CpSvtLSeconjSvtLconjSe(gI1,gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MSm(gI1)))*CpSvtLSmconjSvtLconjSm(gI1,gI1));
   result += -3*SUM(gI1,0,1,A0(Sqr(MSs(gI1)))*CpSvtLSsconjSvtLconjSs(gI1,gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MStau(gI1)))*CpSvtLStauconjSvtLconjStau(gI1,
      gI1));
   result += -3*SUM(gI1,0,1,A0(Sqr(MSt(gI1)))*CpSvtLStconjSvtLconjSt(gI1,gI1));
   result += -3*SUM(gI1,0,1,A0(Sqr(MSu(gI1)))*CpSvtLSuconjSvtLconjSu(gI1,gI1));
   result += SUM(gI1,0,1,(AbsSqr(CpbarChaFtauconjSvtLPL(gI1)) + AbsSqr(
      CpbarChaFtauconjSvtLPR(gI1)))*G0(Sqr(p),Sqr(MCha(gI1)),Sqr(MFtau)));
   result += -2*MFtau*SUM(gI1,0,1,B0(Sqr(p),Sqr(MCha(gI1)),Sqr(MFtau))*(Conj(
      CpbarChaFtauconjSvtLPR(gI1))*CpbarChaFtauconjSvtLPL(gI1) + Conj(
      CpbarChaFtauconjSvtLPL(gI1))*CpbarChaFtauconjSvtLPR(gI1))*MCha(gI1));
   result += SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpStauconjSvtLconjHpm(gI2,gI1))*B0(
      Sqr(p),Sqr(MHpm(gI1)),Sqr(MStau(gI2)))));
   result += SUM(gI2,0,1,AbsSqr(CpSvtLhhconjSvtL(gI2))*B0(Sqr(p),Sqr(MSvtL),Sqr
      (Mhh(gI2))));
   result += SUM(gI2,0,1,AbsSqr(CpStauconjSvtLconjVWm(gI2))*F0(Sqr(p),Sqr(MStau
      (gI2)),Sqr(MVWm)));
   result += SUM(gI2,0,3,(AbsSqr(CpChiFvtconjSvtLPL(gI2)) + AbsSqr(
      CpChiFvtconjSvtLPR(gI2)))*G0(Sqr(p),Sqr(MFvt),Sqr(MChi(gI2))));
   result += -2*MFvt*SUM(gI2,0,3,B0(Sqr(p),Sqr(MFvt),Sqr(MChi(gI2)))*(Conj(
      CpChiFvtconjSvtLPR(gI2))*CpChiFvtconjSvtLPL(gI2) + Conj(CpChiFvtconjSvtLPL(
      gI2))*CpChiFvtconjSvtLPR(gI2))*MChi(gI2));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_VG_1loop(double p ) const
{
   std::complex<double> result;

   result += 3*AbsSqr(CpbargGgGVG())*B00(Sqr(p),Sqr(MVG),Sqr(MVG));
   result += -3*AbsSqr(CpVGVGVG())*(5*B00(Sqr(p),0,0) + 2*B0(Sqr(p),0,0)*Sqr(p)
      );
   result += 0;
   result += 0.5*(AbsSqr(CpbarFbFbVGPL()) + AbsSqr(CpbarFbFbVGPR()))*H0(Sqr(p),
      Sqr(MFb),Sqr(MFb)) + 2*B0(Sqr(p),Sqr(MFb),Sqr(MFb))*Re(Conj(CpbarFbFbVGPL())
      *CpbarFbFbVGPR())*Sqr(MFb);
   result += 0.5*(AbsSqr(CpbarFcFcVGPL()) + AbsSqr(CpbarFcFcVGPR()))*H0(Sqr(p),
      Sqr(MFc),Sqr(MFc)) + 2*B0(Sqr(p),Sqr(MFc),Sqr(MFc))*Re(Conj(CpbarFcFcVGPL())
      *CpbarFcFcVGPR())*Sqr(MFc);
   result += 0.5*(AbsSqr(CpbarFdFdVGPL()) + AbsSqr(CpbarFdFdVGPR()))*H0(Sqr(p),
      Sqr(MFd),Sqr(MFd)) + 2*B0(Sqr(p),Sqr(MFd),Sqr(MFd))*Re(Conj(CpbarFdFdVGPL())
      *CpbarFdFdVGPR())*Sqr(MFd);
   result += 0.5*(AbsSqr(CpbarFsFsVGPL()) + AbsSqr(CpbarFsFsVGPR()))*H0(Sqr(p),
      Sqr(MFs),Sqr(MFs)) + 2*B0(Sqr(p),Sqr(MFs),Sqr(MFs))*Re(Conj(CpbarFsFsVGPL())
      *CpbarFsFsVGPR())*Sqr(MFs);
   result += 0.5*(AbsSqr(CpbarFtFtVGPL()) + AbsSqr(CpbarFtFtVGPR()))*H0(Sqr(p),
      Sqr(MFt),Sqr(MFt)) + 2*B0(Sqr(p),Sqr(MFt),Sqr(MFt))*Re(Conj(CpbarFtFtVGPL())
      *CpbarFtFtVGPR())*Sqr(MFt);
   result += 0.5*(AbsSqr(CpbarFuFuVGPL()) + AbsSqr(CpbarFuFuVGPR()))*H0(Sqr(p),
      Sqr(MFu),Sqr(MFu)) + 2*B0(Sqr(p),Sqr(MFu),Sqr(MFu))*Re(Conj(CpbarFuFuVGPL())
      *CpbarFuFuVGPR())*Sqr(MFu);
   result += 1.5*(AbsSqr(CpGluGluVGPL()) + AbsSqr(CpGluGluVGPR()))*H0(Sqr(p),
      Sqr(MGlu),Sqr(MGlu)) + 6*B0(Sqr(p),Sqr(MGlu),Sqr(MGlu))*Re(Conj(CpGluGluVGPL
      ())*CpGluGluVGPR())*Sqr(MGlu);
   result += 999*SUM(gI1,0,1,A0(Sqr(MSb(gI1)))*CpSbconjSbVGVG(gI1,gI1));
   result += 999*SUM(gI1,0,1,A0(Sqr(MSc(gI1)))*CpScconjScVGVG(gI1,gI1));
   result += 999*SUM(gI1,0,1,A0(Sqr(MSd(gI1)))*CpSdconjSdVGVG(gI1,gI1));
   result += 999*SUM(gI1,0,1,A0(Sqr(MSs(gI1)))*CpSsconjSsVGVG(gI1,gI1));
   result += 999*SUM(gI1,0,1,A0(Sqr(MSt(gI1)))*CpStconjStVGVG(gI1,gI1));
   result += 999*SUM(gI1,0,1,A0(Sqr(MSu(gI1)))*CpSuconjSuVGVG(gI1,gI1));
   result += -2*SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpSbconjSbVG(gI2,gI1))*B00(Sqr(p
      ),Sqr(MSb(gI1)),Sqr(MSb(gI2)))));
   result += -2*SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpScconjScVG(gI2,gI1))*B00(Sqr(p
      ),Sqr(MSc(gI1)),Sqr(MSc(gI2)))));
   result += -2*SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpSdconjSdVG(gI2,gI1))*B00(Sqr(p
      ),Sqr(MSd(gI1)),Sqr(MSd(gI2)))));
   result += -2*SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpSsconjSsVG(gI2,gI1))*B00(Sqr(p
      ),Sqr(MSs(gI1)),Sqr(MSs(gI2)))));
   result += -2*SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpStconjStVG(gI2,gI1))*B00(Sqr(p
      ),Sqr(MSt(gI1)),Sqr(MSt(gI2)))));
   result += -2*SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpSuconjSuVG(gI2,gI1))*B00(Sqr(p
      ),Sqr(MSu(gI1)),Sqr(MSu(gI2)))));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_VP_1loop(double p ) const
{
   std::complex<double> result;

   result += AbsSqr(CpbargWmCgWmCVP())*B00(Sqr(p),Sqr(MVWm),Sqr(MVWm));
   result += AbsSqr(CpbargWmgWmVP())*B00(Sqr(p),Sqr(MVWm),Sqr(MVWm));
   result += -(A0(Sqr(MVWm))*(CpconjVWmVPVPVWm1() + CpconjVWmVPVPVWm2() + 4*
      CpconjVWmVPVPVWm3()));
   result += (AbsSqr(CpbarFeFeVPPL()) + AbsSqr(CpbarFeFeVPPR()))*H0(Sqr(p),Sqr(
      MFe),Sqr(MFe));
   result += (AbsSqr(CpbarFmFmVPPL()) + AbsSqr(CpbarFmFmVPPR()))*H0(Sqr(p),Sqr(
      MFm),Sqr(MFm));
   result += (AbsSqr(CpbarFtauFtauVPPL()) + AbsSqr(CpbarFtauFtauVPPR()))*H0(Sqr
      (p),Sqr(MFtau),Sqr(MFtau));
   result += -2*AbsSqr(CpconjVWmVPVWm())*(A0(Sqr(MVWm)) + 5*B00(Sqr(p),Sqr(MVWm
      ),Sqr(MVWm)) + B0(Sqr(p),Sqr(MVWm),Sqr(MVWm))*(Sqr(MVWm) + 2*Sqr(p)));
   result += 3*((AbsSqr(CpbarFbFbVPPL()) + AbsSqr(CpbarFbFbVPPR()))*H0(Sqr(p),
      Sqr(MFb),Sqr(MFb)) + 4*B0(Sqr(p),Sqr(MFb),Sqr(MFb))*Re(Conj(CpbarFbFbVPPL())
      *CpbarFbFbVPPR())*Sqr(MFb));
   result += 3*((AbsSqr(CpbarFcFcVPPL()) + AbsSqr(CpbarFcFcVPPR()))*H0(Sqr(p),
      Sqr(MFc),Sqr(MFc)) + 4*B0(Sqr(p),Sqr(MFc),Sqr(MFc))*Re(Conj(CpbarFcFcVPPL())
      *CpbarFcFcVPPR())*Sqr(MFc));
   result += 3*((AbsSqr(CpbarFdFdVPPL()) + AbsSqr(CpbarFdFdVPPR()))*H0(Sqr(p),
      Sqr(MFd),Sqr(MFd)) + 4*B0(Sqr(p),Sqr(MFd),Sqr(MFd))*Re(Conj(CpbarFdFdVPPL())
      *CpbarFdFdVPPR())*Sqr(MFd));
   result += 4*B0(Sqr(p),Sqr(MFe),Sqr(MFe))*Re(Conj(CpbarFeFeVPPL())*
      CpbarFeFeVPPR())*Sqr(MFe);
   result += 4*B0(Sqr(p),Sqr(MFm),Sqr(MFm))*Re(Conj(CpbarFmFmVPPL())*
      CpbarFmFmVPPR())*Sqr(MFm);
   result += 3*((AbsSqr(CpbarFsFsVPPL()) + AbsSqr(CpbarFsFsVPPR()))*H0(Sqr(p),
      Sqr(MFs),Sqr(MFs)) + 4*B0(Sqr(p),Sqr(MFs),Sqr(MFs))*Re(Conj(CpbarFsFsVPPL())
      *CpbarFsFsVPPR())*Sqr(MFs));
   result += 4*B0(Sqr(p),Sqr(MFtau),Sqr(MFtau))*Re(Conj(CpbarFtauFtauVPPL())*
      CpbarFtauFtauVPPR())*Sqr(MFtau);
   result += 3*((AbsSqr(CpbarFtFtVPPL()) + AbsSqr(CpbarFtFtVPPR()))*H0(Sqr(p),
      Sqr(MFt),Sqr(MFt)) + 4*B0(Sqr(p),Sqr(MFt),Sqr(MFt))*Re(Conj(CpbarFtFtVPPL())
      *CpbarFtFtVPPR())*Sqr(MFt));
   result += 3*((AbsSqr(CpbarFuFuVPPL()) + AbsSqr(CpbarFuFuVPPR()))*H0(Sqr(p),
      Sqr(MFu),Sqr(MFu)) + 4*B0(Sqr(p),Sqr(MFu),Sqr(MFu))*Re(Conj(CpbarFuFuVPPL())
      *CpbarFuFuVPPR())*Sqr(MFu));
   result += SUM(gI1,0,1,A0(Sqr(MHpm(gI1)))*CpHpmconjHpmVPVP(gI1,gI1));
   result += 3*SUM(gI1,0,1,A0(Sqr(MSb(gI1)))*CpSbconjSbVPVP(gI1,gI1));
   result += 3*SUM(gI1,0,1,A0(Sqr(MSc(gI1)))*CpScconjScVPVP(gI1,gI1));
   result += 3*SUM(gI1,0,1,A0(Sqr(MSd(gI1)))*CpSdconjSdVPVP(gI1,gI1));
   result += SUM(gI1,0,1,A0(Sqr(MSe(gI1)))*CpSeconjSeVPVP(gI1,gI1));
   result += SUM(gI1,0,1,A0(Sqr(MSm(gI1)))*CpSmconjSmVPVP(gI1,gI1));
   result += 3*SUM(gI1,0,1,A0(Sqr(MSs(gI1)))*CpSsconjSsVPVP(gI1,gI1));
   result += SUM(gI1,0,1,A0(Sqr(MStau(gI1)))*CpStauconjStauVPVP(gI1,gI1));
   result += 3*SUM(gI1,0,1,A0(Sqr(MSt(gI1)))*CpStconjStVPVP(gI1,gI1));
   result += 3*SUM(gI1,0,1,A0(Sqr(MSu(gI1)))*CpSuconjSuVPVP(gI1,gI1));
   result += -4*SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpHpmconjHpmVP(gI2,gI1))*B00(Sqr
      (p),Sqr(MHpm(gI1)),Sqr(MHpm(gI2)))));
   result += -12*SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpSbconjSbVP(gI2,gI1))*B00(Sqr(
      p),Sqr(MSb(gI1)),Sqr(MSb(gI2)))));
   result += -12*SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpScconjScVP(gI2,gI1))*B00(Sqr(
      p),Sqr(MSc(gI1)),Sqr(MSc(gI2)))));
   result += -12*SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpSdconjSdVP(gI2,gI1))*B00(Sqr(
      p),Sqr(MSd(gI1)),Sqr(MSd(gI2)))));
   result += -4*SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpSeconjSeVP(gI2,gI1))*B00(Sqr(p
      ),Sqr(MSe(gI1)),Sqr(MSe(gI2)))));
   result += -4*SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpSmconjSmVP(gI2,gI1))*B00(Sqr(p
      ),Sqr(MSm(gI1)),Sqr(MSm(gI2)))));
   result += -12*SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpSsconjSsVP(gI2,gI1))*B00(Sqr(
      p),Sqr(MSs(gI1)),Sqr(MSs(gI2)))));
   result += -4*SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpStauconjStauVP(gI2,gI1))*B00(
      Sqr(p),Sqr(MStau(gI1)),Sqr(MStau(gI2)))));
   result += -12*SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpStconjStVP(gI2,gI1))*B00(Sqr(
      p),Sqr(MSt(gI1)),Sqr(MSt(gI2)))));
   result += -12*SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpSuconjSuVP(gI2,gI1))*B00(Sqr(
      p),Sqr(MSu(gI1)),Sqr(MSu(gI2)))));
   result += SUM(gI1,0,1,SUM(gI2,0,1,(AbsSqr(CpbarChaChaVPPL(gI1,gI2)) + AbsSqr
      (CpbarChaChaVPPR(gI1,gI2)))*H0(Sqr(p),Sqr(MCha(gI1)),Sqr(MCha(gI2))) + 4*B0(
      Sqr(p),Sqr(MCha(gI1)),Sqr(MCha(gI2)))*MCha(gI1)*MCha(gI2)*Re(Conj(
      CpbarChaChaVPPL(gI1,gI2))*CpbarChaChaVPPR(gI1,gI2))));
   result += 2*SUM(gI2,0,1,AbsSqr(CpHpmconjVWmVP(gI2))*B0(Sqr(p),Sqr(MVWm),Sqr(
      MHpm(gI2))));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_VZ_1loop(double p ) const
{
   std::complex<double> result;

   result += AbsSqr(CpbargWmCgWmCVZ())*B00(Sqr(p),Sqr(MVWm),Sqr(MVWm));
   result += AbsSqr(CpbargWmgWmVZ())*B00(Sqr(p),Sqr(MVWm),Sqr(MVWm));
   result += -(A0(Sqr(MVWm))*(4*CpconjVWmVWmVZVZ1() + CpconjVWmVWmVZVZ2() +
      CpconjVWmVWmVZVZ3()));
   result += -4*AbsSqr(CpSveLconjSveLVZ())*B00(Sqr(p),Sqr(MSveL),Sqr(MSveL));
   result += A0(Sqr(MSveL))*CpSveLconjSveLVZVZ();
   result += -4*AbsSqr(CpSvmLconjSvmLVZ())*B00(Sqr(p),Sqr(MSvmL),Sqr(MSvmL));
   result += A0(Sqr(MSvmL))*CpSvmLconjSvmLVZVZ();
   result += -4*AbsSqr(CpSvtLconjSvtLVZ())*B00(Sqr(p),Sqr(MSvtL),Sqr(MSvtL));
   result += A0(Sqr(MSvtL))*CpSvtLconjSvtLVZVZ();
   result += (AbsSqr(CpbarFeFeVZPL()) + AbsSqr(CpbarFeFeVZPR()))*H0(Sqr(p),Sqr(
      MFe),Sqr(MFe));
   result += (AbsSqr(CpbarFmFmVZPL()) + AbsSqr(CpbarFmFmVZPR()))*H0(Sqr(p),Sqr(
      MFm),Sqr(MFm));
   result += (AbsSqr(CpbarFtauFtauVZPL()) + AbsSqr(CpbarFtauFtauVZPR()))*H0(Sqr
      (p),Sqr(MFtau),Sqr(MFtau));
   result += (AbsSqr(CpbarFveFveVZPL()) + AbsSqr(CpbarFveFveVZPR()))*H0(Sqr(p),
      Sqr(MFve),Sqr(MFve));
   result += (AbsSqr(CpbarFvmFvmVZPL()) + AbsSqr(CpbarFvmFvmVZPR()))*H0(Sqr(p),
      Sqr(MFvm),Sqr(MFvm));
   result += (AbsSqr(CpbarFvtFvtVZPL()) + AbsSqr(CpbarFvtFvtVZPR()))*H0(Sqr(p),
      Sqr(MFvt),Sqr(MFvt));
   result += -2*AbsSqr(CpconjVWmVWmVZ())*(A0(Sqr(MVWm)) + 5*B00(Sqr(p),Sqr(MVWm
      ),Sqr(MVWm)) + B0(Sqr(p),Sqr(MVWm),Sqr(MVWm))*(Sqr(MVWm) + 2*Sqr(p)));
   result += 3*((AbsSqr(CpbarFbFbVZPL()) + AbsSqr(CpbarFbFbVZPR()))*H0(Sqr(p),
      Sqr(MFb),Sqr(MFb)) + 4*B0(Sqr(p),Sqr(MFb),Sqr(MFb))*Re(Conj(CpbarFbFbVZPL())
      *CpbarFbFbVZPR())*Sqr(MFb));
   result += 3*((AbsSqr(CpbarFcFcVZPL()) + AbsSqr(CpbarFcFcVZPR()))*H0(Sqr(p),
      Sqr(MFc),Sqr(MFc)) + 4*B0(Sqr(p),Sqr(MFc),Sqr(MFc))*Re(Conj(CpbarFcFcVZPL())
      *CpbarFcFcVZPR())*Sqr(MFc));
   result += 3*((AbsSqr(CpbarFdFdVZPL()) + AbsSqr(CpbarFdFdVZPR()))*H0(Sqr(p),
      Sqr(MFd),Sqr(MFd)) + 4*B0(Sqr(p),Sqr(MFd),Sqr(MFd))*Re(Conj(CpbarFdFdVZPL())
      *CpbarFdFdVZPR())*Sqr(MFd));
   result += 4*B0(Sqr(p),Sqr(MFe),Sqr(MFe))*Re(Conj(CpbarFeFeVZPL())*
      CpbarFeFeVZPR())*Sqr(MFe);
   result += 4*B0(Sqr(p),Sqr(MFm),Sqr(MFm))*Re(Conj(CpbarFmFmVZPL())*
      CpbarFmFmVZPR())*Sqr(MFm);
   result += 3*((AbsSqr(CpbarFsFsVZPL()) + AbsSqr(CpbarFsFsVZPR()))*H0(Sqr(p),
      Sqr(MFs),Sqr(MFs)) + 4*B0(Sqr(p),Sqr(MFs),Sqr(MFs))*Re(Conj(CpbarFsFsVZPL())
      *CpbarFsFsVZPR())*Sqr(MFs));
   result += 4*B0(Sqr(p),Sqr(MFtau),Sqr(MFtau))*Re(Conj(CpbarFtauFtauVZPL())*
      CpbarFtauFtauVZPR())*Sqr(MFtau);
   result += 3*((AbsSqr(CpbarFtFtVZPL()) + AbsSqr(CpbarFtFtVZPR()))*H0(Sqr(p),
      Sqr(MFt),Sqr(MFt)) + 4*B0(Sqr(p),Sqr(MFt),Sqr(MFt))*Re(Conj(CpbarFtFtVZPL())
      *CpbarFtFtVZPR())*Sqr(MFt));
   result += 3*((AbsSqr(CpbarFuFuVZPL()) + AbsSqr(CpbarFuFuVZPR()))*H0(Sqr(p),
      Sqr(MFu),Sqr(MFu)) + 4*B0(Sqr(p),Sqr(MFu),Sqr(MFu))*Re(Conj(CpbarFuFuVZPL())
      *CpbarFuFuVZPR())*Sqr(MFu));
   result += 4*B0(Sqr(p),Sqr(MFve),Sqr(MFve))*Re(Conj(CpbarFveFveVZPL())*
      CpbarFveFveVZPR())*Sqr(MFve);
   result += 4*B0(Sqr(p),Sqr(MFvm),Sqr(MFvm))*Re(Conj(CpbarFvmFvmVZPL())*
      CpbarFvmFvmVZPR())*Sqr(MFvm);
   result += 4*B0(Sqr(p),Sqr(MFvt),Sqr(MFvt))*Re(Conj(CpbarFvtFvtVZPL())*
      CpbarFvtFvtVZPR())*Sqr(MFvt);
   result += 0.5*SUM(gI1,0,1,A0(Sqr(MAh(gI1)))*CpAhAhVZVZ(gI1,gI1));
   result += 0.5*SUM(gI1,0,1,A0(Sqr(Mhh(gI1)))*CphhhhVZVZ(gI1,gI1));
   result += SUM(gI1,0,1,A0(Sqr(MHpm(gI1)))*CpHpmconjHpmVZVZ(gI1,gI1));
   result += 3*SUM(gI1,0,1,A0(Sqr(MSb(gI1)))*CpSbconjSbVZVZ(gI1,gI1));
   result += 3*SUM(gI1,0,1,A0(Sqr(MSc(gI1)))*CpScconjScVZVZ(gI1,gI1));
   result += 3*SUM(gI1,0,1,A0(Sqr(MSd(gI1)))*CpSdconjSdVZVZ(gI1,gI1));
   result += SUM(gI1,0,1,A0(Sqr(MSe(gI1)))*CpSeconjSeVZVZ(gI1,gI1));
   result += SUM(gI1,0,1,A0(Sqr(MSm(gI1)))*CpSmconjSmVZVZ(gI1,gI1));
   result += 3*SUM(gI1,0,1,A0(Sqr(MSs(gI1)))*CpSsconjSsVZVZ(gI1,gI1));
   result += SUM(gI1,0,1,A0(Sqr(MStau(gI1)))*CpStauconjStauVZVZ(gI1,gI1));
   result += 3*SUM(gI1,0,1,A0(Sqr(MSt(gI1)))*CpStconjStVZVZ(gI1,gI1));
   result += 3*SUM(gI1,0,1,A0(Sqr(MSu(gI1)))*CpSuconjSuVZVZ(gI1,gI1));
   result += -4*SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpAhhhVZ(gI2,gI1))*B00(Sqr(p),
      Sqr(MAh(gI2)),Sqr(Mhh(gI1)))));
   result += -4*SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpHpmconjHpmVZ(gI2,gI1))*B00(Sqr
      (p),Sqr(MHpm(gI1)),Sqr(MHpm(gI2)))));
   result += -12*SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpSbconjSbVZ(gI2,gI1))*B00(Sqr(
      p),Sqr(MSb(gI1)),Sqr(MSb(gI2)))));
   result += -12*SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpScconjScVZ(gI2,gI1))*B00(Sqr(
      p),Sqr(MSc(gI1)),Sqr(MSc(gI2)))));
   result += -12*SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpSdconjSdVZ(gI2,gI1))*B00(Sqr(
      p),Sqr(MSd(gI1)),Sqr(MSd(gI2)))));
   result += -4*SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpSeconjSeVZ(gI2,gI1))*B00(Sqr(p
      ),Sqr(MSe(gI1)),Sqr(MSe(gI2)))));
   result += -4*SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpSmconjSmVZ(gI2,gI1))*B00(Sqr(p
      ),Sqr(MSm(gI1)),Sqr(MSm(gI2)))));
   result += -12*SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpSsconjSsVZ(gI2,gI1))*B00(Sqr(
      p),Sqr(MSs(gI1)),Sqr(MSs(gI2)))));
   result += -4*SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpStauconjStauVZ(gI2,gI1))*B00(
      Sqr(p),Sqr(MStau(gI1)),Sqr(MStau(gI2)))));
   result += -12*SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpStconjStVZ(gI2,gI1))*B00(Sqr(
      p),Sqr(MSt(gI1)),Sqr(MSt(gI2)))));
   result += -12*SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpSuconjSuVZ(gI2,gI1))*B00(Sqr(
      p),Sqr(MSu(gI1)),Sqr(MSu(gI2)))));
   result += SUM(gI1,0,1,SUM(gI2,0,1,(AbsSqr(CpbarChaChaVZPL(gI1,gI2)) + AbsSqr
      (CpbarChaChaVZPR(gI1,gI2)))*H0(Sqr(p),Sqr(MCha(gI1)),Sqr(MCha(gI2))) + 4*B0(
      Sqr(p),Sqr(MCha(gI1)),Sqr(MCha(gI2)))*MCha(gI1)*MCha(gI2)*Re(Conj(
      CpbarChaChaVZPL(gI1,gI2))*CpbarChaChaVZPR(gI1,gI2))));
   result += 0.5*SUM(gI1,0,3,SUM(gI2,0,3,(AbsSqr(CpChiChiVZPL(gI1,gI2)) +
      AbsSqr(CpChiChiVZPR(gI1,gI2)))*H0(Sqr(p),Sqr(MChi(gI1)),Sqr(MChi(gI2))) + 4*
      B0(Sqr(p),Sqr(MChi(gI1)),Sqr(MChi(gI2)))*MChi(gI1)*MChi(gI2)*Re(Conj(
      CpChiChiVZPL(gI1,gI2))*CpChiChiVZPR(gI1,gI2))));
   result += SUM(gI2,0,1,AbsSqr(CphhVZVZ(gI2))*B0(Sqr(p),Sqr(MVZ),Sqr(Mhh(gI2))
      ));
   result += 2*SUM(gI2,0,1,AbsSqr(CpHpmconjVWmVZ(gI2))*B0(Sqr(p),Sqr(MVWm),Sqr(
      MHpm(gI2))));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_VWm_1loop(double p ) const
{
   std::complex<double> result;

   result += AbsSqr(CpbargPgWmconjVWm())*B00(Sqr(p),Sqr(MVWm),Sqr(MVP));
   result += AbsSqr(CpbargWmCgPconjVWm())*B00(Sqr(p),Sqr(MVP),Sqr(MVWm));
   result += AbsSqr(CpbargWmCgZconjVWm())*B00(Sqr(p),Sqr(MVZ),Sqr(MVWm));
   result += AbsSqr(CpbargZgWmconjVWm())*B00(Sqr(p),Sqr(MVWm),Sqr(MVZ));
   result += -(A0(Sqr(MVWm))*(CpconjVWmconjVWmVWmVWm1() + 4*
      CpconjVWmconjVWmVWmVWm2() + CpconjVWmconjVWmVWmVWm3()));
   result += 0;
   result += -0.5*A0(Sqr(MVZ))*(4*CpconjVWmVWmVZVZ1() + CpconjVWmVWmVZVZ2() +
      CpconjVWmVWmVZVZ3());
   result += A0(Sqr(MSveL))*CpSveLconjSveLconjVWmVWm();
   result += A0(Sqr(MSvmL))*CpSvmLconjSvmLconjVWmVWm();
   result += A0(Sqr(MSvtL))*CpSvtLconjSvtLconjVWmVWm();
   result += (AbsSqr(CpbarFveFeconjVWmPL()) + AbsSqr(CpbarFveFeconjVWmPR()))*H0
      (Sqr(p),Sqr(MFve),Sqr(MFe));
   result += (AbsSqr(CpbarFvmFmconjVWmPL()) + AbsSqr(CpbarFvmFmconjVWmPR()))*H0
      (Sqr(p),Sqr(MFvm),Sqr(MFm));
   result += (AbsSqr(CpbarFvtFtauconjVWmPL()) + AbsSqr(CpbarFvtFtauconjVWmPR())
      )*H0(Sqr(p),Sqr(MFvt),Sqr(MFtau));
   result += -(AbsSqr(CpconjVWmVPVWm())*(A0(Sqr(MVWm)) + 10*B00(Sqr(p),Sqr(MVWm
      ),0) + B0(Sqr(p),Sqr(MVWm),0)*(Sqr(MVWm) + 4*Sqr(p))));
   result += -(AbsSqr(CpconjVWmVWmVZ())*(A0(Sqr(MVWm)) + A0(Sqr(MVZ)) + 10*B00(
      Sqr(p),Sqr(MVZ),Sqr(MVWm)) + B0(Sqr(p),Sqr(MVZ),Sqr(MVWm))*(Sqr(MVWm) + Sqr(
      MVZ) + 4*Sqr(p))));
   result += 3*((AbsSqr(CpbarFcFsconjVWmPL()) + AbsSqr(CpbarFcFsconjVWmPR()))*
      H0(Sqr(p),Sqr(MFc),Sqr(MFs)) + 4*MFc*MFs*B0(Sqr(p),Sqr(MFc),Sqr(MFs))*Re(
      Conj(CpbarFcFsconjVWmPL())*CpbarFcFsconjVWmPR()));
   result += 3*((AbsSqr(CpbarFtFbconjVWmPL()) + AbsSqr(CpbarFtFbconjVWmPR()))*
      H0(Sqr(p),Sqr(MFt),Sqr(MFb)) + 4*MFb*MFt*B0(Sqr(p),Sqr(MFt),Sqr(MFb))*Re(
      Conj(CpbarFtFbconjVWmPL())*CpbarFtFbconjVWmPR()));
   result += 3*((AbsSqr(CpbarFuFdconjVWmPL()) + AbsSqr(CpbarFuFdconjVWmPR()))*
      H0(Sqr(p),Sqr(MFu),Sqr(MFd)) + 4*MFd*MFu*B0(Sqr(p),Sqr(MFu),Sqr(MFd))*Re(
      Conj(CpbarFuFdconjVWmPL())*CpbarFuFdconjVWmPR()));
   result += 4*MFe*MFve*B0(Sqr(p),Sqr(MFve),Sqr(MFe))*Re(Conj(
      CpbarFveFeconjVWmPL())*CpbarFveFeconjVWmPR());
   result += 4*MFm*MFvm*B0(Sqr(p),Sqr(MFvm),Sqr(MFm))*Re(Conj(
      CpbarFvmFmconjVWmPL())*CpbarFvmFmconjVWmPR());
   result += 4*MFtau*MFvt*B0(Sqr(p),Sqr(MFvt),Sqr(MFtau))*Re(Conj(
      CpbarFvtFtauconjVWmPL())*CpbarFvtFtauconjVWmPR());
   result += 0.5*SUM(gI1,0,1,A0(Sqr(MAh(gI1)))*CpAhAhconjVWmVWm(gI1,gI1));
   result += 0.5*SUM(gI1,0,1,A0(Sqr(Mhh(gI1)))*CphhhhconjVWmVWm(gI1,gI1));
   result += SUM(gI1,0,1,A0(Sqr(MHpm(gI1)))*CpHpmconjHpmconjVWmVWm(gI1,gI1));
   result += 3*SUM(gI1,0,1,A0(Sqr(MSb(gI1)))*CpSbconjSbconjVWmVWm(gI1,gI1));
   result += 3*SUM(gI1,0,1,A0(Sqr(MSc(gI1)))*CpScconjScconjVWmVWm(gI1,gI1));
   result += 3*SUM(gI1,0,1,A0(Sqr(MSd(gI1)))*CpSdconjSdconjVWmVWm(gI1,gI1));
   result += SUM(gI1,0,1,A0(Sqr(MSe(gI1)))*CpSeconjSeconjVWmVWm(gI1,gI1));
   result += SUM(gI1,0,1,A0(Sqr(MSm(gI1)))*CpSmconjSmconjVWmVWm(gI1,gI1));
   result += 3*SUM(gI1,0,1,A0(Sqr(MSs(gI1)))*CpSsconjSsconjVWmVWm(gI1,gI1));
   result += SUM(gI1,0,1,A0(Sqr(MStau(gI1)))*CpStauconjStauconjVWmVWm(gI1,gI1))
      ;
   result += 3*SUM(gI1,0,1,A0(Sqr(MSt(gI1)))*CpStconjStconjVWmVWm(gI1,gI1));
   result += 3*SUM(gI1,0,1,A0(Sqr(MSu(gI1)))*CpSuconjSuconjVWmVWm(gI1,gI1));
   result += -4*SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpAhHpmconjVWm(gI2,gI1))*B00(Sqr
      (p),Sqr(MAh(gI2)),Sqr(MHpm(gI1)))));
   result += -4*SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CphhHpmconjVWm(gI2,gI1))*B00(Sqr
      (p),Sqr(Mhh(gI2)),Sqr(MHpm(gI1)))));
   result += -12*SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpSbconjStconjVWm(gI2,gI1))*B00
      (Sqr(p),Sqr(MSb(gI2)),Sqr(MSt(gI1)))));
   result += -12*SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpSdconjSuconjVWm(gI2,gI1))*B00
      (Sqr(p),Sqr(MSd(gI2)),Sqr(MSu(gI1)))));
   result += -12*SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpSsconjScconjVWm(gI2,gI1))*B00
      (Sqr(p),Sqr(MSs(gI2)),Sqr(MSc(gI1)))));
   result += SUM(gI1,0,3,SUM(gI2,0,1,(AbsSqr(CpChiChaconjVWmPL(gI1,gI2)) +
      AbsSqr(CpChiChaconjVWmPR(gI1,gI2)))*H0(Sqr(p),Sqr(MChi(gI1)),Sqr(MCha(gI2)))
      + 4*B0(Sqr(p),Sqr(MChi(gI1)),Sqr(MCha(gI2)))*MCha(gI2)*MChi(gI1)*Re(Conj(
      CpChiChaconjVWmPL(gI1,gI2))*CpChiChaconjVWmPR(gI1,gI2))));
   result += SUM(gI2,0,1,AbsSqr(CphhconjVWmVWm(gI2))*B0(Sqr(p),Sqr(MVWm),Sqr(
      Mhh(gI2))));
   result += SUM(gI2,0,1,AbsSqr(CpHpmconjVWmVP(gI2))*B0(Sqr(p),0,Sqr(MHpm(gI2))
      ));
   result += SUM(gI2,0,1,AbsSqr(CpHpmconjVWmVZ(gI2))*B0(Sqr(p),Sqr(MVZ),Sqr(
      MHpm(gI2))));
   result += -4*SUM(gI2,0,1,AbsSqr(CpSeconjSveLconjVWm(gI2))*B00(Sqr(p),Sqr(MSe
      (gI2)),Sqr(MSveL)));
   result += -4*SUM(gI2,0,1,AbsSqr(CpSmconjSvmLconjVWm(gI2))*B00(Sqr(p),Sqr(MSm
      (gI2)),Sqr(MSvmL)));
   result += -4*SUM(gI2,0,1,AbsSqr(CpStauconjSvtLconjVWm(gI2))*B00(Sqr(p),Sqr(
      MStau(gI2)),Sqr(MSvtL)));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Chi_1loop_1(double p , int gO1, int gO2) const
{
   std::complex<double> result;

   result += MFve*B0(Sqr(p),Sqr(MFve),Sqr(MSveL))*Conj(CpbarFveUChiSveLPL(gO2))
      *CpbarFveUChiSveLPR(gO1);
   result += MFve*B0(Sqr(p),Sqr(MFve),Sqr(MSveL))*Conj(CpUChiFveconjSveLPL(gO2)
      )*CpUChiFveconjSveLPR(gO1);
   result += MFvm*B0(Sqr(p),Sqr(MFvm),Sqr(MSvmL))*Conj(CpbarFvmUChiSvmLPL(gO2))
      *CpbarFvmUChiSvmLPR(gO1);
   result += MFvm*B0(Sqr(p),Sqr(MFvm),Sqr(MSvmL))*Conj(CpUChiFvmconjSvmLPL(gO2)
      )*CpUChiFvmconjSvmLPR(gO1);
   result += MFvt*B0(Sqr(p),Sqr(MFvt),Sqr(MSvtL))*Conj(CpbarFvtUChiSvtLPL(gO2))
      *CpbarFvtUChiSvtLPR(gO1);
   result += MFvt*B0(Sqr(p),Sqr(MFvt),Sqr(MSvtL))*Conj(CpUChiFvtconjSvtLPL(gO2)
      )*CpUChiFvtconjSvtLPR(gO1);
   result += 3*MFb*SUM(gI1,0,1,B0(Sqr(p),Sqr(MFb),Sqr(MSb(gI1)))*Conj(
      CpUChiFbconjSbPL(gO2,gI1))*CpUChiFbconjSbPR(gO1,gI1));
   result += 3*MFc*SUM(gI1,0,1,B0(Sqr(p),Sqr(MFc),Sqr(MSc(gI1)))*Conj(
      CpUChiFcconjScPL(gO2,gI1))*CpUChiFcconjScPR(gO1,gI1));
   result += 3*MFd*SUM(gI1,0,1,B0(Sqr(p),Sqr(MFd),Sqr(MSd(gI1)))*Conj(
      CpUChiFdconjSdPL(gO2,gI1))*CpUChiFdconjSdPR(gO1,gI1));
   result += MFe*SUM(gI1,0,1,B0(Sqr(p),Sqr(MFe),Sqr(MSe(gI1)))*Conj(
      CpUChiFeconjSePL(gO2,gI1))*CpUChiFeconjSePR(gO1,gI1));
   result += MFm*SUM(gI1,0,1,B0(Sqr(p),Sqr(MFm),Sqr(MSm(gI1)))*Conj(
      CpUChiFmconjSmPL(gO2,gI1))*CpUChiFmconjSmPR(gO1,gI1));
   result += 3*MFs*SUM(gI1,0,1,B0(Sqr(p),Sqr(MFs),Sqr(MSs(gI1)))*Conj(
      CpUChiFsconjSsPL(gO2,gI1))*CpUChiFsconjSsPR(gO1,gI1));
   result += MFtau*SUM(gI1,0,1,B0(Sqr(p),Sqr(MFtau),Sqr(MStau(gI1)))*Conj(
      CpUChiFtauconjStauPL(gO2,gI1))*CpUChiFtauconjStauPR(gO1,gI1));
   result += 3*MFt*SUM(gI1,0,1,B0(Sqr(p),Sqr(MFt),Sqr(MSt(gI1)))*Conj(
      CpUChiFtconjStPL(gO2,gI1))*CpUChiFtconjStPR(gO1,gI1));
   result += 3*MFu*SUM(gI1,0,1,B0(Sqr(p),Sqr(MFu),Sqr(MSu(gI1)))*Conj(
      CpUChiFuconjSuPL(gO2,gI1))*CpUChiFuconjSuPR(gO1,gI1));
   result += -4*SUM(gI1,0,1,B0(Sqr(p),Sqr(MCha(gI1)),Sqr(MVWm))*Conj(
      CpbarChaUChiVWmPL(gI1,gO2))*CpbarChaUChiVWmPR(gI1,gO1)*MCha(gI1));
   result += SUM(gI1,0,1,MCha(gI1)*SUM(gI2,0,1,B0(Sqr(p),Sqr(MCha(gI1)),Sqr(
      MHpm(gI2)))*Conj(CpbarChaUChiHpmPL(gI1,gO2,gI2))*CpbarChaUChiHpmPR(gI1,gO1,
      gI2)));
   result += SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(MCha(gI2)),Sqr(MHpm(gI1)))*
      Conj(CpUChiChaconjHpmPL(gO2,gI2,gI1))*CpUChiChaconjHpmPR(gO1,gI2,gI1)*MCha(
      gI2)));
   result += SUM(gI1,0,1,SUM(gI2,0,3,B0(Sqr(p),Sqr(MChi(gI2)),Sqr(Mhh(gI1)))*
      Conj(CpChiUChihhPL(gI2,gO2,gI1))*CpChiUChihhPR(gI2,gO1,gI1)*MChi(gI2)));
   result += SUM(gI1,0,3,MChi(gI1)*SUM(gI2,0,1,B0(Sqr(p),Sqr(MChi(gI1)),Sqr(MAh
      (gI2)))*Conj(CpChiUChiAhPL(gI1,gO2,gI2))*CpChiUChiAhPR(gI1,gO1,gI2)));
   result += 3*MFb*SUM(gI2,0,1,B0(Sqr(p),Sqr(MFb),Sqr(MSb(gI2)))*Conj(
      CpbarFbUChiSbPL(gO2,gI2))*CpbarFbUChiSbPR(gO1,gI2));
   result += 3*MFc*SUM(gI2,0,1,B0(Sqr(p),Sqr(MFc),Sqr(MSc(gI2)))*Conj(
      CpbarFcUChiScPL(gO2,gI2))*CpbarFcUChiScPR(gO1,gI2));
   result += 3*MFd*SUM(gI2,0,1,B0(Sqr(p),Sqr(MFd),Sqr(MSd(gI2)))*Conj(
      CpbarFdUChiSdPL(gO2,gI2))*CpbarFdUChiSdPR(gO1,gI2));
   result += MFe*SUM(gI2,0,1,B0(Sqr(p),Sqr(MFe),Sqr(MSe(gI2)))*Conj(
      CpbarFeUChiSePL(gO2,gI2))*CpbarFeUChiSePR(gO1,gI2));
   result += MFm*SUM(gI2,0,1,B0(Sqr(p),Sqr(MFm),Sqr(MSm(gI2)))*Conj(
      CpbarFmUChiSmPL(gO2,gI2))*CpbarFmUChiSmPR(gO1,gI2));
   result += 3*MFs*SUM(gI2,0,1,B0(Sqr(p),Sqr(MFs),Sqr(MSs(gI2)))*Conj(
      CpbarFsUChiSsPL(gO2,gI2))*CpbarFsUChiSsPR(gO1,gI2));
   result += MFtau*SUM(gI2,0,1,B0(Sqr(p),Sqr(MFtau),Sqr(MStau(gI2)))*Conj(
      CpbarFtauUChiStauPL(gO2,gI2))*CpbarFtauUChiStauPR(gO1,gI2));
   result += 3*MFt*SUM(gI2,0,1,B0(Sqr(p),Sqr(MFt),Sqr(MSt(gI2)))*Conj(
      CpbarFtUChiStPL(gO2,gI2))*CpbarFtUChiStPR(gO1,gI2));
   result += 3*MFu*SUM(gI2,0,1,B0(Sqr(p),Sqr(MFu),Sqr(MSu(gI2)))*Conj(
      CpbarFuUChiSuPL(gO2,gI2))*CpbarFuUChiSuPR(gO1,gI2));
   result += -4*SUM(gI2,0,1,B0(Sqr(p),Sqr(MCha(gI2)),Sqr(MVWm))*Conj(
      CpUChiChaconjVWmPR(gO2,gI2))*CpUChiChaconjVWmPL(gO1,gI2)*MCha(gI2));
   result += -4*SUM(gI2,0,3,B0(Sqr(p),Sqr(MChi(gI2)),Sqr(MVZ))*Conj(
      CpChiUChiVZPL(gI2,gO2))*CpChiUChiVZPR(gI2,gO1)*MChi(gI2));

   return result * oneOver16PiSqr;

}

Eigen::Matrix<std::complex<double>,4,4> CLASSNAME::self_energy_Chi_1loop_1(double p) const
{
   Eigen::Matrix<std::complex<double>,4,4> self_energy;

   for (int i = 0; i < 4; i++)
      for (int k = 0; k < 4; k++)
         self_energy(i, k) = self_energy_Chi_1loop_1(p, i, k);

   return self_energy;
}

std::complex<double> CLASSNAME::self_energy_Chi_1loop_PR(double p , int gO1, int gO2) const
{
   std::complex<double> result;

   result += -0.5*B1(Sqr(p),Sqr(MFve),Sqr(MSveL))*Conj(CpbarFveUChiSveLPR(gO2))
      *CpbarFveUChiSveLPR(gO1);
   result += -0.5*B1(Sqr(p),Sqr(MFvm),Sqr(MSvmL))*Conj(CpbarFvmUChiSvmLPR(gO2))
      *CpbarFvmUChiSvmLPR(gO1);
   result += -0.5*B1(Sqr(p),Sqr(MFvt),Sqr(MSvtL))*Conj(CpbarFvtUChiSvtLPR(gO2))
      *CpbarFvtUChiSvtLPR(gO1);
   result += -0.5*B1(Sqr(p),Sqr(MFve),Sqr(MSveL))*Conj(CpUChiFveconjSveLPR(gO2)
      )*CpUChiFveconjSveLPR(gO1);
   result += -0.5*B1(Sqr(p),Sqr(MFvm),Sqr(MSvmL))*Conj(CpUChiFvmconjSvmLPR(gO2)
      )*CpUChiFvmconjSvmLPR(gO1);
   result += -0.5*B1(Sqr(p),Sqr(MFvt),Sqr(MSvtL))*Conj(CpUChiFvtconjSvtLPR(gO2)
      )*CpUChiFvtconjSvtLPR(gO1);
   result += -SUM(gI1,0,1,B1(Sqr(p),Sqr(MCha(gI1)),Sqr(MVWm))*Conj(
      CpbarChaUChiVWmPR(gI1,gO2))*CpbarChaUChiVWmPR(gI1,gO1));
   result += -1.5*SUM(gI1,0,1,B1(Sqr(p),Sqr(MFb),Sqr(MSb(gI1)))*Conj(
      CpUChiFbconjSbPR(gO2,gI1))*CpUChiFbconjSbPR(gO1,gI1));
   result += -1.5*SUM(gI1,0,1,B1(Sqr(p),Sqr(MFc),Sqr(MSc(gI1)))*Conj(
      CpUChiFcconjScPR(gO2,gI1))*CpUChiFcconjScPR(gO1,gI1));
   result += -1.5*SUM(gI1,0,1,B1(Sqr(p),Sqr(MFd),Sqr(MSd(gI1)))*Conj(
      CpUChiFdconjSdPR(gO2,gI1))*CpUChiFdconjSdPR(gO1,gI1));
   result += -0.5*SUM(gI1,0,1,B1(Sqr(p),Sqr(MFe),Sqr(MSe(gI1)))*Conj(
      CpUChiFeconjSePR(gO2,gI1))*CpUChiFeconjSePR(gO1,gI1));
   result += -0.5*SUM(gI1,0,1,B1(Sqr(p),Sqr(MFm),Sqr(MSm(gI1)))*Conj(
      CpUChiFmconjSmPR(gO2,gI1))*CpUChiFmconjSmPR(gO1,gI1));
   result += -1.5*SUM(gI1,0,1,B1(Sqr(p),Sqr(MFs),Sqr(MSs(gI1)))*Conj(
      CpUChiFsconjSsPR(gO2,gI1))*CpUChiFsconjSsPR(gO1,gI1));
   result += -0.5*SUM(gI1,0,1,B1(Sqr(p),Sqr(MFtau),Sqr(MStau(gI1)))*Conj(
      CpUChiFtauconjStauPR(gO2,gI1))*CpUChiFtauconjStauPR(gO1,gI1));
   result += -1.5*SUM(gI1,0,1,B1(Sqr(p),Sqr(MFt),Sqr(MSt(gI1)))*Conj(
      CpUChiFtconjStPR(gO2,gI1))*CpUChiFtconjStPR(gO1,gI1));
   result += -1.5*SUM(gI1,0,1,B1(Sqr(p),Sqr(MFu),Sqr(MSu(gI1)))*Conj(
      CpUChiFuconjSuPR(gO2,gI1))*CpUChiFuconjSuPR(gO1,gI1));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,1,B1(Sqr(p),Sqr(MCha(gI1)),Sqr(MHpm(gI2
      )))*Conj(CpbarChaUChiHpmPR(gI1,gO2,gI2))*CpbarChaUChiHpmPR(gI1,gO1,gI2)));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,1,B1(Sqr(p),Sqr(MCha(gI2)),Sqr(MHpm(gI1
      )))*Conj(CpUChiChaconjHpmPR(gO2,gI2,gI1))*CpUChiChaconjHpmPR(gO1,gI2,gI1)));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,3,B1(Sqr(p),Sqr(MChi(gI2)),Sqr(Mhh(gI1)
      ))*Conj(CpChiUChihhPR(gI2,gO2,gI1))*CpChiUChihhPR(gI2,gO1,gI1)));
   result += -0.5*SUM(gI1,0,3,SUM(gI2,0,1,B1(Sqr(p),Sqr(MChi(gI1)),Sqr(MAh(gI2)
      ))*Conj(CpChiUChiAhPR(gI1,gO2,gI2))*CpChiUChiAhPR(gI1,gO1,gI2)));
   result += -1.5*SUM(gI2,0,1,B1(Sqr(p),Sqr(MFb),Sqr(MSb(gI2)))*Conj(
      CpbarFbUChiSbPR(gO2,gI2))*CpbarFbUChiSbPR(gO1,gI2));
   result += -1.5*SUM(gI2,0,1,B1(Sqr(p),Sqr(MFc),Sqr(MSc(gI2)))*Conj(
      CpbarFcUChiScPR(gO2,gI2))*CpbarFcUChiScPR(gO1,gI2));
   result += -1.5*SUM(gI2,0,1,B1(Sqr(p),Sqr(MFd),Sqr(MSd(gI2)))*Conj(
      CpbarFdUChiSdPR(gO2,gI2))*CpbarFdUChiSdPR(gO1,gI2));
   result += -0.5*SUM(gI2,0,1,B1(Sqr(p),Sqr(MFe),Sqr(MSe(gI2)))*Conj(
      CpbarFeUChiSePR(gO2,gI2))*CpbarFeUChiSePR(gO1,gI2));
   result += -0.5*SUM(gI2,0,1,B1(Sqr(p),Sqr(MFm),Sqr(MSm(gI2)))*Conj(
      CpbarFmUChiSmPR(gO2,gI2))*CpbarFmUChiSmPR(gO1,gI2));
   result += -1.5*SUM(gI2,0,1,B1(Sqr(p),Sqr(MFs),Sqr(MSs(gI2)))*Conj(
      CpbarFsUChiSsPR(gO2,gI2))*CpbarFsUChiSsPR(gO1,gI2));
   result += -0.5*SUM(gI2,0,1,B1(Sqr(p),Sqr(MFtau),Sqr(MStau(gI2)))*Conj(
      CpbarFtauUChiStauPR(gO2,gI2))*CpbarFtauUChiStauPR(gO1,gI2));
   result += -1.5*SUM(gI2,0,1,B1(Sqr(p),Sqr(MFt),Sqr(MSt(gI2)))*Conj(
      CpbarFtUChiStPR(gO2,gI2))*CpbarFtUChiStPR(gO1,gI2));
   result += -1.5*SUM(gI2,0,1,B1(Sqr(p),Sqr(MFu),Sqr(MSu(gI2)))*Conj(
      CpbarFuUChiSuPR(gO2,gI2))*CpbarFuUChiSuPR(gO1,gI2));
   result += -SUM(gI2,0,1,B1(Sqr(p),Sqr(MCha(gI2)),Sqr(MVWm))*Conj(
      CpUChiChaconjVWmPL(gO2,gI2))*CpUChiChaconjVWmPL(gO1,gI2));
   result += -SUM(gI2,0,3,B1(Sqr(p),Sqr(MChi(gI2)),Sqr(MVZ))*Conj(CpChiUChiVZPR
      (gI2,gO2))*CpChiUChiVZPR(gI2,gO1));

   return result * oneOver16PiSqr;

}

Eigen::Matrix<std::complex<double>,4,4> CLASSNAME::self_energy_Chi_1loop_PR(double p) const
{
   Eigen::Matrix<std::complex<double>,4,4> self_energy;

   for (int i = 0; i < 4; i++)
      for (int k = 0; k < 4; k++)
         self_energy(i, k) = self_energy_Chi_1loop_PR(p, i, k);

   return self_energy;
}

std::complex<double> CLASSNAME::self_energy_Chi_1loop_PL(double p , int gO1, int gO2) const
{
   std::complex<double> result;

   result += -0.5*B1(Sqr(p),Sqr(MFve),Sqr(MSveL))*Conj(CpbarFveUChiSveLPL(gO2))
      *CpbarFveUChiSveLPL(gO1);
   result += -0.5*B1(Sqr(p),Sqr(MFvm),Sqr(MSvmL))*Conj(CpbarFvmUChiSvmLPL(gO2))
      *CpbarFvmUChiSvmLPL(gO1);
   result += -0.5*B1(Sqr(p),Sqr(MFvt),Sqr(MSvtL))*Conj(CpbarFvtUChiSvtLPL(gO2))
      *CpbarFvtUChiSvtLPL(gO1);
   result += -0.5*B1(Sqr(p),Sqr(MFve),Sqr(MSveL))*Conj(CpUChiFveconjSveLPL(gO2)
      )*CpUChiFveconjSveLPL(gO1);
   result += -0.5*B1(Sqr(p),Sqr(MFvm),Sqr(MSvmL))*Conj(CpUChiFvmconjSvmLPL(gO2)
      )*CpUChiFvmconjSvmLPL(gO1);
   result += -0.5*B1(Sqr(p),Sqr(MFvt),Sqr(MSvtL))*Conj(CpUChiFvtconjSvtLPL(gO2)
      )*CpUChiFvtconjSvtLPL(gO1);
   result += -SUM(gI1,0,1,B1(Sqr(p),Sqr(MCha(gI1)),Sqr(MVWm))*Conj(
      CpbarChaUChiVWmPL(gI1,gO2))*CpbarChaUChiVWmPL(gI1,gO1));
   result += -1.5*SUM(gI1,0,1,B1(Sqr(p),Sqr(MFb),Sqr(MSb(gI1)))*Conj(
      CpUChiFbconjSbPL(gO2,gI1))*CpUChiFbconjSbPL(gO1,gI1));
   result += -1.5*SUM(gI1,0,1,B1(Sqr(p),Sqr(MFc),Sqr(MSc(gI1)))*Conj(
      CpUChiFcconjScPL(gO2,gI1))*CpUChiFcconjScPL(gO1,gI1));
   result += -1.5*SUM(gI1,0,1,B1(Sqr(p),Sqr(MFd),Sqr(MSd(gI1)))*Conj(
      CpUChiFdconjSdPL(gO2,gI1))*CpUChiFdconjSdPL(gO1,gI1));
   result += -0.5*SUM(gI1,0,1,B1(Sqr(p),Sqr(MFe),Sqr(MSe(gI1)))*Conj(
      CpUChiFeconjSePL(gO2,gI1))*CpUChiFeconjSePL(gO1,gI1));
   result += -0.5*SUM(gI1,0,1,B1(Sqr(p),Sqr(MFm),Sqr(MSm(gI1)))*Conj(
      CpUChiFmconjSmPL(gO2,gI1))*CpUChiFmconjSmPL(gO1,gI1));
   result += -1.5*SUM(gI1,0,1,B1(Sqr(p),Sqr(MFs),Sqr(MSs(gI1)))*Conj(
      CpUChiFsconjSsPL(gO2,gI1))*CpUChiFsconjSsPL(gO1,gI1));
   result += -0.5*SUM(gI1,0,1,B1(Sqr(p),Sqr(MFtau),Sqr(MStau(gI1)))*Conj(
      CpUChiFtauconjStauPL(gO2,gI1))*CpUChiFtauconjStauPL(gO1,gI1));
   result += -1.5*SUM(gI1,0,1,B1(Sqr(p),Sqr(MFt),Sqr(MSt(gI1)))*Conj(
      CpUChiFtconjStPL(gO2,gI1))*CpUChiFtconjStPL(gO1,gI1));
   result += -1.5*SUM(gI1,0,1,B1(Sqr(p),Sqr(MFu),Sqr(MSu(gI1)))*Conj(
      CpUChiFuconjSuPL(gO2,gI1))*CpUChiFuconjSuPL(gO1,gI1));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,1,B1(Sqr(p),Sqr(MCha(gI1)),Sqr(MHpm(gI2
      )))*Conj(CpbarChaUChiHpmPL(gI1,gO2,gI2))*CpbarChaUChiHpmPL(gI1,gO1,gI2)));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,1,B1(Sqr(p),Sqr(MCha(gI2)),Sqr(MHpm(gI1
      )))*Conj(CpUChiChaconjHpmPL(gO2,gI2,gI1))*CpUChiChaconjHpmPL(gO1,gI2,gI1)));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,3,B1(Sqr(p),Sqr(MChi(gI2)),Sqr(Mhh(gI1)
      ))*Conj(CpChiUChihhPL(gI2,gO2,gI1))*CpChiUChihhPL(gI2,gO1,gI1)));
   result += -0.5*SUM(gI1,0,3,SUM(gI2,0,1,B1(Sqr(p),Sqr(MChi(gI1)),Sqr(MAh(gI2)
      ))*Conj(CpChiUChiAhPL(gI1,gO2,gI2))*CpChiUChiAhPL(gI1,gO1,gI2)));
   result += -1.5*SUM(gI2,0,1,B1(Sqr(p),Sqr(MFb),Sqr(MSb(gI2)))*Conj(
      CpbarFbUChiSbPL(gO2,gI2))*CpbarFbUChiSbPL(gO1,gI2));
   result += -1.5*SUM(gI2,0,1,B1(Sqr(p),Sqr(MFc),Sqr(MSc(gI2)))*Conj(
      CpbarFcUChiScPL(gO2,gI2))*CpbarFcUChiScPL(gO1,gI2));
   result += -1.5*SUM(gI2,0,1,B1(Sqr(p),Sqr(MFd),Sqr(MSd(gI2)))*Conj(
      CpbarFdUChiSdPL(gO2,gI2))*CpbarFdUChiSdPL(gO1,gI2));
   result += -0.5*SUM(gI2,0,1,B1(Sqr(p),Sqr(MFe),Sqr(MSe(gI2)))*Conj(
      CpbarFeUChiSePL(gO2,gI2))*CpbarFeUChiSePL(gO1,gI2));
   result += -0.5*SUM(gI2,0,1,B1(Sqr(p),Sqr(MFm),Sqr(MSm(gI2)))*Conj(
      CpbarFmUChiSmPL(gO2,gI2))*CpbarFmUChiSmPL(gO1,gI2));
   result += -1.5*SUM(gI2,0,1,B1(Sqr(p),Sqr(MFs),Sqr(MSs(gI2)))*Conj(
      CpbarFsUChiSsPL(gO2,gI2))*CpbarFsUChiSsPL(gO1,gI2));
   result += -0.5*SUM(gI2,0,1,B1(Sqr(p),Sqr(MFtau),Sqr(MStau(gI2)))*Conj(
      CpbarFtauUChiStauPL(gO2,gI2))*CpbarFtauUChiStauPL(gO1,gI2));
   result += -1.5*SUM(gI2,0,1,B1(Sqr(p),Sqr(MFt),Sqr(MSt(gI2)))*Conj(
      CpbarFtUChiStPL(gO2,gI2))*CpbarFtUChiStPL(gO1,gI2));
   result += -1.5*SUM(gI2,0,1,B1(Sqr(p),Sqr(MFu),Sqr(MSu(gI2)))*Conj(
      CpbarFuUChiSuPL(gO2,gI2))*CpbarFuUChiSuPL(gO1,gI2));
   result += -SUM(gI2,0,1,B1(Sqr(p),Sqr(MCha(gI2)),Sqr(MVWm))*Conj(
      CpUChiChaconjVWmPR(gO2,gI2))*CpUChiChaconjVWmPR(gO1,gI2));
   result += -SUM(gI2,0,3,B1(Sqr(p),Sqr(MChi(gI2)),Sqr(MVZ))*Conj(CpChiUChiVZPL
      (gI2,gO2))*CpChiUChiVZPL(gI2,gO1));

   return result * oneOver16PiSqr;

}

Eigen::Matrix<std::complex<double>,4,4> CLASSNAME::self_energy_Chi_1loop_PL(double p) const
{
   Eigen::Matrix<std::complex<double>,4,4> self_energy;

   for (int i = 0; i < 4; i++)
      for (int k = 0; k < 4; k++)
         self_energy(i, k) = self_energy_Chi_1loop_PL(p, i, k);

   return self_energy;
}

std::complex<double> CLASSNAME::self_energy_Cha_1loop_1(double p , int gO1, int gO2) const
{
   std::complex<double> result;

   result += MFe*B0(Sqr(p),Sqr(MFe),Sqr(MSveL))*Conj(CpbarUChaFeconjSveLPL(gO2)
      )*CpbarUChaFeconjSveLPR(gO1);
   result += MFm*B0(Sqr(p),Sqr(MFm),Sqr(MSvmL))*Conj(CpbarUChaFmconjSvmLPL(gO2)
      )*CpbarUChaFmconjSvmLPR(gO1);
   result += MFtau*B0(Sqr(p),Sqr(MFtau),Sqr(MSvtL))*Conj(
      CpbarUChaFtauconjSvtLPL(gO2))*CpbarUChaFtauconjSvtLPR(gO1);
   result += 3*MFb*SUM(gI1,0,1,B0(Sqr(p),Sqr(MFb),Sqr(MSt(gI1)))*Conj(
      CpbarUChaFbconjStPL(gO2,gI1))*CpbarUChaFbconjStPR(gO1,gI1));
   result += 3*MFd*SUM(gI1,0,1,B0(Sqr(p),Sqr(MFd),Sqr(MSu(gI1)))*Conj(
      CpbarUChaFdconjSuPL(gO2,gI1))*CpbarUChaFdconjSuPR(gO1,gI1));
   result += 3*MFs*SUM(gI1,0,1,B0(Sqr(p),Sqr(MFs),Sqr(MSc(gI1)))*Conj(
      CpbarUChaFsconjScPL(gO2,gI1))*CpbarUChaFsconjScPR(gO1,gI1));
   result += SUM(gI1,0,1,MCha(gI1)*SUM(gI2,0,1,B0(Sqr(p),Sqr(MCha(gI1)),Sqr(MAh
      (gI2)))*Conj(CpbarUChaChaAhPL(gO2,gI1,gI2))*CpbarUChaChaAhPR(gO1,gI1,gI2)));
   result += SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(MCha(gI2)),Sqr(Mhh(gI1)))*
      Conj(CpbarUChaChahhPL(gO2,gI2,gI1))*CpbarUChaChahhPR(gO1,gI2,gI1)*MCha(gI2))
      );
   result += SUM(gI1,0,1,SUM(gI2,0,3,B0(Sqr(p),Sqr(MChi(gI2)),Sqr(MHpm(gI1)))*
      Conj(CpbarUChaChiHpmPL(gO2,gI2,gI1))*CpbarUChaChiHpmPR(gO1,gI2,gI1)*MChi(gI2
      )));
   result += 3*MFc*SUM(gI2,0,1,B0(Sqr(p),Sqr(MFc),Sqr(MSs(gI2)))*Conj(
      CpbarFcbarUChaSsPL(gO2,gI2))*CpbarFcbarUChaSsPR(gO1,gI2));
   result += 3*MFt*SUM(gI2,0,1,B0(Sqr(p),Sqr(MFt),Sqr(MSb(gI2)))*Conj(
      CpbarFtbarUChaSbPL(gO2,gI2))*CpbarFtbarUChaSbPR(gO1,gI2));
   result += 3*MFu*SUM(gI2,0,1,B0(Sqr(p),Sqr(MFu),Sqr(MSd(gI2)))*Conj(
      CpbarFubarUChaSdPL(gO2,gI2))*CpbarFubarUChaSdPR(gO1,gI2));
   result += MFve*SUM(gI2,0,1,B0(Sqr(p),Sqr(MFve),Sqr(MSe(gI2)))*Conj(
      CpbarFvebarUChaSePL(gO2,gI2))*CpbarFvebarUChaSePR(gO1,gI2));
   result += MFvm*SUM(gI2,0,1,B0(Sqr(p),Sqr(MFvm),Sqr(MSm(gI2)))*Conj(
      CpbarFvmbarUChaSmPL(gO2,gI2))*CpbarFvmbarUChaSmPR(gO1,gI2));
   result += MFvt*SUM(gI2,0,1,B0(Sqr(p),Sqr(MFvt),Sqr(MStau(gI2)))*Conj(
      CpbarFvtbarUChaStauPL(gO2,gI2))*CpbarFvtbarUChaStauPR(gO1,gI2));
   result += -4*SUM(gI2,0,1,B0(Sqr(p),Sqr(MCha(gI2)),0)*Conj(CpbarUChaChaVPPR(
      gO2,gI2))*CpbarUChaChaVPPL(gO1,gI2)*MCha(gI2));
   result += -4*SUM(gI2,0,1,B0(Sqr(p),Sqr(MCha(gI2)),Sqr(MVZ))*Conj(
      CpbarUChaChaVZPR(gO2,gI2))*CpbarUChaChaVZPL(gO1,gI2)*MCha(gI2));
   result += -4*SUM(gI2,0,3,B0(Sqr(p),Sqr(MChi(gI2)),Sqr(MVWm))*Conj(
      CpbarUChaChiVWmPR(gO2,gI2))*CpbarUChaChiVWmPL(gO1,gI2)*MChi(gI2));

   return result * oneOver16PiSqr;

}

Eigen::Matrix<std::complex<double>,2,2> CLASSNAME::self_energy_Cha_1loop_1(double p) const
{
   Eigen::Matrix<std::complex<double>,2,2> self_energy;

   for (int i = 0; i < 2; i++)
      for (int k = 0; k < 2; k++)
         self_energy(i, k) = self_energy_Cha_1loop_1(p, i, k);

   return self_energy;
}

std::complex<double> CLASSNAME::self_energy_Cha_1loop_PR(double p , int gO1, int gO2) const
{
   std::complex<double> result;

   result += -0.5*B1(Sqr(p),Sqr(MFe),Sqr(MSveL))*Conj(CpbarUChaFeconjSveLPR(gO2
      ))*CpbarUChaFeconjSveLPR(gO1);
   result += -0.5*B1(Sqr(p),Sqr(MFm),Sqr(MSvmL))*Conj(CpbarUChaFmconjSvmLPR(gO2
      ))*CpbarUChaFmconjSvmLPR(gO1);
   result += -0.5*B1(Sqr(p),Sqr(MFtau),Sqr(MSvtL))*Conj(CpbarUChaFtauconjSvtLPR
      (gO2))*CpbarUChaFtauconjSvtLPR(gO1);
   result += -1.5*SUM(gI1,0,1,B1(Sqr(p),Sqr(MFb),Sqr(MSt(gI1)))*Conj(
      CpbarUChaFbconjStPR(gO2,gI1))*CpbarUChaFbconjStPR(gO1,gI1));
   result += -1.5*SUM(gI1,0,1,B1(Sqr(p),Sqr(MFd),Sqr(MSu(gI1)))*Conj(
      CpbarUChaFdconjSuPR(gO2,gI1))*CpbarUChaFdconjSuPR(gO1,gI1));
   result += -1.5*SUM(gI1,0,1,B1(Sqr(p),Sqr(MFs),Sqr(MSc(gI1)))*Conj(
      CpbarUChaFsconjScPR(gO2,gI1))*CpbarUChaFsconjScPR(gO1,gI1));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,1,B1(Sqr(p),Sqr(MCha(gI1)),Sqr(MAh(gI2)
      ))*Conj(CpbarUChaChaAhPR(gO2,gI1,gI2))*CpbarUChaChaAhPR(gO1,gI1,gI2)));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,1,B1(Sqr(p),Sqr(MCha(gI2)),Sqr(Mhh(gI1)
      ))*Conj(CpbarUChaChahhPR(gO2,gI2,gI1))*CpbarUChaChahhPR(gO1,gI2,gI1)));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,3,B1(Sqr(p),Sqr(MChi(gI2)),Sqr(MHpm(gI1
      )))*Conj(CpbarUChaChiHpmPR(gO2,gI2,gI1))*CpbarUChaChiHpmPR(gO1,gI2,gI1)));
   result += -1.5*SUM(gI2,0,1,B1(Sqr(p),Sqr(MFc),Sqr(MSs(gI2)))*Conj(
      CpbarFcbarUChaSsPR(gO2,gI2))*CpbarFcbarUChaSsPR(gO1,gI2));
   result += -1.5*SUM(gI2,0,1,B1(Sqr(p),Sqr(MFt),Sqr(MSb(gI2)))*Conj(
      CpbarFtbarUChaSbPR(gO2,gI2))*CpbarFtbarUChaSbPR(gO1,gI2));
   result += -1.5*SUM(gI2,0,1,B1(Sqr(p),Sqr(MFu),Sqr(MSd(gI2)))*Conj(
      CpbarFubarUChaSdPR(gO2,gI2))*CpbarFubarUChaSdPR(gO1,gI2));
   result += -0.5*SUM(gI2,0,1,B1(Sqr(p),Sqr(MFve),Sqr(MSe(gI2)))*Conj(
      CpbarFvebarUChaSePR(gO2,gI2))*CpbarFvebarUChaSePR(gO1,gI2));
   result += -0.5*SUM(gI2,0,1,B1(Sqr(p),Sqr(MFvm),Sqr(MSm(gI2)))*Conj(
      CpbarFvmbarUChaSmPR(gO2,gI2))*CpbarFvmbarUChaSmPR(gO1,gI2));
   result += -0.5*SUM(gI2,0,1,B1(Sqr(p),Sqr(MFvt),Sqr(MStau(gI2)))*Conj(
      CpbarFvtbarUChaStauPR(gO2,gI2))*CpbarFvtbarUChaStauPR(gO1,gI2));
   result += -SUM(gI2,0,1,B1(Sqr(p),Sqr(MCha(gI2)),0)*Conj(CpbarUChaChaVPPL(gO2
      ,gI2))*CpbarUChaChaVPPL(gO1,gI2));
   result += -SUM(gI2,0,1,B1(Sqr(p),Sqr(MCha(gI2)),Sqr(MVZ))*Conj(
      CpbarUChaChaVZPL(gO2,gI2))*CpbarUChaChaVZPL(gO1,gI2));
   result += -SUM(gI2,0,3,B1(Sqr(p),Sqr(MChi(gI2)),Sqr(MVWm))*Conj(
      CpbarUChaChiVWmPL(gO2,gI2))*CpbarUChaChiVWmPL(gO1,gI2));

   return result * oneOver16PiSqr;

}

Eigen::Matrix<std::complex<double>,2,2> CLASSNAME::self_energy_Cha_1loop_PR(double p) const
{
   Eigen::Matrix<std::complex<double>,2,2> self_energy;

   for (int i = 0; i < 2; i++)
      for (int k = 0; k < 2; k++)
         self_energy(i, k) = self_energy_Cha_1loop_PR(p, i, k);

   return self_energy;
}

std::complex<double> CLASSNAME::self_energy_Cha_1loop_PL(double p , int gO1, int gO2) const
{
   std::complex<double> result;

   result += -0.5*B1(Sqr(p),Sqr(MFe),Sqr(MSveL))*Conj(CpbarUChaFeconjSveLPL(gO2
      ))*CpbarUChaFeconjSveLPL(gO1);
   result += -0.5*B1(Sqr(p),Sqr(MFm),Sqr(MSvmL))*Conj(CpbarUChaFmconjSvmLPL(gO2
      ))*CpbarUChaFmconjSvmLPL(gO1);
   result += -0.5*B1(Sqr(p),Sqr(MFtau),Sqr(MSvtL))*Conj(CpbarUChaFtauconjSvtLPL
      (gO2))*CpbarUChaFtauconjSvtLPL(gO1);
   result += -1.5*SUM(gI1,0,1,B1(Sqr(p),Sqr(MFb),Sqr(MSt(gI1)))*Conj(
      CpbarUChaFbconjStPL(gO2,gI1))*CpbarUChaFbconjStPL(gO1,gI1));
   result += -1.5*SUM(gI1,0,1,B1(Sqr(p),Sqr(MFd),Sqr(MSu(gI1)))*Conj(
      CpbarUChaFdconjSuPL(gO2,gI1))*CpbarUChaFdconjSuPL(gO1,gI1));
   result += -1.5*SUM(gI1,0,1,B1(Sqr(p),Sqr(MFs),Sqr(MSc(gI1)))*Conj(
      CpbarUChaFsconjScPL(gO2,gI1))*CpbarUChaFsconjScPL(gO1,gI1));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,1,B1(Sqr(p),Sqr(MCha(gI1)),Sqr(MAh(gI2)
      ))*Conj(CpbarUChaChaAhPL(gO2,gI1,gI2))*CpbarUChaChaAhPL(gO1,gI1,gI2)));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,1,B1(Sqr(p),Sqr(MCha(gI2)),Sqr(Mhh(gI1)
      ))*Conj(CpbarUChaChahhPL(gO2,gI2,gI1))*CpbarUChaChahhPL(gO1,gI2,gI1)));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,3,B1(Sqr(p),Sqr(MChi(gI2)),Sqr(MHpm(gI1
      )))*Conj(CpbarUChaChiHpmPL(gO2,gI2,gI1))*CpbarUChaChiHpmPL(gO1,gI2,gI1)));
   result += -1.5*SUM(gI2,0,1,B1(Sqr(p),Sqr(MFc),Sqr(MSs(gI2)))*Conj(
      CpbarFcbarUChaSsPL(gO2,gI2))*CpbarFcbarUChaSsPL(gO1,gI2));
   result += -1.5*SUM(gI2,0,1,B1(Sqr(p),Sqr(MFt),Sqr(MSb(gI2)))*Conj(
      CpbarFtbarUChaSbPL(gO2,gI2))*CpbarFtbarUChaSbPL(gO1,gI2));
   result += -1.5*SUM(gI2,0,1,B1(Sqr(p),Sqr(MFu),Sqr(MSd(gI2)))*Conj(
      CpbarFubarUChaSdPL(gO2,gI2))*CpbarFubarUChaSdPL(gO1,gI2));
   result += -0.5*SUM(gI2,0,1,B1(Sqr(p),Sqr(MFve),Sqr(MSe(gI2)))*Conj(
      CpbarFvebarUChaSePL(gO2,gI2))*CpbarFvebarUChaSePL(gO1,gI2));
   result += -0.5*SUM(gI2,0,1,B1(Sqr(p),Sqr(MFvm),Sqr(MSm(gI2)))*Conj(
      CpbarFvmbarUChaSmPL(gO2,gI2))*CpbarFvmbarUChaSmPL(gO1,gI2));
   result += -0.5*SUM(gI2,0,1,B1(Sqr(p),Sqr(MFvt),Sqr(MStau(gI2)))*Conj(
      CpbarFvtbarUChaStauPL(gO2,gI2))*CpbarFvtbarUChaStauPL(gO1,gI2));
   result += -SUM(gI2,0,1,B1(Sqr(p),Sqr(MCha(gI2)),0)*Conj(CpbarUChaChaVPPR(gO2
      ,gI2))*CpbarUChaChaVPPR(gO1,gI2));
   result += -SUM(gI2,0,1,B1(Sqr(p),Sqr(MCha(gI2)),Sqr(MVZ))*Conj(
      CpbarUChaChaVZPR(gO2,gI2))*CpbarUChaChaVZPR(gO1,gI2));
   result += -SUM(gI2,0,3,B1(Sqr(p),Sqr(MChi(gI2)),Sqr(MVWm))*Conj(
      CpbarUChaChiVWmPR(gO2,gI2))*CpbarUChaChiVWmPR(gO1,gI2));

   return result * oneOver16PiSqr;

}

Eigen::Matrix<std::complex<double>,2,2> CLASSNAME::self_energy_Cha_1loop_PL(double p) const
{
   Eigen::Matrix<std::complex<double>,2,2> self_energy;

   for (int i = 0; i < 2; i++)
      for (int k = 0; k < 2; k++)
         self_energy(i, k) = self_energy_Cha_1loop_PL(p, i, k);

   return self_energy;
}

std::complex<double> CLASSNAME::self_energy_Glu_1loop_1(double p ) const
{
   std::complex<double> result;

   result += -12*MGlu*B0(Sqr(p),Sqr(MGlu),0)*Conj(CpGluGluVGPR())*CpGluGluVGPL(
      );
   result += 0.5*MFb*SUM(gI1,0,1,B0(Sqr(p),Sqr(MFb),Sqr(MSb(gI1)))*Conj(
      CpGluFbconjSbPL(gI1))*CpGluFbconjSbPR(gI1));
   result += 0.5*MFc*SUM(gI1,0,1,B0(Sqr(p),Sqr(MFc),Sqr(MSc(gI1)))*Conj(
      CpGluFcconjScPL(gI1))*CpGluFcconjScPR(gI1));
   result += 0.5*MFd*SUM(gI1,0,1,B0(Sqr(p),Sqr(MFd),Sqr(MSd(gI1)))*Conj(
      CpGluFdconjSdPL(gI1))*CpGluFdconjSdPR(gI1));
   result += 0.5*MFs*SUM(gI1,0,1,B0(Sqr(p),Sqr(MFs),Sqr(MSs(gI1)))*Conj(
      CpGluFsconjSsPL(gI1))*CpGluFsconjSsPR(gI1));
   result += 0.5*MFt*SUM(gI1,0,1,B0(Sqr(p),Sqr(MFt),Sqr(MSt(gI1)))*Conj(
      CpGluFtconjStPL(gI1))*CpGluFtconjStPR(gI1));
   result += 0.5*MFu*SUM(gI1,0,1,B0(Sqr(p),Sqr(MFu),Sqr(MSu(gI1)))*Conj(
      CpGluFuconjSuPL(gI1))*CpGluFuconjSuPR(gI1));
   result += 0.5*MFb*SUM(gI2,0,1,B0(Sqr(p),Sqr(MFb),Sqr(MSb(gI2)))*Conj(
      CpbarFbGluSbPL(gI2))*CpbarFbGluSbPR(gI2));
   result += 0.5*MFc*SUM(gI2,0,1,B0(Sqr(p),Sqr(MFc),Sqr(MSc(gI2)))*Conj(
      CpbarFcGluScPL(gI2))*CpbarFcGluScPR(gI2));
   result += 0.5*MFd*SUM(gI2,0,1,B0(Sqr(p),Sqr(MFd),Sqr(MSd(gI2)))*Conj(
      CpbarFdGluSdPL(gI2))*CpbarFdGluSdPR(gI2));
   result += 0.5*MFs*SUM(gI2,0,1,B0(Sqr(p),Sqr(MFs),Sqr(MSs(gI2)))*Conj(
      CpbarFsGluSsPL(gI2))*CpbarFsGluSsPR(gI2));
   result += 0.5*MFt*SUM(gI2,0,1,B0(Sqr(p),Sqr(MFt),Sqr(MSt(gI2)))*Conj(
      CpbarFtGluStPL(gI2))*CpbarFtGluStPR(gI2));
   result += 0.5*MFu*SUM(gI2,0,1,B0(Sqr(p),Sqr(MFu),Sqr(MSu(gI2)))*Conj(
      CpbarFuGluSuPL(gI2))*CpbarFuGluSuPR(gI2));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Glu_1loop_PR(double p ) const
{
   std::complex<double> result;

   result += -3*AbsSqr(CpGluGluVGPL())*B1(Sqr(p),Sqr(MGlu),0);
   result += -0.25*SUM(gI1,0,1,AbsSqr(CpGluFbconjSbPR(gI1))*B1(Sqr(p),Sqr(MFb),
      Sqr(MSb(gI1))));
   result += -0.25*SUM(gI1,0,1,AbsSqr(CpGluFcconjScPR(gI1))*B1(Sqr(p),Sqr(MFc),
      Sqr(MSc(gI1))));
   result += -0.25*SUM(gI1,0,1,AbsSqr(CpGluFdconjSdPR(gI1))*B1(Sqr(p),Sqr(MFd),
      Sqr(MSd(gI1))));
   result += -0.25*SUM(gI1,0,1,AbsSqr(CpGluFsconjSsPR(gI1))*B1(Sqr(p),Sqr(MFs),
      Sqr(MSs(gI1))));
   result += -0.25*SUM(gI1,0,1,AbsSqr(CpGluFtconjStPR(gI1))*B1(Sqr(p),Sqr(MFt),
      Sqr(MSt(gI1))));
   result += -0.25*SUM(gI1,0,1,AbsSqr(CpGluFuconjSuPR(gI1))*B1(Sqr(p),Sqr(MFu),
      Sqr(MSu(gI1))));
   result += -0.25*SUM(gI2,0,1,AbsSqr(CpbarFbGluSbPR(gI2))*B1(Sqr(p),Sqr(MFb),
      Sqr(MSb(gI2))));
   result += -0.25*SUM(gI2,0,1,AbsSqr(CpbarFcGluScPR(gI2))*B1(Sqr(p),Sqr(MFc),
      Sqr(MSc(gI2))));
   result += -0.25*SUM(gI2,0,1,AbsSqr(CpbarFdGluSdPR(gI2))*B1(Sqr(p),Sqr(MFd),
      Sqr(MSd(gI2))));
   result += -0.25*SUM(gI2,0,1,AbsSqr(CpbarFsGluSsPR(gI2))*B1(Sqr(p),Sqr(MFs),
      Sqr(MSs(gI2))));
   result += -0.25*SUM(gI2,0,1,AbsSqr(CpbarFtGluStPR(gI2))*B1(Sqr(p),Sqr(MFt),
      Sqr(MSt(gI2))));
   result += -0.25*SUM(gI2,0,1,AbsSqr(CpbarFuGluSuPR(gI2))*B1(Sqr(p),Sqr(MFu),
      Sqr(MSu(gI2))));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Glu_1loop_PL(double p ) const
{
   std::complex<double> result;

   result += -3*AbsSqr(CpGluGluVGPR())*B1(Sqr(p),Sqr(MGlu),0);
   result += -0.25*SUM(gI1,0,1,AbsSqr(CpGluFbconjSbPL(gI1))*B1(Sqr(p),Sqr(MFb),
      Sqr(MSb(gI1))));
   result += -0.25*SUM(gI1,0,1,AbsSqr(CpGluFcconjScPL(gI1))*B1(Sqr(p),Sqr(MFc),
      Sqr(MSc(gI1))));
   result += -0.25*SUM(gI1,0,1,AbsSqr(CpGluFdconjSdPL(gI1))*B1(Sqr(p),Sqr(MFd),
      Sqr(MSd(gI1))));
   result += -0.25*SUM(gI1,0,1,AbsSqr(CpGluFsconjSsPL(gI1))*B1(Sqr(p),Sqr(MFs),
      Sqr(MSs(gI1))));
   result += -0.25*SUM(gI1,0,1,AbsSqr(CpGluFtconjStPL(gI1))*B1(Sqr(p),Sqr(MFt),
      Sqr(MSt(gI1))));
   result += -0.25*SUM(gI1,0,1,AbsSqr(CpGluFuconjSuPL(gI1))*B1(Sqr(p),Sqr(MFu),
      Sqr(MSu(gI1))));
   result += -0.25*SUM(gI2,0,1,AbsSqr(CpbarFbGluSbPL(gI2))*B1(Sqr(p),Sqr(MFb),
      Sqr(MSb(gI2))));
   result += -0.25*SUM(gI2,0,1,AbsSqr(CpbarFcGluScPL(gI2))*B1(Sqr(p),Sqr(MFc),
      Sqr(MSc(gI2))));
   result += -0.25*SUM(gI2,0,1,AbsSqr(CpbarFdGluSdPL(gI2))*B1(Sqr(p),Sqr(MFd),
      Sqr(MSd(gI2))));
   result += -0.25*SUM(gI2,0,1,AbsSqr(CpbarFsGluSsPL(gI2))*B1(Sqr(p),Sqr(MFs),
      Sqr(MSs(gI2))));
   result += -0.25*SUM(gI2,0,1,AbsSqr(CpbarFtGluStPL(gI2))*B1(Sqr(p),Sqr(MFt),
      Sqr(MSt(gI2))));
   result += -0.25*SUM(gI2,0,1,AbsSqr(CpbarFuGluSuPL(gI2))*B1(Sqr(p),Sqr(MFu),
      Sqr(MSu(gI2))));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fd_1loop_1(double p ) const
{
   std::complex<double> result;

   result += -5.333333333333333*MFd*B0(Sqr(p),Sqr(MFd),0)*Conj(CpbarFdFdVGPR())
      *CpbarFdFdVGPL();
   result += -4*MFd*B0(Sqr(p),Sqr(MFd),0)*Conj(CpbarFdFdVPPR())*CpbarFdFdVPPL()
      ;
   result += -4*MFd*B0(Sqr(p),Sqr(MFd),Sqr(MVZ))*Conj(CpbarFdFdVZPR())*
      CpbarFdFdVZPL();
   result += -4*MFu*B0(Sqr(p),Sqr(MFu),Sqr(MVWm))*Conj(CpbarFdFuVWmPR())*
      CpbarFdFuVWmPL();
   result += MFd*SUM(gI1,0,1,B0(Sqr(p),Sqr(MFd),Sqr(Mhh(gI1)))*Conj(
      CpbarFdFdhhPL(gI1))*CpbarFdFdhhPR(gI1));
   result += MFu*SUM(gI1,0,1,B0(Sqr(p),Sqr(MFu),Sqr(MHpm(gI1)))*Conj(
      CpbarFdFuHpmPL(gI1))*CpbarFdFuHpmPR(gI1));
   result += 1.3333333333333333*MGlu*SUM(gI1,0,1,B0(Sqr(p),Sqr(MGlu),Sqr(MSd(
      gI1)))*Conj(CpbarFdGluSdPL(gI1))*CpbarFdGluSdPR(gI1));
   result += SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(MCha(gI2)),Sqr(MSu(gI1)))*
      Conj(CpbarFdChaSuPL(gI2,gI1))*CpbarFdChaSuPR(gI2,gI1)*MCha(gI2)));
   result += SUM(gI1,0,1,SUM(gI2,0,3,B0(Sqr(p),Sqr(MChi(gI2)),Sqr(MSd(gI1)))*
      Conj(CpbarFdChiSdPL(gI2,gI1))*CpbarFdChiSdPR(gI2,gI1)*MChi(gI2)));
   result += MFd*SUM(gI2,0,1,B0(Sqr(p),Sqr(MFd),Sqr(MAh(gI2)))*Conj(
      CpbarFdFdAhPL(gI2))*CpbarFdFdAhPR(gI2));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fd_1loop_PR(double p ) const
{
   std::complex<double> result;

   result += -1.3333333333333333*AbsSqr(CpbarFdFdVGPL())*B1(Sqr(p),Sqr(MFd),0);
   result += -(AbsSqr(CpbarFdFdVPPL())*B1(Sqr(p),Sqr(MFd),0));
   result += -(AbsSqr(CpbarFdFdVZPL())*B1(Sqr(p),Sqr(MFd),Sqr(MVZ)));
   result += -(AbsSqr(CpbarFdFuVWmPL())*B1(Sqr(p),Sqr(MFu),Sqr(MVWm)));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFdFdhhPR(gI1))*B1(Sqr(p),Sqr(MFd),Sqr
      (Mhh(gI1))));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFdFuHpmPR(gI1))*B1(Sqr(p),Sqr(MFu),
      Sqr(MHpm(gI1))));
   result += -0.6666666666666666*SUM(gI1,0,1,AbsSqr(CpbarFdGluSdPR(gI1))*B1(Sqr
      (p),Sqr(MGlu),Sqr(MSd(gI1))));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpbarFdChaSuPR(gI2,gI1))*B1(
      Sqr(p),Sqr(MCha(gI2)),Sqr(MSu(gI1)))));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,3,AbsSqr(CpbarFdChiSdPR(gI2,gI1))*B1(
      Sqr(p),Sqr(MChi(gI2)),Sqr(MSd(gI1)))));
   result += -0.5*SUM(gI2,0,1,AbsSqr(CpbarFdFdAhPR(gI2))*B1(Sqr(p),Sqr(MFd),Sqr
      (MAh(gI2))));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fd_1loop_PL(double p ) const
{
   std::complex<double> result;

   result += -1.3333333333333333*AbsSqr(CpbarFdFdVGPR())*B1(Sqr(p),Sqr(MFd),0);
   result += -(AbsSqr(CpbarFdFdVPPR())*B1(Sqr(p),Sqr(MFd),0));
   result += -(AbsSqr(CpbarFdFdVZPR())*B1(Sqr(p),Sqr(MFd),Sqr(MVZ)));
   result += -(AbsSqr(CpbarFdFuVWmPR())*B1(Sqr(p),Sqr(MFu),Sqr(MVWm)));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFdFdhhPL(gI1))*B1(Sqr(p),Sqr(MFd),Sqr
      (Mhh(gI1))));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFdFuHpmPL(gI1))*B1(Sqr(p),Sqr(MFu),
      Sqr(MHpm(gI1))));
   result += -0.6666666666666666*SUM(gI1,0,1,AbsSqr(CpbarFdGluSdPL(gI1))*B1(Sqr
      (p),Sqr(MGlu),Sqr(MSd(gI1))));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpbarFdChaSuPL(gI2,gI1))*B1(
      Sqr(p),Sqr(MCha(gI2)),Sqr(MSu(gI1)))));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,3,AbsSqr(CpbarFdChiSdPL(gI2,gI1))*B1(
      Sqr(p),Sqr(MChi(gI2)),Sqr(MSd(gI1)))));
   result += -0.5*SUM(gI2,0,1,AbsSqr(CpbarFdFdAhPL(gI2))*B1(Sqr(p),Sqr(MFd),Sqr
      (MAh(gI2))));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fs_1loop_1(double p ) const
{
   std::complex<double> result;

   result += -4*MFc*B0(Sqr(p),Sqr(MFc),Sqr(MVWm))*Conj(CpbarFsFcVWmPR())*
      CpbarFsFcVWmPL();
   result += -5.333333333333333*MFs*B0(Sqr(p),Sqr(MFs),0)*Conj(CpbarFsFsVGPR())
      *CpbarFsFsVGPL();
   result += -4*MFs*B0(Sqr(p),Sqr(MFs),0)*Conj(CpbarFsFsVPPR())*CpbarFsFsVPPL()
      ;
   result += -4*MFs*B0(Sqr(p),Sqr(MFs),Sqr(MVZ))*Conj(CpbarFsFsVZPR())*
      CpbarFsFsVZPL();
   result += MFc*SUM(gI1,0,1,B0(Sqr(p),Sqr(MFc),Sqr(MHpm(gI1)))*Conj(
      CpbarFsFcHpmPL(gI1))*CpbarFsFcHpmPR(gI1));
   result += MFs*SUM(gI1,0,1,B0(Sqr(p),Sqr(MFs),Sqr(Mhh(gI1)))*Conj(
      CpbarFsFshhPL(gI1))*CpbarFsFshhPR(gI1));
   result += 1.3333333333333333*MGlu*SUM(gI1,0,1,B0(Sqr(p),Sqr(MGlu),Sqr(MSs(
      gI1)))*Conj(CpbarFsGluSsPL(gI1))*CpbarFsGluSsPR(gI1));
   result += SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(MCha(gI2)),Sqr(MSc(gI1)))*
      Conj(CpbarFsChaScPL(gI2,gI1))*CpbarFsChaScPR(gI2,gI1)*MCha(gI2)));
   result += SUM(gI1,0,1,SUM(gI2,0,3,B0(Sqr(p),Sqr(MChi(gI2)),Sqr(MSs(gI1)))*
      Conj(CpbarFsChiSsPL(gI2,gI1))*CpbarFsChiSsPR(gI2,gI1)*MChi(gI2)));
   result += MFs*SUM(gI2,0,1,B0(Sqr(p),Sqr(MFs),Sqr(MAh(gI2)))*Conj(
      CpbarFsFsAhPL(gI2))*CpbarFsFsAhPR(gI2));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fs_1loop_PR(double p ) const
{
   std::complex<double> result;

   result += -(AbsSqr(CpbarFsFcVWmPL())*B1(Sqr(p),Sqr(MFc),Sqr(MVWm)));
   result += -1.3333333333333333*AbsSqr(CpbarFsFsVGPL())*B1(Sqr(p),Sqr(MFs),0);
   result += -(AbsSqr(CpbarFsFsVPPL())*B1(Sqr(p),Sqr(MFs),0));
   result += -(AbsSqr(CpbarFsFsVZPL())*B1(Sqr(p),Sqr(MFs),Sqr(MVZ)));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFsFcHpmPR(gI1))*B1(Sqr(p),Sqr(MFc),
      Sqr(MHpm(gI1))));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFsFshhPR(gI1))*B1(Sqr(p),Sqr(MFs),Sqr
      (Mhh(gI1))));
   result += -0.6666666666666666*SUM(gI1,0,1,AbsSqr(CpbarFsGluSsPR(gI1))*B1(Sqr
      (p),Sqr(MGlu),Sqr(MSs(gI1))));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpbarFsChaScPR(gI2,gI1))*B1(
      Sqr(p),Sqr(MCha(gI2)),Sqr(MSc(gI1)))));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,3,AbsSqr(CpbarFsChiSsPR(gI2,gI1))*B1(
      Sqr(p),Sqr(MChi(gI2)),Sqr(MSs(gI1)))));
   result += -0.5*SUM(gI2,0,1,AbsSqr(CpbarFsFsAhPR(gI2))*B1(Sqr(p),Sqr(MFs),Sqr
      (MAh(gI2))));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fs_1loop_PL(double p ) const
{
   std::complex<double> result;

   result += -(AbsSqr(CpbarFsFcVWmPR())*B1(Sqr(p),Sqr(MFc),Sqr(MVWm)));
   result += -1.3333333333333333*AbsSqr(CpbarFsFsVGPR())*B1(Sqr(p),Sqr(MFs),0);
   result += -(AbsSqr(CpbarFsFsVPPR())*B1(Sqr(p),Sqr(MFs),0));
   result += -(AbsSqr(CpbarFsFsVZPR())*B1(Sqr(p),Sqr(MFs),Sqr(MVZ)));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFsFcHpmPL(gI1))*B1(Sqr(p),Sqr(MFc),
      Sqr(MHpm(gI1))));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFsFshhPL(gI1))*B1(Sqr(p),Sqr(MFs),Sqr
      (Mhh(gI1))));
   result += -0.6666666666666666*SUM(gI1,0,1,AbsSqr(CpbarFsGluSsPL(gI1))*B1(Sqr
      (p),Sqr(MGlu),Sqr(MSs(gI1))));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpbarFsChaScPL(gI2,gI1))*B1(
      Sqr(p),Sqr(MCha(gI2)),Sqr(MSc(gI1)))));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,3,AbsSqr(CpbarFsChiSsPL(gI2,gI1))*B1(
      Sqr(p),Sqr(MChi(gI2)),Sqr(MSs(gI1)))));
   result += -0.5*SUM(gI2,0,1,AbsSqr(CpbarFsFsAhPL(gI2))*B1(Sqr(p),Sqr(MFs),Sqr
      (MAh(gI2))));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fb_1loop_1(double p ) const
{
   std::complex<double> result;

   result += -5.333333333333333*MFb*B0(Sqr(p),Sqr(MFb),0)*Conj(CpbarFbFbVGPR())
      *CpbarFbFbVGPL();
   result += -4*MFb*B0(Sqr(p),Sqr(MFb),0)*Conj(CpbarFbFbVPPR())*CpbarFbFbVPPL()
      ;
   result += -4*MFb*B0(Sqr(p),Sqr(MFb),Sqr(MVZ))*Conj(CpbarFbFbVZPR())*
      CpbarFbFbVZPL();
   result += -4*MFt*B0(Sqr(p),Sqr(MFt),Sqr(MVWm))*Conj(CpbarFbFtVWmPR())*
      CpbarFbFtVWmPL();
   result += MFb*SUM(gI1,0,1,B0(Sqr(p),Sqr(MFb),Sqr(Mhh(gI1)))*Conj(
      CpbarFbFbhhPL(gI1))*CpbarFbFbhhPR(gI1));
   result += MFt*SUM(gI1,0,1,B0(Sqr(p),Sqr(MFt),Sqr(MHpm(gI1)))*Conj(
      CpbarFbFtHpmPL(gI1))*CpbarFbFtHpmPR(gI1));
   result += 1.3333333333333333*MGlu*SUM(gI1,0,1,B0(Sqr(p),Sqr(MGlu),Sqr(MSb(
      gI1)))*Conj(CpbarFbGluSbPL(gI1))*CpbarFbGluSbPR(gI1));
   result += SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(MCha(gI2)),Sqr(MSt(gI1)))*
      Conj(CpbarFbChaStPL(gI2,gI1))*CpbarFbChaStPR(gI2,gI1)*MCha(gI2)));
   result += SUM(gI1,0,1,SUM(gI2,0,3,B0(Sqr(p),Sqr(MChi(gI2)),Sqr(MSb(gI1)))*
      Conj(CpbarFbChiSbPL(gI2,gI1))*CpbarFbChiSbPR(gI2,gI1)*MChi(gI2)));
   result += MFb*SUM(gI2,0,1,B0(Sqr(p),Sqr(MFb),Sqr(MAh(gI2)))*Conj(
      CpbarFbFbAhPL(gI2))*CpbarFbFbAhPR(gI2));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fb_1loop_PR(double p ) const
{
   std::complex<double> result;

   result += -1.3333333333333333*AbsSqr(CpbarFbFbVGPL())*B1(Sqr(p),Sqr(MFb),0);
   result += -(AbsSqr(CpbarFbFbVPPL())*B1(Sqr(p),Sqr(MFb),0));
   result += -(AbsSqr(CpbarFbFbVZPL())*B1(Sqr(p),Sqr(MFb),Sqr(MVZ)));
   result += -(AbsSqr(CpbarFbFtVWmPL())*B1(Sqr(p),Sqr(MFt),Sqr(MVWm)));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFbFbhhPR(gI1))*B1(Sqr(p),Sqr(MFb),Sqr
      (Mhh(gI1))));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFbFtHpmPR(gI1))*B1(Sqr(p),Sqr(MFt),
      Sqr(MHpm(gI1))));
   result += -0.6666666666666666*SUM(gI1,0,1,AbsSqr(CpbarFbGluSbPR(gI1))*B1(Sqr
      (p),Sqr(MGlu),Sqr(MSb(gI1))));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpbarFbChaStPR(gI2,gI1))*B1(
      Sqr(p),Sqr(MCha(gI2)),Sqr(MSt(gI1)))));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,3,AbsSqr(CpbarFbChiSbPR(gI2,gI1))*B1(
      Sqr(p),Sqr(MChi(gI2)),Sqr(MSb(gI1)))));
   result += -0.5*SUM(gI2,0,1,AbsSqr(CpbarFbFbAhPR(gI2))*B1(Sqr(p),Sqr(MFb),Sqr
      (MAh(gI2))));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fb_1loop_PL(double p ) const
{
   std::complex<double> result;

   result += -1.3333333333333333*AbsSqr(CpbarFbFbVGPR())*B1(Sqr(p),Sqr(MFb),0);
   result += -(AbsSqr(CpbarFbFbVPPR())*B1(Sqr(p),Sqr(MFb),0));
   result += -(AbsSqr(CpbarFbFbVZPR())*B1(Sqr(p),Sqr(MFb),Sqr(MVZ)));
   result += -(AbsSqr(CpbarFbFtVWmPR())*B1(Sqr(p),Sqr(MFt),Sqr(MVWm)));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFbFbhhPL(gI1))*B1(Sqr(p),Sqr(MFb),Sqr
      (Mhh(gI1))));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFbFtHpmPL(gI1))*B1(Sqr(p),Sqr(MFt),
      Sqr(MHpm(gI1))));
   result += -0.6666666666666666*SUM(gI1,0,1,AbsSqr(CpbarFbGluSbPL(gI1))*B1(Sqr
      (p),Sqr(MGlu),Sqr(MSb(gI1))));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpbarFbChaStPL(gI2,gI1))*B1(
      Sqr(p),Sqr(MCha(gI2)),Sqr(MSt(gI1)))));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,3,AbsSqr(CpbarFbChiSbPL(gI2,gI1))*B1(
      Sqr(p),Sqr(MChi(gI2)),Sqr(MSb(gI1)))));
   result += -0.5*SUM(gI2,0,1,AbsSqr(CpbarFbFbAhPL(gI2))*B1(Sqr(p),Sqr(MFb),Sqr
      (MAh(gI2))));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fu_1loop_1(double p ) const
{
   std::complex<double> result;

   result += -4*MFd*B0(Sqr(p),Sqr(MFd),Sqr(MVWm))*Conj(CpbarFuFdconjVWmPR())*
      CpbarFuFdconjVWmPL();
   result += -5.333333333333333*MFu*B0(Sqr(p),Sqr(MFu),0)*Conj(CpbarFuFuVGPR())
      *CpbarFuFuVGPL();
   result += -4*MFu*B0(Sqr(p),Sqr(MFu),0)*Conj(CpbarFuFuVPPR())*CpbarFuFuVPPL()
      ;
   result += -4*MFu*B0(Sqr(p),Sqr(MFu),Sqr(MVZ))*Conj(CpbarFuFuVZPR())*
      CpbarFuFuVZPL();
   result += MFd*SUM(gI1,0,1,B0(Sqr(p),Sqr(MFd),Sqr(MHpm(gI1)))*Conj(
      CpbarFuFdconjHpmPL(gI1))*CpbarFuFdconjHpmPR(gI1));
   result += MFu*SUM(gI1,0,1,B0(Sqr(p),Sqr(MFu),Sqr(Mhh(gI1)))*Conj(
      CpbarFuFuhhPL(gI1))*CpbarFuFuhhPR(gI1));
   result += 1.3333333333333333*MGlu*SUM(gI1,0,1,B0(Sqr(p),Sqr(MGlu),Sqr(MSu(
      gI1)))*Conj(CpbarFuGluSuPL(gI1))*CpbarFuGluSuPR(gI1));
   result += SUM(gI1,0,1,MCha(gI1)*SUM(gI2,0,1,B0(Sqr(p),Sqr(MCha(gI1)),Sqr(MSd
      (gI2)))*Conj(CpbarFubarChaSdPL(gI1,gI2))*CpbarFubarChaSdPR(gI1,gI2)));
   result += SUM(gI1,0,1,SUM(gI2,0,3,B0(Sqr(p),Sqr(MChi(gI2)),Sqr(MSu(gI1)))*
      Conj(CpbarFuChiSuPL(gI2,gI1))*CpbarFuChiSuPR(gI2,gI1)*MChi(gI2)));
   result += MFu*SUM(gI2,0,1,B0(Sqr(p),Sqr(MFu),Sqr(MAh(gI2)))*Conj(
      CpbarFuFuAhPL(gI2))*CpbarFuFuAhPR(gI2));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fu_1loop_PR(double p ) const
{
   std::complex<double> result;

   result += -(AbsSqr(CpbarFuFdconjVWmPL())*B1(Sqr(p),Sqr(MFd),Sqr(MVWm)));
   result += -1.3333333333333333*AbsSqr(CpbarFuFuVGPL())*B1(Sqr(p),Sqr(MFu),0);
   result += -(AbsSqr(CpbarFuFuVPPL())*B1(Sqr(p),Sqr(MFu),0));
   result += -(AbsSqr(CpbarFuFuVZPL())*B1(Sqr(p),Sqr(MFu),Sqr(MVZ)));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFuFdconjHpmPR(gI1))*B1(Sqr(p),Sqr(MFd
      ),Sqr(MHpm(gI1))));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFuFuhhPR(gI1))*B1(Sqr(p),Sqr(MFu),Sqr
      (Mhh(gI1))));
   result += -0.6666666666666666*SUM(gI1,0,1,AbsSqr(CpbarFuGluSuPR(gI1))*B1(Sqr
      (p),Sqr(MGlu),Sqr(MSu(gI1))));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpbarFubarChaSdPR(gI1,gI2))*B1
      (Sqr(p),Sqr(MCha(gI1)),Sqr(MSd(gI2)))));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,3,AbsSqr(CpbarFuChiSuPR(gI2,gI1))*B1(
      Sqr(p),Sqr(MChi(gI2)),Sqr(MSu(gI1)))));
   result += -0.5*SUM(gI2,0,1,AbsSqr(CpbarFuFuAhPR(gI2))*B1(Sqr(p),Sqr(MFu),Sqr
      (MAh(gI2))));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fu_1loop_PL(double p ) const
{
   std::complex<double> result;

   result += -(AbsSqr(CpbarFuFdconjVWmPR())*B1(Sqr(p),Sqr(MFd),Sqr(MVWm)));
   result += -1.3333333333333333*AbsSqr(CpbarFuFuVGPR())*B1(Sqr(p),Sqr(MFu),0);
   result += -(AbsSqr(CpbarFuFuVPPR())*B1(Sqr(p),Sqr(MFu),0));
   result += -(AbsSqr(CpbarFuFuVZPR())*B1(Sqr(p),Sqr(MFu),Sqr(MVZ)));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFuFdconjHpmPL(gI1))*B1(Sqr(p),Sqr(MFd
      ),Sqr(MHpm(gI1))));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFuFuhhPL(gI1))*B1(Sqr(p),Sqr(MFu),Sqr
      (Mhh(gI1))));
   result += -0.6666666666666666*SUM(gI1,0,1,AbsSqr(CpbarFuGluSuPL(gI1))*B1(Sqr
      (p),Sqr(MGlu),Sqr(MSu(gI1))));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpbarFubarChaSdPL(gI1,gI2))*B1
      (Sqr(p),Sqr(MCha(gI1)),Sqr(MSd(gI2)))));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,3,AbsSqr(CpbarFuChiSuPL(gI2,gI1))*B1(
      Sqr(p),Sqr(MChi(gI2)),Sqr(MSu(gI1)))));
   result += -0.5*SUM(gI2,0,1,AbsSqr(CpbarFuFuAhPL(gI2))*B1(Sqr(p),Sqr(MFu),Sqr
      (MAh(gI2))));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fc_1loop_1(double p ) const
{
   std::complex<double> result;

   result += -5.333333333333333*MFc*B0(Sqr(p),Sqr(MFc),0)*Conj(CpbarFcFcVGPR())
      *CpbarFcFcVGPL();
   result += -4*MFc*B0(Sqr(p),Sqr(MFc),0)*Conj(CpbarFcFcVPPR())*CpbarFcFcVPPL()
      ;
   result += -4*MFc*B0(Sqr(p),Sqr(MFc),Sqr(MVZ))*Conj(CpbarFcFcVZPR())*
      CpbarFcFcVZPL();
   result += -4*MFs*B0(Sqr(p),Sqr(MFs),Sqr(MVWm))*Conj(CpbarFcFsconjVWmPR())*
      CpbarFcFsconjVWmPL();
   result += MFc*SUM(gI1,0,1,B0(Sqr(p),Sqr(MFc),Sqr(Mhh(gI1)))*Conj(
      CpbarFcFchhPL(gI1))*CpbarFcFchhPR(gI1));
   result += MFs*SUM(gI1,0,1,B0(Sqr(p),Sqr(MFs),Sqr(MHpm(gI1)))*Conj(
      CpbarFcFsconjHpmPL(gI1))*CpbarFcFsconjHpmPR(gI1));
   result += 1.3333333333333333*MGlu*SUM(gI1,0,1,B0(Sqr(p),Sqr(MGlu),Sqr(MSc(
      gI1)))*Conj(CpbarFcGluScPL(gI1))*CpbarFcGluScPR(gI1));
   result += SUM(gI1,0,1,MCha(gI1)*SUM(gI2,0,1,B0(Sqr(p),Sqr(MCha(gI1)),Sqr(MSs
      (gI2)))*Conj(CpbarFcbarChaSsPL(gI1,gI2))*CpbarFcbarChaSsPR(gI1,gI2)));
   result += SUM(gI1,0,1,SUM(gI2,0,3,B0(Sqr(p),Sqr(MChi(gI2)),Sqr(MSc(gI1)))*
      Conj(CpbarFcChiScPL(gI2,gI1))*CpbarFcChiScPR(gI2,gI1)*MChi(gI2)));
   result += MFc*SUM(gI2,0,1,B0(Sqr(p),Sqr(MFc),Sqr(MAh(gI2)))*Conj(
      CpbarFcFcAhPL(gI2))*CpbarFcFcAhPR(gI2));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fc_1loop_PR(double p ) const
{
   std::complex<double> result;

   result += -1.3333333333333333*AbsSqr(CpbarFcFcVGPL())*B1(Sqr(p),Sqr(MFc),0);
   result += -(AbsSqr(CpbarFcFcVPPL())*B1(Sqr(p),Sqr(MFc),0));
   result += -(AbsSqr(CpbarFcFcVZPL())*B1(Sqr(p),Sqr(MFc),Sqr(MVZ)));
   result += -(AbsSqr(CpbarFcFsconjVWmPL())*B1(Sqr(p),Sqr(MFs),Sqr(MVWm)));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFcFchhPR(gI1))*B1(Sqr(p),Sqr(MFc),Sqr
      (Mhh(gI1))));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFcFsconjHpmPR(gI1))*B1(Sqr(p),Sqr(MFs
      ),Sqr(MHpm(gI1))));
   result += -0.6666666666666666*SUM(gI1,0,1,AbsSqr(CpbarFcGluScPR(gI1))*B1(Sqr
      (p),Sqr(MGlu),Sqr(MSc(gI1))));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpbarFcbarChaSsPR(gI1,gI2))*B1
      (Sqr(p),Sqr(MCha(gI1)),Sqr(MSs(gI2)))));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,3,AbsSqr(CpbarFcChiScPR(gI2,gI1))*B1(
      Sqr(p),Sqr(MChi(gI2)),Sqr(MSc(gI1)))));
   result += -0.5*SUM(gI2,0,1,AbsSqr(CpbarFcFcAhPR(gI2))*B1(Sqr(p),Sqr(MFc),Sqr
      (MAh(gI2))));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fc_1loop_PL(double p ) const
{
   std::complex<double> result;

   result += -1.3333333333333333*AbsSqr(CpbarFcFcVGPR())*B1(Sqr(p),Sqr(MFc),0);
   result += -(AbsSqr(CpbarFcFcVPPR())*B1(Sqr(p),Sqr(MFc),0));
   result += -(AbsSqr(CpbarFcFcVZPR())*B1(Sqr(p),Sqr(MFc),Sqr(MVZ)));
   result += -(AbsSqr(CpbarFcFsconjVWmPR())*B1(Sqr(p),Sqr(MFs),Sqr(MVWm)));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFcFchhPL(gI1))*B1(Sqr(p),Sqr(MFc),Sqr
      (Mhh(gI1))));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFcFsconjHpmPL(gI1))*B1(Sqr(p),Sqr(MFs
      ),Sqr(MHpm(gI1))));
   result += -0.6666666666666666*SUM(gI1,0,1,AbsSqr(CpbarFcGluScPL(gI1))*B1(Sqr
      (p),Sqr(MGlu),Sqr(MSc(gI1))));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpbarFcbarChaSsPL(gI1,gI2))*B1
      (Sqr(p),Sqr(MCha(gI1)),Sqr(MSs(gI2)))));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,3,AbsSqr(CpbarFcChiScPL(gI2,gI1))*B1(
      Sqr(p),Sqr(MChi(gI2)),Sqr(MSc(gI1)))));
   result += -0.5*SUM(gI2,0,1,AbsSqr(CpbarFcFcAhPL(gI2))*B1(Sqr(p),Sqr(MFc),Sqr
      (MAh(gI2))));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Ft_1loop_1(double p ) const
{
   std::complex<double> result;

   result += -4*MFb*B0(Sqr(p),Sqr(MFb),Sqr(MVWm))*Conj(CpbarFtFbconjVWmPR())*
      CpbarFtFbconjVWmPL();
   result += -5.333333333333333*MFt*B0(Sqr(p),Sqr(MFt),0)*Conj(CpbarFtFtVGPR())
      *CpbarFtFtVGPL();
   result += -4*MFt*B0(Sqr(p),Sqr(MFt),0)*Conj(CpbarFtFtVPPR())*CpbarFtFtVPPL()
      ;
   result += -4*MFt*B0(Sqr(p),Sqr(MFt),Sqr(MVZ))*Conj(CpbarFtFtVZPR())*
      CpbarFtFtVZPL();
   result += MFb*SUM(gI1,0,1,B0(Sqr(p),Sqr(MFb),Sqr(MHpm(gI1)))*Conj(
      CpbarFtFbconjHpmPL(gI1))*CpbarFtFbconjHpmPR(gI1));
   result += MFt*SUM(gI1,0,1,B0(Sqr(p),Sqr(MFt),Sqr(Mhh(gI1)))*Conj(
      CpbarFtFthhPL(gI1))*CpbarFtFthhPR(gI1));
   result += 1.3333333333333333*MGlu*SUM(gI1,0,1,B0(Sqr(p),Sqr(MGlu),Sqr(MSt(
      gI1)))*Conj(CpbarFtGluStPL(gI1))*CpbarFtGluStPR(gI1));
   result += SUM(gI1,0,1,MCha(gI1)*SUM(gI2,0,1,B0(Sqr(p),Sqr(MCha(gI1)),Sqr(MSb
      (gI2)))*Conj(CpbarFtbarChaSbPL(gI1,gI2))*CpbarFtbarChaSbPR(gI1,gI2)));
   result += SUM(gI1,0,1,SUM(gI2,0,3,B0(Sqr(p),Sqr(MChi(gI2)),Sqr(MSt(gI1)))*
      Conj(CpbarFtChiStPL(gI2,gI1))*CpbarFtChiStPR(gI2,gI1)*MChi(gI2)));
   result += MFt*SUM(gI2,0,1,B0(Sqr(p),Sqr(MFt),Sqr(MAh(gI2)))*Conj(
      CpbarFtFtAhPL(gI2))*CpbarFtFtAhPR(gI2));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Ft_1loop_PR(double p ) const
{
   std::complex<double> result;

   result += -(AbsSqr(CpbarFtFbconjVWmPL())*B1(Sqr(p),Sqr(MFb),Sqr(MVWm)));
   result += -1.3333333333333333*AbsSqr(CpbarFtFtVGPL())*B1(Sqr(p),Sqr(MFt),0);
   result += -(AbsSqr(CpbarFtFtVPPL())*B1(Sqr(p),Sqr(MFt),0));
   result += -(AbsSqr(CpbarFtFtVZPL())*B1(Sqr(p),Sqr(MFt),Sqr(MVZ)));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFtFbconjHpmPR(gI1))*B1(Sqr(p),Sqr(MFb
      ),Sqr(MHpm(gI1))));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFtFthhPR(gI1))*B1(Sqr(p),Sqr(MFt),Sqr
      (Mhh(gI1))));
   result += -0.6666666666666666*SUM(gI1,0,1,AbsSqr(CpbarFtGluStPR(gI1))*B1(Sqr
      (p),Sqr(MGlu),Sqr(MSt(gI1))));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpbarFtbarChaSbPR(gI1,gI2))*B1
      (Sqr(p),Sqr(MCha(gI1)),Sqr(MSb(gI2)))));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,3,AbsSqr(CpbarFtChiStPR(gI2,gI1))*B1(
      Sqr(p),Sqr(MChi(gI2)),Sqr(MSt(gI1)))));
   result += -0.5*SUM(gI2,0,1,AbsSqr(CpbarFtFtAhPR(gI2))*B1(Sqr(p),Sqr(MFt),Sqr
      (MAh(gI2))));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Ft_1loop_PL(double p ) const
{
   std::complex<double> result;

   result += -(AbsSqr(CpbarFtFbconjVWmPR())*B1(Sqr(p),Sqr(MFb),Sqr(MVWm)));
   result += -1.3333333333333333*AbsSqr(CpbarFtFtVGPR())*B1(Sqr(p),Sqr(MFt),0);
   result += -(AbsSqr(CpbarFtFtVPPR())*B1(Sqr(p),Sqr(MFt),0));
   result += -(AbsSqr(CpbarFtFtVZPR())*B1(Sqr(p),Sqr(MFt),Sqr(MVZ)));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFtFbconjHpmPL(gI1))*B1(Sqr(p),Sqr(MFb
      ),Sqr(MHpm(gI1))));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFtFthhPL(gI1))*B1(Sqr(p),Sqr(MFt),Sqr
      (Mhh(gI1))));
   result += -0.6666666666666666*SUM(gI1,0,1,AbsSqr(CpbarFtGluStPL(gI1))*B1(Sqr
      (p),Sqr(MGlu),Sqr(MSt(gI1))));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpbarFtbarChaSbPL(gI1,gI2))*B1
      (Sqr(p),Sqr(MCha(gI1)),Sqr(MSb(gI2)))));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,3,AbsSqr(CpbarFtChiStPL(gI2,gI1))*B1(
      Sqr(p),Sqr(MChi(gI2)),Sqr(MSt(gI1)))));
   result += -0.5*SUM(gI2,0,1,AbsSqr(CpbarFtFtAhPL(gI2))*B1(Sqr(p),Sqr(MFt),Sqr
      (MAh(gI2))));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fve_1loop_1(double p ) const
{
   std::complex<double> result;

   result += -4*MFe*B0(Sqr(p),Sqr(MFe),Sqr(MVWm))*Conj(CpbarFveFeconjVWmPR())*
      CpbarFveFeconjVWmPL();
   result += -4*MFve*B0(Sqr(p),Sqr(MFve),Sqr(MVZ))*Conj(CpbarFveFveVZPR())*
      CpbarFveFveVZPL();
   result += MFe*SUM(gI1,0,1,B0(Sqr(p),Sqr(MFe),Sqr(MHpm(gI1)))*Conj(
      CpbarFveFeconjHpmPL(gI1))*CpbarFveFeconjHpmPR(gI1));
   result += SUM(gI1,0,1,MCha(gI1)*SUM(gI2,0,1,B0(Sqr(p),Sqr(MCha(gI1)),Sqr(MSe
      (gI2)))*Conj(CpbarFvebarChaSePL(gI1,gI2))*CpbarFvebarChaSePR(gI1,gI2)));
   result += SUM(gI2,0,3,B0(Sqr(p),Sqr(MChi(gI2)),Sqr(MSveL))*Conj(
      CpbarFveChiSveLPL(gI2))*CpbarFveChiSveLPR(gI2)*MChi(gI2));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fve_1loop_PR(double p ) const
{
   std::complex<double> result;

   result += -(AbsSqr(CpbarFveFeconjVWmPL())*B1(Sqr(p),Sqr(MFe),Sqr(MVWm)));
   result += -(AbsSqr(CpbarFveFveVZPL())*B1(Sqr(p),Sqr(MFve),Sqr(MVZ)));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFveFeconjHpmPR(gI1))*B1(Sqr(p),Sqr(
      MFe),Sqr(MHpm(gI1))));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpbarFvebarChaSePR(gI1,gI2))*
      B1(Sqr(p),Sqr(MCha(gI1)),Sqr(MSe(gI2)))));
   result += -0.5*SUM(gI2,0,3,AbsSqr(CpbarFveChiSveLPR(gI2))*B1(Sqr(p),Sqr(MChi
      (gI2)),Sqr(MSveL)));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fve_1loop_PL(double p ) const
{
   std::complex<double> result;

   result += -(AbsSqr(CpbarFveFeconjVWmPR())*B1(Sqr(p),Sqr(MFe),Sqr(MVWm)));
   result += -(AbsSqr(CpbarFveFveVZPR())*B1(Sqr(p),Sqr(MFve),Sqr(MVZ)));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFveFeconjHpmPL(gI1))*B1(Sqr(p),Sqr(
      MFe),Sqr(MHpm(gI1))));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpbarFvebarChaSePL(gI1,gI2))*
      B1(Sqr(p),Sqr(MCha(gI1)),Sqr(MSe(gI2)))));
   result += -0.5*SUM(gI2,0,3,AbsSqr(CpbarFveChiSveLPL(gI2))*B1(Sqr(p),Sqr(MChi
      (gI2)),Sqr(MSveL)));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fvm_1loop_1(double p ) const
{
   std::complex<double> result;

   result += -4*MFm*B0(Sqr(p),Sqr(MFm),Sqr(MVWm))*Conj(CpbarFvmFmconjVWmPR())*
      CpbarFvmFmconjVWmPL();
   result += -4*MFvm*B0(Sqr(p),Sqr(MFvm),Sqr(MVZ))*Conj(CpbarFvmFvmVZPR())*
      CpbarFvmFvmVZPL();
   result += MFm*SUM(gI1,0,1,B0(Sqr(p),Sqr(MFm),Sqr(MHpm(gI1)))*Conj(
      CpbarFvmFmconjHpmPL(gI1))*CpbarFvmFmconjHpmPR(gI1));
   result += SUM(gI1,0,1,MCha(gI1)*SUM(gI2,0,1,B0(Sqr(p),Sqr(MCha(gI1)),Sqr(MSm
      (gI2)))*Conj(CpbarFvmbarChaSmPL(gI1,gI2))*CpbarFvmbarChaSmPR(gI1,gI2)));
   result += SUM(gI2,0,3,B0(Sqr(p),Sqr(MChi(gI2)),Sqr(MSvmL))*Conj(
      CpbarFvmChiSvmLPL(gI2))*CpbarFvmChiSvmLPR(gI2)*MChi(gI2));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fvm_1loop_PR(double p ) const
{
   std::complex<double> result;

   result += -(AbsSqr(CpbarFvmFmconjVWmPL())*B1(Sqr(p),Sqr(MFm),Sqr(MVWm)));
   result += -(AbsSqr(CpbarFvmFvmVZPL())*B1(Sqr(p),Sqr(MFvm),Sqr(MVZ)));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFvmFmconjHpmPR(gI1))*B1(Sqr(p),Sqr(
      MFm),Sqr(MHpm(gI1))));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpbarFvmbarChaSmPR(gI1,gI2))*
      B1(Sqr(p),Sqr(MCha(gI1)),Sqr(MSm(gI2)))));
   result += -0.5*SUM(gI2,0,3,AbsSqr(CpbarFvmChiSvmLPR(gI2))*B1(Sqr(p),Sqr(MChi
      (gI2)),Sqr(MSvmL)));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fvm_1loop_PL(double p ) const
{
   std::complex<double> result;

   result += -(AbsSqr(CpbarFvmFmconjVWmPR())*B1(Sqr(p),Sqr(MFm),Sqr(MVWm)));
   result += -(AbsSqr(CpbarFvmFvmVZPR())*B1(Sqr(p),Sqr(MFvm),Sqr(MVZ)));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFvmFmconjHpmPL(gI1))*B1(Sqr(p),Sqr(
      MFm),Sqr(MHpm(gI1))));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpbarFvmbarChaSmPL(gI1,gI2))*
      B1(Sqr(p),Sqr(MCha(gI1)),Sqr(MSm(gI2)))));
   result += -0.5*SUM(gI2,0,3,AbsSqr(CpbarFvmChiSvmLPL(gI2))*B1(Sqr(p),Sqr(MChi
      (gI2)),Sqr(MSvmL)));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fvt_1loop_1(double p ) const
{
   std::complex<double> result;

   result += -4*MFtau*B0(Sqr(p),Sqr(MFtau),Sqr(MVWm))*Conj(
      CpbarFvtFtauconjVWmPR())*CpbarFvtFtauconjVWmPL();
   result += -4*MFvt*B0(Sqr(p),Sqr(MFvt),Sqr(MVZ))*Conj(CpbarFvtFvtVZPR())*
      CpbarFvtFvtVZPL();
   result += MFtau*SUM(gI1,0,1,B0(Sqr(p),Sqr(MFtau),Sqr(MHpm(gI1)))*Conj(
      CpbarFvtFtauconjHpmPL(gI1))*CpbarFvtFtauconjHpmPR(gI1));
   result += SUM(gI1,0,1,MCha(gI1)*SUM(gI2,0,1,B0(Sqr(p),Sqr(MCha(gI1)),Sqr(
      MStau(gI2)))*Conj(CpbarFvtbarChaStauPL(gI1,gI2))*CpbarFvtbarChaStauPR(gI1,
      gI2)));
   result += SUM(gI2,0,3,B0(Sqr(p),Sqr(MChi(gI2)),Sqr(MSvtL))*Conj(
      CpbarFvtChiSvtLPL(gI2))*CpbarFvtChiSvtLPR(gI2)*MChi(gI2));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fvt_1loop_PR(double p ) const
{
   std::complex<double> result;

   result += -(AbsSqr(CpbarFvtFtauconjVWmPL())*B1(Sqr(p),Sqr(MFtau),Sqr(MVWm)))
      ;
   result += -(AbsSqr(CpbarFvtFvtVZPL())*B1(Sqr(p),Sqr(MFvt),Sqr(MVZ)));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFvtFtauconjHpmPR(gI1))*B1(Sqr(p),Sqr(
      MFtau),Sqr(MHpm(gI1))));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpbarFvtbarChaStauPR(gI1,gI2))
      *B1(Sqr(p),Sqr(MCha(gI1)),Sqr(MStau(gI2)))));
   result += -0.5*SUM(gI2,0,3,AbsSqr(CpbarFvtChiSvtLPR(gI2))*B1(Sqr(p),Sqr(MChi
      (gI2)),Sqr(MSvtL)));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fvt_1loop_PL(double p ) const
{
   std::complex<double> result;

   result += -(AbsSqr(CpbarFvtFtauconjVWmPR())*B1(Sqr(p),Sqr(MFtau),Sqr(MVWm)))
      ;
   result += -(AbsSqr(CpbarFvtFvtVZPR())*B1(Sqr(p),Sqr(MFvt),Sqr(MVZ)));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFvtFtauconjHpmPL(gI1))*B1(Sqr(p),Sqr(
      MFtau),Sqr(MHpm(gI1))));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpbarFvtbarChaStauPL(gI1,gI2))
      *B1(Sqr(p),Sqr(MCha(gI1)),Sqr(MStau(gI2)))));
   result += -0.5*SUM(gI2,0,3,AbsSqr(CpbarFvtChiSvtLPL(gI2))*B1(Sqr(p),Sqr(MChi
      (gI2)),Sqr(MSvtL)));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fe_1loop_1(double p ) const
{
   std::complex<double> result;

   result += -4*MFe*B0(Sqr(p),Sqr(MFe),0)*Conj(CpbarFeFeVPPR())*CpbarFeFeVPPL()
      ;
   result += -4*MFe*B0(Sqr(p),Sqr(MFe),Sqr(MVZ))*Conj(CpbarFeFeVZPR())*
      CpbarFeFeVZPL();
   result += -4*MFve*B0(Sqr(p),Sqr(MFve),Sqr(MVWm))*Conj(CpbarFeFveVWmPR())*
      CpbarFeFveVWmPL();
   result += MFe*SUM(gI1,0,1,B0(Sqr(p),Sqr(MFe),Sqr(Mhh(gI1)))*Conj(
      CpbarFeFehhPL(gI1))*CpbarFeFehhPR(gI1));
   result += MFve*SUM(gI1,0,1,B0(Sqr(p),Sqr(MFve),Sqr(MHpm(gI1)))*Conj(
      CpbarFeFveHpmPL(gI1))*CpbarFeFveHpmPR(gI1));
   result += SUM(gI1,0,1,SUM(gI2,0,3,B0(Sqr(p),Sqr(MChi(gI2)),Sqr(MSe(gI1)))*
      Conj(CpbarFeChiSePL(gI2,gI1))*CpbarFeChiSePR(gI2,gI1)*MChi(gI2)));
   result += MFe*SUM(gI2,0,1,B0(Sqr(p),Sqr(MFe),Sqr(MAh(gI2)))*Conj(
      CpbarFeFeAhPL(gI2))*CpbarFeFeAhPR(gI2));
   result += SUM(gI2,0,1,B0(Sqr(p),Sqr(MCha(gI2)),Sqr(MSveL))*Conj(
      CpbarFeChaSveLPL(gI2))*CpbarFeChaSveLPR(gI2)*MCha(gI2));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fe_1loop_PR(double p ) const
{
   std::complex<double> result;

   result += -(AbsSqr(CpbarFeFeVPPL())*B1(Sqr(p),Sqr(MFe),0));
   result += -(AbsSqr(CpbarFeFeVZPL())*B1(Sqr(p),Sqr(MFe),Sqr(MVZ)));
   result += -(AbsSqr(CpbarFeFveVWmPL())*B1(Sqr(p),Sqr(MFve),Sqr(MVWm)));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFeFehhPR(gI1))*B1(Sqr(p),Sqr(MFe),Sqr
      (Mhh(gI1))));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFeFveHpmPR(gI1))*B1(Sqr(p),Sqr(MFve),
      Sqr(MHpm(gI1))));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,3,AbsSqr(CpbarFeChiSePR(gI2,gI1))*B1(
      Sqr(p),Sqr(MChi(gI2)),Sqr(MSe(gI1)))));
   result += -0.5*SUM(gI2,0,1,AbsSqr(CpbarFeChaSveLPR(gI2))*B1(Sqr(p),Sqr(MCha(
      gI2)),Sqr(MSveL)));
   result += -0.5*SUM(gI2,0,1,AbsSqr(CpbarFeFeAhPR(gI2))*B1(Sqr(p),Sqr(MFe),Sqr
      (MAh(gI2))));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fe_1loop_PL(double p ) const
{
   std::complex<double> result;

   result += -(AbsSqr(CpbarFeFeVPPR())*B1(Sqr(p),Sqr(MFe),0));
   result += -(AbsSqr(CpbarFeFeVZPR())*B1(Sqr(p),Sqr(MFe),Sqr(MVZ)));
   result += -(AbsSqr(CpbarFeFveVWmPR())*B1(Sqr(p),Sqr(MFve),Sqr(MVWm)));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFeFehhPL(gI1))*B1(Sqr(p),Sqr(MFe),Sqr
      (Mhh(gI1))));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFeFveHpmPL(gI1))*B1(Sqr(p),Sqr(MFve),
      Sqr(MHpm(gI1))));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,3,AbsSqr(CpbarFeChiSePL(gI2,gI1))*B1(
      Sqr(p),Sqr(MChi(gI2)),Sqr(MSe(gI1)))));
   result += -0.5*SUM(gI2,0,1,AbsSqr(CpbarFeChaSveLPL(gI2))*B1(Sqr(p),Sqr(MCha(
      gI2)),Sqr(MSveL)));
   result += -0.5*SUM(gI2,0,1,AbsSqr(CpbarFeFeAhPL(gI2))*B1(Sqr(p),Sqr(MFe),Sqr
      (MAh(gI2))));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fm_1loop_1(double p ) const
{
   std::complex<double> result;

   result += -4*MFm*B0(Sqr(p),Sqr(MFm),0)*Conj(CpbarFmFmVPPR())*CpbarFmFmVPPL()
      ;
   result += -4*MFm*B0(Sqr(p),Sqr(MFm),Sqr(MVZ))*Conj(CpbarFmFmVZPR())*
      CpbarFmFmVZPL();
   result += -4*MFvm*B0(Sqr(p),Sqr(MFvm),Sqr(MVWm))*Conj(CpbarFmFvmVWmPR())*
      CpbarFmFvmVWmPL();
   result += MFm*SUM(gI1,0,1,B0(Sqr(p),Sqr(MFm),Sqr(Mhh(gI1)))*Conj(
      CpbarFmFmhhPL(gI1))*CpbarFmFmhhPR(gI1));
   result += MFvm*SUM(gI1,0,1,B0(Sqr(p),Sqr(MFvm),Sqr(MHpm(gI1)))*Conj(
      CpbarFmFvmHpmPL(gI1))*CpbarFmFvmHpmPR(gI1));
   result += SUM(gI1,0,1,SUM(gI2,0,3,B0(Sqr(p),Sqr(MChi(gI2)),Sqr(MSm(gI1)))*
      Conj(CpbarFmChiSmPL(gI2,gI1))*CpbarFmChiSmPR(gI2,gI1)*MChi(gI2)));
   result += MFm*SUM(gI2,0,1,B0(Sqr(p),Sqr(MFm),Sqr(MAh(gI2)))*Conj(
      CpbarFmFmAhPL(gI2))*CpbarFmFmAhPR(gI2));
   result += SUM(gI2,0,1,B0(Sqr(p),Sqr(MCha(gI2)),Sqr(MSvmL))*Conj(
      CpbarFmChaSvmLPL(gI2))*CpbarFmChaSvmLPR(gI2)*MCha(gI2));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fm_1loop_PR(double p ) const
{
   std::complex<double> result;

   result += -(AbsSqr(CpbarFmFmVPPL())*B1(Sqr(p),Sqr(MFm),0));
   result += -(AbsSqr(CpbarFmFmVZPL())*B1(Sqr(p),Sqr(MFm),Sqr(MVZ)));
   result += -(AbsSqr(CpbarFmFvmVWmPL())*B1(Sqr(p),Sqr(MFvm),Sqr(MVWm)));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFmFmhhPR(gI1))*B1(Sqr(p),Sqr(MFm),Sqr
      (Mhh(gI1))));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFmFvmHpmPR(gI1))*B1(Sqr(p),Sqr(MFvm),
      Sqr(MHpm(gI1))));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,3,AbsSqr(CpbarFmChiSmPR(gI2,gI1))*B1(
      Sqr(p),Sqr(MChi(gI2)),Sqr(MSm(gI1)))));
   result += -0.5*SUM(gI2,0,1,AbsSqr(CpbarFmChaSvmLPR(gI2))*B1(Sqr(p),Sqr(MCha(
      gI2)),Sqr(MSvmL)));
   result += -0.5*SUM(gI2,0,1,AbsSqr(CpbarFmFmAhPR(gI2))*B1(Sqr(p),Sqr(MFm),Sqr
      (MAh(gI2))));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fm_1loop_PL(double p ) const
{
   std::complex<double> result;

   result += -(AbsSqr(CpbarFmFmVPPR())*B1(Sqr(p),Sqr(MFm),0));
   result += -(AbsSqr(CpbarFmFmVZPR())*B1(Sqr(p),Sqr(MFm),Sqr(MVZ)));
   result += -(AbsSqr(CpbarFmFvmVWmPR())*B1(Sqr(p),Sqr(MFvm),Sqr(MVWm)));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFmFmhhPL(gI1))*B1(Sqr(p),Sqr(MFm),Sqr
      (Mhh(gI1))));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFmFvmHpmPL(gI1))*B1(Sqr(p),Sqr(MFvm),
      Sqr(MHpm(gI1))));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,3,AbsSqr(CpbarFmChiSmPL(gI2,gI1))*B1(
      Sqr(p),Sqr(MChi(gI2)),Sqr(MSm(gI1)))));
   result += -0.5*SUM(gI2,0,1,AbsSqr(CpbarFmChaSvmLPL(gI2))*B1(Sqr(p),Sqr(MCha(
      gI2)),Sqr(MSvmL)));
   result += -0.5*SUM(gI2,0,1,AbsSqr(CpbarFmFmAhPL(gI2))*B1(Sqr(p),Sqr(MFm),Sqr
      (MAh(gI2))));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Ftau_1loop_1(double p ) const
{
   std::complex<double> result;

   result += -4*MFtau*B0(Sqr(p),Sqr(MFtau),0)*Conj(CpbarFtauFtauVPPR())*
      CpbarFtauFtauVPPL();
   result += -4*MFtau*B0(Sqr(p),Sqr(MFtau),Sqr(MVZ))*Conj(CpbarFtauFtauVZPR())*
      CpbarFtauFtauVZPL();
   result += -4*MFvt*B0(Sqr(p),Sqr(MFvt),Sqr(MVWm))*Conj(CpbarFtauFvtVWmPR())*
      CpbarFtauFvtVWmPL();
   result += MFtau*SUM(gI1,0,1,B0(Sqr(p),Sqr(MFtau),Sqr(Mhh(gI1)))*Conj(
      CpbarFtauFtauhhPL(gI1))*CpbarFtauFtauhhPR(gI1));
   result += MFvt*SUM(gI1,0,1,B0(Sqr(p),Sqr(MFvt),Sqr(MHpm(gI1)))*Conj(
      CpbarFtauFvtHpmPL(gI1))*CpbarFtauFvtHpmPR(gI1));
   result += SUM(gI1,0,1,SUM(gI2,0,3,B0(Sqr(p),Sqr(MChi(gI2)),Sqr(MStau(gI1)))*
      Conj(CpbarFtauChiStauPL(gI2,gI1))*CpbarFtauChiStauPR(gI2,gI1)*MChi(gI2)));
   result += MFtau*SUM(gI2,0,1,B0(Sqr(p),Sqr(MFtau),Sqr(MAh(gI2)))*Conj(
      CpbarFtauFtauAhPL(gI2))*CpbarFtauFtauAhPR(gI2));
   result += SUM(gI2,0,1,B0(Sqr(p),Sqr(MCha(gI2)),Sqr(MSvtL))*Conj(
      CpbarFtauChaSvtLPL(gI2))*CpbarFtauChaSvtLPR(gI2)*MCha(gI2));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Ftau_1loop_PR(double p ) const
{
   std::complex<double> result;

   result += -(AbsSqr(CpbarFtauFtauVPPL())*B1(Sqr(p),Sqr(MFtau),0));
   result += -(AbsSqr(CpbarFtauFtauVZPL())*B1(Sqr(p),Sqr(MFtau),Sqr(MVZ)));
   result += -(AbsSqr(CpbarFtauFvtVWmPL())*B1(Sqr(p),Sqr(MFvt),Sqr(MVWm)));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFtauFtauhhPR(gI1))*B1(Sqr(p),Sqr(
      MFtau),Sqr(Mhh(gI1))));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFtauFvtHpmPR(gI1))*B1(Sqr(p),Sqr(MFvt
      ),Sqr(MHpm(gI1))));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,3,AbsSqr(CpbarFtauChiStauPR(gI2,gI1))*
      B1(Sqr(p),Sqr(MChi(gI2)),Sqr(MStau(gI1)))));
   result += -0.5*SUM(gI2,0,1,AbsSqr(CpbarFtauChaSvtLPR(gI2))*B1(Sqr(p),Sqr(
      MCha(gI2)),Sqr(MSvtL)));
   result += -0.5*SUM(gI2,0,1,AbsSqr(CpbarFtauFtauAhPR(gI2))*B1(Sqr(p),Sqr(
      MFtau),Sqr(MAh(gI2))));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Ftau_1loop_PL(double p ) const
{
   std::complex<double> result;

   result += -(AbsSqr(CpbarFtauFtauVPPR())*B1(Sqr(p),Sqr(MFtau),0));
   result += -(AbsSqr(CpbarFtauFtauVZPR())*B1(Sqr(p),Sqr(MFtau),Sqr(MVZ)));
   result += -(AbsSqr(CpbarFtauFvtVWmPR())*B1(Sqr(p),Sqr(MFvt),Sqr(MVWm)));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFtauFtauhhPL(gI1))*B1(Sqr(p),Sqr(
      MFtau),Sqr(Mhh(gI1))));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFtauFvtHpmPL(gI1))*B1(Sqr(p),Sqr(MFvt
      ),Sqr(MHpm(gI1))));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,3,AbsSqr(CpbarFtauChiStauPL(gI2,gI1))*
      B1(Sqr(p),Sqr(MChi(gI2)),Sqr(MStau(gI1)))));
   result += -0.5*SUM(gI2,0,1,AbsSqr(CpbarFtauChaSvtLPL(gI2))*B1(Sqr(p),Sqr(
      MCha(gI2)),Sqr(MSvtL)));
   result += -0.5*SUM(gI2,0,1,AbsSqr(CpbarFtauFtauAhPL(gI2))*B1(Sqr(p),Sqr(
      MFtau),Sqr(MAh(gI2))));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fb_1loop_1_heavy_rotated(double p ) const
{
   std::complex<double> result;

   result += -4*MFb*B0(Sqr(p),Sqr(MFb),Sqr(MVZ))*Conj(CpbarFbFbVZPR())*
      CpbarFbFbVZPL();
   result += -4*MFt*B0(Sqr(p),Sqr(MFt),Sqr(MVWm))*Conj(CpbarFbFtVWmPR())*
      CpbarFbFtVWmPL();
   result += MFb*SUM(gI1,0,1,B0(Sqr(p),Sqr(MFb),Sqr(Mhh(gI1)))*Conj(
      CpbarFbFbhhPL(gI1))*CpbarFbFbhhPR(gI1));
   result += MFt*SUM(gI1,0,1,B0(Sqr(p),Sqr(MFt),Sqr(MHpm(gI1)))*Conj(
      CpbarFbFtHpmPL(gI1))*CpbarFbFtHpmPR(gI1));
   result += 1.3333333333333333*MGlu*SUM(gI1,0,1,B0(Sqr(p),Sqr(MGlu),Sqr(MSb(
      gI1)))*Conj(CpbarFbGluSbPL(gI1))*CpbarFbGluSbPR(gI1));
   result += SUM(gI1,0,1,SUM(gI2,0,1,B0(Sqr(p),Sqr(MCha(gI2)),Sqr(MSt(gI1)))*
      Conj(CpbarFbChaStPL(gI2,gI1))*CpbarFbChaStPR(gI2,gI1)*MCha(gI2)));
   result += SUM(gI1,0,1,SUM(gI2,0,3,B0(Sqr(p),Sqr(MChi(gI2)),Sqr(MSb(gI1)))*
      Conj(CpbarFbChiSbPL(gI2,gI1))*CpbarFbChiSbPR(gI2,gI1)*MChi(gI2)));
   result += MFb*SUM(gI2,0,1,B0(Sqr(p),Sqr(MFb),Sqr(MAh(gI2)))*Conj(
      CpbarFbFbAhPL(gI2))*CpbarFbFbAhPR(gI2));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fb_1loop_PR_heavy_rotated(double p ) const
{
   std::complex<double> result;

   result += -(AbsSqr(CpbarFbFbVZPL())*B1(Sqr(p),Sqr(MFb),Sqr(MVZ)));
   result += -(AbsSqr(CpbarFbFtVWmPL())*B1(Sqr(p),Sqr(MFt),Sqr(MVWm)));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFbFbhhPR(gI1))*B1(Sqr(p),Sqr(MFb),Sqr
      (Mhh(gI1))));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFbFtHpmPR(gI1))*B1(Sqr(p),Sqr(MFt),
      Sqr(MHpm(gI1))));
   result += -0.6666666666666666*SUM(gI1,0,1,AbsSqr(CpbarFbGluSbPR(gI1))*B1(Sqr
      (p),Sqr(MGlu),Sqr(MSb(gI1))));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpbarFbChaStPR(gI2,gI1))*B1(
      Sqr(p),Sqr(MCha(gI2)),Sqr(MSt(gI1)))));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,3,AbsSqr(CpbarFbChiSbPR(gI2,gI1))*B1(
      Sqr(p),Sqr(MChi(gI2)),Sqr(MSb(gI1)))));
   result += -0.5*SUM(gI2,0,1,AbsSqr(CpbarFbFbAhPR(gI2))*B1(Sqr(p),Sqr(MFb),Sqr
      (MAh(gI2))));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fb_1loop_PL_heavy_rotated(double p ) const
{
   std::complex<double> result;

   result += -(AbsSqr(CpbarFbFbVZPR())*B1(Sqr(p),Sqr(MFb),Sqr(MVZ)));
   result += -(AbsSqr(CpbarFbFtVWmPR())*B1(Sqr(p),Sqr(MFt),Sqr(MVWm)));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFbFbhhPL(gI1))*B1(Sqr(p),Sqr(MFb),Sqr
      (Mhh(gI1))));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFbFtHpmPL(gI1))*B1(Sqr(p),Sqr(MFt),
      Sqr(MHpm(gI1))));
   result += -0.6666666666666666*SUM(gI1,0,1,AbsSqr(CpbarFbGluSbPL(gI1))*B1(Sqr
      (p),Sqr(MGlu),Sqr(MSb(gI1))));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpbarFbChaStPL(gI2,gI1))*B1(
      Sqr(p),Sqr(MCha(gI2)),Sqr(MSt(gI1)))));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,3,AbsSqr(CpbarFbChiSbPL(gI2,gI1))*B1(
      Sqr(p),Sqr(MChi(gI2)),Sqr(MSb(gI1)))));
   result += -0.5*SUM(gI2,0,1,AbsSqr(CpbarFbFbAhPL(gI2))*B1(Sqr(p),Sqr(MFb),Sqr
      (MAh(gI2))));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fe_1loop_1_heavy_rotated(double p ) const
{
   std::complex<double> result;

   result += -4*MFe*B0(Sqr(p),Sqr(MFe),Sqr(MVZ))*Conj(CpbarFeFeVZPR())*
      CpbarFeFeVZPL();
   result += -4*MFve*B0(Sqr(p),Sqr(MFve),Sqr(MVWm))*Conj(CpbarFeFveVWmPR())*
      CpbarFeFveVWmPL();
   result += MFe*SUM(gI1,0,1,B0(Sqr(p),Sqr(MFe),Sqr(Mhh(gI1)))*Conj(
      CpbarFeFehhPL(gI1))*CpbarFeFehhPR(gI1));
   result += MFve*SUM(gI1,0,1,B0(Sqr(p),Sqr(MFve),Sqr(MHpm(gI1)))*Conj(
      CpbarFeFveHpmPL(gI1))*CpbarFeFveHpmPR(gI1));
   result += SUM(gI1,0,1,SUM(gI2,0,3,B0(Sqr(p),Sqr(MChi(gI2)),Sqr(MSe(gI1)))*
      Conj(CpbarFeChiSePL(gI2,gI1))*CpbarFeChiSePR(gI2,gI1)*MChi(gI2)));
   result += MFe*SUM(gI2,0,1,B0(Sqr(p),Sqr(MFe),Sqr(MAh(gI2)))*Conj(
      CpbarFeFeAhPL(gI2))*CpbarFeFeAhPR(gI2));
   result += SUM(gI2,0,1,B0(Sqr(p),Sqr(MCha(gI2)),Sqr(MSveL))*Conj(
      CpbarFeChaSveLPL(gI2))*CpbarFeChaSveLPR(gI2)*MCha(gI2));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fe_1loop_PR_heavy_rotated(double p ) const
{
   std::complex<double> result;

   result += -(AbsSqr(CpbarFeFeVZPL())*B1(Sqr(p),Sqr(MFe),Sqr(MVZ)));
   result += -(AbsSqr(CpbarFeFveVWmPL())*B1(Sqr(p),Sqr(MFve),Sqr(MVWm)));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFeFehhPR(gI1))*B1(Sqr(p),Sqr(MFe),Sqr
      (Mhh(gI1))));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFeFveHpmPR(gI1))*B1(Sqr(p),Sqr(MFve),
      Sqr(MHpm(gI1))));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,3,AbsSqr(CpbarFeChiSePR(gI2,gI1))*B1(
      Sqr(p),Sqr(MChi(gI2)),Sqr(MSe(gI1)))));
   result += -0.5*SUM(gI2,0,1,AbsSqr(CpbarFeChaSveLPR(gI2))*B1(Sqr(p),Sqr(MCha(
      gI2)),Sqr(MSveL)));
   result += -0.5*SUM(gI2,0,1,AbsSqr(CpbarFeFeAhPR(gI2))*B1(Sqr(p),Sqr(MFe),Sqr
      (MAh(gI2))));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fe_1loop_PL_heavy_rotated(double p ) const
{
   std::complex<double> result;

   result += -(AbsSqr(CpbarFeFeVZPR())*B1(Sqr(p),Sqr(MFe),Sqr(MVZ)));
   result += -(AbsSqr(CpbarFeFveVWmPR())*B1(Sqr(p),Sqr(MFve),Sqr(MVWm)));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFeFehhPL(gI1))*B1(Sqr(p),Sqr(MFe),Sqr
      (Mhh(gI1))));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFeFveHpmPL(gI1))*B1(Sqr(p),Sqr(MFve),
      Sqr(MHpm(gI1))));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,3,AbsSqr(CpbarFeChiSePL(gI2,gI1))*B1(
      Sqr(p),Sqr(MChi(gI2)),Sqr(MSe(gI1)))));
   result += -0.5*SUM(gI2,0,1,AbsSqr(CpbarFeChaSveLPL(gI2))*B1(Sqr(p),Sqr(MCha(
      gI2)),Sqr(MSveL)));
   result += -0.5*SUM(gI2,0,1,AbsSqr(CpbarFeFeAhPL(gI2))*B1(Sqr(p),Sqr(MFe),Sqr
      (MAh(gI2))));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fm_1loop_1_heavy_rotated(double p ) const
{
   std::complex<double> result;

   result += -4*MFm*B0(Sqr(p),Sqr(MFm),Sqr(MVZ))*Conj(CpbarFmFmVZPR())*
      CpbarFmFmVZPL();
   result += -4*MFvm*B0(Sqr(p),Sqr(MFvm),Sqr(MVWm))*Conj(CpbarFmFvmVWmPR())*
      CpbarFmFvmVWmPL();
   result += MFm*SUM(gI1,0,1,B0(Sqr(p),Sqr(MFm),Sqr(Mhh(gI1)))*Conj(
      CpbarFmFmhhPL(gI1))*CpbarFmFmhhPR(gI1));
   result += MFvm*SUM(gI1,0,1,B0(Sqr(p),Sqr(MFvm),Sqr(MHpm(gI1)))*Conj(
      CpbarFmFvmHpmPL(gI1))*CpbarFmFvmHpmPR(gI1));
   result += SUM(gI1,0,1,SUM(gI2,0,3,B0(Sqr(p),Sqr(MChi(gI2)),Sqr(MSm(gI1)))*
      Conj(CpbarFmChiSmPL(gI2,gI1))*CpbarFmChiSmPR(gI2,gI1)*MChi(gI2)));
   result += MFm*SUM(gI2,0,1,B0(Sqr(p),Sqr(MFm),Sqr(MAh(gI2)))*Conj(
      CpbarFmFmAhPL(gI2))*CpbarFmFmAhPR(gI2));
   result += SUM(gI2,0,1,B0(Sqr(p),Sqr(MCha(gI2)),Sqr(MSvmL))*Conj(
      CpbarFmChaSvmLPL(gI2))*CpbarFmChaSvmLPR(gI2)*MCha(gI2));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fm_1loop_PR_heavy_rotated(double p ) const
{
   std::complex<double> result;

   result += -(AbsSqr(CpbarFmFmVZPL())*B1(Sqr(p),Sqr(MFm),Sqr(MVZ)));
   result += -(AbsSqr(CpbarFmFvmVWmPL())*B1(Sqr(p),Sqr(MFvm),Sqr(MVWm)));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFmFmhhPR(gI1))*B1(Sqr(p),Sqr(MFm),Sqr
      (Mhh(gI1))));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFmFvmHpmPR(gI1))*B1(Sqr(p),Sqr(MFvm),
      Sqr(MHpm(gI1))));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,3,AbsSqr(CpbarFmChiSmPR(gI2,gI1))*B1(
      Sqr(p),Sqr(MChi(gI2)),Sqr(MSm(gI1)))));
   result += -0.5*SUM(gI2,0,1,AbsSqr(CpbarFmChaSvmLPR(gI2))*B1(Sqr(p),Sqr(MCha(
      gI2)),Sqr(MSvmL)));
   result += -0.5*SUM(gI2,0,1,AbsSqr(CpbarFmFmAhPR(gI2))*B1(Sqr(p),Sqr(MFm),Sqr
      (MAh(gI2))));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fm_1loop_PL_heavy_rotated(double p ) const
{
   std::complex<double> result;

   result += -(AbsSqr(CpbarFmFmVZPR())*B1(Sqr(p),Sqr(MFm),Sqr(MVZ)));
   result += -(AbsSqr(CpbarFmFvmVWmPR())*B1(Sqr(p),Sqr(MFvm),Sqr(MVWm)));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFmFmhhPL(gI1))*B1(Sqr(p),Sqr(MFm),Sqr
      (Mhh(gI1))));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFmFvmHpmPL(gI1))*B1(Sqr(p),Sqr(MFvm),
      Sqr(MHpm(gI1))));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,3,AbsSqr(CpbarFmChiSmPL(gI2,gI1))*B1(
      Sqr(p),Sqr(MChi(gI2)),Sqr(MSm(gI1)))));
   result += -0.5*SUM(gI2,0,1,AbsSqr(CpbarFmChaSvmLPL(gI2))*B1(Sqr(p),Sqr(MCha(
      gI2)),Sqr(MSvmL)));
   result += -0.5*SUM(gI2,0,1,AbsSqr(CpbarFmFmAhPL(gI2))*B1(Sqr(p),Sqr(MFm),Sqr
      (MAh(gI2))));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Ftau_1loop_1_heavy_rotated(double p ) const
{
   std::complex<double> result;

   result += -4*MFtau*B0(Sqr(p),Sqr(MFtau),Sqr(MVZ))*Conj(CpbarFtauFtauVZPR())*
      CpbarFtauFtauVZPL();
   result += -4*MFvt*B0(Sqr(p),Sqr(MFvt),Sqr(MVWm))*Conj(CpbarFtauFvtVWmPR())*
      CpbarFtauFvtVWmPL();
   result += MFtau*SUM(gI1,0,1,B0(Sqr(p),Sqr(MFtau),Sqr(Mhh(gI1)))*Conj(
      CpbarFtauFtauhhPL(gI1))*CpbarFtauFtauhhPR(gI1));
   result += MFvt*SUM(gI1,0,1,B0(Sqr(p),Sqr(MFvt),Sqr(MHpm(gI1)))*Conj(
      CpbarFtauFvtHpmPL(gI1))*CpbarFtauFvtHpmPR(gI1));
   result += SUM(gI1,0,1,SUM(gI2,0,3,B0(Sqr(p),Sqr(MChi(gI2)),Sqr(MStau(gI1)))*
      Conj(CpbarFtauChiStauPL(gI2,gI1))*CpbarFtauChiStauPR(gI2,gI1)*MChi(gI2)));
   result += MFtau*SUM(gI2,0,1,B0(Sqr(p),Sqr(MFtau),Sqr(MAh(gI2)))*Conj(
      CpbarFtauFtauAhPL(gI2))*CpbarFtauFtauAhPR(gI2));
   result += SUM(gI2,0,1,B0(Sqr(p),Sqr(MCha(gI2)),Sqr(MSvtL))*Conj(
      CpbarFtauChaSvtLPL(gI2))*CpbarFtauChaSvtLPR(gI2)*MCha(gI2));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Ftau_1loop_PR_heavy_rotated(double p ) const
{
   std::complex<double> result;

   result += -(AbsSqr(CpbarFtauFtauVZPL())*B1(Sqr(p),Sqr(MFtau),Sqr(MVZ)));
   result += -(AbsSqr(CpbarFtauFvtVWmPL())*B1(Sqr(p),Sqr(MFvt),Sqr(MVWm)));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFtauFtauhhPR(gI1))*B1(Sqr(p),Sqr(
      MFtau),Sqr(Mhh(gI1))));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFtauFvtHpmPR(gI1))*B1(Sqr(p),Sqr(MFvt
      ),Sqr(MHpm(gI1))));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,3,AbsSqr(CpbarFtauChiStauPR(gI2,gI1))*
      B1(Sqr(p),Sqr(MChi(gI2)),Sqr(MStau(gI1)))));
   result += -0.5*SUM(gI2,0,1,AbsSqr(CpbarFtauChaSvtLPR(gI2))*B1(Sqr(p),Sqr(
      MCha(gI2)),Sqr(MSvtL)));
   result += -0.5*SUM(gI2,0,1,AbsSqr(CpbarFtauFtauAhPR(gI2))*B1(Sqr(p),Sqr(
      MFtau),Sqr(MAh(gI2))));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Ftau_1loop_PL_heavy_rotated(double p ) const
{
   std::complex<double> result;

   result += -(AbsSqr(CpbarFtauFtauVZPR())*B1(Sqr(p),Sqr(MFtau),Sqr(MVZ)));
   result += -(AbsSqr(CpbarFtauFvtVWmPR())*B1(Sqr(p),Sqr(MFvt),Sqr(MVWm)));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFtauFtauhhPL(gI1))*B1(Sqr(p),Sqr(
      MFtau),Sqr(Mhh(gI1))));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFtauFvtHpmPL(gI1))*B1(Sqr(p),Sqr(MFvt
      ),Sqr(MHpm(gI1))));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,3,AbsSqr(CpbarFtauChiStauPL(gI2,gI1))*
      B1(Sqr(p),Sqr(MChi(gI2)),Sqr(MStau(gI1)))));
   result += -0.5*SUM(gI2,0,1,AbsSqr(CpbarFtauChaSvtLPL(gI2))*B1(Sqr(p),Sqr(
      MCha(gI2)),Sqr(MSvtL)));
   result += -0.5*SUM(gI2,0,1,AbsSqr(CpbarFtauFtauAhPL(gI2))*B1(Sqr(p),Sqr(
      MFtau),Sqr(MAh(gI2))));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Ft_1loop_1_heavy_rotated(double p ) const
{
   std::complex<double> result;

   result += -4*MFb*B0(Sqr(p),Sqr(MFb),Sqr(MVWm))*Conj(CpbarFtFbconjVWmPR())*
      CpbarFtFbconjVWmPL();
   result += -4*MFt*B0(Sqr(p),Sqr(MFt),0)*Conj(CpbarFtFtVPPR())*CpbarFtFtVPPL()
      ;
   result += -4*MFt*B0(Sqr(p),Sqr(MFt),Sqr(MVZ))*Conj(CpbarFtFtVZPR())*
      CpbarFtFtVZPL();
   result += MFb*SUM(gI1,0,1,B0(Sqr(p),Sqr(MFb),Sqr(MHpm(gI1)))*Conj(
      CpbarFtFbconjHpmPL(gI1))*CpbarFtFbconjHpmPR(gI1));
   result += MFt*SUM(gI1,0,1,B0(Sqr(p),Sqr(MFt),Sqr(Mhh(gI1)))*Conj(
      CpbarFtFthhPL(gI1))*CpbarFtFthhPR(gI1));
   result += 1.3333333333333333*MGlu*SUM(gI1,0,1,B0(Sqr(p),Sqr(MGlu),Sqr(MSt(
      gI1)))*Conj(CpbarFtGluStPL(gI1))*CpbarFtGluStPR(gI1));
   result += SUM(gI1,0,1,MCha(gI1)*SUM(gI2,0,1,B0(Sqr(p),Sqr(MCha(gI1)),Sqr(MSb
      (gI2)))*Conj(CpbarFtbarChaSbPL(gI1,gI2))*CpbarFtbarChaSbPR(gI1,gI2)));
   result += SUM(gI1,0,1,SUM(gI2,0,3,B0(Sqr(p),Sqr(MChi(gI2)),Sqr(MSt(gI1)))*
      Conj(CpbarFtChiStPL(gI2,gI1))*CpbarFtChiStPR(gI2,gI1)*MChi(gI2)));
   result += MFt*SUM(gI2,0,1,B0(Sqr(p),Sqr(MFt),Sqr(MAh(gI2)))*Conj(
      CpbarFtFtAhPL(gI2))*CpbarFtFtAhPR(gI2));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Ft_1loop_PR_heavy_rotated(double p ) const
{
   std::complex<double> result;

   result += -(AbsSqr(CpbarFtFbconjVWmPL())*B1(Sqr(p),Sqr(MFb),Sqr(MVWm)));
   result += -(AbsSqr(CpbarFtFtVPPL())*B1(Sqr(p),Sqr(MFt),0));
   result += -(AbsSqr(CpbarFtFtVZPL())*B1(Sqr(p),Sqr(MFt),Sqr(MVZ)));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFtFbconjHpmPR(gI1))*B1(Sqr(p),Sqr(MFb
      ),Sqr(MHpm(gI1))));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFtFthhPR(gI1))*B1(Sqr(p),Sqr(MFt),Sqr
      (Mhh(gI1))));
   result += -0.6666666666666666*SUM(gI1,0,1,AbsSqr(CpbarFtGluStPR(gI1))*B1(Sqr
      (p),Sqr(MGlu),Sqr(MSt(gI1))));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpbarFtbarChaSbPR(gI1,gI2))*B1
      (Sqr(p),Sqr(MCha(gI1)),Sqr(MSb(gI2)))));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,3,AbsSqr(CpbarFtChiStPR(gI2,gI1))*B1(
      Sqr(p),Sqr(MChi(gI2)),Sqr(MSt(gI1)))));
   result += -0.5*SUM(gI2,0,1,AbsSqr(CpbarFtFtAhPR(gI2))*B1(Sqr(p),Sqr(MFt),Sqr
      (MAh(gI2))));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Ft_1loop_PL_heavy_rotated(double p ) const
{
   std::complex<double> result;

   result += -(AbsSqr(CpbarFtFbconjVWmPR())*B1(Sqr(p),Sqr(MFb),Sqr(MVWm)));
   result += -(AbsSqr(CpbarFtFtVPPR())*B1(Sqr(p),Sqr(MFt),0));
   result += -(AbsSqr(CpbarFtFtVZPR())*B1(Sqr(p),Sqr(MFt),Sqr(MVZ)));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFtFbconjHpmPL(gI1))*B1(Sqr(p),Sqr(MFb
      ),Sqr(MHpm(gI1))));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFtFthhPL(gI1))*B1(Sqr(p),Sqr(MFt),Sqr
      (Mhh(gI1))));
   result += -0.6666666666666666*SUM(gI1,0,1,AbsSqr(CpbarFtGluStPL(gI1))*B1(Sqr
      (p),Sqr(MGlu),Sqr(MSt(gI1))));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpbarFtbarChaSbPL(gI1,gI2))*B1
      (Sqr(p),Sqr(MCha(gI1)),Sqr(MSb(gI2)))));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,3,AbsSqr(CpbarFtChiStPL(gI2,gI1))*B1(
      Sqr(p),Sqr(MChi(gI2)),Sqr(MSt(gI1)))));
   result += -0.5*SUM(gI2,0,1,AbsSqr(CpbarFtFtAhPL(gI2))*B1(Sqr(p),Sqr(MFt),Sqr
      (MAh(gI2))));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Ft_1loop_1_heavy(double p ) const
{
   std::complex<double> result;

   result += -4*MFb*B0(Sqr(p),Sqr(MFb),Sqr(MVWm))*Conj(CpbarFtFbconjVWmPR())*
      CpbarFtFbconjVWmPL();
   result += -4*MFt*B0(Sqr(p),Sqr(MFt),0)*Conj(CpbarFtFtVPPR())*CpbarFtFtVPPL()
      ;
   result += -4*MFt*B0(Sqr(p),Sqr(MFt),Sqr(MVZ))*Conj(CpbarFtFtVZPR())*
      CpbarFtFtVZPL();
   result += MFb*SUM(gI1,0,1,B0(Sqr(p),Sqr(MFb),Sqr(MHpm(gI1)))*Conj(
      CpbarFtFbconjHpmPL(gI1))*CpbarFtFbconjHpmPR(gI1));
   result += MFt*SUM(gI1,0,1,B0(Sqr(p),Sqr(MFt),Sqr(Mhh(gI1)))*Conj(
      CpbarFtFthhPL(gI1))*CpbarFtFthhPR(gI1));
   result += 1.3333333333333333*MGlu*SUM(gI1,0,1,B0(Sqr(p),Sqr(MGlu),Sqr(MSt(
      gI1)))*Conj(CpbarFtGluStPL(gI1))*CpbarFtGluStPR(gI1));
   result += SUM(gI1,0,1,MCha(gI1)*SUM(gI2,0,1,B0(Sqr(p),Sqr(MCha(gI1)),Sqr(MSb
      (gI2)))*Conj(CpbarFtbarChaSbPL(gI1,gI2))*CpbarFtbarChaSbPR(gI1,gI2)));
   result += SUM(gI1,0,1,SUM(gI2,0,3,B0(Sqr(p),Sqr(MChi(gI2)),Sqr(MSt(gI1)))*
      Conj(CpbarFtChiStPL(gI2,gI1))*CpbarFtChiStPR(gI2,gI1)*MChi(gI2)));
   result += MFt*SUM(gI2,0,1,B0(Sqr(p),Sqr(MFt),Sqr(MAh(gI2)))*Conj(
      CpbarFtFtAhPL(gI2))*CpbarFtFtAhPR(gI2));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Ft_1loop_PR_heavy(double p ) const
{
   std::complex<double> result;

   result += -(AbsSqr(CpbarFtFbconjVWmPL())*B1(Sqr(p),Sqr(MFb),Sqr(MVWm)));
   result += -(AbsSqr(CpbarFtFtVPPL())*B1(Sqr(p),Sqr(MFt),0));
   result += -(AbsSqr(CpbarFtFtVZPL())*B1(Sqr(p),Sqr(MFt),Sqr(MVZ)));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFtFbconjHpmPR(gI1))*B1(Sqr(p),Sqr(MFb
      ),Sqr(MHpm(gI1))));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFtFthhPR(gI1))*B1(Sqr(p),Sqr(MFt),Sqr
      (Mhh(gI1))));
   result += -0.6666666666666666*SUM(gI1,0,1,AbsSqr(CpbarFtGluStPR(gI1))*B1(Sqr
      (p),Sqr(MGlu),Sqr(MSt(gI1))));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpbarFtbarChaSbPR(gI1,gI2))*B1
      (Sqr(p),Sqr(MCha(gI1)),Sqr(MSb(gI2)))));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,3,AbsSqr(CpbarFtChiStPR(gI2,gI1))*B1(
      Sqr(p),Sqr(MChi(gI2)),Sqr(MSt(gI1)))));
   result += -0.5*SUM(gI2,0,1,AbsSqr(CpbarFtFtAhPR(gI2))*B1(Sqr(p),Sqr(MFt),Sqr
      (MAh(gI2))));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Ft_1loop_PL_heavy(double p ) const
{
   std::complex<double> result;

   result += -(AbsSqr(CpbarFtFbconjVWmPR())*B1(Sqr(p),Sqr(MFb),Sqr(MVWm)));
   result += -(AbsSqr(CpbarFtFtVPPR())*B1(Sqr(p),Sqr(MFt),0));
   result += -(AbsSqr(CpbarFtFtVZPR())*B1(Sqr(p),Sqr(MFt),Sqr(MVZ)));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFtFbconjHpmPL(gI1))*B1(Sqr(p),Sqr(MFb
      ),Sqr(MHpm(gI1))));
   result += -0.5*SUM(gI1,0,1,AbsSqr(CpbarFtFthhPL(gI1))*B1(Sqr(p),Sqr(MFt),Sqr
      (Mhh(gI1))));
   result += -0.6666666666666666*SUM(gI1,0,1,AbsSqr(CpbarFtGluStPL(gI1))*B1(Sqr
      (p),Sqr(MGlu),Sqr(MSt(gI1))));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,1,AbsSqr(CpbarFtbarChaSbPL(gI1,gI2))*B1
      (Sqr(p),Sqr(MCha(gI1)),Sqr(MSb(gI2)))));
   result += -0.5*SUM(gI1,0,1,SUM(gI2,0,3,AbsSqr(CpbarFtChiStPL(gI2,gI1))*B1(
      Sqr(p),Sqr(MChi(gI2)),Sqr(MSt(gI1)))));
   result += -0.5*SUM(gI2,0,1,AbsSqr(CpbarFtFtAhPL(gI2))*B1(Sqr(p),Sqr(MFt),Sqr
      (MAh(gI2))));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::tadpole_hh_1loop(int gO1) const
{
   std::complex<double> result;

   result += A0(Sqr(MVWm))*CpbargWmCgWmCUhh(gO1);
   result += A0(Sqr(MVWm))*CpbargWmgWmUhh(gO1);
   result += A0(Sqr(MVZ))*CpbargZgZUhh(gO1);
   result += -(A0(Sqr(MSveL))*CpSveLUhhconjSveL(gO1));
   result += -(A0(Sqr(MSvmL))*CpSvmLUhhconjSvmL(gO1));
   result += -(A0(Sqr(MSvtL))*CpSvtLUhhconjSvtL(gO1));
   result += 4*A0(Sqr(MVWm))*CpUhhconjVWmVWm(gO1);
   result += 2*A0(Sqr(MVZ))*CpUhhVZVZ(gO1);
   result += 6*MFb*A0(Sqr(MFb))*(CpbarFbFbUhhPL(gO1) + CpbarFbFbUhhPR(gO1));
   result += 6*MFc*A0(Sqr(MFc))*(CpbarFcFcUhhPL(gO1) + CpbarFcFcUhhPR(gO1));
   result += 6*MFd*A0(Sqr(MFd))*(CpbarFdFdUhhPL(gO1) + CpbarFdFdUhhPR(gO1));
   result += 2*MFe*A0(Sqr(MFe))*(CpbarFeFeUhhPL(gO1) + CpbarFeFeUhhPR(gO1));
   result += 2*MFm*A0(Sqr(MFm))*(CpbarFmFmUhhPL(gO1) + CpbarFmFmUhhPR(gO1));
   result += 6*MFs*A0(Sqr(MFs))*(CpbarFsFsUhhPL(gO1) + CpbarFsFsUhhPR(gO1));
   result += 6*MFt*A0(Sqr(MFt))*(CpbarFtFtUhhPL(gO1) + CpbarFtFtUhhPR(gO1));
   result += 2*MFtau*A0(Sqr(MFtau))*(CpbarFtauFtauUhhPL(gO1) +
      CpbarFtauFtauUhhPR(gO1));
   result += 6*MFu*A0(Sqr(MFu))*(CpbarFuFuUhhPL(gO1) + CpbarFuFuUhhPR(gO1));
   result += -0.5*SUM(gI1,0,1,A0(Sqr(MAh(gI1)))*CpAhAhUhh(gI1,gI1,gO1));
   result += -0.5*SUM(gI1,0,1,A0(Sqr(Mhh(gI1)))*CphhhhUhh(gI1,gI1,gO1));
   result += -SUM(gI1,0,1,A0(Sqr(MHpm(gI1)))*CpUhhHpmconjHpm(gO1,gI1,gI1));
   result += -3*SUM(gI1,0,1,A0(Sqr(MSb(gI1)))*CpUhhSbconjSb(gO1,gI1,gI1));
   result += -3*SUM(gI1,0,1,A0(Sqr(MSc(gI1)))*CpUhhScconjSc(gO1,gI1,gI1));
   result += -3*SUM(gI1,0,1,A0(Sqr(MSd(gI1)))*CpUhhSdconjSd(gO1,gI1,gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MSe(gI1)))*CpUhhSeconjSe(gO1,gI1,gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MSm(gI1)))*CpUhhSmconjSm(gO1,gI1,gI1));
   result += -3*SUM(gI1,0,1,A0(Sqr(MSs(gI1)))*CpUhhSsconjSs(gO1,gI1,gI1));
   result += -SUM(gI1,0,1,A0(Sqr(MStau(gI1)))*CpUhhStauconjStau(gO1,gI1,gI1));
   result += -3*SUM(gI1,0,1,A0(Sqr(MSt(gI1)))*CpUhhStconjSt(gO1,gI1,gI1));
   result += -3*SUM(gI1,0,1,A0(Sqr(MSu(gI1)))*CpUhhSuconjSu(gO1,gI1,gI1));
   result += 2*SUM(gI1,0,1,A0(Sqr(MCha(gI1)))*(CpbarChaChaUhhPL(gI1,gI1,gO1) +
      CpbarChaChaUhhPR(gI1,gI1,gO1))*MCha(gI1));
   result += SUM(gI1,0,3,A0(Sqr(MChi(gI1)))*(CpChiChiUhhPL(gI1,gI1,gO1) +
      CpChiChiUhhPR(gI1,gI1,gO1))*MChi(gI1));

   return result * oneOver16PiSqr;

}


void CLASSNAME::calculate_MTopSquark_2nd_generation(double& msf1, double& msf2, double& theta) const {
   sfermions::Mass_data sf_data;
   sf_data.ml2 = Re(mq2(1,1));
   sf_data.mr2 = Re(mu2(1,1));
   sf_data.yf  = Re(Yu(1,1));
   sf_data.vd  = Re(vd);
   sf_data.vu  = Re(vu);
   sf_data.gY  = 0.7745966692414834*g1;
   sf_data.g2  = g2;
   sf_data.Tyf = Re(TYu(1,1));
   sf_data.mu  = Re(Mu);
   sf_data.T3  = sfermions::Isospin[sfermions::up];
   sf_data.Yl  = sfermions::Hypercharge_left[sfermions::up];
   sf_data.Yr  = sfermions::Hypercharge_right[sfermions::up];

   Eigen::Array<double,2,1> msf;

   theta = sfermions::diagonalize_sfermions_2x2(sf_data, msf);
   msf1  = msf(0);
   msf2  = msf(1);
}

void CLASSNAME::calculate_MBottomSquark_2nd_generation(double& msf1, double& msf2, double& theta) const {
   sfermions::Mass_data sf_data;
   sf_data.ml2 = Re(mq2(1,1));
   sf_data.mr2 = Re(md2(1,1));
   sf_data.yf  = Re(Yd(1,1));
   sf_data.vd  = Re(vd);
   sf_data.vu  = Re(vu);
   sf_data.gY  = 0.7745966692414834*g1;
   sf_data.g2  = g2;
   sf_data.Tyf = Re(TYd(1,1));
   sf_data.mu  = Re(Mu);
   sf_data.T3  = sfermions::Isospin[sfermions::down];
   sf_data.Yl  = sfermions::Hypercharge_left[sfermions::down];
   sf_data.Yr  = sfermions::Hypercharge_right[sfermions::down];

   Eigen::Array<double,2,1> msf;

   theta = sfermions::diagonalize_sfermions_2x2(sf_data, msf);
   msf1  = msf(0);
   msf2  = msf(1);
}

void CLASSNAME::calculate_MSneutrino_2nd_generation(double& msf1, double& msf2, double& theta) const {
   sfermions::Mass_data sf_data;
   sf_data.ml2 = Re(ml2(1,1));
   sf_data.mr2 = 0.;
   sf_data.yf  = 0.;
   sf_data.vd  = Re(vd);
   sf_data.vu  = Re(vu);
   sf_data.gY  = 0.7745966692414834*g1;
   sf_data.g2  = g2;
   sf_data.Tyf = 0.;
   sf_data.mu  = Re(Mu);
   sf_data.T3  = sfermions::Isospin[sfermions::neutrino];
   sf_data.Yl  = sfermions::Hypercharge_left[sfermions::neutrino];
   sf_data.Yr  = sfermions::Hypercharge_right[sfermions::neutrino];

   Eigen::Array<double,2,1> msf;

   theta = sfermions::diagonalize_sfermions_2x2(sf_data, msf);
   msf1  = msf(0);
   msf2  = msf(1);
}

void CLASSNAME::calculate_MSelectron_2nd_generation(double& msf1, double& msf2, double& theta) const {
   sfermions::Mass_data sf_data;
   sf_data.ml2 = Re(ml2(1,1));
   sf_data.mr2 = Re(me2(1,1));
   sf_data.yf  = Re(Ye(1,1));
   sf_data.vd  = Re(vd);
   sf_data.vu  = Re(vu);
   sf_data.gY  = 0.7745966692414834*g1;
   sf_data.g2  = g2;
   sf_data.Tyf = Re(TYe(1,1));
   sf_data.mu  = Re(Mu);
   sf_data.T3  = sfermions::Isospin[sfermions::electron];
   sf_data.Yl  = sfermions::Hypercharge_left[sfermions::electron];
   sf_data.Yr  = sfermions::Hypercharge_right[sfermions::electron];

   Eigen::Array<double,2,1> msf;

   theta = sfermions::diagonalize_sfermions_2x2(sf_data, msf);
   msf1  = msf(0);
   msf2  = msf(1);
}

void CLASSNAME::calculate_MTopSquark_3rd_generation(double& msf1, double& msf2, double& theta) const {
   sfermions::Mass_data sf_data;
   sf_data.ml2 = Re(mq2(2,2));
   sf_data.mr2 = Re(mu2(2,2));
   sf_data.yf  = Re(Yu(2,2));
   sf_data.vd  = Re(vd);
   sf_data.vu  = Re(vu);
   sf_data.gY  = 0.7745966692414834*g1;
   sf_data.g2  = g2;
   sf_data.Tyf = Re(TYu(2,2));
   sf_data.mu  = Re(Mu);
   sf_data.T3  = sfermions::Isospin[sfermions::up];
   sf_data.Yl  = sfermions::Hypercharge_left[sfermions::up];
   sf_data.Yr  = sfermions::Hypercharge_right[sfermions::up];

   Eigen::Array<double,2,1> msf;

   theta = sfermions::diagonalize_sfermions_2x2(sf_data, msf);
   msf1  = msf(0);
   msf2  = msf(1);
}

void CLASSNAME::calculate_MBottomSquark_3rd_generation(double& msf1, double& msf2, double& theta) const {
   sfermions::Mass_data sf_data;
   sf_data.ml2 = Re(mq2(2,2));
   sf_data.mr2 = Re(md2(2,2));
   sf_data.yf  = Re(Yd(2,2));
   sf_data.vd  = Re(vd);
   sf_data.vu  = Re(vu);
   sf_data.gY  = 0.7745966692414834*g1;
   sf_data.g2  = g2;
   sf_data.Tyf = Re(TYd(2,2));
   sf_data.mu  = Re(Mu);
   sf_data.T3  = sfermions::Isospin[sfermions::down];
   sf_data.Yl  = sfermions::Hypercharge_left[sfermions::down];
   sf_data.Yr  = sfermions::Hypercharge_right[sfermions::down];

   Eigen::Array<double,2,1> msf;

   theta = sfermions::diagonalize_sfermions_2x2(sf_data, msf);
   msf1  = msf(0);
   msf2  = msf(1);
}

void CLASSNAME::calculate_MSneutrino_3rd_generation(double& msf1, double& msf2, double& theta) const {
   sfermions::Mass_data sf_data;
   sf_data.ml2 = Re(ml2(2,2));
   sf_data.mr2 = 0.;
   sf_data.yf  = 0.;
   sf_data.vd  = Re(vd);
   sf_data.vu  = Re(vu);
   sf_data.gY  = 0.7745966692414834*g1;
   sf_data.g2  = g2;
   sf_data.Tyf = 0.;
   sf_data.mu  = Re(Mu);
   sf_data.T3  = sfermions::Isospin[sfermions::neutrino];
   sf_data.Yl  = sfermions::Hypercharge_left[sfermions::neutrino];
   sf_data.Yr  = sfermions::Hypercharge_right[sfermions::neutrino];

   Eigen::Array<double,2,1> msf;

   theta = sfermions::diagonalize_sfermions_2x2(sf_data, msf);
   msf1  = msf(0);
   msf2  = msf(1);
}

void CLASSNAME::calculate_MSelectron_3rd_generation(double& msf1, double& msf2, double& theta) const {
   sfermions::Mass_data sf_data;
   sf_data.ml2 = Re(ml2(2,2));
   sf_data.mr2 = Re(me2(2,2));
   sf_data.yf  = Re(Ye(2,2));
   sf_data.vd  = Re(vd);
   sf_data.vu  = Re(vu);
   sf_data.gY  = 0.7745966692414834*g1;
   sf_data.g2  = g2;
   sf_data.Tyf = Re(TYe(2,2));
   sf_data.mu  = Re(Mu);
   sf_data.T3  = sfermions::Isospin[sfermions::electron];
   sf_data.Yl  = sfermions::Hypercharge_left[sfermions::electron];
   sf_data.Yr  = sfermions::Hypercharge_right[sfermions::electron];

   Eigen::Array<double,2,1> msf;

   theta = sfermions::diagonalize_sfermions_2x2(sf_data, msf);
   msf1  = msf(0);
   msf2  = msf(1);
}


Eigen::Matrix<double,2,2> CLASSNAME::self_energy_hh_2loop() const
{
   using namespace flexiblesusy::mssm_twoloophiggs;

   // calculate 3rd generation sfermion masses and mixing angles
   double mst_1, mst_2, theta_t;
   double msb_1, msb_2, theta_b;
   double mstau_1, mstau_2, theta_tau;
   double msnu_1, msnu_2, theta_nu;

   calculate_MTopSquark_3rd_generation(mst_1, mst_2, theta_t);
   calculate_MBottomSquark_3rd_generation(msb_1, msb_2, theta_b);
   calculate_MSelectron_3rd_generation(mstau_1, mstau_2, theta_tau);
   calculate_MSneutrino_3rd_generation(msnu_1, msnu_2, theta_nu);

   const double mst1sq = Sqr(mst_1), mst2sq = Sqr(mst_2);
   const double msb1sq = Sqr(msb_1), msb2sq = Sqr(msb_2);
   const double mstau1sq = Sqr(mstau_1), mstau2sq = Sqr(mstau_2);
   const double msnusq = Sqr(msnu_2);
   const double sxt = Sin(theta_t), cxt = Cos(theta_t);
   const double sxb = Sin(theta_b), cxb = Cos(theta_b);
   const double sintau = Sin(theta_tau), costau = Cos(theta_tau);
   const double gs = g3;
   const double rmtsq = Sqr(MFt);
   const double scalesq = Sqr(get_scale());
   const double vev2 = Sqr(vd) + Sqr(vu);
   const double tanb = vu/vd;
   const double amu = Re(-Mu);
   const double mg = MGlu;
   const double mAsq = Sqr(get_MPseudoscalarHiggs()(0));
   const double cotbeta = 1.0 / tanb;
   const double rmbsq = Sqr(MFb);
   const double rmtausq = Sqr(MFtau);

   Eigen::Matrix<double,2,2> self_energy_2l(Eigen::Matrix<double,2,2>::Zero());

   if (HIGGS_2LOOP_CORRECTION_AT_AS) {
      self_energy_2l += self_energy_higgs_2loop_at_as_mssm(
         rmtsq, mg, mst1sq, mst2sq, sxt, cxt, scalesq, amu,
         tanb, vev2, gs);
   }

   if (HIGGS_2LOOP_CORRECTION_AB_AS) {
      self_energy_2l += self_energy_higgs_2loop_ab_as_mssm(
         rmbsq, mg, msb1sq, msb2sq, sxb, cxb, scalesq, amu,
         cotbeta, vev2, gs);
   }

   if (HIGGS_2LOOP_CORRECTION_AT_AT) {
      self_energy_2l += self_energy_higgs_2loop_at_at_mssm(
         rmtsq, rmbsq, mAsq, mst1sq, mst2sq, msb1sq, msb2sq,
         sxt, cxt, sxb, cxb, scalesq, amu, tanb, vev2);
   }

   if (HIGGS_2LOOP_CORRECTION_ATAU_ATAU) {
      self_energy_2l += self_energy_higgs_2loop_atau_atau_mssm(
         rmtausq, mAsq, msnusq, mstau1sq, mstau2sq, sintau,
         costau, scalesq, amu, tanb, vev2);
   }

   return self_energy_2l;
}

Eigen::Matrix<double,2,2> CLASSNAME::self_energy_Ah_2loop() const
{
   using namespace flexiblesusy::mssm_twoloophiggs;

   // calculate 3rd generation sfermion masses and mixing angles
   double mst_1, mst_2, theta_t;
   double msb_1, msb_2, theta_b;
   double mstau_1, mstau_2, theta_tau;
   double msnu_1, msnu_2, theta_nu;

   calculate_MTopSquark_3rd_generation(mst_1, mst_2, theta_t);
   calculate_MBottomSquark_3rd_generation(msb_1, msb_2, theta_b);
   calculate_MSelectron_3rd_generation(mstau_1, mstau_2, theta_tau);
   calculate_MSneutrino_3rd_generation(msnu_1, msnu_2, theta_nu);

   const double mst1sq = Sqr(mst_1), mst2sq = Sqr(mst_2);
   const double msb1sq = Sqr(msb_1), msb2sq = Sqr(msb_2);
   const double mstau1sq = Sqr(mstau_1), mstau2sq = Sqr(mstau_2);
   const double msnusq = Sqr(msnu_2);
   const double sxt = Sin(theta_t), cxt = Cos(theta_t);
   const double sxb = Sin(theta_b), cxb = Cos(theta_b);
   const double sintau = Sin(theta_tau), costau = Cos(theta_tau);
   const double gs = g3;
   const double rmtsq = Sqr(MFt);
   const double scalesq = Sqr(get_scale());
   const double vev2 = Sqr(vd) + Sqr(vu);
   const double tanb = vu/vd;
   const double amu = Re(-Mu);
   const double mg = MGlu;
   const double mAsq = Sqr(get_MPseudoscalarHiggs()(0));
   const double cotbeta = 1.0 / tanb;
   const double rmbsq = Sqr(MFb);
   const double rmtausq = Sqr(MFtau);

   Eigen::Matrix<double,2,2> self_energy_2l(Eigen::Matrix<double,2,2>::Zero());

   if (HIGGS_2LOOP_CORRECTION_AT_AS) {
      self_energy_2l += self_energy_pseudoscalar_2loop_at_as_mssm(
         rmtsq, mg, mst1sq, mst2sq, sxt, cxt, scalesq, amu,
         tanb, vev2, gs);
   }

   if (HIGGS_2LOOP_CORRECTION_AB_AS) {
      self_energy_2l += self_energy_pseudoscalar_2loop_ab_as_mssm(
         rmbsq, mg, msb1sq, msb2sq, sxb, cxb, scalesq, amu,
         cotbeta, vev2, gs);
   }

   if (HIGGS_2LOOP_CORRECTION_AT_AT) {
      self_energy_2l += self_energy_pseudoscalar_2loop_at_at_mssm(
         rmtsq, rmbsq, mAsq, mst1sq, mst2sq, msb1sq, msb2sq,
         sxt, cxt, sxb, cxb, scalesq, amu, tanb, vev2);
   }

   if (HIGGS_2LOOP_CORRECTION_ATAU_ATAU) {
      self_energy_2l += self_energy_pseudoscalar_2loop_atau_atau_mssm(
         rmtausq, mAsq, msnusq, mstau1sq, mstau2sq, sintau,
         costau, scalesq, amu, tanb, vev2);
   }

   return self_energy_2l;
}



Eigen::Matrix<double,2,1> CLASSNAME::tadpole_hh_2loop() const
{
   using namespace flexiblesusy::mssm_twoloophiggs;

   // calculate 3rd generation sfermion masses and mixing angles
   double mst_1, mst_2, theta_t;
   double msb_1, msb_2, theta_b;
   double mstau_1, mstau_2, theta_tau;
   double msnu_1, msnu_2, theta_nu;

   calculate_MTopSquark_3rd_generation(mst_1, mst_2, theta_t);
   calculate_MBottomSquark_3rd_generation(msb_1, msb_2, theta_b);
   calculate_MSelectron_3rd_generation(mstau_1, mstau_2, theta_tau);
   calculate_MSneutrino_3rd_generation(msnu_1, msnu_2, theta_nu);

   const double mst1sq = Sqr(mst_1), mst2sq = Sqr(mst_2);
   const double msb1sq = Sqr(msb_1), msb2sq = Sqr(msb_2);
   const double mstau1sq = Sqr(mstau_1), mstau2sq = Sqr(mstau_2);
   const double msnusq = Sqr(msnu_2);
   const double sxt = Sin(theta_t), cxt = Cos(theta_t);
   const double sxb = Sin(theta_b), cxb = Cos(theta_b);
   const double sintau = Sin(theta_tau), costau = Cos(theta_tau);
   const double gs = g3;
   const double rmtsq = Sqr(MFt);
   const double scalesq = Sqr(get_scale());
   const double vev2 = Sqr(vd) + Sqr(vu);
   const double tanb = vu/vd;
   const double amu = Re(-Mu);
   const double mg = MGlu;
   const double mAsq = Sqr(get_MPseudoscalarHiggs()(0));
   const double cotbeta = 1.0 / tanb;
   const double rmbsq = Sqr(MFb);
   const double rmtausq = Sqr(MFtau);

   Eigen::Matrix<double,2,1> tadpole_2l(Eigen::Matrix<double,2,1>::Zero());

   if (HIGGS_2LOOP_CORRECTION_AT_AS) {
      tadpole_2l += tadpole_higgs_2loop_at_as_mssm(
         rmtsq, mg, mst1sq, mst2sq, sxt, cxt, scalesq,
         amu, tanb, vev2, gs);
   }

   if (HIGGS_2LOOP_CORRECTION_AT_AT) {
      tadpole_2l += tadpole_higgs_2loop_at_at_mssm(
         rmtsq, rmbsq, mAsq, mst1sq, mst2sq, msb1sq, msb2sq,
         sxt, cxt, sxb, cxb, scalesq, amu, tanb, vev2);
   }

   if (HIGGS_2LOOP_CORRECTION_AB_AS) {
      tadpole_2l += tadpole_higgs_2loop_ab_as_mssm(
         rmbsq, mg, msb1sq, msb2sq, sxb, cxb, scalesq,
         amu, cotbeta, vev2, gs);
   }

   if (HIGGS_2LOOP_CORRECTION_ATAU_ATAU) {
      tadpole_2l += tadpole_higgs_2loop_atau_atau_mssm(
         rmtausq, mAsq, msnusq, mstau1sq, mstau2sq, sintau,
         costau, scalesq, amu, tanb, vev2);
   }

   tadpole_2l(0) *= vd;
   tadpole_2l(1) *= vu;

   return tadpole_2l;
}




void CLASSNAME::calculate_MVG_pole()
{
   // diagonalization with medium precision
   PHYSICAL(MVG) = 0.;
}

void CLASSNAME::calculate_MGlu_pole()
{
   // diagonalization with medium precision
   const double M_tree(MGlu);
   const double p = MGlu;
   const double self_energy_1  = Re(self_energy_Glu_1loop_1(p));
   const double self_energy_PL = Re(self_energy_Glu_1loop_PL(p));
   const double self_energy_PR = Re(self_energy_Glu_1loop_PR(p));
   const auto M_loop = M_tree - self_energy_1 - M_tree * (self_energy_PL
      + self_energy_PR);
   PHYSICAL(MGlu) = calculate_singlet_mass(M_loop);
}

void CLASSNAME::calculate_MVP_pole()
{
   // diagonalization with medium precision
   PHYSICAL(MVP) = 0.;
}

void CLASSNAME::calculate_MVZ_pole()
{
   if (!force_output && problems.is_running_tachyon(CMSSMNoFV_info::VZ))
      return;

   // diagonalization with medium precision
   const double M_tree(Sqr(MVZ));
   const double p = MVZ;
   const double self_energy = Re(self_energy_VZ_1loop(p));
   const double mass_sqr = M_tree - self_energy;

   if (mass_sqr < 0.)
      problems.flag_pole_tachyon(CMSSMNoFV_info::VZ);

   PHYSICAL(MVZ) = AbsSqrt(mass_sqr);
}

void CLASSNAME::calculate_MFd_pole()
{
   // diagonalization with medium precision
   const double M_tree(MFd);
   const double p = MFd;
   const double self_energy_1  = Re(self_energy_Fd_1loop_1(p));
   const double self_energy_PL = Re(self_energy_Fd_1loop_PL(p));
   const double self_energy_PR = Re(self_energy_Fd_1loop_PR(p));
   const auto M_loop = M_tree - self_energy_1 - M_tree * (self_energy_PL
      + self_energy_PR);
   PHYSICAL(MFd) = calculate_singlet_mass(M_loop);
}

void CLASSNAME::calculate_MFs_pole()
{
   // diagonalization with medium precision
   const double M_tree(MFs);
   const double p = MFs;
   const double self_energy_1  = Re(self_energy_Fs_1loop_1(p));
   const double self_energy_PL = Re(self_energy_Fs_1loop_PL(p));
   const double self_energy_PR = Re(self_energy_Fs_1loop_PR(p));
   const auto M_loop = M_tree - self_energy_1 - M_tree * (self_energy_PL
      + self_energy_PR);
   PHYSICAL(MFs) = calculate_singlet_mass(M_loop);
}

void CLASSNAME::calculate_MFb_pole()
{
   // diagonalization with medium precision
   const double M_tree(MFb);
   const double p = MFb;
   const double self_energy_1  = Re(self_energy_Fb_1loop_1(p));
   const double self_energy_PL = Re(self_energy_Fb_1loop_PL(p));
   const double self_energy_PR = Re(self_energy_Fb_1loop_PR(p));
   const auto M_loop = M_tree - self_energy_1 - M_tree * (self_energy_PL
      + self_energy_PR);
   PHYSICAL(MFb) = calculate_singlet_mass(M_loop);
}

void CLASSNAME::calculate_MFu_pole()
{
   // diagonalization with medium precision
   const double M_tree(MFu);
   const double p = MFu;
   const double self_energy_1  = Re(self_energy_Fu_1loop_1(p));
   const double self_energy_PL = Re(self_energy_Fu_1loop_PL(p));
   const double self_energy_PR = Re(self_energy_Fu_1loop_PR(p));
   const auto M_loop = M_tree - self_energy_1 - M_tree * (self_energy_PL
      + self_energy_PR);
   PHYSICAL(MFu) = calculate_singlet_mass(M_loop);
}

void CLASSNAME::calculate_MFc_pole()
{
   // diagonalization with medium precision
   const double M_tree(MFc);
   const double p = MFc;
   const double self_energy_1  = Re(self_energy_Fc_1loop_1(p));
   const double self_energy_PL = Re(self_energy_Fc_1loop_PL(p));
   const double self_energy_PR = Re(self_energy_Fc_1loop_PR(p));
   const auto M_loop = M_tree - self_energy_1 - M_tree * (self_energy_PL
      + self_energy_PR);
   PHYSICAL(MFc) = calculate_singlet_mass(M_loop);
}

void CLASSNAME::calculate_MFt_pole()
{
   // diagonalization with medium precision
   const double M_tree(MFt);
   double qcd_1l = 0.;

   {
      const double currentScale = get_scale();
      qcd_1l = -0.008443431970194815*(5. - 3.*Log(Sqr(MFt)/Sqr(
         currentScale)))*Sqr(g3);
   }

   double qcd_2l = 0.;

   if (pole_mass_loop_order > 1 && TOP_POLE_QCD_CORRECTION > 0) {
      const double currentScale = get_scale();
      qcd_2l = -0.005191204615668296*Quad(g3) - 0.0032883224409535764*
         Log(Sqr(currentScale)/Sqr(MFt))*Quad(g3) - 0.0008822328500119351*Quad(
         g3)*Sqr(Log(Sqr(currentScale)/Sqr(MFt)));
   }

   double qcd_3l = 0.;

   if (pole_mass_loop_order > 2 && TOP_POLE_QCD_CORRECTION > 1) {
      const double currentScale = get_scale();
      qcd_3l = 0;
   }

   const double p = MFt;
   const double self_energy_1  = Re(self_energy_Ft_1loop_1_heavy(p));
   const double self_energy_PL = Re(self_energy_Ft_1loop_PL_heavy(p));
   const double self_energy_PR = Re(self_energy_Ft_1loop_PR_heavy(p));
   const auto M_loop = M_tree - self_energy_1 - M_tree * (self_energy_PL
      + self_energy_PR) - M_tree * (qcd_1l + qcd_2l + qcd_3l);

   PHYSICAL(MFt) = calculate_singlet_mass(M_loop);
}

void CLASSNAME::calculate_MFve_pole()
{
   // diagonalization with medium precision
   PHYSICAL(MFve) = 0.;
}

void CLASSNAME::calculate_MFvm_pole()
{
   // diagonalization with medium precision
   PHYSICAL(MFvm) = 0.;
}

void CLASSNAME::calculate_MFvt_pole()
{
   // diagonalization with medium precision
   PHYSICAL(MFvt) = 0.;
}

void CLASSNAME::calculate_MFe_pole()
{
   // diagonalization with medium precision
   const double M_tree(MFe);
   const double p = MFe;
   const double self_energy_1  = Re(self_energy_Fe_1loop_1(p));
   const double self_energy_PL = Re(self_energy_Fe_1loop_PL(p));
   const double self_energy_PR = Re(self_energy_Fe_1loop_PR(p));
   const auto M_loop = M_tree - self_energy_1 - M_tree * (self_energy_PL
      + self_energy_PR);
   PHYSICAL(MFe) = calculate_singlet_mass(M_loop);
}

void CLASSNAME::calculate_MFm_pole()
{
   // diagonalization with medium precision
   const double M_tree(MFm);
   const double p = MFm;
   const double self_energy_1  = Re(self_energy_Fm_1loop_1(p));
   const double self_energy_PL = Re(self_energy_Fm_1loop_PL(p));
   const double self_energy_PR = Re(self_energy_Fm_1loop_PR(p));
   const auto M_loop = M_tree - self_energy_1 - M_tree * (self_energy_PL
      + self_energy_PR);
   PHYSICAL(MFm) = calculate_singlet_mass(M_loop);
}

void CLASSNAME::calculate_MFtau_pole()
{
   // diagonalization with medium precision
   const double M_tree(MFtau);
   const double p = MFtau;
   const double self_energy_1  = Re(self_energy_Ftau_1loop_1(p));
   const double self_energy_PL = Re(self_energy_Ftau_1loop_PL(p));
   const double self_energy_PR = Re(self_energy_Ftau_1loop_PR(p));
   const auto M_loop = M_tree - self_energy_1 - M_tree * (self_energy_PL
      + self_energy_PR);
   PHYSICAL(MFtau) = calculate_singlet_mass(M_loop);
}

void CLASSNAME::calculate_MSveL_pole()
{
   if (!force_output && problems.is_running_tachyon(CMSSMNoFV_info::SveL)
      )
      return;

   // diagonalization with medium precision
   const double M_tree(get_mass_matrix_SveL());
   const double p = MSveL;
   double self_energy = Re(self_energy_SveL_1loop(p));
   const double mass_sqr = M_tree - self_energy;

   PHYSICAL(MSveL) = SignedAbsSqrt(mass_sqr);
}

void CLASSNAME::calculate_MSvmL_pole()
{
   if (!force_output && problems.is_running_tachyon(CMSSMNoFV_info::SvmL)
      )
      return;

   // diagonalization with medium precision
   const double M_tree(get_mass_matrix_SvmL());
   const double p = MSvmL;
   double self_energy = Re(self_energy_SvmL_1loop(p));
   const double mass_sqr = M_tree - self_energy;

   PHYSICAL(MSvmL) = SignedAbsSqrt(mass_sqr);
}

void CLASSNAME::calculate_MSvtL_pole()
{
   if (!force_output && problems.is_running_tachyon(CMSSMNoFV_info::SvtL)
      )
      return;

   // diagonalization with medium precision
   const double M_tree(get_mass_matrix_SvtL());
   const double p = MSvtL;
   double self_energy = Re(self_energy_SvtL_1loop(p));
   const double mass_sqr = M_tree - self_energy;

   PHYSICAL(MSvtL) = SignedAbsSqrt(mass_sqr);
}

void CLASSNAME::calculate_MSd_pole()
{
   if (!force_output && problems.is_running_tachyon(CMSSMNoFV_info::Sd))
      return;

   // diagonalization with medium precision
   const Eigen::Matrix<double,2,2> M_tree(get_mass_matrix_Sd());

   for (int es = 0; es < 2; ++es) {
      const double p = Abs(MSd(es));
      Eigen::Matrix<double,2,2> self_energy = Re(self_energy_Sd_1loop(
         p));
      const Eigen::Matrix<double,2,2> M_loop(M_tree - self_energy);
      Eigen::Array<double,2,1> eigen_values;
      Eigen::Matrix<double,2,2> mix_ZD;
      #ifdef CHECK_EIGENVALUE_ERROR
         double eigenvalue_error;
         fs_diagonalize_hermitian(M_loop, eigen_values, mix_ZD,
            eigenvalue_error);
         problems.flag_bad_mass(CMSSMNoFV_info::Sd,
            eigenvalue_error > precision * Abs(eigen_values(0)));
      #else
         fs_diagonalize_hermitian(M_loop, eigen_values, mix_ZD);
      #endif
         normalize_to_interval(mix_ZD);

      PHYSICAL(MSd(es)) = SignedAbsSqrt(eigen_values(es));
      if (es == 0)
         PHYSICAL(ZD) = mix_ZD;
   }
}

void CLASSNAME::calculate_MSu_pole()
{
   if (!force_output && problems.is_running_tachyon(CMSSMNoFV_info::Su))
      return;

   // diagonalization with medium precision
   const Eigen::Matrix<double,2,2> M_tree(get_mass_matrix_Su());

   for (int es = 0; es < 2; ++es) {
      const double p = Abs(MSu(es));
      Eigen::Matrix<double,2,2> self_energy = Re(self_energy_Su_1loop(
         p));
      const Eigen::Matrix<double,2,2> M_loop(M_tree - self_energy);
      Eigen::Array<double,2,1> eigen_values;
      Eigen::Matrix<double,2,2> mix_ZU;
      #ifdef CHECK_EIGENVALUE_ERROR
         double eigenvalue_error;
         fs_diagonalize_hermitian(M_loop, eigen_values, mix_ZU,
            eigenvalue_error);
         problems.flag_bad_mass(CMSSMNoFV_info::Su,
            eigenvalue_error > precision * Abs(eigen_values(0)));
      #else
         fs_diagonalize_hermitian(M_loop, eigen_values, mix_ZU);
      #endif
         normalize_to_interval(mix_ZU);

      PHYSICAL(MSu(es)) = SignedAbsSqrt(eigen_values(es));
      if (es == 0)
         PHYSICAL(ZU) = mix_ZU;
   }
}

void CLASSNAME::calculate_MSe_pole()
{
   if (!force_output && problems.is_running_tachyon(CMSSMNoFV_info::Se))
      return;

   // diagonalization with medium precision
   const Eigen::Matrix<double,2,2> M_tree(get_mass_matrix_Se());

   for (int es = 0; es < 2; ++es) {
      const double p = Abs(MSe(es));
      Eigen::Matrix<double,2,2> self_energy = Re(self_energy_Se_1loop(
         p));
      const Eigen::Matrix<double,2,2> M_loop(M_tree - self_energy);
      Eigen::Array<double,2,1> eigen_values;
      Eigen::Matrix<double,2,2> mix_ZE;
      #ifdef CHECK_EIGENVALUE_ERROR
         double eigenvalue_error;
         fs_diagonalize_hermitian(M_loop, eigen_values, mix_ZE,
            eigenvalue_error);
         problems.flag_bad_mass(CMSSMNoFV_info::Se,
            eigenvalue_error > precision * Abs(eigen_values(0)));
      #else
         fs_diagonalize_hermitian(M_loop, eigen_values, mix_ZE);
      #endif
         normalize_to_interval(mix_ZE);

      PHYSICAL(MSe(es)) = SignedAbsSqrt(eigen_values(es));
      if (es == 0)
         PHYSICAL(ZE) = mix_ZE;
   }
}

void CLASSNAME::calculate_MSm_pole()
{
   if (!force_output && problems.is_running_tachyon(CMSSMNoFV_info::Sm))
      return;

   // diagonalization with medium precision
   const Eigen::Matrix<double,2,2> M_tree(get_mass_matrix_Sm());

   for (int es = 0; es < 2; ++es) {
      const double p = Abs(MSm(es));
      Eigen::Matrix<double,2,2> self_energy = Re(self_energy_Sm_1loop(
         p));
      const Eigen::Matrix<double,2,2> M_loop(M_tree - self_energy);
      Eigen::Array<double,2,1> eigen_values;
      Eigen::Matrix<double,2,2> mix_ZM;
      #ifdef CHECK_EIGENVALUE_ERROR
         double eigenvalue_error;
         fs_diagonalize_hermitian(M_loop, eigen_values, mix_ZM,
            eigenvalue_error);
         problems.flag_bad_mass(CMSSMNoFV_info::Sm,
            eigenvalue_error > precision * Abs(eigen_values(0)));
      #else
         fs_diagonalize_hermitian(M_loop, eigen_values, mix_ZM);
      #endif
         normalize_to_interval(mix_ZM);

      PHYSICAL(MSm(es)) = SignedAbsSqrt(eigen_values(es));
      if (es == 0)
         PHYSICAL(ZM) = mix_ZM;
   }
}

void CLASSNAME::calculate_MStau_pole()
{
   if (!force_output && problems.is_running_tachyon(CMSSMNoFV_info::Stau)
      )
      return;

   // diagonalization with medium precision
   const Eigen::Matrix<double,2,2> M_tree(get_mass_matrix_Stau());

   for (int es = 0; es < 2; ++es) {
      const double p = Abs(MStau(es));
      Eigen::Matrix<double,2,2> self_energy = Re(
         self_energy_Stau_1loop(p));
      const Eigen::Matrix<double,2,2> M_loop(M_tree - self_energy);
      Eigen::Array<double,2,1> eigen_values;
      Eigen::Matrix<double,2,2> mix_ZTau;
      #ifdef CHECK_EIGENVALUE_ERROR
         double eigenvalue_error;
         fs_diagonalize_hermitian(M_loop, eigen_values, mix_ZTau,
            eigenvalue_error);
         problems.flag_bad_mass(CMSSMNoFV_info::Stau,
            eigenvalue_error > precision * Abs(eigen_values(0)));
      #else
         fs_diagonalize_hermitian(M_loop, eigen_values, mix_ZTau);
      #endif
         normalize_to_interval(mix_ZTau);

      PHYSICAL(MStau(es)) = SignedAbsSqrt(eigen_values(es));
      if (es == 0)
         PHYSICAL(ZTau) = mix_ZTau;
   }
}

void CLASSNAME::calculate_MSs_pole()
{
   if (!force_output && problems.is_running_tachyon(CMSSMNoFV_info::Ss))
      return;

   // diagonalization with medium precision
   const Eigen::Matrix<double,2,2> M_tree(get_mass_matrix_Ss());

   for (int es = 0; es < 2; ++es) {
      const double p = Abs(MSs(es));
      Eigen::Matrix<double,2,2> self_energy = Re(self_energy_Ss_1loop(
         p));
      const Eigen::Matrix<double,2,2> M_loop(M_tree - self_energy);
      Eigen::Array<double,2,1> eigen_values;
      Eigen::Matrix<double,2,2> mix_ZS;
      #ifdef CHECK_EIGENVALUE_ERROR
         double eigenvalue_error;
         fs_diagonalize_hermitian(M_loop, eigen_values, mix_ZS,
            eigenvalue_error);
         problems.flag_bad_mass(CMSSMNoFV_info::Ss,
            eigenvalue_error > precision * Abs(eigen_values(0)));
      #else
         fs_diagonalize_hermitian(M_loop, eigen_values, mix_ZS);
      #endif
         normalize_to_interval(mix_ZS);

      PHYSICAL(MSs(es)) = SignedAbsSqrt(eigen_values(es));
      if (es == 0)
         PHYSICAL(ZS) = mix_ZS;
   }
}

void CLASSNAME::calculate_MSc_pole()
{
   if (!force_output && problems.is_running_tachyon(CMSSMNoFV_info::Sc))
      return;

   // diagonalization with medium precision
   const Eigen::Matrix<double,2,2> M_tree(get_mass_matrix_Sc());

   for (int es = 0; es < 2; ++es) {
      const double p = Abs(MSc(es));
      Eigen::Matrix<double,2,2> self_energy = Re(self_energy_Sc_1loop(
         p));
      const Eigen::Matrix<double,2,2> M_loop(M_tree - self_energy);
      Eigen::Array<double,2,1> eigen_values;
      Eigen::Matrix<double,2,2> mix_ZC;
      #ifdef CHECK_EIGENVALUE_ERROR
         double eigenvalue_error;
         fs_diagonalize_hermitian(M_loop, eigen_values, mix_ZC,
            eigenvalue_error);
         problems.flag_bad_mass(CMSSMNoFV_info::Sc,
            eigenvalue_error > precision * Abs(eigen_values(0)));
      #else
         fs_diagonalize_hermitian(M_loop, eigen_values, mix_ZC);
      #endif
         normalize_to_interval(mix_ZC);

      PHYSICAL(MSc(es)) = SignedAbsSqrt(eigen_values(es));
      if (es == 0)
         PHYSICAL(ZC) = mix_ZC;
   }
}

void CLASSNAME::calculate_MSb_pole()
{
   if (!force_output && problems.is_running_tachyon(CMSSMNoFV_info::Sb))
      return;

   // diagonalization with medium precision
   const Eigen::Matrix<double,2,2> M_tree(get_mass_matrix_Sb());

   for (int es = 0; es < 2; ++es) {
      const double p = Abs(MSb(es));
      Eigen::Matrix<double,2,2> self_energy = Re(self_energy_Sb_1loop(
         p));
      const Eigen::Matrix<double,2,2> M_loop(M_tree - self_energy);
      Eigen::Array<double,2,1> eigen_values;
      Eigen::Matrix<double,2,2> mix_ZB;
      #ifdef CHECK_EIGENVALUE_ERROR
         double eigenvalue_error;
         fs_diagonalize_hermitian(M_loop, eigen_values, mix_ZB,
            eigenvalue_error);
         problems.flag_bad_mass(CMSSMNoFV_info::Sb,
            eigenvalue_error > precision * Abs(eigen_values(0)));
      #else
         fs_diagonalize_hermitian(M_loop, eigen_values, mix_ZB);
      #endif
         normalize_to_interval(mix_ZB);

      PHYSICAL(MSb(es)) = SignedAbsSqrt(eigen_values(es));
      if (es == 0)
         PHYSICAL(ZB) = mix_ZB;
   }
}

void CLASSNAME::calculate_MSt_pole()
{
   if (!force_output && problems.is_running_tachyon(CMSSMNoFV_info::St))
      return;

   // diagonalization with medium precision
   const Eigen::Matrix<double,2,2> M_tree(get_mass_matrix_St());

   for (int es = 0; es < 2; ++es) {
      const double p = Abs(MSt(es));
      Eigen::Matrix<double,2,2> self_energy = Re(self_energy_St_1loop(
         p));
      const Eigen::Matrix<double,2,2> M_loop(M_tree - self_energy);
      Eigen::Array<double,2,1> eigen_values;
      Eigen::Matrix<double,2,2> mix_ZT;
      #ifdef CHECK_EIGENVALUE_ERROR
         double eigenvalue_error;
         fs_diagonalize_hermitian(M_loop, eigen_values, mix_ZT,
            eigenvalue_error);
         problems.flag_bad_mass(CMSSMNoFV_info::St,
            eigenvalue_error > precision * Abs(eigen_values(0)));
      #else
         fs_diagonalize_hermitian(M_loop, eigen_values, mix_ZT);
      #endif
         normalize_to_interval(mix_ZT);

      PHYSICAL(MSt(es)) = SignedAbsSqrt(eigen_values(es));
      if (es == 0)
         PHYSICAL(ZT) = mix_ZT;
   }
}

void CLASSNAME::calculate_Mhh_pole()
{
   if (!force_output && problems.is_running_tachyon(CMSSMNoFV_info::hh))
      return;

   // diagonalization with high precision
   const auto number_of_mass_iterations = get_number_of_mass_iterations()
      ;
   int iteration = 0;
   double diff = 0.0;
   decltype(Mhh) old_Mhh(Mhh), new_Mhh(Mhh);

   // two-loop Higgs self-energy contributions
   Eigen::Matrix<double,2,2> self_energy_2l(Eigen::Matrix<double,2,2>
      ::Zero());

   if (pole_mass_loop_order > 1) {
      self_energy_2l = self_energy_hh_2loop();
      for (int i = 0; i < 2; i++) {
         for (int k = 0; k < 2; k++) {
            if (!std::isfinite(self_energy_2l(i,k))) {
               self_energy_2l(i,k) = 0.;
               problems.flag_bad_mass(CMSSMNoFV_info::hh);
            }
         }
      }
   }

   do {
      const Eigen::Matrix<double,2,2> M_tree(get_mass_matrix_hh());

      for (int es = 0; es < 2; ++es) {
         const double p = Abs(old_Mhh(es));
         Eigen::Matrix<double,2,2> self_energy = Re(
            self_energy_hh_1loop(p));
         self_energy += self_energy_2l;
         const Eigen::Matrix<double,2,2> M_loop(M_tree -
            self_energy);
         Eigen::Array<double,2,1> eigen_values;
         Eigen::Matrix<double,2,2> mix_ZH;
         #ifdef CHECK_EIGENVALUE_ERROR
            double eigenvalue_error;
            fs_diagonalize_hermitian(M_loop, eigen_values,
               mix_ZH, eigenvalue_error);
            problems.flag_bad_mass(CMSSMNoFV_info::hh,
               eigenvalue_error > precision * Abs(eigen_values(0)));
         #else
            fs_diagonalize_hermitian(M_loop, eigen_values,
               mix_ZH);
         #endif
            normalize_to_interval(mix_ZH);

         PHYSICAL(Mhh(es)) = SignedAbsSqrt(eigen_values(es));
         if (es == 0)
            PHYSICAL(ZH) = mix_ZH;
      }

      new_Mhh = PHYSICAL(Mhh);
      diff = MaxRelDiff(new_Mhh, old_Mhh);
      old_Mhh = new_Mhh;
      iteration++;
   } while (diff > precision
            && iteration < number_of_mass_iterations);

   if (diff > precision)
      problems.flag_no_pole_mass_convergence(CMSSMNoFV_info::hh);
   else
      problems.unflag_no_pole_mass_convergence(CMSSMNoFV_info::hh);
}

void CLASSNAME::calculate_MAh_pole()
{
   if (!force_output && problems.is_running_tachyon(CMSSMNoFV_info::Ah))
      return;

   // diagonalization with high precision
   const auto number_of_mass_iterations = get_number_of_mass_iterations()
      ;
   int iteration = 0;
   double diff = 0.0;
   decltype(MAh) old_MAh(MAh), new_MAh(MAh);

   // two-loop Higgs self-energy contributions
   Eigen::Matrix<double,2,2> self_energy_2l(Eigen::Matrix<double,2,2>
      ::Zero());

   if (pole_mass_loop_order > 1) {
      self_energy_2l = self_energy_Ah_2loop();
      for (int i = 0; i < 2; i++) {
         for (int k = 0; k < 2; k++) {
            if (!std::isfinite(self_energy_2l(i,k))) {
               self_energy_2l(i,k) = 0.;
               problems.flag_bad_mass(CMSSMNoFV_info::Ah);
            }
         }
      }
   }

   do {
      const Eigen::Matrix<double,2,2> M_tree(get_mass_matrix_Ah());

      for (int es = 0; es < 2; ++es) {
         const double p = Abs(old_MAh(es));
         Eigen::Matrix<double,2,2> self_energy = Re(
            self_energy_Ah_1loop(p));
         self_energy += self_energy_2l;
         const Eigen::Matrix<double,2,2> M_loop(M_tree -
            self_energy);
         Eigen::Array<double,2,1> eigen_values;
         Eigen::Matrix<double,2,2> mix_ZA;
         #ifdef CHECK_EIGENVALUE_ERROR
            double eigenvalue_error;
            fs_diagonalize_hermitian(M_loop, eigen_values,
               mix_ZA, eigenvalue_error);
            problems.flag_bad_mass(CMSSMNoFV_info::Ah,
               eigenvalue_error > precision * Abs(eigen_values(0)));
         #else
            fs_diagonalize_hermitian(M_loop, eigen_values,
               mix_ZA);
         #endif
            normalize_to_interval(mix_ZA);

         PHYSICAL(MAh(es)) = SignedAbsSqrt(eigen_values(es));
         if (es == 1)
            PHYSICAL(ZA) = mix_ZA;
      }

      new_MAh = PHYSICAL(MAh);
      diff = MaxRelDiff(new_MAh, old_MAh);
      old_MAh = new_MAh;
      iteration++;
   } while (diff > precision
            && iteration < number_of_mass_iterations);

   if (diff > precision)
      problems.flag_no_pole_mass_convergence(CMSSMNoFV_info::Ah);
   else
      problems.unflag_no_pole_mass_convergence(CMSSMNoFV_info::Ah);
}

void CLASSNAME::calculate_MHpm_pole()
{
   if (!force_output && problems.is_running_tachyon(CMSSMNoFV_info::Hpm))
      return;

   // diagonalization with high precision
   const auto number_of_mass_iterations = get_number_of_mass_iterations()
      ;
   int iteration = 0;
   double diff = 0.0;
   decltype(MHpm) old_MHpm(MHpm), new_MHpm(MHpm);

   do {
      const Eigen::Matrix<double,2,2> M_tree(get_mass_matrix_Hpm());

      for (int es = 0; es < 2; ++es) {
         const double p = Abs(old_MHpm(es));
         Eigen::Matrix<double,2,2> self_energy = Re(
            self_energy_Hpm_1loop(p));
         const Eigen::Matrix<double,2,2> M_loop(M_tree -
            self_energy);
         Eigen::Array<double,2,1> eigen_values;
         Eigen::Matrix<double,2,2> mix_ZP;
         #ifdef CHECK_EIGENVALUE_ERROR
            double eigenvalue_error;
            fs_diagonalize_hermitian(M_loop, eigen_values,
               mix_ZP, eigenvalue_error);
            problems.flag_bad_mass(CMSSMNoFV_info::Hpm,
               eigenvalue_error > precision * Abs(eigen_values(0)));
         #else
            fs_diagonalize_hermitian(M_loop, eigen_values,
               mix_ZP);
         #endif
            normalize_to_interval(mix_ZP);

         PHYSICAL(MHpm(es)) = SignedAbsSqrt(eigen_values(es));
         if (es == 1)
            PHYSICAL(ZP) = mix_ZP;
      }

      new_MHpm = PHYSICAL(MHpm);
      diff = MaxRelDiff(new_MHpm, old_MHpm);
      old_MHpm = new_MHpm;
      iteration++;
   } while (diff > precision
            && iteration < number_of_mass_iterations);

   if (diff > precision)
      problems.flag_no_pole_mass_convergence(CMSSMNoFV_info::Hpm);
   else
      problems.unflag_no_pole_mass_convergence(CMSSMNoFV_info::Hpm);
}

void CLASSNAME::calculate_MChi_pole()
{
   // diagonalization with medium precision
   const Eigen::Matrix<double,4,4> M_tree(get_mass_matrix_Chi());
   for (int es = 0; es < 4; ++es) {
      const double p = Abs(MChi(es));
      const Eigen::Matrix<double,4,4> self_energy_1  = Re(
         self_energy_Chi_1loop_1(p));
      const Eigen::Matrix<double,4,4> self_energy_PL = Re(
         self_energy_Chi_1loop_PL(p));
      const Eigen::Matrix<double,4,4> self_energy_PR = Re(
         self_energy_Chi_1loop_PR(p));
      const Eigen::Matrix<double,4,4> delta_M(- self_energy_PR *
         M_tree - M_tree * self_energy_PL - self_energy_1);
      const Eigen::Matrix<double,4,4> M_loop(M_tree + 0.5 * (delta_M +
         delta_M.transpose()));
      Eigen::Array<double,4,1> eigen_values;
      decltype(ZN) mix_ZN;
      #ifdef CHECK_EIGENVALUE_ERROR
         double eigenvalue_error;
         fs_diagonalize_symmetric(M_loop, eigen_values, mix_ZN,
            eigenvalue_error);
         problems.flag_bad_mass(CMSSMNoFV_info::Chi,
            eigenvalue_error > precision * Abs(eigen_values(0)));
      #else
         fs_diagonalize_symmetric(M_loop, eigen_values, mix_ZN);
      #endif
         normalize_to_interval(mix_ZN);
      if (es == 0)
         PHYSICAL(ZN) = mix_ZN;
      PHYSICAL(MChi(es)) = Abs(eigen_values(es));
   }
}

void CLASSNAME::calculate_MCha_pole()
{
   // diagonalization with medium precision
   const Eigen::Matrix<double,2,2> M_tree(get_mass_matrix_Cha());
   for (int es = 0; es < 2; ++es) {
      const double p = Abs(MCha(es));
      const Eigen::Matrix<double,2,2> self_energy_1  = Re(
         self_energy_Cha_1loop_1(p));
      const Eigen::Matrix<double,2,2> self_energy_PL = Re(
         self_energy_Cha_1loop_PL(p));
      const Eigen::Matrix<double,2,2> self_energy_PR = Re(
         self_energy_Cha_1loop_PR(p));
      const Eigen::Matrix<double,2,2> delta_M(- self_energy_PR *
         M_tree - M_tree * self_energy_PL - self_energy_1);
      const Eigen::Matrix<double,2,2> M_loop(M_tree + delta_M);
      Eigen::Array<double,2,1> eigen_values;
      decltype(UM) mix_UM;
      decltype(UP) mix_UP;
   #ifdef CHECK_EIGENVALUE_ERROR
      double eigenvalue_error;
      fs_svd(M_loop, eigen_values, mix_UM, mix_UP, eigenvalue_error);
      problems.flag_bad_mass(CMSSMNoFV_info::Cha, eigenvalue_error >
         precision * Abs(eigen_values(0)));
   #else
      fs_svd(M_loop, eigen_values, mix_UM, mix_UP);
   #endif
      if (es == 0) {
         PHYSICAL(UM) = mix_UM;
         PHYSICAL(UP) = mix_UP;
      }
      PHYSICAL(MCha(es)) = Abs(eigen_values(es));
   }
}

void CLASSNAME::calculate_MVWm_pole()
{
   if (!force_output && problems.is_running_tachyon(CMSSMNoFV_info::VWm))
      return;

   // diagonalization with medium precision
   const double M_tree(Sqr(MVWm));
   const double p = MVWm;
   const double self_energy = Re(self_energy_VWm_1loop(p));
   const double mass_sqr = M_tree - self_energy;

   if (mass_sqr < 0.)
      problems.flag_pole_tachyon(CMSSMNoFV_info::VWm);

   PHYSICAL(MVWm) = AbsSqrt(mass_sqr);
}

double CLASSNAME::calculate_MVWm_pole(double p)
{
   if (!force_output && problems.is_running_tachyon(CMSSMNoFV_info::VWm))
      return 0.;

   const double self_energy = Re(self_energy_VWm_1loop(p));
   const double mass_sqr = Sqr(MVWm) - self_energy;

   if (mass_sqr < 0.)
      problems.flag_pole_tachyon(CMSSMNoFV_info::VWm);

   return AbsSqrt(mass_sqr);
}

double CLASSNAME::calculate_MVZ_pole(double p)
{
   if (!force_output && problems.is_running_tachyon(CMSSMNoFV_info::VZ))
      return 0.;

   const double self_energy = Re(self_energy_VZ_1loop(p));
   const double mass_sqr = Sqr(MVZ) - self_energy;

   if (mass_sqr < 0.)
      problems.flag_pole_tachyon(CMSSMNoFV_info::VZ);

   return AbsSqrt(mass_sqr);
}


double CLASSNAME::calculate_MFve_DRbar(double m_pole) const
{
   const double p = m_pole;
   const double self_energy_1  = Re(self_energy_Fve_1loop_1(p));
   const double self_energy_PL = Re(self_energy_Fve_1loop_PL(p));
   const double self_energy_PR = Re(self_energy_Fve_1loop_PR(p));

   const double m_drbar = m_pole + self_energy_1 + m_pole * (
      self_energy_PL + self_energy_PR);

   return m_drbar;
}

double CLASSNAME::calculate_MFvm_DRbar(double m_pole) const
{
   const double p = m_pole;
   const double self_energy_1  = Re(self_energy_Fvm_1loop_1(p));
   const double self_energy_PL = Re(self_energy_Fvm_1loop_PL(p));
   const double self_energy_PR = Re(self_energy_Fvm_1loop_PR(p));

   const double m_drbar = m_pole + self_energy_1 + m_pole * (
      self_energy_PL + self_energy_PR);

   return m_drbar;
}

double CLASSNAME::calculate_MFvt_DRbar(double m_pole) const
{
   const double p = m_pole;
   const double self_energy_1  = Re(self_energy_Fvt_1loop_1(p));
   const double self_energy_PL = Re(self_energy_Fvt_1loop_PL(p));
   const double self_energy_PR = Re(self_energy_Fvt_1loop_PR(p));

   const double m_drbar = m_pole + self_energy_1 + m_pole * (
      self_energy_PL + self_energy_PR);

   return m_drbar;
}

double CLASSNAME::calculate_MFe_DRbar(double m_sm_msbar) const
{
   const double p = m_sm_msbar;
   const double self_energy_1  = Re(self_energy_Fe_1loop_1_heavy_rotated(
      p));
   const double self_energy_PL = Re(self_energy_Fe_1loop_PL_heavy_rotated
      (p));
   const double self_energy_PR = Re(self_energy_Fe_1loop_PR_heavy_rotated
      (p));
   const double drbar_conversion = 1 - 0.0023747152416172916*(0.6*Sqr(g1)
      - Sqr(g2));
   const double m_sm_drbar = m_sm_msbar * drbar_conversion;
   const double delta_mf_1loop = - self_energy_1/m_sm_drbar -
      self_energy_PL - self_energy_PR;

   const double m_susy_drbar = m_sm_drbar / (1.0 + delta_mf_1loop);

   return m_susy_drbar;
}

double CLASSNAME::calculate_MFm_DRbar(double m_sm_msbar) const
{
   const double p = m_sm_msbar;
   const double self_energy_1  = Re(self_energy_Fm_1loop_1_heavy_rotated(
      p));
   const double self_energy_PL = Re(self_energy_Fm_1loop_PL_heavy_rotated
      (p));
   const double self_energy_PR = Re(self_energy_Fm_1loop_PR_heavy_rotated
      (p));
   const double drbar_conversion = 1 - 0.0023747152416172916*(0.6*Sqr(g1)
      - Sqr(g2));
   const double m_sm_drbar = m_sm_msbar * drbar_conversion;
   const double delta_mf_1loop = - self_energy_1/m_sm_drbar -
      self_energy_PL - self_energy_PR;

   const double m_susy_drbar = m_sm_drbar / (1.0 + delta_mf_1loop);

   return m_susy_drbar;
}

double CLASSNAME::calculate_MFtau_DRbar(double m_sm_msbar) const
{
   const double p = m_sm_msbar;
   const double self_energy_1  = Re(
      self_energy_Ftau_1loop_1_heavy_rotated(p));
   const double self_energy_PL = Re(
      self_energy_Ftau_1loop_PL_heavy_rotated(p));
   const double self_energy_PR = Re(
      self_energy_Ftau_1loop_PR_heavy_rotated(p));
   const double drbar_conversion = 1 - 0.0023747152416172916*(0.6*Sqr(g1)
      - Sqr(g2));
   const double m_sm_drbar = m_sm_msbar * drbar_conversion;
   const double delta_mf_1loop = - self_energy_1/m_sm_drbar -
      self_energy_PL - self_energy_PR;

   const double m_susy_drbar = m_sm_drbar / (1.0 + delta_mf_1loop);

   return m_susy_drbar;
}

double CLASSNAME::calculate_MFu_DRbar(double m_pole) const
{
   const double p = m_pole;
   const double self_energy_1  = Re(self_energy_Fu_1loop_1(p));
   const double self_energy_PL = Re(self_energy_Fu_1loop_PL(p));
   const double self_energy_PR = Re(self_energy_Fu_1loop_PR(p));

   const double m_drbar = m_pole + self_energy_1 + m_pole * (
      self_energy_PL + self_energy_PR);

   return m_drbar;
}

double CLASSNAME::calculate_MFc_DRbar(double m_pole) const
{
   const double p = m_pole;
   const double self_energy_1  = Re(self_energy_Fc_1loop_1(p));
   const double self_energy_PL = Re(self_energy_Fc_1loop_PL(p));
   const double self_energy_PR = Re(self_energy_Fc_1loop_PR(p));

   const double m_drbar = m_pole + self_energy_1 + m_pole * (
      self_energy_PL + self_energy_PR);

   return m_drbar;
}

double CLASSNAME::calculate_MFt_DRbar(double m_pole) const
{
   const double p = m_pole;
   const double self_energy_1  = Re(self_energy_Ft_1loop_1_heavy_rotated(
      p));
   const double self_energy_PL = Re(self_energy_Ft_1loop_PL_heavy_rotated
      (p));
   const double self_energy_PR = Re(self_energy_Ft_1loop_PR_heavy_rotated
      (p));

   const double currentScale = get_scale();
   double qcd_1l = 0., qcd_2l = 0., qcd_3l = 0.;

   qcd_1l = -0.008443431970194815*(5. - 3.*Log(Sqr(MFt)/Sqr(currentScale)
      ))*Sqr(g3);

   if (get_thresholds() > 1 && threshold_corrections.mt > 1) {
      const double q_2l = 0.005191204615668296*Quad(g3) +
         0.0032883224409535764*Log(Sqr(currentScale)/Sqr(MFt))*Quad(g3) +
         0.0008822328500119351*Quad(g3)*Sqr(Log(Sqr(currentScale)/Sqr(MFt)));

      qcd_2l = -q_2l + qcd_1l * qcd_1l;
   }

   const double m_susy_drbar = m_pole + self_energy_1 + m_pole * (
      self_energy_PL + self_energy_PR + qcd_1l + qcd_2l + qcd_3l);

   return m_susy_drbar;
}

double CLASSNAME::calculate_MFd_DRbar(double m_pole) const
{
   const double p = m_pole;
   const double self_energy_1  = Re(self_energy_Fd_1loop_1(p));
   const double self_energy_PL = Re(self_energy_Fd_1loop_PL(p));
   const double self_energy_PR = Re(self_energy_Fd_1loop_PR(p));

   const double m_drbar = m_pole + self_energy_1 + m_pole * (
      self_energy_PL + self_energy_PR);

   return m_drbar;
}

double CLASSNAME::calculate_MFs_DRbar(double m_pole) const
{
   const double p = m_pole;
   const double self_energy_1  = Re(self_energy_Fs_1loop_1(p));
   const double self_energy_PL = Re(self_energy_Fs_1loop_PL(p));
   const double self_energy_PR = Re(self_energy_Fs_1loop_PR(p));

   const double m_drbar = m_pole + self_energy_1 + m_pole * (
      self_energy_PL + self_energy_PR);

   return m_drbar;
}

double CLASSNAME::calculate_MFb_DRbar(double m_sm_msbar) const
{
   const double p = m_sm_msbar;
   const double self_energy_1  = Re(self_energy_Fb_1loop_1_heavy_rotated(
      p));
   const double self_energy_PL = Re(self_energy_Fb_1loop_PL_heavy_rotated
      (p));
   const double self_energy_PR = Re(self_energy_Fb_1loop_PR_heavy_rotated
      (p));
   const double m_tree = MFb;
   const double drbar_conversion = 1 + 0.0006860288475783287*Sqr(g1) +
      0.0023747152416172916*Sqr(g2) - 0.008443431970194815*Sqr(g3);
   const double m_sm_drbar = m_sm_msbar * drbar_conversion;
   const double delta_mb_1loop = - self_energy_1/m_tree - self_energy_PL
      - self_energy_PR;
   double qcd_2l = 0.;

   const double m_susy_drbar = m_sm_drbar / (1.0 + delta_mb_1loop +
      qcd_2l);

   return m_susy_drbar;
}

double CLASSNAME::calculate_MVP_DRbar(double)
{
   return 0.0;
}

double CLASSNAME::calculate_MVZ_DRbar(double m_pole)
{
   const double p = m_pole;
   const double self_energy = Re(self_energy_VZ_1loop(p));
   const double mass_sqr = Sqr(m_pole) + self_energy;

   if (mass_sqr < 0.) {
      problems.flag_pole_tachyon(CMSSMNoFV_info::VZ);
      return m_pole;
   }

   return AbsSqrt(mass_sqr);
}

double CLASSNAME::calculate_MVWm_DRbar(double m_pole)
{
   const double p = m_pole;
   const double self_energy = Re(self_energy_VWm_1loop(p));
   const double mass_sqr = Sqr(m_pole) + self_energy;

   if (mass_sqr < 0.) {
      problems.flag_pole_tachyon(CMSSMNoFV_info::VWm);
      return m_pole;
   }

   return AbsSqrt(mass_sqr);
}


double CLASSNAME::v() const
{
   return Sqrt(Sqr(vd) + Sqr(vu));
}

double CLASSNAME::Betax() const
{
   return ArcSin(Abs(ZP(0,1)));
}

double CLASSNAME::Alpha() const
{
   return ArcTan(ZH(1,1)/ZH(0,1));
}

double CLASSNAME::ThetaW() const
{
   return ArcCos(Abs(ZZ(0,0)));
}


std::ostream& operator<<(std::ostream& ostr, const CMSSMNoFV_mass_eigenstates& model)
{
   model.print(ostr);
   return ostr;
}

} // namespace flexiblesusy
