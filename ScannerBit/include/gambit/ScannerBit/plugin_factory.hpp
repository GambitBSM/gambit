//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  test functions implementations.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Gregory Martinez
///          (gregory.david.martinez@gmail.com)
///  \date Feb 2014
///
///  *********************************************

#ifndef __plugin_factory_hpp__
#define __plugin_factory_hpp__

#include <map>
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>
#include <unordered_map>
#include <typeinfo>
#include <utility>
#include <limits>
#include <type_traits>

#include "gambit/ScannerBit/scanner_utils.hpp"
#include "gambit/ScannerBit/scan.hpp"
#include "gambit/ScannerBit/plugin_interface.hpp"
#include "gambit/Utils/yaml_options.hpp"
#include "gambit/Utils/type_index.hpp"
#include "gambit/Utils/signal_helpers.hpp"
#include "gambit/Utils/signal_handling.hpp"
#include "gambit/ScannerBit/factory_defs.hpp"

#define LOAD_FUNC_TEMPLATE(name, ...) REGISTER_ELEM(__functions__, typeid(__VA_ARGS__), name<__VA_ARGS__>)
#define LOAD_MULTI_FUNC_TEMPLATE(name, ...) REGISTER_ELEM(__multi_functions__, typeid(__VA_ARGS__), name<__VA_ARGS__>)

namespace Gambit
{
    namespace Scanner
    {
        using Gambit::type_index;

        gambit_registry
        {
            typedef void* func_type(const std::vector<std::string> &, const std::string &);
            typedef void* multi_func_type(const std::map<std::string, std::vector<std::string>> &, const std::vector<std::pair<std::string, std::string>> &);
            std::unordered_map<type_index, func_type *, Gambit::type_hasher, Gambit::type_equal_to> __functions__;
            std::unordered_map<type_index, multi_func_type *> __multi_functions__;
        }

        template <typename T>
        class Scanner_Plugin_Function;

        template <typename T>
        class Multi_Scanner_Plugin_Function;

        /// Objective functor made up a single plugin.
        template <typename ret, typename... args>
        class Scanner_Plugin_Function<ret (args...)> : public Plugins::Plugin_Interface<ret (args...)>, public Function_Base<ret (args...)>
        {
        private:
            //std::vector<double> &params;

        public:
            Scanner_Plugin_Function(const std::vector<std::string> &params, const std::string &name)
                    : Plugins::Plugin_Interface<ret (args...)>("objective", name, params)
            {
            }

            ret main(const args&... in)
            {
                // Check for signals to abort run
                if(signaldata().check_if_shutdown_begun())
                {
                    Function_Base<ret (args...)>::tell_scanner_early_shutdown_in_progress(); // e.g. sets 'quit' flag in Diver
                }

                if(signaldata().shutdown_begun() and not Function_Base<ret (args...)>::scanner_can_quit())
                {
                    signaldata().attempt_soft_shutdown();
                    //lnlike = alt_min_valid_lnlike;
                    //point_invalidated = true;
                    return scanner_plugin_def_ret<ret>();
                }
                else
                    return this->Plugins::Plugin_Interface<ret (args...)>::operator()(in...);
            }
        };

        /// Objective functor made up of multiple plugins.
        template <typename ret, typename... args>
        class Multi_Scanner_Plugin_Function <ret (args...)> : public Function_Base<ret (args...)>
        {
        private:
            std::vector< Scanner_Plugin_Function<ret (args...)> > functions;

        public:
            Multi_Scanner_Plugin_Function(const std::map< std::string, std::vector<std::string> > &params, const std::vector<std::pair<std::string, std::string>> &names)
            {
                for (auto it = names.begin(), end = names.end(); it != end; it++)
                {
                    functions.emplace_back(params.at(it->second), it->first);
                }
            }

            ret main(const args&... in)
            {
                // Check for signals to abort run
                if(signaldata().check_if_shutdown_begun())
                {
                    Function_Base<ret (args...)>::tell_scanner_early_shutdown_in_progress(); // e.g. sets 'quit' flag in Diver
                }

                if(signaldata().shutdown_begun() and not Function_Base<ret (args...)>::scanner_can_quit())
                {
                    signaldata().attempt_soft_shutdown();
                    //lnlike = alt_min_valid_lnlike;
                    //point_invalidated = true;
                    return scanner_plugin_def_ret<ret>();
                }
                else
                {
                    ret retval = 0.0;
                    for (auto& it : functions) retval += it.main(in...);
                    return retval;
                }
            }
        };

        LOAD_FUNC_TEMPLATE(Scanner_Plugin_Function, double (std::unordered_map<std::string, double> &));
        LOAD_FUNC_TEMPLATE(Scanner_Plugin_Function, void (const std::vector<double> &, std::unordered_map<std::string, double> &));
        LOAD_FUNC_TEMPLATE(Scanner_Plugin_Function, std::vector<double> (std::unordered_map<std::string, double> &));
        LOAD_MULTI_FUNC_TEMPLATE(Multi_Scanner_Plugin_Function, double(std::unordered_map<std::string, double> &));

        /// Factory class to make objectives using objective plugins.
        class Plugin_Function_Factory : public Factory_Base
        {
        private:
            std::map< std::string, std::vector<std::pair<std::string, std::string> > > names;
            std::map< std::string, std::vector<std::string> > parameters;
            std::unordered_map<std::string, Gambit::type_index> purpose_index;

        public:
            Plugin_Function_Factory(const std::vector<std::string> &keys, std::map< std::string, std::vector<std::pair<std::string, std::string>> > &names)
                    : names(names)
            {
                parameters = convert_to_map(keys);
                purpose_index["Likelihood"] = typeid(double (std::unordered_map<std::string, double> &));
                purpose_index["LogLike"] = typeid(double (std::unordered_map<std::string, double> &));
                purpose_index["Observable"] = typeid(std::vector<double> (std::unordered_map<std::string, double> &));
                purpose_index["Prior"] = typeid(void (const std::vector<double> &, std::unordered_map<std::string, double> &));
            }

            void * operator() (const std::string &purpose) const
            {
                auto it = names.find(purpose);
                std::string purpose_i = purpose;

                if (purpose_index.find(purpose) == purpose_index.end())
                {
                    purpose_i = "Likelihood";
                }

                if (it == names.end())
                {
                    return NULL;
                }
                else if (it->second.size() == 1)
                {
                    return __functions__.at(purpose_index.at(purpose_i))(parameters.at(it->second.at(0).second), it->second.at(0).first);
                }
                else if (it->second.size() > 1)
                {
                    return __multi_functions__.at(purpose_index.at(purpose_i))(parameters, it->second);
                }
                else
                {
                    return NULL;
                }
            }

            ~Plugin_Function_Factory()
            {
            }
        };
    }
}

#endif
