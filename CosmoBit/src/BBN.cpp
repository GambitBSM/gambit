//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  CosmoBit routines relating to BBN.
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
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2020 Sep
///  \date 2022 Jan
///
///  *********************************************

#include <memory>  // make_unique pointers
#include <stdint.h> // save memory addresses as int

#include <gsl/gsl_linalg.h>

#include "gambit/Utils/yaml_options.hpp"
#include "gambit/Utils/ascii_dict_reader.hpp"
#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/CosmoBit/CosmoBit_rollcall.hpp"
#include "gambit/CosmoBit/CosmoBit_types.hpp"

namespace Gambit
{

  namespace CosmoBit
  {
    using namespace LogTags;

    /// Add parameters of relicparam structure that should be set to non-default values
    /// to the AlterBBN_input map.
    /// If you want to modify a parameter which has not been used in CosmoBit before, simply
    /// add it to the function 'fill_cosmomodel' in 'AlterBBN_<version>.cpp' and to the
    /// set of 'known' parameters 'known_relicparam_options'.
    void AlterBBN_Input(map_str_dbl &result)
    {
      using namespace Pipes::AlterBBN_Input;

      // If we are using some of the "non-standard energy content" models, set the
      // inputs for the AlterBBN_input map according to the parameters of that model.
      // In case we are not using one of these models, we use the default values
      // (i.e. eta inferred from LCDM, Nnu = Neff_SM (3.045) and dNnu = 0)
      if (ModelInUse("etaBBN_rBBN_rCMB_dNurBBN_dNurCMB"))
      {
        double dNurBBN = *Param.at("dNur_BBN");

        // Check if the input for Delta N_ur is negative (unphysical)
        // NOTE: CosmoBit performs no sanity checks if you allow negative Delta N_ur; you're on your own.
        static bool allow_negative_delta_N_ur = runOptions->getValueOrDef<bool>(false,"allow_negative_delta_N_ur");

        // Only let the user have negative contributions to NEff from Delta N_ur if they've signed off on it.
        if ( (!allow_negative_delta_N_ur) && (dNurBBN < 0.0) )
        {
          std::ostringstream err;
          err << "A negative value for \"dNur_BBN\" is unphysical and is not allowed in CosmoBit by default!\n\n";
          err << "If you want to proceed with negative values, please add\n\n";
          err << "  - module: CosmoBit\n";
          err << "    options:\n";
          err << "      allow_negative_delta_N_ur: true\n\n";
          err << "to the Rules section of the YAML file.";
          CosmoBit_error().raise(LOCAL_INFO,err.str());
        }

        //If check is passed, set inputs.
        result["Nnu"] = *Dep::Neff_SM*pow(*Param.at("r_BBN"),4); // contribution from SM neutrinos
        result["dNnu"] = dNurBBN;                                // dNnu: within AlterBBN scenarios in which the sum Nnu+dNnu is the same are identical
        result["eta0"] = *Param.at("eta_BBN");                // eta at the end of BBN
      }
      else // at this point either LCDM or LCDM_theta are in use so we assume standard values for Nnu and dNnu
      {
        result["Nnu"] = *Dep::Neff_SM; // contribution from SM neutrinos
        result["dNnu"] = 0.;           // no extra ur species in standard LCDM model
        result["eta0"] = *Dep::eta0;  // assume etaBBN = eta0
      }

      // Adopt the default value for the neutron lifetime in seconds if is not passed as a model parameter
      if (ModelInUse("nuclear_params_neutron_lifetime"))
      {
        result["neutron_lifetime"] = *Param.at("neutron_lifetime");
      }
      else
      {
        result["neutron_lifetime"] = 879.4; // (PDG 2019 recommendation http://pdg.lbl.gov/2019/listings/rpp2019-list-n.pdf);
      }

      // Tell AlterBBN how to the method and precision to solve the differential equations (->failsafe)
      // and also tell it how thorough it should estimate the the theoretical uncertainties.
      result["failsafe"] = runOptions->getValueOrDef<double>(7,"failsafe");
      result["err"] = runOptions->getValueOrDef<double>(1,"err");

      logger() << "Set AlterBBN with parameters eta = " << result["eta0"] << ", Nnu = " << result["Nnu"] << ", dNnu = " << result["dNnu"] << ", neutron lifetime = " << result["neutron_lifetime"];
      logger() << " and error params: failsafe = " << result["failsafe"] << ", err = " << result["err"] << EOM;
    }


