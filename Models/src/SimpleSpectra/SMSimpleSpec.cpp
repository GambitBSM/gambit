//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
//
///  *********************************************
///
///  Authors: 
///  <!-- add name and date if you modify -->
///   
///  \author Ben Farmer
///          (benjamin.farmer@fysik.su.se)
///  \date 2015 Apr 
///
///  *********************************************

#include "gambit/Models/SimpleSpectra/SMSimpleSpec.hpp" 
#include "gambit/Utils/util_functions.hpp" 

#include <boost/preprocessor/tuple/to_seq.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/for_each_product.hpp>

/// Macro to help assign the same function pointers to multiple string keys
// Relies on "tmp_map" being used as the variable name for the temporary maps
// inside the fill_map functions.
#define addtomap_EL(r, PRODUCT)                                         \
{                                                                       \
   str key      = BOOST_PP_SEQ_ELEM(0,PRODUCT); /* string map key */    \
   tmp_map[key] = BOOST_PP_SEQ_ELEM(1,PRODUCT); /* function pointer */  \
}

#define addtomap(__KEYS,FPTR) BOOST_PP_SEQ_FOR_EACH_PRODUCT(addtomap_EL, (BOOST_PP_TUPLE_TO_SEQ(__KEYS))((FPTR)) )

using namespace SLHAea;

namespace Gambit
{

      /// @{ Member functions for SLHAeaModel class
           
      /// Default Constructor
      SMea::SMea() 
        : SLHAeaModel()
      {}

      /// Constructor via SLHAea object
      SMea::SMea(const SLHAea::Coll& slhainput)
        : SLHAeaModel(slhainput)
      {}

      ///// Constructor via SMInputs struct
      //SMea::SMea(const SMInputs& input)
      //{
      //  /// Build an SLHAea object from the SMINPUTS struct        
      //  SLHAeaModel(input)
      //}

      /// @{ Getters for SM information 

      /// Pole masses
      double SMea::get_MZ_pole()        const { return getdata("SMINPUTS",4); }
      double SMea::get_Mtop_pole()      const { return getdata("SMINPUTS",6); }

      // Note, these are actually MSbar masses mb(mb) and mc(mc)
      // However, since this wrapper is very simple, it isn't possible to return
      // these at the same scale as the other running parameters. They can be
      // be considered as approximately pole masses though, so I have allowed
      // to be accessed here. Use as pole masses at own risk.
      double SMea::get_MbMb()           const { return getdata("SMINPUTS",5); }
      double SMea::get_McMc()           const { return getdata("SMINPUTS",24); }

      double SMea::get_Mtau_pole()      const { return getdata("SMINPUTS",7); }
      double SMea::get_Mmuon_pole()     const { return getdata("SMINPUTS",13); }
      double SMea::get_Melectron_pole() const { return getdata("SMINPUTS",11); }

      double SMea::get_Mnu1_pole()      const { return getdata("SMINPUTS",12); }
      double SMea::get_Mnu2_pole()      const { return getdata("SMINPUTS",14); }
      double SMea::get_Mnu3_pole()      const { return getdata("SMINPUTS",8); }

      double SMea::get_MPhoton_pole()   const { return 0.; }
      double SMea::get_MGluon_pole()    const { return 0.; }
      double SMea::get_MPhoton()        const { return 0.; }
      double SMea::get_MGluon()         const { return 0.; }
       
      // In SLHA the W mass is an output, though some spectrum generator authors
      // allow it as a non-standard entry in SMINPUTS. Here we will stick to
      // SLHA.
      double SMea::get_MW_pole()        const { return getdata("MASS",24); }
      double SMea::get_MW_unc()         const { return 0.0; }

      double SMea::get_sinthW2_pole()   const { return (1.0 - Utils::sqr(get_MW_pole()) / Utils::sqr(get_MZ_pole())); }
      
      /// Running masses
      //  Only available for light quarks
      double SMea::get_md() const { return getdata("SMINPUTS",21); }
      double SMea::get_mu() const { return getdata("SMINPUTS",22); }
      double SMea::get_ms() const { return getdata("SMINPUTS",23); }

      double SMea::get_mD(int i) const
      {
        if     (i==1) { return getdata("SMINPUTS",21); }
        else if(i==2) { return getdata("SMINPUTS",23); }
        else if(i==3) { return getdata("SMINPUTS",5); }
        else { utils_error().raise(LOCAL_INFO,"Invalid index input to get_mU! Please check index range limits in wrapper SubSpectrum class!"); return -1; } // Should not return.
      }
   
      double SMea::get_mU(int i) const
      {
        if     (i==1) { return getdata("SMINPUTS",22); }
        else if(i==2) { return getdata("SMINPUTS",24); }
        else if(i==3) { return getdata("SMINPUTS",6); }
        else { utils_error().raise(LOCAL_INFO,"Invalid index input to get_mD! Please check index range limits in wrapper SubSpectrum class!"); return -1; } // Should not return.
      }
   
      double SMea::get_alpha()   const { return 1.0/getdata("SMINPUTS",1); }
      double SMea::get_alphaS()  const { return getdata("SMINPUTS",3); }
 
      // Gauge couplings not provided since they cannot be provided at the same
      // scale. If you want the SLHA definition gauge couplings, you can extract them
      // from the SLHAea object yourself, or use the SMInputs object which comes
      // along with this SubSpectrum inside the parent Spectrum object.
 
      /// @}


      /// @{ Member functions for SMSimpleSpec class

