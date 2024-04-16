//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  SubSpectrum helper class for seaching through
///  the function pointer maps and calling the
///  requested function.
///
///  *********************************************
///
///  Authors:
///  <!-- add name and date if you modify -->
///
///  \author Ben Farmer
///          (benjamin.farmer@fysik.su.se)
///  \date 2015 Jul
///
///  *********************************************

#ifndef __SpecFptrFinder_hpp__
#define __SpecFptrFinder_hpp__

#include "gambit/Elements/spectrum_helpers.hpp"
#include "gambit/Elements/subspectrum.hpp"
#include "gambit/Models/partmap.hpp"

// Particle database access
#define PDB Models::ParticleDB()

// Debugging
//#define CHECK_WHERE_FOUND

namespace Gambit {

   /// Forward declaration of FptrFinder
   template<class HostSpec, class MTag>
   class FptrFinder;

   /// FptrFinder friend class for implementing named parameter idiom
   template<class HostSpec, class MTag>
   class SetMaps
   {
      public:
         SetMaps(const std::string& label, HostSpec* const fakethis)
          : label_(label)
          , fakethis_(fakethis)
          , const_fakethis_(fakethis)
          , no_overrides_(false)
          , override_only_(false)
          , map0_(NULL)
          , map1_(NULL)
          , map2_(NULL)
          , map0W_(NULL)
          , map1W_(NULL)
          , map2W_(NULL)
          , map0M_(NULL)
          , map1M_(NULL)
          , map2M_(NULL)
          , map0I_(NULL)
          , map1I_(NULL)
          , map2I_(NULL)
          , omap0_(NULL)
          , omap1_(NULL)
          , omap2_(NULL)
         {}

         /// Version to deal with const host object
         SetMaps(const std::string& label, const HostSpec* const fakethis)
          : label_(label)
          , fakethis_(NULL) // CANNOT USE WHEN HOST IS CONST
          , const_fakethis_(fakethis)
          , no_overrides_(false)
          , override_only_(false)
          , map0_(NULL)
          , map1_(NULL)
          , map2_(NULL)
          , map0W_(NULL)
          , map1W_(NULL)
          , map2W_(NULL)
          , map0M_(NULL)
          , map1M_(NULL)
          , map2M_(NULL)
          , map0I_(NULL)
          , map1I_(NULL)
          , map2I_(NULL)
          , omap0_(NULL)
          , omap1_(NULL)
          , omap2_(NULL)
         {}

         /// Type of derived spectrum wrapper is known to HostSpec as D
         typedef typename HostSpec::D D;

         /// derived class maps
         SetMaps& map0 (const typename MapTypes<D,MTag>::fmap0&        map0) { map0_ =&map0;  return *this; }
         SetMaps& map1 (const typename MapTypes<D,MTag>::fmap1&        map1) { map1_ =&map1;  return *this; }
         SetMaps& map2 (const typename MapTypes<D,MTag>::fmap2&        map2) { map2_ =&map2;  return *this; }
         SetMaps& map0W(const typename MapTypes<D,MTag>::fmap0W&       map0W){ map0W_=&map0W; return *this; }
         SetMaps& map1W(const typename MapTypes<D,MTag>::fmap1W&       map1W){ map1W_=&map1W; return *this; }
         SetMaps& map2W(const typename MapTypes<D,MTag>::fmap2W&       map2W){ map2W_=&map2W; return *this; }
         SetMaps& map0M(const typename MapTypes<D,MTag>::fmap0_extraM& map0M){ map0M_=&map0M; return *this; }
         SetMaps& map1M(const typename MapTypes<D,MTag>::fmap1_extraM& map1M){ map1M_=&map1M; return *this; }
         SetMaps& map2M(const typename MapTypes<D,MTag>::fmap2_extraM& map2M){ map2M_=&map2M; return *this; }
         SetMaps& map0I(const typename MapTypes<D,MTag>::fmap0_extraI& map0I){ map0I_=&map0I; return *this; }
         SetMaps& map1I(const typename MapTypes<D,MTag>::fmap1_extraI& map1I){ map1I_=&map1I; return *this; }
         SetMaps& map2I(const typename MapTypes<D,MTag>::fmap2_extraI& map2I){ map2I_=&map2I; return *this; }
         /// base class override maps
         SetMaps& omap0(const std::map<std::string,double>& om0)              { omap0_=&om0; return *this;}
         SetMaps& omap1(const std::map<std::string,std::map<int,double>>& om1){ omap1_=&om1; return *this;}
         SetMaps& omap2(const std::map<std::string,std::map<int,std::map<int,double>>>& om2){ omap2_=&om2; return *this;}
         /// Flag to disable searching of override maps (for retrieving original, unoverriden values)
         SetMaps& no_overrides(const bool flag) { no_overrides_=flag; return *this;}
         /// Flag to permit searching only override maps
         SetMaps& override_only(const bool flag) { override_only_=flag; return *this;}
         // (Obviously don't set both of the above flags at once, or else there will be no maps to search...)

      private:
         friend class FptrFinder<HostSpec,MTag>;
         const std::string label_;
         HostSpec* const fakethis_;
         const HostSpec* const const_fakethis_;
         bool no_overrides_;
         bool override_only_;

         /// Maps from derived class
         const typename MapTypes<D,MTag>::fmap0*        map0_;
         const typename MapTypes<D,MTag>::fmap1*        map1_;
         const typename MapTypes<D,MTag>::fmap2*        map2_;
         const typename MapTypes<D,MTag>::fmap0W*       map0W_;
         const typename MapTypes<D,MTag>::fmap1W*       map1W_;
         const typename MapTypes<D,MTag>::fmap2W*       map2W_;
         const typename MapTypes<D,MTag>::fmap0_extraM* map0M_;
         const typename MapTypes<D,MTag>::fmap1_extraM* map1M_;
         const typename MapTypes<D,MTag>::fmap2_extraM* map2M_;
         const typename MapTypes<D,MTag>::fmap0_extraI* map0I_;
         const typename MapTypes<D,MTag>::fmap1_extraI* map1I_;
         const typename MapTypes<D,MTag>::fmap2_extraI* map2I_;

