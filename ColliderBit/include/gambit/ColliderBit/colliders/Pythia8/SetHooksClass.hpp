//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  The SetHooks.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Chris Chang
///  \date Sep 2020
///
///  *********************************************

#pragma once

#include <ostream>
#include <stdexcept>
#include "gambit/Elements/shared_types.hpp"
#include "gambit/ColliderBit/colliders/BaseCollider.hpp"
#include "SLHAea/slhaea.h"


namespace Gambit
{

  namespace ColliderBit
  {

    /// A templated class specific for the UserHooks.
    template <typename PythiaT, typename EventT>
    class SetHooks
    {

      public:
        //Constructor and Destructor
        SetHooks() {}
        ~SetHooks() {}

        //Function to set the UserHook.
        bool SetupHook(PythiaT*)
        {
          return false;
        }
    };


  }
}
