//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  CosmoBit routines relating to setting input parameters
///    for the Boltzmann solvers.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Selim C. Hotinli
///          (selim.hotinli14@pimperial.ac.uk)
///  \date 2017 Jul
///  \date 2018 May
///  \date 2018 Aug - Sep
///
///  \author Patrick Stoecker
///          (stoecker@physik.rwth-aachen.de)
///  \date 2017 Nov
///  \date 2018 Jan - May
///  \date 2019 Jan, Feb, June, Nov
///
///  \author Janina Renk
///          (janina.renk@fysik.su.se)
///  \date 2018 June
///  \date 2019 Mar,June
///  \date 2020 July
///
///  \author Sanjay Bloor
///          (sanjay.bloor12@imperial.ac.uk)
///  \date 2019 June, Nov
///
///  \author Sebastian Hoof
///          (hoof@uni-goettingen.de)
///  \date 2020 Mar
///
///  \author Pat Scott
///          (pat.scott@uq.edu.au)
///  \date 2018 Mar
///  \date 2019 Jul
///  \date 2020 Apr
///
///  *********************************************

#include <boost/algorithm/string/trim.hpp>

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/CosmoBit/CosmoBit_rollcall.hpp"
#include "gambit/CosmoBit/CosmoBit_types.hpp"


namespace Gambit
{

  namespace CosmoBit
  {

    using namespace LogTags;

    #ifdef HAVE_PYBIND11

      /*****************/
      /* Classy inputs */
      /*****************/

      /// Create a Python dictionary with the inputs that have to be passed to class.
      /// Setting parameters related to (massive) neutrinos & non-CDM components.
      void set_classy_NuMasses_Nur_input(pybind11::dict &result)
      {
        using namespace Pipes::set_classy_NuMasses_Nur_input;

        // Make sure dict is empty
        result.clear();

        // Set number of ultra relativistic species
        result["N_ur"] = *Dep::N_ur;

        // Get the neutrino masses
        // The units of StandardModel_SLHA2 are GeV; here we are using eV.
        std::vector<double> nuMasses{
          1e9*(*Param["mNu1"]), 1e9*(*Param["mNu2"]), 1e9*(*Param["mNu3"])
        };

        // Count the nonzero entries
        auto isNonZero = [](double i) {return i > 0.;};
        int N_ncdm = std::count_if(nuMasses.begin(), nuMasses.end(), isNonZero);

        // if nonzero, a mass & temperature for each species has to be
        // passed to class
        if (N_ncdm > 0.)
        {
          result["N_ncdm"] = N_ncdm;

          std::vector<double> m_ncdm(N_ncdm);
          std::copy_if(nuMasses.begin(), nuMasses.end(), m_ncdm.begin(), isNonZero);

          // NOTE: this explicitly assumed that all non-CDM components have the same temperature!
          std::vector<double> T_ncdm(N_ncdm,*Dep::T_ncdm);

          // Create one string with m_ncdm masses and
          // T_ncdm temperatures, separated by commas.
          // This matches the input format of CLASS.
          std::ostringstream ss1, ss2;
          std::string separator;
          for (auto x : m_ncdm)
          {
            ss1 << separator << x;
            separator = ",";
          }
          separator = "";
          for (auto x : T_ncdm)
          {
            ss2 << separator << x;
            separator = ",";
          }

          result["m_ncdm"] = ss1.str();
          result["T_ncdm"] = ss2.str();
        }
      }

