/*
This file is for demonstrating how one can compare two slha files using slhaea.
 */
#include <fstream>
#include <iostream>
#include <string> 
#include "../../contrib/slhaea/include/SLHAea/slhaea.h"


bool is_close_rel_tol(double a, double b, double tol = std::numeric_limits<double>::epsilon() ) {
   //first avoid division by zero
   // check if zero with numerical precision 
   if(std::abs(a - b) < std::numeric_limits<double>::epsilon())
      return true;
   if(std::abs(a) < std::numeric_limits<double>::epsilon()
      || std::abs(b) < std::numeric_limits<double>::epsilon())
      return false;

   return std::abs((a-b)/a) < tol;
}

int main()
{
  std::cout.precision(17); 
  std::ifstream fs_output("LesHouches.out.CMSSM.test_2L_RGEs");
  SLHAea::Coll fs_slha(fs_output);

  std::ifstream gb_output("../GAMBIT_unimproved_spectrum.slha2");
  SLHAea::Coll gb_slha(gb_output);

  const double tol = 1.0e-9;
  int num_fails = 0;
  std::string Block_name = "MSOFT";
  for (SLHAea::Block::const_iterator line = fs_slha[Block_name].begin();
       line != fs_slha[Block_name].end(); ++line)
     {
        if (!line->is_data_line()) continue;
        const int index = std::stoi((*line)[0]);
        const double fs_value = std::stod(fs_slha[Block_name][index][1]);
        const double gb_value = std::stod(gb_slha[Block_name][index][1]);
        if (!is_close_rel_tol(fs_value,gb_value,tol)) {
           std::cout << "Test Fail: in Block " << Block_name 
                     << " values for entry" << index
                     << " do not match within relative tolerance"
                     << tol << " as they are "
                     << fs_value << "and"  << gb_value<< std::endl; 
           num_fails++;
        }
        
        std::cout << "difference fs - gb is " << std::stod((*line)[1]) - std::stod(gb_slha["MSOFT"][index][1]) << std::endl;
        
     }
  
  std::cout << "Now do MASS block"  << std::endl;
  
  for (SLHAea::Block::const_iterator line = fs_slha["MASS"].begin();
       line != fs_slha["MASS"].end(); ++line)
     {
        if (!line->is_data_line()) continue;
        int index = std::stoi((*line)[0]);
        std::cout << "difference fs - gb is " << std::stod((*line)[1]) - std::stod(gb_slha["MASS"][index][1]) << std::endl;
        
     }

  std::cout << "Now do DSQMIX block"  << std::endl;
  for (SLHAea::Block::const_iterator line = fs_slha["DSQMIX"].begin();
       line != fs_slha["DSQMIX"].end(); ++line)
     {
        if (!line->is_data_line()) continue;
        const int index1 = std::stoi((*line)[0]);
        const int index2 = std::stoi((*line)[1]);
             
        const double gb_mixing = std::stod(gb_slha.at("DSQMIX").at(index1,index2).at(2));
        const double fs_mixing = std::stod(fs_slha.at("DSQMIX").at(index1,index2).at(2));

        if(index1 == index2){
           std::cout <<    "fs_mixing  = "
                  << fs_mixing << std::endl;
           std::cout << "gb_mixing = "
                     << gb_mixing << std::endl;
           std::cout << "fs_mixing - gb_mixing = "
                     << fs_mixing - gb_mixing << std::endl;
        }
        else {
            std::cout << "abs(fs_mixing) - abs(gb_mixing) = "
                      << std::abs(fs_mixing) - std::abs(gb_mixing) << std::endl;
        }
        
     }
  
  
}
