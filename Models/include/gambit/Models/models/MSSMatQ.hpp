//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///
///  MSSM models with boundary conditions at generic scale Q
///
///  Models included:
///    MSSM63atQ
///    MSSM30atQ
///    MSSM25atQ
///    MSSM24atQ
///    MSSM20atQ
///    MSSM19atQ
///    MSSM16atQ
///    MSSM15atQ
///    MSSM11atQ
///    MSSM10atQ
///    MSSM10batQ
///    MSSM10catQ
///    MSSM9atQ
///    MSSM9batQ
///    MSSM7atQ
///
///  Translation functions defined in MSSMatQ.cpp
///
///  *********************************************
///
///  Authors
///  =======
///
///  (add name and date if you modify)
///
///  \author Ben Farmer
///          (ben.farmer@gmail.com)
///  \date 2015 Jan
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2015 Sep
///
///  \author Peter Athron
///          (peter.athron@coepp.org.au)
///  \date 2015 Sep
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@kit.edu)
///  \date 2022 Sept
///
///  *********************************************

#ifndef __MSSMatQ_hpp__
#define __MSSMatQ_hpp__

/// FlexibleSUSY compatible general (63 parameters plus sign, plus input scale) MSSM parameterisation
#define MODEL MSSM63atQ
  START_MODEL
  DEFINEPARS(Qin,TanBeta,SignMu,mHu2,mHd2,M1,M2,M3)

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
#undef MODEL


///  Specialisation of MSSM63atQ with all off-diagonal m and A terms set to zero.
#define MODEL MSSM30atQ
#define PARENT MSSM63atQ
  START_MODEL

  DEFINEPARS(Qin,TanBeta,SignMu,mHu2,mHd2,M1,M2,M3)

  DEFINEPARS(mq2_1, mq2_2, mq2_3)

  DEFINEPARS(ml2_1, ml2_2, ml2_3)

  DEFINEPARS(md2_1, md2_2, md2_3)

  DEFINEPARS(mu2_1, mu2_2, mu2_3)

  DEFINEPARS(me2_1, me2_2, me2_3)

  DEFINEPARS(Ae_1, Ae_2, Ae_3)

  DEFINEPARS(Ad_1, Ad_2, Ad_3)

  DEFINEPARS(Au_1, Au_2, Au_3)

  INTERPRET_AS_PARENT_FUNCTION(MSSM30atQ_to_MSSM63atQ)
#undef PARENT
#undef MODEL

#define MODEL MSSM25atQ
#define PARENT MSSM30atQ
  START_MODEL

  DEFINEPARS(Qin,TanBeta,SignMu,mHu2,mHd2,M1,M2,M3)

  DEFINEPARS(mq2_1, mq2_2, mq2_3)

  DEFINEPARS(ml2_1, ml2_2, ml2_3)

  DEFINEPARS(md2_1, md2_2, md2_3)

  DEFINEPARS(mu2_1, mu2_2, mu2_3)

  DEFINEPARS(me2_1, me2_2, me2_3)

  DEFINEPARS(Ae_12, Ae_3)

  DEFINEPARS(Ad_3)

  DEFINEPARS(Au_3)

  INTERPRET_AS_PARENT_FUNCTION(MSSM25atQ_to_MSSM30atQ)
#undef PARENT
#undef MODEL

#define MODEL MSSM24atQ
#define PARENT MSSM25atQ
  START_MODEL

  DEFINEPARS(Qin,TanBeta,SignMu,mHu2,mHd2,M1,M2,M3)

  DEFINEPARS(mq2_1, mq2_2, mq2_3)

  DEFINEPARS(ml2_1, ml2_2, ml2_3)

  DEFINEPARS(md2_1, md2_2, md2_3)

  DEFINEPARS(mu2_1, mu2_2, mu2_3)

  DEFINEPARS(me2_1, me2_2, me2_3)

  DEFINEPARS(Ae_3)

  DEFINEPARS(Ad_3)

  DEFINEPARS(Au_3)

  INTERPRET_AS_PARENT_FUNCTION(MSSM24atQ_to_MSSM25atQ)
#undef PARENT
#undef MODEL

#define MODEL MSSM20atQ
#define PARENT MSSM25atQ
  START_MODEL

  DEFINEPARS(Qin,TanBeta,SignMu,mHu2,mHd2,M1,M2,M3)

  DEFINEPARS(mq2_12, mq2_3)

  DEFINEPARS(ml2_12, ml2_3)

  DEFINEPARS(md2_12, md2_3)

  DEFINEPARS(mu2_12, mu2_3)

  DEFINEPARS(me2_12, me2_3)

  DEFINEPARS(Ae_12, Ae_3)

  DEFINEPARS(Ad_3)

  DEFINEPARS(Au_3)

  INTERPRET_AS_PARENT_FUNCTION(MSSM20atQ_to_MSSM25atQ)
#undef PARENT
#undef MODEL

// pMSSM
#define MODEL MSSM19atQ
#define PARENT MSSM24atQ
  START_MODEL

  DEFINEPARS(Qin,TanBeta,SignMu,mHu2,mHd2,M1,M2,M3)

  DEFINEPARS(mq2_12, mq2_3)

  DEFINEPARS(ml2_12, ml2_3)

  DEFINEPARS(md2_12, md2_3)

  DEFINEPARS(mu2_12, mu2_3)

  DEFINEPARS(me2_12, me2_3)

  DEFINEPARS(Ae_3)

  DEFINEPARS(Ad_3)

  DEFINEPARS(Au_3)

  INTERPRET_AS_PARENT_FUNCTION(MSSM19atQ_to_MSSM24atQ)
  INTERPRET_AS_X_FUNCTION(MSSM20atQ, MSSM19atQ_to_MSSM20atQ)
