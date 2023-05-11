//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
/// Frontend header for SARAH-SPheno 4.0.3 backend,
/// for the gumTHDMII model.
///
///  Authors (add name and date if you modify):    
///       *** Automatically created by GUM ***     
///                                                
///  \author The GAMBIT Collaboration             
///  \date 03:42PM on September 21, 2022
///                                                
///  ********************************************* 

#include "gambit/Backends/frontend_macros.hpp"
#include "gambit/Backends/frontends/SARAHSPheno_gumTHDMII_4_0_3.hpp"
#include "gambit/Elements/spectrum_factories.hpp"
#include "gambit/Models/SimpleSpectra/gumTHDMIISimpleSpec.hpp"
#include "gambit/Utils/version.hpp"

#define BACKEND_DEBUG 0

// Callback function for error handling
BE_NAMESPACE
{
  // This function will be called from SPheno. Needs C linkage, and thus also
  // a backend-specific name to guard against name clashes.
  extern "C"
  void CAT_4(BACKENDNAME,_,SAFE_VERSION,_ErrorHandler)()
  {
    throw std::runtime_error("SARAHSPheno_gumTHDMII backend called TerminateProgram.");
  }
}
END_BE_NAMESPACE

// Convenience functions (definition)
BE_NAMESPACE
{
  
  // Variables and functions to keep and access decay info
  typedef std::tuple<std::vector<int>,int,double> channel_info_triplet; // {pdgs of daughter particles}, spheno index, correction factor
  namespace Fdecays
  {
    // A (pdg,vector) map, where the vector contains a channel_info_triplet for each
    // decay mode of the mother particle. (See typedef of channel_info_triplet above.)
    static std::map<int,std::vector<channel_info_triplet> > all_channel_info;
    
    // Flag indicating whether the decays need to be computed or not.
    static bool BRs_already_calculated = false;
    
    // Function that reads a table of all the possible decays in SARAHSPheno_gumTHDMII
    // and fills the all_channel_info map above
    void fill_all_channel_info(str);
    
    // Helper function to turn a vector<int> into a vector<pairs<int,int> > needed for
    // when calling the GAMBIT DecayTable::set_BF function
    std::vector<std::pair<int,int> > get_pdg_context_pairs(std::vector<int>);
  }
  
  // Convenience function to run SPheno and obtain the spectrum
  int run_SPheno(Spectrum &spectrum, const Finputs &inputs)
  {
    
    *epsI = 1.0E-5;
    *deltaM = 1.0E-6;
    *mGUT = -1.0;
    *ratioWoM = 0.0;
    
    Set_All_Parameters_0();
    
    *kont = 0;
    *delta_mass = 1.0E-4;
    *CTBD = false;
    
    ReadingData(inputs);
    
    try{ SPheno_Main(); }
    catch(std::runtime_error &e) { invalid_point().raise(e.what()); }
    
    if(*kont != 0)
      ErrorHandling(*kont);
    if(*FoundIterativeSolution or *WriteOutputForNonConvergence)
    {
      
      spectrum = Spectrum_Out(inputs);
      
    }
    
    if(*kont != 0)
      ErrorHandling(*kont);
    
    return *kont;
  }
  
  // Helper function to pass the spectrum object to the SPheno frontend and compute the BRs.
  void fill_spectrum_calculate_BRs(const Spectrum &spectrum, const Finputs& inputs)
  {
    if (Fdecays::BRs_already_calculated) return;
    
    // Initialize some variables
    *Iname = 1;
    *CTBD = false;
    *ratioWoM = 0.0;
    *epsI = 1.0E-5;
    *deltaM = 1.0e-6;
    *kont =  0;
    
    // Read options and decay info
    ReadingData_decays(inputs);
    
    // Fill input parameters with spectrum imformation
    
    // Masses
    SMInputs sminputs = spectrum.get_SMInputs();
    (*MFd)(1) = sminputs.mD;
    (*MFd2)(1) = pow((*MFd)(1), 2);
    (*MFd)(2) = sminputs.mS;
    (*MFd2)(2) = pow((*MFd)(2), 2);
    (*MFd)(3) = sminputs.mBmB;
    (*MFd2)(3) = pow((*MFd)(3), 2);
    (*MFu)(1) = sminputs.mU;
    (*MFu2)(1) = pow((*MFu)(1), 2);
    (*MFu)(2) = sminputs.mCmC;
    (*MFu2)(2) = pow((*MFu)(2), 2);
    (*MFu)(3) = sminputs.mT;
    (*MFu2)(3) = pow((*MFu)(3), 2);
    (*MFe)(1) = sminputs.mE;
    (*MFe2)(1) = pow((*MFe)(1), 2);
    (*MFe)(2) = sminputs.mMu;
    (*MFe2)(2) = pow((*MFe)(2), 2);
    (*MFe)(3) = sminputs.mTau;
    (*MFe2)(3) = pow((*MFe)(3), 2);
    (*Mhh)(1) = spectrum.get(Par::Pole_Mass, "h0_1");
    (*Mhh2)(1) = pow((*Mhh)(1), 2);
    (*Mhh)(2) = spectrum.get(Par::Pole_Mass, "h0_2");
    (*Mhh2)(2) = pow((*Mhh)(2), 2);
    (*MAh)(2) = spectrum.get(Par::Pole_Mass, "A0");
    (*MAh2)(2) = pow((*MAh)(2), 2);
    (*MHm)(2) = spectrum.get(Par::Pole_Mass, "H-");
    (*MHm2)(2) = pow((*MHm)(2), 2);
    *MVWm = spectrum.get(Par::Pole_Mass, "W-");
    *MVWm2 = pow(*MVWm,2);
    *MVZ = spectrum.get(Par::Pole_Mass, "Z0");
    *MVZ2 = pow(*MVZ,2);
    
    
    
    // Mixings and other parameters
    *lam1 = spectrum.get(Par::dimensionless, "lam1");
    *lam2 = spectrum.get(Par::dimensionless, "lam2");
    *lam3 = spectrum.get(Par::dimensionless, "lam3");
    *lam4 = spectrum.get(Par::dimensionless, "lam4");
    *lam5 = spectrum.get(Par::dimensionless, "lam5");
    *m112 = spectrum.get(Par::dimensionless, "m112");
    *m222 = spectrum.get(Par::dimensionless, "m222");
    *m122 = spectrum.get(Par::dimensionless, "m122");
    *vd = spectrum.get(Par::dimensionless, "vd");
    *vu = spectrum.get(Par::dimensionless, "vu");
    *TanBeta = spectrum.get(Par::dimensionless, "TanBeta");
    for(int i=1; i<=2; i++)
    {
      for(int j=1; j<=2; j++)
      {
        (*ZH)(i, j) = spectrum.get(Par::Pole_Mixing, "ZH", i, j);
      }
    }
    for(int i=1; i<=2; i++)
    {
      for(int j=1; j<=2; j++)
      {
        (*ZA)(i, j) = spectrum.get(Par::Pole_Mixing, "ZA", i, j);
      }
    }
    for(int i=1; i<=2; i++)
    {
      for(int j=1; j<=2; j++)
      {
        (*ZP)(i, j) = spectrum.get(Par::Pole_Mixing, "ZP", i, j);
      }
    }
    *g1 = spectrum.get(Par::dimensionless, "g1");
    *g2 = spectrum.get(Par::dimensionless, "g2");
    *g3 = spectrum.get(Par::dimensionless, "g3");
    *sinW2 = spectrum.get(Par::Pole_Mixing, "sinW2");
    for(int i=1; i<=3; i++)
    {
      for(int j=1; j<=3; j++)
      {
        (*Yd)(i, j) = spectrum.get(Par::dimensionless, "Yd", i, j);
      }
    }
    for(int i=1; i<=3; i++)
    {
      for(int j=1; j<=3; j++)
      {
        (*Yu)(i, j) = spectrum.get(Par::dimensionless, "Yu", i, j);
      }
    }
    for(int i=1; i<=3; i++)
    {
      for(int j=1; j<=3; j++)
      {
        (*Ye)(i, j) = spectrum.get(Par::dimensionless, "Ye", i, j);
      }
    }
    *v = sqrt(pow(*vd,2) + pow(*vu,2));
    *betaH = asin(abs((*ZP)(1,2)));
    *alphaH = atan((*ZH)(2,2)/(*ZH)(1,2));
    
    // Call SPheno's function to calculate decays
    try{ CalculateBR_2(*CTBD,*ratioWoM,*epsI,*deltaM,*kont,*MAh,*MAh2,*MFd,*MFd2,*MFe,*MFe2,*MFu,*MFu2,*Mhh,*Mhh2,*MHm,*MHm2,*MVWm,*MVWm2,*MVZ,*MVZ2,*TW,*ZDR,*ZER,*ZUR,*v,*ZDL,*ZEL,*ZUL,*ZA,*ZH,*ZP,*ZW,*ZZ,*alphaH,*betaH,*vd,*vu,*g1,*g2,*g3,*lam5,*lam1,*lam4,*lam3,*lam2,*Yu,*Yd,*Ye,*m122,*m112,*m222,*gPFu,*gTFu,*BRFu,*gPFe,*gTFe,*BRFe,*gPFd,*gTFd,*BRFd,*gPhh,*gThh,*BRhh,*gPAh,*gTAh,*BRAh,*gPHm,*gTHm,*BRHm); }
    catch(std::runtime_error &e) { invalid_point().raise(e.what()); }
    
    // Check for errors
    if(*kont != 0)
      ErrorHandling(*kont);
    
    Fdecays::BRs_already_calculated = true;
    
  }
  
  // Convenience function to run Spheno and obtain the decays
  int run_SPheno_decays(const Spectrum &spectrum, DecayTable& decays, const Finputs& inputs)
  {
    
    double BRMin = inputs.options->getValueOrDef<double>(1e-5, "BRMin");
    
    // Pass the GAMBIT spectrum to SPheno and fill the internal decay objects
    fill_spectrum_calculate_BRs(spectrum, inputs);
    
    if(*kont != 0)
      ErrorHandling(*kont);
    
    // Fill in info about the entry for all decays
    DecayTable::Entry entry;
    entry.calculator = STRINGIFY(BACKENDNAME);
    entry.calculator_version = STRINGIFY(VERSION);
    entry.positive_error = 0.0;
    entry.negative_error = 0.0;
    
    // Helper variables
    std::vector<int> daughter_pdgs;
    int spheno_index;
    double corrf;
    
    std::vector<int> pdg = {
      25, // h1
      35, // h2
      36, // Ah2
      37, // Hm2
      1, // Fd1
      3, // Fd2
      5, // Fd3
      2, // Fu1
      4, // Fu2
      6, // Fu3
      11, // Fe1
      13, // Fe2
      15 // Fe3
    };
    int n_particles = pdg.size();
    auto gT = [&](int i)
    {
      if(i==1) return (*gThh)(i-0);
      else if(i==2) return (*gThh)(i-0);
      else if(i==3) return (*gTAh)(i-1);
      else if(i==4) return (*gTHm)(i-2);
      else if(i==5) return (*gTFd)(i-4);
      else if(i==6) return (*gTFd)(i-4);
      else if(i==7) return (*gTFd)(i-4);
      else if(i==8) return (*gTFu)(i-7);
      else if(i==9) return (*gTFu)(i-7);
      else if(i==10) return (*gTFu)(i-7);
      else if(i==11) return (*gTFe)(i-10);
      else if(i==12) return (*gTFe)(i-10);
      else if(i==13) return (*gTFe)(i-10);
      return 0.0;
    };
    
    auto gP = [&](int i, int j)
    {
      if(i==1) return (*gPhh)(i-0 ,j);
      else if(i==2) return (*gPhh)(i-0 ,j);
      else if(i==3) return (*gPAh)(i-1 ,j);
      else if(i==4) return (*gPHm)(i-2 ,j);
      else if(i==5) return (*gPFd)(i-4 ,j);
      else if(i==6) return (*gPFd)(i-4 ,j);
      else if(i==7) return (*gPFd)(i-4 ,j);
      else if(i==8) return (*gPFu)(i-7 ,j);
      else if(i==9) return (*gPFu)(i-7 ,j);
      else if(i==10) return (*gPFu)(i-7 ,j);
      else if(i==11) return (*gPFe)(i-10 ,j);
      else if(i==12) return (*gPFe)(i-10 ,j);
      else if(i==13) return (*gPFe)(i-10 ,j);
      return 0.0;
    };
    
    auto gT1L = [&](int i)
    {
      if(i==1) return (*gT1Lhh)(i-0);
      else if(i==2) return (*gT1Lhh)(i-0);
      else if(i==3) return (*gT1LAh)(i-1);
      else if(i==4) return (*gT1LHm)(i-2);
      else if(i==5) return (*gT1LFd)(i-4);
      else if(i==6) return (*gT1LFd)(i-4);
      else if(i==7) return (*gT1LFd)(i-4);
      else if(i==8) return (*gT1LFu)(i-7);
      else if(i==9) return (*gT1LFu)(i-7);
      else if(i==10) return (*gT1LFu)(i-7);
      else if(i==11) return (*gT1LFe)(i-10);
      else if(i==12) return (*gT1LFe)(i-10);
      else if(i==13) return (*gT1LFe)(i-10);
      return 0.0;
    };
    
    auto gP1L = [&](int i, int j)
    {
      if(i==1) return (*gP1Lhh)(i-0 ,j);
      else if(i==2) return (*gP1Lhh)(i-0 ,j);
      else if(i==3) return (*gP1LAh)(i-1 ,j);
      else if(i==4) return (*gP1LHm)(i-2 ,j);
      else if(i==5) return (*gP1LFd)(i-4 ,j);
      else if(i==6) return (*gP1LFd)(i-4 ,j);
      else if(i==7) return (*gP1LFd)(i-4 ,j);
      else if(i==8) return (*gP1LFu)(i-7 ,j);
      else if(i==9) return (*gP1LFu)(i-7 ,j);
      else if(i==10) return (*gP1LFu)(i-7 ,j);
      else if(i==11) return (*gP1LFe)(i-10 ,j);
      else if(i==12) return (*gP1LFe)(i-10 ,j);
      else if(i==13) return (*gP1LFe)(i-10 ,j);
      return 0.0;
    };
    
    for(int i=0; i<n_particles; i++)
    {
      std::vector<channel_info_triplet> civ = Fdecays::all_channel_info.at(pdg[i]);
      entry.width_in_GeV = gT(i+1);
      entry.channels.clear();
      for(channel_info_triplet ci : civ)
      {
        std::tie(daughter_pdgs, spheno_index, corrf) = ci;
        double BR = 0.;
        if(!*OneLoopDecays)
          BR = gP(i+1,spheno_index)/gT(i+1);
        else
        {
          // One loop decays are only available for 2 body decays
          if(daughter_pdgs.size() <= 2)
            BR = gP1L(i+1,spheno_index)/gT1L(i+1);
        }
        // If below the minimum BR, add the decay to the DecayTable as a zero entry.
        // If decay is zero and channel exists, do not overwrite.
        if(BR * corrf > BRMin)
          entry.set_BF(BR * corrf, 0.0, Fdecays::get_pdg_context_pairs(daughter_pdgs));
        else if(!entry.has_channel(Fdecays::get_pdg_context_pairs(daughter_pdgs)))
          entry.set_BF(0., 0., Fdecays::get_pdg_context_pairs(daughter_pdgs));
      }
      // SM fermions in flavour basis, everything else in mass basis
      if(abs(pdg[i]) < 17)
        decays(Models::ParticleDB().long_name(pdg[i],1)) = entry;
      else
        decays(Models::ParticleDB().long_name(pdg[i],0)) = entry;
    }
    
    // Add W and Z decays manually
    entry.width_in_GeV = *gamW;
    entry.channels.clear();
    entry.set_BF((*BrWqq)(1), 0.0, {iipair(1,0),iipair(-2,0)});
    entry.set_BF((*BrWqq)(2), 0.0, {iipair(3,0),iipair(-4,0)});
    for(int i=1; i<=3; i++) entry.set_BF((*BrWln)(i), 0.0, {iipair(9+2*i,0),iipair(-9-2*i-1,0)});
    decays(Models::ParticleDB().long_name(24,0)) = entry;
    entry.width_in_GeV = *gamZ;
    entry.channels.clear();
    for(int i=1; i<=5; i++) entry.set_BF((*BrZqq)(i), 0.0, {iipair(i,0),iipair(-i,0)});
    for(int i=1; i<=3; i++) entry.set_BF((*BrZll)(i), 0.0, {iipair(9+2*i,0),iipair(-9-2*i,0)});
    for(int i=1; i<=3; i++) entry.set_BF(*BrZinv/3, 0.0, {iipair(10+2*i,0),iipair(-10-2*i,0)});
    decays(Models::ParticleDB().long_name(23,0)) = entry;
    
    return *kont;
  }
  
  // Convenience function to convert internal SPheno variables into a Spectrum object
  Spectrum Spectrum_Out(const Finputs &inputs)
  {
    
    SLHAstruct slha;
    
    Freal8 Q;
    try{ Q = sqrt(GetRenormalizationScale()); }
    catch(std::runtime_error &e) { invalid_point().raise(e.what()); }
    
    // Spectrum generator information
    SLHAea_add_block(slha, "SPINFO");
    SLHAea_add(slha, "SPINFO", 1, "GAMBIT, using "+str(STRINGIFY(BACKENDNAME))+" from SARAH");
    SLHAea_add(slha, "SPINFO", 2, gambit_version()+" (GAMBIT); "+str(STRINGIFY(VERSION))+" ("+str(STRINGIFY(BACKENDNAME))+"); "+str(STRINGIFY(SARAH_VERSION))+" (SARAH)");
    
    // Block MODSEL
    SLHAea_add_block(slha, "MODSEL");
    slha["MODSEL"][""] << 1 << 1 << "# GUT scale input";
    slha["MODSEL"][""] << 2 << *BoundaryCondition << "# Boundary conditions";
    slha["MODSEL"][""] << 5 << 1 << "# Switching on CP violations";
    if(*GenerationMixing)
      slha["MODSEL"][""] << 6 << 1 << "# switching on flavour violation";
    if(inputs.param.find("Qin") != inputs.param.end())
      slha["MODSEL"][""] << 12 << *inputs.param.at("Qin") << "# Qin";
    
    
    // Block SMINPUTS
    SLHAea_add_block(slha, "SMINPUTS");
    slha["SMINPUTS"][""] << 1 << 1.0 / *Alpha_mZ_MS << "# alpha_em^-1(MZ)^MSbar";
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
    
    SLHAea_add_block(slha, "HMIX", Q);
    SLHAea_add_block(slha, "IMHMIX", Q);
    slha["HMIX"][""] << 31 << lam1->re << "# Re(lam1)";
    slha["IMHMIX"][""] << 31 << lam1->im << "# Im(lam1)";
    slha["HMIX"][""] << 32 << lam2->re << "# Re(lam2)";
    slha["IMHMIX"][""] << 32 << lam2->im << "# Im(lam2)";
    slha["HMIX"][""] << 33 << lam3->re << "# Re(lam3)";
    slha["IMHMIX"][""] << 33 << lam3->im << "# Im(lam3)";
    slha["HMIX"][""] << 34 << lam4->re << "# Re(lam4)";
    slha["IMHMIX"][""] << 34 << lam4->im << "# Im(lam4)";
    slha["HMIX"][""] << 35 << lam5->re << "# Re(lam5)";
    slha["IMHMIX"][""] << 35 << lam5->im << "# Im(lam5)";
    slha["HMIX"][""] << 20 << m112->re << "# Re(m112)";
    slha["IMHMIX"][""] << 20 << m112->im << "# Im(m112)";
    slha["HMIX"][""] << 21 << m222->re << "# Re(m222)";
    slha["IMHMIX"][""] << 21 << m222->im << "# Im(m222)";
    slha["HMIX"][""] << 22 << m122->re << "# Re(m122)";
    slha["IMHMIX"][""] << 22 << m122->im << "# Im(m122)";
    slha["HMIX"][""] << 102 << *vd << "# vd";
    slha["HMIX"][""] << 103 << *vu << "# vu";
    slha["HMIX"][""] << 2 << *TanBeta << "# TanBeta";
    
    SLHAea_add_block(slha, "SCALARMIX", Q);
    for(int i=1; i<=2; i++)
    {
      for(int j=1; j<=2; j++)
      {
        slha["SCALARMIX"][""] << i << j << (*ZH)(i,j) << "# SCALARMIX(" << i << "," << j << ")";
      }
    }
    
    SLHAea_add_block(slha, "PSEUDOSCALARMIX", Q);
    for(int i=1; i<=2; i++)
    {
      for(int j=1; j<=2; j++)
      {
        slha["PSEUDOSCALARMIX"][""] << i << j << (*ZA)(i,j) << "# PSEUDOSCALARMIX(" << i << "," << j << ")";
      }
    }
    
    SLHAea_add_block(slha, "CHARGEMIX", Q);
    for(int i=1; i<=2; i++)
    {
      for(int j=1; j<=2; j++)
      {
        slha["CHARGEMIX"][""] << i << j << (*ZP)(i,j) << "# CHARGEMIX(" << i << "," << j << ")";
      }
    }
    
    SLHAea_add_block(slha, "UULMIX", Q);
    SLHAea_add_block(slha, "IMUULMIX", Q);
    for(int i=1; i<=3; i++)
    {
      for(int j=1; j<=3; j++)
      {
        slha["UULMIX"][""] << i << j << (*ZUL)(i,j).re << "# UULMIX(" << i << "," << j << ")";
        slha["IMUULMIX"][""] << i << j << (*ZUL)(i,j).im << "# Im(UULMIX(" << i << "," << j << "))";
      }
    }
    
    SLHAea_add_block(slha, "UDLMIX", Q);
    SLHAea_add_block(slha, "IMUDLMIX", Q);
    for(int i=1; i<=3; i++)
    {
      for(int j=1; j<=3; j++)
      {
        slha["UDLMIX"][""] << i << j << (*ZDL)(i,j).re << "# UDLMIX(" << i << "," << j << ")";
        slha["IMUDLMIX"][""] << i << j << (*ZDL)(i,j).im << "# Im(UDLMIX(" << i << "," << j << "))";
      }
    }
    
    SLHAea_add_block(slha, "UURMIX", Q);
    SLHAea_add_block(slha, "IMUURMIX", Q);
    for(int i=1; i<=3; i++)
    {
      for(int j=1; j<=3; j++)
      {
        slha["UURMIX"][""] << i << j << (*ZUR)(i,j).re << "# UURMIX(" << i << "," << j << ")";
        slha["IMUURMIX"][""] << i << j << (*ZUR)(i,j).im << "# Im(UURMIX(" << i << "," << j << "))";
      }
    }
    
    SLHAea_add_block(slha, "UDRMIX", Q);
    SLHAea_add_block(slha, "IMUDRMIX", Q);
    for(int i=1; i<=3; i++)
    {
      for(int j=1; j<=3; j++)
      {
        slha["UDRMIX"][""] << i << j << (*ZDR)(i,j).re << "# UDRMIX(" << i << "," << j << ")";
        slha["IMUDRMIX"][""] << i << j << (*ZDR)(i,j).im << "# Im(UDRMIX(" << i << "," << j << "))";
      }
    }
    
    SLHAea_add_block(slha, "UELMIX", Q);
    SLHAea_add_block(slha, "IMUELMIX", Q);
    for(int i=1; i<=3; i++)
    {
      for(int j=1; j<=3; j++)
      {
        slha["UELMIX"][""] << i << j << (*ZEL)(i,j).re << "# UELMIX(" << i << "," << j << ")";
        slha["IMUELMIX"][""] << i << j << (*ZEL)(i,j).im << "# Im(UELMIX(" << i << "," << j << "))";
      }
    }
    
    SLHAea_add_block(slha, "UERMIX", Q);
    SLHAea_add_block(slha, "IMUERMIX", Q);
    for(int i=1; i<=3; i++)
    {
      for(int j=1; j<=3; j++)
      {
        slha["UERMIX"][""] << i << j << (*ZER)(i,j).re << "# UERMIX(" << i << "," << j << ")";
        slha["IMUERMIX"][""] << i << j << (*ZER)(i,j).im << "# Im(UERMIX(" << i << "," << j << "))";
      }
    }
    
    SLHAea_add_block(slha, "MINPAR", Q);
    SLHAea_add_block(slha, "IMMINPAR", Q);
    slha["MINPAR"][""] << 1 << Lambda1Input->re << "# Re(Lambda1Input)";
    slha["IMMINPAR"][""] << 1 << Lambda1Input->im << "# Im(Lambda1Input)";
    slha["MINPAR"][""] << 2 << Lambda2Input->re << "# Re(Lambda2Input)";
    slha["IMMINPAR"][""] << 2 << Lambda2Input->im << "# Im(Lambda2Input)";
    slha["MINPAR"][""] << 3 << Lambda3Input->re << "# Re(Lambda3Input)";
    slha["IMMINPAR"][""] << 3 << Lambda3Input->im << "# Im(Lambda3Input)";
    slha["MINPAR"][""] << 4 << Lambda4Input->re << "# Re(Lambda4Input)";
    slha["IMMINPAR"][""] << 4 << Lambda4Input->im << "# Im(Lambda4Input)";
    slha["MINPAR"][""] << 5 << Lambda5Input->re << "# Re(Lambda5Input)";
    slha["IMMINPAR"][""] << 5 << Lambda5Input->im << "# Im(Lambda5Input)";
    slha["MINPAR"][""] << 9 << M122input->re << "# Re(M122input)";
    slha["IMMINPAR"][""] << 9 << M122input->im << "# Im(M122input)";
    slha["MINPAR"][""] << 10 << *TanBeta << "# TanBeta";
    
    SLHAea_add_block(slha, "HMIXIN", Q);
    SLHAea_add_block(slha, "IMHMIXIN", Q);
    slha["HMIXIN"][""] << 35 << lam5->re << "# Re(lam5)";
    slha["IMHMIXIN"][""] << 35 << lam5->im << "# Im(lam5)";
    slha["HMIXIN"][""] << 31 << lam1->re << "# Re(lam1)";
    slha["IMHMIXIN"][""] << 31 << lam1->im << "# Im(lam1)";
    slha["HMIXIN"][""] << 34 << lam4->re << "# Re(lam4)";
    slha["IMHMIXIN"][""] << 34 << lam4->im << "# Im(lam4)";
    slha["HMIXIN"][""] << 33 << lam3->re << "# Re(lam3)";
    slha["IMHMIXIN"][""] << 33 << lam3->im << "# Im(lam3)";
    slha["HMIXIN"][""] << 32 << lam2->re << "# Re(lam2)";
    slha["IMHMIXIN"][""] << 32 << lam2->im << "# Im(lam2)";
    slha["HMIXIN"][""] << 22 << m122->re << "# Re(m122)";
    slha["IMHMIXIN"][""] << 22 << m122->im << "# Im(m122)";
    slha["HMIXIN"][""] << 20 << m112->re << "# Re(m112)";
    slha["IMHMIXIN"][""] << 20 << m112->im << "# Im(m112)";
    slha["HMIXIN"][""] << 21 << m222->re << "# Re(m222)";
    slha["IMHMIXIN"][""] << 21 << m222->im << "# Im(m222)";
    
    SLHAea_add_block(slha, "GAUGE", Q);
    slha["GAUGE"][""] << 1 << *g1 << "# g1";
    slha["GAUGE"][""] << 2 << *g2 << "# g2";
    slha["GAUGE"][""] << 3 << *g3 << "# g3";
    
    SLHAea_add_block(slha, "YD", Q);
    SLHAea_add_block(slha, "IMYD", Q);
    for(int i=1; i<=3; i++)
    {
      for(int j=1; j<=3; j++)
      {
        slha["YD"][""] << i << j << (*Yd)(i,j).re << "# YD(" << i << "," << j << ")";
        slha["IMYD"][""] << i << j << (*Yd)(i,j).im << "# Im(YD(" << i << "," << j << "))";
      }
    }
    
    SLHAea_add_block(slha, "YU", Q);
    SLHAea_add_block(slha, "IMYU", Q);
    for(int i=1; i<=3; i++)
    {
      for(int j=1; j<=3; j++)
      {
        slha["YU"][""] << i << j << (*Yu)(i,j).re << "# YU(" << i << "," << j << ")";
        slha["IMYU"][""] << i << j << (*Yu)(i,j).im << "# Im(YU(" << i << "," << j << "))";
      }
    }
    
    SLHAea_add_block(slha, "YE", Q);
    SLHAea_add_block(slha, "IMYE", Q);
    for(int i=1; i<=3; i++)
    {
      for(int j=1; j<=3; j++)
      {
        slha["YE"][""] << i << j << (*Ye)(i,j).re << "# YE(" << i << "," << j << ")";
        slha["IMYE"][""] << i << j << (*Ye)(i,j).im << "# Im(YE(" << i << "," << j << "))";
      }
    }
    
    // Block MASS
    SLHAea_add_block(slha, "MASS");
    slha["MASS"][""] << 25 << (*Mhh)(1) << "# h1_1";
    slha["MASS"][""] << 35 << (*Mhh)(2) << "# h2_2";
    slha["MASS"][""] << 36 << (*MAh)(2) << "# Ah2_2";
    slha["MASS"][""] << 37 << (*MHm)(2) << "# Hm2_2";
    slha["MASS"][""] << 23 << *MVZ << "# VZ";
    slha["MASS"][""] << 24 << *MVWm << "# VWm";
    
    // Check whether any of the masses is NaN
    auto block = slha["MASS"];
    for(auto it = block.begin(); it != block.end(); it++)
    {
      if((*it)[0] != "BLOCK" and Utils::isnan(stod((*it)[1])) )
      {
        std::stringstream message;
        message << "Error in spectrum generator: mass of " << Models::ParticleDB().long_name(std::pair<int,int>(stoi((*it)[0]),0)) << " is NaN";
        logger() << message.str() << EOM;
        invalid_point().raise(message.str());
      }
    }
    
    // Block DMASS
    if(*GetMassUncertainty)
    {
      SLHAea_add_block(slha, "DMASS");
      slha["DMASS"][""] << 25 << sqrt(pow((*mass_uncertainty_Q)(1),2)+pow((*mass_uncertainty_Yt)(1),2)) << "# h1_1";
      slha["DMASS"][""] << 35 << sqrt(pow((*mass_uncertainty_Q)(2),2)+pow((*mass_uncertainty_Yt)(2),2)) << "# h2_2";
      slha["DMASS"][""] << 36 << sqrt(pow((*mass_uncertainty_Q)(4),2)+pow((*mass_uncertainty_Yt)(4),2)) << "# Ah2_2";
      slha["DMASS"][""] << 37 << sqrt(pow((*mass_uncertainty_Q)(6),2)+pow((*mass_uncertainty_Yt)(6),2)) << "# Hm2_2";
      
      // Do the W mass separately.  Here we use 10 MeV based on the size of corrections from two-loop papers and advice from Dominik Stockinger.
      slha["DMASS"][""] << 24 << 0.01 / *mW << " # mW";
    }
    
    // Block SPhenoINFO
    SLHAea_add_block(slha, "SPhenoInput");
    slha["SPheno"][""] << 1 << *ErrorLevel << "# ErrorLevel";
    slha["SPheno"][""] << 2 << *SPA_convention << "# SPA_conventions";
    slha["SPheno"][""] << 8 << *TwoLoopMethod << "# Two Loop Method";
    slha["SPheno"][""] << 9 << *GaugelessLimit << "# Gauge-less limit";
    slha["SPheno"][""] << 31 << *mGUT << "# GUT scale";
    slha["SPheno"][""] << 33 << Q << "# Renormalization scale";
    slha["SPheno"][""] << 34 << *delta_mass << "# Precision";
    slha["SPheno"][""] << 35 << *n_run << "# Iterations";
    if(*TwoLoopRGE)
      slha["SPheno"][""] << 38 << 2 << "# RGE level";
    else
    slha["SPheno"][""] << 38 << 1 << "# RGE level";
    slha["SPheno"][""] << 40 << 1.0 / *Alpha << "# Alpha^-1";
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
    
    
    // Has the user chosen to override any pole mass values?
    // This will typically break consistency, but may be useful in some special cases
    if (inputs.options->hasKey("override_pole_masses"))
    {
      std::vector<str> particle_names = inputs.options->getNames("override_pole_masses");
      for (auto& name : particle_names)
      {
        double mass = inputs.options->getValue<double>("override_pole_masses", name);
        SLHAea_add(slha, "MASS", Models::ParticleDB().pdg_pair(name).first, mass, name, true);
      }
    }
    
    //Create Spectrum object
    static const Spectrum::mc_info mass_cut;
    static const Spectrum::mr_info mass_ratio_cut;
    Spectrum spectrum = spectrum_from_SLHAea<Gambit::Models::gumTHDMIISimpleSpec, SLHAstruct>(slha,slha,mass_cut,mass_ratio_cut);
    
    return spectrum;
    
  }
  
  // Convenience function to obtain a HiggsCouplingsTable object for HiggsBounds
  int get_HiggsCouplingsTable(const Spectrum& spectrum, HiggsCouplingsTable& hctbl, const Finputs& inputs)
  {
    
    // Pass the GAMBIT spectrum to SPheno and fill the internal decay objects (if necessary)
    fill_spectrum_calculate_BRs(spectrum, inputs);
    
    if(*kont != 0)
      ErrorHandling(*kont);
    
    /* Fill in effective coupling ratios.
      These are the ratios of BR_BSM(channel)/BR_SM(channel) */
    
    // Couplings to SM fermions and gauge bosons
    hctbl.C_WW[0] = (*rHB_S_VWm)(1); // Coupling (h0_1 W+ W-)
    hctbl.C_WW[1] = (*rHB_S_VWm)(2); // Coupling (h0_2 W+ W-)
    hctbl.C_WW[2] = (*rHB_P_VWm)(2); // Coupling (A0_1 W+ W-)
    hctbl.C_ZZ[0] = (*rHB_S_VZ)(1); // Coupling (h0_1 Z Z)
    hctbl.C_ZZ[1] = (*rHB_S_VZ)(2); // Coupling (h0_2 Z Z)
    hctbl.C_ZZ[2] = (*rHB_P_VZ)(2); // Coupling (A0_1 Z Z)
    hctbl.C_bb2[0] = pow( (*rHB_S_S_Fd)(1,3), 2 ); // Coupling (h0_1 b bbar)
    hctbl.C_bb2[1] = pow( (*rHB_S_S_Fd)(2,3), 2 ); // Coupling (h0_2 b bbar)
    hctbl.C_bb2[2] = pow( (*rHB_P_P_Fd)(2,3), 2 ); // Coupling (A0_1 b bbar)
    hctbl.C_cc2[0] = pow( (*rHB_S_S_Fu)(1,2), 2 ); // Coupling (h0_1 c cbar)
    hctbl.C_cc2[1] = pow( (*rHB_S_S_Fu)(2,2), 2 ); // Coupling (h0_2 c cbar)
    hctbl.C_cc2[2] = pow( (*rHB_P_P_Fu)(2,2), 2 ); // Coupling (A0_1 c cbar)
    hctbl.C_gaga2[0] = pow( (*ratioPP)(1).re, 2 ); // Coupling (h0_1 gamma gamma)
    hctbl.C_gaga2[1] = pow( (*ratioPP)(2).re, 2 ); // Coupling (h0_2 gamma gamma)
    hctbl.C_gaga2[2] = pow( (*ratioPPP)(2).re, 2 ); // Coupling (A0_1 gamma gamma)
    hctbl.C_gg2[0] = pow( (*ratioGG)(1).re, 2 ); // Coupling (h0_1 glu glu)
    hctbl.C_gg2[1] = pow( (*ratioGG)(2).re, 2 ); // Coupling (h0_2 glu glu)
    hctbl.C_gg2[2] = pow( (*ratioPGG)(2).re, 2 ); // Coupling (A0_1 glu glu)
    hctbl.C_mumu2[0] = pow( (*rHB_S_S_Fe)(1,2), 2 ); // Coupling (h0_1 mu+ mu-)
    hctbl.C_mumu2[1] = pow( (*rHB_S_S_Fe)(2,2), 2 ); // Coupling (h0_2 mu+ mu-)
    hctbl.C_mumu2[2] = pow( (*rHB_P_P_Fe)(2,2), 2 ); // Coupling (A0_1 mu+ mu-)
    hctbl.C_ss2[0] = pow( (*rHB_S_S_Fd)(1,2), 2 ); // Coupling (h0_1 s sbar)
    hctbl.C_ss2[1] = pow( (*rHB_S_S_Fd)(2,2), 2 ); // Coupling (h0_2 s sbar)
    hctbl.C_ss2[2] = pow( (*rHB_P_P_Fd)(2,2), 2 ); // Coupling (A0_1 s sbar)
    hctbl.C_tautau2[0] = pow( (*rHB_S_S_Fe)(1,3), 2 ); // Coupling (h0_1 tau+ tau-)
    hctbl.C_tautau2[1] = pow( (*rHB_S_S_Fe)(2,3), 2 ); // Coupling (h0_2 tau+ tau-)
    hctbl.C_tautau2[2] = pow( (*rHB_P_P_Fe)(2,3), 2 ); // Coupling (A0_1 tau+ tau-)
    hctbl.C_tt2[0] = pow( (*rHB_S_S_Fu)(1,3), 2 ); // Coupling (h0_1 t tbar)
    hctbl.C_tt2[1] = pow( (*rHB_S_S_Fu)(2,3), 2 ); // Coupling (h0_2 t tbar)
    hctbl.C_tt2[2] = pow( (*rHB_P_P_Fu)(2,3), 2 ); // Coupling (A0_1 t tbar)
    
    // hhZ effective couplings. This is symmetrised (i.e. j,i = i,j)
    hctbl.C_hiZ[0][0] = (*CPL_H_H_Z)(1,1).re; // Coupling (h0_1 h0_1 Z)
    hctbl.C_hiZ[0][1] = (*CPL_H_H_Z)(1,2).re; // Coupling (h0_1 h0_2 Z)
    hctbl.C_hiZ[1][0] = (*CPL_H_H_Z)(2,1).re; // Coupling (h0_2 h0_1 Z)
    hctbl.C_hiZ[1][1] = (*CPL_H_H_Z)(2,2).re; // Coupling (h0_2 h0_2 Z)
    hctbl.C_hiZ[0][0] = (*CPL_A_H_Z)(1,2).re; // Coupling (A0_1 h0_2 Z)
    hctbl.C_hiZ[0][0] = (*CPL_A_H_Z)(1,2).re; // Coupling (h0_2 A0_1 Z)
    hctbl.C_hiZ[1][0] = (*CPL_A_H_Z)(2,2).re; // Coupling (A0_1 h0_2 Z)
    hctbl.C_hiZ[0][1] = (*CPL_A_H_Z)(2,2).re; // Coupling (h0_2 A0_1 Z)
    //hctbl.C_hiZ2[0][0] = (*CPL_A_A_Z)(2,2).re; // Coupling (A0_1 A0_1 Z)
    
    // Check there's no errors
    if(*kont != 0)
      ErrorHandling(*kont);
    
    return *kont;
  }
  
  // Function to read data from the Gambit inputs and fill SPheno internal variables
  void ReadingData(const Finputs &inputs)
  {
    
    InitializeStandardModel(inputs.sminputs);
    try{ InitializeLoopFunctions(); }
    catch(std::runtime_error &e) { invalid_point().raise(e.what()); }
    
    *ErrorLevel = -1;
    //*GenerationMixing = true;
    
    try{ Set_All_Parameters_0(); }
    catch(std::runtime_error &e) { invalid_point().raise(e.what()); }
    
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
    // Some hadron constants, not really needed
    
    /***************/
    /* Block FMASS */
    /***************/
    // Masses of hadrons, not really needed
    
    /***************/
    /* Block FLIFE */
    /***************/
    // Lifetimes of hadrons, not really needed
    
    /*******************************/
    /* Block SPHENOINPUT (options) */
    /*******************************/
    // 1, Error_Level
    *ErrorLevel = inputs.options->getValueOrDef<Finteger>(-1, "ErrorLevel");
    
    // 2, SPA_convention
    *SPA_convention = inputs.options->getValueOrDef<bool>(false, "SPA_convention");
    if(*SPA_convention)
    {
      Freal8 scale = 1.0E6;  // SPA convention is 1 TeV
      try {SetRGEScale(scale); }
      catch(std::runtime_error &e) { invalid_point().raise(e.what()); }
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
    *CalculateTwoLoopHiggsMasses = inputs.options->getValueOrDef<bool>(true, "CalculateTwoLoopHiggsMasses");
    
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
    *GaugelessLimit = inputs.options->getValueOrDef<bool>(true, "GaugelessLimit");
    
    // 400, hstep_pn
    *hstep_pn = inputs.options->getValueOrDef<Freal8>(0.1, "hstep_pn");
    
    // 401, hstep_pn
    *hstep_sa = inputs.options->getValueOrDef<Freal8>(0.001, "hstep_sa");
    
    // 410, TwoLoopRegulatorMass
    *TwoLoopRegulatorMass = inputs.options->getValueOrDef<Freal8>(0.0, "TwoLoopRegulatorMass");
    
    // 10, TwoLoopSafeMode
    *TwoLoopSafeMode = inputs.options->getValueOrDef<bool>(false, "TwoLoopSafeMode");
    
    // 11, whether to calculate branching ratios or not, L_BR
    // All BR details are taken by other convenience function
    *L_BR = false;
    
    // 12, minimal value such that a branching ratio is written out, BRMin
    // All BR details are taken by other convenience function
    
    // 13, 3 boday decays
    // All BR details are taken by other convenience function
    
    // 14, run SUSY couplings to scale of decaying particle
    // All BR details are taken by other convenience function
    
    // 15, MinWidth
    // All BR details are taken by other convenience function
    
    // 16. OneLoopDecays
    // All BR details are taken by other convenience function
    
    // 19, MatchingOrder: maximal number of iterations
    *MatchingOrder = inputs.options->getValueOrDef<Finteger>(-2, "MatchingOrder");
    
    // 20, GetMassUncertainty
    *GetMassUncertainty = inputs.options->getValueOrDef<bool>(false, "GetMassUncertainty");
    
    // 21-26, whether to calculate cross sections or not, L_CS
    *L_CS = false;
    
    // 31, setting a fixed GUT scale, GUTScale
    Freal8 GUTScale = inputs.options->getValueOrDef<Freal8>(0.0, "GUTScale");
    if(GUTScale > 0.0)
    {
      try{ SetGUTScale(GUTScale); }
      catch(std::runtime_error &e) { invalid_point().raise(e.what()); }
    }
    
    // 32, requires strict unification, StrictUnification
    Flogical StrictUnification = inputs.options->getValueOrDef<bool>(false, "StrictUnification");
    if(StrictUnification)
    {
      try{ SetStrictUnification(StrictUnification); }
      catch(std::runtime_error &e) { invalid_point().raise(e.what()); }
    }
    
    // 33, setting a fixed renormalization scale
    Freal8 RGEScale = inputs.options->getValueOrDef<Freal8>(0.0, "RGEScale");
    if(RGEScale > 0.0)
    {
      RGEScale *= RGEScale;
      try{ SetRGEScale(RGEScale); }
      catch(std::runtime_error &e) { invalid_point().raise(e.what()); }
    }
    
    // 34, precision of mass calculation, delta_mass
    *delta_mass = inputs.options->getValueOrDef<Freal8>(0.00001, "delta_mass");
    
    // 35, maximal number of iterations, n_run
    *n_run = inputs.options->getValueOrDef<Finteger>(40, "n_run");
    
    // 36, minimal number of iterations
    *MinimalNumberIterations = inputs.options->getValueOrDef<Finteger>(5, "MinimalNumberIterations");
    
    // 37, if = 1 -> CKM through V_u, if = 2 CKM through V_d, YukawaScheme
    Finteger YukawaScheme = inputs.options->getValueOrDef<Finteger>(1, "YukawaScheme");
    if(YukawaScheme == 1 or YukawaScheme == 2)
    {
      try{ SetYukawaScheme(YukawaScheme); }
      catch(std::runtime_error &e) { invalid_point().raise(e.what()); }
    }
    
    // 38, set looplevel of RGEs, TwoLoopRGE
    *TwoLoopRGE = inputs.options->getValueOrDef<bool>(true, "TwoLoopRGE");
    
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
    // Never rotate the masses, it's agains SLHA convention and Gambit cannot handle complex couplings
    *RotateNegativeFermionMasses = false;
    
    // 51, Switch to SCKM
    // This the default behaviour with GAMBIT
    *SwitchToSCKM = true;
    
    // 52, Ignore negative masses
    *IgnoreNegativeMasses = inputs.options->getValueOrDef<bool>(false, "IgnoreNegativeMasses");
    
    // 53, Ignore negative masses at MZ
    *IgnoreNegativeMassesMZ = inputs.options->getValueOrDef<bool>(false, "IgnoreNegativeMassesMZ");
    
    // 54, Write Out for non convergence
    *WriteOutputForNonConvergence = inputs.options->getValueOrDef<bool>(false, "WriteOutputForNonConvergence");
    
    // 55, calculate one loop masses
    *CalculateOneLoopMasses = inputs.options->getValueOrDef<bool>(true, "CalculateOneLoopMasses");
    
    // 57, calculate low energy observables
    *CalculateLowEnergy = false;
    
    // 58, include delta and/or BSM delta VB
    *IncludeDeltaVB = inputs.options->getValueOrDef<bool>(true, "IncludeDeltaVB");
    if(*IncludeDeltaVB)
      *IncludeBSMdeltaVB = inputs.options->getValueOrDef<bool>(true, "IncludeBSMdeltaVB");
    
    // 60, kinetic mixing
    *KineticMixing = inputs.options->getValueOrDef<bool>(true, "KineticMixing");
    
    // 62,
    *RunningSUSYparametersLowEnergy = inputs.options->getValueOrDef<bool>(true, "RunningSUSYparametersLowEnergy");
      
    // 63,
    *RunningSMparametersLowEnergy = inputs.options->getValueOrDef<bool>(true, "RunningSMparametersLowEnergy");
    
    // 64
    *WriteParametersAtQ = inputs.options->getValueOrDef<bool>(false, "WriteParametersAtQ");
    
    // 65
    *SolutionTadpoleNr = inputs.options->getValueOrDef<Finteger>(1, "SolutionTadpoleNr");
    
    // 66
    *DecoupleAtRenScale = inputs.options->getValueOrDef<bool>(false, "DecoupleAtRenScale");
    
    // 67
    *Calculate_mh_within_SM = inputs.options->getValueOrDef<bool>(true, "Calculate_mh_within_SM");
    if(*Calculate_mh_within_SM)
      *Force_mh_within_SM = inputs.options->getValueOrDef<bool>(false, "Force_mh_within_SM");
    
    // 68
    *MatchZWpoleMasses = inputs.options->getValueOrDef<bool>(false, "MatchZWpolemasses");
    
    // 75,  Writes the parameter file for WHIZARD
    // GAMBIT: no output
    *Write_WHIZARD = false;
    
    // 76, Writes input files for HiggsBounds
    // GAMBIT: no output
    *Write_HiggsBounds = false;
    
    // 77, Use conventions for MO
    // GAMBIT: no output
    *OutputForMO = false;
    
    // 78,  Use conventions for MG
    // GAMBIT: no output
    *OutputForMG = false;
    
    // 79, Writes Wilson coefficients in WCXF format
    *Write_WCXF = inputs.options->getValueOrDef<bool>(false, "Write_WCXF");
    
    // 80, exit for sure with non-zero value if problem occurs, Non_Zero_Exit
    // GAMBIT: never brute exit, let GAMBIT do a controlled exit
    *Non_Zero_Exit = false;
    
    // 86, width to be counted as invisible in HiggsBounds input
    *WidthToBeInvisible = inputs.options->getValueOrDef<Freal8>(0.0, "WidthToBeInvisible");
      
    // 88, maximal mass allowedin loops
    *MaxMassLoop = pow(inputs.options->getValueOrDef<Freal8>(1.0E16, "MaxMassLoop"), 2);
    
    // 80, maximal mass counted as numerical zero
    *MaxMassNumericalZero = inputs.options->getValueOrDef<Freal8>(1.0E-8, "MaxMassNumericalZero");
    
    // 95, force mass matrices at 1-loop to be real
    *ForceRealMatrices = inputs.options->getValueOrDef<bool>(false, "ForceRealMatrices");
    
    // 150, use 1l2lshifts
    *include1l2lshift=inputs.options->getValueOrDef<bool>(false,"include1l2lshift");
    
    // 151
    *NewGBC=inputs.options->getValueOrDef<bool>(true,"NewGBC");
    
    // 440
    *TreeLevelUnitarityLimits=inputs.options->getValueOrDef<bool>(true,"TreeLevelUnitarityLimits");
    
    // 441
    *TrilinearUnitarity=inputs.options->getValueOrDef<bool>(true,"TrilinearUnitarity");
    
    // 442
    *unitarity_s_min = inputs.options->getValueOrDef<Freal8>(2000,"unitarity_s_min");
    
    // 443
    *unitarity_s_max = inputs.options->getValueOrDef<Freal8>(3000,"unitarity_s_max");
    
    // 444
    *unitarity_steps = inputs.options->getValueOrDef<Finteger>(5,"unitarity_steps");
    
    // 445
    *RunRGEs_unitarity=inputs.options->getValueOrDef<bool>(false,"RunRGEs_unitarity");
    
    // 446
    *TUcutLevel = inputs.options->getValueOrDef<Finteger>(2,"TUcutLevel");
    
    // 510, Write tree level tadpole solutions
    // Doesn't seem to have any effect, but add option anyway
    *WriteTreeLevelTadpoleSolutions = inputs.options->getValueOrDef<bool>(false, "WriteTreeLevelTadpoleSolutions");
    
    // 515, Write GUT values
    // In SPheno the default is true, but in GAMBIT we don't often need these, so false
    *WriteGUTvalues = inputs.options->getValueOrDef<bool>(false, "WriteGUTvalues");
    
    // 520, write effective higgs coupling ratios
    // Already done by the getCouplingsTable convenience function, but check
    *WriteEffHiggsCouplingRatios = false;
    
    // 521, Higher order diboson
    *HigherOrderDiboson = inputs.options->getValueOrDef<bool>(true, "HigherOrderDiboson");
    
    // 522
    *PoleMassesInLoops = inputs.options->getValueOrDef<bool>(true, "PoleMassesInLoops");
    
    // 525, write higgs diphoton loop contributions
    // As with 520, these should be in getCouplingsTable
    *WriteHiggsDiphotonLoopContributions = false;
    
    // 530, write tree level tadpole parameters
    *WriteTreeLevelTadpoleParameters = inputs.options->getValueOrDef<bool>(false, "WriteTreeLevelTadpoleParameters");
    
    // 550, CalcFT
    // Does nothing so we don't include it
    
    // 551, one loop FT
    // Does nothing so we don't include it
    
    // 990, make Q test
    // Does nothing so we don't include it
    
    // 000, print debug information
    // GAMBIT: no output
    *PrintDebugInformation = false;
    
    // Silence screen output, added by GAMBIT to SPheno
    *SilenceOutput = inputs.options->getValueOrDef<bool>(true, "SilenceOutput");
    
    /**********************/
    /* Block DECAYOPTIONS */
    /**********************/
    
    // All in ReadingData_decays
    
    
    /****************/
    // Block MINPAR //
    /****************/
    if(inputs.param.find("lam1") != inputs.param.end())
      Lambda1Input->re = *inputs.param.at("lam1");
    if(inputs.param.find("lam2") != inputs.param.end())
      Lambda2Input->re = *inputs.param.at("lam2");
    if(inputs.param.find("lam3") != inputs.param.end())
      Lambda3Input->re = *inputs.param.at("lam3");
    if(inputs.param.find("lam4") != inputs.param.end())
      Lambda4Input->re = *inputs.param.at("lam4");
    if(inputs.param.find("lam5") != inputs.param.end())
      Lambda5Input->re = *inputs.param.at("lam5");
    if(inputs.param.find("m122") != inputs.param.end())
      M122input->re = *inputs.param.at("m122");
    if(inputs.param.find("TanBeta") != inputs.param.end())
      *TanBeta = *inputs.param.at("TanBeta");
    
    /****************/
    /* Block EXTPAR */
    /****************/
    
    /*****************/
    /* Blocks:       */
    /* - HMIXIN        */ 
    /*****************/
    if(inputs.param.find("lam5") != inputs.param.end())
    {
      lam5IN->re = *inputs.param.at("lam5");
      *InputValueforlam5 = true;
    }
    if(inputs.param.find("lam1") != inputs.param.end())
    {
      lam1IN->re = *inputs.param.at("lam1");
      *InputValueforlam1 = true;
    }
    if(inputs.param.find("lam4") != inputs.param.end())
    {
      lam4IN->re = *inputs.param.at("lam4");
      *InputValueforlam4 = true;
    }
    if(inputs.param.find("lam3") != inputs.param.end())
    {
      lam3IN->re = *inputs.param.at("lam3");
      *InputValueforlam3 = true;
    }
    if(inputs.param.find("lam2") != inputs.param.end())
    {
      lam2IN->re = *inputs.param.at("lam2");
      *InputValueforlam2 = true;
    }
    if(inputs.param.find("m122") != inputs.param.end())
    {
      m122IN->re = *inputs.param.at("m122");
      *InputValueform122 = true;
    }
    if(inputs.param.find("m112") != inputs.param.end())
    {
      m112IN->re = *inputs.param.at("m112");
      *InputValueform112 = true;
    }
    if(inputs.param.find("m222") != inputs.param.end())
    {
      m222IN->re = *inputs.param.at("m222");
      *InputValueform222 = true;
    }
    
    /*****************/
    /* Block GAUGEIN */
    /*****************/
    // Irrelevant
    
    // No other blocks are relevant at this stage
    
  }
  // Function to read decay tables and options
  void ReadingData_decays(const Finputs &inputs)
  {
    // Read the file with info about decay channels
    static bool scan_level_decays = true;
    if (scan_level_decays)
    {
      // str decays_file = inputs.options->getValueOrDef<str>("", "decays_file");
      str decays_file = str(GAMBIT_DIR) + "/Backends/data/" + STRINGIFY(BACKENDNAME) + "_" + STRINGIFY(SAFE_VERSION) + "_decays_info.dat";
      
      Fdecays::fill_all_channel_info(decays_file);
      
      scan_level_decays = false;
    }
     
    // Options for decays only
     
    /********************/
    /* Block SPhenoInput */
    /********************/
     
    // 11, whether to calculate branching ratios or not, L_BR
    *L_BR = true;
     
    // 12, minimal value such that a branching ratio is written out, BRMin
    // This really only affects output so we don't care
     
    // 13, 3 boday decays
    *Enable3BDecaysF = false;
    *Enable3BDecaysS = false;
     
    // 14, run SUSY couplings to scale of decaying particle
    *RunningCouplingsDecays = inputs.options->getValueOrDef<bool>(true, "RunningCouplingsDecays");
    
    // 15, MinWidth
    *MinWidth = inputs.options->getValueOrDef<Freal8>(1.0E-30, "MinWidth");
     
    // 16. OneLoopDecays
    *OneLoopDecays = inputs.options->getValueOrDef<bool>(false, "OneLoopDecays");
    
    /**********************/
    /* Block DECAYOPTIONS */
    /**********************/
    
    // CalcLoopDecay_Fe
    *CalcLoopDecay_Fe = inputs.options->getValueOrDef<bool>(true, "CalcLoopDecay_Fe");
    
    // CalcLoopDecay_Fd
    *CalcLoopDecay_Fd = inputs.options->getValueOrDef<bool>(true, "CalcLoopDecay_Fd");
    
    // CalcLoopDecay_hh
    *CalcLoopDecay_hh = inputs.options->getValueOrDef<bool>(true, "CalcLoopDecay_hh");
    
    // CalcLoopDecay_Ah
    *CalcLoopDecay_Ah = inputs.options->getValueOrDef<bool>(true, "CalcLoopDecay_Ah");
    
    // CalcLoopDecay_Hm
    *CalcLoopDecay_Hm = inputs.options->getValueOrDef<bool>(true, "CalcLoopDecay_Hm");
    
    // Calc3BodyDecay_Fu
    *Calc3BodyDecay_Fu = inputs.options->getValueOrDef<bool>(true, "Calc3BodyDecay_Fu");
    
    // Calc3BodyDecay_Fe
    *Calc3BodyDecay_Fe = inputs.options->getValueOrDef<bool>(true, "Calc3BodyDecay_Fe");
    
    // Calc3BodyDecay_Fd
    *Calc3BodyDecay_Fd = inputs.options->getValueOrDef<bool>(true, "Calc3BodyDecay_Fd");
    
    // 1000, Loop induced only
    *CalcLoopDecay_LoopInducedOnly = inputs.options->getValueOrDef<bool>(false, "CalcLoopDecay_LoopInducedOnly");
    
    // 1101, divonly_save
    *divonly_save = inputs.options->getValueOrDef<Finteger>(1,"divonly_save");
    
    // 1102, divergence_save
    *divergence_save = inputs.options->getValueOrDef<Freal8>(0.0,"divergence_save");
    
    // 1110, Simplistic Loop Decays
    *SimplisticLoopDecays = inputs.options->getValueOrDef<bool>(false, "SimplisticLoopDecays");
    
    // 1111, Shift IR divergence
    *ShiftIRdiv = inputs.options->getValueOrDef<bool>(true, "ShiftIRdiv");
    
    // 1103, Debug loop decays
    *DebugLoopDecays = inputs.options->getValueOrDef<bool>(false, "DebugLoopDecays");
    
    // 1104, Only Tree Level Contributions
    *OnlyTreeLevelContributions = inputs.options->getValueOrDef<bool>(false, "OnlyTreeLevelContributions");
    
    // 1114, External Z factors
    *ExternalZfactors = inputs.options->getValueOrDef<bool>(true, "ExternalZfactors");
    if(*ExternalZfactors)
    {
      *UseZeroRotationMatrices = inputs.options->getValueOrDef<bool>(false, "UseZeroRotationMatrices");
      *UseP2Matrices = inputs.options->getValueOrDef<bool>(true, "UseP2Matrices");
    }
    
    // 1115, OS kinematics
    *OSkinematics = inputs.options->getValueOrDef<bool>(true, "OSkinematics");
    
    // 1116, ew/yuk OS in decays
    *ewOSinDecays = inputs.options->getValueOrDef<bool>(true, "ewOSinDecays");
    *yukOSinDecays = inputs.options->getValueOrDef<bool>(false, "yukOSinDecays");
    
    // 1117, CT in loop decays
    *CTinLoopDecays = inputs.options->getValueOrDef<bool>(false, "CTinLoopDecays");
    
    // 1118, Loop induced decays OS
    *LoopInducedDecaysOS = inputs.options->getValueOrDef<bool>(true, "LoopInducedDecaysOS");
    
    // 1201, Mass regulator for photon and gluon
    *Mass_Regulator_PhotonGluon = inputs.options->getValueOrDef<Freal8>(1e-10, "Mass_Regulator_PhotonGluon");
    
    // 1205, Extra scale for loop decays
    *Extra_Scale_LoopDecays = inputs.options->getValueOrDef<bool>(false, "Extra_Scale_LoopDecays");
    if(*Extra_Scale_LoopDecays)
    *Scale_LoopDecays = inputs.options->getValue<Freal8>("Scale_LoopDecays");
    
  }
  
  void InitializeStandardModel(const SMInputs &sminputs)
  {
    
    *kont = 0;
    
    // Contributions to alpha(m_Z), based on F. Jegerlehner, hep-ph/0310234 and Fanchiotti, Kniehl, Sirlin PRD 48 (1993) 307
    *Delta_Alpha_Lepton = 0.04020;
    *Delta_Alpha_Hadron = 0.027651;
    
    // Z-boson
    *mZ = sminputs.mZ;          // mass
    *gamZ = 2.4952;             // width, values henceforth from StandardModel.f90
    (*BrZqq)(1) = 0.156;        // branching ratio in d dbar
    (*BrZqq)(2) = 0.156;        // branching ratio in s sbar
    (*BrZqq)(3) = 0.151;        // branching ratio in b bbar
    (*BrZqq)(4) = 0.116;        // branching ratio in u ubar
    (*BrZqq)(5) = 0.12;         // branching ratio in c cbar
    (*BrZll)(1) = 0.0336;       // branching ratio in e+ e-
    (*BrZll)(2) = 0.0336;       // branching ratio in mu+ mu-
    (*BrZll)(3) = 0.0338;       // branching ratio in tau+ tau-
    *BrZinv = 0.2;              // invisible branching ratio
    
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
    
    float c12 = sqrt(1.0 - s12*s12);
    float c23 = sqrt(1.0 - s23*s23);
    float c13 = sqrt(1.0 - s13*s13);
    
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
    try{ CalculateRunningMasses(*mf_l, *mf_d, *mf_u, *Q_light_quarks, *Alpha_mZ, *AlphaS_mZ, *mZ, *mf_l_mZ, *mf_d_mZ, *mf_u_mZ, *kont); }
    catch(std::runtime_error &e) { invalid_point().raise(e.what()); }
    if(*kont != 0)
    ErrorHandling(*kont);
    
  }
  
  // Function that handles errors
  void ErrorHandling(const int &kont)
  {
    
    str message;
    
    if (kont > 0 and kont <= 31)
    message = (*Math_Error)(kont).str();
    else if (kont > 100 and kont <= 102)
    message = (*SM_Error)(kont-100).str();
    else if (kont > 200 and kont <= 233)
    message = (*SusyM_Error)(kont-200).str();
    else if (kont > 300 and kont <= 315)
    message = (*InOut_Error)(kont-300).str();
    else if (kont > 400 and kont <= 422)
    message = (*Sugra_Error)(kont-400).str();
    else if (kont > 500 and kont <= 525)
    message = (*LoopMass_Error)(kont-500).str();
    else if (kont > 600 and kont <= 609)
    message = (*TwoLoopHiggs_Error)(kont-600).str();
    else if (kont > 1000 and kont <= 1010)
    message = (*MathQP_Error)(kont-1000).str();
    else
    message = "GAMBIT caught an error in SPheno. Check the SPheno output for more info.";
    
    logger() << message << EOM;
    invalid_point().raise(message);
    
    return ;
    
  }


      // Farray<double, 1,3, 1,3> CS_lep_hjhi_ratio;
      // Farray<double, 1,3, 1,3> BR_hjhihi;
      // // Transpose to get around Fortran matrix types
      // for(int i = 0; i < 3; i++) for(int j = 0; j < 3; j++)
      // {
      //   CS_lep_hjhi_ratio(i+1,j+1) = ModelParam.CS_lep_hjhi_ratio[i][j];
      //   BR_hjhihi(i+1,j+1) = ModelParam.BR_hjhihi[i][j];
      // }
      // for(int i = 0; i < 3; i++) for(int j = 0; j < 3; j++)
      // {
      //   ModelParam.CS_lep_hjhi_ratio[j][i] = CS_lep_hjhi_ratio(i+1,j+1);
      //   ModelParam.BR_hjhihi[j][i] = BR_hjhihi(i+1,j+1);
      // }


      // BEreq::HiggsBounds_neutral_input_part(&ModelParam.Mh[0], &ModelParam.hGammaTot[0], &ModelParam.CP[0],
      //         &ModelParam.CS_lep_hjZ_ratio[0], &ModelParam.CS_lep_bbhj_ratio[0],
      //         &ModelParam.CS_lep_tautauhj_ratio[0], &ModelParam.CS_lep_hjhi_ratio[0][0],
      //         &ModelParam.CS_gg_hj_ratio[0], &ModelParam.CS_bb_hj_ratio[0],
      //         &ModelParam.CS_bg_hjb_ratio[0], &ModelParam.CS_ud_hjWp_ratio[0],
      //         &ModelParam.CS_cs_hjWp_ratio[0], &ModelParam.CS_ud_hjWm_ratio[0],
  

  void conv_get_effective_couplings(const Spectrum&, map_str_dbl& result)
  {
    result.clear();
    // const SMInputs& sminputs = spectrum.get_SMInputs();
    
    // Finteger inG; // Higgs index
    // Farray_Fcomplex16_1_3 ratFd; // reduced couplings
    // Farray_Fcomplex16_1_3 ratFe;
    // Farray_Fcomplex16_1_3 ratFu;
    // Farray_Fcomplex16_1_2 ratHm;
    // Fcomplex16 ratVWm;
    // Freal8 mHiggs; // masses
    // Farray_Freal8_1_3 MFd;
    // Farray_Freal8_1_3 MFe;
    // Farray_Freal8_1_3 MFu;
    // Farray_Freal8_1_2 MHm;
    // Freal8 MVWm;
    // Freal8 gNLO; // ??? what
    // Fcomplex16 coup; // result



    // // ???
    // Flogical HigherOrderDiboson = true;

    // // strong coupling
    // Freal8 g3 = 1.169828071135615;
    // // TODO: run strong coupling

    // enum PDG{ d=1, u, s, c, b, t, b_prime, t_prime, 
    //           e=11, ve, mu, vmu, tau, vtau, tau_prime,  vtau_prime, 
    //           g=21, gamma, Z, Wp, h0, 
    //           Hp=37 };

    // enum Basis{ Generic=0, Mass };

    // auto cc = [&](int index, const iipair& p1, const iipair& p2) 
    // { return Fcomplex16(couplings.compute_effective_coupling(index,p1,p2)); };


    // // h0_1

    // inG    = 1;

    // global_cplcFdFdhhL
    // global_cplcFeFehhL
    // global_cplcFuFuhhL

// Do i2=1, 3
// ratFd(i2) = cplcFdFdhhL(i2,i2,i1)*1._dp*vev/MFd(i2) 
// End Do 
// Do i2=1, 3
// ratFe(i2) = cplcFeFehhL(i2,i2,i1)*1._dp*vev/MFe(i2) 
// End Do 
// Do i2=1, 3
// ratFu(i2) = cplcFuFuhhL(i2,i2,i1)*1._dp*vev/MFu(i2) 
// End Do 
// Do i2=1, 2
// ratHm(i2) = 0.5_dp*cplhhHmcHm(i1,i2,i2)*vev/MHm2(i2) 
// End Do 
// ratVWm = -0.5_dp*cplhhcVWmVWm(i1)*vev/MVWm2 


    // double vev = spectrum.get(Par::mass1, "vev");

    // ratFd(1) = (*global_cplcFdFdhhL)(1,1,1) / Fcomplex16(sminputs.mD / vev);
    // ratFd(2) = (*global_cplcFdFdhhL)(2,2,1) / Fcomplex16(sminputs.mS / vev);
    // ratFd(3) = (*global_cplcFdFdhhL)(3,3,1) / Fcomplex16(sminputs.mBmB / vev);

    // ratFu(1) = (*global_cplcFuFuhhL)(1,1,1) / Fcomplex16(sminputs.mU / vev);
    // ratFu(2) = (*global_cplcFuFuhhL)(2,2,1) / Fcomplex16(sminputs.mCmC / vev);
    // ratFu(3) = (*global_cplcFuFuhhL)(3,3,1) / Fcomplex16(sminputs.mT / vev);

    // ratFe(1) = (*global_cplcFeFehhL)(1,1,1) / Fcomplex16(sminputs.mE / vev);
    // ratFe(2) = (*global_cplcFeFehhL)(2,2,1) / Fcomplex16(sminputs.mMu / vev);
    // ratFe(3) = (*global_cplcFeFehhL)(3,3,1) / Fcomplex16(sminputs.mTau / vev);

    // ratHm(1) = (*global_cplhhHmcHm)(1,1,1) / Fcomplex16(spectrum.get(Par::Pole_Mass, "W+") / vev);
    // ratHm(2) = (*global_cplhhHmcHm)(2,2,1) / Fcomplex16(spectrum.get(Par::Pole_Mass, "H+") / vev);
    // ratVWm = (*global_cplhhcVWmVWm)(1) / Fcomplex16(spectrum.get(Par::Pole_Mass, "W+") / vev);

    // ratFd(1) = cc(0,{d,1},{-d,1}); ratFd(2) = cc(0,{s,1},{-s,1}); ratFd(3) = cc(0,{b,1},{-b,1});
    // ratFu(1) = cc(0,{u,1},{-u,1}); ratFu(2) = cc(0,{c,1},{-c,1}); ratFu(3) = cc(0,{t,1},{-t,1});
    // ratFe(1) = cc(0,{e,1},{-e,1}); ratFe(2) = cc(0,{mu,1},{-mu,1}); ratFe(3) = cc(0,{tau,1},{-tau,1});
    // ratHm(1) = cc(0,{Wp,0},{-Wp,0}); ratHm(2) = cc(0,{Hp,0},{-Hp,0});
    // ratVWm = cc(0,{Wp,0},{-Wp,0} );

    // mHiggs = spectrum.get(Par::Pole_Mass, "h0_1");
    // MFd(1) = sminputs.mD;  MFd(2) = sminputs.mS; MFd(3) = sminputs.mBmB;
    // MFu(1) = sminputs.mU;  MFu(2) = sminputs.mCmC; MFu(3) = sminputs.mT;
    // MFe(1) = sminputs.mE;  MFe(2) = sminputs.mMu; MFe(3) = sminputs.mTau;
    // MHm(1) = spectrum.get(Par::Pole_Mass, "W+"); MHm(2) = spectrum.get(Par::Pole_Mass, "H+");
    // MVWm   = spectrum.get(Par::Pole_Mass, "W+");
    // gNLO   = (HigherOrderDiboson == true ? g3 : -1);
    // coup.re   = 0.0;
    // coup.im   = 0.0;

    // CoupHiggsToPhoton(mHiggs, inG, ratFd, ratFe, ratFu, ratHm, ratVWm,
    //                   MFd, MFe, MFu, MHm, MVWm, gNLO, coup);

    result["H1PP_re"] = (*global_cplHiggsPP)(1).re;
    result["H1PP_im"] = (*global_cplHiggsPP)(1).im;
    result["H2PP_re"] = (*global_cplHiggsPP)(2).re;
    result["H2PP_im"] = (*global_cplHiggsPP)(2).im;

    result["H1GG_re"] = (*global_cplHiggsGG)(1).re;
    result["H1GG_im"] = (*global_cplHiggsGG)(1).im;
    result["H2GG_re"] = (*global_cplHiggsGG)(2).re;
    result["H2GG_im"] = (*global_cplHiggsGG)(2).im;

    result["A1PP_re"] = (*global_cplPseudoHiggsPP)(1).re;
    result["A1PP_im"] = (*global_cplPseudoHiggsPP)(1).im;
    result["A2PP_re"] = (*global_cplPseudoHiggsPP)(2).re;
    result["A2PP_im"] = (*global_cplPseudoHiggsPP)(2).im;

    result["A1GG_re"] = (*global_cplPseudoHiggsGG)(1).re;
    result["A1GG_im"] = (*global_cplPseudoHiggsGG)(1).im;
    result["A2GG_re"] = (*global_cplPseudoHiggsGG)(2).re;
    result["A2GG_im"] = (*global_cplPseudoHiggsGG)(2).im;




    // h0_2
    

    // A0
    

    // H+

  }
  
  double conv_Tpar() { return *global_Tpar; }
  double conv_Spar() { return *global_Spar; }
  double conv_Upar() { return *global_Upar; }
  double conv_ae() { return *global_ae; }
  double conv_amu() { return *global_amu; }
  double conv_atau() { return *global_atau; }
  double conv_EDMe() { return *global_EDMe; }
  double conv_EDMmu() { return *global_EDMmu; }
  double conv_EDMtau() { return *global_EDMtau; }
  double conv_dRho() { return *global_dRho; }
  
  double conv_BrBsGamma() { return *global_BrBsGamma; }
  double conv_ratioBsGamma() { return *global_ratioBsGamma; }
  double conv_BrDmunu() { return *global_BrDmunu; }
  double conv_ratioDmunu() { return *global_ratioDmunu; }
  double conv_BrDsmunu() { return *global_BrDsmunu; }
  double conv_ratioDsmunu() { return *global_ratioDsmunu; }
  double conv_BrDstaunu() { return *global_BrDstaunu; }
  double conv_ratioDstaunu() { return *global_ratioDstaunu; }
  double conv_BrBmunu() { return *global_BrBmunu; }
  double conv_ratioBmunu() { return *global_ratioBmunu; }
  double conv_BrBtaunu() { return *global_BrBtaunu; }
  double conv_ratioBtaunu() { return *global_ratioBtaunu; }
  double conv_BrKmunu() { return *global_BrKmunu; }
  double conv_ratioKmunu() { return *global_ratioKmunu; }
  double conv_RK() { return *global_RK; }
  double conv_RKSM() { return *global_RKSM; }
  double conv_muEgamma() { return *global_muEgamma; }
  double conv_tauEgamma() { return *global_tauEgamma; }
  double conv_tauMuGamma() { return *global_tauMuGamma; }
  double conv_CRmuEAl() { return *global_CRmuEAl; }
  double conv_CRmuETi() { return *global_CRmuETi; }
  double conv_CRmuESr() { return *global_CRmuESr; }
  double conv_CRmuESb() { return *global_CRmuESb; }
  double conv_CRmuEAu() { return *global_CRmuEAu; }
  double conv_CRmuEPb() { return *global_CRmuEPb; }
  double conv_BRmuTo3e() { return *global_BRmuTo3e; }
  double conv_BRtauTo3e() { return *global_BRtauTo3e; }
  double conv_BRtauTo3mu() { return *global_BRtauTo3mu; }
  double conv_BRtauToemumu() { return *global_BRtauToemumu; }
  double conv_BRtauTomuee() { return *global_BRtauTomuee; }
  double conv_BRtauToemumu2() { return *global_BRtauToemumu2; }
  double conv_BRtauTomuee2() { return *global_BRtauTomuee2; }
  double conv_BrZtoMuE() { return *global_BrZtoMuE; }
  double conv_BrZtoTauE() { return *global_BrZtoTauE; }
  double conv_BrZtoTauMu() { return *global_BrZtoTauMu; }
  double conv_BrhtoMuE() { return *global_BrhtoMuE; }
  double conv_BrhtoTauE() { return *global_BrhtoTauE; }
  double conv_BrhtoTauMu() { return *global_BrhtoTauMu; }
  double conv_DeltaMBs() { return *global_DeltaMBs; }
  double conv_ratioDeltaMBs() { return *global_ratioDeltaMBs; }
  double conv_DeltaMBq() { return *global_DeltaMBq; }
  double conv_ratioDeltaMBq() { return *global_ratioDeltaMBq; }
  double conv_BrTautoEPi() { return *global_BrTautoEPi; }
  double conv_BrTautoEEta() { return *global_BrTautoEEta; }
  double conv_BrTautoEEtap() { return *global_BrTautoEEtap; }
  double conv_BrTautoMuPi() { return *global_BrTautoMuPi; }
  double conv_BrTautoMuEta() { return *global_BrTautoMuEta; }
  double conv_BrTautoMuEtap() { return *global_BrTautoMuEtap; }
  double conv_BrB0dEE() { return *global_BrB0dEE; }
  double conv_ratioB0dEE() { return *global_ratioB0dEE; }
  double conv_BrB0sEE() { return *global_BrB0sEE; }
  double conv_ratioB0sEE() { return *global_ratioB0sEE; }
  double conv_BrB0dMuMu() { return *global_BrB0dMuMu; }
  double conv_ratioB0dMuMu() { return *global_ratioB0dMuMu; }
  double conv_BrB0sMuMu() { return *global_BrB0sMuMu; }
  double conv_ratioB0sMuMu() { return *global_ratioB0sMuMu; }
  double conv_BrB0dTauTau() { return *global_BrB0dTauTau; }
  double conv_ratioB0dTauTau() { return *global_ratioB0dTauTau; }
  double conv_BrB0sTauTau() { return *global_BrB0sTauTau; }
  double conv_ratioB0sTauTau() { return *global_ratioB0sTauTau; }
  double conv_BrBtoSEE() { return *global_BrBtoSEE; }
  double conv_ratioBtoSEE() { return *global_ratioBtoSEE; }
  double conv_BrBtoSMuMu() { return *global_BrBtoSMuMu; }
  double conv_ratioBtoSMuMu() { return *global_ratioBtoSMuMu; }
  double conv_BrBtoKee() { return *global_BrBtoKee; }
  double conv_ratioBtoKee() { return *global_ratioBtoKee; }
  double conv_BrBtoKmumu() { return *global_BrBtoKmumu; }
  double conv_ratioBtoKmumu() { return *global_ratioBtoKmumu; }
  double conv_BrBtoSnunu() { return *global_BrBtoSnunu; }
  double conv_ratioBtoSnunu() { return *global_ratioBtoSnunu; }
  double conv_BrBtoDnunu() { return *global_BrBtoDnunu; }
  double conv_ratioBtoDnunu() { return *global_ratioBtoDnunu; }
  double conv_BrKptoPipnunu() { return *global_BrKptoPipnunu; }
  double conv_ratioKptoPipnunu() { return *global_ratioKptoPipnunu; }
  double conv_BrKltoPinunu() { return *global_BrKltoPinunu; }
  double conv_ratioKltoPinunu() { return *global_ratioKltoPinunu; }
  double conv_BrK0eMu() { return *global_BrK0eMu; }
  double conv_ratioK0eMu() { return *global_ratioK0eMu; }
  double conv_DelMK() { return *global_DelMK; }
  double conv_ratioDelMK() { return *global_ratioDelMK; }
  double conv_epsK() { return *global_epsK; }
  double conv_ratioepsK() { return *global_ratioepsK; }
  //Helper functions
  void Fdecays::fill_all_channel_info(str decays_file)
  {
    std::ifstream file(decays_file);
    if(file.is_open())
    {
      str line;
      int parent_pdg;
      while(getline(file, line))
      {
        std::istringstream sline(line);
        str first;
        sline >> first;
        // Ignore the line if it is a comment
        if(first[0] != '#' and first != "")
        {
          // If the line starts with DECAY read up the pdg of the decaying particle
          if(first == "DECAY")
          {
            sline >> parent_pdg;
          }
          else
          {
            // Read up the decay index, number of daughters, pdgs for the daughters and the correction factor
            int index, nda, pdg;
            double corrf;
            std::vector<int> daughter_pdgs;
            index = stoi(first);
            sline >> nda;
            for(int i=0; i<nda; i++)
            {
              sline >> pdg;
              daughter_pdgs.push_back(pdg);  //< filling a vector of (PDG code, context int) pairs
            }
            sline >> corrf;
            
            // Now fill the map all_channel_info in the Fdecays namespace
            if(BACKEND_DEBUG)
            std::cout << "DEBUG: Filled channel: parent_pdg=" << parent_pdg << ", index=" << index << ", corrf=" << corrf << std::endl;
            all_channel_info[parent_pdg].push_back(channel_info_triplet (daughter_pdgs, index, corrf));
          }
        }
      }
      
      file.close();
    }
    else
    {
      str message = "Unable to open decays info file " + decays_file;
      logger() << message << EOM;
      backend_error().raise(LOCAL_INFO, message);
      // invalid_point().raise(message);
    }
  }
  
  std::vector<std::pair<int,int> > Fdecays::get_pdg_context_pairs(std::vector<int> pdgs)
  {
    std::vector<std::pair<int,int> > result;
    for(int pdg : pdgs)
    {
      // SM fermions in flavour basis, everything else in mass basis
      if(abs(pdg) < 17)
      result.push_back(std::pair<int,int> (pdg,1));
      else
      result.push_back(std::pair<int,int> (pdg,0));
    }
    return result;
  }
  
}
END_BE_NAMESPACE

BE_INI_FUNCTION
{
  
  // Scan-level initialisation
  static bool scan_level = true;
  if (scan_level)
  {
    // Dump all internal output to stdout
    *ErrCan = 6;
    
    // Set the function pointer in SPheno to our ErrorHandler callback function
    *ErrorHandler_cptr = & CAT_4(BACKENDNAME,_,SAFE_VERSION,_ErrorHandler);
    
    try{ Set_All_Parameters_0(); }
    catch(std::runtime_error &e) { invalid_point().raise(e.what()); }
    
    /****************/
    /* Block MODSEL */
    /****************/
    if((*ModelInUse)("gumTHDMII"))
    {
        *HighScaleModel = "LOW";
        // BC where all parameters are taken at the low scale
        *BoundaryCondition = 3;
    }
    else
    {
        str message = "Model not recognised";
        logger() << message << EOM;
        invalid_point().raise(message);
    }
     
    // GAMBIT default behaviour
    *GenerationMixing = true;
    
  }
  scan_level = false;
  
  // Reset RGE scale
  *Qin = -1;
  try{ SetRGEScale(*Qin); }
  catch(std::runtime_error &e) { invalid_point().raise(e.what()); }
  *Qin = 1.0E6;  // Default value if there's no input
  Freal8 scale_sq = pow(*Qin, 2);
  try{ SetRenormalizationScale(scale_sq); }
  catch(std::runtime_error &e) { invalid_point().raise(e.what()); }
  if(Param.find("Qin") != Param.end())
  { 
    *Qin = *Param.at("Qin");
    scale_sq = pow(*Qin,2);
    try{ SetRGEScale(scale_sq); } 
    catch(std::runtime_error &e) { invalid_point().raise(e.what()); }
  }
  
  // Reset the global flag that indicates whether or not BRs have been computed yet or not for this parameter point.
  Fdecays::BRs_already_calculated = false;
  
}
END_BE_INI_FUNCTION
