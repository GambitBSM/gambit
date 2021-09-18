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

  #include <pybind11/stl.h>

  namespace Gambit
  {
    // Class that manages the input dictionary for Contur
    class Contur_output
    {
    public:
      //Three member objects:
      double LLR;
      map_str_dbl pool_LLR;
      map_str_str pool_tags;

      //Default constructor - used if no events produced
      Contur_output(){
          LLR = 0.0;
          pool_LLR = {};
          pool_tags = {};
      }

      //Conctructor using the pybind11::dict we get from contur:
      Contur_output(pybind11::dict input_dict){
        LLR = input_dict.attr("get")("LLR").cast<double>();
        pool_LLR = input_dict.attr("get")("Pool_LLR").cast<map_str_dbl>();
        pool_tags = input_dict.attr("get")("Pool_tags").cast<map_str_str>();
      }

      //Automatic destructor should be fine, no need to define

      //Print the object and all its data in an easy to read format.
      void print_Contur_output_debug(std::ostream&outstream = std::cout){
        outstream << "\nContur Output Object.\n\tLLR is: " <<
          LLR << "\n\tPool LLR's:";

        for (auto pool : pool_LLR){
          outstream << "\n\t\t" << pool.first << ": " << pool.second;
        }
        outstream << "\n\tPool Histotags:";
        for (auto pool : pool_tags){
          outstream << "\n\t\t" << pool.first << ": " << pool.second;
        }
        outstream << std::endl;
      }
    };
  }
#endif

#endif
