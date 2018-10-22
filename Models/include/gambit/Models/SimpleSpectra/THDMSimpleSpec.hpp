//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  A simple SubSpectrum wrapper for the THDM.
///  No RGEs included.
///
///  *********************************************
///
///  Authors: 
///  <!-- add name and date if you modify -->
///   
///  \author Ben Farmer
///          (benjamin.farmer@fysik.su.se)
///  \date 2015 May 
///
///  *********************************************

#ifndef __THDDMSimpleSpec_hpp__
#define __THDDMSimpleSpec_hpp__

#include "gambit/Elements/spec.hpp"

#include "gambit/Models/SpectrumContents/RegisteredSpectra.hpp"

namespace Gambit
{     
   namespace Models
   {
      /// Simple extension of the SMHiggsSimpleSpec "model object"
      /// to include THDM parameters
      /// We could easily just put these in the wrapper itself, but
      /// I am leaving them in a separate struct for the sake of building
      /// up examples towards a more complicated "model" object
      struct THDMModel
      {
        double mh0;
        double mH0;
        double mA0;
        double mC;
        
        double lambda1;
        double lambda2;
        double lambda3;
        double lambda4;
        double lambda5;
        double lambda6;
        double lambda7;

        double tanb;
        double alpha;
        double m12_2;

        double mW;

        double vev;
        double g1, g2, g3, sinW2;
        double Yd[3], Ye[3], Yu[3];

        double yukawaCoupling;
      };
     
  
      /// Forward declare the wrapper class so that we can use it
      /// as the template parameter for the SpecTraits specialisation. 
      class THDMSimpleSpec;  
   }

   /// Specialisation of traits class needed to inform base spectrum class of the Model and Input types
   template <>
   struct SpecTraits<Models::THDMSimpleSpec> : DefaultTraits
   {
      static std::string name() { return "THDMSimpleSpec"; }
      typedef SpectrumContents::THDM Contents;
   };

   namespace Models
   { 
      class THDMSimpleSpec : public Spec<THDMSimpleSpec> 
      {
         private:
            THDMModel params;

            typedef THDMSimpleSpec Self;

         public:
            /// @{ Constructors/destructors
            THDMSimpleSpec(const THDMModel& p)
                : params(p)
            {}

            static int index_offset() {return -1;}

            /// @}

            // /// Wrapper-side interface functions to parameter object
            double get_vev()        const { return params.vev;      } 
            double get_g1()       const { return params.g1; }
            double get_g2()       const { return params.g2; }
            double get_g3()       const { return params.g3; }
            double get_sinW2()       const { return params.sinW2; }

            double get_Yd(int i, int j)       const { if (i==j){return params.Yd[i];}else{return 0;} }
            double get_Yu(int i, int j)       const { if (i==j){return params.Yu[i];}else{return 0;} }
            double get_Ye(int i, int j)       const { if (i==j){return params.Ye[i];}else{return 0;} }


            // void set_vev(double in)        { params.vev=in;      } 
            // void set_g1(double in)        { params.g1=in; }
            // void set_g2(double in)        { params.g2=in; }
            // void set_g3(double in)       { params.g3=in; }
            // void set_sinW2(double in)       { params.sinW2=in; }

            // void set_Yd(double in, int i, int j)       { if (i==j){params.Yd[i]=in;}}
            // void set_Yu(double in, int i, int j)       { if (i==j){params.Yu[i]=in;}}
            // void set_Ye(double in, int i, int j)       { if (i==j){params.Ye[i]=in;}}


            double get_mh0(int i)           const {
                                                if      (i==1){ return params.mh0; } // Neutral Higgs(1)
                                                else if (i==2){ return params.mH0; } // Neutral Higgs(2)
                                                else { utils_error().raise(LOCAL_INFO,"Invalid index input to get_mh0! Please check index range limits in wrapper SubSpectrum class!"); return -1; } // Should not return.
                                                }
            double get_mA0()           const { return params.mA0; }
            double get_mC()            const { return params.mC; }
            double get_tanb()                     const { return params.tanb; }
            double get_alpha()                     const { return params.alpha; }
            double get_m12_2()                       const { return params.m12_2; }
            double get_lambda6()                     const { return params.lambda6; }
            double get_lambda7()                     const { return params.lambda7; }
            double get_yukawaCoupling()              const { return params.yukawaCoupling; }

