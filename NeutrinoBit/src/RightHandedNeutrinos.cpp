//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Module function definitions for NeutrinoBit 
///  exclusive for right-handed neutrinos
///
///  *********************************************
/// 
///  Authors
/// 
///  \author Suraj Krishnamurthy
///          (S.Krishnamurthy@uva.nl) 
///  \date 2017 February
///
///  \author Tomas Gonzalo
///          (t.e.gonzalo@fys.uio.no)
///  \date 2017 Oct
///  \date 2018
///  \date 2019
///
///  \author Marcin Chrzaszcz
///          (mchrzasz@cern.ch)
///  \date 2018
///
///  \author Julia Harz
///          (jharz@lpthe.jussieu.fr)
///  \date 2018 May
///
///  *********************************************

#include <cmath>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/Utils/numerical_constants.hpp"
#include <unsupported/Eigen/MatrixFunctions>
#include "gambit/Utils/statistics.hpp"
#include "gambit/NeutrinoBit/NeutrinoBit_rollcall.hpp"
#include "gambit/NeutrinoBit/NeutrinoInterpolator.hpp"

//#define NEUTRINOBIT_DEBUG

using namespace Eigen;

namespace Gambit
{
  namespace NeutrinoBit
  {
    // Decay widths of RHNs, for BBN (N -> pi0 nu)
    // All formulae for Gamma come from [arXiv:0705:1729], except where mentioned.
    void Gamma_RHN2pi0nu(std::vector<double>& result)
    {
      using namespace Pipes::Gamma_RHN2pi0nu;
      SMInputs sminputs = *Dep::SMINPUTS;
      static double G_F_sq = pow(sminputs.GF, 2);
      static double m_pi_0 = meson_masses.pi0;
      static double f_pi_sq = 0.0169;  // GeV^2
      std::vector<double> gamma(3), M(3);
      M[0] = *Param["M_1"];
      M[1] = *Param["M_2"];
      M[2] = *Param["M_3"];
      Matrix3d Usq = Dep::SeesawI_Theta->cwiseAbs2(); // |\Theta_{ij}|^2

      for (int i=0; i<3; i++)
      {
        gamma[i] = 0;
        if (M[i] > m_pi_0)
        {
          for (int j=0; j<3; j++)
          {
            gamma[i] += ( (Usq(j,i)*G_F_sq*f_pi_sq*pow(M[i],3))/(32*pi) ) * pow((1 - pow(m_pi_0,2)/pow(M[i],2)),2);
          }
        }
      }
      result = gamma;
    }

    // Decay widths of RHNs, for BBN (N -> pi+ l-)
    void Gamma_RHN2piplusl(std::vector<double>& result)
    {
      using namespace Pipes::Gamma_RHN2piplusl;
      SMInputs sminputs = *Dep::SMINPUTS;
      static double G_F_sq = pow(sminputs.GF, 2);
      static double m_pi_plus = meson_masses.pi_plus;
      static double f_pi_sq = 0.0169;  // GeV^2
      // Take from the model parameters (Wolfenstein) PDG value: 0.97434
      static double Vud = 1.0 - 0.5*pow(*Param["CKM_lambda"],2);
      std::vector<double> m_lep(3), gamma(3), M(3);
      // Since we scan the SLHA2 model, we take masses from it
      m_lep[0] = *Param["mE"];
      m_lep[1] = *Param["mMu"];
      m_lep[2] = *Param["mTau"];
      M[0] = *Param["M_1"];
      M[1] = *Param["M_2"];
      M[2] = *Param["M_3"];
      Matrix3d Usq = Dep::SeesawI_Theta->cwiseAbs2(); // |\Theta_{ij}|^2

      for (int i=0; i<3; i++)
      {
        gamma[i] = 0;
        for (int j=0; j<3; j++)
        {
          if (M[i] > (m_pi_plus+m_lep[j]))
          {
            gamma[i] += ( (Usq(j,i)*G_F_sq*pow(Vud,2)*f_pi_sq*pow(M[i],3))/(16*pi) ) * ( pow((1 - pow(m_lep[j],2)/pow(M[i],2)),2) - ( (pow(m_pi_plus,2)/pow(M[i],2))*(1 + pow(m_lep[j],2)/pow(M[i],2)) ) ) * sqrt( (1 - pow(m_pi_plus-m_lep[j],2)/pow(M[i],2))*(1 - pow(m_pi_plus+m_lep[j],2)/pow(M[i],2)) );
          }
        }
      }
      result = gamma;
    }

    // Decay widths of RHNs, for BBN (N -> K+ l-)
    void Gamma_RHN2Kplusl(std::vector<double>& result)
    {
      using namespace Pipes::Gamma_RHN2Kplusl;
      SMInputs sminputs = *Dep::SMINPUTS;
      static double G_F_sq = pow(sminputs.GF, 2);
      static double m_K_plus = meson_masses.kaon_plus;
      static double f_K_sq = 0.02553604;  // GeV^2
      // Take from the model parameters (Wolfenstein) PDG value: 0.22506
      static double Vus = *Param["CKM_lambda"];
      std::vector<double> m_lep(3), gamma(3), M(3);
       // Since we scan the SLHA2 model, we take masses from it
      m_lep[0] = *Param["mE"];
      m_lep[1] = *Param["mMu"];
      m_lep[2] = *Param["mTau"];
      M[0] = *Param["M_1"];
      M[1] = *Param["M_2"];
      M[2] = *Param["M_3"];
      Matrix3d Usq = Dep::SeesawI_Theta->cwiseAbs2(); // |\Theta_{ij}|^2

      for (int i=0; i<3; i++)
      {
        gamma[i] = 0;
        for (int j=0; j<3; j++)
        {
          if (M[i] > (m_K_plus+m_lep[j]))
          {
            gamma[i] += ( (Usq(j,i)*G_F_sq*pow(Vus,2)*f_K_sq*pow(M[i],3))/(16*pi) ) * ( pow((1 - pow(m_lep[j],2)/pow(M[i],2)),2) - ( (pow(m_K_plus,2)/pow(M[i],2))*(1 + pow(m_lep[j],2)/pow(M[i],2)) ) ) * sqrt( (1 - pow(m_K_plus-m_lep[j],2)/pow(M[i],2))*(1 - pow(m_K_plus+m_lep[j],2)/pow(M[i],2)) );
          }
        }
      }
      result = gamma;
    }

    // Decay widths of RHNs, for BBN (N -> D+ l-)
    void Gamma_RHN2Dplusl(std::vector<double>& result)
    {
      using namespace Pipes::Gamma_RHN2Dplusl;
      SMInputs sminputs = *Dep::SMINPUTS;
      static double G_F_sq = pow(sminputs.GF, 2);
      static double m_D_plus = meson_masses.D_plus;
      static double f_D_sq = 0.04955076;  // GeV^2
      // Take from the model parameters (Wolfenstein) PDG value: 0.22492
      static double Vcd = -*Param["CKM_lambda"];
      std::vector<double> m_lep(3), gamma(3), M(3);
      // Since we scan the SLHA2 model, we take masses from it
      m_lep[0] = *Param["mE"];
      m_lep[1] = *Param["mMu"];
      m_lep[2] = *Param["mTau"];
      M[0] = *Param["M_1"];
      M[1] = *Param["M_2"];
      M[2] = *Param["M_3"];
      Matrix3d Usq = Dep::SeesawI_Theta->cwiseAbs2(); // |\Theta_{ij}|^2

      for (int i=0; i<3; i++)
      {
        gamma[i] = 0;
        for (int j=0; j<3; j++)
        {
          if (M[i] > (m_D_plus+m_lep[j]))
          {
            gamma[i] += ( (Usq(j,i)*G_F_sq*pow(Vcd,2)*f_D_sq*pow(M[i],3))/(16*pi) ) * ( pow((1 - pow(m_lep[j],2)/pow(M[i],2)),2) - ( (pow(m_D_plus,2)/pow(M[i],2))*(1 + pow(m_lep[j],2)/pow(M[i],2)) ) ) * sqrt( (1 - pow(m_D_plus-m_lep[j],2)/pow(M[i],2))*(1 - pow(m_D_plus+m_lep[j],2)/pow(M[i],2)) );
          }
        }
      }
      result = gamma;
    }

    // Decay widths of RHNs, for BBN (N -> Ds+ l-)
    void Gamma_RHN2Dsl(std::vector<double>& result)
    {
      using namespace Pipes::Gamma_RHN2Dsl;
      SMInputs sminputs = *Dep::SMINPUTS;
      static double G_F_sq = pow(sminputs.GF, 2);
      static double m_D_s = meson_masses.D_s;
      static double f_Ds_sq = 0.07845601;  // GeV^2
      // Take from the model parameters (Wolfenstein) PDG value: 0.97351
      static double Vcs = 1 - 0.5*pow(*Param["CKM_lambda"],2);
      std::vector<double> m_lep(3), gamma(3), M(3);
      // Since we scan the SLHA2 model, we take masses from it
      m_lep[0] = *Param["mE"];
      m_lep[1] = *Param["mMu"];
      m_lep[2] = *Param["mTau"];
      M[0] = *Param["M_1"];
      M[1] = *Param["M_2"];
      M[2] = *Param["M_3"];
      Matrix3d Usq = Dep::SeesawI_Theta->cwiseAbs2(); // |\Theta_{ij}|^2

      for (int i=0; i<3; i++)
      {
        gamma[i] = 0;
        for (int j=0; j<3; j++)
        {
          if (M[i] > (m_D_s+m_lep[j]))
          {
            gamma[i] += ( (Usq(j,i)*G_F_sq*pow(Vcs,2)*f_Ds_sq*pow(M[i],3))/(16*pi) ) * ( pow((1 - pow(m_lep[j],2)/pow(M[i],2)),2) - ( (pow(m_D_s,2)/pow(M[i],2))*(1 + pow(m_lep[j],2)/pow(M[i],2)) ) ) * sqrt( (1 - pow(m_D_s-m_lep[j],2)/pow(M[i],2))*(1 - pow(m_D_s+m_lep[j],2)/pow(M[i],2)) );
          }
        }
      }
      result = gamma;
    }

    // Decay widths of RHNs, for BBN (N -> B+ l-)
    void Gamma_RHN2Bplusl(std::vector<double>& result)
    {
      using namespace Pipes::Gamma_RHN2Bplusl;
      SMInputs sminputs = *Dep::SMINPUTS;
      static double G_F_sq = pow(sminputs.GF, 2);
      static double m_B_plus = meson_masses.B_plus;
      static double f_B_sq = 0.0361;  // GeV^2
      // Take from the model parameters (Wolfenstein) PDG value: 0.00357 (absolute value)
      static double Vub = *Param["CKM_A"]*pow(*Param["CKM_lambda"],3)*sqrt(pow(*Param["CKM_rhobar"],2) + pow(*Param["CKM_etabar"],2));
      std::vector<double> m_lep(3), gamma(3), M(3);
      // Since we scan the SLHA2 model, we take masses from it
      m_lep[0] = *Param["mE"];
      m_lep[1] = *Param["mMu"];
      m_lep[2] = *Param["mTau"];
      M[0] = *Param["M_1"];
      M[1] = *Param["M_2"];
      M[2] = *Param["M_3"];
      Matrix3d Usq = Dep::SeesawI_Theta->cwiseAbs2(); // |\Theta_{ij}|^2

      for (int i=0; i<3; i++)
      {
        gamma[i] = 0;
        for (int j=0; j<3; j++)
        {
          if (M[i] > (m_B_plus+m_lep[j]))
          {
            gamma[i] += ( (Usq(j,i)*G_F_sq*pow(Vub,2)*f_B_sq*pow(M[i],3))/(16*pi) ) * ( pow((1 - pow(m_lep[j],2)/pow(M[i],2)),2) - ( (pow(m_B_plus,2)/pow(M[i],2))*(1 + pow(m_lep[j],2)/pow(M[i],2)) ) ) * sqrt( (1 - pow(m_B_plus-m_lep[j],2)/pow(M[i],2))*(1 - pow(m_B_plus+m_lep[j],2)/pow(M[i],2)) );
          }
        }
      }
      result = gamma;
    }

