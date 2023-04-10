///
///  \author Tomas Gonzalo
///          (gonzalo@physik.rwth-aachen.de)
///  \date 2021 July
///  *********************************************


#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/Utils.hpp"
#include "gambit/ColliderBit/analyses/Cutflow.hpp"
#include "gambit/ColliderBit/CMSEfficiencies.hpp"

//#define CHECK_CUTFLOW

// Based on http://cms-results.web.cern.ch/cms-results/public-results/publications/SUS-19-012/index.html

namespace Gambit
{
  namespace ColliderBit
  {

    class Analysis_CMS_13TeV_MultiLEP_137invfb : public Analysis
    {

      protected:
        // Counters for the number of accepted events for each signal region
        std::map<str, EventCounter> _counters;

      private:

        inline str SR(str type, size_t count)
        {
          return count < 10 ? type + "0" + std::to_string(count) : type + std::to_string(count);
        }

      public:
 
        // Required detector sim
        static constexpr const char* detector = "CMS";

        Cutflows _cutflows;

        Analysis_CMS_13TeV_MultiLEP_137invfb()
        {

          // Fill counters map
          // 2SSLep (2lSS)
          for(size_t i=1; i<=20; ++i)
          {
            _counters[SR("SS",i)] =  EventCounter(SR("SS",i));
            _cutflows.addCutflow(SR("SS",i), {"Preselection", "Final"});
          }
          // 3Lep, OSSF pair (3lA)
          for(size_t i=1; i<=64; ++i)
          {
            _counters[SR("A",i)] = EventCounter(SR("A",i));
            _cutflows.addCutflow(SR("A",i), {"Preselection", "Final"});
          }
          // 3Lep, no OSSF pair (3lB)
          for(size_t i=1; i<=3; ++i)
          {
            _counters[SR("B",i)] = EventCounter(SR("B",i));
            _cutflows.addCutflow(SR("B",i), {"Preselection", "Final"});
          }
          // 3Lep, OSSF pair + tau (3lC)
          for(size_t i=1; i<=9; ++i)
          {
            _counters[SR("C",i)] = EventCounter(SR("C",i));
            _cutflows.addCutflow(SR("C",i), {"Preselection", "Final"});
          }
          // 3Lep, no OSSF pair, 2 OS light leptons + tau (3lD)
          for(size_t i=1; i<=16; ++i)
          {
            _counters[SR("D",i)] = EventCounter(SR("D",i));
            _cutflows.addCutflow(SR("D",i), {"Preselection", "Final"});
          }
          // 3Lep, no OSSF pair, 2 SS light leptons + tau (3lE)
          for(size_t i=1; i<=9; ++i)
          {
            _counters[SR("E",i)] = EventCounter(SR("E",i));
            _cutflows.addCutflow(SR("E",i), {"Preselection", "Final"});
          }
          // 3Lep, 2 tau (3lF)
          for(size_t i=1; i<=12; ++i)
          {
            _counters[SR("F",i)] = EventCounter(SR("F",i));
            _cutflows.addCutflow(SR("F",i), {"Preselection", "Final"});
          }
          // 4Lep, 2 OSSF pairs (4lG)
          for(size_t i=1; i<=5; ++i)
          {
            _counters[SR("G",i)] = EventCounter(SR("G",i));
            _cutflows.addCutflow(SR("G",i), {"Preselection", "Final"});
          }
          // 4Lep, 1 or fewer OSSF pairs (4lH)
          for(size_t i=1; i<=3; ++i)
          {
            _counters[SR("H",i)] = EventCounter(SR("H",i));
            _cutflows.addCutflow(SR("H",i), {"Preselection", "Final"});
          }
          // 4Lep, tau + 3 light leptons (4lI)
          for(size_t i=1; i<=3; ++i)
          {
            _counters[SR("I",i)] = EventCounter(SR("I",i));
            _cutflows.addCutflow(SR("I",i), {"Preselection", "Final"});
          }
          // 4Lep, 2 tau + 2 light leptons, 2 OSSF pairs (4lJ)
          for(size_t i=1; i<=3; ++i)
          {
            _counters[SR("J",i)] = EventCounter(SR("J",i));
            _cutflows.addCutflow(SR("J",i), {"Preselection", "Final"});
          }
          // 4Lep, 2 tau + 2 light leptons, 1 or fewer OSSF pairs (4lK)
          for(size_t i=1; i<=3; ++i)
          {
            _counters[SR("K",i)] = EventCounter(SR("K",i));
            _cutflows.addCutflow(SR("K",i), {"Preselection", "Final"});
          }


          set_analysis_name("CMS_13TeV_MultiLEP_137invfb");
          set_luminosity(137.0);

        }

        void counter_cutflow(str SR, const HEPUtils::Event *event, double weight)
        {
          _cutflows[SR].fillnext(weight);
          _counters.at(SR).add_event(event);
        }

