//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Helper utilities for FlavBit
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@kit.edu)
///  \date 2022 Aug
///
///  *********************************************


#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/FlavBit/FlavBit_rollcall.hpp"
#include "gambit/FlavBit/FlavBit_utils.hpp"

namespace Gambit
{

  namespace FlavBit
  {

    /// Some constants used in SuperIso likelihoods
    const int ncorrnuis = 508;
    const nuiscorr (&nuiscorr_help(nuiscorr (&arr)[ncorrnuis], const std::vector<nuiscorr>& v))[ncorrnuis] { std::copy(v.begin(), v.end(), arr); return arr; }
    nuiscorr arr[ncorrnuis];
    const nuiscorr (&corrnuis)[ncorrnuis] = nuiscorr_help(arr, YAML::LoadFile(GAMBIT_DIR "/FlavBit/data/SM_nuisance_correlations.yaml")["correlation_matrix"].as<std::vector<nuiscorr>>());

    /// Print function for FlavBit predictions
    void print(flav_prediction prediction , std::vector<std::string > names)
    {
      for(unsigned i=0; i<names.size(); i++)
      {
        std::cout<<names[i]<<": "<<prediction.central_values[names[i]]<< std::endl;
      }
      std::cout<<"Covariance:"<< std::endl;
      for( unsigned i=0; i<names.size(); i++)
      {
        std::stringstream row;
        for( unsigned j=0; j<names.size(); j++)
        {
          row<<(prediction.covariance)[names[i]]  [names[j]]<<" ";
        }
        std::cout<<row.str()<< std::endl;
      }
    }

    /// Translate B->K*ll observables from theory to LHCb convention
    void Kstarll_Theory2Experiment_translation(flav_observable_map& prediction, int generation)
    {
      // Only works for ll = ee and ll = mumu
      if (generation < 1 or generation > 2)
       FlavBit_error().raise(LOCAL_INFO, "Kstarll_Theory2Experiment_translation called with generation not 1 or 2");
      const std::vector<std::string> all_names[2] = {{"AT_Im"} , {"S4", "S7", "S9"}};
      const std::vector<std::string>& names = all_names[generation-1];
      for (unsigned i=0; i < names.size(); i++)
      {
        auto search = prediction.find(names[i]);
        if (search != prediction.end())
        {
          prediction[names[i]]=(-1.)*prediction[names[i]];
        }
      }
    }

    /// Translate B->K*ll covariances from theory to LHCb convention
    void Kstarll_Theory2Experiment_translation(flav_covariance_map& prediction, int generation)
    {
      // Only works for ll = ee and ll = mumu
      if (generation < 1 or generation > 2)
       FlavBit_error().raise(LOCAL_INFO, "Kstarll_Theory2Experiment_translation called with generation not 1 or 2");

      const std::vector<std::string> names[2] = {{"AT_Im"} , {"S4", "S7", "S9"}};
      std::vector<std::string> names_exist;

      for (unsigned i=0; i < names[generation-1].size(); i++)
      {
        auto search_i = prediction.find(names[generation-1][i]);
        if (search_i != prediction.end()) names_exist.push_back(names[generation-1][i]);
      }
      //changing the rows:
      for (unsigned i=0; i <  names_exist.size(); i++)
      {
        std::string name1=names_exist[i];
        std::map<std::string, double> row=prediction[name1];
        for (std::map<std::string, double>::iterator it=row.begin(); it !=row.end(); it++)
        {
          prediction[name1][it->first]=(-1.)*prediction[name1][it->first];
        }
      }
      // changing the columns:
      for (flav_covariance_map::iterator it=prediction.begin(); it !=prediction.end(); it++)
      {
        std::string name_columns=it->first;
        for (unsigned i=0; i <  names_exist.size(); i++)
        {
          std::string name1=names_exist[i];
          prediction[name_columns][name1]=(-1)*prediction[name_columns][name1];
        }
      }
    }

    /// Find the path to the latest installed version of the HepLike data
    str path_to_latest_heplike_data()
    {
      std::vector<str> working_data = Backends::backendInfo().working_versions("HepLikeData");
      if (working_data.empty()) FlavBit_error().raise(LOCAL_INFO, "No working HepLikeData installations detected.");
      std::sort(working_data.begin(), working_data.end());
      return Backends::backendInfo().corrected_path("HepLikeData", working_data.back());
    }

