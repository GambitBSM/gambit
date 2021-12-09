//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Helpers for using the spectrum classes.
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

#ifndef __spectrum_helpers_hpp__
#define __spectrum_helpers_hpp__

#include <string>
#include <set>
#include <vector>
#include <map>

namespace Gambit
{
   typedef std::string str;

   /// Helper function for checking if indices are valid
   inline bool within_bounds(const int i, const std::set<int> allowed)
   {
     return ( allowed.find(i) != allowed.end() );
   }
   
   /// List of parameter types used to classify spectrum contents
   namespace Par
   {
      enum Tags
      {
          /// Ex-"Phys" tags
          Pole_Mass = 0,
          Pole_Mass_1srd_high,
          Pole_Mass_1srd_low,
          Pole_Mixing,
          /// Ex-"Running" tags
          mass4 = Pole_Mixing+1,
          mass3,
          mass2,
          mass1,
          dimensionless,
          /// 1/mass^d dimensions
          imass1,
          imass2,
          imass3,
          imass4,
          mass_eigenstate
      };

      // Stick enum values in a vector to help auto-generate maps that use them as keys
      inline std::vector<Tags> get_all()
      {
         std::vector<Tags> vec;
         vec.push_back(Pole_Mass);
         vec.push_back(Pole_Mass_1srd_high);
         vec.push_back(Pole_Mass_1srd_low);
         vec.push_back(Pole_Mixing);
         vec.push_back(mass4);
         vec.push_back(mass3);
         vec.push_back(mass2);
         vec.push_back(mass1);
         vec.push_back(dimensionless);
         vec.push_back(imass1);
         vec.push_back(imass2);
         vec.push_back(imass3);
         vec.push_back(imass4);
         vec.push_back(mass_eigenstate);
         return vec;
      }

      /// Map from enum value to string, for error messages
      static std::map<Tags,std::string> fill_map()
      {
         std::map<Tags,std::string> name;
         name[Pole_Mass]       = "Pole_Mass";
         name[Pole_Mass_1srd_high] = "Pole_Mass_1srd_high";
         name[Pole_Mass_1srd_low]  = "Pole_Mass_1srd_low";
         name[Pole_Mixing]     = "Pole_Mixing";
         name[mass4]           = "mass4";
         name[mass3]           = "mass3";
         name[mass2]           = "mass2";
         name[mass1]           = "mass1";
         name[dimensionless]   = "dimensionless";
         name[imass1]          = "imass1";
         name[imass2]          = "imass2";
         name[imass3]          = "imass3";
         name[imass4]          = "imass4";
         name[mass_eigenstate] = "mass_eigenstate";
         return name;
      }
      static const std::map<Tags,std::string> toString = fill_map();
   }

   /// Mini helper class to specify behaviour of getters w.r.t. overrides in a type-safe way
   class SpecOverrideOptions
   {
     private:
      int my_value;
     public:
      int value() const { return my_value; }
      SpecOverrideOptions(int i) : my_value(i) {}
   };
   inline static bool operator==(const SpecOverrideOptions& lhs, const SpecOverrideOptions& rhs) 
   { return lhs.value() == rhs.value(); }
   static const SpecOverrideOptions use_overrides(0);
   static const SpecOverrideOptions overrides_only(1);
   static const SpecOverrideOptions ignore_overrides(2);

   /// Structs to hold function pointers and valid index sets
   /// @{
   
   template <class Fptr>
   struct FcnInfo1
   {
       Fptr fptr; 
       std::set<int> iset1;   
       FcnInfo1() {}
       FcnInfo1(Fptr p, std::set<int> s)
         : fptr(p)
         , iset1(s)
       {}
   };
   
   template <class Fptr>
   struct FcnInfo2
   {
       Fptr fptr; 
       std::set<int> iset1;   
       std::set<int> iset2;
       FcnInfo2() {}
       FcnInfo2(Fptr p, std::set<int> s1, std::set<int> s2)
         : fptr(p)
         , iset1(s1)
         , iset2(s2)
       {}
   };
   
