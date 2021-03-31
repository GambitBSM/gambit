//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file HiggsSignals.cpp
///
///  Frontend source for the HiggsSignals backend.
///
///  Actual implementation of HiggsSignals ini function.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Christopher S. Rogan
///          (crogan@cern.ch)
///  \date 2015 Sept
///
///  *********************************************

#include "gambit/Backends/frontend_macros.hpp"
#include "gambit/Backends/backend_singleton.hpp"
#include "gambit/Backends/frontends/HiggsSignals_1_4.hpp"
#include "gambit/Utils/file_lock.hpp"
#include "gambit/Backends/frontend_macros.hpp"
#include "gambit/Core/cleanup.hpp"

BE_INI_FUNCTION
{

  static bool scan_level = true;
  if(scan_level)
  {
    int nHneut = 3; // number of neutral higgses
    int nHplus = 1; // number of charged higgses
    int pdf = 2;    // choose which pdf style to use for Higgs lineshape; 2 = Gaussian
    // Initialize HiggsSignals. Do this one-by-one for each MPI process with
    // locks, as HS calls HB, which writes files then reads them back in later (crazy).
    // Note that this is the Higgs*Bounds* lock, as in the HiggsBounds ini function,
    // because we need to make sure that neither this function nor the HB ini function
    // run at the same time, beccause both of them cause the HiggsBounds files to be
    // written.

    // Find all the versions of HiggsBounds that have been successfully loaded, and get
    // their locks.
    std::vector<str> hbversions = Backends::backendInfo().working_safe_versions("HiggsBounds");
    std::vector<Utils::ProcessLock*> mylocks;
    for (auto it = hbversions.begin(); it != hbversions.end(); ++it)
    {
      mylocks.push_back(new Utils::ProcessLock("HiggsBounds_" + *it + "_init"));
      mylocks.back()->get_lock();
    }

    // initialize HiggsSignals with the latest results (or custom experimental table) and set pdf shape
    const int clen = 100; // Fixed string length
    char Expt_string[clen];
    Utils::strcpy2f(Expt_string, clen, runOptions->getValueOrDef<std::string>("latestresults", "HS_Expt_string"));
    std::cout << "(HS DEBUG) Input filename (C++ string): " << runOptions->getValueOrDef<std::string>("latestresults", "HS_Expt_string") << " (strcpy2f Fortran string): " << Expt_string << std::endl;
    initialize_HiggsSignals(nHneut,nHplus,Expt_string);
    setup_pdf(pdf);
    ::Gambit::cleanup::register_cleanup_function("finish_HiggsSignals", []() { finish_HiggsSignals(); });

    for (auto it = mylocks.begin(); it != mylocks.end(); ++it)
    {
      (*it)->release_lock();
      delete *it;
    }
    scan_level = false;
  }

}
END_BE_INI_FUNCTION
