//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Functions of module ExampleBit_A.
///
///  Put your functions in files like this
///  if you wish to add observables or likelihoods
///  to this module.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///    \date 2012 Nov
///    \date 2013 Jan, Feb, May, Dec
///
///  \author Christoph Weniger
///    \date 2013 Jan
///
///  \author Anders Kvellestad
///          (anders.kvellestad@fys.uio.no)
///  \date 2013 Nov
///
///  \author Ben Farmer
///          (ben.farmer@gmail.com)
///  \date 2015 Sep
///
///  *********************************************

#include <string>
#include <iostream>
#include <cmath>
#include <functional>
#include <omp.h>
#include <time.h> // For nanosleep (posix only)

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/ExampleBit_A/ExampleBit_A_rollcall.hpp"


namespace Gambit
{

  namespace ExampleBit_A
  {
    using namespace LogTags;

    /// \name Helper functions
    /// Not wrapped in rollcall header.
    /// @{

    /// Pointer to some function
    double(*callback_pointer)(int&, const double&);

    /// Some other example function
    double some_other_function(int &input)
    {
      std::ostringstream ss;
      ss << "  This is some_other_function, invoked with argument " << input;
      logger().send(ss.str(),info);
      double offset = 2.0;
      return callback_pointer(input, offset);
    }

    /// Un-normalised gaussian log-likelihood
    double logf (double x, double mu, double sig)
    {
      return -0.5*log(sig*sig) -0.5*pow(x-mu,2)/(sig*sig);
    }

    /// @}

    //************************************************************

    /// \name Module functions
    /// @{
    void nevents_pred      (double &result)    { static double count = 3.5; result = count++; cout << "My xsection dep: " << *Pipes::nevents_pred::Dep::xsection << endl;}
    void nevents_like      (double &result)    { result = 2.0 * (*Pipes::nevents_like::Dep::eventAccumulation); }
    void particle_identity (str    &result)    { result = "fakion"; }

    void nevents_pred_rounded(int &result)
    {
      result = (int) (*Pipes::nevents_pred_rounded::Dep::nevents);
      // Randomly raise some ficticious alarms about this point, with probability x,
      // where x is given by the input yaml option or a default of 0.5.
      double x = 1.0-Pipes::nevents_pred_rounded::runOptions->getValueOrDef<double>(0.5, "probability_of_validity");
      if (Random::draw() < x)
      {
        //Example of how to raise an error from a module function.
        //ExampleBit_A_error().raise(LOCAL_INFO,"Damn, this integer event count is bad.");
        //Example of how to declare a point invalid.
        invalid_point().raise("I don't like this point.");
      }
      // Example of how to check if computation of another capability depends on this one at all.
      cout << "My name is nevents_pred_rounded, and I am " <<
       (Pipes::nevents_pred_rounded::Downstream::neededFor("nevents") ?
       "proud to contribute to the calculation of nevents today." :
       "completely superfluous to the calculation of nevents.")
      << endl;

    }

    void test_sigma(double &result)
    {
      result = 1.; //trivial test
    }

    void function_pointer_retriever( double(*&result)(int&) )
    {
      using namespace Pipes::function_pointer_retriever;
      //Two ways to return this result, depending on how the group dependency BEgroup::external_funcs is fulfilled:
      if (*BEgroup::external_funcs == "externalFunction")
      {
        //1. A pointer to a fortran function that has been backended (and takes an int as an input by reference):
        result = BEreq::externalFunction.pointer();
      }
      else if (*BEgroup::external_funcs == "externalComplicatedFunction")
      {
        //2. A pointer to a local C++ function (that, e.g. calls a function provided by a backend)
        callback_pointer = BEreq::externalComplicatedFunction.pointer();
        result = &some_other_function;
      }
      else ExampleBit_A_error().raise(LOCAL_INFO,"Unrecognised choice from external_funcs BEgroup.");
    }


