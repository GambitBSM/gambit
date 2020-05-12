//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Function definitions of CosmoBit.
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
///
///  \author Sanjay Bloor
///          (sanjay.bloor12@imperial.ac.uk)
///  \date 2019 June, Nov
///        2020 May
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
#include <cmath>
#include <functional>
#include <iostream>
#include <omp.h>
#include <stdlib.h>     /* malloc, free, rand */
#include <string>
#include <valarray>
#include <memory>  // make_unique pointers
#include <stdint.h> // save memory addresses as int
#include <boost/algorithm/string/trim.hpp>

#include <gsl/gsl_blas.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_integration.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_matrix_double.h>
#include <gsl/gsl_min.h>
#include <gsl/gsl_odeiv2.h>
#include <gsl/gsl_poly.h>
#include <gsl/gsl_sf_log.h>
#include <gsl/gsl_spline.h>

#include "gambit/Utils/yaml_options.hpp"
#include "gambit/Utils/statistics.hpp"
#include "gambit/Utils/ascii_table_reader.hpp"
#include "gambit/Utils/ascii_dict_reader.hpp"
#include "gambit/Utils/numerical_constants.hpp"
#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/CosmoBit/CosmoBit_rollcall.hpp"
#include "gambit/CosmoBit/CosmoBit_types.hpp"
#include "gambit/CosmoBit/CosmoBit_utils.hpp"

/// Helper function for diagnosing MultiModeCode errors
std::string multimode_error_handling(int& err)
{

  std::string message = "MultiModeCode error: ";
  switch(err)
  {

    /// > 0 = "failure; not fatal"
    case 1:
      message = "Inflation did not start.";
      break;
    case 2:
      message = "The pivot scale didn't leave the horizon.";
      break;
    case 3:
      message = "A modes' initial conditions couldn't be set consistently.";
      break;
    case 4:
      message = "Too many e-folds; can't initialize the scale factor.";
      break;
    case 5:
      message = "Trying to save the field values at some reference N, but got less evolution than that.";
      break;
    case 6:
      message = "Didn't satisfy reheating bounds.";
      break;


    /// < 0 = "fatal"
    case -1:
      message = "Numerical underflow error in odeint.";
      break;


    // Otherwise -- who knows.
    default:
      message = "GAMBIT caught an unknown error in MultiModeCode. Check MultiModeCode output and error messages for more "
                "info (set the 'debug' switch in 'set_multimode_inputs' to '1' if you have set it to '0').";
  }
  return message;
}

namespace Gambit
{

  namespace CosmoBit
  {
    using namespace LogTags;

    void energy_injection_spectrum_AnnihilatingDM_mixture(DarkAges::Energy_injection_spectrum& spectrum)
    {
      using namespace Pipes::energy_injection_spectrum_AnnihilatingDM_mixture;

      double m = *Param["mass"];
      double BR_el = *Param["BR"];
      double BR_ph = 1.0 - BR_el;

      if (m <= m_electron && BR_el >= std::numeric_limits<double>::epsilon())
      {
        std::ostringstream err;
        err << "The mass of the annihilating dark matter candiate is below the electron mass.";
        err << " No production of e+/e- is possible.";
        CosmoBit_error().raise(LOCAL_INFO,err.str());
      }

      spectrum.E_el.clear();
      spectrum.E_ph.clear();
      spectrum.spec_el.clear();
      spectrum.spec_ph.clear();

      spectrum.E_el.resize(1,std::max(m-m_electron, std::numeric_limits<double>::min()));
      spectrum.E_ph.resize(1,m);
      spectrum.spec_el.resize(1,BR_el*2e9);
      spectrum.spec_ph.resize(1,BR_ph*2e9);
    }

    void energy_injection_spectrum_DecayingDM_mixture(DarkAges::Energy_injection_spectrum& spectrum)
    {
      using namespace Pipes::energy_injection_spectrum_DecayingDM_mixture;

      double m = *Param["mass"];
      double BR_el = *Param["BR"];
      double BR_ph = 1.0 - BR_el;

      if (m <= 2*m_electron && BR_el >= std::numeric_limits<double>::epsilon())
      {
        std::ostringstream err;
        err << "The mass of the decaying dark matter candiate is below twice the electron mass.";
        err << " No production of e+/e- is possible.";
        CosmoBit_error().raise(LOCAL_INFO,err.str());
      }

      spectrum.E_el.clear();
      spectrum.E_ph.clear();
      spectrum.spec_el.clear();
      spectrum.spec_ph.clear();

      spectrum.E_el.resize(1,std::max(m*0.5-m_electron, std::numeric_limits<double>::min()));
      spectrum.E_ph.resize(1,m*0.5);
      spectrum.spec_el.resize(1,BR_el*2e9);
      spectrum.spec_ph.resize(1,BR_ph*2e9);
    }

    void lifetime_ALP_agg(double& result)
    {
      // lifetime in s if onlz the decay a -> g g is open.
      using namespace Pipes::lifetime_ALP_agg;

      double gagg = *Param["gagg"]; // in GeV^-1
      double ma = *Param["ma0"]; // in eV

      // Calculate the decay width (in GeV)
      // (It's maybe worth being a seperate capability)
      double Gamma = 1/64./pi * pow(gagg,2) * pow(ma,3) * 1e-27;

      // For the lifetime take 1/Gamma and translate GeV^-1 into s by multiplication with "hbar"
      result = 1./Gamma * hbar;

      // Reject points which have a lifetime bigger than 1e17s (or whatever the user chooses)
      // Gets only triggered if the user wishes to do so.
      // !! This is not a real physical bound but it is more to deal with the lack of likelihoods so far. !!
      static bool do_rejection = runOptions->getValueOrDef<bool>(false,"do_rejection");
      static double tdec_max = runOptions->getValueOrDef<double>(1.0e17,"reject_tau_bigger_than");
      if (do_rejection && result > tdec_max)
      {
        std::ostringstream err;
        err << "ALP lifetime (" << result << " [s]) exceeds the threshold of " << tdec_max <<" [s].";
        invalid_point().raise(err.str());
      }
    }

    // Compute the abundance of ALPs expected from thermal production via Primakoff processes
    void minimum_abundance_ALP(double& result)
    {
      using namespace Pipes::minimum_abundance_ALP;

      double gagg = *Param["gagg"];                 // Read axion-photon coupling in GeV^-1
      double T_R_in_GeV = 1e-3 * (*Param["T_R"]);   // Read reheating temperature in MeV and convert it to GeV

      // Check for stupid input (T_R < m_e) and throw an error if the user really pushed it that far.
      if (m_electron >= T_R_in_GeV)
        CosmoBit_error().raise(LOCAL_INFO,"The reheating temperature is below the electron mass.");

      result = 1.56e-5 * pow(gagg,2) * m_planck * (T_R_in_GeV - m_electron);

    }

    // Compute the minimal fraction of dark matter in ALPs expected from thermal production via Primakoff processes
    void minimum_fraction_ALP(double& result)
    {
      using namespace Pipes::minimum_fraction_ALP;

      const double rho0_crit_by_h2 = 3.*pow(m_planck_red*1e9,2) * pow((1e5*1e9*hbar/_Mpc_SI_),2); // rho0_crit/(h^2)

      double ma0 = *Param["ma0"];                    // non-thermal ALP mass in eV
      double T = *Param["T_cmb"];                        // CMB temperature in K
      double omega_cdm = *Param["omega_cdm"];        // omega_cdm = Omega_cdm * h^2

      // Consistency check: if the ALP abundance from all thermal processes is less than that expected just from Primakoff processes, invalidate this point.
      double Ya0_min = *Dep::minimum_abundance;
      double ssm0 = entropy_density_SM(T);           // SM entropy density today in eV^3 (cf. footnote 24 of PDG2018-Astrophysical parameters)
      double rho0_cdm = omega_cdm * rho0_crit_by_h2; // rho0_cdm = Omega_cdm * rho0_crit;
      double rho0_min = Ya0_min * ma0 * ssm0;        // energy density of axions today in eV^4
      result = rho0_min / rho0_cdm;
    }

    // The fraction of dark matter in decaying ALPs at the time of production
    void DM_fraction_ALP(double& result)
    {
      using namespace Pipes::DM_fraction_ALP;

      const double t_rec = 1e12;                     // Age of the Universe at recombination in s

      double f0_thermal = *Param["f0_thermal"];      // Fraction of DM in ALPs at production, due to thermal production
      double omega_ma = *Dep::RD_oh2;                // Cosmological density of ALPs from vacuum misalignment

      double omega_cdm = *Param["omega_cdm"];        // omega_cdm = Omega_cdm * h^2
      double tau_a = *Dep::lifetime;                 // ALP lifetime in s

      // Consistency check: if the ALP abundance from all thermal processes is less than that expected just from Primakoff processes, invalidate this point.
      double f0_min = *Dep::minimum_fraction;
      if (f0_thermal < f0_min)
      {
        std::ostringstream err;
        err << "The choice of f0_thermal (" << f0_thermal;
        err << ") is in contradiction with the minimum dark matter fraction f0_min (";
        err << f0_min << ") produced via Primakoff processes.";
        invalid_point().raise(err.str());
      }

      // Compute the total fraction of DM in ALPs at production
      double xi_ini = f0_thermal + omega_ma/omega_cdm;

      // Consistency check: invalidate if there are more ALPs than dark matter at the time of recombination (t ~ 1e12s)
      double xi_at_rec = xi_ini * exp(-t_rec/tau_a );
      if (xi_at_rec  > 1.)
      {
        std::ostringstream err;
        err << "ALPs are over-abundant (n_a > n_cdm) at t = 10^12 s. (n_a/n_cdm = "<< xi_at_rec <<")";
        invalid_point().raise(err.str());
      }

      result = xi_ini;
    }

    void total_DM_abundance_ALP(double& result)
    {
      using namespace Pipes::total_DM_abundance_ALP;

      const double rho0_crit_by_h2 = 3.*pow(m_planck_red*1e9,2) * pow((1e5*1e9*hbar/_Mpc_SI_),2); // rho0_crit/(h^2)
      double omega_cdm = *Param["omega_cdm"];  // omega_cdm = Omega_cdm * h^2
      double fraction = *Dep::DM_fraction;
      double rho0_ALP = omega_cdm * fraction* rho0_crit_by_h2; // rho0_cdm = Omega_cdm * rho0_crit

      double ma0 = *Param["ma0"];
      double TCMB = *Param["T_cmb"];
      double ssm0 = entropy_density_SM(TCMB);

      result = rho0_ALP / (ma0 * ssm0);
    }

    void energy_injection_efficiency_func(DarkAges::Energy_injection_efficiency_table& result)
    {
      using namespace Pipes::energy_injection_efficiency_func;
      result = BEreq::get_energy_injection_efficiency_table();
    }

