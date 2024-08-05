//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Functions of module FlavBit
///  - Flavour changing charged currents
///    - RD, RD*
///    - FLD*
///    - B -> D tau nu, B -> D* tau nu
///    - B -> D mu nu, B -> D* mu nu
///    - B -> tau nu
///    - D -> tau nu, Ds -> tau nu
///    - D -> mu nu, Ds -> mu nu
///    - RD_emu, Rmu
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
#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/FlavBit/FlavBit_rollcall.hpp"
#include "gambit/FlavBit/FlavBit_macros.hpp"
#include "gambit/FlavBit/Flav_reader.hpp"
#include "gambit/FlavBit/FlavBit_utils.hpp"

namespace Gambit
{

  namespace FlavBit
  {

    ///------------------------///
    ///      Observables       ///
    ///------------------------///


    ///  B-> D tau nu distributions in the THDM
    // TODO: If this only works with taus change name
    double THDM_dGammaBDlnu(std::complex<double> gs, std::complex<double> gsmutau, double q2)
    {
      // TODO: Change to use sminputs and constants
      const double mB = 5.27961;
      const double mD = 1.870;
      const double ml = 1.77686;
      const double mb = 4.18;
      const double mc = 1.28;
      const double GF = 1.16638e-5;
      const double Vcb = 0.041344392;

      const double rho_D2 = 1.186;
      const double V1_1 = 1.074;
      const double Delta = 1;

      double C_V1=0.;
      double C_V2=0.;
      double C_T=0.;

      double lambda_D=((mB-mD)*(mB-mD)-q2)*((mB+mD)*(mB+mD)-q2);

      double r_D=mD/mB;
      double w=(mB*mB+mD*mD-q2)/2./mB/mD;
      double z=(sqrt(w+1.)-sqrt(2.))/(sqrt(w+1.)+sqrt(2.));

      double V1=V1_1*(1.-8.*rho_D2*z+(51.*rho_D2-10.)*z*z-(252.*rho_D2-84.)*z*z*z);
      double S1=V1*(1.+Delta*(-0.019+0.041*(w-1.)-0.015*(w-1.)*(w-1.)));

      double hp=1./2./(1.+r_D*r_D-2.*r_D*w)*(-(1.+r_D)*(1.+r_D)*(w-1.)*V1+(1.-r_D)*(1.-r_D)*(w+1.)*S1);
      double hm=(1.-r_D*r_D)*(w+1.)/2./(1.+r_D*r_D-2.*r_D*w)*(S1-V1);
      double hT=(mb+mc)/(mB+mD)*(hp-(1.+r_D)/(1.-r_D)*hm);

      double F_1=1./2./sqrt(mB*mD)*((mB+mD)*hp-(mB-mD)*hm);
      double F_0=1./2./sqrt(mB*mD)*(((mB+mD)*(mB+mD)-q2)/(mB+mD)*hp-((mB-mD)*(mB-mD)-q2)/(mB-mD)*hm);
      double F_T=(mB+mD)/2./sqrt(mB*mD)*hT;

      double Hs_V0=sqrt(lambda_D/q2)*F_1;
      double Hs_Vt=(mB*mB-mD*mD)/sqrt(q2)*F_0;
      double Hs_S=(mB*mB-mD*mD)/(mb-mc)*F_0;
      double Hs_T=-sqrt(lambda_D)/(mB+mD)*F_T;


      double dGamma_dq2 = std::real(std::norm(GF*Vcb)/192./pow(pi,3.)/pow(mB,3.)*q2*sqrt(lambda_D)*std::norm(1.-ml*ml/q2)*
      (std::norm(1.+C_V1+C_V2)*((1.+ml*ml/2./q2)*Hs_V0*Hs_V0+3./2.*ml*ml/q2*Hs_Vt*Hs_Vt)
      +3./2.*(std::norm(gs)+std::norm(gsmutau))*Hs_S*Hs_S+8.*std::norm(C_T)*(1.+2.*ml*ml/q2)*Hs_T*Hs_T
      +3.*(1.+C_V1+C_V2)*std::real(gs)*ml/sqrt(q2)*Hs_S*Hs_Vt
      -12.*(1.+C_V1+C_V2)*std::conj(C_T)*ml/sqrt(q2)*Hs_T*Hs_V0));

      return dGamma_dq2;
    }

    ///  B->D* tau nu distributions in THDM
    // TODO: If this only works with taus change name
    double THDM_dGammaBDstarlnu(std::complex<double> gp, std::complex<double> gpmutau, double q2)
    {
      // TODO: Change to use sminputs and constants
      const double mB = 5.27961;
      const double mDs = 2.007;
      const double ml = 1.77686;
      const double mb = 4.18;
      const double mc = 1.28;
      const double GF = 1.16638e-5;
      const double Vcb = 0.041344392;

      const double rho_Dstar2=1.214;
      const double R1_1=1.403;
      const double R2_1=0.864;
      const double R3_1=0.97;
      const double hA1_1=0.921;

      double C_V1=0.;
      double C_V2=0.;
      double C_T=0.;

      double lambda_Ds=((mB-mDs)*(mB-mDs)-q2)*((mB+mDs)*(mB+mDs)-q2);

      double r_Dstar=mDs/mB;
      double w=(mB*mB+mDs*mDs-q2)/2./mB/mDs;
      double z=(sqrt(w+1.)-sqrt(2.))/(sqrt(w+1.)+sqrt(2.));

      double hA1=hA1_1*(1.-8.*rho_Dstar2*z+(53.*rho_Dstar2-15.)*z*z-(231.*rho_Dstar2-91.)*z*z*z);
      double R1=R1_1-0.12*(w-1.)+0.05*(w-1.)*(w-1.);
      double R2=R2_1-0.11*(w-1.)-0.06*(w-1.)*(w-1.);
      double R3=R3_1-0.052*(w-1.)+0.026*(w-1.)*(w-1.);

      double hV=R1*hA1;
      double hA2=(R2-R3)/2./r_Dstar*hA1;
      double hA3=(R2+R3)/2.*hA1;

      double hT1=1./2./(1.+r_Dstar*r_Dstar-2.*r_Dstar*w)*((mb-mc)/(mB-mDs)*(1.-r_Dstar)*(1.-r_Dstar)*(w+1.)*hA1-(mb+mc)/(mB+mDs)*(1.+r_Dstar)*(1.+r_Dstar)*(w-1.)*hV);
      double hT2=(1.-r_Dstar*r_Dstar)*(w+1.)/2./(1.+r_Dstar*r_Dstar-2.*r_Dstar*w)*((mb-mc)/(mB-mDs)*hA1-(mb+mc)/(mB+mDs)*hV);
      double hT3=-1./2./(1.+r_Dstar)/(1.+r_Dstar*r_Dstar-2.*r_Dstar*w)*(2.*(mb-mc)/(mB-mDs)*r_Dstar*(w+1.)*hA1-(mb-mc)/(mB-mDs)*(1.+r_Dstar*r_Dstar-2.*r_Dstar*w)*(hA3-r_Dstar*hA2)-(mb+mc)/(mB+mDs)*(1.+r_Dstar)*(1.+r_Dstar)*hV);

      double V=(mB+mDs)/2./sqrt(mB*mDs)*hV;
      double A_1=((mB+mDs)*(mB+mDs)-q2)/2./sqrt(mB*mDs)/(mB+mDs)*hA1;
      double A_2=(mB+mDs)/2./sqrt(mB*mDs)*(hA3+mDs/mB*hA2);
      double A_0=1./2./sqrt(mB*mDs)*(((mB+mDs)*(mB+mDs)-q2)/2./mDs*hA1-(mB*mB-mDs*mDs+q2)/2./mB*hA2-(mB*mB-mDs*mDs-q2)/2./mDs*hA3);
      double T_1=1./2./sqrt(mB*mDs)*((mB+mDs)*hT1-(mB-mDs)*hT2);
      double T_2=1./2./sqrt(mB*mDs)*(((mB+mDs)*(mB+mDs)-q2)/(mB+mDs)*hT1-((mB-mDs)*(mB-mDs)-q2)/(mB-mDs)*hT2);
      double T_3=1./2./sqrt(mB*mDs)*((mB-mDs)*hT1-(mB+mDs)*hT2-2.*(mB*mB-mDs*mDs)/mB*hT3);

      double H_Vp=(mB+mDs)*A_1-sqrt(lambda_Ds)/(mB+mDs)*V;
      double H_Vm=(mB+mDs)*A_1+sqrt(lambda_Ds)/(mB+mDs)*V;
      double H_V0=(mB+mDs)/2./mDs/sqrt(q2)*(-(mB*mB-mDs*mDs-q2)*A_1+lambda_Ds/pow(mB+mDs,2)*A_2);
      double H_Vt=-sqrt(lambda_Ds/q2)*A_0;
      double H_S=-sqrt(lambda_Ds)/(mb+mc)*A_0;
      double H_Tp=1./sqrt(q2)*((mB*mB-mDs*mDs)*T_2+sqrt(lambda_Ds)*T_1);
      double H_Tm=1./sqrt(q2)*(-(mB*mB-mDs*mDs)*T_2+sqrt(lambda_Ds)*T_1);
      double H_T0=1./2./mDs*(-(mB*mB+3.*mDs*mDs-q2)*T_2+lambda_Ds/(mB*mB-mDs*mDs)*T_3);

      double dGamma_dq2 = std::real(std::norm(GF*Vcb)/192./pow(pi,3.)/pow(mB,3.)*q2*sqrt(lambda_Ds)*std::norm(1.-ml*ml/q2)*
      ((std::norm(1.+C_V1)+std::norm(C_V2))*((1.+ml*ml/2./q2)*(H_Vp*H_Vp+H_Vm*H_Vm+H_V0*H_V0)+3./2.*ml*ml/q2*H_Vt*H_Vt)
      -2.*(1.+C_V1)*std::conj(C_V2)*((1.+ml*ml/2./q2)*(H_V0*H_V0+2.*H_Vp*H_Vm)+3./2.*ml*ml/q2*H_Vt*H_Vt)
      +3./2.*(std::norm(gp)+std::norm(gpmutau))*H_S*H_S+8.*std::norm(C_T)*(1.+2.*ml*ml/q2)*(H_Tp*H_Tp+H_Tm*H_Tm+H_T0*H_T0)
      +3.*(1.+C_V1-C_V2)*(std::real(gp))*ml/sqrt(q2)*H_S*H_Vt
      -12.*(1.+C_V1)*std::conj(C_T)*ml/sqrt(q2)*(H_T0*H_V0+H_Tp*H_Vp-H_Tm*H_Vm)
      +12.*C_V2*std::conj(C_T)*ml/sqrt(q2)*(H_T0*H_V0+H_Tp*H_Vm-H_Tm*H_Vp)));

      return dGamma_dq2;
    }

    ///  B->D* tau nu distribution for FLDstar
    double THDM_dFLDstar(std::complex<double> gp, std::complex<double> gpmutau, double q2)
    {
      const double mB = 5.27961;
      const double mDs = 2.007;
      const double ml = 1.77686;
      const double mb = 4.18;
      const double mc = 1.28;
      const double GF = 1.16638e-5;
      const double Vcb = 0.041344392;

      const double rho_Dstar2=1.214;
      const double R1_1=1.403;
      const double R2_1=0.864;
      const double R3_1=0.97;
      const double hA1_1=0.921;

      double C_V1=0.;
      double C_V2=0.;
      double C_T=0.;

      double lambda_Ds=((mB-mDs)*(mB-mDs)-q2)*((mB+mDs)*(mB+mDs)-q2);

      double r_Dstar=mDs/mB;
      double w=(mB*mB+mDs*mDs-q2)/2./mB/mDs;
      double z=(sqrt(w+1.)-sqrt(2.))/(sqrt(w+1.)+sqrt(2.));

      double hA1=hA1_1*(1.-8.*rho_Dstar2*z+(53.*rho_Dstar2-15.)*z*z-(231.*rho_Dstar2-91.)*z*z*z);
      double R1=R1_1-0.12*(w-1.)+0.05*(w-1.)*(w-1.);
      double R2=R2_1-0.11*(w-1.)-0.06*(w-1.)*(w-1.);
      double R3=R3_1-0.052*(w-1.)+0.026*(w-1.)*(w-1.);

      double hV=R1*hA1;
      double hA2=(R2-R3)/2./r_Dstar*hA1;
      double hA3=(R2+R3)/2.*hA1;

      double hT1=1./2./(1.+r_Dstar*r_Dstar-2.*r_Dstar*w)*((mb-mc)/(mB-mDs)*(1.-r_Dstar)*(1.-r_Dstar)*(w+1.)*hA1-(mb+mc)/(mB+mDs)*(1.+r_Dstar)*(1.+r_Dstar)*(w-1.)*hV);
      double hT2=(1.-r_Dstar*r_Dstar)*(w+1.)/2./(1.+r_Dstar*r_Dstar-2.*r_Dstar*w)*((mb-mc)/(mB-mDs)*hA1-(mb+mc)/(mB+mDs)*hV);
      double hT3=-1./2./(1.+r_Dstar)/(1.+r_Dstar*r_Dstar-2.*r_Dstar*w)*(2.*(mb-mc)/(mB-mDs)*r_Dstar*(w+1.)*hA1-(mb-mc)/(mB-mDs)*(1.+r_Dstar*r_Dstar-2.*r_Dstar*w)*(hA3-r_Dstar*hA2)-(mb+mc)/(mB+mDs)*(1.+r_Dstar)*(1.+r_Dstar)*hV);

      double V=(mB+mDs)/2./sqrt(mB*mDs)*hV;
      double A_1=((mB+mDs)*(mB+mDs)-q2)/2./sqrt(mB*mDs)/(mB+mDs)*hA1;
      double A_2=(mB+mDs)/2./sqrt(mB*mDs)*(hA3+mDs/mB*hA2);
      double A_0=1./2./sqrt(mB*mDs)*(((mB+mDs)*(mB+mDs)-q2)/2./mDs*hA1-(mB*mB-mDs*mDs+q2)/2./mB*hA2-(mB*mB-mDs*mDs-q2)/2./mDs*hA3);
      double T_1=1./2./sqrt(mB*mDs)*((mB+mDs)*hT1-(mB-mDs)*hT2);
      double T_2=1./2./sqrt(mB*mDs)*(((mB+mDs)*(mB+mDs)-q2)/(mB+mDs)*hT1-((mB-mDs)*(mB-mDs)-q2)/(mB-mDs)*hT2);
      double T_3=1./2./sqrt(mB*mDs)*((mB-mDs)*hT1-(mB+mDs)*hT2-2.*(mB*mB-mDs*mDs)/mB*hT3);

      double H_Vp=(mB+mDs)*A_1-sqrt(lambda_Ds)/(mB+mDs)*V;
      double H_Vm=(mB+mDs)*A_1+sqrt(lambda_Ds)/(mB+mDs)*V;
      double H_V0=(mB+mDs)/2./mDs/sqrt(q2)*(-(mB*mB-mDs*mDs-q2)*A_1+lambda_Ds/pow(mB+mDs,2)*A_2);
      double H_Vt=-sqrt(lambda_Ds/q2)*A_0;
      double H_S=-sqrt(lambda_Ds)/(mb+mc)*A_0;
      double H_Tp=1./sqrt(q2)*((mB*mB-mDs*mDs)*T_2+sqrt(lambda_Ds)*T_1);
      double H_Tm=1./sqrt(q2)*(-(mB*mB-mDs*mDs)*T_2+sqrt(lambda_Ds)*T_1);
      double H_T0=1./2./mDs*(-(mB*mB+3.*mDs*mDs-q2)*T_2+lambda_Ds/(mB*mB-mDs*mDs)*T_3);

      double dGamma_dq2 = std::real(std::norm(GF*Vcb)/192./pow(pi,3.)/pow(mB,3.)*q2*sqrt(lambda_Ds)*std::norm(1.-ml*ml/q2)*
      ((std::norm(1.+C_V1)+std::norm(C_V2))*((1.+ml*ml/2./q2)*(H_V0*H_V0)+3./2.*ml*ml/q2*H_Vt*H_Vt)
      -2.*(1.+C_V1)*std::conj(C_V2)*((1.+ml*ml/2./q2)*(H_V0*H_V0)+3./2.*ml*ml/q2*H_Vt*H_Vt)
      +3./2.*(std::norm(gp)+std::norm(gpmutau))*H_S*H_S+8.*std::norm(C_T)*(1.+2.*ml*ml/q2)*(H_Tp*H_Tp+H_Tm*H_Tm+H_T0*H_T0)
      +3.*(1.+C_V1-C_V2)*(std::real(gp))*ml/sqrt(q2)*H_S*H_Vt
      -12.*(1.+C_V1)*std::conj(C_T)*ml/sqrt(q2)*(H_T0*H_V0+H_Tp*H_Vp-H_Tm*H_Vm)
      +12.*C_V2*std::conj(C_T)*ml/sqrt(q2)*(H_T0*H_V0+H_Tp*H_Vm-H_Tm*H_Vp)));

      return dGamma_dq2;
    }