        void run(const HEPUtils::Event* event)
        {

          // Useful constants
          double mZ = 91.1876;

          // Missing ET and momentum
          double met = event->met();
          P4 mmom = event->missingmom();

          // Here we will be using the same efficiencies as in the 36invfb version, as there is no public data for this yet

          // Baseline electrons
          std::vector<const HEPUtils::Particle*> baselineElectrons;
          std::vector<const HEPUtils::Particle*> baselineLeptons;
          for (const HEPUtils::Particle* electron : event->electrons())
          {
            bool isEl = has_tag(CMS::eff2DEl.at("SUS_19_008"), fabs(electron->eta()), electron->pT());
            if (electron->pT() > 10. and fabs(electron->eta()) < 2.5)
            {
              baselineLeptons.push_back(electron);
              if(isEl)
                baselineElectrons.push_back(electron);
            }
          }

          // Baseline muons
          std::vector<const HEPUtils::Particle*> baselineMuons;
          for (const HEPUtils::Particle* muon : event->muons())
          {
            bool isMu = has_tag(CMS::eff2DMu.at("SUS_19_008"), fabs(muon->eta()), muon->pT());
            if (muon->pT() > 10. and fabs(muon->eta()) < 2.4)
            {
              baselineLeptons.push_back(muon);
              if(isMu)
                baselineMuons.push_back(muon);
            }
          }

          // Mini-isolation of electrons and muons, Imin < 0.4, hard to implement, leave for now

          // Baseline taus
          std::vector<const HEPUtils::Particle*> baselineTaus;
          for (const HEPUtils::Particle* tau : event->taus())
          {
            bool isTau = has_tag(CMS::eff2DTau.at("SUS_16_039"), fabs(tau->eta()), tau->pT());
            if (tau->pT()>20. &&fabs(tau->eta())<2.3 && isTau)
              baselineTaus.push_back(tau);
          }

          // We assume that the efficiency above accounts for the selection of prompt leptons
          // and only "tight" leptons pass the cuts

          // Baseline jets
          std::vector<const HEPUtils::Jet*> baselineJets;
          for (const HEPUtils::Jet* jet : event->jets())
          {
            if (jet->pT()>25. &&fabs(jet->eta())<2.4)
              baselineJets.push_back(jet);
          }

          // Jets must have a separation of R > 0.4 from any lepton
          removeOverlap(baselineJets, baselineElectrons, 0.4);
          removeOverlap(baselineJets, baselineMuons, 0.4);
          removeOverlap(baselineJets, baselineTaus, 0.4);

          ////////////////////
          // Signal objects //

          // - Keep the four hardest leptons (incl. taus) --> signalLeptons
          // - Create signalLightLeptons and other lepton containers from signalLeptons

          std::vector<const HEPUtils::Particle*> signalLeptonCandidates;
          signalLeptonCandidates.insert(signalLeptonCandidates.end(), baselineElectrons.begin(), baselineElectrons.end());
          signalLeptonCandidates.insert(signalLeptonCandidates.end(), baselineMuons.begin(), baselineMuons.end());
          signalLeptonCandidates.insert(signalLeptonCandidates.end(), baselineTaus.begin(), baselineTaus.end());

          // Only keep the four highest-pT leptons
          sortByPt(signalLeptonCandidates);
          std::vector<const HEPUtils::Particle*> signalLeptons;
          if (signalLeptonCandidates.size() > 4)
          {
            signalLeptons.insert(signalLeptons.end(), signalLeptonCandidates.begin(), signalLeptonCandidates.begin()+3);
          }
          else
          {
            signalLeptons = signalLeptonCandidates;
          }

          // Create other signal lepton containers from signalLeptons
          std::vector<const HEPUtils::Particle*> signalLightLeptons;
          std::vector<const HEPUtils::Particle*> signalElectrons;
          std::vector<const HEPUtils::Particle*> signalMuons;
          std::vector<const HEPUtils::Particle*> signalTaus;
          for (const HEPUtils::Particle* lep : signalLeptons)
          {
            if (amIanElectron(lep))
            {
              signalLightLeptons.push_back(lep);
              signalElectrons.push_back(lep);
            }
            else if (amIaMuon(lep))
            {
              signalLightLeptons.push_back(lep);
              signalMuons.push_back(lep);
            }
            else if (amIaTau(lep))
            {
              signalTaus.push_back(lep);
            }
          }

          // Create containers with SS, OS and OSSF pairs:

          // - SS pairs, only light leptons
          std::vector<std::vector<const HEPUtils::Particle*> > SSpairs = getSSpairs(signalLightLeptons);
          // Should these pairs be unique?

          // - SS pairs, including taus
          std::vector<std::vector<const HEPUtils::Particle*> > SSpairsWithTaus = getSSpairs(signalLeptons);
          // Should these pairs be unique?

          // - OS pairs, only light leptons
          std::vector<std::vector<const HEPUtils::Particle*> > OSpairs = getOSpairs(signalLightLeptons);
          sortByParentMass(OSpairs, mZ);         
          uniquePairs(OSpairs);

          // - OS pairs, including taus
          std::vector<std::vector<const HEPUtils::Particle*> > OSpairsWithTaus = getOSpairs(signalLeptons);
          sortByParentMass(OSpairsWithTaus, mZ);         
          uniquePairs(OSpairsWithTaus);

          // - OSSF pairs, only light leptons
          std::vector<std::vector<const HEPUtils::Particle*> > OSSFpairs = getSFOSpairs(signalLightLeptons);
          sortByParentMass(OSSFpairs, mZ);
          uniquePairs(OSSFpairs);

          // - OSSF pairs, including taus
          std::vector<std::vector<const HEPUtils::Particle*> > OSSFpairsWithTaus = getSFOSpairs(signalLeptons);
          sortByParentMass(OSSFpairsWithTaus, mZ);
          uniquePairs(OSSFpairsWithTaus);


          // Jets
          std::vector<const HEPUtils::Jet*> signalJets = baselineJets;
          sortByPt(signalJets);

          // Make b-jets object, including miss-identification of c and light-quark jets
          std::vector<const HEPUtils::Jet*> signalBJets;
          double ctagmissid = 0.024, qtagmissid = 0.001;
          for(const Jet* j: signalJets)
          {
            if( j->btag() or
                (j->ctag() and random_bool(ctagmissid)) or
                random_bool(qtagmissid) )
              signalBJets.push_back(j);
          }

          // Apply b-tag efficiency on b-jets
          CMS::applyCSVv2TightBtagEff(signalBJets);
          


          ///////////////////////////////
          // Common variables and cuts //
          const size_t nLeptons = signalLeptons.size();
          const size_t nLightLeptons = signalLightLeptons.size();
          const size_t nTaus = signalTaus.size();
          const size_t nSSpairs = SSpairs.size();
          const size_t nOSpairsWithTaus = OSpairsWithTaus.size();
          const size_t nOSSFpairs = OSSFpairs.size();
          const size_t nOSSFpairsWithTaus = OSSFpairsWithTaus.size();

          const size_t nJets = signalJets.size();
          const size_t nBJets = signalBJets.size();

          // Di-lepton invariant mass for OSSF pairs of light leptons
          std::vector<double> mossf;
          for(auto pair: OSSFpairs)
            mossf.push_back( (pair.at(0)->mom() + pair.at(1)->mom()).m() );
          std::sort(mossf.begin(), mossf.end());

          // Invariant mass of third baseline lepton in the event with the rest of leptons
          std::vector<double> m3l;
          if(nLightLeptons == 2)
            for(auto lep: baselineLeptons)
              for(auto lep2 : baselineLeptons)
                if(lep != lep2)
                  m3l.push_back(abs((lep->mom() + lep2->mom()).m() - mZ));
          std::sort(m3l.begin(), m3l.end());

          // Flags for lepton pairs
          bool muonPair = nLeptons == 2 and nLightLeptons == 2 and amIaMuon(signalLeptons.at(0)) and amIaMuon(signalLeptons.at(1));
          bool electronPair = nLeptons == 2 and nLightLeptons == 2 and amIanElectron(signalLeptons.at(0)) and amIanElectron(signalLeptons.at(1));
          bool mixedPair = nLeptons == 2 and nLightLeptons == 2 and ( ( amIaMuon(signalLeptons.at(0)) and amIanElectron(signalLeptons.at(1)) ) or
                                                  ( amIanElectron(signalLeptons.at(0)) and amIaMuon(signalLeptons.at(1)) ) );

          // Cuflow initialization
          const double w = event->weight();
          _cutflows.fillinit(w);

          //////////////////
          // Preselection //
          if(nLeptons < 3 and (nLightLeptons < 2 or nSSpairs == 0) ) return;
          if(nBJets > 0) return;
          if(nOSSFpairs > 0 and mossf.at(0) < 12.0) return;
          _cutflows.fillnext(w);

          ////////////////////
          // Signal regions //

          // 2SSLep, (2lSS)
          if(nLightLeptons == 2 and nLeptons == 2 and nSSpairs == 1 and 
             ( (muonPair and signalLeptons.at(0)->pT() > 20.) or ((electronPair or mixedPair) and signalLeptons.at(0)->pT() > 25.) ) and
             ( (amIanElectron(signalLeptons.at(1)) and signalLeptons.at(1)->pT() >  15.) or (amIaMuon(signalLeptons.at(1)) and signalLeptons.at(1)->pT() > 10.) ) and
             ( nJets < 2 or signalJets.at(1)->pT() < 40) and
             m3l.size() > 0 and m3l.at(0) > 15. and
             met > 60. )
          {

            // Stransverse mass
            double mT2 = get_mT2(signalLeptons.at(0), signalLeptons.at(1), mmom, 0);

            // pT of dilepton system for SS leptons
            double pTll = ( signalLeptons.at(0)->mom() + signalLeptons.at(1)->mom() ).pT();

            // Sign of final states, turns out positive leptons have negative pids, who knew
            bool positive = signalLeptons.at(0)->pid() < 0;
            bool negative = not positive;

            if(mT2 == 0. and pTll <  70.) counter_cutflow("SS01",event,w);
            if(mT2 == 0. and pTll >= 70. and met <  100.) counter_cutflow("SS02",event,w);
            if(mT2 == 0. and pTll >= 70. and met >= 100. and met < 200. and positive) counter_cutflow("SS03",event,w);
            if(mT2 == 0. and pTll >= 70. and met >= 100. and met < 200. and negative) counter_cutflow("SS04",event,w);
            if(mT2 == 0. and pTll >= 70. and met >= 200. and positive) counter_cutflow("SS05",event,w);
            if(mT2 == 0. and pTll >= 70. and met >= 200. and negative) counter_cutflow("SS06",event,w);
            if(mT2 >  0. and mT2 <= 80. and pTll <  30. and met <  200. and positive) counter_cutflow("SS07",event,w);
            if(mT2 >  0. and mT2 <= 80. and pTll <  30. and met <  200. and negative) counter_cutflow("SS08",event,w);
            if(mT2 >  0. and mT2 <= 80. and pTll <  30. and met >= 200.) counter_cutflow("SS09",event,w);
            if(mT2 >  0. and mT2 <= 80. and pTll >= 30.) counter_cutflow("SS10",event,w);
            if(mT2 > 80. and pTll <  200. and met <  100.) counter_cutflow("SS11",event,w);
            if(mT2 > 80. and pTll <  200. and met >= 100. and met < 200. and positive) counter_cutflow("SS12",event,w);
            if(mT2 > 80. and pTll <  200. and met >= 100. and met < 200. and negative) counter_cutflow("SS13",event,w);
            if(mT2 > 80. and pTll <  200. and met >= 200. and positive) counter_cutflow("SS14",event,w);
            if(mT2 > 80. and pTll <  200. and met >= 200. and negative) counter_cutflow("SS15",event,w);
            if(mT2 > 80. and pTll >= 200. and met <  100.) counter_cutflow("SS16",event,w);
            if(mT2 > 80. and pTll >= 200. and met >= 100. and met < 200. and positive) counter_cutflow("SS17",event,w);
            if(mT2 > 80. and pTll >= 200. and met >= 100. and met < 200. and negative) counter_cutflow("SS18",event,w);
            if(mT2 > 80. and pTll >= 200. and met >= 200. and positive) counter_cutflow("SS19",event,w);
            if(mT2 > 80. and pTll >= 200. and met >= 200. and negative) counter_cutflow("SS20",event,w);
          }

          // Selection conditon for 3 lepton events
          if(nLeptons == 3 and nLightLeptons >0)
          {
            static int n3lepevents = 0;
            n3lepevents++;
          }
          bool _3Lep = nLeptons == 3 and 
                      nLightLeptons > 0 and 
                      ( (amIanElectron(signalLightLeptons.at(0)) and signalLightLeptons.at(0)->pT() > 25.) or 
                        (amIaMuon(signalLightLeptons.at(0)) and signalLightLeptons.at(0)->pT() > 20.) ) and
                      ( nLightLeptons < 2 or 
                        (amIanElectron(signalLightLeptons.at(1)) and signalLightLeptons.at(1)->pT() > 15.) or 
                        (amIaMuon(signalLightLeptons.at(1)) and signalLightLeptons.at(1)->pT() > 10.) ) and
                      met > 50;

          // 3Lep, OSSF pair (3lA)
          if(_3Lep and nLightLeptons == 3 and nOSSFpairs > 0)
          {
            // Mll variable, OSSF pairs are already ordered by how close they are to mZ
            double mll = (OSSFpairs.at(0).at(0)->mom() + OSSFpairs.at(0).at(1)->mom()).m();

            // MT variable
            double mT = 0.;
            for(auto lepton : signalLeptons)
            {
              if(lepton != OSSFpairs.at(0).at(0) and lepton != OSSFpairs.at(0).at(1))
                mT = sqrt( 2*mmom.pT()*lepton->pT()*(1 - cos(lepton->phi() - mmom.phi())) );
            }

            //MT3l variable
            double mT3l = get_mT(signalLeptons.at(0), signalLeptons.at(1), signalLeptons.at(2), mmom);

            // HT variable
            double HT = scalarSumPt(signalJets);

            // Signal regions
            if(mll < 50. and mT >= 0.   and mT < 100. and mT3l >=  0. and mT3l <  50.) counter_cutflow("A01",event,w);
            if(mll < 50. and mT >= 0.   and mT < 100. and mT3l >= 50. and mT3l < 100.) counter_cutflow("A02",event,w);
            if(mll < 50. and mT >= 0.   and mT < 100. and mT3l >= 100.) counter_cutflow("A03",event,w);
            if(mll < 50. and mT >= 100. and mT < 200.) counter_cutflow("A04",event,w);
            if(mll < 50. and mT >= 200.) counter_cutflow("A05",event,w);

            if(mll >= 50. and mll < 75. and mT >=   0. and mT < 100. and mT3l >=   0. and mT3l < 100.) counter_cutflow("A06",event,w);
            if(mll >= 50. and mll < 75. and mT >=   0. and mT < 100. and mT3l >= 100. and mT3l < 400.) counter_cutflow("A07",event,w);
            if(mll >= 50. and mll < 75. and mT >=   0. and mT < 100. and mT3l >= 400.) counter_cutflow("A08",event,w);
            if(mll >= 50. and mll < 75. and mT >= 100. and mT < 200. and mT3l >=   0. and mT3l < 200.) counter_cutflow("A09",event,w);
            if(mll >= 50. and mll < 75. and mT >= 100. and mT < 200. and mT3l >= 200.) counter_cutflow("A10",event,w);
            if(mll >= 50. and mll < 75. and mT >= 200. and mT3l >=   0. and mT3l < 400.) counter_cutflow("A11",event,w);
            if(mll >= 50. and mll < 75. and mT >= 200. and mT3l >= 400.) counter_cutflow("A12",event,w);

            if(mll >= 105. and mll < 250. and mT >=   0. and mT < 100. and mT3l >=   0. and mT3l < 400.) counter_cutflow("A13",event,w);
            if(mll >= 105. and mll < 250. and mT >=   0. and mT < 100. and mT3l >= 400.) counter_cutflow("A14",event,w);
            if(mll >= 105. and mll < 250. and mT >= 100. and mT < 200. and mT3l >=   0. and mT3l < 200.) counter_cutflow("A15",event,w);
            if(mll >= 105. and mll < 250. and mT >= 100. and mT < 200. and mT3l >= 200.) counter_cutflow("A16",event,w);
            if(mll >= 105. and mll < 250. and mT >= 200. and mT3l >=   0. and mT3l < 400.) counter_cutflow("A17",event,w);
            if(mll >= 105. and mll < 250. and mT >= 200. and mT3l >= 400.) counter_cutflow("A18",event,w);

            if(mll >= 250. and mT >=   0. and mT < 100. and mT3l >=   0. and mT3l < 400.) counter_cutflow("A19",event,w);
            if(mll >= 250. and mT >=   0. and mT < 100. and mT3l >= 400.) counter_cutflow("A20",event,w);
            if(mll >= 250. and mT >= 100. and mT < 200.) counter_cutflow("A21",event,w);
            if(mll >= 250. and mT >= 200.) counter_cutflow("A22",event,w);

            if(mll >= 75. and mll < 105. and HT < 100 and mT >=   0. and mT < 100. and met >=  50. and met < 100.) counter_cutflow("A23",event,w);
            if(mll >= 75. and mll < 105. and HT < 100 and mT >=   0. and mT < 100. and met >= 100. and met < 150.) counter_cutflow("A24",event,w);
            if(mll >= 75. and mll < 105. and HT < 100 and mT >=   0. and mT < 100. and met >= 150. and met < 200.) counter_cutflow("A25",event,w);
            if(mll >= 75. and mll < 105. and HT < 100 and mT >=   0. and mT < 100. and met >= 200. and met < 250.) counter_cutflow("A26",event,w);
            if(mll >= 75. and mll < 105. and HT < 100 and mT >=   0. and mT < 100. and met >= 250.) counter_cutflow("A27",event,w);
            if(mll >= 75. and mll < 105. and HT < 100 and mT >= 100. and mT < 160. and met >=  50. and met < 100.) counter_cutflow("A28",event,w);
            if(mll >= 75. and mll < 105. and HT < 100 and mT >= 100. and mT < 160. and met >= 100. and met < 150.) counter_cutflow("A29",event,w);
            if(mll >= 75. and mll < 105. and HT < 100 and mT >= 100. and mT < 160. and met >= 150. and met < 200.) counter_cutflow("A30",event,w);
            if(mll >= 75. and mll < 105. and HT < 100 and mT >= 100. and mT < 160. and met >= 200.) counter_cutflow("A31",event,w);
            if(mll >= 75. and mll < 105. and HT < 100 and mT >= 160. and met >=  50. and met < 100.) counter_cutflow("A32",event,w);
            if(mll >= 75. and mll < 105. and HT < 100 and mT >= 160. and met >= 100. and met < 150.) counter_cutflow("A33",event,w);
            if(mll >= 75. and mll < 105. and HT < 100 and mT >= 160. and met >= 150. and met < 200.) counter_cutflow("A34",event,w);
            if(mll >= 75. and mll < 105. and HT < 100 and mT >= 160. and met >= 200.) counter_cutflow("A35",event,w);

            if(mll >= 75. and mll < 105. and HT >= 100. and HT < 200 and mT >=   0. and mT < 100. and met >=  50. and met < 100.) counter_cutflow("A36",event,w);
            if(mll >= 75. and mll < 105. and HT >= 100. and HT < 200 and mT >=   0. and mT < 100. and met >= 100. and met < 150.) counter_cutflow("A37",event,w);
            if(mll >= 75. and mll < 105. and HT >= 100. and HT < 200 and mT >=   0. and mT < 100. and met >= 150. and met < 200.) counter_cutflow("A38",event,w);
            if(mll >= 75. and mll < 105. and HT >= 100. and HT < 200 and mT >=   0. and mT < 100. and met >= 200. and met < 250.) counter_cutflow("A39",event,w);
            if(mll >= 75. and mll < 105. and HT >= 100. and HT < 200 and mT >=   0. and mT < 100. and met >= 250.) counter_cutflow("A40",event,w);
            if(mll >= 75. and mll < 105. and HT >= 100. and HT < 200 and mT >= 100. and mT < 160. and met >=  50. and met < 100.) counter_cutflow("A41",event,w);
            if(mll >= 75. and mll < 105. and HT >= 100. and HT < 200 and mT >= 100. and mT < 160. and met >= 100. and met < 150.) counter_cutflow("A42",event,w);
            if(mll >= 75. and mll < 105. and HT >= 100. and HT < 200 and mT >= 100. and mT < 160. and met >= 150. and met < 200.) counter_cutflow("A43",event,w);
            if(mll >= 75. and mll < 105. and HT >= 100. and HT < 200 and mT >= 100. and mT < 160. and met >= 200.) counter_cutflow("A44",event,w);
            if(mll >= 75. and mll < 105. and HT >= 100. and HT < 200 and mT >= 160. and met >=  50. and met < 100.) counter_cutflow("A45",event,w);
            if(mll >= 75. and mll < 105. and HT >= 100. and HT < 200 and mT >= 160. and met >= 100. and met < 150.) counter_cutflow("A46",event,w);
            if(mll >= 75. and mll < 105. and HT >= 100. and HT < 200 and mT >= 160. and met >= 150. and met < 200.) counter_cutflow("A47",event,w);
            if(mll >= 75. and mll < 105. and HT >= 100. and HT < 200 and mT >= 160. and met >= 200.) counter_cutflow("A48",event,w);

            if(mll >= 75. and mll < 105. and HT >= 200. and mT >=   0. and mT < 100. and met >=  50. and met < 150.) counter_cutflow("A49",event,w);
            if(mll >= 75. and mll < 105. and HT >= 200. and mT >=   0. and mT < 100. and met >= 150. and met < 250.) counter_cutflow("A50",event,w);
            if(mll >= 75. and mll < 105. and HT >= 200. and mT >=   0. and mT < 100. and met >= 250. and met < 350.) counter_cutflow("A51",event,w);
            if(mll >= 75. and mll < 105. and HT >= 200. and mT >=   0. and mT < 100. and met >= 350.) counter_cutflow("A52",event,w);
            if(mll >= 75. and mll < 105. and HT >= 200. and mT >= 100. and mT < 160. and met >=  50. and met < 100.) counter_cutflow("A53",event,w);
            if(mll >= 75. and mll < 105. and HT >= 200. and mT >= 100. and mT < 160. and met >= 100. and met < 150.) counter_cutflow("A54",event,w);
            if(mll >= 75. and mll < 105. and HT >= 200. and mT >= 100. and mT < 160. and met >= 150. and met < 200.) counter_cutflow("A55",event,w);
            if(mll >= 75. and mll < 105. and HT >= 200. and mT >= 100. and mT < 160. and met >= 200. and met < 250.) counter_cutflow("A56",event,w);
            if(mll >= 75. and mll < 105. and HT >= 200. and mT >= 100. and mT < 160. and met >= 250. and met < 300.) counter_cutflow("A57",event,w);
            if(mll >= 75. and mll < 105. and HT >= 200. and mT >= 100. and mT < 160. and met >= 300.) counter_cutflow("A58",event,w);
            if(mll >= 75. and mll < 105. and HT >= 200. and mT >= 160. and met >=  50. and met < 100.) counter_cutflow("A59",event,w);
            if(mll >= 75. and mll < 105. and HT >= 200. and mT >= 160. and met >= 100. and met < 150.) counter_cutflow("A60",event,w);
            if(mll >= 75. and mll < 105. and HT >= 200. and mT >= 160. and met >= 150. and met < 200.) counter_cutflow("A61",event,w);
            if(mll >= 75. and mll < 105. and HT >= 200. and mT >= 160. and met >= 200. and met < 250.) counter_cutflow("A61",event,w);
            if(mll >= 75. and mll < 105. and HT >= 200. and mT >= 160. and met >= 250. and met < 300.) counter_cutflow("A63",event,w);
            if(mll >= 75. and mll < 105. and HT >= 200. and mT >= 160. and met >= 300.) counter_cutflow("A64",event,w);
          }

          // 3Lep, no OSSF pair (3lB)
          if(_3Lep and nLightLeptons == 3 and nOSSFpairs == 0)
          {
            // Min DeltaR variable
            double minDeltaR = 0.;
            for(auto lep1 : signalLeptons)
              for(auto lep2 : signalLeptons)
                if(lep1 != lep2 and (minDeltaR > deltaR_eta(lep1->mom(),lep2->mom()) or minDeltaR == 0.) )
                  minDeltaR = deltaR_eta(lep1->mom(),lep2->mom());

            if(minDeltaR <  0.4) counter_cutflow("B01",event,w);
            if(minDeltaR >= 0.4 and minDeltaR < 1.0) counter_cutflow("B02",event,w);
            if(minDeltaR >= 1.0) counter_cutflow("B03",event,w);
          }

          // 3Lep, OSSF pair + tau (3lC)
          if(_3Lep and nTaus == 1 and nOSSFpairs > 0)
          {
            // mT2 variable
            // TODO: Is this the ll MT2?
            double mT2 = get_mT2(signalLightLeptons.at(0), signalLightLeptons.at(1), mmom, 0);

            // mll variable
            double mll = (signalLightLeptons.at(0)->mom() + signalLightLeptons.at(1)->mom()).m();

            // mT2l variable
            double mT2l = get_mT(signalLightLeptons.at(0), signalLightLeptons.at(1), mmom);

            if(abs(mll - mZ) > 15. and met >=  50. and met < 200. and mT2l >= 0. and mT2 <   80.) counter_cutflow("C01",event,w);
            if(abs(mll - mZ) > 15. and met >=  50. and met < 200. and mT2l >= 0. and mT2 >=  80. and mT2 < 120.) counter_cutflow("C02",event,w);
            if(abs(mll - mZ) > 15. and met >=  50. and met < 200. and mT2l >= 0. and mT2 >= 120.) counter_cutflow("C03",event,w);
            if(abs(mll - mZ) > 15. and met >= 200. and met < 300. and mT2l >= 0. and mT2 <   80.) counter_cutflow("C04",event,w);
            if(abs(mll - mZ) > 15. and met >= 200. and met < 300. and mT2l >= 0. and mT2 >=  80. and mT2 < 120.) counter_cutflow("C05",event,w);
            if(abs(mll - mZ) > 15. and met >= 200. and met < 300. and mT2l >= 0. and mT2 >= 120.) counter_cutflow("C06",event,w);
            if(abs(mll - mZ) > 15. and met >= 300. and mT2l >=   0. and mT2l < 250.) counter_cutflow("C07",event,w);
            if(abs(mll - mZ) > 15. and met >= 300. and mT2l >= 250. and mT2l < 500.) counter_cutflow("C08",event,w);
            if(abs(mll - mZ) > 15. and met >= 300. and mT2l >= 500.) counter_cutflow("C09",event,w);
          }

          // 3Lep, no OSSF pair, 2 OS light leptons + tau (3lD)
          if(_3Lep and nTaus == 1 and nOSSFpairs == 0 and oppositeSign(signalLightLeptons.at(0), signalLightLeptons.at(1)))
          {
            // mll variable
            // Select OS pair with mass closest to the recontructed mass of Z -> tautau (50 for emu pairs and 60 for pairs with a tau)
            double mll = (OSpairs.at(0).at(0)->mom() + OSpairs.at(0).at(1)->mom()).m();
            double mlth = oppositeSign(signalTaus.at(0), signalLightLeptons.at(0)) ? (signalTaus.at(0)->mom() + signalLightLeptons.at(0)->mom()).m() :  (signalTaus.at(0)->mom() + signalLightLeptons.at(1)->mom()).m();
            if(abs(mll - 50.) > abs(mlth - 60.)) mll = mlth;


            // mT2 variable
            double mT2 = get_mT2(signalLightLeptons.at(0), signalLightLeptons.at(1), mmom, 0.);

            if(mT2 >= 0. and mT2 < 100. and mll < 60. and met >=  50. and met < 100.) counter_cutflow("D01",event,w);
            if(mT2 >= 0. and mT2 < 100. and mll < 60. and met >= 100. and met < 150.) counter_cutflow("D02",event,w);
            if(mT2 >= 0. and mT2 < 100. and mll < 60. and met >= 150. and met < 200.) counter_cutflow("D03",event,w);
            if(mT2 >= 0. and mT2 < 100. and mll < 60. and met >= 200. and met < 250.) counter_cutflow("D04",event,w);
            if(mT2 >= 0. and mT2 < 100. and mll < 60. and met >= 250.) counter_cutflow("D05",event,w);

            if(mT2 >= 0. and mT2 < 100. and mll >= 60. and mll < 100. and met >=  50. and met < 100.) counter_cutflow("D06",event,w);
            if(mT2 >= 0. and mT2 < 100. and mll >= 60. and mll < 100. and met >= 100. and met < 150.) counter_cutflow("D07",event,w);
            if(mT2 >= 0. and mT2 < 100. and mll >= 60. and mll < 100. and met >= 150. and met < 200.) counter_cutflow("D08",event,w);
            if(mT2 >= 0. and mT2 < 100. and mll >= 60. and mll < 100. and met >= 200. and met < 250.) counter_cutflow("D09",event,w);
            if(mT2 >= 0. and mT2 < 100. and mll >= 60. and mll < 100. and met >= 250.) counter_cutflow("D10",event,w);

            if(mT2 >= 0. and mT2 < 100. and mll >= 100. and met >=  50. and met < 100.) counter_cutflow("D11",event,w);
            if(mT2 >= 0. and mT2 < 100. and mll >= 100. and met >= 100. and met < 150.) counter_cutflow("D12",event,w);
            if(mT2 >= 0. and mT2 < 100. and mll >= 100. and met >= 150. and met < 200.) counter_cutflow("D13",event,w);
            if(mT2 >= 0. and mT2 < 100. and mll >= 100. and met >= 200.) counter_cutflow("D14",event,w);

            if(mT2 >= 100. and met >=  50. and met < 200.) counter_cutflow("D15",event,w);
            if(mT2 >= 100. and met >= 200.) counter_cutflow("D16",event,w);

          }

          // 3Lep, no OSSF pair, 2 SS light leptons + tau (3lE)
          if(_3Lep and nTaus == 1 and nOSSFpairs == 0 and sameSign(signalLightLeptons.at(0), signalLightLeptons.at(1)))
          {
            // mlth variable
            // Select the OS pair with mass closest to the recontructed mass of Z -> tautau (50 for emu pairs and 60 for pairs with a tau)
            double mlth1 = (signalTaus.at(0)->mom() + signalLightLeptons.at(0)->mom()).m();
            double mlth2 = (signalTaus.at(0)->mom() + signalLightLeptons.at(1)->mom()).m();
            double mlth = abs(mlth1 - 60.) < abs(mlth2 - 60.) ? mlth1 : mlth2;

            // Set mlth to zero is the tau has the same sign as the pair of light leptons
            if(sameSign(signalTaus.at(0), signalLightLeptons.at(0))) mlth = 0.;

            // mT2 varaible
            double mT2 = get_mT2(signalLightLeptons.at(0), signalTaus.at(0), mmom, 0.);

            if(mT2 >= 0. and mT2 < 80. and mlth <= 50. and met >=  50. and met < 100.) counter_cutflow("E01",event,w);
            if(mT2 >= 0. and mT2 < 80. and mlth <= 50. and met >= 100. and met < 250.) counter_cutflow("E02",event,w);
            if(mT2 >= 0. and mT2 < 80. and mlth <= 50. and met >= 250.) counter_cutflow("E03",event,w);
            if(mT2 >= 0. and mT2 < 80. and mlth >  50. and met >=  50. and met < 100.) counter_cutflow("E04",event,w);
            if(mT2 >= 0. and mT2 < 80. and mlth >  50. and met >= 100.) counter_cutflow("E05",event,w); 

            if(mT2 >= 80. and mlth <= 100. and met >=  50. and met < 150.) counter_cutflow("E06",event,w);
            if(mT2 >= 80. and mlth <= 100. and met >= 150.) counter_cutflow("E07",event,w);
            if(mT2 >= 80. and mlth >  100. and met >=  50. and met < 200.) counter_cutflow("E08",event,w);
            if(mT2 >= 80. and mlth >  100. and met >= 200.) counter_cutflow("E09",event,w);
          }

          // 3Lep, 2 tau (3lF)
          if(_3Lep and nTaus == 2)
          {
            // mlth variable
            double mlth = (signalTaus.at(0)->mom() + signalLightLeptons.at(0)->mom()).m();

            // mT2 variable
            double mT2 = get_mT2(signalTaus.at(0), signalLightLeptons.at(0), mmom, 0);

            if(mT2 >= 0. and mT2 < 100. and mlth < 100. and met >=  50. and met < 100.) counter_cutflow("F01",event,w);
            if(mT2 >= 0. and mT2 < 100. and mlth < 100. and met >= 100. and met < 150.) counter_cutflow("F02",event,w);
            if(mT2 >= 0. and mT2 < 100. and mlth < 100. and met >= 150. and met < 200.) counter_cutflow("F03",event,w);
            if(mT2 >= 0. and mT2 < 100. and mlth < 100. and met >= 200. and met < 250.) counter_cutflow("F04",event,w);
            if(mT2 >= 0. and mT2 < 100. and mlth < 100. and met >= 250. and met < 300.) counter_cutflow("F05",event,w);
            if(mT2 >= 0. and mT2 < 100. and mlth < 100. and met >= 300.) counter_cutflow("F06",event,w);

            if(mT2 >= 0. and mT2 < 100. and mlth >= 100. and met >=  50. and met < 100.) counter_cutflow("F07",event,w);
            if(mT2 >= 0. and mT2 < 100. and mlth >= 100. and met >= 100. and met < 150.) counter_cutflow("F08",event,w);
            if(mT2 >= 0. and mT2 < 100. and mlth >= 100. and met >= 150. and met < 200.) counter_cutflow("F09",event,w);
            if(mT2 >= 0. and mT2 < 100. and mlth >= 100. and met >= 200.) counter_cutflow("F10",event,w);

            if(mT2 >= 100. and met >=  50. and met < 200.) counter_cutflow("F11",event,w);
            if(mT2 >= 100. and met >= 200.) counter_cutflow("F12",event,w);
          }

          // 4Lep, 2 OSSF pairs (4lG)
          if(nLeptons == 4 and nLightLeptons == 4 and nOSSFpairs == 2)
          {
            // mT2 variable, using Z1 and Z2
            double mT2 = get_mT2(OSSFpairs.at(0).at(0)->mom() + OSSFpairs.at(0).at(1)->mom(), OSSFpairs.at(1).at(0)->mom() + OSSFpairs.at(1).at(1)->mom(), mmom, 0.);

            // Z2 invariant mass
            double mZ2 = (OSSFpairs.at(1).at(0)->mom() + OSSFpairs.at(1).at(1)->mom()).m();

            if(mT2 >=   0. and mT2 < 150.) counter_cutflow("G01",event,w);
            if(mT2 >= 150. and mT2 < 250. and mZ2 >= 60.) counter_cutflow("G02",event,w);
            if(mT2 >= 150. and mT2 < 250. and mZ2 <  60.) counter_cutflow("G03",event,w);
            if(mT2 >= 250. and mT2 < 400.) counter_cutflow("G04",event,w);
            if(mT2 >= 400) counter_cutflow("G05",event,w);
          }

          // These variables are common to all remaining SRs
          if(nLeptons == 4 and (nOSSFpairsWithTaus > 0 or nOSpairsWithTaus > 0))
          {

            // Z1 invariant mass
            std::vector<const HEPUtils::Particle*> Z1pair;
            double mZ1 = 0.;
            if(nOSSFpairsWithTaus > 0)
            {
              mZ1 = (OSSFpairsWithTaus.at(0).at(0)->mom() + OSSFpairsWithTaus.at(0).at(1)->mom()).m();
              Z1pair.push_back(OSSFpairsWithTaus.at(0).at(0));
              Z1pair.push_back(OSSFpairsWithTaus.at(0).at(1));
            }
            else
            {
              mZ1 = (OSpairsWithTaus.at(0).at(0)->mom() + OSpairsWithTaus.at(0).at(1)->mom()).m();
              Z1pair.push_back(OSpairsWithTaus.at(0).at(0));
              Z1pair.push_back(OSpairsWithTaus.at(0).at(1));
            }

            // deltaRH variable
            std::vector<const HEPUtils::Particle*> deltaRHpair;
            double deltaRH = 0.;
            for(const HEPUtils::Particle* lep : signalLeptons)
            {
              if(lep != Z1pair.at(0) && lep != Z1pair.at(1))
              {
                deltaRHpair.push_back(lep);
              }
            }
            deltaRH = deltaR_eta(deltaRHpair.at(0)->mom(), deltaRHpair.at(1)->mom());


            // 4Lep, 1 or fewer OSSF pairs (4lH)
            if(nLightLeptons == 4 and nOSSFpairsWithTaus < 2)
            {
              if(deltaRH >= 0.8 and mZ1 > 60.) counter_cutflow("H01",event,w);
              if(deltaRH >= 0.8 and mZ1 >  0. and mZ1 <= 60.) counter_cutflow("H02",event,w);
              if(deltaRH < 0.8) counter_cutflow("H03",event,w);
            }

            // 4Lep, tau + 3 light leptons (4lI)
            if(nLightLeptons == 3 and nTaus == 1)
            {
              if(deltaRH >= 0.8 and mZ1 > 60.) counter_cutflow("I01",event,w);
              if(deltaRH >= 0.8 and mZ1 >  0. and mZ1 <= 60.) counter_cutflow("I02",event,w);
              if(deltaRH < 0.8) counter_cutflow("I03",event,w);
            }

            // 4Lep, 2 tau + 2 light leptons, 2 OSSF pairs (4lJ)
            if(nLightLeptons == 2 and nTaus == 2 and nOSSFpairsWithTaus == 2)
            {
              if(deltaRH >= 0.8 and mZ1 > 60.) counter_cutflow("J01",event,w);
              if(deltaRH >= 0.8 and mZ1 >  0. and mZ1 <= 60.) counter_cutflow("J02",event,w);
              if(deltaRH < 0.8) counter_cutflow("J03",event,w);
            }

            // 4Lep, 2 tau + 2 light leptons, 1 or fewer OSSF pairs (4lK)
            if(nLightLeptons == 2 and nTaus == 2 and nOSSFpairsWithTaus < 2)
            {
              if(deltaRH >= 0.8 and mZ1 > 60.) counter_cutflow("K01",event,w);
              if(deltaRH >= 0.8 and mZ1 >  0. and mZ1 <= 60.) counter_cutflow("K02",event,w);
              if(deltaRH < 0.8) counter_cutflow("K03",event,w);
            }
          }

        }

