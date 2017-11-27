//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  ScannerBit interface function library for
///  running ScannerBit via an external interface,
///  (for example see pyScannerBit for a python
//   interface to these functions)
//
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ben Farmer
///          (ben.farmer@gmail.com)
///  \date 2017 Nov
///
///  *********************************************

#include <iostream>
#include "gambit/ScannerBit/ScannerBit_CAPI.h"
#include "gambit/ScannerBit/scannerbit.hpp" // Needed for symbols like
#include "gambit/ScannerBit/scan.hpp"
#include "gambit/ScannerBit/plugin_loader.hpp" // Needed for symbols like plugin_info
#include "gambit/Utils/yaml_parser_base.hpp"
#include "gambit/Utils/threadsafe_rng.hpp"
#include "gambit/Utils/mpiwrapper.hpp"
#include "gambit/Utils/signal_handling.hpp"
#include "gambit/Printers/printermanager.hpp"

using namespace Gambit;
using namespace Gambit::Scanner;

Printers::PrinterManager * printerInterface = NULL;

void hello_world()
{
   std::cout << "Hello world" << std::endl;
}

/// Likelihood contain class for wrapping user-supplied function pointers 
/// (to a 'main' function which evaluates a likelihood)
class CAPI_Likelihood_Container : public Scanner::Function_Base<double (std::unordered_map<std::string, double> &)>
{
  private:
    const user_funcptr my_user_func;

  public:
    /// Constructor
    CAPI_Likelihood_Container(const user_funcptr f) : my_user_func(f) {}

    /// Do the prior transformation and populate the parameter map
    void setParameters (const std::unordered_map<std::string, double> &) {/* nothing yet! */}

    /// Evaluate total likelihood function
    double main (std::unordered_map<std::string, double> &pars) 
    {
      double ret_val = my_user_func(pars);
      //(*this)->getPrinter().enable(); // Make sure printer is re-enabled (might have been disabled by invalid point error)
      // Output the transformed parameter values for this point
      unsigned long long int id = Gambit::Printers::get_point_id();
      int rank = getRank();
      for (std::unordered_map<std::string, double>::const_iterator it = pars.begin(); it != pars.end(); ++it)
      {
         getPrinter().print(it->second, it->first, rank, id);
      }
      return ret_val;
    }

};

/// As well as the likelihood container class, we also need a factory function for this likelihood
/// container, due to the way ScannerBit works.
registry
{
  typedef void* factory_type(const user_funcptr f); //Needs to match constructor of likelihood container
  reg_elem <factory_type> __scanner_factories__;
}
  
class CAPI_Likelihood_Container_Factory : public Scanner::Factory_Base
{
  private:
    const user_funcptr myf;
  public:
    CAPI_Likelihood_Container_Factory(const user_funcptr f) : myf(f) {}
    ~CAPI_Likelihood_Container_Factory() {}
    void * operator() (const str&/*purpose*/) const
    {
       // We don't use the purpose string for anything in this C API, so just ignore it.
       return __scanner_factories__["ScannerBit_C_API_Target_Function"](myf);
    }
};

#define LOAD_SCANNER_FUNCTION(tag, ...) REGISTER(__scanner_factories__, tag, __VA_ARGS__)
LOAD_SCANNER_FUNCTION(ScannerBit_C_API_Target_Function, CAPI_Likelihood_Container)

void run_test_scan(const char in_yaml_file[], const user_funcptr user_func)
{
    std::string yaml_file(in_yaml_file);

    signal(SIGTERM, sighandler_soft);
    signal(SIGINT,  sighandler_soft);
    signal(SIGUSR1, sighandler_soft);
    signal(SIGUSR2, sighandler_soft);

    // Default exit behaviour in cases where no exceptions are raised
    int return_value(EXIT_SUCCESS);

    #ifdef WITH_MPI
    bool allow_finalize(true);
    bool use_mpi_abort = true; // Set later via inifile value
    GMPI::Init();
    #endif

    { // Scope for MPI communicators
        #ifdef WITH_MPI
        // Create an MPI communicator group for use by error handlers
        GMPI::Comm errorComm;
        errorComm.dup(MPI_COMM_WORLD,"errorComm"); // duplicates the COMM_WORLD context
        const int ERROR_TAG=1;         // Tag for error messages
        errorComm.mytag = ERROR_TAG;
        signaldata().set_MPI_comm(&errorComm); // Provide a communicator for signal handling routines to use.
        // Create an MPI communicator group for ScannerBit to use
        GMPI::Comm scanComm;
        scanComm.dup(MPI_COMM_WORLD,"scanComm"); // duplicates the COMM_WORLD context
        Scanner::Plugins::plugin_info.initMPIdata(&scanComm);
        // MPI rank for use in error messages;
        int rank = scanComm.Get_rank();
        #else
        int rank = 0;
        #endif

        IniParser::Parser iniFile;
        iniFile.readFile(yaml_file);

        // Initialise the random number generator, letting the RNG class choose its own default.
        Random::create_rng_engine(iniFile.getValueOrDef<std::string>("default", "rng"));

        // Set up the printer (redirection of scan output)
        bool resume = false;
        Printers::PrinterManager printerManager(iniFile.getPrinterNode(),resume);
        printerInterface = &printerManager;

        //Make scanner yaml node
        YAML::Node scanner_node;
        scanner_node["Scanner"] = iniFile.getScannerNode();
        scanner_node["Parameters"] = iniFile.getParametersNode();
        scanner_node["Priors"] = iniFile.getPriorsNode();

        //Construct likelihood container to wrap user-supplied likelihood function
        CAPI_Likelihood_Container_Factory likelihood(user_func);

        //Create the master scan manager
        Scanner::Scan_Manager scan(scanner_node, &printerManager, &likelihood); 

        scan.Run();

        if (rank == 0) std::cout << "ScannerBit has finished successfully!" << std::endl;
    } // End scope for MPI communicators
    #ifdef WITH_MPI
    if (allow_finalize) GMPI::Finalize();
    #endif
}
