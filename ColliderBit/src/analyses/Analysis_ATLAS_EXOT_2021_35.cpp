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


#define CHECK_CUTFLOW

#ifdef CHECK_CUTFLOW
    #include "YODA/Histo1D.h"
    #include "YODA/WriterYODA.h"
#endif


class WJetTagger
{
private:
    struct TaggerBin
    {
        double ptUpper;   
        double d2Cut;     
        double massMin;   
        double massMax;   
    };
    std::vector<TaggerBin> bins;

public:
    WJetTagger()
    {
        bins.push_back({400,    1.49, 57.3, 103});      // pT   < 400
        bins.push_back({600,    1.89, 62.2, 98.5});     // 400  < pT <= 600
        bins.push_back({800,    1.98, 63.9, 99.3});     // 600  < pT <= 800
        bins.push_back({1000,   2.10, 63.1, 99.3});     // 800  < pT <= 1000
        bins.push_back({1200,   2.14, 61.4, 103});      // 1000 < pT <= 1200
        bins.push_back({1400,   2.23, 57.3, 104});      // 1200 < pT <= 1400
        bins.push_back({1600,   2.40, 54.0, 107});      // 1400 < pT <= 1600
        bins.push_back({1800,   2.55, 53.2, 108});      // 1600 < pT <= 1800
        bins.push_back({2000,   2.65, 49.9, 113});      // 1800 < pT <= 2000
        bins.push_back({2200,   2.74, 47.4, 113});      // 2000 < pT <= 2200
        bins.push_back({2400,   3.04, 49.1, 117});      // 2200 < pT <= 2400
        bins.push_back({2600,   3.14, 49.1, 114});      // 2400 < pT <= 2600
    }

    const TaggerBin& getThreshold(double jet_pt) const
    {
        for (const auto& bin : bins)
        {
            if (jet_pt < bin.ptUpper)
                return bin;
        }
        return bins.back();
    }

