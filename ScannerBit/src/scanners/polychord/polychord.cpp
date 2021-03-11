//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  ScannerBit interface to PolyChord 1.16
///
///  *********************************************
///
///  Authors (add name and date if you modify):
//
///  \author Ben Farmer
///          (ben.farmer@gmail.com)
///  \date October 2013 - Aug 2016
///
///  \author Will Handley
///          (wh260@cam.ac.uk)
///  \date May 2018
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
#include <algorithm>

#include "gambit/ScannerBit/scanner_plugin.hpp"
#include "gambit/ScannerBit/scanners/polychord/polychord.hpp"
#include "gambit/Utils/yaml_options.hpp"
#include "gambit/Utils/util_functions.hpp"


namespace Gambit
{
   namespace PolyChord
   {
      /// Global pointer to loglikelihood wrapper object, for use in the PolyChord callback functions
      LogLikeWrapper *global_loglike_object;
   }
}

/// Typedef for the ScannerBit pointer to the external loglikelihood function
typedef Gambit::Scanner::like_ptr scanPtr;


/// =================================================
/// Interface to ScannerBit
/// =================================================

scanner_plugin(polychord, version(1, 16))
{
   // An error is thrown if any of the following entries are not present in the inifile (none absolutely required for PolyChord).
   reqd_inifile_entries();

   // Tell cmake system to search known paths for these libraries; any not found must be specified in config/scanner_locations.yaml.
   reqd_libraries("chord");

   // Pointer to the (log)likelihood function
   scanPtr LogLike;

   /// The constructor to run when the PolyChord plugin is loaded.
   plugin_constructor
   {
      // Retrieve the external likelihood calculator
      LogLike = get_purpose(get_inifile_value<std::string>("like"));
      if (LogLike->getRank() == 0) std::cout << "Loading PolyChord nested sampling plugin for ScannerBit." << std::endl;
   }

   /// The main routine to run for the PolyChord scanner.
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

      // Initialise polychord settings
      Settings settings(ma, 2);

      // Create the object that interfaces to the PolyChord LogLike callback function
      Gambit::PolyChord::LogLikeWrapper loglwrapper(LogLike, get_printer());
      Gambit::PolyChord::global_loglike_object = &loglwrapper;

      // ---------- Compute an ordering for fast and slow parameters
      // Read list of fast parameters from file
      std::vector<std::string> fast_params = get_inifile_value<std::vector<std::string>>("fast_params", {});
      // Get list of parameters used from loglikelihood
      std::vector<std::string> all_params = LogLike->getParameters();

      // Compute the set difference between fast_params and all_params to check if there are any fast_params not included in all_params
      std::set<std::string> set_fast_params(fast_params.begin(), fast_params.end()), set_params(all_params.begin(), all_params.end()), diff; 
      std::set_difference(set_fast_params.begin(), set_fast_params.end(), set_params.begin(), set_params.end(),std::inserter(diff,diff.begin()));
      if (diff.size())
      {
          // Raise an error if any specified fast_params are not actually being sampled over.
          std::string error_message = "You have specified:\n";
          for (auto param : diff) error_message += param + "\n" ;
          error_message += "as fast param(s), but the list of params is:\n";
          for (auto param : all_params) error_message += param + "\n";
          scan_error().raise(LOCAL_INFO,error_message);
      }

      // Compute the locations in PolyChord's unit hypercube, ordering from slow to fast
      // This defaults to nDims if there are no fast parameters, or if all parameters are fast.
      int nslow = settings.nDims;
      if (fast_params.size() != 0 and fast_params.size() != settings.nDims)
      {

          // grade_dims is a vector of integers that indicates the number of slow and fast parameters
          settings.grade_dims.clear();
          int i = 0;
          // Run through all the parameters, and if they're slow parameters
          // give them an index i, then increment i
          for (auto param : all_params) 
              if (std::find(fast_params.begin(), fast_params.end(),param) == fast_params.end())
                  Gambit::PolyChord::global_loglike_object->index_map[param] = (i++);
          settings.grade_dims.push_back(i);
          nslow = i;

          // Do the same for the fast parameters
          for (auto param : all_params) 
              if (std::find(fast_params.begin(), fast_params.end(),param) != fast_params.end())
                  Gambit::PolyChord::global_loglike_object->index_map[param] = (i++);

          // If there are any fast parameters...
          if (i>settings.grade_dims[0]){ 
              // ... tell this to PolyChord via an extra entry into the grade_dims vector
              settings.grade_dims.push_back(i);
              // Specify the fraction of time to spend in the slow parameters.
              double frac_slow = get_inifile_value<double>("frac_slow",0.75); 
              settings.grade_frac = std::vector<double>({frac_slow, 1-frac_slow});
          }
      }
      // ---------- End computation of ordering for fast and slow parameters

      // PolyChord algorithm options.
      settings.nlive = get_inifile_value<int>("nlive", settings.nDims*25);         // number of live points
      settings.num_repeats = get_inifile_value<int>("num_repeats", nslow*2);       // length of slice sampling chain
      settings.nprior = get_inifile_value<int>("nprior", settings.nlive*10);       // number of prior samples to begin algorithm with
      settings.do_clustering = get_inifile_value<bool>("do_clustering", true);     // Whether or not to perform clustering
      settings.feedback = get_inifile_value<int>("fb", 1);                         // Feedback level
      settings.precision_criterion = get_inifile_value<double>("tol", 0.5);        // Stopping criterion (consistent with multinest)
      settings.logzero = get_inifile_value<double>("logzero",gl0);
      settings.max_ndead = get_inifile_value<double>("maxiter", -1);               // Max no. of iterations, a negative value means infinity (different in comparison with multinest).
      settings.maximise = get_inifile_value<bool>("maximise", false);              // Whether to run a maximisation algorithm once the run is finished
      settings.boost_posterior = 0; // Increase the number of posterior samples produced
      bool outfile (get_inifile_value<bool>("outfile", true));                // write output files?
      settings.posteriors = outfile;
      settings.equals = outfile;
      settings.cluster_posteriors = outfile;
      settings.write_paramnames = outfile;
      settings.write_stats = outfile;
      settings.write_live = outfile; 
      settings.write_dead = outfile;
      settings.write_prior = outfile;
      settings.write_resume = resume_mode;
      settings.read_resume = resume_mode;
      settings.compression_factor = get_inifile_value<double>("compression_factor",0.36787944117144233);
      settings.base_dir = get_inifile_value<std::string>("default_output_path")+"PolyChord";
      settings.file_root = get_inifile_value<std::string>("root", "native");
      settings.seed = get_inifile_value<int>("seed",-1);

      Gambit::Utils::ensure_path_exists(settings.base_dir);
      Gambit::Utils::ensure_path_exists(settings.base_dir + "/clusters/");


      if(resume_mode==1 and outfile==0)
      {
        // It is stupid to be in resume mode while not writing output files.
        // Means subsequent resumes will be impossible. Throw an error.
        scan_error().raise(LOCAL_INFO,"Error from PolyChord ScannerBit plugin! Resume mode is activated, however "
                                      "PolyChord native output files are set to not be written. These are needed "
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

      //Run PolyChord, passing callback functions for the loglike and dumper.
      if(myrank == 0) std::cout << "Starting PolyChord run..." << std::endl;
      run_polychord(Gambit::PolyChord::callback_loglike, Gambit::PolyChord::callback_dumper, settings);
      if(myrank == 0) std::cout << "PolyChord run finished!" << std::endl;
      return 0;

   }

}


/// =================================================
/// Function definitions
/// =================================================

namespace Gambit {

   namespace PolyChord {

      ///@{ Plain-vanilla functions to pass to PolyChord for the callback
      // Note: we are using the c interface from cwrapper.f90, so the function
      // signature is a little different than in the polychord examples.
      double callback_loglike(double *Cube, int ndim, double* phi, int nderived)
      {
         // Call global interface to ScannerBit loglikelihood function
         // Could also pass this object in via context pointer, but that
         // involves some casting and could risk a segfault.
         return global_loglike_object->LogLike(Cube, ndim, phi, nderived);
      }

      void callback_dumper(int ndead, int nlive, int npars, 
                           double *live, double *dead, double* logweights,
                           double logZ, double logZerr)
      {
         global_loglike_object->
            dumper(ndead, nlive, npars, live, dead, logweights, logZ, logZerr);
      }
      ///@}


      /// LogLikeWrapper Constructor
      LogLikeWrapper::LogLikeWrapper(scanPtr loglike, printer_interface& printer)
        : boundLogLike(loglike), boundPrinter(printer)
      { }

      /// Main interface function from PolyChord to ScannerBit-supplied loglikelihood function
      /// This is the function that will be passed to PolyChord as the
      /// loglike callback routine
      ///
      /// Input arguments
      /// ndim          = dimensionality (total number of free parameters) of the problem
      /// nderived      = total number of derived parameters
      /// Cube[ndim]    = ndim parameters 
      ///
      /// Output arguments
      /// phi[nderived] = nderived devired parameters
      /// lnew          = loglikelihood
      ///
      double LogLikeWrapper::LogLike(double *Cube, int ndim, double* phi, int nderived)
      {
         //convert C style array to C++ vector class, reordering parameters slow->fast
         std::vector<std::string> params = boundLogLike->getParameters();
         std::vector<double> unitpars(ndim);
         for (auto i=0; i<ndim; i++) 
             unitpars[i] = Cube[index_map[params[i]]];
         std::vector<double> derived(phi, phi + nderived);

         double lnew = boundLogLike(unitpars);

         // Done! (lnew will be used by PolyChord to guide the search)

         // Get, set and ouptut the process rank and this point's ID
         int myrank  = boundLogLike->getRank(); // MPI rank of this process
         int pointID = boundLogLike->getPtID();   // point ID number
         phi[0] = myrank;
         phi[1] = pointID;
         return lnew;
      }

      /// Main interface to PolyChord dumper routine
      /// The dumper routine will be called every time the live points compress by a factor compression_factor
      /// PolyChord does not need to the user to do anything. User can use the arguments in whichever way they want
      ///
      /// Arguments:
      ///
      /// ndead                                                = total number of discarded points for posterior usage
      /// nlive                                                = total number of live points
      /// nPar                                                 = total number of parameters + 2 (free + derived + 2)
      /// live[nlive*npars]                                    = 2D array containing the last set of live points
      ///                                                        (physical parameters plus derived parameters + birth contour + death contour)

      /// dead[ndead*npars]                                    = posterior distribution containing nSamples points.
      ///                                                        Each sample has nPar parameters (physical + derived)
      ///                                                        along with the their loglike value & posterior probability
      /// logweights[ndead]                                    = log of posterior weighting of dead points. Use this to turn them into posterior weighted samples
      /// logZ                                                 = log evidence value
      /// logZerr                                              = error on log evidence value
      void LogLikeWrapper::dumper(int ndead, int nlive, int npars,
                                  double *live, double *dead, double* logweights, 
                                  double /*logZ*/, double /*logZerr*/)
      {
          int thisrank = boundPrinter.get_stream()->getRank(); // MPI rank of this process
          if(thisrank!=0)
          {
             scan_err <<"Error! ScannerBit PolyChord plugin attempted to run 'dumper' function on a worker process "
                      <<"(thisrank=="<<thisrank<<")! PolyChord should only try to run this function on the master "
                      <<"process. Most likely this means that your PolyChord installation is not running in MPI mode "
                      <<"correctly, and is actually running independent scans on each process. Alternatively, the "
                      <<"version of PolyChord you are using may be too far ahead of what this plugin can handle, "
                      <<"if e.g. the described behaviour has changed since this plugin was written."
                      << scan_end;
          }

          // Get printers for each auxiliary stream
          printer* txt_stream(   boundPrinter.get_stream("txt")   );
          printer* live_stream(  boundPrinter.get_stream("live")  );

          // Reset the print streams. WARNING! This potentially deletes the old data (here we overwrite it on purpose)
          txt_stream->reset();
          live_stream->reset();

          // Ensure the "quantity" IDcode is UNIQUE across all printers! This way fancy printers
          // have the option of ignoring duplicate writes and doing things like combine all the
          // auxiliary streams into a single database. But must be able to assume IDcodes are
          // unique for a given quanity to do this.
          // Negative numbers not used by functors, so those are 'safe' to use here

          // The discarded live points (and rejected candidate live points if IS = 1)
          for( int i_dead = 0; i_dead < ndead; i_dead++ )
          {
             int myrank  = dead[npars*i_dead + npars-4]; //MPI rank stored in fourth last column
             int pointID = dead[npars*i_dead + npars-3]; //pointID stored in third last column
             double logw = logweights[i_dead];           //posterior weight stored in logweights
             txt_stream->print( std::exp(logw), "Posterior", myrank, pointID);
          }

          // The last set of live points
          for( int i_live = 0; i_live < nlive; i_live++ )
          {
             int myrank  = live[npars*i_live + npars-4]; //MPI rank stored in fourth last column
             int pointID = live[npars*i_live + npars-3]; //pointID stored in third last column
             live_stream->print( true, "LastLive", myrank, pointID); // Flag which points were the last live set
          }

      }

   }

}

