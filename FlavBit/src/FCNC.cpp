//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Functions of module FlavBit
///  - Flavour changing neutral currents
///    - RK, RK*
///    - RK_nunu, RK*_nunu
///    - Rmu
///    - b -> s gamma, B -> K* gamma
///    - B -> Xs mu mu, B -> Xs tau tau, B -> phi mu mu
///    - B -> K mu mu, B -> K* mu mu, B -> K* e e
///    - B -> K tau tau, B -> K tau mu, B -> K mu e
///    - B -> mu mu, Bs -> mu tau, Bs -> tau tau
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Nazila Mahmoudi
///  \date 2013 Oct
///  \date 2014
///  \date 2015 Feb
///  \date 2016 Jul
///  \date 2018 Jan
///  \date 2019 Aug
///
///  \author Marcin Chrzaszcz
///  \date 2015 May
///  \date 2015 July
///  \date 2015 August
///  \date 2016 July
///  \date 2016 August
///  \date 2016 October
///  \date 2018 Jan
///  \date 2020 Jan
///  \date 2020 Feb
///  \date 2020 May
///
///  \author Anders Kvellestad
///          (anders.kvellestad@fys.uio.no)
///  \date 2013 Nov
///
///  \author Pat Scott
///          (pat.scott@uq.edu.au)
///  \date 2015 May, June
///  \date 2016 Aug
///  \date 2017 March
///  \date 2019 Oct
///  \date 2020 Feb
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@kit.edu)
///  \date 2017 July
///  \date 2022 Aug
///
///  \author Cristian Sierra
///          (cristian.sierra@monash.edu)
///  \date 2020 June-December
///  \date 2021 Jan-Sep
///  \date 2022 June
///
///  \author Douglas Jacob
///          (douglas.jacob@monash.edu)
///  \date 2020 Nov
///
///  \author Filip Rajec
///          (filip.rajec@adelaide.edu.au)
///  \date 2020 Apr
///
///  \author Jihyun Bhom
///          (jihyun.bhom@ifj.edu.pl)
///  \date 2019 July
///  \date 2019 Nov
///  \date 2019 Dec
///  \date 2020 Jan
///  \date 2020 Feb
///
///  \author Markus Prim
///          (markus.prim@kit.edu)
///  \date 2019 Aug
///  \date 2019 Nov
///  \date 2020 Jan
///
///  *********************************************

#include "gambit/Utils/statistics.hpp"
#include "gambit/Elements/loop_functions.hpp"
#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/FlavBit/FlavBit_rollcall.hpp"
#include "gambit/FlavBit/FlavBit_macros.hpp"
#include "gambit/FlavBit/Flav_reader.hpp"
#include "gambit/FlavBit/FlavBit_utils.hpp"

namespace Gambit
{

  namespace FlavBit
  {

    /// SuperIso prediction for b -> s gamma
    SI_SINGLE_PREDICTION_FUNCTION(b2sgamma)

    /// SuperIso prediction for B -> K* gamma
    SI_SINGLE_PREDICTION_FUNCTION(B2Kstargamma)

    /// SuperIso prediction for B -> Xs mu mu, low q2 bins
    SI_SINGLE_PREDICTION_FUNCTION(BRBXsmumu_lowq2)

    /// SuperIso prediction for B -> Xs mu mu, high q2 bins
    SI_SINGLE_PREDICTION_FUNCTION(BRBXsmumu_highq2)

    /// SuperIso prediction for the forward-backwards assymmetry of B -> Xs mu mu, low q2 bins
    SI_SINGLE_PREDICTION_FUNCTION(AFBBXsmumu_lowq2)

    /// SuperIso prediction for the forward-backwards assymmetry of B -> Xs mu mu, high q2 bins
    SI_SINGLE_PREDICTION_FUNCTION(AFBBXsmumu_highq2)

    /// SuperIso prediction for B -> phi mu mu
    SI_SINGLE_PREDICTION_FUNCTION_BINS(Bs2phimumuBr, ((1, 6), (15, 19)))

    /// SuperIso prediction for the BR of B -> K* mu mu
    SI_SINGLE_PREDICTION_FUNCTION_BINS(B2KstarmumuBr, ((0.1, 0.98), (1.1, 2.5), (2.5, 4), (4, 6), (6, 8), (15, 19)))

    /// SuperIso prediction for the BR of B -> K mu mu
    SI_SINGLE_PREDICTION_FUNCTION_BINS(B2KmumuBr, ((0.05, 2), (2, 4.3), (4.3, 8.68), (14.18, 16), (16, 18), (18, 22)))

    /// SuperIso prediction for RK and RK*
    // TODO: these should be re-activated once RK and RKstar can be extracted from a future version of SuperIso using the check_nameobs function.
    //SI_SINGLE_PREDICTION_FUNCTION(RK_LHCb)
    //SI_SINGLE_PREDICTION_FUNCTION_BINS(RKstar_LHCb, ((0.045, 1.1), (1.1, 6)))

    // TODO: Temporary restore of RK and RKstar convenience functions until their new interface is fixed
    /// SuperIso prediction for RK* in low q^2
    void SuperIso_RKstar_0045_11(double &result)
    {
      using namespace Pipes::SuperIso_RKstar_0045_11;
      if (flav_debug) cout<<"Starting SuperIso_RKstar_0045_11"<<endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result=BEreq::RKstar(&param,0.045,1.1);

      if (flav_debug) printf("RK*_lowq2=%.3e\n",result);
      if (flav_debug) cout<<"Finished SuperIso_RKstar_0045_11"<<endl;
    }

    /// RK* in intermediate q^2
    void SuperIso_RKstar_11_60(double &result)
    {
      using namespace Pipes::SuperIso_RKstar_11_60;
      if (flav_debug) cout<<"Starting SuperIso_RKstar_11_60"<<endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result=BEreq::RKstar(&param,1.1,6.0);

      if (flav_debug) printf("RK*_intermq2=%.3e\n",result);
      if (flav_debug) cout<<"Finished SuperIso_RKstar_11_60"<<endl;
    }

    /// RK between 1 and 6 GeV^2
    void SuperIso_RK(double &result)
    {
      using namespace Pipes::SuperIso_RK;
      if (flav_debug) cout<<"Starting SuperIso_RK"<<endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result=BEreq::RK(&param,1.0,6.0);

      if (flav_debug) printf("RK=%.3e\n",result);
      if (flav_debug) cout<<"Finished SuperIso_RK"<<endl;
    }

    /// SuperIso prediction for B -> K tau tau
    // TODO: this should be used once the BKtautau CONV function is removed from the SuperIso frontend
    //SI_SINGLE_PREDICTION_FUNCTION_BINS(BKtautauBr,_12p6_22p9)

    // The sub-capabilities that may be received from likelihood functions in order to feed them valid observables are listed
    // below. In principle though, these functions will accept as sub-capabilities *any* recognised SuperIso observable names.
    // The recognised observable names can be found in the check_nameobs function in src/chi2.c in SuperIso.

    /// SuperIso prediction for B -> mu mu
    SI_MULTI_PREDICTION_FUNCTION(B2mumu)                                // Typical subcaps: BRuntag_Bsmumu, BR_Bdmumu

    /// SuperIso prediction for the angular observables of B -> K* mu mu
    SI_MULTI_PREDICTION_FUNCTION_BINS(B2KstarmumuAng, Atlas, ((0.1, 2.0), (2.0, 4.0), (4.0, 8.0)))   // Typical subcaps: FL, S3, S4, S5, S7, S8
    SI_MULTI_PREDICTION_FUNCTION_BINS(B2KstarmumuAng, CMS, ((1.0, 2.0), (2.0, 4.3), (4.3, 6.0), (6.0, 8.68), (10.09, 12.86), (14.18, 16.0), (16.0, 19.0)))  // Typical subcaps: P1, P5prime
    SI_MULTI_PREDICTION_FUNCTION_BINS(B2KstarmumuAng, Belle, ((0.1, 4.0), (4.0, 8.0), (10.09, 12.9), (14.18, 19.0)))   // Typical subcaps: P4prime, P5prime
    SI_MULTI_PREDICTION_FUNCTION_BINS(B2KstarmumuAng, LHCb, ((0.1, 0.98), (1.1, 2.5), (2.5, 4.0), (4.0, 6.0), (6.0, 8.0), (15.0, 19.0)))   // Typical subcaps: FL, AFB, S3, S4, S5, S7, S8, S9

