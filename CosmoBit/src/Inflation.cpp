//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  CosmoBit routines relating to inflation.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Selim C. Hotinli
///          (selim.hotinli14@pimperial.ac.uk)
///  \date 2017 Jul
///  \date 2018 May
///  \date 2018 Aug - Sep
///
///  \author Patrick Stoecker
///          (stoecker@physik.rwth-aachen.de)
///  \date 2017 Nov
///  \date 2018 Jan - May
///  \date 2019 Jan, Feb, June, Nov
///
///  \author Janina Renk
///          (janina.renk@fysik.su.se)
///  \date 2018 June
///  \date 2019 Mar,June
///
///  \author Sanjay Bloor
///          (sanjay.bloor12@imperial.ac.uk)
///  \date 2019 June, Nov
///
///  \author Sebastian Hoof
///          (hoof@uni-goettingen.de)
///  \date 2020 Mar
///
///  \author Pat Scott
///          (pat.scott@uq.edu.au)
///  \date 2018 Mar
///  \date 2019 Jul
///  \date 2020 Apr
///
///  *********************************************

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/CosmoBit/CosmoBit_rollcall.hpp"
#include "gambit/CosmoBit/CosmoBit_types.hpp"

namespace Gambit
{

  namespace CosmoBit
  {
    using namespace LogTags;

    /// Helper function for diagnosing MultiModeCode errors
    std::string multimode_error_handling(int& err)
    {

      std::string message = "MultiModeCode error: ";
      switch(err)
      {

        /// > 0 = "failure; not fatal"
        case 1:
          message = "Inflation did not start.";
          break;
        case 2:
          message = "The pivot scale didn't leave the horizon.";
          break;
        case 3:
          message = "A modes' initial conditions couldn't be set consistently.";
          break;
        case 4:
          message = "Too many e-folds; can't initialize the scale factor.";
          break;
        case 5:
          message = "Trying to save the field values at some reference N, but got less evolution than that.";
          break;
        case 6:
          message = "Didn't satisfy reheating bounds.";
          break;

        /// < 0 = "fatal"
        case -1:
          message = "Numerical underflow error in odeint.";
          break;

        // Otherwise -- who knows.
        default:
          message = "GAMBIT caught an unknown error in MultiModeCode. Check MultiModeCode output and error messages for more "
                    "info (set the 'debug' switch in 'set_multimode_inputs' to '1' if you have set it to '0').";
      }
      return message;
    }

