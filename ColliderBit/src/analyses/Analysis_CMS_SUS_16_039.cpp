///
///  \author Rose Kudzman-Blais
///  \date 2017 May
///
///  \author Anders Kvellestad
///  \date 2018 June
///
///  updated by Kelton Whiteaker
///  2020 August
///  *********************************************


#include <vector>
#include <cmath>
#include <memory>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/analyses/AnalysisMacros.hpp"
#include "gambit/ColliderBit/CMSEfficiencies.hpp"
#include "gambit/ColliderBit/mt2_bisect.h"

// Based on http://cms-results.web.cern.ch/cms-results/public-results/superseded/SUS-16-039/index.html

using namespace std;

// #define CHECK_CUTFLOW

#define FILL_SR(NAME) FILL_SIGNAL_REGION(NAME)
#define LOG_SR(...) LOG_CUT(__VA_ARGS__)

// Renamed from: 
//        Analysis_CMS_13TeV_MultiLEP_36invfb
//        Analysis_CMS_13TeV_MultiLEP_2SSLep_36invfb
//        Analysis_CMS_13TeV_MultiLEP_3Lep_36invfb

namespace Gambit
{
  namespace ColliderBit
  {

    // This analysis class is a base class for two SR-specific analysis classes
    // defined further down:
    // - Analysis_CMS_SUS_16_039_2SSLep
    // - Analysis_CMS_SUS_16_039_3Lep
    class Analysis_CMS_SUS_16_039 : public Analysis
    {

      protected:
      private:

      public:

        // Required detector sim
        static constexpr const char* detector = "CMS";

        struct ptComparison
        {
          bool operator() (const HEPUtils::Particle* i,const HEPUtils::Particle* j) {return (i->pT()>j->pT());}
        } comparePt;

        Analysis_CMS_SUS_16_039()
        {
          DEFINE_SIGNAL_REGION("SR1", "2 leptons and 0 taus", "MET > 60 GeV", "conversion veto", "same-sign pair", "leading lepton pT", "N_ISRjets = 0 and MET > 140 GeV and mT > 100 GeV");
          DEFINE_SIGNAL_REGION("SR2", "2 leptons and 0 taus", "MET > 60 GeV", "conversion veto", "same-sign pair", "leading lepton pT", "N_ISRjets = 1 and MET > 200 GeV and mT < 100 GeV and pT_ll < 100 GeV");
          DEFINE_SIGNAL_REGION("SR3", "MET > 50 GeV and conversion veto and Nlep > 2", "Ntau < 2", "leading light lepton pT", "3 light leptons and 0 taus", "mT > 120 GeV and MET > 200 GeV");
          DEFINE_SIGNAL_REGION("SR4", "MET > 50 GeV and conversion veto and Nlep > 2", "Ntau < 2", "leading light lepton pT", "3 light leptons and 0 taus", "MET > 250 GeV");
          DEFINE_SIGNAL_REGION("SR5", "MET > 50 GeV and conversion veto and Nlep > 2", "Ntau < 2", "leading light lepton pT", "2 light leptons and 1 tau", "mT2 > 50 GeV and MET > 200 GeV");
          DEFINE_SIGNAL_REGION("SR6", "MET > 50 GeV and conversion veto and Nlep > 2", "1 light lepton and 2 taus", "leading light lepton pT", "all lepton |eta| < 2.1", "mT2 > 50 GeV and MET > 200 GeV");
          DEFINE_SIGNAL_REGION("SR7", "MET > 50 GeV and conversion veto and Nlep > 2", "1 light lepton and 2 taus", "leading light lepton pT", "all lepton |eta| < 2.1", "MET > 75 GeV");
          DEFINE_SIGNAL_REGION("SR8", "MET > 50 GeV and conversion veto and Nlep > 2", "Ntau < 2", "leading light lepton pT", "Nlep > 3", "MET > 200 GeV");

          set_analysis_name("CMS_SUS_16_039_200_100");
          set_luminosity(35.9);
        }