        /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
        void combine(const Analysis* other)
        {
          const Analysis_CMS_13TeV_MultiLEP_137invfb* specificOther = dynamic_cast<const Analysis_CMS_13TeV_MultiLEP_137invfb*>(other);
          for (auto& pair : _counters) { pair.second += specificOther->_counters.at(pair.first); }
        }

        virtual void collect_results()
        {

          //Now fill a results object with the results for each SR
          // TODO: This is just approximated from the plots, as there is no public data available

          // 2SSLep (2lSS)
          add_result(SignalRegionData(_counters.at("SS01"), 680., {680., 80.}));
          add_result(SignalRegionData(_counters.at("SS02"), 400., {360., 80.}));
          add_result(SignalRegionData(_counters.at("SS03"), 26., {23., 5.}));
          add_result(SignalRegionData(_counters.at("SS04"), 19., {12., 5.}));
          add_result(SignalRegionData(_counters.at("SS05"), 9.5, {6., 2.}));
          add_result(SignalRegionData(_counters.at("SS06"), 1.9, {2., 1.75}));
          add_result(SignalRegionData(_counters.at("SS07"), 700., {650., 80.}));
          add_result(SignalRegionData(_counters.at("SS08"), 600., {550., 80.}));
          add_result(SignalRegionData(_counters.at("SS09"), 1.9, {1.7, 0.8}));
          add_result(SignalRegionData(_counters.at("SS10"), 4100., {4300., 400.}));
          add_result(SignalRegionData(_counters.at("SS11"), 97., {100., 11.}));
          add_result(SignalRegionData(_counters.at("SS12"), 93., {80., 10.}));
          add_result(SignalRegionData(_counters.at("SS13"), 63., {50., 7.5}));
          add_result(SignalRegionData(_counters.at("SS14"), 2.8, {2.3, 1.3}));
          add_result(SignalRegionData(_counters.at("SS15"), 2.9, {0.7, 0.56}));
          add_result(SignalRegionData(_counters.at("SS16"), 10., {13., 3.5}));
          add_result(SignalRegionData(_counters.at("SS17"), 9.5, {3.9, 2.3}));
          add_result(SignalRegionData(_counters.at("SS18"), 5.8, {4., 1.6}));
          add_result(SignalRegionData(_counters.at("SS19"), 5.8, {3.7, 1.2}));
          add_result(SignalRegionData(_counters.at("SS20"), 5.8, {3.9, 1.6}));

          // 3Lep, OSSF pair (3lA)
          add_result(SignalRegionData(_counters.at("A01"), 242., {250., 25.}));
          add_result(SignalRegionData(_counters.at("A02"), 250., {235., 35.}));
          add_result(SignalRegionData(_counters.at("A03"), 280., {260., 35.}));
          add_result(SignalRegionData(_counters.at("A04"), 215., {195., 35.}));
          add_result(SignalRegionData(_counters.at("A05"), 35., {33., 5.5}));
          add_result(SignalRegionData(_counters.at("A06"), 960., {900., 100.}));
          add_result(SignalRegionData(_counters.at("A07"), 390., {360., 55.}));
          add_result(SignalRegionData(_counters.at("A08"), 7., {5.8, 1.6}));
          add_result(SignalRegionData(_counters.at("A09"), 207., {215., 40.}));
          add_result(SignalRegionData(_counters.at("A10"), 27., {20., 4.}));
          add_result(SignalRegionData(_counters.at("A11"), 37., {27., 6.}));
          add_result(SignalRegionData(_counters.at("A12"), 1., {3., 1.}));
          add_result(SignalRegionData(_counters.at("A13"), 620., {580., 80.}));
          add_result(SignalRegionData(_counters.at("A14"), 9., {13., 3.}));
          add_result(SignalRegionData(_counters.at("A15"), 160., {150., 20.}));
          add_result(SignalRegionData(_counters.at("A16"), 27., {24., 5.}));
          add_result(SignalRegionData(_counters.at("A17"), 29., {33., 5.5}));
          add_result(SignalRegionData(_counters.at("A18"), 1., {4.8, 1.2}));
          add_result(SignalRegionData(_counters.at("A19"), 60., {53., 9.}));
          add_result(SignalRegionData(_counters.at("A20"), 2.9, {2.9, 0.9}));
          add_result(SignalRegionData(_counters.at("A21"), 27., {18., 4.}));
          add_result(SignalRegionData(_counters.at("A22"), 9., {6.5, 1.5}));
          add_result(SignalRegionData(_counters.at("A23"), 7300., {7000., 1200.}));
          add_result(SignalRegionData(_counters.at("A24"), 1000., {1000., 200.}));
          add_result(SignalRegionData(_counters.at("A25"), 200., {200., 40.}));
          add_result(SignalRegionData(_counters.at("A26"), 62., {63., 11.}));
          add_result(SignalRegionData(_counters.at("A27"), 35., {43., 9.}));
          add_result(SignalRegionData(_counters.at("A28"), 1250., {1210., 200.}));
          add_result(SignalRegionData(_counters.at("A29"), 270., {230., 50.}));
          add_result(SignalRegionData(_counters.at("A30"), 25., {20.5, 4.5}));
          add_result(SignalRegionData(_counters.at("A31"), 6., {5.4, 1.7}));
          add_result(SignalRegionData(_counters.at("A32"), 112., {77., 16.}));
          add_result(SignalRegionData(_counters.at("A33"), 49., {56, 12.}));
          add_result(SignalRegionData(_counters.at("A34"), 18., {15.5, 3.5}));
          add_result(SignalRegionData(_counters.at("A35"), 15., {12., 2.5}));
          add_result(SignalRegionData(_counters.at("A36"), 1150., {1150., 200.}));
          add_result(SignalRegionData(_counters.at("A37"), 350., {350., 60.}));
          add_result(SignalRegionData(_counters.at("A38"), 100., {98., 17.}));
          add_result(SignalRegionData(_counters.at("A39"), 29., {30., 6.}));
          add_result(SignalRegionData(_counters.at("A40"), 15., {21., 4.}));
          add_result(SignalRegionData(_counters.at("A41"), 230., {215., 40.}));
          add_result(SignalRegionData(_counters.at("A42"), 70., {54., 13.}));
          add_result(SignalRegionData(_counters.at("A43"), 12., {11., 2.}));
          add_result(SignalRegionData(_counters.at("A44"), 4., {2.7, 1.1}));
          add_result(SignalRegionData(_counters.at("A45"), 35., {32., 7.}));
          add_result(SignalRegionData(_counters.at("A46"), 9., {10.5, 4.}));
          add_result(SignalRegionData(_counters.at("A47"), 4., {5.8, 1.6}));
          add_result(SignalRegionData(_counters.at("A48"), 10., {3.4, 0.9}));
          add_result(SignalRegionData(_counters.at("A49"), 1250., {1130., 170.}));
          add_result(SignalRegionData(_counters.at("A50"), 300., {290., 50.}));
          add_result(SignalRegionData(_counters.at("A51"), 76., {82.5, 17.5}));
          add_result(SignalRegionData(_counters.at("A52"), 36., {43., 9.}));
          add_result(SignalRegionData(_counters.at("A53"), 199., {155., 30.}));
          add_result(SignalRegionData(_counters.at("A54"), 63., {55., 11.}));
          add_result(SignalRegionData(_counters.at("A55"), 26., {18., 3.}));
          add_result(SignalRegionData(_counters.at("A56"), 12., {8., 2.2}));
          add_result(SignalRegionData(_counters.at("A57"), 1., {2.5, 1.}));
          add_result(SignalRegionData(_counters.at("A58"), 3., {4.2, 1.4}));
          add_result(SignalRegionData(_counters.at("A59"), 52., {38., 7.}));
          add_result(SignalRegionData(_counters.at("A60"), 20, {16.5, 4.}));
          add_result(SignalRegionData(_counters.at("A61"), 7., {7., 1.5}));
          add_result(SignalRegionData(_counters.at("A62"), 2., {4.1, 1.3}));
          add_result(SignalRegionData(_counters.at("A63"), 2., {1.7, 0.45}));
          add_result(SignalRegionData(_counters.at("A64"), 3., {5.5, 1.8}));

          // 3Lep, no OSSF pair (3lB)
          add_result(SignalRegionData(_counters.at("B01"), 14., {8.2, 1.6}));
          add_result(SignalRegionData(_counters.at("B02"), 110., {110., 25.}));
          add_result(SignalRegionData(_counters.at("B03"), 327, {322., 83.}));

          // 3Lep, OSSF pair + tau (3lC)
          add_result(SignalRegionData(_counters.at("C01"), 3850., {4180., 1640.}));
          add_result(SignalRegionData(_counters.at("C02"), 167., {190., 70.}));
          add_result(SignalRegionData(_counters.at("C03"), 20., {23., 6.}));
          add_result(SignalRegionData(_counters.at("C04"), 42., {34., 13.}));
          add_result(SignalRegionData(_counters.at("C05"), 3., {4.4, 1.7}));
          add_result(SignalRegionData(_counters.at("C06"), 5., {5.3, 1.4}));
          add_result(SignalRegionData(_counters.at("C07"), 7., {9., 3.5}));
          add_result(SignalRegionData(_counters.at("C08"), 1., {2.1, 1.}));
          add_result(SignalRegionData(_counters.at("C09"), 4., {3.4, 1.1}));

          // 3Lep, no OSSF pair, 2 OS light leptons + tau (3lD)
          add_result(SignalRegionData(_counters.at("D01"), 680., {666., 254.}));
          add_result(SignalRegionData(_counters.at("D02"), 280., {230., 90.}));
          add_result(SignalRegionData(_counters.at("D03"), 72., {49., 19.}));
          add_result(SignalRegionData(_counters.at("D04"), 13., {17., 6.}));
          add_result(SignalRegionData(_counters.at("D05"), 11., {13., 5.}));
          add_result(SignalRegionData(_counters.at("D06"), 600., {570., 230.}));
          add_result(SignalRegionData(_counters.at("D07"), 225., {200., 90.}));
          add_result(SignalRegionData(_counters.at("D08"), 47., {55., 21.}));
          add_result(SignalRegionData(_counters.at("D09"), 8., {13., 5.}));
          add_result(SignalRegionData(_counters.at("D10"), 6., {6.8, 2.5}));
          add_result(SignalRegionData(_counters.at("D11"), 200., {190., 70.}));
          add_result(SignalRegionData(_counters.at("D12"), 63., {70., 28.}));
          add_result(SignalRegionData(_counters.at("D13"), 20., {24., 9.}));
          add_result(SignalRegionData(_counters.at("D14"), 7., {13., 4.}));
          add_result(SignalRegionData(_counters.at("D15"), 20., {17., 6.}));
          add_result(SignalRegionData(_counters.at("D16"), 1., {1.13, 0.47}));

          // 3Lep, no OSSF pair, 2 SS light leptons + tau (3lE)
          add_result(SignalRegionData(_counters.at("E01"), 60., {70., 17.}));
          add_result(SignalRegionData(_counters.at("E02"), 28., {22., 3.}));
          add_result(SignalRegionData(_counters.at("E03"), 1., {2.2, 0.8}));
          add_result(SignalRegionData(_counters.at("E04"), 362., {345., 75.}));
          add_result(SignalRegionData(_counters.at("E05"), 108., {95., 18.}));
          add_result(SignalRegionData(_counters.at("E06"), 25., {19., 4.}));
          add_result(SignalRegionData(_counters.at("E07"), 5., {6., 1.6}));
          add_result(SignalRegionData(_counters.at("E08"), 15., {14., 4.}));
          add_result(SignalRegionData(_counters.at("E09"), 1., {1., 0.5}));

          // 3Lep, 2 tau (3lF)
          add_result(SignalRegionData(_counters.at("F01"), 1060., {1170., 400.}));
          add_result(SignalRegionData(_counters.at("F02"), 177., {190., 70.}));
          add_result(SignalRegionData(_counters.at("F03"), 40., {36., 13.}));
          add_result(SignalRegionData(_counters.at("F04"), 9., {9.5, 3.5}));
          add_result(SignalRegionData(_counters.at("F05"), 3., {2., 1.}));
          add_result(SignalRegionData(_counters.at("F06"), 4., {2.6, 1.2}));
          add_result(SignalRegionData(_counters.at("F07"), 585., {600., 200.}));
          add_result(SignalRegionData(_counters.at("F08"), 125., {130., 58.}));
          add_result(SignalRegionData(_counters.at("F09"), 33., {37., 14.}));
          add_result(SignalRegionData(_counters.at("F10"), 19., {17., 6.}));
          add_result(SignalRegionData(_counters.at("F11"), 18., {23., 6.}));
          add_result(SignalRegionData(_counters.at("F12"), 2., {3.5, 1.4}));

          // 4Lep, 2 OSSF pairs (4lG)
          add_result(SignalRegionData(_counters.at("G01"), 370., {365., 30.}));
          add_result(SignalRegionData(_counters.at("G02"), 15., {18.5, 2.}));
          add_result(SignalRegionData(_counters.at("G03"), 6., {6.7, 1.2}));
          add_result(SignalRegionData(_counters.at("G04"), 0., {1.7, 0.8}));
          add_result(SignalRegionData(_counters.at("G05"), 0., {0., 0.}));

          // 4Lep, 1 or fewer OSSF pairs (4lH)
          add_result(SignalRegionData(_counters.at("H01"), 49., {41.7, 5.}));
          add_result(SignalRegionData(_counters.at("H02"), 4., {3., 1.}));
          add_result(SignalRegionData(_counters.at("H03"), 3., {4.3, 0.9}));

          // 4Lep, tau + 3 light leptons (4lI)
          add_result(SignalRegionData(_counters.at("I01"), 92., {96., 17.}));
          add_result(SignalRegionData(_counters.at("I02"), 14., {10., 3.}));
          add_result(SignalRegionData(_counters.at("I03"), 7., {9.4, 1.6}));

          // 4Lep, 2 tau + 2 light leptons, 2 OSSF pairs (4lJ)
          add_result(SignalRegionData(_counters.at("J01"), 34., {35.5, 8.5}));
          add_result(SignalRegionData(_counters.at("J02"), 6., {10.7, 4.3}));
          add_result(SignalRegionData(_counters.at("J03"), 4., {4.3, 1.2}));

          // 4Lep, 2 tau + 2 light leptons, 1 or fewer OSSF pairs (4lK)
          add_result(SignalRegionData(_counters.at("K01"), 8., {16., 6.5}));
          add_result(SignalRegionData(_counters.at("K02"), 5., {5.2, 2.45}));
          add_result(SignalRegionData(_counters.at("K03"), 1., {0.61, 0.61}));

          // Cutflow printout
          #ifdef CHECK_CUTFLOW
            //const double xsec = 5180.86; // 150 GeV winos
            const double xsec = 3832.31; // 150 GeV higgsinos
            //const double xsec = 1165.09; // 225 GeV winos
            // const double xsec = 284.855; // 300 GeV higgsinos
            //const double xsec = 121.013; // 400 GeV winos
            //const double xsec = 46.3533; // 500 GeV winos
            //const double xsec = 20.1372; // 600 GeV winos
            //const double xsec = 2.49667; // 900 GeV winos
            //const double xsec = 0.415851; // 1200 GeV winos
            const double sf = 137*xsec;
            _cutflows.normalize(sf);
            cout << "\nCUTFLOWS:\n" << _cutflows << endl;
            cout << "\nSRCOUNTS:\n";
            for (auto& pair : _counters) cout << pair.second.weight_sum() << "  ";
            cout << "\n" << endl;
          #endif
        }

