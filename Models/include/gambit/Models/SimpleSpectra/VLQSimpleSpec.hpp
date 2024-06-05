//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  A simple SubSpectrum wrapper for
///  VLQ. No RGEs included.
///
///  Authors (add name and date if you modify):    
///       *** Automatically created by GUM ***     
///                                                
///  \author The GAMBIT Collaboration             
///  \date 11:38AM on June 05, 2024
///                                                
///  ********************************************* 

#ifndef __VLQSimpleSpec_hpp__
#define __VLQSimpleSpec_hpp__

#include "gambit/Elements/spec.hpp"
#include "gambit/Models/SpectrumContents/RegisteredSpectra.hpp"

namespace Gambit
{
  namespace Models
  {
    /// Simple VLQ model object.
    class VLQModel : public SLHAeaModel
    {
      
      public:
      
      /// Default uncertainty
      double default_uncert = 0.3;
      
        /// @{ Constructors
        VLQModel(const SLHAstruct &input)
         : SLHAeaModel(input)
        {}
        /// @}
      
        /// @{ Getters for VLQ information
        double get_KBLh1() const { return getdata("KBLH",1); }
        double get_KBLh2() const { return getdata("KBLH",2); }
        double get_KBLh3() const { return getdata("KBLH",3); }
        double get_KBLw1() const { return getdata("KBLW",1); }
        double get_KBLw2() const { return getdata("KBLW",2); }
        double get_KBLw3() const { return getdata("KBLW",3); }
        double get_KBLz1() const { return getdata("KBLZ",1); }
        double get_KBLz2() const { return getdata("KBLZ",2); }
        double get_KBLz3() const { return getdata("KBLZ",3); }
        double get_KBRh1() const { return getdata("KBRH",1); }
        double get_KBRh2() const { return getdata("KBRH",2); }
        double get_KBRh3() const { return getdata("KBRH",3); }
        double get_KBRw1() const { return getdata("KBRW",1); }
        double get_KBRw2() const { return getdata("KBRW",2); }
        double get_KBRw3() const { return getdata("KBRW",3); }
        double get_KBRz1() const { return getdata("KBRZ",1); }
        double get_KBRz2() const { return getdata("KBRZ",2); }
        double get_KBRz3() const { return getdata("KBRZ",3); }
        double get_KTLh1() const { return getdata("KTLH",1); }
        double get_KTLh2() const { return getdata("KTLH",2); }
        double get_KTLh3() const { return getdata("KTLH",3); }
        double get_KTLw1() const { return getdata("KTLW",1); }
        double get_KTLw2() const { return getdata("KTLW",2); }
        double get_KTLw3() const { return getdata("KTLW",3); }
        double get_KTLz1() const { return getdata("KTLZ",1); }
        double get_KTLz2() const { return getdata("KTLZ",2); }
        double get_KTLz3() const { return getdata("KTLZ",3); }
        double get_KTRh1() const { return getdata("KTRH",1); }
        double get_KTRh2() const { return getdata("KTRH",2); }
        double get_KTRh3() const { return getdata("KTRH",3); }
        double get_KTRw1() const { return getdata("KTRW",1); }
        double get_KTRw2() const { return getdata("KTRW",2); }
        double get_KTRw3() const { return getdata("KTRW",3); }
        double get_KTRz1() const { return getdata("KTRZ",1); }
        double get_KTRz2() const { return getdata("KTRZ",2); }
        double get_KTRz3() const { return getdata("KTRZ",3); }
        double get_KXL1() const { return getdata("KXLW",1); }
        double get_KXL2() const { return getdata("KXLW",2); }
        double get_KXL3() const { return getdata("KXLW",3); }
        double get_KXR1() const { return getdata("KXRW",1); }
        double get_KXR2() const { return getdata("KXRW",2); }
        double get_KXR3() const { return getdata("KXRW",3); }
        double get_KYL1() const { return getdata("KYLW",1); }
        double get_KYL2() const { return getdata("KYLW",2); }
        double get_KYL3() const { return getdata("KYLW",3); }
        double get_KYR1() const { return getdata("KYRW",1); }
        double get_KYR2() const { return getdata("KYRW",2); }
        double get_KYR3() const { return getdata("KYRW",3); }
        double get_vev() const { return getdata("VEVS",1); }
        double get_g1() const { return getdata("GAUGE",1); }
        double get_g2() const { return getdata("GAUGE",2); }
        double get_g3() const { return getdata("GAUGE",3); }
        double get_sinW2() const { return getdata("SINTHETAW",1); }
        double get_Yd(int i, int j) const { return getdata("YD",i,j); }
        double get_Yu(int i, int j) const { return getdata("YU",i,j); }
        double get_Ye(int i, int j) const { return getdata("YE",i,j); }
        double get_h0_1PoleMass() const { return getdata("MASS",25); }
        double get_h0_1PoleMass_1srd_low() const
        {
          if (checkdata("DMASS",25)) return getdata("DMASS",25);
          else return default_uncert;
        }
        double get_h0_1PoleMass_1srd_high() const
        {
          if (checkdata("DMASS",25)) return getdata("DMASS",25);
          else return default_uncert;
        }
        double get_xPoleMass() const { return getdata("MASS",6000005); }
        double get_xPoleMass_1srd_low() const
        {
          if (checkdata("DMASS",6000005)) return getdata("DMASS",6000005);
          else return default_uncert;
        }
        double get_xPoleMass_1srd_high() const
        {
          if (checkdata("DMASS",6000005)) return getdata("DMASS",6000005);
          else return default_uncert;
        }
        double get_tpPoleMass() const { return getdata("MASS",6000006); }
        double get_tpPoleMass_1srd_low() const
        {
          if (checkdata("DMASS",6000006)) return getdata("DMASS",6000006);
          else return default_uncert;
        }
        double get_tpPoleMass_1srd_high() const
        {
          if (checkdata("DMASS",6000006)) return getdata("DMASS",6000006);
          else return default_uncert;
        }
        double get_bpPoleMass() const { return getdata("MASS",6000007); }
        double get_bpPoleMass_1srd_low() const
        {
          if (checkdata("DMASS",6000007)) return getdata("DMASS",6000007);
          else return default_uncert;
        }
        double get_bpPoleMass_1srd_high() const
        {
          if (checkdata("DMASS",6000007)) return getdata("DMASS",6000007);
          else return default_uncert;
        }
        double get_yPoleMass() const { return getdata("MASS",6000008); }
        double get_yPoleMass_1srd_low() const
        {
          if (checkdata("DMASS",6000008)) return getdata("DMASS",6000008);
          else return default_uncert;
        }
        double get_yPoleMass_1srd_high() const
        {
          if (checkdata("DMASS",6000008)) return getdata("DMASS",6000008);
          else return default_uncert;
        }
      /// @}}
    
  };
  
