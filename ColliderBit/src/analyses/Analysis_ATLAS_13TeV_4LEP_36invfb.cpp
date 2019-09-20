///
///  \author Anders Kvellestad
///  \date 2018 June
///  *********************************************

// Based on https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/PAPERS/SUSY-2016-21/

// - So far only the signal regions with zero taus have been implemented
// - Some cuts have not yet been implemented

#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>
#include <algorithm>
#include <fstream>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"
#include "gambit/ColliderBit/mt2_bisect.h"

// #define CHECK_CUTFLOW

using namespace std;

namespace Gambit
{
  namespace ColliderBit
  {

    class Analysis_ATLAS_13TeV_4LEP_36invfb : public Analysis
    {

    protected:

      // Counters for the number of accepted events for each signal region
      std::map<string,double> _numSR = {
        {"SR0A", 0},
        {"SR0B", 0},
        {"SR0C", 0},
        {"SR0D", 0},
      };

    private:

      #ifdef CHECK_CUTFLOW
        vector<int> cutFlowVector;
        vector<string> cutFlowVector_str;
        size_t NCUTS;
        vector<double> cutFlowVectorATLAS_400_0;
      #endif

      struct ptComparison
      {
        bool operator() (HEPUtils::Particle* i,HEPUtils::Particle* j) {return (i->pT()>j->pT());}
      } comparePt;

      struct ptJetComparison
      {
        bool operator() (HEPUtils::Jet* i,HEPUtils::Jet* j) {return (i->pT()>j->pT());}
      } compareJetPt;

      // Jet lepton overlap removal
      // Discards jets if they are within DeltaRMax of a lepton
      void JetLeptonOverlapRemoval(vector<HEPUtils::Jet*>& jets, vector<HEPUtils::Particle*>& leptons, double DeltaRMax)
      {
        vector<HEPUtils::Jet*> survivors;
        for(HEPUtils::Jet* jet : jets)
        {
          bool overlap = false;
          for(HEPUtils::Particle* lepton : leptons)
          {
            double dR = jet->mom().deltaR_eta(lepton->mom());
            if(fabs(dR) <= DeltaRMax) overlap = true;
          }
          if(!overlap) survivors.push_back(jet);
        }
        jets = survivors;
        return;
      }

      // Lepton jet overlap removal
      // Discards leptons if they are within DeltaRMax of a jet
      void LeptonJetOverlapRemoval(vector<HEPUtils::Particle*>& leptons, vector<HEPUtils::Jet*>& jets, double DeltaRMax)
      {
        vector<HEPUtils::Particle*> survivors;
        for(HEPUtils::Particle* lepton : leptons)
        {
          bool overlap = false;
          for(HEPUtils::Jet* jet : jets)
          {
            double dR = jet->mom().deltaR_eta(lepton->mom());
            if(fabs(dR) <= DeltaRMax) overlap = true;
          }
          if(!overlap) survivors.push_back(lepton);
        }
        leptons = survivors;
        return;
      }

      // Particle overlap removal
      // Discards particle (from "particles1") if it is within DeltaRMax of another particle
      void ParticleOverlapRemoval(vector<HEPUtils::Particle*>& particles1, vector<HEPUtils::Particle*>& particles2, double DeltaRMax)
      {
        vector<HEPUtils::Particle*> survivors;
        for(HEPUtils::Particle* p1 : particles1)
        {
          bool overlap = false;
          for(HEPUtils::Particle* p2 : particles2)
          {
            double dR = p1->mom().deltaR_eta(p2->mom());
            if(fabs(dR) <= DeltaRMax) overlap = true;
          }
          if(!overlap) survivors.push_back(p1);
        }
        particles1 = survivors;
        return;
      }

      // Removes a lepton from the leptons1 vector if it forms an OS pair with a
      // lepton in leptons2 and the pair has a mass in the range (m_low, m_high).
      void removeOSPairsInMassRange(vector<HEPUtils::Particle*>& leptons1, vector<HEPUtils::Particle*>& leptons2, double m_low, double m_high)
      {
        vector<HEPUtils::Particle*> l1_survivors;
        for(HEPUtils::Particle* l1 : leptons1)
        {
          bool survived = true;
          for(HEPUtils::Particle* l2 : leptons2)
          {
            if(l2 == l1) continue;
            if (l1->pid()*l2->pid() < 0.)
            {
              double m = (l1->mom() + l2->mom()).m();
              if ((m >= m_low) && (m <= m_high))
              {
                survived = false;
                break;
              }
            }
          }
          if(survived) l1_survivors.push_back(l1);
        }
        leptons1 = l1_survivors;
        return;
      }


