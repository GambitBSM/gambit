//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
//
//  Two Higgs Doublet Model
//  *********************************************
//
//  Authors
//  =======
//
//  (add name and date if you modify)
//  James McKay
//  November 2016
//
//  (add name and date if you modify)
//  Filip Rajec
//  June 2016
//
//  *********************************************

#ifndef __THDMflippedatQ_hpp__
#define __THDMflippedatQ_hpp__

#define MODEL THDMflippedatQ
  START_MODEL
  
  DEFINEPARS(lambda_1,lambda_2,lambda_3,lambda_4,lambda_5)
  DEFINEPARS(lambda_6,lambda_7,m12_2)
  DEFINEPARS(tanb)

  DEFINEPARS(Qin,QrunTo)

#undef MODEL

#endif