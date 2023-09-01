///
///  \author Tomas Gonzalo
///  \date 2023 Aug
///
///  *********************************************

// Based on https://cms-results.web.cern.ch/cms-results/public-results/publications/SUS-18-004/index.html

#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>
#include <fstream>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/analyses/AnalysisMacros.hpp"
#include "gambit/ColliderBit/CMSEfficiencies.hpp"

using namespace std;

namespace Gambit
{
  namespace ColliderBit
  {

    class Analysis_CMS_13TeV_2LEPsoft_137invfb : public Analysis
    {

    public:

      // Required detector sim
      static constexpr const char* detector = "CMS";

      Analysis_CMS_13TeV_2LEPsoft_137invfb()
      {
        DEFINE_SIGNAL_REGIONS("2lEW",19, "Test")
        DEFINE_SIGNAL_REGIONS("3lEW", 9)
        DEFINE_SIGNAL_REGIONS("2lST",24)

        set_analysis_name("CMS_13TeV_2LEPsoft_137invfb");
        set_luminosity(35.9);
      }

      void run(const HEPUtils::Event* event)
      {

        //////////////////////
        // Baseline objects //

        static long count = 0;
        count++;

        static long count1 = 0, count2 = 0, count3 = 0;

        int nleptons = event->electrons().size() + event->muons().size();

        if(nleptons == 1)  count1 ++;
        if(nleptons == 2)  count2 ++;
        if(nleptons == 3)  count3 ++;

//        if(!(count%1000)) std::cout << "number of events with 1 electron = " << count1 << std::endl;
//        if(!(count%1000)) std::cout << "number of events with 2 electrons = " << count2 << std::endl;
//        if(!(count%1000)) std::cout << "number of events with 3 electrons = " << count3 << std::endl;

        // TODO: Unsure on what to do about electron and muon efficiencies
        BASELINE_PARTICLES(electrons, baselineElectrons, 5., 0., 30., 2.5, CMS::eff2DEl.at("SUS-18-004"))
        BASELINE_PARTICLES(muons, baselineMuons, 3.5, 0., 30., 2.4, CMS::eff2DMu.at("SUS-18-004"))
        BASELINE_JETS(jets, baselineJets, 25., 0., DBL_MAX, 2.4)
        BASELINE_BJETS(jets, baselineBJets, 25., 0., DBL_MAX, 2.4, CMS::eff2DBJet.at("DeepCSVMedium"), CMS::missIDBJet.at("DeepCSVMedium"))

        static long bcount1 = 0, bcount2 = 0, bcount3 = 0;

        int nbleptons = baselineElectrons.size() + baselineMuons.size();

        if(nbleptons == 1)  bcount1 ++;
        if(nbleptons == 2)  bcount2 ++;
        if(nbleptons == 3)  bcount3 ++;

//        if(!(count%1000)) std::cout << "number of events with 1 electron = " << bcount1 << std::endl;
//        if(!(count%1000)) std::cout << "number of events with 2 electrons = " << bcount2 << std::endl;
//        if(!(count%1000)) std::cout << "number of events with 3 electrons = " << bcount3 << std::endl;


        // Remove overlaps
        // TODO: I don't understand the isolation criteria, so don't apply it

        ////////////////////
        // Signal objects //
        SIGNAL_PARTICLES(baselineElectrons, signalElectrons)
        SIGNAL_PARTICLES(baselineMuons, signalMuons)
        SIGNAL_PARTICLE_COMBINATION(signalLeptons, signalElectrons, signalMuons)
        SIGNAL_JETS(baselineJets, signalJets)
        SIGNAL_JETS(baselineBJets, signalBJets)

        // Pairs containers
        // - OS pairs, unique and ordered from lowest invariant mass
        std::vector<std::vector<const HEPUtils::Particle*> > OSpairs = getOSpairs(signalLeptons);
        uniquePairs(OSpairs);
        sortByParentMass(OSpairs, 0);

        // - OSSF pairs, unique and ordered from lowest invariant mass
        std::vector<std::vector<const HEPUtils::Particle*> > OSSFpairs = getSFOSpairs(signalLeptons);
        uniquePairs(OSSFpairs);
        sortByParentMass(OSSFpairs, 0);

        // - SF pairs, unique and ordered from highest invariant mass
        std::vector<std::vector<const HEPUtils::Particle*> > SFpairs = getSFpairs(signalLeptons);
        uniquePairs(SFpairs);
        sortByParentMass(SFpairs, DBL_MAX);


        ///////////////////////////////
        // Common variables and cuts //

        double met = event->met();
        P4 mmom = event->missingmom();

        size_t nSignalLeptons = signalLeptons.size();
        size_t nSignalMuons = signalMuons.size();
        size_t nSignalBJets = signalBJets.size();
        size_t nOSpairs = OSpairs.size();
        size_t nOSSFpairs = OSSFpairs.size();
        size_t nSFpairs = SFpairs.size();

        // Muon corrected ETmiss
        double metcorr = met;
        for(auto& muon : signalMuons)
          metcorr += sqrt(muon->mom().px() * muon->mom().px() + muon->mom().py() * muon->mom().py());

        // Invariant mass of the lowest-mass OS dilepton pair
        double mllOS = 0.;
        if(nOSpairs > 0) mllOS = (OSpairs.at(0).at(0)->mom() + OSpairs.at(0).at(1)->mom()).m();

        // Invariant mass of the lowest-mass OSSF dilepton pair
        double mllOSSF = 0.;
        if(nOSSFpairs > 0) mllOSSF = (OSSFpairs.at(0).at(0)->mom() + OSSFpairs.at(0).at(1)->mom()).m();

        // Invariant mass of the highest-mass SF dilepton pair
        double mllSF = 0.;
        if(nSFpairs > 0) mllSF = (SFpairs.at(0).at(0)->mom() + SFpairs.at(0).at(1)->mom()).m();

        // Transverse momentum of the lepton pair, only relevant for two leptons
        double pTll = 0.;
        if(nSignalLeptons == 2) pTll = (signalLeptons.at(0)->mom() + signalLeptons.at(1)->mom()).pT();

        // Scalar sum of transverse hadronic energy
        double HT = 0.;
        for (auto& jet: signalJets)
          HT += jet->pT();

        // Veto events with invariant mass in the Y-meson or J/psi-meson mass range
        // Need this computed using the OS and OSSF pairs because the 2lST high MET region does not require having SF pairs
        bool JpsiYvetoOS = false;
        bool JpsiYvetoOSSF = false;
        if(nOSpairs > 0 and ( (mllOS > 9. and mllOS < 10.5) or (mllOS > 3. and mllOS < 3.2) ) )
          JpsiYvetoOS = true;
        if(nOSSFpairs > 0 and ( (mllOSSF > 9. and mllOSSF < 10.5) and (mllOSSF > 3. and mllOSSF < 3.2) ) )
          JpsiYvetoOSSF = true;

        // TODO: "Tight lepton veto" requirement: no idea how to implement
        bool tight_lepton_veto = false;

        // Invariant mass of leptonic-decaying tau pairs
        double mTauTau=0;
        if (nSignalLeptons == 2)
        {
          // TODO: Don't understand this implementation or where it comes from, but I'll take it as I have nothing else
          double determinant = signalLeptons.at(0)->mom().px() * signalLeptons.at(1)->mom().py() - signalLeptons.at(0)->mom().py() * signalLeptons.at(1)->mom().px();
          double xi_1 = (mmom.px() * signalLeptons.at(1)->mom().py() - signalLeptons.at(1)->mom().px() * mmom.py()) / determinant;
          double xi_2 = (mmom.py() * signalLeptons.at(0)->mom().px() - signalLeptons.at(0)->mom().py() * mmom.px()) / determinant;
          mTauTau = (1.+xi_1) * (1.+xi_2) * 2. * signalLeptons.at(0)->mom().dot(signalLeptons.at(1)->mom());
          if(mTauTau > 0) mTauTau = sqrt(mTauTau);
          if(mTauTau < 0) mTauTau = -sqrt(-mTauTau);
        }

        // Transverse mass between each lepton and MET, ordered from largest to smallest
        std::vector<double> mT;
        for(auto& lep: signalLeptons)
          mT.push_back(sqrt(2. * lep->pT() * met * (1. - cos(lep->phi() - mmom.phi())) ));
        std::sort(mT.rbegin(), mT.rend());   // note: reverse iterators


        // Delta R of different leptons, ordered from smallest to largest
        std::vector<double> DeltaRll;
        for(auto &ospair : OSpairs)
          DeltaRll.push_back(deltaR_eta(ospair.at(0)->mom(), ospair.at(1)->mom()));
        std::sort(DeltaRll.begin(), DeltaRll.end());


        ///////////////////
        // Preselection //

        BEGIN_PRESELECTION

        if(nSignalLeptons < 2 or nSignalLeptons > 3) return;
        if(nOSpairs < 1) return;

        // Trigger paths
        bool trigger_path_1 = metcorr > 120;
        bool trigger_path_2 = metcorr > 60. and met > 50. and  nSignalMuons > 2 and signalMuons.at(0)->pT() > 3 and signalMuons.at(1)->pT() > 3 and
             (signalMuons.at(0)->mom() + signalMuons.at(1)->mom()).m() > 3.8 and  (signalMuons.at(0)->mom() + signalMuons.at(1)->mom()).m() < 56;
        // TODO: Trigger path only important for WZ regions, check if it matters
        //bool trigger_path_3 = metcorr > 60. and met > 50. and  nSignalMuons > 2 and signalMuons.at(0)->pT() > 17 and signalMuons.at(1)->pT() > 8;
        if(not trigger_path_1 and not trigger_path_2/* and not trigger_path_3*/) return;

        END_PRESELECTION

//        std::cout<< "met = " << met << ", metcorr = " << metcorr << std::endl;


        ////////////////////
        // Signal Regions //

        // 2lEW, low MET,  signal regions
        if(met > 125. and metcorr > 125. and metcorr <= 200. and
           nSignalLeptons == 2 and
           signalLeptons.at(0)->pT() > 5. and signalLeptons.at(0)->pT() < 30. and
           signalLeptons.at(1)->pT() > 5. and signalLeptons.at(1)->pT() < 30. and
           nOSpairs > 0 and nOSSFpairs > 0 and
           mllOSSF > 4. and mllOSSF < 50. and
           not JpsiYvetoOSSF and
           pTll > 3. and
           not tight_lepton_veto and
           mT[0] < 70. and
           HT > 100. and
           metcorr/HT  > 2./3 and metcorr/HT < 1.4 and
           nSignalBJets == 0 and
           mTauTau < 0 and mTauTau > 160)
        {
//          LOG_CUT("2lEW1", "2lEW2", "2lEW3", "2lEW4")

          if(mllOSSF > 4.  and mllOSSF <= 10.) { FILL_SIGNAL_REGION("2lEW1"); }
          if(mllOSSF > 10. and mllOSSF <= 20.) { FILL_SIGNAL_REGION("2lEW2"); }
          if(mllOSSF > 20. and mllOSSF <= 30.) { FILL_SIGNAL_REGION("2lEW3"); }
          if(mllOSSF > 30. and mllOSSF <  50.) { FILL_SIGNAL_REGION("2lEW4"); }
        }


        // 2lEW, high MET, signal regions
        if(metcorr > 200. and
           nSignalLeptons == 2 and
           ( (amIanElectron(signalLeptons.at(0)) and signalLeptons.at(0)->pT() > 5.) or (amIaMuon(signalLeptons.at(0)) and signalLeptons.at(0)->pT() > 3.5) ) and signalLeptons.at(0)->pT() < 30. and
           ( (amIanElectron(signalLeptons.at(1)) and signalLeptons.at(1)->pT() > 5.) or (amIaMuon(signalLeptons.at(1)) and signalLeptons.at(1)->pT() > 3.5) ) and signalLeptons.at(1)->pT() < 30. and
           nOSpairs > 0 and nOSSFpairs > 0 and
           DeltaRll[0] > 0.3 and
           mllOSSF > 1. and mllOSSF < 50. and
           not JpsiYvetoOSSF and
           pTll > 3. and
           not tight_lepton_veto and
           mT[0] < 70. and
           HT > 100. and
           metcorr/HT  > 2./3 and metcorr/HT < 1.4 and
           nSignalBJets == 0 and
           mTauTau < 0 and mTauTau > 160)
        {
          if(metcorr > 200. and metcorr <= 240. and mllOSSF > 1.  and mllOSSF <=  4.) { FILL_SIGNAL_REGION("2lEW5"); }
          if(metcorr > 200. and metcorr <= 240. and mllOSSF > 4.  and mllOSSF <= 10.) { FILL_SIGNAL_REGION("2lEW6"); }
          if(metcorr > 200. and metcorr <= 240. and mllOSSF > 10. and mllOSSF <= 20.) { FILL_SIGNAL_REGION("2lEW7"); }
          if(metcorr > 200. and metcorr <= 240. and mllOSSF > 20. and mllOSSF <= 30.) { FILL_SIGNAL_REGION("2lEW8"); }
          if(metcorr > 200. and metcorr <= 240. and mllOSSF > 30. and mllOSSF <  50.) { FILL_SIGNAL_REGION("2lEW9"); }
          if(metcorr > 240. and metcorr <= 290. and mllOSSF > 1.  and mllOSSF <=  4.) { FILL_SIGNAL_REGION("2lEW10"); }
          if(metcorr > 240. and metcorr <= 290. and mllOSSF > 4.  and mllOSSF <= 10.) { FILL_SIGNAL_REGION("2lEW11"); }
          if(metcorr > 240. and metcorr <= 290. and mllOSSF > 10. and mllOSSF <= 20.) { FILL_SIGNAL_REGION("2lEW12"); }
          if(metcorr > 240. and metcorr <= 290. and mllOSSF > 20. and mllOSSF <= 30.) { FILL_SIGNAL_REGION("2lEW13"); }
          if(metcorr > 240. and metcorr <= 290. and mllOSSF > 30. and mllOSSF <  50.) { FILL_SIGNAL_REGION("2lEW14"); }
          if(metcorr > 290. and mllOSSF > 1.  and mllOSSF <=  4.) { FILL_SIGNAL_REGION("2lEW15"); }
          if(metcorr > 290. and mllOSSF > 4.  and mllOSSF <= 10.) { FILL_SIGNAL_REGION("2lEW16"); }
          if(metcorr > 290. and mllOSSF > 10. and mllOSSF <= 20.) { FILL_SIGNAL_REGION("2lEW17"); }
          if(metcorr > 290. and mllOSSF > 20. and mllOSSF <= 30.) { FILL_SIGNAL_REGION("2lEW18"); }
          if(metcorr > 290. and mllOSSF > 30. and mllOSSF <  50.) { FILL_SIGNAL_REGION("2lEW19"); }
        }


        // 2lST, low MET, signal regions
        if(met > 125. and metcorr > 125. and metcorr <= 200. and
           nSignalLeptons == 2 and
           signalLeptons.at(0)->pT() > 5. and signalLeptons.at(0)->pT() < 30. and
           signalLeptons.at(1)->pT() > 5. and signalLeptons.at(1)->pT() < 30. and
           nOSpairs > 0 and nOSSFpairs > 0 and
           mllOSSF > 4. and mllOSSF < 50. and
           not JpsiYvetoOSSF and
           pTll > 3. and
           not tight_lepton_veto and
           HT > 100. and
           metcorr/HT  > 2./3 and metcorr/HT < 1.4 and
           nSignalBJets == 0 and
           mTauTau < 0 and mTauTau > 160)
        {
          if(signalLeptons.at(0)->pT() >  3.5 and signalLeptons.at(0)->pT() <=  8.) { FILL_SIGNAL_REGION("2lST1"); }
          if(signalLeptons.at(0)->pT() >  8.  and signalLeptons.at(0)->pT() <= 12.) { FILL_SIGNAL_REGION("2lST2"); }
          if(signalLeptons.at(0)->pT() > 12.  and signalLeptons.at(0)->pT() <= 16.) { FILL_SIGNAL_REGION("2lST3"); }
          if(signalLeptons.at(0)->pT() > 16.  and signalLeptons.at(0)->pT() <= 20.) { FILL_SIGNAL_REGION("2lST4"); }
          if(signalLeptons.at(0)->pT() > 20.  and signalLeptons.at(0)->pT() <= 25.) { FILL_SIGNAL_REGION("2lST5"); }
          if(signalLeptons.at(0)->pT() > 25.  and signalLeptons.at(0)->pT() <  30.) { FILL_SIGNAL_REGION("2lST6"); }
        }


        // 2lST, high MET, signal regions
        if(metcorr > 200. and
           nSignalLeptons == 2 and
           ( (amIanElectron(signalLeptons.at(0)) and signalLeptons.at(0)->pT() > 5.) or (amIaMuon(signalLeptons.at(0)) and signalLeptons.at(0)->pT() > 3.5)) and signalLeptons.at(0)->pT() < 30. and
           ( (amIanElectron(signalLeptons.at(1)) and signalLeptons.at(1)->pT() > 5.) or (amIaMuon(signalLeptons.at(1)) and signalLeptons.at(1)->pT() > 3.5)) and signalLeptons.at(1)->pT() < 30. and
           nOSpairs > 0 and
           DeltaRll[0] > 0.3 and
           mllOS > 1. and mllOS < 50. and
           not JpsiYvetoOS and
           pTll > 3. and
           not tight_lepton_veto and
           HT > 100. and
           metcorr/HT  > 2./3 and metcorr/HT < 1.4 and
           nSignalBJets == 0 and
           mTauTau < 0 and mTauTau > 160)
        {
          if(metcorr > 200. and metcorr <= 290. and signalLeptons.at(0)->pT() >  3.5 and signalLeptons.at(0)->pT() <=  8.) { FILL_SIGNAL_REGION("2lST7"); }
          if(metcorr > 200. and metcorr <= 290. and signalLeptons.at(0)->pT() >  8.  and signalLeptons.at(0)->pT() <= 12.) { FILL_SIGNAL_REGION("2lST8"); }
          if(metcorr > 200. and metcorr <= 290. and signalLeptons.at(0)->pT() > 12.  and signalLeptons.at(0)->pT() <= 16.) { FILL_SIGNAL_REGION("2lST9"); }
          if(metcorr > 200. and metcorr <= 290. and signalLeptons.at(0)->pT() > 16.  and signalLeptons.at(0)->pT() <= 20.) { FILL_SIGNAL_REGION("2lST10"); }
          if(metcorr > 200. and metcorr <= 290. and signalLeptons.at(0)->pT() > 20.  and signalLeptons.at(0)->pT() <= 25.) { FILL_SIGNAL_REGION("2lST11"); }
          if(metcorr > 200. and metcorr <= 290. and signalLeptons.at(0)->pT() > 25.  and signalLeptons.at(0)->pT() <  30.) { FILL_SIGNAL_REGION("2lST12"); }
          if(metcorr > 290. and metcorr <= 340. and signalLeptons.at(0)->pT() >  3.5 and signalLeptons.at(0)->pT() <=  8.) { FILL_SIGNAL_REGION("2lST13"); }
          if(metcorr > 290. and metcorr <= 340. and signalLeptons.at(0)->pT() >  8.  and signalLeptons.at(0)->pT() <= 12.) { FILL_SIGNAL_REGION("2lST14"); }
          if(metcorr > 290. and metcorr <= 340. and signalLeptons.at(0)->pT() > 12.  and signalLeptons.at(0)->pT() <= 16.) { FILL_SIGNAL_REGION("2lST15"); }
          if(metcorr > 290. and metcorr <= 340. and signalLeptons.at(0)->pT() > 16.  and signalLeptons.at(0)->pT() <= 20.) { FILL_SIGNAL_REGION("2lST16"); }
          if(metcorr > 290. and metcorr <= 340. and signalLeptons.at(0)->pT() > 20.  and signalLeptons.at(0)->pT() <= 25.) { FILL_SIGNAL_REGION("2lST17"); }
          if(metcorr > 290. and metcorr <= 340. and signalLeptons.at(0)->pT() > 25.  and signalLeptons.at(0)->pT() <  30.) { FILL_SIGNAL_REGION("2lST18"); }
          if(metcorr > 340. and signalLeptons.at(0)->pT() >  3.5 and signalLeptons.at(0)->pT() <=  8.) { FILL_SIGNAL_REGION("2lST19"); }
          if(metcorr > 340. and signalLeptons.at(0)->pT() >  8.  and signalLeptons.at(0)->pT() <= 12.) { FILL_SIGNAL_REGION("2lST20"); }
          if(metcorr > 340. and signalLeptons.at(0)->pT() > 12.  and signalLeptons.at(0)->pT() <= 16.) { FILL_SIGNAL_REGION("2lST21"); }
          if(metcorr > 340. and signalLeptons.at(0)->pT() > 16.  and signalLeptons.at(0)->pT() <= 20.) { FILL_SIGNAL_REGION("2lST22"); }
          if(metcorr > 340. and signalLeptons.at(0)->pT() > 20.  and signalLeptons.at(0)->pT() <= 25.) { FILL_SIGNAL_REGION("2lST23"); }
          if(metcorr > 340. and signalLeptons.at(0)->pT() > 25.  and signalLeptons.at(0)->pT() <  30.) { FILL_SIGNAL_REGION("2lST24"); }
        }


        // 3lEW, low MET, signal regions
        if(met > 125. and metcorr > 125. and metcorr <= 200. and
           nSignalLeptons == 3 and
           signalLeptons.at(0)->pT() > 5. and signalLeptons.at(0)->pT() < 30. and
           signalLeptons.at(1)->pT() > 5. and signalLeptons.at(1)->pT() < 30. and
           signalLeptons.at(2)->pT() > 5. and signalLeptons.at(2)->pT() < 30. and
           nOSpairs > 0 and nOSSFpairs > 0 and
           mllOSSF > 4. and mllOSSF < 50. and
           mllSF < 60. and
           not JpsiYvetoOSSF and
           HT > 100. and
           nSignalBJets == 0)
        {
          if(mllOSSF >  4. and mllOSSF <= 10.) { FILL_SIGNAL_REGION("3lEW1"); }
          if(mllOSSF > 10. and mllOSSF <= 20.) { FILL_SIGNAL_REGION("3lEW2"); }
          if(mllOSSF > 20. and mllOSSF <= 30.) { FILL_SIGNAL_REGION("3lEW3"); }
          if(mllOSSF > 30. and mllOSSF <  50.) { FILL_SIGNAL_REGION("3lEW4"); }
        }


        // 3lEW, high MET, signal regions
        if(metcorr > 200. and
           nSignalLeptons == 3 and
           ( (amIanElectron(signalLeptons.at(0)) and signalLeptons.at(0)->pT() > 5.) or (amIaMuon(signalLeptons.at(0)) and signalLeptons.at(0)->pT() > 3.5)) and signalLeptons.at(0)->pT() < 30. and
           ( (amIanElectron(signalLeptons.at(1)) and signalLeptons.at(1)->pT() > 5.) or (amIaMuon(signalLeptons.at(1)) and signalLeptons.at(1)->pT() > 3.5)) and signalLeptons.at(1)->pT() < 30. and
           ( (amIanElectron(signalLeptons.at(2)) and signalLeptons.at(2)->pT() > 5.) or (amIaMuon(signalLeptons.at(2)) and signalLeptons.at(2)->pT() > 3.5)) and signalLeptons.at(2)->pT() < 30. and
           nOSpairs > 0 and nOSSFpairs and
           DeltaRll[0] > 0.3 and
           mllOSSF > 1. and mllOSSF < 50. and
           not JpsiYvetoOSSF and
           HT > 100. and
           nSignalBJets == 0)
        {
          if(mllOSSF >  1. and mllOSSF <=  4.) { FILL_SIGNAL_REGION("3lEW5"); }
          if(mllOSSF >  4. and mllOSSF <= 10.) { FILL_SIGNAL_REGION("3lEW6"); }
          if(mllOSSF > 10. and mllOSSF <= 20.) { FILL_SIGNAL_REGION("3lEW7"); }
          if(mllOSSF > 20. and mllOSSF <= 30.) { FILL_SIGNAL_REGION("3lEW8"); }
          if(mllOSSF > 30. and mllOSSF <  50.) { FILL_SIGNAL_REGION("3lEW9"); }
        }

      }

