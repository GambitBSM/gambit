//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Likelihood container declarations.
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
///  \date 2014 May, June
///
///  \author Tomas Gonzalo
///    (tomas.gonzalo@monash.edu)
///  \date 2019 May
///
///  *********************************************

#ifndef __likelihood_container_hpp__
#define __likelihood_container_hpp__

#include "gambit/Core/container_factory.hpp"
#include "gambit/Printers/baseprinter.hpp"

namespace Gambit
{

  /// Class for collecting pointers to all the likelihood components, then running and combining them.
  class Likelihood_Container : public Scanner::Function_Base<double (std::unordered_map<std::string, double> &)>
  {

    private:

      /// Graph vertices corresponding to functors in the ObsLike section of yaml file
      std::vector<DRes::VertexID> target_vertices;

      /// Graph vertices corresponding to additional functors not in ObsLike part of yaml file
      std::vector<DRes::VertexID> aux_vertices;

      /// Bound dependency resolver object
      DRes::DependencyResolver &dependencyResolver;

      /// Bound printer object
      Printers::BaseBasePrinter &printer;

      /// Map of parameter names to values
      //std::unordered_map<str, double> parameterMap;

      /// Map of scanned model names to primary model functors
      std::map<str, primary_model_functor *> functorMap;

      /// Primary value of the log likelihood at which a point is considered so unlikely that it can be ruled out (invalid).
      double min_valid_lnlike;

      /// Alternate value for the minimum log likelihood (scanner can trigger a switch to this in special circumstances)
      double alt_min_valid_lnlike;

      /// Active value for the minimum log likelihood (one of the above two values, whichever is currently in-use)
      double active_min_valid_lnlike;

      /// Switch to print or not print invalid points to the output file
      bool print_invalid_points;

      /// Disable printing for points with log likelihood below some value
      double disable_print_for_lnlike_below;

      /// Map of return types of target functors
      std::map<DRes::VertexID,str> return_types;

      /// Global record of time that last likelihood evaluation began, for computing true total iteration time.
      std::chrono::time_point<std::chrono::system_clock> previous_startL;
      /// Global record of time that last likelihood evaluation ended, for computing intra-iteration overhead time.
      std::chrono::time_point<std::chrono::system_clock> previous_endL;

      /// Print labels for timing data
      const str intralooptime_label; // Time elapsed during likelihood evaluations
      const str interlooptime_label; // Time elapsed between likelihood evaluation
      const str totallooptime_label; // Time elapsed from end of one likelihood evaluation to end of next (sum of the above two)

      /// printer IDs for timing data
      const int intraloopID;
      const int interloopID;
      const int totalloopID;

      /// Invalid Code printing ID
      const int invalidcodeID;

      /// Run in likelihood debug mode?
      bool debug;

    public:

      /// Constructor
      Likelihood_Container (const std::map<str, primary_model_functor *> &functorMap,
       DRes::DependencyResolver &dependencyResolver, IniParser::IniFile &iniFile,
       const str &purpose, Printers::BaseBasePrinter& printer);

      /// Do the prior transformation and populate the parameter map
      void setParameters (const std::unordered_map<std::string, double> &);

      /// Evaluate total likelihood function
      double main (std::unordered_map<std::string, double> &in);

  };

  // Register the Likelihood Container as an available target function for ScannerBit.  The first argument
  // is a tag that gets used later by the Likelihood_Container_Factory to create a new Likelihood_Container
  // and return a pointer to it.
  LOAD_SCANNER_FUNCTION(GAMBIT_Scanner_Target_Function, Likelihood_Container)

}

#endif
