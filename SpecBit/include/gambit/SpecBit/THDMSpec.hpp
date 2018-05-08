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
          std::cout << "THDMSpec.hpp | RunToScaleOverride() | BEFORE run_to(scale) " << std::endl;
        model_interface.model.run_to(scale);
          std::cout << "THDMSpec.hpp | RunToScaleOverride() | BEFORE calculate_DRbar_masses() " << std::endl;
        model_interface.model.calculate_DRbar_masses();
          std::cout << "THDMSpec.hpp | RunToScaleOverride() | END" << std::endl;

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

      // "extra" function to compute TanBeta & alpha
      template <class Model>
      double get_tanbeta(const Model& model)
      {
        return model.get_v2() / model.get_v1();
      }

       template <class Model>
       double get_alpha(const Model& model)
       {
           return -1*model.Alpha();
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
       return model.get_MHm_pole_slha(1);
      }

       template <class Model>
       double get_mHm_running(const Model& model)
       {
           return (model.get_DRbar_masses())(9);
       }

       // get lambdas (running) from FS

       template <class Model>
       double get_Lambda1(const Model& model)
       {
           return model.get_Lambda1();
       }

       template <class Model>
       double get_Lambda2(const Model& model)
       {
           return model.get_Lambda2();
       }

       template <class Model>
       double get_Lambda3(const Model& model)
       {
           return model.get_Lambda3();
       }

       template <class Model>
       double get_Lambda4(const Model& model)
       {
           return model.get_Lambda4();
       }

       template <class Model>
       double get_Lambda5(const Model& model)
       {
           return model.get_Lambda5();
       }

       template <class Model>
       double get_Lambda6(const Model& model)
       {
           return model.get_Lambda6();
       }

       template <class Model>
       double get_Lambda7(const Model& model)
       {
           return model.get_Lambda7();
       }

       template <class Model>
       double get_M122(const Model& model)
       {
           return model.get_m122();
       }


      template <class MI>
      typename THDMSpec<MI>::GetterMaps THDMSpec<MI>::fill_getter_maps()
      {
         typename THDMSpec<MI>::GetterMaps map_collection;
         typedef typename MI::Model Model;

         typedef typename MTget::FInfo1 FInfo1;
         typedef typename MTget::FInfo2 FInfo2;

         // Can't use c++11 initialise lists, se have to initialise the index sets like this.
         static const int i01v[] = {0,1};
         static const std::set<int> i01(i01v, Utils::endA(i01v));

         static const int i012v[] = {0,1,2};
         static const std::set<int> i012(i012v, Utils::endA(i012v));

         static const int i0123v[] = {0,1,2,3};
         static const std::set<int> i0123(i0123v, Utils::endA(i0123v));

         static const int i012345v[] = {0,1,2,3,4,5};
         static const std::set<int> i012345(i012345v, Utils::endA(i012345v));


        // dimensionless parameters
         {
            typename MTget::fmap0 tmp_map;

            tmp_map["g1"]= &Model::get_g1;
            tmp_map["g2"]= &Model::get_g2;
            tmp_map["g3"]= &Model::get_g3;

            map_collection[Par::dimensionless].map0 = tmp_map;
         }

         {
            typename MTget::fmap0_extraM tmp_map;

            tmp_map["sinW2"] = &get_sinthW2_MSbar<Model>;
            tmp_map["tb"] = &get_tanbeta<Model>;
            tmp_map["alpha"] = &get_alpha<Model>;

            map_collection[Par::dimensionless].map0_extraM = tmp_map;
         }

         {
            typename MTget::fmap2 tmp_map;

            tmp_map["Yd"]= FInfo2( &Model::get_Yd, i012, i012);
            tmp_map["Yu"]= FInfo2( &Model::get_Yu, i012, i012);
            tmp_map["Ye"]= FInfo2( &Model::get_Ye, i012, i012);

            map_collection[Par::dimensionless].map2 = tmp_map;
         }

        // parameters of dimension mass 1
         {
            typename MTget::fmap0 tmp_map;
            tmp_map["v1"] = &Model::get_v1;
            tmp_map["v2"] = &Model::get_v2;
            tmp_map["m12_2"]  = &Model::get_M122;
            tmp_map["m112"] = &Model::get_M112;
            tmp_map["m222"] = &Model::get_M222;

             tmp_map["lambda_1"]= &Model::get_Lambda1;
             tmp_map["lambda_2"]= &Model::get_Lambda2;
             tmp_map["lambda_3"]= &Model::get_Lambda3;
             tmp_map["lambda_4"]= &Model::get_Lambda4;
             tmp_map["lambda_5"]= &Model::get_Lambda5;
             tmp_map["lambda_6"]= &Model::get_Lambda6;
             tmp_map["lambda_7"]= &Model::get_Lambda7;

            map_collection[Par::mass1].map0 = tmp_map;
         }

         {
            typename MTget::fmap0_extraM tmp_map;

            tmp_map["mh0"] =  &get_mh_1_running<Model>;
            tmp_map["mH0"] =  &get_mh_2_running<Model>;
            tmp_map["mA"]  =  &get_mA_running<Model>;
            tmp_map["mC"]  =  &get_mHm_running<Model>;

            map_collection[Par::mass1].map0_extraM = tmp_map;
         }

        // mass eigenstates

         {
            typename MTget::fmap1 tmp_map;

            tmp_map["d"] =    FInfo1( &Model::get_MFd, i012 );
            tmp_map["u"] =    FInfo1( &Model::get_MFu, i012 );
            tmp_map["e-"] =   FInfo1( &Model::get_MFe, i012 );
            tmp_map["e"] =    FInfo1( &Model::get_MFe, i012 );
            tmp_map["dbar"] = FInfo1( &Model::get_MFd, i012 );
            tmp_map["ubar"] = FInfo1( &Model::get_MFu, i012 );
            tmp_map["e+"] =   FInfo1( &Model::get_MFe, i012 );

            map_collection[Par::mass_eigenstate].map1 = tmp_map;
         }

         // pole masses
         {
            typename MTget::fmap0 tmp_map;

            tmp_map["Z0"] = &Model::get_MVZ_pole_slha;
            tmp_map["g"] = &Model::get_MVG_pole_slha;


            tmp_map["W+"] = &Model::get_MVWm_pole_slha;
            tmp_map["W-"] = &Model::get_MVWm_pole_slha;

            map_collection[Par::Pole_Mass].map0 = tmp_map;
         }

         {
            typename MTget::fmap0_extraM tmp_map;

            tmp_map["h0_1"] =  &get_mh_1_pole<Model>;
            tmp_map["h0_2"] =  &get_mh_2_pole<Model>;
            tmp_map["A0"]  =  &get_mA_pole<Model>;
            tmp_map["Hm"]  =  &get_mHm_pole<Model>;

            map_collection[Par::Pole_Mass].map0_extraM = tmp_map;
         }



         return map_collection;
      }

      // Filler function for setter function pointer maps extractable from "runningpars" container
      template <class MI>
      typename THDMSpec<MI>::SetterMaps THDMSpec<MI>::fill_setter_maps()
      {
         typename THDMSpec<MI>::SetterMaps map_collection;
         typedef typename MI::Model Model;

         typedef typename MTset::FInfo1 FInfo1;
         typedef typename MTset::FInfo2 FInfo2;

         // Can't use c++11 initialise lists, se have to initialise the index sets like this.
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
         {
            typename MTset::fmap0 tmp_map;

            tmp_map["m12"]  = &Model::set_M122;
            tmp_map["m112"] = &Model::set_M112;
            tmp_map["m222"] = &Model::set_M222;

            map_collection[Par::mass2].map0 = tmp_map;
         }

         //
         // Functions utilising the "plain-vanilla" function signature
         // (Zero index member functions of model object)
         {
            typename MTset::fmap0 tmp_map;
            tmp_map["v1"] = &Model::set_v1;
            tmp_map["v2"] = &Model::set_v2;


            map_collection[Par::mass1].map0 = tmp_map;
         }

         //
         // Functions utilising the "plain-vanilla" function signature
         // (Zero index member functions of model object)
         {
            typename MTset::fmap0 tmp_map;
            tmp_map["g1"]= &Model::set_g1;
            tmp_map["g2"]= &Model::set_g2;
            tmp_map["g3"]= &Model::set_g3;

            tmp_map["lambda_1"]= &Model::set_Lambda1;
            tmp_map["lambda_2"]= &Model::set_Lambda2;
            tmp_map["lambda_3"]= &Model::set_Lambda3;
            tmp_map["lambda_4"]= &Model::set_Lambda4;
            tmp_map["lambda_5"]= &Model::set_Lambda5;
            tmp_map["lambda_6"]= &Model::set_Lambda6;
            tmp_map["lambda_7"]= &Model::set_Lambda7;


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


         return map_collection;
      }

      /// @}

   } // end SpecBit namespace


} // end Gambit namespace

#endif
