//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Type definition header for DarkBit Process
///  Catalog constituents types.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Christoph Weniger
///          (c.weniger@uva.nl)
///  \date 2012 Mar, 2014 Jan
///
///  \author Pat Scott
///          (patscott@physics.mcgill.ca)
///  \date 2015 Mar
///
/// \author Sanjay Bloor
///         (sanjay.bloor12@imperial.ac.uk)
/// \date 2018 Aug
///
///  *********************************************


#ifndef __ProcessCatalog_hpp__
#define __ProcessCatalog_hpp__

#include <vector>
#include <map>

#include "gambit/Utils/util_types.hpp"
#include "gambit/cmake/cmake_variables.hpp"
#include "gambit/Elements/daFunk.hpp"

namespace Gambit
{

  namespace DarkBit
  {
    /// A single resonance of a given width at a given energy (both in GeV)
    struct TH_Resonance
    {
      TH_Resonance() : energy(0.), width (0.) {}

      TH_Resonance(double energy, double width) : energy(energy), width(width) {}

      double energy;
      double width;
    };

    /// Location of resonances and thresholds in energy (GeV)
    struct TH_resonances_thresholds
    {
      TH_resonances_thresholds() {}

      TH_resonances_thresholds(const TH_resonances_thresholds& copy) :
        resonances(copy.resonances), threshold_energy(copy.threshold_energy) {}

      TH_resonances_thresholds& operator= (const TH_resonances_thresholds&) = default;

      TH_resonances_thresholds(const std::vector<TH_Resonance>& resonances,
          const std::vector<double> & thresholds) :
        resonances(resonances), threshold_energy(thresholds) {}

      std::vector<TH_Resonance> resonances;
      std::vector<double> threshold_energy;
    };

    /// A container for the mass and spin of a particle.
    struct TH_ParticleProperty
    {
        /// Constructor
        TH_ParticleProperty(double mass, unsigned int spin2);

        /// Particle mass (GeV)
        double mass;

        /// Twice the spin of the particle
        unsigned int spin2;
    };

    /// All data on a single annihilation or decay channel,
    /// e.g. chi --> gamma gamma, chi chi --> mu+ mu-
    struct TH_Channel
    {
        // Functions

        /// Constructor
        TH_Channel(std::vector<str> finalStateIDs, daFunk::Funk genRate);

        /// Print information about this channel.
        void printChannel() const;

        /// Indicate whether or not the final states of this channel contain a specific particle.
        bool channelContains(str p) const;

        /// Indicate whether or not this channel is the one defined by some specific final states.  Particle name version.
        bool isChannel(str, str, str = "", str = "") const;

        /// Indicate whether or not this channel is the one defined by some specific final states.  Particle vector version.
        bool isChannel(std::vector<str>) const;


        // Variables

        /// Final state identifiers
        std::vector<std::string> finalStateIDs;

        /// Number of final state particles in this channel
        unsigned int nFinalStates;

        /// Energy dependence of final state particles. Includes v_rel ("v") as last argument in case of annihilation
        daFunk::Funk genRate = daFunk::zero("dummyArgument");
    };

    /// A container for a single process.
    /// Contains all channels for decay of a single particle, or for
    /// annihilation of a specific pair of particles.  That is,
    /// TH_Process groups channels together according to initial states,
    /// e.g. chi --> everything, chi chi --> everything.
    struct TH_Process
    {
        // Functions

        /// Constructor for decay process
        TH_Process(const str & particle1ID);

        /// Constructor for annihilation process
        TH_Process(const str & particle1ID, const str & particle2ID);

        /// Compare initial states
        bool isProcess(const str &, const str & = std::string()) const;

        /// Check for given channel.  Return a pointer to it if found, NULL if not.
        const TH_Channel* find(std::vector<str>) const;


        // Variables

        /// Annihilation or decay?
        bool isAnnihilation;

        /// Decaying particle or particle pair
        /// @{
        str particle1ID;
        str particle2ID;
        /// @}

        /// Does the process contain self-conjugate DM? (accounting for correct factors of 1/2 in annihilation spectra)
        bool isSelfConj;

        /// List of channels
        std::vector<TH_Channel> channelList;

        /// List of resonances and thresholds
        TH_resonances_thresholds resonances_thresholds;

        /// Additional decay rate or sigmav (in addition to above channels)
        daFunk::Funk genRateMisc;
    };

    /// A container holding all annihilation and decay initial states relevant for DarkBit.
    struct TH_ProcessCatalog
    {
        // Functions

        /// Retrieve a specific process from the catalog
        TH_Process getProcess(str, str = "") const;

        /// Check for a specific process in the catalog
        const TH_Process* find(str, str = "") const;

        /// Retrieve properties of a given particle involved in one or more processes in this catalog
        TH_ParticleProperty getParticleProperty(str) const;

        /// Check whether particle is in particle properties catalog
        bool hasParticleProperty(str) const;

        /// Validate kinematics and entries
        void validate();


        // Variables

        /// Vector of all processes in this catalog
        std::vector<TH_Process> processList;

        /// Map from particles involved in the processes of this catalog, to their properties.
        std::map<std::string, TH_ParticleProperty> particleProperties;
    };
  }
}

#endif // #defined __ProcessCatalog_hpp__
