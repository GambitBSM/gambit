//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  ColliderBit event loop functions returning
///  events after detector simulation.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Chris Chang
///  \date   2023
///
///  *********************************************

namespace Gambit
{

  namespace ColliderBit
  {

    /// A function that sets the event weight to zero
    /// This is used if the event should be removed at the jet matching step
    void setEventWeight_zero(HEPUtils::Event& event)
    {
      event.set_weight(0.0);
      event.set_weight_err(0.0);
    }
    
    /// Compare jet pT for sorting
    bool sortPT(HEPUtils::Jet a, HEPUtils::Jet b) {
      return a.pT2() >= b.pT2();
    }
    
    /// A function that reads in Les Houches Event files and converts them to HEPUtils::Event format
    /// This is largely copied from getLHEvent.cpp with small tweaks
    /// Returns false until the end of the file
    bool getMGLHEvent_HEPUtils(HEPUtils::Event& result, LHEF::Reader& lhe)
    {

      result.clear();

      // Get yaml option
      const static double jet_pt_min = runOptions->getValueOrDef<double>(10.0, "jet_pt_min");

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

    /// Simply take the hard Scattering Event and pass it on through
    void nojetmatching(HEPUtils::Event& result)
    {
      using namespace Pipes::nojetmatching; 
      result.clear();
      result = *Dep::Dep::HardScatteringEvent;  
    }

    /// Perform jetmatching on an event from Pythia and MadGraph
    /// TODO: This is just a first simple function to get the right inputs and outputs
    /// TODO: Check that the static uses aren't a problem for different parameter points
    template<typename PythiaT, typename EventT, typename hepmc_writerT>
    void jetmatching_dummy(HEPUtils::Event& pythia_event,
                           Py8Collider<PythiaT,EventT,hepmc_writerT>& HardScatteringSim)
    {
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
      
      
      // Don't do anything during special iterations TODO: Only do something during the iteration I want
      if (*Loop::iteration < 0) return;
      
      bool end_of_file = getMGLHEvent_HEPUtils(MadGraphEvent, lhe);
      
      if (end_of_file) {return;} // TODO: Make sure it has the right end condition
      
      
      // Extract the partons from the MG event
      vector<HEPUtils::Jet> partons = MadGraphEvent.jets();
      
      // Sort the partons in order of highest pT
      sortByPt(&partons); // TODO: This might fail if I didn't pass the right type through
      
      // Extract the jets from the pythia event
      vector<HEPUtils::Jet> jets = pythia_event.jets();
      
      
      // Match parton to jet
      bool matched_event = false;
      double deltaR_match = 10000.0; // TODO: Pull this number from YAML, and find a good default (i picked a silly number to remember)
      // Loop over each parton
      for (size_t i=0; = <  partons.size(); i++)
      {
        HEPUtils::Jet parton = partons[i];
        
        double closestdeltaR;
        size_t closestjet;
        bool matched_parton = false;
        // Loop over each jet
        for (size_t j=0; = <  jets.size(); j++)
        {
          HEPUtils::Jet jet = jets[i];
          // Calculate the deltaR of between the parton and jet
          double deltaR = parton.deltaR_eta(jet);
          if (deltaR < deltaR_match && deltaR < closestdeltaR)
          {
            closestdeltaR = deltaR;
            closestjet = j;
            matched_parton = true;
          }
          
        }
        
        if (matched_parton)
        {
          // Remove the jet from the list if it is matched
          jets.erase(jets.begin() + closestjet)
        }
        else
        {
          // Exit the loop early if we know that one of the partons isn't matched
          break;
        }
        
      }
      
      // If there are any leftover jets, matching has failed
      if (jets.size() > 0) {matched_event = false}
      
      // If fails matching, set pythia event weight to zero
      if (not matched_event)
      {
        setEventWeight_zero(pythia_event);
      }
      
      
    }

    /// Perform Jet matching with a specific Pythia
    #define GET_JETMATCHER(NAME, PYTHIA_COLLIDER_TYPE)            \
    void NAME(HEPUtils::Event& pythia_event)                         \
    {                                                            \
      using namespace Pipes::NAME;                               \
      jetmatching_dummy(pythia_event, *Dep::HardScatteringSim);                                \
                                                                 \
    }                                                            \
                                                                 \
    )




  }

}
