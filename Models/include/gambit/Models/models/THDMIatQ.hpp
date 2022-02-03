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
//
//  James McKay
//    November 2016
//
//  Filip Rajec 
//    filip.rajec@adelaide.edu.au
//    Feb 2019
//
//  *********************************************

#ifndef __THDMIatQ_hpp__
#define __THDMIatQ_hpp__

#define MODEL THDMIatQ
  START_MODEL
  
  DEFINEPARS(lambda_1,lambda_2,lambda_3,lambda_4,lambda_5)
  DEFINEPARS(lambda_6,lambda_7,m12_2)
  DEFINEPARS(tanb)

  DEFINEPARS(Qin,QrunTo)

#undef MODEL

#endif
