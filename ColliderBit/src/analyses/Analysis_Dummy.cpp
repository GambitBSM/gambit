///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@kit.edu)
///  \date 2023 July
///  *********************************************


#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/analyses/AnalysisMacros.hpp"
#include "gambit/ColliderBit/Utils.hpp"
#include "gambit/ColliderBit/CMSEfficiencies.hpp"

// Dummy analysis to illustrate the usage of analysis macros

namespace Gambit
{
  namespace ColliderBit
  {

    class Analysis_Dummy : public Analysis
    {

      public:

        // Required detector sim
        static constexpr const char* detector = "CMS";

        Analysis_Dummy()
        {

          // Define a single signal region
          DEFINE_SIGNAL_REGION("SR")

          // Define multiple signal regions at one, number 1..N
          // This defines the signal regions SR1, SR2, SR3, SR4 and SR5
          DEFINE_SIGNAL_REGIONS("SR", 5)

          set_analysis_name("Dummy");
          set_luminosity(137.0);

        }

        void run(const HEPUtils::Event* event)
        {
          ////////////////////////
          // Useful definiitons //
          double mZ = 91.1876;


          //////////////////////
          // Baseline objects //

          // Define baseline objects with BASELINE(object_type, variable_name, minpT, mineta[, maxpT, maxeta, efficiency])
          BASELINE_PARTICLES(electrons, baselineElectrons, 10, 0, DBL_MAX, 2.5, CMS::eff2DEl.at("SUS_19_008"))
          BASELINE_PARTICLES(muons, baselineMuons, 10, 0, DBL_MAX, 2.4, CMS::eff2DMu.at("SUS_19_008"))
          BASELINE_PARTICLES(muons, baselineLooseMuons, 10, 0, DBL_MAX, 2.4)
          BASELINE_PARTICLE_COMBINATION(baselineLeptons, baselineElectrons, baselineMuons)

          //Same for jets, with and without efficiency. Bjets allow also for a missID efficiency
          BASELINE_JETS(jets, baselineJets, 25, 0, DBL_MAX, 2.4)
          BASELINE_BJETS(jets, baselineBJets, 25., 0., DBL_MAX, 2.4, CMS::eff2DBJet.at("CSVv2Tight"), CMS::missIDBJet.at("CSVv2Tight"))

          // Remove overlap from first argument, within certain radius
          removeOverlap(baselineJets, baselineElectrons, 0.4);

          ////////////////////
          // Signal objects //

          // Define signal objects from baseline objects, automatically order by pT (highest first)
          SIGNAL_PARTICLES(baselineElectrons, signalElectrons)
          SIGNAL_PARTICLES(baselineMuons, signalMuons)
          SIGNAL_PARTICLE_COMBINATION(signalLeptons, signalElectrons, signalMuons)
          SIGNAL_JETS(baselineJets, signalJets)
          SIGNAL_JETS(baselineBJets, signalBJets)

          // Create containers with SS, OS and OSSF pairs:
          // CREATE_PAIR(TYPE, SOURCE, CONTAINER, UNIQUE)
          // OS, SS, SF, OSSF, SSSF
          CREATE_PAIR(SS, signalLeptons, SSpairs, false)
          CREATE_PAIR(OS, signalLeptons, OSpairs, true)
          sortByParentMass(OSpairs, mZ);
          CREATE_PAIR(OSSF, signalLeptons, OSSFpairs, true)
          sortByParentMass(OSSFpairs, mZ);

          ///////////////////////////////
          // Common variables and cuts //

          // Missing ET and momentum
          double met = event->met();

          // Define variables used in cuts
          // Here we will be using the same efficiencies as in the 36invfb version, as there is no public data for this yet

          // Object sizes
          const size_t nLeptons = signalLeptons.size();
          const size_t nSSpairs = SSpairs.size();
          const size_t nOSSFpairs = OSSFpairs.size();

          const size_t nBJets = signalBJets.size();

          // Di-lepton invariant mass for OSSF pairs of light leptons
          std::vector<double> mossf;
          for(auto pair: OSSFpairs)
            mossf.push_back( (pair.at(0)->mom() + pair.at(1)->mom()).m() );
          std::sort(mossf.begin(), mossf.end());

          // Other variables, e.g. HT, etc


          //////////////////
          // Preselection //

          BEGIN_PRESELECTION
            if(nLeptons < 3 and nSSpairs == 0) return;
            if(nBJets > 0) return;
            if(nOSSFpairs > 0 and mossf.at(0) < 12.0) return;
          END_PRESELECTION


          ///////////////////////////////////
          // Event cuts and signal regions //

          if(nLeptons == 2)
          {
            LOG_CUT("SR", "SR1", "SR2")

            if(nSSpairs == 1)
            {
              LOG_CUT("SR1", "SR2")

              if(met >= 100. and met < 200) { FILL_SIGNAL_REGION("SR1") }
              if(met >= 200.) { FILL_SIGNAL_REGION("SR2") }
            }
            else
            {
              if(met <  100.) { FILL_SIGNAL_REGION("SR"); }
            }
          }
          else
          {
            return;
          }

        }

        void combine(const Analysis* other)
        {
          const Analysis_Dummy* specificOther = dynamic_cast<const Analysis_Dummy*>(other);
          for (auto& pair : _counters) { pair.second += specificOther->_counters.at(pair.first); }
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
    DEFINE_ANALYSIS_FACTORY(Dummy)

  }
}
