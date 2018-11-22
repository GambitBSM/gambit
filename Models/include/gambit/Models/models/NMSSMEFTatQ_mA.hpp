//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  NMSSMEFTatQ model declaration.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2018 Oct
///
///  *********************************************


#ifndef __NMSSMEFTatQ_mA_hpp__
#define __NMSSMEFTatQ_mA_hpp__

#include "gambit/Models/models/NMSSMEFTatQ.hpp"

/// 8 parameters plus input scale
#define MODEL NMSSMEFTatQ_mA
#define PARENT NMSSMEFTatQ
  START_MODEL
  DEFINEPARS(Qin,TanBeta,M1,M2,kappa,lambda,mA,mu,Akappa)
  INTERPRET_AS_PARENT_FUNCTION(NMSSMEFTatQ_mA_to_NMSSMEFTatQ)
#undef PARENT
#undef MODEL

#endif
