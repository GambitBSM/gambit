//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Functions of module SpecBit
///
///  SpecBit module functions related to the
///  scalar singlet DM model.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ben Farmer
///          (benjamin.farmer@fysik.su.se)
///    \date 2015 May
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

//#include "gambit/Utils/stream_overloads.hpp"
//#include "gambit/Utils/util_macros.hpp"

#include "gambit/SpecBit/SpecBit_rollcall.hpp"
#include "gambit/SpecBit/SpecBit_helpers.hpp"
#include "gambit/SpecBit/RegisteredSpectra.hpp"

// Switch for debug mode
//#define SPECBIT_DEBUG

namespace Gambit
{

  namespace SpecBit
  {
    /// @{
    /// ScalarSingletDM_Z2
 
    /// Get a Spectrum object for the ScalarSingletDM_Z2 model
    void get_ScalarSingletDM_Z2_spectrum(Spectrum& result)
    {
      namespace myPipe = Pipes::get_ScalarSingletDM_Z2_spectrum;
      const SMInputs& sminputs = *myPipe::Dep::SMINPUTS;

      // Initialise an SLHAea object to carry the Singlet plus Higgs sector information
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
      double mh = *myPipe::Param.at("mH");
      std::pair<int,int> pdg = Models::ParticleDB().pdg_pair("h0_1");
      slha["MASS"][""] << pdg.first << mh << "# mH";

      double vev = 1. / sqrt(sqrt(2.)*sminputs.GF);
      slha["VEVS"][""] << 1 << vev << " # vev";

      // Scalar singlet sector
      pdg = Models::ParticleDB().pdg_pair("S");
      double mS = *myPipe::Param.at("mS");
      slha["MASS"][""] << pdg.first << mS << "# mS";
      double lambda_hS = *myPipe::Param.at("lambda_hS");
      slha["COUPLINGS"][""] << 1 << lambda_hS << "# lambda_hS";
      double lambda_S = 0;
      slha["COUPLINGS"][""] << 2 << lambda_S << "# lambda_S";

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
      SpectrumContents::ScalarSingletDM_Z2 scalar;

      // Create spectrum object
      // Take mZ as the spectrum scale
      result = Spectrum(slha, scalar, sminputs.mZ, false);

      // Retrieve any mass cuts
      result.check_mass_cuts(*myPipe::runOptions);
    }

    /// Get the spectrum from FlexibleSUSY for the ScalarSingletDM_Z2 model
    void get_ScalarSingletDM_Z2_spectrum_pole(Spectrum& result)
    {
      namespace myPipe = Pipes::get_ScalarSingletDM_Z2_spectrum_pole;
      const SMInputs& sminputs = *myPipe::Dep::SMINPUTS;
      const Options& runOptions=*myPipe::runOptions;

      // Set up the input structure
      SpectrumInputs inputs(sminputs, SpectrumContents::ScalarSingletDM_Z2(), myPipe::Param, myPipe::runOptions);

      // TODO: This is handled by the backend
      //fill_ScalarSingletDM_input(input,myPipe::Param,sminputs);

      // Get the spectrum from the Backend
      myPipe::BEreq::FS_ScalarSingletDM_Z2_Spectrum(result, inputs);

      // Retrieve any mass cuts
      result.check_mass_cuts(*myPipe::runOptions);

      int check_perturb_pts = runOptions.getValueOrDef<double>(10,"check_perturb_pts");
      double do_check_perturb = runOptions.getValueOrDef<bool>(false,"check_perturb");
      double check_perturb_scale = runOptions.getValueOrDef<double>(1.22e19,"check_high_scale");
      double input_scale_tolerance = runOptions.getValueOrDef<double>(1e-3,"input_scale_tolerance");

      // Check that the Higgs MSbar parameter has been provided at the scale of the singlet MSbar mass
      double Qin = *myPipe::Param.at("Qin");
      if (abs((Qin - *myPipe::Param.at("mS"))/Qin) > input_scale_tolerance) SpecBit_error().raise(LOCAL_INFO, "SM_Higgs_running::Qin must equal ScalarSingletDM_Z2_running::mS");

      if (do_check_perturb)
      {
        static const SpectrumContents::ScalarSingletDM_Z2 contents;
        static const std::vector<SpectrumContents::Parameter> required_parameters = contents.all_parameters_with_tag(Par::dimensionless);
        /* TODO: Not yet ready
        if (!check_perturb(result,required_parameters,check_perturb_scale,check_perturb_pts))
        {
          // invalidate point as spectrum not perturbative up to scale
          std::ostringstream msg;
          msg << "Spectrum not perturbative up to scale = " << check_perturb_scale <<  std::endl;
          #ifdef SPECBIT_DEBUG
            cout << "Spectrum not perturbative up to scale = " << check_perturb_scale <<  endl;
          #endif
          invalid_point().raise(msg.str());
        }*/
      }

    }

