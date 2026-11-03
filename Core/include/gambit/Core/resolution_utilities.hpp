//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Utilities useful during dependency resolution.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///  \author Pat Scott
///          (patrickcolinscott@gmail.com)
///  \date 2022 Nov
///
///  *********************************************

#pragma once

#include "gambit/Utils/util_types.hpp"
#include "gambit/Elements/type_equivalency.hpp"

namespace Gambit
{

  namespace DRes
  {

    /// Check whether s1 (wildcard + regex allowed) matches s2
    bool stringComp(const str & s1, const str & s2);

    /// Check whether type 1 (wildcard + regex allowed) matches type 2, taking into account equivalence classes.
    bool typeComp(str s1, str s2, const Utils::type_equivalency & eq);

  }

}
