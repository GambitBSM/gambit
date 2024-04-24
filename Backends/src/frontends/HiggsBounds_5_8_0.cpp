//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file HiggsBounds.cpp
///
///  Frontend source for the HiggsBounds backend.
///
///  Actual implementation of HiggsBounds ini function.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///   
///  \author Christopher S. Rogan
///          (crogan@cern.ch)
///  \date 2015 Sept
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2016 Feb, Aug
///
///  \author Ankit Beniwal
///          (ankit.beniwal@uclouvain.be)
///  \date 2019 Jul
///  \date 2020 Jul
///
///  \author Jonathan Cornell
///          (jonathancornell@weber.edu)
///  \date 2020 Mar
///
///  *********************************************

#include "gambit/Backends/frontend_macros.hpp"
#include "gambit/Backends/frontends/HiggsBounds_5_8_0.hpp"
#include "gambit/Utils/file_lock.hpp"
#include "gambit/Core/cleanup.hpp"

BE_INI_FUNCTION
{

  // Scan-level initialisation
  static bool scan_level = true;
  if(scan_level)
  {
    int nHneut = 3; // number of neutral higgses
    int nHplus = 1; // number of charged higgses
    int ANA = 1;    // indicates LEP-only analysis

    // Initialize HiggsBounds. Do this one-by-one for each MPI process with
    // locks, as HB writes files here then reads them back in later (crazy). 
    Utils::FileLock mylock("HiggsBounds_" STRINGIFY(SAFE_VERSION) "_init");
    mylock.get_lock();
    
    // --braces just for dramatic effect--
    { 
      // initialize LEP chisq tables
      initialize_HiggsBounds_chisqtables();
      ::Gambit::cleanup::register_cleanup_function("finish_HiggsBounds_chisqtables", []() { finish_HiggsBounds_chisqtables(); });

      // initialize HiggsBounds to LEP only
      initialize_HiggsBounds_int(nHneut,nHplus,ANA);
      ::Gambit::cleanup::register_cleanup_function("finish_HiggsBounds", []() { finish_HiggsBounds(); });
    }
    mylock.release_lock();
    scan_level = false;
  }
   
}
END_BE_INI_FUNCTION
