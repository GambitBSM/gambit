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

void run_test_scan()
{
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

        // Hardcoded YAML ini file for testing 
        std::string filename("/net/archive/groups/plgggambit/ben/repos/gambit/yaml_files/ScannerBit.yaml");

        IniParser::Parser iniFile;
        iniFile.readFile(filename);

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

        //Create the master scan manager
        Scanner::Scan_Manager scan(scanner_node, &printerManager, 0); 

        scan.Run();

        if (rank == 0) std::cout << "ScannerBit has finished successfully!" << std::endl;
    } // End scope for MPI communicators
    #ifdef WITH_MPI
    if (allow_finalize) GMPI::Finalize();
    #endif
}
