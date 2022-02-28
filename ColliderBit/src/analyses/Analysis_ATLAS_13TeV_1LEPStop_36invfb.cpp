#include "gambit/cmake/cmake_variables.hpp"
#ifndef EXCLUDE_ROOT

#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>

#include "gambit/Utils/threadsafe_rng.hpp"
#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"
#include "gambit/ColliderBit/mt2_bisect.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "HEPUtils/FastJet.h"
#include "TRandom3.h"

using namespace std;

/* The ATLAS 1 lepton direct stop analysis

   Based on: https://arxiv.org/abs/1711.11520

   Code by Martin White (based on ATLAS public code snippet on HepData)

   KNOWN ISSUES

   1) Have not added the BDT signal regions (despite having BDT code from ATLAS). They cover a specific kinematic region where the m_stop - m_chi1 mass difference is m_top, which we already know Pythia does badly with.

   2) We have no equivalent of the ATLAS fakeJER method. Am assuming a 3% JER on every jet for now.

   3) Have used TLorentzVectors for boosting. Could probably be done without ROOT?

*/

namespace Gambit {
  namespace ColliderBit {

    // Need two different functions here for use with std::sort
    bool sortByPT_1l(const HEPUtils::Jet* jet1, const HEPUtils::Jet* jet2) { return (jet1->pT() > jet2->pT()); }
    bool sortByPT_1l_sharedptr(std::shared_ptr<HEPUtils::Jet> jet1, std::shared_ptr<HEPUtils::Jet> jet2) { return sortByPT_1l(jet1.get(), jet2.get()); }

    // Need two different functions here for use with std::sort
    bool sortByMass_1l(const HEPUtils::Jet* jet1, const HEPUtils::Jet* jet2) { return (jet1->mass() > jet2->mass()); }
    bool sortByMass_1l_sharedptr(std::shared_ptr<HEPUtils::Jet> jet1, std::shared_ptr<HEPUtils::Jet> jet2) { return sortByMass_1l(jet1.get(), jet2.get()); }

    double calcMT_1l(HEPUtils::P4 jetMom,HEPUtils::P4 metMom)
    {
      //std::cout << "metMom.px() " << metMom.px() << " jetMom PT " << jetMom.pT() << std::endl;
      double met=sqrt(metMom.px()*metMom.px()+metMom.py()*metMom.py());
      double dphi = metMom.deltaPhi(jetMom);
      double mt=sqrt(2*jetMom.pT()*met*(1-std::cos(dphi)));
      return mt;
    }


    class Analysis_ATLAS_13TeV_1LEPStop_36invfb : public Analysis
    {
    private:

      // Numbers passing cuts
      std::map<string, EventCounter> _counters = {
        {"tN_med", EventCounter("tN_med")},
        {"tN_high", EventCounter("tN_high")},
        {"bWN", EventCounter("bWN")},
        {"bC2x_diag", EventCounter("bC2x_diag")},
        {"bC2x_med", EventCounter("bC2x_med")},
        {"bCbv", EventCounter("bCbv")},
        {"DM_low_loose", EventCounter("DM_low_loose")},
        {"DM_low", EventCounter("DM_low")},
        {"DM_high", EventCounter("DM_high")},
        {"bffN", EventCounter("bffN")},
        {"bCsoft_diag", EventCounter("bCsoft_diag")},
        {"bCsoft_med", EventCounter("bCsoft_med")},
        {"bCsoft_high", EventCounter("bCsoft_high")},
      };

      vector<int> cutFlowVector;
      vector<string> cutFlowVector_str;
      int NCUTS; //=16;


      void LeptonLeptonOverlapRemoval(vector<const HEPUtils::Particle*> &lep1vec, vector<const HEPUtils::Particle*> &lep2vec, double DeltaRMax)
      {

        //Routine to do jet-lepton check
        //Discards jets if they are within DeltaRMax of a lepton

        vector<const HEPUtils::Particle*> Survivors;

        for(unsigned int itlep1 = 0; itlep1 < lep1vec.size(); itlep1++)
        {
          bool overlap = false;
          HEPUtils::P4 lep1mom=lep1vec.at(itlep1)->mom();
          for(unsigned int itlep2 = 0; itlep2 < lep2vec.size(); itlep2++)
          {
            HEPUtils::P4 lep2mom=lep2vec.at(itlep2)->mom();
            double dR;

            dR=lep1mom.deltaR_eta(lep2mom);

            if(fabs(dR) <= DeltaRMax) overlap=true;
          }
          if(overlap) continue;
          Survivors.push_back(lep1vec.at(itlep1));
        }
        lep1vec=Survivors;

        return;
      }