        void run(const HEPUtils::Event* event)
        {

          double met = event->met();

          // Baseline objects

          // Note that CMS provides two different efficiency maps, one for the multi-lepton SR and one for the 2SS signal region:
          //   https://twiki.cern.ch/twiki/bin/view/CMSPublic/SUSMoriond2017ObjectsEfficiency
          // Here we have only implemented the multi-lepton efficiency map.

          //@note Numbers digitized from https://twiki.cern.ch/twiki/pub/CMSPublic/SUSMoriond2017ObjectsEfficiency/2d_full_pteta_el_039_multi_ttbar.pdf
          //@note The efficiency map has been extended to cover the low-pT region, using the efficiencies from BuckFast (CMSEfficiencies.hpp)
          const vector<double> aEl={0., 0.8, 1.442, 1.556, 2., 2.5, DBL_MAX};   // Bin edges in eta
          const vector<double> bEl={0., 10., 15., 20., 25., 30., 40., 50., DBL_MAX}; // Bin edges in pT. Assume flat efficiency above 200, where the CMS map stops.
          const vector<double> cEl={
                            // pT: (0,10),  (10,15),  (15,20),  (20,25),  (25,30),  (30,40),  (40,50),  (50,inf)
                                     0.0,    0.95,    0.507,    0.619,    0.682,    0.742,    0.798,    0.863,  // eta: (0, 0.8)
                                     0.0,    0.95,    0.429,    0.546,    0.619,    0.710,    0.734,    0.833,  // eta: (0.8, 1.4429
                                     0.0,    0.95,    0.256,    0.221,    0.315,    0.351,    0.373,    0.437,  // eta: (1.442, 1.556)
                                     0.0,    0.85,    0.249,    0.404,    0.423,    0.561,    0.642,    0.749,  // eta: (1.556, 2)
                                     0.0,    0.85,    0.195,    0.245,    0.380,    0.441,    0.533,    0.644,  // eta: (2, 2.5)
                                     0.0,    0.0,     0.0,      0.0,      0.0,      0.0,      0.0,      0.0,    // eta > 2.5
                                    };
          // const vector<double> aEl={0,0.8,1.442,1.556,2.,2.5};
          // const vector<double> bEl={0.,20.,25.,30.,40.,50.,10000.};  // Assuming flat efficiency above pT = 200 GeV, where the CMS map stops.
          // const vector<double> cEl={0.507,0.619,0.682,0.742,0.798,0.863,0.429,0.546,0.619,0.710,0.734,0.833,0.256,0.221,0.315,0.351,0.373,0.437,0.249,0.404,0.423,0.561,0.642,0.749,0.195,0.245,0.380,0.441,0.533,0.644};
          HEPUtils::BinnedFn2D<double> _eff2dEl(aEl,bEl,cEl);
          vector<const HEPUtils::Particle*> baselineElectrons;
          for (const HEPUtils::Particle* electron : event->electrons())
          {
            bool isEl=has_tag(_eff2dEl, fabs(electron->eta()), electron->pT());
            if (electron->pT()>15. && fabs(electron->eta())<2.5 && isEl)baselineElectrons.push_back(electron);
          }

          //@note Numbers digitized from https://twiki.cern.ch/twiki/pub/CMSPublic/SUSMoriond2017ObjectsEfficiency/2d_full_pteta_mu_039_multi_ttbar.pdf
          //@note The efficiency map has been extended to cover the low-pT region, using the efficiencies from BuckFast (CMSEfficiencies.hpp)
          const vector<double> aMu={0., 0.9, 1.2, 2.1, 2.4, DBL_MAX};   // Bin edges in eta
          const vector<double> bMu={0., 10., 15., 20., 25., 30., 40., 50., DBL_MAX};  // Bin edges in pT. Assume flat efficiency above 200, where the CMS map stops.
          const vector<double> cMu={
                             // pT:   (0,10),  (10,15),  (15,20),  (20,25),  (25,30),  (30,40),  (40,50),  (50,inf)
                                       0.0,     0.704,    0.797,    0.855,    0.880,    0.906,    0.927,    0.931,  // eta: (0, 0.9)
                                       0.0,     0.639,    0.776,    0.836,    0.875,    0.898,    0.940,    0.930,  // eta: (0.9, 1.2)
                                       0.0,     0.596,    0.715,    0.840,    0.862,    0.891,    0.906,    0.925,  // eta: (1.2, 2.1)
                                       0.0,     0.522,    0.720,    0.764,    0.803,    0.807,    0.885,    0.877,  // eta: (2.1, 2.4)
                                       0.0,     0.0,      0.0,      0.0,      0.0,      0.0,      0.0,      0.0,    // eta > 2.4
                                   };
          // const vector<double> aMu={0,0.9,1.2,2.1,2.4};
          // const vector<double> bMu={0.,15.,20.,25.,30.,40.,50.,10000.};  // Assuming flat efficiency above pT = 200 GeV, where the CMS map stops.
          // const vector<double> cMu={0.704,0.797,0.855,0.88,0.906,0.927,0.931,0.639,0.776,0.836,0.875,0.898,0.94,0.93,0.569,0.715,0.84,0.862,0.891,0.906,0.925,0.0522,0.720,0.764,0.803,0.807,0.885,0.877};
          HEPUtils::BinnedFn2D<double> _eff2dMu(aMu,bMu,cMu);
          vector<const HEPUtils::Particle*> baselineMuons;
          for (const HEPUtils::Particle* muon : event->muons())
          {
            bool isMu=has_tag(_eff2dMu, fabs(muon->eta()), muon->pT());
            if (muon->pT()>10. &&fabs(muon->eta())<2.4 && isMu)baselineMuons.push_back(muon);
          }

          // @note Numbers digitized from https://twiki.cern.ch/twiki/pub/CMSPublic/SUSMoriond2017ObjectsEfficiency/TauIDEfficiency_pT_DP2016_066.pdf
          const vector<double> aTau={0.,2.3};
          const vector<double> bTau={0.,25.,30.,35.,40.,45.,50.,60.,70.,80.,DBL_MAX};  // Assuming flat efficiency above pT = 100 GeV, where the CMS map stops.
          // The tau efficiencies should be corrected with a data/simulation scale factor of 0.95, as instructed here: https://twiki.cern.ch/twiki/bin/view/CMSPublic/SUSMoriond2017ObjectsEfficiency
          const vector<double> cTau={0.38*0.95, 0.48*0.95, 0.5*0.95, 0.49*0.95, 0.51*0.95, 0.49*0.95, 0.47*0.95, 0.45*0.95, 0.48*0.95, 0.5*0.95};
          HEPUtils::BinnedFn2D<double> _eff2dTau(aTau,bTau,cTau);
          vector<const HEPUtils::Particle*> baselineTaus;
          for (const HEPUtils::Particle* tau : event->taus())
          {
            bool isTau=has_tag(_eff2dTau, fabs(tau->eta()), tau->pT());
            if (tau->pT()>20. &&fabs(tau->eta())<2.3 && isTau)baselineTaus.push_back(tau);
          }

          vector<const HEPUtils::Jet*> baselineJets;
          for (const HEPUtils::Jet* jet : event->jets("antikt_R04"))
          {
            if (jet->pT()>25. &&fabs(jet->eta())<2.4)baselineJets.push_back(jet);
          }

          // Signal objects
          vector<const HEPUtils::Particle*> signalElectrons=baselineElectrons;
          vector<const HEPUtils::Particle*> signalMuons=baselineMuons;
          vector<const HEPUtils::Particle*> signalTaus=baselineTaus;
          vector<const HEPUtils::Particle*> signalLightLeptons=signalElectrons;
          signalLightLeptons.insert(signalLightLeptons.end(),signalMuons.begin(),signalMuons.end());
          vector<const HEPUtils::Particle*> signalLeptons=signalTaus;
          signalLeptons.insert(signalLeptons.end(),signalLightLeptons.begin(),signalLightLeptons.end());
          sort(signalLightLeptons.begin(),signalLightLeptons.end(),comparePt);
          sort(signalLeptons.begin(),signalLeptons.end(),comparePt);

          vector<const HEPUtils::Jet*> signalJets;
          vector<const HEPUtils::Jet*> signalBJets;
          int num_ISRjets=0;
          for (size_t iJet=0;iJet<baselineJets.size();iJet++)
          {
            bool overlap=false;
            for (size_t iLe=0;iLe<signalLeptons.size();iLe++)
            {
              if (fabs(signalLeptons.at(iLe)->mom().deltaR_eta(baselineJets.at(iJet)->mom()))<0.4) overlap=true;
            }
            if (!overlap)
            {
              signalJets.push_back(baselineJets.at(iJet));
              if (baselineJets.at(iJet)->btag())signalBJets.push_back(baselineJets.at(iJet));
              if (baselineJets.at(iJet)->pT()>40.)num_ISRjets++;
            }
          }
          applyEfficiency(signalBJets, CMS::eff2DBJet.at("CSVv2Medium"));

          // int nSignalElectrons=signalElectrons.size();
          int nSignalMuons=signalMuons.size();
          int nSignalTaus=signalTaus.size();
          int nSignalLightLeptons = signalLightLeptons.size();
          int nSignalLeptons=signalLeptons.size();
          // int nSignalJets=signalJets.size();

          //Variables
          bool preselection=false;
          bool bjet_veto=(signalBJets.size()==0);
          bool low_mass_veto=true;
          bool conversion_veto=true;

          double pT_ll=0;
          double mT=0;
          double mT2=0;
          vector<vector<const HEPUtils::Particle*>> SFOSpair_cont = getSFOSpairs(signalLeptons);
          vector<vector<const HEPUtils::Particle*>> OSpair_cont = getOSpairs(signalLeptons);

          if (nSignalLeptons>1)pT_ll=(signalLeptons.at(0)->mom()+signalLeptons.at(1)->mom()).pT();
          if (nSignalLightLeptons>0 && nSignalTaus>0)
          {
            double pLep1[3] = {signalLightLeptons.at(0)->mass(), signalLightLeptons.at(0)->mom().px(), signalLightLeptons.at(0)->mom().py()};
            double pTau[3] = {signalTaus.at(0)->mass(), signalTaus.at(0)->mom().px(), signalTaus.at(0)->mom().py()};
            double pMiss[3] = {0., event->missingmom().px(), event->missingmom().py() };
            double mn = 0.;

            mt2_bisect::mt2 mt2_calc;
            mt2_calc.set_momenta(pLep1,pTau,pMiss);
            mt2_calc.set_mn(mn);
            mT2 = mt2_calc.get_mt2();
          }
          if (nSignalLeptons==2 || (SFOSpair_cont.size()==0 && OSpair_cont.size()==0))mT=get_mTmin(signalLeptons, event->missingmom());
          if (SFOSpair_cont.size()>0)
          {
            vector<double> mll_mT= get_mll_mT(SFOSpair_cont,signalLeptons,event->missingmom(),0);
            mT=mll_mT.at(1);
          }
          if (SFOSpair_cont.size()==0 && OSpair_cont.size()>0)
          {
            vector<double> mll_mT= get_mll_mT(OSpair_cont,signalLeptons,event->missingmom(),1);
            mT=mll_mT.at(1);
          }
          for (size_t iPa=0;iPa<SFOSpair_cont.size();iPa++)
          {
            double SFOSpair_mass=(SFOSpair_cont.at(iPa).at(0)->mom()+SFOSpair_cont.at(iPa).at(1)->mom()).m();
            if (SFOSpair_mass<12)low_mass_veto=false;
            if (nSignalLeptons==2 && abs(SFOSpair_mass-91.2)<15)conversion_veto=false;
            if (nSignalLeptons>2)
            {
              double m_lll=(signalLeptons.at(0)->mom()+signalLeptons.at(1)->mom()+signalLeptons.at(2)->mom()).m();
              if (SFOSpair_cont.at(iPa).at(0)->abspid()!=15 && abs(m_lll-91.2)<15)conversion_veto=false;
            }
          }
          if (bjet_veto && low_mass_veto)preselection=true;

#ifdef CHECK_CUTFLOW
          BEGIN_PRESELECTION
          if (preselection) END_PRESELECTION
#endif

          //Signal regions
          //2 same-sign leptons
          if (preselection && nSignalLeptons==2 && nSignalTaus==0)
          {
            LOG_SR("SR1", "SR2");
            if (met>60)
            {
              LOG_SR("SR1", "SR2");
              if (conversion_veto)
              {
                LOG_SR("SR1", "SR2");
                if (signalLeptons.at(0)->pid()*signalLeptons.at(1)->pid()>0)
                {
                  LOG_SR("SR1", "SR2");
                  if ((signalLeptons.at(0)->abspid()==11 && signalLeptons.at(0)->pT()>25) || (signalLeptons.at(0)->abspid()==13 && signalLeptons.at(0)->pT()>20))
                  {
                    LOG_SR("SR1", "SR2");
                    if (num_ISRjets==0 && met>140 && mT>100)
                    {
                      LOG_SR("SR1");
                      FILL_SR("SR1");
                    }
                    if (num_ISRjets==1 && met>200 && mT<100 && pT_ll<100)
                    {
                      LOG_SR("SR2");
                      FILL_SR("SR2");
                    }
                  }
                }
              }
            }
          }

          //3 or more leptons
          if (preselection && met>50 && conversion_veto && nSignalLeptons>2)
          {
            LOG_SR("SR3", "SR4", "SR5", "SR6", "SR7", "SR8");

            if (nSignalTaus<2)
            {
              LOG_SR("SR3", "SR4", "SR5", "SR8");
              if ((signalLightLeptons.at(0)->abspid()==11 && signalLightLeptons.at(0)->pT()>25) || (signalLightLeptons.at(0)->abspid()==13 && signalLightLeptons.at(0)->pT()>20 && nSignalMuons>1) || (signalLightLeptons.at(0)->abspid()==13 && signalLightLeptons.at(0)->pT()>25 && nSignalMuons==1))
              {
                LOG_SR("SR3", "SR4", "SR5", "SR8");
                if (nSignalLightLeptons==3 && nSignalTaus==0)
                {
                  LOG_SR("SR3", "SR4");
                  if (mT>120 && met>200)
                  {
                    LOG_SR("SR3");
                    FILL_SR("SR3");
                  }
                  if (met>250)
                  {
                    LOG_SR("SR4");
                    FILL_SR("SR4");
                  }
                }
                if (nSignalLightLeptons==2 && nSignalTaus==1)
                {
                  LOG_SR("SR5");
                  if (mT2>50 && met>200)
                  {
                    LOG_SR("SR5");
                    FILL_SR("SR5");
                  }
                }
                if (nSignalLeptons>3)
                {
                  LOG_SR("SR8");
                  if (met>200)
                  {
                    LOG_SR("SR8");
                    FILL_SR("SR8");
                  }
                }
              }
            }

            if (nSignalLightLeptons==1 && nSignalTaus==2)
            {
              LOG_SR("SR6", "SR7");
              if ((signalLightLeptons.at(0)->abspid()==11 && signalLightLeptons.at(0)->pT()>30) || (signalLightLeptons.at(0)->abspid()==13 && signalLightLeptons.at(0)->pT()>25))
              {
                LOG_SR("SR6", "SR7");
                if (signalLeptons.at(0)->abseta()<2.1 && signalLeptons.at(1)->abseta()<2.1 && signalLeptons.at(2)->abseta()<2.1)
                {
                  LOG_SR("SR6", "SR7");
                  if (mT2>50 && met>200)
                  {
                    LOG_SR("SR6");
                    FILL_SR("SR6");
                  }
                  if (met>75)
                  {
                    LOG_SR("SR7");
                    FILL_SR("SR7");
                  }
                }
              }
            }
          }
        }