    /// Example of interacting with models
    void example_damu (double &result)
    {
      using namespace Pipes::example_damu;
      std::cout << "In ExampleBit_A, function damu" << std::endl;
      logger() << "Is CMSSM being scanned? " << ModelInUse("CMSSM") << endl;
      logger() << "Is NUHM1 being scanned? " << ModelInUse("NUHM1") << endl;
      logger() << "Is NormalDist being scanned? " << ModelInUse("NormalDist") << endl;;
      logger() << "Is ScalarSingletDM_Z2 being scanned? "  << ModelInUse("ScalarSingletDM_Z2");;
      logger() << info << EOM;
      std::cout << "  Printing parameter values:" << std::endl;
      std::cout << "mu: " << *Param["mu"] << std::endl;
      std::cout << "sigma: " << *Param["sigma"] << std::endl;
      //A safety_bucket containing the ModelParameters object itself is also
      //available as a dependency at Pipes::<functionname>::Dep::<modelname>_parameters,
      //in case you want to do something more advanced than just read off the
      //parameter values.
      result = *Param["p1"] * *Param["p2"];
    }

    /// Likelihood function for fitting the population parameters of a
    /// normal distribution (with hard-coded "observations")
    /// Mainly used for testing scanning algorthims
    void lnL_gaussian (double &result)
    {
      using namespace Pipes::lnL_gaussian;

      // Say we have a sample of 20 drawn from a normal distribution with
      // parameters muTrue and sigmaTrue. Let the sample mean and standard
      // deviation be as follows (this is our data):
      static const int N = 20;
      static const double samples [] = {
        21.32034213,  20.39713359,  19.27957134,  19.81839231,
        20.89474358,  20.11058756,  22.38214557,  21.41479798,
        23.49896999,  17.55991187,  24.9921142 ,  23.90166585,
        20.97913273,  18.59180551,  23.49038072,  19.08201714,
        21.19538797,  16.42544039,  18.93568891,  22.40925288
        };

      double loglTotal = 0.;

      // The loglikelihood value for the hypothesised parameters is then:
      if (ModelInUse("NormalDist"))
      {
        for (int i=0; i<N; ++i)
        {
          double mu = *Param["mu"];
          double sigma = *Param["sigma"];
          if(Utils::isnan(mu) or Utils::isnan(sigma))
          {
            ExampleBit_A_error().raise(LOCAL_INFO,"NaN detected in input parameters for model"
            " NormalDist! This may indicate a bug in the scanner plugin you are using.");
          }
          if(sigma==0.)
          {
             // likelihood is nan if sigma=0, so the point is invalid.
             invalid_point().raise("NormalDist::sigma = 0; likelihood is NaN, point invalid.");
          }

          loglTotal += logf(samples[i], mu, sigma);
        }
      }
      else
      {
         ExampleBit_A_error().raise(LOCAL_INFO,"Whoops, you are not scanning the model "
          " NormalDist! There is probably a bug ExampleBit_A_rollcall.hpp; this module "
          " function should have ALLOW_MODELS(NormalDist) defined.");
      }

      // Randomly raise some ficticious alarms about this point, with probability x,
      // where x is given by the input yaml option or a default of 1.
      double x = 1.0-runOptions->getValueOrDef<double>(1., "probability_of_validity");
      if (Random::draw() < x)
      {
        invalid_point().raise("I don't like this point.");
      }

      // Artificially slow down likelihood evaluations
      // Important for debugging new scanner plugins.
      double eval_time = runOptions->getValueOrDef<double>(-1, "eval_time"); // Measured in seconds
      //std::cout << "eval_time:" << eval_time <<std::endl;
      if(eval_time>0)
      {
         struct timespec sleeptime;
         sleeptime.tv_sec = floor(eval_time);
         sleeptime.tv_nsec = floor((eval_time-floor(eval_time))*1e9); // Allow user to choose fractions of second
         //std::cout << "Sleeping for "<<sleeptime.tv_sec<<" seconds and "<<sleeptime.tv_nsec<<" nanoseconds" <<std::endl;
         nanosleep(&sleeptime,NULL);
      }

      // Example use of suspicious point exception with a 1% chance, specifying message, integer code and whether to print to cout
      if (Random::draw() < 0.01)
      {
        Suspicious_point_exception().raise("This is a demo for using suspicious points.",66,true);
      }

      result = loglTotal;
    }


