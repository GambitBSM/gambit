//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Functions of module FlavBit:
///  - Wilson Coefficients
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@kit.edu)
///  \date 2022 Aug
///  \date 2024 Feb
///
///  \author Cristian Sierra
///          (cristian.sierra@monash.edu)
///  \date 2020 June-December
///  \date 2021 Jan-Sep
///  \date 2022 June
///
///  *********************************************

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/FlavBit/FlavBit_rollcall.hpp"
#include "gambit/FlavBit/FlavBit_utils.hpp"
#include "gambit/Utils/statistics.hpp"

namespace Gambit
{

  namespace FlavBit
  {

    using std::vector;
    using complexd = std::complex<double>;
    enum {u=0, c=1, t=2, d=0, s=1, b=2, e=0, mu=1, tau=2};

    /// Module functions for returning WCs in the GWC model
    ///@{

    void DeltaC2(WilsonCoefficient &result)
    {
      using namespace Pipes::DeltaC2;
      result = WilsonCoefficient({*Param["Re_DeltaC2_e"],*Param["Im_DeltaC2_e"]},
                                 {*Param["Re_DeltaC2_mu"],*Param["Im_DeltaC2_mu"]},
                                 {*Param["Re_DeltaC2_tau"],*Param["Im_DeltaC2_tau"]});
    }

    void DeltaC7(WilsonCoefficient &result)
    {
      using namespace Pipes::DeltaC7;
      result = WilsonCoefficient({*Param["Re_DeltaC7_e"],*Param["Im_DeltaC7_e"]},
                                 {*Param["Re_DeltaC7_mu"],*Param["Im_DeltaC7_mu"]},
                                 {*Param["Re_DeltaC7_tau"],*Param["Im_DeltaC7_tau"]});
    }

    void DeltaC8(WilsonCoefficient &result)
    {
      using namespace Pipes::DeltaC8;
      result = WilsonCoefficient({*Param["Re_DeltaC8_e"],*Param["Im_DeltaC8_e"]},
                                 {*Param["Re_DeltaC8_mu"],*Param["Im_DeltaC8_mu"]},
                                 {*Param["Re_DeltaC8_tau"],*Param["Im_DeltaC8_tau"]});
    }

    void DeltaC9(WilsonCoefficient &result)
    {
      using namespace Pipes::DeltaC9;
      result = WilsonCoefficient({*Param["Re_DeltaC9_e"],*Param["Im_DeltaC9_e"]},
                                 {*Param["Re_DeltaC9_mu"],*Param["Im_DeltaC9_mu"]},
                                 {*Param["Re_DeltaC9_tau"],*Param["Im_DeltaC9_tau"]});
    }

    void DeltaC10(WilsonCoefficient &result)
    {
      using namespace Pipes::DeltaC10;
      result = WilsonCoefficient({*Param["Re_DeltaC10_e"],*Param["Im_DeltaC10_e"]},
                                 {*Param["Re_DeltaC10_mu"],*Param["Im_DeltaC10_mu"]},
                                 {*Param["Re_DeltaC10_tau"],*Param["Im_DeltaC10_tau"]});
    }

    void DeltaC2p(WilsonCoefficient &result)
    {
      using namespace Pipes::DeltaC2p;
      result = WilsonCoefficient({*Param["Re_DeltaC2p_e"],*Param["Im_DeltaC2p_e"]},
                                 {*Param["Re_DeltaC2p_mu"],*Param["Im_DeltaC2p_mu"]},
                                 {*Param["Re_DeltaC2p_tau"],*Param["Im_DeltaC2p_tau"]});
    }

    void DeltaC7p(WilsonCoefficient &result)
    {
      using namespace Pipes::DeltaC7p;
      result = WilsonCoefficient({*Param["Re_DeltaC7p_e"],*Param["Im_DeltaC7p_e"]},
                                 {*Param["Re_DeltaC7p_mu"],*Param["Im_DeltaC7p_mu"]},
                                 {*Param["Re_DeltaC7p_tau"],*Param["Im_DeltaC7p_tau"]});
    }

    void DeltaC8p(WilsonCoefficient &result)
    {
      using namespace Pipes::DeltaC8p;
      result = WilsonCoefficient({*Param["Re_DeltaC8p_e"],*Param["Im_DeltaC8p_e"]},
                                 {*Param["Re_DeltaC8p_mu"],*Param["Im_DeltaC8p_mu"]},
                                 {*Param["Re_DeltaC8p_tau"],*Param["Im_DeltaC8p_tau"]});
    }

    void DeltaC9p(WilsonCoefficient &result)
    {
      using namespace Pipes::DeltaC9p;
      result = WilsonCoefficient({*Param["Re_DeltaC9p_e"],*Param["Im_DeltaC9p_e"]},
                                 {*Param["Re_DeltaC9p_mu"],*Param["Im_DeltaC9p_mu"]},
                                 {*Param["Re_DeltaC9p_tau"],*Param["Im_DeltaC9p_tau"]});
    }

    void DeltaC10p(WilsonCoefficient &result)
    {
      using namespace Pipes::DeltaC10p;
      result = WilsonCoefficient({*Param["Re_DeltaC10p_e"],*Param["Im_DeltaC10p_e"]},
                                 {*Param["Re_DeltaC10p_mu"],*Param["Im_DeltaC10p_mu"]},
                                 {*Param["Re_DeltaC10p_tau"],*Param["Im_DeltaC10p_tau"]});
    }

