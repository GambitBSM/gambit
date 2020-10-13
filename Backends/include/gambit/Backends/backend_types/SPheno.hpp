//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Definitions of container classes
///  for the SPheno 3.3.8 backend.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2016 Apr
///  \date 2020 Apr
///
///  \author Pat Scott
///          (pat.scott@uq.edu.au)
///  \date 2020 May
///
///  *********************************************

#include "gambit/Utils/util_types.hpp"

#ifndef __SPHENO_types_hpp__
#define __SPHENO_types_hpp__

namespace Gambit
{
    typedef Farray<Finteger,1,3> Farray_Finteger_1_3;
    typedef Farray<Freal8,1,2> Farray_Freal8_1_2;
    typedef Farray<Freal8,1,3> Farray_Freal8_1_3;
    typedef Farray<Freal8,1,4> Farray_Freal8_1_4;
    typedef Farray<Freal8,1,5> Farray_Freal8_1_5;
    typedef Farray<Freal8,1,6> Farray_Freal8_1_6;
    typedef Farray<Freal8,1,2,1,2> Farray_Freal8_1_2_1_2;
    typedef Farray<Freal8,1,3,1,3> Farray_Freal8_1_3_1_3;
    typedef Farray<Freal8,1,4,1,4> Farray_Freal8_1_4_1_4;
    typedef Farray<Freal8,1,6,1,6> Farray_Freal8_1_6_1_6;
    typedef Farray<Fcomplex16,1,2> Farray_Fcomplex16_1_2;
    typedef Farray<Fcomplex16,1,3> Farray_Fcomplex16_1_3;
    typedef Farray<Fcomplex16,1,2,1,2> Farray_Fcomplex16_1_2_1_2;
    typedef Farray<Fcomplex16,1,3,1,3> Farray_Fcomplex16_1_3_1_3;
    typedef Farray<Fcomplex16,1,4,1,4> Farray_Fcomplex16_1_4_1_4;
    typedef Farray<Fcomplex16,1,5,1,5> Farray_Fcomplex16_1_5_1_5;
    typedef Farray<Fcomplex16,1,6,1,6> Farray_Fcomplex16_1_6_1_6;
    typedef Farray<Flogical,1,100> Farray_Flogical_1_100;
    typedef Farray<Freal8,1,100> Farray_Freal8_1_100;
    typedef Farray<Freal8,1,100,1,2> Farray_Freal8_1_100_1_2;
    typedef Farray<Freal8,1,100,1,5> Farray_Freal8_1_100_1_5;
    typedef Farray<Freal8,1,100,1,2,1,2> Farray_Freal8_1_100_1_2_1_2;
    typedef Farray<Freal8,1,100,1,3,1,3> Farray_Freal8_1_100_1_3_1_3;
    typedef Farray<Freal8,1,100,1,4,1,4> Farray_Freal8_1_100_1_4_1_4;
    typedef Farray<Freal8,1,100,1,5,1,4> Farray_Freal8_1_100_1_5_1_4;
    typedef Farray<Freal8,1,100,1,5,1,5> Farray_Freal8_1_100_1_5_1_5;
    typedef Farray<Freal8,1,100,1,6,1,6> Farray_Freal8_1_100_1_6_1_6;
    typedef Farray<Freal8,1,100,1,7,1,7> Farray_Freal8_1_100_1_7_1_7;
    typedef Farray<Fstring<60>,1,31> Farray_Fstring60_1_31;
    typedef Farray<Fstring<60>,1,10> Farray_Fstring60_1_10;
    typedef Farray<Fstring<60>,1,2> Farray_Fstring60_1_2;
    typedef Farray<Fstring<60>,1,33> Farray_Fstring60_1_33;
    typedef Farray<Fstring<60>,1,15> Farray_Fstring60_1_15;
    typedef Farray<Fstring<60>,1,22> Farray_Fstring60_1_22;
    typedef Farray<Fstring<60>,1,25> Farray_Fstring60_1_25;
    typedef Farray<Fstring<60>,1,9> Farray_Fstring60_1_9;
    typedef Fstring<20> Fstring20;

    struct particle2
    {
      Freal8 m;
      Freal8 m2;
      Freal8 g;
      Finteger id;
      Farray<Finteger,1,200,1,2> id2;
      Farray<Freal8,1,200> gi2;
      Farray<Freal8,1,200> bi2;
    };

    typedef Farray<particle2,1,2> Farray_particle2_1_2;
    typedef Farray<particle2,1,6> Farray_particle2_1_6;

    struct particle23
    {
      Freal8 m;
      Freal8 m2;
      Freal8 g;
      Finteger id;
      Farray<Finteger,1,200,1,2> id2;
      Farray<Finteger,1,600,1,3> id3;
      Farray<Freal8,1,200> gi2;
      Farray<Freal8,1,600> gi3;
      Farray<Freal8,1,200> bi2;
      Farray<Freal8,1,600> bi3;
    };

    typedef Farray<particle23,1,2> Farray_particle23_1_2;
    typedef Farray<particle23,1,3> Farray_particle23_1_3;
    typedef Farray<particle23,1,4> Farray_particle23_1_4;
    typedef Farray<particle23,1,6> Farray_particle23_1_6;

    struct Finputs
    {
      SMInputs sminputs;
      std::map<str, safe_ptr<const double> > param;
      safe_ptr<Options> options;
    };
}

#endif // defined __SPHENO_types_hpp__
