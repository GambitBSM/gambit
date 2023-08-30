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
        DEFINE_SIGNAL_REGIONS("2lEW",19)
        DEFINE_SIGNAL_REGIONS("3lEW", 9)
        DEFINE_SIGNAL_REGIONS("WZ",   7)
        DEFINE_SIGNAL_REGIONS("2lST",24)

        set_analysis_name("CMS_13TeV_2LEPsoft_137invfb");
        set_luminosity(35.9);
      }

      void run(const HEPUtils::Event* event)
      {
        //////////////////////
        // Baseline objects //

        // TODO: Unsure on what to do about electron and muon efficiencies
        BASELINE_PARTICLES(electrons, baselineElectrons, 5., 0., 30., 2.5)
        BASELINE_PARTICLES(muons, baselineMuons, 3.5, 0., 30., 2.4)
        BASELINE_JETS(jets, baselineJets, 25., 0., DBL_MAX, 2.4)
        BASELINE_BJETS(jets, baselineBJets, 25., 0., DBL_MAX, 2.4, CMS::eff2DBJet.at("DeepCSVMedium"), CMS::missIDBJet.at("DeepCSVMedium"))

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


        ///////////////////////////////
        // Common variables and cuts //

        double met = event->met();
        P4 mmom = event->missingmom();

        size_t nSignalLeptons = signalLeptons.size();
        size_t nSignalMuons = signalMuons.size();
        size_t nSignalJets = signalJets.size();
        size_t nSignalBJets = signalBJets.size();
        size_t nOSpairs = OSpairs.size();
        size_t nOSSFpairs = OSSFpairs.size();

        // Muon corrected ETmiss
        double metcorr = 0.;
        for(auto& muon : signalMuons)
          metcorr += sqrt(muon->mom().px() * muon->mom().px() + muon->mom().py() * muon->mom().py());

        // Invariant mass of the OS dilepton pair
        double mllOS = 0.;
        if(nOSpairs > 0) mllOS = (OSpairs.at(0).at(0)->mom() + OSpairs.at(0).at(1)->mom()).m();

        // Invariant mass of the OSSF dilepton pair
        double mllOSSF = 0.;
        if(nOSSFpairs > 0) mllOSSF = (OSSFpairs.at(0).at(0)->mom() + OSSFpairs.at(0).at(1)->mom()).m();

        // Transverse momentum of the lepton pair, only relevant for two leptons
        double pTll = 0.;
        if(nSignalLeptons == 2) pTll = (signalLeptons.at(0)->mom() + signalLeptons.at(1)->mom()).pT();

        // Scalar sum of transverse hadronic energy
        double HT = 0.;
        for (auto& jet: signalJets)
          HT += jet->pT();

        // Veto events with invariant mass in the Y-meson or J/psi-meson mass range
        // TODO: This may not include the case for 2lST high MET where they do not have to be SF
        bool JpsiYveto = false;
        if(nOSSFpairs > 0 and ( (mllOSSF > 9. and mllOSSF < 10.5) or (mllOSSF > 3. and mllOSSF < 3.2) ) )
          JpsiYveto = true;

        // TODO: "Tight lepton veto" requirement: no idea how to implement

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

        // Transverse mass between each lepton and MET
        vector<double> mT;
        for(auto& lep: signalLeptons)
          mT.push_back(sqrt(2. * lep->pT() * met * (1. - cos(lep->phi() - mmom.phi())) ));

        // Cuflow initialization
        const double w = event->weight();
        _cutflows.fillinit(w);


        ///////////////////
        // Preselection //

        if(nSignalLeptons < 2 or nSignalLeptons > 3) return;
        if(nOSpairs < 1) return;

        // Trigger paths
        bool trigger_path_1 = metcorr > 120;
        bool trigger_path_2 = metcorr > 60. and met > 50. and  nSignalMuons > 2 and signalMuons.at(0)->pT() > 3 and signalMuons.at(1)->pT() > 3 and
             (signalMuons.at(0)->mom() + signalMuons.at(1)->mom()).m() > 3.8 and  (signalMuons.at(0)->mom() + signalMuons.at(1)->mom()).m() < 56;
        // TODO: Trigger path only important for WZ regions, check if it matters
        //bool trigger_path_3 = metcorr > 60. and met > 50. and  nSignalMuons > 2 and signalMuons.at(0)->pT() > 17 and signalMuons.at(1)->pT() > 8;
        if(not trigger_path_1 and not trigger_path_2/* and not trigger_path_3*/) return;

        // Fill preselection cutflows
        _cutflows.fillnext(w);


        //////////////////////
        // Event selection //

/*
        if (nSignalLeptons == 2) {
          m_ll=(signalLeptons.at(0)->mom()+signalLeptons.at(1)->mom()).m();
          pT_ll=(signalLeptons.at(0)->mom()+signalLeptons.at(1)->mom()).pT();

          // Calculation of $M_{\tau\tau}$ variable
          double determinant = signalLeptons.at(0)->mom().px()*signalLeptons.at(1)->mom().py()-signalLeptons.at(0)->mom().py()*signalLeptons.at(1)->mom().px();
          double xi_1 = (event->missingmom().px()*signalLeptons.at(1)->mom().py()-signalLeptons.at(1)->mom().px()*event->missingmom().py())/determinant;
          double xi_2 = (event->missingmom().py()*signalLeptons.at(0)->mom().px()-signalLeptons.at(0)->mom().py()*event->missingmom().px())/determinant;
          mTauTau = (1.+xi_1)*(1.+xi_2)*2*signalLeptons.at(0)->mom().dot(signalLeptons.at(1)->mom());
          if(mTauTau > 0) mTauTau = sqrt(mTauTau);
          if(mTauTau < 0) mTauTau = -sqrt(-mTauTau);

          if(m_ll>4. && (m_ll<9. || m_ll>10.5)) JpsiYveto = true;
        }

        for (size_t iJet=0;iJet<nSignalJets;iJet++)hT+=signalJets.at(iJet)->pT();

        for (size_t iLep=0;iLep<nSignalLeptons;iLep++)mT.push_back(sqrt(2*signalLeptons.at(iLep)->pT()*met*(1-cos(signalLeptons.at(iLep)->phi()-event->missingmom().phi()))));
        if (nSignalLeptons==0) {
          mT.push_back(999);
          mT.push_back(999);
        }
        if (nSignalLeptons==1)mT.push_back(999);

        if (nSignalLeptons==2) {
          OS=signalLeptons.at(0)->pid()*signalLeptons.at(1)->pid()<0.;
          SF=signalLeptons.at(0)->abspid() == signalLeptons.at(1)->abspid();
        }

        if (nSignalLeptons==2 && nSignalBJets==0 && nSignalJets>0 && signalLeptons.at(0)->pT()>5.) {
          // EW preselection
          if (OS && SF && signalLeptons.at(1)->pT()>5) {
            if (m_ll<50. && pT_ll>3. && met>125. && metcorr > 125. && met/hT<1.4 && met/hT>0.6 && hT>100. && JpsiYveto && (mTauTau<0. || mTauTau>160.) && mT.at(0)<70. && mT.at(1)<70.) {
              EWpreselection=true;
            }
          }
          // Stop preselection
          if (OS) {
            if (m_ll<50. && pT_ll>3. && met>125. && metcorr > 125. && met/hT<1.4 && met/hT>0.6 && hT>100. && (!SF || JpsiYveto) & (mTauTau<0. || mTauTau>160.) ) {
              STpreselection=true;
            }
          }
        }


        // Signal Regions
        // In the low ETmiss region, for each passing event we add 0.65 due to trigger efficiency
        if (EWpreselection && met>125. && met<200. && nSignalMuons == 2) {
          if (m_ll>4. && m_ll<9.) _counters.at("SREW1").add_event(event->weight() * 0.65, event->weight_err() * 0.65);
          if (m_ll>10.5 && m_ll<20.) _counters.at("SREW2").add_event(event->weight() * 0.65, event->weight_err() * 0.65);
          if (m_ll>20. && m_ll<30.) _counters.at("SREW3").add_event(event->weight() * 0.65, event->weight_err() * 0.65);
          if (m_ll>30. && m_ll<50.) _counters.at("SREW4").add_event(event->weight() * 0.65, event->weight_err() * 0.65);
        }
        if (EWpreselection && met>200. && met<250.) {
          if (m_ll>4. && m_ll<9.) _counters.at("SREW5").add_event(event);
          if (m_ll>10.5 && m_ll<20.) _counters.at("SREW6").add_event(event);
          if (m_ll>20. && m_ll<30.) _counters.at("SREW7").add_event(event);
          if (m_ll>30. && m_ll<50.) _counters.at("SREW8").add_event(event);
        }
        if (EWpreselection && met>250.) {
          if (m_ll>4. && m_ll<9.) _counters.at("SREW9").add_event(event);
          if (m_ll>10.5 && m_ll<20.) _counters.at("SREW10").add_event(event);
          if (m_ll>20. && m_ll<30.) _counters.at("SREW11").add_event(event);
          if (m_ll>30. && m_ll<50.) _counters.at("SREW12").add_event(event);
        }
        if (STpreselection && met>125. && met<200. && nSignalMuons == 2) {
          double leadpT = signalLeptons.at(0)->pT();
          if (leadpT>5. && leadpT<12.) _counters.at("SRST1").add_event(event);
          if (leadpT>12. && leadpT<20.) _counters.at("SRST2").add_event(event);
          if (leadpT>20. && leadpT<30.) _counters.at("SRST3").add_event(event);
        }
        if (STpreselection && met>200. && met<300.) {
          double leadpT = signalLeptons.at(0)->pT();
          if (leadpT>5. && leadpT<12.) _counters.at("SRST4").add_event(event);
          if (leadpT>12. && leadpT<20.) _counters.at("SRST5").add_event(event);
          if (leadpT>20. && leadpT<30.) _counters.at("SRST6").add_event(event);
        }
        if (STpreselection && met>300.) {
          double leadpT = signalLeptons.at(0)->pT();
          if (leadpT>5. && leadpT<12.) _counters.at("SRST7").add_event(event);
          if (leadpT>12. && leadpT<20.) _counters.at("SRST8").add_event(event);
          if (leadpT>20. && leadpT<30.) _counters.at("SRST9").add_event(event);
        }
*/
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

        /// WZ signal regions
        COMMIT_SIGNAL_REGION("WZ1", 4.,  3.5, 1.8)
        COMMIT_SIGNAL_REGION("WZ2", 11., 6.1, 2.3)
        COMMIT_SIGNAL_REGION("WZ3", 9.,  7.8, 2.6)
        COMMIT_SIGNAL_REGION("WZ4", 0.,  0.78, 0.97)
        COMMIT_SIGNAL_REGION("WZ5", 3.,  3.1, 1.6)
        COMMIT_SIGNAL_REGION("WZ6", 19., 14.0, 3.4)
        COMMIT_SIGNAL_REGION("WZ7", 23., 21.0, 4.2)

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