      void JetLeptonOverlapRemoval(vector<const HEPUtils::Jet*> &jetvec, vector<const HEPUtils::Particle*> &lepvec, double DeltaRMax)
      {
        //Routine to do jet-lepton check
        //Discards jets if they are within DeltaRMax of a lepton

        vector<const HEPUtils::Jet*> Survivors;

        for(unsigned int itjet = 0; itjet < jetvec.size(); itjet++)
        {
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


      void LeptonJetOverlapRemoval(vector<const HEPUtils::Particle*> &lepvec, vector<const HEPUtils::Jet*> &jetvec)
      {
        //Routine to do lepton-jet check
        //Discards leptons if they are within dR of a jet as defined in analysis paper

        vector<const HEPUtils::Particle*> Survivors;

        for(unsigned int itlep = 0; itlep < lepvec.size(); itlep++)
        {
          bool overlap = false;
          HEPUtils::P4 lepmom=lepvec.at(itlep)->mom();
          for(unsigned int itjet= 0; itjet < jetvec.size(); itjet++)
          {
            HEPUtils::P4 jetmom=jetvec.at(itjet)->mom();
            double dR;
            double DeltaRMax = std::max(0.1,std::min(0.4, 0.04 + 10 / lepmom.pT()));
            dR=jetmom.deltaR_eta(lepmom);

            if(fabs(dR) <= DeltaRMax) overlap=true;
          }
          if(overlap) continue;
          Survivors.push_back(lepvec.at(itlep));
        }
        lepvec=Survivors;

        return;
      }


    public:

      // Required detector sim
      static constexpr const char* detector = "ATLAS";

      Analysis_ATLAS_13TeV_1LEPStop_36invfb()
      {

        set_analysis_name("ATLAS_13TeV_1LEPStop_36invfb");
        set_luminosity(36.);

        NCUTS=150;

        for(int i=0;i<NCUTS;i++)
        {
          cutFlowVector.push_back(0);
          cutFlowVector_str.push_back("");
        }

      }

      struct ClusteringHistory : public FJNS::PseudoJet::UserInfoBase
      {
        enum Status
        {
          GOOD,
          JET_TOO_SMALL,
          JET_TOO_LARGE,
          TOO_MANY_ITERATIONS,
          NONE,
        };

        struct Step
        {
          double pt;
          double r;
          size_t constit;
          Status status;
        };

        size_t id;  // a per-event unique jet id that is needed for the event dump
        std::vector<Step> steps;

        static ClusteringHistory* AddStep(ClusteringHistory& history, const Step& step)
        {
          auto newHistory = new ClusteringHistory(history);
          newHistory->steps.push_back(step);
          return newHistory;
        }
      };

      // Return the history of a PseudoJet object, handling all the ugly casting.
      ClusteringHistory& GetHistory(const FJNS::PseudoJet& jet)
      {
        auto shared_ptr = jet.user_info_shared_ptr();
        return *dynamic_cast<ClusteringHistory*>(shared_ptr.get());
      }

      static std::vector<FJNS::PseudoJet> SortedByNConstit(std::vector<FJNS::PseudoJet> jets)
      {
        std::sort(jets.begin(), jets.end(), [](const FJNS::PseudoJet& a, const FJNS::PseudoJet& b) {
                        if (a.constituents().size() != b.constituents().size())
                        return a.constituents().size() > b.constituents().size();
                        return a.pt() > b.pt();
                        });

        return jets;
      }

      inline double optimalRadius(const double pT, const double m) { return 2 * m / pT; }
      inline double minRadius(const double pT, const double m) { return optimalRadius(pT, m) - 0.3; }
      inline double maxRadius(const double pT, const double m) { return optimalRadius(pT, m) + 0.5; }


      std::pair<bool, FJNS::PseudoJet> RecursiveRecluster(const FJNS::PseudoJet& candidate, double candRadius,
                   const double mass, size_t step)
      {
        if (minRadius(candidate.pt(), mass) > candRadius)
        {
          GetHistory(candidate).steps.back().status = ClusteringHistory::JET_TOO_SMALL;
          return std::make_pair(false, candidate);
        }
        else if (maxRadius(candidate.pt(), mass) < candRadius)
        {
          const double newR = std::max(maxRadius(candidate.pt(), mass), candRadius / 2.);
          GetHistory(candidate).steps.back().status = ClusteringHistory::JET_TOO_LARGE;

          if (step > 10)
          {
            GetHistory(candidate).steps.back().status = ClusteringHistory::TOO_MANY_ITERATIONS;
            return std::make_pair(false, candidate);
          }

          FJNS::JetDefinition jetDef(FJNS::antikt_algorithm, newR);
          auto cs = new FJNS::ClusterSequence(candidate.constituents(), jetDef);

          std::vector<FJNS::PseudoJet> reclusteredJets;
          reclusteredJets = SortedByNConstit(cs->inclusive_jets());

          if (reclusteredJets.size() == 0)
          {
            delete cs;
            return std::make_pair(false, FJNS::PseudoJet());
          }

          cs->delete_self_when_unused();
          auto newCandidate = reclusteredJets[0];

          auto newHistory = ClusteringHistory::AddStep(
                   GetHistory(candidate),
                   {newCandidate.pt(), newR, newCandidate.constituents().size(), ClusteringHistory::NONE});
          newCandidate.set_user_info(newHistory);

          return RecursiveRecluster(newCandidate, newR, mass, step + 1);
        }
        else
        {
          GetHistory(candidate).steps.back().status = ClusteringHistory::GOOD;
          return std::make_pair(true, candidate);
        }
      }


      HEPUtils::P4 reclusteredParticle(vector<const HEPUtils::Jet*> jets, vector<const HEPUtils::Jet*> bjets,
                                       const double mass, const bool useBJets)
      {

        //AnalysisObject p = AnalysisObject(0., 0., 0., 0., 0, 0, AnalysisObjectType::JET, 0, 0);
        HEPUtils::P4 p;
        double r0 = 3.0;

        vector<const HEPUtils::Jet*> usejets;
        for(const HEPUtils::Jet* jet : jets)
        {
          usejets.push_back(jet);
        }

        if (useBJets && bjets.size())
        {
          for(const HEPUtils::Jet* bjet : bjets)
          {
            usejets.push_back(bjet);
          }
        }

        std::vector<FJNS::PseudoJet> initialJets;

        for (const HEPUtils::Jet* jet : usejets)
        {
          FJNS::PseudoJet Pjet(jet->mom().px(), jet->mom().py(), jet->mom().pz(), jet->mom().E());
          initialJets.push_back(Pjet);
        }

        FJNS::JetDefinition jetDef(FJNS::antikt_algorithm, r0);
        FJNS::ClusterSequence cs(initialJets, jetDef);

        auto candidates = FJNS::sorted_by_pt(cs.inclusive_jets());

        std::vector<FJNS::PseudoJet> selectedJets;
        selectedJets.reserve(candidates.size());
        std::vector<FJNS::PseudoJet> badJets;
        badJets.reserve(candidates.size());

        size_t i = 0;
        for (auto& cand : candidates)
        {
          auto history = new ClusteringHistory();
          history->id = i;
          history->steps.push_back({cand.pt(), r0, cand.constituents().size(), ClusteringHistory::NONE});
          cand.set_user_info(history);
          ++i;
        }

        for (const auto& cand : candidates)
        {
          bool selected = false;
          FJNS::PseudoJet jet;

          std::tie(selected, jet) = RecursiveRecluster(cand, r0, mass, 0);

          if (selected)
            selectedJets.push_back(jet);
          else
            badJets.push_back(jet);
        }

        if (selectedJets.size() < 1)
        {
          return p;
        }

        vector<std::shared_ptr<HEPUtils::Jet>> aoSelectedJets;
        for (const FJNS::PseudoJet& j : selectedJets) aoSelectedJets.push_back(std::make_shared<HEPUtils::Jet>(HEPUtils::mk_p4(j)));

        //for (const auto jet : selectedJets)
        //  aoSelectedJets.push_back(
        //     AnalysisObject(jet.px(), jet.py(), jet.pz(), jet.E(), 0, 0, AnalysisObjectType::COMBINED, 0, 0));

        std::sort(aoSelectedJets.begin(), aoSelectedJets.end(), sortByPT_1l_sharedptr);
        p = aoSelectedJets[0]->mom();

        return p;
      }


      void run(const HEPUtils::Event* event)
      {

        // Missing energy
        HEPUtils::P4 metVec = event->missingmom();
        double Met = event->met();

        // Construct baseline electron objects
        vector<const HEPUtils::Particle*> baselineElectrons;
        for (const HEPUtils::Particle* electron : event->electrons())
        {
          if (electron->pT() > 5. && electron->abseta() < 2.47)
          {
            baselineElectrons.push_back(electron);
          }
        }

        // Apply electron efficiency
        ATLAS::applyElectronEff(baselineElectrons);

        // Construct baseline muon objects
        vector<const HEPUtils::Particle*> baselineMuons;
        for (const HEPUtils::Particle* muon : event->muons())
        {
          if (muon->pT() > 4. && muon->abseta() < 2.7)
          {
            baselineMuons.push_back(muon);
          }
        }

        // Apply muon efficiency
        ATLAS::applyMuonEff(baselineMuons);

        // Construct set of all light baseline leptons
        vector<const HEPUtils::Particle*> baselineLeptons = baselineElectrons;
        baselineLeptons.insert(baselineLeptons.end(), baselineMuons.begin(), baselineMuons.end() );

        // Construct baseline tau objects
        vector<const HEPUtils::Particle*> baselineTaus;
        for (const HEPUtils::Particle* tau : event->taus())
        {
          if (tau->pT() > 20. && fabs(tau->eta()) < 2.5) baselineTaus.push_back(tau);
        }
        // Apply tau efficiency
        ATLAS::applyTauEfficiencyR1(baselineTaus);

        // Photons
        vector<const HEPUtils::Particle*> signalPhotons;
        for (const HEPUtils::Particle* photon : event->photons())
        {
          signalPhotons.push_back(photon);
        }

        // Jets
        vector<const HEPUtils::Jet*> bJets;
        vector<const HEPUtils::Jet*> nonBJets;
        vector<const HEPUtils::Jet*> trueBJets; //for debugging

        // Get b jets
        /// @note We assume that b jets have previously been 100% tagged
        const std::vector<double>  a = {0,10.};
        const std::vector<double>  b = {0,10000.};
        const std::vector<double> c = {0.77}; // set b-tag efficiency to 77%
        HEPUtils::BinnedFn2D<double> _eff2d(a,b,c);
        for (const HEPUtils::Jet* jet : event->jets())
        {
          bool hasTag=has_tag(_eff2d, fabs(jet->eta()), jet->pT());
          if (jet->pT() > 20. && fabs(jet->eta()) < 4.9)
          {
            if(jet->btag() && hasTag && fabs(jet->eta()) < 2.5 && jet->pT() > 20.)
            {
              bJets.push_back(jet);
            }
            else
            {
              nonBJets.push_back(jet);
            }
          }
        }

        // Note: use paper description instead of code snippet
        // This is not identical to the overlap removal in the paper
        // Probably good enough though
        LeptonLeptonOverlapRemoval(baselineMuons,baselineElectrons,0.01); // mimics shared track requirement
        JetLeptonOverlapRemoval(nonBJets,baselineElectrons,0.2);
        LeptonJetOverlapRemoval(baselineElectrons,nonBJets);
        LeptonJetOverlapRemoval(baselineElectrons,bJets);
        LeptonJetOverlapRemoval(baselineMuons,nonBJets);
        LeptonJetOverlapRemoval(baselineMuons,bJets);
        LeptonLeptonOverlapRemoval(baselineTaus,baselineElectrons,0.1);

        // Fill a jet-pointer-to-bool map to make it easy to check
        // if a given jet is treated as a b-jet in this analysis
        map<const HEPUtils::Jet*,bool> analysisBtags;
        for (const HEPUtils::Jet* jet : bJets) {
          analysisBtags[jet] = true;
        }
        for (const HEPUtils::Jet* jet : nonBJets) {
          analysisBtags[jet] = false;
        }

        // Signal object containers
        vector<const HEPUtils::Particle*> signalElectrons;
        vector<const HEPUtils::Particle*> signalSoftElectrons;
        vector<const HEPUtils::Particle*> signalMuons;
        vector<const HEPUtils::Particle*> signalSoftMuons;
        vector<const HEPUtils::Particle*> signalLeptons;
        vector<const HEPUtils::Particle*> signalSoftLeptons;
        vector<const HEPUtils::Particle*> electronsForVeto;
        vector<const HEPUtils::Particle*> muonsForVeto;

        vector<const HEPUtils::Jet*> signalJets;
        vector<const HEPUtils::Jet*> signalBJets;
        vector<const HEPUtils::Jet*> signalNonBJets;

        // Now apply signal jet cuts
        for (const HEPUtils::Jet* jet : bJets)
        {
          if(jet->pT() > 25. && fabs(jet->eta())<2.5)
          {
            signalJets.push_back(jet);
            signalBJets.push_back(jet);
          }
        }

        for (const HEPUtils::Jet* jet : nonBJets)
        {
          if(jet->pT() > 25. && fabs(jet->eta())<2.5)
          {
            signalJets.push_back(jet);
            signalNonBJets.push_back(jet);
          }
        }

        // Note that the isolation requirements and tight selection are currently missing

        for (const HEPUtils::Particle* electron : baselineElectrons)
        {
          signalSoftElectrons.push_back(electron);
          signalSoftLeptons.push_back(electron);
          if(electron->pT() > 25.)
          {
            signalElectrons.push_back(electron);
            signalLeptons.push_back(electron);
          }
        }

        for (const HEPUtils::Particle* muon : baselineMuons)
        {
          signalSoftMuons.push_back(muon);
          signalSoftLeptons.push_back(muon);
          if(muon->pT() > 25.)
          {
            signalMuons.push_back(muon);
            signalLeptons.push_back(muon);
          }
        }

        // We now have the signal electrons, muons, jets and b jets- move on to the analysis

        int nJets=signalJets.size();
        int nBJets = signalBJets.size();

        // Minimal event selection
        bool cut_minSelection=false;
        if((Met > 100. && (baselineElectrons.size()+baselineMuons.size()) == 1 &&
            ((signalSoftLeptons.size() == 1 || signalLeptons.size() == 1)) && nJets > 1)) cut_minSelection=true;

        vector<const HEPUtils::Jet*> mostBjetLike;
        vector<const HEPUtils::Jet*> signalNotBjetLike;
        vector<const HEPUtils::Jet*> signalNotBjet;

        // create containers with exactly 2 jets being considered to be b-jets and the inverse
        int bJet1 = -1, bJet2 = -1;

        for (unsigned int i = 0; i < signalJets.size(); ++i)
        {
          if (!analysisBtags.at(signalJets[i])) continue;
          if (bJet1 == -1)
            bJet1 = i;
          else if (bJet2 == -1)
          {
            bJet2 = i;
            break;
          }
        }
        if (bJet2 == -1)
        {
          for (unsigned int i = 0; i < signalJets.size(); ++i)
          {
            if (analysisBtags.at(signalJets[i])) continue;
            if (bJet1 == -1)
              bJet1 = i;
            else if (bJet2 == -1)
            {
              bJet2 = i;
              break;
            }
          }
        }

        if(signalJets.size()>1)
        {
          mostBjetLike.push_back(signalJets.at(bJet1));
          mostBjetLike.push_back(signalJets.at(bJet2));
        }

        for (int i = 0; i < (int)signalJets.size(); ++i)
        {
          if (!analysisBtags.at(signalJets[i])) signalNotBjet.push_back(signalJets.at(i));
          if (i == bJet1 || i == bJet2) continue;
          signalNotBjetLike.push_back(signalJets.at(i));
        }

        /* ensure object collections to be pT sorted */
        std::sort(signalJets.begin(), signalJets.end(), sortByPT_1l);
        //if (baseTaus.size() > 0) sortObjectsByPt(baseTaus);

        // Now make a collection to hold the JER for each jet
        // Have obtained the values from Matthias' BuckFast code
        // https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/CONFNOTES/ATLAS-CONF-2015-017/
        // Parameterisation can be still improved, but eta dependence is minimal
        const std::vector<double>  binedges_eta = {0,10.};
        const std::vector<double>  binedges_pt = {0,50.,70.,100.,150.,200.,1000.,10000.};
        const std::vector<double> JetsJER = {0.145,0.115,0.095,0.075,0.07,0.05,0.04};
        static HEPUtils::BinnedFn2D<double> _resJets2D(binedges_eta,binedges_pt,JetsJER);
        vector<double> signalJER;

        for(unsigned int i = 0; i < signalJets.size(); ++i)signalJER.push_back(_resJets2D.get_at(signalJets[i]->abseta(), signalJets[i]->pT()));

        float sigmaAbsHtMiss = 0;
        float Ht = 0;
        /* calculate vecHtMiss */
        HEPUtils::P4 vecHtMiss;
        HEPUtils::P4 leptonHtMiss;

        bool preselLowMet=false;
        bool preselHighMet=false;
        double MetPerp = 0.;
        double HtSigMiss=0.;
        double absDPhiJMet0 = 0.;
        double absDPhiJMet1 = 0.;
        double absDPhiJiMet = 0.;
        double mT=0.;
        double topReclM=0.;
        double WReclM=0.;
        double amT2=0.;
        double dRbl=9999.;
        double mT2Tau=0.;
        double dPhiMetLep;
        double pTLepOverMet=999.;

        if(cut_minSelection)
        {

          for (unsigned int i = 0; i < baselineLeptons.size(); ++i)
          {
            vecHtMiss    -= baselineLeptons[i]->mom();
            leptonHtMiss -= baselineLeptons[i]->mom();
          }

          for (unsigned int i = 0; i < signalJets.size(); ++i)
            vecHtMiss -= signalJets[i]->mom();

          /* calculate Ht and HtSig */
          for (const HEPUtils::Jet* jet : signalJets) Ht += jet->pT();

          TRandom3 myRandom;
          myRandom.SetSeed(signalJets[0]->pT());

          int PEs = 100;
          // double smear_factor;
          double ETmissmean = 0, ETmissRMS = 0;
          for (int j = 0; j < PEs; ++j)
          {
            double jetHtx = leptonHtMiss.px();
            double jetHty = leptonHtMiss.py();

            for (unsigned int i = 0; i < signalJets.size(); ++i)
            {
              //std::normal_distribution<> dx(signalJets[i]->mom().px(), signalJets[i]->mom().px() * signalJER[i]);
              //std::normal_distribution<> dy(signalJets[i]->mom().py(), signalJets[i]->mom().px() * signalJER[i]);
              //jetHtx -= dx(Random::rng());
              //jetHty -= dy(Random::rng());
              jetHtx -= myRandom.Gaus(signalJets[i]->mom().px(), signalJets[i]->mom().px() * signalJER[i]);
              jetHty -= myRandom.Gaus(signalJets[i]->mom().py(), signalJets[i]->mom().px() * signalJER[i]);
            }
            double ETtemp = sqrt(jetHtx * jetHtx + jetHty * jetHty);
            ETmissmean += ETtemp;
            ETmissRMS  += ETtemp * ETtemp;
          }

          ETmissmean = ETmissmean / PEs;
          sigmaAbsHtMiss = sqrt((ETmissRMS / PEs) - ETmissmean * ETmissmean);

          HtSigMiss = (ETmissmean - 100.) / sigmaAbsHtMiss;

          double absDPhiJMet[4] = {fabs(signalJets[0]->mom().deltaPhi(metVec)), fabs(signalJets[1]->mom().deltaPhi(metVec)),
                 signalJets.size() > 2 ? fabs(signalJets[2]->mom().deltaPhi(metVec)) : NAN,
                 signalJets.size() > 3 ? fabs(signalJets[3]->mom().deltaPhi(metVec)) : NAN};

          if(nJets>0)absDPhiJMet0 = absDPhiJMet[0];
          if(nJets>1)absDPhiJMet1 = absDPhiJMet[1];

          for (int i = 1; i < 4; i++)
            if (absDPhiJMet[i] < absDPhiJiMet) absDPhiJiMet = absDPhiJMet[i];

          mT = calcMT_1l(baselineLeptons[0]->mom(), metVec);
          dPhiMetLep = fabs(metVec.deltaPhi(baselineLeptons[0]->mom()));

          // Calculate MT2 tau using the leading tau in the event
          mT2Tau = 120.;
          if(baselineTaus.size() > 0)
          {
            double pa_tau[3] = { 0, baselineTaus[0]->mom().px(), baselineTaus[0]->mom().py() };
            double pb_tau[3] = { 0, baselineLeptons[0]->mom().px(), baselineLeptons[0]->mom().py() };
            double pmiss_tau[3] = { 0, metVec.px(), metVec.py() };
            double mn_tau = 0.;
            mt2_bisect::mt2 mt2_event_tau;
            mt2_event_tau.set_momenta(pa_tau,pb_tau,pmiss_tau);
            mt2_event_tau.set_mn(mn_tau);

            mT2Tau = mt2_event_tau.get_mt2();
          }

          pTLepOverMet = baselineLeptons[0]->pT() / Met;
          preselHighMet = Met > 230 && mT > 30;
          preselLowMet  =  baselineLeptons[0]->pT() > 27 && signalBJets.size() > 0 && signalJets[0]->pT() > 50. && Met > 100 && mT > 90;

          // Apply tight selection if lepton is an electron
          // Am using same selection as 8 TeV (probably needs updating)
          // Note that we have already applied a 1 lepton cut
          if (baselineElectrons.size()==1 && baselineMuons.size()==0)
          {
            vector<const HEPUtils::Particle*> tightElectrons;
            tightElectrons.push_back(baselineElectrons[0]);
            ATLAS::applyTightIDElectronSelection(tightElectrons);
            preselLowMet = preselLowMet && (tightElectrons.size()==1);
          }

          // Now calculate amT2 using two different assignments of the b jets and the leptons

          HEPUtils::P4 lepton_plus_bjet0;
          HEPUtils::P4 lepton_plus_bjet1;

          lepton_plus_bjet0 = baselineLeptons[0]->mom()+mostBjetLike[0]->mom();
          lepton_plus_bjet1 = baselineLeptons[0]->mom()+mostBjetLike[1]->mom();

          double pa_a[3] = { 0, lepton_plus_bjet0.px(), lepton_plus_bjet0.py() };
          double pb_a[3] = { 80, mostBjetLike[1]->mom().px(), mostBjetLike[1]->mom().py() };
          double pmiss_a[3] = { 0, metVec.px(), metVec.py() };
          double mn_a = 0.;

          mt2_bisect::mt2 mt2_event_a;

          mt2_event_a.set_momenta(pa_a,pb_a,pmiss_a);
          mt2_event_a.set_mn(mn_a);

          double mt2a = mt2_event_a.get_mt2();

          double pa_b[3] = { 0, lepton_plus_bjet1.px(), lepton_plus_bjet1.py() };
          double pb_b[3] = { 80, mostBjetLike[0]->mom().px(), mostBjetLike[0]->mom().py() };
          double pmiss_b[3] = { 0, metVec.px(), metVec.py() };
          double mn_b = 0.;

          mt2_bisect::mt2 mt2_event_b;

          mt2_event_b.set_momenta(pa_b,pb_b,pmiss_b);
          mt2_event_b.set_mn(mn_b);
          double mt2b = mt2_event_b.get_mt2();

          amT2 = std::min(mt2a,mt2b);
          dRbl = baselineLeptons[0]->mom().deltaR_eta(mostBjetLike[0]->mom());

          /* Reconstruct top by a chi2 based method */
          float mW = 80.;
          float mTop = 170.;
          float chi2min = 9e99;
          //AnalysisObject* topChi2 = new AnalysisObject(0., 0., 0., 0., 0, 0, AnalysisObjectType::JET, 0, 0);
          HEPUtils::P4 topChi2;
          int jetComb[3] = {0, 0, 0};
          vector<double> signalBJER;

          for(unsigned int i = 0; i < mostBjetLike.size(); ++i)signalBJER.push_back(_resJets2D.get_at(mostBjetLike[i]->abseta(), mostBjetLike[i]->pT()));
          float f;

          for (int i = 0; i < (int)signalJets.size(); ++i)
          {
            if (i == bJet1 || i == bJet2) continue;
            for (int j = i + 1; j < (int)signalJets.size(); ++j)
            {
              if (j == bJet1 || j == bJet2) continue;
              for (unsigned int k = 0; k < mostBjetLike.size() && k < 2; ++k)
              {
                f = pow((signalJets[i]->mom() + signalJets[j]->mom() + mostBjetLike[k]->mom()).m() - mTop, 2) /
                        (pow((signalJets[i]->mom() + signalJets[j]->mom() + mostBjetLike[k]->mom()).m(), 2) *
                        (pow(signalJER[i], 2) + pow(signalJER[j], 2) + pow(signalBJER[k], 2))) +
                         pow((signalJets[i]->mom() + signalJets[j]->mom()).m() - mW, 2) /
                        (pow((signalJets[i]->mom() + signalJets[j]->mom()).m(), 2) * (pow(signalJER[i], 2) + pow(signalJER[j], 2)));
                if (f < chi2min)
                {
                  chi2min = f;
                  jetComb[0] = i;
                  jetComb[1] = j;
                  jetComb[2] = k;
                }
              }
            }
          }
          topChi2 = signalJets[jetComb[0]]->mom() + signalJets[jetComb[1]]->mom() + mostBjetLike[jetComb[2]]->mom();


          HEPUtils::P4 top1;
          top1 = baselineLeptons[0]->mom() + (jetComb[2] == 0 ? mostBjetLike[1]->mom() : mostBjetLike[0]->mom());

          /* calculate MetPerp */

          TLorentzVector ttbar;
          ttbar.SetPxPyPzE((topChi2 + top1).px(),(topChi2 + top1).py(),(topChi2 + top1).pz(),(topChi2 + top1).E());
          TLorentzVector top1Rest;
          top1Rest.SetPxPyPzE(top1.px(),top1.py(),top1.pz(),top1.E());
          TLorentzVector metRest;
          metRest.SetPxPyPzE(metVec.px(),metVec.py(),metVec.pz(),metVec.E());


          ttbar.Boost(-ttbar.Px() / ttbar.E(), -ttbar.Py() / ttbar.E(), -ttbar.Pz() / ttbar.E());


          top1Rest.Boost(-ttbar.Px() / ttbar.E(), -ttbar.Py() / ttbar.E(), -ttbar.Pz() / ttbar.E());
          metRest.Boost(-ttbar.Px() / ttbar.E(), -ttbar.Py() / ttbar.E(), -ttbar.Pz() / ttbar.E());
          MetPerp = metRest.Vect().XYvector().Norm(top1Rest.Vect().XYvector()).Mod();

          // Now we have to do the fancy jet reclustering to get reconstructed W and top particles

          HEPUtils::P4 WRecl = reclusteredParticle(signalNotBjet, mostBjetLike, mW, false); //signalNotBjet+mostBjetLike is inconsistent but bjets are not used anyway
          HEPUtils::P4 topRecl = reclusteredParticle(signalNotBjetLike, mostBjetLike, 175., true);

          topReclM=0;

          if (nBJets > 0 && nJets > 3 && preselHighMet)topReclM=topRecl.m();
          WReclM = WRecl.m();

        }

        // Should now be ready to do signal selections

        bool is_tN_med=false;
        bool is_tN_high=false;
        bool is_bWN=false;
        bool is_bC2x_diag=false;
        bool is_bC2x_med=false;
        bool is_bCbv=false;
        // bool is_DM_low_loose=false;  // <-- We currently don't use this
        bool is_DM_low=false;
        bool is_DM_high=false;

        bool is_bffN=false;
        bool is_bCsoft_diag=false;
        bool is_bCsoft_med=false;
        bool is_bCsoft_high=false;

        // non-soft lepton selections
        if (signalLeptons.size() == 1)
        {
          //tN_med
          if (nJets > 3 && nBJets > 0 && preselLowMet && signalJets[0]->pT() > 60 && signalJets[1]->pT() > 50 &&
              signalJets[3]->pT() > 40 && Met > 250 && MetPerp > 230 && HtSigMiss > 14 && mT > 160 && amT2 > 175 &&
              topReclM > 150 && dRbl < 2.0 && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && mT2Tau > 80)
            is_tN_med=true;

          //tN_high
          if (nJets > 3 && nBJets > 0 && preselHighMet && signalJets[0]->pT() > 100 && signalJets[1]->pT() > 80 &&
              signalJets[2]->pT() > 50 && signalJets[3]->pT() > 30 && Met > 550 && HtSigMiss > 27 && mT > 160 &&
              amT2 > 175 && topReclM > 130 && dRbl < 2.0 && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 &&
              mT2Tau > 80)
            is_tN_high=true;

          //bWN
          if (nJets > 3 && nBJets > 0 && preselHighMet && signalJets[0]->pT() > 50 && Met > 300 && mT > 130 &&
              amT2 < 110 && dPhiMetLep < 2.5 && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && mT2Tau > 80)
            is_bWN=true;

          //bC2x_diag
          if (nJets > 3 && nBJets > 1 && preselHighMet && signalJets[2]->pT() > 75 && signalJets[3]->pT() > 30 &&
              signalBJets[1]->pT() > 30 && Met > 230 && HtSigMiss > 13 && mT > 180 && amT2 > 175 &&
              absDPhiJMet0 > 0.7 && absDPhiJMet1 > 0.7 && WReclM > 50 && mT2Tau > 80)
            is_bC2x_diag=true;

          //bC2x_med
          if (nJets > 3 && nBJets > 1 && preselHighMet && signalJets[0]->pT() > 200 && signalJets[1]->pT() > 140 &&
              signalBJets[1]->pT() > 140 && Met > 230 && HtSigMiss > 10 && mT > 120 && amT2 > 300 &&
              absDPhiJMet0 > 0.9 && absDPhiJMet1 > 0.9 && WReclM > 50 && mT2Tau > 80)
            is_bC2x_med=true;

          //bCbv
          if (nJets > 1 && nBJets == 0 && preselHighMet && signalJets[0]->pT() > 120 && signalJets[1]->pT() > 80 &&
              Met > 360 && HtSigMiss > 16 && mT > 200 && absDPhiJMet0 > 2.0 && absDPhiJMet1 > 0.8 &&
              WReclM >= 70 && WReclM <= 100 && dPhiMetLep > 1.2 && baselineLeptons[0]->pT() > 60)
            is_bCbv=true;

          // We currently don't use this.
          // //DM_low_loose
          // if (nJets > 3 && nBJets > 0 && preselHighMet && signalJets[1]->pT() > 60 && signalJets[2]->pT() > 40 &&
          //     Met > 300 && mT > 120 && HtSigMiss > 14 && amT2 > 140 && dPhiMetLep > 0.8 && absDPhiJiMet > 1.4)
          //   is_DM_low_loose=true;

          //DM_low
          if (nJets > 3 && nBJets > 0 && preselHighMet && signalJets[0]->pT() > 120 && signalJets[1]->pT() > 85 &&
              signalJets[2]->pT() > 65 && signalBJets[0]->pT() > 60 && Met > 320 && mT > 170 && HtSigMiss > 14 &&
              amT2 > 160 && topReclM > 130 && dPhiMetLep > 1.2 && absDPhiJiMet > 1.0 && mT2Tau > 80)
            is_DM_low=true;

          //DM_high
          if (nJets > 3 && nBJets > 0 && preselHighMet && signalJets[0]->pT() > 125 && signalJets[1]->pT() > 75 &&
              signalJets[2]->pT() > 65 && Met > 380 && mT > 225 && amT2 > 190 && topReclM > 130 &&
              dPhiMetLep > 1.2 && absDPhiJiMet > 1.0)
            is_DM_high=true;
        }

        // Soft-lepton selections
        bool preselSoftLep=false;
        double Wpt = 0.;

        double minDPhiMetBJet = 99999.;
        for(size_t i=0;i<signalBJets.size();i++)
        {
          double dPhi_tmp = fabs(signalBJets[i]->mom().deltaPhi(metVec));
          if(dPhi_tmp<minDPhiMetBJet)minDPhiMetBJet=dPhi_tmp;
        }

        double dRbb=0;
        if(nBJets>1)dRbb=mostBjetLike[0]->mom().deltaR_eta(mostBjetLike[1]->mom());


        if (signalSoftLeptons.size() == 1)
        {
          preselSoftLep = Met > 230;

          // Apply tight selection if lepton is an electron
          // Am using same selection as 8 TeV (probably needs updating)
          // Note that we have already applied a 1 lepton cut
          if (signalSoftElectrons.size()==1 && signalSoftMuons.size()==0)
          {
            vector<const HEPUtils::Particle*> tightElectrons;
            tightElectrons.push_back(signalSoftElectrons[0]);
            ATLAS::applyTightIDElectronSelection(tightElectrons);
            preselSoftLep = preselSoftLep && (tightElectrons.size()==1);
          }

          Wpt = (signalSoftLeptons[0]->mom()+metVec).pT();
        }

        //bffN
        if (nJets > 1 && nBJets > 0 && preselSoftLep && signalJets[0]->pT() > 400 && Met > 300 && mT < 160 &&
            pTLepOverMet < 0.02 && minDPhiMetBJet < 1.5 && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 &&
            topReclM < 150 && !analysisBtags.at(signalJets[0]))is_bffN=true;

        //bCsoft_diag
        if (nJets > 1 && nBJets > 0 && preselSoftLep && signalJets[0]->pT() > 400 && Met > 300 && mT < 50 &&
            pTLepOverMet < 0.02 && minDPhiMetBJet < 1.5 && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 &&
            topReclM < 150 && !analysisBtags.at(signalJets[0]))is_bCsoft_diag=true;

        //bCsoft_med
        if (nJets > 2 && nBJets > 1 && preselSoftLep && signalJets[0]->pT() > 120 && signalJets[1]->pT() > 60 &&
            signalJets[2]->pT() > 40 && signalBJets[0]->pT() > 120 && signalBJets[1]->pT() > 60 && Met > 230 &&
            mT < 160 && pTLepOverMet < 0.03 && amT2 > 200 && minDPhiMetBJet > 0.8 && absDPhiJMet0 > 0.4 &&
            absDPhiJMet1 > 0.4 && Wpt > 400)is_bCsoft_med=true;

        //bCsoft_high
        if (nJets > 1 && nBJets > 1 && preselSoftLep && signalJets[1]->pT() > 100 && signalBJets[1]->pT() > 100 &&
            Met > 230 && mT < 160 && pTLepOverMet < 0.03 && amT2 > 300 && minDPhiMetBJet > 0.4 &&
            absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && Wpt > 500 && dRbb > 0.8)is_bCsoft_high=true;

        //bool isSRD_high=false;

        cutFlowVector_str[0] = "No cuts ";
        cutFlowVector_str[1] = "Derivation skim";
        cutFlowVector_str[2] = ">=1 baseline lepton ";
        cutFlowVector_str[3] = ">=1 signal lepton ";
        cutFlowVector_str[4] = "==1 signal lepton ";
        cutFlowVector_str[5] = "==1 baseline lepton ";
        cutFlowVector_str[6] = "XE trigger, >=4 jets, met > 230 GeV ";
        cutFlowVector_str[7] = "deltaPhi(j1,met) > 0.4 ";
        cutFlowVector_str[8] = "deltaPhi(j2,met) > 0.4 ";
        cutFlowVector_str[9] = "mT2tau > 80 GeV ";
        cutFlowVector_str[10] = "tN_med: j0 pT > 60 GeV";
        cutFlowVector_str[11] = "tN_med: j1 pT > 50 GeV";
        cutFlowVector_str[12] = "tN_med: j2 pT > 40 GeV ";
        cutFlowVector_str[13] = "tN_med: j3 pT > 40 GeV ";
        cutFlowVector_str[14] = "tN_med: met > 250 GeV ";
        cutFlowVector_str[15] = "tN_med: metPerp > 230 GeV";
        cutFlowVector_str[16] = "tN_med: HTmissSig > 14 ";
        cutFlowVector_str[17] = "tN_med: mT > 160 GeV";
        cutFlowVector_str[18] = "tN_med: amt2 > 175 GeV";
        cutFlowVector_str[19] = "tN_med: >=1 b jet ";
        cutFlowVector_str[20] = "tN_med: deltaR(b,l) < 2.0";
        cutFlowVector_str[21] = "tN_med: mtop_recl > 150 GeV";
        cutFlowVector_str[22] = "tN_high: j0 pT > 100 GeV ";
        cutFlowVector_str[23] = "tN_high: j1 pT > 80 GeV ";
        cutFlowVector_str[24] = "tN_high: j2 pT > 50 GeV";
        cutFlowVector_str[25] = "tN_high: j3 pT > 30 GeV";
        cutFlowVector_str[26] = "tN_high: met > 550 GeV ";
        cutFlowVector_str[27] = "tN_high: HTmissSig > 27";
        cutFlowVector_str[28] = "tN_high: mT > 160 GeV ";
        cutFlowVector_str[29] = "tN_high: amT2 > 175 GeV ";
        cutFlowVector_str[30] = "tN_high: >= 1 b jet";
        cutFlowVector_str[31] = "tN_high: deltaR(b,l) < 2.0";
        cutFlowVector_str[32] = "tN_high: mtop_recl > 130 GeV";
        cutFlowVector_str[33] = "bWN: jet0 pT > 50 GeV";
        cutFlowVector_str[34] = "bWN: Met > 300 GeV ";
        cutFlowVector_str[35] = "bWN: mT > 130 GeV";
        cutFlowVector_str[36] = "bWN: amT2 < 110 GeV";
        cutFlowVector_str[37] = "bWN: >=1 b jet";
        cutFlowVector_str[38] = "bWN: deltaPhi(l,ptmiss) < 2.5";
        cutFlowVector_str[39] = "bffN: Soft lepton preselection";
        cutFlowVector_str[40] = "bffN: Met > 300 GeV";
        cutFlowVector_str[41] = "bffN: jet0 pT > 400 GeV";
        cutFlowVector_str[42] = "bffN: mT < 160 GeV";
        cutFlowVector_str[43] = "bffN: leading jet not b-tagged";
        cutFlowVector_str[44] = "bffN: min(DPhi(ptmiss, b-jet)) < 1.5";
        cutFlowVector_str[45] = "bffN: pTl/Met < 0.05 ";
        cutFlowVector_str[46] = "bffN: top veto (or mtop_recl < 150 GeV) ";
        cutFlowVector_str[47] = "bffN: pTl/met < 0.02 ";
        cutFlowVector_str[48] = "bC2x_diag: jet0 pT > 75 GeV";
        cutFlowVector_str[49] = "bC2x_diag: jet2 pT > 75 GeV ";
        cutFlowVector_str[50] = "bC2x_diag: jet3 pT > 75 GeV ";
        cutFlowVector_str[51] = "bC2x_diag: jet4 pT > 30 GeC ";
        cutFlowVector_str[52] = "bC2x_diag: >=2 b jet ";
        cutFlowVector_str[53] = "bC2x_diag: bjet1 pT > 30 GeV ";
        cutFlowVector_str[54] = "bC2x_diag: dPhi(j1,ptmiss) > 0.7 ";
        cutFlowVector_str[55] = "bC2x_diag: dPhi(j2,ptmiss) > 0.7 ";
        cutFlowVector_str[56] = "bC2x_diag: HTmissSig > 13 ";
        cutFlowVector_str[57] = "bC2x_diag: mT > 180 GeV ";
        cutFlowVector_str[58] = "bC2x_diag: amT2 > 175 GeV ";
        cutFlowVector_str[59] = "bC2x_diag: mWrecl > 50 GeV ";
        cutFlowVector_str[60] = "bC2x_med: jet0 pT > 200 GeV ";
        cutFlowVector_str[61] = "bC2x_med: jet1 pT > 140 GeV ";
        cutFlowVector_str[62] = "bC2x_med: >=2 b jet ";
        cutFlowVector_str[63] = "bC2x_med: bjet0 pT > 140 GeV ";
        cutFlowVector_str[64] = "bC2x_med: bjet1 pT > 140 GeV";
        cutFlowVector_str[65] = "bC2x_med: dPhi(j1,ptmiss) > 0.9 ";
        cutFlowVector_str[66] = "bC2x_med: dPhi(j2,ptmiss) > 0.9 " ;
        cutFlowVector_str[67] = "bC2x_med: HTmissSig > 10";
        cutFlowVector_str[68] = "bC2x_med: mT > 120 GeV";
        cutFlowVector_str[69] = "bC2x_med: amT2 > 300 GeV ";
        cutFlowVector_str[70] = "bC2x_med: mWrecl > 50 GeV ";
        cutFlowVector_str[71] = "bCbv: jet0 pT > 120 GeV";
        cutFlowVector_str[72] = "bCbv: jet1 pT > 80 GeV ";
        cutFlowVector_str[73] = "bCbv: ==0 b jets ";
        cutFlowVector_str[74] = "bCbv: lepton pt > 60 GeV ";
        cutFlowVector_str[75] = "bCbv: dPhi(j1,ptmiss) > 2.0 ";
        cutFlowVector_str[76] = "bCbv: dPhi(j2,ptmiss) > 0.8 ";
        cutFlowVector_str[77] = "bCbv: Met > 360 GeV ";
        cutFlowVector_str[78] = "bCbv: HtmissSig > 16";
        cutFlowVector_str[79] = "bCbv: mT > 200 GeV";
        cutFlowVector_str[80] = "bCbv: mWrecl in [70,100] GeV";
        cutFlowVector_str[81] = "bCbv: dPhi(l,ptmiss) > 1.2";
        cutFlowVector_str[82] = "bCsoft_diag: Soft lepton preselection";
        cutFlowVector_str[83] = "bCsoft_diag: Met > 300 GeV";
        cutFlowVector_str[84] = "bCsoft_diag: jet0 pT > 400 GeV ";
        cutFlowVector_str[85] = "bCsoft_diag: mT < 160 GeV ";
        cutFlowVector_str[86] = "bCsoft_diag: leading jet not b-tagged ";
        cutFlowVector_str[87] = "bCsoft_diag: mT < 50 GeV ";
        cutFlowVector_str[88] = "bCsoft_diag: min(dPhi(ptmiss, b-jet)) < 1.5 ";
        cutFlowVector_str[89] = "bCsoft_diag: pTl/Met < 0.05 ";
        cutFlowVector_str[90] = "bCsoft_diag: top veto (or mtop_recl < 150 GeV) ";
        cutFlowVector_str[91] = "bCsoft_diag: pTl/Met < 0.02";
        cutFlowVector_str[92] = "bCsoft_med: Soft lepton preselection ";
        cutFlowVector_str[93] = "bCsoft_med: >=3 jets";
        cutFlowVector_str[94] = "bCsoft_med: pTW > 400 GeV";
        cutFlowVector_str[95] = "bCsoft_med: jet0 pT > 120 GeV";
        cutFlowVector_str[96] = "bCsoft_med: jet1 pT > 60 GeV";
        cutFlowVector_str[97] = "bCsoft_med: jet2 pT > 40 GeV";
        cutFlowVector_str[98] = "bCsoft_med: mT < 160 GeV";
        cutFlowVector_str[99] = "bCsoft_med: amT2 > 200 GeV";
        cutFlowVector_str[100] = "bCsoft_med: >=2 b jet";
        cutFlowVector_str[101] = "bCsoft_med: bjet0 pT > 120 GeV ";
        cutFlowVector_str[102] = "bCsoft_med: bjet1 pT > 60 GeV";
        cutFlowVector_str[103] = "bCsoft_med: min(dPhi(ptmiss, b-jet)) > 0.8 ";
        cutFlowVector_str[104] = "bCsoft_med: pTl/Met < 0.1";
        cutFlowVector_str[105] = "bCsoft_med: pTl/Met < 0.03";
        cutFlowVector_str[106] = "bCsoft_high: XE trigger, >=2 jets, Met > 230 GeV";
        cutFlowVector_str[107] = "bCsoft_high: dPhi(j1,ptmiss) > 0.4";
        cutFlowVector_str[108] = "bCsoft_high: dPhi(j2,ptmiss) > 0.4";
        cutFlowVector_str[109] = "bCsoft_high: jet0 pt > 100 GeV";
        cutFlowVector_str[110] = "bCsoft_high: jet1 pt > 100 GeV";
        cutFlowVector_str[111] = "bCsoft_high: mT < 160 GeV";
        cutFlowVector_str[112] = "bCsoft_high: pTW > 500 GeV";
        cutFlowVector_str[113] = "bCsoft_high: dRbb > 0.8";
        cutFlowVector_str[114] = "bCsoft_high: min(dPhi(ptmiss, b-jet))";
        cutFlowVector_str[115] = "bCsoft_high: >=2 b jet";
        cutFlowVector_str[116] = "bCsoft_high: bjet0 pT > 100 GeV";
        cutFlowVector_str[117] = "bCsoft_high: bjet1 pT > 100 GeV";
        cutFlowVector_str[118] = "bCsoft_high: amT2 > 300 GeV";

        for(int j=0;j<NCUTS;j++)
        {
          if(
             (j==0) ||

             (j==1 ) ||

             (j==2 && baselineLeptons.size()>0) ||

             (j==3 && baselineLeptons.size()>0 && signalLeptons.size()>0) ||

             (j==4 && baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1) ||

             (j==5 && baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1) ||

             (j==6 && baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=4 && Met > 230.) ||

             (j==7 && baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=4 && Met > 230. && absDPhiJMet0 > 0.4) ||

             (j==8 && baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=4 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4) ||

             (j==9 && baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=4 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && mT2Tau > 80) ||

             //tN_med cutflow

             (j==10 && baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=4 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && mT2Tau > 80 && signalJets[0]->pT() > 60 ) ||

             (j==11 && baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=4 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && mT2Tau > 80 && signalJets[0]->pT() > 60 && signalJets[1]->pT() > 60) ||

             (j==12 && baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=4 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && mT2Tau > 80 && signalJets[0]->pT() > 60 && signalJets[1]->pT() > 60 &&  signalJets[2]->pT() > 40) ||

             (j==13 && baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=4 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && mT2Tau > 80 && signalJets[0]->pT() > 60 && signalJets[1]->pT() > 60 &&  signalJets[2]->pT() > 40 && signalJets[3]->pT() > 40) ||

             (j==14 && baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=4 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && mT2Tau > 80 && signalJets[0]->pT() > 60 && signalJets[1]->pT() > 60 &&  signalJets[2]->pT() > 40 && signalJets[3]->pT() > 40 && Met > 250.) ||

             (j==15 && baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=4 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && mT2Tau > 80 && signalJets[0]->pT() > 60 && signalJets[1]->pT() > 60 &&  signalJets[2]->pT() > 40 && signalJets[3]->pT() > 40 && Met > 250. && MetPerp > 230) ||

             (j==16 && baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=4 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && mT2Tau > 80 && signalJets[0]->pT() > 60 && signalJets[1]->pT() > 60 &&  signalJets[2]->pT() > 40 && signalJets[3]->pT() > 40 && Met > 250. && MetPerp > 230 && HtSigMiss > 14) ||

             (j==17 && baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=4 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && mT2Tau > 80 && signalJets[0]->pT() > 60 && signalJets[1]->pT() > 60 &&  signalJets[2]->pT() > 40 && signalJets[3]->pT() > 40 && Met > 250. && MetPerp > 230 && HtSigMiss > 14 && mT > 160) ||

             (j==18 && baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=4 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && mT2Tau > 80 && signalJets[0]->pT() > 60 && signalJets[1]->pT() > 60 &&  signalJets[2]->pT() > 40 && signalJets[3]->pT() > 40 && Met > 250. && MetPerp > 230 && HtSigMiss > 14 && mT > 160 && amT2 > 175) ||

             (j==19 && baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=4 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && mT2Tau > 80 && signalJets[0]->pT() > 60 && signalJets[1]->pT() > 60 &&  signalJets[2]->pT() > 40 && signalJets[3]->pT() > 40 && Met > 250. && MetPerp > 230 && HtSigMiss > 14 && mT > 160 && amT2 > 175 && nBJets >=1) ||

             (j==20 && baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=4 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && mT2Tau > 80 && signalJets[0]->pT() > 60 && signalJets[1]->pT() > 60 &&  signalJets[2]->pT() > 40 && signalJets[3]->pT() > 40 && Met > 250. && MetPerp > 230 && HtSigMiss > 14 && mT > 160 && amT2 > 175 && nBJets >=1 &&  dRbl < 2.0) ||

             (j==21 && baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=4 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && mT2Tau > 80 && signalJets[0]->pT() > 60 && signalJets[1]->pT() > 60 &&  signalJets[2]->pT() > 40 && signalJets[3]->pT() > 40 && Met > 250. && MetPerp > 230 && HtSigMiss > 14 && mT > 160 && amT2 > 175 && nBJets >=1 &&  dRbl < 2.0 && topReclM > 150) ||

             // tN_high cutflow

             (j==22 && baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=4 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && mT2Tau > 80 && signalJets[0]->pT() > 100) ||

             (j==23 && baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=4 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && mT2Tau > 80 && signalJets[0]->pT() > 100 && signalJets[1]->pT() > 80) ||

             (j==24 && baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=4 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && mT2Tau > 80 && signalJets[0]->pT() > 100 && signalJets[1]->pT() > 80 && signalJets[2]->pT() > 50) ||

             (j==25 && baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=4 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && mT2Tau > 80 && signalJets[0]->pT() > 100 && signalJets[1]->pT() > 80 && signalJets[2]->pT() > 50 && signalJets[3]->pT() > 30) ||

             (j==26 && baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=4 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && mT2Tau > 80 && signalJets[0]->pT() > 100 && signalJets[1]->pT() > 80 && signalJets[2]->pT() > 50 && signalJets[3]->pT() > 30 && Met > 550.) ||

             (j==27 && baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=4 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && mT2Tau > 80 && signalJets[0]->pT() > 100 && signalJets[1]->pT() > 80 && signalJets[2]->pT() > 50 && signalJets[3]->pT() > 30 && Met > 550. &&  HtSigMiss > 27) ||

             (j==28 && baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=4 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && mT2Tau > 80 && signalJets[0]->pT() > 100 && signalJets[1]->pT() > 80 && signalJets[2]->pT() > 50 && signalJets[3]->pT() > 30 && Met > 550. &&  HtSigMiss > 27 && mT > 160) ||

             (j==29 && baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=4 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && mT2Tau > 80 && signalJets[0]->pT() > 100 && signalJets[1]->pT() > 80 && signalJets[2]->pT() > 50 && signalJets[3]->pT() > 30 && Met > 550. &&  HtSigMiss > 27 && mT > 160 && amT2 > 175.) ||

             (j==30 && baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=4 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && mT2Tau > 80 && signalJets[0]->pT() > 100 && signalJets[1]->pT() > 80 && signalJets[2]->pT() > 50 && signalJets[3]->pT() > 30 && Met > 550. &&  HtSigMiss > 27 && mT > 160 && amT2 > 175. && nBJets >=1) ||

             (j==31 && baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=4 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && mT2Tau > 80 && signalJets[0]->pT() > 100 && signalJets[1]->pT() > 80 && signalJets[2]->pT() > 50 && signalJets[3]->pT() > 30 && Met > 550. &&  HtSigMiss > 27 && mT > 160 && amT2 > 175. && nBJets >=1 && dRbl < 2.0) ||

             (j==32 && baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=4 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && mT2Tau > 80 && signalJets[0]->pT() > 100 && signalJets[1]->pT() > 80 && signalJets[2]->pT() > 50 && signalJets[3]->pT() > 30 && Met > 550. &&  HtSigMiss > 27 && mT > 160 && amT2 > 175. && nBJets >=1 && dRbl < 2.0 && topReclM > 130.) ||

             // bWN cutflow

             (j==33 && baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=4 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && mT2Tau > 80 && signalJets[0]->pT() > 50.) ||

             (j==34 && baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=4 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && mT2Tau > 80 && signalJets[0]->pT() > 50. && Met > 300) ||

             (j==35 && baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=4 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && mT2Tau > 80 && signalJets[0]->pT() > 50. && Met > 300 && mT > 130) ||

             (j==36 && baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=4 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && mT2Tau > 80 && signalJets[0]->pT() > 50. && Met > 300 && mT > 130 && amT2 < 110) ||

             (j==37 && baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=4 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && mT2Tau > 80 && signalJets[0]->pT() > 50. && Met > 300 && mT > 130 && amT2 < 110 && nBJets>=1) ||

             (j==38 && baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=4 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && mT2Tau > 80 && signalJets[0]->pT() > 50. && Met > 300 && mT > 130 && amT2 < 110 && nBJets>=1 && dPhiMetLep < 2.5 ) ||

             // bffN cutflow

             (j==39 && baselineLeptons.size()==1 && nJets > 1 && nBJets > 0 && preselSoftLep) ||

             (j==40 && baselineLeptons.size()==1 && nJets > 1 && nBJets > 0 && preselSoftLep && Met > 300.) ||

             (j==41 && baselineLeptons.size()==1 && nJets > 1 && nBJets > 0 && preselSoftLep && Met > 300. && nJets > 0 && signalJets[0]->pT() > 400.) ||

             (j==42 && baselineLeptons.size()==1 && nJets > 1 && nBJets > 0 && preselSoftLep && Met > 300. && nJets > 0 && signalJets[0]->pT() > 400. && mT < 160.) ||

             (j==43 && baselineLeptons.size()==1 && nJets > 1 && nBJets > 0 && preselSoftLep && Met > 300. && nJets > 0 && signalJets[0]->pT() > 400. && mT < 160. &&  !analysisBtags.at(signalJets[0])) ||

             (j==44 && baselineLeptons.size()==1 && nJets > 1 && nBJets > 0 && preselSoftLep && Met > 300. && nJets > 0 && signalJets[0]->pT() > 400. && mT < 160. &&  !analysisBtags.at(signalJets[0]) && minDPhiMetBJet < 1.5) ||

             (j==45 && baselineLeptons.size()==1 && nJets > 1 && nBJets > 0 && preselSoftLep && Met > 300. && nJets > 0 && signalJets[0]->pT() > 400. && mT < 160. &&  !analysisBtags.at(signalJets[0]) && minDPhiMetBJet < 1.5 && pTLepOverMet < 0.05) ||

             (j==46 && baselineLeptons.size()==1 && nJets > 1 && nBJets > 0 && preselSoftLep && Met > 300. && nJets > 0 && signalJets[0]->pT() > 400. && mT < 160. &&  !analysisBtags.at(signalJets[0]) && minDPhiMetBJet < 1.5 && pTLepOverMet < 0.05 && topReclM < 150) ||

             (j==47 && baselineLeptons.size()==1 && nJets > 1 && nBJets > 0 && preselSoftLep && Met > 300. && nJets > 0 && signalJets[0]->pT() > 400. && mT < 160. &&  !analysisBtags.at(signalJets[0]) && minDPhiMetBJet < 1.5 && pTLepOverMet < 0.05 && topReclM < 150 && pTLepOverMet < 0.02) ||

             // bC2x_diag cutflow

             (j==48 &&  baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=4 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && mT2Tau > 80 && signalJets[0]->pT() > 75) ||

             (j==49 &&  baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=4 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && mT2Tau > 80 && signalJets[0]->pT() > 75 && signalJets[1]->pT() > 75) ||

             (j==50 &&  baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=4 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && mT2Tau > 80 && signalJets[0]->pT() > 75 && signalJets[1]->pT() > 75 && signalJets[2]->pT() > 75) ||

             (j==51 &&  baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=4 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && mT2Tau > 80 && signalJets[0]->pT() > 75 && signalJets[1]->pT() > 75 && signalJets[2]->pT() > 75 && signalJets[3]->pT() > 30) ||

             (j==52 &&  baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=4 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && mT2Tau > 80 && signalJets[0]->pT() > 75 && signalJets[1]->pT() > 75 && signalJets[2]->pT() > 75 && signalJets[3]->pT() > 30 && nBJets>=2) ||

             (j==53 &&  baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=4 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && mT2Tau > 80 && signalJets[0]->pT() > 75 && signalJets[1]->pT() > 75 && signalJets[2]->pT() > 75 && signalJets[3]->pT() > 30 && nBJets>=2 && signalBJets[1]->pT() > 30) ||

             (j==54 &&  baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=4 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && mT2Tau > 80 && signalJets[0]->pT() > 75 && signalJets[1]->pT() > 75 && signalJets[2]->pT() > 75 && signalJets[3]->pT() > 30 && nBJets>=2 && signalBJets[1]->pT() > 30 && absDPhiJMet0 > 0.7) ||

             (j==55 &&  baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=4 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && mT2Tau > 80 && signalJets[0]->pT() > 75 && signalJets[1]->pT() > 75 && signalJets[2]->pT() > 75 && signalJets[3]->pT() > 30 && nBJets>=2 && signalBJets[1]->pT() > 30 && absDPhiJMet0 > 0.7 && absDPhiJMet1 > 0.7) ||

             (j==56 &&  baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=4 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && mT2Tau > 80 && signalJets[0]->pT() > 75 && signalJets[1]->pT() > 75 && signalJets[2]->pT() > 75 && signalJets[3]->pT() > 30 && nBJets>=2 && signalBJets[1]->pT() > 30 && absDPhiJMet0 > 0.7 && absDPhiJMet1 > 0.7 && HtSigMiss > 13) ||

             (j==57 &&  baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=4 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && mT2Tau > 80 && signalJets[0]->pT() > 75 && signalJets[1]->pT() > 75 && signalJets[2]->pT() > 75 && signalJets[3]->pT() > 30 && nBJets>=2 && signalBJets[1]->pT() > 30 && absDPhiJMet0 > 0.7 && absDPhiJMet1 > 0.7 && HtSigMiss > 13 && mT > 180) ||

             (j==58 &&  baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=4 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && mT2Tau > 80 && signalJets[0]->pT() > 75 && signalJets[1]->pT() > 75 && signalJets[2]->pT() > 75 && signalJets[3]->pT() > 30 && nBJets>=2 && signalBJets[1]->pT() > 30 && absDPhiJMet0 > 0.7 && absDPhiJMet1 > 0.7 && HtSigMiss > 13 && mT > 180 && amT2 > 175) ||

             (j==59 &&  baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=4 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && mT2Tau > 80 && signalJets[0]->pT() > 75 && signalJets[1]->pT() > 75 && signalJets[2]->pT() > 75 && signalJets[3]->pT() > 30 && nBJets>=2 && signalBJets[1]->pT() > 30 && absDPhiJMet0 > 0.7 && absDPhiJMet1 > 0.7 && HtSigMiss > 13 && mT > 180 && amT2 > 175 && WReclM > 50) ||

             // bC2x_med

             (j==60 &&  baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=4 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && mT2Tau > 80 && signalJets[0]->pT() > 200) ||

             (j==61 &&  baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=4 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && mT2Tau > 80 && signalJets[0]->pT() > 200 && signalJets[1]->pT() > 140) ||

             (j==62 &&  baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=4 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && mT2Tau > 80 && signalJets[0]->pT() > 200 && signalJets[1]->pT() > 140 && nBJets >=2) ||

             (j==63 &&  baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=4 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && mT2Tau > 80 && signalJets[0]->pT() > 200 && signalJets[1]->pT() > 140 && nBJets >=2 && signalBJets[0]->pT() > 140) ||

             (j==64 &&  baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=4 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && mT2Tau > 80 && signalJets[0]->pT() > 200 && signalJets[1]->pT() > 140 && nBJets >=2 && signalBJets[0]->pT() > 140 && signalBJets[1]->pT() > 140) ||

             (j==65 &&  baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=4 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && mT2Tau > 80 && signalJets[0]->pT() > 200 && signalJets[1]->pT() > 140 && nBJets >=2 && signalBJets[0]->pT() > 140 && signalBJets[1]->pT() > 140 && absDPhiJMet0 > 0.9) ||

             (j==66 &&  baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=4 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && mT2Tau > 80 && signalJets[0]->pT() > 200 && signalJets[1]->pT() > 140 && nBJets >=2 && signalBJets[0]->pT() > 140 && signalBJets[1]->pT() > 140 && absDPhiJMet0 > 0.9 && absDPhiJMet1 > 0.9) ||

             (j==67 &&  baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=4 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && mT2Tau > 80 && signalJets[0]->pT() > 200 && signalJets[1]->pT() > 140 && nBJets >=2 && signalBJets[0]->pT() > 140 && signalBJets[1]->pT() > 140 && absDPhiJMet0 > 0.9 && absDPhiJMet1 > 0.9 && HtSigMiss > 10) ||

             (j==68 &&  baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=4 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && mT2Tau > 80 && signalJets[0]->pT() > 200 && signalJets[1]->pT() > 140 && nBJets >=2 && signalBJets[0]->pT() > 140 && signalBJets[1]->pT() > 140 && absDPhiJMet0 > 0.9 && absDPhiJMet1 > 0.9 && HtSigMiss > 10 && mT > 120) ||

             (j==69 &&  baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=4 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && mT2Tau > 80 && signalJets[0]->pT() > 200 && signalJets[1]->pT() > 140 && nBJets >=2 && signalBJets[0]->pT() > 140 && signalBJets[1]->pT() > 140 && absDPhiJMet0 > 0.9 && absDPhiJMet1 > 0.9 && HtSigMiss > 10 && mT > 120 && amT2 > 300) ||

             (j==70 &&  baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=4 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && mT2Tau > 80 && signalJets[0]->pT() > 200 && signalJets[1]->pT() > 140 && nBJets >=2 && signalBJets[0]->pT() > 140 && signalBJets[1]->pT() > 140 && absDPhiJMet0 > 0.9 && absDPhiJMet1 > 0.9 && HtSigMiss > 10 && mT > 120 && amT2 > 300 && WReclM > 50) ||

             // bCbv cutflow

             (j==71 &&  baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=2 && Met > 230. && signalJets[0]->pT() > 120) ||

             (j==72 &&  baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=2 && Met > 230. && signalJets[0]->pT() > 120 && signalJets[1]->pT() > 80) ||

             (j==73 &&  baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=2 && Met > 230. && signalJets[0]->pT() > 120 && signalJets[1]->pT() > 80 && nBJets==0) ||

             (j==74 &&  baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=2 && Met > 230. && signalJets[0]->pT() > 120 && signalJets[1]->pT() > 80 && nBJets==0 &&  baselineLeptons[0]->pT() > 60) ||

             (j==75 &&  baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=2 && Met > 230. && signalJets[0]->pT() > 120 && signalJets[1]->pT() > 80 && nBJets==0 &&  baselineLeptons[0]->pT() > 60 && absDPhiJMet0 > 2.0 ) ||

             (j==76 &&  baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=2 && Met > 230. && signalJets[0]->pT() > 120 && signalJets[1]->pT() > 80 && nBJets==0 &&  baselineLeptons[0]->pT() > 60 && absDPhiJMet0 > 2.0 && absDPhiJMet1 > 0.8) ||

             (j==77 &&  baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=2 && Met > 230. && signalJets[0]->pT() > 120 && signalJets[1]->pT() > 80 && nBJets==0 &&  baselineLeptons[0]->pT() > 60 && absDPhiJMet0 > 2.0 && absDPhiJMet1 > 0.8 && Met > 360) ||

             (j==78 &&  baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=2 && Met > 230. && signalJets[0]->pT() > 120 && signalJets[1]->pT() > 80 && nBJets==0 &&  baselineLeptons[0]->pT() > 60 && absDPhiJMet0 > 2.0 && absDPhiJMet1 > 0.8 && Met > 360 && HtSigMiss > 16) ||

             (j==79 &&  baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=2 && Met > 230. && signalJets[0]->pT() > 120 && signalJets[1]->pT() > 80 && nBJets==0 &&  baselineLeptons[0]->pT() > 60 && absDPhiJMet0 > 2.0 && absDPhiJMet1 > 0.8 && Met > 360 && HtSigMiss > 16 && mT > 200) ||

             (j==80 &&  baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=2 && Met > 230. && signalJets[0]->pT() > 120 && signalJets[1]->pT() > 80 && nBJets==0 &&  baselineLeptons[0]->pT() > 60 && absDPhiJMet0 > 2.0 && absDPhiJMet1 > 0.8 && Met > 360 && HtSigMiss > 16 && mT > 200 && WReclM >= 70 && WReclM <= 100) ||

             (j==81 &&  baselineLeptons.size()>0 && signalLeptons.size()>0 && signalLeptons.size()==1 && baselineLeptons.size()==1 && nJets >=2 && Met > 230. && signalJets[0]->pT() > 120 && signalJets[1]->pT() > 80 && nBJets==0 &&  baselineLeptons[0]->pT() > 60 && absDPhiJMet0 > 2.0 && absDPhiJMet1 > 0.8 && Met > 360 && HtSigMiss > 16 && mT > 200 && WReclM >= 70 && WReclM <= 100 && dPhiMetLep > 1.2 ) ||

             // bCsoft_diag

             (j==82 && baselineLeptons.size()==1 && nJets > 1 && nBJets > 0 && preselSoftLep) ||

             (j==83 && baselineLeptons.size()==1 && nJets > 1 && nBJets > 0 && preselSoftLep && Met > 300.) ||

             (j==84 && baselineLeptons.size()==1 && nJets > 1 && nBJets > 0 && preselSoftLep && Met > 300. && signalJets[0]->pT() > 400) ||

             (j==85 && baselineLeptons.size()==1 && nJets > 1 && nBJets > 0 && preselSoftLep && Met > 300. && signalJets[0]->pT() > 400 && mT < 160) ||

             (j==86 && baselineLeptons.size()==1 && nJets > 1 && nBJets > 0 && preselSoftLep && Met > 300. && signalJets[0]->pT() > 400 && mT < 160 && !analysisBtags.at(signalJets[0])) ||

             (j==87 && baselineLeptons.size()==1 && nJets > 1 && nBJets > 0 && preselSoftLep && Met > 300. && signalJets[0]->pT() > 400 && mT < 160 && !analysisBtags.at(signalJets[0]) && mT < 50) ||

             (j==88 && baselineLeptons.size()==1 && nJets > 1 && nBJets > 0 && preselSoftLep && Met > 300. && signalJets[0]->pT() > 400 && mT < 160 && !analysisBtags.at(signalJets[0]) && mT < 50 && minDPhiMetBJet < 1.5) ||

             (j==89 && baselineLeptons.size()==1 && nJets > 1 && nBJets > 0 && preselSoftLep && Met > 300. && signalJets[0]->pT() > 400 && mT < 160 && !analysisBtags.at(signalJets[0]) && mT < 50 && minDPhiMetBJet < 1.5 &&  pTLepOverMet < 0.05) ||

             (j==90 && baselineLeptons.size()==1 && nJets > 1 && nBJets > 0 && preselSoftLep && Met > 300. && signalJets[0]->pT() > 400 && mT < 160 && !analysisBtags.at(signalJets[0]) && mT < 50 && minDPhiMetBJet < 1.5 &&  pTLepOverMet < 0.05 && topReclM < 150 ) ||

             (j==91 && baselineLeptons.size()==1 && nJets > 1 && nBJets > 0 && preselSoftLep && Met > 300. && signalJets[0]->pT() > 400 && mT < 160 && !analysisBtags.at(signalJets[0]) && mT < 50 && minDPhiMetBJet < 1.5 &&  pTLepOverMet < 0.05 && topReclM < 150 &&  pTLepOverMet < 0.02) ||

             // bCsoft_med cutflow

             (j==92 && baselineLeptons.size()==1 && nJets > 1 && nBJets > 0 && preselSoftLep) ||

             (j==93 && baselineLeptons.size()==1 && nJets > 1 && nBJets > 0 && preselSoftLep && nJets >=3) ||

             (j==94 && baselineLeptons.size()==1 && nJets > 1 && nBJets > 0 && preselSoftLep && nJets >=3 && Wpt > 400) ||

             (j==95 && baselineLeptons.size()==1 && nJets > 1 && nBJets > 0 && preselSoftLep && nJets >=3 && Wpt > 400 && signalJets[0]->pT() > 120) ||

             (j==96 && baselineLeptons.size()==1 && nJets > 1 && nBJets > 0 && preselSoftLep && nJets >=3 && Wpt > 400 && signalJets[0]->pT() > 120 && signalJets[1]->pT() > 60) ||

             (j==97 && baselineLeptons.size()==1 && nJets > 1 && nBJets > 0 && preselSoftLep && nJets >=3 && Wpt > 400 && signalJets[0]->pT() > 120 && signalJets[1]->pT() > 60 && signalJets[2]->pT() > 40) ||
             (j==98 && baselineLeptons.size()==1 && nJets > 1 && nBJets > 0 && preselSoftLep && nJets >=3 && Wpt > 400 && signalJets[0]->pT() > 120 && signalJets[1]->pT() > 60 && signalJets[2]->pT() > 40 && mT < 160) ||

             (j==99 && baselineLeptons.size()==1 && nJets > 1 && nBJets > 0 && preselSoftLep && nJets >=3 && Wpt > 400 && signalJets[0]->pT() > 120 && signalJets[1]->pT() > 60 && signalJets[2]->pT() > 40 && mT < 160 && amT2 > 200) ||

             (j==100 && baselineLeptons.size()==1 && nJets > 1 && nBJets > 0 && preselSoftLep && nJets >=3 && Wpt > 400 && signalJets[0]->pT() > 120 && signalJets[1]->pT() > 60 && signalJets[2]->pT() > 40 && mT < 160 && amT2 > 200 && nBJets > 1) ||

             (j==101 && baselineLeptons.size()==1 && nJets > 1 && nBJets > 0 && preselSoftLep && nJets >=3 && Wpt > 400 && signalJets[0]->pT() > 120 && signalJets[1]->pT() > 60 && signalJets[2]->pT() > 40 && mT < 160 && amT2 > 200 && nBJets > 1 &&  signalBJets[0]->pT() > 120) ||

             (j==102 && baselineLeptons.size()==1 && nJets > 1 && nBJets > 0 && preselSoftLep && nJets >=3 && Wpt > 400 && signalJets[0]->pT() > 120 && signalJets[1]->pT() > 60 && signalJets[2]->pT() > 40 && mT < 160 && amT2 > 200 && nBJets > 1 &&  signalBJets[0]->pT() > 120 && signalBJets[1]->pT() > 60) ||

             (j==103 && baselineLeptons.size()==1 && nJets > 1 && nBJets > 0 && preselSoftLep && nJets >=3 && Wpt > 400 && signalJets[0]->pT() > 120 && signalJets[1]->pT() > 60 && signalJets[2]->pT() > 40 && mT < 160 && amT2 > 200 && nBJets > 1 &&  signalBJets[0]->pT() > 120 && signalBJets[1]->pT() > 60 && minDPhiMetBJet > 0.8) ||

             (j==104 && baselineLeptons.size()==1 && nJets > 1 && nBJets > 0 && preselSoftLep && nJets >=3 && Wpt > 400 && signalJets[0]->pT() > 120 && signalJets[1]->pT() > 60 && signalJets[2]->pT() > 40 && mT < 160 && amT2 > 200 && nBJets > 1 &&  signalBJets[0]->pT() > 120 && signalBJets[1]->pT() > 60 && minDPhiMetBJet > 0.8 && pTLepOverMet < 0.1) ||

             (j==105 && baselineLeptons.size()==1 && nJets > 1 && nBJets > 0 && preselSoftLep && nJets >=3 && Wpt > 400 && signalJets[0]->pT() > 120 && signalJets[1]->pT() > 60 && signalJets[2]->pT() > 40 && mT < 160 && amT2 > 200 && nBJets > 1 &&  signalBJets[0]->pT() > 120 && signalBJets[1]->pT() > 60 && minDPhiMetBJet > 0.8 && pTLepOverMet < 0.1 && pTLepOverMet < 0.03) ||

             // bCsoft_high cutflow

             (j==106 && baselineLeptons.size()>0 && baselineLeptons.size()==1 && nJets >=2 && Met > 230.) ||

             (j==107 && baselineLeptons.size()>0 && baselineLeptons.size()==1 && nJets >=2 && Met > 230. && absDPhiJMet0 > 0.4) ||

             (j==108 && baselineLeptons.size()>0 && baselineLeptons.size()==1 && nJets >=2 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4) ||
             (j==109 && baselineLeptons.size()>0 && baselineLeptons.size()==1 && nJets >=2 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && signalJets[0]->pT() > 100) ||

             (j==110 && baselineLeptons.size()>0 && baselineLeptons.size()==1 && nJets >=2 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && signalJets[0]->pT() > 100 && signalJets[1]->pT() > 100) ||

             (j==111 && baselineLeptons.size()>0 && baselineLeptons.size()==1 && nJets >=2 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && signalJets[0]->pT() > 100 && signalJets[1]->pT() > 100 && mT < 160) ||

             (j==112 && baselineLeptons.size()>0 && baselineLeptons.size()==1 && nJets >=2 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && signalJets[0]->pT() > 100 && signalJets[1]->pT() > 100 && mT < 160 && Wpt > 500) ||

             (j==113 && baselineLeptons.size()>0 && baselineLeptons.size()==1 && nJets >=2 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && signalJets[0]->pT() > 100 && signalJets[1]->pT() > 100 && mT < 160 && Wpt > 500 && dRbb > 0.8) ||

             (j==114 && baselineLeptons.size()>0 && baselineLeptons.size()==1 && nJets >=2 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && signalJets[0]->pT() > 100 && signalJets[1]->pT() > 100 && mT < 160 && Wpt > 500 && dRbb > 0.8 && minDPhiMetBJet > 0.4) ||

             (j==115 && baselineLeptons.size()>0 && baselineLeptons.size()==1 && nJets >=2 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && signalJets[0]->pT() > 100 && signalJets[1]->pT() > 100 && mT < 160 && Wpt > 500 && dRbb > 0.8 && minDPhiMetBJet > 0.4 && nBJets>=2 ) ||

             (j==116 && baselineLeptons.size()>0 && baselineLeptons.size()==1 && nJets >=2 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && signalJets[0]->pT() > 100 && signalJets[1]->pT() > 100 && mT < 160 && Wpt > 500 && dRbb > 0.8 && minDPhiMetBJet > 0.4 && nBJets>=2 && signalBJets[0]->pT() > 100) ||

             (j==117 && baselineLeptons.size()>0 && baselineLeptons.size()==1 && nJets >=2 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && signalJets[0]->pT() > 100 && signalJets[1]->pT() > 100 && mT < 160 && Wpt > 500 && dRbb > 0.8 && minDPhiMetBJet > 0.4 && nBJets>=2 && signalBJets[0]->pT() > 100 && signalBJets[1]->pT() > 100) ||

             (j==118 && baselineLeptons.size()>0 && baselineLeptons.size()==1 && nJets >=2 && Met > 230. && absDPhiJMet0 > 0.4 && absDPhiJMet1 > 0.4 && signalJets[0]->pT() > 100 && signalJets[1]->pT() > 100 && mT < 160 && Wpt > 500 && dRbb > 0.8 && minDPhiMetBJet > 0.4 && nBJets>=2 && signalBJets[0]->pT() > 100 && signalBJets[1]->pT() > 100 && amT2 > 300)
             )
          {
            cutFlowVector[j]++;
          }

        }

        if(is_tN_med) _counters.at("tN_med").add_event(event);
        if(is_tN_high) _counters.at("tN_high").add_event(event);
        if(is_bWN) _counters.at("bWN").add_event(event);
        if(is_bC2x_diag) _counters.at("bC2x_diag").add_event(event);
        if(is_bC2x_med) _counters.at("bC2x_med").add_event(event);
        if(is_bCbv) _counters.at("bCbv").add_event(event);
        if(is_DM_low) _counters.at("DM_low_loose").add_event(event);
        if(is_DM_low) _counters.at("DM_low").add_event(event);
        if(is_DM_high) _counters.at("DM_high").add_event(event);

        if(is_bffN) _counters.at("bffN").add_event(event);
        if(is_bCsoft_diag) _counters.at("bCsoft_diag").add_event(event);
        if(is_bCsoft_med) _counters.at("bCsoft_med").add_event(event);
        if(is_bCsoft_high) _counters.at("bCsoft_high").add_event(event);

        return;

      }

      /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
      void combine(const Analysis* other)
      {
        const Analysis_ATLAS_13TeV_1LEPStop_36invfb* specificOther
                = dynamic_cast<const Analysis_ATLAS_13TeV_1LEPStop_36invfb*>(other);

        for (auto& pair : _counters) { pair.second += specificOther->_counters.at(pair.first); }

        if (NCUTS != specificOther->NCUTS) NCUTS = specificOther->NCUTS;
        for (int j=0; j<NCUTS; j++)
        {
          cutFlowVector[j] += specificOther->cutFlowVector[j];
          cutFlowVector_str[j] = specificOther->cutFlowVector_str[j];
        }
      }


      void collect_results()
      {

        // // For debugging:
        // double scale_by=1.;
        // cout << "------------------------------------------------------------------------------------------------------------------------------ "<<endl;
        // cout << "CUT FLOW: ATLAS 13 TeV 1 lep stop paper "<<endl;
        // cout << "------------------------------------------------------------------------------------------------------------------------------"<<endl;
        // cout<< right << setw(40) << "CUT" << setw(20) << "RAW" << setw(20) << "SCALED"
        //     << setw(20) << "%" << setw(20) << "clean adj RAW"<< setw(20) << "clean adj %" << endl;
        // for (int j=0; j<NCUTS; j++)
        // {
        //   cout << right << setw(40) << cutFlowVector_str[j].c_str() << setw(20)
        //        << cutFlowVector[j] << setw(20) << cutFlowVector[j]*scale_by << setw(20)
        //        << 100.*cutFlowVector[j]/cutFlowVector[0] << "%" << setw(20)
        //        << cutFlowVector[j]*scale_by << setw(20) << 100.*cutFlowVector[j]/cutFlowVector[0]<< "%" << endl;
        // }
        // cout << "------------------------------------------------------------------------------------------------------------------------------ "<<endl;

        /// Register results objects with the results for each SR; obs & bkg numbers from the paper

        add_result(SignalRegionData(_counters.at("tN_med"), 50., { 36.3, 6.6}));
        add_result(SignalRegionData(_counters.at("tN_high"), 8., { 3.8, 1.0}));
        add_result(SignalRegionData(_counters.at("bWN"), 68., { 71, 16}));
        add_result(SignalRegionData(_counters.at("bC2x_diag"), 22., { 21.3, 5.0}));
        add_result(SignalRegionData(_counters.at("bC2x_med"), 4., { 5.8, 1.6}));
        add_result(SignalRegionData(_counters.at("bCbv"), 25., { 25.1, 3.8}));
        add_result(SignalRegionData(_counters.at("DM_low_loose"), 65., { 48.3, 8.2}));
        add_result(SignalRegionData(_counters.at("DM_low"), 13., { 13.8, 3.6}));
        add_result(SignalRegionData(_counters.at("DM_high"), 5., { 7.4, 2.1}));
        add_result(SignalRegionData(_counters.at("bffN"), 70., { 60.5, 6.1}));
        add_result(SignalRegionData(_counters.at("bCsoft_diag"), 33., { 24.7, 3.1}));
        add_result(SignalRegionData(_counters.at("bCsoft_med"), 19., { 13.7, 2.1}));
        add_result(SignalRegionData(_counters.at("bCsoft_high"), 2., { 1.8, 0.3}));

        return;
      }


    protected:
      void analysis_specific_reset()
      {
        for (auto& pair : _counters) { pair.second.reset(); }

        std::fill(cutFlowVector.begin(), cutFlowVector.end(), 0);
      }

    };

    DEFINE_ANALYSIS_FACTORY(ATLAS_13TeV_1LEPStop_36invfb)

  }
}

#endif