      protected:

        void analysis_specific_reset()
        {
          for (auto& pair : _counters) { pair.second.reset(); }
        }


    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_MultiLEP_137invfb)

    // Subset of analysis with only 2lSS SRs
    class Analysis_CMS_13TeV_MultiLEP_2LEP_137invfb : public Analysis_CMS_13TeV_MultiLEP_137invfb
    {

      public:

        Analysis_CMS_13TeV_MultiLEP_2LEP_137invfb()
        {
          set_analysis_name("CMS_13TeV_MultiLEP_2LEP_137invfb");
        }

        virtual void collect_results()
        {
          // 2SSLep (2lSS)
          add_result(SignalRegionData(_counters.at("SS01"), 680., {680., 80.}));
          add_result(SignalRegionData(_counters.at("SS02"), 400., {360., 80.}));
          add_result(SignalRegionData(_counters.at("SS03"), 26., {23., 5.}));
          add_result(SignalRegionData(_counters.at("SS04"), 19., {12., 5.}));
          add_result(SignalRegionData(_counters.at("SS05"), 9.5, {6., 2.}));
          add_result(SignalRegionData(_counters.at("SS06"), 1.9, {2., 1.75}));
          add_result(SignalRegionData(_counters.at("SS07"), 700., {650., 80.}));
          add_result(SignalRegionData(_counters.at("SS08"), 600., {550., 80.}));
          add_result(SignalRegionData(_counters.at("SS09"), 1.9, {1.7, 0.8}));
          add_result(SignalRegionData(_counters.at("SS10"), 4100., {4300., 400.}));
          add_result(SignalRegionData(_counters.at("SS11"), 97., {100., 11.}));
          add_result(SignalRegionData(_counters.at("SS12"), 93., {80., 10.}));
          add_result(SignalRegionData(_counters.at("SS13"), 63., {50., 7.5}));
          add_result(SignalRegionData(_counters.at("SS14"), 2.8, {2.3, 1.3}));
          add_result(SignalRegionData(_counters.at("SS15"), 2.9, {0.7, 0.56}));
          add_result(SignalRegionData(_counters.at("SS16"), 10., {13., 3.5}));
          add_result(SignalRegionData(_counters.at("SS17"), 9.5, {3.9, 2.3}));
          add_result(SignalRegionData(_counters.at("SS18"), 5.8, {4., 1.6}));
          add_result(SignalRegionData(_counters.at("SS19"), 5.8, {3.7, 1.2}));
          add_result(SignalRegionData(_counters.at("SS20"), 5.8, {3.9, 1.6}));
        }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_MultiLEP_2LEP_137invfb)

