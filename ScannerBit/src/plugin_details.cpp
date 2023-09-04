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

#include <string>
#include <ostream>
#include <sstream>
#include <iomanip>

#include "gambit/ScannerBit/scanner_utils.hpp"
#include "gambit/ScannerBit/plugin_details.hpp"
#include "gambit/cmake/cmake_variables.hpp"
#include "gambit/Utils/table_formatter.hpp"

namespace Gambit
{

    namespace Scanner
    {

        namespace Plugins
        {
            Plugin_Details::Plugin_Details(const std::string &str) : full_string(str)
            {
                status= "ok";

                std::string::size_type posMid = str.rfind("__v__");
                version = str.substr(posMid + 5);

                std::string::size_type posLast = str.rfind("__t__", posMid - 1);
                type = str.substr(posLast + 5, posMid - posLast - 5);
                plugin = str.substr(0, posLast);
                posLast = version.find("_");
                major_version = StringToInt(version.substr(0, posLast));
                posMid = version.find("_", posLast + 1);
                minor_version = StringToInt(version.substr(posLast + 1, posMid - posLast - 1));
                posLast = version.find("_", posMid + 1);
                patch_version = StringToInt(version.substr(posMid + 1, posLast - posMid - 1));
                release_version = version.substr(posLast + 1);
                version = IntToString(major_version) + "." + IntToString(minor_version) + "." + IntToString(patch_version);
                if (release_version != "")
                    version += "-" + release_version;
            }

            void Plugin_Details::get_status(const YAML::Node &libNode, const YAML::Node &plugNode, const YAML::Node &flagNode)
            {
                std::vector<std::string> linked_libs_plug, found_incs_plug;

                if (plugNode.IsMap())
                {
                    if (plugNode[type] && plugNode[type][plugin] && plugNode[type][plugin][version] && plugNode[type][plugin][version].IsMap())
                    {
                        if (plugNode[type][plugin][version]["reqd_inifile_entries"].IsSequence())
                            reqd_inifile_entries = plugNode[type][plugin][version]["reqd_inifile_entries"].as<std::vector<std::string>>();
                        if (plugNode[type][plugin][version]["reqd_libraries"].IsSequence())
                            reqd_not_linked_libs = plugNode[type][plugin][version]["reqd_libraries"].as<std::vector<std::string>>();
                        if (plugNode[type][plugin][version]["not_linked_libraries"].IsSequence())
                            ini_libs_not_found = plugNode[type][plugin][version]["not_linked_libraries"].as<std::vector<std::string>>();
                        if (plugNode[type][plugin][version]["reqd_include_paths"].IsSequence())
                            reqd_incs_not_found = plugNode[type][plugin][version]["reqd_include_paths"].as<std::vector<std::string>>();
                        if (plugNode[type][plugin][version]["not_found_include_paths"].IsSequence())
                            ini_incs_not_found = plugNode[type][plugin][version]["not_found_include_paths"].as<std::vector<std::string>>();

                        if (plugNode[type][plugin][version]["linked_libraries"].IsSequence())
                            linked_libs_plug = plugNode[type][plugin][version]["linked_libraries"].as<std::vector<std::string>>();
                        if (plugNode[type][plugin][version]["found_include_paths"].IsSequence())
                            found_incs_plug = plugNode[type][plugin][version]["found_include_paths"].as<std::vector<std::string>>();
                    }
                }

                std::string lib = path.substr(path.rfind("/") + 1);
                if (libNode.IsMap())
                {
                    if (libNode[lib] and libNode[lib].IsMap())
                    {
                        std::multimap<std::string, std::string> linked_libs_temp;
                        if (libNode[lib]["linked_libs"] and libNode[lib]["linked_libs"].IsMap())
                        {
                            for (auto it = libNode[lib]["linked_libs"].begin(), end = libNode[lib]["linked_libs"].end(); it != end; ++it)
                            {
                                linked_libs_temp.insert(std::pair<std::string, std::string>(it->first.as<std::string>(), it->second.as<std::string>()));
                            }
                        }

                        for (auto it = linked_libs_plug.begin(), end = linked_libs_plug.end(); it != end; ++it)
                        {
                            auto range = linked_libs_temp.equal_range(*it);
                            if (range.first != range.second)
                                linked_libs.insert(range.first, range.second);
                        }

                        std::vector<std::string> linked_temp;
                        for (auto it = reqd_not_linked_libs.begin(), end = reqd_not_linked_libs.end(); it != end; ++it)
                        {
                            auto range = linked_libs_temp.equal_range(*it);
                            auto range2 = linked_libs.equal_range(*it);
                            if (range.first == range.second)
                            {
                                linked_temp.push_back(*it);
                            }
                            else if (range2.first == range2.second)
                            {
                                linked_libs.insert(range.first, range.second);
                            }
                        }

                        reqd_not_linked_libs = linked_temp;

                        std::multimap<std::string, std::string> found_incs_temp;
                        if (libNode[lib]["found_incs"] and libNode[lib]["found_incs"].IsMap())
                        {
                            for (auto it = libNode[lib]["found_incs"].begin(), end = libNode[lib]["found_incs"].end(); it != end; ++it)
                                found_incs_temp.insert(std::pair<std::string, std::string>(it->first.as<std::string>(), it->second.as<std::string>()));
                        }

                        for (auto it = found_incs_plug.begin(), end = found_incs_plug.end(); it != end; it++)
                        {
                            //cout << *it << endl;
                            found_incs.insert(std::pair<std::string, std::string>(type + "_locations.yaml", *it));
                        }
                        std::vector<std::string> found_temp;
                        for (auto it = reqd_incs_not_found.begin(), end = reqd_incs_not_found.end(); it != end; ++it)
                        {
                            auto range = found_incs_temp.equal_range(*it);
                            if (range.first == range.second)
                            {
                                found_temp.push_back(*it);
                            }
                            else
                            {
                                found_incs.insert(range.first, range.second);
                            }
                        }

                        reqd_incs_not_found = found_temp;
                    }
                }

                if (flagNode.IsMap())
                {
                    if (flagNode[type] && flagNode[type][plugin] && flagNode[type][plugin][version] && flagNode[type][plugin][version].IsMap())
                    {
                        flags = flagNode[type][plugin][version];
                    }
                }

                if (status != "excluded")
                {
                    if (reqd_incs_not_found.size() > 0)
                    {
                        status = "reqd header file(s) not found";
                    }
                    else if (reqd_not_linked_libs.size() > 0)
                    {
                        status = "reqd lib(s) not found";
                    }
                    else if (ini_libs_not_found.size() > 0)
                    {
                        status = "invalid lib path(s) in locations file";
                    }
                    else if (ini_incs_not_found.size() > 0)
                    {
                        status = "invalid include dir(s) in locations file";
                    }
                }
            }

