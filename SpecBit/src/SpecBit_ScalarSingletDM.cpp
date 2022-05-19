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
#include "gambit/Models/SimpleSpectra/ScalarSingletDMSimpleSpec.hpp"
#include "gambit/SpecBit/model_files_and_boxes.hpp"

#include "gambit/SpecBit/ScalarSingletDM_Z2Spec.hpp"
#include "gambit/SpecBit/ScalarSingletDM_Z3Spec.hpp"

// Flexible SUSY stuff (should not be needed by the rest of gambit)
#include "flexiblesusy/src/ew_input.hpp"
#include "flexiblesusy/src/lowe.h"
#include "flexiblesusy/src/numerics2.hpp"
#include "flexiblesusy/src/spectrum_generator_settings.hpp"
// Switch for debug mode
//#define SPECBIT_DEBUG

namespace Gambit
{

  namespace SpecBit
  {
    using namespace LogTags;
    using namespace flexiblesusy;

    /// Get a (simple) Spectrum object wrapper for the ScalarSingletDM_Z2 model
    void get_ScalarSingletDM_Z2_spectrum(Spectrum& result)
    {
      namespace myPipe = Pipes::get_ScalarSingletDM_Z2_spectrum;
      const SMInputs& sminputs = *myPipe::Dep::SMINPUTS;

      // Initialise an object to carry the Singlet plus Higgs sector information
      Models::ScalarSingletDM_Z2Model singletmodel;

      // quantities needed to fill container spectrum, intermediate calculations
      double alpha_em = 1.0 / sminputs.alphainv;
      double C = alpha_em * pi / (sminputs.GF * pow(2,0.5));
      double sinW2 = 0.5 - pow( 0.25 - C/pow(sminputs.mZ,2) , 0.5);
      double cosW2 = 0.5 + pow( 0.25 - C/pow(sminputs.mZ,2) , 0.5);
      double e = pow( 4*pi*( alpha_em ),0.5) ;

      // Higgs sector
      double mh = *myPipe::Param.at("mH");
      singletmodel.HiggsPoleMass = mh;

      double vev = 1. / sqrt(sqrt(2.)*sminputs.GF);
      singletmodel.HiggsVEV = vev;

      // Scalar singlet sector
      singletmodel.SingletPoleMass = *myPipe::Param.at("mS");
      singletmodel.SingletLambda = *myPipe::Param.at("lambda_hS");
      singletmodel.SingletLambdaS = 0;

      // Standard model
      singletmodel.sinW2 = sinW2;

      // gauge couplings
      singletmodel.g1 = sqrt(5/3) * e / sqrt(cosW2);
      singletmodel.g2 = e / sqrt(sinW2);
      singletmodel.g3   = pow( 4*pi*( sminputs.alphaS ),0.5) ;

      // Yukawas
      double sqrt2v = pow(2.0,0.5)/vev;
      singletmodel.Yu[0] = sqrt2v * sminputs.mU;
      singletmodel.Yu[1] = sqrt2v * sminputs.mCmC;
      singletmodel.Yu[2] = sqrt2v * sminputs.mT;
      singletmodel.Ye[0] = sqrt2v * sminputs.mE;
      singletmodel.Ye[1] = sqrt2v * sminputs.mMu;
      singletmodel.Ye[2] = sqrt2v * sminputs.mTau;
      singletmodel.Yd[0] = sqrt2v * sminputs.mD;
      singletmodel.Yd[1] = sqrt2v * sminputs.mS;
      singletmodel.Yd[2] = sqrt2v * sminputs.mBmB;

      // Create a SubSpectrum object to wrap the EW sector information
      Models::ScalarSingletDM_Z2SimpleSpec singletspec(singletmodel);

      // Retrieve any mass cuts
      static const Spectrum::mc_info mass_cut = myPipe::runOptions->getValueOrDef<Spectrum::mc_info>(Spectrum::mc_info(), "mass_cut");
      static const Spectrum::mr_info mass_ratio_cut = myPipe::runOptions->getValueOrDef<Spectrum::mr_info>(Spectrum::mr_info(), "mass_ratio_cut");

      // We don't supply a LE subspectrum here; an SMSimpleSpec will therefore be automatically created from 'sminputs'
      result = Spectrum(singletspec,sminputs,&myPipe::Param,mass_cut,mass_ratio_cut);

    }

