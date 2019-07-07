#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"

namespace Gambit {
  namespace ColliderBit {
    using namespace std;


    /// Dummy analysis code with a hard-coded return including a SR covariance matrix
    class Analysis_Covariance : public Analysis{
    private:

      // Variables that holds the number of events passing
      // signal region cuts
      int _numSR;

    public:

      // Required detector sim
      static constexpr const char* detector = "ATLAS";

      Analysis_Covariance()
      {
        set_analysis_name("Covariance");
        set_luminosity(30.); // fb
      }


      void run(const HEPUtils::Event*) {}

      /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
      void combine(const Analysis*) {}

      void collect_results()
      {
        // Now fill a results object with the result for two signal regions
        SignalRegionData results_SR1;
        results_SR1.sr_label = "SR1"; // label must be unique for each signal region
        results_SR1.n_observed = 100; // set number of observed events (in LHC paper)
        results_SR1.n_background = 95; // set number of predicted background events (in LHC paper)
        results_SR1.background_sys = 9.5; // set background uncertainty (in LHC paper)
        results_SR1.signal_sys = 0; // set signal uncertainty
        results_SR1.n_signal = 120; // dummy number of signal events (usually incremented in the analysis code)
        add_result(results_SR1);

        SignalRegionData results_SR2;
        results_SR2.sr_label = "SR2"; // label must be unique for each signal region
        results_SR2.n_observed = 10; // set number of observed events (in LHC paper)
        results_SR2.n_background = 9; // set number of predicted background events (in LHC paper)
        results_SR2.background_sys = 4; // set background uncertainty (in LHC paper)
        results_SR2.signal_sys = 0; // set signal uncertainty
        results_SR2.n_signal = 15; // dummy number of signal events (usually incremented in the analysis code)
        add_result(results_SR2);

        // Hard-code the a covariance matrix  between these (representing the bkg sys values above, rotated by 30 deg)
        set_covariance({{71.6875, 32.1512},{32.1512, 34.5625}});

      }


    protected:
      void analysis_specific_reset() {
        _numSR = 0;
      }


      ///////////////////

    };

    DEFINE_ANALYSIS_FACTORY(Covariance)

  }
}
