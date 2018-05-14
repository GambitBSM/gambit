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

// File generated at Thu 10 May 2018 14:48:00

#include "config.h"

#include "HSSUSY_input_parameters.hpp"
#include "HSSUSY_model_slha.hpp"
#include "HSSUSY_spectrum_generator.hpp"

#ifdef ENABLE_TWO_SCALE_SOLVER
#include "HSSUSY_two_scale_spectrum_generator.hpp"
#endif

#include "command_line_options.hpp"
#include "scan.hpp"
#include "lowe.h"
#include "logger.hpp"

#include <iostream>
#include <cstring>

#define INPUTPARAMETER(p) input.p

namespace flexiblesusy {

void print_usage()
{
   std::cout <<
      "Usage: scan_HSSUSY.x [options]\n"
      "Options:\n"
      "  --MSUSY=<value>\n"
      "  --M1Input=<value>\n"
      "  --M2Input=<value>\n"
      "  --M3Input=<value>\n"
      "  --MuInput=<value>\n"
      "  --mAInput=<value>\n"
      "  --MEWSB=<value>\n"
      "  --AtInput=<value>\n"
      "  --AbInput=<value>\n"
      "  --AtauInput=<value>\n"
      "  --TanBeta=<value>\n"
      "  --LambdaLoopOrder=<value>\n"
      "  --TwoLoopAtAs=<value>\n"
      "  --TwoLoopAbAs=<value>\n"
      "  --TwoLoopAtAb=<value>\n"
      "  --TwoLoopAtauAtau=<value>\n"
      "  --TwoLoopAtAt=<value>\n"
      "  --DeltaEFT=<value>\n"

      "  --solver-type=<value>             an integer corresponding\n"
      "                                    to the solver type to use\n"
      "  --help,-h                         print this help message"
             << std::endl;
}

void set_command_line_parameters(const Dynamic_array_view<char*>& args,
                                 HSSUSY_input_parameters& input,
                                 int& solver_type)
{
   for (int i = 1; i < args.size(); ++i) {
      const auto option = args[i];

      if(Command_line_options::get_parameter_value(option, "--MSUSY=", input.MSUSY))
         continue;

      if(Command_line_options::get_parameter_value(option, "--M1Input=", input.M1Input))
         continue;

      if(Command_line_options::get_parameter_value(option, "--M2Input=", input.M2Input))
         continue;

      if(Command_line_options::get_parameter_value(option, "--M3Input=", input.M3Input))
         continue;

      if(Command_line_options::get_parameter_value(option, "--MuInput=", input.MuInput))
         continue;

      if(Command_line_options::get_parameter_value(option, "--mAInput=", input.mAInput))
         continue;

      if(Command_line_options::get_parameter_value(option, "--MEWSB=", input.MEWSB))
         continue;

      if(Command_line_options::get_parameter_value(option, "--AtInput=", input.AtInput))
         continue;

      if(Command_line_options::get_parameter_value(option, "--AbInput=", input.AbInput))
         continue;

      if(Command_line_options::get_parameter_value(option, "--AtauInput=", input.AtauInput))
         continue;

      if(Command_line_options::get_parameter_value(option, "--TanBeta=", input.TanBeta))
         continue;

      if(Command_line_options::get_parameter_value(option, "--LambdaLoopOrder=", input.LambdaLoopOrder))
         continue;

      if(Command_line_options::get_parameter_value(option, "--TwoLoopAtAs=", input.TwoLoopAtAs))
         continue;

      if(Command_line_options::get_parameter_value(option, "--TwoLoopAbAs=", input.TwoLoopAbAs))
         continue;

      if(Command_line_options::get_parameter_value(option, "--TwoLoopAtAb=", input.TwoLoopAtAb))
         continue;

      if(Command_line_options::get_parameter_value(option, "--TwoLoopAtauAtau=", input.TwoLoopAtauAtau))
         continue;

      if(Command_line_options::get_parameter_value(option, "--TwoLoopAtAt=", input.TwoLoopAtAt))
         continue;

      if(Command_line_options::get_parameter_value(option, "--DeltaEFT=", input.DeltaEFT))
         continue;

      
      if (Command_line_options::get_parameter_value(
             option, "--solver-type=", solver_type))
         continue;

      if (strcmp(option,"--help") == 0 || strcmp(option,"-h") == 0) {
         print_usage();
         exit(EXIT_SUCCESS);
      }

      ERROR("Unrecognized command line option: " << option);
      exit(EXIT_FAILURE);
   }
}

struct HSSUSY_scan_result {
   Spectrum_generator_problems problems;
   double higgs{0.};
};

template <class solver_type>
HSSUSY_scan_result run_parameter_point(const softsusy::QedQcd& qedqcd,
   HSSUSY_input_parameters& input)
{
   Spectrum_generator_settings settings;
   settings.set(Spectrum_generator_settings::precision, 1.0e-4);

   HSSUSY_spectrum_generator<solver_type> spectrum_generator;
   spectrum_generator.set_settings(settings);
   spectrum_generator.run(qedqcd, input);

   const auto model = std::get<0>(spectrum_generator.get_models_slha());
   const auto& pole_masses = model.get_physical_slha();

   HSSUSY_scan_result result;
   result.problems = spectrum_generator.get_problems();
   result.higgs = pole_masses.Mhh;

   return result;
}

void scan(int solver_type, HSSUSY_input_parameters& input,
          const std::vector<double>& range)
{
   softsusy::QedQcd qedqcd;

   for (const auto p: range) {
      INPUTPARAMETER(MSUSY) = p;

      HSSUSY_scan_result result;
      switch (solver_type) {
      case 0:
#ifdef ENABLE_TWO_SCALE_SOLVER
      case 1:
         result = run_parameter_point<Two_scale>(qedqcd, input);
         if (!result.problems.have_problem() || solver_type != 0) break;
#endif

      default:
         if (solver_type != 0) {
            ERROR("unknown solver type: " << solver_type);
            exit(EXIT_FAILURE);
         }
      }

      const int error = result.problems.have_problem();
      std::cout << "  "
                << std::setw(12) << std::left << p << ' '
                << std::setw(12) << std::left << result.higgs << ' '
                << std::setw(12) << std::left << error;
      if (error) {
         std::cout << "\t# " << result.problems;
      }
      std::cout << '\n';
   }
}

} // namespace flexiblesusy


int main(int argc, char* argv[])
{
   using namespace flexiblesusy;

   HSSUSY_input_parameters input;
   int solver_type = 1;
   set_command_line_parameters(make_dynamic_array_view(&argv[0], argc), input,
                               solver_type);

   std::cout << "# "
             << std::setw(12) << std::left << "MSUSY" << ' '
             << std::setw(12) << std::left << "Mhh/GeV" << ' '
             << std::setw(12) << std::left << "error"
             << '\n';

   const std::vector<double> range(float_range(0., 100., 10));

   scan(solver_type, input, range);

   return 0;
}
