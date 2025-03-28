///
/// ATLAS 3 b jets + MET, 139invfb
///
/// Based on arXiV:2211.08028
///
/// \author Tomasz Procter
/// \date 2023 August
///
/// Note 1: This analysis requires ONNXRunTime for the Neural Net signal regions.
///
/// Note 2: The Gtb signal regions "SR_Gtb_[M,B,C]" don't work. They use the same variables as all
///         the other regions, but my obtained cutflows are consistently greater by a factor of 2.
///         I observed the same feature when coding the analysis up in Rivet.
///         For now, I've commented out the `add_result` lines to make sure they're not accidentally used.
///
/// *********************************************
#include "gambit/cmake/cmake_variables.hpp"
#ifndef EXCLUDE_ONNXRUNTIME

#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"
#include "gambit/ColliderBit/analyses/Cutflow.hpp"
#include "gambit/ColliderBit/onnx_rt_wrapper.hpp"

// Let's be flexible about fjcore/fastjet
// (define structure copied from heputils/FastJet.h)
#ifndef FJCORE
#ifndef FJNS
#define FJNS fastjet
#endif
#include "fastjet/PseudoJet.hh"
#include "fastjet/ClusterSequence.hh"
#else 
#include "fjcore.hh"
#ifndef FJNS
#define FJNS fjcore
#endif
#endif

using namespace std;

// Renamed from: 
//        Analysis_ATLAS_13TeV_3b_NN_139invfb

#define CHECK_CUTFLOWS

namespace Gambit {

  namespace ColliderBit {

    class Analysis_ATLAS_SUSY_2018_30 : public Analysis {

    protected:
      // Signal region map
      std::map<string, EventCounter> _counters = {
        // C&C regions
        {"SR_Gtt_0l_B", EventCounter("SR_Gtt_0l_B")},
        {"SR_Gtt_0l_M1", EventCounter("SR_Gtt_0l_M1")},
        {"SR_Gtt_0l_M2", EventCounter("SR_Gtt_0l_M2")},
        {"SR_Gtt_0l_C", EventCounter("SR_Gtt_0l_C")},

        {"SR_Gtt_1l_B", EventCounter("SR_Gtt_1l_B")},
        {"SR_Gtt_1l_M1", EventCounter("SR_Gtt_1l_M1")},
        {"SR_Gtt_1l_M2", EventCounter("SR_Gtt_1l_M2")},
        {"SR_Gtt_1l_C", EventCounter("SR_Gtt_1l_C")},

        {"SR_Gbb_B", EventCounter("SR_Gbb_B")},
        {"SR_Gbb_M", EventCounter("SR_Gbb_M")},
        {"SR_Gbb_C", EventCounter("SR_Gbb_C")},

        {"SR_Gtb_B", EventCounter("SR_Gtb_B")},
        {"SR_Gtb_M", EventCounter("SR_Gtb_M")},
        {"SR_Gtb_C", EventCounter("SR_Gtb_C")},

        // NN regions
        {"SR_Gtt_2100_1", EventCounter("SR_Gtt_2100_1")},
        {"SR_Gtt_1800_1", EventCounter("SR_Gtt_1800_1")},
        {"SR_Gtt_2300_1200", EventCounter("SR_Gtt_2300_1200")},
        {"SR_Gtt_1900_1400", EventCounter("SR_Gtt_1900_1400")},

        {"SR_Gbb_2800_1400", EventCounter("SR_Gbb_2800_1400")},
        {"SR_Gbb_2300_1000", EventCounter("SR_Gbb_2300_1000")},
        {"SR_Gbb_2100_1600", EventCounter("SR_Gbb_2100_1600")},
        {"SR_Gbb_2000_1800", EventCounter("SR_Gbb_2000_1800")},
      };

    private:

      Cutflows _cutflows;
      std::unique_ptr<onnx_rt_wrapper> _nn;
      
    public:

      // Required detector sim
      static constexpr const char* detector = "ATLAS";

      // Values taken from fig 17, https://arxiv.org/pdf/1510.03823.pdf
      // (old but most recent JVT publication)
      // This is almost certainly, too conservative.
      static double JVT_eff(const Jet &j){
        if (j.abseta() > 2.4) return 1.;
        if (j.pT() <= 20 || j.pT() >= 60) return 1.;

        const static vector<double> binedges_pt = {20,25,30,35,40,45,50,55,60};
        const static vector<double> binvals = {0.86, 0.9, 0.92, 0.93, 0.94, 0.95, 0.95, 0.96};

        const size_t bini = binIndex(j.pT(), binedges_pt);
        return binvals[bini];
      }

      static double JVT_eff(const Jet* j){
        return JVT_eff(*j);
      }

      static void apply_JVT(const vector<const Jet*> &jsIn, vector<const Jet*> &jsOut){
        for (const Jet* j : jsIn){
          if (random_bool(JVT_eff(j))){
            jsOut.push_back(j);
          }
        }
      }

      
      // Trim reclustered jets (and conveniently apply pt/eta cuts at the same time)
      static void trimJets(const vector<FJNS::PseudoJet> &pjs_in, vector<Jet> &js_out,
                           const double frac = 0.1, const double minPt = 0., 
                           const double maxEta = 6., const double minPt_twosubJets = 0.){
        js_out.clear();
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
          js_out.emplace_back(running_total);
        }
      }

      void normalise_nn_kinematics(vector<float> & nn_inputs) const{
        for (size_t i = 0; i < 84; ++i){
          nn_inputs[i] = ((nn_inputs[i] - _normalisation_means[i])/_normalisation_devs[i]);
        }
      }

      void normalise_nn_parameters(vector<float> & nn_inputs) const{
        for (size_t i = 84; i < 87; ++i){
          nn_inputs[i] = ((nn_inputs[i] - _normalisation_means[i])/_normalisation_devs[i]);
        }
      }


