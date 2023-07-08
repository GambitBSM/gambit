//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Rollcall header for module ExampleBit_A.
///
///  Compile-time registration of available
///  observables and likelihoods, as well as their
///  dependencies.
///
///  Add to this if you want to add an observable
///  or likelihood to this module.
///
///  Don't put typedefs or other type definitions
///  in this file; see
///  Elements/include/gambit/Elements/types_rollcall.hpp
///  for further instructions on how to add new
///  types.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (patscott@physics.mcgill.ca)
///  \date 2012 Nov
///  \date 2013 Jan, Feb
///
///  *********************************************


#ifndef __ExampleBit_A_rollcall_hpp__
#define __ExampleBit_A_rollcall_hpp__

#define MODULE ExampleBit_A
START_MODULE


  #define CAPABILITY nevents                // A physical observable or likelihood that this module can calculate.  There may be one or more
  START_CAPABILITY                          // functions in this module that can calculate this particular thing in different ways.

    #define FUNCTION nevents_pred           // Name of an observable function: floating-point number of events in some hypothetical process
    START_FUNCTION(double)                  // Declare that this function calculates the nevents observable as a double precision variable
    DEPENDENCY(xsection, double)            // Dependencies: Number of events depends on cross-section
    #undef FUNCTION

    #define FUNCTION nevents_pred_rounded   // Name of an observable function: integral number of events in some hypothetical process
    START_FUNCTION(int)                     // Declare that this function calculates the nevents observable as an integer variable
    DEPENDENCY(nevents, double)             // Dependencies: Integral number of events depends on floating-point nevents
    #undef FUNCTION

  #undef CAPABILITY


  #define CAPABILITY Example_lnL_A          // A likelihood that this module can calculate
  START_CAPABILITY

    #define FUNCTION nevents_like           // Likelihood: Likelihood of seeing number of events
    START_FUNCTION(double)                  // Function calculates the nevents_like likelihood as a double precision variable
    DEPENDENCY(nevents, double)             // Dependency: Likelihood calculation requires number of events
    DEPENDENCY(eventAccumulation, int)      // Depends on the accumulated events that pass the make-believe cuts in the make-believe event loop
    #undef FUNCTION

  #undef CAPABILITY


  #define CAPABILITY eventLoopManagement
  START_CAPABILITY

    #define FUNCTION eventLoopManager       // Module functions that have been designed to manage loops over other module functions need to
    START_FUNCTION(void, CAN_MANAGE_LOOPS)  // be declared with the optional CAN_MANAGE_LOOPS flag.  When this flag is absent, or if the
    #undef FUNCTION                         // flag CANNOT_MANAGE_LOOPS is given instead, GAMBIT assumes that the function should not
                                            // be allowed to manage loops.  Functions cannot have void result types unless they CAN_MANAGE_LOOPS.
  #undef CAPABILITY


  #define CAPABILITY event
  START_CAPABILITY

    #define FUNCTION exampleEventGen
    START_FUNCTION(float)
    NEEDS_MANAGER(eventLoopManagement) // Declares that the module function can only run inside a loop, and that the loop
    #undef FUNCTION                    // must be managed by another module function that has CAPABILITY eventLoopManagement
                                       // (and has been declared as a potential manager with the flag CAN_MANAGE_LOOPS).
    #define FUNCTION exampleCut
    START_FUNCTION(int)
    NEEDS_MANAGER(eventLoopManagement)
    DEPENDENCY(event, float)
    #undef FUNCTION

  #undef CAPABILITY


  #define CAPABILITY eventAccumulation
  START_CAPABILITY

    #define FUNCTION eventAccumulator
    START_FUNCTION(int, CANNOT_MANAGE_LOOPS)
    NEEDS_MANAGER(eventLoopManagement)
    DEPENDENCY(event, int)
    #undef FUNCTION

  #undef CAPABILITY


  #define CAPABILITY particle_id            // A physical observable or likelihood that this module can calculate
  START_CAPABILITY

    #define FUNCTION particle_identity      // Observable: particle ID
    START_FUNCTION(std::string)             // Function returns the identity of the particle as a string
    #undef FUNCTION

  #undef CAPABILITY


  // Mock muon (g-2) anomalous contribution; an example of how to interact with models
  #define CAPABILITY damu
  START_CAPABILITY
    #define FUNCTION example_damu
    START_FUNCTION(double)
    // Function must be used with one model from group1 (NormalDist) and one from group2 (CMSSM or SingletDM)
    ALLOW_MODEL_DEPENDENCE(NormalDist, SingletDM, CMSSM)
    MODEL_GROUP(group1, (NormalDist))
    MODEL_GROUP(group2, (CMSSM, SingletDM))
    ALLOW_MODEL_COMBINATION(group1, group2)
      // A dependency that only counts under certain conditions (must come after all BACKEND_REQs)
      #define CONDITIONAL_DEPENDENCY xsection
      START_CONDITIONAL_DEPENDENCY(double)
      ACTIVATE_FOR_MODELS(CMSSM)
      #undef CONDITIONAL_DEPENDENCY
    #undef FUNCTION
  #undef CAPABILITY


  // Test function for fulfilling the dependency of nevents.  Also gives another more complicated example of model group usage.
  #define CAPABILITY xsection
  START_CAPABILITY
    #define FUNCTION test_sigma
    START_FUNCTION(double)

    // Function can be used if either NormalDist or SingletDM alone are in use.
    ALLOW_MODELS(NormalDist, SingletDM)
    // Function can also be used if CMSSM is in use, so long as either NormalDist or SingletDM is in use too.
    ALLOW_MODEL_DEPENDENCE(CMSSM)
    MODEL_GROUP(group1, (NormalDist, SingletDM))
    MODEL_GROUP(group2, (CMSSM))
    ALLOW_MODEL_COMBINATION(group1, group2)
    // Function can also be used if either NUHM1 or NUHM2 is in use, so long as either NormalDist or SingletDM is in use.
    // Note that this automatically means that if CMSSM + (NUHM1 or NUHM2) + (NormalDist or SingletDM) is in use, the function can be used.
    // However, it does not allow the function to be used if only CMSSM + (NUHM1 or NUHM2) are in use.
    ALLOW_MODEL_DEPENDENCE(NUHM1, NUHM2)
    MODEL_GROUP(group3, (NUHM1, NUHM2))
    ALLOW_MODEL_COMBINATION(group1, group3)
    // Function can also be used if MSSM19atQ is in use, but only if CMSSM + (NUHM1 or NUHM2) + (NormalDist or SingletDM) are in use too.
    ALLOW_MODEL_DEPENDENCE(MSSM19atQ)
    MODEL_GROUP(group4, (MSSM19atQ))
    ALLOW_MODEL_COMBINATION(group1, group2, group3, group4)

    #undef FUNCTION
  #undef CAPABILITY


  // A test likelihood: normal distribution
  #define CAPABILITY normaldist_loglike
  START_CAPABILITY
    #define FUNCTION lnL_gaussian
    START_FUNCTION(double)
    ALLOW_MODELS(NormalDist)
    #undef FUNCTION
  #undef CAPABILITY


  // Tester that shows how to retrieve pointers to backend functions
  #define CAPABILITY function_pointer
  START_CAPABILITY
    #define FUNCTION function_pointer_retriever
    START_FUNCTION(fptr)
    BACKEND_GROUP(external_funcs)
    BACKEND_REQ_FROM_GROUP(external_funcs, externalFunction, (), double, (int&))
    BACKEND_REQ_FROM_GROUP(external_funcs, externalComplicatedFunction, (), double, (int&, const double&))
    #undef FUNCTION
  #undef CAPABILITY


  // Tester for Fortran array overlay classes
  #define CAPABILITY test_Farrays
  START_CAPABILITY
    #define FUNCTION do_Farray_stuff
    START_FUNCTION(double)
    BACKEND_REQ(libFarrayTestCommonBlock, (match), libFarrayTest_CB_type)
    BACKEND_REQ(libFarrayTestCommonBlock2, (match), libFarrayTest_CB2_type)
    BACKEND_REQ(libFarrayTestCommonBlock3, (match), libFarrayTest_CB3_type)
    BACKEND_REQ(libFarrayTest_printStuff, (match), void, ())
    BACKEND_REQ(libFarrayTest_fillArrays, (match), void, ())
    BACKEND_REQ(libFarrayTest_fptrRoutine, (match), void, (Farray< Fdouble,1,3>&, Finteger&, Fdouble(*)(Farray< Fdouble,1,3>&)))
    BACKEND_REQ(libFarrayTest_doubleFuncArray, (match), Fdouble, (Farray< Fdouble,1,3>&))
    BACKEND_REQ(libFarrayTest_doubleFuncArray2, (match), Fdouble, (Fdouble*))
    BACKEND_REQ(libFarrayTest_doubleFuncArray3, (match), Fdouble, (Farray<Fdouble, 1,2, 2,3>&))
    BACKEND_OPTION((LibFarrayTest), (match))
    #undef FUNCTION
  #undef CAPABILITY


  // Tester for marginalised Poisson likelihood.
  #define CAPABILITY test_marg_lnlike
  START_CAPABILITY
    #define FUNCTION marg_poisson_test
    START_FUNCTION(double)
    BACKEND_REQ_FROM_GROUP(lnlike_marg_poisson, lnlike_marg_poisson_lognormal_error, (), double, (const int&, const double&, const double&, const double&) )
    BACKEND_REQ_FROM_GROUP(lnlike_marg_poisson, lnlike_marg_poisson_gaussian_error, (), double, (const int&, const double&, const double&, const double&) )
    BACKEND_GROUP(lnlike_marg_poisson)
    #undef FUNCTION
  #undef CAPABILITY

  // Scale test for various aspects of the printer buffer system
  // Creates 1000 items to be printed per point
  #define CAPABILITY large_print
  START_CAPABILITY
    #define FUNCTION large_print
    START_FUNCTION(map_str_dbl)
    #undef FUNCTION
  #undef CAPABILITY


  // Tester for C/C++ backend array interfaces
  #define CAPABILITY test_BE_Array
  START_CAPABILITY
    #define FUNCTION Backend_array_test
    START_FUNCTION(double)
    BACKEND_REQ(example_be_array_1D, (), double, (double*))
    BACKEND_REQ(example_be_array_2D, (), double, (double(*)[10]))
    BACKEND_REQ(example_be_array_3D, (), double, (double(*)[10][10]))
    #undef FUNCTION
  #undef CAPABILITY

  // Flat test likelihood for checking prior distributions
  #define CAPABILITY test_flat_likelihood
  START_CAPABILITY
    #define FUNCTION flat_likelihood
    START_FUNCTION(double)
    ALLOW_MODELS(TestModel1D)
    #undef FUNCTION
  #undef CAPABILITY

#undef MODULE


#endif /* defined(__ExampleBit_A_rollcall_hpp__) */