    /// SuperIso prediction for the angular observables of B -> K* e e
    SI_MULTI_PREDICTION_FUNCTION_BINS(B2KstareeAng_Lowq2, LHCb, ((0.0008, 0.257))) // Typical subcaps: FLee, AT_Re, AT_2, AT_Im

    /// epsilon function for b->snunu in the THDM
    double epsilon(int l, int lp, SMInputs &sminputs, Spectrum &spectrum)
    {
      std::complex<double> epsilonij = THDM_DeltaC_NP(13, l, lp, sminputs, spectrum);

      return real(epsilonij);
    }

    /// eta function for b->snunu in the THDM
    double eta(int l, int lp, SMInputs &sminputs, Spectrum &spectrum)
    {
      std::complex<double> etaij = THDM_DeltaC_NP(14, l, lp, sminputs, spectrum);

      return real(etaij);
    }

    /// RKnunu for b->snunu in the THDM
    void THDM_RKnunu(double &result)
    {
      using namespace Pipes::THDM_RKnunu;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;
      double RKnunu = 0;

      for (int i = 0; i <= 2; ++i)
      {
        for (int j = 0; j <= 2; ++j)
        {
          RKnunu += (0.33333333)*(1-2*eta(i,j,sminputs,spectrum))*pow(epsilon(i,j,sminputs,spectrum),2);
        }
      }

      result = RKnunu;
    }

    /// RKstarnunu for b->snunu in the THDM
    void THDM_RKstarnunu(double &result)
    {
      using namespace Pipes::THDM_RKstarnunu;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;
      double RKstarnunu = 0;
      double kappa = 1.34;

      for (int i = 0; i <= 2; ++i)
      {
        for (int j = 0; j <= 2; ++j)
        {
          RKstarnunu += (0.33333333)*(1 + kappa*eta(i,j,sminputs,spectrum))*pow(epsilon(i,j,sminputs,spectrum),2);
        }
      }

      result = RKstarnunu;
    }

    double THDM_Bs2llp(int l, int lp, SMInputs sminputs, Spectrum spectrum)
    {
      const double mMu = sminputs.mMu;
      const double mTau = sminputs.mTau;
      const double mBmB = sminputs.mBmB;
      const double mS = sminputs.mS;
      const double mW = sminputs.mW;
      const double mZ = sminputs.mZ;
      const double SW = sqrt(1 - pow(mW/mZ,2));
      const vector<double> ml = {0, mMu, mTau};
      const double A      = sminputs.CKM.A;
      const double lambda = sminputs.CKM.lambda;
      const double Vts = -A*lambda*lambda;
      const double Vtb = 1 - (1/2)*A*A*pow(lambda,4);
      const double m_Bs = 5.36677;
      const double life_Bs = 1.510e-12;
      const double f_Bs = 0.2277;
      const double hbar = 6.582119514e-25;
      const double ri = pow(ml[l]/m_Bs,2), rj = pow(ml[lp]/m_Bs,2);

      std::complex<double> CQ1 = THDM_DeltaCQ_NP(1, l, lp, sminputs, spectrum);
      std::complex<double> CQ2 = THDM_DeltaCQ_NP(2, l, lp, sminputs, spectrum);
      std::complex<double> CQ1p = THDM_DeltaCQ_NP(3, l, lp, sminputs, spectrum);
      std::complex<double> CQ2p = THDM_DeltaCQ_NP(4, l, lp, sminputs, spectrum);
      std::complex<double> C9 = THDM_DeltaC_NP(9, l, lp, sminputs, spectrum);
      std::complex<double> C9p = THDM_DeltaC_NP(11, l, lp, sminputs, spectrum);
      std::complex<double> C10 = THDM_DeltaC_NP(10, l, lp, sminputs, spectrum);
      std::complex<double> C10p = THDM_DeltaC_NP(12, l, lp, sminputs, spectrum);

      double frirj = sqrt(1-2*(ri+rj)+pow(ri-rj,2));

     return  pow(sminputs.GF*mW*SW,4)/(32*pow(pi,5))*m_Bs*pow(f_Bs*(ml[l]+ml[lp]),2)*(life_Bs/hbar)*
             pow(Vtb*Vts,2)*frirj*(norm(m_Bs*m_Bs/((mBmB+mS)*(ml[l]+ml[lp]))*conj(CQ2-CQ2p)-conj(C10-C10p))*(1-pow(ri-rj,2)) +
             norm(m_Bs*m_Bs/((mBmB+mS)*(ml[l]+ml[lp]))*conj(CQ1-CQ1p)+((ml[l]-ml[lp])/(ml[l]+ml[lp]))*conj(C9-C9p))*(1-pow(ri+rj,2)));
     }

    void THDM_Bs2mutau(double &result)
    {
      using namespace Pipes::THDM_Bs2mutau;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;
      const int l = 1, lp = 2;

      result = THDM_Bs2llp(l, lp, sminputs, spectrum);
    }

    void THDM_Bs2tautau(double &result)
    {
      using namespace Pipes::THDM_Bs2tautau;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;
      const int l = 2, lp = 2;

      result = THDM_Bs2llp(l, lp, sminputs, spectrum);
    }

    double THDM_B2Kllp(int l, int lp, SMInputs sminputs, Spectrum spectrum)
    {
      //constants from 1903.10440
      const double a_ktaumu = 9.6;
      const double b_ktaumu = 10.0;
      const double a_kmue = 15.4;
      const double b_kmue = 15.7;
      const vector<double> akllp = {a_kmue, a_ktaumu};
      const vector<double> bkllp = {b_kmue, b_ktaumu};

      std::complex<double> C9 = THDM_DeltaC_NP(9, l, lp, sminputs, spectrum);
      std::complex<double> C9p = THDM_DeltaC_NP(11, l, lp, sminputs, spectrum);
      std::complex<double> C10 = THDM_DeltaC_NP(10, l, lp, sminputs, spectrum);
      std::complex<double> C10p = THDM_DeltaC_NP(12, l, lp, sminputs, spectrum);
      std::complex<double> C9lp = THDM_DeltaC_NP(9, lp, l, sminputs, spectrum);
      std::complex<double> C9plp = THDM_DeltaC_NP(11, lp, l, sminputs, spectrum);
      std::complex<double> C10lp = THDM_DeltaC_NP(10, lp, l, sminputs, spectrum);
      std::complex<double> C10plp = THDM_DeltaC_NP(12, lp, l, sminputs, spectrum);

      return 10e-9*(akllp[lp]*norm(C9+C9p)+bkllp[lp]*norm(C10+C10p)+(akllp[lp]*norm(C9lp+C9plp)+bkllp[lp]*norm(C10lp+C10plp)));
    }

    void THDM_B2Ktaumu(double &result)
    {
      using namespace Pipes::THDM_B2Ktaumu;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;
      const int l = 2, lp = 1;

      result = THDM_B2Kllp(l, lp, sminputs, spectrum);
    }

    void THDM_B2Kmue(double &result)
    {
      using namespace Pipes::THDM_B2Kmue;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;
      const int l = 1, lp = 0;

      result = THDM_B2Kllp(l, lp, sminputs, spectrum);
    }

