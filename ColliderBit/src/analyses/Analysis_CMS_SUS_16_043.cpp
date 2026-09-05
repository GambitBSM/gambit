///
///  \author Rose Kudzman-Blais
///  \date 2017 May
///
///  \author Anders Kvellestad
///  \date 2021 Oct
///
///  *********************************************

// Based on confnote http://cms-results.web.cern.ch/cms-results/public-results/preliminary-results/SUS-16-043/index.html
// and the paper version http://cms-results.web.cern.ch/cms-results/public-results/publications/SUS-16-043/index.html

// Renamed from: 
//      Analysis_CMS_13TeV_1LEPbb_36invfb

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

    class Analysis_CMS_SUS_16_043 : public Analysis
    {
    private:

      static constexpr const char* CUTFLOW_NAME = "CMS-SUS-16-043";

    public:

      // Required detector sim
      static constexpr const char* detector = "CMS";

      Analysis_CMS_SUS_16_043()
      {
        _counters["SRA"] = EventCounter("SRA");
        _counters["SRB"] = EventCounter("SRB");

        set_analysis_name("CMS_SUS_16_043");
        set_luminosity(35.9);

        #ifdef CHECK_CUTFLOW
          _cutflows.addCutflow(CUTFLOW_NAME, {
            "All events",
            "$\\geq$ 1 signal lepton; $E_{T}^{miss} > 50 GeV$",
            "2nd lepton veto",
            "Tau veto",
            "2 jets",
            "2 bjets",
            "$90 < m_{bb} < 150 GeV$",
            "$m_{CT} > 170 GeV$",
            "$E_{T}^{miss} > 125 GeV$",
            "$m_{T} > 150 GeV$"
          });
        #endif

      }


      void run(const HEPUtils::Event* event)
      {

        double met = event->met();

        // Baseline objects
        //@note Numbers digitized from https://twiki.cern.ch/twiki/pub/CMSPublic/SUSMoriond2017ObjectsEfficiency/2d_full_pteta_el_043_ttbar.pdf
        const vector<double> aEl={0,0.8,10.};
        const vector<double> bEl={0,40.,50.,10000.};
        const vector<double> cEl={0.654,0.705,0.731,0.665,0.655,0.722};
        HEPUtils::BinnedFn2D<double> _eff2dEl(aEl,bEl,cEl);
        vector<const HEPUtils::Particle*> baselineElectrons;
        for (const HEPUtils::Particle* electron : event->electrons())
        {
          bool isEl=has_tag(_eff2dEl, electron->abseta(), electron->pT());
          if (electron->pT()>5. && electron->abseta()<2.5 && isEl)baselineElectrons.push_back(electron);
        }

        //@note Numbers digitized from https://twiki.cern.ch/twiki/pub/CMSPublic/SUSMoriond2017ObjectsEfficiency/2d_full_pteta_mu_043_ttbar.pdf
        const vector<double> aMu={0,0.9,1.2,10.};
        const vector<double> bMu={0,30.,40.,50.,10000.};
        const vector<double> cMu={0.761,0.804,0.814,0.805,0.769,0.813,0.846,0.82,0.819,0.847,0.834,0.852};
        HEPUtils::BinnedFn2D<double> _eff2dMu(aMu,bMu,cMu);
        vector<const HEPUtils::Particle*> baselineMuons;
        for (const HEPUtils::Particle* muon : event->muons())
        {
          bool isMu=has_tag(_eff2dMu, muon->abseta(), muon->pT());
          if (muon->pT()>5. && muon->abseta()<2.4 && isMu)baselineMuons.push_back(muon);
        }

        vector<const HEPUtils::Particle*> baselineTaus;
        for (const HEPUtils::Particle* tau : event->taus())
        {
          if (tau->pT()>20. && tau->abseta()<2.3)baselineTaus.push_back(tau);
        }

        vector<const HEPUtils::Jet*> baselineJets;
        for (const HEPUtils::Jet* jet : event->jets("antikt_R04"))
        {
          if (jet->pT()>25. &&fabs(jet->eta())<2.4)baselineJets.push_back(jet);
        }

        // Signal objects
        vector<const HEPUtils::Particle*> signalLeptons;
        vector<const HEPUtils::Particle*> signalElectrons;
        vector<const HEPUtils::Particle*> signalMuons;
        vector<const HEPUtils::Jet*> signalJets;
        vector<const HEPUtils::Jet*> signalBJets;

        for (size_t iEl=0;iEl<baselineElectrons.size();iEl++)
        {
          if (baselineElectrons.at(iEl)->pT()>30. && baselineElectrons.at(iEl)->abseta()<1.44)signalElectrons.push_back(baselineElectrons.at(iEl));
        }

        for (size_t iMu=0;iMu<baselineMuons.size();iMu++)
        {
          if (baselineMuons.at(iMu)->pT()>25. && baselineMuons.at(iMu)->abseta()<2.1)signalMuons.push_back(baselineMuons.at(iMu));
        }

        for (size_t iJet=0;iJet<baselineJets.size();iJet++)
        {
          if (baselineJets.at(iJet)->pT()>30.)
          {
            signalJets.push_back(baselineJets.at(iJet));
            if (baselineJets.at(iJet)->btag())signalBJets.push_back(baselineJets.at(iJet));
          }
        }
        vector<const HEPUtils::Jet*> signalBJets_temp=signalBJets;
        applyEfficiency(signalBJets_temp, CMS::eff2DBJet.at("CSVv2Medium"));
        if (signalBJets_temp.size()>0)
        {
          applyEfficiency(signalBJets_temp, CMS::eff2DBJet.at("CSVv2Loose"));
          for (size_t iJet=0;iJet<signalBJets_temp.size();iJet++)
          {
            if (find(signalBJets.begin(),signalBJets.end(),signalBJets_temp.at(iJet))==signalBJets.end())signalBJets.push_back(signalBJets_temp.at(iJet));
          }
        }
        if (signalBJets_temp.size()==0)signalBJets.clear();

        signalLeptons=signalElectrons;
        signalLeptons.insert(signalLeptons.end(),signalMuons.begin(),signalMuons.end());
        int nSignalLeptons=signalLeptons.size();
        int nSignalElectrons=signalElectrons.size();
        int nSignalMuons=signalMuons.size();
        int nSignalJets=signalJets.size();
        int nSignalBJets=signalBJets.size();

        //Variables
        bool preselection=false;
        bool lepton2_veto=true;
        bool tau_veto=true;
        double mCT=0;
        double mbb=0;
        double mT=0;

        const vector<double> aLep={0,10.};
        const vector<double> bLep={0,10000.};
        const vector<double> cEl_Trig={0.825};
        const vector<double> cMu_Trig={0.885};
        HEPUtils::BinnedFn2D<double> _eff2dEl_Trig(aLep,bLep,cEl_Trig);
        HEPUtils::BinnedFn2D<double> _eff2dMu_Trig(aLep,bLep,cMu_Trig);

        if ((baselineMuons.size()+baselineElectrons.size())>1)lepton2_veto=false;
        if (baselineTaus.size()>0)tau_veto=false;
        if (nSignalLeptons>0 && met>50. && lepton2_veto && tau_veto && nSignalJets==2 && nSignalBJets==2)
        {
          if (nSignalMuons==1)
          {
            bool hasTrig=has_tag(_eff2dMu_Trig, signalMuons.at(0)->abseta(), signalMuons.at(0)->pT());
            if (hasTrig)preselection=true;
          }
          if (nSignalElectrons==1)
          {
            bool hasTrig=has_tag(_eff2dEl_Trig, signalElectrons.at(0)->abseta(), signalElectrons.at(0)->pT());
            if (hasTrig)preselection=true;
          }
        }

        if (nSignalBJets>1)
        {
          mCT=sqrt(2*signalBJets.at(0)->pT()*signalBJets.at(1)->pT()*(1+cos(signalBJets.at(0)->mom().deltaPhi(signalBJets.at(1)->mom()))));
          mbb=(signalBJets.at(0)->mom()+signalBJets.at(1)->mom()).m();
        }
        if (signalLeptons.size()>0)mT=sqrt(2*signalLeptons.at(0)->pT()*met*(1-cos(signalLeptons.at(0)->mom().deltaPhi(event->missingmom()))));

        //Signal Regions
        if (preselection && mbb>90 && mbb<150 && mCT>170. && met>125. && mT>150.)
        {
          //SRA
          if (met>125. && met<200.) _counters.at("SRA").add_event(event);
          //SRB
          if (met>200.) _counters.at("SRB").add_event(event);
        }

        #ifdef CHECK_CUTFLOW
          const double w = event->weight();
          const bool cf1 = (nSignalLeptons >= 1 && met > 50.);
          const bool cf2 = (cf1 && lepton2_veto);
          const bool cf3 = (cf2 && tau_veto);
          const bool cf4 = (cf3 && nSignalJets == 2);
          const bool cf5 = preselection;
          const bool cf6 = (cf5 && mbb > 90. && mbb < 150.);
          const bool cf7 = (cf6 && mCT > 170.);
          const bool cf8 = (cf7 && met > 125.);
          const bool cf9 = (cf8 && mT > 150.);

          _cutflows[CUTFLOW_NAME].fillinit(w);
          _cutflows[CUTFLOW_NAME].fillnext(
            std::vector<bool>{true, cf1, cf2, cf3, cf4, cf5, cf6, cf7, cf8, cf9},
            w
          );
        #endif

      }


      void collect_results()
      {
        add_result(SignalRegionData(_counters.at("SRA"), 11., {7.5, 2.5}));
        add_result(SignalRegionData(_counters.at("SRB"), 7., {8.7, 2.2}));

        // Covariance
        // - We know that the correlation coefficient is 0.61, see http://cms-results.web.cern.ch/cms-results/public-results/preliminary-results/SUS-16-043/index.html
        static const vector< vector<double> > BKGCOV = {
          { 6.25,   3.355 },  // cov(A,A), cov(A,B)
          { 3.355,  4.84  },  // cov(B,A), cov(B,B)
        };
        set_covariance(BKGCOV);

COMMIT_CUTFLOWS
      }


    protected:
      void analysis_specific_reset()
      {
        for (auto& pair : _counters) { pair.second.reset(); }
      }

    };


    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_SUS_16_043)


  }
}
