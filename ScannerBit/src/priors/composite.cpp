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

#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

#include "gambit/Utils/yaml_options.hpp"
#include "gambit/ScannerBit/priors_rollcall.hpp"
#include "gambit/ScannerBit/scanner_utils.hpp"

namespace Gambit 
{

 // All priors are transformations which "stretch" one or more random variates
 // sampled uniformly from the interval [0,1] (or higher dim. equivalent) into
 // a sample from a different distribution.
 
 // All priors will be used by pointers to the base class "BasePrior", so they
 // must inherit from this class. Their constructors can be used to set up
 // parameters of the transformation they perform, which should itself be 
 // actioned by the "transform" member function
 
 // Note that before the transformation by these priors, the random number
 // generation is totally symmetric in all parameters (this is my current
 // assumption, may need to relax it to accommodate some fancy scanner)
 // So the way the prior transformation is defined is what really defines which
 // parameter in the hypercube is which physical parameter.
 
 // However, this order has to be the order expected by the scanner wrapper of 
 // the loglikelihood function (see ScannerBit/lib/multinest.cpp for example).
 // Parameter names are provided along with this function so that we can
 // match them up in the prior correctly. The idea is that the constructors
 // for the prior objects should be called in such a way as to match the
 // required parameter order.
 
    namespace Priors 
    {
        std::vector<std::string> expand_dots(const std::vector<std::string> &param_names_in)
        {
            std::vector<std::string> param_names = param_names_in;
                
            for (int i = 0, end = param_names.size(); i < end; i++)
            {
                if (param_names[i].find("...") != std::string::npos)
                {
                    auto p_it = param_names.begin() + i;
                    std::string::size_type pos = p_it->find("...");
                    std::string prefix = p_it->substr(0, pos) + "_";
                    std::stringstream ss(p_it->substr(pos+3));
                    int N = 0;
                    if (bool(ss >> N) && N >0)
                    {
                        p_it = param_names.erase(p_it);
                        std::vector<std::string> temps;
                        
                        for (int j = 0; j < N; j++)
                        {
                            std::stringstream ss;
                            ss << j;
                            temps.push_back(prefix + ss.str());
                        }
                        
                        param_names.insert(p_it, temps.begin(), temps.end());
                        i += N - 1;
                    }
                }
            }
            
            return param_names;
        }
        /// Special "build-a-prior" classi
        // Combines prior objects together, so that the Scanner can deal with just one object in a standard way.
        // This is the class to use for setting simple 1D priors (from the library above) on individual parameters.
        // It also allows for any combination of MD priors to be set on any combination of subspaces of
        // the full prior.
        
