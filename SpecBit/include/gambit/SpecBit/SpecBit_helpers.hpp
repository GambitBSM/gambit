//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Declarations of convenience (i.e. non-Gambit)
///  functions used by more than one SpecBit 
///  source file.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ben Farmer
///          (benjamin.farmer@fysik.su.se)
///    \date 2014 Sep - Dec, 2015 Jan - May
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date Jul 2020
///  
///  *********************************************

#ifndef __SpecBit_helpers_hpp__
#define __SpecBit_helpers_hpp__

#include "gambit/Elements/sminputs.hpp"

// Flexible SUSY stuff (should not be needed by the rest of gambit)
//#include "flexiblesusy/src/ew_input.hpp"
#include "flexiblesusy/src/lowe.h" // From softsusy; used by flexiblesusy
//#include "flexiblesusy/src/numerics.hpp"

namespace Gambit
{

  namespace SpecBit
  {

    /// @{

    /// Non-Gambit helper functions
    //  =======================================================================
    //  These are not known to Gambit, but perform helper tasks used by the
    //  Gambit module functions.

    /// Initialise QedQcd object from SMInputs data
    void setup_QedQcd(softsusy::QedQcd& oneset /*output*/, const SMInputs& sminputs /*input*/);

    /// Check that the spectrum has a neutralino LSP.
    bool has_neutralino_LSP(const Spectrum& result);

    /// Helper to work with pointer
    bool has_neutralino_LSP(const Spectrum* result);

    /// @}

  }
}
 
#endif
