//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Some member function definitions from classes
///  in spec_head.hpp.
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

#ifndef __SubSpectrum_hpp__
#define __SubSpectrum_hpp__

#include "gambit/Utils/safebool.hpp"
#include "gambit/Elements/spec_head.hpp"
#include "gambit/Elements/spec_fptrfinder.hpp"

namespace Gambit {

   /// @{ Spec member function definitions

   /// @{ No indices
   template <class DerivedSpec>
   bool Spec<DerivedSpec>::has(const Par::Tags partype, const str& name, const SpecOverrideOptions check_overrides, const SafeBool check_antiparticle) const
   {
      //typedef typename DerivedSpec::MTget MTget;
      /// TODO: Could avoid dismantling the MapCollection struct by just letting the
      ///       SetMaps class do it, but one step at a time...
      ///       Could also reduce duplication between getter and checker functions by making the
      ///       'has' function take an optional argument to return an FptrFinder, which can then
      ///       just be used to call the found function.

      bool overrides=true;
      bool override_only=false;
      if     (check_overrides == use_overrides) {  overrides=true;  override_only=false; }
      else if(check_overrides == overrides_only){  overrides=true;  override_only=true; }
      else if(check_overrides == ignore_overrides){overrides=false; override_only=false;}

      /* Create finder object, tell it what maps to search, and do the search */
      const OverrideMaps         overridecoll = override_maps.at(partype);
      const MapCollection<MTget> mapcoll      = getter_maps.at(partype);
      FptrFinder<Spec<DerivedSpec>,MapTag::Get> finder =
                       SetMaps<Spec<DerivedSpec>,MapTag::Get>(Par::toString.at(partype),this)
                              .omap0(  overridecoll.m0 )
                              .omap1( overridecoll.m1 )
                              .map0(  mapcoll.map0 )
                              .map1(  mapcoll.map1 )
                              .map0W( mapcoll.map0W )
                              .map1W( mapcoll.map1W )
                              .map0M( mapcoll.map0_extraM )
                              .map1M( mapcoll.map1_extraM )
			      .map0I( mapcoll.map0_extraI )
                              .map1I( mapcoll.map1_extraI )
                              .override_only(override_only)
                              .no_overrides(not overrides);
      return finder.find(name,true,check_antiparticle);
   }

   template <class DerivedSpec>
   double Spec<DerivedSpec>::get(const Par::Tags partype, const str& name, const SpecOverrideOptions check_overrides, const SafeBool check_antiparticle) const
   {
      //typedef typename DerivedSpec::MTget MTget;

      bool overrides=true;
      bool override_only=false;
      if     (check_overrides == use_overrides) {  overrides=true;  override_only=false; }
      else if(check_overrides == overrides_only){  overrides=true;  override_only=true; }
      else if(check_overrides == ignore_overrides){overrides=false; override_only=false;}

     /* Create finder object, tell it what maps to search, and do the search */
      const OverrideMaps         overridecoll = override_maps.at(partype);
      const MapCollection<MTget> mapcoll      = getter_maps.at(partype);
      FptrFinder<Spec<DerivedSpec>,MapTag::Get> finder =
                       SetMaps<Spec<DerivedSpec>,MapTag::Get>(Par::toString.at(partype),this)
                              .omap0(  overridecoll.m0 )
                              .omap1( overridecoll.m1 )
                              .map0(  mapcoll.map0 )
                              .map1(  mapcoll.map1 )
                              .map0W( mapcoll.map0W )
                              .map1W( mapcoll.map1W )
                              .map0M( mapcoll.map0_extraM )
                              .map1M( mapcoll.map1_extraM )
                              .map0I( mapcoll.map0_extraI )
                              .map1I( mapcoll.map1_extraI )
                              .override_only(override_only)
                              .no_overrides(not overrides);
      if( finder.find(name,true,check_antiparticle) ){ return finder.callfcn(); }
      finder.raise_error(LOCAL_INFO);
      return 0;
   }

