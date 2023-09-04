//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  Advanced comparison utilities for scanner plugins.
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

#include <sstream>

#include "gambit/ScannerBit/plugin_comparators.hpp"
#include "gambit/ScannerBit/scanner_utils.hpp"

namespace Gambit
{

        namespace Scanner
        {

                namespace Plugins
                {
                
                        VersionCompareBottom::VersionCompareBottom (const std::string &version) : flag (0x00)
                        {
                                if (version.find_first_not_of(" !()|&=<>") == std::string::npos)
                                {
                                        flag = 0x00;
                                        setEmpty(true);
                                        return;
                                }
                                else
                                {
                                        std::string::size_type i;
                                        for (i = 0; i < version.length(); i++)
                                        {
                                                if (version[i] == '<')
                                                        flag |= LESS;
                                                else if (version[i] == '>')
                                                        flag |= GREATER;
                                                else if (version[i] == '=')
                                                        flag |= EQUAL;
                                                else if (version[i] == '!')
                                                        flag |= NEG;
                                                else if (version[i] != ' ' && version[i] != '|' && version[i] != '&')
                                                        break;
                                        }
                                        
                                        if (i == version.length())
                                        {
                                                flag = 0x00;
                                                return;
                                        }
                                        
                                        if (!bool(flag))
                                                flag = EQUAL;
                                        
                                        std::string::size_type pos = version.find("-", i);
                                        std::string number;
                                        
                                        if (pos != std::string::npos)
                                        {
                                                flag |= RELEASE;
                                                release_version = version.substr(pos + 1);
                                                number = version.substr(i, pos - i);
                                        }
                                        else
                                        {
                                                number = version.substr(i);
                                        }
                                        
                                        pos = number.find(".");
                                        if (pos != std::string::npos)
                                        {
                                                flag |= MAJOR;
                                                major_version = StringToInt(number.substr(0, pos));
                                                
                                                i = number.find(".", pos + 1);
                                                if (i != std::string::npos)
                                                {
                                                        flag |= MINOR;
                                                        minor_version = StringToInt(number.substr(pos + 1, i - pos - 1));
                                                        
                                                        pos = number.find(".", i + 1);
                                                        
                                                        if (pos != std::string::npos)
                                                        {
                                                                flag |= PATCH;
                                                                patch_version = StringToInt(number.substr(i + 1, pos - i - 1));
                                                                
                                                                if (!bool(flag&RELEASE))
                                                                {
                                                                        flag |= RELEASE;
                                                                        release_version = number.substr(pos + 1);
                                                                }
                                                        }
                                                        else
                                                        {
                                                                flag |= PATCH;
                                                                patch_version = StringToInt(number.substr(i + 1));
                                                        }
                                                }
                                        }
                                }
                                
                                unsigned char comp = (flag << 4);
                                comp >>= 4;
                                
                                if (comp == (EQUAL|GREATER|LESS|NEG) ||
                                        comp == (GREATER|LESS|NEG) ||
                                        comp == (EQUAL|NEG) ||
                                        comp == (NEG))
                                                f = neq;
                                else if (comp == (EQUAL|GREATER|LESS) ||
                                        comp == (GREATER|LESS) ||
                                        comp == (EQUAL))
                                                f = eq;
                                else if (comp == (EQUAL|GREATER|NEG) ||
                                        comp == (LESS))
                                                f = lt;
                                else if (comp == (EQUAL|LESS|NEG) ||
                                        comp == (GREATER))
                                                f = gt;
                                else if (comp == (LESS|NEG) ||
                                        comp == (EQUAL|GREATER))
                                                f = gte;
                                else if (comp == (GREATER|NEG) ||
                                        comp == (EQUAL|LESS))
                                                f = lte;
                        }
                        
                        bool VersionCompareBottom::operator() (const Plugin_Details &plugin)
                        {
                                if ((bool(flag&MAJOR) && (!f(plugin.major_version, major_version))) ||
                                        (bool(flag&MINOR) && (!f(plugin.minor_version, minor_version))) ||
                                        (bool(flag&PATCH) && (!f(plugin.patch_version, patch_version))) ||
                                        (bool(flag&RELEASE) && plugin.release_version != release_version))
                                {
                                        return false;
                                }
                                
                                return true;
                        }
                
