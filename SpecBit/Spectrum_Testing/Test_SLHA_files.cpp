/*

Testing the fidelity of spectrum generators implemented in gambit compared to standalone.

We compare slha files from the backlend, e.g. FS and gambit

Need to deal with the following:
 i) Should be case insenstive to bloack names
ii) Different ordering of entries in some blocks, e.g. MASS block
iii) sign converntion differences in mixing elements (compare absolute values)
iv) be as easy as possible to redo for other models

*/

#include "Test_SLHA_files.hpp"


bool test_MSSM_spectrum(SLHAea::Coll fs_slha, SLHAea::Coll gb_slha, std::string MSSM_variant, int & num_fails, double tol) {
  /// Tests that blocks match, failure indicated by boolean 1 return or non-zero num_fails.
  /// Not using boolean output in this way  
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

  if(num_fails == 0) {
     std::cout << "All " << MSSM_variant  << " tests passing at relative and absolute tolreance " << tol  << std::endl;
     return 0;
  }
  else {
     std::cout << MSSM_variant << " test fails!  Number of failing tests is "  << num_fails << std::endl;
     return 1;
  }
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
  const SLHAea::Coll fs_slha(fs_output);

  std::ifstream gb_output("../../GAMBIT_unimproved_spectrum.slha2");
  if(!gb_output.good()) {
     std::cerr << "GAMBIT output SLHA file not found." << std::endl;
     return 1;
  }
  const SLHAea::Coll gb_slha(gb_output);

  const double tol = 1e-8;
  int num_fails = 0;
  
  test_MSSM_spectrum(fs_slha, gb_slha, "CMSSM", num_fails, tol);
  
  if(num_fails == 0)
     std::cout << "All tests passing at relative and absolute tolreance " << tol  << std::endl;
  else
     std::cout << "Test fails!  Number of failing tests is "  << num_fails << std::endl;
  
  
}
