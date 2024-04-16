//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///
///  Dirac fermion singlet DM
///
///  *********************************************
///
///  Authors
///  =======
///
///  (add name and date if you modify)
///
///  \author Ankit Beniwal
///  \date 2016 August, 2017 June
///
///  \author Sebastian Wild
///  \date 2018 January
///
///  \author Sanjay Bloor
///  \date 2018 August
///        2020 May
///
///  *********************************************

#ifndef __DiracSingletDM_Z2_hpp__
#define __DiracSingletDM_Z2_hpp__

#define MODEL DiracSingletDM_Z2
  START_MODEL
  DEFINEPARS(mF, lF, xi)
#undef MODEL

#define MODEL DiracSingletDM_Z2_sps
#define PARENT DiracSingletDM_Z2
  START_MODEL
  DEFINEPARS(mF, lF_s, lF_ps)
  INTERPRET_AS_PARENT_FUNCTION(DiracSingletDM_Z2_sps_to_DiracSingletDM_Z2)
#undef PARENT
#undef MODEL

#endif
