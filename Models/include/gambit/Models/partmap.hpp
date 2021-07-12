//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Class definitions for GAMBIT particle
///  database.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///   
///  \author Pat Scott  
///          (p.scott@imperial.ac.uk)
///  \date 2015 Jan
///
///  \author Sanjay Bloor
///          (sanjay.bloor@imperial.ac.uk)
///  \date 2019 May
///
///  *********************************************


#ifndef __partmaps_hpp__
#define __partmaps_hpp__

#include <map>

#include "gambit/Utils/util_types.hpp"


namespace Gambit
{

  namespace Models
  {

    class partmap
    {

      public:

        /// Constructor
        partmap();

        /// Add a new particle to the database
        void add(str, std::pair<int, int>, int, int, int); 

        /// Add a new Standard Model particle to the database
        void add_SM(str, std::pair<int, int>, int, int, int); 

        /// Add a new generic particle class to the database
        void add_generic(str, std::pair<int, int>, int, int, int); 

        /// Add a new particle to the database with a short name and an index
        void add_with_short_pair(str, std::pair<int, int>, std::pair<str, int>, int, int, int);

        /// Add a new Standard Model particle to the database with a short name and an index
        void add_SM_with_short_pair(str, std::pair<int, int>, std::pair<str, int>, int, int, int);

        /// Retrieve the PDG code and context integer, from the long name
        std::pair<int, int> pdg_pair(str) const; 

        /// Retrieve the PDG code and context integer, from the short name and index
        std::pair<int, int> pdg_pair(str,int) const;

        /// Retrieve the PDG code and context integer, from the short name and index pair
        std::pair<int, int> pdg_pair(std::pair<str,int>) const;

        /// Retrieve the long name, from the short name and index
        str long_name(str,int) const;

        /// Retrieve the long name, from the PDG code and context integer 
        str long_name(std::pair<int, int>) const;

        /// Retrieve the long name, from the PDG code and context integer
        str long_name(int,int) const;

        /// Retrieve the short name and index, from the long name 
        std::pair<str, int> short_name_pair(str) const;

        /// Retrieve the short name and index, from the PDG code and context integer 
        std::pair<str, int> short_name_pair(std::pair<int, int>) const;

        /// Retrieve the short name and index, from the PDG code and context integer
        std::pair<str, int> short_name_pair(int,int) const;

        /// Get a vector PDG codes and context integers of Standard Model particles in the database
        const std::vector<std::pair<int, int> >& get_SM_particles() const;
        
        /// Get a vector PDG codes and context integers of generic particle classes in the database
        const std::vector<std::pair<int, int> >& get_generic_particles() const;
        
        /// Check if a particle is in the database, using the long name 
        bool has_particle(str) const;

        /// Check if a particle is in the database, using the short name and index 
        bool has_particle(str, int) const;
        bool has_particle(std::pair<str, int>) const;

        /// Check if a particle is in the database, using the PDG code and context integer 
        bool has_particle(std::pair<int, int>) const;

        /// Get the matching anti-particle long name for a particle in the database, using the long name 
        str get_antiparticle(str) const;

        /// Get the matching anti-particle short name and index for a particle in the database, using the short name and index 
        /// @{
        std::pair<str, int> get_antiparticle(std::pair<str, int>) const;
        std::pair<str, int> get_antiparticle(str, int) const;
        /// @}

        /// Get the matching anti-particle PDG code and index for a particle in the database, using the PDG code and index 
        /// @{
        std::pair<int, int> get_antiparticle(std::pair<int, int>) const;
        std::pair<int, int> get_antiparticle(int, int) const;
        /// @}

        /// Check if a particle has a matching anti-particle in the database, using the long name 
        bool has_antiparticle(str) const;

        /// Check if a particle has a matching anti-particle in the database, using the short name and index 
        /// @{
        bool has_antiparticle(std::pair<str, int>) const;
        bool has_antiparticle(str, int) const;
        /// @}

        /// Check if a particle has a matching anti-particle in the database, using the PDG code and context integer 
        /// @{
        bool has_antiparticle(std::pair<int, int>) const;
        bool has_antiparticle(int, int) const;
        /// @}

        /// Check if a particle has a short name, using the long name 
        bool has_short_name(str) const;

