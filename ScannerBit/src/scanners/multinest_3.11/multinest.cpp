//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  ScannerBit interface to Multinest 3.11
///
///  *********************************************
///
///  Authors (add name and date if you modify):
//
///  \author Ben Farmer
///          (ben.farmer@gmail.com)
///  \date October 2013 - Aug 2016
///
///  *********************************************

#include <vector>
#include <string>
#include <cmath>
#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <iomanip>  // For debugging only

#include "gambit/ScannerBit/scanner_plugin.hpp"
#include "gambit/ScannerBit/scanners/multinest/multinest.hpp"
#include "gambit/Utils/yaml_options.hpp"
#include "gambit/Utils/util_functions.hpp"


namespace Gambit
{
   namespace MultiNest
   {
      /// Global pointer to loglikelihood wrapper object, for use in the MultiNest callback functions
      LogLikeWrapper *global_loglike_object;
   }
}

/// Typedef for the ScannerBit pointer to the external loglikelihood function
typedef Gambit::Scanner::like_ptr scanPtr;


/// =================================================
/// Interface to ScannerBit
/// =================================================

scanner_plugin(multinest, version(3, 11))
{
   // An error is thrown if any of the following entries are not present in the inifile (none absolutely required for MultiNest).
   reqd_inifile_entries();

   // Tell cmake system to search known paths for these libraries; any not found must be specified in config/scanner_locations.yaml.
   reqd_libraries("nest3");

   // Pointer to the (log)likelihood function
   scanPtr LogLike;

   /// The constructor to run when the MultiNest plugin is loaded.
   plugin_constructor
   {
      // Retrieve the external likelihood calculator
      LogLike = get_purpose(get_inifile_value<std::string>("like"));
      if (LogLike->getRank() == 0) std::cout << "Loading MultiNest nested sampling plugin for ScannerBit." << std::endl;
   }

   /// The main routine to run for the MultiNest scanner.
   int plugin_main (void)
   {
      /// ************
      /// TODO: Replace with some wrapper? Maybe not, this is already pretty straightforward,
      /// though perhaps a little counterintuitive that the printer is the place to get this
      /// information.
      bool resume_mode = get_printer().resume_mode();
      /// ************

      // Retrieve the dimensionality of the scan.
      int ma = get_dimension();

      // Retrieve the global option specifying the minimum interesting likelihood
      double gl0 = get_inifile_value<double>("likelihood: model_invalid_for_lnlike_below");
      // Retrieve the global option specifying the likelihood offset to use
      double offset = get_inifile_value<double>("likelihood: lnlike_offset", 0.);
      // Make sure the likleihood functor knows to apply the offset internally in ScannerBit
      LogLike->setPurposeOffset(offset);
      // Offset the minimum interesting likelihood by the offset
      gl0 = gl0 + offset;

      // MultiNest algorithm options.
      int IS (get_inifile_value<bool>("IS", true) );            // do Nested Importance Sampling?
      int mmodal (get_inifile_value<bool>("mmodal", true) );    // do mode separation?
      int ceff (get_inifile_value<bool>("ceff", false) );       // run in constant efficiency mode?
      int nlive (get_inifile_value<int>("nlive", 1000) );       // number of live points
      double efr (get_inifile_value<double>("efr", 0.8) );      // set the required efficiency
      double tol (get_inifile_value<double>("tol", 0.5) );      // tol, defines the stopping criteria
      int ndims = ma;                                           // dimensionality (no. of free parameters)
      int nPar = ma+2;                                          // Total no. of parameters including free & derived; +2 == {point ID code, MPI rank}
      int nClsPar (get_inifile_value<int>("nClsPar",std::min(ma,4))); // No. of parameters to do mode separation on; don't use more than 4
      int updInt (get_inifile_value<int>("updInt", 1000) );     // after how many iterations feedback is required & the output files should be updated (*10 for dumper)
      double Ztol (get_inifile_value<double>("Ztol", -1E90) );  // all the modes with logZ < Ztol are ignored
      int maxModes (get_inifile_value<int>("maxModes", 100) );  // expected max no. of modes (used only for memory allocation)
      int seed (get_inifile_value<int>("seed", -1) );           // random no. generator seed, if < 0 then take the seed from system clock
      int fb (get_inifile_value<bool>("fb", true) );            // need feedback on standard output?
      int resume ( resume_mode );                               // resume from a previous job?
      int outfile (get_inifile_value<bool>("outfile", true) );  // write output files?
      double ln0 (get_inifile_value<double>("logZero",0.9999*gl0)); // points with loglike < logZero will be ignored by MultiNest
      int maxiter (get_inifile_value<int>("maxiter", 0) );      // Max no. of iterations, a non-positive value means infinity.
      int initMPI(0);                                           // Initialise MPI in ScannerBit, not in MultiNest
      void *context = 0;                                        // any additional information user wants to pass (not required by MN)
      // Which parameters to have periodic boundary conditions?
      int pWrap[ndims];
      for(int i = 0; i < ndims; i++) pWrap[i] = 0; // (need to do more work if we actually want to allow periodic BCs)

      // TODO: check what happens if resume mode is active but multinest native output is not written. I guess it will resume writing to the printer output, but actually start a new scan?

      // Root for output files
      std::string root_str;
      std::string defpath = Gambit::Utils::ensure_path_exists(
           get_inifile_value<std::string>("default_output_path")+"MultiNest/native-"
           ); // from gambit global default
      root_str = get_inifile_value<std::string>("root", defpath);
      char root[1000];  // I think MultiNest will truncate this to 100. But lets use a larger array just in case.
      Gambit::Utils::strcpy2f(root, 1000, root_str);// (copy std::string into char array for transport to Fortran)

      if(resume==1 and outfile==0)
      {
        // It is stupid to be in resume mode while not writing output files.
        // Means subsequent resumes will be impossible. Throw an error.
        scan_error().raise(LOCAL_INFO,"Error from MultiNest ScannerBit plugin! Resume mode is activated, however "
                                      "MultiNest native output files are set to not be written. These are needed "
                                      "for resuming; please change this setting in your yaml file (set option \"outfile: 1\")");
      }

      // Setup auxilliary streams. These are only needed by the master process,
      // so let's create them only for that process
      int myrank = get_printer().get_stream()->getRank(); // MPI rank of this process
      if(myrank==0)
      {
         // Get inifile options for each print stream
         Gambit::Options txt_options   = get_inifile_node("aux_printer_txt_options");
         //Gambit::Options stats_options = get_inifile_node("aux_printer_stats_options"); //FIXME
         Gambit::Options live_options  = get_inifile_node("aux_printer_live_options");

         // Options to desynchronise print streams from the main Gambit iterations. This allows for random access writing, or writing of global scan data.
         //stats_options.setValue("synchronised",false); //FIXME
         txt_options.setValue("synchronised",false);
         live_options.setValue("synchronised",false);

         // Initialise auxiliary print streams
         get_printer().new_stream("txt",txt_options);
         //get_printer().new_stream("stats",stats_options); //FIXME
         get_printer().new_stream("live",live_options);
      }

      // Ensure that MPI processes have the same IDs for auxiliary print streams;
      Gambit::Scanner::assign_aux_numbers("Posterior","LastLive");

      // Create the object that interfaces to the MultiNest LogLike callback function
      Gambit::MultiNest::LogLikeWrapper loglwrapper(LogLike, get_printer());
      Gambit::MultiNest::global_loglike_object = &loglwrapper;

      //Run MultiNest, passing callback functions for the loglike and dumper.
      if(myrank == 0) std::cout << "Starting MultiNest run..." << std::endl;
      run(IS, mmodal, ceff, nlive, tol, efr, ndims, nPar, nClsPar, maxModes, updInt, Ztol,
          root, seed, pWrap, fb, resume, outfile, initMPI, ln0, maxiter,
          Gambit::MultiNest::callback_loglike, Gambit::MultiNest::callback_dumper, context);
      if(myrank == 0) std::cout << "Multinest run finished!" << std::endl;
      return 0;

   }

}


