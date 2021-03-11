//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  declaration for scanner module
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Gregory Martinez
///          (gregory.david.martinez@gmail.com)
///  \date 2013 August
///        2014 Feb
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)   
///  \date 2014 Dec
///
///  *********************************************

#ifndef GAMBIT_PLUGIN_DEFS_HPP
#define GAMBIT_PLUGIN_DEFS_HPP

#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <typeinfo>
#include <unistd.h>

#ifdef WITH_MPI
#include <mpi.h>
#endif

#include "gambit/ScannerBit/printer_interface.hpp"
#include "gambit/Utils/type_index.hpp"
#include "gambit/ScannerBit/plugin_loader.hpp"
#include "gambit/ScannerBit/base_prior.hpp"

namespace Gambit
{

    namespace Scanner
    {
        typedef Priors::BasePrior prior_interface;
        
        /// class to interface with the plugin manager resume functions.
        class resume_params_func
        {
        private:
            std::string name;
            bool resume;
            int rank;
            int numtasks;
            
        public:
            resume_params_func(const std::string &name_in) : resume(false)
            {
#ifdef WITH_MPI
                MPI_Comm_rank(MPI_COMM_WORLD, &rank);
                MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
#else
                rank = 0;
                numtasks = 1;
#endif
                std::stringstream ss;
                ss << rank;
                name = name_in + "_" + ss.str();
            }
            
            std::string get_name() const { return name; }

            void set_resume_mode(const bool &mode)
            {
                resume = mode;
            }
            
            bool resume_mode() const {return resume;}
            
            std::string get_temp_file_name(const std::string &temp_file)
            {
                std::stringstream ss;
                ss << Gambit::Scanner::Plugins::plugin_info.temp_file_path();
                ss << name;
                ss << "_";
                ss << temp_file;
                ss << "_";
                ss << rank;
                
                return ss.str();
            }
            
            void dump()
            {
                Gambit::Scanner::Plugins::plugin_info.dump(name);
            }
            
            int Rank() const {return rank;}
            int NumTasks() const {return numtasks;}
            
            template <typename... T>
            void operator ()(T&... params)
            {
                Gambit::Scanner::Plugins::plugin_info.resume(name, params...);
            }
        };
            
        namespace Plugins
        {
            using Gambit::type_index;
            
            /// These classes are used by the plugins to load and save data
            /// @{
            class factoryBase
            {
            public:
                virtual void *operator()() = 0;
                virtual ~factoryBase() {}
            };
            
            template <typename T>
            class funcFactory : public factoryBase
            {
            private:
                T *func;
                    
            public:
                funcFactory (T *in) : func(in) {}
                void *operator()(){return *(void**)&func;}
                ~funcFactory(){}
            };
            
            template <typename T>
            class classFactory : public factoryBase
            {
            private:
                std::vector<T *> ptrs;
                    
            public:
                void *operator()()
                {
                    T *ptr = new T;
                    ptrs.push_back(ptr);
                    return (void*) ptr;
                }
                
                ~classFactory()
                {
                    for (auto it = ptrs.begin(), end = ptrs.end(); it != end; it++)
                        delete *it;
                }
            };
            /// @}
            
            /// Structure that holds all the data provided by plugins about themselves.
            struct pluginData
            {
                std::string name;
                std::string type;
                std::string version;
                std::string tag;
                YAML::Node node;
                printer_interface *printer;
                prior_interface *prior;
                std::vector <void *> inputData;
                std::vector <void (*)(pluginData &)> inits;
                std::map<std::string, factoryBase *> outputFuncs;
                std::map<type_index, void *> plugin_mains;
                void (*deconstructor)();
                bool loaded;
                
                pluginData(const std::string &name, const std::string &type, const std::string &version_in) 
                        : name(name), type(type), version(version_in), deconstructor(NULL), loaded(false)
                {
                    std::string::size_type posLast = version.find("_");
                    std::string major_version = version.substr(0, posLast);
                    std::string::size_type posMid = version.find("_", posLast + 1);
                    std::string minor_version = version.substr(posLast + 1, posMid - posLast - 1);
                    posLast = version.find("_", posMid + 1);
                    std::string patch_version = version.substr(posMid + 1, posLast - posMid - 1);
                    std::string release_version = version.substr(posLast + 1);
                    version = major_version + "." + minor_version + "." + patch_version;
                    if (release_version != "") 
                        version += "-" + release_version;
                }
                
                std::string print()
                {
                    std::stringstream ss;
                    ss << "plugin name:  " << name << std::endl;
                    ss << "plugin type:  " << type << std::endl;
                    ss << "plugin version: " << version << std::endl;
                    
                    return ss.str();
                }
                
                ~pluginData()
                {
                    if (deconstructor != NULL && loaded == true)
                        deconstructor();
                    
                    for (auto it = outputFuncs.begin(), end = outputFuncs.end(); it != end; it++)
                    {
                        delete it->second;
                    }
                    
                    loaded = false;
                }
            };  

        }

    }

}

#endif
