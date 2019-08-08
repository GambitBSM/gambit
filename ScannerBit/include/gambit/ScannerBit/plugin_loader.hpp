//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  Loader singleton class for scanner plugins
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Gregory Martinez
///          (gregory.david.martinez@gmail.com)
///  \date 2013 August
///  \date 2014 Feb
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2014 Dec
///
///  \author Ben Farmer
///          (benjamin.farmer@fysik.su.se)
///  \date 2016 Aug
///
///  *********************************************

#ifndef __PLUGIN_LOADER_HPP
#define __PLUGIN_LOADER_HPP

#include <vector>
#include <unordered_map>
#include <string>
#include <type_traits>

#include "gambit/ScannerBit/plugin_details.hpp"
#include "gambit/Utils/yaml_options.hpp"
#include "gambit/Utils/util_macros.hpp"
#include "gambit/ScannerBit/printer_interface.hpp"
#include "gambit/cmake/cmake_variables.hpp"
#include "gambit/ScannerBit/scanner_utils.hpp"
#include "gambit/Utils/util_functions.hpp"
#include "gambit/ScannerBit/base_prior.hpp"

namespace Gambit
{
    /// Forward declare MPI class
    namespace GMPI { class Comm; }

    namespace Scanner
    {

        namespace Plugins
        {
            ///Plugin info from inifile
            struct Proto_Plugin_Details
            {
                std::string plugin;
                std::string version;
                std::string path;

                Proto_Plugin_Details() : plugin(""), version(""), path("") {}
            };

            ///Plugin info to be given to the interface class
            struct EXPORT_SYMBOLS Plugin_Interface_Details
            {
                Plugin_Details &details;
                printer_interface *printer;
                Priors::BasePrior *prior;
                YAML::Node flags;
                YAML::Node node;

                Plugin_Interface_Details(Plugin_Details &details, printer_interface *printer, Priors::BasePrior *prior, const YAML::Node &node)
                        : details(details), printer(printer), prior(prior), flags(details.flags), node(node) {}
            };

            ///container class for the actual plugins detected by ScannerBit
            class EXPORT_SYMBOLS Plugin_Loader
            {
            private:
                std::string path;
                std::vector<Plugin_Details> plugins;
                std::map<std::string, std::map<std::string, std::vector<Plugin_Details>>> plugin_map;
                std::vector<Plugin_Details> excluded_plugins;
                std::map<std::string, std::map<std::string, std::vector<Plugin_Details>>> excluded_plugin_map;
                std::vector<Plugin_Details> total_plugins;
                std::map<std::string, std::map<std::string, std::vector<Plugin_Details>>> total_plugin_map;
                std::vector<Plugin_Details> loadExcluded(const std::string &);
                void process(const std::string &, const std::string &, const std::string &, std::vector<Plugin_Details>&);

            public:
                Plugin_Loader();
                const std::vector<Plugin_Details> &getPluginsVec() const {return total_plugins;}
                const std::map<std::string, std::map<std::string, std::vector<Plugin_Details>>> &getPluginsMap() const {return total_plugin_map;}
                void loadLibrary (const std::string &, const std::string & = "");
                std::vector<std::string> print_plugin_names(const std::string & = "") const;
                std::string print_all (const std::string &plug_type = "") const;
                int print_all_to_screen (const std::string &plug_type = "") const;
                std::string print_plugin (const std::string &) const;
                std::string print_plugin (const std::string &, const std::string &) const;
                std::vector<std::string> list_prior_groups() const;
                std::string print_priors (const std::string &prior_group = "priors") const;
                int print_plugin_to_screen (const std::string &) const;
                int print_plugin_to_screen (const std::string &, const std::string &) const;
                int print_plugin_to_screen (const std::vector<std::string> &) const;
                Plugin_Details &find (const std::string &, const std::string &, const std::string &, const std::string &) const;
            };

            ///Virtual container base class to store plugin values for resume function
            class __plugin_resume_base__
            {
            public:
                virtual void print(std::ofstream &) = 0;
                virtual ~__plugin_resume_base__() {}
            };

            ///Container class to store plugin values for resume function
            template <typename T>
            class __plugin_resume__ : public __plugin_resume_base__
            {
            private:
                T *data;

            public:
                __plugin_resume__(T &data) : data(&data) {}

                void print(std::ofstream &out)
                {
                    resume_file_output<T>(out, *data);
                }

                ~__plugin_resume__(){}
            };