        // This function can be overridden by the derived SR-specific classes
        virtual void collect_results()
        {
COMMIT_CUTFLOWS
          //Now fill a results object with the results for each SR

          add_result(SignalRegionData(_counters.at("SR1"), 13., {12., 3.}));
          add_result(SignalRegionData(_counters.at("SR2"), 18., {18., 4.}));
          add_result(SignalRegionData(_counters.at("SR3"), 19., {19., 4.}));
          add_result(SignalRegionData(_counters.at("SR4"), 128., {142, 34.}));
          add_result(SignalRegionData(_counters.at("SR5"), 18., {22, 5.}));
          add_result(SignalRegionData(_counters.at("SR6"), 2., {1, 0.6}));
          add_result(SignalRegionData(_counters.at("SR7"), 82., {109, 28.}));
          add_result(SignalRegionData(_counters.at("SR8"), 166., {197, 42.}));
        }



        vector<double> get_mll_mT(vector<vector<const HEPUtils::Particle*>> pair_cont, vector<const HEPUtils::Particle*> leptons, HEPUtils::P4 met, int type)
        {
          vector<double> mll_mT;
          vector<vector<double>> mll_mT_container;
          for (size_t iPa=0;iPa<pair_cont.size();iPa++)
          {
            double m_ll_temp=(pair_cont.at(iPa).at(0)->mom()+pair_cont.at(iPa).at(1)->mom()).m();
            double mT_temp=0;
            for (size_t iLe=0;iLe<leptons.size();iLe++)
            {
              if (leptons.at(iLe)!=pair_cont.at(iPa).at(0) && leptons.at(iLe)!=pair_cont.at(iPa).at(1))mT_temp=sqrt(2*met.pT()*leptons.at(iLe)->pT()*(1-cos(leptons.at(iLe)->phi()-met.phi())));
            }
            double mass=0;
            if (type==0)mass=91.2;
            if (type==1)
            {
              mass=50.;
              if (pair_cont.at(iPa).at(0)->abspid()==15 || pair_cont.at(iPa).at(1)->abspid()==15)mass=60;;
            }
            vector<double> temp;
            temp.push_back(m_ll_temp);
            temp.push_back(mT_temp);
            temp.push_back(fabs(m_ll_temp-mass));
            mll_mT_container.push_back(temp);
          }

          struct mllComparison
          {
            bool operator() (vector<double> i,vector<double> j) {return (i.at(2)<j.at(2));}
          } compare_mll;

          if (mll_mT_container.size()>0)
          {
            sort(mll_mT_container.begin(),mll_mT_container.end(),compare_mll);
            mll_mT_container.at(0).pop_back();
            mll_mT=mll_mT_container.at(0);
          }
          return mll_mT;
        }

