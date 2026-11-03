//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  A simple SubSpectrum wrapper for the super-
///  renormalizable Higgs portal model.
///  No RGEs included.
///
///  *********************************************
///
///  Authors:
///  <!-- add name and date if you modify -->
///
///  \author Inigo Saez Casares
///          (inigo.saez_casares@ens-paris-saclay.fr)
///
///  \date 2020 March
///
///  *********************************************

// TODO: Temporarily disabled until project is ready
/*
#ifndef __SuperRenormHPSimpleSpec_hpp__
#define __SuperRenormHPSimpleSpec_hpp__

#include "gambit/Elements/spec.hpp"

#include "gambit/Models/SpectrumContents/RegisteredSpectra.hpp"

namespace Gambit
{
   namespace Models
   {
      /// Simple extension of the SMHiggsSimpleSpec "model object"
      /// to include super-renormalizable Higgs portal model parameters
      struct SuperRenormHPModel
      {
         // Higgs sector
         double HiggsPoleMass;
         double HiggsVEV;
         double HiggsPoleMass_1srd_low,HiggsPoleMass_1srd_high;

         // Scalar DM sector
         double ScalarPoleMass;
         double MixingAngle;
      };

        /// Forward declare the wrapper class so that we can use it
        /// as the template parameter for the SpecTraits specialisation.
        class SuperRenormHPSimpleSpec;
     }

     /// Specialisation of traits class needed to inform base spectrum class of the Model and Input types
     template <>
     struct SpecTraits<Models::SuperRenormHPSimpleSpec> : DefaultTraits
     {
        static std::string name() { return "SuperRenormHPSimpleSpec"; }
        typedef SpectrumContents::SuperRenormHP Contents;
     };

     namespace Models
     {

        class SuperRenormHPSimpleSpec : public Spec<SuperRenormHPSimpleSpec>
        {
           private:
              SuperRenormHPModel params;

              typedef SuperRenormHPSimpleSpec Self;

           public:
              /// @{ Constructors/destructors
            SuperRenormHPSimpleSpec(const SuperRenormHPModel& p)
             : params(p)
            {}

            static int index_offset() {return -1;}

            /// @}

            /// Wrapper-side interface functions to parameter object
            double get_HiggsPoleMass()   const { return params.HiggsPoleMass; }
            double get_HiggsVEV()        const { return params.HiggsVEV;      }
            double get_HiggsPoleMass_1srd_low()  const  { return params.HiggsPoleMass_1srd_low;  }
            double get_HiggsPoleMass_1srd_high() const  { return params.HiggsPoleMass_1srd_high; }

            double get_ScalarPoleMass()  const { return params.ScalarPoleMass; }
            double get_MixingAngle()     const { return params.MixingAngle;    }

            void set_HiggsPoleMass(double in)  { params.HiggsPoleMass=in; }
            void set_HiggsVEV(double in)       { params.HiggsVEV=in;      }
            void set_HiggsPoleMass_1srd_low(double in)  { params.HiggsPoleMass_1srd_low=in;  }
            void set_HiggsPoleMass_1srd_high(double in) { params.HiggsPoleMass_1srd_high=in; }

            void set_ScalarPoleMass(double in) { params.ScalarPoleMass=in; }
            void set_MixingAngle(double in)    { params.MixingAngle=in;    }

            /// @{ Map fillers
            static GetterMaps fill_getter_maps()
            {
               GetterMaps getters;

               using namespace Par;

               getters[mass1].map0W["vev"]               = &Self::get_HiggsVEV;
               getters[Pole_Mass].map0W["h0_1"]          = &Self::get_HiggsPoleMass;
               getters[Pole_Mass_1srd_high].map0W["h0"]  = &Self::get_HiggsPoleMass_1srd_high;
               getters[Pole_Mass_1srd_low].map0W["h0"]   = &Self::get_HiggsPoleMass_1srd_low;

               getters[Pole_Mass].map0W["S"]             = &Self::get_ScalarPoleMass;
               getters[dimensionless].map0W["theta"]     = &Self::get_MixingAngle;

               return getters;
            }

            static SetterMaps fill_setter_maps()
            {
               SetterMaps setters;

               using namespace Par;

               setters[mass1].map0W["vev"]               = &Self::set_HiggsVEV;
               setters[Pole_Mass].map0W["h0_1"]          = &Self::set_HiggsPoleMass;
               setters[Pole_Mass_1srd_high].map0W["h0"]  = &Self::set_HiggsPoleMass_1srd_high;
               setters[Pole_Mass_1srd_low].map0W["h0"]   = &Self::set_HiggsPoleMass_1srd_low;

               setters[Pole_Mass].map0W["S"]             = &Self::set_ScalarPoleMass;
               setters[dimensionless].map0W["theta"]     = &Self::set_MixingAngle;

               return setters;
            }
            /// @}
      };

   } // end Models namespace
} // end Gambit namespace

#endif
*/