    str heplike_data_file(str filename)
    {
      str filepath = path_to_latest_heplike_data() + filename;
      if(not Utils::file_exists(filepath))
        FlavBit_error().raise(LOCAL_INFO, "HepLikeData file " + filepath + " not found");
      return filepath;
    }

    /// Extract central values of the given observables from the central value map.
    std::vector<double> get_obs_theory(const flav_prediction& prediction, const std::vector<std::string>& observables)
    {
      if(flav_debug) std::cout<<"In get_obs_theory() function"<<std::endl;
      std::vector<double> obs_theory;
      obs_theory.reserve(observables.size());
      for (unsigned int i = 0; i < observables.size(); ++i)
      {
        if(flav_debug) std::cout<<"Trying to find: "<<observables[i]<<std::endl;
        obs_theory.push_back(prediction.central_values.at(observables[i]));
      }
      return obs_theory;
    };

    /// Extract central value of the given observable from the central value map.
    double get_obs_theory(const flav_prediction& prediction, const std::string& observable)
    {
      return prediction.central_values.at(observable);
    };

    /// Reorder a FlavBit observables list to match ordering expected by HEPLike
    void update_obs_list(std::vector<str>& obs_list, const std::vector<str>& HL_obs_list)
    {
      std::vector<str> FB_obs_list = translate_flav_obs("HEPLike", "FlavBit", HL_obs_list);
      std::vector<str> temp;
      for (auto it = FB_obs_list.begin(); it != FB_obs_list.end(); ++it)
      {
        if (std::find(obs_list.begin(), obs_list.end(), *it) != obs_list.end())
        {
          temp.push_back(*it);
        }
      }
      obs_list = temp;
    }

    /// Extract covariance matrix of the given observables from the covariance map.
    boost::numeric::ublas::matrix<double> get_obs_covariance(const flav_prediction& prediction, const std::vector<std::string>& observables)
    {
      boost::numeric::ublas::matrix<double> obs_covariance(observables.size(), observables.size());
      for (unsigned int i = 0; i < observables.size(); ++i)
      {
        for (unsigned int j = 0; j < observables.size(); ++j)
        {
          obs_covariance(i, j) = prediction.covariance.at(observables[i]).at(observables[j]);
        }
      }
      return obs_covariance;
    };

    /// Extract uncertainty of the given observable from the covariance map.
    double get_obs_covariance(const flav_prediction& prediction, const std::string& observable)
    {
      return prediction.covariance.at(observable).at(observable);
    };