      Analysis_ATLAS_SUSY_2018_30() {
        set_analysis_name("ATLAS_SUSY_2018_30");
        set_luminosity(139.);

        // Load the NN
        //TODO: We really want to be as sure as possible this is called the minimal number of times.
        _nn = std::make_unique<onnx_rt_wrapper>(GAMBIT_DIR"/ColliderBit/data/analyses_ML/Analysis_ATLAS_SUSY_2018_30.onnx");

        #ifdef CHECK_CUTFLOWS
        // C&C regions
        _cutflows.addCutflow("SR_Gtt_0l_B", {"Nsiglep=0","dPhi4jmin>0.4","NJet>=5","ETMiss>=600","Meff>=2900","mbjets_Tmin>120","TotJetMass>=300"}); //TODO: bjets????
        _cutflows.addCutflow("SR_Gtt_0l_M1", {"Nsiglep=0","dPhi4jmin>0.4","NJet>=9&&Nbs>=3","ETMiss>=600","Meff>=1700","mbjets_Tmin>120","TotJetMass>=300"});
        _cutflows.addCutflow("SR_Gtt_0l_M2", {"Nsiglep=0","dPhi4jmin>0.4","NJet>=10&&Nbs>=3","ETMiss>=500","Meff>=1100","mbjets_Tmin>120","TotJetMass>=200"}); 
        _cutflows.addCutflow("SR_Gtt_0l_C", {"Nsiglep=0","dPhi4jmin>0.4","NJets>=10","NBjets>=4","ETMiss>=400","Meff>=800","mbjets_Tmin>180","TotJetMass>=100"});

         //TODO: where does the bjet presel cut come in?
        _cutflows.addCutflow("SR_Gbb_B", {"Nsiglep=0","dPhi4jmin>0.4","mbjets_Tmin>=130","ETMiss>=550","pTjet>=65","Meff>=2600"});
        _cutflows.addCutflow("SR_Gbb_M", {"Nsiglep=0","dPhi4jmin>0.4","mbjets_Tmin>=130","ETMiss>=550","Meff>=2000"});
        // n.b. I'm 99% sure Aux Table 4 gets meff and the met cut the wrong way round for Gbb_C, should be consistent with Gbb_B, Gbb_M
        _cutflows.addCutflow("SR_Gbb_C", {"Nsiglep=0","dPhi4jmin>0.4","mbjets_Tmin>=130","ETMiss>=550","Meff>=1600"}); 

        _cutflows.addCutflow("SR_Gtb_B", {"ETmissTrigger", "Nsiglep=0", "dPhi4jmin>0.4", "mbjets_Tmin>=130", "Meff>=2500", "ETMiss>=550", "totJetMass>=200"});
        _cutflows.addCutflow("SR_Gtb_M", {"ETmissTrigger", "Nsiglep=0", "dPhi4jmin>0.4", "mbjets_Tmin>=130", "nJets>=6", "nbs>=4", "Meff>=2000", "ETMiss>=550","totJetMass>=200"});
        _cutflows.addCutflow("SR_Gtb_C", {"ETmissTrigger", "Nsiglep=0", "dPhi4jmin>0.4", "mbjets_Tmin>=130", "nJets>=7", "nbs>=4", "Meff>=1300", "ETMiss>=500","totJetMass>=50"}); 

        //TODO: the ordering of the bjet cut confuses me (again).
        _cutflows.addCutflow("SR_Gtt_1l_B", {"Nsiglep=1","NJet>=4 && nbs >= 3","ETMiss>=600","Meff>=2300","m_trans>=150","mbjets_Tmin>120","TotJetMass>=200"});
        _cutflows.addCutflow("SR_Gtt_1l_M1", {"Nsiglep=1","NJet>=5 && nbs >= 3","ETMiss>=600","Meff>=2000","m_trans>=200","mbjets_Tmin>120","TotJetMass>=200"});
        _cutflows.addCutflow("SR_Gtt_1l_M2", {"Nsiglep=1","NJet>=8 && nbs >= 3","ETMiss>=500","Meff>=1100","m_trans>=200","mbjets_Tmin>120","TotJetMass>=100"}); 
        _cutflows.addCutflow("SR_Gtt_1l_C", {"Nsiglep=1","NJet>=9 && nbs >= 3","ETMiss>=300","Meff>=800","m_trans>=150","mbjets_Tmin>120"});

        // NN regions
        const vector<string> NN_Gbb_cuts{"NBaseLep=0", "dPhi4jmin", "P(Gbb)"};
        const vector<string> NN_Gtt_cuts{"Common", "P(Gtt)"};
        _cutflows.addCutflow("SR_Gtt_2100_1",NN_Gtt_cuts);
        _cutflows.addCutflow("SR_Gtt_1800_1",NN_Gtt_cuts);
        _cutflows.addCutflow("SR_Gtt_2300_1200",NN_Gtt_cuts);
        _cutflows.addCutflow("SR_Gtt_1900_1400",NN_Gtt_cuts);
        _cutflows.addCutflow("SR_Gbb_2800_1400",NN_Gbb_cuts);
        _cutflows.addCutflow("SR_Gbb_2300_1000",NN_Gbb_cuts);
        _cutflows.addCutflow("SR_Gbb_2100_1600",NN_Gbb_cuts);
        _cutflows.addCutflow("SR_Gbb_2000_1800",NN_Gbb_cuts);

        #endif //CHECK_CUTFLOWS

      }

      // Calculate transverse mass
      inline static double transverse_mass(HEPUtils::P4 pmiss, HEPUtils::P4 p4) {
        return sqrt(2*p4.pT()*pmiss.pT()*(1-cos(p4.deltaPhi(pmiss))));
      }

