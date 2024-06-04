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


    /// In the case that the VLQ model is being run.
    template <>
    class SetHooks<Pythia_VLQ_default::Pythia8::Pythia,Pythia_VLQ_default::Pythia8::Event>
    {
      public:
        Pythia_VLQ_8_212::Pythia8::UserHooks* matching;
        Pythia_VLQ_8_212::Pythia8::CombineMatchingInput combined;

        //Constructor and Destructor
        SetHooks() { }
        ~SetHooks() { }

        //Function to set the UserHook
        bool SetupHook(Pythia_VLQ_default::Pythia8::Pythia* Py8Collider)
        {
          matching = combined.getHook(*Py8Collider);
          Py8Collider->setUserHooksPtr(matching);
          return true;
        }
    };

  }
}
