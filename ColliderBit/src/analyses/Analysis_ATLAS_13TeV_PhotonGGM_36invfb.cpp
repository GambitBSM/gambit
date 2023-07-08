#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"
#include "gambit/ColliderBit/mt2_bisect.h"

// #define CHECK_CUTFLOW


using namespace std;

/// @brief Simulation of "Search for photonic signatures of gauge-mediated supersymmetry in 13 TeV pp collisions with the ATLAS detector"
///
/// Based on:
///  - https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/PAPERS/SUSY-2016-27/
///
/// @author Martin White
///
/// Known issues:
///
/// 1) Photon isolation requirement is missing
/// 2) They use a bizarre HT definition where they don't apply overlap removal
///    between photons and jets. This might not work for us, since jets won't be
///    made by photons in our events.
///
///

namespace Gambit
{
  namespace ColliderBit
  {

    bool sortByPT_jet(const HEPUtils::Jet* jet1, const HEPUtils::Jet* jet2) { return (jet1->pT() > jet2->pT()); }
    bool sortByPT_lep(const HEPUtils::Particle* lep1, const HEPUtils::Particle* lep2) { return (lep1->pT() > lep2->pT()); }


    class Analysis_ATLAS_13TeV_PhotonGGM_36invfb : public Analysis
    {
      protected:

        // Numbers passing cuts
        std::map<string, EventCounter> _counters = {
          {"SRaa_SL", EventCounter("SRaa_SL")},
          {"SRaa_SH", EventCounter("SRaa_SH")},
          {"SRaa_WL", EventCounter("SRaa_WL")},
          {"SRaa_WH", EventCounter("SRaa_WH")},
          {"SRaj_L", EventCounter("SRaj_L")},
          {"SRaj_L200", EventCounter("SRaj_L200")},
          {"SRaj_H", EventCounter("SRaj_H")},
        };


        // Cut Flow
        #ifdef CHECK_CUTFLOW
          vector<int> cutFlowVector;
          vector<double> cutFlowVector_ATLAS;
          vector<string> cutFlowVector_str;
          int NCUTS;
        #endif


        // Overlap removal -- discard from first list if deltaR < deltaR1 and
        // discard from the second list deltaR1 < deltaR < deltaR2
        /*
        void JetParticleOverlapRemoval2(vector<const HEPUtils::Jet*> &jetvec, vector<const HEPUtils::Particle*> &particlevec, double deltaR1, double deltaR2, bool use_rapidity=false)
        {

          vector<const HEPUtils::Jet*> keep_jets;
          vector<const HEPUtils::Jet*> kill_jets;

          vector<const HEPUtils::Particle*> keep_particles;
          vector<const HEPUtils::Particle*> kill_particles;

          for(const HEPUtils::Jet* j : jetvec)
          {

            for(const HEPUtils::Particle* p : particlevec)
            {

                const double dR = (use_rapidity) ? j->mom().deltaR_rap(p->mom()) : j->mom().deltaR_eta(p->mom());

                if (fabs(dR) <= deltaR1)
                {
                  // If jet j is not in kill_jets, add it.
                  if ( find(kill_jets.begin(), kill_jets.end(), j) ==  kill_jets.end() ) kill_jets.push_back(j);
                }
                else if ((fabs(dR) > deltaR1) && (fabs(dR) <= deltaR2))
                {
                  // If particle p is not in kill_particles, add it.
                  if ( find(kill_particles.begin(), kill_particles.end(), p) ==  kill_particles.end() ) kill_particles.push_back(p);
                }
            }
          }

          // All jets that are not in kill_jets should go into keep_jets
          for(const HEPUtils::Jet* j : jetvec)
          {
            if ( find(kill_jets.begin(), kill_jets.end(), j) ==  kill_jets.end() ) keep_jets.push_back(j);
          }

          // All particles that are not in kill_particles should go into keep_particles
          for(const HEPUtils::Particle* p : particlevec)
          {
            if ( find(kill_particles.begin(), kill_particles.end(), p) ==  kill_particles.end() ) keep_particles.push_back(p);
          }

          jetvec = keep_jets;
          particlevec = keep_particles;

          return;
        }
        */

      public:

        // Required detector sim
        static constexpr const char* detector = "ATLAS";

        Analysis_ATLAS_13TeV_PhotonGGM_36invfb()
        {

          set_analysis_name("ATLAS_13TeV_PhotonGGM_36invfb");
          set_luminosity(36.1);

          #ifdef CHECK_CUTFLOW
            NCUTS= 51;
            for(int i=0;i<NCUTS;i++)
            {
                cutFlowVector.push_back(0);
                cutFlowVector_ATLAS.push_back(-1.0);
                cutFlowVector_str.push_back("");
            }
          #endif

        }

