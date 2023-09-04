//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Model definitions for Cosmological Energy injection
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Patrick Stoecker
///          (stoecker@physik.rwth-aachen.de)
///  \date 2019 Sep
///  \date 2020 Jan
///
///  *********************************************

#ifndef __CosmoEnergyInjection_hpp__
#define __CosmoEnergyInjection_hpp__

// General model for s-wave annihilating dark matter
#define MODEL AnnihilatingDM_general
  START_MODEL
  DEFINEPARS(mass)      // mass of dm candidate [GeV]
  DEFINEPARS(sigmav)    // thermally averaged cross section [cm^3 s^-1]
#undef MODEL

// Toy model of annihilating dark matter with monochromatic injection of e+/- and photons
#define MODEL AnnihilatingDM_mixture
#define PARENT AnnihilatingDM_general
  START_MODEL
  DEFINEPARS(mass)      // mass of dm candidate [GeV]
  DEFINEPARS(sigmav)    // thermally averaged cross section [cm^3 s^-1]
  DEFINEPARS(BR_el)     // Branching ratio into electrons
  DEFINEPARS(BR_ph)     // Branching ratio into photons
                        // (1 - BR_el -BR_ph) >= 0 must hold !!

  INTERPRET_AS_PARENT_FUNCTION(AnnihilatingDM_mixture_to_AnnihilatingDM_general)
#undef PARENT
#undef MODEL

// Special case of 'AnnihilatingDM_mixture': Only annihilate into photons
#define MODEL AnnihilatingDM_photon
#define PARENT AnnihilatingDM_mixture
  START_MODEL
  DEFINEPARS(mass)      // mass of dm candidate [GeV]
  DEFINEPARS(sigmav)    // thermally averaged cross section [cm^3 s^-1]

  INTERPRET_AS_PARENT_FUNCTION(AnnihilatingDM_photon_to_AnnihilatingDM_mixture)
#undef PARENT
#undef MODEL

// Special case of 'AnnihilatingDM_mixture': Only annihilate into electrons
#define MODEL AnnihilatingDM_electron
#define PARENT AnnihilatingDM_mixture
  START_MODEL
  DEFINEPARS(mass)      // mass of dm candidate [GeV]
  DEFINEPARS(sigmav)    // thermally averaged cross section [cm^3 s^-1]

  INTERPRET_AS_PARENT_FUNCTION(AnnihilatingDM_electron_to_AnnihilatingDM_mixture)
#undef PARENT
#undef MODEL

// General model for decaying dark matter
#define MODEL DecayingDM_general
  START_MODEL
  DEFINEPARS(mass)      // mass of dm candidate [GeV] (with density rho_dm)
  DEFINEPARS(lifetime)  // lifetime of dm candiate [s]
  DEFINEPARS(fraction)  // rho_dm / rho_cdm in the infinite past
#undef MODEL

// Toy model of decaying dark matter with monochromatic injection of e+/- and photons
#define MODEL DecayingDM_mixture
#define PARENT DecayingDM_general
  START_MODEL
  DEFINEPARS(mass)      // mass of dm candidate [GeV] (with density rho_dm)
  DEFINEPARS(lifetime)  // lifetime of dm candiate [s]
  DEFINEPARS(fraction)  // rho_dm / rho_cdm in the infinite past
  DEFINEPARS(BR_el)     // Branching ratio into electrons
  DEFINEPARS(BR_ph)     // Branching ratio into photons
                        // (1 - BR_el -BR_ph) >= 0 must hold !!

  INTERPRET_AS_PARENT_FUNCTION(DecayingDM_mixture_to_DecayingDM_general)
#undef PARENT
#undef MODEL

// Special case of 'DecayingDM_mixture': Only decay into photons
#define MODEL DecayingDM_photon
#define PARENT DecayingDM_mixture
  START_MODEL
  DEFINEPARS(mass)      // mass of dm candidate [GeV] (with density rho_dm)
  DEFINEPARS(lifetime)  // lifetime of dm candiate [s]
  DEFINEPARS(fraction)  // rho_dm / rho_cdm in the infinite past

  INTERPRET_AS_PARENT_FUNCTION(DecayingDM_photon_to_DecayingDM_mixture)
#undef PARENT
#undef MODEL

// Special case of 'DecayingDM_mixture': Only decay into electrons
#define MODEL DecayingDM_electron
#define PARENT DecayingDM_mixture
  START_MODEL
  DEFINEPARS(mass)      // mass of dm candidate [GeV] (with density rho_dm)
  DEFINEPARS(lifetime)  // lifetime of dm candiate [s]
  DEFINEPARS(fraction)  // rho_dm / rho_cdm in the infinite past

  INTERPRET_AS_PARENT_FUNCTION(DecayingDM_electron_to_DecayingDM_mixture)
#undef PARENT
#undef MODEL

#endif
