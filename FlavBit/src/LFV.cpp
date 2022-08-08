//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Functions of module FlavBit:
///   - Lepton Flavour Violation
///     - tau -> e gamma, mu -> e gamma
///     - mu -> e e e, tau -> mu e e, tau -> mu mu e
///     - mu - e conversion (Ti, Pb, Au)
///     - ge/gmu
///
///  *********************************************
///
///  Authors (add name and date if you modify):
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
//
///  \author Douglas Jacob
///          (douglas.jacob@monash.edu)
///  \date 2020 Nov
///
///  *********************************************

#include "gambit/Utils/statistics.hpp"
#include "gambit/Elements/loop_functions.hpp"
#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/FlavBit/FlavBit_rollcall.hpp"
#include "gambit/FlavBit/Flav_reader.hpp"
#include "gambit/FlavBit/FlavBit_utils.hpp"

namespace Gambit
{
  namespace FlavBit
  {

    /// RHN predictions

    /// Contribution to mu -> e gamma from RHNs
    void RHN_muegamma(double &result)
    {
      using namespace Pipes::RHN_muegamma;
      SMInputs sminputs = *Dep::SMINPUTS;

      Eigen::Matrix3cd m_nu = *Dep::m_nu;
      vector<double> ml = {sminputs.mE, sminputs.mMu, sminputs.mTau};
      vector<double> mnu = {real(m_nu(0,0)), real(m_nu(1,1)), real(m_nu(2,2)), *Param["M_1"], *Param["M_2"], *Param["M_3"]};

      Eigen::Matrix3cd Theta = *Dep::SeesawI_Theta;
      Eigen::Matrix3cd Vnu = *Dep::SeesawI_Vnu;
      Eigen::Matrix<complex<double>,3,6> U;

      for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
        {
          U(i,j) = Vnu(i,j);
          U(i,j+3) = Theta(i,j);
        }

      result = pow(sminputs.mMu,5)/(4 * sminputs.alphainv);

      // Form factors
      int e = 0, mu = 1;
      complex<double> k2l = FormFactors::K2L(mu, e, sminputs, U, ml, mnu);
      complex<double> k2r = FormFactors::K2R(mu, e, sminputs, U, ml, mnu);

      result *= (norm(k2l) + norm(k2r));

      result /= Dep::mu_minus_decay_rates->width_in_GeV;
    }

    /// Contribution to tau -> e gamma from RHNs
    void RHN_tauegamma(double &result)
    {
      using namespace Pipes::RHN_tauegamma;
      SMInputs sminputs = *Dep::SMINPUTS;

      Eigen::Matrix3cd m_nu = *Dep::m_nu;
      vector<double> ml = {sminputs.mE, sminputs.mMu, sminputs.mTau};
      vector<double> mnu = {real(m_nu(0,0)), real(m_nu(1,1)), real(m_nu(2,2)), *Param["M_1"], *Param["M_2"], *Param["M_3"]};

      Eigen::Matrix3cd Theta = *Dep::SeesawI_Theta;
      Eigen::Matrix3cd Vnu = *Dep::SeesawI_Vnu;
      Eigen::Matrix<complex<double>,3,6> U;

      for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
        {
          U(i,j) = Vnu(i,j);
          U(i,j+3) = Theta(i,j);
        }

      result = pow(sminputs.mTau,5)/(4*sminputs.alphainv);

      // Form factors
      int e = 0, tau = 2;
      complex<double> k2l = FormFactors::K2L(tau, e, sminputs, U, ml, mnu);
      complex<double> k2r = FormFactors::K2R(tau, e, sminputs, U, ml, mnu);

      result *= (norm(k2l) + norm(k2r));

      result /= Dep::tau_minus_decay_rates->width_in_GeV;
    }

    /// Contribution to tau -> mu gamma from RHNs
    void RHN_taumugamma(double &result)
    {
      using namespace Pipes::RHN_taumugamma;
      SMInputs sminputs = *Dep::SMINPUTS;

      Eigen::Matrix3cd m_nu = *Dep::m_nu;
      vector<double> ml = {sminputs.mE, sminputs.mMu, sminputs.mTau};
      vector<double> mnu = {real(m_nu(0,0)), real(m_nu(1,1)), real(m_nu(2,2)), *Param["M_1"], *Param["M_2"], *Param["M_3"]};

      Eigen::Matrix3cd Theta = *Dep::SeesawI_Theta;
      Eigen::Matrix3cd Vnu = *Dep::SeesawI_Vnu;
      Eigen::Matrix<complex<double>,3,6> U;

      for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
        {
          U(i,j) = Vnu(i,j);
          U(i,j+3) = Theta(i,j);
        }

      result = pow(sminputs.mTau,5)/(4 * sminputs.alphainv);

      // Form factors
      int mu = 1, tau = 2;
      complex<double> k2l = FormFactors::K2L(tau, mu, sminputs, U, ml, mnu);
      complex<double> k2r = FormFactors::K2R(tau, mu, sminputs, U, ml, mnu);

      result *= (norm(k2l) + norm(k2r));

      result /= Dep::tau_minus_decay_rates->width_in_GeV;
    }

    /// General contribution to l_\alpha^- -> l_\beta^- l_\gamma^- l_\delta^+ from RHNs
    double RHN_l2lll(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix3cd Vnu, Eigen::Matrix3cd Theta, Eigen::Matrix3cd m_nu, double M1, double M2, double M3, double mH)
    {
      vector<double> ml = {sminputs.mE, sminputs.mMu, sminputs.mTau};
      vector<double> mnu = {real(m_nu(0,0)), real(m_nu(1,1)), real(m_nu(2,2)), M1, M2, M3};

      Eigen::Matrix<complex<double>,3,6> U;

      for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
        {
          U(i,j) = Vnu(i,j);
          U(i,j+3) = Theta(i,j);
        }

      // Form factors
      complex<double> k2l = FormFactors::K2L(alpha, beta, sminputs, U, ml, mnu);
      complex<double> k2r = FormFactors::K2R(alpha, beta, sminputs, U, ml, mnu);
      complex<double> k1r = FormFactors::K1R(alpha, beta, sminputs, U, mnu);
      complex<double> asll = FormFactors::ASLL(alpha, beta, gamma, delta, sminputs, U, ml, mnu, mH);
      complex<double> aslr = FormFactors::ASLR(alpha, beta, gamma, delta, sminputs, U, ml, mnu, mH);
      complex<double> asrl = FormFactors::ASRL(alpha, beta, gamma, delta, sminputs, U, ml, mnu, mH);
      complex<double> asrr = FormFactors::ASRR(alpha, beta, gamma, delta, sminputs, U, ml, mnu, mH);
      complex<double> avll = FormFactors::AVLL(alpha, beta, gamma, delta, sminputs, U, ml, mnu);
      complex<double> avlr = FormFactors::AVLR(alpha, beta, gamma, delta, sminputs, U, ml, mnu);
      complex<double> avrl = FormFactors::AVLL(alpha, beta, gamma, delta, sminputs, U, ml, mnu);
      complex<double> avrr = FormFactors::AVRR(alpha, beta, gamma, delta, sminputs, U, ml, mnu);

      complex<double> avhatll = avll;
      complex<double> avhatlr = avlr;
      complex<double> avhatrl = avrl + 4. * pi / sminputs.alphainv * k1r;
      complex<double> avhatrr = avrr + 4. * pi / sminputs.alphainv * k1r;

      double l2lll = 0;
      if(beta == gamma and gamma == delta) // l(alpha)- -> l(beta)- l(beta)- l(beta)+
      {
        l2lll = real(16. * pow(pi,2) / pow(sminputs.alphainv,2) * (norm(k2l) + norm(k2r)) * (16./3.*log(ml[alpha]/ml[beta]) - 22./3.) + 1./24. * (norm(asll) + norm(asrr) + 2.*norm(aslr) + 2.*norm(asrl)) + 1./3. * (2.*norm(avhatll) + 2.*norm(avhatrr) + norm(avhatlr) + norm(avhatrl)) + 4.*pi/(3.*sminputs.alphainv)*(k2l*conj(asrl - 2.*avhatrl - 4.*avhatrr) + conj(k2l)*(asrl - 2.*avhatrl - 4.*avhatrr) + k2r*conj(aslr - 2.*avhatlr - 4.*avhatll) + conj(k2r)*(aslr - 2.*avhatlr - 4.*avhatll)) - 1./6. * (aslr*conj(avhatlr) + asrl*conj(avhatrl) + conj(aslr)*avhatlr + conj(asrl)*avhatrl));
      }
      else if(gamma == delta) // l(alpha)- -> l(beta)- l(gamma)- l(gamma)+
      {
        l2lll = real(16. *pow(pi,2) / pow(sminputs.alphainv,2) * (norm(k2l) + norm(k2r)) * (16./3.*log(ml[alpha]/ml[gamma]) - 8.) + 1./12. *(norm(asll) + norm(asrr) + norm(aslr) + norm(asrl)) + 1./3. * (norm(avhatll) + norm(avhatrr) + norm(avhatlr) + norm(avhatrl)) + 8.*pi/(3.*sminputs.alphainv) * (k2l*conj(avhatrl + avhatrr) + k2r*conj(avhatlr + avhatll) + conj(k2l)*(avhatrl + avhatrr) + conj(k2r)*(avhatlr + avhatll)));
      }
      else if(beta == gamma) // l(alpha)- -> l(beta)- l(beta)- l(delta)+
      {
        l2lll = real(1./24. * (norm(asll) + norm(asrr) + 2.*norm(aslr) + 2.*norm(asrl)) + 1./3.*(2.*norm(avhatll) + 2.*norm(avhatrr) + norm(avhatlr) + norm(avhatrl)) - 1./6.*(aslr*conj(avhatlr) + asrl*conj(avhatrl) + conj(aslr)*avhatlr + conj(asrl)*avhatrl));
      }
      return l2lll;
    }

