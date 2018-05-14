//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  A simple SubSpectrum wrapper for the TDHM model. No RGEs included.
///
///  *********************************************
///
///  Authors:
///  <!-- add name and date if you modify -->
///
///  \author Filip Rajec, July 2016
///  Orginal code by Ben Farmer
///
///  *********************************************

#ifndef __THDMSimpleSpec_hpp__
#define __THDMSimpleSpec_hpp__

#include "gambit/Elements/spec.hpp"
#include "gambit/Models/SpectrumContents/RegisteredSpectra.hpp"

namespace Gambit
{
  namespace Models
  {
    /// Simple extension of the SMHiggsSimpleSpec "model object"
    /// to include THDM parameters
    struct THDMModel
    {
        double mh0;
        double mH0;
        double mA0;
        double mC;
        double tanb;
        double m12_2;
        double lambda6;
        double lambda7;
        double alpha;
        double yukawaCoupling;
        
        double lambda1;
        double lambda2;
        double lambda3;
        double lambda4;
        double lambda5;

        double mW;

        double vev;
        double g1, g2, g3;
        double Yd2[3][3], Ye2[3][3], Yu2[3][3];

        double get_vev()        const { return vev;      } 
        double get_g1()       const { return g1; }
        double get_g2()       const { return g2; }
        double get_g3()       const { return g3; }
  
        double get_Yd2(int i, int j)       const { return Yd2[i][j];}
        double get_Yu2(int i, int j)       const { return Yu2[i][j];}
        double get_Ye2(int i, int j)       const { return Ye2[i][j];}

        double get_mh0(int i)           const {
                                                if      (i==1){ return mh0; } // Neutral Higgs(1)
                                                else if (i==2){ return mH0; } // Neutral Higgs(2)
                                                else { utils_error().raise(LOCAL_INFO,"Invalid index input to get_mh0! Please check index range limits in wrapper SubSpectrum class!"); return -1; } // Should not return.
                                              }
        double get_mA0()           const { return mA0; }
        double get_mC()            const { return mC; }
        double get_tanb()                     const { return tanb; }
        double get_m12_2()                       const { return m12_2; }
        double get_lambda6()                     const { return lambda6; }
        double get_lambda7()                     const { return lambda7; }
        double get_alpha()                       const { return alpha; }
        double get_yukawaCoupling()              const { return yukawaCoupling; }
        
        double get_lambda1()                     const { return lambda1;}
        double get_lambda2()                     const { return lambda2;}
        double get_lambda3()                     const { return lambda3;}
        double get_lambda4()                     const { return lambda4;}
        double get_lambda5()                     const { return lambda5;}
        double get_MW_pole()                    const { return mW; } // REQUIRED output of subspectrum
        double get_sinthW2_DRbar() const {
                                            double sg1 = 0.6 * Utils::sqr(get_g1());
                                            return sg1 / (sg1 + Utils::sqr(get_g2()));
                                          }
      
        void set_mh0(double in, int i)            {
         if      (i==1){ mh0=in; } // Neutral Higgs(1)
         else if (i==2){ mH0=in;} // Neutral Higgs(2)
         else { utils_error().raise(LOCAL_INFO,"Invalid index input to set_mh0! Please check index range limits in wrapper SubSpectrum class!"); } // Should not return.
        }
        void set_mA0(double in)               { mA0=in; }
        void set_mC(double in)                { mC=in; }
        void set_tanb(double in)                      { tanb=in; }
        void set_m12_2(double in )                       { m12_2=in; }
        void set_lambda6(double in)                      { lambda6=in; }
        void set_lambda7(double in)                      { lambda7=in; }
        void set_alpha(double in)                        { alpha=in; }
        void set_yukawaCoupling(double in)               { yukawaCoupling=in; }

        void set_lambda1(double in)               { lambda1=in; }
        void set_lambda2(double in)               { lambda2=in; }
        void set_lambda3(double in)               { lambda3=in; }
        void set_lambda4(double in)               { lambda4=in; }
        void set_lambda5(double in)               { lambda5=in; }

        // void set_HiggsPoleMass(double in)   { HiggsPoleMass=in; }

        void set_vev(double in)             { vev=in; } 
        void set_g1(double in)              { g1=in; }
        void set_g2(double in)              { g2=in; }
        void set_g3(double in)              { g3=in; }

        void set_Yd2(double in, int i, int j)       { Yd2[i][j]=in;}
        void set_Yu2(double in, int i, int j)       { Yu2[i][j]=in;}
        void set_Ye2(double in, int i, int j)       { Ye2[i][j]=in;}

        void set_MW_pole(double in)       { mW=in;}

    };
    
