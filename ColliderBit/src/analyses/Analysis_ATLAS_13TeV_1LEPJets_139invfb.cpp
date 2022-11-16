///
///  \author Tomasz Procter
///  \date 2022 November
///  *********************************************

// Based on 
// https://arxiv.org/pdf/2106.09609.pdf
// and using the provided simpleAnalyis code liberally to understand the analysis logic

// CR/VR bins not in the simpleAnalyis not included
// Still puzzled by some discrepancies between the simpleAnalysis and the paper.


#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>
#include <algorithm>
#include <fstream>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"

#include "lwtnn/LightweightGraph.hh"
#include "lwtnn/parse_json.hh"

// #define CHECK_CUTFLOW

using namespace std;

namespace Gambit
{
  namespace ColliderBit
  {

    class Analysis_ATLAS_13TeV_1LEPJets_139invfb : public Analysis
    {

    protected:

      // Counters for the number of accepted events for each signal region
      std::map<string, EventCounter> _counters = {
        //2lsc - jet counting bins
        {"ss_10j20_0b", EventCounter("ss_10j20_0b")},
        {"ss_10j20_3b", EventCounter("ss_10j20_3b")},
        {"ss_8j40_0b", EventCounter("ss_8j40_0b")},
        {"ss_8j40_3b", EventCounter("ss_8j40_3b")},
        {"ss_7j60_0b", EventCounter("ss_7j60_0b")},
        {"ss_7j60_3b", EventCounter("ss_7j60_3b")},
        {"ss_6j80_0b", EventCounter("ss_6j80_0b")},
        {"ss_6j80_3b", EventCounter("ss_6j80_3b")},
        {"ss_6j100_0b", EventCounter("ss_6j100_0b")},
        {"ss_6j100_3b", EventCounter("ss_6j100_3b")},
        //2lsc - shape analysis bin
        {"ss_shape_6j_3b", EventCounter("ss_shape_6j_3b")},

        //1l channel - jet counting bins
        {"1l_15j20_0b", EventCounter("1l_15j20_0b")},
        {"1l_15j20_3b", EventCounter("1l_15j20_3b")},
        {"1l_12j40_0b", EventCounter("1l_12j40_0b")},
        {"1l_12j40_3b", EventCounter("1l_12j40_3b")},
        {"1l_12j60_0b", EventCounter("1l_12j60_0b")},
        {"1l_12j60_3b", EventCounter("1l_12j60_3b")},
        {"1l_10j80_0b", EventCounter("1l_10j80_0b")},
        {"1l_10j80_3b", EventCounter("1l_10j80_3b")},
        {"1l_8j100_0b", EventCounter("1l_8j100_0b")},
        {"1l_8j100_3b", EventCounter("1l_8j100_3b")},
        //1l channel - shape/neural net bins
        {"1l_shape_4j_4b",EventCounter("1l_shape_4j_4b") },
        {"1l_shape_5j_4b",EventCounter("1l_shape_4j_4b) },
        {"1l_shape_6j_4b",EventCounter("1l_shape_4j_4b") },
        {"1l_shape_7j_4b",EventCounter("1l_shape_4j_4b") },
        {"1l_shape_8j_4b",EventCounter("1l_shape_4j_4b") },
      };

    private:

      //The neural network objects:
      std::map<size_t, unique_ptr<lwt::LightweightGraph>> _neuralNets;
      //Where the neural net json files are:
      //TODO: Are there any refdata loading conventions in GAMBIT?
      //TODO: See other TODO in constructo
      std::map<size_t, string> _neuralNetPaths = {{4, (string)GAMBIT_DIR+(string)"/ColliderBit/data/analyses/lwtnn/ATLAS_13TeV_1LEPJets_139invfb_4j.json"},
                                                    {5, (string)GAMBIT_DIR+(string)"/ColliderBit/data/analyses/lwtnn/ATLAS_13TeV_1LEPJets_139invfb_5j.json"},
                                                    {6, (string)GAMBIT_DIR+(string)"/ColliderBit/data/analyses/lwtnn/ATLAS_13TeV_1LEPJets_139invfb_6j.json"},
                                                    {7, (string)GAMBIT_DIR+(string)"/ColliderBit/data/analyses/lwtnn/ATLAS_13TeV_1LEPJets_139invfb_7j.json"},
                                                    {8, (string)GAMBIT_DIR+(string)"/ColliderBit/data/analyses/lwtnn/ATLAS_13TeV_1LEPJets_139invfb_8j.json"}};
      //_neuralNet cut off scores.
      map<size_t, double> _neuralNetCuts = {{4, 0.73}, {5, 0.76}, {6, 0.77}, {7, 0.72}, {8, 0.73}};                                                  

      bool _lepCatis_2lsc;

      struct ptComparison
      {
        bool operator() (const HEPUtils::Particle* i,const HEPUtils::Particle* j) {return (i->pT()>j->pT());}
      } comparePt;

      struct ptJetComparison
      {
        bool operator() (const HEPUtils::Jet* i,const HEPUtils::Jet* j) {return (i->pT()>j->pT());}
      } compareJetPt;

      // lepton-lepton overlap removal
      // Discards leptons1 if they are within DeltaRMax of a lepton2
      void LeptonLeptonOverlapRemoval(vector<const HEPUtils::Particle*>& leptons1, 
                                      vector<const HEPUtils::Particle*>& leptons2, 
                                      double DeltaRMax)
      {
        vector<const HEPUtils::Particle*> survivors;
        for(const HEPUtils::Particle* lep1 : leptons1)
        {
          bool overlap = false;
          for(const HEPUtils::Particle* lep2 : leptons2)
          {
            double dR = lep1->mom().deltaR_eta(lep2->mom());
            if(fabs(dR) <= DeltaRMax) overlap = true;
          }
          if(!overlap) survivors.push_back(lep1);
        }
        leptons1 = survivors;
        return;
      }

      // Jet lepton overlap removal
      // Discards jets if they are within DeltaRMax of a lepton
      // Optionally don't filter out btagged jets
      //Also optionally require a max number of jet tracks to still filter
      // (Use -1 to switch off)
      //TODO - How do I get the number of tracks?
      void JetLeptonOverlapRemoval(vector<const HEPUtils::Jet*>& jets,
                                    vector<const HEPUtils::Particle*>& leptons,
                                    double DeltaRMax, bool ignoreBtag, ssize_t maxJetTracks)
      {
        vector<const HEPUtils::Jet*> survivors;
        for(const HEPUtils::Jet* jet : jets)
        {
          bool overlap = false;
          if (!(ignoreBtag && jet->btag())){
            for(const HEPUtils::Particle* lepton : leptons) {
              double dR = jet->mom().deltaR_eta(lepton->mom());
              if(fabs(dR) <= DeltaRMax) overlap = true;
            }
          }
          if(!overlap) survivors.push_back(jet);
        }
        jets = survivors;
        return;
      }

      // Lepton jet overlap removal
      // Discards leptons if they are within DeltaRMax of a jet
      void LeptonJetOverlapRemoval(vector<const HEPUtils::Particle*>& leptons, 
                                  vector<const HEPUtils::Jet*>& jets,
                                  double DeltaRMax)
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

      // Removes a lepton from the leptons1 vector if it forms an OS pair with a
      // lepton in leptons2 and the pair has a mass in the range (m_low, m_high).
      void removeOSPairsInMassRange(vector<const HEPUtils::Particle*>& leptons1, vector<const HEPUtils::Particle*>& leptons2, double m_low, double m_high)
      {
        vector<const HEPUtils::Particle*> l1_survivors;
        for(const HEPUtils::Particle* l1 : leptons1)
        {
          bool survived = true;
          for(const HEPUtils::Particle* l2 : leptons2)
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

    //UTILITY FUNCTIONS FOR NN INPUT PARAMETERS

    //Copied wholesale from SimpleAnalysis with some slight logic tweaks
    static double calc_mlj_pair(const HEPUtils::Particle* l1, const HEPUtils::Particle* l2,
                            const std::vector<const HEPUtils::Jet*> &Jets, const size_t max_njets)
    {
      float minmax = 9e9;
      float tmpmass;
      const size_t iterate_max = max(max_njets, Jets.size());
      for(size_t i = 0; i < iterate_max; ++i){
        for(size_t j = 0; j < iterate_max; ++j){
          if(i==j) continue;
          tmpmass = std::max((l1->mom() + Jets[i]->mom()).m(),
                              (l2->mom() + Jets[j]->mom()).m());
          if(tmpmass < minmax) minmax = tmpmass;
        }
      }
      return minmax;
    }

    //Get the mass of the system of the three jets with highest combined pt
    //Required as a neural net input
    static double calc_threejet_max_pt_mass(const std::vector<const HEPUtils::Jet*>& jets){
      double max_pt = 0;
      HEPUtils::P4 max4mom;
      for (size_t i = 0; i < jets.size(); ++i){
        for (size_t j = i+1; j < jets.size(); ++j){
          for (size_t k = j+1; k < jets.size(); ++k){
            if ((jets[i]->mom() + jets[j]->mom() + jets[k]->mom()).pT() > max_pt){
              max_pt = (jets[i]->mom() + jets[j]->mom() + jets[k]->mom()).pT();
              max4mom = (jets[i]->mom() + jets[j]->mom() + jets[k]->mom());
            }
          } 
        }  
      }
      return max4mom.m();
    }

    //Get the mass of the system of the three jets with highest combined pt
    //TODO: Double check handling of MET
    static double calc_threejet_lepmet_max_pt_mass(const std::vector<const HEPUtils::Jet*>& jets,
                      const HEPUtils::Particle* lep, const HEPUtils::P4 met4){
      double max_pt = 0;
      HEPUtils::P4 max4mom;
      for (size_t i = 0; i < jets.size(); ++i){
        for (size_t j = i+1; j < jets.size(); ++j){
          for (size_t k = j+1; k < jets.size(); ++k){
            if ((jets[i]->mom() + jets[j]->mom() + jets[k]->mom() + lep->mom() + met4).pT() > max_pt){
              max4mom = (jets[i]->mom() + jets[j]->mom() + jets[k]->mom() 
                  + lep->mom() + met4);
              max_pt = max4mom.pT();
            }
          } 
        }  
      }
      return max4mom.m();
    }

     //Calculate the minium deltaR between a lepton and a jet
    static double min_dr_lep_jet(const std::vector<const HEPUtils::Jet*>& jets, 
                            const std::vector<const HEPUtils::Particle*>& leptons){
      double min_dr = DBL_MAX;
      for (const Particle* l : leptons){
        for (const Jet* j: jets){
          if (l->mom().deltaR_eta(j->mom()) < min_dr){
            min_dr = l->mom().deltaR_eta(j->mom());
          }
        }
      }
      return min_dr;
    }

    //Helper function for the below, copied from SA for same reason.
    static int countSetBits( int n)
    {
      int count = 0;
      while (n) {
          count += n & 1;
          n >>= 1;
      }
      return count;
    }

    //TODO (or at least nb) Copied almost wholesale from simpleanalysis as 
    //I cannot understand this clearly
    static double calc_minmax_mass(const std::vector<const HEPUtils::Jet*>& jets, int jetdiff=10)
    {
      const int nJets = jets.size();

      //bitwise representation of all jets and for which half they are selected
      // One bit for every jet, marking into which set they are grouped
      const unsigned int bitmax = 1 << nJets;
      float minmass = 999999999;

      for(unsigned int bit=0; bit < bitmax; bit++){
          const int bitcount = countSetBits(bit);
          if (abs(nJets - 2*bitcount) > jetdiff) {
            continue;
          }

          HEPUtils::P4 sum1, sum2;
          // loop through jets and assign to either sum, depending on bit
          for(int i=0; i<nJets; i++) {
              if (bit & (1<<i)) 
                sum1 += jets[i]->mom();
              else
                sum2 += jets[i]->mom();
          }
          if (sum1.m() > sum2.m() && sum1.m() < minmass) 
            minmass = sum1.m();
          else if (sum2.m() > sum1.m() && sum2.m() < minmass)
            minmass = sum2.m();
      }
      return minmass;
    }


    public:

      // Required detector sim
      static constexpr const char* detector = "ATLAS";

      Analysis_ATLAS_13TeV_1LEPJets_139invfb()
      {

        set_analysis_name("ATLAS_13TeV_1LEPJets_139invfb");
        set_luminosity(139);

        //Load the neural networks (one each for 4j - 8j)
        for (size_t i = 4; i <= 8; ++i){
          //TODO: I suspect we're going to end up needing to try and be more file-read efficient about this?
          ifstream input(_neuralNetPaths[i]);
          lwt::GraphConfig cfg = lwt::parse_json_graph(input);
          _neuralNets[i] = make_unique<lwt::LightweightGraph>(cfg);
        }
        

      }

      void run(const HEPUtils::Event* event)
      {
        //=====================================================================
        //OBJECT SELECTION

        // Baseline objects
        vector<const HEPUtils::Particle*> baselineElectrons;
        vector<const HEPUtils::Particle*> baselineElectronCandidates;//(looser criteria, overlap removal only)
        vector<const HEPUtils::Particle*> baselineMuons;
        vector<const HEPUtils::Jet*> baselineJets;
        vector<const HEPUtils::Jet*> bJets;
        HEPUtils::P4 met4 = event->missingmom();
        double met = event->met();
        double metphi = met4.phi();
      
        //ELECTRONS
        for (const HEPUtils::Particle* electron : event->electrons())
        {
          if (electron->pT()>15. && electron->abseta()<2.47 && 
              !(electron->abseta() > 1.37 && electron->abseta() < 1.52)){
                baselineElectrons.push_back(electron);
                baselineElectronCandidates.push_back(electron);
          } 
        }
        // Apply electron efficiency
        ATLAS::applyElectronEff(baselineElectrons);
        ATLAS::applyElectronEff(baselineElectronCandidates);
        // Apply tight electron selection
        //TODO: Is there not an R2 version of this function ?!
        ATLAS::applyTightIDElectronSelection(baselineElectrons);
        ATLAS::applyMediumIDElectronSelectionR2(baselineElectronCandidates);


        //MUONS
        for (const HEPUtils::Particle* muon : event->muons())
        {
          if (muon->pT()>10. && muon->abseta()<2.5) baselineMuons.push_back(muon);
        }
        // Apply muon efficiency
        ATLAS::applyMuonEff(baselineMuons);
        // Missing: Apply "medium" muon ID criteria

        //JETS
        for (const HEPUtils::Jet* jet : event->jets())
        {
          if (jet->pT()>20. && jet->abseta()<2.5) baselineJets.push_back(jet);
        }
        // Missing: Some additional requirements for jets with pT < 60 and abseta < 2.4 (see paper)


        // OVERLAP REMOVAL

        // 1) Remove electron sharing an ID track with a muon
          //Use simpleAnalysis proxy of dR < 0.01.
        LeptonLeptonOverlapRemoval(baselineElectronCandidates, baselineMuons, 0.01);
        LeptonLeptonOverlapRemoval(baselineElectrons, baselineMuons, 0.01);

        // 2) Remove non-btagged jets within 0.2 of an electron candidate
        JetLeptonOverlapRemoval(baselineJets, baselineElectronCandidates, 0.2, true, -1);

        // 3) Remove non b-tagged jets of < 3 tracks within DeltaR = 0.4 of a muon
        //TODO: Track counting doesn't work properly.
        JetLeptonOverlapRemoval(baselineJets, baselineMuons, 0.4, true, -1);

        // 4) Remove electrons and muons within a variable deltaR of a jet
        // n.b discrepancy between simpleAnalysis and paper.



        // Signal objects
        vector<const HEPUtils::Jet*> signalJets = baselineJets;
        vector<const HEPUtils::Particle*> signalElectrons = baselineElectrons;
        vector<const HEPUtils::Particle*> signalMuons = baselineMuons;
        vector<const HEPUtils::Particle*> signalLeptons;
        signalLeptons = signalElectrons;
        signalLeptons.insert(signalLeptons.end(), signalMuons.begin(), signalMuons.end());

        // Missing: pT-dependent isolation criteria for signal leptons (see paper)

        // Sort by pT
        sort(signalJets.begin(), signalJets.end(), compareJetPt);
        sort(signalLeptons.begin(), signalLeptons.end(), comparePt);

        // Count signal leptons and jets
        // size_t nSignalElectrons = signalElectrons.size();
        // size_t nSignalMuons = signalMuons.size();
        size_t nSignalLeptons = signalLeptons.size();
        size_t nSignalJets = signalJets.size();


        // PRESEECTION
        // ====================================================================
          //require at least 1 lepton of pT > 27 GeV and four jets of pT > 20
        if (nSignalLeptons == 0 || signalLeptons[0]->pT() < 27. || nSignalJets < 4){
          return;
        }

        //DECIDE LEPTON CATEGORY
        // ====================================================================
        if (signalLeptons.size() ==2 && signalLeptons[0]->pid()*signalLeptons[1]->pid() > 0){
          _lepCatis_2lsc = true;
        } else {
          _lepCatis_2lsc = false;
        }

        //Count Jets: needed by both channels:
        size_t njets40 = 0; size_t njets60 = 0; size_t njets80 = 0; size_t njets100 = 0;
        size_t nbjets20 = 0; size_t nbjets40 = 0; size_t nbjets60 = 0; size_t nbjets80 = 0; size_t nbjets100 = 0;
        for (const HEPUtils::Jet* j : signalJets){
          if (j->btag()){
            if (j->pT() > 20) {++nbjets20;}
            if (j->pT() > 40) {++njets40; ++nbjets40;}
            if (j->pT() > 60) {++njets60; ++nbjets60;}
            if (j->pT() > 80) {++njets80; ++nbjets80;}
            if (j->pT() > 100) {++njets100; ++nbjets100;}
          } else {
            if (j->pT() > 40) ++njets40;
            if (j->pT() > 60) ++njets60;
            if (j->pT() > 80) ++njets60;
            if (j->pT() > 100) ++njets60;
          }
        }

        // SIGNAL REGIONS
        // =====================================================================
          // _2lsc category
            // Jet counting analysis
        if ( _lepCatis_2lsc){
          if (nSignalJets >= 10){
            if (nbjets20 == 0) _counters.at("ss_10j20_0b").add_event(event);
            else if (nbjets20 >= 3) _counters.at("ss_10j20_3b").add_event(event);
          }
          if (njets40 >= 8){
            if (nbjets40 == 0) _counters.at("ss_8j40_0b").add_event(event);
            else if (nbjets40 >= 3) _counters.at("ss_8j40_3b").add_event(event);
          }
          if (njets60 >= 7){
            if (nbjets60 == 0) _counters.at("ss_7j60_0b").add_event(event);
            else if (nbjets60 >= 3) _counters.at("ss_7j60_3b").add_event(event);
          }
          if (njets80 >= 6){
            if (nbjets80 == 0) _counters.at("ss_6j80_0b").add_event(event);
            else if (nbjets80 >= 3) _counters.at("ss_6j80_3b").add_event(event);
          }
          if (njets100 >= 6){
            if (nbjets100 == 0) _counters.at("ss_6j100_0b").add_event(event);
            else if (nbjets100 >= 3) _counters.at("ss_6j100_3b").add_event(event);
          }
          //2lsc shape analysis
          if (nSignalJets == 6 && nbjets20 > 2){
            if (calc_mlj_pair(signalLeptons[0], signalLeptons[1], signalJets, 4) < 155){
              _counters.at("ss_shape_6j_3b").add_event(event);
            }
          } 
        }
        //-----------------------------------------------
        // 1 lepton channel/category
        else {
          // Jet counting analysis
          if (nSignalJets >= 15){
            if (nbjets20 == 0) _counters.at("1l_15j20_0b").add_event(event);
            else if (nbjets20 >= 3) _counters.at("1l_15j20_0b").add_event(event);
          }
          if (njets40 >= 12){
            if (nbjets40 == 0) _counters.at("1l_12j40_0b").add_event(event);
            else if (nbjets40 >= 3) _counters.at("1l_12j40_3b").add_event(event);
          }
          if (njets60 >= 12){
            if (nbjets60 == 0) _counters.at("1l_12j60_0b").add_event(event);
            else if (nbjets60 >= 3) _counters.at("1l_12j60_3b").add_event(event);
          }
          if (njets80 >= 10){
            if (nbjets80 == 0) _counters.at("1l_10j80_0b").add_event(event);
            else if (nbjets80 >= 3) _counters.at("1l_10j80_0b").add_event(event);
          }
          if (njets100 >= 8){
            if (nbjets100 == 0) _counters.at("1l_8j100_0b").add_event(event);
            else if (nbjets100 >= 3) _counters.at("1l_8j100_3b").add_event(event);
          }

          //Shape based analysis. Finally the neural net shows its face.
          // Only for 4 <= numjets <= 8
          if (nSignalJets >= 4 && nSignalJets <= 8){
            
            constexpr double Escale = 100;//Energy scale for dimensionful quantities.

            const map<string, double> nn_input_map = {
              //Whole event level features
              {"n_jet", nSignalJets},
              {"n_bcat", (nbjets20 <= 3) ? nbjets20 - 1 : 3},
              {"n_bjet", nbjets20},
              {"three_jet_maxpt_mass", calc_threejet_max_pt_mass(signalJets) / Escale},
              {"ht_jet", std::accumulate(signalJets.begin(), signalJets.end(), 0.0, 
                            [](double t, const HEPUtils::Jet* j){return t + j->pT();}) / Escale},
              {"ht_bjet", std::accumulate(signalJets.begin(), signalJets.end(), 0.0, 
                            [](double t, const HEPUtils::Jet* j){return t + (j->btag())?(j->pT()):0.;}) / Escale},
              {"three_jet_lep_met_mass_max_pt", 
                  calc_threejet_lepmet_max_pt_mass(signalJets, signalLeptons[0], met4)/Escale},
              //TODO see function defintion^^^
              {"minDeltaRlj", min_dr_lep_jet(signalJets, signalLeptons)},
              {"minmax_mass", calc_minmax_mass(signalJets) / Escale},
              {"met", met},
              {"met_phi", metphi},

              //Jet pts (n.b at least four jets must exist to pass presel)
              {"jet_pt_0", signalJets[0]->pT()/Escale},
              {"jet_pt_1", signalJets[1]->pT()/Escale},
              {"jet_pt_2", signalJets[2]->pT()/Escale},
              {"jet_pt_3", signalJets[3]->pT()/Escale},
              {"jet_pt_4", signalJets.size() > 4 ? signalJets[4]->pT()/Escale: 1e-7},
              {"jet_pt_5", signalJets.size() > 5 ? signalJets[5]->pT()/Escale: 1e-7},
              {"jet_pt_6", signalJets.size() > 6 ? signalJets[6]->pT()/Escale: 1e-7},
              {"jet_pt_7", signalJets.size() > 7 ? signalJets[7]->pT()/Escale: 1e-7},
              {"jet_pt_8", signalJets.size() > 8 ? signalJets[8]->pT()/Escale: 1e-7},
              {"jet_pt_9", signalJets.size() > 9 ? signalJets[9]->pT()/Escale: 1e-7},

              //Jet etas (n.b at least four jets must exist to pass presel)
              {"jet_eta_0", signalJets[0]->eta()},
              {"jet_eta_1", signalJets[1]->eta()},
              {"jet_eta_2", signalJets[2]->eta()},
              {"jet_eta_3", signalJets[3]->eta()},
              {"jet_eta_4", signalJets.size() > 4 ? signalJets[4]->eta(): 1e-7},
              {"jet_eta_5", signalJets.size() > 5 ? signalJets[5]->eta(): 1e-7},
              {"jet_eta_6", signalJets.size() > 6 ? signalJets[6]->eta(): 1e-7},
              {"jet_eta_7", signalJets.size() > 7 ? signalJets[7]->eta(): 1e-7},
              {"jet_eta_8", signalJets.size() > 8 ? signalJets[8]->eta(): 1e-7},
              {"jet_eta_9", signalJets.size() > 9 ? signalJets[9]->eta(): 1e-7},

              //Jet phis (n.b at least four jets must exist to pass presel)
              {"jet_phi_0", signalJets[0]->phi()},
              {"jet_phi_1", signalJets[1]->phi()},
              {"jet_phi_2", signalJets[2]->phi()},
              {"jet_phi_3", signalJets[3]->phi()},
              {"jet_phi_4", signalJets.size() > 4 ? signalJets[4]->phi(): -5},
              {"jet_phi_5", signalJets.size() > 5 ? signalJets[5]->phi(): -5},
              {"jet_phi_6", signalJets.size() > 6 ? signalJets[6]->phi(): -5},
              {"jet_phi_7", signalJets.size() > 7 ? signalJets[7]->phi(): -5},
              {"jet_phi_8", signalJets.size() > 8 ? signalJets[8]->phi(): -5},
              {"jet_phi_9", signalJets.size() > 9 ? signalJets[9]->phi(): -5},

              //Jet energies (n.b at least four jets must exist to pass presel)
              {"jet_e_0", signalJets[0]->E()/Escale},
              {"jet_e_1", signalJets[1]->E()/Escale},
              {"jet_e_2", signalJets[2]->E()/Escale},
              {"jet_e_3", signalJets[3]->E()/Escale},
              {"jet_e_4", signalJets.size() > 4 ? signalJets[4]->E()/Escale: 1e-7},
              {"jet_e_5", signalJets.size() > 5 ? signalJets[5]->E()/Escale: 1e-7},
              {"jet_e_6", signalJets.size() > 6 ? signalJets[6]->E()/Escale: 1e-7},
              {"jet_e_7", signalJets.size() > 7 ? signalJets[7]->E()/Escale: 1e-7},
              {"jet_e_8", signalJets.size() > 8 ? signalJets[8]->E()/Escale: 1e-7},
              {"jet_e_9", signalJets.size() > 9 ? signalJets[9]->E()/Escale: 1e-7},

              //Jet btags (n.b at least four jets must exist to pass presel)
              //TODO: WORK OUT
              {"jet_btag_bin_0", (signalJets[0]->btag() ? 5 : 1)},
              {"jet_btag_bin_1", (signalJets[1]->btag() ? 5 : 1)},
              {"jet_btag_bin_2", (signalJets[2]->btag() ? 5 : 1)},
              {"jet_btag_bin_3", (signalJets[3]->btag() ? 5 : 1)},
              {"jet_btag_bin_4", signalJets.size() > 4 ? (signalJets[4]->btag() ? 5 : 1): 0},
              {"jet_btag_bin_5", signalJets.size() > 5 ? (signalJets[5]->btag() ? 5 : 1) : 0},
              {"jet_btag_bin_6", signalJets.size() > 6 ? (signalJets[6]->btag() ? 5 : 1) : 0},
              {"jet_btag_bin_7", signalJets.size() > 7 ? (signalJets[7]->btag() ? 5 : 1) : 0},
              {"jet_btag_bin_8", signalJets.size() > 8 ? (signalJets[8]->btag() ? 5 : 1) : 0},
              {"jet_btag_bin_9", signalJets.size() > 9 ? (signalJets[9]->btag() ? 5 : 1) : 0},

              //Leptons features
              {"lepton_pt", signalLeptons[0]->pT()},
              {"lepton_eta", signalLeptons[0]->eta()},
              {"lepton_phi", signalLeptons[0]->phi()},
              {"lepton_e", signalLeptons[0]->E()},
            };
            map<string, map<string, double>> nn_input = {{"node_0", nn_input_map}};
            map<string, double> nn_output = _neuralNets.at(nSignalJets)->compute(nn_input);

            //TODO: Simple analysis has a histo here which would be great for debugging purposes.

            if(nn_output["out_0"] > _neuralNetCuts[nSignalJets]){
              _counters.at("1l_shape_"+std::to_string(nSignalJets)+"j_4b").add_event(event);
            }

          }

        }
      }

      /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
      void combine(const Analysis* other)
      {
        const Analysis_ATLAS_13TeV_1LEPJets_139invfb* specificOther
                = dynamic_cast<const Analysis_ATLAS_13TeV_1LEPJets_139invfb*>(other);

        for (auto& pair : _counters) { pair.second += specificOther->_counters.at(pair.first); }
      }

      // This function can be overridden by the derived SR-specific classes
      virtual void collect_results() {

        add_result(SignalRegionData(_counters.at("SR0A"), 13., {10.2, 2.1}));
        add_result(SignalRegionData(_counters.at("SR0B"),  2., {1.31, 0.24}));
        add_result(SignalRegionData(_counters.at("SR0C"), 47., {37., 9.}));
        add_result(SignalRegionData(_counters.at("SR0D"), 10., {4.1, 0.7}));


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
        for (auto& pair : _counters) { pair.second.reset(); }
        #ifdef CHECK_CUTFLOW
          std::fill(cutFlowVector.begin(), cutFlowVector.end(), 0);
        #endif
      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(ATLAS_13TeV_1LEPJets_139invfb)


  }
}
