//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Definitions of the container structure
///  for the SuperIso backend.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Nazila Mahmoudi
///          (FIXME @blah.edu)
///  \date 2013 Dec
///  \auther Marcin Chrzaszcz
///  \date 2016 Oct
///
///  *********************************************


#ifndef __SuperIso_types_hpp__
#define __SuperIso_types_hpp__

namespace Gambit
{

  struct parameters
  {
    int SM;
    int model; /* CMSSM=1, GMSB=2, AMSB=3, WC=4 */
    int generator; /* ISAJET=1, SOFTSUSY=3, SPHENO=4, SUSPECT=5, NMSSMTOOLS=6 */
    double Q; /* Qmax ; default = M_EWSB = sqrt(m_stop1*mstop2) */
    double m0,m12,tan_beta,sign_mu,A0; /* CMSSM parameters */
    double Lambda,Mmess,N5,cgrav,m32; /* AMSB, GMSB parameters */
    double mass_Z,mass_W,mass_b,mass_top_pole,mass_tau_pole; /* SM parameters */
    double inv_alpha_em,alphas_MZ,Gfermi,GAUGE_Q; /* SM parameters */
    double charg_Umix[3][3],charg_Vmix[3][3],stop_mix[3][3],sbot_mix[3][3],stau_mix[3][3],neut_mix[6][6],mass_neut[6],alpha; /* mass mixing matrices */
    double Min,M1_Min,M2_Min,M3_Min,At_Min,Ab_Min,Atau_Min,M2H1_Min,M2H2_Min,mu_Min,M2A_Min,tb_Min,mA_Min; /* optional input parameters at scale Min */
    double MeL_Min,MmuL_Min,MtauL_Min,MeR_Min,MmuR_Min,MtauR_Min; /* optional input parameters at scale Min */
    double MqL1_Min,MqL2_Min,MqL3_Min,MuR_Min,McR_Min,MtR_Min,MdR_Min,MsR_Min,MbR_Min; /* optional input parameters at scale Min */
    double N51,N52,N53,M2H1_Q,M2H2_Q; /* optional input parameters (N51...3: GMSB) */
    double mass_d,mass_u,mass_s,mass_c,mass_t,mass_e,mass_nue,mass_mu,mass_num,mass_tau,mass_nut; /* SM masses */
    double mass_gluon,mass_photon,mass_Z0; /* SM masses */
    double mass_h0,mass_H0,mass_A0,mass_H,mass_dnl,mass_upl,mass_stl,mass_chl,mass_b1,mass_t1; /* Higgs & superparticle masses */
    double mass_el,mass_nuel,mass_mul,mass_numl,mass_tau1,mass_nutl,mass_gluino,mass_cha1,mass_cha2; /* superparticle masses */
    double mass_dnr,mass_upr,mass_str,mass_chr,mass_b2,mass_t2,mass_er,mass_mur,mass_tau2; /* superparticle masses */
    double mass_nuer,mass_numr,mass_nutr,mass_graviton,mass_gravitino; /* superparticle masses */
    double gp,g2,gp_Q,g2_Q,g3_Q,YU_Q,yut[4],YD_Q,yub[4],YE_Q,yutau[4]; /* couplings */
    double HMIX_Q,mu_Q,tanb_GUT,Higgs_VEV,mA2_Q,MSOFT_Q,M1_Q,M2_Q,M3_Q; /* parameters at scale Q */
    double MeL_Q,MmuL_Q,MtauL_Q,MeR_Q,MmuR_Q,MtauR_Q,MqL1_Q,MqL2_Q,MqL3_Q,MuR_Q,McR_Q,MtR_Q,MdR_Q,MsR_Q,MbR_Q; /* masses at scale Q */
    double AU_Q,A_u,A_c,A_t,AD_Q,A_d,A_s,A_b,AE_Q,A_e,A_mu,A_tau; /* trilinear couplings */

