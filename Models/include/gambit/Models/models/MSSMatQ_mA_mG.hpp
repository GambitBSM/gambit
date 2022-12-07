//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///
///  MSSM models with boundary conditions at generic scale Q
///  with A pole mass and mu as explicit input parameters
///  instead of mHu2 and mHd2 and with a light gravitino.
///
///  Models included:
///    MSSM63atQ_mA_mG
///    MSSM30atQ_mA_mG
///    MSSM24atQ_mA_mG
///    MSSM25atQ_mA_mG
///    MSSM20atQ_mA_mG
///    MSSM19atQ_mA_mG
///    MSSM16atQ_mA_mG
///    MSSM15atQ_mA_mG
///    MSSM11atQ_mA_mG
///    MSSM10atQ_mA_mG
///    MSSM10batQ_mA_mG
///    MSSM10catQ_mA_mG
///    MSSM9atQ_mA_mG
///    MSSM9batQ_mA_mG
///    MSSM7atQ_mA_mG
///
///  Translation functions defined in MSSMatQ_mA_mG.cpp
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
///  \date 2018 Sept
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@kit.edu)
///  \date 2022 Sept
///
///  *********************************************

#ifndef __MSSMatQ_mA_mG_hpp__
#define __MSSMatQ_mA_mG_hpp__

#include "gambit/Models/models/MSSMatQ_mG.hpp" // Must include models which are targets of translation functions

// Forward declaration of needed types
// Also declare a helper function for translating 'mA' MSSM parameterisations into the primary parameterisations,
// and another for translating from scales MGUT and MSUSY to arbitrary scale Q
// (function definition in MSSM63atX_mA_mG.cpp and MSSM63atX.cpp respectively)

namespace Gambit
{
   class Spectrum;
   class SubSpectrum;

   // Translation function for mA,mu parameterisation to mHu2,mHd2 parameterisation
   void MSSM_mA_mG_to_MSSM_mhud(const ModelParameters &myP, ModelParameters &targetP, const SubSpectrum& HE);

   // Translation function for MSSM defined at RGE-determined scale (e.g. GUT, SUSY) to arbitrary scale Q
   void MSSMatX_to_MSSMatQ(const ModelParameters &myP, ModelParameters &targetP, const SubSpectrum& HE);
}

#define MODEL MSSM63atQ_mA_mG
#define PARENT MSSM63atQ_mG
  START_MODEL

  /// Can translate this model into MSSM63atQ_mG
  INTERPRET_AS_PARENT_FUNCTION(MSSM63atQ_mA_mG_to_MSSM63atQ_mG)
  /// Depends on an MSSM spectrum, since RGEs must run in order to determine MGUT
  INTERPRET_AS_PARENT_DEPENDENCY(unimproved_MSSM_spectrum, Spectrum)

  DEFINEPARS(Qin,TanBeta,mA,mu,M1,M2,M3,mG)

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

// Specialisation of MSSM63atQ_mA_mG with all off-diagonal m and A terms set to zero.
#define MODEL MSSM30atQ_mA_mG
#define PARENT MSSM63atQ_mA_mG
  START_MODEL

  DEFINEPARS(Qin,TanBeta,mA,mu,M1,M2,M3,mG)

  DEFINEPARS(mq2_1, mq2_2, mq2_3)

  DEFINEPARS(ml2_1, ml2_2, ml2_3)

  DEFINEPARS(md2_1, md2_2, md2_3)

  DEFINEPARS(mu2_1, mu2_2, mu2_3)

  DEFINEPARS(me2_1, me2_2, me2_3)

  DEFINEPARS(Ae_1, Ae_2, Ae_3)

  DEFINEPARS(Ad_1, Ad_2, Ad_3)

  DEFINEPARS(Au_1, Au_2, Au_3)

  INTERPRET_AS_PARENT_FUNCTION(MSSM30atQ_mA_mG_to_MSSM63atQ_mA_mG)
  INTERPRET_AS_X_FUNCTION(MSSM30atQ_mG, MSSM30atQ_mA_mG_to_MSSM30atQ_mG)
  INTERPRET_AS_X_DEPENDENCY(MSSM30atQ_mG, unimproved_MSSM_spectrum, Spectrum)
#undef PARENT
#undef MODEL

