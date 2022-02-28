//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  A simple SubSpectrum wrapper for
///  DMEFT. No RGEs included.
///
///  Authors (add name and date if you modify):    
///       *** Automatically created by GUM ***     
///                                                
///  \author The GAMBIT Collaboration             
///  \date 12:32PM on October 15, 2019
///                                                
///  ********************************************* 

#ifndef __DMEFTSimpleSpec_hpp__
#define __DMEFTSimpleSpec_hpp__

#include "gambit/Elements/spec.hpp"
#include "gambit/Models/SpectrumContents/RegisteredSpectra.hpp"

namespace Gambit
{
  namespace Models
  {
    /// Simple DMEFT model object.
    struct DMEFTModel
    {
      double DMEFT_Lambda;
      double DMEFT_C51;
      double DMEFT_C52;
      double DMEFT_C61;
      double DMEFT_C62;
      double DMEFT_C63;
      double DMEFT_C64;
      double DMEFT_C71;
      double DMEFT_C72;
      double DMEFT_C73;
      double DMEFT_C74;
      double DMEFT_C75;
      double DMEFT_C76;
      double DMEFT_C77;
      double DMEFT_C78;
      double DMEFT_C79;
      double DMEFT_C710;
      double vev;
      double g1;
      double g2;
      double g3;
      double sinW2;
      double Yd[3][3];
      double Yu[3][3];
      double Ye[3][3];
      double DMEFT_chi_Pole_Mass;
      double DMEFT_h0_1_Pole_Mass;
      double mtrun; // input mtrun for this model
    };
    
    /// Forward declare the wrapper class so that we can use it
    /// as the template parameter for the SpecTraits specialisation.
    class DMEFTSimpleSpec;
  }
  
  /// Specialisation of traits class needed to inform base spectrum class of the Model and Input types
  template <> 
  struct SpecTraits<Models::DMEFTSimpleSpec> : DefaultTraits
  {
    static std::string name() { return "DMEFTSimpleSpec"; }
    typedef SpectrumContents::DMEFT Contents;
  };
  
  namespace Models
  {
    class DMEFTSimpleSpec : public Spec<DMEFTSimpleSpec>
    {
      private:
       DMEFTModel  params;
      typedef DMEFTSimpleSpec Self;
      
      public:
      /// Constructors & destructors
      DMEFTSimpleSpec(const DMEFTModel& p)
       : params(p)
      {}
      
      static int index_offset() {return -1;}
      
      /// Construct the SubSpectrumContents
      const SpectrumContents::DMEFT contents;
      
      /// Add SLHAea object using the SimpleSpec_to_SLHAea routine
      void add_to_SLHAea(int /*slha_version*/, SLHAea::Coll& slha) const
      {
        // Add SPINFO data if not already present
        SLHAea_add_GAMBIT_SPINFO(slha);
        
        // All blocks given in the SimpleSpec
        
        add_SimpleSpec_to_SLHAea(*this, slha, contents);
      }
      
      /// Wrapper functions to parameter object.
      double get_Lambda() const { return params.DMEFT_Lambda; }
      double get_C51() const { return params.DMEFT_C51; }
      double get_C52() const { return params.DMEFT_C52; }
      double get_C61() const { return params.DMEFT_C61; }
      double get_C62() const { return params.DMEFT_C62; }
      double get_C63() const { return params.DMEFT_C63; }
      double get_C64() const { return params.DMEFT_C64; }
      double get_C71() const { return params.DMEFT_C71; }
      double get_C72() const { return params.DMEFT_C72; }
      double get_C73() const { return params.DMEFT_C73; }
      double get_C74() const { return params.DMEFT_C74; }
      double get_C75() const { return params.DMEFT_C75; }
      double get_C76() const { return params.DMEFT_C76; }
      double get_C77() const { return params.DMEFT_C77; }
      double get_C78() const { return params.DMEFT_C78; }
      double get_C79() const { return params.DMEFT_C79; }
      double get_C710() const { return params.DMEFT_C710; }
      double get_vev() const { return params.vev; }
      double get_g1() const { return params.g1; }
      double get_g2() const { return params.g2; }
      double get_g3() const { return params.g3; }
      double get_sinW2() const { return params.sinW2; }
      double get_Yd(int i, int j) const { return params.Yd[i][j]; }
      double get_Yu(int i, int j) const { return params.Yu[i][j]; }
      double get_Ye(int i, int j) const { return params.Ye[i][j]; }
      double get_chiPoleMass() const { return params.DMEFT_chi_Pole_Mass; }
      double get_h0_1PoleMass() const { return params.DMEFT_h0_1_Pole_Mass; }
      double get_mtrun() const {return params.mtrun;}
      
