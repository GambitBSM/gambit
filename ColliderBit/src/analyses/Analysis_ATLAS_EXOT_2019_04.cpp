///
///  \author Pengxuan Zhu (zhupx99@icloud.com, pengxuan.zhu@adelaide.edu.au)
///  \date 2025 Oct
///
///  *********************************************

// Based on
//  - https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/PAPERS/EXOT-2019-04/
//  - https://cds.cern.ch/record/2858670
//  - https://inspirehep.net/literature/2686498
//  - https://arxiv.org/abs/2308.02595

// Search for the single vector-like B (B -> b+H( -> bb)) in pp collisions at s√= 13 TeV

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/analyses/AnalysisMacros.hpp"
#include "gambit/ColliderBit/Utils.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"
#include "HEPUtils/FastJet.h"
#include "HEPUtils/Event.h"
#include "HEPUtils/Jet.h"

// Similar to ATLAS_13_TeV_3b_NN_139invfb (define structure copied from heputils/FastJet.h)
#ifndef FJCORE
#ifndef FJNS
#define FJNS fastjet
#endif
#include "fastjet/ClusterSequence.hh"
#include "fastjet/PseudoJet.hh"
#include "fastjet/tools/Filter.hh"
#include "fastjet/tools/Pruner.hh"
#include "fastjet/Selector.hh"
#include "fastjet/contrib/EnergyCorrelator.hh"
// #include "gambit/contrib/fjcontrib-1.045/EnergyCorrelator/EnergyCorrelator.hh"
#else
#include "fjcore.hh"
#ifndef FJNS
#define FJNS fjcore
#endif
#endif

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
        class Analysis_ATLAS_EXOT_2019_04 : public Analysis
        {
        private:
        /* data */
        public:

        #ifdef CHECK_CUTFLOW
            Cutflows _cutflows;
            YODA::Histo1D *_histo_mB;
            int Nevent = 0;
        #endif

        static constexpr const char *detector = "ATLAS";
        Analysis_ATLAS_EXOT_2019_04()
        {
            DEFINE_SIGNAL_REGION_NOCUTS("SR");

            set_analysis_name("ATLAS_EXOT_2019_04");
            set_luminosity(139.0);

            #ifdef CHECK_CUTFLOW
                    _histo_mB = new YODA::Histo1D(14, 900., 2300., "SR/mB");
            #endif
        }

        void run(const HEPUtils::Event *event)
        {
            #ifdef CHECK_CUTFLOW
                    // BEGIN_PRESELECTION
                    if (Nevent % 200 == 0) { cout << "Complete " << Nevent << " Events" << endl; }
                    Nevent += 1;
            #endif

            double met = event->met();
            HEPUtils::P4 pmiss = event->missingmom();

            BASELINE_PARTICLES(event->electrons(), baselineEl1, 25., 0, DBL_MAX, 1.37)
            BASELINE_PARTICLES(event->electrons(), baselineEl2, 25., 1.52, DBL_MAX, 2.47)
            BASELINE_PARTICLES(event->muons(), baselineMuons, 25., 0, DBL_MAX, 2.5)
            BASELINE_PARTICLES(event->photons(), baselinePh1, 10., 0, DBL_MAX, 1.37)
            BASELINE_PARTICLES(event->photons(), baselinePh2, 10., 1.52, DBL_MAX, 2.47)

            BASELINE_PARTICLE_COMBINATION(baselineElectrons, baselineEl1, baselineEl2)
            BASELINE_PARTICLE_COMBINATION(baselinePhotons, baselinePh1, baselinePh2)

            applyEfficiency(baselineElectrons, ATLAS::eff1DEl.at("EGAM_2018_01_ID_Loose"));
            applyEfficiency(baselineMuons, ATLAS::eff1DMu.at("MUON_2018_03_ID_Medium"));
            applyEfficiency(baselinePhotons, ATLAS::eff1DPhoton.at("GAM_2018_03_Iso_Tight"));

            BASELINE_JETS(event->jets("antikt_R04"), baselineCentralJets, 25., 0, DBL_MAX, 2.5)
            BASELINE_JETS(event->jets("antikt_R04"), baselineForwardJets, 40., 2.5, DBL_MAX, 4.5)
            BASELINE_JETS(event->jets("antikt_R10"), baseLargeRJets, 200., 0, DBL_MAX, 2.0)
            BASELINE_JET_COMBINATION(BaselineJets, baselineCentralJets, baselineForwardJets)

            SIGNAL_PARTICLES(baselineElectrons, signalEl)
            SIGNAL_PARTICLES(baselineMuons, signalMu)
            SIGNAL_PARTICLES(baselinePhotons, signalPh)
            SIGNAL_PARTICLE_COMBINATION(signalLep, signalEl, signalMu)
            
            std::vector<const HEPUtils::Jet*> VR_jets;
            for (const HEPUtils::Jet* j : event->vrjets("VRTrackJets")) {
                if (j->pT() > 10. && j->abseta() < 2.5) VR_jets.push_back(j);
            }
            std::sort(VR_jets.begin(), VR_jets.end(), [](const HEPUtils::Jet* a, const HEPUtils::Jet* b){ return a->pT() > b->pT(); });



            // Sort object by pT
            sortByPt(BaselineJets); 
            sortByPt(baselineElectrons); 
            sortByPt(baselineMuons); 
            sortByPt(VR_jets); 


            // W-tagging from https://cds.cern.ch/record/2724149/files/ATL-PHYS-PUB-2020-017.pdf
            //              Figure 14 for W-boson 80% effeicency

            // Large-R jet grooming and selection (ATLAS EXOT-2019-04, Table 6)
            // Anti-kt R=1.0 LCTopo inputs, trimming with R_trim=0.2 and f_cut=0.05
            const double Rtrim  = 0.2;   // R_sub
            const double fcut   = 0.05;  // pT fraction
            const double beta   = 1.0;
            FJNS::Filter trimmer(fastjet::JetDefinition(fastjet::kt_algorithm, Rtrim),
                                 fastjet::SelectorPtFractionMin(fcut));
            FJNS::contrib::EnergyCorrelator C2(2, beta, fastjet::contrib::EnergyCorrelator::pt_R);
            FJNS::contrib::EnergyCorrelator C3(3, beta, fastjet::contrib::EnergyCorrelator::pt_R);

            vector<const HEPUtils::Jet *> trimmedLargeRJets;
            // vector<const HEPUtils::Jet *> WJets;
            for (size_t i = 0; i < baseLargeRJets.size(); ++i)
            {
                // Obtain the FastJet PseudoJet objects;
                const fastjet::PseudoJet &pseudojet = baseLargeRJets.at(i)->pseudojet();
                // Make sure there is constituents inside the jets
                if (pseudojet.constituents().empty()) continue;
                fastjet::PseudoJet trimmedJet = trimmer(pseudojet);
                HEPUtils::Jet *hepUtilsJet = new HEPUtils::Jet(trimmedJet);

                // Apply selection after trimming: pT > 200 GeV, |eta| < 2.0, mass > 50 GeV
                if (trimmedJet.pt() > 200. && std::fabs(trimmedJet.eta()) < 2.0 && trimmedJet.m() > 50.)
                {
                    const double jet_mass = trimmedJet.m();
                    // Calculate the Energy correlator functions
                    const double C2_value = C2(trimmedJet);
                    const double C3_value = C3(trimmedJet);
                    const double D2_value = (C2_value > 0) ? C3_value / std::pow(C2_value, 3) : 0.0;

                    // WJetTagger Threshold;
                    bool wtag = Threshold.passTag(trimmedJet.pt(), trimmedJet.m(), D2_value);
                    // if (wtag && random_bool(0.8))
                    trimmedLargeRJets.push_back(hepUtilsJet);
                }
            }
                        // Identify the Higgs candidate large‑R jet (leading trimmed large‑R)
            sortByPt(trimmedLargeRJets);
            const HEPUtils::Jet* HiggsLR = trimmedLargeRJets.empty() ? nullptr : trimmedLargeRJets.front();
            if (!HiggsLR) return;
            // Build the set of VR track‑jets inspected for b‑tagging: those matched to the HiggsLR
            std::vector<const HEPUtils::Jet*> VR_matched;

                        // --- VR track-jet b-tagging (DL1r 70% WP): b=0.70119, c=0.10, light=0.0025
            std::map<const Jet*, bool> vr_btags = generateBTagsMap(VR_jets, 0.70119, 0.10, 0.0025);
            int nVR_assoc_b = 0; 
            int nVR_assoc   = 0; 
            for (const HEPUtils::Jet* j : VR_jets) {
                if (j->mom().deltaR_eta(HiggsLR->mom()) < 1.0) {
                    nVR_assoc += 1; 
                    VR_matched.push_back(j);
                    if (vr_btags.at(j)) nVR_assoc_b += 1; 
                }
            }

            bool collinear_veto = false;
            for (size_t i = 0; i < VR_matched.size() && !collinear_veto; ++i) {
                const HEPUtils::Jet* ji = VR_matched[i];
                const double Ri = VR_Reff(ji->pT());
                for (size_t j = 0; j < VR_jets.size(); ++j) {
                    const HEPUtils::Jet* jj = VR_jets[j];
                    if (jj == ji) continue; // skip self
                    const double Rj = VR_Reff(jj->pT());
                    const double dR = ji->mom().deltaR_eta(jj->mom());
                    const double Rmin_ij = std::min(Ri, Rj);
                    if (dR < Rmin_ij) { collinear_veto = true; break; }
                }
            }

            // --- Diphoton resonance veto (remove overlap with H→γγ searches)
            bool diphoton_veto = false; 
            if (baselinePhotons.size() >= 2) {
                for (size_t i = 0; i < baselinePhotons.size(); ++i) {
                    for (size_t j = i + 1; j < baselinePhotons.size(); ++j) {
                        const double m_gg = (baselinePhotons[i]->mom() + baselinePhotons[j]->mom()).m();
                        if (m_gg > 105. && m_gg < 160.) {
                            diphoton_veto = true; // Reject diphoton Higgs-like events
                        }
                    }
                }
            } 
                        // --- Lepton veto (no isolated electrons or muons expected)
            const bool lepton_veto = signalLep.size() > 0; 

            bool preselection = false; 
            if (collinear_veto) return;

            vector<const HEPUtils::Jet *> sgJets;
            vector<const HEPUtils::Jet *> bJets;
            std::map<const Jet *, bool> analysisBtags = generateBTagsMap(baselineJets, 0.70, 0.10, 0.002);

            for (const HEPUtils::Jet *jet : baselineJets)
            {
                bool isbtag = analysisBtags.at(jet);
                if (isbtag && jet->abseta() < 2.5 && jet->pT() > 25.) bJets.push_back(jet);
                if (jet->mom().deltaR_eta(Whad->mom()) > 1.0) sgJets.push_back(jet);
            }
            SIGNAL_JETS(sgJets, signalJets)

            // bool lep_pre = (signalLep.size() == 1) ? signalLep.at(0)->pT() > 60. : false;
            // bool lRj_pre = (trimmedJets.size() >= 1) ? trimmedJets.at(0)->pT() > 200. : false;
            // bool sRj_pre1 = signalJets.size() >= 3;
            // bool sRj_pre2 = (sRj_pre1) ? signalJets.at(1)->pT() > 25. : false;
            // bool sRj_pre3 = (sRj_pre1) ? signalJets.at(0)->pT() > 200. : false;
            // bool preselection = lep_pre && lRj_pre && sRj_pre1 && sRj_pre2;
            // if (preselection)
            // {

            // double nv_px = pmiss.px();
            // double nv_py = pmiss.py();
            // std::vector<double> pz_nus = calculate_pvz(signalLep.at(0)->mom(), nv_px, nv_py);
            // double nv_pz = solute_pvZ(pz_nus);
            // double nv_E = std::sqrt(nv_px * nv_px + nv_py * nv_py + nv_pz * nv_pz);
            // HEPUtils::P4 vp4(nv_px, nv_py, nv_pz, nv_E);
            // HEPUtils::P4 WLepp4 = vp4 + signalLep.at(0)->mom();

            // const int nbjets = bJets.size();
            // const double dRWW = WLepp4.deltaR_eta(Whad->mom());

            // HEPUtils::P4 p4VLQlep;
            // HEPUtils::P4 p4VLQhad;
            // double dmVLQ = 99999.;
            // double dPhilmet = signalLep.at(0)->mom().deltaPhi(pmiss);
            // double ST = met + signalLep.at(0)->pT();

            // for (const HEPUtils::Jet *jet : signalJets) { ST += jet->pT(); }
            // double dPhiJ0met = signalJets.at(0)->mom().deltaPhi(pmiss);

            // VLQ pairring VLQ-lep VLQ-had
            // for (size_t ii = 0; ii < 3; ii++)
            //     for (size_t jj = 0; jj < 3; jj++)
            //     {
            //     if (ii != jj)
            //     {
            //         double mVLQlep = (WLepp4 + signalJets.at(ii)->mom()).m();
            //         double mVLQhad = (Whad->mom() + signalJets.at(jj)->mom()).m();
            //         if (fabs(mVLQlep - mVLQhad) < dmVLQ)
            //         {
            //         dmVLQ = fabs(mVLQlep - mVLQhad);
            //         p4VLQhad = Whad->mom() + signalJets.at(jj)->mom();
            //         p4VLQlep = WLepp4 + signalJets.at(ii)->mom();
            //         }
            //     }
            //     }

            // bool sr = true;
            // if (sr) FILL_SIGNAL_REGION("SR1")

            // #ifdef CHECK_CUTFLOW
            // if (sr) _histo_mB->fill(p4VLQlep.m());
            // #endif
            // std::cout << "[VR] n_all=" << nVR_all << " n_matched=" << nVR_matched << " n_bMatched=" << nVRb_matched << std::endl;
            // }
            return;
        }

        virtual void collect_results()
        {
            COMMIT_SIGNAL_REGION("SR1", 262, 260, 17)

            COMMIT_CUTFLOWS;
    #ifdef CHECK_CUTFLOW
            std::vector<YODA::AnalysisObject *> histos;
            histos.push_back(_histo_mB);
            histos.push_back(_histo_mVLQ_sr2);
            YODA::WriterYODA::write("ATLAS_EXOT_2019_04.yoda", histos.begin(), histos.end());
            delete _histo_mB;
            delete _histo_mVLQ_sr2;
    #endif
            return;
        }

        protected:
        void analysis_specific_reset()
        {
            for (auto &pair : _counters) { pair.second.reset(); }
        }

        private:
          // ---- Helpers specific to this analysis ----
            double VR_Reff(double pt_GeV, double rho_GeV = 30.0, double Rmin = 0.02, double Rmax = 0.40)
            {
                if (pt_GeV <= 0.) return Rmax;
                const double r = rho_GeV / pt_GeV;
                return std::max(Rmin, std::min(Rmax, r));
            }
          // Note: ghost association is approximated here by ΔR matching where needed.
        };
        DEFINE_ANALYSIS_FACTORY(ATLAS_EXOT_2019_04)
    } // namespace ColliderBit
} // namespace Gambit