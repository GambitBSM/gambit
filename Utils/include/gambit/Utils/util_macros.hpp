//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  General small utility macros.
///
///  *********************************************
///
///  Authors:
///  <!-- add name and date if you modify -->
///
///  \author Pat Scott
///          (patscott@physics.mcgill.ca)
///  \date 2013 Apr, Oct
///  \date 2014 Mar
///
///  *********************************************

#ifndef __util_macros_hpp__
#define __util_macros_hpp__

#include <unistd.h>

#include "gambit/Utils/boost_fallbacks.hpp"
#include "gambit/Utils/cats.hpp"
#include "gambit/Utils/stringify.hpp"  // stringification macro
#include "gambit/Utils/local_info.hpp" // Local information macro.
#include "gambit/Utils/export_symbols.hpp" // macro for controlling symbol visibility

#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/punctuation/comma.hpp>
#include <boost/preprocessor/punctuation/paren.hpp>

/// \name Compile-time error macro.
#define FAIL(x) static_assert(false,"GAMBIT precompiler error: " x);

/// \name Token appendment macro for use with BOOST_PP_SEQ_TRANSFORM
#define APPEND_TOKEN(s,data,elem) CAT(elem,data)

/// \name Dummy macros
/// Dummy macros that expand to nothing.
/// @{
#define DUMMY
#define DUMMYARG(...)
/// @}

/// \name Macro returning only the first argument passed
#define FIRST_ARG(A1,...) A1

/// \name Macro returning all but the first argument passed
/// @{
#define REMFIRST(...) REMFIRST_I(__VA_ARGS__)
#define REMFIRST_I(A1,...) (__VA_ARGS__)
/// @}

/// \name Macro chain for stripping parantheses off an argument
/// Usage: STRIP_PARENS(x). Example: STRIP_PARENS((y,z)) expands to y,z
/// @{
#define APPLY(macro, args) APPLY_I(macro, args)
#define APPLY_I(macro, args) macro args
#define STRIP_PARENS(x) EVAL_PAR((STRIP_PARENS_I x), x)
#define STRIP_PARENS_I(...) 1,1
#define EVAL_PAR(test, x) EVAL_PAR_I(test, x)
#define EVAL_PAR_I(test, x) MAYBE_STRIP_PARENS(TEST_ARITY test, x)
#define TEST_ARITY(...) APPLY(TEST_ARITY_I, (__VA_ARGS__, 2, 1, 0))
#define TEST_ARITY_I(a,b,c,...) c
#define MAYBE_STRIP_PARENS(cond, x) MAYBE_STRIP_PARENS_I(cond, x)
#define MAYBE_STRIP_PARENS_I(cond, x) CAT(MAYBE_STRIP_PARENS_, cond)(x)
#define MAYBE_STRIP_PARENS_1(x) x
#define MAYBE_STRIP_PARENS_2(x) APPLY(MAYBE_STRIP_PARENS_2_I, x)
#define MAYBE_STRIP_PARENS_2_I(...) __VA_ARGS__
/// @}

/// \name Macro chain checking if the argument has parantheses
/// Usage: HAS_PARENS(x). Example: HAS_PARENS((y,z)) expands to 1
/// @{
#define HAS_PARENS(x) EVAL_HASP((HAS_PARENS_I x), x)
#define HAS_PARENS_I(...) 1,1
#define EVAL_HASP(test, x) EVAL_HASP_I(test, x)
#define EVAL_HASP_I(test, x) CHECK_PARENS(TEST_ARITY test, x)
#define CHECK_PARENS(cond, x) CHECK_PARENS_I(cond, x)
#define CHECK_PARENS_I(cond, x) CAT(CHECK_PARENS_, cond)(x)
#define CHECK_PARENS_1(x) 0
#define CHECK_PARENS_2(x) 1
/// @}