    /// Branching ratio B+ ->K+ tau tau
    //  TODO: this function should be deleted once BRBKtautau_CONV is removed from the SuperIso frontend
    void SuperIso_prediction_BRBKtautau(double &result)
    {
      using namespace Pipes::SuperIso_prediction_BRBKtautau;
      if (flav_debug) cout<<"Starting SuperIso_prediction_BRBKtautau"<<endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      double mB = 5.27926;
      double mK = 0.493677;
      const double mTau = Dep::SMINPUTS->mTau;
      double Q2min = 4*mTau*mTau;
      double Q2max = pow(mB-mK,2);
      result=BEreq::BRBKtautau_CONV(&param,byVal(Q2min),byVal(Q2max));

      if (flav_debug) printf("BR(B=->K+ tau tau)=%.3e\n",result);
      if (flav_debug) cout<<"Finished SuperIso_prediction_BRBKtautau"<<endl;
    }

    /// 2-to-3-body decay ratio for semileptonic K and pi decays
    void SuperIso_prediction_Rmu23(double &result)
    {
      using namespace Pipes::SuperIso_prediction_Rmu23;
      if (flav_debug) cout<<"Starting SuperIso_prediction_Rmu23"<<endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result = BEreq::Rmu23(&param);

      if (flav_debug) printf("Rmu23=%.3e\n",result);
      if (flav_debug) cout<<"Finished SuperIso_prediction_Rmu23"<<endl;
    }

    /// Delta_0 (CP-averaged isospin asymmetry of B -> K* gamma)
    void SuperIso_prediction_delta0(double &result)
    {
      using namespace Pipes::SuperIso_prediction_delta0;
      if (flav_debug) cout<<"Starting SuperIso_prediction_delta0"<<endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result=BEreq::modified_delta0(&param);

      if (flav_debug) printf("Delta0(B->K* gamma)=%.3e\n",result);
      if (flav_debug) cout<<"Finished SuperIso_prediction_delta0"<<endl;
    }

    /// Zero crossing of the forward-backward asymmetry of B -> X_s mu mu
    void SuperIso_prediction_A_BXsmumu_zero(double &result)
    {
      using namespace Pipes::SuperIso_prediction_A_BXsmumu_zero;
      if (flav_debug) cout<<"Starting SuperIso_prediction_A_BXsmumu_zero"<<endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result=BEreq::A_BXsmumu_zero(&param);

      if (flav_debug) printf("AFB(B->Xs mu mu)_zero=%.3e\n",result);
      if (flav_debug) cout<<"Finished SuperIso_prediction_A_BXsmumu_zero"<<endl;
    }

    /// Inclusive branching fraction B -> X_s tau tau at high q^2
    void SuperIso_prediction_BRBXstautau_highq2(double &result)
    {
      using namespace Pipes::SuperIso_prediction_BRBXstautau_highq2;
      if (flav_debug) cout<<"Starting SuperIso_prediction_BRBXstautau_highq2"<<endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result=BEreq::BRBXstautau_highq2(&param);

      if (flav_debug) printf("BR(B->Xs tau tau)_highq2=%.3e\n",result);
      if (flav_debug) cout<<"Finished SuperIso_prediction_BRBXstautau_highq2"<<endl;
    }

    /// Forward-backward asymmetry of B -> X_s tau tau at high q^2
    void SuperIso_prediction_A_BXstautau_highq2(double &result)
    {
      using namespace Pipes::SuperIso_prediction_A_BXstautau_highq2;
      if (flav_debug) cout<<"Starting SuperIso_prediction_A_BXstautau_highq2"<<endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result=BEreq::A_BXstautau_highq2(&param);

      if (flav_debug) printf("AFB(B->Xs tau tau)_highq2=%.3e\n",result);
      if (flav_debug) cout<<"Finished SuperIso_prediction_A_BXstautau_highq2"<<endl;
    }

    /// RK* for RHN, using same approximations as RK, low q^2
    void RHN_RKstar_0045_11(double &result)
    {
      using namespace Pipes::RHN_RKstar_0045_11;
      SMInputs sminputs = *Dep::SMINPUTS;
      Eigen::Matrix3cd Theta = *Dep::SeesawI_Theta;
      std::vector<double> mN = {*Param["M_1"],*Param["M_2"],*Param["M_3"]};
      double mt = *Param["mT"];

      if (flav_debug) cout << "Starting RHN_RKstar_0045_11" << endl;

      const double mW = sminputs.mW;
      const double sinW2 = sqrt(1.0 - pow(sminputs.mW/sminputs.mZ,2));

      // NNLL calculation of SM Wilson coefficients from 1712.01593 and 0811.1214
      const double C10_SM = -4.103;
      const double C9_SM = 4.211;

      // Wilson coefficients for the RHN model, from 1706.07570
      std::complex<double> C10_mu = {0.0, 0.0}, C10_e = {0.0, 0.0};
      for(int i=0; i<3; i++)
      {
        C10_mu += 1.0/(4.0*sinW2)*Theta.adjoint()(i,1)*Theta(1,i) * LoopFunctions::E(pow(mt/mW,2),pow(mN[i]/mW,2));
        C10_e += 1.0/(4.0*sinW2)*Theta.adjoint()(i,0)*Theta(0,i) * LoopFunctions::E(pow(mt/mW,2),pow(mN[i]/mW,2));
      }
      std::complex<double> C9_mu = - C10_mu, C9_e = -C10_e;

      // Aproximated solution from eq A.3 in 1408.4097
      result =  std::norm(C10_SM + C10_mu) + std::norm(C9_SM + C9_mu);
      result /= std::norm(C10_SM + C10_e) + std::norm(C9_SM + C9_e);

      if (flav_debug) cout << "RK = " << result << endl;
      if (flav_debug) cout << "Finished RHN_RKstar_0045_11" << endl;
    }

    /// RK* for RHN, using same approximations as RK, intermediate q^2
    void RHN_RKstar_11_60(double &result)
    {
      using namespace Pipes::RHN_RKstar_11_60;
      SMInputs sminputs = *Dep::SMINPUTS;
      Eigen::Matrix3cd Theta = *Dep::SeesawI_Theta;
      std::vector<double> mN = {*Param["M_1"],*Param["M_2"],*Param["M_3"]};
      double mt = *Param["mT"];

      if (flav_debug) cout << "Starting RHN_RKstar_11_60" << endl;

      const double mW = sminputs.mW;
      const double sinW2 = sqrt(1.0 - pow(sminputs.mW/sminputs.mZ,2));

      // NNLL calculation of SM Wilson coefficients from 1712.01593 and 0811.1214
      const double C10_SM = -4.103;
      const double C9_SM = 4.211;

      // Wilson coefficients for the RHN model, from 1706.07570
      std::complex<double> C10_mu = {0.0, 0.0}, C10_e = {0.0, 0.0};
      for(int i=0; i<3; i++)
      {
        C10_mu += 1.0/(4.0*sinW2)*Theta.adjoint()(i,1)*Theta(1,i) * LoopFunctions::E(pow(mt/mW,2),pow(mN[i]/mW,2));
        C10_e += 1.0/(4.0*sinW2)*Theta.adjoint()(i,0)*Theta(0,i) * LoopFunctions::E(pow(mt/mW,2),pow(mN[i]/mW,2));
      }
      std::complex<double> C9_mu = - C10_mu, C9_e = -C10_e;

      // Aproximated solution from eq A.3 in 1408.4097
      result =  std::norm(C10_SM + C10_mu) + std::norm(C9_SM + C9_mu);
      result /= std::norm(C10_SM + C10_e) + std::norm(C9_SM + C9_e);

      if (flav_debug) cout << "RK = " << result << endl;
      if (flav_debug) cout << "Finished RHN_RKstar_11_60" << endl;
    }