    void DeltaCQ1(WilsonCoefficient &result)
    {
      using namespace Pipes::DeltaCQ1;
      result = WilsonCoefficient({*Param["Re_DeltaCQ1_e"],*Param["Im_DeltaCQ1_e"]},
                                 {*Param["Re_DeltaCQ1_mu"],*Param["Im_DeltaCQ1_mu"]},
                                 {*Param["Re_DeltaCQ1_tau"],*Param["Im_DeltaCQ1_tau"]});
    }

    void DeltaCQ2(WilsonCoefficient &result)
    {
      using namespace Pipes::DeltaCQ2;
      result = WilsonCoefficient({*Param["Re_DeltaCQ2_e"],*Param["Im_DeltaCQ2_e"]},
                                 {*Param["Re_DeltaCQ2_mu"],*Param["Im_DeltaCQ2_mu"]},
                                 {*Param["Re_DeltaCQ2_tau"],*Param["Im_DeltaCQ2_tau"]});
    }

    void DeltaCQ1p(WilsonCoefficient &result)
    {
      using namespace Pipes::DeltaCQ1p;
      result = WilsonCoefficient({*Param["Re_DeltaCQ1p_e"],*Param["Im_DeltaCQ1p_e"]},
                                 {*Param["Re_DeltaCQ1p_mu"],*Param["Im_DeltaCQ1p_mu"]},
                                 {*Param["Re_DeltaCQ1p_tau"],*Param["Im_DeltaCQ1p_tau"]});
    }

    void DeltaCQ2p(WilsonCoefficient &result)
    {
      using namespace Pipes::DeltaCQ2p;
      result = WilsonCoefficient({*Param["Re_DeltaCQ2p_e"],*Param["Im_DeltaCQ2p_e"]},
                                 {*Param["Re_DeltaCQ2p_mu"],*Param["Im_DeltaCQ2p_mu"]},
                                 {*Param["Re_DeltaCQ2p_tau"],*Param["Im_DeltaCQ2p_tau"]});
    }

    void DeltaCL(WilsonCoefficient &result)
    {
      using namespace Pipes::DeltaCL;
      result = WilsonCoefficient({*Param["Re_DeltaCLL_V"],*Param["Im_DeltaCLL_V"]});
    }

    void DeltaCR(WilsonCoefficient &result)
    {
      using namespace Pipes::DeltaCR;
      result = WilsonCoefficient({*Param["Re_DeltaCRR_V"],*Param["Im_DeltaCRR_V"]});
    }

    ///@}

    /// Umbrella modfule function that contains all wilson coefficients
    void DeltaC(WilsonCoefficients &result)
    {
      using namespace Pipes::DeltaC;

      result["C2"] = *Dep::DeltaC2;
      result["C7"] = *Dep::DeltaC7;
      result["C8"] = *Dep::DeltaC8;
      result["C9"] = *Dep::DeltaC9;
      result["C10"] = *Dep::DeltaC10;
      result["C2p"] = *Dep::DeltaC2p;
      result["C7p"] = *Dep::DeltaC7p;
      result["C8p"] = *Dep::DeltaC8p;
      result["C9p"] = *Dep::DeltaC9p;
      result["C10p"] = *Dep::DeltaC10p;
      result["CQ1"] = *Dep::DeltaCQ1;
      result["CQ2"] = *Dep::DeltaCQ2;
      result["CQ1p"] = *Dep::DeltaCQ1p;
      result["CQ2p"] = *Dep::DeltaCQ2p;
      result["CL"] = *Dep::DeltaCL;
      result["CR"] = *Dep::DeltaCR;
    }

    ///Green functions for Delta C9 and Delta C10 in the THDM
    ///@{

    ///Gamma penguin Greens function
    double DHp(double t)
    {
      if(fabs(1.-t)<1.e-5) return DHp(0.9999);

      return -(-38 + 117*t - 126*t*t + 47*pow(t,3) +
            6*(4 - 6*t + 3*pow(t,3))*log(1/t))/
           (108.*pow(t-1,4));
    }

    ///Z penguin Greens function
    double CHp(double t)
    {
      if(fabs(1.-t)<1.e-5) return CHp(0.9999);

      return (1.-t-t*log(1/t))/(pow(t-1,2));
    }

    ///Zmix  penguin Greens function
    double CHpmix(double t)
    {
      if(fabs(1.-t)<1.e-5) return CHpmix(0.9999);

      return t*(-1 + t*t +2*t*log(1/t))/(pow(t-1,3));
    }

    ///Box diagram Greens function
    double BHp(double t)
    {
      if(fabs(1.-t)<1.e-5) return BHp(0.9999);

      return (-1 + t + t*log(1/t))/(16.*pow(t-1,2));
    }

    ///Box diagram Greens function for C9' and C10'
    double BHpp(double t)
    {
      if(fabs(1.-t)<1.e-5) return BHpp(0.9999);

      return ((-1 + t + t*log(1/t)))/(16.*pow(t-1,2));
    }

