//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Rollcall header for NeutrinoBit.
///
///  Compile-time registration of available
///  observables and likelihoods for neutrino observables.
///
///  Don't put typedefs or other type definitions
///  in this file; see
///  Core/include/types_rollcall.hpp for further
///  instructions on how to add new types.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Suraj Krishnamurthy
///          (S.Krishnamurthy@uva.nl)
///  \date 2017 Feb
///
///  \author Tomas Gonzalo
///          (t.e.gonzalo@fys.uio.no)
///  \date 2017 July
///  \date 2018
///  \date 2019
///
///  \author Julia Harz
///          (jharz@lpthe.jussieu.fr)
///  \date 2018 April
///  *********************************************


#ifndef __NeutrinoBit_rollcall_hpp__
#define __NeutrinoBit_rollcall_hpp__

#include <Eigen/Sparse>
#include <Eigen/Dense>

#define MODULE NeutrinoBit
START_MODULE

  #define CAPABILITY ordering
  START_CAPABILITY
    #define FUNCTION ordering
    START_FUNCTION(bool)
    ALLOW_MODEL(StandardModel_SLHA2)
    #undef FUNCTION
  #undef CAPABILITY

  // Neutrino mass matrix
  #define CAPABILITY m_nu
  START_CAPABILITY
    // Neutrino masss matrix
    #define FUNCTION M_nu
    START_FUNCTION(Eigen::Matrix3cd)
    DEPENDENCY(ordering, bool)
    ALLOW_MODELS(StandardModel_SLHA2)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY md21
  START_CAPABILITY
    #define FUNCTION md21
    START_FUNCTION(double)
    DEPENDENCY(m_nu, Eigen::Matrix3cd)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY md31
  START_CAPABILITY
    #define FUNCTION md31
    START_FUNCTION(double)
    DEPENDENCY(m_nu, Eigen::Matrix3cd)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY md32
  START_CAPABILITY
    #define FUNCTION md32
    START_FUNCTION(double)
    DEPENDENCY(m_nu, Eigen::Matrix3cd)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY min_mass
  START_CAPABILITY
    #define FUNCTION min_mass
    START_FUNCTION(double)
    DEPENDENCY(m_nu, Eigen::Matrix3cd)
    DEPENDENCY(ordering, bool)
    #undef FUNCTION
  #undef CAPABILITY

  // Construct the neutrino PMNS matrix
  #define CAPABILITY UPMNS
  START_CAPABILITY
    // Neutrino PMNS matrix in a parametrization where the charged Yukawas are diagonal
    #define FUNCTION UPMNS
    START_FUNCTION(Eigen::Matrix3cd)
    ALLOW_MODELS(StandardModel_SLHA2)
    #undef FUNCTION
  #undef CAPABILITY

  // Construct the neutrino Seesaw I type Theta matrix
  #define CAPABILITY SeesawI_Theta
  START_CAPABILITY
    // Theta in the Casas-Ibarra parametrization
    #define FUNCTION CI_Theta
    START_FUNCTION(Eigen::Matrix3cd)
    DEPENDENCY(m_nu, Eigen::Matrix3cd)
    DEPENDENCY(UPMNS, Eigen::Matrix3cd)
    DEPENDENCY(SMINPUTS, SMInputs)
    ALLOW_JOINT_MODEL(StandardModel_Higgs, RightHandedNeutrinos)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY SeesawI_Vnu
  START_CAPABILITY
    #define FUNCTION Vnu
    START_FUNCTION(Eigen::Matrix3cd)
    DEPENDENCY(UPMNS, Eigen::Matrix3cd)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    ALLOW_MODELS(RightHandedNeutrinos)
    #undef FUNCTION
  #undef CAPABILITY

  // Unitarity checks for the mixing matrix
  #define CAPABILITY Unitarity
  START_CAPABILITY
    // Unitarity of the PMNS matrix
    #define FUNCTION Unitarity_UPMNS
    START_FUNCTION(bool)
    DEPENDENCY(UPMNS, Eigen::Matrix3cd)
    DEPENDENCY(m_nu, Eigen::Matrix3cd)
    #undef FUNCTION

    // Unitarity of the mixing matrix in seesaw I
    #define FUNCTION Unitarity_SeesawI
    START_FUNCTION(bool)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    DEPENDENCY(SeesawI_Vnu, Eigen::Matrix3cd)
    DEPENDENCY(m_nu, Eigen::Matrix3cd)
    ALLOW_MODEL(RightHandedNeutrinos)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Ue1
  START_CAPABILITY
    #define FUNCTION Ue1
    START_FUNCTION(double)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Ue1_phase
  START_CAPABILITY
    #define FUNCTION Ue1_phase
    START_FUNCTION(double)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Um1
  START_CAPABILITY
    #define FUNCTION Um1
    START_FUNCTION(double)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Um1_phase
  START_CAPABILITY
    #define FUNCTION Um1_phase
    START_FUNCTION(double)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Ut1
  START_CAPABILITY
    #define FUNCTION Ut1
    START_FUNCTION(double)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Ut1_phase
  START_CAPABILITY
    #define FUNCTION Ut1_phase
    START_FUNCTION(double)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Ue2
  START_CAPABILITY
    #define FUNCTION Ue2
    START_FUNCTION(double)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Ue2_phase
  START_CAPABILITY
    #define FUNCTION Ue2_phase
    START_FUNCTION(double)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Um2
  START_CAPABILITY
    #define FUNCTION Um2
    START_FUNCTION(double)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Um2_phase
  START_CAPABILITY
    #define FUNCTION Um2_phase
    START_FUNCTION(double)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Ut2
  START_CAPABILITY
    #define FUNCTION Ut2
    START_FUNCTION(double)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Ut2_phase
  START_CAPABILITY
    #define FUNCTION Ut2_phase
    START_FUNCTION(double)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Ue3
  START_CAPABILITY
    #define FUNCTION Ue3
    START_FUNCTION(double)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Ue3_phase
  START_CAPABILITY
    #define FUNCTION Ue3_phase
    START_FUNCTION(double)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Um3
  START_CAPABILITY
    #define FUNCTION Um3
    START_FUNCTION(double)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Um3_phase
  START_CAPABILITY
    #define FUNCTION Um3_phase
    START_FUNCTION(double)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Ut3
  START_CAPABILITY
    #define FUNCTION Ut3
    START_FUNCTION(double)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Ut3_phase
  START_CAPABILITY
    #define FUNCTION Ut3_phase
    START_FUNCTION(double)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Gamma_RHN2piplusl
  START_CAPABILITY
    #define FUNCTION Gamma_RHN2piplusl
    START_FUNCTION(std::vector<double>)
    DEPENDENCY(SMINPUTS, SMInputs)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    ALLOW_JOINT_MODEL(RightHandedNeutrinos, StandardModel_SLHA2)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Gamma_RHN2Kplusl
  START_CAPABILITY
    #define FUNCTION Gamma_RHN2Kplusl
    START_FUNCTION(std::vector<double>)
    DEPENDENCY(SMINPUTS, SMInputs)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    ALLOW_JOINT_MODEL(RightHandedNeutrinos, StandardModel_SLHA2)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Gamma_RHN2Dplusl
  START_CAPABILITY
    #define FUNCTION Gamma_RHN2Dplusl
    START_FUNCTION(std::vector<double>)
    DEPENDENCY(SMINPUTS, SMInputs)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    ALLOW_JOINT_MODEL(RightHandedNeutrinos, StandardModel_SLHA2)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Gamma_RHN2Dsl
  START_CAPABILITY
    #define FUNCTION Gamma_RHN2Dsl
    START_FUNCTION(std::vector<double>)
    DEPENDENCY(SMINPUTS, SMInputs)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    ALLOW_JOINT_MODEL(RightHandedNeutrinos, StandardModel_SLHA2)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Gamma_RHN2Bplusl
  START_CAPABILITY
    #define FUNCTION Gamma_RHN2Bplusl
    START_FUNCTION(std::vector<double>)
    DEPENDENCY(SMINPUTS, SMInputs)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    ALLOW_JOINT_MODEL(RightHandedNeutrinos, StandardModel_SLHA2)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Gamma_RHN2Bcl
  START_CAPABILITY
    #define FUNCTION Gamma_RHN2Bcl
    START_FUNCTION(std::vector<double>)
    DEPENDENCY(SMINPUTS, SMInputs)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    ALLOW_JOINT_MODEL(RightHandedNeutrinos, StandardModel_SLHA2)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Gamma_RHN2pi0nu
  START_CAPABILITY
    #define FUNCTION Gamma_RHN2pi0nu
    START_FUNCTION(std::vector<double>)
    DEPENDENCY(SMINPUTS, SMInputs)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    ALLOW_MODELS(RightHandedNeutrinos)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Gamma_RHN2etanu
  START_CAPABILITY
    #define FUNCTION Gamma_RHN2etanu
    START_FUNCTION(std::vector<double>)
    DEPENDENCY(SMINPUTS, SMInputs)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    ALLOW_MODEL(RightHandedNeutrinos)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Gamma_RHN2etaprimenu
  START_CAPABILITY
    #define FUNCTION Gamma_RHN2etaprimenu
    START_FUNCTION(std::vector<double>)
    DEPENDENCY(SMINPUTS, SMInputs)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    ALLOW_MODEL(RightHandedNeutrinos)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Gamma_RHN2etacnu
  START_CAPABILITY
    #define FUNCTION Gamma_RHN2etacnu
    START_FUNCTION(std::vector<double>)
    DEPENDENCY(SMINPUTS, SMInputs)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    ALLOW_MODEL(RightHandedNeutrinos)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Gamma_RHN2rhoplusl
  START_CAPABILITY
    #define FUNCTION Gamma_RHN2rhoplusl
    START_FUNCTION(std::vector<double>)
    DEPENDENCY(SMINPUTS, SMInputs)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    ALLOW_JOINT_MODEL(RightHandedNeutrinos, StandardModel_SLHA2)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Gamma_RHN2Dstarplusl
  START_CAPABILITY
    #define FUNCTION Gamma_RHN2Dstarplusl
    START_FUNCTION(std::vector<double>)
    DEPENDENCY(SMINPUTS, SMInputs)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    ALLOW_JOINT_MODEL(RightHandedNeutrinos, StandardModel_SLHA2)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Gamma_RHN2Dstarsl
  START_CAPABILITY
    #define FUNCTION Gamma_RHN2Dstarsl
    START_FUNCTION(std::vector<double>)
    DEPENDENCY(SMINPUTS, SMInputs)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    ALLOW_JOINT_MODEL(RightHandedNeutrinos, StandardModel_SLHA2)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Gamma_RHN2rho0nu
  START_CAPABILITY
    #define FUNCTION Gamma_RHN2rho0nu
    START_FUNCTION(std::vector<double>)
    DEPENDENCY(SMINPUTS, SMInputs)
    DEPENDENCY(prec_sinW2_eff, triplet<double>)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    ALLOW_MODEL(RightHandedNeutrinos)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Gamma_RHN2omeganu
  START_CAPABILITY
    #define FUNCTION Gamma_RHN2omeganu
    START_FUNCTION(std::vector<double>)
    DEPENDENCY(SMINPUTS, SMInputs)
    DEPENDENCY(prec_sinW2_eff, triplet<double>)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    ALLOW_MODEL(RightHandedNeutrinos)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Gamma_RHN2phinu
  START_CAPABILITY
    #define FUNCTION Gamma_RHN2phinu
    START_FUNCTION(std::vector<double>)
    DEPENDENCY(SMINPUTS, SMInputs)
    DEPENDENCY(prec_sinW2_eff, triplet<double>)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    ALLOW_MODEL(RightHandedNeutrinos)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Gamma_RHN2Jpsinu
  START_CAPABILITY
    #define FUNCTION Gamma_RHN2Jpsinu
    START_FUNCTION(std::vector<double>)
    DEPENDENCY(SMINPUTS, SMInputs)
    DEPENDENCY(prec_sinW2_eff, triplet<double>)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    ALLOW_MODEL(RightHandedNeutrinos)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Gamma_RHN23nu
  START_CAPABILITY
    #define FUNCTION Gamma_RHN23nu
    START_FUNCTION(std::vector<double>)
    DEPENDENCY(SMINPUTS, SMInputs)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    ALLOW_MODEL(RightHandedNeutrinos)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Gamma_RHN2llnu
  START_CAPABILITY
    #define FUNCTION Gamma_RHN2llnu
    START_FUNCTION(std::vector<double>)
    DEPENDENCY(SMINPUTS, SMInputs)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    ALLOW_JOINT_MODEL(RightHandedNeutrinos, StandardModel_SLHA2)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Gamma_RHN2null
  START_CAPABILITY
    #define FUNCTION Gamma_RHN2null
    START_FUNCTION(std::vector<double>)
    DEPENDENCY(SMINPUTS, SMInputs)
    DEPENDENCY(prec_sinW2_eff, triplet<double>)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    ALLOW_JOINT_MODEL(RightHandedNeutrinos, StandardModel_SLHA2)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Gamma_RHN2nuuubar
  START_CAPABILITY
    #define FUNCTION Gamma_RHN2nuuubar
    START_FUNCTION(std::vector<double>)
    DEPENDENCY(SMINPUTS, SMInputs)
    DEPENDENCY(prec_sinW2_eff, triplet<double>)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    ALLOW_JOINT_MODEL(RightHandedNeutrinos, StandardModel_SLHA2)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Gamma_RHN2nuddbar
  START_CAPABILITY
    #define FUNCTION Gamma_RHN2nuddbar
    START_FUNCTION(std::vector<double>)
    DEPENDENCY(SMINPUTS, SMInputs)
    DEPENDENCY(prec_sinW2_eff, triplet<double>)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    ALLOW_JOINT_MODEL(RightHandedNeutrinos, StandardModel_SLHA2)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Gamma_RHN2ludbar
  START_CAPABILITY
    #define FUNCTION Gamma_RHN2ludbar
    START_FUNCTION(std::vector<double>)
    DEPENDENCY(SMINPUTS, SMInputs)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    ALLOW_JOINT_MODEL(RightHandedNeutrinos, StandardModel_SLHA2)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Gamma_BBN
  START_CAPABILITY
    #define FUNCTION Gamma_BBN
    START_FUNCTION(std::vector<double>)
    DEPENDENCY(Gamma_RHN2piplusl, std::vector<double>)
    DEPENDENCY(Gamma_RHN2Kplusl, std::vector<double>)
    DEPENDENCY(Gamma_RHN2Dplusl, std::vector<double>)
    DEPENDENCY(Gamma_RHN2Dsl, std::vector<double>)
    DEPENDENCY(Gamma_RHN2Bplusl, std::vector<double>)
    DEPENDENCY(Gamma_RHN2Bcl, std::vector<double>)
    DEPENDENCY(Gamma_RHN2pi0nu, std::vector<double>)
    DEPENDENCY(Gamma_RHN2etanu, std::vector<double>)
    DEPENDENCY(Gamma_RHN2etaprimenu, std::vector<double>)
    DEPENDENCY(Gamma_RHN2etacnu, std::vector<double>)
    DEPENDENCY(Gamma_RHN2rhoplusl, std::vector<double>)
    DEPENDENCY(Gamma_RHN2Dstarplusl, std::vector<double>)
    DEPENDENCY(Gamma_RHN2Dstarsl, std::vector<double>)
    DEPENDENCY(Gamma_RHN2rho0nu, std::vector<double>)
    DEPENDENCY(Gamma_RHN2omeganu, std::vector<double>)
    DEPENDENCY(Gamma_RHN2phinu, std::vector<double>)
    DEPENDENCY(Gamma_RHN2Jpsinu, std::vector<double>)
    DEPENDENCY(Gamma_RHN23nu, std::vector<double>)
    DEPENDENCY(Gamma_RHN2llnu, std::vector<double>)
    DEPENDENCY(Gamma_RHN2null, std::vector<double>)
    DEPENDENCY(Gamma_RHN2nuuubar, std::vector<double>)
    DEPENDENCY(Gamma_RHN2nuddbar, std::vector<double>)
    DEPENDENCY(Gamma_RHN2ludbar, std::vector<double>)
    ALLOW_MODELS(RightHandedNeutrinos)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lnL_bbn
  START_CAPABILITY
    #define FUNCTION lnL_bbn
    START_FUNCTION(double)
    DEPENDENCY(Gamma_BBN, std::vector<double>)
    ALLOW_MODELS(RightHandedNeutrinos)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY R_pi
  START_CAPABILITY
    #define FUNCTION RHN_R_pi
    START_FUNCTION(double)
    DEPENDENCY(SMINPUTS, SMInputs)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    DEPENDENCY(SeesawI_Vnu, Eigen::Matrix3cd)
    ALLOW_MODEL(RightHandedNeutrinos)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY R_K
  START_CAPABILITY
    #define FUNCTION RHN_R_K
    START_FUNCTION(double)
    DEPENDENCY(SMINPUTS, SMInputs)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    DEPENDENCY(SeesawI_Vnu, Eigen::Matrix3cd)
    ALLOW_MODEL(RightHandedNeutrinos)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY R_tau
  START_CAPABILITY
    #define FUNCTION RHN_R_tau
    START_FUNCTION(double)
    DEPENDENCY(SMINPUTS, SMInputs)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    ALLOW_MODEL(RightHandedNeutrinos)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY R_W
  START_CAPABILITY
    #define FUNCTION RHN_R_W
    START_FUNCTION(std::vector<double>)
    //DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    //DEPENDENCY(mw, triplet<double>)
    DEPENDENCY(W_to_l_decays, std::vector<double>)
    ALLOW_MODEL(RightHandedNeutrinos)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lnL_R_K
  START_CAPABILITY
    #define FUNCTION lnL_R_K
    START_FUNCTION(double)
    DEPENDENCY(R_K, double)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lnL_R_pi
  START_CAPABILITY
    #define FUNCTION lnL_R_pi
    START_FUNCTION(double)
    DEPENDENCY(R_pi, double)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lnL_R_tau
  START_CAPABILITY
    #define FUNCTION lnL_R_tau
    START_FUNCTION(double)
    DEPENDENCY(R_tau, double)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lnL_R_W
  START_CAPABILITY
    #define FUNCTION lnL_R_W
    START_FUNCTION(double)
    DEPENDENCY(R_W, std::vector<double>)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Thalf_0nubb_Xe
  START_CAPABILITY
    #define FUNCTION RHN_Thalf_0nubb_Xe
    START_FUNCTION(double)
    DEPENDENCY(m_nu, Eigen::Matrix3cd)
    DEPENDENCY(UPMNS, Eigen::Matrix3cd)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    ALLOW_MODEL(RightHandedNeutrinos)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lnL_0nubb_KamLAND_Zen
  START_CAPABILITY
    #define FUNCTION lnL_0nubb_KamLAND_Zen
    START_FUNCTION(double)
    DEPENDENCY(Thalf_0nubb_Xe, double)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Thalf_0nubb_Ge
  START_CAPABILITY
    #define FUNCTION RHN_Thalf_0nubb_Ge
    START_FUNCTION(double)
    DEPENDENCY(m_nu, Eigen::Matrix3cd)
    DEPENDENCY(UPMNS, Eigen::Matrix3cd)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    ALLOW_MODEL(RightHandedNeutrinos)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lnL_0nubb_GERDA
  START_CAPABILITY
    #define FUNCTION lnL_0nubb_GERDA
    START_FUNCTION(double)
    DEPENDENCY(Thalf_0nubb_Ge, double)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lnL_0nubb
  START_CAPABILITY
    #define FUNCTION lnL_0nubb
    START_FUNCTION(double) 
    DEPENDENCY(lnL_0nubb_KamLAND_Zen, double)
    DEPENDENCY(lnL_0nubb_GERDA, double)
    #undef FUNCTION
  #undef CAPABILITY
    
  #define CAPABILITY mbb_0nubb_Xe
  START_CAPABILITY
    #define FUNCTION RHN_mbb_0nubb_Xe
    START_FUNCTION(double)
    DEPENDENCY(m_nu, Eigen::Matrix3cd)
    DEPENDENCY(UPMNS, Eigen::Matrix3cd)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    ALLOW_MODEL(RightHandedNeutrinos)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lnL_mbb_0nubb_KamLAND_Zen
  START_CAPABILITY
    #define FUNCTION lnL_mbb_0nubb_KamLAND_Zen
    START_FUNCTION(double)
    DEPENDENCY(mbb_0nubb_Xe, double)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY mbb_0nubb_Ge
  START_CAPABILITY
    #define FUNCTION RHN_mbb_0nubb_Ge
    START_FUNCTION(double)
    DEPENDENCY(m_nu, Eigen::Matrix3cd)
    DEPENDENCY(UPMNS, Eigen::Matrix3cd)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    ALLOW_MODEL(RightHandedNeutrinos)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lnL_mbb_0nubb_GERDA
  START_CAPABILITY
    #define FUNCTION lnL_mbb_0nubb_GERDA
    START_FUNCTION(double)
    DEPENDENCY(mbb_0nubb_Ge, double)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lnL_mbb_0nubb
  START_CAPABILITY
    #define FUNCTION lnL_mbb_0nubb
    START_FUNCTION(double) 
    DEPENDENCY(lnL_mbb_0nubb_KamLAND_Zen, double)
    DEPENDENCY(lnL_mbb_0nubb_GERDA, double)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY calc_Vus
  START_CAPABILITY
    #define FUNCTION calc_Vus
    START_FUNCTION(double)
    DEPENDENCY(SMINPUTS, SMInputs)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    ALLOW_MODEL(RightHandedNeutrinos)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lnLckm_Vusmin
  START_CAPABILITY
    #define FUNCTION lnL_ckm_Vusmin
    START_FUNCTION(double)
    DEPENDENCY(SMINPUTS, SMInputs)
    DEPENDENCY(calc_Vus, double)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    ALLOW_MODELS(RightHandedNeutrinos)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lnLckm_Vus
  START_CAPABILITY
    #define FUNCTION lnL_ckm_Vus
    START_FUNCTION(double)
    DEPENDENCY(SMINPUTS, SMInputs)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    ALLOW_JOINT_MODEL(RightHandedNeutrinos, StandardModel_SLHA2)
    #undef FUNCTION
  #undef CAPABILITY


  #define CAPABILITY lnLpienu
  START_CAPABILITY
    #define FUNCTION lnL_pienu
    START_FUNCTION(double)
    ALLOW_MODEL(RightHandedNeutrinos)
    DEPENDENCY(Ue1, double)
    DEPENDENCY(Ue2, double)
    DEPENDENCY(Ue3, double)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lnLps191e
  START_CAPABILITY
    #define FUNCTION lnL_ps191_e
    START_FUNCTION(double)
    ALLOW_MODEL(RightHandedNeutrinos)
    DEPENDENCY(Ue1, double)
    DEPENDENCY(Ue2, double)
    DEPENDENCY(Ue3, double)
    DEPENDENCY(Um1, double)
    DEPENDENCY(Um2, double)
    DEPENDENCY(Um3, double)
    DEPENDENCY(Ut1, double)
    DEPENDENCY(Ut2, double)
    DEPENDENCY(Ut3, double)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lnLps191mu
  START_CAPABILITY
    #define FUNCTION lnL_ps191_mu
    START_FUNCTION(double)
    ALLOW_MODEL(RightHandedNeutrinos)
    DEPENDENCY(Ue1, double)
    DEPENDENCY(Ue2, double)
    DEPENDENCY(Ue3, double)
    DEPENDENCY(Um1, double)
    DEPENDENCY(Um2, double)
    DEPENDENCY(Um3, double)
    DEPENDENCY(Ut1, double)
    DEPENDENCY(Ut2, double)
    DEPENDENCY(Ut3, double)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lnLcharme
  START_CAPABILITY
    #define FUNCTION lnL_charm_e
    START_FUNCTION(double)
    ALLOW_MODEL(RightHandedNeutrinos)
    DEPENDENCY(Ue1, double)
    DEPENDENCY(Ue2, double)
    DEPENDENCY(Ue3, double)
    DEPENDENCY(Um1, double)
    DEPENDENCY(Um2, double)
    DEPENDENCY(Um3, double)
    DEPENDENCY(Ut1, double)
    DEPENDENCY(Ut2, double)
    DEPENDENCY(Ut3, double)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lnLcharmmu
  START_CAPABILITY
    #define FUNCTION lnL_charm_mu
    START_FUNCTION(double)
    ALLOW_MODEL(RightHandedNeutrinos)
    DEPENDENCY(Ue1, double)
    DEPENDENCY(Ue2, double)
    DEPENDENCY(Ue3, double)
    DEPENDENCY(Um1, double)
    DEPENDENCY(Um2, double)
    DEPENDENCY(Um3, double)
    DEPENDENCY(Ut1, double)
    DEPENDENCY(Ut2, double)
    DEPENDENCY(Ut3, double)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lnLdelphi_shortlived
  START_CAPABILITY
    #define FUNCTION lnL_delphi_short_lived
    START_FUNCTION(double)
    ALLOW_MODEL(RightHandedNeutrinos)
    DEPENDENCY(Ue1, double)
    DEPENDENCY(Ue2, double)
    DEPENDENCY(Ue3, double)
    DEPENDENCY(Um1, double)
    DEPENDENCY(Um2, double)
    DEPENDENCY(Um3, double)
    DEPENDENCY(Ut1, double)
    DEPENDENCY(Ut2, double)
    DEPENDENCY(Ut3, double)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lnLdelphi_longlived
  START_CAPABILITY
    #define FUNCTION lnL_delphi_long_lived
    START_FUNCTION(double)
    ALLOW_MODEL(RightHandedNeutrinos)
    DEPENDENCY(Ue1, double)
    DEPENDENCY(Ue2, double)
    DEPENDENCY(Ue3, double)
    DEPENDENCY(Um1, double)
    DEPENDENCY(Um2, double)
    DEPENDENCY(Um3, double)
    DEPENDENCY(Ut1, double)
    DEPENDENCY(Ut2, double)
    DEPENDENCY(Ut3, double)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lnLatlase
  START_CAPABILITY
    #define FUNCTION lnL_atlas_e
    START_FUNCTION(double)
    ALLOW_MODEL(RightHandedNeutrinos)
    DEPENDENCY(Ue1, double)
    DEPENDENCY(Ue2, double)
    DEPENDENCY(Ue3, double)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lnLatlasmu
  START_CAPABILITY
    #define FUNCTION lnL_atlas_mu
    START_FUNCTION(double)
    ALLOW_MODEL(RightHandedNeutrinos)
    DEPENDENCY(Um1, double)
    DEPENDENCY(Um2, double)
    DEPENDENCY(Um3, double)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lnLe949
  START_CAPABILITY
    #define FUNCTION lnL_e949
    START_FUNCTION(double)
    ALLOW_MODEL(RightHandedNeutrinos)
    DEPENDENCY(Um1, double)
    DEPENDENCY(Um2, double)
    DEPENDENCY(Um3, double)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lnLnutev
  START_CAPABILITY
    #define FUNCTION lnL_nutev
    START_FUNCTION(double)
    ALLOW_MODEL(RightHandedNeutrinos)
    DEPENDENCY(Um1, double)
    DEPENDENCY(Um2, double)
    DEPENDENCY(Um3, double)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lnLcharmtau
  START_CAPABILITY
    #define FUNCTION lnL_charm_tau
    START_FUNCTION(double)
    ALLOW_MODEL(RightHandedNeutrinos)
    DEPENDENCY(Ut1, double)
    DEPENDENCY(Ut2, double)
    DEPENDENCY(Ut3, double)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lnLlhce
  START_CAPABILITY
    #define FUNCTION lnL_lhc_e
    START_FUNCTION(double)
    ALLOW_MODEL(RightHandedNeutrinos)
    DEPENDENCY(Ue1, double)
    DEPENDENCY(Ue2, double)
    DEPENDENCY(Ue3, double)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lnLlhcmu
  START_CAPABILITY
    #define FUNCTION lnL_lhc_mu
    START_FUNCTION(double)
    ALLOW_MODEL(RightHandedNeutrinos)
    DEPENDENCY(Um1, double)
    DEPENDENCY(Um2, double)
    DEPENDENCY(Um3, double)
    #undef FUNCTION
  #undef CAPABILITY

  // Perturbativity of the Yukawa couplings (from arXiv:1509.02678)
  #define CAPABILITY perturbativity_lnL
  START_CAPABILITY
    #define FUNCTION perturbativity_likelihood
    START_FUNCTION(double)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    DEPENDENCY(SMINPUTS, SMInputs)
    ALLOW_MODEL(RightHandedNeutrinos)
    #undef FUNCTION
  #undef CAPABILITY

  // Active neutrino likelihoods
  #define CAPABILITY theta12
  START_CAPABILITY
    #define FUNCTION theta12
    START_FUNCTION(double)
    ALLOW_MODEL(StandardModel_SLHA2)
    #undef FUNCTION
  #undef CAPABILITY
    
  #define CAPABILITY theta12_lnL
  START_CAPABILITY
    #define FUNCTION theta12_lnL
    START_FUNCTION(double)
    DEPENDENCY(ordering, bool)
    DEPENDENCY(theta12, double)
    #undef FUNCTION
  #undef CAPABILITY  

  #define CAPABILITY theta23
  START_CAPABILITY
    #define FUNCTION theta23
    START_FUNCTION(double)
    ALLOW_MODEL(StandardModel_SLHA2)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY theta23_lnL
  START_CAPABILITY
    #define FUNCTION theta23_lnL
    START_FUNCTION(double)
    DEPENDENCY(ordering, bool)
    DEPENDENCY(theta23, double)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY theta13
  START_CAPABILITY
    #define FUNCTION theta13
    START_FUNCTION(double)
    ALLOW_MODEL(StandardModel_SLHA2)
    #undef FUNCTION
  #undef CAPABILITY
    
  #define CAPABILITY theta13_lnL
  START_CAPABILITY
    #define FUNCTION theta13_lnL
    START_FUNCTION(double)
    DEPENDENCY(ordering, bool)
    DEPENDENCY(theta13, double)
    #undef FUNCTION
  #undef CAPABILITY
 
  #define CAPABILITY deltaCP
  START_CAPABILITY
    #define FUNCTION deltaCP
    START_FUNCTION(double)
    ALLOW_MODEL(StandardModel_SLHA2)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY deltaCP_lnL
  START_CAPABILITY
    #define FUNCTION deltaCP_lnL
    START_FUNCTION(double)
    DEPENDENCY(ordering, bool)
    DEPENDENCY(deltaCP, double)
    #undef FUNCTION
  #undef CAPABILITY  
    
  #define CAPABILITY md21_lnL
  START_CAPABILITY
    #define FUNCTION md21_lnL
    START_FUNCTION(double)
    DEPENDENCY(ordering, bool)
    DEPENDENCY(md21, double)
    #undef FUNCTION
  #undef CAPABILITY  
  
  #define CAPABILITY md3l_lnL
  START_CAPABILITY
    #define FUNCTION md3l_lnL
    START_FUNCTION(double)
    DEPENDENCY(ordering, bool)
    DEPENDENCY(md31, double)
    DEPENDENCY(md32, double)
    #undef FUNCTION
  #undef CAPABILITY 

  #define CAPABILITY sum_mnu_lnL
  START_CAPABILITY
    #define FUNCTION sum_mnu_lnL
    START_FUNCTION(double)
    ALLOW_MODEL(StandardModel_SLHA2)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY RHN_coupling_slide
  START_CAPABILITY
    #define FUNCTION coupling_slide
    START_FUNCTION(double)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    DEPENDENCY(Ut1, double)
    DEPENDENCY(Ut2, double)
    DEPENDENCY(Ut3, double)	
    ALLOW_MODELS(RightHandedNeutrinos)
    #undef FUNCTION
  #undef CAPABILITY

#undef MODULE

#endif /* defined(__NeutrinoBit_rollcall_hpp__) */
