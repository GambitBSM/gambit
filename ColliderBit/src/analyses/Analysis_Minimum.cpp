#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"

namespace Gambit {
  namespace ColliderBit {
    using namespace std;


    /// Basic analysis code for copying
    class Analysis_Minimum : public Analysis {
    private:

      // Variables to hold the number of events passing signal region cuts
      double _numSR;

    public:

      // Required detector sim
      static constexpr const char* detector = "ATLAS";

      Analysis_Minimum() {

        // Set the analysis name
        set_analysis_name("Minimum");

        // Set the LHC luminosity
        set_luminosity(20.3);

        // Set number of events passing cuts to zero upon initialisation
        _numSR = 0;


      }


      void run(const HEPUtils::Event* event){

        // Get the missing energy in the event
        double met = event->met();

        // Now define vectors of baseline objects,  including:
        // - retrieval of electron, muon and jets from the event)
        // - application of basic pT and eta cuts

        // Baseline electrons
        vector<HEPUtils::Particle*> baselineElectrons;
        for (HEPUtils::Particle* electron : event->electrons()) {
          if (electron->pT() > 10. && fabs(electron->eta()) < 2.47) baselineElectrons.push_back(electron);
        }

        // Baseline muons
        vector<HEPUtils::Particle*> baselineMuons;
        for (HEPUtils::Particle* muon : event->muons()) {
          if (muon->pT() > 10. && fabs(muon->eta()) < 2.4) baselineMuons.push_back(muon);
        }

        // Baseline jets
        vector<HEPUtils::Jet*> baselineJets;
        for (HEPUtils::Jet* jet : event->jets()) {
          if (jet->pT() > 20. && fabs(jet->eta()) < 4.5) baselineJets.push_back(jet);
        }

        // Could add ATLAS style overlap removal here
        // See Analysis_ATLAS_0LEP_20invfb for example

        // Could add ATLAS or CMS efficiencies here
        // See Analysis_ATLAS_2LEPEW_20invfb.cpp for an example

        int nElectrons = baselineElectrons.size();
        int nMuons = baselineMuons.size();
        int nJets = baselineJets.size();

        std::cerr << "nElectrons " << nElectrons << " nMuons " << nMuons << " nJets " << nJets << " met " << met << std::endl;

        // Increment number of events passing signal region cuts
        // Dummy signal region: need 2 jets, met > 150 and no leptons

        if((nElectrons+nMuons)==0 && nJets==2 && met>150.)_numSR++;

      }


      /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
      void combine(const Analysis* other)
      {
        const Analysis_Minimum* specificOther = dynamic_cast<const Analysis_Minimum*>(other);
        _numSR += specificOther->_numSR;
      }


      void collect_results() {

        // Now fill a results object with the result for our signal region
        // We have made up a number of observed events
        // We have also made up a number of predicted background events (with a made up uncertainty)
        SignalRegionData results_SR;
        results_SR.sr_label = "SR"; // label must be unique for each signal region
        results_SR.n_observed = 100.; // set number of observed events (in LHC paper)
        results_SR.n_background = 95.; // set number of predicted background events (in LHC paper)
        results_SR.background_sys = 9.5; // set background uncertainty (in LHC paper)
        results_SR.signal_sys = 0.; // set signal uncertainty
        results_SR.n_signal = _numSR; // set this to number of signal events incremented in the analysis above
        add_result(results_SR);

      }


    protected:
      void analysis_specific_reset() {
        _numSR = 0;
      }

      ///////////////////

    };

    DEFINE_ANALYSIS_FACTORY(Minimum)

  }
}