         /// Maps from base class (override maps, only used in getter case)
         const std::map<std::string,double>*                             omap0_;
         const std::map<std::string,std::map<int,double>>*               omap1_;
         const std::map<std::string,std::map<int,std::map<int,double>>>* omap2_;
   };

   /// Helper class for calling function pointers found by FptrFinder
   template<class HostSpec, class MTag>
   class CallFcn;

   /// Helper class for locating the function pointer corresponding to a
   /// requested string, from amongst the various different maps in which
   /// it could be located.
   template<class HostSpec, class MTag>
   class FptrFinder
   {
      friend class CallFcn<HostSpec,MTag>;

      private:
         /// Label to help track down errors if they occur
         const std::string label;

         /// Last used search string (only set if there was a problem, for error messages)
         std::string lastname;

         /// HostSpec class pretending to be an extra set of class functions, so need the "this" pointer
         HostSpec* const fakethis;
         const HostSpec* const const_fakethis;

         /// Get type of the derived spectrum wrapper from HostSpec
         typedef typename HostSpec::D D; // D for "DerivedSpec"

         /// Flag to disable searching of override maps (for retrieving original, unoverriden values)
         const bool no_overrides_;

         /// Flag to permit searching only override maps
         const bool override_only_;

         /// Pointers to const maps to use for search
         /// Maps from base class (override maps, should only be used in getter case)
         const std::map<std::string,double>*                             omap0_;
         const std::map<std::string,std::map<int,double>>*               omap1_;
         const std::map<std::string,std::map<int,std::map<int,double>>>* omap2_;
         /// Maps filled by derived (wrapper) classes
         const typename MapTypes<D,MTag>::fmap0*        map0_;
         const typename MapTypes<D,MTag>::fmap1*        map1_;
         const typename MapTypes<D,MTag>::fmap2*        map2_;
         const typename MapTypes<D,MTag>::fmap0W*       map0W_;
         const typename MapTypes<D,MTag>::fmap1W*       map1W_;
         const typename MapTypes<D,MTag>::fmap2W*       map2W_;
         const typename MapTypes<D,MTag>::fmap0_extraM* map0M_;
         const typename MapTypes<D,MTag>::fmap1_extraM* map1M_;
         const typename MapTypes<D,MTag>::fmap2_extraM* map2M_;
         const typename MapTypes<D,MTag>::fmap0_extraI* map0I_;
         const typename MapTypes<D,MTag>::fmap1_extraI* map1I_;
         const typename MapTypes<D,MTag>::fmap2_extraI* map2I_;

         /// Iterators needed for storing locatation of search result
         /// ...for override values
         std::map<std::string,double>::const_iterator                ito0; // 0
         std::map<std::string,std::map<int,double>>::const_iterator  ito1; // 1
         std::map<std::string,std::map<int,std::map<int,double>>>::const_iterator ito2; // 2
         /// ...for derived class values
         typename MapTypes<D,MTag>::fmap0::const_iterator        it0;  // 3
         typename MapTypes<D,MTag>::fmap1::const_iterator        it1;  // 6
         typename MapTypes<D,MTag>::fmap2::const_iterator        it2;  // 9 //was 7
         typename MapTypes<D,MTag>::fmap0W::const_iterator       it0W; // ? 12
         typename MapTypes<D,MTag>::fmap1W::const_iterator       it1W; // ? 13
         typename MapTypes<D,MTag>::fmap2W::const_iterator       it2W; // ? 14
         typename MapTypes<D,MTag>::fmap0_extraM::const_iterator it0M; // 4
         typename MapTypes<D,MTag>::fmap1_extraM::const_iterator it1M; // 7
         typename MapTypes<D,MTag>::fmap2_extraM::const_iterator it2M; // 10
         typename MapTypes<D,MTag>::fmap0_extraI::const_iterator it0I; // 5
         typename MapTypes<D,MTag>::fmap1_extraI::const_iterator it1I; // 8
         typename MapTypes<D,MTag>::fmap2_extraI::const_iterator it2I; // 11

         /// empty maps used to initialise the above iterators
         static const std::map<std::string,double>                nullmap_ito0; // 0
         static const std::map<std::string,std::map<int,double>>  nullmap_ito1; // 1
         static const std::map<std::string,std::map<int,std::map<int,double>>> nullmap_ito2; // 2
         static const typename MapTypes<D,MTag>::fmap0        nullmap_it0;  // 3
         static const typename MapTypes<D,MTag>::fmap1        nullmap_it1;  // 6
         static const typename MapTypes<D,MTag>::fmap2        nullmap_it2;  // 9 //was 7
         static const typename MapTypes<D,MTag>::fmap0W       nullmap_it0W;  // ? 12
         static const typename MapTypes<D,MTag>::fmap1W       nullmap_it1W;  // ? 13
         static const typename MapTypes<D,MTag>::fmap2W       nullmap_it2W;  // ? 14
         static const typename MapTypes<D,MTag>::fmap0_extraM nullmap_it0M; // 4
         static const typename MapTypes<D,MTag>::fmap1_extraM nullmap_it1M; // 7
         static const typename MapTypes<D,MTag>::fmap2_extraM nullmap_it2M; // 10
         static const typename MapTypes<D,MTag>::fmap0_extraI nullmap_it0I; // 5
         static const typename MapTypes<D,MTag>::fmap1_extraI nullmap_it1I; // 8
         static const typename MapTypes<D,MTag>::fmap2_extraI nullmap_it2I; // 11

