//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  SignalRegionData struct.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Abram Krislock
///          (a.m.b.krislock@fys.uio.no)
///
///  \author Andy Buckley
///          (andy.buckley@cern.ch)
///
///  \author Anders Kvellestad
///          (anders.kvellestad@fys.uio.no)
///  \date often
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2019 Feb
///
///  *********************************************

#pragma once

#include "gambit/Utils/begin_ignore_warnings_eigen.hpp"
#include "Eigen/Core"
#include "gambit/Utils/end_ignore_warnings.hpp"

#include <string>
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <cfloat>
#include <limits>
#include <memory>
#include <iomanip>
#include <algorithm>
#include "gambit/ColliderBit/analyses/EventCounter.hpp"

namespace Gambit
{
  namespace ColliderBit
  {

    /// A simple container for the result of one signal region from one analysis.
    struct SignalRegionData
    {

      /// Constructor with EventCounter arg for the signal count and SR name
      SignalRegionData(const EventCounter& scounter,
                       double nobs, const std::pair<double,double>& nbkg,
                       double nsigscaled=0)
       : SignalRegionData(scounter.name(), nobs, scounter.weight_sum(), nbkg.first, scounter.weight_sum_err(), nbkg.second, nsigscaled)
      {}

      /// Constructor with EventCounter arg for the signal count, but separate name
      SignalRegionData(const std::string& sr,
                       double nobs, const EventCounter& scounter, const std::pair<double,double>& nbkg,
                       double nsigscaled=0)
       : SignalRegionData(sr, nobs, scounter.weight_sum(), nbkg.first, scounter.weight_sum_err(), nbkg.second, nsigscaled)
      {}

      /// Constructor with {n,nsys} pair args
      SignalRegionData(const std::string& sr,
                       double nobs, const std::pair<double,double>& nsigMC, const std::pair<double,double>& nbkg,
                       double nsigscaled=0)
       : SignalRegionData(sr, nobs, nsigMC.first, nbkg.first, nsigMC.second, nbkg.second, nsigscaled)
      {}

      /// Constructor with separate n & nsys args
      SignalRegionData(const std::string& sr,
                       double nobs, double nsigMC, double nbkg,
                       double nsigMCsys, double nbkgerr, double nsigscaled=0) :
        sr_label(sr),
        n_obs(nobs), 
        n_sig_MC(nsigMC), 
        n_sig_MC_sys(nsigMCsys), 
        n_sig_MC_stat(sqrt(nsigMC)), 
        n_sig_scaled(nsigscaled), 
        n_bkg(nbkg),
        n_bkg_err(nbkgerr)
      { }

      /// Default constructor
      SignalRegionData() {}

      /// Consistency check
      bool check() const
      {
        bool consistent = true;
        /// @todo Add SR consistency checks
        return consistent;
      }

      /// Uncertainty calculators
      double scalefactor() const { return n_sig_MC == 0 ? 1 : n_sig_scaled / n_sig_MC; }

      double calc_n_sig_MC_err() const 
      { 
        return sqrt( n_sig_MC_stat * n_sig_MC_stat + n_sig_MC_sys * n_sig_MC_sys ); 
      }

      double calc_n_sig_scaled_err() const { return scalefactor() * calc_n_sig_MC_err(); }

      double calc_n_sigbkg_err() const 
      { 
        double n_sig_scaled_err = calc_n_sig_scaled_err();
        return sqrt( n_sig_scaled_err * n_sig_scaled_err + n_bkg_err * n_bkg_err );  
      }

      void combine_SR_MC_signal(const SignalRegionData& other)
      {
        n_sig_MC += other.n_sig_MC;
        n_sig_MC_stat = sqrt(n_sig_MC);
      }

      /// @todo Set up a more complete system of getters/setters and make the member variables private

      /// @name Signal region specification
      //@{
      std::string sr_label; ///< A label for the particular signal region of the analysis
      //@}

      /// @name Signal region data
      //@{
      double n_obs; ///< The number of events passing selection for this signal region as reported by the experiment
      double n_sig_MC; ///< The number of simulated model events passing selection for this signal region
      double n_sig_MC_sys; ///< The absolute systematic error of n_sig_MC
      double n_sig_MC_stat; ///< The absolute statistical (MC) error of n_sig_MC
      double n_sig_scaled; ///< n_sig_MC, scaled to luminosity * cross-section
      double n_bkg; ///< The number of standard model events expected to pass the selection for this signal region, as reported by the experiment.
      double n_bkg_err; ///< The absolute error of n_bkg
      //@}

    };

  }
}