    void f_effective_func(double& result)
    {
      using namespace Pipes::f_effective_func;

      double z_eff = 0.01;
      if(ModelInUse("DecayingDM_general"))
      {
        z_eff = runOptions->getValueOrDef<double>(300.,"z_eff");
      }
      else if (ModelInUse("AnnihilatingDM_general"))
      {
        z_eff = runOptions->getValueOrDef<double>(600.,"z_eff");
      }

      DarkAges::Energy_injection_efficiency_table fzt = *Dep::energy_injection_efficiency;

      bool f_eff_mode = fzt.f_eff_mode;
      std::vector<double> z = fzt.redshift;
      std::vector<double> fh = fzt.f_heat;
      std::vector<double> fly = fzt.f_lya;
      std::vector<double> fhi = fzt.f_hion;
      std::vector<double> fhei = fzt.f_heion;
      std::vector<double> flo = fzt.f_lowe;
      std::vector<double> feff = fzt.f_eff;

      int npts = z.size();
      std::vector<double> ftot(npts);
      for (int i = 0; i < npts; i++)
      {
        if (f_eff_mode)
          ftot.at(i) = feff.at(i);
        else
          ftot.at(i) = fh.at(i) + fly.at(i) + fhi.at(i) + fhei.at(i) + flo.at(i);
      }

      gsl_interp_accel *gsl_accel_ptr = gsl_interp_accel_alloc();
      gsl_spline *spline_ptr = gsl_spline_alloc(gsl_interp_cspline, npts);

      gsl_spline_init(spline_ptr, z.data(), ftot.data(), npts);

      result = gsl_spline_eval(spline_ptr, z_eff, gsl_accel_ptr);

      gsl_spline_free(spline_ptr);
      gsl_interp_accel_free(gsl_accel_ptr);
    }

    /// Function for setting k_pivot in Mpc^-1 for consistent use within CosmoBit
    /// (to make sure it is consistent between CLASS and multimodecode)
    void set_k_pivot(double &result)
    {
      result = Pipes::set_k_pivot::runOptions->getValueOrDef<double>(0.05, "k_pivot");
    }

    void get_mNu_tot(double& result)
    {
      using namespace Pipes::get_mNu_tot;

      // The untis of StandardModel_SLHA2 are GeV; here we are using eV.
      result = 1e9 * ( *Param["mNu1"] + *Param["mNu2"] + *Param["mNu3"] );
    }

    // Returns the effective number of ultrarelativistic species today
    void get_N_ur(double& result)
    {
      using namespace Pipes::get_N_ur;

      // The untis of StandardModel_SLHA2 are GeV; here we are using eV.
      std::vector<double> nuMasses{
        1e9*(*Param["mNu1"]), 1e9*(*Param["mNu2"]), 1e9*(*Param["mNu3"])
      };

      // Count the nonzero entries
      auto isNonZero = [](double i) {return i > 0.;};
      int N_ncdm = std::count_if(nuMasses.begin(), nuMasses.end(), isNonZero);

      // Assing the result to the standard value of N_ur depending on the number of massive neutrinos.
      switch (N_ncdm)
      {
        case 1:
          result = 2.0328;  // N_ur (today) = 2.0328 for 1 massive neutrino at CMB release
          break;
        case 2:
          result = 1.0196;  // N_ur (today) = 1.0196 for 2 massive neutrino at CMB release
          break;
        case 3:
          result = 0.00641;  // N_ur (today) = 0.00641 for 3 massive neutrinos at CMB release
          break;
        case 0:
          result = 3.046;
          break;
        default:
          {
            std::ostringstream err;
            err << "You are asking for more than three massive neutrino species.\n";
            err << "Such a case is not implemented in CosmoBit. ";
            err << "If you want to consider this you can add it to the function ";
            err << "'get_N_ur' of the capability 'N_ur'.";
            CosmoBit_error().raise(LOCAL_INFO, err.str());
          }
      }

      // If "etaBBN_rBBN_rCMB_dNurBBN_dNurCMB" is in use, the result will
      // be scaled and gets extra contributions
      if (ModelInUse("etaBBN_rBBN_rCMB_dNurBBN_dNurCMB"))
      {
        // Check if the input for dNeff is negative (unphysical)
        static bool allow_negative_delta_N_ur = runOptions->getValueOrDef<bool>(false,"allow_negative_delta_N_ur");
        const ModelParameters& NP_params = *Dep::etaBBN_rBBN_rCMB_dNurBBN_dNurCMB_parameters;
        double dNurCMB =  NP_params.at("dNur_CMB");
        double rCMB =  NP_params.at("r_CMB");
        if ( (!allow_negative_delta_N_ur) && (dNurCMB < 0.0) )
        {
          std::ostringstream err;
          err << "A negative value for \"dNur_CMB\" is unphysical and is not allowed in CosmoBit by default!\n\n";
          err << "If you want to proceed with megative values, please add\n\n";
          err << "  - module: CosmoBit\n";
          err << "    options:\n";
          err << "      allow_negative_delta_N_ur: true\n\n";
          err << "to the Rules section of the yaml-file.";
          CosmoBit_error().raise(LOCAL_INFO,err.str());
        }

        // If the check is passed, set the result.
        result = pow(rCMB,4)*(result) + dNurCMB;
      }
      logger() << "N_ur calculated to be " << result << EOM;
    }

    /// create a python dictionary with the inputs that have to be passed to class
    /// setting parameters related to (massive) neutrinos & ncdm components
    void set_classy_NuMasses_Nur_input(pybind11::dict &result)
    {
      using namespace Pipes::set_classy_NuMasses_Nur_input;

      // make sure dict is empty
      result.clear();

      // set number of ultra relativistic species
      result["N_ur"] = *Dep::N_ur;

      // Get the neutrino masses
      // The untis of StandardModel_SLHA2 are GeV; here we are using eV.
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

        // head up: this explicitly assumed that all ncdm components have the same temperature!! todo ?
        std::vector<double> T_ncdm(N_ncdm,*Dep::T_ncdm);

        // create one string with m_ncdm masses and
        // T_ncdm temperatures separated by commas (to match the input
        // format of class)
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

    /// create a python dictionary with the standard inputs that have to be passed
    /// to class: cosmological parameters ([H0/100*theta_s],omega_b,tau_reio,omega_cdm) & add
    /// model dependent results for N_ur, neutrino masses & helium abundance
    /// here potential extra input options given in the yaml file are read in
    void set_classy_baseline_params(pybind11::dict &result)
    {
      using namespace Pipes::set_classy_baseline_params;

      //std::cout << " enter " << __PRETTY_FUNCTION__ << std::endl;

      if (ModelInUse("LCDM") and ModelInUse("LCDM_theta"))
      {
        CosmoBit_error().raise(LOCAL_INFO, "You have requested to scan both LCDM and LCDM_theta.\n"
                                           "This is not allowed. Please select one in your YAML file.");
      }

      // make sure dict is empty
      result.clear();

      // keep track if it is the first run -- if so
      // some extra consistency checks to make sure no contradicting
      // values are in the classy python input dictionary
      static bool first_run = true;

      // Get the dictionary with inputs for the neutrino masses and merge it
      // into the empty results dictionary.
      pybind11::dict NuMasses_In = *Dep::classy_NuMasses_Nur_input;
      merge_pybind_dicts(result, NuMasses_In, first_run);

      // standard cosmological parameters (common to all CDM -like models)
      result["T_cmb"] =         *Param["T_cmb"];
      result["omega_b"] =       *Param["omega_b"];
      result["tau_reio"] =      *Param["tau_reio"];
      result["omega_cdm"] =     *Param["omega_cdm"];

      // Depending on parametrisation, pass either Hubble or the acoustic scale
      if (ModelInUse("LCDM")) 
      {  
        result["H0"] = *Param["H0"];
      }
      else if (ModelInUse("LCDM_theta")) 
      {
        result["100*theta_s"] = *Param["100theta_s"];
      }
      else
        CosmoBit_error().raise(LOCAL_INFO, "Neither LCDM or LCDM_theta seem to be in use...\n");

      // S.B. 12/05 moved Helium abundance into separate capability to enable classy internal 
      // calculation instead, if we want.
      /*// Set helium abundance
      result["YHe"] = *Dep::helium_abundance;*/

      // TODO: need to test if class or exo_class in use! does not work -> (JR) should be fixed with classy implementation
      // -> (JR again) not sure if that is actually true.. need to test.
      if (ModelInUse("DecayingDM_general") || ModelInUse("AnnihilatingDM_general"))
      {
        // add Decaying/annihilating DM specific options to python dictionary passed to CLASS, consistency checks only executed in first run
        merge_pybind_dicts(result,*Dep::classy_parameters_EnergyInjection, first_run);
      }

      // Other Class input direct from the YAML file
      // check if these are already contained in the input dictionary -- if so throw an error
      // only do it for the first run though
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
            if (not result.contains(name.c_str()))
            {
              yaml_input[name.c_str()] = value;
            }
            // If it does, throw an error, there's some YAML conflict going on.
            else
            {
              std::cout << pybind11::repr(result) << std::endl;
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
                  "to the Rules section of your yaml file.");
          }
          if (yaml_input.contains("P_k_ini type"))
          {
            CosmoBit_error().raise(LOCAL_INFO,
              "GAMBIT will take care of setting all CLASS inputs regarding the primordial power spectrum consistently.\n"
              "Please remove the option 'P_k_ini type' for the capability 'classy_baseline_params'.");
          }
        }
      }

      // Add yaml options to python dictionary passed to CLASS; consistency checks only executed on first run
      merge_pybind_dicts(result, yaml_input, first_run);

      // At last: if the Planck likelihood is used add all relevant input parameters to the CLASS dictionary:
      // output: 'lCl, pCl, tCl', lensing: yes, non linear: halofit , l_max_scalar: 2508
      // Note: this has to be done *after* the yaml options are read it since it would trigger an error of duplicated
      //   keys in case the user specifies one of the options themselves. The 'merge_pybind_dicts' routine will properly
      //   with concatennating the output values and choosing the maximum passed value for l_max_scalars. Contradictions
      //   in the lensing or non linear choice will rightfully trigger an error.
      if (ModelInUse("cosmo_nuisance_Planck_lite") || ModelInUse("cosmo_nuisance_Planck_TTTEEE")|| ModelInUse("cosmo_nuisance_Planck_TT"))
      {
        // add Planck-likelihood-specific options to python dictionary passed to CLASS; consistency checks only executed on first run
        merge_pybind_dicts(result,*Dep::classy_PlanckLike_input, first_run);
      }

