//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  Likelihood container implementations.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Christoph Weniger
///    (c.weniger@uva.nl)
///  \date 2013 May, June, July
///
///  \author Gregory Martinez
///    (gregory.david.martinez@gmail.com)
///  \date 2013 July
///  \date 2014 Feb
///
///  \author Pat Scott
///    (patscott@physics.mcgill.ca)
///  \date 2013 Aug
///  \date 2014 May, June, onwards...
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2019 May
///
///  \author Anders Kvellestad
///          (anders.kvellestad@fys.uio.no
///  \date 2021 Feb
///
///  *********************************************

#include "gambit/Core/likelihood_container.hpp"
#include "gambit/Utils/signal_helpers.hpp"
#include "gambit/Utils/signal_handling.hpp"
#include "gambit/Utils/mpiwrapper.hpp"
#include "gambit/Utils/lnlike_modifiers.hpp"

//#define CORE_DEBUG

namespace Gambit
{

  // Methods for Likelihood_Container class.

  /// Constructor
  Likelihood_Container::Likelihood_Container(const std::map<str, primary_model_functor *> &functorMap,
   DRes::DependencyResolver &dependencyResolver, IniParser::IniFile &iniFile,
   const str &purpose, Printers::BaseBasePrinter& printer)
  : dependencyResolver               (dependencyResolver),
    printer                          (printer),
    functorMap                       (functorMap),
    min_valid_lnlike                 (iniFile.getValueOrDef<double>(0.9*std::numeric_limits<double>::lowest(), "likelihood", "model_invalid_for_lnlike_below")),
    alt_min_valid_lnlike             (iniFile.getValueOrDef<double>(0.5*min_valid_lnlike, "likelihood", "model_invalid_for_lnlike_below_alt")),
    active_min_valid_lnlike          (min_valid_lnlike), // can be switched to the alternate value by the scanner
    print_invalid_points             (iniFile.getValueOrDef<bool>(true, "likelihood", "print_invalid_points")),
    disable_print_for_lnlike_below   (iniFile.getValueOrDef<double>(min_valid_lnlike, "likelihood", "disable_print_for_lnlike_below")),
    lnlike_modifier_name             (iniFile.getValueOrDef<str>("identity", "likelihood", "use_lnlike_modifier")),
    intralooptime_label              ("Runtime(ms) intraloop"),
    interlooptime_label              ("Runtime(ms) interloop"),
    totallooptime_label              ("Runtime(ms) totalloop"),
    /* Note, likelihood container should be constructed after dependency
       resolution, so that new printer IDs can be safely acquired without
       risk of collision with graph vertex IDs */
    intraloopID(Printers::get_main_param_id(intralooptime_label)),
    interloopID(Printers::get_main_param_id(interlooptime_label)),
    totalloopID(Printers::get_main_param_id(totallooptime_label)),
    invalidcodeID(Printers::get_main_param_id("Invalidation Code")),
    #ifdef CORE_DEBUG
      debug            (true)
    #else
      debug            (iniFile.getValueOrDef<bool>(false, "debug") or iniFile.getValueOrDef<bool>(false, "likelihood", "debug"))
    #endif
  {
    // Get the parameter node for the chosen lnlike_modifier (if any)
    if (lnlike_modifier_name != "identity")
    {
      lnlike_modifier_params = Options(iniFile.getValue<YAML::Node>("likelihood", "lnlike_modifiers", lnlike_modifier_name));
    }
    // Set the list of valid return types of functions that can be used for 'purpose' by this container class.
    const std::vector<str> allowed_types_for_purpose = initVector<str>("double", "std::vector<double>", "float", "std::vector<float>");
    // Find subset of vertices that match requested purpose
    auto all_vertices = dependencyResolver.getObsLikeOrder();
    for (auto it = all_vertices.begin(); it != all_vertices.end(); ++it)
    {
      if (dependencyResolver.getIniEntry(*it)->purpose == purpose)
      {
        return_types[*it] = dependencyResolver.checkTypeMatch(*it, purpose, allowed_types_for_purpose);
        target_vertices.push_back(std::move(*it));
      }
      else
      {
        aux_vertices.push_back(std::move(*it));
      }
    }
  }

