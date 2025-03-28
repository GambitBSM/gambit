///
///  \author Pengxuan Zhu (zhupx99@icloud.com, pengxuan.zhu@adelaide.edu.au)
///  \date 2025 Feb
///
///  *********************************************

// Based on
//  - https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/PAPERS/EXOT-2021-35/
//  - https://inspirehep.net/literature/2791855
//  - https://arxiv.org/abs/2405.19862
// Search for the pair production of heavy vector-like Q (light-flavor) in pp collisions at s√= 13 TeV
//   primarily BR(Q->Wq) = 1
 
#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/analyses/AnalysisMacros.hpp"
#include "gambit/ColliderBit/Utils.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"
#include "HEPUtils/FastJet.h"
#include "HEPUtils/Event.h"
#include "HEPUtils/Jet.h"

using namespace std;


// #define CHECK_CUTFLOW

#ifdef CHECK_CUTFLOW
    #include "YODA/Histo1D.h"
    #include "YODA/WriterYODA.h"
#endif

namespace Gambit
{
    namespace ColliderBit
    {
        class Analysis_ATLAS_EXOT_2021_035 : public Analysis
        {
        private:
            /* data */
        public:
            #ifdef CHECK_CUTFLOW
                Cutflows _cutflows;
                YODA::Histo1D *_histo_mVLQ; 
                int Nevent = 0;
            #endif

            static constexpr const char *detector = "ATLAS";
            Analysis_ATLAS_EXOT_2021_035()
            {
                DEFINE_SIGNAL_REGION("SR1");
                DEFINE_SIGNAL_REGION("SR2");

                set_analysis_name("ATLAS_EXOT_2021_035");
                set_luminosity(140.0);

                #ifdef CHECK_CUTFLOW
                    _histo_mVLQ = new YODA::Histo1D(17, 0., 2550., "SR/mVLQ"); 
                    cout << "====== Cutflows ======" << endl; 
                    _cutflows.addCutflow("Signal Region", {
                        "No Cut", 
                        "Preselection",
                        "Leading Jet is b-tagged",
                        "Leading Jet pT > 350 GeV",
                        "Veto event with jet with dR(jet, b-tagged jet) < 1.2 or > 2.7",
                        "dPhi(l, b-tagged jet) > 2.5",
                        "Forward jets > 0",
                        "dR(l, jets) > 2.0"
                    });
                #endif
            }