    /// \name Loopmanager Examples
    /// Some example functions for using loops within the dependency structure
    /// @{


    /// Run a fake 'event loop'
    void eventLoopManager()
    {
      using namespace Pipes::eventLoopManager;
      unsigned int nEvents = 200;         // Number of times to run the loop

      //There are three things available from the Loops namespace in loop managers like this one:
      //  Loop::executeIteration(int iteration_number) -- executes a single iteration of the ordered
      //                                                  set of nested functions, passing them the iteration_number.
      //  Loop::done -- boolean flag indicating if the loop should terminate or not
      //  Loop::reset() -- reset the 'done' flag

      //A simple loop example without OpenMP.  Commented out for now.
      //unsigned int nEvents = 20;       // Number of times to run the loop
      //for(unsigned long it = 0; it < nEvents; it++)
      //{
      //  cout << "This is iteration " << it+1 << " of " << nEvents << " being run by eventLoopManager." << endl;
      //  Loop::executeIteration(it);    // This is a (member) function pointer, so *Loop::executeIteration(it) works fine too.
      //}

      logger() << "Running eventLoopManager" << EOM;

      //A simple loop example using OpenMP
      unsigned int it = 0;
      Loop::executeIteration(it);         //Do the zero iteration separately to allow nested functions to self-init.
      #pragma omp parallel
      {
        while(not *Loop::done and it<nEvents and not piped_errors.inquire())
        { Loop::executeIteration(it++); }
      }
      // Raise any piped exceptions that occurred in the loop functors
      piped_warnings.check(ExampleBit_A_warning());
      piped_errors.check(ExampleBit_A_error());

      // Start over again, just to demonstrate the reset function.  This just sets the Loop::done flag
      // false again.  Note that when you do this, you need to beware to re-initialise the nested functions themselves
      // by re-running iteration zero again, unless you want them to just set Loop::done true again straight away.
      std::cout << "Resetting loop!" << std::endl;
      it = 0;
      Loop::reset();
      Loop::executeIteration(it);         //Do the zero iteration separately to allow nested functions to self-init.
      #pragma omp parallel
      {
        while(not *Loop::done and it<nEvents and not piped_errors.inquire())
        { Loop::executeIteration(it++); }
      }

      //Do the final iteration separately to make the final result 'serially accessible' to functions that run after this one.
      Loop::executeIteration(it++);

    }

    /// Produces a random floating-point 'event count' between 0 and 5.
    void exampleEventGen(float &result)
    {
      using namespace Pipes::exampleEventGen;
      result = Random::draw()*5.0;                 // Generate and return the random number

      // Print some diagnostic info
      //#pragma omp critical (print)
      //{
      //  cout<<"  Running exampleEventGen in iteration "<<*Loop::iteration<<endl;
      //}

      // Test MPI shutdown on random failure
      // if(result<0.0001*5.0) // shut down with 0.01% probability
      // {
      //   // Don't raise errors like this when inside a looped region:
      //   //   ExampleBit_A_error().raise(LOCAL_INFO,"Error triggered for testing purposes.");
      //   // Must raise them like this instead:
      //   piped_errors.request(LOCAL_INFO, "Error triggered for testing purposes.");
      // }

      // Test loggers during parallel block
      logger() << "Thread "<<omp_get_thread_num()<<": Running exampleEventGen in iteration "<<*Loop::iteration<<EOM;

      //if (result > 2.0) invalid_point().raise("This point is annoying.");
    }

    /// Rounds an event count to the nearest integer
    void exampleCut(int &result)
    {
      static bool first = true;
      using namespace Pipes::exampleCut;
      result = (int) *Dep::event;
      logger()<<"  Running exampleCut in iteration "<<*Loop::iteration<<endl;
      if (first)
      {
        cout << "exampleCut has the following dependees: " << endl;
        for (auto x : *Downstream::dependees) { cout << "  " << x << endl; }

        cout << "and the following subcaps: " << endl;
        cout << "  " << Downstream::subcaps->getNames() << endl;

        str s1 = (Downstream::neededFor("eventAccumulation") ? " " : " not ");
        str s2 = (Downstream::neededFor("xsection") ? " " : " not ");
        cout << "It is" << s1 << "needed for eventAccumulation." << endl;
        cout << "It is" << s2 << "needed for xsection." << endl;
        first = false;
      }
    }

