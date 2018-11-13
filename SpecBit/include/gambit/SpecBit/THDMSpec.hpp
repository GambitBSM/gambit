//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  THDM derived version of SubSpectrum class.
///
///  *********************************************
///
///  Authors:
///  <!-- add name and date if you modify -->
///
///  \author James McKay
///          (j.mckay14@imperial.ac.uk)
///  \date 2016 Oct
///
///  -modified:
///   Filip Rajec
///   Feb 2017
///
///  *********************************************

#ifndef THDMSPEC_H
#define THDMSPEC_H

#include <memory>

#include "gambit/cmake/cmake_variables.hpp"
#include "gambit/Elements/subspectrum.hpp"
#include "gambit/Elements/slhaea_helpers.hpp"
#include "gambit/Utils/util_functions.hpp"
#include "gambit/SpecBit/THDMSpec_head.hpp"

// Flexible SUSY stuff (should not be needed by the rest of gambit)
#include "flexiblesusy/config/config.h"


namespace Gambit
{


   namespace SpecBit
   {
      template <class MI>
      const int THDMSpec<MI>::_index_offset = MI::index_offset;

      // NOTE!! mi is COPIED into the object, so when we get the reference to the
      // actual Model object to store in 'model', we need to use the copy inside
      // the object. So also need to make sure 'model_interface' is initialised first
      // (i.e. it should be declared first)
      template <class MI>
      THDMSpec<MI>::THDMSpec(MI mi, str be_name, str be_version)
         : backend_name(be_name)
         , backend_version(be_version)
         , model_interface(mi)
      {}


      template <class MI>
      THDMSpec<MI>::THDMSpec()
      {}

      template <class MI>
      THDMSpec<MI>::~THDMSpec()
      {}



      template <class MI>
      void THDMSpec<MI>::RunToScaleOverride(double scale)
      {
          // std::cout << "THDMSpec.hpp | RunToScaleOverride() | BEFORE run_to(scale) " << std::endl;
        try {
          model_interface.model.run_to(scale);
        }
        catch(...){
          invalid_point().raise("FS Invalid Point: RunToScale Failed");
          //TODO: Terminal message here
        }
          // std::cout << "THDMSpec.hpp | RunToScaleOverride() | BEFORE calculate_DRbar_masses() " << std::endl;
        model_interface.model.calculate_DRbar_masses();
          // std::cout << "THDMSpec.hpp | RunToScaleOverride() | END" << std::endl;

      }
      template <class MI>
      double THDMSpec<MI>::GetScale() const
      {
        return model_interface.model.get_scale();
      }


      template <class MI>
      void THDMSpec<MI>::SetScale(double scale)
      {
        model_interface.model.set_scale(scale);
      }

      template <class MI>
      std::string THDMSpec<MI>::AccessError(std::string state) const
      {
        std::string errormsg;
        errormsg = "Error accessing "+ state + " element is out of bounds";
        return errormsg;
      }

      template <class Model>
      double get_sinthW2_MSbar(const Model& model)
      {
       double sthW2 = Utils::sqr(model.get_g1()) * 0.6 /
                      (0.6 * Utils::sqr(model.get_g1()) +
                      Utils::sqr(model.get_g2()));
       return sthW2;
      }

      // "extra" function to compute TanBeta 
      template <class Model>
      double get_tanb(const Model& model)
      {
        // this needs implementation!!
        //return model.get_tanb();
        return model.get_v2()/model.get_v1();
      }