                        VersionCompare::VersionCompare(const std::string &version) : compare1(NULL), compare2(NULL), flag(0x00)
                        {
                                std::string::size_type p_pos = version.find_first_of("(|&");
                                
                                if (version.find_first_not_of(" !()|&=<>") == std::string::npos)
                                {
                                        setEmpty(true);
                                }
                                else if (p_pos == std::string::npos)
                                {
                                        compare1 = new VersionCompareBottom(version);
                                }
                                else if (version[p_pos] == '|')
                                {
                                        flag |= OR;
                                        compare1 = new VersionCompare(version.substr(0, p_pos));
                                        compare2 = new VersionCompare(version.substr(p_pos + 1));
                                }
                                else if (version[p_pos] == '&')
                                {
                                        flag |= AND;
                                        compare1 = new VersionCompare(version.substr(0, p_pos));
                                        compare2 = new VersionCompare(version.substr(p_pos + 1));
                                }
                                else if (version[p_pos] == '(' && p_pos == version.find_first_not_of(" "))
                                {
                                        unsigned int p_num = 1;
                                        std::string::size_type pos = p_pos;
                                        
                                        for (;;)
                                        {
                                                pos = version.find_first_of("()", pos + 1);
                                                if (pos != std::string::npos)
                                                {
                                                        if (version[pos] == '(')
                                                        {
                                                                p_num++;
                                                        }
                                                        else
                                                        {
                                                                p_num--;
                                                                if (p_num == 0)
                                                                {
                                                                        compare1 = new VersionCompare(version.substr(p_pos +1, pos - p_pos - 1));
                                                                        pos = version.find_first_of("&|", pos + 1);
                                                                        if (pos == std::string::npos)
                                                                        {
                                                                        }
                                                                        else if (version[pos] == '|')
                                                                        {
                                                                                flag |= OR;
                                                                                compare2 = new VersionCompare(version.substr(pos + 1));
                                                                        }
                                                                        else if (version[pos] == '&')
                                                                        {
                                                                                flag |= AND;
                                                                                compare2 = new VersionCompare(version.substr(pos + 1));
                                                                        }
                                                                        
                                                                        break;
                                                                }
                                                        }
                                                }
                                                else
                                                {
                                                        compare1 = new VersionCompare(version.substr(pos + 1));
                                                        break;
                                                }
                                        }
                                }
                                else
                                {
                                        scan_err << "Could not parse version string \"" << version << "\"." << scan_end;
                                }
                                
                                if (compare1 != NULL && compare1->isEmpty())
                                {
                                        delete compare1;
                                        compare1 = NULL;
                                }
                                
                                if (compare2 != NULL && compare2->isEmpty())
                                {
                                        delete compare2;
                                        compare2 = NULL;
                                }
                                
                                if (compare1 == NULL && compare2 == NULL)
                                        setEmpty(true);
                                
                                return;
                        }
                        
                        bool VersionCompare::operator() (const Plugin_Details &plugin)
                        {
                                if (compare1 == NULL && compare2 == NULL)
                                {
                                        return true;
                                }
                                else if (compare1 == NULL && compare2 != NULL)
                                {
                                        return (*compare2)(plugin);
                                }
                                else if (compare1 != NULL && compare2 == NULL)
                                {
                                        return (*compare1)(plugin);
                                }
                                
                                if (bool(flag&OR))  return (*compare1)(plugin) || (*compare2)(plugin);
                                if (bool(flag&AND)) return (*compare1)(plugin) && (*compare2)(plugin);

                                // None of the previous pieces of code have triggered; something must be wrong.
                                scan_err << "Unknown logical operator in VersionCompare () operator." << scan_end;
                                return false;                                
                        }
                        
                        VersionCompare::~VersionCompare()
                        {
                                if (compare1 != NULL)
                                        delete compare1;
                                if (compare2 != NULL)
                                        delete compare2;
                        }

                }

       }

}

