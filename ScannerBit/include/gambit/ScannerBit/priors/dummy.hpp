//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  declaration for scanner module
///
///  *********************************************
///
///  Authors (add name and date if you modify):
//
///  \author Gregory Martinez
///          (gregory.david.martinez@gmail.com)
///  \date Feb 2014
///
///  *********************************************

#ifndef DUMMY_PRIOR_HPP
#define DUMMY_PRIOR_HPP

#include <algorithm>

#include "gambit/ScannerBit/priors.hpp"


namespace Gambit
{
    namespace Priors
    {
        class Dummy : public BasePrior
        {
        private:

        public:
            // Constructor
            Dummy(const std::vector<std::string>& param, const Options&) : BasePrior(param, param.size())
            {
            }

            void transform(const std::vector<double> &unitpars, std::unordered_map<std::string, double> &outputMap) const override
            {
                auto it_vec = unitpars.begin();
                for (auto it = param_names.begin(), end = param_names.end(); it != end; it++)
                {
                    outputMap[*it] = *(it_vec++);
                }
            }

            std::vector<double> inverse_transform(const std::unordered_map<std::string, double> &physical) const override
            {
                std::vector<double> u;
                for (const auto& n : param_names)
                {
                    u.push_back(physical.at(n));
                }
                return u;
            }

        };

        class None : public BasePrior
        {
        private:

        public:
            None(const std::vector<std::string>& param, const Options&) : BasePrior(param)
            {
            }

            void transform(const std::vector<double> &, std::unordered_map<std::string, double> &outputMap) const override
            {
                for (auto it = param_names.begin(), end = param_names.end(); it != end; it++)
                {
                    if (outputMap.find(*it) == outputMap.end())
                    {
                        scan_err << "Parameter " << *it << " prior is specified as 'none'"
                                 << " and the scanner has not inputed a value for it."
                                 << scan_end;
                    }
                }
            }

            std::vector<double> inverse_transform(const std::unordered_map<std::string, double> &) const override
            {
              scan_err << "'None' prior has no inverse transform" << scan_end;
              return {};
            }


        };

        LOAD_PRIOR(dummy, Dummy)
        LOAD_PRIOR(none, None)
    }
}

#endif
