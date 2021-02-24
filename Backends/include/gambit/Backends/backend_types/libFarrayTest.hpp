//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Definitions of container classes
///  for the libFarrayTest backend.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Lars A. Dal
///          (l.a.dal@fys.uio.no)
///  \date 2014 Feb
///
///  *********************************************

#ifndef __libFarrayTest_types_hpp__
#define __libFarrayTest_types_hpp__

#include "gambit/Utils/util_types.hpp"

// Farray syntax:
// Farray<[type], [lower index, dim 1], [upper index, dim 1], [alternating lower/upper indices for subsequent dimensions]>
// Fstring syntax:
// Fstring<[string length]>
// FstringArray syntax:
// FstringArray<[string length], [lower index, dim 1], [upper index, dim 1], [alternating lower/upper indices for subsequent dimensions]>

// See util_types.hpp for the typedefs (such as Finteger) used in the code below
namespace Gambit
{
    struct libFarrayTest_CB_type
    {
        Farray< Fdouble,-2,0> a;
        Farray< Fdouble,1,3>  b;
        Finteger c;
        Farray<Finteger, 1,3, 0,1, -1,0> d;
    };
    struct libFarrayTest_CB2_type
    {
        Fstring<5> chara;
        FstringArray<5, 1,3>  charb;
        FstringArray<6, 1,2, -1,0> charc;
        Finteger e;
    };
    struct libFarrayTest_CB3_type
    {
        Fcomplex cpa;
        Fcomplex16 cpb;
        Finteger f;
    };
}

#endif // defined __libFarrayTest_types_hpp__
