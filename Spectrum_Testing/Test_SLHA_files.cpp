/*

Testing the fidelity of spectrum generators implemented in gambit compared to standalone.

We compare slha files from the backlend, e.g. FS and gambit

Need to deal with the following:
 i) Should be case insenstive to bloack names
ii) Different ordering of entries in some blocks, e.g. MASS block
iii) sign converntion differences in mixing elements (compare absolute values)
iv) be as easy as possible to redo for other models

*/

#include <fstream>
#include <iostream>
#include <string> 
#include "../contrib/slhaea/include/SLHAea/slhaea.h"

bool is_close_abs_tol(double a, double b, double tol = std::numeric_limits<double>::epsilon()) {
      return std::fabs(a - b) < tol;
}

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

bool test_block_1_index(std::string Block_name, SLHAea::Coll slha_file1, SLHAea::Coll slha_file2, int & num_fails, double tol)
{
   int num_fails_local = 0;
   for (SLHAea::Block::const_iterator line = slha_file1[Block_name].begin();
       line != slha_file1[Block_name].end(); ++line)
      {
         if (!line->is_data_line()) continue;
         const int index = std::stoi((*line)[0]);
         const double fs_value = std::stod(slha_file1[Block_name][index][1]);
         const double gb_value = std::stod(slha_file2[Block_name][index][1]);
         if (!is_close_rel_tol(fs_value,gb_value,tol) && !is_close_rel_tol(fs_value,gb_value,tol)) {
            std::cerr << "Test Fail: in Block " << Block_name 
                      << " values for entry " << index
                      << " do not match within relative and absolute tolerance"
                      << tol << " as they are "
                      << fs_value << " and "  << gb_value<< std::endl; 
            num_fails_local++;
         }
      }
   num_fails += num_fails_local;
   if(num_fails_local > 0) {
      std::cerr << "Total failures in Block " << Block_name
                << " = " <<  num_fails_local
                << std::endl;
      return true;
   }
   else
      return false;
}

/// need a special case for Yukawas due to FS having 3 by 3 matrices and
/// GAMBIT having diagonal Yukawas, more strictly SLHA2
bool test_block_2_indices(std::string Block_name, SLHAea::Coll slha_file1, SLHAea::Coll slha_file2, int & num_fails, double tol, bool diagonal_only=false)
{
   int num_fails_local = 0;
   for (SLHAea::Block::const_iterator line = slha_file1[Block_name].begin();
       line != slha_file1[Block_name].end(); ++line)
      {
         if (!line->is_data_line()) continue;    
         const int index1 = std::stoi((*line)[0]);
         const int index2 = std::stoi((*line)[1]);
         if(diagonal_only && index1!=index2) continue;
         const double fs_value = std::stod(slha_file1.at(Block_name).at(index1,index2).at(2));
         const double gb_value = std::stod(slha_file2.at(Block_name).at(index1,index2).at(2));
         if (!is_close_rel_tol(fs_value,gb_value,tol) && !is_close_abs_tol(fs_value,gb_value,tol) ) {
            std::cerr << "Test Fail: in Block " << Block_name 
                      << " values for entry " << index1 << "  "  << index2
                      << " do not match within relative and absolute tolerance"
                      << tol << " as they are "
                      << fs_value << " and "  << gb_value<< std::endl; 
            num_fails_local++;
         }
      }
   num_fails += num_fails_local;
   if(num_fails_local > 0) {
      std::cerr << "Total failures in Block " << Block_name
                << " = " <<  num_fails_local
                << std::endl;
      return true;
   }
   else
      return false;
}



