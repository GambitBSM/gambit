//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Type definition header for module SpecBit.
///
///  Compile-time registration of type definitions
///  required for the rest of the code to
///  communicate with SpecBit.
///
///  Add to this if you want to define a new type
///  for the functions in SpecBit to return, but
///  you don't expect that type to be needed by
///  any other modules.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Tomas Gonzalo
///          (gonzalo@physik.rwth-aachen.de)
///  \date 2021 Mar
///
///  *********************************************

#ifndef __SpecBit_types_hpp__
#define __SpecBit_types_hpp__

namespace Gambit
{

  namespace SpecBit
  {

    enum THDM_TYPE
    {
       TYPE_I = 1,
       TYPE_II,
       TYPE_LS,
       TYPE_flipped,
       TYPE_III
    };

  }
}


#endif
