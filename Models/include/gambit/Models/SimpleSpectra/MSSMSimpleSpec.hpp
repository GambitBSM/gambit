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
///  \author Ben Farmer
///          (benjamin.farmer@fysik.su.se)
///  \date 2015 Apr
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2016 Oct
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2019 Mar
///  
///  *********************************************

#ifndef __MSSMSimpleSpec_hpp__
#define __MSSMSimpleSpec_hpp__

#include "gambit/Elements/spec.hpp"
#include "gambit/Models/SimpleSpectra/SLHASimpleSpec.hpp"
#include "gambit/Models/SpectrumContents/RegisteredSpectra.hpp"
#include  <boost/preprocessor/control/iif.hpp>


/// Macros to declare and define pole mass getters
/// Each macro declares or defines getters for pole masses and uncertainties
/// @{

// Macros for the declaration of getters
// with no index
#define DEC_MX_POLE_0(NAME, SUFFIX)                                       \
  double CAT_4(get_,NAME,_pole,SUFFIX)() const;                           \
  double CAT_3(get_,NAME,_pole_1srd_high)() const;                        \
  double CAT_3(get_,NAME,_pole_1srd_low)() const;

// with 1 index
#define DEC_MX_POLE_1(NAME,SUFFIX)                        \
  double CAT_4(get_,NAME,_pole,SUFFIX)(int i) const;      \
  double CAT_3(get_,NAME,_pole_1srd_high)(int i) const;   \
  double CAT_3(get_,NAME,_pole_1srd_low)(int i) const;

// Macro for the definitions of getters
// with no index
#define GET_MX_POLE_0(NAME,PREFFIX,SUFFIX,PDG)                                          \
  double CAT_5(PREFFIX,ea::get_,NAME,_pole,SUFFIX)() const                          \
  {                                                                             \
    return getdata("MASS",PDG);                                                 \
  }                                                                             \
  double CAT_4(PREFFIX,ea::get_,NAME,_pole_1srd_high)() const                       \
  {                                                                             \
    return finddata("DMASS",PDG) ? getdata("DMASS",PDG) : default_uncert;       \
  }                                                                             \
  double CAT_4(PREFFIX,ea::get_,NAME,_pole_1srd_low)() const                        \
  {                                                                             \
    return finddata("DMASS",PDG) ? getdata("DMASS",PDG) : default_uncert;       \
  }

// with 1 index
#define GET_MX_POLE_1(NAME,PREFFIX,SUFFIX,...)                                                  \
  double CAT_5(PREFFIX,ea::get_,NAME,_pole,SUFFIX)(int i) const                             \
  {                                                                                     \
    std::vector<int> pdgs = {__VA_ARGS__};                                                       \
    if(i > 0 and unsigned(i) <= pdgs.size())                                                      \
      return getdata("MASS",pdgs[i-1]);                                                 \
    else                                                                                \
      utils_error().raise(LOCAL_INFO, "Invalid index input to CAT_3(get_,NAME,_pole)! Please check index range limits in wrapper SubSpectrum class"); return -1;                  \
  }                                                                                     \
  double CAT_4(PREFFIX,ea::get_,NAME,_pole_1srd_high)(int i) const                          \
  {                                                                                     \
    std::vector<int> pdgs = {__VA_ARGS__};                                                       \
    if(i > 0 and unsigned(i) <= pdgs.size())                                                      \
      return finddata("DMASS",pdgs[i-1]) ? getdata("DMASS",pdgs[i-1]) : default_uncert; \
    else                                                                                \
      utils_error().raise(LOCAL_INFO, "Invalid index input to CAT_3(get_,NAME,_pole_1srd_high)! Please check index range limits in wrapper SubSpectrum class"); return -1;        \
  }                                                                                     \
  double CAT_4(PREFFIX,ea::get_,NAME,_pole_1srd_low)(int i) const                           \
  {                                                                                     \
    std::vector<int> pdgs = {__VA_ARGS__};                                                       \
    if(i > 0 and unsigned(i) <= pdgs.size())                                                      \
      return finddata("DMASS",pdgs[i-1]) ? getdata("DMASS",pdgs[i-1]) : default_uncert; \
    else                                                                                \
      utils_error().raise(LOCAL_INFO, "Invalid index input to CAT_3(get_,NAME,_pole_1srd_low)! Please check index range limits in wrapper SubSpectrum class"); return -1;         \
  }
 