        void run(const HEPUtils::Event* event)
        {

          // Missing energy w/ smearing
          double ht = 0;
          for (const HEPUtils::Particle* p : event->visible_particles()) ht += p->pT();
          HEPUtils::P4 pmiss = event->missingmom();
          ATLAS::smearMET(pmiss, ht);
          const double met = pmiss.pT();

          // Baseline lepton objects
          vector<const HEPUtils::Particle*> baselineElectrons, baselineMuons;

          // Baseline electrons
          for (const HEPUtils::Particle* electron : event->electrons())
          {
            bool crack = (electron->abseta() > 1.37) && (electron->abseta() < 1.52);
            if (electron->pT() > 25. && electron->abseta() < 2.47 && !crack) baselineElectrons.push_back(electron);
          }

          // Apply electron efficiency
          ATLAS::applyElectronEff(baselineElectrons);

          // Apply tight electron selection
          ATLAS::applyTightIDElectronSelection(baselineElectrons);

          for (const HEPUtils::Particle* muon : event->muons())
          {
            if (muon->pT() > 25. && muon->abseta() < 2.7) baselineMuons.push_back(muon);
          }

          // Apply muon efficiency
          ATLAS::applyMuonEff(baselineMuons);

          // Photons
          vector<const HEPUtils::Particle*> baselinePhotons;
          for (const HEPUtils::Particle* photon : event->photons())
          {
            bool crack = (photon->abseta() > 1.37) && (photon->abseta() < 1.52);
            if (photon->pT() > 25. && photon->abseta() < 2.37 && !crack) baselinePhotons.push_back(photon);
          }
          ATLAS::applyPhotonEfficiencyR2(baselinePhotons);

          // Jets
          vector<const HEPUtils::Jet*> jets28;
          vector<const HEPUtils::Jet*> jets28_nophooverlap;
          for (const HEPUtils::Jet* jet : event->jets())
          {
            if (jet->pT() > 30. && fabs(jet->eta()) < 2.8)
            {
              jets28.push_back(jet);
              jets28_nophooverlap.push_back(jet);
            }
          }


          // Overlap removal
          const bool use_rapidity=true;
          removeOverlap(baselinePhotons,baselineElectrons, 0.01, use_rapidity); // <-- taken from ATLAS code snippets on HEPData

          removeOverlap(jets28, baselineElectrons, 0.2, use_rapidity);
          removeOverlap(jets28_nophooverlap, baselineElectrons, 0.2, use_rapidity);
          removeOverlap(jets28, baselinePhotons, 0.2, use_rapidity);
          removeOverlap(baselineElectrons, jets28_nophooverlap, 0.4, use_rapidity);
          removeOverlap(baselineElectrons, jets28, 0.4, use_rapidity);
          removeOverlap(baselinePhotons, jets28, 0.4, use_rapidity);
          removeOverlap(baselineMuons, jets28, 0.4, use_rapidity);
          removeOverlap(baselineMuons, jets28_nophooverlap, 0.4, use_rapidity);


          // Make |eta| < 2.5 jets
          vector<const HEPUtils::Jet*> jets25;
          for (const HEPUtils::Jet* jet : jets28)
          {
            if (fabs(jet->eta()) < 2.5) jets25.push_back(jet);
          }

          // Put objects in pT order
          sortByPt(jets25);
          sortByPt(jets28);
          sortByPt(jets28_nophooverlap);
          sortByPt(baselineElectrons);
          sortByPt(baselineMuons);
          sortByPt(baselinePhotons);


          // Function used to get b jets
          vector<const HEPUtils::Jet*> bJets25;
          vector<const HEPUtils::Jet*> bJets28;

          const std::vector<double>  a = {0,10.};
          const std::vector<double>  b = {0,10000.};
          const std::vector<double> c = {0.77};
          HEPUtils::BinnedFn2D<double> _eff2d(a,b,c);
          for (const HEPUtils::Jet* jet : jets25)
          {
            bool hasTag=has_tag(_eff2d, jet->abseta(), jet->pT());
            if(jet->btag() && hasTag) bJets25.push_back(jet);
          }

          for (const HEPUtils::Jet* jet : jets28)
          {
            bool hasTag=has_tag(_eff2d, jet->abseta(), jet->pT());
            if(jet->btag() && hasTag) bJets28.push_back(jet);
          }

          // Multiplicities
          int nLep = baselineElectrons.size() + baselineMuons.size();
          int nJets25 = jets25.size();
          int nPhotons = baselinePhotons.size();


          // Pre-selection
          bool preSelection2a=false;
          if(nPhotons==2 && baselinePhotons[0]->pT() > 75. && baselinePhotons[1]->pT() > 75.) preSelection2a=true;

          bool preSelectionSRLaj = false;
          if(nPhotons==1 && baselinePhotons[0]->pT() > 145.) preSelectionSRLaj=true;

          bool preSelectionSRHaj = false;
          if(nPhotons==1 && baselinePhotons[0]->pT() > 400.) preSelectionSRHaj=true;

          // Useful variables
          // "Photon-enhanced" HT, with no overlap removal of photons-jets
          double HT = 0.;
          for(const HEPUtils::Particle* photon : baselinePhotons)
          {
            HT += photon->pT();
          }
          for(const HEPUtils::Particle* electron : baselineElectrons)
          {
            HT += electron->pT();
          }
          for(const HEPUtils::Particle* muon : baselineMuons)
          {
            HT += muon->pT();
          }
          for(const HEPUtils::Jet* jet : jets28_nophooverlap)
          {
            HT += jet->pT();
          }

          // meff
          double meff = met;
          for(const HEPUtils::Particle* photon : baselinePhotons)
          {
            meff += photon->pT();
          }
          for(const HEPUtils::Particle* electron : baselineElectrons)
          {
            meff += electron->pT();
          }
          for(const HEPUtils::Particle* muon : baselineMuons)
          {
            meff += muon->pT();
          }

          // Note that meff is only used for aj signal regions -> |jet eta| < 2.5
          for(const HEPUtils::Jet* jet : jets25)
          {
            meff += jet->pT();
          }

          // dphimin(a,met)
          double dphimin_amet = 999.;
          if (nPhotons == 1)
          {
            dphimin_amet = pmiss.deltaPhi(baselinePhotons.at(0)->mom());
          }
          else if (nPhotons >= 2)
          {
            dphimin_amet = std::min( pmiss.deltaPhi(baselinePhotons.at(0)->mom()), pmiss.deltaPhi(baselinePhotons.at(1)->mom()) );
          }


          double dphimin_j25met = 999.;
          if (jets25.size() == 1)
          {
            dphimin_j25met = pmiss.deltaPhi(jets25.at(0)->mom());
          }
          else if (jets25.size() >= 2)
          {
            dphimin_j25met = std::min( pmiss.deltaPhi(jets25.at(0)->mom()), pmiss.deltaPhi(jets25.at(1)->mom()) );
          }


          double dphimin_j28met = 999.;
          if (jets28.size() == 1)
          {
            dphimin_j28met = pmiss.deltaPhi(jets28.at(0)->mom());
          }
          else if (jets28.size() >= 2)
          {
            dphimin_j28met = std::min( pmiss.deltaPhi(jets28.at(0)->mom()), pmiss.deltaPhi(jets28.at(1)->mom()) );
          }


          // RT4
          // Only used in aj regions -> use |jet eta| < 2.5
          double RT4 = 1.;
          if(jets25.size() > 3)
          {
            RT4 = jets25[0]->pT() + jets25[1]->pT() + jets25[2]->pT() + jets25[3]->pT();
            double denom=0.;
            for(const HEPUtils::Jet* jet : jets25)
            {
              denom += jet->pT();
            }
            RT4 = RT4 / denom;
          }


          // All variables are now done
          // Increment signal region variables
          // 2a regions
          if(preSelection2a && met > 150. && HT > 2750 && dphimin_j28met > 0.5) _counters.at("SRaa_SL").add_event(event);
          if(preSelection2a && met > 250. && HT > 2000 && dphimin_j28met > 0.5 && dphimin_amet > 0.5) _counters.at("SRaa_SH").add_event(event);
          if(preSelection2a && met > 150. && HT > 1500 && dphimin_j28met > 0.5) _counters.at("SRaa_WL").add_event(event);
          if(preSelection2a && met > 250. && HT > 1000 && dphimin_j28met > 0.5 && dphimin_amet > 0.5) _counters.at("SRaa_WH").add_event(event);

          // aj regions
          if(preSelectionSRLaj && nJets25 >=5 && nLep == 0 && met > 300. && meff > 2000. && RT4 < 0.90 && dphimin_j25met > 0.5 && dphimin_amet > 0.5) _counters.at("SRaj_L").add_event(event);
          if(preSelectionSRLaj && nJets25 >=5 && nLep == 0 && met > 200. && meff > 2000. && RT4 < 0.90 && dphimin_j25met > 0.5 && dphimin_amet > 0.5) _counters.at("SRaj_L200").add_event(event);
          if(preSelectionSRHaj && nJets25 >=3 && nLep == 0 && met > 400. && meff > 2400. && dphimin_j25met > 0.5 && dphimin_amet > 0.5) _counters.at("SRaj_H").add_event(event);


          #ifdef CHECK_CUTFLOW

            /*                                                       */
            /*********************************************************/
            cutFlowVector_str[0] = "Total ";
            /*---------------------------------------*/
            cutFlowVector_str[1] = "SBL: trigger && 2 photons";
            cutFlowVector_str[2] = "SBL: PhotonsPt";
            cutFlowVector_str[3] = "SBL: MET";
            cutFlowVector_str[4] = "SBL: HT";
            cutFlowVector_str[5] = "SBL: dPhiMin(jet,met)";
            cutFlowVector_str[6] = "SBL: dPhiMin(gamma,met)";

            cutFlowVector_str[7] = "SBH: trigger && 2 photons";
            cutFlowVector_str[8] = "SBH: PhotonsPt";
            cutFlowVector_str[9] = "SBH: MET";
            cutFlowVector_str[10] = "SBH: HT";
            cutFlowVector_str[11] = "SBH: dPhiMin(jet,met)";
            cutFlowVector_str[12] = "SBH: dPhiMin(gamma,met)";

            cutFlowVector_str[13] = "WBL: trigger && 2 photons";
            cutFlowVector_ATLAS[13] = 26.6;
            cutFlowVector_str[14] = "WBL: PhotonsPt";
            cutFlowVector_ATLAS[14] = 21.3;
            cutFlowVector_str[15] = "WBL: MET";
            cutFlowVector_ATLAS[15] = 16.9;
            cutFlowVector_str[16] = "WBL: HT";
            cutFlowVector_ATLAS[16] = 14.7;
            cutFlowVector_str[17] = "WBL: dPhiMin(jet,met)";
            cutFlowVector_ATLAS[17] = 11.0;
            cutFlowVector_str[18] = "WBL: dPhiMin(gamma,met)";
            cutFlowVector_ATLAS[18] = 11.0;

            cutFlowVector_str[19] = "WBH: trigger && 2 photons";
            cutFlowVector_ATLAS[19] = 19.6;
            cutFlowVector_str[20] = "WBH: PhotonsPt";
            cutFlowVector_ATLAS[20] = 19.2;
            cutFlowVector_str[21] = "WBH: MET";
            cutFlowVector_ATLAS[21] = 15.6;
            cutFlowVector_str[22] = "WBH: HT";
            cutFlowVector_ATLAS[22] = 15.6;
            cutFlowVector_str[23] = "WBH: dPhiMin(jet,met)";
            cutFlowVector_ATLAS[23] = 14.8;
            cutFlowVector_str[24] = "WBH: dPhiMin(gamma,met)";
            cutFlowVector_ATLAS[24] = 14.6;

            cutFlowVector_str[25] = "SRL: trigger && 1 photon";
            cutFlowVector_str[26] = "SRL: lepton veto";
            cutFlowVector_str[27] = "SRL: pT_gamma";
            cutFlowVector_str[28] = "SRL: met";
            cutFlowVector_str[29] = "SRL: Njets";
            cutFlowVector_str[30] = "SRL: dphimin(jet,met)";
            cutFlowVector_str[31] = "SRL: dphimin(gamma,met)";
            cutFlowVector_str[32] = "SRL: meff";
            cutFlowVector_str[33] = "SRL: RT4";

            cutFlowVector_str[34] = "SRL200: trigger && 1 photon";
            cutFlowVector_str[35] = "SRL200: lepton veto";
            cutFlowVector_str[36] = "SRL200: pT_gamma";
            cutFlowVector_str[37] = "SRL200: met";
            cutFlowVector_str[38] = "SRL200: Njets";
            cutFlowVector_str[39] = "SRL200: dphimin(jet,met)";
            cutFlowVector_str[40] = "SRL200: dphimin(gamma,met)";
            cutFlowVector_str[41] = "SRL200: meff";
            cutFlowVector_str[42] = "SRL200: RT4";

            cutFlowVector_str[43] = "SRH: trigger && 1 photon";
            cutFlowVector_str[44] = "SRH: lepton veto";
            cutFlowVector_str[45] = "SRH: pT_gamma";
            cutFlowVector_str[46] = "SRH: met";
            cutFlowVector_str[47] = "SRH: Njets";
            cutFlowVector_str[48] = "SRH: dphimin(jet,met)";
            cutFlowVector_str[49] = "SRH: dphimin(gamma,met)";
            cutFlowVector_str[50] = "SRH: meff";

            for(int j=0;j<NCUTS;j++)
            {
              if(
                (j==0) ||

                /*
                  cutFlowVector_str[1] = "SBL: trigger && 2 photons";
                  cutFlowVector_str[2] = "SBL: PhotonsPt";
                  cutFlowVector_str[3] = "SBL: MET";
                  cutFlowVector_str[4] = "SBL: HT";
                  cutFlowVector_str[5] = "SBL: dPhiMin(jet,met)";
                  cutFlowVector_str[6] = "SBL: dPhiMin(gamma,met)";
                */

                (j==1 && nPhotons==2 && baselinePhotons[0]->pT() > 35. && baselinePhotons[1]->pT() > 25.) ||
                (j==2 && nPhotons==2 && baselinePhotons[0]->pT() > 75. && baselinePhotons[1]->pT() > 75.) ||
                (j==3 && nPhotons==2 && baselinePhotons[0]->pT() > 75. && baselinePhotons[1]->pT() > 75. && met > 150.) ||
                (j==4 && nPhotons==2 && baselinePhotons[0]->pT() > 75. && baselinePhotons[1]->pT() > 75. && met > 150. && HT > 2750.) ||
                (j==5 && nPhotons==2 && baselinePhotons[0]->pT() > 75. && baselinePhotons[1]->pT() > 75. && met > 150. && HT > 2750. && dphimin_j28met > 0.5) ||
                (j==6 && nPhotons==2 && baselinePhotons[0]->pT() > 75. && baselinePhotons[1]->pT() > 75. && met > 150. && HT > 2750. && dphimin_j28met > 0.5) || // No extra cut in this case


                /*
                  cutFlowVector_str[7] = "SBH: trigger && 2 photons";
                  cutFlowVector_str[8] = "SBH: PhotonsPt";
                  cutFlowVector_str[9] = "SBH: MET";
                  cutFlowVector_str[10] = "SBH: HT";
                  cutFlowVector_str[11] = "SBH: dPhiMin(jet,met)";
                  cutFlowVector_str[12] = "SBH: dPhiMin(gamma,met)";
                */

                (j==7 && nPhotons==2 && baselinePhotons[0]->pT() > 35. && baselinePhotons[1]->pT() > 25.) ||
                (j==8 && nPhotons==2 && baselinePhotons[0]->pT() > 75. && baselinePhotons[1]->pT() > 75.) ||
                (j==9 && nPhotons==2 && baselinePhotons[0]->pT() > 75. && baselinePhotons[1]->pT() > 75. && met > 250.) ||
                (j==10 && nPhotons==2 && baselinePhotons[0]->pT() > 75. && baselinePhotons[1]->pT() > 75. && met > 250. && HT > 2000.) ||
                (j==11 && nPhotons==2 && baselinePhotons[0]->pT() > 75. && baselinePhotons[1]->pT() > 75. && met > 250. && HT > 2000. && dphimin_j28met > 0.5) ||
                (j==12 && nPhotons==2 && baselinePhotons[0]->pT() > 75. && baselinePhotons[1]->pT() > 75. && met > 250. && HT > 2000. && dphimin_j28met > 0.5 && dphimin_amet > 0.5) ||


                /*
                  cutFlowVector_str[13] = "WBL: trigger && 2 photons";
                  cutFlowVector_str[14] = "WBL: PhotonsPt";
                  cutFlowVector_str[15] = "WBL: MET";
                  cutFlowVector_str[16] = "WBL: HT";
                  cutFlowVector_str[17] = "WBL: dPhiMin(jet,met)";
                  cutFlowVector_str[18] = "WBL: dPhiMin(gamma,met)";
                */

                (j==13 && nPhotons==2 && baselinePhotons[0]->pT() > 35. && baselinePhotons[1]->pT() > 25.) ||
                (j==14 && nPhotons==2 && baselinePhotons[0]->pT() > 75. && baselinePhotons[1]->pT() > 75.) ||
                (j==15 && nPhotons==2 && baselinePhotons[0]->pT() > 75. && baselinePhotons[1]->pT() > 75. && met > 150.) ||
                (j==16 && nPhotons==2 && baselinePhotons[0]->pT() > 75. && baselinePhotons[1]->pT() > 75. && met > 150. && HT > 1500.) ||
                (j==17 && nPhotons==2 && baselinePhotons[0]->pT() > 75. && baselinePhotons[1]->pT() > 75. && met > 150. && HT > 1500. && dphimin_j28met > 0.5) ||
                (j==18 && nPhotons==2 && baselinePhotons[0]->pT() > 75. && baselinePhotons[1]->pT() > 75. && met > 150. && HT > 1500. && dphimin_j28met > 0.5) || // no additional cut in this case


                /*
                  cutFlowVector_str[19] = "WBH: trigger && 2 photons";
                  cutFlowVector_str[20] = "WBH: PhotonsPt";
                  cutFlowVector_str[21] = "WBH: MET";
                  cutFlowVector_str[22] = "WBH: HT";
                  cutFlowVector_str[23] = "WBH: dPhiMin(jet,met)";
                  cutFlowVector_str[24] = "WBH: dPhiMin(gamma,met)";
                */

                (j==19 && nPhotons==2 && baselinePhotons[0]->pT() > 35. && baselinePhotons[1]->pT() > 25.) ||
                (j==20 && nPhotons==2 && baselinePhotons[0]->pT() > 75. && baselinePhotons[1]->pT() > 75.) ||
                (j==21 && nPhotons==2 && baselinePhotons[0]->pT() > 75. && baselinePhotons[1]->pT() > 75. && met > 250.) ||
                (j==22 && nPhotons==2 && baselinePhotons[0]->pT() > 75. && baselinePhotons[1]->pT() > 75. && met > 250. && HT > 1000.) ||
                (j==23 && nPhotons==2 && baselinePhotons[0]->pT() > 75. && baselinePhotons[1]->pT() > 75. && met > 250. && HT > 1000. && dphimin_j28met > 0.5) ||
                (j==24 && nPhotons==2 && baselinePhotons[0]->pT() > 75. && baselinePhotons[1]->pT() > 75. && met > 250. && HT > 1000. && dphimin_j28met > 0.5 && dphimin_amet > 0.5) || // no additional cut in this case


    // --------


                /*
                  cutFlowVector_str[25] = "SRL: trigger && 1 photon";
                  cutFlowVector_str[26] = "SRL: lepton veto";
                  cutFlowVector_str[27] = "SRL: pT_gamma";
                  cutFlowVector_str[28] = "SRL: met";
                  cutFlowVector_str[29] = "SRL: Njets";
                  cutFlowVector_str[30] = "SRL: dphimin(jet,met)";
                  cutFlowVector_str[31] = "SRL: dphimin(gamma,met)";
                  cutFlowVector_str[32] = "SRL: meff";
                  cutFlowVector_str[33] = "SRL: RT4";
                */

                (j==25 && nPhotons==1 && baselinePhotons[0]->pT() > 140.) ||
                (j==26 && nPhotons==1 && nLep==0 && baselinePhotons[0]->pT() > 140.) ||
                (j==27 && nPhotons==1 && nLep==0 && baselinePhotons[0]->pT() > 145.) ||
                (j==28 && nPhotons==1 && nLep==0 && baselinePhotons[0]->pT() > 145. && met > 300.) ||
                (j==29 && nPhotons==1 && nLep==0 && baselinePhotons[0]->pT() > 145. && met > 300. && nJets25 >= 5) ||
                (j==30 && nPhotons==1 && nLep==0 && baselinePhotons[0]->pT() > 145. && met > 300. && nJets25 >= 5 && dphimin_j25met > 0.4) ||
                (j==31 && nPhotons==1 && nLep==0 && baselinePhotons[0]->pT() > 145. && met > 300. && nJets25 >= 5 && dphimin_j25met > 0.4 && dphimin_amet > 0.4) ||
                (j==32 && nPhotons==1 && nLep==0 && baselinePhotons[0]->pT() > 145. && met > 300. && nJets25 >= 5 && dphimin_j25met > 0.4 && dphimin_amet > 0.4 && meff > 2000.) ||
                (j==33 && nPhotons==1 && nLep==0 && baselinePhotons[0]->pT() > 145. && met > 300. && nJets25 >= 5 && dphimin_j25met > 0.4 && dphimin_amet > 0.4 && meff > 2000. && RT4 < 0.90) ||


                /*
                  cutFlowVector_str[25] = "SRL200: trigger && 1 photon";
                  cutFlowVector_str[26] = "SRL200: lepton veto";
                  cutFlowVector_str[27] = "SRL200: pT_gamma";
                  cutFlowVector_str[28] = "SRL200: met";
                  cutFlowVector_str[29] = "SRL200: Njets";
                  cutFlowVector_str[30] = "SRL200: dphimin(jet,met)";
                  cutFlowVector_str[31] = "SRL200: dphimin(gamma,met)";
                  cutFlowVector_str[32] = "SRL200: meff";
                  cutFlowVector_str[33] = "SRL200: RT4";
                */

                (j==34 && nPhotons==1 && baselinePhotons[0]->pT() > 140.) ||
                (j==35 && nPhotons==1 && nLep==0 && baselinePhotons[0]->pT() > 140.) ||
                (j==36 && nPhotons==1 && nLep==0 && baselinePhotons[0]->pT() > 145.) ||
                (j==37 && nPhotons==1 && nLep==0 && baselinePhotons[0]->pT() > 145. && met > 200.) ||
                (j==38 && nPhotons==1 && nLep==0 && baselinePhotons[0]->pT() > 145. && met > 200. && nJets25 >= 5) ||
                (j==39 && nPhotons==1 && nLep==0 && baselinePhotons[0]->pT() > 145. && met > 200. && nJets25 >= 5 && dphimin_j25met > 0.4) ||
                (j==40 && nPhotons==1 && nLep==0 && baselinePhotons[0]->pT() > 145. && met > 200. && nJets25 >= 5 && dphimin_j25met > 0.4 && dphimin_amet > 0.4) ||
                (j==41 && nPhotons==1 && nLep==0 && baselinePhotons[0]->pT() > 145. && met > 200. && nJets25 >= 5 && dphimin_j25met > 0.4 && dphimin_amet > 0.4 && meff > 2000.) ||
                (j==42 && nPhotons==1 && nLep==0 && baselinePhotons[0]->pT() > 145. && met > 200. && nJets25 >= 5 && dphimin_j25met > 0.4 && dphimin_amet > 0.4 && meff > 2000. && RT4 < 0.90) ||


                /*
                  cutFlowVector_str[34] = "SRH: trigger && 1 photon";
                  cutFlowVector_str[35] = "SRH: lepton veto";
                  cutFlowVector_str[36] = "SRH: pT_gamma";
                  cutFlowVector_str[37] = "SRH: met";
                  cutFlowVector_str[38] = "SRH: Njets";
                  cutFlowVector_str[39] = "SRH: dphimin(jet,met)";
                  cutFlowVector_str[40] = "SRH: dphimin(gamma,met)";
                  cutFlowVector_str[41] = "SRH: meff";
                */

                (j==43 && nPhotons==1 && baselinePhotons[0]->pT() > 140.) ||
                (j==44 && nPhotons==1 && nLep==0 && baselinePhotons[0]->pT() > 140.) ||
                (j==45 && nPhotons==1 && nLep==0 && baselinePhotons[0]->pT() > 400.) ||
                (j==46 && nPhotons==1 && nLep==0 && baselinePhotons[0]->pT() > 400. && met > 400.) ||
                (j==47 && nPhotons==1 && nLep==0 && baselinePhotons[0]->pT() > 400. && met > 400. && nJets25 >= 3) ||
                (j==48 && nPhotons==1 && nLep==0 && baselinePhotons[0]->pT() > 400. && met > 400. && nJets25 >= 3 && dphimin_j25met > 0.4) ||
                (j==49 && nPhotons==1 && nLep==0 && baselinePhotons[0]->pT() > 400. && met > 400. && nJets25 >= 3 && dphimin_j25met > 0.4 && dphimin_amet > 0.4) ||
                (j==50 && nPhotons==1 && nLep==0 && baselinePhotons[0]->pT() > 400. && met > 400. && nJets25 >= 3 && dphimin_j25met > 0.4 && dphimin_amet > 0.4 && meff > 2400.)

              )cutFlowVector[j]++;

            }

          #endif // end #ifdef CHECK_CUTFLOW

          return;

        }

