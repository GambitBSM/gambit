/////////////////////////////////////////
//                                     //
//  BOSS - Backend-On-a-Stick Script   //
//                                     //
/////////////////////////////////////////

// Test for BOSS
// Main test file

#include "Unspecified.hpp"
#include "Specified.hpp"

#include <iostream>

int main(int argc, char** argv)
{

  Unspecified<int> testU;
  std::cout << testU.myTemplatedVar() << std::endl;
  std::cout << "test" << std::endl;

}
