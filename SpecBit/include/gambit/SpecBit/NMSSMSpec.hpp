//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  NMSSM derived version of SubSpectrum class. Designed
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
    double get_MAh1_pole_slha(const Model& model, int i)
    {
      return model.get_MAh_pole_slha(i+1);
    }

    template <class Model>\
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
    void set_MSu_pole_slha(Model& model, double mass, int i)
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
        tmp_map["ms2"]  = &Model::get_ms2;
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
        tmp_map["vS"]= &Model::get_vS;
        tmp_map["Tlambda"]= &Model::get_Tlambda;
        tmp_map["Tkappa"]= &Model::get_Tkappa;
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
        tmp_map["lambda"]= &Model::get_lambda;
        tmp_map["kappa"]= &Model::get_kappa;
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
        tmp_map["A0"]= Finfo1( &Model::get_MAh1_pole_slha, i01 );
        tmp_map["h0"] =  FInfo1( &Model::get_Mhh_pole_slha, i012 );
        tmp_map["~chi+"] = FInfo1( &Model::get_MCha_pole_slha, i01 );
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

        tmp_map["~d"] =   FInfo2( &Model::get_ZD_pole_slha, i012345, i012345);
        tmp_map["~nu"] =   FInfo2( &Model::get_ZV_pole_slha, i012, i012);
        tmp_map["~u"] =   FInfo2( &Model::get_ZU_pole_slha, i012345, i012345);
        tmp_map["~e-"] =   FInfo2( &Model::get_ZE_pole_slha, i012345, i012345);
        tmp_map["h0"] =   FInfo2( &Model::get_ZH_pole_slha, i012, i012);
        tmp_map["A0"] =   FInfo2( &Model::get_ZA_pole_slha, i012, i012);
        tmp_map["H+"] = FInfo2( &Model::get_ZP_pole_slha, i01, i01);
        tmp_map["~chi0"] =   FInfo2( &Model::get_ZN_pole_slha, i01234, i01234);
        tmp_map["~chi-"] =   FInfo2( &Model::get_UM_pole_slha, i01, i01);
        tmp_map["~chi+"] =   FInfo2( &Model::get_UP_pole_slha, i01, i01);

        map_collection[Par::Pole_Mixing].map2 = tmp_map;
      }
      /// @}


       return map_collection;
    }


    // Filler function for setter function pointer maps
    template <class MI>
    typename NMSSMSpec<MI>::SetterMaps NMSSMSpec<MI>::fill_setter_maps()
    {
      typename NMSSMSpec<MI>::SetterMaps map_collection;
      typedef typename MI::Model Model;

      typedef typename MTset::FInfo2 FInfo2;

      typedef typename MTset::FInfo1M FInfo1M;
      typedef typename MTset::FInfo2M FInfo2M;

      static const std::set<int> i01 = initSet(0,1);
      static const std::set<int> i012 = initSet(0,1,2);
      static const std::set<int> i0123 = initSet(0,1,2,3);
      static const std::set<int> i01234 = initSet(0,1,2,3,4);
      static const std::set<int> i012345 = initSet(0,1,2,3,4,5);

      /// @{ mass2 - mass dimension 2 parameters
      //
      // Functions utilising the "plain-vanilla" function signature
      // (Zero index member functions of model object)
      { // scope so we can reuse the name 'tmp_map' several times, so that our macro works.
        // could make a better macro, or an actual function, but I'm in a hurry
        typename MTget::fmap0 tmp_map;
        tmp_map["BMu"]  = &Model::set_BMu;
        tmp_map["mHd2"] = &Model::set_mHd2;
        tmp_map["mHu2"] = &Model::set_mHu2;
        tmp_map["ms2"]  = &Model::set_ms2;
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
        typename MTget::fmap0 tmp_map;
        tmp_map["M1"]= &Model::set_MassB;
        tmp_map["M2"]= &Model::set_MassWB;
        tmp_map["M3"]= &Model::set_MassG;
        tmp_map["Mu"]= &Model::set_Mu;
        tmp_map["vu"]= &Model::set_vu;
        tmp_map["vd"]= &Model::set_vd;
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
        tmp_map["g1"]= &Model::set_g1;
        tmp_map["g2"]= &Model::set_g2;
        tmp_map["g3"]= &Model::set_g3;
        tmp_map["lambda"]= &Model::set_lambda;
        tmp_map["kappa"]= &Model::set_kappa;
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

      /// @{ Pole_Mass - Pole mass parameters
      // Functions utilising the one-index "plain-vanilla" function signature
      // (One-index member functions of model object)
      {
        typename MTset::fmap0_extraM tmp_map;
        tmp_map["~g"] = &set_MGluino_pole_slha<Model>;
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
        tmp_map["~chi0"] = FInfo1M( &set_MChi_pole_slha<Model>, i01234 );
        tmp_map["A0"] = FInfo1M( &set_MAh1_pole_slha<Model>, i01 );
        tmp_map["h0"] =  FInfo1M( &set_Mhh_pole_slha<Model>, i012 );

        map_collection[Par::Pole_Mass].map1_extraM = tmp_map;
      }

      /// @}

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
        tmp_map["h0"] =   FInfo2M( &set_ZH_pole_slha, i012, i012);
        tmp_map["A0"] =   FInfo2M( &set_ZA_pole_slha, i012, i012);
        tmp_map["H+"] = FInfo2M( &set_ZP_pole_slha, i01, i01);
        tmp_map["~chi0"] =   FInfo2M( &set_ZN_pole_slha, i01234, i01234);
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
