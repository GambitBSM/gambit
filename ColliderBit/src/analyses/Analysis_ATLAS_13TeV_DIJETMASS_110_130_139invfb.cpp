// -*- C++ -*-
#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/analyses/Cutflow.hpp"

// This is a basic toy ATLAS dijet mass analysis. A single signal region is
// defined by requiring the invariant mass of the two hardest baseline jets
// to lie between 110 and 130 GeV, together with missing transverse energy of
// at least 100 GeV.

namespace Gambit
{
  namespace ColliderBit
  {

    using namespace std;
    using namespace HEPUtils;

    /// @brief Basic ATLAS dijet mass analysis, signal region 110-130 GeV
    class Analysis_ATLAS_13TeV_DIJETMASS_110_130_139invfb : public Analysis
    {
      public:

        // Required detector sim
        static constexpr const char* detector = "ATLAS";

        EventCounter _counterSR = EventCounter("SR");

        Analysis_ATLAS_13TeV_DIJETMASS_110_130_139invfb()
        {
          analysis_specific_reset();
          set_analysis_name("ATLAS_13TeV_DIJETMASS_110_130_139invfb");
          set_luminosity(139.0);
        }

        void run(const Event* event)
        {

          // Missing transverse energy
          const double met = event->met();

          // Baseline jets
          vector<const Jet*> baselineJets;
          for (const Jet* jet : event->jets("antikt_R04"))
          {
            if (jet->pT() > 20. && jet->abseta() < 2.8) baselineJets.push_back(jet);
          }

          // Sort jets by pT, hardest first
          sortByPt(baselineJets);

          // Need at least two jets to form the dijet system
          if (baselineJets.size() < 2) return;

          // Require missing transverse energy of at least 100 GeV
          if (met < 100.) return;

          // Invariant mass of the two hardest jets
          const double mjj = (baselineJets[0]->mom() + baselineJets[1]->mom()).m();

          // Signal region: dijet mass between 110 and 130 GeV
          if (mjj > 110. && mjj < 130.)
          {
            _counterSR.add_event(event->weight(), event->weight_err());
          }

        }

        /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
        void combine(const Analysis* other)
        {
          const Analysis_ATLAS_13TeV_DIJETMASS_110_130_139invfb* specificOther = dynamic_cast<const Analysis_ATLAS_13TeV_DIJETMASS_110_130_139invfb*>(other);
          _counterSR += specificOther->_counterSR;
        }

        void collect_results()
        {
          // Made-up observed and background numbers, as this is a toy analysis with no associated publication
          add_result(SignalRegionData(_counterSR, 100., {100., 10.}));
        }

      protected:

        void analysis_specific_reset()
        {
          _counterSR.reset();
        }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(ATLAS_13TeV_DIJETMASS_110_130_139invfb)

  }
}