    /// Contribution to mu -> e e e from RHNs
    void RHN_mueee(double &result)
    {
      using namespace Pipes::RHN_mueee;
      SMInputs sminputs = *Dep::SMINPUTS;

      Eigen::Matrix3cd m_nu = *Dep::m_nu;
      Eigen::Matrix3cd Theta = *Dep::SeesawI_Theta;
      Eigen::Matrix3cd Vnu = *Dep::SeesawI_Vnu;

      result = pow(sminputs.mMu,5)/(512*pow(pi,3));

      int e = 0, mu = 1;
      result *=  RHN_l2lll(mu, e, e, e, sminputs, Vnu, Theta, m_nu, *Param["M_1"], *Param["M_2"], *Param["M_3"], *Param["mH"]);

      result /= Dep::mu_minus_decay_rates->width_in_GeV;
    }

    /// Contribution to tau -> e e e from RHNs
    void RHN_taueee(double &result)
    {
      using namespace Pipes::RHN_taueee;
      SMInputs sminputs = *Dep::SMINPUTS;

      Eigen::Matrix3cd m_nu = *Dep::m_nu;
      Eigen::Matrix3cd Theta = *Dep::SeesawI_Theta;
      Eigen::Matrix3cd Vnu = *Dep::SeesawI_Vnu;

      result = pow(sminputs.mTau,5)/(512*pow(pi,3));

      int e = 0, tau = 2;
      result *=  RHN_l2lll(tau, e, e, e, sminputs, Vnu, Theta, m_nu, *Param["M_1"], *Param["M_2"], *Param["M_3"], *Param["mH"]);

      result /= Dep::tau_minus_decay_rates->width_in_GeV;
    }

    /// Contribution to tau -> mu mu mu from RHNs
    void RHN_taumumumu(double &result)
    {
      using namespace Pipes::RHN_taumumumu;
      SMInputs sminputs = *Dep::SMINPUTS;

      Eigen::Matrix3cd m_nu = *Dep::m_nu;
      Eigen::Matrix3cd Theta = *Dep::SeesawI_Theta;
      Eigen::Matrix3cd Vnu = *Dep::SeesawI_Vnu;

      result = pow(sminputs.mTau,5)/(512*pow(pi,3));

      int mu = 1, tau = 2;
      result *=  RHN_l2lll(tau, mu, mu, mu, sminputs, Vnu, Theta, m_nu, *Param["M_1"], *Param["M_2"], *Param["M_3"], *Param["mH"]);

      result /= Dep::tau_minus_decay_rates->width_in_GeV;
    }

    /// Contribution to tau^- -> mu^- e^- e^+ from RHNs
    void RHN_taumuee(double &result)
    {
      using namespace Pipes::RHN_taumuee;
      SMInputs sminputs = *Dep::SMINPUTS;

      Eigen::Matrix3cd m_nu = *Dep::m_nu;
      Eigen::Matrix3cd Theta = *Dep::SeesawI_Theta;
      Eigen::Matrix3cd Vnu = *Dep::SeesawI_Vnu;

      result = pow(sminputs.mTau,5)/(512*pow(pi,3));

      int e = 0, mu = 1, tau = 2;
      result *=  RHN_l2lll(tau, mu, e, e, sminputs, Vnu, Theta, m_nu, *Param["M_1"], *Param["M_2"], *Param["M_3"], *Param["mH"]);

      result /= Dep::tau_minus_decay_rates->width_in_GeV;
    }

    /// Contribution to tau^- -> e^- e^- mu^+ from RHNs
    void RHN_taueemu(double &result)
    {
      using namespace Pipes::RHN_taueemu;
      SMInputs sminputs = *Dep::SMINPUTS;

      Eigen::Matrix3cd m_nu = *Dep::m_nu;
      Eigen::Matrix3cd Theta = *Dep::SeesawI_Theta;
      Eigen::Matrix3cd Vnu = *Dep::SeesawI_Vnu;

      result = pow(sminputs.mTau,5)/(512*pow(pi,3));

      int e = 0, mu = 1, tau = 2;
      result *=  RHN_l2lll(tau, e, e, mu, sminputs, Vnu, Theta, m_nu, *Param["M_1"], *Param["M_2"], *Param["M_3"], *Param["mH"]);

      result /= Dep::tau_minus_decay_rates->width_in_GeV;
    }

    /// Contribution to tau^- -> e^- mu^- mu^+ from RHNs
    void RHN_tauemumu(double &result)
    {
      using namespace Pipes::RHN_tauemumu;
      SMInputs sminputs = *Dep::SMINPUTS;

      Eigen::Matrix3cd m_nu = *Dep::m_nu;
      Eigen::Matrix3cd Theta = *Dep::SeesawI_Theta;
      Eigen::Matrix3cd Vnu = *Dep::SeesawI_Vnu;

      result = pow(sminputs.mTau,5)/(512*pow(pi,3));

      int e = 0, mu = 1, tau = 2;
      result *=  RHN_l2lll(tau, e, mu, mu, sminputs, Vnu, Theta, m_nu, *Param["M_1"], *Param["M_2"], *Param["M_3"], *Param["mH"]);

      result /= Dep::tau_minus_decay_rates->width_in_GeV;
    }

    /// Contribution to tau^- -> mu^- mu^- e^+ from RHNs
    void RHN_taumumue(double &result)
    {
      using namespace Pipes::RHN_taumumue;
      SMInputs sminputs = *Dep::SMINPUTS;

      Eigen::Matrix3cd m_nu = *Dep::m_nu;
      Eigen::Matrix3cd Theta = *Dep::SeesawI_Theta;
      Eigen::Matrix3cd Vnu = *Dep::SeesawI_Vnu;

      result = pow(sminputs.mTau,5)/(512*pow(pi,3));

      int e = 0, mu = 1, tau = 2;
      result *=  RHN_l2lll(tau, mu, mu, e, sminputs, Vnu, Theta, m_nu, *Param["M_1"], *Param["M_2"], *Param["M_3"], *Param["mH"]);

      result /= Dep::tau_minus_decay_rates->width_in_GeV;
    }

