//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  GAMBIT demonstration models.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///   
///  \author Ben Farmer
///  \date 2013 May
///  \date 2014 Mar
///  \date 2019 Jul
///
///  \author Pat Scott
///  \date 2013 Sep
///
///  *********************************************


#ifndef __demo_hpp__
#define __demo_hpp__

// This is the normal distribution toy model used in ExampleBit_A.
#define MODEL NormalDist
  START_MODEL
  DEFINEPARS(mu,sigma)
#undef MODEL

// A one-parameter model for testing simple prior transformations
#define MODEL TestModel1D
  START_MODEL
  DEFINEPARS(x)
#undef MODEL

// The following are some examples that demonstrate the available ways to declare
// models and their relationships.  These are commented out as they are not necessary for  
// any of the module examples, but you can uncomment and experiment with them in order to
// learn about model declaration in GAMBIT if you like.

/*
 
#include "gambit/Logs/logging.hpp"
#include <string>

// Start a new model family tree, beginning at the top. The_ancient_one has no parent.
#define MODEL the_ancient_one
  START_MODEL
  DEFINEPARS(p1,p2,p3)
#undef MODEL

// This is a model that everything else is connected through, but really does nothing -- kinda like Kevin Bacon.
// Feel free to rename it after your most unresponsive senior collaborator.
#define MODEL kevin_bacon
#define PARENT the_ancient_one
  START_MODEL
  DEFINEPARS(M1,M2,M3)    // You can call this more than once:
  DEFINEPARS(AU1,AU2,AU3)

  // Declare the interpret-as-parent function.  This function gets CAPABILITY = PARENT_parameters,
  // TYPE = ModelParameters and MODULE = MODEL.  It converts parameter values of the MODEL to
  // parameter values of the PARENT.  The user-defined part of the function can go anywhere, so
  // long as you properly attach it to this declaration (which puts the function here:
  // Gambit::Models::MODEL::<FUNCTION>).  The MODEL_NAMESPACE macro gets you the Gambit::Models::MODEL
  // part, if MODEL is defined.
  INTERPRET_AS_PARENT_FUNCTION(kevin_bacon_IAPfunc)

  // Define the interpret-as-parent function.
  // Note that "myparams" must be const. You're not allowed to change them here. Change "parentparams".
  // To be able to access the Pipes, in case dependencies exist, this function has to be put in
  // the correct namespace, and be defined after it has been declared using the INTERPRET_AS_PARENT macro.
  // To make it easier to attach the function definition to the correct declaration, use the macro "MODEL_NAMESPACE".
  void MODEL_NAMESPACE::kevin_bacon_IAPfunc (const ModelParameters &myparams, ModelParameters &parentparams)
  {
      logger()<<"Running interpret_as_parent calculations for kevin_bacon -> the_ancient_one ..."<<EOM;
      
      double M1 = myparams["M1"];
      double M2 = myparams["M2"];
      double M3 = myparams["M3"];
      double AU1 = myparams["AU1"];
      double AU2 = myparams["AU2"];
      double AU3 = myparams["AU3"];
    
      parentparams.setValue("p1", 0.01*M1*M2+AU1);
      parentparams.setValue("p2", 0.10*M2*M3+AU2);
      parentparams.setValue("p3", 1.00*M1*M3+AU3);
  } 
#undef PARENT
#undef MODEL


#define MODEL demo_A
#define PARENT kevin_bacon
  START_MODEL
  DEFINEPARS(M0, M12, A0, Mstop, tanb, sgnmu)
  
  // Attach a CAPABILITY to a parameter.
  // This creates a new module function with CAPABILITY = Mstop_obs, TYPE = double and MODULE = MODEL.
  MAP_TO_CAPABILITY(Mstop, Mstop_obs)

  // Declare the interpret-as-parent function for going up the model hierarchy to kevin_bacon.  
  INTERPRET_AS_PARENT_FUNCTION(demo_A_IAPfunc)

  // Give the new interpret-as-parent function a dependency, a la regular GAMBIT module functions.
  INTERPRET_AS_PARENT_DEPENDENCY(id, std::string)
  
  // Define the interpret-as-parent function.  This can also be done in a source file if you prefer.
  void MODEL_NAMESPACE::demo_A_IAPfunc (const ModelParameters &myparams, ModelParameters &parentparams)
  {
      // Finding the correct Pipes to retrieve dependencies in model functions can take
      // a little effort.  To save this effort, use the USE_MODEL_PIPE(MODEL_X) macro. 
      // This macro just expands to the following:
      //   using namespace Gambit::Models::MODEL::Pipes::MODEL_X_parameters;
      // which points to the Pipes for the module function that wraps the user-defined
      // interpret-as function.
      USE_MODEL_PIPE(PARENT)

      logger()<<"Running interpret_as_parent calculations for demo_A -> kevin_bacon ..."<<EOM;
      
      double M0  = myparams["M0"];
      double A0  = myparams["A0"];
      
      // Play around with the extra info obtained from the dependency.
      logger()<<"identity dependency has supplied the value: "<<*Dep::id<<EOM;
      
      // Grab a reference to the parent parameter object and set some values. 
      // The parent parameter object already exists if we have gotten this 
      // far (it was created along with the functor that wraps this function).
      parentparams.setValue("M1", M0);
      parentparams.setValue("M2", 0.5*M0);
      parentparams.setValue("M3", 3*M0);
      parentparams.setValue("AU1", A0);
      parentparams.setValue("AU2", 2*A0);
      parentparams.setValue("AU3", 0);
  }
#undef PARENT
#undef MODEL


// Alternative parameterisations of models are treated just like any other model. You may like to have
// a "primary" parameterisation, and "alternative" parameterisations which are child models of the
// primary, with interpret-as-parent functions defined to convert from the alternate to the primary parameters.
#define MODEL demo_A_alternative
#define PARENT demo_A
  START_MODEL
  DEFINEPARS(M0, M12, A0, Mstop, X_rotated, Y_rotated)
  INTERPRET_AS_PARENT_FUNCTION(demo_A_alternative_IAPfunc)

  void MODEL_NAMESPACE::demo_A_alternative_IAPfunc (const ModelParameters &myparams, ModelParameters &parentparams)
  {
    // Get the Pipes for the interpret-as-parent function
    USE_MODEL_PIPE(PARENT)
    // Get alternative model parameters
    double xrot = myparams["X_rotated"];
    double yrot = myparams["Y_rotated"];
    // Convert to primary model parameters
    parentparams.setValue("M0", myparams["M0"]);
    parentparams.setValue("M12", myparams["M12"]);
    parentparams.setValue("A0", myparams["A0"]);
    parentparams.setValue("tanb", 0.5*(xrot+yrot));
    parentparams.setValue("sgnmu", 0.5*(xrot-yrot));
  }
#undef PARENT
#undef MODEL


// Make a second branch of the model tree, and connect it to the first branch using the INTERPRET_AS_X macro.

#define MODEL demo_B_ancestor
  START_MODEL
  DEFINEPARS(X, Y, Z)
#undef MODEL

#define MODEL demo_B
#define PARENT demo_B_ancestor
  START_MODEL
  DEFINEPARS(X, Y, Z)
  INTERPRET_AS_PARENT_FUNCTION(to_parent)
  INTERPRET_AS_X_FUNCTION(kevin_bacon,to_kevin_bacon)

  void MODEL_NAMESPACE::to_parent(const ModelParameters &myparams, ModelParameters &parentparams)
  {
      // Get the Pipes for the interpret-as-parent function
      USE_MODEL_PIPE(PARENT)
      logger()<<"Running interpret_as_parent calculations for demo_B -> demo_B_ancestor ..."<<EOM;     
      parentparams.setValue("X",myparams["X"]);
      parentparams.setValue("Y",2.0*myparams["Y"]);
      parentparams.setValue("Z",myparams["Z"]);
  }

  void MODEL_NAMESPACE::to_kevin_bacon(const ModelParameters &myparams, ModelParameters &kevin_bacon_params)
  {
      // Get the Pipes for the interpret-as-X function
      USE_MODEL_PIPE(kevin_bacon)
      logger()<<"Running interpret_as_X calculations for demo_B -> kevin_bacon ..."<<EOM;     
      kevin_bacon_params.setValue("M1",myparams["X"]);
      kevin_bacon_params.setValue("M2",myparams["Y"]);
      kevin_bacon_params.setValue("M3",myparams["Z"]);
      kevin_bacon_params.setValue("AU1",1.0);
      kevin_bacon_params.setValue("AU2",2.0);
      kevin_bacon_params.setValue("AU3",3.0);
  }
#undef PARENT
#undef MODEL


#define MODEL demo_B_subspace
#define PARENT demo_B
  START_MODEL
  DEFINEPARS(Y,Z)
  INTERPRET_AS_PARENT_FUNCTION(to_parent)

  void MODEL_NAMESPACE::to_parent(const ModelParameters &myparams, ModelParameters &parentparams)
  {
      // Get the Pipes for the interpret-as-parent function
      USE_MODEL_PIPE(PARENT)
      logger()<<"Running interpret_as_parent calculations for demo_B_subspace -> demo_B ..."<<EOM;     
      parentparams.setValue("X",1.0);
      parentparams.setValue("Y",myparams["Y"]);
      parentparams.setValue("Z",myparams["Z"]);
  }
#undef PARENT
#undef MODEL

*/