/// @}


namespace Gambit
{

      /// Skeleton "model" class which interacts with an SLHAea object
      /// Some common functions defined in base class
      class MSSMea: public SLHAeaModel
      {

         protected:
           double default_uncert = 0.03;

         public:
           /// @{ Constructors
           MSSMea();
           MSSMea(const SLHAstruct& input);
           /// @}

           /// @{ Getters for MSSM information
           double get_Mu()  const;
           double get_v()   const; 
           double get_mA2() const;
           double get_BMu() const;
           double get_vd()  const;
           double get_vu()  const;
           double get_tanbeta() const;
           double get_tanbeta_mZ() const;

           double get_MassB () const;
           double get_MassWB() const;
           double get_MassG () const;
           double get_mHd2()   const;
           double get_mHu2()   const;

           double get_mq2(int i, int j) const;
           double get_ml2(int i, int j) const;
           double get_md2(int i, int j) const;
           double get_mu2(int i, int j) const;
           double get_me2(int i, int j) const;

           double get_TYd(int i, int j) const;
           double get_TYu(int i, int j) const;
           double get_TYe(int i, int j) const;

           double get_Yd(int i, int j) const;
           double get_Yu(int i, int j) const;
           double get_Ye(int i, int j) const;

           double get_g1() const;
           double get_g2() const;
           double get_g3() const;
           double get_sinthW2_DRbar() const;

           DEC_MX_POLE_0(MGlu,)

           DEC_MX_POLE_1(Mhh,_slha)
           DEC_MX_POLE_0(MAh,)
           DEC_MX_POLE_0(MHpm,)
           DEC_MX_POLE_0(MW,)

           DEC_MX_POLE_1(MCha,_slha)
           DEC_MX_POLE_1(MSd,_slha)
           DEC_MX_POLE_1(MSu,_slha)
           DEC_MX_POLE_1(MSe,_slha)
           DEC_MX_POLE_1(MSv,_slha)
           DEC_MX_POLE_1(MChi,_slha)

           // Pole Mixings
           double get_ZD_pole_slha(int i, int j) const;
           double get_ZU_pole_slha(int i, int j) const;
           double get_ZV_pole_slha(int i, int j) const;
           double get_ZE_pole_slha(int i, int j) const;
           double get_ZH_pole_slha(int i, int j) const;
           double get_ZA_pole_slha(int i, int j) const;
           double get_ZP_pole_slha(int i, int j) const;
           double get_ZN_pole_slha(int i, int j) const;
           double get_UM_pole_slha(int i, int j) const;
           double get_UP_pole_slha(int i, int j) const;
           /// @}
      };

      class MSSMSimpleSpec;

      /// Specialisation of traits class needed to inform base spectrum class of the Model and Input types
      template <>
      struct SpecTraits<MSSMSimpleSpec>
      {
          static std::string name() { return "MSSMSimpleSpec"; }
          typedef SpectrumContents::MSSM Contents;
          typedef MSSMea     Model;
          typedef DummyInput Input; // DummyInput is just an empty struct
      };

      /// MSSM specialisation of SLHAea object wrapper version of SubSpectrum class
      class MSSMSimpleSpec : public SLHASimpleSpec<MSSMSimpleSpec>
      {
         private:
            /// Set pole mass uncertainties
            //void set_pole_mass_uncertainties(double);

         public:
            /// Constructors.
            /// The optional double uncert is the uncertainty to assign to pole masses (default is 3%).
            /// @{
            MSSMSimpleSpec(/*double uncert = 0.03*/);
            MSSMSimpleSpec(const SLHAstruct&/*, double uncert = 0.03*/);
            MSSMSimpleSpec(const MSSMSimpleSpec&/*, double uncert = 0.03*/);
            /// @}

            /// Destructor
            virtual ~MSSMSimpleSpec() {};

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
