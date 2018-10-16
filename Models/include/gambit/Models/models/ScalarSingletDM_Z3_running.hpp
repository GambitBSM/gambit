//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///
///  Z3 scalar singlet dark matter with running mass
///  and quartic coupling
///
///  *********************************************
///
///  Authors
///  =======
///
///  \author James McKay
///  \date 2015 September
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2018 Sep
///
///  *********************************************

#ifndef __ScalarSingletDM_Z3_running_hpp__
#define __ScalarSingletDM_Z3_running_hpp__

#define MODEL ScalarSingletDM_Z3_running
  START_MODEL
  DEFINEPARS(mS, lambda_hS, lambda_S, mu3)
#undef MODEL

#endif
