//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  MSSM derived version of SubSpectrum class. Designed
///  for easy interface to FlexibleSUSY, but also
///  works with SoftSUSY as the backend with an
///  appropriately designed intermediate later.
///
///  *********************************************
///
///  Authors:
///  <!-- add name and date if you modify -->
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2018 Oct
///
///  \author Sanjay Bloor
///          (sanjay.bloor12@imperial.ac.uk)
///  \date 2019 Feb
///
///  *********************************************

#ifndef NMSSMSPEC_H
#define NMSSMSPEC_H

#include <memory>

#include "gambit/Elements/slhaea_helpers.hpp"
//#include "gambit/Elements/mssm_slhahelp.hpp"
#include "gambit/Utils/version.hpp"
#include "gambit/Utils/util_functions.hpp"
#include "gambit/SpecBit/NMSSMSpec_head.hpp"   // "Header" declarations for NMSSMSpec class

namespace Gambit
{

   namespace SpecBit
   {

      template <class MI>
      NMSSMSpec<MI>::NMSSMSpec(MI mi, str be_name, str be_version)
         : backend_name(be_name)
         , backend_version(be_version)
         , model_interface(mi)
      {}

      // Default constructor
      template <class MI>
      NMSSMSpec<MI>::NMSSMSpec()
      {}

      template <class MI>
      NMSSMSpec<MI>::~NMSSMSpec()
      {}

      // Fill an SLHAea object with spectrum information
      // TODO: Check if needs to change for NMSSM
      template <class MI>
      void NMSSMSpec<MI>::add_to_SLHAea(int slha_version, SLHAstruct& slha) const
      {
         std::ostringstream comment;

         // SPINFO block
         // TODO: This needs to become more sophisticated to deal with data potentially
         // produced by different LE and HE spectrum sources. For now whichever subspectrum
         // adds this block first will "win".
         if(not SLHAea_block_exists(slha, "SPINFO"))
         {
            SLHAea_add_block(slha, "SPINFO");
            SLHAea_add(slha, "SPINFO", 1, "GAMBIT, using "+backend_name);
            SLHAea_add(slha, "SPINFO", 2, gambit_version()+" (GAMBIT); "+backend_version+" ("+backend_name+")");
         }
 
         // All other MSSM blocks
         slhahelp::add_MSSM_spectrum_to_SLHAea(*this, slha, slha_version);
      }

      /// @{ Fillers for "Running" parameters

      // Filler function for getter function pointer maps
      template <class MI>
      typename NMSSMSpec<MI>::GetterMaps NMSSMSpec<MI>::fill_getter_maps()
      {
         typename NMSSMSpec<MI>::GetterMaps map_collection;
         typedef typename MI::Model Model;

         typedef typename MTget::FInfo1 FInfo1;
         typedef typename MTget::FInfo2 FInfo2;

         static const std::set<int> i01 = initSet(0,1);
         static const std::set<int> i012 = initSet(0,1,2);
         static const std::set<int> i01234 = initSet(0,1,2,3,4);
         static const std::set<int> i012345 = initSet(0,1,2,3,4,5);

         // Fill the MSSM getter maps
         map_collection = MSSMSpec<MI>::fill_getter_maps();

         /// @{ mass2 - mass dimension 2 parameters
         //
         // Functions utilising the "plain-vanilla" function signature
         // (Zero index member functions of model object)
         {  // scope so we can reuse the name 'tmp_map' several times, so that our macro works.
            // could make a better macro, or an actual function, but I'm in a hurry
            typename MTget::fmap0 tmp_map;
            tmp_map["ms2"]  = &Model::get_ms2;
            map_collection[Par::mass2].map0 = tmp_map;
         }

         /// @}
         /// @{ mass1 - mass dimension 1 parameters
         //
         // Functions utilising the "plain-vanilla" function signature
         // (Zero index member functions of model object)
         {
            typename MTget::fmap0 tmp_map;
            tmp_map["vS"]= &Model::get_vS;
            tmp_map["Tlambda"]= &Model::get_Tlambda;
            tmp_map["Tkappa"]= &Model::get_Tkappa;
            map_collection[Par::mass1].map0 = tmp_map;
         }

         /// @}

         // @{ dimensionless - mass dimension 0 parameters
         //
         // Functions utilising the "plain-vanilla" function signature
         // (Zero index member functions of model object)
         {
            typename MTget::fmap0 tmp_map;
            tmp_map["lambda"]= &Model::get_lambda;
            tmp_map["kappa"]= &Model::get_kappa;
            map_collection[Par::dimensionless].map0 = tmp_map;
         }

         /// @{ Pole_Mass - Pole mass parameters

         // Functions utilising the one-index "plain-vanilla" function signature
         // (One-index member functions of model object)
         {
            typename MTget::fmap1 tmp_map;
            tmp_map["A0"]= Finfo1( &Model::get_MAh_pole_slha, i01 );
            tmp_map["h0"] =  FInfo1( &Model::get_Mhh_pole_slha, i012 );
            tmp_map["~chi0"] = FInfo1( &Model::get_MChi_pole_slha, i01234 );
            map_collection[Par::Pole_Mass].map1 = tmp_map;
         }

         /// @}

         /// @{ Pole_Mixing - Pole mass parameters
         //
         // Functions utilising the two-index "plain-vanilla" function signature
         // (Two-index member functions of model object)
         {
            typename MTget::fmap2 tmp_map;

            tmp_map["h0"] =   FInfo2( &Model::get_ZH_pole_slha, i012, i012);
            tmp_map["A0"] =   FInfo2( &Model::get_ZA_pole_slha, i012, i012);
            tmp_map["~chi0"] =   FInfo2( &Model::get_ZN_pole_slha, i01234, i01234);

            map_collection[Par::Pole_Mixing].map2 = tmp_map;
         }
         /// @}

         return map_collection;
      }

