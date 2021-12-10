//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Implementation of SpecBit routines for 
///  DMEFT.
///
///  Authors (add name and date if you modify):    
///       *** Automatically created by GUM ***     
///                                                
///  \author The GAMBIT Collaboration             
///  \date 12:32PM on October 15, 2019
///                                                
///  ********************************************* 

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/Elements/spectrum.hpp"
#include "gambit/Utils/stream_overloads.hpp"
#include "gambit/Utils/util_macros.hpp"
#include "gambit/SpecBit/RegisteredSpectra.hpp"
#include "gambit/SpecBit/SpecBit_rollcall.hpp"
#include "gambit/SpecBit/SpecBit_helpers.hpp"

namespace Gambit
{
  
  namespace SpecBit
  {
    using namespace LogTags;
    
    /// Get a simple wrapper for Spectrum object.
    void get_DMEFT_spectrum(Spectrum& result)
    {
      namespace myPipe = Pipes::get_DMEFT_spectrum;
      const SMInputs& sminputs = *myPipe::Dep::SMINPUTS;
      
      // Initialise an SLHAea object to carry the Dirac plus Higgs sector information
      SLHAea::Coll slha;
      SLHAea_add_block(slha, "MASS");
      SLHAea_add_block(slha, "VEVS");
      SLHAea_add_block(slha, "WISLON");
      SLHAea_add_block(slha, "SINTHETAW");
      SLHAea_add_block(slha, "GAUGE");
      SLHAea_add_block(slha, "YD");
      SLHAea_add_block(slha, "YU");
      SLHAea_add_block(slha, "YE");

      // BSM parameters
      double Lambda = *myPipe::Param.at("Lambda");
      slha["WILSON"][""] << 1 << Lambda << "# lambda";
      slha["WILSON"][""] << 2 << *myPipe::Param.at("C51") <<  "# C_{51}";
      slha["WILSON"][""] << 3 << *myPipe::Param.at("C52") <<  "# C_{52}";
      slha["WILSON"][""] << 4 << *myPipe::Param.at("C61") <<  "# C_{61}";
      slha["WILSON"][""] << 5 << *myPipe::Param.at("C62") <<  "# C_{62}";
      slha["WILSON"][""] << 6 << *myPipe::Param.at("C63") <<  "# C_{63}";
      slha["WILSON"][""] << 7 << *myPipe::Param.at("C64") <<  "# C_{64}";
      slha["WILSON"][""] << 8 << *myPipe::Param.at("C71") <<  "# C_{71}";
      slha["WILSON"][""] << 9 << *myPipe::Param.at("C72") <<  "# C_{72}";
      slha["WILSON"][""] << 10 << *myPipe::Param.at("C73") <<  "# C_{73}";
      slha["WILSON"][""] << 11 << *myPipe::Param.at("C74") <<  "# C_{74}";
      slha["WILSON"][""] << 12 << *myPipe::Param.at("C75") <<  "# C_{75}";
      slha["WILSON"][""] << 13 << *myPipe::Param.at("C76") <<  "# C_{76}";
      slha["WILSON"][""] << 14 << *myPipe::Param.at("C77") <<  "# C_{77}";
      slha["WILSON"][""] << 15 << *myPipe::Param.at("C78") <<  "# C_{78}";
      slha["WILSON"][""] << 16 << *myPipe::Param.at("C79") <<  "# C_{79}";
      slha["WILSON"][""] << 17 << *myPipe::Param.at("C710") <<  "# C_{710}";
      // Pole mass inputs (mh is a nuiisance parameter?)
      double m_chi = *myPipe::Param.at("mchi"); 
      slha["MASS"][""] << 62 << m_chi << "# m_chi";
      slha["MASS"][""] << 25 << *myPipe::Param.at("mH") << "# m_H";
      // running top mass input, must be standard model msbar mt(mt)
      slha["MRUN"][""] << 6 << *myPipe::Param.at("mtrunIN") << "# m_t (MSbar)";
      // Invalidate point if the EFT is violated for DM annihilation i.e. 2*m_DM > Lambda
      // Default: true
      if (myPipe::runOptions->getValueOrDef<bool>(true,"impose_EFT_validity"))
      {
        if (Lambda < (2*m_chi))
        {
          std::ostringstream msg;
          msg << "Parameter point [mchi, Lambda] = [" << m_chi << " GeV, "
              << Lambda << " GeV] does not satisfy the EFT.";
          invalid_point().raise(msg.str());
        }
      }
      else {}
      
      // quantities needed to fill container spectrum
      double alpha_em = 1.0 / sminputs.alphainv;
      double C = alpha_em * pi / (sminputs.GF * pow(2,0.5));
      double sinW2 = 0.5 - pow( 0.25 - C/pow(sminputs.mZ,2) , 0.5);
      double cosW2 = 0.5 + pow( 0.25 - C/pow(sminputs.mZ,2) , 0.5);
      double e = pow( 4*pi*( alpha_em ),0.5);
      double vev = 1. / sqrt(sqrt(2.)*sminputs.GF);
      
      // Standard model
      slha["SINTHETAW"][""] << 1 << sinW2 << "# sinW2";
      slha["VEVS"][""] << 1 <<  vev << "# vev";

      // Gauge couplings
      slha["GAUGE"][""] << 1 << e / sqrt(cosW2) << "# g1";
      slha["GAUGE"][""] << 2 << e / sqrt(sinW2) << "# g2";
      slha["GAUGE"][""] << 3 << pow( 4*pi*( sminputs.alphaS ),0.5) << "# g3";

      // Yukawas
      double sqrt2v = pow(2.0,0.5)/vev;
      slha["YU"][""] << 1 << 1 << sqrt2v * sminputs.mU << "# Yu(1,1)";
      slha["YU"][""] << 2 << 2 << sqrt2v * sminputs.mCmC << "# Yu(2,2)";
      slha["YU"][""] << 3 << 3 << sqrt2v * sminputs.mT << "# Yu(3,3)";
      slha["YE"][""] << 1 << 1 << sqrt2v * sminputs.mE << "# Ye(1,1)";
      slha["YE"][""] << 2 << 2 << sqrt2v * sminputs.mMu << "# Ye(2,2)";
      slha["YE"][""] << 3 << 3 << sqrt2v * sminputs.mTau << "# Ye(3,3)";
      slha["YD"][""] << 1 << 1 << sqrt2v * sminputs.mD << "# Yd(1,1)";
      slha["YD"][""] << 2 << 2 << sqrt2v * sminputs.mS << "# Yd(2,2)";
      slha["YD"][""] << 3 << 3 << sqrt2v * sminputs.mBmB << "# Yd(3,3)";

      // SpectrumContents struct
      SpectrumContents::DMEFT dmeft;

      // Create spectrum object
      // Take mZ as the spectrum scale
      result = Spectrum(slha, dmeft, sminputs.mZ, false);

      // Retrieve any mass cuts
      result.check_mass_cuts(*myPipe::runOptions);

      // TODO: TG: I don't know what to do with this in the new setting, Peter, can you have a look?
      // We have decided to calculate mT pole from the input running mt
      // using only one-loop QCD corrections
      // See footnote 9 https://link.springer.com/article/10.1007/JHEP11(2019)150

      // Approximate alpha_S(mtop) as alpha_S(mZ) because even a
      // one-loop correction here will lead to O(alpha_S^2) correction on mT
      // Via correspondence with the authors we checked this
      // approximation matches what is done in
      // https://link.springer.com/article/10.1007/JHEP11(2019)150
      // which we also validated numerically
      
      //const double alpha_S_mtop = sminputs.alphaS;
      // Now extract pole mass from running mass
      //const double mtop_MSBAR_mtop = DMEFTmodel.mtrun; // must be SM MSbar mt(mt)
      //const double mtop_pole = mtop_MSBAR_mtop * (1. + 4. / 3.
			//			  * alpha_S_mtop / M_PI);

      // Make a local sminputs so we can change pole mT to the one we calculated
      //SMInputs localsminputs = sminputs;
      //localsminputs.mT = mtop_pole;
      // We don't supply a LE subspectrum here; an SMSimpleSpec will therefore be automatically created from 'localsminputs'
      //result = Spectrum(spec,localsminputs,&myPipe::Param,mass_cut,mass_ratio_cut);

    }

    void get_DMEFT_spectrum_as_map(std::map<std::string,double>& specmap)
    {
      namespace myPipe = Pipes::get_DMEFT_spectrum_as_map;
      const Spectrum& spec(*myPipe::Dep::DMEFT_spectrum);
      fill_map_from_spectrum<SpectrumContents::DMEFT>(specmap, spec);
    }
    
  }
  
}