      /// Set the classy parameters for an LCDM run with a parametrised primordial power spectrum.
      void set_classy_parameters_parametrised_ps(pybind11::dict& result)
      {
        using namespace Pipes::set_classy_parameters_parametrised_ps;

        // Clean the input container
        result.clear();

        // Now need to pass the primordial power spectrum
        result["n_s"] = *Param["n_s"];
        result["ln10^{10}A_s"] = *Param["ln10A_s"];

        // Pass pivot scale of external spectrum to CLASS
        result["P_k_ini type"] = "analytic_Pk";
        result["k_pivot"] = *Dep::k_pivot;

        // If r = 0 only compute scalar modes, else tensor modes as well
        //
        // => Don't explicitly set "modes" to 's' since it defaults to it. If you set it here anyways
        // you won't be able to run CLASS when only requesting background quantities (e.g. for BAO & SNe likelihoods)
        // as the perturbations module won't run and therefore the entry "modes" won't be read.
        if(*Param["r"] == 0){}
        else
        {
          // Don't set 'r' to zero in CLASS dictionary, as it won't be read if no tensor modes are requested
          result["r"] = *Param["r"];
          result["modes"] = "t,s";
        }

        // Set helium abundance
        result["YHe"] = *Dep::helium_abundance;
      }

      /// Set the classy parameters for an LCDM run with an explicit non-parametric primordial power spectrum.
      void set_classy_parameters_primordial_ps(pybind11::dict& result)
      {
        using namespace Pipes::set_classy_parameters_primordial_ps;

        // Clean the input container
        result.clear();

        // Now need to pass the primordial power spectrum
        static Primordial_ps pps{};
        pps = *Dep::primordial_power_spectrum;
        result["modes"] = "t,s";
        result["P_k_ini type"] = "pointer_to_Pk";
        result["k_array"] = memaddress_to_uint(pps.get_k().data());
        result["pks_array"] = memaddress_to_uint(pps.get_P_s().data());
        result["pkt_array"] = memaddress_to_uint(pps.get_P_t().data());
        result["lnk_size" ] = pps.get_vec_size(); // makes this consistent with multimodecode (rather than hardcoding it)

        // Pass pivot scale of external spectrum to CLASS
        result["k_pivot"] = *Dep::k_pivot;

        // Set helium abundance
        result["YHe"] = *Dep::helium_abundance;
      }