#undef PARENT
#undef MODEL

#define MODEL MSSM16atQ
#define PARENT MSSM19atQ
  START_MODEL

  DEFINEPARS(Qin,TanBeta,SignMu,mHu2,mHd2,M1,M2,M3)

  DEFINEPARS(mq2_12, mq2_3, mu2_3, md2_3)

  DEFINEPARS(ml2_12, ml2_3, me2_3)

  DEFINEPARS(Ae_3)

  DEFINEPARS(Ad_3)

  DEFINEPARS(Au_3)

  INTERPRET_AS_PARENT_FUNCTION(MSSM16atQ_to_MSSM19atQ)
#undef PARENT
#undef MODEL

// This model matches the one explored in arXiv:1405.0622.
#define MODEL MSSM15atQ
#define PARENT MSSM16atQ
  START_MODEL

  DEFINEPARS(Qin,TanBeta,SignMu,mHu2,mHd2,M1,M2,M3)

  DEFINEPARS(mq2_12, mq2_3, mu2_3, md2_3)

  DEFINEPARS(ml2_12, ml2_3, me2_3)

  DEFINEPARS(A0, Au_3)

  INTERPRET_AS_PARENT_FUNCTION(MSSM15atQ_to_MSSM16atQ)
#undef PARENT
#undef MODEL

#define MODEL MSSM11atQ
#define PARENT MSSM16atQ
  START_MODEL

  DEFINEPARS(Qin,TanBeta,SignMu,mHu2,mHd2,M1,M2,M3)

  DEFINEPARS(mq2)

  DEFINEPARS(ml2)

  DEFINEPARS(Ae_3)

  DEFINEPARS(Ad_3)

  DEFINEPARS(Au_3)

  INTERPRET_AS_PARENT_FUNCTION(MSSM11atQ_to_MSSM16atQ)
#undef PARENT
#undef MODEL


#define MODEL MSSM10atQ
#define PARENT MSSM11atQ
  START_MODEL

  DEFINEPARS(Qin,TanBeta,SignMu,mHu2,mHd2,M1,M2,M3)

  DEFINEPARS(mq2)

  DEFINEPARS(ml2)

  DEFINEPARS(Ad_3)

  DEFINEPARS(Au_3)

  INTERPRET_AS_PARENT_FUNCTION(MSSM10atQ_to_MSSM11atQ)
#undef PARENT
#undef MODEL

#define MODEL MSSM10batQ
#define PARENT MSSM11atQ
  START_MODEL

  DEFINEPARS(Qin,TanBeta,SignMu,mHu2,mHd2,M1,M2,M3)

  DEFINEPARS(mf2)

  DEFINEPARS(Ae_3)

  DEFINEPARS(Ad_3)

  DEFINEPARS(Au_3)

  INTERPRET_AS_PARENT_FUNCTION(MSSM10batQ_to_MSSM11atQ)
#undef PARENT
#undef MODEL

// This model matches the one explored in arXiv:1504.03260 and referred to as 'pMSSM10'
#define MODEL MSSM10catQ
#define PARENT MSSM15atQ
  START_MODEL

  DEFINEPARS(Qin,TanBeta,SignMu,mHu2,mHd2,M1,M2,M3)

  DEFINEPARS(mq2_12, mq2_3)

  DEFINEPARS(ml2)

  DEFINEPARS(A0)

  INTERPRET_AS_PARENT_FUNCTION(MSSM10catQ_to_MSSM15atQ)
#undef PARENT
#undef MODEL

#define MODEL MSSM9atQ
#define PARENT MSSM10atQ
  START_MODEL

  DEFINEPARS(Qin,TanBeta,SignMu,mHu2,mHd2,M1,M2,M3)

  DEFINEPARS(mf2)

  DEFINEPARS(Ad_3)

  DEFINEPARS(Au_3)

  INTERPRET_AS_PARENT_FUNCTION(MSSM9atQ_to_MSSM10atQ)
  INTERPRET_AS_X_FUNCTION(MSSM10batQ, MSSM9atQ_to_MSSM10batQ)
#undef PARENT
#undef MODEL

#define MODEL MSSM9batQ
#define PARENT MSSM15atQ
  START_MODEL

  DEFINEPARS(Qin,TanBeta,SignMu,mHu2,mHd2,M1,M2,M3)

  DEFINEPARS(mq2_3)

  DEFINEPARS(msf2)

  DEFINEPARS(Au_3)

  INTERPRET_AS_PARENT_FUNCTION(MSSM9batQ_to_MSSM15atQ)
#undef PARENT
#undef MODEL

// Forward declaration of needed types
namespace Gambit
{
  struct SMInputs;
}

#define MODEL MSSM7atQ
#define PARENT MSSM9atQ
  START_MODEL

  DEFINEPARS(Qin,TanBeta,SignMu,mHu2,mHd2,M2)

  DEFINEPARS(mf2)

  DEFINEPARS(Ad_3)

  DEFINEPARS(Au_3)

  INTERPRET_AS_PARENT_FUNCTION(MSSM7atQ_to_MSSM9atQ)
  INTERPRET_AS_PARENT_DEPENDENCY(SMINPUTS, SMInputs)
#undef PARENT
#undef MODEL

#endif