        /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
        void combine(const Analysis* other)
        {
          const Analysis_ATLAS_13TeV_PhotonGGM_36invfb* specificOther
            = dynamic_cast<const Analysis_ATLAS_13TeV_PhotonGGM_36invfb*>(other);

          #ifdef CHECK_CUTFLOW
            if (NCUTS != specificOther->NCUTS) NCUTS = specificOther->NCUTS;
            for (int j=0; j<NCUTS; j++)
            {
              cutFlowVector[j] += specificOther->cutFlowVector[j];
              cutFlowVector_str[j] = specificOther->cutFlowVector_str[j];
            }
          #endif

          for (auto& pair : _counters) { pair.second += specificOther->_counters.at(pair.first); }

        }


        virtual void collect_results()
        {

          #ifdef CHECK_CUTFLOW
            double scale_by= 70.8 / 1.0e4;
            cout << "------------------------------------------------------------------------------------------------------------------------------ "<<endl;
            cout << "CUT FLOW: ATLAS_13TeV_PhotonGGM_36invfb "<<endl;
            cout << "------------------------------------------------------------------------------------------------------------------------------"<<endl;
            cout << right << setw(40) << "CUT," << setw(20) << "RAW," << setw(20) << "SCALED,"
                 << setw(20) << "%," << setw(20) << "ATLAS," << setw(20) << "GAMBIT (scaled) /ATLAS" << endl;
            for (int j=0; j<NCUTS; j++)
            {
              cout << right <<  setw(40) << cutFlowVector_str[j].c_str() <<  "," << setw(20)
                   << cutFlowVector[j] <<  "," << setw(20) << cutFlowVector[j]*scale_by <<  "," << setw(20)
                   << 100.*cutFlowVector[j]/cutFlowVector[0] << "%,"  << setw(20) << cutFlowVector_ATLAS[j] << "," << setw(20) << (cutFlowVector[j]*scale_by / cutFlowVector_ATLAS[j]) << endl;
            }
            cout << "------------------------------------------------------------------------------------------------------------------------------ "<<endl;
          #endif

            // add_result(SignalRegionData("SR label", n_obs, {n_sig_MC, n_sig_MC_sys}, {n_bkg, n_bkg_err}));

            add_result(SignalRegionData(_counters.at("SRaa_SL"), 0., { 0.50, 0.30}));
            add_result(SignalRegionData(_counters.at("SRaa_SH"), 0., { 0.48, 0.30}));
            add_result(SignalRegionData(_counters.at("SRaa_WL"), 6., { 3.7, 1.1}));
            add_result(SignalRegionData(_counters.at("SRaa_WH"), 1., { 2.05, 0.65}));
            add_result(SignalRegionData(_counters.at("SRaj_L"), 4., { 1.33, 0.54}));
            add_result(SignalRegionData(_counters.at("SRaj_L200"), 8., { 2.68, 0.64}));
            add_result(SignalRegionData(_counters.at("SRaj_H"), 3., { 1.14, 0.61}));

          return;
        }