    /// @}

    /// @{
    /// ScalarSingletDM_Z3

    /// Get a Spectrum object for the ScalarSingletDM_Z3 model
    void get_ScalarSingletDM_Z3_spectrum(Spectrum& result)
    {
      namespace myPipe = Pipes::get_ScalarSingletDM_Z3_spectrum;
      const SMInputs& sminputs = *myPipe::Dep::SMINPUTS;

      // Initialise an SLHAea object to carry the Singlet plus Higgs sector information
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
      double mh = *myPipe::Param.at("mH");
      std::pair<int,int> pdg = Models::ParticleDB().pdg_pair("h0_1");
      slha["MASS"][""] << pdg.first << mh << "# mH";

      double vev = 1. / sqrt(sqrt(2.)*sminputs.GF);
      slha["VEVS"][""] << 1 << vev << " # vev";

      // Scalar singlet sector
      pdg = Models::ParticleDB().pdg_pair("S");
      double mS = *myPipe::Param.at("mS");
      slha["MASS"][""] << pdg.first << mS << "# mS";
      double lambda_hS = *myPipe::Param.at("lambda_hS");
      slha["COUPLINGS"][""] << 1 << lambda_hS << "# lambda_hS";
      double lambda_S = *myPipe::Param.at("lambda_S");
      slha["COUPLINGS"][""] << 2 << lambda_S << "# lambda_S";
      double mu3 = *myPipe::Param.at("mu3");
      slha["COUPLINGS"][""] << 4 << mu3 << "# mu3";

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
      SpectrumContents::ScalarSingletDM_Z2 scalar;

      // Create spectrum object
      // Take mZ as the spectrum scale
      result = Spectrum(slha, scalar, sminputs.mZ, false);

      // Retrieve any mass cuts
      result.check_mass_cuts(*myPipe::runOptions);
    }

    /// Get the spectrum from FlexibleSUSY for the ScalarSingletDM_Z3 model
    void get_ScalarSingletDM_Z3_spectrum_pole(Spectrum& result)
    {
      namespace myPipe = Pipes::get_ScalarSingletDM_Z3_spectrum_pole;
      const SMInputs& sminputs = *myPipe::Dep::SMINPUTS;
      const Options& runOptions=*myPipe::runOptions;

      // Set up the input structure
      SpectrumInputs inputs(sminputs, SpectrumContents::ScalarSingletDM_Z3(), myPipe::Param, myPipe::runOptions);

      // TODO: This is handled by the backend
      //fill_ScalarSingletDM_input(input,myPipe::Param,sminputs);
      //fill_extra_input(input,myPipe::Param);

      // Get the spectrum from the Backend
      myPipe::BEreq::FS_ScalarSingletDM_Z3_Spectrum(result, inputs);

      // Retrieve any mass cuts
      result.check_mass_cuts(*myPipe::runOptions);

      int check_perturb_pts = runOptions.getValueOrDef<double>(10,"check_perturb_pts");
      double do_check_perturb = runOptions.getValueOrDef<bool>(false,"check_perturb");
      double check_perturb_scale = runOptions.getValueOrDef<double>(1.22e19,"check_high_scale");
      double input_scale_tolerance = runOptions.getValueOrDef<double>(1e-3,"input_scale_tolerance");

      // Check that the Higgs MSbar parameter has been provided at the scale of the singlet MSbar mass
      double Qin = *myPipe::Param.at("Qin");
      if (abs((Qin - *myPipe::Param.at("mS"))/Qin) > input_scale_tolerance) SpecBit_error().raise(LOCAL_INFO, "SM_Higgs_running::Qin must equal ScalarSingletDM_Z3_running::mS");

      if (do_check_perturb)
      {
        static const SpectrumContents::ScalarSingletDM_Z3 contents;
        static const std::vector<SpectrumContents::Parameter> required_parameters = contents.all_parameters_with_tag(Par::dimensionless);
        /* TODO: Not yet ready
        if (!check_perturb(result,required_parameters,check_perturb_scale,check_perturb_pts))
        {
          // invalidate point as spectrum not perturbative up to scale
          std::ostringstream msg;

          msg << "Spectrum not perturbative up to scale = " << check_perturb_scale <<  std::endl;
          #ifdef SPECBIT_DEBUG
            cout << "Spectrum not perturbative up to scale = " << check_perturb_scale <<  endl;
          #endif
          invalid_point().raise(msg.str());
        }*/
      }

    }

