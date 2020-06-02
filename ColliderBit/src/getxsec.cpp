//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Module functions for computing cross-sections
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2019 Feb, May
///
///  \author Anders Kvellestad
///          (a.kvellestad@imperial.ac.uk)
///  \date 2019 Sep, Oct, Nov
///
///  *********************************************

#include "gambit/ColliderBit/ColliderBit_eventloop.hpp"
#include "gambit/ColliderBit/complete_process_PID_pair_multimaps.hpp"

// #define COLLIDERBIT_DEBUG
#define DEBUG_PREFIX "DEBUG: OMP thread " << omp_get_thread_num() << ": " << __FILE__ << ":" << __LINE__ << ":  "

namespace Gambit
{

  namespace ColliderBit
  {

    extern std::map<std::string,bool> event_weight_flags;

    // ======= Utility functions =======


    /// Helper function that takes a cross-section value in fb or pb, 
    /// along with an absolute or relative uncertainty, and returns the 
    /// xsec and absolute uncertainty in fb.
    std::pair<double,double> convert_xsecs_to_fb(double input_xsec, double input_xsec_uncert, str input_unit, bool input_fractional_uncert)
    {
      double xsec_fb;
      double xsec_uncert_fb;

      if (input_unit == "fb" && !input_fractional_uncert)
      {
        xsec_fb = input_xsec;
        xsec_uncert_fb = input_xsec_uncert;
      }
      else if (input_unit == "fb" && input_fractional_uncert)
      {
        xsec_fb = input_xsec;
        xsec_uncert_fb = input_xsec_uncert * xsec_fb;
      }
      else if (input_unit == "pb" && !input_fractional_uncert)
      {
        xsec_fb = input_xsec * 1000.;
        xsec_uncert_fb = input_xsec_uncert * 1000.;
      }
      else if (input_unit == "pb" && input_fractional_uncert)
      {
        xsec_fb = input_xsec * 1000.;
        xsec_uncert_fb = input_xsec_uncert * xsec_fb;
      }
      else
      {
        ColliderBit_error().raise(LOCAL_INFO, "Unknown combination of options for function convert_xsecs_to_fb.");
      }      

      return std::make_pair(xsec_fb, xsec_uncert_fb);
    }



    // ======= Module functions =======


    #ifdef HAVE_PYBIND11
      /// Get a cross-section from the xsecBE backend
      void getPIDPairCrossSectionsMap_xsecBE(map_PID_pair_PID_pair_xsec& result)
      {
        using namespace Pipes::getPIDPairCrossSectionsMap_xsecBE;
  
        if(*Loop::iteration == COLLIDER_INIT)
        {
          result.clear();
        }
 
        if(*Loop::iteration == XSEC_CALCULATION)
        {
          // Create dicts to pass parameters and flags to the backend
          pybind11::dict xsecBE_pars;
          // pybind11::dict xsecBE_flags;

          // // First set the flags
          // xsecBE_flags["alphas_err"] = true;
          // xsecBE_flags["scale_err"] = true;
          // xsecBE_flags["pdf_err"] = true;
          // xsecBE_flags["regression_err"] = true;
          // BEreq::xsecBE_set_flags(xsecBE_flags);

          // Then set the neceassary parameters and spectrum info:
          // - Energy
          // @todo This can't be hard-coded... Need to match it to collider energy!
          xsecBE_pars["energy"] = 13000;
          BEreq::xsecBE_set_parameters(xsecBE_pars);

          // - Import the SLHA1 spectrum
          const SLHAstruct& slha_spec = *Dep::SLHA1Spectrum;
          str slha_string = slha_spec.str();
          BEreq::xsecBE_import_slha_string(slha_string);

          // Now get the cross-sections for all the requested PID pairs. Save the results
          // in the result map (type map<PID_pair,PID_pair_xsec_container>)
          for (const PID_pair& pid_pair : *Dep::ActivePIDPairs)
          {

            // Create PID_pair_xsec_container instance
            // and set the PIDs
            PID_pair_xsec_container pp_xs;
            pp_xs.set_pid_pair(pid_pair);

            // Get the PIDs as an iipair (= std::pair<int,int>)
            iipair proc = pid_pair.PIDs();

            // Get dictionary with cross-section results from backend
            pybind11::dict xs_fb_dict = BEreq::xsecBE_get_xsection(proc);

            // The xsec_container classes don't have asymmetric errors yet,
            // so let's take the max error for now
            double xs_fb = xs_fb_dict["central"].cast<double>();
            double xs_symm_err_fb = std::max(xs_fb_dict["tot_err_down"].cast<double>(), xs_fb_dict["tot_err_up"].cast<double>());
            // double xs_fb = xs_fb_dict["central"];
            // double xs_symm_err_fb = std::max(xs_fb_dict["tot_err_down"], xs_fb_dict["tot_err_up"]);

            // Update the PID_pair_xsec_container instance 
            pp_xs.set_xsec(xs_fb, xs_symm_err_fb);
            pp_xs.set_info_string("xsecBE_NLO");

            // Add it to the result map
            result[pid_pair] = pp_xs;
          }

        } // end iteration

      }
    #endif

    #ifdef HAVE_PYBIND11
      /// Get a cross-section from the salami backend (using Prospino for LO)
      void getPIDPairCrossSectionsMap_salami(map_PID_pair_PID_pair_xsec& result)
      {
        using namespace Pipes::getPIDPairCrossSectionsMap_salami;
  
        // Read options from yaml file
        const static double fixed_xs_rel_err = runOptions->getValueOrDef<double>(-1.0, "fixed_relative_cross_section_uncertainty");

        // Collider energy 
        // @todo Need to get this from the collider options
        double energy = 13000.;

        if(*Loop::iteration == COLLIDER_INIT)
        {
          result.clear();
        }

        if(*Loop::iteration == XSEC_CALCULATION)
        {

          // Get a copy of the SLHA1 spectrum that we can modify
          SLHAstruct slha(*Dep::SLHA1Spectrum);

          // Contstruct EXTPAR block from the GAMBIT model parameters
          // @todo Put this in a separate utils function 'contruct_extpar_block'. 
          SLHAea_add_block(slha, "EXTPAR");
          slha["EXTPAR"][""] << 0 << *Param.at("Qin") << "# scale Q where the parameters below are defined";
          slha["EXTPAR"][""] << 1 << *Param.at("M1") << "# M_1";
          slha["EXTPAR"][""] << 2 << *Param.at("M2") << "# M_2";
          slha["EXTPAR"][""] << 3 << *Param.at("M3") << "# M_3";
          slha["EXTPAR"][""] << 11 << *Param.at("Au_33") << "# A_t";
          slha["EXTPAR"][""] << 12 << *Param.at("Ad_33") << "# A_b";
          slha["EXTPAR"][""] << 13 << *Param.at("Ae_33") << "# A_l";
          if(Param.find("mu") != Param.end() && Param.find("mA") != Param.end())
          {
            slha["EXTPAR"][""] << 23 << *Param.at("mu") << "# mu";
            slha["EXTPAR"][""] << 24 << pow(*Param.at("mA"),2) << "# m_A^2";
          }
          else if(Param.find("mHd2") != Param.end() && Param.find("mHd2") != Param.end())
          {
            slha["EXTPAR"][""] << 21 << *Param.at("mHd2") << "# m_Hd^2";
            slha["EXTPAR"][""] << 22 << *Param.at("mHu2") << "# m_Hu^2";
          }
          else
          {
            ColliderBit_error().raise(LOCAL_INFO, "Got an unknown combination of Higgs sector parameters when trying to fill an SLHA EXTPAR block.");
          }
          slha["EXTPAR"][""] << 31 << sqrt(*Param.at("ml2_11")) << "# M_(L,11)";
          slha["EXTPAR"][""] << 32 << sqrt(*Param.at("ml2_22")) << "# M_(L,22)";
          slha["EXTPAR"][""] << 33 << sqrt(*Param.at("ml2_33")) << "# M_(L,33)";
          slha["EXTPAR"][""] << 34 << sqrt(*Param.at("me2_11")) << "# M_(E,11)";
          slha["EXTPAR"][""] << 35 << sqrt(*Param.at("me2_22")) << "# M_(E,22)";
          slha["EXTPAR"][""] << 36 << sqrt(*Param.at("me2_33")) << "# M_(E,33)";
          slha["EXTPAR"][""] << 41 << sqrt(*Param.at("mq2_11")) << "# M_(Q,11)";
          slha["EXTPAR"][""] << 42 << sqrt(*Param.at("mq2_22")) << "# M_(Q,22)";
          slha["EXTPAR"][""] << 43 << sqrt(*Param.at("mq2_33")) << "# M_(Q,33)";
          slha["EXTPAR"][""] << 44 << sqrt(*Param.at("mu2_11")) << "# M_(U,11)";
          slha["EXTPAR"][""] << 45 << sqrt(*Param.at("mu2_22")) << "# M_(U,22)";
          slha["EXTPAR"][""] << 46 << sqrt(*Param.at("mu2_33")) << "# M_(U,33)";
          slha["EXTPAR"][""] << 47 << sqrt(*Param.at("md2_11")) << "# M_(D,11)";
          slha["EXTPAR"][""] << 48 << sqrt(*Param.at("md2_22")) << "# M_(D,22)";
          slha["EXTPAR"][""] << 49 << sqrt(*Param.at("md2_33")) << "# M_(D,33)";

          // Create a SLHA string
          str slha_string = slha.str();

          // 
          // Init Prospino
          // 

          // We only want the LO cross-section from Prospino
          const static int inlo = 0;
          const static int isq_ng_in = 1;  // specify degenerate [0] or free [1] squark masses
          const static int icoll_in = 1;   // collider : tevatron[0], lhc[1]
          const static double energy_in = energy;  // collider energy in GeV
          const static int i_error_in = 0; // with central scale [0] or scale variation [1]
          const static bool set_missing_cross_sections_to_zero = runOptions->getValueOrDef<bool>(false, "set_missing_cross_sections_to_zero");

          // Pass SLHA1 input to prospino
          BEreq::prospino_read_slha1_input(slha);        

          // Loop over each PID_pair in ActivePIDPairs
          // and calculate LO cross-sections
          std::map<PID_pair, PID_pair_xsec_container> pp_LOxs_map; 
          for (const PID_pair& pid_pair : *Dep::ActivePIDPairs)
          {
            // Create PID_pair_xsec_container instance and set the PIDs
            PID_pair_xsec_container pp_LOxs;
            pp_LOxs.set_pid_pair(pid_pair);

            // Call Prospino and get the result in a map<string,double>.
            map_str_dbl prospino_output = BEreq::prospino_run_alloptions(pid_pair, inlo, isq_ng_in, icoll_in, energy_in, i_error_in, set_missing_cross_sections_to_zero);

            // Get the trust_level
            int prospino_trust_level = static_cast<int>(prospino_output.at("trust_level"));

            // Update the PID_pair_xsec_container instance with the Prospino result
            double LOxs_fb = prospino_output.at("LO_ms[pb]") * 1000.;
            double LOxs_rel_err = prospino_output.at("LO_rel_error");
            pp_LOxs.set_info_string("prospino_LO");

            double LOxs_err_fb = LOxs_fb * LOxs_rel_err;
            pp_LOxs.set_xsec(LOxs_fb, LOxs_err_fb);

            cerr << "DEBUG: got trust_level: " << prospino_trust_level << endl;
            pp_LOxs.set_trust_level(prospino_trust_level);

            // Put the LO cross-section in the map
            pp_LOxs_map[pid_pair] = pp_LOxs;
          }


          // Pass a dictionary with parameters/settings (if any) to the backend
          pybind11::dict salami_pars;
          // (fill salami_pars here...)
          BEreq::salami_set_parameters(salami_pars);

          // Import the SLHA1 spectrum
          BEreq::salami_import_slha_string(slha_string);

          // Now get the cross-sections for all the requested PID pairs. Save the results
          // in the result map (type map<PID_pair,PID_pair_xsec_container>)
          for (const PID_pair& pid_pair : *Dep::ActivePIDPairs)
          {
            // Create PID_pair_xsec_container instance
            // and set the PIDs
            PID_pair_xsec_container pp_xs;
            pp_xs.set_pid_pair(pid_pair);

            // Get the PIDs as an iipair (= std::pair<int,int>)
            iipair proc = pid_pair.PIDs();

            // Get LO cross-section value from map
            double LOxs_fb = pp_LOxs_map.at(pid_pair).xsec();

            // Get the trust_level to the level of the pp_LOxs
            int LOxs_trust_level = pp_LOxs_map.at(pid_pair).trust_level();

            // Get dictionary with cross-section results from backend
            pybind11::dict xs_fb_dict = BEreq::salami_get_xsection(proc, energy, LOxs_fb);

            // The xsec_container classes don't have asymmetric errors yet,
            // so let's take the max error for now
            double xs_fb = xs_fb_dict["central"].cast<double>();
            double xs_err_fb = std::max(xs_fb_dict["tot_err_down"].cast<double>(), xs_fb_dict["tot_err_up"].cast<double>());

            // Get the trust_level reported by the salami backend
            int xs_trust_level = xs_fb_dict["trust_level"].cast<int>();

            // Should we rather use the fixed uncertainty from the YAML file?
            if(fixed_xs_rel_err >= 0.0)
            {
              xs_err_fb = xs_fb * fixed_xs_rel_err;
            }

            // Update the PID_pair_xsec_container instance 
            pp_xs.set_xsec(xs_fb, xs_err_fb);
            pp_xs.set_info_string("salami_NLO");

            // Set the trust_level
            pp_xs.set_trust_level(std::min(LOxs_trust_level, xs_trust_level));

            // Add it to the result map
            result[pid_pair] = pp_xs;
          }

        } // end iteration

      }
    #endif


