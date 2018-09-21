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

// File generated at Thu 10 May 2018 15:00:02

#include "MSSMNoFV_slha_io.hpp"
#include "MSSMNoFV_input_parameters.hpp"
#include "logger.hpp"
#include "wrappers.hpp"
#include "numerics2.hpp"
#include "config.h"

#include <array>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

#define Pole(p) physical.p
#define PHYSICAL(p) model.get_physical().p
#define PHYSICAL_SLHA(p) model.get_physical_slha().p
#define LOCALPHYSICAL(p) physical.p
#define MODELPARAMETER(p) model.get_##p()
#define INPUTPARAMETER(p) input.p
#define EXTRAPARAMETER(p) model.get_##p()
#define DEFINE_PHYSICAL_PARAMETER(p) decltype(LOCALPHYSICAL(p)) p;
#define LowEnergyConstant(p) Electroweak_constants::p

using namespace softsusy;

namespace flexiblesusy {

MSSMNoFV_slha_io::MSSMNoFV_slha_io()
   : slha_io()
   , print_imaginary_parts_of_majorana_mixings(false)
{
}

void MSSMNoFV_slha_io::clear()
{
   slha_io.clear();
}

void MSSMNoFV_slha_io::set_print_imaginary_parts_of_majorana_mixings(bool flag)
{
   print_imaginary_parts_of_majorana_mixings = flag;
}

/**
 * Stores the EXTPAR input parameters in the SLHA object.
 *
 * @param input struct of input parameters
 */
void MSSMNoFV_slha_io::set_extpar(const MSSMNoFV_input_parameters& input)
{
   std::ostringstream extpar;

   extpar << "Block EXTPAR\n";
   extpar << FORMAT_ELEMENT(0, input.Qin, "Qin");
   extpar << FORMAT_ELEMENT(1, input.M1, "M1");
   extpar << FORMAT_ELEMENT(2, input.M2, "M2");
   extpar << FORMAT_ELEMENT(3, input.M3, "M3");
   extpar << FORMAT_ELEMENT(11, input.AtIN, "AtIN");
   extpar << FORMAT_ELEMENT(12, input.AbIN, "AbIN");
   extpar << FORMAT_ELEMENT(13, input.AtauIN, "AtauIN");
   extpar << FORMAT_ELEMENT(14, input.AcIN, "AcIN");
   extpar << FORMAT_ELEMENT(15, input.AsIN, "AsIN");
   extpar << FORMAT_ELEMENT(16, input.AmuonIN, "AmuonIN");
   extpar << FORMAT_ELEMENT(17, input.AuIN, "AuIN");
   extpar << FORMAT_ELEMENT(18, input.AdIN, "AdIN");
   extpar << FORMAT_ELEMENT(19, input.AeIN, "AeIN");
   extpar << FORMAT_ELEMENT(21, input.mHd2IN, "mHd2IN");
   extpar << FORMAT_ELEMENT(22, input.mHu2IN, "mHu2IN");
   extpar << FORMAT_ELEMENT(31, input.ml11IN, "ml11IN");
   extpar << FORMAT_ELEMENT(32, input.ml22IN, "ml22IN");
   extpar << FORMAT_ELEMENT(33, input.ml33IN, "ml33IN");
   extpar << FORMAT_ELEMENT(34, input.me11IN, "me11IN");
   extpar << FORMAT_ELEMENT(35, input.me22IN, "me22IN");
   extpar << FORMAT_ELEMENT(36, input.me33IN, "me33IN");
   extpar << FORMAT_ELEMENT(41, input.mq11IN, "mq11IN");
   extpar << FORMAT_ELEMENT(42, input.mq22IN, "mq22IN");
   extpar << FORMAT_ELEMENT(43, input.mq33IN, "mq33IN");
   extpar << FORMAT_ELEMENT(44, input.mu11IN, "mu11IN");
   extpar << FORMAT_ELEMENT(45, input.mu22IN, "mu22IN");
   extpar << FORMAT_ELEMENT(46, input.mu33IN, "mu33IN");
   extpar << FORMAT_ELEMENT(47, input.md11IN, "md11IN");
   extpar << FORMAT_ELEMENT(48, input.md22IN, "md22IN");
   extpar << FORMAT_ELEMENT(49, input.md33IN, "md33IN");
   slha_io.set_block(extpar);

}

/**
 * Stores the IMMINPAR input parameters in the SLHA object.
 *
 * @param input struct of input parameters
 */
void MSSMNoFV_slha_io::set_imminpar(const MSSMNoFV_input_parameters& input)
{

}

/**
 * Stores the IMEXTPAR input parameters in the SLHA object.
 *
 * @param input struct of input parameters
 */
void MSSMNoFV_slha_io::set_imextpar(const MSSMNoFV_input_parameters& input)
{

}

/**
 * Stores the MODSEL input parameters in the SLHA object.
 *
 * @param modsel struct of MODSEL parameters
 */
void MSSMNoFV_slha_io::set_modsel(const SLHA_io::Modsel& modsel)
{
   slha_io.set_modsel(modsel);
}

/**
 * Stores the MINPAR input parameters in the SLHA object.
 *
 * @param input struct of input parameters
 */
void MSSMNoFV_slha_io::set_minpar(const MSSMNoFV_input_parameters& input)
{
   std::ostringstream minpar;

   minpar << "Block MINPAR\n";
   minpar << FORMAT_ELEMENT(3, input.TanBeta, "TanBeta");
   minpar << FORMAT_ELEMENT(4, input.SignMu, "SignMu");
   slha_io.set_block(minpar);

}

/**
 * Stores all input parameters in the SLHA object.
 *
 * @param input struct of input parameters
 */
void MSSMNoFV_slha_io::set_input(const MSSMNoFV_input_parameters& input)
{
   set_minpar(input);
   set_extpar(input);
   set_imminpar(input);
   set_imextpar(input);


}

/**
 * Stores the additional physical input (FlexibleSUSYInput block) in
 * the SLHA object.
 *
 * @param input class of input
 */
void MSSMNoFV_slha_io::set_physical_input(const Physical_input& input)
{
   slha_io.set_physical_input(input);
}

/**
 * Stores the settings (FlexibleSUSY block) in the SLHA object.
 *
 * @param settings class of settings
 */
void MSSMNoFV_slha_io::set_settings(const Spectrum_generator_settings& settings)
{
   slha_io.set_settings(settings);
}

/**
 * Stores the SMINPUTS input parameters in the SLHA object.
 *
 * @param qedqcd class of Standard Model parameters
 */
void MSSMNoFV_slha_io::set_sminputs(const softsusy::QedQcd& qedqcd)
{
   slha_io.set_sminputs(qedqcd);
}

/**
 * Stores the spectrum generator information in the SPINFO block in
 * the SLHA object.
 *
 * @param problems struct with parameter point problems
 */
void MSSMNoFV_slha_io::set_spinfo(const Spectrum_generator_problems& problems)
{
   set_spinfo(problems.get_problem_strings(), problems.get_warning_strings());
}

/**
 * Stores the spectrum generator information in the SPINFO block in
 * the SLHA object.
 *
 * @param problems struct with parameter point problems
 */
void MSSMNoFV_slha_io::set_spinfo(const Problems& problems)
{
   set_spinfo(problems.get_problem_strings(), problems.get_warning_strings());
}

/**
 * Stores the given problems and warnings in the SPINFO block in the
 * SLHA object.
 *
 * @param problems vector of problem strings
 * @param warnings vector of warning strings
 */
void MSSMNoFV_slha_io::set_spinfo(
   const std::vector<std::string>& problems,
   const std::vector<std::string>& warnings)
{
   std::ostringstream spinfo;
   spinfo << "Block SPINFO\n"
          << FORMAT_SPINFO(1, PKGNAME)
          << FORMAT_SPINFO(2, FLEXIBLESUSY_VERSION);

   for (const auto& s: warnings)
      spinfo << FORMAT_SPINFO(3, s);

   for (const auto& s: problems)
      spinfo << FORMAT_SPINFO(4, s);

   spinfo << FORMAT_SPINFO(5, MSSMNoFV_info::model_name)
          << FORMAT_SPINFO(9, SARAH_VERSION);

   slha_io.set_block(spinfo, SLHA_io::front);
}

/**
 * Stores the particle masses in the SLHA object.
 *
 * @param physical struct of physical parameters
 *
 * @param write_sm_masses flag to indicate if Standard Model
 *    particle masses should be written as well
 */
void MSSMNoFV_slha_io::set_mass(const MSSMNoFV_physical& physical,
                                   bool write_sm_masses)
{
   std::ostringstream mass;

   mass << "Block MASS\n"
      << FORMAT_MASS(1000021, LOCALPHYSICAL(MGlu), "Glu")
      << FORMAT_MASS(24, LOCALPHYSICAL(MVWm), "VWm")
      << FORMAT_MASS(1000012, LOCALPHYSICAL(MSveL), "SveL")
      << FORMAT_MASS(1000014, LOCALPHYSICAL(MSvmL), "SvmL")
      << FORMAT_MASS(1000016, LOCALPHYSICAL(MSvtL), "SvtL")
      << FORMAT_MASS(1000024, LOCALPHYSICAL(MCha(0)), "Cha(1)")
      << FORMAT_MASS(1000037, LOCALPHYSICAL(MCha(1)), "Cha(2)")
      << FORMAT_MASS(25, LOCALPHYSICAL(Mhh(0)), "hh(1)")
      << FORMAT_MASS(35, LOCALPHYSICAL(Mhh(1)), "hh(2)")
      << FORMAT_MASS(37, LOCALPHYSICAL(MHpm(1)), "Hpm(2)")
      << FORMAT_MASS(36, LOCALPHYSICAL(MAh(1)), "Ah(2)")
      << FORMAT_MASS(1000001, LOCALPHYSICAL(MSd(0)), "Sd(1)")
      << FORMAT_MASS(2000001, LOCALPHYSICAL(MSd(1)), "Sd(2)")
      << FORMAT_MASS(1000003, LOCALPHYSICAL(MSs(0)), "Ss(1)")
      << FORMAT_MASS(2000003, LOCALPHYSICAL(MSs(1)), "Ss(2)")
      << FORMAT_MASS(1000005, LOCALPHYSICAL(MSb(0)), "Sb(1)")
      << FORMAT_MASS(2000005, LOCALPHYSICAL(MSb(1)), "Sb(2)")
      << FORMAT_MASS(1000011, LOCALPHYSICAL(MSe(0)), "Se(1)")
      << FORMAT_MASS(2000011, LOCALPHYSICAL(MSe(1)), "Se(2)")
      << FORMAT_MASS(1000013, LOCALPHYSICAL(MSm(0)), "Sm(1)")
      << FORMAT_MASS(2000013, LOCALPHYSICAL(MSm(1)), "Sm(2)")
      << FORMAT_MASS(1000015, LOCALPHYSICAL(MStau(0)), "Stau(1)")
      << FORMAT_MASS(2000015, LOCALPHYSICAL(MStau(1)), "Stau(2)")
      << FORMAT_MASS(1000002, LOCALPHYSICAL(MSu(0)), "Su(1)")
      << FORMAT_MASS(2000002, LOCALPHYSICAL(MSu(1)), "Su(2)")
      << FORMAT_MASS(1000004, LOCALPHYSICAL(MSc(0)), "Sc(1)")
      << FORMAT_MASS(2000004, LOCALPHYSICAL(MSc(1)), "Sc(2)")
      << FORMAT_MASS(1000006, LOCALPHYSICAL(MSt(0)), "St(1)")
      << FORMAT_MASS(2000006, LOCALPHYSICAL(MSt(1)), "St(2)")
      << FORMAT_MASS(1000022, LOCALPHYSICAL(MChi(0)), "Chi(1)")
      << FORMAT_MASS(1000023, LOCALPHYSICAL(MChi(1)), "Chi(2)")
      << FORMAT_MASS(1000025, LOCALPHYSICAL(MChi(2)), "Chi(3)")
      << FORMAT_MASS(1000035, LOCALPHYSICAL(MChi(3)), "Chi(4)")
   ;

   if (write_sm_masses) {
      mass
         << FORMAT_MASS(21, LOCALPHYSICAL(MVG), "VG")
         << FORMAT_MASS(1, LOCALPHYSICAL(MFd), "Fd")
         << FORMAT_MASS(3, LOCALPHYSICAL(MFs), "Fs")
         << FORMAT_MASS(5, LOCALPHYSICAL(MFb), "Fb")
         << FORMAT_MASS(2, LOCALPHYSICAL(MFu), "Fu")
         << FORMAT_MASS(4, LOCALPHYSICAL(MFc), "Fc")
         << FORMAT_MASS(6, LOCALPHYSICAL(MFt), "Ft")
         << FORMAT_MASS(12, LOCALPHYSICAL(MFve), "Fve")
         << FORMAT_MASS(14, LOCALPHYSICAL(MFvm), "Fvm")
         << FORMAT_MASS(16, LOCALPHYSICAL(MFvt), "Fvt")
         << FORMAT_MASS(11, LOCALPHYSICAL(MFe), "Fe")
         << FORMAT_MASS(13, LOCALPHYSICAL(MFm), "Fm")
         << FORMAT_MASS(15, LOCALPHYSICAL(MFtau), "Ftau")
         << FORMAT_MASS(22, LOCALPHYSICAL(MVP), "VP")
         << FORMAT_MASS(23, LOCALPHYSICAL(MVZ), "VZ")
      ;
   }

   slha_io.set_block(mass);

}

/**
 * Stores the mixing matrices in the SLHA object.
 *
 * @param physical struct of physical parameters
 *
 * @param write_sm_mixing_matrics flag to indicate if Standard Model
 *    particle mixing matrices should be written as well
 */
void MSSMNoFV_slha_io::set_mixing_matrices(const MSSMNoFV_physical& physical,
                                              bool write_sm_mixing_matrics)
{
   slha_io.set_block("UMIX", LOCALPHYSICAL(UM), "UM");
   slha_io.set_block("VMIX", LOCALPHYSICAL(UP), "UP");
   slha_io.set_block("PSEUDOSCALARMIX", LOCALPHYSICAL(ZA), "ZA");
   slha_io.set_block("sbotmix", LOCALPHYSICAL(ZB), "ZB");
   slha_io.set_block("scharmmix", LOCALPHYSICAL(ZC), "ZC");
   slha_io.set_block("sdownmix", LOCALPHYSICAL(ZD), "ZD");
   slha_io.set_block("selemix", LOCALPHYSICAL(ZE), "ZE");
   slha_io.set_block("SCALARMIX", LOCALPHYSICAL(ZH), "ZH");
   slha_io.set_block("smumix", LOCALPHYSICAL(ZM), "ZM");
   slha_io.set_block("NMIX", LOCALPHYSICAL(ZN), "ZN");
   slha_io.set_block("CHARGEMIX", LOCALPHYSICAL(ZP), "ZP");
   slha_io.set_block("sstrmix", LOCALPHYSICAL(ZS), "ZS");
   slha_io.set_block("stopmix", LOCALPHYSICAL(ZT), "ZT");
   slha_io.set_block("staumix", LOCALPHYSICAL(ZTau), "ZTau");
   slha_io.set_block("supmix", LOCALPHYSICAL(ZU), "ZU");

   if (write_sm_mixing_matrics) {
   }

   if (print_imaginary_parts_of_majorana_mixings) {
      slha_io.set_block_imag("IMNMIX", LOCALPHYSICAL(ZN), "ZN");
   }

}

void MSSMNoFV_slha_io::set_ckm(
   const Eigen::Matrix<std::complex<double>,3,3>& ckm_matrix,
   double scale)
{
   slha_io.set_block("VCKM"  , ckm_matrix.real(), "Re(CKM)", scale);
   slha_io.set_block("IMVCKM", ckm_matrix.imag(), "Im(CKM)", scale);
}

void MSSMNoFV_slha_io::set_pmns(
   const Eigen::Matrix<std::complex<double>,3,3>& pmns_matrix,
   double scale)
{
   slha_io.set_block("VPMNS"  , pmns_matrix.real(), "Re(PMNS)", scale);
   slha_io.set_block("IMVPMNS", pmns_matrix.imag(), "Im(PMNS)", scale);
}

/**
 * Write SLHA object to given output.  If output == "-", then the SLHA
 * object is written to std::cout.  Otherwise, output is interpreted
 * as a file name
 *
 * @param output "-" for cout, or file name
 */
void MSSMNoFV_slha_io::write_to(const std::string& output) const
{
   if (output == "-")
      write_to_stream(std::cout);
   else
      write_to_file(output);
}

/**
 * Read (DR-bar) model parameter output scale from MODSEL entry 12
 */
double MSSMNoFV_slha_io::get_parameter_output_scale() const
{
   return slha_io.get_modsel().parameter_output_scale;
}

/**
 * Read SLHA object from file
 *
 * @param file_name file name
 */
void MSSMNoFV_slha_io::read_from_file(const std::string& file_name)
{
   slha_io.read_from_file(file_name);
}

/**
 * Read SLHA object from source
 *
 * calls SLHA_io::read_from_source()
 *
 * @param source source name
 */
void MSSMNoFV_slha_io::read_from_source(const std::string& source)
{
   slha_io.read_from_source(source);
}

/**
 * Read SLHA object from stream
 *
 * @param istr stream name
 */
void MSSMNoFV_slha_io::read_from_stream(std::istream& istr)
{
   slha_io.read_from_stream(istr);
}

/**
 * Fill struct of model input parameters from SLHA object (MINPAR,
 * EXTPAR and IMEXTPAR blocks)
 *
 * @param input struct of model input parameters
 */
void MSSMNoFV_slha_io::fill(MSSMNoFV_input_parameters& input) const
{
   SLHA_io::Tuple_processor minpar_processor = [&input, this] (int key, double value) {
      return fill_minpar_tuple(input, key, value);
   };

   SLHA_io::Tuple_processor extpar_processor = [&input, this] (int key, double value) {
      return fill_extpar_tuple(input, key, value);
   };

   SLHA_io::Tuple_processor imminpar_processor = [&input, this] (int key, double value) {
      return fill_imminpar_tuple(input, key, value);
   };

   SLHA_io::Tuple_processor imextpar_processor = [&input, this] (int key, double value) {
      return fill_imextpar_tuple(input, key, value);
   };

   slha_io.read_block("MINPAR", minpar_processor);
   slha_io.read_block("EXTPAR", extpar_processor);
   slha_io.read_block("IMMINPAR", imminpar_processor);
   slha_io.read_block("IMEXTPAR", imextpar_processor);


}

/**
 * Reads DR-bar parameters from a SLHA output file.
 *
 * @param model model class to be filled
 */
void MSSMNoFV_slha_io::fill_drbar_parameters(MSSMNoFV_mass_eigenstates& model) const
{
   model.set_g1(slha_io.read_entry("gauge", 1) * 1.2909944487358056);
   model.set_g2(slha_io.read_entry("gauge", 2));
   model.set_g3(slha_io.read_entry("gauge", 3));
   {
      Eigen::Matrix<double,3,3> Yu;
      slha_io.read_block("Yu", Yu);
      model.set_Yu(Yu);
   }
   {
      Eigen::Matrix<double,3,3> Yd;
      slha_io.read_block("Yd", Yd);
      model.set_Yd(Yd);
   }
   {
      Eigen::Matrix<double,3,3> Ye;
      slha_io.read_block("Ye", Ye);
      model.set_Ye(Ye);
   }
   {
      Eigen::Matrix<double,3,3> TYe;
      slha_io.read_block("Te", TYe);
      model.set_TYe(TYe);
   }
   {
      Eigen::Matrix<double,3,3> TYd;
      slha_io.read_block("Td", TYd);
      model.set_TYd(TYd);
   }
   {
      Eigen::Matrix<double,3,3> TYu;
      slha_io.read_block("Tu", TYu);
      model.set_TYu(TYu);
   }
   model.set_Mu(slha_io.read_entry("HMIX", 1));
   model.set_BMu(slha_io.read_entry("HMIX", 101));
   {
      Eigen::Matrix<double,3,3> mq2;
      slha_io.read_block("MSQ2", mq2);
      model.set_mq2(mq2);
   }
   {
      Eigen::Matrix<double,3,3> me2;
      slha_io.read_block("MSE2", me2);
      model.set_me2(me2);
   }
   {
      Eigen::Matrix<double,3,3> ml2;
      slha_io.read_block("MSL2", ml2);
      model.set_ml2(ml2);
   }
   {
      Eigen::Matrix<double,3,3> mu2;
      slha_io.read_block("MSU2", mu2);
      model.set_mu2(mu2);
   }
   {
      Eigen::Matrix<double,3,3> md2;
      slha_io.read_block("MSD2", md2);
      model.set_md2(md2);
   }
   model.set_mHd2(slha_io.read_entry("MSOFT", 21));
   model.set_mHu2(slha_io.read_entry("MSOFT", 22));
   model.set_MassB(slha_io.read_entry("MSOFT", 1));
   model.set_MassWB(slha_io.read_entry("MSOFT", 2));
   model.set_MassG(slha_io.read_entry("MSOFT", 3));
   model.set_vd(slha_io.read_entry("HMIX", 102));
   model.set_vu(slha_io.read_entry("HMIX", 103));


   model.set_scale(read_scale());
}

/**
 * Reads DR-bar parameters, pole masses and mixing matrices (in
 * Haber-Kane convention) from a SLHA output file.
 *
 * @param model model class to be filled
 */
void MSSMNoFV_slha_io::fill(MSSMNoFV_mass_eigenstates& model) const
{
   fill_drbar_parameters(model);

   MSSMNoFV_physical physical_hk;
   fill_physical(physical_hk);
   physical_hk.convert_to_hk();
   model.get_physical() = physical_hk;
}

/**
 * Fill struct of extra physical input parameters from SLHA object
 * (FlexibleSUSYInput block)
 *
 * @param input struct of physical non-SLHA input parameters
 */
void MSSMNoFV_slha_io::fill(Physical_input& input) const
{
   slha_io.fill(input);
}

/**
 * Fill struct of spectrum generator settings from SLHA object
 * (FlexibleSUSY block)
 *
 * @param settings struct of spectrum generator settings to be filled
 */
void MSSMNoFV_slha_io::fill(Spectrum_generator_settings& settings) const
{
   slha_io.fill(settings);
}

void MSSMNoFV_slha_io::fill_minpar_tuple(MSSMNoFV_input_parameters& input,
                                                int key, double value)
{
   switch (key) {
   case 3: input.TanBeta = value; break;
   case 4: input.SignMu = value; break;
   default: WARNING("Unrecognized entry in block MINPAR: " << key); break;
   }

}

void MSSMNoFV_slha_io::fill_extpar_tuple(MSSMNoFV_input_parameters& input,
                                                int key, double value)
{
   switch (key) {
   case 0: input.Qin = value; break;
   case 1: input.M1 = value; break;
   case 2: input.M2 = value; break;
   case 3: input.M3 = value; break;
   case 11: input.AtIN = value; break;
   case 12: input.AbIN = value; break;
   case 13: input.AtauIN = value; break;
   case 14: input.AcIN = value; break;
   case 15: input.AsIN = value; break;
   case 16: input.AmuonIN = value; break;
   case 17: input.AuIN = value; break;
   case 18: input.AdIN = value; break;
   case 19: input.AeIN = value; break;
   case 21: input.mHd2IN = value; break;
   case 22: input.mHu2IN = value; break;
   case 31: input.ml11IN = value; break;
   case 32: input.ml22IN = value; break;
   case 33: input.ml33IN = value; break;
   case 34: input.me11IN = value; break;
   case 35: input.me22IN = value; break;
   case 36: input.me33IN = value; break;
   case 41: input.mq11IN = value; break;
   case 42: input.mq22IN = value; break;
   case 43: input.mq33IN = value; break;
   case 44: input.mu11IN = value; break;
   case 45: input.mu22IN = value; break;
   case 46: input.mu33IN = value; break;
   case 47: input.md11IN = value; break;
   case 48: input.md22IN = value; break;
   case 49: input.md33IN = value; break;
   default: WARNING("Unrecognized entry in block EXTPAR: " << key); break;
   }

}

void MSSMNoFV_slha_io::fill_imminpar_tuple(MSSMNoFV_input_parameters& input,
                                                int key, double value)
{
   switch (key) {
   default: WARNING("Unrecognized entry in block IMMINPAR: " << key); break;
   }

}

void MSSMNoFV_slha_io::fill_imextpar_tuple(MSSMNoFV_input_parameters& input,
                                                int key, double value)
{
   switch (key) {
   default: WARNING("Unrecognized entry in block IMEXTPAR: " << key); break;
   }

}

/**
 * Reads pole masses and mixing matrices from a SLHA output file to be filled.
 */
void MSSMNoFV_slha_io::fill_physical(MSSMNoFV_physical& physical) const
{
   {
      DEFINE_PHYSICAL_PARAMETER(ZH);
      slha_io.read_block("SCALARMIX", ZH);
      LOCALPHYSICAL(ZH) = ZH;
   }
   {
      DEFINE_PHYSICAL_PARAMETER(ZA);
      slha_io.read_block("PSEUDOSCALARMIX", ZA);
      LOCALPHYSICAL(ZA) = ZA;
   }
   {
      DEFINE_PHYSICAL_PARAMETER(ZP);
      slha_io.read_block("CHARGEMIX", ZP);
      LOCALPHYSICAL(ZP) = ZP;
   }
   {
      DEFINE_PHYSICAL_PARAMETER(ZN);
      slha_io.read_block("NMIX", ZN);
      LOCALPHYSICAL(ZN) = ZN;
   }
   {
      DEFINE_PHYSICAL_PARAMETER(UP);
      slha_io.read_block("VMIX", UP);
      LOCALPHYSICAL(UP) = UP;
   }
   {
      DEFINE_PHYSICAL_PARAMETER(UM);
      slha_io.read_block("UMIX", UM);
      LOCALPHYSICAL(UM) = UM;
   }
   {
      DEFINE_PHYSICAL_PARAMETER(ZD);
      slha_io.read_block("sdownmix", ZD);
      LOCALPHYSICAL(ZD) = ZD;
   }
   {
      DEFINE_PHYSICAL_PARAMETER(ZS);
      slha_io.read_block("sstrmix", ZS);
      LOCALPHYSICAL(ZS) = ZS;
   }
   {
      DEFINE_PHYSICAL_PARAMETER(ZB);
      slha_io.read_block("sbotmix", ZB);
      LOCALPHYSICAL(ZB) = ZB;
   }
   {
      DEFINE_PHYSICAL_PARAMETER(ZU);
      slha_io.read_block("supmix", ZU);
      LOCALPHYSICAL(ZU) = ZU;
   }
   {
      DEFINE_PHYSICAL_PARAMETER(ZC);
      slha_io.read_block("scharmmix", ZC);
      LOCALPHYSICAL(ZC) = ZC;
   }
   {
      DEFINE_PHYSICAL_PARAMETER(ZT);
      slha_io.read_block("stopmix", ZT);
      LOCALPHYSICAL(ZT) = ZT;
   }
   {
      DEFINE_PHYSICAL_PARAMETER(ZE);
      slha_io.read_block("selemix", ZE);
      LOCALPHYSICAL(ZE) = ZE;
   }
   {
      DEFINE_PHYSICAL_PARAMETER(ZM);
      slha_io.read_block("smumix", ZM);
      LOCALPHYSICAL(ZM) = ZM;
   }
   {
      DEFINE_PHYSICAL_PARAMETER(ZTau);
      slha_io.read_block("staumix", ZTau);
      LOCALPHYSICAL(ZTau) = ZTau;
   }

   LOCALPHYSICAL(MVG) = slha_io.read_entry("MASS", 21);
   LOCALPHYSICAL(MGlu) = slha_io.read_entry("MASS", 1000021);
   LOCALPHYSICAL(MVP) = slha_io.read_entry("MASS", 22);
   LOCALPHYSICAL(MVZ) = slha_io.read_entry("MASS", 23);
   LOCALPHYSICAL(MFd) = slha_io.read_entry("MASS", 1);
   LOCALPHYSICAL(MFs) = slha_io.read_entry("MASS", 3);
   LOCALPHYSICAL(MFb) = slha_io.read_entry("MASS", 5);
   LOCALPHYSICAL(MFu) = slha_io.read_entry("MASS", 2);
   LOCALPHYSICAL(MFc) = slha_io.read_entry("MASS", 4);
   LOCALPHYSICAL(MFt) = slha_io.read_entry("MASS", 6);
   LOCALPHYSICAL(MFve) = slha_io.read_entry("MASS", 12);
   LOCALPHYSICAL(MFvm) = slha_io.read_entry("MASS", 14);
   LOCALPHYSICAL(MFvt) = slha_io.read_entry("MASS", 16);
   LOCALPHYSICAL(MFe) = slha_io.read_entry("MASS", 11);
   LOCALPHYSICAL(MFm) = slha_io.read_entry("MASS", 13);
   LOCALPHYSICAL(MFtau) = slha_io.read_entry("MASS", 15);
   LOCALPHYSICAL(MSveL) = slha_io.read_entry("MASS", 1000012);
   LOCALPHYSICAL(MSvmL) = slha_io.read_entry("MASS", 1000014);
   LOCALPHYSICAL(MSvtL) = slha_io.read_entry("MASS", 1000016);
   LOCALPHYSICAL(MSd)(0) = slha_io.read_entry("MASS", 1000001);
   LOCALPHYSICAL(MSd)(1) = slha_io.read_entry("MASS", 2000001);
   LOCALPHYSICAL(MSu)(0) = slha_io.read_entry("MASS", 1000002);
   LOCALPHYSICAL(MSu)(1) = slha_io.read_entry("MASS", 2000002);
   LOCALPHYSICAL(MSe)(0) = slha_io.read_entry("MASS", 1000011);
   LOCALPHYSICAL(MSe)(1) = slha_io.read_entry("MASS", 2000011);
   LOCALPHYSICAL(MSm)(0) = slha_io.read_entry("MASS", 1000013);
   LOCALPHYSICAL(MSm)(1) = slha_io.read_entry("MASS", 2000013);
   LOCALPHYSICAL(MStau)(0) = slha_io.read_entry("MASS", 1000015);
   LOCALPHYSICAL(MStau)(1) = slha_io.read_entry("MASS", 2000015);
   LOCALPHYSICAL(MSs)(0) = slha_io.read_entry("MASS", 1000003);
   LOCALPHYSICAL(MSs)(1) = slha_io.read_entry("MASS", 2000003);
   LOCALPHYSICAL(MSc)(0) = slha_io.read_entry("MASS", 1000004);
   LOCALPHYSICAL(MSc)(1) = slha_io.read_entry("MASS", 2000004);
   LOCALPHYSICAL(MSb)(0) = slha_io.read_entry("MASS", 1000005);
   LOCALPHYSICAL(MSb)(1) = slha_io.read_entry("MASS", 2000005);
   LOCALPHYSICAL(MSt)(0) = slha_io.read_entry("MASS", 1000006);
   LOCALPHYSICAL(MSt)(1) = slha_io.read_entry("MASS", 2000006);
   LOCALPHYSICAL(Mhh)(0) = slha_io.read_entry("MASS", 25);
   LOCALPHYSICAL(Mhh)(1) = slha_io.read_entry("MASS", 35);
   LOCALPHYSICAL(MAh)(1) = slha_io.read_entry("MASS", 36);
   LOCALPHYSICAL(MHpm)(1) = slha_io.read_entry("MASS", 37);
   LOCALPHYSICAL(MChi)(0) = slha_io.read_entry("MASS", 1000022);
   LOCALPHYSICAL(MChi)(1) = slha_io.read_entry("MASS", 1000023);
   LOCALPHYSICAL(MChi)(2) = slha_io.read_entry("MASS", 1000025);
   LOCALPHYSICAL(MChi)(3) = slha_io.read_entry("MASS", 1000035);
   LOCALPHYSICAL(MCha)(0) = slha_io.read_entry("MASS", 1000024);
   LOCALPHYSICAL(MCha)(1) = slha_io.read_entry("MASS", 1000037);
   LOCALPHYSICAL(MVWm) = slha_io.read_entry("MASS", 24);

}

/**
 * Reads the renormalization scales from all DR-bar parameter blocks.
 * If blocks with different scales are found the last scale is
 * returned and a warning is printed.
 *
 * @return common renormalization scale
 */
double MSSMNoFV_slha_io::read_scale() const
{
   static const std::array<std::string, 14> drbar_blocks =
      { "gauge", "Yu", "Yd", "Ye", "Te", "Td", "Tu", "HMIX", "MSQ2", "MSE2",
   "MSL2", "MSU2", "MSD2", "MSOFT" }
;

   double scale = 0.;

   for (const auto& block: drbar_blocks) {
      const double block_scale = slha_io.read_scale(block);
      if (!is_zero(block_scale)) {
         if (!is_zero(scale) && !is_equal(scale, block_scale))
            WARNING("DR-bar parameters defined at different scales");
         scale = block_scale;
      }
   }

   return scale;
}

} // namespace flexiblesusy
