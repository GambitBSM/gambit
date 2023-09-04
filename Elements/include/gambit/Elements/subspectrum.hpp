//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Abstract class for accessing general spectrum information.
///
///  *********************************************
///
///  Authors:
///  <!-- add name and date if you modify -->
///
///  \author Peter Athron
///          (peter.athron@coepp.org.au)
///  \date 2014, 2015 Jan, Feb, Mar
///
///  \author Ben Farmer
///          (benjamin.farmer@fysik.su.se)
///  \date 2014, 2015 Jan - Jul
///
///  \author Abram Krislock
///          (a.m.b.krislock@fys.uio.no)
///  \date 2016 Feb
///
///  *********************************************

#ifndef __subspectrum_hpp__
#define __subspectrum_hpp__

#include <map>
#include <set>
#include <cfloat>
#include <sstream>

#include "gambit/Utils/cats.hpp"
#include "gambit/Utils/safebool.hpp"
#include "gambit/Utils/standalone_error_handlers.hpp"
#include "gambit/Utils/util_functions.hpp"
#include "gambit/Elements/slhaea_spec_helpers.hpp"
#include "gambit/Elements/spectrum_helpers.hpp"
#include "gambit/Models/partmap.hpp"


// Particle database access
#define PDB Models::ParticleDB()

namespace Gambit
{

   /// Helper macro for throwing errors in base class versions of virtual functions
   #define vfcn_error(local_info) \
     utils_error().forced_throw(local_info,"This virtual function (of SubSpectrum object) has not been overridden in the derived class! (name = "+getName()+")")

   class SubSpectrum;

   /// Struct to hold collections of function pointer maps to be filled by derived classes
   template <class MapTypes>
   struct MapCollection
   {
      typename MapTypes::fmap0        map0;
      typename MapTypes::fmap1        map1;
      typename MapTypes::fmap2        map2;
      typename MapTypes::fmap0W       map0W;
      typename MapTypes::fmap1W       map1W;
      typename MapTypes::fmap2W       map2W;
      typename MapTypes::fmap0_extraM map0_extraM;
      typename MapTypes::fmap1_extraM map1_extraM;
      typename MapTypes::fmap2_extraM map2_extraM;
      typename MapTypes::fmap0_extraI map0_extraI;
      typename MapTypes::fmap1_extraI map1_extraI;
      typename MapTypes::fmap2_extraI map2_extraI;
   };

   /// Definition of struct to hold various override values for a given ParamTag
   struct OverrideMaps
   {
      std::map<str,double>                             m0; // No indices
      std::map<str,std::map<int,double>>               m1; // One index
      std::map<str,std::map<int,std::map<int,double>>> m2; // Two indices
      /* e.g. retrieve like this: contents = m2[name][i][j]; */
   };



   /// Virtual base class for interacting with spectrum generator output
   // Includes facilities for running RGEs
   // This is the interface class that most module-writers see
   class SubSpectrum
   {

      public:
         /// @{ Constructors/destructors
         SubSpectrum() : override_maps(create_override_maps()) {}
         virtual ~SubSpectrum() {}
         /// @}

         /// @{ Main public interface functions

         /// Get name
         virtual std::string getName() const = 0;

         /// Clone the SubSpectrum object
         virtual std::unique_ptr<SubSpectrum> clone() const = 0;

         /// Dump out spectrum information to an SLHA file (if possible)
         virtual void writeSLHAfile(int, const str&) const;

         /// Get spectrum information in SLHAea format (if possible)
         virtual SLHAstruct getSLHAea(int) const;

         /// Add spectrum information to an SLHAea object (if possible)
         virtual void add_to_SLHAea(int, SLHAstruct&) const {}

         /// There may be more than one *new* stable particle
         ///  this method will tell you how many.
         /// If more than zero you probbaly *need* to know what model
         ///  you are working on, so we don't give all stable particles
         virtual int get_numbers_stable_particles() const { vfcn_error(LOCAL_INFO); return -1; }

