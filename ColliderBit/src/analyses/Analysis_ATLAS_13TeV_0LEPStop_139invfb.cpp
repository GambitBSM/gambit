#include "gambit/cmake/cmake_variables.hpp"
#include "gambit/Utils/threadsafe_rng.hpp"
#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"
#include "gambit/ColliderBit/mt2_bisect.h"
#include "METSignificance/METSignificance.hpp"
#include "HEPUtils/FastJet.h"

using namespace std;

/* The ATLAS 0 lepton direct stop analysis

   Based on: https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/PAPERS/SUSY-2018-12/

   Code by Martin White (based on ATLAS public code snippet on HepData)

   Note: RJR regions will be coded up in a separate file

*/

namespace Gambit
{
  namespace ColliderBit
  {

    // Need two different functions here for use with std::sort
    //bool sortByPT(const HEPUtils::Jet* jet1, const HEPUtils::Jet* jet2) { return (jet1->pT() > jet2->pT()); }
    //bool sortByPT_sharedptr(std::shared_ptr<HEPUtils::Jet> jet1, std::shared_ptr<HEPUtils::Jet> jet2) { return sortByPT(jet1.get(), jet2.get()); }

    bool sortByPT0l(const HEPUtils::Jet* jet1, const HEPUtils::Jet* jet2) { return (jet1->pT() > jet2->pT()); }
    bool sortByPT0l_sharedptr(std::shared_ptr<HEPUtils::Jet> jet1, std::shared_ptr<HEPUtils::Jet> jet2) { return sortByPT0l(jet1.get(), jet2.get()); }

    class Analysis_ATLAS_13TeV_0LEPStop_139invfb : public Analysis
    {

    protected:
      std::map<string, EventCounter> _counters = {
        //{"SRA", EventCounter("SRA")},
        {"SRATT", EventCounter("SRATT")},
        {"SRATW", EventCounter("SRATW")},
        {"SRAT0", EventCounter("SRAT0")},
        {"SRBTT", EventCounter("SRBTT")},
        {"SRBTW", EventCounter("SRBTW")},
        {"SRBT0", EventCounter("SRBT0")},
        {"SRD0", EventCounter("SRD0")},
        {"SRD1", EventCounter("SRD1")},
        {"SRD2", EventCounter("SRD2")},
      };


    private:

    public:

      // Required detector sim
      static constexpr const char* detector = "ATLAS";


      void muJetSpecialOverlapRemoval(vector<const HEPUtils::Jet*> &jetvec, vector<const HEPUtils::Particle*> &lepvec)
      {

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

            double DeltaRMax = 0.;
            if(lepmom.pT()/jetmom.pT()>0.5) DeltaRMax = 0.2;
            if(fabs(dR) <= DeltaRMax) overlap=true;
          }
          if(overlap) continue;
          Survivors.push_back(jetvec.at(itjet));
        }
        jetvec=Survivors;

        return;

      }


      struct ptComparison
      {
        bool operator() (const HEPUtils::Particle* i,const HEPUtils::Particle* j) {return (i->pT()>j->pT());}
      } comparePt;

      struct ptJetComparison
      {
        bool operator() (const HEPUtils::Jet* i,const HEPUtils::Jet* j) {return (i->pT()>j->pT());}
      } compareJetPt;


      Analysis_ATLAS_13TeV_0LEPStop_139invfb()
      {

        set_analysis_name("ATLAS_13TeV_0LEPStop_139invfb");
        set_luminosity(139.);

        _cutflows.addCutflow("SRATT",
          {"MET > 250.",
           "njets >= 4",
           "nbjets >=2",
           "Lepton veto",
           "pT j4 > 40 GeV",
           "pT j2 > 80 GeV",
           "|dPhi(pT1-4, MET)| > 0.4",
           "Pass MET trigger",
           "S > 5",
           "mTbmin > 50 GeV",
           "tau veto",
           "mTbmin > 200 GeV",
           "m1(R=1.2) > 120 GeV",
           "m2(R=1.2) > 120 GeV",
           "mT2, chi^2 > 450 GeV",
           "m1(R=0.8) > 60 GeV",
           "S > 25",
           "j1(R=1.2)",
           "j2(R=1.2)",
           "deltaR(b1.b2) > 1",});

        _cutflows.addCutflow("SRATW",
          {"MET > 250.",
           "njets >= 4",
           "nbjets >=2",
           "Lepton veto",
           "pT j4 > 40 GeV",
           "pT j2 > 80 GeV",
           "|dPhi(pT1-4, MET)| > 0.4",
           "Pass MET trigger",
           "S > 5",
           "mTbmin > 50 GeV",
           "tau veto",
           "mTbmin > 200 GeV",
           "m1(R=1.2) > 120 GeV",
           "m2(R=1.2) > 60 GeV",
           "m2(R=1.2) < 120 GeV",
           "mT2, chi^2 > 450 GeV",
           "m1(R=0.8) > 60 GeV",
           "S > 25",
           "j1(R=1.2)",});


      }

