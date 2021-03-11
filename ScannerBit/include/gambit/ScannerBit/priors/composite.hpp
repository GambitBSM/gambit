//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  Prior object construction routines
///  
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///   
///  \author Ben Farmer
///          (benjamin.farmer@monash.edu.au)
///  \date 2013 Dec
///
///  \author Gregory Martinez
///          (gregory.david.martinez@gmail.com)
///  \date 2014 Feb
///
///  *********************************************

#ifndef PRIOR_COMPOSITE_HPP
#define PRIOR_COMPOSITE_HPP

#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <iostream>

#include "gambit/Utils/yaml_options.hpp"
#include "gambit/ScannerBit/priors.hpp"


namespace Gambit 
{
    namespace Priors 
    {
        /// Special "build-a-prior" class
        /// This is the class to use for setting simple 1D priors (from the library above) on individual parameters.
        /// It actually also allows for any combination of MD priors to be set on any combination of subspaces of
        /// the full prior.

        class CompositePrior : public BasePrior
        {
                        
        private:
            // References to component prior objects
            std::vector<BasePrior*> my_subpriors;
            std::vector<std::string> shown_param_names;
                
        public:
        
            // Constructors defined in composite.cpp
            CompositePrior(const Options &model_options, const Options &prior_options);
            
            CompositePrior(const std::vector<std::string> &params, const Options &options);
            
            inline std::vector<std::string> getShownParameters() const {return shown_param_names;}
            
            // Transformation from unit hypercube to my_ranges
            void transform(const std::vector<double> &unitPars, std::unordered_map<std::string,double> &outputMap) const
            {
                std::vector<double>::const_iterator unit_it = unitPars.begin(), unit_next;
                for (auto it = my_subpriors.begin(), end = my_subpriors.end(); it != end; it++)
                {
                    unit_next = unit_it + (*it)->size();
                    std::vector<double> subUnit(unit_it, unit_next);
                    unit_it = unit_next;
                    (*it)->transform(subUnit, outputMap);
                }
            }
            
            //~CompositePrior() noexcept
            ~CompositePrior()
            {
                // Need to destroy all the prior objects that we created using 'new'
                for (auto it = my_subpriors.begin(), end = my_subpriors.end(); it != end; it++)
                {  
                    // Delete prior object
                    delete *it;
                }
            }  
        };
            
        LOAD_PRIOR(composite, CompositePrior)
    } // end namespace Priors
} // end namespace Gambit

#endif