#define MODEL MSSM25atQ_mA_mG
#define PARENT MSSM30atQ_mA_mG
  START_MODEL

  DEFINEPARS(Qin,TanBeta,mA,mu,M1,M2,M3,mG)

  DEFINEPARS(mq2_1, mq2_2, mq2_3)

  DEFINEPARS(ml2_1, ml2_2, ml2_3)

  DEFINEPARS(md2_1, md2_2, md2_3)

  DEFINEPARS(mu2_1, mu2_2, mu2_3)

  DEFINEPARS(me2_1, me2_2, me2_3)

  DEFINEPARS(Ae_12, Ae_3)

  DEFINEPARS(Ad_3)

  DEFINEPARS(Au_3)

  INTERPRET_AS_PARENT_FUNCTION(MSSM25atQ_mA_mG_to_MSSM30atQ_mA_mG)
#undef PARENT
#undef MODEL

#define MODEL MSSM24atQ_mA_mG
#define PARENT MSSM25atQ_mA_mG
  START_MODEL

  DEFINEPARS(Qin,TanBeta,mA,mu,M1,M2,M3,mG)

  DEFINEPARS(mq2_1, mq2_2, mq2_3)

  DEFINEPARS(ml2_1, ml2_2, ml2_3)

  DEFINEPARS(md2_1, md2_2, md2_3)

  DEFINEPARS(mu2_1, mu2_2, mu2_3)

  DEFINEPARS(me2_1, me2_2, me2_3)

  DEFINEPARS(Ae_3)

  DEFINEPARS(Ad_3)

  DEFINEPARS(Au_3)

  INTERPRET_AS_PARENT_FUNCTION(MSSM24atQ_mA_mG_to_MSSM25atQ_mA_mG)
#undef PARENT
#undef MODEL

#define MODEL MSSM20atQ_mA_mG
#define PARENT MSSM25atQ_mA_mG
  START_MODEL

  DEFINEPARS(Qin,TanBeta,mA,mu,M1,M2,M3,mG)

  DEFINEPARS(mq2_12, mq2_3)

  DEFINEPARS(ml2_12, ml2_3)

  DEFINEPARS(md2_12, md2_3)

  DEFINEPARS(mu2_12, mu2_3)

  DEFINEPARS(me2_12, me2_3)

  DEFINEPARS(Ae_12, Ae_3)

  DEFINEPARS(Ad_3)

  DEFINEPARS(Au_3)

  INTERPRET_AS_PARENT_FUNCTION(MSSM20atQ_mA_mG_to_MSSM25atQ_mA_mG)
  INTERPRET_AS_X_FUNCTION(MSSM20atQ_mG, MSSM20atQ_mA_mG_to_MSSM20atQ_mG)
  INTERPRET_AS_X_DEPENDENCY(MSSM20atQ_mG, unimproved_MSSM_spectrum, Spectrum)
#undef PARENT
#undef MODEL

/// pMSSM
#define MODEL MSSM19atQ_mA_mG
#define PARENT MSSM24atQ_mA_mG
  START_MODEL

  DEFINEPARS(Qin,TanBeta,mA,mu,M1,M2,M3,mG)

  DEFINEPARS(mq2_12, mq2_3)

  DEFINEPARS(ml2_12, ml2_3)

  DEFINEPARS(md2_12, md2_3)

  DEFINEPARS(mu2_12, mu2_3)

  DEFINEPARS(me2_12, me2_3)

  DEFINEPARS(Ae_3)

  DEFINEPARS(Ad_3)

  DEFINEPARS(Au_3)

  INTERPRET_AS_PARENT_FUNCTION(MSSM19atQ_mA_mG_to_MSSM24atQ_mA_mG)
  INTERPRET_AS_X_FUNCTION(MSSM20atQ_mA_mG, MSSM19atQ_mA_mG_to_MSSM20atQ_mA_mG)
#undef PARENT
#undef MODEL

#define MODEL MSSM16atQ_mA_mG
#define PARENT MSSM19atQ_mA_mG
  START_MODEL

  DEFINEPARS(Qin,TanBeta,mA,mu,M1,M2,M3,mG)

  DEFINEPARS(mq2_12, mq2_3, mu2_3, md2_3)

  DEFINEPARS(ml2_12, ml2_3, me2_3)

  DEFINEPARS(Ae_3)

  DEFINEPARS(Ad_3)

  DEFINEPARS(Au_3)

  INTERPRET_AS_PARENT_FUNCTION(MSSM16atQ_mA_mG_to_MSSM19atQ_mA_mG)

#undef PARENT
#undef MODEL

// This model matches the one explored in arXiv:1405.0622.
#define MODEL MSSM15atQ_mA_mG
#define PARENT MSSM16atQ_mA_mG
  START_MODEL

  DEFINEPARS(Qin,TanBeta,mA,mu,M1,M2,M3,mG)

  DEFINEPARS(mq2_12, mq2_3, mu2_3, md2_3)

  DEFINEPARS(ml2_12, ml2_3, me2_3)

  DEFINEPARS(A0, Au_3)

  INTERPRET_AS_PARENT_FUNCTION(MSSM15atQ_mA_mG_to_MSSM16atQ_mA_mG)