      /// @{ Constructors 
 
      /// Default Constructor
      SMSimpleSpec::SMSimpleSpec() 
      {}

      /// Construct via SLHAea object
      SMSimpleSpec::SMSimpleSpec(const SLHAea::Coll& slhainput)
        : SLHASimpleSpec(slhainput)
      {}

      /// Construct via SMINPUTS object
      SMSimpleSpec::SMSimpleSpec(const SMInputs& sminput)
        : SLHASimpleSpec(sminput.getSLHAea())
      {}

      /// Copy constructor: needed by clone function.
      SMSimpleSpec::SMSimpleSpec(const SMSimpleSpec& other)
        : SLHASimpleSpec(other)
      {} 

      /// @}  
       
      /// Hardcoded to return SLHA2 defined scale of light quark MSbar masses in SMINPUTS block (2 GeV)
      double SMSimpleSpec::GetScale() const { return 2; }
      
      /// @}
      
      // Map fillers

      SMSimpleSpec::GetterMaps SMSimpleSpec::fill_getter_maps()
      {
         GetterMaps map_collection; 

         typedef MTget::FInfo1 FInfo1;

         // Can't use c++11 initialiser lists, se have to initialise the index sets like this.
         static const int i123v[] = {1,2,3};
         static const std::set<int> i123(i123v, Utils::endA(i123v));


         /// Fill for mass1 map 
         {
            MTget::fmap0 tmp_map;

            tmp_map["gamma"] = &SMea::get_MPhoton;
            tmp_map["g"] = &SMea::get_MGluon;

            //tmp_map["u_1"]  = &SMea::get_mu; // u
            //tmp_map["d_1"]  = &SMea::get_md; // d
            //tmp_map["d_2"]  = &SMea::get_ms; // s

            // Nearest flavour 'aliases' for the SM mass eigenstates
            tmp_map["u"]  = &SMea::get_mu; // u
            tmp_map["d"]  = &SMea::get_md; // d
            tmp_map["s"]  = &SMea::get_ms; // s

            tmp_map["e-_3"]= &SMea::get_Mtau_pole; // tau
            tmp_map["e-_2"]= &SMea::get_Mmuon_pole; // mu
            tmp_map["e-_1"]= &SMea::get_Melectron_pole;

            map_collection[Par::mass1].map0 = tmp_map;
         }

         {
            MTget::fmap1 tmp_map;
            tmp_map["d"] =    FInfo1( &Model::get_mD, i123 );
            tmp_map["u"] =    FInfo1( &Model::get_mU, i123 );
            //tmp_map["e-"] =   FInfo1( &Model::get_me, i123456 );

            map_collection[Par::mass1].map1 = tmp_map;
         }

         /// Fill Pole_mass map (from Model object)
         {
            { //local scoping block
              MTget::fmap0 tmp_map;
 
          
              tmp_map["Z0"]  = &SMea::get_MZ_pole;      
              tmp_map["W+"]  = &SMea::get_MW_pole;
              tmp_map["gamma"] = &SMea::get_MPhoton_pole;  
              tmp_map["g"]     = &SMea::get_MGluon_pole;  

              tmp_map["d_3"] = &SMea::get_MbMb; // b
              tmp_map["u_2"] = &SMea::get_McMc; // c
              tmp_map["u_3"] = &SMea::get_Mtop_pole; //t    
              tmp_map["e-_3"]= &SMea::get_Mtau_pole; // tau
              tmp_map["e-_2"]= &SMea::get_Mmuon_pole; // mu
              tmp_map["e-_1"]= &SMea::get_Melectron_pole;
              tmp_map["nu_1"]= &SMea::get_Mnu1_pole;
              tmp_map["nu_2"]= &SMea::get_Mnu2_pole;
              tmp_map["nu_3"]= &SMea::get_Mnu3_pole;
 
              // Nearest flavour 'aliases' for the SM mass eigenstates
              tmp_map["b"]   = &SMea::get_MbMb; // b
              tmp_map["c"]   = &SMea::get_McMc; // c
              tmp_map["t"]   = &SMea::get_Mtop_pole; //t    
              tmp_map["tau-"]= &SMea::get_Mtau_pole; // tau
              tmp_map["mu-"] = &SMea::get_Mmuon_pole; // mu
              tmp_map["e-"]  = &SMea::get_Melectron_pole;
 
   
              map_collection[Par::Pole_Mass].map0 = tmp_map;
            }
           
            { // fill W mass uncertainties
              MTget::fmap0 tmp_map;
              tmp_map["W+"] = &SMea::get_MW_unc;
              map_collection[Par::Pole_Mass_1srd_high].map0 = tmp_map;
            }
                       
            {
              MTget::fmap0 tmp_map;
              tmp_map["W+"] = &SMea::get_MW_unc;
              map_collection[Par::Pole_Mass_1srd_low].map0 = tmp_map;
            }
           

            { //local scoping block
              MTget::fmap0 tmp_map;
  
              tmp_map["sinW2"] = &SMea::get_sinthW2_pole;
  
              map_collection[Par::Pole_Mixing].map0 = tmp_map;
            }

            {
              MTget::fmap0 tmp_map;

              tmp_map["alpha"] = &SMea::get_alpha;
              tmp_map["alphaS"] = &SMea::get_alphaS;

              map_collection[Par::dimensionless].map0 = tmp_map;
            }

         }

         return map_collection;
      }

} // end Gambit namespace


