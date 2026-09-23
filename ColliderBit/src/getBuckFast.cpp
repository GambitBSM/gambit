//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  ColliderBit event loop functions returning
///  detector simulations.
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
#include "gambit/ColliderBit/Utils.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"
#include "gambit/ColliderBit/CMSEfficiencies.hpp"
#include "gambit/ColliderBit/detectors/BuckFast.hpp"

namespace Gambit
{

  namespace ColliderBit
  {
    namespace
    {
      std::vector<std::string> get_vr_jetcollections_no_smear(const Options& runOptions, const str& current_collider)
      {
        std::lock_guard<std::recursive_mutex> lock(jet_collection_options_mutex());

        if (runOptions.hasKey("jet_collections"))
        {
          return vr_jetcollection_keys(read_jet_collection_settings_from_options(runOptions).collections);
        }

        if (runOptions.hasKey(current_collider))
        {
          YAML::Node colNode = runOptions.getValue<YAML::Node>(current_collider);
          Options colOptions(colNode);
          if (colOptions.hasKey("jet_collections"))
          {
            return vr_jetcollection_keys(read_jet_collection_settings_from_options(colOptions).collections);
          }
        }

        return {};
      }
    }

    /// Retrieve a BuckFast sim of ATLAS
    void getBuckFastATLAS(BaseDetector* &result)
    {
      using namespace Pipes::getBuckFastATLAS;
      thread_local BuckFast bucky;
      if (*Loop::iteration == START_SUBPROCESS)
      {
        bucky.smearElectronEnergy = &ATLAS::smearElectronEnergy;
        bucky.smearMuonMomentum   = &ATLAS::smearMuonMomentum;
        bucky.smearTaus           = &ATLAS::smearTaus;
        bucky.smearJets           = &ATLAS::smearJets;
        bucky.jetcollections_no_smear = get_vr_jetcollections_no_smear(*runOptions, (*Dep::RunMC).current_collider());
        result = &bucky;
      }
    }

    /// Retrieve a BuckFast sim of CMS
    void getBuckFastCMS(BaseDetector* &result)
    {
      using namespace Pipes::getBuckFastCMS;
      thread_local BuckFast bucky;
      if (*Loop::iteration == START_SUBPROCESS)
      {
        bucky.smearElectronEnergy = &CMS::smearElectronEnergy;
        bucky.smearMuonMomentum   = &CMS::smearMuonMomentum;
        bucky.smearTaus           = &CMS::smearTaus;
        bucky.smearJets           = &CMS::smearJets;
        bucky.jetcollections_no_smear = get_vr_jetcollections_no_smear(*runOptions, (*Dep::RunMC).current_collider());
        result = &bucky;
      }
    }

    /// Retrieve an Identity BuckFast sim (no sim)
    void getBuckFastIdentity(BaseDetector* &result)
    {
      using namespace Pipes::getBuckFastIdentity;
      thread_local BuckFast bucky;
      if (*Loop::iteration == START_SUBPROCESS)
      {
        bucky.jetcollections_no_smear = get_vr_jetcollections_no_smear(*runOptions, (*Dep::RunMC).current_collider());
      }
      result = &bucky;
    }

  }

}