      first_run = false;
    }

    /* Treatment of Helium abundance */
    // 1. Helium abundance as a numerical input (i.e. from BBN)
    void set_classy_YHe_numerical(pybind11::dict &result)
    {
      using namespace Pipes::set_classy_YHe_numerical;
      
      // Remove all input
      result.clear();

      // Set helium abundance from the dependency, which is a numerical value,
      // e.g. from AlterBBN
      result["YHe"] = *Dep::helium_abundance;

      // Merge it with the other classy input
      merge_pybind_dicts(result, *Dep::classy_baseline_params, false);
    }

    // 2. Helium abundance computed internally within classy
    void set_classy_YHe_internal(pybind11::dict &result)
    {
      using namespace Pipes::set_classy_YHe_internal;

      // Remove all input
      result.clear();

      // Pass key "BBN" to classy, which tells it to use internal calculations
      result["YHe"] = "BBN";

      // Merge it with the other classy input
      merge_pybind_dicts(result, *Dep::classy_baseline_params, false);
    }

    /// Set the classy parameter for an LCDM run with a parameterised primordial power spectrum.
    void set_classy_parameters_parametrised_ps(Classy_input& result)
    {
      using namespace Pipes::set_classy_parameters_parametrised_ps;

      //std::cout << " enter " << __PRETTY_FUNCTION__ << std::endl;

      // Clean the input container
      result.clear();

      // Now need to pass the primordial power spectrum
      // FIXME are the units on A_s correct here or should there be another 10?
      result.add_entry("n_s", *Param["n_s"]);
      result.add_entry("ln10^{10}A_s", *Param["ln10A_s"]);

      // add k_pivot entry
      result.add_entry("P_k_ini type", "analytic_Pk");
      result.add_entry("k_pivot", *Dep::k_pivot);

      // if r = 0 only compute scalar modes, else tensor modes as well
      //
      // => don't explicitly set "modes" to 's' since it defaults to it. If you set it here anyways
      // you won't be able to run CLASS when only requesting background quantities (e.g. for BAO & SNe likelihoods)
      // as the perturbations module won't run and therefore the entry "modes" won't be read.
      if(*Param["r"] == 0){}
      else
      {
        // don't set to zero in CLASS dict as it won't be read if no tensor modes are requested
        result.add_entry("r", *Param["r"]);
        result.add_entry("modes","t,s");
      }

      // Get standard cosmo parameters, nu masses, helium abundance &
      // extra run options for class passed in yaml file to capability
      // 'classy_baseline_params'
      // Note: this should only contain a value for 'k_pivot' if the model 'LCDM'
      //    is in use.
      //pybind11::dict classy_base_dict = *Dep::classy_baseline_params;
      pybind11::dict classy_base_dict = *Dep::classy_baseline_plus_YHe;

      // Add classy_base_dict entries to the result dictionary of the type Classy_input
      std::string common_keys = result.add_dict(classy_base_dict);
      if(common_keys != "")
      {
        CosmoBit_error().raise(LOCAL_INFO, "The key(s) '" + common_keys + "' already "
                "exist in the CLASSY dictionary. You are probably trying to override a CLASS setting. Check that none "
                "of the parameters that you pass in your yaml file through RunOptions for the capability 'classy_baseline_params' "
                "is in contradiction with any settings made via the dependency resolution by CosmoBit in the function '"+__func__+"'.");
      }
    }

    /// Set the classy parameter for an LCDM run with an explicit non-parametric primordial power spectrum.
    void set_classy_parameters_primordial_ps(Classy_input& result)
    {
      using namespace Pipes::set_classy_parameters_primordial_ps;

      //std::cout << " enter " << __PRETTY_FUNCTION__ << std::endl;

      // Clean the input container
      result.clear();

      // Now need to pass the primordial power spectrum
      static Primordial_ps pps{};
      pps = *Dep::primordial_power_spectrum;
      result.add_entry("modes", "t,s");

      result.add_entry("P_k_ini type", "pointer_to_Pk");
      result.add_entry("k_array", pps.get_k());
      result.add_entry("pks_array", pps.get_P_s());
      result.add_entry("pkt_array", pps.get_P_t());
      result.add_entry("lnk_size" , pps.get_vec_size()); // don't hard code but somehow make consistent with multimode @TODO -> test
      // pass pivot scale of external spectrum to CLASS
      result.add_entry("k_pivot", *Dep::k_pivot);

      // Get standard cosmo parameters, nu masses, helium abundance &
      // extra run options for class passed in yaml file to capability
      // 'classy_baseline_params'
      // Note: this should only contain a value for 'k_pivot' if the model 'LCDM'
      //    is in use, which is not allowed in this function as the full pk
      //    is provided by an external model scanned in combination with 'LCDM_no_primordial'
      // pybind11::dict classy_base_dict = *Dep::classy_baseline_params;
      pybind11::dict classy_base_dict = *Dep::classy_baseline_plus_YHe;


      // Add classy_base_dict entries to the result dictionary of the type Classy_input
      // The string common_keys will be empty if the two dictionaries 'result'
      // and 'classy_base_dict' have no keys in common. If so 'common_keys'
      // will be a concatenation of the duplicated entries.
      std::string common_keys = result.add_dict(classy_base_dict);

      // No check if something went wrong and some parameters were defined twice
      if(common_keys != "")
      {
        CosmoBit_error().raise(LOCAL_INFO, "The key(s) '" + common_keys + "' already "
                "exists in the CLASSY dictionary. You are probably trying to override a CLASS setting. Check that none "
                "of the parameters you pass through your yaml file through RunOptions for the capability 'classy_baseline_params' "
                "is in contradiction with any settings made via the dependency resolution by CosmoBit in the function '"+__func__+"'.");
      }
    }

    // Function to set the generic inputs used for MultiModeCode (MMC).
    // N.B. Most of the available MMC parameters are already set by the default constructor of Multimode_inputs. These default
    //      values generally relate to the case of a single inflation field with instant reheating. In general, at least some of the
    //      parameters need to be adjusted for other models.
    void set_multimode_inputs(Multimode_inputs &result)
    {
      using namespace Pipes::set_multimode_inputs;

      // Clear anything from previous run
      result = Multimode_inputs();

      // Silence uncaught error messages from MMC ('0' = output, '1' = no output).
      result.silence_output = runOptions->getValueOrDef<int>(0,"silence_output");

      // Set pivot scale consistently with the rest of CosmoBit via capability
      result.k_pivot = *Dep::k_pivot;
      // Difference in k-space used when pivot-scale observables from mode equations are evaluated
      result.dlnk = runOptions->getValueOrDef<double>(0.4,"dlnk");

      // Set k-range and number of k-values (in log space) where the full power spectrum (PS) is evaluated
      // N.B. Not used if only the parameterised PS has been requested in a scan
      result.k_min = runOptions->getValueOrDef<double>(1e-6,"k_min");
      result.k_max = runOptions->getValueOrDef<double>(1e+6,"k_max");
      result.numsteps = runOptions->getValueOrDef<int>(100,"numsteps");
      if (result.numsteps > 1000) { CosmoBit_error().raise(LOCAL_INFO, "Currently MultiModeCode supports a maximum k-array size of 1000. Please change your yaml file settings."); };

      // Go through each inflation model known to GAMBIT, set the number of inflaton field, the parameters
      // for the inflation potential parameters (vparams), and initial conditions.

      // N.B. Available inflation potentials are defined in the MultiModeCode file modpk_potential.f90.
      //      If you want to study an inflation model of inflation that is not listed below, check if
      //      the model is available in modpk_potential.f90 or add it to that file before adding it here.
      if (ModelInUse("Inflation_InstReh_1mono23"))
      {
        result.vparams.push_back(log10(*Param["lambda"])); // MultiModeCode uses log10 of this parameter
        result.potential_choice = 5; // V(phi) = 1.5 lambda M_P^(10/3) phi^(2/3)
        result.vparam_rows = 1;
      }
      else if (ModelInUse("Inflation_InstReh_1linear"))
      {
        result.vparams.push_back(log10(*Param["lambda"])); // MultiModeCode uses log10 of this parameter
        result.potential_choice = 4; // V(phi) = lambda M_P^3 phi
        result.vparam_rows = 1;
      }
      else if (ModelInUse("Inflation_InstReh_1quadratic"))
      {
        result.vparams.push_back(2.0*log10(*Param["m_phi"])); // MultiModeCode uses log10 of m_phi^2
        result.potential_choice = 1; // V(phi) = 0.5 m^2 phi^2 = 0.5 m_phi^2 M_P^2 phi^2
        result.vparam_rows = 1;
      }
      else if (ModelInUse("Inflation_InstReh_1quartic"))
      {
        result.vparams.push_back(log10(*Param["lambda"])); // MultiModeCode uses log10 of this parameter
        result.potential_choice = 3; // V(phi) = 0.25 lambda phi^4
        result.vparam_rows = 1;
      }
      else if (ModelInUse("Inflation_InstReh_1natural"))
      {
        // MultiModeCode uses log10 of both parameters below
        result.vparams.push_back(log10(*Param["lambda"]));
        result.vparams.push_back(log10(*Param["f_phi"]));
        result.potential_choice = 2; // V(phi) = Lambda^4 [ 1 + cos(phi/f) ] = (lambda M_P)^4 [ 1 + cos(phi/[f_phi M_P]) ]
        result.vparam_rows = 2;
      }
      else if (ModelInUse("Inflation_InstReh_1Starobinsky"))
      {
        result.vparams.push_back(pow(*Param["lambda"],4)); // MultiModeCode uses the fourth power of Lambda as a parameter
        result.potential_choice = 19; // V(phi) = Lambda^4 [ 1 - exp(-sqrt(2/3) phi / M_P) ]^2 = (lambda M_P)^4 [ 1 - exp(-sqrt(2/3) phi / M_P) ]^2
        result.vparam_rows = 1;
      }

      static bool first_run = true;
      // do some consistency check for inputs passed to multimode before the first run
      if(first_run)
      {
        int size = result.vparams.size();
        if (result.num_inflaton*result.vparam_rows != size)
        {
          std::ostringstream err;
          err << "Error in MultiModecode settings: the number of free parameters in a inflation model";
          err << " set through the vector 'vparams' has to match (num_inflaton) x (vparam_rows). In this case the ";
          err << "length is " << result.vparams.size() << " and the product is "  << result.num_inflaton*result.vparam_rows <<  " -- double check the model dependent settings in 'get_multimode_results'";
          CosmoBit_error().raise(LOCAL_INFO, err.str());
        }
        if (result.potential_choice == -1 || result.num_inflaton == -1 || result.vparam_rows == -1)
        {
          std::ostringstream err;
          err << "Error in MultiModecode settings: you did not set one (or more) of the parameters";
          err << "'potential_choice', 'num_inflaton' or 'vparam_rows' for your inflation model. ";
          err << "Double check the model dependent settings in 'get_multimode_results'";
          CosmoBit_error().raise(LOCAL_INFO, err.str());
        }
        first_run = false;
      }
    }

    /// Use the inputs from the MultiModeCode initialisation function to compute
    /// a non-parametric primordial power spectrum.
    void get_multimode_primordial_ps(Primordial_ps &result)
    {
      using namespace Pipes::get_multimode_primordial_ps;

      // Clear it all
      result = Primordial_ps();

      // Get the inflationary inputs
      Multimode_inputs inputs = *Dep::multimode_input_parameters;

      // The parameters below are only used by multimode if the full Pk is requested.
      int steps = inputs.numsteps;
      double kmin = inputs.k_min;
      double kmax = inputs.k_max;

      gambit_inflation_observables observables;

      //-------------------------------------------------------------
      // The function below calls the MultiModeCode backend
      //  for a given choice of inflationary model,
      //  which calculates the observables.
      //-------------------------------------------------------------

      try
      {
        observables = BEreq::multimodecode_primordial_ps(inputs.num_inflaton,
                                                       inputs.potential_choice,
                                                       inputs.evaluate_modes,
                                                       inputs.get_runningofrunning,
                                                       byVal(&inputs.phi_init0[0]),
                                                       byVal(&inputs.dphi_init0[0]),
                                                       byVal(&inputs.vparams[0]),
                                                       inputs.N_pivot,
                                                       inputs.k_pivot,
                                                       inputs.dlnk,
                                                       steps,
                                                       kmin,
                                                       kmax,
                                                       inputs.vparam_rows,
                                                       inputs.slowroll_infl_end,
                                                       inputs.instreheat,
                                                       inputs.use_deltaN_SR,
                                                       inputs.use_horiz_cross_approx);
      }
      catch(std::runtime_error &e)
      {
        logger() << e.what() << EOM;
        invalid_point().raise(e.what());
      }

      // If there's an error -> pass it to the helper function and invalidate the point
      if(observables.err != 0)
      {
        std::string message = multimode_error_handling(observables.err);
        logger() << message << EOM;
        invalid_point().raise(message);
      }

      // Fill up the GAMBIT prim. PS if we're good.
      result.set_N_pivot(observables.N_pivot);
      result.fill_k(observables.k_array, inputs.numsteps);
      result.fill_P_s(observables.pks_array, inputs.numsteps);
      result.fill_P_s_iso(observables.pks_array_iso, inputs.numsteps);
      result.fill_P_t(observables.pkt_array, inputs.numsteps);

    }

    /// Use the inputs from the MultiModeCode initialisation function to compute
    /// a parameterised primordial power spectrum.
    void get_multimode_parametrised_ps(ModelParameters &result)
    {
      using namespace Pipes::get_multimode_parametrised_ps;
      gambit_inflation_observables observables;

      // Set up this ModelParameters object on first run
      static bool first = true;
      if (first)
      {
        result.setModelName("PowerLaw_ps");
        result._definePars({"ln10A_s","n_s","r","N_pivot"});
        first = false;
      }

      // Get the inflationary inputs
      Multimode_inputs inputs = *Dep::multimode_input_parameters;

      //-------------------------------------------------------------
      // The function below calls the MultiModeCode backend
      //  for a given choice of inflationary model,
      //  which calculates the observables.
      //-------------------------------------------------------------
      try
      {
        observables = BEreq::multimodecode_parametrised_ps(inputs.num_inflaton,
                                                         inputs.potential_choice,
                                                         inputs.evaluate_modes,
                                                         inputs.get_runningofrunning,
                                                         byVal(&inputs.phi_init0[0]),
                                                         byVal(&inputs.dphi_init0[0]),
                                                         byVal(&inputs.vparams[0]),
                                                         inputs.N_pivot,
                                                         inputs.k_pivot,
                                                         inputs.dlnk,
                                                         inputs.vparam_rows,
                                                         inputs.slowroll_infl_end,
                                                         inputs.instreheat,
                                                         inputs.use_deltaN_SR,
                                                         inputs.use_horiz_cross_approx);
      }
      catch(std::runtime_error &e)
      {
        logger() << e.what() << EOM;
        invalid_point().raise(e.what());
      }
      // If there's an error -> pass it to the helper function and invalidate the point
      if(observables.err != 0)
      {
        std::string message = multimode_error_handling(observables.err);
        logger() << message << EOM;
        invalid_point().raise(message);
      }

      result.setValue("N_pivot", observables.N_pivot);
      result.setValue("n_s", observables.ns);
      result.setValue("ln10A_s", 10. * log(10.) + log(observables.As) );
      result.setValue("r", observables.r);

    }


    // Getter functions for CL spectra from classy

    void class_get_unlensed_Cl_TT(std::vector<double>& result)
    {
      using namespace Pipes::class_get_unlensed_Cl_TT;
      result = BEreq::class_get_unlensed_cl("tt");

      // Loop through the TT spectrum and check if there is a negative value. If so, invalidate.
      for (auto it=result.begin(); it != result.end(); it++)
      {
        if (*it < 0.0)
        {
          invalid_point().raise("Found a negative value in the TT spectrum.");
        }
      }
    }

    void class_get_unlensed_Cl_TE(std::vector<double>& result)
    {
      using namespace Pipes::class_get_unlensed_Cl_TE;
      result = BEreq::class_get_unlensed_cl("te");
    }

    void class_get_unlensed_Cl_EE(std::vector<double>& result)
    {
      using namespace Pipes::class_get_unlensed_Cl_EE;
      result = BEreq::class_get_unlensed_cl("ee");

      // Loop through the EE spectrum and check if there is a negative value. If so, invalidate.
      for (auto it=result.begin(); it != result.end(); it++)
      {
        if (*it < 0.0)
        {
          invalid_point().raise("Found a negative value in the EE spectrum.");
        }
      }
    }

    void class_get_unlensed_Cl_BB(std::vector<double>& result)
    {
      using namespace Pipes::class_get_unlensed_Cl_BB;
      result = BEreq::class_get_unlensed_cl("bb");

      // Loop through the BB spectrum and check if there is a negative value. If so, invalidate.
      for (auto it=result.begin(); it != result.end(); it++)
      {
        if (*it < 0.0)
        {
          invalid_point().raise("Found a negative value in the BB spectrum.");
        }
      }
    }

    void class_get_unlensed_Cl_PhiPhi(std::vector<double>& result)
    {
      using namespace Pipes::class_get_unlensed_Cl_PhiPhi;
      result = BEreq::class_get_unlensed_cl("pp");

      // Loop through the PhiPhi spectrum and check if there is a negative value. If so, invalidate.
      for (auto it=result.begin(); it != result.end(); it++)
      {
        if (*it < 0.0)
        {
          invalid_point().raise("Found a negative value in the PhiPhi spectrum.");
        }
      }
    }

    void class_get_lensed_Cl_TT(std::vector<double>& result)
    {
      using namespace Pipes::class_get_lensed_Cl_TT;
      result = BEreq::class_get_lensed_cl("tt");

      // Loop through the TT spectrum and check if there is a negative value. If so, invalidate.
      for (auto it=result.begin(); it != result.end(); it++)
      {
        if (*it < 0.0)
        {
          invalid_point().raise("Found a negative value in the TT spectrum.");
        }
      }
    }

    void class_get_lensed_Cl_TE(std::vector<double>& result)
    {
      using namespace Pipes::class_get_lensed_Cl_TE;
      result = BEreq::class_get_lensed_cl("te");
    }

    void class_get_lensed_Cl_EE(std::vector<double>& result)
    {
      using namespace Pipes::class_get_lensed_Cl_EE;
      result = BEreq::class_get_lensed_cl("ee");

      // Loop through the EE spectrum and check if there is a negative value. If so, invalidate.
      for (auto it=result.begin(); it != result.end(); it++)
      {
        if (*it < 0.0)
        {
          invalid_point().raise("Found a negative value in the EE spectrum.");
        }
      }
    }

    void class_get_lensed_Cl_BB(std::vector<double>& result)
    {
      using namespace Pipes::class_get_lensed_Cl_BB;
      result = BEreq::class_get_lensed_cl("bb");

      // Loop through the BB spectrum and check if there is a negative value. If so, invalidate.
      for (auto it=result.begin(); it != result.end(); it++)
      {
        if (*it < 0.0)
        {
          invalid_point().raise("Found a negative value in the BB spectrum.");
        }
      }
    }

    void class_get_lensed_Cl_PhiPhi(std::vector<double>& result)
    {
      using namespace Pipes::class_get_lensed_Cl_PhiPhi;
      result = BEreq::class_get_lensed_cl("pp");

      // Loop through the PhiPhi spectrum and check if there is a negative value. If so, invalidate.
      for (auto it=result.begin(); it != result.end(); it++)
      {
        if (*it < 0.0)
        {
          invalid_point().raise("Found a negative value in the PhiPhi spectrum.");
        }
      }
    }

