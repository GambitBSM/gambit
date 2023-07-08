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
///  \author Inigo Saez Casares
///          (inigo.saez_casares@ens-paris-saclay.fr))
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

    struct SM                       : SubSpectrumContents { SM(); };
    struct SM_slha                  : SubSpectrumContents { SM_slha(); }; // Missing some running masses that aren't part of SMINPUTS in slha
    struct SMHiggs                  : SubSpectrumContents { SMHiggs(); };
    struct MSSM                     : SubSpectrumContents { MSSM(); };
    struct MDM                      : SubSpectrumContents { MDM(); };
    struct ScalarSingletDM_Z2       : SubSpectrumContents { ScalarSingletDM_Z2(); };
    struct ScalarSingletDM_Z3       : SubSpectrumContents { ScalarSingletDM_Z3(); };
    struct VectorSingletDM_Z2       : SubSpectrumContents { VectorSingletDM_Z2(); };
    struct MajoranaSingletDM_Z2     : SubSpectrumContents { MajoranaSingletDM_Z2(); };
    struct DiracSingletDM_Z2        : SubSpectrumContents { DiracSingletDM_Z2(); };
    struct DMEFT                    : SubSpectrumContents { DMEFT(); };
    struct DMsimpVectorMedDiracDM   : SubSpectrumContents { DMsimpVectorMedDiracDM(); };
    struct DMsimpVectorMedMajoranaDM: SubSpectrumContents { DMsimpVectorMedMajoranaDM(); };
    struct DMsimpVectorMedScalarDM  : SubSpectrumContents { DMsimpVectorMedScalarDM(); };
    struct DMsimpVectorMedVectorDM: SubSpectrumContents { DMsimpVectorMedVectorDM(); };

    // TODO: Temporarily disabled until project is ready
    // struct SuperRenormHP        : SubSpectrumContents { SuperRenormHP(); };

  }
}
#endif
