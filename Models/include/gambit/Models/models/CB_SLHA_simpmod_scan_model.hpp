//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Dummy model for doing a scan based on replacing
///  entries in a SLHA file
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///   
///  \author Anders Kvellestad
///  \date 2019 Jul
///
///  *********************************************


#ifndef __cb_slha_simpmod_scan_model_hpp__
#define __cb_slha_simpmod_scan_model_hpp__

#define MODEL CB_SLHA_simpmod_scan_model
  START_MODEL
  DEFINEPARS(m1,m2,cross_section_fb,cross_section_uncert_fb,br1,br2)
#undef MODEL

#endif /* defined(__cb_slha_simpmod_scan_model_hpp__) */