    /// Get a (simple) Spectrum object wrapper for the ScalarSingletDM_Z3 model
    void get_ScalarSingletDM_Z3_spectrum(Spectrum& result)
    {
      namespace myPipe = Pipes::get_ScalarSingletDM_Z3_spectrum;
      const SMInputs& sminputs = *myPipe::Dep::SMINPUTS;

      // Initialise an object to carry the Singlet plus Higgs sector information
      Models::ScalarSingletDM_Z3Model singletmodel;

      // quantities needed to fill container spectrum, intermediate calculations
      double alpha_em = 1.0 / sminputs.alphainv;
      double C = alpha_em * pi / (sminputs.GF * pow(2,0.5));
      double sinW2 = 0.5 - pow( 0.25 - C/pow(sminputs.mZ,2) , 0.5);
      double cosW2 = 0.5 + pow( 0.25 - C/pow(sminputs.mZ,2) , 0.5);
      double e = pow( 4*pi*( alpha_em ),0.5) ;

      // Higgs sector
      double mh = *myPipe::Param.at("mH");
      singletmodel.HiggsPoleMass = mh;

      double vev = 1. / sqrt(sqrt(2.)*sminputs.GF);
      singletmodel.HiggsVEV = vev;

      // Scalar singlet sector
      singletmodel.SingletPoleMass = *myPipe::Param.at("mS");
      singletmodel.SingletLambda = *myPipe::Param.at("lambda_hS");
      singletmodel.SingletLambdaS = *myPipe::Param.at("lambda_S");

      singletmodel.mu3 = *myPipe::Param.at("mu3");

      // Standard model
      singletmodel.sinW2 = sinW2;

      // gauge couplings
      singletmodel.g1 = sqrt(5/3) * e / sqrt(cosW2);
      singletmodel.g2 = e / sqrt(sinW2);
      singletmodel.g3   = pow( 4*pi*( sminputs.alphaS ),0.5) ;

      // Yukawas
      double sqrt2v = pow(2.0,0.5)/vev;
      singletmodel.Yu[0] = sqrt2v * sminputs.mU;
      singletmodel.Yu[1] = sqrt2v * sminputs.mCmC;
      singletmodel.Yu[2] = sqrt2v * sminputs.mT;
      singletmodel.Ye[0] = sqrt2v * sminputs.mE;
      singletmodel.Ye[1] = sqrt2v * sminputs.mMu;
      singletmodel.Ye[2] = sqrt2v * sminputs.mTau;
      singletmodel.Yd[0] = sqrt2v * sminputs.mD;
      singletmodel.Yd[1] = sqrt2v * sminputs.mS;
      singletmodel.Yd[2] = sqrt2v * sminputs.mBmB;

      // Create a SubSpectrum object to wrap the EW sector information
      Models::ScalarSingletDM_Z3SimpleSpec singletspec(singletmodel);

      // Retrieve any mass cuts
      static const Spectrum::mc_info mass_cut = myPipe::runOptions->getValueOrDef<Spectrum::mc_info>(Spectrum::mc_info(), "mass_cut");
      static const Spectrum::mr_info mass_ratio_cut = myPipe::runOptions->getValueOrDef<Spectrum::mr_info>(Spectrum::mr_info(), "mass_ratio_cut");

      // We don't supply a LE subspectrum here; an SMSimpleSpec will therefore be automatically created from 'sminputs'
      result = Spectrum(singletspec,sminputs,&myPipe::Param,mass_cut,mass_ratio_cut);

    }


