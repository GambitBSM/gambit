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
///  \author Peter Athron
///          (peter.athron@coepp.org.au)
///  \date 2014, 2015 Jan, Feb, Mar
///
///  \author Ben Farmer
///          (benjamin.farmer@fysik.su.se)
///  \date 2014, 2015 Jan, Feb, Mar
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2015 Aug
///
///  *********************************************

#ifndef MSSMSPEC_H
#define MSSMSPEC_H

#include <memory>

#include "gambit/Elements/slhaea_spec_helpers.hpp"
#include "gambit/Elements/mssm_slhahelp.hpp"
#include "gambit/Utils/version.hpp"
#include "gambit/Utils/util_functions.hpp"
#include "gambit/SpecBit/MSSMSpec_head.hpp"   // "Header" declarations for MSSMSpec class

// Flexible SUSY stuff (should not be needed by the rest of gambit)
#include "flexiblesusy/config/config.h"

namespace Gambit
{

   namespace SpecBit
   {

      //
      // IMPLEMENTATION OF MSSMSpec MEMBER FUNCTIONS FOLLOWS
      //
      // MSSMSpec this is a template class, we need these definition in the header
      // file. It is nice to keep them seperate from the class declaration though.
      //

      // Set index offset from interface class
      template <class MI>
      const int MSSMSpec<MI>::_index_offset = MI::index_offset;

      // NOTE!! mi is COPIED into the object, so when we get the reference to the
      // actual Model object to store in 'model', we need to use the copy inside
      // the object. So also need to make sure 'model_interface' is initialised first
      // (i.e. it should be declared first)
      template <class MI>
      MSSMSpec<MI>::MSSMSpec(MI mi, str be_name, str be_version)
         : backend_name(be_name)
         , backend_version(be_version)
         , model_interface(mi)
      {}

      // Default constructor
      template <class MI>
      MSSMSpec<MI>::MSSMSpec()
      {}

      template <class MI>
      MSSMSpec<MI>::~MSSMSpec()
      {}

      // Fill an SLHAea object with spectrum information
      template <class MI>
      void MSSMSpec<MI>::add_to_SLHAea(int slha_version, SLHAstruct& slha) const
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

      //inspired by softsusy's lsp method.
      //This MSSM version assumes all states mass ordered.
      //returns lsp mass and gives 3 integers to specify the state
      // for most general case of a particle type with mass matrix
      // row and col set to -1 when not needed
      //(row only is used for vector)
      //particle_type = 0 (neutralino), 1(Sneutrino), 2(up squark),
      //3(down squarks), 4(charged slepton), 5(Chargino), 6(gluino)
      //
      // TODO: Ben: I'm a little unclear why we access the flexiblesusy
      // data directly like this. Can't we use the function pointer maps
      // that we wrote? This will reduce how much the softsusy wrapper
      // has to clone the flexiblesusy model object structure.
      template <class MI>
      double MSSMSpec<MI>::get_lsp_mass(int & particle_type, int & row, int & col) const
      {
         row = -1; col = -1;  particle_type =-1;//set default
         double mlsp = fabs(model_interface.model.get_physical().MChi(0)); //most common lsp
         particle_type = 0;
         row = 0;

         /// sneutrinos 1
         double temp = model_interface.model.get_physical().MSv(0);
         if (temp < mlsp) {
            mlsp = temp;
            particle_type = 1;
            row=0;
         }

         /// up squarks 2
         temp = model_interface.model.get_physical().MSu(0);
         if (temp < mlsp) {
            mlsp = temp;
            particle_type = 2;
            row=0;
         }

         /// down squarks 3
         temp = model_interface.model.get_physical().MSd(0);
         if (temp < mlsp) {
            mlsp = temp;
            particle_type = 3;
            row=0;
         }

         /// sleptons 4
         temp = model_interface.model.get_physical().MSe(0);
         if (temp < mlsp) {
            mlsp = temp;
            particle_type = 4;
            row=0;
         }

         /// charginos 5
         temp = fabs(model_interface.model.get_physical().MCha(0));
         if (temp < mlsp) {
            mlsp = temp;
            particle_type = 5;
            row=0;
         }

         /// gluino 6
         temp = fabs(model_interface.model.get_physical().MGlu);
         if (temp < mlsp) {
            mlsp = temp;
            particle_type = 6;
            row=0;
         }

         //We have no gravitino mass right now.   this should be added.
         // /// gravitino -1
         // temp = displayGravitino();
         // if (temp < mlsp) {
         //   mlsp = temp; posi = 0; posj = 0; particle_type = -1; }

         return mlsp;
      }