// ***************************************************************************************************************

    /// RHS of differential equation
    ///  dT/dt = 15/pi^2 (m_a n_a(t)/ tau_a) T^(-3) - H(T) T , where H(T) = 3.7978719e-7*T*T  // TODO: refer to Eq. number in paper when ready
    ///  params: stores (m_a n_a(t)/ tau_a)
    ///  y[0]: stores SM T[t0]
    int diff_eq_rhs (double t, const double y[], double f[], void *params)
    {
      fast_interpolation injection_inter = *(static_cast<fast_interpolation*>(params));
      f[0] = (15.0/(4.0*pi*pi)) * injection_inter.interp(t)/pow(y[0], 3) - 3.7978719e-7*y[0]*y[0]*y[0];
      return GSL_SUCCESS;
    }

    void compute_dNeff_etaBBN_ALP(map_str_dbl &result)  // takes about 0.2 s with 3000 grid points and 1e-6 convergence criterion atm
    {
      using namespace Pipes::compute_dNeff_etaBBN_ALP;

      double dNeff, Neff_SM, Neff_ALP, eta_ratio;
      double temp_eta_ratio = 1; // temporary values to check convergence of iteration
      double temp_dNeff = 1;
      int ii=0;

      // --- precision parameters --
      double hstart = runOptions->getValueOrDef<double>(1e-6,"hstart"); // initial step size for GSL ODE solver
      double epsrel = runOptions->getValueOrDef<double>(1e-6,"epsrel"); // desired relative accuracy for GSL ODE solver and dNeff & etaBBN
      double max_iter = runOptions->getValueOrDef<int>(10,"max_iter"); // maximum number of iterations before error message is thrown if result not converged
      double grid_size = runOptions->getValueOrDef<int>(3000,"grid_size"); // number of (logarithmic) grid points in t

      double t0 = runOptions->getValueOrDef<double>(1e4,"t_initial"); // initial time in seconds
      double tf = runOptions->getValueOrDef<double>(1e12,"t_final"); // final time in seconds

      std::valarray<double> t_grid(grid_size), T_evo(grid_size), Tnu_grid(grid_size), na_grid(grid_size), injection_grid(grid_size); // arrays containing time dependence of variables

      SM_time_evo SM(t0,tf,grid_size);  // set time evolution of SM
      t_grid = SM.get_t_grid();         // has to be updated when solving the differential equation
      T_evo = SM.get_T_evo();

      // --- model parameters ----
      double Ya0 = *Dep::total_DM_abundance;
      double T0 = T_evo[0];
      double ssm_at_T0 = entropy_density_SM(T0, true);; // T0 in units of keV, set T_in_eV=True to interpret it correctly

      double na_t0 = Ya0 * ssm_at_T0;     // initial number density of a at t=t0, in units keV^3.
      double m_a = 1e-3*(*Param["ma0"]);  // mass of a in keV
      double tau_a = *Dep::lifetime;      // lifetime of a in seconds

      // loop over iterations until convergence or max_iter is reached
      while( ((fabs(temp_eta_ratio-eta_ratio) > epsrel) || fabs(temp_dNeff - dNeff) > epsrel) && (ii <= max_iter) )
      {
        temp_eta_ratio = eta_ratio;  // to check for convergence
        temp_dNeff = dNeff;

        SM.calc_H_int();
        na_grid = na_t0*exp(-3.0*SM.get_H_int())*exp(-t_grid/tau_a);    // na(t) in units keV^3
        injection_grid = (m_a/tau_a)*na_grid;                           // m_a*na(t)/tau_a in units keV^4/s
        Tnu_grid = SM.get_Tnu_evo()[0]*exp(-1.0*SM.get_H_int());        // T_nu(t) in units keV
        fast_interpolation injection_inter(t_grid, injection_grid);     // interpolating function

        gsl_odeiv2_system sys = {diff_eq_rhs, NULL, 1, &injection_inter};
        gsl_odeiv2_driver *d = gsl_odeiv2_driver_alloc_y_new (&sys, gsl_odeiv2_step_rkf45, hstart, 0.0, epsrel);

        double y[1] = {T_evo[0]}; // initial condition: T(t0) = T_SM(t0)
        double t=t0;

        for (int jj = 0; jj < grid_size; jj++)
        {
          double t_j = t_grid[jj];
          int status = gsl_odeiv2_driver_apply (d, &t, t_j, y);
          if (status != GSL_SUCCESS)
          {
            std::ostringstream err;
            err << "Failed to solve differential equation to compute dNeffCMB and etaBB for GeneralCosmoALP model at iteration step "<< ii <<". Invalidating point";
            invalid_point().raise(err.str());
          }
          T_evo[jj] = y[0];
        }

        gsl_odeiv2_driver_free (d);

        // update Hubble rate for next iteration
        SM.set_HT_evo(T_evo);

        eta_ratio = pow(T_evo[grid_size-1]/T_evo[0], 3) * exp(3.0*SM.get_H_int()[grid_size-1]);
        Neff_ALP = 3*pow(Tnu_grid[grid_size-1]/T_evo[grid_size-1], 4) * 3.85280407965; // (11/4)^(4/3) = 3.85280407965
        Neff_SM = 3*pow(Tnu_grid[0]/T_evo[0], 4) * 3.85280407965; // (11/4)^(4/3) = 3.85280407965
        dNeff = Neff_ALP - Neff_SM;
        ii ++;
      }

      // invalidate point if results not converged after 'max_iter' steps
      if( ((fabs(temp_eta_ratio-eta_ratio) > epsrel) || fabs(temp_dNeff - dNeff) > epsrel) && (ii >= max_iter) )
      {
        std::ostringstream err;
        err << "Computation of dNeffCMB and etaBBN for GeneralCosmoALP model did not converge after n = "<< ii <<" iterations. You can increase the maximum number of iterations with the run Option 'max_iter'. Invalidating point.";
        invalid_point().raise(err.str());
      }

      result["dNeff"] = dNeff;
      result["Neff_ratio"] = Neff_ALP/Neff_SM;
      result["eta_ratio"] = eta_ratio;
      logger() << "GeneralCosmoALP model: calculated Neff @BBN to be " << result["dNeff"] <<", and etaBB(ALP)/etaBBN(SM) = " << result["eta_ratio"] << ". Calculation converged after "<< ii <<" iterations." << EOM;

    }