    ///Partial decay width for B->D l nu computed with Simpson's rule
    // TODO: Does this actually work for muons, or only taus
    double Gamma_BDlnu(std::complex<double> gs, std::complex<double> gsmutau, int gen, int n)
    {
      double a = 0.0;
      if (gen==3)
      {
        a = 1.77686*1.77686;//mTau^2
      }
      else if (gen==2)
      {
        a = 0.105658*0.105658;//mMu^2
      }
      else if (gen==1)
      {
        FlavBit_error().raise(LOCAL_INFO, "BDenu is not supported for THDM model");
      }
      const double b = 3.40961*3.40961;//(mB-mD)^2
      double h = (b-a)/n;
      double sum_odds = 0.0;
      for (int i = 1; i < n; i += 2)
      {
        sum_odds += THDM_dGammaBDlnu(gs, gsmutau, a + i * h);
      }
      double sum_evens = 0.0;
      for (int i = 2; i < n; i += 2)
      {
        sum_evens += THDM_dGammaBDlnu(gs, gsmutau, a + i * h);
      }
      return (THDM_dGammaBDlnu(gs, gsmutau, a) + THDM_dGammaBDlnu(gs, gsmutau, b) + 2 * sum_evens + 4 * sum_odds) * h / 3;
    }

    ///Partial decay width for B->D* l nu computed with Simpson's rule
    // TODO: Does this actually work for muons, or only taus
    double Gamma_BDstarlnu(std::complex<double> gp, std::complex<double> gpmutau, int gen, int n)
    {
      double a = 0.0;
      if (gen==3)
      {
        a = 1.77686*1.77686;//mTau^2
      }
      else if (gen==2)
      {
        a = 0.105658*0.105658;//mMu^2
      }
      else if (gen==1)
      {
        FlavBit_error().raise(LOCAL_INFO, "BDstarnu is not supported for THDM model");
      }
      const double b = 3.27261*3.27261;//(mB-mDs)^2
      double h = (b-a)/n;
      double sum_odds = 0.0;
      for (int i = 1; i < n; i += 2)
      {
        sum_odds += THDM_dGammaBDstarlnu(gp, gpmutau, a + i * h);
      }
      double sum_evens = 0.0;
      for (int i = 2; i < n; i += 2)
      {
        sum_evens += THDM_dGammaBDstarlnu(gp, gpmutau, a + i * h);
      }
      return (THDM_dGammaBDstarlnu(gp, gpmutau, a) + THDM_dGammaBDstarlnu(gp, gpmutau, b) + 2 * sum_evens + 4 * sum_odds) * h / 3;
    }

    ///Partial decay width for B->D* l nu for lambda_Dstar=0 computed with Simpson's rule
    double GammaDstar_BDstarlnu(std::complex<double> gp, std::complex<double> gpmutau, int n)
    {
      const double a = 1.77686*1.77686;//mTau^2
      const double b = 3.27261*3.27261;//(mB-mDs)^2
      double h = (b-a)/n;
      double sum_odds = 0.0;
      for (int i = 1; i < n; i += 2)
      {
        sum_odds += THDM_dFLDstar(gp, gpmutau, a + i * h);
      }
      double sum_evens = 0.0;
      for (int i = 2; i < n; i += 2)
      {
        sum_evens += THDM_dFLDstar(gp, gpmutau, a + i * h);
      }
      return (THDM_dFLDstar(gp, gpmutau, a) + THDM_dFLDstar(gp, gpmutau, b) + 2 * sum_evens + 4 * sum_odds) * h / 3;
    }

    ///FLDstar Gamma=lambda_Dstar=0(B->D* l nu)/Gamma
    double GammaDstar_Gamma(std::complex<double> gp, std::complex<double> gpmutau)
    {
      double GammaDstar_Gamma = GammaDstar_BDstarlnu(gp, gpmutau, 13)/Gamma_BDstarlnu(gp, gpmutau, 3, 13);

      return GammaDstar_Gamma;
    }

    /// FLDstar Gamma=lambda_Dstar=0(B->D* l nu)/Gamma in THDM
    void THDM_FLDstar(double &result)
    {
      using namespace Pipes::THDM_FLDstar;
      if (flav_debug) std::cout<<"Starting THDM_FLDstarlnu"<< std::endl;

      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      const double lambda = Dep::SMINPUTS->CKM.lambda;
      const double A = Dep::SMINPUTS->CKM.A;
      const double Vcs = 1 - (1/2)*lambda*lambda;
      const double Vcb = A*lambda*lambda;
      const double Vtb = 1 - (1/2)*A*A*pow(lambda,4);
      double tanb = spectrum.get(Par::dimensionless,"tanb");
      double beta = atan(tanb);
      double cosb = cos(beta);
      const double v = spectrum.get(Par::mass1, "vev");
      const double CSMcb = 4*sminputs.GF*Vcb/sqrt(2.0);
      const double mTau = Dep::SMINPUTS->mTau;
      const double mBmB = Dep::SMINPUTS->mBmB;
      double mHp = spectrum.get(Par::Pole_Mass,"H+");
      std::complex<double> Ymutau(spectrum.get(Par::dimensionless,"Ye2",2,3), spectrum.get(Par::dimensionless, "ImYe2",2,3));
      std::complex<double> Ytautau(spectrum.get(Par::dimensionless,"Ye2",3,3), spectrum.get(Par::dimensionless, "ImYe2",3,3));
      std::complex<double> Ytc(spectrum.get(Par::dimensionless,"Yu2",3,2), spectrum.get(Par::dimensionless, "ImYu2",3,2));
      std::complex<double> Ybb(spectrum.get(Par::dimensionless,"Yd2",3,3), spectrum.get(Par::dimensionless, "ImYd2",3,3));
      std::complex<double> Ysb(spectrum.get(Par::dimensionless,"Yd2",2,3), spectrum.get(Par::dimensionless, "ImYd2",2,3));
      std::complex<double> xitc = Ytc/cosb;
      std::complex<double> xibb = -((sqrt(2)*mBmB*tanb)/v) + Ybb/cosb;
      std::complex<double> xisb = Ysb/cosb;
      std::complex<double> xitautau = -((sqrt(2)*mTau*tanb)/v) + Ytautau/cosb;
      std::complex<double> ximutau = Ymutau/cosb;
      const double mCmC = Dep::SMINPUTS->mCmC;
      std::complex<double> Ycc(spectrum.get(Par::dimensionless,"Yu2",2,2), spectrum.get(Par::dimensionless, "ImYu2",2,2));
      std::complex<double> xicc = -((sqrt(2)*mCmC*tanb)/v) + Ycc/cosb;
      std::complex<double> CRcb = -(Vcb*xibb+Vcs*xisb)*std::conj(xitautau)/pow(mHp,2);
      std::complex<double> CLcb = (Vcb*std::conj(xicc)+Vtb*std::conj(xitc))*std::conj(xitautau)/pow(mHp,2);
      std::complex<double> CRcbmutau = -(Vcb*xibb+Vcs*xisb)*std::conj(ximutau)/pow(mHp,2);
      std::complex<double> CLcbmutau = (Vcb*std::conj(xicc)+Vtb*std::conj(xitc))*std::conj(ximutau)/pow(mHp,2);
      std::complex<double> gp =  1.5*(CRcb - CLcb)/CSMcb;
      std::complex<double> gpmutau =  1.5*(CRcbmutau - CLcbmutau)/CSMcb;

      result = GammaDstar_Gamma(gp,gpmutau);
      if (flav_debug) printf("Gamma(B->D* tau nu)/Gamma=%.3e\n",result);
      if (flav_debug) std::cout<<"Finished THDM_FLDstar"<< std::endl;
    }

    /// Normalized partial decay width  dGamma(B->D tau nu)/dq2/Gamma
    double THDM_dGammaBDtaunu_Gamma(double q2min, double q2max, SMInputs sminputs, Spectrum spectrum)
    {
      const double A      = sminputs.CKM.A;
      const double lambda = sminputs.CKM.lambda;
      const double Vcs = 1 - (1/2)*lambda*lambda;
      const double Vcb = A*lambda*lambda;
      const double Vtb = 1 - (1/2)*A*A*pow(lambda,4);
      double tanb = spectrum.get(Par::dimensionless,"tanb");
      double beta = atan(tanb);
      double cosb = cos(beta);
      const double v = spectrum.get(Par::mass1, "vev");
      const double mTau = sminputs.mTau;
      const double mBmB = sminputs.mBmB;
      const double mCmC = sminputs.mCmC;
      const double CSMcb = 4*sminputs.GF*Vcb/(sqrt(2.0));
      double mHp = spectrum.get(Par::Pole_Mass,"H+");
      std::complex<double> Ymutau(spectrum.get(Par::dimensionless,"Ye2",2,3), spectrum.get(Par::dimensionless, "ImYe2",2,3));
      std::complex<double> Ytautau(spectrum.get(Par::dimensionless,"Ye2",3,3), spectrum.get(Par::dimensionless, "ImYe2",3,3));
      std::complex<double> Ytc(spectrum.get(Par::dimensionless,"Yu2",3,2), spectrum.get(Par::dimensionless, "ImYu2",3,2));
      std::complex<double> Ybb(spectrum.get(Par::dimensionless,"Yd2",3,3), spectrum.get(Par::dimensionless, "ImYd2",3,3));
      std::complex<double> Ysb(spectrum.get(Par::dimensionless,"Yd2",2,3), spectrum.get(Par::dimensionless, "ImYd2",2,3));
      std::complex<double> xitc = Ytc/cosb;
      std::complex<double> xibb = -((sqrt(2)*mBmB*tanb)/v) + Ybb/cosb;
      std::complex<double> xisb = Ysb/cosb;
      std::complex<double> xitautau = -((sqrt(2)*mTau*tanb)/v) + Ytautau/cosb;
      std::complex<double> ximutau = Ymutau/cosb;
      std::complex<double> Ycc(spectrum.get(Par::dimensionless,"Yu2",2,2), spectrum.get(Par::dimensionless, "ImYu2",2,2));
      std::complex<double> xicc = -((sqrt(2)*mCmC*tanb)/v) + Ycc/cosb;
      std::complex<double> CRcb = -(Vcb*xibb+Vcs*xisb)*std::conj(xitautau)/pow(mHp,2);
      std::complex<double> CLcb = (Vcb*std::conj(xicc)+Vtb*std::conj(xitc))*std::conj(xitautau)/pow(mHp,2);
      std::complex<double> CRcbmutau = -(Vcb*xibb+Vcs*xisb)*std::conj(ximutau)/pow(mHp,2);
      std::complex<double> CLcbmutau = (Vcb*std::conj(xicc)+Vtb*std::conj(xitc))*std::conj(ximutau)/pow(mHp,2);
      std::complex<double> gs =  1.5*(CRcb + CLcb)/CSMcb;
      std::complex<double> gsmutau =  1.5*(CRcbmutau + CLcbmutau)/CSMcb;

      double q2 = (q2min + q2max)/2;

      double dGamma_dq2_Gamma = THDM_dGammaBDlnu(gs, gsmutau, q2)/Gamma_BDlnu(gs, gsmutau, 3, 15);

      return dGamma_dq2_Gamma;
    }

