//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Concatenation macros
///
///  *********************************************
///
///  Authors: 
///   
///  \author Pat Scott  
///          (patscott@physics.mcgill.ca)
///  \date 2014 Oct
///
///  *********************************************

#ifndef __cats_hpp__
#define __cats_hpp__

/// Concatenate macro arguments for 2-7 arguments.
/// @{
#define CAT(X,Y) CAT2(X,Y)
#define CAT2(X,Y) X##Y
#define CAT_2 CAT
#define CAT_3(X,Y,Z) CAT(X,CAT(Y,Z))
#define CAT_4(A,X,Y,Z) CAT(A,CAT_3(X,Y,Z))
#define CAT_5(A,B,X,Y,Z) CAT(A,CAT_4(B,X,Y,Z))
#define CAT_6(A,B,C,X,Y,Z) CAT(A,CAT_5(B,C,X,Y,Z))
#define CAT_7(A,B,C,D,X,Y,Z) CAT(A,CAT_6(B,C,D,X,Y,Z))
/// @}

#endif // __cats_hpp__