    /// Adds an integral event count to a total number of accumulated events.
    void eventAccumulator(int &result)
    {
      //There are basically just two things available in nested functions from the Loops namespace:
      //  int* Loop::iteration -- the iteration number passed down directly by the function managing the loop that this one runs within.
      //  void Loop::wrapup()  -- a function to call if you want to cause the loop to end.
      //You can always get at OpenMP functions too (omp_get_thread_num, omp_get_ancestor_thread_num, etc) -- but it is better not to assume
      //too much about the other functions that might be managing this one, either directly or indirectly.

      using namespace Pipes::eventAccumulator;

      // Do the actual computations in each thread seperately
      int increment = *Dep::event + 1;

      // Only let one thread at a time mess with the accumulator.
      #pragma omp critical (eventAccumulator_update)
      {
        static int accumulatedCounts = 0;
        // In the first iteration of a loop
        if (*Loop::iteration == 0)
        {
          // Zero the total accumulated counts
          accumulatedCounts = 0;
        }
        else
        {
          // Add the latest event count to the total
          accumulatedCounts += increment;
        }
        // Return the current total
        result = accumulatedCounts;
      }

      // Print some diagnostic info
      //#pragma omp critical (print)
      //{
      //  cout<<"  Running eventAccumulator in iteration "<<*Loop::iteration<<endl;
      //  cout<<"  Retrieved event count: "<<*Dep::event<<endl;
      //  cout<<"  I have thread index: "<<omp_get_thread_num()<<endl;
      //  cout<<"  Current total counts is: "<<result<<endl;
      //}

      // If we have reached 50 counts, quit the loop.
      if (result >= 50) { Loop::wrapup(); }

    }