            ///Container for all the plugin info from the inifile and Scannerbit
            class EXPORT_SYMBOLS pluginInfo
            {
            private:
                bool keepRunning;
                bool funcCalculating;
                std::map<std::string, std::map<std::string, Proto_Plugin_Details> > selectedPlugins;
                mutable Plugins::Plugin_Loader plugins;
                std::map<std::string, std::vector<__plugin_resume_base__ *>> resume_data;
                std::map<std::string, std::ifstream *> resume_streams;
                printer_interface *printer;
                Priors::BasePrior *prior;
                Options options;
                std::string def_out_path;
                int MPIrank;
                #ifdef WITH_MPI
                GMPI::Comm* scannerComm;
                bool MPIdata_is_init;
                #endif
                /// Flag to indicate if early shutdown is in progess (e.g. due to intercepted OS signal). When set to 'true' scanners should at minimum close off their output files, and if possible they should stop scanning and return control to GAMBIT (or whatever the host code might be).
                bool earlyShutdownInProgress;

                inline void set_resume(std::vector<__plugin_resume_base__ *> &){}

                template<typename U, typename... T>
                void set_resume(std::vector<__plugin_resume_base__ *> &r_data, U& param, T&... params)
                {
                    r_data.push_back(new __plugin_resume__<typename std::decay<U>::type>(param));
                    set_resume(r_data, params...);
                }

                inline void get_resume(std::ifstream &){}

                template<typename U, typename... T>
                void get_resume(std::ifstream &in, U& param, T&... params)
                {
                    resume_file_input(in, param);
                    get_resume(in, params...);
                }

                inline size_t get_size_of(){return 0;}

                template<typename U, typename... T>
                inline size_t get_size_of(U& param, T&... params)
                {
                    return resume_size_of(param) + get_size_of(params...);
                }

            public:
                pluginInfo();

                ///Enter plugin inifile
                void iniFile(const Options &);
                void printer_prior(printer_interface &, Priors::BasePrior &);
                bool keep_running() const {return keepRunning;}
                void set_running(bool b){keepRunning = b;}
                bool func_calculating() const {return funcCalculating;}
                void set_calculating(bool b){funcCalculating = b;}
                void set_early_shutdown_in_progress(){earlyShutdownInProgress=true;}
                bool early_shutdown_in_progress() const {return earlyShutdownInProgress;}
                bool resume_mode() const { return printer->resume_mode(); }
                std::string temp_file_path() {return Gambit::Utils::ensure_path_exists(def_out_path + "/temp_files/");}

                #ifdef WITH_MPI
                // tags for messages sent via scannerComm
                static const int MIN_LOGL_MSG = 0;
                ///Initialise any MPI functionality (currently just used to provide a communicator object to ScannerBit)
                void initMPIdata(GMPI::Comm* newcomm);
                GMPI::Comm& scanComm();
                #endif
                int getRank() { return MPIrank; }

                ///resume function
                template <typename... T>
                void resume(const std::string &name, T&... data)
                {
                    if (resume_mode())
                    {
                        if (resume_streams.find(name) == resume_streams.end())
                        {
                            std::string path = Gambit::Utils::ensure_path_exists(def_out_path + "/temp_files/" + name);
                            resume_streams[name] = new std::ifstream((path).c_str(), std::ifstream::binary);
                        }

                        if (resume_streams[name]->is_open())
                        {
                            get_resume(*resume_streams[name], data...);
                        }
                        else
                        {
                            std::cerr << "Could not load resume data." << std::endl;
                            //scan_err << "Could not load resume data." << scan_end;
                        }
                    }

                    set_resume(resume_data[name], data...);
                }

                ///Dump contents for resume.
                void dump();

                ///Dump contents for one plugin
                void dump(const std::string &);

                ///Save persistence file to record that the alternative min_LogL value is in use for this scan
                void save_alt_min_LogL_state() const;

                ///Delete the persistence file if it exists (e.g. when starting a new run)
                void clear_alt_min_LogL_state() const;

                ///Check persistence file to see if we should be using the alternative min_LogL value
                bool check_alt_min_LogL_state() const;

                ///Retrieve plugin data.
                const Plugin_Loader &operator()() {return plugins;}

                ///Get plugin data for single plugin.
                Plugin_Interface_Details operator()(const std::string &, const std::string &);
                ~pluginInfo();
            };

            ///Access Functor for plugin info.  This will manage all the
            ///plugins including stored and writing resume info.
            extern EXPORT_SYMBOLS pluginInfo plugin_info;

        }

    }

}

#endif