    // Decay widths of RHNs, for BBN (N -> Bs+ l-)
    void Gamma_RHN2Bsl(std::vector<double>& result)
    {
      using namespace Pipes::Gamma_RHN2Bsl;
      SMInputs sminputs = *Dep::SMINPUTS;
      static double G_F_sq = pow(sminputs.GF, 2);
      static double m_B_s = meson_masses.B_s;
      static double f_Bs_sq = 0.0529;  // GeV^2
      // Take from the model parameters (Wolfenstein) PDG value: 0.22506
      static double Vus = *Param["CKM_lambda"];
      std::vector<double> m_lep(3), gamma(3), M(3);
      // Since we scan the SLHA2 model, we take masses from it
      m_lep[0] = *Param["mE"];
      m_lep[1] = *Param["mMu"];
      m_lep[2] = *Param["mTau"];
      M[0] = *Param["M_1"];
      M[1] = *Param["M_2"];
      M[2] = *Param["M_3"];
      Matrix3d Usq = Dep::SeesawI_Theta->cwiseAbs2(); // |\Theta_{ij}|^2

      for (int i=0; i<3; i++)
      {
        gamma[i] = 0;
        for (int j=0; j<3; j++)
        {
          if (M[i] > (m_B_s+m_lep[j]))
          {
            gamma[i] += ( (Usq(j,i)*G_F_sq*pow(Vus,2)*f_Bs_sq*pow(M[i],3))/(16*pi) ) * ( pow((1 - pow(m_lep[j],2)/pow(M[i],2)),2) - ( (pow(m_B_s,2)/pow(M[i],2))*(1 + pow(m_lep[j],2)/pow(M[i],2)) ) ) * sqrt( (1 - pow(m_B_s-m_lep[j],2)/pow(M[i],2))*(1 - pow(m_B_s+m_lep[j],2)/pow(M[i],2)) );
          }
        }
      }
      result = gamma;
    }

    // Decay widths of RHNs, for BBN (N -> Bc+ l-)
    void Gamma_RHN2Bcl(std::vector<double>& result)
    {
      using namespace Pipes::Gamma_RHN2Bcl;
      SMInputs sminputs = *Dep::SMINPUTS;
      static double G_F_sq = pow(sminputs.GF, 2);
      static double m_B_c = meson_masses.B_c;
      static double f_Bc_sq = 0.2304;  // GeV^2
      // Take from the model parameters (Wolfenstein) PDG value: 0.0411
      static double Vcb = *Param["CKM_A"]*pow(*Param["CKM_lambda"],2);
      std::vector<double> m_lep(3), gamma(3), M(3);
      // Since we scan the SLHA2 model, we take masses from it
      m_lep[0] = *Param["mE"];
      m_lep[1] = *Param["mMu"];
      m_lep[2] = *Param["mTau"];
      M[0] = *Param["M_1"];
      M[1] = *Param["M_2"];
      M[2] = *Param["M_3"];
      Matrix3d Usq = Dep::SeesawI_Theta->cwiseAbs2(); // |\Theta_{ij}|^2

      for (int i=0; i<3; i++)
      {
        gamma[i] = 0;
        for (int j=0; j<3; j++)
        {
          if (M[i] > (m_B_c+m_lep[j]))
          {
            gamma[i] += ( (Usq(j,i)*G_F_sq*pow(Vcb,2)*f_Bc_sq*pow(M[i],3))/(16*pi) ) * ( pow((1 - pow(m_lep[j],2)/pow(M[i],2)),2) - ( (pow(m_B_c,2)/pow(M[i],2))*(1 + pow(m_lep[j],2)/pow(M[i],2)) ) ) * sqrt( (1 - pow(m_B_c-m_lep[j],2)/pow(M[i],2))*(1 - pow(m_B_c+m_lep[j],2)/pow(M[i],2)) );
          }
        }
      }
      result = gamma;
    }

    // Decay widths of RHNs, for BBN (N -> eta nu)
    void Gamma_RHN2etanu(std::vector<double>& result)
    {
      using namespace Pipes::Gamma_RHN2etanu;
      SMInputs sminputs = *Dep::SMINPUTS;
      static double G_F_sq = pow(sminputs.GF, 2);
      static double m_eta = meson_masses.eta;
      static double f_eta_sq = 0.024336;  // GeV^2
      std::vector<double> gamma(3), M(3);
      M[0] = *Param["M_1"];
      M[1] = *Param["M_2"];
      M[2] = *Param["M_3"];
      Matrix3d Usq = Dep::SeesawI_Theta->cwiseAbs2(); // |\Theta_{ij}|^2

      for (int i=0; i<3; i++)
      {
        gamma[i] = 0;
        if (M[i] > m_eta)
        {
          for (int j=0; j<3; j++)
          {
            gamma[i] += ( (Usq(j,i)*G_F_sq*f_eta_sq*pow(M[i],3))/(32*pi) ) * pow((1 - pow(m_eta,2)/pow(M[i],2)),2);
          }
        }
      }
      result = gamma;
    }

    // Decay widths of RHNs, for BBN (N -> eta' nu)
    void Gamma_RHN2etaprimenu(std::vector<double>& result)
    {
      using namespace Pipes::Gamma_RHN2etaprimenu;
      SMInputs sminputs = *Dep::SMINPUTS;
      static double G_F_sq = pow(sminputs.GF, 2);
      static double m_eta_prime = meson_masses.eta_prime;
      static double f_etaprime_sq = 0.00342225;  // GeV^2
      std::vector<double> gamma(3), M(3);
      M[0] = *Param["M_1"];
      M[1] = *Param["M_2"];
      M[2] = *Param["M_3"];
      Matrix3d Usq = Dep::SeesawI_Theta->cwiseAbs2(); // |\Theta_{ij}|^2

      for (int i=0; i<3; i++)
      {
        gamma[i] = 0;
        if (M[i] > m_eta_prime)
        {
          for (int j=0; j<3; j++)
          {
            gamma[i] += ( (Usq(j,i)*G_F_sq*f_etaprime_sq*pow(M[i],3))/(32*pi) ) * pow((1 - pow(m_eta_prime,2)/pow(M[i],2)),2);
          }
        }
      }
      result = gamma;
    }

    // Decay widths of RHNs, for BBN (N -> rho+ l-)
    void Gamma_RHN2rhoplusl(std::vector<double>& result)
    {
      using namespace Pipes::Gamma_RHN2rhoplusl;
      SMInputs sminputs = *Dep::SMINPUTS;
      static double g_rho_sq = 0.010404;  // GeV^4
      static double G_F_sq = pow(sminputs.GF, 2);
      static double m_rho_plus = meson_masses.rho_plus;
      // Take from the model parameters (Wolfenstein) PDG value: 0.97434
      static double Vud = 1.0 - 0.5*pow(*Param["CKM_lambda"],2);
      std::vector<double> m_lep(3), gamma(3), M(3);
      // Since we scan the SLHA2 model, we take masses from it
      m_lep[0] = *Param["mE"];
      m_lep[1] = *Param["mMu"];
      m_lep[2] = *Param["mTau"];
      M[0] = *Param["M_1"];
      M[1] = *Param["M_2"];
      M[2] = *Param["M_3"];
      Matrix3d Usq = Dep::SeesawI_Theta->cwiseAbs2(); // |\Theta_{ij}|^2

      for (int i=0; i<3; i++)
      {
        gamma[i] = 0;
        for (int j=0; j<3; j++)
        {
          if (M[i] > (m_rho_plus+m_lep[j]))
          {
            gamma[i] += ( (Usq(j,i)*g_rho_sq*G_F_sq*pow(Vud,2)*pow(M[i],3))/(8*pi*pow(m_rho_plus,2)) ) * ( pow((1 - pow(m_lep[j],2)/pow(M[i],2)),2) + ( (pow(m_rho_plus,2)/pow(M[i],2))*(1 + (pow(m_lep[j],2)-(2*pow(m_rho_plus,2)))/pow(M[i],2)) ) ) * sqrt( (1 - pow(m_rho_plus-m_lep[j],2)/pow(M[i],2))*(1 - pow(m_rho_plus+m_lep[j],2)/pow(M[i],2)) );
          }
        }
      }
      result = gamma;
    }

    // Decay widths of RHNs, for BBN (N -> rho0 nu)
    void Gamma_RHN2rho0nu(std::vector<double>& result)
    {
      using namespace Pipes::Gamma_RHN2rho0nu;
      SMInputs sminputs = *Dep::SMINPUTS;
      static double g_rho_sq = 0.010404;  // GeV^4
      static double G_F_sq = pow(sminputs.GF, 2);
      static double m_rho_0 = meson_masses.rho0;
      std::vector<double> gamma(3), M(3);
      M[0] = *Param["M_1"];
      M[1] = *Param["M_2"];
      M[2] = *Param["M_3"];
      Matrix3d Usq = Dep::SeesawI_Theta->cwiseAbs2(); // |\Theta_{ij}|^2

      for (int i=0; i<3; i++)
      {
        gamma[i] = 0;
        if (M[i] > m_rho_0)
        {
          for (int j=0; j<3; j++)
          {
            gamma[i] += ( (Usq(j,i)*g_rho_sq*G_F_sq*pow(M[i],3))/(16*pi*pow(m_rho_0,2)) ) * (1 + (2*pow(m_rho_0,2))/pow(M[i],2)) * pow((1 - pow(m_rho_0,2)/pow(M[i],2)),2);
          }
        }
      }
      result = gamma;
    }

    // Decay widths of RHNs, for BBN (N -> nu nu nu)
    void Gamma_RHN23nu(std::vector<double>& result)
    {
      using namespace Pipes::Gamma_RHN23nu;
      SMInputs sminputs = *Dep::SMINPUTS;
      static double G_F_sq = pow(sminputs.GF, 2);
      std::vector<double> gamma(3), M(3);
      M[0] = *Param["M_1"];
      M[1] = *Param["M_2"];
      M[2] = *Param["M_3"];
      Matrix3d Usq = Dep::SeesawI_Theta->cwiseAbs2(); // |\Theta_{ij}|^2

      for (int i=0; i<3; i++)
      {
        gamma[i] = ( (G_F_sq*pow(M[i],5)) / (192*pow(pi,3)) ) * (Usq(0,i)+Usq(1,i)+Usq(2,i));
      }
      result = gamma;
    }

    // Helper function; formula is in [arXiv:1208.4607v2]
    double S(double xa, double xb)
    {
      return sqrt((1-pow((xa+xb),2))*(1-pow((xa-xb),2)));
    }

    // Also helper function; formula is in [arXiv:1208.4607v2]
    double g(double xa, double xb)
    {
     return (1 - (7*pow(xa,2)) - (7*pow(xb,2)) - (7*pow(xa,4)) - (7*pow(xb,4)) + (12*pow(xa,2)*pow(xb,2)) - (7*pow(xa,2)*pow(xb,4)) - (7*pow(xa,4)*pow(xb,2)) + pow(xa,6) + pow(xb,6));
    }

    // Decay widths of RHNs, for BBN (N -> l+ l- nu)
    // Formula is from [arXiv:1208.4607v2]
    void Gamma_RHN2llnu(std::vector<double>& result)
    {
      using namespace Pipes::Gamma_RHN2llnu;
      SMInputs sminputs = *Dep::SMINPUTS;
      static double G_F_sq = pow(sminputs.GF, 2);
      double x_a, x_b;
      std::vector<double> m_lep(3), gamma(3), M(3);
      // Since we scan the SLHA2 model, we take masses from it
      m_lep[0] = *Param["mE"];
      m_lep[1] = *Param["mMu"];
      m_lep[2] = *Param["mTau"];
      M[0] = *Param["M_1"];
      M[1] = *Param["M_2"];
      M[2] = *Param["M_3"];
      Matrix3d Usq = Dep::SeesawI_Theta->cwiseAbs2(); // |\Theta_{ij}|^2
      for (int i=0; i<3; i++)
      {
        gamma[i] = 0;
        for (int j=0; j<3; j++)
        {
          for (int k=0; k<3; k++)
          {
            if ( (j != k) and (M[i] > (m_lep[j]+m_lep[k])) )
            {
              x_a = m_lep[j]/M[i];
              x_b = m_lep[k]/M[i];
              gamma[i] += ( (G_F_sq*pow(M[i],5)) / (192*pow(pi,3)) ) * Usq(j,i) * (S(x_a,x_b)*g(x_a,x_b) - (x_a < 1E-2 ? -12*pow(x_a,4) : 12*pow(x_a,4)*log( (1 - (S(x_a,x_b)*(1+pow(x_a,2)-pow(x_b,2))) - (2*pow(x_b,2)) + pow((pow(x_a,2)-pow(x_b,2)),2)) / (2*pow(x_a,2)) ) ) - (x_b < 1E-2 ? -12*pow(x_b,4) : 12*pow(x_b,4)*log( (1 - (S(x_a,x_b)*(1-pow(x_a,2)+pow(x_b,2))) - (2*pow(x_a,2)) + pow((pow(x_a,2)-pow(x_b,2)),2)) / (2*pow(x_b,2)) ) ) + (x_a < 1E-2 or x_b < 1E-2 ? -12*pow(x_a,4)*pow(x_b,4) : 12*pow(x_a,4)*pow(x_b,4)*log( (1 - (S(x_a,x_b)*(1-pow(x_a,2)-pow(x_b,2))) - (2*pow(x_a,2)) - (2*pow(x_b,2)) + pow(x_a,4) + pow(x_b,4)) / (2*pow(x_a,2)*pow(x_b,2)) ) ) );
            }
          }
        }
      }
      result = gamma;
    }

