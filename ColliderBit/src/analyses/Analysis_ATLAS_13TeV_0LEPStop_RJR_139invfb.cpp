///
///  \author Pengxuan Zhu
///  \date 2024 Nov
///
///  *********************************************

// Based on RJR regions of https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/PAPERS/SUSY-2018-12/.
// Luminosity: 139 fb^-1
// Signal Region SRC

#include "gambit/cmake/cmake_variables.hpp"
#ifndef EXCLUDE_ROOT
#ifndef EXCLUDE_RESTFRAMES
#define CHECK_CUTFLOW

#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>
#include <algorithm>
#include <fstream>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"
#include "gambit/ColliderBit/analyses/Cutflow.hpp"
#include "gambit/ColliderBit/analyses/AnalysisMacros.hpp"
#include "gambit/ColliderBit/mt2_bisect.h"
#include "METSignificance/METSignificance.hpp"

#include "RestFrames/RestFrames.hh"
#include "TLorentzVector.h"

using namespace std;

namespace Gambit
{
    namespace ColliderBit
    {
        static bool sortByPT0l(const HEPUtils::Jet *jet1, const HEPUtils::Jet *jet2) { return (jet1->pT() > jet2->pT()); }
        static bool sortByPT0l_sharedptr(std::shared_ptr<HEPUtils::Jet> jet1, std::shared_ptr<HEPUtils::Jet> jet2) { return sortByPT0l(jet1.get(), jet2.get()); }

        class Analysis_ATLAS_13TeV_0LEPStop_RJR_139invfb : public Analysis
        {
        protected:
#ifdef CHECK_CUTFLOW
            Cutflows _cutflows;
#endif

        private:
            // Recursive Jigsaw Objects (using RestFrames)
            unique_ptr<RestFrames::LabRecoFrame> LAB;
            unique_ptr<RestFrames::DecayRecoFrame> CM;
            unique_ptr<RestFrames::DecayRecoFrame> S;
            unique_ptr<RestFrames::VisibleRecoFrame> ISR;
            unique_ptr<RestFrames::VisibleRecoFrame> V;
            unique_ptr<RestFrames::InvisibleRecoFrame> I;

            unique_ptr<RestFrames::InvisibleGroup> INV;
            unique_ptr<RestFrames::CombinatoricGroup> VIS;
            unique_ptr<RestFrames::SetMassInvJigsaw> InvMass;
            unique_ptr<RestFrames::MinMassesCombJigsaw> SplitVis;

        public:
            // Requrired detector sim
            static constexpr const char *detector = "ATLAS";

            void muJetSpecialOverlapRemoval(vector<const HEPUtils::Jet *> &jetvec, vector<const HEPUtils::Particle *> &lepvec)
            {

                vector<const HEPUtils::Jet *> Survivors;

                for (unsigned int itjet = 0; itjet < jetvec.size(); itjet++)
                {
                    bool overlap = false;
                    HEPUtils::P4 jetmom = jetvec.at(itjet)->mom();
                    for (unsigned int itlep = 0; itlep < lepvec.size(); itlep++)
                    {
                        HEPUtils::P4 lepmom = lepvec.at(itlep)->mom();
                        double dR;

                        dR = jetmom.deltaR_eta(lepmom);

                        double DeltaRMax = 0.;
                        if (lepmom.pT() / jetmom.pT() > 0.5)
                            DeltaRMax = 0.2;
                        if (fabs(dR) <= DeltaRMax)
                            overlap = true;
                    }
                    if (overlap)
                        continue;
                    Survivors.push_back(jetvec.at(itjet));
                }
                jetvec = Survivors;

                return;
            }

            struct ptComparison
            {
                bool operator()(const HEPUtils::Particle *i, const HEPUtils::Particle *j) { return (i->pT() > j->pT()); }
            } comparePt;

