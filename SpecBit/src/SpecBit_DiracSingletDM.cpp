//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Functions of module SpecBit
///
///  SpecBit module functions related to the
///  DiracSingletDM model
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ankit Beniwal
///          (ankit.beniwal@adelaide.edu.au)
///  \date 2016 Oct, Nov
///  \date 2017 Jun, Sep
///  \date 2018 Feb
///
///  \author Sanjay Bloor
///          (sanjay.bloor12@imperial.ac.uk)
///  \date 2018 Aug
///
///  *********************************************

#include <string>
#include <sstream>

#include "gambit/Elements/gambit_module_headers.hpp"

#include "gambit/Elements/spectrum.hpp"
#include "gambit/Utils/stream_overloads.hpp"
#include "gambit/Utils/util_macros.hpp"

#include "gambit/SpecBit/SpecBit_rollcall.hpp"
#include "gambit/SpecBit/SpecBit_helpers.hpp"
#include "gambit/SpecBit/QedQcdWrapper.hpp"
#include "gambit/Models/SimpleSpectra/SMHiggsSimpleSpec.hpp"
#include "gambit/Models/SimpleSpectra/DiracSingletDM_Z2SimpleSpec.hpp"

// Switch for debug mode
//#define SPECBIT_DEBUG

namespace Gambit
{

  namespace SpecBit
  {
    using namespace LogTags;

    /// Get a (simple) Spectrum object wrapper for the DiracSingletDM_Z2 model
    void get_DiracSingletDM_Z2_spectrum(Spectrum& result)
    {
      namespace myPipe = Pipes::get_DiracSingletDM_Z2_spectrum;
      const SMInputs& sminputs = *myPipe::Dep::SMINPUTS;

      // Initialise an object to carry the Dirac plus Higgs sector information
      Models::DiracSingletDM_Z2Model diracmodel;

      // quantities needed to fill container spectrum, intermediate calculations
      double alpha_em = 1.0 / sminputs.alphainv;
      double C = alpha_em * pi / (sminputs.GF * pow(2,0.5));
      double sinW2 = 0.5 - pow( 0.25 - C/pow(sminputs.mZ,2) , 0.5);
      double cosW2 = 0.5 + pow( 0.25 - C/pow(sminputs.mZ,2) , 0.5);
      double e = pow( 4*pi*( alpha_em ),0.5) ;

      // Higgs sector
      double mh   = *myPipe::Param.at("mH");
      diracmodel.HiggsPoleMass   = mh;

      double vev        = 1. / sqrt(sqrt(2.)*sminputs.GF);
      diracmodel.HiggsVEV        = vev;
      // diracmodel.LambdaH   = GF*pow(mh,2)/pow(2,0.5) ;

      // DiracSingletDM_Z2 sector
      diracmodel.DiracPoleMass = *myPipe::Param.at("mF");
      diracmodel.DiracLambda   = *myPipe::Param.at("lF");
      diracmodel.DiracXi       = *myPipe::Param.at("xi");

      // Invalidate point if the EFT validity constraint is not satisfied
      // See https://arxiv.org/abs/1512.06458v4 for more details
      if (myPipe::runOptions->getValueOrDef<bool>(false,"impose_EFT_validity"))
      {
        // Different EFT validity constraints for different model parametrisations.
        if (myPipe::ModelInUse("DiracSingletDM_Z2_sps"))
        {
          // Invadlidate point if the EFT validity constraint is not satisfied,
          // for each coupling independently.
          double gs = diracmodel.DiracLambda * std::cos(diracmodel.DiracXi);
          double gp = diracmodel.DiracLambda * std::sin(diracmodel.DiracXi);

          if (myPipe::runOptions->getValueOrDef<bool>(false,"impose_EFT_validity"))
          {
            if (gs >= (4*pi)/(2*diracmodel.DiracPoleMass))
            {
              std::ostringstream msg;
              msg << "Parameter point [mF, lF_s] = [" << diracmodel.DiracPoleMass << " GeV, "
                  << gs << "/GeV] does not satisfy the EFT validity constraint.";
              invalid_point().raise(msg.str());
            }
            if (gp >= (4*pi)/(2*diracmodel.DiracPoleMass))
            {
              std::ostringstream msg;
              msg << "Parameter point [mF, lF_ps] = [" << diracmodel.DiracPoleMass << " GeV, "
                  << gp << "/GeV] does not satisfy the EFT validity constraint.";
              invalid_point().raise(msg.str());
            }
          }
        }
        else
        {
          // Parametrisation with lambda/Lambda, xi
          if (diracmodel.DiracLambda >= (4*pi)/(2*diracmodel.DiracPoleMass))
          {
            std::ostringstream msg;
            msg << "Parameter point [mF, lF] = [" << diracmodel.DiracPoleMass << " GeV, "
                << diracmodel.DiracLambda << "/GeV] does not satisfy the EFT validity constraint.";
            invalid_point().raise(msg.str());
          }
        }
      }

      // Standard model
      diracmodel.sinW2 = sinW2;

      // gauge couplings
      diracmodel.g1 = sqrt(5/3) * e / sqrt(cosW2);
      diracmodel.g2 = e / sqrt(sinW2);
      diracmodel.g3   = pow( 4*pi*( sminputs.alphaS ),0.5) ;

      // Yukawas
      double sqrt2v = pow(2.0,0.5)/vev;
      diracmodel.Yu[0] = sqrt2v * sminputs.mU;
      diracmodel.Yu[1] = sqrt2v * sminputs.mCmC;
      diracmodel.Yu[2] = sqrt2v * sminputs.mT;
      diracmodel.Ye[0] = sqrt2v * sminputs.mE;
      diracmodel.Ye[1] = sqrt2v * sminputs.mMu;
      diracmodel.Ye[2] = sqrt2v * sminputs.mTau;
      diracmodel.Yd[0] = sqrt2v * sminputs.mD;
      diracmodel.Yd[1] = sqrt2v * sminputs.mS;
      diracmodel.Yd[2] = sqrt2v * sminputs.mBmB;

      // Create a SubSpectrum object to wrap the EW sector information
      Models::DiracSingletDM_Z2SimpleSpec diracspec(diracmodel);

      // Retrieve any mass cuts
      static const Spectrum::mc_info mass_cut = myPipe::runOptions->getValueOrDef<Spectrum::mc_info>(Spectrum::mc_info(), "mass_cut");
      static const Spectrum::mr_info mass_ratio_cut = myPipe::runOptions->getValueOrDef<Spectrum::mr_info>(Spectrum::mr_info(), "mass_ratio_cut");

      // We don't supply a LE subspectrum here; an SMSimpleSpec will therefore be automatically created from 'sminputs'
      result = Spectrum(diracspec,sminputs,&myPipe::Param,mass_cut,mass_ratio_cut);

    }

