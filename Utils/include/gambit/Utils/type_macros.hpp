//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Macros for declaring different types for
///  GAMBIT.  Version to be included in main
///  compilation unit.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2014 Sep
///
///  *********************************************

#ifndef __type_macros_hpp__
#define __type_macros_hpp__

#include "gambit/Utils/util_macros.hpp"

#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/subseq.hpp>
#include <boost/preprocessor/seq/subseq.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>

// If STANDALONE is defined, register that this is the main compilation unit.
#ifdef STANDALONE
  #define __gambit_main_hpp__
#endif

// If this file has been included from the main compilation unit, define TYPEDEFAULT
// and REGISTER_DEFAULT differently from the way they are normally defined.
#ifdef __gambit_main_hpp__

  #include "gambit/Elements/ini_functions.hpp"

  /// Helper macro to register the default version of a classloading backend to use
  #define REGISTER_DEFAULT(BE, VER, DEFAULT)                                          \
  namespace Gambit                                                                    \
  {                                                                                   \
    namespace Backends                                                                \
    {                                                                                 \
      namespace CAT_3(BE,_,VER)                                                       \
      {                                                                               \
        int def = pass_default_to_backendinfo(STRINGIFY(BE),STRINGIFY(DEFAULT));      \
      }                                                                               \
    }                                                                                 \
  }                                                                                   \

  /// Helper macro for setting default backend version for BOSSed types.
  #define TYPEDEFAULT(r,data,elem)                                                    \
    namespace Gambit                                                                  \
    {                                                                                 \
                                                                                      \
      namespace Backends                                                              \
      {                                                                               \
                                                                                      \
        namespace BOOST_PP_SEQ_ELEM(0,data)                                           \
        {                                                                             \
                                                                                      \
          BOOST_PP_SEQ_FOR_EACH_I(START_NAMESPACE, ,                                  \
           BOOST_PP_SEQ_SUBSEQ(elem,0,BOOST_PP_SUB(BOOST_PP_SEQ_SIZE(elem),1)))       \
                                                                                      \
            int CAT(add_equivrelation_,                                               \
             BOOST_PP_SEQ_ELEM(BOOST_PP_SUB(BOOST_PP_SEQ_SIZE(elem),1),elem)) =       \
             add_equivrelation                                                        \
             (                                                                        \
              STRINGIFY(BOOST_PP_SEQ_ELEM(1,data)::                                   \
               BOOST_PP_SEQ_FOR_EACH_I(TRAILING_NSQUALIFIER, ,                        \
               BOOST_PP_SEQ_SUBSEQ(elem,0,BOOST_PP_SUB(BOOST_PP_SEQ_SIZE(elem),1)))   \
               BOOST_PP_SEQ_ELEM(BOOST_PP_SUB(BOOST_PP_SEQ_SIZE(elem),1),elem)),      \
              STRINGIFY(BOOST_PP_SEQ_ELEM(2,data)_default::                           \
               BOOST_PP_SEQ_FOR_EACH_I(TRAILING_NSQUALIFIER, ,                        \
               BOOST_PP_SEQ_SUBSEQ(elem,0,BOOST_PP_SUB(BOOST_PP_SEQ_SIZE(elem),1)))   \
               BOOST_PP_SEQ_ELEM(BOOST_PP_SUB(BOOST_PP_SEQ_SIZE(elem),1),elem))       \
             );                                                                       \
                                                                                      \
          BOOST_PP_REPEAT(BOOST_PP_SUB(BOOST_PP_SEQ_SIZE(elem),1),END_NAMESPACE, )    \
                                                                                      \
        }                                                                             \
                                                                                      \
      }                                                                               \
                                                                                      \
      namespace CAT(BOOST_PP_SEQ_ELEM(2,data),_default)                               \
      {                                                                               \
        BOOST_PP_SEQ_FOR_EACH_I(START_NAMESPACE, ,                                    \
         BOOST_PP_SEQ_SUBSEQ(elem,0,BOOST_PP_SUB(BOOST_PP_SEQ_SIZE(elem),1)))         \
        typedef BOOST_PP_SEQ_ELEM(1,data)::                                           \
         BOOST_PP_SEQ_FOR_EACH_I(TRAILING_NSQUALIFIER, ,                              \
         BOOST_PP_SEQ_SUBSEQ(elem,0,BOOST_PP_SUB(BOOST_PP_SEQ_SIZE(elem),1)))         \
         BOOST_PP_SEQ_ELEM(BOOST_PP_SUB(BOOST_PP_SEQ_SIZE(elem),1),elem)              \
         BOOST_PP_SEQ_ELEM(BOOST_PP_SUB(BOOST_PP_SEQ_SIZE(elem),1),elem);             \
        BOOST_PP_REPEAT(BOOST_PP_SUB(BOOST_PP_SEQ_SIZE(elem),1),END_NAMESPACE, )      \
      }                                                                               \
  }                                                                                   \