            struct ptJetComparison
            {
                bool operator()(const HEPUtils::Jet *i, const HEPUtils::Jet *j) { return (i->pT() > j->pT()); }
            } compareJetPt;

            Analysis_ATLAS_13TeV_0LEPStop_RJR_139invfb()
            {
                DEFINE_SIGNAL_REGION("SRC1");
                DEFINE_SIGNAL_REGION("SRC2");
                DEFINE_SIGNAL_REGION("SRC3");
                DEFINE_SIGNAL_REGION("SRC4");
                DEFINE_SIGNAL_REGION("SRC5");

                set_analysis_name("ATLAS_13TeV_0LEPStop_RJR_139invfb");
                set_luminosity(139);

                // enable_progress_tracking(1000);

#ifdef CHECK_CUTFLOW
                cout << "Starting run Analysis \n booking Cutflows" << endl;

                _cutflows.addCutflow("SRC",
                                     {
                                         "MET > 250",
                                         "njets >= 4",
                                         "nbjets >= 1",
                                         "Lepton veto",
                                         "pT j4 > 40 GeV",
                                         "pT j2 > 80 GeV",
                                         "dPhimin(pT1-4, MET) > 0.2",
                                         "Pass MET trigger",
                                         "S > 5",
                                         "njS >= 4",
                                         "nbS >= 2",
                                         "mS > 400 GeV",
                                         "pT1 Sb > 40 GeV",
                                         "dPhi(pTISR, MET) > 3.00",
                                         "pTISR > 400 GeV",
                                         "pT4S > 50 GeV",
                                         "S >= 5.",
                                         "METtrack > 30 GeV",
                                         "dPhi(MET, METtrack) < pi/3",
                                         "0.3 <= RISR < 0.4 (SRC-1)",
                                         "0.4 <= RISR < 0.5 (SRC-2)",
                                         "0.5 <= RISR < 0.6 (SRC-3)",
                                         "0.6 <= RISR < 0.7 (SRC-4)",
                                         "RISR >= 0.7 (SRC-5)",
                                     });
#endif

#pragma omp critical(init_ATLAS_13TeV_0LEPStop_RJR_139invfb)
                {
                    LAB.reset(new RestFrames::LabRecoFrame("LAB", "LAB"));
                    CM.reset(new RestFrames::DecayRecoFrame("CM", "CM"));
                    S.reset(new RestFrames::DecayRecoFrame("S", "S"));
                    ISR.reset(new RestFrames::VisibleRecoFrame("ISR", "ISR"));
                    V.reset(new RestFrames::VisibleRecoFrame("V", "V"));
                    I.reset(new RestFrames::InvisibleRecoFrame("I", "I"));

                    LAB->SetChildFrame(*CM);
                    CM->AddChildFrame(*ISR);
                    CM->AddChildFrame(*S);
                    S->AddChildFrame(*V);
                    S->AddChildFrame(*I);

                    if (!LAB->InitializeTree())
                    {
                        str errmsg;
                        errmsg = "Some problem occurred when calling LAB->InitializeTree() from the Analysis_ATLAS_13TeV_0LEPStop_RJR_139invfb analysis class.\n";
                        piped_errors.request(LOCAL_INFO, errmsg);
                    }

                    /// Jigsaw Rules Set-up ///
                    /// Define Groups ///
                    INV.reset(new RestFrames::InvisibleGroup("INV", "Invisible System"));
                    INV->AddFrame(*I);

                    VIS.reset(new RestFrames::CombinatoricGroup("VIS", "Visible System"));
                    VIS->AddFrame(*ISR);
                    VIS->SetNElementsForFrame(*ISR, 1, false);
                    VIS->AddFrame(*V);
                    VIS->SetNElementsForFrame(*V, 0, false);

                    // Set the invisible system mass to zero
                    InvMass.reset(new RestFrames::SetMassInvJigsaw("InvMass", "kSetMass"));
                    INV->AddJigsaw(*InvMass);

                    // Define the rule for partitioning objects between "ISR" and "V"
                    SplitVis.reset(new RestFrames::MinMassesCombJigsaw("CombPPJigsaw", "kMinMasses"));
                    VIS->AddJigsaw(*SplitVis);

                    // "0" group (ISR)
                    SplitVis->AddFrame(*ISR, 0);
                    // "1" group (V + I)
                    SplitVis->AddFrame(*V, 1);
                    SplitVis->AddFrame(*I, 1);

                    if (!LAB->InitializeAnalysis())
                    {
                        str errmsg;
                        errmsg = "Some problem occured when calling LAB->InitializeAnalysis() from the Analysis_ATLAS_13TeV_0LEPStop_RJR_139invfb analysis class.\n";
                        piped_errors.request(LOCAL_INFO, errmsg);
                    }
                }
            }