      template <class Model>
      double get_alpha(const Model& model)
      {
        double v1 = model.get_v1(), v2 = model.get_v2();
        double lambda345 = model.get_Lambda3() + model.get_Lambda4() + model.get_Lambda5();
        double lambda6 = model.get_Lambda6(), lambda7 = model.get_Lambda7();

        double A = model.get_M112() + 3.0/2.0*model.get_Lambda1()*v1*v1 + 1.0/2.0*lambda345*v2*v2 + 3.0*v1*v2*lambda6;
        double B = model.get_M222() + 3.0/2.0*model.get_Lambda2()*v2*v2 + 1.0/2.0*lambda345*v1*v1 + 3.0*v1*v2*lambda7;
        double C = -model.get_M122() + 3.0/2.0*v1*v2 + 3.0/2.0*(lambda6*v1*v1 + lambda7*v2*v2);
        // double a3 = model.get_M122();
        // double b11 = 1.0/2.0*model.get_Lambda1();
        // double b22 = 1.0/2.0*model.get_Lambda2();
        // double b33 = model.get_Lambda4() + model.get_Lambda5();
        // double b12 = model.get_Lambda3();
        // double b13 = model.get_Lambda6();
        // double b23 = model.get_Lambda7();
 
        // double H1 = 4*pow(v1,2)*b11 + 2.0*v1*v2*b13 + pow(v2,2)*b33;
        // double H2 = pow(v1,2)*b33 + 2*v1*v2*b23 + 4.0*pow(v2,2)*b22;
        // double H3 = pow(v1,2)*b13 + v1*v2*(2.0*b12+b33) + pow(v2,2)*b23;
        // double V3 = a3 + 2.0*b33*v1*v2 + b13*pow(v1,2) + b23*pow(v2,2);
        // double Hm = (-1.0*V3*(v2/(2.0*v1) - v1/(2.0*v2))) + H1 - H2;
        // double H3d = H3 - 2.0*V3;
        // double Hc = sqrt(pow(Hm,2) + 4.0*pow(H3d,2));

        return 1.0/2.0*atan(2.0*C/(A-B));//atan(2.0*H3d/(Hc-Hm));
      }

//    extract pole masses from arrays
      template <class Model>
      double get_mA_pole(const Model& model)
      {
       return model.get_MAh_pole_slha(1);
      }

       template <class Model>
       double get_mA_running(const Model& model)
       {
        return (model.get_DRbar_masses())(7);
       }

      template <class Model>
      double get_mh_2_pole(const Model& model)
      {
       return model.get_Mhh_pole_slha(1);
      }

       template <class Model>
       double get_mh_2_running(const Model& model)
       {
           return (model.get_DRbar_masses())(5);
       }


      template <class Model>
      double get_mh_1_pole(const Model& model)
      {
       return model.get_Mhh_pole_slha(0);
      }

       template <class Model>
       double get_mh_1_running(const Model& model)
       {
           return (model.get_DRbar_masses())(4);
       }

      template <class Model>
      double get_mHm_pole(const Model& model)
      {
      //  return model.get_MHm_pole_slha(1);
      return model.get_MHm(1);
      }

       template <class Model>
       double get_mHm_running(const Model& model)
       {
           return (model.get_DRbar_masses())(9);
       }

       // get lambdas (running) from FS

       template <class Model>
       double get_lambda1(const Model& model)
       {
           return model.get_Lambda1();
       }

       template <class Model>
       double get_lambda2(const Model& model)
       {
           return model.get_Lambda2();
       }

       template <class Model>
       double get_lambda3(const Model& model)
       {
           return model.get_Lambda3();
       }

       template <class Model>
       double get_lambda4(const Model& model)
       {
           return model.get_Lambda4();
       }

       template <class Model>
       double get_lambda5(const Model& model)
       {
           return model.get_Lambda5();
       }

       template <class Model>
       double get_lambda6(const Model& model)
       {
           return model.get_Lambda6();
       }

       template <class Model>
       double get_lambda7(const Model& model)
       {
           return model.get_Lambda7();
       }

       template <class Model>
       double get_m12_2(const Model& model)
       {
           return model.get_M122();
       }

       template <class Model>
      double get_sinthW2_DRbar(const Model& model)
      {
       double sthW2 = Utils::sqr(model.get_g1()) * 0.6 /
                      (0.6 * Utils::sqr(model.get_g1()) +
                      Utils::sqr(model.get_g2()));
       return sthW2;
      }

       template <class Model>
      double get_MAh1_pole_slha(const Model& model)
      {
        return model.get_MAh_pole_slha(1);
      }

      template <class Model>
      double get_MHpm1_pole_slha(const Model& model)
      {
        return model.get_MHm_pole_slha(1);
      }

    //    template <class Model>
    //   void set_Mhh_pole_slha(Model& model, double mass, int i)
    //   {
    //     cout << "set_Mhh_pole_slha: " << mass << endl;
    //     model.get_physical_slha().Mhh(i) = mass;
    //   }

    //    template <class Model>
    //   void set_MAh1_pole_slha(Model& model, double mass)
    //   {
    //     model.get_physical_slha().MAh(1) = mass;
    //   }

    //   template <class Model>
    //   void set_MHpm1_pole_slha(Model& model, double mass)
    //   {
    //     model.get_physical_slha().MHm(1) = mass;
    //   }

