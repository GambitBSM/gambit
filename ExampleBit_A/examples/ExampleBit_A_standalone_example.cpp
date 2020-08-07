//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Example of GAMBIT ExampleBit_A standalone
///  main program.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///  \date 2014 Jan, Feb
///
///  \author Ben Farmer
///  \date 2014 Dec
///
///  *********************************************

// Always required in any standalone module main file
#include "gambit/Elements/standalone_module.hpp"
#include "gambit/ExampleBit_A/ExampleBit_A_rollcall.hpp"

// Only needed here
#include "gambit/Utils/util_functions.hpp"

using namespace ExampleBit_A::Functown;     // Functors wrapping the module's actual module functions
using namespace BackendIniBit::Functown;    // Functors wrapping the backend initialisation functions

// Register ad-hoc module functions for use; as many or as few models can be given as desired.
// Full declaration as per regular rollcall headers such as ExampleBit_A_rollcall.hpp is also allowed.
//QUICK_FUNCTION(ExampleBit_A, xsection, NEW_CAPABILITY, local_xsection, double, (NUHM1))
QUICK_FUNCTION(ExampleBit_A, xsection, OLD_CAPABILITY, local_xsection, double, (NUHM1))

// Ad-hoc functions for filling dependencies that cannot or should not otherwise be filled from inside ExampleBit_A.
namespace Gambit
{
  namespace ExampleBit_A
  {
    void local_xsection(double &result) { result = *Pipes::local_xsection::Param["M0"];}
  }
}


