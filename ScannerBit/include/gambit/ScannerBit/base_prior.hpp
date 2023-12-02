//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  Abstract base class for a prior
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ben Farmer
///      (benjamin.farmer@monash.edu.au)
///  \date 2013 Dec
///
///  \author Gregory Martinez
///      (gregory.david.martinez@gmail.com)
///  \date 2014 Feb
///
///  \author Andrew Fowlie
///    (andrew.j.fowlie@qq.com)
///  \date August 2020
///
///  *********************************************

#ifndef __BASE_PRIORS_HPP__
#define __BASE_PRIORS_HPP__

#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

#include "gambit/ScannerBit/scanner_utils.hpp"

namespace Gambit {

    namespace Priors {

        using ::Gambit::Scanner::hyper_cube_ref;
        using ::Gambit::Scanner::map_vector;

        /**
        * @brief Abstract base class for priors
        */
        class BasePrior 
        {
        private:
            unsigned int param_size;

        protected:
            std::vector<std::string> param_names;

        public:
            virtual ~BasePrior() = default;

            BasePrior() : param_size(0), param_names(0) {}

            explicit BasePrior(const int param_size) : param_size(param_size), param_names(0) {}

            explicit BasePrior(const std::vector<std::string> &param_names, const int param_size = 0) :
                param_size(param_size), param_names(param_names) {}

            explicit BasePrior(const std::string &param_name, const int param_size = 0) :
                param_size(param_size), param_names(1, param_name) {}

            /** @brief Transform from unit hypercube to physical parameter */
            virtual void transform(hyper_cube_ref<double> unit, std::unordered_map<std::string, double> &physical) const = 0;

            /** @overload in place STL containers */
            void transform(const std::vector<double> &unit, std::unordered_map<std::string, double> &physical) const 
            {
                transform(map_vector<double>(const_cast<double *>(&unit[0]), unit.size()), physical);
            }

            /** @overload return STL containers */
            std::unordered_map<std::string, double> transform(const std::vector<double> &unit) const 
            {
                std::unordered_map<std::string, double> physical;
                transform(unit, physical);
                return physical;
            }

            /** @brief Transform from physical parameter to unit hypercube */
            virtual void inverse_transform(const std::unordered_map<std::string, double> &physical, hyper_cube_ref<double> unit) const = 0;

            /** @overload in place STL containers */
            void inverse_transform(const std::unordered_map<std::string, double> &physical, std::vector<double> &unit) const 
            {
                inverse_transform(physical, map_vector<double>(const_cast<double *>(&unit[0]), unit.size()));
            }

            /** @overload return STL containers */
            std::vector<double> inverse_transform(const std::unordered_map<std::string, double> &physical) const 
            {
                std::vector<double> unit(param_size);
                inverse_transform(physical, unit);
                return unit;
            }

            /** @brief Log of prior density */
            virtual double log_prior_density(const std::unordered_map<std::string, double> &) const = 0;

            virtual std::vector<std::string> getShownParameters() const { return param_names; }

            inline unsigned int size() const { return param_size; }

            inline void setSize(const unsigned int size) { param_size = size; }

            inline unsigned int & sizeRef() { return param_size; }

            inline std::vector<std::string> getParameters() const { return param_names; }
        };

    }  // namespace Priors
    
}  // namespace Gambit

#endif  // __BASE_PRIORS_HPP__