      /// Create a Python dictionary with the standard inputs that have to be passed
      /// to CLASS: cosmological parameters ([H0/100*theta_s],omega_b,tau_reio,omega_cdm) & add
      /// model-dependent results for N_ur, neutrino masses & helium abundance.
      /// Also read in any extra input options from the YAML file to pass to CLASS.
      void set_classy_input_params(Classy_input &result)
      {
        using namespace Pipes::set_classy_input_params;

        if (ModelInUse("LCDM") and ModelInUse("LCDM_theta"))
        {
          CosmoBit_error().raise(LOCAL_INFO, "You have requested to scan both LCDM and LCDM_theta.\n"
                                             "This is not allowed. Please select one in your YAML file.");
        }

        // Make sure dict is empty
        result.clear();

        // Keep track if it is the first run: if so, perform some
        // extra consistency checks to make sure no contradicting
        // values are in the classy python input dictionary.
        static bool first_run = true;

        // Get the dictionary with inputs for the neutrino masses and merge it
        // into Classy_Input dictionary
        result.merge_input_dicts(*Dep::classy_MPLike_input);
        result.merge_input_dicts(*Dep::classy_NuMasses_Nur_input);
        result.merge_input_dicts(*Dep::classy_primordial_input);

        // Standard cosmological parameters (common to all CDM-like models)
        result.add_entry("T_cmb"      , *Param["T_cmb"]);
        result.add_entry("omega_b"    , *Param["omega_b"]);
        result.add_entry("tau_reio"   , *Param["tau_reio"]);
        result.add_entry("omega_cdm"  , *Param["omega_cdm"]);

        // Depending on parametrisation, pass either Hubble or the acoustic scale
        if (ModelInUse("LCDM")) result.add_entry("H0", *Param["H0"]);
        else result.add_entry("100*theta_s", *Param["100theta_s"]);

        // add energy-injection-related CLASS input parameters
        // Note: if one of the models below is in use, an "exo" version of CLASS needs
        // to be used. Otherwise the features for energy injection are not available.
        // To ensure this, there is a check in the classy frontends that cannot
        // handle energy injection. In that case, a fatal error is thrown and
        // the user is told to use exoCLASS (and how to install it).
        if (ModelInUse("DecayingDM_general") || ModelInUse("AnnihilatingDM_general"))
        {
          // Add decaying/annihilating DM-specific options to Python dictionary passed to CLASS (consistency checks only executed in first run).
          result.merge_input_dicts(*Dep::classy_parameters_EnergyInjection);
        }

        // Other CLASS input direct from the YAML file.
        // Check if these are already contained in the input dictionary -- if so throw an error.
        // Only do this for the first run...
        static pybind11::dict yaml_input;
        if(first_run)
        {
          YAML::Node classy_dict;
          if (runOptions->hasKey("classy_dict"))
          {
            classy_dict = runOptions->getValue<YAML::Node>("classy_dict");
            for (auto it=classy_dict.begin(); it != classy_dict.end(); it++)
            {
              std::string name = it->first.as<std::string>();
              std::string value = it->second.as<std::string>();
              // Check if the key exists in the dictionary
              if (not result.has_key(name.c_str()))
              {
                yaml_input[name.c_str()] = value;
              }
              // If it does, throw an error, there's some YAML conflict going on.
              else
              {
                CosmoBit_error().raise(LOCAL_INFO, "The key '" + name + "' already "
                  "exists in the CLASSY dictionary. You are probably trying to override a model parameter. If you really"
                  "want to do this you should define an extra function to set the class parameters for the model you "
                  "are considering.");
              }
            }
            // Make sure that user did not try to pass k_pivot, N_star or P_k_ini type through class dictionary.
            // These are fixed by capabilities to ensure consistent use throughout the code
            if (yaml_input.contains("k_pivot") || yaml_input.contains("N_star"))
            {
              CosmoBit_error().raise(LOCAL_INFO,
                    "You tried to pass 'k_pivot' and/or 'N_star' to CLASS. These values must \n"
                    "be set consistently throughout the code. N_pivot is set automatically\n"
                    "by the assumption of instant reheating, or as an explicit model parameter.\n"
                    "k_pivot can be set by adding\n "
                    "  - capability: k_pivot\n    function: set_k_pivot\n    options:\n"
                    "      k_pivot: 0.02\n"
                    "to the Rules section of your YAML file.");
            }
            if (yaml_input.contains("P_k_ini type"))
            {
              CosmoBit_error().raise(LOCAL_INFO,
                "GAMBIT will take care of setting all CLASS inputs regarding the primordial power spectrum consistently.\n"
                "Please remove the option 'P_k_ini type' for the capability 'classy_baseline_params'.");
            }
          }
        // Only want to do the gnarly stuff once!
        first_run = false;
        }

        // Add YAML options to python dictionary passed to CLASS; consistency checks only executed on first run
        result.merge_input_dicts(yaml_input);

        // If the Planck likelihood is used, add the following relevant input parameters to the CLASS dictionary:
        // - output: 'lCl, pCl, tCl'
        // - lensing: yes
        // - non linear: halofit
        // - l_max_scalars: 2508

        // NOTE: this if performed *after* the YAML options are read in, since it would trigger an error of duplicated
        // keys in the event the user specifies one of the options themselves. The 'merge_input_dicts' routine will properly
        // deal with concatenating the output values and choosing the maximum passed value for l_max_scalars. Contradictions
        // in the lensing or non-linear choice will rightfully trigger an error.
        if (ModelInUse("cosmo_nuisance_Planck_lite") || ModelInUse("cosmo_nuisance_Planck_TTTEEE") || ModelInUse("cosmo_nuisance_Planck_TT"))
        {
          // add Planck-likelihood-specific options to python dictionary passed to CLASS; consistency checks only executed on first run
          result.merge_input_dicts(*Dep::classy_PlanckLike_input);
        }


      }