/// =================================================
/// Function definitions
/// =================================================

namespace Gambit {

   namespace MultiNest {

      ///@{ Plain-vanilla functions to pass to Multinest for the callback
      // Note: we are using the c interface from cwrapper.f90, so the function
      // signature is a little different than in the multinest examples.
      double callback_loglike(double *Cube, int ndim, int npars, void*)
      {
         // Call global interface to ScannerBit loglikelihood function
         // Could also pass this object in via context pointer, but that
         // involves some casting and could risk a segfault.
         return global_loglike_object->LogLike(Cube, ndim, npars);
      }

      void callback_dumper(int nSamples, int nlive, int nPar, double *physLive,
                           double *posterior, double *paramConstr,
                           double maxLogLike, double logZ, double logZerr,
                           void*)
      {
         global_loglike_object->
            dumper(nSamples, nlive, nPar, physLive, posterior, paramConstr,
                   maxLogLike, logZ, logZerr);
      }
      ///@}


      /// LogLikeWrapper Constructor
      LogLikeWrapper::LogLikeWrapper(scanPtr loglike, printer_interface& printer)
        : boundLogLike(loglike), boundPrinter(printer), dumper_runonce(false)
      { }

      /// Main interface function from MultiNest to ScannerBit-supplied loglikelihood function
      /// This is the function that will be passed to Multinest as the
      /// loglike callback routine
      ///
      /// Input arguments
      /// ndim    = dimensionality (total number of free parameters) of the problem
      /// npars   = total number of free plus derived parameters
      /// context = void pointer, any additional information
      ///
      /// Input/Output arguments
      /// Cube[npars]  = on entry has the ndim parameters in unit-hypercube
      ///                on exit, the physical parameters plus copy any derived parameters
      ///                you want to store with the free parameters
      ///
      /// Output arguments
      /// lnew = loglikelihood
      ///
      double LogLikeWrapper::LogLike(double *Cube, int ndim, int)
      {
         //convert C style array to C++ vector class
         std::vector<double> unitpars(Cube, Cube + ndim);

         double lnew = boundLogLike(unitpars);

         // Extract the primary printer from the printer manager
         //printer* primary_stream( boundPrinter.get_stream() );

         // Get, set and ouptut the process rank and this point's ID
         int myrank  = boundLogLike->getRank(); // MPI rank of this process
         int pointID = boundLogLike->getPtID();   // point ID number
         Cube[ndim+0] = myrank;
         Cube[ndim+1] = pointID;

         // Done! (lnew will be used by MultiNest to guide the search)
         return lnew;
      }