    /// @}

/* TODO: Not yet ready
    bool check_perturb(const Spectrum& spec, const std::vector<SpectrumContents::Parameter>& required_parameters, double scale, int pts)
    {
      std::unique_ptr<Spectrum> ScalarSingletDM = spec.clone_HE();
      double step = log10(scale) / pts;
      double runto;
      double ul = 4.0 * pi;

      for (int i=0;i<pts;i++)
      {
        runto = pow(10,step*float(i+1.0)); // scale to run spectrum to
        if (runto<100){runto=100.0;}// avoid running to low scales

        ScalarSingletDM -> RunToScale(runto);

        for(std::vector<SpectrumParameter>::const_iterator it = required_parameters.begin();
              it != required_parameters.end(); ++it)
        {
          const Par::Tags        tag   = it->tag();
          const std::string      name  = it->name();
          const std::vector<int> shape = it->shape();
          std::ostringstream label;
          label << name <<" "<< Par::toString.at(tag);

          if (name == "lambda_S"){ul =  pi;}
          else if (name == "lambda_h"){ul =  2*pi;}
          else if (name == "lambda_hS"){ul =  4*pi;}
          else {ul = 100;}

          if(shape.size()==1 and shape[0]==1)
          {
            if (abs(ScalarSingletDM->get(tag,name))>ul)
            {
							return false;
						}
          }
          else if(shape.size()==1 and shape[0]>1)
          {
            for(int k = 1; k<=shape[0]; ++k)
            {
              if (abs(ScalarSingletDM->get(tag,name,k))>ul) return false;
            }
          }
          else if(shape.size()==2)
          {
            for(int k = 1; k<=shape[0]; ++k)
            {
              for(int j = 1; j<=shape[0]; ++j)
              {
                if (abs(ScalarSingletDM->get(tag,name,k,j))>ul) return false;
              }
            }
          }

          // check stability condition

          double lamhs = ScalarSingletDM->get(Par::dimensionless,"lambda_hS");
          double lams = ScalarSingletDM->get(Par::dimensionless,"lambda_S");
          double lamh = ScalarSingletDM->get(Par::dimensionless,"lambda_h");

          double stability_condition = 2.0 * pow(0.5* 0.25 *  lamh*lams,0.5) + 0.5*lamhs;

          if (!(stability_condition > 0) && (lams>0) && (lamh>0))
					{
						//cout << "EW stability condition violated at Q = " << scale <<" , lambda_hs = "<< lamhs << "lamh = " << lamh << " lams = " << lams << endl;
						return false;
					}

        }
      }

      return true;

    }
*/

    void find_non_perturb_scale_ScalarSingletDM_Z2(double &result)
    {
      namespace myPipe = Pipes::find_non_perturb_scale_ScalarSingletDM_Z2;

      const Spectrum& fullspectrum = *myPipe::Dep::ScalarSingletDM_Z2_spectrum;

      // bound x by (a,b)
      double ms = *myPipe::Param.at("mS");

      double a = log10(ms);

      if (a > 20.0)
      {
        std::ostringstream msg;
        msg << "Scalar mass larger than 10^20 GeV " << std::endl;
        invalid_point().raise(msg.str());
      }

      double b = 20.0;
      double x = 0.5 * ( b + ms );

      while (abs(a-b)>1e-10)
      {
        x=0.5*(b-a)+a;
        static const SpectrumContents::ScalarSingletDM_Z2 contents;
        static const std::vector<SpectrumContents::Parameter> required_parameters = contents.all_parameters_with_tag(Par::dimensionless);
        /* TODO: Not ready yet
        if (!check_perturb(fullspectrum,required_parameters,pow(10,x),3))
        {
          b=x;
        }
        else
        {
          a=x;
        }*/
      }
      result = pow(10,0.5*(a+b));
    }