    /* SLHA2 */
    int NMSSM,RV,CPV,FV;
    double mass_nutau2,mass_e2,mass_nue2,mass_mu2,mass_numu2,mass_d2,mass_u2,mass_s2,mass_c2;
    double CKM_lambda,CKM_A,CKM_rhobar,CKM_etabar;
    double PMNS_theta12,PMNS_theta23,PMNS_theta13,PMNS_delta13,PMNS_alpha1,PMNS_alpha2;
    double lambdaNMSSM_Min,kappaNMSSM_Min,AlambdaNMSSM_Min,AkappaNMSSM_Min,lambdaSNMSSM_Min,xiFNMSSM_Min,xiSNMSSM_Min,mupNMSSM_Min,mSp2NMSSM_Min,mS2NMSSM_Min,mass_H03,mass_A02,NMSSMRUN_Q,lambdaNMSSM,kappaNMSSM,AlambdaNMSSM,AkappaNMSSM,lambdaSNMSSM,xiFNMSSM,xiSNMSSM,mupNMSSM,mSp2NMSSM,mS2NMSSM; /* NMSSM parameters */
    double PMNSU_Q,CKM_Q,IMCKM_Q,MSE2_Q,MSU2_Q,MSD2_Q,MSL2_Q,MSQ2_Q,TU_Q,TD_Q,TE_Q;
    double CKM[4][4],IMCKM[4][4]; /* CKM matrix */
    double H0_mix[4][4],A0_mix[4][4]; /* Higgs mixing matrices */
    double sU_mix[7][7],sD_mix[7][7],sE_mix[7][7], sNU_mix[4][4]; /* mixing matrices */
    double sCKM_msq2[4][4],sCKM_msl2[4][4],sCKM_msd2[4][4],sCKM_msu2[4][4],sCKM_mse2[4][4]; /* super CKM matrices */
    double PMNS_U[4][4]; /* PMNS mixing matrices */
    double TU[4][4],TD[4][4],TE[4][4]; /* trilinear couplings */

    /* non-SLHA*/
    double mass_b_1S,mass_b_pole,mtmt;
    double Lambda5; /* Lambda QCD */

    /* Flavour constants */
    double f_B,f_Bs,f_Ds,f_D,fK_fpi,f_K;
    double f_Kstar_par,f_Kstar_perp;
    double f_phi_perp,f_phi_par,a1phi_perp,a2phi_perp,a1phi_par,a2phi_par;
    double m_B,m_Bs,m_Bd,m_pi,m_Ds,m_K0,m_K,m_Kstar0,m_Kstar,m_D0,m_D,m_Dstar0,m_Dstar,m_phi;
    double life_pi,life_K,life_B,life_Bs,life_Bd,life_D,life_Ds;
    double a1par,a2par,a1perp,a2perp,a1K,a2K;
    double zeta3A,zeta3V,wA10,deltatp,deltatm,deltatp_phi,deltatm_phi;
    double lambda_Bp,lambda_Bsp,rho1,lambda2;
    double BR_BXclnu_exp; /* Used in bsgamma.c and bsll.c */
    int fullFF; /* full or soft form factor approach */

    /* CKM matrix */
    std::complex<double> Vud,Vus,Vub,Vcd,Vcs,Vcb,Vtd,Vts,Vtb;

    /* 2HDM */
    int THDM_model;
    double lambda_u[4][4],lambda_d[4][4],lambda_l[4][4];

    /* NMSSMTools */
    int NMSSMcoll,NMSSMtheory,NMSSMups1S,NMSSMetab1S;

    /* Decay widths */
    double width_Z,width_W;

    // Extra members not in the SuperIso definition, but we can add them at the end of the class and the rest of the class will still
    // follow the memory layout that SuperIso expects.

    /* Wilson Coefficients */
    double Re_DeltaC7 = 0.;
    double Im_DeltaC7 = 0.;
    double Re_DeltaC9 = 0.;
    double Im_DeltaC9 = 0.;
    double Re_DeltaC10 = 0.;
    double Im_DeltaC10 = 0.;
    double Re_DeltaCQ1 = 0.;
    double Im_DeltaCQ1 = 0.;
    double Re_DeltaCQ2 = 0.;
    double Im_DeltaCQ2 = 0.;
  };

  /// This class holds all the B0 -> K*0 mumu observables
  struct Flav_KstarMuMu_obs
  {
    double BR;
    double AFB;
    double FL;
    double S3;
    double S4;
    double S5;
    double S7;
    double S8;
    double S9;
    double q2_min;
    double q2_max;
  };

}

#endif /* defined __SuperIso_types_hpp__ */