      void run(const HEPUtils::Event* event)
      {

        // Missing energy
        HEPUtils::P4 metVec = event->missingmom();
        double Met = event->met();

        // Baseline electrons
        vector<const HEPUtils::Particle*> baselineElectrons;
        for (const HEPUtils::Particle* electron : event->electrons())
        {
          if (electron->pT() > 4.5 && electron->abseta() < 2.47) baselineElectrons.push_back(electron);
        }
        // Apply electron efficiency
        // Loose electron ID selection
        applyEfficiency(baselineElectrons, ATLAS::eff1DEl.at("EGAM_2018_01_Recon"));

        //applyEfficiency(baselineElectrons, ATLAS::eff1DEl.at("eff1DEl_PERF_2017_01_ID_Loose"));

        // Baseline muons have satisfy "medium" criteria and have pT > 3 GeV and |eta| < 2.7
        vector<const HEPUtils::Particle*> baselineMuons;
        for (const HEPUtils::Particle* muon : event->muons())
        {
          if (muon->pT() > 4.0 && muon->abseta() < 2.7) baselineMuons.push_back(muon);
        }

        // Apply muon efficiency
        // Missing: "Medium" muon ID criteria
        applyEfficiency(baselineMuons, ATLAS::eff2DMu.at("R2"));

        // Baseline jets
        vector<const HEPUtils::Jet*> baselineJets;
        for (const HEPUtils::Jet* jet : event->jets("antikt_R04"))
        {
          if (jet->pT() > 20. && fabs(jet->eta()) < 2.8 )
            baselineJets.push_back(jet);
        }

        // Taus
        float MtTauCand = -1;
        vector<const HEPUtils::Particle*> tauCands;
        for (const HEPUtils::Particle* tau : event->taus())
        {
          if (tau->pT() > 10. && tau->abseta() < 2.47) tauCands.push_back(tau);
        }
        applyEfficiency(tauCands, ATLAS::effTau.at("R1"));

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
        for (const HEPUtils::Jet* jet : baselineJets)
        {
          bool hasTag=has_tag(_eff2d, fabs(jet->eta()), jet->pT());

          if(jet->btag() && hasTag && fabs(jet->eta()) < 2.5 && jet->pT() > 20.)
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
        removeOverlap(baselineElectrons,nonBJets,0.2);
        removeOverlap(baselineElectrons,bJets,0.2);


        muJetSpecialOverlapRemoval(nonBJets, baselineMuons);
        removeOverlap(baselineMuons, nonBJets, 0.2);
        removeOverlap(baselineMuons, bJets, 0.2);

        auto lambda = [](double lepton_pT) { return std::min(0.4, 0.04 + 10./(lepton_pT) ); };

        removeOverlap(baselineMuons, nonBJets, lambda);
        removeOverlap(baselineMuons, bJets, lambda);
        removeOverlap(baselineElectrons, nonBJets, lambda);
        removeOverlap(baselineElectrons, bJets, lambda);

        // Fill a jet-pointer-to-bool map to make it easy to check
        // if a given jet is treated as a b-jet in this analysis
        map<const HEPUtils::Jet*,bool> analysisBtags;
        for (const HEPUtils::Jet* jet : bJets) {
          analysisBtags[jet] = true;
        }
        for (const HEPUtils::Jet* jet : nonBJets) {
          analysisBtags[jet] = false;
        }


        // After OR Baseline Leptons
        int nBaseElectrons = baselineElectrons.size();
        int nBaseMuons = baselineMuons.size();
        int nLep = nBaseElectrons + nBaseMuons;

        vector<const HEPUtils::Particle*> baselineLeptons = baselineElectrons;
        baselineLeptons.insert(baselineLeptons.end(), baselineMuons.begin(), baselineMuons.end());

        // Signal object containers
        vector<const HEPUtils::Particle*> signalElectrons;
        vector<const HEPUtils::Particle*> signalMuons;

        vector<const HEPUtils::Jet*> signalJets;
        vector<const HEPUtils::Jet*> signalBJets;
        vector<const HEPUtils::Jet*> signalNonBJets;

        // Now apply signal jet cuts
        for (const HEPUtils::Jet* jet : bJets)
        {
          if(jet->pT() > 20. && fabs(jet->eta())<2.5)
          {
            signalJets.push_back(jet);
            signalBJets.push_back(jet);
          }
        }

        for (const HEPUtils::Jet* jet : nonBJets)
        {
          if(jet->pT() > 20. && fabs(jet->eta())<2.8)
          {
            signalJets.push_back(jet);
            signalNonBJets.push_back(jet);
          }
        }

        // Sort by pT
        //Put signal jets in pT order
        sort(signalJets.begin(), signalJets.end(), compareJetPt);
        sort(signalBJets.begin(), signalBJets.end(), compareJetPt);
        sort(signalNonBJets.begin(), signalNonBJets.end(), compareJetPt);

        for (const HEPUtils::Particle* electron : baselineElectrons)
        {
          signalElectrons.push_back(electron);
        }

        for (const HEPUtils::Particle* muon : baselineMuons)
        {
          signalMuons.push_back(muon);
        }

        // Now do the met sig calculation
        // Note: use signal jets since pT and eta requirements are same as baseline
        //       but overlap removal has been done correctly
        // Get the photons for the purpose of the calculation: no info in paper, have guessed pT and eta from other analyses
        vector<const HEPUtils::Particle*> baselinePhotons;
        for (const HEPUtils::Particle* photon : event->photons())
        {
          if (photon->pT() > 25. && photon->abseta() < 2.37) baselinePhotons.push_back(photon);
        }
        // Apply photon efficiency
        applyEfficiency(baselinePhotons, ATLAS::eff2DPhoton.at("R2"));


        double MetSig = calcMETSignificance(baselineElectrons, baselinePhotons, baselineMuons, signalJets, tauCands, metVec);

        // Need to recluster jets at this point (R=0.8 and R=1.2)
        vector<std::shared_ptr<HEPUtils::Jet>> fatJetsR8=get_jets(signalJets,0.8);
        vector<std::shared_ptr<HEPUtils::Jet>> fatJetsR12=get_jets(signalJets,1.2);

        //int nFatJetsR8 = fatJetsR8.size();
        int nFatJetsR12 = fatJetsR12.size();

        //Put 1_2 signal jets in decreasing pT order
        std::sort(fatJetsR12.begin(), fatJetsR12.end(), sortByPT0l_sharedptr);

        //Put 0_8 signal jets in pT order
        std::sort(fatJetsR8.begin(), fatJetsR8.end(), sortByPT0l_sharedptr);

        int nBJets = signalBJets.size();
        int nNonBJets = signalNonBJets.size();
        int nSignalJets = signalJets.size();

        // DRBB
        float DRBB = 0;
        if (nBJets > 1) DRBB=signalBJets[1]->mom().deltaR_eta(signalBJets[0]->mom());

        // dPhiJetMet
        double dPhiJetMetMin2 = 0;
        double dPhiJetMetMin3 = 0;
        double dPhiJetMetMin4 = 0;
        if (nSignalJets >= 2) {
          dPhiJetMetMin2 = std::min(fabs(metVec.deltaPhi(signalJets[0]->mom())), fabs(metVec.deltaPhi(signalJets[1]->mom())));
          if (nSignalJets>=3) {
            dPhiJetMetMin3 = std::min(dPhiJetMetMin2, fabs(metVec.deltaPhi(signalJets[2]->mom())));
            if (nSignalJets>=4) {
              dPhiJetMetMin4 = std::min(dPhiJetMetMin3, fabs(metVec.deltaPhi(signalJets[3]->mom())));
            }
          }
        }

        float AntiKt8M_0 = 0;
        //float AntiKt8M_1 = 0;
        float AntiKt12M_0 = 0;
        float AntiKt12M_1 = 0;

        if (fatJetsR8.size()>0)  AntiKt8M_0 = fatJetsR8[0]->mass() ;
        //if (fatJetsR8.size()>1)  AntiKt8M_1 = fatJetsR8[1]->mass() ;
        if (fatJetsR12.size()>0) AntiKt12M_0 = fatJetsR12[0]->mass() ;
        if (fatJetsR12.size()>1) AntiKt12M_1 = fatJetsR12[1]->mass() ;


        bool hasTaus = false;
        for (const HEPUtils::Particle* tau : tauCands) {
          if (tau->mom().deltaPhi(metVec) < M_PI/5.) {
            MtTauCand = get_mT(tau->mom(), metVec);
          }
          if (MtTauCand > 0) hasTaus = true;
        }

        // Close-by b-jets and MtBMets
        int NCloseByBJets12Leading = 0;
        int NCloseByBJets12Subleading = 0;
        float MtBMin = 0;
        float MtBMax = 0;
        double dPhi_min = 1000.;
        double dPhi_max = 0.;
        if (nBJets >= 2) {
          for (const HEPUtils::Jet* jet : signalBJets) {
            double dphi = fabs(metVec.deltaPhi(jet->mom()));
            if (dphi < dPhi_min) {
              dPhi_min = dphi;
              MtBMin = get_mT(jet->mom(), metVec);
            }
            if (dphi > dPhi_max) {
              dPhi_max = dphi;
              MtBMax = get_mT(jet->mom(), metVec);
            }
            if (nFatJetsR12 > 0 && jet->mom().deltaR_eta(fatJetsR12[0]->mom()) <= 1.2)
              NCloseByBJets12Leading++;
            if (nFatJetsR12 > 1 && jet->mom().deltaR_eta(fatJetsR12[1]->mom()) <= 1.2)
              NCloseByBJets12Subleading++;
          }
        }



        //Chi2 method (Same as stop0L2015.cxx)
        float realWMass = 80.385;
        float realTopMass = 173.210;
        float MT2Chi2 = 0.;
        double Chi2min = DBL_MAX;
        int W1j1_low = -1, W1j2_low = -1, W2j1_low = -1, W2j2_low = -1, b1_low = -1, b2_low = -1;
        if (nSignalJets >= 4 && nBJets >= 2 && nNonBJets >= 2)
        {
          for (int W1j1 = 0; W1j1 < (int) nNonBJets; W1j1++)
          {
            for (int W2j1 = 0; W2j1 < (int) nNonBJets; W2j1++)
            {
              if (W2j1 == W1j1) continue;
              for (int b1 = 0; b1 < (int) nBJets; b1++)
              {
                for (int b2 = 0; b2 < (int) nBJets; b2++)
                {
                  if (b2 == b1) continue;
                  double chi21, chi22, mW1, mW2, mt1, mt2;
                  if (W2j1 > W1j1)
                  {
                    mW1 = nonBJets[W1j1]->mass();
                    mW2 = nonBJets[W2j1]->mass();
                    mt1 = (nonBJets[W1j1]->mom() + signalBJets[b1]->mom()).m();
                    mt2 = (nonBJets[W2j1]->mom() + signalBJets[b2]->mom()).m();
                    chi21 = (mW1 - realWMass) * (mW1 - realWMass) / realWMass + (mt1 - realTopMass) * (mt1 - realTopMass) / realTopMass;
                    chi22 = (mW2 - realWMass) * (mW2 - realWMass) / realWMass + (mt2 - realTopMass) * (mt2 - realTopMass) / realTopMass;
                    if (Chi2min > (chi21 + chi22))
                    {
                      Chi2min = chi21 + chi22;
                      if (chi21 < chi22)
                      {
                        W1j1_low = W1j1;
                        W1j2_low = -1;
                        W2j1_low = W2j1;
                        W2j2_low = -1;
                        b1_low = b1;
                        b2_low = b2;
                      }
                      else
                      {
                        W2j1_low = W1j1;
                        W2j2_low = -1;
                        W1j1_low = W2j1;
                        W1j2_low = -1;
                        b2_low = b1;
                        b1_low = b2;
                      }
                    }
                  }
                  if (nNonBJets < 3)
                  continue;
                  for (int W1j2 = W1j1 + 1; W1j2 < nNonBJets; W1j2++)
                  {
                    if (W1j2 == W2j1) continue;
                    //try bll,bl top candidates
                    mW1 = (nonBJets[W1j1]->mom() + nonBJets[W1j2]->mom()).m();
                    mW2 = (nonBJets[W2j1]->mom()).m();
                    mt1 = (nonBJets[W1j1]->mom() + nonBJets[W1j2]->mom() + signalBJets[b1]->mom()).m();
                    mt2 = (nonBJets[W2j1]->mom() + signalBJets[b2]->mom()).m();
                    chi21 = (mW1 - realWMass) * (mW1 - realWMass) / realWMass + (mt1 - realTopMass) * (mt1 - realTopMass) / realTopMass;
                    chi22 = (mW2 - realWMass) * (mW2 - realWMass) / realWMass + (mt2 - realTopMass) * (mt2 - realTopMass) / realTopMass;
                    if (Chi2min > (chi21 + chi22))
                    {
                      Chi2min = chi21 + chi22;
                      if (chi21 < chi22)
                      {
                        W1j1_low = W1j1;
                        W1j2_low = W1j2;
                        W2j1_low = W2j1;
                        W2j2_low = -1;
                        b1_low = b1;
                        b2_low = b2;
                      }
                      else
                      {
                        W2j1_low = W1j1;
                        W2j2_low = W1j2;
                        W1j1_low = W2j1;
                        W1j2_low = -1;
                        b2_low = b1;
                        b1_low = b2;
                      }
                    }
                    if (nNonBJets < 4) continue;
                    //try bll, bll top candidates
                    for (int W2j2 = W2j1 + 1; W2j2 < (int) nNonBJets; W2j2++)
                    {
                      if ((W2j2 == W1j1) || (W2j2 == W1j2)) continue;
                      if (W2j1 < W1j1) continue; //runtime reasons, we don't want combinations checked twice <--------------------This line should be added
                      mW1 = (nonBJets[W1j1]->mom() + nonBJets[W1j2]->mom()).m();
                      mW2 = (nonBJets[W2j1]->mom() + nonBJets[W2j2]->mom()).m();
                      mt1 = (nonBJets[W1j1]->mom() + nonBJets[W1j2]->mom() + signalBJets[b1]->mom()).m();
                      mt2 = (nonBJets[W2j1]->mom() + nonBJets[W2j2]->mom() + signalBJets[b2]->mom()).m();
                      chi21 = (mW1 - realWMass) * (mW1 - realWMass) / realWMass + (mt1 - realTopMass) * (mt1 - realTopMass) / realTopMass;
                      chi22 = (mW2 - realWMass) * (mW2 - realWMass) / realWMass + (mt2 - realTopMass) * (mt2 - realTopMass) / realTopMass;
                      if (Chi2min > (chi21 + chi22))
                      {
                        Chi2min = chi21 + chi22;
                        if (chi21 < chi22)
                        {
                          W1j1_low = W1j1;
                          W1j2_low = W1j2;
                          W2j1_low = W2j1;
                          W2j2_low = W2j2;
                          b1_low = b1;
                          b2_low = b2;
                        }
                        else
                        {
                          W2j1_low = W1j1;
                          W2j2_low = W1j2;
                          W1j1_low = W2j1;
                          W1j2_low = W2j2;
                          b2_low = b1;
                          b1_low = b2;
                        }
                      }
                    }
                  }
                }
              }
            }
          }

          HEPUtils::P4 WCand0 = nonBJets[W1j1_low]->mom();
          if (W1j2_low != -1) WCand0 += signalNonBJets[W1j2_low]->mom();
          HEPUtils::P4 topCand0 = WCand0 + signalBJets[b1_low]->mom();

          HEPUtils::P4 WCand1 = signalNonBJets[W2j1_low]->mom();
          if(W2j2_low != -1) WCand1 += signalNonBJets[W2j2_low]->mom();
          HEPUtils::P4 topCand1 = WCand1 + signalBJets[b2_low]->mom();

          HEPUtils::P4 tempTop0=HEPUtils::P4::mkEtaPhiMPt(0.,topCand0.phi(),173.210,topCand0.pT());
          HEPUtils::P4 tempTop1=HEPUtils::P4::mkEtaPhiMPt(0.,topCand1.phi(),173.210,topCand1.pT());

          // Note that the first component here is the mass
          // This must be the top mass (i.e. mass of our vectors) and not zero!

          double pa_a[3] = { tempTop0.m() , tempTop0.px(), tempTop0.py() };
          double pb_a[3] = { tempTop1.m() , tempTop1.px(), tempTop1.py() };
          double pmiss_a[3] = { 0, metVec.px(), metVec.py() };
          double mn_a = 0.;

          mt2_bisect::mt2 mt2_event_a;

          mt2_event_a.set_momenta(pa_a,pb_a,pmiss_a);
          mt2_event_a.set_mn(mn_a);

          MT2Chi2 = mt2_event_a.get_mt2();
        }


        double Ht=0;

        for(size_t jet=0;jet<signalJets.size();jet++)Ht+=signalJets[jet]->pT();

        double HtSig = Met/sqrt(Ht);

        int nBadJets=0;

        //////////////////////////////////////
        // Region Cuts
        bool pre1B4J0L = Met > 250 && nLep == 0 && nSignalJets >= 4 && nBJets >= 1 && signalJets[1]->pT() > 80 && signalJets[3]->pT() > 40 && dPhiJetMetMin2>0.4;
        bool pre2B4J0L = pre1B4J0L && nBJets >= 2 && dPhiJetMetMin4 > 0.4 && MetSig > 5 && MtBMin > 50 && MtTauCand < 0;
        bool pre2B4J0Ltight = pre2B4J0L && MtBMin > 200;
        bool pre2B4J0LtightTT = pre2B4J0Ltight && nFatJetsR12>=2 && AntiKt12M_0>120. && AntiKt12M_1>120;
        bool pre2B4J0LtightTW = pre2B4J0Ltight && nFatJetsR12>=2 && AntiKt12M_0>120. && AntiKt12M_1>60 && AntiKt12M_1<120;
        bool pre2B4J0LtightT0 = pre2B4J0Ltight && nFatJetsR12>=2 && AntiKt12M_0>120. && AntiKt12M_1>0 && AntiKt12M_1<60;

        //bool SRA = pre2B4J0Ltight && MT2Chi2 > 450 && nFatJetsR12>=2 && AntiKt12M_0>120 && AntiKt8M_0 > 60.00 && MetSig > 25.00 && NCloseByBJets12Leading >= 1;
        bool SRATT = !hasTaus && pre2B4J0LtightTT && MT2Chi2 > 450 && AntiKt8M_0 > 60.00 && MetSig > 25.00 && NCloseByBJets12Leading >= 1 && NCloseByBJets12Subleading >= 1 && DRBB > 1.00;
        bool SRATW = !hasTaus && pre2B4J0LtightTW && MT2Chi2 > 450 && AntiKt8M_0 > 60.00 && MetSig > 25.00 && NCloseByBJets12Leading >= 1;
        bool SRAT0 = !hasTaus && pre2B4J0LtightT0 && MT2Chi2 > 450 && AntiKt8M_0 > 60.00 && MetSig > 25.00 && NCloseByBJets12Leading >= 1;

        bool SRB = !hasTaus && pre2B4J0Ltight && MtBMax>200 && DRBB>1.4 && nFatJetsR12>=2 && AntiKt12M_0>120 && MT2Chi2<450 && MetSig>14;
        bool SRBTT = SRB && nFatJetsR12>=2 && AntiKt12M_0>120. && AntiKt12M_1>120;
        bool SRBTW = SRB && nFatJetsR12>=2 && AntiKt12M_0>120. && AntiKt12M_1>60 && AntiKt12M_1<120;
        bool SRBT0 = SRB && nFatJetsR12>=2 && AntiKt12M_0>120. && AntiKt12M_1>0 && AntiKt12M_1<60;

        if (SRATT)_counters.at("SRATT").add_event(event);
        if (SRATW)_counters.at("SRATW").add_event(event);
        if (SRAT0)_counters.at("SRAT0").add_event(event);
        if (SRBTT)_counters.at("SRBTT").add_event(event);
        if (SRBTW)_counters.at("SRBTW").add_event(event);
        if (SRBT0)_counters.at("SRBT0").add_event(event);

        // SRC missing (these are the RJR regions)

        bool SRDLoose = nLep == 0 && nBadJets == 0 && Met > 250 && nonBJets.size() > 0 && nonBJets.size() > 0 && nonBJets[0]->pT()>250 && nonBJets[0]->mom().deltaR_eta(metVec) > 2.4 && HtSig > 22;
        bool SRD0 = SRDLoose && nBJets == 0 && dPhiJetMetMin4>0.4 && HtSig > 26;
        bool SRD1 = SRDLoose && nBJets == 1 && fabs(signalBJets[0]->eta())<1.6 && signalBJets[0]->mom().deltaPhi(nonBJets[0]->mom())>2.0 && signalBJets[0]->mom().deltaPhi(nonBJets[0]->mom())>2.2;
        bool SRD2 = SRDLoose && nBJets >= 2 && signalBJets[0]->pT()<175 && fabs(signalBJets[1]->eta())<1.2 && signalBJets[0]->mom().deltaPhi(nonBJets[0]->mom())>2.2 && signalBJets[1]->mom().deltaPhi(nonBJets[0]->mom())>1.6;
        //bool SRD = SRD0 || SRD1 || SRD2;

        if ( SRD0 )_counters.at("SRD0").add_event(event);
        if ( SRD1 )_counters.at("SRD1").add_event(event);
        if ( SRD2 )_counters.at("SRD2").add_event(event);


        // Now fill the cutflows
        const double w = event->weight();

        _cutflows.fillinit(w);

        _cutflows["SRATT"].fillnext({
          Met > 250.,
          nSignalJets >=4,
          nBJets >=2,
          nLep == 0,
          nSignalJets >=4 && signalJets[3]->pT() > 40,
          nSignalJets >=2 && signalJets[1]->pT() > 80,
          dPhiJetMetMin2>0.4,
          true,
          MetSig > 5,
          MtBMin > 50.,
          !hasTaus,
          MtBMin > 200.,
          AntiKt12M_0>120.,
          AntiKt12M_1>120,
          MT2Chi2 > 450,
          AntiKt8M_0 > 60.,
          MetSig > 25.,
          NCloseByBJets12Leading >= 1,
          NCloseByBJets12Subleading >= 1,
          DRBB > 1.}, w);

        _cutflows["SRATW"].fillnext({
          Met > 250.,
          nSignalJets >=4,
          nBJets >=2,
          nLep == 0,
          nSignalJets >=4 && signalJets[3]->pT() > 40,
          nSignalJets >=2 && signalJets[1]->pT() > 80,
          dPhiJetMetMin2>0.4,
          true,
          MetSig > 5,
          MtBMin > 50.,
          !hasTaus,
          MtBMin > 200.,
          AntiKt12M_0>120.,
          AntiKt12M_1>60.,
                           AntiKt12M_1<120.,
          MT2Chi2 > 450.,
          AntiKt8M_0 > 60.,
          MetSig > 25.,
          NCloseByBJets12Leading >= 1},w);

        return;

      }

      void collect_results()
      {

        add_result(SignalRegionData(_counters.at("SRATT"), 4.0, { 3.2, 0.5}));
        add_result(SignalRegionData(_counters.at("SRATW"), 8.0, { 5.6, 0.7}));
        add_result(SignalRegionData(_counters.at("SRAT0"), 11., { 17.3, 1.7}));
        add_result(SignalRegionData(_counters.at("SRBTT"), 67., { 46.0, 7.0}));
        add_result(SignalRegionData(_counters.at("SRBTW"), 84., { 81., 7.}));
        add_result(SignalRegionData(_counters.at("SRBT0"), 292., { 276., 24.}));
        add_result(SignalRegionData(_counters.at("SRD0"), 5., { 6.9, 1.3}));
        add_result(SignalRegionData(_counters.at("SRD1"), 4., { 3.1, 1.0}));
        add_result(SignalRegionData(_counters.at("SRD2"), 10., { 12.2, 1.5}));

        add_cutflows(_cutflows);

        return;
      }


    protected:
      void analysis_specific_reset()
      {
        for (auto& pair : _counters) { pair.second.reset(); }
      }

    };

    DEFINE_ANALYSIS_FACTORY(ATLAS_13TeV_0LEPStop_139invfb)

  }
}