    // Helper function; formula is in [arXiv:0705.1729]
    // This function varies wrt the paper to include the x^4 factor up front and a cutoff for small x
    double L(double x)
    {
      if(x < 1E-2)
        return -pow(x,4);
      return pow(x,4)*log((1-(3*pow(x,2.0))-((1-pow(x,2.0))*sqrt(1 - (4*pow(x,2.0))))) / (pow(x,2.0)*(1+sqrt(1 - (4*pow(x,2.0))))) );
    }

    // Decay widths of RHNs, for BBN (N -> nu l+ l-)
    void Gamma_RHN2null(std::vector<double>& result)
    {
      using namespace Pipes::Gamma_RHN2null;
      SMInputs sminputs = *Dep::SMINPUTS;
      static double G_F_sq = pow(sminputs.GF, 2);
      static double s_W_sq = 0.22336;  // get from within GAMBIT in future
      static double C1 = 0.25*(1 - (4*s_W_sq) + (8*pow(s_W_sq,2)));
      static double C2 = 0.5*s_W_sq*((2*s_W_sq) - 1);
      static double C3 = 0.25*(1 + (4*s_W_sq) + (8*pow(s_W_sq,2)));
      static double C4 = 0.5*s_W_sq*((2*s_W_sq) + 1);
      std::vector<double> m_lep(3), gamma(3), M(3);
       // Since we scan the SLHA2 model, we take masses from it
      m_lep[0] = *Param["mE"];
      m_lep[1] = *Param["mMu"];
      m_lep[2] = *Param["mTau"];
      M[0] = *Param["M_1"];
      M[1] = *Param["M_2"];
      M[2] = *Param["M_3"];
      Matrix3d Usq = Dep::SeesawI_Theta->cwiseAbs2(); // |\Theta_{ij}|^2

      for (int i=0; i<3; i++)
      {
        gamma[i] = 0;
        for (int j=0; j<3; j++)
        {
          for (int k=0; k<3; k++)
          {
            if (M[i] > (2*m_lep[k]))
            {
              double x_l = m_lep[k]/M[i];
              if (j == k)
              {
                gamma[i] += ( (G_F_sq*pow(M[i],5)) / (192*pow(pi,3)) ) * Usq(j,i) * ( (C3*(((1 - (14*pow(x_l,2)) - (2*pow(x_l,4)) - (12*pow(x_l,6)))*sqrt(1 - (4*pow(x_l,2)))) + (12*(pow(x_l,4)-1)*L(x_l)))) + 4*C4*((pow(x_l,2)*(2 + (10*pow(x_l,2)) - (12*pow(x_l,4)))*sqrt(1 - (4*pow(x_l,2)))) + 6*(1.0-2*pow(x_l,2)+2*pow(x_l,4))*L(x_l)) );
              }
              else
              {
                gamma[i] += ( (G_F_sq*pow(M[i],5)) / (192*pow(pi,3)) ) * Usq(j,i) * ( (C1*(((1 - (14*pow(x_l,2)) - (2*pow(x_l,4)) - (12*pow(x_l,6)))*sqrt(1 - (4*pow(x_l,2)))) + (12*(pow(x_l,4)-1)*L(x_l)))) + (4*C2*((pow(x_l,2)*(2 + (10*pow(x_l,2)) - (12*pow(x_l,4)))*sqrt(1 - (4*pow(x_l,2)))) + (6*(1.0-2*pow(x_l,2)+2*pow(x_l,4))*L(x_l)))) );
              }
            }
          }
        }
      }
      result = gamma;
    }

    // Helper function; formula is in [arXiv:1208.4607v2]
    double f_u(double x)
    {
      static double s_W_sq = 0.22336;  // get from within GAMBIT in future
      static double C1 = s_W_sq*(3 - (4*s_W_sq));
      return (0.25 - ((2/9)*C1) - ((3.5-((20/9)*C1))*pow(x,2)) - ((0.5+(4*C1))*pow(x,4)) - ((3-(8*C1))*pow(x,6)));
    }

    // Decay widths of RHNs, for BBN (N -> nu u ubar)
    // Formula is from [arXiv:1208.4607v2]
    void Gamma_RHN2nuuubar(std::vector<double>& result)
    {
      using namespace Pipes::Gamma_RHN2nuuubar;
      SMInputs sminputs = *Dep::SMINPUTS;
      static double G_F_sq = pow(sminputs.GF, 2);
      static double s_W_sq = 0.22336;  // get from within GAMBIT in future
      static double C1 = s_W_sq*(3 - (4*s_W_sq));
      std::vector<double> m_uquark(3), gamma(3), M(3);
      double x_q;
      // Since we scan the SLHA2 model, we take masses from it
      m_uquark[0] = *Param["mU"];
      m_uquark[1] = *Param["mCmC"];
      m_uquark[2] = *Param["mT"];
      M[0] = *Param["M_1"];
      M[1] = *Param["M_2"];
      M[2] = *Param["M_3"];
      Matrix3d Usq = Dep::SeesawI_Theta->cwiseAbs2(); // |\Theta_{ij}|^2

      for (int i=0; i<3; i++)
      {
        gamma[i] = 0;
        for (int j=0; j<3; j++)
        {
          for (int k=0; k<3; k++)
          {
            if ( (M[i] > (2*m_uquark[k])) and (M[i] > 7.5) )  // For now, take 7.5 GeV to be the mass limit beyond which the RHN decay is to lepton+quark final state
            {
              x_q = m_uquark[k]/M[i];
              gamma[i] += ( (G_F_sq*pow(M[i],5)) / (192*pow(pi,3)) ) * Usq(j,i) * ( (f_u(x_q)*S(x_q,x_q)) + ( pow(x_q,4) * (3 - ((16/3)*C1*pow(x_q,2)) + ((3-(8*C1))*pow(x_q,4))) * log( (1-(4*pow(x_q,2))+(2*pow(x_q,4))+(S(x_q,x_q)*(1-(2*pow(x_q,2))))) / (2*pow(x_q,4)))) );
            }
          }
        }
      }
      result = gamma;
    }

    // Helper function; formula is in [arXiv:1208.4607v2]
    double f_d(double x)
    {
      static double s_W_sq = 0.22336;  // get from within GAMBIT in future
      static double C2 = s_W_sq*(3 - (2*s_W_sq));
      return (0.25 - ((1/9)*C2) - (((2/7)-((10/9)*C2))*pow(x,2)) - ((0.5+(2*C2))*pow(x,4)) - ((3-(4*C2))*pow(x,6)));
    }

    // Decay widths of RHNs, for BBN (N -> nu d dbar)
    // Formula is from [arXiv:1208.4607v2]
    void Gamma_RHN2nuddbar(std::vector<double>& result)
    {
      using namespace Pipes::Gamma_RHN2nuddbar;
      SMInputs sminputs = *Dep::SMINPUTS;
      static double G_F_sq = pow(sminputs.GF, 2);
      static double s_W_sq = 0.22336;  // get from within GAMBIT in future
      static double C2 = s_W_sq*(3 - (2*s_W_sq));
      std::vector<double> m_dquark(3), gamma(3), M(3);
      double x_q;
      // Since we scan the SLHA2 model, we take masses from it
      m_dquark[0] = *Param["mD"];
      m_dquark[1] = *Param["mS"];
      m_dquark[2] = *Param["mBmB"];
      M[0] = *Param["M_1"];
      M[1] = *Param["M_2"];
      M[2] = *Param["M_3"];
      Matrix3d Usq = Dep::SeesawI_Theta->cwiseAbs2(); // |\Theta_{ij}|^2

      for (int i=0; i<3; i++)
      {
        gamma[i] = 0;
        for (int j=0; j<3; j++)
        {
          for (int k=0; k<3; k++)
          {
            if ( (M[i] > (2*m_dquark[k])) and (M[i] > 7.5) )  // For now, take 7.5 GeV to be the mass limit beyond which the RHN decay is to lepton+quark final state
            {
              x_q = m_dquark[k]/M[i];
              gamma[i] += ( (G_F_sq*pow(M[i],5)) / (192*pow(pi,3)) ) * Usq(j,i) * ( (f_d(x_q)*S(x_q,x_q)) + ( pow(x_q,4) * (3 - ((8/3)*C2*pow(x_q,2)) + ((1-((4/3)*C2))*pow(x_q,4))) * log( (1-(4*pow(x_q,2))+(2*pow(x_q,4))+(S(x_q,x_q)*(1-(2*pow(x_q,2))))) / (2*pow(x_q,4)))) );
            }
          }
        }
      }
      result = gamma;
    }

    // Helper function to find two heavier decay products
    std::vector<double> two_heaviest_sort(std::vector<double> decay_prod)
    {
      std::vector<double> result(2);
      double temp;
      result[0] = decay_prod[0];
      result[1] = decay_prod[1];
      if (result[0]<result[1])
      {
        temp = result[0];
        result[0] = result[1];
        result[1] = temp;
      }
      if (decay_prod[2]>result[0])
      {
        result[1] = result[0];
        result[0] = decay_prod[2];
      }
      else if (decay_prod[2]>result[1])
        result[1] = decay_prod[2];
      return result;
    }

    // Decay widths of RHNs, for BBN (N -> l u dbar)
    // Formula is from [arXiv:1208.4607v2]
    void Gamma_RHN2ludbar(std::vector<double>& result)
    {
      using namespace Pipes::Gamma_RHN2ludbar;
      SMInputs sminputs = *Dep::SMINPUTS;
      static double G_F_sq = pow(sminputs.GF, 2);
      // Take from the model parameters (Wolfenstein) (absolute values)
      // Values from PDG: V =  { {0.97434,0.22506,0.00357},
      //                         {0.22492,0.97351,0.0411},
      //                         {0.00875,0.0403,0.99915} };
      static double Vus = *Param["CKM_lambda"];
      static double Vud = 1.0 - 0.5*pow(Vus,2);
      static double Vub = *Param["CKM_A"]*pow(Vus,3)*sqrt(pow(*Param["CKM_rhobar"],2) + pow(*Param["CKM_etabar"],2));
      static double Vcd = Vus;
      static double Vcs = Vud;
      static double Vcb = *Param["CKM_A"]*pow(Vus,2);
      static double Vtd = Vcb*Vus*sqrt(pow(1.0 - *Param["CKM_rhobar"],2) + pow(*Param["CKM_etabar"],2));
      static double Vts = Vcb;
      static double Vtb = 1;
      static std::vector<std::vector<double> > V = { {Vud, Vus, Vub}, {Vcd, Vcs, Vcb}, {Vtd, Vts, Vtb} };

      double x, y;
      std::vector<double> m_lep(3), m_uquark(3), m_dquark(3), gamma(3), M(3), decay_prod(3), two_heaviest(2);
      // Since we scan the SLHA2 model, we take masses from it
      m_lep[0] = *Param["mE"];
      m_lep[1] = *Param["mMu"];
      m_lep[2] = *Param["mTau"];
      m_uquark[0] = *Param["mU"];
      m_uquark[1] = *Param["mCmC"];
      m_uquark[2] = *Param["mT"];
      m_dquark[0] = *Param["mD"];
      m_dquark[1] = *Param["mS"];
      m_dquark[2] = *Param["mBmB"];
      M[0] = *Param["M_1"];
      M[1] = *Param["M_2"];
      M[2] = *Param["M_3"];
      Matrix3d Usq = Dep::SeesawI_Theta->cwiseAbs2(); // |\Theta_{ij}|^2

      for (int i=0; i<3; i++)
      {
        gamma[i] = 0;
        for (int j=0; j<3; j++)
        {
          for (int k=0; k<3; k++)
          {
            for (int l=0; l<3; l++)
            {
              if ( (M[i] > (m_lep[j]+m_uquark[k]+m_dquark[l])) and (M[i] > 7.5) )  // For now, take 7.5 GeV to be the mass limit below which the RHN decay is to lepton+meson final state
              {
                decay_prod[0] = m_lep[j];
                decay_prod[1] = m_uquark[k];
                decay_prod[2] = m_dquark[l];
                two_heaviest = two_heaviest_sort(decay_prod);
                x = two_heaviest[0]/M[i];
                y = two_heaviest[1]/M[i];
                gamma[i] += ( (G_F_sq*pow(M[i],5)) / (192*pow(pi,3)) ) * Usq(j,i) * pow(V[k][l],2) * ((S(x,y)*g(x,y)) - (x < 1E-2 ? -12*pow(x,4) : 12*pow(x,4)*log( (1 - (S(x,y)*(1+pow(x,2)-pow(y,2))) - (2*pow(y,2)) + pow((pow(x,2)-pow(y,2)),2)) / (2*pow(x,2)) ) ) - (y < 1E-2 ? -12*pow(y,4) : 12*pow(y,4)*log( (1 - (S(x,y)*(1-pow(x,2)+pow(y,2))) - (2*pow(x,2)) + pow((pow(x,2)-pow(y,2)),2)) / (2*pow(y,2)) ) ) + (x < 1E-2 or y < 1E-2 ? -12*pow(x,4)*pow(y,4) : 12*pow(x,4)*pow(y,4)*log( (1 - (S(x,y)*(1-pow(x,2)-pow(y,2))) - (2*pow(x,2)) - (2*pow(y,2)) + pow(x,4) + pow(y,4)) / (2*pow(x,2)*pow(y,2)) ) ) );
              }
            }
          }
        }
      }
      result = gamma;
    }

