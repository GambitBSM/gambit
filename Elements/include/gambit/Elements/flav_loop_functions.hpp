//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Loop functions for flavour violating decays of charged leptons (from hep-ph/9403398)
///  And for RK from 1706.07570
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Tomas Gonzalo
///          (t.e.gonzalo@fys.uio.no)
///  \date 2017 Aug, 2018 Feb
///
///  \author Cristian Sierra 
///          (cristian.sierra@monash.edu)
///  \date 2020 Oct
///
///  \author Douglas Jacob
///          (douglas.jacob@monash.edu)
///  \date 2020 Nov
///
///  *********************************************

#ifndef __flav_loop_functions_hpp
#define __flav_loop_functions_hpp
#include <complex>
#include <gsl/gsl_integration.h>
#include <gsl/gsl_sf_dilog.h>
#include <gsl/gsl_sf_result.h>

namespace Gambit
{

    //Yukawas vertices for THDM
    namespace Vertices_THDM
    {
      complex<double> yff_h(int f, int fp, double mf, Eigen::Matrix3cd xi_f, double vev, double cosab);
    
      complex<double> yff_H(int f, int fp, double mf, Eigen::Matrix3cd xi_f, double vev, double cosab);
    }

    //Auxiliary function to flip the sign and choose the scalar field in the fermion-fermion-Higgs vertex
    namespace Yukawas
    {
      complex<double> yff_phi(int f, int i, int j, int phi, double mf, Eigen::Matrix3cd xi_f, Eigen::Matrix3cd VCKM, double vev, double cosab);
    }

    //2-loop functions for BR(l>l' gamma) for the gTHDM
    namespace TwoLoopFunctions
    {
      complex<double> TwoLoopFH(complex<double> x);
      complex<double> TwoLoopFA(complex<double> x);
      complex<double> TwoLoopGW(complex<double> x);

      // Two Loop Functions for Muon g-2 for gTHDM
      double TwoLoopPhi(double m1, double m2, double m3)

      complex<double> TwoLoopfgammaphi(double Nc, double Qf, double alph, double mmu, double mf, double mphi, double mW, double mZ)
      complex<double> TwoLoopfZbosonphi(double Nc, double Qf, double alph, double mmu, double mf, double mphi, double mW, double mZ)
      complex<double> TwoLoopfgammaA(double Nc, double Qf, double alph, double mmu, double mf, double mphi, double mW, double mZ)
      complex<double> TwoLoopfZbosonA(double Nc, double Qf, double alph, double mmu, double mf, double mphi, double mW, double mZ)

      complex<double> TwoLoopfC(int f, double Nc, double Qu, double Qd, double alph, double mmu, double mf, double mphi, double mW)

      double TwoLoopf1(double x, void * params)
      double TwoLoopf2(double x, void * params)
      double TwoLoopf3(double x, void * params)
      double TwoLoopf4(double x, void * params)

      double TwoLoopF(double w, gsl_function fun)

      struct G_params {double wa; double wb; int n;};

      double TwoLoopg(double x, void * params)

      double TwoLoopG(double wa, double wb, int n)
    }

    // Loop functions for one loop diagrams
    namespace OneLoopFunctions
    {
      double OneLoopB(const double x);

      double OneLoopC(const double x);

      double OneLoopE(const double x);

      double OneLoopF(const double x);
    }

    // Amplitudes for BR(l>l' gamma) for the gTHDM
    namespace Amplitudes
    {
      //1-loop AL and AR amplitudes
      complex<double> A_loop1L(int f, int l, int li, int lp, int phi, vector<double> mnu, vector<double> ml, double mphi, Eigen::Matrix3cd xi_L, Eigen::Matrix3cd VCKM, double vev, double cosab);
      complex<double> A_loop1R(int f, int l, int li, int lp, int phi, vector<double> mnu, vector<double> ml, double mphi, Eigen::Matrix3cd xi_L, Eigen::Matrix3cd VCKM, double vev, double cosab);

      //2-loop fermionic contribution
      //AL
      complex<double> A_loop2fL(int lf, int l, int lp, int phi, double ml, double mlf, double mphi, Eigen::Matrix3cd xi_L, Eigen::Matrix3cd xi_U, Eigen::Matrix3cd xi_D, Eigen::Matrix3cd VCKM, double vev, double cosab);
      //AR
      complex<double> A_loop2fR(int lf, int l, int lp, int phi, double ml, double mlf, double mphi, Eigen::Matrix3cd xi_L, Eigen::Matrix3cd xi_U, Eigen::Matrix3cd xi_D, Eigen::Matrix3cd VCKM, double vev, double cosab);

