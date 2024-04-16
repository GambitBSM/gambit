//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Dummy model for doing a ColliderBit-only 
///  scan based on replacing SLHA file entries
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Anders Kvellestad
///          (anders.kvellestad@fys.uio.no)
///  \date 2019 Jul
///  \date 2020 Dec
///
///  *********************************************


#ifndef __colliderbit_slha_scan_model_hpp__
#define __colliderbit_slha_scan_model_hpp__

#define MODEL ColliderBit_SLHA_scan_model
  START_MODEL
  DEFINEPARS(m1,m2,cross_section_fb,cross_section_uncert_fb,br1,br2)
#undef MODEL

#endif /* defined(__colliderbit_slha_scan_model_hpp__) */
