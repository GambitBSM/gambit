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
///  \author Filip Rajec
///          (filip.rajec@adelaide.edu.au)
///  \date Feb 2019
///
///  *********************************************

#ifndef __THDDMSimpleSpecSM_hpp__
#define __THDDMSimpleSpecSM_hpp__

#include "gambit/Elements/spec.hpp"
#include "gambit/Models/SimpleSpectra/SLHASimpleSpec.hpp"
#include "gambit/Models/SpectrumContents/RegisteredSpectra.hpp"
#include "gambit/Elements/thdm_slhahelp.hpp"
/*
namespace Gambit
{     
   namespace Models
   {
      /// Simple extension of the SMHiggsSimpleSpec "model object"
      /// to include THDM parameters for models whwere there is no running.
      struct THDMModel
      {
        double mh0, mH0, mA0, mC, mG0, mGC;
        double lambda1, lambda2, lambda3, lambda4, lambda5, lambda6, lambda7;
        double tanb, alpha, m11_2, m12_2, m22_2;
        double Lambda1, Lambda2, Lambda3, Lambda4, Lambda5, Lambda6, Lambda7;
        double M11_2, M12_2, M22_2;
        double mW;
        double vev;
        double g1, g2, g3, sinW2;
        double Yd1[3], Ye1[3], Yu1[3];
        double Yd2[3], Ye2[3], Yu2[3];
        double yukawaCoupling;
      };
  
      /// Forward declare the wrapper class so that we can use it
      /// as the template parameter for the SpecTraits specialisation. 
      class THDMSimpleSpecSM;  
   }

   /// Specialisation of traits class needed to inform base spectrum class of the Model and Input types
   template <>
   struct SpecTraits<Models::THDMSimpleSpecSM> : DefaultTraits
   {
      static std::string name() { return "THDMSimpleSpecSM"; }
      typedef SpectrumContents::THDM Contents;
   };

   namespace Models
   { 
      class THDMSimpleSpecSM : public Spec<THDMSimpleSpecSM> 
      {
         private:
            THDMModel params;
            typedef THDMSimpleSpecSM Self;

         public:
            /// @{ Constructors/destructors
            THDMSimpleSpecSM(const THDMModel& p)
                : params(p)
            {}

            static int index_offset() {return -1;}

            /// Add SLHAea object to another
            virtual void add_to_SLHAea(int slha_version, SLHAea::Coll& slha) const override {
               // Add SPINFO data if not already present
               SLHAea_add_GAMBIT_SPINFO(slha);

               // All MSSM blocks
               slhahelp::add_THDM_spectrum_to_SLHAea(*this, slha, slha_version);
            }

            /// Add SLHAea object to another
            virtual double GetScale() const override { 
               // set default scale for inputs as 2 GeV
               const double mu = 2;
               return mu;
            }

            /// @}

            // /// Wrapper-side interface functions to parameter object
            /// @{ getter functions
            double get_vev()      const { return params.vev;      } 
            double get_g1()       const { return params.g1; }
            double get_g2()       const { return params.g2; }
            double get_g3()       const { return params.g3; }
            double get_sinW2()    const { return params.sinW2; }

            double get_Yd(int i, int j)       const { if (i==j){return params.Yd[i];}else{return 0;} }
            double get_Yu(int i, int j)       const { if (i==j){return params.Yu[i];}else{return 0;} }
            double get_Ye(int i, int j)       const { if (i==j){return params.Ye[i];}else{return 0;} }

            double get_mh0(int i)           const {
                                                if      (i==0){ return params.mh0; } // Neutral Higgs(1)
                                                else if (i==1){ return params.mH0; } // Neutral Higgs(2)
                                                else { utils_error().raise(LOCAL_INFO,"Invalid index input to get_mh0! Please check index range limits in wrapper SubSpectrum class!"); return -1; } // Should not return.
                                                }
            double get_mA0()                const { return params.mA0; }
            double get_mC()                 const { return params.mC; }
            double get_mG0()                const { return params.mG0; }
            double get_mGC()                const { return params.mGC; }
            double get_tanb()               const { return params.tanb; }
            double get_alpha()              const { return params.alpha; }
            double get_yukawaCoupling()     const { return params.yukawaCoupling; }

            double get_lambda1()            const { return params.lambda1;}
            double get_lambda2()            const { return params.lambda2;}
            double get_lambda3()            const { return params.lambda3;}
            double get_lambda4()            const { return params.lambda4;}
            double get_lambda5()            const { return params.lambda5;}
            double get_lambda6()            const { return params.lambda6;}
            double get_lambda7()            const { return params.lambda7;}
            double get_m11_2()              const { return params.m11_2; }
            double get_m12_2()              const { return params.m12_2; }
            double get_m22_2()              const { return params.m22_2; }
            double get_MW_pole()            const { return params.mW; } // REQUIRED output of subspectrum
            double get_sinthW2_DRbar()      const {
                                                double sg1 = 0.6 * Utils::sqr(get_g1());
                                                return sg1 / (sg1 + Utils::sqr(get_g2()));
                                                }
            double get_Lambda1()            const { return params.Lambda1;}
            double get_Lambda2()            const { return params.Lambda2;}
            double get_Lambda3()            const { return params.Lambda3;}
            double get_Lambda4()            const { return params.Lambda4;}
            double get_Lambda5()            const { return params.Lambda5;}
            double get_Lambda6()            const { return params.Lambda6;}
            double get_Lambda7()            const { return params.Lambda7;}
            double get_M11_2()              const { return params.M11_2; }
            double get_M12_2()              const { return params.M12_2; }
            double get_M22_2()              const { return params.M22_2; }

            ///  @}

            ///  @{ setter functions

            void set_mh0(double in, int i) {
                if      (i==1){ params.mh0=in; }    // Neutral Higgs(1)
                else if (i==2){ params.mH0=in;}     // Neutral Higgs(2)
                else { utils_error().raise(LOCAL_INFO,"Invalid index input to set_mh0! Please check index range limits in wrapper SubSpectrum class!"); } // Should not return.
            }

            void set_mA0(double in)                         { params.mA0=in; }
            void set_mC(double in)                          { params.mC=in; }
            void set_mG0(double in)                         { params.mG0=in; }
            void set_mGC(double in)                         { params.mGC=in; }
            void set_tanb(double in)                        { params.tanb=in; }
            void set_yukawaCoupling(double in)              { params.yukawaCoupling=in; }

            void set_lambda1(double in)               { params.lambda1=in; }
            void set_lambda2(double in)               { params.lambda2=in; }
            void set_lambda3(double in)               { params.lambda3=in; }
            void set_lambda4(double in)               { params.lambda4=in; }
            void set_lambda5(double in)               { params.lambda5=in; }
            void set_lambda6(double in)               { params.lambda6=in; }
            void set_lambda7(double in)               { params.lambda7=in; }
            void set_m11_2(double in )                { params.m11_2=in; }
            void set_m22_2(double in )                { params.m22_2=in; }
            void set_m12_2(double in )                { params.m12_2=in; }

            void set_Lambda1(double in)               { params.Lambda1=in; }
            void set_Lambda2(double in)               { params.Lambda2=in; }
            void set_Lambda3(double in)               { params.Lambda3=in; }
            void set_Lambda4(double in)               { params.Lambda4=in; }
            void set_Lambda5(double in)               { params.Lambda5=in; }
            void set_Lambda6(double in)               { params.Lambda6=in; }
            void set_Lambda7(double in)               { params.Lambda7=in; }
            void set_M11_2(double in )                { params.M11_2=in; }
            void set_M22_2(double in )                { params.M22_2=in; }
            void set_M12_2(double in )                { params.M12_2=in; }

            void set_vev(double in)             { params.vev=in; } 
            void set_g1(double in)              { params.g1=in; }
            void set_g2(double in)              { params.g2=in; }
            void set_g3(double in)              { params.g3=in; }

            void set_MW_pole(double in)       { params.mW=in;}
            void set_sinW2(double in)       { params.sinW2=in; }

            void set_Yd(double in, int i, int j)       { if (i==j){params.Yd[i]=in;}}
            void set_Yu(double in, int i, int j)       { if (i==j){params.Yu[i]=in;}}
            void set_Ye(double in, int i, int j)       { if (i==j){params.Ye[i]=in;}}

            ///  @}

            /// @{ Map fillers
            static GetterMaps fill_getter_maps()
            {
               GetterMaps getters;
               typedef typename MTget::FInfo1W FInfo1W;
               static const int i12v[] = {0,1};
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
               getters[mass1]        .map0W["m11_2"]  = &Self::get_m11_2;
               getters[mass1]        .map0W["m22_2"]  = &Self::get_m22_2;
               getters[mass1]        .map0W["m12_2"]  = &Self::get_m12_2;

               getters[mass1]        .map0W["Lambda_1"]  = &Self::get_Lambda1;
               getters[mass1]        .map0W["Lambda_2"]  = &Self::get_Lambda2;
               getters[mass1]        .map0W["Lambda_3"]  = &Self::get_Lambda3;
               getters[mass1]        .map0W["Lambda_4"]  = &Self::get_Lambda4;
               getters[mass1]        .map0W["Lambda_5"]  = &Self::get_Lambda5;
               getters[mass1]        .map0W["Lambda_6"]  = &Self::get_Lambda6;
               getters[mass1]        .map0W["Lambda_7"]  = &Self::get_Lambda7;
               getters[mass1]        .map0W["M11_2"]  = &Self::get_M11_2;
               getters[mass1]        .map0W["M22_2"]  = &Self::get_M22_2;
               getters[mass1]        .map0W["M12_2"]  = &Self::get_M12_2;

               getters[dimensionless].map0W["tanb"] = &Self::get_tanb;

               getters[Pole_Mass].map1W["h0"]    = FInfo1W( &Self::get_mh0, i12 );
               getters[Pole_Mass].map0W["A0"]    = &Self::get_mA0;
               getters[Pole_Mass].map0W["H+"]    = &Self::get_mC;
               getters[Pole_Mass].map0W["H-"]    = &Self::get_mC;
               getters[Pole_Mass].map0W["G0"]    = &Self::get_mG0;
               getters[Pole_Mass].map0W["G+"]    = &Self::get_mGC;
               getters[Pole_Mass].map0W["G-"]    = &Self::get_mGC;
               getters[Pole_Mass].map0W["W+"]    = &Self::get_MW_pole;
               getters[Pole_Mass].map0W["W-"]    = &Self::get_MW_pole;

               getters[mass1].map1W["h0"]    = FInfo1W( &Self::get_mh0, i12 );
               getters[mass1].map0W["A0"]    = &Self::get_mA0;
               getters[mass1].map0W["H+"]    = &Self::get_mC;
               getters[mass1].map0W["H-"]    = &Self::get_mC;
               getters[mass1].map0W["G0"]    = &Self::get_mG0;
               getters[mass1].map0W["G+"]    = &Self::get_mGC;
               getters[mass1].map0W["G-"]    = &Self::get_mGC;
               getters[mass1].map0W["W+"]    = &Self::get_MW_pole;
               getters[mass1].map0W["W-"]    = &Self::get_MW_pole;

               getters[dimensionless].map0W["g1"] = &Self::get_g1;
               getters[dimensionless].map0W["g2"] = &Self::get_g2;
               getters[dimensionless].map0W["g3"] = &Self::get_g3;
               getters[dimensionless].map0W["sinW2"] = &Self::get_sinW2;
               getters[dimensionless].map0W["alpha"] = &Self::get_alpha;

               getters[dimensionless].map0W["yukawaCoupling"] = &Self::get_yukawaCoupling;
              
               getters[dimensionless].map2W["Yd"]= FInfo2W( &Self::get_Yd, i012, i012);
               getters[dimensionless].map2W["Yu"]= FInfo2W( &Self::get_Yu, i012, i012);
               getters[dimensionless].map2W["Ye"]= FInfo2W( &Self::get_Ye, i012, i012);

               return getters;
            }

            static SetterMaps fill_setter_maps()
            {
               SetterMaps setters;
               typedef typename MTset::FInfo1W FInfo1W;
               static const int i12v[] = {0,1};
               static const std::set<int> i12(i12v, Utils::endA(i12v));

               typedef typename MTset::FInfo2W FInfo2W;
               static const int i012v[] = {0,1,2};
               static const std::set<int> i012(i012v, Utils::endA(i012v));
              
               using namespace Par;

               setters[mass1].map0W["vev"]       = &Self::set_vev;
               setters[mass1].map0W["lambda_1"]  = &Self::set_lambda1;
               setters[mass1].map0W["lambda_2"]  = &Self::set_lambda2;
               setters[mass1].map0W["lambda_3"]  = &Self::set_lambda3;
               setters[mass1].map0W["lambda_4"]  = &Self::set_lambda4;
               setters[mass1].map0W["lambda_5"]  = &Self::set_lambda5;
               setters[mass1].map0W["lambda_6"]  = &Self::set_lambda6;
               setters[mass1].map0W["lambda_7"]  = &Self::set_lambda7;
               setters[mass1].map0W["m11_2"]     = &Self::set_m11_2;
               setters[mass1].map0W["m22_2"]     = &Self::set_m22_2;
               setters[mass1].map0W["m12_2"]     = &Self::set_m12_2;

               setters[mass1].map0W["Lambda_1"]  = &Self::set_Lambda1;
               setters[mass1].map0W["Lambda_2"]  = &Self::set_Lambda2;
               setters[mass1].map0W["Lambda_3"]  = &Self::set_Lambda3;
               setters[mass1].map0W["Lambda_4"]  = &Self::set_Lambda4;
               setters[mass1].map0W["Lambda_5"]  = &Self::set_Lambda5;
               setters[mass1].map0W["Lambda_6"]  = &Self::set_Lambda6;
               setters[mass1].map0W["Lambda_7"]  = &Self::set_Lambda7;
               setters[mass1].map0W["M11_2"]     = &Self::set_M11_2;
               setters[mass1].map0W["M22_2"]     = &Self::set_M22_2;
               setters[mass1].map0W["M12_2"]     = &Self::set_M12_2;

               setters[dimensionless].map0W["tanb"] = &Self::set_tanb;

               setters[dimensionless].map0W["g1"] = &Self::set_g1;
               setters[dimensionless].map0W["g2"] = &Self::set_g2;
               setters[dimensionless].map0W["g3"] = &Self::set_g3;
               setters[dimensionless].map0W["sinW2"] = &Self::set_sinW2;

               setters[dimensionless].map0W["yukawaCoupling"] = &Self::set_yukawaCoupling;

               setters[mass1].map1W["h0"]    = FInfo1W( &Self::set_mh0, i12 );
               setters[mass1].map0W["A0"]    = &Self::set_mA0;
               setters[mass1].map0W["H+"]    = &Self::set_mC;
               setters[mass1].map0W["H-"]    = &Self::set_mC;
               setters[mass1].map0W["G0"]    = &Self::set_mG0;
               setters[mass1].map0W["G+"]    = &Self::set_mGC;
               setters[mass1].map0W["G-"]    = &Self::set_mGC;
               setters[mass1].map0W["W+"]    = &Self::set_MW_pole;
               setters[mass1].map0W["W-"]    = &Self::set_MW_pole;
               
               setters[Pole_Mass].map1W["h0"]    = FInfo1W( &Self::set_mh0, i12 );
               setters[Pole_Mass].map0W["A0"]    = &Self::set_mA0;
               setters[Pole_Mass].map0W["H+"]    = &Self::set_mC;
               setters[Pole_Mass].map0W["H-"]    = &Self::set_mC;
               setters[Pole_Mass].map0W["G0"]    = &Self::set_mG0;
               setters[Pole_Mass].map0W["G+"]    = &Self::set_mGC;
               setters[Pole_Mass].map0W["G-"]    = &Self::set_mGC;
               setters[Pole_Mass].map0W["W+"]    = &Self::set_MW_pole;
               setters[Pole_Mass].map0W["W-"]    = &Self::set_MW_pole;
   
               setters[dimensionless].map2W["Yd"]= FInfo2W( &Self::set_Yd, i012, i012);
               setters[dimensionless].map2W["Yu"]= FInfo2W( &Self::set_Yu, i012, i012);
               setters[dimensionless].map2W["Ye"]= FInfo2W( &Self::set_Ye, i012, i012);

               return setters;
            }
            /// @}

        }; 

   } // end Models namespace
} // end Gambit namespace
*/
#endif
