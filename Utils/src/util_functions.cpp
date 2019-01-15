//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  General small utility functions.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (patscott@physics.mcgill.ca)
///  \date 2013 Apr, July, Aug, Sep
///  \date 2014 Mar
///
///  \author Ben Farmer
///          (benjamin.farmer@monash.edu.au)
///  \date 2013 May, June, July
///
///  *********************************************

/// Standard libraries
#include <cstring>
#include <chrono>  // chrono::system_clock
#include <ctime>   // localtime
#include <cctype>  // ::tolower function
#include <sstream> // stringstream
#include <string>  // string

/// POSIX filesystem libraries
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <libgen.h>

/// Gambit
#include "gambit/Utils/util_functions.hpp"


namespace Gambit
{

  namespace Utils
  {

    const char* whitespaces[] = {" ", "\t", "\n", "\f", "\r"};

    /// Split a string into a vector of strings using a delimiter,
    /// and remove any whitespace around the delimiters.
    std::vector<str> delimiterSplit(str s, str delim)
    {
      std::vector<str> vec;
      // Get rid of any whitespace around the delimiters
      #if GAMBIT_CONFIG_FLAG_use_regex     // Using regex :D
        regex rgx1("\\s+"+delim), rgx2(delim+"\\s+");
        s = regex_replace(s, rgx1, delim);
        s = regex_replace(s, rgx2, delim);
      #else                                // Using lame-o methods >:(
        str previous = s+".";
        while (s != previous)
        {
          previous = s;
          for (int i = 0; i != 5; i++)
          {
            boost::replace_all(s, whitespaces[i]+delim, delim);
            boost::replace_all(s, delim+whitespaces[i], delim);
          }
        }
      #endif
      if (s == "") return vec;
      // Split up the list of versions by the delimiters
      boost::split(vec, s, boost::is_any_of(delim), boost::token_compress_on);
      return vec;
    }

    /// Strips namespace from the start of a string, or after "const".
    str strip_leading_namespace(str s, str ns)
    {
      #if GAMBIT_CONFIG_FLAG_use_regex     // Using regex :D
        regex expression("(^|[\\s\\*\\&\\(\\,\\[])"+ns+"::");
        s = regex_replace(s, expression, str("\\1"));
      #else                                // Using lame-o methods >:(
        int len = ns.length() + 2;
        if (s.substr(0,len) == ns+str("::")) s.replace(0,len,"");
        boost::replace_all(s, str(",")+ns+"::", str(","));
        boost::replace_all(s, str("*")+ns+"::", str("*"));
        boost::replace_all(s, str("&")+ns+"::", str("&"));
        boost::replace_all(s, str("(")+ns+"::", str("("));
        boost::replace_all(s, str("[")+ns+"::", str("["));
        for (int i = 0; i != 5; i++)
        {
          boost::replace_all(s, whitespaces[i]+ns+"::", whitespaces[i]);
        }
      #endif
      return s;
    }

    /// Strips all whitespaces from a string, but re-inserts a single regular space after "const".
    void strip_whitespace_except_after_const(str &s)
    {
      str tempstr("__TEMP__"), empty(""), constdec2("const ");
      #if GAMBIT_CONFIG_FLAG_use_regex     // Using regex :D
        regex constdec1("const\\s+"), temp(tempstr), whitespace("\\s+");
        s = regex_replace(s, constdec1, tempstr);
        s = regex_replace(s, whitespace, empty);
        s = regex_replace(s, temp, constdec2);
      #else                                // Using lame-o methods >:(
        str previous = s+".";
        while (s != previous)
        {
          previous = s;
          for (int i = 0; i != 5; i++)
          {
            boost::replace_all(s, str("const")+whitespaces[i], tempstr);
            s.erase(std::remove(s.begin(), s.end(), *whitespaces[i]), s.end());
          }
        }
        boost::replace_all(s, tempstr, constdec2);
      #endif
    }