    // Calculates total decay width for each RHN [GeV]
    void Gamma_BBN(std::vector<double>& result)
    {
      using namespace Pipes::Gamma_BBN;
      std::vector<double> RHN2pi0nu = *Dep::Gamma_RHN2pi0nu;
      std::vector<double> RHN2piplusl = *Dep::Gamma_RHN2piplusl;
      std::vector<double> RHN2Kplusl = *Dep::Gamma_RHN2Kplusl;
      std::vector<double> RHN2Dplusl = *Dep::Gamma_RHN2Dplusl;
      std::vector<double> RHN2Dsl = *Dep::Gamma_RHN2Dsl;
      std::vector<double> RHN2Bplusl = *Dep::Gamma_RHN2Bplusl;
      std::vector<double> RHN2Bsl = *Dep::Gamma_RHN2Bsl;
      std::vector<double> RHN2Bcl = *Dep::Gamma_RHN2Bcl;
      std::vector<double> RHN2etanu = *Dep::Gamma_RHN2etanu;
      std::vector<double> RHN2etaprimenu = *Dep::Gamma_RHN2etaprimenu;
      std::vector<double> RHN2rhoplusl = *Dep::Gamma_RHN2rhoplusl;
      std::vector<double> RHN2rho0nu = *Dep::Gamma_RHN2rho0nu;
      std::vector<double> RHN23nu = *Dep::Gamma_RHN23nu;
      std::vector<double> RHN2llnu = *Dep::Gamma_RHN2llnu;
      std::vector<double> RHN2null = *Dep::Gamma_RHN2null;
      std::vector<double> RHN2nuuubar = *Dep::Gamma_RHN2nuuubar;
      std::vector<double> RHN2nuddbar = *Dep::Gamma_RHN2nuddbar;
      std::vector<double> RHN2ludbar = *Dep::Gamma_RHN2ludbar;
      std::vector<double> gamma_total(3);
      
      for (int i=0; i<3; i++)
      {
        gamma_total[i] = 2*(RHN2pi0nu[i]+RHN2piplusl[i]+RHN2Kplusl[i]+RHN2Dplusl[i]+RHN2Dsl[i]+RHN2Bplusl[i]+RHN2Bsl[i]+RHN2Bcl[i]+RHN2etanu[i]+RHN2etaprimenu[i]+RHN2rhoplusl[i]+RHN2rho0nu[i]+RHN23nu[i]+RHN2llnu[i]+RHN2null[i]+RHN2nuuubar[i]+RHN2nuddbar[i]+RHN2ludbar[i]);  // factor of 2 accounts for Majorana nature
      }
      result = gamma_total;
    }

    // BBN constraint likelihood : lifetime must be less than 0.1s [arXiv:1202.2841]
    // This is here implemented as step function in the likelihood
    void lnL_bbn(double& result_bbn)
    {
      using namespace Pipes::lnL_bbn;
      std::vector<double> gamma = *Dep::Gamma_BBN;
      result_bbn = 0.0;
      for(int i=0; i<3; i++)
      {
        if((hbar/gamma[i])>0.1)
        {
          result_bbn = -100;
        }
      }
    }

    // Lepton universality constraint: R_{e,mu)^pi. Computation from 1502.00477. R_pi_SM from Phys. Rev. Lett 99, 231801.
    void RHN_R_pi(double& R_pi)
    {
      using namespace Pipes::RHN_R_pi;
      SMInputs sminputs = *Dep::SMINPUTS;
      static double m_pi = meson_masses.pi_plus;
      static double R_pi_SM = 1.2354e-4;
      static double r_e_pi = pow(sminputs.mE,2)/pow(m_pi,2);
      static double r_mu_pi = pow(sminputs.mMu,2)/pow(m_pi,2);
      double e_f_pi = 0.0, mu_f_pi = 0.0, d_r_pi = 1.0;
      std::vector<double> M(3), r_I_pi(3), G_e_pi = {0.0,0.0,0.0}, G_mu_pi = {0.0,0.0,0.0};
      Matrix3d Usq = Dep::SeesawI_Theta->cwiseAbs2();

      M[0] = *Param["M_1"];
      M[1] = *Param["M_2"];
      M[2] = *Param["M_3"];

      for (int i=0; i<3; i++)
      {
        r_I_pi[i] = pow(M[i], 2)/pow(m_pi, 2);
 
        if(M[i] + sminputs.mMu < m_pi)
        {
          G_mu_pi[i] = ( r_mu_pi + r_I_pi[i] - pow((r_mu_pi - r_I_pi[i]), 2) ) * sqrt(1.0 - 2.0*(r_mu_pi + r_I_pi[i]) + pow(r_mu_pi - r_I_pi[i], 2)) / (r_mu_pi * pow((1.0 - r_mu_pi), 2));
        } 
        else
          G_mu_pi[i] = 0.0;

        if(M[i] + sminputs.mE < m_pi)
        {
          G_e_pi[i] = ( r_e_pi + r_I_pi[i] - pow(r_e_pi - r_I_pi[i], 2) ) * sqrt(1.0 - 2.0*(r_e_pi + r_I_pi[i]) + pow((r_e_pi - r_I_pi[i]), 2)) / (r_e_pi * pow((1.0 - r_e_pi), 2));
        }
        else
          G_e_pi[i] = 0.0;

        e_f_pi += Usq(0,i) * (G_e_pi[i] - 1.0);
        mu_f_pi += Usq(1,i) * (G_mu_pi[i] - 1.0);
  
      }

      d_r_pi = ((1.0 + e_f_pi)/(1.0 + mu_f_pi));
      R_pi = R_pi_SM * d_r_pi;
 
    }

    // Lepton universality constraint: R_(e,mu)^K. Computation from 1502.00477. R_K_SM from Phys. Rev. Lett 99, 231801.
    void RHN_R_K(double& R_K)
    {
      using namespace Pipes::RHN_R_K;
      SMInputs sminputs = *Dep::SMINPUTS;
      static double m_K = meson_masses.kaon_plus; 
      static double R_K_SM = 2.477e-5;
      static double r_e_K = pow(sminputs.mE,2)/pow(m_K,2);
      static double r_mu_K = pow(sminputs.mMu,2)/pow(m_K,2);
      double e_f_K = 0.0, mu_f_K = 0.0, d_r_K = 1.0;
      std::vector<double> M(3), r_I_K(3), G_e_K = {0.0,0.0,0.0}, G_mu_K = {0.0,0.0,0.0};
      Matrix3d Usq = Dep::SeesawI_Theta->cwiseAbs2();

      M[0] = *Param["M_1"];
      M[1] = *Param["M_2"];
      M[2] = *Param["M_3"];

      for (int i=0; i<3; i++)
      {
        r_I_K[i] = pow(M[i], 2)/pow(m_K,2);

        if(M[i] + sminputs.mMu < m_K)
        {
          G_mu_K[i] = ( r_mu_K + r_I_K[i] - pow((r_mu_K - r_I_K[i]), 2) ) * sqrt(1.0 - 2.0*(r_mu_K + r_I_K[i]) + pow(r_mu_K - r_I_K[i], 2)) / (r_mu_K * pow((1.0 - r_mu_K), 2));
        } 
        else
          G_mu_K[i] = 0.0;

        if(M[i] + sminputs.mE < m_K)
        {
          G_e_K[i] = ( r_e_K + r_I_K[i] - pow((r_e_K - r_I_K[i]), 2) ) * sqrt(1.0 - 2.0*(r_e_K + r_I_K[i]) + pow((r_e_K - r_I_K[i]), 2)) / (r_e_K * pow((1.0 - r_e_K), 2));
        }
        else
          G_e_K[i] = 0.0;

        e_f_K += Usq(0,i) * (G_e_K[i] - 1.0);
        mu_f_K += Usq(1,i) * (G_mu_K[i] - 1.0);
          
      }

      d_r_K = ((1.0 + e_f_K)/(1.0 + mu_f_K));
      R_K = R_K_SM * d_r_K;
    }

    // Lepton universality constraint: R_(e,mu)^tau. Computation from 1502.00477. R_tau_SM from Int. J. Mod. Phys. A 24, 715, 2009.
    void RHN_R_tau(double& R_tau)
    {
      using namespace Pipes::RHN_R_tau;
      SMInputs sminputs = *Dep::SMINPUTS;
      static double m_tau = sminputs.mTau;  // GeV
      static double R_tau_SM = 0.973;
      double e_f_tau = 0.0, mu_f_tau = 0.0, d_r_tau = 1.0;
      std::vector<double> M(3);
      Matrix3d Usq = Dep::SeesawI_Theta->cwiseAbs2();

      M[0] = *Param["M_1"];
      M[1] = *Param["M_2"];
      M[2] = *Param["M_3"];

      for (int i=0; i<3; i++)
      {
        if(M[i] > m_tau)
        {
          e_f_tau  -= Usq(0,i);
          mu_f_tau -= Usq(1,i);
        }
        else
        {
          e_f_tau += 0.0;
          mu_f_tau += 0.0;
        }
      }

      d_r_tau = ((1.0 + mu_f_tau)/(1.0 + e_f_tau));
      R_tau = R_tau_SM * d_r_tau;
    }

    // Lepton universality from W decays
    // 0: R(W->mu nu/W->e nu) from LHCb 1608.01484
    // 1: R(W->tau nu/W->e nu) from LEP 1302.3415
    // 2: R(W->tau nu/W->mu nu) from LEP 1302.3415
    void RHN_R_W(std::vector<double> &R_W)
    {
      using namespace Pipes::RHN_R_W;
      std::vector<double> Wdecays = *Dep::W_to_l_decays;

      R_W.clear();

      R_W.push_back(Wdecays[1]/Wdecays[0]);
      R_W.push_back(Wdecays[2]/Wdecays[0]);
      R_W.push_back(Wdecays[2]/Wdecays[1]);
    }

    // Log-likelihood for the lepton universality constraint R_(e,mu)^K
    void lnL_R_K(double& result)
    {
      using namespace Pipes::lnL_R_K;
      double R_K = *Dep::R_K;
      double R_K_exp = 2.488e-5; // 1212.4012 (Phys. Lett. B 719 (2013), 326)
      double R_K_err = 0.010e-5;

      result = Stats::gaussian_loglikelihood(R_K, R_K_exp, 0.0, R_K_err, false);
    }

    // Log-likelihood for the lepton universality constraint R_(e,mu)^pi
    void lnL_R_pi(double& result)
    {
      using namespace Pipes::lnL_R_pi;
      double R_pi = *Dep::R_pi;
      double R_pi_exp = 1.2327e-4; // PDG average from Phys.Rev.Lett. 70 (1993) 17-20, Phys. Rev. Lett. 115, 071801 (2015), Phys. Rev. Lett. 68, 3000 (1992)
      double R_pi_err = 0.0023e-4;

      result = Stats::gaussian_loglikelihood(R_pi, R_pi_exp, 0.0, R_pi_err, false);
    }

    // Log-likelihood for the lepton universality constraint R_(e,mu)^tau
    void lnL_R_tau(double& result)
    {
      using namespace Pipes::lnL_R_tau;
      double R_tau = *Dep::R_tau;
      double R_tau_exp = 0.9762; // 1612.07233 (Phys. Rev. D 86, 010001) 
      double R_tau_err = 0.0028;

      result = Stats::gaussian_loglikelihood(R_tau, R_tau_exp, 0.0, R_tau_err, false);
    }
 
    // Log-likelihood for the lepton universality constraint R_(e,mu)^W 
    void lnL_R_W(double& result)
    {
      using namespace Pipes::lnL_R_W;
      std::vector<double> R_W = *Dep::R_W;

      std::vector<double> R_W_exp = {0.986, 1.043, 1.070}; // PDG 18
      std::vector<double> R_W_err = {0.013, 0.024, 0.026}; // PDG 18

      result = Stats::gaussian_loglikelihood(R_W[0], R_W_exp[0], 0.0, R_W_err[0], false);
      result += Stats::gaussian_loglikelihood(R_W[1], R_W_exp[1], 0.0, R_W_err[1], false);
      result += Stats::gaussian_loglikelihood(R_W[2], R_W_exp[2], 0.0, R_W_err[2], false);
    }