         /// Functions to check whether or not it is safe to dereference the above iterators
         bool ito0_safe() { return ito0 != nullmap_ito0.end(); };
         bool ito1_safe() { return ito1 != nullmap_ito1.end(); };
         bool ito2_safe() { return ito2 != nullmap_ito2.end(); };
         bool it0_safe()  { return it0  != nullmap_it0.end(); };
         bool it1_safe()  { return it1  != nullmap_it1.end(); };
         bool it2_safe()  { return it2  != nullmap_it2.end(); };
         bool it0W_safe() { return it0W != nullmap_it0W.end(); };
         bool it1W_safe() { return it1W != nullmap_it1W.end(); };
         bool it2W_safe() { return it2W != nullmap_it2W.end(); };
         bool it0M_safe() { return it0M != nullmap_it0M.end(); };
         bool it1M_safe() { return it1M != nullmap_it1M.end(); };
         bool it2M_safe() { return it2M != nullmap_it2M.end(); };
         bool it0I_safe() { return it0I != nullmap_it0I.end(); };
         bool it1I_safe() { return it1I != nullmap_it1I.end(); };
         bool it2I_safe() { return it2I != nullmap_it2I.end(); };

         // int which records which iterator points to the search result
         int whichiter;

         // indices required for function call
         int index1;
         int index2;

         // error code
         // -1 : search not yet attempted
         //  0 : no problem, search succeeded
         //  1 : string name lookup failed
         //  2 : string name lookup succeeded, index1 out of bounds
         //  3 : string name lookup succeeded, index2 out of bounds
         int error_code;

         // Messages corresponding to the above error codes
         static const std::map<int, const std::string> error_msg;

      public:
         /// Caller for whatever function was found
         /// HostSpec has to work slightly differently depending on whether FptrFinder is
         /// specialised for MapTag::Get or MapTag::Set, so we just declare it here and
         /// do the specialisation after the class declaration.
         /// HostSpec has to be a struct, since we partial specialisation of functions is
         /// not allowed in C++, but it is treated like a member function.
         CallFcn<HostSpec,MTag> callfcn;

         // Constructor utilising named "parameters"
         FptrFinder(const SetMaps<HostSpec,MTag>& params)
           : label(params.label_)
           , lastname("NONE")
           , fakethis(params.fakethis_)
           , const_fakethis(params.const_fakethis_)
           , no_overrides_(params.no_overrides_)
           , override_only_(params.override_only_)
           , omap0_(params.omap0_)
           , omap1_(params.omap1_)
           , omap2_(params.omap2_)
           , map0_ (params.map0_)
           , map1_ (params.map1_)
           , map2_ (params.map2_)
           , map0W_(params.map0W_)
           , map1W_(params.map1W_)
           , map2W_(params.map2W_)
           , map0M_(params.map0M_)
           , map1M_(params.map1M_)
           , map2M_(params.map2M_)
           , map0I_(params.map0I_)
           , map1I_(params.map1I_)
           , map2I_(params.map2I_)
           , ito0(nullmap_ito0.end())
           , ito1(nullmap_ito1.end())
           , ito2(nullmap_ito2.end())
           , it0 (nullmap_it0.end())
           , it1 (nullmap_it1.end())
           , it2 (nullmap_it2.end())
           , it0W(nullmap_it0W.end())
           , it1W(nullmap_it1W.end())
           , it2W(nullmap_it2W.end())
           , it0M(nullmap_it0M.end())
           , it1M(nullmap_it1M.end())
           , it2M(nullmap_it2M.end())
           , it0I(nullmap_it0I.end())
           , it1I(nullmap_it1I.end())
           , it2I(nullmap_it2I.end())
           , whichiter(-1)
           , index1(-1)
           , index2(-1)
           , error_code(-1)
           , callfcn(this)
         {}

         /// @{ Error reporting
         int          get_error_code(){ return error_code; }
         std::string  get_error_message()
         {
            std::string msg;
            switch(error_code)
            {
                case -2: msg = "Search began but did not properly set the error code!"; break;
                case -1: msg = "Search not yet attempted"; break;
                case 0:  msg = "No problem, search succeeded"; break;
                case 1:  msg = "String name lookup failed"; break;
                case 2:  msg = "String name lookup succeeded, index1 out of bounds"; break;
                case 3:  msg = "String name lookup succeeded, index2 out of bounds"; break;
                default: msg = "Unrecognised error code! This is a bug in FptrFinder!";
           }
           return msg;
         }
         // Raise error if the calling context can't handle a failed search
         void raise_error(const std::string& origin)
         {
           std::ostringstream errmsg;
           errmsg << "Error retrieving particle spectrum data!" << std::endl;
           errmsg << "No "<<label<<" with string reference '"<<lastname<<"' exists!" <<std::endl;
           errmsg << "Search failed with error_code "<<error_code<<" from FptrFinder with label "<<label<<": "<<get_error_message();
           if(index1!=-1) errmsg << "  index1: "<<index1<<std::endl;
           if(index2!=-1) errmsg << "  index2: "<<index2<<std::endl;
           utils_error().forced_throw(origin,errmsg.str());
         }
         // Check if an index has been set, and raise error if not
         void check_index_initd(const std::string& origin, const int index, const std::string& label)
         {
           if(index==-1)
           {
             std::ostringstream errmsg;
             errmsg << "Error retrieving particle spectrum data!" << std::endl;
             errmsg << "An index ("<<label<<") was not set when retrieving item of type '"<<label<<"' with string reference '"<<lastname<<"'!" <<std::endl;
             errmsg << "This is a bug in the FptrFinder class, please report it."<<std::endl;
             utils_error().forced_throw(origin,errmsg.str());
           }
         }
         /// @}

         /// helper functions for searching individual maps
         template<class Map>
         bool search_map(const std::string& name, const Map* const map, typename Map::const_iterator& it)
         {
           bool found = true;
           if(map==NULL)
           {
              std::ostringstream errmsg;
              errmsg << "Tried to use FptrFinder to search a SubSpectrum function pointer map, but did not correctly supply the map to FptrFinder! This is a bug in the SubSpectrum class; please report it. (Attempted to access map of type "<<typeid(Map).name()<<")";
              utils_error().forced_throw(LOCAL_INFO,errmsg.str());
           }
           it = map->find(name);
           if( it == map->end() ){ found = false; lastname = name; }
           return found;
         }