      /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
      void combine(const Analysis* other)
      {
        const Analysis_CMS_13TeV_2LEPsoft_137invfb* specificOther = dynamic_cast<const Analysis_CMS_13TeV_2LEPsoft_137invfb*>(other);
        for (auto& pair : _counters) { pair.second += specificOther->_counters.at(pair.first); }

      }


      virtual void collect_results()
      {

        /// 2lEW signal regions
        COMMIT_SIGNAL_REGION("2lEW1",  73., 68.7, 8.7)
        COMMIT_SIGNAL_REGION("2lEW2",  165., 151., 13.)
        COMMIT_SIGNAL_REGION("2lEW3",  156., 151., 13.)
        COMMIT_SIGNAL_REGION("2lEW4",  80., 82.9, 9.6)
        COMMIT_SIGNAL_REGION("2lEW5",  2., 5.5, 2.5)
        COMMIT_SIGNAL_REGION("2lEW6",  19., 17.8, 4.4)
        COMMIT_SIGNAL_REGION("2lEW7",  59., 60.1, 8.3)
        COMMIT_SIGNAL_REGION("2lEW8",  47., 44.3, 7.1)
        COMMIT_SIGNAL_REGION("2lEW9",  24., 27.7, 5.6)
        COMMIT_SIGNAL_REGION("2lEW10", 2., 2.7, 1.9)
        COMMIT_SIGNAL_REGION("2lEW11", 11., 7.7, 3.9)
        COMMIT_SIGNAL_REGION("2lEW12", 19., 23.8, 5.4)
        COMMIT_SIGNAL_REGION("2lEW13", 13., 17.0, 4.5)
        COMMIT_SIGNAL_REGION("2lEW14", 10., 11.6, 5.8)
        COMMIT_SIGNAL_REGION("2lEW15", 1., 1.5, 1.3)
        COMMIT_SIGNAL_REGION("2lEW16", 3., 5.2, 2.5)
        COMMIT_SIGNAL_REGION("2lEW17", 15., 13.5, 4.1)
        COMMIT_SIGNAL_REGION("2lEW18", 13., 8.8, 3.2)
        COMMIT_SIGNAL_REGION("2lEW19", 9., 6.8, 3.0)

        /// 3lEW signal regions
        COMMIT_SIGNAL_REGION("3lEW1", 3., 5.7, 2.2)
        COMMIT_SIGNAL_REGION("3lEW2", 7., 4.9, 2.2)
        COMMIT_SIGNAL_REGION("3lEW3", 4., 2.4, 1.5)
        COMMIT_SIGNAL_REGION("3lEW4", 1., 1.8, 1.4)
        COMMIT_SIGNAL_REGION("3lEW5", 3., 1.7, 1.2)
        COMMIT_SIGNAL_REGION("3lEW6", 1., 4.0, 1.8)
        COMMIT_SIGNAL_REGION("3lEW7", 5., 4.2, 2.0)
        COMMIT_SIGNAL_REGION("3lEW8", 2., 1.7, 1.3)
        COMMIT_SIGNAL_REGION("3lEW9", 1., 1.3, 1.1)

        /// 2lST signal regions
        COMMIT_SIGNAL_REGION("2lST1",  52.,  49.9, 7.2)
        COMMIT_SIGNAL_REGION("2lST2",  156., 144., 12.)
        COMMIT_SIGNAL_REGION("2lST3",  196., 180., 14.)
        COMMIT_SIGNAL_REGION("2lST4",  238., 229., 16.)
        COMMIT_SIGNAL_REGION("2lST5",  285., 273., 18.)
        COMMIT_SIGNAL_REGION("2lST6",  246., 256., 17.)
        COMMIT_SIGNAL_REGION("2lST7",  53.,  49.9, 7.3)
        COMMIT_SIGNAL_REGION("2lST8",  130., 129., 12.)
        COMMIT_SIGNAL_REGION("2lST9",  153., 156., 13.)
        COMMIT_SIGNAL_REGION("2lST10", 163., 177., 14.)
        COMMIT_SIGNAL_REGION("2lST11", 220., 220., 16.)
        COMMIT_SIGNAL_REGION("2lST12", 219., 218., 16.)
        COMMIT_SIGNAL_REGION("2lST13", 4.,   4.1,  2.1)
        COMMIT_SIGNAL_REGION("2lST14", 15.,  15.0, 4.1)
        COMMIT_SIGNAL_REGION("2lST15", 16.,  14.8, 4.1)
        COMMIT_SIGNAL_REGION("2lST16", 23.,  24.6, 5.2)
        COMMIT_SIGNAL_REGION("2lST17", 30.,  28.8, 5.8)
        COMMIT_SIGNAL_REGION("2lST18", 38.,  31.5, 6.0)
        COMMIT_SIGNAL_REGION("2lST19", 7.,   4.7,  2.3)
        COMMIT_SIGNAL_REGION("2lST20", 11.,  12.2, 3.6)
        COMMIT_SIGNAL_REGION("2lST21", 14.,  11.6, 3.6)
        COMMIT_SIGNAL_REGION("2lST22", 11.,  16.7, 4.4)
        COMMIT_SIGNAL_REGION("2lST23", 26.,  25.7, 5.5)
        COMMIT_SIGNAL_REGION("2lST24", 26.,  27.9, 5.7)

        /// Cutflows
        COMMIT_CUTFLOWS
      }


    protected:

      void analysis_specific_reset()
      {

        for (auto& pair : _counters) { pair.second.reset(); }
      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_2LEPsoft_137invfb)


  }
}