        double get_mTmin(vector<const HEPUtils::Particle*> leptons, HEPUtils::P4 met)
        {
          vector<double> mT_container;
          for (size_t iLe=0;iLe<leptons.size();iLe++)
          {
            mT_container.push_back(sqrt(2*met.pT()*leptons.at(iLe)->pT()*(1-cos(leptons.at(iLe)->phi()-met.phi()))));
          }
          sort(mT_container.begin(),mT_container.end());
          if (mT_container.size()>0)return mT_container.at(0);
          else return -1;
        }


      protected:
        void analysis_specific_reset()
        {
          for (auto& pair : _counters) { pair.second.reset(); }
        }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_SUS_16_039)


    //
    // Derived analysis class for the 2Lep0Jets SRs
    //
    class Analysis_CMS_SUS_16_039_2SSLep : public Analysis_CMS_SUS_16_039
    {

      public:
        Analysis_CMS_SUS_16_039_2SSLep()
        {
          set_analysis_name("CMS_SUS_16_039_2SSLep");
        }

        virtual void collect_results()
        {
COMMIT_CUTFLOWS
          add_result(SignalRegionData(_counters.at("SR1"), 13., {12., 3.}));
          add_result(SignalRegionData(_counters.at("SR2"), 18., {18., 4.}));
        }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_SUS_16_039_2SSLep)



    //
    // Derived analysis class for the 3Lep SRs
    //
    class Analysis_CMS_SUS_16_039_3Lep : public Analysis_CMS_SUS_16_039
    {

      public:
        Analysis_CMS_SUS_16_039_3Lep()
        {
          set_analysis_name("CMS_SUS_16_039_3Lep");
        }

        virtual void collect_results()
        {
COMMIT_CUTFLOWS
          add_result(SignalRegionData(_counters.at("SR3"), 19., {19., 4.}));
          add_result(SignalRegionData(_counters.at("SR4"), 128., {142, 34.}));
          add_result(SignalRegionData(_counters.at("SR5"), 18., {22, 5.}));
          add_result(SignalRegionData(_counters.at("SR6"), 2., {1, 0.6}));
          add_result(SignalRegionData(_counters.at("SR7"), 82., {109, 28.}));
          add_result(SignalRegionData(_counters.at("SR8"), 166., {197, 42.}));
        }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_SUS_16_039_3Lep)


  }
}
