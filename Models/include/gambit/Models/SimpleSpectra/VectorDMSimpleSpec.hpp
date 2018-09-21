//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  A simple SubSpectrum wrapper for the VectorDM
///  model. No RGEs included.
///
///  *********************************************
///
///  Authors: 
///  <!-- add name and date if you modify -->
///   
///  \author Ankit Beniwal
///          (ankit.beniwal@adelaide.edu.au)
///  \date 2016 Sep, 2017 Jun
///
///  \author Sanjay Bloor
///          (sanjay.bloor12@imperial.ac.uk)
///  \date 2018 Aug
///
///  *********************************************

#ifndef __VectorDMSimpleSpec_hpp__
#define __VectorDMSimpleSpec_hpp__

#include "gambit/Elements/spec.hpp"
#include "gambit/Models/SpectrumContents/RegisteredSpectra.hpp"

namespace Gambit
{     
   namespace Models
   {
      /// Simple extension of the SMHiggsSimpleSpec "model object"
      /// to include vector DM parameters
      /// We could easily just put these in the wrapper itself, but
      /// I am leaving them in a separate struct for the sake of building
      /// up examples towards a more complicated "model" object
      struct VectorDMModel
      {
         double HiggsPoleMass;
         double HiggsVEV;
         double VectorPoleMass;
         double VectorLambda;
         double HiggsPoleMass_1srd_low,HiggsPoleMass_1srd_high;
     
         double LambdaH;
         double VectorLambdaS;
         double g1, g2, g3, sinW2;
         double Yd[3], Ye[3], Yu[3];
      };
     
  
      /// Forward declare the wrapper class so that we can use it
      /// as the template parameter for the SpecTraits specialisation. 
      class VectorDMSimpleSpec;  
   }

   /// Specialisation of traits class needed to inform base spectrum class of the Model and Input types
   template <>
   struct SpecTraits<Models::VectorDMSimpleSpec> : DefaultTraits
   {
      static std::string name() { return "VectorDMSimpleSpec"; }
      typedef SpectrumContents::VectorDM Contents;
   };

   namespace Models
   { 
      class VectorDMSimpleSpec : public Spec<VectorDMSimpleSpec> 
      {
         private:
            VectorDMModel params;

            typedef VectorDMSimpleSpec Self;

         public:
            /// @{ Constructors/destructors
            VectorDMSimpleSpec(const VectorDMModel& p)
             : params(p)
            {}

            static int index_offset() {return -1;}
        
            /// @}
 
            /// Wrapper-side interface functions to parameter object
            double get_HiggsPoleMass()   const { return params.HiggsPoleMass; } 

            double get_HiggsPoleMass_1srd_low() const  { return params.HiggsPoleMass_1srd_low; }
            double get_HiggsPoleMass_1srd_high() const  { return params.HiggsPoleMass_1srd_high; }

            double get_HiggsVEV()        const { return params.HiggsVEV;      } 
            double get_VectorPoleMass() const { return params.VectorPoleMass; } 
            double get_lambda_hV()       const { return params.VectorLambda; }
            double get_lambda_h()       const { return params.LambdaH; }
            double get_g1()       const { return params.g1; }
            double get_g2()       const { return params.g2; }
            double get_g3()       const { return params.g3; }
            double get_sinW2()       const { return params.sinW2; }
           
            double get_Yd(int i, int j)       const { if (i==j){return params.Yd[i];}else{return 0;} }
            double get_Yu(int i, int j)       const { if (i==j){return params.Yu[i];}else{return 0;} }
            double get_Ye(int i, int j)       const { if (i==j){return params.Ye[i];}else{return 0;} }
           
            void set_HiggsPoleMass(double in)   { params.HiggsPoleMass=in; } 
            void set_HiggsPoleMass_1srd_low(double in)   { params.HiggsPoleMass_1srd_low=in; }
            void set_HiggsPoleMass_1srd_high(double in)   { params.HiggsPoleMass_1srd_high=in; }