    /// Get a cross-section from Prospino
    void getPIDPairCrossSectionsMap_prospino(map_PID_pair_PID_pair_xsec& result)
    {
      using namespace Pipes::getPIDPairCrossSectionsMap_prospino;

      // Read options from yaml file
      const static double fixed_xs_rel_err = runOptions->getValueOrDef<double>(-1.0, "fixed_relative_cross_section_uncertainty");
      const static int inlo = runOptions->getValueOrDef<int>(1, "inlo");

      if(*Loop::iteration == COLLIDER_INIT)
      {
        result.clear();
      }

      if(*Loop::iteration == XSEC_CALCULATION)
      {

        // Get a copy of the SLHA1 spectrum that we can modify
        SLHAstruct slha(*Dep::SLHA1Spectrum);

        // // Get the GAMBIT model parameters
        // const param_map_type& model_params = Param;

        // Contstruct EXTPAR block from the GAMBIT model parameters
        SLHAea_add_block(slha, "EXTPAR");
        slha["EXTPAR"][""] << 0 << *Param.at("Qin") << "# scale Q where the parameters below are defined";
        slha["EXTPAR"][""] << 1 << *Param.at("M1") << "# M_1";
        slha["EXTPAR"][""] << 2 << *Param.at("M2") << "# M_2";
        slha["EXTPAR"][""] << 3 << *Param.at("M3") << "# M_3";
        slha["EXTPAR"][""] << 11 << *Param.at("Au_33") << "# A_t";
        slha["EXTPAR"][""] << 12 << *Param.at("Ad_33") << "# A_b";
        slha["EXTPAR"][""] << 13 << *Param.at("Ae_33") << "# A_l";
        if(Param.find("mu") != Param.end() && Param.find("mA") != Param.end())
        {
          slha["EXTPAR"][""] << 23 << *Param.at("mu") << "# mu";
          slha["EXTPAR"][""] << 24 << pow(*Param.at("mA"),2) << "# m_A^2";
        }
        else if(Param.find("mHd2") != Param.end() && Param.find("mHd2") != Param.end())
        {
          slha["EXTPAR"][""] << 21 << *Param.at("mHd2") << "# m_Hd^2";
          slha["EXTPAR"][""] << 22 << *Param.at("mHu2") << "# m_Hu^2";
        }
        else
        {
          ColliderBit_error().raise(LOCAL_INFO, "Got an unknown combination of Higgs sector parameters when trying to fill an SLHA EXTPAR block.");
        }
        slha["EXTPAR"][""] << 31 << sqrt(*Param.at("ml2_11")) << "# M_(L,11)";
        slha["EXTPAR"][""] << 32 << sqrt(*Param.at("ml2_22")) << "# M_(L,22)";
        slha["EXTPAR"][""] << 33 << sqrt(*Param.at("ml2_33")) << "# M_(L,33)";
        slha["EXTPAR"][""] << 34 << sqrt(*Param.at("me2_11")) << "# M_(E,11)";
        slha["EXTPAR"][""] << 35 << sqrt(*Param.at("me2_22")) << "# M_(E,22)";
        slha["EXTPAR"][""] << 36 << sqrt(*Param.at("me2_33")) << "# M_(E,33)";
        slha["EXTPAR"][""] << 41 << sqrt(*Param.at("mq2_11")) << "# M_(Q,11)";
        slha["EXTPAR"][""] << 42 << sqrt(*Param.at("mq2_22")) << "# M_(Q,22)";
        slha["EXTPAR"][""] << 43 << sqrt(*Param.at("mq2_33")) << "# M_(Q,33)";
        slha["EXTPAR"][""] << 44 << sqrt(*Param.at("mu2_11")) << "# M_(U,11)";
        slha["EXTPAR"][""] << 45 << sqrt(*Param.at("mu2_22")) << "# M_(U,22)";
        slha["EXTPAR"][""] << 46 << sqrt(*Param.at("mu2_33")) << "# M_(U,33)";
        slha["EXTPAR"][""] << 47 << sqrt(*Param.at("md2_11")) << "# M_(D,11)";
        slha["EXTPAR"][""] << 48 << sqrt(*Param.at("md2_22")) << "# M_(D,22)";
        slha["EXTPAR"][""] << 49 << sqrt(*Param.at("md2_33")) << "# M_(D,33)";

        // Pass SLHA1 input to prospino
        BEreq::prospino_read_slha1_input(slha);        

        // Loop over each PID_pair in ActivePIDPairs
        for (const PID_pair& pid_pair : *Dep::ActivePIDPairs)
        {
          // Create PID_pair_xsec_container instance and set the PIDs
          PID_pair_xsec_container pp_xs;
          pp_xs.set_pid_pair(pid_pair);

          // Call Prospino and get the result in a map<string,double>
          map_str_dbl prospino_output = BEreq::prospino_run(pid_pair, *runOptions);

          // Get the trust_level
          int prospino_trust_level = static_cast<int>(prospino_output.at("trust_level"));

          // Update the PID_pair_xsec_container instance with the Prospino result
          double xs_fb;
          double xs_rel_err;
          if(inlo == 0)
          {
            xs_fb = prospino_output.at("LO_ms[pb]") * 1000.;
            xs_rel_err = prospino_output.at("LO_rel_error");
            pp_xs.set_info_string("prospino_LO");
          }
          else
          {
            xs_fb = prospino_output.at("NLO_ms[pb]") * 1000.;
            xs_rel_err = prospino_output.at("NLO_rel_error");
            pp_xs.set_info_string("prospino_NLO");
          }
          // Should we rather use the fixed uncertainty from the YAML file?
          if(fixed_xs_rel_err >= 0.0) { xs_rel_err = fixed_xs_rel_err; }
          double xs_err_fb = xs_fb * xs_rel_err;

          pp_xs.set_xsec(xs_fb, xs_err_fb);

          pp_xs.set_trust_level(prospino_trust_level);

          // Add the PID_pair_xsec_container instance to the result map
          result[pid_pair] = pp_xs;
        }
      }
    } // end getPIDPairCrossSectionsMap_prospino



    /// Test functions for provding PIDPairCrossSectionsMap (cross-sections in fb)
    PID_pair_xsec_container silly_pid_xsec_constructor(PID_pair pid_pair, double xsec_val)
    {
      PID_pair_xsec_container result;

      result.reset();
      result.set_pid_pair(pid_pair);
      result.set_xsec(xsec_val, xsec_val * 0.01);

      return result;
    }

