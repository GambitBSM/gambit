//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Simple reader for ASCII tables
///
///  *********************************************
///
///  Authors (add name and date if you modify):
//
///  \author Janina Renk
///          <janina.renk@fysik.su.se>
///  \date Oct 2018
///
///  *********************************************

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>

#include "gambit/Utils/standalone_error_handlers.hpp"
#include "gambit/Utils/local_info.hpp"

#ifndef __ASCIIdictReader__
#define __ASCIIdictReader__

// Usage:
//    ASCIIdictReader ascii(filename);
//    ascii.setcolnames("mass", "BR1", "BR2");
//    std::cout << ascii["mass"][0] << std::endl;
//    std::cout << ascii["BR1"][1] << std::endl;
//    std::cout << ascii["BR2"][2] << std::endl;

namespace Gambit
{
  class ASCIIdictReader
  {
    public:
      ASCIIdictReader(std::string filename)
      {
        duplicate = false;
        read(filename);
      };
      ASCIIdictReader() {};  // Dummy initializer
      ~ASCIIdictReader() {}

      int read(std::string filename);
      const std::vector<std::string>& get_keys() const {return keys;}
      const std::map<std::string,std::vector<double>>& get_dict() const {return dict;}
      bool duplicated_keys() const {return duplicate;}
      int nrow() const {return keys.size();}

    private:
      std::map<std::string,std::vector<double>> dict;
      std::vector<std::string> keys;
      bool duplicate;
  };
}

#endif // defined __ASCIIdictReader__