            std::string Plugin_Details::printMin() const
            {
                std::stringstream out;
                out << "plugin:  " << plugin << std::endl;
                out << "version:  " << version << std::endl;
                out << "type:  " << type << std::endl;

                return out.str();
            }

            std::string Plugin_Details::print() const
            {
                std::stringstream out;
                out << "plugin:  " << plugin << std::endl;
                out << "\tversion:  " << version << std::endl;
                out << "\tmajor version:  " << major_version << std::endl;
                out << "\tminor version:  " << minor_version << std::endl;
                out << "\tpatch version:  " << patch_version << std::endl;
                out << "\tplugin path:  " << path << std::endl;
                out << "\ttype:  " << type << std::endl;

                return out.str();
            }

            std::string Plugin_Details::printFull() const
            {
                std::stringstream out;

                /*table_formatter table(type + " PLUGIN", "VERSION", "STATUS");
                table.capitalize_title();
                table.padding(1);
                table << plugin << version;
                if (status == "ok")
                    table.green() << status;
                else
                    table.red() << status;

                out << table.str();*/

                out << "\n\x1b[01m\x1b[04mGENERAL PLUGIN INFO\x1b[0m" << std::endl;
                out << "\nname:     " << plugin;
                out << "\ntype:     " << type;
                out << "\nversion:  " << version;
                out << "\nstatus:   ";
                if (status == "ok")
                    out << "\x1b[32;01m" << status << "\x1b[0m" << std::endl;
                else
                    out << "\x1b[31;01m" << status << "\x1b[0m" << std::endl;

                if (reason.size() > 0)
                {
                    out << "\nreason for exclusion:\n";
                    for (auto it = reason.begin(), end = reason.end(); it != end; ++it)
                        out << "    " << *it << std::endl;
                }

                out << std::endl;

                out << "\n\x1b[01m\x1b[04mHEADER & LINK INFO\x1b[0m" << std::endl;
                out << "\nrequired inifile entries:  ";
                if (reqd_inifile_entries.empty())
                    out << "none" << std::endl;
                else
                    out << reqd_inifile_entries << std::endl;
                out << "\n\x1b[04mlink status\x1b[0m:" << std::endl;
                //out << "-----------" << std::endl;
                if (not reqd_not_linked_libs.empty())
                    out << "    could not find libraries requested by plugin: " << reqd_not_linked_libs << std::endl;
                if (not ini_libs_not_found.empty())
                    out << "    could not find libraries specified in *locations.yaml: " << ini_libs_not_found << std::endl;
                out << "    linked libraries:";
                if (linked_libs.empty())
                {
                    out << " none" << std::endl;
                }
                else
                {
                    out << std::endl;
                    for (auto it = linked_libs.begin(), end = linked_libs.end(); it != end; ++it)
                            out << "        " << it->first << ": " << it->second << std::endl;
                }

                out << "\n\x1b[04minclude header status\x1b[0m:" << std::endl;
                //out << "---------------------" << std::endl;
                if (not reqd_incs_not_found.empty())
                    out << "    could not find headers requested by plugin: " << reqd_incs_not_found << std::endl;
                if (not ini_incs_not_found.empty())
                    out << "    could not find include paths specified in *locations.yaml: " << ini_incs_not_found << std::endl;
                out << "    headers found:";
                if (found_incs.empty())
                {
                    out << " none" << std::endl;
                }
                else
                {
                    out << std::endl;
                    for (auto it = found_incs.begin(), end = found_incs.end(); it != end; ++it)
                            out << "        " << it->first << ": " << it->second << std::endl;
                }

                out << std::endl;

                out << "\n\x1b[01m\x1b[04mDESCRIPTION\x1b[0m\n" << std::endl;

                std::string p_str, description;
                std::string path = GAMBIT_DIR "/config/";
                if (FILE* p_f = popen((std::string("ls ") + path + std::string(" | grep \".dat\" | grep \""+ type + "\"")).c_str(), "r"))
                {
                    char path_buffer[1024];
                    int p_n;
                    while ((p_n = fread(path_buffer, 1, sizeof path_buffer, p_f)) > 0)
                    {
                        std::stringstream p_ss(std::string(path_buffer, p_n));
                        while (p_ss >> p_str)
                        {
                            YAML::Node node = YAML::LoadFile(path + p_str);
                            if (node[plugin])
                            {
                                description = node[plugin].as<std::string>();
                                break;
                            }
                        }
                    }

                    pclose(p_f);
                }

                out << description << std::endl;

                return out.str();
            }
            