            void run(const HEPUtils::Event *event)
            {
                LAB->ClearEvent();
                // Missing Energy
                HEPUtils::P4 metVec = event->missingmom();
                double Met = event->met();

                // Baseline electrons
                vector<const HEPUtils::Particle *> baselineElectrons;
                for (const HEPUtils::Particle *electron : event->electrons())
                {
                    if (electron->pT() > 4.5 && electron->abseta() < 2.47)
                        baselineElectrons.push_back(electron);
                }
                // Loose electron ID selection
                applyEfficiency(baselineElectrons, ATLAS::eff1DEl.at("EGAM_2018_01_Recon"));

                // Baseline muon
                vector<const HEPUtils::Particle *> baselineMuons;
                for (const HEPUtils::Particle *muon : event->muons())
                {
                    if (muon->pT() > 4.0 && muon->abseta() < 2.7)
                        baselineMuons.push_back(muon);
                }

                // Apply muon efficiency
                applyEfficiency(baselineMuons, ATLAS::eff2DMu.at("R2"));

                vector<const HEPUtils::Particle *> baselinePhotons;
                for (const HEPUtils::Particle *photon : event->photons())
                {
                    if (photon->pT() > 25. && photon->abseta() < 2.37)
                        baselinePhotons.push_back(photon);
                }
                // Apply photon efficiency
                applyEfficiency(baselinePhotons, ATLAS::eff2DPhoton.at("R2"));

                // Baseline jets
                vector<const HEPUtils::Jet *> baselineJets;
                for (const HEPUtils::Jet *jet : event->jets("antikt_R04"))
                {
                    if (jet->pT() > 20. && fabs(jet->eta()) < 2.8)
                        baselineJets.push_back(jet);
                }

                // Jets
                vector<const HEPUtils::Jet *> bJets;
                vector<const HEPUtils::Jet *> nonBJets;
                vector<const HEPUtils::Jet *> trueBJets; // for debugging

                // Taus
                // float MtTauCand = -1;
                vector<const HEPUtils::Particle *> tauCands;
                for (const HEPUtils::Particle *tau : event->taus())
                {
                    if (tau->pT() > 20. && tau->abseta() < 2.47)
                    {
                        tauCands.push_back(tau);
                        // HEPUtils::Jet* newJet = new HEPUtils::Jet(tau->mom());
                        // nonBJets.push_back(newJet);
                    }
                }
                applyEfficiency(tauCands, ATLAS::effTau.at("R1"));

                // B-tag efficiencies
                std::map<const Jet *, bool> analysisBtags = generateBTagsMap(baselineJets, 0.77, 0.10, 0.005);

                // const double accbtag = pow(0.7 / 0.77, 2);
                // std::random_device rd;
                // std::mt19937 gen(rd());
                // std::uniform_real_distribution<> dis(0.0, 1.0);
                // double randomNumber = dis(gen);
                // bool accbtag_SRA = randomNumber < accbtag;

                for (const HEPUtils::Jet *jet : baselineJets)
                {
                    bool hasTag = analysisBtags.at(jet);

                    if (hasTag && fabs(jet->eta()) < 2.5 && jet->pT() > 20.)
                    {
                        bJets.push_back(jet);
                    }
                    else
                    {
                        nonBJets.push_back(jet);
                    }
                }

                // Overlap removal
                // Note: ATLAS uses rapidity rather than eta so this version is not 100% accurate
                removeOverlap(baselineElectrons, baselineMuons, 0.01);

                removeOverlap(nonBJets, baselineElectrons, 0.2);
                removeOverlap(baselineElectrons, nonBJets, 0.2);
                removeOverlap(baselineElectrons, bJets, 0.2);

                muJetSpecialOverlapRemoval(nonBJets, baselineMuons);
                removeOverlap(baselineMuons, nonBJets, 0.2);
                removeOverlap(baselineMuons, bJets, 0.2);

                auto lambda = [](double lepton_pT)
                { return std::min(0.4, 0.04 + 10. / (lepton_pT)); };

                removeOverlap(baselineMuons, nonBJets, lambda);
                removeOverlap(baselineMuons, bJets, lambda);
                removeOverlap(baselineElectrons, nonBJets, lambda);
                removeOverlap(baselineElectrons, bJets, lambda);

                // // Fill a jet-pointer-to-bool map to make it easy to check
                // // if a given jet is treated as a b-jet in this analysis
                // map<const HEPUtils::Jet*,bool> analysisBtags;
                for (const HEPUtils::Jet *jet : bJets)
                {
                    analysisBtags[jet] = true;
                }
                for (const HEPUtils::Jet *jet : nonBJets)
                {
                    analysisBtags[jet] = false;
                }

                // After OR Baseline Leptons
                int nBaseElectrons = baselineElectrons.size();
                int nBaseMuons = baselineMuons.size();
                int nLep = nBaseElectrons + nBaseMuons;

                vector<const HEPUtils::Particle *> baselineLeptons = baselineElectrons;
                baselineLeptons.insert(baselineLeptons.end(), baselineMuons.begin(), baselineMuons.end());

                // Signal object containers
                vector<const HEPUtils::Particle *> signalElectrons;
                vector<const HEPUtils::Particle *> signalMuons;

                vector<const HEPUtils::Jet *> signalJets;
                vector<const HEPUtils::Jet *> signalBJets;
                vector<const HEPUtils::Jet *> signalNonBJets;

                // Now apply signal jet cuts
                for (const HEPUtils::Jet *jet : bJets)
                {
                    if (jet->pT() > 20. && fabs(jet->eta()) < 2.5)
                    {
                        signalJets.push_back(jet);
                        signalBJets.push_back(jet);
                    }
                }

                for (const HEPUtils::Jet *jet : nonBJets)
                {
                    if (jet->pT() > 20. && fabs(jet->eta()) < 2.8)
                    {
                        signalJets.push_back(jet);
                        signalNonBJets.push_back(jet);
                    }
                }

                // Sort by pT
                // Put signal jets in pT order
                sort(signalJets.begin(), signalJets.end(), compareJetPt);
                sort(signalBJets.begin(), signalBJets.end(), compareJetPt);
                sort(signalNonBJets.begin(), signalNonBJets.end(), compareJetPt);

                for (const HEPUtils::Particle *electron : baselineElectrons)
                {
                    signalElectrons.push_back(electron);
                }

                for (const HEPUtils::Particle *muon : baselineMuons)
                {
                    signalMuons.push_back(muon);
                }

                double MetSig = calcMETSignificance(baselineElectrons, baselinePhotons, baselineMuons, signalJets, tauCands, metVec);

                // RestFrames Stuff
                double CA_PTISR = 0;
                double CA_MS = 0;
                double CA_NbV = 0;
                double CA_NjV = 0;
                double CA_RISR = 0;
                double CA_dphiISRI = 0;
                double CA_pTjV4 = 0;
                double CA_pTbV1 = 0;

                vector<RestFrames::RFKey> jetID;
                for (const HEPUtils::Jet *jet : signalJets)
                {

                    TLorentzVector jetT4;
                    jetT4.SetPtEtaPhiM(jet->pT(), 0.0, jet->phi(), jet->mass());
                    jetID.push_back(VIS->AddLabFrameFourVector(jetT4));
                }

                TVector3 ETMiss;
                ETMiss.SetXYZ(metVec.px(), metVec.py(), 0.);
                INV->SetLabFrameThreeVector(ETMiss);

                int nBJets = signalBJets.size();
                // int nNonBJets = signalNonBJets.size();
                int nSignalJets = signalJets.size();

                int m_NjV(0);
                int m_NbV(0);
                int m_NbISR(0);
                double m_pTjV4(0.);
                double m_pTbV1(0);
                double m_PTISR(0.);
                double m_MS(0.);
                double m_RISR(0.);
                double m_dphiISRI(0.);

                double dPhiJetMetMin2 = 0;
                double dPhiJetMetMin3 = 0;
                double dPhiJetMetMin4 = 0;
                if (nSignalJets >= 2)
                {
                    dPhiJetMetMin2 = std::min(fabs(metVec.deltaPhi(signalJets[0]->mom())), fabs(metVec.deltaPhi(signalJets[1]->mom())));
                    if (nSignalJets >= 3)
                    {
                        dPhiJetMetMin3 = std::min(dPhiJetMetMin2, fabs(metVec.deltaPhi(signalJets[2]->mom())));
                        if (nSignalJets >= 4)
                        {
                            dPhiJetMetMin4 = std::min(dPhiJetMetMin3, fabs(metVec.deltaPhi(signalJets[3]->mom())));
                        }
                    }
                }

                if (nSignalJets > 0)
                {
                    if (!LAB->AnalyzeEvent())
                    {
                        str errmsg;
                        errmsg = "Some problem occured when calling LAB_comb->AnalyzeEvent() from the Analysis_ATLAS_13TeV_0LEPStop_RJR_139invfb analysis class.\n";
                        piped_warnings.request(LOCAL_INFO, errmsg);
                        return;
                    }

                    for (int i = 0; i < nSignalJets; i++)
                    {
                        if (VIS->GetFrame(jetID[i]) == *V)
                        {
                            m_NjV++;
                            if (m_NjV == 4)
                                m_pTjV4 = signalJets[i]->pT();
                            if (analysisBtags.at(signalJets[i]) && fabs(signalJets[i]->eta()) < 2.5)
                            {
                                m_NbV++;
                                if (m_NbV == 1)
                                    m_pTbV1 = signalJets[i]->pT();
                            }
                        }
                        else
                        {
                            if (analysisBtags.at(signalJets[i]) && fabs(signalJets[i]->eta()) < 2.5)
                                m_NbISR++;
                        }
                    }

                    if (m_NjV >= 1)
                    {
                        TVector3 vP_ISR = ISR->GetFourVector(*CM).Vect();
                        TVector3 vP_I = I->GetFourVector(*CM).Vect();

                        m_PTISR = vP_ISR.Mag();
                        m_RISR = fabs(vP_I.Dot(vP_ISR.Unit())) / m_PTISR;

                        m_MS = S->GetMass();
                        m_dphiISRI = fabs(vP_ISR.DeltaPhi(vP_I));

                        CA_PTISR = m_PTISR;
                        CA_MS = m_MS;
                        CA_NbV = m_NbV;
                        CA_NjV = m_NjV;
                        CA_RISR = m_RISR;
                        CA_dphiISRI = m_dphiISRI;
                        CA_pTjV4 = m_pTjV4;
                        CA_pTbV1 = m_pTbV1;
                    }
                }

                double Ht = 0.;
                for (size_t jet = 0; jet < signalJets.size(); jet++)
                {
                    Ht += signalJets[jet]->pT();
                }
                // double HtSig = Met / sqrt(Ht);

                bool pre1B4J0L = Met > 250 && nLep == 0 && nSignalJets >= 4 && nBJets >= 1 && signalJets[1]->pT() > 80 && signalJets[3]->pT() > 40 && dPhiJetMetMin2 > 0.4;
                bool SRC = pre1B4J0L && CA_NbV >= 2 && MetSig > 5 && CA_NjV >= 4 && CA_pTbV1 > 40 && CA_MS > 400 && CA_dphiISRI > 3.00 && CA_PTISR > 400 && CA_pTjV4 > 50;

                if (SRC && CA_RISR >= 0.3 && CA_RISR < 0.4)
                    _counters.at("SRC1").add_event(event);
                if (SRC && CA_RISR >= 0.4 && CA_RISR < 0.5)
                    _counters.at("SRC2").add_event(event);
                if (SRC && CA_RISR >= 0.5 && CA_RISR < 0.6)
                    _counters.at("SRC3").add_event(event);
                if (SRC && CA_RISR >= 0.6 && CA_RISR < 0.7)
                    _counters.at("SRC4").add_event(event);
                if (SRC && CA_RISR >= 0.7)
                    _counters.at("SRC5").add_event(event);

#ifdef CHECK_CUTFLOW
                const double w = event->weight();
                _cutflows.fillinit(w);

                _cutflows["SRC"].fillnext({Met > 250.,
                                           nSignalJets >= 4,
                                           nBJets >= 1,
                                           nLep == 0,
                                           nSignalJets >= 4 && signalJets[3]->pT() > 40,
                                           nSignalJets >= 2 && signalJets[1]->pT() > 80,
                                           dPhiJetMetMin4 > 0.2,
                                           true,
                                           MetSig > 5,
                                           CA_NjV >= 4,
                                           CA_NbV >= 2,
                                           CA_MS > 400.,
                                           CA_pTbV1 > 40.,
                                           CA_dphiISRI > 3.0,
                                           CA_PTISR > 400.,
                                           CA_pTjV4 > 50.,
                                           true,
                                           true,
                                           true},
                                          w);

                if (SRC)
                {
                    if (CA_RISR >= 0.3 && CA_RISR < 0.4)
                        _cutflows["SRC"].fill(20, true, w);
                    if (CA_RISR >= 0.4 && CA_RISR < 0.5)
                        _cutflows["SRC"].fill(21, true, w);
                    if (CA_RISR >= 0.5 && CA_RISR < 0.6)
                        _cutflows["SRC"].fill(22, true, w);
                    if (CA_RISR >= 0.6 && CA_RISR < 0.7)
                        _cutflows["SRC"].fill(23, true, w);
                    if (CA_RISR >= 0.7)
                        _cutflows["SRC"].fill(24, true, w);
                }
#endif

                return;
            }

            void collect_results()
            {
                add_result(SignalRegionData(_counters.at("SRC1"), 53., {46., 12.}));
                add_result(SignalRegionData(_counters.at("SRC2"), 57., {52., 9.}));
                add_result(SignalRegionData(_counters.at("SRC3"), 38., {38., 7.}));
                add_result(SignalRegionData(_counters.at("SRC4"), 9., {11.8, 3.1}));
                add_result(SignalRegionData(_counters.at("SRC5"), 4., {2.5, 0.7}));

                // COMMIT_CUTFLOWS;
#ifdef CHECK_CUTFLOW
                // _cutflows.combine();
                cout << "\n ===== CUTFLOWS ====== \n"
                     << _cutflows << endl;
                add_cutflows(_cutflows);
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
        };

        DEFINE_ANALYSIS_FACTORY(ATLAS_13TeV_0LEPStop_RJR_139invfb)

    }
}

#endif
#endif