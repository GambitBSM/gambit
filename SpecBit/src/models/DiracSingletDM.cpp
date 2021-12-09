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
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2019 Nov
///
///  *********************************************

#include <string>
#include <sstream>

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/Elements/spectrum.hpp"

#include "gambit/SpecBit/SpecBit_rollcall.hpp"
#include "gambit/SpecBit/SpecBit_helpers.hpp"
#include "gambit/SpecBit/RegisteredSpectra.hpp"

#include "gambit/Models/partmap.hpp"

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

      // Initialise an SLHAea object to carry the Dirac plus Higgs sector information
      SLHAea::Coll slha;
      SLHAea_add_block(slha, "MASS");
      SLHAea_add_block(slha, "VEVS");
      SLHAea_add_block(slha, "COUPLINGS");
      SLHAea_add_block(slha, "SINTHETAW");
      SLHAea_add_block(slha, "GAUGE");
      SLHAea_add_block(slha, "YD");
      SLHAea_add_block(slha, "YU");
      SLHAea_add_block(slha, "YE");

      // quantities needed to fill container spectrum, intermediate calculations
      double alpha_em = 1.0 / sminputs.alphainv;
      double C = alpha_em * pi / (sminputs.GF * pow(2,0.5));
      double sinW2 = 0.5 - pow( 0.25 - C/pow(sminputs.mZ,2) , 0.5);
      double cosW2 = 0.5 + pow( 0.25 - C/pow(sminputs.mZ,2) , 0.5);
      double e = pow( 4*pi*( alpha_em ),0.5) ;

      // Higgs sector
      double mh   = *myPipe::Param.at("mH");
      std::pair<int,int> pdg = Models::ParticleDB().pdg_pair("h0_1");
      slha["MASS"][""] << pdg.first << mh << "# mH";

      double vev        = 1. / sqrt(sqrt(2.)*sminputs.GF);
      slha["VEVS"][""] << 1 << vev << " # vev";
      // slha["COUPLINGS"][""] << 2 << GF*pow(mh,2)/pow(2,0.5) << " # lambda_h";

      // DiracSingletDM_Z2 sector
      pdg = Models::ParticleDB().pdg_pair("F");
      double mF = *myPipe::Param.at("mF");
      slha["MASS"][""] << pdg.first << mF << "# mF";
      double lF = *myPipe::Param.at("lF");
      slha["COUPLINGS"][""] << 1 << lF << "# lF";
      double xi = *myPipe::Param.at("xi");
      slha["COUPLINGS"][""] << 3 << xi << "# xi";

      // Invalidate point if the EFT validity constraint is not satisfied
      // See https://arxiv.org/abs/1512.06458v4 for more details
      if (myPipe::runOptions->getValueOrDef<bool>(false,"impose_EFT_validity"))
      {
        // Different EFT validity constraints for different model parametrisations.
        if (myPipe::ModelInUse("DiracSingletDM_Z2_sps"))
        {
          // Invadlidate point if the EFT validity constraint is not satisfied,
          // for each coupling independently.
          double gs = lF * std::cos(xi);
          double gp = lF * std::sin(xi);

          if (myPipe::runOptions->getValueOrDef<bool>(false,"impose_EFT_validity"))
          {
            if (gs >= (4*pi)/(2*mF))
            {
              std::ostringstream msg;
              msg << "Parameter point [mF, lF_s] = [" << mF << " GeV, "
                  << gs << "/GeV] does not satisfy the EFT validity constraint.";
              invalid_point().raise(msg.str());
            }
            if (gp >= (4*pi)/(2*mF))
            {
              std::ostringstream msg;
              msg << "Parameter point [mF, lF_ps] = [" << mF << " GeV, "
                  << gp << "/GeV] does not satisfy the EFT validity constraint.";
              invalid_point().raise(msg.str());
            }
          }
        }
        else
        {
          // Parametrisation with lambda/Lambda, xi
          if (lF >= (4*pi)/(2*mF))
          {
            std::ostringstream msg;
            msg << "Parameter point [mF, lF] = [" << mF << " GeV, "
                << lF << "/GeV] does not satisfy the EFT validity constraint.";
            invalid_point().raise(msg.str());
          }
        }
      }

      // Standard model
      slha["SINTHETAW"][""] << 1 << sinW2 << "# sinW2";

      // gauge couplings
      slha["GAUGE"][""] << 1 << sqrt(5/3) * e / sqrt(cosW2) << "# g1";
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
      SpectrumContents::DiracSingletDM_Z2 dirac;

      // Create spectrum object
      // Take mZ as the spectrum scale
      result = Spectrum(slha, dirac, sminputs.mZ, false);

      // Retrieve any mass cuts
      result.check_mass_cuts(*myPipe::runOptions);

    }

    // Convert a DiracSingletDM_Z2 spectrum into a standard map so that it can be printed
    void get_DiracSingletDM_Z2_spectrum_as_map (std::map<std::string,double>& specmap)
    {
      namespace myPipe = Pipes::get_DiracSingletDM_Z2_spectrum_as_map;
      const Spectrum& diracdmspec(*myPipe::Dep::DiracSingletDM_Z2_spectrum);
      fill_map_from_spectrum<SpectrumContents::DiracSingletDM_Z2>(specmap, diracdmspec);
    }

  } // end namespace SpecBit
} // end namespace Gambit
