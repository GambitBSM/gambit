//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  THDM tree-level basis transformation functions
///
///  *********************************************
///
///  Authors:
///
///  \author A.S. Woodcock
///          (alex.woodcock@outlook.com)
///  \date   Feb 2022
///
///  \author Filip Rajec
///          (filip.rajec@adelaide.edu.au)
///  \date 2020 Apr
///
///  **********************************************

#ifndef THDMSPEC_BASIS_H
#define THDMSPEC_BASIS_H

#include "gambit/SpecBit/SpecBit_helpers.hpp"
#include "gambit/Utils/util_functions.hpp"

namespace Gambit { class SubSpectrum; }

namespace Gambit
{
   namespace SpecBit
   {
      // additional type definitions
      enum scalar_type
      {
         h0 = 1,
         H0,
         A0,
         G0,
         Hp,
         Hm,
         Gp,
         Gm
      };
      
      // fill type for struct below
      enum ThdmSpecFill
      {
         FILL_GENERIC = 1<<0,
         FILL_HIGGS = 1<<1,
         FILL_PHYSICAL = 1<<2,
         FILL_ANGLES = 1<<3,
         FILL_TYPE = 1<<4,
         FILL_YUKAWAS = 1<<5,
      };

      constexpr double nan = std::numeric_limits<double>::quiet_NaN();

      // simple structure for passing around 2HDM parameters at a fixed scale
      // with simple variable names so that you don't need to unwrap them
      struct ThdmSpec
      {
         // Generic basis params
         double lam1=nan, lam2=nan, lam3=nan, lam4=nan, lam5=nan, lam6=nan, lam7=nan;
         // Higgs basis params
         double Lam1=nan, Lam2=nan, Lam3=nan, Lam4=nan, Lam5=nan, Lam6=nan, Lam7=nan;
         // Physical params
         double mh=nan, mH=nan, mA=nan, mHp=nan, mG=nan, mGp=nan, v=nan, v2=nan, m122=nan, m112=nan, m222=nan;
         // angles
         double beta=nan, alpha=nan, tanb=nan, cosba=nan, sinba=nan;
         // other
         double model_type=nan, g1=nan, g2=nan, g3=nan;
         // Yukawas
         std::vector<double> Ye, Yu, Yd;
         // std::vector<std::vector<complexd>> Ye1, Ye2, Yd1, Yd2, Yu1, Yu2;

         // constructor
         ThdmSpec(const SubSpectrum& he, const int fill_type = 0xFFFF);
      };

      // helper function to ensure that the 2HDM scalar sector is Z2 symmetric
      void check_Z2(const double lambda6, const double lambda7, const str calculation_name);
   }

}

#endif