         /// Check if it is (supposed to be) safe to dereference a map iterator
         /// Throw an error if it isn't
         void check(bool safe)
         {
           if(not safe)
           {
              std::ostringstream errmsg;
              errmsg << "Safety check for map iterator failed! (in FptrFinder). This indicates a bug in the FptrFinder class; please report it.";
              utils_error().forced_throw(LOCAL_INFO,errmsg.str());
           }
         }

         /// Methods for setting parameters (named parameter idiom)
         /// E.g. call constructor like this to use named "parameters"
         /// FptrFinder().map(x).map2(z).mapM(y)
         /// Could protect parameters from being reset by putting these setters in a friend class,
         /// which can only set the FptrFinder parameters via the FptrFinder constructor, but this
         /// is good enough for the use here I think.
         /// NOTE: I think this comment refers to moved/removed functionality...

         template<class ITER>
         bool check_indices_1(const std::string& name, const ITER& it, const int i, const int whichit, const bool debug)
         {
            bool found = false;
            /* Switch index convention */
            int offset = const_fakethis->get_index_offset();
            index1 = i + offset; /* set for later use */
            /* Check that index is in the permitted set */
            if( not within_bounds(index1, it->second.iset1) )
            {
               /* index1 out of bounds */
               found = false;
               error_code = 2;
            }
            else {
               /* everything cool. */
               found = true;
               if(debug) std::cout<<"   Found ("<<name<<","<<i<<") in 1-index map"<<std::endl;
               whichiter=whichit;
            }
            return found;
         }

         template<class ITER>
         bool check_indices_2(const std::string& /*name*/, const ITER& it, const int i, const int j, const int whichit)
         {
            bool found = false;
            /* Switch index convention */
            int offset = const_fakethis->get_index_offset();
            index1 = i + offset; /* set for later use */
            index2 = j + offset; /* set for later use */
            /* Check that index is in the permitted set */
            if( not within_bounds(index1, it->second.iset1) )
            {
               /* index1 out of bounds */
               found = false;
               error_code = 2;
            }
            else if( not within_bounds(index2, it->second.iset2) )
            {
               /* index2 out of bounds */
               found = false;
               error_code = 3;
            }
            else {
               /* everything cool. */
               found = true;
               whichiter=whichit;
            }
            return found;
         }

         /// @{ Functions to search for specific entries with no translation
         /// (to factorise the various pieces of the complicated search functions)

         /// Search 0-index override map
         bool find_override_0index(const std::string& name)
         {
            bool found = false;
            #ifdef CHECK_WHERE_FOUND
            std::cout<<"   Searching 0-index override maps for "<<name<<std::endl;
            #endif
            if( omap0_!=NULL and search_map(name,omap0_,ito0) )
            {
               found=true;
               whichiter=0;
               #ifdef CHECK_WHERE_FOUND
               std::cout<<"   Found "<<name<<" in 0-index override map"<<std::endl;
               #endif
            }
            return found;
         }

         /// Search 1-index override map
         bool find_override_1index(const std::string& name, const int i)
         {
            bool found = false;
            #ifdef CHECK_WHERE_FOUND
            std::cout<<"   Searching 1-index override maps for ("<<name<<","<<i<<")"<<std::endl;
            #endif
            if( omap1_!=NULL and search_map(name,omap1_,ito1) )
            {
               // Check that index (key) exists in inner map
               std::map<int,double>::const_iterator it = ito1->second.find(i);
               if( it != ito1->second.end() )
               {
                  found=true;
                  index1=i;
                  whichiter=1;
                  #ifdef CHECK_WHERE_FOUND
                  std::cout<<"   Found ("<<name<<","<<i<<") in 1-index override map"<<std::endl;
                  #endif
               }
            }
            return found;
         }

         /// Search 2-index override map
         bool find_override_2index(const std::string& name, const int i, const int j)
         {
            bool found = false;
            #ifdef CHECK_WHERE_FOUND
            std::cout<<"   Searching 2-index override maps for ("<<name<<","<<i<<","<<j<<")"<<std::endl;
            #endif
            if( omap2_!=NULL and search_map(name,omap2_,ito2) )
            {
               // Check that first index (key) exists in inner map
               std::map<int,std::map<int,double>>::const_iterator jt = ito2->second.find(i);
               if( jt != ito2->second.end() )
               {
                  // Check that second index (key) exists in second-inner map
                  std::map<int,double>::const_iterator jt2 = jt->second.find(j);
                  if( jt2 != jt->second.end() )
                  {
                     found=true;
                     index1=i;
                     index2=j;
                     whichiter=2;
                  }
               }
            }
            return found;
         }

         /// Search 0-index wrapper maps
         bool find_0index(const std::string& name)
         {
            bool found = false;
            #ifdef CHECK_WHERE_FOUND
            std::cout<<"   Searching 0-index standard maps for "<<name<<std::endl;
            #endif
            if     ( search_map(name,map0_,it0)   ){ found=true; whichiter=3;
               #ifdef CHECK_WHERE_FOUND
               std::cout<<"   Found "<<name<<" in found in 0-index map (type O)"<<std::endl;
               #endif
            }
            else if( search_map(name,map0W_,it0W) ){ found=true; whichiter=12;
               #ifdef CHECK_WHERE_FOUND
               std::cout<<"   Found "<<name<<" in found in 0-index map (type OW)"<<std::endl;
               #endif
            }
            else if( search_map(name,map0M_,it0M) ){ found=true; whichiter=4;
               #ifdef CHECK_WHERE_FOUND
               std::cout<<"   Found "<<name<<" in found in 0-index map (type OM)"<<std::endl;
               #endif
            }
            else if( search_map(name,map0I_,it0I) ){ found=true; whichiter=5;
               #ifdef CHECK_WHERE_FOUND
               std::cout<<"   Found "<<name<<" in found in 0-index map (type OI)"<<std::endl;
               #endif
            }
            return found;
         }