      /// Initialises the container within CosmoBit from classy. This holds
      /// an instance of the classy class Class() (Yep, I know...)
      /// which can be handed over to MontePython, or just used to compute
      /// some observables.
      void set_classy_input_no_MPLike(pybind11::dict& result)
      {
        using namespace Pipes::set_classy_input_no_MPLike;

        // Make sure nobody is trying to use MP downstream (prevents segfaults).
        if (Downstream::neededFor("MP_LogLikes"))
        {
          std::ostringstream ss;
          ss << "Sorry, you cannot use the function CosmoBit::set_classy_input with MontePython." << endl
             << "Please modify the Rules section of your YAML file to instead point to the function" << endl
             << "CosmoBit::set_classy_input_with_MPLike. An appropriate rule would look like this:" << endl << endl
             << "  - capability: classy_final_input" << endl
             << "    function: set_classy_input_with_MPLike" << endl;
          CosmoBit_error().raise(LOCAL_INFO, ss.str());
        }

        // If the above check passes, nothing to do here.
        pybind11::dict r;
        result = r;
      }

      /// Initialises the container within CosmoBit from classy, but designed specifically
      /// to be used when MontePython is in use. This will ensure additional outputs are
      /// computed by classy CLASS to be passed to MontePython:
      /// When initialising the MontePython Likelihood objects they add the output that needs to be computed by class
      /// to the input dictionary. We need to get these before starting the class run
      /// e.g. for Planck_SZ likelihood the entries {'output': ' mPk ', 'P_k_max_h/Mpc': '1.'} need to be added
      /// to compute all needed observables, these entries are collected here.
      void set_classy_input_with_MPLike(pybind11::dict& result)
      {
        using namespace Pipes::set_classy_input_with_MPLike;
        static bool first = true;

        // Only do this this first time through, and if something actually needs info from MP downstream
        if (first and Downstream::neededFor("MP_LogLikes"))
        {
          // Get extra cosmo_arguments from MP (gives a dictionary with output values that need
          // to be set for the class run)
          pybind11::dict tmp_dict = std::get<0>(*Dep::MP_objects).attr("cosmo_arguments");
          // Stringify all values in the dictionary and strip off leading and trailing whitespaces
          for (auto it: tmp_dict)
          {
            std::string key = (pybind11::str(it.first)).cast<std::string>();
            std::string val = (pybind11::str(it.second)).cast<std::string>();
            boost::algorithm::trim(val);
            result[key.c_str()] = val.c_str();
          }
          logger() << LogTags::debug << "Extra cosmo_arguments needed from MP Likelihoods: ";
          logger() << pybind11::repr(result) << EOM;
          first = false;
        }
      }

      /// Set the parameters for exoCLASS for a scenario with annihilating dark matter.
      void set_classy_parameters_EnergyInjection_AnnihilatingDM(pybind11::dict &result)
      {
        using namespace Pipes::set_classy_parameters_EnergyInjection_AnnihilatingDM;

        // Make sure nothing from previous run is contained
        result.clear();

        // Set relevant inputs for the scenario of s-wave annihilating DM
        result["DM_annihilation_cross_section"] = *Param["sigmav"];
        result["DM_annihilation_mass"] = *Param["mass"];

        // Get the results from the DarkAges tables that hold extra information to be passed to the CLASS thermodynamics structure
        static DarkAges::Energy_injection_efficiency_table fz;
        static DarkAges::Energy_injection_efficiency_table cached_fz;

        fz = *Dep::energy_injection_efficiency;
        bool f_eff_mode = fz.f_eff_mode;

        // Flag passed to CLASS to signal that the energy_deposition_function is coming from GAMBIT
        // we patched exoCLASS to accept this. An alternative way without patching would be to write the tables to disk &
        // just have CLASS read in the file. To avoid the repeated file writing & deleting we pass pointers to the vector/arrays
        // to CLASS instead
        if (f_eff_mode)
        {
          result["f_eff_type"] = "pointer_to_fz_eff";
        }
        else
        {
          result["f_eff_type"] = "pointer_to_fz_channel";
        }

        // Set the lengths of the input tables (since we are passing pointers to arrays CLASS has to know how long they are)
        result["energyinj_coef_num_lines"] = fz.redshift.size();

        // Add the pointers to arrays class needs to know about to input dictionary
        // NOTE: memory addresses are passed as strings (the Python wrapper for CLASS
        // converts every entry to a string internally so we need to do that for the
        // memory addresses, before Python casts them to something else)
        result["energyinj_coef_z"] = memaddress_to_uint(fz.redshift.data());
        if (f_eff_mode)
        {
          result["energyinj_coef_tot"] = memaddress_to_uint(fz.f_eff.data());
        }
        else
        {
          result["energyinj_coef_heat"] = memaddress_to_uint(fz.f_heat.data());
          result["energyinj_coef_lya"] = memaddress_to_uint(fz.f_lya.data());
          result["energyinj_coef_ionH"] = memaddress_to_uint(fz.f_hion.data());
          result["energyinj_coef_ionHe"] = memaddress_to_uint(fz.f_heion.data());
          result["energyinj_coef_lowE"] = memaddress_to_uint(fz.f_lowe.data());
        }

        // Check if the table has changed compared to the previous iteration.
        // If so, notify class by adding {"EnergyInjection_changed":"yes"}
        // to the dictionary.
        // The classy frontend will just look for the key - the value is not important here.
        if (fz != cached_fz)
          result["EnergyInjection_changed"] = "yes";

        // Copy fz to cache
        cached_fz = fz;

        // If "sigmav" is zero, clear the whole dictionary again
        // as no energy injection is considered.
        if (!(*Param["sigmav"] > 0.0)) result.clear();
      }

