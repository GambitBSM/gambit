#ifndef __wrapper_CMSSM_mass_eigenstates_def_FlexibleSUSY_CMSSM_2_0_1_h__
#define __wrapper_CMSSM_mass_eigenstates_def_FlexibleSUSY_CMSSM_2_0_1_h__

#include <string>
#include <ostream>
#include <complex>
#include "wrapper_CMSSM_input_parameters_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace flexiblesusy
    {
        
        // Member functions: 
        inline void CMSSM_mass_eigenstates::calculate_DRbar_masses()
        {
            get_BEptr()->calculate_DRbar_masses();
        }
        
        inline void CMSSM_mass_eigenstates::calculate_pole_masses()
        {
            get_BEptr()->calculate_pole_masses();
        }
        
        inline void CMSSM_mass_eigenstates::check_pole_masses_for_tachyons()
        {
            get_BEptr()->check_pole_masses_for_tachyons();
        }
        
        inline void CMSSM_mass_eigenstates::clear()
        {
            get_BEptr()->clear();
        }
        
        inline void CMSSM_mass_eigenstates::clear_DRbar_parameters()
        {
            get_BEptr()->clear_DRbar_parameters();
        }
        
        inline void CMSSM_mass_eigenstates::do_calculate_sm_pole_masses(bool arg_1)
        {
            get_BEptr()->do_calculate_sm_pole_masses(arg_1);
        }
        
        inline bool CMSSM_mass_eigenstates::do_calculate_sm_pole_masses() const
        {
            return get_BEptr()->do_calculate_sm_pole_masses();
        }
        
        inline void CMSSM_mass_eigenstates::do_calculate_bsm_pole_masses(bool arg_1)
        {
            get_BEptr()->do_calculate_bsm_pole_masses(arg_1);
        }
        
        inline bool CMSSM_mass_eigenstates::do_calculate_bsm_pole_masses() const
        {
            return get_BEptr()->do_calculate_bsm_pole_masses();
        }
        
        inline void CMSSM_mass_eigenstates::do_force_output(bool arg_1)
        {
            get_BEptr()->do_force_output(arg_1);
        }
        
        inline bool CMSSM_mass_eigenstates::do_force_output() const
        {
            return get_BEptr()->do_force_output();
        }
        
        inline void CMSSM_mass_eigenstates::reorder_DRbar_masses()
        {
            get_BEptr()->reorder_DRbar_masses();
        }
        
        inline void CMSSM_mass_eigenstates::reorder_pole_masses()
        {
            get_BEptr()->reorder_pole_masses();
        }
        
        inline void CMSSM_mass_eigenstates::set_ewsb_iteration_precision(double arg_1)
        {
            get_BEptr()->set_ewsb_iteration_precision(arg_1);
        }
        
        inline void CMSSM_mass_eigenstates::set_ewsb_loop_order(int arg_1)
        {
            get_BEptr()->set_ewsb_loop_order(arg_1);
        }
        
        inline void CMSSM_mass_eigenstates::set_pole_mass_loop_order(int arg_1)
        {
            get_BEptr()->set_pole_mass_loop_order(arg_1);
        }
        
        inline int CMSSM_mass_eigenstates::get_pole_mass_loop_order() const
        {
            return get_BEptr()->get_pole_mass_loop_order();
        }
        
        inline double CMSSM_mass_eigenstates::get_ewsb_iteration_precision() const
        {
            return get_BEptr()->get_ewsb_iteration_precision();
        }
        
        inline double CMSSM_mass_eigenstates::get_ewsb_loop_order() const
        {
            return get_BEptr()->get_ewsb_loop_order();
        }
        
        inline int CMSSM_mass_eigenstates::solve_ewsb_tree_level()
        {
            return get_BEptr()->solve_ewsb_tree_level();
        }
        
        inline int CMSSM_mass_eigenstates::solve_ewsb_one_loop()
        {
            return get_BEptr()->solve_ewsb_one_loop();
        }
        
        inline int CMSSM_mass_eigenstates::solve_ewsb()
        {
            return get_BEptr()->solve_ewsb();
        }
        
        inline void CMSSM_mass_eigenstates::calculate_spectrum()
        {
            get_BEptr()->calculate_spectrum();
        }
        
        inline void CMSSM_mass_eigenstates::clear_problems()
        {
            get_BEptr()->clear_problems();
        }
        
        inline ::std::basic_string<char> CMSSM_mass_eigenstates::name() const
        {
            return get_BEptr()->name();
        }
        
        inline void CMSSM_mass_eigenstates::run_to(double scale, double eps)
        {
            get_BEptr()->run_to(scale, eps);
        }
        
        inline void CMSSM_mass_eigenstates::run_to(double scale)
        {
            get_BEptr()->run_to__BOSS(scale);
        }
        
        inline void CMSSM_mass_eigenstates::print(::std::basic_ostream<char>& out) const
        {
            get_BEptr()->print(out);
        }
        
        inline void CMSSM_mass_eigenstates::print() const
        {
            get_BEptr()->print__BOSS();
        }
        
        inline void CMSSM_mass_eigenstates::set_precision(double arg_1)
        {
            get_BEptr()->set_precision(arg_1);
        }
        
        inline double CMSSM_mass_eigenstates::get_precision() const
        {
            return get_BEptr()->get_precision();
        }
        
        inline double CMSSM_mass_eigenstates::get_MVG() const
        {
            return get_BEptr()->get_MVG();
        }
        
        inline double CMSSM_mass_eigenstates::get_MGlu() const
        {
            return get_BEptr()->get_MGlu();
        }
        
        inline double CMSSM_mass_eigenstates::get_MFv(int i) const
        {
            return get_BEptr()->get_MFv(i);
        }
        
        inline double CMSSM_mass_eigenstates::get_MSd(int i) const
        {
            return get_BEptr()->get_MSd(i);
        }
        
        inline double CMSSM_mass_eigenstates::get_MSv(int i) const
        {
            return get_BEptr()->get_MSv(i);
        }
        
        inline double CMSSM_mass_eigenstates::get_MSu(int i) const
        {
            return get_BEptr()->get_MSu(i);
        }
        
        inline double CMSSM_mass_eigenstates::get_MSe(int i) const
        {
            return get_BEptr()->get_MSe(i);
        }
        
        inline double CMSSM_mass_eigenstates::get_Mhh(int i) const
        {
            return get_BEptr()->get_Mhh(i);
        }
        
        inline double CMSSM_mass_eigenstates::get_MAh(int i) const
        {
            return get_BEptr()->get_MAh(i);
        }
        
        inline double CMSSM_mass_eigenstates::get_MHpm(int i) const
        {
            return get_BEptr()->get_MHpm(i);
        }
        
        inline double CMSSM_mass_eigenstates::get_MChi(int i) const
        {
            return get_BEptr()->get_MChi(i);
        }
        
        inline double CMSSM_mass_eigenstates::get_MCha(int i) const
        {
            return get_BEptr()->get_MCha(i);
        }
        
        inline double CMSSM_mass_eigenstates::get_MFe(int i) const
        {
            return get_BEptr()->get_MFe(i);
        }
        
        inline double CMSSM_mass_eigenstates::get_MFd(int i) const
        {
            return get_BEptr()->get_MFd(i);
        }
        
        inline double CMSSM_mass_eigenstates::get_MFu(int i) const
        {
            return get_BEptr()->get_MFu(i);
        }
        
        inline double CMSSM_mass_eigenstates::get_MVWm() const
        {
            return get_BEptr()->get_MVWm();
        }
        
        inline double CMSSM_mass_eigenstates::get_MVP() const
        {
            return get_BEptr()->get_MVP();
        }
        
        inline double CMSSM_mass_eigenstates::get_MVZ() const
        {
            return get_BEptr()->get_MVZ();
        }
        
        inline double CMSSM_mass_eigenstates::get_ZD(int i, int k) const
        {
            return get_BEptr()->get_ZD(i, k);
        }
        
        inline double CMSSM_mass_eigenstates::get_ZV(int i, int k) const
        {
            return get_BEptr()->get_ZV(i, k);
        }
        
        inline double CMSSM_mass_eigenstates::get_ZU(int i, int k) const
        {
            return get_BEptr()->get_ZU(i, k);
        }
        
        inline double CMSSM_mass_eigenstates::get_ZE(int i, int k) const
        {
            return get_BEptr()->get_ZE(i, k);
        }
        
        inline double CMSSM_mass_eigenstates::get_ZH(int i, int k) const
        {
            return get_BEptr()->get_ZH(i, k);
        }
        
        inline double CMSSM_mass_eigenstates::get_ZA(int i, int k) const
        {
            return get_BEptr()->get_ZA(i, k);
        }
        
        inline double CMSSM_mass_eigenstates::get_ZP(int i, int k) const
        {
            return get_BEptr()->get_ZP(i, k);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::get_ZN(int i, int k) const
        {
            return get_BEptr()->get_ZN(i, k);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::get_UM(int i, int k) const
        {
            return get_BEptr()->get_UM(i, k);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::get_UP(int i, int k) const
        {
            return get_BEptr()->get_UP(i, k);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::get_ZEL(int i, int k) const
        {
            return get_BEptr()->get_ZEL(i, k);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::get_ZER(int i, int k) const
        {
            return get_BEptr()->get_ZER(i, k);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::get_ZDL(int i, int k) const
        {
            return get_BEptr()->get_ZDL(i, k);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::get_ZDR(int i, int k) const
        {
            return get_BEptr()->get_ZDR(i, k);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::get_ZUL(int i, int k) const
        {
            return get_BEptr()->get_ZUL(i, k);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::get_ZUR(int i, int k) const
        {
            return get_BEptr()->get_ZUR(i, k);
        }
        
        inline double CMSSM_mass_eigenstates::get_ZZ(int i, int k) const
        {
            return get_BEptr()->get_ZZ(i, k);
        }
        
        inline void CMSSM_mass_eigenstates::set_PhaseGlu(::std::complex<double> PhaseGlu_)
        {
            get_BEptr()->set_PhaseGlu(PhaseGlu_);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::get_PhaseGlu() const
        {
            return get_BEptr()->get_PhaseGlu();
        }
        
        inline double CMSSM_mass_eigenstates::get_mass_matrix_VG() const
        {
            return get_BEptr()->get_mass_matrix_VG();
        }
        
        inline void CMSSM_mass_eigenstates::calculate_MVG()
        {
            get_BEptr()->calculate_MVG();
        }
        
        inline double CMSSM_mass_eigenstates::get_mass_matrix_Glu() const
        {
            return get_BEptr()->get_mass_matrix_Glu();
        }
        
        inline void CMSSM_mass_eigenstates::calculate_MGlu()
        {
            get_BEptr()->calculate_MGlu();
        }
        
        inline void CMSSM_mass_eigenstates::calculate_MFv()
        {
            get_BEptr()->calculate_MFv();
        }
        
        inline void CMSSM_mass_eigenstates::calculate_MSd()
        {
            get_BEptr()->calculate_MSd();
        }
        
        inline void CMSSM_mass_eigenstates::calculate_MSv()
        {
            get_BEptr()->calculate_MSv();
        }
        
        inline void CMSSM_mass_eigenstates::calculate_MSu()
        {
            get_BEptr()->calculate_MSu();
        }
        
        inline void CMSSM_mass_eigenstates::calculate_MSe()
        {
            get_BEptr()->calculate_MSe();
        }
        
        inline void CMSSM_mass_eigenstates::calculate_Mhh()
        {
            get_BEptr()->calculate_Mhh();
        }
        
        inline void CMSSM_mass_eigenstates::calculate_MAh()
        {
            get_BEptr()->calculate_MAh();
        }
        
        inline void CMSSM_mass_eigenstates::calculate_MHpm()
        {
            get_BEptr()->calculate_MHpm();
        }
        
        inline void CMSSM_mass_eigenstates::calculate_MChi()
        {
            get_BEptr()->calculate_MChi();
        }
        
        inline void CMSSM_mass_eigenstates::calculate_MCha()
        {
            get_BEptr()->calculate_MCha();
        }
        
        inline void CMSSM_mass_eigenstates::calculate_MFe()
        {
            get_BEptr()->calculate_MFe();
        }
        
        inline void CMSSM_mass_eigenstates::calculate_MFd()
        {
            get_BEptr()->calculate_MFd();
        }
        
        inline void CMSSM_mass_eigenstates::calculate_MFu()
        {
            get_BEptr()->calculate_MFu();
        }
        
        inline double CMSSM_mass_eigenstates::get_mass_matrix_VWm() const
        {
            return get_BEptr()->get_mass_matrix_VWm();
        }
        
        inline void CMSSM_mass_eigenstates::calculate_MVWm()
        {
            get_BEptr()->calculate_MVWm();
        }
        
        inline void CMSSM_mass_eigenstates::calculate_MVPVZ()
        {
            get_BEptr()->calculate_MVPVZ();
        }
        
        inline double CMSSM_mass_eigenstates::get_ewsb_eq_hh_1() const
        {
            return get_BEptr()->get_ewsb_eq_hh_1();
        }
        
        inline double CMSSM_mass_eigenstates::get_ewsb_eq_hh_2() const
        {
            return get_BEptr()->get_ewsb_eq_hh_2();
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUSdconjUSdVZVZ(int gO1, int gO2) const
        {
            return get_BEptr()->CpUSdconjUSdVZVZ(gO1, gO2);
        }
        
        inline double CMSSM_mass_eigenstates::CpUSdconjUSdconjVWmVWm(int gO1, int gO2) const
        {
            return get_BEptr()->CpUSdconjUSdconjVWmVWm(gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpAhAhUSdconjUSd(int gI1, int gI2, int gO1, int gO2) const
        {
            return get_BEptr()->CpAhAhUSdconjUSd(gI1, gI2, gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CphhhhUSdconjUSd(int gI1, int gI2, int gO1, int gO2) const
        {
            return get_BEptr()->CphhhhUSdconjUSd(gI1, gI2, gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpHpmUSdconjHpmconjUSd(int gI1, int gO1, int gI2, int gO2) const
        {
            return get_BEptr()->CpHpmUSdconjHpmconjUSd(gI1, gO1, gI2, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUSdSvconjUSdconjSv(int gO1, int gI1, int gO2, int gI2) const
        {
            return get_BEptr()->CpUSdSvconjUSdconjSv(gO1, gI1, gO2, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpChaFuconjUSdPR(int gI2, int gI1, int gO2) const
        {
            return get_BEptr()->CpChaFuconjUSdPR(gI2, gI1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpChaFuconjUSdPL(int gI2, int gI1, int gO1) const
        {
            return get_BEptr()->CpChaFuconjUSdPL(gI2, gI1, gO1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpChiFdconjUSdPR(int gI2, int gI1, int gO2) const
        {
            return get_BEptr()->CpChiFdconjUSdPR(gI2, gI1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpChiFdconjUSdPL(int gI2, int gI1, int gO1) const
        {
            return get_BEptr()->CpChiFdconjUSdPL(gI2, gI1, gO1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUSdconjUSdconjSdSd(int gO1, int gO2, int gI1, int gI2) const
        {
            return get_BEptr()->CpUSdconjUSdconjSdSd(gO1, gO2, gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUSdconjUSdconjSuSu(int gO1, int gO2, int gI1, int gI2) const
        {
            return get_BEptr()->CpUSdconjUSdconjSuSu(gO1, gO2, gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUSdSeconjUSdconjSe(int gO1, int gI1, int gO2, int gI2) const
        {
            return get_BEptr()->CpUSdSeconjUSdconjSe(gO1, gI1, gO2, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpAhSdconjUSd(int gI2, int gI1, int gO2) const
        {
            return get_BEptr()->CpAhSdconjUSd(gI2, gI1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CphhSdconjUSd(int gI2, int gI1, int gO2) const
        {
            return get_BEptr()->CphhSdconjUSd(gI2, gI1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpHpmSuconjUSd(int gI2, int gI1, int gO2) const
        {
            return get_BEptr()->CpHpmSuconjUSd(gI2, gI1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpGluFdconjUSdPR(int gI2, int gO2) const
        {
            return get_BEptr()->CpGluFdconjUSdPR(gI2, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpGluFdconjUSdPL(int gI2, int gO1) const
        {
            return get_BEptr()->CpGluFdconjUSdPL(gI2, gO1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpSdconjUSdVG(int gI2, int gO2) const
        {
            return get_BEptr()->CpSdconjUSdVG(gI2, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpSdconjUSdVP(int gI2, int gO2) const
        {
            return get_BEptr()->CpSdconjUSdVP(gI2, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpSdconjUSdVZ(int gI2, int gO2) const
        {
            return get_BEptr()->CpSdconjUSdVZ(gI2, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpSuconjUSdVWm(int gI2, int gO2) const
        {
            return get_BEptr()->CpSuconjUSdVWm(gI2, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUSvconjUSvVZVZ(int gO1, int gO2) const
        {
            return get_BEptr()->CpUSvconjUSvVZVZ(gO1, gO2);
        }
        
        inline double CMSSM_mass_eigenstates::CpUSvconjUSvconjVWmVWm(int gO1, int gO2) const
        {
            return get_BEptr()->CpUSvconjUSvconjVWmVWm(gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpAhAhUSvconjUSv(int gI1, int gI2, int gO1, int gO2) const
        {
            return get_BEptr()->CpAhAhUSvconjUSv(gI1, gI2, gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CphhhhUSvconjUSv(int gI1, int gI2, int gO1, int gO2) const
        {
            return get_BEptr()->CphhhhUSvconjUSv(gI1, gI2, gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpHpmUSvconjHpmconjUSv(int gI1, int gO1, int gI2, int gO2) const
        {
            return get_BEptr()->CpHpmUSvconjHpmconjUSv(gI1, gO1, gI2, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarChaFeconjUSvPR(int gI1, int gI2, int gO2) const
        {
            return get_BEptr()->CpbarChaFeconjUSvPR(gI1, gI2, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarChaFeconjUSvPL(int gI1, int gI2, int gO1) const
        {
            return get_BEptr()->CpbarChaFeconjUSvPL(gI1, gI2, gO1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpSeconjHpmconjUSv(int gI2, int gI1, int gO2) const
        {
            return get_BEptr()->CpSeconjHpmconjUSv(gI2, gI1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpSvUSvconjSvconjUSv(int gI1, int gO1, int gI2, int gO2) const
        {
            return get_BEptr()->CpSvUSvconjSvconjUSv(gI1, gO1, gI2, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CphhSvconjUSv(int gI2, int gI1, int gO2) const
        {
            return get_BEptr()->CphhSvconjUSv(gI2, gI1, gO2);
        }
        
        inline double CMSSM_mass_eigenstates::CpChiFvconjUSvPR(int arg_1, int arg_2, int arg_3) const
        {
            return get_BEptr()->CpChiFvconjUSvPR(arg_1, arg_2, arg_3);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpChiFvconjUSvPL(int gI2, int gI1, int gO1) const
        {
            return get_BEptr()->CpChiFvconjUSvPL(gI2, gI1, gO1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpSdUSvconjSdconjUSv(int gI1, int gO1, int gI2, int gO2) const
        {
            return get_BEptr()->CpSdUSvconjSdconjUSv(gI1, gO1, gI2, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpSeUSvconjSeconjUSv(int gI1, int gO1, int gI2, int gO2) const
        {
            return get_BEptr()->CpSeUSvconjSeconjUSv(gI1, gO1, gI2, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpSuUSvconjSuconjUSv(int gI1, int gO1, int gI2, int gO2) const
        {
            return get_BEptr()->CpSuUSvconjSuconjUSv(gI1, gO1, gI2, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpSvconjUSvVZ(int gI2, int gO2) const
        {
            return get_BEptr()->CpSvconjUSvVZ(gI2, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpSeconjUSvconjVWm(int gI2, int gO2) const
        {
            return get_BEptr()->CpSeconjUSvconjVWm(gI2, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUSuconjUSuVZVZ(int gO1, int gO2) const
        {
            return get_BEptr()->CpUSuconjUSuVZVZ(gO1, gO2);
        }
        
        inline double CMSSM_mass_eigenstates::CpUSuconjUSuconjVWmVWm(int gO1, int gO2) const
        {
            return get_BEptr()->CpUSuconjUSuconjVWmVWm(gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpAhAhUSuconjUSu(int gI1, int gI2, int gO1, int gO2) const
        {
            return get_BEptr()->CpAhAhUSuconjUSu(gI1, gI2, gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CphhhhUSuconjUSu(int gI1, int gI2, int gO1, int gO2) const
        {
            return get_BEptr()->CphhhhUSuconjUSu(gI1, gI2, gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpHpmUSuconjHpmconjUSu(int gI1, int gO1, int gI2, int gO2) const
        {
            return get_BEptr()->CpHpmUSuconjHpmconjUSu(gI1, gO1, gI2, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarChaFdconjUSuPR(int gI1, int gI2, int gO2) const
        {
            return get_BEptr()->CpbarChaFdconjUSuPR(gI1, gI2, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarChaFdconjUSuPL(int gI1, int gI2, int gO1) const
        {
            return get_BEptr()->CpbarChaFdconjUSuPL(gI1, gI2, gO1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpSdconjHpmconjUSu(int gI2, int gI1, int gO2) const
        {
            return get_BEptr()->CpSdconjHpmconjUSu(gI2, gI1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUSuSvconjUSuconjSv(int gO1, int gI1, int gO2, int gI2) const
        {
            return get_BEptr()->CpUSuSvconjUSuconjSv(gO1, gI1, gO2, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpChiFuconjUSuPR(int gI2, int gI1, int gO2) const
        {
            return get_BEptr()->CpChiFuconjUSuPR(gI2, gI1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpChiFuconjUSuPL(int gI2, int gI1, int gO1) const
        {
            return get_BEptr()->CpChiFuconjUSuPL(gI2, gI1, gO1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpSeUSuconjSeconjUSu(int gI1, int gO1, int gI2, int gO2) const
        {
            return get_BEptr()->CpSeUSuconjSeconjUSu(gI1, gO1, gI2, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUSuconjUSuconjSdSd(int gO1, int gO2, int gI1, int gI2) const
        {
            return get_BEptr()->CpUSuconjUSuconjSdSd(gO1, gO2, gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUSuconjUSuconjSuSu(int gO1, int gO2, int gI1, int gI2) const
        {
            return get_BEptr()->CpUSuconjUSuconjSuSu(gO1, gO2, gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpAhSuconjUSu(int gI2, int gI1, int gO2) const
        {
            return get_BEptr()->CpAhSuconjUSu(gI2, gI1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CphhSuconjUSu(int gI2, int gI1, int gO2) const
        {
            return get_BEptr()->CphhSuconjUSu(gI2, gI1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpGluFuconjUSuPR(int gI2, int gO2) const
        {
            return get_BEptr()->CpGluFuconjUSuPR(gI2, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpGluFuconjUSuPL(int gI2, int gO1) const
        {
            return get_BEptr()->CpGluFuconjUSuPL(gI2, gO1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpSdconjUSuconjVWm(int gI2, int gO2) const
        {
            return get_BEptr()->CpSdconjUSuconjVWm(gI2, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpSuconjUSuVG(int gI2, int gO2) const
        {
            return get_BEptr()->CpSuconjUSuVG(gI2, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpSuconjUSuVP(int gI2, int gO2) const
        {
            return get_BEptr()->CpSuconjUSuVP(gI2, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpSuconjUSuVZ(int gI2, int gO2) const
        {
            return get_BEptr()->CpSuconjUSuVZ(gI2, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUSeconjUSeVZVZ(int gO1, int gO2) const
        {
            return get_BEptr()->CpUSeconjUSeVZVZ(gO1, gO2);
        }
        
        inline double CMSSM_mass_eigenstates::CpUSeconjUSeconjVWmVWm(int gO1, int gO2) const
        {
            return get_BEptr()->CpUSeconjUSeconjVWmVWm(gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpAhAhUSeconjUSe(int gI1, int gI2, int gO1, int gO2) const
        {
            return get_BEptr()->CpAhAhUSeconjUSe(gI1, gI2, gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CphhhhUSeconjUSe(int gI1, int gI2, int gO1, int gO2) const
        {
            return get_BEptr()->CphhhhUSeconjUSe(gI1, gI2, gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpHpmUSeconjHpmconjUSe(int gI1, int gO1, int gI2, int gO2) const
        {
            return get_BEptr()->CpHpmUSeconjHpmconjUSe(gI1, gO1, gI2, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUSeSvconjUSeconjSv(int gO1, int gI1, int gO2, int gI2) const
        {
            return get_BEptr()->CpUSeSvconjUSeconjSv(gO1, gI1, gO2, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpHpmSvconjUSe(int gI2, int gI1, int gO2) const
        {
            return get_BEptr()->CpHpmSvconjUSe(gI2, gI1, gO2);
        }
        
        inline double CMSSM_mass_eigenstates::CpChaFvconjUSePR(int arg_1, int arg_2, int arg_3) const
        {
            return get_BEptr()->CpChaFvconjUSePR(arg_1, arg_2, arg_3);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpChaFvconjUSePL(int gI2, int gI1, int gO1) const
        {
            return get_BEptr()->CpChaFvconjUSePL(gI2, gI1, gO1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpChiFeconjUSePR(int gI2, int gI1, int gO2) const
        {
            return get_BEptr()->CpChiFeconjUSePR(gI2, gI1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpChiFeconjUSePL(int gI2, int gI1, int gO1) const
        {
            return get_BEptr()->CpChiFeconjUSePL(gI2, gI1, gO1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpSdUSeconjSdconjUSe(int gI1, int gO1, int gI2, int gO2) const
        {
            return get_BEptr()->CpSdUSeconjSdconjUSe(gI1, gO1, gI2, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpSeUSeconjSeconjUSe(int gI1, int gO1, int gI2, int gO2) const
        {
            return get_BEptr()->CpSeUSeconjSeconjUSe(gI1, gO1, gI2, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUSeSuconjUSeconjSu(int gO1, int gI1, int gO2, int gI2) const
        {
            return get_BEptr()->CpUSeSuconjUSeconjSu(gO1, gI1, gO2, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpAhSeconjUSe(int gI2, int gI1, int gO2) const
        {
            return get_BEptr()->CpAhSeconjUSe(gI2, gI1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CphhSeconjUSe(int gI2, int gI1, int gO2) const
        {
            return get_BEptr()->CphhSeconjUSe(gI2, gI1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpSvconjUSeVWm(int gI2, int gO2) const
        {
            return get_BEptr()->CpSvconjUSeVWm(gI2, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpSeconjUSeVP(int gI2, int gO2) const
        {
            return get_BEptr()->CpSeconjUSeVP(gI2, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpSeconjUSeVZ(int gI2, int gO2) const
        {
            return get_BEptr()->CpSeconjUSeVZ(gI2, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbargWmgWmUhh(int gO1) const
        {
            return get_BEptr()->CpbargWmgWmUhh(gO1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbargWmCgWmCUhh(int gO1) const
        {
            return get_BEptr()->CpbargWmCgWmCUhh(gO1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbargZgZUhh(int gO1) const
        {
            return get_BEptr()->CpbargZgZUhh(gO1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUhhVZVZ(int gO2) const
        {
            return get_BEptr()->CpUhhVZVZ(gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUhhconjVWmVWm(int gO2) const
        {
            return get_BEptr()->CpUhhconjVWmVWm(gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUhhUhhVZVZ(int gO1, int gO2) const
        {
            return get_BEptr()->CpUhhUhhVZVZ(gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUhhUhhconjVWmVWm(int gO1, int gO2) const
        {
            return get_BEptr()->CpUhhUhhconjVWmVWm(gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpAhAhUhhUhh(int gI1, int gI2, int gO1, int gO2) const
        {
            return get_BEptr()->CpAhAhUhhUhh(gI1, gI2, gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CphhhhUhhUhh(int gI1, int gI2, int gO1, int gO2) const
        {
            return get_BEptr()->CphhhhUhhUhh(gI1, gI2, gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUhhUhhHpmconjHpm(int gO1, int gO2, int gI1, int gI2) const
        {
            return get_BEptr()->CpUhhUhhHpmconjHpm(gO1, gO2, gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpAhAhUhh(int gI1, int gI2, int gO2) const
        {
            return get_BEptr()->CpAhAhUhh(gI1, gI2, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CphhhhUhh(int gI1, int gI2, int gO2) const
        {
            return get_BEptr()->CphhhhUhh(gI1, gI2, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUhhHpmconjHpm(int gO2, int gI2, int gI1) const
        {
            return get_BEptr()->CpUhhHpmconjHpm(gO2, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarChaChaUhhPR(int gI1, int gI2, int gO2) const
        {
            return get_BEptr()->CpbarChaChaUhhPR(gI1, gI2, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarChaChaUhhPL(int gI1, int gI2, int gO1) const
        {
            return get_BEptr()->CpbarChaChaUhhPL(gI1, gI2, gO1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUhhUhhSvconjSv(int gO1, int gO2, int gI1, int gI2) const
        {
            return get_BEptr()->CpUhhUhhSvconjSv(gO1, gO2, gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUhhSvconjSv(int gO2, int gI2, int gI1) const
        {
            return get_BEptr()->CpUhhSvconjSv(gO2, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFdFdUhhPR(int gI1, int gI2, int gO2) const
        {
            return get_BEptr()->CpbarFdFdUhhPR(gI1, gI2, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFdFdUhhPL(int gI1, int gI2, int gO1) const
        {
            return get_BEptr()->CpbarFdFdUhhPL(gI1, gI2, gO1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFeFeUhhPR(int gI1, int gI2, int gO2) const
        {
            return get_BEptr()->CpbarFeFeUhhPR(gI1, gI2, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFeFeUhhPL(int gI1, int gI2, int gO1) const
        {
            return get_BEptr()->CpbarFeFeUhhPL(gI1, gI2, gO1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFuFuUhhPR(int gI1, int gI2, int gO2) const
        {
            return get_BEptr()->CpbarFuFuUhhPR(gI1, gI2, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFuFuUhhPL(int gI1, int gI2, int gO1) const
        {
            return get_BEptr()->CpbarFuFuUhhPL(gI1, gI2, gO1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpChiChiUhhPR(int gI1, int gI2, int gO2) const
        {
            return get_BEptr()->CpChiChiUhhPR(gI1, gI2, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpChiChiUhhPL(int gI1, int gI2, int gO1) const
        {
            return get_BEptr()->CpChiChiUhhPL(gI1, gI2, gO1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUhhUhhSdconjSd(int gO1, int gO2, int gI1, int gI2) const
        {
            return get_BEptr()->CpUhhUhhSdconjSd(gO1, gO2, gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUhhUhhSeconjSe(int gO1, int gO2, int gI1, int gI2) const
        {
            return get_BEptr()->CpUhhUhhSeconjSe(gO1, gO2, gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUhhUhhSuconjSu(int gO1, int gO2, int gI1, int gI2) const
        {
            return get_BEptr()->CpUhhUhhSuconjSu(gO1, gO2, gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUhhSdconjSd(int gO2, int gI2, int gI1) const
        {
            return get_BEptr()->CpUhhSdconjSd(gO2, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUhhSeconjSe(int gO2, int gI2, int gI1) const
        {
            return get_BEptr()->CpUhhSeconjSe(gO2, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUhhSuconjSu(int gO2, int gI2, int gI1) const
        {
            return get_BEptr()->CpUhhSuconjSu(gO2, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpAhUhhVZ(int gI2, int gO2) const
        {
            return get_BEptr()->CpAhUhhVZ(gI2, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUhhHpmconjVWm(int gO2, int gI2) const
        {
            return get_BEptr()->CpUhhHpmconjVWm(gO2, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbargWmgWmUAh(int gO1) const
        {
            return get_BEptr()->CpbargWmgWmUAh(gO1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbargWmCgWmCUAh(int gO1) const
        {
            return get_BEptr()->CpbargWmCgWmCUAh(gO1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUAhUAhVZVZ(int gO1, int gO2) const
        {
            return get_BEptr()->CpUAhUAhVZVZ(gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUAhUAhconjVWmVWm(int gO1, int gO2) const
        {
            return get_BEptr()->CpUAhUAhconjVWmVWm(gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpAhAhUAhUAh(int gI1, int gI2, int gO1, int gO2) const
        {
            return get_BEptr()->CpAhAhUAhUAh(gI1, gI2, gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUAhUAhhhhh(int gO1, int gO2, int gI1, int gI2) const
        {
            return get_BEptr()->CpUAhUAhhhhh(gO1, gO2, gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUAhUAhHpmconjHpm(int gO1, int gO2, int gI1, int gI2) const
        {
            return get_BEptr()->CpUAhUAhHpmconjHpm(gO1, gO2, gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpAhUAhhh(int gI2, int gO2, int gI1) const
        {
            return get_BEptr()->CpAhUAhhh(gI2, gO2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUAhHpmconjHpm(int gO2, int gI2, int gI1) const
        {
            return get_BEptr()->CpUAhHpmconjHpm(gO2, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarChaChaUAhPR(int gI1, int gI2, int gO2) const
        {
            return get_BEptr()->CpbarChaChaUAhPR(gI1, gI2, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarChaChaUAhPL(int gI1, int gI2, int gO1) const
        {
            return get_BEptr()->CpbarChaChaUAhPL(gI1, gI2, gO1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUAhUAhSvconjSv(int gO1, int gO2, int gI1, int gI2) const
        {
            return get_BEptr()->CpUAhUAhSvconjSv(gO1, gO2, gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFdFdUAhPR(int gI1, int gI2, int gO2) const
        {
            return get_BEptr()->CpbarFdFdUAhPR(gI1, gI2, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFdFdUAhPL(int gI1, int gI2, int gO1) const
        {
            return get_BEptr()->CpbarFdFdUAhPL(gI1, gI2, gO1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFeFeUAhPR(int gI1, int gI2, int gO2) const
        {
            return get_BEptr()->CpbarFeFeUAhPR(gI1, gI2, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFeFeUAhPL(int gI1, int gI2, int gO1) const
        {
            return get_BEptr()->CpbarFeFeUAhPL(gI1, gI2, gO1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFuFuUAhPR(int gI1, int gI2, int gO2) const
        {
            return get_BEptr()->CpbarFuFuUAhPR(gI1, gI2, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFuFuUAhPL(int gI1, int gI2, int gO1) const
        {
            return get_BEptr()->CpbarFuFuUAhPL(gI1, gI2, gO1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpChiChiUAhPR(int gI1, int gI2, int gO2) const
        {
            return get_BEptr()->CpChiChiUAhPR(gI1, gI2, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpChiChiUAhPL(int gI1, int gI2, int gO1) const
        {
            return get_BEptr()->CpChiChiUAhPL(gI1, gI2, gO1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUAhUAhSdconjSd(int gO1, int gO2, int gI1, int gI2) const
        {
            return get_BEptr()->CpUAhUAhSdconjSd(gO1, gO2, gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUAhUAhSeconjSe(int gO1, int gO2, int gI1, int gI2) const
        {
            return get_BEptr()->CpUAhUAhSeconjSe(gO1, gO2, gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUAhUAhSuconjSu(int gO1, int gO2, int gI1, int gI2) const
        {
            return get_BEptr()->CpUAhUAhSuconjSu(gO1, gO2, gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUAhSdconjSd(int gO2, int gI2, int gI1) const
        {
            return get_BEptr()->CpUAhSdconjSd(gO2, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUAhSeconjSe(int gO2, int gI2, int gI1) const
        {
            return get_BEptr()->CpUAhSeconjSe(gO2, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUAhSuconjSu(int gO2, int gI2, int gI1) const
        {
            return get_BEptr()->CpUAhSuconjSu(gO2, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUAhhhVZ(int gO2, int gI2) const
        {
            return get_BEptr()->CpUAhhhVZ(gO2, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUAhHpmconjVWm(int gO2, int gI2) const
        {
            return get_BEptr()->CpUAhHpmconjVWm(gO2, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbargWmgZUHpm(int gO2) const
        {
            return get_BEptr()->CpbargWmgZUHpm(gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbargZgWmconjUHpm(int gO1) const
        {
            return get_BEptr()->CpbargZgWmconjUHpm(gO1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbargWmCgZconjUHpm(int gO1) const
        {
            return get_BEptr()->CpbargWmCgZconjUHpm(gO1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbargZgWmCUHpm(int gO2) const
        {
            return get_BEptr()->CpbargZgWmCUHpm(gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpconjUHpmVPVWm(int gO2) const
        {
            return get_BEptr()->CpconjUHpmVPVWm(gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpconjUHpmVWmVZ(int gO2) const
        {
            return get_BEptr()->CpconjUHpmVWmVZ(gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUHpmconjUHpmVZVZ(int gO1, int gO2) const
        {
            return get_BEptr()->CpUHpmconjUHpmVZVZ(gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUHpmconjUHpmconjVWmVWm(int gO1, int gO2) const
        {
            return get_BEptr()->CpUHpmconjUHpmconjVWmVWm(gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpAhAhUHpmconjUHpm(int gI1, int gI2, int gO1, int gO2) const
        {
            return get_BEptr()->CpAhAhUHpmconjUHpm(gI1, gI2, gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CphhhhUHpmconjUHpm(int gI1, int gI2, int gO1, int gO2) const
        {
            return get_BEptr()->CphhhhUHpmconjUHpm(gI1, gI2, gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpHpmUHpmconjHpmconjUHpm(int gI1, int gO1, int gI2, int gO2) const
        {
            return get_BEptr()->CpHpmUHpmconjHpmconjUHpm(gI1, gO1, gI2, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpAhHpmconjUHpm(int gI2, int gI1, int gO2) const
        {
            return get_BEptr()->CpAhHpmconjUHpm(gI2, gI1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CphhHpmconjUHpm(int gI2, int gI1, int gO2) const
        {
            return get_BEptr()->CphhHpmconjUHpm(gI2, gI1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUHpmSvconjUHpmconjSv(int gO1, int gI1, int gO2, int gI2) const
        {
            return get_BEptr()->CpUHpmSvconjUHpmconjSv(gO1, gI1, gO2, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFuFdconjUHpmPR(int gI1, int gI2, int gO2) const
        {
            return get_BEptr()->CpbarFuFdconjUHpmPR(gI1, gI2, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFuFdconjUHpmPL(int gI1, int gI2, int gO1) const
        {
            return get_BEptr()->CpbarFuFdconjUHpmPL(gI1, gI2, gO1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFvFeconjUHpmPR(int gI1, int gI2, int gO2) const
        {
            return get_BEptr()->CpbarFvFeconjUHpmPR(gI1, gI2, gO2);
        }
        
        inline double CMSSM_mass_eigenstates::CpbarFvFeconjUHpmPL(int arg_1, int arg_2, int arg_3) const
        {
            return get_BEptr()->CpbarFvFeconjUHpmPL(arg_1, arg_2, arg_3);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpSeconjUHpmconjSv(int gI2, int gO2, int gI1) const
        {
            return get_BEptr()->CpSeconjUHpmconjSv(gI2, gO2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpChiChaconjUHpmPR(int gI1, int gI2, int gO2) const
        {
            return get_BEptr()->CpChiChaconjUHpmPR(gI1, gI2, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpChiChaconjUHpmPL(int gI1, int gI2, int gO1) const
        {
            return get_BEptr()->CpChiChaconjUHpmPL(gI1, gI2, gO1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUHpmSdconjUHpmconjSd(int gO1, int gI1, int gO2, int gI2) const
        {
            return get_BEptr()->CpUHpmSdconjUHpmconjSd(gO1, gI1, gO2, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUHpmSeconjUHpmconjSe(int gO1, int gI1, int gO2, int gI2) const
        {
            return get_BEptr()->CpUHpmSeconjUHpmconjSe(gO1, gI1, gO2, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUHpmSuconjUHpmconjSu(int gO1, int gI1, int gO2, int gI2) const
        {
            return get_BEptr()->CpUHpmSuconjUHpmconjSu(gO1, gI1, gO2, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpSdconjUHpmconjSu(int gI2, int gO2, int gI1) const
        {
            return get_BEptr()->CpSdconjUHpmconjSu(gI2, gO2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpAhconjUHpmVWm(int gI2, int gO2) const
        {
            return get_BEptr()->CpAhconjUHpmVWm(gI2, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CphhconjUHpmVWm(int gI2, int gO2) const
        {
            return get_BEptr()->CphhconjUHpmVWm(gI2, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpHpmconjUHpmVP(int gI2, int gO2) const
        {
            return get_BEptr()->CpHpmconjUHpmVP(gI2, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpHpmconjUHpmVZ(int gI2, int gO2) const
        {
            return get_BEptr()->CpHpmconjUHpmVZ(gI2, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpVGVGVG() const
        {
            return get_BEptr()->CpVGVGVG();
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbargGgGVG() const
        {
            return get_BEptr()->CpbargGgGVG();
        }
        
        inline double CMSSM_mass_eigenstates::CpbarFdFdVGPL(int gI1, int gI2) const
        {
            return get_BEptr()->CpbarFdFdVGPL(gI1, gI2);
        }
        
        inline double CMSSM_mass_eigenstates::CpbarFdFdVGPR(int gI1, int gI2) const
        {
            return get_BEptr()->CpbarFdFdVGPR(gI1, gI2);
        }
        
        inline double CMSSM_mass_eigenstates::CpbarFuFuVGPL(int gI1, int gI2) const
        {
            return get_BEptr()->CpbarFuFuVGPL(gI1, gI2);
        }
        
        inline double CMSSM_mass_eigenstates::CpbarFuFuVGPR(int gI1, int gI2) const
        {
            return get_BEptr()->CpbarFuFuVGPR(gI1, gI2);
        }
        
        inline double CMSSM_mass_eigenstates::CpSdconjSdVGVG(int gI1, int gI2) const
        {
            return get_BEptr()->CpSdconjSdVGVG(gI1, gI2);
        }
        
        inline double CMSSM_mass_eigenstates::CpSuconjSuVGVG(int gI1, int gI2) const
        {
            return get_BEptr()->CpSuconjSuVGVG(gI1, gI2);
        }
        
        inline double CMSSM_mass_eigenstates::CpSdconjSdVG(int gI2, int gI1) const
        {
            return get_BEptr()->CpSdconjSdVG(gI2, gI1);
        }
        
        inline double CMSSM_mass_eigenstates::CpSuconjSuVG(int gI2, int gI1) const
        {
            return get_BEptr()->CpSuconjSuVG(gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpGluGluVGPL() const
        {
            return get_BEptr()->CpGluGluVGPL();
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpGluGluVGPR() const
        {
            return get_BEptr()->CpGluGluVGPR();
        }
        
        inline double CMSSM_mass_eigenstates::CpVGVGVGVG1() const
        {
            return get_BEptr()->CpVGVGVGVG1();
        }
        
        inline double CMSSM_mass_eigenstates::CpVGVGVGVG2() const
        {
            return get_BEptr()->CpVGVGVGVG2();
        }
        
        inline double CMSSM_mass_eigenstates::CpVGVGVGVG3() const
        {
            return get_BEptr()->CpVGVGVGVG3();
        }
        
        inline double CMSSM_mass_eigenstates::CpbargWmgWmVP() const
        {
            return get_BEptr()->CpbargWmgWmVP();
        }
        
        inline double CMSSM_mass_eigenstates::CpbargWmCgWmCVP() const
        {
            return get_BEptr()->CpbargWmCgWmCVP();
        }
        
        inline double CMSSM_mass_eigenstates::CpconjVWmVPVWm() const
        {
            return get_BEptr()->CpconjVWmVPVWm();
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpHpmconjHpmVPVP(int gI1, int gI2) const
        {
            return get_BEptr()->CpHpmconjHpmVPVP(gI1, gI2);
        }
        
        inline double CMSSM_mass_eigenstates::CpHpmconjHpmVP(int gI2, int gI1) const
        {
            return get_BEptr()->CpHpmconjHpmVP(gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarChaChaVPPL(int gI1, int gI2) const
        {
            return get_BEptr()->CpbarChaChaVPPL(gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarChaChaVPPR(int gI1, int gI2) const
        {
            return get_BEptr()->CpbarChaChaVPPR(gI1, gI2);
        }
        
        inline double CMSSM_mass_eigenstates::CpbarFdFdVPPL(int gI1, int gI2) const
        {
            return get_BEptr()->CpbarFdFdVPPL(gI1, gI2);
        }
        
        inline double CMSSM_mass_eigenstates::CpbarFdFdVPPR(int gI1, int gI2) const
        {
            return get_BEptr()->CpbarFdFdVPPR(gI1, gI2);
        }
        
        inline double CMSSM_mass_eigenstates::CpbarFeFeVPPL(int gI1, int gI2) const
        {
            return get_BEptr()->CpbarFeFeVPPL(gI1, gI2);
        }
        
        inline double CMSSM_mass_eigenstates::CpbarFeFeVPPR(int gI1, int gI2) const
        {
            return get_BEptr()->CpbarFeFeVPPR(gI1, gI2);
        }
        
        inline double CMSSM_mass_eigenstates::CpbarFuFuVPPL(int gI1, int gI2) const
        {
            return get_BEptr()->CpbarFuFuVPPL(gI1, gI2);
        }
        
        inline double CMSSM_mass_eigenstates::CpbarFuFuVPPR(int gI1, int gI2) const
        {
            return get_BEptr()->CpbarFuFuVPPR(gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpSdconjSdVPVP(int gI1, int gI2) const
        {
            return get_BEptr()->CpSdconjSdVPVP(gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpSeconjSeVPVP(int gI1, int gI2) const
        {
            return get_BEptr()->CpSeconjSeVPVP(gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpSuconjSuVPVP(int gI1, int gI2) const
        {
            return get_BEptr()->CpSuconjSuVPVP(gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpSdconjSdVP(int gI2, int gI1) const
        {
            return get_BEptr()->CpSdconjSdVP(gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpSeconjSeVP(int gI2, int gI1) const
        {
            return get_BEptr()->CpSeconjSeVP(gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpSuconjSuVP(int gI2, int gI1) const
        {
            return get_BEptr()->CpSuconjSuVP(gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpHpmconjVWmVP(int gI2) const
        {
            return get_BEptr()->CpHpmconjVWmVP(gI2);
        }
        
        inline double CMSSM_mass_eigenstates::CpconjVWmVPVPVWm1() const
        {
            return get_BEptr()->CpconjVWmVPVPVWm1();
        }
        
        inline double CMSSM_mass_eigenstates::CpconjVWmVPVPVWm2() const
        {
            return get_BEptr()->CpconjVWmVPVPVWm2();
        }
        
        inline double CMSSM_mass_eigenstates::CpconjVWmVPVPVWm3() const
        {
            return get_BEptr()->CpconjVWmVPVPVWm3();
        }
        
        inline double CMSSM_mass_eigenstates::CpbargWmgWmVZ() const
        {
            return get_BEptr()->CpbargWmgWmVZ();
        }
        
        inline double CMSSM_mass_eigenstates::CpbargWmCgWmCVZ() const
        {
            return get_BEptr()->CpbargWmCgWmCVZ();
        }
        
        inline double CMSSM_mass_eigenstates::CpconjVWmVWmVZ() const
        {
            return get_BEptr()->CpconjVWmVWmVZ();
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpAhAhVZVZ(int gI1, int gI2) const
        {
            return get_BEptr()->CpAhAhVZVZ(gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CphhhhVZVZ(int gI1, int gI2) const
        {
            return get_BEptr()->CphhhhVZVZ(gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpHpmconjHpmVZVZ(int gI1, int gI2) const
        {
            return get_BEptr()->CpHpmconjHpmVZVZ(gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpAhhhVZ(int gI2, int gI1) const
        {
            return get_BEptr()->CpAhhhVZ(gI2, gI1);
        }
        
        inline double CMSSM_mass_eigenstates::CpHpmconjHpmVZ(int gI2, int gI1) const
        {
            return get_BEptr()->CpHpmconjHpmVZ(gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarChaChaVZPL(int gI1, int gI2) const
        {
            return get_BEptr()->CpbarChaChaVZPL(gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarChaChaVZPR(int gI1, int gI2) const
        {
            return get_BEptr()->CpbarChaChaVZPR(gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpSvconjSvVZVZ(int gI1, int gI2) const
        {
            return get_BEptr()->CpSvconjSvVZVZ(gI1, gI2);
        }
        
        inline double CMSSM_mass_eigenstates::CpSvconjSvVZ(int gI2, int gI1) const
        {
            return get_BEptr()->CpSvconjSvVZ(gI2, gI1);
        }
        
        inline double CMSSM_mass_eigenstates::CpbarFdFdVZPL(int gI1, int gI2) const
        {
            return get_BEptr()->CpbarFdFdVZPL(gI1, gI2);
        }
        
        inline double CMSSM_mass_eigenstates::CpbarFdFdVZPR(int gI1, int gI2) const
        {
            return get_BEptr()->CpbarFdFdVZPR(gI1, gI2);
        }
        
        inline double CMSSM_mass_eigenstates::CpbarFeFeVZPL(int gI1, int gI2) const
        {
            return get_BEptr()->CpbarFeFeVZPL(gI1, gI2);
        }
        
        inline double CMSSM_mass_eigenstates::CpbarFeFeVZPR(int gI1, int gI2) const
        {
            return get_BEptr()->CpbarFeFeVZPR(gI1, gI2);
        }
        
        inline double CMSSM_mass_eigenstates::CpbarFuFuVZPL(int gI1, int gI2) const
        {
            return get_BEptr()->CpbarFuFuVZPL(gI1, gI2);
        }
        
        inline double CMSSM_mass_eigenstates::CpbarFuFuVZPR(int gI1, int gI2) const
        {
            return get_BEptr()->CpbarFuFuVZPR(gI1, gI2);
        }
        
        inline double CMSSM_mass_eigenstates::CpbarFvFvVZPL(int gI1, int gI2) const
        {
            return get_BEptr()->CpbarFvFvVZPL(gI1, gI2);
        }
        
        inline double CMSSM_mass_eigenstates::CpbarFvFvVZPR(int arg_1, int arg_2) const
        {
            return get_BEptr()->CpbarFvFvVZPR(arg_1, arg_2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpChiChiVZPL(int gI1, int gI2) const
        {
            return get_BEptr()->CpChiChiVZPL(gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpChiChiVZPR(int gI1, int gI2) const
        {
            return get_BEptr()->CpChiChiVZPR(gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpSdconjSdVZVZ(int gI1, int gI2) const
        {
            return get_BEptr()->CpSdconjSdVZVZ(gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpSeconjSeVZVZ(int gI1, int gI2) const
        {
            return get_BEptr()->CpSeconjSeVZVZ(gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpSuconjSuVZVZ(int gI1, int gI2) const
        {
            return get_BEptr()->CpSuconjSuVZVZ(gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpSdconjSdVZ(int gI2, int gI1) const
        {
            return get_BEptr()->CpSdconjSdVZ(gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpSeconjSeVZ(int gI2, int gI1) const
        {
            return get_BEptr()->CpSeconjSeVZ(gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpSuconjSuVZ(int gI2, int gI1) const
        {
            return get_BEptr()->CpSuconjSuVZ(gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CphhVZVZ(int gI2) const
        {
            return get_BEptr()->CphhVZVZ(gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpHpmconjVWmVZ(int gI2) const
        {
            return get_BEptr()->CpHpmconjVWmVZ(gI2);
        }
        
        inline double CMSSM_mass_eigenstates::CpconjVWmVWmVZVZ1() const
        {
            return get_BEptr()->CpconjVWmVWmVZVZ1();
        }
        
        inline double CMSSM_mass_eigenstates::CpconjVWmVWmVZVZ2() const
        {
            return get_BEptr()->CpconjVWmVWmVZVZ2();
        }
        
        inline double CMSSM_mass_eigenstates::CpconjVWmVWmVZVZ3() const
        {
            return get_BEptr()->CpconjVWmVWmVZVZ3();
        }
        
        inline double CMSSM_mass_eigenstates::CpbargPgWmconjVWm() const
        {
            return get_BEptr()->CpbargPgWmconjVWm();
        }
        
        inline double CMSSM_mass_eigenstates::CpbargWmCgPconjVWm() const
        {
            return get_BEptr()->CpbargWmCgPconjVWm();
        }
        
        inline double CMSSM_mass_eigenstates::CpbargWmCgZconjVWm() const
        {
            return get_BEptr()->CpbargWmCgZconjVWm();
        }
        
        inline double CMSSM_mass_eigenstates::CpbargZgWmconjVWm() const
        {
            return get_BEptr()->CpbargZgWmconjVWm();
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpAhAhconjVWmVWm(int gI1, int gI2) const
        {
            return get_BEptr()->CpAhAhconjVWmVWm(gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CphhhhconjVWmVWm(int gI1, int gI2) const
        {
            return get_BEptr()->CphhhhconjVWmVWm(gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpHpmconjHpmconjVWmVWm(int gI1, int gI2) const
        {
            return get_BEptr()->CpHpmconjHpmconjVWmVWm(gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpAhHpmconjVWm(int gI2, int gI1) const
        {
            return get_BEptr()->CpAhHpmconjVWm(gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CphhHpmconjVWm(int gI2, int gI1) const
        {
            return get_BEptr()->CphhHpmconjVWm(gI2, gI1);
        }
        
        inline double CMSSM_mass_eigenstates::CpSvconjSvconjVWmVWm(int gI1, int gI2) const
        {
            return get_BEptr()->CpSvconjSvconjVWmVWm(gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFuFdconjVWmPL(int gI1, int gI2) const
        {
            return get_BEptr()->CpbarFuFdconjVWmPL(gI1, gI2);
        }
        
        inline double CMSSM_mass_eigenstates::CpbarFuFdconjVWmPR(int arg_1, int arg_2) const
        {
            return get_BEptr()->CpbarFuFdconjVWmPR(arg_1, arg_2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFvFeconjVWmPL(int gI1, int gI2) const
        {
            return get_BEptr()->CpbarFvFeconjVWmPL(gI1, gI2);
        }
        
        inline double CMSSM_mass_eigenstates::CpbarFvFeconjVWmPR(int arg_1, int arg_2) const
        {
            return get_BEptr()->CpbarFvFeconjVWmPR(arg_1, arg_2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpSeconjSvconjVWm(int gI2, int gI1) const
        {
            return get_BEptr()->CpSeconjSvconjVWm(gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpChiChaconjVWmPL(int gI1, int gI2) const
        {
            return get_BEptr()->CpChiChaconjVWmPL(gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpChiChaconjVWmPR(int gI1, int gI2) const
        {
            return get_BEptr()->CpChiChaconjVWmPR(gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpSdconjSdconjVWmVWm(int gI1, int gI2) const
        {
            return get_BEptr()->CpSdconjSdconjVWmVWm(gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpSeconjSeconjVWmVWm(int gI1, int gI2) const
        {
            return get_BEptr()->CpSeconjSeconjVWmVWm(gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpSuconjSuconjVWmVWm(int gI1, int gI2) const
        {
            return get_BEptr()->CpSuconjSuconjVWmVWm(gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpSdconjSuconjVWm(int gI2, int gI1) const
        {
            return get_BEptr()->CpSdconjSuconjVWm(gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CphhconjVWmVWm(int gI2) const
        {
            return get_BEptr()->CphhconjVWmVWm(gI2);
        }
        
        inline double CMSSM_mass_eigenstates::CpconjVWmconjVWmVWmVWm1() const
        {
            return get_BEptr()->CpconjVWmconjVWmVWmVWm1();
        }
        
        inline double CMSSM_mass_eigenstates::CpconjVWmconjVWmVWmVWm2() const
        {
            return get_BEptr()->CpconjVWmconjVWmVWmVWm2();
        }
        
        inline double CMSSM_mass_eigenstates::CpconjVWmconjVWmVWmVWm3() const
        {
            return get_BEptr()->CpconjVWmconjVWmVWmVWm3();
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarChaUChiHpmPL(int gI1, int gO2, int gI2) const
        {
            return get_BEptr()->CpbarChaUChiHpmPL(gI1, gO2, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarChaUChiHpmPR(int gI1, int gO1, int gI2) const
        {
            return get_BEptr()->CpbarChaUChiHpmPR(gI1, gO1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUChiChaconjHpmPL(int gO2, int gI2, int gI1) const
        {
            return get_BEptr()->CpUChiChaconjHpmPL(gO2, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUChiChaconjHpmPR(int gO1, int gI2, int gI1) const
        {
            return get_BEptr()->CpUChiChaconjHpmPR(gO1, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpChiUChihhPL(int gI2, int gO2, int gI1) const
        {
            return get_BEptr()->CpChiUChihhPL(gI2, gO2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpChiUChihhPR(int gI2, int gO1, int gI1) const
        {
            return get_BEptr()->CpChiUChihhPR(gI2, gO1, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarChaUChiVWmPL(int gI1, int gO2) const
        {
            return get_BEptr()->CpbarChaUChiVWmPL(gI1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarChaUChiVWmPR(int gI1, int gO1) const
        {
            return get_BEptr()->CpbarChaUChiVWmPR(gI1, gO1);
        }
        
        inline double CMSSM_mass_eigenstates::CpbarFvUChiSvPL(int arg_1, int arg_2, int arg_3) const
        {
            return get_BEptr()->CpbarFvUChiSvPL(arg_1, arg_2, arg_3);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFvUChiSvPR(int gI1, int gO1, int gI2) const
        {
            return get_BEptr()->CpbarFvUChiSvPR(gI1, gO1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUChiFvconjSvPL(int gO2, int gI2, int gI1) const
        {
            return get_BEptr()->CpUChiFvconjSvPL(gO2, gI2, gI1);
        }
        
        inline double CMSSM_mass_eigenstates::CpUChiFvconjSvPR(int arg_1, int arg_2, int arg_3) const
        {
            return get_BEptr()->CpUChiFvconjSvPR(arg_1, arg_2, arg_3);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFdUChiSdPL(int gI1, int gO2, int gI2) const
        {
            return get_BEptr()->CpbarFdUChiSdPL(gI1, gO2, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFdUChiSdPR(int gI1, int gO1, int gI2) const
        {
            return get_BEptr()->CpbarFdUChiSdPR(gI1, gO1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFeUChiSePL(int gI1, int gO2, int gI2) const
        {
            return get_BEptr()->CpbarFeUChiSePL(gI1, gO2, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFeUChiSePR(int gI1, int gO1, int gI2) const
        {
            return get_BEptr()->CpbarFeUChiSePR(gI1, gO1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFuUChiSuPL(int gI1, int gO2, int gI2) const
        {
            return get_BEptr()->CpbarFuUChiSuPL(gI1, gO2, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFuUChiSuPR(int gI1, int gO1, int gI2) const
        {
            return get_BEptr()->CpbarFuUChiSuPR(gI1, gO1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpChiUChiAhPL(int gI1, int gO2, int gI2) const
        {
            return get_BEptr()->CpChiUChiAhPL(gI1, gO2, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpChiUChiAhPR(int gI1, int gO1, int gI2) const
        {
            return get_BEptr()->CpChiUChiAhPR(gI1, gO1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUChiFdconjSdPL(int gO2, int gI2, int gI1) const
        {
            return get_BEptr()->CpUChiFdconjSdPL(gO2, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUChiFdconjSdPR(int gO1, int gI2, int gI1) const
        {
            return get_BEptr()->CpUChiFdconjSdPR(gO1, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUChiFeconjSePL(int gO2, int gI2, int gI1) const
        {
            return get_BEptr()->CpUChiFeconjSePL(gO2, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUChiFeconjSePR(int gO1, int gI2, int gI1) const
        {
            return get_BEptr()->CpUChiFeconjSePR(gO1, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUChiFuconjSuPL(int gO2, int gI2, int gI1) const
        {
            return get_BEptr()->CpUChiFuconjSuPL(gO2, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUChiFuconjSuPR(int gO1, int gI2, int gI1) const
        {
            return get_BEptr()->CpUChiFuconjSuPR(gO1, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUChiChaconjVWmPR(int gO2, int gI2) const
        {
            return get_BEptr()->CpUChiChaconjVWmPR(gO2, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpUChiChaconjVWmPL(int gO1, int gI2) const
        {
            return get_BEptr()->CpUChiChaconjVWmPL(gO1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpChiUChiVZPL(int gI2, int gO2) const
        {
            return get_BEptr()->CpChiUChiVZPL(gI2, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpChiUChiVZPR(int gI2, int gO1) const
        {
            return get_BEptr()->CpChiUChiVZPR(gI2, gO1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUChaChaAhPL(int gO2, int gI1, int gI2) const
        {
            return get_BEptr()->CpbarUChaChaAhPL(gO2, gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUChaChaAhPR(int gO1, int gI1, int gI2) const
        {
            return get_BEptr()->CpbarUChaChaAhPR(gO1, gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUChaChahhPL(int gO2, int gI2, int gI1) const
        {
            return get_BEptr()->CpbarUChaChahhPL(gO2, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUChaChahhPR(int gO1, int gI2, int gI1) const
        {
            return get_BEptr()->CpbarUChaChahhPR(gO1, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUChaChiHpmPL(int gO2, int gI2, int gI1) const
        {
            return get_BEptr()->CpbarUChaChiHpmPL(gO2, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUChaChiHpmPR(int gO1, int gI2, int gI1) const
        {
            return get_BEptr()->CpbarUChaChiHpmPR(gO1, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUChaFeconjSvPL(int gO2, int gI2, int gI1) const
        {
            return get_BEptr()->CpbarUChaFeconjSvPL(gO2, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUChaFeconjSvPR(int gO1, int gI2, int gI1) const
        {
            return get_BEptr()->CpbarUChaFeconjSvPR(gO1, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUChabarFuSdPL(int gO2, int gI1, int gI2) const
        {
            return get_BEptr()->CpbarUChabarFuSdPL(gO2, gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUChabarFuSdPR(int gO1, int gI1, int gI2) const
        {
            return get_BEptr()->CpbarUChabarFuSdPR(gO1, gI1, gI2);
        }
        
        inline double CMSSM_mass_eigenstates::CpbarUChabarFvSePL(int arg_1, int arg_2, int arg_3) const
        {
            return get_BEptr()->CpbarUChabarFvSePL(arg_1, arg_2, arg_3);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUChabarFvSePR(int gO1, int gI1, int gI2) const
        {
            return get_BEptr()->CpbarUChabarFvSePR(gO1, gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUChaFdconjSuPL(int gO2, int gI2, int gI1) const
        {
            return get_BEptr()->CpbarUChaFdconjSuPL(gO2, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUChaFdconjSuPR(int gO1, int gI2, int gI1) const
        {
            return get_BEptr()->CpbarUChaFdconjSuPR(gO1, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUChaChaVPPR(int gO2, int gI2) const
        {
            return get_BEptr()->CpbarUChaChaVPPR(gO2, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUChaChaVPPL(int gO1, int gI2) const
        {
            return get_BEptr()->CpbarUChaChaVPPL(gO1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUChaChaVZPR(int gO2, int gI2) const
        {
            return get_BEptr()->CpbarUChaChaVZPR(gO2, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUChaChaVZPL(int gO1, int gI2) const
        {
            return get_BEptr()->CpbarUChaChaVZPL(gO1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUChaChiVWmPR(int gO2, int gI2) const
        {
            return get_BEptr()->CpbarUChaChiVWmPR(gO2, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUChaChiVWmPL(int gO1, int gI2) const
        {
            return get_BEptr()->CpbarUChaChiVWmPL(gO1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUFeFehhPL(int gO2, int gI2, int gI1) const
        {
            return get_BEptr()->CpbarUFeFehhPL(gO2, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUFeFehhPR(int gO1, int gI2, int gI1) const
        {
            return get_BEptr()->CpbarUFeFehhPR(gO1, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUFeFvHpmPL(int gO2, int gI2, int gI1) const
        {
            return get_BEptr()->CpbarUFeFvHpmPL(gO2, gI2, gI1);
        }
        
        inline double CMSSM_mass_eigenstates::CpbarUFeFvHpmPR(int arg_1, int arg_2, int arg_3) const
        {
            return get_BEptr()->CpbarUFeFvHpmPR(arg_1, arg_2, arg_3);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUFeChaSvPL(int gO2, int gI2, int gI1) const
        {
            return get_BEptr()->CpbarUFeChaSvPL(gO2, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUFeChaSvPR(int gO1, int gI2, int gI1) const
        {
            return get_BEptr()->CpbarUFeChaSvPR(gO1, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUFeFeAhPL(int gO2, int gI1, int gI2) const
        {
            return get_BEptr()->CpbarUFeFeAhPL(gO2, gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUFeFeAhPR(int gO1, int gI1, int gI2) const
        {
            return get_BEptr()->CpbarUFeFeAhPR(gO1, gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUFeChiSePL(int gO2, int gI2, int gI1) const
        {
            return get_BEptr()->CpbarUFeChiSePL(gO2, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUFeChiSePR(int gO1, int gI2, int gI1) const
        {
            return get_BEptr()->CpbarUFeChiSePR(gO1, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUFeFeVPPR(int gO2, int gI2) const
        {
            return get_BEptr()->CpbarUFeFeVPPR(gO2, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUFeFeVPPL(int gO1, int gI2) const
        {
            return get_BEptr()->CpbarUFeFeVPPL(gO1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUFeFeVZPR(int gO2, int gI2) const
        {
            return get_BEptr()->CpbarUFeFeVZPR(gO2, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUFeFeVZPL(int gO1, int gI2) const
        {
            return get_BEptr()->CpbarUFeFeVZPL(gO1, gI2);
        }
        
        inline double CMSSM_mass_eigenstates::CpbarUFeFvVWmPR(int arg_1, int arg_2) const
        {
            return get_BEptr()->CpbarUFeFvVWmPR(arg_1, arg_2);
        }
        
        inline double CMSSM_mass_eigenstates::CpbarUFeFvVWmPL(int gO1, int gI2) const
        {
            return get_BEptr()->CpbarUFeFvVWmPL(gO1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUFdFdhhPL(int gO2, int gI2, int gI1) const
        {
            return get_BEptr()->CpbarUFdFdhhPL(gO2, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUFdFdhhPR(int gO1, int gI2, int gI1) const
        {
            return get_BEptr()->CpbarUFdFdhhPR(gO1, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUFdFuHpmPL(int gO2, int gI2, int gI1) const
        {
            return get_BEptr()->CpbarUFdFuHpmPL(gO2, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUFdFuHpmPR(int gO1, int gI2, int gI1) const
        {
            return get_BEptr()->CpbarUFdFuHpmPR(gO1, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUFdFdAhPL(int gO2, int gI1, int gI2) const
        {
            return get_BEptr()->CpbarUFdFdAhPL(gO2, gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUFdFdAhPR(int gO1, int gI1, int gI2) const
        {
            return get_BEptr()->CpbarUFdFdAhPR(gO1, gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUFdChaSuPL(int gO2, int gI2, int gI1) const
        {
            return get_BEptr()->CpbarUFdChaSuPL(gO2, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUFdChaSuPR(int gO1, int gI2, int gI1) const
        {
            return get_BEptr()->CpbarUFdChaSuPR(gO1, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUFdChiSdPL(int gO2, int gI2, int gI1) const
        {
            return get_BEptr()->CpbarUFdChiSdPL(gO2, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUFdChiSdPR(int gO1, int gI2, int gI1) const
        {
            return get_BEptr()->CpbarUFdChiSdPR(gO1, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUFdGluSdPL(int gO2, int gI1) const
        {
            return get_BEptr()->CpbarUFdGluSdPL(gO2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUFdGluSdPR(int gO1, int gI1) const
        {
            return get_BEptr()->CpbarUFdGluSdPR(gO1, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUFdFdVGPR(int gO2, int gI2) const
        {
            return get_BEptr()->CpbarUFdFdVGPR(gO2, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUFdFdVGPL(int gO1, int gI2) const
        {
            return get_BEptr()->CpbarUFdFdVGPL(gO1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUFdFdVPPR(int gO2, int gI2) const
        {
            return get_BEptr()->CpbarUFdFdVPPR(gO2, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUFdFdVPPL(int gO1, int gI2) const
        {
            return get_BEptr()->CpbarUFdFdVPPL(gO1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUFdFdVZPR(int gO2, int gI2) const
        {
            return get_BEptr()->CpbarUFdFdVZPR(gO2, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUFdFdVZPL(int gO1, int gI2) const
        {
            return get_BEptr()->CpbarUFdFdVZPL(gO1, gI2);
        }
        
        inline double CMSSM_mass_eigenstates::CpbarUFdFuVWmPR(int arg_1, int arg_2) const
        {
            return get_BEptr()->CpbarUFdFuVWmPR(arg_1, arg_2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUFdFuVWmPL(int gO1, int gI2) const
        {
            return get_BEptr()->CpbarUFdFuVWmPL(gO1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUFuFdconjHpmPL(int gO2, int gI2, int gI1) const
        {
            return get_BEptr()->CpbarUFuFdconjHpmPL(gO2, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUFuFdconjHpmPR(int gO1, int gI2, int gI1) const
        {
            return get_BEptr()->CpbarUFuFdconjHpmPR(gO1, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUFuFuhhPL(int gO2, int gI2, int gI1) const
        {
            return get_BEptr()->CpbarUFuFuhhPL(gO2, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUFuFuhhPR(int gO1, int gI2, int gI1) const
        {
            return get_BEptr()->CpbarUFuFuhhPR(gO1, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarChabarUFuSdPL(int gI1, int gO2, int gI2) const
        {
            return get_BEptr()->CpbarChabarUFuSdPL(gI1, gO2, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarChabarUFuSdPR(int gI1, int gO1, int gI2) const
        {
            return get_BEptr()->CpbarChabarUFuSdPR(gI1, gO1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUFuFuAhPL(int gO2, int gI1, int gI2) const
        {
            return get_BEptr()->CpbarUFuFuAhPL(gO2, gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUFuFuAhPR(int gO1, int gI1, int gI2) const
        {
            return get_BEptr()->CpbarUFuFuAhPR(gO1, gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUFuChiSuPL(int gO2, int gI2, int gI1) const
        {
            return get_BEptr()->CpbarUFuChiSuPL(gO2, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUFuChiSuPR(int gO1, int gI2, int gI1) const
        {
            return get_BEptr()->CpbarUFuChiSuPR(gO1, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUFuGluSuPL(int gO2, int gI1) const
        {
            return get_BEptr()->CpbarUFuGluSuPL(gO2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUFuGluSuPR(int gO1, int gI1) const
        {
            return get_BEptr()->CpbarUFuGluSuPR(gO1, gI1);
        }
        
        inline double CMSSM_mass_eigenstates::CpbarUFuFdconjVWmPR(int arg_1, int arg_2) const
        {
            return get_BEptr()->CpbarUFuFdconjVWmPR(arg_1, arg_2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUFuFdconjVWmPL(int gO1, int gI2) const
        {
            return get_BEptr()->CpbarUFuFdconjVWmPL(gO1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUFuFuVGPR(int gO2, int gI2) const
        {
            return get_BEptr()->CpbarUFuFuVGPR(gO2, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUFuFuVGPL(int gO1, int gI2) const
        {
            return get_BEptr()->CpbarUFuFuVGPL(gO1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUFuFuVPPR(int gO2, int gI2) const
        {
            return get_BEptr()->CpbarUFuFuVPPR(gO2, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUFuFuVPPL(int gO1, int gI2) const
        {
            return get_BEptr()->CpbarUFuFuVPPL(gO1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUFuFuVZPR(int gO2, int gI2) const
        {
            return get_BEptr()->CpbarUFuFuVZPR(gO2, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarUFuFuVZPL(int gO1, int gI2) const
        {
            return get_BEptr()->CpbarUFuFuVZPL(gO1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFdGluSdPL(int gI1, int gI2) const
        {
            return get_BEptr()->CpbarFdGluSdPL(gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFdGluSdPR(int gI1, int gI2) const
        {
            return get_BEptr()->CpbarFdGluSdPR(gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFuGluSuPL(int gI1, int gI2) const
        {
            return get_BEptr()->CpbarFuGluSuPL(gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFuGluSuPR(int gI1, int gI2) const
        {
            return get_BEptr()->CpbarFuGluSuPR(gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpGluFdconjSdPL(int gI2, int gI1) const
        {
            return get_BEptr()->CpGluFdconjSdPL(gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpGluFdconjSdPR(int gI2, int gI1) const
        {
            return get_BEptr()->CpGluFdconjSdPR(gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpGluFuconjSuPL(int gI2, int gI1) const
        {
            return get_BEptr()->CpGluFuconjSuPL(gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpGluFuconjSuPR(int gI2, int gI1) const
        {
            return get_BEptr()->CpGluFuconjSuPR(gI2, gI1);
        }
        
        inline double CMSSM_mass_eigenstates::CpbarFvFeconjHpmPL(int arg_1, int arg_2, int arg_3) const
        {
            return get_BEptr()->CpbarFvFeconjHpmPL(arg_1, arg_2, arg_3);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFvFeconjHpmPR(int gO1, int gI2, int gI1) const
        {
            return get_BEptr()->CpbarFvFeconjHpmPR(gO1, gI2, gI1);
        }
        
        inline double CMSSM_mass_eigenstates::CpbarChabarFvSePL(int arg_1, int arg_2, int arg_3) const
        {
            return get_BEptr()->CpbarChabarFvSePL(arg_1, arg_2, arg_3);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarChabarFvSePR(int gI1, int gO1, int gI2) const
        {
            return get_BEptr()->CpbarChabarFvSePR(gI1, gO1, gI2);
        }
        
        inline double CMSSM_mass_eigenstates::CpbarFvChiSvPL(int arg_1, int arg_2, int arg_3) const
        {
            return get_BEptr()->CpbarFvChiSvPL(arg_1, arg_2, arg_3);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFvChiSvPR(int gO1, int gI2, int gI1) const
        {
            return get_BEptr()->CpbarFvChiSvPR(gO1, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFeFehhPL(int gO2, int gI2, int gI1) const
        {
            return get_BEptr()->CpbarFeFehhPL(gO2, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFeFehhPR(int gO1, int gI2, int gI1) const
        {
            return get_BEptr()->CpbarFeFehhPR(gO1, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFeFvHpmPL(int gO2, int gI2, int gI1) const
        {
            return get_BEptr()->CpbarFeFvHpmPL(gO2, gI2, gI1);
        }
        
        inline double CMSSM_mass_eigenstates::CpbarFeFvHpmPR(int arg_1, int arg_2, int arg_3) const
        {
            return get_BEptr()->CpbarFeFvHpmPR(arg_1, arg_2, arg_3);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFeChaSvPL(int gO2, int gI2, int gI1) const
        {
            return get_BEptr()->CpbarFeChaSvPL(gO2, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFeChaSvPR(int gO1, int gI2, int gI1) const
        {
            return get_BEptr()->CpbarFeChaSvPR(gO1, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFeFeAhPL(int gO2, int gI1, int gI2) const
        {
            return get_BEptr()->CpbarFeFeAhPL(gO2, gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFeFeAhPR(int gO1, int gI1, int gI2) const
        {
            return get_BEptr()->CpbarFeFeAhPR(gO1, gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFeChiSePL(int gO2, int gI2, int gI1) const
        {
            return get_BEptr()->CpbarFeChiSePL(gO2, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFeChiSePR(int gO1, int gI2, int gI1) const
        {
            return get_BEptr()->CpbarFeChiSePR(gO1, gI2, gI1);
        }
        
        inline double CMSSM_mass_eigenstates::CpbarFeFvVWmPR(int arg_1, int arg_2) const
        {
            return get_BEptr()->CpbarFeFvVWmPR(arg_1, arg_2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFeFvVWmPL(int gO1, int gI2) const
        {
            return get_BEptr()->CpbarFeFvVWmPL(gO1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFdFdhhPL(int gO2, int gI2, int gI1) const
        {
            return get_BEptr()->CpbarFdFdhhPL(gO2, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFdFdhhPR(int gO1, int gI2, int gI1) const
        {
            return get_BEptr()->CpbarFdFdhhPR(gO1, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFdFuHpmPL(int gO2, int gI2, int gI1) const
        {
            return get_BEptr()->CpbarFdFuHpmPL(gO2, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFdFuHpmPR(int gO1, int gI2, int gI1) const
        {
            return get_BEptr()->CpbarFdFuHpmPR(gO1, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFdFdAhPL(int gO2, int gI1, int gI2) const
        {
            return get_BEptr()->CpbarFdFdAhPL(gO2, gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFdFdAhPR(int gO1, int gI1, int gI2) const
        {
            return get_BEptr()->CpbarFdFdAhPR(gO1, gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFdChaSuPL(int gO2, int gI2, int gI1) const
        {
            return get_BEptr()->CpbarFdChaSuPL(gO2, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFdChaSuPR(int gO1, int gI2, int gI1) const
        {
            return get_BEptr()->CpbarFdChaSuPR(gO1, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFdChiSdPL(int gO2, int gI2, int gI1) const
        {
            return get_BEptr()->CpbarFdChiSdPL(gO2, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFdChiSdPR(int gO1, int gI2, int gI1) const
        {
            return get_BEptr()->CpbarFdChiSdPR(gO1, gI2, gI1);
        }
        
        inline double CMSSM_mass_eigenstates::CpbarFdFuVWmPR(int arg_1, int arg_2) const
        {
            return get_BEptr()->CpbarFdFuVWmPR(arg_1, arg_2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFdFuVWmPL(int gO1, int gI2) const
        {
            return get_BEptr()->CpbarFdFuVWmPL(gO1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFuFdconjHpmPL(int gO2, int gI2, int gI1) const
        {
            return get_BEptr()->CpbarFuFdconjHpmPL(gO2, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFuFdconjHpmPR(int gO1, int gI2, int gI1) const
        {
            return get_BEptr()->CpbarFuFdconjHpmPR(gO1, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFuFuhhPL(int gO2, int gI2, int gI1) const
        {
            return get_BEptr()->CpbarFuFuhhPL(gO2, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFuFuhhPR(int gO1, int gI2, int gI1) const
        {
            return get_BEptr()->CpbarFuFuhhPR(gO1, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarChabarFuSdPL(int gI1, int gO2, int gI2) const
        {
            return get_BEptr()->CpbarChabarFuSdPL(gI1, gO2, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarChabarFuSdPR(int gI1, int gO1, int gI2) const
        {
            return get_BEptr()->CpbarChabarFuSdPR(gI1, gO1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFuFuAhPL(int gO2, int gI1, int gI2) const
        {
            return get_BEptr()->CpbarFuFuAhPL(gO2, gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFuFuAhPR(int gO1, int gI1, int gI2) const
        {
            return get_BEptr()->CpbarFuFuAhPR(gO1, gI1, gI2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFuChiSuPL(int gO2, int gI2, int gI1) const
        {
            return get_BEptr()->CpbarFuChiSuPL(gO2, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::CpbarFuChiSuPR(int gO1, int gI2, int gI1) const
        {
            return get_BEptr()->CpbarFuChiSuPR(gO1, gI2, gI1);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::self_energy_Sd_1loop(double p, int gO1, int gO2) const
        {
            return get_BEptr()->self_energy_Sd_1loop(p, gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::self_energy_Sv_1loop(double p, int gO1, int gO2) const
        {
            return get_BEptr()->self_energy_Sv_1loop(p, gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::self_energy_Su_1loop(double p, int gO1, int gO2) const
        {
            return get_BEptr()->self_energy_Su_1loop(p, gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::self_energy_Se_1loop(double p, int gO1, int gO2) const
        {
            return get_BEptr()->self_energy_Se_1loop(p, gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::self_energy_hh_1loop(double p, int gO1, int gO2) const
        {
            return get_BEptr()->self_energy_hh_1loop(p, gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::self_energy_Ah_1loop(double p, int gO1, int gO2) const
        {
            return get_BEptr()->self_energy_Ah_1loop(p, gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::self_energy_Hpm_1loop(double p, int gO1, int gO2) const
        {
            return get_BEptr()->self_energy_Hpm_1loop(p, gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::self_energy_VG_1loop(double p) const
        {
            return get_BEptr()->self_energy_VG_1loop(p);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::self_energy_VP_1loop(double p) const
        {
            return get_BEptr()->self_energy_VP_1loop(p);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::self_energy_VZ_1loop(double p) const
        {
            return get_BEptr()->self_energy_VZ_1loop(p);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::self_energy_VWm_1loop(double p) const
        {
            return get_BEptr()->self_energy_VWm_1loop(p);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::self_energy_Chi_1loop_1(double p, int gO1, int gO2) const
        {
            return get_BEptr()->self_energy_Chi_1loop_1(p, gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::self_energy_Chi_1loop_PR(double p, int gO1, int gO2) const
        {
            return get_BEptr()->self_energy_Chi_1loop_PR(p, gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::self_energy_Chi_1loop_PL(double p, int gO1, int gO2) const
        {
            return get_BEptr()->self_energy_Chi_1loop_PL(p, gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::self_energy_Cha_1loop_1(double p, int gO1, int gO2) const
        {
            return get_BEptr()->self_energy_Cha_1loop_1(p, gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::self_energy_Cha_1loop_PR(double p, int gO1, int gO2) const
        {
            return get_BEptr()->self_energy_Cha_1loop_PR(p, gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::self_energy_Cha_1loop_PL(double p, int gO1, int gO2) const
        {
            return get_BEptr()->self_energy_Cha_1loop_PL(p, gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::self_energy_Fe_1loop_1(double p, int gO1, int gO2) const
        {
            return get_BEptr()->self_energy_Fe_1loop_1(p, gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::self_energy_Fe_1loop_PR(double p, int gO1, int gO2) const
        {
            return get_BEptr()->self_energy_Fe_1loop_PR(p, gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::self_energy_Fe_1loop_PL(double p, int gO1, int gO2) const
        {
            return get_BEptr()->self_energy_Fe_1loop_PL(p, gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::self_energy_Fd_1loop_1(double p, int gO1, int gO2) const
        {
            return get_BEptr()->self_energy_Fd_1loop_1(p, gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::self_energy_Fd_1loop_PR(double p, int gO1, int gO2) const
        {
            return get_BEptr()->self_energy_Fd_1loop_PR(p, gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::self_energy_Fd_1loop_PL(double p, int gO1, int gO2) const
        {
            return get_BEptr()->self_energy_Fd_1loop_PL(p, gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::self_energy_Fu_1loop_1(double p, int gO1, int gO2) const
        {
            return get_BEptr()->self_energy_Fu_1loop_1(p, gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::self_energy_Fu_1loop_PR(double p, int gO1, int gO2) const
        {
            return get_BEptr()->self_energy_Fu_1loop_PR(p, gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::self_energy_Fu_1loop_PL(double p, int gO1, int gO2) const
        {
            return get_BEptr()->self_energy_Fu_1loop_PL(p, gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::self_energy_Glu_1loop_1(double p) const
        {
            return get_BEptr()->self_energy_Glu_1loop_1(p);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::self_energy_Glu_1loop_PR(double p) const
        {
            return get_BEptr()->self_energy_Glu_1loop_PR(p);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::self_energy_Glu_1loop_PL(double p) const
        {
            return get_BEptr()->self_energy_Glu_1loop_PL(p);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::self_energy_Fv_1loop_1(double p, int gO1, int gO2) const
        {
            return get_BEptr()->self_energy_Fv_1loop_1(p, gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::self_energy_Fv_1loop_PR(double p, int gO1, int gO2) const
        {
            return get_BEptr()->self_energy_Fv_1loop_PR(p, gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::self_energy_Fv_1loop_PL(double p, int gO1, int gO2) const
        {
            return get_BEptr()->self_energy_Fv_1loop_PL(p, gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::self_energy_Fe_1loop_1_heavy_rotated(double p, int gO1, int gO2) const
        {
            return get_BEptr()->self_energy_Fe_1loop_1_heavy_rotated(p, gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::self_energy_Fe_1loop_PR_heavy_rotated(double p, int gO1, int gO2) const
        {
            return get_BEptr()->self_energy_Fe_1loop_PR_heavy_rotated(p, gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::self_energy_Fe_1loop_PL_heavy_rotated(double p, int gO1, int gO2) const
        {
            return get_BEptr()->self_energy_Fe_1loop_PL_heavy_rotated(p, gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::self_energy_Fd_1loop_1_heavy_rotated(double p, int gO1, int gO2) const
        {
            return get_BEptr()->self_energy_Fd_1loop_1_heavy_rotated(p, gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::self_energy_Fd_1loop_PR_heavy_rotated(double p, int gO1, int gO2) const
        {
            return get_BEptr()->self_energy_Fd_1loop_PR_heavy_rotated(p, gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::self_energy_Fd_1loop_PL_heavy_rotated(double p, int gO1, int gO2) const
        {
            return get_BEptr()->self_energy_Fd_1loop_PL_heavy_rotated(p, gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::self_energy_Fu_1loop_1_heavy_rotated(double p, int gO1, int gO2) const
        {
            return get_BEptr()->self_energy_Fu_1loop_1_heavy_rotated(p, gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::self_energy_Fu_1loop_PR_heavy_rotated(double p, int gO1, int gO2) const
        {
            return get_BEptr()->self_energy_Fu_1loop_PR_heavy_rotated(p, gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::self_energy_Fu_1loop_PL_heavy_rotated(double p, int gO1, int gO2) const
        {
            return get_BEptr()->self_energy_Fu_1loop_PL_heavy_rotated(p, gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::self_energy_Fu_1loop_1_heavy(double p, int gO1, int gO2) const
        {
            return get_BEptr()->self_energy_Fu_1loop_1_heavy(p, gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::self_energy_Fu_1loop_PR_heavy(double p, int gO1, int gO2) const
        {
            return get_BEptr()->self_energy_Fu_1loop_PR_heavy(p, gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::self_energy_Fu_1loop_PL_heavy(double p, int gO1, int gO2) const
        {
            return get_BEptr()->self_energy_Fu_1loop_PL_heavy(p, gO1, gO2);
        }
        
        inline ::std::complex<double> CMSSM_mass_eigenstates::tadpole_hh_1loop(int gO1) const
        {
            return get_BEptr()->tadpole_hh_1loop(gO1);
        }
        
        inline void CMSSM_mass_eigenstates::tadpole_equations(double* arg_1) const
        {
            get_BEptr()->tadpole_equations(arg_1);
        }
        
        inline void CMSSM_mass_eigenstates::calculate_MSu_2nd_generation(double& arg_1, double& arg_2, double& arg_3) const
        {
            get_BEptr()->calculate_MSu_2nd_generation(arg_1, arg_2, arg_3);
        }
        
        inline void CMSSM_mass_eigenstates::calculate_MSd_2nd_generation(double& arg_1, double& arg_2, double& arg_3) const
        {
            get_BEptr()->calculate_MSd_2nd_generation(arg_1, arg_2, arg_3);
        }
        
        inline void CMSSM_mass_eigenstates::calculate_MSv_2nd_generation(double& arg_1, double& arg_2, double& arg_3) const
        {
            get_BEptr()->calculate_MSv_2nd_generation(arg_1, arg_2, arg_3);
        }
        
        inline void CMSSM_mass_eigenstates::calculate_MSe_2nd_generation(double& arg_1, double& arg_2, double& arg_3) const
        {
            get_BEptr()->calculate_MSe_2nd_generation(arg_1, arg_2, arg_3);
        }
        
        inline void CMSSM_mass_eigenstates::calculate_MSu_3rd_generation(double& arg_1, double& arg_2, double& arg_3) const
        {
            get_BEptr()->calculate_MSu_3rd_generation(arg_1, arg_2, arg_3);
        }
        
        inline void CMSSM_mass_eigenstates::calculate_MSd_3rd_generation(double& arg_1, double& arg_2, double& arg_3) const
        {
            get_BEptr()->calculate_MSd_3rd_generation(arg_1, arg_2, arg_3);
        }
        
        inline void CMSSM_mass_eigenstates::calculate_MSv_3rd_generation(double& arg_1, double& arg_2, double& arg_3) const
        {
            get_BEptr()->calculate_MSv_3rd_generation(arg_1, arg_2, arg_3);
        }
        
        inline void CMSSM_mass_eigenstates::calculate_MSe_3rd_generation(double& arg_1, double& arg_2, double& arg_3) const
        {
            get_BEptr()->calculate_MSe_3rd_generation(arg_1, arg_2, arg_3);
        }
        
        inline void CMSSM_mass_eigenstates::calculate_MVG_pole()
        {
            get_BEptr()->calculate_MVG_pole();
        }
        
        inline void CMSSM_mass_eigenstates::calculate_MGlu_pole()
        {
            get_BEptr()->calculate_MGlu_pole();
        }
        
        inline void CMSSM_mass_eigenstates::calculate_MFv_pole()
        {
            get_BEptr()->calculate_MFv_pole();
        }
        
        inline void CMSSM_mass_eigenstates::calculate_MVP_pole()
        {
            get_BEptr()->calculate_MVP_pole();
        }
        
        inline void CMSSM_mass_eigenstates::calculate_MVZ_pole()
        {
            get_BEptr()->calculate_MVZ_pole();
        }
        
        inline void CMSSM_mass_eigenstates::calculate_MSd_pole()
        {
            get_BEptr()->calculate_MSd_pole();
        }
        
        inline void CMSSM_mass_eigenstates::calculate_MSv_pole()
        {
            get_BEptr()->calculate_MSv_pole();
        }
        
        inline void CMSSM_mass_eigenstates::calculate_MSu_pole()
        {
            get_BEptr()->calculate_MSu_pole();
        }
        
        inline void CMSSM_mass_eigenstates::calculate_MSe_pole()
        {
            get_BEptr()->calculate_MSe_pole();
        }
        
        inline void CMSSM_mass_eigenstates::calculate_Mhh_pole()
        {
            get_BEptr()->calculate_Mhh_pole();
        }
        
        inline void CMSSM_mass_eigenstates::calculate_MAh_pole()
        {
            get_BEptr()->calculate_MAh_pole();
        }
        
        inline void CMSSM_mass_eigenstates::calculate_MHpm_pole()
        {
            get_BEptr()->calculate_MHpm_pole();
        }
        
        inline void CMSSM_mass_eigenstates::calculate_MChi_pole()
        {
            get_BEptr()->calculate_MChi_pole();
        }
        
        inline void CMSSM_mass_eigenstates::calculate_MCha_pole()
        {
            get_BEptr()->calculate_MCha_pole();
        }
        
        inline void CMSSM_mass_eigenstates::calculate_MFe_pole()
        {
            get_BEptr()->calculate_MFe_pole();
        }
        
        inline void CMSSM_mass_eigenstates::calculate_MFd_pole()
        {
            get_BEptr()->calculate_MFd_pole();
        }
        
        inline void CMSSM_mass_eigenstates::calculate_MFu_pole()
        {
            get_BEptr()->calculate_MFu_pole();
        }
        
        inline void CMSSM_mass_eigenstates::calculate_MVWm_pole()
        {
            get_BEptr()->calculate_MVWm_pole();
        }
        
        inline double CMSSM_mass_eigenstates::calculate_MVWm_pole(double arg_1)
        {
            return get_BEptr()->calculate_MVWm_pole(arg_1);
        }
        
        inline double CMSSM_mass_eigenstates::calculate_MVZ_pole(double arg_1)
        {
            return get_BEptr()->calculate_MVZ_pole(arg_1);
        }
        
        inline double CMSSM_mass_eigenstates::calculate_MFv_DRbar(double arg_1, int arg_2) const
        {
            return get_BEptr()->calculate_MFv_DRbar(arg_1, arg_2);
        }
        
        inline double CMSSM_mass_eigenstates::calculate_MFe_DRbar(double arg_1, int arg_2) const
        {
            return get_BEptr()->calculate_MFe_DRbar(arg_1, arg_2);
        }
        
        inline double CMSSM_mass_eigenstates::calculate_MFu_DRbar(double arg_1, int arg_2) const
        {
            return get_BEptr()->calculate_MFu_DRbar(arg_1, arg_2);
        }
        
        inline double CMSSM_mass_eigenstates::calculate_MFd_DRbar(double arg_1, int arg_2) const
        {
            return get_BEptr()->calculate_MFd_DRbar(arg_1, arg_2);
        }
        
        inline double CMSSM_mass_eigenstates::calculate_MVP_DRbar(double arg_1)
        {
            return get_BEptr()->calculate_MVP_DRbar(arg_1);
        }
        
        inline double CMSSM_mass_eigenstates::calculate_MVZ_DRbar(double arg_1)
        {
            return get_BEptr()->calculate_MVZ_DRbar(arg_1);
        }
        
        inline double CMSSM_mass_eigenstates::calculate_MVWm_DRbar(double arg_1)
        {
            return get_BEptr()->calculate_MVWm_DRbar(arg_1);
        }
        
        inline double CMSSM_mass_eigenstates::v() const
        {
            return get_BEptr()->v();
        }
        
        inline double CMSSM_mass_eigenstates::Betax() const
        {
            return get_BEptr()->Betax();
        }
        
        inline double CMSSM_mass_eigenstates::Alpha() const
        {
            return get_BEptr()->Alpha();
        }
        
        inline double CMSSM_mass_eigenstates::ThetaW() const
        {
            return get_BEptr()->ThetaW();
        }
        
        
        // Wrappers for original constructors: 
        inline CMSSM_mass_eigenstates::CMSSM_mass_eigenstates(const flexiblesusy::CMSSM_input_parameters& input_) :
            CMSSM_soft_parameters(__factory0(input_)),
            number_of_ewsb_equations( get_BEptr()->number_of_ewsb_equations_ref__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline CMSSM_mass_eigenstates::CMSSM_mass_eigenstates() :
            CMSSM_soft_parameters(__factory1()),
            number_of_ewsb_equations( get_BEptr()->number_of_ewsb_equations_ref__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline CMSSM_mass_eigenstates::CMSSM_mass_eigenstates(Abstract_CMSSM_mass_eigenstates* in) :
            CMSSM_soft_parameters(in),
            number_of_ewsb_equations( get_BEptr()->number_of_ewsb_equations_ref__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Copy constructor: 
        inline CMSSM_mass_eigenstates::CMSSM_mass_eigenstates(const CMSSM_mass_eigenstates& in) :
            CMSSM_soft_parameters(in.get_BEptr()->pointer_copy__BOSS()),
            number_of_ewsb_equations( get_BEptr()->number_of_ewsb_equations_ref__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline CMSSM_mass_eigenstates& CMSSM_mass_eigenstates::operator=(const CMSSM_mass_eigenstates& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline CMSSM_mass_eigenstates::~CMSSM_mass_eigenstates()
        {
            if (get_BEptr() != 0)
            {
                get_BEptr()->set_delete_wrapper(false);
                if (can_delete_BEptr())
                {
                    delete BEptr;
                    BEptr = 0;
                }
            }
            set_delete_BEptr(false);
        }
        
        // Returns correctly casted pointer to Abstract class: 
        inline Abstract_CMSSM_mass_eigenstates* flexiblesusy::CMSSM_mass_eigenstates::get_BEptr() const
        {
            return dynamic_cast<Abstract_CMSSM_mass_eigenstates*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_CMSSM_mass_eigenstates_def_FlexibleSUSY_CMSSM_2_0_1_h__ */
