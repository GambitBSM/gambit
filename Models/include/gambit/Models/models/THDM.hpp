//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///
///  Two Higgs Doublet Model
///  (Type III)
///
///  Models included:
///    THDMatQ
///    THDM
///    THDM_higgs
///    THDM_physical
///
///  Translation functions defined in THDM.cpp
///
///  *********************************************
///
///  Authors
///  =======
///
///  (add name and date if you modify)
///
///  \author James McKay
///          (j.mckay14@imperial.ac.uk)
///  \date 2016 November
///
///  \author Filip Rajec
///          (filip.rajec@adelaide.edu.au)
///  \date 2016 Aug
///
///  \author Cristian Sierra
///          (cristian.sierra@monash.edu)
///  \date 2020 Mar
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2020 Apr
///  \date 2021 Mar
///  
///  *********************************************

#ifndef __THDM_hpp__
#define __THDM_hpp__

#include "gambit/Elements/sminputs.hpp"

// Forward declaration of needed types
namespace Gambit
{
  class SMInputs;
}

#define MODEL THDMatQ
  START_MODEL

  DEFINEPARS(lambda1,lambda2,lambda3,lambda4,lambda5,lambda6,lambda7)
  DEFINEPARS(m12_2)
  DEFINEPARS(tanb)

  DEFINEPARS(yu2_re_11, yu2_im_11, yu2_re_12, yu2_im_12, yu2_re_13, yu2_im_13,
             yu2_re_21, yu2_im_21, yu2_re_22, yu2_im_22, yu2_re_23, yu2_im_23,
             yu2_re_31, yu2_im_31, yu2_re_32, yu2_im_32, yu2_re_33, yu2_im_33)

  DEFINEPARS(yd2_re_11, yd2_im_11, yd2_re_12, yd2_im_12, yd2_re_13, yd2_im_13,
             yd2_re_21, yd2_im_21, yd2_re_22, yd2_im_22, yd2_re_23, yd2_im_23,
             yd2_re_31, yd2_im_31, yd2_re_32, yd2_im_32, yd2_re_33, yd2_im_33)

  DEFINEPARS(yl2_re_11, yl2_im_11, yl2_re_12, yl2_im_12, yl2_re_13, yl2_im_13,
             yl2_re_21, yl2_im_21, yl2_re_22, yl2_im_22, yl2_re_23, yl2_im_23,
             yl2_re_31, yl2_im_31, yl2_re_32, yl2_im_32, yl2_re_33, yl2_im_33)

  DEFINEPARS(Qin)

#undef MODEL

#define MODEL THDM
#define PARENT THDMatQ

  START_MODEL

  DEFINEPARS(lambda1,lambda2,lambda3,lambda4,lambda5,lambda6,lambda7)
  DEFINEPARS(m12_2)
  DEFINEPARS(tanb)
  
  DEFINEPARS(yu2_re_11, yu2_im_11, yu2_re_12, yu2_im_12, yu2_re_13, yu2_im_13,
             yu2_re_21, yu2_im_21, yu2_re_22, yu2_im_22, yu2_re_23, yu2_im_23,
             yu2_re_31, yu2_im_31, yu2_re_32, yu2_im_32, yu2_re_33, yu2_im_33)

  DEFINEPARS(yd2_re_11, yd2_im_11, yd2_re_12, yd2_im_12, yd2_re_13, yd2_im_13,
             yd2_re_21, yd2_im_21, yd2_re_22, yd2_im_22, yd2_re_23, yd2_im_23,
             yd2_re_31, yd2_im_31, yd2_re_32, yd2_im_32, yd2_re_33, yd2_im_33)

  DEFINEPARS(yl2_re_11, yl2_im_11, yl2_re_12, yl2_im_12, yl2_re_13, yl2_im_13,
             yl2_re_21, yl2_im_21, yl2_re_22, yl2_im_22, yl2_re_23, yl2_im_23,
             yl2_re_31, yl2_im_31, yl2_re_32, yl2_im_32, yl2_re_33, yl2_im_33)

  // Translation functions defined in THDM.cpp
  INTERPRET_AS_PARENT_FUNCTION(THDM_to_THDMatQ)
  INTERPRET_AS_PARENT_DEPENDENCY(SMINPUTS, SMInputs)
