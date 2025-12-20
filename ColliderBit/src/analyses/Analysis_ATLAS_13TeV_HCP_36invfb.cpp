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
//#include "gambit/ColliderBit/analyses/AnalysisMacros.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"
#include "gambit/ColliderBit/analyses/Cutflow.hpp"


using namespace std;

namespace Gambit
{
  namespace ColliderBit
  {

    class Analysis_ATLAS_13TeV_HCP_36invfb : public Analysis
    {

    private:

      // Cut-flows
      size_t NCUTS;
      vector<int> cutFlowVector;
      vector<string> cutFlowVector_str;
      vector<double> cutFlowVectorATLAS;

    public:
      
      // Required detector sim
      static constexpr const char* detector = "ATLAS";

      Analysis_ATLAS_13TeV_HCP_36invfb()
      {

        set_analysis_name("ATLAS_13TeV_HCP_36invfb");
        set_luminosity(36.1);
        
        NCUTS=3;
        for(size_t i=0;i<NCUTS;i++){
          cutFlowVector.push_back(0);
          cutFlowVectorATLAS.push_back(0);
          cutFlowVector_str.push_back("");
        }

      }

    protected:
      // Signal region map
      std::map<string, EventCounter> _counters = {
        // Counters for the number of accepted events for each signal region
        {"SR-1Cand-mTOF175", EventCounter("SR-1Cand-mTOF175")},
        {"SR-1Cand-mTOF375", EventCounter("SR-1Cand-mTOF375")},
        {"SR-1Cand-mTOF600", EventCounter("SR-1Cand-mTOF600")},
        {"SR-1Cand-mTOF825", EventCounter("SR-1Cand-mTOF825")},

        {"SR-2Cand-mTOF150", EventCounter("SR-2Cand-mTOF150")},
        {"SR-2Cand-mTOF350", EventCounter("SR-2Cand-mTOF350")},
        {"SR-2Cand-mTOF575", EventCounter("SR-2Cand-mTOF575")},
        {"SR-2Cand-mTOF800", EventCounter("SR-2Cand-mTOF800")},
      };

      
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
        
        // Trigger for missing energy
        if (met > 110) trigger = true;
          
        // TODO: Trigger for track

        // TODO: Count up tight and loose

        // If it has reached this point, it has passed pre-selection
        if (trigger) presel = true;

        
        // If event does not pass pre-selection, exit early
        if (presel == false) return;
        
        
        //
        // Signal regions
        //
        
        double mTOF = 0;
        
        // SR with 1 tight candidate
        while (true)
        {
          if (nTight == 1) cutFlowVector[1]++;
          else break;
          
          if (mTOF > 175) _counters.at("SR-1Cand-mTOF175").add_event(event);
          if (mTOF > 375) _counters.at("SR-1Cand-mTOF375").add_event(event);
          if (mTOF > 600) _counters.at("SR-1Cand-mTOF600").add_event(event);
          if (mTOF > 825) _counters.at("SR-1Cand-mTOF825").add_event(event);
          
          // Applied all cuts
          break;
        }
        
        // SR with 2 loose candidates
        while (true)
        {
          if (nLoose == 2) cutFlowVector[2]++;
          else break;
          
          if (mTOF > 150) _counters.at("SR-2Cand-mTOF150").add_event(event);
          if (mTOF > 350) _counters.at("SR-2Cand-mTOF350").add_event(event);
          if (mTOF > 575) _counters.at("SR-2Cand-mTOF575").add_event(event);
          if (mTOF > 800) _counters.at("SR-2Cand-mTOF800").add_event(event);
          
          // Applied all cuts
          break;
        }

      } // End run function


      /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
      void combine(const Analysis* other)
      {
        const Analysis_ATLAS_13TeV_HCP_36invfb* specificOther
          = dynamic_cast<const Analysis_ATLAS_13TeV_HCP_36invfb*>(other);

        for (auto& pair : _counters) { pair.second += specificOther->_counters.at(pair.first); }

        if (NCUTS != specificOther->NCUTS) NCUTS = specificOther->NCUTS;
        for (size_t j=0; j<NCUTS; j++) {
          cutFlowVector[j] += specificOther->cutFlowVector[j];
          cutFlowVector_str[j] = specificOther->cutFlowVector_str[j];
        }
      }

      // This function can be overridden by the derived SR-specific classes
      virtual void collect_results()
      {
        
        cout << "CUTFLOW" << endl;
        double L = 36.1;
        double xsec = 3.460;
        for (size_t i=0; i<NCUTS; i++)
        {
          double ATLAS_abs = cutFlowVectorATLAS[i];
          double eff = (double)cutFlowVector[i] / (double)cutFlowVector[0];
          double GAMBIT_scaled = eff * xsec * L;
          double ratio = GAMBIT_scaled/ATLAS_abs;
          cout << "CUTFLOW " << i << ":   " << setprecision(4) << ATLAS_abs << "\t" << GAMBIT_scaled << "\t" << "\t" << ratio << "\t\t" << cutFlowVector_str[i] << endl;
        }
        cout << "CUTFLOW" << endl;

        add_result(SignalRegionData(_counters.at("SR-1Cand-mTOF175"), 227, {240,     20}));
        add_result(SignalRegionData(_counters.at("SR-1Cand-mTOF175"),  16, { 17,      2}));
        add_result(SignalRegionData(_counters.at("SR-1Cand-mTOF175"),   1, {  2.2,    0.2}));
        add_result(SignalRegionData(_counters.at("SR-1Cand-mTOF175"),   0, {  0.48,   0.07}));
        add_result(SignalRegionData(_counters.at("SR-2Cand-mTOF150"),   0, {  1.5,    0.3}));
        add_result(SignalRegionData(_counters.at("SR-2Cand-mTOF350"),   0, {  0.06,   0.01}));
        add_result(SignalRegionData(_counters.at("SR-2Cand-mTOF575"),   0, {  0.007,  0.002}));
        add_result(SignalRegionData(_counters.at("SR-2Cand-mTOF800"),   0, {  0.0017, 0.0009}));

      }

      void analysis_specific_reset()
      {
        // Clear signal regions
        for (auto& pair : _counters)
        {
          pair.second.reset();
        }
        
        // Clear cut flow vector
        std::fill(cutFlowVector.begin(), cutFlowVector.end(), 0);
      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(ATLAS_13TeV_HCP_36invfb)

  }
}

