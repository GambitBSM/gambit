//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Register the definitions of SubSpectrum
///  contents here.
///
///  *********************************************
///
///  Authors:
///  <!-- add name and date if you modify -->
///
///  \author Ben Farmer
///          (benjamin.farmer@fysik.su.se)
///  \date 2016 Feb
///
///  \author Ankit Beniwal
///          (ankit.beniwal@adelaide.edu.au)
///  \date 2016 Aug
///
///  *********************************************

#ifndef __registeredspectra_hpp__
#define __registeredspectra_hpp__

#include "gambit/Models/SpectrumContents/subspectrum_contents.hpp"

/// Just declare the classes here; should be defined in source files

namespace Gambit
{
  namespace SpectrumContents
  {

    struct SM              : SubSpectrumContents { SM(); };
    struct SM_slha         : SubSpectrumContents { SM_slha(); }; // Missing some running masses that aren't part of SMINPUTS in slha
    struct SMHiggs         : SubSpectrumContents { SMHiggs(); };
    struct MSSM            : SubSpectrumContents { MSSM(); };
    struct SingletDM       : SubSpectrumContents { SingletDM(); };    
    struct SingletDMZ3     : SubSpectrumContents { SingletDMZ3(); };
    struct VectorDM        : SubSpectrumContents { VectorDM(); };
    struct MajoranaDM      : SubSpectrumContents { MajoranaDM(); }; 
    struct DiracDM         : SubSpectrumContents { DiracDM(); };
  } 
}
#endif
