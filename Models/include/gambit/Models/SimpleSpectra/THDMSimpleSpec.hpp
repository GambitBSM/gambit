//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  A simple SubSpectrum wrapper for the TDHM model. No RGEs included.
///
///  *********************************************
///
///  Authors:
///  <!-- add name and date if you modify -->
///
///  \author Filip Rajec, July 2016
///  Orginal code by Ben Farmer
///
///  *********************************************

#ifndef __THDMSimpleSpec_hpp__
#define __THDMSimpleSpec_hpp__

#include "gambit/Elements/spec.hpp"
#include "gambit/Models/SpectrumContents/RegisteredSpectra.hpp"

namespace Gambit
{
  namespace Models
  {
    /// Simple extension of the SMHiggsSimpleSpec "model object"
    /// to include THDM parameters
    struct THDMModel
    {
        double lightHiggsMass;
        double heavyHiggsMass;
        double pseudoscalarHiggsMass;
        double chargedHiggsMass;
        double tanBeta;
        double m12_2;
        double lambda6;
        double lambda7;
        double alpha;
        double yukawaCoupling;
        
        double lambda1;
        double lambda2;
        double lambda3;
        double lambda4;
        double lambda5;

        double get_lightHiggsMass()              const { return lightHiggsMass; }
        double get_heavyHiggsMass()              const { return heavyHiggsMass; }
        double get_pseudoscalarHiggsMass()       const { return pseudoscalarHiggsMass; }
        double get_chargedHiggsMass()            const { return chargedHiggsMass; }
        double get_tanBeta()                     const { return tanBeta; }
        double get_m12_2()                       const { return m12_2; }
        double get_lambda6()                     const { return lambda6; }
        double get_lambda7()                     const { return lambda7; }
        double get_alpha()                       const { return alpha; }
        double get_yukawaCoupling()              const { return yukawaCoupling; }
        
        double get_lambda1()                     const { return lambda1;}
        double get_lambda2()                     const { return lambda2;}
        double get_lambda3()                     const { return lambda3;}
        double get_lambda4()                     const { return lambda4;}
        double get_lambda5()                     const { return lambda5;}
      
        void set_lightHiggsMass(double in)               { lightHiggsMass=in; }
        void set_heavyHiggsMass(double in)               { heavyHiggsMass=in; }
        void set_pseudoscalarHiggsMass(double in)        { pseudoscalarHiggsMass=in; }
        void set_chargedHiggsMass(double in)             { chargedHiggsMass=in; }
        void set_tanBeta(double in)                      { tanBeta=in;      }
        void set_m12_2(double in )                       { m12_2=in; }
        void set_lambda6(double in)                      { lambda6=in; }
        void set_lambda7(double in)                      { lambda7=in; }
        void set_alpha(double in)                        { alpha=in; }
        void set_yukawaCoupling(double in)               { yukawaCoupling=in; }

        void set_lambda1(double in)               { lambda1=in; }
        void set_lambda2(double in)               { lambda2=in; }
        void set_lambda3(double in)               { lambda3=in; }
        void set_lambda4(double in)               { lambda4=in; }
        void set_lambda5(double in)               { lambda5=in; }
    };
    
    /// Forward declare the wrapper class so that we can use it
    /// as the template parameter for the SpecTraits specialisation.
    class THDMSimpleSpec;
  }
  
  /// Specialisation of traits class needed to inform base spectrum class of the Model and Input types
  template <>
  struct SpecTraits<Models::THDMSimpleSpec>
  {
    static std::string name() { return "THDMSimpleSpec"; }
    typedef SpectrumContents::THDM Contents;
    typedef Models::THDMModel Model;
    typedef DummyInput              Input; // DummyInput is just an empty struct
  };
  
  namespace Models
  {
    class THDMSimpleSpec : public Spec<THDMSimpleSpec>
    {
    private:
      Model model;
      Input dummyinput;
      
    public:
      /// @{ Constructors/destructors
      THDMSimpleSpec(const Model& m)
      : model(m)
      , dummyinput()
      {}
      /// @}
      
      // Functions to interface Model and Input objects with the base 'Spec' class
      Model& get_Model() { return model; }
      Input& get_Input() { return dummyinput; /*unused here, but needs to be defined for the interface*/ }
      const Model& get_Model() const { return model; }
      const Input& get_Input() const { return dummyinput; /*unused here, but needs to be defined for the interface*/ }
      
      /// @{ Map fillers
      static GetterMaps fill_getter_maps()
      {
        GetterMaps map_collection;
        
        map_collection[Par::Pole_Mass].map0["mh0"]              = &Model::get_lightHiggsMass;
        map_collection[Par::Pole_Mass].map0["mH0"]              = &Model::get_heavyHiggsMass;
        map_collection[Par::Pole_Mass].map0["mA"]               = &Model::get_pseudoscalarHiggsMass;
        map_collection[Par::Pole_Mass].map0["mC"]               = &Model::get_chargedHiggsMass;
        map_collection[Par::dimensionless].map0["tanb"]         = &Model::get_tanBeta;
        map_collection[Par::mass1].map0["m12_2"]                = &Model::get_m12_2;
        map_collection[Par::dimensionless].map0["alpha"]        = &Model::get_alpha;
        map_collection[Par::dimensionless].map0["y_type"]       = &Model::get_yukawaCoupling;
        map_collection[Par::mass1].map0["lambda_1"]    = &Model::get_lambda1;
        map_collection[Par::mass1].map0["lambda_2"]    = &Model::get_lambda2;
        map_collection[Par::mass1].map0["lambda_3"]    = &Model::get_lambda3;
        map_collection[Par::mass1].map0["lambda_4"]    = &Model::get_lambda4;
        map_collection[Par::mass1].map0["lambda_5"]    = &Model::get_lambda5;
        map_collection[Par::mass1].map0["lambda_6"]    = &Model::get_lambda6;
        map_collection[Par::mass1].map0["lambda_7"]    = &Model::get_lambda7;
        
        return map_collection;
      }
      
      static SetterMaps fill_setter_maps()
      {
        SetterMaps map_collection;
        
        map_collection[Par::mass1].map0["mh0"]              = &Model::set_lightHiggsMass;
        map_collection[Par::mass1].map0["mH0"]              = &Model::set_heavyHiggsMass;
        map_collection[Par::mass1].map0["mA"]               = &Model::set_pseudoscalarHiggsMass;
        map_collection[Par::mass1].map0["mC"]               = &Model::set_chargedHiggsMass;
        map_collection[Par::dimensionless].map0["tanb"]     = &Model::set_tanBeta;
        map_collection[Par::mass1].map0["m12_2"]            = &Model::set_m12_2;
        map_collection[Par::mass1].map0["lambda_6"]         = &Model::set_lambda6;
        map_collection[Par::mass1].map0["lambda_7"]         = &Model::set_lambda7;
        map_collection[Par::dimensionless].map0["alpha"]    = &Model::set_alpha;
        map_collection[Par::dimensionless].map0["y_type"]   = &Model::set_yukawaCoupling;
          
        map_collection[Par::mass1].map0["lambda_1"]        = &Model::set_lambda1;
        map_collection[Par::mass1].map0["lambda_2"]        = &Model::set_lambda2;
        map_collection[Par::mass1].map0["lambda_3"]        = &Model::set_lambda3;
        map_collection[Par::mass1].map0["lambda_4"]        = &Model::set_lambda4;
        map_collection[Par::mass1].map0["lambda_5"]        = &Model::set_lambda5;       
        
      return map_collection;
      }
      /// @}
      
    };
    
  } // end Models namespace
} // end Gambit namespace

#endif
