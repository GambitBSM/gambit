//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Implementation of DMEFT
///  DarkBit routines.
///
///  Authors (add name and date if you modify):    
///       *** Automatically created by GUM ***     
///                                                
///  \author The GAMBIT Collaboration             
///  \date 12:32PM on October 15, 2019
///
///  \author Sanjay Bloor
///         (sanjay.bloor12@imperial.ac.uk)
///  \date Oct 2019
///                                                  
///  ********************************************* 

#include "boost/make_shared.hpp"

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/DarkBit/DarkBit_rollcall.hpp"
#include "gambit/Utils/ascii_table_reader.hpp"
#include "gambit/DarkBit/DarkBit_utils.hpp"

namespace Gambit
{
  namespace DarkBit
  {
    class DMEFT_3flavour
    {
      public:
      /// Initialize DMEFT_3flavour object (branching ratios etc)
      DMEFT_3flavour() {};
      ~DMEFT_3flavour() {};

    };

    void DarkMatter_ID_DMEFT_3flavour(std::string& result){ result = "chi"; }

    void DarkMatterConj_ID_DMEFT_3flavour(std::string& result){ result = "chi~"; }

    /// Relativistic Wilson Coefficients for direct detection
    /// DMEFT basis is the same as that used in DirectDM
    void DD_rel_WCs_flavscheme_DMEFT_3flavour(map_str_dbl& result)
    {
      using namespace Pipes::DD_rel_WCs_flavscheme_DMEFT_3flavour;

      // In our model the Wilson coefficients are dimensionless
      // The new-physics scale is fixed to 2 GeV
      double Lambda = 2;

      double C51  = *Param["C51"];
      double C52  = *Param["C52"];
      
      double C61u  = *Param["C61u"];
      double C62u  = *Param["C62u"];
      double C63u  = *Param["C63u"];
      double C64u  = *Param["C64u"];
      
      double C61d  = *Param["C61d"];
      double C62d  = *Param["C62d"];
      double C63d  = *Param["C63d"];
      double C64d  = *Param["C64d"];

      // So we need to rescale them by the appropriate scale
      result["C51"]  = C51/Lambda;
      result["C52"]  = C52/Lambda;

      // Assume equal couplings to down and strange quarks

      result["C61d"]  = C61d/pow(Lambda, 2.);
      result["C61u"]  = C61u/pow(Lambda, 2.);
      result["C61s"]  = C61d/pow(Lambda, 2.);

      result["C62d"]  = C62d/pow(Lambda, 2.);
      result["C62u"]  = C62u/pow(Lambda, 2.);
      result["C62s"]  = C62d/pow(Lambda, 2.);

      result["C63d"]  = C63d/pow(Lambda, 2.);
      result["C63u"]  = C63u/pow(Lambda, 2.);
      result["C63s"]  = C63d/pow(Lambda, 2.);

      result["C64d"]  = C64d/pow(Lambda, 2.);
      result["C64u"]  = C64u/pow(Lambda, 2.);
      result["C64s"]  = C64d/pow(Lambda, 2.);
    } // DD_rel_WCs_flavscheme_DMEFT
    
  } //namespace DarkBit
  
} //namespace Gambit

