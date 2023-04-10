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

namespace Gambit
{

  namespace FlavBit
  {

    using std::vector;
    using complexd = std::complex<double>;
    enum {u=0, c=1, t=2, d=0, s=1, b=2, e=0, mu=1, tau=2};

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

      return -t*(-1 + t + log(1/t))/(8.*pow(t-1,2));
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

      const complexd xi_sb     = xiD[s][b];
      const complexd xi_bs     = xiD[b][s];
      const complexd xi_mumu   = xiE[mu][mu];
      const complexd xi_mutau  = xiE[mu][tau];
      const complexd xi_taumu  = xiE[tau][mu];
      const complexd xi_tautau = xiE[tau][tau];

      const double Vts = -A*lambda*lambda;
      const double Vtb = 1 - (1/2)*A*A*pow(lambda,4);

      Eigen::Matrix3cd xi_L, deltaij;

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

      const complexd xi_tt     = xiU[t][t];
      const complexd xi_cc     = xiU[c][c];
      const complexd xi_tc     = xiU[t][c];
      const complexd xi_ct     = xiU[c][t];
      const complexd xi_bb     = xiD[b][b];
      const complexd xi_ss     = xiD[s][s];
      const complexd xi_sb     = xiD[s][b];
      const complexd xi_bs     = xiD[b][s];
      const complexd xi_mumu   = xiE[mu][mu];
      const complexd xi_mutau  = xiE[mu][tau];
      const complexd xi_taumu  = xiE[tau][mu];
      const complexd xi_tautau = xiE[tau][tau];

      Eigen::Matrix3cd xi_L;

      xi_L << 0,       0,       0,
              0,  xi_mumu, xi_mutau,
              0, xi_taumu, xi_tautau;

      Eigen::Vector3cd xil_m1 = xi_L.col(l);
      Eigen::Vector3cd xil_m1conj = xil_m1.conjugate();
      Eigen::Vector3cd xilp_m2 = xi_L.col(lp);


      complexd C9_gamma = (1/(sqrt(2)*std::real(Vtb*std::conj(Vts))*sminputs.GF*mHp*mHp))*(xi_ct*std::conj(Vcs) + xi_tt*std::conj(Vts))*
                                      (Vcb*std::conj(xi_ct) + Vtb*std::conj(xi_tt))*DHp(pow(mT/mHp,2));
      complexd C9_Z = ((4*SW*SW-1)/(sqrt(2)*mW*mW*SW*SW*std::real(Vtb*std::conj(Vts))*sminputs.GF))*(xi_ct*std::conj(Vcs) + xi_tt*std::conj(Vts))*
                                  (Vcb*std::conj(xi_ct) + Vtb*std::conj(xi_tt))*CHp(pow(mT/mHp,2));
      complexd C9_Zmix = (mBmB*(4*SW*SW-1)*(xi_bb*std::conj(Vtb) + xi_sb*std::conj(Vts))*(Vcs*std::conj(xi_ct) + Vts*std::conj(xi_tt)))*CHpmix(pow(mT/mHp,2))/(16.*sqrt(2)*sminputs.GF*mT*pow(mW,2)*pow(SW,2)*Vtb*std::conj(Vts));

      complexd C9_Box = (1/(2*mW*mW*SW*SW*std::real(Vtb*std::conj(Vts))*pow(sminputs.GF,2)*mHp*mHp))*(xil_m1conj.dot(xilp_m2))*(std::conj(Vcs)*(Vcb*xi_cc*std::conj(xi_cc) + Vcb*xi_ct*std::conj(xi_ct) + Vtb*xi_cc*std::conj(xi_tc) + Vtb*xi_ct*std::conj(xi_tt)) + std::conj(Vts)*(Vcb*xi_tc*std::conj(xi_cc) + Vcb*xi_tt*std::conj(xi_ct) + Vtb*xi_tc*std::conj(xi_tc) + Vtb*xi_tt*std::conj(xi_tt)))*BHp(pow(mT/mHp,2));