   template <class DerivedSpec>
   void Spec<DerivedSpec>::set(const Par::Tags partype, const double set_value, const str& name, const SafeBool check_antiparticle)
   {
      typedef typename DerivedSpec::MTset MTset;

      /* Before trying to set parameter, check if there is an override defined
         for it, so that we can warn people that the value they are trying to
         set will be masked by the override */
      const OverrideMaps overridecoll = override_maps.at(partype);
      FptrFinder<Spec<DerivedSpec>,MapTag::Set> override_finder =
                       SetMaps<Spec<DerivedSpec>,MapTag::Set>(Par::toString.at(partype),this)
                              .omap0( overridecoll.m0 )
                              .omap1( overridecoll.m1 )
                              .override_only(true); // switch to permit search of only override maps
      if( override_finder.find(name,true,check_antiparticle) )
      {
        std::ostringstream errmsg;
        errmsg << "Warning from SubSpectrum object while trying to manually set a parameter!" << std::endl;
        errmsg << "An override entry was detected for "<<Par::toString.at(partype)<<" with string reference '"<<name<<"'. The override value will hide the value I have been instructed to set." <<std::endl;
        utils_warning().raise(LOCAL_INFO,errmsg.str());
      }
      // else no problem

      /* Create finder object, tell it what maps to search, and do the search */
      const MapCollection<MTset> mapcoll = setter_maps.at(partype);
      FptrFinder<Spec<DerivedSpec>,MapTag::Set> finder =
                       SetMaps<Spec<DerivedSpec>,MapTag::Set>(Par::toString.at(partype),this)
                              .map0(  mapcoll.map0 )
                              .map1(  mapcoll.map1 )
                              .map0W( mapcoll.map0W )
                              .map1W( mapcoll.map1W )
                              .map0M( mapcoll.map0_extraM )
                              .map1M( mapcoll.map1_extraM )
                              .map0I( mapcoll.map0_extraI )
                              .map1I( mapcoll.map1_extraI );
      if( finder.find(name,true,check_antiparticle) ){ finder.callfcn(set_value); }
      else { finder.raise_error(LOCAL_INFO); }
   }
   /// @}
   /// @{ One index
   template <class DerivedSpec>
   bool Spec<DerivedSpec>::has(const Par::Tags partype, const str& name, const int i, const SpecOverrideOptions check_overrides, const SafeBool check_antiparticle) const
   {
      //typedef typename DerivedSpec::MTget MTget;

      bool overrides=true;
      bool override_only=false;
      if     (check_overrides == use_overrides) {  overrides=true;  override_only=false; }
      else if(check_overrides == overrides_only){  overrides=true;  override_only=true; }
      else if(check_overrides == ignore_overrides){overrides=false; override_only=false;}

      /* Create finder object, tell it what maps to search, and do the search */
      const OverrideMaps         overridecoll = override_maps.at(partype);
      const MapCollection<MTget> mapcoll      = getter_maps.at(partype);
      FptrFinder<Spec<DerivedSpec>,MapTag::Get> finder =
                       SetMaps<Spec<DerivedSpec>,MapTag::Get>(Par::toString.at(partype),this)
                              .omap0( overridecoll.m0 )
                              .omap1( overridecoll.m1 )
                              .map0(  mapcoll.map0 )
                              .map1(  mapcoll.map1 )
                              .map0W( mapcoll.map0W )
                              .map1W( mapcoll.map1W )
                              .map0M( mapcoll.map0_extraM )
                              .map1M( mapcoll.map1_extraM )
                              .map0I( mapcoll.map0_extraI )
                              .map1I( mapcoll.map1_extraI )
                              .override_only(override_only)
                              .no_overrides(not overrides);
      return finder.find(name,i,true,check_antiparticle);
   }

   template <class DerivedSpec>
   double Spec<DerivedSpec>::get(const Par::Tags partype, const str& name, const int i, const SpecOverrideOptions check_overrides, const SafeBool check_antiparticle) const
   {
      //typedef typename DerivedSpec::MTget MTget;

      bool overrides=true;
      bool override_only=false;
      if     (check_overrides == use_overrides) {  overrides=true;  override_only=false; }
      else if(check_overrides == overrides_only){  overrides=true;  override_only=true; }
      else if(check_overrides == ignore_overrides){overrides=false; override_only=false;}

      /* Create finder object, tell it what maps to search, and do the search */
      const OverrideMaps         overridecoll = override_maps.at(partype);
      const MapCollection<MTget> mapcoll      = getter_maps.at(partype);
      FptrFinder<Spec<DerivedSpec>,MapTag::Get> finder =
                       SetMaps<Spec<DerivedSpec>,MapTag::Get>(Par::toString.at(partype),this)
                              .omap0( overridecoll.m0 )
                              .omap1( overridecoll.m1 )
                              .map0(  mapcoll.map0 )
                              .map1(  mapcoll.map1 )
                              .map0W( mapcoll.map0W )
                              .map1W( mapcoll.map1W )
                              .map0M( mapcoll.map0_extraM )
                              .map1M( mapcoll.map1_extraM )
                              .map0I( mapcoll.map0_extraI )
                              .map1I( mapcoll.map1_extraI )
                              .override_only(override_only)
                              .no_overrides(not overrides);
     if( finder.find(name,i,true,check_antiparticle) ){ return finder.callfcn(); }
     finder.raise_error(LOCAL_INFO);
     return 0;
   }

