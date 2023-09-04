//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  Prior function made up of two log priors
///  (positive and negative branch) joined across
///  zero by a flat region.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///   
///  \author Ben Farmer
///          (benjamin.farmer@fysik.su.se)
///  \date 2016 Jun
///
///  *********************************************

#ifndef PRIOR_DOUBLELOGFLATJOIN_HPP
#define PRIOR_DOUBLELOGFLATJOIN_HPP

#include "gambit/ScannerBit/priors.hpp"
#include "gambit/Utils/yaml_options.hpp"

#include <vector>
  
namespace Gambit
{
   namespace Priors
   {
      /// 1D double log prior with flat bridge over zero.
      /// (for creating a prior similar to log that works across positive and negative values continuously).
      /// Takes the arguments: [minval : flat_start : flat_end : maxval]
      class DoubleLogFlatJoin : public BasePrior
      {
      private:
         /// Name of the parameter that this prior is supposed to transform
         const std::string &myparameter;
         /// Variables controlling the prior range etc.
         /// @{
         double lower;
         double flat_start;
         double flat_end;
         double upper;
         /// @}
         /// Useful quantities
         /// @{
         double C; 
         double P01;
         double P12;
         double P23;
         /// @}

         /// Flags to register if special cases are active.
         /// @{
         bool no_lower_log;
         bool no_upper_log;
         /// @}
	 
         /// Try to get options for double log-flat joined prior
         double get_option(const str&, const Options&);

      public: 
         /// Constructor defined in doublelogflatjoin.cpp
         DoubleLogFlatJoin(const std::vector<std::string>& param, const Options&); 

         /// Transformation from unit interval to the double log + flat join (inverse prior transform)
         void transform(const std::vector <double> &unitpars, std::unordered_map <std::string, double> &output) const override;
         std::vector<double> inverse_transform(const std::unordered_map<std::string, double> &) const override;

         /// Probability density function
         double operator()(const std::vector<double> &vec) const override;
      };
  
      LOAD_PRIOR(double_log_flat_join, DoubleLogFlatJoin)
   }
}

#endif
