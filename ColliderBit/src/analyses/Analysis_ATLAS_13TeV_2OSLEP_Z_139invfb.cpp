///
///  \author Tomas Gonzalo
///  \date 2019 June
///  *********************************************

// Based on https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/CONFNOTES/ATLAS-CONF-2019-016/

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

// #define CHECK_CUTFLOW

using namespace std;

namespace Gambit
{
  namespace ColliderBit
  {

    class Analysis_ATLAS_13TeV_2OSLEP_Z_139invfb : public Analysis
    {

    protected:

      // Counters for the number of accepted events for each signal region
      std::map<string, EventCounter> _counters = {
        {"SR1A", EventCounter("SR1A")},
        {"SR1B", EventCounter("SR1B")},
        {"SR2A", EventCounter("SR2A")},
        {"SR2B", EventCounter("SR2B")},
      };

       vector<Cutflow> _cutflow;

       //vector<int> _test;
       //int _test2;

    private:

      struct ptComparison
      {
        bool operator() (const HEPUtils::Particle* i,const HEPUtils::Particle* j) {return (i->pT()>j->pT());}
      } comparePt;

      struct ptJetComparison
      {
        bool operator() (const HEPUtils::Jet* i,const HEPUtils::Jet* j) {return (i->pT()>j->pT());}
      } compareJetPt;


    public:

      // Required detector sim
      static constexpr const char* detector = "ATLAS";

      Analysis_ATLAS_13TeV_2OSLEP_Z_139invfb()
      {

        set_analysis_name("ATLAS_13TeV_2OSLEP_Z_139invfb");
        set_luminosity(139);


        str cutflow_name = "ATLAS 2 opposite sign leptons at the Z peak 13 TeV";
        vector<str> SR1A = {"Trigger", "Third leading lepton pT > 20 GeV", "|mll - mZ| < 15 GeV", "nb-tagged (pT > 30 GeV) >= 1", "njets (pT > 30 GeV) >= 4", "MET > 250 GeV", "mT23l > 100 GeV"};
        vector<str> SR1B = {"Trigger", "Third leading lepton pT > 20 GeV", "|mll - mZ| < 15 GeV", "nb-tagged (pT > 30 GeV) >= 1", "njets (pT > 30 GeV) >= 5", "MET > 150 GeV", "pTll > 150 GeV", "Leading b-tagged jet pT > 100 GeV"};
        vector<str> SR2A = {"Trigger", "Third leading lepton pT < 20 GeV", "|mll - mZ| < 15 GeV", "Leading jet pT > 150 GeV", "MET > 200 GeV", "pTll < 50 GeV"};
        vector<str> SR2B = {"Trigger", "Third leading lepton pT < 60 GeV", "|mll - mZ| < 15 GeV", "nb-tagged (pT > 30 GeV) >= 1", "MET > 350 GeV", "pTll > 150 GeV"};
        _cutflow = { Cutflow(cutflow_name, SR1A),
                     Cutflow(cutflow_name, SR1B),
                     Cutflow(cutflow_name, SR2A),
                     Cutflow(cutflow_name, SR2B) };
        //_test = {0,0,0,0,0};
        //_test2 = 0;

      }

