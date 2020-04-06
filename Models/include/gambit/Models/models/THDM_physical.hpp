//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
//
//  Two Higgs Doublet Model (Higgs Basis)
//  *********************************************
//
//  Authors
//  =======
//
//  (add name and date if you modify)
//  Filip Rajec
//  Aug 2016
//
//  Cristian Sierra
//  cristian.sierra@monash.edu
//  Apr 2020
//
//  *********************************************

#ifndef __THDM_physical_hpp__
#define __THDM_physical_hpp__

// Must include models which are targets of translation functions
#include "gambit/Models/models/THDM.hpp"

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

  //INTERPRET_AS_X_FUNCTION(FRIEND, THDM_to_THDMatQ)
  INTERPRET_AS_PARENT_FUNCTION(THDM_physical_to_THDM)
  // Translation functions defined in THDM.cpp
#undef PARENT
#undef MODEL

#endif