/// \name Macro chain checking if the argument(s) passed has commas. Accepts up to 128 arguments.
/// Example: HAS_COMMA(1,2,3) expands to 1; HAS_COMMA(1) expands to 0
/// @{
#define _ARG128(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15,                                           \
_16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31,                                                 \
_32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47,                                                 \
_48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63,                                                 \
_64, _65, _66, _67, _68, _69, _70, _71, _72, _73, _74, _75, _76, _77, _78, _79,                                                 \
_80, _81, _82, _83, _84, _85, _86, _87, _88, _89, _90, _91, _92, _93, _94, _95,                                                 \
_96, _97, _98, _99, _100, _101, _102, _103, _104, _105, _106, _107, _108, _109,                                                 \
_110, _111, _112, _113, _114, _115, _116, _117, _118, _119, _120, _121, _122, _123, _124, _125, _126, _127, ...) _127

#define HAS_COMMA(...) _ARG128(__VA_ARGS__, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,                                                       \
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,                                                                     \
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,                                                                     \
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,                                                                     \
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,                                                                     \
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,                                                                     \
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0)
/// @}

/// \name Macro chain checking if the argument passed is empty
/// Example: ISEMPTY() expands to 1; ISEMPTY(1,2,3) expands to 0
/// @{
#define ISEMPTY(ARG) ISEMPTY_I(_129ONES STRIP_PARENS(ARG) ())
#define ISEMPTY_I(A) ISEMPTY_II(A,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)
#define ISEMPTY_II(...) _ARG128(__VA_ARGS__)
#define _129ONES() 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, \
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,\
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,\
    1,1,1,1,1,1,1,1,1,1,1,1
/// @}

/// \name Macro that expands to the argument list with a comma in front
/// if the (bracket enclosed) argument list is not empty.
/// If the agrument list is empty, expands to nothing.
/// @{
#define INSERT_NONEMPTY(ARG) CAT(INSERT_NONEMPTY_I,ISEMPTY(ARG))(ARG)
#define INSERT_NONEMPTY_I0(ARG) ,STRIP_PARENS(ARG)
#define INSERT_NONEMPTY_I1(...) DUMMYARG(__VA_ARGS__)
/// @}

/// \name Boost 2-tuple access macros
/// Used to avoid possible reentrancy issues with multiple use of BOOST_PP_TUPLE_ELEM.
/// @{
#define PAIR_ELEMENT0(TPLE) PAIR_ELEMENT0_I TPLE
#define PAIR_ELEMENT0_I(A,B) A
#define PAIR_ELEMENT1(TPLE) PAIR_ELEMENT1_I TPLE
#define PAIR_ELEMENT1_I(A,B) B
/// @}

/// \name Type comparison macros
/// Macros to evaluate whether two intrinsic types are identical or not.
/// Example use: define a macro that evaluates to 1 if token X = void, 0
/// otherwise.
/// \code
/// #define X_IS_VOID(X) IS_TYPE(X, void)
/// \endcode
/// @{
#define void_void                       1)(1
#define int_int                         1)(1
#define float_float                     1)(1
#define double_double                   1)(1
#define bool_bool                       1)(1
#define char_char                       1)(1
#define string_string                   1)(1
#define ModelParameters_ModelParameters 1)(1
#define IS_TYPE(COMPTYPE,TYPE) BOOST_PP_EQUAL(BOOST_PP_SEQ_SIZE((CAT_3(COMPTYPE,_,TYPE))),2)
/// @}

/// \name String comparison macros.
/// Macros for evaluating whether tokens are equal or not for certain special values, and
/// for then switching on the result.
/// Define your special values, such as "myToken" locally as
/// \code
/// #define myToken_myToken 1)(1
/// Just like the IS_TYPE macro, so redirects to that.
/// \endcode
/// @{
#define IS_EQUAL(A,B)          IS_TYPE(A,B)
#define IF_EQUAL(A,B,C)        BOOST_PP_IIF(IS_EQUAL(A,B),C,)
#define IF_NOT_EQUAL(A,B,C)    BOOST_PP_IIF(IS_EQUAL(A,B), ,C)
#define IF_ELSE_EQUAL(A,B,C,D) BOOST_PP_IIF(IS_EQUAL(A,B),C,D)
/// @}

