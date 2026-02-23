//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  A simple SubSpectrum wrapper for
///  Inert. No RGEs included.
///
///  Authors (add name and date if you modify):    
///       *** Automatically created by GUM ***     
///                                                
///  \author The GAMBIT Collaboration             
///  \date 03:33PM on February 18, 2026
///                                                
///  ********************************************* 

#ifndef __InertSimpleSpec_hpp__
#define __InertSimpleSpec_hpp__

#include "gambit/Elements/spec.hpp"
#include "gambit/Models/SpectrumContents/RegisteredSpectra.hpp"

namespace Gambit
{
  namespace Models
  {
    /// Simple Inert model object.
    class InertModel : public SLHAeaModel
    {
      
      public:
      
      /// Default uncertainty
      double default_uncert = 0.3;
      
        /// @{ Constructors
        InertModel(const SLHAstruct &input)
         : SLHAeaModel(input)
        {}
        /// @}
      
        /// @{ Getters for Inert information
        double get_mHd2() const { return getdata("MSOFT",21); }
        double get_mHu2() const { return getdata("MSOFT",22); }
        double get_v() const { return getdata("HMIX",3); }
        double get_ZP(int i, int j) const { return getdata("CHARGEMIX",i,j); }
        double get_ZEL(int i, int j) const { return getdata("UELMIX",i,j); }
        double get_ZER(int i, int j) const { return getdata("UERMIX",i,j); }
        double get_ZDL(int i, int j) const { return getdata("UDLMIX",i,j); }
        double get_ZDR(int i, int j) const { return getdata("UDRMIX",i,j); }
        double get_ZUL(int i, int j) const { return getdata("UULMIX",i,j); }
        double get_ZUR(int i, int j) const { return getdata("UURMIX",i,j); }
        double get_Lam1() const { return getdata("HDM",1); }
        double get_Lam2() const { return getdata("HDM",2); }
        double get_Lam3() const { return getdata("HDM",3); }
        double get_Lam4() const { return getdata("HDM",4); }
        double get_Lam5() const { return getdata("HDM",5); }
        double get_g1() const { return getdata("GAUGE",1); }
        double get_g2() const { return getdata("GAUGE",2); }
        double get_g3() const { return getdata("GAUGE",3); }
        double get_Yd(int i, int j) const { return getdata("YD",i,j); }
        double get_Yu(int i, int j) const { return getdata("YU",i,j); }
        double get_Ye(int i, int j) const { return getdata("YE",i,j); }
        double get_hPoleMass() const { return getdata("MASS",25); }
        double get_hPoleMass_1srd_low() const
        {
          if (checkdata("DMASS",25)) return getdata("DMASS",25);
          else return default_uncert;
        }
        double get_hPoleMass_1srd_high() const
        {
          if (checkdata("DMASS",25)) return getdata("DMASS",25);
          else return default_uncert;
        }
        double get_H0PoleMass() const { return getdata("MASS",35); }
        double get_H0PoleMass_1srd_low() const
        {
          if (checkdata("DMASS",35)) return getdata("DMASS",35);
          else return default_uncert;
        }
        double get_H0PoleMass_1srd_high() const
        {
          if (checkdata("DMASS",35)) return getdata("DMASS",35);
          else return default_uncert;
        }
        double get_A0PoleMass() const { return getdata("MASS",36); }
        double get_A0PoleMass_1srd_low() const
        {
          if (checkdata("DMASS",36)) return getdata("DMASS",36);
          else return default_uncert;
        }
        double get_A0PoleMass_1srd_high() const
        {
          if (checkdata("DMASS",36)) return getdata("DMASS",36);
          else return default_uncert;
        }
        double get_Hp2PoleMass() const { return getdata("MASS",37); }
        double get_Hp2PoleMass_1srd_low() const
        {
          if (checkdata("DMASS",37)) return getdata("DMASS",37);
          else return default_uncert;
        }
        double get_Hp2PoleMass_1srd_high() const
        {
          if (checkdata("DMASS",37)) return getdata("DMASS",37);
          else return default_uncert;
        }
      /// @}}
    
  };
  
  /// Forward declare the wrapper class so that we can use it
  /// as the template parameter for the SpecTraits specialisation.
  class InertSimpleSpec;
}

/// Specialisation of traits class needed to inform base spectrum class of the Model and Input types
template <> 
struct SpecTraits<Models::InertSimpleSpec> : DefaultTraits
{
  static std::string name() { return "InertSimpleSpec"; }
  typedef SpectrumContents::Inert Contents;
  typedef Models::InertModel Model;
};

namespace Models
{
  class InertSimpleSpec : public SLHASimpleSpec<InertSimpleSpec>
  {
    