      /// Main interface to MultiNest dumper routine
      /// The dumper routine will be called every updInt*10 iterations
      /// MultiNest does not need to the user to do anything. User can use the arguments in whichever way he/she wants
      ///
      /// Arguments:
      ///
      /// nSamples                                             = total number of samples in posterior distribution
      /// nlive                                                = total number of live points
      /// nPar                                                 = total number of parameters (free + derived)
      /// physLive[1][nlive * (nPar + 1)]                      = 2D array containing the last set of live points
      ///                                                        (physical parameters plus derived parameters) along
      ///                                                        with their loglikelihood values
      /// TODO: Multinest uses the likelihood of the lowest live point as the "threshold" for iterating, i.e. it throws out the live point if it finds a better one. So we can use this number to update the GAMBIT 'cutoff' threshold when evaluating the likelihood function.

      /// posterior[1][nSamples * (nPar + 2)]                  = posterior distribution containing nSamples points.
      ///                                                        Each sample has nPar parameters (physical + derived)
      ///                                                        along with the their loglike value & posterior probability
      /// paramConstr[0][0] to paramConstr[0][nPar - 1]        = mean values of the parameters
      /// paramConstr[0][nPar] to paramConstr[0][2*nPar - 1]   = standard deviation of the parameters
      /// paramConstr[0][nPar*2] to paramConstr[0][3*nPar - 1] = best-fit (maxlike) parameters
      /// paramConstr[0][nPar*4] to paramConstr[0][4*nPar - 1] = MAP (maximum-a-posteriori) parameters
      /// paramConstr[1][4*nPar]                               = ????
      /// maxLogLike                                           = maximum loglikelihood value
      /// logZ                                                 = log evidence value
      /// logZerr                                              = error on log evidence value
      /// context                                              = void pointer, any additional information
      void LogLikeWrapper::dumper(int nSamples, int nlive, int nPar, double *physLive, double *posterior, double* /*paramConstr*/,
       double /*maxLogLike*/, double /*logZ*/, double /*logZerr*/)
      {
          int thisrank = boundPrinter.get_stream()->getRank(); // MPI rank of this process
          if(thisrank!=0)
          {
             scan_err <<"Error! ScannerBit MultiNest plugin attempted to run 'dumper' function on a worker process "
                      <<"(thisrank=="<<thisrank<<")! MultiNest should only try to run this function on the master "
                      <<"process. Most likely this means that your multinest installation is not running in MPI mode "
                      <<"correctly, and is actually running independent scans on each process. Alternatively, the "
                      <<"version of MultiNest you are using may be too far ahead of what this plugin can handle, "
                      <<"if e.g. the described behaviour has changed since this plugin was written."
                      << scan_end;
          }

          // Send signal to other processes to switch to higher min_logL value.
          // MultiNest was sometimes getting stuck looking for live point candidates;
          // increasing this above the MultiNext zero_LogL value should avoid that
          // issue.
          // We do this here because initial live point generation should be finished
          // once the dumper runs, and we want the original min_logL value while generating
          // live points.
          if (!dumper_runonce)
          {
             dumper_runonce = true;
             boundLogLike->switch_to_alternate_min_LogL();
             std::cerr << "Multinest dumper first ran on process "<<boundLogLike->getRank()<<" at iteration "<<boundLogLike->getPtID()<<std::endl;
          }

          // Get printers for each auxiliary stream
          //printer* stats_stream( boundPrinter.get_stream("stats") ); //FIXME see below
          printer* txt_stream(   boundPrinter.get_stream("txt")   );
          printer* live_stream(  boundPrinter.get_stream("live")  );

          // Reset the print streams. WARNING! This potentially deletes the old data (here we overwrite it on purpose)
          //stats_stream->reset();  // FIXME
          txt_stream->reset();
          live_stream->reset();

          // Ensure the "quantity" IDcode is UNIQUE across all printers! This way fancy printers
          // have the option of ignoring duplicate writes and doing things like combine all the
          // auxiliary streams into a single database. But must be able to assume IDcodes are
          // unique for a given quanity to do this.
          // Negative numbers not used by functors, so those are 'safe' to use here

          // FIXME this is buggy atm
          // Stats file
          // For now, MPIrank set to 0 and pointID set to -1, as not needed. Might change how this works later.
          //                  Quantity    Label         IDcode  MPIrank  pointID
          //stats_stream->print(maxLogLike, "maxLogLike", -1,  0,  -1);
          //stats_stream->print(logZ,       "logZ",       -2,  0,  -1);
          //stats_stream->print(logZerr,    "logZerr",    -3,  0,  -1);

          // txt file stuff
          // Send info for each point to printer one command at a time
          int pointID; // ID number for each point
          int myrank;  // MPI rank which wrote each point

          // The discarded live points (and rejected candidate live points if IS = 1)
          for( int i = 0; i < nSamples; i++ )
          {
             myrank  = posterior[(nPar-2)*nSamples + i]; //MPI rank stored in second last entry of cube
             pointID = posterior[(nPar-1)*nSamples + i]; //pointID stored in last entry of cube

             txt_stream->print( posterior[(nPar+1)*nSamples + i], "Posterior", myrank, pointID);
             // Put rest of parameters into a vector for printing all together // TODO: not needed, delete?
             // std::vector<double> parameters;
             // for( int j = 0; j < nPar-2; j++ )
             // {
             //     parameters.push_back( posterior[j*nSamples + i] );
             // }
          }

          // The last set of live points
          for( int i = 0; i < nlive; i++ )
          {
             myrank  = physLive[(nPar-2)*nlive + i]; //MPI rank number stored in second last entry of cube
             pointID = physLive[(nPar-1)*nlive + i]; //pointID stored in last entry of cube
             live_stream->print( true, "LastLive", myrank, pointID); // Flag which points were the last live set
             // // Put rest of parameters into a vector for printing all together // TODO: not needed, delete?
             // std::vector<double> parameters;
             // for( int j = 0; j < nPar-2; j++ )
             // {
             //     parameters.push_back( physLive[j*nlive + i] );
             // }
             // //live_stream->print(parameters, "Parameters", myrank, pointID);
          }
          
          // Flush these printers to disk
          txt_stream->flush();
          live_stream->flush();

      }

   }

}