   /// @}
   
   /// @{ Traits structs for function pointer maps
   /// Get the types like this: MapTypes<WrapTraits,MapTag::Get>::fmap
   ///                 or this: MapTypes<WrapTraits,MapTag::Set>::fmap
  
   /// Tags
   struct MapTag {
     struct Get {};
     struct Set {};
   };

   /// Fully unspecialised MapTypes declaration
   template <class DerivedSpec, class GetOrSet>
   struct MapTypes;

   /// Declare empty base traits class which communicates
   /// Model and Input typedefs from the wrapper class
   template <class>
   struct SpecTraits;

   /// Types needed for function pointer maps
   /// Partial specialisation for "getter" maps
   template <class DerivedSpec>
   struct MapTypes<DerivedSpec, MapTag::Get>
   {
      // Typedef collection
      typedef typename SpecTraits<DerivedSpec>::Model Model;
      typedef typename SpecTraits<DerivedSpec>::Input Input;
      typedef double(Model::*FSptr)(void) const; /* Function pointer signature for Model object member functions with no arguments */
      typedef double(Model::*FSptr1)(int) const; /* Function pointer signature for Model object member functions with one argument */
      typedef double(Model::*FSptr2)(int,int) const; /* Function pointer signature for Model object member functions with two arguments */
      typedef double(DerivedSpec::*FSptrW)(void) const; /* Function pointer signature for DerivedSpec member functions with no arguments */
      typedef double(DerivedSpec::*FSptr1W)(int) const; /* Function pointer signature for DerivedSpec member functions with one argument */
      typedef double(DerivedSpec::*FSptr2W)(int,int) const; /* Function pointer signature for DerivedSpec member functions with two arguments */
      typedef double(*plainfptrM)(const Model&); /* Function pointer for plain functions; used for custom functions */
      typedef double(*plainfptrM1)(const Model&,int); /* ... with one index */
      typedef double(*plainfptrM2)(const Model&,int,int); /* ... with two indices */
      typedef double(*plainfptrI)(const Input&);     /* Function pointer for plain functions; used for custom functions */
      typedef double(*plainfptrI1)(const Input&,int); /* ... with one index */
      typedef double(*plainfptrI2)(const Input&,int,int); /* with two indices */
      typedef FcnInfo1<FSptr1> FInfo1; // Structs to help specify valid indices for functions
      typedef FcnInfo2<FSptr2> FInfo2; //    "              " 
      typedef FcnInfo1<FSptr1W> FInfo1W; //    "              "
      typedef FcnInfo2<FSptr2W> FInfo2W; //    "              " 
      typedef FcnInfo1<plainfptrM1> FInfo1M; //    "              " 
      typedef FcnInfo2<plainfptrM2> FInfo2M; //    "              " 
      typedef FcnInfo1<plainfptrI1> FInfo1I; //    "              " 
      typedef FcnInfo2<plainfptrI2> FInfo2I; //    "              " 
      typedef std::map<str, FSptr> fmap0; /* Typedef for map of strings to Model function pointers */
      typedef std::map<str, FInfo1> fmap1;/*with an index*/
      typedef std::map<str, FInfo2> fmap2; /*with 2 indices */
      typedef std::map<str, FSptrW> fmap0W; /* Typedef for map of strings to DerivedSpec function pointers */
      typedef std::map<str, FInfo1W> fmap1W;/* with an index*/
      typedef std::map<str, FInfo2W> fmap2W; /*with 2 indices */
      typedef std::map<str, plainfptrM> fmap0_extraM;  /* map of plain function pointers */
      typedef std::map<str, FInfo1M> fmap1_extraM;  /* map of plain function pointers */
      typedef std::map<str, FInfo2M> fmap2_extraM;  /* map of plain function pointers */
      typedef std::map<str, plainfptrI> fmap0_extraI; /* map of plain function pointers */
      typedef std::map<str, FInfo1I> fmap1_extraI; /* map of plain function pointers */
      typedef std::map<str, FInfo2I> fmap2_extraI; /* map of plain function pointers */
   };