    /// Form factors for to mu - e conversion
    void RHN_mue_FF(const SMInputs sminputs, std::vector<double> &mnu, Eigen::Matrix<complex<double>,3,6> &U, const double mH, complex<double> &g0SL, complex<double> &g0SR, complex<double> &g0VL, complex<double> &g0VR, complex<double> &g1SL, complex<double> &g1SR, complex<double> &g1VL, complex<double> &g1VR)
    {
      vector<double> ml = {sminputs.mE, sminputs.mMu, sminputs.mTau};

      int e = 0, mu = 1;
      complex<double> k1r = FormFactors::K1R(mu, e, sminputs, U, mnu);
      complex<double> k2l = FormFactors::K2L(mu, e, sminputs, U, ml, mnu);
      complex<double> k2r = FormFactors::K2R(mu, e, sminputs, U, ml, mnu);

      int u = 0, d =0, s = 1;
      complex<double> CVLLu = FormFactors::CVLL(mu, e, u, u, sminputs, U, ml, mnu);
      complex<double> CVLLd = FormFactors::BVLL(mu, e, d, d, sminputs, U, ml, mnu);
      complex<double> CVLLs = FormFactors::BVLL(mu, e, s, s, sminputs, U, ml, mnu);
      complex<double> CVLRu = FormFactors::CVLR(mu, e, u, u, sminputs, U, ml, mnu);
      complex<double> CVLRd = FormFactors::BVLR(mu, e, d, d, sminputs, U, ml, mnu);
      complex<double> CVLRs = FormFactors::BVLR(mu, e, s, s, sminputs, U, ml, mnu);
      complex<double> CVRLu = FormFactors::CVRL(mu, e, u, u, sminputs, U, ml, mnu);
      complex<double> CVRLd = FormFactors::BVRL(mu, e, d, d, sminputs, U, ml, mnu);
      complex<double> CVRLs = FormFactors::BVRL(mu, e, s, s, sminputs, U, ml, mnu);
      complex<double> CVRRu = FormFactors::CVRR(mu, e, u, u, sminputs, U, ml, mnu);
      complex<double> CVRRd = FormFactors::BVRR(mu, e, d, d, sminputs, U, ml, mnu);
      complex<double> CVRRs = FormFactors::BVRR(mu, e, s, s, sminputs, U, ml, mnu);

      complex<double> CSLLu = FormFactors::CSLL(mu, e, u, u, sminputs, U, ml, mnu, mH);
      complex<double> CSLLd = FormFactors::BSLL(mu, e, d, d, sminputs, U, ml, mnu, mH);
      complex<double> CSLLs = FormFactors::BSLL(mu, e, s, s, sminputs, U, ml, mnu, mH);
      complex<double> CSLRu = FormFactors::CSLL(mu, e, u, u, sminputs, U, ml, mnu, mH);
      complex<double> CSLRd = FormFactors::BSLL(mu, e, d, d, sminputs, U, ml, mnu, mH);
      complex<double> CSLRs = FormFactors::BSLL(mu, e, s, s, sminputs, U, ml, mnu, mH);
      complex<double> CSRLu = FormFactors::CSLL(mu, e, u, u, sminputs, U, ml ,mnu, mH);
      complex<double> CSRLd = FormFactors::BSLL(mu, e, d, d, sminputs, U, ml ,mnu, mH);
      complex<double> CSRLs = FormFactors::BSLL(mu, e, s, s, sminputs, U, ml ,mnu, mH);
      complex<double> CSRRu = FormFactors::CSLL(mu, e, u, u, sminputs, U, ml ,mnu, mH);
      complex<double> CSRRd = FormFactors::BSLL(mu, e, d, d, sminputs, U, ml, mnu, mH);
      complex<double> CSRRs = FormFactors::BSLL(mu, e, s, s, sminputs, U, ml ,mnu, mH);

      double Qu = 2./3.;
      complex<double> gVLu = sqrt(2)/sminputs.GF * (4.*pi / sminputs.alphainv * Qu * (0. - k2r) - 0.5*(CVLLu + CVLRu));
      complex<double> gSLu = -1./(sqrt(2)*sminputs.GF)*(CSLLu + CSLRu);
      complex<double> gVRu = sqrt(2)/sminputs.GF * (4.*pi / sminputs.alphainv * Qu * (k1r - k2l) - 0.5*(CVRRu + CVRLu));
      complex<double> gSRu = -1./(sqrt(2)*sminputs.GF)*(CSRRu + CSRLu);

      double Qd = -1./3.;
      complex<double> gVLd = sqrt(2)/sminputs.GF * (4.*pi / sminputs.alphainv * Qd * (0. - k2r) - 0.5*(CVLLd + CVLRd));
      complex<double> gSLd = -1./(sqrt(2)*sminputs.GF)*(CSLLd + CSLRd);
      complex<double> gVRd = sqrt(2)/sminputs.GF * (4.*pi / sminputs.alphainv * Qd * (k1r - k2l) - 0.5*(CVRRd + CVRLd));
      complex<double> gSRd = -1./(sqrt(2)*sminputs.GF)*(CSRRd + CSRLd);

      double Qs = -1./3.;
      complex<double> gVLs = sqrt(2)/sminputs.GF * (4.*pi / sminputs.alphainv * Qs * (0. - k2r) - 0.5*(CVLLs + CVLRs));
      complex<double> gSLs = -1./(sqrt(2)*sminputs.GF)*(CSLLs + CSLRs);
      complex<double> gVRs = sqrt(2)/sminputs.GF * (4.*pi / sminputs.alphainv * Qs * (k1r - k2l) - 0.5*(CVRRs + CVRLs));
      complex<double> gSRs = -1./(sqrt(2)*sminputs.GF)*(CSRRs + CSRLs);

      double GVup = 2, GVdn = 2, GVdp = 1, GVun = 1, GVsp = 0, GVsn = 0;
      double GSup = 5.1, GSdn = 5.1, GSdp = 4.3, GSun = 4.3, GSsp = 2.5, GSsn = 2.5;

      g0SL = 0.5*(gSLu*(GSup + GSun) + gSLd*(GSdp + GSdn) + gSLs*(GSsp + GSsn));
      g0SR = 0.5*(gSRu*(GSup + GSun) + gSRd*(GSdp + GSdn) + gSRs*(GSsp + GSsn));
      g0VL = 0.5*(gVLu*(GVup + GVun) + gVLd*(GVdp + GVdn) + gVLs*(GVsp + GVsn));
      g0VR = 0.5*(gVRu*(GVup + GVun) + gVRd*(GVdp + GVdn) + gVRs*(GVsp + GVsn));
      g1SL = 0.5*(gSLu*(GSup - GSun) + gSLd*(GSdp - GSdn) + gSLs*(GSsp - GSsn));
      g1SR = 0.5*(gSRu*(GSup - GSun) + gSRd*(GSdp - GSdn) + gSRs*(GSsp - GSsn));
      g1VL = 0.5*(gVLu*(GVup - GVun) + gVLd*(GVdp - GVdn) + gVLs*(GVsp - GVsn));
      g1VR = 0.5*(gVRu*(GVup - GVun) + gVRd*(GVdp - GVdn) + gVRs*(GVsp - GVsn));
    }

    /// Contribution to mu - e conversion in Ti nuclei from RHNs
    void RHN_mueTi(double &result)
    {
      using namespace Pipes::RHN_mueTi;
      const SMInputs sminputs = *Dep::SMINPUTS;
      Eigen::Matrix3cd m_nu = *Dep::m_nu;
      Eigen::Matrix3cd Vnu = *Dep::SeesawI_Vnu;
      Eigen::Matrix3cd Theta = *Dep::SeesawI_Theta;

      vector<double> mnu = {real(m_nu(0,0)), real(m_nu(1,1)), real(m_nu(2,2)), *Param["M_1"], *Param["M_2"], *Param["M_3"]};
      Eigen::Matrix<complex<double>,3,6> U;

      for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
        {
          U(i,j) = Vnu(i,j);
          U(i,j+3) = Theta(i,j);
        }

      complex<double> g0SL, g0SR, g0VL, g0VR, g1SL, g1SR, g1VL, g1VR;
      RHN_mue_FF(sminputs, mnu, U, *Param["mH"], g0SL, g0SR, g0VL, g0VR, g1SL, g1SR, g1VL, g1VR);

      // Parameters for Ti, from Table 1 in 1209.2679 for Ti
      double Z = 22, N = 26;
      double Zeff = 17.6, Fp = 0.54;
      double hbar = 6.582119514e-25; // GeV * s
      double GammaCapt = 2.59e6 * hbar;

      result = (pow(sminputs.GF,2)*pow(sminputs.mMu,5)*pow(Zeff,4)*pow(Fp,2)) / (8.*pow(pi,4)*pow(sminputs.alphainv,3)*Z*GammaCapt) * (norm((Z+N)*(g0VL + g0SL) + (Z-N)*(g1VL + g1SL)) + norm((Z+N)*(g0VR + g0SR) + (Z-N)*(g1VR + g1SR)));
    }

    /// Contribution to mu - e conversion in Au nuclei from RHNs
    void RHN_mueAu(double &result)
    {
      using namespace Pipes::RHN_mueAu;
      const SMInputs sminputs = *Dep::SMINPUTS;
      Eigen::Matrix3cd m_nu = *Dep::m_nu;
      Eigen::Matrix3cd Vnu = *Dep::SeesawI_Vnu;
      Eigen::Matrix3cd Theta = *Dep::SeesawI_Theta;

      vector<double> mnu = {real(m_nu(0,0)), real(m_nu(1,1)), real(m_nu(2,2)), *Param["M_1"], *Param["M_2"], *Param["M_3"]};
      Eigen::Matrix<complex<double>,3,6> U;

      for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
        {
          U(i,j) = Vnu(i,j);
          U(i,j+3) = Theta(i,j);
        }

      complex<double> g0SL, g0SR, g0VL, g0VR, g1SL, g1SR, g1VL, g1VR;
      RHN_mue_FF(sminputs, mnu, U, *Param["mH"], g0SL, g0SR, g0VL, g0VR, g1SL, g1SR, g1VL, g1VR);


      // Parameters for Au, from Table 1 in 1209.2679 for Au
      double Z = 79, N = 118;
      double Zeff = 33.5, Fp = 0.16;
      double hbar = 6.582119514e-25; // GeV * s
      double GammaCapt = 13.07e6 * hbar;

      result = (pow(sminputs.GF,2)*pow(sminputs.mMu,5)*pow(Zeff,4)*pow(Fp,2)) / (8.*pow(pi,4)*pow(sminputs.alphainv,3)*Z*GammaCapt) * (norm((Z+N)*(g0VL + g0SL) + (Z-N)*(g1VL + g1SL)) + norm((Z+N)*(g0VR + g0SR) + (Z-N)*(g1VR + g1SR)));
    }

    /// Contribution to mu - e conversion in Pb nuclei from RHNs
    void RHN_muePb(double &result)
    {
      using namespace Pipes::RHN_muePb;
      const SMInputs sminputs = *Dep::SMINPUTS;
      Eigen::Matrix3cd m_nu = *Dep::m_nu;
      Eigen::Matrix3cd Vnu = *Dep::SeesawI_Vnu;
      Eigen::Matrix3cd Theta = *Dep::SeesawI_Theta;

      vector<double> mnu = {real(m_nu(0,0)), real(m_nu(1,1)), real(m_nu(2,2)), *Param["M_1"], *Param["M_2"], *Param["M_3"]};
      Eigen::Matrix<complex<double>,3,6> U;

      for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
        {
          U(i,j) = Vnu(i,j);
          U(i,j+3) = Theta(i,j);
        }

      complex<double> g0SL, g0SR, g0VL, g0VR, g1SL, g1SR, g1VL, g1VR;
      RHN_mue_FF(sminputs, mnu, U, *Param["mH"], g0SL, g0SR, g0VL, g0VR, g1SL, g1SR, g1VL, g1VR);

      // Parameters for Pb, from Table 1 in 1209.2679 for Pb
      double Z = 82, N = 126;
      double Zeff = 34., Fp = 0.15;
      double hbar = 6.582119514e-25; // GeV * s
      double GammaCapt = 13.45e6 * hbar;

      result = (pow(sminputs.GF,2)*pow(sminputs.mMu,5)*pow(Zeff,4)*pow(Fp,2)) / (8.*pow(pi,4)*pow(sminputs.alphainv,3)*Z*GammaCapt) * (norm((Z+N)*(g0VL + g0SL) + (Z-N)*(g1VL + g1SL)) + norm((Z+N)*(g0VR + g0SR) + (Z-N)*(g1VR + g1SR)));
    }



    /// THDM predictions

