//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  ScannerBit interface to Multinest 3.10
///
///  Header file
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ben Farmer
///          (ben.farmer@gmail.com)
///  \date 2015 January
///
///  *********************************************

#ifndef __multinest_hpp__
#define __multinest_hpp__

#include "gambit/ScannerBit/scanner_plugin.hpp"

// Auxilliary classes and functions needed by multinest
// (cloned largely from eggbox.cc, and modified to use cwrapper.f90 interface
//  instead of multinest.h)

// C++ prototypes for the main run function for multinest, as well as the
// loglike and dumper functions
extern "C"
{
        void run(bool, bool, bool, int, double, double, int, int, int, int, int,
                    double, char[], int, int[], bool, bool, bool, bool, double, int,
                    double (*)(double*,int,int,void*),
                    void (*)(int,int,int,double*,double*,double*,double,double,
                      double,void*),
                    void *);
}
//extern "C" double loglike(double*, int, int, void *);
//extern "C" void dumper(int, int, int, double*, double*, double*,
//                       double, double, double, void*);

namespace Gambit
{

   namespace MultiNest
   {

      /// Typedef for the ScannerBit pointer to the external loglikelihood function
      typedef Gambit::Scanner::like_ptr scanPtr;

      /// Bring printer_interface and printer names into this scope
      using Gambit::Scanner::printer_interface;
      using Gambit::Scanner::printer;

      /// Class to connect multinest log-likelihood function and ScannerBit likelihood function
      class LogLikeWrapper
      {
         private:
            /// Scanner pointer (points to the ScannerBit provided log-likelihood function)
            scanPtr boundLogLike;

            /// Reference to a printer_interface object
            printer_interface& boundPrinter;

            /// Variable to indicate whether the dumper function has been run at least once
            bool dumper_runonce;

         public:
            /// Constructor
            LogLikeWrapper(scanPtr, printer_interface&);

            /// Main interface function from MultiNest to ScannerBit-supplied loglikelihood function
            double LogLike(double*, int, int);

            /// Main interface to MultiNest dumper routine
            void dumper(int, int, int, double*, double*, double*, double, double, double);
      };

      ///@{ Plain-vanilla C-functions to pass to Multinest for the callbacks
      // Note: we are using the c interface from cwrapper.f90, so the function
      // signature is a little different than in the multinest examples.
      double callback_loglike(double*, int, int, void*);

      void callback_dumper(int, int, int, double*, double*, double*, double, double, double, void*);
      ///@}

   } // End Multinest namespace

} // End Gambit namespace

#endif
