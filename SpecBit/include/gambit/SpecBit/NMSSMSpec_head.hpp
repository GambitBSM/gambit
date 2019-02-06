//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  "Header" declarations for MSSMSpec class
///  (definitions in another header file due to
///  this being a template class)
///
///  *********************************************
///
///  Authors:
///  <!-- add name and date if you modify -->
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2018 Oct
///
///  \author Sanjay Bloor
///          (sanjay.bloor12@imperial.ac.uk)
///  \date 2019 Feb
///
///  *********************************************

#ifndef NMSSMSPEC_HEAD_H
#define NMSSMSPEC_HEAD_H

#include "gambit/Elements/spec.hpp"
#include "gambit/Utils/util_functions.hpp"
#include "gambit/Models/SpectrumContents/RegisteredSpectra.hpp"
#include "gambit/SpecBit/MSSMSpec_head.hpp"

namespace Gambit
{
   namespace SpecBit
   {
      template <class MI>  // "MI" for "Model_interface"
      class NMSSMSpec;
   }

   // For example of what kind of class MI needs to be, see
   // SpecBit/include/model_files_and_boxes.hpp,
   // MODELNAME_interface class

   /// Specialisation of "traits" class used to inform Spec<T> class of what
   /// "Model" and "Input" are for this derived class
   template <class MI>
   struct SpecTraits<SpecBit::NMSSMSpec<MI>>
   {
      static std::string name() { return "NMSSMSpec"; }
      typedef SpectrumContents::NMSSM Contents;
      typedef typename MI::Model Model;
      typedef DummyInput Input;
   };

   namespace SpecBit
   {
      template <class MI>
      class NMSSMSpec : public MSSMSpec<MI>
      {
         private:
            str backend_name;
            str backend_version;
            static const int _index_offset;

         public:
            /// These typedefs are inherited, but the name lookup doesn't work so smoothly in
            /// templated wrapper classes, so need to help them along:
            typedef NMSSMSpec<MI> Self;
            typedef typename Self::MTget MTget;
            typedef typename Self::MTset MTset;
            typedef typename Self::GetterMaps GetterMaps;
            typedef typename Self::SetterMaps SetterMaps;
            typedef typename SpecTraits<Self>::Model Model;
            typedef typename SpecTraits<Self>::Input Input;

            /// Interface function overrides
            //virtual double GetScale() const;
            //virtual void SetScale(double scale);
            //virtual void RunToScaleOverride(double scale);

            //constructors
            NMSSMSpec();
            NMSSMSpec(MI, str backend_name, str backend_version);

            // These are public for now so that SpecBit_tests.cpp can access them
            MI model_interface;

            // Dummy placeholder for potential Inputs object
            DummyInput dummyinput;

            //Destructor
            virtual ~NMSSMSpec();

            // Fill an SLHAea object with spectrum information
            virtual void add_to_SLHAea(int slha_version, SLHAstruct& slha) const;

            /// TODO: Need to implement this properly...
            /// Copy low energy spectrum information from another model object
            // Should work from any flexiblesusy model object with the same particle content as the MSSM
            // TODO: Check if needs chage for NMSSM
            template<class MSSMlike>
            void get_lowe_data_from(MSSMlike &othermodel)
            {
              // Maybe we can copy the pole masses etc directly, but since I am not sure how to do that, for now I am just copying the soft parameters and recomputing the pole masses. Will have to chat to Peter about this.
              // Update: Yeah Peter says we definitely should copy the pole and drbar masses directly :).

              // Actually, we may want to instead write out the data from one object into SLHAea, and then read it into the other. That will let us copy data out of (say) softsusy objects into flexiblesusy ones, and vice-versa, more easily. Of course that will be restricted to the SLHA compatible models... Perhaps we can overload this function to deal with various inputs.
              //model = othermodel;
              typename MI::Model& model = model_interface.model;

              model.set_scale( othermodel.get_scale() );
              model.set_Yu( othermodel.get_Yu() );

              //model.calculate_DRbar_parameters();
              //model.calculate_pole_masses();

              return;
            }

            /// Map filler overrides
            static GetterMaps fill_getter_maps();
            static SetterMaps fill_setter_maps();

      };

     /// This struct contains all the strings we will use for the MSSM
     /// in the maps.  this allows us to implement the maps in
     /// a safer way if we choose , while still giving the option of
     /// flexibility.

     struct NMSSM_strs
     {
       NMSSM_strs();
       /// some strings are used in multiple masses
       /// comments indicate first map they appear
       /// dimension 2, no index
       static const str mHd2;
       static const str mHu2;
       static const str ms2;
       /// dimension 2, 2 indices
       static const str mq2;
       static const str ml2;
       static const str md2;
       static const str mu2;
       static const str me2;
       /// dimension 1, no index
       static const str M1;
       static const str M2;
       static const str M3;
       static const str vu;
       static const str vd;
       static const str vS;
       static const str Tlambda;
       static const str Tkappa; 
       /// dimension 1, 2 indices
       static const str TYd;
       static const str TYe;
       static const str TYu;
       static const str ad;
       static const str ae;
       static const str au;
       /// dimension 0, no index
       static const str g1;
       static const str g2;
       static const str g3;
       static const str lambda;
       static const str kappa;
       /// dimension 0, no index, special map
       static const str tanbeta;
       static const str sinW2;
       /// dimension 0, 2 indices
       static const str Yd;
       static const str Yu;
       static const str Ye;

       ///Pole mass
       /// dimension 1, no index , special for setters
       static const str gluino;
       static const str A0;
       static const str Hplus;
       static const str Hminus;
       static const str Goldstone0;
       static const str Goldstoneplus;
       static const str Goldstoneminus;
       static const str Wplus;
       static const str Wminus;
       static const str Z0;


       /// dimension 1, 1 index , special for setters
       static const str su     ;
       static const str sd      ;
       static const str se      ;
       static const str snu     ;
       static const str chiplus;
       static const str chi0   ;
       static const str h0      ;
       static const str subar  ;
       static const str sdbar  ;
       static const str seplus ;
       static const str snubar ;
       static const str chiminus;

       /// @{ "Metadata" vectors
       // TODO: replace with a more integrated system

       /// @{ Pole_Mass tagged entries
       static const std::vector<str> pole_mass_strs;
       static const std::vector<str> pole_mass_pred;
       static const std::vector<str> pole_mass_strs_1;
       static const std::vector<str> pole_mass_strs_1_6;
       static const std::vector<str> pole_mass_strs_1_5;
       static const std::vector<str> pole_mass_strs_1_3;
       static const std::vector<str> pole_mass_strs_1_2;
       /// @}

       /// @{ Pole_Mixing tagged entries
       static const std::vector<str> pole_mixing_strs_2_6x6;
       static const std::vector<str> pole_mixing_strs_2_5x5;
       static const std::vector<str> pole_mixing_strs_2_3x3;
       static const std::vector<str> pole_mixing_strs_2_2x2;
       /// @}

       /// @{ mass2 tagged entries
       static const std::vector<str> mass2_strs;
       static const std::vector<str> mass2_strs_2_3x3;
       /// @}

       /// @{ mass1 tagged entries
       static const std::vector<str> mass1_strs;
       static const std::vector<str> mass1_strs_2_3x3;
       /// @}

       /// @{ dimensionless tagged entries
       static const std::vector<str> dimensionless_strs;
       static const std::vector<str> dimensionless_strs_2_3x3;
       /// @}

       /// TODO: left out mass_eigenstate entries for now


       /// @}
     };


   } // end SpecBit namespace
} // end Gambit namespace

#undef MAPS
#undef MAPS1
#endif