#undef PARENT
#undef MODEL

#define MODEL MSSM11atQ_mA_mG
#define PARENT MSSM16atQ_mA_mG
  START_MODEL

  DEFINEPARS(Qin,TanBeta,mA,mu,M1,M2,M3,mG)

  DEFINEPARS(mq2)

  DEFINEPARS(ml2)

  DEFINEPARS(Ae_3)

  DEFINEPARS(Ad_3)

  DEFINEPARS(Au_3)

  INTERPRET_AS_PARENT_FUNCTION(MSSM11atQ_mA_mG_to_MSSM16atQ_mA_mG)
#undef PARENT
#undef MODEL

#define MODEL MSSM10atQ_mA_mG
#define PARENT MSSM11atQ_mA_mG
  START_MODEL

  DEFINEPARS(Qin,TanBeta,mA,mu,M1,M2,M3,mG)

  DEFINEPARS(mq2)

  DEFINEPARS(ml2)

  DEFINEPARS(Ad_3)

  DEFINEPARS(Au_3)

  INTERPRET_AS_PARENT_FUNCTION(MSSM10atQ_mA_mG_to_MSSM11atQ_mA_mG)
#undef PARENT
#undef MODEL

#define MODEL MSSM10batQ_mA_mG
#define PARENT MSSM11atQ_mA_mG
  START_MODEL

  DEFINEPARS(Qin,TanBeta,mA,mu,M1,M2,M3,mG)

  DEFINEPARS(mf2)

  DEFINEPARS(Ae_3)

  DEFINEPARS(Ad_3)

  DEFINEPARS(Au_3)

  INTERPRET_AS_PARENT_FUNCTION(MSSM10batQ_mA_mG_to_MSSM11atQ_mA_mG)
#undef PARENT
#undef MODEL

///  This model matches the one explored in arXiv:1504.03260 and referred to as 'pMSSM10'.
#define MODEL MSSM10catQ_mA_mG
#define PARENT MSSM15atQ_mA_mG
  START_MODEL

  DEFINEPARS(Qin,TanBeta,mA,mu,M1,M2,M3,mG)

  DEFINEPARS(mq2_12, mq2_3)

  DEFINEPARS(ml2)

  DEFINEPARS(A0)

  INTERPRET_AS_PARENT_FUNCTION(MSSM10catQ_mA_mG_to_MSSM15atQ_mA_mG)
#undef PARENT
#undef MODEL

#define MODEL MSSM9atQ_mA_mG
#define PARENT MSSM10atQ_mA_mG
  START_MODEL

  DEFINEPARS(Qin,TanBeta,mA,mu,M1,M2,M3,mG)

  DEFINEPARS(mf2)

  DEFINEPARS(Ad_3)

  DEFINEPARS(Au_3)

  INTERPRET_AS_PARENT_FUNCTION(MSSM9atQ_mA_mG_to_MSSM10atQ_mA_mG)
  INTERPRET_AS_X_FUNCTION(MSSM10batQ_mA_mG, MSSM9atQ_mA_mG_to_MSSM10batQ_mA_mG)
#undef PARENT
#undef MODEL

#define MODEL MSSM9batQ_mA_mG
#define PARENT MSSM15atQ_mA_mG
  START_MODEL

  DEFINEPARS(Qin,TanBeta,mA,mu,M1,M2,M3,mG)

  DEFINEPARS(mq2_3)

  DEFINEPARS(msf2)

  DEFINEPARS(Au_3)

  INTERPRET_AS_PARENT_FUNCTION(MSSM9batQ_mA_mG_to_MSSM15atQ_mA_mG)
#undef PARENT
#undef MODEL

// Forward declaration of needed types
namespace Gambit
{
  struct SMInputs;
}

#define MODEL MSSM7atQ_mA_mG
#define PARENT MSSM9atQ_mA_mG
  START_MODEL

  DEFINEPARS(Qin,TanBeta,mA,mu,M2,mG)

  DEFINEPARS(mf2)

  DEFINEPARS(Ad_3)

  DEFINEPARS(Au_3)

  INTERPRET_AS_PARENT_FUNCTION(MSSM7atQ_mA_mG_to_MSSM9atQ_mA_mG)
  INTERPRET_AS_PARENT_DEPENDENCY(SMINPUTS, SMInputs)
#undef PARENT
#undef MODEL

#endif