    public:

      // Required detector sim
      static constexpr const char* detector = "ATLAS";

      Analysis_ATLAS_13TeV_4LEP_36invfb()
      {

        set_analysis_name("ATLAS_13TeV_4LEP_36invfb");
        set_luminosity(36.1);

        #ifdef CHECK_CUTFLOW
          NCUTS = 11;
          for (size_t i=0;i<NCUTS;i++)
          {
            cutFlowVector.push_back(0);
            cutFlowVectorATLAS_400_0.push_back(0);
            cutFlowVector_str.push_back("");
          }
        #endif

      }

      void run(const HEPUtils::Event* event)
      {

        // Baseline objects
        vector<HEPUtils::Particle*> baselineElectrons;
        vector<HEPUtils::Particle*> baselineMuons;
        vector<HEPUtils::Particle*> baselineTaus;
        vector<HEPUtils::Jet*> baselineJets;
        double met = event->met();

        #ifdef  CHECK_CUTFLOW
          bool generator_filter = false;
          bool trigger = true;
          bool event_cleaning = true;

          vector<HEPUtils::Particle*> baselineLeptons_cutflow;
          for (HEPUtils::Particle* electron : event->electrons())
          {
            if (electron->pT()>4. && electron->abseta()<2.8) baselineLeptons_cutflow.push_back(electron);
          }
          for (HEPUtils::Particle* muons : event->muons())
          {
            if (muons->pT()>4. && muons->abseta()<2.8) baselineLeptons_cutflow.push_back(muons);
          }
          if (baselineLeptons_cutflow.size() >= 4) generator_filter = true;
        #endif


        for (HEPUtils::Particle* electron : event->electrons())
        {
          if (electron->pT()>7. && electron->abseta()<2.47) baselineElectrons.push_back(electron);
        }

        // Apply electron efficiency
        ATLAS::applyElectronEff(baselineElectrons);

        // Apply loose electron selection
        ATLAS::applyLooseIDElectronSelectionR2(baselineElectrons);

        for (HEPUtils::Particle* muon : event->muons())
        {
          if (muon->pT()>5. && muon->abseta()<2.7) baselineMuons.push_back(muon);
        }

        // Apply muon efficiency
        ATLAS::applyMuonEff(baselineMuons);

        // Missing: Apply "medium" muon ID criteria

        for (HEPUtils::Particle* tau : event->taus())
        {
          if (tau->pT()>20. && tau->abseta()<2.47) baselineTaus.push_back(tau);
        }
        // Since tau efficiencies are not applied as part of the BuckFast ATLAS sim we apply it here
        ATLAS::applyTauEfficiencyR2(baselineTaus);

        for (HEPUtils::Jet* jet : event->jets())
        {
          if (jet->pT()>20. && jet->abseta()<2.8) baselineJets.push_back(jet);
        }
        // Missing: Some additional requirements for jets with pT < 60 and abseta < 2.4 (see paper)



        // Overlap removal
        // 1) Remove taus within DeltaR = 0.2 of an electron or muon
        ParticleOverlapRemoval(baselineTaus, baselineElectrons, 0.2);
        ParticleOverlapRemoval(baselineTaus, baselineMuons, 0.2);

        // 2) Missing: Remove electron sharing an ID track with a muon

        // 3) Remove jets within DeltaR = 0.2 of electron
        JetLeptonOverlapRemoval(baselineJets, baselineElectrons, 0.2);

        // 4) Remove electrons within DeltaR = 0.4 of a jet
        LeptonJetOverlapRemoval(baselineElectrons, baselineJets, 0.4);

        // 5) Missing: Remove jets with < 3 assocated tracks if a muon is
        //    within DeltaR = 0.2 *or* if the muon is a track in the jet.

        // 6) Remove muons within DeltaR = 0.4 of jet
        LeptonJetOverlapRemoval(baselineMuons, baselineJets, 0.4);

        // 7) Remove jets within DeltaR = 0.4 of a "medium" tau
        JetLeptonOverlapRemoval(baselineJets, baselineTaus, 0.4);


        // Suppress low-mass particle decays
        vector<HEPUtils::Particle*> baselineLeptons;
        baselineLeptons = baselineElectrons;
        baselineLeptons.insert(baselineLeptons.end(), baselineMuons.begin(), baselineMuons.end());
        // - Remove low-mass OS pairs
        removeOSPairsInMassRange(baselineElectrons, baselineLeptons, 0.0, 4.0);
        removeOSPairsInMassRange(baselineMuons, baselineLeptons, 0.0, 4.0);
        // - Remove SFOS pairs in the mass range (8.4, 10.4) GeV
        removeOSPairsInMassRange(baselineElectrons, baselineElectrons, 8.4, 10.4);
        removeOSPairsInMassRange(baselineMuons, baselineMuons, 8.4, 10.4);


        // Signal objects
        vector<HEPUtils::Jet*> signalJets = baselineJets;
        vector<HEPUtils::Particle*> signalElectrons = baselineElectrons;
        vector<HEPUtils::Particle*> signalMuons = baselineMuons;
        vector<HEPUtils::Particle*> signalTaus = baselineTaus;
        vector<HEPUtils::Particle*> signalLeptons;
        signalLeptons = signalElectrons;
        signalLeptons.insert(signalLeptons.end(), signalMuons.begin(), signalMuons.end());

        // Missing: pT-dependent isolation criteria for signal leptons (see paper)

        // Sort by pT
        sort(signalJets.begin(), signalJets.end(), compareJetPt);
        sort(signalLeptons.begin(), signalLeptons.end(), comparePt);

        // Count signal leptons and jets
        // size_t nSignalElectrons = signalElectrons.size();
        // size_t nSignalMuons = signalMuons.size();
        size_t nSignalTaus = signalTaus.size();
        size_t nSignalLeptons = signalLeptons.size();
        // size_t nSignalJets = signalJets.size();

        // Get OS and SFOS pairs
        vector<vector<HEPUtils::Particle*>> SFOSpairs = getSFOSpairs(signalLeptons);
        vector<vector<HEPUtils::Particle*>> OSpairs = getOSpairs(signalLeptons);

        // Z requirements
        vector<double> SFOSpair_masses;
        for (vector<HEPUtils::Particle*> pair : SFOSpairs)
        {
          SFOSpair_masses.push_back( (pair.at(0)->mom() + pair.at(1)->mom()).m() );
        }
        std::sort(SFOSpair_masses.begin(), SFOSpair_masses.end(), std::greater<double>());

        bool Z1 = false;
        bool Z2 = false;
        bool Zlike = false;
        for(double m : SFOSpair_masses)
        {
          if (!Z1 && (m > 81.2) && (m < 101.2))
          {
            Z1 = true;
          }
          else if (Z1 && (m > 61.2) && (m < 101.2))
          {
            Z2 = true;
          }
        }
        if (Z1) Zlike = true;
        // Missing: Also check Z-like combinations of SFOS+L and SFOS+SFOS (see paper)


        // Effective mass (met + pT of all signal leptons + pT of all jets with pT>40 GeV)
        double meff = met;
        for (HEPUtils::Particle* l : signalLeptons)
        {
          meff += l->pT();
        }
        for (HEPUtils::Jet* jet : signalJets)
        {
          if(jet->pT()>40.) meff += jet->pT();
        }


        // Signal Regions

        // --- 4L0T ---

        // SR0A
        if (nSignalTaus == 0 && nSignalLeptons >= 4 && !Zlike && meff > 600.) _numSR["SR0A"]++;
        // if (nSignalTaus == 0 && nSignalLeptons >= 4 && !Zlike && meff > 600.)
        // {
        //   cout << "DEBUG: " << "--- Got event for SR0A ---" << endl;
        //   cout << "DEBUG: " << "  leptons: " << nSignalLeptons << ", electrons: " << nSignalElectrons << ", muons: " << nSignalMuons << endl;
        //   cout << "DEBUG: " << "  jets: " << nSignalJets << endl;
        //   cout << "DEBUG: " << "  meff = " << meff << endl;
        //   cout << "DEBUG: " << "  nSFOSpairs = " << SFOSpairs.size() << endl;
        //   for (double mass : SFOSpair_masses)
        //   {
        //     cout << "DEBUG: " << "  pair mass: " << mass << endl;
        //   }

        //   _numSR["SR0A"]++;
        // }

        // SR0B
        if (nSignalTaus == 0 && nSignalLeptons >= 4 && !Zlike && meff > 1100.) _numSR["SR0B"]++;
        // if (nSignalTaus == 0 && nSignalLeptons >= 4 && !Zlike && meff > 1100.)
        // {
        //   cout << "DEBUG: " << "--- Got event for SR0B ---" << endl;
        //   cout << "DEBUG: " << "  leptons: " << nSignalLeptons << ", electrons: " << nSignalElectrons << ", muons: " << nSignalMuons << endl;
        //   cout << "DEBUG: " << "  jets: " << nSignalJets << endl;
        //   cout << "DEBUG: " << "  meff = " << meff << endl;
        //   cout << "DEBUG: " << "  nSFOSpairs = " << SFOSpairs.size() << endl;
        //   for (double mass : SFOSpair_masses)
        //   {
        //     cout << "DEBUG: " << "  pair mass: " << mass << endl;
        //   }

        //   _numSR["SR0B"]++;
        // }

        // SR0C
        if (nSignalTaus == 0 && nSignalLeptons >= 4 && Z1 && Z2 && met > 50.) _numSR["SR0C"]++;
        // if (nSignalTaus == 0 && nSignalLeptons >= 4 && Z1 && Z2 && met > 50.)
        // {
        //   cout << "DEBUG: " << "--- Got event for SR0C ---" << endl;
        //   cout << "DEBUG: " << "  leptons: " << nSignalLeptons << ", electrons: " << nSignalElectrons << ", muons: " << nSignalMuons << endl;
        //   cout << "DEBUG: " << "  jets: " << nSignalJets << endl;
        //   cout << "DEBUG: " << "  met = " << met << endl;
        //   cout << "DEBUG: " << "  nSFOSpairs = " << SFOSpairs.size() << endl;
        //   for (double mass : SFOSpair_masses)
        //   {
        //     cout << "DEBUG: " << "  pair mass: " << mass << endl;
        //   }

        //   _numSR["SR0C"]++;
        // }

        // SR0D
        if (nSignalTaus == 0 && nSignalLeptons >= 4 && Z1 && Z2 && met > 100.) _numSR["SR0D"]++;
        // if (nSignalTaus == 0 && nSignalLeptons >= 4 && Z1 && Z2 && met > 100.)
        // {
        //   cout << "DEBUG: " << "--- Got event for SR0D ---" << endl;
        //   cout << "DEBUG: " << "  leptons: " << nSignalLeptons << ", electrons: " << nSignalElectrons << ", muons: " << nSignalMuons << endl;
        //   cout << "DEBUG: " << "  jets: " << nSignalJets << endl;
        //   cout << "DEBUG: " << "  met = " << met << endl;
        //   cout << "DEBUG: " << "  nSFOSpairs = " << SFOSpairs.size() << endl;
        //   for (double mass : SFOSpair_masses)
        //   {
        //     cout << "DEBUG: " << "  pair mass: " << mass << endl;
        //   }

        //   _numSR["SR0D"]++;
        // }

        // Missing: signal regions SR1 (3L1T) and SR2 (2L2T)

        #ifdef CHECK_CUTFLOW
          cutFlowVector_str[0] = "Initial";
          cutFlowVector_str[1] = "Generator filter";
          cutFlowVector_str[2] = "Trigger";
          cutFlowVector_str[3] = "Event cleaning";
          cutFlowVector_str[4] = "N_e_mu >= 1";
          cutFlowVector_str[5] = "N_e_mu >= 2";
          cutFlowVector_str[6] = "N_e_mu >= 3";
          cutFlowVector_str[7] = "N_e_mu >= 4";
          cutFlowVector_str[8] = "ZZ selection";
          cutFlowVector_str[9] = "ETmiss > 50 (SRC)";
          cutFlowVector_str[10] = "ETmiss > 100 (SRD)";

          cutFlowVectorATLAS_400_0[0] = 3203.45;
          cutFlowVectorATLAS_400_0[1] = 36.34;
          cutFlowVectorATLAS_400_0[2] = 28.77;
          cutFlowVectorATLAS_400_0[3] = 27.64;
          cutFlowVectorATLAS_400_0[4] = 26.14;
          cutFlowVectorATLAS_400_0[5] = 23.34;
          cutFlowVectorATLAS_400_0[6] = 14.19;
          cutFlowVectorATLAS_400_0[7] = 7.59;
          cutFlowVectorATLAS_400_0[8] = 5.71;
          cutFlowVectorATLAS_400_0[9] = 5.44;
          cutFlowVectorATLAS_400_0[10] = 4.84;

          for (size_t j=0;j<NCUTS;j++)
          {
            if(
              (j==0) ||

              (j==1 && generator_filter) ||

              (j==2 && generator_filter && trigger) ||

              (j==3 && generator_filter && trigger && event_cleaning) ||

              (j==4 && generator_filter && trigger && event_cleaning && nSignalLeptons >= 1) ||

              (j==5 && generator_filter && trigger && event_cleaning && nSignalLeptons >= 2) ||

              (j==6 && generator_filter && trigger && event_cleaning && nSignalLeptons >= 3) ||

              (j==7 && generator_filter && trigger && event_cleaning && nSignalLeptons >= 4) ||

              (j==8 && generator_filter && trigger && event_cleaning && nSignalLeptons >= 4 && Z1 && Z2) ||

              (j==9 && generator_filter && trigger && event_cleaning && nSignalLeptons >= 4 && Z1 && Z2 && met > 50.) ||

              (j==10 && generator_filter && trigger && event_cleaning && nSignalLeptons >= 4 && Z1 && Z2 && met > 100.)

              )

            cutFlowVector[j]++;
          }
        #endif
      }