    /// BR(l -> l' gamma) for the GTHDM from 1511.08880
    double THDM_llpgamma(int l, int lp, SMInputs sminputs, Spectrum spectrum, double BRltolpnunu)
    {
      const double Alpha_em = 1/(sminputs.alphainv);
      const double alpha_h = spectrum.get(Par::dimensionless,"alpha");
      const double tanb = spectrum.get(Par::dimensionless,"tanb");
      const double beta = atan(tanb);
      const double cosb = cos(beta);
      const double vev = spectrum.get(Par::mass1, "vev");
      const double cab = cos(alpha_h-beta);
      const double mE = sminputs.mE;
      const double mMu = sminputs.mMu;
      const double mTau = sminputs.mTau;
      const double mNu1 = sminputs.mNu1;
      const double mNu2 = sminputs.mNu2;
      const double mNu3 = sminputs.mNu3;
      const double mBmB = sminputs.mBmB;
      const double mS = sminputs.mS;
      const double mCmC = sminputs.mCmC;
      const double mT = sminputs.mT;
      const double mh = spectrum.get(Par::Pole_Mass,"h0",1);
      const double mH = spectrum.get(Par::Pole_Mass,"h0",2);
      const double mA = spectrum.get(Par::Pole_Mass,"A0");
      const double mHp = spectrum.get(Par::Pole_Mass,"H+");
      const vector<double> ml = {mE, mMu, mTau};     // charged leptons
      const vector<double> mvl = {mNu1, mNu2, mNu3}; // neutrinos
      const vector<double> mlf = {mTau, mBmB, mT};   // fermions in the second loop
      const vector<double> mphi = {mh, mH, mA, mHp};
      const std::complex<double> Yee(spectrum.get(Par::dimensionless,"Ye2",1,1), spectrum.get(Par::dimensionless, "ImYe2",1,1));
      const std::complex<double> Yemu(spectrum.get(Par::dimensionless,"Ye2",1,2), spectrum.get(Par::dimensionless, "ImYe2",1,2));
      const std::complex<double> Ymue(spectrum.get(Par::dimensionless,"Ye2",2,1), spectrum.get(Par::dimensionless, "ImYe2",2,1));
      const std::complex<double> Yetau(spectrum.get(Par::dimensionless,"Ye2",1,3), spectrum.get(Par::dimensionless, "ImYe2",1,3));
      const std::complex<double> Ytaue(spectrum.get(Par::dimensionless,"Ye2",3,1), spectrum.get(Par::dimensionless, "ImYe2",3,1));
      const complex<double> Ymumu(spectrum.get(Par::dimensionless,"Ye2",2,2), spectrum.get(Par::dimensionless, "ImYe2",2,2));
      const std::complex<double> Ymutau(spectrum.get(Par::dimensionless,"Ye2",2,3), spectrum.get(Par::dimensionless, "ImYe2",2,3));
      const complex<double> Ytaumu(spectrum.get(Par::dimensionless,"Ye2",3,2), spectrum.get(Par::dimensionless, "ImYe2",3,2));
      const complex<double> Ytautau(spectrum.get(Par::dimensionless,"Ye2",3,3), spectrum.get(Par::dimensionless, "ImYe2",3,3));
      const complex<double> Ytt(spectrum.get(Par::dimensionless,"Yu2",3,3), spectrum.get(Par::dimensionless, "ImYu2",3,3));
      const complex<double> Ytc(spectrum.get(Par::dimensionless,"Yu2",3,2), spectrum.get(Par::dimensionless, "ImYu2",3,2));
      const complex<double> Yct(spectrum.get(Par::dimensionless,"Yu2",2,3), spectrum.get(Par::dimensionless, "ImYu2",2,3));
      const complex<double> Ycc(spectrum.get(Par::dimensionless,"Yu2",2,2), spectrum.get(Par::dimensionless, "ImYu2",2,2));
      const complex<double> Ybb(spectrum.get(Par::dimensionless,"Yd2",3,3), spectrum.get(Par::dimensionless, "ImYd2",3,3));
      const complex<double> Ybs(spectrum.get(Par::dimensionless,"Yd2",3,2), spectrum.get(Par::dimensionless, "ImYd2",3,2));
      const complex<double> Ysb(spectrum.get(Par::dimensionless,"Yd2",2,3), spectrum.get(Par::dimensionless, "ImYd2",2,3));
      const complex<double> Yss(spectrum.get(Par::dimensionless,"Yd2",2,2), spectrum.get(Par::dimensionless, "ImYd2",2,2));
      const double A      = sminputs.CKM.A;
      const double lambda = sminputs.CKM.lambda;
      const double rhobar = sminputs.CKM.rhobar;
      const double etabar = sminputs.CKM.etabar;
      const complex<double> Vud(1 - (1/2)*lambda*lambda);
      const complex<double> Vcd(-lambda,0);
      const complex<double> Vtd((1-rhobar)*A*pow(lambda,3),-etabar*A*pow(lambda,3));
      const complex<double> Vus(lambda,0);
      const complex<double> Vcs(1 - (1/2)*lambda*lambda,0);
      const complex<double> Vts(-A*lambda*lambda,0);
      const complex<double> Vub(rhobar*A*pow(lambda,3),-etabar*A*pow(lambda,3));
      const complex<double> Vcb(A*lambda*lambda,0);
      const complex<double> Vtb(1,0);
      const complex<double> xitt = -((sqrt(2)*mT*tanb)/vev) + Ytt/cosb;
      const complex<double> xicc = -((sqrt(2)*mCmC*tanb)/vev) + Ycc/cosb;
      const complex<double> xitc = Ytc/cosb;
      const complex<double> xict = Yct/cosb;
      const complex<double> xibb = -((sqrt(2)*mBmB*tanb)/vev) + Ybb/cosb;
      const complex<double> xiss = -((sqrt(2)*mS*tanb)/vev) + Yss/cosb;
      const complex<double> xisb = Ysb/cosb;
      const complex<double> xibs = Ybs/cosb;
      const complex<double> xiee = -((sqrt(2)*mE*tanb)/vev) + Yee/cosb;
      const complex<double> xiemu = Yemu/cosb;
      const complex<double> ximue = Ymue/cosb;
      const complex<double> xietau = Yetau/cosb;
      const complex<double> xitaue = Ytaue/cosb;
      const complex<double> ximumu = -((sqrt(2)*mMu*tanb)/vev) + Ymumu/cosb;
      const complex<double> ximutau = Ymutau/cosb;
      const complex<double> xitaumu = Ytaumu/cosb;
      const complex<double> xitautau = -((sqrt(2)*mTau*tanb)/vev) + Ytautau/cosb;

      Eigen::Matrix3cd xi_L, xi_U, xi_D, VCKM;

      xi_L << xiee,  xiemu,  xietau,
              ximue, ximumu, ximutau,
              xitaue, xitaumu, xitautau;

      xi_U << 0,   0,    0,
              0, xicc, xict,
              0, xitc, xitt;

      xi_D << 0,   0,    0,
              0, xiss, xisb,
              0, xibs, xibb;

      const vector<Eigen::Matrix3cd> xi_f = {xi_L, xi_D, xi_U};

      // Needed for Hpm-l-vl couplings
      VCKM << Vud, Vus, Vub,
              Vcd, Vcs, Vcb,
              Vtd, Vts, Vtb;

      int f = 0;

      // One loop amplitude
      complex<double> Aloop1L = 0;
      complex<double> Aloop1R = 0;
      //Charged higgs contributions are being neglected
      //no longer
      for (int phi=0; phi<=3; ++phi)
      {
        for (int li = 0; li <=2; ++li)
        {
          Aloop1L += (1/(16*pow(pi*mphi[phi],2)))*Amplitudes::A_loop1L(f, l, li, lp, phi, mvl, ml, mphi[phi], xi_L, VCKM, vev, cab);
          Aloop1R += (1/(16*pow(pi*mphi[phi],2)))*Amplitudes::A_loop1R(f, l, li, lp, phi, mvl, ml, mphi[phi], xi_L, VCKM, vev, cab);
        }
      }

      /// Two loop amplitude
      const double mW = sminputs.mW;
      const double mZ = sminputs.mZ;
      const double sw2 = 1 - pow(mW/mZ,2);
      const vector<double> Qf = {2./3.,-1./3.,-1.};
      const vector<double> QfZ = {-1./2.*2.-4.*Qf[0]*sw2,1./2.*2.-4.*Qf[1]*sw2,-1./2.*2.-4.*Qf[2]*sw2};
      const vector<double> Nc = {3.,3.,1.};
      //Fermionic contribution
      complex<double> Aloop2fL = 0;
      complex<double> Aloop2fR = 0;
      for (int phi=0; phi<=2; ++phi)
      {
        for (int lf=0; lf<=2; ++lf)
        {
          Aloop2fL += -((Nc[lf]*Qf[lf]*Alpha_em)/(8*pow(pi,3))/(ml[l]*mlf[lf]))*Amplitudes::A_loop2fL(f, lf, l, lp, phi, ml[l], mlf[lf], mphi[phi], mZ, Qf[lf], QfZ[lf], xi_f[lf], xi_L, VCKM, sw2, vev, cab);
          Aloop2fR += -((Nc[lf]*Qf[lf]*Alpha_em)/(8*pow(pi,3))/(ml[l]*mlf[lf]))*Amplitudes::A_loop2fR(f, lf, l, lp, phi, ml[l], mlf[lf], mphi[phi], mZ, Qf[lf], QfZ[lf], xi_f[lf], xi_L, VCKM, sw2, vev, cab);
         }
      }
      //Bosonic contribution
      complex<double> Aloop2bL = 0;
      complex<double> Aloop2bR = 0;
      for (int phi=0; phi<=1; ++phi)
      {
       const complex<double> sab(sqrt(1-cab*cab),0);
       const complex<double> Cab(cab,0);//auxiliary definition to deal with the complex product
       const vector<complex<double>> angle = {sab,Cab};
       Aloop2bL += (Alpha_em/(16*pow(pi,3)*ml[l]*vev))*angle[phi]*Amplitudes::A_loop2bL(f, l, lp, phi, ml[l], mphi[phi], xi_L, VCKM, sw2, vev, cab, mW, mZ);
       Aloop2bR += (Alpha_em/(16*pow(pi,3)*ml[l]*vev))*angle[phi]*Amplitudes::A_loop2bR(f, l, lp, phi, ml[l], mphi[phi], xi_L, VCKM, sw2, vev, cab, mW, mZ);
      }


      double NormAs = norm(Aloop1L+Aloop2fL+Aloop2bL) + norm(Aloop1R+Aloop2fR+Aloop2bR);
      return NormAs*BRltolpnunu*48*pow(pi,3)*Alpha_em/pow(sminputs.GF,2);
    }

