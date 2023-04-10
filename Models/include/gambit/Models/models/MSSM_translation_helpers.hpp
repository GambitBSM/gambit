//
///  GAMBIT: Global and Modular BSM Inference Tool
///  *********************************************
///
///  Declare a helper function for translating 'mA'
///  MSSM parameterisations into the primary
///  parameterisations, and another for translating
///  from scales MGUT and MSUSY to arbitrary scale Q.
///
///  *********************************************
///
///  Authors
///  =======
///
///  (add name and date if you modify)
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2017 Aug
///
///  *********************************************

#ifndef __MSSM_translation_helpers_hpp__
#define __MSSM_translation_helpers_hpp__

#include "gambit/Utils/model_parameters.hpp"

namespace Gambit
{
   class SubSpectrum;

   /// Translation function for mA,mu parameterisation to mHu2,mHd2 parameterisation
   void MSSM_mA_to_MSSM_mhud(const ModelParameters &myP, ModelParameters &targetP, const SubSpectrum& HE);

   /// Translation function for MSSM defined at RGE-determined scale (e.g. GUT, SUSY) to arbitrary scale Q
   void MSSMatX_to_MSSMatQ(const ModelParameters &myP, ModelParameters &targetP, const SubSpectrum& HE);

   /// Translation functions for 20-parameter models to 25-parameter
   void MSSM20atX_to_MSSM25atX(const ModelParameters &myP, ModelParameters &targetP);

   /// Translation functions for 25-parameter models to 30-parameter
   void MSSM25atX_to_MSSM30atX(const ModelParameters &myP, ModelParameters &targetP);

   /// Translation functions for 30-parameter models to 63-parameter
   void MSSM30atX_to_MSSM63atX(const ModelParameters &myP, ModelParameters &targetP);

}

#endif