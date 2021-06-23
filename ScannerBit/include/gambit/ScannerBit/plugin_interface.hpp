//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  Interface details for scanner plugins
///
///  *********************************************
///
///  Authors (add name and date if you modify):
//
///  \author Gregory Martinez
///          (gregory.david.martinez@gmail.com)
///  \date 2013 August
///  \date 2014 Feb
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)   
///  \date 2014 Dec
///
///  *********************************************

#ifndef __PLUGIN_INTERFACE_HPP
#define __PLUGIN_INTERFACE_HPP

#include <vector>
#include <map>
#include <sstream>
#include <dlfcn.h>
#include <typeinfo>

#include "gambit/ScannerBit/scanner_utils.hpp"
#include "gambit/ScannerBit/plugin_loader.hpp"
#include "gambit/ScannerBit/printer_interface.hpp"
#include "gambit/Utils/type_index.hpp"

namespace Gambit
{

    namespace Scanner
    {

        namespace Plugins
        {
            using Gambit::type_index;
            
            inline const std::map<type_index, void *>& error_map_return()
            {
                static const std::map<type_index, void *> temp_map;
                return temp_map;
            }
            
            /*******************************************************/
            /************ Plugin Main Interface Base ***************/
            /*******************************************************/
            
            template <typename T>
            class Plugin_Main_Interface_Base;
            
            template <typename ret, typename... args>
            class Plugin_Main_Interface_Base <ret (args...)>
            {
            private:
                typedef ret (*mainFuncType)(args...);
                mainFuncType main;
                    
            public:
                Plugin_Main_Interface_Base() : main(0) {}
                
                int enterMain(const std::string &name, const std::map<type_index, void *> & index_map)
                {
                    for (auto it = index_map.begin(), end = index_map.end(); it != end; it++)
                    {
                        if (it->first == typeid(ret (args...)))
                        {
                            main = reinterpret_cast<mainFuncType>(it->second);
                            return 0;
                        }
                    }
                    
                    scan_err << "Plugin interface requires the plugin_main function in plugin \"" << name << "\" to be of the form \"" 
                            << demangle(typeid(ret).name()) << " (" << stringifyVariadic(demangle(typeid(args).name())...) << ")\"" << scan_end;
                    
                    return 1;
                }
                
                ret operator() (const args&... params) 
                {
                        return main(params...);
                }
            };
            
            /**************************************************/
            /************ Plugin Interface Base ***************/
            /**************************************************/
            
            class Plugin_Interface_Base
            {
            private:
                void *plugin;
                YAML::Node flags;
                std::vector<void *> input;
                std::string tag;
                typedef const std::map<type_index, void *> &(*initFuncType)(const std::string &, const YAML::Node &, const printer_interface &, Priors::BasePrior &, std::vector<void *> &);                              
                typedef void * (*getFuncType)(std::string);
                initFuncType initFunc;
                getFuncType getFunc;
                    
            protected:
                template <typename... plug_args>
                const std::map<type_index, void *> &initPlugin(const std::string &type, const std::string &name, const plug_args&... inputs) 
                {
                    Plugin_Interface_Details details = plugin_info(type, name);
                    flags = details.flags;
                    plugin = dlopen (details.details.path.c_str(), RTLD_LAZY);
                    
                    if (bool(plugin))
                    {
                        tag = name;
                        input_variadic_vector(input, inputs...);
                        initFunc = (initFuncType)dlsym(plugin, (std::string("__gambit_plugin_pluginInit_") + details.details.full_string + std::string("__")).c_str());
                        getFunc = (getFuncType)dlsym(plugin, (std::string("__gambit_plugin_getMember_") + details.details.full_string + std::string("__")).c_str());
                        
                        char *errmesg = dlerror();
                        if (errmesg != NULL)
                        {
                            scan_err << "error loading plugin " << name << ":  " << errmesg << scan_end;
                            return error_map_return();
                        }
                        else
                        {
                            return initFunc(tag, details.node, *details.printer, *details.prior, input);
                        }
                    }
                    else
                    {
                        scan_err << "Cannot load " << details.details.path << ":  " << dlerror() << scan_end;
                        plugin = 0;
                        return error_map_return();
                    }
                }
                    
            public:
                Plugin_Interface_Base() : plugin(0), initFunc(0), getFunc(0) {}
                
                YAML::Node operator[](const std::string &key){return flags[key];}
                
                ~Plugin_Interface_Base()
                {
                    if (plugin != 0) dlclose(plugin);
                }
            };
            
            
            /*********************************************/
            /************ Plugin Interface ***************/
            /*********************************************/
            
            /// Interface for a ScannerBit plugin.  Called like:
            /// Plugins::Plugin_Interface<int ()> interface("scanner", pluginName, dim, *factory);
            /// interface();
            template <typename... T> 
            class Plugin_Interface : public Plugin_Interface_Base, public Plugin_Main_Interface_Base<T>...
            {
            private:
                template <typename... T1>
                void dummy(T1...){}
            public:
                template <typename... plug_args>
                Plugin_Interface(const std::string &type, const std::string &name, const plug_args&... inputs)
                {
                    auto index_map = initPlugin(type, name, inputs...);
                    dummy(Plugin_Main_Interface_Base<T>::enterMain(name, index_map)...);
                }

                template <typename... args>
                auto operator()(args&... params) -> typename find_variadic_type <void (args...), T...>::ret_type
                {
                    static_assert(find_variadic_type <void (args...), T...>::value, "\n\033[00;31;1mPlugin Interface:  Entered argument types do not match any of the plugin mains' argument types.\033[00m\n");
                    return Plugin_Main_Interface_Base<typename find_variadic_type <void (args...), T...>::func_type>::operator()(params...);
                }
            };
            
            template <typename ret, typename... args>
            class Plugin_Interface <ret (args...)> : public Plugin_Interface_Base, public Plugin_Main_Interface_Base<ret (args...)>
            {
            private:
                    
            public:
                template <typename... plug_args>
                Plugin_Interface(const std::string &type, const std::string &name, const plug_args&... inputs)
                {
                    Plugin_Main_Interface_Base<ret (args...)>::enterMain(name, initPlugin(type, name, inputs...));
                }
                
                ret operator() (const args&... params)
                {
                    return Plugin_Main_Interface_Base<ret (args...)>::operator()(params...);
                }
            };

        }

    }

}

#endif