         /// Search 1-index wrapper maps
         bool find_1index(const std::string& name, const int i)
         {
            bool found = false;
            #ifdef CHECK_WHERE_FOUND
            std::cout<<"   Searching standard 1-index maps for ("<<name<<","<<i<<")"<<std::endl;
            #endif

            bool debug=false;
            #ifdef CHECK_WHERE_FOUND
            debug=true;
            #endif

            if( search_map(name,map1_,it1) )       { check(it1_safe());  found=check_indices_1(name,it1 ,i,6,debug); }
            else if( search_map(name,map1W_,it1W) ){ check(it1W_safe()); found=check_indices_1(name,it1W,i,13,debug); }
            else if( search_map(name,map1M_,it1M) ){ check(it1M_safe()); found=check_indices_1(name,it1M,i,7,debug); }
            else if( search_map(name,map1I_,it1I) ){ check(it1I_safe()); found=check_indices_1(name,it1I,i,8,debug); }
            return found;
         }

         /// Search 2-index wrapper maps
         bool find_2index(const std::string& name, const int i, const int j)
         {
            bool found = false;
            #ifdef CHECK_WHERE_FOUND
            std::cout<<"   Searching standard 2-index maps for ("<<name<<","<<i<<","<<j<<")"<<std::endl;
            #endif

            if( search_map(name,map2_,it2) )       { check(it2_safe());  found=check_indices_2(name,it2, i,j,9);  }
            else if( search_map(name,map2W_,it2W) ){ check(it2W_safe()); found=check_indices_2(name,it2W,i,j,14); }
            else if( search_map(name,map2M_,it2M) ){ check(it2M_safe()); found=check_indices_2(name,it2M,i,j,10); }
            else if( search_map(name,map2I_,it2I) ){ check(it2I_safe()); found=check_indices_2(name,it2I,i,j,11); }
            else {
              found = false;
              error_code = 1;
            }

            return found;
         }

         /// @}

         /// Search function for 0-index maps
         bool find(const std::string& name, bool /*doublecheck*/=true, SafeBool check_antiparticle = SafeBool(true))
         {
            bool found = false;
            lastname = name;
            error_code = -2;
            #ifdef CHECK_WHERE_FOUND
            std::cout<<"   Searching all 0-index maps for "<<name<<std::endl;
            #endif

            /// Get antiparticle name if it exists
            /// Slightly wasteful to do this all the time if not needed, but makes the
            /// code simpler and realistically won't make any difference.
            std::string antiname = "none";
            if(check_antiparticle and PDB.has_particle(name) and PDB.has_antiparticle(name))
            {
              antiname = PDB.get_antiparticle(name);
            } else {
              check_antiparticle = SafeBool(false); // No antiparticle PDB entry, so cancel that part of search.
            }

            //  Search override maps first
            if(not found and not no_overrides_)
            {
               if(not found) found = find_override_0index(name);
               if(not found and PDB.has_short_name(name) ) {
                 std::pair<str, int> p = PDB.short_name_pair(name);
                 found = find_override_1index(p.first, p.second);
               }
               if(check_antiparticle) // Check antiparticles
               {
                  if(not found) found = find_override_0index(antiname);
                  if(not found and PDB.has_short_name(antiname) ) {
                    std::pair<str, int> p = PDB.short_name_pair(antiname);
                    found = find_override_1index(p.first, p.second);
                  }
               }
               if(not found) error_code = 1;
            }

            // If no override match, search the wrapper class maps
            if(not found and not override_only_)
            {
               if(not found) found = find_0index(name);
               if(not found and PDB.has_short_name(name) ) {
                 std::pair<str, int> p = PDB.short_name_pair(name);
                 found = find_1index(p.first, p.second);
               }
               if(check_antiparticle) // Check antiparticles
               {
                  if(not found) found = find_0index(antiname);
                  if(not found and PDB.has_short_name(antiname) ) {
                    std::pair<str, int> p = PDB.short_name_pair(antiname);
                    found = find_1index(p.first, p.second);
                  }
               }
               if(not found) error_code = 1;
            }

            #ifdef CHECK_WHERE_FOUND
            std::cout<<"   0-index search result: found="<<found<<std::endl;
            #endif

            if(found) error_code = 0; // Should be no problem!
            return found;
         }

         /// Search function for 1-index maps
         bool find(const std::string& name, int i, bool /*doublecheck*/=true, SafeBool check_antiparticle = SafeBool(true))
         {
            bool found = false;
            lastname = name;
            error_code = -2;
            #ifdef CHECK_WHERE_FOUND
            std::cout<<"   Searching all 1-index maps for ("<<name<<","<<i<<")"<<std::endl;
            #endif

            /// Get antiparticle name if it exists
            std::string antiname = "none";
            int ai = 0;
            if(check_antiparticle and PDB.has_particle(name,i) and PDB.has_antiparticle(name,i))
            {
              std::pair<str,int> p = PDB.get_antiparticle(name,i);
              antiname = p.first;
              ai = p.second;
            } else {
              check_antiparticle = SafeBool(false); // No antiparticle PDB entry, so cancel that part of search.
            }

            //  Search override maps first
            if(not found and not no_overrides_)
            {
               if(not found) found = find_override_1index(name,i);
               if(not found and PDB.has_particle(name,i)) found = find_override_0index(PDB.long_name(name,i));
               if(check_antiparticle) // Check antiparticles
               {
                  if(not found) found = find_override_1index(antiname,ai);
                  if(not found and PDB.has_particle(antiname,i)) found = find_override_0index(PDB.long_name(antiname,ai));
               }
               if(not found) error_code = 1;
            }

            if(not found and not override_only_)
            {
               if(not found) found = find_1index(name,i);
               if(not found and PDB.has_particle(name,i)) found = find_0index(PDB.long_name(name,i));
               if(check_antiparticle) // Check antiparticles
               {
                  if(not found) found = find_1index(antiname,ai);
                  if(not found and PDB.has_particle(antiname,i)) found = find_0index(PDB.long_name(antiname,ai));
               }
               if(not found) error_code = 1;
            }

            #ifdef CHECK_WHERE_FOUND
            std::cout<<"   1-index search result: found="<<found<<std::endl;
            #endif

            if(found) error_code = 0; // Should be no problem!
            return found;
         }