    //  //PA:  setting MZ and MW is necessary because we may have them as ouptuts
    //  template <class Model>
    //  void set_MZ_pole_slha(Model& model, double mass)
    //  {
    //     model.get_physical_slha().MVZ = mass;
    //  }

    //  template <class Model>
    //  void set_MW_pole_slha(Model& model, double mass)
    //  {
    //     model.get_physical_slha().MVWm = mass;
    //  }

      template <class MI>
      typename THDMSpec<MI>::GetterMaps THDMSpec<MI>::fill_getter_maps()
      {
        typename THDMSpec<MI>::GetterMaps map_collection;
         typedef typename MI::Model Model;

         typedef typename MTget::FInfo1 FInfo1;
         typedef typename MTget::FInfo2 FInfo2;

        //  static const std::set<int> i01 = initSet(0,1);
        //  static const std::set<int> i012 = initSet(0,1,2);
        //  static const std::set<int> i0123 = initSet(0,1,2,3);
        //  static const std::set<int> i012345 = initSet(0,1,2,3,4,5);

         static const int i01v[] = {0,1};
         static const std::set<int> i01(i01v, Utils::endA(i01v));

         static const int i012v[] = {0,1,2};
         static const std::set<int> i012(i012v, Utils::endA(i012v));

         static const int i0123v[] = {0,1,2,3};
         static const std::set<int> i0123(i0123v, Utils::endA(i0123v));

         static const int i012345v[] = {0,1,2,3,4,5};
         static const std::set<int> i012345(i012345v, Utils::endA(i012345v));

         /// @{ mass2 - mass dimension 2 parameters
         //
         // Functions utilising the "plain-vanilla" function signature
         // (Zero index member functions of model object)
         {  // scope so we can reuse the name 'tmp_map' several times, so that our macro works.
            // could make a better macro, or an actual function, but I'm in a hurry
            // ##nil
         }

         // Functions utilising the "extraM" function signature
         // (Zero index, model object as argument)
         {
            // ##nil
         }

         // functions utilising the two-index "plain-vanilla" function signature
         // (two-index member functions of model object)
         {
            // ##nil
         }

         /// @}
         /// @{ mass1 - mass dimension 1 parameters
         //
         // Functions utilising the "plain-vanilla" function signature
         // (Zero index member functions of model object)
         {
            typename MTget::fmap0 tmp_map;
            // tmp_map["vev"]= &Model::get_vev;

            map_collection[Par::mass1].map0 = tmp_map;
         }

          // Functions utilising the "extraM" function signature
         // (Zero index, model object as argument)
         {
            typename MTget::fmap0_extraM tmp_map;
            tmp_map["m12_2"]= &get_m12_2<Model>;
            tmp_map["lambda_1"]= &get_lambda1<Model>;
            tmp_map["lambda_2"]= &get_lambda2<Model>;
            tmp_map["lambda_3"]= &get_lambda3<Model>;
            tmp_map["lambda_4"]= &get_lambda4<Model>;
            tmp_map["lambda_5"]= &get_lambda5<Model>;
            tmp_map["lambda_6"]= &get_lambda6<Model>;
            tmp_map["lambda_7"]= &get_lambda7<Model>;
            // tmp_map["vev"]= &Model::get_vev;

            tmp_map["A0"] = &get_mA_running<Model>;
            tmp_map["H+"] = &get_mHm_running<Model>;

            map_collection[Par::mass1].map0_extraM = tmp_map;
         }

         // Functions utilising the two-index "plain-vanilla" function signature
         // (Two-index member functions of model object)
        {
            typename MTget::fmap1 tmp_map;

            tmp_map["h0"] =  FInfo1( &Model::get_Mhh, i01 );
            
            map_collection[Par::mass1].map1 = tmp_map;
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

            // tmp_map["tanb"]= &Model::get_tanb;

            map_collection[Par::dimensionless].map0 = tmp_map;
         }

         // Functions utilising the "extraM" function signature
         // (Zero index, model object as argument)
         {
            typename MTget::fmap0_extraM tmp_map;
            tmp_map["sinW2"] = &get_sinthW2_DRbar<Model>;
            tmp_map["tanb"]= &get_tanb<Model>;
            tmp_map["alpha"]= &get_alpha<Model>;
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
            // tmp_map["Goldstone0"] = &get_neutral_goldstone_pole_slha<Model>;
            // tmp_map["Goldstone+"] = &get_charged_goldstone_pole_slha<Model>;
            // Antiparticle label (no automatic conversion for this)
            // tmp_map["Goldstone-"] = &get_charged_goldstone_pole_slha<Model>;

            map_collection[Par::Pole_Mass].map0_extraM = tmp_map;
         }

         // Functions utilising the one-index "plain-vanilla" function signature
         // (One-index member functions of model object)
         {
            typename MTget::fmap1 tmp_map;

            tmp_map["h0"] =  FInfo1( &Model::get_Mhh_pole_slha, i01 );
            
            map_collection[Par::Pole_Mass].map1 = tmp_map;
         }

         /// @}

         /// @{ Pole_Mixing - Pole mass parameters
         //
         // Functions utilising the two-index "plain-vanilla" function signature
         // (Two-index member functions of model object)
         {
            // typename MTget::fmap2 tmp_map;

            // tmp_map["h0"] =   FInfo2( &Model::get_ZH_pole_slha, i01, i01);
            // tmp_map["A0"] =   FInfo2( &Model::get_ZA_pole_slha, i01, i01);
            // tmp_map["H+"] = FInfo2( &Model::get_ZP_pole_slha, i01, i01);

            // map_collection[Par::Pole_Mixing].map2 = tmp_map;
         }
         /// @}

        //  cout << "map_collection[Par::Pole_Mass]: " << map_collection[Par::Pole_Mass] << endl;

         return map_collection;
      }