    /// Strips leading and/or trailing parentheses from a string.
    void strip_parentheses(str &s)
    {
      if (s.at(0) == '(')       s = s.substr(1, s.size());
      if (*s.rbegin() == ')')   s = s.substr(0, s.size()-1);
    }

    /// Created a std::string of a specified length.
    str str_fixed_len(str s, int len)
    {
      int oldlen = s.length();
      if (oldlen > len)
      {
        return s.substr(0,len-1);
      }
      else if (oldlen < len)
      {
        s.append(len-oldlen,' ');
      }
      return s;
    }

    /// Check if a string represents an integer
    /// From: http://stackoverflow.com/a/2845275/1447953
    bool isInteger(const std::string & s)
    {
       if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false ;

       char * p ;
       strtol(s.c_str(), &p, 10) ;

       return (*p == 0) ;
    }

    /// Copy a std::string to a character array, stripping the null termination character.  Good for sending to Fortran.
    void strcpy2f(char* arr, int len, str s)
    {
      s = str_fixed_len(s, len-1);
      strcpy(arr, s.c_str());
      arr[len-1] = ' ';
    }

    /// Perform a simple case-insensitive string comparison
    /// From: https://stackoverflow.com/a/4119881/1447953
    bool iequals(const std::string& a, const std::string& b, bool case_sensitive)
    {
        if(case_sensitive)
            return a==b;
        unsigned int sz = a.size();
        if (b.size() != sz)
            return false;
        for (unsigned int i = 0; i < sz; ++i)
            if (tolower(a[i]) != tolower(b[i]))
                return false;
        return true;
    }

    /// Ensure that a path exists (and then return the path, for chaining purposes)
    const std::string& ensure_path_exists(const std::string& path)
    {
       // Split off potential filename
       // If only path is provided, it must end in a slash!!!
       size_t found = path.find_last_of("/\\");
       if (found != std::string::npos)
       {
         std::string prefix = path.substr(0,found);
         recursive_mkdir( prefix.c_str() );
       }
       return path;
    }

    /// Check if a file exists
    bool file_exists(const std::string& filename)
    {
        //std::ifstream file(filename);
        //return not file.fail();
        struct stat buffer;
        return (stat(filename.c_str(), &buffer) == 0);
    }

    /// Return a vector of strings listing the contents of a directory (POSIX)
    /// Based on http://www.gnu.org/software/libtool/manual/libc/Simple-Directory-Lister.html
    std::vector<std::string> ls_dir(const std::string& dir)
    {
      std::vector<std::string> dir_contents;
      DIR *dp;
      struct dirent *ep;
      dp = opendir(dir.c_str());

      if( dp != NULL )
      {
        while( (ep = readdir(dp)) )
        {
          dir_contents.push_back(ep->d_name);
        }
        (void) closedir(dp);
      }
      else
      {
        std::string msg = "Utils::ls_dir function failed to open the directory '"+dir+"'!";
        std::cerr << msg << std::endl;
        abort();
      }
      return dir_contents;
    }

    /// Get directory name from full path+filename (POSIX)
    std::string dir_name(const std::string& path)
    {
       char buffer[1000]; // temporary buffer for dirname to work with (it is a C function)
       path.copy(buffer, path.size()); //TODO: error if path.size()>1000
       buffer[path.size()] = '\0';
       std::string result = dirname(&buffer[0]); // should use the C function...
       return result;
    }

    /// Get file name from full path+filename (POSIX)
    std::string base_name(const std::string& path)
    {
       char buffer[1000]; // temporary buffer for basename to work with (it is a C function)
       path.copy(buffer, path.size()); //TODO: error if path.size()>1000
       buffer[path.size()] = '\0';
       std::string result = basename(&buffer[0]); // should use the C function...
       return result;
    }