    // Subset of analysis with only 3l (no taus)SRs
    class Analysis_CMS_13TeV_MultiLEP_3LEP_137invfb : public Analysis_CMS_13TeV_MultiLEP_137invfb
    {

      public:

        Analysis_CMS_13TeV_MultiLEP_3LEP_137invfb()
        {
          set_analysis_name("CMS_13TeV_MultiLEP_3LEP_137invfb");
        }

        virtual void collect_results()
        {
          // 3Lep, OSSF pair (3lA)
          add_result(SignalRegionData(_counters.at("A01"), 242., {250., 25.}));
          add_result(SignalRegionData(_counters.at("A02"), 250., {235., 35.}));
          add_result(SignalRegionData(_counters.at("A03"), 280., {260., 35.}));
          add_result(SignalRegionData(_counters.at("A04"), 215., {195., 35.}));
          add_result(SignalRegionData(_counters.at("A05"), 35., {33., 5.5}));
          add_result(SignalRegionData(_counters.at("A06"), 960., {900., 100.}));
          add_result(SignalRegionData(_counters.at("A07"), 390., {360., 55.}));
          add_result(SignalRegionData(_counters.at("A08"), 7., {5.8, 1.6}));
          add_result(SignalRegionData(_counters.at("A09"), 207., {215., 40.}));
          add_result(SignalRegionData(_counters.at("A10"), 27., {20., 4.}));
          add_result(SignalRegionData(_counters.at("A11"), 37., {27., 6.}));
          add_result(SignalRegionData(_counters.at("A12"), 1., {3., 1.}));
          add_result(SignalRegionData(_counters.at("A13"), 620., {580., 80.}));
          add_result(SignalRegionData(_counters.at("A14"), 9., {13., 3.}));
          add_result(SignalRegionData(_counters.at("A15"), 160., {150., 20.}));
          add_result(SignalRegionData(_counters.at("A16"), 27., {24., 5.}));
          add_result(SignalRegionData(_counters.at("A17"), 29., {33., 5.5}));
          add_result(SignalRegionData(_counters.at("A18"), 1., {4.8, 1.2}));
          add_result(SignalRegionData(_counters.at("A19"), 60., {53., 9.}));
          add_result(SignalRegionData(_counters.at("A20"), 2.9, {2.9, 0.9}));
          add_result(SignalRegionData(_counters.at("A21"), 27., {18., 4.}));
          add_result(SignalRegionData(_counters.at("A22"), 9., {6.5, 1.5}));
          add_result(SignalRegionData(_counters.at("A23"), 7300., {7000., 1200.}));
          add_result(SignalRegionData(_counters.at("A24"), 1000., {1000., 200.}));
          add_result(SignalRegionData(_counters.at("A25"), 200., {200., 40.}));
          add_result(SignalRegionData(_counters.at("A26"), 62., {63., 11.}));
          add_result(SignalRegionData(_counters.at("A27"), 35., {43., 9.}));
          add_result(SignalRegionData(_counters.at("A28"), 1250., {1210., 200.}));
          add_result(SignalRegionData(_counters.at("A29"), 270., {230., 50.}));
          add_result(SignalRegionData(_counters.at("A30"), 25., {20.5, 4.5}));
          add_result(SignalRegionData(_counters.at("A31"), 6., {5.4, 1.7}));
          add_result(SignalRegionData(_counters.at("A32"), 112., {77., 16.}));
          add_result(SignalRegionData(_counters.at("A33"), 49., {56, 12.}));
          add_result(SignalRegionData(_counters.at("A34"), 18., {15.5, 3.5}));
          add_result(SignalRegionData(_counters.at("A35"), 15., {12., 2.5}));
          add_result(SignalRegionData(_counters.at("A36"), 1150., {1150., 200.}));
          add_result(SignalRegionData(_counters.at("A37"), 350., {350., 60.}));
          add_result(SignalRegionData(_counters.at("A38"), 100., {98., 17.}));
          add_result(SignalRegionData(_counters.at("A39"), 29., {30., 6.}));
          add_result(SignalRegionData(_counters.at("A40"), 15., {21., 4.}));
          add_result(SignalRegionData(_counters.at("A41"), 230., {215., 40.}));
          add_result(SignalRegionData(_counters.at("A42"), 70., {54., 13.}));
          add_result(SignalRegionData(_counters.at("A43"), 12., {11., 2.}));
          add_result(SignalRegionData(_counters.at("A44"), 4., {2.7, 1.1}));
          add_result(SignalRegionData(_counters.at("A45"), 35., {32., 7.}));
          add_result(SignalRegionData(_counters.at("A46"), 9., {10.5, 4.}));
          add_result(SignalRegionData(_counters.at("A47"), 4., {5.8, 1.6}));
          add_result(SignalRegionData(_counters.at("A48"), 10., {3.4, 0.9}));
          add_result(SignalRegionData(_counters.at("A49"), 1250., {1130., 170.}));
          add_result(SignalRegionData(_counters.at("A50"), 300., {290., 50.}));
          add_result(SignalRegionData(_counters.at("A51"), 76., {82.5, 17.5}));
          add_result(SignalRegionData(_counters.at("A52"), 36., {43., 9.}));
          add_result(SignalRegionData(_counters.at("A53"), 199., {155., 30.}));
          add_result(SignalRegionData(_counters.at("A54"), 63., {55., 11.}));
          add_result(SignalRegionData(_counters.at("A55"), 26., {18., 3.}));
          add_result(SignalRegionData(_counters.at("A56"), 12., {8., 2.2}));
          add_result(SignalRegionData(_counters.at("A57"), 1., {2.5, 1.}));
          add_result(SignalRegionData(_counters.at("A58"), 3., {4.2, 1.4}));
          add_result(SignalRegionData(_counters.at("A59"), 52., {38., 7.}));
          add_result(SignalRegionData(_counters.at("A60"), 20, {16.5, 4.}));
          add_result(SignalRegionData(_counters.at("A61"), 7., {7., 1.5}));
          add_result(SignalRegionData(_counters.at("A62"), 2., {4.1, 1.3}));
          add_result(SignalRegionData(_counters.at("A63"), 2., {1.7, 0.45}));
          add_result(SignalRegionData(_counters.at("A64"), 3., {5.5, 1.8}));

          // 3Lep, no OSSF pair (3lB)
          add_result(SignalRegionData(_counters.at("B01"), 14., {8.2, 1.6}));
          add_result(SignalRegionData(_counters.at("B02"), 110., {110., 25.}));
          add_result(SignalRegionData(_counters.at("B03"), 327, {322., 83.}));
        }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_MultiLEP_3LEP_137invfb)