      complexd C9_mub = (2/(4*sqrt(2)*27*std::real(Vtb*std::conj(Vts))*sminputs.GF*mHp*mHp))*(xi_cc*std::conj(Vcs) + xi_tc*std::conj(Vts))*
                                      (Vcb*std::conj(xi_cc) + Vtb*std::conj(xi_tc))*(19+12*log(pow(mBmB/mHp,2)));

      complexd C10_Ztotal = (1/(4*SW*SW-1))*(C9_Z+C9_Zmix);

      complexd C10_Box = C9_Box;

      complexd C9p_gamma = (1/(sqrt(2)*std::real(Vtb*std::conj(Vts))*sminputs.GF*mHp*mHp))*((Vtb*xi_bb + Vts*xi_sb)*(Vtb*xi_bs + Vts*xi_ss))*DHp(pow(mT/mHp,2));

      complexd C9p_Z = ((1-4*SW*SW)/(sqrt(2)*mW*mW*SW*SW*std::real(Vtb*std::conj(Vts))*sminputs.GF))*((Vtb*xi_bb + Vts*xi_sb)*(Vtb*xi_bs + Vts*xi_ss))*CHp(pow(mT/mHp,2));

      complexd C9p_Box = (1/(2*mW*mW*SW*SW*std::real(Vtb*std::conj(Vts))*pow(sminputs.GF,2)*mHp*mHp))*(xil_m1conj.dot(xilp_m2))*(((Vcb*xi_bb + Vcs*xi_sb)*std::conj(Vcb) + (Vtb*xi_bb + Vts*xi_sb)*std::conj(Vtb) + (Vub*xi_bb + Vus*xi_sb)*std::conj(Vub))*std::conj(xi_bs) + ((Vcb*xi_bb + Vcs*xi_sb)*std::conj(Vcs) + (Vtb*xi_bb + Vts*xi_sb)*std::conj(Vts) + (Vub*xi_bb + Vus*xi_sb)*std::conj(Vus))*std::conj(xi_ss))*BHpp(pow(mT/mHp,2));

      complexd C9p_mub = (2/(4*sqrt(2)*27*std::real(Vtb*std::conj(Vts))*sminputs.GF*mHp*mHp))*((Vcb*xi_bb + Vcs*xi_sb)*(Vcb*xi_bs + Vcs*xi_ss))*(19+12*log(pow(mBmB/mHp,2)));

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
    void THDM_DeltaCQ1(complexd &result)
    {
      using namespace Pipes::THDM_DeltaCQ1;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;
      const int l = 1, lp = 1;
      complexd DeltaCQ1=THDM_DeltaCQ_NP(1, l, lp, sminputs, spectrum);
      result = DeltaCQ1;
    }

    /// Delta CQ1' at tree level in the THDM
    void THDM_DeltaCQ1_Prime(complexd &result)
    {
      using namespace Pipes::THDM_DeltaCQ1_Prime;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;
      const int l = 1, lp = 1;

      result = THDM_DeltaCQ_NP(3, l, lp, sminputs, spectrum);
    }

    /// Delta CQ2 at tree level in the THDM
    void THDM_DeltaCQ2(complexd &result)
    {
      using namespace Pipes::THDM_DeltaCQ2;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;
      const int l = 1, lp = 1;

      result = THDM_DeltaCQ_NP(2, l, lp, sminputs, spectrum);
    }

    /// Delta CQ2' at tree level in the THDM
    void THDM_DeltaCQ2_Prime(complexd &result)
    {
      using namespace Pipes::THDM_DeltaCQ2_Prime;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;
      const int l = 1, lp = 1;

      result = THDM_DeltaCQ_NP(4, l, lp, sminputs, spectrum);
    }

    /// Delta CQ1_tautau at tree level in the THDM
    void THDM_DeltaCQ1_tautau(complexd &result)
    {
      using namespace Pipes::THDM_DeltaCQ1_tautau;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;
      const int l = 2, lp = 2;

      result = THDM_DeltaCQ_NP(1, l, lp, sminputs, spectrum);
    }

