//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
//
//  Test for cross-section scan for DAMA likelihood
//
//  *********************************************
//
//  Authors
//  =======
//
//  (add name and date if you modify)
//
//  Lauren Street
//  2020 May
//
//  *********************************************

#ifndef __DAMA_xsec_hpp__
#define __DAMA_xsec_hpp__

#define MODEL DAMA_xsec
  START_MODEL
  DEFINEPARS(sigmap_SI, sigmap_SD, sigman_SD)

#undef MODEL

#endif
