//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  A simple SubSpectrum wrapper for
///  DMsimpVectorMedVectorDM. No RGEs included.
///
///  Authors (add name and date if you modify):    
///       *** Automatically created by GUM ***     
///                                                
///  \author The GAMBIT Collaboration             
///  \date 03:49PM on February 07, 2023
///                                                
///  ********************************************* 

#ifndef __DMsimpVectorMedVectorDMSimpleSpec_hpp__
#define __DMsimpVectorMedVectorDMSimpleSpec_hpp__

#include "gambit/Elements/spec.hpp"
#include "gambit/Models/SpectrumContents/RegisteredSpectra.hpp"

namespace Gambit
{
  namespace Models
  {
    /// Simple DMsimpVectorMedVectorDM model object.
    class DMsimpVectorMedVectorDMModel : public SLHAeaModel
    {

      public:

      /// Default uncertainty
      double default_uncert = 0.3;

        /// @{ Constructors
        DMsimpVectorMedVectorDMModel(const SLHAstruct &input)
         : SLHAeaModel(input)
        {}
        /// @}

        /// @{ Getters for DMsimpVectorMedVectorDM information
        double get_gVXv() const { return getdata("DMINT",1); }
        double get_gVq() const { return getdata("DMINT",2); }
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
        double get_XvPoleMass() const { return getdata("MASS",5000523); }
        double get_XvPoleMass_1srd_low() const
        {
          if (checkdata("DMASS",5000523)) return getdata("DMASS",5000523);
          else return default_uncert;
        }
        double get_XvPoleMass_1srd_high() const
        {
          if (checkdata("DMASS",5000523)) return getdata("DMASS",5000523);
          else return default_uncert;
        }
        double get_Y1PoleMass() const { return getdata("MASS",5000001); }
        double get_Y1PoleMass_1srd_low() const
        {
          if (checkdata("DMASS",5000001)) return getdata("DMASS",5000001);
          else return default_uncert;
        }
        double get_Y1PoleMass_1srd_high() const
        {
          if (checkdata("DMASS",5000001)) return getdata("DMASS",5000001);
          else return default_uncert;
        }
      /// @}}

  };

  /// Forward declare the wrapper class so that we can use it
  /// as the template parameter for the SpecTraits specialisation.
  class DMsimpVectorMedVectorDMSimpleSpec;
}

/// Specialisation of traits class needed to inform base spectrum class of the Model and Input types
template <> 
struct SpecTraits<Models::DMsimpVectorMedVectorDMSimpleSpec> : DefaultTraits
{
  static std::string name() { return "DMsimpVectorMedVectorDMSimpleSpec"; }
  typedef SpectrumContents::DMsimpVectorMedVectorDM Contents;
  typedef Models::DMsimpVectorMedVectorDMModel Model;
};

namespace Models
{
  class DMsimpVectorMedVectorDMSimpleSpec : public SLHASimpleSpec<DMsimpVectorMedVectorDMSimpleSpec>
  {

    public:
      /// @{
      /// Constructor via SLHAea object
      DMsimpVectorMedVectorDMSimpleSpec(const SLHAea::Coll& input)
       : SLHASimpleSpec(input)
      {}

      /// Copy constructor
      DMsimpVectorMedVectorDMSimpleSpec(const DMsimpVectorMedVectorDMSimpleSpec& other)
       : SLHASimpleSpec(other)
      {}

      /// Destructor
      virtual ~DMsimpVectorMedVectorDMSimpleSpec() {};

      static int index_offset() {return 0;}

      /// Construct the SubSpectrumContents
      const SpectrumContents::DMsimpVectorMedVectorDM contents;

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

        getters[dimensionless].map0["gVXv"] =  &Model::get_gVXv;
        getters[dimensionless].map0["gVq"] =  &Model::get_gVq;
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
        getters[Pole_Mass].map0["~Xv"] =  &Model::get_XvPoleMass;
        getters[Pole_Mass_1srd_low].map0["~Xv"] =  &Model::get_XvPoleMass_1srd_low;
        getters[Pole_Mass_1srd_high].map0["~Xv"] =  &Model::get_XvPoleMass_1srd_high;
        getters[Pole_Mass].map0["Y1"] =  &Model::get_Y1PoleMass;
        getters[Pole_Mass_1srd_low].map0["Y1"] =  &Model::get_Y1PoleMass_1srd_low;
        getters[Pole_Mass_1srd_high].map0["Y1"] =  &Model::get_Y1PoleMass_1srd_high;

        return getters;
      }

    };
  }
} // namespace Gambit
#endif