    void do_Farray_stuff (double &result)
    {
      using namespace Pipes::do_Farray_stuff;
      using std::cout;
      using std::endl;
      libFarrayTest_CB_type  *commonBlock  = BEreq::libFarrayTestCommonBlock.pointer();
      libFarrayTest_CB2_type *commonBlock2 = BEreq::libFarrayTestCommonBlock2.pointer();
      libFarrayTest_CB3_type *commonBlock3 = BEreq::libFarrayTestCommonBlock3.pointer();

      cout << "do_Farray_stuff has been summoned!" << endl;
      cout << "Ph'nglui mglw'nafh Cthulhu R'lyeh wgah'nagl fhtagn" << endl;
      cout << "Calling fillArrays to reset array contents" << endl;
      BEreq::libFarrayTest_fillArrays();
      cout << "Calling printStuff..." << endl;
      BEreq::libFarrayTest_printStuff();
      cout << "Setting d(2,0,-1) = 99 and d(1,1,0) = 77 " << endl;
      commonBlock->d(2,0,-1) = 99;
      commonBlock->d(1,1,0) = 77;
      cout << "Calling printStuff again..." << endl;
      BEreq::libFarrayTest_printStuff();

      // Using pointers here is not necessary
      cout << endl << "Retrieving pointer to doubleFuncArray..." << endl;
      Fdouble(*function_pointer)(Farray< Fdouble,1,3>&) = BEreq::libFarrayTest_doubleFuncArray.pointer();
      cout << "Calling doubleFuncArray with commonblock element b as argument..." << endl;
      // Passing farray to Fortran function
      double tmp = function_pointer(commonBlock->b);
      cout << "Returned value: " << tmp << endl;

      // Example on how to pass an farray to a Fortran function that is declared to take Fdouble* instead of Farray< Fdouble,1,3>&
      // This should only be necessary in very special cases, where you need to pass arrays with different index ranges than those specified in the function.
      cout << "Calling doubleFuncArray2 with commonblock element b as argument..." << endl;
      tmp = BEreq::libFarrayTest_doubleFuncArray2(&(commonBlock->b.array[0]));
      cout << "Returned value: " << tmp << endl;

      cout << endl << "Calling fptrRoutine with commonblock elements b and c and function doubleFuncArray as arguments..." << endl;
      BEreq::libFarrayTest_fptrRoutine(commonBlock->b,commonBlock->c,byVal(function_pointer));
      // Note: byVal is necessary to convert lvalue to rvalue
      // If we instead pass BEreq::libFarrayTest_doubleFuncArray2.pointer() directly, byVal is not necessary
      //cout << endl << "Calling fptrRoutine with commonblock elements b and c and function doubleFuncArray as arguments..." << endl;
      //BEreq::libFarrayTest_fptrRoutine(commonBlock->b.array,commonBlock->c,BEreq::libFarrayTest_doubleFuncArray2.pointer());

      cout << "Creating a 2-dimensional array in c++ and passing it to Fortran:" << endl;
      Farray<double, 1,2, 2,3> arr;
      arr(1,2) = 12;
      arr(1,3) = 13;
      arr(2,2) = 22;
      arr(2,3) = 23;
      tmp = BEreq::libFarrayTest_doubleFuncArray3(arr);
      cout << "Return value: " << tmp << endl << endl;

      cout << "Playing around with commmonBlock2:" << endl;

      cout << "Reading charb(3) with and without trailing spaces. Result:" << endl;
      std::string trail   = commonBlock2->charb(3)->str();
      std::string noTrail = commonBlock2->charb(3)->trimmed_str();
      cout << trail   << "<-- string ends here" << endl;
      cout << noTrail << "<-- string ends here" << endl << endl;

      cout << "Reading the elements of charc from c++:" << endl;
      cout << "(1,-1):" << commonBlock2->charc(1,-1)->trimmed_str() << "  (1,0):" << commonBlock2->charc(1,0)->trimmed_str() << endl;
      cout << "(2,-1):" << commonBlock2->charc(2,-1)->trimmed_str() << "  (2,0):" << commonBlock2->charc(2,0)->trimmed_str() << endl << endl;

      cout << "Setting charc(2,0) = chara." << endl;
      *commonBlock2->charc(2,0)=commonBlock2->chara;
      cout << "Setting charc(1,-1) = \"WIN!567\", which will be truncated." << endl;
      *commonBlock2->charc(1,-1) = "WIN!567";
      cout << "Setting charb(1) = \"ha!\"." << endl;
      *commonBlock2->charb(1) = "ha!";
      cout << "Setting charb(2) = chara." << endl;
      *commonBlock2->charb(2) = commonBlock2->chara;

      cout << "Calling printStuff..." << endl;
      BEreq::libFarrayTest_printStuff();

      cout << "Getting value of e:" << endl;
      cout << commonBlock2->e << endl << endl;

      cout << "Reading complex numbers from Fortran: " << commonBlock3->cpa.re << " + " << commonBlock3->cpa.im << "i" << endl;
      cout << "Reading complex numbers from Fortran: " << commonBlock3->cpb.re << " + " << commonBlock3->cpb.im << "i" << endl;
      cout << "f from commonblock3 = " << commonBlock3->f << endl;

      result = 1.0;

    }

    /// @}

    /// Scale test for various aspects of the printer buffer system
    /// Creates 1000 items to be printed per point
    void large_print(std::map<std::string,double>& result)
    {
        for(int i=0; i<1000; i++)
        {
            std::stringstream ss;
            ss<<i;
            result[ss.str()] = i;
        }
    }