    template<class MI,class SI>
    Spectrum run_FS_spectrum_generator
        ( const typename MI::InputParameters& input
        , const SMInputs& sminputs
        , const Options& runOptions
        , const std::map<str, safe_ptr<const double> >& input_Param
        )
    {
      // SoftSUSY object used to set quark and lepton masses and gauge
      // couplings in QEDxQCD effective theory
      // Will be initialised by default using values in lowe.h, which we will
      // override next.
      softsusy::QedQcd oneset;

      // Fill QedQcd object with SMInputs values
      setup_QedQcd(oneset,sminputs);

      // Run everything to Mz
      oneset.toMz();

      // Create spectrum generator object
      typename MI::SpectrumGenerator spectrum_generator;

      // Spectrum generator settings
      // Default options copied from flexiblesusy/src/spectrum_generator_settings.hpp
      //
      // | enum                             | possible values              | default value   |
      // |----------------------------------|------------------------------|-----------------|
      // | precision                        | any positive double          | 1.0e-4          |
      // | max_iterations                   | any positive double          | 0 (= automatic) |
      // | algorithm                        | 0 (two-scale) or 1 (lattice) | 0 (= two-scale) |
      // | calculate_sm_masses              | 0 (no) or 1 (yes)            | 0 (= no)        |
      // | pole_mass_loop_order             | 0, 1, 2                      | 2 (= 2-loop)    |
      // | ewsb_loop_order                  | 0, 1, 2                      | 2 (= 2-loop)    |
      // | beta_loop_order                  | 0, 1, 2                      | 2 (= 2-loop)    |
      // | threshold_corrections_loop_order | 0, 1                         | 1 (= 1-loop)    |
      // | higgs_2loop_correction_at_as     | 0, 1                         | 1 (= enabled)   |
      // | higgs_2loop_correction_ab_as     | 0, 1                         | 1 (= enabled)   |
      // | higgs_2loop_correction_at_at     | 0, 1                         | 1 (= enabled)   |
      // | higgs_2loop_correction_atau_atau | 0, 1                         | 1 (= enabled)   |

      Spectrum_generator_settings settings;
      settings.set(Spectrum_generator_settings::precision, runOptions.getValueOrDef<double>(1.0e-4,"precision_goal"));
      settings.set(Spectrum_generator_settings::max_iterations, runOptions.getValueOrDef<double>(0,"max_iterations"));
      settings.set(Spectrum_generator_settings::calculate_sm_masses, runOptions.getValueOrDef<bool> (true, "calculate_sm_masses"));
      settings.set(Spectrum_generator_settings::pole_mass_loop_order, runOptions.getValueOrDef<int>(2,"pole_mass_loop_order"));
      settings.set(Spectrum_generator_settings::pole_mass_loop_order, runOptions.getValueOrDef<int>(2,"ewsb_loop_order"));
      settings.set(Spectrum_generator_settings::beta_loop_order, runOptions.getValueOrDef<int>(2,"beta_loop_order"));
      settings.set(Spectrum_generator_settings::threshold_corrections_loop_order, runOptions.getValueOrDef<int>(2,"threshold_corrections_loop_order"));
      settings.set(Spectrum_generator_settings::higgs_2loop_correction_at_as, runOptions.getValueOrDef<int>(1,"higgs_2loop_correction_at_as"));
      settings.set(Spectrum_generator_settings::higgs_2loop_correction_ab_as, runOptions.getValueOrDef<int>(1,"higgs_2loop_correction_ab_as"));
      settings.set(Spectrum_generator_settings::higgs_2loop_correction_at_at, runOptions.getValueOrDef<int>(1,"higgs_2loop_correction_at_at"));
      settings.set(Spectrum_generator_settings::higgs_2loop_correction_atau_atau, runOptions.getValueOrDef<int>(1,"higgs_2loop_correction_atau_atau"));

      spectrum_generator.set_settings(settings);

      // Generate spectrum
      spectrum_generator.run(oneset, input);
      const typename MI::Problems& problems = spectrum_generator.get_problems();
      MI model_interface(spectrum_generator,oneset,input);
      SI singletdmspec(model_interface, "FlexibleSUSY", "1.5.1");

      singletdmspec.set_override(Par::mass1,spectrum_generator.get_high_scale(),"high_scale",true);
      singletdmspec.set_override(Par::mass1,spectrum_generator.get_susy_scale(),"susy_scale",true);
      singletdmspec.set_override(Par::mass1,spectrum_generator.get_low_scale(), "low_scale", true);

      singletdmspec.set_override(Par::Pole_Mass_1srd_high,0.0, "h0_1", true);
      singletdmspec.set_override(Par::Pole_Mass_1srd_low,0.0,"h0_1", true);

      // Create a second SubSpectrum object to wrap the qedqcd object used to initialise the spectrum generator
      // Attach the sminputs object as well, so that SM pole masses can be passed on (these aren't easily
      // extracted from the QedQcd object, so use the values that we put into it.)
      QedQcdWrapper qedqcdspec(oneset,sminputs);

      // Deal with points where spectrum generator encountered a problem
      #ifdef SPECBIT_DEBUG
        std::cout<<"Problem? "<<problems.have_problem()<<std::endl;
        std::cout<<"Warning? "<<problems.have_warning()<<std::endl;
      #endif
      if( problems.have_problem() )
      {
         if( runOptions.getValueOrDef<bool>(false,"invalid_point_fatal") )
         {
            std::ostringstream errmsg;
            errmsg << "A serious problem was encountered during spectrum generation!";
            errmsg << "Message from FlexibleSUSY:" << std::endl;
            problems.print_problems(errmsg);
            problems.print_warnings(errmsg);
            SpecBit_error().raise(LOCAL_INFO,errmsg.str());
         }
         else
         {
            // Check what the problem was
            // see: contrib/MassSpectra/flexiblesusy/src/problems.hpp
            std::ostringstream msg;
            problems.print_problems(msg);
            invalid_point().raise(msg.str()); //TODO: This message isn't ending up in the logs.
         }
      }
			double QEWSB  = *input_Param.at("QEWSB");
			singletdmspec.RunToScaleOverride(QEWSB);

      // Retrieve any mass cuts
      static const Spectrum::mc_info mass_cut = runOptions.getValueOrDef<Spectrum::mc_info>(Spectrum::mc_info(), "mass_cut");
      static const Spectrum::mr_info mass_ratio_cut = runOptions.getValueOrDef<Spectrum::mr_info>(Spectrum::mr_info(), "mass_ratio_cut");

      return Spectrum(qedqcdspec,singletdmspec,sminputs,&input_Param, mass_cut, mass_ratio_cut);

    }