#undef PARENT
#undef MODEL

#define MODEL THDM_higgs
#define PARENT THDM
  START_MODEL

  DEFINEPARS(Lambda1,Lambda2,Lambda3,Lambda4,Lambda5,Lambda7)
  DEFINEPARS(M22_2)
  DEFINEPARS(alpha,tanb)

  DEFINEPARS(yu2_re_11, yu2_im_11, yu2_re_12, yu2_im_12, yu2_re_13, yu2_im_13,
             yu2_re_21, yu2_im_21, yu2_re_22, yu2_im_22, yu2_re_23, yu2_im_23,
             yu2_re_31, yu2_im_31, yu2_re_32, yu2_im_32, yu2_re_33, yu2_im_33)

  DEFINEPARS(yd2_re_11, yd2_im_11, yd2_re_12, yd2_im_12, yd2_re_13, yd2_im_13,
             yd2_re_21, yd2_im_21, yd2_re_22, yd2_im_22, yd2_re_23, yd2_im_23,
             yd2_re_31, yd2_im_31, yd2_re_32, yd2_im_32, yd2_re_33, yd2_im_33)

  DEFINEPARS(yl2_re_11, yl2_im_11, yl2_re_12, yl2_im_12, yl2_re_13, yl2_im_13,
             yl2_re_21, yl2_im_21, yl2_re_22, yl2_im_22, yl2_re_23, yl2_im_23,
             yl2_re_31, yl2_im_31, yl2_re_32, yl2_im_32, yl2_re_33, yl2_im_33)

  // Translation functions defined in THDM.cpp
  INTERPRET_AS_PARENT_FUNCTION(THDM_higgs_to_THDM)
  INTERPRET_AS_PARENT_DEPENDENCY(SMINPUTS, SMInputs)
#undef PARENT
#undef MODEL

#define MODEL THDM_physical
#define PARENT THDM
  START_MODEL

  DEFINEPARS(mh2,mH2,mA2,mC2)
  DEFINEPARS(lambda6,lambda7,m12_2)
  DEFINEPARS(sba,tanb)

  DEFINEPARS(yu2_re_11, yu2_im_11, yu2_re_12, yu2_im_12, yu2_re_13, yu2_im_13,
             yu2_re_21, yu2_im_21, yu2_re_22, yu2_im_22, yu2_re_23, yu2_im_23,
             yu2_re_31, yu2_im_31, yu2_re_32, yu2_im_32, yu2_re_33, yu2_im_33)

  DEFINEPARS(yd2_re_11, yd2_im_11, yd2_re_12, yd2_im_12, yd2_re_13, yd2_im_13,
             yd2_re_21, yd2_im_21, yd2_re_22, yd2_im_22, yd2_re_23, yd2_im_23,
             yd2_re_31, yd2_im_31, yd2_re_32, yd2_im_32, yd2_re_33, yd2_im_33)

  DEFINEPARS(yl2_re_11, yl2_im_11, yl2_re_12, yl2_im_12, yl2_re_13, yl2_im_13,
             yl2_re_21, yl2_im_21, yl2_re_22, yl2_im_22, yl2_re_23, yl2_im_23,
             yl2_re_31, yl2_im_31, yl2_re_32, yl2_im_32, yl2_re_33, yl2_im_33)

  // Translation functions defined in THDM.cpp
  INTERPRET_AS_PARENT_FUNCTION(THDM_physical_to_THDM)
  INTERPRET_AS_PARENT_DEPENDENCY(SMINPUTS, SMInputs)
#undef PARENT
#undef MODEL

#endif