         /// Limits to RGE running; warning/error raised if running beyond these is attempted.
         /// If these aren't overridden in the derived class then effectively no limit on running will exist.
         /// These are public so that module writers can use them to check what the limits are.
         virtual double hard_upper() const {return DBL_MAX;}
         virtual double soft_upper() const {return DBL_MAX;}
         virtual double soft_lower() const {return 0.;}
         virtual double hard_lower() const {return 0.;}

         /// @{ Functions to be overridden in classes derived from Spec<Derived>
         /// (i.e. the final wrappers)

         /// Run spectrum to new scale
         virtual void RunToScaleOverride(double) { vfcn_error(LOCAL_INFO); }
         /// Returns the renormalisation scale of parameters
         virtual double GetScale() const { vfcn_error(LOCAL_INFO); return -1;}
         /// Manually set the renormalisation scale of parameters
         /// somewhat dangerous to allow this but may be needed
         virtual void SetScale(double) { vfcn_error(LOCAL_INFO); }

         /// @}

         /// Run spectrum to a new scale
         /// This function is a wrapper for RunToScaleOverride which automatically checks limits and
         /// raises warnings.
         // Behaviour modified by "behave" integer:
         // behave = 0  -- If running beyond soft limit requested, halt at soft limit
         //                (assumes hard limits outside of soft limits; but this is not enforced)
         // behave = 1  -- If running beyond soft limit requested, throw warning
         //                  "           "   hard limit     "    , throw error
         // behave = anything else -- Ignore limits and attempt running to requested scale
         void RunToScale(double scale, const int behave = 0);

         /// Getters/Setters etc.

         /* Getters and checker declarations for parameter retrieval with zero, one, and two indices
            Note optional arguments:
             first bool; "check_overrides". Set to SafeBool(false) to disable matching on override entries
             second bool; "check_antiparticle". Set to SafeBool(false) to disable matching on antiparticle entries */
         virtual bool   has(const Par::Tags, const str&, const SpecOverrideOptions=use_overrides, const SafeBool check_antiparticle = SafeBool(true)) const = 0;
         virtual double get(const Par::Tags, const str&, const SpecOverrideOptions=use_overrides, const SafeBool check_antiparticle = SafeBool(true)) const = 0;
         virtual bool   has(const Par::Tags, const str&, const int, const SpecOverrideOptions=use_overrides, const SafeBool check_antiparticle = SafeBool(true)) const = 0;
         virtual double get(const Par::Tags, const str&, const int, const SpecOverrideOptions=use_overrides, const SafeBool check_antiparticle = SafeBool(true)) const = 0;
         virtual bool   has(const Par::Tags, const str&, const int, const int, const SpecOverrideOptions=use_overrides) const = 0;
         virtual double get(const Par::Tags, const str&, const int, const int, const SpecOverrideOptions=use_overrides) const = 0;

         /* Setter declarations, for setting parameters in a derived model object,
            and for overriding model object values with values stored outside
            the model object (for when values cannot be inserted back into the
            model object)
            Note; these are NON-CONST */
         virtual void set(const Par::Tags, const double, const str&, const SafeBool check_antiparticle = SafeBool(true)) = 0;
         virtual void set(const Par::Tags, const double, const str&, const int, const SafeBool check_antiparticle = SafeBool(true)) = 0;
         virtual void set(const Par::Tags, const double, const str&, const int, const int) = 0;

         /* The parameter overrides are handled entirely by this base class, so
            they are not virtual.
            optional arguments:
               allow_new:   Allow "overriding" non-existent parameters if 'true'..
               decouple: If allow_new=true AND decouple=true, allows adding separate particle and antiparticle values. */
         void set_override(const Par::Tags, const double, const str&, const bool allow_new = false, const bool decouple = false);
         void set_override(const Par::Tags, const double, const str&, const int, const bool allow_new = false, const bool decouple = false);
         void set_override(const Par::Tags, const double, const str&, const int, const int, const bool allow_new = false);

         /* Helpers for override functions which take parameter names and indices as vectors, and
            loop over them, to make it easy to set many parameters to the same value.
            No two-index versions at the moment, but could be added if needed. */
         void set_override_vector(const Par::Tags, const double, const std::vector<str>&, const bool allow_new = false, const bool decouple = false);
         void set_override_vector(const Par::Tags, const double, const std::vector<str>&, const std::vector<int>, const bool allow_new = false, const bool decouple = false);
         void set_override_vector(const Par::Tags, const double, const std::vector<str>&, const int, const bool allow_new = false, const bool decouple = false);
         void set_override_vector(const Par::Tags, const double, const str&, const std::vector<int>, const bool allow_new = false, const bool decouple = false);