            std::string Plugin_Details::printMultiPlugins(const std::vector<const Plugin_Details *> &plugins)
            {
                std::stringstream out;

                if (plugins.empty())
                    return "";
                else if (plugins.size() == 1)
                    return plugins[0]->printFull();
                
                out << "\n\x1b[01m\x1b[04mGENERAL PLUGIN INFO\x1b[0m" << std::endl;
                out << "\nname:     " << plugins[0]->plugin;
                out << "\ntype:     " << plugins[0]->type;
                out << "\nversions: ";
                out << plugins[0]->version;
                for (int i = 1, end = plugins.size(); i < end; ++i)
                {
                    out << ", " << plugins[i]->version;
                }
                out << "\nstatus:   ";
                for (auto &&plug : plugins)
                {
                    out << "\n    " << plug->version << ":  ";
                    if (plug->status == "ok")
                        out << "\x1b[32;01m" << plug->status << "\x1b[0m";
                    else
                        out << "\x1b[31;01m" << plug->status << "\x1b[0m";
                }
                out << std::endl;

                bool exclude{false};
                for (auto&& plug : plugins)
                {
                    if (not plug->reason.empty())
                    {
                        exclude = true;
                        break;
                    }
                }

                if (exclude)
                {
                    out << "\nreason for exclusion:";
                    for (auto &&plug : plugins)
                    {
                        out << "\n    " << plug->version << ":\n";
                        for (auto it = plug->reason.begin(), end = plug->reason.end(); it != end; ++it)
                            out << "        " << *it << std::endl;
                    }
                }

                out << std::endl;

                out << "\n\x1b[01m\x1b[04mHEADER & LINK INFO\x1b[0m" << std::endl;
                out << "\n\x1b[04mrequired inifile entries\x1b[0m:";
                for (auto &&plug : plugins)
                {
                    out << "\n    " << plug->version << ":  ";
                    if (plug->reqd_inifile_entries.empty())
                        out << "none";
                    else
                        out << plug->reqd_inifile_entries;
                }
                out << std::endl;
                out << "\n\x1b[04mlink status\x1b[0m:" << std::endl;
                for (auto &&plug : plugins)
                {
                    out << "    " << plug->version << ":\n";
                    if (not plug->reqd_not_linked_libs.empty())
                    {
                        out << "        could not find libraries requested by plugin: " << plug->reqd_not_linked_libs << std::endl;
                    }
                    if (not plug->ini_libs_not_found.empty())
                    {
                        out << "        could not find libraries specified in *locations.yaml: " << plug->ini_libs_not_found << std::endl;
                    }
                
                    out << "        linked libraries:";
                    if (plug->linked_libs.empty())
                    {
                        out << " none" << std::endl;
                    }
                    else
                    {
                        out << std::endl;
                        for (auto it = plug->linked_libs.begin(), end = plug->linked_libs.end(); it != end; ++it)
                                out << "            " << it->first << ": " << it->second << std::endl;
                    }
                    out << std::endl;
                }

                out << "\x1b[04minclude header status\x1b[0m:" << std::endl;
                for (auto &&plug : plugins)
                {
                    out << "    " << plug->version << ":\n";
                    if (not plug->reqd_incs_not_found.empty())
                        out << "        could not find headers requested by plugin: " << plug->reqd_incs_not_found << std::endl;
                    if (not plug->ini_incs_not_found.empty())
                        out << "        could not find include paths specified in *locations.yaml: " << plug->ini_incs_not_found << std::endl;
                    out << "        headers found:";
                    if (plug->found_incs.empty())
                    {
                        out << " none" << std::endl;
                    }
                    else
                    {
                        out << std::endl;
                        for (auto it = plug->found_incs.begin(), end = plug->found_incs.end(); it != end; ++it)
                                out << "            " << it->first << ": " << it->second << std::endl;
                    }
                    out << std::endl;
                }
                out << std::endl;

                out << "\x1b[01m\x1b[04mDESCRIPTION\x1b[0m\n" << std::endl;

                out << get_description(plugins) << std::endl;

                return out.str();
            }