    /// BR(mu -> e  gamma) for gTHDM from 1511.08880
    void THDM_muegamma(double &result)
    {
      using namespace Pipes::THDM_muegamma;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;
      const int l = 1, lp = 0;
      const double BRmutoenunu = 100./100.;//BR(mu->e nu nu) from PDG 2020

      result = THDM_llpgamma(l, lp, sminputs, spectrum, BRmutoenunu);
    }

    /// BR(tau -> e gamma) for gTHDM from 1511.08880
    void THDM_tauegamma(double &result)
    {
      using namespace Pipes::THDM_tauegamma;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;
      const int l = 2, lp = 0;
      const double BRtautoenunu = 17.82/100.;//BR(tau->e nu nu) from PDG 2020

      result = THDM_llpgamma(l, lp, sminputs, spectrum, BRtautoenunu);
    }

    /// BR(tau -> mu gamma) for gTHDM from 1511.08880
    void THDM_taumugamma(double &result)
    {
      using namespace Pipes::THDM_taumugamma;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;
      const int l = 2, lp = 1;
      const double BRtautomununu = 17.39/100.;//BR(tau->mu nu nu) from PDG 2020

      result = THDM_llpgamma(l, lp, sminputs, spectrum, BRtautomununu);
    }


    //l2lll from THDMs

    // General contribution to l_\i^- -> l_\j^- l_\k^- l_\l^+ for gTHDM from 1511.08880
    double THDM_l2lll(int i, int j, int k, int l, SMInputs sminputs, Spectrum spectrum)
    {
      double alpha = spectrum.get(Par::dimensionless,"alpha");
      double tanb = spectrum.get(Par::dimensionless,"tanb");
      double beta = atan(tanb);
      double cosb = cos(beta);
      double v = spectrum.get(Par::mass1, "vev");
      double cab = cos(alpha-beta);
      double mE = sminputs.mE;
      double mMu = sminputs.mMu;
      double mTau = sminputs.mTau;
      vector<double> ml = {mE, mMu, mTau};
      double mh = spectrum.get(Par::Pole_Mass,"h0",1);
      double mH = spectrum.get(Par::Pole_Mass,"h0",2);
      double mA = spectrum.get(Par::Pole_Mass,"A0");
      vector<double> mphi= {mh, mH, mA};
      std::complex<double> Yee(spectrum.get(Par::dimensionless,"Ye2",1,1), spectrum.get(Par::dimensionless, "ImYe2",1,1));
      std::complex<double> Yemu(spectrum.get(Par::dimensionless,"Ye2",1,2), spectrum.get(Par::dimensionless, "ImYe2",1,2));
      std::complex<double> Ymue(spectrum.get(Par::dimensionless,"Ye2",2,1), spectrum.get(Par::dimensionless, "ImYe2",2,1));
      std::complex<double> Yetau(spectrum.get(Par::dimensionless,"Ye2",1,3), spectrum.get(Par::dimensionless, "ImYe2",1,3));
      std::complex<double> Ytaue(spectrum.get(Par::dimensionless,"Ye2",3,1), spectrum.get(Par::dimensionless, "ImYe2",3,1));
      std::complex<double> Ymumu(spectrum.get(Par::dimensionless,"Ye2",2,2), spectrum.get(Par::dimensionless, "ImYe2",2,2));
      std::complex<double> Ymutau(spectrum.get(Par::dimensionless,"Ye2",2,3), spectrum.get(Par::dimensionless, "ImYe2",2,3));
      std::complex<double> Ytaumu(spectrum.get(Par::dimensionless,"Ye2",3,2), spectrum.get(Par::dimensionless, "ImYe2",3,2));
      std::complex<double> Ytautau(spectrum.get(Par::dimensionless,"Ye2",3,3), spectrum.get(Par::dimensionless, "ImYe2",3,3));
      double A      = sminputs.CKM.A;
      double lambda = sminputs.CKM.lambda;
      double rhobar = sminputs.CKM.rhobar;
      double etabar = sminputs.CKM.etabar;
      complex<double> Vud(1 - (1/2)*lambda*lambda);
      complex<double> Vcd(-lambda,0);
      complex<double> Vtd((1-rhobar)*A*pow(lambda,3),-etabar*A*pow(lambda,3));
      complex<double> Vus(lambda,0);
      complex<double> Vcs(1 - (1/2)*lambda*lambda,0);
      complex<double> Vts(-A*lambda*lambda,0);
      complex<double> Vub(rhobar*A*pow(lambda,3),-etabar*A*pow(lambda,3));
      complex<double> Vcb(A*lambda*lambda,0);
      complex<double> Vtb(1,0);
      std::complex<double> xiee = -((sqrt(2)*mE*tanb)/v) + Yee/cosb;
      std::complex<double> xiemu = Yemu/cosb;
      std::complex<double> ximue = Ymue/cosb;
      std::complex<double> xietau = Yetau/cosb;
      std::complex<double> xitaue = Ytaue/cosb;
      std::complex<double> ximumu = -((sqrt(2)*mMu*tanb)/v) + Ymumu/cosb;
      std::complex<double> ximutau = Ymutau/cosb;
      std::complex<double> xitaumu = Ytaumu/cosb;
      std::complex<double> xitautau = -((sqrt(2)*mTau*tanb)/v) + Ytautau/cosb;
      Eigen::Matrix3cd xi_L, VCKM;

      xi_L << xiee,  xiemu,  xietau,
              ximue, ximumu, ximutau,
              xitaue, xitaumu, xitautau;

      // Needed for Hpm-l-vl couplings
      VCKM << Vud, Vus, Vub,
              Vcd, Vcs, Vcb,
              Vtd, Vts, Vtb;

      int f=0;
      double l2lll = 0;
      complex<double> two(2,0);

      for (int phi=0; phi<=2; ++phi)
      {
        for (int phip=0; phip<=2; ++phip)
        {
         if(j == k and k == l) // l(i)- -> l(j)- l(j)- l(j)+
         {

                   l2lll += real(0.5*(1/pow(mphi[phi]*mphi[phip],2))*( two*(Yukawas::yff_phi(f, k, i, phi,  ml[k], xi_L, VCKM, v, cab)*conj(Yukawas::yff_phi(f, k, k, phi, ml[k], xi_L, VCKM, v, cab)) * (conj(Yukawas::yff_phi(f, k, i, phip, ml[k], xi_L, VCKM, v, cab))*Yukawas::yff_phi(f, k, k, phip, ml[k], xi_L, VCKM, v, cab)))
                                                           + two*(Yukawas::yff_phi(f, i, k, phi,  ml[i], xi_L, VCKM, v, cab)*conj(Yukawas::yff_phi(f, k, k, phi, ml[k], xi_L, VCKM, v, cab)) * (conj(Yukawas::yff_phi(f, i, k, phip, ml[i], xi_L, VCKM, v, cab))*Yukawas::yff_phi(f, k, k, phip, ml[k], xi_L, VCKM, v, cab)))
                                                           +   (Yukawas::yff_phi(f, k, i, phi,  ml[k], xi_L, VCKM, v, cab)*Yukawas::yff_phi(f, k, k, phi, ml[k], xi_L, VCKM, v, cab) * (conj(Yukawas::yff_phi(f, k, i, phip, ml[k], xi_L, VCKM, v, cab))*conj(Yukawas::yff_phi(f, k, k, phip, ml[k], xi_L, VCKM, v, cab))))
                                                           +   (Yukawas::yff_phi(f, i, k, phi,  ml[i], xi_L, VCKM, v, cab)*Yukawas::yff_phi(f, k, k, phi, ml[k], xi_L, VCKM, v, cab) * (conj(Yukawas::yff_phi(f, i, k, phip, ml[i], xi_L, VCKM, v, cab))*conj(Yukawas::yff_phi(f, k, k, phip, ml[k], xi_L, VCKM, v, cab))))));
         }
         else if(k == l) // l(i)- -> l(j)- l(k)- l(k)+
         {
                   l2lll += real( 1/(pow(mphi[phi]*mphi[phip],2))*( (Yukawas::yff_phi(f, k, i, phi,  ml[k], xi_L, VCKM, v, cab)*conj(Yukawas::yff_phi(f, k, k, phi, ml[k], xi_L, VCKM, v, cab)) * (conj(Yukawas::yff_phi(f, k, i, phip, ml[k], xi_L, VCKM, v, cab))*Yukawas::yff_phi(f, k, k, phip, ml[k], xi_L, VCKM, v, cab)))
                                                           + (Yukawas::yff_phi(f, i, k, phi,  ml[i], xi_L, VCKM, v, cab)*conj(Yukawas::yff_phi(f, k, k, phi, ml[k], xi_L, VCKM, v, cab)) * (conj(Yukawas::yff_phi(f, i, k, phip, ml[i], xi_L, VCKM, v, cab))*Yukawas::yff_phi(f, k, k, phip, ml[k], xi_L, VCKM, v, cab)))
                                                           +   (Yukawas::yff_phi(f, k, i, phi,  ml[k], xi_L, VCKM, v, cab)*Yukawas::yff_phi(f, k, k, phi, ml[k], xi_L, VCKM, v, cab) * (conj(Yukawas::yff_phi(f, k, i, phip, ml[k], xi_L, VCKM, v, cab))*conj(Yukawas::yff_phi(f, k, k, phip, ml[k], xi_L, VCKM, v, cab))))
                                                           +   (Yukawas::yff_phi(f, i, k, phi,  ml[i], xi_L, VCKM, v, cab)*Yukawas::yff_phi(f, k, k, phi, ml[k], xi_L, VCKM, v, cab) * (conj(Yukawas::yff_phi(f, i, k, phip, ml[i], xi_L, VCKM, v, cab))*conj(Yukawas::yff_phi(f, k, k, phip, ml[k], xi_L, VCKM, v, cab))))));
         }

         else if(j == k) // l(i)- -> l(j)- l(j)- l(l)+
         {
                   l2lll +=  real(0.5*(1/pow(mphi[phi]*mphi[phip],2))*( two*(Yukawas::yff_phi(f, k, i, phi,  ml[k], xi_L, VCKM, v, cab)*conj(Yukawas::yff_phi(f, l, l, phi, ml[l], xi_L, VCKM, v, cab)) * (conj(Yukawas::yff_phi(f, k, i, phip, ml[k], xi_L, VCKM, v, cab))*Yukawas::yff_phi(f,  l, l, phi, ml[l], xi_L, VCKM, v, cab)))
                                                           + two*(Yukawas::yff_phi(f, i, k, phi,  ml[i], xi_L, VCKM, v, cab)*conj(Yukawas::yff_phi(f, l, l, phi, ml[l], xi_L, VCKM, v, cab)) * (conj(Yukawas::yff_phi(f, i, k, phip, ml[i], xi_L, VCKM, v, cab))*Yukawas::yff_phi(f, l, l, phi, ml[l], xi_L, VCKM, v, cab)))
                                                           +   (Yukawas::yff_phi(f, k, i, phi,  ml[k], xi_L, VCKM, v, cab)*Yukawas::yff_phi(f, l, l, phi, ml[l], xi_L, VCKM, v, cab) * (conj(Yukawas::yff_phi(f, k, i, phip, ml[k], xi_L, VCKM, v, cab))*conj(Yukawas::yff_phi(f, l, l, phi, ml[l], xi_L, VCKM, v, cab))))
                                                           +   (Yukawas::yff_phi(f, i, k, phi,  ml[i], xi_L, VCKM, v, cab)*Yukawas::yff_phi(f, l, l, phi, ml[l], xi_L, VCKM, v, cab) * (conj(Yukawas::yff_phi(f, i, k, phip, ml[i], xi_L, VCKM, v, cab))*conj(Yukawas::yff_phi(f, l, l, phi, ml[l], xi_L, VCKM, v, cab))))));
          }
         }
       }

      double BRtautomununu = 17.39/100;//BR(tau->mu nu nu) from PDG 2020
      return (BRtautomununu/(32*pow(sminputs.GF,2)))*l2lll;
    }