      void run(const HEPUtils::Event* event)
      {

        // Baseline objects
        vector<const HEPUtils::Particle*> baselineElectrons;
        vector<const HEPUtils::Particle*> baselineMuons;
        vector<const HEPUtils::Particle*> baselineTaus;
        vector<const HEPUtils::Jet*> baselineJets;
        vector<const HEPUtils::Jet*> baselineBJets;
        vector<const HEPUtils::Jet*> baselineNonBJets;

        // Missing momentum and energy
        HEPUtils::P4 ptot = event->missingmom();
        double met = event->met();

        //if(event->electrons().size() + event->muons().size() >= 3)
        //  _test2++;

        // Initialize cutflow
        for(int i=0; i<4; i++)
          _cutflow[i].fillinit();

        // Electron candidates are reconstructed from isolated electromagnetic calorimeter energy deposits matched to ID tracks and are required to have |η| < 2.47, a transverse momentum pT > 4.5 GeV, and to pass the “LooseAndBLayer” requirement in arXiv: 1902.04655 [hep-ex].
        for (const HEPUtils::Particle* electron : event->electrons())
        {
          if (electron->pT()>4.5 && electron->abseta()<2.47) baselineElectrons.push_back(electron);
        }

        // Apply electron efficiency
        // Loose electron ID selection
        ATLAS::applyElectronIDEfficiency2019(baselineElectrons, "Loose");

        // Muon candidates are reconstructed in the region |η| < 2.4 from muon spectrometer tracks matching ID tracks. Candidate muons must have pT > 4 GeV and pass the medium identification requirements defined in arXiv: 1603.05598 [hep-ex].
        for (const HEPUtils::Particle* muon : event->muons())
        {
          if (muon->pT()>4. && muon->abseta()<2.4) baselineMuons.push_back(muon);
        }

        // Apply muon efficiency
        // Missing: "Medium" muon ID criteria
        ATLAS::applyMuonEff(baselineMuons);

        // Missing: transverse and longitudinal impact parameter cuts


        // Only jet candidates with pT > 20 GeV and |η| < 2.8 are considered in the analysis
        // Jets with pT < 120 GeV and |η| < 2.8 have an efficiency of 90%
        // Mising:  cut based on detector noise and non-collision backgrounds
        double jet_eff = 0.9;
        for (const HEPUtils::Jet* jet : event->jets())
        {
          if (jet->pT()>20. && jet->abseta()<2.8)
            if( (jet->pT() >= 120. || jet->abseta() >= 2.5) || random_bool(jet_eff) ) baselineJets.push_back(jet);
        }

        // Overlap removal

        // 1) Remove jets within DeltaR = 0.2 of electron
        // If b-tagging efficiency > 85%, do not remove jet. The lepton will be removed anyway.
        removeOverlap(baselineJets, baselineElectrons, 0.2, false, 200, 0.85);

        // 3) Remove jets within DeltaR = 0.2 of a muon
        removeOverlap(baselineJets, baselineMuons, 0.2, false, DBL_MAX, 0.85);

        // 2) Remove electrons within DeltaR = 0.4 of a jet
        removeOverlap(baselineElectrons, baselineJets, 0.4);

        // 4) Remove muons within DeltaR = 0.4 of jet
        // Use lambda function to remove overlap with DeltaRMax as min(0.4, 0.04 + pT(µ)/10 GeV)
        // Missing: Remove the jet instead if the jet has fewer than 3 associated tracks
        auto lambda = [](double muonpT) { return std::min(0.4, 0.04 + muonpT/10.); };
        removeOverlap(baselineMuons, baselineJets, lambda);

        // 5) Remove electron candidates sharing and ID track with a muon candidate
        // Missing: No track information

        // Find b-jets
        // Copied from ATLAS_13TeV_3b_24invfb
        double btag = 0.77; double cmisstag = 1/16.; double misstag = 1./113.;
        for (const HEPUtils::Jet* jet : baselineJets) {
          // Tag
          if( jet->btag() && random_bool(btag) ) baselineBJets.push_back(jet);
          // Misstag c-jet
          else if( jet->ctag() && random_bool(cmisstag) ) baselineBJets.push_back(jet);
          // Misstag light jet
          else if( random_bool(misstag) ) baselineBJets.push_back(jet);
          // Non b-jet
          else baselineNonBJets.push_back(jet);
        }

        // Signal objects
        vector<const HEPUtils::Jet*> signalJets = baselineJets;
        vector<const HEPUtils::Jet*> signalBJets = baselineBJets;
        vector<const HEPUtils::Particle*> signalElectrons = baselineElectrons;
        vector<const HEPUtils::Particle*> signalMuons;
        vector<const HEPUtils::Particle*> signalLeptons;

        // Signal electrons must satisfy the “medium” identification requirement as defined in arXiv: 1902.04655 [hep-ex]
        ATLAS::applyElectronIDEfficiency2019(signalElectrons, "Medium");


        // Signal muons must have pT > 5 GeV.
        for (const HEPUtils::Particle* signalMuon : baselineMuons)
        {
          if (signalMuon->pT() > 5.) signalMuons.push_back(signalMuon);
        }

        // Missing: we need track information for isolation criteria for signal leptons

        // Fill signal leptons
        signalLeptons = signalElectrons;
        signalLeptons.insert(signalLeptons.end(), signalMuons.begin(), signalMuons.end());

        // Sort by pT
        sort(signalJets.begin(), signalJets.end(), compareJetPt);
        sort(signalBJets.begin(), signalBJets.end(), compareJetPt);
        sort(signalLeptons.begin(), signalLeptons.end(), comparePt);

        // Trigger requirements are
        // - >=3 signal leptons
        // - >=1 SF-OS pair
        // - leading lepton pT > 40 GeV
        // - subleading lepton pT > 20 GeV
        // - Zlike, |mll - mZ| < 15 GeV
        bool preselection = false;

        // Count signal leptons and jets
        size_t nSignalLeptons = signalLeptons.size();
        size_t nSignalJets = signalJets.size();
        size_t nSignalBJets = signalBJets.size();

        // Get SFOS pairs
        vector<vector<const HEPUtils::Particle*>> SFOSpairs = getSFOSpairs(signalLeptons);

        // Get SFOS pairs masses and pTs
        vector<double> SFOSpair_masses;
        vector<double> SFOSpair_pTs;
        for (vector<const HEPUtils::Particle*> pair : SFOSpairs)
        {
          SFOSpair_masses.push_back( (pair.at(0)->mom() + pair.at(1)->mom()).m() );
          SFOSpair_pTs.push_back( (pair.at(0)->mom() + pair.at(1)->mom()).pT() );
        }
        std::sort(SFOSpair_masses.begin(), SFOSpair_masses.end(), std::greater<double>());
        std::sort(SFOSpair_pTs.begin(), SFOSpair_pTs.end(), std::greater<double>());

        // Z resonance
        bool Zlike = false;
        double mZ = 91.2;
        for(double m : SFOSpair_masses)
        {
          if (abs(m - mZ) < 15)
            Zlike = true;
        }

        // Combine all preselection cuts
        preselection = nSignalLeptons >= 3 && SFOSpairs.size() >= 1 && signalLeptons.at(0)->pT() > 40. && signalLeptons.at(1)->pT() > 20. && Zlike;

        // Construct the mT23l variable for the pair of SFOS with invariant mass closest to mZ and highest pT lepton not in the pair
        vector<const HEPUtils::Particle*> SFOSpairClosestToMZ;
        double mll =  0;
        // Find the SFOS pair high inv mass closest to mZ
        for (vector<const HEPUtils::Particle*> pair: SFOSpairs)
        {
          if( fabs( (pair.at(0)->mom() + pair.at(1)->mom()).m() - mZ ) < fabs(mll - mZ) )
          {
            mll = (pair.at(0)->mom() + pair.at(1)->mom()).m();
            SFOSpairClosestToMZ = pair;
          }
        }

        // Construct the pTll variable
        double pTll = 0.0;
        if(SFOSpairClosestToMZ.size() == 2)
          pTll = ( SFOSpairClosestToMZ.at(0)->mom() + SFOSpairClosestToMZ.at(1)->mom() ).pT();

        // Find the highest pT lepton not in the pair, but make sure there are at least 3 leptons
        double mT23l = 0.0;
        if(nSignalLeptons >= 3 and SFOSpairClosestToMZ.size() == 2)
        {
          const HEPUtils::Particle* thirdLepton;
          if(signalLeptons.at(0) != SFOSpairClosestToMZ.at(0) && signalLeptons.at(0) != SFOSpairClosestToMZ.at(1))
            thirdLepton = signalLeptons.at(0);
          else if(signalLeptons.at(1) != SFOSpairClosestToMZ.at(0) && signalLeptons.at(1) != SFOSpairClosestToMZ.at(1))
            thirdLepton = signalLeptons.at(1);
          else
            thirdLepton = signalLeptons.at(2);

          double pa[3] = { mll, (SFOSpairClosestToMZ.at(0)->mom() + SFOSpairClosestToMZ.at(1)->mom()).px(), (SFOSpairClosestToMZ.at(0)->mom() + SFOSpairClosestToMZ.at(1)->mom()).py() };
          double pb[3] = { 0, thirdLepton->mom().px(), thirdLepton->mom().py() };
          double pmiss[3] = { met, ptot.px(), ptot.py() };
          double mn = 0.;

          mt2_bisect::mt2 mt2_calc;
          mt2_calc.set_momenta(pa,pb,pmiss);
          mt2_calc.set_mn(mn);
          mT23l = mt2_calc.get_mt2();
        }

        // Signal Regions

        // Requirement                      SR1A     SR1B    SR2A    SR2B
        // ---------------------------------------------------------------
        // Third leading lepton pT           >20      >20     <20     <60   // done
        // njets (pT > 30 GeV)               >=4      >=5     >=3     >=3   // done
        // nb-tagged jets (pT > 30 GeV)      >=1      >=1      -      >=1   // done
        // Leading jet pT                     -        -     >150      -    // done
        // Leading b-tagged jet pT            -      >100      -       -    // done
        // MET                              >250     >150    >200    >350   // done
        // pTll                               -      >150     <50    >150   // done
        // mT23l                            >100       -       -       -    // done

        // SR1A
        if (preselection &&
            signalLeptons.at(2)->pT() > 20. &&
            nSignalJets >= 4 && signalJets.at(3)->pT() > 30. &&
            nSignalBJets >= 1 && signalBJets.at(0)->pT() > 30. &&
            // -
            // -
            met > 250. &&
            // -
            mT23l > 100.
           )
          _counters.at("SR1A").add_event(event);

        // SR1B
        if (preselection &&
            signalLeptons.at(2)->pT() > 20. &&
            nSignalJets >= 5 && signalJets.at(4)->pT() > 30. &&
            nSignalBJets >= 1 && signalBJets.at(0)->pT() > 30. &&
            // -
            signalBJets.at(0)->pT() > 100. &&
            met > 150. &&
            pTll > 150.
            // -
           )
          _counters.at("SR1B").add_event(event);

        // SR2A
        if (preselection &&
            signalLeptons.at(2)->pT() < 20. &&
            nSignalJets >= 3 && signalJets.at(2)->pT() > 30. &&
            // -
            signalJets.at(0)->pT() > 150. &&
            // -
            met > 200. &&
            pTll < 50.
            // -
           )
          _counters.at("SR2A").add_event(event);

        // SR2B
        if (preselection &&
            signalLeptons.at(2)->pT() < 60. &&
            nSignalJets >= 3 && signalJets.at(2)->pT() > 30. &&
            nSignalBJets >= 1 && signalBJets.at(0)->pT() > 30. &&
           // -
           // -
           met > 350. &&
           pTll > 150.
           // -
           )
          _counters.at("SR2B").add_event(event);

        // Cutflows

        // Fill cutflow with preselection trigger as defined by ATLAS
        //if(nSignalLeptons >= 3) _test[0]++;
        //if(nSignalLeptons >= 3 && nSignalJets >= 3 && signalJets.at(2)->pT() > 30.) _test[1]++;
        //if(nSignalLeptons >= 3 && nSignalJets >= 3 && signalJets.at(2)->pT() > 30. && met > 50.) _test[2]++;
        //if(nSignalLeptons >= 3 && nSignalJets >= 3 && signalJets.at(2)->pT() > 30. && met > 50. && signalLeptons.at(0)->pT() > 40.) _test[3]++;
        //if(nSignalLeptons >= 3 && nSignalJets >= 3 && signalJets.at(2)->pT() > 30. && met > 50. && signalLeptons.at(0)->pT() > 40. && signalLeptons.at(1)->pT() > 20.) _test[4]++;
        if(nSignalLeptons >= 3 && nSignalJets >= 3 && signalJets.at(2)->pT() > 30. && met > 50. && signalLeptons.at(0)->pT() > 40. && signalLeptons.at(1)->pT() > 20.)
        {
          // 1
          for(int i=0; i<4; i++)
            _cutflow[i].fill(1);

          bool SR[] ={true, true, true, true};

          // 2
          // Third leading lepton pT
          for(int i=0; i<2; i++)
            if(signalLeptons.at(2)->pT() > 20)
              _cutflow[i].fill(2);
            else
              SR[i] = false;
          if(signalLeptons.at(2)->pT() < 20)
            _cutflow[2].fill(2);
          else SR[2] = false;
          if(signalLeptons.at(2)->pT() < 60)
            _cutflow[3].fill(2);
          else SR[3] = false;

          // 3
          // Z peak
          for(int i=0; i<4; i++)
            if(Zlike)
             _cutflow[i].fill(3, SR[i]);
            else SR[i] = false;

          // 4
          // nbtagged jets (pT > 30 GeV)
          for(int i=0; i<4; i++)
            if(nSignalBJets >= 1 && signalBJets.at(0)->pT() > 30. && i != 2)
              _cutflow[i].fill(4, SR[i]);
            else if (i != 2)
              SR[i] = false;
          // Leading jet pT > 150 GeV
          if(signalJets.at(0)->pT() > 150.)
            _cutflow[2].fill(4, SR[2]);
          else SR[2] = false;

          // 5
          // n jets (pT > 30 GeV)
          if(nSignalJets >= 4 && signalJets.at(3)->pT() > 30.)
            _cutflow[0].fill(5, SR[0]);
          else SR[0] = false;
          if(nSignalJets >= 5 && signalJets.at(4)->pT() > 30.)
            _cutflow[1].fill(5, SR[1]);
          else SR[1] = false;
          // MET
          if(met > 200.)
            _cutflow[2].fill(5, SR[2]);
          else SR[2] = false;
          if(met > 350.)
            _cutflow[3].fill(5, SR[3]);
          else SR[3] = false;

          // 6
          // MET
          if(met > 250.)
            _cutflow[0].fill(6, SR[0]);
          else SR[0] = false;
          if(met > 150.)
            _cutflow[1].fill(6, SR[1]);
          else SR[1] = false;
          // pTll
          if(pTll < 50.)
            _cutflow[2].fill(6, SR[2]);
          else SR[2] = false;
          if(pTll > 150.)
            _cutflow[3].fill(6, SR[3]);
          else SR[3] = false;

          // 7
          // mT23l
          if(mT23l > 100.)
            _cutflow[0].fill(7, SR[0]);
          else SR[0] = false;
          // pTll
          if(pTll > 150.)
            _cutflow[1].fill(7, SR[1]);
          else SR[1] = false;

          // 8
          // Leading b-tagget jet pT > 100 GeV
          if(nSignalBJets >= 1 && signalBJets.at(0)->pT() > 100.)
            _cutflow[1].fill(8, SR[1]);
          else SR[1] = false;
        }
      }