  /// Do the prior transformation and populate the parameter map
  void Likelihood_Container::setParameters (const std::unordered_map<std::string, double> &parameterMap)
  {
    // Set up a stream containing the parameter values, for diagnostic output
    std::ostringstream parstream;

    // Iterate over the primary_model_parameters functors of all the models being scanned.
    for (auto act_it = functorMap.begin(), act_end = functorMap.end(); act_it != act_end; act_it++)
    {
      parstream << "  " << act_it->first << ":" << endl;
      // Get the names of the parameters for this model.
      auto paramkeys = act_it->second->getcontentsPtr()->getKeys();
      // Iterate over the parameters, setting their values in the primary_model_parameters functors from the parameterMap.
      for (auto par_it = paramkeys.begin(), par_end = paramkeys.end(); par_it != par_end; par_it++)
      {
        str key = act_it->first + "::" + *par_it;
        auto tmp_it = parameterMap.find(key);
        if(tmp_it == parameterMap.end())
        {
           std::ostringstream err;
           err << "Error! Failed to set parameter '"<<key<<"' following prior transformation! The parameter could not be found in the map returned by the prior. This probably means that the prior you are using contains a bug." << std::endl;
           err << "The parameters and values that *were* returned by the prior were:" <<std::endl;
           if(parameterMap.size()==0){ err << "None! Size of map was zero." << std::endl; }
           else {
             for (auto par_jt = parameterMap.begin(); par_jt != parameterMap.end(); ++par_jt)
             {
               err << par_jt->first << "=" << par_jt->second << std::endl;
             }
           }
           core_error().raise(LOCAL_INFO,err.str());
        }
        parstream << "    " << *par_it << ": " << tmp_it->second << endl;
        act_it->second->getcontentsPtr()->setValue(*par_it, tmp_it->second);
      }
    }

    // Notify all exceptions of the values of the parameters for this point.
    exception::set_parameters("\n\nYAML-ready parameter values at failed point:\n"+parstream.str());

    // Print out the MPI rank and values of the parameters for this point if in debug mode.
    if (debug)
    {
      #ifdef WITH_MPI
        GMPI::Comm COMM_WORLD;
        std::cout << "MPI process rank: "<< COMM_WORLD.Get_rank() << std::endl;
      #endif
      cout << parstream.str();
      logger() << LogTags::core << "\nBeginning computations for parameter point:\n" << parstream.str() << EOM;
    }
    // Print the parameter point to the logs, even if not in debug mode
    //logger() << LogTags::core << "\nBeginning computations for parameter point:\n" << parstream.str() << EOM;


  }