   /// Types needed for function pointer maps
   /// Partial specialisation for "setter" maps
   template <class DerivedSpec>
   struct MapTypes<DerivedSpec, MapTag::Set>
   {
      // Typedef collection
      typedef typename SpecTraits<DerivedSpec>::Model Model;
      typedef typename SpecTraits<DerivedSpec>::Input Input;
      typedef void(Model::*FSptr)(double); /* Function pointer signature for Model object member functions with no arguments */
      typedef void(Model::*FSptr1)(int,const double&); /* Function pointer signature for Model object member functions with one argument */
      typedef void(Model::*FSptr2)(int,int,const double&); /* Function pointer signature for Model object member functions with two arguments */
      typedef void(DerivedSpec::*FSptrW)(double); /* Function pointer signature for DerivedSpec member functions with no arguments */
      typedef void(DerivedSpec::*FSptr1W)(double,int); /* Function pointer signature for DerivedSpec member functions with one argument */
      typedef void(DerivedSpec::*FSptr2W)(double,int,int); /* Function pointer signature for DerivedSpec object member functions with two arguments */
       typedef void(*plainfptrM)(Model&, double); /* Function pointer for plain functions; used for custom functions */
      typedef void(*plainfptrM1)(Model&, double, int); /* Function pointer for plain functions; used for custom functions */
      typedef void(*plainfptrM2)(Model&, double, int, int); /* Function pointer for plain functions; used for custom functions */
      typedef void(*plainfptrI)(Input&, double); /* Function pointer for plain functions; used for custom functions */
      typedef void(*plainfptrI1)(Input&, double, int); /* Function pointer for plain functions; used for custom functions */
      typedef void(*plainfptrI2)(Input&, double, int, int); /* Function pointer for plain functions; used for custom functions */
      typedef FcnInfo1<FSptr1> FInfo1; // Structs to help specify valid indices for functions
      typedef FcnInfo2<FSptr2> FInfo2; //    "              " 
      typedef FcnInfo1<FSptr1W> FInfo1W; //    "              "
      typedef FcnInfo2<FSptr2W> FInfo2W; //    "              " 
      typedef FcnInfo1<plainfptrM1> FInfo1M; //    "              " 
      typedef FcnInfo2<plainfptrM2> FInfo2M; //    "              " 
      typedef FcnInfo1<plainfptrI1> FInfo1I; //    "              " 
      typedef FcnInfo2<plainfptrI2> FInfo2I; //    "              " 
      typedef std::map<str, FSptr> fmap0; /* Typedef for map of strings to function pointers */
      typedef std::map<str, FInfo1> fmap1;/*with an index*/
      typedef std::map<str, FInfo2> fmap2; /*with 2 indices */
      typedef std::map<str, FSptrW> fmap0W; /* Typedef for map of strings to DerivedSpec function pointers */
      typedef std::map<str, FInfo1W> fmap1W;/* with an index*/
      typedef std::map<str, FInfo2W> fmap2W; /*with 2 indices */
      typedef std::map<str, plainfptrM> fmap0_extraM;  /* map of plain function pointers */
      typedef std::map<str, FInfo1M> fmap1_extraM;  /* map of plain function pointers */
      typedef std::map<str, FInfo2M> fmap2_extraM;  /* map of plain function pointers */
      typedef std::map<str, plainfptrI> fmap0_extraI; /* map of plain function pointers */
      typedef std::map<str, FInfo1I> fmap1_extraI; /* map of plain function pointers */
      typedef std::map<str, FInfo2I> fmap2_extraI; /* map of plain function pointers */
   };

   /// @}

}

#endif // #defined __spectrum_helpers_hpp__
