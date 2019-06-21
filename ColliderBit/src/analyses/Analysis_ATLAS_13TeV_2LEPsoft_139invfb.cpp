///
///  \author Tomas Gonzalo
///  \date 2019 June
///  *********************************************

// Based on https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/CONFNOTES/ATLAS-CONF-2019-014/ 

// - 139 fb^-1 data

#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>
#include <algorithm>
#include <fstream>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"
#include "gambit/ColliderBit/analyses/Cutflow.hpp"
#include "gambit/ColliderBit/mt2_bisect.h"

 #define CHECK_CUTFLOW

using namespace std;

namespace Gambit
{
  namespace ColliderBit
  {

    class Analysis_ATLAS_13TeV_2LEPsoft_139invfb : public Analysis
    {

    protected:

      // Counters for the number of accepted events for each signal region
      std::map<string,double> _numSR = {
        {"SRLowMETLowDM", 0},
        {"SRLowMETHighDm", 0},
        {"SRHighMET", 0},
        {"SR1l1T", 0},
      };

       vector<Cutflow> _cutflow;

    private:

      struct ptComparison
      {
        bool operator() (HEPUtils::Particle* i,HEPUtils::Particle* j) {return (i->pT()>j->pT());}
      } comparePt;

      struct ptJetComparison
      {
        bool operator() (HEPUtils::Jet* i,HEPUtils::Jet* j) {return (i->pT()>j->pT());}
      } compareJetPt;


    public:

      // Required detector sim
      static constexpr const char* detector = "ATLAS";

      Analysis_ATLAS_13TeV_2LEPsoft_139invfb()
      {

        set_analysis_name("ATLAS_13TeV_2LEPsoft_139invfb");
        set_luminosity(139);
        
        
//        str cutflow_name = "ATLAS 2 opposite sign leptons at the Z peak 13 TeV";
//        vector<str> SR1A = {"Trigger", "Third leading lepton pT > 20 GeV", "|mll - mZ| < 15 GeV", "nb-tagged (pT > 30 GeV) >= 1", "njets (pT > 30 GeV) >= 4", "MET > 250 GeV", "mT23l > 100 GeV"};
//        vector<str> SR1B = {"Trigger", "Third leading lepton pT > 20 GeV", "|mll - mZ| < 15 GeV", "nb-tagged (pT > 30 GeV) >= 1", "njets (pT > 30 GeV) >= 5", "MET > 150 GeV", "pTll > 150 GeV", "Leading b-tagged jet pT > 100 GeV"};
//        vector<str> SR2A = {"Trigger", "Third leading lepton pT < 20 GeV", "|mll - mZ| < 15 GeV", "Leading jet pT > 150 GeV", "MET > 200 GeV", "pTll < 50 GeV"};
//        vector<str> SR2B = {"Trigger", "Third leading lepton pT < 60 GeV", "|mll - mZ| < 15 GeV", "nb-tagged (pT > 30 GeV) >= 1", "MET > 350 GeV", "pTll > 150 GeV"};
//        _cutflow = { Cutflow(cutflow_name, SR1A),
//                     Cutflow(cutflow_name, SR1B),
//                     Cutflow(cutflow_name, SR2A), 
//                     Cutflow(cutflow_name, SR2B) };

      }

      void run(const HEPUtils::Event* event)
      {

        // Preselected objects
        vector<HEPUtils::Particle*> preselectedElectrons;
//        vector<HEPUtils::Particle*> baselineMuons;
//        vector<HEPUtils::Particle*> baselineTaus;
//        vector<HEPUtils::Jet*> baselineJets;
//        vector<HEPUtils::Jet*> baselineBJets;
//        vector<HEPUtils::Jet*> baselineNonBJets;

        // Missing momentum and energy
        double met = event->met();

        // TODO: Candidate events are required to have at least one reconstructed pp interaction vertex with a minimum of two associated tracks with pT > 500 MeV 
        // TODO: In events with multiple vertices, the primary vertex is defined as the one with the highest sum pT^2 of associated tracks. 
        // Missing: We cannot reject events with detector noise or non-collision backgrounds.

        // Electrons are required to have pT > 4.5 GeV and |η| < 2.47. 
        // Preselected electrons are further required to pass the calorimeter- and tracking-based VeryLoose likelihood identification (arXiv:1902.04655), and to have a longitudinal impact parameter z0 relative to the primary vertex that satisfies |z0 sin θ| < 0.5 mm.
        // Missing: We cannot add cuts relating to impact parameters
        for (HEPUtils::Particle* electron : event->electrons())
        {
          if (electron->pT()>4.5 && electron->abseta()<2.47)  preselectedElectrons.push_back(electron);
        }

        // Apply electron efficiency
        // TODO: Is this needed if below is done
        ATLAS::applyElectronEff(preselectedElectrons);

        // Apply loose electron selection
        // TODO: This is not the same as in the reference. Need the VeryLoose efficiency
        ATLAS::applyLooseIDElectronSelectionR2(preselectedElectrons);

        // Signal objects
        vector<HEPUtils::Particle*> signalElectrons = preselectedElectrons;

        // Signal electrons must satisfy the Medium identification criterion (arXiv:1902.04655), and be compatible with originating from the primary vertex, with the significance of the transverse impact parameter defined relative to the beam position satisfying |d0|/σ(d0) < 5. 
        // Signal electrons are further refined using the Gradient isolation working point (arXiv:1902.04655), which uses both tracking and calorimeter information.
        // Missing: No impact parameter info
        // TODO: Isolation?
        // TODO: Outdated efficiency selection, use newer one (arXiv:1902.04655)
        ATLAS::applyMediumIDElectronSelectionR2(signalElectrons);

      }

      /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
      void combine(const Analysis* other)
      {
        const Analysis_ATLAS_13TeV_2LEPsoft_139invfb* specificOther
                = dynamic_cast<const Analysis_ATLAS_13TeV_2LEPsoft_139invfb*>(other);

        for (auto& el : _numSR)
        {
          el.second += specificOther->_numSR.at(el.first);
        }

      }

      // This function can be overridden by the derived SR-specific classes
      virtual void collect_results()
      {

        // add_result(SignalRegionData("SR label", n_obs, {s, s_sys}, {b, b_sys}));

        #ifdef CHECK_CUTFLOW
          cout << _cutflow << endl;
          for (auto& el : _numSR)
          {
             cout << el.first << "\t" << _numSR[el.first] << endl;
          }
        #endif


      }


    protected:
      void analysis_specific_reset()
      {
        for (auto& el : _numSR) { el.second = 0.;}
      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(ATLAS_13TeV_2LEPsoft_139invfb)


  }
}
