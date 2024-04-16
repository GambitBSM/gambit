//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  AnalysisLogLikes struct.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Anders Kvellestad
///          (anders.kvellestad@fys.uio.no)
///  \date 2021 Jun
///
///  *********************************************

#pragma once

#include <string>
#include <vector>
#include <map>

// #define ANALYSISLOGLIKES_DEBUG

#ifdef ANALYSISLOGLIKES_DEBUG
#include <iostream>
#endif


namespace Gambit
{
  namespace ColliderBit
  {

    /// @brief Container for loglike information for an analysis
    struct AnalysisLogLikes
    {
      // Signal region labels
      std::vector<std::string> sr_labels;

      // The "observed" log-likelihood (per SR)
      std::vector<double> sr_loglikes;

      // Map of vectors of alternative log-likelihoods (per SR)
      std::map<std::string, std::vector<double>> alt_sr_loglikes;

      std::string combination_sr_label;
      int combination_sr_index;
      double combination_loglike;
      std::map<std::string, double> alt_combination_loglikes;

      AnalysisLogLikes() :
        combination_sr_label("undefined"),
        combination_sr_index(-2),
        combination_loglike(0.0)
        { }

      // Get the number of SRs and the correponding SR labels from
      // an AnalysisData instance. Use this to initialize.
      void initialize(const AnalysisData& adata_in, const std::vector<std::string>& alt_loglike_keys = {})
      {
        const size_t n_sr = adata_in.size();

        for (size_t sr_index = 0; sr_index < n_sr; ++sr_index)
        {
          const std::string& sr_label = adata_in.srdata[sr_index].sr_label;
          sr_labels.push_back(sr_label);
          sr_loglikes.push_back(0.0);
        }

        // Initialize map of alternative SR loglikes,
        // and vector of alternative combined loglikes
        for (const std::string& key : alt_loglike_keys)
        {
          alt_sr_loglikes[key] = std::vector<double>(n_sr, 0.0);
          alt_combination_loglikes[key] = 0.0;
        }

      }

      void set_no_signal_result_combination(std::string combination_sr_label_in, int combination_sr_index_in)
      {
        // Fill the variables for the combined result
        combination_sr_index = combination_sr_index_in;
        combination_sr_label = combination_sr_label_in;
        combination_loglike = 0.0;
        for (auto& map_element : alt_combination_loglikes)
        {
          map_element.second = 0.0;
        }
      }

      void set_no_signal_result_all_SRs(std::string combination_sr_label_in, int combination_sr_index_in)
      {
        // Fill the variables for the combined result
        set_no_signal_result_combination(combination_sr_label_in, combination_sr_index_in);

        // Fill the vectors of per-SR results
        std::fill(sr_loglikes.begin(), sr_loglikes.end(), 0);
        for (auto& map_element : alt_sr_loglikes)
        {
          std::fill(map_element.second.begin(), map_element.second.end(), 0);
        }

      }

    };

  }
}
