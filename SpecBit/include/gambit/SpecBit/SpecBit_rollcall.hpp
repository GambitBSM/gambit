//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Rollcall header for module SpecBit
///
///  These functions link ModelParameters to
///  Spectrum objects in various ways.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ben Farmer
///          (benjamin.farmer@fysik.su.se)
///    \date 2014 Sep - Dec, 2015 Jan - Mar
///
///  \author Ankit Beniwal
///          (ankit.beniwal@adelaide.edu.au)
///    \date 2016 Aug
///
///  *********************************************

#ifndef __SpecBit_rollcall_hpp__
#define __SpecBit_rollcall_hpp__

#include "gambit/SpecBit/SpecBit_types.hpp"

#define MODULE SpecBit
#define REFERENCE GAMBITModelsWorkgroup:2017ilg
START_MODULE

  // Capabilities used in more than one of the headers
  // below need to be declared up-front (and then not
  // declared in the header)

  // Generalised Higgs couplings
  #define CAPABILITY Higgs_Couplings
  START_CAPABILITY
  #undef CAPABILITY

  /// Module function declarations for SpecBit_SM.cpp
  #include "gambit/SpecBit/SpecBit_SM_rollcall.hpp"

  /// Module function declarations for SpecBit_MSSM.cpp
  #include "gambit/SpecBit/SpecBit_MSSM_rollcall.hpp"

  #include "gambit/SpecBit/SpecBit_VS_rollcall.hpp"

  /// Module function declarations for SpecBit_ScalarSingletDM.cpp
  #include "gambit/SpecBit/SpecBit_ScalarSingletDM_rollcall.hpp"

  /// Module function declarations for SpecBit_VectorSingletDM_Z2.cpp
  #include "gambit/SpecBit/SpecBit_VectorSingletDM_rollcall.hpp"

  /// Module function declarations for SpecBit_MajoranaSingletDM_Z2.cpp
  #include "gambit/SpecBit/SpecBit_MajoranaSingletDM_rollcall.hpp"

  /// Module function declarations for SpecBit_DiracSingletDM_Z2.cpp
  #include "gambit/SpecBit/SpecBit_DiracSingletDM_rollcall.hpp"

  /// Module function declarations for SpecBit_MDM.cpp
  #include "gambit/SpecBit/SpecBit_MDM_rollcall.hpp"

  /// Module function declarations for SpecBit_tests.cpp (new tests)
  #include "gambit/SpecBit/SpecBit_tests_rollcall.hpp"

  /// Module function declarations for SpecBit_DMsimpVectorMedVectorDM.cpp
  #include "gambit/SpecBit/SpecBit_DMsimpVectorMedVectorDM_rollcall.hpp"

  /// Module function declarations for SpecBit_DMsimpVectorMedScalarDM.cpp
  #include "gambit/SpecBit/SpecBit_DMsimpVectorMedScalarDM_rollcall.hpp"

  /// Module function declarations for SpecBit_DMsimpVectorMedMajoranaDM.cpp
  #include "gambit/SpecBit/SpecBit_DMsimpVectorMedMajoranaDM_rollcall.hpp"

  /// Module function declarations for SpecBit_DMsimpVectorMedDiracDM.cpp
  #include "gambit/SpecBit/SpecBit_DMsimpVectorMedDiracDM_rollcall.hpp"

  /// Module function declarations for SpecBit_DMEFT.cpp
  #include "gambit/SpecBit/SpecBit_DMEFT_rollcall.hpp"

// TODO: Temporarily disabled until project is ready
/*
  /// Module function declarations for SpecBit_SuperRenormHP.cpp
  #include "gambit/SpecBit/SpecBit_SuperRenormHP_rollcall.hpp"
*/
  /// For SpecBit testing only
  //#include "gambit/SpecBit/SpecBit_sandbox_rollcall.hpp"

  /// Functions to change the capability associated with a Spectrum object to "SM_spectrum"
  /// @{
  QUICK_FUNCTION(MODULE, SM_spectrum, OLD_CAPABILITY, convert_MSSM_to_SM,  Spectrum, (MSSM63atQ, MSSM63atMGUT), (MSSM_spectrum, Spectrum))
  QUICK_FUNCTION(MODULE, SM_spectrum, OLD_CAPABILITY, convert_NMSSM_to_SM,  Spectrum, (NMSSM_does_not_exist_yet), (NMSSM_spectrum, Spectrum))
  QUICK_FUNCTION(MODULE, SM_spectrum, OLD_CAPABILITY, convert_E6MSSM_to_SM, Spectrum, (E6MSSM_does_not_exist_yet), (E6MSSM_spectrum, Spectrum))
  /// @}

  // 'Convenience' functions to retrieve certain particle properities in a simple format

  // #define CAPABILITY LSP_mass   // Supplies the mass of the lightest supersymmetric particle
  // START_CAPABILITY

  //   #define FUNCTION get_LSP_mass                      // Retrieves the LSP mass from a Spectrum object
  //   START_FUNCTION(double)
  //   DEPENDENCY(particle_spectrum, SpectrumPtr)            // Takes a Spectrum object and returns an SLHAstruct
  //   ALLOW_MODELS(MSSM24, CMSSM)
  //   #undef FUNCTION

  // #undef CAPABILITY

#undef REFERENCE
#undef MODULE

#endif /* defined(__SpecBit_rollcall_hpp__) */



