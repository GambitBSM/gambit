//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  ScalarSingletDM_Z2 derived version of SubSpectrum class.
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
///  \author James McKay
///          (j.mckay14@imperial.ac.uk)
///  \date 2016 Mar
///
///  *********************************************

#ifndef ScalarSingletDM_Z2SPEC_H
#define ScalarSingletDM_Z2SPEC_H

#include <memory>

#include "gambit/cmake/cmake_variables.hpp"
#include "gambit/Elements/subspectrum.hpp"
#include "gambit/Elements/slhaea_spec_helpers.hpp"
#include "gambit/Utils/util_functions.hpp"
#include "gambit/SpecBit/ScalarSingletDM_Z2Spec_head.hpp"   // "Header" declarations for ScalarSingletDM_Z2Spec class

// Flexible SUSY stuff (should not be needed by the rest of gambit)
#include "flexiblesusy/config/config.h"


namespace Gambit
{

   namespace SpecBit
   {
      template <class MI>
      const int ScalarSingletDM_Z2Spec<MI>::_index_offset = MI::index_offset;

      template <class MI>
      ScalarSingletDM_Z2Spec<MI>::ScalarSingletDM_Z2Spec(MI mi, str be_name, str be_version)
         : backend_name(be_name)
         , backend_version(be_version)
         , model_interface(mi)
      {}


      template <class MI>
      ScalarSingletDM_Z2Spec<MI>::ScalarSingletDM_Z2Spec()
      {}

      template <class MI>
      ScalarSingletDM_Z2Spec<MI>::~ScalarSingletDM_Z2Spec()
      {}



      template <class MI>
      void ScalarSingletDM_Z2Spec<MI>::RunToScaleOverride(double scale)
      {
        model_interface.model.run_to(scale);
      }
      template <class MI>
      double ScalarSingletDM_Z2Spec<MI>::GetScale() const
      {
        return model_interface.model.get_scale();
      }
      template <class MI>
      void ScalarSingletDM_Z2Spec<MI>::SetScale(double scale)
      {
        model_interface.model.set_scale(scale);
      }

      template <class MI>
      std::string ScalarSingletDM_Z2Spec<MI>::AccessError(std::string state) const
      {
        std::string errormsg;
        errormsg = "Error accessing "+ state + " element is out of bounds";
        return errormsg;
      }



//
      template <class Model>
      double get_sinthW2_MSbar(const Model& model)
      {
       double sthW2 = Utils::sqr(model.get_g1()) * 0.6 /
                      (0.6 * Utils::sqr(model.get_g1()) +
                      Utils::sqr(model.get_g2()));
       return sthW2;
      }