    /// Normalized partial decay width dGamma(B->D* tau nu)/dq2/Gamma
    double THDM_dGammaBDstartaunu_Gamma(double q2min, double q2max, SMInputs sminputs, Spectrum spectrum)
    {
      const double A      = sminputs.CKM.A;
      const double lambda = sminputs.CKM.lambda;
      const double Vcs = 1 - (1/2)*lambda*lambda;
      const double Vcb = A*lambda*lambda;
      const double Vtb = 1 - (1/2)*A*A*pow(lambda,4);
      const double CSMcb = 4*sminputs.GF*Vcb/(sqrt(2.0));
      double tanb = spectrum.get(Par::dimensionless,"tanb");
      double beta = atan(tanb);
      double cosb = cos(beta);
      const double v = spectrum.get(Par::mass1, "vev");
      const double mTau = sminputs.mTau;
      const double mBmB = sminputs.mBmB;
      const double mCmC = sminputs.mCmC;
      double mHp = spectrum.get(Par::Pole_Mass,"H+");
      std::complex<double> Ymutau(spectrum.get(Par::dimensionless,"Ye2",2,3), spectrum.get(Par::dimensionless, "ImYe2",2,3));
      std::complex<double> Ytautau(spectrum.get(Par::dimensionless,"Ye2",3,3), spectrum.get(Par::dimensionless, "ImYe2",3,3));
      std::complex<double> Ytc(spectrum.get(Par::dimensionless,"Yu2",3,2), spectrum.get(Par::dimensionless, "ImYu2",3,2));
      std::complex<double> Ybb(spectrum.get(Par::dimensionless,"Yd2",3,3), spectrum.get(Par::dimensionless, "ImYd2",3,3));
      std::complex<double> Ysb(spectrum.get(Par::dimensionless,"Yd2",2,3), spectrum.get(Par::dimensionless, "ImYd2",2,3));
      std::complex<double> xitc = Ytc/cosb;
      std::complex<double> xibb = -((sqrt(2)*mBmB*tanb)/v) + Ybb/cosb;
      std::complex<double> xisb = Ysb/cosb;
      std::complex<double> xitautau = -((sqrt(2)*mTau*tanb)/v) + Ytautau/cosb;
      std::complex<double> ximutau = Ymutau/cosb;
      std::complex<double> Ycc(spectrum.get(Par::dimensionless,"Yu2",2,2), spectrum.get(Par::dimensionless, "ImYu2",2,2));
      std::complex<double> xicc = -((sqrt(2)*mCmC*tanb)/v) + Ycc/cosb;
      std::complex<double> CRcb = -(Vcb*xibb+Vcs*xisb)*std::conj(xitautau)/pow(mHp,2);
      std::complex<double> CLcb = (Vcb*std::conj(xicc)+Vtb*std::conj(xitc))*std::conj(xitautau)/pow(mHp,2);
      std::complex<double> CRcbmutau = -(Vcb*xibb+Vcs*xisb)*std::conj(ximutau)/pow(mHp,2);
      std::complex<double> CLcbmutau = (Vcb*std::conj(xicc)+Vtb*std::conj(xitc))*std::conj(ximutau)/pow(mHp,2);
      std::complex<double> gp = 1.5*(CRcb - CLcb)/CSMcb;
      std::complex<double> gpmutau = 1.5*(CRcbmutau - CLcbmutau)/CSMcb;
      double q2 = (q2min + q2max)/2;

      double dGamma_dq2_Gamma = THDM_dGammaBDstarlnu(gp, gpmutau, q2)/Gamma_BDstarlnu(gp, gpmutau, 3, 13);

      return dGamma_dq2_Gamma;
    }

    /// Normalized differential B-> D tau nu width
    void THDM_dBRBDtaunu(map_dblpair_dbl &result)
    {
      using namespace Pipes::THDM_dBRBDtaunu;
      if (flav_debug) std::cout<<"Starting THDM_dBRBDtaunu"<< std::endl;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      std::vector<ddpair> bins = {{4.0, 4.5}, {4.5, 5.0}, {5.0, 5.5}, {5.5, 6.0},
                                  {6.0, 6.5}, {6.5, 7.0}, {7.0, 7.5}, {7.5, 8.0},
                                  {8.0, 8.5}, {8.5, 9.0}, {9.0, 9.5}, {9.5, 10.0},
                                  {10.0, 10.5}, {10.5, 11.0}, {11.0, 11.5}};

      for(ddpair bin : bins)
        result[bin] = THDM_dGammaBDtaunu_Gamma(bin.first, bin.second, sminputs, spectrum);

      if (flav_debug) std::cout<<"dGamma(B->D tau nu)/dq2/Gamma=" << result << std::endl;
      if (flav_debug) std::cout<<"Finished THDM_dBRBDtaunu"<< std::endl;
    }

    /// Normalized differential B-> D* tau nu width
    void THDM_dBRBDstartaunu(map_dblpair_dbl &result)
    {
      using namespace Pipes::THDM_dBRBDstartaunu;
      if (flav_debug) std::cout<<"Starting THDM_dBRBDstartaunu"<< std::endl;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      std::vector<ddpair> bins = {{4.0, 4.5}, {4.5, 5.0}, {5.0, 5.5}, {5.5, 6.0},
                                  {6.0, 6.5}, {6.5, 7.0}, {7.0, 7.5}, {7.5, 8.0},
                                  {8.0, 8.5}, {8.5, 9.0}, {9.0, 9.5}, {9.5, 10.0},
                                  {10.0, 10.5}};

      for(ddpair bin : bins)
        result[bin] = THDM_dGammaBDstartaunu_Gamma(bin.first, bin.second, sminputs, spectrum);

      if (flav_debug) std::cout<<"dGamma(B->D* tau nu)/dq2/Gamma=" << result << std::endl;
      if (flav_debug) std::cout<<"Finished THDM_dBRBDstartaunu"<< std::endl;
    }

    /// Measurements for the differential widths of tree-level semileptonic B decays
    void dBRBDtaunu_measurements(predictions_measurements_covariances &pmc)
    {
      using namespace Pipes::dBRBDtaunu_measurements;

      map_dblpair_dbl bins_theory = *Dep::dBRBDtaunu;

      const int n_bins=bins_theory.size();
      static bool first = true;
      static std::vector<bool> th_err_absolute;
      static std::vector<double> th_err;

      if (flav_debug) std::cout<<"Starting dBRBDtaunu_measurements"<< std::endl;

      // Read and calculate things based on the observed data only the first time through, as none of it depends on the model parameters.
      if (first)
      {
        pmc.LL_name="dBRBDtaunu_LogLikelihood";

        // Read in experimental measuremens
        Flav_reader fread(GAMBIT_DIR  "/FlavBit/data");
        fread.debug_mode(flav_debug);
        if (flav_debug) std::cout<<"Initialised Flav reader in BDtaunu_measurements"<< std::endl;

        for (auto bins_th: bins_theory)
        {
          std::ostringstream observable;
          observable << "dBR_BDlnu_" << std::fixed << std::setprecision(1) << bins_th.first.first << "-" << bins_th.first.second;
          fread.read_yaml_measurement("flav_data.yaml", observable.str());
        }

        fread.initialise_matrices();
        pmc.cov_exp=fread.get_exp_cov();
        pmc.value_exp=fread.get_exp_value();

        pmc.value_th.resize(n_bins,1);
        // Set all entries in the covariance matrix explicitly to zero, as we will only write the diagonal ones later.
        pmc.cov_th = boost::numeric::ublas::zero_matrix<double>(n_bins,n_bins);
        for (int i = 0; i < n_bins; ++i)
        {
          th_err.push_back(fread.get_th_err()(i,0).first);
          th_err_absolute.push_back(fread.get_th_err()(i,0).second);
        }

        pmc.dim=n_bins;

        // Init over.
        first = false;
      }

      std::vector<double> theory;
      for(auto bins_th : bins_theory)
        theory.push_back(bins_th.second);

      for (int i = 0; i < n_bins; ++i)
      {
        pmc.value_th(i,0) = theory[i];
        pmc.cov_th(i,i) = th_err[i]*th_err[i] * (th_err_absolute[i] ? 1.0 : theory[i]*theory[i]);
      }

      pmc.diff.clear();
      for (int i=0;i<n_bins;++i)
      {
        pmc.diff.push_back(pmc.value_exp(i,0)-pmc.value_th(i,0));
      }

      if (flav_debug) std::cout<<"Finished dBRBDtaunu_measurements"<< std::endl;

    }

    /// Measurements of the differential width for tree-level semileptonic B decays
    void dBRBDstartaunu_measurements(predictions_measurements_covariances &pmc)
    {
      using namespace Pipes::dBRBDstartaunu_measurements;

      map_dblpair_dbl bins_theory = *Dep::dBRBDstartaunu;

      const int n_bins=bins_theory.size();
      static bool first = true;
      static std::vector<bool> th_err_absolute;
      static std::vector<double> th_err;

      if (flav_debug) std::cout<<"Starting dBRBDstartaunu_measurements"<< std::endl;

      // Read and calculate things based on the observed data only the first time through, as none of it depends on the model parameters.
      if (first)
      {
        pmc.LL_name="dBRBDstartaunu_LogLikelihood";

        // Read in experimental measuremens
        Flav_reader fread(GAMBIT_DIR  "/FlavBit/data");
        fread.debug_mode(flav_debug);
        if (flav_debug) std::cout<<"Initialised Flav reader in BDstartaunu_measurements"<< std::endl;

        for (auto bins_th: bins_theory)
        {
          std::ostringstream observable;
          observable << "dBR_BDstarlnu_" << std::fixed << std::setprecision(1) << bins_th.first.first << "-" << bins_th.first.second;
          fread.read_yaml_measurement("flav_data.yaml", observable.str());
        }

        fread.initialise_matrices();
        pmc.cov_exp=fread.get_exp_cov();
        pmc.value_exp=fread.get_exp_value();

        pmc.value_th.resize(n_bins,1);
        // Set all entries in the covariance matrix explicitly to zero, as we will only write the diagonal ones later.
        pmc.cov_th = boost::numeric::ublas::zero_matrix<double>(n_bins,n_bins);
        for (int i = 0; i < n_bins; ++i)
        {
          th_err.push_back(fread.get_th_err()(i,0).first);
          th_err_absolute.push_back(fread.get_th_err()(i,0).second);
        }

        pmc.dim=n_bins;

        // Init over.
        first = false;
      }

      std::vector<double> theory;
      for(auto bins_th : bins_theory)
        theory.push_back(bins_th.second);

      for (int i = 0; i < n_bins; ++i)
      {
        pmc.value_th(i,0) = theory[i];
        pmc.cov_th(i,i) = th_err[i]*th_err[i] * (th_err_absolute[i] ? 1.0 : theory[i]*theory[i]);
      }

      pmc.diff.clear();
      for (int i=0;i<n_bins;++i)
      {
        pmc.diff.push_back(pmc.value_exp(i,0)-pmc.value_th(i,0));
      }

      if (flav_debug) std::cout<<"Finished dBRBDstartaunu_measurements"<< std::endl;
    }


    //TODO: This does not work currently in this form as it is not implemented in SuperIso
    /// SuperIso prediction for B -> tau nu_tau
    //SI_SINGLE_PREDICTION_FUNCTION(B2taunu)

    /// Br B->tau nu_tau decays
    void SuperIso_prediction_Btaunu(double &result)
    {
      using namespace Pipes::SuperIso_prediction_Btaunu;
      if (flav_debug) std::cout<<"Starting SuperIso_prediction_Btaunu"<< std::endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result = BEreq::Btaunu(&param);

      if (flav_debug) printf("BR(B->tau nu)=%.3e\n",result);
      if (flav_debug) std::cout<<"Finished SuperIso_prediction_Btaunu"<< std::endl;
    }

    /// Br Bu->tau nu in the THDM
    void THDM_Btaunu(double &result)//(flav_prediction &result)
    {
      using namespace Pipes::THDM_Btaunu;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;
      const double m_B = 5.27926;//All values are taken from SuperIso 3.6
      const double f_B = 0.1905;
      const double hbar = 6.582119514e-25;
      const double life_B = 1.638e-12;
      double tanb = spectrum.get(Par::dimensionless,"tanb");
      double mHp = spectrum.get(Par::Pole_Mass,"H+");
      const double v = spectrum.get(Par::mass1, "vev");
      const double lambda = Dep::SMINPUTS->CKM.lambda;
      const double Vus = lambda;
      const double Vub = 3.55e-3;
      const double mTau = Dep::SMINPUTS->mTau;
      const double mBmB = Dep::SMINPUTS->mBmB;
      std::complex<double> Ysb(spectrum.get(Par::dimensionless,"Yd2",2,3), spectrum.get(Par::dimensionless, "ImYd2",2,3));
      std::complex<double> Ybb(spectrum.get(Par::dimensionless,"Yd2",3,3), spectrum.get(Par::dimensionless, "ImYd2",3,3));
      std::complex<double> Ytaumu(spectrum.get(Par::dimensionless,"Ye2",3,2), spectrum.get(Par::dimensionless, "ImYe2",3,2));
      std::complex<double> Ytautau(spectrum.get(Par::dimensionless,"Ye2",3,3), spectrum.get(Par::dimensionless, "ImYe2",3,3));
      std::complex<double> X13 = (v*(Vub*(-((sqrt(2)*mBmB*tanb)/v) + sqrt(1 + pow(tanb,2))*Ybb) + sqrt(1 + pow(tanb,2))*Vus*Ysb))/(sqrt(2)*mBmB);
      std::complex<double> Z33 = (v*(-((sqrt(2)*mTau*tanb)/v) + sqrt(1 + pow(tanb,2))*Ytautau))/(sqrt(2)*mTau);
      std::complex<double> Z32 = -((sqrt(1 + pow(tanb,2))*v*Ytaumu)/(sqrt(2)*mTau));

      std::complex<double> Deltaij = (pow(m_B,2)*X13*(Z33))/(pow(mHp,2)*Vub);
      std::complex<double> Deltataumu = (pow(m_B,2)*X13*(Z32))/(pow(mHp,2)*Vub);
      std::complex<double> one = {1,0};
      double prediction = std::real((pow(one - Deltaij,2)+pow(Deltataumu,2))*(pow(f_B,2)*pow(sminputs.GF,2)*pow(mTau,2)*pow(1 - pow(mTau,2)/pow(m_B,2),2)*m_B*life_B*pow(Vub,2))/(8.*hbar*pi));
      result = prediction;
      //result.central_values["B2taunu"] = prediction;
      if (flav_debug) std::cout << "BR(Bu->tau nu) = " << prediction << std::endl;
      if (flav_debug) std::cout << "Finished THDMB2taunu" << std::endl;
    }

