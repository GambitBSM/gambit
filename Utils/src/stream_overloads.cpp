//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Define overloadings of the stream operator for
///  various containers.
///  (Should really be templated eventually)
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (patscott@physics.mcgill.ca)
///  \date 2013 Jan, Dec
///
///  \author Ben Farmer
///          (benjamin.farmer@monash.edu)
///  \date 2013 Jun, 2016, Jan
///
///  *********************************************

#include "gambit/Utils/stream_overloads.hpp"

namespace Gambit
{

  /// Spacing utility for stream overloads
  std::string spacing(int len, int maxlen)
  {
    int offset = 0;
    if (len < maxlen) {offset=maxlen-len;}
    return std::string(offset+5,' ');
  }

}