      //2-loop bosonic contribution
      //AL
      complex<double> A_loop2bL(int f, int l, int lp, int phi, double ml, double mphi, Eigen::Matrix3cd xi_L, Eigen::Matrix3cd VCKM, double vev, double cosab, double mW, double mZ);
      //AR
      complex<double> A_loop2bR(int f, int l, int lp, int phi, double ml, double mphi, Eigen::Matrix3cd xi_L, Eigen::Matrix3cd VCKM, double vev, double cosab, double mW, double mZ);
    }

    // Two Loop Contributions for gTHDM from 1607.06292
    namespace TwoLoopContributions
    {
      double gm2mu_loop2f(int f, int fi, int phi, double mmu, double mf, double mphi, Eigen::Matrix3cd xi_L, Eigen::Matrix3cd xi_D, Eigen::Matrix3cd xi_U, Eigen::Matrix3cd VCKM, double vev, double cosab, double
mW, double mZ, double alph)

      double gm2mu_barrzeephigammaf(int f, int fi, int phi, double mmu, double mf, double mphi, Eigen::Matrix3cd xi_L, Eigen::Matrix3cd xi_D, Eigen::Matrix3cd xi_U, Eigen::Matrix3cd VCKM, double vev, double cosa
b, double mW, double mZ, double alph)
      double gm2mu_barrzeephigammaC(int phi, double mmu, double mHp, double mphi, Eigen::Matrix3cd xi_L, Eigen::Matrix3cd VCKM, double vev, double cosab, double alph)
      double gm2mu_barrzeephigammaW(int phi, double mmu, double mW, double mphi, Eigen::Matrix3cd xi_L, Eigen::Matrix3cd VCKM, double vev, double cosab, double alph)

      double gm2mu_barrzeeCHiggsWBosontb(double mmu, double mt, double mb, double mHp, double Qt, double Qb, Eigen::Matrix3cd xi_L, Eigen::Matrix3cd xi_D, Eigen::Matrix3cd xi_U, Eigen::Matrix3cd VCKM, double vev
, double cosab, double mW, double mZ, double alph)
      double gm2mu_barrzeeCHiggsWBosonC(int phi, double mmu, double mphi, double mHp, Eigen::Matrix3cd xi_L, Eigen::Matrix3cd xi_D, Eigen::Matrix3cd xi_U, Eigen::Matrix3cd VCKM, double vev, double cosab, double
mW, double mZ, double alph)
      double gm2mu_barrzeeCHiggsWBosonW(int phi, double mmu, double mphi, double mHp, Eigen::Matrix3cd xi_L, Eigen::Matrix3cd xi_D, Eigen::Matrix3cd xi_U, Eigen::Matrix3cd VCKM, double vev, double cosab, double
mW, double mZ, double alph)
    }
    
    // Loop functions for LFV diagrams
    namespace LoopFunctions
    {
      double G1(const double x);
      double G1(const double a, const double b, const double c);

      double MFVV(const double a, const double b);

      double B1(const double a, const double b, const double Q);
      double B0(const double a, const double b, const double Q);

      double C0(const double a, const double b, const double c);
      double C00(const double a, const double b, const double c, const double Q);
      
      // Finite combination of loop functions that appears in VZw10
      double B02C00C0(const double a, const double b, const double c, const double Q);
      double D0(const double a, const double b, const double c, const double d);
      double D27(const double a, const double b, const double c, const double d);
      double IC0D0(const double a, const double b, const double c, const double d);
    //}

    // Loop function for RK
    //namespace LoopFunctions
    //{
      double E(const double x, const double y);
    }

    // Vertices for LFV diagrams
    namespace Vertices
    {
      // Fermion-vector vertices
      complex<double> VpL(int i, int j, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U);
      double EL(int i,int j, SMInputs sminputs);
      double ER(int i, int j, SMInputs sminputs);
      complex<double> VL(int i, int j, SMInputs sminputs);
      complex<double> VR(int i, int j, SMInputs sminputs);
      complex<double> DL(int i, int j, SMInputs sminputs);
      complex<double> DR(int i, int j, SMInputs sminputs);
      complex<double> UL(int i, int j, SMInputs sminputs);
      complex<double> UR(int i, int j, SMInputs sminputs);
      complex<double> VuL(int i, int j, SMInputs sminputs);

