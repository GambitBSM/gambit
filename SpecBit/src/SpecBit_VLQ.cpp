//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Implementation of SpecBit routines for 
///  VLQ.
///
///  Authors (add name and date if you modify):    
///       *** Automatically created by GUM ***     
///                                                
///  \author The GAMBIT Collaboration             
///  \date 09:55AM on June 04, 2024
///                                                
///  ********************************************* 

#include <string>
#include <sstream>

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/Elements/spectrum.hpp"
#include "gambit/Elements/spectrum_factories.hpp"
#include "gambit/Utils/stream_overloads.hpp"
#include "gambit/Utils/util_macros.hpp"

#include "gambit/SpecBit/SpecBit_rollcall.hpp"
#include "gambit/SpecBit/SpecBit_helpers.hpp"
#include "gambit/Models/SpectrumContents/RegisteredSpectra.hpp"
#include "gambit/SpecBit/QedQcdWrapper.hpp"
#include "gambit/Models/SimpleSpectra/VLQSimpleSpec.hpp"
#include "gambit/Models/SimpleSpectra/SMHiggsSimpleSpec.hpp"


namespace Gambit
{
  
  namespace SpecBit
  {
    using namespace LogTags;
    
    /// Get a (simple) Spectrum object wrapper for VLQ_spectrum model.
    void get_VLQ_spectrum(Spectrum& result)
    {
      namespace myPipe = Pipes::get_VLQ_spectrum;
      const SMInputs& sminputs = *myPipe::Dep::SMINPUTS;
      
      // Initialise SLHAea object 
      SLHAstruct slha;
      
      // Block KBLH
      SLHAea_add_block(slha, "KBLH");
      SLHAea_add(slha, "KBLH", 1, *myPipe::Param["KBLh1"]);
      SLHAea_add(slha, "KBLH", 2, *myPipe::Param["KBLh2"]);
      SLHAea_add(slha, "KBLH", 3, *myPipe::Param["KBLh3"]);
      
      // Block KBLW
      SLHAea_add_block(slha, "KBLW");
      SLHAea_add(slha, "KBLW", 1, *myPipe::Param["KBLw1"]);
      SLHAea_add(slha, "KBLW", 2, *myPipe::Param["KBLw2"]);
      SLHAea_add(slha, "KBLW", 3, *myPipe::Param["KBLw3"]);
      
      // Block KBLZ
      SLHAea_add_block(slha, "KBLZ");
      SLHAea_add(slha, "KBLZ", 1, *myPipe::Param["KBLz1"]);
      SLHAea_add(slha, "KBLZ", 2, *myPipe::Param["KBLz2"]);
      SLHAea_add(slha, "KBLZ", 3, *myPipe::Param["KBLz3"]);
      
      // Block KBRH
      SLHAea_add_block(slha, "KBRH");
      SLHAea_add(slha, "KBRH", 1, *myPipe::Param["KBRh1"]);
      SLHAea_add(slha, "KBRH", 2, *myPipe::Param["KBRh2"]);
      SLHAea_add(slha, "KBRH", 3, *myPipe::Param["KBRh3"]);
      
      // Block KBRW
      SLHAea_add_block(slha, "KBRW");
      SLHAea_add(slha, "KBRW", 1, *myPipe::Param["KBRw1"]);
      SLHAea_add(slha, "KBRW", 2, *myPipe::Param["KBRw2"]);
      SLHAea_add(slha, "KBRW", 3, *myPipe::Param["KBRw3"]);
      
      // Block KBRZ
      SLHAea_add_block(slha, "KBRZ");
      SLHAea_add(slha, "KBRZ", 1, *myPipe::Param["KBRz1"]);
      SLHAea_add(slha, "KBRZ", 2, *myPipe::Param["KBRz2"]);
      SLHAea_add(slha, "KBRZ", 3, *myPipe::Param["KBRz3"]);
      
      // Block KTLH
      SLHAea_add_block(slha, "KTLH");
      SLHAea_add(slha, "KTLH", 1, *myPipe::Param["KTLh1"]);
      SLHAea_add(slha, "KTLH", 2, *myPipe::Param["KTLh2"]);
      SLHAea_add(slha, "KTLH", 3, *myPipe::Param["KTLh3"]);
      
      // Block KTLW
      SLHAea_add_block(slha, "KTLW");
      SLHAea_add(slha, "KTLW", 1, *myPipe::Param["KTLw1"]);
      SLHAea_add(slha, "KTLW", 2, *myPipe::Param["KTLw2"]);
      SLHAea_add(slha, "KTLW", 3, *myPipe::Param["KTLw3"]);
      
      // Block KTLZ
      SLHAea_add_block(slha, "KTLZ");
      SLHAea_add(slha, "KTLZ", 1, *myPipe::Param["KTLz1"]);
      SLHAea_add(slha, "KTLZ", 2, *myPipe::Param["KTLz2"]);
      SLHAea_add(slha, "KTLZ", 3, *myPipe::Param["KTLz3"]);
      
      // Block KTRH
      SLHAea_add_block(slha, "KTRH");
      SLHAea_add(slha, "KTRH", 1, *myPipe::Param["KTRh1"]);
      SLHAea_add(slha, "KTRH", 2, *myPipe::Param["KTRh2"]);
      SLHAea_add(slha, "KTRH", 3, *myPipe::Param["KTRh3"]);
      
      // Block KTRW
      SLHAea_add_block(slha, "KTRW");
      SLHAea_add(slha, "KTRW", 1, *myPipe::Param["KTRw1"]);
      SLHAea_add(slha, "KTRW", 2, *myPipe::Param["KTRw2"]);
      SLHAea_add(slha, "KTRW", 3, *myPipe::Param["KTRw3"]);
      
      // Block KTRZ
      SLHAea_add_block(slha, "KTRZ");
      SLHAea_add(slha, "KTRZ", 1, *myPipe::Param["KTRz1"]);
      SLHAea_add(slha, "KTRZ", 2, *myPipe::Param["KTRz2"]);
      SLHAea_add(slha, "KTRZ", 3, *myPipe::Param["KTRz3"]);
      
      // Block KXLW
      SLHAea_add_block(slha, "KXLW");
      SLHAea_add(slha, "KXLW", 1, *myPipe::Param["KXL1"]);
      SLHAea_add(slha, "KXLW", 2, *myPipe::Param["KXL2"]);
      SLHAea_add(slha, "KXLW", 3, *myPipe::Param["KXL3"]);
      
      // Block KXRW
      SLHAea_add_block(slha, "KXRW");
      SLHAea_add(slha, "KXRW", 1, *myPipe::Param["KXR1"]);
      SLHAea_add(slha, "KXRW", 2, *myPipe::Param["KXR2"]);
      SLHAea_add(slha, "KXRW", 3, *myPipe::Param["KXR3"]);
      
      // Block KYLW
      SLHAea_add_block(slha, "KYLW");
      SLHAea_add(slha, "KYLW", 1, *myPipe::Param["KYL1"]);
      SLHAea_add(slha, "KYLW", 2, *myPipe::Param["KYL2"]);
      SLHAea_add(slha, "KYLW", 3, *myPipe::Param["KYL3"]);
      
      // Block KYRW
      SLHAea_add_block(slha, "KYRW");
      SLHAea_add(slha, "KYRW", 1, *myPipe::Param["KYR1"]);
      SLHAea_add(slha, "KYRW", 2, *myPipe::Param["KYR2"]);
      SLHAea_add(slha, "KYRW", 3, *myPipe::Param["KYR3"]);
      double vev = 1. / sqrt(sqrt(2.)*sminputs.GF);
      double sqrt2v = pow(2.0,0.5)/vev;
      
      SLHAea_add_block(slha, "VEVS");
      SLHAea_add(slha, "VEVS", 1, vev);
      
      SLHAea_add_block(slha, "HMIX");
      SLHAea_add(slha, "HMIX", 3, vev);
      
      
      // Block MASS
      SLHAea_add_block(slha, "MASS");
      SLHAea_add(slha, "MASS", 25, *myPipe::Param["mH"]);
      SLHAea_add(slha, "MASS", 6000005, *myPipe::Param["MX"]);
      SLHAea_add(slha, "MASS", 6000006, *myPipe::Param["MTP"]);
      SLHAea_add(slha, "MASS", 6000007, *myPipe::Param["MBP"]);
      SLHAea_add(slha, "MASS", 6000008, *myPipe::Param["MY"]);
      
      // quantities needed to fill container spectrum
      double alpha_em = 1.0 / sminputs.alphainv;
      double C = alpha_em * pi / (sminputs.GF * pow(2,0.5));
      double sinW2 = 0.5 - pow( 0.25 - C/pow(sminputs.mZ,2) , 0.5);
      double cosW2 = 0.5 + pow( 0.25 - C/pow(sminputs.mZ,2) , 0.5);
      double e = pow( 4*pi*( alpha_em ),0.5);
      
      SLHAea_add_block(slha, "GAUGE");
      SLHAea_add(slha, "GAUGE", 1, sqrt(5/3) * e / sqrt(cosW2) );
      SLHAea_add(slha, "GAUGE", 2, e / sqrt(sinW2));
      SLHAea_add(slha, "GAUGE", 3, pow( 4*pi*sminputs.alphaS,0.5) );
      
      SLHAea_add_block(slha, "SINTHETAW");
      SLHAea_add(slha, "SINTHETAW", 1, sinW2);
      
      SLHAea_add_block(slha, "YU");
      SLHAea_add(slha, "YU", 1, 1, sqrt2v*sminputs.mU, "u");
      SLHAea_add(slha, "YU", 1, 2, 0., "");
      SLHAea_add(slha, "YU", 1, 3, 0., "");
      SLHAea_add(slha, "YU", 2, 1, 0., "");
      SLHAea_add(slha, "YU", 2, 2, sqrt2v*sminputs.mCmC, "c");
      SLHAea_add(slha, "YU", 2, 3, 0., "");
      SLHAea_add(slha, "YU", 3, 1, 0., "");
      SLHAea_add(slha, "YU", 3, 2, 0., "");
      SLHAea_add(slha, "YU", 3, 3, sqrt2v*sminputs.mT, "t");
      
      SLHAea_add_block(slha, "YE");
      SLHAea_add(slha, "YE", 1, 1, sqrt2v*sminputs.mE, "e");
      SLHAea_add(slha, "YE", 1, 2, 0., "");
      SLHAea_add(slha, "YE", 1, 3, 0., "");
      SLHAea_add(slha, "YE", 2, 1, 0., "");
      SLHAea_add(slha, "YE", 2, 2, sqrt2v*sminputs.mMu, "mu");
      SLHAea_add(slha, "YE", 2, 3, 0., "");
      SLHAea_add(slha, "YE", 3, 1, 0., "");
      SLHAea_add(slha, "YE", 3, 2, 0., "");
      SLHAea_add(slha, "YE", 3, 3, sqrt2v*sminputs.mTau, "tau");
      
      SLHAea_add_block(slha, "YD");
      SLHAea_add(slha, "YD", 1, 1, sqrt2v*sminputs.mD, "d");
      SLHAea_add(slha, "YD", 1, 2, 0., "");
      SLHAea_add(slha, "YD", 1, 3, 0., "");
      SLHAea_add(slha, "YD", 2, 1, 0., "");
      SLHAea_add(slha, "YD", 2, 2, sqrt2v*sminputs.mS, "s");
      SLHAea_add(slha, "YD", 2, 3, 0., "");
      SLHAea_add(slha, "YD", 3, 1, 0., "");
      SLHAea_add(slha, "YD", 3, 2, 0., "");
      SLHAea_add(slha, "YD", 3, 3, sqrt2v*sminputs.mBmB, "b");
      
      // Block SMINPUTS
      SLHAea_add_block(slha, "SMINPUTS");
      SLHAea_add(slha, "SMINPUTS", 1, sminputs.alphainv, "# alpha_em^-1(MZ)^MSbar");
      SLHAea_add(slha, "SMINPUTS", 2, sminputs.GF, "# G_mu [GeV^-2]");
      SLHAea_add(slha, "SMINPUTS", 3, sminputs.alphaS, "# alpha_s(MZ)^MSbar");
      SLHAea_add(slha, "SMINPUTS", 4, sminputs.mZ, "# m_Z(pole)");
      SLHAea_add(slha, "SMINPUTS", 5, sminputs.mBmB, "# m_b(m_b), MSbar");
      SLHAea_add(slha, "SMINPUTS", 6, sminputs.mT, "# m_t(pole)");
      SLHAea_add(slha, "SMINPUTS", 7, sminputs.mTau, "# m_tau(pole)");
      SLHAea_add(slha, "SMINPUTS", 8, sminputs.mNu3, "# m_nu_3");
      SLHAea_add(slha, "SMINPUTS", 11, sminputs.mE, "# m_e(pole)");
      SLHAea_add(slha, "SMINPUTS", 12, sminputs.mNu1, "# m_nu_1");
      SLHAea_add(slha, "SMINPUTS", 13, sminputs.mMu, "# m_muon(pole)");
      SLHAea_add(slha, "SMINPUTS", 14, sminputs.mNu2, "# m_nu_2");
      SLHAea_add(slha, "SMINPUTS", 21, sminputs.mD, "# m_d(2 GeV), MSbar");
      SLHAea_add(slha, "SMINPUTS", 22, sminputs.mU, "# m_u(2 GeV), MSbar");
      SLHAea_add(slha, "SMINPUTS", 23, sminputs.mS, "# m_s(2 GeV), MSbar");
      SLHAea_add(slha, "SMINPUTS", 24, sminputs.mCmC, "# m_c(m_c), MSbar");
      
      // And the W for good measure
      SLHAea_add(slha, "MASS", 24, sminputs.mW);
      
      // Retrieve any mass cuts
      static const Spectrum::mc_info mass_cut = myPipe::runOptions->getValueOrDef<Spectrum::mc_info>(Spectrum::mc_info(), "mass_cut");
      static const Spectrum::mr_info mass_ratio_cut = myPipe::runOptions->getValueOrDef<Spectrum::mr_info>(Spectrum::mr_info(), "mass_ratio_cut");
      
      // Construct the Spectrum object from the SLHAea inputs
      result = spectrum_from_SLHAea<Gambit::Models::VLQSimpleSpec, SLHAstruct>(slha,slha,mass_cut,mass_ratio_cut);
    }
    
    
    // Declaration: print spectrum out
    void fill_map_from_VLQ_spectrum(std::map<std::string,double>&, const Spectrum&);
    
