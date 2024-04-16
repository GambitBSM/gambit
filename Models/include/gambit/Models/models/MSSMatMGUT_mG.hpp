//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///
///  MSSM models with boundary conditions at MGUT scale
///  with a light gravitino
///
///  Models included:
///    MSSM63atMGUT_mG
///    MSSM30atMGUT_mG
///    MSSM25atMGUT_mG
///    MSSM20atMGUT_mG
///
///  Translation functions defined in MSSMatMGUT_mG.cpp
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
///  \date 2018 Sep
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@kit.edu)
///  \date 2022 Sept
///
///  *********************************************

#ifndef __MSSMatMGUT_mG_hpp__
#define __MSSMatMGUT_mG_hpp__

#include "gambit/Models/models/MSSMatQ_mG.hpp" // Must include models which are targets of translation functions

// Forward declaration of needed types
namespace Gambit
{
   class Spectrum;
}

// General GUT boundary condition parameterisation of the MSSM
// There are several of these, compatible with different spectrum generators
// To use a constrained GUT model like the CMSSM, there needs to be an
// "interpret_as_X" function which translates the CMSSM parameters into
// the appropriate general GUT parameterisation for the spectrum generator
// being used.

#define MODEL  MSSM63atMGUT_mG
#define PARENT MSSM63atQ_mG
  START_MODEL

  /// Can translate this model into MSSM63atQ_mG (where Q will then be set to MGUT)
  INTERPRET_AS_PARENT_FUNCTION(MSSM63atMGUT_mG_to_MSSM63atQ_mG)
  /// Depends on an MSSM spectrum, since RGEs must run in order to determine MGUT
  INTERPRET_AS_PARENT_DEPENDENCY(unimproved_MSSM_spectrum, Spectrum)

  DEFINEPARS(TanBeta,SignMu,mHu2,mHd2,M1,M2,M3,mG)

  /// Mass matrices are symmetric (Hermitian, and we are restricted to real entries at the moment)
  /// so only one 'triangle' needed.
  DEFINEPARS(mq2_11, mq2_12, mq2_13,
                     mq2_22, mq2_23,
                             mq2_33)

  DEFINEPARS(ml2_11, ml2_12, ml2_13,
                     ml2_22, ml2_23,
                             ml2_33)

  DEFINEPARS(md2_11, md2_12, md2_13,
                     md2_22, md2_23,
                             md2_33)

  DEFINEPARS(mu2_11, mu2_12, mu2_13,
                     mu2_22, mu2_23,
                             mu2_33)

  DEFINEPARS(me2_11, me2_12, me2_13,
                     me2_22, me2_23,
                             me2_33)

  DEFINEPARS(Ae_11, Ae_12, Ae_13,
             Ae_21, Ae_22, Ae_23,
             Ae_31, Ae_32, Ae_33)

  DEFINEPARS(Ad_11, Ad_12, Ad_13,
             Ad_21, Ad_22, Ad_23,
             Ad_31, Ad_32, Ad_33)

  DEFINEPARS(Au_11, Au_12, Au_13,
             Au_21, Au_22, Au_23,
             Au_31, Au_32, Au_33)
#undef PARENT
#undef MODEL

///  Specialisation of MSSM63atQ_mG with all off-diagonal m and A terms set to zero.
#define MODEL MSSM30atMGUT_mG
#define PARENT MSSM63atMGUT_mG
  START_MODEL

  DEFINEPARS(TanBeta,SignMu,mHu2,mHd2,M1,M2,M3,mG)

  DEFINEPARS(mq2_1, mq2_2, mq2_3)

  DEFINEPARS(ml2_1, ml2_2, ml2_3)

  DEFINEPARS(md2_1, md2_2, md2_3)

  DEFINEPARS(mu2_1, mu2_2, mu2_3)

  DEFINEPARS(me2_1, me2_2, me2_3)

  DEFINEPARS(Ae_1, Ae_2, Ae_3)

  DEFINEPARS(Ad_1, Ad_2, Ad_3)

  DEFINEPARS(Au_1, Au_2, Au_3)

  INTERPRET_AS_PARENT_FUNCTION(MSSM30atMGUT_mG_to_MSSM63atMGUT_mG)
  INTERPRET_AS_X_FUNCTION(MSSM30atQ_mG, MSSM30atMGUT_mG_to_MSSM30atQ_mG)
  INTERPRET_AS_X_DEPENDENCY(MSSM30atQ_mG, unimproved_MSSM_spectrum, Spectrum)
#undef PARENT
#undef MODEL

#define MODEL MSSM25atMGUT_mG
#define PARENT MSSM30atMGUT_mG
  START_MODEL

  DEFINEPARS(TanBeta,SignMu,mHu2,mHd2,M1,M2,M3,mG)

  DEFINEPARS(mq2_1, mq2_2, mq2_3)

  DEFINEPARS(ml2_1, ml2_2, ml2_3)

  DEFINEPARS(md2_1, md2_2, md2_3)

  DEFINEPARS(mu2_1, mu2_2, mu2_3)

  DEFINEPARS(me2_1, me2_2, me2_3)

  DEFINEPARS(Ae_12, Ae_3)

  DEFINEPARS(Ad_3)

  DEFINEPARS(Au_3)

  INTERPRET_AS_PARENT_FUNCTION(MSSM25atMGUT_mG_to_MSSM30atMGUT_mG)
#undef PARENT
#undef MODEL

#define MODEL MSSM20atMGUT_mG
#define PARENT MSSM25atMGUT_mG
  START_MODEL

  DEFINEPARS(TanBeta,SignMu,mHu2,mHd2,M1,M2,M3,mG)

  DEFINEPARS(mq2_12, mq2_3)

  DEFINEPARS(ml2_12, ml2_3)

  DEFINEPARS(md2_12, md2_3)

  DEFINEPARS(mu2_12, mu2_3)

  DEFINEPARS(me2_12, me2_3)

  DEFINEPARS(Ae_12, Ae_3)

  DEFINEPARS(Ad_3)

  DEFINEPARS(Au_3)

  INTERPRET_AS_PARENT_FUNCTION(MSSM20atMGUT_mG_to_MSSM25atMGUT_mG)
  INTERPRET_AS_X_FUNCTION(MSSM20atQ_mG, MSSM20atMGUT_mG_to_MSSM20atQ_mG)
  INTERPRET_AS_X_DEPENDENCY(MSSM20atQ_mG, unimproved_MSSM_spectrum, Spectrum)
#undef PARENT
#undef MODEL

#endif