  /// Evaluate total likelihood function
  double Likelihood_Container::main(std::unordered_map<std::string, double> &in)
  {
    logger() << LogTags::core << LogTags::debug << "Entered Likelihood_Container::main" << EOM;

    double lnlike = 0;
    bool point_invalidated = false;

    // Check for signals from the scanner to switch to an alternate minimum log likelihood value. TODO: could let scanner plugin set the actual value?
    static bool switch_done(false); // Disable this check once the switch occurs
    if(not switch_done)
    {
      if(check_for_switch_to_alternate_min_LogL())
      {
        active_min_valid_lnlike = alt_min_valid_lnlike; // starts off equal to min_valid_lnlike
        logger() << "Switched to using alt_min_valid_lnlike ("<<alt_min_valid_lnlike<<") instead of original value ("<<min_valid_lnlike<<")" << EOM;
        switch_done = true;
      }
    }

    // Check for signals to abort run
    if(signaldata().check_if_shutdown_begun())
    {
      tell_scanner_early_shutdown_in_progress(); // e.g. sets 'quit' flag in Diver
      logger() << "Informed scanner that early shutdown is in progress and it should secure all its output files if possible." << EOM;
    }

    // Decide if we need to skip the likelihood calculation due to shutdown procedure
    if(signaldata().shutdown_begun() and not scanner_can_quit())
    {
      // If the scanner does not have a built-in mechanism for halting the scan early, then we will assume
      // responsiblity for the process and attempt to shut the scan down from our side.
      signaldata().attempt_soft_shutdown();
      lnlike = alt_min_valid_lnlike; // Always use this larger value to avoid scanner deadlocks (e.g. MultiNest refuses to progress without a likelihood above its minimum threshold)
      point_invalidated = true; // Will prevent this likelihood value from being flagged as 'valid' by the printer
      logger() << "Shutdown in progess! The scanner is not flagged as being able to shut itself down, so are managing the shutdown from the likelihood container side. Returning min_valid_lnlike to ScannerBit instead of computing likelihood." << EOM;
    }
    else // Do the normal likelihood calculation
    {
      // If the shutdown has been triggered but the quit flag is present, then we let the likelihood evaluation proceed as normal.

      bool compute_aux = true;

      // Set the values of the parameter point in the PrimaryParameters functor, and log them to cout and/or the logs if desired.
      setParameters(in);

      // Logger debug output; things labelled 'LogTags::debug' only get logged if the logger::debug or master debug flags are true, not if only 'likelihood::debug' is true.
      logger() << LogTags::core << LogTags::debug << "Number of target vertices to calculate:    " << target_vertices.size() << endl
                                                  << "Number of auxiliary vertices to calculate: " << aux_vertices.size() << EOM;

      // Begin timing of total likelihood evaluation
      std::chrono::time_point<std::chrono::system_clock> startL = std::chrono::system_clock::now();

      // Compute time since the previous likelihood evaluation ended
      std::chrono::duration<double> interloop_time = startL - previous_endL;

      // First work through the target functors, i.e. the ones contributing to the likelihood.
      for (auto it = target_vertices.begin(), end = target_vertices.end(); it != end; ++it)
      {
        // Log the likelihood being tried.
        str likelihood_tag = "ikelihood contribution from " + dependencyResolver.get_functor(*it)->origin()
                             + "::" + dependencyResolver.get_functor(*it)->name();
        if (debug) logger() << LogTags::core << "Calculating l" << likelihood_tag << "." << EOM;

        try
        {
          // Set up debug output streams.
          std::ostringstream debug_to_cout;
          if (debug) debug_to_cout << "  L" << likelihood_tag << ": ";

          // Calculate the likelihood component.
          dependencyResolver.calcObsLike(*it);

          // Switch depending on whether the functor returns floats or doubles and a single likelihood or a vector of them.
          str rtype = return_types[*it];
          if (rtype == "double")
          {
            double result = dependencyResolver.getObsLike<double>(*it);
            if (debug) debug_to_cout << result;
            lnlike += result;
          }
          else if (rtype == "std::vector<double>")
          {
            std::vector<double> result = dependencyResolver.getObsLike<std::vector<double> >(*it);
            for (auto jt = result.begin(); jt != result.end(); ++jt)
            {
              if (debug) debug_to_cout << *jt << " ";
              lnlike += *jt;
            }
          }
          else if (rtype == "float")
          {
            float result = dependencyResolver.getObsLike<float>(*it);
            if (debug) debug_to_cout << result;
            lnlike += result;
          }
          else if (rtype == "std::vector<float>")
          {
            std::vector<float> result = dependencyResolver.getObsLike<std::vector<float> >(*it);
            for (auto jt = result.begin(); jt != result.end(); ++jt)
            {
              if (debug) debug_to_cout << *jt << " ";
              lnlike += *jt;
            }
          }
          else core_error().raise(LOCAL_INFO, "Unexpected target functor type.");

          // Print debug info
          if (debug) cout << debug_to_cout.str() << endl;

          // Don't just roll over if it's a NaN, kill the scan and force the developer to fix it.
          if (Utils::isnan(lnlike))
          {
            core_error().raise(LOCAL_INFO, "L" + likelihood_tag + " is NaN!");
          }

          // If we've dropped below the likelihood corresponding to effective zero already, skip the rest of the vertices.
          if (lnlike <= active_min_valid_lnlike) dependencyResolver.invalidatePointAt(*it, false);

          // Log completion of this likelihood.
          if (debug) logger() << LogTags::core << "Computed l" << likelihood_tag << "." << EOM;
        }

        // Catch points that are invalid, either due to low like or pathology.  Skip the rest of the vertices if a point is invalid.
        catch(invalid_point_exception& e)
        {
          logger() << LogTags::core << "Point invalidated by " << e.thrower()->origin() << "::" << e.thrower()->name() << ": " << e.message() << "Invalidation code " << e.invalidcode << EOM;
          logger().leaving_module();
          lnlike = active_min_valid_lnlike;
          compute_aux = false;
          point_invalidated = true;
          int rankinv = printer.getRank();
          // If print_ivalid_points is false disable the printer
          if(!print_invalid_points)
            printer.disable();
          printer.print(e.invalidcode, "Invalidation Code", invalidcodeID, rankinv, getPtID());
          if (debug) cout << "Point invalid. Invalidation code: " << e.invalidcode << endl;
          break;
        }
      }


      // If none of the likelihood calculations have invalidated the point, calculate the additional auxiliary observables.
      if (compute_aux)
      {
        if (debug) logger() << LogTags::core <<  "Completed likelihoods.  Calculating additional observables." << EOM;

        for (auto it = aux_vertices.begin(), end = aux_vertices.end(); it != end; ++it)
        {
          // Log the observables being tried.
          str aux_tag = "dditional observable from " + dependencyResolver.get_functor(*it)->origin()
                               + "::" + dependencyResolver.get_functor(*it)->name();
          if (debug) logger() << LogTags::core <<  "Calculating a" << aux_tag << "." << EOM;

          try
          {
            dependencyResolver.calcObsLike(*it);
            if (debug) logger() << LogTags::core << "Computed a" << aux_tag << "." << EOM;
          }
          catch(Gambit::invalid_point_exception& e)
          {
            logger() << LogTags::core << "Additional observable invalidated by " << e.thrower()->origin()
                     << "::" << e.thrower()->name() << ": " << e.message() << "Invalidation code " << e.invalidcode << EOM;
          }
        }
      }

      // If the point is invalid and print_invalid_points = false disable the printer, otherwise print vertices
      if(point_invalidated and !print_invalid_points)
        printer.disable();
      // If the likelihood is below the limit given in disable_print_for_lnlike_below, disable the printer
      else if(lnlike <= disable_print_for_lnlike_below)
        printer.disable();
      else
      {
        for (auto it = target_vertices.begin(), end = target_vertices.end(); it != end; ++it)
           dependencyResolver.printObsLike(*it,getPtID());
        for (auto it = aux_vertices.begin(), end = aux_vertices.end(); it != end; ++it)
           dependencyResolver.printObsLike(*it,getPtID());
      }

      // End timing of total likelihood evaluation
      std::chrono::time_point<std::chrono::system_clock> endL = std::chrono::system_clock::now();

      // Compute time since the previous likelihood evaluation ended
      // I.e. computing time of this likelihood, plus overhead from previous inter-loop time.
      std::chrono::duration<double> true_total_loop_time = endL - previous_endL;

      // Update stored timing information for use in next loop
      previous_startL = startL;
      previous_endL   = endL;

      std::chrono::duration<double> runtimeL = endL - startL;
      typedef std::chrono::milliseconds ms;

      // Print timing data
      if(dependencyResolver.printTiming())
      {
        int rank = printer.getRank();
        // Convert time counts to doubles (had weird problem with long long ints on some systems)
        double d_runtime   = std::chrono::duration_cast<ms>(runtimeL).count();
        double d_interloop = std::chrono::duration_cast<ms>(interloop_time).count();
        double d_total     = std::chrono::duration_cast<ms>(true_total_loop_time).count();
        printer.print(d_runtime,   intralooptime_label, intraloopID, rank, getPtID());
        printer.print(d_interloop, interlooptime_label, interloopID, rank, getPtID());
        printer.print(d_total,     totallooptime_label, totalloopID, rank, getPtID());
      }

    }

    if (debug) cout << "Total log-likelihood: " << lnlike << endl << endl;
    logger() << "Total lnL: " << lnlike << EOM;
    dependencyResolver.resetAll();

    // Disable the printer so that it doesn't try to output the min_valid_lnlike as a valid likelihood value. ScannerBit will re-enable it when needed again.
    // Disable only for the next print call
    if(point_invalidated) printer.disable(1);

    logger() << LogTags::core << LogTags::debug << "Returning control to ScannerBit" << EOM;

    return lnlike;
  }

  /// Use this to modify the total likelihood function before passing it to the scanner
  double Likelihood_Container::purposeModifier(double lnlike)
  {
    return Utils::run_lnlike_modifier(lnlike, lnlike_modifier_name, lnlike_modifier_params);
  }

}

