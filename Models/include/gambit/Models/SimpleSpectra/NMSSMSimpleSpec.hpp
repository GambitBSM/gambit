//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
//
///  *********************************************
///
///  Authors:
///  <!-- add name and date if you modify -->
///
///  \author Tomas Gonzalo 
///          (tomas.gonzalo@monash.edu)
///  \date 2018 Oct
///
///  *********************************************

#ifndef __NMSSMSimpleSpec_hpp__
#define __NMSSMSimpleSpec_hpp__

#include "gambit/Elements/spec.hpp"
#include "gambit/Models/SimpleSpectra/SLHASimpleSpec.hpp"
#include "gambit/Models/SpectrumContents/RegisteredSpectra.hpp"
#include "gambit/Models/SimpleSpectra/MSSMSimpleSpec.hpp"

namespace Gambit
{

      /// Skeleton "model" class which interacts with an SLHAea object
      /// Some common functions defined in base class
      /// NMSSM inherits from MSSM
      class NMSSMea: public MSSMea
      {
         public:
           /// @{ Constructors
           NMSSMea();
           NMSSMea(const SLHAstruct& input);
           /// @}

           /// @{ Getters for NMSSM-only information
           double get_lambda() const;
           double get_kappa() const;
           //double get_mueff() const;
           double get_vS() const;

           double get_ms2() const;

           double get_Tlambda() const;
           double get_Tkappa() const;

           //double get_Mhh_pole_slha(int i) const;
           DEC_MX_POLE_1(Mhh,_slha)
           //double get_MAh_pole_slha(int i) const;
           DEC_MX_POLE_1(MAh,_slha)

           //double get_MChi_pole_slha(int i) const;
           DEC_MX_POLE_1(MChi,_slha)

           /// @}
      };

      class NMSSMSimpleSpec;

      /// Specialisation of traits class needed to inform base spectrum class of the Model and Input types
      template <>
      struct SpecTraits<NMSSMSimpleSpec>
      {
          static std::string name() { return "NMSSMSimpleSpec"; }
          typedef SpectrumContents::NMSSM Contents;
          typedef NMSSMea    Model;
          typedef DummyInput Input; // DummyInput is just an empty struct
      };

      /// NMSSM specialisation of SLHAea object wrapper version of SubSpectrum class
      class NMSSMSimpleSpec : public SLHASimpleSpec<NMSSMSimpleSpec>
      {
         private:

         public:
            /// Constructors.
            /// The optional double uncert is the uncertainty to assign to pole masses (default is 3%).
            /// @{
            NMSSMSimpleSpec();
            NMSSMSimpleSpec(const SLHAstruct&);
            NMSSMSimpleSpec(const NMSSMSimpleSpec&);
            /// @}

            /// Destructor
            virtual ~NMSSMSimpleSpec() {};

            virtual int get_index_offset() const;
            //virtual SLHAstruct getSLHAea(int) const; // Using SubSpectrum bass class version
            virtual void add_to_SLHAea(int, SLHAea::Coll&) const;
            virtual const std::map<int, int>& PDG_translator() const;

            /// Map fillers
            /// Used to initialise maps in Spec class, accessed via SubSpectrum interface class
            /// (specialisations created and stored automatically by Spec<QedQcdWrapper>)

            static GetterMaps fill_getter_maps();
            //static SetterMaps fill_setter_maps();
       };

} // end Gambit namespace

#endif
