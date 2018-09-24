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

#ifndef __BASE_PRIORS_HPP__
#define __BASE_PRIORS_HPP__

#include <vector>
#include <unordered_map>

namespace Gambit
{
    namespace Priors
    {

        //
        // Prior classes
        //

        /// Abstract base class for priors
        class BasePrior
        {
        private:
            unsigned int param_size;

        protected:
            std::vector<std::string> param_names;

        public:
            BasePrior() : param_size(0), param_names(0) {}

            BasePrior(const int param_size) : param_size(param_size), param_names(0) {}

            BasePrior(const std::vector<std::string> &param_names, const int param_size = 0) : param_size(param_size), param_names(param_names) {}

            BasePrior(const std::string &param_name, const int param_size = 0) : param_size(param_size), param_names(1, param_name) {}

            virtual void transform(const std::vector<double> &, std::unordered_map<std::string, double> &) const = 0;

            virtual double operator()(const std::vector<double> &) const {return 0.0;}

            inline unsigned int size() const {return param_size;}

            inline void setSize(const unsigned int size) {param_size = size;}

            inline unsigned int & sizeRef(){return param_size;}

            inline std::vector<std::string> getParameters() const {return param_names;}
            
            virtual std::vector<std::string> getShownParameters() const {return param_names;}

            virtual ~BasePrior () {}
        };

    } // end namespace Priors

} // end namespace Gambit

#endif /* defined(__priors_hpp__) */