      void set_Lambda(double in) { params.DMEFT_Lambda=in; }
      void set_C51(double in) { params.DMEFT_C51=in; }
      void set_C52(double in) { params.DMEFT_C52=in; }
      void set_C61(double in) { params.DMEFT_C61=in; }
      void set_C62(double in) { params.DMEFT_C62=in; }
      void set_C63(double in) { params.DMEFT_C63=in; }
      void set_C64(double in) { params.DMEFT_C64=in; }
      void set_C71(double in) { params.DMEFT_C71=in; }
      void set_C72(double in) { params.DMEFT_C72=in; }
      void set_C73(double in) { params.DMEFT_C73=in; }
      void set_C74(double in) { params.DMEFT_C74=in; }
      void set_C75(double in) { params.DMEFT_C75=in; }
      void set_C76(double in) { params.DMEFT_C76=in; }
      void set_C77(double in) { params.DMEFT_C77=in; }
      void set_C78(double in) { params.DMEFT_C78=in; }
      void set_C79(double in) { params.DMEFT_C79=in; }
      void set_C710(double in) { params.DMEFT_C710=in; }
      void set_vev(double in) { params.vev=in; }
      void set_g1(double in) { params.g1=in; }
      void set_g2(double in) { params.g2=in; }
      void set_g3(double in) { params.g3=in; }
      void set_sinW2(double in) { params.sinW2=in; }
      void set_Yd(double in, int i, int j) { params.Yd[i][j]=in; }
      void set_Yu(double in, int i, int j) { params.Yu[i][j]=in; }
      void set_Ye(double in, int i, int j) { params.Ye[i][j]=in; }
      void set_chiPoleMass(double in) { params.DMEFT_chi_Pole_Mass=in; }
      void set_h0_1PoleMass(double in) { params.DMEFT_h0_1_Pole_Mass=in; }
      void set_mtrun(double in) { params.mtrun=in; }
      /// Map fillers
      static GetterMaps fill_getter_maps()
      {
        GetterMaps getters;
        
        typedef typename MTget::FInfo2W FInfo2W;
        static const int i012v[] = {0,1,2};
        static const std::set<int> i012(i012v, Utils::endA(i012v));
        
        using namespace Par;
        
        getters[mass1].map0W["Lambda"] =  &Self::get_Lambda;
        getters[dimensionless].map0W["C51"] =  &Self::get_C51;
        getters[dimensionless].map0W["C52"] =  &Self::get_C52;
        getters[dimensionless].map0W["C61"] =  &Self::get_C61;
        getters[dimensionless].map0W["C62"] =  &Self::get_C62;
        getters[dimensionless].map0W["C63"] =  &Self::get_C63;
        getters[dimensionless].map0W["C64"] =  &Self::get_C64;
        getters[dimensionless].map0W["C71"] =  &Self::get_C71;
        getters[dimensionless].map0W["C72"] =  &Self::get_C72;
        getters[dimensionless].map0W["C73"] =  &Self::get_C73;
        getters[dimensionless].map0W["C74"] =  &Self::get_C74;
        getters[dimensionless].map0W["C75"] =  &Self::get_C75;
        getters[dimensionless].map0W["C76"] =  &Self::get_C76;
        getters[dimensionless].map0W["C77"] =  &Self::get_C77;
        getters[dimensionless].map0W["C78"] =  &Self::get_C78;
        getters[dimensionless].map0W["C79"] =  &Self::get_C79;
        getters[dimensionless].map0W["C710"] =  &Self::get_C710;
        getters[mass1].map0W["vev"] =  &Self::get_vev;
        getters[dimensionless].map0W["g1"] =  &Self::get_g1;
        getters[dimensionless].map0W["g2"] =  &Self::get_g2;
        getters[dimensionless].map0W["g3"] =  &Self::get_g3;
        getters[dimensionless].map0W["sinW2"] =  &Self::get_sinW2;
        getters[dimensionless].map2W["Yd"] = FInfo2W(&Self::get_Yd, i012, i012);
        getters[dimensionless].map2W["Yu"] = FInfo2W(&Self::get_Yu, i012, i012);
        getters[dimensionless].map2W["Ye"] = FInfo2W(&Self::get_Ye, i012, i012);
        getters[Pole_Mass].map0W["chi"] =  &Self::get_chiPoleMass;
        getters[Pole_Mass].map0W["h0_1"] =  &Self::get_h0_1PoleMass;
        getters[mass1].map0W["mtrun"] = &Self::get_mtrun;
        return getters;
      }
      