            void set_HiggsVEV(double in)        { params.HiggsVEV=in;      } 
            void set_VectorPoleMass(double in) { params.VectorPoleMass=in; } 
            void set_lambda_hV(double in)       { params.VectorLambda=in; }
            void set_lambda_h(double in)       { params.LambdaH=in; }
            void set_g1(double in)        { params.g1=in; }
            void set_g2(double in)        { params.g2=in; }
            void set_g3(double in)       { params.g3=in; }
            void set_sinW2(double in)       { params.sinW2=in; }
           
            void set_Yd(double in, int i, int j)       { if (i==j){params.Yd[i]=in;}}
            void set_Yu(double in, int i, int j)       { if (i==j){params.Yu[i]=in;}}
            void set_Ye(double in, int i, int j)       { if (i==j){params.Ye[i]=in;}}

            /// @{ Map fillers
            static GetterMaps fill_getter_maps()
            {
               GetterMaps getters;
               typedef typename MTget::FInfo2W FInfo2W;
               static const int i012v[] = {0,1,2};
               static const std::set<int> i012(i012v, Utils::endA(i012v));

               using namespace Par;

               getters[mass1]        .map0W["vev"]       = &Self::get_HiggsVEV;
               getters[dimensionless].map0W["lambda_hV"] = &Self::get_lambda_hV;
               getters[Pole_Mass].map0W["V"]       = &Self::get_VectorPoleMass;               

               getters[Pole_Mass].map0W["h0_1"]    = &Self::get_HiggsPoleMass;
               getters[Pole_Mass_1srd_high].map0W["h0_1"]    = &Self::get_HiggsPoleMass_1srd_high;
               getters[Pole_Mass_1srd_low].map0W["h0_1"]    = &Self::get_HiggsPoleMass_1srd_low;
               
               getters[dimensionless].map0W["lambda_h"] = &Self::get_lambda_h;

               getters[dimensionless].map0W["g1"] = &Self::get_g1;
               getters[dimensionless].map0W["g2"] = &Self::get_g2;
               getters[dimensionless].map0W["g3"] = &Self::get_g3;
               getters[dimensionless].map0W["sinW2"] = &Self::get_sinW2;
              
               getters[dimensionless].map2W["Yd"]= FInfo2W( &Self::get_Yd, i012, i012);
               getters[dimensionless].map2W["Yu"]= FInfo2W( &Self::get_Yu, i012, i012);
               getters[dimensionless].map2W["Ye"]= FInfo2W( &Self::get_Ye, i012, i012);

               return getters;
            }

            static SetterMaps fill_setter_maps()
            {
               SetterMaps setters;
               typedef typename MTset::FInfo2W FInfo2W;
               static const int i012v[] = {0,1,2};
               static const std::set<int> i012(i012v, Utils::endA(i012v));
              
               using namespace Par;

               setters[mass1].map0W["vev"]       = &Self::set_HiggsVEV;
               setters[dimensionless].map0W["lambda_hV"] = &Self::set_lambda_hV;
               setters[dimensionless].map0W["lambda_h"] = &Self::set_lambda_h;
               setters[Pole_Mass].map0W["V"]       = &Self::set_VectorPoleMass;

               setters[dimensionless].map0W["g1"] = &Self::set_g1;
               setters[dimensionless].map0W["g2"] = &Self::set_g2;
               setters[dimensionless].map0W["g3"] = &Self::set_g3;
               setters[dimensionless].map0W["sinW2"] = &Self::set_sinW2;

               setters[Pole_Mass].map0W["h0_1"]  = &Self::set_HiggsPoleMass;
               setters[Pole_Mass_1srd_high].map0W["h0_1"]    = &Self::set_HiggsPoleMass_1srd_high;
               setters[Pole_Mass_1srd_low].map0W["h0_1"]    = &Self::set_HiggsPoleMass_1srd_low;
               
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
