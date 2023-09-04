///
///  \author Tomasz Procter
///  \date 2023 August
///
///
/// Based on arXiv:2307.07584
/// Search for single production of VLQ T -> Zt
/// in multilepton final states
///  *********************************************

// #define CHECK_CUTFLOW

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"
#include "fastjet/contrib/VariableRPlugin.hh"

using namespace std;

namespace Gambit
{
  namespace ColliderBit
  {

    class Analysis_ATLAS_13TeV_VLQ_VLT_Zt_Multilep_139invfb : public Analysis
    {

      protected:
        // region map
        // TODO: I'm including the CRs/VRs because I can, plus useful validation.
        std::map<string, EventCounter> _counters = {
          //TODO: really the analysis fits bins of the meff histogram in each SR.
          // But do we have all the required info to actually implement this.
          // 2 lepton channel regions
          {"2lSR", EventCounter("2lSR")},
          {"2lCR1", EventCounter("2lCR1")},
          {"2lCR2", EventCounter("2lCR2")},
          {"2lCR3", EventCounter("2lCR3")},
          {"2lVR1", EventCounter("2lVR1")},
          {"2lVR2", EventCounter("2lVR2")},

          // 3 lepton channel regions
          {"3lSR", EventCounter("3lSR")},
          {"3lVV", EventCounter("3lVV")},
          {"3lMixed", EventCounter("3lMixed")},
          {"3lttX", EventCounter("3lttX")},
          {"3lVR", EventCounter("3lVR")},
        };

      private:

        // Internally used masses
        constexpr static double mZ = 91.1876; // [GeV]
        constexpr static double mtop = 172.76; // [GeV]

        #ifdef CHECK_CUTFLOW
        // Cut-flow variables
        string benchmark = BENCHMARK;
        size_t NCUTS=42;
        vector<double> _cutflow_GAMBIT{vector<double>(NCUTS)};
        vector<double> _cutflow_ATLAS{vector<double>(NCUTS)};
        vector<string> _cuts{vector<string>(NCUTS)};
        #endif

      public:

        // Required detector sim
        static constexpr const char* detector = "ATLAS";

        Analysis_ATLAS_13TeV_VLQ_VLT_Zt_Multilep_139invfb()
        {
          set_analysis_name("ATLAS_13TeV_VLQ_VLT_Zt_Multilep_139invfb");
          set_luminosity(139.);
        }

        // Discards jets if they are within DeltaRMax of a lepton
        // Optionally spare b-tagged jets and/or set a "sparing" number of tracks
        void JetLeptonOverlapRemoval(vector<const HEPUtils::Jet*> &jetvec, vector<const HEPUtils::Particle*> &lepvec, const double DeltaRMax,
                                        const bool sparebtags=false, const int minTracks=-1)
        {
          vector<const HEPUtils::Jet*> Survivors;

          for(unsigned int itjet = 0; itjet < jetvec.size(); itjet++)
          {
            // If sparing b-tagged jets, deal with this immediately
            if (sparebtags && jetvec.at(itjet)->btag()) continue;
            // If sparing jets with >= minTracks, deal with this immediately
            // TODO: this appears impossible with HEPUtils::Jet. welp.

            bool overlap = false;
            HEPUtils::P4 jetmom=jetvec.at(itjet)->mom();
            for(unsigned int itlep = 0; itlep < lepvec.size(); itlep++)
            {
              HEPUtils::P4 lepmom=lepvec.at(itlep)->mom();
              double dR;

              dR=jetmom.deltaR_eta(lepmom);

              if(fabs(dR) <= DeltaRMax) overlap=true;
            }
            if(overlap) continue;
            Survivors.push_back(jetvec.at(itjet));
          }
          jetvec=Survivors;

          return;
        }