      void set_classy_parameters_EnergyInjection_AnnihilatingDM_onSpot(pybind11::dict &result)
      {
        using namespace Pipes::set_classy_parameters_EnergyInjection_AnnihilatingDM_onSpot;

        // Make sure nothing from previous run is contained
        result.clear();

        // Get the value for f_eff.
        const double f_eff = *Dep::f_eff;

        // Set relevant inputs for the scenario of s-wave annihilating DM
        // Scale "sigmav" by "f_eff" as CLASS will implicitly asume f_eff=1.
        result["DM_annihilation_cross_section"] = (*Param["sigmav"]) * f_eff;
        result["DM_annihilation_mass"] = *Param["mass"];

        // Tell CLASS to use the on-the-spot approximation;
        result["f_eff_type"] = "on_the_spot";

        // If "sigmav" or "f_eff" is zero, clear the whole dictionary again
        // as no energy injection is considered.
        if (!(*Param["sigmav"] > 0.0  && f_eff > 0.0)) result.clear();
      }

      /// Set the parameters for exoCLASS for a scenario with decaying dark matter.
      void set_classy_parameters_EnergyInjection_DecayingDM(pybind11::dict &result)
      {
        using namespace Pipes::set_classy_parameters_EnergyInjection_DecayingDM;

        // Make sure nothing from previous run is contained
        result.clear();

        // Set relevant inputs for the scenario of decaying DM
        result["DM_decay_tau"] = *Param["lifetime"];
        result["DM_decay_fraction"] = *Param["fraction"];

        // Get the results from the DarkAges tables that hold extra information to be passed to the CLASS thermodynamics structure
        static DarkAges::Energy_injection_efficiency_table fz;
        static DarkAges::Energy_injection_efficiency_table cached_fz;

        fz = *Dep::energy_injection_efficiency;
        bool f_eff_mode = fz.f_eff_mode;

        // Flag passed to CLASS to signal that the energy_deposition_function is coming from GAMBIT
        // (exoCLASS has been patched to accept this). An alternative way without patching would be
        // to write the tables to disk & just have CLASS read in the file. To avoid the repeated
        // file writing & deleting we pass pointers to the vector/arrays to CLASS instead.
        if (f_eff_mode)
        {
          result["f_eff_type"] = "pointer_to_fz_eff";
        }
        else
        {
          result["f_eff_type"] = "pointer_to_fz_channel";
        }

        // Set the lengths of the input tables (since we are passing pointers to arrays CLASS has to know how long they are)
        result["energyinj_coef_num_lines"] = fz.redshift.size();

        // Add the pointers to arrays class needs to know about to input dictionary
        // NOTE: memory addresses are passed as strings (the Python wrapper for CLASS
        // converts every entry to a string internally so we need to do that for the
        // memory addresses, before Python casts them to something else)
        result["energyinj_coef_z"] = memaddress_to_uint(fz.redshift.data());
        if (f_eff_mode)
        {
          result["energyinj_coef_tot"] = memaddress_to_uint(fz.f_eff.data());
        }
        else
        {
          result["energyinj_coef_heat"] = memaddress_to_uint(fz.f_heat.data());
          result["energyinj_coef_lya"] = memaddress_to_uint(fz.f_lya.data());
          result["energyinj_coef_ionH"] = memaddress_to_uint(fz.f_hion.data());
          result["energyinj_coef_ionHe"] = memaddress_to_uint(fz.f_heion.data());
          result["energyinj_coef_lowE"] = memaddress_to_uint(fz.f_lowe.data());
        }

        // Check if the table has changed compared to the previous iteration.
        // If not, notify class by adding {"EnergyInjection_changed":"yes"}
        // to the dictionary.
        // The classy frontend will just look for the key - the value is not important here.
        if (fz != cached_fz)
          result["EnergyInjection_changed"] = "yes";

        // Copy fz to cache
        cached_fz = fz;

        // If "fraction" is zero, clear the whole dictionary again
        // as no energy injection is considered.
        if (!(*Param["fraction"] > 0.0)) result.clear();
      }