    /// Delta CQ1'_tautau at tree level in the THDM
    void THDM_DeltaCQ1_tautau_Prime(complexd &result)
    {
      using namespace Pipes::THDM_DeltaCQ1_tautau_Prime;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;
      const int l = 2, lp = 2;

      result = THDM_DeltaCQ_NP(3, l, lp, sminputs, spectrum);
    }

    /// Delta CQ2_tautau at tree level in the THDM
    void THDM_DeltaCQ2_tautau(complexd &result)
    {
      using namespace Pipes::THDM_DeltaCQ2_tautau;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;
      const int l = 2, lp = 2;

      result = THDM_DeltaCQ_NP(2, l, lp, sminputs, spectrum);
    }

    /// Delta CQ2'_tautau at tree level in the THDM
    void THDM_DeltaCQ2_tautau_Prime(complexd &result)
    {
      using namespace Pipes::THDM_DeltaCQ2_tautau_Prime;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;
      const int l = 2, lp = 2;

      result = THDM_DeltaCQ_NP(4, l, lp, sminputs, spectrum);
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
    void THDM_DeltaC2(complexd &result)
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
      const complexd xi_tc     = xiU[t][c];
      const complexd xi_bb     = xiD[b][b];
      const complexd xi_sb     = xiD[s][b];
      const complexd xi_cc     = xiU[c][c];

      const double Vcs = 1 - (1/2)*lambda*lambda;
      const double Vcb = A*lambda*lambda;
      const double Vts = -A*lambda*lambda;
      const double Vtb = 1 - (1/2)*A*A*pow(lambda,4);

      complexd C2diag = (-7.*(xi_cc*std::conj(Vcs) + xi_tc*std::conj(Vts))*(Vcb*std::conj(xi_cc) + Vtb*std::conj(xi_tc)))/(72.*sqrt(2)*sminputs.GF*pow(mHp,2)*Vtb*Vts);

      complexd C2mix = -(mC*(xi_bb*std::conj(Vcb) + xi_sb*std::conj(Vcs))*(xi_cc*std::conj(Vcs) + xi_tc*std::conj(Vts))*(3 + 4*log(pow(mBmB,2)/pow(mHp,2))))/(12.*sqrt(2)*sminputs.GF*mBmB*pow(mHp,2)*Vtb*Vts);

      result = C2diag + C2mix;
    }

    /// Delta C7 in the THDM
    void THDM_DeltaC7(complexd &result)
    {
      using namespace Pipes::THDM_DeltaC7;
      Spectrum spectrum = *Dep::THDM_spectrum;
      SMInputs sminputs = *Dep::SMINPUTS;
      const double lambda = Dep::SMINPUTS->CKM.lambda;
      const double A = Dep::SMINPUTS->CKM.A;
      const double mT = Dep::SMINPUTS->mT;
      const double mBmB = Dep::SMINPUTS->mBmB;
      double mHp = spectrum.get(Par::Pole_Mass,"H+");

      auto xiU = get_xiF(spectrum,'u');
      auto xiD = get_xiF(spectrum,'d');
      const complexd xi_tt     = xiU[t][t];
      const complexd xi_ct     = xiU[c][t];
      const complexd xi_bb     = xiD[b][b];
      const complexd xi_sb     = xiD[s][b];

      const double Vcs = 1 - (1/2)*lambda*lambda;
      const double Vcb = A*lambda*lambda;
      const double Vts = -A*lambda*lambda;
      const double Vtb = 1 - (1/2)*A*A*pow(lambda,4);

      complexd C70 = (1/(sqrt(2)*std::real(Vtb*std::conj(Vts))*sminputs.GF*mHp*mHp))*((xi_ct*std::conj(Vcs) + xi_tt*std::conj(Vts))*
               (Vcb*std::conj(xi_ct) + Vtb*std::conj(xi_tt))*F7_1(pow(mT/mHp,2)))
               + (1/(sqrt(2)*std::real(Vtb*std::conj(Vts))*sminputs.GF*mHp*mBmB))*((Vtb*xi_bb + Vts*xi_sb)*
               (std::conj(Vcs)*std::conj(xi_ct) + std::conj(Vts)*std::conj(xi_tt))*F7_2(pow(mT/mHp,2)));

      result = C70;
    }

