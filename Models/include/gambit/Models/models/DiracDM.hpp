//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
//
//  Dirac DM
//
//  *********************************************
//
//  Authors
//  =======
//
//  (add name and date if you modify)
//
//  Ankit Beniwal
//  2016 August, 2017 June
//
//  Sebastian Wild
//  2018 January
//
//  Sanjay Bloor
//  2018 August
//
//  *********************************************

#ifndef __DiracDM_hpp__
#define __DiracDM_hpp__

#define MODEL DiracDM
  START_MODEL
  DEFINEPARS(mF, lF, xi)
#undef MODEL

#define MODEL DiracDM_sps
#define PARENT DiracDM
  START_MODEL
  DEFINEPARS(mF, lF_s, lF_ps)
  INTERPRET_AS_PARENT_FUNCTION(DiracDM_sps_to_DiracDM)
#undef PARENT
#undef MODEL

#endif