/// \name Empty token test macros.
/// Macros for evaluating whether certain tokens are empty or not, and
/// for then switching on the result.
/// @{
#define EMPTY_TOKEN_TESTER 1)(1
#define IS_EMPTY(A)          IS_EQUAL(CAT(A,EMPTY),TOKEN_TESTER)
#define IF_EMPTY(A,B)        BOOST_PP_IIF(IS_EMPTY(A),B,)
#define IF_NOT_EMPTY(A,B)    BOOST_PP_IIF(IS_EMPTY(A), ,B)
#define IF_ELSE_EMPTY(A,B,C) BOOST_PP_IIF(IS_EMPTY(A),B,C)
/// @}

/// \name General variadic macro expanders
/// Generic variadic macro expanders for 1 to 10 arguments.
/// Example use: redirect EXAMPLE according to whether it is called
/// with 2, 3 or 4 arguments.
/// \code
/// #define EXAMPLE_4(_1, _2, _3, _4) DOSTUFF(_1,  _2,  _3,  _4)
/// #define EXAMPLE_3(_1, _2, _3)     DOSTUFF(_1,  _2,  _3, foo)
/// #define EXAMPLE_2(_1, _2)         DOSTUFF(_1,  _2, foo, bar)
/// #define EXAMPLE(...)              VARARG(EXAMPLE, __VA_ARGS__)
/// \endcode
/// @{
#define VA_NARGS_IMPL(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, N, ...) N
#define VA_NARGS(...) VA_NARGS_IMPL(X,__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#define VARARG_IMPL2(base, count, ...) CAT_3(base,_,count)(__VA_ARGS__)
#define VARARG_IMPL(base, count, ...) VARARG_IMPL2(base, count, __VA_ARGS__)
#define VARARG(base, ...) VARARG_IMPL(base, VA_NARGS(__VA_ARGS__), __VA_ARGS__)
/// @}

/// \name Duplicate of variadic macro expanders, to allow nesting.
/// @{
#define VA_NARGS_NESTED_IMPL(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, N, ...) N
#define VA_NARGS_NESTED(...) VA_NARGS_NESTED_IMPL(X,__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#define VARARG_NESTED_IMPL2(base, count, ...) CAT_3(base,_,count)(__VA_ARGS__)
#define VARARG_NESTED_IMPL(base, count, ...) VARARG_NESTED_IMPL2(base, count, __VA_ARGS__)
#define VARARG_NESTED(base, ...) VARARG_NESTED_IMPL(base, VA_NARGS_NESTED(__VA_ARGS__), __VA_ARGS__)
/// @}

/// \name Variadic macro expanders taking 3 leading arguments
/// @{
#define VA_NARGS_AB_IMPL(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, N, ...) N
#define VA_NARGS_AB(...) VA_NARGS_AB_IMPL(X,__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#define VARARG_AB_IMPL2(base, A, B, count, ...) CAT_3(base,_,count)(A, B, __VA_ARGS__)
#define VARARG_AB_IMPL(base, A, B, count, ...) VARARG_AB_IMPL2(base, A, B, count, __VA_ARGS__)
#define VARARG_AB(base, A, B, ...) VARARG_AB_IMPL(base, A, B, VA_NARGS_AB(__VA_ARGS__), __VA_ARGS__)
/// @}

/// \name Variadic macro expanders for distinguishing between 1 and >1 variadic argument
/// @{
#define VARARG_SWITCH_ON_GT_ONE_TESTER_1 1)(1
#define VA_NARGS_SWITCH_ON_GT_ONE_IMPL(_1, _2, _3, N, ...) IF_ELSE_EQUAL(VARARG_SWITCH_ON_GT_ONE_TESTER,N,N,MORE)
#define VA_NARGS_SWITCH_ON_GT_ONE(...) VA_NARGS_SWITCH_ON_GT_ONE_IMPL(X,__VA_ARGS__, 2, 1, 0)
#define VARARG_SWITCH_ON_GT_ONE_IMPL2(base, count, ...) CAT_3(base,_,count)(__VA_ARGS__)
#define VARARG_SWITCH_ON_GT_ONE_IMPL(base, count, ...) VARARG_SWITCH_ON_GT_ONE_IMPL2(base, count, __VA_ARGS__)
#define VARARG_SWITCH_ON_GT_ONE(base, ...) VARARG_SWITCH_ON_GT_ONE_IMPL(base, VA_NARGS_SWITCH_ON_GT_ONE(__VA_ARGS__), __VA_ARGS__)
/// @}