    /// Delta C8 in the THDM
    void THDM_DeltaC8(complexd &result)
    {
      using namespace Pipes::THDM_DeltaC8;
      Spectrum spectrum = *Dep::THDM_spectrum;
      SMInputs sminputs = *Dep::SMINPUTS;
      const double lambda = Dep::SMINPUTS->CKM.lambda;
      const double A = Dep::SMINPUTS->CKM.A;
      const double mT = Dep::SMINPUTS->mT;
      const double mBmB = Dep::SMINPUTS->mBmB;
      double mHp = spectrum.get(Par::Pole_Mass,"H+");

      auto xiU = get_xiF(spectrum,'u');
      auto xiD = get_xiF(spectrum,'d');
      const complexd xi_tt     = xiU[t][t];
      const complexd xi_ct     = xiU[c][t];
      const complexd xi_bb     = xiD[b][b];
      const complexd xi_sb     = xiD[s][b];

      const double Vcs = 1 - (1/2)*lambda*lambda;
      const double Vcb = A*lambda*lambda;
      const double Vts = -A*lambda*lambda;
      const double Vtb = 1 - (1/2)*A*A*pow(lambda,4);

      complexd C80 = (1/(sqrt(2)*std::real(Vtb*std::conj(Vts))*sminputs.GF*mHp*mHp))*((xi_ct*std::conj(Vcs) + xi_tt*std::conj(Vts))*
               (Vcb*std::conj(xi_ct) + Vtb*std::conj(xi_tt))*F7_3(pow(mT/mHp,2)))
               + (1/(sqrt(2)*std::real(Vtb*std::conj(Vts))*sminputs.GF*mHp*mBmB))*((Vtb*xi_bb + Vts*xi_sb)*
               (std::conj(Vcs)*std::conj(xi_ct) + std::conj(Vts)*std::conj(xi_tt))*F7_4(pow(mT/mHp,2)));

      result = C80;
    }

    /// Delta C7' in the THDM
    void THDM_DeltaC7_Prime(complexd &result)
    {
      using namespace Pipes::THDM_DeltaC7_Prime;
      Spectrum spectrum = *Dep::THDM_spectrum;
      SMInputs sminputs = *Dep::SMINPUTS;
      const double lambda = Dep::SMINPUTS->CKM.lambda;
      const double A = Dep::SMINPUTS->CKM.A;
      const double mT = Dep::SMINPUTS->mT;
      const double mBmB = Dep::SMINPUTS->mBmB;
      double mHp = spectrum.get(Par::Pole_Mass,"H+");

      auto xiU = get_xiF(spectrum,'u');
      auto xiD = get_xiF(spectrum,'d');
      const complexd xi_tt     = xiU[t][t];
      const complexd xi_bb     = xiD[b][b];
      const complexd xi_sb     = xiD[s][b];
      const complexd xi_ct     = xiU[c][t];

      const double Vts = -A*lambda*lambda;
      const double Vtb = 1 - (1/2)*A*A*pow(lambda,4);
      const double Vcb = A*lambda*lambda;

      complexd C7p0 =  (1/(sqrt(2)*std::real(Vtb*std::conj(Vts))*sminputs.GF*mHp*mHp))*(xi_sb*std::conj(Vtb))*(Vtb*xi_bb + Vts*xi_sb)*F7_1(pow(mT/mHp,2))
               +(1/(sqrt(2)*std::real(Vtb*std::conj(Vts))*sminputs.GF*mHp*mBmB))*(Vtb*xi_sb)*(Vcb*std::conj(xi_ct) + Vtb*std::conj(xi_tt))*F7_2(pow(mT/mHp,2));

      result = C7p0;
    }