    /// RK for RHN
    void RHN_RK(double &result)
    {
      using namespace Pipes::RHN_RK;
      SMInputs sminputs = *Dep::SMINPUTS;
      Eigen::Matrix3cd Theta = *Dep::SeesawI_Theta;
      std::vector<double> mN = {*Param["M_1"],*Param["M_2"],*Param["M_3"]};
      double mt = *Param["mT"];

      if (flav_debug) cout << "Starting RHN_RK" << endl;

      const double mW = sminputs.mW;
      const double sinW2 = sqrt(1.0 - pow(sminputs.mW/sminputs.mZ,2));

      // NNLL calculation of SM Wilson coefficients from 1712.01593 and 0811.1214
      const double C10_SM = -4.103;
      const double C9_SM = 4.211;

      // Wilson coefficients for the RHN model, from 1706.07570
      std::complex<double> C10_mu = {0.0, 0.0}, C10_e = {0.0, 0.0};
      for(int i=0; i<3; i++)
      {
        C10_mu += 1.0/(4.0*sinW2)*Theta.adjoint()(i,1)*Theta(1,i) * LoopFunctions::E(pow(mt/mW,2),pow(mN[i]/mW,2));
        C10_e += 1.0/(4.0*sinW2)*Theta.adjoint()(i,0)*Theta(0,i) * LoopFunctions::E(pow(mt/mW,2),pow(mN[i]/mW,2));
      }
      std::complex<double> C9_mu = - C10_mu, C9_e = -C10_e;

      // Aproximated solution from eq A.3 in 1408.4097
      result =  std::norm(C10_SM + C10_mu) + std::norm(C9_SM + C9_mu);
      result /= std::norm(C10_SM + C10_e) + std::norm(C9_SM + C9_e);

      if (flav_debug) cout << "RK = " << result << endl;
      if (flav_debug) cout << "Finished RHN_RK" << endl;
    }

    /// Isospin asymmetry of B-> K* mu mu
    void SuperIso_prediction_AI_BKstarmumu(double &result)
    {
      using namespace Pipes::SuperIso_prediction_AI_BKstarmumu;
      if (flav_debug) cout<<"Starting SuperIso_prediction_AI_BKstarmumu"<<endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result=BEreq::modified_AI_BKstarmumu(&param);

      if (flav_debug) printf("A_I(B->K* mu mu)_lowq2=%.3e\n",result);
      if (flav_debug) cout<<"Finished SuperIso_prediction_AI_BKstarmumu"<<endl;
    }

    /// Zero crossing of isospin asymmetry of B-> K* mu mu
    void SuperIso_prediction_AI_BKstarmumu_zero(double &result)
    {
      using namespace Pipes::SuperIso_prediction_AI_BKstarmumu_zero;

      if (flav_debug) cout<<"Starting SuperIso_prediction_AI_BKstarmumu_zero"<<endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result=BEreq::modified_AI_BKstarmumu_zero(&param);

      if (flav_debug) printf("A_I(B->K* mu mu)_zero=%.3e\n",result);
      if (flav_debug) cout<<"Finished SuperIso_prediction_AI_BKstarmumu_zero"<<endl;
    }

    ///These functions extract observables from a FeynHiggs flavour result
    ///@{
    void FeynHiggs_prediction_bsgamma(double &result)
    {
      result = Pipes::FeynHiggs_prediction_bsgamma::Dep::FlavourObs->Bsg_MSSM;
    }
    void FeynHiggs_prediction_Bsmumu (double &result)
    {
      result = Pipes::FeynHiggs_prediction_Bsmumu::Dep::FlavourObs->Bsmumu_MSSM;
    }
    void FeynHiggs_prediction_DeltaMs(double &result)
    {
      result = Pipes::FeynHiggs_prediction_DeltaMs::Dep::FlavourObs->deltaMs_MSSM;
    }
    ///@}


    ///------------------------///
    ///      Likelihoods       ///
    ///------------------------///


    /// HEPLike LogLikelihood b -> s gamma
    HEPLIKE_GAUSSIAN_1D_LIKELIHOOD(b2sgamma, "/data/HFLAV_18/RD/b2sgamma.yaml")

    /// HEPLike LogLikelihood B -> Kstar gamma
    HEPLIKE_GAUSSIAN_1D_LIKELIHOOD(B2Kstargamma, "/data/HFLAV_18/RD/B2Kstar_gamma_BR.yaml")


    /// Likelihood for Bs -> mu tau and Bs -> tau tau
    void Bs2llp_likelihood(double &result)
    {
      using namespace Pipes::Bs2llp_likelihood;

      static bool first = true;
      static boost::numeric::ublas::matrix<double> cov_exp, value_exp;
      static double th_err[2];
      double theory[2];

      // Read and calculate things based on the observed data only the first time through, as none of it depends on the model parameters.
      if (first)
      {
        // Read in experimental measurements
        Flav_reader fread(GAMBIT_DIR  "/FlavBit/data");
        fread.debug_mode(flav_debug);

        // Bs -> mu tau
        fread.read_yaml_measurement("flav_data.yaml", "BR_Bsmutau");
        // Bs -> tau tau
        fread.read_yaml_measurement("flav_data.yaml", "BR_Bstautau");

        fread.initialise_matrices();
        cov_exp=fread.get_exp_cov();
        value_exp=fread.get_exp_value();

        for (int i = 0; i < 2; ++i)
          th_err[i] = fread.get_th_err()(i,0).first;

        // Init over.
        first = false;
      }

     theory[0] = *Dep::Bs2mutau;
     if(flav_debug) cout << "Bs -> mu tau = " << theory[0] << endl;
     theory[1] = *Dep::Bs2tautau;
     if(flav_debug) cout << "Bs -> tau+ tau- = " << theory[1] << endl;

     result = 0;
     for (int i = 0; i < 2; ++i)
       result += Stats::gaussian_upper_limit(theory[i], value_exp(i,0), th_err[i], sqrt(cov_exp(i,i)), false);
    }

    /// Likelihood for B+->K+ l lp
    void B2Kllp_likelihood(double &result)
    {
      using namespace Pipes::B2Kllp_likelihood;

      static bool first = true;
      static boost::numeric::ublas::matrix<double> cov_exp, value_exp;
      static double th_err[3];
      double theory[3];

      // Read and calculate things based on the observed data only the first time through, as none of it depends on the model parameters.
      if (first)
      {
        // Read in experimental measurements
        Flav_reader fread(GAMBIT_DIR  "/FlavBit/data");
        fread.debug_mode(flav_debug);

        // B+-> K+ tau+- mu-+
        fread.read_yaml_measurement("flav_data.yaml", "BR_BKtaumu");
        // B+-> K+ mu+- e-+
        fread.read_yaml_measurement("flav_data.yaml", "BR_BKmue");
        // B+-> K+ tau+ tau-
        fread.read_yaml_measurement("flav_data.yaml", "BR_BKtautau");

        fread.initialise_matrices();
        cov_exp=fread.get_exp_cov();
        value_exp=fread.get_exp_value();

        for (int i = 0; i < 3; ++i)
          th_err[i] = fread.get_th_err()(i,0).first;

        // Init over.
        first = false;
      }

     theory[0] = *Dep::B2Ktaumu;
     if(flav_debug) cout << "B ->K tau mu = " << theory[0] << endl;
     theory[1] = *Dep::B2Kmue;
     if(flav_debug) cout << "B ->K mu e = " << theory[1] << endl;
     theory[2] = *Dep::B2Ktautau;
     // theory[2] = Dep::B2Ktautau->central_values.at("BKtautauBr");
     if(flav_debug) cout << "B ->K tau tau = " << theory[2] << endl;

     result = 0;
     for (int i = 0; i < 3; ++i)
       result += Stats::gaussian_upper_limit(theory[i], value_exp(i,0), th_err[i], sqrt(cov_exp(i,i)), false);
    }

