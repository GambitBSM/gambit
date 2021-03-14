//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Simple SubSpectrum wrapper for the THDM
///
///  *********************************************
///
//
///  <!-- add name and date if you modify -->
///   
///  \author Filip Rajec
///          (filip.rajec@adelaide.edu.au)
///  \date 2019 Feb 
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2020 Apr
///
///  *********************************************

#ifndef __THDMSimpleSpec_hpp__
#define __THDMSimpleSpec_hpp__
#include "gambit/Elements/spec.hpp"
#include "gambit/Elements/sminputs.hpp"
#include "gambit/Models/SimpleSpectra/SLHASimpleSpec.hpp"
#include "gambit/Models/SpectrumContents/RegisteredSpectra.hpp"
#include "gambit/Elements/thdm_slhahelp.hpp"

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
        //double Lambda1, Lambda2, Lambda3, Lambda4, Lambda5, Lambda6, Lambda7;
        //double M11_2, M12_2, M22_2;
        double mW;
        double vev;
        double g1, g2, g3, sinW2;
        double Yd1[3][3], Ye1[3][3], Yu1[3][3];
        double Yd2[3][3], Ye2[3][3], Yu2[3][3];
        double ImYd1[3][3], ImYe1[3][3], ImYu1[3][3];
        double ImYd2[3][3], ImYe2[3][3], ImYu2[3][3];
        //double yukawaCoupling;
      };
    }

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
            double get_v1()             const;
            double get_v2()             const;

            double get_g1()             const;
            double get_g2()             const;
            double get_g3()             const;
            double get_sinW2()          const;

            double get_Yd1(int i, int j)     const;
            double get_Yu1(int i, int j)     const;
            double get_Ye1(int i, int j)     const;

            double get_ImYd1(int i, int j)     const;
            double get_ImYu1(int i, int j)     const;
            double get_ImYe1(int i, int j)     const;

            double get_Yd2(int i, int j)     const;
            double get_Yu2(int i, int j)     const;
            double get_Ye2(int i, int j)     const;

            double get_ImYd2(int i, int j)     const;
            double get_ImYu2(int i, int j)     const;
            double get_ImYe2(int i, int j)     const;

            double get_mh0(int i)           const;
            double get_mA0()                const;
            double get_mC()                 const;
            double get_mG0()                 const;
            double get_mGC()                 const;

            double get_tanb()               const;
            double get_beta()               const;
            double get_alpha()              const;

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
        private:
          Models::THDMModel params;

        public:
          // Constructors/destructors
          THDMSimpleSpec();
          THDMSimpleSpec(const SLHAea::Coll&);
          THDMSimpleSpec(const THDMSimpleSpec&);
          THDMSimpleSpec(const Models::THDMModel&); 

          virtual ~THDMSimpleSpec() {};

          virtual double GetScale() const;

          /// Add SLHAea object to another
          virtual void add_to_SLHAea(int slha_version, SLHAea::Coll& slha) const override {
             // Add SPINFO data if not already present
             SLHAea_add_GAMBIT_SPINFO(slha);

             // All THDM  blocks
             slhahelp::add_THDM_spectrum_to_SLHAea(*this, slha, slha_version);
          }
         
          /// Map filler
          /// Used to initialise maps of function pointers
          static GetterMaps fill_getter_maps();
  };

} // end Gambit namespace

#endif