    vector<vector<complexd>> get_xiF(Spectrum& spectrum, char F)
    {
      const double beta = atan(spectrum.get(Par::dimensionless,"tanb"));
      const double cosb = cos(beta), sinb = sin(beta);
      vector<vector<complexd>> xiF(3,vector<complexd>(3, 0.0));
      char YF1[7]; sprintf(YF1, "Y%c1", F);
      char YF2[7]; sprintf(YF2, "Y%c2", F);
      char ImYF1[7]; sprintf(ImYF1, "ImY%c1", F);
      char ImYF2[7]; sprintf(ImYF2, "ImY%c2", F);

      for (int i=0; i<3; ++i)
      {
        for (int j=0; j<3; ++j)
        {
          complexd YF1_ij ( spectrum.get(Par::dimensionless,YF1,i+1,j+1), spectrum.get(Par::dimensionless,ImYF1,i+1,j+1) );
          complexd YF2_ij ( spectrum.get(Par::dimensionless,YF2,i+1,j+1), spectrum.get(Par::dimensionless,ImYF2,i+1,j+1) );
          xiF[i][j] = YF2_ij*cosb - YF1_ij*sinb;
        }
      }
      return xiF;
    }

    ///@}

    /// Wilson coefficients
    ///@{

    /// Scalar WCs at tree level in the THDM
    complexd THDM_DeltaCQ_NP(int wc, int l, int lp, SMInputs &sminputs, Spectrum &spectrum)
    {
      const double alpha = spectrum.get(Par::dimensionless,"alpha");
      const double tanb = spectrum.get(Par::dimensionless,"tanb");
      const double beta = atan(tanb);
      const double v = spectrum.get(Par::mass1, "vev");
      const double cba = cos(beta-alpha), sba = sin(beta-alpha);
      const double mW = sminputs.mW;
      const double mZ = sminputs.mZ;
      const double SW = sqrt(1 - pow(mW/mZ,2));
      const double mMu = sminputs.mMu;
      const double mTau = sminputs.mTau;
      const vector<double> ml = {0, mMu, mTau};     // charged leptons
      const double mBmB = sminputs.mBmB;
      const double mh = spectrum.get(Par::Pole_Mass,"h0",1);
      const double mH = spectrum.get(Par::Pole_Mass,"h0",2);
      const double mA = spectrum.get(Par::Pole_Mass,"A0");
      const double yh = 1/(mh*mh), yH = 1/(mH*mH), yA = 1/(mA*mA);

      const double A      = sminputs.CKM.A;
      const double lambda = sminputs.CKM.lambda;

      auto xiD = get_xiF(spectrum,'d');
      auto xiE = get_xiF(spectrum,'e');

      const complexd xi_sb     = (1/sqrt(2))*xiD[s][b];
      const complexd xi_bs     = (1/sqrt(2))*xiD[b][s];
      const complexd xi_mumu   = (1/sqrt(2))*xiE[mu][mu];
      const complexd xi_mutau  = (1/sqrt(2))*xiE[mu][tau];
      const complexd xi_taumu  = (1/sqrt(2))*xiE[tau][mu];
      const complexd xi_tautau = (1/sqrt(2))*xiE[tau][tau];

      const double Vts = -A*lambda*lambda;
      const double Vtb = 1 - (1/2)*A*A*pow(lambda,4);

      Eigen::Matrix3cd xi_L, deltaij;

      // TODO: This is not valid for l = 0 or lp = 0
      xi_L << 0,       0,       0,
              0,  xi_mumu, xi_mutau,
              0, xi_taumu, xi_tautau;

      deltaij << 1 ,0 ,0,
                 0 ,1 ,0,
                 0 ,0 ,1;

      complexd Lijp = yA*(xi_L(l,lp)-std::conj(xi_L(lp,l)))+(cba*cba*yh+sba*sba*yH)*(xi_L(l,lp)+std::conj(xi_L(lp,l)));
      complexd Lijm = yA*(xi_L(l,lp)-std::conj(xi_L(lp,l)))-(cba*cba*yh+sba*sba*yH)*(xi_L(l,lp)+std::conj(xi_L(lp,l)));

      complexd result = mBmB*pow(pi,2)/(2.*pow(sminputs.GF,2)*pow(mW,2)*pow(SW,2)*Vtb*Vts);

      switch(wc)
      {
        case 1:
           result*= std::conj(xi_bs)*(2*sba*cba*(ml[l]*deltaij(l,lp)/v)*(yh-yH) + Lijp);
           return result;
           break;

        case 2:
           result*= std::conj(xi_bs)*((cba*cba*yh+sba*sba*yH)*(xi_L(l,lp)-std::conj(xi_L(lp,l))) + yA*(xi_L(l,lp)+std::conj(xi_L(lp,l))));
           return result;
           break;

        case 3://CQ1prime
           result*= xi_sb*(2*sba*cba*(ml[l]*deltaij(l,lp)/v)*(yh-yH) - Lijm);
           return result;
           break;

        case 4://CQ2prime
           result*= xi_sb*((cba*cba*yh+sba*sba*yH)*(xi_L(l,lp)-std::conj(xi_L(lp,l))) - yA*(xi_L(l,lp)+std::conj(xi_L(lp,l))));
           return result;
           break;
      }

      return 0.0;
    }


