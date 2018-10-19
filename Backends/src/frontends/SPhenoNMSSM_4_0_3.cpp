//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend for SPheno 4.3.0 backend (SARAH NMSSM version)
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Tomas Gonzalo
///  \date 2018 Sep
///
///  *********************************************

#include "gambit/Backends/frontend_macros.hpp"
#include "gambit/Backends/frontends/SPhenoNMSSM_4_0_3.hpp"
#include "gambit/Elements/slhaea_helpers.hpp"
#include "gambit/Elements/spectrum_factories.hpp"
#include "gambit/Models/SimpleSpectra/MSSMSimpleSpec.hpp"
#include "gambit/Utils/version.hpp"

// Convenience functions (definition)
BE_NAMESPACE
{

  // Convenience function to run SPheno and obtain the spectrum
  int run_SPheno(Spectrum &spectrum, const Finputs &inputs)
  {

    *epsI = 1.0E-5;
    *deltaM = 1.0E-6;
    *mGUT = -1.0;
    *ratioWoM = 0.0;

    Set_All_Parameters_0();

    Freal8 scale = 1.0E6;
    *Qin = SetRenormalizationScale(scale);
    *kont = 0;
    *delta_mass = 1.0E-4;
    *CalcTBD = false;

    // Intialize variables native to SPhenoNMSSM
    Freal8 vSM = 0.0;
    Freal8 g1SM = 0.0;
    Freal8 g2SM = 0.0;
    Freal8 g3SM = 0.0;
    Farray_Fcomplex16_1_3_1_3 YuSM, YdSM, YeSM;
    Farray_Fcomplex16_1_3_1_3 Yu_ckm, Yd_ckm, Tu_ckm, Td_ckm, mq2_ckm, mu2_ckm, md2_ckm;
    Farray_Fcomplex16_1_3_1_3 Td_out, Tu_out, mq2_out, md2_out, mu2_out;
    for(int i=1; i<=3; i++)
      for(int j=1; j<=3; j++)
      {
        YuSM(i,j) = {0.0,0.0};
        YdSM(i,j) = {0.0,0.0};
        YeSM(i,j) = {0.0,0.0};
        Yu_ckm(i,j) = {0.0,0.0};
        Yd_ckm(i,j) = {0.0,0.0};
        Tu_ckm(i,j) = {0.0,0.0};
        Td_ckm(i,j) = {0.0,0.0};
        mq2_ckm(i,j) = {0.0,0.0};
        mu2_ckm (i,j) = {0.0,0.0};
        md2_ckm(i,j) = {0.0,0.0};
        Td_out(i,j) = {0.0,0.0};
        Tu_out(i,j) = {0.0,0.0};
        mq2_out(i,j) = {0.0,0.0};
        md2_out(i,j) = {0.0,0.0};
        mu2_out(i,j) = {0.0,0.0};
      }

    ReadingData(inputs);

    if((*MatchingOrder < -1) or (*MatchingOrder > 2))
    {
      if(*HighScaleModel == "LOW")
      {
        if(!*CalculateOneLoopMasses)
          *MatchingOrder = -1;
        else
          *MatchingOrder =  2;
      }
      else
        *MatchingOrder =  2;
    }
    switch(*MatchingOrder)
    {
      case 0:
        *OneLoopMatching = false;
        *TwoLoopMatching = false;
        *GuessTwoLoopMatchingBSM = false;
        break;
      case 1:
        *OneLoopMatching = true;
        *TwoLoopMatching = false;
        *GuessTwoLoopMatchingBSM = false;
        break;
      case 2:
        *OneLoopMatching = true;
        *TwoLoopMatching = true;
        *GuessTwoLoopMatchingBSM = true;
        break;
    }

   if(*MatchingOrder == -1)
    {
      // Setting values 
      *vd = *vdIN;
      *vu = *vuIN;
      *vS = *vSIN;
      *g1 = *g1IN;
      *g2 = *g2IN;
      *g3 = *g3IN;
      *Yd = *YdIN;
      *Ye = *YeIN;
      *lam = *lamIN;
      *kap = *kapIN;
      *Yu = *YuIN;
      *Td = *TdIN;
      *Te = *TeIN;
      *Tlam = *TlamIN;
      *Tk = *TkIN;
      *Tu = *TuIN;
      *mq2 = *mq2IN;
      *ml2 = *ml2IN;
      *mHd2 = *mHd2IN;
      *mHu2 = *mHu2IN;
      *md2 = *md2IN;
      *mu2 = *mu2IN;
      *me2 = *me2IN;
      *ms2 = *ms2IN;
      *M1 = *M1IN;
      *M2 = *M2IN;
      *M3 = *M3IN;
      *kap = *KappaInput;
      *lam = *LambdaInput;
      *Tk = *AKappaInput * *KappaInput;
      *Tlam = *ALambdaInput * *LambdaInput;
      *vd = (2*sqrt(*mZ2/(pow(*g1,2) + pow(*g2,2))))/sqrt(1 + pow(*TanBeta,2));
      *vu = (2*sqrt(*mZ2/(pow(*g1,2) + pow(*g2,2))) * *TanBeta)/sqrt(1 + pow(*TanBeta,2));
      *vS = sqrt(2.0) * (*MuEffinput / *LambdaInput).re;
      *TanBetaMZ = *TanBeta;
 
      //Setting VEVs used for low energy constraints 
      *vdMZ = *vd;
      *vuMZ = *vu;
      *vSMZ = *vS;
      double sinW2 = 1.0 - *mW2 / *mZ2;
      vSM = 1/sqrt((*G_F*sqrt(2.0)));
      g1SM = sqrt(4*pi * *Alpha_mZ/(1-sinW2));
      g2SM = sqrt(4*pi * *Alpha_mZ/sinW2);
      g3SM = sqrt(*AlphaS_mZ*4*pi);
      for(int i1=1; i1<=3; i1++)
      {
        YuSM(i1,i1)=sqrt(2.0) * (*mf_u)(i1) / vSM;
        YeSM(i1,i1)=sqrt(2.0) * (*mf_l)(i1) / vSM;
        YdSM(i1,i1)=sqrt(2.0) * (*mf_d)(i1) / vSM;
      }
      if(*GenerationMixing)
      {
        for(int i=1; i<=3; i++)
          for(int j=1; j<=3; j++)
            for(int k=1; k<=3; k++)
               YuSM(i,j) = (*CKM)(i,k) * YuSM(k,j);
      }
 
      // Setting Boundary conditions 
      Flogical MZsuffix = false;
      cout << "g1SM = " << g1SM  << endl;
      cout << "g2SM = " << g2SM  << endl;
      SetMatchingConditions(g1SM, g2SM, g3SM, YuSM, YdSM, YeSM, vSM, *vd, *vu, *vS, *g1, *g2, *g3, *Yd, *Ye, *lam, *kap, *Yu, *Td, *Te, *Tlam, *Tk, *Tu, *mq2, *ml2, *mHd2, *mHu2, *md2, *mu2, *me2, *ms2, *M1, *M2, *M3, MZsuffix);
 
      *kap = *KappaInput;
      *lam = *LambdaInput;
      *Tk = *AKappaInput * *KappaInput;
      *Tlam = *ALambdaInput * *LambdaInput;
      *vd = (2*sqrt(*mZ2/(pow(*g1,2) + pow(*g2,2))))/sqrt(1 + pow(*TanBeta,2));
      *vu = (2*sqrt(*mZ2/(pow(*g1,2) + pow(*g2,2))) * *TanBeta)/sqrt(1 + pow(*TanBeta,2));
      *vS = sqrt(2.0) * MuEffinput->re / LambdaInput->re;

      cout << "g1 = " << *g1 << endl;
      cout << "g2 = " << *g2 << endl;
      cout << "MuEffInput =  " <<  MuEffinput->re << endl;
      cout << "LambdaInput = " << LambdaInput->re << endl;
      cout << "vS = "<< *vS << endl;
      cout << "vd = "<< *vd << endl;
      cout << "vu = " << *vu << endl;
  
      // Translate input form SCKM to electroweak basis 
      if(*SwitchToSCKM)
      {
        Yd_ckm = *Yd;
        Yu_ckm = *Yu;
        Td_ckm = *Td;
        Tu_ckm = *Tu;
        mq2_ckm = *mq2;
        md2_ckm = *md2;
        mu2_ckm = *mu2;
        // TODO: Actual definition in SPhenoNMSSM and InputOutput is longer, may cause problems
        Switch_from_superCKM(Yd_ckm, Yu_ckm, Td_ckm, Tu_ckm, md2_ckm, mq2_ckm, mu2_ckm, Td_out, Tu_out, md2_out, mq2_out, mu2_out, true);
        if(*InputValueforTd) *Td = Td_out;
        if(*InputValueforTu) *Tu = Tu_out;
        if(*InputValueformq2) *mq2 = mq2_out;
        if(*InputValueformd2) *md2 = md2_out;
        if(*InputValueformu2) *mu2 = mu2_out;
      }
  
      Farray_Fcomplex16_1_3 Tad1Loop;
      SolveTadpoleEquations(*g1, *g2, *g3, *Yd, *Ye, *lam, *kap, *Yu, *Td, *Te, *Tlam, *Tk, *Tu, *mq2, *ml2, *mHd2, *mHu2, *md2, *mu2, *me2, *ms2, *M1, *M2, *M3, *vd, *vu, *vS, Tad1Loop);
  
      OneLoopMasses(*MAh, *MAh2, *MCha, *MCha2, *MChi, *MChi2, *MFd, *MFd2, *MFe, *MFe2, *MFu, *MFu2, *MGlu, *MGlu2, *Mhh, *Mhh2, *MHpm, *MHpm2, *MSd, *MSd2, *MSe, *MSe2, *MSu, *MSu2, *MSv, *MSv2, *MVWm, *MVWm2, *MVZ, *MVZ2, *pG, *TW, *UM, *UP, *v, *ZA, *ZD, *ZDL, *ZDR, *ZE, *ZEL, *ZER, *ZH, *ZN, *ZP, *ZU, *ZUL, *ZUR, *ZV, *ZW, *ZZ, *betaH, *vd, *vu, *vS, *g1, *g2, *g3, *Yd, *Ye, *lam, *kap, *Yu, *Td, *Te, *Tlam, *Tk, *Tu, *mq2, *ml2, *mHd2, *mHu2, *md2, *mu2, *me2, *ms2, *M1, *M2, *M3, *kont);

      cout << "MSd = {" << (*MSd)(1) << ", " << (*MSd)(2) << ", " << (*MSd)(3) << ", " << (*MSd)(4) << ", " << (*MSd)(5) << ", " << (*MSd)(6) << endl;
  
      // TODO: Add some checks for SignOfMassChanged

    }
    else
    {
      if(*GetMassUncertainty)
      {
        if(*CalculateOneLoopMasses and *CalculateTwoLoopHiggsMasses)
        {
          *OneLoopMatching = true;
          *TwoLoopMatching = false;
          *GuessTwoLoopMatchingBSM = true;
        }
        else if(*CalculateOneLoopMasses and  !*CalculateTwoLoopHiggsMasses)
        {
          *OneLoopMatching = true;
          *TwoLoopMatching = false;
          *GuessTwoLoopMatchingBSM = false;
        }
        else
        {
          *OneLoopMatching = true;
          *TwoLoopMatching = false;
          *GuessTwoLoopMatchingBSM = false;
        }
 
        CalculateSpectrum(*n_run, *delta_mass, *WriteOut, *kont, *MAh, *MAh2, *MCha, *MCha2, *MChi, *MChi2, *MFd, *MFd2, *MFe, *MFe2, *MFu, *MFu2, *MGlu, *MGlu2, *Mhh, *Mhh2, *MHpm, *MHpm2, *MSd, *MSd2, *MSe, *MSe2, *MSu, *MSu2, *MSv, *MSv2, *MVWm, *MVWm2, *MVZ, *MVZ2, *pG, *TW, *UM, *UP, *v, *ZA, *ZD, *ZDL, *ZDR, *ZE, *ZEL, *ZER, *ZH, *ZN, *ZP, *ZU, *ZUL, *ZUR, *ZV, *ZW, *ZZ, *betaH, *vd, *vu, *vS, *g1, *g2, *g3, *Yd, *Ye, *lam, *kap, *Yu, *Td, *Te, *Tlam, *Tk, *Tu, *mq2, *ml2, *mHd2, *mHu2, *md2, *mu2, *me2, *ms2, *M1, *M2, *M3, *mGUT);

        int n_tot = 0;
        for(int i=1; i<=6; i++)
          (*mass_uncertainty_Yt)(n_tot+i) = (*MSd)(i); // difference will be taken later 
        n_tot = n_tot + 6;
        for(int i=1; i<=3; i++) 
          (*mass_uncertainty_Yt)(n_tot+i) = (*MSv)(i); // difference will be taken later 
        n_tot = n_tot + 3;
        for(int i=1; i<=6; i++) 
          (*mass_uncertainty_Yt)(n_tot+i) = (*MSu)(i); // difference will be taken later 
        n_tot = n_tot + 6;
        for(int i=1; i<=6; i++) 
          (*mass_uncertainty_Yt)(n_tot+i) = (*MSe)(i); // difference will be taken later 
        n_tot = n_tot + 6;
        for(int i=1; i<=3; i++) 
          (*mass_uncertainty_Yt)(n_tot+i) = (*Mhh)(i); // difference will be taken later 
        n_tot = n_tot + 3;
        for(int i=1; i<=3; i++) 
          (*mass_uncertainty_Yt)(n_tot+i) = (*MAh)(i); // difference will be taken later 
        n_tot = n_tot + 3;
        for(int i=1; i<=2; i++) 
          (*mass_uncertainty_Yt)(n_tot+i) = (*MHpm)(i); // difference will be taken later 
        n_tot = n_tot + 2;
        for(int i=1; i<=5; i++) 
          (*mass_uncertainty_Yt)(n_tot+i) = (*MChi)(i); // difference will be taken later 
        n_tot = n_tot + 5;
        for(int i=1; i<=2; i++) 
          (*mass_uncertainty_Yt)(n_tot+i) = (*MCha)(i); // difference will be taken later 
        n_tot = n_tot + 2;
        (*mass_uncertainty_Yt)(n_tot+1) = *MGlu; // difference will be taken later 

        if(*CalculateOneLoopMasses and *CalculateTwoLoopHiggsMasses)
        {
          *OneLoopMatching = true;
          *TwoLoopMatching = true;
          *GuessTwoLoopMatchingBSM = false;
        }
        else if(*CalculateOneLoopMasses and !*CalculateTwoLoopHiggsMasses)
        {
          *OneLoopMatching = false;
          *TwoLoopMatching = false;
          *GuessTwoLoopMatchingBSM = false;
        }
        else
        {
          *OneLoopMatching = false;
          *TwoLoopMatching = false;
          *GuessTwoLoopMatchingBSM = false;
        }
      }
 
      CalculateSpectrum(*n_run, *delta_mass, *WriteOut, *kont, *MAh, *MAh2, *MCha, *MCha2, *MChi, *MChi2, *MFd, *MFd2, *MFe, *MFe2, *MFu, *MFu2, *MGlu, *MGlu2, *Mhh, *Mhh2, *MHpm, *MHpm2, *MSd, *MSd2, *MSe, *MSe2, *MSu, *MSu2, *MSv, *MSv2, *MVWm, *MVWm2, *MVZ, *MVZ2, *pG, *TW, *UM, *UP, *v, *ZA, *ZD, *ZDL, *ZDR, *ZE, *ZEL, *ZER, *ZH, *ZN, *ZP, *ZU, *ZUL, *ZUR, *ZV, *ZW, *ZZ, *betaH, *vd, *vu, *vS, *g1, *g2, *g3, *Yd, *Ye, *lam, *kap, *Yu, *Td, *Te, *Tlam, *Tk, *Tu, *mq2, *ml2, *mHd2, *mHu2, *md2, *mu2, *me2, *ms2, *M1, *M2, *M3, *mGUT);

      if(*GetMassUncertainty)
        GetScaleUncertainty(*delta_mass, *WriteOut, *kont, *MAh, *MAh2, *MCha, *MCha2, *MChi, *MChi2, *MFd, *MFd2, *MFe, *MFe2, *MFu, *MFu2, *MGlu, *MGlu2, *Mhh, *Mhh2, *MHpm, *MHpm2, *MSd, *MSd2, *MSe, *MSe2, *MSu, *MSu2, *MSv, *MSv2, *MVWm, *MVWm2, *MVZ, *MVZ2, *pG, *TW, *UM, *UP, *v, *ZA, *ZD, *ZDL, *ZDR, *ZE, *ZEL, *ZER, *ZH, *ZN, *ZP, *ZU, *ZUL, *ZUR, *ZV, *ZW, *ZZ, *betaH, *vd, *vu, *vS, *g1, *g2, *g3, *Yd, *Ye, *lam, *kap, *Yu, *Td, *Te, *Tlam, *Tk, *Tu, *mq2, *ml2, *mHd2, *mHu2, *md2, *mu2, *me2, *ms2, *M1, *M2, *M3, *mass_uncertainty_Q);

    }

    if(*FoundIterativeSolution or *WriteOutputForNonConvergence)
    {
      if(*OutputForMO)
      {
        // Not covered
      }

      // TODO: ScatterinEingenvalues

      // TODO: TrilinearUnitarity
      spectrum = Spectrum_Out(inputs.param);


    }

    if(*kont != 0)
      ErrorHandling(*kont);

    return *kont;

  }

  // Convenience funciton to run Spheno and obtain the decays
  int run_SPheno_decays(const Spectrum &spectrum)
  {

    // Initialize some variables
    *CalcTBD = false;
    *ratioWoM = 0.0;
    *epsI = 1.0E-5;
    *deltaM = 1.0e-6;
    *kont =  0;

    // Fill input parameters with spectrum information
    for(int i=1; i<=3; i++)
    {
      (*MAh)(i) = spectrum.get(Par::Pole_Mass, "A0",i);
      (*MAh2)(i) = pow((*MAh)(i),2);
    }
    for(int i=1; i<=2; i++)
    {
      (*MCha)(i) = spectrum.get(Par::Pole_Mass, "~chi+",i);
      (*MCha2)(i) = pow((*MCha)(i),2);
    }
    for(int i=1; i<=5; i++)
    {
      (*MChi)(i) = spectrum.get(Par::Pole_Mass, "~chi0",i);
      (*MChi2)(i) = pow((*MChi)(i),2);
    }
    (*MFd)(1) = spectrum.get(Par::Pole_Mass, "d_1");
    (*MFd)(2) = spectrum.get(Par::Pole_Mass, "d_2");
    (*MFd)(3) = spectrum.get(Par::Pole_Mass, "d_3");
    (*MFe)(1) = spectrum.get(Par::Pole_Mass, "e-_1");
    (*MFe)(2) = spectrum.get(Par::Pole_Mass, "e-_2");
    (*MFe)(3) = spectrum.get(Par::Pole_Mass, "e-_3");
    (*MFu)(1) = spectrum.get(Par::Pole_Mass, "u_1");
    (*MFu)(2) = spectrum.get(Par::Pole_Mass, "u_2");
    (*MFu)(3) = spectrum.get(Par::Pole_Mass, "u_3");
    for(int i=1; i<=3; i++)
    {
      (*MFd2)(i) = pow((*MFd)(i),2);
      (*MFe2)(i) = pow((*MFe)(i),2);
      (*MFu2)(i) = pow((*MFu)(i),2);
    }
    *MGlu = spectrum.get(Par::Pole_Mass, "~g");
    *MGlu2 = pow(*MGlu,2);
    for(int i=1; i<=3; i++)
    {
      (*Mhh)(i) = spectrum.get(Par::Pole_Mass, "h0",i);
      (*Mhh2)(i) = pow((*Mhh2)(i),2);
    }
    for(int i=1; i<=2; i++)
    {
      (*MHpm)(i) = spectrum.get(Par::Pole_Mass, "H+",i);
      (*MHpm2)(i) = pow((*MHpm)(i),2);
    }
    for(int i=1; i<=6; i++)
    {
      (*MSd)(i) = spectrum.get(Par::Pole_Mass, "~d",i);
      (*MSd2)(i) = pow((*MSd)(i),2);
      (*MSe)(i) = spectrum.get(Par::Pole_Mass, "~e-",i);
      (*MSe2)(i) = pow((*MSe)(i),2);
      (*MSu)(i) = spectrum.get(Par::Pole_Mass, "~u",i);
      (*MSu2)(i) = pow((*MSu)(i),2);
    }
    for(int i=1; i<=3; i++)
    {
      (*MSv)(i) = spectrum.get(Par::Pole_Mass, "~nu",i);
      (*MSv2)(i) = pow((*MSv)(i),2);
    }
    *MVWm = spectrum.get(Par::Pole_Mass, "W-");
    *MVWm2 = pow(*MVWm,2);
    *MVZ = spectrum.get(Par::Pole_Mass, "Z0");
    *MVZ2 = pow(*MVZ,2);
    // TODO: check whether this value makes sense
    *pG = 1;
/*    *TW = acos(abs(;
    *v;*/
    for(int i=1; i<=6; i++)
    {
      for(int j=1; j<=6; j++)
      {
        (*ZD)(i,j) = spectrum.get(Par::Pole_Mixing, "~d", i, j);
        (*ZE)(i,j) = spectrum.get(Par::Pole_Mixing, "~e-", i, j);
        (*ZU)(i,j) = spectrum.get(Par::Pole_Mixing, "~u", i, j);
        if(i <=3 and j <=3)
        {
          (*ZDL)(i,j) = 0;
          (*ZDR)(i,j) = 0;
          (*ZEL)(i,j) = 0;
          (*ZER)(i,j) = 0;
          (*ZUL)(i,j) = 0;
          (*ZUR)(i,j) = 0;
          if(i==j)
          {
            (*ZDL)(i,j) = 1;
            (*ZDR)(i,j) = 1;
            (*ZEL)(i,j) = 1;
            (*ZER)(i,j) = 1;
            (*ZUL)(i,j) = 1;
            (*ZUR)(i,j) = 1;
          }
          (*ZH)(i,j) = spectrum.get(Par::Pole_Mixing, "h0", i, j);
          (*ZA)(i,j) = spectrum.get(Par::Pole_Mixing, "A0", i, j);
          (*ZV)(i,j) = spectrum.get(Par::Pole_Mixing, "~nu", i, j);
        }
        if(i<=5 and j<=5)
          (*ZN)(i,j) = spectrum.get(Par::Pole_Mixing, "chi0", i, j);
        if(i<=2 and j<=2)
        {
          (*ZP)(i,j) = spectrum.get(Par::Pole_Mixing, "H+", i, j);
          (*UM)(i,j) = spectrum.get(Par::Pole_Mixing, "~chi-", i, j);
          (*UP)(i,j) = spectrum.get(Par::Pole_Mixing, "~chi+", i, j);
        }
    }
   //*ZV;
   // *ZW;
    //*ZZ;
/*    *betaH;
    *vd;
    *vu;
    *vS;
    *g1;
    *g2;
    *g3;
    *Yd;
    *Ye;
    *lam;
    *kap;
    *Yu;
    *Td;
    *Te ;
    *Tlam;
    *Tk;
    *Tu;
    *mq2;
    *ml2;
    *mHd2;
    *mHu2;
    *md2;
    *mu2;
    *me2;
    *ms2;
    *M1;
    *M2;
    *M3;
  */ 
    // Call SPheno's function to calculate decays
    //CalculateBR(*CalcTBD, *ratioWoM, *epsI, *deltaM, *kont, *MAh, *MAh2, *MCha, *MCha2, *MChi, *MChi2, *MFd, *MFd2, *MFe, *MFe2, *MFu, *MFu2, *MGlu, *MGlu2, *Mhh, *Mhh2, *MHpm, *MHpm2, *MSd, *MSd2, *MSe, *MSe2, *MSu, *MSu2, *MSv, *MSv2, *MVWm, *MVWm2, *MVZ, *MVZ2, *pG, *TW, *UM, *UP, *v, *ZA, *ZD, *ZDL, *ZDR, *ZE, *ZEL, *ZER, *ZH, *ZN, *ZP, *ZU, *ZUL, *ZUR, *ZV, *ZW, *ZZ, *betaH, *vd, *vu, *vS, *g1, *g2, *g3, *Yd, *Ye, *lam, *kap, *Yu, *Td, *Te, *Tlam, *Tk, *Tu, *mq2, *ml2, *mHd2, *mHu2, *md2, *mu2, *me2, *ms2, *M1, *M2, *M3, *gPSd, *gTSd, *BRSd, *gPSu, *gTSu, *BRSu, *gPSe, *gTSe, *BRSe, *gPSv, *gTSv, *BRSv, *gPhh, *gThh, *BRhh, *gPAh, *gTAh, *BRAh, *gPHpm, *gTHpm, *BRHpm, *gPGlu, *gTGlu, *BRGlu, *gPChi, *gTChi, *BRChi, *gPCha, *gTCha, *BRCha, *gPFu, *gTFu, *BRFu);

    return *kont;
  }


  // Convenience function to convert internal SPheno variables into a Spectrum object
  Spectrum Spectrum_Out(const std::map<str, safe_ptr<double> >& input_Param)
  {

    SLHAstruct slha;

    Freal8 Q = sqrt(GetRenormalizationScale());

    // TODO: add this bit
    //if(!*RotateNegativeFermionMasses)

    // Spectrum generator information
    SLHAea_add_block(slha, "SPINFO");
    SLHAea_add(slha, "SPINFO", 1, "GAMBIT, using "+str(STRINGIFY(BACKENDNAME))+" from SARAH");
    SLHAea_add(slha, "SPINFO", 2, gambit_version()+" (GAMBIT); "+str(STRINGIFY(VERSION))+" ("+str(STRINGIFY(BACKENDNAME))+"); "+str(STRINGIFY(SARAH_VERSION))+" (SARAH)");

    // Block MODSEL
    SLHAea_add_block(slha, "MODSEL");
    if(*HighScaleModel == "LOW")
      slha["MODSEL"][""] << 1 << 0 << "# SUSY scale input";
    else
      slha["MODSEL"][""] << 1 << 1 << "# GUT scale input";
    slha["MODSEL"][""] << 2 << *BoundaryCondition << "# Boundary conditions";
    if(*GenerationMixing)
      slha["MODSEL"][""] << 6 << 1 << "# switching on flavour violation";
    if(input_Param.find("Qin") != input_Param.end())
      slha["MODSEL"][""] << 12 << *input_Param.at("Qin") << "# Qin";

    // Block MINPAR
    SLHAea_add_block(slha, "MINPAR");
    if(input_Param.find("M0") != input_Param.end())
      slha["MINPAR"][""] << 1 << *input_Param.at("M0") << "# m0";
    if(input_Param.find("M12") != input_Param.end())
      slha["MINPAR"][""] << 2 << *input_Param.at("M12") << "# m12";
    if(input_Param.find("TanBeta") != input_Param.end())
      slha["MINPAR"][""] << 3 << *input_Param.at("TanBeta") << "# tanb at m_Z";
    if(input_Param.find("A0") != input_Param.end())
      slha["MINPAR"][""] << 5 << *input_Param.at("A0") << "# A0";

    // Block EXTPAR
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
    if(input_Param.find("lambda") != input_Param.end())
      slha["EXTPAR"][""] << 61 << *input_Param.at("lambda") << "# Lambda";
    if(input_Param.find("kappa") != input_Param.end())
      slha["EXTPAR"][""] << 62 << *input_Param.at("kappa") << "# kappa";
    if(input_Param.find("Alambda") != input_Param.end())
      slha["EXTPAR"][""] << 63 << *input_Param.at("Alambda") << "# ALambda";
    if(input_Param.find("Akappa") != input_Param.end())
      slha["EXTPAR"][""] << 64 << *input_Param.at("Akappa") << "# Akappa";
    if(input_Param.find("mueff") != input_Param.end())
      slha["EXTPAR"][""] << 65 << *input_Param.at("mueff") << "# mueff";
 
    // Block gaugeGUT
    SLHAea_add_block(slha, "GAUGEGUT", *mGUT);
    slha["GAUGEGUT"][""] << 1 << *g1GUT << "# g1(mGUT)";
    slha["GAUGEGUT"][""] << 2 << *g2GUT << "# g2(mGUT)";
    slha["GAUGEGUT"][""] << 3 << *g3GUT << "# g3(mGUT)";
 
    // Block SMINPUTS
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

    // TODO: Add this
    // if(*SwitchToSCKM)

    // Block GAUGE
    SLHAea_add_block(slha, "GAUGE", Q);
    slha["GAUGE"][""] << 1 << *g1 << "# g1";
    slha["GAUGE"][""] << 2 << *g2 << "# g2";
    slha["GAUGE"][""] << 3 << *g3 << "# g3";

    // Block NMSSMRUN
    SLHAea_add_block(slha, "NMSSMRUN", Q);
    slha["NMSSMRUN"][""] << 1 << lam->re << "# lam";
    slha["NMSSMRUN"][""] << 2 << kap->re << "# kap";
    slha["NMSSMRUN"][""] << 3 << Tlam->re << "# Tlam";
    slha["NMSSMRUN"][""] << 4 << Tk->re << "# Tk";
    slha["NMSSMRUN"][""] << 5 << *vS << "# vS";
    slha["NMSSMRUN"][""] << 10 << *ms2 << "# ms2";

    // Block MSOFT
    SLHAea_add_block(slha, "MSOFT", Q);
    slha["MSOFT"][""] << 1 << M1->re << "# M1";
    slha["MSOFT"][""] << 2 << M2->re << "# M2";
    slha["MSOFT"][""] << 3 << M3->re << "# M3";
    slha["MSOFT"][""] << 21 << *mHd2 << "# mHd2";
    slha["MSOFT"][""] << 22 << *mHu2 << "# mHu2";

    slha["MSOFT"][""] << 31 << sqrt((*ml2)(1,1).re) << "# mL(1,1)";
    slha["MSOFT"][""] << 32 << sqrt((*ml2)(2,2).re) << "# mL(2,2)";
    slha["MSOFT"][""] << 33 << sqrt((*ml2)(3,3).re) << "# mL(3,3)";
    slha["MSOFT"][""] << 34 << sqrt((*me2)(1,1).re) << "# mE(1,1)";
    slha["MSOFT"][""] << 35 << sqrt((*me2)(2,2).re) << "# mE(2,2)";
    slha["MSOFT"][""] << 36 << sqrt((*me2)(3,3).re) << "# mE(3,3)";
    slha["MSOFT"][""] << 41 << sqrt((*mq2)(1,1).re) << "# mQ(1,1)";
    slha["MSOFT"][""] << 42 << sqrt((*mq2)(2,2).re) << "# mQ(2,2)";
    slha["MSOFT"][""] << 43 << sqrt((*mq2)(3,3).re) << "# mQ(3,3)";
    slha["MSOFT"][""] << 44 << sqrt((*mu2)(1,1).re) << "# mU(1,1)";
    slha["MSOFT"][""] << 45 << sqrt((*mu2)(2,2).re) << "# mU(2,2)";
    slha["MSOFT"][""] << 46 << sqrt((*mu2)(3,3).re) << "# mU(3,3)";
    slha["MSOFT"][""] << 47 << sqrt((*md2)(1,1).re) << "# mD(1,1)";
    slha["MSOFT"][""] << 48 << sqrt((*md2)(2,2).re) << "# mD(2,2)";
    slha["MSOFT"][""] << 49 << sqrt((*md2)(3,3).re) << "# mD(3,3)";

    if(M1->im != 0 or M2->im != 0 or M3->im != 0)
    {
      SLHAea_add_block(slha, "IMMSOFT", Q);
      slha["IMMSOFT"][""] << 1 << M1->im << "# Im(M1)";
      slha["IMMSOFT"][""] << 2 << M2->im << "# Im(M2)";
      slha["IMMSOFT"][""] << 3 << M3->im << "# Im(M3)";
    }

    // Block HMIX
    SLHAea_add_block(slha, "HMIX", Q);
    slha["HMIX"][""] << 1 << *input_Param.at("mueff") << " # mueff";
    slha["HMIX"][""] << 2 << *TanBeta << "# TanBeta";
    slha["HMIX"][""] << 3 << sqrt(std::norm(*vu) + std::norm(*vd)) << "# v";
    slha["HMIX"][""] << 4 << 0.0 << "# m^2_A(Q)";
    slha["HMIX"][""] << 10 << *betaH << "# betaH";
    slha["HMIX"][""] << 102 << *vd << "# vd";
    slha["HMIX"][""] << 103 << *vu << "# vu";

    // Block PHASES
    SLHAea_add_block(slha, "PHASES", Q);
    slha["PHASES"][""] << 1 << pG->re << "# pG";
    if(pG->im != 0)
    {
      SLHAea_add_block(slha, "IMPHASES", Q);
      slha["IMPHASES"][""] << 1 << pG->im << "# Im(pG)";
    }

    // TODO: check if important
    // if(*WriteTreeLevelTadpoleParameters

    // Blocks Yu, Yd, Ye
    SLHAea_add_block(slha, "Yu", Q);
    SLHAea_add_block(slha, "Yd", Q);
    SLHAea_add_block(slha, "Ye", Q);
    SLHAea_add_block(slha, "IMYu", Q);
    SLHAea_add_block(slha, "IMYd", Q);
    SLHAea_add_block(slha, "IMYe", Q);
    for(int i=1; i<=3; i++)
      for(int j=1; j<=3; j++)
      {
        slha["Yu"][""] << i << j << (*Yu)(i,j).re << "# Yu(" << i << "," << j << ")";
        slha["Yd"][""] << i << j << (*Yd)(i,j).re << "# Yd(" << i << "," << j << ")";
        slha["Ye"][""] << i << j << (*Ye)(i,j).re << "# Ye(" << i << "," << j << ")";
        slha["IMYu"][""] << i << j << (*Yu)(i,j).im << "# Im(Yu(" << i << "," << j << "))";
        slha["IMYd"][""] << i << j << (*Yd)(i,j).im << "# Im(Yd(" << i << "," << j << "))";
        slha["IMYe"][""] << i << j << (*Ye)(i,j).im << "# Im(Ye(" << i << "," << j << "))";
      }

    // Blocks Te, Tu, Td
    SLHAea_add_block(slha, "Te", Q);
    SLHAea_add_block(slha, "Tu", Q);
    SLHAea_add_block(slha, "Td", Q);
    SLHAea_add_block(slha, "IMTe", Q);
    SLHAea_add_block(slha, "IMTu", Q);
    SLHAea_add_block(slha, "IMTd", Q);
    for(int i=1; i<=3; i++)
      for(int j=1; j<=3; j++)
      {
        slha["Te"][""] << i << j << (*Te)(i,j).re << "# Te(" << i << "," << j << ")";
        slha["Tu"][""] << i << j << (*Tu)(i,j).re << "# Tu(" << i << "," << j << ")";
        slha["Td"][""] << i << j << (*Td)(i,j).re << "# Td(" << i << "," << j << ")";
        slha["IMTe"][""] << i << j << (*Te)(i,j).im << "# Im(Te(" << i << "," << j << "))";
        slha["IMTu"][""] << i << j << (*Tu)(i,j).im << "# Im(Tu(" << i << "," << j << "))";
        slha["IMTd"][""] << i << j << (*Td)(i,j).im << "# Im(Td(" << i << "," << j << "))";
      }

    // Blocks MSL2, MSE2, MSQ2, MSU2, MSD2
    SLHAea_add_block(slha, "MSL2", Q);
    SLHAea_add_block(slha, "MSE2", Q);
    SLHAea_add_block(slha, "MSQ2", Q);
    SLHAea_add_block(slha, "MSU2", Q);
    SLHAea_add_block(slha, "MSD2", Q);
    SLHAea_add_block(slha, "IMMSL2", Q);
    SLHAea_add_block(slha, "IMMSE2", Q);
    SLHAea_add_block(slha, "IMMSQ2", Q);
    SLHAea_add_block(slha, "IMMSU2", Q);
    SLHAea_add_block(slha, "IMMSD2", Q);
    for(int i=1; i<=3; i++)
      for(int j=1; j<=3; j++)
      {
        slha["MSL2"][""] << i << j << (*ml2)(i,j).re << "# ml2(" << i << "," << j << ")";
        slha["MSE2"][""] << i << j << (*me2)(i,j).re << "# me2(" << i << "," << j << ")";
        slha["MSQ2"][""] << i << j << (*mq2)(i,j).re << "# mq2(" << i << "," << j << ")";
        slha["MSU2"][""] << i << j << (*mu2)(i,j).re << "# mu2(" << i << "," << j << ")";
        slha["MSD2"][""] << i << j << (*md2)(i,j).re << "# md2(" << i << "," << j << ")";
        slha["IMMSL2"][""] << i << j << (*ml2)(i,j).im << "# Im(ml2(" << i << "," << j << "))";
        slha["IMMSE2"][""] << i << j << (*me2)(i,j).im << "# Im(me2(" << i << "," << j << "))";
        slha["IMMSQ2"][""] << i << j << (*mq2)(i,j).im << "# Im(mq2(" << i << "," << j << "))";
        slha["IMMSU2"][""] << i << j << (*mu2)(i,j).im << "# Im(mu2(" << i << "," << j << "))";
        slha["IMMSD2"][""] << i << j << (*md2)(i,j).im << "# Im(md2(" << i << "," << j << "))";
     }

    // TODO: add this
    // if(*WriteGUTvalues)

    SLHAea_add_block(slha, "MASS");
    slha["MASS"][""] << 1000001 << (*MSd)(1) << "# Sd_1";
    slha["MASS"][""] << 1000003 << (*MSd)(2) << "# Sd_2";
    slha["MASS"][""] << 1000005 << (*MSd)(3) << "# Sd_3";
    slha["MASS"][""] << 2000001 << (*MSd)(4) << "# Sd_4";
    slha["MASS"][""] << 2000003 << (*MSd)(5) << "# Sd_5";
    slha["MASS"][""] << 2000005 << (*MSd)(6) << "# Sd_6";
    slha["MASS"][""] << 1000002 << (*MSu)(1) << "# Su_1";
    slha["MASS"][""] << 1000004 << (*MSu)(2) << "# Su_2";
    slha["MASS"][""] << 1000006 << (*MSu)(3) << "# Su_3";
    slha["MASS"][""] << 2000002 << (*MSu)(4) << "# Su_4";
    slha["MASS"][""] << 2000004 << (*MSu)(5) << "# Su_5";
    slha["MASS"][""] << 2000006 << (*MSu)(6) << "# Su_6";
    slha["MASS"][""] << 1000011 << (*MSe)(1) << "# Se_1";
    slha["MASS"][""] << 1000013 << (*MSe)(2) << "# Se_2";
    slha["MASS"][""] << 1000015 << (*MSe)(3) << "# Se_3";
    slha["MASS"][""] << 2000011 << (*MSe)(4) << "# Se_4";
    slha["MASS"][""] << 2000013 << (*MSe)(5) << "# Se_5";
    slha["MASS"][""] << 2000015 << (*MSe)(6) << "# Se_6";
    slha["MASS"][""] << 1000012 << (*MSv)(1) << "# Sv_1";
    slha["MASS"][""] << 1000014 << (*MSv)(2) << "# Sv_2";
    slha["MASS"][""] << 1000016 << (*MSv)(3) << "# Sv_3";

    slha["MASS"][""] << 25 << (*Mhh)(1) << "# hh_1";
    slha["MASS"][""] << 35 << (*Mhh)(2) << "# hh_2";
    slha["MASS"][""] << 45 << (*Mhh)(3) << "# hh_3";
    slha["MASS"][""] << 36 << (*MAh)(2) << "# Ah_2";
    slha["MASS"][""] << 46 << (*MAh)(3) << "# Ah_3";
    slha["MASS"][""] << 37 << (*MHpm)(2) << "# Hpm_2";

    slha["MASS"][""] << 23 << *MVZ << "# VZ";
    slha["MASS"][""] << 24 << *MVWm << "# VWm";
   
    slha["MASS"][""] << 1 << (*MFd)(1) << "# Fd_1";
    slha["MASS"][""] << 3 << (*MFd)(2) << "# Fd_2";
    slha["MASS"][""] << 5 << (*MFd)(3) << "# Fd_3";
    slha["MASS"][""] << 2 << (*MFu)(1)<< "# Fu_1";
    slha["MASS"][""] << 4 << (*MFu)(2)<< "# Fu_2";
    slha["MASS"][""] << 6 << (*MFu)(3)<< "# Fu_3";
    slha["MASS"][""] << 11 << (*MFe)(1)<< "# Fe_1";
    slha["MASS"][""] << 13 << (*MFe)(2)<< "# Fe_2";
    slha["MASS"][""] << 15 << (*MFe)(3)<< "# Fe_3";
 
    slha["MASS"][""] << 1000021 << *MGlu << "# Glu";

    slha["MASS"][""] << 1000022 << (*MChi)(1) << "# Chi_1";
    slha["MASS"][""] << 1000023 << (*MChi)(2) << "# Chi_2";
    slha["MASS"][""] << 1000025 << (*MChi)(3) << "# Chi_3";
    slha["MASS"][""] << 1000035 << (*MChi)(4) << "# Chi_4";
    slha["MASS"][""] << 1000045 << (*MChi)(5) << "# Chi_5";
    slha["MASS"][""] << 1000024 << (*MCha)(1) << "# Cha_1";
    slha["MASS"][""] << 1000037 << (*MCha)(2) << "# Cha_2";

    // TODO: missing
    // if(*GetMassUncertainty)
    // Block DMASS

    // TODO: maybe add this one too
    // Block LSP
 
    // Blocks DSQMIX, USQMIX, SELMIX, SNUMIX
    SLHAea_add_block(slha, "DSQMIX", Q);
    SLHAea_add_block(slha, "USQMIX", Q);
    SLHAea_add_block(slha, "SELMIX", Q);
    SLHAea_add_block(slha, "SNUMIX", Q);
    for(int i=1; i<=6; i++)
      for(int j=1; j<=6; j++)
      {
        slha["DSQMIX"][""] << i << j << (*ZD)(i,j).re << "# ZD(" << i << "," << j << ")";
        slha["IMDSQMIX"][""] << i << j << (*ZD)(i,j).im << "# Im(ZD(" << i << "," << j << "))";
        slha["USQMIX"][""] << i << j << (*ZU)(i,j).re << "# ZU(" << i << "," << j << ")";
        slha["IMUSQMIX"][""] << i << j << (*ZU)(i,j).im << "# Im(ZU(" << i << "," << j << "))";
        slha["SELMIX"][""] << i << j << (*ZE)(i,j).re << "# ZE(" << i << "," << j << ")";
        slha["IMSELMIX"][""] << i << j << (*ZE)(i,j).im << "# Im(ZE(" << i << "," << j << "))";
        if(i<=3 and j<=3)
        {
          slha["SNUMIX"][""] << i << j << (*ZV)(i,j).re << "# ZV(" << i << "," << j << ")";
          slha["IMSNUMIX"][""] << i << j << (*ZV)(i,j).im << "# Im(ZV(" << i << "," << j << "))";
        }
      }

    // Blocks SCALARMIX, PSEUDOSCALARMIX, CHARGEMIX
    SLHAea_add_block(slha, "SCALARMIX", Q);
    SLHAea_add_block(slha, "PSEUDOSCALARMIX", Q);
    SLHAea_add_block(slha, "CHARGEMIX", Q);
    for(int i=1; i<=3; i++)
      for(int j=1; j<=3; j++)
      {
        slha["SCALARMIX"][""] << i << j << (*ZH)(i,j) << "# ZH(" << i << "," << j << ")";
        slha["PSEUDOSCALARMIX"][""] << i << j << (*ZA)(i,j) << "# ZA(" << i << "," << j << ")";
        if(i < 3 and j < 3)
          slha["CHARGEMIX"][""] << i << j << (*ZP)(i,j) << "# ZP(" << i << "," << j << ")";
      }

    // Blocks NMNIX, UMIX, VMIX
    SLHAea_add_block(slha, "NMNMIX", Q);
    SLHAea_add_block(slha, "INMNMIX", Q);
    SLHAea_add_block(slha, "UMIX", Q);
    SLHAea_add_block(slha, "IMUMIX", Q);
    SLHAea_add_block(slha, "VMIX", Q);
    SLHAea_add_block(slha, "IMVMIX", Q);
    for(int i=1; i<=5; i++)
      for(int j=1; j<=5; j++)
      {
        slha["NMIX"][""] << i << j << (*ZN)(i,j).re << "# ZN(" << i << "," << j << ")";
        slha["IMNMIX"][""] << i << j << (*ZN)(i,j).im << "# Im(ZN(" << i << ", " << j << "))";
        if(i <= 2 and j <= 2)
        {
          slha["UMIX"][""] << i << j << (*UM)(i,j).re << "# UM(" << i << "," << j << ")";
          slha["IMUMIX"][""] << i << j << (*UM)(i,j).im << "# Im(UM(" << i << "," << j << "))";
          slha["VMIX"][""] << i << j << (*UP)(i,j).re << "# UP(" << i << "," << j << ")";
          slha["IMVMIX"][""] << i << j << (*UP)(i,j).im << "# Im(UP(" << i << "," << j << "))";
        }
      }

    // Blocks UELMIX, UERMIX, UDLMIX, UDRMIX, UULMIX, UURMIX
    SLHAea_add_block(slha, "UELMIX", Q);
    SLHAea_add_block(slha, "IMUELMIX", Q);
    SLHAea_add_block(slha, "UERMIX", Q);
    SLHAea_add_block(slha, "IMUERMIX", Q);
    SLHAea_add_block(slha, "UDLMIX", Q);
    SLHAea_add_block(slha, "IMUDLMIX", Q);
    SLHAea_add_block(slha, "UDRMIX", Q);
    SLHAea_add_block(slha, "IMUDRMIX", Q);
    SLHAea_add_block(slha, "UULMIX", Q);
    SLHAea_add_block(slha, "IMUULMIX", Q);
    SLHAea_add_block(slha, "UURMIX", Q);
    SLHAea_add_block(slha, "IMUURMIX", Q);
    for(int i=1; i<=3; i++)
      for(int j=1; j<=3; j++)
      {
        slha["UELMIX"][""] << i << j << (*ZEL)(i,j).re << "# ZEL(" << i << "," << j << ")";
        slha["IMUELMIX"][""] << i << j << (*ZEL)(i,j).im << "# Im(ZEL(" << i << "," << j << "))";
        slha["UERMIX"][""] << i << j << (*ZER)(i,j).re << "# ZER(" << i << "," << j << ")";
        slha["IMUERMIX"][""] << i << j << (*ZER)(i,j).im << "# Im(ZER(" << i << "," << j << "))";
        slha["UDLMIX"][""] << i << j << (*ZDL)(i,j).re << "# ZDL(" << i << "," << j << ")";
        slha["IMUDLMIX"][""] << i << j << (*ZDL)(i,j).im << "# Im(ZDL(" << i << "," << j << "))";
        slha["UDRMIX"][""] << i << j << (*ZDR)(i,j).re << "# ZDR(" << i << "," << j << ")";
        slha["IMUDRMIX"][""] << i << j << (*ZDR)(i,j).im << "# Im(ZDR(" << i << "," << j << "))";
        slha["UULMIX"][""] << i << j << (*ZUL)(i,j).re << "# ZUL(" << i << "," << j << ")";
        slha["IMUULMIX"][""] << i << j << (*ZUL)(i,j).im << "# Im(ZUL(" << i << "," << j << "))";
        slha["UURMIX"][""] << i << j << (*ZUR)(i,j).re << "# ZUR(" << i << "," << j << ")";
        slha["IMUURMIX"][""] << i << j << (*ZUR)(i,j).im << "# Im(ZUR(" << i << "," << j << "))";
     }

    // Block SPhenoINFO 
    SLHAea_add_block(slha, "SPheno");
    slha["SPheno"][""] << 1 << *ErrorLevel << "# ErrorLevel";
    slha["SPheno"][""] << 2 << *SPA_convention << "# SPA_conventions";
    slha["SPheno"][""] << 8 << *TwoLoopMethod << "# Two Loop Method";
    slha["SPheno"][""] << 9 << *GaugelessLimit << "# Gauge-less limit";
    slha["SPheno"][""] << 11 << *L_BR << "# Branching ratios";
    //slha["SPheno"][""] << 13 << *Enable3BDecays << "# 3 Body decays";
    slha["SPheno"][""] << 31 << *mGUT << "# GUT scale";
    slha["SPheno"][""] << 33 << Q << "# Renormalization scale";
    slha["SPheno"][""] << 34 << *delta_mass << "# Precision";
    slha["SPheno"][""] << 35 << *n_run << "# Iterations";
    if(*TwoLoopRGE)
      slha["SPheno"][""] << 38 << 2 << "# RGE level";
    else
      slha["SPheno"][""] << 38 << 1 << "# RGE level";
    slha["SPheno"][""] << 40 << *Alpha << "# Alpha";
    slha["SPheno"][""] << 41 << *gamZ << "# Gamma_Z";
    slha["SPheno"][""] << 42 << *gamW << "# Gamma_W";
    slha["SPheno"][""] << 50 << *RotateNegativeFermionMasses << "# Rotate negative fermion masses";
    slha["SPheno"][""] << 51 << *SwitchToSCKM << "# Switch to SCKM matrix";
    slha["SPheno"][""] << 52 << *IgnoreNegativeMasses << "# Ignore negative masses";
    slha["SPheno"][""] << 53 << *IgnoreNegativeMassesMZ << "# Ignore negative masses at MZ";
    slha["SPheno"][""] << 55 << *CalculateOneLoopMasses << "# Calculate one loop masses";
    slha["SPheno"][""] << 56 << *CalculateTwoLoopHiggsMasses << "# Calculate two-loop Higgs masses";
    slha["SPheno"][""] << 57 << *CalculateLowEnergy << "# Calculate low energy";
    slha["SPheno"][""] << 60 << *KineticMixing << "# Include kinetic mixing";
    slha["SPheno"][""] << 65 << *SolutionTadpoleNr << "# Solution of tadpole equation";

    //Create Spectrum object
    static const Spectrum::mc_info mass_cut;
    static const Spectrum::mr_info mass_ratio_cut;
    Spectrum spectrum = spectrum_from_SLHAea<MSSMSimpleSpec, SLHAstruct>(slha,slha,mass_cut,mass_ratio_cut);

    // Add the high scale variable by hand
//    spectrum.get_HE().set_override(Par::mass1, SLHAea::to<double>(slha.at("GAMBIT").at(1).at(1)), "high_scale", true);

    return spectrum;

  }

  // Function to read data from the Gambit inputs and fill SPheno internal variables
  void ReadingData(const Finputs &inputs)
  {

    InitializeStandardModel(inputs.sminputs);
    InitializeLoopFunctions();
 
    *ErrorLevel = -1;
    *GenerationMixing = false;

    Set_All_Parameters_0();

    *TwoLoopRGE = true;

    *kont = 0;

    /****************/
    /* Block MODSEL */
    /****************/
    // Already in Backend initialization function
 
    /******************/
    /* Block SMINPUTS */
    /******************/
    // Already in InitializeStandardModel

    /****************/
    /* Block VCKMIN */
    /****************/ 
    // Already in SMInputs

    /****************/
    /* Block FCONST */
    /****************/
    // TODO: Check if not needed

    /***************/
    /* Block FMASS */
    /***************/
    // TODO: Check if not needed

    /***************/
    /* Block FLIFE */
    /***************/
    // TODO: Check if not needed

    /*******************************/
    /* Block SPHENOINPUT (options) */
    /*******************************/
    // 1, Error_Level
    *ErrorLevel = inputs.options->getValueOrDef<Finteger>(-1, "ErrorLevel");
    // GAMBIT: keep error level always 0 (print every warning), let GAMBIT handle errors
    *ErrorLevel = 0;

    // 2, SPA_convention
    *SPA_convention = inputs.options->getValueOrDef<Flogical>(false, "SPA_convention");
    if(*SPA_convention)
    {
      Freal8 scale = 1.0E6;
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

    // 6, RXiNew
    *RXiNew = inputs.options->getValueOrDef<Freal8>(1.0, "RXiNew");

    // 7, Caclulate Two Loop Higgs Masses
    *CalculateTwoLoopHiggsMasses = inputs.options->getValueOrDef<Flogical>(true, "CalculateTwoLoopHiggsMasses");

    // 8, Two Loop method 
    *TwoLoopMethod = inputs.options->getValueOrDef<Finteger>(3, "TwoLoopMethod");
    switch(*TwoLoopMethod)
    {
      case 1:
        *PurelyNumericalEffPot = true;
        *CalculateMSSM2Loop = false;
        break;
      case 2:
        *PurelyNumericalEffPot = false;
        *CalculateMSSM2Loop = false;
        break;
      case 3: 
        *CalculateMSSM2Loop = false;
        break;
      case 8:
        *CalculateMSSM2Loop = true;
        break;
      case 9:
        *CalculateMSSM2Loop = true;
        break;
      default:
        *CalculateTwoLoopHiggsMasses = false;
    }

    // 9, GaugelessLimit
    *GaugelessLimit = inputs.options->getValueOrDef<Flogical>(true, "GaugelessLimit");

    // 400, hstep_pn
    *hstep_pn = inputs.options->getValueOrDef<Freal8>(0.1, "hstep_pn");

    // 401, hstep_pn
    *hstep_sa = inputs.options->getValueOrDef<Freal8>(0.001, "hstep_sa");

    // 410, TwoLoopRegulatorMass
    *TwoLoopRegulatorMass = inputs.options->getValueOrDef<Freal8>(0.0, "TwoLoopRegulatorMass"); 

   // 10, TwoLoopSafeMode
    *TwoLoopSafeMode = inputs.options->getValueOrDef<Flogical>(true, "TwoLoopSafeMode");

    // 11, whether to calculate branching ratios or not, L_BR
    // TODO: Branching ratios, not covered yet
    //*L_BR = inputs.options->getValueOrDef<Flogical>(false, "L_BR");
    *L_BR = false;


    // 12, minimal value such that a branching ratio is written out, BRMin
    // TODO: Branching ratios, not covered yet
    //Freal8 BrMin = inputs.options->getValueOrDef<Freal8>(0.0, "BRMin");
    //if(BrMin > 0.0)
    //  SetWriteMinBr(BrMin);

    // 13, 3 boday decays
    // TODO: Branching ratios, not covered yet

    // 14, run SUSY couplings to scale of decaying particle
    // TODO: Branching ratios, not covered yet

    // 15, MinWidth
    // TODO: Branching ratios, not covered yet

    // 16. OneLoopDecays
    // TODO: Branching ratios, not covered yet

    // 19, MatchingOrder: maximal number of iterations
    *MatchingOrder = inputs.options->getValueOrDef<Finteger>(-2, "MatchingOrder");

    // 20, GetMassUncertainty
    *GetMassUncertainty = inputs.options->getValueOrDef<Flogical>(false, "GetMassUncertainty");

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

    // 33, setting a fixed renormalization scale
    Freal8 RGEScale = inputs.options->getValueOrDef<Freal8>(0.0, "RGEScale");
    if(RGEScale > 0.0)
    {
      RGEScale *= RGEScale;
      SetRGEScale(RGEScale);
    }

    // 34, precision of mass calculation, delta_mass
    *delta_mass = inputs.options->getValueOrDef<Freal8>(0.00001, "delta_mass");

    // 35, maximal number of iterations, n_run
    *n_run = inputs.options->getValueOrDef<Finteger>(40, "n_run");

    // 36, minimal number of iterations
    *MinimalNumberIterations = inputs.options->getValueOrDef<Finteger>(5, "MinimalNumberIterations");

    // 37, if = 1 -> CKM through V_u, if = 2 CKM through V_d, YukawaScheme
    // GAMBIT: not covered

    // 38, set looplevel of RGEs, TwoLoopRGE
    *TwoLoopRGE = inputs.options->getValueOrDef<Flogical>(true, "TwoLoopRGE");

    // 39, write additional SLHA1 file, Write_SLHA1
    // GABMIT: Always false, no file output
    *WriteSLHA1 = false;

    // 40, alpha(0), Alpha
    Freal8 alpha = 1.0/137.035999074;
    *Alpha = inputs.options->getValueOrDef<Freal8>(alpha,"Alpha");

    // 41, Z-boson width, gamZ
    *gamZ = inputs.options->getValueOrDef<Freal8>(2.49,"gamZ");

    // 42, W-boson width, gamW
    *gamW = inputs.options->getValueOrDef<Freal8>(2.06,"gamW");

    // 50, RotateNegativeFermionMasses
    *RotateNegativeFermionMasses = inputs.options->getValueOrDef<Flogical>(true,"RotateNegativeFermionMasses");

    // 51, Switch to SCKM
    *SwitchToSCKM = inputs.options->getValueOrDef<Flogical>(false, "SwitchToSCKM");

    // 52, Ignore negative masses
    *IgnoreNegativeMasses = inputs.options->getValueOrDef<Flogical>(false, "IgnoreNegativeMasses");

    // 53, Ignore negative masses at MZ
    *IgnoreNegativeMassesMZ = inputs.options->getValueOrDef<Flogical>(false, "IgnoreNegativeMassesMZ");
    // 54, Write Out for non convergence
    *WriteOutputForNonConvergence = inputs.options->getValueOrDef<Flogical>(false, "WriteOutputForNonConvergence");

    // 55, calculate one loop masses
    *CalculateOneLoopMasses = inputs.options->getValueOrDef<Flogical>(true, "CalculateOneLoopMasses");

    // 57, calculate low energy observables
    // TODO: No low energy observables yet
    *CalculateLowEnergy = false;

    // 58, include delta and/or BSM delta VB
    *IncludeDeltaVB = inputs.options->getValueOrDef<Flogical>(true, "IncludeDeltaVB");
    if(*IncludeDeltaVB)
      *IncludeBSMdeltaVB = inputs.options->getValueOrDef<Flogical>(true, "IncludeBSMdeltaVB");

    // 60, kinetic mixing
    *KineticMixing = inputs.options->getValueOrDef<Flogical>(true, "KineticMixing");

    // 62,
    *RunningSUSYparametersLowEnergy = inputs.options->getValueOrDef<Flogical>(true, "RunningSUSYparametersLowEnergy");

    // 63,
    *RunningSMparametersLowEnergy = inputs.options->getValueOrDef<Flogical>(true, "RunningSMparametersLowEnergy");

    // 64
    *WriteParametersAtQ = inputs.options->getValueOrDef<Flogical>(false, "WriteParametersAtQ");

    // 65
    *SolutionTadpoleNr = inputs.options->getValueOrDef<Finteger>(1, "SolutionTadpoleNr");

    // 66
    *DecoupleAtRenScale = inputs.options->getValueOrDef<Flogical>(false, "DecoupleAtRenScale");

    // 67
    *Calculate_mh_within_SM = inputs.options->getValueOrDef<Flogical>(true, "Calculate_mh_within_SM");
    if(*Calculate_mh_within_SM)
      *Force_mh_within_SM = inputs.options->getValueOrDef<Flogical>(false, "Force_mh_within_SM");

    // 68
    *MatchZWpoleMasses = inputs.options->getValueOrDef<Flogical>(false, "MatchZWpolemasses");

    // 75,  Writes the parameter file for WHIZARD
    // GAMBIT: no output
    *Write_WHIZARD = false;

    // 76, Writes input files for HiggsBounfs
    // GAMBIT: no output
    *Write_HiggsBounds = false;

    // 77, Use conventions for MO
    // TODO: Maybe no output
    *OutputForMO = false;

    // 78,  Use conventions for MG
    // TODO: Maybe no output
    *OutputForMG = false;

    // 79, Writes Wilson coefficients in WCXF format
    *Write_WCXF = inputs.options->getValueOrDef<Flogical>(false, "Write_WCXF");

    // 80, exit for sure with non-zero value if problem occurs, Non_Zero_Exit
    // GAMBIT: never brute exit, let GAMBIT do a controlled exit
    *Non_Zero_Exit = false;

    // 86, width to be counted as invvisible in HiggsBounds input
    *WidthToBeInvisible = inputs.options->getValueOrDef<Freal8>(0.0, "WidthToBeInvisible");

    // 88, maximal mass allowedin loops
    *MaxMassLoop = pow(inputs.options->getValueOrDef<Freal8>(1.0E16, "MaxMassLoop"), 2);

    // 80, maximal mass counted as numerical zero
    *MaxMassNumericalZero = inputs.options->getValueOrDef<Freal8>(1.0E-8, "MaxMassNumericalZero");

    // 95, force mass mastrices at 1-loop to be real
    *ForceRealMatrices = inputs.options->getValueOrDef<Flogical>(false, "ForceRealMatrices");

    // 150, use 1l2lshifts
    *include1l2lshift=inputs.options->getValueOrDef<Flogical>(false,"include1l2lshift");

    // 151
    *NewGBC=inputs.options->getValueOrDef<Flogical>(true,"NewGBC");
 
    // 440
    *TreeLevelUnitarityLimits=inputs.options->getValueOrDef<Flogical>(true,"TreeLevelUnitarityLimits");
 
    // 441
    *TrilinearUnitarity=inputs.options->getValueOrDef<Flogical>(true,"TrilinearUnitarity");
 
    // 442
    *unitarity_s_min = inputs.options->getValueOrDef<Freal8>(2000,"unitarity_s_min");
 
    // 443
    *unitarity_s_max = inputs.options->getValueOrDef<Freal8>(3000,"unitarity_s_max");
 
    // 444
    *unitarity_steps = inputs.options->getValueOrDef<Finteger>(5,"unitarity_steps");
 
    // 445
    *RunRGEs_unitarity=inputs.options->getValueOrDef<Flogical>(false,"RunRGEs_unitarity");
 
    // 446
    *TUcutLevel = inputs.options->getValueOrDef<Finteger>(2,"TUcutLevel");
 
    // 510, Write tree level tadpole solutions
    // GAMBIT: no output
    *WriteTreeLevelTadpoleSolutions = false;

    // 515, Write GUT values
    // GAMBIT: no output
    *WriteGUTvalues = false;

    // 520, write effective higgs coupling ratios
    // GAMBIT: no output
    *WriteEffHiggsCouplingRatios = false;

    // 521, Higher order diboson
    *HigherOrderDiboson = inputs.options->getValueOrDef<Flogical>(true, "HigherOrderDiboson");

    // 522
    *PoleMassesInLoops = inputs.options->getValueOrDef<Flogical>(true, "PoleMassesInLoops");

    // 525, write higgs diphoton loop contributions
    // GAMBIT: no output
    *WriteHiggsDiphotonLoopContributions = false;

    // 530, write tree level tadpole parameters
    // GAMBIT: no output
    *WriteTreeLevelTadpoleParameters = false;
 
    // 550, CalcFT
    // Has no effect
    *CalcFT = true;

    // 551, one loop FT
    *OneLoopFT = inputs.options->getValueOrDef<Flogical>(false, "OneLoopFT");

    // 990, make Q test
    *MakeQTEST = inputs.options->getValueOrDef<Flogical>(false, "MakeQTEST");

    // 000, print debug information
    // GAMBIT: no output
    *PrintDebugInformation = false;

 
    /**********************/
    /* Block DECAYOPTIONS */
    /**********************/
    //TODO: Implement

    /****************/
    // Block MINPAR //
    /****************/
    // M0
    if(inputs.param.find("M0") != inputs.param.end())
      *m0 = *inputs.param.at("M0");
    // M12
    if(inputs.param.find("M12") != inputs.param.end())
      m12->re = *inputs.param.at("M12");
    // TanBeta
    if(inputs.param.find("TanBeta") != inputs.param.end())
      *TanBeta = *inputs.param.at("TanBeta");
    // A0
    if(inputs.param.find("A0") != inputs.param.end())
      Azero->re = *inputs.param.at("A0");

    /****************/
    /* Block EXTPAR */
    /****************/
    // These guys are not really in EXTPAR in the NMSSM
    // M_1
    //if(inputs.param.find("M1") != inputs.param.end())
    //  M1input->re = *inputs.param.at("M1");
    // M_2
    //if(inputs.param.find("M2") != inputs.param.end())
    //  M2input->re = *inputs.param.at("M2");
    // M_3
    //if(inputs.param.find("M3") != inputs.param.end())
    //  M3input->re = *inputs.param.at("M3");
    // Mu
    // No Mu input in GAMBIT
    // MA^2
    // No MA input in GAMBIT
    // TanBeta
    // in GAMBIT tanb is always at mZ

    // Parameters specific of the NMSSM
    LambdaInput->re = *inputs.param.at("lambda");
    KappaInput->re = *inputs.param.at("kappa");
    ALambdaInput->re = *inputs.param.at("Alambda");
    AKappaInput->re = *inputs.param.at("Akappa");
    if(inputs.param.find("mueff") != inputs.param.end())
      MuEffinput->re = *inputs.param.at("mueff");
    // maybe add option to input vs in the future
 

    for(int i=1; i<=3; i++)
      for(int j=1; j<=3; j++)
      {
        /********/
	/* TUIN */
	/********/
        std::stringstream parname;
        parname << "Au_" << i << j;
        if(inputs.param.find(parname.str()) != inputs.param.end())
        {
          *InputValueforTu = true;
          (*TuIN)(i,j).re = *inputs.param.at(parname.str());
        }

        /********/
        /* TDIN */
        /********/
        parname.str(std::string());
        parname << "Ad_" << i << j;
        if(inputs.param.find(parname.str()) != inputs.param.end())
        {
          *InputValueforTd = true;
          (*TdIN)(i,j).re = *inputs.param.at(parname.str());
        }

        /********/
        /* TEIN */
        /********/
        parname.str(std::string());
        parname << "Ae_" << i << j;
        if(inputs.param.find(parname.str()) != inputs.param.end())
        {
          *InputValueforTe = true;
          (*TeIN)(i,j).re = *inputs.param.at(parname.str());
        }
      }

    for(int i=1; i<=3; i++)
      for(int j=i; j<=3; j++)
      {
        /**********/
        /* MSL2IN */
        /**********/
        std::stringstream parname;
        parname << "ml2_" << i << j;
        if(inputs.param.find(parname.str()) != inputs.param.end())
        {
          *InputValueforml2 = true;
          (*ml2IN)(i,j).re = *inputs.param.at(parname.str());
        }
        /**********/
        /* MSE2IN */
        /**********/
        parname.str(std::string());
        parname << "me2_" << i << j;
        if(inputs.param.find(parname.str()) != inputs.param.end())
        {
          *InputValueforme2 = true;
          (*me2IN)(i,j).re = *inputs.param.at(parname.str());
        }
        /**********/
        /* MSQ2IN */
        /**********/
        parname.str(std::string());
        parname << "mq2_" << i << j;
        if(inputs.param.find(parname.str()) != inputs.param.end())
        {
          *InputValueformq2 = true;
          (*mq2IN)(i,j).re = *inputs.param.at(parname.str());
        }
        /**********/
        /* MSU2IN */
        /**********/
        parname.str(std::string());
        parname << "mu2_" << i << j;
        if(inputs.param.find(parname.str()) != inputs.param.end())
        {
          *InputValueformu2 = true;
          (*mu2IN)(i,j).re = *inputs.param.at(parname.str());
        }
        /**********/
        /* MSD2IN */
        /**********/
        parname.str(std::string());
        parname << "md2_" << i << j;
        if(inputs.param.find(parname.str()) != inputs.param.end())
        {
          *InputValueformd2 = true;
          (*md2IN)(i,j).re = *inputs.param.at(parname.str());
        }
      }

    /*****************/
    /* Block GAUGEIN */
    /*****************/
    // Irrelevant

    /********************/
    /* Block NMSSMRUNIN */
    /********************/
    // This should be read from EXTPAR

    /****************/
    /* Block HMIXIN */
    /****************/
    // Irrelevant

    /*****************/
    /* Block MSOFTIN */
    /*****************/
    // mHd2
    if(inputs.param.find("mHd2") != inputs.param.end())
    {
      *InputValueformHd2 = true;
      *mHd2IN = *inputs.param.at("mHd2");
    }
    // mHu2
    if(inputs.param.find("mHu2") != inputs.param.end())
    {
      *InputValueformHu2 = true;
      *mHu2IN = *inputs.param.at("mHu2");
    }
    // M_1
    if(inputs.param.find("M1") != inputs.param.end())
    {
      *InputValueforM1 = true;
      M1IN->re = *inputs.param.at("M1");
    }
    // M_2
    if(inputs.param.find("M2") != inputs.param.end())
    {
      *InputValueforM2 = true;
      M2IN->re = *inputs.param.at("M2");
    }
    // M_3
    if(inputs.param.find("M3") != inputs.param.end())
    {
      *InputValueforM3 = true;
      M3IN->re = *inputs.param.at("M3");
    }

    // No other blocks are relevant at this stage

    // now some checks and additional settings
    // This all is already covered in InitializeStandardModel
    /**gmZ = *gamZ * *mZ;
    *gmZ2 = pow(*gmZ, 2);
    *mW2 = *mZ2 * (0.5 + sqrt(0.25 - *Alpha_mZ*pi / (sqrt(2) * *G_F * *mZ2))) / 0.985;
    *mW = sqrt(*mW2); 	// mass
    *mW_SM = *mW;
    *gamW = 2.06;	// width
    *gamW2 = pow(*gamW, 2);
    *gmW = *gamW * *mW;
    *gmW2 = pow(*gmW, 2);
    *Alpha_mZ = Alpha_MSbar(*mZ, *mW);
    CalculateRunningMasses(*mf_l, *mf_d, *mf_u, *Q_light_quarks, *Alpha_mZ, *AlphaS_mZ, *mZ, *mf_l_mZ, *mf_d_mZ, *mf_u_mZ, *kont);*/

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
    *Alpha =  1.0/137.035999074;
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

    for(int i=1; i<=3; i++)
    {
      (*mf_l_mZ)(i) = 0.0;
      (*mf_d_mZ)(i) = 0.0;
      (*mf_u_mZ)(i) = 0.0;
    }
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

  // Scan-level initialisation
  static bool scan_level = true;
  if (scan_level)
  {
    // Dump all internal output
    *ErrCan = 0;

    Set_All_Parameters_0();

    /****************/
    /* Block MODSEL */
    /****************/
    if((*ModelInUse)("NMSSM66atQ"))
    {
      *HighScaleModel = "LOW";
      // BC where all NMSSM parameters are taken at the SUSY scale
      *BoundaryCondition = 3;
    }
    else
    {
      str message = "Model nor recognised";
      logger() << message << EOM;
      invalid_point().raise(message);
    }

    *GenerationMixing = runOptions->getValueOrDef<Flogical>(false, "GenerationMixing");

    if(Param.find("Qin") != Param.end())
    {
      Freal8 RGEScale = pow(*Param.at("Qin"),2);
      SetRGEScale(RGEScale);
    }

  }
  scan_level = false;


}
END_BE_INI_FUNCTION