    template <class T>
    void fill_ScalarSingletDM_input(T& input, const std::map<str, safe_ptr<const double> >& Param,SMInputs sminputs)//,double scale)
    {
      double mH = *Param.at("mH");
      double mS = *Param.at("mS");
      double lambda_hs = *Param.at("lambda_hS");
      double lambda_s  = *Param.at("lambda_S");

      double QEFT  = mS;

      if (QEFT < sminputs.mT)
      {
				//QEFT = *Param.at("mZ");
				QEFT = sminputs.mT;
			}

      input.HiggsIN = -0.5*pow(mH,2);
      double vev = 1. / sqrt(sqrt(2.)*sminputs.GF);

      input.muSInput = pow(mS,2)-0.5*lambda_hs*pow(vev,2);
      input.LamSHInput = lambda_hs;
      input.LamSInput = lambda_s;
      input.QEWSB = QEFT;  // scale where EWSB conditions are applied
      input.Qin = QEFT; //scale;  // highest scale at which model is run to

    }

    template <class T>
    void fill_extra_input(T& input, const std::map<str, safe_ptr<const double> >& Param )
    {
      input.mu3Input=*Param.at("mu3");
    }

    bool check_perturb(const Spectrum& spec, const std::vector<SpectrumParameter>& required_parameters, double scale, int pts)
    {
      std::unique_ptr<SubSpectrum> ScalarSingletDM = spec.clone_HE();
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

    #if(FS_MODEL_ScalarSingletDM_Z2_IS_BUILT)
    void get_ScalarSingletDM_Z2_spectrum_pole(Spectrum& result)
    {
      using namespace softsusy;
      namespace myPipe = Pipes::get_ScalarSingletDM_Z2_spectrum_pole;
      const SMInputs& sminputs = *myPipe::Dep::SMINPUTS;
      const Options& runOptions=*myPipe::runOptions;
      ScalarSingletDM_Z2_input_parameters input;
      fill_ScalarSingletDM_input(input,myPipe::Param,sminputs);
      result = run_FS_spectrum_generator<ScalarSingletDM_Z2_interface<ALGORITHM1>,ScalarSingletDM_Z2Spec<ScalarSingletDM_Z2_interface<ALGORITHM1>>>(input,sminputs,*myPipe::runOptions,myPipe::Param);

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
        static const std::vector<SpectrumParameter> required_parameters = contents.all_parameters_with_tag(Par::dimensionless);
        if (!check_perturb(result,required_parameters,check_perturb_scale,check_perturb_pts))
        {
          // invalidate point as spectrum not perturbative up to scale
          std::ostringstream msg;
          msg << "Spectrum not perturbative up to scale = " << check_perturb_scale <<  std::endl;
          #ifdef SPECBIT_DEBUG
            cout << "Spectrum not perturbative up to scale = " << check_perturb_scale <<  endl;
          #endif
          invalid_point().raise(msg.str());
        }
      }

    }
    #endif

