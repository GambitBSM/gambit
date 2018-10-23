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


#ifndef __NMSSMEFTatQ_hpp__
#define __NMSSMEFTatQ_hpp__

#include "gambit/Models/models/NMSSM66atQ.hpp"

/// 7 parameters plus input scale
#define MODEL NMSSMEFTatQ
#define PARENT NMSSM66atQ
  START_MODEL
  DEFINEPARS(Qin,TanBeta,M1,M2,kappa,lambda,Akappa,vS)
  INTERPRET_AS_PARENT_FUNCTION(NMSSMEFTatQ_to_NMSSM66atQ)
#undef PARENT
#undef MODEL

#endif