   template <class DerivedSpec>
   void Spec<DerivedSpec>::set(const Par::Tags partype, const double set_value, const str& name, const int i, const SafeBool check_antiparticle)
   {
      typedef typename DerivedSpec::MTset MTset;

      /* Before trying to set parameter, check if there is an override defined
         for it, so that we can warn people that the value they are trying to
         set will be masked by the override */
      const OverrideMaps overridecoll = override_maps.at(partype);
      FptrFinder<Spec<DerivedSpec>,MapTag::Set> override_finder =
                       SetMaps<Spec<DerivedSpec>,MapTag::Set>(Par::toString.at(partype),this)
                              .omap0( overridecoll.m0 )
                              .omap1( overridecoll.m1 )
                              .override_only(true); // switch to permit search of only override maps
      if( override_finder.find(name,i,true,check_antiparticle) )
      {
        std::ostringstream errmsg;
        errmsg << "Warning from SubSpectrum object while trying to manually set a parameter!" << std::endl;
        errmsg << "An override entry was detected for "<<Par::toString.at(partype)<<" with string reference '"<<name<<"', index '"<<i<<"'. The override value will hide the value I have been instructed to set." <<std::endl;
        utils_warning().raise(LOCAL_INFO,errmsg.str());
      }
      // else no problem

      /* Create finder object, tell it what maps to search, and do the search */
      const MapCollection<MTset> mapcoll = setter_maps.at(partype);
      FptrFinder<Spec<DerivedSpec>,MapTag::Set> finder =
                       SetMaps<Spec<DerivedSpec>,MapTag::Set>(Par::toString.at(partype),this)
                              .map0(  mapcoll.map0 )
                              .map1(  mapcoll.map1 )
                              .map0W( mapcoll.map0W )
                              .map1W( mapcoll.map1W )
                              .map0M( mapcoll.map0_extraM )
                              .map1M( mapcoll.map1_extraM )
                              .map0I( mapcoll.map0_extraI )
                              .map1I( mapcoll.map1_extraI );
     if( finder.find(name,i,true,check_antiparticle) ){ finder.callfcn(set_value); }
      else { finder.raise_error(LOCAL_INFO); }
   }

   /// @}
   /// @{ Two indices

   template <class DerivedSpec>
   bool Spec<DerivedSpec>::has(const Par::Tags partype, const str& name, const int i, const int j, const SpecOverrideOptions check_overrides) const
   {
      //typedef typename DerivedSpec::MTget MTget;

      bool overrides=true;
      bool override_only=false;
      if     (check_overrides == use_overrides) {  overrides=true;  override_only=false; }
      else if(check_overrides == overrides_only){  overrides=true;  override_only=true; }
      else if(check_overrides == ignore_overrides){overrides=false; override_only=false;}

      /* Create finder object, tell it what maps to search, and do the search */
      const OverrideMaps         overridecoll = override_maps.at(partype);
      const MapCollection<MTget> mapcoll      = getter_maps.at(partype);
      FptrFinder<Spec<DerivedSpec>,MapTag::Get> finder =
                       SetMaps<Spec<DerivedSpec>,MapTag::Get>(Par::toString.at(partype),this)
                              .omap2( overridecoll.m2 )
                              .map2(  mapcoll.map2 )
                              .map2W( mapcoll.map2W )
                              .map2M( mapcoll.map2_extraM )
                              .map2I( mapcoll.map2_extraI )
                              .override_only(override_only)
                              .no_overrides(not overrides);
     return finder.find(name,i,j);
   }

   template <class DerivedSpec>
   double Spec<DerivedSpec>::get(const Par::Tags partype, const str& name, const int i, const int j, const SpecOverrideOptions check_overrides) const
   {
      //typedef typename DerivedSpec::MTget MTget;

      bool overrides=true;
      bool override_only=false;
      if     (check_overrides == use_overrides) {  overrides=true;  override_only=false; }
      else if(check_overrides == overrides_only){  overrides=true;  override_only=true; }
      else if(check_overrides == ignore_overrides){overrides=false; override_only=false;}

      /* Create finder object, tell it what maps to search, and do the search */
      const OverrideMaps         overridecoll = override_maps.at(partype);
      const MapCollection<MTget> mapcoll      = getter_maps.at(partype);
      FptrFinder<Spec<DerivedSpec>,MapTag::Get> finder =
                       SetMaps<Spec<DerivedSpec>,MapTag::Get>(Par::toString.at(partype),this)
                              .omap2( overridecoll.m2 )
                              .map2(  mapcoll.map2 )
                              .map2W( mapcoll.map2W )
                              .map2M( mapcoll.map2_extraM )
                              .map2I( mapcoll.map2_extraI )
                              .override_only(override_only)
                              .no_overrides(not overrides);
      if( finder.find(name,i,j) ){ return finder.callfcn(); }
      finder.raise_error(LOCAL_INFO);
      return 0;
   }

   template <class DerivedSpec>
   void Spec<DerivedSpec>::set(const Par::Tags partype, const double set_value, const str& name, const int i, const int j)
   {
      typedef typename DerivedSpec::MTset MTset;

      /* Create finder object, tell it what maps to search, and do the search */
      const MapCollection<MTset> mapcoll = setter_maps.at(partype);
      FptrFinder<Spec<DerivedSpec>,MapTag::Set> finder =
                       SetMaps<Spec<DerivedSpec>,MapTag::Set>(Par::toString.at(partype),this)
                              .map2(  mapcoll.map2 )
                              .map2W( mapcoll.map2W )
                              .map2M( mapcoll.map2_extraM )
                              .map2I( mapcoll.map2_extraI );
      if( finder.find(name,i,j) ){ finder.callfcn(set_value); }
      else { finder.raise_error(LOCAL_INFO); }
   }

   /// @}

   /// @}

}

#endif