         /* Overloads of getter/checker functions to allow access using PDG codes */
         /* as defined in Models/src/particle_database.cpp */
         /* These don't have to be virtual; they just call the virtual functions in the end. */
         bool   has(const Par::Tags, const int, const int,
              const SpecOverrideOptions=use_overrides,
              const SafeBool check_antiparticle = SafeBool(true)) const;     /* Input PDG code plus context integer */

         double get(const Par::Tags, const int, const int,
              const SpecOverrideOptions=use_overrides,
              const SafeBool check_antiparticle = SafeBool(true)) const;     /* Input PDG code plus context integer */

         bool   has(const Par::Tags, const std::pair<int,int>,
              const SpecOverrideOptions=use_overrides,
              const SafeBool check_antiparticle = SafeBool(true)) const; /* Input PDG code plus context integer */

         double get(const Par::Tags, const std::pair<int,int>,
              const SpecOverrideOptions=use_overrides,
              const SafeBool check_antiparticle = SafeBool(true)) const; /* Input PDG code plus context integer */

         bool   has(const Par::Tags, const std::pair<str,int>,
              const SpecOverrideOptions=use_overrides,
              const SafeBool check_antiparticle = SafeBool(true)) const; /* Input short name plus index */

         double get(const Par::Tags, const std::pair<str,int>,
              const SpecOverrideOptions=use_overrides,
              const SafeBool check_antiparticle = SafeBool(true)) const; /* Input short name plus index */

         /* Getters which first check the sanity of the thing they are returning */
         /* These don't have to be virtual; they just call the virtual functions in the end. */
         double safeget(const Par::Tags, const str&,
              const SpecOverrideOptions=use_overrides,
              const SafeBool check_antiparticle = SafeBool(true)) const;

         double safeget(const Par::Tags, const str&, const int,
              const SpecOverrideOptions=use_overrides,
              const SafeBool check_antiparticle = SafeBool(true)) const;

         double safeget(const Par::Tags, const str&, const int, const int,
              const SpecOverrideOptions=use_overrides) const;

         double safeget(const Par::Tags, const int, const int,
              const SpecOverrideOptions=use_overrides,
              const SafeBool check_antiparticle = SafeBool(true)) const;     /* Input PDG code plus context integer */

         double safeget(const Par::Tags, const std::pair<int,int>,
              const SpecOverrideOptions=use_overrides,
              const SafeBool check_antiparticle = SafeBool(true)) const; /* Input PDG code plus context integer */

         double safeget(const Par::Tags, const std::pair<str,int>,
              const SpecOverrideOptions=use_overrides,
              const SafeBool check_antiparticle = SafeBool(true)) const; /* Input short name plus index */

         /// @{ PDB overloads for setters

         /* Input PDG code plus context integer */
         void set_override(const Par::Tags, const double, const int, const int,     const bool allow_new = false, const bool decouple = false);
         void set_override(const Par::Tags, const double, const std::pair<int,int>, const bool allow_new = false, const bool decouple = false);

         /* Input short name plus index */
         void set_override(const Par::Tags, const double, const std::pair<str,int>, const bool allow_new = false, const bool decouple = false);

         /// @}

         /// TODO: extra PDB overloads to handle all the one and two index cases (well all the ones that are feasible...)


         /// PDG code translation map, for special cases where an SLHA file has been read in and the PDG codes changed.
         virtual const std::map<int, int>& PDG_translator() const { return empty_map; }

     private:

         const std::map<int, int> empty_map;

         /// Initialiser function for override_maps
         static std::map<Par::Tags,OverrideMaps> create_override_maps();

     protected:
         /// Map of override maps
         std::map<Par::Tags,OverrideMaps> override_maps;

   };

} // end namespace Gambit

// Undef the various helper macros to avoid contaminating other files
#undef PDB

#endif
