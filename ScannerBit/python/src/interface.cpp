#include <csignal>

#include "gambit/Logs/logger.hpp"
#include "gambit/Logs/logmaster.hpp"
#include "gambit/Utils/signal_helpers.hpp"
#include "gambit/Utils/signal_handling.hpp"
#include "gambit/Utils/static_members.hpp"
#include "gambit/Utils/stream_overloads.hpp"
#include "gambit/Utils/yaml_parser_base.hpp"
#include "gambit/Logs/logger.hpp"
#include "gambit/Printers/printermanager.hpp"
#include "gambit/ScannerBit/scannerbit.hpp"
#include "gambit/ScannerBit/priors_rollcall.hpp"
#include "gambit/Utils/mpiwrapper.hpp"
#include "gambit/Utils/yaml_parser_base.hpp"
#include "gambit/ScannerBit/scan.hpp"
#include "interface.hpp"

using namespace Gambit;
using namespace LogTags;



namespace Gambit
{
    
    namespace Scanner
    {

        namespace Python
        {
            
            class IniFileParser : public Gambit::IniParser::Parser
            {
            public:
                void inputNode(const YAML::Node &node)
                {
                    this->basicParse(node, "pyScannerBit.yaml");
                }
            };
            
            void do_cleanup()
            {
                Gambit::Scanner::Plugins::plugin_info.dump(); // Also calls printer finalise() routine
            }
                
            static void terminator()
            {
                std::cout << std::endl << "Gambit has encountered an uncaught error during initialisation." << std::endl;
                std::cout << std::endl << "Check the output logs for details." << std::endl;
                std::cout << std::endl << "(Check your yaml file if you can't recall where the logs are.)" << std::endl << std::endl;

                std::exception_ptr eptr = std::current_exception();
                try
                {
                    std::rethrow_exception(eptr);
                }
                catch (const std::exception &e)
                {
                    std::cout << "what(): " << e.what() << std::endl;
                }
                catch (...)
                {
                    std::cout << "Exception not derived from std::exception." << std::endl;
                }
                exit(1);
            }

            scan_interface::scan_interface(bool 
                                            #ifdef WITH_MPI
                                                initmpi
                                            #endif
                                          )
              #ifdef WITH_MPI 
              : init_mpi(initmpi)
              #endif
            {
                #ifdef WITH_MPI
                    if (init_mpi)
                    {
                        //bool allow_finalize(true);
                        GMPI::Init();
                    }
                #endif
            }
                
            std::shared_ptr<printer_wrapper> scan_interface::get_printer()
            {
                return std::shared_ptr<printer_wrapper>(new printer_wrapper(this), [](printer_wrapper *in){delete in;});
            }
            
