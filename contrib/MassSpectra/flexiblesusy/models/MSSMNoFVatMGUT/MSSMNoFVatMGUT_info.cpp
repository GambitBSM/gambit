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

// File generated at Thu 10 May 2018 14:51:55

#include "MSSMNoFVatMGUT_info.hpp"

#include <iostream>

namespace flexiblesusy {

namespace MSSMNoFVatMGUT_info {
   const double normalization_g1 = 0.7745966692414834;
   const double normalization_g2 = 1;
   const double normalization_g3 = 1;

   const std::array<int, NUMBER_OF_PARTICLES> particle_multiplicities = {1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
      , 2, 4, 2, 1, 1, 1};

   const std::array<std::string, NUMBER_OF_PARTICLES> particle_names = {"VG",
      "Glu", "Fd", "Fs", "Fb", "Fu", "Fc", "Ft", "Fve", "Fvm", "Fvt", "Fe", "Fm",
      "Ftau", "SveL", "SvmL", "SvtL", "Sd", "Su", "Se", "Sm", "Stau", "Ss", "Sc",
      "Sb", "St", "hh", "Ah", "Hpm", "Chi", "Cha", "VWm", "VP", "VZ"};

   const std::array<std::string, NUMBER_OF_PARTICLES> particle_latex_names = {
      "g", "\\tilde{g}", "d", "s", "b", "u", "c", "t", "\\nu_e", "\\nu_{\\mu}",
      "\\nu_{\\tau}", "e", "m", "\\tau", "\\tilde{\\nu}_e", "\\tilde{\\nu}_{\\mu}"
      , "\\tilde{\\nu}_{\\tau}", "\\tilde{d}", "\\tilde{u}", "\\tilde{e}",
      "\\tilde{\\mu}", "\\tilde{\\tau}", "\\tilde{s}", "\\tilde{c}", "\\tilde{b}",
      "\\tilde{t}", "h", "A^0", "H^-", "\\tilde{\\chi}^0", "\\tilde{\\chi}^-",
      "W^-", "\\gamma", "Z"};

   const std::array<std::string, NUMBER_OF_PARAMETERS> parameter_names = {
      "Yd(0,0)", "Yd(0,1)", "Yd(0,2)", "Yd(1,0)", "Yd(1,1)", "Yd(1,2)", "Yd(2,0)",
      "Yd(2,1)", "Yd(2,2)", "Ye(0,0)", "Ye(0,1)", "Ye(0,2)", "Ye(1,0)", "Ye(1,1)"
      , "Ye(1,2)", "Ye(2,0)", "Ye(2,1)", "Ye(2,2)", "Yu(0,0)", "Yu(0,1)",
      "Yu(0,2)", "Yu(1,0)", "Yu(1,1)", "Yu(1,2)", "Yu(2,0)", "Yu(2,1)", "Yu(2,2)",
      "Mu", "g1", "g2", "g3", "vd", "vu", "TYd(0,0)", "TYd(0,1)", "TYd(0,2)",
      "TYd(1,0)", "TYd(1,1)", "TYd(1,2)", "TYd(2,0)", "TYd(2,1)", "TYd(2,2)",
      "TYe(0,0)", "TYe(0,1)", "TYe(0,2)", "TYe(1,0)", "TYe(1,1)", "TYe(1,2)",
      "TYe(2,0)", "TYe(2,1)", "TYe(2,2)", "TYu(0,0)", "TYu(0,1)", "TYu(0,2)",
      "TYu(1,0)", "TYu(1,1)", "TYu(1,2)", "TYu(2,0)", "TYu(2,1)", "TYu(2,2)",
      "BMu", "mq2(0,0)", "mq2(0,1)", "mq2(0,2)", "mq2(1,0)", "mq2(1,1)",
      "mq2(1,2)", "mq2(2,0)", "mq2(2,1)", "mq2(2,2)", "ml2(0,0)", "ml2(0,1)",
      "ml2(0,2)", "ml2(1,0)", "ml2(1,1)", "ml2(1,2)", "ml2(2,0)", "ml2(2,1)",
      "ml2(2,2)", "mHd2", "mHu2", "md2(0,0)", "md2(0,1)", "md2(0,2)", "md2(1,0)",
      "md2(1,1)", "md2(1,2)", "md2(2,0)", "md2(2,1)", "md2(2,2)", "mu2(0,0)",
      "mu2(0,1)", "mu2(0,2)", "mu2(1,0)", "mu2(1,1)", "mu2(1,2)", "mu2(2,0)",
      "mu2(2,1)", "mu2(2,2)", "me2(0,0)", "me2(0,1)", "me2(0,2)", "me2(1,0)",
      "me2(1,1)", "me2(1,2)", "me2(2,0)", "me2(2,1)", "me2(2,2)", "MassB",
      "MassWB", "MassG"};