            std::string Plugin_Details::get_description(const std::vector<const Plugin_Details *> &plugins) {
                std::string description;
                std::string p_str;
                const std::string path = GAMBIT_DIR "/config/";
                if (FILE* p_f = popen((std::string("ls ") + path + std::string(" | grep \".dat\" | grep \""+ plugins[0]->type + "\"")).c_str(), "r"))
                {
                    char path_buffer[1024];
                    int p_n;
                    while ((p_n = fread(path_buffer, 1, sizeof path_buffer, p_f)) > 0)
                    {
                        std::stringstream p_ss(std::string(path_buffer, p_n));
                        while (p_ss >> p_str)
                        {
                            YAML::Node node = YAML::LoadFile(path + p_str);
                            if (node[plugins[0]->plugin])
                            {
                                description = node[plugins[0]->plugin].as<std::string>();
                                break;
                            }
                        }
                    }

                    pclose(p_f);
                }
                return description;
            }

            bool Plugin_Version_Supersedes(const Plugin_Details &plug1, const Plugin_Details &plug2)
            {
                if (plug1.major_version > plug2.major_version)
                {
                    return true;
                }
                else if (plug1.major_version == plug2.major_version)
                {
                    if (plug1.minor_version > plug2.minor_version)
                    {
                        return true;
                    }
                    else if (plug1.minor_version == plug2.minor_version)
                    {
                        if (plug1.patch_version > plug2.patch_version)
                        {
                            return true;
                        }
                        else if (plug1.patch_version == plug2.patch_version)
                        {
                            if (plug1.release_version == "" && plug2.release_version != "")
                            {
                                return true;
                            }
                        }
                    }
                }

                return false;
            }

        }

    }

}