    void getPIDPairCrossSectionsMap_testing(map_PID_pair_PID_pair_xsec& result)
    {
      using namespace Pipes::getPIDPairCrossSectionsMap_testing;

      static bool first = true;
      static map_PID_pair_PID_pair_xsec all_my_pid_pair_xsecs;
      if (first)
      {
        all_my_pid_pair_xsecs[PID_pair(1000021,1000021)] = silly_pid_xsec_constructor( PID_pair(1000021,1000021), 5.39328e+01);
        all_my_pid_pair_xsecs[PID_pair(1000001,1000021)] = silly_pid_xsec_constructor( PID_pair(1000001,1000021), 2.37137e+01);
        all_my_pid_pair_xsecs[PID_pair(-1000001,1000021)] = silly_pid_xsec_constructor( PID_pair(-1000001,1000021), 2.37137e+01);
        all_my_pid_pair_xsecs[PID_pair(1000002,1000021)] = silly_pid_xsec_constructor( PID_pair(1000002,1000021), 6.28372e+01);
        all_my_pid_pair_xsecs[PID_pair(-1000002,1000021)] = silly_pid_xsec_constructor( PID_pair(-1000002,1000021), 6.28372e+01);
        all_my_pid_pair_xsecs[PID_pair(1000003,1000021)] = silly_pid_xsec_constructor( PID_pair(1000003,1000021), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000003,1000021)] = silly_pid_xsec_constructor( PID_pair(-1000003,1000021), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000004,1000021)] = silly_pid_xsec_constructor( PID_pair(1000004,1000021), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000004,1000021)] = silly_pid_xsec_constructor( PID_pair(-1000004,1000021), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000005,1000021)] = silly_pid_xsec_constructor( PID_pair(1000005,1000021), 7.47639e-01);
        all_my_pid_pair_xsecs[PID_pair(-1000005,1000021)] = silly_pid_xsec_constructor( PID_pair(-1000005,1000021), 7.47639e-01);
        all_my_pid_pair_xsecs[PID_pair(1000021,2000001)] = silly_pid_xsec_constructor( PID_pair(1000021,2000001), 2.72593e+01);
        all_my_pid_pair_xsecs[PID_pair(-2000001,1000021)] = silly_pid_xsec_constructor( PID_pair(-2000001,1000021), 2.72593e+01);
        all_my_pid_pair_xsecs[PID_pair(1000021,2000002)] = silly_pid_xsec_constructor( PID_pair(1000021,2000002), 7.01002e+01);
        all_my_pid_pair_xsecs[PID_pair(-2000002,1000021)] = silly_pid_xsec_constructor( PID_pair(-2000002,1000021), 7.01002e+01);
        all_my_pid_pair_xsecs[PID_pair(1000021,2000003)] = silly_pid_xsec_constructor( PID_pair(1000021,2000003), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000003,1000021)] = silly_pid_xsec_constructor( PID_pair(-2000003,1000021), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000021,2000004)] = silly_pid_xsec_constructor( PID_pair(1000021,2000004), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000004,1000021)] = silly_pid_xsec_constructor( PID_pair(-2000004,1000021), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000021,2000005)] = silly_pid_xsec_constructor( PID_pair(1000021,2000005), 6.99128e-01);
        all_my_pid_pair_xsecs[PID_pair(-2000005,1000021)] = silly_pid_xsec_constructor( PID_pair(-2000005,1000021), 6.99128e-01);
        all_my_pid_pair_xsecs[PID_pair(-1000001,1000001)] = silly_pid_xsec_constructor( PID_pair(-1000001,1000001), 3.87896e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000002,1000002)] = silly_pid_xsec_constructor( PID_pair(-1000002,1000002), 4.56614e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000003,1000003)] = silly_pid_xsec_constructor( PID_pair(-1000003,1000003), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000004,1000004)] = silly_pid_xsec_constructor( PID_pair(-1000004,1000004), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000005,1000005)] = silly_pid_xsec_constructor( PID_pair(-1000005,1000005), 5.37644e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000006,1000006)] = silly_pid_xsec_constructor( PID_pair(-1000006,1000006), 2.06296e+01);
        all_my_pid_pair_xsecs[PID_pair(-2000001,2000001)] = silly_pid_xsec_constructor( PID_pair(-2000001,2000001), 5.43262e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000002,2000002)] = silly_pid_xsec_constructor( PID_pair(-2000002,2000002), 6.00883e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000003,2000003)] = silly_pid_xsec_constructor( PID_pair(-2000003,2000003), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000004,2000004)] = silly_pid_xsec_constructor( PID_pair(-2000004,2000004), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000005,2000005)] = silly_pid_xsec_constructor( PID_pair(-2000005,2000005), 4.11417e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000006,2000006)] = silly_pid_xsec_constructor( PID_pair(-2000006,2000006), 4.07898e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000003,1000001)] = silly_pid_xsec_constructor( PID_pair(-1000003,1000001), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000001,1000003)] = silly_pid_xsec_constructor( PID_pair(-1000001,1000003), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000005,1000001)] = silly_pid_xsec_constructor( PID_pair(-1000005,1000001), 1.03708e-01);
        all_my_pid_pair_xsecs[PID_pair(-1000001,1000005)] = silly_pid_xsec_constructor( PID_pair(-1000001,1000005), 1.03708e-01);
        all_my_pid_pair_xsecs[PID_pair(-2000001,1000001)] = silly_pid_xsec_constructor( PID_pair(-2000001,1000001), 3.13966e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000001,2000001)] = silly_pid_xsec_constructor( PID_pair(-1000001,2000001), 3.13966e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000003,1000001)] = silly_pid_xsec_constructor( PID_pair(-2000003,1000001), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000001,2000003)] = silly_pid_xsec_constructor( PID_pair(-1000001,2000003), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000005,1000001)] = silly_pid_xsec_constructor( PID_pair(-2000005,1000001), 3.91678e-01);
        all_my_pid_pair_xsecs[PID_pair(-1000001,2000005)] = silly_pid_xsec_constructor( PID_pair(-1000001,2000005), 3.91678e-01);
        all_my_pid_pair_xsecs[PID_pair(-1000004,1000002)] = silly_pid_xsec_constructor( PID_pair(-1000004,1000002), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000002,1000004)] = silly_pid_xsec_constructor( PID_pair(-1000002,1000004), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000002,1000002)] = silly_pid_xsec_constructor( PID_pair(-2000002,1000002), 5.79460e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000002,2000002)] = silly_pid_xsec_constructor( PID_pair(-1000002,2000002), 5.79460e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000004,1000002)] = silly_pid_xsec_constructor( PID_pair(-2000004,1000002), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000002,2000004)] = silly_pid_xsec_constructor( PID_pair(-1000002,2000004), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000001,1000002)] = silly_pid_xsec_constructor( PID_pair(-1000001,1000002), 6.75142e-01);
        all_my_pid_pair_xsecs[PID_pair(-1000002,1000001)] = silly_pid_xsec_constructor( PID_pair(-1000002,1000001), 6.75142e-01);
        all_my_pid_pair_xsecs[PID_pair(-1000003,1000002)] = silly_pid_xsec_constructor( PID_pair(-1000003,1000002), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000002,1000003)] = silly_pid_xsec_constructor( PID_pair(-1000002,1000003), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000005,1000002)] = silly_pid_xsec_constructor( PID_pair(-1000005,1000002), 2.79093e-01);
        all_my_pid_pair_xsecs[PID_pair(-1000002,1000005)] = silly_pid_xsec_constructor( PID_pair(-1000002,1000005), 2.79093e-01);
        all_my_pid_pair_xsecs[PID_pair(-2000001,1000002)] = silly_pid_xsec_constructor( PID_pair(-2000001,1000002), 4.63839e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000002,2000001)] = silly_pid_xsec_constructor( PID_pair(-1000002,2000001), 4.63839e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000003,1000002)] = silly_pid_xsec_constructor( PID_pair(-2000003,1000002), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000002,2000003)] = silly_pid_xsec_constructor( PID_pair(-1000002,2000003), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000005,1000002)] = silly_pid_xsec_constructor( PID_pair(-2000005,1000002), 9.02379e-01);
        all_my_pid_pair_xsecs[PID_pair(-1000002,2000005)] = silly_pid_xsec_constructor( PID_pair(-1000002,2000005), 9.02379e-01);
        all_my_pid_pair_xsecs[PID_pair(-1000005,1000003)] = silly_pid_xsec_constructor( PID_pair(-1000005,1000003), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000003,1000005)] = silly_pid_xsec_constructor( PID_pair(-1000003,1000005), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000001,1000003)] = silly_pid_xsec_constructor( PID_pair(-2000001,1000003), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000003,2000001)] = silly_pid_xsec_constructor( PID_pair(-1000003,2000001), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000003,1000003)] = silly_pid_xsec_constructor( PID_pair(-2000003,1000003), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000003,2000003)] = silly_pid_xsec_constructor( PID_pair(-1000003,2000003), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000005,1000003)] = silly_pid_xsec_constructor( PID_pair(-2000005,1000003), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000003,2000005)] = silly_pid_xsec_constructor( PID_pair(-1000003,2000005), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000002,1000004)] = silly_pid_xsec_constructor( PID_pair(-2000002,1000004), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000004,2000002)] = silly_pid_xsec_constructor( PID_pair(-1000004,2000002), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000004,1000004)] = silly_pid_xsec_constructor( PID_pair(-2000004,1000004), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000004,2000004)] = silly_pid_xsec_constructor( PID_pair(-1000004,2000004), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000001,1000004)] = silly_pid_xsec_constructor( PID_pair(-1000001,1000004), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000004,1000001)] = silly_pid_xsec_constructor( PID_pair(-1000004,1000001), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000003,1000004)] = silly_pid_xsec_constructor( PID_pair(-1000003,1000004), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000004,1000003)] = silly_pid_xsec_constructor( PID_pair(-1000004,1000003), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000005,1000004)] = silly_pid_xsec_constructor( PID_pair(-1000005,1000004), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000004,1000005)] = silly_pid_xsec_constructor( PID_pair(-1000004,1000005), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000001,1000004)] = silly_pid_xsec_constructor( PID_pair(-2000001,1000004), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000004,2000001)] = silly_pid_xsec_constructor( PID_pair(-1000004,2000001), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000003,1000004)] = silly_pid_xsec_constructor( PID_pair(-2000003,1000004), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000004,2000003)] = silly_pid_xsec_constructor( PID_pair(-1000004,2000003), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000005,1000004)] = silly_pid_xsec_constructor( PID_pair(-2000005,1000004), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000004,2000005)] = silly_pid_xsec_constructor( PID_pair(-1000004,2000005), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000001,1000005)] = silly_pid_xsec_constructor( PID_pair(-2000001,1000005), 5.00782e-01);
        all_my_pid_pair_xsecs[PID_pair(-1000005,2000001)] = silly_pid_xsec_constructor( PID_pair(-1000005,2000001), 5.00782e-01);
        all_my_pid_pair_xsecs[PID_pair(-2000003,1000005)] = silly_pid_xsec_constructor( PID_pair(-2000003,1000005), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000005,2000003)] = silly_pid_xsec_constructor( PID_pair(-1000005,2000003), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000005,1000005)] = silly_pid_xsec_constructor( PID_pair(-2000005,1000005), 8.12020e-03);
        all_my_pid_pair_xsecs[PID_pair(-1000005,2000005)] = silly_pid_xsec_constructor( PID_pair(-1000005,2000005), 8.12020e-03);
        all_my_pid_pair_xsecs[PID_pair(-2000006,1000006)] = silly_pid_xsec_constructor( PID_pair(-2000006,1000006), 2.87405e-02);
        all_my_pid_pair_xsecs[PID_pair(-1000006,2000006)] = silly_pid_xsec_constructor( PID_pair(-1000006,2000006), 2.87405e-02);
        all_my_pid_pair_xsecs[PID_pair(-1000001,1000006)] = silly_pid_xsec_constructor( PID_pair(-1000001,1000006), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000006,1000001)] = silly_pid_xsec_constructor( PID_pair(-1000006,1000001), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000003,1000006)] = silly_pid_xsec_constructor( PID_pair(-1000003,1000006), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000006,1000003)] = silly_pid_xsec_constructor( PID_pair(-1000006,1000003), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000005,1000006)] = silly_pid_xsec_constructor( PID_pair(-1000005,1000006), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000006,1000005)] = silly_pid_xsec_constructor( PID_pair(-1000006,1000005), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000005,1000006)] = silly_pid_xsec_constructor( PID_pair(-2000005,1000006), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000006,2000005)] = silly_pid_xsec_constructor( PID_pair(-1000006,2000005), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000003,2000001)] = silly_pid_xsec_constructor( PID_pair(-2000003,2000001), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000001,2000003)] = silly_pid_xsec_constructor( PID_pair(-2000001,2000003), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000005,2000001)] = silly_pid_xsec_constructor( PID_pair(-2000005,2000001), 1.17545e-01);
        all_my_pid_pair_xsecs[PID_pair(-2000001,2000005)] = silly_pid_xsec_constructor( PID_pair(-2000001,2000005), 1.17545e-01);
        all_my_pid_pair_xsecs[PID_pair(-2000004,2000002)] = silly_pid_xsec_constructor( PID_pair(-2000004,2000002), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000002,2000004)] = silly_pid_xsec_constructor( PID_pair(-2000002,2000004), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000001,2000002)] = silly_pid_xsec_constructor( PID_pair(-1000001,2000002), 4.41063e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000002,1000001)] = silly_pid_xsec_constructor( PID_pair(-2000002,1000001), 4.41063e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000003,2000002)] = silly_pid_xsec_constructor( PID_pair(-1000003,2000002), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000002,1000003)] = silly_pid_xsec_constructor( PID_pair(-2000002,1000003), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000005,2000002)] = silly_pid_xsec_constructor( PID_pair(-1000005,2000002), 1.19048e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000002,1000005)] = silly_pid_xsec_constructor( PID_pair(-2000002,1000005), 1.19048e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000001,2000002)] = silly_pid_xsec_constructor( PID_pair(-2000001,2000002), 1.38722e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000002,2000001)] = silly_pid_xsec_constructor( PID_pair(-2000002,2000001), 1.38722e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000003,2000002)] = silly_pid_xsec_constructor( PID_pair(-2000003,2000002), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000002,2000003)] = silly_pid_xsec_constructor( PID_pair(-2000002,2000003), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000005,2000002)] = silly_pid_xsec_constructor( PID_pair(-2000005,2000002), 2.59644e-01);
        all_my_pid_pair_xsecs[PID_pair(-2000002,2000005)] = silly_pid_xsec_constructor( PID_pair(-2000002,2000005), 2.59644e-01);
        all_my_pid_pair_xsecs[PID_pair(-2000005,2000003)] = silly_pid_xsec_constructor( PID_pair(-2000005,2000003), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000003,2000005)] = silly_pid_xsec_constructor( PID_pair(-2000003,2000005), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000001,2000004)] = silly_pid_xsec_constructor( PID_pair(-1000001,2000004), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000004,1000001)] = silly_pid_xsec_constructor( PID_pair(-2000004,1000001), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000003,2000004)] = silly_pid_xsec_constructor( PID_pair(-1000003,2000004), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000004,1000003)] = silly_pid_xsec_constructor( PID_pair(-2000004,1000003), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000005,2000004)] = silly_pid_xsec_constructor( PID_pair(-1000005,2000004), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000004,1000005)] = silly_pid_xsec_constructor( PID_pair(-2000004,1000005), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000001,2000004)] = silly_pid_xsec_constructor( PID_pair(-2000001,2000004), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000004,2000001)] = silly_pid_xsec_constructor( PID_pair(-2000004,2000001), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000003,2000004)] = silly_pid_xsec_constructor( PID_pair(-2000003,2000004), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000004,2000003)] = silly_pid_xsec_constructor( PID_pair(-2000004,2000003), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000005,2000004)] = silly_pid_xsec_constructor( PID_pair(-2000005,2000004), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000004,2000005)] = silly_pid_xsec_constructor( PID_pair(-2000004,2000005), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000001,2000006)] = silly_pid_xsec_constructor( PID_pair(-1000001,2000006), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000006,1000001)] = silly_pid_xsec_constructor( PID_pair(-2000006,1000001), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000003,2000006)] = silly_pid_xsec_constructor( PID_pair(-1000003,2000006), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000006,1000003)] = silly_pid_xsec_constructor( PID_pair(-2000006,1000003), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000005,2000006)] = silly_pid_xsec_constructor( PID_pair(-1000005,2000006), 5.76595e-02);
        all_my_pid_pair_xsecs[PID_pair(-2000006,1000005)] = silly_pid_xsec_constructor( PID_pair(-2000006,1000005), 5.76595e-02);
        all_my_pid_pair_xsecs[PID_pair(-2000005,2000006)] = silly_pid_xsec_constructor( PID_pair(-2000005,2000006), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000006,2000005)] = silly_pid_xsec_constructor( PID_pair(-2000006,2000005), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000001,1000001)] = silly_pid_xsec_constructor( PID_pair(1000001,1000001), 4.03788e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000001,-1000001)] = silly_pid_xsec_constructor( PID_pair(-1000001,-1000001), 4.03788e+00);
        all_my_pid_pair_xsecs[PID_pair(1000001,1000003)] = silly_pid_xsec_constructor( PID_pair(1000001,1000003), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000003,-1000001)] = silly_pid_xsec_constructor( PID_pair(-1000003,-1000001), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000001,1000005)] = silly_pid_xsec_constructor( PID_pair(1000001,1000005), 4.90364e-01);
        all_my_pid_pair_xsecs[PID_pair(-1000005,-1000001)] = silly_pid_xsec_constructor( PID_pair(-1000005,-1000001), 4.90364e-01);
        all_my_pid_pair_xsecs[PID_pair(1000001,2000001)] = silly_pid_xsec_constructor( PID_pair(1000001,2000001), 2.79640e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000001,-1000001)] = silly_pid_xsec_constructor( PID_pair(-2000001,-1000001), 2.79640e+00);
        all_my_pid_pair_xsecs[PID_pair(1000001,2000003)] = silly_pid_xsec_constructor( PID_pair(1000001,2000003), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000003,-1000001)] = silly_pid_xsec_constructor( PID_pair(-2000003,-1000001), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000001,2000005)] = silly_pid_xsec_constructor( PID_pair(1000001,2000005), 1.02498e-01);
        all_my_pid_pair_xsecs[PID_pair(-2000005,-1000001)] = silly_pid_xsec_constructor( PID_pair(-2000005,-1000001), 1.02498e-01);
        all_my_pid_pair_xsecs[PID_pair(1000002,1000002)] = silly_pid_xsec_constructor( PID_pair(1000002,1000002), 2.01717e+01);
        all_my_pid_pair_xsecs[PID_pair(-1000002,-1000002)] = silly_pid_xsec_constructor( PID_pair(-1000002,-1000002), 2.01717e+01);
        all_my_pid_pair_xsecs[PID_pair(1000002,1000004)] = silly_pid_xsec_constructor( PID_pair(1000002,1000004), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000004,-1000002)] = silly_pid_xsec_constructor( PID_pair(-1000004,-1000002), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000002,2000002)] = silly_pid_xsec_constructor( PID_pair(1000002,2000002), 1.51834e+01);
        all_my_pid_pair_xsecs[PID_pair(-2000002,-1000002)] = silly_pid_xsec_constructor( PID_pair(-2000002,-1000002), 1.51834e+01);
        all_my_pid_pair_xsecs[PID_pair(1000002,2000004)] = silly_pid_xsec_constructor( PID_pair(1000002,2000004), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000004,-1000002)] = silly_pid_xsec_constructor( PID_pair(-2000004,-1000002), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000001,1000002)] = silly_pid_xsec_constructor( PID_pair(1000001,1000002), 3.02769e+01);
        all_my_pid_pair_xsecs[PID_pair(-1000002,-1000001)] = silly_pid_xsec_constructor( PID_pair(-1000002,-1000001), 3.02769e+01);
        all_my_pid_pair_xsecs[PID_pair(1000002,1000003)] = silly_pid_xsec_constructor( PID_pair(1000002,1000003), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000003,-1000002)] = silly_pid_xsec_constructor( PID_pair(-1000003,-1000002), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000002,1000005)] = silly_pid_xsec_constructor( PID_pair(1000002,1000005), 4.49579e-01);
        all_my_pid_pair_xsecs[PID_pair(-1000005,-1000002)] = silly_pid_xsec_constructor( PID_pair(-1000005,-1000002), 4.49579e-01);
        all_my_pid_pair_xsecs[PID_pair(1000002,2000001)] = silly_pid_xsec_constructor( PID_pair(1000002,2000001), 6.67099e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000001,-1000002)] = silly_pid_xsec_constructor( PID_pair(-2000001,-1000002), 6.67099e+00);
        all_my_pid_pair_xsecs[PID_pair(1000002,2000003)] = silly_pid_xsec_constructor( PID_pair(1000002,2000003), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000003,-1000002)] = silly_pid_xsec_constructor( PID_pair(-2000003,-1000002), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000002,2000005)] = silly_pid_xsec_constructor( PID_pair(1000002,2000005), 9.00972e-01);
        all_my_pid_pair_xsecs[PID_pair(-2000005,-1000002)] = silly_pid_xsec_constructor( PID_pair(-2000005,-1000002), 9.00972e-01);
        all_my_pid_pair_xsecs[PID_pair(1000003,1000003)] = silly_pid_xsec_constructor( PID_pair(1000003,1000003), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000003,-1000003)] = silly_pid_xsec_constructor( PID_pair(-1000003,-1000003), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000003,1000005)] = silly_pid_xsec_constructor( PID_pair(1000003,1000005), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000005,-1000003)] = silly_pid_xsec_constructor( PID_pair(-1000005,-1000003), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000003,2000001)] = silly_pid_xsec_constructor( PID_pair(1000003,2000001), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000001,-1000003)] = silly_pid_xsec_constructor( PID_pair(-2000001,-1000003), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000003,2000003)] = silly_pid_xsec_constructor( PID_pair(1000003,2000003), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000003,-1000003)] = silly_pid_xsec_constructor( PID_pair(-2000003,-1000003), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000003,2000005)] = silly_pid_xsec_constructor( PID_pair(1000003,2000005), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000005,-1000003)] = silly_pid_xsec_constructor( PID_pair(-2000005,-1000003), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000004,1000004)] = silly_pid_xsec_constructor( PID_pair(1000004,1000004), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000004,-1000004)] = silly_pid_xsec_constructor( PID_pair(-1000004,-1000004), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000004,2000002)] = silly_pid_xsec_constructor( PID_pair(1000004,2000002), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000002,-1000004)] = silly_pid_xsec_constructor( PID_pair(-2000002,-1000004), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000004,2000004)] = silly_pid_xsec_constructor( PID_pair(1000004,2000004), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000004,-1000004)] = silly_pid_xsec_constructor( PID_pair(-2000004,-1000004), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000001,1000004)] = silly_pid_xsec_constructor( PID_pair(1000001,1000004), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000004,-1000001)] = silly_pid_xsec_constructor( PID_pair(-1000004,-1000001), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000003,1000004)] = silly_pid_xsec_constructor( PID_pair(1000003,1000004), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000004,-1000003)] = silly_pid_xsec_constructor( PID_pair(-1000004,-1000003), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000004,1000005)] = silly_pid_xsec_constructor( PID_pair(1000004,1000005), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000005,-1000004)] = silly_pid_xsec_constructor( PID_pair(-1000005,-1000004), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000004,2000001)] = silly_pid_xsec_constructor( PID_pair(1000004,2000001), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000001,-1000004)] = silly_pid_xsec_constructor( PID_pair(-2000001,-1000004), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000004,2000003)] = silly_pid_xsec_constructor( PID_pair(1000004,2000003), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000003,-1000004)] = silly_pid_xsec_constructor( PID_pair(-2000003,-1000004), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000004,2000005)] = silly_pid_xsec_constructor( PID_pair(1000004,2000005), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000005,-1000004)] = silly_pid_xsec_constructor( PID_pair(-2000005,-1000004), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000005,1000005)] = silly_pid_xsec_constructor( PID_pair(1000005,1000005), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000005,-1000005)] = silly_pid_xsec_constructor( PID_pair(-1000005,-1000005), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000005,2000001)] = silly_pid_xsec_constructor( PID_pair(1000005,2000001), 1.43230e-01);
        all_my_pid_pair_xsecs[PID_pair(-2000001,-1000005)] = silly_pid_xsec_constructor( PID_pair(-2000001,-1000005), 1.43230e-01);
        all_my_pid_pair_xsecs[PID_pair(1000005,2000003)] = silly_pid_xsec_constructor( PID_pair(1000005,2000003), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000003,-1000005)] = silly_pid_xsec_constructor( PID_pair(-2000003,-1000005), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000005,2000005)] = silly_pid_xsec_constructor( PID_pair(1000005,2000005), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000005,-1000005)] = silly_pid_xsec_constructor( PID_pair(-2000005,-1000005), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000001,1000006)] = silly_pid_xsec_constructor( PID_pair(1000001,1000006), 1.31527e-01);
        all_my_pid_pair_xsecs[PID_pair(-1000006,-1000001)] = silly_pid_xsec_constructor( PID_pair(-1000006,-1000001), 1.31527e-01);
        all_my_pid_pair_xsecs[PID_pair(1000003,1000006)] = silly_pid_xsec_constructor( PID_pair(1000003,1000006), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000006,-1000003)] = silly_pid_xsec_constructor( PID_pair(-1000006,-1000003), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000005,1000006)] = silly_pid_xsec_constructor( PID_pair(1000005,1000006), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000006,-1000005)] = silly_pid_xsec_constructor( PID_pair(-1000006,-1000005), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000006,2000005)] = silly_pid_xsec_constructor( PID_pair(1000006,2000005), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000005,-1000006)] = silly_pid_xsec_constructor( PID_pair(-2000005,-1000006), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(2000001,2000001)] = silly_pid_xsec_constructor( PID_pair(2000001,2000001), 4.35961e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000001,-2000001)] = silly_pid_xsec_constructor( PID_pair(-2000001,-2000001), 4.35961e+00);
        all_my_pid_pair_xsecs[PID_pair(2000001,2000003)] = silly_pid_xsec_constructor( PID_pair(2000001,2000003), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000003,-2000001)] = silly_pid_xsec_constructor( PID_pair(-2000003,-2000001), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(2000001,2000005)] = silly_pid_xsec_constructor( PID_pair(2000001,2000005), 4.58386e-01);
        all_my_pid_pair_xsecs[PID_pair(-2000005,-2000001)] = silly_pid_xsec_constructor( PID_pair(-2000005,-2000001), 4.58386e-01);
        all_my_pid_pair_xsecs[PID_pair(2000002,2000002)] = silly_pid_xsec_constructor( PID_pair(2000002,2000002), 2.05502e+01);
        all_my_pid_pair_xsecs[PID_pair(-2000002,-2000002)] = silly_pid_xsec_constructor( PID_pair(-2000002,-2000002), 2.05502e+01);
        all_my_pid_pair_xsecs[PID_pair(2000002,2000004)] = silly_pid_xsec_constructor( PID_pair(2000002,2000004), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000004,-2000002)] = silly_pid_xsec_constructor( PID_pair(-2000004,-2000002), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000001,2000002)] = silly_pid_xsec_constructor( PID_pair(1000001,2000002), 6.37069e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000002,-1000001)] = silly_pid_xsec_constructor( PID_pair(-2000002,-1000001), 6.37069e+00);
        all_my_pid_pair_xsecs[PID_pair(1000003,2000002)] = silly_pid_xsec_constructor( PID_pair(1000003,2000002), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000002,-1000003)] = silly_pid_xsec_constructor( PID_pair(-2000002,-1000003), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000005,2000002)] = silly_pid_xsec_constructor( PID_pair(1000005,2000002), 1.04695e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000002,-1000005)] = silly_pid_xsec_constructor( PID_pair(-2000002,-1000005), 1.04695e+00);
        all_my_pid_pair_xsecs[PID_pair(2000001,2000002)] = silly_pid_xsec_constructor( PID_pair(2000001,2000002), 2.47250e+01);
        all_my_pid_pair_xsecs[PID_pair(-2000002,-2000001)] = silly_pid_xsec_constructor( PID_pair(-2000002,-2000001), 2.47250e+01);
        all_my_pid_pair_xsecs[PID_pair(2000002,2000003)] = silly_pid_xsec_constructor( PID_pair(2000002,2000003), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000003,-2000002)] = silly_pid_xsec_constructor( PID_pair(-2000003,-2000002), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(2000002,2000005)] = silly_pid_xsec_constructor( PID_pair(2000002,2000005), 4.29016e-01);
        all_my_pid_pair_xsecs[PID_pair(-2000005,-2000002)] = silly_pid_xsec_constructor( PID_pair(-2000005,-2000002), 4.29016e-01);
        all_my_pid_pair_xsecs[PID_pair(2000003,2000003)] = silly_pid_xsec_constructor( PID_pair(2000003,2000003), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000003,-2000003)] = silly_pid_xsec_constructor( PID_pair(-2000003,-2000003), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(2000003,2000005)] = silly_pid_xsec_constructor( PID_pair(2000003,2000005), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000005,-2000003)] = silly_pid_xsec_constructor( PID_pair(-2000005,-2000003), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(2000004,2000004)] = silly_pid_xsec_constructor( PID_pair(2000004,2000004), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000004,-2000004)] = silly_pid_xsec_constructor( PID_pair(-2000004,-2000004), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000001,2000004)] = silly_pid_xsec_constructor( PID_pair(1000001,2000004), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000004,-1000001)] = silly_pid_xsec_constructor( PID_pair(-2000004,-1000001), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000003,2000004)] = silly_pid_xsec_constructor( PID_pair(1000003,2000004), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000004,-1000003)] = silly_pid_xsec_constructor( PID_pair(-2000004,-1000003), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000005,2000004)] = silly_pid_xsec_constructor( PID_pair(1000005,2000004), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000004,-1000005)] = silly_pid_xsec_constructor( PID_pair(-2000004,-1000005), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(2000001,2000004)] = silly_pid_xsec_constructor( PID_pair(2000001,2000004), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000004,-2000001)] = silly_pid_xsec_constructor( PID_pair(-2000004,-2000001), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(2000003,2000004)] = silly_pid_xsec_constructor( PID_pair(2000003,2000004), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000004,-2000003)] = silly_pid_xsec_constructor( PID_pair(-2000004,-2000003), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(2000004,2000005)] = silly_pid_xsec_constructor( PID_pair(2000004,2000005), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000005,-2000004)] = silly_pid_xsec_constructor( PID_pair(-2000005,-2000004), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(2000005,2000005)] = silly_pid_xsec_constructor( PID_pair(2000005,2000005), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000005,-2000005)] = silly_pid_xsec_constructor( PID_pair(-2000005,-2000005), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000001,2000006)] = silly_pid_xsec_constructor( PID_pair(1000001,2000006), 3.02755e-03);
        all_my_pid_pair_xsecs[PID_pair(-2000006,-1000001)] = silly_pid_xsec_constructor( PID_pair(-2000006,-1000001), 3.02755e-03);
        all_my_pid_pair_xsecs[PID_pair(1000003,2000006)] = silly_pid_xsec_constructor( PID_pair(1000003,2000006), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000006,-1000003)] = silly_pid_xsec_constructor( PID_pair(-2000006,-1000003), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000005,2000006)] = silly_pid_xsec_constructor( PID_pair(1000005,2000006), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000006,-1000005)] = silly_pid_xsec_constructor( PID_pair(-2000006,-1000005), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(2000005,2000006)] = silly_pid_xsec_constructor( PID_pair(2000005,2000006), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000006,-2000005)] = silly_pid_xsec_constructor( PID_pair(-2000006,-2000005), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000001,1000022)] = silly_pid_xsec_constructor( PID_pair(1000001,1000022), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000001,1000022)] = silly_pid_xsec_constructor( PID_pair(-1000001,1000022), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000002,1000022)] = silly_pid_xsec_constructor( PID_pair(1000002,1000022), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000002,1000022)] = silly_pid_xsec_constructor( PID_pair(-1000002,1000022), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000003,1000022)] = silly_pid_xsec_constructor( PID_pair(1000003,1000022), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000003,1000022)] = silly_pid_xsec_constructor( PID_pair(-1000003,1000022), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000004,1000022)] = silly_pid_xsec_constructor( PID_pair(1000004,1000022), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000004,1000022)] = silly_pid_xsec_constructor( PID_pair(-1000004,1000022), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000005,1000022)] = silly_pid_xsec_constructor( PID_pair(1000005,1000022), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000005,1000022)] = silly_pid_xsec_constructor( PID_pair(-1000005,1000022), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000022,2000001)] = silly_pid_xsec_constructor( PID_pair(1000022,2000001), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000001,1000022)] = silly_pid_xsec_constructor( PID_pair(-2000001,1000022), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000022,2000002)] = silly_pid_xsec_constructor( PID_pair(1000022,2000002), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000002,1000022)] = silly_pid_xsec_constructor( PID_pair(-2000002,1000022), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000022,2000003)] = silly_pid_xsec_constructor( PID_pair(1000022,2000003), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000003,1000022)] = silly_pid_xsec_constructor( PID_pair(-2000003,1000022), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000022,2000004)] = silly_pid_xsec_constructor( PID_pair(1000022,2000004), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000004,1000022)] = silly_pid_xsec_constructor( PID_pair(-2000004,1000022), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000022,2000005)] = silly_pid_xsec_constructor( PID_pair(1000022,2000005), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000005,1000022)] = silly_pid_xsec_constructor( PID_pair(-2000005,1000022), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000001,1000023)] = silly_pid_xsec_constructor( PID_pair(1000001,1000023), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000001,1000023)] = silly_pid_xsec_constructor( PID_pair(-1000001,1000023), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000002,1000023)] = silly_pid_xsec_constructor( PID_pair(1000002,1000023), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000002,1000023)] = silly_pid_xsec_constructor( PID_pair(-1000002,1000023), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000003,1000023)] = silly_pid_xsec_constructor( PID_pair(1000003,1000023), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000003,1000023)] = silly_pid_xsec_constructor( PID_pair(-1000003,1000023), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000004,1000023)] = silly_pid_xsec_constructor( PID_pair(1000004,1000023), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000004,1000023)] = silly_pid_xsec_constructor( PID_pair(-1000004,1000023), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000005,1000023)] = silly_pid_xsec_constructor( PID_pair(1000005,1000023), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000005,1000023)] = silly_pid_xsec_constructor( PID_pair(-1000005,1000023), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000023,2000001)] = silly_pid_xsec_constructor( PID_pair(1000023,2000001), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000001,1000023)] = silly_pid_xsec_constructor( PID_pair(-2000001,1000023), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000023,2000002)] = silly_pid_xsec_constructor( PID_pair(1000023,2000002), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000002,1000023)] = silly_pid_xsec_constructor( PID_pair(-2000002,1000023), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000023,2000003)] = silly_pid_xsec_constructor( PID_pair(1000023,2000003), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000003,1000023)] = silly_pid_xsec_constructor( PID_pair(-2000003,1000023), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000023,2000004)] = silly_pid_xsec_constructor( PID_pair(1000023,2000004), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000004,1000023)] = silly_pid_xsec_constructor( PID_pair(-2000004,1000023), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000023,2000005)] = silly_pid_xsec_constructor( PID_pair(1000023,2000005), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000005,1000023)] = silly_pid_xsec_constructor( PID_pair(-2000005,1000023), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000001,1000025)] = silly_pid_xsec_constructor( PID_pair(1000001,1000025), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000001,1000025)] = silly_pid_xsec_constructor( PID_pair(-1000001,1000025), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000002,1000025)] = silly_pid_xsec_constructor( PID_pair(1000002,1000025), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000002,1000025)] = silly_pid_xsec_constructor( PID_pair(-1000002,1000025), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000003,1000025)] = silly_pid_xsec_constructor( PID_pair(1000003,1000025), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000003,1000025)] = silly_pid_xsec_constructor( PID_pair(-1000003,1000025), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000004,1000025)] = silly_pid_xsec_constructor( PID_pair(1000004,1000025), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000004,1000025)] = silly_pid_xsec_constructor( PID_pair(-1000004,1000025), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000005,1000025)] = silly_pid_xsec_constructor( PID_pair(1000005,1000025), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000005,1000025)] = silly_pid_xsec_constructor( PID_pair(-1000005,1000025), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000025,2000001)] = silly_pid_xsec_constructor( PID_pair(1000025,2000001), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000001,1000025)] = silly_pid_xsec_constructor( PID_pair(-2000001,1000025), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000025,2000002)] = silly_pid_xsec_constructor( PID_pair(1000025,2000002), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000002,1000025)] = silly_pid_xsec_constructor( PID_pair(-2000002,1000025), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000025,2000003)] = silly_pid_xsec_constructor( PID_pair(1000025,2000003), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000003,1000025)] = silly_pid_xsec_constructor( PID_pair(-2000003,1000025), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000025,2000004)] = silly_pid_xsec_constructor( PID_pair(1000025,2000004), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000004,1000025)] = silly_pid_xsec_constructor( PID_pair(-2000004,1000025), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000025,2000005)] = silly_pid_xsec_constructor( PID_pair(1000025,2000005), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000005,1000025)] = silly_pid_xsec_constructor( PID_pair(-2000005,1000025), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000001,1000035)] = silly_pid_xsec_constructor( PID_pair(1000001,1000035), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000001,1000035)] = silly_pid_xsec_constructor( PID_pair(-1000001,1000035), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000002,1000035)] = silly_pid_xsec_constructor( PID_pair(1000002,1000035), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000002,1000035)] = silly_pid_xsec_constructor( PID_pair(-1000002,1000035), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000003,1000035)] = silly_pid_xsec_constructor( PID_pair(1000003,1000035), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000003,1000035)] = silly_pid_xsec_constructor( PID_pair(-1000003,1000035), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000004,1000035)] = silly_pid_xsec_constructor( PID_pair(1000004,1000035), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000004,1000035)] = silly_pid_xsec_constructor( PID_pair(-1000004,1000035), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000005,1000035)] = silly_pid_xsec_constructor( PID_pair(1000005,1000035), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000005,1000035)] = silly_pid_xsec_constructor( PID_pair(-1000005,1000035), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000035,2000001)] = silly_pid_xsec_constructor( PID_pair(1000035,2000001), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000001,1000035)] = silly_pid_xsec_constructor( PID_pair(-2000001,1000035), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000035,2000002)] = silly_pid_xsec_constructor( PID_pair(1000035,2000002), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000002,1000035)] = silly_pid_xsec_constructor( PID_pair(-2000002,1000035), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000035,2000003)] = silly_pid_xsec_constructor( PID_pair(1000035,2000003), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000003,1000035)] = silly_pid_xsec_constructor( PID_pair(-2000003,1000035), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000035,2000004)] = silly_pid_xsec_constructor( PID_pair(1000035,2000004), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000004,1000035)] = silly_pid_xsec_constructor( PID_pair(-2000004,1000035), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000035,2000005)] = silly_pid_xsec_constructor( PID_pair(1000035,2000005), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000005,1000035)] = silly_pid_xsec_constructor( PID_pair(-2000005,1000035), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000001,1000024)] = silly_pid_xsec_constructor( PID_pair(1000001,1000024), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000024,-1000001)] = silly_pid_xsec_constructor( PID_pair(-1000024,-1000001), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000024,1000002)] = silly_pid_xsec_constructor( PID_pair(-1000024,1000002), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000002,1000024)] = silly_pid_xsec_constructor( PID_pair(-1000002,1000024), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000003,1000024)] = silly_pid_xsec_constructor( PID_pair(1000003,1000024), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000024,-1000003)] = silly_pid_xsec_constructor( PID_pair(-1000024,-1000003), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000024,1000004)] = silly_pid_xsec_constructor( PID_pair(-1000024,1000004), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000004,1000024)] = silly_pid_xsec_constructor( PID_pair(-1000004,1000024), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000005,1000024)] = silly_pid_xsec_constructor( PID_pair(1000005,1000024), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000024,-1000005)] = silly_pid_xsec_constructor( PID_pair(-1000024,-1000005), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000024,1000006)] = silly_pid_xsec_constructor( PID_pair(-1000024,1000006), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000006,1000024)] = silly_pid_xsec_constructor( PID_pair(-1000006,1000024), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000024,2000005)] = silly_pid_xsec_constructor( PID_pair(1000024,2000005), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000005,-1000024)] = silly_pid_xsec_constructor( PID_pair(-2000005,-1000024), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000024,2000006)] = silly_pid_xsec_constructor( PID_pair(-1000024,2000006), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000006,1000024)] = silly_pid_xsec_constructor( PID_pair(-2000006,1000024), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000001,1000037)] = silly_pid_xsec_constructor( PID_pair(1000001,1000037), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000037,-1000001)] = silly_pid_xsec_constructor( PID_pair(-1000037,-1000001), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000037,1000002)] = silly_pid_xsec_constructor( PID_pair(-1000037,1000002), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000002,1000037)] = silly_pid_xsec_constructor( PID_pair(-1000002,1000037), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000003,1000037)] = silly_pid_xsec_constructor( PID_pair(1000003,1000037), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000037,-1000003)] = silly_pid_xsec_constructor( PID_pair(-1000037,-1000003), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000037,1000004)] = silly_pid_xsec_constructor( PID_pair(-1000037,1000004), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000004,1000037)] = silly_pid_xsec_constructor( PID_pair(-1000004,1000037), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000005,1000037)] = silly_pid_xsec_constructor( PID_pair(1000005,1000037), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000037,-1000005)] = silly_pid_xsec_constructor( PID_pair(-1000037,-1000005), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000037,1000006)] = silly_pid_xsec_constructor( PID_pair(-1000037,1000006), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000006,1000037)] = silly_pid_xsec_constructor( PID_pair(-1000006,1000037), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000037,2000005)] = silly_pid_xsec_constructor( PID_pair(1000037,2000005), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000005,-1000037)] = silly_pid_xsec_constructor( PID_pair(-2000005,-1000037), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000037,2000006)] = silly_pid_xsec_constructor( PID_pair(-1000037,2000006), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000006,1000037)] = silly_pid_xsec_constructor( PID_pair(-2000006,1000037), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000022,1000022)] = silly_pid_xsec_constructor( PID_pair(1000022,1000022), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000022,1000023)] = silly_pid_xsec_constructor( PID_pair(1000022,1000023), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000023,1000023)] = silly_pid_xsec_constructor( PID_pair(1000023,1000023), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000022,1000025)] = silly_pid_xsec_constructor( PID_pair(1000022,1000025), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000023,1000025)] = silly_pid_xsec_constructor( PID_pair(1000023,1000025), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000025,1000025)] = silly_pid_xsec_constructor( PID_pair(1000025,1000025), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000022,1000035)] = silly_pid_xsec_constructor( PID_pair(1000022,1000035), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000023,1000035)] = silly_pid_xsec_constructor( PID_pair(1000023,1000035), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000025,1000035)] = silly_pid_xsec_constructor( PID_pair(1000025,1000035), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000035,1000035)] = silly_pid_xsec_constructor( PID_pair(1000035,1000035), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000022,1000024)] = silly_pid_xsec_constructor( PID_pair(1000022,1000024), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000024,1000022)] = silly_pid_xsec_constructor( PID_pair(-1000024,1000022), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000022,1000037)] = silly_pid_xsec_constructor( PID_pair(1000022,1000037), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000037,1000022)] = silly_pid_xsec_constructor( PID_pair(-1000037,1000022), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000023,1000024)] = silly_pid_xsec_constructor( PID_pair(1000023,1000024), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000024,1000023)] = silly_pid_xsec_constructor( PID_pair(-1000024,1000023), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000023,1000037)] = silly_pid_xsec_constructor( PID_pair(1000023,1000037), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000037,1000023)] = silly_pid_xsec_constructor( PID_pair(-1000037,1000023), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000024,1000025)] = silly_pid_xsec_constructor( PID_pair(1000024,1000025), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000024,1000025)] = silly_pid_xsec_constructor( PID_pair(-1000024,1000025), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000025,1000037)] = silly_pid_xsec_constructor( PID_pair(1000025,1000037), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000037,1000025)] = silly_pid_xsec_constructor( PID_pair(-1000037,1000025), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000024,1000035)] = silly_pid_xsec_constructor( PID_pair(1000024,1000035), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000024,1000035)] = silly_pid_xsec_constructor( PID_pair(-1000024,1000035), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000035,1000037)] = silly_pid_xsec_constructor( PID_pair(1000035,1000037), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000037,1000035)] = silly_pid_xsec_constructor( PID_pair(-1000037,1000035), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000024,1000024)] = silly_pid_xsec_constructor( PID_pair(-1000024,1000024), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000037,1000024)] = silly_pid_xsec_constructor( PID_pair(-1000037,1000024), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000024,1000037)] = silly_pid_xsec_constructor( PID_pair(-1000024,1000037), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000037,1000037)] = silly_pid_xsec_constructor( PID_pair(-1000037,1000037), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000021,1000022)] = silly_pid_xsec_constructor( PID_pair(1000021,1000022), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000021,1000023)] = silly_pid_xsec_constructor( PID_pair(1000021,1000023), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000021,1000025)] = silly_pid_xsec_constructor( PID_pair(1000021,1000025), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000021,1000035)] = silly_pid_xsec_constructor( PID_pair(1000021,1000035), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000021,1000024)] = silly_pid_xsec_constructor( PID_pair(1000021,1000024), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000024,1000021)] = silly_pid_xsec_constructor( PID_pair(-1000024,1000021), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(1000021,1000037)] = silly_pid_xsec_constructor( PID_pair(1000021,1000037), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000037,1000021)] = silly_pid_xsec_constructor( PID_pair(-1000037,1000021), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000011,1000011)] = silly_pid_xsec_constructor( PID_pair(-1000011,1000011), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000012,1000012)] = silly_pid_xsec_constructor( PID_pair(-1000012,1000012), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000011,1000012)] = silly_pid_xsec_constructor( PID_pair(-1000011,1000012), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000012,1000011)] = silly_pid_xsec_constructor( PID_pair(-1000012,1000011), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000013,1000013)] = silly_pid_xsec_constructor( PID_pair(-1000013,1000013), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000014,1000014)] = silly_pid_xsec_constructor( PID_pair(-1000014,1000014), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000013,1000014)] = silly_pid_xsec_constructor( PID_pair(-1000013,1000014), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000014,1000013)] = silly_pid_xsec_constructor( PID_pair(-1000014,1000013), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000015,1000015)] = silly_pid_xsec_constructor( PID_pair(-1000015,1000015), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000015,1000015)] = silly_pid_xsec_constructor( PID_pair(-2000015,1000015), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000015,2000015)] = silly_pid_xsec_constructor( PID_pair(-1000015,2000015), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000016,1000016)] = silly_pid_xsec_constructor( PID_pair(-1000016,1000016), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000015,1000016)] = silly_pid_xsec_constructor( PID_pair(-1000015,1000016), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000016,1000015)] = silly_pid_xsec_constructor( PID_pair(-1000016,1000015), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000015,1000016)] = silly_pid_xsec_constructor( PID_pair(-2000015,1000016), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-1000016,2000015)] = silly_pid_xsec_constructor( PID_pair(-1000016,2000015), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000011,2000011)] = silly_pid_xsec_constructor( PID_pair(-2000011,2000011), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000013,2000013)] = silly_pid_xsec_constructor( PID_pair(-2000013,2000013), 0.00000e+00);
        all_my_pid_pair_xsecs[PID_pair(-2000015,2000015)] = silly_pid_xsec_constructor( PID_pair(-2000015,2000015), 0.00000e+00);
      }

      if(*Loop::iteration == COLLIDER_INIT)
      {
        result.clear();
      }

      if(*Loop::iteration == XSEC_CALCULATION)
      {
        for (const PID_pair& pid_pair : *Dep::ActivePIDPairs)
        {
          #ifdef COLLIDERBIT_DEBUG
            cout << DEBUG_PREFIX << "getPIDPairCrossSectionsMap_testing: " << "Looking up xsec for [" << pid_pair.pid1() << "," << pid_pair.pid2() << "]." << endl;
          #endif
          result[pid_pair] = all_my_pid_pair_xsecs.at(pid_pair);
        }
      } // end iteration

    }



    /// Get a map between Pythia process codes and cross-sections
    void getProcessCrossSectionsMap(map_int_process_xsec& result)
    {
      using namespace Pipes::getProcessCrossSectionsMap;

      // Use a static variable to communicate the result calculated on thread 0 during 
      // iteration XSEC_CALCULATION to all threads during iteration START_SUBPROCESS
      static map_int_process_xsec shared_result;

      const static bool set_missing_cross_sections_to_zero = runOptions->getValueOrDef<bool>(false, "set_missing_cross_sections_to_zero");

      // Only thread 0
      if(*Loop::iteration == COLLIDER_INIT)
      {
        shared_result.clear();
      }

      // All threads
      if(*Loop::iteration == COLLIDER_INIT_OMP)
      {
        result.clear();
      }

      // Only thread 0
      if(*Loop::iteration == XSEC_CALCULATION)
      {
        // Loop over all active processes and construct the cross-section map (shared_result)
        for (size_t i = 0; i != Dep::ActiveProcessCodes->size(); ++i)
        {
          // Get process code
          int proc_code = Dep::ActiveProcessCodes->at(i);

          // Construct a process_xsec_container instance to be stored in the shared_result map
          process_xsec_container proc_xs;
          proc_xs.set_process_code(proc_code);

          // Get iterator bounds (as a pair) over the multimap entries that match the key proc_code
          auto mm_proc2pid_range = Dep::ActiveProcessCodeToPIDPairsMap->equal_range(proc_code);

          // Loop over these elements in the multimap
          for (auto mm_it = mm_proc2pid_range.first; mm_it != mm_proc2pid_range.second; ++mm_it)
          {
            const PID_pair& pids = mm_it->second;

            // Obtain the cross-section from the PID pair via the PIDPairCrossSectionsMap (map_PID_pair_PID_pair_xsec) dependency
            PID_pair_xsec_container pids_xs;
            map_PID_pair_PID_pair_xsec::const_iterator iter = Dep::PIDPairCrossSectionsMap->find(pids);
            if (iter != Dep::PIDPairCrossSectionsMap->end())
            {
              pids_xs = iter->second;
            }
            else
            {
              if(set_missing_cross_sections_to_zero)
              {
                pids_xs.set_xsec(0.0, 0.0);
              }
              else
              {
                std::stringstream errmsg_ss;
                errmsg_ss << "No cross-section provided for PID pair [" << pids.pid1() << "," << pids.pid2() <<"]. ";
                ColliderBit_error().raise(LOCAL_INFO, errmsg_ss.str());
              }
            }

            // Make sure the trust_level of the process_xsec_container proc_xs is set to 
            // the lowest trust_level of the contributing PID_pair_xsec_containers
            cerr << "DEBUG: pids_xs.trust_level() = " << pids_xs.trust_level() << ",  pids_xs.pid_pair().str() = " << pids_xs.pid_pair().str() << endl;
            if (pids_xs.trust_level() < proc_xs.trust_level()) { proc_xs.set_trust_level(pids_xs.trust_level()); }

            // Accumulate result in the process_xsec_container proc_xs
            proc_xs.sum_xsecs(pids_xs.xsec(), pids_xs.xsec_err());
            proc_xs.register_related_pid_pair(pids);


            // Check if the current PID pair is related to any other process_codes,
            // using the multimap returned by all_PID_pairs_to_process_codes().
            // If yes, check that these processes are among the active processes
            // and register them in the proc_xs instance as processes sharing the cross-section

            // Get iterator bounds (as a pair) over the multimap entries that match the key pids
            auto mm_pid2proc_range = all_PID_pairs_to_process_codes().equal_range(pids);

            // Loop over these elements in the multimap
            for (auto mm_it = mm_pid2proc_range.first; mm_it != mm_pid2proc_range.second; ++mm_it)
            {
              // Get other process code
              int other_proc_code = mm_it->second;

              // Don't run around in circles...
              if(other_proc_code == proc_code) continue;

              // Check that other_proc_code is itself in one of the active processes, i.e. listed in Dep::ActiveProcessCodes
              if(std::find(Dep::ActiveProcessCodes->begin(), Dep::ActiveProcessCodes->end(), other_proc_code) != Dep::ActiveProcessCodes->end())  
              {
                // Add other_proc_code to the list of processes that share cross-section with proc_code
                // (The process_xsec_container class makes sure we only register each process once.)
                proc_xs.register_process_sharing_xsec(other_proc_code);
              }
              else
              {
                std::stringstream errmsg_ss;
                errmsg_ss << "For correct cross-section scaling of collider process " << proc_code;
                errmsg_ss << ", process " << other_proc_code << " must also be activated. Please check your collider settings.";
                ColliderBit_error().raise(LOCAL_INFO, errmsg_ss.str());
              }
            }
          }

          // Construct info string of the form "ProcessCode:<proc_code>"
          std::stringstream info_ss;
          info_ss << "ProcessCode:" << proc_code;
          proc_xs.set_info_string(info_ss.str());

          // Store proc_xs in the shared_result map
          shared_result[proc_code] = proc_xs;
        }

        // Let thread 0 return the correct result already after iteration XSEC_CALCULATION
        result = shared_result;
      }


      // All threads
      if (*Loop::iteration == START_SUBPROCESS)
      {
        // All threads read the result from shared_result
        result = shared_result;
      }

    }


    /// Compute a cross-section from Monte Carlo
    void getEvGenCrossSection(MC_xsec_container& result)
    {
      using namespace Pipes::getEvGenCrossSection;

      static bool first = true;
      if (first)
      {
        event_weight_flags["total_cross_section_from_MC"] = true;
        first = false;
      }

      // Don't bother if there are no analyses that will use this.
      if (Dep::RunMC->analyses.empty()) return;

      // Reset the xsec objects on all threads
      if (*Loop::iteration == COLLIDER_INIT_OMP)
      {
        result.reset();
      }

      // If we are in the main event loop, count the event towards cross-section normalisation on this thread
      if (*Loop::iteration >= 0)
      {
        result.log_event();
      }

      // Extract the xsecs from the MC on each thread
      if (*Loop::iteration == END_SUBPROCESS && Dep::RunMC->event_generation_began)
      {
        if (not Dep::RunMC->exceeded_maxFailedEvents)
        {
          const double xs_fb = (*Dep::HardScatteringSim)->xsec_fb();
          const double xserr_fb = (*Dep::HardScatteringSim)->xsecErr_fb();
          result.set_xsec(xs_fb, xserr_fb);
          #ifdef COLLIDERBIT_DEBUG
            cout << DEBUG_PREFIX << "xs_fb = " << xs_fb << " +/- " << xserr_fb << endl;
          #endif


          //
          // Debug code to print process cross-sections:
          //

          // #ifdef COLLIDERBIT_DEBUG

          //   std::vector<PID_pair> all_pid_pairs;
          //   std::map<int,int> pcode_counter;

          //   for (const std::pair<int,PID_pair>& elem : all_process_codes_to_PID_pairs)
          //   {
          //     int pcode = elem.first;
          //     const PID_pair& pids = elem.second;

          //     double LO_proc_xsec = (*Dep::HardScatteringSim)->xsec_fb(pcode);

          //     cout << std::fixed << std::setprecision(7);
          //     cout << DEBUG_PREFIX << "All xsecs:  " << pcode << ", [" 
          //                                            << pids.pid1() << "," << pids.pid2() << "], "
          //                                            << std::scientific << std::setprecision(5)
          //                                            << LO_proc_xsec << endl;

          //     // Get list of all unique PID_pairs
          //     if (std::find(all_pid_pairs.begin(), all_pid_pairs.end(), pids) == all_pid_pairs.end())
          //     {
          //       all_pid_pairs.push_back( PID_pair(pids) );
          //     }

          //     // Count pcode
          //     pcode_counter[pcode]++;
          //   }

          //   // Loop over PID_pairs
          //   for (const PID_pair& pids : all_pid_pairs)
          //   {
          //     double pids_xsec_val = 0.0;

          //     // double sgn_pid1 = double(pids.pid1()) / double(abs(pids.pid1()));
          //     // double sgn_pid2 = double(pids.pid2()) / double(abs(pids.pid2()));

          //     PID_pair cc_pid_pair = pids.cc_pid_pair();

          //     auto mm_pid2proc_range = all_PID_pairs_to_process_codes().equal_range(pids);

          //     // Loop over these elements in the multimap
          //     for (auto mm_it = mm_pid2proc_range.first; mm_it != mm_pid2proc_range.second; ++mm_it)
          //     {
          //       int pcode = mm_it->second;

          //       double factor = 1.0 / pcode_counter.at(pcode);

          //       // if ((!pids.is_antiparticle_pair()) && (sgn_pid1 * sgn_pid2 < 0))
          //       // {
          //       //   // factor = factor * 2.0;
          //       //   if (std::find(all_pid_pairs.begin(), all_pid_pairs.end(), cc_pid_pair) != all_pid_pairs.end() )
          //       //   {
          //       //     factor = factor * 2.0;

          //       //     if (pcode == 1491)
          //       //     {
          //       //       cout << "DEBUG: pcode==1491: factor adjusted by 2: " << factor << endl;
          //       //     }

          //       //   }                
          //       // }

          //       pids_xsec_val += (*Dep::HardScatteringSim)->xsec_fb(pcode) * factor;
          //     }

          //     cout << std::fixed << std::setprecision(7);
          //     cout << DEBUG_PREFIX << "PIDs xsecs:  " << "[" 
          //                                            << pids.pid1() << "," << pids.pid2() << "]: "
          //                                            << std::scientific << std::setprecision(5)
          //                                            << pids_xsec_val << endl;
          //   }

          // #endif

        }
      }

      // Gather the xsecs from all threads into one
      if (*Loop::iteration == COLLIDER_FINALIZE)
      {
        result.gather_xsecs();
      }

    }

    /// Return MC_xsec_container as the base xsec_container
    void getEvGenCrossSection_as_base(xsec_container& result)
    {
      using namespace Pipes::getEvGenCrossSection_as_base;
      result = *Dep::TotalEvGenCrossSection;
    }


    /// Get a cross-section from NLL-FAST
    void getNLLFastCrossSection(xsec_container& result)
    {
      using namespace Pipes::getNLLFastCrossSection;

      // Use a static variable to communicate the result calculated on thread 0 during 
      // iteration XSEC_CALCULATION to all threads during iteration START_SUBPROCESS
      static xsec_container shared_result;

      // Don't bother if there are no analyses that will use this.
      if (Dep::RunMC->analyses.empty()) return;

      // Only thread 0
      if(*Loop::iteration == COLLIDER_INIT) shared_result.reset();
      
      // All threads
      if (*Loop::iteration == COLLIDER_INIT_OMP) result.reset();

      // Set the xsec and its error.
      // Only thread 0
      if (*Loop::iteration == XSEC_CALCULATION)
      {
        double xs_fb = 0.1;             // replace with xsec from NLL-Fast
        double xserr_fb = 0.1 * xs_fb;  // or whatever
        shared_result.set_xsec(xs_fb, xserr_fb);

        // Let thread 0 return the correct result already after iteration XSEC_CALCULATION
        result = shared_result;
      }

      // All threads
      if (*Loop::iteration == START_SUBPROCESS)
      {
        // All threads copy the result from shared_result
        result = shared_result;
      }

    }


    /// A helper function to check the YAML options for getYAMLCrossSection and getYAMLCrossSection_SLHA
    bool checkOptions_getYAMLCrossSection(const Options& runOptions, const str calling_function, std::pair<str,str>& xsec_pnames, str& input_unit, bool& input_fractional_uncert, str& errmsg)
    {

      errmsg = "";

      str valid_option_pairs_msg;
      valid_option_pairs_msg  = "This function requires one of the following pairs of YAML options:\n";
      valid_option_pairs_msg += "  cross_section_fb, cross_section_uncert_fb\n";
      valid_option_pairs_msg += "  cross_section_fb, cross_section_fractional_uncert\n";
      valid_option_pairs_msg += "  cross_section_pb, cross_section_uncert_pb\n";
      valid_option_pairs_msg += "  cross_section_pb, cross_section_fractional_uncert\n";

      // Check that enough options are provided
      if (runOptions.getNames().size() < 2)
      {
        errmsg = "Not enough YAML options provided for function " + calling_function + ".\n";
        errmsg += valid_option_pairs_msg;
        return false;
      }

      // Check that a valid combination of options is provided, 
      // and set variable references accordingly
      if ((runOptions.hasKey("cross_section_fb")) && (runOptions.hasKey("cross_section_uncert_fb")))
      {
        xsec_pnames.first = "cross_section_fb";
        xsec_pnames.second = "cross_section_uncert_fb";
        input_unit = "fb";
        input_fractional_uncert = false;
      }
      else if ((runOptions.hasKey("cross_section_fb")) && (runOptions.hasKey("cross_section_fractional_uncert")))
      {
        xsec_pnames.first = "cross_section_fb";
        xsec_pnames.second = "cross_section_fractional_uncert";
        input_unit = "fb";
        input_fractional_uncert = true;
      }
      else if ((runOptions.hasKey("cross_section_pb")) && (runOptions.hasKey("cross_section_uncert_pb")))
      {
        xsec_pnames.first = "cross_section_pb";
        xsec_pnames.second = "cross_section_uncert_pb";
        input_unit = "pb";
        input_fractional_uncert = false;
      }
      else if ((runOptions.hasKey("cross_section_pb")) && (runOptions.hasKey("cross_section_fractional_uncert")))
      {
        xsec_pnames.first = "cross_section_pb";
        xsec_pnames.second = "cross_section_fractional_uncert";
        input_unit = "pb";
        input_fractional_uncert = true;
      }
      else
      {
        errmsg =  "Unknown combination of options provided for function " + calling_function + ".\n";
        errmsg += valid_option_pairs_msg;
        return false;
      }

      return true;
    }


    /// A function that reads the total cross-section from the input file, but builds up the number of events from the event loop
    void getYAMLCrossSection(xsec_container& result)
    {
      using namespace Pipes::getYAMLCrossSection;

      // Use a static variable to communicate the result calculated on thread 0 during 
      // iteration XSEC_CALCULATION to all threads during iteration START_SUBPROCESS
      static xsec_container shared_result;

      // Don't bother if there are no analyses that will use this.
      if (Dep::RunMC->analyses.empty()) return;

      static std::pair<str,str> xsec_pnames;
      static str input_unit; 
      static bool input_fractional_uncert = false;

      static bool first = true;
      if (*Loop::iteration == BASE_INIT)
      {

        // Check that the required YAML options are provided
        if (first)
        {
          str errmsg;
          bool valid_options = checkOptions_getYAMLCrossSection(*runOptions, "getYAMLCrossSection", xsec_pnames, input_unit, input_fractional_uncert, errmsg);
          if (!valid_options)
          {
            ColliderBit_error().raise(LOCAL_INFO, errmsg);
          }
          first = false;
        }
      }

      // Retrieve the total cross-section and cross-section error
      const static double input_xsec = runOptions->getValue<double>(xsec_pnames.first);
      const static double input_xsec_uncert = runOptions->getValue<double>(xsec_pnames.second);

      // Only thread 0
      if(*Loop::iteration == COLLIDER_INIT) shared_result.reset();
      
      // All threads
      if (*Loop::iteration == COLLIDER_INIT_OMP) result.reset();

      // Set the xsec and its error
      // Only thread 0
      if (*Loop::iteration == XSEC_CALCULATION)
      {
        std::pair<double,double> temp = convert_xsecs_to_fb(input_xsec, input_xsec_uncert, input_unit, input_fractional_uncert);
        double xsec_fb = temp.first;
        double xsec_uncert_fb = temp.second;
        shared_result.set_xsec(xsec_fb, xsec_uncert_fb);

        // Let thread 0 return the correct result already after iteration XSEC_CALCULATION
        result = shared_result;
      }

      // All threads
      if (*Loop::iteration == START_SUBPROCESS)
      {
        // All threads copy the result from shared_result
        result = shared_result;
      }

    }


    /// A function that reads a list of (SLHA file, total cross-section) pairs from the input YAML file
    void getYAMLCrossSection_SLHA(xsec_container& result)
    {
      using namespace Pipes::getYAMLCrossSection_SLHA;

      // Use a static variable to communicate the result calculated on thread 0 during 
      // iteration XSEC_CALCULATION to all threads during iteration START_SUBPROCESS
      static xsec_container shared_result;

      // Don't bother if there are no analyses that will use this.
      if (Dep::RunMC->analyses.empty()) return;

      static std::pair<str,str> xsec_pnames;
      static str input_unit; 
      static bool input_fractional_uncert = false;

      static bool first = true;
      if (*Loop::iteration == BASE_INIT)
      {
        // Check that the required YAML options are provided
        if (first)
        {
          str errmsg;
          bool valid_options = checkOptions_getYAMLCrossSection(*runOptions, "getYAMLCrossSection_SLHA", xsec_pnames, input_unit, input_fractional_uncert, errmsg);
          if (!valid_options)
          {
            ColliderBit_error().raise(LOCAL_INFO, errmsg);
          }
          first = false;
        }
      }

      // Get the filename, look for it in the xsec and uncertainty lists
      const static YAML::Node colNode_xsec = runOptions->getValue<YAML::Node>(xsec_pnames.first);
      const static Options colOptions_xsec(colNode_xsec);
      const static YAML::Node colNode_uncert = runOptions->getValue<YAML::Node>(xsec_pnames.second);
      const static Options colOptions_uncert(colNode_uncert);
      static str filename;

      if (*Loop::iteration == BASE_INIT)
      {
        // Update the SLHA filename
        filename = Dep::SLHAFileNameAndContent->first;

        // Look for the filename in the xsec lists
        if (!colOptions_xsec.hasKey(filename)) piped_invalid_point.request(str("No cross-section found for SLHA file ").append(filename));
        if (!colOptions_uncert.hasKey(filename)) piped_invalid_point.request(str("No fractional cross-section uncertainty found for SLHA file ").append(filename));
      }

      // Only thread 0
      if(*Loop::iteration == COLLIDER_INIT) shared_result.reset();
      
      // All threads
      if (*Loop::iteration == COLLIDER_INIT_OMP) result.reset();

      // Set the xsec and its error
      if (*Loop::iteration == XSEC_CALCULATION)
      {
        double input_xsec = colOptions_xsec.getValue<double>(filename);
        double input_xsec_uncert = colOptions_uncert.getValue<double>(filename);

        std::pair<double,double> temp = convert_xsecs_to_fb(input_xsec, input_xsec_uncert, input_unit, input_fractional_uncert);
        double xsec_fb = temp.first;
        double xsec_uncert_fb = temp.second;
        shared_result.set_xsec(xsec_fb, xsec_uncert_fb);

        // Let thread 0 return the correct result already after iteration XSEC_CALCULATION
        result = shared_result;
      }

      // All threads
      if (*Loop::iteration == START_SUBPROCESS)
      {
        // All threads copy the result from shared_result
        result = shared_result;
      }

    }  // end getYAMLxsec_SLHA



    /// A function that assigns a total cross-sections directly from the scan parameters
    /// (for models CB_SLHA_simpmod_scan_model and CB_SLHA_scan_model)
    void getYAMLCrossSection_param(xsec_container& result)
    {
      using namespace Pipes::getYAMLCrossSection_param;

      // Use a static variable to communicate the result calculated on thread 0 during 
      // iteration XSEC_CALCULATION to all threads during iteration START_SUBPROCESS
      static xsec_container shared_result;

      // Don't bother if there are no analyses that will use this.
      if (Dep::RunMC->analyses.empty()) return;

      static std::vector<str> pnames;
      static std::pair<str,str> xsec_pnames;

      static str input_unit; 
      static bool input_fractional_uncert = false;

      static bool first = true;
      if (*Loop::iteration == BASE_INIT)
      {

        if (first)
        {

          // Get all parameter names
          for (const auto& parname_parptr_pair : Param)
          {
            pnames.push_back(parname_parptr_pair.first);
          }

          // Determine the correct combination of parameters
          if ((std::find(pnames.begin(), pnames.end(), "cross_section_fb") != pnames.end()) 
               && (std::find(pnames.begin(), pnames.end(), "cross_section_uncert_fb") != pnames.end()))
          {
            xsec_pnames.first = "cross_section_fb";
            xsec_pnames.second = "cross_section_uncert_fb";
            input_unit = "fb";
            input_fractional_uncert = false;
          }
          else if ((std::find(pnames.begin(), pnames.end(), "cross_section_fb") != pnames.end()) 
                    && (std::find(pnames.begin(), pnames.end(), "cross_section_fractional_uncert") != pnames.end()))
          {
            xsec_pnames.first = "cross_section_fb";
            xsec_pnames.second = "cross_section_fractional_uncert";
            input_unit = "fb";
            input_fractional_uncert = true;
          }
          else if ((std::find(pnames.begin(), pnames.end(), "cross_section_pb") != pnames.end()) 
                    && (std::find(pnames.begin(), pnames.end(), "cross_section_uncert_pb") != pnames.end()))
          {
            xsec_pnames.first = "cross_section_pb";
            xsec_pnames.second = "cross_section_uncert_pb";
            input_unit = "pb";
            input_fractional_uncert = false;
          }
          else if ((std::find(pnames.begin(), pnames.end(), "cross_section_pb") != pnames.end()) 
                    && (std::find(pnames.begin(), pnames.end(), "cross_section_fractional_uncert") != pnames.end()))
          {
            xsec_pnames.first = "cross_section_pb";
            xsec_pnames.second = "cross_section_fractional_uncert";
            input_unit = "pb";
            input_fractional_uncert = true;
          }
          else
          {
            std::stringstream errmsg_ss;
            errmsg_ss << "Unknown combination of parameters for function getYAMLCrossSection_param." << endl;
            errmsg_ss << "Needs one of the following sets of parameter names:" << endl;
            errmsg_ss << "  cross_section_fb, cross_section_uncert_fb" << endl;
            errmsg_ss << "  cross_section_fb, cross_section_fractional_uncert" << endl;
            errmsg_ss << "  cross_section_pb, cross_section_uncert_pb" << endl;
            errmsg_ss << "  cross_section_pb, cross_section_fractional_uncert" << endl;
            ColliderBit_error().raise(LOCAL_INFO, errmsg_ss.str());
          }

          first = false;
        }
      }

      // Only thread 0
      if(*Loop::iteration == COLLIDER_INIT) shared_result.reset();
      
      // All threads
      if (*Loop::iteration == COLLIDER_INIT_OMP) result.reset();

      // Set the xsec and its error
      // Only thread 0
      if (*Loop::iteration == XSEC_CALCULATION)
      {
        double input_xsec = *Param.at(xsec_pnames.first);
        double input_xsec_uncert = *Param.at(xsec_pnames.second); 

        std::pair<double,double> temp = convert_xsecs_to_fb(input_xsec, input_xsec_uncert, input_unit, input_fractional_uncert);
        double xsec_fb = temp.first;
        double xsec_uncert_fb = temp.second;
        shared_result.set_xsec(xsec_fb, xsec_uncert_fb);

        // Let thread 0 return the correct result already after iteration XSEC_CALCULATION
        result = shared_result;
      }

      // All threads
      if (*Loop::iteration == START_SUBPROCESS)
      {
        // All threads copy the result from shared_result
        result = shared_result;
      }

    }

    /// Get cross-section info as map_str_dbl (for simple printing)
    void getTotalCrossSectionAsMap(map_str_dbl& result)
    {
      using namespace Pipes::getTotalCrossSectionAsMap;

      // @todo Do we need this to ensure that the result map is always of the same length (for the printer)?
      // // Append the xsec info for the current collider to the result map
      // if (*Loop::iteration == COLLIDER_INIT)
      // {
      //   xsec empty_xs;
      //   for(auto s_d_pair : empty_xs.get_content_as_map())
      //   {
      //     std::string new_key(Dep::RunMC->current_collider());
      //     new_key.append("__").append(s_d_pair.first);
      //     result[new_key] = s_d_pair.second;
      //   }
      // }

      // Append the xsec info for the current collider to the result map
      if (*Loop::iteration == COLLIDER_FINALIZE)
      {
        for(auto s_d_pair : Dep::TotalCrossSection->get_content_as_map())
        {
          std::string new_key(Dep::RunMC->current_collider());
          new_key.append("__").append(s_d_pair.first);
          result[new_key] = s_d_pair.second;
        }
      }
    }  // end getXsecInfoMap


    /// Output PID pair cross-sections as a str-dbl map, for easy printing
    void getPIDPairCrossSectionsInfo(map_str_dbl& result)
    {
      using namespace Pipes::getPIDPairCrossSectionsInfo;

      if (*Loop::iteration == BASE_INIT)
      {
        result.clear();
      }

      // Add cross-sections for each collider
      if (*Loop::iteration == XSEC_CALCULATION)
      {
        for(const auto& PID_pair_xsec_pair : *Dep::PIDPairCrossSectionsMap)
        {
          const PID_pair& pp = PID_pair_xsec_pair.first;
          const PID_pair_xsec_container& xs = PID_pair_xsec_pair.second;
          result[Dep::RunMC->current_collider() + "_PID_pair_" + pp.str() + "_" + xs.info_string() + "_cross_section_fb"] = xs.xsec();
          result[Dep::RunMC->current_collider() + "_PID_pair_" + pp.str() + "_" + xs.info_string() + "_cross_section_err_fb"] = xs.xsec_err();
          result[Dep::RunMC->current_collider() + "_PID_pair_" + pp.str() + "_" + xs.info_string() + "_trust_level"] = xs.trust_level();
        }
      }

    }

  }
}
