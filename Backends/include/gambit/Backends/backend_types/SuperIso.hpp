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
  int model; /* CMSSM=1, GMSB=2, AMSB=3 */
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
  double mass_c_pole,mass_b_1S,mass_b_pole,mtmt;
  int scheme_c_mass;
  double Lambda3,Lambda4,Lambda5,Lambda6; /* Lambda QCD */
  double alphasMZ_Lambda3,alphasMZ_Lambda4,alphasMZ_Lambda5,alphasMZ_Lambda6; /* alpha_s */

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

  /* b -> s gamma */
  double mu_G2_bsg,rho_D3_bsg,rho_LS3_bsg,mu_c_bsg;

  /* B->K* gamma */
  double T1_BKstar;

  /* B -> Kstar FF */
  double a0V_BKstar,a1V_BKstar,a2V_BKstar,MV_BKstar;
  double a0A1_BKstar,a1A1_BKstar,a2A1_BKstar,MA1_BKstar;
  double a0A12_BKstar,a1A12_BKstar,a2A12_BKstar,MA12_BKstar;
  double a0A0_BKstar,a1A0_BKstar,a2A0_BKstar,MA0_BKstar;
  double a0T1_BKstar,a1T1_BKstar,a2T1_BKstar,MT1_BKstar;
  double a0T2_BKstar,a1T2_BKstar,a2T2_BKstar,MT2_BKstar;
  double a0T23_BKstar,a1T23_BKstar,a2T23_BKstar,MT23_BKstar;

  /* Bs -> phi FF */
  double a0V_Bsphi,a1V_Bsphi,a2V_Bsphi,MV_Bsphi;
  double a0A1_Bsphi,a1A1_Bsphi,a2A1_Bsphi,MA1_Bsphi;
  double a0A12_Bsphi,a1A12_Bsphi,a2A12_Bsphi,MA12_Bsphi;
  double a0A0_Bsphi,a1A0_Bsphi,a2A0_Bsphi,MA0_Bsphi;
  double a0T1_Bsphi,a1T1_Bsphi,a2T1_Bsphi,MT1_Bsphi;
  double a0T2_Bsphi,a1T2_Bsphi,a2T2_Bsphi,MT2_Bsphi;
  double a0T23_Bsphi,a1T23_Bsphi,a2T23_Bsphi,MT23_Bsphi;

  /* B -> K FF */
  double a00_BK,a10_BK,a20_BK,a30_BK;
  double a0p_BK,a1p_BK,a2p_BK,DmBp_BK;
  double a0T_BK,a1T_BK,a2T_BK,DmBT_BK;

  /* B -> Kstar hadronic uncertainties */
  double hadrerrBKstar;
  std::complex<double> BtoKstarlow_ALperp_err_noq2,BtoKstarlow_ARperp_err_noq2,BtoKstarlow_ALpar_err_noq2,BtoKstarlow_ARpar_err_noq2,BtoKstarlow_AL0_err_noq2,BtoKstarlow_AR0_err_noq2,BtoKstarlow_At_err_noq2,BtoKstarlow_AS_err_noq2;
  std::complex<double> BtoKstarlow_ALperp_err_q2,BtoKstarlow_ARperp_err_q2,BtoKstarlow_ALpar_err_q2,BtoKstarlow_ARpar_err_q2,BtoKstarlow_AL0_err_q2,BtoKstarlow_AR0_err_q2,BtoKstarlow_At_err_q2,BtoKstarlow_AS_err_q2;
  std::complex<double> BtoKstarhigh_ALperp_err,BtoKstarhigh_ARperp_err,BtoKstarhigh_ALpar_err,BtoKstarhigh_ARpar_err,BtoKstarhigh_AL0_err,BtoKstarhigh_AR0_err,BtoKstarhigh_At_err,BtoKstarhigh_AS_err;

  /* B -> K hadronic uncertainties */
  double hadrerrBK;
  std::complex<double> BtoKlow_FV_err_noq2,BtoKlow_FA_err_noq2,BtoKlow_FS_err_noq2,BtoKlow_FP_err_noq2;
  std::complex<double> BtoKlow_FV_err_q2,BtoKlow_FA_err_q2,BtoKlow_FS_err_q2,BtoKlow_FP_err_q2;
  std::complex<double> BtoKhigh_FV_err,BtoKhigh_FA_err,BtoKhigh_FS_err,BtoKhigh_FP_err;

  /* Bs -> phi hadronic uncertainties */
  double hadrerrBsphi;
  std::complex<double> Bstophilow_ALperp_err_noq2,Bstophilow_ARperp_err_noq2,Bstophilow_ALpar_err_noq2,Bstophilow_ARpar_err_noq2,Bstophilow_AL0_err_noq2,Bstophilow_AR0_err_noq2,Bstophilow_At_err_noq2,Bstophilow_AS_err_noq2;
  std::complex<double> Bstophilow_ALperp_err_q2,Bstophilow_ARperp_err_q2,Bstophilow_ALpar_err_q2,Bstophilow_ARpar_err_q2,Bstophilow_AL0_err_q2,Bstophilow_AR0_err_q2,Bstophilow_At_err_q2,Bstophilow_AS_err_q2;
  std::complex<double> Bstophihigh_ALperp_err,Bstophihigh_ARperp_err,Bstophihigh_ALpar_err,Bstophihigh_ARpar_err,Bstophihigh_AL0_err,Bstophihigh_AR0_err,Bstophihigh_At_err,Bstophihigh_AS_err;

  /* B -> K* power correction implementation */
  int BKstar_implementation;

  std::complex<double> hplus0,hminus0,hplus1,hminus1,hplus2,hminus2,hzero0,hzero1,hzero2; /* hadronic parameters (nonfactorisable power corrections) */

  double real_alpha_perp0,real_alpha_perp1,real_alpha_perp2;
  double real_alpha_par0,real_alpha_par1,real_alpha_par2;
  double real_alpha_zero0,real_alpha_zero1;
  double imag_alpha_perp0,imag_alpha_perp1,imag_alpha_perp2;
  double imag_alpha_par0,imag_alpha_par1,imag_alpha_par2;
  double imag_alpha_zero0,imag_alpha_zero1;

  double DeltaC9_M1_q2bar,r1_M1,r2_M1;
  double DeltaC9_M2_q2bar,r1_M2,r2_M2;
  double DeltaC9_M3_q2bar,r1_M3,r2_M3;

  /* B->K* mu mu - likelihood or method of moments */
  int likelihoodBKstarmumu;

  /* B -> D parameters */
  double Delta_BD,rho_D2_BD,V1_1_BD;

  /* B -> D* parameters */
  double Delta_BDstar,rho_Dstar2_BDstar,R1_1_BDstar,R2_1_BDstar,R3_1_BDstar,V1_1_BDstar,hA1_1_BDstar;

  /* NP contributions to Wilson coefficients */
  std::complex<double> deltaC[31],deltaCp[31],deltaCQ[7],deltaCQp[7];

  /* Decay widths */
  int widthcalc; /* 0=none, 1=hdecay, 2=feynhiggs */
  double width_h0,width_H0,width_A0,width_H,width_Z,width_W,width_top,width_H03,width_A02;
  double width_gluino,width_t1,width_t2,width_b1,width_b2,width_ul,width_ur,width_dl,width_dr;
  double width_cl,width_cr,width_sl,width_sr,width_el,width_er,width_ml,width_mr,width_tau1,width_tau2,width_gravitino;
  double width_nuel,width_numl,width_nutaul,width_c1,width_c2,width_o1,width_o2,width_o3,width_o4,width_o5;

  /* 2HDM */
  int THDM_model;
  double lambda_u[4][4],lambda_d[4][4],lambda_l[4][4];

  /* NMSSMTools */
  int NMSSMcoll,NMSSMtheory,NMSSMups1S,NMSSMetab1S;

    /* SDECAY */
  double BRtbW,BRtbH,BRtt1o1,BRtt1o2,BRtt1o3,BRtt1o4,BRtt2o1,BRtt2o2,BRtt2o3,BRtt2o4;
  double BRgluinot1tbar,BRgluinot1bart,BRgluinodldbar,BRgluinodlbard,BRgluinodrdbar,BRgluinodrbard,BRgluinoulubar,BRgluinoulbaru,BRgluinourubar,BRgluinourbaru,BRgluinoslsbar,BRgluinoslbars,BRgluinosrsbar,BRgluinosrbars,BRgluinoclcbar,BRgluinoclbarc,BRgluinocrcbar,BRgluinocrbarc,BRgluinob1bbar,BRgluinob1barb,BRgluinob2bbar,BRgluinob2barb,BRgluinot2tbar,BRgluinot2bart,BRgluinoo1g,BRgluinoo2g,BRgluinoo3g,BRgluinoo4g,BRgluinoo1ddbar,BRgluinoo1uubar,BRgluinoo1ssbar,BRgluinoo1ccbar,BRgluinoo1bbbar,BRgluinoo1ttbar,BRgluinoo2ddbar,BRgluinoo2uubar,BRgluinoo2ssbar,BRgluinoo2ccbar,BRgluinoo2bbbar,BRgluinoo2ttbar,BRgluinoo3ddbar,BRgluinoo3uubar,BRgluinoo3ssbar,BRgluinoo3ccbar,BRgluinoo3bbbar,BRgluinoo3ttbar,BRgluinoo4ddbar,BRgluinoo4uubar,BRgluinoo4ssbar,BRgluinoo4ccbar,BRgluinoo4bbbar,BRgluinoo4ttbar,BRgluinoc1dubar,BRgluinoc1udbar,BRgluinoc1scbar,BRgluinoc1csbar,BRgluinoc1btbar,BRgluinoc1tbbar,BRgluinoc2dubar,BRgluinoc2udbar,BRgluinoc2scbar,BRgluinoc2csbar,BRgluinoc2btbar,BRgluinoc2tbbar,BRgluinot1barW,BRgluinot1W,BRgluinot1barH,BRgluinot1H;
  double BRt1o1t,BRt1o2t,BRt1o3t,BRt1o4t,BRt1c1b,BRt1c2b,BRt1o1c,BRt1o1u,BRt1gluinoc;
  double BRt2o1t,BRt2o2t,BRt2o3t,BRt2o4t,BRt2c1b,BRt2c2b,BRt2t1h,BRt2t1Z,BRt2b1W,BRt2o1c,BRt2o1u,BRt2gluinoc;
  double BRb1o1b,BRb1o2b,BRb1o3b,BRb1o4b,BRb1c1t,BRb1c2t,BRb1gluinob,BRb1t1W;
  double BRb2o1b,BRb2o2b,BRb2o3b,BRb2o4b,BRb2c1t,BRb2c2t,BRb2gluinob,BRb2b1h,BRb2b1Z,BRb2t1W,BRb2t2W;
  double BRulo1u,BRulo2u,BRulo3u,BRulo4u,BRulc1d,BRulc2d,BRulgluinou;
  double BRuro1u,BRuro2u,BRuro3u,BRuro4u,BRurc1d,BRurgluinou,BRurc2d;
  double BRdlo1d,BRdlo2d,BRdlo3d,BRdlo4d,BRdlc1u,BRdlc2u,BRdlgluinod;
  double BRdro1d,BRdro2d,BRdro3d,BRdro4d,BRdrgluinod,BRdrc1u,BRdrc2u;
  double BRclo1c,BRclo2c,BRclo3c,BRclo4c,BRclc1s,BRclc2s,BRclgluinoc;
  double BRcro1c,BRcro2c,BRcro3c,BRcro4c,BRcrc1s,BRcrgluinoc,BRcrc2s;
  double BRslo1s,BRslo2s,BRslo3s,BRslo4s,BRslc1c,BRslc2c,BRslgluinos;
  double BRsro1s,BRsro2s,BRsro3s,BRsro4s,BRsrgluinos,BRsrc1c,BRsrc2c;
  double BRelo1e,BRelo2e,BRelo3e,BRelo4e,BRelc1nue,BRelc2nue;
  double BRero1e,BRero2e,BRero3e,BRero4e,BRerc1nue,BRerc2nue;
  double BRmlo1m,BRmlo2m,BRmlo3m,BRmlo4m,BRmlc1num,BRmlc2num;
  double BRmro1m,BRmro2m,BRmro3m,BRmro4m,BRmrc1num,BRmrc2num;
  double BRtau1o1tau,BRtau1o2tau,BRtau1o3tau,BRtau1o4tau,BRtau1c1nutau,BRtau1c2nutau,BRtau1nutaulH,BRtau1nutaulW;
  double BRtau2o1tau,BRtau2o2tau,BRtau2o3tau,BRtau2o4tau,BRtau2c1nutau,BRtau2c2nutau,BRtau2tau1h,BRtau2tau1Z,BRtau2nutaulH,BRtau2nutaulW,BRtau2tau1H,BRtau2tau1A;
  double BRnuelo1nue,BRnuelo2nue,BRnuelo3nue,BRnuelo4nue,BRnuelc1e,BRnuelc2e;
  double BRnumlo1num,BRnumlo2num,BRnumlo3num,BRnumlo4num,BRnumlc1m,BRnumlc2m;
  double BRnutaulo1nutau,BRnutaulo2nutau,BRnutaulo3nutau,BRnutaulo4nutau,BRnutaulc1tau,BRnutaulc2tau,BRnutaultau1W,BRnutaultau1H,BRnutaultau2H,BRnutaultau2W;
  double BRc1o1W,BRc1tau1nutau,BRc1o1udbar,BRc1o1csbar,BRc1o1enue,BRc1o1mnum,BRc1o1taunutau,BRc1o2udbar,BRc1o2csbar,BRc1o2enue,BRc1o2mnum,BRc1o2taunutau,BRc1o3udbar,BRc1o3csbar,BRc1o3enue,BRc1o3mnum,BRc1o3taunutau,BRc1o4udbar,BRc1o4csbar,BRc1o4enue,BRc1o4mnum,BRc1o4taunutau,BRc1nuele,BRc1numlm,BRc1elnue,BRc1mlnum,BRc1tau2nutau,BRc1c1Z,BRc1c1h,BRc1nutaultau,BRc1o2W;
  double BRc2c1Z,BRc2o1W,BRc2o2W,BRc2c1h,BRc2nuele,BRc2numlm,BRc2nutaultau,BRc2elnue,BRc2mlnum,BRc2tau1nutau,BRc2tau2nutau;
  double BRo2o1Z,BRo2o1h,BRo2tau1taubar,BRo2tau1bartau,BRo2o1gamma,BRo2o1ubaru,BRo2o1dbard,BRo2o1cbarc,BRo2o1sbars,BRo2o1bbarb,BRo2o1tbart,BRo2o1ebare,BRo2o1mbarm,BRo2o1taubartau,BRo2o1nuebarnue,BRo2o1numbarnum,BRo2o1nutaubarnutau,BRo2c1ubard,BRo2c1dbaru,BRo2c1cbars,BRo2c1sbarc,BRo2c1tbarb,BRo2c1bbart,BRo2c1nuebare,BRo2c1nueebar,BRo2c1numbarm,BRo2c1nummbar,BRo2c1nutaubartau,BRo2c1nutautaubar,BRo2c2ubard,BRo2c2dbaru,BRo2c2cbars,BRo2c2sbarc,BRo2c2tbarb,BRo2c2bbart,BRo2c2nuebare,BRo2c2nueebar,BRo2c2numbarm,BRo2c2nummbar,BRo2c2nutaubartau,BRo2c2nutautaubar,BRo2elebar,BRo2elbare,BRo2erebar,BRo2erbare,BRo2mlmbar,BRo2mlbarm,BRo2mrmbar,BRo2mrbarm,BRo2tau2taubar,BRo2tau2bartau,BRo2nuelnuebar,BRo2nuelbarnue,BRo2numlnumbar,BRo2numlbarnum,BRo2nutaulnutaubar,BRo2nutaulbarnutau;
  double BRo3o1Z,BRo3o2Z,BRo3c1W,BRo3c1barW,BRo3o1h,BRo3o2h,BRo3elebar,BRo3elbare,BRo3erebar,BRo3erbare,BRo3mlmbar,BRo3mlbarm,BRo3mrmbar,BRo3mrbarm,BRo3tau1taubar,BRo3tau1bartau,BRo3tau2taubar,BRo3tau2bartau,BRo3nuelnuebar,BRo3nuelbarnue,BRo3numlnumbar,BRo3numlbarnum,BRo3nutaulnutaubar,BRo3nutaulbarnutau,BRo3o1gamma,BRo3o2gamma;
  double BRo4o1Z,BRo4o2Z,BRo4c1W,BRo4c1barW,BRo4o1h,BRo4o2h,BRo4elebar,BRo4elbare,BRo4erebar,BRo4erbare,BRo4mlmbar,BRo4mlbarm,BRo4mrmbar,BRo4mrbarm,BRo4tau1taubar,BRo4tau1bartau,BRo4tau2taubar,BRo4tau2bartau,BRo4nuelnuebar,BRo4nuelbarnue,BRo4numlnumbar,BRo4numlbarnum,BRo4nutaulnutaubar,BRo4nutaulbarnutau,BRo4o1gamma,BRo4o2gamma,BRo4o3gamma;
  double BRo5o1Z,BRo5o2Z,BRo5c1W,BRo5c1barW,BRo5o1h,BRo5o2h,BRo5elebar,BRo5elbare,BRo5erebar,BRo5erbare,BRo5mlmbar,BRo5mlbarm,BRo5mrmbar,BRo5mrbarm,BRo5tau1taubar,BRo5tau1bartau,BRo5tau2taubar,BRo5tau2bartau,BRo5nuelnuebar,BRo5nuelbarnue,BRo5numlnumbar,BRo5numlbarnum,BRo5nutaulnutaubar,BRo5nutaulbarnutau,BRo5o1gamma,BRo5o2gamma,BRo5o3gamma;

    /* HDECAY & FeynHiggs */
  double mass_h0SM,width_h0SM;
  double mass_H0SM,width_H0SM;
  double mass_A0SM,width_A0SM;
  double BRh0bb_SM,BRh0tautau_SM,BRh0WW_SM,BRh0gg_SM,BRh0gaga_SM,BRh0ZZ_SM;
  double BRH0bb_SM,BRH0tautau_SM,BRH0WW_SM,BRH0gg_SM,BRH0gaga_SM,BRH0ZZ_SM;
  double BRA0bb_SM,BRA0tautau_SM,BRA0WW_SM,BRA0gg_SM,BRA0gaga_SM,BRA0ZZ_SM;

  double BRh0bb,BRh0tautau,BRh0WW,BRh0gg,BRh0gaga,BRh0ZZ;
  double BRH0bb,BRH0tautau,BRH0WW,BRH0gg,BRH0gaga,BRH0ZZ;
  double BRA0bb,BRA0tautau,BRA0WW,BRA0gg,BRA0gaga,BRA0ZZ;
  double BRh0mumu,BRh0ss,BRh0cc,BRh0tt,BRh0gaZ;
  double BRh0n1n2,BRh0n1n3,BRh0n1n4,BRh0n2n3,BRh0n2n4,BRh0c1c1,BRh0c1c2,BRh0n1n1,BRh0n2n2;
  double BRH0mumu,BRH0ss,BRH0cc,BRH0tt,BRH0gaZ,BRH0hZ;
  double BRH0n1n2,BRH0n1n3,BRH0n1n4,BRH0n2n3,BRH0n2n4,BRH0c1c1,BRH0c1c2,BRH0n1n1,BRH0n2n2,BRH0hh;
  double BRA0mumu,BRA0ss,BRA0cc,BRA0tt,BRA0gaZ,BRA0hZ;
  double BRA0n1n2,BRA0n1n3,BRA0n1n4,BRA0n2n3,BRA0n2n4,BRA0c1c1,BRA0c1c2,BRA0n1n1,BRA0n2n2,BRA0hh;
  double BRHmunu,BRHtaunu,BRHub,BRHus,BRHcs,BRHcb,BRHtb,BRHWh,BRHWA,BRHc1n1,BRHc1n2,BRHc1n3,BRHc1n4,BRHc2n1,BRHc2n2;
  double BRh0mumu_SM,BRh0ss_SM,BRh0cc_SM,BRh0tt_SM,BRh0gaZ_SM;
  double BRh0stau1stau1,BRh0stau1stau2,BRh0stau2stau2;
  double BRH0stau1stau1,BRH0stau1stau2,BRH0stau2stau2;
  double BRA0stau1stau1,BRA0stau1stau2,BRA0stau2stau2;
  double BRh0b1b1,BRh0b1b2,BRh0b2b2;
  double BRH0b1b1,BRH0b1b2,BRH0b2b2;
  double BRA0b1b1,BRA0b1b2,BRA0b2b2;

  double BRH03bb,BRH03tautau,BRH03WW,BRH03gg,BRH03gaga,BRH03ZZ;
  double BRA02bb,BRA02tautau,BRA02WW,BRA02gg,BRA02gaga,BRA02ZZ;
  double BRH03mumu,BRH03ss,BRH03cc,BRH03tt,BRH03gaZ,BRH03hZ;
  double BRH03n1n2,BRH03n1n3,BRH03n1n4,BRH03n2n3,BRH03n2n4,BRH03c1c1,BRH03c1c2,BRH03n1n1,BRH03n2n2,BRH03hh;
  double BRA02mumu,BRA02ss,BRA02cc,BRA02tt,BRA02gaZ,BRA02hZ;
  double BRA02n1n2,BRA02n1n3,BRA02n1n4,BRA02n2n3,BRA02n2n4,BRA02c1c1,BRA02c1c2,BRA02n1n1,BRA02n2n2,BRA02hh;
  double BRH03stau1stau1,BRH03stau1stau2,BRH03stau2stau2;
  double BRA02stau1stau1,BRA02stau1stau2,BRA02stau2stau2;
  double BRH03b1b1,BRH03b1b2,BRH03b2b2;
  double BRA02b1b1,BRA02b1b2,BRA02b2b2;

  /* For chi2 calculation with flavour observables */
  double log_mu_W_mass_W,log_mu_b_mass_b,log_mu_spec_lambda_h_mass_b;
  double bsgamma_rand;
  double BRBXsmumu_lowq2_rand,BRBXsmumu_highq2_rand,BRBXsmumu_full_rand;
  double BRBXsee_lowq2_rand,BRBXsee_highq2_rand,BRBXsee_full_rand;
  double BRBXstautau_lowq2_rand,BRBXstautau_highq2_rand,BRBXstautau_full_rand;

  char nuisance_values[100],nuisance_corr[100],exp_values[100],exp_corr[100],exp_values_mom[100],exp_corr_mom[100];

    // Extra members not in the SuperIso definition, but we can add them at the end of the class and the rest of the class will still
    // follow the memory layout that SuperIso expects.

    /* Wilson Coefficients */
    double Re_DeltaC7 = 0.;
    double Im_DeltaC7 = 0.;
    double Re_DeltaC8 = 0.;
    double Im_DeltaC8 = 0.;
    double Re_DeltaC9 = 0.;
    double Im_DeltaC9 = 0.;
    double Re_DeltaC10 = 0.;
    double Im_DeltaC10 = 0.;
    double Re_DeltaCQ1 = 0.;
    double Im_DeltaCQ1 = 0.;
    double Re_DeltaCQ2 = 0.;
    double Im_DeltaCQ2 = 0.;

    double Re_DeltaC7_mu = 0.;
    double Im_DeltaC7_mu = 0.;
    double Re_DeltaC9_mu = 0.;
    double Im_DeltaC9_mu = 0.;
    double Re_DeltaC10_mu = 0.;
    double Im_DeltaC10_mu = 0.;
    double Re_DeltaCQ1_mu = 0.;
    double Im_DeltaCQ1_mu = 0.;
    double Re_DeltaCQ2_mu = 0.;
    double Im_DeltaCQ2_mu = 0.;

    double Re_DeltaC7_e = 0.;
    double Im_DeltaC7_e = 0.;
    double Re_DeltaC9_e = 0.;
    double Im_DeltaC9_e = 0.;
    double Re_DeltaC10_e = 0.;
    double Im_DeltaC10_e = 0.;
    double Re_DeltaCQ1_e = 0.;
    double Im_DeltaCQ1_e = 0.;
    double Re_DeltaCQ2_e = 0.;
    double Im_DeltaCQ2_e = 0.;

    double Re_DeltaC7_tau = 0.;
    double Im_DeltaC7_tau = 0.;
    double Re_DeltaC9_tau = 0.;
    double Im_DeltaC9_tau = 0.;
    double Re_DeltaC10_tau = 0.;
    double Im_DeltaC10_tau = 0.;
    double Re_DeltaCQ1_tau = 0.;
    double Im_DeltaCQ1_tau = 0.;
    double Re_DeltaCQ2_tau = 0.;
    double Im_DeltaCQ2_tau = 0.;

    double Re_DeltaC7_Prime = 0.;
    double Im_DeltaC7_Prime = 0.;
    double Re_DeltaC8_Prime = 0.;
    double Im_DeltaC8_Prime = 0.;
    double Re_DeltaC9_Prime = 0.;
    double Im_DeltaC9_Prime = 0.;
    double Re_DeltaC10_Prime = 0.;
    double Im_DeltaC10_Prime = 0.;
    double Re_DeltaCQ1_Prime = 0.;
    double Im_DeltaCQ1_Prime = 0.;
    double Re_DeltaCQ2_Prime = 0.;
    double Im_DeltaCQ2_Prime = 0.;


  };

  struct indnuis
  /* structure for individual nuisance parameters */
  {
  double cent,dev; /* central value, standard deviation */
  int type; /* 1=gaussian distribution, 2= flat distribution */
  char* name;
  };

  struct nuisance
  /* structure containing nuisance parameters for the statistical analysis */
  {
    /* SM parameters */
  indnuis alphas_MZ,mass_b,mass_c,mass_s,mass_top_pole,mass_h0;
    /* CKM parameters */
  indnuis CKM_lambda,CKM_A,CKM_rhobar,CKM_etabar;
    /* Scales of Wilson coefficients */
  indnuis log_mu_W_mass_W,log_mu_b_mass_b;

    /* inclusive b -> s */
  indnuis BR_BXclnu_exp;
  /* b -> s gamma */
  indnuis mu_G2_bsg,rho_D3_bsg,rho_LS3_bsg,bsgamma_rand,mu_c_bsg;
  /* b -> s mu mu */
  indnuis BRBXsmumu_lowq2_rand,BRBXsmumu_highq2_rand,BRBXsmumu_full_rand;
  /* b -> s e e */
  indnuis BRBXsee_lowq2_rand,BRBXsee_highq2_rand,BRBXsee_full_rand;
  /* b -> s tau tau */
  indnuis BRBXstautau_lowq2_rand,BRBXstautau_highq2_rand,BRBXstautau_full_rand;

    /* B */
  indnuis f_B,lambda_Bp;
  /* B -> K* */
  indnuis f_Kstar_par,f_Kstar_perp,a1perp,a2perp,a1par,a2par;
  /* B -> K* gamma */
  indnuis T1_BKstar,log_mu_spec_lambda_h_mass_b;

    /* low */
    indnuis BtoKstarlow_ALperp_err_noq2,BtoKstarlow_ARperp_err_noq2,BtoKstarlow_ALpar_err_noq2,BtoKstarlow_ARpar_err_noq2,BtoKstarlow_AL0_err_noq2,BtoKstarlow_AR0_err_noq2,BtoKstarlow_At_err_noq2,BtoKstarlow_AS_err_noq2;
    indnuis BtoKstarlow_ALperp_err_q2,BtoKstarlow_ARperp_err_q2,BtoKstarlow_ALpar_err_q2,BtoKstarlow_ARpar_err_q2,BtoKstarlow_AL0_err_q2,BtoKstarlow_AR0_err_q2,BtoKstarlow_At_err_q2,BtoKstarlow_AS_err_q2;

    indnuis real_alpha_perp0,real_alpha_perp1,real_alpha_perp2,real_alpha_par0,real_alpha_par1,real_alpha_par2,real_alpha_zero0,real_alpha_zero1,imag_alpha_perp0,imag_alpha_perp1,imag_alpha_perp2,imag_alpha_par0,imag_alpha_par1,imag_alpha_par2,imag_alpha_zero0,imag_alpha_zero1;

    indnuis DeltaC9_M1_q2bar,r1_M1,r2_M1,DeltaC9_M2_q2bar,r1_M2,r2_M2,DeltaC9_M3_q2bar,r1_M3,r2_M3;

    /* high */
    indnuis BtoKstarhigh_ALperp_err,BtoKstarhigh_ARperp_err,BtoKstarhigh_ALpar_err,BtoKstarhigh_ARpar_err,BtoKstarhigh_AL0_err,BtoKstarhigh_AR0_err,BtoKstarhigh_At_err,BtoKstarhigh_AS_err;

  /* B -> K */
  indnuis f_K,a1K,a2K;

    /* Form factors B->K ll */
    indnuis a00_BK,a10_BK,a20_BK,a30_BK;
    indnuis a0p_BK,a1p_BK,a2p_BK;
    indnuis a0T_BK,a1T_BK,a2T_BK;

    /* low */
    indnuis BtoKlow_FV_err_noq2,BtoKlow_FA_err_noq2,BtoKlow_FS_err_noq2,BtoKlow_FP_err_noq2;
    indnuis BtoKlow_FV_err_q2,BtoKlow_FA_err_q2,BtoKlow_FS_err_q2,BtoKlow_FP_err_q2;

    /* high */
    indnuis BtoKhigh_FV_err,BtoKhigh_FA_err,BtoKhigh_FS_err,BtoKhigh_FP_err;

    /* Form factors B->K* ll */
    indnuis a0A0_BKstar,a1A0_BKstar,a2A0_BKstar;
    indnuis a0A1_BKstar,a1A1_BKstar,a2A1_BKstar;
    indnuis a0A12_BKstar,a1A12_BKstar,a2A12_BKstar;
    indnuis a0V_BKstar,a1V_BKstar,a2V_BKstar;
    indnuis a0T1_BKstar,a1T1_BKstar,a2T1_BKstar;
    indnuis a0T2_BKstar,a1T2_BKstar,a2T2_BKstar;
    indnuis a0T23_BKstar,a1T23_BKstar,a2T23_BKstar;

    /* Bs */
  indnuis life_Bs,f_Bs,lambda_Bsp;

  /* Bs -> phi */
  indnuis f_phi_par,f_phi_perp,a1phi_perp,a1phi_par,a2phi_perp,a2phi_par;

    /* low */
    indnuis Bstophilow_ALperp_err_noq2,Bstophilow_ARperp_err_noq2,Bstophilow_ALpar_err_noq2,Bstophilow_ARpar_err_noq2,Bstophilow_AL0_err_noq2,Bstophilow_AR0_err_noq2,Bstophilow_At_err_noq2,Bstophilow_AS_err_noq2;
    indnuis Bstophilow_ALperp_err_q2,Bstophilow_ARperp_err_q2,Bstophilow_ALpar_err_q2,Bstophilow_ARpar_err_q2,Bstophilow_AL0_err_q2,Bstophilow_AR0_err_q2,Bstophilow_At_err_q2,Bstophilow_AS_err_q2;

    /* high */
    indnuis Bstophihigh_ALperp_err,Bstophihigh_ARperp_err,Bstophihigh_ALpar_err,Bstophihigh_ARpar_err,Bstophihigh_AL0_err,Bstophihigh_AR0_err,Bstophihigh_At_err,Bstophihigh_AS_err;

    /* Form factors Bs->phi ll */
    indnuis a0A0_Bsphi,a1A0_Bsphi,a2A0_Bsphi;
    indnuis a0A1_Bsphi,a1A1_Bsphi,a2A1_Bsphi;
    indnuis a0A12_Bsphi,a1A12_Bsphi,a2A12_Bsphi;
    indnuis a0V_Bsphi,a1V_Bsphi,a2V_Bsphi;
    indnuis a0T1_Bsphi,a1T1_Bsphi,a2T1_Bsphi;
    indnuis a0T2_Bsphi,a1T2_Bsphi,a2T2_Bsphi;
    indnuis a0T23_Bsphi,a1T23_Bsphi,a2T23_Bsphi;
  };

  struct nuiscorr
  /* structure containing nuisance parameters for the statistical analysis */
  {
  char obs1[50],obs2[50];
  double value;
  };

  struct obsname
  /* structure for observable names */
  {
  char type[20]; /* BR, AFB, ... */
  char decay[20];

  double low; /* lower bin value */
  double high; /* higher bin value */

  char other[50];

  char name[100];
  };

  struct flhaparam
  /* structure containing all the scanned parameters from the FLHA file */
  {
  std::complex<double> dC7[3],dC8[3],dC9[3],dC10[3],dC9e[3],dC10e[3];
  std::complex<double> dC7p[3],dC8p[3],dC9p[3],dC10p[3],dC9pe[3],dC10pe[3];
  std::complex<double> C7[3],C8[3],C9[3],C10[3],C9e[3],C10e[3];
  std::complex<double> C7p[3],C8p[3],C9p[3],C10p[3],C9pe[3],C10pe[3];
  std::complex<double> C7SM[3],C8SM[3],C9SM[3],C10SM[3],C9eSM[3],C10eSM[3];
  std::complex<double> C7pSM[3],C8pSM[3],C9pSM[3],C10pSM[3],C9peSM[3],C10peSM[3];
  double Q;
  };

}

#endif /* defined __SuperIso_types_hpp__ */
