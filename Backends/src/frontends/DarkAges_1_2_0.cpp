//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend for DarkAges 1.2.0 backend
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Patrick Stoecker
///          (stoecker@physik.rwth-aachen.de)
///  \date 2019 Oct, Nov
///  \date 2020 Jan
///
///  *********************************************

#include "gambit/Backends/frontend_macros.hpp"
#include "gambit/Backends/frontends/DarkAges_1_2_0.hpp"

#include "gambit/Utils/numerical_constants.hpp"

#include <algorithm>

#ifdef HAVE_PYBIND11

  // Convenience functions (definitions)
  BE_NAMESPACE
  {
    // Make life convenient
    using Backends::cast_std_to_np;
    using Backends::cast_np_to_std;

    namespace py = pybind11;

    template<typename T = double>
    using pyArray = typename py::array_t<T>;
    using pyArray_dbl = pyArray<>;

    // Static variables
    static bool hasAnnihilation = false;
    static bool hasDecay = false;
    static bool f_eff_mode;

    static size_t z_size;
    static double zmax;

    static py::module DA;
    static py::module DA_model;

    static pyArray_dbl redshift;
    static std::map<std::string, py::object> transfer_functions;
    static std::map<std::string, pyArray_dbl> result_map;

    // Convenience function to add given values to the front and the back of a numpy array
    inline pyArray_dbl push_to_front_and_back(pyArray_dbl input, double front, double back)
    {
      return Backends::merge(front, Backends::merge(input, back));
    }

    // Convenience function to repeat the front and the back of a numpy array.
    inline pyArray_dbl repeat_front_and_back(pyArray_dbl input)
    {
      size_t len = input.size();
      double front = (input.attr("__getitem__")(0)).cast<double>();
      double back = (input.attr("__getitem__")(len-1)).cast<double>();

      return push_to_front_and_back(input,front,back);
    }

    // Main routine of DarkAges
    // Calculates the f(z) table for a given injection spectrum, mass, and lifetime
    // (For annihilating DM, lifetime has a dummy value and will not be used)
    void calc_f(DarkAges::Energy_injection_spectrum spec, double mass, double lifetime)
    {
      // This is nothing else than 'import numpy as np'
      static py::module np = py::module::import("numpy");

      // Define lambdas to transform the input spectrum
      static auto transform_spectrum = [](double& x){x *= 1e-9;};
      static auto transform_energy = [](double& x){x = log10(1e9*x);};
      static auto isNonZero = [](double& x){return abs(x) > 0;};

      // Transform E (in GeV) to log10E (E in eV)
      std::for_each(spec.E_el.begin(), spec.E_el.end(), transform_energy);
      std::for_each(spec.E_ph.begin(), spec.E_ph.end(), transform_energy);

      // Transform dN/dE from 1/GeV to 1/eV
      std::for_each(spec.spec_el.begin(), spec.spec_el.end(), transform_spectrum);
      std::for_each(spec.spec_ph.begin(), spec.spec_ph.end(), transform_spectrum);

      // Do we have electrons/postitrons?
      bool hasElectrons = std::any_of(spec.spec_el.begin(), spec.spec_el.end(), isNonZero);
      // Do we have photons?
      bool hasPhotons = std::any_of(spec.spec_ph.begin(), spec.spec_ph.end(), isNonZero);

      // Cast the STL vectors into numpy arrays
      pyArray_dbl logE_el = cast_std_to_np(spec.E_el);
      pyArray_dbl spec_el = cast_std_to_np(spec.spec_el);
      pyArray_dbl null_el = np.attr("zeros_like")(spec_el);
      pyArray_dbl logE_ph = cast_std_to_np(spec.E_ph);
      pyArray_dbl spec_ph = cast_std_to_np(spec.spec_ph);
      pyArray_dbl null_ph = np.attr("zeros_like")(spec_ph);

      // Shift the mass from GeV to eV
      mass *= 1.e9;
      const double me_eV = 1.e9 * m_electron;

      // Initialise the appropriate "model"
      // Electrons/positrons and photons are treated separately
      static py::object model_el;
      static py::object model_ph;
      if (hasAnnihilation)
      {
        py::object mod = DA_model.attr("annihilating_model");
        model_el = mod(spec_el, null_el, null_el,
                       mass-me_eV, logE_el, redshift,
                       py::arg("normalize_spectrum_by") = "mass");
        model_ph = mod(null_ph, spec_ph, null_ph,
                       mass, logE_ph, redshift,
                       py::arg("normalize_spectrum_by") = "mass");
      }
      else if (hasDecay)
      {
        py::object mod = DA_model.attr("decaying_model");
        model_el = mod(spec_el, null_el, null_el,
                       mass-2*me_eV, lifetime, logE_el, redshift,
                       py::arg("normalize_spectrum_by") = "mass");
        model_ph = mod(null_ph, spec_ph, null_ph,
                       mass, lifetime, logE_ph, redshift,
                       py::arg("normalize_spectrum_by") = "mass");
      }

      // Loop through all transfer functions and calculate f_c(z)
      // and add it to result_map
      for (auto const& it : transfer_functions)
      {
        std::string channel = it.first;
        py::object tf = it.second;
        pyArray_dbl f = np.attr("zeros_like")(redshift);
        if (hasElectrons)
          f = f.attr("__add__")((model_el.attr("calc_f")(tf)).attr("__getitem__")(-1));
        if (hasPhotons)
          f = f.attr("__add__")((model_ph.attr("calc_f")(tf)).attr("__getitem__")(-1));
        result_map[channel] = repeat_front_and_back(f);
      }

      // Add redshift to result_map
      // (Shift entries by one to get z and not z+1)
      pyArray_dbl z(z_size,redshift.data());
      std::for_each(z.mutable_data(), z.mutable_data()+z.size(), [](double& x){x -= 1;});
      result_map["redshift"] =  push_to_front_and_back(z,0,zmax);

      // And we are done
    }

    DarkAges::Energy_injection_efficiency_table get_energy_injection_efficiency_table()
    {
      DarkAges::Energy_injection_efficiency_table result{};

      // lambda to safely check if requested column is in result_map
      auto safe_retrieve = [](const str& key) -> std::vector<double>
      {
        if (result_map.count(key) != 0)
        {
          return cast_np_to_std(result_map[key]);
        }
        else
        {
          std::ostringstream errMssg;
          errMssg << "Could not successfully gather the results ";
          errMssg << "of DarkAges_v"<< STRINGIFY(VERSION)<<".\n";
          errMssg << "The key -> " << key << " <- is not in \'result map\'.";
          backend_error().raise(LOCAL_INFO,errMssg.str());

          // This will never be returned, but the compiler keeps quiet
          return std::vector<double>{};
         }
      };

      // Fill the effiency table with all calculated columns
      result.f_eff_mode = f_eff_mode;

      result.redshift = safe_retrieve("redshift");

      if (f_eff_mode)
      {
        result.f_eff = safe_retrieve("effective");
      }
      else
      {
        result.f_heat = safe_retrieve("Heat");
        result.f_lya = safe_retrieve("Ly-A");
        result.f_hion = safe_retrieve("H-Ion");
        result.f_heion = safe_retrieve("He-Ion");
        result.f_lowe = safe_retrieve("LowE");
      }

      return result;
    }
  }
  END_BE_NAMESPACE