    // Subset of analysis with only 3l (with taus)SRs
    class Analysis_CMS_13TeV_MultiLEP_3LEPTau_137invfb : public Analysis_CMS_13TeV_MultiLEP_137invfb
    {

      public:

        Analysis_CMS_13TeV_MultiLEP_3LEPTau_137invfb()
        {
          set_analysis_name("CMS_13TeV_MultiLEP_3LEPTau_137invfb");
        }

        virtual void collect_results()
        {
          // 3Lep, OSSF pair + tau (3lC)
          add_result(SignalRegionData(_counters.at("C01"), 3850., {4180., 1640.}));
          add_result(SignalRegionData(_counters.at("C02"), 167., {190., 70.}));
          add_result(SignalRegionData(_counters.at("C03"), 20., {23., 6.}));
          add_result(SignalRegionData(_counters.at("C04"), 42., {34., 13.}));
          add_result(SignalRegionData(_counters.at("C05"), 3., {4.4, 1.7}));
          add_result(SignalRegionData(_counters.at("C06"), 5., {5.3, 1.4}));
          add_result(SignalRegionData(_counters.at("C07"), 7., {9., 3.5}));
          add_result(SignalRegionData(_counters.at("C08"), 1., {2.1, 1.}));
          add_result(SignalRegionData(_counters.at("C09"), 4., {3.4, 1.1}));

          // 3Lep, no OSSF pair, 2 OS light leptons + tau (3lD)
          add_result(SignalRegionData(_counters.at("D01"), 680., {666., 254.}));
          add_result(SignalRegionData(_counters.at("D02"), 280., {230., 90.}));
          add_result(SignalRegionData(_counters.at("D03"), 72., {49., 19.}));
          add_result(SignalRegionData(_counters.at("D04"), 13., {17., 6.}));
          add_result(SignalRegionData(_counters.at("D05"), 11., {13., 5.}));
          add_result(SignalRegionData(_counters.at("D06"), 600., {570., 230.}));
          add_result(SignalRegionData(_counters.at("D07"), 225., {200., 90.}));
          add_result(SignalRegionData(_counters.at("D08"), 47., {55., 21.}));
          add_result(SignalRegionData(_counters.at("D09"), 8., {13., 5.}));
          add_result(SignalRegionData(_counters.at("D10"), 6., {6.8, 2.5}));
          add_result(SignalRegionData(_counters.at("D11"), 200., {190., 70.}));
          add_result(SignalRegionData(_counters.at("D12"), 63., {70., 28.}));
          add_result(SignalRegionData(_counters.at("D13"), 20., {24., 9.}));
          add_result(SignalRegionData(_counters.at("D14"), 7., {13., 4.}));
          add_result(SignalRegionData(_counters.at("D15"), 20., {17., 6.}));
          add_result(SignalRegionData(_counters.at("D16"), 1., {1.13, 0.47}));

          // 3Lep, no OSSF pair, 2 SS light leptons + tau (3lE)
          add_result(SignalRegionData(_counters.at("E01"), 60., {70., 17.}));
          add_result(SignalRegionData(_counters.at("E02"), 28., {22., 3.}));
          add_result(SignalRegionData(_counters.at("E03"), 1., {2.2, 0.8}));
          add_result(SignalRegionData(_counters.at("E04"), 362., {345., 75.}));
          add_result(SignalRegionData(_counters.at("E05"), 108., {95., 18.}));
          add_result(SignalRegionData(_counters.at("E06"), 25., {19., 4.}));
          add_result(SignalRegionData(_counters.at("E07"), 5., {6., 1.6}));
          add_result(SignalRegionData(_counters.at("E08"), 15., {14., 4.}));
          add_result(SignalRegionData(_counters.at("E09"), 1., {1., 0.5}));

          // 3Lep, 2 tau (3lF)
          add_result(SignalRegionData(_counters.at("F01"), 1060., {1170., 400.}));
          add_result(SignalRegionData(_counters.at("F02"), 177., {190., 70.}));
          add_result(SignalRegionData(_counters.at("F03"), 40., {36., 13.}));
          add_result(SignalRegionData(_counters.at("F04"), 9., {9.5, 3.5}));
          add_result(SignalRegionData(_counters.at("F05"), 3., {2., 1.}));
          add_result(SignalRegionData(_counters.at("F06"), 4., {2.6, 1.2}));
          add_result(SignalRegionData(_counters.at("F07"), 585., {600., 200.}));
          add_result(SignalRegionData(_counters.at("F08"), 125., {130., 58.}));
          add_result(SignalRegionData(_counters.at("F09"), 33., {37., 14.}));
          add_result(SignalRegionData(_counters.at("F10"), 19., {17., 6.}));
          add_result(SignalRegionData(_counters.at("F11"), 18., {23., 6.}));
          add_result(SignalRegionData(_counters.at("F12"), 2., {3.5, 1.4}));
        }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_MultiLEP_3LEPTau_137invfb)