            void run(const HEPUtils::Event *event)
            {
                #ifdef CHECK_CUTFLOW
                    _cutflows["Signal Region"].fillinit(event->weight());
                    _cutflows["Signal Region"].fill(1, true, event->weight()); 
                    if (Nevent % 200 == 0)
                    {
                        cout << "Complete " << Nevent << " Events" << endl;
                    }
                    Nevent += 1; 
                #endif

                double met = event->met();
                HEPUtils::P4 pmiss = event->missingmom();

                BASELINE_PARTICLES(event->electrons(), baselineEl1, 27., 0, DBL_MAX, 1.37);
                BASELINE_PARTICLES(event->electrons(), baselineEl2, 27., 1.52, DBL_MAX, 2.47);
                BASELINE_PARTICLES(event->muons(), baselineMuons, 27., 0, DBL_MAX, 2.5);
                
                BASELINE_PARTICLE_COMBINATION(baselineElectrons, baselineEl1, baselineEl2);
                applyEfficiency(baselineElectrons, ATLAS::eff1DEl.at("PERF_2017_01_ID_Tight")); 
                applyEfficiency(baselineMuons, ATLAS::eff1DMu.at("MUON_2018_03_ID_Tight")); 
                
                BASELINE_JETS(event->jets("antikt_R04"), baselineJets, 25., 0, DBL_MAX, 2.5);
                BASELINE_JETS(event->jets("antikt_R10"), baseLargeRJets, 200., 0, DBL_MAX, 2.0);

                removeOverlap(baselineJets, baselineElectrons, 0.2);
                removeOverlap(baselineJets, baselineElectrons, 0.2);
                
                removeOverlap(baselineElectrons, baselineJets, 0.4);

                vector<const HEPUtils::Particle *> sgmuons; 
                for (const HEPUtils::Particle *mu : baselineMuons) 
                {
                    double deltaR = min(0.4, 0.004 + 10./ mu->pT()); 
                    bool ovtag = true; 
                    for (const HEPUtils::Jet * jet : baselineJets)
                    {
                        double dR = jet->mom().deltaR_eta(mu->mom()); 
                        if (dR < deltaR) ovtag = false; 
                    }
                    if (ovtag) sgmuons.push_back(mu); 
                }
                removeOverlap(sgmuons, baselineJets, 0.4); 

                SIGNAL_PARTICLES(baselineElectrons, signalEl); 
                SIGNAL_PARTICLES(sgmuons, signalMu); 
                SIGNAL_PARTICLE_COMBINATION(signalLep, signalEl, signalMu); 

                bool base_pre = (signalLep.size() == 1) ? signalLep.at(0)->pT() > 60. : false;
                if (base_pre)
                {
                    double nv_px = pmiss.px();
                    double nv_py = pmiss.py();
                    std::vector<double> pz_nus = calculate_pvz(signalLep.at(0)->mom(), nv_px, nv_py);
                    double nv_pz = solute_pvZ(pz_nus);
                    double nv_E = std::sqrt(nv_px * nv_px + nv_py * nv_py + nv_pz * nv_pz);
                    HEPUtils::P4 vp4(nv_px, nv_py, nv_pz, nv_E);
                    HEPUtils::P4 WLepp4 = vp4 + signalLep.at(0)->mom();
                }
                return; 

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
                SIGNAL_JET_COMBINATION(ctrJets, signalctrBJets, signalctrJets); 

                bool preselection = (signalLeptons.size() == 1) && (met > 120.) && (nctrBJet + nctrJet >= 1);

                if (preselection)
                {

                    bool leadbjet01 = (nctrBJet > 0 && nctrJet == 0);
                    bool leadbjet02 = (nctrBJet > 0 && nctrJet > 0) ? (signalctrBJets.at(0)->pT() > signalctrJets.at(0)->pT()) : false;
                    bool leadbjet = leadbjet01 || leadbjet02; 

                    #ifdef CHECK_CUTFLOW
                        _cutflows["Signal Region"].fill(2, true, event->weight());
                    #endif
                    int Jetincone = false;
                    if (leadbjet)
                    {
                        HEPUtils::P4 Bjet0mom = signalctrBJets.at(0)->mom(); 
                        for (unsigned int ii = 1; ii < ctrJets.size(); ii++)
                        {
                            HEPUtils::P4 jetmom = ctrJets.at(ii)->mom();
                            double jetpt = ctrJets.at(ii)->pT();
                            double jeteta = ctrJets.at(ii)->abseta();
                            if (jetpt > 75. && jeteta < 2.5) {
                                double dRjj = Bjet0mom.deltaR_eta(jetmom); 
                                if ((dRjj < 1.2) || (dRjj > 2.7)) Jetincone = true; 
                            }
                        }

                        double dPhiLepBjet0 = signalLeptons.at(0)->mom().deltaPhi(Bjet0mom); 
                        double dRLepj = 999.; 
                        for (unsigned int ii = 1; ii < signalctrBJets.size(); ii ++) {
                            dRLepj = std::min(dRLepj, signalLeptons.at(0)->mom().deltaR_eta(signalctrBJets.at(ii)->mom())); 
                        }
                        for (unsigned int ii = 0; ii < signalctrJets.size(); ii ++) {
                            dRLepj = std::min(dRLepj, signalLeptons.at(0)->mom().deltaR_eta(signalctrJets.at(ii)->mom())); 
                        }
                        int nfwdJet = signalfwdJets.size(); 

                        #ifdef CHECK_CUTFLOW
                            _cutflows["Signal Region"].fillnext({
                                leadbjet,
                                signalctrBJets.at(0)->pT() > 350., 
                                !Jetincone, 
                                dPhiLepBjet0 > 2.5, 
                                nfwdJet >= 1, 
                                dRLepj > 2.0
                            }, event->weight());
                        #endif
                        if (signalctrBJets.at(0)->pT() > 350. && !Jetincone && dPhiLepBjet0 > 2.5  && dRLepj >= 2.0 && nfwdJet >= 1)                    
                        {
                            _counters.at("SR").add_event(event);
                        }


                        // Reconstructing mVLQ 
                        #ifdef CHECK_CUTFLOW
                            double nv_px = pmiss.px();
                            double nv_py = pmiss.py();
                            std::vector<double> pz_nus = calculate_pvz(signalLeptons.at(0)->mom(), nv_px, nv_py); 
                            double nv_pz = solute_pvZ(pz_nus); 
                            double nv_E  = std::sqrt(nv_px * nv_px + nv_py * nv_py + nv_pz * nv_pz ); 
                            HEPUtils::P4 pv4(nv_px, nv_py, nv_pz, nv_E);
                            HEPUtils::P4 pVLQ4 = pv4 + signalLeptons.at(0)->mom() + Bjet0mom; 
                            double mVLQ = pVLQ4.m(); 
                            if (!Jetincone && dPhiLepBjet0 > 2.5  && dRLepj >= 2.0 && nfwdJet >= 1)
                                _histo_mVLQ->fill(mVLQ, 1.); 
                        #endif
                    }
                }
                return; 
            }

            virtual void
            collect_results()
            {
                add_result(SignalRegionData(_counters.at("SR1"), 156, {150, 10}));
                add_result(SignalRegionData(_counters.at("SR2"), 186, {192, 12}));

                COMMIT_CUTFLOWS;
                #ifdef CHECK_CUTFLOW
                    std::vector<YODA::AnalysisObject *> histos; 
                    histos.push_back(_histo_mVLQ);
                    YODA::WriterYODA::write("ATLAS_EXOT_2021_035.yoda", histos.begin(), histos.end()); 
                    delete _histo_mVLQ; 
                #endif
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
        
        private: 
            const double mW = 80.4; 

            std::vector<double> calculate_pvz(const HEPUtils::P4 &lep, double met_px, double met_py)
            {
                double px_l = lep.px();
                double py_l = lep.py();
                double pz_l = lep.pz();
                double E_l = lep.E();
                double ETM2 = met_px * met_px + met_py * met_py; 

                double m_l = lep.m(); 

                double A = mW * mW - m_l * m_l + 2.0 * px_l * met_px + 2.0 * met_py * py_l; 
                double B = 2.0 * pz_l; 
                double C = -2.0 * E_l; 

                double discriminant = (A * A) * (C * C) + (B * B) * (C * C) * ETM2 - (C * C * C * C) * ETM2; 
                double denominator = (C * C) - (B * B); 

                std::vector<double> solutions;

                if (discriminant >= 0)
                {
                    double sqrt_discriminant = std::sqrt(discriminant);
                    solutions.push_back((A * B + sqrt_discriminant)/denominator);
                    solutions.push_back((A * B - sqrt_discriminant)/denominator);
                }

                return solutions;
            }

            double solute_pvZ(const std::vector<double> &solutions)
            {
                if (solutions.empty())
                    return 0.0;
                return (std::abs(solutions[0]) < std::abs(solutions[1])) ? solutions[0] : solutions[1];
            }

        };
        DEFINE_ANALYSIS_FACTORY(ATLAS_EXOT_2021_035)
    } // namespace ColliderBit
} // namespace Gambi
