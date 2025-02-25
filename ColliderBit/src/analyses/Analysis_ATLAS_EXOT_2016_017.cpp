///
///  \author Pengxuan Zhu (zhupx99@icloud.com, pengxuan.zhu@adelaide.edu.au)
///  \date 2025 Feb
///
///  *********************************************

// Based on
//  - https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/PAPERS/EXOT-2016-17/
//  - https://cds.cern.ch/record/2652224
//  - https://arxiv.org/abs/1812.07343
// Search for the single production of heavy vector-like T and/or Y in pp collisions at s√= 13 TeV
//   primarily targeting the events of final a W boson + b-quark

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/analyses/AnalysisMacros.hpp"
#include "gambit/ColliderBit/Utils.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"
#include "HEPUtils/FastJet.h"
#include "HEPUtils/Event.h"
#include "HEPUtils/Jet.h"

using namespace std;

#define CHECK_CUTFLOW

namespace Gambit
{
    namespace ColliderBit
    {
        class Analysis_ATLAS_EXOT_2016_017 : public Analysis
        {
        private:
            /* data */
        public:
#ifdef CHECK_CUTFLOW
            Cutflows _cutflows;
#endif

            static constexpr const char *detector = "ATLAS";
            Analysis_ATLAS_EXOT_2016_017()
            {
                DEFINE_SIGNAL_REGION("SR");

                set_analysis_name("ATLAS_EXOT_2016_017");
                set_luminosity(36.1);
            }

            void run(const HEPUtils::Event *event)
            {
                double met = event->met();
                HEPUtils::P4 metVec = event->missingmom();

                BASELINE_PARTICLES(event->electrons(), baselineEl1, 25, 0, DBL_MAX, 1.37, ATLAS::eff1DEl.at("PERF_2017_01_ID_Tight"));
                BASELINE_PARTICLES(event->electrons(), baselineEl2, 25, 1.52, DBL_MAX, 2.47, ATLAS::eff1DEl.at("PERF_2017_01_ID_Tight"));
                BASELINE_PARTICLES(event->muons(), baselineMuons, 25, 0, DBL_MAX, 2.5, ATLAS::eff1DMu.at("MUON_2018_03_ID_Tight"));
                BASELINE_PARTICLE_COMBINATION(baselineElectrons, baselineEl1, baselineEl2)
                BASELINE_PARTICLE_COMBINATION(baselineLeptons, baselineElectrons, baselineMuons);

                BASELINE_JETS(event->jets("antikt_R04"), basectrJets, 25, 0, DBL_MAX, 2.5);
                BASELINE_JETS(event->jets("antikt_R04"), basefwdJets, 40., 2.5, DBL_MAX, 4.5);

                removeOverlap(basectrJets, baselineLeptons, 0.2);
                removeOverlap(baselineLeptons, basectrJets, 0.4);

                // define Signal Objects;
                vector<const HEPUtils::Jet *> signalctrJets;
                vector<const HEPUtils::Jet *> signalctrBJets;
                vector<const HEPUtils::Particle *> signalLeptons;
                vector<const HEPUtils::Jet *> signalfwdJets;

                for (const HEPUtils::Particle *lep : baselineLeptons)
                {
                    if (lep->pT() > 28.)
                    {
                        signalLeptons.push_back(lep);
                    }
                }
                // B-tag efficiency
                std::map<const Jet *, bool> analysisBtags = generateBTagsMap(basectrJets, 0.85, 0.334, 0.0294);
                for (const HEPUtils::Jet *jet : basectrJets)
                {
                    bool isbtag = analysisBtags.at(jet);
                    if (isbtag && jet->abseta() < 2.5 && jet->pT() > 25.)
                    {
                        signalctrBJets.push_back(jet);
                    }
                    else
                    {
                        signalctrJets.push_back(jet);
                    }
                }

                const int nctrBJet = signalctrBJets.size();
                const int nctrJet = signalctrJets.size();

                for (const HEPUtils::Jet *jet : basefwdJets)
                {
                    if (jet->pT() > 40.)
                        signalfwdJets.push_back(jet);
                }
                SIGNAL_JET_COMBINATION(signalJets, basectrJets, signalfwdJets);

                bool preselection = (signalLeptons.size() == 1) && (met > 120.) && (nctrBJet + nctrJet >= 1);
                if (preselection)
                {
                    bool leadbjet = nctrBJet > 0 ? signalctrBJets.at(0)->pT() >= 350. : false;
                    leadbjet = (nctrBJet > 0 && nctrJet > 0) ? signalctrBJets.at(0)->pT() > signalctrJets.at(0)->pT() : false;
                    int Jetincone = false;
                    if (leadbjet)
                    {
                        HEPUtils::P4 Bjet0mom = signalctrBJets.at(0)->mom(); 
                        for (unsigned int ii = 1; ii < signalJets.size(); ii++)
                        {
                            HEPUtils::P4 jetmom = signalJets.at(ii)->mom();
                            double jetpt = signalJets.at(ii)->pT();
                            double jeteta = signalJets.at(ii)->abseta();
                            if (jetpt > 75. && jeteta < 2.5) {
                                double dRjj = Bjet0mom.deltaR_eta(jetmom); 
                                if (dRjj < 1.2) || (dRjj > 2.7) Jetincone = true; 
                            }
                        }
                        double dPhiLepBjet0 = signalLeptons.at(0)->mom().deltaPhi(Bjet0mom); 
                        double dRLepj = 999.; 
                        for (unsigned int ii = 1; ii < signalctrBJets.size(); ii ++) {
                            double dRlj = std::min(dRLepj, signalLeptons.at(0)->mom().deltaR_eta(signalctrBJets.at(ii)->mom())); 
                        }
                        for (unsigned int ii = 1; ii < signalctrJets.size(); ii ++) {
                            double dRlj = std::min(dRLepj, signalLeptons.at(0)->mom().deltaR_eta(signalctrJets.at(ii)->mom())); 
                        }
                        int nfwdJet = signalfwdJets.size(); 
                        if (!Jetincone && dRLepj >= 2.0 && nfwdJet >= 1) {FILL_SIGNAL_REGION("SR"); }
                    }
                }
                return; 
            }

            virtual void
            collect_result()
            {
                add_result(SignalRegionData(_counters.at("SR"), 497, {500, 30}));

                COMMIT_CUTFLOWS;

                return;
            }

        protected:
            void analysis_specific_reset()
            {
                for (auto &pair : _counters)
                {
                    pair.second.reset();
                }
            }
        };

        // Factory fn 
        DEFINE_ANALYSIS_FACTORY(ATLAS_EXOT_2016_017)
    } // namespace ColliderBit
} // namespace Gambi