    ///Function for WCs 9,10 and primes in the THDM
    complexd THDM_DeltaC_NP(int wc, int l, int lp, SMInputs &sminputs, Spectrum &spectrum)
    {
      const double mBmB = sminputs.mBmB;
      const double mT = sminputs.mT;
      const double mHp = spectrum.get(Par::Pole_Mass,"H+");
      const double mW = sminputs.mW;
      const double mZ = sminputs.mZ;
      const double SW = sqrt(1 - pow(mW/mZ,2));

      const double A      = sminputs.CKM.A;
      const double lambda = sminputs.CKM.lambda;

      //const double rhobar = sminputs.CKM.rhobar;
      //const double etabar = sminputs.CKM.etabar;
      const double Vcs = 1 - (1/2)*lambda*lambda;
      const double Vcb = A*lambda*lambda;
      const double Vts = -A*lambda*lambda;
      const double Vtb = 1 - (1/2)*A*A*pow(lambda,4);
      const double Vub = 0;//This should be improved by directly calling an Eigen object
      const double Vus = lambda;

      auto xiU = get_xiF(spectrum,'u');
      auto xiD = get_xiF(spectrum,'d');
      auto xiE = get_xiF(spectrum,'e');

      const complexd xi_tt     = (1/sqrt(2))*xiU[t][t];
      const complexd xi_cc     = (1/sqrt(2))*xiU[c][c];
      const complexd xi_tc     = (1/sqrt(2))*xiU[t][c];
      const complexd xi_ct     = (1/sqrt(2))*xiU[c][t];
      const complexd xi_bb     = (1/sqrt(2))*xiD[b][b];
      const complexd xi_ss     = (1/sqrt(2))*xiD[s][s];
      const complexd xi_sb     = (1/sqrt(2))*xiD[s][b];
      const complexd xi_bs     = (1/sqrt(2))*xiD[b][s];
      const complexd xi_mumu   = (1/sqrt(2))*xiE[mu][mu];
      const complexd xi_mutau  = (1/sqrt(2))*xiE[mu][tau];
      const complexd xi_taumu  = (1/sqrt(2))*xiE[tau][mu];
      const complexd xi_tautau = (1/sqrt(2))*xiE[tau][tau];

      Eigen::Matrix3cd xi_L;

      // TODO: This is not valid for l = 0 or lp = 0
      xi_L << 0,       0,       0,
              0,  xi_mumu, xi_mutau,
              0, xi_taumu, xi_tautau;

      Eigen::Vector3cd xil_m1 = xi_L.col(l);
      Eigen::Vector3cd xil_m1conj = xil_m1.conjugate();
      Eigen::Vector3cd xilp_m2 = xi_L.col(lp);


      complexd C9_gamma = (1/(sqrt(2)*std::real(Vtb*std::conj(Vts))*sminputs.GF*mHp*mHp))*(xi_ct*std::conj(Vcs) + xi_tt*std::conj(Vts))*
                                      (Vcb*std::conj(xi_ct) + Vtb*std::conj(xi_tt))*DHp(pow(mT/mHp,2));
      complexd C9_Z = ((4*SW*SW-1)/(8.*sqrt(2)*mW*mW*SW*SW*std::real(Vtb*std::conj(Vts))*sminputs.GF))*(xi_ct*std::conj(Vcs) + xi_tt*std::conj(Vts))*
                                  (Vcb*std::conj(xi_ct) + Vtb*std::conj(xi_tt))*(CHp(pow(mT/mHp,2))-1.);
      complexd C9_Zmix = (mBmB*(4*SW*SW-1)*(xi_bb*std::conj(Vtb) + xi_sb*std::conj(Vts))*(Vcs*std::conj(xi_ct) + Vts*std::conj(xi_tt)))*CHpmix(pow(mT/mHp,2))/(16.*sqrt(2)*sminputs.GF*mT*pow(mW,2)*pow(SW,2)*Vtb*std::conj(Vts));

      complexd C9_Box = (1/(2.*mW*mW*SW*SW*std::real(Vtb*std::conj(Vts))*pow(sminputs.GF,2)*mHp*mHp))*(xil_m1conj.dot(xilp_m2))*(std::conj(Vcs)*(Vcb*xi_cc*std::conj(xi_cc) + Vcb*xi_ct*std::conj(xi_ct) + Vtb*xi_cc*std::conj(xi_tc) + Vtb*xi_ct*std::conj(xi_tt)) + std::conj(Vts)*(Vcb*xi_tc*std::conj(xi_cc) + Vcb*xi_tt*std::conj(xi_ct) + Vtb*xi_tc*std::conj(xi_tc) + Vtb*xi_tt*std::conj(xi_tt)))*BHp(pow(mT/mHp,2));

      complexd C9_mub = (2/(4.*sqrt(2)*27*std::real(Vtb*std::conj(Vts))*sminputs.GF*mHp*mHp))*(xi_cc*std::conj(Vcs) + xi_tc*std::conj(Vts))*
                                      (Vcb*std::conj(xi_cc) + Vtb*std::conj(xi_tc))*(19+12*log(pow(mBmB/mHp,2)));

      complexd C10_Ztotal = (1/(4*SW*SW-1))*(C9_Z+C9_Zmix);

      complexd C10_Box = C9_Box;

      complexd C9p_gamma = (1/(sqrt(2)*std::real(Vtb*std::conj(Vts))*sminputs.GF*mHp*mHp))*((Vtb*xi_bb + Vts*xi_sb)*(Vtb*xi_bs + Vts*xi_ss))*DHp(pow(mT/mHp,2));

      complexd C9p_Z = ((1-4*SW*SW)/(8.*sqrt(2)*mW*mW*SW*SW*std::real(Vtb*std::conj(Vts))*sminputs.GF))*((Vtb*xi_bb + Vts*xi_sb)*(Vtb*xi_bs + Vts*xi_ss))*(CHp(pow(mT/mHp,2))-1.);

      complexd C9p_Box = (1/(2.*mW*mW*SW*SW*std::real(Vtb*std::conj(Vts))*pow(sminputs.GF,2)*mHp*mHp))*(xil_m1conj.dot(xilp_m2))*(((Vcb*xi_bb + Vcs*xi_sb)*std::conj(Vcb) + (Vtb*xi_bb + Vts*xi_sb)*std::conj(Vtb) + (Vub*xi_bb + Vus*xi_sb)*std::conj(Vub))*std::conj(xi_bs) + ((Vcb*xi_bb + Vcs*xi_sb)*std::conj(Vcs) + (Vtb*xi_bb + Vts*xi_sb)*std::conj(Vts) + (Vub*xi_bb + Vus*xi_sb)*std::conj(Vus))*std::conj(xi_ss))*BHpp(pow(mT/mHp,2));

      complexd C9p_mub = (2/(4.*sqrt(2)*27*std::real(Vtb*std::conj(Vts))*sminputs.GF*mHp*mHp))*((Vcb*xi_bb + Vcs*xi_sb)*(Vcb*xi_bs + Vcs*xi_ss))*(19+12*log(pow(mBmB/mHp,2)));

      complexd C10p_Z = -(1/(1-4*SW*SW))*C9p_Z;

      complexd C10p_Box = C9p_Box;

      complexd CL_nunu = -C9_Box;

      complexd CR_nunu = -C9p_Box;

      const double CL_SM = -1.469/pow(SW,2);
      const double denom = norm(CL_nunu+CL_SM)+norm(CR_nunu);

      switch(wc)
      {
        case 9:
           return  C9_gamma + C9_Z + C9_Zmix + C9_Box + C9_mub;
           break;

        case 10:
           return  C10_Ztotal + C10_Box;
           break;

        case 11://C9prime
           return  C9p_gamma + C9p_Z + C9p_Box + C9p_mub;//C9p_Zmix contribution is suppressed by the strange quark mass
           break;

        case 12://C10prime
           return  C10p_Z + C10p_Box;//C10p_Zmix contribution is suppressed by the strange quark mass
           break;

        case 13://epsilon for b->snunu from 1409.4557
           if(l != lp)
           {
           return 0;
           break;
           }
           else
           {
           return  sqrt(norm(CL_nunu + CL_SM)+norm(CR_nunu))/abs(CL_SM);
           break;
           }

        case 14://eta for b->snunu from 1409.4557
           if(denom == 0)
           {
           return 0;
           break;
           }
           else
           {
           return  -std::real((CL_nunu+CL_SM)*std::conj(CR_nunu))/denom;
           break;
           }
      }
      return 0.0;
    }