/// -----------
/// Capabilities for general cosmological quantities
/// -----------

    void T_ncdm_SM(double &result)
    {
      using namespace Pipes::T_ncdm_SM;

      // set to 0.71611 in units of photon temperature, above the instantaneous decoupling value (4/11)^(1/3)
      // to recover Sum_i mNu_i/omega = 93.14 eV resulting from studies of active neutrino decoupling (hep-ph/0506164)
      result = 0.71611;
      // This standard values enters in many assumption entering class. Therefore changing this value in
      // the yaml file is disabled at the moment. If you still want to modify it uncomment the line below and
      // you can set is as a run option (as T_cmb).
      // result = runOptions->getValueOrDef<double>(0.71611,"T_ncdm");
    }

    void T_ncdm(double &result)
    {
      using namespace Pipes::T_ncdm;

      double rCMB = 1.0; // Default value if no energy injection is assumed.

      // If the "etaBBN_rBBN_rCMB_dNurBBN_dNurCMB" model is included in the scan,
      // we use rCMB of this model.
      if (ModelInUse("etaBBN_rBBN_rCMB_dNurBBN_dNurCMB"))
      {
        const ModelParameters& NP_params = *Dep::etaBBN_rBBN_rCMB_dNurBBN_dNurCMB_parameters;
        rCMB = NP_params.at("r_CMB");
      }

      // Take the SM value of T_ncdm (T_nu) and multiply it with the value of rCMB
      result = rCMB*(*Dep::T_ncdm_SM);
    }

    void eta0_LCDM(double &result)
    {
      using namespace Pipes::eta0_LCDM;

      double ngamma, nb;
      ngamma = 16*pi*zeta3*pow(*Param["T_cmb"]*_kB_eV_over_K_/_hc_eVcm_,3); // photon number density today
      nb = *Param["omega_b"]*3*100*1e3*100*1e3/_Mpc_SI_/_Mpc_SI_/(8*pi*_GN_cgs_* m_proton*1e9*eV2g); // baryon number density today

      result =  nb/ngamma;
      logger() << "Baryon to photon ratio (eta) today computed to be " << result << EOM;
    }

    void etaBBN_SM(double& result)
    {
      using namespace Pipes::etaBBN_SM;

      result = *Dep::eta0;
    }

    void compute_Omega0_m(double &result)
    {
      using namespace Pipes::compute_Omega0_m;

      result =(*Dep::Omega0_b) + (*Dep::Omega0_cdm) + (*Dep::Omega0_ncdm);
    }

    void compute_Omega0_b(double &result)
    {
      using namespace Pipes::compute_Omega0_b;

      double h = *Dep::H0/100.;
      result =*Param["omega_b"]/h/h;
    }

    void compute_Omega0_cdm(double &result)
    {
      using namespace Pipes::compute_Omega0_cdm;

      double h = *Dep::H0/100.;
      result =*Param["omega_cdm"]/h/h;
    }

    void compute_Omega0_g(double &result)
    {
      using namespace Pipes::compute_Omega0_g;

      double h = *Dep::H0/100.;
      result = (4.*_sigmaB_SI_/_c_SI_*pow(*Param["T_cmb"],4.)) / (3.*_c_SI_*_c_SI_*1.e10*h*h/_Mpc_SI_/_Mpc_SI_/8./pi/_GN_SI_);
    }

    void compute_n0_g(double &result)
    {
      using namespace Pipes::compute_n0_g;

      result = 2./pi/pi*zeta3 *pow(*Param["T_cmb"]*_kB_eV_over_K_,3.)/pow(_hP_eVs_*_c_SI_/2./pi,3)/100/100/100; // result per cm^3
    }

    void compute_Omega0_ur(double &result)
    {
      using namespace Pipes::compute_Omega0_ur;

      double N_ur = *Dep::N_ur;
      double Omega0_g = *Dep::Omega0_g;
      result = (N_ur)*7./8.*pow(4./11.,4./3.)* Omega0_g;
    }


    // (JR) delete when CLASS c interface is removed.
    void compute_Omega0_ncdm(double &result)
    {
      using namespace Pipes::compute_Omega0_ncdm;

      double mNu_tot_eV = *Dep::mNu_tot;
      double h = *Dep::H0/100.;

      result = mNu_tot_eV/(93.14*h*h);  // TODO: heads up: explicit assumption of T_ncdm = 0.71611 and T_cmb goes in here. Has to be generalised
    }

    void compute_Omega0_r(double &result)
    {
      using namespace Pipes::compute_Omega0_r;

      result = *Dep::Omega0_g + (*Dep::Omega0_ur);
      //std::cout << "omega0_g g " << *Dep::Omega0_g << " omega_ur " << *Dep::Omega0_ur <<  std::endl;
    }

/*
    (PS: Not sure if we really need this step in between. For all our casess so far we directly could map from eta0 to eta_BBN (up to constnat factors in front))
 *
    void calculate_etaCMB_SM(double &result)
    {
      using namespace Pipes::calculate_etaCMB_SM;

      result =  *Dep::eta0; // in SM the baryon to photon ratio does not change between today an CMB release
      logger() << "Baryon to photon ratio (eta) @CMB computed to be " << result << EOM;
    }
*/


