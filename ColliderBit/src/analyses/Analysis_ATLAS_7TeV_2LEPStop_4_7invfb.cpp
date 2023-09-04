//
// Created by dsteiner on 26/07/18.
// Amended by Martin White on 08/03/19
//
// Based on https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/PAPERS/SUSY-2012-04/ (arXiv:1208.4305)

#include "gambit/ColliderBit/ATLASEfficiencies.hpp"
#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/analyses/Cutflow.hpp"
#include "gambit/ColliderBit/analyses/AnalysisUtil.hpp"
#include "gambit/ColliderBit/Utils.hpp"

namespace Gambit
{
  namespace ColliderBit
  {

    using namespace std;
    using namespace HEPUtils;

    class Analysis_ATLAS_7TeV_2LEPStop_4_7invfb : public Analysis {

    public:

      // Required detector sim
      static constexpr const char* detector = "ATLAS";

      double numEE=0;
      double numUU=0;
      double numEU=0;


      Analysis_ATLAS_7TeV_2LEPStop_4_7invfb()
      {
        set_analysis_name("ATLAS_7TeV_2LEPStop_4_7invfb");
        set_luminosity(4.7);
        //clear();
      }

      void run(const Event *event)
      {


        std::vector<const Particle*> electrons = event->electrons();
        std::vector<const Particle*> muons = event->muons();
        std::sort(electrons.begin(), electrons.end(), AnalysisUtil::sortParticlesByPt);
        std::sort(muons.begin(), muons.end(), AnalysisUtil::sortParticlesByPt);

        // get the jets and leptons filtered by their pt and eta requirements
        electrons = AnalysisUtil::filterPtEta(electrons, 10, 2.47);
        muons = AnalysisUtil::filterPtEta(muons, 10, 2.4);
        std::vector<const Jet*> jets = AnalysisUtil::filterPtEta(event->jets(), 20, 4.5);

        // check if any of the triggers were triggered
        bool eeTrigger = AnalysisUtil::isMultipleParticleTriggered(electrons, {17, 17});
        bool uuTrigger = AnalysisUtil::isMultipleParticleTriggered(muons, {12, 12});
        bool euTrigger =
          AnalysisUtil::isSingleParticleTriggered(electrons, 15) &&
          AnalysisUtil::isSingleParticleTriggered(muons, 10);
        bool triggered = eeTrigger || uuTrigger || euTrigger;

        // do overlap removal
        jets = AnalysisUtil::jetLeptonOverlapRemoval(jets, electrons, 0.2);
        electrons = AnalysisUtil::leptonJetOverlapRemoval(electrons, jets, 0.4);
        muons = AnalysisUtil::leptonJetOverlapRemoval(muons, jets, 0.4);

        // This uses 8TeV tight electron selection, but it is close enough to the 7TeV implementation so we still use it
        ATLAS::applyTightIDElectronSelection(electrons);

        // fill a vector with all of the leptons
        std::vector<const Particle*> leptons;
        leptons.insert(leptons.end(), electrons.begin(), electrons.end());
        leptons.insert(leptons.end(), muons.begin(), muons.end());

        // sort jets and leptons by pT
        std::sort(jets.begin(), jets.end(), AnalysisUtil::sortJetsByPt);
        std::sort(leptons.begin(), leptons.end(), AnalysisUtil::sortParticlesByPt);

        // minimum requirements
        if (leptons.size() != 2 || jets.empty() || !triggered)
          {
            return;
          }

        if (!AnalysisUtil::oppositeSign(leptons[0], leptons[1]))
          {
            return;
          }

        const Particle* lep0 = leptons[0];
        const Particle* lep1 = leptons[1];

        // calculate discriminating variables
        double mll = (*lep0 + *lep1).m();
        bool zVeto = mll <= 81 || mll >= 101;

        double Ht = lep0->pT() + lep1->pT();
        for (const Jet* jet : jets)
          {
            Ht += jet->pT();
          }
        double Met = event->met();
        double MetSig = Met / std::sqrt(Ht);

        // any channel
        if (lep0->pT() < 30 && jets[0]->pT() > 25 && Met > 20 && MetSig > 7.5 && mll > 20)
          {
            // ee or mu-mu channel
            if (zVeto)
              {
                // ee channel
                if (electrons.size() == 2 && electrons[0]->pT() > 17)
                  {
                    numEE += event->weight();
                  }
                // mu-mu channel
                if (muons.size() == 2 && muons[0]->pT() > 12 && AnalysisUtil::muonFilter7TeV(muons))
                  {
                    numUU += event->weight();
                  }
              }
            // e-mu channel
            if (muons.size() == 1 && electrons.size() == 1 && electrons[0]->pT() > 17 && muons[0]->pT() > 12)
              {
                numEU += event->weight();
              }
          }
        // cout << numEE << ", " << numEU << ", " << numUU << endl;
      }

      /*void Analysis_ATLAS_7TeV_2LEPStop_4_7invfb::scale(double factor)
      {
        HEPUtilsAnalysis::scale(factor);
        cout << "SAVE_XSEC:" << xsec() << endl;
        auto save = [](double value, std::string name)
          {
            cout << "SAVE_START:" << name << endl;
            cout << value << endl;
            cout << "SAVE_END" << endl;
          };
        save(numEE, "numEE");
        save(numUU, "numUU");
        save(numEU, "numEU");
        }*/

      void combine(const Analysis* other)
      {
        const Analysis_ATLAS_7TeV_2LEPStop_4_7invfb* specificOther = dynamic_cast<const Analysis_ATLAS_7TeV_2LEPStop_4_7invfb*>(other);


        // Here we will add the subclass member variables:
        numEE += specificOther->numEE;
        numEU += specificOther->numEU;
        numUU += specificOther->numUU;

      }


      void collect_results()
      {
        add_result(SignalRegionData("ee", 48, {numEE,  0.}, {61., 6.}));
        add_result(SignalRegionData("eu", 188, {numEU,  0.}, {189., 21.}));
        add_result(SignalRegionData("uu", 195, {numUU,  0.}, {190., 31.}));

        // std::cout << "Results ee " << numEE << std::endl;
        // std::cout << "Results emu " << numEU << std::endl;
        // std::cout << "Results mumu " << numUU << std::endl;

      }

    protected:
      void analysis_specific_reset()
      {
        numEE = 0;
        numUU = 0;
        numEU = 0;
      }
    };

    DEFINE_ANALYSIS_FACTORY(ATLAS_7TeV_2LEPStop_4_7invfb)
  }
}