/// \name Variadic macro expanders for distinguishing between 1 and >1 variadic argument, taking 1 leading argument
/// @{
#define VARARG_SWITCH_ON_GT_ONE_A_TESTER_1 1)(1
#define VA_NARGS_SWITCH_ON_GT_ONE_A_IMPL(_1, _2, _3, N, ...) IF_ELSE_EQUAL(VARARG_SWITCH_ON_GT_ONE_A_TESTER,N,N,MORE)
#define VA_NARGS_SWITCH_ON_GT_ONE_A(...) VA_NARGS_SWITCH_ON_GT_ONE_A_IMPL(X,__VA_ARGS__, 2, 1, 0)
#define VARARG_SWITCH_ON_GT_ONE_A_IMPL2(base, A, count, ...) CAT_3(base,_,count)(A, __VA_ARGS__)
#define VARARG_SWITCH_ON_GT_ONE_A_IMPL(base, A, count, ...) VARARG_SWITCH_ON_GT_ONE_A_IMPL2(base, A, count, __VA_ARGS__)
#define VARARG_SWITCH_ON_GT_ONE_A(base, A, ...) VARARG_SWITCH_ON_GT_ONE_A_IMPL(base, A, VA_NARGS_SWITCH_ON_GT_ONE_A(__VA_ARGS__), __VA_ARGS__)
/// @}

/// \name Variadic macro expanders for distinguishing between 1 and >1 variadic argument, taking 3 leading arguments
/// @{
#define VARARG_SWITCH_ON_GT_ONE_ABC_TESTER_1 1)(1
#define VA_NARGS_SWITCH_ON_GT_ONE_ABC_IMPL(_1, _2, _3, N, ...) IF_ELSE_EQUAL(VARARG_SWITCH_ON_GT_ONE_ABC_TESTER,N,N,MORE)
#define VA_NARGS_SWITCH_ON_GT_ONE_ABC(...) VA_NARGS_SWITCH_ON_GT_ONE_ABC_IMPL(X,__VA_ARGS__, 2, 1, 0)
#define VARARG_SWITCH_ON_GT_ONE_ABC_IMPL2(base, A, B, C, count, ...) CAT_3(base,_,count)(A, B, C, __VA_ARGS__)
#define VARARG_SWITCH_ON_GT_ONE_ABC_IMPL(base, A, B, C, count, ...) VARARG_SWITCH_ON_GT_ONE_ABC_IMPL2(base, A, B, C, count, __VA_ARGS__)
#define VARARG_SWITCH_ON_GT_ONE_ABC(base, A, B, C, ...) VARARG_SWITCH_ON_GT_ONE_ABC_IMPL(base, A, B, C, VA_NARGS_SWITCH_ON_GT_ONE_ABC(__VA_ARGS__), __VA_ARGS__)
/// @}

/// \name Variadic macro expanders for distinguishing between 1, 2 and >2 variadic arguments, taking 3 leading arguments
/// @{
#define VARARG_SWITCH_ON_GT_TWO_ABC_TESTER_2 1)(1
#define VARARG_SWITCH_ON_GT_TWO_ABC_TESTER_1 1)(1
#define VA_NARGS_SWITCH_ON_GT_TWO_ABC_IMPL(_1, _2, _3, _4, N, ...) IF_ELSE_EQUAL(VARARG_SWITCH_ON_GT_TWO_ABC_TESTER,\
                                                                                 BOOST_PP_TUPLE_ELEM(0,(STRIP_PARENS(N))),N,MORE)
#define VA_NARGS_SWITCH_ON_GT_TWO_ABC(...) VA_NARGS_SWITCH_ON_GT_TWO_ABC_IMPL(X,__VA_ARGS__, 3, 2, 1, 0)
#define VARARG_SWITCH_ON_GT_TWO_ABC_IMPL2(base, A, B, C, count, ...) CAT_3(base,_,count)(A, B, C, __VA_ARGS__)
#define VARARG_SWITCH_ON_GT_TWO_ABC_IMPL(base, A, B, C, count, ...) VARARG_SWITCH_ON_GT_TWO_ABC_IMPL2(base, A, B, C, count, __VA_ARGS__)
#define VARARG_SWITCH_ON_GT_TWO_ABC(base, A, B, C, ...) VARARG_SWITCH_ON_GT_TWO_ABC_IMPL(base, A, B, C, VA_NARGS_SWITCH_ON_GT_TWO_ABC(__VA_ARGS__), __VA_ARGS__)
/// @}

