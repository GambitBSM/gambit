//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Creates the 2HDM SLHA
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
      void add_THDM_spectrum_to_SLHAea(const SubSpectrum& thdmspec, SLHAstruct& slha, int slha_version) {
        if (slha_version==2) {

          const double m_h = thdmspec.get(Par::Pole_Mass, "h0",1);
          const double m_H = thdmspec.get(Par::Pole_Mass, "h0",2);
          const double m_A = thdmspec.get(Par::Pole_Mass, "A0");
          const double m_Hp = thdmspec.get(Par::Pole_Mass, "H+");
          const double alpha = thdmspec.get(Par::dimensionless, "alpha");
          const double tanb = thdmspec.get(Par::dimensionless, "tanb");
          const double lambda1 = thdmspec.get(Par::mass1, "lambda_1");
          const double lambda2 = thdmspec.get(Par::mass1, "lambda_2");
          const double lambda3 = thdmspec.get(Par::mass1, "lambda_3");
          const double lambda4 = thdmspec.get(Par::mass1, "lambda_4");
          const double lambda5 = thdmspec.get(Par::mass1, "lambda_5");
          const double beta = atan(tanb);
          const double sba = sin(beta - alpha);
          const double lambda6 = thdmspec.get(Par::mass1,"lambda_6");
          const double lambda7 = thdmspec.get(Par::mass1,"lambda_7");
          const double m12_2 = thdmspec.get(Par::mass1,"m12_2");
          const double MW = thdmspec.get(Par::Pole_Mass,"W+");
          const double g = thdmspec.get(Par::dimensionless,"g1");
          const double g_prime = thdmspec.get(Par::dimensionless,"g2");
          const double g_3 = thdmspec.get(Par::dimensionless,"g3");
          const int yukawa_coupling = thdmspec.get(Par::dimensionless,"yukawaCoupling");

          SLHAea_add_block(slha, "MODSEL");;
          SLHAea_add(slha, "MODSEL", 0, 10, "THDM", true); // 10 = THDM
          SLHAea_add(slha, "MODSEL", 1, 10, "THDM", true); // 10 = THDM

          SLHAea_add_block(slha, "FMODSEL"); // Flavor MODSEL
          SLHAea_add(slha, "FMODSEL", 1, (30 + yukawa_coupling), "THDM", true); // THDM Model Type 30+yukawas_type
          SLHAea_add(slha, "FMODSEL", 5, 0, "No CP-violation", true); // 0 = No CP-violation

          SLHAea_add_block(slha, "MSOFT", thdmspec.GetScale());

          SLHAea_add_block(slha, "GAUGE");
          SLHAea_add(slha, "GAUGE", 1, g, "g", true);
          SLHAea_add(slha, "GAUGE", 2, g_prime, "g'", true);
          SLHAea_add(slha, "GAUGE", 3, g_3, "g_3'", true);

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
          SLHAea_add(slha, "MINPAR", 21, sqrt(1.0-pow(sba,2)), "cos(b-a)", true);

          SLHAea_add_block(slha, "MASS");
          SLHAea_add(slha, "MASS", 24, MW, "MW", true);
          SLHAea_add(slha, "MASS", 25, m_h, "Mh0_1", true);
          SLHAea_add(slha, "MASS", 35, m_H, "Mh0_2", true);
          SLHAea_add(slha, "MASS", 36, m_A, "MA0", true);
          SLHAea_add(slha, "MASS", 37, m_Hp, "MHc", true);

          SLHAea_add_block(slha, "ALPHA");
          SLHAea_add(slha, "ALPHA", 0, alpha, "alpha", true);

          // std::vector<double> matrix_u, matrix_d, matrix_l;
          std::vector<double> u_coupl_matrix, d_coupl_matrix, l_coupl_matrix;

          for (int i=0;i<9;i++) {
              // matrix_u.push_back(0); matrix_d.push_back(0); matrix_l.push_back(0);
              u_coupl_matrix.push_back(0); d_coupl_matrix.push_back(0); l_coupl_matrix.push_back(0);
          }

          // matrix_u[0] = thdmspec.get(Par::dimensionless, "Yu", 1, 1);
          // matrix_u[4] = thdmspec.get(Par::dimensionless, "Yu", 2, 2);
          // matrix_u[8] = thdmspec.get(Par::dimensionless, "Yu", 3, 3);

          // matrix_d[0] = thdmspec.get(Par::dimensionless, "Yd", 1, 1);
          // matrix_d[4] = thdmspec.get(Par::dimensionless, "Yd", 2, 2);
          // matrix_d[8] = thdmspec.get(Par::dimensionless, "Yd", 3, 3);

          // matrix_l[0] = thdmspec.get(Par::dimensionless, "Ye", 1, 1);
          // matrix_l[4] = thdmspec.get(Par::dimensionless, "Ye", 2, 2);
          // matrix_l[8] = thdmspec.get(Par::dimensionless, "Ye", 3, 3);

          double u_coupl, d_coupl, l_coupl;

          switch(yukawa_coupling) {
            case 1: u_coupl = 1.0/tanb; d_coupl = 1.0/tanb; l_coupl = 1.0/tanb; break;
            case 2: u_coupl = 1.0/tanb; d_coupl = -tanb;    l_coupl = -tanb; break;
            case 3: u_coupl = 1.0/tanb; d_coupl = 1.0/tanb; l_coupl = -tanb; break;
            case 4: u_coupl = 1.0/tanb; d_coupl = -tanb;    l_coupl = 1.0/tanb; break;
          }
          u_coupl_matrix[0] = u_coupl;
          u_coupl_matrix[4] = u_coupl;
          u_coupl_matrix[8] = u_coupl;

          d_coupl_matrix[0] = d_coupl;
          d_coupl_matrix[4] = d_coupl;
          d_coupl_matrix[8] = d_coupl;

          l_coupl_matrix[0] = l_coupl;
          l_coupl_matrix[4] = l_coupl;
          l_coupl_matrix[8] = l_coupl;

          SLHAea_add_block(slha, "UCOUPL");
          SLHAea_add_matrix(slha, "UCOUPL", u_coupl_matrix, 3, 3, "LU", true);

          SLHAea_add_block(slha, "DCOUPL");
          SLHAea_add_matrix(slha, "DCOUPL", d_coupl_matrix, 3, 3, "LD", true);

          SLHAea_add_block(slha, "LCOUPL");
          SLHAea_add_matrix(slha, "LCOUPL", l_coupl_matrix, 3, 3, "LL", true);
        
        }
        else {
          // at the moment only SLHA2 is called, but in case, throw an error
          std::cerr << "Only SLHA2 convention is currently compatible with the THDM. Expect problems." << std::endl;
        }

       }
   }  // namespace slhahelp
} //namespace gambit
