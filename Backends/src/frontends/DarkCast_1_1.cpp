//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend for DarkCast 1.1 backend
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Quan Huynh
///          (qhuy0003@student.monash.edu)
///  \date 2022 Apr
///
///  *********************************************

#include <cstring>

#include "gambit/Backends/frontend_macros.hpp"
#include "gambit/Backends/frontends/DarkCast_1_1.hpp"

BE_INI_FUNCTION{}
END_BE_INI_FUNCTION

#ifdef HAVE_PYBIND11

  #include "gambit/Utils/begin_ignore_warnings_pybind11.hpp"
  #include <pybind11/stl.h>
  #include <pybind11/stl_bind.h>
  #include <pybind11/functional.h>
  #include <pybind11/embed.h>
  #include "gambit/Utils/end_ignore_warnings.hpp"

  BE_NAMESPACE
  {
    namespace py = pybind11;

    static py::object dark_photon;
    static bool object_initialised;

    //Initialise and store the dark_photon instance
    void dark_photon_ini()
    {
      std::string model_name = "dark_photon";
      dark_photon = DarkCast.attr("Model")(model_name);
      object_initialised = true;
    }

    //For a single final state
    double dark_photon_decay_width(double& k, std::string state, double& mass)
    {
      if (!object_initialised)
      {
        dark_photon_ini();
      }

      double width = dark_photon.attr("width")(state, mass, k).cast<double>();
      return width;
    }

    double dark_photon_branching_fraction(std::string state, double& mass)
    {
      if (!object_initialised)
      {
        dark_photon_ini();
      }

      double bfrac = dark_photon.attr("bfrac")(state, mass).cast<double>();
      return bfrac;
    }

    //For a combination of final states. Take a vector of string input, eg: std::vector<std::string> ("e_e","u_u","d_d")
    double dark_photon_decay_width_multi(double& k, std::vector<std::string> states, double& mass)
    {
      if (!object_initialised)
      {
        dark_photon_ini();
      }

      double width = dark_photon.attr("width")(states, mass, k).cast<double>();
      return width;
    }

    double dark_photon_branching_fraction_multi(std::vector<std::string> states, double& mass)
    {
      if (!object_initialised)
      {
        dark_photon_ini();
      }

      double bfrac = dark_photon.attr("bfrac")(states, mass).cast<double>();
      return bfrac;
    }
  }
  END_BE_NAMESPACE

#endif