    ///@}
    /// Module functions
    ///@{

    /// Delta CQ1 at tree level in the THDM
    void THDM_DeltaCQ1(WilsonCoefficient &result)
    {
      using namespace Pipes::THDM_DeltaCQ1;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      result.e = THDM_DeltaCQ_NP(1, e, e, sminputs, spectrum);
      result.mu = THDM_DeltaCQ_NP(1, mu, mu, sminputs, spectrum);
      result.tau = THDM_DeltaCQ_NP(1, tau, tau, sminputs, spectrum);
    }

    /// Delta CQ1' at tree level in the THDM
    void THDM_DeltaCQ1p(WilsonCoefficient &result)
    {
      using namespace Pipes::THDM_DeltaCQ1p;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      result.e = THDM_DeltaCQ_NP(3, e, e, sminputs, spectrum);
      result.mu = THDM_DeltaCQ_NP(3, mu, mu, sminputs, spectrum);
      result.tau = THDM_DeltaCQ_NP(3, tau, tau, sminputs, spectrum);
    }

    /// Delta CQ2 at tree level in the THDM
    void THDM_DeltaCQ2(WilsonCoefficient &result)
    {
      using namespace Pipes::THDM_DeltaCQ2;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      result.e = THDM_DeltaCQ_NP(2, e, e, sminputs, spectrum);
      result.mu = THDM_DeltaCQ_NP(2, mu, mu, sminputs, spectrum);
      result.tau = THDM_DeltaCQ_NP(2, tau, tau, sminputs, spectrum);
    }

    /// Delta CQ2' at tree level in the THDM
    void THDM_DeltaCQ2p(WilsonCoefficient &result)
    {
      using namespace Pipes::THDM_DeltaCQ2p;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      result.e = THDM_DeltaCQ_NP(4, e, e, sminputs, spectrum);
      result.mu = THDM_DeltaCQ_NP(4, mu, mu, sminputs, spectrum);
      result.tau = THDM_DeltaCQ_NP(4, tau, tau, sminputs, spectrum);
    }

    ///Green functions for Delta C7 in THDM
    ///@{

    double F7_1(double t)
    {
        if(fabs(1.-t)<1.e-5) return F7_1(0.9999);
        return -((7 - 12*t - 3*t*t + 8*t*t*t +
           6*t*(-2 + 3*t)*log(1/t)))/(72.*pow(-1 + t,4));
    }