    // Calculate 0nubb half-life [1/yr] for 136Xe 0nubb detector, for the RHN model
    void RHN_Thalf_0nubb_Xe(double& result)
    {
      using namespace Pipes::RHN_Thalf_0nubb_Xe;
      double mp, A_0nubb_Xe, p2_0nubb_Xe, prefactor;
      std::vector<double> M(3);
      std::complex<double> sum = {0.0,0.0};

      // Relevant model parameters
      Matrix3cd theta = *Dep::SeesawI_Theta;
      M[0] = *Param["M_1"];
      M[1] = *Param["M_2"];
      M[2] = *Param["M_3"];

      // Nuisance parameters following the definitions in Faessler et al. 2014 (1408.6077)
      A_0nubb_Xe = runOptions->getValueOrDef<double>(8.74, "A");
      A_0nubb_Xe *= 1e-10;  // [1/yr]
      p2_0nubb_Xe = pow(runOptions->getValueOrDef<double>(183.0, "p"), 2);
      p2_0nubb_Xe *= 1e-6;  // MeV^2 --> GeV^2
      mp = 0.938;  // [GeV] (PDG 2014)

      // Lifetime equation is adopted from Faessler+14, Eq. (13)
      prefactor = A_0nubb_Xe*mp*mp/p2_0nubb_Xe/p2_0nubb_Xe;
      for (int i=0; i<3; i++)
      {
        sum+=pow(theta(0,i),2)*M[i]*p2_0nubb_Xe/(p2_0nubb_Xe+pow(M[i], 2));
      }
      result = prefactor * abs(sum) * abs(sum);
    }
    
    // Calculate 0nubb half-life [1/yr] for 76Ge 0nubb detector, for the RHN model
    void RHN_Thalf_0nubb_Ge(double& result)
    {
      using namespace Pipes::RHN_Thalf_0nubb_Ge;
      double mp, A_0nubb_Ge, p2_0nubb_Ge, prefactor;
      std::vector<double> M(3);
      std::complex<double> sum = {0.0,0.0};

      // Relevant model parameters
      Matrix3cd theta = *Dep::SeesawI_Theta;
      M[0] = *Param["M_1"];
      M[1] = *Param["M_2"];
      M[2] = *Param["M_3"];

      // Nuisance parameters following the definitions in Faessler et al. 2014 (1408.6077)
      A_0nubb_Ge = runOptions->getValueOrDef<double>(5.05, "A");
      A_0nubb_Ge *= 1e-10;  // [1/yr]
      p2_0nubb_Ge = pow(runOptions->getValueOrDef<double>(163.0, "p"), 2);
      p2_0nubb_Ge *= 1e-6;  // MeV^2 --> GeV^2
      mp = 0.938;  // [GeV] (PDG 2014)

      // Lifetime equation is adopted from Faessler+14, Eq. (13)
      prefactor = A_0nubb_Ge*mp*mp/p2_0nubb_Ge/p2_0nubb_Ge;
      for (int i=0; i<3; i++)
      {
        sum+=pow(theta(0,i),2)*M[i]*p2_0nubb_Ge/(p2_0nubb_Ge+pow(M[i], 2));
      }
      result = prefactor * abs(sum) * abs(sum);
    }

    // KamLAND-Zen: Phys. Rev. Lett 117 (2016) 082503
    void lnL_0nubb_KamLAND_Zen(double& result)
    {
      using namespace Pipes::lnL_0nubb_KamLAND_Zen;
      double tau_limit = 1.07e26;  // [yr] 90% CL

      double Thalf = *Dep::Thalf_0nubb_Xe;

      // Factor 1.28155 corresponds to one-sided UL at 90% CL
      result = Stats::gaussian_upper_limit(Thalf, 0., 0., tau_limit/1.28155, false);
    }

    // GERDA: Phys. Rev. Lett. 111 (2013) 122503
    //        Update: Nature 544 (2017) 47
    void lnL_0nubb_GERDA(double& result)
    {
      using namespace Pipes::lnL_0nubb_GERDA;
      double tau_limit = 5.3e25;  // [yr] 90% CL

      double Thalf = *Dep::Thalf_0nubb_Ge;

      // Factor 1.28155 corresponds to one-sided UL at 90% CL
      result = Stats::gaussian_upper_limit(Thalf, 0., 0., tau_limit/1.28155, false);
    }

    // Unified 0nubb likelihood
    void lnL_0nubb(double &result)
    {
      using namespace Pipes::lnL_0nubb;
      result = *Dep::lnL_0nubb_KamLAND_Zen + *Dep::lnL_0nubb_GERDA;
    }

    // Calculate mbb for 136Xe 0nubb detector, for the RHN model
    void RHN_mbb_0nubb_Xe(double& result)
    {
      using namespace Pipes::RHN_mbb_0nubb_Xe;
      double p2_0nubb_Xe;
      std::vector<double> M(3);
      std::complex<double> sum = {0.0,0.0};

      // Relevant model parameters
      Matrix3cd m_light = *Dep::m_nu;
      Matrix3cd U_light = *Dep::UPMNS;
      Matrix3cd theta = *Dep::SeesawI_Theta;
      M[0] = *Param["M_1"];
      M[1] = *Param["M_2"];
      M[2] = *Param["M_3"];

      // Nuisance parameters following the definitions in Faessler et al. 2014 (1408.6077)
      p2_0nubb_Xe = pow(runOptions->getValueOrDef<double>(178.0, "p"), 2);
      p2_0nubb_Xe *= 1e-6;  // MeV^2 --> GeV^2
      
      // mbb equation is adopted from Drewes, Eijima 2017, Eq. (14) and following
      for (int i=0; i<3; i++)
      {
        sum += pow(U_light(0,i),2)*m_light(i,i);
      }
      for (int i=0; i<3; i++)
      {
        sum += pow(theta(0,i),2)*M[i]*(p2_0nubb_Xe/(p2_0nubb_Xe + pow(M[i],2)));
      }
      result = abs(sum);
    } 
    
    // Calculate mbb for 76Ge 0nubb detector, for the RHN model
    void RHN_mbb_0nubb_Ge(double& result)
    {
      using namespace Pipes::RHN_mbb_0nubb_Ge;
      double p2_0nubb_Ge;
      std::vector<double> M(3);
      std::complex<double> sum = {0.0,0.0};

      // Relevant model parameters
      Matrix3cd m_light = *Dep::m_nu;
      Matrix3cd U_light = *Dep::UPMNS;
      Matrix3cd theta = *Dep::SeesawI_Theta;
      M[0] = *Param["M_1"];
      M[1] = *Param["M_2"];
      M[2] = *Param["M_3"];

      // Nuisance parameters following the definitions in Faessler et al. 2014 (1408.6077)
      p2_0nubb_Ge = pow(runOptions->getValueOrDef<double>(159.0, "p"), 2);
      p2_0nubb_Ge *= 1e-6;  // MeV^2 --> GeV^2
      
      // mbb equation is adopted from Drewes, Eijima 2017, Eq. (14) and following
      for (int i=0; i<3; i++)
      {
        sum += pow(U_light(0,i),2)*m_light(i,i);
      }
      for (int i=0; i<3; i++)
      {
        sum += pow(theta(0,i),2)*M[i]*(p2_0nubb_Ge/(p2_0nubb_Ge + pow(M[i],2)));
      }
      result = abs(sum);
    } 
    
    // KamLAND-Zen: Phys. Rev. Lett 117 (2016) 082503
    void lnL_mbb_0nubb_KamLAND_Zen(double& result)
    {
      using namespace Pipes::lnL_mbb_0nubb_KamLAND_Zen;
      double mbb_limit = 0.165*1e-9;  // [GeV] mbb < (0.061-0.165)eV at 90% C

      double mbb = *Dep::mbb_0nubb_Xe;

      // Factor 1.28155 corresponds to one-sided UL at 90% CL
      result = Stats::gaussian_upper_limit(mbb, 0., 0., mbb_limit/1.28155, false);
    }

    // GERDA: Phys. Rev. Lett. 111 (2013) 122503
    //        Update: Nature 544 (2017) 47
    void lnL_mbb_0nubb_GERDA(double& result)
    {
      using namespace Pipes::lnL_mbb_0nubb_GERDA;
      double mbb_limit = 0.33*1e-9;  // [GeV] mbb < (0.15-0.33)eV at 90% CL

      double mbb = *Dep::mbb_0nubb_Ge;

      // Factor 1.28155 corresponds to one-sided UL at 90% CL
      result = Stats::gaussian_upper_limit(mbb, 0., 0., mbb_limit/1.28155, false);
    }

    // Unified 0nubb likelihood based on mbb
    void lnL_mbb_0nubb(double &result)
    {
      using namespace Pipes::lnL_mbb_0nubb;
      result = *Dep::lnL_mbb_0nubb_KamLAND_Zen + *Dep::lnL_mbb_0nubb_GERDA;
    }

    // Helper function to fill all needed experimental info for CKM unitarity
    void fill_ckm_exp(Matrix3cd &Theta, double GF, triplet<double> (&Vus_exp)[8], triplet<double> &Vud_exp, double (&f)[8])
    {
      // Vus
      // Experimental values determined for K and tau decays. From table 1 in 1502.00477
      double V_us_exp[] = {0.2163, 0.2166, 0.2155, 0.2160, 0.2158, 0.2262, 0.2214, 0.2173};
      double err_V_us_exp[] = {0.0006, 0.0006, 0.0013, 0.0011, 0.0014, 0.0013, 0.0022, 0.0022};
      double f_plus = 0.959;
      double err_f_plus = 0.005;
      for(int i=0; i<5; i++)
      {
        V_us_exp[i] /= f_plus;
        err_V_us_exp[i] = sqrt(pow(err_V_us_exp[i] / f_plus,2) + pow(V_us_exp[i] * err_f_plus / f_plus, 2));
      }
 
      // Fill Vus_exp triplet
      for(int i=0; i<8; i++)
      {
        Vus_exp[i].central = V_us_exp[i];
        Vus_exp[i].upper = err_V_us_exp[i];
        Vus_exp[i].lower = err_V_us_exp[i];
      }

      // Vud
      // Combined value from the PDG
      static double V_ud_exp = 0.97417;
      static double err_V_ud_exp = 0.00021;
 
      // Fill Vud_exp triplet
      Vud_exp.central = V_ud_exp;
      Vud_exp.upper = err_V_ud_exp;
      Vud_exp.lower = err_V_ud_exp;

      // f
      Matrix3d ThetaNorm = (Theta * Theta.adjoint()).real();
      double Gmu = sqrt(GF*GF*(1. - ThetaNorm(1,1) - ThetaNorm(0,0)));

      f[0] = pow(GF/Gmu,2)*(1 - ThetaNorm(0,0));
      f[1] = f[0];
      f[2] = f[0];
      f[3] = pow(GF/Gmu,2)*(1 - ThetaNorm(1,1));
      f[4] = f[3];
      f[5] = 1 + ThetaNorm(1,1);
      f[6] = 1 + ThetaNorm(0,0) + ThetaNorm(1,1) - ThetaNorm(2,2);
      f[7] = 1 + 0.2*ThetaNorm(0,0) - 0.9*ThetaNorm(1,1) - 0.2*ThetaNorm(2,2);
    }
     
    // CKM unitarity constraint: optimize on Vus from Theta [PDG 2016]
    void calc_Vus(double& result_Vus)
    {
      using namespace Pipes::calc_Vus;
      SMInputs sminputs = *Dep::SMINPUTS;
      Matrix3cd Theta = *Dep::SeesawI_Theta;

      // Fill experimental data
      triplet<double> V_us_exp[8];
      triplet<double> V_ud_exp;
      double f[8];
      fill_ckm_exp(Theta, sminputs.GF, V_us_exp, V_ud_exp, f);
      
      // For the minimalization it's much better to transform the Vud experimental result to Vus the same as we do for theory and minimize only Vus
      static double V_us_from_Vud=sqrt(1.-V_ud_exp.central*V_ud_exp.central);
      static double err_V_us_from_Vud_exp= ( (V_ud_exp.central)/(sqrt(1-V_ud_exp.central*V_ud_exp.central))  ) * V_ud_exp.upper;
                                             
      double est_Vus = 0.;
      double sum_numerator = 0;
      double sum_denominator = 0;
      for (int i=0; i<7; i++)
      {
        sum_numerator += (V_us_exp[i].central/f[i]) / (V_us_exp[i].upper*V_us_exp[i].upper /( f[i]*f[i]));
        sum_denominator += 1./(V_us_exp[i].upper*V_us_exp[i].upper /( f[i]*f[i]));
      }
      // now vud
      sum_numerator += (V_us_from_Vud /f[0]) / ( (err_V_us_from_Vud_exp*err_V_us_from_Vud_exp)/( f[0]*f[0]));
      sum_denominator +=  1./( (err_V_us_from_Vud_exp*err_V_us_from_Vud_exp) /( f[0]*f[0]) );

      est_Vus = sum_numerator/sum_denominator;
      
      result_Vus = est_Vus;
    }

