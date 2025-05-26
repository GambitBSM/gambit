//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  A simple SubSpectrum wrapper for the SubGeVDM
///  model. No RGEs included.
///
///  *********************************************
///
///  Authors:
///  <!-- add name and date if you modify -->
///
///  \author Felix Kahlhoefer
///          (kahlhoefer@kit.edu)
///  \date 2022 May
///
///  *********************************************

#ifndef __SubGeVDMSimpleSpec_hpp__
#define __SubGeVDMSimpleSpec_hpp__

#include "gambit/Elements/spec.hpp"
#include "gambit/Models/SpectrumContents/RegisteredSpectra.hpp"

namespace Gambit
{
   namespace Models
   {
      /// Simple extension of the SMHiggsSimpleSpec "model object"
      /// to include Sub-GeV DM parameters
      /// We could easily just put these in the wrapper itself, but
      /// I am leaving them in a separate struct for the sake of building
      /// up examples towards a more complicated "model" object
      struct SubGeVDMModel
      {
         double SubGeV_DMPoleMass;
         double SubGeV_ApPoleMass;
         double SubGeV_gDM;
         double SubGeV_kappa;
         double vev;
         double g1, g2, g3, sinW2;
         double Yd[3], Ye[3], Yu[3];
      };


      /// Forward declare the wrapper class so that we can use it
      /// as the template parameter for the SpecTraits specialisation.
      class SubGeVDMSimpleSpec;
   }

   /// Specialisation of traits class needed to inform base spectrum class of the Model and Input types
   template <>
   struct SpecTraits<Models::SubGeVDMSimpleSpec> : DefaultTraits
   {
      static std::string name() { return "SubGeVDMSimpleSpec"; }
      typedef SpectrumContents::SubGeVDM Contents;
   };

   namespace Models
   {
      class SubGeVDMSimpleSpec : public Spec<SubGeVDMSimpleSpec>
      {
         private:
            SubGeVDMModel params;

            typedef SubGeVDMSimpleSpec Self;

         public:
            /// @{ Constructors/destructors
            SubGeVDMSimpleSpec(const SubGeVDMModel& p)
             : params(p)
            {}

            static int index_offset() {return -1;}

            /// @}

            /// Wrapper-side interface functions to parameter object

            double get_vev()        const { return params.vev;      }
            double get_SubGeV_DMPoleMass() const { return params.SubGeV_DMPoleMass; }
            double get_SubGeV_ApPoleMass() const { return params.SubGeV_ApPoleMass; }
            double get_SubGeV_gDM()        const { return params.SubGeV_gDM; }
            double get_SubGeV_kappa()        const { return params.SubGeV_kappa; }
            double get_g1()       const { return params.g1; }
            double get_g2()       const { return params.g2; }
            double get_g3()       const { return params.g3; }
            double get_sinW2()       const { return params.sinW2; }

            double get_Yd(int i, int j)       const { if (i==j){return params.Yd[i];}else{return 0;} }
            double get_Yu(int i, int j)       const { if (i==j){return params.Yu[i];}else{return 0;} }
            double get_Ye(int i, int j)       const { if (i==j){return params.Ye[i];}else{return 0;} }

            void set_vev(double in)        { params.vev=in;      }
            void set_SubGeV_DMPoleMass(double in) { params.SubGeV_DMPoleMass=in; }
            void set_SubGeV_ApPoleMass(double in)       { params.SubGeV_ApPoleMass=in; }
            void set_SubGeV_gDM(double in)       { params.SubGeV_gDM=in; }
            void set_SubGeV_kappa(double in)       { params.SubGeV_kappa=in; }
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

               getters[mass1]        .map0W["vev"]       = &Self::get_vev;
               getters[dimensionless].map0W["gDM"] = &Self::get_SubGeV_gDM;
               getters[Pole_Mass].map0W["DM"]       = &Self::get_SubGeV_DMPoleMass;
               getters[Pole_Mass].map0W["Ap"]       = &Self::get_SubGeV_ApPoleMass;

               getters[dimensionless].map0W["kappa"] = &Self::get_SubGeV_kappa;

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

               setters[mass1].map0W["vev"]       = &Self::set_vev;
               setters[dimensionless].map0W["gDM"] = &Self::set_SubGeV_gDM;
               setters[dimensionless].map0W["kappa"] = &Self::set_SubGeV_kappa;
               setters[Pole_Mass].map0W["DM"]       = &Self::set_SubGeV_DMPoleMass;
               setters[Pole_Mass].map0W["Ap"]       = &Self::set_SubGeV_ApPoleMass;

               setters[dimensionless].map0W["g1"] = &Self::set_g1;
               setters[dimensionless].map0W["g2"] = &Self::set_g2;
               setters[dimensionless].map0W["g3"] = &Self::set_g3;
               setters[dimensionless].map0W["sinW2"] = &Self::set_sinW2;

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