    double F7_2(double t)
    {
    if(fabs(1.-t)<1.e-5) return F7_2(0.9999);
        return sqrt(t)*(3 - 8*t + 5*t*t + (-4 + 6*t)*log(1/t))/
           (12.*pow(-1 + t,3));
    }
    double F7_3 (double t)
    {
    if (fabs (1. - t) < 1.e-5) return F7_3 (0.9999);
        return -(3*t*(-2*log (1/t) + 1) - 6*t*t + t*t*t + 2)/(24.* pow (-1 + t, 4));
    }

    double F7_4 (double t)
    {
    if (fabs (1. - t) < 1.e-5) return F7_4 (0.9999);
        return sqrt(t)*(-2*log (1/t) + 3 - 4*t + t*t)/(4.*pow (-1 + t, 3));
    }

    ///@}

    /// Delta C2 in the THDM
    void THDM_DeltaC2(WilsonCoefficient &result)
    {
      using namespace Pipes::THDM_DeltaC2;
      Spectrum spectrum = *Dep::THDM_spectrum;
      SMInputs sminputs = *Dep::SMINPUTS;
      const double lambda = Dep::SMINPUTS->CKM.lambda;
      const double A = Dep::SMINPUTS->CKM.A;
      const double mC = Dep::SMINPUTS->mCmC;
      const double mBmB = Dep::SMINPUTS->mBmB;
      double mHp = spectrum.get(Par::Pole_Mass,"H+");
      auto xiU = get_xiF(spectrum,'u');
      auto xiD = get_xiF(spectrum,'d');
      const complexd xi_tc     = (1/sqrt(2))*xiU[t][c];
      const complexd xi_bb     = (1/sqrt(2))*xiD[b][b];
      const complexd xi_sb     = (1/sqrt(2))*xiD[s][b];
      const complexd xi_cc     = (1/sqrt(2))*xiU[c][c];

      const double Vcs = 1 - (1/2)*lambda*lambda;
      const double Vcb = A*lambda*lambda;
      const double Vts = -A*lambda*lambda;
      const double Vtb = 1 - (1/2)*A*A*pow(lambda,4);

      complexd C2diag = (-7.*(xi_cc*std::conj(Vcs) + xi_tc*std::conj(Vts))*(Vcb*std::conj(xi_cc) + Vtb*std::conj(xi_tc)))/(72.*sqrt(2)*sminputs.GF*pow(mHp,2)*Vtb*Vts);

      complexd C2mix = -(mC*(xi_bb*std::conj(Vcb) + xi_sb*std::conj(Vcs))*(xi_cc*std::conj(Vcs) + xi_tc*std::conj(Vts))*(3 + 4*log(pow(mBmB,2)/pow(mHp,2))))/(12.*sqrt(2)*sminputs.GF*mBmB*pow(mHp,2)*Vtb*Vts);

      // TODO: Is this only for muon flavour?
      result.mu = C2diag + C2mix;
    }

    /// Delta C7 in the THDM
    void THDM_DeltaC7(WilsonCoefficient &result)
    {
      using namespace Pipes::THDM_DeltaC7;
      Spectrum spectrum = *Dep::THDM_spectrum;
      SMInputs sminputs = *Dep::SMINPUTS;
      const double lambda = Dep::SMINPUTS->CKM.lambda;
      const double A = Dep::SMINPUTS->CKM.A;
      const double mT = Dep::SMINPUTS->mT;
      const double mBmB = Dep::SMINPUTS->mBmB;
      const double mC = Dep::SMINPUTS->mCmC;
      double mHp = spectrum.get(Par::Pole_Mass,"H+");

      auto xiU = get_xiF(spectrum,'u');
      auto xiD = get_xiF(spectrum,'d');
      const complexd xi_tt     = (1/sqrt(2))*xiU[t][t];
      const complexd xi_ct     = (1/sqrt(2))*xiU[c][t];
      const complexd xi_bb     = (1/sqrt(2))*xiD[b][b];
      const complexd xi_sb     = (1/sqrt(2))*xiD[s][b];
      const complexd xi_tc     = (1/sqrt(2))*xiU[t][c];
      const complexd xi_cc     = (1/sqrt(2))*xiU[c][c];

      const double Vcs = 1 - (1/2)*lambda*lambda;
      const double Vcb = A*lambda*lambda;
      const double Vts = -A*lambda*lambda;
      const double Vtb = 1 - (1/2)*A*A*pow(lambda,4);

      //Mixing with four-fermion operators from JHEP06(2019)119
      complexd C2diag = (-7.*(xi_cc*std::conj(Vcs) + xi_tc*std::conj(Vts))*(Vcb*std::conj(xi_cc) + Vtb*std::conj(xi_tc)))/(72.*sqrt(2)*sminputs.GF*pow(mHp,2)*Vtb*Vts);

      complexd C2mix = -(mC*(xi_bb*std::conj(Vcb) + xi_sb*std::conj(Vcs))*(xi_cc*std::conj(Vcs) + xi_tc*std::conj(Vts))*(3 + 4*log(pow(mBmB,2)/pow(mHp,2))))/(12.*sqrt(2)*sminputs.GF*mBmB*pow(mHp,2)*Vtb*Vts);
      // C7 from gamma penguins
      complexd C70 = (1/(sqrt(2)*std::real(Vtb*std::conj(Vts))*sminputs.GF*mHp*mHp))*((xi_ct*std::conj(Vcs) + xi_tt*std::conj(Vts))*
               (Vcb*std::conj(xi_ct) + Vtb*std::conj(xi_tt))*F7_1(pow(mT/mHp,2)))
               + (1/(sqrt(2)*std::real(Vtb*std::conj(Vts))*sminputs.GF*mHp*mBmB))*((Vtb*xi_bb + Vts*xi_sb)*
               (std::conj(Vcs)*std::conj(xi_ct) + std::conj(Vts)*std::conj(xi_tt))*F7_2(pow(mT/mHp,2)));

      // TODO: Is this only for muon flavour?
      result.mu = C70 + C2diag + C2mix;
    }