    /// Helper function to avoid code duplication.
    void SuperIso_prediction_helper(const std::vector<std::string>& FB_obslist, const std::vector<std::string>& SI_obslist, flav_prediction& result,
                                    const parameters& param, const nuisance& nuislist,
                                    void (*get_predictions_nuisance)(char**, int*, double**, const parameters*, const nuisance*),
                                    void (*observables)(int, obsname*, int, double*, double*, const nuisance*, char**, const parameters*),
                                    void (*convert_correlation)(nuiscorr*, int, double**, char**, int),
                                    void (*get_th_covariance_nuisance)(double***, char**, int*, const parameters*, const nuisance*, double**),
                                    bool useSMCovariance,
                                    bool SMCovarianceCached
                                    )
    {
      if (flav_debug)
      {
        std::cout << "Starting SuperIso_prediction" << std::endl;
      }

      int nObservables = SI_obslist.size();
      if (flav_debug) std::cout<<"Observables: "<<std::endl;

      char obsnames[nObservables][50];
      for(int iObservable = 0; iObservable < nObservables; iObservable++)
      {
        strcpy(obsnames[iObservable], SI_obslist[iObservable].c_str());
        if( flav_debug) std::cout<<SI_obslist[iObservable].c_str()<<std::endl;
      }

      // ---------- CENTRAL VALUES ----------
      double *result_central;

      // Reserve memory
      result_central = (double *) calloc(nObservables, sizeof(double));

      // Needed for SuperIso backend
      get_predictions_nuisance((char**)obsnames, &nObservables, &result_central, &param, &nuislist);

      // Compute the central values
      for(int iObservable = 0; iObservable < nObservables; ++iObservable)
      {
        result.central_values[FB_obslist[iObservable]] = result_central[iObservable];
      }

      // Free memory
      free(result_central);
      result_central = NULL;

      if (flav_debug)
      {
        for(int iObservable = 0; iObservable < nObservables; ++iObservable)
        {
          printf("%s=%.4e\n", obsnames[iObservable], result.central_values[FB_obslist[iObservable]]);
        }
      }

      //Switch the observables to LHCb convention
      Kstarll_Theory2Experiment_translation(result.central_values, 1);
      Kstarll_Theory2Experiment_translation(result.central_values, 2);

      // If we need to compute the covariance, either because we're doing it for every point or we haven't cached the SM value, do it.
      if (not useSMCovariance or not SMCovarianceCached)
      {

        // ---------- COVARIANCE ----------
        static bool first = true;
        static const int nNuisance=171;
        static char namenuisance[nNuisance+1][50];
        static double **corr=(double  **) malloc((nNuisance+1)*sizeof(double *));  // Nuisance parameter correlations

        if (first)
        {
          observables(0, NULL, 0, NULL, NULL, &nuislist, (char **)namenuisance, &param); // Initialization of namenuisance

          // Reserve memory
          for(int iObservable = 0; iObservable <= nNuisance; ++iObservable)
          {
            corr[iObservable]=(double *) malloc((nNuisance+1)*sizeof(double));
          }

          // Needed for SuperIso backend
          convert_correlation((nuiscorr *)corrnuis, byVal(ncorrnuis), (double **)corr, (char **)namenuisance, byVal(nNuisance));

          first = false;
        }

        double **result_covariance;

        if (useSMCovariance)
        {
          // Copy the parameters and set all Wilson Coefficients to 0 (SM values)
          parameters param_SM = param;
          for(int ie=1;ie<=30;ie++)
          {
            param_SM.deltaC[ie]=0.;
            param_SM.deltaCp[ie]=0.;
          }
          for(int ie=1;ie<=6;ie++)
          {
            param_SM.deltaCQ[ie]=0.;
            param_SM.deltaCQp[ie]=0.;
          }
          // Use the SM values of the parameters to calculate the SM theory covariance.
          get_th_covariance_nuisance(&result_covariance, (char**)obsnames, &nObservables, &param_SM, &nuislist, (double **)corr);
        }
        else
        {
          // Calculate covariance at the new physics point.
          get_th_covariance_nuisance(&result_covariance, (char**)obsnames, &nObservables, &param, &nuislist, (double **)corr);
        }

        // Fill the covariance matrix in the result structure
        for(int iObservable=0; iObservable < nObservables; ++iObservable)
        {
          for(int jObservable = 0; jObservable < nObservables; ++jObservable)
          {
            result.covariance[FB_obslist[iObservable]][FB_obslist[jObservable]] = result_covariance[iObservable][jObservable];
          }
        }

        // Free memory for result_covariance
        for(int iObservable = 0; iObservable < nObservables; ++iObservable) free(result_covariance[iObservable]);
        free(result_covariance);

        //Switch the covariances to LHCb convention
        Kstarll_Theory2Experiment_translation(result.covariance, 1);
        Kstarll_Theory2Experiment_translation(result.covariance, 2);

        // We are not freeing the memory because we made the variable static.
        // Just keeping this for reference on how to clean up the allocated
        // memory in case of non-static calculation of **corr.
        // Free memory
        //for(int iObservable = 0; iObservable <= nNuisance; ++iObservable) free(corr[iObservable]);
        //free(corr);
      }

      if (flav_debug)
      {
        for(int iObservable=0; iObservable < nObservables; ++iObservable)
        {
          for(int jObservable = iObservable; jObservable < nObservables; ++jObservable)
          {
            printf("Covariance %s - %s: %.4e\n",
              obsnames[iObservable], obsnames[jObservable], result.covariance[FB_obslist[iObservable]][FB_obslist[jObservable]]);
           }
        }
        std::cout << "Finished SuperIso_prediction" << std::endl;
      }

    }

  }

}
