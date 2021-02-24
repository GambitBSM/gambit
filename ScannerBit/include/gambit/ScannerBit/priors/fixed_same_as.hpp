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

#ifndef FIXED_SAME_AS_PRIOR_HPP
#define FIXED_SAME_AS_PRIOR_HPP

#include <algorithm>

#include "gambit/ScannerBit/priors.hpp"


namespace Gambit
{
    namespace Priors
    {
        //if the parameter has a fixed value
        class FixedPrior : public BasePrior
        {
        private:
            std::vector<double> value;
            mutable int iter;

        public:
            FixedPrior(const std::vector<std::string>& param, const Options& options) : BasePrior(param), iter(0)
            {
                if (options.hasKey("fixed_value"))
                {
                    if (options.getNode("fixed_value").IsScalar())
                    {
                        value.push_back(options.getValue<double>("fixed_value"));
                    }
                    else if (options.getNode("fixed_value").IsSequence())
                    {
                        value = options.getValue<std::vector<double>>("fixed_value");
                    }
                    else
                    {
                        scan_err << "fixed_value input for parameter " << param_names[0] << " is neither scalar nor sequence" << scan_end;
                    }
                }
                else
                {
                    scan_err << "Did not give fixed_value for parameter " << param_names[0] << "..." << scan_end;
                }
            }

            FixedPrior(const std::string& param, const Options& options) : BasePrior(param), iter(0)
            {
                if (options.getNode().IsScalar())
                {
                    value.push_back(options.getValue<double>());
                }
                else if (options.getNode().IsSequence())
                {
                    value = options.getValue<std::vector<double>>();
                }
                else
                {
                    scan_err << "fixed_value input for parameter " << param_names[0] << " is neither scalar nor sequence" << scan_end;
                }
            }

            FixedPrior(const std::string &name, double value) : BasePrior(name), value(1, value), iter(0) {}
            
            std::vector<std::string> getShownParameters() const {return std::vector<std::string>();}

            void transform(const std::vector<double> &, std::unordered_map<std::string, double> &outputMap) const
            {
                for (auto it = param_names.begin(), end = param_names.end(); it != end; it++)
                {
                    outputMap[*it] = value[iter];
                }

                iter = (iter + 1)%value.size();
            }
        };

        //if the parameter shares multiple different parameters
        class MultiPriors : public BasePrior
        {
        private:
            std::string name;
            std::vector<double> scale, shift;

        public:
            MultiPriors(const std::vector<std::string>& param, const Options& options) : BasePrior(param), scale(param.size(), 1.0), shift(param.size(), 0.0)
            {
                if (options.hasKey("same_as"))
                {
                    name = options.getValue<std::string>("same_as");
                }
                else
                {
                    std::stringstream err;
                    scan_err << "Did not give same_as parameters for parameter " << name << scan_end;
                }

                if (options.hasKey("scale"))
                {
                    scale = options.getValue<std::vector<double>>("scale");
                }

                if (options.hasKey("shift"))
                {
                    shift = options.getValue<std::vector<double>>("shift");
                }
            }

            MultiPriors(std::string name_in, std::unordered_map<std::string, std::pair<double, double> > &map_in)
            {
                std::string::size_type pos_old = 0;
                std::string::size_type pos = name_in.find("+");
                while (pos != std::string::npos)
                {
                    std::string p_name = name_in.substr(pos_old, (pos-pos_old));
                    param_names.push_back(p_name);
                    if (map_in.find(p_name) == map_in.end())
                    {
                        scale.push_back(1.0);
                        shift.push_back(0.0);
                    }
                    else
                    {
                        scale.push_back(map_in[p_name].first);
                        shift.push_back(map_in[p_name].second);
                    }
                    pos_old = pos + 1;
                    pos = name_in.find("+", pos_old);
                }

                name = name_in.substr(pos_old);
                param_names.push_back(name_in);
            }
            
            std::vector<std::string> getShownParameters() const {return std::vector<std::string>();}

            void transform (const std::vector<double> &, std::unordered_map<std::string, double> &outputMap) const
            {
                double value = outputMap[name];

                auto it1 = scale.begin(), it2 = shift.begin();
                for (auto it = param_names.begin(), end = param_names.end(); it != end; ++it, ++it1, ++it2)
                {
                    outputMap[*it] = (*it1)*value + *it2;
                }
            }
        };

        LOAD_PRIOR(fixed_value, FixedPrior)
        LOAD_PRIOR(same_as, MultiPriors)
    }
}

#endif
