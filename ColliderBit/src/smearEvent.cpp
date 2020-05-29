//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  ColliderBit event loop functions returning
///  events after detector simulation.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Abram Krislock
///          (a.m.b.krislock@fys.uio.no)
///
///  \author Aldo Saavedra
///
///  \author Andy Buckley
///
///  \author Chris Rogan
///          (crogan@cern.ch)
///  \date 2014 Aug
///  \date 2015 May
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2015 Jul
///  \date 2018 Jan
///  \date 2019 Jan
///
///  \author Anders Kvellestad
///          (anders.kvellestad@fys.uio.no)
///  \date   2017 March
///  \date   2018 Jan
///  \date   2018 May
///
///  *********************************************

#include "gambit/ColliderBit/ColliderBit_eventloop.hpp"

namespace Gambit
{

  namespace ColliderBit
  {

    /// Smear an event
    void smearEvent(HEPUtils::Event& result,
                    const HEPUtils::Event& HardScatteringEvent,
                    const BaseDetector& detector,
                    const MCLoopInfo& RunMC,
                    const int iteration,
                    const str& detname)
    {
      if (iteration <= BASE_INIT or not RunMC.current_analyses_exist_for(detname)) return;
      result.clear();
      HardScatteringEvent.cloneTo(result);
      detector.processEvent(result);
    }

    /// Smear an event using a simulation of EXPERIMENT
    #define SMEAR_EVENT(NAME, EXPERIMENT)                                                \
    void NAME(HEPUtils::Event& result)                                                   \
    {                                                                                    \
      using namespace Pipes::NAME;                                                       \
      smearEvent(result, *Dep::HardScatteringEvent, *(*Dep::CAT(EXPERIMENT,DetectorSim)),\
       *Dep::RunMC, *Loop::iteration, #EXPERIMENT);                                      \
    }

    SMEAR_EVENT(smearEventATLAS, ATLAS)
    SMEAR_EVENT(smearEventCMS, CMS)
    SMEAR_EVENT(copyEvent, Identity)

  }

}