    /// Check the validity of a correlation matrix for AlterBBN likelihood calculations given in the YAML file, and use it to populate a correlation matrix object
    void populate_correlation_matrix(const std::map<std::string, int>& abund_map, std::vector<std::vector<double>>& corr,
                                     std::vector<double>& errors, bool has_errors, const Options& runOptions)
    {
      std::vector<str> isotope_basis = runOptions.getValue<std::vector<str> >("isotope_basis");
      unsigned int nisotopes = isotope_basis.size();

      std::vector<std::vector<double>> tmp_corr;
      if (runOptions.hasKey("correlation_matrix"))
      {
        tmp_corr = runOptions.getValue<std::vector<std::vector<double>>>("correlation_matrix");
      }
      else
      {
        tmp_corr = std::vector<std::vector<double>>(nisotopes, std::vector<double>(nisotopes,0.0));
        for (unsigned int ie = 0; ie < nisotopes; ie++)
          tmp_corr.at(ie).at(ie) = 1.0;
      }

      std::vector<double> tmp_err;

      // Check if the size of the isotope_basis and the size of the correlation matrix agree
      if (nisotopes != tmp_corr.size())
      {
        std::ostringstream err;
        err << "The length of the list \'isotope_basis\' and the size of the correlation matrix \'correlation_matrix\' do not agree";
        CosmoBit_error().raise(LOCAL_INFO, err.str());
      }

      // If the relative errors or absolute errors are also given, then do also
      // a check if the length of the list is correct and if the entries are positive.
      if (has_errors)
      {
        if (runOptions.hasKey("relative_errors"))
        {
          tmp_err = runOptions.getValue< std::vector<double> >("relative_errors");
          if (nisotopes != tmp_err.size())
          {
            std::ostringstream err;
            err << "The length of the list \'isotope_basis\' and the length of \'relative_errors\' do not agree";
            CosmoBit_error().raise(LOCAL_INFO, err.str());
          }
        }
        else
        {
          tmp_err = runOptions.getValue< std::vector<double> >("absolute_errors");
          if (nisotopes != tmp_err.size())
          {
            std::ostringstream err;
            err << "The length of the list \'isotope_basis\' and the length of \'absolute_errors\' do not agree";
            CosmoBit_error().raise(LOCAL_INFO, err.str());
          }
        }

        for (std::vector<double>::iterator it = tmp_err.begin(); it != tmp_err.end(); it++)
        {
          if (*it <= 0.0)
          {
            std::ostringstream err;
            err << "At least one entry in 'relative_error'/'absolute_error' is not positive";
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
        // Check if the diagonal entries are equal to 1.
        if (std::abs(tmp_corr.at(ie).at(ie) - 1.) > 1e-6)
        {
          std::ostringstream err;
          err << "Not all diagonal elements of the correlation matrix are 1.";
          CosmoBit_error().raise(LOCAL_INFO, err.str());
        }
        for (unsigned int je=0; je<=ie; je++)
        {
          // Check for symmetry
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

      // Populate the correlation matrix and relative (absolute) errors
      for (std::vector<str>::iterator it1 = isotope_basis.begin(); it1 != isotope_basis.end(); it1++)
      {
        int ie  =  abund_map.at(*it1);
        int i = std::distance( isotope_basis.begin(), it1 );
        // If errors are given, fill errors with the respective values (-1.0 refers to no errors given).
        if (has_errors) errors.at(ie) = tmp_err.at(i);
        for (std::vector<str>::iterator it2 = isotope_basis.begin(); it2 != isotope_basis.end(); it2++)
        {
          int je = abund_map.at(*it2);
          int j = std::distance( isotope_basis.begin(), it2 );
          corr.at(ie).at(je) = tmp_corr.at(i).at(j);
        }
      }
    }

    /// Compute elemental abundances from BBN
    void compute_primordial_abundances_BBN(BBN_container &result)
    {
      using namespace Pipes::compute_primordial_abundances_BBN;

      // Global variable of AlterBBN (# computed element abundances)
      const static size_t NNUC = BEreq::get_NNUC();

      // In AlterBBN ratioH and cov_ratioH are arrays of fixed length.
      // With certain compiler versions (gcc 5.4.0) we have seen memory corruption problems
      // if we initialise these as double ratioH[NNUC+1], since the memory was not allocated properly.
      // Fixed size arrays do not seem to be properly supported even though there are no errors at compile time.
      // Using a unique pointer for ratioH and a 2D vector for cov_ratioH avoids these problems.
      auto deleter = [&](double* ptr){delete [] ptr;};
      std::unique_ptr<double[], decltype(deleter)> ratioH(new double[NNUC+1](), deleter);
      std::unique_ptr<double[], decltype(deleter)> ratioH_upper(new double[NNUC+1](), deleter);
      std::unique_ptr<double[], decltype(deleter)> ratioH_lower(new double[NNUC+1](), deleter);
      std::unique_ptr<double[], decltype(deleter)> cov_ratioH(new double[(NNUC+1)*(NNUC+1)](), deleter);

      static bool first = true;

      /*  Logic of the modified uncertainty treatment:
          - To modify the covariance matrix, the list containing the isotope basis
            must be present.
          - If the correlation_matrix is given it will be read, if it is missing,
            it is assumed to be diagonal.
          - For the uncertainties on the respective isotopes, either the relative
            or an absolute error can be specified. They are mutually exclusive.
            If they are missing, the uncertainty will be deduced from the result
            of AlterBBN
      */
      const static bool use_custom_covariances = (runOptions->hasKey("isotope_basis"));
      const static bool has_relative_errors = runOptions->hasKey("relative_errors");
      const static bool has_absolute_errors = runOptions->hasKey("absolute_errors");
      const static bool has_custom_correlations = runOptions->hasKey("correlation_matrix");
      const static bool use_diff_uncertainties = runOptions->getValueOrDef<bool>(false, "diff_uncertainties");

      // Raise error if the modified uncertainty treatment is intended but 'isotope_basis' is missing
      if( !use_custom_covariances &&
          (has_relative_errors || has_absolute_errors || has_custom_correlations) )
      {
        str err = "It appears that you intend to pass a custom covariance"
                  " matrix to AlterBBN, but the entry for \'isotope_basis\'"
                  " is missing in the options.\n"
                  "Without this entry neither of the options \'relative_errors\',"
                  " \'absolute_errors\', or \'correlation_matrix\' can be interpreted.\n\n"
                  "Please fix this by providing \'isotope_basis\' or by deleting the conflicting options.";
                  CosmoBit_error().raise(LOCAL_INFO, err);
      }

      // Raise error if the uncertainty rules are contradictory
      if (has_relative_errors && has_absolute_errors)
      {
        str err = "You specified both \'relative_errors\' and \'absolute_errors\'.\n"
                  "This is contradictory. Please choose only one option.\n";
        CosmoBit_error().raise(LOCAL_INFO, err);
      }

      if ((has_relative_errors or has_absolute_errors) and use_diff_uncertainties)
      {
        str err = "The options \'relative_errors\' and \'absolute_errors\' are contradictory with \'diff_uncertainties\'.\n"
                  "Please choose either one of the former or the latter option.\n";
        CosmoBit_error().raise(LOCAL_INFO, err);
      }

      // Define the vectors to hold the customs errors (correlation matrix + relative (absolute) errors on the isotopes)
      static std::vector<double> errors(NNUC+1, -1.0);
      static std::vector<std::vector<double>> corr(NNUC+1, std::vector<double>(NNUC+1, 0.0));

      // Fill AlterBBN_input map with the parameters for the model in consideration
      map_str_dbl AlterBBN_input = *Dep::AlterBBN_Input;

      if (first)
      {
        // Init abundance map and allocate arrays in result
        result.set_abund_map(BEreq::get_abund_map_AlterBBN());
        result.init_arr_size(NNUC);

        // Work out which isotopes have been requested downstream
        // From the YAML sub-capabilities
        std::vector<str> v = Downstream::subcaps->getNames();
        // From other dependencies
        if (Downstream::neededFor("helium_abundance")) v.push_back("He4");
        result.set_active_isotopes(std::set<str>(v.begin(), v.end()));
        if (result.get_active_isotopes().empty())
        {
          str err = "No relevant sub-capabilities found for compute_primordial_abundances_BBN.  Please specify elements to\n"
                    "compute abundances for in the ObsLikes section of your yaml file as in e.g.\n"
                    "  sub_capabilities: [He4, D, Li7]";
          CosmoBit_error().raise(LOCAL_INFO, err);
        }

        // Process user-defined correlations (if provided)
        if (use_custom_covariances)
        {
          for (size_t ie = 1; ie <= NNUC; ie++) corr.at(ie).at(ie) = 1.;
          std::map<std::string, int> abund_map = result.get_abund_map();

          // Check whether any of the entries in isotope_basis is not recognised
          std::vector<str> isotope_basis = runOptions->getValue<std::vector<str> >("isotope_basis");
          for (const auto& it : isotope_basis)
          {
            if (abund_map.count(it) == 0)
            {
              std::ostringstream err;
              err << "The isotope \'" << it << "\' is not recognised by AlterBBN." ;
              CosmoBit_error().raise(LOCAL_INFO, err.str());
            }
          }

          bool has_errors = (has_relative_errors || has_absolute_errors);

          // If either has_relative_errors or has_absolute_errors is and the "err" option for AlterBBN is nonzero,
          // we need to carefully check, whether we are about to override all error estimates for the relevant abundances.
          // To this end, perform a set difference between the elements in the subcaps (i.e. isotopes we are interested in)
          // and the isotopes in isotope basis (the ones we want to override).
          // When all elements in v are included in isotope_basis, throw an error
          if (has_errors && int(AlterBBN_input["err"]) != 0)
          {
            std::set<int> modified_indices, diff;
            for (const auto& it : isotope_basis)
            {
              modified_indices.insert(abund_map[it]);
            }
            std::set<int> active_indices = result.get_active_isotope_indices();
            std::set_difference(active_indices.begin(), active_indices.end(),
                                modified_indices.begin(), modified_indices.end(),
                                std::inserter(diff, diff.begin()));

            if (diff.size() == 0)
            {
              std::ostringstream err;
              err << "It seems that you run AlterBBN in a mode with \'error\' != 0 ";
              err << "but you have also chosen to set the uncertainties manually by ";
              err << "either \'absolute_errors\' or \'relative_errors\'.\n";
              err << "Given your input for the \'isotope_basis\' option, you are about ";
              err << "to ovveride all relevant entries of the covariance matrix.\n\n";
              err << "Therefore any nonzero value for \'err\' would have no effect on your ";
              err << "results but can slow down the code significantly.\n" ;
              err << "Please fix this by setting \'err\'to 0 in the rule for \'AlterBBN_Input\'.";
              CosmoBit_error().raise(LOCAL_INFO, err.str());
            }
          }

          populate_correlation_matrix(abund_map, corr, errors, has_errors, *runOptions);
        }

        // Here for a good time, not a long time
        first = false;
      }

      // Call AlterBBN routine to calculate element abundances (& errors -- depending
      // on error calculation settings made with parameters 'err' and failsafe set in
      // 'AlterBBN_Input')
      if (not BEreq::call_nucl_err(AlterBBN_input, &ratioH[0], &cov_ratioH[0]))
      {
        std::ostringstream err;
        err << "AlterBBN calculation for primordial element abundances failed. Invalidating Point.";
        invalid_point().raise(err.str());
      }

      // If the uncertainties are to be taken as difference of high/low values, compute the high and low abundances
      if(use_diff_uncertainties)
      {
        int err = AlterBBN_input["err"];
        AlterBBN_input["err"] = 1;
        int err1 = BEreq::call_nucl(AlterBBN_input, &ratioH_upper[0]);
        AlterBBN_input["err"] = 2;
        int err2 = BEreq::call_nucl(AlterBBN_input, &ratioH_lower[0]);
        AlterBBN_input["err"] = err;
        if (not err1 or not err2)
        {
          std::ostringstream err;
          err << "AlterBBN calculation for primordial element abundances failed.";
          CosmoBit_error().raise(LOCAL_INFO, err.str());
        }
      }

      // Fill relative (absolute) errors
      std::vector<double> err_ratio(NNUC+1,0);
      if (use_custom_covariances) for (size_t ie=1; ie <= NNUC; ++ie)
      {
        if (has_relative_errors && (errors.at(ie) > 0.0))
          err_ratio.at(ie) =  errors.at(ie) * ratioH[ie];
        else if (has_absolute_errors && (errors.at(ie) > 0.0))
          err_ratio.at(ie) =  errors.at(ie);
        else if (use_diff_uncertainties)
        {
          err_ratio.at(ie) = std::max(std::abs(ratioH_upper[ie]-ratioH[ie]),std::abs(ratioH_lower[ie]-ratioH[ie]));
          // If the error is larger than the central value, take as error the central value
          if(err_ratio.at(ie) > ratioH[ie]) err_ratio.at(ie) = ratioH[ie];
        }
        else
          // get every diagonal element (row and line 0 are not filled)
          err_ratio.at(ie) = sqrt(cov_ratioH[ie*(NNUC+1)+ie]);
      }

      // Fill abundances and covariance matrix of BBN_container with requested results from AlterBBN
      for (size_t ie=1; ie <= NNUC; ++ie)
      {
        result.set_BBN_abund(ie, triplet<double>(ratioH[ie],ratioH_upper[ie],ratioH_lower[ie]));
        for (size_t je=1; je <= NNUC; ++je)
        {
          if (use_custom_covariances)
            result.set_BBN_covmat(ie, je, corr.at(ie).at(je) * err_ratio.at(ie) * err_ratio.at(je));
          else
            result.set_BBN_covmat(ie, je, cov_ratioH[ie*(NNUC+1)+je]);
        }
      }

    }

    // Dummy function to return the primordial abundances unchanged from BBN
    void primordial_abundances(BBN_container &result)
    {
      using namespace Pipes::primordial_abundances;
      result = *Dep::primordial_abundances_BBN;
    }

    // Compute the primordial abundances including the effects of photodisintegration
    // from a decaying DM component.
    void primordial_abundances_decayingDM(BBN_container &result)
    {
      using namespace Pipes::primordial_abundances_decayingDM;

      // Get all the relevant parameters from the decayingDM_mixture model
      const double m_in_MeV = 1e3*(*Param["mass"]);
      const double tau = *Param["lifetime"];
      const double BR_el = *Param["BR_el"];
      const double BR_ph = *Param["BR_ph"];
      const double xi = *Param["fraction"];

      // Calculate the number density of the decaying particles today as if they would not have decayed. (in MeV^3)
      const double rho0_crit_by_h2 = 3.*pow(m_planck_red*1e3,2) * pow((1e5*1e3*hbar/Mpc_SI),2);  // rho0_crit/(h^2) in MeV^4
      const double omega_cdm = *Param["omega_cdm"];
      const double n0_a = xi / m_in_MeV * omega_cdm * rho0_crit_by_h2;

      // Normalise n0_a with respect to the photon number density at T0.
      const double T_cmb_in_MeV = 1e-6 * kB_eV_over_K * *Param["T_cmb"];
      const double n0_gamma = 2. * zeta3 / pow(pi,2) * pow(T_cmb_in_MeV,3);
      const double N0a = n0_a / n0_gamma;

      // Fixed number of isotopes
      int niso = 9;

      // Set input parameters
      BEreq::set_input_params(
        byVal(runOptions->getValueOrDef<bool>(false, "verbose")),
        byVal(runOptions->getValueOrDef<int>(150, "NE_pd")), // default: 150, fast: 75, aggresive: 30
        byVal(runOptions->getValueOrDef<int>(50, "NT_pd")), // default: 50, fast: 25, aggresive: 10
        byVal(runOptions->getValueOrDef<double>(1e-3, "eps")) // default: 1e-3, fast: 1e-2, aggresive: 1e-1
      );

      result = *Dep::primordial_abundances_BBN;

      std::vector<double> abundances_pre(niso,0.0);
      std::vector<double> covariance_pre(niso*niso,0.0);
      for(int i=0; i !=niso; ++i)
      {
        abundances_pre[i] = result.get_BBN_abund(i+1);
        for(int j=0; j<niso; ++j)
        {
          covariance_pre[i*niso + j] = result.get_BBN_covmat(i+1,j+1);
        }
      }
      std::vector<double> abundances_post(niso,0.0);
      std::vector<double> covariance_post(niso*niso,0.0);

      BEreq::abundance_photodisintegration_decay(abundances_pre.data(),
                                                 covariance_pre.data(),
                                                 abundances_post.data(),
                                                 covariance_post.data(),
                                                 byVal(m_in_MeV),
                                                 byVal(tau),
                                                 byVal(N0a),
                                                 byVal(BR_el),
                                                 byVal(BR_ph),
                                                 byVal(niso));

      for(int i=0; i !=niso; ++i)
      {
        result.set_BBN_abund(i+1,abundances_post[i]);
        for(int j=0; j < niso; ++j)
        {
          result.set_BBN_covmat(i+1,j+1,covariance_post[i*niso+j]);
        }
      }

      // If there are higher and lower abundances, apply photodisintegration on them too
      // and take the uncertainty as the largest difference
      if(result.has_BBN_abund_upper() or result.has_BBN_abund_lower())
      {
        std::vector<double> abundances_upper_post(niso,0.0);
        std::vector<double> abundances_lower_post(niso,0.0);

        for(int i=0; i !=niso; ++i) abundances_pre[i] = result.get_BBN_abund_upper(i+1);
        BEreq::abundance_photodisintegration_decay(abundances_pre.data(),
                                                   covariance_pre.data(),
                                                   abundances_upper_post.data(),
                                                   covariance_post.data(),
                                                   byVal(m_in_MeV),
                                                   byVal(tau),
                                                   byVal(N0a),
                                                   byVal(BR_el),
                                                   byVal(BR_ph),
                                                   byVal(niso));

        for(int i=0; i !=niso; ++i) abundances_pre[i] = result.get_BBN_abund_lower(i+1);
        BEreq::abundance_photodisintegration_decay(abundances_pre.data(),
                                                   covariance_pre.data(),
                                                   abundances_lower_post.data(),
                                                   covariance_post.data(),
                                                   byVal(m_in_MeV),
                                                   byVal(tau),
                                                   byVal(N0a),
                                                   byVal(BR_el),
                                                   byVal(BR_ph),
                                                   byVal(niso));

        for(int i=0; i !=niso; ++i)
        {
          result.set_BBN_abund(i+1,triplet<double>(abundances_post[i], abundances_upper_post[i], abundances_lower_post[i]));
          result.set_BBN_covmat(i+1,i+1,pow(std::max(std::abs(abundances_upper_post[i]-abundances_post[i]),std::abs(abundances_lower_post[i]-abundances_post[i])),2));
          // If the error is larger than the central value, take as error the central value
          if(result.get_BBN_covmat(i+1,i+1) > abundances_post[i]) result.set_BBN_covmat(i+1,i+1,abundances_post[i]);
        }
      }
    }

    /// Extract helium-4 abundance from BBN abundance container
    void extract_helium_abundance(double &result)
    {
      using namespace Pipes::extract_helium_abundance;
      result = Dep::primordial_abundances->get_BBN_abund("He4");
    }

    /// Compute the overall log-likelihood from BBN
    void compute_BBN_LogLike(double &result)
    {
      using namespace Pipes::compute_BBN_LogLike;

      double chi2 = 0;
      int ii = 0;
      int ie,je,s;

      BBN_container BBN_res = *Dep::primordial_abundances; // Fill BBN_container with the values of primordial abundances today

      const std::map<std::string, int>& abund_map = BBN_res.get_abund_map();
      const int niso = BBN_res.get_NNUC();

      // The measurement of the abundance for 3He is done for 3H/D, whereas the computed abundance is 3He/H, so convert it
      int He3 = abund_map.at("He3"), D = abund_map.at("D");
      double YD = BBN_res.get_BBN_abund("D"), YHe3 = BBN_res.get_BBN_abund("He3")/BBN_res.get_BBN_abund("D");
      
      // If the abundance of deuterium is smaller than some arbitrary value, it is effectively zero, so no need to compute anything as the point will be invalidated anyway
      if(YD > 1.0e-20)
      {
        double old_covmat_He3_D = BBN_res.get_BBN_covmat(He3,D);
        BBN_res.set_BBN_abund(He3, YHe3);
        for(int i=1; i<=niso; i++)
        {
          if(i != He3)
          {
            BBN_res.set_BBN_covmat(i, He3, (BBN_res.get_BBN_covmat(i,He3)-BBN_res.get_BBN_covmat(i,D)*YHe3) / YD);
            BBN_res.set_BBN_covmat(He3, i, BBN_res.get_BBN_covmat(i,He3));
          }
          else
          {
            BBN_res.set_BBN_covmat(He3, He3, (YHe3*YHe3)/(YD*YD) * (BBN_res.get_BBN_covmat(He3,He3)/pow(YHe3,2) + BBN_res.get_BBN_covmat(D,D)/pow(YD,2) - 2*old_covmat_He3_D/YD/YHe3));
            // If the uncertainty is negative, it means that the correlations are larger thatn the uncertainties, which is an unphysical point, so invalidate it
            if(BBN_res.get_BBN_covmat(He3,He3) < 0)
            {
              std::ostringstream err;
              err << "Unphysical uncertainties. Invalidating Point.";
              invalid_point().raise(err.str());
            }
          }
        }
      }
      else
      {
        std::ostringstream err;
        err << "Deuterium abundance is too small. Invalidating Point.";
        invalid_point().raise(err.str());
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

        // Check that all isotopes requested in the YAML file exist in the datafile, and keep only the data needed
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
                    "compute likelihoods from in the ObsLikes section of your YAML file as in e.g.\n"
                    "  sub_capabilities: [He4, D]";
          CosmoBit_error().raise(LOCAL_INFO, err);
        }

        // Init out.
        first = false;
      }

      // Init vectors with observations, predictions and covariance matrix
      double prediction[nobs],observed[nobs],sigmaobs[nobs],translate[nobs];
      bool upperlimit[nobs];
      gsl_matrix *cov = gsl_matrix_alloc(nobs, nobs);
      gsl_matrix *invcov = gsl_matrix_alloc(nobs, nobs);
      gsl_permutation *p = gsl_permutation_alloc(nobs);

      // Iterate through observation dictionary to fill observed, sigmaobs and prediction arrays
      for(std::map<std::string,std::vector<double>>::iterator iter = dict.begin(); iter != dict.end(); ++iter)
      {
        std::string key = iter->first; // iter = ["element key", [mean, sigma, upper_limit]]
        if(abund_map.count(key)!=1)   // throw error if element not contained in abundance map was entered in data file
        {
          std::ostringstream err;
          err << "Unknown element '"<< key <<"' in BBN data file '"<< filename<<"'. \nYou can only enter 'Yp' or 'He4', 'D' or 'H2', 'He3', 'Li7'.";
          CosmoBit_error().raise(LOCAL_INFO, err.str());
        }
        translate[ii]=abund_map.at(key); // to order observed and predicted abundances consistently
        observed[ii]=iter->second[0];
        sigmaobs[ii]=iter->second[1];
        upperlimit[ii] = round(iter->second[2]);
        prediction[ii]= BBN_res.get_BBN_abund(key);
        ii++;
      }

      // Fill the covariance matrix
      for(ie=0;ie<nobs;ie++) {for(je=0;je<nobs;je++) gsl_matrix_set(cov, ie, je,pow(sigmaobs[ie],2.)*(ie==je)+BBN_res.get_BBN_covmat(translate[ie], translate[je]));}

      // Compute the LU decomposition and inverse of covariance matrix
      gsl_linalg_LU_decomp(cov,p,&s);
      gsl_linalg_LU_invert(cov,p,invcov);

      // Compute the determinant of the inverse of the covariance matrix
      double det_cov = gsl_linalg_LU_det(cov,s);

      // compute chi2
      for(ie=0;ie<nobs;ie++)
      {
        for(je=0;je<nobs;je++)
        {
          if( (not upperlimit[ie] or prediction[ie] > observed[ie]) and
              (not upperlimit[je] or prediction[je] > observed[je]) )
            chi2+=(prediction[ie]-observed[ie])*gsl_matrix_get(invcov,ie,je)*(prediction[je]-observed[je]);
        }
      }
      result = -0.5*(chi2 + log(pow(2*pi,nobs)*det_cov));

      logger() << "BBN LogLike computed to be: " << result << EOM;

      gsl_matrix_free(cov);
      gsl_matrix_free(invcov);
      gsl_permutation_free(p);
    }

  } // namespace CosmoBit

} // namespace Gambit