            double get_lambda1()                     const { return params.lambda1;}
            double get_lambda2()                     const { return params.lambda2;}
            double get_lambda3()                     const { return params.lambda3;}
            double get_lambda4()                     const { return params.lambda4;}
            double get_lambda5()                     const { return params.lambda5;}
            double get_MW_pole()                    const { return params.mW; } // REQUIRED output of subspectrum
            double get_sinthW2_DRbar() const {
                                            double sg1 = 0.6 * Utils::sqr(get_g1());
                                            return sg1 / (sg1 + Utils::sqr(get_g2()));
                                            }

            void set_mh0(double in, int i)            {
            if      (i==1){ params.mh0=in; } // Neutral Higgs(1)
            else if (i==2){ params.mH0=in;} // Neutral Higgs(2)
            else { utils_error().raise(LOCAL_INFO,"Invalid index input to set_mh0! Please check index range limits in wrapper SubSpectrum class!"); } // Should not return.
            }
            void set_mA0(double in)                         { params.mA0=in; }
            void set_mC(double in)                          { params.mC=in; }
            void set_tanb(double in)                        { params.tanb=in; }
            void set_m12_2(double in )                      { params.m12_2=in; }
            void set_lambda6(double in)                     { params.lambda6=in; }
            void set_lambda7(double in)                     { params.lambda7=in; }
            void set_yukawaCoupling(double in)              { params.yukawaCoupling=in; }

            void set_lambda1(double in)               { params.lambda1=in; }
            void set_lambda2(double in)               { params.lambda2=in; }
            void set_lambda3(double in)               { params.lambda3=in; }
            void set_lambda4(double in)               { params.lambda4=in; }
            void set_lambda5(double in)               { params.lambda5=in; }

            void set_vev(double in)             { params.vev=in; } 
            void set_g1(double in)              { params.g1=in; }
            void set_g2(double in)              { params.g2=in; }
            void set_g3(double in)              { params.g3=in; }

            // void set_Yd(double in, int i, int j)       { Yd[i][j]=in;}
            // void set_Yu(double in, int i, int j)       { Yu[i][j]=in;}
            // void set_Ye(double in, int i, int j)       { Ye[i][j]=in;}

            void set_MW_pole(double in)       { params.mW=in;}

            void set_sinW2(double in)       { params.sinW2=in; }

            void set_Yd(double in, int i, int j)       { if (i==j){params.Yd[i]=in;}}
            void set_Yu(double in, int i, int j)       { if (i==j){params.Yu[i]=in;}}
            void set_Ye(double in, int i, int j)       { if (i==j){params.Ye[i]=in;}}