    /// Likelihood for  RKnunu and RKstarnunu
    void RK_RKstarnunu_likelihood(double &result)
    {
      using namespace Pipes::RK_RKstarnunu_likelihood;

      static bool first = true;
      static boost::numeric::ublas::matrix<double> cov_exp, value_exp;
      static double th_err[2];
      double theory[2];

      // Read and calculate things based on the observed data only the first time through, as none of it depends on the model parameters.
      if (first)
      {
        // Read in experimental measurements
        Flav_reader fread(GAMBIT_DIR  "/FlavBit/data");
        fread.debug_mode(flav_debug);

        // RKnunu
        fread.read_yaml_measurement("flav_data.yaml", "RKnunu");
        // RKstarnunu
        fread.read_yaml_measurement("flav_data.yaml", "RKstarnunu");

        fread.initialise_matrices();
        cov_exp=fread.get_exp_cov();
        value_exp=fread.get_exp_value();

        for (int i = 0; i < 2; ++i)
          th_err[i] = fread.get_th_err()(i,0).first;

        // Init over.
        first = false;
      }

     theory[0] = *Dep::RKnunu;
     if(flav_debug) cout << "RKnunu = " << theory[0] << endl;
     theory[1] = *Dep::RKstarnunu;
     if(flav_debug) cout << "RKstarnunu = " << theory[1] << endl;

     result = 0;
     for (int i = 0; i < 2; ++i)
       result += Stats::gaussian_upper_limit(theory[i], value_exp(i,0), th_err[i], sqrt(cov_exp(i,i)), false);
    }

    /// HEPLike LogLikelihood B -> ll (CMS)
    /// Recognised sub-capabilities:
    ///    BRuntag_Bsmumu
    ///    BR_Bdmumu
    void HEPLike_B2mumu_LogLikelihood_CMS(double &result)
    {
      using namespace Pipes::HEPLike_B2mumu_LogLikelihood_CMS;
      static const std::string inputfile = path_to_latest_heplike_data() + "/data/CMS/RD/B2MuMu/CMS-PAS-BPH-16-004.yaml";
      static std::vector<str> obs_list = Downstream::subcaps->getNames();
      static HepLike_default::HL_nDimLikelihood nDimLikelihood(inputfile);
      static bool first = true;

      if (obs_list.empty()) FlavBit_error().raise(LOCAL_INFO, "No subcapabilities specified!");

      if (first)
      {
        if (flav_debug) std::cout << "Debug: Reading HepLike data file: " << inputfile << endl;
        nDimLikelihood.Read();
        update_obs_list(obs_list, nDimLikelihood.GetObservables());
        first = false;
      }

      /* nDimLikelihood does not support theory errors */
      result = nDimLikelihood.GetLogLikelihood(get_obs_theory(*Dep::prediction_B2mumu, obs_list));

      if (flav_debug) std::cout << "HEPLike_B2mumu_LogLikelihood_CMS result: " << result << std::endl;
    }

    /// HEPLike LogLikelihood B -> ll (ATLAS)
    /// Recognised sub-capabilities:
    ///    BRuntag_Bsmumu
    ///    BR_Bdmumu
    void HEPLike_B2mumu_LogLikelihood_Atlas(double &result)
    {
      using namespace Pipes::HEPLike_B2mumu_LogLikelihood_Atlas;
      static const std::string inputfile = path_to_latest_heplike_data() + "/data/ATLAS/RD/B2MuMu/CERN-EP-2018-291.yaml";
      static std::vector<str> obs_list = Downstream::subcaps->getNames();
      static HepLike_default::HL_nDimLikelihood nDimLikelihood(inputfile);

      if (obs_list.empty()) FlavBit_error().raise(LOCAL_INFO, "No subcapabilities specified!");

      static bool first = true;
      if (first)
      {
        if (flav_debug) std::cout << "Debug: Reading HepLike data file: " << inputfile << endl;
        nDimLikelihood.Read();
        update_obs_list(obs_list, nDimLikelihood.GetObservables());
        first = false;
      }

      /* nDimLikelihood does not support theory errors */
      result = nDimLikelihood.GetLogLikelihood(get_obs_theory(*Dep::prediction_B2mumu, obs_list));

      if (flav_debug) std::cout << "HEPLike_B2mumu_LogLikelihood_Atlas result: " << result << std::endl;
    }

    /// HEPLike LogLikelihood B -> ll (LHCb)
    /// Recognised sub-capabilities:
    ///    BRuntag_Bsmumu
    ///    BR_Bdmumu
    void HEPLike_B2mumu_LogLikelihood_LHCb(double &result)
    {
      using namespace Pipes::HEPLike_B2mumu_LogLikelihood_LHCb;
      static const std::string inputfile = path_to_latest_heplike_data() + "/data/LHCb/RD/B2MuMu/CERN-EP-2017-100.yaml";
      static std::vector<str> obs_list = Downstream::subcaps->getNames();
      static HepLike_default::HL_nDimLikelihood nDimLikelihood(inputfile);

      if (obs_list.empty()) FlavBit_error().raise(LOCAL_INFO, "No subcapabilities specified!");

      static bool first = true;
      if (first)
      {
        if (flav_debug) std::cout << "Debug: Reading HepLike data file: " << inputfile << endl;
        nDimLikelihood.Read();
        update_obs_list(obs_list, nDimLikelihood.GetObservables());
        first = false;
      }

      /* nDimLikelihood does not support theory errors */
      result = nDimLikelihood.GetLogLikelihood(get_obs_theory(*Dep::prediction_B2mumu, obs_list));

      if (flav_debug) std::cout << "HEPLike_B2mumu_LogLikelihood_LHCb result: " << result << std::endl;
    }

    /// HEPLike LogLikelihood B -> K* mu mu Angular (ATLAS)
    /// Recognised sub-capabilities:
    ///   FL
    ///   S3
    ///   S4
    ///   S5
    ///   S7
    ///   S8
    void HEPLike_B2KstarmumuAng_LogLikelihood_Atlas(double &result)
    {
      if (flav_debug) std::cout << "Starting HEPLike_B2KstarmumuAng_LogLikelihood_Atlas"<<std::endl;
      using namespace Pipes::HEPLike_B2KstarmumuAng_LogLikelihood_Atlas;
      static const std::string inputfile = path_to_latest_heplike_data() + "/data/ATLAS/RD/Bd2KstarMuMu_Angular/CERN-EP-2017-161_q2_";
      static std::vector<str> obs_list = Downstream::subcaps->getNames();
      static std::vector<HepLike_default::HL_nDimGaussian> nDimGaussian;

      if (obs_list.empty()) FlavBit_error().raise(LOCAL_INFO, "No subcapabilities specified!");

      flav_binned_prediction binned_prediction= *Dep::prediction_B2KstarmumuAng_Atlas;
      if(runOptions->getValueOrDef<bool>(false, "ignore_lowq2_bin"))
      {
        binned_prediction.erase(binned_prediction.begin(), next(binned_prediction.begin()));
      }
      std::vector<flav_prediction> prediction;
      for(auto pred : binned_prediction)
        prediction.push_back(pred.second);

      static bool first = true;
      if (first)
      {
        for (auto pred : binned_prediction)
        {
          nDimGaussian.push_back(HepLike_default::HL_nDimGaussian(inputfile + pred.first + ".yaml"));
          if (flav_debug) std::cout << "Debug: Reading HepLike data file: " << inputfile + pred.first + ".yaml" << endl;
          nDimGaussian[nDimGaussian.size()-1].Read();
        }
        update_obs_list(obs_list, nDimGaussian[0].GetObservables());
        first = false;
      }

      result = 0;
      for (unsigned int i = 0; i < nDimGaussian.size(); i++)
      {
        result += nDimGaussian[i].GetLogLikelihood(get_obs_theory(prediction[i], obs_list), get_obs_covariance(prediction[i], obs_list));
      }
      if (flav_debug) std::cout << "HEPLike_B2KstarmumuAng_LogLikelihood_Atlas result: " << result << std::endl;
    }