      // Filler function for setter function pointer maps
      template <class MI>
      typename THDMSpec<MI>::SetterMaps THDMSpec<MI>::fill_setter_maps()
      {
         typename THDMSpec<MI>::SetterMaps map_collection;
         typedef typename MI::Model Model;

         typedef typename MTset::FInfo2 FInfo2;

        //  typedef typename MTset::FInfo1M FInfo1M;
        //  typedef typename MTset::FInfo2M FInfo2M;

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
            // ##nil
         }

         // Functions utilising the two-index "plain-vanilla" function signature
         // (Two-index member functions of model object)
         {
            // ##nil
         }
         /// @}

         /// @{ mass1 - mass dimension 1 parameters
         //
         // Functions utilising the "plain-vanilla" function signature
         // (Zero index member functions of model object)
         {
            typename MTset::fmap0 tmp_map;
            // tmp_map["vev"]= &Model::set_vev;

            map_collection[Par::mass1].map0 = tmp_map;
         }

         // Functions utilising the two-index "plain-vanilla" function signature
         // (Two-index member functions of model object)
         {
            // ##nil
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

            // tmp_map["tanb"]= &Model::set_tanb;

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
          // tmp_map["A0"] = &set_MAh1_pole_slha<Model>;
          // tmp_map["H+"] = &set_MHpm1_pole_slha<Model>;

            /// Note; these aren't in the particle database, so no
            /// conversion between particle/antiparticle.
            //   tmp_map["Goldstone0"] = &set_neutral_goldstone_pole_slha<Model>;
            //   tmp_map["Goldstone+"] = &set_charged_goldstone_pole_slha<Model>;
            //   tmp_map["Goldstone-"] = &set_charged_goldstone_pole_slha<Model>;

            /// PA: MW is a prediction in FS and most spectrum generators
            /// so this belongs in the HE object.
            /// MZ is not and so belongs in LE object
          // tmp_map["W+"] = &set_MW_pole_slha<Model>;

          map_collection[Par::dimensionless].map0_extraM = tmp_map;
        }

        {
          typename MTset::fmap1_extraM tmp_map;

          // tmp_map["h0"] =  FInfo1M( &set_Mhh_pole_slha<Model>, i01 );

          map_collection[Par::Pole_Mass].map1_extraM = tmp_map;
        }


        /// @{ Pole_Mixing - Pole mass parameters
        //
        // Functions utilising the two-index "plain-vanilla" function signature
        // (Two-index member functions of model object)
        {
        //   typename MTset::fmap2_extraM tmp_map;

        //   tmp_map["h0"] =   FInfo2M( &set_ZH_pole_slha, i01, i01);
        //   tmp_map["A0"] =   FInfo2M( &set_ZA_pole_slha, i01, i01);
        //   tmp_map["H+"] = FInfo2M( &set_ZP_pole_slha, i01, i01);

        //   map_collection[Par::Pole_Mixing].map2_extraM = tmp_map;
        }


         return map_collection;
      }

   } // end SpecBit namespace


} // end Gambit namespace

#endif