#endif

// Initialisation function (definition)
BE_INI_FUNCTION
{

  #ifdef HAVE_PYBIND11

    static bool first_point = true;
    static bool print_table = false;

    // Cache the Inputs
    static DarkAges::Energy_injection_spectrum cached_spec{};
    static double cached_mass{};
    static double cached_lifetime{};

    // Enter this scope only for the first point
    if (first_point)
    {
      first_point = false;

      // Check if annihilating DM or decaying DM are considered.
      // If both is considered, raise an error.
      // The BE_ALLOW_MODELS-macro in the frontend header ensures that
      // hasAnnihilation and hasDecay cannot be false at the same time.
      hasAnnihilation = ModelInUse("AnnihilatingDM_general");
      hasDecay = ModelInUse("DecayingDM_general");
      if (hasAnnihilation && hasDecay)
      {
        std::ostringstream errMssg;
        errMssg << "You asked for a combined scenario of decaying DM and annihilating DM. ";
        errMssg << "The current version of DarkAges (v"<< STRINGIFY(VERSION)<<") cannot handle this.\n";
        errMssg << "Please consider only one scenario exclusively.";
        backend_error().raise(LOCAL_INFO,errMssg.str());
      }

      // Save the submodule "model" (for later)
      DA = Gambit::Backends::DarkAges_1_2_0::DarkAges;
      std::string module_name = DA.attr("__name__").cast<std::string>();
      DA_model = py::module::import( (module_name + ".model").c_str() );

      // Get redshift array (z+1) and its size
      redshift = DA.attr("get_redshift")();
      z_size = redshift.size();

      // Should the f(z) be printed (for debugging)
      print_table = runOptions->getValueOrDef<bool>(false,"print_table");

      // What is the execution mode today?
      f_eff_mode = runOptions->getValueOrDef<bool>(false,"f_eff_mode");

      // If the capability 'f_eff' depends on the functionality of this
      // backend, "f_eff_mode" must be set to true.
      // If this is not the case, throw an error and tell the user how to fix it.
      if (Downstream::neededFor("f_eff") && !f_eff_mode)
      {
        std::ostringstream errMssg;
        errMssg << "An error occured in DarkAges_" << STRINGIFY(SAFE_VERSION) << "_init:\n\n";
        errMssg << "The capability \'f_eff\' will depend on the energy injection efficiency table ";
        errMssg << "provided by this backend and assumes that the option \'f_eff_mode\' is set to \'true\' ";
        errMssg << "but this option is currently set to \'false\' (which is the default value of this option) ";
        errMssg << "such that \'f_eff\' cannot work properly.\n\n";
        errMssg << "In order to proceed, please consider to set this option to \'true\' via the ";
        errMssg << "following rule in the yaml file of the scan:\n\n";
        errMssg << "  - capability: DarkAges_" << STRINGIFY(SAFE_VERSION) << "_init\n";
        errMssg << "    options:\n";
        errMssg << "      f_eff_mode: true\n";
        backend_error().raise(LOCAL_INFO, errMssg.str());
      }

      // Depending on the execution mode, collect the relevant transfer functions.
      if (f_eff_mode)
      {
        py::object tf_vec = DA.attr("transfer_functions");
        py::object tf_corr = DA.attr("transfer_functions_corr");

        py::object tf_eff = tf_vec.attr("sum")();
        tf_eff = tf_eff.attr("__sub__")(tf_corr);
        transfer_functions["effective"] = tf_eff;
      }
      else
      {
        map_str_int channel_map = DA.attr("channel_dict").cast<map_str_int>();
        for (auto const& it: channel_map)
        {
          std::string channel = it.first;
          int idx = it.second;
          py::object tf = DA.attr("transfer_functions").attr("__getitem__")(idx);
          transfer_functions[channel] = tf;
        }
      }

      // How far (in redshift) should the table be extended?
      zmax = runOptions->getValueOrDef<double>(1e7,"z_max");
    }

    // Get the injected spectrum
    DarkAges::Energy_injection_spectrum spec = *Dep::energy_injection_spectrum;

    // Get the remaining inputs depneding on the scenario (decay / annihilation)
    double mass{};
    double lifetime{};
    if (hasDecay)
    {
      mass = *Param["mass"];
      lifetime = *Param["lifetime"];
    }
    else if (hasAnnihilation)
    {
      mass = *Param["mass"];
      lifetime  = -1.0; // This input will be ignored anyway if hasAnnihilation is true
    }

    // Only calculate when the inputs changed, skip it otherwise
    if ( spec == cached_spec && mass == cached_mass && lifetime == cached_lifetime )
    {
      logger().send("Message from \'DarkAges_1.2.0_ini\'. Skipped \'calc_f\' as the inputs have not changed.",LogTags::info);
    }
    else
    {
      logger().send("Message from \'DarkAges_1.2.0_ini\'. Starting \'calc_f\'.",LogTags::info);

      // Reset results from previous point
      result_map.clear();

      calc_f(spec,mass,lifetime);

      // Update the cache
      cached_spec = spec;
      cached_mass = mass;
      cached_lifetime = lifetime;

      logger().send("Message from \'DarkAges_1.2.0_ini\'. Finished \'calc_f\'.",LogTags::info);
    }

    // Print the table effiency functions if asked for
    if (print_table)
    {
      std::ostringstream buff;
      buff << "---------------" << "\n";
      if (f_eff_mode)
        buff << "z\tf_eff" << "\n";
      else
        buff << "z\tf_heat\tf_lya\tf_hion\tf_heion\tf_lowe" << "\n";
      for (unsigned int i = 0; i < result_map["redshift"].size(); i++)
      {
        buff << result_map["redshift"].at(i) << "\t";
        if (f_eff_mode)
        {
          buff << result_map["effective"].at(i) << "\n";
        }
        else
        {
          buff << result_map["Heat"].at(i) << "\t";
          buff << result_map["Ly-A"].at(i) << "\t";
          buff << result_map["H-Ion"].at(i) << "\t";
          buff << result_map["He-Ion"].at(i) << "\t";
          buff << result_map["LowE"].at(i)  << "\n";
        }
      }
      buff << "---------------" << "\n";
      std::cout << buff.str();
    }

  #endif
}
END_BE_INI_FUNCTION
