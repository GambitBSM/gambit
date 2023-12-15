///
///  \author Anders Kvellestad
///          (anders.kvellestad@fys.uio.no)
///  \date 2023 December
///  *********************************************


#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/analyses/AnalysisMacros.hpp"
#include "gambit/ColliderBit/Utils.hpp"
#include "gambit/ColliderBit/CMSEfficiencies.hpp"

// An analysis that is used to get a broad overview of relevant baseline selections

namespace Gambit
{
  namespace ColliderBit
  {

    class Analysis_Baselines : public Analysis
    {

      public:

        // Required detector sim
        static constexpr const char* detector = "CMS";

        Analysis_Baselines()
        {

          // Define a single signal region and the associated cuts
          // DEFINE_SIGNAL_REGION(SRNAME, CF1, CF2, ...)
          // Fills _counters and _cutflows variables
          // By default the Preselection and Final cuts are always defined
          DEFINE_SIGNAL_REGION("SR")

          // Define multiple signal regions at one, number 1..N
          // This defines the signal regions SR1, SR2, SR3, SR4 and SR5
          DEFINE_SIGNAL_REGIONS("SR", 5)

          set_analysis_name("Baselines");
          set_luminosity(139.0);

        }

        void run(const HEPUtils::Event* event)
        {
          ////////////////////////
          // Useful definiitons //
          double mZ = 91.1876;
          // double mh = 125.11;


          //////////////////////
          // Baseline objects //

          // Baseline selections inspired by 
          // - Analysis_CMS_13TeV_MultiLEP_137invfb
          // - Analysis_CMS_13TeV_2OSLEP_137invfb

          // HEPUtils objects: photons, electrons, muons, taus, invisibles, jets
          // HEPUtils variables: met, missingmom

          // Define baseline objects with BASELINE(object_type, variable_name, minpT, mineta[, maxpT, maxeta, efficiency])
          BASELINE_PARTICLES(event->electrons(), baselineElectrons, 10, 0, DBL_MAX, 2.5, CMS::eff2DEl.at("SUS_19_008"))
          BASELINE_PARTICLES(event->muons(), baselineMuons, 10, 0, DBL_MAX, 2.4, CMS::eff2DMu.at("SUS_19_008"))
          BASELINE_PARTICLE_COMBINATION(baselineLeptons, baselineElectrons, baselineMuons)

          BASELINE_PARTICLES(event->photons(), baselinePhotons, 50, 0, DBL_MAX, 2.4)

          BASELINE_JETS(event->jets("antikt_R04"), baselineJets, 25, 0, DBL_MAX, 2.4)
          // TODO: Add baseline jets with antikt_R08 ?

          // Remove overlap from first argument, within certain radius
          removeOverlap(baselineElectrons, baselineMuons, 0.01);
          removeOverlap(baselineJets, baselineElectrons, 0.4);
          removeOverlap(baselineJets, baselineMuons, 0.4);
          removeOverlap(baselineJets, baselinePhotons, 0.4);
          removeOverlap(baselinePhotons, baselineElectrons, 0.3);
          removeOverlap(baselinePhotons, baselineMuons, 0.3);

          // Get b-jets from the surviving jets
          BASELINE_BJETS(baselineJets, baselineBJets, 25., 0., DBL_MAX, 2.4, CMS::eff2DBJet.at("CSVv2Medium"), CMS::misIDBJet.at("CSVv2Medium"))


          ////////////////////
          // Signal objects //

          // Define signal objects from baseline objects, automatically order by pT (highest first)
          SIGNAL_PARTICLES(baselineElectrons, electrons)
          SIGNAL_PARTICLES(baselineMuons, muons)
          SIGNAL_PARTICLE_COMBINATION(leptons, electrons, muons)
          SIGNAL_JETS(baselineJets, jets)
          SIGNAL_JETS(baselineBJets, bjets)

          // Create containers with SS, OS and OSSF pairs:
          // CREATE_PAIR(TYPE, SOURCE, CONTAINER, UNIQUE)
          // OS, SS, SF, OSSF, SSSF
          CREATE_PAIR(SS, leptons, SSpairs, false)
          CREATE_PAIR(OS, leptons, OSpairs, true)
          sortByParentMass(OSpairs, mZ);
          CREATE_PAIR(OSSF, leptons, OSSFpairs, true)
          sortByParentMass(OSSFpairs, mZ);

          ///////////////////////////////
          // Common variables and cuts //

          // n_lep * n_jet * n_met * n_bveto * n_OSSF * n_SS *  n_Zcand * n_Hcand

          // Object sizes
          const size_t nLeptons = leptons.size();
          const size_t nSSpairs = SSpairs.size();
          const size_t nOSpairs = OSpairs.size();
          const size_t nOSSFpairs = OSSFpairs.size();
          const size_t nBJets = bjets.size();

          // Missing ET and momentum
          double met = event->met();

          // HT
          double HT = 0;
          for (const HEPUtils::Jet* jet : jets)
          {
            HT += jet->pT();
          }

          // // Di-lepton invariant mass for OSSF pairs of light leptons
          // std::vector<double> mossf;
          // for(auto pair: OSSFpairs)
          //   mossf.push_back( (pair.at(0)->mom() + pair.at(1)->mom()).m() );
          // std::sort(mossf.begin(), mossf.end());

          // // Other variables, e.g. HT, etc


          // //////////////////
          // // Preselection //

          // BEGIN_PRESELECTION
          //   if(nLeptons < 3 and nSSpairs == 0) return;
          //   if(nBJets > 0) return;
          //   if(nOSSFpairs > 0 and mossf.at(0) < 12.0) return;
          // END_PRESELECTION


          // ///////////////////////////////////
          // // Event cuts and signal regions //

          // if(nLeptons == 2)
          // {
          //   LOG_CUT("SR", "SR1", "SR2")

          //   if(nSSpairs == 1)
          //   {
          //     LOG_CUT("SR1", "SR2")

          //     if(met >= 100. and met < 200) { FILL_SIGNAL_REGION("SR1") }
          //     if(met >= 200.) { FILL_SIGNAL_REGION("SR2") }
          //   }
          //   else
          //   {
          //     if(met <  100.) { FILL_SIGNAL_REGION("SR"); }
          //   }
          // }
          // else
          // {
          //   return;
          // }

          return; 
        }


        virtual void collect_results()
        {

          // Commit the results for signal regions, included observed and bacground counts
          // COMMIT_SIGNAL_REGION(SR, OBS, BKG, BKG_ERR)

          COMMIT_SIGNAL_REGION("SR", 53., 34., 2.)

          // Add cutflow data to the analysis results
          COMMIT_CUTFLOWS
        }

      protected:

        void analysis_specific_reset()
        {
          for (auto& pair : _counters) { pair.second.reset(); }
        }


    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(Baselines)

  }
}
