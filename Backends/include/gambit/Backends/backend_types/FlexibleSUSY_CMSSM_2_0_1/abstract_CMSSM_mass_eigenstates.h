#ifndef __abstract_CMSSM_mass_eigenstates_FlexibleSUSY_CMSSM_2_0_1_h__
#define __abstract_CMSSM_mass_eigenstates_FlexibleSUSY_CMSSM_2_0_1_h__

#include <cstddef>
#include <iostream>
#include <string>
#include <ostream>
#include <complex>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.h"
#include "forward_decls_wrapper_classes.h"
#include "wrapper_CMSSM_input_parameters_decl.h"
#include "wrapper_CMSSM_soft_parameters_decl.h"

#include "enum_decl_copies.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    namespace flexiblesusy
    {
        class Abstract_CMSSM_mass_eigenstates : virtual public flexiblesusy::Abstract_CMSSM_soft_parameters
        {
            public:
    
                virtual flexiblesusy::Abstract_CMSSM_mass_eigenstates& operator_equal__BOSS(const flexiblesusy::Abstract_CMSSM_mass_eigenstates&) =0;
    
                virtual const int& number_of_ewsb_equations_ref__BOSS() =0;
    
                virtual void calculate_DRbar_masses() =0;
    
                virtual void calculate_pole_masses() =0;
    
                virtual void check_pole_masses_for_tachyons() =0;
    
                virtual void clear() =0;
    
                virtual void clear_DRbar_parameters() =0;
    
                virtual void do_calculate_sm_pole_masses(bool) =0;
    
                virtual bool do_calculate_sm_pole_masses() const =0;
    
                virtual void do_calculate_bsm_pole_masses(bool) =0;
    
                virtual bool do_calculate_bsm_pole_masses() const =0;
    
                virtual void do_force_output(bool) =0;
    
                virtual bool do_force_output() const =0;
    
                virtual void reorder_DRbar_masses() =0;
    
                virtual void reorder_pole_masses() =0;
    
                virtual void set_ewsb_iteration_precision(double) =0;
    
                virtual void set_ewsb_loop_order(int) =0;
    
                virtual void set_pole_mass_loop_order(int) =0;
    
                virtual int get_pole_mass_loop_order() const =0;
    
                virtual double get_ewsb_iteration_precision() const =0;
    
                virtual double get_ewsb_loop_order() const =0;
    
                virtual int solve_ewsb_tree_level() =0;
    
                virtual int solve_ewsb_one_loop() =0;
    
                virtual int solve_ewsb() =0;
    
                virtual void calculate_spectrum() =0;
    
                virtual void clear_problems() =0;
    
                virtual ::std::basic_string<char> name() const =0;
    
                virtual void run_to(double, double) =0;
    
                virtual void run_to__BOSS(double) =0;
    
                virtual void print(::std::basic_ostream<char>&) const =0;
    
                virtual void print__BOSS() const =0;
    
                virtual void set_precision(double) =0;
    
                virtual double get_precision() const =0;
    
                virtual double get_MVG() const =0;
    
                virtual double get_MGlu() const =0;
    
                virtual double get_MFv(int) const =0;
    
                virtual double get_MSd(int) const =0;
    
                virtual double get_MSv(int) const =0;
    
                virtual double get_MSu(int) const =0;
    
                virtual double get_MSe(int) const =0;
    
                virtual double get_Mhh(int) const =0;
    
                virtual double get_MAh(int) const =0;
    
                virtual double get_MHpm(int) const =0;
    
                virtual double get_MChi(int) const =0;
    
                virtual double get_MCha(int) const =0;
    
                virtual double get_MFe(int) const =0;
    
                virtual double get_MFd(int) const =0;
    
                virtual double get_MFu(int) const =0;
    
                virtual double get_MVWm() const =0;
    
                virtual double get_MVP() const =0;
    
                virtual double get_MVZ() const =0;
    
                virtual double get_ZD(int, int) const =0;
    
                virtual double get_ZV(int, int) const =0;
    
                virtual double get_ZU(int, int) const =0;
    
                virtual double get_ZE(int, int) const =0;
    
                virtual double get_ZH(int, int) const =0;
    
                virtual double get_ZA(int, int) const =0;
    
                virtual double get_ZP(int, int) const =0;
    
                virtual ::std::complex<double> get_ZN(int, int) const =0;
    
                virtual ::std::complex<double> get_UM(int, int) const =0;
    
                virtual ::std::complex<double> get_UP(int, int) const =0;
    
                virtual ::std::complex<double> get_ZEL(int, int) const =0;
    
                virtual ::std::complex<double> get_ZER(int, int) const =0;
    
                virtual ::std::complex<double> get_ZDL(int, int) const =0;
    
                virtual ::std::complex<double> get_ZDR(int, int) const =0;
    
                virtual ::std::complex<double> get_ZUL(int, int) const =0;
    
                virtual ::std::complex<double> get_ZUR(int, int) const =0;
    
                virtual double get_ZZ(int, int) const =0;
    
                virtual void set_PhaseGlu(::std::complex<double>) =0;
    
                virtual ::std::complex<double> get_PhaseGlu() const =0;
    
                virtual double get_mass_matrix_VG() const =0;
    
                virtual void calculate_MVG() =0;
    
                virtual double get_mass_matrix_Glu() const =0;
    
                virtual void calculate_MGlu() =0;
    
                virtual void calculate_MFv() =0;
    
                virtual void calculate_MSd() =0;
    
                virtual void calculate_MSv() =0;
    
                virtual void calculate_MSu() =0;
    
                virtual void calculate_MSe() =0;
    
                virtual void calculate_Mhh() =0;
    
                virtual void calculate_MAh() =0;
    
                virtual void calculate_MHpm() =0;
    
                virtual void calculate_MChi() =0;
    
                virtual void calculate_MCha() =0;
    
                virtual void calculate_MFe() =0;
    
                virtual void calculate_MFd() =0;
    
                virtual void calculate_MFu() =0;
    
                virtual double get_mass_matrix_VWm() const =0;
    
                virtual void calculate_MVWm() =0;
    
                virtual void calculate_MVPVZ() =0;
    
                virtual double get_ewsb_eq_hh_1() const =0;
    
                virtual double get_ewsb_eq_hh_2() const =0;
    
                virtual ::std::complex<double> CpUSdconjUSdVZVZ(int, int) const =0;
    
                virtual double CpUSdconjUSdconjVWmVWm(int, int) const =0;
    
                virtual ::std::complex<double> CpAhAhUSdconjUSd(int, int, int, int) const =0;
    
                virtual ::std::complex<double> CphhhhUSdconjUSd(int, int, int, int) const =0;
    
                virtual ::std::complex<double> CpHpmUSdconjHpmconjUSd(int, int, int, int) const =0;
    
                virtual ::std::complex<double> CpUSdSvconjUSdconjSv(int, int, int, int) const =0;
    
                virtual ::std::complex<double> CpChaFuconjUSdPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpChaFuconjUSdPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpChiFdconjUSdPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpChiFdconjUSdPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpUSdconjUSdconjSdSd(int, int, int, int) const =0;
    
                virtual ::std::complex<double> CpUSdconjUSdconjSuSu(int, int, int, int) const =0;
    
                virtual ::std::complex<double> CpUSdSeconjUSdconjSe(int, int, int, int) const =0;
    
                virtual ::std::complex<double> CpAhSdconjUSd(int, int, int) const =0;
    
                virtual ::std::complex<double> CphhSdconjUSd(int, int, int) const =0;
    
                virtual ::std::complex<double> CpHpmSuconjUSd(int, int, int) const =0;
    
                virtual ::std::complex<double> CpGluFdconjUSdPR(int, int) const =0;
    
                virtual ::std::complex<double> CpGluFdconjUSdPL(int, int) const =0;
    
                virtual ::std::complex<double> CpSdconjUSdVG(int, int) const =0;
    
                virtual ::std::complex<double> CpSdconjUSdVP(int, int) const =0;
    
                virtual ::std::complex<double> CpSdconjUSdVZ(int, int) const =0;
    
                virtual ::std::complex<double> CpSuconjUSdVWm(int, int) const =0;
    
                virtual ::std::complex<double> CpUSvconjUSvVZVZ(int, int) const =0;
    
                virtual double CpUSvconjUSvconjVWmVWm(int, int) const =0;
    
                virtual ::std::complex<double> CpAhAhUSvconjUSv(int, int, int, int) const =0;
    
                virtual ::std::complex<double> CphhhhUSvconjUSv(int, int, int, int) const =0;
    
                virtual ::std::complex<double> CpHpmUSvconjHpmconjUSv(int, int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarChaFeconjUSvPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarChaFeconjUSvPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpSeconjHpmconjUSv(int, int, int) const =0;
    
                virtual ::std::complex<double> CpSvUSvconjSvconjUSv(int, int, int, int) const =0;
    
                virtual ::std::complex<double> CphhSvconjUSv(int, int, int) const =0;
    
                virtual double CpChiFvconjUSvPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpChiFvconjUSvPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpSdUSvconjSdconjUSv(int, int, int, int) const =0;
    
                virtual ::std::complex<double> CpSeUSvconjSeconjUSv(int, int, int, int) const =0;
    
                virtual ::std::complex<double> CpSuUSvconjSuconjUSv(int, int, int, int) const =0;
    
                virtual ::std::complex<double> CpSvconjUSvVZ(int, int) const =0;
    
                virtual ::std::complex<double> CpSeconjUSvconjVWm(int, int) const =0;
    
                virtual ::std::complex<double> CpUSuconjUSuVZVZ(int, int) const =0;
    
                virtual double CpUSuconjUSuconjVWmVWm(int, int) const =0;
    
                virtual ::std::complex<double> CpAhAhUSuconjUSu(int, int, int, int) const =0;
    
                virtual ::std::complex<double> CphhhhUSuconjUSu(int, int, int, int) const =0;
    
                virtual ::std::complex<double> CpHpmUSuconjHpmconjUSu(int, int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarChaFdconjUSuPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarChaFdconjUSuPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpSdconjHpmconjUSu(int, int, int) const =0;
    
                virtual ::std::complex<double> CpUSuSvconjUSuconjSv(int, int, int, int) const =0;
    
                virtual ::std::complex<double> CpChiFuconjUSuPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpChiFuconjUSuPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpSeUSuconjSeconjUSu(int, int, int, int) const =0;
    
                virtual ::std::complex<double> CpUSuconjUSuconjSdSd(int, int, int, int) const =0;
    
                virtual ::std::complex<double> CpUSuconjUSuconjSuSu(int, int, int, int) const =0;
    
                virtual ::std::complex<double> CpAhSuconjUSu(int, int, int) const =0;
    
                virtual ::std::complex<double> CphhSuconjUSu(int, int, int) const =0;
    
                virtual ::std::complex<double> CpGluFuconjUSuPR(int, int) const =0;
    
                virtual ::std::complex<double> CpGluFuconjUSuPL(int, int) const =0;
    
                virtual ::std::complex<double> CpSdconjUSuconjVWm(int, int) const =0;
    
                virtual ::std::complex<double> CpSuconjUSuVG(int, int) const =0;
    
                virtual ::std::complex<double> CpSuconjUSuVP(int, int) const =0;
    
                virtual ::std::complex<double> CpSuconjUSuVZ(int, int) const =0;
    
                virtual ::std::complex<double> CpUSeconjUSeVZVZ(int, int) const =0;
    
                virtual double CpUSeconjUSeconjVWmVWm(int, int) const =0;
    
                virtual ::std::complex<double> CpAhAhUSeconjUSe(int, int, int, int) const =0;
    
                virtual ::std::complex<double> CphhhhUSeconjUSe(int, int, int, int) const =0;
    
                virtual ::std::complex<double> CpHpmUSeconjHpmconjUSe(int, int, int, int) const =0;
    
                virtual ::std::complex<double> CpUSeSvconjUSeconjSv(int, int, int, int) const =0;
    
                virtual ::std::complex<double> CpHpmSvconjUSe(int, int, int) const =0;
    
                virtual double CpChaFvconjUSePR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpChaFvconjUSePL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpChiFeconjUSePR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpChiFeconjUSePL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpSdUSeconjSdconjUSe(int, int, int, int) const =0;
    
                virtual ::std::complex<double> CpSeUSeconjSeconjUSe(int, int, int, int) const =0;
    
                virtual ::std::complex<double> CpUSeSuconjUSeconjSu(int, int, int, int) const =0;
    
                virtual ::std::complex<double> CpAhSeconjUSe(int, int, int) const =0;
    
                virtual ::std::complex<double> CphhSeconjUSe(int, int, int) const =0;
    
                virtual ::std::complex<double> CpSvconjUSeVWm(int, int) const =0;
    
                virtual ::std::complex<double> CpSeconjUSeVP(int, int) const =0;
    
                virtual ::std::complex<double> CpSeconjUSeVZ(int, int) const =0;
    
                virtual ::std::complex<double> CpbargWmgWmUhh(int) const =0;
    
                virtual ::std::complex<double> CpbargWmCgWmCUhh(int) const =0;
    
                virtual ::std::complex<double> CpbargZgZUhh(int) const =0;
    
                virtual ::std::complex<double> CpUhhVZVZ(int) const =0;
    
                virtual ::std::complex<double> CpUhhconjVWmVWm(int) const =0;
    
                virtual ::std::complex<double> CpUhhUhhVZVZ(int, int) const =0;
    
                virtual ::std::complex<double> CpUhhUhhconjVWmVWm(int, int) const =0;
    
                virtual ::std::complex<double> CpAhAhUhhUhh(int, int, int, int) const =0;
    
                virtual ::std::complex<double> CphhhhUhhUhh(int, int, int, int) const =0;
    
                virtual ::std::complex<double> CpUhhUhhHpmconjHpm(int, int, int, int) const =0;
    
                virtual ::std::complex<double> CpAhAhUhh(int, int, int) const =0;
    
                virtual ::std::complex<double> CphhhhUhh(int, int, int) const =0;
    
                virtual ::std::complex<double> CpUhhHpmconjHpm(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarChaChaUhhPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarChaChaUhhPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpUhhUhhSvconjSv(int, int, int, int) const =0;
    
                virtual ::std::complex<double> CpUhhSvconjSv(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarFdFdUhhPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarFdFdUhhPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarFeFeUhhPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarFeFeUhhPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarFuFuUhhPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarFuFuUhhPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpChiChiUhhPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpChiChiUhhPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpUhhUhhSdconjSd(int, int, int, int) const =0;
    
                virtual ::std::complex<double> CpUhhUhhSeconjSe(int, int, int, int) const =0;
    
                virtual ::std::complex<double> CpUhhUhhSuconjSu(int, int, int, int) const =0;
    
                virtual ::std::complex<double> CpUhhSdconjSd(int, int, int) const =0;
    
                virtual ::std::complex<double> CpUhhSeconjSe(int, int, int) const =0;
    
                virtual ::std::complex<double> CpUhhSuconjSu(int, int, int) const =0;
    
                virtual ::std::complex<double> CpAhUhhVZ(int, int) const =0;
    
                virtual ::std::complex<double> CpUhhHpmconjVWm(int, int) const =0;
    
                virtual ::std::complex<double> CpbargWmgWmUAh(int) const =0;
    
                virtual ::std::complex<double> CpbargWmCgWmCUAh(int) const =0;
    
                virtual ::std::complex<double> CpUAhUAhVZVZ(int, int) const =0;
    
                virtual ::std::complex<double> CpUAhUAhconjVWmVWm(int, int) const =0;
    
                virtual ::std::complex<double> CpAhAhUAhUAh(int, int, int, int) const =0;
    
                virtual ::std::complex<double> CpUAhUAhhhhh(int, int, int, int) const =0;
    
                virtual ::std::complex<double> CpUAhUAhHpmconjHpm(int, int, int, int) const =0;
    
                virtual ::std::complex<double> CpAhUAhhh(int, int, int) const =0;
    
                virtual ::std::complex<double> CpUAhHpmconjHpm(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarChaChaUAhPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarChaChaUAhPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpUAhUAhSvconjSv(int, int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarFdFdUAhPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarFdFdUAhPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarFeFeUAhPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarFeFeUAhPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarFuFuUAhPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarFuFuUAhPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpChiChiUAhPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpChiChiUAhPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpUAhUAhSdconjSd(int, int, int, int) const =0;
    
                virtual ::std::complex<double> CpUAhUAhSeconjSe(int, int, int, int) const =0;
    
                virtual ::std::complex<double> CpUAhUAhSuconjSu(int, int, int, int) const =0;
    
                virtual ::std::complex<double> CpUAhSdconjSd(int, int, int) const =0;
    
                virtual ::std::complex<double> CpUAhSeconjSe(int, int, int) const =0;
    
                virtual ::std::complex<double> CpUAhSuconjSu(int, int, int) const =0;
    
                virtual ::std::complex<double> CpUAhhhVZ(int, int) const =0;
    
                virtual ::std::complex<double> CpUAhHpmconjVWm(int, int) const =0;
    
                virtual ::std::complex<double> CpbargWmgZUHpm(int) const =0;
    
                virtual ::std::complex<double> CpbargZgWmconjUHpm(int) const =0;
    
                virtual ::std::complex<double> CpbargWmCgZconjUHpm(int) const =0;
    
                virtual ::std::complex<double> CpbargZgWmCUHpm(int) const =0;
    
                virtual ::std::complex<double> CpconjUHpmVPVWm(int) const =0;
    
                virtual ::std::complex<double> CpconjUHpmVWmVZ(int) const =0;
    
                virtual ::std::complex<double> CpUHpmconjUHpmVZVZ(int, int) const =0;
    
                virtual ::std::complex<double> CpUHpmconjUHpmconjVWmVWm(int, int) const =0;
    
                virtual ::std::complex<double> CpAhAhUHpmconjUHpm(int, int, int, int) const =0;
    
                virtual ::std::complex<double> CphhhhUHpmconjUHpm(int, int, int, int) const =0;
    
                virtual ::std::complex<double> CpHpmUHpmconjHpmconjUHpm(int, int, int, int) const =0;
    
                virtual ::std::complex<double> CpAhHpmconjUHpm(int, int, int) const =0;
    
                virtual ::std::complex<double> CphhHpmconjUHpm(int, int, int) const =0;
    
                virtual ::std::complex<double> CpUHpmSvconjUHpmconjSv(int, int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarFuFdconjUHpmPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarFuFdconjUHpmPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarFvFeconjUHpmPR(int, int, int) const =0;
    
                virtual double CpbarFvFeconjUHpmPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpSeconjUHpmconjSv(int, int, int) const =0;
    
                virtual ::std::complex<double> CpChiChaconjUHpmPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpChiChaconjUHpmPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpUHpmSdconjUHpmconjSd(int, int, int, int) const =0;
    
                virtual ::std::complex<double> CpUHpmSeconjUHpmconjSe(int, int, int, int) const =0;
    
                virtual ::std::complex<double> CpUHpmSuconjUHpmconjSu(int, int, int, int) const =0;
    
                virtual ::std::complex<double> CpSdconjUHpmconjSu(int, int, int) const =0;
    
                virtual ::std::complex<double> CpAhconjUHpmVWm(int, int) const =0;
    
                virtual ::std::complex<double> CphhconjUHpmVWm(int, int) const =0;
    
                virtual ::std::complex<double> CpHpmconjUHpmVP(int, int) const =0;
    
                virtual ::std::complex<double> CpHpmconjUHpmVZ(int, int) const =0;
    
                virtual ::std::complex<double> CpVGVGVG() const =0;
    
                virtual ::std::complex<double> CpbargGgGVG() const =0;
    
                virtual double CpbarFdFdVGPL(int, int) const =0;
    
                virtual double CpbarFdFdVGPR(int, int) const =0;
    
                virtual double CpbarFuFuVGPL(int, int) const =0;
    
                virtual double CpbarFuFuVGPR(int, int) const =0;
    
                virtual double CpSdconjSdVGVG(int, int) const =0;
    
                virtual double CpSuconjSuVGVG(int, int) const =0;
    
                virtual double CpSdconjSdVG(int, int) const =0;
    
                virtual double CpSuconjSuVG(int, int) const =0;
    
                virtual ::std::complex<double> CpGluGluVGPL() const =0;
    
                virtual ::std::complex<double> CpGluGluVGPR() const =0;
    
                virtual double CpVGVGVGVG1() const =0;
    
                virtual double CpVGVGVGVG2() const =0;
    
                virtual double CpVGVGVGVG3() const =0;
    
                virtual double CpbargWmgWmVP() const =0;
    
                virtual double CpbargWmCgWmCVP() const =0;
    
                virtual double CpconjVWmVPVWm() const =0;
    
                virtual ::std::complex<double> CpHpmconjHpmVPVP(int, int) const =0;
    
                virtual double CpHpmconjHpmVP(int, int) const =0;
    
                virtual ::std::complex<double> CpbarChaChaVPPL(int, int) const =0;
    
                virtual ::std::complex<double> CpbarChaChaVPPR(int, int) const =0;
    
                virtual double CpbarFdFdVPPL(int, int) const =0;
    
                virtual double CpbarFdFdVPPR(int, int) const =0;
    
                virtual double CpbarFeFeVPPL(int, int) const =0;
    
                virtual double CpbarFeFeVPPR(int, int) const =0;
    
                virtual double CpbarFuFuVPPL(int, int) const =0;
    
                virtual double CpbarFuFuVPPR(int, int) const =0;
    
                virtual ::std::complex<double> CpSdconjSdVPVP(int, int) const =0;
    
                virtual ::std::complex<double> CpSeconjSeVPVP(int, int) const =0;
    
                virtual ::std::complex<double> CpSuconjSuVPVP(int, int) const =0;
    
                virtual ::std::complex<double> CpSdconjSdVP(int, int) const =0;
    
                virtual ::std::complex<double> CpSeconjSeVP(int, int) const =0;
    
                virtual ::std::complex<double> CpSuconjSuVP(int, int) const =0;
    
                virtual ::std::complex<double> CpHpmconjVWmVP(int) const =0;
    
                virtual double CpconjVWmVPVPVWm1() const =0;
    
                virtual double CpconjVWmVPVPVWm2() const =0;
    
                virtual double CpconjVWmVPVPVWm3() const =0;
    
                virtual double CpbargWmgWmVZ() const =0;
    
                virtual double CpbargWmCgWmCVZ() const =0;
    
                virtual double CpconjVWmVWmVZ() const =0;
    
                virtual ::std::complex<double> CpAhAhVZVZ(int, int) const =0;
    
                virtual ::std::complex<double> CphhhhVZVZ(int, int) const =0;
    
                virtual ::std::complex<double> CpHpmconjHpmVZVZ(int, int) const =0;
    
                virtual ::std::complex<double> CpAhhhVZ(int, int) const =0;
    
                virtual double CpHpmconjHpmVZ(int, int) const =0;
    
                virtual ::std::complex<double> CpbarChaChaVZPL(int, int) const =0;
    
                virtual ::std::complex<double> CpbarChaChaVZPR(int, int) const =0;
    
                virtual ::std::complex<double> CpSvconjSvVZVZ(int, int) const =0;
    
                virtual double CpSvconjSvVZ(int, int) const =0;
    
                virtual double CpbarFdFdVZPL(int, int) const =0;
    
                virtual double CpbarFdFdVZPR(int, int) const =0;
    
                virtual double CpbarFeFeVZPL(int, int) const =0;
    
                virtual double CpbarFeFeVZPR(int, int) const =0;
    
                virtual double CpbarFuFuVZPL(int, int) const =0;
    
                virtual double CpbarFuFuVZPR(int, int) const =0;
    
                virtual double CpbarFvFvVZPL(int, int) const =0;
    
                virtual double CpbarFvFvVZPR(int, int) const =0;
    
                virtual ::std::complex<double> CpChiChiVZPL(int, int) const =0;
    
                virtual ::std::complex<double> CpChiChiVZPR(int, int) const =0;
    
                virtual ::std::complex<double> CpSdconjSdVZVZ(int, int) const =0;
    
                virtual ::std::complex<double> CpSeconjSeVZVZ(int, int) const =0;
    
                virtual ::std::complex<double> CpSuconjSuVZVZ(int, int) const =0;
    
                virtual ::std::complex<double> CpSdconjSdVZ(int, int) const =0;
    
                virtual ::std::complex<double> CpSeconjSeVZ(int, int) const =0;
    
                virtual ::std::complex<double> CpSuconjSuVZ(int, int) const =0;
    
                virtual ::std::complex<double> CphhVZVZ(int) const =0;
    
                virtual ::std::complex<double> CpHpmconjVWmVZ(int) const =0;
    
                virtual double CpconjVWmVWmVZVZ1() const =0;
    
                virtual double CpconjVWmVWmVZVZ2() const =0;
    
                virtual double CpconjVWmVWmVZVZ3() const =0;
    
                virtual double CpbargPgWmconjVWm() const =0;
    
                virtual double CpbargWmCgPconjVWm() const =0;
    
                virtual double CpbargWmCgZconjVWm() const =0;
    
                virtual double CpbargZgWmconjVWm() const =0;
    
                virtual ::std::complex<double> CpAhAhconjVWmVWm(int, int) const =0;
    
                virtual ::std::complex<double> CphhhhconjVWmVWm(int, int) const =0;
    
                virtual ::std::complex<double> CpHpmconjHpmconjVWmVWm(int, int) const =0;
    
                virtual ::std::complex<double> CpAhHpmconjVWm(int, int) const =0;
    
                virtual ::std::complex<double> CphhHpmconjVWm(int, int) const =0;
    
                virtual double CpSvconjSvconjVWmVWm(int, int) const =0;
    
                virtual ::std::complex<double> CpbarFuFdconjVWmPL(int, int) const =0;
    
                virtual double CpbarFuFdconjVWmPR(int, int) const =0;
    
                virtual ::std::complex<double> CpbarFvFeconjVWmPL(int, int) const =0;
    
                virtual double CpbarFvFeconjVWmPR(int, int) const =0;
    
                virtual ::std::complex<double> CpSeconjSvconjVWm(int, int) const =0;
    
                virtual ::std::complex<double> CpChiChaconjVWmPL(int, int) const =0;
    
                virtual ::std::complex<double> CpChiChaconjVWmPR(int, int) const =0;
    
                virtual ::std::complex<double> CpSdconjSdconjVWmVWm(int, int) const =0;
    
                virtual ::std::complex<double> CpSeconjSeconjVWmVWm(int, int) const =0;
    
                virtual ::std::complex<double> CpSuconjSuconjVWmVWm(int, int) const =0;
    
                virtual ::std::complex<double> CpSdconjSuconjVWm(int, int) const =0;
    
                virtual ::std::complex<double> CphhconjVWmVWm(int) const =0;
    
                virtual double CpconjVWmconjVWmVWmVWm1() const =0;
    
                virtual double CpconjVWmconjVWmVWmVWm2() const =0;
    
                virtual double CpconjVWmconjVWmVWmVWm3() const =0;
    
                virtual ::std::complex<double> CpbarChaUChiHpmPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarChaUChiHpmPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpUChiChaconjHpmPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpUChiChaconjHpmPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpChiUChihhPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpChiUChihhPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarChaUChiVWmPL(int, int) const =0;
    
                virtual ::std::complex<double> CpbarChaUChiVWmPR(int, int) const =0;
    
                virtual double CpbarFvUChiSvPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarFvUChiSvPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpUChiFvconjSvPL(int, int, int) const =0;
    
                virtual double CpUChiFvconjSvPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarFdUChiSdPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarFdUChiSdPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarFeUChiSePL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarFeUChiSePR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarFuUChiSuPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarFuUChiSuPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpChiUChiAhPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpChiUChiAhPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpUChiFdconjSdPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpUChiFdconjSdPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpUChiFeconjSePL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpUChiFeconjSePR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpUChiFuconjSuPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpUChiFuconjSuPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpUChiChaconjVWmPR(int, int) const =0;
    
                virtual ::std::complex<double> CpUChiChaconjVWmPL(int, int) const =0;
    
                virtual ::std::complex<double> CpChiUChiVZPL(int, int) const =0;
    
                virtual ::std::complex<double> CpChiUChiVZPR(int, int) const =0;
    
                virtual ::std::complex<double> CpbarUChaChaAhPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarUChaChaAhPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarUChaChahhPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarUChaChahhPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarUChaChiHpmPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarUChaChiHpmPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarUChaFeconjSvPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarUChaFeconjSvPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarUChabarFuSdPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarUChabarFuSdPR(int, int, int) const =0;
    
                virtual double CpbarUChabarFvSePL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarUChabarFvSePR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarUChaFdconjSuPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarUChaFdconjSuPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarUChaChaVPPR(int, int) const =0;
    
                virtual ::std::complex<double> CpbarUChaChaVPPL(int, int) const =0;
    
                virtual ::std::complex<double> CpbarUChaChaVZPR(int, int) const =0;
    
                virtual ::std::complex<double> CpbarUChaChaVZPL(int, int) const =0;
    
                virtual ::std::complex<double> CpbarUChaChiVWmPR(int, int) const =0;
    
                virtual ::std::complex<double> CpbarUChaChiVWmPL(int, int) const =0;
    
                virtual ::std::complex<double> CpbarUFeFehhPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarUFeFehhPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarUFeFvHpmPL(int, int, int) const =0;
    
                virtual double CpbarUFeFvHpmPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarUFeChaSvPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarUFeChaSvPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarUFeFeAhPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarUFeFeAhPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarUFeChiSePL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarUFeChiSePR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarUFeFeVPPR(int, int) const =0;
    
                virtual ::std::complex<double> CpbarUFeFeVPPL(int, int) const =0;
    
                virtual ::std::complex<double> CpbarUFeFeVZPR(int, int) const =0;
    
                virtual ::std::complex<double> CpbarUFeFeVZPL(int, int) const =0;
    
                virtual double CpbarUFeFvVWmPR(int, int) const =0;
    
                virtual double CpbarUFeFvVWmPL(int, int) const =0;
    
                virtual ::std::complex<double> CpbarUFdFdhhPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarUFdFdhhPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarUFdFuHpmPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarUFdFuHpmPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarUFdFdAhPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarUFdFdAhPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarUFdChaSuPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarUFdChaSuPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarUFdChiSdPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarUFdChiSdPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarUFdGluSdPL(int, int) const =0;
    
                virtual ::std::complex<double> CpbarUFdGluSdPR(int, int) const =0;
    
                virtual ::std::complex<double> CpbarUFdFdVGPR(int, int) const =0;
    
                virtual ::std::complex<double> CpbarUFdFdVGPL(int, int) const =0;
    
                virtual ::std::complex<double> CpbarUFdFdVPPR(int, int) const =0;
    
                virtual ::std::complex<double> CpbarUFdFdVPPL(int, int) const =0;
    
                virtual ::std::complex<double> CpbarUFdFdVZPR(int, int) const =0;
    
                virtual ::std::complex<double> CpbarUFdFdVZPL(int, int) const =0;
    
                virtual double CpbarUFdFuVWmPR(int, int) const =0;
    
                virtual ::std::complex<double> CpbarUFdFuVWmPL(int, int) const =0;
    
                virtual ::std::complex<double> CpbarUFuFdconjHpmPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarUFuFdconjHpmPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarUFuFuhhPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarUFuFuhhPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarChabarUFuSdPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarChabarUFuSdPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarUFuFuAhPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarUFuFuAhPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarUFuChiSuPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarUFuChiSuPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarUFuGluSuPL(int, int) const =0;
    
                virtual ::std::complex<double> CpbarUFuGluSuPR(int, int) const =0;
    
                virtual double CpbarUFuFdconjVWmPR(int, int) const =0;
    
                virtual ::std::complex<double> CpbarUFuFdconjVWmPL(int, int) const =0;
    
                virtual ::std::complex<double> CpbarUFuFuVGPR(int, int) const =0;
    
                virtual ::std::complex<double> CpbarUFuFuVGPL(int, int) const =0;
    
                virtual ::std::complex<double> CpbarUFuFuVPPR(int, int) const =0;
    
                virtual ::std::complex<double> CpbarUFuFuVPPL(int, int) const =0;
    
                virtual ::std::complex<double> CpbarUFuFuVZPR(int, int) const =0;
    
                virtual ::std::complex<double> CpbarUFuFuVZPL(int, int) const =0;
    
                virtual ::std::complex<double> CpbarFdGluSdPL(int, int) const =0;
    
                virtual ::std::complex<double> CpbarFdGluSdPR(int, int) const =0;
    
                virtual ::std::complex<double> CpbarFuGluSuPL(int, int) const =0;
    
                virtual ::std::complex<double> CpbarFuGluSuPR(int, int) const =0;
    
                virtual ::std::complex<double> CpGluFdconjSdPL(int, int) const =0;
    
                virtual ::std::complex<double> CpGluFdconjSdPR(int, int) const =0;
    
                virtual ::std::complex<double> CpGluFuconjSuPL(int, int) const =0;
    
                virtual ::std::complex<double> CpGluFuconjSuPR(int, int) const =0;
    
                virtual double CpbarFvFeconjHpmPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarFvFeconjHpmPR(int, int, int) const =0;
    
                virtual double CpbarChabarFvSePL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarChabarFvSePR(int, int, int) const =0;
    
                virtual double CpbarFvChiSvPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarFvChiSvPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarFeFehhPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarFeFehhPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarFeFvHpmPL(int, int, int) const =0;
    
                virtual double CpbarFeFvHpmPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarFeChaSvPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarFeChaSvPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarFeFeAhPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarFeFeAhPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarFeChiSePL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarFeChiSePR(int, int, int) const =0;
    
                virtual double CpbarFeFvVWmPR(int, int) const =0;
    
                virtual ::std::complex<double> CpbarFeFvVWmPL(int, int) const =0;
    
                virtual ::std::complex<double> CpbarFdFdhhPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarFdFdhhPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarFdFuHpmPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarFdFuHpmPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarFdFdAhPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarFdFdAhPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarFdChaSuPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarFdChaSuPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarFdChiSdPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarFdChiSdPR(int, int, int) const =0;
    
                virtual double CpbarFdFuVWmPR(int, int) const =0;
    
                virtual ::std::complex<double> CpbarFdFuVWmPL(int, int) const =0;
    
                virtual ::std::complex<double> CpbarFuFdconjHpmPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarFuFdconjHpmPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarFuFuhhPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarFuFuhhPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarChabarFuSdPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarChabarFuSdPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarFuFuAhPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarFuFuAhPR(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarFuChiSuPL(int, int, int) const =0;
    
                virtual ::std::complex<double> CpbarFuChiSuPR(int, int, int) const =0;
    
                virtual ::std::complex<double> self_energy_Sd_1loop(double, int, int) const =0;
    
                virtual ::std::complex<double> self_energy_Sv_1loop(double, int, int) const =0;
    
                virtual ::std::complex<double> self_energy_Su_1loop(double, int, int) const =0;
    
                virtual ::std::complex<double> self_energy_Se_1loop(double, int, int) const =0;
    
                virtual ::std::complex<double> self_energy_hh_1loop(double, int, int) const =0;
    
                virtual ::std::complex<double> self_energy_Ah_1loop(double, int, int) const =0;
    
                virtual ::std::complex<double> self_energy_Hpm_1loop(double, int, int) const =0;
    
                virtual ::std::complex<double> self_energy_VG_1loop(double) const =0;
    
                virtual ::std::complex<double> self_energy_VP_1loop(double) const =0;
    
                virtual ::std::complex<double> self_energy_VZ_1loop(double) const =0;
    
                virtual ::std::complex<double> self_energy_VWm_1loop(double) const =0;
    
                virtual ::std::complex<double> self_energy_Chi_1loop_1(double, int, int) const =0;
    
                virtual ::std::complex<double> self_energy_Chi_1loop_PR(double, int, int) const =0;
    
                virtual ::std::complex<double> self_energy_Chi_1loop_PL(double, int, int) const =0;
    
                virtual ::std::complex<double> self_energy_Cha_1loop_1(double, int, int) const =0;
    
                virtual ::std::complex<double> self_energy_Cha_1loop_PR(double, int, int) const =0;
    
                virtual ::std::complex<double> self_energy_Cha_1loop_PL(double, int, int) const =0;
    
                virtual ::std::complex<double> self_energy_Fe_1loop_1(double, int, int) const =0;
    
                virtual ::std::complex<double> self_energy_Fe_1loop_PR(double, int, int) const =0;
    
                virtual ::std::complex<double> self_energy_Fe_1loop_PL(double, int, int) const =0;
    
                virtual ::std::complex<double> self_energy_Fd_1loop_1(double, int, int) const =0;
    
                virtual ::std::complex<double> self_energy_Fd_1loop_PR(double, int, int) const =0;
    
                virtual ::std::complex<double> self_energy_Fd_1loop_PL(double, int, int) const =0;
    
                virtual ::std::complex<double> self_energy_Fu_1loop_1(double, int, int) const =0;
    
                virtual ::std::complex<double> self_energy_Fu_1loop_PR(double, int, int) const =0;
    
                virtual ::std::complex<double> self_energy_Fu_1loop_PL(double, int, int) const =0;
    
                virtual ::std::complex<double> self_energy_Glu_1loop_1(double) const =0;
    
                virtual ::std::complex<double> self_energy_Glu_1loop_PR(double) const =0;
    
                virtual ::std::complex<double> self_energy_Glu_1loop_PL(double) const =0;
    
                virtual ::std::complex<double> self_energy_Fv_1loop_1(double, int, int) const =0;
    
                virtual ::std::complex<double> self_energy_Fv_1loop_PR(double, int, int) const =0;
    
                virtual ::std::complex<double> self_energy_Fv_1loop_PL(double, int, int) const =0;
    
                virtual ::std::complex<double> self_energy_Fe_1loop_1_heavy_rotated(double, int, int) const =0;
    
                virtual ::std::complex<double> self_energy_Fe_1loop_PR_heavy_rotated(double, int, int) const =0;
    
                virtual ::std::complex<double> self_energy_Fe_1loop_PL_heavy_rotated(double, int, int) const =0;
    
                virtual ::std::complex<double> self_energy_Fd_1loop_1_heavy_rotated(double, int, int) const =0;
    
                virtual ::std::complex<double> self_energy_Fd_1loop_PR_heavy_rotated(double, int, int) const =0;
    
                virtual ::std::complex<double> self_energy_Fd_1loop_PL_heavy_rotated(double, int, int) const =0;
    
                virtual ::std::complex<double> self_energy_Fu_1loop_1_heavy_rotated(double, int, int) const =0;
    
                virtual ::std::complex<double> self_energy_Fu_1loop_PR_heavy_rotated(double, int, int) const =0;
    
                virtual ::std::complex<double> self_energy_Fu_1loop_PL_heavy_rotated(double, int, int) const =0;
    
                virtual ::std::complex<double> self_energy_Fu_1loop_1_heavy(double, int, int) const =0;
    
                virtual ::std::complex<double> self_energy_Fu_1loop_PR_heavy(double, int, int) const =0;
    
                virtual ::std::complex<double> self_energy_Fu_1loop_PL_heavy(double, int, int) const =0;
    
                virtual ::std::complex<double> tadpole_hh_1loop(int) const =0;
    
                virtual void tadpole_equations(double*) const =0;
    
                virtual void calculate_MSu_2nd_generation(double&, double&, double&) const =0;
    
                virtual void calculate_MSd_2nd_generation(double&, double&, double&) const =0;
    
                virtual void calculate_MSv_2nd_generation(double&, double&, double&) const =0;
    
                virtual void calculate_MSe_2nd_generation(double&, double&, double&) const =0;
    
                virtual void calculate_MSu_3rd_generation(double&, double&, double&) const =0;
    
                virtual void calculate_MSd_3rd_generation(double&, double&, double&) const =0;
    
                virtual void calculate_MSv_3rd_generation(double&, double&, double&) const =0;
    
                virtual void calculate_MSe_3rd_generation(double&, double&, double&) const =0;
    
                virtual void calculate_MVG_pole() =0;
    
                virtual void calculate_MGlu_pole() =0;
    
                virtual void calculate_MFv_pole() =0;
    
                virtual void calculate_MVP_pole() =0;
    
                virtual void calculate_MVZ_pole() =0;
    
                virtual void calculate_MSd_pole() =0;
    
                virtual void calculate_MSv_pole() =0;
    
                virtual void calculate_MSu_pole() =0;
    
                virtual void calculate_MSe_pole() =0;
    
                virtual void calculate_Mhh_pole() =0;
    
                virtual void calculate_MAh_pole() =0;
    
                virtual void calculate_MHpm_pole() =0;
    
                virtual void calculate_MChi_pole() =0;
    
                virtual void calculate_MCha_pole() =0;
    
                virtual void calculate_MFe_pole() =0;
    
                virtual void calculate_MFd_pole() =0;
    
                virtual void calculate_MFu_pole() =0;
    
                virtual void calculate_MVWm_pole() =0;
    
                virtual double calculate_MVWm_pole(double) =0;
    
                virtual double calculate_MVZ_pole(double) =0;
    
                virtual double calculate_MFv_DRbar(double, int) const =0;
    
                virtual double calculate_MFe_DRbar(double, int) const =0;
    
                virtual double calculate_MFu_DRbar(double, int) const =0;
    
                virtual double calculate_MFd_DRbar(double, int) const =0;
    
                virtual double calculate_MVP_DRbar(double) =0;
    
                virtual double calculate_MVZ_DRbar(double) =0;
    
                virtual double calculate_MVWm_DRbar(double) =0;
    
                virtual double v() const =0;
    
                virtual double Betax() const =0;
    
                virtual double Alpha() const =0;
    
                virtual double ThetaW() const =0;
    
            public:
                using flexiblesusy::Abstract_CMSSM_soft_parameters::pointer_assign__BOSS;
                virtual void pointer_assign__BOSS(Abstract_CMSSM_mass_eigenstates*) =0;
                virtual Abstract_CMSSM_mass_eigenstates* pointer_copy__BOSS() =0;
    
            private:
                CMSSM_mass_eigenstates* wptr;
                bool delete_wrapper;
            public:
                CMSSM_mass_eigenstates* get_wptr() { return wptr; }
                void set_wptr(CMSSM_mass_eigenstates* wptr_in) { wptr = wptr_in; }
                bool get_delete_wrapper() { return delete_wrapper; }
                void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
    
            public:
                Abstract_CMSSM_mass_eigenstates()
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_CMSSM_mass_eigenstates(const Abstract_CMSSM_mass_eigenstates& in) : 
                    flexiblesusy::Abstract_Beta_function(in), flexiblesusy::Abstract_CMSSM_susy_parameters(in), flexiblesusy::Abstract_CMSSM_soft_parameters(in)
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_CMSSM_mass_eigenstates& operator=(const Abstract_CMSSM_mass_eigenstates&) { return *this; }
    
                virtual void init_wrapper() =0;
    
                CMSSM_mass_eigenstates* get_init_wptr()
                {
                    init_wrapper();
                    return wptr;
                }
    
                CMSSM_mass_eigenstates& get_init_wref()
                {
                    init_wrapper();
                    return *wptr;
                }
    
                virtual ~Abstract_CMSSM_mass_eigenstates() =0;
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_CMSSM_mass_eigenstates_FlexibleSUSY_CMSSM_2_0_1_h__ */