      template <class MI>
      typename ScalarSingletDM_Z2Spec<MI>::GetterMaps ScalarSingletDM_Z2Spec<MI>::fill_getter_maps()
      {
         typename ScalarSingletDM_Z2Spec<MI>::GetterMaps map_collection;
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


        {
            typename MTget::fmap0 tmp_map;
            tmp_map["mS2"]  = &Model::get_muS;
            tmp_map["mu2"] = &Model::get_muH;
            map_collection[Par::mass2].map0 = tmp_map;
         }



         //dimensionless - mass dimension 0 parameters

         {
            typename MTget::fmap0 tmp_map;
            tmp_map["g1"]= &Model::get_g1;
            tmp_map["g2"]= &Model::get_g2;
            tmp_map["g3"]= &Model::get_g3;
            tmp_map["lambda_h"]= &Model::get_LamH;
            tmp_map["lambda_hS"]= &Model::get_LamSH;
            tmp_map["lambda_S"]= &Model::get_LamS;

            map_collection[Par::dimensionless].map0 = tmp_map;
         }


          {
            typename MTget::fmap0_extraM tmp_map;
            tmp_map["sinW2"] = &get_sinthW2_MSbar<Model>;
            map_collection[Par::dimensionless].map0_extraM = tmp_map;
         }



         {
            typename MTget::fmap0 tmp_map;
            tmp_map["vev"] = &Model::get_v;
            tmp_map["lambda_hS"]= &Model::get_LamSH;  // ??? not sure why it wants it here
            map_collection[Par::mass1].map0 = tmp_map;
         }

         // Functions utilising the "extraM" function signature
         // (Zero index, model object as argument)


         // Functions utilising the two-index "plain-vanilla" function signature
         // (Two-index member functions of model object)
         {
            typename MTget::fmap2 tmp_map;

            tmp_map["Yd"]= FInfo2( &Model::get_Yd, i012, i012);
            tmp_map["Yu"]= FInfo2( &Model::get_Yu, i012, i012);
            tmp_map["Ye"]= FInfo2( &Model::get_Ye, i012, i012);

            map_collection[Par::dimensionless].map2 = tmp_map;
         }

         // Functions utilising the one-index "plain-vanilla" function signature
         // (One-index member functions of model object)
         {
            typename MTget::fmap1 tmp_map;

            //tmp_map["S"] = FInfo1( &Model::get_Mss, i012345 );
            //tmp_map["h0"] = FInfo1( &Model::get_Mhh, i01 );

            //Here we may access the goldstone boson
            //and higgs. maybe too dangerous to keep?
            tmp_map["d"] =    FInfo1( &Model::get_MFd, i012 );
            tmp_map["u"] =    FInfo1( &Model::get_MFu, i012 );
            tmp_map["e-"] =   FInfo1( &Model::get_MFe, i012 );
            tmp_map["e"] =    FInfo1( &Model::get_MFe, i012 );
            tmp_map["dbar"] = FInfo1( &Model::get_MFd, i012 );
            tmp_map["ubar"] = FInfo1( &Model::get_MFu, i012 );
            tmp_map["e+"] =   FInfo1( &Model::get_MFe, i012 );

            map_collection[Par::mass_eigenstate].map1 = tmp_map;
         }


         {
            typename MTget::fmap0 tmp_map;

            // ***REMOVED THESE! Leave them to the QedQcdWrapper.***
            // reinstating the Z and W getters as otherwise there is no
            // point in having the setters!
            tmp_map["Z0"] = &Model::get_MVZ_pole_slha;
            //// //tmp_map["g"] = &Model::get_MGluon_pole_slha;
             tmp_map["g"] = &Model::get_MVG_pole_slha;


            map_collection[Par::Pole_Mass].map0 = tmp_map;
         }

         {
            typename MTget::fmap0 tmp_map;

            tmp_map["S"] =  &Model::get_Mss_pole_slha;
            tmp_map["h0_1"] = &Model::get_Mhh_pole_slha; //added to match SM Higgs container naming
            tmp_map["A0"] = &Model::get_MAh_pole_slha;



            map_collection[Par::Pole_Mass].map0 = tmp_map;
         }





         return map_collection;
      }

      // Filler function for setter function pointer maps extractable from "runningpars" container
      template <class MI>
      typename ScalarSingletDM_Z2Spec<MI>::SetterMaps ScalarSingletDM_Z2Spec<MI>::fill_setter_maps()
      {
         typename ScalarSingletDM_Z2Spec<MI>::SetterMaps map_collection;
         typedef typename MI::Model Model;

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

            tmp_map["mS2"] = &Model::set_muS;
            tmp_map["mu2"] = &Model::set_muH;

            map_collection[Par::mass2].map0 = tmp_map;
         }

         //
         // Functions utilising the "plain-vanilla" function signature
         // (Zero index member functions of model object)
         {
            typename MTset::fmap0 tmp_map;
            tmp_map["vev"] = &Model::set_v;

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
            tmp_map["lambda_h"]= &Model::set_LamH;
            tmp_map["lambda_hS"]= &Model::set_LamSH;
            tmp_map["lambda_S"]= &Model::set_LamS;

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
