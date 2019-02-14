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
///  \author Filip Rajec
///          (filip.rajec@adelaide.edu.au)
///  \date 2019 Feb 
///
///  *********************************************

#include "gambit/Models/SimpleSpectra/THDMSimpleSpec.hpp" 
#include "gambit/Elements/thdm_slhahelp.hpp"
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
      THDMea::THDMea() 
        : SLHAeaModel()
      {}

      /// Constructor via SLHAea object
      THDMea::THDMea(const SLHAea::Coll& slhainput)
        : SLHAeaModel(slhainput)
      {}

      ///// Constructor via SMInputs struct
      //THDMea::THDMea(const THDMInputs& input)
      //{
      //  /// Build an SLHAea object from the SMINPUTS struct        
      //  SLHAeaModel(input)
      //}

      /// @{ Getters for SM information 

      /// Pole masses
      double THDMea::get_MZ_pole()        const { return getdata("SMINPUTS",4); }
      double THDMea::get_Mtop_pole()      const { return getdata("SMINPUTS",6); }

      // Note, these are actually MSbar masses mb(mb) and mc(mc)
      // However, since this wrapper is very simple, it isn't possible to return
      // these at the same scale as the other running parameters. They can be
      // be considered as approximately pole masses though, so I have allowed
      // to be accessed here. Use as pole masses at own risk.
      double THDMea::get_MbMb()           const { return getdata("SMINPUTS",5); }
      double THDMea::get_McMc()           const { return getdata("SMINPUTS",24); }

      double THDMea::get_Mtau_pole()      const { return getdata("SMINPUTS",7); }
      double THDMea::get_Mmuon_pole()     const { return getdata("SMINPUTS",13); }
      double THDMea::get_Melectron_pole() const { return getdata("SMINPUTS",11); }

      double THDMea::get_Mnu1_pole()      const { return getdata("SMINPUTS",12); }
      double THDMea::get_Mnu2_pole()      const { return getdata("SMINPUTS",14); }
      double THDMea::get_Mnu3_pole()      const { return getdata("SMINPUTS",8); }

      double THDMea::get_MPhoton_pole()   const { return 0.; }
      double THDMea::get_MGluon_pole()    const { return 0.; }
       
      // In SLHA the W mass is an output, though some spectrum generator authors
      // allow it as a non-standard entry in SMINPUTS. Here we will stick to
      // SLHA.
      double THDMea::get_MW_pole()        const { return getdata("MASS",24); }
      double THDMea::get_MW_unc()         const { return 0.0; }

      double THDMea::get_sinthW2_pole()   const { return (1.0 - Utils::sqr(get_MW_pole()) / Utils::sqr(get_MZ_pole())); }
      
      /// Running masses
      //  Only available for light quarks
      double THDMea::get_md() const { return getdata("SMINPUTS",21); }
      double THDMea::get_mu() const { return getdata("SMINPUTS",22); }
      double THDMea::get_ms() const { return getdata("SMINPUTS",23); }

        double THDMea::get_vev()      const { return 247.0; } 
        double THDMea::get_g1()       const { return getdata("GAUGE",1); }
        double THDMea::get_g2()       const { return getdata("GAUGE",1); }
        double THDMea::get_g3()       const { return getdata("GAUGE",1); }
        double THDMea::get_sinW2()    const { return (0.5 - pow( 0.25 - (1.0/getdata("SMINPUTS",1) * M_PI / (getdata("SMINPUTS",2) * pow(2,0.5)))/pow(getdata("SMINPUTS",4),2) , 0.5)); }

        double THDMea::get_Yd(int i, int j) const { return getdata("Yd",i,j); }
        double THDMea::get_Yu(int i, int j) const { return getdata("Yu",i,j); }
        double THDMea::get_Ye(int i, int j) const { return getdata("Ye",i,j); }
        
        double THDMea::get_mh0(int i)       const {
                                                if      (i==0){ getdata("MASS",25); } // Neutral Higgs(1)
                                                else if (i==1){ getdata("MASS",35); } // Neutral Higgs(2)
                                                else { utils_error().raise(LOCAL_INFO,"Invalid index input to get_mh0! Please check index range limits in wrapper SubSpectrum class!"); return -1; } // Should not return.
                                            }
        double THDMea::get_mA0()                const { return getdata("MASS",36); }
        double THDMea::get_mC()                 const { return getdata("MASS",37); }
        double THDMea::get_tanb()               const { return getdata("MINPAR",3); }
        double THDMea::get_alpha()              const { return getdata("ALPHA",0); }
        double THDMea::get_m12_2()              const { return getdata("MINPAR",18); }
        double THDMea::get_lambda6()            const { return getdata("MINPAR",16); }
        double THDMea::get_lambda7()            const { return getdata("MINPAR",17); }
        double THDMea::get_yukawaCoupling()     const { return (getdata("FMODSEL",1) - 30); }
        double THDMea::get_lambda1()            const { return getdata("MINPAR",11); }
        double THDMea::get_lambda2()            const { return getdata("MINPAR",12); }
        double THDMea::get_lambda3()            const { return getdata("MINPAR",13); }
        double THDMea::get_lambda4()            const { return getdata("MINPAR",14); }
        double THDMea::get_lambda5()            const { return getdata("MINPAR",15); }
        // double THDMea::get_sinthW2_DRbar()      const {
        //                                     double sg1 = 0.6 * Utils::sqr(get_g1());
        //                                     return sg1 / (sg1 + Utils::sqr(get_g2()));
        //                                     }
 
      /// @}


      /// @{ Member functions for THDMSimpleSpec class

      /// @{ Constructors 
 
      /// Default Constructor
      THDMSimpleSpec::THDMSimpleSpec() 
      {}

      /// Construct via SLHAea object
      THDMSimpleSpec::THDMSimpleSpec(const SLHAea::Coll& slhainput)
        : SLHASimpleSpec(slhainput)
      {}

      /// Construct via SMINPUTS object
    //   THDMSimpleSpec::THDMSimpleSpec(const SMnputs& sminput)
    //     : SLHASimpleSpec(sminput.getSLHAea())
    //   {}

      /// Copy constructor: needed by clone function.
      THDMSimpleSpec::THDMSimpleSpec(const THDMSimpleSpec& other)
        : SLHASimpleSpec(other)
      {} 

      /// @}  
       
      /// Hardcoded to return SLHA2 defined scale of light quark MSbar masses in SMINPUTS block (2 GeV)
      double THDMSimpleSpec::GetScale() const { return 2; }
      
      /// @}
      
      // Map fillers

      THDMSimpleSpec::GetterMaps THDMSimpleSpec::fill_getter_maps()
      {

            GetterMaps map_collection; 

            typedef MTget::FInfo1 FInfo1;
            typedef MTget::FInfo2 FInfo2;

            static const int i12v[] = {0,1};
            static const std::set<int> i12(i12v, Utils::endA(i12v));

            static const int i012v[] = {0,1,2};
            static const std::set<int> i012(i012v, Utils::endA(i012v));

         /// Fill for mass1 map 
         {
            MTget::fmap0 tmp_map;

            tmp_map["u_1"]  = &THDMea::get_mu; // u
            tmp_map["d_1"]  = &THDMea::get_md; // d
            tmp_map["d_2"]  = &THDMea::get_ms; // s

            // Nearest flavour 'aliases' for the THDM mass eigenstates
            tmp_map["u"]  = &THDMea::get_mu; // u
            tmp_map["d"]  = &THDMea::get_md; // d
            tmp_map["s"]  = &THDMea::get_ms; // s

            // vev
            tmp_map["vev"]  = &THDMea::get_vev;

            // THDM potential parameters
            tmp_map["lambda_1"]  = &THDMea::get_lambda1;
            tmp_map["lambda_2"]  = &THDMea::get_lambda2;
            tmp_map["lambda_3"]  = &THDMea::get_lambda3;
            tmp_map["lambda_4"]  = &THDMea::get_lambda4;
            tmp_map["lambda_5"]  = &THDMea::get_lambda5;
            tmp_map["lambda_6"]  = &THDMea::get_lambda6;
            tmp_map["lambda_7"]  = &THDMea::get_lambda7;
            tmp_map["m12_2"]  = &THDMea::get_m12_2;

            map_collection[Par::mass1].map0 = tmp_map;
         }

         /// Fill Pole_mass map (from Model object)
         {
            { //local scoping block
              MTget::fmap0 tmp_map;
 
          
              tmp_map["Z0"]  = &THDMea::get_MZ_pole;      
              tmp_map["W+"]  = &THDMea::get_MW_pole;
              tmp_map["gamma"] = &THDMea::get_MPhoton_pole;  
              tmp_map["g"]     = &THDMea::get_MGluon_pole;  

              tmp_map["d_3"] = &THDMea::get_MbMb; // b
              tmp_map["u_2"] = &THDMea::get_McMc; // c
              tmp_map["u_3"] = &THDMea::get_Mtop_pole; //t    
              tmp_map["e-_3"]= &THDMea::get_Mtau_pole; // tau
              tmp_map["e-_2"]= &THDMea::get_Mmuon_pole; // mu
              tmp_map["e-_1"]= &THDMea::get_Melectron_pole;
              tmp_map["nu_1"]= &THDMea::get_Mnu1_pole;
              tmp_map["nu_2"]= &THDMea::get_Mnu2_pole;
              tmp_map["nu_3"]= &THDMea::get_Mnu3_pole;
 
              // Nearest flavour 'aliases' for the THDM mass eigenstates
              tmp_map["b"]   = &THDMea::get_MbMb; // b
              tmp_map["c"]   = &THDMea::get_McMc; // c
              tmp_map["t"]   = &THDMea::get_Mtop_pole; //t    
              tmp_map["tau-"]= &THDMea::get_Mtau_pole; // tau
              tmp_map["mu-"] = &THDMea::get_Mmuon_pole; // mu
              tmp_map["e-"]  = &THDMea::get_Melectron_pole;

              // THDM Extra Scalar Pole Masses
              tmp_map["A0"]= &THDMea::get_mA0;
              tmp_map["H+"] = &THDMea::get_mC;
              tmp_map["H-"]  = &THDMea::get_mC;

              map_collection[Par::Pole_Mass].map0 = tmp_map;
            }

            { // THDM Scalar Higgs Pole Mass
              MTget::fmap1 tmp_map;
              tmp_map["h0"]   = FInfo1( &THDMea::get_mh0, i12 );

              map_collection[Par::Pole_Mass].map1 = tmp_map;
            }
           
            { // fill W mass uncertainties
              MTget::fmap0 tmp_map;
              tmp_map["W+"] = &THDMea::get_MW_unc;
              map_collection[Par::Pole_Mass_1srd_high].map0 = tmp_map;
            }
                       
            {
              MTget::fmap0 tmp_map;
              tmp_map["W+"] = &THDMea::get_MW_unc;
              map_collection[Par::Pole_Mass_1srd_low].map0 = tmp_map;
            }
           

            { //local scoping block
              MTget::fmap0 tmp_map;
  
              tmp_map["sinW2"] = &THDMea::get_sinthW2_pole;
  
              map_collection[Par::Pole_Mixing].map0 = tmp_map;
            }

            { // Gauge couplings block
              MTget::fmap0 tmp_map;
              tmp_map["g1"]   = &THDMea::get_g1;
              tmp_map["g2"]   = &THDMea::get_g2;
              tmp_map["g3"]   = &THDMea::get_g3;

                map_collection[Par::dimensionless].map0 = tmp_map;
            }

            { // Yukawas block
              MTget::fmap2 tmp_map;
              tmp_map["Yu"]   = FInfo2( &THDMea::get_Yu, i012, i012);
              tmp_map["Yd"]   = FInfo2( &THDMea::get_Yd, i012, i012);
              tmp_map["Ye"]   = FInfo2( &THDMea::get_Ye, i012, i012);

              map_collection[Par::dimensionless].map2 = tmp_map;
            }

         }

         return map_collection;
      }

} // end Gambit namespace


