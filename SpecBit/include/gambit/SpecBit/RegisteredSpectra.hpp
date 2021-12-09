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
///          (benjamin.farmer@imperial.ac.uk)
///  \date 2016 Feb, 2019 June
///
///  \author Ankit Beniwal
///          (ankit.beniwal@adelaide.edu.au)
///  \date 2016 Aug
///
///  *********************************************

#ifndef __registeredspectra_hpp__
#define __registeredspectra_hpp__

#include "gambit/Elements/spectrum_contents.hpp"

/// Just declare the Contents derived classes here; should be defined in source files

namespace Gambit
{
  namespace SpectrumContents
  {

    struct SM                   : Contents { SM(); };
    struct SM_slha              : Contents 
    {  // SLHA version doesn't have running masses that aren't part of SMINPUTS in slha 
        SM_slha();
        static SLHAstruct generateOutputSLHAea(const Spectrum&, const int version);
    };
    struct MSSM                 : Contents 
    { 
        MSSM();
        static SLHAstruct transformInputSLHAea(const SLHAstruct& input);
        static SLHAstruct generateOutputSLHAea(const Spectrum&, const int version);
    };
    struct MDM                  : Contents { MDM(); };
    struct ScalarSingletDM_Z2   : Contents { ScalarSingletDM_Z2(); };
    struct ScalarSingletDM_Z3   : Contents { ScalarSingletDM_Z3(); };
    struct VectorSingletDM_Z2   : Contents { VectorSingletDM_Z2(); };
    struct MajoranaSingletDM_Z2 : Contents { MajoranaSingletDM_Z2(); };
    struct DiracSingletDM_Z2    : Contents { DiracSingletDM_Z2(); };
    struct DMEFT                : SubSpectrumContents { DMEFT(); };

  }
}
#endif