  /// Forward declare the wrapper class so that we can use it
  /// as the template parameter for the SpecTraits specialisation.
  class VLQSimpleSpec;
}

/// Specialisation of traits class needed to inform base spectrum class of the Model and Input types
template <> 
struct SpecTraits<Models::VLQSimpleSpec> : DefaultTraits
{
  static std::string name() { return "VLQSimpleSpec"; }
  typedef SpectrumContents::VLQ Contents;
  typedef Models::VLQModel Model;
};

namespace Models
{
  class VLQSimpleSpec : public SLHASimpleSpec<VLQSimpleSpec>
  {
    
    public:
      /// @{
      /// Constructor via SLHAea object
      VLQSimpleSpec(const SLHAea::Coll& input)
       : SLHASimpleSpec(input)
      {}
      
      /// Copy constructor
      VLQSimpleSpec(const VLQSimpleSpec& other)
       : SLHASimpleSpec(other)
      {}
      
      /// Destructor
      virtual ~VLQSimpleSpec() {};
      
      static int index_offset() {return 0;}
      
      /// Construct the SubSpectrumContents
      const SpectrumContents::VLQ contents;
      
      /// Add SLHAea object using the SimpleSpec_to_SLHAea routine
      void add_to_SLHAea(int /*slha_version*/, SLHAea::Coll& slha) const
      {
        // Add SPINFO data if not already present
        SLHAea_add_GAMBIT_SPINFO(slha);
        
        // All blocks given in the SimpleSpec
        
        add_SimpleSpec_to_SLHAea(*this, slha, contents);
      }
      
      /// Wrapper functions to parameter object.
      