    // Subset of analysis with only 4l (no taus) SRs
    class Analysis_CMS_13TeV_MultiLEP_4LEP_137invfb : public Analysis_CMS_13TeV_MultiLEP_137invfb
    {

      public:

        Analysis_CMS_13TeV_MultiLEP_4LEP_137invfb()
        {
          set_analysis_name("CMS_13TeV_MultiLEP_4LEP_137invfb");
        }

        virtual void collect_results()
        {
          // 4Lep, 2 OSSF pairs (4lG)
          add_result(SignalRegionData(_counters.at("G01"), 370., {365., 30.}));
          add_result(SignalRegionData(_counters.at("G02"), 15., {18.5, 2.}));
          add_result(SignalRegionData(_counters.at("G03"), 6., {6.7, 1.2}));
          add_result(SignalRegionData(_counters.at("G04"), 0., {1.7, 0.8}));
          add_result(SignalRegionData(_counters.at("G05"), 0., {0., 0.}));

          // 4Lep, 1 or fewer OSSF pairs (4lH)
          add_result(SignalRegionData(_counters.at("H01"), 49., {41.7, 5.}));
          add_result(SignalRegionData(_counters.at("H02"), 4., {3., 1.}));
          add_result(SignalRegionData(_counters.at("H03"), 3., {4.3, 0.9}));
        }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_MultiLEP_4LEP_137invfb)

