//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Implementation class "behind the scenes" of
///  abstract SubSpectrum interface class. Sits
///  between SubSpectrum and model-specific 
///  wrapper classes.
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
///  *********************************************

#ifndef __spec_hpp__
#define __spec_hpp__

#include "gambit/Elements/subspectrum.hpp"
#include "gambit/Models/SpectrumContents/subspectrum_contents.hpp"

// Particle database access
#define PDB Models::ParticleDB()        

namespace Gambit
{

   /// Need to forward declare Spec class
   template <class>
   class Spec;

   /// Dummy classes to satisfy template parameters for Spec class in cases when those objects
   /// are not needed by the getters.
   /// @{
   class DummyModel {};
   class DummyInput {};
   /// @}
 
   /// Helper for the static_assert below
   template< typename T >
   struct always_false { 
       enum { value = false };  
   };

   /// Forward declare base traits class which communicates
   /// Model and Input typedefs from the wrapper class
   /// Triggers informative compiler error if an appropriate specialisation is not defined
   /// for whatever SubSpectrum wrapper might be trying to instantiate this.
   template <class T>
   struct SpecTraits
   {
      static_assert(always_false<T>::value, "Failed to find appropriate specialisation of SpecTraits! Did you define one along with your SubSpectrum wrapper? If so, please be sure that the template parameter matches the name of your wrapper class.");
   };

   /// Default values for traits. Specialisations of SpecTraits should inherit from this, and then override the traits that they want to customise.
   struct DefaultTraits
   {
      typedef DummyModel Model;
      typedef DummyInput Input;
   };

   /// Forward declarations related to FptrFinder class
   template<class,class> class SetMaps;
   template<class,class> class FptrFinder;  
   template<class,class> class CallFcn; 

   /// Simpler helper class to run the verify_contents function only
   /// once, the first time a particular wrapper class is constructed.
   template<class Contents>
   class VerifyContents
   {
      public:
        VerifyContents(const SubSpectrum& spec)
        {
          Contents contents;
          contents.verify_contents(spec); 
        }
   };

   // CRTP used to allow access to some special data members of the derived class.
   // Various inherited classes are just used to factor out code, some of which
   // doesn't need to be templated.
   template <class DerivedSpec>
   class Spec : public SubSpectrum
   {
     template <class,class>
     friend class FptrFinder;
 
     public:
         typedef DerivedSpec D;
         typedef Spec<D> Self;

         /// Note: Wrapper need to define a specialisation of 
         /// SpecTraits, which typedefs Model and Input.
         /// "Grab" these typedefs here to simplify notation
         typedef typename SpecTraits<D>::Contents Contents;
         typedef typename SpecTraits<D>::Model    Model;
         typedef typename SpecTraits<D>::Input    Input;

         typedef MapTypes<D,MapTag::Get> MTget; 
         typedef MapTypes<D,MapTag::Set> MTset; 

         std::string getName() const { return SpecTraits<D>::name(); };

         /* Getters and checker declarations for parameter retrieval with zero, one, and two indices */
         bool   has(const Par::Tags, const str&, const SpecOverrideOptions=use_overrides, const SafeBool=SafeBool(true)) const;
         double get(const Par::Tags, const str&, const SpecOverrideOptions=use_overrides, const SafeBool=SafeBool(true)) const;
         bool   has(const Par::Tags, const str&, const int, const SpecOverrideOptions=use_overrides, const SafeBool=SafeBool(true)) const;
         double get(const Par::Tags, const str&, const int, const SpecOverrideOptions=use_overrides, const SafeBool=SafeBool(true)) const;
         bool   has(const Par::Tags, const str&, const int, const int, const SpecOverrideOptions=use_overrides) const;
         double get(const Par::Tags, const str&, const int, const int, const SpecOverrideOptions=use_overrides) const;

         /* Setter declarations, for setting parameters in a derived model object,
            and for overriding model object values with values stored outside
            the model object (for when values cannot be inserted back into the
            model object)
            Note; these are NON-CONST */
         void set(const Par::Tags, const double, const str&, const SafeBool=SafeBool(true));
         void set(const Par::Tags, const double, const str&, const int, const SafeBool=SafeBool(true));
         void set(const Par::Tags, const double, const str&, const int, const int);

         /// @{ Default (empty) map filler functions
         /// Override as needed in derived classes
         static const std::map<Par::Tags,MapCollection<MTget>> fill_getter_maps()
         {     
            std::map<Par::Tags,MapCollection<MTget>> tmp;
            return tmp;
         }
         static const std::map<Par::Tags,MapCollection<MTset>> fill_setter_maps()
         {     
            std::map<Par::Tags,MapCollection<MTset>> tmp;
            return tmp;
         }

