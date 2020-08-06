//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
//
///  *********************************************
///

///  <!-- add name and date if you modify -->
///   
///  \author Filip Rajec
///          (filip.rajec@adelaide.edu.au)
///  \date 2019 Feb 
///
///  *********************************************

#ifndef __THDMSimpleSpec_hpp__
#define __THDMSimpleSpec_hpp__

#include "gambit/Elements/spec.hpp"
#include "gambit/Elements/sminputs.hpp"
#include "gambit/Models/SimpleSpectra/SLHASimpleSpec.hpp"
#include "gambit/Models/SpectrumContents/RegisteredSpectra.hpp"

namespace Gambit
{

      /// Skeleton "model" class which interacts with an SLHAea object
      /// Some common functions defined in base class
      class THDMea: public SLHAeaModel
      {
         public:
           /// @{ Constructors
           THDMea();
           THDMea(const SLHAea::Coll& input);
           /// @}

           /// @{ Getters for THDM information 
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
                                             
           double get_MW_pole()        const; 

           double get_sinthW2_pole()   const;
           double get_MW_unc()         const;
           
           double get_md()             const;
           double get_mu()             const;
           double get_ms()             const;

           double get_vev()            const;
           double get_v1()            const;
           double get_v2()            const;
           double get_g1()             const;
           double get_g2()             const;
           double get_g3()             const;
           double get_sinW2()          const;

           double get_Yd(int i, int j)     const;
           double get_Yu(int i, int j)     const;
           double get_Ye(int i, int j)     const;

           double get_mh0(int i)           const;
           double get_mA0()                const;
           double get_mC()                 const;
           double get_mG0()                 const;
           double get_mGC()                 const;
           double get_tanb()               const;
           double get_beta()              const;
           double get_alpha()              const;
           double get_yukawaCoupling()     const;

           double get_lambda1()            const;
           double get_lambda2()            const;
           double get_lambda3()            const;
           double get_lambda4()            const;
           double get_lambda5()            const;
           double get_lambda6()            const;
           double get_lambda7()            const;
           double get_m11_2()              const;
           double get_m22_2()              const;
           double get_m12_2()              const;

           double get_Lambda1()            const;
           double get_Lambda2()            const;
           double get_Lambda3()            const;
           double get_Lambda4()            const;
           double get_Lambda5()            const;
           double get_Lambda6()            const;
           double get_Lambda7()            const;
           double get_M11_2()              const;
           double get_M22_2()              const;
           double get_M12_2()              const;
      //      double get_sinthW2_DRbar()      const;
           /// @}
      };

      class THDMSimpleSpec;

      /// Specialisation of traits class needed to inform base spectrum class of the Model and Input types
      template <>
      struct SpecTraits<THDMSimpleSpec> 
      {
          static std::string name() { return "THDMSimpleSpec"; }
          typedef SpectrumContents::THDM Contents;
          typedef THDMea     Model;
          typedef DummyInput Input; // DummyInput is just an empty struct
      };

      /// THDM specialisation of SLHAea object wrapper version of SubSpectrum class
      class THDMSimpleSpec : public SLHASimpleSpec<THDMSimpleSpec> 
      {
        
         public:
            // Constructors/destructors
            THDMSimpleSpec();
            THDMSimpleSpec(const SLHAea::Coll&);
            THDMSimpleSpec(const THDMSimpleSpec&);
            virtual ~THDMSimpleSpec() {};

            virtual double GetScale() const;
           
            /// Map filler
            /// Used to initialise maps of function pointers
            static GetterMaps fill_getter_maps();
      };

} // end Gambit namespace

#endif