    /// Br D_s -> tau nu
    void SuperIso_prediction_Dstaunu(double &result)
    {
      using namespace Pipes::SuperIso_prediction_Dstaunu;
      if (flav_debug) std::cout<<"Starting SuperIso_prediction_Dstaunu"<< std::endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result = BEreq::Dstaunu(&param);

      if (flav_debug) printf("BR(Ds->tau nu)=%.3e\n",result);
      if (flav_debug) std::cout<<"Finished SuperIso_prediction_Dstaunu"<< std::endl;
    }

    /// Br D_s->tau nu in the THDM
    void THDM_Dstaunu(double &result)
    {
      using namespace Pipes::THDM_Dstaunu;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;
      const double m_Ds = 1.9683;//All values are taken from SuperIso 3.6
      const double f_Ds = 0.2486;
      const double hbar = 6.582119514e-25;
      const double life_Ds = 5.e-13;
      double tanb = spectrum.get(Par::dimensionless,"tanb");
      double mHp = spectrum.get(Par::Pole_Mass,"H+");
      const double v = spectrum.get(Par::mass1, "vev");
      const double lambda = Dep::SMINPUTS->CKM.lambda;
      const double A = Dep::SMINPUTS->CKM.A;
      const double Vcs = 1 - (1/2)*lambda*lambda;
      const double Vcb = A*lambda*lambda;
      const double Vts = -A*lambda*lambda;
      const double mTau = Dep::SMINPUTS->mTau;
      const double mS = Dep::SMINPUTS->mS;
      const double mCmC = Dep::SMINPUTS->mCmC;
      std::complex<double> Ysb(spectrum.get(Par::dimensionless,"Yd2",2,3), spectrum.get(Par::dimensionless, "ImYd2",2,3));
      std::complex<double> Ytc(spectrum.get(Par::dimensionless,"Yu2",3,2), spectrum.get(Par::dimensionless, "ImYu2",3,2));
      std::complex<double> Ytaumu(spectrum.get(Par::dimensionless,"Ye2",3,2), spectrum.get(Par::dimensionless, "ImYe2",3,2));
      std::complex<double> Ytautau(spectrum.get(Par::dimensionless,"Ye2",3,3), spectrum.get(Par::dimensionless, "ImYe2",3,3));
      std::complex<double> Ycc(spectrum.get(Par::dimensionless,"Yu2",2,2), spectrum.get(Par::dimensionless, "ImYu2",2,2));
      std::complex<double> Yss(spectrum.get(Par::dimensionless,"Yd2",2,2), spectrum.get(Par::dimensionless, "ImYd2",2,2));
      std::complex<double> Y22 = ((v*(Vcs*(-((sqrt(2)*mCmC*tanb)/v) + sqrt(1 + pow(tanb,2))*Ycc) + sqrt(1 + pow(tanb,2))*Vts*Ytc))/(sqrt(2)*mCmC));
      std::complex<double> X22 = (v*(sqrt(1 + pow(tanb,2))*Vcb*Ysb + Vcs*(-((sqrt(2)*mS*tanb)/v) + sqrt(1 + pow(tanb,2))*Yss)))/(sqrt(2)*mS);
      std::complex<double> Z33 = (v*(-((sqrt(2)*mTau*tanb)/v) + sqrt(1 + pow(tanb,2))*Ytautau))/(sqrt(2)*mTau);
      std::complex<double> Z32 = -((sqrt(1 + pow(tanb,2))*v*Ytaumu)/(sqrt(2)*mTau));

      std::complex<double> Deltaij = (pow(m_Ds,2)*(mS*X22 + mCmC*Y22)*std::conj(Z33))/(pow(mHp,2)*(mS + mCmC)*Vcs);
      std::complex<double> Deltataumu = (pow(m_Ds,2)*(mS*X22 + mCmC*Y22)*std::conj(Z32))/(pow(mHp,2)*(mS + mCmC)*Vcs);
      std::complex<double> one = {1,0};
      result = std::real((pow(one - Deltaij,2)+pow(Deltataumu,2))*(pow(f_Ds,2)*pow(sminputs.GF,2)*pow(mTau,2)*pow(1 - pow(mTau,2)/pow(m_Ds,2),2)*m_Ds*life_Ds*pow(Vcs,2))/(8.*hbar*pi));

      if (flav_debug) std::cout << "BR(Ds->tau nu) = " << result << std::endl;
      if (flav_debug) std::cout << "Finished THDM_Dstaunu" << std::endl;
    }

    /// Br D_s -> mu nu
    void SuperIso_prediction_Dsmunu(double &result)
    {
      using namespace Pipes::SuperIso_prediction_Dsmunu;
      if (flav_debug) std::cout<<"Starting SuperIso_prediction_Dsmunu"<< std::endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result = BEreq::Dsmunu(&param);

      if (flav_debug) printf("BR(Ds->mu nu)=%.3e\n",result);
      if (flav_debug) std::cout<<"Finished SuperIso_prediction_Dsmunu"<< std::endl;
    }

    /// Br D_s->mu nu in the THDM
    void THDM_Dsmunu(double &result)
    {
      using namespace Pipes::THDM_Dsmunu;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;
      const double m_Ds = 1.9683;//All values are taken from SuperIso 3.6
      const double f_Ds = 0.2486;
      const double hbar = 6.582119514e-25;
      const double life_Ds = 5.e-13;
      double tanb = spectrum.get(Par::dimensionless,"tanb");
      double mHp = spectrum.get(Par::Pole_Mass,"H+");
      const double v = spectrum.get(Par::mass1, "vev");
      const double lambda = Dep::SMINPUTS->CKM.lambda;
      const double A = Dep::SMINPUTS->CKM.A;
      const double Vcs = 1 - (1/2)*lambda*lambda;
      const double Vcb = A*lambda*lambda;
      const double Vts = -A*lambda*lambda;
      const double mMu = Dep::SMINPUTS->mMu;
      const double mS = Dep::SMINPUTS->mS;
      const double mCmC = Dep::SMINPUTS->mCmC;
      std::complex<double> Ysb(spectrum.get(Par::dimensionless,"Yd2",2,3), spectrum.get(Par::dimensionless, "ImYd2",2,3));
      std::complex<double> Ytc(spectrum.get(Par::dimensionless,"Yu2",3,2), spectrum.get(Par::dimensionless, "ImYu2",3,2));
      std::complex<double> Ymumu(spectrum.get(Par::dimensionless,"Ye2",2,2), spectrum.get(Par::dimensionless, "ImYe2",2,2));
      std::complex<double> Ymutau(spectrum.get(Par::dimensionless,"Ye2",2,3), spectrum.get(Par::dimensionless, "ImYe2",2,3));
      std::complex<double> Ycc(spectrum.get(Par::dimensionless,"Yu2",2,2), spectrum.get(Par::dimensionless, "ImYu2",2,2));
      std::complex<double> Yss(spectrum.get(Par::dimensionless,"Yd2",2,2), spectrum.get(Par::dimensionless, "ImYd2",2,2));
      std::complex<double> Y22 = ((v*(Vcs*(-((sqrt(2)*mCmC*tanb)/v) + sqrt(1 + pow(tanb,2))*Ycc) + sqrt(1 + pow(tanb,2))*Vts*Ytc))/(sqrt(2)*mCmC));
      std::complex<double> X22 = (v*(sqrt(1 + pow(tanb,2))*Vcb*Ysb + Vcs*(-((sqrt(2)*mS*tanb)/v) + sqrt(1 + pow(tanb,2))*Yss)))/(sqrt(2)*mS);
      std::complex<double> Z22 = (v*(-((sqrt(2)*mMu*tanb)/v) + sqrt(1 + pow(tanb,2))*Ymumu))/(sqrt(2)*mMu);
      std::complex<double> Z23 = (sqrt(1 + pow(tanb,2))*v*Ymutau)/(sqrt(2)*mMu);
      std::complex<double> Deltaij = (pow(m_Ds,2)*(mS*X22 + mCmC*Y22)*std::conj(Z22))/(pow(mHp,2)*(mS + mCmC)*Vcs);
      std::complex<double> Deltamutau = (pow(m_Ds,2)*(mS*X22 + mCmC*Y22)*std::conj(Z23))/(pow(mHp,2)*(mS + mCmC)*Vcs);
      std::complex<double> one = {1,0};
      result = std::real(((pow(one - Deltaij,2)+pow(Deltamutau,2))*pow(f_Ds,2)*pow(sminputs.GF,2)*pow(mMu,2)*pow(1 - pow(mMu,2)/pow(m_Ds,2),2)*m_Ds*life_Ds*pow(Vcs,2))/(8.*hbar*pi));

      if (flav_debug) std::cout << "BR(Ds->mu nu) = " << result << std::endl;
      if (flav_debug) std::cout << "Finished THDM_Dsmunu" << std::endl;
    }

    /// Br D -> mu nu
    void SuperIso_prediction_Dmunu(double &result)
    {
      using namespace Pipes::SuperIso_prediction_Dmunu;
      if (flav_debug) std::cout<<"Starting SuperIso_prediction_Dmunu"<< std::endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result = BEreq::Dmunu(&param);

      if (flav_debug) printf("BR(D->mu nu)=%.3e\n",result);
      if (flav_debug) std::cout<<"Finished SuperIso_prediction_Dmunu"<< std::endl;
    }

    /// Br D->mu nu in the THDM
    void THDM_Dmunu(double &result)
    {
      using namespace Pipes::THDM_Dmunu;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;
      const double m_D = 1.86961;//All values are taken from SuperIso 3.6
      const double f_D = 0.2135;
      const double hbar = 6.582119514e-25;
      const double life_D = 1.040e-12;
      double tanb = spectrum.get(Par::dimensionless,"tanb");
      double mHp = spectrum.get(Par::Pole_Mass,"H+");
      const double v = spectrum.get(Par::mass1, "vev");
      const double lambda = Dep::SMINPUTS->CKM.lambda;
      const double Vcd = -lambda;
      const double Vtd = 8.54e-3;//This should be to be called directly from an Eigen object, for the moment is fine.
      const double mMu = Dep::SMINPUTS->mMu;
      const double mCmC = Dep::SMINPUTS->mCmC;
      std::complex<double> Ytc(spectrum.get(Par::dimensionless,"Yu2",3,2), spectrum.get(Par::dimensionless, "ImYu2",3,2));
      std::complex<double> Ymumu(spectrum.get(Par::dimensionless,"Ye2",2,2), spectrum.get(Par::dimensionless, "ImYe2",2,2));
      std::complex<double> Ymutau(spectrum.get(Par::dimensionless,"Ye2",2,3), spectrum.get(Par::dimensionless, "ImYe2",2,3));
      std::complex<double> Ycc(spectrum.get(Par::dimensionless,"Yu2",2,2), spectrum.get(Par::dimensionless, "ImYu2",2,2));
      std::complex<double> Y21 = -((v*(Vcd*(-((sqrt(2)*mCmC*tanb)/v) + sqrt(1 + pow(tanb,2))*Ycc) + sqrt(1 + pow(tanb,2))*Vtd*Ytc))/(sqrt(2)*mCmC));
      std::complex<double> Z22 = (v*(-((sqrt(2)*mMu*tanb)/v) + sqrt(1 + pow(tanb,2))*Ymumu))/(sqrt(2)*mMu);
      std::complex<double> Z23 = (sqrt(1 + pow(tanb,2))*v*Ymutau)/(sqrt(2)*mMu);
      std::complex<double> Deltaij = (pow(m_D,2)*Y21*(Z22))/(pow(mHp,2)*Vcd);
      std::complex<double> Deltamutau = (pow(m_D,2)*Y21*(Z23))/(pow(mHp,2)*Vcd);
      std::complex<double> one = {1,0};
      result =  std::real(((pow(one - Deltaij,2)+pow(Deltamutau,2))*pow(f_D,2)*pow(sminputs.GF,2)*pow(mMu,2)*pow(1 - pow(mMu,2)/pow(m_D,2),2)*m_D*life_D*pow(Vcd,2))/(8.*hbar*pi));

      if (flav_debug) std::cout << "BR(D->mu nu) = " << result << std::endl;
      if (flav_debug) std::cout << "Finished THDM_Dmunu" << std::endl;
    }

    /// Br D -> tau nu
    void SuperIso_prediction_Dtaunu(double &result)
    {
      using namespace Pipes::SuperIso_prediction_Dtaunu;
      if (flav_debug) std::cout<<"Starting SuperIso_prediction_Dtaunu"<< std::endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result = BEreq::Dlnu(byVal(3),&param);

      if (flav_debug) printf("BR(D->tau nu)=%.3e\n",result);
      if (flav_debug) std::cout<<"Finished SuperIso_prediction_Dtaunu"<< std::endl;
    }

    /// Br D->tau nu in the THDM
    void THDM_Dtaunu(double &result)
    {
      using namespace Pipes::THDM_Dtaunu;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;
      const double m_D = 1.86961;//All values are taken from SuperIso 3.6
      const double f_D = 0.2135;
      const double hbar = 6.582119514e-25;
      const double life_D = 1.040e-12;
      double tanb = spectrum.get(Par::dimensionless,"tanb");
      double mHp = spectrum.get(Par::Pole_Mass,"H+");
      const double v = spectrum.get(Par::mass1, "vev");
      const double lambda = Dep::SMINPUTS->CKM.lambda;
      const double Vcd = -lambda;
      const double Vtd = 8.54e-3;//This should be to be called directly from an Eigen object, for the moment is fine.
      const double mTau = Dep::SMINPUTS->mTau;
      const double mCmC = Dep::SMINPUTS->mCmC;
      std::complex<double> Ytc(spectrum.get(Par::dimensionless,"Yu2",3,2), spectrum.get(Par::dimensionless, "ImYu2",3,2));
      std::complex<double> Ytautau(spectrum.get(Par::dimensionless,"Ye2",3,3), spectrum.get(Par::dimensionless, "ImYe2",3,3));
      std::complex<double> Ymutau(spectrum.get(Par::dimensionless,"Ye2",2,3), spectrum.get(Par::dimensionless, "ImYe2",2,3));
      std::complex<double> Ycc(spectrum.get(Par::dimensionless,"Yu2",2,2), spectrum.get(Par::dimensionless, "ImYu2",2,2));
      std::complex<double> Y21 = -((v*(Vcd*(-((sqrt(2)*mCmC*tanb)/v) + sqrt(1 + pow(tanb,2))*Ycc) + sqrt(1 + pow(tanb,2))*Vtd*Ytc))/(sqrt(2)*mCmC));
      std::complex<double> Z33 = (v*(-((sqrt(2)*mTau*tanb)/v) + sqrt(1 + pow(tanb,2))*Ytautau))/(sqrt(2)*mTau);
      std::complex<double> Z23 = (sqrt(1 + pow(tanb,2))*v*Ymutau)/(sqrt(2)*mTau);
      std::complex<double> Deltaij = (pow(m_D,2)*Y21*(Z33))/(pow(mHp,2)*Vcd);
      std::complex<double> Deltamutau = (pow(m_D,2)*Y21*(Z23))/(pow(mHp,2)*Vcd);
      std::complex<double> one = {1,0};
      result = std::real(((pow(one - Deltaij,2)+pow(Deltamutau,2))*pow(f_D,2)*pow(sminputs.GF,2)*pow(mTau,2)*pow(1 - pow(mTau,2)/pow(m_D,2),2)*m_D*life_D*pow(Vcd,2))/(8.*hbar*pi));

      if (flav_debug) std::cout << "BR(D->tau nu) = " << result << std::endl;
      if (flav_debug) std::cout << "Finished THDM_Dtaunu" << std::endl;
    }

