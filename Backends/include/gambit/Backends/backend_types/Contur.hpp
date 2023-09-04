//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Declaration of the Contur_output class that
///  converts the python dictionary output from
///  the contur API main into a simple class.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Tomasz Procter
///          (t.procter.1@research.gla.ac.uk)
///  \date 2021 July
///
///  *********************************************

#ifndef __contur_types_hpp__
#define __contur_types_hpp__

#include "gambit/cmake/cmake_variables.hpp"
#include "gambit/Utils/util_types.hpp"

#ifdef HAVE_PYBIND11

  #include "gambit/Utils/begin_ignore_warnings_pybind11.hpp"
  #include <pybind11/stl.h>
  #include "gambit/Utils/end_ignore_warnings.hpp"

  namespace Gambit
  {
    // Class that manages the input dictionary for Contur
    class Contur_output
    {
      friend Contur_output merge_contur_outputs(const Contur_output& output1, const Contur_output& output2);

      public:
        //Three member objects:
        double LLR;
        map_str_dbl pool_LLR;
        map_str_str pool_tags;

        //Default constructor - used if no events produced
        Contur_output()
        {
            LLR = 0.0;
            pool_LLR = {};
            pool_tags = {};
        }

        //Constructor using the pybind11::dict we get from contur:
        Contur_output(pybind11::dict input_dict)
        {
          //Eliminating the factor of -2 for the GAMBIT LLR definition
          LLR = -0.5*input_dict.attr("get")("LLR").cast<double>();
          pool_LLR = input_dict.attr("get")("Pool_LLR").cast<map_str_dbl>();
          //Eliminating the factor of -2 in the pools:
          for (auto &pool : pool_LLR)
          {
            pool.second=-0.5*pool.second;
          }
          pool_tags = input_dict.attr("get")("Pool_tags").cast<map_str_str>();
        }

        //Constructor with all parts supplied: for the friend merge function
        Contur_output(const double newLLR, const map_str_dbl& newPool_LLR, const map_str_str& newPool_tags)
        {
          LLR = newLLR;
          pool_LLR = newPool_LLR;
          pool_tags = newPool_tags;
        }

        //Automatic destructor should be fine, no need to define

        //Print the object and all its data in an easy to read format.
        void print_Contur_output_debug(std::ostream&outstream = std::cout) const;

      };

      //For running Contur multiple times with different settings.
      typedef std::map<std::string, Contur_output> Multi_Contur_output;

      //Helper function
      Contur_output merge_contur_outputs(const Contur_output& output1, const Contur_output& output2);
      Multi_Contur_output merge_multi_contur_outputs(const Multi_Contur_output& output1, const Multi_Contur_output& output2);

      void print_Multi_Contur_output_debug(const Multi_Contur_output& multi_contur_out, std::ostream& outstream = std::cout);

  }
#endif

#endif