      /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
      void combine(const Analysis* other)
      {
        const Analysis_ATLAS_13TeV_2OSLEP_Z_139invfb* specificOther
                = dynamic_cast<const Analysis_ATLAS_13TeV_2OSLEP_Z_139invfb*>(other);

        for (auto& pair : _counters) { pair.second += specificOther->_counters.at(pair.first); }
      }

      // This function can be overridden by the derived SR-specific classes
      virtual void collect_results()
      {

        add_result(SignalRegionData(_counters.at("SR1A"), 3., {5.4, 0.7}));
        add_result(SignalRegionData(_counters.at("SR1B"), 14., {12.8, 1.6}));
        add_result(SignalRegionData(_counters.at("SR2A"), 3., {5.7, 1.7}));
        add_result(SignalRegionData(_counters.at("SR2B"), 6., {5.4, 0.8}));

        #ifdef CHECK_CUTFLOW
          cout << _cutflow << endl;
          //cout << "n signal leptons before = " << _test2 << endl;
          //cout << "n signal leptons = " << _test[0] << endl;
          //cout << "n signal jets (pT > 30) = " << _test[1] << endl;
          //cout << "met = " << _test[2] << endl;
          //cout << "leading lepton pT > 40 = " << _test[3] << endl;
          //cout << "subleading lepton pT > 20 = " << _test[4] << endl;
        #endif


      }


    protected:
      void analysis_specific_reset()
      {
        for (auto& pair : _counters) { pair.second.reset(); }
      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(ATLAS_13TeV_2OSLEP_Z_139invfb)


  }
}