    /// Br B -> D tau nu
    /// TODO: This does not work well with WCs, fix
    void SuperIso_prediction_BDtaunu(double &result)
    {
      using namespace Pipes::SuperIso_prediction_BDtaunu;
      if (flav_debug) std::cout<<"Starting SuperIso_prediction_BDtaunu"<< std::endl;

      parameters const& param = *Dep::SuperIso_modelinfo;

      double q2_min_tau_D  = 3.16; // 1.776**2
      double q2_max_tau_D  = 11.6;   // (5.28-1.869)**2
      int gen_tau_D        = 3;
      int charge_tau_D     = 0;// D* is the charged version
      double obs_tau_D[3];

      result=BEreq::BRBDlnu(byVal(gen_tau_D), byVal( charge_tau_D), byVal(q2_min_tau_D), byVal(q2_max_tau_D), byVal(obs_tau_D), &param);

      if (flav_debug) printf("BR(B-> D tau nu )=%.3e\n",result);
      if (flav_debug) std::cout<<"Finished SuperIso_prediction_BDtaunu"<< std::endl;
    }

    // Auxiliary function for BR(B->Dlnu),1st generation is not supported
    void THDM_Gamma_BDlnu(SMInputs sminputs, Spectrum spectrum, int gen, double &result)
    {
      const double A      = sminputs.CKM.A;
      const double lambda = sminputs.CKM.lambda;
      const double Vcs = 1 - (1/2)*lambda*lambda;
      const double Vcb = A*lambda*lambda;
      const double Vtb = 1 - (1/2)*A*A*pow(lambda,4);
      const double CSMcb = 4*sminputs.GF*Vcb/(sqrt(2.0));
      double tanb = spectrum.get(Par::dimensionless,"tanb");
      double beta = atan(tanb);
      double cosb = cos(beta);
      const double v = spectrum.get(Par::mass1, "vev");
      const double mTau = sminputs.mTau;
      const double mMu  = sminputs.mMu;
      const double mBmB = sminputs.mBmB;
      const double mCmC = sminputs.mCmC;
      double mHp = spectrum.get(Par::Pole_Mass,"H+");
      std::complex<double> Ymutau(spectrum.get(Par::dimensionless,"Ye2",2,3), spectrum.get(Par::dimensionless, "ImYe2",2,3));
      std::complex<double> Ymumu(spectrum.get(Par::dimensionless,"Ye2",2,2), spectrum.get(Par::dimensionless, "ImYe2",2,2));
      std::complex<double> Ytautau(spectrum.get(Par::dimensionless,"Ye2",3,3), spectrum.get(Par::dimensionless, "ImYe2",3,3));
      std::complex<double> Ytc(spectrum.get(Par::dimensionless,"Yu2",3,2), spectrum.get(Par::dimensionless, "ImYu2",3,2));
      std::complex<double> Ybb(spectrum.get(Par::dimensionless,"Yd2",3,3), spectrum.get(Par::dimensionless, "ImYd2",3,3));
      std::complex<double> Ysb(spectrum.get(Par::dimensionless,"Yd2",2,3), spectrum.get(Par::dimensionless, "ImYd2",2,3));
      std::complex<double> xitc = Ytc/cosb;
      std::complex<double> xibb = -((sqrt(2)*mBmB*tanb)/v) + Ybb/cosb;
      std::complex<double> xisb = Ysb/cosb;
      std::complex<double> xitautau = -((sqrt(2)*mTau*tanb)/v) + Ytautau/cosb;
      std::complex<double> ximumu = -((sqrt(2)*mMu*tanb)/v) + Ymumu/cosb;
      std::complex<double> ximutau = Ymutau/cosb;
      std::complex<double> Ycc(spectrum.get(Par::dimensionless,"Yu2",2,2), spectrum.get(Par::dimensionless, "ImYu2",2,2));
      std::complex<double> xicc = -((sqrt(2)*mCmC*tanb)/v) + Ycc/cosb;
      std::complex<double> CRcb(0,0);
      std::complex<double> CLcb(0,0);
      if (gen==3)
      {
      CRcb = -(Vcb*xibb+Vcs*xisb)*std::conj(xitautau)/pow(mHp,2);
      CLcb = (Vcb*std::conj(xicc)+Vtb*std::conj(xitc))*std::conj(xitautau)/pow(mHp,2);
      }
      else if (gen==2)
      {
      CRcb = -(Vcb*xibb+Vcs*xisb)*std::conj(ximumu)/pow(mHp,2);
      CLcb = (Vcb*std::conj(xicc)+Vtb*std::conj(xitc))*std::conj(ximumu)/pow(mHp,2);
      }
      std::complex<double> CRcbmutau = -(Vcb*xibb+Vcs*xisb)*std::conj(ximutau)/pow(mHp,2);
      std::complex<double> CLcbmutau = (Vcb*std::conj(xicc)+Vtb*std::conj(xitc))*std::conj(ximutau)/pow(mHp,2);
      std::complex<double> gs = 1.5*(CRcb + CLcb)/CSMcb;
      std::complex<double> gsmutau = 1.5*(CRcbmutau + CLcbmutau)/CSMcb;

      double Gamma = Gamma_BDlnu(gs, gsmutau, gen, 13);

      result = Gamma;

    }

    ///  BR(B->Dtanu) in the THDM
    void THDM_BDtaunu(double &result)
    {
      using namespace Pipes::THDM_BDtaunu;

      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      THDM_Gamma_BDlnu(sminputs, spectrum, 3, result);
    }

    /// Br B -> D mu nu
    /// TODO: This does not work well with WCs, fix
    void SuperIso_prediction_BDmunu(double &result)
    {
      using namespace Pipes::SuperIso_prediction_BDmunu;
      if (flav_debug) std::cout<<"Starting SuperIso_prediction_BDmunu"<< std::endl;

      parameters const& param = *Dep::SuperIso_modelinfo;

      double q2_min_mu_D=  0.012; // 0.105*0.105
      double q2_max_mu_D=  11.6;   // (5.28-1.869)**2
      int gen_mu_D        =2;
      int charge_mu_D     =0;// D* is the charged version
      double obs_mu_D[3];

      result= BEreq::BRBDlnu(byVal(gen_mu_D), byVal( charge_mu_D), byVal(q2_min_mu_D), byVal(q2_max_mu_D), byVal(obs_mu_D), &param);

      if (flav_debug) printf("BR(B->D mu nu)=%.3e\n",result);
      if (flav_debug) std::cout<<"Finished SuperIso_prediction_BDmunu"<< std::endl;
    }

    /// BR B -> D mu nu
    void THDM_BDmunu(double &result)
    {
      using namespace Pipes::THDM_BDmunu;

      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      THDM_Gamma_BDlnu(sminputs, spectrum, 2, result);
    }

    /// Br B -> D* tau nu
    /// TODO: This does not work well with WCs, fix
    void SuperIso_prediction_BDstartaunu(double &result)
    {
      using namespace Pipes::SuperIso_prediction_BDstartaunu;
      if (flav_debug) std::cout<<"Starting SuperIso_prediction_BDstartaunu"<< std::endl;

      parameters const& param = *Dep::SuperIso_modelinfo;

      double q2_min_tau_Dstar = 3.16; // 1.776**2
      double q2_max_tau_Dstar = 10.67;   //(5.279-2.01027)*(5.279-2.01027);
      int gen_tau_Dstar        =3;
      int charge_tau_Dstar     =1;// D* is the charged version
      double obs_tau_Dstar[4];

      result= BEreq::BRBDstarlnu(byVal(gen_tau_Dstar), byVal( charge_tau_Dstar), byVal(q2_min_tau_Dstar), byVal(q2_max_tau_Dstar), byVal(obs_tau_Dstar), &param);

      if (flav_debug) printf("BR(B->Dstar tau nu)=%.3e\n",result);
      if (flav_debug) std::cout<<"Finished SuperIso_prediction_BDstartaunu"<< std::endl;
    }

    // Auxiliary function for BR(B->Dstarlnu),1st generation is not supported
    void THDM_Gamma_BDstarlnu(SMInputs sminputs, Spectrum spectrum, int gen, double &result)
    {
      const double A      = sminputs.CKM.A;
      const double lambda = sminputs.CKM.lambda;
      const double Vcs = 1 - (1/2)*lambda*lambda;
      const double Vcb = A*lambda*lambda;
      const double Vtb = 1 - (1/2)*A*A*pow(lambda,4);
      const double CSMcb = 4*sminputs.GF*Vcb/(sqrt(2.0));
      double tanb = spectrum.get(Par::dimensionless,"tanb");
      double beta = atan(tanb);
      double cosb = cos(beta);
      const double v = spectrum.get(Par::mass1, "vev");
      const double mTau = sminputs.mTau;
      const double mMu  = sminputs.mMu;
      const double mBmB = sminputs.mBmB;
      const double mCmC = sminputs.mCmC;
      double mHp = spectrum.get(Par::Pole_Mass,"H+");
      std::complex<double> Ymutau(spectrum.get(Par::dimensionless,"Ye2",2,3), spectrum.get(Par::dimensionless, "ImYe2",2,3));
      std::complex<double> Ymumu(spectrum.get(Par::dimensionless,"Ye2",2,2), spectrum.get(Par::dimensionless, "ImYe2",2,2));
      std::complex<double> Ytautau(spectrum.get(Par::dimensionless,"Ye2",3,3), spectrum.get(Par::dimensionless, "ImYe2",3,3));
      std::complex<double> Ytc(spectrum.get(Par::dimensionless,"Yu2",3,2), spectrum.get(Par::dimensionless, "ImYu2",3,2));
      std::complex<double> Ybb(spectrum.get(Par::dimensionless,"Yd2",3,3), spectrum.get(Par::dimensionless, "ImYd2",3,3));
      std::complex<double> Ysb(spectrum.get(Par::dimensionless,"Yd2",2,3), spectrum.get(Par::dimensionless, "ImYd2",2,3));
      std::complex<double> xitc = Ytc/cosb;
      std::complex<double> xibb = -((sqrt(2)*mBmB*tanb)/v) + Ybb/cosb;
      std::complex<double> xisb = Ysb/cosb;
      std::complex<double> xitautau = -((sqrt(2)*mTau*tanb)/v) + Ytautau/cosb;
      std::complex<double> ximumu = -((sqrt(2)*mMu*tanb)/v) + Ymumu/cosb;
      std::complex<double> ximutau = Ymutau/cosb;
      std::complex<double> Ycc(spectrum.get(Par::dimensionless,"Yu2",2,2), spectrum.get(Par::dimensionless, "ImYu2",2,2));
      std::complex<double> xicc = -((sqrt(2)*mCmC*tanb)/v) + Ycc/cosb;
      std::complex<double> CRcb(0,0);
      std::complex<double> CLcb(0,0);
      if (gen==3)
      {
      CRcb = -(Vcb*xibb+Vcs*xisb)*std::conj(xitautau)/pow(mHp,2);
      CLcb = (Vcb*std::conj(xicc)+Vtb*std::conj(xitc))*std::conj(xitautau)/pow(mHp,2);
      }
      else if (gen==2)
      {
      CRcb = -(Vcb*xibb+Vcs*xisb)*std::conj(ximumu)/pow(mHp,2);
      CLcb = (Vcb*std::conj(xicc)+Vtb*std::conj(xitc))*std::conj(ximumu)/pow(mHp,2);
      }
      std::complex<double> CRcbmutau = -(Vcb*xibb+Vcs*xisb)*std::conj(ximutau)/pow(mHp,2);
      std::complex<double> CLcbmutau = (Vcb*std::conj(xicc)+Vtb*std::conj(xitc))*std::conj(ximutau)/pow(mHp,2);
      std::complex<double> gp = 1.5*(CRcb - CLcb)/CSMcb;
      std::complex<double> gpmutau = 1.5*(CRcbmutau - CLcbmutau)/CSMcb;

      double Gamma = Gamma_BDstarlnu(gp, gpmutau, gen, 15);

      result = Gamma;

    }

    /// BR B -> D* tau nu
    void THDM_BDstartaunu(double &result)
    {
      using namespace Pipes::THDM_BDstartaunu;

      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      THDM_Gamma_BDstarlnu(sminputs, spectrum, 3, result);
    }

    /// Br B -> D* mu nu
    /// TODO: This does not work well with WCs, fix
    void SuperIso_prediction_BDstarmunu(double &result)
    {
      using namespace Pipes::SuperIso_prediction_BDstarmunu;
      if (flav_debug) std::cout<<"Starting SuperIso_prediction_BDstarmunu"<< std::endl;

      parameters const& param = *Dep::SuperIso_modelinfo;

      double q2_min_mu_Dstar = 0.012; // 0.105*0.105
      double q2_max_mu_Dstar = 10.67;   //(5.279-2.01027)*(5.279-2.01027);
      int gen_mu_Dstar        =2;
      int charge_mu_Dstar     =1;// D* is the charged version
      double obs_mu_Dstar[4];

      result=BEreq::BRBDstarlnu(byVal(gen_mu_Dstar), byVal( charge_mu_Dstar), byVal(q2_min_mu_Dstar), byVal(q2_max_mu_Dstar), byVal(obs_mu_Dstar), &param);

      if (flav_debug) printf("BR(B->Dstar mu nu)=%.3e\n",result);
      if (flav_debug) std::cout<<"Finished SuperIso_prediction_BDstarmunu"<< std::endl;
    }