// for sfermion mixings ignore signs
bool test_block_2_indices_sf_mixing(std::string Block_name, SLHAea::Coll slha_file1, SLHAea::Coll slha_file2, int & num_fails, double tol)
{
   int num_fails_local = 0;
   for (SLHAea::Block::const_iterator line = slha_file1[Block_name].begin();
       line != slha_file1[Block_name].end(); ++line)
      {
         if (!line->is_data_line()) continue;
         const int index1 = std::stoi((*line)[0]);
         const int index2 = std::stoi((*line)[1]);
         
         double fs_value = std::abs(std::stod(slha_file1.at(Block_name).at(index1,index2).at(2)));
         double gb_value = std::abs(std::stod(slha_file2.at(Block_name).at(index1,index2).at(2)));
         if (!is_close_rel_tol(fs_value,gb_value,tol) && !is_close_abs_tol(fs_value,gb_value,tol)) {
            std::cerr << "Test Fail: in Block " << Block_name 
                      << " values for entry " << index1 << "  "  << index2
                      << " do not match within relative and absolute tolerance"
                      << tol << " as they are "
                      << fs_value << " and "  << gb_value<< std::endl; 
            num_fails_local++;
         }
      }
   num_fails += num_fails_local;
   if(num_fails_local > 0) {
      std::cerr << "Total failures in Block " << Block_name
                << " = " <<  num_fails_local
                << std::endl;
      return true;
   }
   else
      return false;
}

int main()
{
  std::cout.precision(17);
  std::cerr.precision(17);
  std::ifstream fs_output("LesHouches.out.CMSSM.test_2L_RGEs");
  if(!fs_output.good()) {
     std::cerr << "FS output SLHA file not found." << std::endl;
     return 1;
  }
  SLHAea::Coll fs_slha(fs_output);

  std::ifstream gb_output("../GAMBIT_unimproved_spectrum.slha2");
  if(!gb_output.good()) {
     std::cerr << "GAMBIT output SLHA file not found." << std::endl;
     return 1;
  }
  SLHAea::Coll gb_slha(gb_output);

  const double tol = 1e-8;
  int num_fails = 0;
  test_block_1_index("gauge", fs_slha, gb_slha, num_fails, tol); // case insensitive?
  test_block_2_indices("Yu", fs_slha, gb_slha, num_fails, tol, true); // case insensitive?
  test_block_2_indices("Yd", fs_slha, gb_slha, num_fails, tol, true); // case insensitive?
  test_block_2_indices("Ye", fs_slha, gb_slha, num_fails, tol, true); // case insensitive?
  test_block_2_indices("Te", fs_slha, gb_slha, num_fails, tol); // case insensitive?
  test_block_2_indices("Td", fs_slha, gb_slha, num_fails, tol); // case insensitive?
  test_block_2_indices("Tu", fs_slha, gb_slha, num_fails, tol); // case insensitive?
  test_block_2_indices("MSQ2", fs_slha, gb_slha, num_fails, tol);
  test_block_2_indices("MSE2", fs_slha, gb_slha, num_fails, tol);
  test_block_2_indices("MSL2", fs_slha, gb_slha, num_fails, tol);
  test_block_2_indices("MSU2", fs_slha, gb_slha, num_fails, tol);
  test_block_2_indices("MSD2", fs_slha, gb_slha, num_fails, tol);
  test_block_1_index("MASS", fs_slha, gb_slha, num_fails, tol);
  test_block_2_indices("UMIX", fs_slha, gb_slha, num_fails, tol);
  test_block_2_indices("VMIX", fs_slha, gb_slha, num_fails, tol);
  test_block_2_indices("PSEUDOSCALARMIX", fs_slha, gb_slha, num_fails, tol);
  test_block_2_indices_sf_mixing("DSQMIX", fs_slha, gb_slha, num_fails, tol);
  test_block_2_indices_sf_mixing("SELMIX", fs_slha, gb_slha, num_fails, tol);
  test_block_2_indices_sf_mixing("USQMIX", fs_slha, gb_slha, num_fails, tol);
  test_block_2_indices_sf_mixing("SNUMIX", fs_slha, gb_slha, num_fails, tol);
  test_block_2_indices("SCALARMIX", fs_slha, gb_slha, num_fails, tol);
  test_block_2_indices("NMIX", fs_slha, gb_slha, num_fails, tol);
  test_block_2_indices("CHARGEMIX", fs_slha, gb_slha, num_fails, tol);
  test_block_1_index("MSOFT", fs_slha, gb_slha, num_fails, tol);

  if(num_fails == 0)
     std::cout << "All tests passing at relative and absolute tolreance " << tol  << std::endl;
  else
     std::cout << "Test fails.  Number of failing tests is "  << num_fails << std::endl;
  
  
}
