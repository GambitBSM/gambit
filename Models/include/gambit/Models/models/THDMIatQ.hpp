//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///
///  Two Higgs Doublet Model
///  (Type I, Generic Basis, at scale Q)
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
///  \date 2019 Feb
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2020 Apr
///
///  *********************************************

#ifndef __THDMIatQ_hpp__
#define __THDMIatQ_hpp__

// Must include models which are targets of translation functions
#include "gambit/Models/models/THDMatQ.hpp"

#define MODEL THDMIatQ
#define PARENT THDMatQ

  START_MODEL
  
  DEFINEPARS(lambda1,lambda2,lambda3,lambda4,lambda5,lambda6,lambda7)
  DEFINEPARS(m12_2)
  DEFINEPARS(tanb)

  DEFINEPARS(Qin,QrunTo)

  // Translation functions defined in THDMI.cpp
  INTERPRET_AS_PARENT_FUNCTION(THDMIatQ_to_THDMatQ)
#undef PARENT
#undef MODEL

#endif