/// \name Bottom-level definition-checking macros
/// Generic macros that can be used from within other macros
/// to test whether or not some other macro is defined.
/// To count as "defined" for the purposes of these macros, there
/// must exist a macro definition of the following form:
/// \code
/// #define DEFINED_FOO ()
/// \endcode
/// If this definition exists, DEFINED(FOO) will return 1.  It is up to
/// you to actually create a matching macro FOO when you create DEFINED_FOO,
/// and then do something with the information that DEFINED provides about
/// the existence of DEFINED_FOO (and presumably also FOO).
///
/// Typically these macros would be used to switch behaviour on a flag
/// passed to a macro.  See \link START_FUNCTION() START_FUNCTION \endlink
/// in module_macros_common.hpp for a detailed worked example.
/// @{
#define CHECK_N(x, n, ...) n
#define CHECK(...) CHECK_N(__VA_ARGS__, 0, 0)
#define PROBE(x) x, 1
#define DEFINED_PROBE(NAME)            DEFINED_PROBE_PROXY( DEFINED_##NAME )      // concatenate DEFINED_ prefix with function name
#define DEFINED_PROBE_PROXY(...)       DEFINED_PROBE_PRIMITIVE(__VA_ARGS__)       // expand arguments
#define DEFINED_PROBE_PRIMITIVE(x)     DEFINED_PROBE_COMBINE_ x                   // collapse again
#define DEFINED_PROBE_COMBINE_(...)    PROBE(X)
/// Returns 1 or 0 depending on whether a corresponding DEFINED_<NAME> () macro has been
/// \code #defined \endcode or not.
#define DEFINED(NAME)                  CHECK(DEFINED_PROBE(NAME))
/// @}

/// \name High-level definition-checking macros.
/// These are just nice wrappers around \link DEFINED() DEFINED\endlink for specific logical cases.
/// @{

/// Do ACTION if NAME is defined.
#define IF_DEFINED(NAME,ACTION)        BOOST_PP_IF(DEFINED(NAME), ACTION, )
/// Do ACTION if NAME is undefined.
#define IF_NOT_DEFINED(NAME,ACTION)    BOOST_PP_IF(DEFINED(NAME), , ACTION)
/// Do IF if NAME is defined, otherwise do ELSE.
#define IF_ELSE_DEFINED(NAME,IF,ELSE)  BOOST_PP_IF(DEFINED(NAME), IF, ELSE)
/// @}

/// \name Sneaky redefinition of \link DEFINED() DEFINED\endlink to allow testing whether specific tokens are defined.
/// @{
#define TOKEN_DEFINED(A) BOOST_PP_NOT(DEFINED(A))
#define IF_TOKEN_DEFINED(A,B) BOOST_PP_IIF(DEFINED(A),BOOST_PP_EMPTY(),B)
#define IF_TOKEN_UNDEFINED(A,B) BOOST_PP_IIF(DEFINED(A),B,BOOST_PP_EMPTY())
#define IF_ELSE_TOKEN_DEFINED(A,B,C) BOOST_PP_IIF(DEFINED(A),C,B)
#define DEFINED_MODULE                 ()
#define DEFINED_CAPABILITY             ()
#define DEFINED_FUNCTION               ()
#define DEFINED_CONDITIONAL_DEPENDENCY ()
/// @}

