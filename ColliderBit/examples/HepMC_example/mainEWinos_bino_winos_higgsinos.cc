// mainEwinos_bino_winos_higgsinos.cc.

// Author: Tomas Gonzalo (tomas.gonzalo@monash.edu)

// This program illustrates how HepMC can be interfaced to Pythia8.
// It uses the SLHA file for the best fit point from EWMSSM
// arXiv:1809.02097 

// WARNING: the default version generateds 30k events, including ISR, FSR and Hadronization. HepMC files can weight over 2G

#include "Pythia8/Pythia.h"
#include "Pythia8Plugins/HepMC2.h"

using namespace Pythia8;

int main() {
  // Interface for conversion from Pythia8::Event to HepMC event.
  HepMC::Pythia8ToHepMC ToHepMC;

  // Specify file where HepMC events will be stored.
  HepMC::IO_GenEvent ascii_io("hepmcEWinos_bino_winos_higgsinos.dat", std::ios::out);

  // Generator. Shorthand for the event.
  Pythia pythia;
//  Event& event = pythia.event;

  // Read in commands from external file.
  pythia.readFile("mainEWinos_bino_winos_higgsinos.cmnd");

  // Initialize
  pythia.init();

  // Extract settings to be used in the main program.
  int nEvent   = pythia.mode("Main:numberOfEvents");

  // Begin event loop. Generate event. Skip if error.
  for (int iEvent = 0; iEvent < nEvent; ++iEvent)
  {
    if (!pythia.next()) continue;

    // Construct new empty HepMC event and fill it.
    // Units will be as chosen for HepMC build; but can be changed
    // by arguments, e.g. GenEvt( HepMC::Units::GEV, HepMC::Units::MM)
    HepMC::GenEvent* hepmcevt = new HepMC::GenEvent();
    ToHepMC.fill_next_event( pythia, hepmcevt );

    // Write the HepMC event to file. Done with it.
    ascii_io << hepmcevt;
    delete hepmcevt;

  // End of event loop. Statistics. Histogram.
  }
  pythia.stat();

  // Done.
  return 0;
}