        // Discards leptons if they are within DeltaRMax of a jet
        void LeptonJetOverlapRemoval(vector<const HEPUtils::Particle*> &lepvec, vector<const HEPUtils::Jet*> &jetvec, double DeltaRMax)
        {

          vector<const HEPUtils::Particle*> Survivors;

          for(unsigned int itlep = 0; itlep < lepvec.size(); itlep++)
          {
            bool overlap = false;
            HEPUtils::P4 lepmom=lepvec.at(itlep)->mom();
            for(unsigned int itjet= 0; itjet < jetvec.size(); itjet++)
            {
              HEPUtils::P4 jetmom=jetvec.at(itjet)->mom();
              double dR;

              dR=jetmom.deltaR_eta(lepmom);

              if(fabs(dR) <= DeltaRMax) overlap=true;
            }
            if(overlap) continue;
            Survivors.push_back(lepvec.at(itlep));
          }
          lepvec=Survivors;

          return;
        }

        // Discards leptons if they are within a cone DeltaR = min (rmax, rmin+rho/lep.pt) of a jet (used for muon removal)
        void LeptonJetVariableROverlapRemoval(vector<const HEPUtils::Particle*> &lepvec, vector<const HEPUtils::Jet*> &jetvec, double rMax, double rMin, double rho)
        {
          vector<const HEPUtils::Particle*> Survivors;

          for(unsigned int itlep = 0; itlep < lepvec.size(); itlep++)
          {
            bool overlap = false;
            HEPUtils::P4 lepmom=lepvec.at(itlep)->mom();
            const double dRcut = min(rMax, rMin+rho/lepmom.pT());
            for(unsigned int itjet= 0; itjet < jetvec.size(); itjet++)
            {
              HEPUtils::P4 jetmom=jetvec.at(itjet)->mom();
              double dR;

              dR=jetmom.deltaR_eta(lepmom);

              if(fabs(dR) <= dRcut) overlap=true;
            }
            if(overlap) continue;
            Survivors.push_back(lepvec.at(itlep));
          }
          lepvec=Survivors;

          return;
        }