    /// Test inline marginalisation of a Poisson likelihood over a log-normally or Gaussianly-distributed nuisance parameter.
    void marg_poisson_test(double &result)
    {
        using namespace Pipes::marg_poisson_test;
        int n_obs = 5;                      // Actual observed number of events
        double n_predicted_exact = 1.5;     // A contribution to the predicted number of events that is know exactly (e.g. from data-driven background estimate)
        double n_predicted_uncertain = 3.1; // A contribution to the predicted number of events that is not know exactly
        double uncertainty = 0.2;           // A fractional uncertainty on n_predicted_uncertain (e.g. 0.2 from 20% uncertainty on efficencty wrt signal events)

        if (*BEgroup::lnlike_marg_poisson == "lnlike_marg_poisson_lognormal_error")
        {
          // Use a log-normal distribution for the nuisance parameter (more correct)
          result = BEreq::lnlike_marg_poisson_lognormal_error(n_obs,n_predicted_exact,n_predicted_uncertain,uncertainty);
        }
        else if (*BEgroup::lnlike_marg_poisson == "lnlike_marg_poisson_gaussian_error")
        {
          // Use a Gaussian distribution for the nuisance parameter (marginally faster)
          result = BEreq::lnlike_marg_poisson_gaussian_error(n_obs,n_predicted_exact,n_predicted_uncertain,uncertainty);
        }
        else ExampleBit_A_error().raise(LOCAL_INFO,"Unrecognised choice from lnlike_marg_poisson BEgroup.");

        logger() << "This is marg_poisson_test using req " << *BEgroup::lnlike_marg_poisson << ". My result is " << result << EOM;
    }


    /// Example of using a BOSSed version of Pythia
    void bossed_pythia_test_function(bool &result)
    {
      using namespace Pipes::bossed_pythia_test_function;

      cout << "Testing Pythia backend" << endl;
      cout << "======================" << endl;

      static str default_doc_path = GAMBIT_DIR "/Backends/installed/Pythia/" +
                                    Backends::backendInfo().default_version("Pythia") +
                                    "/share/Pythia8/xmldoc/";

      Pythia_default::Pythia8::Pythia pythia(default_doc_path, false);

      pythia.readString("Beams:eCM = 8000.");
      pythia.readString("HardQCD:all = on");
      pythia.readString("PhaseSpace:pTHatMin = 20.");

      pythia.readString("Next:numberShowInfo = 0");
      pythia.readString("Next:numberShowProcess = 0");
      pythia.readString("Next:numberShowEvent = 0");

      pythia.init();

      Pythia_default::Pythia8::Hist mult("charged multiplicity", 2, -0.5, 799.5);
      // Begin event loop. Generate event. Skip if error. List first one.
      for (int iEvent = 0; iEvent < 2; ++iEvent) {
        if (!pythia.next()) continue;
        // Find number of all final charged particles and fill histogram.
        int nCharged = 0;
        for (int i = 0; i < pythia.event.size(); ++i)
          if (pythia.event[i].isFinal() && pythia.event[i].isCharged())
            ++nCharged;
        mult.fill( nCharged );
        cout << "Event: " << iEvent << "   nCharged: " << nCharged << endl;
      // End of event loop. Statistics. Histogram. Done.
      }

      pythia.stat();

      cout << "Done testing Pythia backend" << endl;
      cout << "===========================" << endl;

      result = true;
    }


    /// Tester for C/C++ backend array interfaces
    void Backend_array_test(double &result)
    {
      using namespace Pipes::Backend_array_test;
      double arr1D[10], arr2D[10][10], arr3D[10][10][10];
      arr1D[0] = 5;
      arr1D[9] = 2;
      arr2D[0][0] = 5;
      arr2D[9][0] = 2;
      arr2D[9][9] = 3;
      arr3D[0][0][0] = 5;
      arr3D[9][0][0] = 2;
      arr3D[9][9][9] = 8;
      double test1 = BEreq::example_be_array_1D(&arr1D[0]);
      cout << "TEST 1 in array_test: " << test1 << endl;
      double test2 = BEreq::example_be_array_2D(&arr2D[0]);
      cout << "TEST 2 in array_test: " << test2 << endl;
      double test3 = BEreq::example_be_array_3D(&arr3D[0]);
      cout << "TEST 3 in array_test: " << test3 << endl;
      result = test3;
    }

    /// Flat test likelihood for checking prior distributions
    void flat_likelihood(double &result){ result = 1; }

    /// @}
  }

}