    /// charged boxes diagrams for tau to 3 mu in the THDM
    double THDM_box_l2lll(int l, int lp, SMInputs sminputs, Spectrum spectrum)
    {
      const double Alpha_em = 1/(sminputs.alphainv);
      const double alpha_h = spectrum.get(Par::dimensionless,"alpha");
      const double tanb = spectrum.get(Par::dimensionless,"tanb");
      const double beta = atan(tanb);
      const double cosb = cos(beta);
      const double vev = spectrum.get(Par::mass1, "vev");
      const double cab = cos(alpha_h-beta);
      const double mE = sminputs.mE;
      const double mMu = sminputs.mMu;
      const double mTau = sminputs.mTau;
      const double mNu1 = sminputs.mNu1;
      const double mNu2 = sminputs.mNu2;
      const double mNu3 = sminputs.mNu3;
      const double mBmB = sminputs.mBmB;
      const double mS = sminputs.mS;
      const double mCmC = sminputs.mCmC;
      const double mT = sminputs.mT;
      const double mh = spectrum.get(Par::Pole_Mass,"h0",1);
      const double mH = spectrum.get(Par::Pole_Mass,"h0",2);
      const double mA = spectrum.get(Par::Pole_Mass,"A0");
      const double mHp = spectrum.get(Par::Pole_Mass,"H+");
      const vector<double> ml = {mE, mMu, mTau};     // charged leptons
      const vector<double> mvl = {mNu1, mNu2, mNu3}; // neutrinos
      const vector<double> mlf = {mTau, mBmB, mT};   // fermions in the second loop
      const vector<double> mphi = {mh, mH, mA, mHp};
      const complex<double> Yee(spectrum.get(Par::dimensionless,"Ye2",1,1), spectrum.get(Par::dimensionless, "ImYe2",1,1));
      const complex<double> Yemu(spectrum.get(Par::dimensionless,"Ye2",1,2), spectrum.get(Par::dimensionless, "ImYe2",1,2));
      const complex<double> Ymue(spectrum.get(Par::dimensionless,"Ye2",2,1), spectrum.get(Par::dimensionless, "ImYe2",2,1));
      const complex<double> Yetau(spectrum.get(Par::dimensionless,"Ye2",1,3), spectrum.get(Par::dimensionless, "ImYe2",1,3));
      const complex<double> Ytaue(spectrum.get(Par::dimensionless,"Ye2",3,1), spectrum.get(Par::dimensionless, "ImYe2",3,1));
      const complex<double> Ymumu(spectrum.get(Par::dimensionless,"Ye2",2,2), spectrum.get(Par::dimensionless, "ImYe2",2,2));
      const complex<double> Ymutau(spectrum.get(Par::dimensionless,"Ye2",2,3), spectrum.get(Par::dimensionless, "ImYe2",2,3));
      const complex<double> Ytaumu(spectrum.get(Par::dimensionless,"Ye2",3,2), spectrum.get(Par::dimensionless, "ImYe2",3,2));
      const complex<double> Ytautau(spectrum.get(Par::dimensionless,"Ye2",3,3), spectrum.get(Par::dimensionless, "ImYe2",3,3));
      const complex<double> Ytt(spectrum.get(Par::dimensionless,"Yu2",3,3), spectrum.get(Par::dimensionless, "ImYu2",3,3));
      const complex<double> Ytc(spectrum.get(Par::dimensionless,"Yu2",3,2), spectrum.get(Par::dimensionless, "ImYu2",3,2));
      const complex<double> Yct(spectrum.get(Par::dimensionless,"Yu2",2,3), spectrum.get(Par::dimensionless, "ImYu2",2,3));
      const complex<double> Ycc(spectrum.get(Par::dimensionless,"Yu2",2,2), spectrum.get(Par::dimensionless, "ImYu2",2,2));
      const complex<double> Ybb(spectrum.get(Par::dimensionless,"Yd2",3,3), spectrum.get(Par::dimensionless, "ImYd2",3,3));
      const complex<double> Ybs(spectrum.get(Par::dimensionless,"Yd2",3,2), spectrum.get(Par::dimensionless, "ImYd2",3,2));
      const complex<double> Ysb(spectrum.get(Par::dimensionless,"Yd2",2,3), spectrum.get(Par::dimensionless, "ImYd2",2,3));
      const complex<double> Yss(spectrum.get(Par::dimensionless,"Yd2",2,2), spectrum.get(Par::dimensionless, "ImYd2",2,2));
      const double A      = sminputs.CKM.A;
      const double lambda = sminputs.CKM.lambda;
      const double rhobar = sminputs.CKM.rhobar;
      const double etabar = sminputs.CKM.etabar;
      const complex<double> Vud(1 - (1/2)*lambda*lambda);
      const complex<double> Vcd(-lambda,0);
      const complex<double> Vtd((1-rhobar)*A*pow(lambda,3),-etabar*A*pow(lambda,3));
      const complex<double> Vus(lambda,0);
      const complex<double> Vcs(1 - (1/2)*lambda*lambda,0);
      const complex<double> Vts(-A*lambda*lambda,0);
      const complex<double> Vub(rhobar*A*pow(lambda,3),-etabar*A*pow(lambda,3));
      const complex<double> Vcb(A*lambda*lambda,0);
      const complex<double> Vtb(1,0);
      const complex<double> xitt = -((sqrt(2)*mT*tanb)/vev) + Ytt/cosb;
      const complex<double> xicc = -((sqrt(2)*mCmC*tanb)/vev) + Ycc/cosb;
      const complex<double> xitc = Ytc/cosb;
      const complex<double> xict = Yct/cosb;
      const complex<double> xibb = -((sqrt(2)*mBmB*tanb)/vev) + Ybb/cosb;
      const complex<double> xiss = -((sqrt(2)*mS*tanb)/vev) + Yss/cosb;
      const complex<double> xisb = Ysb/cosb;
      const complex<double> xibs = Ybs/cosb;
      const complex<double> xiee = -((sqrt(2)*mE*tanb)/vev) + Yee/cosb;
      const complex<double> xiemu = Yemu/cosb;
      const complex<double> ximue = Ymue/cosb;
      const complex<double> xietau = Yetau/cosb;
      const complex<double> xitaue = Ytaue/cosb;
      const complex<double> ximumu = -((sqrt(2)*mMu*tanb)/vev) + Ymumu/cosb;
      const complex<double> ximutau = Ymutau/cosb;
      const complex<double> xitaumu = Ytaumu/cosb;
      const complex<double> xitautau = -((sqrt(2)*mTau*tanb)/vev) + Ytautau/cosb;

      Eigen::Matrix3cd xi_L, xi_U, xi_D, VCKM;

      xi_L << xiee,  xiemu,  xietau,
              ximue, ximumu, ximutau,
              xitaue, xitaumu, xitautau;

      xi_U << 0,   0,    0,
              0, xicc, xict,
              0, xitc, xitt;

      xi_D << 0,   0,    0,
              0, xiss, xisb,
              0, xibs, xibb;

      const vector<Eigen::Matrix3cd> xi_f = {xi_L, xi_D, xi_U};

      // Needed for Hpm-l-vl couplings
      VCKM << Vud, Vus, Vub,
              Vcd, Vcs, Vcb,
              Vtd, Vts, Vtb;

      int f = 0;

      // One loop amplitude
      complex<double> Aloop1R = 0;
      //Charged higgs contributions are being neglected
      //no longer
      for (int phi=0; phi<=3; ++phi)
      {
        for (int li = 0; li <=2; ++li)
        {
          Aloop1R += (1/(16*pow(pi*mphi[phi],2)))*Amplitudes::A_loop1R(f, l, li, lp, phi, mvl, ml, mphi[phi], xi_L, VCKM, vev, cab);
        }
      }

      /// Two loop amplitude
      const double mW = sminputs.mW;
      const double mZ = sminputs.mZ;
      const double sw2 = 1 - pow(mW/mZ,2);
      const vector<double> Qf = {2./3.,-1./3.,-1.};
      const vector<double> QfZ = {-1./2.*2.-4.*Qf[0]*sw2,1./2.*2.-4.*Qf[1]*sw2,-1./2.*2.-4.*Qf[2]*sw2};
      const vector<double> Nc = {3.,3.,1.};
      //Fermionic contribution
      complex<double> Aloop2fR = 0;
      for (int phi=0; phi<=2; ++phi)
      {
        for (int lf=0; lf<=2; ++lf)
        {
          Aloop2fR += -((Nc[lf]*Qf[lf]*Alpha_em)/(8*pow(pi,3))/(ml[l]*mlf[lf]))*Amplitudes::A_loop2fR(f, lf, l, lp, phi, ml[l], mlf[lf], mphi[phi], mZ, Qf[lf], QfZ[lf], xi_f[lf], xi_L, VCKM, sw2, vev, cab);
         }
      }
      //Bosonic contribution
      complex<double> Aloop2bR = 0;
      for (int phi=0; phi<=1; ++phi)
      {
       const complex<double> sab(sqrt(1-cab*cab),0);
       const complex<double> Cab(cab,0);//auxiliary definition to deal with the complex product
       const vector<complex<double>> angle = {sab,Cab};
       Aloop2bR += (Alpha_em/(16*pow(pi,3)*ml[l]*vev))*angle[phi]*Amplitudes::A_loop2bR(f, l, lp, phi, ml[l], mphi[phi], xi_L, VCKM, sw2, vev, cab, mW, mZ);
      }
      //g2 coupling
      complex<double> g2 = mMu*mMu*xitaumu*(ximumu*ximumu+xitaumu*xitaumu)*(ximumu+xitautau)/(192*sqrt(2)*pi*pi*sminputs.GF*pow(mHp,4));
      //g4 coupling
      complex<double> g4 = -xitaumu*(ximumu*ximumu+xitaumu*xitaumu)*(ximumu+xitautau)/(128*sqrt(2)*pi*pi*sminputs.GF*pow(mHp,2));

      double C2 = norm(g2)/16 + norm(g4);
      double C7 = (pi*Alpha_em/(sqrt(2)*sminputs.GF))*real(conj(g4)*(Aloop1R+Aloop2fR+Aloop2bR));

      return 2*C2+16*C7;
    }



