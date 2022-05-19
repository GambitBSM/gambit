//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Macros for defining new particles.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///   
///  \author Pat Scott  
///          (p.scott@imperial.ac.uk)
///  \date 2015 Jan
///
///  *********************************************

#ifndef __particle_macros_hpp__
#define __particle_macros_hpp__

#include "gambit/Utils/boost_fallbacks.hpp"

#include <boost/preprocessor/tuple/to_seq.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/arithmetic/add.hpp>

#define add_particle(LONGNAME, INTPAIR, SPINX2, CHARGEX3, COLOR) particles->add(LONGNAME, std::pair<int, int> INTPAIR, SPINX2, CHARGEX3, COLOR);
#define add_SM_particle(LONGNAME, INTPAIR, SPINX2, CHARGEX3, COLOR) particles->add_SM(LONGNAME, std::pair<int, int> INTPAIR, SPINX2, CHARGEX3, COLOR );
#define add_generic_particle(LONGNAME, INTPAIR, SPINX2, CHARGEX3, COLOR) particles->add_generic(LONGNAME, std::pair<int, int> INTPAIR, SPINX2, CHARGEX3, COLOR);
#define ADD_PARTICLE_I(r, DATA, I, ELEM) particles->add_with_short_pair(BOOST_PP_TUPLE_ELEM(4, 0, DATA) "_" STRINGIFY(BOOST_PP_ADD(I,1)), std::pair<int, int> ELEM, std::pair<str, int> (BOOST_PP_TUPLE_ELEM(4, 0, DATA),BOOST_PP_ADD(I,1)), BOOST_PP_TUPLE_ELEM(4, 1, DATA), BOOST_PP_TUPLE_ELEM(4, 2, DATA), BOOST_PP_TUPLE_ELEM(4, 3, DATA));
#define ADD_SM_PARTICLE_I(r, DATA, I, ELEM) particles->add_SM_with_short_pair(BOOST_PP_TUPLE_ELEM(4, 0, DATA) "_" STRINGIFY(BOOST_PP_ADD(I,1)), std::pair<int, int> ELEM, std::pair<str, int> (BOOST_PP_TUPLE_ELEM(4, 0, DATA),BOOST_PP_ADD(I,1)), BOOST_PP_TUPLE_ELEM(4, 1, DATA), BOOST_PP_TUPLE_ELEM(4, 2, DATA), BOOST_PP_TUPLE_ELEM(4, 3, DATA));
#define add_particle_set(SHORTNAME, __TUP, SPINX2, CHARGEX3, COLOR) BOOST_PP_SEQ_FOR_EACH_I(ADD_PARTICLE_I, (SHORTNAME, SPINX2, CHARGEX3, COLOR), BOOST_PP_TUPLE_TO_SEQ(__TUP))
#define add_SM_particle_set(SHORTNAME, __TUP, SPINX2, CHARGEX3, COLOR) BOOST_PP_SEQ_FOR_EACH_I(ADD_SM_PARTICLE_I, (SHORTNAME, SPINX2, CHARGEX3, COLOR), BOOST_PP_TUPLE_TO_SEQ(__TUP))

#endif //__particle_macros_hpp__