      /// Set the parameters for exoCLASS for a scenario with decaying dark matter.
      void set_classy_parameters_EnergyInjection_DecayingDM_onSpot(pybind11::dict &result)
      {
        using namespace Pipes::set_classy_parameters_EnergyInjection_DecayingDM_onSpot;

        // Make sure nothing from previous run is contained
        result.clear();

        // Get the value for f_eff.
        const double f_eff = *Dep::f_eff;

        // Set relevant inputs for the scenario of decaying DM
        // Scale "fraction" by "f_eff" as CLASS will implicitly asume f_eff=1.
        result["DM_decay_tau"] = *Param["lifetime"];
        result["DM_decay_fraction"] = (*Param["fraction"]) * f_eff;

        // Tell CLASS to use the on-the-spot approximation;
        result["f_eff_type"] = "on_the_spot";

        // If "fraction" or "f_eff" is zero, clear the whole dictionary again
        // as no energy injection is considered.
        if (!(*Param["fraction"] > 0.0  && f_eff > 0.0)) result.clear();
      }

      /// Add all inputs for CLASS needed to produce the correct output to be
      /// able to compute the Planck CMB likelihoods
      void set_classy_PlanckLike_input(pybind11::dict &result)
      {
        using namespace Pipes::set_classy_PlanckLike_input;

        // Make sure nothing from previous run is contained
        result.clear();

        static std::ostringstream output;
        static std::ostringstream l_max_scalars;

        static bool first = true;
        if(first)
        {
          int lmax = -1;
          bool needs_tCl = false;
          bool needs_pCl = false;

          // Get requirements of the loaded likelihoods in the plc backend
          BEreq::plc_required_Cl(lmax,needs_tCl,needs_pCl);

          // Prepare the classy input for "output"
          // -- The likelihoods need the lensed Cl such that lensing is required everytime
          output << "lCl";
          // -- Are additional Cl, other to Cl_phiphi, required?
          if (needs_tCl)
            output << ", tCl";
          if (needs_pCl)
            output << ", pCl";

          // Prepare the classy input for "l_max_scalars"
          l_max_scalars << lmax;

          first = false;
        }

        result["lensing"] = "yes";
        result["non linear"] = "halofit";
        result["output"] = output.str();
        result["l_max_scalars"] = l_max_scalars.str();
      }

  #endif

  } // namespace CosmoBit

} // namespace Gambit
