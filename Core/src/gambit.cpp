//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  GAMBIT executable.
///
///  *********************************************
///
///  Authors:
///
///  \author The GAMBIT Collaboration
///  \date 2012 Oct onwards
///
///  *********************************************

#include <csignal>

#include "gambit/Core/gambit.hpp"
#include "gambit/Utils/mpiwrapper.hpp"


using namespace Gambit;
using namespace LogTags;

#ifdef WITH_MPI
  bool use_mpi_abort = true; // Set later via inifile value
#endif

/// Cleanup function
void do_cleanup()
{
  Gambit::Scanner::Plugins::plugin_info.dump(); // Also calls printer finalise() routine
}


/// Main GAMBIT program
int main(int argc, char* argv[])
{
  std::set_terminate(terminator);
  cout << std::setprecision(Core().get_outprec());

  // Default exit behaviour in cases where no exceptions are raised
  int return_value(EXIT_SUCCESS);

  #ifdef WITH_MPI
    bool allow_finalize(true);
    GMPI::Init();
  #endif

  /// Idea by Tom Fogal, for optionally preventing execution of code until debugger allows it
  /// Source: http://www.sci.utah.edu/~tfogal/academic/Fogal-ParallelDebugging.pdf
  #ifdef WITH_MPI
  {
     GMPI::Comm temp_comm;
     int rank = temp_comm.Get_rank();
     if( getenv("GAMBIT_MPI_DEBUG") != NULL )
     {
        fprintf(stderr, "pid %li (rank %i) waiting for debugger \n", (long)getpid(), rank);
        if( rank==0 )
        {
           volatile int i = 0;
           while(i == 0) { /* change ’i’ in the debugger */ }
           fprintf(stderr, "Variable 'i' changed externally; resuming execution! \n");
        }
     }
     temp_comm.Barrier();
     // All processes wait at the barrier until process 0 is "released" by debugger.
     // If try/catch etc needs to be set for other processes, do those first before
     // releasing process zero.
  }
  #endif

  { // Scope to ensure that all MPI communicators get destroyed before Finalize is called.

    // Set up signal handling function
    // We attempt a clean shutdown on any of these signals
    signal(SIGTERM, sighandler_soft);
    signal(SIGINT,  sighandler_soft);
    signal(SIGUSR1, sighandler_soft);
    signal(SIGUSR2, sighandler_soft);

    #ifdef WITH_MPI
      /// Create an MPI communicator group for use by error handlers
      GMPI::Comm errorComm;
      errorComm.dup(MPI_COMM_WORLD,"errorComm"); // duplicates the COMM_WORLD context
      const int ERROR_TAG=1;         // Tag for error messages
      errorComm.mytag = ERROR_TAG;
      signaldata().set_MPI_comm(&errorComm); // Provide a communicator for signal handling routines to use.
      /// Create an MPI communicator group for ScannerBit to use
      GMPI::Comm scanComm;
      scanComm.dup(MPI_COMM_WORLD,"scanComm"); // duplicates the COMM_WORLD context
      Scanner::Plugins::plugin_info.initMPIdata(&scanComm);
      /// MPI rank for use in error messages;
      int rank = scanComm.Get_rank();
    #else
      int rank = 0;
    #endif

    try
    {
      // Parse command line arguments, launching into the appropriate diagnostic mode
      // if the argument passed warrants it. Otherwise just get the filename.
      const str filename = Core().run_diagnostic(argc,argv);

      if (rank == 0)
      {
        cout << endl << "Starting GAMBIT" << endl;
        cout << "----------" << endl;
        if(Core().found_inifile) cout << "YAML file: "<< filename << endl;
      }

      std::vector<std::string> arguments(argv, argv + argc);
      logger() << core << "Command invoked: ";
      for(int i=0;i<argc;i++){ logger() << arguments[i] << " "; }
      logger() << endl;
      logger() << core << "Starting GAMBIT" << EOM;
      if( Core().resume ) logger() << core << "Attempting to resume scan..." << EOM;
      logger() << core << "Registered module functors [Core().getModuleFunctors().size()]: ";
      logger() << Core().getModuleFunctors().size() << endl;
      logger() << "Registered backend functors [Core().getBackendFunctors().size()]: ";
      logger() << Core().getBackendFunctors().size() << EOM;

      // Read YAML file, which also initialises the logger.
      IniParser::IniFile iniFile;
      iniFile.readFile(filename);

      // Check if user wants to disable use of MPI_Abort (since it does not work correctly in all MPI implementations)
      #ifdef WITH_MPI
        use_mpi_abort = iniFile.getValueOrDef<bool>(true, "use_mpi_abort");
      #endif

      // Initialise the random number generator, letting the RNG class choose its own default.
      Random::create_rng_engine(iniFile.getValueOrDef<str>("default", "rng"));

      // Determine selected model(s)
      std::set<str> selectedmodels = iniFile.getModelNames();

      // Activate "primary" model functors
      Core().registerActiveModelFunctors( Models::ModelDB().getPrimaryModelFunctorsToActivate( selectedmodels, Core().getPrimaryModelFunctors() ) );

      // Deactivate module functions reliant on classes from missing backends
      Core().accountForMissingClasses();

      // Set up the printer manager for redirection of scan output.
      Printers::PrinterManager printerManager(iniFile.getPrinterNode(),Core().resume);

      // Set up dependency resolver
      DRes::DependencyResolver dependencyResolver(Core(), Models::ModelDB(), iniFile, Utils::typeEquivalencies(), *(printerManager.printerptr));

      // Log module function info
      dependencyResolver.printFunctorList();

      // Do the dependency resolution
      if (rank == 0) cout << "Resolving dependencies and backend requirements.  Hang tight..." << endl;
      dependencyResolver.doResolution();
      if (rank == 0) cout << "...done!" << endl;

      // Check that all requested models are used for at least one computation
      Models::ModelDB().checkPrimaryModelFunctorUsage(Core().getActiveModelFunctors());

      // Report the proposed (output) functor evaluation order
      dependencyResolver.printFunctorEvalOrder(Core().show_runorder);

      // If true, bail out (just wanted the run order, not a scan); otherwise, keep going.
      if (not Core().show_runorder)
      {
        //Define the likelihood container object for the scanner
        Likelihood_Container_Factory factory(Core(), dependencyResolver, iniFile, *(printerManager.printerptr)
          #ifdef WITH_MPI
            , errorComm
          #endif
        );

        //Make scanner yaml node
        YAML::Node scanner_node;
        scanner_node["Scanner"] = iniFile.getScannerNode();
        scanner_node["Parameters"] = iniFile.getParametersNode();
        scanner_node["Priors"] = iniFile.getPriorsNode();

        //Create the master scan manager
        Scanner::Scan_Manager scan(scanner_node, &printerManager, &factory);

        // Set cleanup function to call during premature shutdown
        signaldata().set_cleanup(&do_cleanup);

        // For extra speed with fast likelihood evaluations, disable the logs while the scans runs
        bool disable_logs_during_scan = iniFile.getValueOrDef<bool>(false, "disable_logs_during_scan");
        if(disable_logs_during_scan) logger().disable();
        //Do the scan!
        logger() << core << "Starting scan." << EOM;
        if (rank == 0) std::cerr << "Starting scan." << std::endl;
        scan.Run(); // Note: the likelihood container will unblock signals when it is safe to receive them.
        logger().enable(); // Turn logs back on (in case they were disabled for speed)
        // Check why we have exited the scanner; scan may have been terminated early by a signal.
        // We assume here that because the scanner has exited that it has already down whatever
        // cleanup it requires, including finalising the printers, i.e. the 'do_cleanup()' function will NOT run.
        if(signaldata().shutdown_begun())
        {
           logger() << "GAMBIT has performed a controlled early shutdown due to early termination of the scanner plugin." << EOM;
           if (rank == 0) cout << "GAMBIT has performed a controlled early shutdown." << endl << endl;
        }
        else
        {
           //Scan is done; inform signal handlers
           signaldata().set_shutdown_begun();
           logger() << "GAMBIT run completed successfully." << EOM;
           if (rank == 0) cout << endl << "GAMBIT has finished successfully!" << endl << endl;
        }
      }

    }

    /// Special catch block for silent shutdown
    /// This exception is designed to be thrown during diagnostic mode
    catch (const SilentShutdownException& e)
    {
      // No need to do anything, just let program shut down normally from here
    }

    /// Special catch block for controlled shutdown
    /// This exception should only be thrown if it is safe to call MPI_Finalise,
    /// as this will occur once we leave the catch block.
    catch (const SoftShutdownException& e)
    {
      if (not logger().disabled())
      {
        std::ostringstream ss;
        ss << e.what() << endl;
        ss << "GAMBIT has performed a controlled early shutdown." << endl;
        if(rank == 0) cout << ss.str();
        logger() << ss.str() << signaldata().display_received_signals() << EOM;
      }
      // Let program shutdown normally from here
    }

    /// Special catch block for hard shutdown
    /// No MPI_Finalise called, nor MPI_Abort. Should only be triggered when all
    /// processes are supposed to be trying to shut themselves down quickly, for
    /// example if synchronising for soft shutdown fails.
    catch (const HardShutdownException& e)
    {
      if (not logger().disabled())
      {
        std::ostringstream ss;
        ss << e.what() << endl;
        ss << "GAMBIT has shutdown (but could not finalise or abort MPI)." << endl;
        if(rank == 0) cout << ss.str();
        logger() << ss.str() << signaldata().display_received_signals() << EOM;
      }
      return EXIT_SUCCESS;
    }

    /// Shut down due receipt of MPI emergency shutdown message
    catch (const MPIShutdownException& e)
    {
      if (not logger().disabled())
      {
        std::ostringstream ss;
        ss << e.what() << endl;
        ss << "GAMBIT has shutdown due to an error on another process." << endl;
        if(rank == 0) cout << ss.str();
        logger() << ss.str() << EOM;
        #ifdef WITH_MPI
          signaldata().discard_excess_shutdown_messages();
          allow_finalize = GMPI::PrepareForFinalizeWithTimeout(use_mpi_abort);
        #endif
      }
      return_value = EXIT_FAILURE;
    }

    catch (const std::exception& e)
    {
      if (not logger().disabled())
      {
        cerr << endl << " \033[00;31;1mFATAL ERROR\033[00m" << endl << endl;
        cerr << "GAMBIT has exited with fatal exception: " << e.what() << endl;
      }
      #ifdef WITH_MPI
        signaldata().broadcast_shutdown_signal();
        signaldata().discard_excess_shutdown_messages();
        allow_finalize = GMPI::PrepareForFinalizeWithTimeout(use_mpi_abort);
      #endif
      return_value = EXIT_FAILURE;
    }

    catch (str& e)
    {
      cout << endl << " \033[00;31;1mFATAL ERROR\033[00m" << endl << endl;
      cout << "GAMBIT has exited with a fatal and uncaught exception " << endl;
      cout << "thrown from a backend code.  Due to poor code design in " << e << endl;
      cout << "the backend, the exception has been thrown as a string. " << endl;
      cout << "If you are the author of the backend, please throw only " << endl;
      cout << "exceptions that inherit from std::exception.  Error string: " << endl;
      cout << e << endl;
      #ifdef WITH_MPI
        signaldata().broadcast_shutdown_signal();
        signaldata().discard_excess_shutdown_messages();
        allow_finalize = GMPI::PrepareForFinalizeWithTimeout(use_mpi_abort);
      #endif
      return_value = EXIT_FAILURE;
    }

    #ifdef WITH_MPI
      if (signaldata().shutdown_begun()) signaldata().discard_excess_shutdown_messages();
      // If all processes receive a POSIX signal to shutdown there might be many of these
      // (e.g. says 1000 processes all independently get a POSIX signal to shut down;
      // they will each broadcast this command via MPI to all other processes, i.e.
      // 1000*1000 messages will be sent. Could be slow.
    #endif

    if(rank == 0) cout << "Calling MPI_Finalize..." << endl; // Debug
  } // End main scope; want to destruct all communicators before MPI_Finalize() is called

  #ifdef WITH_MPI
    if (allow_finalize) GMPI::Finalize();
  #endif

  return return_value;

}
