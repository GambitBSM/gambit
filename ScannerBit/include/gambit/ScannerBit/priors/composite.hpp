//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  Combine several priors to a prior for
///  e.g. an entire model
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
#include "gambit/ScannerBit/scanner_utils.hpp"


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
            
            double log_prior_density(const std::unordered_map<std::string, double> &physical) const override 
            {
                double log_pdf_density = 0.0;
                for (auto it = my_subpriors.begin(), end = my_subpriors.end(); it != end; ++it)
                {
                    log_pdf_density += (*it)->log_prior_density(physical);
                }
                
                return log_pdf_density;
            }
            
            inline std::vector<std::string> getShownParameters() const override { return shown_param_names; }
            
            // Transformation from unit hypercube to physical parameters
            void transform(hyper_cube_ref<double> unitPars, std::unordered_map<std::string,double> &outputMap) const override
            {
                int unit_i = 0, unit_size;
                for (auto it = my_subpriors.begin(), end = my_subpriors.end(); it != end; ++it)
                {
                    unit_size = (*it)->size();
                    (*it)->transform(unitPars.segment(unit_i, unit_size), outputMap);
                    unit_i += unit_size;
                }
            }

            // Transformation from physical parameters back to unit hypercube
            void inverse_transform(const std::unordered_map<std::string, double> &physical, hyper_cube_ref<double> unit) const override
            {
                int unit_i = 0, unit_size;
                for (auto it = my_subpriors.begin(), end = my_subpriors.end(); it != end; it++)
                {
                    unit_size = (*it)->size();
                    (*it)->inverse_transform(physical, unit.segment(unit_i, unit_size));
                    unit_i += unit_size;
                }

                // Check it
                for (int i = 0, end = unit.size(); i < end; ++i)
                {
                    if (unit[i] >= 1 || unit[i] <= 0)
                    {
                        scan_warn << "unit hypercube outside 0 and 1" << scan_end;
                    }
                }

                auto round_trip = physical;
                transform(unit, round_trip);
                const double rtol = 1e-4;
                for (const auto &s : physical) 
                {
                    const double a = round_trip.at(s.first);
                    const double b = s.second;
                    const double rdiff = std::abs(a - b) / std::max(std::abs(a), std::abs(b));
                    if (rdiff > rtol)
                    {
                        scan_err << "could not convert physical parameters to hypercube" << scan_end;
                    }
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