    #if(FS_MODEL_ScalarSingletDM_Z3_IS_BUILT)
    void get_ScalarSingletDM_Z3_spectrum_pole(Spectrum& result)
    {
      using namespace softsusy;
      namespace myPipe = Pipes::get_ScalarSingletDM_Z3_spectrum_pole;
      const SMInputs& sminputs = *myPipe::Dep::SMINPUTS;
      const Options& runOptions=*myPipe::runOptions;
      //double scale = runOptions.getValueOrDef<double>(173.34,"FS_high_scale");
      ScalarSingletDM_Z3_input_parameters input;
      fill_ScalarSingletDM_input(input,myPipe::Param,sminputs);
      fill_extra_input(input,myPipe::Param);
      result = run_FS_spectrum_generator<ScalarSingletDM_Z3_interface<ALGORITHM1>,ScalarSingletDM_Z3Spec<ScalarSingletDM_Z3_interface<ALGORITHM1>>>(input,sminputs,*myPipe::runOptions,myPipe::Param);

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
        static const std::vector<SpectrumParameter> required_parameters = contents.all_parameters_with_tag(Par::dimensionless);
        if (!check_perturb(result,required_parameters,check_perturb_scale,check_perturb_pts))
        {
          // invalidate point as spectrum not perturbative up to scale
          std::ostringstream msg;

          msg << "Spectrum not perturbative up to scale = " << check_perturb_scale <<  std::endl;
          #ifdef SPECBIT_DEBUG
            cout << "Spectrum not perturbative up to scale = " << check_perturb_scale <<  endl;
          #endif
          invalid_point().raise(msg.str());
        }
      }

    }
    #endif