        /// Check if a particle has a short name, using the PDG code and context integer 
        bool has_short_name(std::pair<int, int>) const;

        /// Check if a particle has a spin (x2) entry, using the long name
        bool has_spinx2(str) const;

        /// Check if a particle has a spin (x2) entry, using the PDG code and context integer
        bool has_spinx2(std::pair<int, int>) const;
        bool has_spinx2(int, int) const;

        /// Check if a particle has a spin (x2) entry,  using the short name and index 
        bool has_spinx2(std::pair<str, int>) const;
        bool has_spinx2(str, int) const;

        /// Get spin (x2) of a given particle, using the PDG code and context integer
        /// @{
        int get_spinx2(std::pair<int, int>) const;
        int get_spinx2(int, int) const;
        /// @}

        /// Get spin (x2) of a given particle, using the long name
        /// @{
        int get_spinx2(str) const;
        /// @}

        /// Get spin (x2) of a given particle, using the short name and index
        /// @{
        int get_spinx2(std::pair<str, int>) const;
        int get_spinx2(str, int) const;
        /// @}

        /// Check if a particle has a charge (x3) entry, using the long name
        bool has_chargex3(str) const;

        /// Check if a particle has a charge (x3) entry, using the PDG code and context integer
        bool has_chargex3(std::pair<int, int>) const;
        bool has_chargex3(int, int) const;

        /// Check if a particle has a charge (x3) entry,  using the short name and index 
        bool has_chargex3(std::pair<str, int>) const;
        bool has_chargex3(str, int) const;

        /// Get charge (x3) of a given particle, using the PDG code and context integer
        /// @{
        int get_chargex3(std::pair<int, int>) const;
        int get_chargex3(int, int) const;
        /// @}

        /// Get charge (x3) of a given particle, using the long name
        /// @{
        int get_chargex3(str) const;
        /// @}

        /// Get charge (x3) of a given particle, using the short name and index
        /// @{
        int get_chargex3(std::pair<str, int>) const;
        int get_chargex3(str, int) const;
        /// @}

        /// Check if a particle has a color entry, using the long name
        bool has_color(str) const;

        /// Check if a particle has a color entry, using the PDG code and context integer
        bool has_color(std::pair<int, int>) const;
        bool has_color(int, int) const;

        /// Check if a particle has a color entry,  using the short name and index 
        bool has_color(std::pair<str, int>) const;
        bool has_color(str, int) const;

        /// Get color of a given particle, using the PDG code and context integer
        /// @{
        int get_color(std::pair<int, int>) const;
        int get_color(int, int) const;
        /// @}

        /// Get color of a given particle, using the long name
        /// @{
        int get_color(str) const;
        /// @}

        /// Get color of a given particle, using the short name and index
        /// @{
        int get_color(std::pair<str, int>) const;
        int get_color(str, int) const;
        /// @}

        /// For debugging: use to check the contents of the particle database
        void check_contents() const;

      private:
          
        /// All SM particles in the database, by PDG code and context integer.
        std::vector<std::pair<int, int> > SM;
        /// All generic particle classes in the database, by PDG code and context integer.
        std::vector<std::pair<int, int> > generic;
        /// Map from long name to PDG code and context integer
        std::map<str, std::pair<int, int> > long_name_to_pdg_pair;
        /// Map from PDG code and context integer to long name
        std::map<std::pair<int, int>, str> pdg_pair_to_long_name;
        /// Map from short name and index to PDG code and context integer
        std::map<std::pair<str, int>, std::pair<int, int> > short_name_pair_to_pdg_pair;
        /// Map from PDG code and context integer to short name and index
        std::map<std::pair<int, int>, std::pair<str, int> > pdg_pair_to_short_name_pair;
        /// Map from long name to short name and index
        std::map<str, std::pair<str, int> > long_name_to_short_name_pair;
        /// Map from short name and index to long name
        std::map<std::pair<str, int>, str> short_name_pair_to_long_name;
        /// Map from long name to twice the spin of particle
        std::map<str, int> long_name_to_spinx2;
        /// Map from long name to three times the charge of particle
        std::map<str, int> long_name_to_chargex3;
        /// Map from long name to color representation of particle
        std::map<str, int> long_name_to_color;

    };

    /// Database accessor function
    partmap& ParticleDB();

  }

}


#endif //__partmaps_hpp__