    public:
      /// @{
      /// Constructor via SLHAea object
      InertSimpleSpec(const SLHAea::Coll& input)
       : SLHASimpleSpec(input)
      {}
      
      /// Copy constructor
      InertSimpleSpec(const InertSimpleSpec& other)
       : SLHASimpleSpec(other)
      {}
      
      /// Destructor
      virtual ~InertSimpleSpec() {};
      
      static int index_offset() {return 0;}
      
      /// Construct the SubSpectrumContents
      const SpectrumContents::Inert contents;
      
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
        static const int i12v[] = {1,2};
        static const std::set<int> i12(i12v, Utils::endA(i12v));
        
        using namespace Par;
        
        getters[dimensionless].map0["mHd2"] =  &Model::get_mHd2;
        getters[dimensionless].map0["mHu2"] =  &Model::get_mHu2;
        getters[dimensionless].map0["v"] =  &Model::get_v;
        getters[Pole_Mixing].map2["ZP"] = FInfo2(&Model::get_ZP, i12, i12);
        getters[Pole_Mixing].map2["ZEL"] = FInfo2(&Model::get_ZEL, i123, i123);
        getters[Pole_Mixing].map2["ZER"] = FInfo2(&Model::get_ZER, i123, i123);
        getters[Pole_Mixing].map2["ZDL"] = FInfo2(&Model::get_ZDL, i123, i123);
        getters[Pole_Mixing].map2["ZDR"] = FInfo2(&Model::get_ZDR, i123, i123);
        getters[Pole_Mixing].map2["ZUL"] = FInfo2(&Model::get_ZUL, i123, i123);
        getters[Pole_Mixing].map2["ZUR"] = FInfo2(&Model::get_ZUR, i123, i123);
        getters[dimensionless].map0["Lam1"] =  &Model::get_Lam1;
        getters[dimensionless].map0["Lam2"] =  &Model::get_Lam2;
        getters[dimensionless].map0["Lam3"] =  &Model::get_Lam3;
        getters[dimensionless].map0["Lam4"] =  &Model::get_Lam4;
        getters[dimensionless].map0["Lam5"] =  &Model::get_Lam5;
        getters[dimensionless].map0["g1"] =  &Model::get_g1;
        getters[dimensionless].map0["g2"] =  &Model::get_g2;
        getters[dimensionless].map0["g3"] =  &Model::get_g3;
        getters[dimensionless].map2["Yd"] = FInfo2(&Model::get_Yd, i123, i123);
        getters[dimensionless].map2["Yu"] = FInfo2(&Model::get_Yu, i123, i123);
        getters[dimensionless].map2["Ye"] = FInfo2(&Model::get_Ye, i123, i123);
        getters[Pole_Mass].map0["h0_1"] =  &Model::get_hPoleMass;
        getters[Pole_Mass_1srd_low].map0["h0_1"] =  &Model::get_hPoleMass_1srd_low;
        getters[Pole_Mass_1srd_high].map0["h0_1"] =  &Model::get_hPoleMass_1srd_high;
        getters[Pole_Mass].map0["h0_2"] =  &Model::get_H0PoleMass;
        getters[Pole_Mass_1srd_low].map0["h0_2"] =  &Model::get_H0PoleMass_1srd_low;
        getters[Pole_Mass_1srd_high].map0["h0_2"] =  &Model::get_H0PoleMass_1srd_high;
        getters[Pole_Mass].map0["A0"] =  &Model::get_A0PoleMass;
        getters[Pole_Mass_1srd_low].map0["A0"] =  &Model::get_A0PoleMass_1srd_low;
        getters[Pole_Mass_1srd_high].map0["A0"] =  &Model::get_A0PoleMass_1srd_high;
        getters[Pole_Mass].map0["H+"] =  &Model::get_Hp2PoleMass;
        getters[Pole_Mass_1srd_low].map0["H+"] =  &Model::get_Hp2PoleMass_1srd_low;
        getters[Pole_Mass_1srd_high].map0["H+"] =  &Model::get_Hp2PoleMass_1srd_high;
        
        return getters;
      }
      
    };
  }
} // namespace Gambit
#endif