            /// @{ Map fillers
            static GetterMaps fill_getter_maps()
            {
               GetterMaps getters;
               typedef typename MTget::FInfo1W FInfo1W;
               static const int i12v[] = {1,2};
               static const std::set<int> i12(i12v, Utils::endA(i12v));

               typedef typename MTget::FInfo2W FInfo2W;
               static const int i012v[] = {0,1,2};
               static const std::set<int> i012(i012v, Utils::endA(i012v));

               using namespace Par;

               getters[mass1]        .map0W["vev"]       = &Self::get_vev;
               getters[mass1]        .map0W["lambda_1"]  = &Self::get_lambda1;
               getters[mass1]        .map0W["lambda_2"]  = &Self::get_lambda2;
               getters[mass1]        .map0W["lambda_3"]  = &Self::get_lambda3;
               getters[mass1]        .map0W["lambda_4"]  = &Self::get_lambda4;
               getters[mass1]        .map0W["lambda_5"]  = &Self::get_lambda5;
               getters[mass1]        .map0W["lambda_6"]  = &Self::get_lambda6;
               getters[mass1]        .map0W["lambda_7"]  = &Self::get_lambda7;
               getters[mass1]        .map0W["m12_2"]  = &Self::get_m12_2;

               getters[dimensionless].map0W["tanb"] = &Self::get_tanb;

               getters[Pole_Mass].map1W["h0"]    = FInfo1W( &Self::get_mh0, i12 );
               getters[Pole_Mass].map0W["A0"]    = &Self::get_mA0;
               getters[Pole_Mass].map0W["H+"]    = &Self::get_mC;
               getters[Pole_Mass].map0W["H-"]    = &Self::get_mC;
               getters[Pole_Mass].map0W["W+"]    = &Self::get_MW_pole;

               getters[dimensionless].map0W["g1"] = &Self::get_g1;
               getters[dimensionless].map0W["g2"] = &Self::get_g2;
               getters[dimensionless].map0W["g3"] = &Self::get_g3;
               getters[dimensionless].map0W["sinW2"] = &Self::get_sinW2;
               getters[dimensionless].map0W["alpha"] = &Self::get_alpha;
              
               getters[dimensionless].map2W["Yd"]= FInfo2W( &Self::get_Yd, i012, i012);
               getters[dimensionless].map2W["Yu"]= FInfo2W( &Self::get_Yu, i012, i012);
               getters[dimensionless].map2W["Ye"]= FInfo2W( &Self::get_Ye, i012, i012);

               return getters;
            }

            static SetterMaps fill_setter_maps()
            {
               SetterMaps setters;
               typedef typename MTset::FInfo1W FInfo1W;
               static const int i12v[] = {1,2};
               static const std::set<int> i12(i12v, Utils::endA(i12v));

               typedef typename MTset::FInfo2W FInfo2W;
               static const int i012v[] = {0,1,2};
               static const std::set<int> i012(i012v, Utils::endA(i012v));
              
               using namespace Par;

               /// REFLECT TO BELOW ///

               setters[mass1].map0W["vev"]       = &Self::set_vev;
               setters[mass1].map0W["lambda_1"]  = &Self::set_lambda1;
               setters[mass1].map0W["lambda_2"]  = &Self::set_lambda2;
               setters[mass1].map0W["lambda_3"]  = &Self::set_lambda3;
               setters[mass1].map0W["lambda_4"]  = &Self::set_lambda4;
               setters[mass1].map0W["lambda_5"]  = &Self::set_lambda5;
               setters[mass1].map0W["lambda_6"]  = &Self::set_lambda6;
               setters[mass1].map0W["lambda_7"]  = &Self::set_lambda7;
               setters[mass1].map0W["m12_2"]     = &Self::set_m12_2;

               setters[dimensionless].map0W["tanb"] = &Self::set_tanb;

               setters[dimensionless].map0W["g1"] = &Self::set_g1;
               setters[dimensionless].map0W["g2"] = &Self::set_g2;
               setters[dimensionless].map0W["g3"] = &Self::set_g3;
               setters[dimensionless].map0W["sinW2"] = &Self::set_sinW2;
               
               setters[Pole_Mass].map1W["h0"]    = FInfo1W( &Self::set_mh0, i12 );
               setters[Pole_Mass].map0W["A0"]    = &Self::set_mA0;
               setters[Pole_Mass].map0W["H+"]    = &Self::set_mC;
               setters[Pole_Mass].map0W["H-"]    = &Self::set_mC;
               setters[Pole_Mass].map0W["W+"]    = &Self::set_MW_pole;
   
               setters[dimensionless].map2W["Yd"]= FInfo2W( &Self::set_Yd, i012, i012);
               setters[dimensionless].map2W["Yu"]= FInfo2W( &Self::set_Yu, i012, i012);
               setters[dimensionless].map2W["Ye"]= FInfo2W( &Self::set_Ye, i012, i012);

               return setters;
            }
            /// @}

        }; 

   } // end Models namespace
} // end Gambit namespace

#endif