    // print spectrum out, stripped down copy from MSSM version with variable names changed
    void fill_map_from_DiracSingletDM_Z2spectrum(std::map<std::string,double>&, const Spectrum&);

    void get_DiracSingletDM_Z2_spectrum_as_map (std::map<std::string,double>& specmap)
    {
      namespace myPipe = Pipes::get_DiracSingletDM_Z2_spectrum_as_map;
      const Spectrum& diracdmspec(*myPipe::Dep::DiracSingletDM_Z2_spectrum);
      fill_map_from_DiracSingletDM_Z2spectrum(specmap, diracdmspec);
    }

    void fill_map_from_DiracSingletDM_Z2spectrum(std::map<std::string,double>& specmap, const Spectrum& diracdmspec)
    {
      /// Add everything... use spectrum contents routines to automate task
      static const SpectrumContents::DiracSingletDM_Z2 contents;
      static const std::vector<SpectrumParameter> required_parameters = contents.all_parameters();

      for(std::vector<SpectrumParameter>::const_iterator it = required_parameters.begin();
           it != required_parameters.end(); ++it)
      {
         const Par::Tags        tag   = it->tag();
         const std::string      name  = it->name();
         const std::vector<int> shape = it->shape();

         /// Verification routine should have taken care of invalid shapes etc, so won't check for that here.

         // Check scalar case
         if(shape.size()==1 and shape[0]==1)
         {
           std::ostringstream label;
           label << name <<" "<< Par::toString.at(tag);
           specmap[label.str()] = diracdmspec.get_HE().get(tag,name);
         }
         // Check vector case
         else if(shape.size()==1 and shape[0]>1)
         {
           for(int i = 1; i<=shape[0]; ++i) {
             std::ostringstream label;
             label << name <<"_"<<i<<" "<< Par::toString.at(tag);
             specmap[label.str()] = diracdmspec.get_HE().get(tag,name,i);
           }
         }
         // Check matrix case
         else if(shape.size()==2)
         {
           for(int i = 1; i<=shape[0]; ++i) {
             for(int j = 1; j<=shape[0]; ++j) {
               std::ostringstream label;
               label << name <<"_("<<i<<","<<j<<") "<<Par::toString.at(tag);
               specmap[label.str()] = diracdmspec.get_HE().get(tag,name,i,j);
             }
           }
         }
         // Deal with all other cases
         else
         {
           // ERROR
           std::ostringstream errmsg;
           errmsg << "Error, invalid parameter received while converting DiracSingletDM_Z2spectrum to map of strings! This should no be possible if the spectrum content verification routines were working correctly; they must be buggy, please report this.";
           errmsg << "Problematic parameter was: "<< tag <<", " << name << ", shape="<< shape;
           utils_error().forced_throw(LOCAL_INFO,errmsg.str());
         }
      }

    }

  } // end namespace SpecBit
} // end namespace Gambit