        // Trim reclustered jets (and conveniently apply pt/eta cuts at the same time)
        static void trimJets(const vector<FJNS::PseudoJet> &pjs_in, vector<Jet> & largeJetsOut,
                      const double frac=0.00, const double minPt = 0.,
                      const double maxEta = 6., const double minPt_twosubJets = 0.){
          largeJetsOut.clear();
          for (const FJNS::PseudoJet & pj : pjs_in){
            if (pj.pt() < minPt || abs(pj.eta()) > maxEta || 
              (pj.pt() < minPt_twosubJets && pj.constituents().size() == 1)) continue;
            const double vetoPt = frac*pj.pt();
            P4 running_total;
            vector<FJNS::PseudoJet> preserved_subjets;
            for (const FJNS::PseudoJet & constit : pj.constituents()){
              if (constit.pt() > vetoPt){
                preserved_subjets.push_back(constit);
                running_total += P4(constit.px(), constit.py(), constit.pz(), constit.E());
              }
            }
            if (running_total.pT() < minPt || running_total.abseta() > maxEta || 
              (running_total.pT() < minPt_twosubJets && preserved_subjets.size() == 1)) continue;
            largeJetsOut.emplace_back(running_total);
          }
        }


        
        // Main event analysis
        //
        void run(const HEPUtils::Event* event)
        {
          //
          // Baseline objects
          //

          // Get the missing energy in the event
          double met = event->met();
          HEPUtils::P4 metVec = event->missingmom();


          // Electrons
          vector<const HEPUtils::Particle*> electrons;
          for (const HEPUtils::Particle* electron : event->electrons())
          {
            if (electron->pT() > 28  && electron->abseta() < 2.47 && !(electron->abseta() > 1.37 && electron->abseta() < 1.52))
            {
              electrons.push_back(electron);
            }
          }
          // Apply electron reconstruction efficiency from 1908.00005
          ATLAS::applyElectronReconstructionEfficiency2020(electrons, "Candidate");

          // Muons
          vector<const HEPUtils::Particle*> muons;
          for (const HEPUtils::Particle* muon : event->muons())
          {
            if (muon->pT() > 28 && fabs(muon->eta()) < 2.5)
            {
              muons.push_back(muon);
            }
          }
          // Apply muon ID efficiency from "Medium" criteria in 2012.00578
          ATLAS::applyMuonIDEfficiency2020(muons, "Medium");

          // Apply cuts to get signal electrons
          // Apply electron isolation efficiency from "Tight" criteria in 1908.00005
          ATLAS::applyElectronIsolationEfficiency2020(electrons, "Tight");
          // Apply muon isolation efficiency from "Tight" criteria in 2012.00578
          // TODO: double check this -> Paper says Medium, but only options are tight/loose
          ATLAS::applyMuonIsolationEfficiency2020(muons, "Tight");

          // Jets
          vector<const HEPUtils::Jet*> centralJets;
          vector<const HEPUtils::Jet*> forwardJets;
          for (const HEPUtils::Jet* jet : event->jets())
          {
            if (jet->pT() > 25. && jet->abseta() < 2.5 )
              centralJets.push_back(jet);
            else if (jet->pT() > 35. && jet->abseta() < 4.5 )
              forwardJets.push_back(jet);
          }
          // b-jets
          const double btag = 0.77; const double cmisstag = 1./6.; const double misstag = 1./192.;
          size_t nb = 0;
          vector<const HEPUtils::Jet*> bJets;
          for ( const HEPUtils::Jet* jet : centralJets )
          {
            // Tag b-jet
            if( jet->btag())
            {
              if(random_bool(btag) )
              {
                bJets.push_back(jet);
                nb++;
              }
            }
            // Misstag c-jet
            else if( !jet->btag() && jet->ctag())
            {
              if (random_bool(cmisstag))
              {
                bJets.push_back(jet);
                nb++;
              }
            } 
            // Misstag light jet
            else if( !jet->btag() && !jet->ctag())
            {
              if (random_bool(misstag) )
              {
                bJets.push_back(jet);
                nb++;
              }
            } 
          }

          //
          // Overlap removal
          //

          // Remove jets \Delta R < 0.2 from electrons
          JetLeptonOverlapRemoval(centralJets, electrons, 0.2);
          JetLeptonOverlapRemoval(forwardJets, electrons, 0.2);
          // Remove electrons \Delta R < 0.4 from jets
          LeptonJetOverlapRemoval(electrons, centralJets, 0.4);
          LeptonJetOverlapRemoval(electrons, forwardJets, 0.4);
          // Remove Jets within 0.2 of a muon IF jet not btagged and jet has <= 2 tracks
          // TODO: ntracks requirement not currently doable -- skipped for now.
          // Remove Muons within min(0.4, 0.04+10/mu.pt) of remainning jets
          LeptonJetVariableROverlapRemoval(muons, centralJets, 0.4, 0.04, 10);
          LeptonJetVariableROverlapRemoval(muons, forwardJets, 0.4, 0.04, 10);
          
          //
          // Signal objects
          //

          // We need at least two same flavour leptons - save time and quit now if we ain't got em.
          if (electrons.size() < 2 && muons.size() < 2) {return;}

          // TODO: is HT defined on central + forward or just central
          double HT = scalarSumPt(centralJets);
          
          // 
          // Actually start analysing
          // 

          // We need as OSSF pair
          vector<pair<Particle, Particle>> ossf_pairs;
          for (size_t i = 0; i < electrons.size(); ++i)
          {
            for (size_t j = 0; j < i; ++j)
            {
              // Check if the pair have opposite sign
              if (electrons[i]->pid() != electrons[j]->pid())
              {
                ossf_pairs.push_back({electrons[i], electrons[j]});
              }
            } 
          }
          for (size_t i = 0; i < muons.size(); ++i)
          {
            for (size_t j = 0; j < i; ++j)
            {
              // Check if the pair have opposite sign
              if (muons[i]->pid() != muons[j]->pid())
              {
                ossf_pairs.push_back({muons[i], muons[j]});
              }
            } 
          }
          // Pick the pair with the closest mass to the Z boson (must be within 10GeV)
          double bestMassDiff = 10;
          pair<Particle, Particle> zcandidate_pair;
          bool zfound = false;
          for (const pair<Particle, Particle> & p : ossf_pairs)
          {
            const double pairmass = (p.first.mom()+p.second.mom()).m();
            if (fabs(pairmass-mZ) < bestMassDiff)
            {
              zcandidate_pair = p;
              bestMassDiff = fabs(pairmass-mZ);
              zfound = true;
            }
          }
          if (!zfound) {return;};
          P4 zCandidate = zcandidate_pair.first.mom()+zcandidate_pair.second.mom();

          // The parting of the ways: 2 lepton or 3(+) lepton channel
          
          /////////////////////////////////////////////////////////////////////
          // 2l Channel
          if (muons.size() + electrons.size() == 2)
          {
            // Require HT > 300GeV
            if (HT < 300) {return;};

            vector<Jet> vrcJets;
            {
              vector<fastjet::PseudoJet> jetsIn;
              // TODO: is there a nicer way of converting pseudojets<->heputils jets?
              for (size_t i = 0; i < centralJets.size(); ++i){
                jetsIn.push_back(fastjet::PseudoJet(centralJets[i]->mom().px(), 
                                                    centralJets[i]->mom().py(),
                                                    centralJets[i]->mom().pz(),
                                                    centralJets[i]->mom().E()));
              }
              // TODO: min/max R not actually given, need to be double checked.
              fastjet::JetDefinition::Plugin* variableRplugin =
                 new fastjet::contrib::VariableRPlugin(mtop*2, 0.4, 1.5, fastjet::contrib::VariableRPlugin::AKTLIKE);
              fastjet::JetDefinition jdef(variableRplugin);
              fastjet::ClusterSequence cseq(jetsIn, jdef);
              vector<FJNS::PseudoJet> VRC_jets = cseq.inclusive_jets();
              
              //TODO: min eta cut? Constituent check?
              trimJets(VRC_jets, vrcJets, 0.00, 200, 2.0, 700);
            }
            // Require at least one vRC jet:
            if (vrcJets.size() == 0) return;

            //Reconstruct the momentum of the top quark:
            const P4 llJ = zCandidate + vrcJets[0].mom();

            //Require m_llJ > HT+ETMiss
            if (HT + met > llJ.m()) return;

            // 2l channel presel passed!
            const size_t nTopTags =  std::count_if(vrcJets.begin(), vrcJets.end(),
                                                  [](const Jet &j){return j.mass() >= 140;});
            const size_t nTopVetoes = vrcJets.size() - nTopTags;

            // 2lCR1, 2lVR1, 2lSR:
            if (forwardJets.size() > 0){
              if (nTopTags >= 1 && nb >= 1)
              {
                _counters["2lSR"].add_event(event);
              }
              else if (nTopTags >= 1 && nb == 0)
              {
                _counters["2lVR1"].add_event(event);
              }
              if (nTopVetoes >= 1 && nb == 0)
              {
                _counters["2lCR1"].add_event(event);
              }
              return;
            }
            // 2lCR2, 2lCR3, 2lVR2
            else {
              if (nTopTags >= 1 && nb >= 1)
              {
                _counters["2lVR2"].add_event(event);
              }
              else if (nTopTags >= 1 && nb == 0)
              {
                _counters["2lCR3"].add_event(event);
              }
              if (nTopVetoes >= 1 && nb >= 1)
              {
                _counters["2lCR2"].add_event(event);
              }
              return;
            }
          }
          /////////////////////////////////////////////////////////////////////
          // 3l Channel
          else {
            // Require at least two central Jets
            if (centralJets.size() < 2) {return;};

            //3lVV CR
            if (nb == 0)
            {
              _counters["3lVV"].add_event(event);
              return;
            }

            // Identify lead bJet.
            sortByPt(centralJets);
            sortByPt(bJets);

            // Identify the "third" lepton - highest pt lepton not in zcandidate pair.
            Particle lepton3;
            {
              double max_pt = 0;
              for (const Particle* e : electrons)
              {
                if (e->mom().deltaR_eta(zcandidate_pair.first) < 0.01 || e->mom().deltaR_eta(zcandidate_pair.second) < 0.01 )
                  continue;
                if (e->pT() > max_pt)
                {
                  lepton3 = e;
                  max_pt = e->pT();
                }
              }
              for (const Particle* mu : muons)
              {
                if (mu->mom().deltaR_eta(zcandidate_pair.first) < 0.01 || mu->mom().deltaR_eta(zcandidate_pair.second) < 0.01 )
                  continue;
                if (mu->pT() > max_pt)
                {
                  lepton3 = mu;
                  max_pt = mu->pT();
                }
              }
            }

            //3lMixed && 3lttX CRs
            if (forwardJets.size() == 0)
            {
              if (zCandidate.deltaPhi(lepton3) < 2.6)
              {
                if (nb == 1)
                {
                  _counters["3lMixed"].add_event(event);
                }
                else if (nb >= 2)
                {
                  _counters["3lttX"].add_event(event);
                }
                else return;
              }
              else return;
            }
            // All other regions: >= 1 forward jet
            else {
              
              const Jet& leadbjet = *bJets[0];
              
              // 3l VR
              if (zCandidate.deltaPhi(lepton3) < M_PI_2 || zCandidate.deltaPhi(leadbjet) < M_PI_2)
              {
                _counters["3lVR"].add_event(event);
                return;
              }

              // 3l SR
              else if (zCandidate.deltaPhi(lepton3) > M_PI_2 && zCandidate.deltaPhi(leadbjet) > M_PI_2)
              {
                // Require lead lep pt > 200 GeV
                sortByPt(electrons); sortByPt(muons);
                const double maxleppt = max(electrons.size()!= 0 ? electrons[0]->pT() : 0.0, muons.size()!=0 ? muons[0]->pT() : 0.0);
                if (maxleppt < 200) {return;};

                //pt(zCandidate) > 300 GeV
                if (zCandidate.pT() < 300) {return;};

                // HT*nJets < 6TeV
                // TODO: still unclear if this is nCentral or nCentral + nFwd;
                if (centralJets.size()*HT > 6000 ) {return;};

                _counters["3lSR"].add_event(event);

              }
            }
          }
        } // End of event analysis


