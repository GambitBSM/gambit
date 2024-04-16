//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Citation keys for GAMBIT.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Tomas Gonzalo
///          (gonzalo@physik.rwth-aachen.de)
///  \date 2021 Sep
///
///  *********************************************

#ifndef __citation_keys_hpp__
#define __citation_keys_hpp__

#include "gambit/Utils/util_types.hpp"

namespace Gambit
{

  // GAMBIT citation keys
  const std::vector<str> gambit_citation_keys = 
  {
    "GAMBIT:2017yxo", // GAMBIT Core paper
    "Kvellestad:2019vxm", // GAMBIT review
      // GUM additions
    "Bloor:2021gtp", // GUM 1.0 Paper
    "Alloul:2013bka", // FeynRules 2.0 Manual
    "Christensen:2008py", // FeynRules made easy
    "Christensen:2010wz", // FeynRules: Whizard Interface
    "Christensen:2009jx", // FeynRules: CalcHEP, FeynArts, Sherpa interfaces
    "Degrande:2011ua", // Universal FeynRules Output
    "Pukhov:2004ca", // Calchep 2.3
    "Belyaev:2012qa", // Calchep 3.4
    "Belanger:2014vza", // Micromegas 4.1
    "Belanger:2013oya", // Micromegas 3.0
    "Belanger:2010gh", // Micromegas 2.4
    "Belanger:2008sj", // Micromegas 2.2
    "Belanger:2006is", // Micromegas 2.0
    "Belanger:2004yn", // Micromegas 1.3
    "Belanger:2001fz", // Micromegas 1.0
  };
}

#endif // defined __citation_keys_hpp__