    // Function to set the generic inputs used for MultiModeCode (MMC).
    // N.B. Most of the available MMC parameters are already set by the default constructor of Multimode_inputs. These default
    //      values generally relate to the case of a single inflation field with instant reheating. In general, at least some of the
    //      parameters need to be adjusted for other models.
    void set_multimode_inputs(Multimode_inputs &result)
    {
      using namespace Pipes::set_multimode_inputs;

      // Clear anything from previous run
      result = Multimode_inputs();

      // Silence uncaught error messages from MMC ('0' = output, '1' = no output).
      result.silence_output = runOptions->getValueOrDef<int>(0,"silence_output");

      // Set pivot scale consistently with the rest of CosmoBit via capability
      result.k_pivot = *Dep::k_pivot;
      // Difference in k-space used when pivot-scale observables from mode equations are evaluated
      result.dlnk = runOptions->getValueOrDef<double>(0.4,"dlnk");

      // Set k-range and number of k-values (in log space) where the full power spectrum (PS) is evaluated
      // N.B. Not used if only the parametrised PS has been requested in a scan
      result.k_min = runOptions->getValueOrDef<double>(1e-6,"k_min");
      result.k_max = runOptions->getValueOrDef<double>(1e+6,"k_max");
      result.numsteps = runOptions->getValueOrDef<int>(100,"numsteps");
      if (result.numsteps > 1000) { CosmoBit_error().raise(LOCAL_INFO, "Currently MultiModeCode supports a maximum k-array size of 1000. Please change your yaml file settings."); };

      // Go through each inflation model known to GAMBIT, set the number of inflaton field, the parameters
      // for the inflation potential parameters (vparams), and initial conditions.

      // N.B. Available inflation potentials are defined in the MultiModeCode file modpk_potential.f90.
      //      If you want to study an inflation model of inflation that is not listed below, check if
      //      the model is available in modpk_potential.f90 or add it to that file before adding it here.
      if (ModelInUse("Inflation_InstReh_1mono23"))
      {
        result.vparams.push_back(log10(*Param["lambda"])); // MultiModeCode uses log10 of this parameter
        result.potential_choice = 5; // V(phi) = 1.5 lambda M_P^(10/3) phi^(2/3)
        result.vparam_rows = 1;
      }
      else if (ModelInUse("Inflation_InstReh_1linear"))
      {
        result.vparams.push_back(log10(*Param["lambda"])); // MultiModeCode uses log10 of this parameter
        result.potential_choice = 4; // V(phi) = lambda M_P^3 phi
        result.vparam_rows = 1;
      }
      else if (ModelInUse("Inflation_InstReh_1quadratic"))
      {
        result.vparams.push_back(2.0*log10(*Param["m_phi"])); // MultiModeCode uses log10 of m_phi^2
        result.potential_choice = 1; // V(phi) = 0.5 m^2 phi^2 = 0.5 m_phi^2 M_P^2 phi^2
        result.vparam_rows = 1;
      }
      else if (ModelInUse("Inflation_InstReh_1quartic"))
      {
        result.vparams.push_back(log10(*Param["lambda"])); // MultiModeCode uses log10 of this parameter
        result.potential_choice = 3; // V(phi) = 0.25 lambda phi^4
        result.vparam_rows = 1;
      }
      else if (ModelInUse("Inflation_InstReh_1natural"))
      {
        // MultiModeCode uses log10 of both parameters below
        result.vparams.push_back(log10(*Param["lambda"]));
        result.vparams.push_back(log10(*Param["f_phi"]));
        result.potential_choice = 2; // V(phi) = Lambda^4 [ 1 + cos(phi/f) ] = (lambda M_P)^4 [ 1 + cos(phi/[f_phi M_P]) ]
        result.vparam_rows = 2;
      }
      else if (ModelInUse("Inflation_InstReh_1Starobinsky"))
      {
        result.vparams.push_back(pow(*Param["lambda"],4)); // MultiModeCode uses the fourth power of Lambda as a parameter
        result.potential_choice = 19; // V(phi) = Lambda^4 [ 1 - exp(-sqrt(2/3) phi / M_P) ]^2 = (lambda M_P)^4 [ 1 - exp(-sqrt(2/3) phi / M_P) ]^2
        result.vparam_rows = 1;
      }

      static bool first_run = true;
      // Do some consistency check for inputs passed to MultiModeCode before the first run
      if(first_run)
      {
        int size = result.vparams.size();
        if (result.num_inflaton*result.vparam_rows != size)
        {
          std::ostringstream err;
          err << "Error in MultiModecode settings: the number of free parameters in a inflation model";
          err << " set through the vector 'vparams' has to match (num_inflaton) x (vparam_rows). In this case the ";
          err << "length is " << result.vparams.size() << " and the product is "  << result.num_inflaton*result.vparam_rows <<  " -- double check the model dependent settings in 'get_multimode_results'";
          CosmoBit_error().raise(LOCAL_INFO, err.str());
        }
        if (result.potential_choice == -1 || result.num_inflaton == -1 || result.vparam_rows == -1)
        {
          std::ostringstream err;
          err << "Error in MultiModecode settings: you did not set one (or more) of the parameters";
          err << "'potential_choice', 'num_inflaton' or 'vparam_rows' for your inflation model. ";
          err << "Double check the model dependent settings in 'get_multimode_results'";
          CosmoBit_error().raise(LOCAL_INFO, err.str());
        }
        first_run = false;
      }
    }