      // Filler function for setter function pointer maps
      template <class MI>
      typename NMSSMSpec<MI>::SetterMaps NMSSMSpec<MI>::fill_setter_maps()
      {
         typename MSSMSpec<MI>::SetterMaps map_collection;
         typedef typename MI::Model Model;

         typedef typename MTset::FInfo2 FInfo2;

         typedef typename MTset::FInfo1M FInfo1M;
         typedef typename MTset::FInfo2M FInfo2M;

         static const std::set<int> i01 = initSet(0,1);
         static const std::set<int> i012 = initSet(0,1,2);
         static const std::set<int> i0123 = initSet(0,1,2,3);
         static const std::set<int> i01234 = initSet(0,1,2,3,4);
         static const std::set<int> i012345 = initSet(0,1,2,3,4,5);

         // Fill the MSSM setter maps
         map_collection = MSSMSpec<MI>::fill_setter_maps();

         /// @{ mass2 - mass dimension 2 parameters
         //
         // Functions utilising the "plain-vanilla" function signature
         // (Zero index member functions of model object)
         {  // scope so we can reuse the name 'tmp_map' several times, so that our macro works.
            // could make a better macro, or an actual function, but I'm in a hurry
            typename MTget::fmap0 tmp_map;
            tmp_map["ms2"]  = &Model::set_ms2;
            map_collection[Par::mass2].map0 = tmp_map;
         }

         /// @}
         /// @{ mass1 - mass dimension 1 parameters
         //
         // Functions utilising the "plain-vanilla" function signature
         // (Zero index member functions of model object)
         {
            typename MTget::fmap0 tmp_map;
            tmp_map["vS"]= &Model::set_vS;
            tmp_map["Tlambda"]= &Model::set_Tlambda;
            tmp_map["Tkappa"]= &Model::set_Tkappa;
            map_collection[Par::mass1].map0 = tmp_map;
         }

         /// @}

         // @{ dimensionless - mass dimension 0 parameters
         //
         // Functions utilising the "plain-vanilla" function signature
         // (Zero index member functions of model object)
         {
            typename MTget::fmap0 tmp_map;
            tmp_map["lambda"]= &Model::set_lambda;
            tmp_map["kappa"]= &Model::set_kappa;
            map_collection[Par::dimensionless].map0 = tmp_map;
         }

         /// @{ Pole_Mass - Pole mass parameters

         // Functions utilising the one-index "plain-vanilla" function signature
         // (One-index member functions of model object)
         {
            typename MTget::fmap1 tmp_map;
            tmp_map["A0"]= Finfo1( &Model::set_MAh_pole_slha, i01 );
            tmp_map["h0"] =  FInfo1( &Model::set_Mhh_pole_slha, i012 );
            tmp_map["~chi0"] = FInfo1( &Model::set_MChi_pole_slha, i01234 );
            map_collection[Par::Pole_Mass].map1 = tmp_map;
         }

         /// @}

         /// @{ Pole_Mixing - Pole mass parameters
         //
         // Functions utilising the two-index "plain-vanilla" function signature
         // (Two-index member functions of model object)
         {
            typename MTget::fmap2 tmp_map;

            tmp_map["h0"] =   FInfo2( &Model::set_ZH_pole_slha, i012, i012);
            tmp_map["A0"] =   FInfo2( &Model::set_ZA_pole_slha, i012, i012);
            tmp_map["~chi0"] =   FInfo2( &Model::set_ZN_pole_slha, i01234, i01234);

            map_collection[Par::Pole_Mixing].map2 = tmp_map;
         }
         /// @}

         return map_collection;
      }

      /// @}


   } // end SpecBit namespace
} // end Gambit namespace

#endif
