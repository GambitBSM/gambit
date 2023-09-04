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

#include "gambit/Utils/ascii_dict_reader.hpp"

namespace Gambit
{


  int ASCIIdictReader::read(std::string filename)
  { 
    std::ifstream in(filename.c_str(), std::ios::binary);
    if (in.fail())
    { 
      std::ostringstream errmsg;
      errmsg << "Failed to read file '"<< filename <<"'. Check if file exists.";
      utils_error().raise(LOCAL_INFO, errmsg.str());
    }

    std::string line;
    while(std::getline(in, line))
    {
      if (line[0] == '#' || line.empty() ) continue;  // Ignore comments lines, starting with "#" and empty lines
      std::stringstream ss(line);

      double tmp;
      std::string key;
      std::vector<double> data_tmp;

      ss >> key;
      while(ss >> tmp)
      {
        data_tmp.push_back(tmp);
      }
  

      if (std::find(keys.begin(), keys.end(), key) != keys.end())
      {
        duplicate = true;
      }

      dict[key] = data_tmp;
      keys.push_back(key); 
      
    }
    in.close();
    return 0;
  }



}