      protected:
        void analysis_specific_reset()
        {

          for (auto& pair : _counters) { pair.second.reset(); }

          #ifdef CHECK_CUTFLOW
            std::fill(cutFlowVector.begin(), cutFlowVector.end(), 0);
          #endif
        }

    };

    // Factory function
    DEFINE_ANALYSIS_FACTORY(ATLAS_13TeV_PhotonGGM_36invfb)


    //
    // Derived analysis class for the 1Photon SRs
    //
    class Analysis_ATLAS_13TeV_PhotonGGM_1Photon_36invfb : public Analysis_ATLAS_13TeV_PhotonGGM_36invfb
    {

      public:
        Analysis_ATLAS_13TeV_PhotonGGM_1Photon_36invfb()
        {
          set_analysis_name("ATLAS_13TeV_PhotonGGM_1Photon_36invfb");
        }

        virtual void collect_results()
        {

          add_result(SignalRegionData(_counters.at("SRaj_L"), 4., { 1.33, 0.54}));
          add_result(SignalRegionData(_counters.at("SRaj_L200"), 8., { 2.68, 0.64}));
          add_result(SignalRegionData(_counters.at("SRaj_H"), 3., { 1.14, 0.61}));

        }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(ATLAS_13TeV_PhotonGGM_1Photon_36invfb)


    //
    // Derived analysis class for the 1Photon SRs
    //
    class Analysis_ATLAS_13TeV_PhotonGGM_2Photon_36invfb : public Analysis_ATLAS_13TeV_PhotonGGM_36invfb
    {

      public:
        Analysis_ATLAS_13TeV_PhotonGGM_2Photon_36invfb()
        {
          set_analysis_name("ATLAS_13TeV_PhotonGGM_2Photon_36invfb");
        }

        virtual void collect_results()
        {

          add_result(SignalRegionData(_counters.at("SRaa_SL"), 0., { 0.50, 0.30}));
          add_result(SignalRegionData(_counters.at("SRaa_SH"), 0., { 0.48, 0.30}));
          add_result(SignalRegionData(_counters.at("SRaa_WL"), 6., { 3.7, 1.1}));
          add_result(SignalRegionData(_counters.at("SRaa_WH"), 1., { 2.05, 0.65}));

        }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(ATLAS_13TeV_PhotonGGM_2Photon_36invfb)


  }
}