        // Constructor
        CompositePrior::CompositePrior(const Options &model_options, const Options &prior_options)
        {       
            std::map<std::string, std::string> sameMap;
            std::unordered_map<std::string, std::pair<double, double>> sameMapOptions;
            std::vector<BasePrior *> phantomPriors;
            std::set<std::string> needSet;
            
            // Get model parameters from the inifile
            std::vector <std::string> modelNames = model_options.getNames();
            std::sort(modelNames.begin(), modelNames.end());
            
            //main loop to enter in parameter values
            for (auto mod_it = modelNames.begin(), mod_end = modelNames.end(); mod_it != mod_end; ++mod_it)
            {//loop over iniFile models
                std::string &mod = *mod_it;
                std::vector <std::string> parameterNames = model_options.getNames(mod);
                std::sort(parameterNames.begin(), parameterNames.end());
                
                int default_N = 0, default_i = 0;
                bool isDefault = false;
                std::string default_prefix;
                std::string::size_type par_pos;
                
                for (auto par_it = parameterNames.begin(), par_end = parameterNames.end(); par_it != par_end; par_it++)
                {//loop over iniFile parameters
                    Options par_options;
                    std::string par_name;
                    
                    par_pos = par_it->find("...");
                    if (!isDefault && par_pos != std::string::npos)
                    {
                        std::stringstream ss(par_it->substr(par_pos + 3));
                        isDefault = true;
                        if (bool(ss >> default_N) && default_N > 0)
                        {
                            isDefault = true;
                            default_prefix = par_it->substr(0, par_pos) + "_";
                            default_i = 0;
                        }
                    }
                    
                    if (isDefault)
                    {
                        std::stringstream ss;
                        ss << default_i++;
                        par_name = default_prefix + ss.str();
                    }
                    else
                    {
                        par_name = *par_it;
                    }
                    
                    param_names.push_back(mod + std::string("::") + par_name);
                    
                    if (model_options.getNode(mod, *par_it).IsSequence() || model_options.getNode(mod, *par_it).IsScalar())
                    {
                        phantomPriors.push_back(new FixedPrior(mod + std::string("::") + par_name, model_options.getNode(mod, *par_it)));
                    }
                    else
                    {
                        par_options = Options(model_options.getNode(mod, *par_it));
                    
                        if (par_options.hasKey("same_as"))
                        {
                            std::string connectedName = par_options.getValue<std::string>("same_as");
                            std::string::size_type pos = connectedName.rfind("::");
                            if (pos == std::string::npos)
                            {
                                connectedName += std::string("::") + par_name;
                            }
                            
                            sameMap[mod + std::string("::") + par_name] = connectedName;
                            
                            auto opt = std::pair<double, double>(1.0, 0.0);
                            if (par_options.hasKey("scale"))
                            {
                                opt.first = par_options.getValue<double>("scale");
                            }
                            
                            if (par_options.hasKey("shift"))
                            {
                                opt.second = par_options.getValue<double>("shift");
                            }
                            
                            sameMapOptions[mod + std::string("::") + par_name] = opt;
                        }
                        else if (par_options.hasKey("fixed_value"))
                        {
                            phantomPriors.push_back(new FixedPrior(mod + std::string("::") + par_name, par_options.getNode("fixed_value")));
                        }
                        else   
                        {
                            std::string joined_parname = mod + std::string("::") + par_name;
                            
                            if (par_options.hasKey("prior_type"))
                            {
                                Options options = par_options.getOptions();
                                std::string priortype = par_options.getValue<std::string>("prior_type");
                                
                                if(priortype == "same_as")
                                {
                                    if (options.hasKey("same_as"))
                                    {
                                        sameMap[joined_parname] = options.getValue<std::string>("same_as");
                                        
                                        auto opt = std::pair<double, double>(1.0, 0.0);
                                        if (par_options.hasKey("scale"))
                                        {
                                            opt.first = par_options.getValue<double>("scale");
                                        }
                                        
                                        if (par_options.hasKey("shift"))
                                        {
                                            opt.second = par_options.getValue<double>("shift");
                                        }
                                        
                                        sameMapOptions[joined_parname] = opt;
                                    }
                                    else
                                    {
                                        scan_err << "Same_as prior for parameter \"" << mod << "\" in model \""<< par_name << "\" has no \"same_as\" entry." << scan_end;
                                    }
                                }
                                else
                                {
                                    if (prior_creators.find(priortype) == prior_creators.end())
                                    {
                                        scan_err << "Parameter '"<< par_name <<"' of model '" << mod << "' is of type '"<<priortype
                                            <<"', but no entry for this type exists in the factory function map.\n" << prior_creators.print() << scan_end;
                                    }
                                    else
                                    {
                                        BasePrior *new_prior = prior_creators.at(priortype)(std::vector<std::string>(1, joined_parname),options);
                                        
                                        if (priortype == "fixed")
                                        {
                                            phantomPriors.push_back(new_prior);
                                        }
                                        else
                                        {
                                            my_subpriors.push_back( new_prior );
                                            shown_param_names.push_back(joined_parname);
                                        }
                                    }
                                }
                            }
                            else if (par_options.hasKey("range"))
                            {
                                shown_param_names.push_back(joined_parname);
                                
                                my_subpriors.push_back(new RangePrior1D<flatprior>(std::vector<std::string>(1, joined_parname), par_options));
                            }
                            else 
                            {
                                shown_param_names.push_back(joined_parname);
                                needSet.insert(joined_parname);
                            }
                        }
                    }
                    
                    if (isDefault && default_N > 0)
                    {
                        if (default_N > default_i)
                            par_it--;
                        else
                            isDefault = false;
                    }
                }
            }
            
            // Get the list of priors to build from the iniFile
            std::vector<std::string> priorNames = prior_options.getNames();
            std::sort(priorNames.begin(), priorNames.end());
            std::set<std::string> paramSet(shown_param_names.begin(), shown_param_names.end()); 

            for (auto priorname_it = priorNames.begin(), priorname_end = priorNames.end(); priorname_it != priorname_end; priorname_it++)
            {
                std::string &priorname = *priorname_it;
                if (prior_options.hasKey(priorname, "parameters") && prior_options.hasKey(priorname, "prior_type"))
                {
                    auto params = expand_dots(prior_options.getValue<std::vector<std::string>>(priorname, "parameters"));
                    
                    for (auto par_it = params.begin(), par_end = params.end(); par_it != par_end; par_it++)
                    {
                        if (paramSet.find(*par_it) == paramSet.end())
                        {
                            scan_err << "Parameter " << *par_it << " requested by " << priorname << " is either not defined by the inifile, is fixed, or is the \"same as\" another parameter." << scan_end;
                        }
                        else
                        {
                            auto find_it = needSet.find(*par_it);
                            if (find_it == needSet.end())
                            {
                                scan_err << "Parameter " << *par_it << " requested by prior '"<< priorname <<"' is reserved by a different prior." << scan_end;
                            }
                            else
                            {
                                needSet.erase(find_it);
                            }
                        }
                    }

                    auto options = prior_options.getOptions(priorname);
                    auto priortype = prior_options.getValue<std::string>(priorname, "prior_type");
                    
                    if (prior_creators.find(priortype) == prior_creators.end())
                    {
                        scan_err << "Prior '"<< priorname <<"' is of type '"<< priortype <<"', but no entry for this type exists in the factory function map.\n" << prior_creators.print() << scan_end;
                    }
                    else
                    {
                        if (priortype == "fixed")
                        {
                            /*for (auto par_it = params.begin(), par_end = params.end(); par_it != par_end; par_it++)
                            {
                                shown_param_names.erase
                                (
                                    std::find(shown_param_names.begin(), shown_param_names.end(), *par_it)
                                );
                            }*/
                            
                            //my_subpriors.push_back( prior_creators.at(priortype)(params,options) );
                            phantomPriors.push_back( prior_creators.at(priortype)(params,options) );
                        }
                        else if (priortype == "same_as")
                        {
                            if (options.hasKey("same_as"))
                            {
                                std::string same_name = options.getValue<std::string>("same_as");
                                for (auto par_it = params.begin(), par_end = params.end(); par_it != par_end; ++par_it)
                                {
                                    /*shown_param_names.erase
                                    (
                                        std::find(shown_param_names.begin(), shown_param_names.end(), *par_it)
                                    );*/
                                    sameMap[*par_it] = same_name;
                                }
                            }
                            else
                            {
                                scan_err << "Same_as prior \"" << priorname << "\" has no \"same_as\" entry." << scan_end;
                            }
                        }
                        else
                        {
                            BasePrior* new_prior = prior_creators.at(priortype)(params,options);
                            my_subpriors.push_back( new_prior );
                            
                            auto params = new_prior->getShownParameters();
                            shown_param_names.insert(shown_param_names.end(), params.begin(), params.end());
                            
                            /*if (priortype == "composite")
                            {
                                auto composite_new_prior = static_cast<CompositePrior *>(new_prior);
                                auto params = composite_new_prior->getShownParameters();
                                shown_param_names.insert(shown_param_names.end(), params.begin(), params.end());
                            }
                            else
                            {
                                auto params = new_prior->getShownParameters();
                                shown_param_names.insert(shown_param_names.end(), params.begin(), params.end());
                            }*/
                        }
                    }
                }
                else
                {
                    scan_err << "\"parameters\" and \"prior_type\" need to be defined for prior \"" << priorname << "\"" << scan_end;
                }
            }
            
            if (needSet.size() != 0)
            {
                scan_err << "Priors are not defined for the following parameters:  [";
                auto it = needSet.begin();
                scan_err << *(it++);
                for (; it != needSet.end(); it++)
                {
                    scan_err << ", "<< *it;
                }
                scan_err << "]" << scan_end;
            }
            
            std::map<std::string, std::string> keyMap;
            std::string index, result;
            unsigned int reps;
            for (auto strMap = sameMap.begin(), strMap_end = sameMap.end(); strMap != strMap_end; ++strMap)
            {
                index = strMap->first;
                result = strMap->second;
                reps = 0;
                while (sameMap.find(result) != sameMap.end())
                {
                    index = result;
                    result = sameMap[index];
                    
                    if (result == strMap->first)
                    {
                        scan_err << "Parameter " << strMap->first << " is \"same as\" itself." << scan_end;
                        break;
                    }
                    
                    if (reps > sameMap.size())
                    {
                        scan_err << "Parameter's \"same as\"'s are loop in on each other." << scan_end;
                        break;
                    }
                    reps++;
                }
                
                if (keyMap.find(result) == keyMap.end())
                    keyMap[result] = strMap->first + std::string("+") + result;
                else
                    keyMap[result] = strMap->first + std::string("+") + keyMap[result];
            }
            
            for (auto str_it = shown_param_names.begin(), str_end = shown_param_names.end(); str_it != str_end; str_it++)
            {
                auto it = keyMap.find(*str_it);
                if (it != keyMap.end())
                {
                    *str_it = it->second;
                }
            }
            
            for (auto key_it = keyMap.begin(), key_end = keyMap.end(); key_it != key_end; key_it++)
            {
                if (paramSet.find(key_it->first) == paramSet.end())
                {
                    scan_err << "same_as:  " << key_it->first << " is not defined in inifile." << scan_end;
                }
                else
                {
                    phantomPriors.push_back(new MultiPriors(key_it->second, sameMapOptions));
                }
            }
            
            int param_size = 0;
            for (auto subprior = my_subpriors.begin(), prior_end = my_subpriors.end(); subprior != prior_end; subprior++)
            {
                param_size += (*subprior)->size();
            }
            
            setSize(param_size);
            
            my_subpriors.insert(my_subpriors.end(), phantomPriors.begin(), phantomPriors.end());
        }  
        
