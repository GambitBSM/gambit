//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  creates the 2HDM SLHA object 
///  (currently this only supports Z2-symmetric models & SLHA2)
///
///  *********************************************
///
///  Authors:
///  <!-- add name and date if you modify -->
///
///  \author Filip Rajec
///          (filip.rajec@adelaide.edu.au)
///  \date 2020 Apr
///
///  \author Tomas Gonzalo
///          (gonzalo@physik.rwth-aachen.de)
///  \date 2021 Mar
///
///  \author Chris Chang
///  \date 2023 Sep
///
///  *********************************************

#include "gambit/Elements/thdm_slhahelp.hpp"
#include "gambit/Elements/ini_functions.hpp"
#include "gambit/Utils/util_functions.hpp"

namespace Gambit
{
  namespace slhahelp
  {
    // slha_version - should be 1 or 2. Specifies whether to output closest-matching SLHA1 format
    // entries, or to maintain SLHA2 as is used internally.
    void add_THDM_spectrum_to_SLHAea(const SubSpectrum& thdmspec, SLHAstruct& slha, int slha_version)
    {
      
      if (slha_version==2)
      {

        // get all THDM variables
        const int model_type = thdmspec.get(Par::dimensionless, "model_type");
        const double m_h = thdmspec.get(Par::Pole_Mass, "h0",1);
        const double m_H = thdmspec.get(Par::Pole_Mass, "h0",2);
        const double m_A = thdmspec.get(Par::Pole_Mass, "A0");
        const double m_Hp = thdmspec.get(Par::Pole_Mass, "H+");
        const double alpha = thdmspec.get(Par::dimensionless, "alpha");
        const double tanb = thdmspec.get(Par::dimensionless, "tanb");
        const double lambda1 = thdmspec.get(Par::dimensionless, "lambda1");
        const double lambda2 = thdmspec.get(Par::dimensionless, "lambda2");
        const double lambda3 = thdmspec.get(Par::dimensionless, "lambda3");
        const double lambda4 = thdmspec.get(Par::dimensionless, "lambda4");
        const double lambda5 = thdmspec.get(Par::dimensionless, "lambda5");
        const double beta = atan(tanb);
        const double sba = sin(beta - alpha);
        const double cba = cos(beta - alpha);
        const double lambda6 = thdmspec.get(Par::dimensionless,"lambda6");
        const double lambda7 = thdmspec.get(Par::dimensionless,"lambda7");
        const double m12_2 = thdmspec.get(Par::mass1,"m12_2");
        const double MW = thdmspec.get(Par::Pole_Mass,"W+");
        const double g = thdmspec.get(Par::dimensionless,"g1");
        const double g_prime = thdmspec.get(Par::dimensionless,"g2");
        const double g_3 = thdmspec.get(Par::dimensionless,"g3");
        const double vev = thdmspec.get(Par::mass1, "vev");
        const double sina = sin(alpha);
        const double cosa = cos(alpha);
        const double cosb = cos(beta);
        const double sinb = sin(beta);

        // begin filling the SLHA
        
        // TODO: Higgs couplings, these depend on which Type of THDM model
        // TODO: This should probably be moved somewhere more reasonable, like in the Models or SpecBit modules
        // TODO: Also double check consistency of couplings with Pythia
        
        // TODO: This if for my Testing, and is not safe for pushing yet
        // TODO: Pull from the correct part of GAMBIT, for now I am just putting in some test values to check whether it overwrites Pythia's values correctly
        bool TypeI = true;
        bool TypeII = false;
        
        double H1_coup2d;
        double H1_coup2u;
        double H1_coup2l;
        double H1_coup2Z;
        double H1_coup2W;
        
        double H2_coup2d;
        double H2_coup2u;
        double H2_coup2l;
        double H2_coup2Z;
        double H2_coup2W;
        double H2_coup2H1Z;
        double H2_coup2HchgW;
        
        double A3_coup2d;
        double A3_coup2u;
        double A3_coup2l;
        double A3_coup2Z;
        double A3_coup2W;
        double A3_coup2H1Z;
        double A3_coup2H2Z;
        double A3_coup2HchgW;
        
        double Hchg_coup2H1W;
        double Hchg_coup2H2W;
        
        double H1_coup2Hchg;
        double H2_coup2Hchg;
        double H2_coup2H1H1;
        double H2_coup2A3A3;
        double H2_coup2A3H1;
        double A3_coup2H1H1;
        double A3_coup2Hchg;
        
        if (TypeI)
        {
          //H1_coup2d = sina/cosb;
          //H1_coup2u = cosa/sinb;
          //H1_coup2l = cosa/sinb;
          H1_coup2d = 1.0;
          H1_coup2u = 1.0;
          H1_coup2l = 1.0;
          H1_coup2Z = 1.0;
          H1_coup2W = 1.0;
        
          //H2_coup2d = sina/sinb;
          //H2_coup2u = sina/sinb;
          //H2_coup2l = sina/sinb;
          H2_coup2d = 1.0;
          H2_coup2u = 1.0;
          H2_coup2l = 1.0;
          H2_coup2Z = 1.0;
          H2_coup2W = 1.0;
          H2_coup2H1Z = 0.0;
          H2_coup2HchgW = 1.0;
        
          //A3_coup2d = -1./tanb;
          //A3_coup2u = 1./tanb;
          A3_coup2d = 1.0;
          A3_coup2u = 1.0;
          A3_coup2l = 1.0;
          A3_coup2Z = 0.0;
          A3_coup2W = 0.0;
          A3_coup2H1Z = 1.0;
          A3_coup2H2Z = 1.0;
          A3_coup2HchgW = 1.0;
        
          Hchg_coup2H1W = 1.0;
          Hchg_coup2H2W = 1.0;
        
          H1_coup2Hchg = 1.0;
          H2_coup2Hchg = 1.0;
          H2_coup2H1H1 = 1.0;
          H2_coup2A3A3 = 1.0;
          H2_coup2A3H1 = 0.0;
          A3_coup2H1H1 = 0.0;
          A3_coup2Hchg = 0.0;
        }
        else if (TypeII)
        {
          H1_coup2d = 1.0;
          H1_coup2u = 1.0;
          H1_coup2l = 1.0;
          H1_coup2Z = 1.0;
          H1_coup2W = 1.0;
        
          H2_coup2d = 1.0;
          H2_coup2u = 1.0;
          H2_coup2l = 1.0;
          H2_coup2Z = 1.0;
          H2_coup2W = 1.0;
          H2_coup2H1Z = 0.0;
          H2_coup2HchgW = 1.0;
        
          A3_coup2d = 1.0;
          A3_coup2u = 1.0;
          A3_coup2l = 1.0;
          A3_coup2Z = 0.0;
          A3_coup2W = 0.0;
          A3_coup2H1Z = 1.0;
          A3_coup2H2Z = 1.0;
          A3_coup2HchgW = 1.0;
        
          Hchg_coup2H1W = 1.0;
          Hchg_coup2H2W = 1.0;
        
          H1_coup2Hchg = 1.0;
          H2_coup2Hchg = 1.0;
          H2_coup2H1H1 = 1.0;
          H2_coup2A3A3 = 1.0;
          H2_coup2A3H1 = 0.0;
          A3_coup2H1H1 = 0.0;
          A3_coup2Hchg = 0.0;
        }
        
        SLHAea_add_block(slha, "THDMCOUPLINGS");
        SLHAea_add(slha, "THDMCOUPLINGS", 1, H1_coup2d, "HiggsH1:coup2d", true);
        SLHAea_add(slha, "THDMCOUPLINGS", 2, H1_coup2u, "HiggsH1:coup2u", true);
        SLHAea_add(slha, "THDMCOUPLINGS", 3, H1_coup2l, "HiggsH1:coup2l", true);
        SLHAea_add(slha, "THDMCOUPLINGS", 4, H1_coup2Z, "HiggsH1:coup2Z", true);
        SLHAea_add(slha, "THDMCOUPLINGS", 5, H1_coup2W, "HiggsH1:coup2W", true);
        
        SLHAea_add(slha, "THDMCOUPLINGS", 6, H2_coup2d, "HiggsH2:coup2d", true);
        SLHAea_add(slha, "THDMCOUPLINGS", 7, H2_coup2u, "HiggsH2:coup2u", true);
        SLHAea_add(slha, "THDMCOUPLINGS", 8, H2_coup2l, "HiggsH2:coup2l", true);
        SLHAea_add(slha, "THDMCOUPLINGS", 9, H2_coup2Z, "HiggsH2:coup2Z", true);
        SLHAea_add(slha, "THDMCOUPLINGS", 10, H2_coup2W, "HiggsH2:coup2W", true);
        SLHAea_add(slha, "THDMCOUPLINGS", 11, H2_coup2H1Z, "HiggsH2:coup2H1Z", true);
        SLHAea_add(slha, "THDMCOUPLINGS", 12, H2_coup2HchgW, "HiggsH2:coup2HchgW", true);
        
        SLHAea_add(slha, "THDMCOUPLINGS", 13, A3_coup2d, "HiggsA3:coup2d", true);
        SLHAea_add(slha, "THDMCOUPLINGS", 14, A3_coup2u, "HiggsA3:coup2u", true);
        SLHAea_add(slha, "THDMCOUPLINGS", 15, A3_coup2l, "HiggsA3:coup2l", true);
        SLHAea_add(slha, "THDMCOUPLINGS", 16, A3_coup2Z, "HiggsA3:coup2Z", true);
        SLHAea_add(slha, "THDMCOUPLINGS", 17, A3_coup2W, "HiggsA3:coup2W", true);
        SLHAea_add(slha, "THDMCOUPLINGS", 18, A3_coup2H1Z, "HiggsA3:coup2H1Z", true);
        SLHAea_add(slha, "THDMCOUPLINGS", 19, A3_coup2H2Z, "HiggsA3:coup2H2Z", true);
        SLHAea_add(slha, "THDMCOUPLINGS", 20, A3_coup2HchgW, "HiggsA3:coup2HchgW", true);
        
        SLHAea_add(slha, "THDMCOUPLINGS", 21, tanb, "HiggsHchg:tanBeta", true);
        SLHAea_add(slha, "THDMCOUPLINGS", 22, Hchg_coup2H1W, "HiggsHchg:coup2H1W", true);
        SLHAea_add(slha, "THDMCOUPLINGS", 23, Hchg_coup2H2W, "HiggsHchg:coup2H2W", true);
        
        SLHAea_add(slha, "THDMCOUPLINGS", 24, H1_coup2Hchg, "HiggsH1:coup2Hchg", true);
        SLHAea_add(slha, "THDMCOUPLINGS", 25, H2_coup2Hchg, "HiggsH2:coup2Hchg", true);
        SLHAea_add(slha, "THDMCOUPLINGS", 26, H2_coup2H1H1, "HiggsH2:coup2H1H1", true);
        SLHAea_add(slha, "THDMCOUPLINGS", 27, H2_coup2A3A3, "HiggsH2:coup2A3A3", true);
        SLHAea_add(slha, "THDMCOUPLINGS", 28, H2_coup2A3H1, "HiggsH2:coup2A3H1", true);
        SLHAea_add(slha, "THDMCOUPLINGS", 29, A3_coup2H1H1, "HiggsA3:coup2H1H1", true);
        SLHAea_add(slha, "THDMCOUPLINGS", 30, A3_coup2Hchg, "HiggsA3:coup2Hchg", true);
        

        // model selection block(10 = THDM)
        SLHAea_add_block(slha, "MODSEL");
        SLHAea_add(slha, "MODSEL", 0, 10, "THDM", true);
        SLHAea_add(slha, "MODSEL", 1, 10, "THDM", true);
        
        // flavor MODSEL block
        // THDM Yukawa type is given by (30 + model_type), we also have no CP-violation in our model
        SLHAea_add_block(slha, "FMODSEL");
        SLHAea_add(slha, "FMODSEL", 1, (30 + model_type), "THDM", true);
        // TODO: Actually it might not be true with imaginary yukawas, but leave for now
        SLHAea_add(slha, "FMODSEL", 5, 0, "No CP-violation", true);

        // scale
        SLHAea_add_block(slha, "MSOFT", thdmspec.GetScale());

        // gauge parameters
        SLHAea_add_block(slha, "GAUGE");
        SLHAea_add(slha, "GAUGE", 1, g, "g", true);
        SLHAea_add(slha, "GAUGE", 2, g_prime, "g'", true);
        SLHAea_add(slha, "GAUGE", 3, g_3, "g_3'", true);

        // geenral basis parameters 
        SLHAea_add_block(slha, "MINPAR");
        SLHAea_add(slha, "MINPAR", 3, tanb, "tanb", true);
        SLHAea_add(slha, "MINPAR", 11, lambda1, "lambda1", true);
        SLHAea_add(slha, "MINPAR", 12, lambda2, "lambda2", true);
        SLHAea_add(slha, "MINPAR", 13, lambda3, "lambda3", true);
        SLHAea_add(slha, "MINPAR", 14, lambda4, "lambda4", true);
        SLHAea_add(slha, "MINPAR", 15, lambda5, "lambda5", true);
        SLHAea_add(slha, "MINPAR", 16, lambda6, "lambda6", true);
        SLHAea_add(slha, "MINPAR", 17, lambda7, "lambda7", true);
        SLHAea_add(slha, "MINPAR", 18, m12_2, "m12^2", true);
        SLHAea_add(slha, "MINPAR", 20, sba, "sin(b-a)", true);
        SLHAea_add(slha, "MINPAR", 21, cba, "cos(b-a)", true);

        // physical mass parameters
        //SLHAea_add_block(slha, "MASS"); // commented this out because it is causing a repeat of the MASS block
        SLHAea_add(slha, "MASS", 24, MW, "MW", true);
        SLHAea_add(slha, "MASS", 25, m_h, "Mh0_1", true);
        SLHAea_add(slha, "MASS", 35, m_H, "Mh0_2", true);
        SLHAea_add(slha, "MASS", 36, m_A, "MA0", true);
        SLHAea_add(slha, "MASS", 37, m_Hp, "MHc", true);

        // Adding in some entries in the HMIX Block
        SLHAea_add_block(slha, "HMIX", thdmspec.GetScale());
        SLHAea_add(slha, "HMIX", 1, sqrt(m12_2), "mu", true); // TODO: Double check that m12_2 is m12 squared
        SLHAea_add(slha, "HMIX", 2, tanb, "tanb", true);
        SLHAea_add(slha, "HMIX", 3, vev, "vev", true);
        SLHAea_add(slha, "HMIX", 4, m_A*m_A, "mA^2", true);

        // angle alpha
        SLHAea_add_block(slha, "ALPHA");
        //SLHAea_add(slha, "ALPHA", 0, alpha, "alpha", true);
        slha["ALPHA"][""] << alpha << "# alpha";// Pythia expects it is without an index, which is very odd, and different to how it expects all other parameters in the slha
        
        SLHAea_add_block(slha, "YU1");
        SLHAea_add_block(slha, "YD1");
        SLHAea_add_block(slha, "YE1");
        SLHAea_add_block(slha, "YU2");
        SLHAea_add_block(slha, "YD2");
        SLHAea_add_block(slha, "YE2");

        SLHAea_add_block(slha, "IMYU1");
        SLHAea_add_block(slha, "IMYD1");
        SLHAea_add_block(slha, "IMYE1");
        SLHAea_add_block(slha, "IMYU2");
        SLHAea_add_block(slha, "IMYD2");
        SLHAea_add_block(slha, "IMYE2");



        for(int i=1;i<=3;i++)
        {
            for(int j=1;j<=3;j++)
            {
            SLHAea_add(slha,"YU1",i,j,thdmspec.get(Par::dimensionless, "Yu1", i, j),"Yu1", true);
            SLHAea_add(slha,"YD1",i,j,thdmspec.get(Par::dimensionless, "Yd1", i, j),"Yd1", true);
            SLHAea_add(slha,"YE1",i,j,thdmspec.get(Par::dimensionless, "Ye1", i, j),"Ye1", true);
            SLHAea_add(slha,"YU2",i,j,thdmspec.get(Par::dimensionless, "Yu2", i, j),"Yu2", true);
            SLHAea_add(slha,"YD2",i,j,thdmspec.get(Par::dimensionless, "Yd2", i, j),"Yd2", true);
            SLHAea_add(slha,"YE2",i,j,thdmspec.get(Par::dimensionless, "Ye2", i, j),"Ye2", true);
           
            SLHAea_add(slha,"IMYU1",i,j,thdmspec.get(Par::dimensionless, "ImYu1", i, j),"ImYu1", true);
            SLHAea_add(slha,"IMYD1",i,j,thdmspec.get(Par::dimensionless, "ImYd1", i, j),"ImYd1", true);
            SLHAea_add(slha,"IMYE1",i,j,thdmspec.get(Par::dimensionless, "ImYe1", i, j),"ImYe1", true);
            SLHAea_add(slha,"IMYU2",i,j,thdmspec.get(Par::dimensionless, "ImYu2", i, j),"ImYu2", true);
            SLHAea_add(slha,"IMYD2",i,j,thdmspec.get(Par::dimensionless, "ImYd2", i, j),"ImYd2", true);
            SLHAea_add(slha,"IMYE2",i,j,thdmspec.get(Par::dimensionless, "ImYe2", i, j),"ImYe2", true);
            }  
        }
      }
      else 
      {
        // at the moment only SLHA2 is called, but in case, throw an error
        std::ostringstream errmsg;
        errmsg << "Only SLHA2 convention is currently compatible with the THDM. Expect problems." << std::endl;
        utils_error().raise(LOCAL_INFO,errmsg.str());

      }
    }
  
  }  // namespace slhahelp

} //namespace gambit