      void run(const HEPUtils::Event* event) {
        
        // Get the missing energy in the event
        double met = event->met();
        HEPUtils::P4 metVec = event->missingmom();

        // Electrons
        vector<const HEPUtils::Particle*> electrons;
        for (const HEPUtils::Particle* electron : event->electrons()) {
          if (electron->pT() > 20.
              && electron->eta() < 2.47
                && !(electron->abseta() > 1.37 && electron->abseta() < 1.52))
            electrons.push_back(electron);
        }

        // Muons
        vector<const HEPUtils::Particle*> muons;
        for (const HEPUtils::Particle* muon : event->muons()) {
          if (muon->pT() > 20.
              && muon->abseta() < 2.5)
            muons.push_back(muon);
        }

        // Get base and signal leptons CONSISTENTLY (i.e. all tight electrons are loose 
        //    electrons, never more signal than base etc.)
        vector<const HEPUtils::Particle*> sigElectrons, baseElectrons;
        vector<const HEPUtils::Particle*> sigMuons, baseMuons;
        for (const HEPUtils::Particle* el : electrons){
          const thread_local static auto loose_func = ATLAS::eff1DEl.at("EGAM_2018_01_ID_Loose");
          const thread_local static auto tight_func = ATLAS::eff1DEl.at("EGAM_2018_01_ID_Tight");
          const double eff_loose = loose_func.get_at(el->pT());
          const double eff_tight = tight_func.get_at(el->pT());
          const double rnd = Random::draw();

          if (rnd < eff_tight){
            sigElectrons.push_back(el);
            baseElectrons.push_back(el);
          }
          else if (rnd < eff_loose){
            baseElectrons.push_back(el);
          }
        }
        for (const HEPUtils::Particle* mu : muons){
          const thread_local static auto tight_func = ATLAS::eff1DMu.at("MUON_2018_03_ID_Tight");
          const thread_local static auto loose_func = ATLAS::eff1DMu.at("MUON_2018_03_ID_Tight");
          const double eff_tight = tight_func.get_at(mu->pT());
          const double eff_loose = loose_func.get_at(mu->pT());
          const double rnd = Random::draw();

          if (rnd < eff_tight){
            sigMuons.push_back(mu);
            baseMuons.push_back(mu);
          }
          else if (rnd < eff_loose){
            baseMuons.push_back(mu);
          }
        }

        // Tracks => Charged final state particles? (TODO: I think we make this approx in rivet, how valid is it)
        // const vector<const HEPUtils::Particle*> cfs1 = event->particles();
        vector<HEPUtils::P4> tracks;
        for (const Particle* p: event->particles() ){
          if (p->abseta() < 2.5 && p->pT() > 0.5)
            tracks.push_back(p->mom());
        }
        // Signal electrons: Fix(loose) - from 1902.04655 table 4.
        // n.b. only pT (not Et) part of the criteria implemented - How to define the Et calorimeter cone in gambit I have no idea
        ifilter_reject(sigElectrons, [&tracks](const HEPUtils::Particle* el){
          const double elRadius = min(0.2, (10*GeV)/el->pT());
          return (1.15*el->pT() < std::accumulate(tracks.begin(), tracks.end(), 0.0, 
          [el, &elRadius](const double tot, const P4& track){
            return (el->mom().deltaR_eta(track) < elRadius && 
              (el->mom().deltaPhi(track) > 0.1 &&
                el->mom().deltaEta(track) > 0.05)) ? tot+track.pT() : tot ;
          }));
        }, false);
        //Signal Muons: FixedCutTightTrackOnly - definition inferred from arXiv:1603.05598 table 2
        ifilter_reject(sigMuons, [&tracks](const Particle& mu){
          const double muRadius = min(0.3, (10*GeV)/mu.pT());
          const double conePt = std::accumulate(tracks.begin(), tracks.end(), 0.0, 
            [muRadius, &mu](const double tot, const P4& track){
              return mu.mom().deltaR_eta(track) < muRadius ? tot+track.pT() : tot ;
          });
          return (1.06*mu.pT() < conePt);
        }, false);
      
        vector<const HEPUtils::Jet*> preJVTJets;
        vector<const HEPUtils::Jet*> candJets;
        vector<const HEPUtils::Jet*>  bJets;
        vector<const HEPUtils::Jet*>  nonbJets;
        for (const HEPUtils::Jet* jet : event->jets("antikt_R04")) {
          if (jet->pT() > 30. && fabs(jet->eta()) < 2.8)
            preJVTJets.push_back(jet);
        }
        apply_JVT(preJVTJets, candJets);
        // Find b-jets
        const double cmisstag = 1/6.; const double misstag = 1./134.;
        // pt-dependent b-tagging -> turns out to be kind of important due to
        // large number of high-pt jets.
        const static vector<double>binedges_pt = {0.00, 30.0, 40.00, 50.00, 60.0, 75.00, 90.0, 105., 150., 200., 500 };
        const static vector<double> eff_pt =     {0.63, 0.705, 0.74, 0.76, 0.775, 0.785, 0.795, 0.80, 0.79, 0.75, 0.675};
        // N.b!!! The overflow value is extrapolated (from ATL-PHYS-PUB-2016-012)
        // You could quite reasonably pick a very wide range of values, and the
        // difference on the final result is order 5-10%.
        for (const HEPUtils::Jet* jet : candJets) {
          if (jet->abseta() >= 2.5) continue;
          // Tag
          if( jet->btag() && random_bool(eff_pt[binIndex(jet->pT(), binedges_pt, true)]) ) bJets.push_back(jet);
          // Misstag c-jet
          else if( jet->ctag() && random_bool(cmisstag) ) bJets.push_back(jet);
          // Misstag light jet
          else if( random_bool(misstag) ) bJets.push_back(jet);
          // Non b-jet
          else nonbJets.push_back(jet);
        }
        // Overlap removal
        // TODO: Just left in for now.
        removeOverlap(nonbJets, baseElectrons, 0.2);
        removeOverlap(nonbJets, sigElectrons, 0.2);
        
        removeOverlap(baseElectrons,nonbJets, 0.4);
        removeOverlap(baseElectrons,bJets, 0.4);
        removeOverlap(sigElectrons,nonbJets, 0.4);
        removeOverlap(sigElectrons,bJets, 0.4);

        // Jet-Muon probably not doable, skip for now (need number of jet constituents)
        // Should be relatively negligible, only applies to jets <= 2 tracks.
        auto mudRmax = [](const double mupt){return std::min(0.4, 0.04 + 10./mupt);};
        removeOverlap(baseMuons, nonbJets, mudRmax);
        removeOverlap(baseMuons,bJets, mudRmax);
        removeOverlap(sigMuons,nonbJets, mudRmax);
        removeOverlap(sigMuons,bJets, mudRmax);
        
        // Number of objects
        size_t nbJets = bJets.size();
        size_t nnonbJets = nonbJets.size();
        size_t nJets = nbJets + nnonbJets;
        size_t nBaseLeptons = baseElectrons.size() + baseMuons.size();
        size_t nSigMuons=sigMuons.size();
        size_t nSigElectrons=sigElectrons.size();
        size_t nSigLeptons = nSigElectrons+nSigMuons;

        //Combine objects together:
        //TODO: there has to be a better way of doing this... please...
        vector<const HEPUtils::Particle *> sigLeptons {};
        sigLeptons.insert(sigLeptons.end(), sigElectrons.begin(), sigElectrons.end());
        sigLeptons.insert(sigLeptons.end(), sigMuons.begin(), sigMuons.end());
        sortByPt(sigLeptons);
        vector<HEPUtils::Jet> smallJets;
        for (const Jet * j : bJets){
          smallJets.emplace_back(j->mom(), true);
        }
        for (const Jet * j : nonbJets){
          smallJets.emplace_back(j->mom(), false);
        }
        std::sort(smallJets.begin(), smallJets.end(), [](const Jet &j1, const Jet &j2){return j1.pT() > j2.pT();});


        // Preselection cut: 4 jets, 3 bjets, and 200GeV of MET
        if (nJets < 4 || nbJets < 3 || met < 200) return;

        // Make large r jets
        vector<Jet> largeJets;
        {
          vector<FJNS::PseudoJet> inJets;
          for (const Jet &j: smallJets){
            inJets.emplace_back(j.mom().px(), j.mom().py(), j.mom().pz(), j.E());
          }
          FJNS::JetDefinition jdef(FJNS::antikt_algorithm, 0.8);
          FJNS::ClusterSequence cseq(inJets, jdef);
          vector<FJNS::PseudoJet> largeRPseudoJets = cseq.inclusive_jets();
          trimJets(largeRPseudoJets, largeJets, 0.1, 100, 2.0);
        }
        const size_t nLargeJets = largeJets.size();
        std::sort(largeJets.begin(), largeJets.end(), [](const Jet &j1, const Jet &j2){return j1.pT() > j2.pT();});


        // Important variables
        const double dPhi4jmin =  min({smallJets[0].mom().deltaPhi(metVec),
               smallJets[1].mom().deltaPhi(metVec),
               smallJets[2].mom().deltaPhi(metVec),
               smallJets[3].mom().deltaPhi(metVec)});
        const double totJetMass = accumulate(largeJets.begin(), largeJets.end(), 0.0,
                                                  [](double tot, const Jet &j){return tot+j.mass();});                                       
        const double meff = met + accumulate(smallJets.begin(), smallJets.end(), 0.0, 
                                              [](double tot, const Jet & j){return tot+j.pT();})
                                + accumulate(sigElectrons.begin(), sigElectrons.end(), 0.0, 
                                              [](double tot, const Particle* el){return tot+el->pT();})
                                + accumulate(sigMuons.begin(), sigMuons.end(), 0.0, 
                                              [](double tot, const Particle* mu){return tot+mu->pT();});
        const double m_transverse_B_min = min({transverse_mass(metVec, bJets[0]->mom()),
                                               transverse_mass(metVec, bJets[1]->mom()),
                                               transverse_mass(metVec, bJets[2]->mom())});
        
        ///////////////////////////////////////////////////////////////////////
        // NN analysis
        // n.b. cast to float is an onnx necessity
        std::vector<float> nn_inputs = {
          // Small jet variables
          // TODO: double check heputils  phi convention - we want (-pi, pi], NOT [0, 2pi).
          (float)smallJets[0].pT(), (float)smallJets[0].eta(), (float)smallJets[0].phi(), (float)smallJets[0].mass(),  (float)smallJets[0].btag(),
          (float)smallJets[1].pT(), (float)smallJets[1].eta(), (float)smallJets[1].phi(), (float)smallJets[1].mass(),  (float)smallJets[1].btag(),
          (float)smallJets[2].pT(), (float)smallJets[2].eta(), (float)smallJets[2].phi(), (float)smallJets[2].mass(),  (float)smallJets[2].btag(),
          (float)smallJets[3].pT(), (float)smallJets[3].eta(), (float)smallJets[3].phi(), (float)smallJets[3].mass(),  (float)smallJets[3].btag(),
          (nJets > 4 ? (float)smallJets[4].pT() : 0.0f), nJets > 4 ? (float)smallJets[4].eta() : 0.f, nJets > 4 ? (float)smallJets[4].phi() : 0.f, nJets > 4 ? (float)smallJets[4].mass() : 0.f,  nJets > 4 ? (float)smallJets[4].btag() : 0.f,
          (nJets > 5 ? (float)smallJets[5].pT() : 0.0f), nJets > 5 ? (float)smallJets[5].eta() : 0.f, nJets > 5 ? (float)smallJets[5].phi() : 0.f, nJets > 5 ? (float)smallJets[5].mass() : 0.f,  nJets > 5 ? (float)smallJets[5].btag() : 0.f,
          (nJets > 6 ? (float)smallJets[6].pT() : 0.0f), nJets > 6 ? (float)smallJets[6].eta() : 0.f, nJets > 6 ? (float)smallJets[6].phi() : 0.f, nJets > 6 ? (float)smallJets[6].mass() : 0.f,  nJets > 6 ? (float)smallJets[6].btag() : 0.f,
          (nJets > 7 ? (float)smallJets[7].pT() : 0.0f), nJets > 7 ? (float)smallJets[7].eta() : 0.f, nJets > 7 ? (float)smallJets[7].phi() : 0.f, nJets > 7 ? (float)smallJets[7].mass() : 0.f,  nJets > 7 ? (float)smallJets[7].btag() : 0.f,
          (nJets > 8 ? (float)smallJets[8].pT() : 0.0f), nJets > 8 ? (float)smallJets[8].eta() : 0.f, nJets > 8 ? (float)smallJets[8].phi() : 0.f, nJets > 8 ? (float)smallJets[8].mass() : 0.f,  nJets > 8 ? (float)smallJets[8].btag() : 0.f,
          (nJets > 9 ? (float)smallJets[9].pT() : 0.0f), nJets > 9 ? (float)smallJets[9].eta() : 0.f, nJets > 9 ? (float)smallJets[9].phi() : 0.f, nJets > 9 ? (float)smallJets[9].mass() : 0.f,  nJets > 9 ? (float)smallJets[9].btag() : 0.f,

          // large Jet variables
          (nLargeJets > 0 ) ? (float)largeJets[0].pT() : 0.f, (nLargeJets > 0 ) ? (float)largeJets[0].eta() : 0.f, (nLargeJets > 0 ) ? (float)largeJets[0].phi() : 0.f, (nLargeJets > 0 ) ? (float)largeJets[0].mass() : 0.f, 
          (nLargeJets > 1 ) ? (float)largeJets[1].pT() : 0.f, (nLargeJets > 1 ) ? (float)largeJets[1].eta() : 0.f, (nLargeJets > 1 ) ? (float)largeJets[1].phi() : 0.f, (nLargeJets > 1 ) ? (float)largeJets[1].mass() : 0.f, 
          (nLargeJets > 2 ) ? (float)largeJets[2].pT() : 0.f, (nLargeJets > 2 ) ? (float)largeJets[2].eta() : 0.f, (nLargeJets > 2 ) ? (float)largeJets[2].phi() : 0.f, (nLargeJets > 2 ) ? (float)largeJets[2].mass() : 0.f, 
          (nLargeJets > 3 ) ? (float)largeJets[3].pT() : 0.f, (nLargeJets > 3 ) ? (float)largeJets[3].eta() : 0.f, (nLargeJets > 3 ) ? (float)largeJets[3].phi() : 0.f, (nLargeJets > 3 ) ? (float)largeJets[3].mass() : 0.f, 

          // lepton variables - pt, eta, phi, mass for four-leading leptons.
          (nSigLeptons > 0 ) ? (float)sigLeptons[0]->pT() : 0.f, (nSigLeptons > 0 ) ? (float)sigLeptons[0]->eta() : 0.f, (nSigLeptons > 0 ) ? (float)sigLeptons[0]->phi() : 0.f, (nSigLeptons > 0 ) ? (float)sigLeptons[0]->mass() : 0.f, 
          (nSigLeptons > 1 ) ? (float)sigLeptons[1]->pT() : 0.f, (nSigLeptons > 1 ) ? (float)sigLeptons[1]->eta() : 0.f, (nSigLeptons > 1 ) ? (float)sigLeptons[1]->phi() : 0.f, (nSigLeptons > 1 ) ? (float)sigLeptons[1]->mass() : 0.f, 
          (nSigLeptons > 2 ) ? (float)sigLeptons[2]->pT() : 0.f, (nSigLeptons > 2 ) ? (float)sigLeptons[2]->eta() : 0.f, (nSigLeptons > 2 ) ? (float)sigLeptons[2]->phi() : 0.f, (nSigLeptons > 2 ) ? (float)sigLeptons[2]->mass() : 0.f, 
          (nSigLeptons > 3 ) ? (float)sigLeptons[3]->pT() : 0.f, (nSigLeptons > 3 ) ? (float)sigLeptons[3]->eta() : 0.f, (nSigLeptons > 3 ) ? (float)sigLeptons[3]->phi() : 0.f, (nSigLeptons > 3 ) ? (float)sigLeptons[3]->mass() : 0.f, 

          // Met variables
          (float)met, (float)metVec.phi(),

          // Parameter variables (to be filled in later)
          0.f, 0.f, 0.f,

        };
        
        normalise_nn_kinematics(nn_inputs);
        map<string, vector<float>> nn_outputs;

        // Run network for Gtt param points
        if ((nBaseLeptons == 0 && dPhi4jmin >= 0.4) || sigLeptons.size() >= 1 ){
          for (const pair<size_t, size_t> &param_point : _gtt_param_points){
            nn_inputs[84]=1.0; nn_inputs[85] = param_point.first; nn_inputs[86] = param_point.second;
            const string param_string = to_string(param_point.first)+"_"+to_string(param_point.second);
            normalise_nn_parameters(nn_inputs);
            _nn->compute(nn_inputs, nn_outputs["Gtt_"+param_string]);
          }
          if (nn_outputs["Gtt_2100_1"][0] > 0.9997){
            _counters["SR_Gtt_2100_1"].add_event(event);
          }
          if (nn_outputs["Gtt_1800_1"][0] > 0.9997){
            _counters["SR_Gtt_1800_1"].add_event(event);
          }
          if (nn_outputs["Gtt_2300_1200"][0] > 0.9993){
            _counters["SR_Gtt_2300_1200"].add_event(event);
          }
          if (nn_outputs["Gtt_1900_1400"][0] > 0.9987){
            _counters["SR_Gtt_1900_1400"].add_event(event);
          }
        }
        // Run network for Gbb param points
        if (nBaseLeptons == 0 && dPhi4jmin > 0.4 ){
          for (const pair<size_t, size_t> &param_point : _gbb_param_points){
            nn_inputs[84]=0.0; nn_inputs[85] = param_point.first; nn_inputs[86] = param_point.second;
            normalise_nn_parameters(nn_inputs);
            _nn->compute(nn_inputs, nn_outputs["Gbb_"+to_string(param_point.first)+"_"+to_string(param_point.second)]);
          }
          if (dPhi4jmin >= 0.6 && nn_outputs["Gbb_2800_1400"][1] > 0.999){
            _counters["SR_Gbb_2800_1400"].add_event(event);
          }
          if (dPhi4jmin >= 0.6 && nn_outputs["Gbb_2300_1000"][1] > 0.9994){
            _counters["SR_Gbb_2300_1000"].add_event(event);
          }
          if (nn_outputs["Gbb_2100_1600"][1] > 0.9993){
            _counters["SR_Gbb_2100_1600"].add_event(event);
          }
          if (nn_outputs["Gbb_2000_1800"][1] > 0.997){
            _counters["SR_Gbb_2000_1800"].add_event(event);
          }
        }

        // NN region cutflows
        #ifdef CHECK_CUTFLOWS
        if ((nBaseLeptons == 0 && dPhi4jmin >= 0.4) || nSigLeptons >= 1){
          _cutflows["SR_Gtt_2100_1"].fill(1, {(nBaseLeptons == 0 && dPhi4jmin >= 0.4) || nSigLeptons == 1, nn_outputs["Gtt_2100_1"][0] > 0.9997}, event->weight());
          _cutflows["SR_Gtt_1800_1"].fill(1, {(nBaseLeptons == 0 && dPhi4jmin >= 0.4) || nSigLeptons == 1, nn_outputs["Gtt_1800_1"][0] > 0.9997}, event->weight());
          _cutflows["SR_Gtt_2300_1200"].fill(1, {(nBaseLeptons == 0 && dPhi4jmin >= 0.4) || nSigLeptons == 1, nn_outputs["Gtt_2300_1200"][0] > 0.9993}, event->weight());
          _cutflows["SR_Gtt_1900_1400"].fill(1, {(nBaseLeptons == 0 && dPhi4jmin >= 0.4) || nSigLeptons == 1, nn_outputs["Gtt_1900_1400"][0] > 0.9987}, event->weight());
        }
        if (nBaseLeptons == 0){
          _cutflows["SR_Gbb_2100_1600"].fill(1, event->weight());
          _cutflows["SR_Gbb_2000_1800"].fill(1, event->weight());
          _cutflows["SR_Gbb_2800_1400"].fill(1, event->weight());
          _cutflows["SR_Gbb_2300_1000"].fill(1, event->weight());
          if (dPhi4jmin >= 0.4){
            _cutflows["SR_Gbb_2100_1600"].fill(2, {dPhi4jmin >= 0.4, nn_outputs["Gbb_2100_1600"][1] > 0.9993}, event->weight());
            _cutflows["SR_Gbb_2000_1800"].fill(2, {dPhi4jmin >= 0.4, nn_outputs["Gbb_2000_1800"][1] > 0.997}, event->weight());
          }
          if (dPhi4jmin >= 0.6){
            _cutflows["SR_Gbb_2800_1400"].fill(2, {dPhi4jmin >= 0.6, nn_outputs["Gbb_2800_1400"][1] > 0.999}, event->weight());
            _cutflows["SR_Gbb_2300_1000"].fill(2, {dPhi4jmin >= 0.6, nn_outputs["Gbb_2300_1000"][1] > 0.9994}, event->weight());
          }
        }
        #endif //CHECK_CUTFLOWS
        ///////////////////////////////////////////////////////////////////////
        // Cut 'n' Count analysis

        // O lepton channel
        if (nBaseLeptons == 0){
          if (dPhi4jmin >= 0.4 && m_transverse_B_min >= 130){
            // Gbb regions
            if (met >= 550 && smallJets[0].pT() >= 65 && meff >= 2600){
              _counters["SR_Gbb_B"].add_event(event);
            }
            if (met >= 550 && meff >= 2000){
              _counters["SR_Gbb_M"].add_event(event);
            }
            if (met >= 550 && meff >= 1600){
              _counters["SR_Gbb_C"].add_event(event);
            }
            //Gtb regions
            if (meff >= 2500 && met >= 550 && totJetMass >= 200){
              _counters["SR_Gtb_B"].add_event(event);
            }
            if (nJets >= 6 && nbJets>= 4 && meff >= 2000 && met >= 550 && totJetMass >= 200){
              _counters["SR_Gtb_M"].add_event(event);
            }
            if (nJets >= 7 && nbJets>= 4 && meff >= 1300 && met >= 500 && totJetMass >= 50){
              _counters["SR_Gtb_C"].add_event(event);
            }
          }
          if (dPhi4jmin >= 0.4){
            // Gtb regions
            if (nJets >= 5 && met >= 600 && meff >= 2900 && m_transverse_B_min >= 120 && totJetMass >= 300){
              _counters["SR_Gtt_0l_B"].add_event(event);
            }
            if (nJets >= 9 && met >= 600 && meff >= 1700 && m_transverse_B_min >= 120 && totJetMass >= 300){
              _counters["SR_Gtt_0l_M1"].add_event(event);
            }
            if (nJets >= 10 && met >= 500 && meff >= 1100 && m_transverse_B_min >= 120 && totJetMass >= 200){
              _counters["SR_Gtt_0l_M2"].add_event(event);
            }
            if (nJets >= 10 && nbJets >=4 && met >= 400 && meff >= 800 && m_transverse_B_min >= 180 && totJetMass >= 100){
              _counters["SR_Gtt_0l_C"].add_event(event);
            }
          }
          #ifdef CHECK_CUTFLOWS
          _cutflows["SR_Gbb_B"].fill(1, {true, dPhi4jmin>=0.4, m_transverse_B_min>=130, met>=550, smallJets[0].pT() >= 65, meff >= 2600}, event->weight());
          _cutflows["SR_Gbb_M"].fill(1, {true, dPhi4jmin>=0.4, m_transverse_B_min>=130, met>=550, meff >= 2000}, event->weight());
          _cutflows["SR_Gbb_C"].fill(1, {true, dPhi4jmin>=0.4, m_transverse_B_min>=130, met>=550, meff >= 1600}, event->weight());

          _cutflows["SR_Gtb_B"].fill(2, {true, dPhi4jmin>=0.4, m_transverse_B_min>=130, meff>=2500, met >=550, totJetMass >= 200}, event->weight());
          _cutflows["SR_Gtb_M"].fill(2, {true, dPhi4jmin>=0.4, m_transverse_B_min>=130, nJets>=6, nbJets>=4, meff>=2000, met >=550, totJetMass >= 200}, event->weight());
          _cutflows["SR_Gtb_C"].fill(2, {true, dPhi4jmin>=0.4, m_transverse_B_min>=130, nJets>=7, nbJets>=4, meff>=1300, met >=500, totJetMass >= 50}, event->weight());

          _cutflows["SR_Gtt_0l_B"].fill(1, {true, dPhi4jmin>=0.4, nJets>=5, met>=600, meff>=2900, m_transverse_B_min>=120, totJetMass >= 300}, event->weight());
          _cutflows["SR_Gtt_0l_M1"].fill(1, {true, dPhi4jmin>=0.4, nJets>=9, met>=600, meff>=1700, m_transverse_B_min>=120, totJetMass >= 300}, event->weight());
          _cutflows["SR_Gtt_0l_M2"].fill(1, {true, dPhi4jmin>=0.4, nJets>=10, met>=600, meff>=1100, m_transverse_B_min>=120, totJetMass >= 200}, event->weight());
          _cutflows["SR_Gtt_0l_C"].fill(1, {true, dPhi4jmin>=0.4, nJets>=10, nbJets>=4, met>=400, meff>=800, m_transverse_B_min>=180, totJetMass >= 100}, event->weight());
          #endif //CHECK_CUTFLOWS
        }
        // 1 lepton channel
        else if (nSigLeptons >= 1){
          const double m_transverse = transverse_mass(metVec, sigLeptons[0]->mom());

          if (met >= 600 && meff >= 2300 && m_transverse >= 150 && m_transverse_B_min >= 120 && totJetMass >= 200){
            _counters["SR_Gtt_1l_B"].add_event(event);
          }
          if (nJets >=5 && met >= 600 && meff >= 2000 && m_transverse >= 200 && m_transverse_B_min >= 120 && totJetMass >= 200){
            _counters["SR_Gtt_1l_M1"].add_event(event);
          }
          if (nJets >=8 && met >= 500 && meff >= 1100 && m_transverse >= 200 && m_transverse_B_min >= 120 && totJetMass >= 100){
            _counters["SR_Gtt_1l_M2"].add_event(event);
          }
          if (nJets >= 9 && met >= 300 && meff >= 800 && m_transverse >= 150 && m_transverse_B_min >= 120){
            _counters["SR_Gtt_1l_C"].add_event(event);
          }
          #ifdef CHECK_CUTFLOWS
            _cutflows["SR_Gtt_1l_B"].fill(1,{true, nJets >= 4 && nbJets>=3, met >= 600, meff >= 2300, m_transverse >= 150, m_transverse_B_min >= 120, totJetMass >= 200}, event->weight());
            _cutflows["SR_Gtt_1l_M1"].fill(1,{true, nJets >= 5 && nbJets>=3, met >= 600, meff >= 2000, m_transverse >= 200, m_transverse_B_min >= 120, totJetMass >= 200}, event->weight());
            _cutflows["SR_Gtt_1l_M2"].fill(1,{true, nJets >= 8 && nbJets>=3, met >= 500, meff >= 1100, m_transverse >= 200, m_transverse_B_min >= 120, totJetMass >= 200}, event->weight());
            _cutflows["SR_Gtt_1l_C"].fill(1,{true, nJets >= 9 && nbJets>=3, met >= 300, meff >= 800, m_transverse >= 150, m_transverse_B_min >= 120}, event->weight());
          #endif 
        }
        return;
      } // End of analyze