/// -----------
/// BBN related functions (call AlterBBN, BBN abundances & Likelihood)
/// -----------

    /// add parameters of relicparam structure that should be set to non-default values
    /// to the AlterBBN_input map.
    /// If you want to modify a parameter which has not been used in CosmoBit before simply
    /// add it to the function 'fill_cosmomodel' in 'AlterBBN_<version>.cpp' and to the
    /// set of 'known' parameters 'known_relicparam_options'
    void AlterBBN_Input(map_str_dbl &result)
    {
      using namespace Pipes::AlterBBN_Input;


      // If we are using some of the "non-standard energy content" models, set the
      // inputs for the AlterBBN_input map according to the parameters of that model.
      // In case we are not using one of these models, we use the default values
      // (i.e. eta inferred from LCDM, Nnu = 3.046 and dNnu = 0)
      if (ModelInUse("etaBBN_rBBN_rCMB_dNurBBN_dNurCMB"))
      {
        const ModelParameters& NP_params = *Dep::etaBBN_rBBN_rCMB_dNurBBN_dNurCMB_parameters;

        double dNurBBN =  NP_params.at("dNur_BBN");

        // Check if the input for dNeff is negative (unphysical)
        static bool allow_negative_delta_N_ur = runOptions->getValueOrDef<bool>(false,"allow_negative_delta_N_ur");
        if ( (!allow_negative_delta_N_ur) && (dNurBBN < 0.0) )
        {
          std::ostringstream err;
          err << "A negative value for \"dNur_BBN\" is unphysical and is not allowed in CosmoBit by default!\n\n";
          err << "If you want to proceed with megative values, please add\n\n";
          err << "  - module: CosmoBit\n";
          err << "    options:\n";
          err << "      allow_negative_delta_N_ur: true\n\n";
          err << "to the Rules section of the yaml-file.";
          CosmoBit_error().raise(LOCAL_INFO,err.str());
        }

        //If check is passed, set inputs.
        result["Nnu"]=3.046*pow(NP_params.at("r_BBN"),4); // contribution from SM neutrinos
        result["dNnu"]=dNurBBN;    // dNnu: within AlterBBN scenarios in which the sum Nnu+dNnu is the same are identical
      }
      else
      {
        result["Nnu"]=3.046; // contribution from SM neutrinos
        result["dNnu"]=0.;    // no extra ur species in standard LCDM model
      }
      result["eta0"] = *Dep::etaBBN;

      result["failsafe"] = runOptions->getValueOrDef<double>(3,"failsafe");
      result["err"] = runOptions->getValueOrDef<double>(3,"err");

      logger() << "Set AlterBBN with parameters eta = " << result["eta0"] << ", Nnu = " << result["Nnu"] << ", dNnu = " << result["dNnu"];
      logger() << " and error params: failsafe = " << result["failsafe"] << ", err = " << result["err"] << EOM;
    }


    /// Check the validity of a correlation matrix for AlterBBN likelihood calculations given in the YAML file, and use it to populate a correlation matrix object
    void populate_correlation_matrix(const std::map<std::string, int>& abund_map, std::vector<std::vector<double>>& corr,
                                     std::vector<double>& relerr, bool use_relative_errors, const Options& runOptions)
    {
      std::vector<str> isotope_basis = runOptions.getValue<std::vector<str> >("isotope_basis");
      std::vector<std::vector<double>> tmp_corr = runOptions.getValue<std::vector<std::vector<double>>>("correlation_matrix");
      std::vector<double> tmp_relerr;
      unsigned int nisotopes = isotope_basis.size();

      // Check if the size of the isotope_basis and the size of the correlation matrix agree
      if (nisotopes != tmp_corr.size())
      {
        std::ostringstream err;
        err << "The length of the list \'isotope_basis\' and the size of the correlation matrix \'correlation_matrix\' do not agree";
        CosmoBit_error().raise(LOCAL_INFO, err.str());
      }

      // If the relative errors are also given, then do also a check if the length of the list is correct and if the entries are positive.
      if (use_relative_errors)
      {
        tmp_relerr = runOptions.getValue< std::vector<double> >("relative_errors");
        if (nisotopes != tmp_relerr.size())
        {
          std::ostringstream err;
          err << "The length of the list \'isotope_basis\' and the length of \'relative_errors\' do not agree";
          CosmoBit_error().raise(LOCAL_INFO, err.str());
        }
        for (std::vector<double>::iterator it = tmp_relerr.begin(); it != tmp_relerr.end(); it++)
        {
          if (*it <= 0.0)
          {
            std::ostringstream err;
            err << "One entry for the relative error is not positive";
            CosmoBit_error().raise(LOCAL_INFO, err.str());
          }
        }
      }

      // Check if the correlation matrix is square
      for (std::vector<std::vector<double>>::iterator it = tmp_corr.begin(); it != tmp_corr.end(); it++)
      {
        if (it->size() != nisotopes)
        {
          std::ostringstream err;
          err << "The correlation matrix is not a square matrix";
          CosmoBit_error().raise(LOCAL_INFO, err.str());
        }
      }

      // Check if the entries in the correlation matrix are reasonable
      for (unsigned int ie=0; ie<nisotopes; ie++)
      {
        //Check if the diagonal entries are equal to 1.
        if (std::abs(tmp_corr.at(ie).at(ie) - 1.) > 1e-6)
        {
          std::ostringstream err;
          err << "Not all diagonal elements of the correlation matirx are 1.";
          CosmoBit_error().raise(LOCAL_INFO, err.str());
        }
        for (unsigned int je=0; je<=ie; je++)
        {
          //Check for symmetry
          if (std::abs(tmp_corr.at(ie).at(je) - tmp_corr.at(je).at(ie)) > 1e-6)
          {
            std::ostringstream err;
            err << "The correlation matrix is not symmetric";
            CosmoBit_error().raise(LOCAL_INFO, err.str());
          }
          // Check if the off-diagonal elements are between -1 and 1.
          if (std::abs(tmp_corr.at(ie).at(je)) >= 1. && (ie != je))
          {
            std::ostringstream err;
            err << "The off-diagonal elements of the correlation matrix are not sensible (abs(..) > 1)";
            CosmoBit_error().raise(LOCAL_INFO, err.str());
          }
        }
      }

      // Check if the isotopes in the basis are actually known.
      for (std::vector<str>::iterator it = isotope_basis.begin(); it != isotope_basis.end(); it++)
      {
        if (abund_map.count(*it) == 0)
        {
          std::ostringstream err;
          err << "I do not recognise the element \'" << *it << "\'";
          CosmoBit_error().raise(LOCAL_INFO, err.str());
        }
      }

      // Populate the correlation matrix and relative errors
      for (std::vector<str>::iterator it1 = isotope_basis.begin(); it1 != isotope_basis.end(); it1++)
      {
        int ie  =  abund_map.at(*it1);
        int i = std::distance( isotope_basis.begin(), it1 );
        // If the relative errors are given, fill relerr with the respective values (-1.0 refers to no errors given).
        if (use_relative_errors) relerr.at(ie) = tmp_relerr.at(i);
        for (std::vector<str>::iterator it2 = isotope_basis.begin(); it2 != isotope_basis.end(); it2++)
        {
          int je = abund_map.at(*it2);
          int j = std::distance( isotope_basis.begin(), it2 );
          corr.at(ie).at(je) = tmp_corr.at(i).at(j);
        }
      }
    }

    /// Compute elemental abundances from BBN
    void compute_BBN_abundances(BBN_container &result)
    {
      using namespace Pipes::compute_BBN_abundances;

      // global variable of AlterBBN (# computed element abundances)
      const static int NNUC = BEreq::get_NNUC();

      // in AlterBBN ratioH and cov_ratioH are arrays of fixed length
      // with certain compiler versions (gcc 5.4.0) we have seen memory corruption problems
      // if we initialise these as
      // double ratioH[NNUC+1]
      // since the memory was not allocated properly. Fixed size arrays do not seem to be
      // properly supported even though there are no errors at compile time.
      // using a unique pointer for ratioH and a 2d vector for cov_ratioH avoids
      // these problems.
      auto deleter = [&](double* ptr){delete [] ptr;};
      std::unique_ptr<double[], decltype(deleter)> ratioH(new double[NNUC+1](), deleter);
      std::unique_ptr<double[], decltype(deleter)> cov_ratioH(new double[(NNUC+1)*(NNUC+1)](), deleter);

      static bool first = true;
      const static bool use_fudged_correlations = (runOptions->hasKey("correlation_matrix") && runOptions->hasKey("isotope_basis"));
      const static bool use_relative_errors = runOptions->hasKey("relative_errors");
      static std::vector<double> relerr(NNUC+1, -1.0);
      static std::vector<std::vector<double>> corr(NNUC+1, std::vector<double>(NNUC+1, 0.0));

      if (first)
      {
        // Init abundance map and allocate arrays in result
        result.set_abund_map(BEreq::get_abund_map_AlterBBN());
        result.init_arr_size(NNUC);

        // Work out which isotopes have been requested downstream
        // From the yaml sub-capabilities
        std::vector<str> v = Downstream::subcaps->getNames();
        // From other dependencies
        if (Downstream::neededFor("helium_abundance")) v.push_back("He4");
        result.set_active_isotopes(std::set<str>(v.begin(), v.end()));
        if (result.get_active_isotopes().empty())
        {
          str err = "No relevant sub-capabilities found for compute_BBN_abundances.  Please specify elements to\n"
                    "compute abundances for in the ObsLikes section of your yaml file as in e.g.\n"
                    "  sub_capabilities: [He4, D, Li7]";
          CosmoBit_error().raise(LOCAL_INFO, err);
        }

        // Process user-defined correlations (if provided)
        if (use_fudged_correlations)
        {
          for (int ie = 1; ie < NNUC; ie++) corr.at(ie).at(ie) = 1.;
          const std::map<std::string, int>& abund_map = result.get_abund_map();
          populate_correlation_matrix(abund_map, corr, relerr, use_relative_errors, *runOptions);
        }

        // Here for a good time, not a long time
        first = false;
      }

      // Fill AlterBBN_input map with the parameters for the model in consideration
      map_str_dbl AlterBBN_input = *Dep::AlterBBN_Input;

      // Call AlterBBN routine to calculate element abundances (& errors -- depending
      // on error calculation settings made with parameters 'err' and failsafe set in
      // 'AlterBBN_Input')
      if (not BEreq::call_nucl_err(AlterBBN_input, &ratioH[0], &cov_ratioH[0]))
      {
        std::ostringstream err;
        err << "AlterBBN calculation for primordial element abundances failed. Invalidating Point.";
        invalid_point().raise(err.str());
      }

      // Fill relative errors
      std::vector<double> err_ratio(NNUC+1,0);
      if (use_fudged_correlations) for (const int& ie : result.get_active_isotope_indices())
      {
        if (use_relative_errors && (relerr.at(ie) > 0.0))
          err_ratio.at(ie) =  relerr.at(ie) * ratioH[ie];
        else
          // get every diagonal element (row and line 0 is not filled)
          err_ratio.at(ie) = sqrt(cov_ratioH[ie*(NNUC+1)+ie]);
      }

      // Fill abundances and covariance matrix of BBN_container with requested results from AlterBBN
      for (const int& ie : result.get_active_isotope_indices())
      {
        result.set_BBN_abund(ie, ratioH[ie]);
        for (const int& je : result.get_active_isotope_indices())
        {
          if (use_fudged_correlations)
            result.set_BBN_covmat(ie, je, corr.at(ie).at(je) * err_ratio.at(ie) * err_ratio.at(je));
          else
            result.set_BBN_covmat(ie, je, cov_ratioH[ie*(NNUC+1)+je]);
        }
      }
    }

    /// Extract helium-4 abundance from BBN abundance container
    void extract_helium_abundance(double &result)
    {
      result = Pipes::extract_helium_abundance::Dep::BBN_abundances->get_BBN_abund("He4");
    }

    /// Compute the overall log-likelihood from BBN
    void compute_BBN_LogLike(double &result)
    {
      using namespace Pipes::compute_BBN_LogLike;

      double chi2 = 0;
      int ii = 0;
      int ie,je,s;

      BBN_container BBN_res = *Dep::BBN_abundances; // fill BBN_container with abundance results from AlterBBN
      const std::map<std::string, int>& abund_map = BBN_res.get_abund_map();

      // S.B. horrible hacky override here to use the YHe value from classy. 
      // Sorry, design principles. Sorry, modularity.
      bool override = runOptions->getValueOrDef(false, "use_classy_value");
      if (override)
      {
        BBN_res.set_BBN_abund("He4", *Dep::helium_abundance);
      }        

      static bool first = true;
      const static str filename = runOptions->getValueOrDef<std::string>("default.dat", "DataFile");
      const static str path_to_file = GAMBIT_DIR "/CosmoBit/data/BBN/" + filename;
      static std::map<std::string,std::vector<double>> dict;
      static int nobs;

      if (first)
      {
        // Read the data
        const ASCIIdictReader data(path_to_file);
        logger() << "BBN data read from file '" << filename << "'." << EOM;

        // Execute initialisation checks on the contents of the datafile
        std::map<std::string,std::vector<double>> td = data.get_dict();
        const str err = "Double entry for one element in BBN data file '" + filename + "'. \nYou can only enter one measurement per element.";
        if (data.duplicated_keys()) CosmoBit_error().raise(LOCAL_INFO, err);
        std::vector<sspair> doppelgangers = {{"Yp", "He4"}, {"D","H2"}};
        for (const sspair& x : doppelgangers)
        {
          if (td.count(x.first) == 0 and td.count(x.second) == 0)
          {
            CosmoBit_error().raise(LOCAL_INFO, err + "\nNote that "+x.first+" and "+x.second+" are the same species!");
          }
        }

        // Check that all isotopes requested in the yaml file exist in the datafile, and keep only the data needed
        const std::vector<str>& v = Downstream::subcaps->getNames();
        for (const str& isotope : std::set<str>(v.begin(), v.end()))
        {
          auto it = td.find(isotope);
          // Check if the isotope has been listed as a subcapability
          if (it == td.end())
          {
            str alt_name = "";
            for (const sspair& pair : doppelgangers)
            {
              if (isotope == pair.first) alt_name = pair.second;
              if (isotope == pair.second) alt_name = pair.first;
            }
            // Check if the isotope's doppelganger has been listed as a subcapability
            if (alt_name != "") it = td.find(alt_name);
          }
          // Throw an error if the isotope is not found in the datafile
          if (it == td.end()) CosmoBit_error().raise(LOCAL_INFO, "Did not find observations for "+isotope+" in "+filename+".");
          // Otherwise, save the corresponding dictionary entry
          else dict[isotope] = it->second;
        }

        // Save the number of observations to include in the likelihood.
        nobs = dict.size();
        if (nobs == 0)
        {
          str err = "No relevant sub-capabilities found for compute_BBN_LogLike.  Please specify elements to\n"
                    "compute likelihoods from in the ObsLikes section of your yaml file as in e.g.\n"
                    "  sub_capabilities: [He4, D]";
          CosmoBit_error().raise(LOCAL_INFO, err);
        }

        // Init out.
        first = false;
      }

      // Init vectors with observations, predictions and covmat
      double prediction[nobs],observed[nobs],sigmaobs[nobs],translate[nobs];
      gsl_matrix *cov = gsl_matrix_alloc(nobs, nobs);
      gsl_matrix *invcov = gsl_matrix_alloc(nobs, nobs);
      gsl_permutation *p = gsl_permutation_alloc(nobs);

      // Iterate through observation dictionary to fill observed, sigmaobs and prediction arrays
      for(std::map<std::string,std::vector<double>>::iterator iter = dict.begin(); iter != dict.end(); ++iter)
      {
        std::string key = iter->first; // iter = ["element key", [mean, sigma]]
        if(abund_map.count(key)!=1)   // throw error if element not contained in abundance map was entered in data file
        {
          std::ostringstream err;
          err << "Unknown element '"<< key <<"' in BBN data file '"<< filename<<"'. \nYou can only enter 'Yp' or 'He4', 'D' or 'H2', 'He3', 'Li7'.";
          CosmoBit_error().raise(LOCAL_INFO, err.str());
        }
        translate[ii]=abund_map.at(key); // to order observed and predicted abundances consistently
        observed[ii]=iter->second[0];
        sigmaobs[ii]=iter->second[1];
        prediction[ii]= BBN_res.get_BBN_abund(key);
        ii++;
      }

      // Fill the covariance matrix
      for(ie=0;ie<nobs;ie++) {for(je=0;je<nobs;je++) gsl_matrix_set(cov, ie, je,pow(sigmaobs[ie],2.)*(ie==je)+BBN_res.get_BBN_covmat(translate[ie], translate[je]));}

      // Compute the LU decomposition and inverse of cov mat
      gsl_linalg_LU_decomp(cov,p,&s);
      gsl_linalg_LU_invert(cov,p,invcov);

      // Compute the determinant of the inverse of the covmat
      double det_cov = gsl_linalg_LU_det(cov,s);

      // compute chi2
      for(ie=0;ie<nobs;ie++) for(je=0;je<nobs;je++) chi2+=(prediction[ie]-observed[ie])*gsl_matrix_get(invcov,ie,je)*(prediction[je]-observed[je]);
      result = -0.5*(chi2 + log(pow(2*pi,nobs)*det_cov));

      logger() << "BBN LogLike computed to be: " << result << EOM;

      gsl_matrix_free(cov);
      gsl_matrix_free(invcov);
      gsl_permutation_free(p);
    }

    /// -----------
    /// Background Likelihoods (SNe + H0 + BAO + Sigma8)
    /// -----------

    void compute_H0_LogLike(double &result)
    {
      using namespace Pipes::compute_H0_LogLike;

      const str filename = runOptions->getValue<std::string>("DataFile");
      const str path_to_file = GAMBIT_DIR "/CosmoBit/data/H0/" + runOptions->getValue<std::string>("DataFile");
      static ASCIItableReader data(path_to_file);
      static bool read_data = false;

      if(read_data == false)
      {
        logger() << "H0 data read from file '"<<filename<<"'." << EOM;
        std::vector<std::string> colnames = initVector<std::string>("mean", "sigma");
        data.setcolnames(colnames);

        if(data.getnrow() != 1)
        {
          std::ostringstream err;
          err << data.getnrow() << " data points for H0 measurement data read from '"<< filename << "'.\n Only one expected.";
          CosmoBit_error().raise(LOCAL_INFO, err.str());
        }
        read_data = true;
      }
      result = -0.5 * pow(*Dep::H0 - data["mean"][0],2)/ pow(data["sigma"][0],2);
    }

    void compute_sigma8_LogLike(double &result)
    {
      using namespace Pipes::compute_sigma8_LogLike;

      double sigma8,Omega0_m; // cosmo distances and sound horizon at drag,Hubble, theoretical prediction
      double chi2 =0;

      const str filename = runOptions->getValue<std::string>("DataFile");
      const str path_to_file = GAMBIT_DIR "/CosmoBit/data/sigma8/" + runOptions->getValue<std::string>("DataFile");
      static ASCIItableReader data(path_to_file);
      static bool read_data = false;
      static int nrow;

      sigma8 = BEreq::class_get_sigma8();
      Omega0_m = *Dep::Omega0_m;

      if(read_data == false)
      {
        logger() << "Sigma8 data read from file '"<<filename<<"'." << EOM;
        std::vector<std::string> colnames = initVector<std::string>("Omega_m_ref","Omega_m_index", "bestfit","sigma");
        data.setcolnames(colnames);
        nrow=data.getnrow();

        read_data = true;
      }

      for(int ie=0;ie<nrow;ie++)
      {
        chi2 += pow(( sigma8*pow(Omega0_m/data["Omega_m_ref"][ie], data["Omega_m_index"][ie]) - data["bestfit"][ie])/ data["sigma"][ie],2);
      }
      result = -0.5*chi2;
    }

