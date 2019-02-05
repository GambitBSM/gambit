//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Definitions of routines to help users / Bits
///  translate between SLHA2 sfermions
///  and SLHA1 (or similar) sfermions
///
///  *********************************************
///
///  Authors:
///  <!-- add name and date if you modify -->
///
///    Filip Rajec 
///      filip.rajec@adelaide.edu.au
///    Feb 2019
///
///  *********************************************

#include "gambit/Elements/thdm_slhahelp.hpp"
#include "gambit/Elements/ini_functions.hpp"
#include "gambit/Utils/util_functions.hpp"

namespace Gambit
{

   namespace slhahelp
   {

      // TODO: discriminate betweem SLHA version 1 & 2

      /// Add an entire THDM spectrum to an SLHAea object
      // Here we assume that all SM input info comes from the SMINPUT object,
      // and all low-E stuff (quark pole masses and the like) come from the LE subspectrum.
      // In other words all those things should be added to the SLHAea object via
      // different functions to this one. Here we add only THDM information
      // NOTE: check the below statement:
       // Note that the SMINPUT object's dump-to-SLHAea function does not know how to discriminate
       // between SLHA1 and SLHA2, but that doesn't matter, as the SM parameters defined in SLHA2
       // just constitute additional blocks/block entries, not replacements for SLHA1 blocks.  In the
       // MSSM sector, this is not true, and we take care to write version-specific blocks here.
      //
      // slha_version - should be 1 or 2. Specifies whether to output closest-matching SLHA1 format
      // entries, or to maintain SLHA2 as is used internally.
      void add_THDM_spectrum_to_SLHAea(const SubSpectrum& thdmspec, SLHAstruct& slha, int slha_version)
      {
         // std::ostringstream comment;
        const double m_h = thdmspec.get(Par::Pole_Mass, "h0",1);
        const double m_H = thdmspec.get(Par::Pole_Mass, "h0",2);
        const double m_A = thdmspec.get(Par::Pole_Mass, "A0");
        const double m_Hp = thdmspec.get(Par::Pole_Mass, "H+");
        const double alpha = thdmspec.get(Par::dimensionless, "alpha");
        const double tan_beta = thdmspec.get(Par::dimensionless, "tanb");
        const double lambda1 = thdmspec.get(Par::mass1, "lambda_1");
        const double lambda2 = thdmspec.get(Par::mass1, "lambda_2");
        const double lambda3 = thdmspec.get(Par::mass1, "lambda_3");
        const double lambda4 = thdmspec.get(Par::mass1, "lambda_4");
        const double lambda5 = thdmspec.get(Par::mass1, "lambda_5");
        const double beta = atan(tan_beta);
        const double sba = sin(beta - alpha);
        const double lambda6 = thdmspec.get(Par::mass1,"lambda_6");
        const double lambda7 = thdmspec.get(Par::mass1,"lambda_7");
        const double m12_2 = thdmspec.get(Par::mass1,"m12_2");
        const double MW = thdmspec.get(Par::Pole_Mass,"W+");

        SLHAea_add_block(slha, "MODSEL");;
        SLHAea_add(slha, "MODSEL", 0, 10, "2HDM", true);
        SLHAea_add(slha, "MODSEL", 1, 10, "2HDM", true);

        SLHAea_add_block(slha, "FMODSEL");
        SLHAea_add(slha, "FMODSEL", 1, 32, "2HDM", true);
        SLHAea_add(slha, "FMODSEL", 5, 0, "No CP-violation", true);

        SLHAea_add_block(slha, "MSOFT", thdmspec.GetScale());
        
        // SLHAea_add_block(slha, "SMINPUTS");
        // SLHAea_add(slha, "SMINPUTS", 1, alphaInv, "1/alpha_em", true);
        // SLHAea_add(slha, "SMINPUTS", 2, GF, "GF", true);
        // SLHAea_add(slha, "SMINPUTS", 3, alphaS, "alphaS", true);
        // SLHAea_add(slha, "SMINPUTS", 4, MZ, "MZ", true);
        // SLHAea_add(slha, "SMINPUTS", 5, m_d[2], "Mb", true);
        // SLHAea_add(slha, "SMINPUTS", 6, m_u[2], "Mt - pole", true);
        // SLHAea_add(slha, "SMINPUTS", 7, m_l[2], "Mtau - pole", true);

        // SLHAea_add_block(slha, "GAUGE");
        // SLHAea_add(slha, "GAUGE", 1, g, "g", true);
        // SLHAea_add(slha, "GAUGE", 2, g_prime, "g'", true);
        // SLHAea_add(slha, "GAUGE", 3, g_3, "g_3'", true);

        SLHAea_add_block(slha, "MINPAR");
        SLHAea_add(slha, "MINPAR", 3, tan_beta, "tanb", true);
        SLHAea_add(slha, "MINPAR", 11, lambda1, "lambda1", true);
        SLHAea_add(slha, "MINPAR", 12, lambda2, "lambda2", true);
        SLHAea_add(slha, "MINPAR", 13, lambda3, "lambda3", true);
        SLHAea_add(slha, "MINPAR", 14, lambda4, "lambda4", true);
        SLHAea_add(slha, "MINPAR", 15, lambda5, "lambda5", true);
        SLHAea_add(slha, "MINPAR", 16, lambda6, "lambda6", true);
        SLHAea_add(slha, "MINPAR", 17, lambda7, "lambda7", true);
        SLHAea_add(slha, "MINPAR", 18, m12_2, "m12^2", true);
        SLHAea_add(slha, "MINPAR", 20, sba, "sin(b-a)", true);
        SLHAea_add(slha, "MINPAR", 21, sqrt(1.0-pow(sba,2)), "cos(b-a)", true);

        // SLHAea_add_block(slha, "VCKMIN");
        // SLHAea_add(slha, "VCKMIN", 1, lambda, "lambda-CKM", true);
        // SLHAea_add(slha, "VCKMIN", 2, A, "A-CKM", true);
        // SLHAea_add(slha, "VCKMIN", 3, rho, "rhobar-CKM", true);
        // SLHAea_add(slha, "VCKMIN", 4, eta, "etabar-CKM", true);

        SLHAea_add_block(slha, "MASS");
        // SLHAea_add(slha, "MASS", 1, m_d[0], "Md - pole", true);
        // SLHAea_add(slha, "MASS", 2, m_u[0], "Mu - pole", true);
        // SLHAea_add(slha, "MASS", 3, m_d[1], "Ms - pole", true);
        // SLHAea_add(slha, "MASS", 4, m_u[1], "Mc - pole", true);
        // SLHAea_add(slha, "MASS", 5, m_d[2], "Mb - pole", true);
        // SLHAea_add(slha, "MASS", 6, m_u[2], "Mt - pole", true);
        // SLHAea_add(slha, "MASS", 11, m_l[0], "Me - pole", true);
        // SLHAea_add(slha, "MASS", 13, m_l[1], "Mmu - pole", true);
        // SLHAea_add(slha, "MASS", 15, m_l[2], "Mtau - pole", true);
        // SLHAea_add(slha, "MASS", 23, MZ, "MZ", true);
        SLHAea_add(slha, "MASS", 24, MW, "MW", true);
        SLHAea_add(slha, "MASS", 25, m_h, "Mh0_1", true);
        SLHAea_add(slha, "MASS", 35, m_H, "Mh0_2", true);
        SLHAea_add(slha, "MASS", 36, m_A, "MA0", true);
        SLHAea_add(slha, "MASS", 37, m_Hp, "MHc", true);

        SLHAea_add_block(slha, "ALPHA");
        SLHAea_add(slha, "ALPHA", 0, alpha, "alpha", true);

      std::vector<double> matrix_u, matrix_d, matrix_l;

        for (int i=0;i<3;i++) {
          for (int j=0;j<3;j++) {
            matrix_u.push_back(0);
            matrix_d.push_back(0);
            matrix_l.push_back(0);
            // fills with 9 zeros
          }
        }

        // TODO uncomment from spectrum
        matrix_u[0] = 0.0;//thdmspec.get(Par::dimensionless, "Yu", 1, 1);
        matrix_u[4] = 0.1;//thdmspec.get(Par::dimensionless, "Yu", 2, 2);
        matrix_u[8] = 0.9;//thdmspec.get(Par::dimensionless, "Yu", 3, 3);

        matrix_d[0] = 0.0;//thdmspec.get(Par::dimensionless, "Yd", 1, 1);
        matrix_d[4] = 0.01;//thdmspec.get(Par::dimensionless, "Yd", 2, 2);
        matrix_d[8] = 0.2;//thdmspec.get(Par::dimensionless, "Yd", 3, 3);

        matrix_l[0] = 0.0;//thdmspec.get(Par::dimensionless, "Yl", 1, 1);
        matrix_l[4] = 0.01;//thdmspec.get(Par::dimensionless, "Yl", 2, 2);
        matrix_l[8] = 0.1;//thdmspec.get(Par::dimensionless, "Yl", 3, 3);

        SLHAea_add_block(slha, "UCOUPL");
        SLHAea_add_matrix(slha, "UCOUPL", matrix_u, 3, 3, "LU", true);

        SLHAea_add_block(slha, "DCOUPL");
        SLHAea_add_matrix(slha, "DCOUPL", matrix_d, 3, 3, "LU", true);

        SLHAea_add_block(slha, "LCOUPL");
        SLHAea_add_matrix(slha, "LCOUPL", matrix_l, 3, 3, "LU", true);

       }

   }  // namespace slhahelp


} //namespace gambit