    /// Delta C8' in the THDM
    void THDM_DeltaC8_Prime(complexd &result)
    {
      using namespace Pipes::THDM_DeltaC8_Prime;
      Spectrum spectrum = *Dep::THDM_spectrum;
      SMInputs sminputs = *Dep::SMINPUTS;
      const double lambda = Dep::SMINPUTS->CKM.lambda;
      const double A = Dep::SMINPUTS->CKM.A;
      const double mT = Dep::SMINPUTS->mT;
      const double mBmB = Dep::SMINPUTS->mBmB;
      double mHp = spectrum.get(Par::Pole_Mass,"H+");

      auto xiU = get_xiF(spectrum,'u');
      auto xiD = get_xiF(spectrum,'d');
      const complexd xi_tt     = xiU[t][t];
      const complexd xi_bb     = xiD[b][b];
      const complexd xi_sb     = xiD[s][b];
      const complexd xi_ct     = xiU[c][t];

      const double Vts = -A*lambda*lambda;
      const double Vtb = 1 - (1/2)*A*A*pow(lambda,4);
      const double Vcb = A*lambda*lambda;

      complexd C8p0 =  (1/(sqrt(2)*std::real(Vtb*std::conj(Vts))*sminputs.GF*mHp*mHp))*(xi_sb*std::conj(Vtb))*(Vtb*xi_bb + Vts*xi_sb)*F7_3(pow(mT/mHp,2))
                 +(1/(sqrt(2)*std::real(Vtb*std::conj(Vts))*sminputs.GF*mHp*mBmB))*(Vtb*xi_sb)*(Vcb*std::conj(xi_ct) + Vtb*std::conj(xi_tt))*F7_4(pow(mT/mHp,2));


      result = C8p0;
    }

    /// Delta C9 in the THDM
    void THDM_DeltaC9(complexd &result)
    {
      using namespace Pipes::THDM_DeltaC9;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;
      const int l = 1, lp = 1;

      result = THDM_DeltaC_NP(9, l, lp, sminputs, spectrum);
    }

    /// Delta C10 in the THDM
    void THDM_DeltaC10(complexd &result)
    {
      using namespace Pipes::THDM_DeltaC10;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;
      const int l = 1, lp = 1;

      result = THDM_DeltaC_NP(10, l, lp, sminputs, spectrum);
    }

    /// Delta C9' in the THDM
    void THDM_DeltaC9_Prime(complexd &result)
    {
      using namespace Pipes::THDM_DeltaC9_Prime;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;
      const int l = 1, lp = 1;

      result = THDM_DeltaC_NP(11, l, lp, sminputs, spectrum);
    }

    /// Delta C10' in the THDM
    void THDM_DeltaC10_Prime(complexd &result)
    {
      using namespace Pipes::THDM_DeltaC10_Prime;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;
      const int l = 1, lp = 1;

      result = THDM_DeltaC_NP(12, l, lp, sminputs, spectrum);
    }

    /// Delta C9 tautau in the THDM
    void THDM_DeltaC9_tautau(complexd &result)
    {
      using namespace Pipes::THDM_DeltaC9_tautau;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;
      const int l = 2, lp = 2;

      result = THDM_DeltaC_NP(9, l, lp, sminputs, spectrum);
    }

    /// Delta C10 tautau in the THDM
    void THDM_DeltaC10_tautau(complexd &result)
    {
      using namespace Pipes::THDM_DeltaC10_tautau;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;
      const int l = 2, lp = 2;

      result = THDM_DeltaC_NP(10, l, lp, sminputs, spectrum);
    }

    /// Delta C9' tautau in the THDM
    void THDM_DeltaC9_tautau_Prime(complexd &result)
    {
      using namespace Pipes::THDM_DeltaC9_tautau_Prime;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;
      const int l = 2, lp = 2;

      result = THDM_DeltaC_NP(11, l, lp, sminputs, spectrum);
    }

    /// Delta C10' tautau in the THDM
    void THDM_DeltaC10_tautau_Prime(complexd &result)
    {
      using namespace Pipes::THDM_DeltaC10_tautau_Prime;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;
      const int l = 2, lp = 2;

      result = THDM_DeltaC_NP(12, l, lp, sminputs, spectrum);
    }

    ///@}
  }
}