    // Contribution to mu -> e e e from THDM
    void THDM_mueee(double &result)
    {
      using namespace Pipes::THDM_mueee;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      const double Alpha_em = 1/(sminputs.alphainv);
      const double mE = sminputs.mE;
      const double mMu = sminputs.mMu;

      const int l = 1, lp = 0;
      const double BRmutoenunu = 100./100.;//BR(mu->e nu nu) from PDG 2020
      const double dipoleconst = (Alpha_em/(3*pi))*(log(pow(mMu/mE,2))-11./4);

      result = THDM_l2lll(l, lp, lp, lp, sminputs, spectrum) + (dipoleconst/BRmutoenunu)*THDM_llpgamma(l, lp, sminputs, spectrum, BRmutoenunu);
    }

    /// Contribution to tau -> e e e from THDM
    void THDM_taueee(double &result)
    {
      using namespace Pipes::THDM_taueee;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      const double Alpha_em = 1/(sminputs.alphainv);
      const double mE = sminputs.mE;
      const double mTau = sminputs.mTau;

      const int l = 2, lp = 0;
      const double BRtautoenunu = 17.82/100.;//BR(tau->e nu nu) from PDG 2020
      const double dipoleconst = (Alpha_em/(3*pi))*(log(pow(mTau/mE,2))-11./4);

      result = THDM_l2lll(l, lp, lp, lp, sminputs, spectrum) + (dipoleconst/BRtautoenunu)*THDM_llpgamma(l, lp, sminputs, spectrum, BRtautoenunu);
    }

    /// Contribution to tau -> mu mu mu from THDM
    void THDM_taumumumu(double &result)
    {
      using namespace Pipes::THDM_taumumumu;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      const double Alpha_em = 1/(sminputs.alphainv);
      const double mMu = sminputs.mMu;
      const double mTau = sminputs.mTau;

      const int l = 2, lp = 1;
      const double BRtautomununu = 17.39/100.;//BR(tau->mu nu nu) from PDG 2020
      const double dipoleconst = (Alpha_em/(3*pi))*(log(pow(mTau/mMu,2))-11./4);

      result = THDM_l2lll(l, lp, lp, lp, sminputs, spectrum) + (dipoleconst/BRtautomununu)*THDM_llpgamma(l, lp, sminputs, spectrum, BRtautomununu) + THDM_box_l2lll(l, lp, sminputs, spectrum);
    }

    /// Contribution to tau^- -> mu^- e^- e^+ from THDM
    void THDM_taumuee(double &result)
    {
      using namespace Pipes::THDM_taumuee;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      int e = 0, mu = 1, tau = 2;
      result =  THDM_l2lll(tau, mu, e, e, sminputs, spectrum);
    }

    /// Contribution to tau^- -> e^- e^- mu^+ from THDM
    void THDM_taueemu(double &result)
    {
      using namespace Pipes::THDM_taueemu;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      int e = 0, mu = 1, tau = 2;
      result =  THDM_l2lll(tau, e, e, mu, sminputs, spectrum);
    }

    /// Contribution to tau^- -> e^- mu^- mu^+ from THDM
    void THDM_tauemumu(double &result)
    {
      using namespace Pipes::THDM_tauemumu;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      int e = 0, mu = 1, tau = 2;
      result =  THDM_l2lll(tau, e, mu, mu, sminputs, spectrum);
    }

    /// Contribution to tau^- -> mu^- mu^- e^+ from THDM
    void THDM_taumumue(double &result)
    {
      using namespace Pipes::THDM_taumumue;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      int e = 0, mu = 1, tau = 2;
      result =  THDM_l2lll(tau, mu, mu, e, sminputs, spectrum);
    }

    /// mu-e universality for the general THDM from JHEP07(2013)044
    /// Green functions
    double Fint(double x)
    {
      if (x < 0)
        FlavBit_error().raise(LOCAL_INFO, "Negative mass in loop function");
      if (x==0)
        return 1;
      return 1 + 9*x - 9*pow(x,2) - pow(x,3) + 6*x*(1 + x)*log(x);
    }

    double Fps(double x)
    {
      if (x < 0)
        FlavBit_error().raise(LOCAL_INFO, "Negative mass in loop function");
      if (x==0)
        return 1;
      return 1 - 8*x + 8*pow(x,3) - pow(x,4) - 12*pow(x,2)*log(x);
    }