    /// HEPLike LogLikelihood B -> K* mu mu Angular (CMS)
    /// Recognised sub-capabilities:
    ///   P1
    ///   P5prime
    void HEPLike_B2KstarmumuAng_LogLikelihood_CMS(double &result)
    {
      using namespace Pipes::HEPLike_B2KstarmumuAng_LogLikelihood_CMS;
      static const std::string inputfile = path_to_latest_heplike_data() + "/data/CMS/RD/Bd2KstarMuMu_Angular/CERN-EP-2017-240_q2_";
      static std::vector<str> obs_list = Downstream::subcaps->getNames();
      static std::vector<HepLike_default::HL_nDimBifurGaussian> nDimBifurGaussian;

      if (obs_list.empty()) FlavBit_error().raise(LOCAL_INFO, "No subcapabilities specified!");

      flav_binned_prediction binned_prediction= *Dep::prediction_B2KstarmumuAng_CMS;
      std::vector<flav_prediction> prediction;
      for(auto pred : binned_prediction)
        prediction.push_back(pred.second);

      static bool first = true;
      if (first)
      {
        for (auto pred : binned_prediction)
        {
          nDimBifurGaussian.push_back(HepLike_default::HL_nDimBifurGaussian(inputfile + pred.first + ".yaml"));
          if (flav_debug) std::cout << "Debug: Reading HepLike data file: " << inputfile + pred.first + ".yaml" << endl;
          nDimBifurGaussian[nDimBifurGaussian.size()-1].Read();
        }
        update_obs_list(obs_list, nDimBifurGaussian[0].GetObservables());
        first = false;
      }

      result = 0;
      for (unsigned int i = 0; i < nDimBifurGaussian.size(); i++)
      {
        result += nDimBifurGaussian[i].GetLogLikelihood(get_obs_theory(prediction[i], obs_list), get_obs_covariance(prediction[i], obs_list));
      }

      if (flav_debug) std::cout << "HEPLike_B2KstarmumuAng_LogLikelihood_CMS result: " << result << std::endl;
    }

    /// HEPLike LogLikelihood B -> K* mu mu Angular (Belle)
    /// Recognised sub-capabilities:
    ///   P4prime
    ///   P5prime
    void HEPLike_B2KstarmumuAng_LogLikelihood_Belle(double &result)
    {
      using namespace Pipes::HEPLike_B2KstarmumuAng_LogLikelihood_Belle;
      static const std::string inputfile = path_to_latest_heplike_data() + "/data/Belle/RD/Bd2KstarMuMu_Angular/KEK-2016-54_q2_";
      static std::vector<str> obs_list = Downstream::subcaps->getNames();
      static std::vector<HepLike_default::HL_nDimBifurGaussian> nDimBifurGaussian;

      if (obs_list.empty()) FlavBit_error().raise(LOCAL_INFO, "No subcapabilities specified!");

      flav_binned_prediction binned_prediction= *Dep::prediction_B2KstarmumuAng_Belle;
      if(runOptions->getValueOrDef<bool>(false, "ignore_lowq2_bin"))
      {
        binned_prediction.erase(binned_prediction.begin(), next(binned_prediction.begin()));
      }
      std::vector<flav_prediction> prediction;
      for(auto pred : binned_prediction)
        prediction.push_back(pred.second);

      static bool first = true;
      if (first)
      {
        for (auto pred : binned_prediction)
        {
          nDimBifurGaussian.push_back(HepLike_default::HL_nDimBifurGaussian(inputfile + pred.first + ".yaml"));
          if (flav_debug) std::cout << "Debug: Reading HepLike data file: " << inputfile + pred.first + ".yaml" << endl;
          nDimBifurGaussian[nDimBifurGaussian.size()-1].Read();
        }
        update_obs_list(obs_list, nDimBifurGaussian[0].GetObservables());
        first = false;
      }

      result = 0;
      for (unsigned int i = 0; i < nDimBifurGaussian.size(); i++)
      {
        result += nDimBifurGaussian[i].GetLogLikelihood(get_obs_theory(prediction[i], obs_list), get_obs_covariance(prediction[i], obs_list));
      }

      if (flav_debug) std::cout << "HEPLike_B2KstarmumuAng_LogLikelihood_Belle result: " << result << std::endl;
    }

    /// HEPLike LogLikelihood B -> K* ell ell Angular (Belle)
    /// Recognised sub-capabilities:
    ///   P4prime
    ///   P5prime
    void HEPLike_B2KstarellellAng_LogLikelihood_Belle(double &result)
    {
      using namespace Pipes::HEPLike_B2KstarellellAng_LogLikelihood_Belle;
      static const std::string inputfile = path_to_latest_heplike_data() + "/data/Belle/RD/Bd2KstarEllEll_Angular/KEK-2016-54_q2_";
      static std::vector<str> obs_list = Downstream::subcaps->getNames();
      static std::vector<HepLike_default::HL_nDimBifurGaussian> nDimBifurGaussian;

      if (obs_list.empty()) FlavBit_error().raise(LOCAL_INFO, "No subcapabilities specified!");

      flav_binned_prediction binned_prediction= *Dep::prediction_B2KstarmumuAng_Belle;
      std::vector<flav_prediction> prediction;
      for(auto pred : binned_prediction)
        prediction.push_back(pred.second);

      static bool first = true;
      if (first)
      {
        for (auto pred : binned_prediction)
        {
          nDimBifurGaussian.push_back(HepLike_default::HL_nDimBifurGaussian(inputfile + pred.first + ".yaml"));
          if (flav_debug) std::cout << "Debug: Reading HepLike data file: " << inputfile + pred.first + ".yaml" << endl;
          nDimBifurGaussian[nDimBifurGaussian.size()-1].Read();
        }
        update_obs_list(obs_list, nDimBifurGaussian[0].GetObservables());
        first = false;
      }

      result = 0;
      for (unsigned int i = 0; i < nDimBifurGaussian.size(); i++)
      {
        result += nDimBifurGaussian[i].GetLogLikelihood(get_obs_theory(prediction[i], obs_list), get_obs_covariance(prediction[i], obs_list));
      }

      if (flav_debug) std::cout << "HEPLike_B2KstarellellAng_LogLikelihood_Belle result: " << result << std::endl;
    }

    /// HEPLike LogLikelihood B -> K* mu mu Angular (LHCb)
    /// Recognised sub-capabilities:
    ///   FL
    ///   AFB
    ///   S3
    ///   S4
    ///   S5
    ///   S7
    ///   S8
    ///   S9
    void HEPLike_B2KstarmumuAng_LogLikelihood_LHCb(double &result)
    {
      using namespace Pipes::HEPLike_B2KstarmumuAng_LogLikelihood_LHCb;
      static const std::string inputfile = path_to_latest_heplike_data() + "/data/LHCb/RD/Bd2KstarMuMu_Angular/PH-EP-2015-314_q2_";
      static std::vector<str> obs_list = Downstream::subcaps->getNames();
      static std::vector<HepLike_default::HL_nDimBifurGaussian> nDimBifurGaussian;

      if (obs_list.empty()) FlavBit_error().raise(LOCAL_INFO, "No subcapabilities specified!");

      flav_binned_prediction binned_prediction= *Dep::prediction_B2KstarmumuAng_LHCb;
      std::vector<flav_prediction> prediction;
      for(auto pred : binned_prediction)
        prediction.push_back(pred.second);

      static bool first = true;
      if (first)
      {
        for (auto pred : binned_prediction)
        {
          nDimBifurGaussian.push_back(HepLike_default::HL_nDimBifurGaussian(inputfile + pred.first + ".yaml"));
          if (flav_debug) std::cout << "Debug: Reading HepLike data file: " << inputfile + pred.first + ".yaml" << endl;
          nDimBifurGaussian[nDimBifurGaussian.size()-1].Read();
        }
        update_obs_list(obs_list, nDimBifurGaussian[0].GetObservables());
        first = false;
      }

      result = 0;
      for (unsigned int i = 0; i < nDimBifurGaussian.size(); i++)
      {
        result += nDimBifurGaussian[i].GetLogLikelihood(get_obs_theory(prediction[i], obs_list), get_obs_covariance(prediction[i], obs_list));
      }

      if (flav_debug) std::cout << "HEPLike_B2KstarmumuAng_LogLikelihood_LHCb result: " << result << std::endl;
    }

