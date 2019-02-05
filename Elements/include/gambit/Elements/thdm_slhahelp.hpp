//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Routines to help translate between SLHA2 sfermions
///  and SLHA1 (or similar) sfermions.
///
///  Note that when family mixing occurs, there is no clear
///  definition of ~t_1, ~t_2, etc, as these are neither
///  gauge eigenstates nor mass eigenstates.  Extensive
///  matrix manipulations would be required in order to
///  define the family states as the results of diagonalising
///  a 2x2 submatrix of the full 6x6 mass matrix.  Here
///  we instead define the family states to be the two mass
///  eigenstates with the largest contributions from gauge
///  eigenstates of the appropriate family.  For example,
///  this means that ~t_1 is the lightest of the two mass
///  eigenstates that have the largest combined contribution
///  from the gauge eigenstates ~t_L and ~t_R.
///
///  *********************************************
///
///  Authors:
///
///    Filip Rajec 
///      filip.rajec@adelaide.edu.au
// /   Feb 2019
///
///  *********************************************


#ifndef __THDM_slhahelp_hpp__
#define __THDM_slhahelp_hpp__

#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <set>

#include "gambit/Elements/subspectrum.hpp"
#include "gambit/Elements/spectrum.hpp"
#include "gambit/Utils/util_types.hpp"

namespace Gambit
{

   namespace slhahelp
   {

      /// Add an entire THDM spectrum to an SLHAea object
      void add_THDM_spectrum_to_SLHAea(const SubSpectrum& mssmspec, SLHAstruct& slha, int slha_version);

   }  // namespace slhahelp

} // namespace gambit

#endif