      //The MSSM has just one LSP - often the lightest neutralino
      template <class MI>
      int MSSMSpec<MI>::get_numbers_stable_particles() const {
         return 1;
      }

      //these are just wrappers.  Need to test this carefully though
      //inheritance is complicated
      //TODO: Ben: If it helps, we can now put the run_to function
      //in the interface class. Might be similar to what you were
      //already doing for the softsusy interface. Should merge our
      //approaches. Could do all of this via the interface. Depends
      //what will be simplest in general.
      template <class MI>
      void MSSMSpec<MI>::RunToScaleOverride(double scale)
      {
        model_interface.model.run_to(scale);
      }
      template <class MI>
      double MSSMSpec<MI>::GetScale() const
      {
        return model_interface.model.get_scale();
      }
      template <class MI>
      void MSSMSpec<MI>::SetScale(double scale)
      {
        model_interface.model.set_scale(scale);
      }

      template <class MI>
      std::string MSSMSpec<MI>::AccessError(std::string state) const
      {
        std::string errormsg;
        errormsg = "Error accessing "+ state + " element is out of bounds";
        return errormsg;
      }

      // "extra" function to compute TanBeta
      template <class Model>
      double get_tanbeta(const Model& model)
      {
        return model.get_vu() / model.get_vd();
      }

      // "extra" function to compute mA2
      template <class Model>
      double get_DRbar_mA2(const Model& model)
      {
        double tb = model.get_vu() / model.get_vd();
        double cb = cos(atan(tb));
        double sb = sin(atan(tb));
        return model.get_BMu() / (sb * cb);
      }

      template <class Model>
      double get_sinthW2_DRbar(const Model& model)
      {
       double sthW2 = Utils::sqr(model.get_g1()) * 0.6 /
                      (0.6 * Utils::sqr(model.get_g1()) +
                      Utils::sqr(model.get_g2()));
       return sthW2;
      }

      // Need wrapper functions for A0 and H+ getters, to retrieve only the
      // non-Goldstone entries.
      // Need to pass in the model object, since we won't have the 'this' pointer
      template <class Model>
      double get_MAh1_pole_slha(const Model& model)
      {
        return model.get_MAh_pole_slha(1);
      }

      template <class Model>
      double get_MHpm1_pole_slha(const Model& model)
      {
        return model.get_MHpm_pole_slha(1);
      }

     // maybe we will need the goldstones at some point
     // I think it doesn't hurt to add them in case we do
     template <class Model>
      double get_neutral_goldstone_pole_slha(const Model& model)
      {
        return model.get_MAh_pole_slha(0);
      }

      template <class Model>
      double get_charged_goldstone_pole_slha(const Model& model)
      {
        return model.get_MHpm_pole_slha(0);
      }


      template <class Model>
      void set_MSu_pole_slha(Model& model, double mass,int i)
      {
        model.get_physical_slha().MSu(i) = mass;
      }

      template <class Model>
      void set_MSd_pole_slha(Model& model, double mass,int i)
      {
        model.get_physical_slha().MSd(i) = mass;
      }

      template <class Model>
      void set_MSe_pole_slha(Model& model, double mass,int i)
      {
        model.get_physical_slha().MSe(i) = mass;
      }

      template <class Model>
      void set_MSv_pole_slha(Model& model, double mass,int i)
      {
        model.get_physical_slha().MSv(i) = mass;
      }

      template <class Model>
      void set_MCha_pole_slha(Model& model, double mass, int i)
      {
        model.get_physical_slha().MCha(i) = mass;
      }