    /// Forward declare the wrapper class so that we can use it
    /// as the template parameter for the SpecTraits specialisation.
    class THDMSimpleSpec;
  }
  
  /// Specialisation of traits class needed to inform base spectrum class of the Model and Input types
  template <>
  struct SpecTraits<Models::THDMSimpleSpec>
  {
    static std::string name() { return "THDMSimpleSpec"; }
    typedef SpectrumContents::THDM Contents;
    typedef Models::THDMModel Model;
    typedef DummyInput              Input; // DummyInput is just an empty struct
  };
  
  namespace Models
  {
    class THDMSimpleSpec : public Spec<THDMSimpleSpec>
    {
    private:
      Model model;
      Input dummyinput;
      
    public:
      /// @{ Constructors/destructors
      THDMSimpleSpec(const Model& m)
      : model(m)
      , dummyinput()
      {}
      /// @}
      
      // Functions to interface Model and Input objects with the base 'Spec' class
      Model& get_Model() { return model; }
      Input& get_Input() { return dummyinput; /*unused here, but needs to be defined for the interface*/ }
      const Model& get_Model() const { return model; }
      const Input& get_Input() const { return dummyinput; /*unused here, but needs to be defined for the interface*/ }
      
      /// @{ Map fillers
      static GetterMaps fill_getter_maps()
      {
        GetterMaps map_collection;
        typedef typename MTget::FInfo2W FInfo2W;
        static const int i012v[] = {0,1,2};
        static const std::set<int> i012(i012v, Utils::endA(i012v));

         typedef MTget::FInfo1 FInfo1;
         typedef MTget::FInfo2 FInfo2;

         // Can't use c++11 initialiser lists, se have to initialise the index sets like this.
         static const int i12v[] = {1,2};
         static const std::set<int> i12(i12v, Utils::endA(i12v));

         static const int i123v[] = {1,2,3};
         static const std::set<int> i123(i123v, Utils::endA(i123v));

         static const int i1234v[] = {1,2,3,4};
         static const std::set<int> i1234(i1234v, Utils::endA(i1234v));

         static const int i123456v[] = {1,2,3,4,5,6};
         static const std::set<int> i123456(i123456v, Utils::endA(i123456v));

        map_collection[Par::dimensionless].map0["y_type"]       = &Model::get_yukawaCoupling;

        // Running parameters
         {
            // MTget::fmap0 tmp_map;
            // ##NIL
            // map_collection[Par::mass2].map0 = tmp_map;
         }
         {
            // MTget::fmap2 tmp_map;
            // ##NIL
            // map_collection[Par::mass2].map2 = tmp_map;
         }
         {
            MTget::fmap0 tmp_map;
            tmp_map["vev"]= &Model::get_vev;
            tmp_map["lambda_1"]= &Model::get_lambda1;
            tmp_map["lambda_2"]= &Model::get_lambda2;
            tmp_map["lambda_3"]= &Model::get_lambda3;
            tmp_map["lambda_4"]= &Model::get_lambda4;
            tmp_map["lambda_5"]= &Model::get_lambda5;
            tmp_map["lambda_6"]= &Model::get_lambda6;
            tmp_map["lambda_7"]= &Model::get_lambda7;
            tmp_map["m12_2"]= &Model::get_m12_2;
            map_collection[Par::mass1].map0 = tmp_map;
         }
         {
           // ##NIL
            // MTget::fmap2 tmp_map; 
            // tmp_map["TYd"]= FInfo2( &Model::get_TYd, i123, i123);
            // tmp_map["TYe"]= FInfo2( &Model::get_TYe, i123, i123);
            // tmp_map["TYu"]= FInfo2( &Model::get_TYu, i123, i123);
            // tmp_map["ad"] = FInfo2( &Model::get_TYd, i123, i123);
            // tmp_map["ae"] = FInfo2( &Model::get_TYe, i123, i123);
            // tmp_map["au"] = FInfo2( &Model::get_TYu, i123, i123);
            // map_collection[Par::mass1].map2 = tmp_map;
         }
         {
            MTget::fmap0 tmp_map;
            tmp_map["g1"]= &Model::get_g1;
            tmp_map["g2"]= &Model::get_g2;
            tmp_map["g3"]= &Model::get_g3;
            tmp_map["tanb"]= &Model::get_tanb;
            tmp_map["alpha"]= &Model::get_alpha; // Special entry for reproducing MINPAR entry in SLHA
            tmp_map["sinW2"]= &Model::get_sinthW2_DRbar;
            map_collection[Par::dimensionless].map0 = tmp_map;
         }
         {
            MTget::fmap2 tmp_map;
            tmp_map["Yd2"]= FInfo2( &Model::get_Yd2, i123, i123);
            tmp_map["Yu2"]= FInfo2( &Model::get_Yu2, i123, i123);
            tmp_map["Ye2"]= FInfo2( &Model::get_Ye2, i123, i123);
            map_collection[Par::dimensionless].map2 = tmp_map;
         }

         // "Physical" parameters
         {
            MTget::fmap0 tmp_map;
            tmp_map["A0"] = &Model::get_mA0;//get_MAh_pole;
            tmp_map["H+"] = &Model::get_mC;//get_MHpm_pole;
            // Antiparticle label
            tmp_map["H-"] = &Model::get_mC;//get_MHpm_pole;
            tmp_map["W+"] = &Model::get_MW_pole;
            map_collection[Par::Pole_Mass].map0 = tmp_map;
         }
         {
            MTget::fmap1 tmp_map;
            tmp_map["h0"] =    FInfo1( &Model::get_mh0, i12 );

            map_collection[Par::Pole_Mass].map1 = tmp_map;
         }
         {
            // MTget::fmap2 tmp_map;
            // tmp_map["h0"] =    FInfo2( &Model::get_ZH_pole_slha, i12, i12);
            // tmp_map["A0"] =    FInfo2( &Model::get_ZA_pole_slha, i12, i12);
            // tmp_map["H+"] =    FInfo2( &Model::get_ZP_pole_slha, i12, i12);
            // map_collection[Par::Pole_Mixing].map2 = tmp_map;
         }

      }
      
