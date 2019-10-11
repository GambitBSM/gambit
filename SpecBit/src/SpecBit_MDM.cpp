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
///  \author James McKay
///    \date 2018 March
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
#include "gambit/SpecBit/model_files_and_boxes.hpp"

#include "gambit/SpecBit/MDMSpec.hpp"

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


    template<class MI,class SI>
    Spectrum run_FS_spectrum_generator
        ( const typename MI::InputParameters& input
        , const SMInputs& sminputs
        , const Options& runOptions
        , const std::map<str, safe_ptr<const double> >& input_Param
        )
    {
      softsusy::QedQcd oneset;

      // Fill QedQcd object with SMInputs values
      setup_QedQcd(oneset,sminputs);

      // Run everything to Mz
      oneset.toMz();

      // Create spectrum generator object
      typename MI::SpectrumGenerator spectrum_generator;

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
      SI mdmspec(model_interface, "FlexibleSUSY", "1.5.1");


      mdmspec.set_override(Par::mass1,spectrum_generator.get_high_scale(),"high_scale",true);
      mdmspec.set_override(Par::mass1,spectrum_generator.get_susy_scale(),"susy_scale",true);
      mdmspec.set_override(Par::mass1,spectrum_generator.get_low_scale(), "low_scale", true);

      mdmspec.set_override(Par::Pole_Mass_1srd_high,0.0, "h0_1", true);
      mdmspec.set_override(Par::Pole_Mass_1srd_low,0.0,"h0_1", true);

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
			mdmspec.RunToScaleOverride(QEWSB);

      // Retrieve any mass cuts
      static const Spectrum::mc_info mass_cut = runOptions.getValueOrDef<Spectrum::mc_info>(Spectrum::mc_info(), "mass_cut");
      static const Spectrum::mr_info mass_ratio_cut = runOptions.getValueOrDef<Spectrum::mr_info>(Spectrum::mr_info(), "mass_ratio_cut");

      return Spectrum(qedqcdspec,mdmspec,sminputs,&input_Param, mass_cut, mass_ratio_cut);

    }


    template <class T>
    void fill_MDM_input(T& input, const std::map<str, safe_ptr<const double> >& Param,SMInputs sminputs)
    {
      double mH = *Param.at("mH");
      double mChi = *Param.at("mChi");

      //double QEFT  = mChi;
			/*
      if (QEFT < sminputs.mT)
      {
				QEFT = sminputs.mT;
			}
      */
      double QEFT  = sminputs.mT;

      input.HiggsIN = 0.5*pow(mH,2);

      input.YcIN = 0.5*mChi;

      input.QEWSB = QEFT;  // scale where EWSB conditions are applied
      input.Qin = QEFT; //scale;  // highest scale at which model is run to

    }

    bool check_perturb_MDM(const Spectrum& spec,double scale,int pts)
    {
      using namespace flexiblesusy;
      using namespace Gambit;
      using namespace SpecBit;
      std::unique_ptr<SubSpectrum> MDM = spec.clone_HE();
      double step = log10(scale) / pts;
      double runto;

      //const double ul = std::sqrt(4.0 * pi); // Maximum value for perturbative couplings, same perturbativity bound that FlexibleSUSY uses
      double ul = 4.0 * pi;
      for (int i=0;i<pts;i++)
      {
        runto = pow(10,step*float(i+1.0)); // scale to run spectrum to
        if (runto<100){runto=100.0;}// avoid running to low scales

        try
	      {
	        MDM -> RunToScale(runto);
	      }
	      catch (const Error& error)
	      {
	        return false;
	      };




        static const SpectrumContents::MDM contents;
        static const std::vector<SpectrumParameter> required_parameters = contents.all_parameters_with_tag(Par::dimensionless);

        for(std::vector<SpectrumParameter>::const_iterator it = required_parameters.begin();
              it != required_parameters.end(); ++it)
        {
          const Par::Tags        tag   = it->tag();
          const std::string      name  = it->name();
          const std::vector<int> shape = it->shape();
          std::ostringstream label;
          label << name <<" "<< Par::toString.at(tag);

          if (name == "lambda_h"){ul =  2*pi;}
          else {ul = 4.0 * pi;}

          if(shape.size()==1 and shape[0]==1)
          {
            if (abs(MDM->get(tag,name))>ul)
            {
							return false;
						}
          }
          else if(shape.size()==1 and shape[0]>1)
          {
            for(int k = 1; k<=shape[0]; ++k)
            {
              if (abs(MDM->get(tag,name,k))>ul) return false;
            }
          }
          else if(shape.size()==2)
          {
            for(int k = 1; k<=shape[0]; ++k)
            {
              for(int j = 1; j<=shape[0]; ++j)
              {
                if (abs(MDM->get(tag,name,k,j))>ul) return false;
              }
            }
          }

        }
      }

      return true;

    }

    #if(FS_MODEL_MDM_IS_BUILT)
    void get_MDM_spectrum(Spectrum& result)
    {
      using namespace softsusy;
      namespace myPipe = Pipes::get_MDM_spectrum;
      const SMInputs& sminputs = *myPipe::Dep::SMINPUTS;
      const Options& runOptions=*myPipe::runOptions;
      //double scale = runOptions.getValueOrDef<double>(173.34,"FS_high_scale");
      MDM_input_parameters input;
      fill_MDM_input(input,myPipe::Param,sminputs);
      result = run_FS_spectrum_generator<MDM_interface<ALGORITHM1>,MDMSpec<MDM_interface<ALGORITHM1>>>(input,sminputs,*myPipe::runOptions,myPipe::Param);

      int check_perturb_pts = runOptions.getValueOrDef<double>(10,"check_perturb_pts");
      double do_check_perturb = runOptions.getValueOrDef<bool>(false,"check_perturb");
      double check_perturb_scale = runOptions.getValueOrDef<double>(1.22e19,"check_high_scale");
      double input_scale_tolerance = runOptions.getValueOrDef<double>(1e-3,"input_scale_tolerance");

      // Check that the Higgs MSbar parameter has been provided at the scale of the MDM MSbar multiplet mass
      double Qin = *myPipe::Param.at("Qin");
      if (abs((Qin - *myPipe::Param.at("mChi"))/Qin) > input_scale_tolerance) SpecBit_error().raise(LOCAL_INFO, "SM_Higgs_running::Qin must equal MDM::mChi");

      if (do_check_perturb)
      {
        if (!check_perturb_MDM(result,check_perturb_scale,check_perturb_pts))
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


		void find_non_perturb_scale_MDM(double &result)
		{
			using namespace flexiblesusy;
      using namespace softsusy;
      namespace myPipe = Pipes::find_non_perturb_scale_MDM;
      using namespace Gambit;
      using namespace SpecBit;

      const Spectrum& fullspectrum = *myPipe::Dep::MDM_spectrum;

		  // bound x by (a,b)
		  // do all this is log space please

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
		    //cout<< "\r" << "(a,b) = " << a << "  " << b << endl;
		    //std::cout << std::flush;

		    x=0.5*(b-a)+a;


		    if (!check_perturb_MDM(fullspectrum,pow(10,x),3))
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


    /// Print MDM spectrum out. Stripped down copy from MSSM version with variable names changed
    void fill_map_from_MDMspectrum(std::map<std::string,double>&, const Spectrum&);

    void get_MDM_spectrum_as_map (std::map<std::string,double>& specmap)
    {
      namespace myPipe = Pipes::get_MDM_spectrum_as_map;
      const Spectrum& mdmspec(*myPipe::Dep::MDM_spectrum);
      fill_map_from_MDMspectrum(specmap, mdmspec);
    }

    void fill_map_from_MDMspectrum(std::map<std::string,double>& specmap, const Spectrum& mdmspec)
    {
      /// Add everything... use spectrum contents routines to automate task
      static const SpectrumContents::MDM contents;
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
           specmap[label.str()] = mdmspec.get_HE().get(tag,name);
         }
         // Check vector case
         else if(shape.size()==1 and shape[0]>1)
         {
           for(int i = 1; i<=shape[0]; ++i) {
             std::ostringstream label;
             label << name <<"_"<<i<<" "<< Par::toString.at(tag);
             specmap[label.str()] = mdmspec.get_HE().get(tag,name,i);
           }
         }
         // Check matrix case
         else if(shape.size()==2)
         {
           for(int i = 1; i<=shape[0]; ++i) {
             for(int j = 1; j<=shape[0]; ++j) {
               std::ostringstream label;
               label << name <<"_("<<i<<","<<j<<") "<<Par::toString.at(tag);
               specmap[label.str()] = mdmspec.get_HE().get(tag,name,i,j);
             }
           }
         }
         // Deal with all other cases
         else
         {
           // ERROR
           std::ostringstream errmsg;
           errmsg << "Error, invalid parameter received while converting MDMspectrum to map of strings! This should no be possible if the spectrum content verification routines were working correctly; they must be buggy, please report this.";
           errmsg << "Problematic parameter was: "<< tag <<", " << name << ", shape="<< shape;
           utils_error().forced_throw(LOCAL_INFO,errmsg.str());
         }
      }

    }

  } // end namespace SpecBit
} // end namespace Gambit