            /// Main scan execution program
            int scan_interface::run_scan(Gambit::IniParser::Parser &iniFile, const Gambit::Scanner::Factory_Base *factory, Gambit::Priors::BasePrior *user_prior, bool resume)
            {
                #ifdef WITH_MPI
                bool use_mpi_abort = true; // Set later via inifile value
                #endif
                std::set_terminate(terminator);
                //rm: cout << std::setprecision(Core().get_outprec());

                // Default exit behaviour in cases where no exceptions are raised
                int return_value(EXIT_SUCCESS);

                #ifdef WITH_MPI
                bool allow_finalize(true);
                //GMPI::Init();
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
                        //rm: const str filename = Core().run_diagnostic(argc,argv);

                        if (rank == 0)
                        {
                            cout << endl << "Starting ScannerBit" << endl;
                            cout << "----------" << endl;
                            //rm: if(Core().found_inifile) cout << "YAML file: "<< filename << endl;
                        }

                        //rm: std::vector<std::string> arguments(argv, argv + argc);
                        //rm: logger() << core << "Command invoked: ";
                        //rm: for(int i=0;i<argc;i++){ logger() << arguments[i] << " "; }
                        //rm: logger() << endl;
                        //rm: logger() << core << "Starting ScannerBit" << EOM;
                        //rm: if( Core().resume ) logger() << core << "Attempting to resume scan..." << EOM;
                        //rm: logger() << core << "Registered module functors [Core().getModuleFunctors().size()]: ";
                        //rm: logger() << Core().getModuleFunctors().size() << endl;
                        //rm: logger() << "Registered backend functors [Core().getBackendFunctors().size()]: ";
                        //rm: logger() << Core().getBackendFunctors().size() << EOM;

                        // Read YAML file, which also initialises the logger.
                        //rm: IniParser::IniFile iniFile;
                        //rm: iniFile.readFile(filename);

                        // Check if user wants to disable use of MPI_Abort (since it does not work correctly in all MPI implementations)
                        #ifdef WITH_MPI
                            use_mpi_abort = iniFile.getValueOrDef<bool>(true, "use_mpi_abort");
                        #endif

                        // Initialise the random number generator, letting the RNG class choose its own defaults.
                        Options rng(iniFile.getValueOrDef<YAML::Node>(YAML::Node(), "rng"));
                        std::string generator = rng.getValueOrDef<std::string>("default", "generator");
                        int seed = rng.getValueOrDef<int>(-1, "seed");
                        Random::create_rng_engine(generator, seed);

                        // Determine selected model(s)
                        //rm: std::set<str> selectedmodels = iniFile.getModelNames();

                        // Activate "primary" model functors
                        //rm: Core().registerActiveModelFunctors( Models::ModelDB().getPrimaryModelFunctorsToActivate( selectedmodels, Core().getPrimaryModelFunctors() ) );

                        // Deactivate module functions reliant on classes from missing backends
                        //rm: Core().accountForMissingClasses();

                        // Set up the printer manager for redirection of scan output.
                        Printers::PrinterManager printerManager(iniFile.getPrinterNode(),resume);
                        global_printer = &printerManager;
                        // Set up dependency resolver
                        //rm: DRes::DependencyResolver dependencyResolver(Core(), Models::ModelDB(), iniFile, Utils::typeEquivalencies(), *(printerManager.printerptr));

                        // Log module function info
                        //rm: dependencyResolver.printFunctorList();

                        // Do the dependency resolution
                        //rm: if (rank == 0) cout << "Resolving dependencies and backend requirements.  Hang tight..." << endl;
                        //rm: dependencyResolver.doResolution();
                        //rm: if (rank == 0) cout << "...done!" << endl;

                        // Check that all requested models are used for at least one computation
                        //rm: Models::ModelDB().checkPrimaryModelFunctorUsage(Core().getActiveModelFunctors());

                        // Report the proposed (output) functor evaluation order
                        //rm: dependencyResolver.printFunctorEvalOrder(Core().show_runorder);

                        // If true, bail out (just wanted the run order, not a scan); otherwise, keep going.
                        //rm: if (not Core().show_runorder)
                        //rm: {
                            //Define the likelihood container object for the scanner
                        //rm:  Likelihood_Container_Factory factory(Core(), dependencyResolver, iniFile, *(printerManager.printerptr)
                        //rm:    #ifdef WITH_MPI
                        //rm:      , errorComm
                        //rm:    #endif
                        //rm:  );

                        //Make scanner yaml node
                        YAML::Node scanner_node;
                        scanner_node["Scanner"] = iniFile.getScannerNode();
                        scanner_node["Parameters"] = iniFile.getParametersNode();
                        scanner_node["Priors"] = iniFile.getPriorsNode();

                        //Create the master scan manager
                        Scanner::Scan_Manager scan(scanner_node, &printerManager, factory, user_prior);

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
                            logger() << "ScannerBit has performed a controlled early shutdown due to early termination of the scanner plugin." << EOM;
                            if (rank == 0) cout << "ScannerBit has performed a controlled early shutdown." << endl << endl;
                        }
                        else
                        {
                            //Scan is done; inform signal handlers
                            signaldata().set_shutdown_begun();
                            logger() << "ScannerBit run completed successfully." << EOM;
                            if (rank == 0) cout << endl << "ScannerBit has finished successfully!" << endl << endl;
                        }
                    //rm: }

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
                        ss << "ScannerBit has performed a controlled early shutdown." << endl;
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
                            ss << "ScannerBit has shutdown (but could not finalise or abort MPI)." << endl;
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
                            ss << "ScannerBit has shutdown due to an error on another process." << endl;
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
                            cerr << "ScannerBit has exited with fatal exception: " << e.what() << endl;
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
                        cout << "ScannerBit has exited with a fatal and uncaught exception " << endl;
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

                    #ifdef WITH_MPI 
                    if(rank == 0 and init_mpi) cout << "Calling MPI_Finalize..." << endl; // Debug
                    #endif
                } // End main scope; want to destruct all communicators before MPI_Finalize() is called

                #ifdef WITH_MPI
                if (init_mpi and allow_finalize) GMPI::Finalize();
                #endif

                return return_value;

            }
        
            int scan_interface::run_scan_node(YAML::Node *node, const Gambit::Scanner::Factory_Base *factory, Gambit::Priors::BasePrior *user_prior, bool resume)
            {
                IniFileParser iniFile;
                iniFile.inputNode(*node);
                
                return run_scan(iniFile, factory, user_prior, resume);
            }
                
                
            int scan_interface::run_scan_str(std::string *filename, const Gambit::Scanner::Factory_Base *factory, Gambit::Priors::BasePrior *user_prior, bool resume)
            {
                IniFileParser iniFile;
                iniFile.readFile(*filename);
                
                return run_scan(iniFile, factory, user_prior, resume);
            }
            
            void printer_wrapper::aux_printer(const std::string &key, const double &value)                         
            {                                                                                                               
                using Gambit::Printers::get_aux_param_id;                                                                  
                Gambit::Scanner::printer *printer = scanner->get_printer_manager().get_stream();                                             
                printer->print(value, key, get_aux_param_id(key), printer->getRank(), Gambit::Printers::get_point_id());
            }
            
            void printer_wrapper::main_printer(const std::string &key, const double &value)                         
            {                                                                                                               
                using Gambit::Printers::get_main_param_id;                                                                  
                Gambit::Scanner::printer *printer = scanner->get_printer_manager().get_stream();                                             
                printer->print(value, key, get_main_param_id(key), printer->getRank(), Gambit::Printers::get_point_id());
            }
            
            void printer_wrapper::main_printer(std::unordered_map<std::string, double> &key_map)                         
            {                                                                                                               
                using Gambit::Printers::get_main_param_id;                                                                  
                Gambit::Scanner::printer *printer = scanner->get_printer_manager().get_stream();                                             
                for (auto it = key_map.begin(), end = key_map.end(); it != end; ++it)                                 
                {                                                                                                           
                    printer->print(it->second, it->first, get_main_param_id(it->first), printer->getRank(), Gambit::Printers::get_point_id());          
                }                                                                                                           
            }
                
        }
        
    }
    
}
