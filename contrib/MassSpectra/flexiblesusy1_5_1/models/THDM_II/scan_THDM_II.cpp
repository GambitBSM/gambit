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

// File generated at Wed 29 Mar 2017 15:37:11

#include "THDM_II_input_parameters.hpp"
#include "THDM_II_spectrum_generator.hpp"
#include "THDM_II_two_scale_model_slha.hpp"

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
      "Usage: scan_THDM_II.x [options]\n"
      "Options:\n"
      "  --Lambda1IN=<value>\n"
      "  --Lambda2IN=<value>\n"
      "  --Lambda3IN=<value>\n"
      "  --Lambda4IN=<value>\n"
      "  --Lambda5IN=<value>\n"
      "  --Lambda6IN=<value>\n"
      "  --Lambda7IN=<value>\n"
      "  --M122IN=<value>\n"
      "  --TanBeta=<value>\n"
      "  --Qin=<value>\n"
      "  --QEWSB=<value>\n"

      "  --help,-h                         print this help message"
             << std::endl;
}

void set_command_line_parameters(int argc, char* argv[],
                                 THDM_II_input_parameters& input)
{
   for (int i = 1; i < argc; ++i) {
      const char* option = argv[i];

      if(Command_line_options::get_parameter_value(option, "--Lambda1IN=", input.Lambda1IN))
         continue;

      if(Command_line_options::get_parameter_value(option, "--Lambda2IN=", input.Lambda2IN))
         continue;

      if(Command_line_options::get_parameter_value(option, "--Lambda3IN=", input.Lambda3IN))
         continue;

      if(Command_line_options::get_parameter_value(option, "--Lambda4IN=", input.Lambda4IN))
         continue;

      if(Command_line_options::get_parameter_value(option, "--Lambda5IN=", input.Lambda5IN))
         continue;

      if(Command_line_options::get_parameter_value(option, "--Lambda6IN=", input.Lambda6IN))
         continue;

      if(Command_line_options::get_parameter_value(option, "--Lambda7IN=", input.Lambda7IN))
         continue;

      if(Command_line_options::get_parameter_value(option, "--M122IN=", input.M122IN))
         continue;

      if(Command_line_options::get_parameter_value(option, "--TanBeta=", input.TanBeta))
         continue;

      if(Command_line_options::get_parameter_value(option, "--Qin=", input.Qin))
         continue;

      if(Command_line_options::get_parameter_value(option, "--QEWSB=", input.QEWSB))
         continue;

      
      if (strcmp(option,"--help") == 0 || strcmp(option,"-h") == 0) {
         print_usage();
         exit(EXIT_SUCCESS);
      }

      ERROR("Unrecognized command line option: " << option);
      exit(EXIT_FAILURE);
   }
}

} // namespace flexiblesusy


int main(int argc, char* argv[])
{
   using namespace flexiblesusy;
   typedef Two_scale algorithm_type;

   THDM_II_input_parameters input;
   set_command_line_parameters(argc, argv, input);

   softsusy::QedQcd qedqcd;

   try {
      qedqcd.to(qedqcd.displayPoleMZ()); // run SM fermion masses to MZ
   } catch (const std::string& s) {
      ERROR(s);
      return EXIT_FAILURE;
   }

   THDM_II_spectrum_generator<algorithm_type> spectrum_generator;
   spectrum_generator.set_precision_goal(1.0e-4);
   spectrum_generator.set_max_iterations(0);         // 0 == automatic
   spectrum_generator.set_calculate_sm_masses(0);    // 0 == no
   spectrum_generator.set_parameter_output_scale(0); // 0 == susy scale

   const std::vector<double> range(float_range(0., 100., 10));

   cout << "# "
        << std::setw(12) << std::left << "Lambda1IN" << ' '
        << std::setw(12) << std::left << "Mhh(0)/GeV" << ' '
        << std::setw(12) << std::left << "error"
        << '\n';

   for (std::vector<double>::const_iterator it = range.begin(),
           end = range.end(); it != end; ++it) {
      INPUTPARAMETER(Lambda1IN) = *it;


      spectrum_generator.run(qedqcd, input);

      const THDM_II_slha<algorithm_type> model(spectrum_generator.get_model());
      const THDM_II_physical& pole_masses = model.get_physical_slha();
      const Problems<THDM_II_info::NUMBER_OF_PARTICLES>& problems
         = spectrum_generator.get_problems();
      const double higgs = pole_masses.Mhh(0);
      const bool error = problems.have_problem();

      cout << "  "
           << std::setw(12) << std::left << *it << ' '
           << std::setw(12) << std::left << higgs << ' '
           << std::setw(12) << std::left << error;
      if (error) {
         cout << "\t# " << problems;
      }
      cout << '\n';
   }

   return 0;
}
