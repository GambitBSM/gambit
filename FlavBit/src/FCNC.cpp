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
///          (cristian.sierra@njnu.edu.cn)
///  \date 2020 June-December
///  \date 2021 Jan-Sep
///  \date 2022 June
///  \date 2023 August
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
#include "gambit/Utils/integration.hpp"
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
    SI_MULTI_PREDICTION_FUNCTION_BINS(RKRKstar,LHCb, ((0.1, 1.1), (1.1, 6)))

    // TODO: Temporary restore of RK and RKstar convenience functions until their new interface is fixed
    /// SuperIso prediction for RK* in low q^2
    void SuperIso_RKstar_01_11(double &result)
    {
      using namespace Pipes::SuperIso_RKstar_01_11;
      if (flav_debug) std::cout<<"Starting SuperIso_RKstar_01_11"<< std::endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result=BEreq::SuperIso_RKstar_computation(&param,0.1,1.1);

      if (flav_debug) printf("RK*_lowq2=%.3e\n",result);
      if (flav_debug) std::cout<<"Finished SuperIso_RKstar_01_11"<< std::endl;
    }

    /// RK* in intermediate q^2
    void SuperIso_RKstar_11_60(double &result)
    {
      using namespace Pipes::SuperIso_RKstar_11_60;
      if (flav_debug) std::cout<<"Starting SuperIso_RKstar_11_60"<< std::endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result=BEreq::SuperIso_RKstar_computation(&param,1.1,6.0);

      if (flav_debug) printf("RK*_intermq2=%.3e\n",result);
      if (flav_debug) std::cout<<"Finished SuperIso_RKstar_11_60"<< std::endl;
    }

    /// RK between 0.1 and 1.1 GeV^2
    void SuperIso_RK_01_11(double &result)
    {
      using namespace Pipes::SuperIso_RK_01_11;
      if (flav_debug) std::cout<<"Starting SuperIso_RK_01_11"<< std::endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result=BEreq::SuperIso_RK_computation(&param,0.1,1.1);

      if (flav_debug) printf("RK=%.3e\n",result);
      if (flav_debug) std::cout<<"Finished SuperIso_RK_01_11"<< std::endl;
    }

    /// RK between 1.1 and 6 GeV^2
    void SuperIso_RK_11_60(double &result)
    {
      using namespace Pipes::SuperIso_RK_11_60;
      if (flav_debug) std::cout<<"Starting SuperIso_RK_11_60"<< std::endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result=BEreq::SuperIso_RK_computation(&param,1.1,6.0);

      if (flav_debug) printf("RK=%.3e\n",result);
      if (flav_debug) std::cout<<"Finished SuperIso_RK_11_60"<< std::endl;
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

    /// SuperIso prediction for the angular observables of B_u -> K* mu mu
    SI_MULTI_PREDICTION_FUNCTION_BINS(Bu2KstarmumuAng, LHCb, ((0.1, 0.98), (1.1, 2.5), (2.5, 4.0), (4.0, 6.0), (6.0, 8.0), (11.0, 12.5), (15.0, 17.0), (17.0, 19.0))) // Typical subcaps: FL, AFB, S3, S4, S5, S7, S8, S9

    /// SuperIso prediction for the angular observables of B_u -> K* mu mu with alternative binning
    SI_MULTI_PREDICTION_FUNCTION_BINS(Bu2KstarmumuAng_alt, LHCb, ((0.1, 0.98), (1.1, 6.0), (6.0, 8.0), (11.0, 12.5), (15.0, 19.0))) // Typical subcaps: FL, AFB, S3, S4, S5, S7, S8, S9 // TODO Why does this bin exist

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

    double THDM_Bs2ll(int l, int lp, SMInputs sminputs, Spectrum spectrum)
    {
      const double mMu = sminputs.mMu;
      const double mTau = sminputs.mTau;
      const double mBmB = sminputs.mBmB;
      const double mS = sminputs.mS;
      const double mW = sminputs.mW;
      const double mZ = sminputs.mZ;
      const double SW = sqrt(1 - pow(mW/mZ,2));
      const std::vector<double> ml = {0, mMu, mTau};
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

      result = THDM_Bs2ll(l, lp, sminputs, spectrum);
    }

    void THDM_Bs2tautau(double &result)
    {
      using namespace Pipes::THDM_Bs2tautau;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;
      const int l = 2, lp = 2;

      result = THDM_Bs2ll(l, lp, sminputs, spectrum);
    }

    double THDM_B2Kll(int l, int lp, SMInputs sminputs, Spectrum spectrum)
    {
      //constants from 1903.10440
      const double a_ktaumu = 9.6;
      const double b_ktaumu = 10.0;
      const double a_kmue = 15.4;
      const double b_kmue = 15.7;
      const std::vector<double> akll = {a_kmue, a_ktaumu};
      const std::vector<double> bkll = {b_kmue, b_ktaumu};

      std::complex<double> C9 = THDM_DeltaC_NP(9, l, lp, sminputs, spectrum);
      std::complex<double> C9p = THDM_DeltaC_NP(11, l, lp, sminputs, spectrum);
      std::complex<double> C10 = THDM_DeltaC_NP(10, l, lp, sminputs, spectrum);
      std::complex<double> C10p = THDM_DeltaC_NP(12, l, lp, sminputs, spectrum);
      std::complex<double> C9lp = THDM_DeltaC_NP(9, lp, l, sminputs, spectrum);
      std::complex<double> C9plp = THDM_DeltaC_NP(11, lp, l, sminputs, spectrum);
      std::complex<double> C10lp = THDM_DeltaC_NP(10, lp, l, sminputs, spectrum);
      std::complex<double> C10plp = THDM_DeltaC_NP(12, lp, l, sminputs, spectrum);

      return 10e-9*(akll[lp]*norm(C9+C9p)+bkll[lp]*norm(C10+C10p)+(akll[lp]*norm(C9lp+C9plp)+bkll[lp]*norm(C10lp+C10plp)));
    }

    void THDM_B2Ktaumu(double &result)
    {
      using namespace Pipes::THDM_B2Ktaumu;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;
      const int l = 2, lp = 1;

      result = THDM_B2Kll(l, lp, sminputs, spectrum);
    }

    void THDM_B2Kmue(double &result)
    {
      using namespace Pipes::THDM_B2Kmue;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;
      const int l = 1, lp = 0;

      result = THDM_B2Kll(l, lp, sminputs, spectrum);
    }

    /// Branching ratio B+ ->K+ tau tau
    //  TODO: this function should be deleted once BRBKtautau_CONV is removed from the SuperIso frontend
    void SuperIso_prediction_BRBKtautau(double &result)
    {
      using namespace Pipes::SuperIso_prediction_BRBKtautau;
      if (flav_debug) std::cout<<"Starting SuperIso_prediction_BRBKtautau"<< std::endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      double mB = 5.27926;
      double mK = 0.493677;
      const double mTau = Dep::SMINPUTS->mTau;
      double Q2min = 4*mTau*mTau;
      double Q2max = pow(mB-mK,2);
      result=BEreq::BRBKtautau_CONV(&param,byVal(Q2min),byVal(Q2max));

      if (flav_debug) printf("BR(B=->K+ tau tau)=%.3e\n",result);
      if (flav_debug) std::cout<<"Finished SuperIso_prediction_BRBKtautau"<< std::endl;
    }

    /// 2-to-3-body decay ratio for semileptonic K and pi decays
    void SuperIso_prediction_Rmu23(double &result)
    {
      using namespace Pipes::SuperIso_prediction_Rmu23;
      if (flav_debug) std::cout<<"Starting SuperIso_prediction_Rmu23"<< std::endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result = BEreq::Rmu23(&param);

      if (flav_debug) printf("Rmu23=%.3e\n",result);
      if (flav_debug) std::cout<<"Finished SuperIso_prediction_Rmu23"<< std::endl;
    }

    /// Delta_0 (CP-averaged isospin asymmetry of B -> K* gamma)
    void SuperIso_prediction_delta0(double &result)
    {
      using namespace Pipes::SuperIso_prediction_delta0;
      if (flav_debug) std::cout<<"Starting SuperIso_prediction_delta0"<< std::endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result=BEreq::modified_delta0(&param);

      if (flav_debug) printf("Delta0(B->K* gamma)=%.3e\n",result);
      if (flav_debug) std::cout<<"Finished SuperIso_prediction_delta0"<< std::endl;
    }

    /// Zero crossing of the forward-backward asymmetry of B -> X_s mu mu
    void SuperIso_prediction_A_BXsmumu_zero(double &result)
    {
      using namespace Pipes::SuperIso_prediction_A_BXsmumu_zero;
      if (flav_debug) std::cout<<"Starting SuperIso_prediction_A_BXsmumu_zero"<< std::endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result=BEreq::A_BXsmumu_zero(&param);

      if (flav_debug) printf("AFB(B->Xs mu mu)_zero=%.3e\n",result);
      if (flav_debug) std::cout<<"Finished SuperIso_prediction_A_BXsmumu_zero"<< std::endl;
    }

    /// Inclusive branching fraction B -> X_s tau tau at high q^2
    void SuperIso_prediction_BRBXstautau_highq2(double &result)
    {
      using namespace Pipes::SuperIso_prediction_BRBXstautau_highq2;
      if (flav_debug) std::cout<<"Starting SuperIso_prediction_BRBXstautau_highq2"<< std::endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result=BEreq::BRBXstautau_highq2(&param);

      if (flav_debug) printf("BR(B->Xs tau tau)_highq2=%.3e\n",result);
      if (flav_debug) std::cout<<"Finished SuperIso_prediction_BRBXstautau_highq2"<< std::endl;
    }

    /// Forward-backward asymmetry of B -> X_s tau tau at high q^2
    void SuperIso_prediction_A_BXstautau_highq2(double &result)
    {
      using namespace Pipes::SuperIso_prediction_A_BXstautau_highq2;
      if (flav_debug) std::cout<<"Starting SuperIso_prediction_A_BXstautau_highq2"<< std::endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result=BEreq::A_BXstautau_highq2(&param);

      if (flav_debug) printf("AFB(B->Xs tau tau)_highq2=%.3e\n",result);
      if (flav_debug) std::cout<<"Finished SuperIso_prediction_A_BXstautau_highq2"<< std::endl;
    }

    /// RK* for RHN, using same approximations as RK, low q^2
    void RHN_RKstar_01_11(double &result)
    {
      using namespace Pipes::RHN_RKstar_01_11;
      SMInputs sminputs = *Dep::SMINPUTS;
      Eigen::Matrix3cd Theta = *Dep::SeesawI_Theta;
      std::vector<double> mN = {*Param["M_1"],*Param["M_2"],*Param["M_3"]};
      double mt = *Param["mT"];

      if (flav_debug) std::cout << "Starting RHN_RKstar_01_11" << std::endl;

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

      if (flav_debug) std::cout << "RK = " << result << std::endl;
      if (flav_debug) std::cout << "Finished RHN_RKstar_01_11" << std::endl;
    }

    /// RK* for RHN, using same approximations as RK, intermediate q^2
    void RHN_RKstar_11_60(double &result)
    {
      using namespace Pipes::RHN_RKstar_11_60;
      SMInputs sminputs = *Dep::SMINPUTS;
      Eigen::Matrix3cd Theta = *Dep::SeesawI_Theta;
      std::vector<double> mN = {*Param["M_1"],*Param["M_2"],*Param["M_3"]};
      double mt = *Param["mT"];

      if (flav_debug) std::cout << "Starting RHN_RKstar_11_60" << std::endl;

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

      if (flav_debug) std::cout << "RK = " << result << std::endl;
      if (flav_debug) std::cout << "Finished RHN_RKstar_11_60" << std::endl;
    }

    /// RK for RHN
    void RHN_RK(double &result)
    {
      using namespace Pipes::RHN_RK;
      SMInputs sminputs = *Dep::SMINPUTS;
      Eigen::Matrix3cd Theta = *Dep::SeesawI_Theta;
      std::vector<double> mN = {*Param["M_1"],*Param["M_2"],*Param["M_3"]};
      double mt = *Param["mT"];

      if (flav_debug) std::cout << "Starting RHN_RK" << std::endl;

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

      if (flav_debug) std::cout << "RK = " << result << std::endl;
      if (flav_debug) std::cout << "Finished RHN_RK" << std::endl;
    }

    /// Isospin asymmetry of B-> K* mu mu
    void SuperIso_prediction_AI_BKstarmumu(double &result)
    {
      using namespace Pipes::SuperIso_prediction_AI_BKstarmumu;
      if (flav_debug) std::cout<<"Starting SuperIso_prediction_AI_BKstarmumu"<< std::endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result=BEreq::modified_AI_BKstarmumu(&param);

      if (flav_debug) printf("A_I(B->K* mu mu)_lowq2=%.3e\n",result);
      if (flav_debug) std::cout<<"Finished SuperIso_prediction_AI_BKstarmumu"<< std::endl;
    }

    /// Zero crossing of isospin asymmetry of B-> K* mu mu
    void SuperIso_prediction_AI_BKstarmumu_zero(double &result)
    {
      using namespace Pipes::SuperIso_prediction_AI_BKstarmumu_zero;

      if (flav_debug) std::cout<<"Starting SuperIso_prediction_AI_BKstarmumu_zero"<< std::endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result=BEreq::modified_AI_BKstarmumu_zero(&param);

      if (flav_debug) printf("A_I(B->K* mu mu)_zero=%.3e\n",result);
      if (flav_debug) std::cout<<"Finished SuperIso_prediction_AI_BKstarmumu_zero"<< std::endl;
    }

    // Kahler function
    double lambdaK(double q2, double mB, double mK)
    {
      return mB*mB*mB*mB + mK*mK*mK*mK + q2*q2 - 2.*mB*mB*mK*mK - 2.*mK*mK*q2 - 2.*mB*mB*q2;
    }

    /// Calculaton of dGamma(B->Knunu)/dq2
    // Expression taken from 2107.01080
    double dGammaBKnunudq2(double q2, ModelParameters param, SMInputs sminputs, double mB, double mK)
    {
      // CKM parameters
      const double A      = sminputs.CKM.A;
      const double lambda = sminputs.CKM.lambda;
      const double Vts = -A*lambda*lambda;
      const double Vtb = 1 - (1/2)*A*A*pow(lambda,4);

      // TODO: Using mb(mb) not pole mass
      const double mb = sminputs.mBmB;
      const double ms = sminputs.mS;

      // Standard Model value for CLL
      // Took this from Table 1 in Bednyakov et al
      const double CLLSM = 4.1;
      const double CLLSM_uncert = 0.5;

      // Extract Wilson coefficients from model
      std::complex<double> CVLL = {param["Re_DeltaCLL_V"], param["Im_DeltaCLL_V"]};
      std::complex<double> CVLR = {param["Re_DeltaCLR_V"], param["Im_DeltaCLR_V"]};
      std::complex<double> CVRL = {param["Re_DeltaCRL_V"], param["Im_DeltaCRL_V"]};
      std::complex<double> CVRR = {param["Re_DeltaCRR_V"], param["Im_DeltaCRR_V"]};
      std::complex<double> CSLL = {param["Re_DeltaCLL_S"], param["Im_DeltaCLL_S"]};
      std::complex<double> CSLR = {param["Re_DeltaCLR_S"], param["Im_DeltaCLR_S"]};
      std::complex<double> CSRL = {param["Re_DeltaCRL_S"], param["Im_DeltaCRL_S"]};
      std::complex<double> CSRR = {param["Re_DeltaCRR_S"], param["Im_DeltaCRR_S"]};
      std::complex<double> CTLL = {param["Re_DeltaCLL_T"], param["Im_DeltaCLL_T"]};
      std::complex<double> CTRR = {param["Re_DeltaCRR_T"], param["Im_DeltaCRR_T"]};


      // The WCs are assumed to be diagonal in flavour, so we add a prefactor of 3 for the number of flavours
      const double Nf = 3;

      // Form factors
      // TODO: Missing
      const double fp = 1;
      const double f0 = 1;
      const double fT = 1;

      // Helicity amplitudes
      const double HV = sqrt(lambdaK(q2, mB, mK)/q2)*fp;
      const double HS = (mB*mB - mK*mK)/(mb - ms)*f0;
      const double HT = - sqrt(lambdaK(q2, mB, mK))*(mB + mK)*fT;

      double dGammadq2 = Nf*pow(sminputs.GF * Vts * Vtb / sminputs.alphainv,2) / (192. * 16*pow(pi,5)*pow(mb,3)) * q2 * pow(lambdaK(q2, mB, mK),1/2) * ( std::norm(CLLSM + CVLL + CVRL) + std::norm(CVLR + CVRR)  * HV*HV + 3./2 * ( std::norm(CSRL + CSLL) + std::norm(CSRR + CSLR) ) * HS*HS + 8.*(std::norm(CTLL) + std::norm(CTRR)) * HT*HT);

      return dGammadq2;
    }

    /// Calculaton of dGamma(B->Kstarnunu)/dq2
    // Expression taken from 2107.01080
    double dGammaBKstarnunudq2(double q2, ModelParameters param, SMInputs sminputs, double mB, double mKstar)
    {
      // CKM parameters
      const double A      = sminputs.CKM.A;
      const double lambda = sminputs.CKM.lambda;
      const double Vts = -A*lambda*lambda;
      const double Vtb = 1 - (1/2)*A*A*pow(lambda,4);

      // TODO: Using mb(mb) not pole mass
      const double mb = sminputs.mBmB;
      const double mc = sminputs.mCmC;

      // Standard Model value for CLL
      // Took this from Table 1 in Bednyakov et al
      const double CLLSM = 4.1;
      const double CLLSM_uncert = 0.5;

      // Extract Wilson coefficients from model
      std::complex<double> CVLL = {param["Re_DeltaCLL_V"], param["Im_DeltaCLL_V"]};
      std::complex<double> CVLR = {param["Re_DeltaCLR_V"], param["Im_DeltaCLR_V"]};
      std::complex<double> CVRL = {param["Re_DeltaCRL_V"], param["Im_DeltaCRL_V"]};
      std::complex<double> CVRR = {param["Re_DeltaCRR_V"], param["Im_DeltaCRR_V"]};
      std::complex<double> CSLL = {param["Re_DeltaCLL_S"], param["Im_DeltaCLL_S"]};
      std::complex<double> CSLR = {param["Re_DeltaCLR_S"], param["Im_DeltaCLR_S"]};
      std::complex<double> CSRL = {param["Re_DeltaCRL_S"], param["Im_DeltaCRL_S"]};
      std::complex<double> CSRR = {param["Re_DeltaCRR_S"], param["Im_DeltaCRR_S"]};
      std::complex<double> CTLL = {param["Re_DeltaCLL_T"], param["Im_DeltaCLL_T"]};
      std::complex<double> CTRR = {param["Re_DeltaCRR_T"], param["Im_DeltaCRR_T"]};

      // The WCs are assumed to be diagonal in flavour, so we add a prefactor of 3 for the number of flavours
      const double Nf = 3;

      // Form factors
      // TODO: Missing
      const double A12 = 1;
      const double A1 = 1, A0 = 1, V = 1;
      const double T23 = 0, T1 = 0, T2 = 0;

      // Helicity amplitudes
      const double HV0 = 8./sqrt(q2)*mB*mKstar*A12;
      const double HVp = (mB + mKstar)*A1 - sqrt(lambdaK(q2, mB, mKstar))/(mB + mKstar)*V;
      const double HVm = (mB + mKstar)*A1 + sqrt(lambdaK(q2, mB, mKstar))/(mB + mKstar)*V;
      const double HS = -sqrt(lambdaK(q2, mB, mKstar))/(mb + mc)*A0;
      const double HT0 = -(4.*mB*mKstar)/(mB + mKstar)*T23;
      const double HTp = 1./sqrt(q2)*((mB*mB - mKstar*mKstar)*T2 + sqrt(lambdaK(q2, mB, mKstar))*T1);
      const double HTm = 1./sqrt(q2)*(-(mB*mB - mKstar*mKstar)*T2 + sqrt(lambdaK(q2, mB, mKstar))*T1);

      double dGammadq2 = Nf*pow(sminputs.GF * Vts * Vtb / sminputs.alphainv,2) / (192. * 16*pow(pi,5)*pow(mb,3)) * q2 * pow(lambdaK(q2, mB, mKstar),1/2) * ( std::norm(CLLSM + CVLL)*(HVp*HVp+HVm*HVm) + std::norm(CLLSM + CVLL - CVRL)*HV0*HV0 - 4.*std::real((CLLSM + CVLL)*std::conj(CVRL))*HVp*HVm + (std::norm(CVRL) + std::norm(CVLR) + std::norm(CVRR))*(HVp*HVp+HVm*HVm) + std::norm(CVLR - CVRR)*HV0*HV0 -4.*std::real(CVLR*std::conj(CVRR))*HVp*HVm + 3./2*(std::norm(CSRL - CSLL) + std::norm(CSRR - CSLR))*HS*HS + 8.*(std::norm(CTLL) + std::norm(CTRR))*(HTp*HTp + HTm*HTm + HT0*HT0));

      return dGammadq2;
    }

    /// Calculation of BR(B -> K nu nu)
    void BKnunu(double &result)
    {
      using namespace Pipes::BKnunu;

      // Meson masses
      const double mB = Mesons_masses::B_0;
      const double mK = Mesons_masses::kaon0;

      std::function<double(double)> dGammadq2 = [&](double q2)
      {
        return dGammaBKnunudq2(q2, *Dep::WC_nunu_parameters, *Dep::SMINPUTS, mB, mK);
      };

      // Integration limits and variables
      double q2min = 0., q2max = pow(mB - mK,2);
      static double epsabs = 0;
      static double epsrel = 1e-2;

      result = Utils::integrate_cquad(dGammadq2, q2min, q2max, epsabs, epsrel);

    }

    /// Calculation of FL_Knunu
    /// Based on equation 8 of 2107.01080
    double FL_Knunu_q2(double q2, ModelParameters param, SMInputs sminputs, double mB, double mKstar)
    {
      // CKM parameters
      const double A      = sminputs.CKM.A;
      const double lambda = sminputs.CKM.lambda;
      const double Vts = -A*lambda*lambda;
      const double Vtb = 1 - (1/2)*A*A*pow(lambda,4);

      // TODO: Using mb(mb) not pole mass
      const double mb = sminputs.mBmB;

      // Standard Model value for CLL
      // Took this from Table 1 in Bednyakov et al
      const double CLLSM = 4.1;
      const double CLLSM_uncert = 0.5;

      // Extract Wilson coefficients from model
      std::complex<double> CVLL = {param["Re_DeltaCLL_V"], param["Im_DeltaCLL_V"]};
      std::complex<double> CVLR = {param["Re_DeltaCLR_V"], param["Im_DeltaCLR_V"]};
      std::complex<double> CVRL = {param["Re_DeltaCRL_V"], param["Im_DeltaCRL_V"]};
      std::complex<double> CVRR = {param["Re_DeltaCRR_V"], param["Im_DeltaCRR_V"]};
      std::complex<double> CTLL = {param["Re_DeltaCLL_T"], param["Im_DeltaCLL_T"]};
      std::complex<double> CTRR = {param["Re_DeltaCRR_T"], param["Im_DeltaCRR_T"]};

      // The WCs are assumed to be diagonal in flavour, so we add a prefactor of 3 for the number of flavours
      const double Nf = 3;

      // Form factors
      // TODO: Missing
      const double A12 = 1;
      const double T23 = 0;

      // Helicity amplitudes
      const double HV0 = 8./sqrt(q2)*mB*mKstar*A12;
      const double HT0 = -(4.*mB*mKstar)/(mB + mKstar)*T23;

      double FL_Knunu_q2 = Nf*pow(sminputs.GF * Vts * Vtb / sminputs.alphainv,2) / (192. * 16*pow(pi,5)*pow(mb,3)) * q2 * pow(lambdaK(q2,mB,mKstar),1/2) * (1./dGammaBKstarnunudq2(q2, param, sminputs, mB, mKstar)) * (std::norm(CLLSM + CVLL - CVRL) * HV0*HV0 - 8.*std::norm(CTLL) * HT0*HT0 + std::norm(CVLR - CVRR)  * HV0*HV0 -8.* std::norm(CTRR) * HT0*HT0 );

      return FL_Knunu_q2;

    }

    /// Calculation of FL_Knunu
    void FL_Knunu(double &result)
    {
      using namespace Pipes::FL_Knunu;

      // Meson masses
      const double mB = Mesons_masses::B_0;
      const double mK = Mesons_masses::kaon0;

      std::function<double(double)> FL_q2 = [&](double q2)
      {
        return FL_Knunu_q2(q2, *Dep::WC_nunu_parameters, *Dep::SMINPUTS, mB, mK);
      };

      // Integration limits and variables
      double q2min = 0., q2max = pow(mB - mK,2);
      static double epsabs = 0;
      static double epsrel = 1e-2;

      result = Utils::integrate_cquad(FL_q2, q2min, q2max, epsabs, epsrel);

    }

    /// Calculation of BR(B_u+ -> K+ nu nu)
    void BuKnunu(double &result)
    {
      using namespace Pipes::BuKnunu;

      // Meson masses
      const double mB = Mesons_masses::B_plus;
      const double mK = Mesons_masses::kaon_plus;

      std::function<double(double)> dGammadq2 = [&](double q2)
      {
        return dGammaBKnunudq2(q2, *Dep::WC_nunu_parameters, *Dep::SMINPUTS, mB, mK);
      };

      // Integration limits and variables
      double q2min = 0., q2max = pow(mB - mK,2);
      static double epsabs = 0;
      static double epsrel = 1e-2;

      result = Utils::integrate_cquad(dGammadq2, q2min, q2max, epsabs, epsrel);

    }

    /// Calculation of BR(B -> K* nu nu)
    void BKstarnunu(double &result)
    {
      using namespace Pipes::BKstarnunu;

      // Meson masses
      const double mB = Mesons_masses::B_0;
      const double mK = Mesons_masses::kaonstar0;

      std::function<double(double)> dGammadq2 = [&](double q2)
      {
        return dGammaBKstarnunudq2(q2, *Dep::WC_nunu_parameters, *Dep::SMINPUTS, mB, mK);
      };

      // Integration limits and variables
      double q2min = 0., q2max = pow(mB - mK,2);
      static double epsabs = 0;
      static double epsrel = 1e-2;

      result = Utils::integrate_cquad(dGammadq2, q2min, q2max, epsabs, epsrel);

    }

   /// Calculation of BR(B_u+ -> K*+ nu nu)
    void BuKstarnunu(double &result)
    {
      using namespace Pipes::BuKstarnunu;

      // Meson masses
      const double mB = Mesons_masses::B_plus;
      const double mK = Mesons_masses::kaonstar_plus;

      std::function<double(double)> dGammadq2 = [&](double q2)
      {
        return dGammaBKstarnunudq2(q2, *Dep::WC_nunu_parameters, *Dep::SMINPUTS, mB, mK);
      };

      // Integration limits and variables
      double q2min = 0., q2max = pow(mB - mK,2);
      static double epsabs = 0;
      static double epsrel = 1e-2;

      result = Utils::integrate_cquad(dGammadq2, q2min, q2max, epsabs, epsrel);

    }

    /// Observable: RKnunu = BR(B_u+ -> K+ nu nu) / BR(B_u+ -> K+ nu nu)_SM
    void RKnunu(double &result)
    {
      using namespace Pipes::RKnunu;

      // SM prediction for BR(B_u+ -> K+ nu nu), from 2107.01080
      const double BuKnunuSM = 4.6e-6;
      const double BuKnunuSM_uncert = 0.5e-6;

      result = *Dep::BuKnunu / BuKnunuSM;
    }

    /// Observable: RKstarnunu = BR(B -> Kstar nu nu) / BR(B -> Kstar nu nu)_SM
    void RKstarnunu(double &result)
    {
      using namespace Pipes::RKstarnunu;

      // SM prediction for BR(B -> Kstar nu nu), from 2107.01080
      // TODO: I think this is outdated, check
      const double BKstarnunuSM = 8.4e-6;
      const double BKstarnunuSM_uncert = 1.5e-6;

      result = *Dep::BKstarnunu / BKstarnunuSM;
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
    void Bs2ll_likelihood(double &result)
    {
      using namespace Pipes::Bs2ll_likelihood;

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
     if(flav_debug) std::cout << "Bs -> mu tau = " << theory[0] << std::endl;
     theory[1] = *Dep::Bs2tautau;
     if(flav_debug) std::cout << "Bs -> tau+ tau- = " << theory[1] << std::endl;

     result = 0;
     for (int i = 0; i < 2; ++i)
       result += Stats::gaussian_upper_limit(theory[i], value_exp(i,0), th_err[i], sqrt(cov_exp(i,i)), false);
    }

    /// Likelihood for B+->K+ l- l+
    void B2Kll_likelihood(double &result)
    {
      using namespace Pipes::B2Kll_likelihood;

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
     if(flav_debug) std::cout << "B ->K tau mu = " << theory[0] << std::endl;
     theory[1] = *Dep::B2Kmue;
     if(flav_debug) std::cout << "B ->K mu e = " << theory[1] << std::endl;
     theory[2] = *Dep::B2Ktautau;
     // theory[2] = Dep::B2Ktautau->central_values.at("BKtautauBr");
     if(flav_debug) std::cout << "B ->K tau tau = " << theory[2] << std::endl;

     result = 0;
     for (int i = 0; i < 3; ++i)
       result += Stats::gaussian_upper_limit(theory[i], value_exp(i,0), th_err[i], sqrt(cov_exp(i,i)), false);
    }

    /// Likelihood for B2Xsnunu
    /// Uses the obseravables RKnunu and RKstarnunu
    void B2Xsnunu_likelihood(double &result)
    {
      using namespace Pipes::B2Xsnunu_likelihood;

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
     if(flav_debug) std::cout << "RKnunu = " << theory[0] << std::endl;
     theory[1] = *Dep::RKstarnunu;
     if(flav_debug) std::cout << "RKstarnunu = " << theory[1] << std::endl;

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
        if (flav_debug) std::cout << "Debug: Reading HepLike data file: " << inputfile << std::endl;
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
        if (flav_debug) std::cout << "Debug: Reading HepLike data file: " << inputfile << std::endl;
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
        if (flav_debug) std::cout << "Debug: Reading HepLike data file: " << inputfile << std::endl;
        nDimLikelihood.Read();
        update_obs_list(obs_list, nDimLikelihood.GetObservables());
        first = false;
      }

      /* nDimLikelihood does not support theory errors */
      result = nDimLikelihood.GetLogLikelihood(get_obs_theory(*Dep::prediction_B2mumu, obs_list));

      if (flav_debug) std::cout << "HEPLike_B2mumu_LogLikelihood_LHCb result: " << result << std::endl;
    }

    /// HEPLike LogLikelihood B -> l l (combination CMS ATLAS LHCb)
    /// Recognised sub-capabilities:
    ///    BRuntag_Bsmumu
    ///    BR_Bdmumu
    void HEPLike_B2mumu_LogLikelihood_CMS_ATLAS_LHCb(double &result)
    {
      if (flav_debug) std::cout << "Starting HEPLike_B2mumu_LogLikelihood_CMS_ATLAS_LHCb"<<std::endl;
      using namespace Pipes::HEPLike_B2mumu_LogLikelihood_CMS_ATLAS_LHCb;
      static const std::string inputfile = path_to_latest_heplike_data() + "/data/B2MuMu_CMS-ATLAS-LHCb/CMS-ATLAS-LHCb-2022-combination.yaml";
      static std::vector<str> obs_list = Downstream::subcaps->getNames();
      static std::vector<HepLike_default::HL_nDimGaussian> nDimGaussian;

      if (obs_list.empty()) FlavBit_error().raise(LOCAL_INFO, "No subcapabilities specified!");

      nDimGaussian.push_back(HepLike_default::HL_nDimGaussian(inputfile));
      nDimGaussian[0].Read();
      update_obs_list(obs_list, nDimGaussian[0].GetObservables());

      result = 0;
      result += nDimGaussian[0].GetLogLikelihood(get_obs_theory(*Dep::prediction_B2mumu, obs_list), get_obs_covariance(*Dep::prediction_B2mumu, obs_list));

      if (flav_debug) std::cout << "HEPLike_B2mumu_LogLikelihood_CMS_ATLAS_LHCb result: " << result << std::endl;
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
          if (flav_debug) std::cout << "Debug: Reading HepLike data file: " << inputfile + pred.first + ".yaml" << std::endl;
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
          if (flav_debug) std::cout << "Debug: Reading HepLike data file: " << inputfile + pred.first + ".yaml" << std::endl;
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
          if (flav_debug) std::cout << "Debug: Reading HepLike data file: " << inputfile + pred.first + ".yaml" << std::endl;
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
          if (flav_debug) std::cout << "Debug: Reading HepLike data file: " << inputfile + pred.first + ".yaml" << std::endl;
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
          if (flav_debug) std::cout << "Debug: Reading HepLike data file: " << inputfile + pred.first + ".yaml" << std::endl;
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
          if (flav_debug) std::cout << "Debug: Reading HepLike data file: " << inputfile + pred.first + ".yaml" << std::endl;
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
          if (flav_debug) std::cout << "Debug: Reading HepLike data file: " << inputfile + pred.first + "_CPA.yaml" << std::endl;
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
          if (flav_debug) std::cout << "Debug: Reading HepLike data file: " << inputfile + pred.first + ".yaml" << std::endl;
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

      flav_binned_prediction binned_prediction= *Dep::prediction_Bu2KstarmumuAng_LHCb;
      std::vector<flav_prediction> prediction;
      for(auto pred : binned_prediction)
        prediction.push_back(pred.second);

      static bool first = true;
      if (first)
      {
        for (auto pred : binned_prediction)
        {
          nDimGaussian.push_back(HepLike_default::HL_nDimGaussian(inputfile + pred.first + ".yaml"));
          if (flav_debug) std::cout << "Debug: Reading HepLike data file: " << inputfile + pred.first + ".yaml" << std::endl;
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

      if (flav_debug) std::cout << "HEPLike_Bu2KstarmumuAng_LogLikelihood_LHCb result: " << result << std::endl;
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
          if (flav_debug) std::cout << "Debug: Reading HepLike data file " <<  inputfile + pred.first + ".yaml"  << std::endl;
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
          if (flav_debug) std::cout << "Debug: Reading HepLike data file " << inputfile + pred.first + ".yaml" << std::endl;
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
          if (flav_debug) std::cout << "Debug: Reading HepLike data file " << inputfile + pred.first + ".yaml" << std::endl;
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


    /// Likelihood for RKstar
    void RKstar_LogLikelihood_LHCb(double &result)
    {
      using namespace Pipes::RKstar_LogLikelihood_LHCb;

      static double value_exp[2], value_th[2];
      static boost::numeric::ublas::matrix<double> cov_exp, cov_th;

      static bool first = true;

      static double theory_RKstar_0045_11_err, theory_RKstar_11_60_err;

      // Read and calculate things based on the observed data only the first time through, as none of it depends on the model parameters.
      if (first)
      {

        Flav_reader fread(GAMBIT_DIR  "/FlavBit/data");
        fread.debug_mode(flav_debug);

        fread.read_yaml_measurement("flav_data.yaml", "RKstar_0045_11");
        fread.read_yaml_measurement("flav_data.yaml", "RKstar_11_60");

        fread.initialise_matrices();

        theory_RKstar_0045_11_err = fread.get_th_err()(0,0).first;
        theory_RKstar_11_60_err = fread.get_th_err()(1,0).first;

        value_exp[0] = fread.get_exp_value()(0,0);
        value_exp[1] = fread.get_exp_value()(1,0);
        cov_exp=fread.get_exp_cov();

        // Init over and out.
        first = false;
      }

      // Get theory prediction
      value_th[0] = *Dep::RKstar_0045_11;
      value_th[1] = *Dep::RKstar_11_60;

      // Compute error on theory prediction and populate the covariance matrix
      cov_th.resize(2,2);
      cov_th(0,0) = theory_RKstar_0045_11_err;
      cov_th(0,1) = 0.0;
      cov_th(1,0) = 0.0;
      cov_th(1,1) = theory_RKstar_11_60_err;

      // Calculating the differences between theory and experiment
      std::vector<double> diff;
      diff.push_back(value_exp[0] - value_th[0]);
      diff.push_back(value_exp[1] - value_th[1]);

      // adding theory and experimental covariance
      boost::numeric::ublas::matrix<double> cov = cov_exp + cov_th;

      boost::numeric::ublas::matrix<double> cov_inv(2,2);
      InvertMatrix(cov, cov_inv);

      double Chi2=0;
      for (int i=0; i<2; ++i)
        for (int j=0; j<2; ++j)
          Chi2 += diff[i] * cov_inv(i,j) * diff[j];
      result=-0.5*Chi2;
    }

    /// HEPLike LogLikelihood for RK and RKstar (LHCb)
    /// Recognised sub-capabilities:
    ///    RK_low
    ///    RK_central
    ///    RKstar_low
    ///    RKstar_central
    void HEPLike_RKRKstar_LogLikelihood_LHCb(double &result)
    {
      using namespace Pipes::HEPLike_RKRKstar_LogLikelihood_LHCb;

      static const std::string inputfile = path_to_latest_heplike_data() + "/data/LHCb/RD/RKRKstar/CERN-EP-2022-278.yaml";
      static std::vector<str> obs_list = Downstream::subcaps->getNames();
      static HepLike_default::HL_nDimBifurGaussian nDimBifurGaussian(inputfile);

      if (obs_list.empty()) FlavBit_error().raise(LOCAL_INFO, "No subcapabilities specified!");

      flav_binned_prediction binned_prediction = *Dep::prediction_RKRKstar_LHCb;

      // HepLikeData has correlations across bins for RK-RKstar, so convert into single-bin, multi-observable prediction
      flav_prediction prediction;
      std::vector<str> new_obs_list;
      for(auto pred: binned_prediction)
      {
        for(auto val : pred.second.central_values)
        {
          prediction.central_values[val.first+"_"+pred.first] = val.second;

          // Change observable list
          if(std::find(obs_list.begin(), obs_list.end(), val.first) != obs_list.end() )
            new_obs_list.push_back(val.first+"_"+pred.first);
        }

        for(auto cov1 : pred.second.covariance)
          for(auto cov2 : cov1.second)
          {
            prediction.covariance[cov1.first+"_"+pred.first][cov2.first+"_"+pred.first] = cov2.second;
          }

      }
      // Fill the uncorrelated covariance entries
      for(auto cov1 : prediction.covariance)
        for(auto cov2 : prediction.covariance)
          if(cov1.second.find(cov2.first) == cov1.second.end())
            prediction.covariance[cov1.first][cov2.first] = 0.;

      static bool first = true;
      if (first)
      {
        if (flav_debug) std::cout << "Debug: Reading HepLike data file: " << inputfile  << std::endl;
        nDimBifurGaussian.Read();
        update_obs_list(new_obs_list, nDimBifurGaussian.GetObservables());
        first = false;
      }

      result = nDimBifurGaussian.GetLogLikelihood(get_obs_theory(prediction, new_obs_list), get_obs_covariance(prediction, new_obs_list));
      if (flav_debug) std::cout << "HEPLike_RKRKstar_LogLikelihood_LHCb result: " << result << std::endl;

    }

    /// HEPLike LogLikehood for BR(B -> K nu nu) from Belle with semileptonic tagging
    void HEPLike_BKnunu_LogLikelihood_Belle_sl(double &result)
    {
      using namespace Pipes::HEPLike_BKnunu_LogLikelihood_Belle_sl;

      static const std::string inputfile = heplike_data_file("/data/Belle/Semileptonic/B2KNuNu/KEK-2017-6.yaml");
      static HepLike_default::HL_Limit Limit(inputfile);

      static bool first = true;
      if (first)
      {
        Limit.Read();
        first = false;
      }

      const double theory = *Dep::BKnunu;
      // TODO: Deal properly with theory uncertainty
      const double theory_variance = 0.001;

      // TODO: Implement theory uncertainty of HL_Limit
      result = Limit.GetLogLikelihood(theory);
    }

    /// HEPLike LogLikehood for BR(B -> K nu nu) from Belle with hadronic tagging
    void HEPLike_BKnunu_LogLikelihood_Belle_had(double &result)
    {
      using namespace Pipes::HEPLike_BKnunu_LogLikelihood_Belle_had;

      static const std::string inputfile = heplike_data_file("/data/Belle/Hadronic/B2KNuNu/KEK-2012-37.yaml");
      static HepLike_default::HL_Limit Limit(inputfile);

      static bool first = true;
      if (first)
      {
        Limit.Read();
        first = false;
      }

      const double theory = *Dep::BKnunu;
      // TODO: Deal properly with theory uncertainty
      const double theory_variance = 0.001;

      // TODO: Implement theory uncertainty of HL_Limit
      result = Limit.GetLogLikelihood(theory);
    }

    /// HEPLike LogLikehood for BR(B_u+ -> K+ nu nu) from Belle with semileptonic tagging
    void HEPLike_BuKnunu_LogLikelihood_Belle_sl(double &result)
    {
      using namespace Pipes::HEPLike_BuKnunu_LogLikelihood_Belle_sl;

      static const std::string inputfile = heplike_data_file("/data/Belle/Semileptonic/Bu2KNuNu/KEK-2017-6.yaml");
      static HepLike_default::HL_Limit Limit(inputfile);

      static bool first = true;
      if (first)
      {
        Limit.Read();
        first = false;
      }

      const double theory = *Dep::BuKnunu;
      // TODO: Deal properly with theory uncertainty
      const double theory_variance = 0.001;

      // TODO: Implement theory uncertainty of HL_Limit
      result = Limit.GetLogLikelihood(theory);
    }

    /// HEPLike LogLikehood for BR(B_u+ -> K+ nu nu) from Belle with hadronic tagging
    void HEPLike_BuKnunu_LogLikelihood_Belle_had(double &result)
    {
      using namespace Pipes::HEPLike_BuKnunu_LogLikelihood_Belle_had;

      static const std::string inputfile = heplike_data_file("/data/Belle/Hadronic/Bu2KNuNu/KEK-2012-37.yaml");
      static HepLike_default::HL_Limit Limit(inputfile);

      static bool first = true;
      if (first)
      {
        Limit.Read();
        first = false;
      }

      const double theory = *Dep::BuKnunu;
      // TODO: Deal properly with theory uncertainty
      const double theory_variance = 0.001;

      // TODO: Implement theory uncertainty of HL_Limit
      result = Limit.GetLogLikelihood(theory);
    }

    /// HEPLike LogLikehood for BR(B_u+ -> K+ nu nu) from BelleII
    void HEPLike_BuKnunu_LogLikelihood_BelleII(double &result)
    {
      using namespace Pipes::HEPLike_BuKnunu_LogLikelihood_BelleII;

      static const std::string inputfile = heplike_data_file("/data/BelleII/Inclusive/Bu2KNuNu/KEK-2020-45.yaml");
      static HepLike_default::HL_BifurGaussian BifurGaussian(inputfile);

      static bool first = true;
      if (first)
      {
        BifurGaussian.Read();
        first = false;
      }

      const double theory = *Dep::BuKnunu;
      // TODO: Deal properly with theory uncertainty
      const double theory_variance = 0.001;

      result = BifurGaussian.GetLogLikelihood(theory, theory_variance);
    }

    /// HEPLike LogLikehood for BR(B -> K* nu nu) from Belle with semileptonic tagging
    void HEPLike_BKstarnunu_LogLikelihood_Belle_sl(double &result)
    {
      using namespace Pipes::HEPLike_BKstarnunu_LogLikelihood_Belle_sl;

      static const std::string inputfile = heplike_data_file("/data/Belle/Semileptonic/B2KstarNuNu/KEK-2017-6.yaml");
      static HepLike_default::HL_Limit Limit(inputfile);

      static bool first = true;
      if (first)
      {
        Limit.Read();
        first = false;
      }

      const double theory = *Dep::BKstarnunu;
      // TODO: Deal properly with theory uncertainty
      const double theory_variance = 0.001;

      // TODO: Implement theory uncertainty of HL_Limit
      result = Limit.GetLogLikelihood(theory);
    }

    /// HEPLike LogLikehood for BR(B -> K* nu nu) from Belle with hadronic tagging
    void HEPLike_BKstarnunu_LogLikelihood_Belle_had(double &result)
    {
      using namespace Pipes::HEPLike_BKstarnunu_LogLikelihood_Belle_had;

      static const std::string inputfile = heplike_data_file("/data/Belle/Hadronic/B2KstarNuNu/KEK-2012-37.yaml");
      static HepLike_default::HL_Limit Limit(inputfile);

      static bool first = true;
      if (first)
      {
        Limit.Read();
        first = false;
      }

      const double theory = *Dep::BKstarnunu;
      // TODO: Deal properly with theory uncertainty
      const double theory_variance = 0.001;

      // TODO: Implement theory uncertainty of HL_Limit
      result = Limit.GetLogLikelihood(theory);
    }

    /// HEPLike LogLikehood for BR(B_u+ -> K*+ nu nu) from Belle with semileptonic tagging
    void HEPLike_BuKstarnunu_LogLikelihood_Belle_sl(double &result)
    {
      using namespace Pipes::HEPLike_BuKstarnunu_LogLikelihood_Belle_sl;

      static const std::string inputfile = heplike_data_file("/data/Belle/Semileptonic/Bu2KstarNuNu/KEK-2017-6.yaml");
      static HepLike_default::HL_Limit Limit(inputfile);

      static bool first = true;
      if (first)
      {
        Limit.Read();
        first = false;
      }

      const double theory = *Dep::BuKstarnunu;
      // TODO: Deal properly with theory uncertainty
      const double theory_variance = 0.001;

      // TODO: Implement theory uncertainty of HL_Limit
      result = Limit.GetLogLikelihood(theory);
    }

    /// HEPLike LogLikehood for BR(B_u+ -> K*+ nu nu) from Belle with hadronic tagging
    void HEPLike_BuKstarnunu_LogLikelihood_Belle_had(double &result)
    {
      using namespace Pipes::HEPLike_BuKstarnunu_LogLikelihood_Belle_had;

      static const std::string inputfile = heplike_data_file("/data/Belle/Hadronic/Bu2KstarNuNu/KEK-2012-37.yaml");
      static HepLike_default::HL_Limit Limit(inputfile);

      static bool first = true;
      if (first)
      {
        Limit.Read();
        first = false;
      }

      const double theory = *Dep::BuKstarnunu;
      // TODO: Deal properly with theory uncertainty
      const double theory_variance = 0.001;

      // TODO: Implement theory uncertainty of HL_Limit
      result = Limit.GetLogLikelihood(theory);
    }

    /// HEPLike LogLikelihood for BR(B -> K nu nu) from BaBar
    void HEPLike_BKnunu_LogLikelihood_BaBar(double &result)
    {
      using namespace Pipes::HEPLike_BKnunu_LogLikelihood_BaBar;

      static const std::string inputfile = heplike_data_file("/data/BaBar/Combined/B2KNuNu/BABAR-2013-002.yaml");
      static HepLike_default::HL_Limit Limit(inputfile);

      static bool first = true;
      if (first)
      {
        Limit.Read();
        first = false;
      }

      const double theory = *Dep::BKnunu;
      // TODO: Deal properly with theory uncertainty
      const double theory_variance = 0.001;

      // TODO: Implement theory uncertainty of HL_Limit
      result = Limit.GetLogLikelihood(theory);
    }

    /// HEPLike LogLikelihood for BR(B_u+ -> K+ nu nu) from BaBar
    void HEPLike_BuKnunu_LogLikelihood_BaBar(double &result)
    {
      using namespace Pipes::HEPLike_BuKnunu_LogLikelihood_BaBar;

      static const std::string inputfile = heplike_data_file("/data/BaBar/Combined/Bu2KNuNu/BABAR-2013-002.yaml");
      static HepLike_default::HL_Limit Limit(inputfile);

      static bool first = true;
      if (first)
      {
        Limit.Read();
        first = false;
      }

      const double theory = *Dep::BuKnunu;
      // TODO: Deal properly with theory uncertainty
      const double theory_variance = 0.001;

      // TODO: Implement theory uncertainty of HL_Limit
      result = Limit.GetLogLikelihood(theory);
    }

    /// HEPLike LogLikelihood for BR(B -> K* nu nu) from BaBar
    void HEPLike_BKstarnunu_LogLikelihood_BaBar(double &result)
    {
      using namespace Pipes::HEPLike_BKstarnunu_LogLikelihood_BaBar;

      static const std::string inputfile = heplike_data_file("/data/BaBar/Combined/B2KstarNuNu/BABAR-2013-002.yaml");
      static HepLike_default::HL_Limit Limit(inputfile);

      static bool first = true;
      if (first)
      {
        Limit.Read();
        first = false;
      }

      const double theory = *Dep::BKstarnunu;
      // TODO: Deal properly with theory uncertainty
      const double theory_variance = 0.001;

      // TODO: Implement theory uncertainty of HL_Limit
      result = Limit.GetLogLikelihood(theory);
    }

    /// HEPLike LogLikelihood for BR(B_u+ -> K*+ nu nu) from BaBar
    void HEPLike_BuKstarnunu_LogLikelihood_BaBar(double &result)
    {
      using namespace Pipes::HEPLike_BuKstarnunu_LogLikelihood_BaBar;

      static const std::string inputfile = heplike_data_file("/data/BaBar/Combined/Bu2KstarNuNu/BABAR-2013-002.yaml");
      static HepLike_default::HL_Limit Limit(inputfile);

      static bool first = true;
      if (first)
      {
        Limit.Read();
        first = false;
      }

      const double theory = *Dep::BuKstarnunu;
      // TODO: Deal properly with theory uncertainty
      const double theory_variance = 0.001;

      // TODO: Implement theory uncertainty of HL_Limit
      result = Limit.GetLogLikelihood(theory);
    }

  }
}