    /// HEPLike LogLikelihood B -> K* mu mu Angular (LHCb)
    /// Recognised sub-capabilities:
    ///   FL
    ///   AFB
    ///   S3
    ///   S4
    ///   S5
    ///   S7
    ///   S8
    ///   S9
    void HEPLike_B2KstarmumuAng_LogLikelihood_LHCb_2020(double &result)
    {
      using namespace Pipes::HEPLike_B2KstarmumuAng_LogLikelihood_LHCb_2020;
      static const std::string inputfile = path_to_latest_heplike_data() + "/data/LHCb/RD/Bd2KstarMuMu_Angular/CERN-EP-2020-027_q2_";
      static std::vector<str> obs_list = Downstream::subcaps->getNames();
      static std::vector<HepLike_default::HL_nDimGaussian> nDimGaussian;

      if (obs_list.empty()) FlavBit_error().raise(LOCAL_INFO, "No subcapabilities specified!");

      flav_binned_prediction binned_prediction= *Dep::prediction_B2KstarmumuAng_LHCb;
      if(runOptions->getValueOrDef<bool>(false, "ignore_lowq2_bin"))
      {
        binned_prediction.erase(binned_prediction.begin(), next(binned_prediction.begin()));
      }
      std::vector<flav_prediction> prediction;
      for(auto pred : binned_prediction)
        prediction.push_back(pred.second);

      static bool first = true;
      if (first)
      {
        for (auto pred : binned_prediction)
        {
          nDimGaussian.push_back(HepLike_default::HL_nDimGaussian(inputfile + pred.first + ".yaml"));
          if (flav_debug) std::cout << "Debug: Reading HepLike data file: " << inputfile + pred.first + ".yaml" << endl;
          nDimGaussian[nDimGaussian.size()-1].Read();
        }
        update_obs_list(obs_list, nDimGaussian[0].GetObservables());
        first = false;
      }

      result = 0;
      for (unsigned int i = 0; i < nDimGaussian.size(); i++)
      {
        result += nDimGaussian[i].GetLogLikelihood(get_obs_theory(prediction[i], obs_list), get_obs_covariance(prediction[i], obs_list));
      }

      if (flav_debug) std::cout << "HEPLike_B2KstarmumuAng_LogLikelihood_LHCb 2020 result: " << result << std::endl;
    }

    /// HEPLike LogLikelihood B -> K* mu mu Angular (LHCb)
    void HEPLike_B2KstarmumuAng_CPAssym_LogLikelihood_LHCb(double &result)
    {
      using namespace Pipes::HEPLike_B2KstarmumuAng_CPAssym_LogLikelihood_LHCb;
      static const std::string inputfile = path_to_latest_heplike_data() + "/data/LHCb/RD/Bd2KstarMuMu_Angular/PH-EP-2015-314_q2_";
      static std::vector<str> obs_list = Downstream::subcaps->getNames();
      static std::vector<HepLike_default::HL_nDimGaussian> nDimGaussian;

      if (obs_list.empty()) FlavBit_error().raise(LOCAL_INFO, "No subcapabilities specified!");

      flav_binned_prediction binned_prediction= *Dep::prediction_B2KstarmumuAng_LHCb;
      std::vector<flav_prediction> prediction;
      for(auto pred : binned_prediction)
        prediction.push_back(pred.second);

      static bool first = true;
      if (first)
      {
        for (auto pred : binned_prediction)
        {
          nDimGaussian.push_back(HepLike_default::HL_nDimGaussian(inputfile + pred.first + ".yaml"));
          if (flav_debug) std::cout << "Debug: Reading HepLike data file: " << inputfile + pred.first + "_CPA.yaml" << endl;
          nDimGaussian[nDimGaussian.size()-1].Read();
        }
        update_obs_list(obs_list, nDimGaussian[0].GetObservables());
        first = false;
      }

      result = 0;
      for (unsigned int i = 0; i < nDimGaussian.size(); i++)
      {
        result += nDimGaussian[i].GetLogLikelihood(get_obs_theory(prediction[i], obs_list), get_obs_covariance(prediction[i], obs_list));
      }

      if (flav_debug) std::cout << "HEPLike_B2KstarmumuAng_CPAssym_LogLikelihood_LHCb  result: " << result << std::endl;
    }

    /// HEPLike LogLikelihood B -> K* e e Angular low q2 (LHCb)
    /// Recognised sub-capabilities:
    ///   FLee
    ///   AT_Re
    ///   AT_2
    ///   AT_Im
    void HEPLike_B2KstareeAng_Lowq2_LogLikelihood_LHCb_2020(double &result)
    {
      using namespace Pipes::HEPLike_B2KstareeAng_Lowq2_LogLikelihood_LHCb_2020;
      static const std::string inputfile = path_to_latest_heplike_data() + "/data/LHCb/RD/Bd2KstarEE_Angular/CERN-EP-2020-176.yaml";
      static std::vector<str> obs_list = Downstream::subcaps->getNames();
      static HepLike_default::HL_nDimGaussian nDimGaussian(inputfile);

      if (obs_list.empty()) FlavBit_error().raise(LOCAL_INFO, "No subcapabilities specified!");

      flav_binned_prediction binned_prediction= *Dep::prediction_B2KstareeAng_Lowq2_LHCb;
      std::vector<flav_prediction> prediction;
      for(auto pred : binned_prediction)
        prediction.push_back(pred.second);

      static bool first = true;
      if (first)
      {
        for (auto pred : binned_prediction)
        {
          if (flav_debug) std::cout << "Debug: Reading HepLike data file: " << inputfile + pred.first + ".yaml" << endl;
          nDimGaussian.Read();
        }
        first = false;
      }

      result = 0;
      for (unsigned int i = 0; i < prediction.size(); i++)
      {
        result += nDimGaussian.GetLogLikelihood(get_obs_theory(prediction[i], obs_list), get_obs_covariance(prediction[i], obs_list));
      }

      if (flav_debug) std::cout << "HEPLike_B2KstareeAng_Lowq2_LogLikelihood_LHCb_2020 result: " << result << std::endl;
    }

    /// HEPLike LogLikelihood Bu -> K*+ mu mu Angular (LHCb)
    /// Recognised sub-capabilities:
    ///   FL
    ///   AFB
    ///   S3
    ///   S4
    ///   S5
    ///   S7
    ///   S8
    ///   S9
    void HEPLike_Bu2KstarmumuAng_LogLikelihood_LHCb_2020(double &result)
    {
      using namespace Pipes::HEPLike_Bu2KstarmumuAng_LogLikelihood_LHCb_2020;
      static const std::string inputfile = path_to_latest_heplike_data() + "/data/LHCb/RD/Bu2KstarMuMu_Angular/CERN-EP-2020-239_q2_";
      static std::vector<str> obs_list = Downstream::subcaps->getNames();
      static std::vector<HepLike_default::HL_nDimGaussian> nDimGaussian;

      if (obs_list.empty()) FlavBit_error().raise(LOCAL_INFO, "No subcapabilities specified!");

      flav_binned_prediction binned_prediction= *Dep::prediction_B2KstarmumuAng_LHCb;
      std::vector<flav_prediction> prediction;
      for(auto pred : binned_prediction)
        prediction.push_back(pred.second);

      static bool first = true;
      if (first)
      {
        for (auto pred : binned_prediction)
        {
          nDimGaussian.push_back(HepLike_default::HL_nDimGaussian(inputfile + pred.first + ".yaml"));
          if (flav_debug) std::cout << "Debug: Reading HepLike data file: " << inputfile + pred.first + ".yaml" << endl;
          nDimGaussian[nDimGaussian.size()-1].Read();
        }
        update_obs_list(obs_list, nDimGaussian[0].GetObservables());
        first = false;
      }

      result = 0;
      for (unsigned int i = 0; i < nDimGaussian.size(); i++)
      {
        result += nDimGaussian[i].GetLogLikelihood(get_obs_theory(prediction[i], obs_list), get_obs_covariance(prediction[i], obs_list));
      }

      if (flav_debug) std::cout << "HEPLike_Bu2KstarmumuAng_LogLikelihood_LHCb 2020 result: " << result << std::endl;
    }

