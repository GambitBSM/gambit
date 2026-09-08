///
///  \author Anders Kvellestad
///  \date 2020 Aug
///  \date 2021 Sep
///
///  \author Victor Ananyev
///  \date 2020 Sep
///  *********************************************

// Based on confnote https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/CONFNOTES/ATLAS-CONF-2020-040/
// Updated to paper version:
//   https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/PAPERS/SUSY-2018-02/
//   https://arxiv.org/abs/2103.11684

// Old Analysis Name: ATLAS_13TeV_4LEP_139invfb

#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>
#include <algorithm>
#include <fstream>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/analyses/AnalysisMacros.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"
#include "gambit/ColliderBit/mt2_bisect.h"

// #define CHECK_CUTFLOW

using namespace std;

// Renamed from: Analysis_ATLAS_13TeV_4LEP_139invfb

namespace Gambit
{
  namespace ColliderBit
  {

    class Analysis_ATLAS_SUSY_2018_02 : public Analysis
    {

    protected:

    private:

      #ifdef CHECK_CUTFLOW
        vector<string> legacyCutNames;
        size_t NCUTS;
        vector<double> legacyCutATLAS_200_50;
        vector<double> legacyCutATLAS_300_100;
      #endif

      struct ptComparison
      {
        bool operator() (const HEPUtils::Particle* i,const HEPUtils::Particle* j) {return (i->pT()>j->pT());}
      } comparePt;

      struct ptJetComparison
      {
        bool operator() (const HEPUtils::Jet* i,const HEPUtils::Jet* j) {return (i->pT()>j->pT());}
      } compareJetPt;

      // Jet lepton overlap removal
      // Discards jets if they are within DeltaRMax of a lepton
      void JetLeptonOverlapRemoval(vector<const HEPUtils::Jet*>& jets, vector<const HEPUtils::Particle*>& leptons, double DeltaRMax)
      {
        vector<const HEPUtils::Jet*> survivors;
        for(const HEPUtils::Jet* jet : jets)
        {
          bool overlap = false;
          for(const HEPUtils::Particle* lepton : leptons)
          {
            double dR = jet->mom().deltaR_eta(lepton->mom());
            if(fabs(dR) <= DeltaRMax) overlap = true;
          }
          if(!overlap) survivors.push_back(jet);
        }
        jets = survivors;
        return;
      }

      size_t bTagger(vector<const HEPUtils::Jet*>& signalJets, vector<const HEPUtils::Particle*> signalTaus)
      {
        size_t n_btags = 0;
        // Numbers taken from Table 4 in https://arxiv.org/pdf/1907.05120.pdf
        const double btag = 0.85;
        const double cmisstag = 1/2.7;
        const double misstag = 1./25.;
        const double taumisstag = 1/6.1;

        // Loop over signal jets and count b-tags
        for (const HEPUtils::Jet* jet : signalJets)
        {
          if (jet->abseta() > 2.5) continue;
          // Count number of true b-jets that are tagged
          if( jet->btag() )
          {
              if (random_bool(btag)) n_btags++;
          }
          // Count number of true c-jets that are misstagged as b-jets
          else if( jet->ctag())
          {
              if (random_bool(cmisstag)) n_btags++;
          }
          // Count number of light-flavour jets that are misstagged as b-jets
          else
          {
              if (random_bool(misstag)) n_btags++;
          }
        }

        // Count number of taus misstagged as b-jets 6.1
        for (const HEPUtils::Particle* p : signalTaus)
        {
          if (p->abseta() > 2.5) continue;
          if (random_bool(taumisstag)) n_btags++;
        }

        return n_btags;
      }