      /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
      void combine(const Analysis* other)
      {
        const Analysis_ATLAS_SUSY_2018_30* specificOther
          = dynamic_cast<const Analysis_ATLAS_SUSY_2018_30*>(other);
        for (auto& pair : _counters) { pair.second += specificOther->_counters.at(pair.first); }

        // TODO: Merge cutflows?
      }


      virtual void collect_results() {

        // Now fill a results object with the results for each SR
        // TODO: prefit errors not present in table - using postfit errors as 1st approx
        // NN SR's
        add_result(SignalRegionData(_counters.at("SR_Gtt_2100_1"), 0., {0.56, 0.4}));
        add_result(SignalRegionData(_counters.at("SR_Gtt_1800_1"), 0., {0.50, 0.27}));
        add_result(SignalRegionData(_counters.at("SR_Gtt_2300_1200"), 1., {0.7, 0.5}));
        add_result(SignalRegionData(_counters.at("SR_Gtt_1900_1400"), 1., {0.7, 1.0}));

        add_result(SignalRegionData(_counters.at("SR_Gbb_2800_1400"), 1., {1.3, 0.6}));
        add_result(SignalRegionData(_counters.at("SR_Gbb_2300_1000"), 1., {1.1, 0.6}));
        add_result(SignalRegionData(_counters.at("SR_Gbb_2100_1600"), 0., {1.3, 1.3}));
        add_result(SignalRegionData(_counters.at("SR_Gbb_2000_1800"), 1., {0.4, 0.5}));

        // C'n'C 0l 
        add_result(SignalRegionData(_counters.at("SR_Gbb_B"), 7., {3.5, 1.4}));
        add_result(SignalRegionData(_counters.at("SR_Gbb_M"), 18, {14, 4}));
        add_result(SignalRegionData(_counters.at("SR_Gbb_C"), 32, {33, 9}));

        // Cutflow repoduction here isn't great - don't trust Gtb
        // add_result(SignalRegionData(_counters.at("SR_Gtb_B"), 8., {3, 0.9}));
        // add_result(SignalRegionData(_counters.at("SR_Gtb_M"), 1, {1.3, 0.6}));
        // add_result(SignalRegionData(_counters.at("SR_Gtb_C"), 4, {5.8, 2.2}));

        add_result(SignalRegionData(_counters.at("SR_Gtt_0l_B"), 3., {0.87, 0.32}));
        add_result(SignalRegionData(_counters.at("SR_Gtt_0l_M1"), 1.3, {0.55, 0.6}));
        add_result(SignalRegionData(_counters.at("SR_Gtt_0l_M2"), 2.7, {1.0, 1.3}));
        add_result(SignalRegionData(_counters.at("SR_Gtt_0l_C"), 1.4, {3.7, 0.8}));

        // C'n'C 1l
        add_result(SignalRegionData(_counters.at("SR_Gtt_1l_B"), 1., {0.55, 0.4}));
        add_result(SignalRegionData(_counters.at("SR_Gtt_1l_M1"), 0., {0.55, 0.27}));
        add_result(SignalRegionData(_counters.at("SR_Gtt_1l_M2"), 0., {1.0, 0.4}));
        add_result(SignalRegionData(_counters.at("SR_Gtt_1l_C"), 2., {3.7, 2.0}));

        #ifdef CHECK_CUTFLOWS
          _cutflows.print(std::cout);
        #endif //CHECK_CUTFLOWS

        return;

      }