    /// HEPLike LogLikelihood B -> K* mu mu Br (LHCb)
    void HEPLike_B2KstarmumuBr_LogLikelihood_LHCb(double &result)
    {
      using namespace Pipes::HEPLike_B2KstarmumuBr_LogLikelihood_LHCb;
      static const std::string inputfile = path_to_latest_heplike_data() + "/data/LHCb/RD/Bd2KstarMuMu_Br/CERN-EP-2016-141_q2_";
      static std::vector<HepLike_default::HL_BifurGaussian> BifurGaussian;

      flav_binned_prediction binned_prediction = *Dep::prediction_B2KstarmumuBr;
      if(runOptions->getValueOrDef<bool>(false, "ignore_lowq2_bin"))
      {
        binned_prediction.erase(binned_prediction.begin(), next(binned_prediction.begin()));
      }
      std::vector<flav_prediction> prediction;
      for(auto pred : binned_prediction)
        prediction.push_back(pred.second);

      static bool first = true;
      if (first)
      {
        for(auto pred : binned_prediction)
        {
          BifurGaussian.push_back(HepLike_default::HL_BifurGaussian(inputfile + pred.first + ".yaml"));
          if (flav_debug) std::cout << "Debug: Reading HepLike data file " <<  inputfile + pred.first + ".yaml"  << endl;
          BifurGaussian[BifurGaussian.size()-1].Read();
        }
        first = false;
      }

      result = 0;

      for (unsigned int i = 0; i < BifurGaussian.size(); i++)
      {
        double theory = prediction[i].central_values.begin()->second;
        double theory_variance = prediction[i].covariance.begin()->second.begin()->second;
        result += BifurGaussian[i].GetLogLikelihood(theory, theory_variance);
      }

      if (flav_debug) std::cout << "HEPLike_B2KstarmumuBr_LogLikelihood_LHCb result: " << result << std::endl;
    }

    /// HEPLike LogLikelihood B -> K+ mu mu Br (LHCb)
    void HEPLike_B2KmumuBr_LogLikelihood_LHCb(double &result)
    {
      using namespace Pipes::HEPLike_B2KmumuBr_LogLikelihood_LHCb;
      static const std::string inputfile = path_to_latest_heplike_data() + "/data/LHCb/RD/B2KMuMu_Br/CERN-PH-EP-2012-263_q2_";
      static std::vector<HepLike_default::HL_Gaussian> Gaussian;

      flav_binned_prediction binned_prediction = *Dep::prediction_B2KmumuBr;
      std::vector<flav_prediction> prediction;
      for(auto pred : binned_prediction)
        prediction.push_back(pred.second);


      static bool first = true;
      if (first)
      {
        for(auto pred : binned_prediction)
        {
          Gaussian.push_back(HepLike_default::HL_Gaussian(inputfile + pred.first + ".yaml"));
          if (flav_debug) std::cout << "Debug: Reading HepLike data file " << inputfile + pred.first + ".yaml" << endl;
          Gaussian[Gaussian.size()-1].Read();
        }
        first = false;
      }

      result = 0;

      for (unsigned int i = 0; i < Gaussian.size(); i++)
      {
        double theory = prediction[i].central_values.begin()->second;
        double theory_variance = prediction[i].covariance.begin()->second.begin()->second;
        result += Gaussian[i].GetLogLikelihood(theory, theory_variance);
      }

      if (flav_debug) std::cout << "HEPLike_B2KmumuBR_LogLikelihood_LHCb result: " << result << std::endl;
    }


    void HEPLike_Bs2phimumuBr_LogLikelihood(double &result)
    {
      using namespace Pipes::HEPLike_Bs2phimumuBr_LogLikelihood;

      static const std::string inputfile = path_to_latest_heplike_data() + "/data/LHCb/RD/Bs2PhiMuMu_Br/CERN-PH-EP-2015-145_";
      static std::vector<HepLike_default::HL_BifurGaussian> BifurGaussian;

      flav_binned_prediction binned_prediction = *Dep::prediction_Bs2phimumuBr;
      std::vector<flav_prediction> prediction;
      for(auto pred : binned_prediction)
        prediction.push_back(pred.second);

      static bool first = true;
      if (first)
      {
        for(auto pred : binned_prediction)
        {
          BifurGaussian.push_back(HepLike_default::HL_BifurGaussian(inputfile + pred.first + ".yaml"));
          if (flav_debug) std::cout << "Debug: Reading HepLike data file " << inputfile + pred.first + ".yaml" << endl;
          BifurGaussian[BifurGaussian.size()-1].Read();
        }
        first = false;
      }

      result = 0;
      for (unsigned int i = 0; i < BifurGaussian.size(); i++)
      {
        double theory = prediction[i].central_values.begin()->second;
        double theory_variance = prediction[i].covariance.begin()->second.begin()->second;
        result += BifurGaussian[i].GetLogLikelihood(theory, theory_variance);
      }

      if (flav_debug) std::cout << "HEPLike_Bs2phimumuBr_LogLikelihood result: " << result << std::endl;
    }


    void HEPLike_RK_LogLikelihood_LHCb(double &result)
    {
      using namespace Pipes::HEPLike_RK_LogLikelihood_LHCb;

      static const std::string inputfile = path_to_latest_heplike_data() + "/data/LHCb/RD/Rk/CERN-EP-2019-043.yaml";
      static HepLike_default::HL_ProfLikelihood ProfLikelihood(inputfile);

      static bool first = true;
      if (first)
      {
        if (flav_debug) std::cout << "Debug: Reading HepLike data file: " << inputfile << endl;
        ProfLikelihood.Read();

        first = false;
      }

      //flav_prediction prediction = *Dep::prediction_RK_LHCb;

      //const double theory = prediction.central_values.begin()->second;
      //const double theory_variance = prediction.covariance.begin()->second.begin()->second;
      const double theory = *Dep::RK;
      const double theory_variance = 0.0;

      result = ProfLikelihood.GetLogLikelihood(1. + theory, theory_variance);

      if (flav_debug) std::cout << "HEPLike_RK_LogLikelihood_LHC_LHCb result: " << result << std::endl;
    }


    void HEPLike_RKstar_LogLikelihood_LHCb(double &result)
    {

      using namespace Pipes::HEPLike_RKstar_LogLikelihood_LHCb;

      static const std::string inputfile = path_to_latest_heplike_data() + "/data/LHCb/RD/RKstar/CERN-EP-2017-100_q2_";
      static std::vector<HepLike_default::HL_ProfLikelihood> ProfLikelihood;

      //flav_binned_prediction binned_prediction = *Dep::prediction_RKstar_LHCb;
      //std::vector<flav_prediction> prediction;
      //for(auto pred : binned_prediction)
      //  prediction.push_back(pred.second);
      std::vector<double> prediction = {*Dep::RKstar_0045_11, *Dep::RKstar_11_60};
      std::vector<str> bins = {"0.045_1.1", "1.1_6"};

      static bool first = true;
      if (first)
      {
        //for(auto pred : binned_prediction)
        for(str bin : bins)
        {
          //ProfLikelihood.push_back(HepLike_default::HL_ProfLikelihood(inputfile + pred.first + ".yaml"));
          ProfLikelihood.push_back(HepLike_default::HL_ProfLikelihood(inputfile + bin + ".yaml"));
          //if (flav_debug) std::cout << "Debug: Reading HepLike data file " <<  inputfile + pred.first + ".yaml"  << endl;
          if (flav_debug) std::cout << "Debug: Reading HepLike data file " <<  inputfile + bin + ".yaml"  << endl;
          ProfLikelihood[ProfLikelihood.size()-1].Read();

        }
        first = false;
      }

      result = 0;
      for (unsigned int i = 0; i < ProfLikelihood.size(); i++)
      {
        //const double theory = prediction[i].central_values.begin()->second;
        //const double theory_variance = prediction[i].covariance.begin()->second.begin()->second;
        const double theory = prediction[i];
        const double theory_variance = 0.0;
        result += ProfLikelihood[i].GetLogLikelihood(1. + theory, theory_variance);
      }

      if (flav_debug) std::cout << "HEPLike_RKstar_LogLikelihood_LHCb result: " << result << std::endl;
    }

  }
}