    void find_non_perturb_scale_ScalarSingletDM_Z3(double &result)
    {
      namespace myPipe = Pipes::find_non_perturb_scale_ScalarSingletDM_Z3;

      const Spectrum& fullspectrum = *myPipe::Dep::ScalarSingletDM_Z3_spectrum;

      // bound x by (a,b)

      double ms = *myPipe::Param.at("mS");

      double a = log10(ms);

      if (a > 20.0)
      {
        std::ostringstream msg;
        msg << "Scalar mass larger than 10^20 GeV " << std::endl;
        invalid_point().raise(msg.str());
      }

      double b = 20.0;
      double x = 0.5 * ( b + ms );

      while (abs(a-b)>1e-10)
      {
        x=0.5*(b-a)+a;
        static const SpectrumContents::ScalarSingletDM_Z3 contents;
        static const std::vector<SpectrumContents::Parameter> required_parameters = contents.all_parameters_with_tag(Par::dimensionless);
        /* TODO: Not ready yet
        if (!check_perturb(fullspectrum,required_parameters,pow(10,x),3))
        {
          b=x;
        }
        else
        {
          a=x;
        }*/
      }
      result = pow(10,0.5*(a+b));
    }

    /// Put together the Higgs couplings for the ScalarSingletDM models, from partial widths only
    void ScalarSingletDM_higgs_couplings_pwid(HiggsCouplingsTable &result)
    {
      using namespace Pipes::ScalarSingletDM_higgs_couplings_pwid;
      dep_bucket<Spectrum>* spectrum_dependency = nullptr;
      if (ModelInUse("ScalarSingletDM_Z2") or ModelInUse("ScalarSingletDM_Z2_running"))
      {
        spectrum_dependency = &Dep::ScalarSingletDM_Z2_spectrum;
      }
      else if (ModelInUse("ScalarSingletDM_Z3") or ModelInUse("ScalarSingletDM_Z3_running"))
      {
        spectrum_dependency = &Dep::ScalarSingletDM_Z3_spectrum;
      }
      else SpecBit_error().raise(LOCAL_INFO, "No valid model for ScalarSingletDM_higgs_couplings_pwid.");
      const Spectrum& spec = **spectrum_dependency;

      // Set the number of Higgses
      result.set_n_neutral_higgs(1);
      result.set_n_charged_higgs(0);
      // Set the CP of the Higgs.
      result.CP[0] = 1;
      // Set the decays
      result.set_neutral_decays_SM(0, "h0_1", *Dep::Reference_SM_Higgs_decay_rates);
      result.set_neutral_decays(0, "h0_1", *Dep::Higgs_decay_rates);

      // Identify the singlet as the only possible invisible particle
      if (spec.get(Par::Pole_Mass, "S") * 2.0 < spec.get(Par::Pole_Mass, "h0_1"))
        result.invisibles = initVector<std::pair<str,str>>(std::make_pair("S","S"));
      else
        result.invisibles.clear();
      // Leave all the effective couplings for all neutral higgses set to unity (done at construction).
    }


    // Convert ScalarSingletDM_Z2 spectrum into a standard map so that it can be printed
    void get_ScalarSingletDM_Z2_spectrum_as_map (std::map<std::string,double>& specmap)
    {
      namespace myPipe = Pipes::get_ScalarSingletDM_Z2_spectrum_as_map;
      static const Spectrum& spec = *myPipe::Dep::ScalarSingletDM_Z2_spectrum;
      fill_map_from_spectrum<SpectrumContents::ScalarSingletDM_Z2>(specmap, spec);
    }

    // Convert ScalarSingletDM_Z3 spectrum into a standard map so that it can be printed
    void get_ScalarSingletDM_Z3_spectrum_as_map (std::map<std::string,double>& specmap)
    {
      namespace myPipe = Pipes::get_ScalarSingletDM_Z3_spectrum_as_map;
      static const Spectrum& spec = *myPipe::Dep::ScalarSingletDM_Z3_spectrum;
      fill_map_from_spectrum<SpectrumContents::ScalarSingletDM_Z3>(specmap, spec);
    }

  } // end namespace SpecBit
} // end namespace Gambit

