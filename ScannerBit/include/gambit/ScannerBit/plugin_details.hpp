//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  Class to hold details of scanner plugins and
///  define simple comparison operations on them. 
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

#ifndef __PLUGIN_DETAILS_HPP
#define __PLUGIN_DETAILS_HPP

#include <vector>
#include "yaml-cpp/yaml.h"

namespace Gambit
{
    
    namespace Scanner
    {
        
        namespace Plugins
        {
            
            ///container info for a specific plugin
            struct Plugin_Details
            {
                ///version string: maj.min.patch-release
                std::string version;
                ///major version number
                int major_version;
                ///minor version number
                int minor_version;
                ///patch version number
                int patch_version;
                ///status, not set right now
                std::string status;
                ///reason is excluded
                std::vector<std::string> reason;
                ///release version
                std::string release_version;
                ///full path to library containing plugin
                std::string path;
                ///plugin name
                std::string plugin;
                ///plugin type
                std::string type;
                ///full string that ScannerBit sees
                std::string full_string;
                ///inifile entries requested my plugin in the "reqd_inifile_entries(...)" function
                std::vector<std::string> reqd_inifile_entries;
                ///libraries that were not linked but requested by the "reqd_libraries(...)" function
                std::vector<std::string> reqd_not_linked_libs;
                ///libraries specified in the "locations.yaml" file but not found
                std::vector<std::string> ini_libs_not_found;
                ///list of all libraries that are linked:  {lib_name: path_to_lib}
                std::multimap<std::string, std::string> linked_libs;
                ///requested include files that were not found
                std::vector<std::string> reqd_incs_not_found;
                ///paths specified in the "locations.yaml" file but where not found
                std::vector<std::string> ini_incs_not_found;
                ///list of all files that were found:  {file_name: include_path_to_file}
                std::multimap<std::string, std::string> found_incs;
                ///flag list
                mutable YAML::Node flags;
                
                Plugin_Details(){}
                
                std::multimap<std::string, std::string> linked_libraries() const {return linked_libs;}
                
                Plugin_Details(const std::string &str);
                
                void get_status(const YAML::Node &, const YAML::Node &, const YAML::Node &);

                static std::string get_description(const std::vector<const Plugin_Details *> &plugins);
                
                std::string printMin() const;
                
                std::string print() const;
                
                std::string printFull() const;
                
                static std::string printMultiPlugins(const std::vector<const Plugin_Details *> &);
            };
            
            inline bool operator == (const Plugin_Details &plug1, const Plugin_Details &plug2)
            {
                if ((plug1.major_version != plug2.major_version) ||
                    (plug1.major_version != plug2.major_version) ||
                    (plug1.minor_version != plug2.minor_version) ||
                    (plug1.release_version == "" && plug2.release_version != "") ||
                    (plug1.release_version != "" && plug2.release_version == ""))
                {
                    return false;
                }
                
                return true;
            }
            
            class Plugin_Details_Ref
            {
            private:
                mutable const Plugin_Details *details;
                
            public:
                Plugin_Details_Ref() {}
                Plugin_Details_Ref(const Plugin_Details &details) : details(&details) {}
                Plugin_Details_Ref(const Plugin_Details_Ref &details) : details(details.details) {}
                
                //const Plugin_Details_Ref &operator = (const Plugin_Details &details_in) const
                //{
                //    details = &details_in;
                //    return *this;
                //}
                
                const Plugin_Details_Ref &operator = (const Plugin_Details_Ref &details_in) const
                {
                    details = details_in.details;
                    return *this;
                }
                
                //Plugin_Details_Ref &operator = (Plugin_Details &details_in)
                //{
                //    details = &details_in;
                //    return *this;
                //}
                
                Plugin_Details_Ref &operator = (Plugin_Details_Ref &details_in)
                {
                    details = details_in.details;
                    return *this;
                }
                
                operator Plugin_Details &(){return *(Plugin_Details *)details;}
                operator const Plugin_Details &() const {return *details;}
            };
            
            ///compares the user defined plugin version to the actual plugin version.
            bool Plugin_Version_Supersedes(const Plugin_Details &plug1, const Plugin_Details &plug2);
                                
        }
        
    }
    
}

#endif
