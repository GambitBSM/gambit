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
#include "gambit/SpecBit/SpecBit_rollcall.hpp"
#include "gambit/SpecBit/SpecBit_helpers.hpp"
#include "gambit/SpecBit/QedQcdWrapper.hpp"
#include "gambit/Models/SimpleSpectra/DMEFTSimpleSpec.hpp"
#include "gambit/Models/SimpleSpectra/SMHiggsSimpleSpec.hpp"

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
      
      // Initialise model object 
      Models::DMEFTModel DMEFTmodel;
      
      // BSM parameters
      DMEFTmodel.DMEFT_Lambda = *myPipe::Param.at("Lambda");
      DMEFTmodel.DMEFT_C51 = *myPipe::Param.at("C51");
      DMEFTmodel.DMEFT_C52 = *myPipe::Param.at("C52");
      DMEFTmodel.DMEFT_C61 = *myPipe::Param.at("C61");
      DMEFTmodel.DMEFT_C62 = *myPipe::Param.at("C62");
      DMEFTmodel.DMEFT_C63 = *myPipe::Param.at("C63");
      DMEFTmodel.DMEFT_C64 = *myPipe::Param.at("C64");
      DMEFTmodel.DMEFT_C71 = *myPipe::Param.at("C71");
      DMEFTmodel.DMEFT_C72 = *myPipe::Param.at("C72");
      DMEFTmodel.DMEFT_C73 = *myPipe::Param.at("C73");
      DMEFTmodel.DMEFT_C74 = *myPipe::Param.at("C74");
      DMEFTmodel.DMEFT_C75 = *myPipe::Param.at("C75");
      DMEFTmodel.DMEFT_C76 = *myPipe::Param.at("C76");
      DMEFTmodel.DMEFT_C77 = *myPipe::Param.at("C77");
      DMEFTmodel.DMEFT_C78 = *myPipe::Param.at("C78");
      DMEFTmodel.DMEFT_C79 = *myPipe::Param.at("C79");
      DMEFTmodel.DMEFT_C710 = *myPipe::Param.at("C710");
      // Pole mass inputs (mh is a nuiisance parameter?)
      DMEFTmodel.DMEFT_chi_Pole_Mass = *myPipe::Param.at("mchi");
      DMEFTmodel.DMEFT_h0_1_Pole_Mass = *myPipe::Param.at("mH");
      // running top mass input, must be standard model msbar mt(mt)
      DMEFTmodel.mtrun = *myPipe::Param.at("mtrunIN");
      // Invalidate point if the EFT is violated for DM annihilation i.e. 2*m_DM > Lambda
      // Default: true
      if (myPipe::runOptions->getValueOrDef<bool>(true,"impose_EFT_validity"))
      {
        if (DMEFTmodel.DMEFT_Lambda < (2*DMEFTmodel.DMEFT_chi_Pole_Mass))
        {
          std::ostringstream msg;
          msg << "Parameter point [mchi, Lambda] = [" << DMEFTmodel.DMEFT_chi_Pole_Mass << " GeV, "
              << DMEFTmodel.DMEFT_Lambda << " GeV] does not satisfy the EFT.";
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
      
      // Gauge couplings
      DMEFTmodel.vev = vev;
      DMEFTmodel.g1 = e / sqrt(sinW2);
      DMEFTmodel.g2 = e / sqrt(cosW2);
      DMEFTmodel.g3 = pow( 4*pi*( sminputs.alphaS ),0.5);
      
      // Yukawas
      double sqrt2v = pow(2.0,0.5)/vev;
      DMEFTmodel.Yu[0][0] = sqrt2v * sminputs.mU;
      DMEFTmodel.Yu[1][1] = sqrt2v * sminputs.mCmC;
      // top quark is treated at one-loop with different running and pole mass
      DMEFTmodel.Yu[2][2] = sqrt2v * DMEFTmodel.mtrun;
      DMEFTmodel.Ye[0][0] = sqrt2v * sminputs.mE;
      DMEFTmodel.Ye[1][1] = sqrt2v * sminputs.mMu;
      DMEFTmodel.Ye[2][2] = sqrt2v * sminputs.mTau;
      DMEFTmodel.Yd[0][0] = sqrt2v * sminputs.mD;
      DMEFTmodel.Yd[1][1] = sqrt2v * sminputs.mS;
      DMEFTmodel.Yd[2][2] = sqrt2v * sminputs.mBmB;

      // Create a SubSpectrum object wrapper
      Models::DMEFTSimpleSpec spec(DMEFTmodel);
      
      // Retrieve any mass cuts
      static const Spectrum::mc_info mass_cut = myPipe::runOptions->getValueOrDef<Spectrum::mc_info>(Spectrum::mc_info(), "mass_cut");
      static const Spectrum::mr_info mass_ratio_cut = myPipe::runOptions->getValueOrDef<Spectrum::mr_info>(Spectrum::mr_info(), "mass_ratio_cut");

      // We have decided to calculate mT pole from the input running mt
      // using only one-loop QCD corrections
      // See footnote 9 https://link.springer.com/article/10.1007/JHEP11(2019)150

      // Approximate alpha_S(mtop) as alpha_S(mZ) because even a
      // one-loop correction here will lead to O(alpha_S^2) correction on mT
      // Via correspondence with the authors we checked this
      // approximation matches what is done in
      // https://link.springer.com/article/10.1007/JHEP11(2019)150
      // which we also validated numerically
      
      const double alpha_S_mtop = sminputs.alphaS;
      // Now extract pole mass from running mass
      const double mtop_MSBAR_mtop = DMEFTmodel.mtrun; // must be SM MSbar mt(mt)
      const double mtop_pole = mtop_MSBAR_mtop * (1. + 4. / 3.
						  * alpha_S_mtop / M_PI);

      // Make a local sminputs so we can change pole mT to the one we calculated
      SMInputs localsminputs = sminputs;
      localsminputs.mT = mtop_pole;
      // We don't supply a LE subspectrum here; an SMSimpleSpec will therefore be automatically created from 'localsminputs'
      result = Spectrum(spec,localsminputs,&myPipe::Param,mass_cut,mass_ratio_cut);

    }

    // Declaration: print spectrum out
    void fill_map_from_DMEFT_spectrum(std::map<std::string,double>&, const Spectrum&);
    
    void get_DMEFT_spectrum_as_map(std::map<std::string,double>& specmap)
    {
      namespace myPipe = Pipes::get_DMEFT_spectrum_as_map;
      const Spectrum& spec(*myPipe::Dep::DMEFT_spectrum);
      fill_map_from_DMEFT_spectrum(specmap, spec);
    }
    
    void fill_map_from_DMEFT_spectrum(std::map<std::string, double>& specmap, const Spectrum& spec)
    {
      /// Use SpectrumContents routines to automate
      static const SpectrumContents::DMEFT contents;
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
          errmsg << "Invalid parameter received while converting DMEFT_spectrum to map of strings!";
          errmsg << "Problematic parameter was: "<< tag <<", " << name << ", shape="<< shape;
          utils_error().forced_throw(LOCAL_INFO,errmsg.str());
        }

        // Include the pole mass of the top (which is a derived parameter and not in SpectrumContents::DMEFT)
        std::ostringstream label;
        label << "t" <<" "<< Par::toString.at(Par::Pole_Mass);
        specmap[label.str()] = spec.get(Par::Pole_Mass,"t");
      }
    }
    
  }
  
}