      template <class Model>
      void set_MChi_pole_slha(Model& model, double mass, int i)
      {
        model.get_physical_slha().MChi(i) = mass;
      }

      template <class Model>
      void set_Mhh_pole_slha(Model& model, double mass, int i)
      {
        model.get_physical_slha().Mhh(i) = mass;
      }

      template <class Model>
      void set_ZD_pole_slha(Model& model, double mass, int i, int j)
      {
        model.get_physical_slha().ZD(i,j) = mass;
      }

      template <class Model>
      void set_ZU_pole_slha(Model& model, double mass, int i, int j)
      {
        model.get_physical_slha().ZU(i,j) = mass;
      }

      template <class Model>
      void set_ZE_pole_slha(Model& model, double mass, int i, int j)
      {
        model.get_physical_slha().ZE(i,j) = mass;
      }

      template <class Model>
      void set_ZV_pole_slha(Model& model, double mass, int i, int j)
      {
        model.get_physical_slha().ZV(i,j) = mass;
      }

      template <class Model>
      void set_ZH_pole_slha(Model& model, double mass, int i, int j)
      {
        model.get_physical_slha().ZH(i,j) = mass;
      }

      template <class Model>
      void set_ZA_pole_slha(Model& model, double mass, int i, int j)
      {
        model.get_physical_slha().ZA(i,j) = mass;
      }

      template <class Model>
      void set_ZP_pole_slha(Model& model, double mass, int i, int j)
      {
        model.get_physical_slha().ZP(i,j) = mass;
      }

      template <class Model>
      void set_ZN_pole_slha(Model& model, double mass, int i, int j)
      {
        model.get_physical_slha().ZN(i,j) = mass;
      }

      template <class Model>
      void set_UM_pole_slha(Model& model, double mass, int i, int j)
      {
        model.get_physical_slha().UM(i,j) = mass;
      }

      template <class Model>
      void set_UP_pole_slha(Model& model, double mass, int i, int j)
      {
        model.get_physical_slha().UP(i,j) = mass;
      }

      template <class Model>
      void set_MAh1_pole_slha(Model& model, double mass)
      {
        model.get_physical_slha().MAh(1) = mass;
      }

      template <class Model>
      void set_MHpm1_pole_slha(Model& model, double mass)
      {
        model.get_physical_slha().MHpm(1) = mass;
      }

      // goldstone setters.  maybe we need these for some consistent calculation
      // unlikely but I'll add them for now.
      template <class Model>
      void set_neutral_goldstone_pole_slha(Model& model, double mass)
      {
        model.get_physical_slha().MAh(0) = mass;
      }

      template <class Model>
      void set_charged_goldstone_pole_slha(Model& model, double mass)
      {
        model.get_physical_slha().MHpm(0) = mass;
      }


     // PA: I'm using nicer names than the FlexibleSUSY ones here
     // but maybe I shouldn't as it breaks the symmetry with the
     // getters and could generate some confusion
     template <class Model>

     void set_MGluino_pole_slha(Model& model, double mass)
     {
        model.get_physical_slha().MGlu = mass;
    }

     //PA:  setting MZ and MW is necessary because we may have them as ouptuts
     template <class Model>
     void set_MZ_pole_slha(Model& model, double mass)
     {
        model.get_physical_slha().MVZ = mass;
     }

     template <class Model>
     void set_MW_pole_slha(Model& model, double mass)
     {
        model.get_physical_slha().MVWm = mass;
     }



      /// @{ Fillers for "Running" parameters