         /// Search function for 2-index maps
         bool find(const std::string& name, int i, int j)
         {
            bool found = false;
            lastname = name;
            error_code = -2;

            // Antiparticle string is a bit tricky here, because it is not
            // well-defined whether the name or a name plus index is needed
            // for the conversion. Better off just banning antiparticle
            // name conversions for two-index cases.

            //  Search maps for function; if found then store it
            if( not no_overrides_ )
            {
              if(not found) found = find_override_2index(name,i,j);
              if(not found) error_code = 1;
            }

            // If no override, search the wrapper class maps
            if(not found and not override_only_)
            {
              if(not found) found = find_2index(name,i,j);
              if(not found) error_code = 1;
            }

            #ifdef CHECK_WHERE_FOUND
            std::cout<<"   2-index search result: found="<<found<<std::endl;
            #endif

            if(found) error_code = 0; // Should be no problem!
            return found;
         }

   }; // end class FptrFinder

   /// Initialise static members of FptrFinder
   template<class HS, class MT> const std::map<std::string,double>                FptrFinder<HS,MT>::nullmap_ito0 = std::map<std::string,double>              (); // 0
   template<class HS, class MT> const std::map<std::string,std::map<int,double>>  FptrFinder<HS,MT>::nullmap_ito1 = std::map<std::string,std::map<int,double>>(); // 1
   template<class HS, class MT> const std::map<std::string,std::map<int,std::map<int,double>>> FptrFinder<HS,MT>::nullmap_ito2 = std::map<std::string,std::map<int,std::map<int,double>>>(); // 2
   /// ...for derived class values
   template<class HS, class MT> const typename MapTypes<typename HS::D,MT>::fmap0        FptrFinder<HS,MT>::nullmap_it0  = typename MapTypes<typename HS::D,MT>::fmap0       (); // 3
   template<class HS, class MT> const typename MapTypes<typename HS::D,MT>::fmap1        FptrFinder<HS,MT>::nullmap_it1  = typename MapTypes<typename HS::D,MT>::fmap1       (); // 6
   template<class HS, class MT> const typename MapTypes<typename HS::D,MT>::fmap2        FptrFinder<HS,MT>::nullmap_it2  = typename MapTypes<typename HS::D,MT>::fmap2       (); // 9 //was 7
   template<class HS, class MT> const typename MapTypes<typename HS::D,MT>::fmap0W       FptrFinder<HS,MT>::nullmap_it0W = typename MapTypes<typename HS::D,MT>::fmap0W      (); // 12
   template<class HS, class MT> const typename MapTypes<typename HS::D,MT>::fmap1W       FptrFinder<HS,MT>::nullmap_it1W = typename MapTypes<typename HS::D,MT>::fmap1W      (); // 13
   template<class HS, class MT> const typename MapTypes<typename HS::D,MT>::fmap2W       FptrFinder<HS,MT>::nullmap_it2W = typename MapTypes<typename HS::D,MT>::fmap2W      (); // 14
   template<class HS, class MT> const typename MapTypes<typename HS::D,MT>::fmap0_extraM FptrFinder<HS,MT>::nullmap_it0M = typename MapTypes<typename HS::D,MT>::fmap0_extraM(); // 4
   template<class HS, class MT> const typename MapTypes<typename HS::D,MT>::fmap1_extraM FptrFinder<HS,MT>::nullmap_it1M = typename MapTypes<typename HS::D,MT>::fmap1_extraM(); // 7
   template<class HS, class MT> const typename MapTypes<typename HS::D,MT>::fmap2_extraM FptrFinder<HS,MT>::nullmap_it2M = typename MapTypes<typename HS::D,MT>::fmap2_extraM(); // 10
   template<class HS, class MT> const typename MapTypes<typename HS::D,MT>::fmap0_extraI FptrFinder<HS,MT>::nullmap_it0I = typename MapTypes<typename HS::D,MT>::fmap0_extraI(); // 5
   template<class HS, class MT> const typename MapTypes<typename HS::D,MT>::fmap1_extraI FptrFinder<HS,MT>::nullmap_it1I = typename MapTypes<typename HS::D,MT>::fmap1_extraI(); // 8
   template<class HS, class MT> const typename MapTypes<typename HS::D,MT>::fmap2_extraI FptrFinder<HS,MT>::nullmap_it2I = typename MapTypes<typename HS::D,MT>::fmap2_extraI(); // 11


   /// Specialisation of CallFcn for calling 'getter' functions
   template<class HostSpec>
   class CallFcn<HostSpec,MapTag::Get>
   {
     private:
      // Model and Input types from wrapper traits class
      typedef typename HostSpec::D DerivedSpec;
      typedef typename SpecTraits<DerivedSpec>::Model Model;
      typedef typename SpecTraits<DerivedSpec>::Input Input;

      typedef MapTypes<DerivedSpec,MapTag::Get> MT;
      FptrFinder<HostSpec,MapTag::Get>* ff;

     public:
      CallFcn(FptrFinder<HostSpec,MapTag::Get>* host)
        : ff(host)
      {}