    // CKM unitarity constraint: V_ud should lie within 3sigma of the world average [PDG 2016]
    void lnL_ckm_Vusmin(double& result_ckm)
    {
      using namespace Pipes::lnL_ckm_Vusmin;
      SMInputs sminputs = *Dep::SMINPUTS;
      Matrix3cd Theta = *Dep::SeesawI_Theta;
      double V_us = *Dep::calc_Vus;

      // Fill experimental data
      triplet<double> V_us_exp[8];
      triplet<double> V_ud_exp;
      double f[8];
      fill_ckm_exp(Theta, sminputs.GF, V_us_exp, V_ud_exp, f);
 
      double chi2 = 0.0;
      for (int i=0; i<7; i++)
        chi2 += pow( (sqrt(pow(V_us,2)*f[i]) - V_us_exp[i].central) / V_us_exp[i].upper, 2);
      // According to 1407.6607 the correction for Vud is the same as K->pi e nu (f[0])
      double V_ub = 3.94e-3;
      chi2 += pow( (sqrt((1 - pow(V_us,2) - pow(V_ub,2))*f[0]) - V_ud_exp.central)/ V_ud_exp.upper/1.20, 2);
      result_ckm = -0.5*chi2;
    }
  
    // CKM unitarity constraint: V_ud should lie within 3sigma of the world average [PDG 2016]
    void lnL_ckm_Vus(double& result_ckm)
    {
      using namespace Pipes::lnL_ckm_Vus;
      SMInputs sminputs = *Dep::SMINPUTS;
      Matrix3cd Theta = *Dep::SeesawI_Theta;
      double V_us = *Param["CKM_lambda"];

      // Fill experimental data
      triplet<double> V_us_exp[8];
      triplet<double> V_ud_exp;
      double f[8];
      fill_ckm_exp(Theta, sminputs.GF, V_us_exp, V_ud_exp, f);

      double chi2 = 0.0;
      for (int i=0; i<7; i++)
        chi2 += pow( (sqrt(pow(V_us,2)*f[i]) - V_us_exp[i].central) / V_us_exp[i].upper, 2);
      // According to 1407.6607 the correction for Vud is the same as K->pi e nu (f[0])
      chi2 += pow( (sqrt((1 - pow(V_us,2))*f[0]) - V_ud_exp.central)/ V_ud_exp.upper, 2);
      result_ckm = -0.5*chi2;
    }
    
    // Likelihood contribution from PIENU; searched for extra peaks in the spectrum of pi -> mu + nu. Constrains |U_ei|^2 at 90% in the mass range 60-129 MeV. [Phys. Rev. D, 84 (052002), 2011] (arXiv:1106.4055)
    void lnL_pienu(double& result)
    {
      using namespace Pipes::lnL_pienu;

      // Mass range of experiment
      static double low_lim = 0.06060759493670887;  // GeV
      static double upp_lim = 0.12926582278481014;  // GeV
      std::vector<double> M(3), U(3), mixing_sq(3);

      mixing_sq[0] = *Dep::Ue1;
      mixing_sq[1] = *Dep::Ue2;
      mixing_sq[2] = *Dep::Ue3;
      M[0] = *Param["M_1"];
      M[1] = *Param["M_2"];
      M[2] = *Param["M_3"];

      static NeutrinoInterpolator s("NeutrinoBit/data/pienu.csv");

      // Assume Gaussian errors with zero mean and that limits scale as |U|^2.
      result = 0;
      for(int i=0; i<3; i++)
      {
        if ( (M[i] < low_lim) or (M[i] > upp_lim) )
        {
          result += -0.5*log(2.0*pi/1.28/1.28);
        }
        else
        {
          U[i] = s.eval(M[i]);
          result += Stats::gaussian_upper_limit(mixing_sq[i]/U[i], 0, 0, 1/1.28, false);  // exp_error = abs(exp_value - 90CL_value), exp_value = 0, 1.28: 90% CL limit for half-Gaussian.
        }
      }
    }

    // Likelihood contribution from PS191, electron sector; looked for charged tracks originating from RHN decays: nu_r -> l(-) + l(+) + nu / l + pi / e + pi(+) + pi(0). Constrains |U_ei|^2 at 90% in the mass range 20-450 MeV. Function also incorporates a later re-interpretation of the data to account for neutral current interaction (ignored in original) as well as the RHNs' Majorana nature. [Original: Phys. Lett. B, 203(3):332-334, 1988][Re-interp.: JHEP, 2012(6):1-27 (arXiv:1112.3319)]
    void lnL_ps191_e(double& result)
    {
      using namespace Pipes::lnL_ps191_e;

      // Mass range of experiment
      static double low_lim = 0.011810586;  // GeV
      static double upp_lim = 0.4491907842;  // GeV
      std::vector<double> M(3), U(3), mixing_sq(3);
      double c_e = 0.5711;
      double c_mu = 0.1265;
      double c_tau = 0.1265;

      mixing_sq[0] = *Dep::Ue1 * ((c_e * *Dep::Ue1) + (c_mu * *Dep::Um1) + (c_tau * *Dep::Ut1));
      mixing_sq[1] = *Dep::Ue2 * ((c_e * *Dep::Ue2) + (c_mu * *Dep::Um2) + (c_tau * *Dep::Ut2));
      mixing_sq[2] = *Dep::Ue3 * ((c_e * *Dep::Ue3) + (c_mu * *Dep::Um3) + (c_tau * *Dep::Ut3));
      M[0] = *Param["M_1"];
      M[1] = *Param["M_2"];
      M[2] = *Param["M_3"];

      static NeutrinoInterpolator s("NeutrinoBit/data/ps191_e.csv");

      // Assume scaling with |U|^4, zero bkg, number of events at 90% CL is
      // reverse engineered.  We assume that lnL = mu_sig is a faithful
      // approximation to the true Poisson likelihood.
      result = 0;
      for (int i=0; i<3; i++)
      {
        if ( (M[i] < low_lim) or (M[i] > upp_lim) )
          result += 0;
        else
        {
          U[i] = s.eval(M[i]);
          result += -2.44*(mixing_sq[i]/pow(U[i],2));
        }
      }
    }

    // Likelihood contribution from PS191, muon sector. Constrains |U_(mu,i)|^2 at 90% in the mass range 20-450 MeV. Description & references above.
    void lnL_ps191_mu(double& result)
    {
      using namespace Pipes::lnL_ps191_mu;

      // Mass range of experiment
      static double low_lim = 0.0103348894;  // GeV
      static double upp_lim = 0.3610401587;  // GeV
      std::vector<double> M(3), U(3), mixing_sq(3);
      double c_e = 0.5711;
      double c_mu = 0.1265;
      double c_tau = 0.1265;

      mixing_sq[0] = *Dep::Um1 * ((c_e * *Dep::Ue1) + (c_mu * *Dep::Um1) + (c_tau * *Dep::Ut1));
      mixing_sq[1] = *Dep::Um2 * ((c_e * *Dep::Ue2) + (c_mu * *Dep::Um2) + (c_tau * *Dep::Ut2));
      mixing_sq[2] = *Dep::Um3 * ((c_e * *Dep::Ue3) + (c_mu * *Dep::Um3) + (c_tau * *Dep::Ut3));
      M[0] = *Param["M_1"];
      M[1] = *Param["M_2"];
      M[2] = *Param["M_3"];

      static NeutrinoInterpolator s("NeutrinoBit/data/ps191_mu.csv");

      // Assume scaling with |U|^4, zero bkg, number of events at 90% CL is
      // reverse engineered.  We assume that lnL = mu_sig is a faithful
      // approximation to the true Poisson likelihood.
      result = 0;
      for (int i=0; i<3; i++)
      {
        if ( (M[i] < low_lim) or (M[i] > upp_lim) )
          result += 0;
        else
        {
          U[i] = s.eval(M[i]);
          result += -2.44*(mixing_sq[i]/pow(U[i],2));
        }
      }
    }

    // Likelihood contribution from CHARM, electron sector; searched for charged and neutral current decays of RHNs. Constrains |U_ei|^2 at 90% in the mass range 0.5-2.8 GeV. [Phys. Lett. B, 166(4):473-478, 1986]
    void lnL_charm_e(double& result)
    {
      using namespace Pipes::lnL_charm_e;

      // Mass range of experiment
      static double low_lim = 0.1595725833606568;  // GeV
      static double upp_lim = 2.0814785578102417;  // GeV
      std::vector<double> M(3), U(3), mixing_sq(3);
      double c_e = 0.5711;
      double c_mu = 0.1265;
      double c_tau = 0.1265;

      mixing_sq[0] = *Dep::Ue1 * ((c_e * *Dep::Ue1) + (c_mu * *Dep::Um1) + (c_tau * *Dep::Ut1));
      mixing_sq[1] = *Dep::Ue2 * ((c_e * *Dep::Ue2) + (c_mu * *Dep::Um2) + (c_tau * *Dep::Ut2));
      mixing_sq[2] = *Dep::Ue3 * ((c_e * *Dep::Ue3) + (c_mu * *Dep::Um3) + (c_tau * *Dep::Ut3));
      M[0] = *Param["M_1"];
      M[1] = *Param["M_2"];
      M[2] = *Param["M_3"];

      static NeutrinoInterpolator s("NeutrinoBit/data/charm_e.csv");

      // Assume scaling with |U|^4, zero bkg, number of events at 90% CL is
      // reverse engineered.  We assume that lnL = mu_sig is a faithful
      // approximation to the true Poisson likelihood.
      result = 0;
      for (int i=0; i<3; i++)
      {
        if ( (M[i] < low_lim) or (M[i] > upp_lim) )
          result += 0;
        else
        {
          U[i] = s.eval(M[i])/sqrt(2);  // Division by sqrt(2) to account for Majorana nature.
          result += -2.44*(mixing_sq[i]/pow(U[i],2));
        }
      }
    }

    // Likelihood contribution from CHARM, muon sector. Constrains |U_(mu,i)|^2 at 90% in the mass range 0.5-2.8 GeV. Description & references above.
    void lnL_charm_mu(double& result)
    {
      using namespace Pipes::lnL_charm_mu;

      // Mass range of experiment
      static double low_lim = 0.4483153374997989;  // GeV
      static double upp_lim = 1.9231171483448785;  // GeV
      std::vector<double> M(3), U(3), mixing_sq(3);
      double c_e = 0.5711;
      double c_mu = 0.1265;
      double c_tau = 0.1265;

      mixing_sq[0] = *Dep::Um1 * ((c_e * *Dep::Ue1) + (c_mu * *Dep::Um1) + (c_tau * *Dep::Ut1));
      mixing_sq[1] = *Dep::Um2 * ((c_e * *Dep::Ue2) + (c_mu * *Dep::Um2) + (c_tau * *Dep::Ut2));
      mixing_sq[2] = *Dep::Um3 * ((c_e * *Dep::Ue3) + (c_mu * *Dep::Um3) + (c_tau * *Dep::Ut3));
      M[0] = *Param["M_1"];
      M[1] = *Param["M_2"];
      M[2] = *Param["M_3"];

      static NeutrinoInterpolator s("NeutrinoBit/data/charm_mu.csv");

      // Assume scaling with |U|^4, zero bkg, number of events at 90% CL is
      // reverse engineered.  We assume that lnL = mu_sig is a faithful
      // approximation to the true Poisson likelihood.
      result = 0;
      for (int i=0; i<3; i++)
      {
        if ( (M[i] < low_lim) or (M[i] > upp_lim) )
          result += 0;
        else
        {
          U[i] = s.eval(M[i])/sqrt(2);  // Division by sqrt(2) to account for Majorana nature.
          result += -2.44*(mixing_sq[i]/pow(U[i],2));
        }
      }
    }

    // Likelihood contribution from DELPHI's short-lived RHN analysis; searched for charged and neutral current decays of RHNs. Constrains |U_ei|^2, |U_(mu,i)|^2 as well as |U_(tau,i)|^2 at 95% in the mass range 3.5-50 GeV. [Z. Phys. C, 74(1):57-71, 1997]
    void lnL_delphi_short_lived(double& result)
    {
      using namespace Pipes::lnL_delphi_short_lived;

      // Mass range of experiment
      static double low_lim = 1.8102188251700203;  // GeV
      static double upp_lim = 80.00000000000006;  // GeV
      std::vector<double> M(3), U(3), mixing_sq(9);

      mixing_sq[0] = *Dep::Ue1;  // This is |U_{e1}|^2 etc
      mixing_sq[1] = *Dep::Ue2;
      mixing_sq[2] = *Dep::Ue3;
      mixing_sq[3] = *Dep::Um1;
      mixing_sq[4] = *Dep::Um2;
      mixing_sq[5] = *Dep::Um3;
      mixing_sq[6] = *Dep::Ut1;
      mixing_sq[7] = *Dep::Ut2;
      mixing_sq[8] = *Dep::Ut3;
      M[0] = *Param["M_1"];
      M[1] = *Param["M_2"];
      M[2] = *Param["M_3"];

      static NeutrinoInterpolator s("NeutrinoBit/data/delphi_short_lived.csv");

      // Assume scaling with |U|^4, zero bkg, number of events at 95% CL is
      // reverse engineered.  We assume that lnL = mu_sig is a faithful
      // approximation to the true Poisson likelihood.
      result = 0;
      for (int i=0; i<3; i++)
      {
        if ( (M[i] < low_lim) or (M[i] > upp_lim) )
          result += 0;
        else
        {
          for (int j=i; j<9; j+=3)
          {
            U[i] = s.eval(M[i]);
            result += -3.09*(pow(mixing_sq[j]/U[i],2));
          }
        }
      }
    }