    /// Use the inputs from the MultiModeCode initialisation function to compute
    /// a non-parametric primordial power spectrum.
    void get_multimode_primordial_ps(Primordial_ps &result)
    {
      using namespace Pipes::get_multimode_primordial_ps;

      // Clear it all
      result = Primordial_ps();

      // Get the inflationary inputs
      Multimode_inputs inputs = *Dep::multimode_input_parameters;

      // The parameters below are only used by MultiModeCode if the full power spectrum is requested.
      int steps = inputs.numsteps;
      double kmin = inputs.k_min;
      double kmax = inputs.k_max;

      gambit_inflation_observables observables;

      //-------------------------------------------------------------
      // The function below calls the MultiModeCode backend
      //  for a given choice of inflationary model,
      //  which calculates the observables.
      //-------------------------------------------------------------

      try
      {
        observables = BEreq::multimodecode_primordial_ps(inputs.num_inflaton,
                                                       inputs.potential_choice,
                                                       inputs.evaluate_modes,
                                                       inputs.get_runningofrunning,
                                                       byVal(&inputs.phi_init0[0]),
                                                       byVal(&inputs.dphi_init0[0]),
                                                       byVal(&inputs.vparams[0]),
                                                       inputs.N_pivot,
                                                       inputs.k_pivot,
                                                       inputs.dlnk,
                                                       steps,
                                                       kmin,
                                                       kmax,
                                                       inputs.vparam_rows,
                                                       inputs.slowroll_infl_end,
                                                       inputs.instreheat,
                                                       inputs.use_deltaN_SR,
                                                       inputs.use_horiz_cross_approx);
      }
      catch(std::runtime_error &e)
      {
        logger() << e.what() << EOM;
        invalid_point().raise(e.what());
      }

      // If there's an error, pass it to the helper function and invalidate the point.
      if(observables.err != 0)
      {
        std::string message = multimode_error_handling(observables.err);
        logger() << message << EOM;
        invalid_point().raise(message);
      }

      // Fill up the GAMBIT primordial power spectrum object from the outputs.
      result.set_N_pivot(observables.N_pivot);
      result.fill_k(observables.k_array, inputs.numsteps);
      result.fill_P_s(observables.pks_array, inputs.numsteps);
      result.fill_P_s_iso(observables.pks_array_iso, inputs.numsteps);
      result.fill_P_t(observables.pkt_array, inputs.numsteps);

    }

    /// Use the inputs from the MultiModeCode initialisation function to compute
    /// a parametrised primordial power spectrum.
    void get_multimode_parametrised_ps(ModelParameters &result)
    {
      using namespace Pipes::get_multimode_parametrised_ps;
      gambit_inflation_observables observables;

      // Set up this ModelParameters object on first run
      static bool first = true;
      if (first)
      {
        result.setModelName("PowerLaw_ps");
        result._definePars({"ln10A_s","n_s","r","N_pivot"});
        first = false;
      }

      // Get the inflationary inputs
      Multimode_inputs inputs = *Dep::multimode_input_parameters;

      //-------------------------------------------------------------
      // The function below calls the MultiModeCode backend
      //  for a given choice of inflationary model,
      //  which calculates the observables.
      //-------------------------------------------------------------

      try
      {
        observables = BEreq::multimodecode_parametrised_ps(inputs.num_inflaton,
                                                         inputs.potential_choice,
                                                         inputs.evaluate_modes,
                                                         inputs.get_runningofrunning,
                                                         byVal(&inputs.phi_init0[0]),
                                                         byVal(&inputs.dphi_init0[0]),
                                                         byVal(&inputs.vparams[0]),
                                                         inputs.N_pivot,
                                                         inputs.k_pivot,
                                                         inputs.dlnk,
                                                         inputs.vparam_rows,
                                                         inputs.slowroll_infl_end,
                                                         inputs.instreheat,
                                                         inputs.use_deltaN_SR,
                                                         inputs.use_horiz_cross_approx);
      }
      catch(std::runtime_error &e)
      {
        logger() << e.what() << EOM;
        invalid_point().raise(e.what());
      }
      // If there's an error, pass it to the helper function and invalidate the point.
      if(observables.err != 0)
      {
        std::string message = multimode_error_handling(observables.err);
        logger() << message << EOM;
        invalid_point().raise(message);
      }

      // Set the parameters of the PowerLaw_ps model from the outputs.
      result.setValue("N_pivot", observables.N_pivot);
      result.setValue("n_s", observables.ns);
      result.setValue("ln10A_s", 10. * log(10.) + log(observables.As) );
      result.setValue("r", observables.r);

    }

  } // namespace CosmoBit

} // namespace Gambit