		#if(FS_MODEL_ScalarSingletDM_Z2_IS_BUILT)
		void find_non_perturb_scale_ScalarSingletDM_Z2(double &result)
		{
			using namespace flexiblesusy;
      using namespace softsusy;
      namespace myPipe = Pipes::find_non_perturb_scale_ScalarSingletDM_Z2;
      using namespace Gambit;
      using namespace SpecBit;

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
        static const std::vector<SpectrumParameter> required_parameters = contents.all_parameters_with_tag(Par::dimensionless);
		    if (!check_perturb(fullspectrum,required_parameters,pow(10,x),3))
		    {
		      b=x;
		    }
		    else
		    {
		      a=x;
		    }
		  }
		  result = pow(10,0.5*(a+b));
		}
		#endif

		#if(FS_MODEL_ScalarSingletDM_Z3_IS_BUILT)
		void find_non_perturb_scale_ScalarSingletDM_Z3(double &result)
		{
			using namespace flexiblesusy;
      using namespace softsusy;
      namespace myPipe = Pipes::find_non_perturb_scale_ScalarSingletDM_Z3;
      using namespace Gambit;
      using namespace SpecBit;

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
        static const std::vector<SpectrumParameter> required_parameters = contents.all_parameters_with_tag(Par::dimensionless);
		    if (!check_perturb(fullspectrum,required_parameters,pow(10,x),3))
		    {
		      b=x;
		    }
		    else
		    {
		      a=x;
		    }
		  }
		  result = pow(10,0.5*(a+b));
		}
    #endif

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
      const SubSpectrum& spec = (*spectrum_dependency)->get_HE();

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

    /// Print ScalarSingletDM spectra out. Stripped down copy of MSSM version with variable names changed
    void fill_map_from_ScalarSingletDM_spectrum(std::map<std::string,double>& specmap, const Spectrum& singletdmspec,
                                         const std::vector<SpectrumParameter>& required_parameters)
    {
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
           specmap[label.str()] = singletdmspec.get_HE().get(tag,name);
         }
         // Check vector case
         else if(shape.size()==1 and shape[0]>1)
         {
           for(int i = 1; i<=shape[0]; ++i) {
             std::ostringstream label;
             label << name <<"_"<<i<<" "<< Par::toString.at(tag);
             specmap[label.str()] = singletdmspec.get_HE().get(tag,name,i);
           }
         }
         // Check matrix case
         else if(shape.size()==2)
         {
           for(int i = 1; i<=shape[0]; ++i) {
             for(int j = 1; j<=shape[0]; ++j) {
               std::ostringstream label;
               label << name <<"_("<<i<<","<<j<<") "<<Par::toString.at(tag);
               specmap[label.str()] = singletdmspec.get_HE().get(tag,name,i,j);
             }
           }
         }
         // Deal with all other cases
         else
         {
           // ERROR
           std::ostringstream errmsg;
           errmsg << "Error, invalid parameter received while converting SingletDMspectrum to map of strings! This should no be possible if the spectrum content verification routines were working correctly; they must be buggy, please report this.";
           errmsg << "Problematic parameter was: "<< tag <<", " << name << ", shape="<< shape;
           utils_error().forced_throw(LOCAL_INFO,errmsg.str());
         }
      }

    }

    void get_ScalarSingletDM_Z2_spectrum_as_map (std::map<std::string,double>& specmap)
    {
      namespace myPipe = Pipes::get_ScalarSingletDM_Z2_spectrum_as_map;
      static const Spectrum& spec = *myPipe::Dep::ScalarSingletDM_Z2_spectrum;
      static const SpectrumContents::ScalarSingletDM_Z2 contents;
      static const std::vector<SpectrumParameter> required_parameters = contents.all_parameters();
      fill_map_from_ScalarSingletDM_spectrum(specmap, spec, required_parameters);
    }

		void get_ScalarSingletDM_Z3_spectrum_as_map (std::map<std::string,double>& specmap)
    {
      namespace myPipe = Pipes::get_ScalarSingletDM_Z3_spectrum_as_map;
      static const Spectrum& spec = *myPipe::Dep::ScalarSingletDM_Z3_spectrum;
      static const SpectrumContents::ScalarSingletDM_Z3 contents;
      static const std::vector<SpectrumParameter> required_parameters = contents.all_parameters();
      fill_map_from_ScalarSingletDM_spectrum(specmap, spec, required_parameters);
    }

  } // end namespace SpecBit
} // end namespace Gambit

