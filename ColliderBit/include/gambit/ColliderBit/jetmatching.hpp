//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Performs Jet Matching on events
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Chris Chang
///  \date   2023
///
///  *********************************************

#include "gambit/Utils/util_functions.hpp"
#include "gambit/ColliderBit/lhef2heputils.hpp"
#include "HepMC3/LHEF.h"
#include "gambit/ColliderBit/ColliderBit_eventloop.hpp"
#include "gambit/ColliderBit/colliders/Pythia8/Py8EventConversions.hpp"

namespace Gambit
{

  namespace ColliderBit
  {

    /// Simply take the hard Scattering Event and pass it on through
    void nojetmatching(HEPUtils::Event& result)
    {
      using namespace Pipes::nojetmatching; 
      result.clear();
      (*Dep::HardScatteringEvent).cloneTo(result);
    }

    /// A function that sets the event weight to zero
    /// This is used if the event should be removed at the jet matching step
    void setEventWeight_zero(HEPUtils::Event& event)
    {
      event.set_weight(0.0);
      event.set_weight_err(0.0);
    }
    
    /// Compare jet pT for sorting
    bool sortPT(HEPUtils::Jet* a, HEPUtils::Jet* b) {
      return a->pT2() >= b->pT2();
    }
    
    /// A function that reads in Les Houches Event files and converts them to HEPUtils::Event format
    /// This is largely copied from getLHEvent.cpp with small tweaks
    /// Returns false until the end of the file
    bool getMGLHEvent_HEPUtils(HEPUtils::Event& result, LHEF::Reader& lhe, double& jet_pt_min)
    {

      result.clear();

      // Attempt to read the next LHE event as a HEPUtils event. If there are no more events, wrap up the loop and skip the rest of this iteration.
      bool event_retrieved = true;
      #pragma omp critical (reading_LHEvent)
      {
        if (lhe.readEvent()) get_HEPUtils_event(lhe, result, jet_pt_min);
        else event_retrieved = false;
      }
      if (not event_retrieved)
      {
        // Report that it is at the end of the file
        return true;
      }
      
      return false;

    }

    /// Perform jetmatching on an event from Pythia and MadGraph
    /// TODO: This is just a first simple function to get the right inputs and outputs
    /// TODO: Check that the static uses aren't a problem for different parameter points
    template<typename PythiaT, typename EventT, typename hepmc_writerT>
    void jetmatching_dummy(HEPUtils::Event& result,
                           const HEPUtils::Event& pythia_event,
                           const Py8Collider<PythiaT,EventT,hepmc_writerT>& HardScatteringSim,
                           const int iteration,
                           const safe_ptr<Options>& runOptions)
    {
      // If in any other special iteration, do nothing
      if (iteration <= BASE_INIT) return;
      
      // Copy the output of the jet matched event from the pythia event
      pythia_event.cloneTo(result);
      
      std::string lhef_filename = HardScatteringSim.get_LHE_path();
      static bool first = true;
      if (first)
      {
        if (not Utils::file_exists(lhef_filename)) throw std::runtime_error("LHE file "+lhef_filename+" not found.  Quitting...");
        first = false;
      }
      
      
      // Pull the event from MadGraph
      HEPUtils::Event MadGraphEvent;
      static LHEF::Reader lhe(lhef_filename);
      
      // Get minimum pT for a jet
      double jet_pt_min = runOptions->getValueOrDef<double>(10.0, "jet_pt_min");
      
      // Check that we still have events to process
      bool end_of_file = getMGLHEvent_HEPUtils(MadGraphEvent, lhe, jet_pt_min);
      
      if (end_of_file) {return;} // TODO: Make sure it has the right end condition
      
      
      // Extract the partons from the MG event
      std::vector<HEPUtils::Jet*> partons = MadGraphEvent.jets();
      
      // Sort the partons in order of highest pT
      std::sort(partons.begin(), partons.end(), sortPT);
      
      // Extract the jets from the pythia event
      std::vector<const HEPUtils::Jet*> jets = pythia_event.jets();
      
      // Match parton to jet
      bool matched_event = false;
      double deltaR_match = runOptions->getValueOrDef<double>(0.7, "deltaR_match"); // TODO: Work out a good default to choose
      
      // Loop over each parton
      double softest_matched_jet_pt;
      size_t Nmatched_partons = 0;
      for (size_t i=0; i <  partons.size(); i++)
      {
        HEPUtils::Jet* parton = partons[i];
        
        double closestdeltaR = deltaR_match; // Setting initial value as large as a matched jet deltaR could be
        size_t closestjet;
        bool matched_parton = false;
        // Loop over each jet
        for (size_t j=0; j <  jets.size(); j++)
        {
          const HEPUtils::Jet* jet = jets[i];
          // Calculate the deltaR of between the parton and jet
          double deltaR = (parton->mom()).deltaR_eta(jet->mom());
          if (deltaR < deltaR_match && deltaR < closestdeltaR)
          {
            closestdeltaR = deltaR;
            closestjet = j;
            softest_matched_jet_pt = (jet->mom()).pT();
            matched_parton = true;
          }
          
        }
        
        if (matched_parton)
        {
          // Add to the number of matched partons
          Nmatched_partons = Nmatched_partons + 1;
          // Remove the jet from the list if it is matched
          jets.erase(jets.begin() + closestjet);
        }
        else
        {
          // Exit the loop early if we know that one of the partons isn't matched
          break;
        }
        
      }
      
      // If number of matched partons is equal to total number of partons, event is matched (unless the next condition isn't met)
      if (Nmatched_partons == partons.size())
      {
        matched_event = true;
      }
      
      // If there are any leftover jets that are not softer than the softest matched jet, matching has failed
      // TODO: Note: With my test sample, this is stopping a big portion of these from being matched.
      if (Nmatched_partons == partons.size() && jets.size() > 0)
      {
        // Find the hardest remaining jet
        double hardest_nonmatched_jet_pt = (jets[0]->mom()).pT();
        for(size_t j=0; j <  jets.size(); j++)
        {
          if ((jets[j]->mom()).pT() > hardest_nonmatched_jet_pt)
          {
            hardest_nonmatched_jet_pt = (jets[j]->mom()).pT();
          }
        }
        
        if (softest_matched_jet_pt < hardest_nonmatched_jet_pt)
        {
          matched_event = false;
        }
      }
      
      // If fails matching, set pythia event weight to zero
      if (not matched_event)
      {
        setEventWeight_zero(result);
      }
      
    }

    /// Perform Jet matching with a specific Pythia
    #define GET_JETMATCHER(NAME, PYTHIA_COLLIDER_TYPE)           \
    void NAME(HEPUtils::Event& result)                     \
    {                                                            \
      using namespace Pipes::NAME;                               \
      jetmatching_dummy(result, *Dep::HardScatteringEvent, *Dep::HardScatteringSim,   \
      *Loop::iteration, runOptions);                                        \
                                                                 \
    }                                                            


  }

}