    void get_VLQ_spectrum_as_map(std::map<std::string,double>& specmap)
    {
      namespace myPipe = Pipes::get_VLQ_spectrum_as_map;
      const Spectrum& spec(*myPipe::Dep::VLQ_spectrum);
      fill_map_from_VLQ_spectrum(specmap, spec);
    }
    
    void fill_map_from_VLQ_spectrum(std::map<std::string, double>& specmap, const Spectrum& spec)
    {
      /// Use SpectrumContents routines to automate
      static const SpectrumContents::VLQ contents;
      static const std::vector<SpectrumParameter> required_parameters = contents.all_parameters();
      
      for(std::vector<SpectrumParameter>::const_iterator it = required_parameters.begin(); it != required_parameters.end(); ++it)
      {
        const Par::Tags        tag   = it->tag();
        const std::string      name  = it->name();
        const std::vector<int> shape = it->shape();
        
        // Scalar case
        if(shape.size()==1 and shape[0]==1)
        {
          std::ostringstream label;
          label << name <<" "<< Par::toString.at(tag);
          specmap[label.str()] = spec.get_HE().get(tag,name);
        }
        // Vector case
        else if(shape.size()==1 and shape[0]>1)
        {
          for(int i = 1; i<=shape[0]; ++i)
          {
            std::ostringstream label;
            label << name <<"_"<<i<<" "<< Par::toString.at(tag);
            specmap[label.str()] = spec.get_HE().get(tag,name,i);
          }
        }
        // Matrix case
        else if(shape.size()==2)
        {
          for(int i = 1; i<=shape[0]; ++i)
          {
            for(int j = 1; j<=shape[0]; ++j)
            {
              std::ostringstream label;
              label << name <<"_("<<i<<","<<j<<") "<<Par::toString.at(tag);
              specmap[label.str()] = spec.get_HE().get(tag,name,i,j);
            }
          }
        }
        // Deal with all other cases
        else
        {
          // ERROR
          std::ostringstream errmsg;
          errmsg << "Invalid parameter received while converting VLQ_spectrum to map of strings!";
          errmsg << "Problematic parameter was: "<< tag <<", " << name << ", shape="<< shape;
          utils_error().forced_throw(LOCAL_INFO,errmsg.str());
        }
      }
    }
    
  }
  
}