      static SetterMaps fill_setter_maps()
      {
        SetterMaps map_collection;

        // typedef typename MTset::FInfo2W FInfo2W;
        // static const int i012v[] = {0,1,2};

        //  typedef MTset::FInfo1 FInfo1;
        //  typedef MTset::FInfo2 FInfo2;

        //  // Can't use c++11 initialiser lists, se have to initialise the index sets like this.
        //  static const int i12v[] = {1,2};
        //  static const std::set<int> i12(i12v, Utils::endA(i12v));

        //  static const int i123v[] = {1,2,3};
        //  static const std::set<int> i123(i123v, Utils::endA(i123v));

        //  static const int i1234v[] = {1,2,3,4};
        //  static const std::set<int> i1234(i1234v, Utils::endA(i1234v));

        //  static const int i123456v[] = {1,2,3,4,5,6};
        //  static const std::set<int> i123456(i123456v, Utils::endA(i123456v));

         typedef typename MTset::FInfo2 FInfo2;

         typedef typename MTset::FInfo1M FInfo1M;
         typedef typename MTset::FInfo2M FInfo2M;

         static const std::set<int> i01 = initSet(0,1);
         static const std::set<int> i012 = initSet(0,1,2);
         static const std::set<int> i0123 = initSet(0,1,2,3);
         static const std::set<int> i012345 = initSet(0,1,2,3,4,5);

        map_collection[Par::dimensionless].map0["y_type"]       = &Model::set_yukawaCoupling;

        // Running parameters
         {
            // MTget::fmap0 tmp_map;
            // ##NIL
            // map_collection[Par::mass2].map0 = tmp_map;
         }
         {
            // MTget::fmap2 tmp_map;
            // ##NIL
            // map_collection[Par::mass2].map2 = tmp_map;
         }
         {
            MTset::fmap0 tmp_map;
            tmp_map["vev"]= &Model::set_vev;
            tmp_map["lambda_1"]= &Model::set_lambda1;
            tmp_map["lambda_2"]= &Model::set_lambda2;
            tmp_map["lambda_3"]= &Model::set_lambda3;
            tmp_map["lambda_4"]= &Model::set_lambda4;
            tmp_map["lambda_5"]= &Model::set_lambda5;
            tmp_map["lambda_6"]= &Model::set_lambda6;
            tmp_map["lambda_7"]= &Model::set_lambda7;
            tmp_map["m12_2"]= &Model::set_m12_2;
            map_collection[Par::mass1].map0 = tmp_map;
         }
         {
           // ##NIL
            // MTget::fmap2 tmp_map; 
            // tmp_map["TYd"]= FInfo2( &Model::get_TYd, i123, i123);
            // tmp_map["TYe"]= FInfo2( &Model::get_TYe, i123, i123);
            // tmp_map["TYu"]= FInfo2( &Model::get_TYu, i123, i123);
            // tmp_map["ad"] = FInfo2( &Model::get_TYd, i123, i123);
            // tmp_map["ae"] = FInfo2( &Model::get_TYe, i123, i123);
            // tmp_map["au"] = FInfo2( &Model::get_TYu, i123, i123);
            // map_collection[Par::mass1].map2 = tmp_map;
         }
         {
            MTset::fmap0 tmp_map;
            tmp_map["g1"]= &Model::set_g1;
            tmp_map["g2"]= &Model::set_g2;
            tmp_map["g3"]= &Model::set_g3;
            tmp_map["tanb"]= &Model::set_tanb;
            tmp_map["alpha"]= &Model::set_alpha; // Special entry for reproducing MINPAR entry in SLHA
            map_collection[Par::dimensionless].map0 = tmp_map;
         }
         {
           
            MTset::fmap2 tmp_map;
            // tmp_map["Yd2"]= FInfo2( &Model::set_Yd2, i012, i012);
            // tmp_map["Yu2"]= FInfo2( &Model::set_Yu2, i012, i012);
            // tmp_map["Ye2"]= FInfo2( &Model::set_Ye2, i012, i012);
            map_collection[Par::dimensionless].map2 = tmp_map;
         }

         // "Physical" parameters
         {
            MTset::fmap0 tmp_map;
            tmp_map["A0"] = &Model::set_mA0;//get_MAh_pole;
            tmp_map["H+"] = &Model::set_mC;//get_MHpm_pole;
            // Antiparticle label
            tmp_map["H-"] = &Model::set_mC;//get_MHpm_pole;
            tmp_map["W+"] = &Model::set_MW_pole;
            map_collection[Par::Pole_Mass].map0 = tmp_map;
         }
         {
            MTset::fmap1 tmp_map;
            // tmp_map["h0"] =    FInfo1( &Model::set_mh0, i12 );

            map_collection[Par::Pole_Mass].map1 = tmp_map;
         }
         {
            // MTget::fmap2 tmp_map;
            // tmp_map["h0"] =    FInfo2( &Model::get_ZH_pole_slha, i12, i12);
            // tmp_map["A0"] =    FInfo2( &Model::get_ZA_pole_slha, i12, i12);
            // tmp_map["H+"] =    FInfo2( &Model::get_ZP_pole_slha, i12, i12);
            // map_collection[Par::Pole_Mixing].map2 = tmp_map;
         }

        // typedef typename MTset::FInfo2W FInfo2W;
        // static const int i012v[] = {0,1,2};
        // static const std::set<int> i012(i012v, Utils::endA(i012v));

        // map_collection[Par::mass1].map0W["vev"]       = &Model::set_HiggsVEV;

        // map_collection[Par::dimensionless].map0W["g1"] = &Model::set_g1;
        // map_collection[Par::dimensionless].map0W["g2"] = &Model::set_g2;
        // map_collection[Par::dimensionless].map0W["g3"] = &Model::set_g3;
        // map_collection[Par::dimensionless].map0W["sinW2"] = &Model::set_sinW2;

        // // map_collection[Par::Pole_Mass].map0W["h0_1"]    = &Model::set_HiggsPoleMass;

        // map_collection[Par::dimensionless].map2W["Yd2"]= FInfo2W( &Model::set_Yd, i012, i012);
        // map_collection[Par::dimensionless].map2W["Yu2"]= FInfo2W( &Model::set_Yu, i012, i012);
        // map_collection[Par::dimensionless].map2W["Ye2"]= FInfo2W( &Model::set_Ye, i012, i012);

        // map_collection[Par::mass1].map0["mh0"]              = &Model::set_lightHiggsMass;
        // map_collection[Par::mass1].map0["mH0"]              = &Model::set_heavyHiggsMass;
        // map_collection[Par::mass1].map0["mA"]               = &Model::set_pseudoscalarHiggsMass;
        // map_collection[Par::mass1].map0["mC"]               = &Model::set_chargedHiggsMass;
        // map_collection[Par::dimensionless].map0["tanb"]     = &Model::set_tanBeta;
        // map_collection[Par::mass1].map0["m12_2"]            = &Model::set_m12_2;
        // map_collection[Par::mass1].map0["lambda_6"]         = &Model::set_lambda6;
        // map_collection[Par::mass1].map0["lambda_7"]         = &Model::set_lambda7;
        // map_collection[Par::dimensionless].map0["alpha"]    = &Model::set_alpha;
        // map_collection[Par::dimensionless].map0["y_type"]   = &Model::set_yukawaCoupling;
          
        // map_collection[Par::mass1].map0["lambda_1"]        = &Model::set_lambda1;
        // map_collection[Par::mass1].map0["lambda_2"]        = &Model::set_lambda2;
        // map_collection[Par::mass1].map0["lambda_3"]        = &Model::set_lambda3;
        // map_collection[Par::mass1].map0["lambda_4"]        = &Model::set_lambda4;
        // map_collection[Par::mass1].map0["lambda_5"]        = &Model::set_lambda5;       
        
      return map_collection;
      }
      /// @}
      
    };
    
  } // end Models namespace
} // end Gambit namespace

#endif