    /// Delta C8 in the THDM
    void THDM_DeltaC8(WilsonCoefficient &result)
    {
      using namespace Pipes::THDM_DeltaC8;
      Spectrum spectrum = *Dep::THDM_spectrum;
      SMInputs sminputs = *Dep::SMINPUTS;
      const double lambda = Dep::SMINPUTS->CKM.lambda;
      const double A = Dep::SMINPUTS->CKM.A;
      const double mT = Dep::SMINPUTS->mT;
      const double mBmB = Dep::SMINPUTS->mBmB;
      const double mC = Dep::SMINPUTS->mCmC;
      double mHp = spectrum.get(Par::Pole_Mass,"H+");

      auto xiU = get_xiF(spectrum,'u');
      auto xiD = get_xiF(spectrum,'d');
      const complexd xi_tt     = (1/sqrt(2))*xiU[t][t];
      const complexd xi_ct     = (1/sqrt(2))*xiU[c][t];
      const complexd xi_bb     = (1/sqrt(2))*xiD[b][b];
      const complexd xi_sb     = (1/sqrt(2))*xiD[s][b];
      const complexd xi_tc     = (1/sqrt(2))*xiU[t][c];
      const complexd xi_cc     = (1/sqrt(2))*xiU[c][c];

      const double Vcs = 1 - (1/2)*lambda*lambda;
      const double Vcb = A*lambda*lambda;
      const double Vts = -A*lambda*lambda;
      const double Vtb = 1 - (1/2)*A*A*pow(lambda,4);

      //Mixing with four-fermion operators from JHEP06(2019)119
      complexd C2diag = (-1.*(xi_cc*std::conj(Vcs) + xi_tc*std::conj(Vts))*(Vcb*std::conj(xi_cc) + Vtb*std::conj(xi_tc)))/(12.*sqrt(2)*sminputs.GF*pow(mHp,2)*Vtb*Vts);

      complexd C2mix = -(mC*(xi_bb*std::conj(Vcb) + xi_sb*std::conj(Vcs))*(xi_cc*std::conj(Vcs) + xi_tc*std::conj(Vts))*(3 + 2*log(pow(mBmB,2)/pow(mHp,2))))/(4.*sqrt(2)*sminputs.GF*mBmB*pow(mHp,2)*Vtb*Vts);
      // C8 from gluon penguins

      complexd C80 = (1/(sqrt(2)*std::real(Vtb*std::conj(Vts))*sminputs.GF*mHp*mHp))*((xi_ct*std::conj(Vcs) + xi_tt*std::conj(Vts))*
               (Vcb*std::conj(xi_ct) + Vtb*std::conj(xi_tt))*F7_3(pow(mT/mHp,2)))
               + (1/(sqrt(2)*std::real(Vtb*std::conj(Vts))*sminputs.GF*mHp*mBmB))*((Vtb*xi_bb + Vts*xi_sb)*
               (std::conj(Vcs)*std::conj(xi_ct) + std::conj(Vts)*std::conj(xi_tt))*F7_4(pow(mT/mHp,2)));

      // TODO: Is this only for muon flavour?
      result.mu = C80 + C2diag + C2mix;
    }

    /// Delta C2' in the THDM
    void THDM_DeltaC2p(WilsonCoefficient &result)
    {
      using namespace Pipes::THDM_DeltaC2p;

      // TODO: This one is not yet implemented
      result.mu = 0.;
    }

    /// Delta C7' in the THDM
    void THDM_DeltaC7p(WilsonCoefficient &result)
    {
      using namespace Pipes::THDM_DeltaC7p;
      Spectrum spectrum = *Dep::THDM_spectrum;
      SMInputs sminputs = *Dep::SMINPUTS;
      const double lambda = Dep::SMINPUTS->CKM.lambda;
      const double A = Dep::SMINPUTS->CKM.A;
      const double mT = Dep::SMINPUTS->mT;
      const double mBmB = Dep::SMINPUTS->mBmB;
      double mHp = spectrum.get(Par::Pole_Mass,"H+");

      auto xiU = get_xiF(spectrum,'u');
      auto xiD = get_xiF(spectrum,'d');
      const complexd xi_tt     = (1/sqrt(2))*xiU[t][t];
      const complexd xi_bb     = (1/sqrt(2))*xiD[b][b];
      const complexd xi_sb     = (1/sqrt(2))*xiD[s][b];
      const complexd xi_ct     = (1/sqrt(2))*xiU[c][t];

      const double Vts = -A*lambda*lambda;
      const double Vtb = 1 - (1/2)*A*A*pow(lambda,4);
      const double Vcb = A*lambda*lambda;

      complexd C7p0 =  (1/(sqrt(2)*std::real(Vtb*std::conj(Vts))*sminputs.GF*mHp*mHp))*(xi_sb*std::conj(Vtb))*(Vtb*xi_bb + Vts*xi_sb)*F7_1(pow(mT/mHp,2))
               +(1/(sqrt(2)*std::real(Vtb*std::conj(Vts))*sminputs.GF*mHp*mBmB))*(Vtb*xi_sb)*(Vcb*std::conj(xi_ct) + Vtb*std::conj(xi_tt))*F7_2(pow(mT/mHp,2));

      // TODO: Is this only for muon flavour?
      result.mu = C7p0;
    }