        /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
        void combine(const Analysis* other)
        {
          const Analysis_ATLAS_13TeV_VLQ_VLT_Zt_Multilep_139invfb* specificOther = dynamic_cast<const Analysis_ATLAS_13TeV_VLQ_VLT_Zt_Multilep_139invfb*>(other);
          for (auto& pair : _counters) { pair.second += specificOther->_counters.at(pair.first); }
        }


        void collect_results()
        {
          // TODO: Paper only supplies post-fit numbers.
          // Maybe hepdata will be available at some point?
          // Sig regions
          add_result(SignalRegionData(_counters.at("2lSR"), 181, {174, 9}));
          add_result(SignalRegionData(_counters.at("3lSR"), 24, {21, 2.2}));

          // Control regions
          add_result(SignalRegionData(_counters.at("2lCR1"), 4887, {4886, 70}));
          add_result(SignalRegionData(_counters.at("2lCR2"), 3818, {3821, 60}));
          add_result(SignalRegionData(_counters.at("2lCR3"), 3735, {3727, 60}));
          add_result(SignalRegionData(_counters.at("2lVR1"), 704, {732, 16}));
          add_result(SignalRegionData(_counters.at("2lVR2"), 846, {802, 24}));

          add_result(SignalRegionData(_counters.at("3lVV"), 4590, {4594, 70}));
          add_result(SignalRegionData(_counters.at("3lVR"), 21, {27, 3}));
          add_result(SignalRegionData(_counters.at("3lMixed"), 690, {692, 26}));
          add_result(SignalRegionData(_counters.at("3lttX"), 279, {281, 16}));
        }

        void analysis_specific_reset()
        {
          // Clear signal regions
          for (auto& pair : _counters) { pair.second.reset(); }
        }

    };


    // Factory fn
    DEFINE_ANALYSIS_FACTORY(ATLAS_13TeV_VLQ_VLT_Zt_Multilep_139invfb)

  }
}

