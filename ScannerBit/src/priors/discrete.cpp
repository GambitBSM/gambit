//  GAMBIT: Global and Modular BSM Inference Tool
//  **********************************************
///  \file
///
///  Prior function that implements a discrete
///  distribution from a user-provided list of
///  values (and possibly associated frequencies).
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Sebastian Hoof
///          (s.hoof.physics@gmail.com)
///  \date 2021 Mar
///        2024 Feb
///
///  *********************************************

#include "gambit/ScannerBit/priors/discrete.hpp"
#include "gambit/Utils/yaml_options.hpp"

#include <algorithm>
#include <list>


namespace Gambit
{
  namespace Priors
  {

    Discrete::Discrete(const std::vector<std::string>& param, const Options& options)
      : BasePrior(param, 1)
      , myparameter(param_names[0])
      {
        bool is_1d = true;
        std::vector <double> param_data;
        // Use lists because they are more efficient for deleting elements 
        std::list<double> param_values;
        std::list<double> param_frequency;
        // Only intended for 1D parameter transformations
        if (param.size() != 1)
        {
          scan_err << "Invalid input to Discrete prior (in constructor): " << endl
                   << "This prior only works with one-dimensional parameters. "
                   << "Input parameters must be a vector of size 1! (has size " << param.size()
                   << ")" << scan_end;
        }

        // Read the entries we need from the options and check for consistency
        if ( options.hasKey("hist_data") )
        {
          // Get the histogram from the YAML file
          param_data = options.getValue<std::vector<double>>("hist_data");
          if ( options.hasKey("hist_file") )
          {
            scan_err << "You specified both 'hist_data' and 'hist_file' as inputs for the Discrete prior. "
                     << "Please only specify one options." << endl;
          }
        }
        else if ( options.hasKey("hist_file") )
        {
          // Read column of a data file to get the histogram
          std::string file = options.getValue<std::string>("hist_file");
          ASCIItableReader data (file);
          if (data.getnrow() < 2) {
            scan_err << "The file for the Discrete prior contains only one row. If you did this intentionally, "
                     << "use a 'fixed_prior' instead. The expected format is either one column of numbers or two "
                     << "columns, where the 2nd column specifies the relative frequency." << endl;
          }
          if (data.getncol() > 2) { scan_warn << "Detected more than 2 columns in the data file; the additional columns will be ignored."; }
          param_data = data[0];
          if (data.getncol() == 2)
          {
            is_1d = false;
            param_frequency.assign(data[1].begin(), data[1].end());
          }
        }
        else
        {
          scan_err << "You need to specify either the 'hist_data' option or the 'hist_file' option "
                   << "in order for the Discrete prior to work." << endl;
        }

        if (is_1d) { param_frequency.assign(param_data.size(), 1.0); }
        param_values.assign(param_data.begin(), param_data.end());

        // Sort and delete non-unique entries
        unique_params = param_data;
        std::sort(unique_params.begin(), unique_params.end());
        unique_params.erase(std::unique(unique_params.begin(), unique_params.end()), unique_params.end());
        pmf_values.clear();
        cmf_values.clear();
        // Iterate through all the entries to compute the PMF and CMF
        double total = 0;
        for (auto upar = unique_params.begin(); upar != unique_params.end(); upar++)
        {
          // Initialize a new PMF total
          pmf_values.push_back(0);
          // Credit to Michael Kristofik (https://stackoverflow.com/a/596180) for deleting-while-iterating routine
          auto par = param_values.begin();
          auto freq = param_frequency.begin();
          // Need a while loop since we'll be deleting elements
          while (par != param_values.end())
          {
            if (*upar == *par)
            {
              pmf_values.back() += *freq;
              total += *freq;
              /// Remove these entries since we don't need to consider them anymore
              param_frequency.erase(freq++);
              param_values.erase(par++);
            }
            else
            {
              ++par;
              ++freq;
            }
          }
          // Now add the running total to the CMF
          cmf_values.push_back(total);
        }
        // Normalise all PMF and CMF values, and take the log of PMF
        for (size_t i = 0; i < pmf_values.size(); ++i)
        {
          pmf_values[i] = log(pmf_values[i]/total);
          cmf_values[i] /= total;
        }
      }

      void Discrete::transform(hyper_cube_ref<double> unitpars, std::unordered_map<std::string, double> &physicalpars) const
      {
        // Use std::lower_bound to ensure that both u=0 and u=1 will result in a match
        auto lower = std::lower_bound(cmf_values.begin(), cmf_values.end(), unitpars[0]);
        size_t index = std::distance(cmf_values.begin(), lower);
        physicalpars[myparameter] = unique_params[index];
      }

      void Discrete::inverse_transform(const std::unordered_map<std::string, double> &physicalpars, hyper_cube_ref<double> unitpars) const
      {
        // Use std::lower_bound to ensure a match
        const double x = physicalpars.at(myparameter);
        auto lower = std::lower_bound(unique_params.begin(), unique_params.end(), x);
        size_t index = std::distance(unique_params.begin(), lower);
        unitpars[0] = cmf_values[index];
      }

      double Discrete::log_prior_density(const std::unordered_map<std::string, double> &physicalpars) const
      {
        // Use std::lower_bound to ensure a match
        const double x = physicalpars.at(myparameter);
        auto lower = std::lower_bound(unique_params.begin(), unique_params.end(), x);
        size_t index = std::distance(unique_params.begin(), lower);
        return pmf_values[index];
      }
   }
}
