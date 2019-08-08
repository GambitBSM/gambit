//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Type definition header for module DarkBit.
///
///  Compile-time registration of type definitions
///  required for the rest of the code to
///  communicate with DarkBit.
///
///  Add to this if you want to define a new type
///  for the functions in DarkBit to return, but
///  you don't expect that type to be needed by
///  any other modules.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Christoph Weniger
///          (c.weniger@uva.nl)
///  \date 2012 Mar, 2014 Jan
///
///  \author Torsten Bringmann
///          (torsten.bringmann@fys.uio.no)
///  \date 2013 Jun
///
///  \author Pat Scott
///          (patscott@physics.mcgill.ca)
///  \date 2013 Oct
///  \date 2014 Jan, Apr
///  \date 2015 Mar
///
///  \author Lars A. Dal
///          (l.a.dal@fys.uio.no)
///  \date 2014 Mar, Jul, Sep, Oct, Dec
///  \date 2015 Jan
///
///  \author Christopher Savage
///          (chris@savage.name)
///  \date 2015 Jan
///
///  \author Jonathan Cornell
///          (jcornell@ucsc.edu)
///  \date 2014
///
///  \author Sebastian Wild
///          (sebastian.wild@ph.tum.de)
///  \date 2016 Aug
///  *********************************************


#ifndef __DarkBit_types_hpp__
#define __DarkBit_types_hpp__

#include "gambit/DarkBit/decay_chain.hpp"
#include "gambit/DarkBit/SimpleHist.hpp"
#include "gambit/DarkBit/ProcessCatalog.hpp"
#include "gambit/Elements/daFunk.hpp"

namespace Gambit
{

  namespace DarkBit
  {

    // Forward declaration of warnings and errors
    error& DarkBit_error();
    warning& DarkBit_warning();

    // Local preferred sources of tools.
    using boost::weak_ptr;
    using boost::shared_ptr;
    using boost::dynamic_pointer_cast;
    using boost::static_pointer_cast;
    using boost::enable_shared_from_this;

    // A simple example
    struct Wstruct
    {
      double valA;
      double valB;
    };

    //generalized capture cross section
    // struct genCapXsec
    // {
    //   std::map< std::pair < int, int >, double> sigma;
    //   // std::map<const char*,int> sigma;
    // };

    struct RD_coannihilating_particle
    {
      RD_coannihilating_particle() {}
      RD_coannihilating_particle(const unsigned int & index, const unsigned int & dof, const double & mass) : index(index), degreesOfFreedom(dof), mass(mass) {}

      unsigned int index;
      unsigned int degreesOfFreedom;
      double mass;
    };

    struct RD_spectrum_type
    {
      RD_spectrum_type() {}
      RD_spectrum_type(const std::vector<RD_coannihilating_particle> & coannPart, const std::vector<TH_Resonance> & resonances, const std::vector<double> & thresholds) : coannihilatingParticles(coannPart), resonances(resonances), threshold_energy(thresholds) {}

      std::vector<RD_coannihilating_particle> coannihilatingParticles;
      std::vector<TH_Resonance> resonances;
      std::vector<double> threshold_energy;
    };


    //////////////////////////////////////////////
    // Neutrino telescope data structures
    //////////////////////////////////////////////

    /// Neutrino telescope yield info container
    struct nuyield_info
    {
      public:
        bool threadsafe;
        nuyield_function_pointer pointer;
    };

    /// Neutrino telescope data container
    struct nudata
    {
      public:
        int nobs;
        double signal;
        double bg;
        double loglike;
        double bgloglike;
        double pvalue;
    };

    /// Annihilation/decay channel
    struct SimYieldChannel
    {
        SimYieldChannel(daFunk::Funk dNdE, std::string p1, std::string p2,
            std::string finalState, double Ecm_min, double Ecm_max);
        daFunk::Funk dNdE;
        daFunk::BoundFunk dNdE_bound;  // Pre-bound version for use in e.g. cascade decays
        std::string p1;
        std::string p2;
        std::string finalState;
        double Ecm_min;
        double Ecm_max;
    };

    /// \brief Channel container
    /// Object containing tabularized yields for particle decay and two-body final states.
    class SimYieldTable
    {
        public:
            SimYieldTable();
            void addChannel(daFunk::Funk dNdE, std::string p1, std::string p2, std::string finalState, double Ecm_min, double Ecm_max);
            void addChannel(daFunk::Funk dNdE, std::string p1, std::string finalState, double Ecm_min, double Ecm_max);
            bool hasChannel(std::string p1, std::string p2, std::string finalState) const;
            bool hasChannel(std::string p1, std::string finalState) const;
            bool hasAnyChannel(std::string p1) const;
            bool hasAnyChannel(std::string p1, std::string p2) const;
            const SimYieldChannel& getChannel(std::string p1, std::string p2, std::string finalState) const;
            daFunk::Funk operator()(std::string p1, std::string p2, std::string finalState, double Ecm) const;
            daFunk::Funk operator()(std::string p1, std::string finalState, double Ecm) const;
            daFunk::Funk operator()(std::string p1, std::string p2, std::string finalState) const;
            daFunk::Funk operator()(std::string p1, std::string finalState) const;

        private:
            SimYieldChannel dummy_channel;
            std::vector<SimYieldChannel> channel_list;
            int findChannel(std::string p1, std::string p2, std::string finalState) const;
    };

  }
}

#endif // defined __DarkBit_types_hpp__
