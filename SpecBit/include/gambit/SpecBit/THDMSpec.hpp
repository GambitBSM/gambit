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
///  \author Filip Rajec
///          (filip.rajec@adelaide.edu.au)
///  \date 2020 Apr
///
///  *********************************************

#ifndef THDMSPEC_H
#define THDMSPEC_H

#include <memory>
#include <typeinfo>

#include "gambit/cmake/cmake_variables.hpp"
#include "gambit/Elements/slhaea_helpers.hpp"
#include "gambit/Elements/thdm_slhahelp.hpp"
#include "gambit/Elements/subspectrum.hpp"
#include "gambit/Utils/util_functions.hpp"
#include "gambit/Utils/version.hpp"
#include "gambit/SpecBit/THDMSpec_head.hpp"

// Flexible SUSY stuff (should not be needed by the rest of gambit)
#include "flexiblesusy/config/config.h"

#include "gambit/Elements/shared_types.hpp"

// #define ALPHA_DEBUG

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

      // runs to scale, throws an invalid point if FS fails to validate model
      // by default if FS fails to validate model the scan stops
      template <class MI>
      void THDMSpec<MI>::RunToScaleOverride(double scale)
      {
        try {
          model_interface.model.run_to(scale);
        }
        catch(...){
          std::cout << "Debug: SpecBit throwing invalid point when running" << std::endl; // TODO: remove this
          invalid_point().raise("FS Invalid Point: RunToScale Failed");
        }
      // get DR bar masses
      model_interface.model.calculate_DRbar_masses();
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

      // Fill an SLHAea object with spectrum information
      template <class MI>
      void THDMSpec<MI>::add_to_SLHAea(int slha_version, SLHAstruct& slha) const
      {
         std::ostringstream comment;
         // comment carried over
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
         // All other THDM blocks using THDMSLHA helper
         slhahelp::add_THDM_spectrum_to_SLHAea(*this, slha, slha_version);
      }

      template <class MI>
      std::string THDMSpec<MI>::AccessError(std::string state) const
      {
        std::string errormsg;
        errormsg = "Error accessing "+ state + " element is out of bounds";
        return errormsg;
      }

      // wrapper getter methods for

      template <class Model>
      double get_sinthW2_MSbar(const Model& model) {
         double sthW2 = Utils::sqr(model.get_g1()) * 0.6 /
         (0.6 * Utils::sqr(model.get_g1()) +
         Utils::sqr(model.get_g2()));
         return sthW2;
      }

      template <class Model>
      double get_sinthW2_DRbar(const Model& model) {
         double sthW2 = Utils::sqr(model.get_g1()) * 0.6 /
         (0.6 * Utils::sqr(model.get_g1()) +
         Utils::sqr(model.get_g2()));
         return sthW2;
      }

      template <class Model>
      double get_v1(const Model& model) {
         return model.get_v1();
      }

      template <class Model>
      double get_v2(const Model& model) {
         return model.get_v2();
      }

      template <class Model>
      double get_vev(const Model& model) {
         return sqrt(pow(model.get_v1(),2) + pow(model.get_v2(),2));
      }

      // wrapper getter methods for
      // physical masses
      template <class Model>
      double get_mW_running(const Model& model) {
         return (model.get_DRbar_masses())(19);
      }

      template <class Model>
      double get_mW_pole_slha(const Model& model) {
         return model.get_MVWm_pole_slha();
      }

      template <class Model>
      double get_mA_running(const Model& model) {
         return (model.get_DRbar_masses())(7);
      }

      template <class Model>
      double get_mA_pole_slha(const Model& model) {
         return model.get_MAh_pole_slha(1);
      }

      template <class Model>
      double get_mA_goldstone_running(const Model& model) {
         return (model.get_DRbar_masses())(6);
      }

      template <class Model>
      double get_mA_goldstone_pole_slha(const Model& model) {
         return model.get_MAh_pole_slha(0);
      }

      template <class Model>
      double get_mh_1_running(const Model& model) {
         return (model.get_DRbar_masses())(4);
      }

      template <class Model>
      double get_mh_1_pole_slha(const Model& model) {
         return model.get_Mhh_pole_slha(0);
      }

      template <class Model>
      double get_mh_2_running(const Model& model) {
         return (model.get_DRbar_masses())(5);
      }

      template <class Model>
      double get_mh_2_pole_slha(const Model& model) {
         return model.get_Mhh_pole_slha(1);
      }

      template <class Model>
      double get_mHpm_running(const Model& model) {
         return (model.get_DRbar_masses())(9);
      }

      template <class Model>
      double get_mHpm_pole_slha(const Model& model) {
         return model.get_MHm_pole_slha(1);
      }

      template <class Model>
      double get_mHpm_goldstone_running(const Model& model) {
         return (model.get_DRbar_masses())(8);
      }

      template <class Model>
      double get_mHpm_goldstone_pole_slha(const Model& model) {
         return model.get_MHm_pole_slha(0);
      }

      // wrapper getter methods for higgs basis parameters 
      // forward declaration as needed
      template <class Model>
      double get_tanb(const Model& model);

      template <class Model>
      double get_beta(const Model& model) {
         return atan(get_tanb(model));
      }

      template <class Model>
      double get_Lambda1(const Model& model) {
         double lam1 = model.get_Lambda1(), lam2 = model.get_Lambda2(), lam345 = model.get_Lambda3() + model.get_Lambda4() + model.get_Lambda5();
         double lam6 = model.get_Lambda6(), lam7 = model.get_Lambda7(), b = atan(get_tanb(model)), cb = cos(b), sb = sin(b), s2b = sin(2.*b);
         return lam1*pow(cb,4) + lam2*pow(sb,4) + 0.5*lam345*pow(s2b,2) + 2.*s2b*(pow(cb,2)*lam6+pow(sb,2)*lam7);
      }

      template <class Model>
      double get_Lambda2(const Model& model) {
         double lam1 = model.get_Lambda1(), lam2 = model.get_Lambda2(), lam345 = model.get_Lambda3() + model.get_Lambda4() + model.get_Lambda5();
         double lam6 = model.get_Lambda6(), lam7 = model.get_Lambda7(), b = atan(get_tanb(model)), cb = cos(b), sb = sin(b), s2b = sin(2.*b);
         return lam1*pow(sb,4) + lam2*pow(cb,4) + 0.5*lam345*pow(s2b,2) - 2.*s2b*(pow(sb,2)*lam6+pow(cb,2)*lam7);
      }

      template <class Model>
      double get_Lambda3(const Model& model) {
         double lam1 = model.get_Lambda1(), lam2 = model.get_Lambda2(), lam3 = model.get_Lambda3(), lam345 = lam3 + model.get_Lambda4() + model.get_Lambda5();
         double lam6 = model.get_Lambda6(), lam7 = model.get_Lambda7(), b = atan(get_tanb(model)), c2b = cos(2.*b), s2b = sin(2.*b);
         return 0.25*pow(s2b,2)*(lam1+lam2-2.*lam345) + lam3 - s2b*c2b*(lam6-lam7);
      }

      template <class Model>
      double get_Lambda4(const Model& model) {
         double lam1 = model.get_Lambda1(), lam2 = model.get_Lambda2(), lam4 = model.get_Lambda4(), lam345 = model.get_Lambda3() + lam4 + model.get_Lambda5();
         double lam6 = model.get_Lambda6(), lam7 = model.get_Lambda7(), b = atan(get_tanb(model)), c2b = cos(2.*b), s2b = sin(2.*b);
         return 0.25*pow(s2b,2)*(lam1+lam2-2.*lam345) + lam4 - s2b*c2b*(lam6-lam7);
      }

      template <class Model>
      double get_Lambda5(const Model& model) {
         double lam1 = model.get_Lambda1(), lam2 = model.get_Lambda2(), lam5 = model.get_Lambda5(), lam345 = model.get_Lambda3() + model.get_Lambda4() + lam5;
         double lam6 = model.get_Lambda6(), lam7 = model.get_Lambda7(), b = atan(get_tanb(model)), c2b = cos(2.*b), s2b = sin(2.*b);
         return 0.25*pow(s2b,2)*(lam1+lam2-2.*lam345) + lam5 - s2b*c2b*(lam6-lam7);
      }

      template <class Model>
      double get_Lambda6(const Model& model) {
         double lam1 = model.get_Lambda1(), lam2 = model.get_Lambda2(), lam345 = model.get_Lambda3() + model.get_Lambda4() + model.get_Lambda5();
         double lam6 = model.get_Lambda6(), lam7 = model.get_Lambda7(), b = atan(get_tanb(model)), cb = cos(b), sb = sin(b), c2b = cos(2.*b), s2b = sin(2.*b);
         return -0.5*s2b*(lam1*pow(cb,2)-lam2*pow(sb,2)-lam345*c2b) + cb*cos(3.*b)*lam6 + sb*sin(3.*b)*lam7;
      }

      template <class Model>
      double get_Lambda7(const Model& model) {
         double lam1 = model.get_Lambda1(), lam2 = model.get_Lambda2(), lam345 = model.get_Lambda3() + model.get_Lambda4() + model.get_Lambda5();
         double lam6 = model.get_Lambda6(), lam7 = model.get_Lambda7(), b = atan(get_tanb(model)), cb = cos(b), sb = sin(b), c2b = cos(2.*b), s2b = sin(2.*b);
         return -0.5*s2b*(lam1*sb*sb-lam2*cb*cb+lam345*c2b)+sb*sin(3.*b)*lam6+cb*cos(3.*b)*lam7;
      }

      template <class Model>
      double get_M12_2(const Model& model) {
         double m12_2 = model.get_M122(), m11_2 = model.get_M112(), m22_2 = model.get_M222();
         double b = atan(get_tanb(model)), c2b = cos(2.*b), s2b = sin(2.*b);
         return 0.5*(m11_2-m22_2)*s2b + m12_2*c2b;
      }

      template <class Model>
      double get_M11_2(const Model& model) {
         double m12_2 = model.get_M122(), m11_2 = model.get_M112(), m22_2 = model.get_M222();
         double b = atan(get_tanb(model)), cb = cos(b), sb = sin(b), s2b = sin(2.*b);
         return m11_2*pow(cb,2) + m22_2*pow(sb,2) - m12_2*s2b;
      }

      template <class Model>
      double get_M22_2(const Model& model) {
         double m12_2 = model.get_M122(), m11_2 = model.get_M112(), m22_2 = model.get_M222();
         double b = atan(get_tanb(model)), cb = cos(b), sb = sin(b), s2b = sin(2.*b);
         return m11_2*pow(sb,2) + m22_2*pow(cb,2) + m12_2*s2b;
      }

      // wrapper getter methods for
      // generic basis parameters
      template <class Model>
      double get_lambda1(const Model& model) {
         return model.get_Lambda1();
      }

      template <class Model>
      double get_lambda2(const Model& model) {
         return model.get_Lambda2();
      }

      template <class Model>
      double get_lambda3(const Model& model) {
         return model.get_Lambda3();
      }

      template <class Model>
      double get_lambda4(const Model& model) {
         return model.get_Lambda4();
      }

      template <class Model>
      double get_lambda5(const Model& model) {
         return model.get_Lambda5();
      }

      template <class Model>
      double get_lambda6(const Model& model) {
         return model.get_Lambda6();
      }

      template <class Model>
      double get_lambda7(const Model& model) {
         return model.get_Lambda7();
      }

      template <class Model>
      double get_m12_2(const Model& model) {
         return model.get_M122();
      }

      template <class Model>
      double get_m11_2(const Model& model) {
         return model.get_M112();
      }

      template <class Model>
      double get_m22_2(const Model& model) {
         return model.get_M222();
      }

      // wrapper getter method for
      // yukawa couplings
      // TODO: find a 'nicer' way to do this
      template <class Model>
      double get_yukawa_type(const Model& model) {
         std::string spec_class_type = typeid(model).name();
         if (spec_class_type == "N12flexiblesusy11THDM_I_slhaINS_6THDM_IINS_9Two_scaleEEEEE"){
            return 1;
         }
         else if (spec_class_type == "N12flexiblesusy12THDM_II_slhaINS_7THDM_IIINS_9Two_scaleEEEEE"){
            return 2;
         }
         else if (spec_class_type == "N12flexiblesusy16THDM_LS_slhaINS_11THDM_LSINS_9Two_scaleEEEEE"){
            return 3;
         }
         else if (spec_class_type == "N12flexiblesusy17THDM_flipped_slhaINS_12THDM_flippedINS_9Two_scaleEEEEE"){
            return 4;
         }
         else {
           utils_error().raise(LOCAL_INFO,"Unknown spectrum generator requested for THDM."); return -1;
            exit(0);
         }
      }

      // wrapper getter methods for
      // mixing angles
      template <class Model>
      double get_tanb(const Model& model) {
         return model.get_v2()/model.get_v1();
      }

      template <class Model>
      double get_alpha(const Model& model) {
         double v_1 = model.get_v1(), v_2 = model.get_v2();
         double b = atan(v_2/v_1), v2 = pow(v_1,2) + pow(v_2,2);
         double mA = get_mA_running(model), m_A2 = pow(mA,2);
         double Lam1 = get_Lambda1(model), Lam5 = get_Lambda5(model), Lam6 = get_Lambda6(model);
         double sb = sin(b), cb = cos(b), tb = v_2/v_1, ctb = v_1/v_2;
         double sb2 = sb*sb, cb2 = cb*cb;
         double m122 = model.get_M122();
         double lam1 = model.get_Lambda1(), lam2 = model.get_Lambda2(), lam3 = model.get_Lambda3(), lam4 = model.get_Lambda4();
         double lam5 = model.get_Lambda5(), lam6 = model.get_Lambda6(), lam7 = model.get_Lambda7();

         double s2ba = -2.*Lam6*v2, c2ba = -(m_A2+(Lam5-Lam1)*v2);
         // gaurenteed to be in quadrant I or IV, due to 1/2 factor
         double ba = 0.5*atan2(s2ba,c2ba);
         double alpha = b - ba;
         return alpha;
      }

      #ifdef ALPHA_DEBUG
         // debug method to check that alpha agrees in all cases
         template <class Model>
         double get_alpha_calculated(const Model& model) {
            double v_1 = model.get_v1(), v_2 = model.get_v2();
            double b = atan(v_2/v_1), v2 = pow(v_1,2) + pow(v_2,2);
            double mA = get_mA_running(model), m_A2 = pow(mA,2);
            double Lam1 = get_Lambda1(model), Lam5 = get_Lambda5(model), Lam6 = get_Lambda6(model);
            double sb = sin(b), cb = cos(b), tb = v_2/v_1, ctb = v_1/v_2;
            double sb2 = sb*sb, cb2 = cb*cb;
            double m122 = model.get_M122();
            double lam1 = model.get_Lambda1(), lam2 = model.get_Lambda2(), lam3 = model.get_Lambda3(), lam4 = model.get_Lambda4();
            double lam5 = model.get_Lambda5(), lam6 = model.get_Lambda6(), lam7 = model.get_Lambda7();

            // method 1
            double s2ba = -2.*Lam6*v2, c2ba = -(m_A2+(Lam5-Lam1)*v2);
            double ba = 0.5*atan2(s2ba,c2ba);
            double alpha = b - ba;

            if (alpha>M_PI/2.0) {
               alpha =  alpha-M_PI;
            }

            std::cout << "-------------" << std::endl;
            std::cout << "method 1" << std::endl;
            std::cout << "s2ba: " <<  s2ba << std::endl;
            std::cout << "c2ba: " <<  c2ba << std::endl;
            std::cout << "ba: " << ba << std::endl;
            std::cout << alpha << std::endl;

            // method 2
            double mA2 = m122/(sb*cb) - v2/2.0 * ( 2.0*lam5 + lam6*ctb + lam7*tb );
            double mC2 = mA2 + v2/2.0 * ( lam5 - lam4 );

            double M112 = mA2*sb2 + v2*( lam1*cb2 + 2.0*lam6*sb*cb + lam5*sb2 );
            double M222 = mA2*cb2 + v2*( lam2*sb2 + 2.0*lam7*sb*cb + lam5*cb2 );
            double M122 = -mA2*sb*cb + v2*( (lam3+lam4)*sb*cb + lam6*cb2 + lam7*sb2 );
            
            double s2a = 2*M122/sqrt( pow( ( M112 - M222 ) , 2 ) + 4.0*pow( ( M122 ) , 2 ) );
            double c2a = ( M112 - M222 )/sqrt( pow( ( M112 - M222 ) , 2 ) + 4.0*pow( ( M122 ) , 2 ) );

            double alpha_1 = asin(s2a)/2.0;
            double alpha_2 = acos(c2a)/2.0;

            alpha = atan2(s2a,c2a)/2.0;

            std::cout << "-------------" << std::endl;
            std::cout << "method 2" << std::endl;
            std::cout << alpha << std::endl;
            std::cout << "-------------" << std::endl;

            return alpha;
         }
      #endif

      // Filler function for getter function pointer maps
      template <class MI>
      typename THDMSpec<MI>::GetterMaps THDMSpec<MI>::fill_getter_maps()
      {
        typename THDMSpec<MI>::GetterMaps map_collection;
         typedef typename MI::Model Model;

         typedef typename MTget::FInfo1 FInfo1;
         typedef typename MTget::FInfo2 FInfo2;

         static const int i01v[] = {0,1};
         static const std::set<int> i01(i01v, Utils::endA(i01v));

         static const int i012v[] = {0,1,2};
         static const std::set<int> i012(i012v, Utils::endA(i012v));

         static const int i0123v[] = {0,1,2,3};
         static const std::set<int> i0123(i0123v, Utils::endA(i0123v));

         static const int i012345v[] = {0,1,2,3,4,5};
         static const std::set<int> i012345(i012345v, Utils::endA(i012345v));

         /// @{ mass1 - mass dimension 1 parameters
         //
         // Functions utilising the "plain-vanilla" function signature
         // (Zero index member functions of model object)
         {
            typename MTget::fmap0 tmp_map;
            // none
            map_collection[Par::mass1].map0 = tmp_map;
         }

          // Functions utilising the "extraM" function signature
         // (Zero index, model object as argument)
         {
            typename MTget::fmap0_extraM tmp_map;
            // coupling basis potential parameters
            tmp_map["m11_2"]= &get_m11_2<Model>;
            tmp_map["m22_2"]= &get_m22_2<Model>;
            tmp_map["m12_2"]= &get_m12_2<Model>;
            tmp_map["lambda_1"]= &get_lambda1<Model>;
            tmp_map["lambda_2"]= &get_lambda2<Model>;
            tmp_map["lambda_3"]= &get_lambda3<Model>;
            tmp_map["lambda_4"]= &get_lambda4<Model>;
            tmp_map["lambda_5"]= &get_lambda5<Model>;
            tmp_map["lambda_6"]= &get_lambda6<Model>;
            tmp_map["lambda_7"]= &get_lambda7<Model>;
            // higgs basis potential parameters
            tmp_map["M11_2"]= &get_M11_2<Model>;
            tmp_map["M22_2"]= &get_M22_2<Model>;
            tmp_map["M12_2"]= &get_M12_2<Model>;
            tmp_map["Lambda_1"]= &get_Lambda1<Model>;
            tmp_map["Lambda_2"]= &get_Lambda2<Model>;
            tmp_map["Lambda_3"]= &get_Lambda3<Model>;
            tmp_map["Lambda_4"]= &get_Lambda4<Model>;
            tmp_map["Lambda_5"]= &get_Lambda5<Model>;
            tmp_map["Lambda_6"]= &get_Lambda6<Model>;
            tmp_map["Lambda_7"]= &get_Lambda7<Model>;
            // physical basis running masses
            tmp_map["A0"] = &get_mA_running<Model>;
            tmp_map["H+"] = &get_mHpm_running<Model>;
            tmp_map["H-"] = &get_mHpm_running<Model>;
            tmp_map["G0"] = &get_mA_goldstone_running<Model>;
            tmp_map["G+"] = &get_mHpm_goldstone_running<Model>;
            tmp_map["G-"] = &get_mHpm_goldstone_running<Model>;
            tmp_map["W+"] = &get_mW_running<Model>;
            tmp_map["W-"] = &get_mW_running<Model>;
            // vev
            tmp_map["vev"]= &get_vev<Model>;
            tmp_map["v1"]= &get_v1<Model>;
            tmp_map["v2"]= &get_v2<Model>;
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
            map_collection[Par::dimensionless].map0 = tmp_map;
         }

         // Functions utilising the "extraM" function signature
         // (Zero index, model object as argument)
         {
            typename MTget::fmap0_extraM tmp_map;
            tmp_map["sinW2"] = &get_sinthW2_DRbar<Model>;
            tmp_map["tanb"]= &get_tanb<Model>;
            tmp_map["alpha"]= &get_alpha<Model>;
            tmp_map["beta"]= &get_beta<Model>;
            #ifdef ALPHA_DEBUG
               tmp_map["alpha_alt"]= &get_alpha_calculated<Model>;
            #endif
            tmp_map["yukawaCoupling"]= &get_yukawa_type<Model>;
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
            // none
            map_collection[Par::Pole_Mass].map0 = tmp_map;
         }

         // Functions utilising the "extraM" function signature
         // (Zero index, model object as argument)
         {
            typename MTget::fmap0_extraM tmp_map;
            tmp_map["A0"] = &get_mA_pole_slha<Model>;
            tmp_map["H+"] = &get_mHpm_pole_slha<Model>;
            tmp_map["H-"] = &get_mHpm_pole_slha<Model>;
            tmp_map["G0"] = &get_mA_goldstone_pole_slha<Model>;
            tmp_map["G+"] = &get_mHpm_goldstone_pole_slha<Model>;
            tmp_map["G-"] = &get_mHpm_goldstone_pole_slha<Model>;
            tmp_map["W+"] = &get_mW_pole_slha<Model>;
            tmp_map["W-"] = &get_mW_pole_slha<Model>;
            map_collection[Par::Pole_Mass].map0_extraM = tmp_map;
         }

         // Functions utilising the one-index "plain-vanilla" function signature
         // (One-index member functions of model object)s
         {
            typename MTget::fmap1 tmp_map;
            tmp_map["h0"] =  FInfo1( &Model::get_Mhh_pole_slha, i01 );
            map_collection[Par::Pole_Mass].map1 = tmp_map;
         }
         /// @}

         return map_collection;
      }

      // Filler function for setter function pointer maps
      template <class MI>
      typename THDMSpec<MI>::SetterMaps THDMSpec<MI>::fill_setter_maps()
      {
         typename THDMSpec<MI>::SetterMaps map_collection;
         typedef typename MI::Model Model;
         typedef typename MTset::FInfo2 FInfo2;
         static const std::set<int> i01 = initSet(0,1);
         static const std::set<int> i012 = initSet(0,1,2);
         static const std::set<int> i0123 = initSet(0,1,2,3);
         static const std::set<int> i012345 = initSet(0,1,2,3,4,5);

         /// @{ mass1 - mass dimension 1 parameters
         //
         // Functions utilising the "plain-vanilla" function signature
         // (Zero index member functions of model object)
         {
            typename MTset::fmap0 tmp_map;
            //none
            map_collection[Par::mass1].map0 = tmp_map;
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
          // none
          map_collection[Par::dimensionless].map0_extraM = tmp_map;
        }

        {
          typename MTset::fmap1_extraM tmp_map;
          // none
          map_collection[Par::Pole_Mass].map1_extraM = tmp_map;
        }
         return map_collection;
      }

   } // end SpecBit namespace
} // end Gambit namespace

#endif
