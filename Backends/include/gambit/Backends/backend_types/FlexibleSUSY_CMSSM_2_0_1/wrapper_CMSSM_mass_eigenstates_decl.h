#ifndef __wrapper_CMSSM_mass_eigenstates_decl_FlexibleSUSY_CMSSM_2_0_1_h__
#define __wrapper_CMSSM_mass_eigenstates_decl_FlexibleSUSY_CMSSM_2_0_1_h__

#include <cstddef>
#include <string>
#include <ostream>
#include <complex>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_CMSSM_mass_eigenstates.h"
#include "wrapper_CMSSM_soft_parameters_decl.h"
#include "wrapper_CMSSM_input_parameters_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace flexiblesusy
    {
        
        class CMSSM_mass_eigenstates : public CMSSM_soft_parameters
        {
                // Member variables: 
            public:
                // -- Static factory pointers: 
                static Abstract_CMSSM_mass_eigenstates* (*__factory0)(const flexiblesusy::CMSSM_input_parameters&);
                static Abstract_CMSSM_mass_eigenstates* (*__factory1)();
        
                // -- Other member variables: 
            public:
                const int& number_of_ewsb_equations;
        
                // Member functions: 
            public:
                void calculate_DRbar_masses();
        
                void calculate_pole_masses();
        
                void check_pole_masses_for_tachyons();
        
                void clear();
        
                void clear_DRbar_parameters();
        
                void do_calculate_sm_pole_masses(bool arg_1);
        
                bool do_calculate_sm_pole_masses() const;
        
                void do_calculate_bsm_pole_masses(bool arg_1);
        
                bool do_calculate_bsm_pole_masses() const;
        
                void do_force_output(bool arg_1);
        
                bool do_force_output() const;
        
                void reorder_DRbar_masses();
        
                void reorder_pole_masses();
        
                void set_ewsb_iteration_precision(double arg_1);
        
                void set_ewsb_loop_order(int arg_1);
        
                void set_pole_mass_loop_order(int arg_1);
        
                int get_pole_mass_loop_order() const;
        
                double get_ewsb_iteration_precision() const;
        
                double get_ewsb_loop_order() const;
        
                int solve_ewsb_tree_level();
        
                int solve_ewsb_one_loop();
        
                int solve_ewsb();
        
                void calculate_spectrum();
        
                void clear_problems();
        
                ::std::basic_string<char> name() const;
        
                void run_to(double scale, double eps);
        
                void run_to(double scale);
        
                void print(::std::basic_ostream<char>& out) const;
        
                void print() const;
        
                void set_precision(double arg_1);
        
                double get_precision() const;
        
                double get_MVG() const;
        
                double get_MGlu() const;
        
                double get_MFv(int i) const;
        
                double get_MSd(int i) const;
        
                double get_MSv(int i) const;
        
                double get_MSu(int i) const;
        
                double get_MSe(int i) const;
        
                double get_Mhh(int i) const;
        
                double get_MAh(int i) const;
        
                double get_MHpm(int i) const;
        
                double get_MChi(int i) const;
        
                double get_MCha(int i) const;
        
                double get_MFe(int i) const;
        
                double get_MFd(int i) const;
        
                double get_MFu(int i) const;
        
                double get_MVWm() const;
        
                double get_MVP() const;
        
                double get_MVZ() const;
        
                double get_ZD(int i, int k) const;
        
                double get_ZV(int i, int k) const;
        
                double get_ZU(int i, int k) const;
        
                double get_ZE(int i, int k) const;
        
                double get_ZH(int i, int k) const;
        
                double get_ZA(int i, int k) const;
        
                double get_ZP(int i, int k) const;
        
                ::std::complex<double> get_ZN(int i, int k) const;
        
                ::std::complex<double> get_UM(int i, int k) const;
        
                ::std::complex<double> get_UP(int i, int k) const;
        
                ::std::complex<double> get_ZEL(int i, int k) const;
        
                ::std::complex<double> get_ZER(int i, int k) const;
        
                ::std::complex<double> get_ZDL(int i, int k) const;
        
                ::std::complex<double> get_ZDR(int i, int k) const;
        
                ::std::complex<double> get_ZUL(int i, int k) const;
        
                ::std::complex<double> get_ZUR(int i, int k) const;
        
                double get_ZZ(int i, int k) const;
        
                void set_PhaseGlu(::std::complex<double> PhaseGlu_);
        
                ::std::complex<double> get_PhaseGlu() const;
        
                double get_mass_matrix_VG() const;
        
                void calculate_MVG();
        
                double get_mass_matrix_Glu() const;
        
                void calculate_MGlu();
        
                void calculate_MFv();
        
                void calculate_MSd();
        
                void calculate_MSv();
        
                void calculate_MSu();
        
                void calculate_MSe();
        
                void calculate_Mhh();
        
                void calculate_MAh();
        
                void calculate_MHpm();
        
                void calculate_MChi();
        
                void calculate_MCha();
        
                void calculate_MFe();
        
                void calculate_MFd();
        
                void calculate_MFu();
        
                double get_mass_matrix_VWm() const;
        
                void calculate_MVWm();
        
                void calculate_MVPVZ();
        
                double get_ewsb_eq_hh_1() const;
        
                double get_ewsb_eq_hh_2() const;
        
                ::std::complex<double> CpUSdconjUSdVZVZ(int gO1, int gO2) const;
        
                double CpUSdconjUSdconjVWmVWm(int gO1, int gO2) const;
        
                ::std::complex<double> CpAhAhUSdconjUSd(int gI1, int gI2, int gO1, int gO2) const;
        
                ::std::complex<double> CphhhhUSdconjUSd(int gI1, int gI2, int gO1, int gO2) const;
        
                ::std::complex<double> CpHpmUSdconjHpmconjUSd(int gI1, int gO1, int gI2, int gO2) const;
        
                ::std::complex<double> CpUSdSvconjUSdconjSv(int gO1, int gI1, int gO2, int gI2) const;
        
                ::std::complex<double> CpChaFuconjUSdPR(int gI2, int gI1, int gO2) const;
        
                ::std::complex<double> CpChaFuconjUSdPL(int gI2, int gI1, int gO1) const;
        
                ::std::complex<double> CpChiFdconjUSdPR(int gI2, int gI1, int gO2) const;
        
                ::std::complex<double> CpChiFdconjUSdPL(int gI2, int gI1, int gO1) const;
        
                ::std::complex<double> CpUSdconjUSdconjSdSd(int gO1, int gO2, int gI1, int gI2) const;
        
                ::std::complex<double> CpUSdconjUSdconjSuSu(int gO1, int gO2, int gI1, int gI2) const;
        
                ::std::complex<double> CpUSdSeconjUSdconjSe(int gO1, int gI1, int gO2, int gI2) const;
        
                ::std::complex<double> CpAhSdconjUSd(int gI2, int gI1, int gO2) const;
        
                ::std::complex<double> CphhSdconjUSd(int gI2, int gI1, int gO2) const;
        
                ::std::complex<double> CpHpmSuconjUSd(int gI2, int gI1, int gO2) const;
        
                ::std::complex<double> CpGluFdconjUSdPR(int gI2, int gO2) const;
        
                ::std::complex<double> CpGluFdconjUSdPL(int gI2, int gO1) const;
        
                ::std::complex<double> CpSdconjUSdVG(int gI2, int gO2) const;
        
                ::std::complex<double> CpSdconjUSdVP(int gI2, int gO2) const;
        
                ::std::complex<double> CpSdconjUSdVZ(int gI2, int gO2) const;
        
                ::std::complex<double> CpSuconjUSdVWm(int gI2, int gO2) const;
        
                ::std::complex<double> CpUSvconjUSvVZVZ(int gO1, int gO2) const;
        
                double CpUSvconjUSvconjVWmVWm(int gO1, int gO2) const;
        
                ::std::complex<double> CpAhAhUSvconjUSv(int gI1, int gI2, int gO1, int gO2) const;
        
                ::std::complex<double> CphhhhUSvconjUSv(int gI1, int gI2, int gO1, int gO2) const;
        
                ::std::complex<double> CpHpmUSvconjHpmconjUSv(int gI1, int gO1, int gI2, int gO2) const;
        
                ::std::complex<double> CpbarChaFeconjUSvPR(int gI1, int gI2, int gO2) const;
        
                ::std::complex<double> CpbarChaFeconjUSvPL(int gI1, int gI2, int gO1) const;
        
                ::std::complex<double> CpSeconjHpmconjUSv(int gI2, int gI1, int gO2) const;
        
                ::std::complex<double> CpSvUSvconjSvconjUSv(int gI1, int gO1, int gI2, int gO2) const;
        
                ::std::complex<double> CphhSvconjUSv(int gI2, int gI1, int gO2) const;
        
                double CpChiFvconjUSvPR(int arg_1, int arg_2, int arg_3) const;
        
                ::std::complex<double> CpChiFvconjUSvPL(int gI2, int gI1, int gO1) const;
        
                ::std::complex<double> CpSdUSvconjSdconjUSv(int gI1, int gO1, int gI2, int gO2) const;
        
                ::std::complex<double> CpSeUSvconjSeconjUSv(int gI1, int gO1, int gI2, int gO2) const;
        
                ::std::complex<double> CpSuUSvconjSuconjUSv(int gI1, int gO1, int gI2, int gO2) const;
        
                ::std::complex<double> CpSvconjUSvVZ(int gI2, int gO2) const;
        
                ::std::complex<double> CpSeconjUSvconjVWm(int gI2, int gO2) const;
        
                ::std::complex<double> CpUSuconjUSuVZVZ(int gO1, int gO2) const;
        
                double CpUSuconjUSuconjVWmVWm(int gO1, int gO2) const;
        
                ::std::complex<double> CpAhAhUSuconjUSu(int gI1, int gI2, int gO1, int gO2) const;
        
                ::std::complex<double> CphhhhUSuconjUSu(int gI1, int gI2, int gO1, int gO2) const;
        
                ::std::complex<double> CpHpmUSuconjHpmconjUSu(int gI1, int gO1, int gI2, int gO2) const;
        
                ::std::complex<double> CpbarChaFdconjUSuPR(int gI1, int gI2, int gO2) const;
        
                ::std::complex<double> CpbarChaFdconjUSuPL(int gI1, int gI2, int gO1) const;
        
                ::std::complex<double> CpSdconjHpmconjUSu(int gI2, int gI1, int gO2) const;
        
                ::std::complex<double> CpUSuSvconjUSuconjSv(int gO1, int gI1, int gO2, int gI2) const;
        
                ::std::complex<double> CpChiFuconjUSuPR(int gI2, int gI1, int gO2) const;
        
                ::std::complex<double> CpChiFuconjUSuPL(int gI2, int gI1, int gO1) const;
        
                ::std::complex<double> CpSeUSuconjSeconjUSu(int gI1, int gO1, int gI2, int gO2) const;
        
                ::std::complex<double> CpUSuconjUSuconjSdSd(int gO1, int gO2, int gI1, int gI2) const;
        
                ::std::complex<double> CpUSuconjUSuconjSuSu(int gO1, int gO2, int gI1, int gI2) const;
        
                ::std::complex<double> CpAhSuconjUSu(int gI2, int gI1, int gO2) const;
        
                ::std::complex<double> CphhSuconjUSu(int gI2, int gI1, int gO2) const;
        
                ::std::complex<double> CpGluFuconjUSuPR(int gI2, int gO2) const;
        
                ::std::complex<double> CpGluFuconjUSuPL(int gI2, int gO1) const;
        
                ::std::complex<double> CpSdconjUSuconjVWm(int gI2, int gO2) const;
        
                ::std::complex<double> CpSuconjUSuVG(int gI2, int gO2) const;
        
                ::std::complex<double> CpSuconjUSuVP(int gI2, int gO2) const;
        
                ::std::complex<double> CpSuconjUSuVZ(int gI2, int gO2) const;
        
                ::std::complex<double> CpUSeconjUSeVZVZ(int gO1, int gO2) const;
        
                double CpUSeconjUSeconjVWmVWm(int gO1, int gO2) const;
        
                ::std::complex<double> CpAhAhUSeconjUSe(int gI1, int gI2, int gO1, int gO2) const;
        
                ::std::complex<double> CphhhhUSeconjUSe(int gI1, int gI2, int gO1, int gO2) const;
        
                ::std::complex<double> CpHpmUSeconjHpmconjUSe(int gI1, int gO1, int gI2, int gO2) const;
        
                ::std::complex<double> CpUSeSvconjUSeconjSv(int gO1, int gI1, int gO2, int gI2) const;
        
                ::std::complex<double> CpHpmSvconjUSe(int gI2, int gI1, int gO2) const;
        
                double CpChaFvconjUSePR(int arg_1, int arg_2, int arg_3) const;
        
                ::std::complex<double> CpChaFvconjUSePL(int gI2, int gI1, int gO1) const;
        
                ::std::complex<double> CpChiFeconjUSePR(int gI2, int gI1, int gO2) const;
        
                ::std::complex<double> CpChiFeconjUSePL(int gI2, int gI1, int gO1) const;
        
                ::std::complex<double> CpSdUSeconjSdconjUSe(int gI1, int gO1, int gI2, int gO2) const;
        
                ::std::complex<double> CpSeUSeconjSeconjUSe(int gI1, int gO1, int gI2, int gO2) const;
        
                ::std::complex<double> CpUSeSuconjUSeconjSu(int gO1, int gI1, int gO2, int gI2) const;
        
                ::std::complex<double> CpAhSeconjUSe(int gI2, int gI1, int gO2) const;
        
                ::std::complex<double> CphhSeconjUSe(int gI2, int gI1, int gO2) const;
        
                ::std::complex<double> CpSvconjUSeVWm(int gI2, int gO2) const;
        
                ::std::complex<double> CpSeconjUSeVP(int gI2, int gO2) const;
        
                ::std::complex<double> CpSeconjUSeVZ(int gI2, int gO2) const;
        
                ::std::complex<double> CpbargWmgWmUhh(int gO1) const;
        
                ::std::complex<double> CpbargWmCgWmCUhh(int gO1) const;
        
                ::std::complex<double> CpbargZgZUhh(int gO1) const;
        
                ::std::complex<double> CpUhhVZVZ(int gO2) const;
        
                ::std::complex<double> CpUhhconjVWmVWm(int gO2) const;
        
                ::std::complex<double> CpUhhUhhVZVZ(int gO1, int gO2) const;
        
                ::std::complex<double> CpUhhUhhconjVWmVWm(int gO1, int gO2) const;
        
                ::std::complex<double> CpAhAhUhhUhh(int gI1, int gI2, int gO1, int gO2) const;
        
                ::std::complex<double> CphhhhUhhUhh(int gI1, int gI2, int gO1, int gO2) const;
        
                ::std::complex<double> CpUhhUhhHpmconjHpm(int gO1, int gO2, int gI1, int gI2) const;
        
                ::std::complex<double> CpAhAhUhh(int gI1, int gI2, int gO2) const;
        
                ::std::complex<double> CphhhhUhh(int gI1, int gI2, int gO2) const;
        
                ::std::complex<double> CpUhhHpmconjHpm(int gO2, int gI2, int gI1) const;
        
                ::std::complex<double> CpbarChaChaUhhPR(int gI1, int gI2, int gO2) const;
        
                ::std::complex<double> CpbarChaChaUhhPL(int gI1, int gI2, int gO1) const;
        
                ::std::complex<double> CpUhhUhhSvconjSv(int gO1, int gO2, int gI1, int gI2) const;
        
                ::std::complex<double> CpUhhSvconjSv(int gO2, int gI2, int gI1) const;
        
                ::std::complex<double> CpbarFdFdUhhPR(int gI1, int gI2, int gO2) const;
        
                ::std::complex<double> CpbarFdFdUhhPL(int gI1, int gI2, int gO1) const;
        
                ::std::complex<double> CpbarFeFeUhhPR(int gI1, int gI2, int gO2) const;
        
                ::std::complex<double> CpbarFeFeUhhPL(int gI1, int gI2, int gO1) const;
        
                ::std::complex<double> CpbarFuFuUhhPR(int gI1, int gI2, int gO2) const;
        
                ::std::complex<double> CpbarFuFuUhhPL(int gI1, int gI2, int gO1) const;
        
                ::std::complex<double> CpChiChiUhhPR(int gI1, int gI2, int gO2) const;
        
                ::std::complex<double> CpChiChiUhhPL(int gI1, int gI2, int gO1) const;
        
                ::std::complex<double> CpUhhUhhSdconjSd(int gO1, int gO2, int gI1, int gI2) const;
        
                ::std::complex<double> CpUhhUhhSeconjSe(int gO1, int gO2, int gI1, int gI2) const;
        
                ::std::complex<double> CpUhhUhhSuconjSu(int gO1, int gO2, int gI1, int gI2) const;
        
                ::std::complex<double> CpUhhSdconjSd(int gO2, int gI2, int gI1) const;
        
                ::std::complex<double> CpUhhSeconjSe(int gO2, int gI2, int gI1) const;
        
                ::std::complex<double> CpUhhSuconjSu(int gO2, int gI2, int gI1) const;
        
                ::std::complex<double> CpAhUhhVZ(int gI2, int gO2) const;
        
                ::std::complex<double> CpUhhHpmconjVWm(int gO2, int gI2) const;
        
                ::std::complex<double> CpbargWmgWmUAh(int gO1) const;
        
                ::std::complex<double> CpbargWmCgWmCUAh(int gO1) const;
        
                ::std::complex<double> CpUAhUAhVZVZ(int gO1, int gO2) const;
        
                ::std::complex<double> CpUAhUAhconjVWmVWm(int gO1, int gO2) const;
        
                ::std::complex<double> CpAhAhUAhUAh(int gI1, int gI2, int gO1, int gO2) const;
        
                ::std::complex<double> CpUAhUAhhhhh(int gO1, int gO2, int gI1, int gI2) const;
        
                ::std::complex<double> CpUAhUAhHpmconjHpm(int gO1, int gO2, int gI1, int gI2) const;
        
                ::std::complex<double> CpAhUAhhh(int gI2, int gO2, int gI1) const;
        
                ::std::complex<double> CpUAhHpmconjHpm(int gO2, int gI2, int gI1) const;
        
                ::std::complex<double> CpbarChaChaUAhPR(int gI1, int gI2, int gO2) const;
        
                ::std::complex<double> CpbarChaChaUAhPL(int gI1, int gI2, int gO1) const;
        
                ::std::complex<double> CpUAhUAhSvconjSv(int gO1, int gO2, int gI1, int gI2) const;
        
                ::std::complex<double> CpbarFdFdUAhPR(int gI1, int gI2, int gO2) const;
        
                ::std::complex<double> CpbarFdFdUAhPL(int gI1, int gI2, int gO1) const;
        
                ::std::complex<double> CpbarFeFeUAhPR(int gI1, int gI2, int gO2) const;
        
                ::std::complex<double> CpbarFeFeUAhPL(int gI1, int gI2, int gO1) const;
        
                ::std::complex<double> CpbarFuFuUAhPR(int gI1, int gI2, int gO2) const;
        
                ::std::complex<double> CpbarFuFuUAhPL(int gI1, int gI2, int gO1) const;
        
                ::std::complex<double> CpChiChiUAhPR(int gI1, int gI2, int gO2) const;
        
                ::std::complex<double> CpChiChiUAhPL(int gI1, int gI2, int gO1) const;
        
                ::std::complex<double> CpUAhUAhSdconjSd(int gO1, int gO2, int gI1, int gI2) const;
        
                ::std::complex<double> CpUAhUAhSeconjSe(int gO1, int gO2, int gI1, int gI2) const;
        
                ::std::complex<double> CpUAhUAhSuconjSu(int gO1, int gO2, int gI1, int gI2) const;
        
                ::std::complex<double> CpUAhSdconjSd(int gO2, int gI2, int gI1) const;
        
                ::std::complex<double> CpUAhSeconjSe(int gO2, int gI2, int gI1) const;
        
                ::std::complex<double> CpUAhSuconjSu(int gO2, int gI2, int gI1) const;
        
                ::std::complex<double> CpUAhhhVZ(int gO2, int gI2) const;
        
                ::std::complex<double> CpUAhHpmconjVWm(int gO2, int gI2) const;
        
                ::std::complex<double> CpbargWmgZUHpm(int gO2) const;
        
                ::std::complex<double> CpbargZgWmconjUHpm(int gO1) const;
        
                ::std::complex<double> CpbargWmCgZconjUHpm(int gO1) const;
        
                ::std::complex<double> CpbargZgWmCUHpm(int gO2) const;
        
                ::std::complex<double> CpconjUHpmVPVWm(int gO2) const;
        
                ::std::complex<double> CpconjUHpmVWmVZ(int gO2) const;
        
                ::std::complex<double> CpUHpmconjUHpmVZVZ(int gO1, int gO2) const;
        
                ::std::complex<double> CpUHpmconjUHpmconjVWmVWm(int gO1, int gO2) const;
        
                ::std::complex<double> CpAhAhUHpmconjUHpm(int gI1, int gI2, int gO1, int gO2) const;
        
                ::std::complex<double> CphhhhUHpmconjUHpm(int gI1, int gI2, int gO1, int gO2) const;
        
                ::std::complex<double> CpHpmUHpmconjHpmconjUHpm(int gI1, int gO1, int gI2, int gO2) const;
        
                ::std::complex<double> CpAhHpmconjUHpm(int gI2, int gI1, int gO2) const;
        
                ::std::complex<double> CphhHpmconjUHpm(int gI2, int gI1, int gO2) const;
        
                ::std::complex<double> CpUHpmSvconjUHpmconjSv(int gO1, int gI1, int gO2, int gI2) const;
        
                ::std::complex<double> CpbarFuFdconjUHpmPR(int gI1, int gI2, int gO2) const;
        
                ::std::complex<double> CpbarFuFdconjUHpmPL(int gI1, int gI2, int gO1) const;
        
                ::std::complex<double> CpbarFvFeconjUHpmPR(int gI1, int gI2, int gO2) const;
        
                double CpbarFvFeconjUHpmPL(int arg_1, int arg_2, int arg_3) const;
        
                ::std::complex<double> CpSeconjUHpmconjSv(int gI2, int gO2, int gI1) const;
        
                ::std::complex<double> CpChiChaconjUHpmPR(int gI1, int gI2, int gO2) const;
        
                ::std::complex<double> CpChiChaconjUHpmPL(int gI1, int gI2, int gO1) const;
        
                ::std::complex<double> CpUHpmSdconjUHpmconjSd(int gO1, int gI1, int gO2, int gI2) const;
        
                ::std::complex<double> CpUHpmSeconjUHpmconjSe(int gO1, int gI1, int gO2, int gI2) const;
        
                ::std::complex<double> CpUHpmSuconjUHpmconjSu(int gO1, int gI1, int gO2, int gI2) const;
        
                ::std::complex<double> CpSdconjUHpmconjSu(int gI2, int gO2, int gI1) const;
        
                ::std::complex<double> CpAhconjUHpmVWm(int gI2, int gO2) const;
        
                ::std::complex<double> CphhconjUHpmVWm(int gI2, int gO2) const;
        
                ::std::complex<double> CpHpmconjUHpmVP(int gI2, int gO2) const;
        
                ::std::complex<double> CpHpmconjUHpmVZ(int gI2, int gO2) const;
        
                ::std::complex<double> CpVGVGVG() const;
        
                ::std::complex<double> CpbargGgGVG() const;
        
                double CpbarFdFdVGPL(int gI1, int gI2) const;
        
                double CpbarFdFdVGPR(int gI1, int gI2) const;
        
                double CpbarFuFuVGPL(int gI1, int gI2) const;
        
                double CpbarFuFuVGPR(int gI1, int gI2) const;
        
                double CpSdconjSdVGVG(int gI1, int gI2) const;
        
                double CpSuconjSuVGVG(int gI1, int gI2) const;
        
                double CpSdconjSdVG(int gI2, int gI1) const;
        
                double CpSuconjSuVG(int gI2, int gI1) const;
        
                ::std::complex<double> CpGluGluVGPL() const;
        
                ::std::complex<double> CpGluGluVGPR() const;
        
                double CpVGVGVGVG1() const;
        
                double CpVGVGVGVG2() const;
        
                double CpVGVGVGVG3() const;
        
                double CpbargWmgWmVP() const;
        
                double CpbargWmCgWmCVP() const;
        
                double CpconjVWmVPVWm() const;
        
                ::std::complex<double> CpHpmconjHpmVPVP(int gI1, int gI2) const;
        
                double CpHpmconjHpmVP(int gI2, int gI1) const;
        
                ::std::complex<double> CpbarChaChaVPPL(int gI1, int gI2) const;
        
                ::std::complex<double> CpbarChaChaVPPR(int gI1, int gI2) const;
        
                double CpbarFdFdVPPL(int gI1, int gI2) const;
        
                double CpbarFdFdVPPR(int gI1, int gI2) const;
        
                double CpbarFeFeVPPL(int gI1, int gI2) const;
        
                double CpbarFeFeVPPR(int gI1, int gI2) const;
        
                double CpbarFuFuVPPL(int gI1, int gI2) const;
        
                double CpbarFuFuVPPR(int gI1, int gI2) const;
        
                ::std::complex<double> CpSdconjSdVPVP(int gI1, int gI2) const;
        
                ::std::complex<double> CpSeconjSeVPVP(int gI1, int gI2) const;
        
                ::std::complex<double> CpSuconjSuVPVP(int gI1, int gI2) const;
        
                ::std::complex<double> CpSdconjSdVP(int gI2, int gI1) const;
        
                ::std::complex<double> CpSeconjSeVP(int gI2, int gI1) const;
        
                ::std::complex<double> CpSuconjSuVP(int gI2, int gI1) const;
        
                ::std::complex<double> CpHpmconjVWmVP(int gI2) const;
        
                double CpconjVWmVPVPVWm1() const;
        
                double CpconjVWmVPVPVWm2() const;
        
                double CpconjVWmVPVPVWm3() const;
        
                double CpbargWmgWmVZ() const;
        
                double CpbargWmCgWmCVZ() const;
        
                double CpconjVWmVWmVZ() const;
        
                ::std::complex<double> CpAhAhVZVZ(int gI1, int gI2) const;
        
                ::std::complex<double> CphhhhVZVZ(int gI1, int gI2) const;
        
                ::std::complex<double> CpHpmconjHpmVZVZ(int gI1, int gI2) const;
        
                ::std::complex<double> CpAhhhVZ(int gI2, int gI1) const;
        
                double CpHpmconjHpmVZ(int gI2, int gI1) const;
        
                ::std::complex<double> CpbarChaChaVZPL(int gI1, int gI2) const;
        
                ::std::complex<double> CpbarChaChaVZPR(int gI1, int gI2) const;
        
                ::std::complex<double> CpSvconjSvVZVZ(int gI1, int gI2) const;
        
                double CpSvconjSvVZ(int gI2, int gI1) const;
        
                double CpbarFdFdVZPL(int gI1, int gI2) const;
        
                double CpbarFdFdVZPR(int gI1, int gI2) const;
        
                double CpbarFeFeVZPL(int gI1, int gI2) const;
        
                double CpbarFeFeVZPR(int gI1, int gI2) const;
        
                double CpbarFuFuVZPL(int gI1, int gI2) const;
        
                double CpbarFuFuVZPR(int gI1, int gI2) const;
        
                double CpbarFvFvVZPL(int gI1, int gI2) const;
        
                double CpbarFvFvVZPR(int arg_1, int arg_2) const;
        
                ::std::complex<double> CpChiChiVZPL(int gI1, int gI2) const;
        
                ::std::complex<double> CpChiChiVZPR(int gI1, int gI2) const;
        
                ::std::complex<double> CpSdconjSdVZVZ(int gI1, int gI2) const;
        
                ::std::complex<double> CpSeconjSeVZVZ(int gI1, int gI2) const;
        
                ::std::complex<double> CpSuconjSuVZVZ(int gI1, int gI2) const;
        
                ::std::complex<double> CpSdconjSdVZ(int gI2, int gI1) const;
        
                ::std::complex<double> CpSeconjSeVZ(int gI2, int gI1) const;
        
                ::std::complex<double> CpSuconjSuVZ(int gI2, int gI1) const;
        
                ::std::complex<double> CphhVZVZ(int gI2) const;
        
                ::std::complex<double> CpHpmconjVWmVZ(int gI2) const;
        
                double CpconjVWmVWmVZVZ1() const;
        
                double CpconjVWmVWmVZVZ2() const;
        
                double CpconjVWmVWmVZVZ3() const;
        
                double CpbargPgWmconjVWm() const;
        
                double CpbargWmCgPconjVWm() const;
        
                double CpbargWmCgZconjVWm() const;
        
                double CpbargZgWmconjVWm() const;
        
                ::std::complex<double> CpAhAhconjVWmVWm(int gI1, int gI2) const;
        
                ::std::complex<double> CphhhhconjVWmVWm(int gI1, int gI2) const;
        
                ::std::complex<double> CpHpmconjHpmconjVWmVWm(int gI1, int gI2) const;
        
                ::std::complex<double> CpAhHpmconjVWm(int gI2, int gI1) const;
        
                ::std::complex<double> CphhHpmconjVWm(int gI2, int gI1) const;
        
                double CpSvconjSvconjVWmVWm(int gI1, int gI2) const;
        
                ::std::complex<double> CpbarFuFdconjVWmPL(int gI1, int gI2) const;
        
                double CpbarFuFdconjVWmPR(int arg_1, int arg_2) const;
        
                ::std::complex<double> CpbarFvFeconjVWmPL(int gI1, int gI2) const;
        
                double CpbarFvFeconjVWmPR(int arg_1, int arg_2) const;
        
                ::std::complex<double> CpSeconjSvconjVWm(int gI2, int gI1) const;
        
                ::std::complex<double> CpChiChaconjVWmPL(int gI1, int gI2) const;
        
                ::std::complex<double> CpChiChaconjVWmPR(int gI1, int gI2) const;
        
                ::std::complex<double> CpSdconjSdconjVWmVWm(int gI1, int gI2) const;
        
                ::std::complex<double> CpSeconjSeconjVWmVWm(int gI1, int gI2) const;
        
                ::std::complex<double> CpSuconjSuconjVWmVWm(int gI1, int gI2) const;
        
                ::std::complex<double> CpSdconjSuconjVWm(int gI2, int gI1) const;
        
                ::std::complex<double> CphhconjVWmVWm(int gI2) const;
        
                double CpconjVWmconjVWmVWmVWm1() const;
        
                double CpconjVWmconjVWmVWmVWm2() const;
        
                double CpconjVWmconjVWmVWmVWm3() const;
        
                ::std::complex<double> CpbarChaUChiHpmPL(int gI1, int gO2, int gI2) const;
        
                ::std::complex<double> CpbarChaUChiHpmPR(int gI1, int gO1, int gI2) const;
        
                ::std::complex<double> CpUChiChaconjHpmPL(int gO2, int gI2, int gI1) const;
        
                ::std::complex<double> CpUChiChaconjHpmPR(int gO1, int gI2, int gI1) const;
        
                ::std::complex<double> CpChiUChihhPL(int gI2, int gO2, int gI1) const;
        
                ::std::complex<double> CpChiUChihhPR(int gI2, int gO1, int gI1) const;
        
                ::std::complex<double> CpbarChaUChiVWmPL(int gI1, int gO2) const;
        
                ::std::complex<double> CpbarChaUChiVWmPR(int gI1, int gO1) const;
        
                double CpbarFvUChiSvPL(int arg_1, int arg_2, int arg_3) const;
        
                ::std::complex<double> CpbarFvUChiSvPR(int gI1, int gO1, int gI2) const;
        
                ::std::complex<double> CpUChiFvconjSvPL(int gO2, int gI2, int gI1) const;
        
                double CpUChiFvconjSvPR(int arg_1, int arg_2, int arg_3) const;
        
                ::std::complex<double> CpbarFdUChiSdPL(int gI1, int gO2, int gI2) const;
        
                ::std::complex<double> CpbarFdUChiSdPR(int gI1, int gO1, int gI2) const;
        
                ::std::complex<double> CpbarFeUChiSePL(int gI1, int gO2, int gI2) const;
        
                ::std::complex<double> CpbarFeUChiSePR(int gI1, int gO1, int gI2) const;
        
                ::std::complex<double> CpbarFuUChiSuPL(int gI1, int gO2, int gI2) const;
        
                ::std::complex<double> CpbarFuUChiSuPR(int gI1, int gO1, int gI2) const;
        
                ::std::complex<double> CpChiUChiAhPL(int gI1, int gO2, int gI2) const;
        
                ::std::complex<double> CpChiUChiAhPR(int gI1, int gO1, int gI2) const;
        
                ::std::complex<double> CpUChiFdconjSdPL(int gO2, int gI2, int gI1) const;
        
                ::std::complex<double> CpUChiFdconjSdPR(int gO1, int gI2, int gI1) const;
        
                ::std::complex<double> CpUChiFeconjSePL(int gO2, int gI2, int gI1) const;
        
                ::std::complex<double> CpUChiFeconjSePR(int gO1, int gI2, int gI1) const;
        
                ::std::complex<double> CpUChiFuconjSuPL(int gO2, int gI2, int gI1) const;
        
                ::std::complex<double> CpUChiFuconjSuPR(int gO1, int gI2, int gI1) const;
        
                ::std::complex<double> CpUChiChaconjVWmPR(int gO2, int gI2) const;
        
                ::std::complex<double> CpUChiChaconjVWmPL(int gO1, int gI2) const;
        
                ::std::complex<double> CpChiUChiVZPL(int gI2, int gO2) const;
        
                ::std::complex<double> CpChiUChiVZPR(int gI2, int gO1) const;
        
                ::std::complex<double> CpbarUChaChaAhPL(int gO2, int gI1, int gI2) const;
        
                ::std::complex<double> CpbarUChaChaAhPR(int gO1, int gI1, int gI2) const;
        
                ::std::complex<double> CpbarUChaChahhPL(int gO2, int gI2, int gI1) const;
        
                ::std::complex<double> CpbarUChaChahhPR(int gO1, int gI2, int gI1) const;
        
                ::std::complex<double> CpbarUChaChiHpmPL(int gO2, int gI2, int gI1) const;
        
                ::std::complex<double> CpbarUChaChiHpmPR(int gO1, int gI2, int gI1) const;
        
                ::std::complex<double> CpbarUChaFeconjSvPL(int gO2, int gI2, int gI1) const;
        
                ::std::complex<double> CpbarUChaFeconjSvPR(int gO1, int gI2, int gI1) const;
        
                ::std::complex<double> CpbarUChabarFuSdPL(int gO2, int gI1, int gI2) const;
        
                ::std::complex<double> CpbarUChabarFuSdPR(int gO1, int gI1, int gI2) const;
        
                double CpbarUChabarFvSePL(int arg_1, int arg_2, int arg_3) const;
        
                ::std::complex<double> CpbarUChabarFvSePR(int gO1, int gI1, int gI2) const;
        
                ::std::complex<double> CpbarUChaFdconjSuPL(int gO2, int gI2, int gI1) const;
        
                ::std::complex<double> CpbarUChaFdconjSuPR(int gO1, int gI2, int gI1) const;
        
                ::std::complex<double> CpbarUChaChaVPPR(int gO2, int gI2) const;
        
                ::std::complex<double> CpbarUChaChaVPPL(int gO1, int gI2) const;
        
                ::std::complex<double> CpbarUChaChaVZPR(int gO2, int gI2) const;
        
                ::std::complex<double> CpbarUChaChaVZPL(int gO1, int gI2) const;
        
                ::std::complex<double> CpbarUChaChiVWmPR(int gO2, int gI2) const;
        
                ::std::complex<double> CpbarUChaChiVWmPL(int gO1, int gI2) const;
        
                ::std::complex<double> CpbarUFeFehhPL(int gO2, int gI2, int gI1) const;
        
                ::std::complex<double> CpbarUFeFehhPR(int gO1, int gI2, int gI1) const;
        
                ::std::complex<double> CpbarUFeFvHpmPL(int gO2, int gI2, int gI1) const;
        
                double CpbarUFeFvHpmPR(int arg_1, int arg_2, int arg_3) const;
        
                ::std::complex<double> CpbarUFeChaSvPL(int gO2, int gI2, int gI1) const;
        
                ::std::complex<double> CpbarUFeChaSvPR(int gO1, int gI2, int gI1) const;
        
                ::std::complex<double> CpbarUFeFeAhPL(int gO2, int gI1, int gI2) const;
        
                ::std::complex<double> CpbarUFeFeAhPR(int gO1, int gI1, int gI2) const;
        
                ::std::complex<double> CpbarUFeChiSePL(int gO2, int gI2, int gI1) const;
        
                ::std::complex<double> CpbarUFeChiSePR(int gO1, int gI2, int gI1) const;
        
                ::std::complex<double> CpbarUFeFeVPPR(int gO2, int gI2) const;
        
                ::std::complex<double> CpbarUFeFeVPPL(int gO1, int gI2) const;
        
                ::std::complex<double> CpbarUFeFeVZPR(int gO2, int gI2) const;
        
                ::std::complex<double> CpbarUFeFeVZPL(int gO1, int gI2) const;
        
                double CpbarUFeFvVWmPR(int arg_1, int arg_2) const;
        
                double CpbarUFeFvVWmPL(int gO1, int gI2) const;
        
                ::std::complex<double> CpbarUFdFdhhPL(int gO2, int gI2, int gI1) const;
        
                ::std::complex<double> CpbarUFdFdhhPR(int gO1, int gI2, int gI1) const;
        
                ::std::complex<double> CpbarUFdFuHpmPL(int gO2, int gI2, int gI1) const;
        
                ::std::complex<double> CpbarUFdFuHpmPR(int gO1, int gI2, int gI1) const;
        
                ::std::complex<double> CpbarUFdFdAhPL(int gO2, int gI1, int gI2) const;
        
                ::std::complex<double> CpbarUFdFdAhPR(int gO1, int gI1, int gI2) const;
        
                ::std::complex<double> CpbarUFdChaSuPL(int gO2, int gI2, int gI1) const;
        
                ::std::complex<double> CpbarUFdChaSuPR(int gO1, int gI2, int gI1) const;
        
                ::std::complex<double> CpbarUFdChiSdPL(int gO2, int gI2, int gI1) const;
        
                ::std::complex<double> CpbarUFdChiSdPR(int gO1, int gI2, int gI1) const;
        
                ::std::complex<double> CpbarUFdGluSdPL(int gO2, int gI1) const;
        
                ::std::complex<double> CpbarUFdGluSdPR(int gO1, int gI1) const;
        
                ::std::complex<double> CpbarUFdFdVGPR(int gO2, int gI2) const;
        
                ::std::complex<double> CpbarUFdFdVGPL(int gO1, int gI2) const;
        
                ::std::complex<double> CpbarUFdFdVPPR(int gO2, int gI2) const;
        
                ::std::complex<double> CpbarUFdFdVPPL(int gO1, int gI2) const;
        
                ::std::complex<double> CpbarUFdFdVZPR(int gO2, int gI2) const;
        
                ::std::complex<double> CpbarUFdFdVZPL(int gO1, int gI2) const;
        
                double CpbarUFdFuVWmPR(int arg_1, int arg_2) const;
        
                ::std::complex<double> CpbarUFdFuVWmPL(int gO1, int gI2) const;
        
                ::std::complex<double> CpbarUFuFdconjHpmPL(int gO2, int gI2, int gI1) const;
        
                ::std::complex<double> CpbarUFuFdconjHpmPR(int gO1, int gI2, int gI1) const;
        
                ::std::complex<double> CpbarUFuFuhhPL(int gO2, int gI2, int gI1) const;
        
                ::std::complex<double> CpbarUFuFuhhPR(int gO1, int gI2, int gI1) const;
        
                ::std::complex<double> CpbarChabarUFuSdPL(int gI1, int gO2, int gI2) const;
        
                ::std::complex<double> CpbarChabarUFuSdPR(int gI1, int gO1, int gI2) const;
        
                ::std::complex<double> CpbarUFuFuAhPL(int gO2, int gI1, int gI2) const;
        
                ::std::complex<double> CpbarUFuFuAhPR(int gO1, int gI1, int gI2) const;
        
                ::std::complex<double> CpbarUFuChiSuPL(int gO2, int gI2, int gI1) const;
        
                ::std::complex<double> CpbarUFuChiSuPR(int gO1, int gI2, int gI1) const;
        
                ::std::complex<double> CpbarUFuGluSuPL(int gO2, int gI1) const;
        
                ::std::complex<double> CpbarUFuGluSuPR(int gO1, int gI1) const;
        
                double CpbarUFuFdconjVWmPR(int arg_1, int arg_2) const;
        
                ::std::complex<double> CpbarUFuFdconjVWmPL(int gO1, int gI2) const;
        
                ::std::complex<double> CpbarUFuFuVGPR(int gO2, int gI2) const;
        
                ::std::complex<double> CpbarUFuFuVGPL(int gO1, int gI2) const;
        
                ::std::complex<double> CpbarUFuFuVPPR(int gO2, int gI2) const;
        
                ::std::complex<double> CpbarUFuFuVPPL(int gO1, int gI2) const;
        
                ::std::complex<double> CpbarUFuFuVZPR(int gO2, int gI2) const;
        
                ::std::complex<double> CpbarUFuFuVZPL(int gO1, int gI2) const;
        
                ::std::complex<double> CpbarFdGluSdPL(int gI1, int gI2) const;
        
                ::std::complex<double> CpbarFdGluSdPR(int gI1, int gI2) const;
        
                ::std::complex<double> CpbarFuGluSuPL(int gI1, int gI2) const;
        
                ::std::complex<double> CpbarFuGluSuPR(int gI1, int gI2) const;
        
                ::std::complex<double> CpGluFdconjSdPL(int gI2, int gI1) const;
        
                ::std::complex<double> CpGluFdconjSdPR(int gI2, int gI1) const;
        
                ::std::complex<double> CpGluFuconjSuPL(int gI2, int gI1) const;
        
                ::std::complex<double> CpGluFuconjSuPR(int gI2, int gI1) const;
        
                double CpbarFvFeconjHpmPL(int arg_1, int arg_2, int arg_3) const;
        
                ::std::complex<double> CpbarFvFeconjHpmPR(int gO1, int gI2, int gI1) const;
        
                double CpbarChabarFvSePL(int arg_1, int arg_2, int arg_3) const;
        
                ::std::complex<double> CpbarChabarFvSePR(int gI1, int gO1, int gI2) const;
        
                double CpbarFvChiSvPL(int arg_1, int arg_2, int arg_3) const;
        
                ::std::complex<double> CpbarFvChiSvPR(int gO1, int gI2, int gI1) const;
        
                ::std::complex<double> CpbarFeFehhPL(int gO2, int gI2, int gI1) const;
        
                ::std::complex<double> CpbarFeFehhPR(int gO1, int gI2, int gI1) const;
        
                ::std::complex<double> CpbarFeFvHpmPL(int gO2, int gI2, int gI1) const;
        
                double CpbarFeFvHpmPR(int arg_1, int arg_2, int arg_3) const;
        
                ::std::complex<double> CpbarFeChaSvPL(int gO2, int gI2, int gI1) const;
        
                ::std::complex<double> CpbarFeChaSvPR(int gO1, int gI2, int gI1) const;
        
                ::std::complex<double> CpbarFeFeAhPL(int gO2, int gI1, int gI2) const;
        
                ::std::complex<double> CpbarFeFeAhPR(int gO1, int gI1, int gI2) const;
        
                ::std::complex<double> CpbarFeChiSePL(int gO2, int gI2, int gI1) const;
        
                ::std::complex<double> CpbarFeChiSePR(int gO1, int gI2, int gI1) const;
        
                double CpbarFeFvVWmPR(int arg_1, int arg_2) const;
        
                ::std::complex<double> CpbarFeFvVWmPL(int gO1, int gI2) const;
        
                ::std::complex<double> CpbarFdFdhhPL(int gO2, int gI2, int gI1) const;
        
                ::std::complex<double> CpbarFdFdhhPR(int gO1, int gI2, int gI1) const;
        
                ::std::complex<double> CpbarFdFuHpmPL(int gO2, int gI2, int gI1) const;
        
                ::std::complex<double> CpbarFdFuHpmPR(int gO1, int gI2, int gI1) const;
        
                ::std::complex<double> CpbarFdFdAhPL(int gO2, int gI1, int gI2) const;
        
                ::std::complex<double> CpbarFdFdAhPR(int gO1, int gI1, int gI2) const;
        
                ::std::complex<double> CpbarFdChaSuPL(int gO2, int gI2, int gI1) const;
        
                ::std::complex<double> CpbarFdChaSuPR(int gO1, int gI2, int gI1) const;
        
                ::std::complex<double> CpbarFdChiSdPL(int gO2, int gI2, int gI1) const;
        
                ::std::complex<double> CpbarFdChiSdPR(int gO1, int gI2, int gI1) const;
        
                double CpbarFdFuVWmPR(int arg_1, int arg_2) const;
        
                ::std::complex<double> CpbarFdFuVWmPL(int gO1, int gI2) const;
        
                ::std::complex<double> CpbarFuFdconjHpmPL(int gO2, int gI2, int gI1) const;
        
                ::std::complex<double> CpbarFuFdconjHpmPR(int gO1, int gI2, int gI1) const;
        
                ::std::complex<double> CpbarFuFuhhPL(int gO2, int gI2, int gI1) const;
        
                ::std::complex<double> CpbarFuFuhhPR(int gO1, int gI2, int gI1) const;
        
                ::std::complex<double> CpbarChabarFuSdPL(int gI1, int gO2, int gI2) const;
        
                ::std::complex<double> CpbarChabarFuSdPR(int gI1, int gO1, int gI2) const;
        
                ::std::complex<double> CpbarFuFuAhPL(int gO2, int gI1, int gI2) const;
        
                ::std::complex<double> CpbarFuFuAhPR(int gO1, int gI1, int gI2) const;
        
                ::std::complex<double> CpbarFuChiSuPL(int gO2, int gI2, int gI1) const;
        
                ::std::complex<double> CpbarFuChiSuPR(int gO1, int gI2, int gI1) const;
        
                ::std::complex<double> self_energy_Sd_1loop(double p, int gO1, int gO2) const;
        
                ::std::complex<double> self_energy_Sv_1loop(double p, int gO1, int gO2) const;
        
                ::std::complex<double> self_energy_Su_1loop(double p, int gO1, int gO2) const;
        
                ::std::complex<double> self_energy_Se_1loop(double p, int gO1, int gO2) const;
        
                ::std::complex<double> self_energy_hh_1loop(double p, int gO1, int gO2) const;
        
                ::std::complex<double> self_energy_Ah_1loop(double p, int gO1, int gO2) const;
        
                ::std::complex<double> self_energy_Hpm_1loop(double p, int gO1, int gO2) const;
        
                ::std::complex<double> self_energy_VG_1loop(double p) const;
        
                ::std::complex<double> self_energy_VP_1loop(double p) const;
        
                ::std::complex<double> self_energy_VZ_1loop(double p) const;
        
                ::std::complex<double> self_energy_VWm_1loop(double p) const;
        
                ::std::complex<double> self_energy_Chi_1loop_1(double p, int gO1, int gO2) const;
        
                ::std::complex<double> self_energy_Chi_1loop_PR(double p, int gO1, int gO2) const;
        
                ::std::complex<double> self_energy_Chi_1loop_PL(double p, int gO1, int gO2) const;
        
                ::std::complex<double> self_energy_Cha_1loop_1(double p, int gO1, int gO2) const;
        
                ::std::complex<double> self_energy_Cha_1loop_PR(double p, int gO1, int gO2) const;
        
                ::std::complex<double> self_energy_Cha_1loop_PL(double p, int gO1, int gO2) const;
        
                ::std::complex<double> self_energy_Fe_1loop_1(double p, int gO1, int gO2) const;
        
                ::std::complex<double> self_energy_Fe_1loop_PR(double p, int gO1, int gO2) const;
        
                ::std::complex<double> self_energy_Fe_1loop_PL(double p, int gO1, int gO2) const;
        
                ::std::complex<double> self_energy_Fd_1loop_1(double p, int gO1, int gO2) const;
        
                ::std::complex<double> self_energy_Fd_1loop_PR(double p, int gO1, int gO2) const;
        
                ::std::complex<double> self_energy_Fd_1loop_PL(double p, int gO1, int gO2) const;
        
                ::std::complex<double> self_energy_Fu_1loop_1(double p, int gO1, int gO2) const;
        
                ::std::complex<double> self_energy_Fu_1loop_PR(double p, int gO1, int gO2) const;
        
                ::std::complex<double> self_energy_Fu_1loop_PL(double p, int gO1, int gO2) const;
        
                ::std::complex<double> self_energy_Glu_1loop_1(double p) const;
        
                ::std::complex<double> self_energy_Glu_1loop_PR(double p) const;
        
                ::std::complex<double> self_energy_Glu_1loop_PL(double p) const;
        
                ::std::complex<double> self_energy_Fv_1loop_1(double p, int gO1, int gO2) const;
        
                ::std::complex<double> self_energy_Fv_1loop_PR(double p, int gO1, int gO2) const;
        
                ::std::complex<double> self_energy_Fv_1loop_PL(double p, int gO1, int gO2) const;
        
                ::std::complex<double> self_energy_Fe_1loop_1_heavy_rotated(double p, int gO1, int gO2) const;
        
                ::std::complex<double> self_energy_Fe_1loop_PR_heavy_rotated(double p, int gO1, int gO2) const;
        
                ::std::complex<double> self_energy_Fe_1loop_PL_heavy_rotated(double p, int gO1, int gO2) const;
        
                ::std::complex<double> self_energy_Fd_1loop_1_heavy_rotated(double p, int gO1, int gO2) const;
        
                ::std::complex<double> self_energy_Fd_1loop_PR_heavy_rotated(double p, int gO1, int gO2) const;
        
                ::std::complex<double> self_energy_Fd_1loop_PL_heavy_rotated(double p, int gO1, int gO2) const;
        
                ::std::complex<double> self_energy_Fu_1loop_1_heavy_rotated(double p, int gO1, int gO2) const;
        
                ::std::complex<double> self_energy_Fu_1loop_PR_heavy_rotated(double p, int gO1, int gO2) const;
        
                ::std::complex<double> self_energy_Fu_1loop_PL_heavy_rotated(double p, int gO1, int gO2) const;
        
                ::std::complex<double> self_energy_Fu_1loop_1_heavy(double p, int gO1, int gO2) const;
        
                ::std::complex<double> self_energy_Fu_1loop_PR_heavy(double p, int gO1, int gO2) const;
        
                ::std::complex<double> self_energy_Fu_1loop_PL_heavy(double p, int gO1, int gO2) const;
        
                ::std::complex<double> tadpole_hh_1loop(int gO1) const;
        
                void tadpole_equations(double* arg_1) const;
        
                void calculate_MSu_2nd_generation(double& arg_1, double& arg_2, double& arg_3) const;
        
                void calculate_MSd_2nd_generation(double& arg_1, double& arg_2, double& arg_3) const;
        
                void calculate_MSv_2nd_generation(double& arg_1, double& arg_2, double& arg_3) const;
        
                void calculate_MSe_2nd_generation(double& arg_1, double& arg_2, double& arg_3) const;
        
                void calculate_MSu_3rd_generation(double& arg_1, double& arg_2, double& arg_3) const;
        
                void calculate_MSd_3rd_generation(double& arg_1, double& arg_2, double& arg_3) const;
        
                void calculate_MSv_3rd_generation(double& arg_1, double& arg_2, double& arg_3) const;
        
                void calculate_MSe_3rd_generation(double& arg_1, double& arg_2, double& arg_3) const;
        
                void calculate_MVG_pole();
        
                void calculate_MGlu_pole();
        
                void calculate_MFv_pole();
        
                void calculate_MVP_pole();
        
                void calculate_MVZ_pole();
        
                void calculate_MSd_pole();
        
                void calculate_MSv_pole();
        
                void calculate_MSu_pole();
        
                void calculate_MSe_pole();
        
                void calculate_Mhh_pole();
        
                void calculate_MAh_pole();
        
                void calculate_MHpm_pole();
        
                void calculate_MChi_pole();
        
                void calculate_MCha_pole();
        
                void calculate_MFe_pole();
        
                void calculate_MFd_pole();
        
                void calculate_MFu_pole();
        
                void calculate_MVWm_pole();
        
                double calculate_MVWm_pole(double arg_1);
        
                double calculate_MVZ_pole(double arg_1);
        
                double calculate_MFv_DRbar(double arg_1, int arg_2) const;
        
                double calculate_MFe_DRbar(double arg_1, int arg_2) const;
        
                double calculate_MFu_DRbar(double arg_1, int arg_2) const;
        
                double calculate_MFd_DRbar(double arg_1, int arg_2) const;
        
                double calculate_MVP_DRbar(double arg_1);
        
                double calculate_MVZ_DRbar(double arg_1);
        
                double calculate_MVWm_DRbar(double arg_1);
        
                double v() const;
        
                double Betax() const;
        
                double Alpha() const;
        
                double ThetaW() const;
        
        
                // Wrappers for original constructors: 
            public:
                CMSSM_mass_eigenstates(const flexiblesusy::CMSSM_input_parameters& input_);
                CMSSM_mass_eigenstates();
        
                // Special pointer-based constructor: 
                CMSSM_mass_eigenstates(Abstract_CMSSM_mass_eigenstates* in);
        
                // Copy constructor: 
                CMSSM_mass_eigenstates(const CMSSM_mass_eigenstates& in);
        
                // Assignment operator: 
                CMSSM_mass_eigenstates& operator=(const CMSSM_mass_eigenstates& in);
        
                // Destructor: 
                ~CMSSM_mass_eigenstates();
        
                // Returns correctly casted pointer to Abstract class: 
                Abstract_CMSSM_mass_eigenstates* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_CMSSM_mass_eigenstates_decl_FlexibleSUSY_CMSSM_2_0_1_h__ */