      // Filler function for getter function pointer maps
      template <class MI>
      typename MSSMSpec<MI>::GetterMaps MSSMSpec<MI>::fill_getter_maps()
      {
         typename MSSMSpec<MI>::GetterMaps map_collection;
         typedef typename MI::Model Model;

         typedef typename MTget::FInfo1 FInfo1;
         typedef typename MTget::FInfo2 FInfo2;

         static const std::set<int> i01 = initSet(0,1);
         static const std::set<int> i012 = initSet(0,1,2);
         static const std::set<int> i0123 = initSet(0,1,2,3);
         static const std::set<int> i012345 = initSet(0,1,2,3,4,5);

         /// @{ mass2 - mass dimension 2 parameters
         //
         // Functions utilising the "plain-vanilla" function signature
         // (Zero index member functions of model object)
         {  // scope so we can reuse the name 'tmp_map' several times, so that our macro works.
            // could make a better macro, or an actual function, but I'm in a hurry
            typename MTget::fmap0 tmp_map;
            tmp_map["BMu"]  = &Model::get_BMu;
            tmp_map["mHd2"] = &Model::get_mHd2;
            tmp_map["mHu2"] = &Model::get_mHu2;

            map_collection[Par::mass2].map0 = tmp_map;
         }

         // Functions utilising the "extraM" function signature
         // (Zero index, model object as argument)
         {
            typename MTget::fmap0_extraM tmp_map;
            tmp_map["mA2"] = &get_DRbar_mA2<Model>;
            map_collection[Par::mass2].map0_extraM = tmp_map;
         }

         // functions utilising the two-index "plain-vanilla" function signature
         // (two-index member functions of model object)
         {
            typename MTget::fmap2 tmp_map;
            tmp_map["mq2"] = FInfo2( &Model::get_mq2, i012, i012);
            tmp_map["ml2"] = FInfo2( &Model::get_ml2, i012, i012);
            tmp_map["md2"] = FInfo2( &Model::get_md2, i012, i012);
            tmp_map["mu2"] = FInfo2( &Model::get_mu2, i012, i012);
            tmp_map["me2"] = FInfo2( &Model::get_me2, i012, i012);

            map_collection[Par::mass2].map2 = tmp_map;
         }

         /// @}
         /// @{ mass1 - mass dimension 1 parameters
         //
         // Functions utilising the "plain-vanilla" function signature
         // (Zero index member functions of model object)
         {
            typename MTget::fmap0 tmp_map;
            tmp_map["M1"]= &Model::get_MassB;
            tmp_map["M2"]= &Model::get_MassWB;
            tmp_map["M3"]= &Model::get_MassG;
            tmp_map["Mu"]= &Model::get_Mu;
            tmp_map["vu"]= &Model::get_vu;
            tmp_map["vd"]= &Model::get_vd;

            map_collection[Par::mass1].map0 = tmp_map;
         }

         // Functions utilising the two-index "plain-vanilla" function signature
         // (Two-index member functions of model object)
         {
            typename MTget::fmap2 tmp_map;
            tmp_map["TYd"]= FInfo2( &Model::get_TYd, i012, i012);
            tmp_map["TYe"]= FInfo2( &Model::get_TYe, i012, i012);
            tmp_map["TYu"]= FInfo2( &Model::get_TYu, i012, i012);
            tmp_map["ad"] = FInfo2( &Model::get_TYd, i012, i012);
            tmp_map["ae"] = FInfo2( &Model::get_TYe, i012, i012);
            tmp_map["au"] = FInfo2( &Model::get_TYu, i012, i012);

            map_collection[Par::mass1].map2 = tmp_map;
         }

         /// @}

         // @{ dimensionless - mass dimension 0 parameters
         //
         // Functions utilising the "plain-vanilla" function signature
         // (Zero index member functions of model object)
         {
            typename MTget::fmap0 tmp_map;
            tmp_map["g1"]= &Model::get_g1;
            tmp_map["g2"]= &Model::get_g2;
            tmp_map["g3"]= &Model::get_g3;

            map_collection[Par::dimensionless].map0 = tmp_map;
         }

         // Functions utilising the "extraM" function signature
         // (Zero index, model object as argument)
         {
            typename MTget::fmap0_extraM tmp_map;
            tmp_map["tanbeta"] = &get_tanbeta<Model>;
            tmp_map["sinW2"] = &get_sinthW2_DRbar<Model>;
            map_collection[Par::dimensionless].map0_extraM = tmp_map;
         }

         // Functions utilising the two-index "plain-vanilla" function signature
         // (Two-index member functions of model object)
         {
            typename MTget::fmap2 tmp_map;

            tmp_map["Yd"]= FInfo2( &Model::get_Yd, i012, i012);
            tmp_map["Yu"]= FInfo2( &Model::get_Yu, i012, i012);
            tmp_map["Ye"]= FInfo2( &Model::get_Ye, i012, i012);

            map_collection[Par::dimensionless].map2 = tmp_map;
         }
         /// @}

         /// @{ Pole_Mass - Pole mass parameters
         //
         // Functions utilising the "plain-vanilla" function signature
         // (Zero index member functions of model object)
         {
            typename MTget::fmap0 tmp_map;

	    /// PA: W mass is a prediction in most spectrum generators
	    /// so we need this.  One tricky question is how to interface
	    /// spectrum generators which have different input / outputs
	    /// *may* be ok to still mimic the FS way
            tmp_map["W+"] = &Model::get_MVWm_pole_slha;
            tmp_map["~g"] = &Model::get_MGlu_pole_slha;

            map_collection[Par::Pole_Mass].map0 = tmp_map;
         }

         // Functions utilising the "extraM" function signature
         // (Zero index, model object as argument)
         {
            typename MTget::fmap0_extraM tmp_map;

            // Using wrapper functions defined above
            tmp_map["A0"] = &get_MAh1_pole_slha<Model>;
            tmp_map["H+"] = &get_MHpm1_pole_slha<Model>;

            // Goldstones
            // Using wrapper functions defined above
            tmp_map["Goldstone0"] = &get_neutral_goldstone_pole_slha<Model>;
            tmp_map["Goldstone+"] = &get_charged_goldstone_pole_slha<Model>;
            // Antiparticle label (no automatic conversion for this)
            tmp_map["Goldstone-"] = &get_charged_goldstone_pole_slha<Model>;

            map_collection[Par::Pole_Mass].map0_extraM = tmp_map;
         }

         // Functions utilising the one-index "plain-vanilla" function signature
         // (One-index member functions of model object)
         {
            typename MTget::fmap1 tmp_map;

            tmp_map["~d"] =  FInfo1( &Model::get_MSd_pole_slha, i012345 );
            tmp_map["~u"] =  FInfo1( &Model::get_MSu_pole_slha, i012345 );
            tmp_map["~e-"] = FInfo1( &Model::get_MSe_pole_slha, i012345 );
            tmp_map["~nu"]=  FInfo1( &Model::get_MSv_pole_slha, i012 );
            tmp_map["h0"] =  FInfo1( &Model::get_Mhh_pole_slha, i01 );
            tmp_map["A0"] =  FInfo1( &Model::get_MAh_pole_slha, i01 );
            tmp_map["~chi+"] = FInfo1( &Model::get_MCha_pole_slha, i01 );
            tmp_map["~chi0"] = FInfo1( &Model::get_MChi_pole_slha, i0123 );

            map_collection[Par::Pole_Mass].map1 = tmp_map;
         }

         /// @}

         /// @{ Pole_Mixing - Pole mass parameters
         //
         // Functions utilising the two-index "plain-vanilla" function signature
         // (Two-index member functions of model object)
         {
            typename MTget::fmap2 tmp_map;

            tmp_map["~d"] =   FInfo2( &Model::get_ZD_pole_slha, i012345, i012345);
            tmp_map["~nu"] =   FInfo2( &Model::get_ZV_pole_slha, i012, i012);
            tmp_map["~u"] =   FInfo2( &Model::get_ZU_pole_slha, i012345, i012345);
            tmp_map["~e-"] =   FInfo2( &Model::get_ZE_pole_slha, i012345, i012345);
            tmp_map["h0"] =   FInfo2( &Model::get_ZH_pole_slha, i01, i01);
            tmp_map["A0"] =   FInfo2( &Model::get_ZA_pole_slha, i01, i01);
            tmp_map["H+"] = FInfo2( &Model::get_ZP_pole_slha, i01, i01);
            tmp_map["~chi0"] =   FInfo2( &Model::get_ZN_pole_slha, i0123, i0123);
            tmp_map["~chi-"] =   FInfo2( &Model::get_UM_pole_slha, i01, i01);
            tmp_map["~chi+"] =   FInfo2( &Model::get_UP_pole_slha, i01, i01);

            map_collection[Par::Pole_Mixing].map2 = tmp_map;
         }
         /// @}

         return map_collection;
      }