// Model demonstration the use of "ordinary" module functions directly in a model namespace
// (rather than putting them in some other module)
// Basically the generalisation of MAP_TO_CAPABILITY, just using the normal module function
// macros
// 
#define MODEL demo_CAP
  START_MODEL
  DEFINEPARS(a,b,c)

  #define CAPABILITY a_cap
  START_CAPABILITY

    #define FUNCTION get_a_cap
    START_FUNCTION(unsigned int)
    ALLOW_MODELS(demo_CAP)
    DEPENDENCY(xsection, double) // From ExampleBit_A
    // Other module-function macros not tested in model context
    // Please submit a bug report if they don't work for you! 
   #undef FUNCTION

  #undef CAPABILITY

  // The "module function" definition
  // Have to put it in the right namespace, and can't used MODEL_NAMESPACE macro unless
  // we change something in the START_FUNCTION macro to first declare the function in
  // the right namespace. So just used the below as the template for what the namespace
  // should be.
  namespace Gambit {
    namespace Models {
      namespace MODEL {
        void get_a_cap(unsigned int& result)
        {
            using namespace Pipes::get_a_cap;

            double xsec = *Dep::xsection; // Just for demonstration purposes
 
            logger()<<"Running 'get_a_cap' function in model-module 'demo_CAP'"<<EOM;     
          
            result = *Param.at("a") * xsec;
        }
      }
    }
  }

#undef MODEL

#endif /* defined(__demo_hpp__) */














