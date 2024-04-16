//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Declarations of container classes
///  for the MontePythonLike backend.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Janina Renk
///          (janina.renk@fysik.su.se)
///  \date 2019 Jun
///
///  \author Pat Scott
///          (pat.scott@uq.edu.au)
///  \date 2020 Apr
///
///  *********************************************

#ifndef __MontePythonLike_types_hpp__
#define __MontePythonLike_types_hpp__

#include "gambit/cmake/cmake_variables.hpp"
#include "gambit/Backends/python_helpers.hpp"

#ifdef HAVE_PYBIND11

  #include "gambit/Utils/begin_ignore_warnings_pybind11.hpp"
  #include <pybind11/pybind11.h>
  #include <pybind11/stl_bind.h>
  #include "gambit/Utils/end_ignore_warnings.hpp"

  namespace Gambit
  {

    /// Class holding MPLike data structure & map with initialised Likelihoods objects; this is
    /// separated form the Classy_cosmo_container since it needs to be initialised as 'static const'
    /// such that the initialisation and reading in of data only happens once.
    /// This is essential since the parsing of the data at initialisation of a Likelihood object can take
    /// much longer than the actual Likelihood calculation.
    class MPLike_data_container
    {
      public:

        MPLike_data_container() {}
        MPLike_data_container(pybind11::object &data_in, map_str_pyobj likelihoods_in): data(data_in), likelihoods(likelihoods_in){}

        /// MPLike data structure
        pybind11::object data;

        /// Map likelihood name to initialised MPLike likelihood object
        map_str_pyobj likelihoods;
    };

  }

#endif // end of HAVE_PYBIND11 bracket

#endif // defined __MontePythonLike_types_hpp__
