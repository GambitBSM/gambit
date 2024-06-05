//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Class defining the parameters that SubSpectrum
///  objects providing VLQ
///  spectrum data must provide.
///
///  Authors (add name and date if you modify):    
///       *** Automatically created by GUM ***     
///                                                
///  \author The GAMBIT Collaboration             
///  \date 11:38AM on June 05, 2024
///                                                
///  ********************************************* 

#ifndef __VLQ_contents_hpp__
#define __VLQ_contents_hpp__

#include "gambit/Models/SpectrumContents/RegisteredSpectra.hpp"

namespace Gambit
{
  SpectrumContents::VLQ::VLQ()
  {
    setName("VLQ");
    
    std::vector<int> scalar = initVector(1); // i.e. get(Par::Tag, "name")
    std::vector<int> m3x3  = initVector(3,3); // i.e. get(Par::Tag, "name", i, j)
    
    addParameter(Par::dimensionless, "KBLh1", scalar, "KBLH", 1);
    addParameter(Par::dimensionless, "KBLh2", scalar, "KBLH", 2);
    addParameter(Par::dimensionless, "KBLh3", scalar, "KBLH", 3);
    addParameter(Par::dimensionless, "KBLw1", scalar, "KBLW", 1);
    addParameter(Par::dimensionless, "KBLw2", scalar, "KBLW", 2);
    addParameter(Par::dimensionless, "KBLw3", scalar, "KBLW", 3);
    addParameter(Par::dimensionless, "KBLz1", scalar, "KBLZ", 1);
    addParameter(Par::dimensionless, "KBLz2", scalar, "KBLZ", 2);
    addParameter(Par::dimensionless, "KBLz3", scalar, "KBLZ", 3);
    addParameter(Par::dimensionless, "KBRh1", scalar, "KBRH", 1);
    addParameter(Par::dimensionless, "KBRh2", scalar, "KBRH", 2);
    addParameter(Par::dimensionless, "KBRh3", scalar, "KBRH", 3);
    addParameter(Par::dimensionless, "KBRw1", scalar, "KBRW", 1);
    addParameter(Par::dimensionless, "KBRw2", scalar, "KBRW", 2);
    addParameter(Par::dimensionless, "KBRw3", scalar, "KBRW", 3);
    addParameter(Par::dimensionless, "KBRz1", scalar, "KBRZ", 1);
    addParameter(Par::dimensionless, "KBRz2", scalar, "KBRZ", 2);
    addParameter(Par::dimensionless, "KBRz3", scalar, "KBRZ", 3);
    addParameter(Par::dimensionless, "KTLh1", scalar, "KTLH", 1);
    addParameter(Par::dimensionless, "KTLh2", scalar, "KTLH", 2);
    addParameter(Par::dimensionless, "KTLh3", scalar, "KTLH", 3);
    addParameter(Par::dimensionless, "KTLw1", scalar, "KTLW", 1);
    addParameter(Par::dimensionless, "KTLw2", scalar, "KTLW", 2);
    addParameter(Par::dimensionless, "KTLw3", scalar, "KTLW", 3);
    addParameter(Par::dimensionless, "KTLz1", scalar, "KTLZ", 1);
    addParameter(Par::dimensionless, "KTLz2", scalar, "KTLZ", 2);
    addParameter(Par::dimensionless, "KTLz3", scalar, "KTLZ", 3);
    addParameter(Par::dimensionless, "KTRh1", scalar, "KTRH", 1);
    addParameter(Par::dimensionless, "KTRh2", scalar, "KTRH", 2);
    addParameter(Par::dimensionless, "KTRh3", scalar, "KTRH", 3);
    addParameter(Par::dimensionless, "KTRw1", scalar, "KTRW", 1);
    addParameter(Par::dimensionless, "KTRw2", scalar, "KTRW", 2);
    addParameter(Par::dimensionless, "KTRw3", scalar, "KTRW", 3);
    addParameter(Par::dimensionless, "KTRz1", scalar, "KTRZ", 1);
    addParameter(Par::dimensionless, "KTRz2", scalar, "KTRZ", 2);
    addParameter(Par::dimensionless, "KTRz3", scalar, "KTRZ", 3);
    addParameter(Par::dimensionless, "KXL1", scalar, "KXLW", 1);
    addParameter(Par::dimensionless, "KXL2", scalar, "KXLW", 2);
    addParameter(Par::dimensionless, "KXL3", scalar, "KXLW", 3);
    addParameter(Par::dimensionless, "KXR1", scalar, "KXRW", 1);
    addParameter(Par::dimensionless, "KXR2", scalar, "KXRW", 2);
    addParameter(Par::dimensionless, "KXR3", scalar, "KXRW", 3);
    addParameter(Par::dimensionless, "KYL1", scalar, "KYLW", 1);
    addParameter(Par::dimensionless, "KYL2", scalar, "KYLW", 2);
    addParameter(Par::dimensionless, "KYL3", scalar, "KYLW", 3);
    addParameter(Par::dimensionless, "KYR1", scalar, "KYRW", 1);
    addParameter(Par::dimensionless, "KYR2", scalar, "KYRW", 2);
    addParameter(Par::dimensionless, "KYR3", scalar, "KYRW", 3);
    addParameter(Par::mass1, "vev", scalar, "VEVS", 1);
    addParameter(Par::dimensionless, "g1", scalar, "GAUGE", 1);
    addParameter(Par::dimensionless, "g2", scalar, "GAUGE", 2);
    addParameter(Par::dimensionless, "g3", scalar, "GAUGE", 3);
    addParameter(Par::dimensionless, "sinW2", scalar, "SINTHETAW", 1);
    addParameter(Par::dimensionless, "Yd", m3x3, "YD", 1);
    addParameter(Par::dimensionless, "Yu", m3x3, "YU", 1);
    addParameter(Par::dimensionless, "Ye", m3x3, "YE", 1);
    addParameter(Par::Pole_Mass, "h0_1", scalar, "MASS", 25);
    addParameter(Par::Pole_Mass, "x", scalar, "MASS", 6000005);
    addParameter(Par::Pole_Mass, "tp", scalar, "MASS", 6000006);
    addParameter(Par::Pole_Mass, "bp", scalar, "MASS", 6000007);
    addParameter(Par::Pole_Mass, "y", scalar, "MASS", 6000008);
    
  } // namespace Models
} // namespace Gambit
#endif
