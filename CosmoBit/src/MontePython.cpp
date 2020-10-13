//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  CosmoBit routines relating to MontePython interface.
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
///  *********************************************

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/CosmoBit/CosmoBit_rollcall.hpp"
#include "gambit/CosmoBit/CosmoBit_types.hpp"


namespace Gambit
{

  namespace CosmoBit
  {

    using namespace LogTags;
    
    #ifdef HAVE_PYBIND11

      /***************/
      /* MontePython */
      /***************/

      /// Function to fill the mcmc_parameters dictionary of MontePython's Data object
      /// with current values of nuisance parameters.
      void set_parameter_dict_for_MPLike(pybind11::dict & result)
      {
        using namespace Pipes::set_parameter_dict_for_MPLike;
        using namespace pybind11::literals;

        // The loop has to be executed for every parameter point. It takes about 0.00023s -> ~4 minutes for 1e6 points
        for (auto it=Param.begin(); it != Param.end(); it++)
        {
          std::string name = it->first;
          double value = *Param[name];

          // Check if any models are scanned for which we had to rename the nuisance parameters due to:
          //    a) parameters having the same name  -> e.g. 'epsilon' and 'sigma_NL'
          //    b) parameter names containing symbols that can't be used in macros -> e.g. "^" in 'beta_0^Euclid'

          // a) have to rename parameters epsilon_ska, epsilon_euclid,.. to "epsilon" as they are implemented in MontePython
          if (name.find("epsilon") != std::string::npos){name="epsilon";}

          // a) have to rename parameters sigma_NL_ska, sigma_NL_euclid,.. to "sigma_NL" as they are implemented in MontePython
          else if (name.find("sigma_NL") != std::string::npos){name="sigma_NL";}

          // b) get the "^" characters back into the parameter names
          //   -> beta_x<experiment> has to be beta_x^<experiment> where x = 0 or 1 and <experiment> = Euclid, SKA1 or SKA2
          // ATM this is the case for  "cosmo_nuisance_euclid_pk" and "cosmo_nuisance_ska" models
          else if (name.find("beta_")!= std::string::npos){name = name.insert(6,"^");}

          result[name.c_str()] = pybind11::dict("current"_a=value,"scale"_a=1.); // scale always 1 in GAMBIT
        
        }
      }

      /// Function to fill the mcmc_parameters dictionary of MontePython's Data object with an empty dictionary.
      /// This version of the capability 'parameter_dict_for_MPLike' is used when no Likelihood with nuisance
      /// parameters are in use, and just passes an empty Python dictionary
      void pass_empty_parameter_dict_for_MPLike(pybind11::dict & result)
      {
        using namespace Pipes::pass_empty_parameter_dict_for_MPLike;

        static bool first = true;
        
        if (first)
        {
          result = pybind11::dict();
          first = false;
        }
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
          // Using the default datafile can be achieved by leaving the datafile out, or setting it to "default".
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

      /// Computes lnL for each experiment initialised in MontePython
      void compute_MP_LogLikes(map_str_dbl & result)
      {
        using namespace Pipes::compute_MP_LogLikes;

        static bool first_run = true;
        static pybind11::object data = std::get<0>(*Dep::MP_objects);
        static const map_str_str& experiments = std::get<1>(*Dep::MP_objects);
        static const map_str_pyobj& likelihoods = std::get<2>(*Dep::MP_objects);
        static const MPLike_data_container mplike_cont(data, likelihoods);

        // in the first run test if any unused nuisance parameters are passed
        // to MontePython. If so this function will throw an error identifying
        // the parameter that is scanned over but not in use.
        if(first_run) mplike_cont.data.attr("check_nuisance_params")();

        // get classy backend directory. The only reason we need to pass this
        // to MP is because the likelihood 'sdss_lrgDR7' requires pre-computed fiducial spectra.
        // These can, in general, depend on the CLASS version they were calculated with (if the 
        // treatment of non-linearities changes). To make sure the fiducial spectra and the ones
        // for each point in parameter space are computed with the same CLASS version, we pass the 
        // CLASS version to MP. The fiducial spectra are automatically calculated when CLASS is build.
        static std::string backendDir = BEreq::get_classy_backendDir();
        mplike_cont.data.attr("set_class_version")(backendDir);

        // Pass current values of nuisance parameters to data.mcmc_parameters dictionary for likelihood computation in MP
        mplike_cont.data.attr("mcmc_parameters") = *Dep::parameter_dict_for_MPLike;

        // Create instance of classy class Class
        pybind11::object cosmo = BEreq::get_classy_cosmo_object();

        // Loop through the list of experiments, and query the lnL from the MontePython backend.
        for (sspair it : experiments)
        {
          // perform check if all requested MP likelihoods are compatible 
          // with CLASS version in use. 
          // Got to do that here, as the MP data object gets the information 
          // about the classy version a few lines above through the BEreq
          // get_classy_backendDir()
          if(first_run)
          {
            BEreq::check_likelihood_classy_combi(it.first,backendDir);
          }

          // Likelihood names are keys of experiment map (str, str map mapping likelihood name to .data file)
          double logLike = BEreq::get_MP_loglike(mplike_cont, cosmo, it.first);
          result[it.first] = logLike;
          logger() << "(compute_MP_LogLikes):  name: " << it.first << "\tvalue: " << logLike << EOM;
        }
        first_run = false;
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

      /// Get correlation coefficients and uncorrelated likelihood
      /// of MP likelihood "bao_correlations".
      /// Warning: this routine is specific to this likelihood, don't use for anything else!
      void get_bao_like_correlation(map_str_dbl& result)
      {
        using namespace Pipes::get_bao_like_correlation;

        // This function has a dependency on MP_LogLikes even though it is not directly
        // needed in the calculation. However, through this dependency we make sure that
        // MP was called before this function is executed -> don't remove it!

        // Get map containing python likelihood objects
        static const map_str_pyobj& likelihoods = std::get<2>(*Dep::MP_objects);

        // Check if "bao_correlations" likelihood was computed, if so
        // retrieve correlation coefficients and uncorrelated likelihood value
        if(likelihoods.find("bao_correlations") != likelihoods.end())
        {
            result["uncorrelated_loglike"] = likelihoods.at("bao_correlations").attr("uncorrelated_loglike").cast<double>();
            pybind11::list corr_coeffs =  likelihoods.at("bao_correlations").attr("correlation_coeffs");
            result["correlation_coeffs_0"] = corr_coeffs[0].cast<double>();
            result["correlation_coeffs_1"] = corr_coeffs[1].cast<double>();
            result["correlation_coeffs_2"] = corr_coeffs[2].cast<double>();
        }
        else
        {
            str errmsg = "Likelihood 'bao_correlations' was not requested in the YAML file, but you are asking for\n";
            errmsg += "the correlation coefficients from this likelihood. Either remove 'bao_like_correlation' from the ObsLikes section\n";
            errmsg += "in your YAML file or include the computation of the 'bao_correlations' likelihood by adding:\n\n";
            errmsg += "  - purpose:      LogLike\n";
            errmsg += "    capability:   MP_Combined_LogLike\n";
            errmsg += "    sub_capabilities:\n";
            errmsg += "      - bao_correlations\n\n";
            errmsg += "to the YAML file.";
            CosmoBit_error().raise(LOCAL_INFO, errmsg);
        }
      }

  #endif

  } // namespace CosmoBit

} // namespace Gambit