      // Vector vertices
      double Fw(SMInputs sminputs);
      double Zww(SMInputs sminputs);

      // Scalar vertices
      double HL(int i, int j, SMInputs sminputs);
      double HR(int i, int j, SMInputs sminputs);
      double HdL(int i, int j, SMInputs sminputs);
      double HdR(int i, int j, SMInputs sminputs);
      double HuL(int i, int j, SMInputs sminputs);
      double HuR(int i, int j, SMInputs sminputs);
    }

    // Penguin contributions
    namespace Penguins
    {
      // Fotonic penguins
      complex<double> A1R(int alpha, int beta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> mnu);
      complex<double> A2L(int alpha, int beta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu);
      complex<double> A2R(int alpha, int beta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu);

      // Z penguins
      complex<double> VZw2w4LL(int alpha, int beta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu);
      complex<double> VZw2w4LR(int alpha, int beta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu);
      complex<double> VZw2w4RR(int alpha, int beta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu);
      complex<double> VZw2w4RL(int alpha, int beta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu);

      complex<double> VZw8LL(int alpha, int beta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> mnu);
      complex<double> VZw8LR(int alpha, int beta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> mnu);
      complex<double> VZw10LL(int alpha, int beta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> mnu);
      complex<double> VZw10LR(int alpha, int beta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> mnu);

      // Sum over Z penguins
      complex<double> VZsumLL(int alpha, int beta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu);
      complex<double> VZsumLR(int alpha, int beta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu);
      complex<double> VZsumRL(int alpha, int beta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu);
      complex<double> VZsumRR(int alpha, int beta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu);

      // Scalar penguins
      complex<double> Shw2w4LL(int alpha, int beta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu);
      complex<double> Shw2w4LR(int alpha, int beta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu);
      complex<double> Shw2w4RR(int alpha, int beta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu);
      complex<double> Shw2w4RL(int alpha, int beta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu);

      // Sum over scalar penguins
      complex<double> ShsumLL(int alpha, int beta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu);
      complex<double> ShsumLR(int alpha, int beta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu);
      complex<double> ShsumRL(int alpha, int beta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu);
      complex<double> ShsumRR(int alpha, int beta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu);

    }

    // Box contributions
    namespace Boxes
    {
      complex<double> Vw4lLL(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> mnu);
      complex<double> Vw8lLL(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> mnu);
      complex<double> Vw4lpLL(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> mnu);
      complex<double> Vw8lpLL(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> mnu);
      complex<double> Vw4dLL(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> mnu);
      complex<double> Vw4uLL(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> mnu);

      // Sum over boxes
      complex<double> VsumlLL(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> mnu);
      complex<double> VsumdLL(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> mnu);
      complex<double> VsumuLL(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> mnu);

    } // Diagrams

    // Form factors for LFV diagrams
    namespace FormFactors
    {
      complex<double> K1R(int alpha, int beta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> mnu);
      complex<double> K2L(int alpha, int beta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu);
      complex<double> K2R(int alpha, int beta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu);

      complex<double> AVLL(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu);
      complex<double> AVLR(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu);
      complex<double> AVRL(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu);
      complex<double> AVRR(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu);
      complex<double> ASLL(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu, double mh);
      complex<double> ASLR(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu, double mh);
      complex<double> ASRL(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu, double mh);
      complex<double> ASRR(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu, double mh);

      complex<double> BVLL(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu);
      complex<double> BVLR(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu);
      complex<double> BVRL(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu);
      complex<double> BVRR(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu);
      complex<double> BSLL(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu, double mh);
      complex<double> BSLR(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu, double mh);
      complex<double> BSRL(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu, double mh);
      complex<double> BSRR(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu, double mh);

      complex<double> CVLL(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu);
      complex<double> CVLR(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu);
      complex<double> CVRL(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu);
      complex<double> CVRR(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu);
      complex<double> CSLL(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu, double mh);
      complex<double> CSLR(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu, double mh);
      complex<double> CSRL(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu, double mh);
      complex<double> CSRR(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu, double mh);

    } // Form Factors
}

#endif //#defined __flav_loop_functions_hpp__