    /// Delta C8' in the THDM
    void THDM_DeltaC8p(WilsonCoefficient &result)
    {
      using namespace Pipes::THDM_DeltaC8p;
      Spectrum spectrum = *Dep::THDM_spectrum;
      SMInputs sminputs = *Dep::SMINPUTS;
      const double lambda = Dep::SMINPUTS->CKM.lambda;
      const double A = Dep::SMINPUTS->CKM.A;
      const double mT = Dep::SMINPUTS->mT;
      const double mBmB = Dep::SMINPUTS->mBmB;
      double mHp = spectrum.get(Par::Pole_Mass,"H+");

      auto xiU = get_xiF(spectrum,'u');
      auto xiD = get_xiF(spectrum,'d');
      const complexd xi_tt     = (1/sqrt(2))*xiU[t][t];
      const complexd xi_bb     = (1/sqrt(2))*xiD[b][b];
      const complexd xi_sb     = (1/sqrt(2))*xiD[s][b];
      const complexd xi_ct     = (1/sqrt(2))*xiU[c][t];
      const double Vts = -A*lambda*lambda;
      const double Vtb = 1 - (1/2)*A*A*pow(lambda,4);
      const double Vcb = A*lambda*lambda;

      complexd C8p0 =  (1/(sqrt(2)*std::real(Vtb*std::conj(Vts))*sminputs.GF*mHp*mHp))*(xi_sb*std::conj(Vtb))*(Vtb*xi_bb + Vts*xi_sb)*F7_3(pow(mT/mHp,2))
                 +(1/(sqrt(2)*std::real(Vtb*std::conj(Vts))*sminputs.GF*mHp*mBmB))*(Vtb*xi_sb)*(Vcb*std::conj(xi_ct) + Vtb*std::conj(xi_tt))*F7_4(pow(mT/mHp,2));

      // TODO: Is this only for muon flavour?
      result.mu = C8p0;
    }


    /// Delta C9 in the THDM
    void THDM_DeltaC9(WilsonCoefficient &result)
    {
      using namespace Pipes::THDM_DeltaC9;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      result.e = THDM_DeltaC_NP(9, e, e, sminputs, spectrum);
      result.mu = THDM_DeltaC_NP(9, mu, mu, sminputs, spectrum);
      result.tau = THDM_DeltaC_NP(9, tau, tau, sminputs, spectrum);
    }

    /// Delta C10 in the THDM
    void THDM_DeltaC10(WilsonCoefficient &result)
    {
      using namespace Pipes::THDM_DeltaC10;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      result.e = THDM_DeltaC_NP(10, e, e, sminputs, spectrum);
      result.mu = THDM_DeltaC_NP(10, mu, mu, sminputs, spectrum);
      result.tau = THDM_DeltaC_NP(10, tau, tau, sminputs, spectrum);
    }

    /// Delta C9' in the THDM
    void THDM_DeltaC9p(WilsonCoefficient &result)
    {
      using namespace Pipes::THDM_DeltaC9p;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      result.e = THDM_DeltaC_NP(11, e, e, sminputs, spectrum);
      result.mu = THDM_DeltaC_NP(11, mu, mu, sminputs, spectrum);
      result.tau = THDM_DeltaC_NP(11, tau, tau, sminputs, spectrum);
    }

    /// Delta C10' in the THDM
    void THDM_DeltaC10p(WilsonCoefficient &result)
    {
      using namespace Pipes::THDM_DeltaC10p;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      result.e = THDM_DeltaC_NP(12, e, e, sminputs, spectrum);
      result.mu = THDM_DeltaC_NP(12, mu, mu, sminputs, spectrum);
      result.tau = THDM_DeltaC_NP(12, tau, tau, sminputs, spectrum);
    }

    /// Delta CL for nunu processes in the THDM
    void THDM_DeltaCL(WilsonCoefficient &result)
    {
      using namespace Pipes::THDM_DeltaCL;

      // TODO: Implement this
      logger() << "THDM_DeltaCL has not been implemented yet" << EOM;
      result.mu = 0.;
    }

    /// Delta CR for nunu processes in the THDM
    void THDM_DeltaCR(WilsonCoefficient &result)
    {
      using namespace Pipes::THDM_DeltaCR;

      // TODO: Implement this
      logger() << "THDM_DeltaCR has not been implemented yet" << EOM;
      result.mu = 0.;
    }

    // TODO: Remove this
    /// Temporariy hacky likelihood for DeltaC9_mu
    void DeltaC9_mu_LogLikelihood(double &result)
    {
      using namespace Pipes::DeltaC9_mu_LogLikelihood;

      result = Stats::gaussian_loglikelihood(Dep::DeltaC9->mu.real(), -0.8, 0., 0.3, false);
    }

    ///@}
  }

}