      double operator()()
      {
         double result(-1); // should not be returned in this state
         if(ff->error_code==0)
         {
            const Model& model = ff->const_fakethis->model();
            const Input& input = ff->const_fakethis->input();
            switch( ff->whichiter )
            {
               // Override retrieval cases
               case 0: {
                 ff->check(ff->ito0_safe());
                 result = ff->ito0->second;
                 break;}
               case 1: {
                 ff->check(ff->ito1_safe());
                 ff->check_index_initd(LOCAL_INFO,ff->index1,"index1");
                 result = (ff->ito1->second).at(ff->index1);
                 break;}
               case 2: {
                 ff->check(ff->ito2_safe());
                 ff->check_index_initd(LOCAL_INFO,ff->index1,"index1");
                 ff->check_index_initd(LOCAL_INFO,ff->index2,"index2");
                 result = (ff->ito2->second).at(ff->index1).at(ff->index2);
                 break;}
               // Wrapper class function call cases
               case 3: {
                 ff->check(ff->it0_safe());
                 typename MT::FSptr f = ff->it0->second;
                 result = (model.*f)();
                 break;}
               case 4: {
                 ff->check(ff->it0M_safe());
                 typename MT::plainfptrM f = ff->it0M->second;
                 result = (*f)(model);
                 break;}
               case 5: {
                 ff->check(ff->it0I_safe());
                 typename MT::plainfptrI f = ff->it0I->second;
                 result = (*f)(input);
                 break;}
               case 6: {
                 ff->check(ff->it1_safe());
                 ff->check_index_initd(LOCAL_INFO,ff->index1,"index1");
                 typename MT::FSptr1 f = ff->it1->second.fptr;
                 result = (model.*f)(ff->index1);
                 break;}
               case 7: {
                 ff->check(ff->it1M_safe());
                 typename MT::plainfptrM1 f = ff->it1M->second.fptr;
                 ff->check_index_initd(LOCAL_INFO,ff->index1,"index1");
                 result = (*f)(model,ff->index1);
                 break;}
               case 8: {
                 ff->check(ff->it1I_safe());
                 typename MT::plainfptrI1 f = ff->it1I->second.fptr;
                 ff->check_index_initd(LOCAL_INFO,ff->index1,"index1");
                 result = (*f)(input,ff->index1);
                 break;}
              case 9: {
                 ff->check(ff->it2_safe());
                 ff->check_index_initd(LOCAL_INFO,ff->index1,"index1");
                 ff->check_index_initd(LOCAL_INFO,ff->index2,"index2");
                 typename MT::FSptr2 f = ff->it2->second.fptr;
                 result = (model.*f)(ff->index1,ff->index2);
                 break;}
               case 10: {
                 ff->check(ff->it2M_safe());
                 ff->check_index_initd(LOCAL_INFO,ff->index1,"index1");
                 ff->check_index_initd(LOCAL_INFO,ff->index2,"index2");
                 typename MT::plainfptrM2 f = ff->it2M->second.fptr;
                 result = (*f)(model,ff->index1,ff->index2);
                 break;}
               case 11: {
                 ff->check(ff->it2I_safe());
                 ff->check_index_initd(LOCAL_INFO,ff->index1,"index1");
                 ff->check_index_initd(LOCAL_INFO,ff->index2,"index2");
                 typename MT::plainfptrI2 f = ff->it2I->second.fptr;
                 result = (*f)(input,ff->index1,ff->index2);
                 break;}
               case 12: {
                 ff->check(ff->it0W_safe());
                 typename MT::FSptrW f = ff->it0W->second;
                 // These are member functions of DerivedSpec, but "HostSpec"
                 // (and therefore the fakethis pointers) is going to be of
                 // type Spec<DerivedSpec>. Therefore need to cast to the
                 // derived type to call the function.
                 const DerivedSpec* wrapper = static_cast<const DerivedSpec*>(ff->const_fakethis);
                 result = (wrapper->*f)();
                 break;}
               case 13: {
                 ff->check(ff->it1W_safe());
                 ff->check_index_initd(LOCAL_INFO,ff->index1,"index1");
                 typename MT::FSptr1W f = ff->it1W->second.fptr;
                 const DerivedSpec* wrapper = static_cast<const DerivedSpec*>(ff->const_fakethis);
                 result = (wrapper->*f)(ff->index1);
                 break;}
               case 14: {
                 ff->check(ff->it2W_safe());
                 ff->check_index_initd(LOCAL_INFO,ff->index1,"index1");
                 ff->check_index_initd(LOCAL_INFO,ff->index2,"index2");
                 typename MT::FSptr2W f = ff->it2W->second.fptr;
                 const DerivedSpec* wrapper = static_cast<const DerivedSpec*>(ff->const_fakethis);
                 result = (wrapper->*f)(ff->index1,ff->index2);
                 break;}
              default:{
                 std::ostringstream errmsg;
                 errmsg << "Error! Unanticipated whichiter code received while trying to call a function from SubSpectrum maps. This indicates a bug in the FptrFinder class. Please report it! (this FptrFinder has label="<<ff->label<<" and is specialised for Getter maps, current error_code="<<ff->error_code<<", whichiter="<<ff->whichiter<<")"<<std::endl;
                 utils_error().forced_throw(LOCAL_INFO,errmsg.str());
                 }
            }
         } else if(ff->error_code==-1)
         {
           std::ostringstream errmsg;
           errmsg << "Error! Tried to call function from SubSpectrum maps without first finding the function! This indicates a bug, probably in the Spectrum or SubSpectrum classes. Please report it! (this FptrFinder has label="<<ff->label<<" and is specialised for Getter maps, current error_code="<<ff->error_code<<")"<<std::endl;
           utils_error().forced_throw(LOCAL_INFO,errmsg.str());
         } else {
           std::ostringstream errmsg;
           errmsg << "Error! Unanticipated error code received while trying to call a function from SubSpectrum maps. This indicates a bug in the FptrFinder class. Please report it! (this FptrFinder has label="<<ff->label<<" and is specialised for Getter maps, current error_code="<<ff->error_code<<")"<<std::endl;
           utils_error().forced_throw(LOCAL_INFO,errmsg.str());
         }
         return result;
      }
   };

   /// Specialisation of CallFcn for calling 'setter' functions
   template<class HostSpec>
   class CallFcn<HostSpec,MapTag::Set>
   {
     private:
      // Model and Input types from wrapper traits class
      typedef typename HostSpec::D DerivedSpec;
      typedef typename SpecTraits<DerivedSpec>::Model Model;
      typedef typename SpecTraits<DerivedSpec>::Input Input;

