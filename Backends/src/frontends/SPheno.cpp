//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend for SPheno 3.3.8 backend
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Tomas Gonzalo
///  \date 2016 Apr, May, June
///
///  *********************************************

#include "gambit/Backends/frontend_macros.hpp"
#include "gambit/Backends/frontends/SPheno.hpp"
#include "gambit/Elements/slhaea_helpers.hpp"
#include "gambit/Elements/spectrum_factories.hpp"
#include "gambit/Models/SimpleSpectra/MSSMSimpleSpec.hpp"
#include "gambit/Utils/version.hpp"

// Convenience functions (definition)
BE_NAMESPACE
{

  // Run SPheno
  int run_SPheno(Spectrum &spectrum, const Finputs &inputs)
  {
    Set_All_Parameters_0();

    ReadingData(inputs);

    *epsI = pow(10,-5);
    *deltaM = pow(10,-3);
    *CalcTBD = false;
    *ratioWoM = 0;


    Initialize_MSSM(*GenerationMixing, *id_gl, *id_ph, *id_Z, *id_W, *id_nu, *id_l, *id_d, *id_u, *id_grav);

    // Variables needed to get masses of sparticles
    Farray_Freal8_1_2 mChiPm;
    Farray_Freal8_1_2 mChiPm2;
    Farray_Freal8_1_4 mChi0;
    Farray_Freal8_1_4 mChi02;
    Farray_Freal8_1_2 mS0;
    Farray_Freal8_1_2 mS02;
    Farray_Freal8_1_2 mP0;
    Farray_Freal8_1_2 mP02;
    Farray_Freal8_1_2 mSpm;
    Farray_Freal8_1_2 mSpm2;
    Farray_Freal8_1_6 mSdown;
    Farray_Freal8_1_6 mSdown2;
    Farray_Freal8_1_6 mSup;
    Farray_Freal8_1_6 mSup2;
    Farray_Freal8_1_6 mSlepton;
    Farray_Freal8_1_6 mSlepton2;
    Farray_Freal8_1_3 mSneut;
    Farray_Freal8_1_3 mSneut2;
    Freal8 mGlu;

    CalculateSpectrum(*n_run, *delta_mass, *WriteOut, *kont, *tanb, *vevSM, mChiPm, *U, *V, mChi0, *N, mS0, mS02, *RS0, mP0, mP02, *RP0, mSpm, mSpm2, *RSpm, mSdown, mSdown2, *RSdown, mSup, mSup2, *RSup, mSlepton, mSlepton2, *RSlepton, mSneut, mSneut2, *RSneut, mGlu, *PhaseGlu, *gauge, *uL_L, *uL_R, *uD_L, *uD_R, *uU_L, *uU_R, *Y_l, *Y_d, *Y_u, *Mi, *A_l, *A_d, *A_u, *M2_E, *M2_L, *M2_D, *M2_Q, *M2_U, *M2_H, *mu, *B, *m_GUT);


    if(!*kont)
    {
      for(int i=1; i<=2; i++)
      {
        (*ChiPm)(i).m = mChiPm(i);
        (*ChiPm)(i).m2 = pow(mChiPm(i),2);
        (*S0)(i).m = mS0(i);
        (*S0)(i).m2 = mS02(i);
        (*P0)(i).m = mP0(i);
        (*P0)(i).m2 = mP02(i);
        (*Spm)(i).m = mSpm(i);
        (*Spm)(i).m2 = mSpm2(i);
      }
      for(int i=1; i<=3; i++)
      {
        (*Sneut)(i).m = mSneut(i);
        (*Sneut)(i).m2 = mSneut2(i);
      }
      for(int i=1; i<=4; i++)
      {
        (*Chi0)(i).m = mChi0(i);
        (*Chi0)(i).m2 = pow(mChi0(i),2);
      }
      for(int i=1; i<=6; i++)
      {
        (*Sdown)(i).m = mSdown(i);
        (*Sdown)(i).m2 = mSdown2(i);
        (*Sup)(i).m = mSup(i);
        (*Sup)(i).m2 = mSup2(i);
        (*Slepton)(i).m = mSlepton(i);
        (*Slepton)(i).m2 = mSlepton2(i);
      }
      Glu->m = mGlu;
      Glu->m2 = pow(mGlu,2);

      *Q_in = sqrt(GetRenormalizationScale());

      spectrum = Spectrum_Out(inputs.param);


      *BRBtosgamma = 0.0;
      *BtoSNuNu = 0.0;
      *BrBToSLL = 0.0;
      *DeltaMBd = 0.0;
      *DeltaMBs = 0.0;
      *Bs_ll = 0.0;
      *Bd_ll = 0.0;
      *BR_Bu_TauNu = 0.0;
      *R_Bu_TauNu = 0.0;

      *epsK = 0.0;
      *DeltaMK2 = 0.0;
      *K0toPi0NuNu = 0.0;
      *KptoPipNuNu = 0.0;

      *a_e = 0.0;
      *a_mu = 0.0;
      *a_tau = 0.0;
      *d_e = 0.0;
      *d_mu = 0.0;
      *d_tau = 0.0;
      *BrMutoEGamma = 0.0;
      *BrTautoEGamma = 0.0;
      *BrTautoMuGamma = 0.0;
      *BrMu3e = 0.0;
      *BrTau3e = 0.0;
      *BrTau3Mu = 0.0;
      *BR_Z_e_mu = 0.0;
      *BR_Z_e_tau = 0.0;
      *BR_Z_mu_tau = 0.0;
      *rho_parameter = 0.0;

      // TODO: Low energy constraints, uncomment if needed
      //Low_Energy_Constraints_MSSM(*Q_in, *gauge, *Y_l, *Y_d, *Y_u, *A_l, *A_d, *A_u, *Mi, *mu, *M2_E, *M2_L, *M2_D, *M2_Q, *M2_U, *M2_H, *B, *tanb_Q, mP02, mS02, mSpm2, *CKM, *kont, *GenerationMixing, *rho_parameter, *DeltaMBd, *BRBtosgamma, *Bs_ll, *Bd_ll, *BrBToSLL, *BtoSNuNu, *BR_Bu_TauNu, *R_Bu_TauNu, *epsK, *DeltaMK2, *K0toPi0NuNu, *KptoPipNuNu, *a_e, *a_mu, *a_tau, *d_e, *d_mu, *d_tau, *BrMutoEGamma, *BrTautoEGamma, *BrTautoMuGamma, *BrMu3e, *BrTau3e, *BrTau3Mu, *BR_Z_e_mu, *BR_Z_e_tau, *BR_Z_mu_tau);
      // reorder state identification if necessary
      // TODO: Swap Order

      // Calculation of the branching ratios and widths provided L_BR is set .TRUE. (default) and that the routine Sugra has finished correctly (kont.eq.0)
      // TODO: Branching ratios, uncomment if needed
      /*
      if(*L_BR and !*kont)
      {
        if(*HighScaleModel == "mSUGRA" or *HighScaleModel == "SUGRA")
        {
          CalculateBR_MSSM(*n_nu, *id_nu, *n_l, *id_l, *n_d, *id_d, *n_u, *id_u, *n_Z, *id_Z, *n_W, *id_W, *n_Snu, *n_Sle, *n_Sd, *n_Su, *n_N, *n_C, *n_g, *n_S0, *n_P0, *n_Spm, *id_grav, *id_gl, *id_ph, *gauge, *Glu, *PhaseGlu, *ChiPm, *U, *V, *Chi0, *N, *Sneut, *RSneut, *Slepton, *RSlepton, *Sup, *RSup, *Sdown, *RSdown, *uL_L, *uL_R, *uD_L, *uD_R, *uU_L, *uU_R, *S0, *RS0, *P0, *RP0, *Spm, *RSpm, *epsI, *deltaM, *CalcTBD, *ratioWoM, *Y_d, *A_d, *Y_l, *A_l, *Y_u, *A_u, *mu, *vevSM, *F_GMSB, *m32, *grav_fac);
        }
        else
        {
          // TODO: NMSSM, etc
        }
      }
      */

      // Calculation of the cross sections in e+ e- annihilation provided L_Cs is set .TRUE. (default) and that the routine Sugra has finished correctly (kont.eq.0).  In the case that the file CrossSections.in does not exist, the following default values are used: Ecms = 500 GeV, Pm = Pp = 0, ISR = .TRUE.
      // TODO: Cross sections, uncomment if needed
      /*
      if(*L_CS and !*kont)
      {
        for(int i=1; i<=3; i++)
          for(int j=1; j<=3; j++)
          {
            (*Ylp)(i,j).re = (*Y_l)(i,j).re / (*gauge)(2);
            (*Ylp)(i,j).im = (*Y_l)(i,j).im / (*gauge)(2);
          }
        // TODO: Ecms check
        Fstring<20> Tesla = "Tesla800";
        int p_max = 100;
        for(int i=1; i<=p_max; i++)
        {
          if((*Ecms)(i) != 0)
          {
            Farray_Freal8_1_6_1_6 SSup, SSdown, SSle;
            Farray_Freal8_1_4_1_4 SChi0;
            Farray_Freal8_1_3_1_3 SSn;
            Farray_Freal8_1_2_1_2 SC;
            Farray_Freal8_1_2 SS0, SSP;
            Freal8 SHp;
            CalculateCrossSectionsMSSM((*Ecms)(i), (*Pm)(i), (*Pp)(i), (*ISR)(i), (*Beam)(i), Tesla, mSup, *RSup, *mf_u, mSdown, *RSdown, *mf_d, mGlu, SSup, SSdown, mSlepton, *RSlepton, *Ylp, mSneut, *RSneut, SSle, SSn, mChiPm, *U, *V, mChi0, *N, SC, SChi0, mS0, *RS0, *vevSM, mP0, *RP0, mSpm, *RSpm, SS0, SSP, SHp);
            for(int j=1; j<=6; j++)
            {
              for(int k=1; k<=6; k++)
              {
                (*SigSup)(i,j,k) = SSup(j,k);
                (*SigSdown)(i,j,k) = SSdown(j,k);
                (*SigSle)(i,j,k) = SSle(j,k);
                if(j<=4 and k<=4)
                  (*SigChi0)(i,j,k) = SChi0(j,k);
                if(j<=3 and k<=3)
                  (*SigSn)(i,j,k) = SSn(j,k);
                if(j<=2 and k<=2)
                {
                  (*SigC)(i,j,k) = SC(j,k);
                }
              }
              if(j<=2)
              {
                (*SigS0)(i,j) = SS0(j);
                (*SigSP)(i,j,1) = SSP(j);
              }
            }
            (*SigHp)(i,1,1) = SHp;
          }
        }
      }
      */

    }

    if(*kont != 0)
      ErrorHandling(*kont);

    return *kont;

  }

  Spectrum Spectrum_Out(const std::map<str, safe_ptr<const double> >& input_Param)
  {

    SLHAstruct slha;

    Freal8 Q = sqrt(GetRenormalizationScale());

    // Spectrum generator information
    SLHAea_add_block(slha, "SPINFO");
    SLHAea_add(slha, "SPINFO", 1, "GAMBIT, using "+str(STRINGIFY(BACKENDNAME)));
    SLHAea_add(slha, "SPINFO", 2, gambit_version()+" (GAMBIT); "+str(STRINGIFY(VERSION))+" ("+str(STRINGIFY(BACKENDNAME))+")");

    // General information
    SLHAea_add_block(slha, "SPhenoINFO");
    if(*TwoLoopRGE)
      SLHAea_add(slha, "SPhenoINFO", 1, 2, "# using 2-loop RGES");
    else
      SLHAea_add(slha, "SPhenoINFO", 1, 1, "# using 1-loop RGES");
    if(*YukScen)
      SLHAea_add(slha, "SPhenoINFO", 2, 1, "# using running masses for boundary conditions at mZ");
    else
      SLHAea_add(slha, "SPhenoINFO", 2, 2, "# using pole masses for boundary conditions at mZ");

    // model information
    if(*HighScaleModel == "mSUGRA")
    {
      SLHAea_add_block(slha, "MODSEL");
      slha["MODSEL"][""] << 1 << 1 << "# mSUGRA model";
      if(*GenerationMixing)
        slha["MODSEL"][""] << 6 << 3 << "# switching on flavour violation";

      SLHAea_add_block(slha, "MINPAR");
      if(input_Param.find("M0") != input_Param.end())
        slha["MINPAR"][""] << 1 << *input_Param.at("M0") << "# m0";
      if(input_Param.find("M12") != input_Param.end())
        slha["MINPAR"][""] << 2 << *input_Param.at("M12") << "# m12";
      slha["MINPAR"][""] << 3 << *input_Param.at("TanBeta") << "# tanb at m_Z";
      slha["MINPAR"][""] << 4 << *input_Param.at("SignMu") << "# cos(phase_mu)";
      if(input_Param.find("A0") != input_Param.end())
        slha["MINPAR"][""] << 5 << *input_Param.at("A0") << "# A0";

    }

    if(*HighScaleModel == "SUGRA") // SUGRA
    {
      SLHAea_add_block(slha, "EXTPAR");
      if(input_Param.find("Qin") != input_Param.end())
        slha["EXTPAR"][""] << 0 << *input_Param.at("Qin") << "# scale Q where the parameters below are defined";
      if(input_Param.find("M1") != input_Param.end())
        slha["EXTPAR"][""] << 1 << *input_Param.at("M1") << "# M_1";
      if(input_Param.find("M2") != input_Param.end())
        slha["EXTPAR"][""] << 2 << *input_Param.at("M2") << "# M_2";
      if(input_Param.find("M3") != input_Param.end())
        slha["EXTPAR"][""] << 3 << *input_Param.at("M3") << "# M_3";
      if(input_Param.find("Au_33") != input_Param.end())
        slha["EXTPAR"][""] << 11 << *input_Param.at("Au_33") << "# A_t";
      if(input_Param.find("Ad_33") != input_Param.end())
        slha["EXTPAR"][""] << 12 << *input_Param.at("Ad_33") << "# A_b";
      if(input_Param.find("Ae_33") != input_Param.end())
        slha["EXTPAR"][""] << 13 << *input_Param.at("Ae_33") << "# A_l";
      if(input_Param.find("mHd2") != input_Param.end())
        slha["EXTPAR"][""] << 21 << *input_Param.at("mHd2") << "# m_Hd^2";
      if(input_Param.find("mHu2") != input_Param.end())
        slha["EXTPAR"][""] << 22 << *input_Param.at("mHd2") << "# m_Hu^2";
      if(input_Param.find("ml2_11") != input_Param.end())
        slha["EXTPAR"][""] << 31 << sqrt(*input_Param.at("ml2_11")) << "# M_(L,11)";
      if(input_Param.find("ml2_22") != input_Param.end())
        slha["EXTPAR"][""] << 32 << sqrt(*input_Param.at("ml2_22")) << "# M_(L,22)";
      if(input_Param.find("ml2_33") != input_Param.end())
        slha["EXTPAR"][""] << 33 << sqrt(*input_Param.at("ml2_33")) << "# M_(L,33)";
      if(input_Param.find("me2_11") != input_Param.end())
        slha["EXTPAR"][""] << 34 << sqrt(*input_Param.at("me2_11")) << "# M_(E,11)";
      if(input_Param.find("me2_22") != input_Param.end())
        slha["EXTPAR"][""] << 35 << sqrt(*input_Param.at("me2_22")) << "# M_(E,22)";
      if(input_Param.find("me2_33") != input_Param.end())
        slha["EXTPAR"][""] << 36 << sqrt(*input_Param.at("me2_33")) << "# M_(E,33)";
      if(input_Param.find("mq2_11") != input_Param.end())
        slha["EXTPAR"][""] << 41 << sqrt(*input_Param.at("mq2_11")) << "# M_(Q,11)";
      if(input_Param.find("mq2_22") != input_Param.end())
        slha["EXTPAR"][""] << 42 << sqrt(*input_Param.at("mq2_22")) << "# M_(Q,22)";
      if(input_Param.find("mq2_33") != input_Param.end())
        slha["EXTPAR"][""] << 43 << sqrt(*input_Param.at("mq2_33")) << "# M_(Q,33)";
      if(input_Param.find("mu2_11") != input_Param.end())
        slha["EXTPAR"][""] << 44 << sqrt(*input_Param.at("mu2_11")) << "# M_(U,11)";
      if(input_Param.find("mu2_22") != input_Param.end())
        slha["EXTPAR"][""] << 45 << sqrt(*input_Param.at("mu2_22")) << "# M_(U,22)";
      if(input_Param.find("mu2_33") != input_Param.end())
        slha["EXTPAR"][""] << 46 << sqrt(*input_Param.at("mu2_33")) << "# M_(U,33)";
      if(input_Param.find("md2_11") != input_Param.end())
        slha["EXTPAR"][""] << 47 << sqrt(*input_Param.at("md2_11")) << "# M_(D,11)";
      if(input_Param.find("md2_22") != input_Param.end())
        slha["EXTPAR"][""] << 48 << sqrt(*input_Param.at("md2_22")) << "# M_(D,22)";
      if(input_Param.find("md2_33") != input_Param.end())
        slha["EXTPAR"][""] << 49 << sqrt(*input_Param.at("md2_33")) << "# M_(D,33)";

    }

    // parameters + masses for SPheno.spc
    SLHAea_add_block(slha, "SMINPUTS");
    slha["SMINPUTS"][""] << 1 << 1.0 / Alpha_MSbar(*mZ, *mW) << "# alpha_em^-1(MZ)^MSbar";
    slha["SMINPUTS"][""] << 2 << *G_F << "# G_mu [GeV^-2]";
    slha["SMINPUTS"][""] << 3 << *AlphaS_mZ << "# alpha_s(MZ)^MSbar";
    slha["SMINPUTS"][""] << 4 << *mZ << "# m_Z(pole)";
    slha["SMINPUTS"][""] << 5 << (*mf_d)(3) << "# m_b(m_b), MSbar";
    slha["SMINPUTS"][""] << 6 << (*mf_u)(3) << "# m_t(pole)";
    slha["SMINPUTS"][""] << 7 << (*mf_l)(3) << "# m_tau(pole)";
    slha["SMINPUTS"][""] << 8 << (*mf_nu)(3) << "# m_nu_3";
    slha["SMINPUTS"][""] << 11 << (*mf_l)(1) << "# m_e(pole)";
    slha["SMINPUTS"][""] << 12 << (*mf_nu)(1) << "# m_nu_1";
    slha["SMINPUTS"][""] << 13 << (*mf_l)(2) << "# m_muon(pole)";
    slha["SMINPUTS"][""] << 14 << (*mf_nu)(2) << "# m_nu_2";
    slha["SMINPUTS"][""] << 21 << (*mf_d)(1) << "# m_d(2 GeV), MSbar";
    slha["SMINPUTS"][""] << 22 << (*mf_u)(1) << "# m_u(2 GeV), MSbar";
    slha["SMINPUTS"][""] << 23 << (*mf_d)(2) << "# m_s(2 GeV), MSbar";
    slha["SMINPUTS"][""] << 24 << (*mf_u)(2) << "# m_c(m_c), MSbar";

    SLHAea_add_block(slha, "MSL2");
    SLHAea_add_block(slha, "MSE2");
    SLHAea_add_block(slha, "MSQ2");
    SLHAea_add_block(slha, "MSU2");
    SLHAea_add_block(slha, "MSD2");

    for(int i=1; i<=3; i++)
      for(int j=1; j<=3; j++)
      {
        slha["MSL2"][""] << i << j << (*M2_L_0)(i,j).re << "# M_(L," << i << j << ")";
        slha["MSE2"][""] << i << j << (*M2_E_0)(i,j).re << "# M_(E," << i << j << ")";
        slha["MSQ2"][""] << i << j << (*M2_Q_0)(i,j).re << "# M_(Q," << i << j << ")";
        slha["MSU2"][""] << i << j << (*M2_U_0)(i,j).re << "# M_(U," << i << j << ")";
        slha["MSD2"][""] << i << j << (*M2_D_0)(i,j).re << "# M_(D," << i << j << ")";
     }

    SLHAea_add_block(slha, "TE");
    SLHAea_add_block(slha, "TU");
    SLHAea_add_block(slha, "TD");

    for(int i=1; i<=3; i++)
      for(int j=1; j<=3; j++)
      {
        slha["TE"][""] << i << j << (*A_l_0)(i,j).re << "# A_(E," << i << j << ")";
        slha["TU"][""] << i << j << (*A_u_0)(i,j).re << "# A_(U," << i << j << ")";
        slha["TD"][""] << i << j << (*A_d_0)(i,j).re << "# A_(D," << i << j << ")";
      }

    SLHAea_add_block(slha, "GAUGE", *m_GUT);
    slha["GAUGE"][""] << 1 << (*gauge_0)(1) << "# g'(M_GUT)^DRbar";
    slha["GAUGE"][""] << 2 << (*gauge_0)(2) << "# g(M_GUT)^DRbar";
    slha["GAUGE"][""] << 3 << (*gauge_0)(3) << "# g3(M_GUT)^DRbar";

    SLHAea_add_block(slha, "Yu", *m_GUT);
    SLHAea_add_block(slha, "Yd", *m_GUT);
    SLHAea_add_block(slha, "Ye", *m_GUT);

    for(int i=1; i<=3; i++)
      for(int j=1; j<=3; j++)
      {
        slha["Yu"][""] << i << j << (*Y_u_0)(i,j).re << "# Y_u(" << i << "," << j << ")(M_GUT)^DRbar";
        slha["Yd"][""] << i << j << (*Y_d_0)(i,j).re << "# Y_d(" << i << "," << j << "(M_GUT)^DRbar";
        slha["Ye"][""] << i << j << (*Y_l_0)(i,j).re << "# Y_e(" << i << "," << j << "(M_GUT)^DRbar";
      }

    SLHAea_add_block(slha, "GAUGE", Q);
    slha["GAUGE"][""] << 1 << (*gauge)(1) << "# g'(Q)^DRbar";
    slha["GAUGE"][""] << 2 << (*gauge)(2) << "# g(Q)^DRbar";
    slha["GAUGE"][""] << 3 << (*gauge)(3) << "# g3(Q)^DRbar";

    SLHAea_add_block(slha, "Yu", Q);
    SLHAea_add_block(slha, "Yd", Q);
    SLHAea_add_block(slha, "Ye", Q);

    for(int i=1; i<=3; i++)
      for(int j=1; j<=3; j++)
      {
        slha["Yu"][""] << i << j << (*Y_u)(i,j).re << "# Y_u(" << i << "," << j << ")(Q)^DRbar";
        slha["Yd"][""] << i << j << (*Y_d)(i,j).re << "# Y_d(" << i << "," << j << ")(Q)^DRbar";
        slha["Ye"][""] << i << j << (*Y_l)(i,j).re << "# Y_e(" << i << "," << j << ")(Q)^DRbar";
      }

    SLHAea_add_block(slha, "Au", Q);
    SLHAea_add_block(slha, "IMAu", Q);
    SLHAea_add_block(slha, "Ad", Q);
    SLHAea_add_block(slha, "IMAd", Q);
    SLHAea_add_block(slha, "Ae", Q);
    SLHAea_add_block(slha, "IMAe", Q);

    for(int i=1; i<=3; i++)
      for(int j=1; j<=3; j++)
      {
        if((*Y_u)(i,j).abs() > 0)
        {
          slha["Au"][""] << i << j << ((*A_u)(i,j)/(*Y_u)(i,j)).re << "# A_u" << i << "," << j << ")(Q)^DRbar";
          slha["IMAu"][""] << i << j << ((*A_u)(i,j)/(*Y_u)(i,j)).im << "# Im(A_u)(" << i << "," << j << ")(Q)^DRbar";
        }
        if((*Y_d)(i,j).abs() > 0)
        {
          slha["Ad"][""] << i << j << ((*A_d)(i,j)/(*Y_d)(i,j)).re << "# A_d(" << i << "," << j << ")(Q)^DRbar";
          slha["IMAd"][""] << i << j << ((*A_d)(i,j)/(*Y_d)(i,j)).im << "# Im(A_d)(" << i << "," << j << ")(Q)^DRbar";
        }
        if((*Y_l)(i,j).abs() > 0)
        {
          slha["Ae"][""] << i << j << ((*A_l)(i,j)/(*Y_l)(i,j)).re << "# A_e(" << i << "," << j << ")(Q)^DRbar";
          slha["IMAe"][""] << i << j << ((*A_l)(i,j)/(*Y_l)(i,j)).im << "# Im(A_e)(" << i << "," << j << ")(Q)^DRbar";
        }
      }

    SLHAea_add_block(slha, "MSOFT", Q);
    slha["MSOFT"][""] << 1 << (*Mi)(1).re << "# M_1";
    slha["MSOFT"][""] << 2 << (*Mi)(2).re << "# M_2";
    slha["MSOFT"][""] << 3 << (*Mi)(3).re << "# M_3";
    slha["MSOFT"][""] << 21 << (*M2_H)(1) << "# M^2_(H,d)";
    slha["MSOFT"][""] << 22 << (*M2_H)(2) << "# M^2_(H,u)";

    slha["MSOFT"][""] << 31 << sqrt((*M2_L)(1,1).re) << "# M_(L,11)";
    slha["MSOFT"][""] << 32 << sqrt((*M2_L)(2,2).re) << "# M_(L,22)";
    slha["MSOFT"][""] << 33 << sqrt((*M2_L)(3,3).re) << "# M_(L,33)";
    slha["MSOFT"][""] << 34 << sqrt((*M2_E)(1,1).re) << "# M_(E,11)";
    slha["MSOFT"][""] << 35 << sqrt((*M2_E)(2,2).re) << "# M_(E,22)";
    slha["MSOFT"][""] << 36 << sqrt((*M2_E)(3,3).re) << "# M_(E,33)";
    slha["MSOFT"][""] << 41 << sqrt((*M2_Q)(1,1).re) << "# M_(Q,11)";
    slha["MSOFT"][""] << 42 << sqrt((*M2_Q)(2,2).re) << "# M_(Q,22)";
    slha["MSOFT"][""] << 43 << sqrt((*M2_Q)(3,3).re) << "# M_(Q,33)";
    slha["MSOFT"][""] << 44 << sqrt((*M2_U)(1,1).re) << "# M_(U,11)";
    slha["MSOFT"][""] << 45 << sqrt((*M2_U)(2,2).re) << "# M_(U,22)";
    slha["MSOFT"][""] << 46 << sqrt((*M2_U)(3,3).re) << "# M_(U,33)";
    slha["MSOFT"][""] << 47 << sqrt((*M2_D)(1,1).re) << "# M_(D,11)";
    slha["MSOFT"][""] << 48 << sqrt((*M2_D)(2,2).re) << "# M_(D,22)";
    slha["MSOFT"][""] << 49 << sqrt((*M2_D)(3,3).re) << "# M_(D,33)";

    if((*Mi)(1).im != 0 or (*Mi)(2).im != 0 or (*Mi)(3).im != 0)
    {
      SLHAea_add_block(slha, "IMMSOFT", Q);
      slha["IMMSOFT"][""] << 1 << (*Mi)(1).im << "# M_1";
      slha["IMMSOFT"][""] << 2 << (*Mi)(2).im << "# M_2";
      slha["IMMSOFT"][""] << 3 << (*Mi)(3).im << "# M_3";
    }

    SLHAea_add_block(slha, "MASS");
    slha["MASS"][""] << 6 << (*mf_u)(3) << "# m_t(pole)";
    slha["MASS"][""] << 23 << *mZ << "# m_Z(pole)";
    slha["MASS"][""] << 24 << *mW << "# m_W(pole)";
    slha["MASS"][""] << 15 << (*mf_l)(3) << "# m_tau(pole)";

    slha["MASS"][""] << 25 << (*S0)(1).m << "# h0";
    slha["MASS"][""] << 35 << (*S0)(2).m << "# H0";
    slha["MASS"][""] << 36 << (*P0)(2).m << "# A0";
    slha["MASS"][""] << 37 << (*Spm)(2).m << "# H+";

    // squarks
    if(*GenerationMixing)
    {
      // TODO: GenerationMixing
    }
    else
    {
      if((*RSdown)(1,1).abs() > 0.5)
      {
        slha["MASS"][""] << 1000001 << (*Sdown)(1).m << "# ~d_L";
        slha["MASS"][""] << 2000001 << (*Sdown)(2).m << "# ~d_R";
      }
      else
      {
        slha["MASS"][""] << 1000001 << (*Sdown)(2).m << "# ~d_L";
        slha["MASS"][""] << 2000001 << (*Sdown)(1).m << "# ~d_R";
      }
      if((*RSup)(1,1).abs() > 0.5)
      {
        slha["MASS"][""] << 1000002 << (*Sup)(1).m << "# ~u_L";
        slha["MASS"][""] << 2000002 << (*Sup)(2).m << "# ~u_R";
      }
      else
      {
        slha["MASS"][""] << 1000002 << (*Sup)(2).m << "# ~u_L";
        slha["MASS"][""] << 2000002 << (*Sup)(1).m << "# ~u_R";
      }
      if((*RSdown)(3,3).abs() > 0.5)
      {
        slha["MASS"][""] << 1000003 << (*Sdown)(3).m << "# ~s_L";
        slha["MASS"][""] << 2000003 << (*Sdown)(4).m << "# ~s_R";
      }
      else
      {
        slha["MASS"][""] << 1000003 << (*Sdown)(4).m << "# ~s_L";
        slha["MASS"][""] << 2000003 << (*Sdown)(3).m << "# ~s_R";
      }
      if((*RSup)(3,3).abs() > 0.5)
      {
        slha["MASS"][""] << 1000004 << (*Sup)(3).m << "# ~c_L";
        slha["MASS"][""] << 2000004 << (*Sup)(4).m << "# ~c_R";
      }
      else
      {
        slha["MASS"][""] << 1000004 << (*Sup)(4).m << "# ~c_L";
        slha["MASS"][""] << 2000004 << (*Sup)(3).m << "# ~c_R";
      }
      slha["MASS"][""] << 1000005 << (*Sdown)(5).m << "# ~b_1";
      slha["MASS"][""] << 2000005 << (*Sdown)(6).m << "# ~b_2";
      slha["MASS"][""] << 1000006 << (*Sup)(5).m << "# ~t_1";
      slha["MASS"][""] << 2000006 << (*Sup)(6).m << "# ~t_2";

    }

    // sleptons
    if(*GenerationMixing)
    {
      // TODO: GenerationMixing
    }
    else
    {
      if((*RSlepton)(1,1).abs() > 0.5)
      {
        slha["MASS"][""] << 1000011 << (*Slepton)(1).m << "# ~e_L-";
        slha["MASS"][""] << 2000011 << (*Slepton)(2).m << "# ~e_R-";
      }
      else
      {
        slha["MASS"][""] << 1000011 << (*Slepton)(2).m << "# ~e_L-";
        slha["MASS"][""] << 2000011 << (*Slepton)(1).m << "# ~e_R-";
      }
      slha["MASS"][""] << 1000012 << (*Sneut)(1).m << "# ~nu_eL";
      if((*RSlepton)(3,3).abs() > 0.5)
      {
        slha["MASS"][""] << 1000013 << (*Slepton)(3).m << "# ~mu_L-";
        slha["MASS"][""] << 2000013 << (*Slepton)(4).m << "# ~mu_R-";
      }
      else
      {
        slha["MASS"][""] << 1000013 << (*Slepton)(4).m << "# ~mu_L-";
        slha["MASS"][""] << 2000013 << (*Slepton)(3).m << "# ~mu_R-";
      }
      slha["MASS"][""] << 1000014 << (*Sneut)(2).m << "# ~nu_muL";
      slha["MASS"][""] << 1000015 << (*Slepton)(5).m << "# ~tau_1-";
      slha["MASS"][""] << 2000015 << (*Slepton)(6).m << "# ~tau_2-";
      slha["MASS"][""] << 1000016 << (*Sneut)(3).m << "# ~nu_tauL";
    }

    // gauginos/higssinos
    slha["MASS"][""] << 1000021 << Glu->m << "# ~g";

    Farray_Freal8_1_4 mNr;
    Farray_Fcomplex16_1_4_1_4 Nr;

    for(int i=1; i<=4; i++)
    {
      Freal8 sum = 0;
      for(int j=1; j<=4; j++)
        sum += (*N)(i,j).re;
      if(sum == 0)
      {
        mNr(i) = -(*Chi0)(i).m;
        for(int j=1; j<=4; j++)
          Nr(i,j).re = (*N)(i,j).im;
      }
      else
      {
        mNr(i) = (*Chi0)(i).m;
        for(int j=1; j<=4; j++)
          Nr(i,j) = (*N)(i,j);
      }
    }
    slha["MASS"][""] << 1000022 << mNr(1) << "# ~chi_10";
    slha["MASS"][""] << 1000023 << mNr(2) << "# ~chi_20";
    slha["MASS"][""] << 1000025 << mNr(3) << "# ~chi_30";
    slha["MASS"][""] << 1000035 << mNr(4) << "# ~chi_40";
    slha["MASS"][""] << 1000024 << (*ChiPm)(1).m << "# ~chi_1+";
    slha["MASS"][""] << 1000037 << (*ChiPm)(2).m << "# ~chi_2+";

    // Mixing matrices
    SLHAea_add_block(slha, "ALPHA");
    slha["ALPHA"][""] << -asin((*RS0)(1,1)) << "# alpha";

    SLHAea_add_block(slha, "HMIX", Q);
    slha["HMIX"][""] << 1 << mu->re << "# mu";
    slha["HMIX"][""] << 2 << *tanb_Q << "# tan[beta](Q)";
    slha["HMIX"][""] << 3 << *vev_Q << "# v(Q)";
    slha["HMIX"][""] << 4 << *mA2_Q << "# m^2_A(Q)";
    slha["HMIX"][""] << 101 << B->re << "# Bmu DRBar";
    slha["HMIX"][""] << 102 << (*vevSM)(1) << "# vd DRBar";
    slha["HMIX"][""] << 103 << (*vevSM)(2) << "# vu DRBar";

    if(mu->im != 0)
    {
      SLHAea_add_block(slha, "IMHMIX", Q);
      slha["IMHMIX"][""] << 1 << mu->im << "# Im(mu)";
    }

    SLHAea_add_block(slha, "SCALARMIX");
    SLHAea_add_block(slha, "PSEUDOSCALARMIX");
    SLHAea_add_block(slha, "CHARGEMIX");
    for(int i=1; i<=2; i++)
      for(int j=1; j<=2; j++)
      {
        slha["SCALARMIX"][""] << i << j << (*RS0)(i,j) << "# ZH(" << i << "," << j << ")";
        slha["PSEUDOSCALARMIX"][""] << i << j << (*RP0)(i,j) << "# ZA(" << i << "," << j << ")";
        slha["CHARGEMIX"][""] << i << j << (*RSpm)(i,j).re << "# ZP(" << i << "," << j << ")";
      }

    if(*GenerationMixing)
    {
      // TODO: GenerationMixing
    }
    else
    {
      SLHAea_add_block(slha, "STOPMIX");
      for(int i=1; i<=2; i++)
        for(int j=1; j<=2; j++)
        {
          slha["STOPMIX"][""] << i << j << (*RSup)(i+4,j+4).re << "# R_st(" << i << "," << j << ")";
          if((*RSup)(i+4,j+4).im != 0)
          {
            SLHAea_check_block(slha, "IMSTOPMIX", i, true);
            slha["IMSTOPMIX"][""] << i << j << (*RSup)(i+4,j+4).im << "# Im(R_st)(" << i << "," << j << ")";
          }
        }

      SLHAea_add_block(slha, "SBOTMIX");
      for(int i=1; i<=2; i++)
        for(int j=1; j<=2; j++)
        {
          slha["SBOTMIX"][""] << i << j << (*RSdown)(i+4,j+4).re << "# R_sb(" << i << "," << j << ")";
          if((*RSdown)(i+4,j+4).im != 0)
          {
            SLHAea_check_block(slha, "IMSBOTMIX", i, true);
            slha["IMSBOTMIX"][""] << i << j << (*RSdown)(i+4,j+4).im << "# Im(R_sb)(" << i << "," << j << ")";
          }
        }

      SLHAea_add_block(slha, "STAUMIX");
      for(int i=1; i<=2; i++)
        for(int j=1; j<=2; j++)
        {
          slha["STAUMIX"][""] << i << j << (*RSlepton)(i+4,j+4).re << "# R_sta(" << i << "," << j << ")";
          if((*RSlepton)(i+4,j+4).im != 0)
          {
            SLHAea_check_block(slha, "IMSBOTMIX", i, true);
            slha["IMSBOTMIX"][""] << i << j << (*RSlepton)(i+4,j+4).im << "# Im(R_sta)(" << i << "," << j << ")";
          }
        }
    }

    SLHAea_add_block(slha, "NMIX");
    for(int i=1; i<=4; i++)
      for(int j=1; j<=4; j++)
      {
        slha["NMIX"][""] << i << j << Nr(i,j).re << "# N(" << i << j << ")";
        if(Nr(i,j).im != 0)
        {
          SLHAea_check_block(slha, "IMNMIX", i, true);
          slha["IMNMIX"][""] << i << j << Nr(i,j).im << "# Im(N)(" << i << j << ")";
        }
      }

    SLHAea_add_block(slha, "UMIX");
    for(int i=1; i<=2; i++)
      for(int j=1; j<=2; j++)
      {
        slha["UMIX"][""] << i << j << (*U)(i,j).re << "# U(" << i << j << ")";
        if((*U)(i,j).im != 0)
        {
          SLHAea_check_block(slha, "IMUMIX", i, true);
          slha["IMUMIX"][""] << i << j << (*U)(i,j).im << "# Im(U)(" << i << j << ")";
        }
      }


    SLHAea_add_block(slha, "VMIX");
    for(int i=1; i<=2; i++)
      for(int j=1; j<=2; j++)
      {
        slha["VMIX"][""] << i << j << (*V)(i,j).re << "# V(" << i << j << ")";
        if((*V)(i,j).im != 0)
        {
          SLHAea_check_block(slha, "IMVMIX", i, true);
          slha["IMVMIX"][""] << i << j << (*V)(i,j).im << "# Im(V)(" << i << j << ")";
        }
      }

    // TODO: Low Energy Observables

    // Block GAMBIT
    SLHAea_add_block(slha, "GAMBIT");
    slha["GAMBIT"][""] << 1 << *m_GUT << "# Input scale of (upper) boundary contidions, e.g. GUT scale";

    //Create Spectrum object
    static const Spectrum::mc_info mass_cut;
    static const Spectrum::mr_info mass_ratio_cut;
    Spectrum spectrum = spectrum_from_SLHAea<MSSMSimpleSpec, SLHAstruct>(slha,slha,mass_cut,mass_ratio_cut);

    // Add the high scale variable by hand
    spectrum.get_HE().set_override(Par::mass1, SLHAea::to<double>(slha.at("GAMBIT").at(1).at(1)), "high_scale", true);

    return spectrum;

  }

  // Function to read data from the Gambit inputs and fill SPheno internal variables
  void ReadingData(const Finputs &inputs)
  {

    // Set up options, same as BLOCK SPHENOINPUT

    // 1, Error_Level
    *ErrorLevel = inputs.options->getValueOrDef<Finteger>(-1, "ErrorLevel");
    // GAMBIT: keep error level always 0 (print every warning), let GAMBIT handle errors
    *ErrorLevel = 0;

    // 2, SPA_convention
    *SPA_convention = inputs.options->getValueOrDef<Flogical>(false, "SPA_convention");
    if(*SPA_convention)
    {
      Freal8 scale = 1E6;
      SetRGEScale(scale);
    }

    // 3, External_Spectrum
    // GAMBIT: no need for external spectrum options
    *External_Spectrum = false;
    *External_Higgs = false;

    // 4, Use_Flavour_States
    // GAMBIT: private variable, cannot import

    // 5, FermionMassResummation
    // GAMBIT: not covered
    *FermionMassResummation = true;

    // 6, Ynu_at_MR3, Fixed_Nu_Yukawas
    // GAMBIT: not covered
    *Ynu_at_MR3 = false;
    *Fixed_Nu_Yukawas = false;

    // 7, Only_1loop_Higgsmass
    // GAMBIT: not covered
    *Only_1loop_Higgsmass = false;

    // 8, Calculates Masses for extra scales if required, Calc_Mass
    // GAMBIT: not covered
    *Calc_Mass = false;

    // 9, Use old version of BoundaryEW, UseNewBoundaryEW
    // GAMBIT: not covered
    *UseNewBoundaryEW = true;

    // 10, use old version to calculate scale, UseNewScale
    // GAMBIT: not covered
    *UseNewScale = true;

    // 11, whether to calculate branching ratios or not, L_BR
    // TODO: Branching ratios, not covered yet
    //*L_BR = inputs.options->getValueOrDef<Flogical>(false, "L_BR");
    *L_BR = false;

    // 12, minimal value such that a branching ratio is written out, BRMin
    // TODO: Branching ratios, not covered yet
    //Freal8 BrMin = inputs.options->getValueOrDef<Freal8>(0.0, "BRMin");
    //if(BrMin > 0.0)
    //  SetWriteMinBr(BrMin);

    // 13, whether the output of h-> V V* should be folded with branching ratios of the V*,
    // BR_Higgs_with_offshell_V
    // GAMBIT: private variable, cannot import

    // 21, whether to calculate cross sections or not, L_CS
    // TODO: Cross sections, not covered yet
    //*L_CS = inputs.options->getValueOrDef<Flogical>(false, "L_CS");
    //*L_CS = false;

    // 22, CMS energy, Ecms
    // TODO: Perhaps there is the option of setting more than one Ecms
    // TODO: Cross sections, not covered yet
    //static  int p_max = 100;
    //static Finteger p_act = 0;
    //p_act ++;
    //if(p_act <= p_max)
    //  (*Ecms)(p_act) = inputs.options->getValueOrDef<Freal8>(0.0, "Ecms");
    //else
    //  backend_error().raise(LOCAL_INFO, "The number of required points for the calculation of cross sections exceeds the maximum");

    // 23, polarisation of incoming e- beam, Pm
    // TODO: Cross sections, not covered yet
    //if(p_act <= p_max)
    //  (*Pm)(p_act) = inputs.options->getValueOrDef<Freal8>(0.0, "Pm");
    //if((*Pm)(p_act) > 1)
    //{
    //  backend_error().raise(LOCAL_INFO, "e- beam polarisation has to be between -1 and 1");
    //  (*Pm)(p_act) = 0;
    //}

    // 24, polarisation of incoming e+ beam, Pp
    // TODO: Cross sections, not covered yet
    //if(p_act <= p_max)
    //  (*Pp)(p_act) = inputs.options->getValueOrDef<Freal8>(0.0, "Pp");
    //if((*Pp)(p_act) > 1)
    //{
    //  backend_error().raise(LOCAL_INFO, "e+ beam polarisation has to be between -1 and 1");
    //  (*Pp)(p_act) = 0;
    //}

    // 25, caluclate initial state radiation, ISR
    // TODO: Cross sections, not covered yet
    //if(p_act <= p_max)
    //  (*ISR)(p_act) = inputs.options->getValueOrDef<Flogical>(false, "ISR");
    //

    // 26, minimal value such that a cross section is written out, SigMin
    // TODO: Cross sections, not covered yet
    //*Freal8 SigMin = inputs.options->getValueOrDef<Freal8>(0.0, "SigMin");
    //if(SigMin > 0.0)
    //  SetWriteMinSig(SigMin);

    // 31, setting a fixed GUT scale, GUTScale
    Freal8 GUTScale = inputs.options->getValueOrDef<Freal8>(0.0, "GUTScale");
    if(GUTScale > 0.0)
       SetGUTScale(GUTScale);

    // 32, requires strict unification, StrictUnification
    Flogical StrictUnification = inputs.options->getValueOrDef<Flogical>(false, "StrictUnification");
    if(StrictUnification)
      SetStrictUnification(StrictUnification);

    // 34, precision of mass calculation, delta_mass
    *delta_mass = inputs.options->getValueOrDef<Freal8>(0.00001, "delta_mass");

    // 35, maximal number of iterations, n_run
    *n_run = inputs.options->getValueOrDef<Finteger>(40, "n_run");

    // 36, write out debug information, WriteOut
    // GAMBIT: no write out, all debug info is handled by GAMBIT
    *WriteOut = false;

    // 37, if = 1 -> CKM through V_u, if = 2 CKM through V_d, YukawaScheme
    // GAMBIT: not covered

    // 38, set looplevel of RGEs, TwoLoopRGE
    *TwoLoopRGE = inputs.options->getValueOrDef<Flogical>(true, "TwoLoopRGE");

    // 39, write additional SLHA1 file, Write_SLHA1
    // GABMIT: Always false, no file output
    *Write_SLHA1 = false;

    // 40, alpha(0), Alpha
    Freal8 alpha = 1.0/137.035999074;
    *Alpha = inputs.options->getValueOrDef<Freal8>(alpha,"Alpha");

    // 41, Z-boson width, gamZ
    *gamZ = inputs.options->getValueOrDef<Freal8>(2.49,"gamZ");

    // 42, W-boson width, gamW
    *gamW = inputs.options->getValueOrDef<Freal8>(2.06,"gamW");

    // 80, exit for sure with non-zero value if problem occurs, Non_Zero_Exit
    // GAMBIT: never brute exit, let GAMBIT do a controlled exit
    *Non_Zero_Exit = false;

    // 81, quick and dirty way to implement model by Suchita Kulkarni, Model_Suchita
    // GAMBIT: not covered
    *Model_Suchita = false;

    // 90, add R-parity at low energies, Add_RParity
    // TODO: RParity, not covered yet
    //*Add_RParity = inputs.options->getValueOrDef<Flogical>(false, "Add_RParity");
    *Add_RParity = false;

    // 91, fit RP parameters such that neutrino data are ok, L_Fit_RP_Parameters
    // TODO: RParity, not covered yet
    //*L_Fit_RP_Parameters = inputs.options->getValueOrDef<Flogical>(false, "L_Fit_RP_Parameters");
    *L_Fit_RP_Parameters = false;

    // 92, for Pythia input, L_RP_Pythia
    // GAMBIT: private variable, cannot import

    // 93, calculates cross section in case of RP, only partially implemented, L_CSrp
    // TODO: RParity and Cross Sections, not covered yet
    //*L_CSrp = inputs.options->getValueOrDef<Flogical>(false, "L_CSrp");
    *L_CSrp = false;

    // 94, io_RP
    // GAMBIT: private variable, cannot import

    // 99, MADGraph output style, some additional information
    // GAMBIT: always false, no file output, private variable, cannot import

    // 100, use bsstep instead of rkqs, Use_bsstep_instead_of_rkqs
    Flogical bsstep = inputs.options->getValueOrDef<Flogical>(false, "Use_bsstep_instead_of_rkqs");
    if(bsstep)
      Set_Use_bsstep_instead_of_rkqs(bsstep);

    // 101, use rzextr instead of pzextr, Use_rzextr_instead_of_pzextr
    Flogical rzextr = inputs.options->getValueOrDef<Flogical>(false, "Use_rzextr_instead_of_pzextr");
    if(rzextr)
      Set_Use_rzextr_instead_of_pzextr(rzextr);

    // 110, write ouput for LHC observables, LWrite_LHC_Observables
    // GAMBIT: private variable, cannot import


    InitializeStandardModel(inputs.sminputs);
    InitializeLoopFunctions();

    //*ErrorLevel = -1;
    *GenerationMixing = false;
    *L_BR = false;
    *L_CS = false;

    Set_All_Parameters_0();

    // necessary to exclude right handed neutrinos from RGEs
    // is set to positive in the corresponding model
    *MNuR = -1E-9;

    // take highest precision, will be change at a later stage (already taken from SPHENOINPUT
    *TwoLoopRGE = true;

    // these variables are only used in GMSB and will be set correctly below
    *F_GMSB = 1E12;
    *m32 = 1E10;

    *kont = 0;

    // Block SMINPUTS
    // Already in InitializeStandardModel

    // Block MINPAR
    if(*HighScaleModel == "mSUGRA")
    {
      // M0
      if(inputs.param.find("M0") != inputs.param.end())
      {
        for(int i=1; i<=3; i++)
          (*M2D_0_sckm)(i,i) = pow(*inputs.param.at("M0"),2);
        *M2E_0_pmns = *M2D_0_sckm;
        *M2L_0_pmns = *M2D_0_sckm;
        *M2_R_0 = *M2D_0_sckm;
        *M2Q_0_sckm = *M2D_0_sckm;
        *M2U_0_sckm = *M2D_0_sckm;
        for(int i=1; i<=2; i++)
          (*M2_H_0)(i) = pow(*inputs.param.at("M0"),2);
        *M2_T_0 = *M2_H_0;
      }
      // M12
      if(inputs.param.find("M12") != inputs.param.end())
      {
        for(int i=1; i<=3; i++)
          (*Mi_0)(i) = *inputs.param.at("M12");
      }
      // TanBeta
      *tanb = *inputs.param.at("TanBeta");
      // SignMu
      *phase_mu = *inputs.param.at("SignMu");
      // A0
      if(inputs.param.find("A0") != inputs.param.end())
      {
        for(int i=1; i<=3; i++)
          (*AoY_d_0)(i,i) = *inputs.param.at("A0");
        *AoY_l_0 = *AoY_d_0;
        *AoY_u_0 = *AoY_d_0;
        *AoY_nu_0 = *AoY_d_0;
        *AoT_0 = *AoY_d_0;
        for(int i=1; i<=2; i++)
          (*Aolam12_0)(i) = (*AoY_d_0)(1,1);
      }
    }
    else if(*HighScaleModel == "GMSB")
    {
      // Lambda
      *Lambda = *inputs.param.at("Lambda");
      // M_M
      *MLambdaS = *inputs.param.at("MLambdaS");
      // SignMu
      *phase_mu = *inputs.param.at("SignMu");
      // n_5
      *n5plets = *inputs.param.at("n5");
      // n_10
      *n10plets = 0;
      // grav_fac
      *grav_fac = *inputs.param.at("grav_fac");
      // TanBeta
      *tanb = *inputs.param.at("TanBeta");
    }
    else if(*HighScaleModel == "AMSB")
    {
      // M0
      *M0_amsb = *inputs.param.at("M0");
      // M32
      *M_32 = *inputs.param.at("M32");
      // SignMu
      *phase_mu = *inputs.param.at("SignMu");

      // TanBeta
      *tanb = *inputs.param.at("TanBeta");

    }
    else if(*HighScaleModel == "SUGRA")
    {
      // SignMu
      *phase_mu = *inputs.param.at("SignMu");
      // TanBeta
      *tanb = *inputs.param.at("TanBeta");
    }
    // Missing pars 7 - 10

    // Block EXTPAR
    if(*HighScaleModel == "SUGRA") // SUGRA
    {
      // Scale of input parameters
      if(inputs.param.find("Qin") != inputs.param.end())
      {
        Freal8 Qin = *inputs.param.at("Qin");
	SetGUTScale(Qin);
      }
      // M_1
      if(inputs.param.find("M1") != inputs.param.end())
      {
        (*Mi)(1).re = *inputs.param.at("M1");
        (*Mi_0)(1).re = *inputs.param.at("M1");
      }
      // M_2
      if(inputs.param.find("M2") != inputs.param.end())
      {
        (*Mi)(2).re = *inputs.param.at("M2");
        (*Mi_0)(2).re = *inputs.param.at("M2");
      }
      // M_3
      if(inputs.param.find("M3") != inputs.param.end())
      {
        (*Mi)(3).re = *inputs.param.at("M3");
        (*Mi_0)(3).re = *inputs.param.at("M3");
      }
      // tanb
      // in GAMBIT tanb is always at mZ
      *tanb_in_at_Q = false;

      for(int i=1; i<=3; i++)
        for(int j=1; j<=3; j++)
        {
          // A_u, Block TUIN
          std::stringstream parname;
          parname << "Au_" << i << j;
          if(inputs.param.find(parname.str()) != inputs.param.end())
          {
            (*Au_0_sckm)(i,j).re = *inputs.param.at(parname.str());
            (*Au_sckm)(j,i).re = *inputs.param.at(parname.str());
          }
          // A_d, Block TDIN
          parname.str(std::string());
          parname << "Ad_" << i << j;
          if(inputs.param.find(parname.str()) != inputs.param.end())
          {
            (*Ad_0_sckm)(i,j).re = *inputs.param.at(parname.str());
            (*Ad_sckm)(j,i).re = *inputs.param.at(parname.str());
          }
          // A_l, Block TEIN
          parname.str(std::string());
          parname << "Ae_" << i << j;
          if(inputs.param.find(parname.str()) != inputs.param.end())
          {
            (*Al_0_pmns)(i,j).re = *inputs.param.at(parname.str());
            (*Al_pmns)(j,i).re = *inputs.param.at(parname.str());
          }
        }

      // A_t
      if(inputs.param.find("Au_33") != inputs.param.end())
      {
        (*AoY_u)(3,3).re = *inputs.param.at("Au_33");
        *At_save = (*AoY_u)(3,3);
        *AoY_u_0 = *AoY_u;
      }
      // A_b
      if(inputs.param.find("Ad_33") != inputs.param.end())
      {
        (*AoY_d)(3,3).re = *inputs.param.at("Ad_33");
        *Ab_save = (*AoY_d)(3,3);
        *AoY_d_0 = *AoY_d;
      }
      // A_tau
      if(inputs.param.find("Ae_33") != inputs.param.end())
      {
        (*AoY_l)(3,3).re = *inputs.param.at("Ae_33");
        *Atau_save = (*AoY_l)(3,3);
        *AoY_l_0 = *AoY_l;
      }

      // M^2_Hd
      if(inputs.param.find("mHd2") != inputs.param.end())
      {
        (*M2_H)(1) = *inputs.param.at("mHd2");
        (*M2_H_0)(1) = *inputs.param.at("mHd2");
      }
      // M^2_Hu
      if(inputs.param.find("mHu2") != inputs.param.end())
      {
        (*M2_H)(2) = *inputs.param.at("mHu2");
        (*M2_H_0)(2) = *inputs.param.at("mHu2");
      }
      // mu, not in GAMBIT input
      // M^2_A(Q), not in GAMBIT input
      // m_A, pole mass, not in GAMBIT input
      for(int i=1; i<=3; i++)
        for(int j=i; j<=3; j++)
        {
          // M^2_L, Block MSL2
          std::stringstream parname;
          parname << "ml2_" << i << j;
          if(inputs.param.find(parname.str()) != inputs.param.end())
          {
           (*M2L_pmns)(i,j) = *inputs.param.at(parname.str());
            (*M2L_pmns)(j,i) = *inputs.param.at(parname.str());
          }
          // M^2_E, Block MSE2
          parname.str(std::string());
          parname << "me2_" << i << j;
          if(inputs.param.find(parname.str()) != inputs.param.end())
          {
            (*M2E_pmns)(i,j) = *inputs.param.at(parname.str());
            (*M2E_pmns)(j,i) = *inputs.param.at(parname.str());
          }
          // M^2_Q, Block MSQ2
          parname.str(std::string());
          parname << "mq2_" << i << j;
          if(inputs.param.find(parname.str()) != inputs.param.end())
          {
            (*M2Q_sckm)(i,j) = *inputs.param.at(parname.str());
            (*M2Q_sckm)(j,i) = *inputs.param.at(parname.str());
          }
          // M^2_U, Block MSU2
          parname.str(std::string());
          parname << "mu2_" << i << j;
          if(inputs.param.find(parname.str()) != inputs.param.end())
          {
            (*M2U_sckm)(i,j) = *inputs.param.at(parname.str());
            (*M2U_sckm)(j,i) = *inputs.param.at(parname.str());
          }
          // M^2_D, Block MSD2
          parname.str(std::string());
          parname << "md2_" << i << j;
          if(inputs.param.find(parname.str()) != inputs.param.end())
          {
            (*M2D_sckm)(i,j) = *inputs.param.at(parname.str());
            (*M2D_sckm)(j,i) = *inputs.param.at(parname.str());
          }
        }
      *M2L_0_pmns = *M2L_pmns;
      *M2E_0_pmns = *M2E_pmns;
      *M2Q_0_sckm = *M2Q_sckm;
      *M2U_0_sckm = *M2U_sckm;
      *M2D_0_sckm = *M2D_sckm;
    }

    // TODO: NMSSM

    // TODO: R-parity breaking

    // Block SPHENOINPUT
    // Already in run_SPheno

    // Block SPINFO, nothing to do here

    // No other blocks are relevant at this stage

    // now some checks and additional settings
    if(phase_mu->re == 0 and (mu->abs() > 0))
    {
      *phase_mu = *mu;
      phase_mu->re /= mu->abs();
      phase_mu->im /= mu->abs();
    }

    if(*SPA_convention)
    {
      backend_warning().raise(LOCAL_INFO,"SPheno Warning: in case of SPA conventions, tan(beta) should be given at 1 TeV.");
    }

    // recalculate quantities to be sure
    *gmZ = *gamZ * *mZ;
    *gmZ2 = pow(*gmZ, 2);

    // W-boson, first rough estimate
    *mW2 = *mZ2 * (0.5 + sqrt(0.25 - *Alpha_mZ*M_PI / (sqrt(2) * *G_F * *mZ2))) / 0.985;
    *mW = sqrt(*mW2); 	// mass
    *gamW = 2.06;	// width
    *gamW2 = pow(*gamW, 2);
    *gmW = *gamW * *mW;
    *gmW2 = pow(*gmW, 2);

    // the running fermion masses at m_Z need to be recalculated
    *Alpha_mZ = Alpha_MSbar(*mZ, *mW);
    CalculateRunningMasses(*mf_l, *mf_d, *mf_u, *Q_light_quarks, *Alpha_mZ, *AlphaS_mZ, *mZ, *mf_l_mZ, *mf_d_mZ, *mf_u_mZ, *kont);

    // TODO: SUGRA_NuR and SEESAW

    // TODO: External_spectrum

    // TODO: l_pmns

    // check if T_f and A_f given, if yes, then A_f gets overwritten
    if((*Au_sckm)(3,3).abs() != 0)
    {
      At_save->re = 0;
      At_save->im = 0;
    }
    if((*Ad_sckm)(3,3).abs() != 0)
    {
      Ab_save->re = 0;
      Ab_save->im = 0;
    }
    if((*Al_pmns)(3,3).abs() != 0)
    {
      Atau_save->re = 0;
      Atau_save->im = 0;
    }

  }

  void InitializeStandardModel(const SMInputs &sminputs)
  {

    *kont = 0;

    // Contributions to alpha(m_Z), based on F. Jegerlehner, hep-ph/0310234 and Fanchiotti, Kniehl, Sirlin PRD 48 (1993) 307
    *Delta_Alpha_Lepton = 0.04020;
    *Delta_Alpha_Hadron = 0.027651;

    // Z-boson
    *mZ = sminputs.mZ;    	// mass
    *gamZ = 2.4952;		// width, values henceforth from StandardModel.f90
    (*BrZqq)(1) = 0.156;	// branching ratio in d \bar{d}
    (*BrZqq)(2) = 0.156;	// branching ratio in s \bar{s}
    (*BrZqq)(3) = 0.151;	// branching ratio in b \bar{b}
    (*BrZqq)(4) = 0.116;	// branching ratio in u \bar{u}
    (*BrZqq)(5) = 0.12;		// branching ratio in c \bar{c}
    (*BrZll)(1) = 0.0336;	// branching ratio in e+ e-
    (*BrZll)(2) = 0.0336;	// branching ratio in mu+ mu-
    (*BrZll)(3) = 0.0338;	// branching ratio in tau+ tau-
    *BrZinv = 0.2;		// invisible branching ratio

    *mZ2 = *mZ * *mZ;
    *gamZ2 = *gamZ * *gamZ;
    *gmZ = *gamZ * *mZ;
    *gmZ2 = *gmZ * *gmZ;

    // W-boson
    *mW = 80.385;
    *gamW = 2.085;
    (*BrWqq)(1) = 0.35;
    (*BrWqq)(2) = 0.35;
    for(int i=1; i<=3; i++)
      (*BrWln)(i) = 0.1;

    *mW2 = pow(*mW, 2);
    *gamW2 = pow(*gamW, 2);
    *gmW = *gamW * *mW;
    *gmW2 = pow(*gmW, 2);

    // lepton masses: e, muon, tau
    (*mf_l)(1) = sminputs.mE;
    (*mf_l)(2) = sminputs.mMu;
    (*mf_l)(3) = sminputs.mTau;

    // default for neutrino masses
    (*mf_nu)(1) = 0.0;
    (*mf_nu)(2) = 0.0;
    (*mf_nu)(3) = 0.0;

    // scale where masses of light quarks are defined [in GeV]
    (*Q_light_quarks) = 2;

    // up-quark masses: u, c, t
    (*mf_u)(1) = sminputs.mU;
    (*mf_u)(2) = sminputs.mCmC;
    (*mf_u)(3) = sminputs.mT;

    // down-quark masses: d, s, b
    (*mf_d)(1) = sminputs.mD;
    (*mf_d)(2) = sminputs.mS;
    (*mf_d)(3) = sminputs.mBmB;

    for(int i=1; i<=3; i++)
    {
       (*mf_l2)(i) = pow((*mf_l)(i),2);
       (*mf_u2)(i) = pow((*mf_u)(i),2);
       (*mf_d2)(i) = pow((*mf_d)(i),2);
    }

    // couplings: Alpha(Q=0), Alpha(mZ), Alpha_S(mZ), Fermi constant G_F
    *Alpha_mZ = 1.0/sminputs.alphainv;
    *Alpha_mZ_MS = *Alpha_mZ; // from SMINPUTS
    *MZ_input = true;
    *AlphaS_mZ = sminputs.alphaS;
    *G_F = sminputs.GF;

    // for ISR correction in e+e- annihilation
    *KFactorLee = 1.0 + (M_PI/3.0 - 1.0/(2*M_PI))*(*Alpha);

    // CKM matrix
    *lam_wolf = sminputs.CKM.lambda;
    *A_wolf = sminputs.CKM.A;
    *rho_wolf = sminputs.CKM.rhobar;
    *eta_wolf = sminputs.CKM.etabar;

    float s12 = sminputs.CKM.lambda;
    float s23 = pow(s12,2) * sminputs.CKM.A;
    float s13 = s23 * sminputs.CKM.lambda * sqrt(pow(sminputs.CKM.etabar,2) + pow(sminputs.CKM.rhobar,2));
    float phase = atan(sminputs.CKM.etabar/sminputs.CKM.rhobar);

    float c12 = sqrt(1.0 - pow(s12,2));
    float c23 = sqrt(1.0 - pow(s23,2));
    float c13 = sqrt(1.0 - pow(s13,2));

    std::complex<float> i = -1;
    i = sqrt(i);

    (*CKM)(1,1) = c12 * c13;
    (*CKM)(1,2) = s12 * c13;
    (*CKM)(1,3) = s13 * exp(-i * phase);
    (*CKM)(2,1) = -s12*c23 -c12*s23*s13 * exp(i * phase);
    (*CKM)(2,2) = c12*c23 -s12*s23*s13 * exp(i * phase );
    (*CKM)(2,3) = s23 * c13;
    (*CKM)(3,1) = s12*s23 -c12*c23*s13 * exp(i * phase );
    (*CKM)(3,2) = -c12*s23 - s12*c23*s13 * exp( i * phase );
    (*CKM)(3,3) = c23 * c13;

    CalculateRunningMasses(*mf_l, *mf_d, *mf_u, *Q_light_quarks, *Alpha_mZ, *AlphaS_mZ, *mZ, *mf_l_mZ, *mf_d_mZ, *mf_u_mZ, *kont);

  }

  // Function that handles errors
  void ErrorHandling(const int &kont)
  {

    str message;

    switch(kont)
    {
      case -1: message = "Problem in OdeInt, stepsize smaller than minimum."; break ;
      case -2: message =  "Problem in OdeInt, max val > 10^36."; break ;
      case -3: message = "Proglem in OdeInt, too many steps."; break ;
      case -4: message = "Proglem in OdeIntB, boundary condition not fulfilled."; break ;
      case -5: message = "Problem in OdeIntB, stepsize smaller than minimum."; break ;
      case -6: message = "Problem in OdeIntB, max val > 10^36."; break ;
      case -7: message = "Problem in OdeIntB, too many steps."; break ;
      case -8: message = "Problem in OdeIntC, boundary condition not fullfilled."; break ;
      case -9: message = "Problem in OdeIntC, stepsize smaller than minimum."; break ;
      case -10: message = "Problem in OdeIntC, max val > 10^36."; break ;
      case -11: message = "Problem in OdeIntC, too many steps."; break ;
      case -12: message = "Problem in rkqs, stepsize undeflow."; break ;
      case -13: message = "Error in Subroutine ComplexEigenSystem. Dimensions do not match."; break ;
      case -14: message = "Potential numerical problems in routine ComplexEigenSystem."; break ;
      case -15: message = "Error in Subroutine RealEigenSystem. Dimensions do not match."; break ;
      case -16: message = "Potential numerical problems in routine RealEigenSystem."; break ;
      case -17: message = "Error in tqli."; break ;
      case -18: message = "Problem in tqli, too many iterations."; break ;
      case -19: message = "Function DGAUSS ... too high accuracy required."; break ;
      case -20: message = "Subroutine DGaussInt ... Too high accuracy required."; break ;
      case -21: message = "Problem in function kappa."; break ;
      case -24: message = "Singular matrix in routine GaussJ."; break ;
      case -27: message = "Problem in bsstep, stepsize undeflow."; break ;
      case -28: message = "Routine pzextr: probable misuse, too much extrapolation"; break ;
      case -29: message = "Routine rzextr: probable misuse, too much extrapolation"; break ;
      case -30: message = "Error in Subroutine RealEigenSystem. Matrix contains NaN."; break ;
      case -31: message = "Error in Subroutine ComplexEigenSystem. Matrix contains NaN."; break ;
      case -101: message = "Problem in routine CalculateRunningMasses: Qlow > mb(mb)."; break ;
      case -102: message = "Problem in routine CalculateRunningMasses: Max(Qlow, mb(mb)) > Qmax."; break ;
      case -201: message = "Warning from Subroutine ChargedScalarMassEps1nt, a mass squared is negative."; break ;
      case -202: message = "Warning from Subroutine ChargedScalarMassEps3, a mass squared is negative."; break ;
      case -203: message = "Warning from Subroutine ChargedScalarMassLam3nt, a mass squared is negative."; break ;
      case -204: message = "Severe Warning from routine CharginoMass3. Abs(h_tau)**2 < 0. Taking the square root from the negative."; break ;
      case -205: message = "Severe Warning from routine CharginoMass5. Abs(h_tau)**2 < 0. Taking the square root from the negative."; break ;
      case -206: message = "Warning from Subroutine PseudoScalarMassEps1nT, a mass squared is negative."; break ;
      case -207: message = "Warning from Subroutine PseudoScalarMassEps3nT, a mass squared is negative."; break ;
      case -208: message = "Warning from Subroutine PseudoScalarMassMSSMnT, a mass squared is negative."; break ;
      case -210: message = "Warning from Subroutine ScalarMassEps1nT, a mass squared is negative."; break ;
      case -211: message = "Warning form Subroutine ScalarMassEps3nT, a mass squared is negative."; break ;
      case -212: message = "Warning from ScalarMassMSSMeff, m_h^2. Setting m_h to the sqrt(abs(m^2_h))."; break ;
      case -213: message = "Warning from Subroutine ScalarMassMSSMnT, a mass squared is negative."; break ;
      case -214: message = "L*k*tanbq*mu = 0 in routine ScalarMassNMSSMeff."; break ;
      case -215: message = "m^2_{S_1^0} < 0 in routine ScalarMassNMSSMeff."; break ;
      case -216: message = "m^2_{P_1^0} < 0 in routine ScalarMassNMSSMeff."; break ;
      case -217: message = "m^2_{S^+} < 0 in routine ScalarMassNMSSMeff."; break ;
      case -219: message = "Warning from routine SdwonMass3Lam. In the calculation of the masses occurred a negative mass squared."; break ;
      case -220: message = "Warning from routine SfermionMass1. In the calculation of the masses occurred a negative mass squared."; break ;
      case -221: message = "Warning from routine SfermionMass1. In the calculation of the masses occurred a negative mass squared."; break ;
      case -222: message = "Warning from routine SfermionMass1mssm. In the calculation of the masses occurred a negative mass squared."; break ;
      case -223: message = "Warning from routine SfermionMass3mssm. In the calculation of the masses occurred a negative mass squared."; break ;
      case -224: message = "Warning from routine SquarkMass3Eps. In the calculation of the masses occurred a negative mass squared."; break ;
      case -225: message = "Error in subroutine TreeMassesEps1. mSneutrino^2 <= 0. Setting it to 10."; break ;
      case -226: message = "Warning from TreeMassesMSSM. mSneut2 < 0. Set to its modulus."; break ;
      case -227: message = "Warning from TreeMassesMSSM. mP02 < 0. Set to its modulus."; break ;
      case -228: message = "Warning from TreeMassesMSSM. mSpm2 < 0. Set to its modulus."; break ;
      case -229: message = "Warning from TreeMassesMSSM2. mSneut2 < 0. Set to 0."; break ;
      case -230: message = "Warning from TreeMassesMSSM2. mP02 < 0. Set to its modulus."; break ;
      case -231: message = "Warning from TreeMassesMSSM2. mSpm2 < 0. Set to its modulus."; break ;
      case -232: message = "Warning from TreeMassesMSSM3. mSneut2 < 0. Set to 0."; break ;
      case -233: message = "Warning from TreeMassesNMSSM. mSneut2 < 0. Set to its modulus."; break ;
      case -302: message = "Routine LesHouches Input: unknown entry for Block MODSEL."; break ;
      case -303: message = "Routine LesHouches Input: model must be specified before parameters."; break ;
      case -304: message = "Routine LesHouches Input: unknown entry for Block MINPAR."; break ;
      case -305: message = "Routine LesHouches Input: model has not been specified completly."; break ;
      case -306: message = "Routine LesHouches Input: a serious error has been part of the input."; break ;
      case -307: message = "Routine LesHouches Input: Higgs sector has not been fully specified."; break ;
      case -308: message = "Routine ReadMatrixC: indices exceed the given boundaries."; break ;
      case -309: message = "Routine ReadMatrixR: indices exceed the given boundaries."; break ;
      case -310: message = "Routine ReadVectorC: index exceeds the given boundaries."; break ;
      case -311: message = "Routine ReadVectorR: index exceeds the given boundaries."; break ;
      case -312: message = "Routine ReadMatrixC: indices exceed the given boundaries"; break ;
      case -401: message = "Routine BoundaryEW: negative scalar mass squared as input."; break ;
      case -402: message = "Routine BoundaryEW: m^2_Z(m_Z) < 0."; break ;
      case -403: message = "Routine BoundaryEW: sin^2(θ_DR) < 0."; break ;
      case -404: message = "Routine BoundaryEW: m^2_W < 0."; break ;
      case -405: message = "Routine BoundaryEW: either m_(l_D R)/m_l < 0.1 or m_(l_D R)/m_l > 10."; break ;
      case -406: message = "Routine BoundaryEW: either m_(d_D R)/m_u < 0.1 or m_(d_D R)/m_d > 10."; break ;
      case -407: message = "Routine BoundaryEW: either m_(u_D R)/m_d < 0.1 or m_(u_D R)/m_u > 10."; break ;
      case -408: message = "Routine RunRGE: entering non-perturbative regime."; break ;
      case -409: message = "Routine RunRGE: nor g_1 = g_ 2 at M_GUT neither any other unification."; break ;
      case -410: message = "Routine RunRGE: entering non-perturbative regime at M_GUT."; break ;
      case -411: message = "Routine RunRGE: entering non-perturbative regime at M_(H_3)."; break ;
      case -412: message = "Routine Sugra: run did not converge."; break ;
      case -413: message = "Routine Calculate_Gi_Yi: m^2_Z(m_Z) < 0."; break ;
      case -414: message = "Routine Calculate_Gi_Yi: too many iterations to calculate m_b(m_b) in the MS scheme."; break ;
      case -415: message = "Routine Sugra: |μ|^2 < 0 at m_Z."; break ;
      case -501: message = "Negative mass squared in routine SleptonMass_1L."; break ;
      case -502: message = "p^2 iteration did not converge in routine SleptonMass_1L."; break ;
      case -503: message = "Negative mass squared in routine SneutrinoMass_1L."; break ;
      case -504: message = "p^2 iteration did not converge in routine SneutrinoMass_1L."; break ;
      case -505: message = "Negative mass squared in routine SquarkMass_1L."; break ;
      case -506: message = "p^2 iteration did not converge in routine SquarkMass_1L."; break ;
      case -507: message = "m^2_(h^0) < 0 in routine LoopMassesMSSM."; break ;
      case -508: message = "m^2_(A^0) < 0 in routine LoopMassesMSSM."; break ;
      case -509: message = "m^2_(H^+) < 0 in routine LoopMassesMSSM."; break ;
      case -510: message = "|μ|^2 > 10^20 in routine LoopMassesMSSM."; break ;
      case -511: message = "|μ|^2 < 0 in routine LoopMassesMSSM."; break ;
      case -512: message = "m^2_Z(m_Z)^2 < 0 in routine LoopMassesMSSM."; break ;
      case -513: message = "m^2_(h^0) < 0 in routine LoopMassesMSSM_2."; break ;
      case -514: message = "m^2_(A^0) < 0 in routine LoopMassesMSSM_2."; break ;
      case -515: message = "m^2_(H^+) < 0 in routine LoopMassesMSSM_2."; break ;
      case -516: message = "|μ|^2 > 10^20 in routine LoopMassesMSSM_2."; break ;
      case -517: message = "|μ|^2 < 0 in routine LoopMassesMSSM_2."; break ;
      case -518: message = "m^2_Z(m_Z)^2 < 0 in routine LoopMassesMSSM_2."; break ;
      case -519: message = "m^2_(h^0) < 0 in routine LoopMassesMSSM_3."; break ;
      case -520: message = "m^2_(A^0) < 0 in routine LoopMassesMSSM_3."; break ;
      case -521: message = "m^2_(H^+) < 0 in routine LoopMassesMSSM_3."; break ;
      case -522: message = "|μ|^2 > 10^20 in routine LoopMassesMSSM_3."; break ;
      case -523: message = "|μ|^2 < 0 in routine LoopMassesMSSM_3."; break ;
      case -524: message = "m^2_Z(m_Z)^2 < 0 in routine LoopMassesMSSM_3."; break ;
      case -525: message = "Negative mass squared in routine Sigma_SM_chirally enhanced."; break ;
      case -601: message = "Routine PiPseudoScalar2: m^2_(~t) < 0."; break ;
      case -602: message = "Routine PiPseudoScalar2: m^2_(~b < 0."; break ;
      case -603: message = "Routine PiPseudoScalar2: m^2_(~τ) < 0."; break ;
      case -604: message = "Routine PiScalar2: m^2_(~t) < 0."; break ;
      case -605: message = "Routine PiScalar2: m^2_(~b) < 0."; break ;
      case -606: message = "Routine PiScalar2: m^2_(~τ) < 0."; break ;
      case -607: message = "Routine Two Loop Tadpoles: m^2_(~t) < 0."; break ;
      case -608: message = "Routine Two Loop Tadpoles: m^2_(~b) < 0."; break ;
      case -609: message = "Routine Two Loop Tadpoles: m^2_(~τ) < 0."; break ;
      case -1001: message = "The size of the arrays do not match in routine ComplexEigenSystems_DP."; break ;
      case -1002: message = "Potential numerical problems in routine ComplexEigenSystems_DP."; break ;
      case -1003: message = "The size of the arrays do not match in routine ComplexEigenSystems_QP."; break ;
      case -1004: message = "Potential numerical problems in routine ComplexEigenSystems_QP."; break ;
      case -1005: message = "The size of the arrays do not match in routine RealEigenSystems_DP."; break ;
      case -1006: message = "Potential numerical problems in routine RealEigenSystems_ DP."; break ;
      case -1007: message = "The size of the arrays do not match in routine RealEigenSystems_QP."; break ;
      case -1008: message = "The size of the arrays do not match in routine Tqli_QP."; break ;
      case -1009: message = "Too many iterations in routine Tqli_QP."; break ;
      case -1010: message = "Too many iterations in routine Tql2_QP."; break ;
    }

    message = "Unspecified error";

    logger() << message << EOM;
    invalid_point().raise(message);

   return ;

  }

}
END_BE_NAMESPACE

// Initialisation function (definition)
BE_INI_FUNCTION
{

    // Dump all internal output
    *ErrCan = 0;

    Set_All_Parameters_0();

    // Set up model, same as Block MODSEL
    if((*ModelInUse)("CMSSM"))
    {
      *HighScaleModel = "mSUGRA";
      SetHighScaleModel("SUGRA");
    }
    else
    {
      *HighScaleModel = "SUGRA"; // SUGRA
      SetHighScaleModel("SUGRA");
    }

}
END_BE_INI_FUNCTION