      /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
      void combine(const Analysis* other)
      {
        const Analysis_ATLAS_13TeV_4LEP_36invfb* specificOther
                = dynamic_cast<const Analysis_ATLAS_13TeV_4LEP_36invfb*>(other);

        #ifdef CHECK_CUTFLOW
          // if (NCUTS != specificOther->NCUTS) NCUTS = specificOther->NCUTS;
          for (size_t j = 0; j < NCUTS; j++) {
            cutFlowVector[j] += specificOther->cutFlowVector[j];
            cutFlowVector_str[j] = specificOther->cutFlowVector_str[j];
          }
        #endif

        for (auto& el : _numSR)
        {
          el.second += specificOther->_numSR.at(el.first);
        }

      }

      // This function can be overridden by the derived SR-specific classes
      virtual void collect_results() {

        // add_result(SignalRegionData("SR label", n_obs, {s, s_sys}, {b, b_sys}));
        add_result(SignalRegionData("SR0A", 13., {_numSR["SR0A"], 0.}, {10.2, 2.1}));
        add_result(SignalRegionData("SR0B",  2., {_numSR["SR0B"], 0.}, {1.31, 0.24}));
        add_result(SignalRegionData("SR0C", 47., {_numSR["SR0C"], 0.}, {37., 9.}));
        add_result(SignalRegionData("SR0D", 10., {_numSR["SR0D"], 0.}, {4.1, 0.7}));


        #ifdef CHECK_CUTFLOW
          vector<double> cutFlowVector_scaled;
          for (size_t i=0 ; i < cutFlowVector.size() ; i++)
          {
            double scale_factor = cutFlowVectorATLAS_400_0[0]/cutFlowVector[0];
            cutFlowVector_scaled.push_back(cutFlowVector[i] * scale_factor);
          }
          cout << "DEBUG CUTFLOW:   ATLAS    GAMBIT(raw)    GAMBIT(scaled) " << endl;
          cout << "DEBUG CUTFLOW:   -------------------------------------" << endl;

          for (size_t j = 0; j < NCUTS; j++) {
            cout << setprecision(4) << "DEBUG CUTFLOW:   " << cutFlowVectorATLAS_400_0[j] << "\t\t"
                                        << cutFlowVector[j] << "\t\t"
                                        << cutFlowVector_scaled[j] << "\t\t"
                                        << cutFlowVector_str[j]
                                        << endl;
          }
        #endif
      }


    protected:
      void analysis_specific_reset() {
        for (auto& el : _numSR) { el.second = 0.;}
        #ifdef CHECK_CUTFLOW
          std::fill(cutFlowVector.begin(), cutFlowVector.end(), 0);
        #endif
      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(ATLAS_13TeV_4LEP_36invfb)


  }
}