/// Pop the last argument off a Boost preprocessor sequence
/// @{
#define POP_LAST(...) CAT(POP_LAST_, BOOST_PP_VARIADIC_SIZE __VA_ARGS__) __VA_ARGS__
#define POP_LAST_1(x1)
#define POP_LAST_2(x1, x2) x1
#define POP_LAST_3(x1, x2, x3) x1, x2
#define POP_LAST_4(x1, x2, x3, x4) x1, x2, x3
#define POP_LAST_5(x1, x2, x3, x4, x5) x1, x2, x3, x4
#define POP_LAST_6(x1, x2, x3, x4, x5, x6) x1, x2, x3, x4, x5
#define POP_LAST_7(x1, x2, x3, x4, x5, x6, x7) x1, x2, x3, x4, x5, x6
#define POP_LAST_8(x1, x2, x3, x4, x5, x6, x7, x8) x1, x2, x3, x4, x5, x6, x7
#define POP_LAST_9(x1, x2, x3, x4, x5, x6, x7, x8, x9) x1, x2, x3, x4, x5, x6, x7, x8
#define POP_LAST_10(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10) x1, x2, x3, x4, x5, x6, x7, x8, x9
/// @}

/// Macros for dealing with variadic function arguments in backend functions
/// @{
#define etc_etc 1)(1
#define LAST_ARG_VARIADIC(T) IS_ELLIPSIS(BOOST_PP_TUPLE_ELEM(BOOST_PP_SUB(BOOST_PP_VARIADIC_SIZE T,1),T))
#define IS_ELLIPSIS(ELEM) IS_EQUAL(etc,ELEM)
#define STRIP_VARIADIC_ARG(T)   BOOST_PP_IIF(LAST_ARG_VARIADIC(T), (POP_LAST(T)),      T)
#define CONVERT_VARIADIC_ARG(T) BOOST_PP_IIF(LAST_ARG_VARIADIC(T), (POP_LAST(T), ...), T)
/// @}

/// \name Preprocessor switch-case statements
/// @{
#define IF_ELSEIF_9(VAR1, _1, VAR2, _2, VAR3, _3, VAR4, _4, _5) \
         BOOST_PP_IF(VAR1, _1,                                  \
         BOOST_PP_IF(VAR2, _2,                                  \
         BOOST_PP_IF(VAR3, _3,                                  \
         BOOST_PP_IF(VAR4, _4, _5))))
#define IF_ELSEIF_7(VAR1, _1, VAR2, _2, VAR3, _3, _4)           \
         BOOST_PP_IF(VAR1, _1,                                  \
         BOOST_PP_IF(VAR2, _2,                                  \
         BOOST_PP_IF(VAR3, _3, _4)))
#define IF_ELSEIF_5(VAR1, _1, VAR2, _2, _3)                     \
         BOOST_PP_IF(VAR1, _1,                                  \
         BOOST_PP_IF(VAR2, _2, _3))
#define IF_ELSEIF(...) VARARG_NESTED(IF_ELSEIF, __VA_ARGS__)
/// @}

/// Macro for defining a static const vector easily. With C++11 could use initialiser lists, but
/// this is not available in all the compilers we want to support. Use this as a replacement.
/// e.g.
/// static const std::vector<int> myvector = {1,2,3,4}; // Not possible in all compilers we support.
/// becomes
/// MAKE_STATIC_VECTOR(int,myvector,(1,2,3,4))
#define BRACED_INIT_LIST(...) { __VA_ARGS__ }
#define MAKE_STATIC_VECTOR(TYPE,NAME,TUPLE) \
   static const TYPE NAME##_array[] = BRACED_INIT_LIST TUPLE; \
   static const std::vector<TYPE> NAME(NAME##_array, Utils::endA( NAME##_array ));
#define MAKE_STATIC_SET(TYPE,NAME,TUPLE) \
   static const TYPE NAME##_array[] = BRACED_INIT_LIST(TUPLE); \
   static const std::set<TYPE> NAME(NAME##_array, Utils::endA( NAME##_array ));

/// Macro to redirect stderr to /dev/null for a single function call,
/// for use with particularly noisy external libraries
#define CALL_WITH_SILENCED_STDERR(FUNCTION_CALL)    \
  int fd;                                           \
  fpos_t pos;                                       \
  fflush(stderr);                                   \
  fgetpos(stderr, &pos);                            \
  fd = dup(fileno(stderr));                         \
  freopen("/dev/null", "w", stderr);                \
                                                    \
  (FUNCTION_CALL);                                  \
                                                    \
  fflush(stderr);                                   \
  dup2(fd, fileno(stderr));                         \
  close(fd);                                        \
  clearerr(stderr);                                 \
  fsetpos(stderr, &pos);


#endif //defined __util_macros_hpp__