        CompositePrior::CompositePrior(const std::vector<std::string> &params_in, const Options &options_in) : BasePrior(params_in)//, shown_param_names(params_in)
        {       
            std::map<std::string, std::string> sameMap;
            std::unordered_map<std::string, std::pair<double, double>> sameMapOptions;
            std::set<std::string> needSet(params_in.begin(), params_in.end());
            std::set<std::string> paramSet(params_in.begin(), params_in.end());
            std::vector<BasePrior *> phantomPriors;

            auto priorNames = options_in.getNames();
            std::sort(priorNames.begin(), priorNames.end());
            
            for (auto priorname_it = priorNames.begin(), priorname_end = priorNames.end(); priorname_it != priorname_end; ++priorname_it)
            {
                std::string &priorname = *priorname_it;
                if (options_in.hasKey(priorname, "parameters") && options_in.hasKey(priorname, "prior_type"))
                {
                    //auto params = options_in.getValue<std::vector<std::string>>(priorname, "parameters");
                    
                    auto params = Gambit::Scanner::get_yaml_vector<std::string>(options_in.getNode(priorname, "parameters"));
                    
                    for (auto par_it = params.begin(), par_end = params.end(); par_it != par_end; par_it++)
                    {
                        std::string &par = *par_it;
                        if (paramSet.find(par) == paramSet.end())
                        {
                            scan_err << "Parameter " << par << " requested by " << priorname 
                                << " is either not defined by the inifile, is fixed, or is the \"same as\" another parameter." << scan_end;
                        }
                        else
                        {
                            auto find_it = needSet.find(par);
                            if (find_it == needSet.end())
                            {
                                scan_err << "Parameter " << par << " requested by prior '"<< priorname 
                                    <<"' is reserved by a different prior." << scan_end;
                            }
                            else
                            {
                                needSet.erase(find_it);
                            }
                        }
                    }

                    auto options = options_in.getOptions(priorname);
                    auto priortype = options_in.getValue<std::string>(priorname, "prior_type");
                    
                    if (prior_creators.find(priortype) == prior_creators.end())
                    {
                        scan_err << "Prior '"<< priorname <<"' is of type '"<< priortype 
                            <<"', but no entry for this type exists in the factory function map.\n" << prior_creators.print() << scan_end;
                    }
                    else
                    {
                        if (priortype == "fixed")
                        {
                            /*for (auto par_it = params.begin(), par_end = params.end(); par_it != par_end; par_it++)
                            {
                                shown_param_names.erase
                                (
                                    std::find(shown_param_names.begin(), shown_param_names.end(), *par_it)
                                );
                            }*/
                                
                            phantomPriors.push_back( prior_creators.at(priortype)(params,options) );
                        }
                        else if (priortype == "same_as")
                        {
                            if (options.hasKey("same_as"))
                            {
                                std::string same_name = options.getValue<std::string>("same_as");
                                for (auto par_it = params.begin(), par_end = params.end(); par_it != par_end; par_it++)
                                {
                                    /*shown_param_names.erase
                                    (
                                        std::find(shown_param_names.begin(), shown_param_names.end(), *par_it)
                                    );*/
                                    sameMap[*par_it] = same_name;
                                }
                            }
                            else
                            {
                                scan_err << "Same_as prior \"" << priorname << "\" has no \"same_as\" entry." << scan_end;
                            }
                        }
                        else
                        {
                            //my_subpriors.push_back( prior_creators.at(priortype)(params,options) );
                            
                            BasePrior* new_prior = prior_creators.at(priortype)(params,options);
                            my_subpriors.push_back( new_prior );
                            
                            auto params = new_prior->getShownParameters();
                            shown_param_names.insert(shown_param_names.end(), params.begin(), params.end());
                        }
                    }
                }
                else
                {
                    scan_err << "\"parameters\" and \"prior_type\" need to be defined for prior \"" << priorname << "\"" << scan_end;
                }
            }
            
            if (needSet.size() != 0)
            {
                scan_err << "Priors are not defined for the following parameters:  [";
                auto it = needSet.begin();
                scan_err << *(it++);
                for (; it != needSet.end(); it++)
                {
                    scan_err << ", "<< *it;
                }
                scan_err << "]" << scan_end;
            }
            
            std::map<std::string, std::string> keyMap;
            std::string index, result;
            unsigned int reps;
            for (auto strMap_it = sameMap.begin(), strMap_end = sameMap.end(); strMap_it != strMap_end; strMap_it++)
            {
                index = strMap_it->first;
                result = strMap_it->second;
                reps = 0;
                while (sameMap.find(result) != sameMap.end())
                {
                    index = result;
                    result = sameMap[index];
                    
                    if (result == strMap_it->first)
                    {
                        scan_err << "Parameter " << strMap_it->first << " is \"same as\" itself." << scan_end;
                        break;
                    }
                    
                    if (reps > sameMap.size())
                    {
                        scan_err << "Parameter's \"same as\"'s are loop in on each other." << scan_end;
                        break;
                    }
                    reps++;
                }
                
                if (keyMap.find(result) == keyMap.end())
                    keyMap[result] = strMap_it->first + std::string("+") + result;
                else
                    keyMap[result] = strMap_it->first + std::string("+") + keyMap[result];
            }
            
            for (auto str_it = shown_param_names.begin(), str_end = shown_param_names.end(); str_it != str_end; str_it++)
            {
                auto it = keyMap.find(*str_it);
                if (it != keyMap.end())
                {
                    *str_it = it->second;
                }
            }
            
            for (auto key_it = keyMap.begin(), key_end = keyMap.end(); key_it != key_end; key_it++)
            {
                if (paramSet.find(key_it->first) == paramSet.end())
                {
                    scan_err << "same_as:  " << key_it->first << " is not defined in inifile." << scan_end;
                }
                else
                {
                    phantomPriors.push_back(new MultiPriors(key_it->second, sameMapOptions));
                }
            }
            
            int param_size = 0;
            for (auto subprior = my_subpriors.begin(), subprior_end = my_subpriors.end(); subprior != subprior_end; subprior++)
            {
                param_size += (*subprior)->size();
            }
            
            setSize(param_size);
            
            my_subpriors.insert(my_subpriors.end(), phantomPriors.begin(), phantomPriors.end());
        }
    } // end namespace Priors
} // end namespace Gambit