    ///Lepton universality test observable from JHEP07(2013)044
    void THDM_gmu_ge(double &result)
    {
      using namespace Pipes::THDM_gmu_ge;
      Spectrum spectrum = *Dep::THDM_spectrum;
      const double v = spectrum.get(Par::mass1, "vev");
      double tanb = spectrum.get(Par::dimensionless,"tanb");
      double beta = atan(tanb);
      double cosb = cos(beta);
      const double mMu = Dep::SMINPUTS->mMu;
      const double mTau = Dep::SMINPUTS->mTau;
      double mHp = spectrum.get(Par::Pole_Mass,"H+");
      double D = (2*mMu*Fint(pow(mMu,2)/pow(mTau,2)))/(mTau*Fps(pow(mMu,2)/pow(mTau,2)));
      std::complex<double> Ymumu(spectrum.get(Par::dimensionless,"Ye2",2,2), spectrum.get(Par::dimensionless, "ImYe2",2,2));
      std::complex<double> Ymutau(spectrum.get(Par::dimensionless,"Ye2",2,3), spectrum.get(Par::dimensionless, "ImYe2",2,3));
      std::complex<double> Ytaumu(spectrum.get(Par::dimensionless,"Ye2",3,2), spectrum.get(Par::dimensionless, "ImYe2",3,2));
      std::complex<double> Ytautau(spectrum.get(Par::dimensionless,"Ye2",3,3), spectrum.get(Par::dimensionless, "ImYe2",3,3));
      std::complex<double> xi_mumu = -((sqrt(2)*mMu*tanb)/v) + Ymumu/cosb;
      std::complex<double> xi_mutau = Ymutau/cosb;
      std::complex<double> xi_taumu = Ytaumu/cosb;
      std::complex<double> xi_tautau = -((sqrt(2)*mTau*tanb)/v) + Ytautau/cosb;
      std::complex<double> R = ((v*v)/(2*mHp*mHp))*(xi_mumu*xi_tautau);
      std::complex<double> Roff = 2*((v*v)/(2*mHp*mHp))*(xi_mutau*xi_taumu);//The 2 factor accounts for tau mu and mu tau neutrinos
      std::complex<double> one = {1,0};
      result =real(sqrt(one + 0.25*(R*R+Roff*Roff) - D*(R)));
    }



    /// Likelihood functions
    /// {@

    /// Likelihood for l -> l gamma processes
    void l2lgamma_likelihood(double &result)
    {
      using namespace Pipes::l2lgamma_likelihood;

      static bool first = true;
      static boost::numeric::ublas::matrix<double> cov_exp, value_exp;
      static double th_err[3];
      double theory[3];

      // Read and calculate things based on the observed data only the first time through, as none of it depends on the model parameters.
      if (first)
      {
        // Read in experimental measuremens
        Flav_reader fread(GAMBIT_DIR  "/FlavBit/data");
        fread.debug_mode(flav_debug);

        // mu -> e gamma
        fread.read_yaml_measurement("flav_data.yaml", "BR_muegamma");
        // tau -> e gamma
        fread.read_yaml_measurement("flav_data.yaml", "BR_tauegamma");
        // tau -> mu gamma
        fread.read_yaml_measurement("flav_data.yaml", "BR_taumugamma");

        fread.initialise_matrices();
        cov_exp=fread.get_exp_cov();
        value_exp=fread.get_exp_value();

        for (int i = 0; i < 3; ++i)
          th_err[i] = fread.get_th_err()(i,0).first;

        // Init over.
        first = false;
      }

     theory[0] = *Dep::muegamma;
     if(flav_debug) cout << "mu- -> e- gamma = " << theory[0] << endl;
     theory[1] = *Dep::tauegamma;
     if(flav_debug) cout << "tau- -> e- gamma = " << theory[1] << endl;
     theory[2] = *Dep::taumugamma;
     if(flav_debug) cout << "tau- -> mu- gamma = " << theory[2] << endl;

     result = 0;
     for (int i = 0; i < 3; ++i)
       result += Stats::gaussian_upper_limit(theory[i], value_exp(i,0), th_err[i], sqrt(cov_exp(i,i)), false);
    }

    /// Likelihood for l -> l l l processes
    void l2lll_likelihood(double &result)
    {
      using namespace Pipes::l2lll_likelihood;

      static bool first = true;
      static boost::numeric::ublas::matrix<double> cov_exp, value_exp;
      static double th_err[7];
      double theory[7];


      // Read and calculate things based on the observed data only the first time through, as none of it depends on the model parameters.
      if (first)
      {
        // Read in experimental measuremens
        Flav_reader fread(GAMBIT_DIR  "/FlavBit/data");
        fread.debug_mode(flav_debug);

        // mu- -> e- e- e+
        fread.read_yaml_measurement("flav_data.yaml", "BR_mueee");
        // tau- -> e- e- e+
        fread.read_yaml_measurement("flav_data.yaml", "BR_taueee");
        // tau- -> mu- mu- mu+
        fread.read_yaml_measurement("flav_data.yaml", "BR_taumumumu");
        // tau- -> mu- e- e+
        fread.read_yaml_measurement("flav_data.yaml", "BR_taumuee");
        // tau- -> e- e- mu+
        fread.read_yaml_measurement("flav_data.yaml", "BR_taueemu");
        // tau- -> e- mu- mu+
        fread.read_yaml_measurement("flav_data.yaml", "BR_tauemumu");
        // tau- -> mu- mu- e+
        fread.read_yaml_measurement("flav_data.yaml", "BR_taumumue");

        fread.initialise_matrices();
        cov_exp=fread.get_exp_cov();
        value_exp=fread.get_exp_value();

        for (int i = 0; i < 7; ++i)
          th_err[i] = fread.get_th_err()(i,0).first;

        // Init over.
        first = false;
      }

     theory[0] = *Dep::mueee;
     if(flav_debug) cout << "mu-  -> e-  e-  e+  = " << theory[0] << endl;
     theory[1] = *Dep::taueee;
     if(flav_debug) cout << "tau- -> e-  e-  e+  = " << theory[1] << endl;
     theory[2] = *Dep::taumumumu;
     if(flav_debug) cout << "tau- -> mu- mu- mu+ = " << theory[2] << endl;
     theory[3] = *Dep::taumuee;
     if(flav_debug) cout << "tau- -> mu- e-  e-  = " << theory[3] << endl;
     theory[4] = *Dep::taueemu;
     if(flav_debug) cout << "tau- -> e-  e-  mu+ = " << theory[4] << endl;
     theory[5] = *Dep::tauemumu;
     if(flav_debug) cout << "tau- -> e-  mu- mu+ = " << theory[5] << endl;
     theory[6] = *Dep::taumumue;
     if(flav_debug) cout << "tau- -> mu- mu- e+  = " << theory[6] << endl;

     result = 0;
     for (int i = 0; i < 7; ++i)
       result += Stats::gaussian_upper_limit(theory[i], value_exp(i,0), th_err[i], sqrt(cov_exp(i,i)), false);
    }

    /// Likelihood for mu - e conversion in nuclei
    void mu2e_likelihood(double &result)
    {
      using namespace Pipes::mu2e_likelihood;

      static bool first = true;
      static boost::numeric::ublas::matrix<double> cov_exp, value_exp;
      static int n_measurements = 3;
      static double th_err[3];
      double theory[3];


      // Read and calculate things based on the observed data only the first time through, as none of it depends on the model parameters.
      if (first)
      {
        // Read in experimental measuremens
        Flav_reader fread(GAMBIT_DIR  "/FlavBit/data");
        fread.debug_mode(flav_debug);

        // mu - e (Ti)
        fread.read_yaml_measurement("flav_data.yaml", "R_mueTi");
        // mu - e (Au)
        fread.read_yaml_measurement("flav_data.yaml", "R_mueAu");
        // mu - e (Pb)
        fread.read_yaml_measurement("flav_data.yaml", "R_muePb");

        fread.initialise_matrices();
        cov_exp=fread.get_exp_cov();
        value_exp=fread.get_exp_value();

        for (int i = 0; i < n_measurements; ++i)
          th_err[i] = fread.get_th_err()(i,0).first;

        // Init over.
        first = false;
      }

      theory[0] = *Dep::mueTi;
      if(flav_debug) cout << "mu - e (Ti) = " << theory[0] << endl;
      theory[1] = *Dep::mueAu;
      if(flav_debug) cout << "mu - e (Au) = " << theory[1] << endl;
      theory[2] = *Dep::muePb;
      if(flav_debug) cout << "mu - e (Pb) = " << theory[2] << endl;

      result = 0;
      for (int i = 0; i < n_measurements; ++i)
        result += Stats::gaussian_upper_limit(theory[i], value_exp(i,0), th_err[i], sqrt(cov_exp(i,i)), false);
    }


    /// Likelihood for  mu-e universality
    void gmu_ge_likelihood(double &result)
    {
      using namespace Pipes::gmu_ge_likelihood;
      static bool th_err_absolute, first = true;
      static double exp_meas, exp_gmu_ge_err, th_err;

      if (flav_debug) cout << "gmu_ge_likelihood"<<endl;

      if (first)
      {
        Flav_reader fread(GAMBIT_DIR  "/FlavBit/data");
        fread.debug_mode(flav_debug);
        if (flav_debug) cout<<"Initialised Flav reader in gmu_ge_ikelihood"<<endl;
        fread.read_yaml_measurement("flav_data.yaml", "gmu_ge");
        fread.initialise_matrices();
        exp_meas = fread.get_exp_value()(0,0);
        exp_gmu_ge_err = sqrt(fread.get_exp_cov()(0,0));
        th_err = fread.get_th_err()(0,0).first;
        th_err_absolute = fread.get_th_err()(0,0).second;
        first = false;
      }

      if (flav_debug) cout << "Experiment: " << exp_meas << " " << exp_gmu_ge_err << " " << th_err << endl;

      double theory_prediction = *Dep::gmu_ge;
      double theory_gmu_ge_err = th_err * (th_err_absolute ? 1.0 : std::abs(theory_prediction));
      if (flav_debug) cout<<"Theory prediction: "<<theory_prediction<<" +/- "<<exp_gmu_ge_err<<endl;

      bool profile = runOptions->getValueOrDef<bool>(false, "profile_systematics");

      result = Stats::gaussian_loglikelihood(theory_prediction, exp_meas, theory_gmu_ge_err, exp_gmu_ge_err, profile);
    }

    /// @}

  }
}