      /// Map fillers
      static GetterMaps fill_getter_maps()
      {
        GetterMaps getters;
        
        typedef typename MTget::FInfo2 FInfo2;
        static const int i123v[] = {1,2,3};
        static const std::set<int> i123(i123v, Utils::endA(i123v));
        
        using namespace Par;
        
        getters[dimensionless].map0["KBLh1"] =  &Model::get_KBLh1;
        getters[dimensionless].map0["KBLh2"] =  &Model::get_KBLh2;
        getters[dimensionless].map0["KBLh3"] =  &Model::get_KBLh3;
        getters[dimensionless].map0["KBLw1"] =  &Model::get_KBLw1;
        getters[dimensionless].map0["KBLw2"] =  &Model::get_KBLw2;
        getters[dimensionless].map0["KBLw3"] =  &Model::get_KBLw3;
        getters[dimensionless].map0["KBLz1"] =  &Model::get_KBLz1;
        getters[dimensionless].map0["KBLz2"] =  &Model::get_KBLz2;
        getters[dimensionless].map0["KBLz3"] =  &Model::get_KBLz3;
        getters[dimensionless].map0["KBRh1"] =  &Model::get_KBRh1;
        getters[dimensionless].map0["KBRh2"] =  &Model::get_KBRh2;
        getters[dimensionless].map0["KBRh3"] =  &Model::get_KBRh3;
        getters[dimensionless].map0["KBRw1"] =  &Model::get_KBRw1;
        getters[dimensionless].map0["KBRw2"] =  &Model::get_KBRw2;
        getters[dimensionless].map0["KBRw3"] =  &Model::get_KBRw3;
        getters[dimensionless].map0["KBRz1"] =  &Model::get_KBRz1;
        getters[dimensionless].map0["KBRz2"] =  &Model::get_KBRz2;
        getters[dimensionless].map0["KBRz3"] =  &Model::get_KBRz3;
        getters[dimensionless].map0["KTLh1"] =  &Model::get_KTLh1;
        getters[dimensionless].map0["KTLh2"] =  &Model::get_KTLh2;
        getters[dimensionless].map0["KTLh3"] =  &Model::get_KTLh3;
        getters[dimensionless].map0["KTLw1"] =  &Model::get_KTLw1;
        getters[dimensionless].map0["KTLw2"] =  &Model::get_KTLw2;
        getters[dimensionless].map0["KTLw3"] =  &Model::get_KTLw3;
        getters[dimensionless].map0["KTLz1"] =  &Model::get_KTLz1;
        getters[dimensionless].map0["KTLz2"] =  &Model::get_KTLz2;
        getters[dimensionless].map0["KTLz3"] =  &Model::get_KTLz3;
        getters[dimensionless].map0["KTRh1"] =  &Model::get_KTRh1;
        getters[dimensionless].map0["KTRh2"] =  &Model::get_KTRh2;
        getters[dimensionless].map0["KTRh3"] =  &Model::get_KTRh3;
        getters[dimensionless].map0["KTRw1"] =  &Model::get_KTRw1;
        getters[dimensionless].map0["KTRw2"] =  &Model::get_KTRw2;
        getters[dimensionless].map0["KTRw3"] =  &Model::get_KTRw3;
        getters[dimensionless].map0["KTRz1"] =  &Model::get_KTRz1;
        getters[dimensionless].map0["KTRz2"] =  &Model::get_KTRz2;
        getters[dimensionless].map0["KTRz3"] =  &Model::get_KTRz3;
        getters[dimensionless].map0["KXL1"] =  &Model::get_KXL1;
        getters[dimensionless].map0["KXL2"] =  &Model::get_KXL2;
        getters[dimensionless].map0["KXL3"] =  &Model::get_KXL3;
        getters[dimensionless].map0["KXR1"] =  &Model::get_KXR1;
        getters[dimensionless].map0["KXR2"] =  &Model::get_KXR2;
        getters[dimensionless].map0["KXR3"] =  &Model::get_KXR3;
        getters[dimensionless].map0["KYL1"] =  &Model::get_KYL1;
        getters[dimensionless].map0["KYL2"] =  &Model::get_KYL2;
        getters[dimensionless].map0["KYL3"] =  &Model::get_KYL3;
        getters[dimensionless].map0["KYR1"] =  &Model::get_KYR1;
        getters[dimensionless].map0["KYR2"] =  &Model::get_KYR2;
        getters[dimensionless].map0["KYR3"] =  &Model::get_KYR3;
        getters[mass1].map0["vev"] =  &Model::get_vev;
        getters[dimensionless].map0["g1"] =  &Model::get_g1;
        getters[dimensionless].map0["g2"] =  &Model::get_g2;
        getters[dimensionless].map0["g3"] =  &Model::get_g3;
        getters[dimensionless].map0["sinW2"] =  &Model::get_sinW2;
        getters[dimensionless].map2["Yd"] = FInfo2(&Model::get_Yd, i123, i123);
        getters[dimensionless].map2["Yu"] = FInfo2(&Model::get_Yu, i123, i123);
        getters[dimensionless].map2["Ye"] = FInfo2(&Model::get_Ye, i123, i123);
        getters[Pole_Mass].map0["h0_1"] =  &Model::get_h0_1PoleMass;
        getters[Pole_Mass_1srd_low].map0["h0_1"] =  &Model::get_h0_1PoleMass_1srd_low;
        getters[Pole_Mass_1srd_high].map0["h0_1"] =  &Model::get_h0_1PoleMass_1srd_high;
        getters[Pole_Mass].map0["x"] =  &Model::get_xPoleMass;
        getters[Pole_Mass_1srd_low].map0["x"] =  &Model::get_xPoleMass_1srd_low;
        getters[Pole_Mass_1srd_high].map0["x"] =  &Model::get_xPoleMass_1srd_high;
        getters[Pole_Mass].map0["tp"] =  &Model::get_tpPoleMass;
        getters[Pole_Mass_1srd_low].map0["tp"] =  &Model::get_tpPoleMass_1srd_low;
        getters[Pole_Mass_1srd_high].map0["tp"] =  &Model::get_tpPoleMass_1srd_high;
        getters[Pole_Mass].map0["bp"] =  &Model::get_bpPoleMass;
        getters[Pole_Mass_1srd_low].map0["bp"] =  &Model::get_bpPoleMass_1srd_low;
        getters[Pole_Mass_1srd_high].map0["bp"] =  &Model::get_bpPoleMass_1srd_high;
        getters[Pole_Mass].map0["y"] =  &Model::get_yPoleMass;
        getters[Pole_Mass_1srd_low].map0["y"] =  &Model::get_yPoleMass_1srd_low;
        getters[Pole_Mass_1srd_high].map0["y"] =  &Model::get_yPoleMass_1srd_high;
        
        return getters;
      }
      
    };
  }
} // namespace Gambit
#endif
