//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  ScannerBit interface to PolyChord 1.20.1
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
///  \date May 2018, June 2021, Mar 2022
///
///  \author Patrick Stoecker
///          (stoecker@physik.rwth-aachen.de)
///  \date May 2020
///
///  \author Anders Kvellestad
///          (anders.kvellestad@fys.uio.no)
///  \date June 2022
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
#include <numeric>

#include "gambit/ScannerBit/scanner_plugin.hpp"
#include "gambit/ScannerBit/scanners/polychord/1.20.1/polychord.hpp"
#include "gambit/Utils/yaml_options.hpp"
#include "gambit/Utils/util_functions.hpp"


namespace Gambit
{
   namespace PolyChord_1_20_1
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

scanner_plugin(polychord, version(1, 20, 1))
{
   // Access PolyChord stuff and standard Gambit things
   using namespace Gambit;
   using namespace Gambit::PolyChord_1_20_1;

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

      // Retrieve whether the scanned parameters should be added to the native output and determine nderived
      int nderived = 2;
      if (get_inifile_value<bool>("print_parameters_in_native_output", false)) nderived += ma;

      // Initialise polychord settings
      Settings settings(ma, nderived);

      // Create the object that interfaces to the PolyChord LogLike callback function
      LogLikeWrapper loglwrapper(LogLike, get_printer());
      global_loglike_object = &loglwrapper;

      // ---------- Compute an ordering for fast and slow parameters
      // Read list of fast parameters from file
      std::vector<std::string> fast_params = get_inifile_value<std::vector<std::string>>("fast_params", {});
      // Get list of parameters used from loglikelihood
      std::vector<std::string> varied_params = LogLike->getShownParameters();
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
      // grade_dims is a vector of integers that indicates the number of slow and fast parameters
      settings.grade_dims.clear();
      unsigned int i = 0;
      // Run through all the parameters, and if they're slow parameters
      // give them an index i, then increment i
      for (auto param : varied_params)
         if (std::find(fast_params.begin(), fast_params.end(),param) == fast_params.end())
            global_loglike_object->index_map[param] = (i++);
      unsigned int nslow = i;
      if(nslow!=0) settings.grade_dims.push_back(nslow);

      // Do the same for the fast parameters
      for (auto param : varied_params)
         if (std::find(fast_params.begin(), fast_params.end(),param) != fast_params.end())
            global_loglike_object->index_map[param] = (i++);
      unsigned int nfast = i-nslow;
      if (nfast>0) settings.grade_dims.push_back(nfast);

      // In the unusual case of all fast parameters, there's only one grade. 
      if (nslow==0) {nslow = nfast; nfast=0;}

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
      settings.write_resume = outfile;
      settings.read_resume = resume_mode;
      settings.compression_factor = get_inifile_value<double>("compression_factor",0.36787944117144233);
      settings.synchronous = get_inifile_value<bool>("synchronous", true); // Whether to run in synchronous parallelisation mode
      settings.base_dir = get_inifile_value<std::string>("default_output_path")+"PolyChord";
      settings.file_root = get_inifile_value<std::string>("root", "native");
      settings.seed = get_inifile_value<int>("seed",-1);

      if (nslow>0 and nfast>0)
      {
         // Specify the fraction of time to spend in the slow parameters.
         //double frac_slow = get_inifile_value<double>("frac_slow",0.75);
         //settings.grade_frac = std::vector<double>({frac_slow, 1-frac_slow});
         double oversample_fast = get_inifile_value<double>("oversample_fast",30.0); 
         settings.grade_frac = std::vector<double>({settings.num_repeats*1.0, oversample_fast*nfast});
      }

      Utils::ensure_path_exists(settings.base_dir);
      Utils::ensure_path_exists(settings.base_dir + "/clusters/");

      // Point the boundSettings to the settings in use
      global_loglike_object->boundSettings = settings;

      // Set the speed threshold for the printer.
      // Evaluations of speeds >= threshold are not printed
      // Speeds start at 0
      global_loglike_object->printer_speed_threshold =
        get_inifile_value<int>("printer_speed_threshold",settings.grade_dims.size());

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
         Options txt_options   = get_inifile_node("aux_printer_txt_options");
         //Options stats_options = get_inifile_node("aux_printer_stats_options"); //FIXME
         Options live_options  = get_inifile_node("aux_printer_live_options");

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
      Scanner::assign_aux_numbers("Posterior","LastLive");

      //Run PolyChord, passing callback functions for the loglike and dumper.
      if(myrank == 0) std::cout << "Starting PolyChord run..." << std::endl;
      run_polychord(callback_loglike, callback_dumper, settings);
      if(myrank == 0) std::cout << "PolyChord run finished!" << std::endl;
      return 0;

   }

}