    /// BR B -> D* mu nu
    void THDM_BDstarmunu(double &result)
    {
      using namespace Pipes::THDM_BDstarmunu;

      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      THDM_Gamma_BDstarlnu(sminputs, spectrum, 2, result);
    }


    /// SuperIso prediction for RD and RD*
    //SI_MULTI_PREDICTION_FUNCTION(RDRDstar)  // TODO: Typical subcaps: RD, RDstar

    ///  B-> D tau nu / B-> D e nu decays
    /// TODO: This does not work well with WCs, fix
    void SuperIso_prediction_RD(double &result)
    {
      using namespace Pipes::SuperIso_prediction_RD;
      if (flav_debug) std::cout<<"Starting SuperIso_prediction_RD"<< std::endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result = BEreq::BDtaunu_BDenu(&param);

      if (flav_debug) printf("BR(B->D tau nu)/BR(B->D e nu)=%.3e\n",result);
      if (flav_debug) std::cout<<"Finished SuperIso_prediction_RD"<< std::endl;
    }

    ///  B-> D tau nu / B-> D mu nu decays in THDM
    void THDM_RD(double &result)
    {
      using namespace Pipes::THDM_RD;
      if (flav_debug) std::cout<<"Starting THDM_RD"<< std::endl;

      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      const double lambda = Dep::SMINPUTS->CKM.lambda;
      const double A = Dep::SMINPUTS->CKM.A;
      const double Vcs = 1 - (1/2)*lambda*lambda;
      const double Vcb = A*lambda*lambda;
      const double Vtb = 1 - (1/2)*A*A*pow(lambda,4);
      double tanb = spectrum.get(Par::dimensionless,"tanb");
      double beta = atan(tanb);
      double cosb = cos(beta);
      const double v = spectrum.get(Par::mass1, "vev");
      const double CSMcb = 4*sminputs.GF*Vcb/sqrt(2.0);
      const double mMu = Dep::SMINPUTS->mMu;
      const double mTau = Dep::SMINPUTS->mTau;
      const double mBmB = Dep::SMINPUTS->mBmB;
      double mHp = spectrum.get(Par::Pole_Mass,"H+");
      std::complex<double> Yetau(spectrum.get(Par::dimensionless,"Ye2",1,3), spectrum.get(Par::dimensionless, "ImYe2",1,3));
      std::complex<double> Ymumu(spectrum.get(Par::dimensionless,"Ye2",2,2), spectrum.get(Par::dimensionless, "ImYe2",2,2));
      std::complex<double> Ymutau(spectrum.get(Par::dimensionless,"Ye2",2,3), spectrum.get(Par::dimensionless, "ImYe2",2,3));
      std::complex<double> Ytautau(spectrum.get(Par::dimensionless,"Ye2",3,3), spectrum.get(Par::dimensionless, "ImYe2",3,3));
      std::complex<double> Ytc(spectrum.get(Par::dimensionless,"Yu2",3,2), spectrum.get(Par::dimensionless, "ImYu2",3,2));
      std::complex<double> Ybb(spectrum.get(Par::dimensionless,"Yd2",3,3), spectrum.get(Par::dimensionless, "ImYd2",3,3));
      std::complex<double> Ysb(spectrum.get(Par::dimensionless,"Yd2",2,3), spectrum.get(Par::dimensionless, "ImYd2",2,3));
      std::complex<double> xitc = Ytc/cosb;
      std::complex<double> xibb = -((sqrt(2)*mBmB*tanb)/v) + Ybb/cosb;
      std::complex<double> xisb = Ysb/cosb;
      std::complex<double> xitautau = -((sqrt(2)*mTau*tanb)/v) + Ytautau/cosb;
      std::complex<double> ximumu = -((sqrt(2)*mMu*tanb)/v) + Ymumu/cosb;
      std::complex<double> ximutau = Ymutau/cosb;
      std::complex<double> xietau = Yetau/cosb;
      const double mCmC = Dep::SMINPUTS->mCmC;
      std::complex<double> Ycc(spectrum.get(Par::dimensionless,"Yu2",2,2), spectrum.get(Par::dimensionless, "ImYu2",2,2));
      std::complex<double> xicc = -((sqrt(2)*mCmC*tanb)/v) + Ycc/cosb;
      std::complex<double> CRcb = -(Vcb*xibb+Vcs*xisb)*std::conj(xitautau)/pow(mHp,2);
      std::complex<double> CLcb = (Vcb*std::conj(xicc)+Vtb*std::conj(xitc))*std::conj(xitautau)/pow(mHp,2);
      std::complex<double> CRcbmumu = -(Vcb*xibb+Vcs*xisb)*std::conj(ximumu)/pow(mHp,2);
      std::complex<double> CLcbmumu = (Vcb*std::conj(xicc)+Vtb*std::conj(xitc))*std::conj(ximumu)/pow(mHp,2);
      std::complex<double> CRcbmutau = -(Vcb*xibb+Vcs*xisb)*std::conj(ximutau)/pow(mHp,2);
      std::complex<double> CLcbmutau = (Vcb*std::conj(xicc)+Vtb*std::conj(xitc))*std::conj(ximutau)/pow(mHp,2);
      std::complex<double> CRcbetau = -(Vcb*xibb+Vcs*xisb)*conj(xietau)/pow(mHp,2);
      std::complex<double> CLcbetau = (Vcb*conj(xicc)+Vtb*conj(xitc))*conj(xietau)/pow(mHp,2);
      std::complex<double> gs = 1.5*(CRcb+CLcb)/CSMcb;//The 1.5 factor comes from RG effects
      std::complex<double> gsmumu =  1.5*(CRcbmumu+CLcbmumu)/CSMcb;
      std::complex<double> gsmutau =  1.5*(CRcbmutau+CLcbmutau)/CSMcb;
      std::complex<double> gsetau =  1.5*(CRcbetau+CLcbetau)/CSMcb;
      //Expression calculated using form factors and definitions from SuperIso
      result = (1+1.725*std::real(gs)+1.355*(std::norm(gs)+std::norm(gsmutau)+std::norm(gsetau)))/(3.271+0.57*(std::real(gsmumu))+4.795*(std::norm(gsmumu)));
      //result = (1+1.725*std::real(gs+gsmutau+gsetau)+1.355*(std::norm(gs)+std::norm(gsmutau)+std::norm(gsetau)))/(3.271+0.57*(std::real(gsmumu+gsmutau))+4.795*(std::norm(gsmumu)+std::norm(gsmutau)));
      if (flav_debug) printf("BR(B->D tau nu)/BR(B->D mu nu)=%.3e\n",result);
      if (flav_debug) std::cout<<"Finished THDM_RD"<< std::endl;
    }

    ///  B->D* tau nu / B-> D* e nu decays
    /// TODO: This does not work well with WCs, fix
    void SuperIso_prediction_RDstar(double &result)
    {
      using namespace Pipes::SuperIso_prediction_RDstar;
      if (flav_debug) std::cout<<"Starting SuperIso_prediction_RDstar"<< std::endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result = BEreq::BDstartaunu_BDstarenu(&param);

      if (flav_debug) printf("BR(B->D* tau nu)/BR(B->D* e nu)=%.3e\n",result);
      if (flav_debug) std::cout<<"Finished SuperIso_prediction_RD*"<< std::endl;
    }

    ///  B->D* tau nu / B-> D* mu nu decays in THDM
    void THDM_RDstar(double &result)
    {
      using namespace Pipes::THDM_RDstar;
      if (flav_debug) std::cout<<"Starting THDM_RDstar"<< std::endl;

      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      const double lambda = Dep::SMINPUTS->CKM.lambda;
      const double A = Dep::SMINPUTS->CKM.A;
      const double Vcs = 1 - (1/2)*lambda*lambda;
      const double Vcb = A*lambda*lambda;
      const double Vtb = 1 - (1/2)*A*A*pow(lambda,4);
      double tanb = spectrum.get(Par::dimensionless,"tanb");
      double beta = atan(tanb);
      double cosb = cos(beta);
      const double v = spectrum.get(Par::mass1, "vev");
      const double CSMcb = 4*sminputs.GF*Vcb/sqrt(2.0);
      const double mMu = Dep::SMINPUTS->mMu;
      const double mTau = Dep::SMINPUTS->mTau;
      const double mBmB = Dep::SMINPUTS->mBmB;
      double mHp = spectrum.get(Par::Pole_Mass,"H+");
      std::complex<double> Yetau(spectrum.get(Par::dimensionless,"Ye2",1,3), spectrum.get(Par::dimensionless, "ImYe2",1,3));
      std::complex<double> Ymumu(spectrum.get(Par::dimensionless,"Ye2",2,2), spectrum.get(Par::dimensionless, "ImYe2",2,2));
      std::complex<double> Ymutau(spectrum.get(Par::dimensionless,"Ye2",2,3), spectrum.get(Par::dimensionless, "ImYe2",2,3));
      std::complex<double> Ytautau(spectrum.get(Par::dimensionless,"Ye2",3,3), spectrum.get(Par::dimensionless, "ImYe2",3,3));
      std::complex<double> Ytc(spectrum.get(Par::dimensionless,"Yu2",3,2), spectrum.get(Par::dimensionless, "ImYu2",3,2));
      std::complex<double> Ybb(spectrum.get(Par::dimensionless,"Yd2",3,3), spectrum.get(Par::dimensionless, "ImYd2",3,3));
      std::complex<double> Ysb(spectrum.get(Par::dimensionless,"Yd2",2,3), spectrum.get(Par::dimensionless, "ImYd2",2,3));
      std::complex<double> xitc = Ytc/cosb;
      std::complex<double> xibb = -((sqrt(2)*mBmB*tanb)/v) + Ybb/cosb;
      std::complex<double> xisb = Ysb/cosb;
      std::complex<double> xitautau = -((sqrt(2)*mTau*tanb)/v) + Ytautau/cosb;
      std::complex<double> ximumu = -((sqrt(2)*mMu*tanb)/v) + Ymumu/cosb;
      std::complex<double> ximutau = Ymutau/cosb;
      std::complex<double> xietau = Yetau/cosb;
      const double mCmC = Dep::SMINPUTS->mCmC;
      std::complex<double> Ycc(spectrum.get(Par::dimensionless,"Yu2",2,2), spectrum.get(Par::dimensionless, "ImYu2",2,2));
      std::complex<double> xicc = -((sqrt(2)*mCmC*tanb)/v) + Ycc/cosb;
      std::complex<double> CRcb = -(Vcb*xibb+Vcs*xisb)*std::conj(xitautau)/pow(mHp,2);
      std::complex<double> CLcb = (Vcb*std::conj(xicc)+Vtb*std::conj(xitc))*std::conj(xitautau)/pow(mHp,2);
      std::complex<double> CRcbmumu = -(Vcb*xibb+Vcs*xisb)*std::conj(ximumu)/pow(mHp,2);
      std::complex<double> CLcbmumu = (Vcb*std::conj(xicc)+Vtb*std::conj(xitc))*std::conj(ximumu)/pow(mHp,2);
      std::complex<double> CRcbmutau = -(Vcb*xibb+Vcs*xisb)*std::conj(ximutau)/pow(mHp,2);
      std::complex<double> CLcbmutau = (Vcb*std::conj(xicc)+Vtb*std::conj(xitc))*std::conj(ximutau)/pow(mHp,2);
      std::complex<double> CRcbetau = -(Vcb*xibb+Vcs*xisb)*std::conj(xietau)/pow(mHp,2);
      std::complex<double> CLcbetau = (Vcb*std::conj(xicc)+Vtb*std::conj(xitc))*std::conj(xietau)/pow(mHp,2);
      std::complex<double> gp =  1.5*(CRcb - CLcb)/CSMcb;
      std::complex<double> gpmumu =  1.5*(CRcbmumu - CLcbmumu)/CSMcb;
      std::complex<double> gpmutau = 1.5*(CRcbmutau - CLcbmutau)/CSMcb;
      std::complex<double> gpetau = 1.5*(CRcbetau - CLcbetau)/CSMcb;
      result = (1+0.11*std::real(gp)+0.04*(std::norm(gp)+std::norm(gpmutau)+std::norm(gpetau)))/(3.89+0.082*(std::real(gpmumu))+0.25*(std::norm(gpmumu)));
      //result = (1+0.11*std::real(gp+gpmutau+gpetau)+0.04*(std::norm(gp)+std::norm(gpmutau)+std::norm(gpetau)))/(3.89+0.082*(std::real(gpmumu+gpmutau))+0.25*(std::norm(gpmumu)+std::norm(gpmutau)));
      if (flav_debug) printf("BR(B->D* tau nu)/BR(B->D* mu nu)=%.3e\n",result);
      if (flav_debug) std::cout<<"Finished THDM_RDstar"<< std::endl;
    }

    /// B -> D e nu / B -> D mu nu
    /// TODO: This does not work well with WCs, fix
    void SuperIso_prediction_RDemu(double &result)
    {
      using namespace Pipes::SuperIso_prediction_RDemu;
      if (flav_debug) std::cout<<"Starting SuperIso_prediction_RDemu"<< std::endl;

      parameters const& param = *Dep::SuperIso_modelinfo;

      double q2_min_mu_D=  0.012; // 0.105*0.105
      double q2_min_e_D = 0.261; // 0.511**2
      double q2_max_D  = 11.6;   // (5.28-1.869)**2
      int gen_e_D = 1, gen_mu_D = 2;
      int charge_D  = 0;// D* is the charged version
      double obs_mu_D[3], obs_e_D[3];

      result=BEreq::BRBDlnu(byVal(gen_e_D), byVal( charge_D), byVal(q2_min_e_D), byVal(q2_max_D), byVal(obs_e_D), &param) /
             BEreq::BRBDlnu(byVal(gen_mu_D), byVal( charge_D), byVal(q2_min_mu_D), byVal(q2_max_D), byVal(obs_mu_D), &param);

      if (flav_debug) printf("BR(B->D e nu)/BR(B->D mu nu)=%.3e\n",result);
      if (flav_debug) std::cout<<"Finished SuperIso_prediction_RDemu"<< std::endl;
    }