      static SetterMaps fill_setter_maps()
      {
        SetterMaps setters;
        
        typedef typename MTset::FInfo2W FInfo2W;
        static const int i012v[] = {0,1,2};
        static const std::set<int> i012(i012v, Utils::endA(i012v));
        
        using namespace Par;
        
        setters[dimensionless].map0W["Lambda"] =  &Self::set_Lambda;
        setters[dimensionless].map0W["C51"] =  &Self::set_C51;
        setters[dimensionless].map0W["C52"] =  &Self::set_C52;
        setters[dimensionless].map0W["C61"] =  &Self::set_C61;
        setters[dimensionless].map0W["C62"] =  &Self::set_C62;
        setters[dimensionless].map0W["C63"] =  &Self::set_C63;
        setters[dimensionless].map0W["C64"] =  &Self::set_C64;
        setters[dimensionless].map0W["C71"] =  &Self::set_C71;
        setters[dimensionless].map0W["C72"] =  &Self::set_C72;
        setters[dimensionless].map0W["C73"] =  &Self::set_C73;
        setters[dimensionless].map0W["C74"] =  &Self::set_C74;
        setters[dimensionless].map0W["C75"] =  &Self::set_C75;
        setters[dimensionless].map0W["C76"] =  &Self::set_C76;
        setters[dimensionless].map0W["C77"] =  &Self::set_C77;
        setters[dimensionless].map0W["C78"] =  &Self::set_C78;
        setters[dimensionless].map0W["C79"] =  &Self::set_C79;
        setters[dimensionless].map0W["C710"] =  &Self::set_C710;
        setters[mass1].map0W["vev"] =  &Self::set_vev;
        setters[dimensionless].map0W["g1"] =  &Self::set_g1;
        setters[dimensionless].map0W["g2"] =  &Self::set_g2;
        setters[dimensionless].map0W["g3"] =  &Self::set_g3;
        setters[dimensionless].map0W["sinW2"] =  &Self::set_sinW2;
        setters[dimensionless].map2W["Yd"] = FInfo2W(&Self::set_Yd, i012, i012);
        setters[dimensionless].map2W["Yu"] = FInfo2W(&Self::set_Yu, i012, i012);
        setters[dimensionless].map2W["Ye"] = FInfo2W(&Self::set_Ye, i012, i012);
        setters[Pole_Mass].map0W["chi"] =  &Self::set_chiPoleMass;
        setters[Pole_Mass].map0W["h0_1"] =  &Self::set_h0_1PoleMass;
        setters[mass1].map0W["mtrun"] = &Self::set_mtrun;
        return setters;
      }
    };
  }
} // namespace Gambit
#endif
