///
///  Search for long-lived Heavy Charged Particles
///
///  Based on https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/PAPERS/SUSY-2016-32
///
///  \author Are Raklev
///  \date 2025 Dec
///
///  This currently uses only the SR-1Cand-FullDet and SR-2Cand-FullDet signal regions
///
///  *********************************************



#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>
#include <algorithm>
#include <fstream>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/analyses/AnalysisMacros.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"
#include "gambit/ColliderBit/analyses/Cutflow.hpp"
//#include "gambit/ColliderBit/mt2_bisect.h"
//#include "METSignificance/METSignificance.hpp"

using namespace std;

namespace Gambit
{
  namespace ColliderBit
  {

    class Analysis_ATLAS_13TeV_HCP_36invfb : public Analysis
    {

    public:

      // Required detector sim
      static constexpr const char* detector = "ATLAS";

      Analysis_ATLAS_13TeV_HCP_36invfb()
      {

        set_analysis_name("ATLAS_13TeV_HCP_36invfb");
        set_detector_name(detector);
        set_luminosity(36.1);
        set_bkgjson("ColliderBit/data/analyses_json_files/ATLAS_13TeV_2LEPJETS_EW_139invfb_full_bkgonly.json");

        // Counters for the number of accepted events for each signal region
        DEFINE_SIGNAL_REGION("SR-1Cand-mTOF175", "n tight = 1")
        DEFINE_SIGNAL_REGION("SR-1Cand-mTOF375", "n tight = 1")
        DEFINE_SIGNAL_REGION("SR-1Cand-mTOF600", "n tight = 1")
        DEFINE_SIGNAL_REGION("SR-1Cand-mTOF825", "n tight = 1")
        
        DEFINE_SIGNAL_REGION("SR-2Cand-mTOF150", "n loose = 2")
        DEFINE_SIGNAL_REGION("SR-2Cand-mTOF350", "n loose = 2")
        DEFINE_SIGNAL_REGION("SR-2Cand-mTOF575", "n loose = 2")
        DEFINE_SIGNAL_REGION("SR-2Cand-mTOF800", "n loose = 2")
      }

      void run(const HEPUtils::Event* event)
      {
        //
        // Define objects
        //
        
        // TODO: Do we want jets for overlap removal or not?
        // Baseline objects
        vector<const HEPUtils::Jet*> baselineJets;
        for (const HEPUtils::Jet* jet : event->jets("antikt_R04"))
        {
          if (jet->pT()>20. && jet->abseta()<2.8)
          {
             baselineJets.push_back(jet);
          }
        }

        // TODO: Put basline HCP candidates here
        
        // Missing momentum and energy
        HEPUtils::P4 metVec = event->missingmom();
        double met = event->met();

        // Overlap removal
        // Remove jets within DeltaR = 0.05 of electron
        //removeOverlap(baselineJets, baselineElectrons, 0.05);

        // Signal objects
        vector<const HEPUtils::Jet*> signalJets;
 
        
        //
        // Preselection
        //
        
        // True if passes this cut, false otherwise
        bool presel = false; // Total Pre-selection cut

        // Initialise some useful variables
        bool trigger = false;
        int nLoose = 0;
        int nTight = 0;

        // Perform all pre-selection cuts
        BEGIN_PRESELECTION
        while(true)
        {
          // Trigger for missing energy
          if (met > 110) trigger = true;
          
          // TODO: Trigger for track

          // TODO: Count up tight and loose
          

          // If it has reached this point, it has passed pre-selection
          if (trigger) presel = true;

          // Applied all cuts
          break;
        }

        // If event does not pass pre-selection, exit early
        if (presel == false) return;
        END_PRESELECTION

        
        //
        // Signal regions
        //
        
        double mTOF = 0;
        
        // SR with 1 tight candidate
        while (true)
        {
          if (nTight == 1) { LOG_CUT("Tight1") }
          else break;
          
          if (mTOF > 175) FILL_SIGNAL_REGION("SR-1Cand-mTOF175");
          if (mTOF > 375) FILL_SIGNAL_REGION("SR-1Cand-mTOF375");
          if (mTOF > 600) FILL_SIGNAL_REGION("SR-1Cand-mTOF600");
          if (mTOF > 825) FILL_SIGNAL_REGION("SR-1Cand-mTOF825");
          
          // Applied all cuts
          break;
        }
        
        // SR with 2 loose candidates
        while (true)
        {
          if (nLoose == 2) { LOG_CUT("Loose2") }
          else break;
          
          if (mTOF > 150) FILL_SIGNAL_REGION("SR-2Cand-mTOF150");
          if (mTOF > 350) FILL_SIGNAL_REGION("SR-2Cand-mTOF350");
          if (mTOF > 575) FILL_SIGNAL_REGION("SR-2Cand-mTOF575");
          if (mTOF > 800) FILL_SIGNAL_REGION("SR-2Cand-mTOF800");
          
          // Applied all cuts
          break;
        }

      } // End run function


      // This function can be overridden by the derived SR-specific classes
      virtual void collect_results()
      {
        COMMIT_SIGNAL_REGION("SR-1Cand-mTOF175", 227, 240,     20);
        COMMIT_SIGNAL_REGION("SR-1Cand-mTOF375",  16,  17,      2);
        COMMIT_SIGNAL_REGION("SR-1Cand-mTOF600",   1,   2.2,    0.2);
        COMMIT_SIGNAL_REGION("SR-1Cand-mTOF825",   0,   0.48,   0.07);
        COMMIT_SIGNAL_REGION("SR-2Cand-mTOF150",   0.,  1.5,    0.3);
        COMMIT_SIGNAL_REGION("SR-2Cand-mTOF350",   0.,  0.06,   0.01);
        COMMIT_SIGNAL_REGION("SR-2Cand-mTOF575",   0.,  0.007,  0.002);
        COMMIT_SIGNAL_REGION("SR-2Cand-mTOF800",   0.,  0.0017, 0.0009);

        COMMIT_CUTFLOWS
      }

    protected:
//      void analysis_specific_reset()
//      {
//        for (auto& pair : _counters)
//        {
//          pair.second.reset();
//        }
//      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(ATLAS_13TeV_HCP_36invfb)

  }
}