      // Filler function for setter function pointer maps
      template <class MI>
      typename MSSMSpec<MI>::SetterMaps MSSMSpec<MI>::fill_setter_maps()
      {
         typename MSSMSpec<MI>::SetterMaps map_collection;
         typedef typename MI::Model Model;

         typedef typename MTset::FInfo2 FInfo2;

         typedef typename MTset::FInfo1M FInfo1M;
         typedef typename MTset::FInfo2M FInfo2M;

         static const std::set<int> i01 = initSet(0,1);
         static const std::set<int> i012 = initSet(0,1,2);
         static const std::set<int> i0123 = initSet(0,1,2,3);
         static const std::set<int> i012345 = initSet(0,1,2,3,4,5);

         /// @{ mass2 - mass dimension 2 parameters
         //
         // Functions utilising the "plain-vanilla" function signature
         // (Zero index member functions of model object)
         {  // scope so we can reuse the name 'tmp_map' several times, so that our macro works.
            // could make a better macro, or an actual function, but I'm in a hurry
            typename MTset::fmap0 tmp_map;
            tmp_map["BMu"]  = &Model::set_BMu;
            tmp_map["mHd2"] = &Model::set_mHd2;
            tmp_map["mHu2"] = &Model::set_mHu2;

            map_collection[Par::mass2].map0 = tmp_map;
         }

         // Functions utilising the two-index "plain-vanilla" function signature
         // (Two-index member functions of model object)
         {
            typename MTset::fmap2 tmp_map;
            tmp_map["mq2"] = FInfo2( &Model::set_mq2, i012, i012);
            tmp_map["ml2"] = FInfo2( &Model::set_ml2, i012, i012);
            tmp_map["md2"] = FInfo2( &Model::set_md2, i012, i012);
            tmp_map["mu2"] = FInfo2( &Model::set_mu2, i012, i012);
            tmp_map["me2"] = FInfo2( &Model::set_me2, i012, i012);

            map_collection[Par::mass2].map2 = tmp_map;
         }
         /// @}

         /// @{ mass1 - mass dimension 1 parameters
         //
         // Functions utilising the "plain-vanilla" function signature
         // (Zero index member functions of model object)
         {
            typename MTset::fmap0 tmp_map;
            tmp_map["M1"]= &Model::set_MassB;
            tmp_map["M2"]= &Model::set_MassWB;
            tmp_map["M3"]= &Model::set_MassG;
            tmp_map["Mu"]= &Model::set_Mu;
            tmp_map["vu"]= &Model::set_vu;
            tmp_map["vd"]= &Model::set_vd;

            map_collection[Par::mass1].map0 = tmp_map;
         }

         // Functions utilising the two-index "plain-vanilla" function signature
         // (Two-index member functions of model object)
         {
            typename MTset::fmap2 tmp_map;
            tmp_map["TYd"]= FInfo2( &Model::set_TYd, i012, i012);
            tmp_map["TYe"]= FInfo2( &Model::set_TYe, i012, i012);
            tmp_map["TYu"]= FInfo2( &Model::set_TYu, i012, i012);
            tmp_map["ad"] = FInfo2( &Model::set_TYd, i012, i012);
            tmp_map["ae"] = FInfo2( &Model::set_TYe, i012, i012);
            tmp_map["au"] = FInfo2( &Model::set_TYu, i012, i012);

            map_collection[Par::mass1].map2 = tmp_map;
         }

         /// @}

         // @{ dimensionless - mass dimension 0 parameters
         //
         // Functions utilising the "plain-vanilla" function signature
         // (Zero index member functions of model object)
         {
            typename MTset::fmap0 tmp_map;
            tmp_map["g1"]= &Model::set_g1;
            tmp_map["g2"]= &Model::set_g2;
            tmp_map["g3"]= &Model::set_g3;

            map_collection[Par::dimensionless].map0 = tmp_map;
         }

         // Functions utilising the two-index "plain-vanilla" function signature
         // (Two-index member functions of model object)
         {
            typename MTset::fmap2 tmp_map;

            tmp_map["Yd"]= FInfo2( &Model::set_Yd, i012, i012);
            tmp_map["Yu"]= FInfo2( &Model::set_Yu, i012, i012);
            tmp_map["Ye"]= FInfo2( &Model::set_Ye, i012, i012);

            map_collection[Par::dimensionless].map2 = tmp_map;
         }

        {
          typename MTset::fmap0_extraM tmp_map;
          tmp_map["~g"] = &set_MGluino_pole_slha<Model>;
          tmp_map["A0"] = &set_MAh1_pole_slha<Model>;
          tmp_map["H+"] = &set_MHpm1_pole_slha<Model>;
          /// Note; these aren't in the particle database, so no
          /// conversion between particle/antiparticle.
          tmp_map["Goldstone0"] = &set_neutral_goldstone_pole_slha<Model>;
          tmp_map["Goldstone+"] = &set_charged_goldstone_pole_slha<Model>;
          tmp_map["Goldstone-"] = &set_charged_goldstone_pole_slha<Model>;

          /// PA: MW is a prediction in FS and most spectrum generators
	  /// so this belongs in the HE object.
	  /// MZ is not and so belongs in LE object
          tmp_map["W+"] = &set_MW_pole_slha<Model>;

          map_collection[Par::Pole_Mass].map0_extraM = tmp_map;
        }

        {
          typename MTset::fmap1_extraM tmp_map;

          tmp_map["~u"] = FInfo1M( &set_MSu_pole_slha<Model>, i012345 );
          tmp_map["~d"] = FInfo1M( &set_MSd_pole_slha<Model>, i012345 );
          tmp_map["~e-"]= FInfo1M( &set_MSe_pole_slha<Model>, i012345 );

          tmp_map["~nu"]=  FInfo1M( &set_MSv_pole_slha<Model>, i012 );
          tmp_map["~chi+"] = FInfo1M( &set_MCha_pole_slha<Model>, i01 );
          tmp_map["~chi0"] = FInfo1M( &set_MChi_pole_slha<Model>, i0123 );
          tmp_map["h0"] =  FInfo1M( &set_Mhh_pole_slha<Model>, i01 );

          map_collection[Par::Pole_Mass].map1_extraM = tmp_map;
        }


        /// @{ Pole_Mixing - Pole mass parameters
        //
        // Functions utilising the two-index "plain-vanilla" function signature
        // (Two-index member functions of model object)
        {
          typename MTset::fmap2_extraM tmp_map;

          tmp_map["~d"] =   FInfo2M( &set_ZD_pole_slha, i012345, i012345);
          tmp_map["~nu"] =   FInfo2M( &set_ZV_pole_slha, i012, i012);
          tmp_map["~u"] =   FInfo2M( &set_ZU_pole_slha, i012345, i012345);
          tmp_map["~e-"] =   FInfo2M( &set_ZE_pole_slha, i012345, i012345);
          tmp_map["h0"] =   FInfo2M( &set_ZH_pole_slha, i01, i01);
          tmp_map["A0"] =   FInfo2M( &set_ZA_pole_slha, i01, i01);
          tmp_map["H+"] = FInfo2M( &set_ZP_pole_slha, i01, i01);
          tmp_map["~chi0"] =   FInfo2M( &set_ZN_pole_slha, i0123, i0123);
          tmp_map["~chi-"] =   FInfo2M( &set_UM_pole_slha, i01, i01);
          tmp_map["~chi+"] =   FInfo2M( &set_UP_pole_slha, i01, i01);

          map_collection[Par::Pole_Mixing].map2_extraM = tmp_map;
        }


         return map_collection;
      }

      /// @}


   } // end SpecBit namespace
} // end Gambit namespace

#endif