    /// Delete all files in a directory (does not act recursively)
    int remove_all_files_in(const str& dirname, bool error_if_absent)
    {
      struct dirent *pDirent;
      DIR *pDir;
      pDir = opendir(dirname.c_str());
      if (pDir == NULL)
      {
        if (error_if_absent)
        {
          utils_error().raise(LOCAL_INFO, "Directory "+dirname+" not found.");
        }
        else
        {
          return 1;
        }
      }
      while ( (pDirent = readdir(pDir)) != NULL )
      {
        // Delete the contents
        if ( strcmp(pDirent->d_name, ".") and strcmp(pDirent->d_name, "..") )
        {
          std::ostringstream ss;
          ss << dirname << pDirent->d_name;
          cout << "Deleting " << ss.str() << endl;
          remove(ss.str().c_str());
        }
      }
      closedir (pDir);
      return 0;
    }

    /// Get current system clock time
    time_point get_clock_now()
    {
        return std::chrono::system_clock::now();
    }

    /// Return (locally defined) date and time corresponding to time_point
    std::string return_time_and_date(const time_point& in)
    {
        std::time_t t = std::chrono::system_clock::to_time_t(in);

        std::string ts = std::ctime(&t); // for example : Tue Sep 27 14:21:13 2011\n
        ts.resize(ts.size()-1); // Remove the annoying trailing newline
        return ts;
    }

    /// Check if two strings are a "close" match
    /// Used for "did you mean?" type checking during command line argument processing
    bool are_similar(const std::string& s1, const std::string& s2)
    {
      if(check1(s1,s2) or check1(s2,s1)){ return true; }
      else if(check2(s1,s2)){ return true; } // symmetric
      else{ return false; }
      //TODO: Add more checks? These ones are pretty minimal. Maybe something that computes percentage match between strings...
    }

    /// true if s1 can be obtained by deleting one character from s2
    bool check1(const std::string& s1, const std::string& s2)
    {
      if(s2.length() - s1.length() != 1){ return false; }
      unsigned int i,j;
      for(i=0,j=0; i<s2.length(); i++,j++)
      {
          if(s2[i] == s1[j])
          {/*do  nothing*/}
          else if(i == j)
          { j++;}
          else
          {return false;}
      }
      return true;
    }

    /// true if s1 can be obtained from s2 by changing no more than X characters (X=2 for now)
    bool check2(const std::string& s1, const std::string& s2)
    {
      unsigned int error_limit = 2;
      unsigned int number_of_errors = 0;

      if(s2.length() != s1.length()){ return false; }
      unsigned int i,j;
      for(i=0,j=0; i<s2.length(); i++,j++)
      {
          if(s2[i] == s1[j])
          {/*do  nothing*/}
          else if(number_of_errors <= error_limit)
          { number_of_errors++;}
          else
          {return false;}
      }
      return true;
    }

    /// returns square of double - saves tedious repetition
    double sqr(double a)
    {
      return a * a;
    }

    /// Checks whether `str' ends with `suffix'
    // credit: http://stackoverflow.com/a/41041484/1447953
    bool endsWith(const std::string& str, const std::string& suffix)
    {
      if (&suffix == &str) return true; // str and suffix are the same string
      if (suffix.length() > str.length()) return false;
      size_t delta = str.length() - suffix.length();
      for (size_t i = 0; i < suffix.length(); ++i) {
          if (suffix[i] != str[delta + i]) return false;
      }
      return true;
    }

    // Inspired by the above. Checks whether 'str' begins with 'prefix'
    bool startsWith(const std::string& str, const std::string& prefix, bool case_sensitive)
    {
      if (&prefix == &str) return true; // str and prefix are the same string
      if (prefix.length() > str.length()) return false;
      for (size_t i = 0; i < prefix.length(); ++i) {
          if(case_sensitive)
          {
             if (prefix[i] != str[i]) return false;
          }
          else
          {
             if (tolower(prefix[i]) != tolower(str[i])) return false; 
          }
      }
      return true;
    }


  }

}