    ///  B-> D e nu / B-> D mu nu decays in THDM
    void THDM_RDemu(double &result)
    {
      using namespace Pipes::THDM_RDemu;
      if (flav_debug) std::cout<<"Starting THDM_RDemu"<< std::endl;

      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      const double lambda = Dep::SMINPUTS->CKM.lambda;
      const double A = Dep::SMINPUTS->CKM.A;
      const double Vcs = 1 - (1/2)*lambda*lambda;
      const double Vcb = A*lambda*lambda;
      const double Vtb = 1 - (1/2)*A*A*pow(lambda,4);
      double tanb = spectrum.get(Par::dimensionless,"tanb");
      double beta = atan(tanb);
      double cosb = cos(beta);
      const double v = spectrum.get(Par::mass1, "vev");
      const double CSMcb = 4*sminputs.GF*Vcb/sqrt(2.0);
      const double mMu = Dep::SMINPUTS->mMu;
      const double mBmB = Dep::SMINPUTS->mBmB;
      double mHp = spectrum.get(Par::Pole_Mass,"H+");
      std::complex<double> Ymumu(spectrum.get(Par::dimensionless,"Ye2",2,2), spectrum.get(Par::dimensionless, "ImYe2",2,2));
      std::complex<double> Ytc(spectrum.get(Par::dimensionless,"Yu2",3,2), spectrum.get(Par::dimensionless, "ImYu2",3,2));
      std::complex<double> Ybb(spectrum.get(Par::dimensionless,"Yd2",3,3), spectrum.get(Par::dimensionless, "ImYd2",3,3));
      std::complex<double> Ysb(spectrum.get(Par::dimensionless,"Yd2",2,3), spectrum.get(Par::dimensionless, "ImYd2",2,3));
      std::complex<double> xitc = Ytc/cosb;
      std::complex<double> xibb = -((sqrt(2)*mBmB*tanb)/v) + Ybb/cosb;
      std::complex<double> xisb = Ysb/cosb;
      std::complex<double> ximumu = -((sqrt(2)*mMu*tanb)/v) + Ymumu/cosb;
      const double mCmC = Dep::SMINPUTS->mCmC;
      std::complex<double> Ycc(spectrum.get(Par::dimensionless,"Yu2",2,2), spectrum.get(Par::dimensionless, "ImYu2",2,2));
      std::complex<double> xicc = -((sqrt(2)*mCmC*tanb)/v) + Ycc/cosb;
      std::complex<double> CRcbmumu = -(Vcb*xibb+Vcs*xisb)*std::conj(ximumu)/pow(mHp,2);
      std::complex<double> CLcbmumu = (Vcb*std::conj(xicc)+Vtb*std::conj(xitc))*std::conj(ximumu)/pow(mHp,2);
      std::complex<double> gsmumu = 1.5*(CRcbmumu + CLcbmumu)/CSMcb;

      result = 1/(0.9964+0.175*std::real(gsmumu)+1.46*(std::norm(gsmumu)));
     // result = 1/(0.9964+0.175*std::real(gsemu+gsmumu+gstaumu)+1.46*(std::norm(gsemu)+std::norm(gsmumu)+std::norm(gstaumu)));

      if (flav_debug) printf("BR(B->D e nu)/BR(B->D mu nu)=%.3e\n",result);
      if (flav_debug) std::cout<<"Finished THDM_RDemu"<< std::endl;
    }

    /// B->K mu nu / B-> pi mu nu
    void SuperIso_prediction_Rmu(double &result)
    {
      using namespace Pipes::SuperIso_prediction_Rmu;
      if (flav_debug) std::cout<<"Starting SuperIso_prediction_Rmu"<< std::endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result = BEreq::Kmunu_pimunu(&param);

      if (flav_debug) printf("R_mu=BR(K->mu nu)/BR(pi->mu nu)=%.3e\n",result);
      if (flav_debug) std::cout<<"Finished SuperIso_prediction_Rmu"<< std::endl;
    }

    /// BR(K->mu nu) /BR pi-> mu nu) in the THDM
    void THDM_Rmu(double &result)
    {
      using namespace Pipes::THDM_Rmu;
      if (flav_debug) std::cout<<"Starting THDM_Rmu"<< std::endl;
      Spectrum spectrum = *Dep::THDM_spectrum;
      const double delta_em = -0.0070;//All values taken from SuperIso 3.6
      const double m_pi = 0.13957;
      const double m_K = 0.493677;
      const double fK_fpi = 1.193;
      const double life_pi=2.6033e-8;
      const double life_K=1.2380e-8;
      double tanb = spectrum.get(Par::dimensionless,"tanb");
      double mHp = spectrum.get(Par::Pole_Mass,"H+");
      const double v = spectrum.get(Par::mass1, "vev");
      const double lambda = Dep::SMINPUTS->CKM.lambda;
      const double Vud = 1. - 0.5*pow(lambda,2);
      const double Vus = lambda;
      double Vub = 3.55e-3;//From superiso 3.6 manual
      const double mMu = Dep::SMINPUTS->mMu;
      const double mS = Dep::SMINPUTS->mS;
      std::complex<double> Ysb(spectrum.get(Par::dimensionless,"Yd2",2,3), spectrum.get(Par::dimensionless, "ImYd2",2,3));
      std::complex<double> Ymumu(spectrum.get(Par::dimensionless,"Ye2",2,2), spectrum.get(Par::dimensionless, "ImYe2",2,2));
      std::complex<double> Ymutau(spectrum.get(Par::dimensionless,"Ye2",2,3), spectrum.get(Par::dimensionless, "ImYe2",2,3));
      std::complex<double> Yss(spectrum.get(Par::dimensionless,"Yd2",2,2), spectrum.get(Par::dimensionless, "ImYd2",2,2));
      std::complex<double> X12 = (v*(sqrt(1 + pow(tanb,2))*Vub*Ysb + Vus*(-((sqrt(2)*mS*tanb)/v) + sqrt(1 + pow(tanb,2))*Yss)))/(sqrt(2)*mS);
      std::complex<double> Z22 = (v*(-((sqrt(2)*mMu*tanb)/v) + sqrt(1 + pow(tanb,2))*Ymumu))/(sqrt(2)*mMu);
      std::complex<double> Z23 = (sqrt(1 + pow(tanb,2))*v*Ymutau)/(sqrt(2)*mMu);
      std::complex<double> Deltaij = (pow(m_K,2)*X12*(Z22))/(pow(mHp,2)*Vus);
      std::complex<double> Deltamutau = (pow(m_K,2)*X12*(Z23))/(pow(mHp,2)*Vus);
      std::complex<double> leptonFactor = pow((1 - pow(mMu,2)/pow(m_K,2))/(1 - pow(mMu,2)/pow(m_pi,2)),2);
      std::complex<double> one = {1,0};
      result = std::real((life_K/life_pi)*pow(fK_fpi*Vus/Vud,2)*(m_K/m_pi)*leptonFactor*(1.+delta_em)*(pow(one - Deltaij,2)+pow(Deltamutau,2)));

      if (flav_debug) printf("R_mu=BR(K->mu nu)/BR(pi->mu nu) in THDM =%.3e\n",result);
      if (flav_debug) std::cout<<"Finished THDM_Rmu"<< std::endl;
    }


    /// Measurements for tree-level leptonic and semileptonic B decays
    void SL_measurements(predictions_measurements_covariances &pmc)
    {
      using namespace Pipes::SL_measurements;

      const int n_experiments=11;
      static bool th_err_absolute[n_experiments], first = true;
      static double th_err[n_experiments];

      if (flav_debug) std::cout<<"Starting SL_measurements"<< std::endl;

      // Read and calculate things based on the observed data only the first time through, as none of it depends on the model parameters.
      if (first)
      {
        pmc.LL_name="SL_LogLikelihood";

        // Read in experimental measuremens
        Flav_reader fread(GAMBIT_DIR  "/FlavBit/data");
        fread.debug_mode(flav_debug);
        if (flav_debug) std::cout<<"Initialised Flav reader in SL_measurements"<< std::endl;

        // B-> tau nu
        fread.read_yaml_measurement("flav_data.yaml", "BR_Btaunu");
        // B-> D mu nu
        fread.read_yaml_measurement("flav_data.yaml", "BR_BDmunu");
        // B-> D* mu nu
        fread.read_yaml_measurement("flav_data.yaml", "BR_BDstarmunu");
        // RD
        fread.read_yaml_measurement("flav_data.yaml", "RD");
        // RDstar
        fread.read_yaml_measurement("flav_data.yaml", "RDstar");
        // Ds-> tau nu
        fread.read_yaml_measurement("flav_data.yaml", "BR_Dstaunu");
        // Ds -> mu nu
        fread.read_yaml_measurement("flav_data.yaml", "BR_Dsmunu");
        // D -> mu nu
        fread.read_yaml_measurement("flav_data.yaml", "BR_Dmunu");
        // D -> tau nu
        fread.read_yaml_measurement("flav_data.yaml", "BR_Dtaunu");
         // R_mu
        fread.read_yaml_measurement("flav_data.yaml", "R_mu");
         // RDemu
        fread.read_yaml_measurement("flav_data.yaml", "RDemu");

        fread.initialise_matrices();
        pmc.cov_exp=fread.get_exp_cov();
        pmc.value_exp=fread.get_exp_value();

        pmc.value_th.resize(n_experiments,1);
        // Set all entries in the covariance matrix explicitly to zero, as we will only write the diagonal ones later.
        pmc.cov_th = boost::numeric::ublas::zero_matrix<double>(n_experiments,n_experiments);
        for (int i = 0; i < n_experiments; ++i)
        {
          th_err[i] = fread.get_th_err()(i,0).first;
          th_err_absolute[i] = fread.get_th_err()(i,0).second;
        }

        pmc.dim=n_experiments;

        // Init over.
        first = false;
      }

      pmc.names = {"BDtaunu", "BDmunu", "BDstarmunu", "RD", "RDstar", "Dstaunu", "Dsmunu", "Dmunu", "Dtaunu", "Rmu", "RDemu"};

      // R(D) is calculated assuming isospin symmetry
      double theory[11];
      // B-> tau nu SI
      theory[0] = *Dep::Btaunu;
      // B-> D mu nu
      theory[1] = *Dep::BDmunu;
      // B-> D* mu nu
      theory[2] = *Dep::BDstarmunu;
      // RD
      theory[3] = *Dep::RD;
      // RDstar
      theory[4] = *Dep::RDstar;
      // Ds-> tau nu
      theory[5] = *Dep::Dstaunu;
      // Ds -> mu nu
      theory[6] = *Dep::Dsmunu;
      // D -> mu nu
      theory[7] = *Dep::Dmunu;
      // D -> tau nu
      theory[8] = *Dep::Dtaunu;
      //R_mu
      theory[9] = *Dep::Rmu;
      //RDemu
      theory[10] = *Dep::RDemu;

      // hax (to ignore some of them)
      // theory[0] = pmc.value_exp(0,0); // B-> tau nu SI
      // theory[1] = pmc.value_exp(1,0); // B-> D mu nu
      // theory[2] = pmc.value_exp(2,0); // B-> D* mu nu
      // theory[3] = pmc.value_exp(3,0); // RD
      // theory[4] = pmc.value_exp(4,0); // RDstar
      // theory[5] = pmc.value_exp(5,0); // Ds-> tau nu
      // theory[6] = pmc.value_exp(6,0); // Ds -> mu nu
      // theory[7] = pmc.value_exp(7,0); // D -> mu nu
      // theory[8] = pmc.value_exp(8,0); // D -> tau nu
      // theory[9] = pmc.value_exp(9,0); //R_mu
      // theory[10] = pmc.value_exp(10,0); //RDemu

      for (int i = 0; i < n_experiments; ++i)
      {
        pmc.value_th(i,0) = theory[i];
        pmc.cov_th(i,i) = th_err[i]*th_err[i] * (th_err_absolute[i] ? 1.0 : theory[i]*theory[i]);
      }
      // Add in the correlations between B-> D mu nu and RD
      pmc.cov_th(1,3) = pmc.cov_th(3,1) = -0.55 * th_err[1]*th_err[3] * (th_err_absolute[1] ? 1.0 : theory[1]) * (th_err_absolute[3] ? 1.0 : theory[3]);
      // Add in the correlations between B-> D* mu nu and RD*
      pmc.cov_th(2,4) = pmc.cov_th(4,2) = -0.62 * th_err[2]*th_err[4] * (th_err_absolute[2] ? 1.0 : theory[2]) * (th_err_absolute[4] ? 1.0 : theory[4]);

      pmc.diff.clear();
      for (int i=0;i<n_experiments;++i)
      {
        pmc.diff.push_back(pmc.value_exp(i,0)-pmc.value_th(i,0));
      }

      if (flav_debug) std::cout<<"Finished SL_measurements"<< std::endl;
    }

