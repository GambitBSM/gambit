// Search for single production of vector-like quarks decaying to W(l nu)b.
// ATLAS EXOT-2018-60, arXiv:2506.15515.

#include "gambit/ColliderBit/analyses/Analysis.hpp"

namespace Gambit
{
  namespace ColliderBit
  {
    class Analysis_ATLAS_EXOT_2018_60 : public Analysis
    {
    public:
      static constexpr const char* detector = "ATLAS";

      Analysis_ATLAS_EXOT_2018_60()
      {
        set_analysis_name("ATLAS_EXOT_2018_60");
        set_luminosity(140.0);
      }

      void run(const HEPUtils::Event*)
      {
        // TODO: Implement the published selection and signal-region yields.
      }

      void collect_results()
      {
      }

    protected:
      void analysis_specific_reset()
      {
      }
    };

    DEFINE_ANALYSIS_FACTORY(ATLAS_EXOT_2018_60)
  }
}
