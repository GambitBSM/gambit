//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Macros for interfacing with backends written
///  in other languages.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2017 Dec
///
///  \author Tomas Gonzalo
///          (t.e.gonzalo@fys.uio.no)
///  \date 2016 Oct
///
///  *********************************************

#ifndef __interoperability_macros_hpp__
#define __interoperability_macros_hpp__

/// If not defined already, define the backend languages
#ifndef UNKNOWN
  #define UNKNOWN 0
#endif
#ifndef CC_LANG
  #define CC_LANG 1
#endif
#ifndef CXX_LANG
  #define CXX_LANG 2
#endif
#ifndef FORTRAN_LANG
  #define FORTRAN_LANG 3
#endif
#ifndef Fortran_LANG
  #define Fortran_LANG 3
#endif
#ifndef MATHEMATICA_LANG
  #define MATHEMATICA_LANG 4
#endif
#ifndef Mathematica_LANG
  #define Mathematica_LANG 4
#endif
#ifndef PYTHON_LANG
  #define PYTHON_LANG 5
#endif
#ifndef Python_LANG
  #define Python_LANG 5
#endif
#ifndef PYTHON2_LANG
  #define PYTHON2_LANG 5
#endif
#ifndef Python2_LANG
  #define Python2_LANG 5
#endif
#ifndef PYTHON3_LANG
  #define PYTHON3_LANG 5
#endif
#ifndef Python3_LANG
  #define Python3_LANG 5
#endif
#ifndef DATA_LANG
  #define DATA_LANG 6
#endif
#ifndef Data_LANG
  #define Data_LANG 6
#endif

/// Macro to help identifying the language of the backend
#ifndef DEFINED_BACKENDLANG
#define DEFINED_BACKENDLANG ()
#endif

/// Macro to choose between mathematica types, python types and normal types
#define MATH_TYPE(TYPE)                                                                         \
        IF_ELSEIF(USING_MATHEMATICA, mathematica_variable<TYPE>,                                \
                  USING_PYTHON, python_variable<TYPE>,                                          \
                  /*USING NONE OF THE ABOVE*/ TYPE)

/// Macro that determines whether the language of the backend is C
#define USING_CC IF_ELSE_TOKEN_DEFINED(BACKENDLANG,                                             \
        BOOST_PP_EQUAL(CAT(BACKENDLANG,_LANG), CC_LANG), 0)

/// Macro that determines whether the language of the backend is C++
#define USING_CXX IF_ELSE_TOKEN_DEFINED(BACKENDLANG,                                            \
        BOOST_PP_EQUAL(CAT(BACKENDLANG,_LANG), CXX_LANG), 0)

/// Macro that determines whether the language of the backend is Fortran
#define USING_FORTRAN IF_ELSE_TOKEN_DEFINED(BACKENDLANG,                                        \
        BOOST_PP_EQUAL(CAT(BACKENDLANG,_LANG), FORTRAN_LANG), 0)

/// Macro that determines whether the language of the backend is Mathematica
#define USING_MATHEMATICA IF_ELSE_TOKEN_DEFINED(BACKENDLANG,                                    \
        BOOST_PP_EQUAL(CAT(BACKENDLANG,_LANG), MATHEMATICA_LANG), 0)

/// Macro that determines whether the language of the backend is Python
#define USING_PYTHON IF_ELSE_TOKEN_DEFINED(BACKENDLANG,                                         \
        BOOST_PP_EQUAL(CAT(BACKENDLANG,_LANG), PYTHON_LANG), 0)

/// Macro that determines whether the the backend is purely data
#define DATA_ONLY IF_ELSE_TOKEN_DEFINED(BACKENDLANG,                                            \
        BOOST_PP_EQUAL(CAT(BACKENDLANG,_LANG), DATA_LANG), 0)

#endif // #defined __interoperability_macros_hpp__