#else

  /// Helper macro to register the default version of a classloading backend to use
  #define REGISTER_DEFAULT(BE, VER, DEFAULT)  DUMMYARG(BE, VER, DEFAULT)              \

  /// Helper macro for setting default backend version for BOSSed types.
  #define TYPEDEFAULT(r,data,elem)                                                    \
    namespace Gambit                                                                  \
    {                                                                                 \
      namespace CAT(BOOST_PP_SEQ_ELEM(2,data),_default)                               \
      {                                                                               \
        BOOST_PP_SEQ_FOR_EACH_I(START_NAMESPACE, ,                                    \
         BOOST_PP_SEQ_SUBSEQ(elem,0,BOOST_PP_SUB(BOOST_PP_SEQ_SIZE(elem),1)))         \
        typedef BOOST_PP_SEQ_ELEM(1,data)::                                           \
         BOOST_PP_SEQ_FOR_EACH_I(TRAILING_NSQUALIFIER, ,                              \
         BOOST_PP_SEQ_SUBSEQ(elem,0,BOOST_PP_SUB(BOOST_PP_SEQ_SIZE(elem),1)))         \
         BOOST_PP_SEQ_ELEM(BOOST_PP_SUB(BOOST_PP_SEQ_SIZE(elem),1),elem)              \
         BOOST_PP_SEQ_ELEM(BOOST_PP_SUB(BOOST_PP_SEQ_SIZE(elem),1),elem);             \
        BOOST_PP_REPEAT(BOOST_PP_SUB(BOOST_PP_SEQ_SIZE(elem),1),END_NAMESPACE, )      \
      }                                                                               \
    }

#endif //__gambit_main_hpp__

#ifdef STANDALONE
  #undef __gambit_main_hpp__
#endif

/// Set default backend version for BOSSed types.
#define SET_DEFAULT_VERSION_FOR_LOADING_TYPES(BE, VER, DEFAULT)                       \
REGISTER_DEFAULT(BE, VER, DEFAULT)                                                    \
BOOST_PP_SEQ_FOR_EACH(PRE_TYPEDEFAULT, (CAT_3(BE,_,VER))(CAT_3(BE,_,DEFAULT))(BE),    \
 CAT_5(BE,_,DEFAULT,_,all_data) )

/// Open a namespace
#define START_NAMESPACE(r,data,i,elem) namespace elem {

/// Close a namespace.
#define END_NAMESPACE(z,n,data) }

/// An entry with a trailing namespace qualifier
#define TRAILING_NSQUALIFIER(r,data,i,elem) elem::

// Strip out the actual type info sequence from the all_data entry.
#define PRE_TYPEDEFAULT(r,data,elem) TYPEDEFAULT(r,data,BOOST_PP_TUPLE_ELEM(2,0,elem))

// For testing whether a given backend version's classes have been loaded or not
#define ALREADY_LOADED(BE) CAT_3(__loaded_types_,BE,_hpp__)

#endif //__type_macros_hpp__


