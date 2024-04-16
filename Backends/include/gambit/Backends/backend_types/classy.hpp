//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Declaration of the Classy_input class used for
///  communicating with the backend classy.
///  It has the attribute 'input_dict' which is a python
///  dictionary containing the input parameters for CLASS
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Patrick Stoecker
///          (stoecker@physik.rwth-aachen.de)
///  \date 2017 Nov
///  \date 2018 May
///
///  \author Janina Renk
///          (janina.renk@fysik.su.se)
///  \date 2018 Oct
///  \date 2019 Mar
///  \date 2020 Aug
///
///  \author Sebastian Hoof
///          (hoof@uni-goettingen.de)
///  \date 2020 Mar
///
///  \author Pat Scott
///          (pat.scott@uq.edu.au)
///  \date 2020 Apr
///
///  *********************************************

#ifndef __classy_types_hpp__
#define __classy_types_hpp__

#include "gambit/cmake/cmake_variables.hpp"
#include "gambit/Utils/util_types.hpp"

#ifdef HAVE_PYBIND11

  #include "gambit/Utils/begin_ignore_warnings_pybind11.hpp"
  #include <pybind11/stl.h>
  #include "gambit/Utils/end_ignore_warnings.hpp"

  namespace Gambit
  {

    // Class that manages the input dictionary for classy
    class Classy_input
    {
      public:

        // add entries of different types to 
        // member input_dict
        void add_entry(str, double);
        void add_entry(str, int);
        void add_entry(str, str);
        void add_entry(str, std::vector<double>&);

        // method to check if certain key is 
        // already contained in input_dict
        bool has_key(str);

        // merge dictionaries with overwriting/combining rules that only
        // apply for CLASS input dictionaries
        // e.g. concatenate strings for 'output' option, take
        // more precise values for a given precision parameter (which 
        // one the more precise one is is set in the string sets
        // keep_larger_val and keep_smaller_val defined below)
        void merge_input_dicts(pybind11::dict);

        // clears all entries from input_dict
        void clear();

       // return input_dict
        pybind11::dict get_input_dict();

      private:
        pybind11::dict input_dict;

        // string lists containing the input parameters for
        // CLASS that are more precise when they take
        // larger/smaller values.
        // These are used to decide wether to keep the smaller/
        // larger value when merging two CLASS input dictionaries
        // containing the same parameter. Hard-coded -- add to these
        // lists if you want to use a parameter that is not implemented yet.
        std::set<std::string> keep_larger_val { "l_max_scalars", "l_max_tensors", "l_max_vectors", "l_max_lss", "z_max_pk","selection_sampling_bessel", "P_k_max_h/Mpc", "P_k_max_1/Mpc" };
        std::set<std::string> keep_smaller_val { "l_logstep", "l_linstep", "l_switch_limber", "l_switch_limber_for_cl_density_over_z"};
    };

  }

#endif // end of HAVE_PYBIND11 bracket

#endif // defined __classy_types_hpp__