int main()
{

  try
  {

    std::cout << std::endl << "Starting ExampleBit_A standalone example" << std::endl;
    std::cout << "----------" << std::endl;

    //Initialise logging (just comment out if you want no logfiles)
    initialise_standalone_logs("runs/ExampleBit_A_standalone/logs/");

    // Change the fatality of different errors and warnings from the defaults, if desired.
    model_warning().set_fatal(true);
    ExampleBit_A::ExampleBit_A_error().set_fatal(true);

    // Initialise the random number generator.
    Random::create_rng_engine("default");

    // Test message (note: we are not actually "inside" ExampleBit_A here, so the log message will not receive an 'ExampleBit_A' tag).
    logger()<<"Running ExampleBit_A standalone example"<<LogTags::info<<EOM;

    // Check that required backends are present
    if (not Backends::backendInfo().works["LibFortran1.0"]) backend_error().raise(LOCAL_INFO, "LibFortran 1.0 is missing!");

    // Retrieve a raw pointer to the parameter set of each primary model to be scanned, for manually setting parameter values
    ModelParameters* CMSSM_primary_parameters = Models::CMSSM::Functown::primary_parameters.getcontentsPtr();

    // Resolve backend requirements 'by hand'.  Must be done before dependencies are resolved.
    function_pointer_retriever.resolveBackendReq(&Backends::LibFortran_1_0::Functown::externalFunction);

    // Notify any module functions that care of the model(s) being scanned.
    // 'Care' means where they depend on model parameters directly, or have dependencies or backend requirements that are
    // conditional on the model being analysed.
    Models::CMSSM::Functown::NUHM1_parameters.notifyOfModel("CMSSM");
    local_xsection.notifyOfModel("CMSSM");

    // Resolve dependencies 'by hand'.  The ordering is unimportant, but if you want to set parameters from this program,
    // then *something* in the chain must have one of its dependencies filled by Models::PRI::Functown::primary_parameters,
    // where PRI is a primary model.
    Models::CMSSM::Functown::NUHM1_parameters.resolveDependency(&Models::CMSSM::Functown::primary_parameters);
    local_xsection.resolveDependency(&Models::CMSSM::Functown::NUHM1_parameters);
    nevents_pred.resolveDependency(&local_xsection);
    nevents_pred_rounded.resolveDependency(&nevents_pred);

    // Resolve dependencies of nested functions on each other
    exampleCut.resolveDependency(&exampleEventGen);
    eventAccumulator.resolveDependency(&exampleCut);

    // Set loop manager for nested functions
    exampleEventGen.resolveLoopManager(&eventLoopManager);
    exampleCut.resolveLoopManager(&eventLoopManager);
    eventAccumulator.resolveLoopManager(&eventLoopManager);

    // Set up the mini dependency tree to be run by EventLoopManager
    std::vector<functor*> nested_functions = initVector<functor*>(&exampleEventGen, &exampleCut, &eventAccumulator);

    // Notify the loop manager of that tree
    eventLoopManager.setNestedList(nested_functions);

    // Double-check which backend requirements have been filled with what
    std::cout << std::endl << "My function function_pointer_retriever has had its backend requirement on externalFunction filled by:" << std::endl;
    std::cout << ExampleBit_A::Pipes::function_pointer_retriever::BEreq::externalFunction.origin() << "::";
    std::cout << ExampleBit_A::Pipes::function_pointer_retriever::BEreq::externalFunction.name() << std::endl;

    // Double-check which dependencies have been filled with what (not every combo is done)
    std::cout << std::endl << "My function nevents_pred_rounded has had its dependency on nevents filled by:" << endl;
    std::cout << ExampleBit_A::Pipes::nevents_pred_rounded::Dep::nevents.origin() << "::";
    std::cout << ExampleBit_A::Pipes::nevents_pred_rounded::Dep::nevents.name() << std::endl;
    std::cout << std::endl << "My function nevents_pred has had its dependency on xsection filled by:" << endl;
    std::cout << ExampleBit_A::Pipes::nevents_pred::Dep::xsection.origin() << "::";
    std::cout << ExampleBit_A::Pipes::nevents_pred::Dep::xsection.name() << std::endl;
    std::cout << std::endl << "My function local_xsection has had its dependency on MSSM parameters filled by:" << std::endl;
    std::cout << ExampleBit_A::Pipes::local_xsection::Dep::NUHM1_parameters.origin() << "::";
    std::cout << ExampleBit_A::Pipes::local_xsection::Dep::NUHM1_parameters.name() << std::endl;
    std::cout << std::endl << "The model function CMSSM::Functown::NUHM1_parameters has had its dependency on CMSSM parameters filled by:" << endl;
    std::cout << Models::CMSSM::Pipes::NUHM1_parameters::Dep::CMSSM_parameters.origin() << "::";
    std::cout << Models::CMSSM::Pipes::NUHM1_parameters::Dep::CMSSM_parameters.name() << std::endl << std::endl;
    std::cout << std::endl << "My function exampleCut has had its dependency on event filled by:" << std::endl;
    std::cout << ExampleBit_A::Pipes::exampleCut::Dep::event.origin() << "::";
    std::cout << ExampleBit_A::Pipes::exampleCut::Dep::event.name() << std::endl;

    // Set some module function options
    nevents_pred_rounded.setOption<double>("probability_of_validity", 0.8);

    // Start a loop over some low-E points in the primary model parameter space
    std::cout << "Starting model scan..." << std::endl << std::endl;
    for (int i = 0; i<5; i++)
    {

      try
      {

        // Give the primary model parameters
        CMSSM_primary_parameters->setValue("M0",i*1.);
        CMSSM_primary_parameters->setValue("A0",i*5.);
        CMSSM_primary_parameters->setValue("M12",i*2.);
        CMSSM_primary_parameters->setValue("TanBeta",i*10.);
        CMSSM_primary_parameters->setValue("SignMu",1.);

        // Call the initialisation functions for all backends that are in use.
        LibFortran_1_0_init.reset_and_calculate();

        // Call the actual module functions, taking care to calculate in the order implied by how the dependencies have been filled;
        // i.e. calculate quantities that other quantities depend on first.
        function_pointer_retriever.reset_and_calculate(); // (These two don't actually matter for the rest of the dependency chain,
        eventLoopManager.reset_and_calculate();           // so could go anywhere.)
        Models::CMSSM::Functown::NUHM1_parameters.reset_and_calculate();
        local_xsection.reset_and_calculate();
        nevents_pred.reset_and_calculate();
        nevents_pred_rounded.reset_and_calculate();

        // Retrieve the (cached) results of the module functions.  The argument is the thread index; everything except '0' is just temporary data.
        double r1 = nevents_pred(0);
        int r2 = nevents_pred_rounded(0);
        std::cout << std::endl << "Retrieved results: " << r1 << ", " << r2 << std::endl << std::endl;

      }

      // Be sure to do something sensible in cases where the point was invalidated by one of functions.
      catch (Gambit::invalid_point_exception& e)
      {
        std::cout << std::endl << "That was a bad point.  Oh well, try again." << std::endl << std::endl;
      }

    }

    std::cout << "ExampleBit_A standalone example has finished successfully." << std::endl << std::endl;

  }

  catch (std::exception& e)
  {
    std::cout << "ExampleBit_A standalone example has exited with fatal exception: " << e.what() << std::endl;
  }

  return 0;

}