    // Likelihood contribution from DELPHI's long-lived RHN analysis; searched for charged and neutral current decays of RHNs. Constrains |U_ei|^2, |U_(mu,i)|^2 as well as |U_(tau,i)|^2 at 95% in the mass range 0.5-4.2 GeV. [Z. Phys. C, 74(1):57-71, 1997]
    void lnL_delphi_long_lived(double& result)
    {
      using namespace Pipes::lnL_delphi_long_lived;

      // Mass range of experiment
      static double low_lim = 0.4383563;  // GeV
      static double upp_lim = 4.1954595;  // GeV
      std::vector<double> M(3), U(3), mixing_sq(9);

      mixing_sq[0] = *Dep::Ue1;  // This is |U_{e1}|^2 etc
      mixing_sq[1] = *Dep::Ue2;
      mixing_sq[2] = *Dep::Ue3;
      mixing_sq[3] = *Dep::Um1;
      mixing_sq[4] = *Dep::Um2;
      mixing_sq[5] = *Dep::Um3;
      mixing_sq[6] = *Dep::Ut1;
      mixing_sq[7] = *Dep::Ut2;
      mixing_sq[8] = *Dep::Ut3;
      M[0] = *Param["M_1"];
      M[1] = *Param["M_2"];
      M[2] = *Param["M_3"];

      static NeutrinoInterpolator s("NeutrinoBit/data/delphi_long_lived.csv");

      // Assume scaling with |U|^4, zero bkg, number of events at 95% CL is
      // reverse engineered.  We assume that lnL = mu_sig is a faithful
      // approximation to the true Poisson likelihood.
      result = 0;
      for (int i=0; i<3; i++)
      {
        if ( (M[i] < low_lim) or (M[i] > upp_lim) )
          result += 0;
        else
        {
          for (int j=i; j<9; j+=3)
          {
            U[i] = s.eval(M[i]);
            result += -3.09*(pow(mixing_sq[j]/U[i],2));
          }
        }
      }
    }

    // Likelihood contribution from ATLAS, electron sector; looked at the production and decay chain: pp -> W*(+-) -> l(+-) + nu_r. nu_r then decays into an on-shell W and a lepton; the W decays primarily into a qq pair. Constrains |U_ei|^2 at 95% in the mass range 50-500 GeV. [JHEP, 07:162, 2015 (arXiv:1506.06020)]
    void lnL_atlas_e(double& result)
    {
      using namespace Pipes::lnL_atlas_e;

      // Mass range of experiment
      static double low_lim = 100.1041668;  // GeV
      static double upp_lim = 476.1458333;  // GeV
      std::vector<double> M(3), U(3), mixing_sq(3);

      mixing_sq[0] = *Dep::Ue1;
      mixing_sq[1] = *Dep::Ue2;
      mixing_sq[2] = *Dep::Ue3;
      M[0] = *Param["M_1"];
      M[1] = *Param["M_2"];
      M[2] = *Param["M_3"];

      static NeutrinoInterpolator s("NeutrinoBit/data/atlas_e.csv");

      // Assume Gaussian errors with zero mean and that limits scale as |U|^4.
      result = 0;
      for(int i=0; i<3; i++)
      {
        if ( (M[i] < low_lim) or (M[i] > upp_lim) )
        {
          result += -0.5*log(2.0*pi/1.64/1.64);
        }
        else
        {
          U[i] = s.eval(M[i]);
          result += Stats::gaussian_upper_limit(pow(mixing_sq[i]/U[i],2), 0, 0, 1/1.64, false);  // exp_error = abs(exp_value - 95CL_value), exp_value = 0, 1.64: 95% CL limit for half-Gaussian.
        }
      }
    }

    // Likelihood contribution from ATLAS, muon sector. Constrains |U_(mu,i)|^2 at 95% in the mass range 50-500 GeV. Description & references above.
    void lnL_atlas_mu(double& result)
    {
      using namespace Pipes::lnL_atlas_mu;

      // Mass range of experiment
      static double low_lim = 101.89094090419824;  // GeV
      static double upp_lim = 500.76903192219294;  // GeV
      std::vector<double> M(3), U(3), mixing_sq(3);

      mixing_sq[0] = *Dep::Um1;
      mixing_sq[1] = *Dep::Um2;
      mixing_sq[2] = *Dep::Um3;
      M[0] = *Param["M_1"];
      M[1] = *Param["M_2"];
      M[2] = *Param["M_3"];

      static NeutrinoInterpolator s("NeutrinoBit/data/atlas_mu.csv");

      // Assume Gaussian errors with zero mean and that limits scale as |U|^4.
      result = 0;
      for(int i=0; i<3; i++)
      {
        if ( (M[i] < low_lim) or (M[i] > upp_lim) )
        {
          result += -0.5*log(2.0*pi/1.64/1.64);
        }
        else
        {
          U[i] = s.eval(M[i]);
          result += Stats::gaussian_upper_limit(pow(mixing_sq[i]/U[i],2), 0, 0, 1/1.64, false); // exp_error = abs(exp_value - 95CL_value), exp_value = 0, 1.64: 95% CL limit for half-Gaussian.
        }
      }
    }

    // Likelihood contribution from E949; used the kaon decay: K(+) -> mu(+) + nu_r. Constrains |U_(mu,i)|^2 at 90% in the mass range 175-300 MeV. [Phys. Rev. D, 91, 052001 (2015) (arXiv:1411.3963v2)]
    void lnL_e949(double& result)
    {
      using namespace Pipes::lnL_e949;

      // Mass range of experiment
      static double low_lim = 0.1794613032227713;  // GeV
      static double upp_lim = 0.2995365796283227;  // GeV
      std::vector<double> M(3), U(3), mixing_sq(3);

      mixing_sq[0] = *Dep::Um1;
      mixing_sq[1] = *Dep::Um2;
      mixing_sq[2] = *Dep::Um3;
      M[0] = *Param["M_1"];
      M[1] = *Param["M_2"];
      M[2] = *Param["M_3"];

      static NeutrinoInterpolator s("NeutrinoBit/data/e949.csv");

      // Assume Gaussian errors with zero mean and that limits scale as |U|^2.
      result = 0;
      for(int i=0; i<3; i++)
      {
        if ( (M[i] < low_lim) or (M[i] > upp_lim) )
        {
          result += -0.5*log(2.0*pi/1.28/1.28);
        }
        else
        {
          U[i] = s.eval(M[i])/sqrt(2);  // Division by sqrt(2) to account for Majorana nature.
          result += Stats::gaussian_upper_limit(mixing_sq[i]/U[i], 0, 0,  1/1.28, false); // exp_error = abs(exp_value - 90CL_value), exp_value = 0, 1.28: 90% CL limit for half-Gaussian.
        }
      }
    }

    // Likelihood contribution from NuTeV; used RHN decays into muonic final states (mu + mu + nu / mu + e + nu / mu + pi / mu + rho). Constrains |U_(mu,i)|^2 at 90% CL in the mass range 0.25-2 GeV. [Phys. Rev. Lett., 83:4943-4946, 1999 (arXiv:hep-ex/9908011)]
    void lnL_nutev(double& result)
    {
      using namespace Pipes::lnL_nutev;

      // Mass range of experiment
      static double low_lim = 0.2116390354;  // GeV
      static double upp_lim = 2.0161957132;  // GeV
      std::vector<double> M(3), U(3), mixing_sq(3);

      mixing_sq[0] = *Dep::Um1;
      mixing_sq[1] = *Dep::Um2;
      mixing_sq[2] = *Dep::Um3;
      M[0] = *Param["M_1"];
      M[1] = *Param["M_2"];
      M[2] = *Param["M_3"];

      static NeutrinoInterpolator s("NeutrinoBit/data/nutev.csv");

      // Assume scaling with |U|^4, zero bkg, number of events at 90% CL is
      // reverse engineered.  We assume that lnL = mu_sig is a faithful
      // approximation to the true Poisson likelihood.
      result = 0;
      for (int i=0; i<3; i++)
      {
        if ( (M[i] < low_lim) or (M[i] > upp_lim) )
          result += 0;
        else
        {
          U[i] = s.eval(M[i]);
          result += -2.44*(pow(mixing_sq[i]/U[i],2));
        }
      }
    }

    // Likelihood contribution from a re-interpretation of CHARM data; assumes tau mixing is dominant. Constrains |U_(tau,i)|^2 at 90% CL in the mass range 10-290 MeV. [Phys. Lett. B, 550(1-2):8-15, 2002 (arXiv:hep-ph/0208075)]
    void lnL_charm_tau(double& result)
    {
      using namespace Pipes::lnL_charm_tau;

      // Mass range of experiment
      static double low_lim = 0.010685579196217497;  // GeV
      static double upp_lim = 0.288745725563687;  // GeV
      std::vector<double> M(3), U(3), mixing_sq(3);

      mixing_sq[0] = *Dep::Ut1;
      mixing_sq[1] = *Dep::Ut2;
      mixing_sq[2] = *Dep::Ut3;
      M[0] = *Param["M_1"];
      M[1] = *Param["M_2"];
      M[2] = *Param["M_3"];

      static NeutrinoInterpolator s("NeutrinoBit/data/tau.csv");

      // Assume Gaussian errors with zero mean and that limits scale as |U|^4.
      result = 0;
      for(int i=0; i<3; i++)
      {
        if ( (M[i] < low_lim) or (M[i] > upp_lim) )
        {
          result += -0.5*log(2*pi/1.28/1.28);
        }
        else
        {
          U[i] = s.eval(M[i])/sqrt(2);  // Division by sqrt(2) to account for Majorana nature.
          result += Stats::gaussian_upper_limit(pow(mixing_sq[i]/U[i],2), 0, 0, 1/1.28, false); // exp_error = abs(exp_value - 95CL_value), exp_value = 0, 1.28: 90% CL limit for half-Gaussian.
        }
      }
    }

    // Likelihood contribution from LHC (CMS), electron sector; looked at the production and decay chain: pp -> W*(+-) -> l(+-) + nu_r. nu_r then decays into an on-shell W and a lepton; the W decays primarily into a qq pair. Constrains |U_ei|^2 at 95% in the mass range 1-1.2e3 GeV. [arXiv:1802.02965v1]
    void lnL_lhc_e(double& result)
    {
      using namespace Pipes::lnL_lhc_e;

      // Mass range of experiment
      static double low_lim = 1.0293246;  // GeV
      static double upp_lim = 1e3;  // GeV
      std::vector<double> M(3), U(3), mixing_sq(3);

      mixing_sq[0] = *Dep::Ue1;
      mixing_sq[1] = *Dep::Ue2;
      mixing_sq[2] = *Dep::Ue3;
      M[0] = *Param["M_1"];
      M[1] = *Param["M_2"];
      M[2] = *Param["M_3"];

      static NeutrinoInterpolator s("NeutrinoBit/data/lhc_e.csv");

      // Assume Gaussian errors with zero mean and that limits scale as |U|^4.
      result = 0;
      for(int i=0; i<3; i++)
      {
        if ( (M[i] < low_lim) or (M[i] > upp_lim) )
        {
          result += -0.5*log(2.0*pi/1.64/1.64);
        }
        else
        {
          U[i] = s.eval(M[i]);
          result += Stats::gaussian_upper_limit(pow(mixing_sq[i]/U[i],2), 0, 0, 1/1.64, false);  // exp_error = abs(exp_value - 95CL_value), exp_value = 0, 1.64: 95% CL limit for half-Gaussian.
        }
      }
    }

    // Likelihood contribution from LHC (CMS), muon sector. Constrains |U_(mu,i)|^2 at 95% in the mass range 1-1.2e3 GeV. Description and references above.
    void lnL_lhc_mu(double& result)
    {
      using namespace Pipes::lnL_lhc_mu;

      // Mass range of experiment
      static double low_lim = 1.0145564;  // GeV
      static double upp_lim = 985.652549;  // GeV
      std::vector<double> M(3), U(3), mixing_sq(3);

      mixing_sq[0] = *Dep::Um1;
      mixing_sq[1] = *Dep::Um2;
      mixing_sq[2] = *Dep::Um3;
      M[0] = *Param["M_1"];
      M[1] = *Param["M_2"];
      M[2] = *Param["M_3"];

      static NeutrinoInterpolator s("NeutrinoBit/data/lhc_mu.csv");

      // Assume Gaussian errors with zero mean and that limits scale as |U|^4.
      result = 0;
      for(int i=0; i<3; i++)
      {
        if ( (M[i] < low_lim) or (M[i] > upp_lim) )
        {
          result += -0.5*log(2.0*pi/1.64/1.64);
        }
        else
        {
          U[i] = s.eval(M[i]);
          result += Stats::gaussian_upper_limit(pow(mixing_sq[i]/U[i],2), 0, 0, 1/1.64, false);  // exp_error = abs(exp_value - 95CL_value), exp_value = 0, 1.64: 95% CL limit for half-Gaussian.
        }
      }
    }