   const std::array<std::string, NUMBER_OF_MIXINGS> particle_mixing_names = {
      "ZD(0,0)", "ZD(0,1)", "ZD(1,0)", "ZD(1,1)", "ZU(0,0)", "ZU(0,1)", "ZU(1,0)"
      , "ZU(1,1)", "ZE(0,0)", "ZE(0,1)", "ZE(1,0)", "ZE(1,1)", "ZM(0,0)",
      "ZM(0,1)", "ZM(1,0)", "ZM(1,1)", "ZTau(0,0)", "ZTau(0,1)", "ZTau(1,0)",
      "ZTau(1,1)", "ZS(0,0)", "ZS(0,1)", "ZS(1,0)", "ZS(1,1)", "ZC(0,0)",
      "ZC(0,1)", "ZC(1,0)", "ZC(1,1)", "ZB(0,0)", "ZB(0,1)", "ZB(1,0)", "ZB(1,1)",
      "ZT(0,0)", "ZT(0,1)", "ZT(1,0)", "ZT(1,1)", "ZH(0,0)", "ZH(0,1)", "ZH(1,0)"
      , "ZH(1,1)", "ZA(0,0)", "ZA(0,1)", "ZA(1,0)", "ZA(1,1)", "ZP(0,0)",
      "ZP(0,1)", "ZP(1,0)", "ZP(1,1)", "Re(ZN(0,0))", "Im(ZN(0,0))", "Re(ZN(0,1))"
      , "Im(ZN(0,1))", "Re(ZN(0,2))", "Im(ZN(0,2))", "Re(ZN(0,3))", "Im(ZN(0,3))",
      "Re(ZN(1,0))", "Im(ZN(1,0))", "Re(ZN(1,1))", "Im(ZN(1,1))", "Re(ZN(1,2))",
      "Im(ZN(1,2))", "Re(ZN(1,3))", "Im(ZN(1,3))", "Re(ZN(2,0))", "Im(ZN(2,0))",
      "Re(ZN(2,1))", "Im(ZN(2,1))", "Re(ZN(2,2))", "Im(ZN(2,2))", "Re(ZN(2,3))",
      "Im(ZN(2,3))", "Re(ZN(3,0))", "Im(ZN(3,0))", "Re(ZN(3,1))", "Im(ZN(3,1))",
      "Re(ZN(3,2))", "Im(ZN(3,2))", "Re(ZN(3,3))", "Im(ZN(3,3))", "Re(UM(0,0))",
      "Im(UM(0,0))", "Re(UM(0,1))", "Im(UM(0,1))", "Re(UM(1,0))", "Im(UM(1,0))",
      "Re(UM(1,1))", "Im(UM(1,1))", "Re(UP(0,0))", "Im(UP(0,0))", "Re(UP(0,1))",
      "Im(UP(0,1))", "Re(UP(1,0))", "Im(UP(1,0))", "Re(UP(1,1))", "Im(UP(1,1))",
      "ZZ(0,0)", "ZZ(0,1)", "ZZ(1,0)", "ZZ(1,1)"};

   const std::array<std::string, NUMBER_OF_INPUT_PARAMETERS>
      input_parameter_names = {"TanBeta", "Sign(Mu)", "M1", "M2", "M3", "AtIN",
      "AbIN", "AtauIN", "AcIN", "AsIN", "AmuonIN", "AuIN", "AdIN", "AeIN",
      "mHd2IN", "mHu2IN", "ml11IN", "ml22IN", "ml33IN", "me11IN", "me22IN",
      "me33IN", "mq11IN", "mq22IN", "mq33IN", "mu11IN", "mu22IN", "mu33IN",
      "md11IN", "md22IN", "md33IN"};

   const std::array<std::string, NUMBER_OF_EXTRA_PARAMETERS>
      extra_parameter_names = {};

   const std::string model_name = "MSSMNoFVatMGUT";

void print(std::ostream& ostr)
{
   ostr
      << "Model information\n"
      << "=================\n"
      << "Model name:                  " << model_name << '\n'
      << "Is a low-energy model:       "
      << (is_low_energy_model ? "yes" : "no") << '\n'
      << "Is a supersymmetric model:   "
      << (is_supersymmetric_model ? "yes" : "no") << '\n'
      << "Is a FlexibleEFTHiggs model: "
      << (is_FlexibleEFTHiggs ? "yes" : "no") << '\n'
      << "Number of multiplets:        " << NUMBER_OF_PARTICLES << '\n'
      << "Number of parameters:        " << NUMBER_OF_PARAMETERS << '\n'
      ;

   ostr << "\n"
      "Multiplets:                  ";
   for (int i = 0; i < NUMBER_OF_PARTICLES; i++) {
      ostr << particle_names[i]
           << '[' << particle_multiplicities[i] << ']';
      if (i + 1 < NUMBER_OF_PARTICLES)
         ostr << ", ";
   }

   ostr << "\n\n"
      "Parameters:                  ";
   for (int i = 0; i < NUMBER_OF_PARAMETERS; i++) {
      ostr << parameter_names[i];
      if (i + 1 < NUMBER_OF_PARAMETERS)
         ostr << ", ";
   }

   ostr << "\n\n"
      "Input parameters:            ";
   for (int i = 0; i < NUMBER_OF_INPUT_PARAMETERS; i++) {
      ostr << input_parameter_names[i];
      if (i + 1 < NUMBER_OF_INPUT_PARAMETERS)
         ostr << ", ";
   }

   ostr << '\n';
}

} // namespace MSSMNoFVatMGUT_info

} // namespace flexiblesusy

