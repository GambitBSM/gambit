//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
//
///  *********************************************
///

///  <!-- add name and date if you modify -->
///   
///  \author Ben Farmer
///          (benjamin.farmer@fysik.su.se)
///  \date 2015 Apr 
///
///  *********************************************

#ifndef __SMSimpleSpec_hpp__
#define __SMSimpleSpec_hpp__

#include "gambit/Elements/spec.hpp"
#include "gambit/Elements/sminputs.hpp"
#include "gambit/Models/SimpleSpectra/SLHASimpleSpec.hpp"
#include "gambit/Models/SpectrumContents/RegisteredSpectra.hpp"

namespace Gambit
{

      /// Skeleton "model" class which interacts with an SLHAea object
      /// Some common functions defined in base class
      class SMea: public SLHAeaModel
      {
         public:
           /// @{ Constructors
           SMea();
           SMea(const SLHAea::Coll& input);
           /// @}

           /// @{ Getters for SM information 
           double get_MZ_pole()        const; 
           double get_Mtop_pole()      const;
                                             
           double get_MbMb()           const; 
           double get_McMc()           const; 
                                             
           double get_Mtau_pole()      const; 
           double get_Mmuon_pole()     const; 
           double get_Melectron_pole() const; 
                                             
           double get_Mnu1_pole()      const; 
           double get_Mnu2_pole()      const; 
           double get_Mnu3_pole()      const; 
                                             
           double get_MPhoton_pole()   const; 
           double get_MGluon_pole()    const; 
           double get_MPhoton()        const; 
           double get_MGluon()         const; 
                                             
           double get_MW_pole()        const; 

           double get_sinthW2_pole()   const;
           double get_MW_unc()         const;
           
           double get_md()             const;
           double get_mu()             const;
           double get_ms()             const;

           double get_mD(int)          const;
           double get_mU(int)          const;

           double get_alpha()          const;
           double get_alphaS()         const;
           /// @}
      };

      class SMSimpleSpec;

      /// Specialisation of traits class needed to inform base spectrum class of the Model and Input types
      template <>
      struct SpecTraits<SMSimpleSpec> 
      {
          static std::string name() { return "SMSimpleSpec"; }
          typedef SpectrumContents::SM_slha Contents;
          typedef SMea     Model;
          typedef DummyInput Input; // DummyInput is just an empty struct
      };

      /// SM specialisation of SLHAea object wrapper version of SubSpectrum class
      class SMSimpleSpec : public SLHASimpleSpec<SMSimpleSpec> 
      {
        
         public:
            // Constructors/destructors
            SMSimpleSpec();
            SMSimpleSpec(const SLHAea::Coll&);
            SMSimpleSpec(const SMInputs&);
            SMSimpleSpec(const SMSimpleSpec&);
            virtual ~SMSimpleSpec() {};

            virtual double GetScale() const;
           
            /// Map filler
            /// Used to initialise maps of function pointers
            static GetterMaps fill_getter_maps();
      };

} // end Gambit namespace

#endif