    // Squared matrix element |Theta(1,1)|^2
    void Ue1(double& Ue1_sq)
    {
      using namespace Pipes::Ue1;
      Ue1_sq = ((*Dep::SeesawI_Theta).cwiseAbs2())(0,0);

      #ifdef NEUTRINOBIT_DEBUG
        cout << "Ue1 = " << Ue1_sq << endl;
      #endif

      double upper_limit = runOptions->getValueOrDef<double>(-1, "upper_limit");
      double lower_limit = runOptions->getValueOrDef<double>(-1, "lower_limit");

      if( (upper_limit != -1 and Ue1_sq > upper_limit) or (lower_limit != -1 and Ue1_sq < lower_limit) )
      {
        std::ostringstream msg;
        msg << "Coupling outside of given limits";
        logger() << msg.str() << EOM;
        invalid_point().raise(msg.str());
      }
    }

    // Phase of matrix element Theta(1,1)
    void Ue1_phase(double& Ue1_p)
    {
      using namespace Pipes::Ue1_phase;
      Ue1_p = std::arg((*Dep::SeesawI_Theta)(0,0));
    }

    // Squared matrix element |Theta(2,1)|^2
    void Um1(double& Um1_sq)
    {
      using namespace Pipes::Um1;
      Um1_sq = (Dep::SeesawI_Theta->cwiseAbs2())(1,0);

      #ifdef NEUTRINOBIT_DEBUG
        cout << "Um1 = " << Um1_sq << endl;
      #endif

      double upper_limit = runOptions->getValueOrDef<double>(-1, "upper_limit");
      double lower_limit = runOptions->getValueOrDef<double>(-1, "lower_limit");

      if( (upper_limit != -1 and Um1_sq > upper_limit) or (lower_limit != -1 and Um1_sq < lower_limit) )
      {
        std::ostringstream msg;
        msg << "Coupling outside of given limits";
        logger() << msg.str() << EOM;
        invalid_point().raise(msg.str());
      }
 
    }

    // Phase of matrix element Theta(2,1)
    void Um1_phase(double& Um1_p)
    {
      using namespace Pipes::Um1_phase;
      Um1_p = std::arg((*Dep::SeesawI_Theta)(1,0));
    }

    // Squared matrix element |Theta(3,1)|^2
    void Ut1(double& Ut1_sq)
    {
      using namespace Pipes::Ut1;
      Ut1_sq = (Dep::SeesawI_Theta->cwiseAbs2())(2,0);

      #ifdef NEUTRINOBIT_DEBUG
        cout << "Ut1 = " << Ut1_sq << endl;
      #endif

      double upper_limit = runOptions->getValueOrDef<double>(-1, "upper_limit");
      double lower_limit = runOptions->getValueOrDef<double>(-1, "lower_limit");

      if( (upper_limit != -1 and Ut1_sq > upper_limit) or (lower_limit != -1 and Ut1_sq < lower_limit) )
      {
        std::ostringstream msg;
        msg << "Coupling outside of given limits";
        logger() << msg.str() << EOM;
        invalid_point().raise(msg.str());
      }
 
    }

    // Phase of matrix element Theta(3,1)
    void Ut1_phase(double& Ut1_p)
    {
      using namespace Pipes::Ut1_phase;
      Ut1_p = std::arg((*Dep::SeesawI_Theta)(2,0));
    }

    // Squared matrix element |Theta(1,2)|^2
    void Ue2(double& Ue2_sq)
    {
      using namespace Pipes::Ue2;
      Ue2_sq = (Dep::SeesawI_Theta->cwiseAbs2())(0,1);

      #ifdef NEUTRINOBIT_DEBUG
        cout << "Ue2 = " << Ue2_sq << endl;
      #endif

      double upper_limit = runOptions->getValueOrDef<double>(-1, "upper_limit");
      double lower_limit = runOptions->getValueOrDef<double>(-1, "lower_limit");

      if( (upper_limit != -1 and Ue2_sq > upper_limit) or (lower_limit != -1 and Ue2_sq < lower_limit) )
      {
        std::ostringstream msg;
        msg << "Coupling outside of given limits";
        logger() << msg.str() << EOM;
        invalid_point().raise(msg.str());
      }
 
    }

    // Phase of matrix element Theta(1,2)
    void Ue2_phase(double& Ue2_p)
    {
      using namespace Pipes::Ue2_phase;
      Ue2_p = std::arg((*Dep::SeesawI_Theta)(0,1));
    }

    // Squared matrix element |Theta(2,2)|^2
    void Um2(double& Um2_sq)
    {
      using namespace Pipes::Um2;
      Um2_sq = (Dep::SeesawI_Theta->cwiseAbs2())(1,1);
 
      #ifdef NEUTRINOBIT_DEBUG
        cout << "Um2 = " << Um2_sq << endl;
      #endif

      double upper_limit = runOptions->getValueOrDef<double>(-1, "upper_limit");
      double lower_limit = runOptions->getValueOrDef<double>(-1, "lower_limit");

      if( (upper_limit != -1 and Um2_sq > upper_limit) or (lower_limit != -1 and Um2_sq < lower_limit) )
      {
        std::ostringstream msg;
        msg << "Coupling outside of given limits";
        logger() << msg.str() << EOM;
        invalid_point().raise(msg.str());
      }
 
    }

    // Phase of matrix element Theta(2,2)
    void Um2_phase(double& Um2_p)
    {
      using namespace Pipes::Um2_phase;
      Um2_p = std::arg((*Dep::SeesawI_Theta)(1,1));
    }

    // Squared matrix element |Theta(3,2)|^2
    void Ut2(double& Ut2_sq)
    {
      using namespace Pipes::Ut2;
      Ut2_sq = (Dep::SeesawI_Theta->cwiseAbs2())(2,1);

      #ifdef NEUTRINOBIT_DEBUG
        cout << "Ut2 = " << Ut2_sq << endl;
      #endif

      double upper_limit = runOptions->getValueOrDef<double>(-1, "upper_limit");
      double lower_limit = runOptions->getValueOrDef<double>(-1, "lower_limit");

      if( (upper_limit != -1 and Ut2_sq > upper_limit) or (lower_limit != -1 and Ut2_sq < lower_limit) )
      {
        std::ostringstream msg;
        msg << "Coupling outside of given limits";
        logger() << msg.str() << EOM;
        invalid_point().raise(msg.str());
      }
 
    }

    // Phase of matrix element Theta(3,2)
    void Ut2_phase(double& Ut2_p)
    {
      using namespace Pipes::Ut2_phase;
      Ut2_p = std::arg((*Dep::SeesawI_Theta)(2,1));
    }

    // Squared matrix element |Theta(1,3)|^2
    void Ue3(double& Ue3_sq)
    {
      using namespace Pipes::Ue3;
      Ue3_sq = (Dep::SeesawI_Theta->cwiseAbs2())(0,2);

      #ifdef NEUTRINOBIT_DEBUG
        cout << "Ue3 = " << Ue3_sq << endl;
      #endif

      double upper_limit = runOptions->getValueOrDef<double>(-1, "upper_limit");
      double lower_limit = runOptions->getValueOrDef<double>(-1, "lower_limit");

      if( (upper_limit != -1 and Ue3_sq > upper_limit) or (lower_limit != -1 and Ue3_sq < lower_limit) )
      {
        std::ostringstream msg;
        msg << "Coupling outside of given limits";
        logger() << msg.str() << EOM;
        invalid_point().raise(msg.str());
      }
 
    }

    // Phase of matrix element Theta(1,3)
    void Ue3_phase(double& Ue3_p)
    {
      using namespace Pipes::Ue3_phase;
      Ue3_p = std::arg((*Dep::SeesawI_Theta)(0,2));
    }

    // Squared matrix element |Theta(2,3)|^2
    void Um3(double& Um3_sq)
    {
      using namespace Pipes::Um3;
      Um3_sq = (Dep::SeesawI_Theta->cwiseAbs2())(1,2);

      #ifdef NEUTRINOBIT_DEBUG
        cout << "Um3 = " << Um3_sq << endl;
      #endif

      double upper_limit = runOptions->getValueOrDef<double>(-1, "upper_limit");
      double lower_limit = runOptions->getValueOrDef<double>(-1, "lower_limit");

      if( (upper_limit != -1 and Um3_sq > upper_limit) or (lower_limit != -1 and Um3_sq < lower_limit) )
      {
        std::ostringstream msg;
        msg << "Coupling outside of given limits";
        logger() << msg.str() << EOM;
        invalid_point().raise(msg.str());
      }
 
    }

    // Phase of matrix element Theta(2,3)
    void Um3_phase(double& Um3_p)
    {
      using namespace Pipes::Um3_phase;
      Um3_p = std::arg((*Dep::SeesawI_Theta)(1,2));
    }

    // Squared matrix element |Theta(3,3)|^2
    void Ut3(double& Ut3_sq)
    {
      using namespace Pipes::Ut3;
      Ut3_sq = (Dep::SeesawI_Theta->cwiseAbs2())(2,2);

      #ifdef NEUTRINOBIT_DEBUG
        cout << "Ut3 = " << Ut3_sq << endl;
      #endif

      double upper_limit = runOptions->getValueOrDef<double>(-1, "upper_limit");
      double lower_limit = runOptions->getValueOrDef<double>(-1, "lower_limit");

      if( (upper_limit != -1 and Ut3_sq > upper_limit) or (lower_limit != -1 and Ut3_sq < lower_limit) )
      {
        std::ostringstream msg;
        msg << "Coupling outside of given limits";
        logger() << msg.str() << EOM;
        invalid_point().raise(msg.str());
      }
 
    }

    // Phase of matrix element Theta(3,3)
    void Ut3_phase(double& Ut3_p)
    {
      using namespace Pipes::Ut3_phase;
      Ut3_p = std::arg((*Dep::SeesawI_Theta)(2,2));
    }

    // Step-function log likelihood on the perturbativity of the Yukawas
    void perturbativity_likelihood(double &lnL)
    {
      using namespace Pipes::perturbativity_likelihood;
      SMInputs sminputs = *Dep::SMINPUTS;

      Matrix3d MN;
      MN << *Param["M_1"], 0, 0,
            0, *Param["M_2"], 0,
            0, 0, *Param["M_3"];

      double vev= 1. / sqrt(sqrt(2.)*sminputs.GF);

      // Yukawa coupling |F|^2 from eq 26 in 1502.00477
      Matrix3cd F2 = 1.0/pow(vev,2) * *Dep::SeesawI_Theta * Dep::SeesawI_Theta->adjoint() * MN * MN;
      
      lnL = 0;
      for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
          if(F2(i,j).real() >= 4*pi) 
          {
            std::ostringstream msg;
            msg << "Yukawas not perturbative; point invalidated.";
            logger() << msg.str() << EOM;
            invalid_point().raise(msg.str());
            return ;
          }
    }

    // Artificial slide likelihood on couplings and masses
    void coupling_slide(double &lnL)
    {
      using namespace Pipes::coupling_slide;
      int I = runOptions->getValueOrDef<int>(1, "I");
      int flavour = runOptions->getValueOrDef<int>(1, "i");
      double slope = runOptions->getValueOrDef<double>(1, "slope");
      double mslope = runOptions->getValueOrDef<double>(0, "mslope");
      std::vector<double> M(3);
      M[0] = *Param["M_1"];
      M[1] = *Param["M_2"];
      M[2] = *Param["M_3"];

      if (flavour > 0)
      {
        double U = (Dep::SeesawI_Theta->cwiseAbs2())(flavour-1,I-1);
        lnL = slope*log10(std::min(U, 1.)) + mslope*log10(M[I-1]);
      }
      else
      {
        double U1 = (Dep::SeesawI_Theta->cwiseAbs2())(0, I-1);
        double U2 = (Dep::SeesawI_Theta->cwiseAbs2())(1, I-1);
        double U3 = (Dep::SeesawI_Theta->cwiseAbs2())(2, I-1);
        lnL = 0;
        lnL += slope*log10(std::min(U1, 1.)) + mslope*log10(M[I-1]);
        lnL += slope*log10(std::min(U2, 1.)) + mslope*log10(M[I-1]);
        lnL += slope*log10(std::min(U3, 1.)) + mslope*log10(M[I-1]);
      }
    }
  }
}
