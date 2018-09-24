// ====================================================================
// This file is part of FlexibleSUSY.
//
// FlexibleSUSY is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
//
// FlexibleSUSY is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with FlexibleSUSY.  If not, see
// <http://www.gnu.org/licenses/>.
// ====================================================================

// File generated at Thu 10 May 2018 14:56:01

#ifndef CMSSMNoFV_INFO_H
#define CMSSMNoFV_INFO_H

#include "problems.hpp"

#include <array>
#include <iosfwd>
#include <string>

namespace flexiblesusy {

namespace CMSSMNoFV_info {
   enum Particles : int { VG, Glu, Fd, Fs, Fb, Fu, Fc, Ft, Fve, Fvm, Fvt, Fe,
      Fm, Ftau, SveL, SvmL, SvtL, Sd, Su, Se, Sm, Stau, Ss, Sc, Sb, St, hh, Ah,
      Hpm, Chi, Cha, VWm, VP, VZ, NUMBER_OF_PARTICLES };

   enum Masses : int { MVG, MGlu, MFd, MFs, MFb, MFu, MFc, MFt, MFve, MFvm,
      MFvt, MFe, MFm, MFtau, MSveL, MSvmL, MSvtL, MSd_1, MSd_2, MSu_1, MSu_2,
      MSe_1, MSe_2, MSm_1, MSm_2, MStau_1, MStau_2, MSs_1, MSs_2, MSc_1, MSc_2,
      MSb_1, MSb_2, MSt_1, MSt_2, Mhh_1, Mhh_2, MAh_1, MAh_2, MHpm_1, MHpm_2,
      MChi_1, MChi_2, MChi_3, MChi_4, MCha_1, MCha_2, MVWm, MVP, MVZ,
      NUMBER_OF_MASSES };

   enum Parameters : int { Yd0_0, Yd0_1, Yd0_2, Yd1_0, Yd1_1, Yd1_2, Yd2_0,
      Yd2_1, Yd2_2, Ye0_0, Ye0_1, Ye0_2, Ye1_0, Ye1_1, Ye1_2, Ye2_0, Ye2_1, Ye2_2,
      Yu0_0, Yu0_1, Yu0_2, Yu1_0, Yu1_1, Yu1_2, Yu2_0, Yu2_1, Yu2_2, Mu, g1, g2,
      g3, vd, vu, TYd0_0, TYd0_1, TYd0_2, TYd1_0, TYd1_1, TYd1_2, TYd2_0, TYd2_1,
      TYd2_2, TYe0_0, TYe0_1, TYe0_2, TYe1_0, TYe1_1, TYe1_2, TYe2_0, TYe2_1,
      TYe2_2, TYu0_0, TYu0_1, TYu0_2, TYu1_0, TYu1_1, TYu1_2, TYu2_0, TYu2_1,
      TYu2_2, BMu, mq20_0, mq20_1, mq20_2, mq21_0, mq21_1, mq21_2, mq22_0, mq22_1,
      mq22_2, ml20_0, ml20_1, ml20_2, ml21_0, ml21_1, ml21_2, ml22_0, ml22_1,
      ml22_2, mHd2, mHu2, md20_0, md20_1, md20_2, md21_0, md21_1, md21_2, md22_0,
      md22_1, md22_2, mu20_0, mu20_1, mu20_2, mu21_0, mu21_1, mu21_2, mu22_0,
      mu22_1, mu22_2, me20_0, me20_1, me20_2, me21_0, me21_1, me21_2, me22_0,
      me22_1, me22_2, MassB, MassWB, MassG, NUMBER_OF_PARAMETERS };

   enum Mixings : int { ZD0_0, ZD0_1, ZD1_0, ZD1_1, ZU0_0, ZU0_1, ZU1_0, ZU1_1,
      ZE0_0, ZE0_1, ZE1_0, ZE1_1, ZM0_0, ZM0_1, ZM1_0, ZM1_1, ZTau0_0, ZTau0_1,
      ZTau1_0, ZTau1_1, ZS0_0, ZS0_1, ZS1_0, ZS1_1, ZC0_0, ZC0_1, ZC1_0, ZC1_1,
      ZB0_0, ZB0_1, ZB1_0, ZB1_1, ZT0_0, ZT0_1, ZT1_0, ZT1_1, ZH0_0, ZH0_1, ZH1_0,
      ZH1_1, ZA0_0, ZA0_1, ZA1_0, ZA1_1, ZP0_0, ZP0_1, ZP1_0, ZP1_1, ReZN0_0,
      ImZN0_0, ReZN0_1, ImZN0_1, ReZN0_2, ImZN0_2, ReZN0_3, ImZN0_3, ReZN1_0,
      ImZN1_0, ReZN1_1, ImZN1_1, ReZN1_2, ImZN1_2, ReZN1_3, ImZN1_3, ReZN2_0,
      ImZN2_0, ReZN2_1, ImZN2_1, ReZN2_2, ImZN2_2, ReZN2_3, ImZN2_3, ReZN3_0,
      ImZN3_0, ReZN3_1, ImZN3_1, ReZN3_2, ImZN3_2, ReZN3_3, ImZN3_3, ReUM0_0,
      ImUM0_0, ReUM0_1, ImUM0_1, ReUM1_0, ImUM1_0, ReUM1_1, ImUM1_1, ReUP0_0,
      ImUP0_0, ReUP0_1, ImUP0_1, ReUP1_0, ImUP1_0, ReUP1_1, ImUP1_1, ZZ0_0, ZZ0_1,
      ZZ1_0, ZZ1_1, NUMBER_OF_MIXINGS };

   enum Input_parameters : int { m0, m12, TanBeta, SignMu, Azero,
      NUMBER_OF_INPUT_PARAMETERS };

   enum Extra_parameters : int { NUMBER_OF_EXTRA_PARAMETERS };

   extern const double normalization_g1;
   extern const double normalization_g2;
   extern const double normalization_g3;

   extern const std::array<int, NUMBER_OF_PARTICLES> particle_multiplicities;
   extern const std::array<std::string, NUMBER_OF_PARTICLES> particle_names;
   extern const std::array<std::string, NUMBER_OF_PARTICLES> particle_latex_names;
   extern const std::array<std::string, NUMBER_OF_PARAMETERS> parameter_names;
   extern const std::array<std::string, NUMBER_OF_MIXINGS> particle_mixing_names;
   extern const std::array<std::string, NUMBER_OF_INPUT_PARAMETERS> input_parameter_names;
   extern const std::array<std::string, NUMBER_OF_EXTRA_PARAMETERS> extra_parameter_names;
   extern const std::string model_name;
   constexpr bool is_low_energy_model = false;
   constexpr bool is_supersymmetric_model = true;
   constexpr bool is_FlexibleEFTHiggs = false;

   void print(std::ostream&);

   class CMSSMNoFV_particle_names : public Names {
   public:
      virtual ~CMSSMNoFV_particle_names() = default;
      virtual const std::string& get(int index) const override {
         return particle_names[index];
      }
      virtual int size() const override {
         return NUMBER_OF_PARTICLES;
      }
   };

   class CMSSMNoFV_parameter_names : public Names {
   public:
      virtual ~CMSSMNoFV_parameter_names() = default;
      virtual const std::string& get(int index) const override {
         return parameter_names[index];
      }
      virtual int size() const override {
         return NUMBER_OF_PARAMETERS;
      }
   };

   const CMSSMNoFV_particle_names  particle_names_getter{};
   const CMSSMNoFV_parameter_names parameter_names_getter{};

} // namespace CMSSMNoFV_info

} // namespace flexiblesusy

#endif