         /// Get integer offset convention used by internal model class (needed by getters which take indices) 
         /// By default assume no offset. Overrride as needed in derived class.
         static int index_offset() { return 0; } 


      private:
         /// Function to retrieve the possibly overridden index offset from the derived class via CRTP
         static int get_index_offset() { return D::index_offset(); }

         /// @{ Functions to ensure that all the possible tags exist in the final map, 
         ///    even if no getters/setters are stored under those tags.
       
         static void getter_maps_fill_tags(std::map<Par::Tags,MapCollection<MTget>>& in)
         {     
            std::vector<Par::Tags> all = Par::get_all();
            for(std::vector<Par::Tags>::iterator it = all.begin(); it!=all.end(); ++it)
            {
              in[*it]; // insert tag key if missing
            }
         }
         static void setter_maps_fill_tags(std::map<Par::Tags,MapCollection<MTset>>& in)
         {     
            std::vector<Par::Tags> all = Par::get_all();
            for(std::vector<Par::Tags>::iterator it = all.begin(); it!=all.end(); ++it)
            {
              in[*it]; // insert tag key if missing
            }
         }

         /// @}

         /// @{ Filler functions that are *actually* directly used to fill the maps
         ///    Combines the (possibly overriden) map filler, plus the fill_tags
         ///    functions to fill in any unused tag keys.
         ///    DO NOT override these!
         ///
         static const std::map<Par::Tags,MapCollection<MTget>> final_fill_getter_maps()
         {  
            // Fill from (possibly overriden) derived class filler function
            std::map<Par::Tags,MapCollection<MTget>> tmp = D::fill_getter_maps();
            // Add in any missing tags
            getter_maps_fill_tags(tmp);    
            return tmp;
         }
         static const std::map<Par::Tags,MapCollection<MTset>> final_fill_setter_maps()
         {     
            // Fill from (possibly overriden) derived class filler function
            std::map<Par::Tags,MapCollection<MTset>> tmp = D::fill_setter_maps();
            // Add in any missing tags
            setter_maps_fill_tags(tmp);    
            return tmp;
         }

         /// @}
         
      public: 

         /// Constructor
         /// This uses the "Contents" class to verify (once, not every construction)
         /// that this wrapper provides all the basic functionality that it is
         /// supposed to.
         Spec() { static VerifyContents<Contents> runonce(*this); };
       
         /// Virtual destructor
         virtual ~Spec() {};
    
         /// CRTP-style polymorphic clone function
         /// Now derived classes will not need to re-implement the clone function.
         virtual std::unique_ptr<SubSpectrum> clone() const       
         {
           return std::unique_ptr<SubSpectrum>(
              new DerivedSpec(static_cast<DerivedSpec const &>(*this))
              );
         }
 
         /// @{ Getters for wrapped data; be sure to define the 'get_Model' and
         ///    'get_Input' functions in the wrappers (with public access)
         ///    Might as well use static polymorphism rather than virtual functions,
         ///    since we are using the CRTP already anyway.

         /// Default "null" versions of get_Model and get_Input, to be used if
         /// wrapper does not override them.
         DummyModel dummymodel;
         DummyInput dummyinput;
         Model& get_Model() { return dummymodel; }
         Input& get_Input() { return dummyinput; }
         const Model& get_Model() const { return dummymodel; }
         const Input& get_Input() const { return dummyinput; }

         /// Get model object on which to call function pointers
         Model& model() { return static_cast<DerivedSpec*>(this)->get_Model(); }
         /// Return it as const if we are a const object
         const Model& model() const { return static_cast<const DerivedSpec*>(this)->get_Model(); }

         /// Get struct containing any extra data input on SubSpectrum object creation
         Input& input() { return static_cast<DerivedSpec*>(this)->get_Input(); }
         /// Return it as const if we are a const object
         const Input& input() const { return static_cast<const DerivedSpec*>(this)->get_Input(); }

         /// @}

         /// Will need a map of map collections for both the getters and setters,
         /// containing the map collections for the permitted parameter types

         typedef std::map<Par::Tags,MapCollection<MTget>> GetterMaps;
         typedef std::map<Par::Tags,MapCollection<MTset>> SetterMaps;
         static const GetterMaps getter_maps;
         static const SetterMaps setter_maps;

   };

   /// Initialise maps (uses filler overrides from DerivedSpec if defined)
   template <class D>
   const typename Spec<D>::GetterMaps Spec<D>::getter_maps(Spec<D>::final_fill_getter_maps());

   template <class D>
   const typename Spec<D>::SetterMaps Spec<D>::setter_maps(Spec<D>::final_fill_setter_maps());
 
} // end namespace Gambit

// Undef the various helper macros to avoid contaminating other files
#undef PDB

#endif