/// =================================================
/// Function definitions
/// =================================================

namespace Gambit {

   namespace PolyChord_1_20_1 {

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
         // Cached "below threshold" unitcube parameters of the previous point.
         static int ndim_threshold =
            std::accumulate( boundSettings.grade_dims.begin(),
                             boundSettings.grade_dims.begin() + printer_speed_threshold,
                             0);
         static std::vector<double> prev_slow_unit(ndim_threshold);

         //convert C style array to C++ vector class, reordering parameters slow->fast
         std::vector<std::string> params = boundLogLike->getShownParameters();
         std::vector<double> unitpars(ndim);
         for (auto i=0; i<ndim; i++)
            unitpars[i] = Cube[index_map[params[i]]];
         std::vector<double> derived(phi, phi + nderived);

         // Disable the printer when the unitcube parameters with speeds below
         // the threshold have not changed and enable it otherwise
         // (It might be probably already enabled again at that point)
         if (   ndim_threshold < ndim
            &&  std::equal(prev_slow_unit.begin(),prev_slow_unit.end(),Cube) )
         {
            boundLogLike->getPrinter().disable();
         }
         else
         {
            boundLogLike->getPrinter().enable();
         }
         prev_slow_unit = std::vector<double>(Cube,Cube+ndim_threshold);

         double lnew = boundLogLike(unitpars);

         // Done! (lnew will be used by PolyChord to guide the search)

         // Get the transformed parameters and add them as derived parameters
         if (nderived > 2)
         {
            std::unordered_map<std::string,double> param_map;
            boundLogLike->getPrior().transform(unitpars, param_map);
            for (auto& param: param_map)
            {
               // param_map contains ALL parameters.
               // We just need the ones which are varied (i.e. the keys of index_map)
               if (index_map.find(param.first) != index_map.end())
                  phi[index_map[param.first]] = param.second;
            }
         }

         // Get, set and ouptut the process rank and this point's ID
         int myrank  = boundLogLike->getRank(); // MPI rank of this process
         int pointID = boundLogLike->getPtID();   // point ID number
         phi[nderived - 2] = myrank;
         phi[nderived - 1] = pointID;

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

         // Write a file at first run of dumper to specify the index of a given dataset.
         static bool first = true;
         if (first)
         {
            int ndim = boundSettings.nDims;
            int nderived = boundSettings.nDerived;

            // Construct the inversed index map
            // map[polychord_hypercube] = {name, gambit_hypercube}
            std::vector<std::string> params = boundLogLike->getShownParameters();
            std::map<int,std::pair<std::string,int>> inversed_map;
            for (int i=0; i<ndim; ++i)
               inversed_map[index_map[params[i]]] = {params[i],i};

            std::ostringstream fname;
            fname << boundSettings.base_dir << "/" <<boundSettings.file_root << ".indices";
            std::ofstream ofs(fname.str());

            int index = 0;
            ofs << index++ << "\t" << "Posterior" << std::endl;
            ofs << index++ << "\t" << "-2*(" << boundLogLike->getPurpose() << ")" << std::endl;

            for (int i=0; i<ndim; ++i)
               ofs << index++ << "\t" << "unitCubeParameters[" << inversed_map[i].second <<"]" << std::endl;
            for (int i=0; i<nderived -2; ++i)
               ofs << index++ << "\t" << inversed_map[i].first << std::endl;

            ofs << index++ << "\t" << "MPIrank" << std::endl;
            ofs << index++ << "\t" << "pointID" << std::endl;

            ofs.close();
         }
         first = false;

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
            double birth = dead[npars*i_dead + npars-2];   // birth contours
            double death = dead[npars*i_dead + npars-1]; // death contours
            txt_stream->print( std::exp(logw), "Posterior", myrank, pointID);
            txt_stream->print( birth, "LogLike_birth", myrank, pointID);
            txt_stream->print( death, "LogLike_death", myrank, pointID);
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

