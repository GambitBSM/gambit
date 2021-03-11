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
/// \author Tomas Gonzalo
/// \date 2016 Apr
///
///  *********************************************

#include "gambit/Utils/util_types.hpp"

#ifndef __SPHENO_types_hpp__
#define __SPHENO_types_hpp__

namespace Gambit
{
    // Typedef for function pointer to a void() function 
    typedef void (*type_fptr_SPhenoErrorHandler)();
    
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
    typedef Farray<Freal8,1,2,1,3> Farray_Freal8_1_2_1_3;
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
    typedef Farray<Freal8,1,43> Farray_Freal8_1_43;
    typedef Farray<Freal8,1,46> Farray_Freal8_1_46;
    typedef Farray<Freal8,1,6,1,993> Farray_Freal8_1_6_1_993;
    typedef Farray<Freal8,1,6,1,1092> Farray_Freal8_1_6_1_1092;
    typedef Farray<Freal8,1,6,1,1245> Farray_Freal8_1_6_1_1245;
    typedef Farray<Freal8,1,6,1,1128> Farray_Freal8_1_6_1_1128;
    typedef Farray<Freal8,1,3,1,894> Farray_Freal8_1_3_1_894;
    typedef Farray<Freal8,1,3,1,1002> Farray_Freal8_1_3_1_1002;
    typedef Farray<Freal8,1,2,1,191> Farray_Freal8_1_2_1_191;
    typedef Farray<Freal8,1,3,1,209> Farray_Freal8_1_3_1_209;
    typedef Farray<Freal8,1,3,1,207> Farray_Freal8_1_3_1_207;
    typedef Farray<Freal8,1,2,1,90> Farray_Freal8_1_2_1_90;
    typedef Farray<Freal8,1,2,1,96> Farray_Freal8_1_2_1_96;
    typedef Farray<Freal8,1,1,1,136> Farray_Freal8_1_1_1_136;
    typedef Farray<Freal8,1,1,1,157> Farray_Freal8_1_1_1_157;
    typedef Farray<Freal8,1,4,1,366> Farray_Freal8_1_4_1_366;
    typedef Farray<Freal8,1,5,1,482> Farray_Freal8_1_5_1_482;
    typedef Farray<Freal8,1,2,1,316> Farray_Freal8_1_2_1_316;
    typedef Farray<Freal8,1,2,1,274> Farray_Freal8_1_2_1_274;
    typedef Farray<Freal8,1,2,1,189> Farray_Freal8_1_2_1_189;
    typedef Farray<Freal8,1,3,1,66> Farray_Freal8_1_3_1_66;
    typedef Farray<Freal8,1,3,1,78> Farray_Freal8_1_3_1_78;
    typedef Farray<Fstring<60>,1,31> Farray_Fstring60_1_31;
    typedef Farray<Fstring<60>,1,10> Farray_Fstring60_1_10;
    typedef Farray<Fstring<60>,1,2> Farray_Fstring60_1_2;
    typedef Farray<Fstring<60>,1,33> Farray_Fstring60_1_33;
    typedef Farray<Fstring<60>,1,15> Farray_Fstring60_1_15;
    typedef Farray<Fstring<60>,1,22> Farray_Fstring60_1_22;
    typedef Farray<Fstring<60>,1,25> Farray_Fstring60_1_25;
    typedef Farray<Fstring<60>,1,9> Farray_Fstring60_1_9;
   
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
	Farray<Freal8,1,200,1,2> id2;
	Farray<Freal8,1,600,1,3> id3;
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