    bool passTag(double jet_pt, double jet_mass, double jet_d2) const
    {
       const TaggerBin& threshold = getThreshold(jet_pt);

        if (jet_mass < threshold.massMin || jet_mass > threshold.massMax)
            return false;
        if (jet_d2 > threshold.d2Cut)
            return false;
        return true;
    }
};


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
                YODA::Histo1D *_histo_mVLQ_sr1; 
                YODA::Histo1D *_histo_mVLQ_sr2; 
                int Nevent = 0;
            #endif

            static constexpr const char *detector = "ATLAS";
            Analysis_ATLAS_EXOT_2021_035()
            {
                DEFINE_SIGNAL_REGION("SR1")
                DEFINE_SIGNAL_REGION("SR2")

                set_analysis_name("ATLAS_EXOT_2021_035");
                set_luminosity(140.0);

                #ifdef CHECK_CUTFLOW
                    _histo_mVLQ_sr1 = new YODA::Histo1D(10, 0., 2000., "SR1/mVLQlep");
                    _histo_mVLQ_sr2 = new YODA::Histo1D(10, 0., 2000., "SR2/mVLQlep");
                #endif
            }

            void run(const HEPUtils::Event *event)
            {
                #ifdef CHECK_CUTFLOW
                    BEGIN_PRESELECTION

                    if (Nevent % 200 == 0)
                    {
                        cout << "Complete " << Nevent << " Events" << endl;
                    }
                    Nevent += 1; 
                #endif

                double met = event->met();
                HEPUtils::P4 pmiss = event->missingmom();

                BASELINE_PARTICLES(event->electrons(), baselineEl1, 27., 0, DBL_MAX, 1.37)
                BASELINE_PARTICLES(event->electrons(), baselineEl2, 27., 1.52, DBL_MAX, 2.47)
                BASELINE_PARTICLES(event->muons(), baselineMuons, 27., 0, DBL_MAX, 2.5)
                
                BASELINE_PARTICLE_COMBINATION(baselineElectrons, baselineEl1, baselineEl2)
                applyEfficiency(baselineElectrons, ATLAS::eff1DEl.at("PERF_2017_01_ID_Tight"));
                applyEfficiency(baselineMuons, ATLAS::eff1DMu.at("MUON_2018_03_ID_Tight"));
                
                BASELINE_JETS(event->jets("antikt_R04"), baselineJets, 25., 0, DBL_MAX, 2.5)
                BASELINE_JETS(event->jets("antikt_R10"), baseLargeRJets, 200., 0, DBL_MAX, 2.0)

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

                SIGNAL_PARTICLES(baselineElectrons, signalEl)
                SIGNAL_PARTICLES(sgmuons, signalMu)
                SIGNAL_PARTICLE_COMBINATION(signalLep, signalEl, signalMu)

                // W-tagging from https://cds.cern.ch/record/2724149/files/ATL-PHYS-PUB-2020-017.pdf
                //              Figure 14 for W-boson 80% effeicency 
                
                const double Rsub = 0.2;
                const double ptfrac = 0.05;
                const double beta = 1.0; 
                FJNS::Filter trimmer(fastjet::JetDefinition(fastjet::kt_algorithm, Rsub), fastjet::SelectorPtFractionMin(ptfrac));
                FJNS::contrib::EnergyCorrelator C2(2, beta, fastjet::contrib::EnergyCorrelator::pt_R);
                FJNS::contrib::EnergyCorrelator C3(3, beta, fastjet::contrib::EnergyCorrelator::pt_R);  

                
                vector<const HEPUtils::Jet *> trimmedJets; 
                vector<const HEPUtils::Jet *> WJets; 
                for (size_t i = 0; i < baseLargeRJets.size(); ++i)
                {
                    // Obtain the FastJet PseudoJet objects;
                    const fastjet::PseudoJet &pseudojet = baseLargeRJets.at(i)->pseudojet();
                    // Make sure there is constituents inside the jets
                    if (pseudojet.constituents().empty()) continue;
                    fastjet::PseudoJet trimmedJet = trimmer(pseudojet);
                    HEPUtils::Jet* hepUtilsJet = new HEPUtils::Jet(trimmedJet);

                    if (trimmedJet.pt() > 200 &&  fabs(trimmedJet.eta() < 2.0)) { 
                        double jet_mass = trimmedJet.m();
                        if (jet_mass < 0) continue; // filter the negative mass situation 
                        // Calculate the Energy correlator function 
                        double C2_value = C2(trimmedJet);
                        double C3_value = C3(trimmedJet);
                        double D2_value = (C2_value > 0) ? C3_value / std::pow(C2_value, 3) : 0.0;

                        WJetTagger Threshold;
                        bool wtag = Threshold.passTag(trimmedJet.pt(), trimmedJet.m(), D2_value);
                        // if (wtag && random_bool(0.8))
                        if (wtag)
                        {
                            WJets.push_back(hepUtilsJet);
                        }
                        trimmedJets.push_back(hepUtilsJet);
                    }
                }

                const HEPUtils::Jet* Whad = nullptr;
                if (WJets.size() >= 1)  Whad = WJets.at(0);
                else if (trimmedJets.size() >= 1) {
                    double dmw = 999999.0; 
                    for (const HEPUtils::Jet *jet : trimmedJets )
                    {
                        if (jet->mom().m() - mW < dmw) 
                        {
                            dmw = jet->mom().m() - mW ; 
                            Whad = jet; 
                        }
                    }
                }
                if (Whad == nullptr) return; 
                vector<const HEPUtils::Jet *> sgJets; 
                vector<const HEPUtils::Jet *> bJets; 
                std::map<const Jet *, bool> analysisBtags = generateBTagsMap(baselineJets, 0.70, 0.106, 0.00256);

                for (const HEPUtils::Jet *jet : baselineJets)
                {
                    bool isbtag = analysisBtags.at(jet);
                    if (isbtag && jet->abseta() < 2.5 && jet->pT() > 25.)
                        bJets.push_back(jet);
                    if (jet->mom().deltaR_eta(Whad->mom()) > 1.0)
                        sgJets.push_back(jet);
                }
                SIGNAL_JETS(sgJets, signalJets)

                bool lep_pre = (signalLep.size() == 1) ? signalLep.at(0)->pT() > 60. : false;
                bool lRj_pre = (trimmedJets.size() >= 1) ? trimmedJets.at(0)->pT() > 200. : false; 
                bool sRj_pre1 = signalJets.size() >= 3; 
                bool sRj_pre2 = (sRj_pre1) ? signalJets.at(1)->pT() > 25. : false; 
                bool sRj_pre3 = (sRj_pre1) ? signalJets.at(0)->pT() > 200. : false; 
                bool preselection = lep_pre && lRj_pre && sRj_pre1 && sRj_pre2; 
                if (preselection)
                {
                    #ifdef CHECK_CUTFLOW
                        END_PRESELECTION
                    #endif

                    double nv_px = pmiss.px();
                    double nv_py = pmiss.py();
                    std::vector<double> pz_nus = calculate_pvz(signalLep.at(0)->mom(), nv_px, nv_py);
                    double nv_pz = solute_pvZ(pz_nus);
                    double nv_E = std::sqrt(nv_px * nv_px + nv_py * nv_py + nv_pz * nv_pz);
                    HEPUtils::P4 vp4(nv_px, nv_py, nv_pz, nv_E);
                    HEPUtils::P4 WLepp4 = vp4 + signalLep.at(0)->mom();

                    const int nbjets    = bJets.size(); 
                    const double dRWW      = WLepp4.deltaR_eta(Whad->mom()); 

                    HEPUtils::P4 p4VLQlep; 
                    HEPUtils::P4 p4VLQhad; 
                    double dmVLQ = 99999.; 
                    double dPhilmet = signalLep.at(0)->mom().deltaPhi(pmiss); 
                    double ST = met + signalLep.at(0)->pT(); 

                    for (const HEPUtils::Jet * jet:signalJets){
                        ST += jet->pT(); 
                    }
                    double dPhiJ0met = signalJets.at(0)->mom().deltaPhi(pmiss); 

                    // VLQ pairring VLQ-lep VLQ-had 
                    for (size_t ii = 0; ii < 3; ii++) for(size_t jj = 0; jj < 3; jj++)
                    {
                        if (ii != jj) {
                            double mVLQlep = (WLepp4 + signalJets.at(ii)->mom()).m(); 
                            double mVLQhad = (Whad->mom() + signalJets.at(jj)->mom()).m(); 
                            if (fabs(mVLQlep - mVLQhad) < dmVLQ){
                                dmVLQ = fabs(mVLQlep - mVLQhad); 
                                p4VLQhad = Whad->mom() + signalJets.at(jj)->mom(); 
                                p4VLQlep = WLepp4 + signalJets.at(ii)->mom(); 
                            }
                        }
                    }

                    bool sr1 = (nbjets == 0) && (WJets.size() >= 1) && (dRWW > 0.8) && (dPhilmet < 0.5) && (ST >= 2000.) && (dPhiJ0met < 2.75); 
                    bool sr2 = (nbjets == 0) && (WJets.size() >= 1) && (dRWW > 0.8) && (dPhilmet < 0.5) && (ST >= 2000.) && (dPhiJ0met >= 2.75); 
                    if (sr1) FILL_SIGNAL_REGION("SR1") 
                    if (sr2) FILL_SIGNAL_REGION("SR2") 

                    #ifdef CHECK_CUTFLOW
                        if (sr1) _histo_mVLQ_sr1->fill(p4VLQlep.m()); 
                        if (sr2) _histo_mVLQ_sr2->fill(p4VLQlep.m()); 
                    #endif
                }
                return; 

            
            }

            virtual void
            collect_results()
            {
                COMMIT_SIGNAL_REGION("SR1", 156, 150, 10)
                COMMIT_SIGNAL_REGION("SR2", 186, 192, 12)

                COMMIT_CUTFLOWS;
                #ifdef CHECK_CUTFLOW
                    std::vector<YODA::AnalysisObject *> histos; 
                    histos.push_back(_histo_mVLQ_sr1);
                    histos.push_back(_histo_mVLQ_sr2);
                    YODA::WriterYODA::write("ATLAS_EXOT_2021_035.yoda", histos.begin(), histos.end()); 
                    delete _histo_mVLQ_sr1; 
                    delete _histo_mVLQ_sr2; 
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