    /// Auxiliary function for  BR(Bc->taunu) adn Bc lifetime in the THDM
    void THDM_Bc_obs(SMInputs sminputs, Spectrum spectrum, int i, double &result)
    {
      const double lambda = sminputs.CKM.lambda;
      const double A = sminputs.CKM.A;
      const double Vcs = 1 - (1/2)*lambda*lambda;
      const double Vcb = A*lambda*lambda;
      const double Vtb = 1 - (1/2)*A*A*pow(lambda,4);
      double tanb = spectrum.get(Par::dimensionless,"tanb");
      double beta = atan(tanb);
      double cosb = cos(beta);
      const double v = spectrum.get(Par::mass1, "vev");
      const double CSMcb = 4*sminputs.GF*Vcb/sqrt(2.0);
      const double mTau = sminputs.mTau;
      const double mBmB = sminputs.mBmB;
      double mHp = spectrum.get(Par::Pole_Mass,"H+");
      const double hbar = 6.582119514e-25;
      const double mCmC = sminputs.mCmC;
      std::complex<double> Yetau(spectrum.get(Par::dimensionless,"Ye2",1,3), spectrum.get(Par::dimensionless, "ImYe2",1,3));
      std::complex<double> Ymutau(spectrum.get(Par::dimensionless,"Ye2",2,3), spectrum.get(Par::dimensionless, "ImYe2",2,3));
      std::complex<double> Ytautau(spectrum.get(Par::dimensionless,"Ye2",3,3), spectrum.get(Par::dimensionless, "ImYe2",3,3));
      std::complex<double> Ytc(spectrum.get(Par::dimensionless,"Yu2",3,2), spectrum.get(Par::dimensionless, "ImYu2",3,2));
      std::complex<double> Ybb(spectrum.get(Par::dimensionless,"Yd2",3,3), spectrum.get(Par::dimensionless, "ImYd2",3,3));
      std::complex<double> Ysb(spectrum.get(Par::dimensionless,"Yd2",2,3), spectrum.get(Par::dimensionless, "ImYd2",2,3));
      std::complex<double> xitc = Ytc/cosb;
      std::complex<double> xibb = -((sqrt(2)*mBmB*tanb)/v) + Ybb/cosb;
      std::complex<double> xisb = Ysb/cosb;
      std::complex<double> xitautau = -((sqrt(2)*mTau*tanb)/v) + Ytautau/cosb;
      std::complex<double> ximutau = Ymutau/cosb;
      std::complex<double> xietau = Yetau/cosb;
      std::complex<double> Ycc(spectrum.get(Par::dimensionless,"Yu2",2,2), spectrum.get(Par::dimensionless, "ImYu2",2,2));
      std::complex<double> xicc = -((sqrt(2)*mCmC*tanb)/v) + Ycc/cosb;
      std::complex<double> CRcb = -(Vcb*xibb+Vcs*xisb)*conj(xitautau)/pow(mHp,2);
      std::complex<double> CLcb = (Vcb*conj(xicc)+Vtb*conj(xitc))*conj(xitautau)/pow(mHp,2);
      std::complex<double> CRcbmutau = -(Vcb*xibb+Vcs*xisb)*conj(ximutau)/pow(mHp,2);
      std::complex<double> CLcbmutau = (Vcb*conj(xicc)+Vtb*conj(xitc))*conj(ximutau)/pow(mHp,2);
      std::complex<double> CRcbetau = -(Vcb*xibb+Vcs*xisb)*conj(xietau)/pow(mHp,2);
      std::complex<double> CLcbetau = (Vcb*conj(xicc)+Vtb*conj(xitc))*conj(xietau)/pow(mHp,2);
      std::complex<double> gp =  1.5*(CRcb - CLcb)/CSMcb;
      std::complex<double> gpmutau =  1.5*(CRcbmutau - CLcbmutau)/CSMcb;
      std::complex<double> gpetau =  1.5*(CRcbetau - CLcbetau)/CSMcb;
      std::complex<double> factor = {4.35,0};
      std::complex<double> one = {1,0};
      const double Gamma_Bc_SM = (hbar/(0.52e-12)); //Theoretical value in GeV^-1 from 1611.06676
      const double Gamma_Bc_exp = (hbar/(0.510e-12)); //experimental value in GeV^-1
      const double BR_Bc_SM = 0.022634487;
      double BR_Bc_THDM = BR_Bc_SM*(norm(one + factor*gp)+norm(factor*gpmutau)+norm(factor*gpetau));
      double Gamma_Bc_THDM = (BR_Bc_THDM-BR_Bc_SM)*Gamma_Bc_exp;
      if (i==1)
      {
      result = hbar/(Gamma_Bc_SM + Gamma_Bc_THDM);
      }
      else if (i==2)
      {
      result = BR_Bc_THDM;
      }

    }

    void THDM_Bc_lifetime(double &result)
    {
      using namespace Pipes::THDM_Bc_lifetime;

      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;
      THDM_Bc_obs(sminputs,spectrum, 1, result);
    }

    void THDM_Bc2taunu(double &result)
    {
      using namespace Pipes::THDM_Bc2taunu;

      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;
      THDM_Bc_obs(sminputs,spectrum, 2, result);
    }

    ///------------------------///
    ///      Likelihoods       ///
    ///------------------------///

    /// Likelihood for the differential widths of tree-level semileptonic B decays to tau leptons
    void dBRBDtaunu_LogLikelihood(double &result)
    {
      using namespace Pipes::dBRBDtaunu_LogLikelihood;

      if (flav_debug) std::cout<<"Starting dBRBDtaunu_LogLikelihood"<< std::endl;

      predictions_measurements_covariances pmc = *Dep::dBRBDtaunu_M;

      boost::numeric::ublas::matrix<double> cov=pmc.cov_exp;

      // adding theory and experimental covariance
      cov+=pmc.cov_th;
      //calculating a diff
      std::vector<double> diff;
      diff=pmc.diff;

      boost::numeric::ublas::matrix<double> cov_inv(pmc.dim, pmc.dim);
      InvertMatrix(cov, cov_inv);
      double Chi2=0;

      for (int i=0; i < pmc.dim; ++i)
      {
        for (int j=0; j<pmc.dim; ++j)
        {
          Chi2+= diff[i] * cov_inv(i,j)*diff[j];
        }
      }

      result=-0.5*Chi2;

      if (flav_debug) std::cout<<"Finished dBRBDtaunu_LogLikelihood"<< std::endl;

      if (flav_debug_LL) std::cout<<"Likelihood result dBRBDtaunu_LogLikelihood  : "<< result<< std::endl;
    }

    /// Likelihood for the differential widths of tree-level semileptonic B decays to tau leptons
    void dBRBDstartaunu_LogLikelihood(double &result)
    {
      using namespace Pipes::dBRBDstartaunu_LogLikelihood;

      if (flav_debug) std::cout<<"Starting dBRBDstartaunu_LogLikelihood"<< std::endl;

      predictions_measurements_covariances pmc = *Dep::dBRBDstartaunu_M;

      boost::numeric::ublas::matrix<double> cov=pmc.cov_exp;

      // adding theory and experimental covariance
      cov+=pmc.cov_th;
      //calculating a diff
      std::vector<double> diff;
      diff=pmc.diff;

      boost::numeric::ublas::matrix<double> cov_inv(pmc.dim, pmc.dim);
      InvertMatrix(cov, cov_inv);
      double Chi2=0;
      for (int i=0; i < pmc.dim; ++i)
      {
        for (int j=0; j<pmc.dim; ++j)
        {
          Chi2+= diff[i] * cov_inv(i,j)*diff[j];
        }
      }

      result=-0.5*Chi2;

      if (flav_debug) std::cout<<"Finished dBRBDstartaunu_LogLikelihood"<< std::endl;

      if (flav_debug_LL) std::cout<<"Likelihood result dBRBDstartaunu_LogLikelihood  : "<< result<< std::endl;
    }

    /// Likelihood for tree-level leptonic and semileptonic B decays
    void SL_LogLikelihood(double &result)
    {
      using namespace Pipes::SL_LogLikelihood;

      if (flav_debug) std::cout<<"Starting SL_LogLikelihood"<< std::endl;

      predictions_measurements_covariances pmc = *Dep::SL_M;
      static std::vector<str> obs_list = Downstream::subcaps->getNames();

      boost::numeric::ublas::matrix<double> cov=pmc.cov_exp;

      // adding theory and experimental covariance
      cov+=pmc.cov_th;

      //calculating a diff
      std::vector<double> diff;
      diff=pmc.diff;

      boost::numeric::ublas::matrix<double> cov_inv(pmc.dim, pmc.dim);
      InvertMatrix(cov, cov_inv);

      double Chi2=0;
      for (int i=0; i < pmc.dim; ++i)
      {
        if(std::find(obs_list.begin(), obs_list.end(), pmc.names[i]) != obs_list.end())
        {
          for (int j=0; j<pmc.dim; ++j)
          {
              Chi2+= diff[i] * cov_inv(i,j)*diff[j];
          }
        }
      }

      result=-0.5*Chi2;

      if (flav_debug) std::cout<<"Finished SL_LogLikelihood"<< std::endl;
      if (flav_debug_LL) std::cout<<"Likelihood result SL_LogLikelihood  : "<< result<< std::endl;
    }


    /// LogLikelihood for FLDstar
    void FLDstar_LogLikelihood(double &result)
    {
      using namespace Pipes::FLDstar_LogLikelihood;
      static bool th_err_absolute, first = true;
      static double exp_meas, exp_FLDstar_err, th_err;

      if (flav_debug) std::cout << "FLDstar_LogLikelihood"<< std::endl;

      if (first)
      {
        Flav_reader fread(GAMBIT_DIR  "/FlavBit/data");
        fread.debug_mode(flav_debug);
        if (flav_debug) std::cout<<"Initialised Flav reader in FLDstar_LogLikelihood"<< std::endl;
        fread.read_yaml_measurement("flav_data.yaml", "FLDstar");
        fread.initialise_matrices();
        exp_meas = fread.get_exp_value()(0,0);
        exp_FLDstar_err = sqrt(fread.get_exp_cov()(0,0));
        th_err = fread.get_th_err()(0,0).first;
        th_err_absolute = fread.get_th_err()(0,0).second;
        first = false;
      }

      if (flav_debug) std::cout << "Experiment: " << exp_meas << " " << exp_FLDstar_err << " " << th_err << std::endl;

      double theory_prediction = *Dep::FLDstar;
      double theory_FLDstar_err = th_err * (th_err_absolute ? 1.0 : std::abs(theory_prediction));
      if (flav_debug) std::cout<<"Theory prediction: "<<theory_prediction<<" +/- "<<exp_FLDstar_err<< std::endl;

      bool profile = runOptions->getValueOrDef<bool>(false, "profile_systematics");

      result = Stats::gaussian_loglikelihood(theory_prediction, exp_meas, theory_FLDstar_err, exp_FLDstar_err, profile);
    }


    /// HEPLike LogLikelihood RD RDstar
    // TODO: Recognised sub-capabilities:
    //    RD
    //    RDstar
    void HEPLike_RDRDstar_LogLikelihood(double& result)
    {
      using namespace Pipes::HEPLike_RDRDstar_LogLikelihood;
      static const std::string inputfile = path_to_latest_heplike_data() + "/data/HFLAV_19/Semileptonic/RD_RDstar.yaml";
      static HepLike_default::HL_nDimGaussian nDimGaussian(inputfile);
      static bool first = true;
      if (first)
      {
        if (flav_debug) std::cout << "Debug: Reading HepLike data file: " << inputfile << std::endl;
        nDimGaussian.Read();
        first = false;
      }

      // TODO: SuperIso is not ready to give correlations for these observables. So currently we fall back to the old way.
      //       Below code is for future reference.
      // static std::vector<str> obs_list = Downstream::subcaps->getNames();
      // flav_prediction prediction = *Dep::prediction_RDRDstar;
      // flav_observable_map theory = prediction.central_values;
      // flav_covariance_map theory_covariance = prediction.covariance;

      // result = nDimGaussian.GetLogLikelihood(get_obs_theory(prediction, obs_list), get_obs_covariance(prediction, obs_list));
      const std::vector<double> theory{*Dep::RD, *Dep::RDstar};
      result = nDimGaussian.GetLogLikelihood(theory /* , theory_covariance */);

      if (flav_debug) std::cout << "HEPLike_RDRDstar_LogLikelihood result: " << result << std::endl;
    }

    // TODO: This does not work currently in this form as it is not implemented in SuperIso
    /// HEPLike LogLikelihood B -> tau nu
    //HEPLIKE_GAUSSIAN_1D_LIKELIHOOD(B2taunu, "/data/PDG/Semileptonic/B2TauNu.yaml")

    /// Likelihood for the Bc lifetime
    void Bc_lifetime_LogLikelihood(double &result)
    {
      using namespace Pipes::Bc_lifetime_LogLikelihood;
      static bool th_err_absolute, first = true;
      static double exp_meas, exp_taulifetime_err, th_err;

      if (flav_debug) std::cout << "Bc_lifetime_LogLikelihood"<< std::endl;

      if (first)
      {
        Flav_reader fread(GAMBIT_DIR  "/FlavBit/data");
        fread.debug_mode(flav_debug);
        if (flav_debug) std::cout<<"Initialised Flav reader in Bc_lifetime_ikelihood"<< std::endl;
        fread.read_yaml_measurement("flav_data.yaml", "Bc_lifetime");
        fread.initialise_matrices();
        exp_meas = fread.get_exp_value()(0,0);
        exp_taulifetime_err = sqrt(fread.get_exp_cov()(0,0));
        th_err = fread.get_th_err()(0,0).first;
        th_err_absolute = fread.get_th_err()(0,0).second;
        first = false;
      }

      if (flav_debug) std::cout << "Experiment: " << exp_meas << " " << exp_taulifetime_err << " " << th_err << std::endl;

      double theory_prediction = *Dep::Bc_lifetime;
      double theory_taulifetime_err = th_err * (th_err_absolute ? 1.0 : std::abs(theory_prediction));
      if (flav_debug) std::cout<<"Theory prediction: "<<theory_prediction<<" +/- "<<exp_taulifetime_err<< std::endl;

      bool profile = runOptions->getValueOrDef<bool>(false, "profile_systematics");

      result = Stats::gaussian_loglikelihood(theory_prediction, exp_meas, theory_taulifetime_err, exp_taulifetime_err, profile);
    }

    /// Likelihood for Bc->tau nu
    void Bc2taunu_LogLikelihood(double &result)
    {
      using namespace Pipes::Bc2taunu_LogLikelihood;
      static bool first = true;
      static boost::numeric::ublas::matrix<double> cov_exp, value_exp;
      static double th_err[1];
      double theory[1];

      if (first)
      {
        // Read in experimental measurements
        Flav_reader fread(GAMBIT_DIR  "/FlavBit/data");
        fread.debug_mode(flav_debug);

        fread.read_yaml_measurement("flav_data.yaml", "Bc2taunu");

        fread.initialise_matrices();
        cov_exp=fread.get_exp_cov();
        value_exp=fread.get_exp_value();

        for (int i = 0; i < 1; ++i)
          th_err[i] = fread.get_th_err()(i,0).first;

        // Init over.
        first = false;
      }

     theory[0] = *Dep::Bc2taunu;
     if(flav_debug) std::cout << "BR(Bc ->tau nu ) = " << theory[0] << std::endl;

     result = 0;
     for (int i = 0; i < 1; ++i)
       result += Stats::gaussian_upper_limit(theory[i], value_exp(i,0), th_err[i], sqrt(cov_exp(i,i)), false);
    }    

  }
}