/***********************************************/
/* Interface to CLASS Python wrapper, 'classy' */
/***********************************************/

    /// Initialises the container within CosmoBit from classy. This holds
    /// an instance of the classy class Class() (Yep, I know...)
    /// which can be handed over to MontePython, or just used to compute
    /// some observables.
    void set_classy_input(Classy_input& result)
    {
      using namespace Pipes::set_classy_input;
      result = *Dep::classy_primordial_parameters;
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
    }

    /// Initialises the container within CosmoBit from classy, but designed specifically
    /// to be used when MontePython is in use. This will ensure additional outputs are
    /// computed by classy CLASS to be passed to MontePython.
    void set_classy_input_with_MPLike(Classy_input& result)
    {
      using namespace Pipes::set_classy_input_with_MPLike;
      result = *Dep::classy_primordial_parameters;

      // Only get info from MP if something actually needs it downstream
      if (Downstream::neededFor("MP_LogLikes"))
      {
        // get extra cosmo_arguments from MP (gives a dictionary with output values that need
        // to be set for the class run)
        static pybind11::dict MP_cosmo_arguments = *Dep::cosmo_args_from_MPLike;
        logger() << LogTags::debug << "Extra cosmo_arguments needed from MP Likelihoods: ";
        logger() << pybind11::repr(MP_cosmo_arguments) << EOM;

        // add the arguments from Mp_cosmo_arguments which are not yet in cosmo_input_dict to it
        // also takes care of merging the "output" key values
        result.merge_input_dicts(MP_cosmo_arguments); // TODO (JR) use merge_pybind_dict routine instead -> don't need to duplicate code
        //merge_pybind_dicts(result, MP_cosmo_arguments);
      }
    }


  void set_classy_parameters_EnergyInjection_AnnihilatingDM(pybind11::dict &result)
  {
    using namespace Pipes::set_classy_parameters_EnergyInjection_AnnihilatingDM;

    // make sure nothing from previous run is contained
    result.clear();

    // Set relevant inputs for the scenario of s-wave annihilating DM
    const ModelParameters& NP_params = *Dep::AnnihilatingDM_general_parameters;
    result["DM_annihilation_cross_section"] = NP_params.at("sigmav");
    result["DM_annihilation_mass"] = NP_params.at("mass");

    // Get the results from the DarkAges tables that hold extra information to be passed to the CLASS thermodynamics structure
    static DarkAges::Energy_injection_efficiency_table fz;
    fz = *Dep::energy_injection_efficiency;
    bool f_eff_mode = fz.f_eff_mode;

    // flag passed to CLASS to signal that the energy_deposition_function is coming from GAMBIT
    // we patched exoclass to accept this. An alternative way without patching would be to write the tables to disk &
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

    // set the lengths of the input tables (since we are passing pointers to arrays CLASS has to know how long they are)
    result["energyinj_coef_num_lines"] = fz.redshift.size();

    // add the pointers to arrays class needs to know about to input dictionary
    // Note:
    //    - memory addresses are passed as strings (python wrapper for CLASS converts every entry to a string internally so
    //      we need to do that for the memory addresses before python casts them to something else)
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
  }

  void set_classy_parameters_EnergyInjection_DecayingDM(pybind11::dict &result)
  {
    using namespace Pipes::set_classy_parameters_EnergyInjection_DecayingDM;

    // make sure nothing from previous run is contained
    result.clear();

    // Set relevant inputs for the scenario of decaying DM
    const ModelParameters& NP_params = *Dep::DecayingDM_general_parameters;
    result["DM_decay_tau"] = NP_params.at("lifetime");
    result["DM_decay_fraction"] = NP_params.at("fraction");

    // Get the results from the DarkAges tables that hold extra information to be passed to the CLASS thermodynamics structure
    static DarkAges::Energy_injection_efficiency_table fz;
    fz = *Dep::energy_injection_efficiency;
    bool f_eff_mode = fz.f_eff_mode;

    // flag passed to CLASS to signal that the energy_deposition_function is coming from GAMBIT
    // we patched exoclass to accept this. An alternative way without patching would be to write the tables to disk &
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

    // set the lengths of the input tables (since we are passing pointers to arrays CLASS has to know how long they are)
    result["energyinj_coef_num_lines"] = fz.redshift.size();

    // add the pointers to arrays class needs to know about to input dictionary
    // Note:
    //    - memory addresses are passed as strings (python wrapper for CLASS converts every entry to a string internally so
    //      we need to do that for the memory addresses before python casts them to something else)
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
  }

  /// add all inputs for CLASS needed to produce the correct output to be
  /// able to compute the Planck CMB likelihoods
  void set_classy_PlanckLike_input(pybind11::dict &result)
  {
    using namespace Pipes::set_classy_PlanckLike_input;

    // make sure nothing from previous run is contained
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



    /* Classy getter functions */

    /// Hubble
    void get_H0_classy(double &result)
    {
      using namespace Pipes::get_H0_classy;

      // Rescale by c [km/s]
      result = _c_SI_*BEreq::class_get_H0()/1000;
    }

    /// Energy densities *today* (Omega0)

    /// Matter
    void get_Omega0_m_classy(double& result)
    {
      using namespace Pipes::get_Omega0_m_classy;

      result = BEreq::class_get_Omega0_m();
    }

    /// Radiation
    void get_Omega0_r_classy(double& result)
    {
      using namespace Pipes::get_Omega0_r_classy;

      result = BEreq::class_get_Omega0_r();
    }

    /// Ultra-relativistic
    void get_Omega0_ur_classy(double& result)
    {
      using namespace Pipes::get_Omega0_ur_classy;

      result = BEreq::class_get_Omega0_ur();
    }

    /// Non-cold Dark Matter
    void get_Omega0_ncdm_tot_classy(double& result)
    {
      using namespace Pipes::get_Omega0_ncdm_tot_classy;

      result = BEreq::class_get_Omega0_ncdm_tot();
    }

    /// Sigma8
    void get_Sigma8_classy(double& result)
    {
      using namespace Pipes::get_Sigma8_classy;

      double sigma8 = BEreq::class_get_sigma8();
      double Omega0_m = *Dep::Omega0_m;

      result = sigma8*pow(Omega0_m/0.3, 0.5);
    }

    /// Effective number of neutrino species
    // (mostly for cross-checking!)
    void get_Neff_classy(double& result)
    {
      using namespace Pipes::get_Neff_classy;

      result = BEreq::class_get_Neff();
    }

    /// Comoving sound horizon at Baryon drag epoch
    void get_rs_drag_classy(double& result)
    {
      using namespace Pipes::get_rs_drag_classy;

      result = BEreq::class_get_rs();
    }

    /// Helium abundance
    void get_YHe_classy(double& result)
    {
      using namespace Pipes::get_YHe_classy;

      result = BEreq::class_get_YHe();
    }


/***************/
/* MontePython */
/***************/

    /// function to fill the mcmc_parameters dictionary of MontePython's Data object with current
    /// values of nuisance parameters
    void set_parameter_dict_for_MPLike(pybind11::dict & result)
    {
      using namespace Pipes::set_parameter_dict_for_MPLike;
      using namespace pybind11::literals;

      // The loop has to be executed for every parameter point. It takes about 0.00023 s -> ~4 minutes for 1e6 points
      for (auto it=Param.begin(); it != Param.end(); it++)
      {
        std::string name = it->first;
        double value = *Param[name];

        // check if any models are scanned for which we had to rename the nuisance parameters due to
        //    a) parameters having the same name  -> e.g. 'epsilon' and 'sigma_NL'
        //    b) parameter names containing symbols that can't be used in macros -> e.g. "^" in 'beta_0^Euclid'

        // a) have to rename parameters epsilon_ska, epsilon_euclid,.. to "epsilon" as they are implemented in MontePython
        if (name.find("epsilon") != std::string::npos){name="epsilon";}

        // a) have to rename parameters sigma_NL_ska, sigma_NL_euclid,.. to "sigma_NL" as they are implemented in MontePython
        else if (name.find("sigma_NL") != std::string::npos){name="sigma_NL";}

        // b) get the "^" characters back into the parameter names
        //   -> beta_x<experiment> has to be beta_x^<experiment> where x = 0 or 1 and <experiment> = Euclid, SKA1 or SKA2
        //if(ModelInUse("cosmo_nuisance_euclid_pk") or ModelInUse("cosmo_nuisance_ska"))
        else if (name.find("beta_")!= std::string::npos){name = name.insert(6,"^");}

        result[name.c_str()] = pybind11::dict("current"_a=value,"scale"_a=1.); // scale always 1 in GAMBIT
      }
    }

    /// function to fill the mcmc_parameters dictionary of MontePython's Data object with current
    /// This version of the capability 'parameter_dict_for_MPLike' is used when no Likelihood with nuisance parameters is in use
    /// just passes an empty py dictionary
    void pass_empty_parameter_dict_for_MPLike(pybind11::dict & result)
    {
      using namespace Pipes::pass_empty_parameter_dict_for_MPLike;
      pybind11::dict r;
      result = r;
      // Nothing to do here.
    }

    /// Create the MontePython data and likelihood objects, determining which experiments are in use in the process
    void create_MP_objects(MPLike_objects_container &result)
    {
      using namespace Pipes::create_MP_objects;
      static map_str_pyobj likelihoods;
      static bool first = true;

      // Determine which likelihoods to compute and initialise the relevant MontePython objects.
      if (first)
      {
        // Set up some references for easier reading
        auto& data = std::get<0>(result);
        auto& experiments = std::get<1>(result);
        auto& likelihoods = std::get<2>(result);

        // Get list of likelihoods implemented in MP
        std::vector<str> avail_likes = BEreq::get_MP_available_likelihoods();

        // Get the list of the experiments and datafiles given in the YAML file as sub-capabilities.
        // Using the default datafile can be achieved by leaving the datafile out, or settting it to "default".
        YAML::Node subcaps = Downstream::subcaps->getNode();
        std::vector<YAML::Node> empties;
        for (const auto& x : subcaps) if (x.second.IsNull()) empties.push_back(x.first);
        for (const auto& x : empties) subcaps[x] = "default";
        if (subcaps.IsNull())
        {
          if (Downstream::neededFor("MP_LogLikes"))
          {
            std::ostringstream ss;
            ss << "No sub-capabilities found when attempting to create MontePython objects." << endl
               << "This can happen because you either forgot to choose any experiments," << endl
               << "or because you used incorrect syntax to choose them as sub-capabilities." << endl
               << "You can do this in the relevant entry of the ObsLikes section of your YAML file," << endl
               << "by setting sub_capabilities as a scalar (if you only want one experiment), e.g." << endl
               << "    sub_capabilities: bao_smallz_2014" << endl
               << "or as a sequence (if you don't need to specify data files), e.g." << endl
               << "    sub_capabilities:" << endl
               << "      - bao_smallz_2014" << endl
               << "      - Pantheon" << endl
               << "or even as a map (if you want to specify data files), e.g." << endl
               << "    sub_capabilities:" << endl
               << "      bao_smallz_2014: default" << endl
               << "      Pantheon: default" << endl;
            CosmoBit_error().raise(LOCAL_INFO, ss.str());
          }
        }
        else experiments = subcaps.as<map_str_str>();

        // S.B. remove the BBN likes from here: sub-caps aren't meant 
        // to work like this, I guess.
        experiments.erase("H2");
        experiments.erase("D");
        experiments.erase("H3");
        experiments.erase("He3");
        experiments.erase("He4");
        experiments.erase("Yp");
        experiments.erase("Li6");
        experiments.erase("Li7");
        experiments.erase("Be7");
        experiments.erase("Li8");

        // Check that all the requested likelihoods can actually be provided by MP
        for (const auto& x : experiments)
        {
          if (std::find(avail_likes.begin(), avail_likes.end(), x.first) == avail_likes.end())
          {
            str errmsg = "Likelihood '" + x.first + "' is not implemented in MontePython. Check for typos or implement it.\nLikelihoods currently available are:\n";
            for (const auto& value : avail_likes) errmsg += ("\t"+value+"\n");
            CosmoBit_error().raise(LOCAL_INFO, errmsg);
          }
          logger() << LogTags::debug << "Read MontePythonLike option "<< x.first << ", using data file " << x.second << EOM;
        }

        // MPLike_data_container should only be created and set once, when calculating the first point.
        // After that it has to be kept alive since it contains a vector with the initialised MPLike Likelihood objects.
        data = BEreq::create_MP_data_object(experiments);

        // Add current parameters to data object to enable check if all nuisance parameters are
        // scanned upon initialisation of likelihood objects
        data.attr("mcmc_parameters") = *Dep::parameter_dict_for_MPLike;
        likelihoods = BEreq::create_MP_likelihood_objects(data, experiments);

        // It's been nice, but let's not do this again.
        first = false;
      }
    }

    /// When initialising the MontePython Likelihood objects they add the output that needs to be computed by class
    /// to the input dictionary. We need to get these before starting the class run
    /// e.g. for Planck_SZ likelihood the entries {'output': ' mPk ', 'P_k_max_h/Mpc': '1.'} need to be added
    /// to compute all needed observables
    void init_cosmo_args_from_MPLike(pybind11::dict &result)
    {
      using namespace Pipes::init_cosmo_args_from_MPLike;
      result.clear();
      pybind11::dict tmp_dict = std::get<0>(*Dep::MP_objects).attr("cosmo_arguments");
      // Stringify all values in the dictionary and strip off leading and trailing whitespaces
      for (auto it: tmp_dict)
      {
        std::string key = (pybind11::str(it.first)).cast<std::string>();
        std::string val = (pybind11::str(it.second)).cast<std::string>();
        boost::algorithm::trim(val);
        result[key.c_str()] = val.c_str();
      }
    }

    /// Computes lnL for each experiment initialised in MontePython
    void compute_MP_LogLikes(map_str_dbl & result)
    {
      using namespace Pipes::compute_MP_LogLikes;
      static pybind11::object data = std::get<0>(*Dep::MP_objects);
      static const map_str_str& experiments = std::get<1>(*Dep::MP_objects);
      static const map_str_pyobj& likelihoods = std::get<2>(*Dep::MP_objects);
      static const MPLike_data_container mplike_cont(data, likelihoods);

      // Pass current values of nuisance parameters to data.mcmc_parameters dictionary for likelihood computation in MP
      mplike_cont.data.attr("mcmc_parameters") = *Dep::parameter_dict_for_MPLike;

      // Create instance of classy class Class
      pybind11::object cosmo = BEreq::get_classy_cosmo_object();

      // Loop through the list of experiments, and query the lnL from the MontePython backend.
      for (sspair it : experiments)
      {
        // Likelihood names are keys of experiment map (str, str map mapping likelihood name to .data file)
        double logLike = BEreq::get_MP_loglike(mplike_cont, cosmo, it.first);
        result[it.first] = logLike;
        logger() << "(compute_MP_LogLikes):  name: " << it.first << "\tvalue: " << logLike << EOM;
        //std::cout << "(compute_MP_LogLikes):  name: " << it.first << "\tvalue: "<< logLike << std::endl;
      }
    }

    /// Computes the combined lnL from the set of experiments
    /// given to MontePython.
    void compute_MP_combined_LogLike(double& result)
    {
      using namespace Pipes::compute_MP_combined_LogLike;

      // Get likelihoods computed by MontePython
      map_str_dbl MP_lnLs = *Dep::MP_LogLikes;

      // Retrieve the sub-capabilities requested in the YAML file
      std::vector<str> subcaps = Downstream::subcaps->getNames();

      // Iterate through map of doubles and return one big fat double,
      // selecting only those entries specified as sub-capabilities.
      double lnL = 0.;
      logger() << LogTags::debug << "(compute_MP_combined_LogLike):";
      for (const auto &p : MP_lnLs)
      {
        if (std::find(subcaps.begin(), subcaps.end(), p.first) != subcaps.end())
        {
          logger() << endl << "  name: "  << p.first << "\tvalue: " << p.second;
          lnL += p.second;
        }
      }
      logger() << EOM;
      result = lnL;
    }

  }
}