      void analysis_specific_reset() {
        // Clear signal regions
        for (auto& pair : _counters) { pair.second.reset(); }
        
        //TODO: Clear cutflows?
      }


      // normalisation vectors from simpleAnalysis
      const vector<float> _normalisation_means = {348.82672119140625, 0.001224843435920775, 0.011215382255613804, 35.01051712036133, 0.4123765528202057, 205.96482849121094, 0.000866758287884295, 0.0026113702915608883, 21.943532943725586, 0.5219350457191467, 131.5203399658203, 0.0014234248083084822, 0.0028221921529620886, 14.679434776306152, 0.4859117269515991, 89.95111083984375, 0.0024308657739311457, 0.003201194340363145, 10.921121597290039, 0.41861748695373535, 51.72813415527344, 0.002211648505181074, 0.001059219939634204, 6.8958611488342285, 0.2480594962835312, 29.507577896118164, 0.0014721028273925185, 0.0011491943150758743, 4.127583026885986, 0.1373944729566574, 16.116954803466797, 0.0008737104362808168, 0.0005380049697123468, 2.326930522918701, 0.07252819091081619, 8.416145324707031, 0.000563444453291595, 0.0004173719498794526, 1.2422566413879395, 0.036873701959848404, 4.170749664306641, 0.0005186111084185541, 0.0001961462403414771, 0.6271772384643555, 0.017829529941082, 1.9352974891662598, 2.8667405786109157e-05, 0.00025558529887348413, 0.2950354516506195, 0.008070512674748898, 388.2679443359375, 0.0005678863381035626, 0.010501296259462833, 75.08436584472656, 201.22515869140625, 0.0007426381343975663, -0.0012021028669551015, 37.745521545410156, 86.0351333618164, 0.0001722413144307211, 0.00024551310343667865, 14.23154354095459, 28.54050636291504, 7.828087836969644e-05, 0.0004572096804622561, 4.361158847808838, 52.769752502441406, 0.00055172317661345, -0.004927645903080702, 0.03030405007302761, 3.7328639030456543, 3.698996079037897e-05, 9.778635285329074e-05, 0.0030516863334923983, 0.23780983686447144, -1.23310519484221e-05, -5.973678707960062e-05, 0.0002457579248584807, 0.009709575213491917, -7.139377089515619e-07, 9.422020411875565e-06, 1.2358904314169195e-05, 272.284423828125, 3.157931327819824, 0.5684433579444885, 1924.33984375, 813.9981079101562};
      const vector<float> _normalisation_devs = {260.26678466796875, 1.043735384941101, 1.8061413764953613, 31.465930938720703, 0.48998895287513733, 158.85206604003906, 1.0634719133377075, 1.8049265146255493, 19.196178436279297, 0.49979639053344727, 95.81076049804688, 1.1140797138214111, 1.8063502311706543, 10.480488777160645, 0.499955415725708, 61.92335510253906, 1.1796157360076904, 1.806037187576294, 6.566783428192139, 0.48769065737724304, 46.49405288696289, 1.0528481006622314, 1.561020016670227, 5.663470268249512, 0.41597431898117065, 36.96717834472656, 0.8779095411300659, 1.279522180557251, 4.860283851623535, 0.33421754837036133, 28.791873931884766, 0.6928571462631226, 1.0022454261779785, 3.9111227989196777, 0.25323963165283203, 19.419239044189453, 0.5242016315460205, 0.7574199438095093, 2.817417860031128, 0.1853451132774353, 13.448785781860352, 0.3827989995479584, 0.5529165267944336, 2.029693365097046, 0.13118404150009155, 9.043235778808594, 0.26963910460472107, 0.3887377977371216, 1.4025100469589233, 0.08914224058389664, 286.4169921875, 0.8792079091072083, 1.7478116750717163, 76.41952514648438, 198.80892944335938, 0.7650731801986694, 1.5172309875488281, 50.877689361572266, 126.01263427734375, 0.6058558821678162, 1.156052827835083, 26.713064193725586, 68.72575378417969, 0.40241798758506775, 0.740081787109375, 13.1954927444458, 83.16204071044922, 0.7241584062576294, 1.3046456575393677, 0.05489525943994522, 19.12066078186035, 0.24320338666439056, 0.42904603481292725, 0.01846902072429657, 4.206113815307617, 0.07045941799879074, 0.12233318388462067, 0.005232449620962143, 0.7187768816947937, 0.016513027250766754, 0.027744540944695473, 0.001166886300779879, 239.20870971679688, 1.8090277910232544, 0.48885977268218994, 471.8238525390625, 555.2835693359375};

      // Parameter points tested by the network explicitly in form {mglu, mneutralino}.
      const vector<pair<size_t, size_t>> _gtt_param_points {{1900,1400}, {1800,1}, {2100,1}, {2300,1200}};
      const vector<pair<size_t, size_t>> _gbb_param_points {{2000,1800}, {2100,1600}, {2300,1000}, {2800,1400}};

    };

    DEFINE_ANALYSIS_FACTORY(ATLAS_SUSY_2018_30)

  }

}

//#undef CHECK_CUTFLOWS

#endif