     // Subset of analysis with only 4l (with taus) SRs
    class Analysis_CMS_13TeV_MultiLEP_4LEPTau_137invfb : public Analysis_CMS_13TeV_MultiLEP_137invfb
    {

      public:

        Analysis_CMS_13TeV_MultiLEP_4LEPTau_137invfb()
        {
          set_analysis_name("CMS_13TeV_MultiLEP_4LEPTau_137invfb");
        }

        virtual void collect_results()
        {
          // 4Lep, tau + 3 light leptons (4lI)
          add_result(SignalRegionData(_counters.at("I01"), 92., {96., 17.}));
          add_result(SignalRegionData(_counters.at("I02"), 14., {10., 3.}));
          add_result(SignalRegionData(_counters.at("I03"), 7., {9.4, 1.6}));

          // 4Lep, 2 tau + 2 light leptons, 2 OSSF pairs (4lJ)
          add_result(SignalRegionData(_counters.at("J01"), 34., {35.5, 8.5}));
          add_result(SignalRegionData(_counters.at("J02"), 6., {10.7, 4.3}));
          add_result(SignalRegionData(_counters.at("J03"), 4., {4.3, 1.2}));

          // 4Lep, 2 tau + 2 light leptons, 1 or fewer OSSF pairs (4lK)
          add_result(SignalRegionData(_counters.at("K01"), 8., {16., 6.5}));
          add_result(SignalRegionData(_counters.at("K02"), 5., {5.2, 2.45}));
          add_result(SignalRegionData(_counters.at("K03"), 1., {0.61, 0.61}));
        }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_MultiLEP_4LEPTau_137invfb)
   
  }
}