      typedef MapTypes<DerivedSpec,MapTag::Set> MT;
      FptrFinder<HostSpec,MapTag::Set>* ff;

     public:
      CallFcn(FptrFinder<HostSpec,MapTag::Set>* host)
        : ff(host)
      {}

      void operator()(const double set_value)
      {
         if(ff->error_code==0)
         {
            // Must use NON-const version; make sure pointer correctly initialised!
            if(ff->fakethis==NULL)
            {
               std::ostringstream errmsg;
               errmsg << "Error! 'Setter' version of FptrFinder tried to use non-const 'fakethis' pointer, but the pointer was not initialised! This indicates a bug in the FptrFinder class. Please report it! (this FptrFinder has label="<<ff->label<<" and is specialised for Setter maps, current error_code="<<ff->error_code<<", whichiter="<<ff->whichiter<<")"<<std::endl;
                utils_error().forced_throw(LOCAL_INFO,errmsg.str());
            }
            Model& model = ff->fakethis->model();
            Input& input = ff->fakethis->input();
            switch( ff->whichiter )
            {
               // Override retrieval cases
               // ABSENT ON PURPOSE. set_override functions don't work via an fptrfinder
               case 0:
               case 1:
               case 2: {
                 std::ostringstream errmsg;
                 errmsg << "Error! 'Setter' version of FptrFinder called a map-access case reserved for override maps, however these only work in the 'Getter' version (since SubSpectrum override values are not supposed to be set via an FptrFinder). This indicates a bug in the FptrFinder class. Please report it! (this FptrFinder has label="<<ff->label<<" and is specialised for Setter maps, current error_code="<<ff->error_code<<", whichiter="<<ff->whichiter<<")"<<std::endl;
                 utils_error().forced_throw(LOCAL_INFO,errmsg.str());
                 break;
               }
               // Wrapper class function call cases
               case 3: {
                 ff->check(ff->it0_safe());
                 typename MT::FSptr f = ff->it0->second;
                 (model.*f)(set_value);
                 break;}
               case 4: {
                 ff->check(ff->it0M_safe());
                 typename MT::plainfptrM f = ff->it0M->second;
                 (*f)(model,set_value);
                 break;}
               case 5: {
                 ff->check(ff->it0I_safe());
                 typename MT::plainfptrI f = ff->it0I->second;
                 (*f)(input,set_value);
                 break;}
               case 6: {
                 ff->check(ff->it1_safe());
                 ff->check_index_initd(LOCAL_INFO,ff->index1,"index1");
                 typename MT::FSptr1 f = ff->it1->second.fptr;
                 (model.*f)(set_value,ff->index1);
                 break;}
               case 7: {
                 ff->check(ff->it1M_safe());
                 ff->check_index_initd(LOCAL_INFO,ff->index1,"index1");
                 typename MT::plainfptrM1 f = ff->it1M->second.fptr;
                 (*f)(model,set_value,ff->index1);
                 break;}
               case 8: {
                 ff->check(ff->it1I_safe());
                 ff->check_index_initd(LOCAL_INFO,ff->index1,"index1");
                 typename MT::plainfptrI1 f = ff->it1I->second.fptr;
                 (*f)(input,set_value,ff->index1);
                 break;}
               case 9: {
                 ff->check(ff->it2_safe());
                 ff->check_index_initd(LOCAL_INFO,ff->index1,"index1");
                 ff->check_index_initd(LOCAL_INFO,ff->index2,"index2");
                 typename MT::FSptr2 f = ff->it2->second.fptr;
                 (model.*f)(set_value,ff->index1,ff->index2);
                 break;}
               case 10: {
                 ff->check(ff->it2M_safe());
                 ff->check_index_initd(LOCAL_INFO,ff->index1,"index1");
                 ff->check_index_initd(LOCAL_INFO,ff->index2,"index2");
                 typename MT::plainfptrM2 f = ff->it2M->second.fptr;
                 (*f)(model,set_value,ff->index1,ff->index2);
                 break;}
               case 11: {
                 ff->check(ff->it2I_safe());
                 ff->check_index_initd(LOCAL_INFO,ff->index1,"index1");
                 ff->check_index_initd(LOCAL_INFO,ff->index2,"index2");
                 typename MT::plainfptrI2 f = ff->it2I->second.fptr;
                 (*f)(input,set_value,ff->index1,ff->index2);
                 break;}
               default:{
                 std::ostringstream errmsg;
                 errmsg << "Error! Unanticipated whichiter code received while trying to call a function from SubSpectrum maps. This indicates a bug in the FptrFinder class. Please report it! (this FptrFinder has label="<<ff->label<<" and is specialised for Setter maps, current error_code="<<ff->error_code<<", whichiter="<<ff->whichiter<<")"<<std::endl;
                 utils_error().forced_throw(LOCAL_INFO,errmsg.str());
                 }
            }
         } else if(ff->error_code==-1)
         {
           std::ostringstream errmsg;
           errmsg << "Error! Tried to call function from SubSpectrum maps without first finding the function! This indicates a bug, probably in the Spectrum or SubSpectrum classes. Please report it! (this FptrFinder has label="<<ff->label<<" and is specialised for Getter maps, current error_code="<<ff->error_code<<")"<<std::endl;
           utils_error().forced_throw(LOCAL_INFO,errmsg.str());
         } else {
           std::ostringstream errmsg;
           errmsg << "Error! Unanticipated error code received while trying to call a function from SubSpectrum maps. This indicates a bug in the FptrFinder class. Please report it! (this FptrFinder has label="<<ff->label<<" and is specialised for Getter maps, current error_code="<<ff->error_code<<")"<<std::endl;
           utils_error().forced_throw(LOCAL_INFO,errmsg.str());
         }
      }
   };

}
#undef PDB
#undef CHECK_WHERE_FOUND

#endif
