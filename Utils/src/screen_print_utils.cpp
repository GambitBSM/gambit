//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
/// \file
///  Utility Functions for the Gambit Scanner
///
///  *********************************************
///
///  Authors
///  =======
///
///  (add name and date if you modify)
///
///  \author Gregory Martinez
///          (gregory.david.martinez@gmail.com)
///  \date 2015 Sep
///
///  *********************************************

/*
 * To get the screen, use
 * int width = get_screen_cols();
 * This will return -1 if it can't
 * To print a string through less, do
 * print_to_screen(string, file_name);
 * Will print to 'more' if there is no 'less
 */

#include <cstdlib>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <utility>

#include <iostream>

#include "gambit/Utils/screen_print_utils.hpp"
#include "gambit/Utils/standalone_error_handlers.hpp"
#include "gambit/Utils/util_macros.hpp"

namespace Gambit
{
    /********************************************/
    /****** adds spaces to fit to screen ********/
    /********************************************/

    inline void add_screen_spaces(std::string &str, std::string::size_type size, std::string::size_type indent)
    {
        std::stringstream ss(str.substr(indent));
        std::string word;
        std::string::size_type words =0;

        while (ss >> word){words++;}
        words--;
        if (words <= 0)
            return;
        std::string::size_type to_add = (size - str.length())/(words);
        std::string::size_type extras = (size - str.length())%(words);
        std::string::size_type extras_even = words/2;
        std::string::size_type extras_odd = words - extras_even;
        if (extras > extras_odd)
        {
            extras_even = extras - extras_odd;
        }
        else
        {
            extras_odd = extras;
            extras_even = 0;
        }

        std::string::size_type pos = str.find_first_not_of(" ", indent);
        pos = str.find_first_of(" ", pos);
        int i = 0;
        while (pos != std::string::npos)
        {
            i++;
            if (i%2 == 0 && extras_even > 0)
            {
                str.insert(pos, to_add + 1, ' ');
                extras_even--;
            }
            else if (i%2 == 1 && extras_odd > 0)
            {
                str.insert(pos, to_add + 1, ' ');
                extras_odd--;
            }
            else if (to_add > 0)
            {
                str.insert(pos, to_add, ' ');
            }

            pos = str.find_first_not_of(" ", pos);
            pos = str.find_first_of(" ", pos);
        }
    }

    /*********************************************/
    /****** formats output for the screen ********/
    /*********************************************/

    std::string format_for_screen(const std::string &input_string)
    {
        int cols = get_screen_cols();
        std::string output_string, str;
        std::stringstream ss(input_string);

        if (cols > 0)
        {
            std::string::size_type cols_pos = cols;
            while (std::getline(ss, str))
            {
                bool add_n = false;
                std::string line = str;

                if (str.length() >= 16 && str.substr(0, 16) == "#remove_newlines")
                {
                    bool ck_space = false;
                    line = "";

                    while(std::getline(ss, str))
                    {
                        if (str.length() >= 21 && str.substr(0, 21) == "#dont_remove_newlines")
                        {
                            break;
                        }
                        else if (str.find_first_not_of(" ") == std::string::npos)
                        {
                            add_n = true;
                            break;
                        }
                        else if (!(str.length() > 0 && str[0] == '#'))
                        {
                            if (ck_space)
                            {
                                if (str[0] != ' ')
                                    line += " ";

                                ck_space = false;
                            }

                            if (str[str.length()-1] != ' ')
                                ck_space = true;

                            line += str;
                        }
                    }
                }

                std::string::size_type len = line.find_last_not_of(" ");
                if (len == std::string::npos || line.length() == 0)
                {
                    output_string += "\n";
                }
                else if (!(line.length() > 0 && line[0] == '#'))
                {
                    line = line.substr(0, len+1);

                    std::string::size_type cols_corr = line.find_first_of("\x1b");
                    std::string::size_type indent = line.find_first_not_of(" ");
                    std::string::size_type colon_indent = line.find_first_of(":");

                    if (colon_indent != std::string::npos && 2*colon_indent < cols_pos)
                    {
                        indent = line.find_first_not_of(" ", colon_indent +1);
                    }

                    for (;;)
                    {
                        if ((cols_corr == std::string::npos) && (line.length() > cols_pos))
                        {
                            std::string temp = separate_line(line, indent, cols_pos);
                            add_screen_spaces(temp, cols_pos, indent);
                            output_string += temp + "\n";
                        }
                        else
                        {
                            output_string += line + "\n";
                            break;
                        }
                    }

                    if (add_n)
                        output_string += "\n";
                }
            }
        }
        else
        {
            while(std::getline(ss, str))
            {
                if (!(str.length() > 0 && str[0] == '#'))
                {
                    str = str.substr(0, str.find_last_not_of(" ")+1);
                    output_string += str + "\n";
                }
            }
        }

        return output_string;
    }

    /*************************************************/
    /****** pipes output through less or more ********/
    /*************************************************/

    void print_to_screen(const std::string &file_in, const std::string &name)
    {
        if (file_in.empty()) return;

        std::string file = format_for_screen(file_in);
        char temp_file[20] = "_gambit_temp_XXXXXX";
        int err = mkstemp(temp_file);
        if (err == -1) utils_error().raise(LOCAL_INFO, "Error returned from mkstemp.");
        std::ofstream out(temp_file);
        out << file << std::flush;
        if (std::system("command -v less >/dev/null"))
        {
            err = std::system((std::string("more -d ") + std::string(temp_file)).c_str());
            if (err) utils_error().raise(LOCAL_INFO, "Error returned from call to more.");
        }
        else
        {
            err = std::system((std::string("less -S -R -P\"Gambit diagnostic ") + name + std::string(" line %l (press h for help or q to quit)\" ") + std::string(temp_file)).c_str());
            if (err) utils_error().raise(LOCAL_INFO, "Error returned from call to less.");
        }
        err = std::system(("rm -f " + std::string(temp_file) + " >/dev/null").c_str());
        if (err) utils_error().raise(LOCAL_INFO, "Error returned from attempt to remove temp file.");
    }

}