      // Lepton jet overlap removal
      // Discards leptons if they are within DeltaRMax of a jet
      void LeptonJetOverlapRemoval(vector<const HEPUtils::Particle*>& leptons, vector<const HEPUtils::Jet*>& jets, double DeltaRMax)
      {
        vector<const HEPUtils::Particle*> survivors;
        for(const HEPUtils::Particle* lepton : leptons)
        {
          bool overlap = false;
          for(const HEPUtils::Jet* jet : jets)
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
      void ParticleOverlapRemoval(vector<const HEPUtils::Particle*>& particles1, vector<const HEPUtils::Particle*>& particles2, double DeltaRMax)
      {
        vector<const HEPUtils::Particle*> survivors;
        for(const HEPUtils::Particle* p1 : particles1)
        {
          bool overlap = false;
          for(const HEPUtils::Particle* p2 : particles2)
          {
            double dR = p1->mom().deltaR_eta(p2->mom());
            if(fabs(dR) <= DeltaRMax) overlap = true;
          }
          if(!overlap) survivors.push_back(p1);
        }
        particles1 = survivors;
        return;
      }

      // Particle overlap removal
      // Discard particles within DeltaRMax of one another, IF pT of any < pTMax
      void ParticlePTOverlapPairsRemoval(vector<const HEPUtils::Particle*>& particles, double DeltaRMax, double pTMax)
      {
        if (particles.size() < 2)
            return;
        vector<const HEPUtils::Particle*> survivors;
        vector<const HEPUtils::Particle*> todrop;
        for(auto p1_it = particles.begin(); p1_it != particles.end()-1; ++p1_it)
        {
          auto p1 = *p1_it;
          bool overlap = false;
          bool lowpt = false;
          for(auto p2_it = p1_it+1; p2_it != particles.end(); ++p2_it)
          {
            auto p2 = *p2_it;
            double dR = p1->mom().deltaR_eta(p2->mom());
            if (fabs(dR) <= DeltaRMax)
            {
              overlap = true;
              lowpt = true;
              if (p1->pT() < pTMax || p2->pT() < pTMax)
              {
                todrop.push_back(p2);
                lowpt = true;
                break;
              }
            }
          }
          if (!(overlap && lowpt))
          {
            survivors.push_back(p1);
          }
        }
        std::sort(survivors.begin(), survivors.end());
        std::sort(todrop.begin(), todrop.end());
        vector<const HEPUtils::Particle*> result;
        std::set_difference(survivors.begin(), survivors.end(), todrop.begin(), todrop.end(), std::back_inserter(result));
        particles = result;
        return;
      }

      // Removes a lepton from the leptons1 vector if it forms an OS pair with a
      // lepton in leptons2 and the pair has a mass in the range (m_low, m_high).
      void removeOSPairsInMassRange(vector<const HEPUtils::Particle*>& leptons1, vector<const HEPUtils::Particle*>& leptons2, double m_low, double m_high)
      {
        vector<const HEPUtils::Particle*> l1_survivors;
        for (const HEPUtils::Particle* l1 : leptons1)
        {
          bool survived = true;
          for (const HEPUtils::Particle* l2 : leptons2)
          {
            if (l2 == l1) continue;
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
          if (survived) l1_survivors.push_back(l1);
        }
        leptons1 = l1_survivors;
        return;
      }


    public:

      // Required detector sim
      static constexpr const char* detector = "ATLAS";

      Analysis_ATLAS_SUSY_2018_02()
      {
        // Counters for the number of accepted events for each signal region
        _counters["SR0-ZZ-loose-bveto"] = EventCounter("SR0-ZZ-loose-bveto");
        _counters["SR0-ZZ-tight-bveto"] = EventCounter("SR0-ZZ-tight-bveto");
        _counters["SR0-ZZ-loose"] = EventCounter("SR0-ZZ-loose");
        _counters["SR0-ZZ-tight"] = EventCounter("SR0-ZZ-tight");
        _counters["SR0-loose-bveto"] = EventCounter("SR0-loose-bveto");
        _counters["SR0-tight-bveto"] = EventCounter("SR0-tight-bveto");
        _counters["SR0-breq"] = EventCounter("SR0-breq");
        _counters["SR5L"] = EventCounter("SR5L");

        set_analysis_name("ATLAS_SUSY_2018_02");
        set_luminosity(139.);

        #ifdef CHECK_CUTFLOW
          NCUTS = 12;
          for (size_t i=0;i<NCUTS;i++)
          {
            legacyCutATLAS_200_50.push_back(0);
            legacyCutATLAS_300_100.push_back(0);
            legacyCutNames.push_back("");
          }
        #endif

      }

      void run(const HEPUtils::Event* event)
      {

        // Baseline objects
        vector<const HEPUtils::Particle*> baselineElectrons;
        vector<const HEPUtils::Particle*> baselineMuons;
        vector<const HEPUtils::Particle*> baselineTaus;
        vector<const HEPUtils::Jet*> baselineJets;
        double met = event->met();

        #ifdef  CHECK_CUTFLOW
          bool generator_filter = false;
          bool trigger = true;
        #endif


        #ifdef  CHECK_CUTFLOW
            int gen_filter_cnt = 0;
        #endif
        for (const HEPUtils::Particle* electron : event->electrons())
        {
          if (electron->pT()>4.5 && electron->abseta()<2.47) baselineElectrons.push_back(electron);
          #ifdef  CHECK_CUTFLOW
            if (!generator_filter && electron->pT() > 4 && electron->abseta()<2.8)
            {
              ++gen_filter_cnt;
            }
          #endif
        }

        // Apply electron efficiency
        applyEfficiency(baselineElectrons, ATLAS::eff2DEl.at("Generic"));

        // Apply loose electron selection
        applyEfficiency(baselineElectrons, ATLAS::eff2DEl.at("ATLAS_PHYS_PUB_2015_041_Loose"));

        for (const HEPUtils::Particle* muon : event->muons())
        {
          if (muon->pT()>3. && muon->abseta()<2.7) baselineMuons.push_back(muon);
          #ifdef  CHECK_CUTFLOW
            if (!generator_filter && muon->pT() > 4 && muon->abseta() < 2.8)
            {
              ++gen_filter_cnt;
            }
          #endif
        }

        // Apply muon efficiency
        applyEfficiency(baselineMuons, ATLAS::eff2DMu.at("Generic"));

        // Missing: Apply "medium" muon ID criteria

        for (const HEPUtils::Particle* tau : event->taus())
        {
          if (tau->pT()>20. && (tau->abseta()<1.37 || (tau->abseta()>1.51 && tau->abseta()<2.47))) baselineTaus.push_back(tau);
          #ifdef  CHECK_CUTFLOW
            if (!generator_filter && tau->pT() > 15 && tau->abseta() < 2.8)
            {
              ++gen_filter_cnt;
            }
          #endif
        }
        #ifdef  CHECK_CUTFLOW
          if (!generator_filter && gen_filter_cnt >= 4)
          {
            generator_filter = true;
          }
        #endif

        // Since tau efficiencies are not applied as part of the BuckFast ATLAS sim we apply it here
        applyEfficiency(baselineTaus, ATLAS::eff1DTau.at("R2"));

        for (const HEPUtils::Jet* jet : event->jets("antikt_R04"))
        {
          if (jet->pT()>20. && jet->abseta()<2.8) baselineJets.push_back(jet);
        }
        // Missing: Some additional requirements for jets with abseta < 2.5, originating from b-quarks (see paper)
        // Missing: some jets are originating from hadronically decayed taus pT > 10, abseta < 2.47 and more. (see paper)



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
        vector<const HEPUtils::Particle*> baselineLeptons;
        baselineLeptons = baselineElectrons;
        baselineLeptons.insert(baselineLeptons.end(), baselineMuons.begin(), baselineMuons.end());
        // - Remove low-mass OS pairs
        removeOSPairsInMassRange(baselineElectrons, baselineLeptons, 0.0, 4.0);
        removeOSPairsInMassRange(baselineMuons, baselineLeptons, 0.0, 4.0);
        // - Remove SFOS pairs in the mass range (8.4, 10.4) GeV
        removeOSPairsInMassRange(baselineElectrons, baselineElectrons, 8.4, 10.4);
        removeOSPairsInMassRange(baselineMuons, baselineMuons, 8.4, 10.4);
        ParticlePTOverlapPairsRemoval(baselineLeptons, 0.6, 30.);


        // Signal objects
        vector<const HEPUtils::Jet*> signalJets = baselineJets;
        // vector<const HEPUtils::Jet*> signalBJets = baselineJets;
        // bTagger(signalBJets);  // Keep only B-tagged jets
        vector<const HEPUtils::Particle*> signalElectrons = baselineElectrons;
        vector<const HEPUtils::Particle*> signalMuons = baselineMuons;
        vector<const HEPUtils::Particle*> signalTaus = baselineTaus;
        vector<const HEPUtils::Particle*> signalLeptons;
        signalLeptons = signalElectrons;
        signalLeptons.insert(signalLeptons.end(), signalMuons.begin(), signalMuons.end());

        // Missing: pT-dependent isolation criteria for signal leptons (see paper)

        // Sort by pT
        sort(signalJets.begin(), signalJets.end(), compareJetPt);
        sort(signalLeptons.begin(), signalLeptons.end(), comparePt);

        // Count signal leptons
        size_t nSignalLeptons = signalLeptons.size();

        // Count number of b-tagged jets
        size_t NbJets = bTagger(signalJets, signalTaus);

        // Get OS and SFOS pairs
        vector<vector<const HEPUtils::Particle*>> SFOSpairs = getSFOSpairs(signalLeptons);
        vector<vector<const HEPUtils::Particle*>> OSpairs = getOSpairs(signalLeptons);

        // Z requirements
        vector<double> SFOSpair_masses;
        for (vector<const HEPUtils::Particle*> pair : SFOSpairs)
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

        // Missing soft term correction for Et_miss. Constructed from tracks matched to the primary vertex
        // but not associated with identified physics objects (see paper)

        // Effective mass (met + pT of all signal leptons + pT of all jets with pT>40 GeV)
        double meff = met;
        for (const HEPUtils::Particle* l : signalLeptons)
        {
          meff += l->pT();
        }
        for (const HEPUtils::Jet* jet : signalJets)
        {
          if(jet->pT()>40.) meff += jet->pT();
        }


        // Signal Regions

        // --- 4L0T ---

        // SR0-ZZ-loose-bveto
        if (nSignalLeptons >= 4 && NbJets == 0 && Z1 && Z2 && met > 100.) _counters.at("SR0-ZZ-loose-bveto").add_event(event);
        //if (nSignalLeptons >= 4 && NbJets == 0 && Z1 && Z2 && met > 100.)
        // {
        //   cout << "DEBUG: " << "--- Got event for SR0-ZZ-loose-bveto ---" << endl;
        //   cout << "DEBUG: " << "  leptons: " << nSignalLeptons << ", electrons: " << nSignalElectrons << ", muons: " << nSignalMuons << endl;
        //   cout << "DEBUG: " << "  jets: " << nSignalJets << endl;
        //   cout << "DEBUG: " << "  met = " << met << endl;
        //   cout << "DEBUG: " << "  nSFOSpairs = " << SFOSpairs.size() << endl;
        //   for (double mass : SFOSpair_masses)
        //   {
        //     cout << "DEBUG: " << "  pair mass: " << mass << endl;
        //   }
        // }

        // SR0-ZZ-tight-bveto
        if (nSignalLeptons >= 4 && NbJets == 0 && Z1 && Z2 && met > 200.) _counters.at("SR0-ZZ-tight-bveto").add_event(event);
        //if (nSignalLeptons >= 4 && NbJets == 0 && Z1 && Z2 && met > 200.)
        // {
        //   cout << "DEBUG: " << "--- Got event for SR0-ZZ-tight-bveto ---" << endl;
        //   cout << "DEBUG: " << "  leptons: " << nSignalLeptons << ", electrons: " << nSignalElectrons << ", muons: " << nSignalMuons << endl;
        //   cout << "DEBUG: " << "  jets: " << nSignalJets << endl;
        //   cout << "DEBUG: " << "  met = " << met << endl;
        //   cout << "DEBUG: " << "  nSFOSpairs = " << SFOSpairs.size() << endl;
        //   for (double mass : SFOSpair_masses)
        //   {
        //     cout << "DEBUG: " << "  pair mass: " << mass << endl;
        //   }
        // }

        // SR0-ZZ-loose
        if (nSignalLeptons >= 4 && Z1 && Z2 && met > 50.) _counters.at("SR0-ZZ-loose").add_event(event);
        //if (nSignalLeptons >= 4 && Z1 && Z2 && met > 50.)
        // {
        //   cout << "DEBUG: " << "--- Got event for SR0-ZZ-loose ---" << endl;
        //   cout << "DEBUG: " << "  leptons: " << nSignalLeptons << ", electrons: " << nSignalElectrons << ", muons: " << nSignalMuons << endl;
        //   cout << "DEBUG: " << "  jets: " << nSignalJets << endl;
        //   cout << "DEBUG: " << "  met = " << met << endl;
        //   cout << "DEBUG: " << "  nSFOSpairs = " << SFOSpairs.size() << endl;
        //   for (double mass : SFOSpair_masses)
        //   {
        //     cout << "DEBUG: " << "  pair mass: " << mass << endl;
        //   }
        // }

        // SR0-ZZ-tight
        if (nSignalLeptons >= 4 && Z1 && Z2 && met > 100.) _counters.at("SR0-ZZ-tight").add_event(event);
        //if (nSignalLeptons >= 4 && Z1 && Z2 && met > 100.)
        // {
        //   cout << "DEBUG: " << "--- Got event for SR0-ZZ-tight-bveto ---" << endl;
        //   cout << "DEBUG: " << "  leptons: " << nSignalLeptons << ", electrons: " << nSignalElectrons << ", muons: " << nSignalMuons << endl;
        //   cout << "DEBUG: " << "  jets: " << nSignalJets << endl;
        //   cout << "DEBUG: " << "  met = " << met << endl;
        //   cout << "DEBUG: " << "  nSFOSpairs = " << SFOSpairs.size() << endl;
        //   for (double mass : SFOSpair_masses)
        //   {
        //     cout << "DEBUG: " << "  pair mass: " << mass << endl;
        //   }
        // }

        // SR0-loose-bveto
        if (nSignalLeptons >= 4 && NbJets == 0 && !Zlike && meff > 600.) _counters.at("SR0-loose-bveto").add_event(event);

        // SR0-tight-bveto
        if (nSignalLeptons >= 4 && NbJets == 0 && !Zlike && meff > 1250.) _counters.at("SR0-tight-bveto").add_event(event);

        // SR0-breq
        if (nSignalLeptons >= 4 && NbJets >= 1 && !Zlike && meff > 1300.) _counters.at("SR0-breq").add_event(event);

        // SR5L
        if (nSignalLeptons >= 5) _counters.at("SR5L").add_event(event);


        #ifdef CHECK_CUTFLOW
          legacyCutNames[0] = "Initial";
          legacyCutNames[1] = "Good Event";
          legacyCutNames[2] = "N_e_mu >= 2";
          legacyCutNames[3] = "Trigger";
          legacyCutNames[4] = "N_e_mu >= 4";
          legacyCutNames[5] = "ZZ";
          legacyCutNames[6] = "met > 50 (SR0-ZZ-loose)";
          legacyCutNames[7] = "met > 100 (SR0-ZZ-tight)";
          legacyCutNames[8] = "b-veto";
          legacyCutNames[9] = "met > 100 (SR0-ZZ-loose-bveto)";
          legacyCutNames[10] = "met > 200 (SR0-ZZ-tight-bveto)";
          legacyCutNames[11] = "SR5L";

          legacyCutATLAS_200_50[0] = -1;
          legacyCutATLAS_200_50[1] = 2716.37;
          legacyCutATLAS_200_50[2] = 1041.64;
          legacyCutATLAS_200_50[3] = 951.78;
          legacyCutATLAS_200_50[4] = 116.87;
          legacyCutATLAS_200_50[5] = 71.53;
          legacyCutATLAS_200_50[6] = 55.88;
          legacyCutATLAS_200_50[7] = 28.47;
          legacyCutATLAS_200_50[8] = 66.21;
          legacyCutATLAS_200_50[9] = 26.41;
          legacyCutATLAS_200_50[10] = 2.96;
          legacyCutATLAS_200_50[11] = 0.79;

          legacyCutATLAS_300_100[0] = -1;
          legacyCutATLAS_300_100[1] = 493.16;
          legacyCutATLAS_300_100[2] = 319.87;
          legacyCutATLAS_300_100[3] = 308.22;
          legacyCutATLAS_300_100[4] = 74.92;
          legacyCutATLAS_300_100[5] = 61.14;
          legacyCutATLAS_300_100[6] = 56.74;
          legacyCutATLAS_300_100[7] = 46.76;
          legacyCutATLAS_300_100[8] = 55.42;
          legacyCutATLAS_300_100[9] = 42.77;
          legacyCutATLAS_300_100[10] = 19.46;
          legacyCutATLAS_300_100[11] = 0.06;

          #ifdef CHECK_CUTFLOW
            if (_cutflows.cfs.empty()) _cutflows.addCutflow(analysis_name(), legacyCutNames);
            _cutflows[analysis_name()].fillinit(event->weight());
          #endif

          for (size_t j=0;j<NCUTS;j++)
          {
            if(
              (j==0) ||

              (j==1 && generator_filter) ||

              (j==2 && generator_filter && nSignalLeptons >= 2) ||

              (j==3 && generator_filter && nSignalLeptons >= 2 && trigger) ||

              (j==4 && generator_filter && nSignalLeptons >= 4 && trigger) ||

              (j==5 && generator_filter && nSignalLeptons >= 4 && trigger && Z1 && Z2) ||

              (j==6 && generator_filter && nSignalLeptons >= 4 && trigger && Z1 && Z2 && met > 50) ||

              (j==7 && generator_filter && nSignalLeptons >= 4 && trigger && Z1 && Z2 && met > 100) ||

              (j==8 && generator_filter && nSignalLeptons >= 4 && trigger && Z1 && Z2 && NbJets == 0) ||

              (j==9 && generator_filter && nSignalLeptons >= 4 && trigger && Z1 && Z2 && NbJets == 0 && met > 100) ||

              (j==10 && generator_filter && nSignalLeptons >= 4 && trigger && Z1 && Z2 && NbJets == 0 && met > 200) ||

              (j==11 && generator_filter && nSignalLeptons >= 5 && trigger)

              )

            #ifdef CHECK_CUTFLOW
              _cutflows[analysis_name()].fill(j+1, true, event->weight());
            #endif
          }
        #endif
      }


      // This function can be overridden by the derived SR-specific classes
      virtual void collect_results()
      {

        COMMIT_CUTFLOWS;
        add_result(SignalRegionData(_counters.at("SR0-ZZ-loose"), 157., {161., 42.}));
        add_result(SignalRegionData(_counters.at("SR0-ZZ-tight"), 17., {18.4, 3.3}));
        add_result(SignalRegionData(_counters.at("SR0-ZZ-loose-bveto"), 5., {7.3, 2.15}));
        add_result(SignalRegionData(_counters.at("SR0-ZZ-tight-bveto"), 1., {1.1, 0.4}));
        add_result(SignalRegionData(_counters.at("SR0-loose-bveto"), 11., {11.5, 2.55}));
        add_result(SignalRegionData(_counters.at("SR0-tight-bveto"), 1., {3.5, 2.1}));
        add_result(SignalRegionData(_counters.at("SR0-breq"), 3., {1.16, 0.26}));
        add_result(SignalRegionData(_counters.at("SR5L"), 21., {12.4, 2.3}));

      }


    protected:
      void analysis_specific_reset()
      {
        for (auto& pair : _counters) { pair.second.reset(); }
        #ifdef CHECK_CUTFLOW
        #endif
      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(ATLAS_SUSY_2018_02)


  }
}
