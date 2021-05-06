//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  Prior function made up of two log priors
///  (positive and negative branch) joined across
///  zero by a flat region.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///   
///  \author Ben Farmer
///          (benjamin.farmer@fysik.su.se)
///  \date 2016 Jun
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2016 Jun
///
///  *********************************************

#include "gambit/ScannerBit/priors/doublelogflatjoin.hpp"

#include <cmath>

namespace Gambit
{
  namespace Priors
  {

    /// Constructor
    DoubleLogFlatJoin::DoubleLogFlatJoin(const std::vector<std::string>& param, const Options& options) 
      : BasePrior(param, 1)
      , myparameter(param_names[0])
      , lower(0.0)
      , flat_start(0.0)
      , flat_end(0.0)
      , upper(0.0)
      , C(0.0)  
      , P01(0.0) 
      , P12(0.0) 
      , P23(0.0)
      , no_lower_log(false)
      , no_upper_log(false) 
    {
      // Only valid for 1D parameter transformation
      if (param.size()!=1)
      {
        scan_err << "Invalid input to DoubleLogFlatJoin prior (in constructor): " << endl
                 << "Input parameters must be a vector of size 1! (has size=" << param.size() << ")" << scan_end;
      }

      // Read the entries we need from the options
      if ( options.hasKey("ranges") )
      {
        // Shortcut option assignment method
        std::vector<double> ranges = options.getValue<std::vector<double>>("ranges");
        if(ranges.size()!=4)
        {
          scan_err << "Invalid input to DoubleLogFlatJoin prior (in constructor): value " << endl
                   << "of 'ranges' key must be a vector of length 4 (length was "<<ranges.size()<<"), " << endl
                   << "where the entries specify 'lower', 'flat_start', 'flat_end', and 'upper'." << scan_end;
        }
        lower      = ranges[0];
        flat_start = ranges[1];
        flat_end   = ranges[2];
        upper      = ranges[3];
      }
      else if ( options.hasKey("range") )
      {
        // Semi-shortcut option assignment method
        std::vector<double> range = options.getValue<std::vector<double>>("range");
        if(range.size()!=2)
        {
          scan_err << "Invalid input to DoubleLogFlatJoin prior (in constructor): value " << endl
                   << "of 'range' key must be a vector of length 2 (length was "<<range.size()<<"), " << endl
                   << "where the entries specify 'lower', and 'upper'." << scan_end;
        }
        lower      = range[0];
        upper      = range[1];
        flat_start = get_option("flat_start", options);
        flat_end = get_option("flat_end", options);
      }
      else
      {
        lower = get_option("lower", options);
        flat_start = get_option("flat_start", options);
        flat_end = get_option("flat_end", options);
        upper = get_option("upper", options);
      }

      // Make sure ordering of constraints makes sense
      if(     (lower < flat_start)
          and (flat_start < 0) 
          and (0 < flat_end) 
          and (flat_end < upper) )
      { 
        // No problem  
      }
      else if( (lower==flat_start)
               and  (flat_start <= flat_end)
               and  (0 < flat_end)
               and  (flat_end < upper) )
      {
        // Lower log portion is collapsed; flat portion may now be fully above zero, and is allowed to collapse.
        no_lower_log = true;
      }
      else if( (lower < flat_start)
               and  (flat_start < 0)
               and  (flat_start <= flat_end)
               and  (flat_end==upper) )
      {
        // Upper log portion is collapsed; flat portion may now be fully below zero, and is allowed to collapse.
        no_upper_log = true;
      } 
      else if( (lower==flat_start)
               and  (flat_start < flat_end)
               and  (flat_end==upper) )
      {
        // Both log portions collapsed; flat portion may now be anywhere, but is not allowed to collapse.
        no_upper_log = true;
      } 
      else
      {
        scan_err << "Inconsistent values of options for DoubleLogFlatJoin prior detected! " << endl
                 << "The required ordering is: lower <= flat_start < 0 < flat_end <= upper."<< endl
                 << "Values received were: ["<<lower<<", "<<flat_start<<", "<<flat_end<<", "<<upper<<"]." << endl
                 << "(if either log portion is collapsed then the flat portion is permitted to move from covering zero as appropriate)" << scan_end;
      }

      // Useful quantities:
      double x0 = lower;
      double x1 = flat_start;
      double x2 = flat_end;
      double x3 = upper;
      double Nlower = 0;
      double Nupper = 0;
      double Nflat = x2-x1;
      if(not no_lower_log) Nlower = x1*log(fabs(x1/x0)); 
      if(not no_upper_log) Nupper = x2*log(fabs(x3/x2)); 
      C   = 1. / ( Nflat + Nlower + Nupper );   // Normalization factor 
      P01 =   C * Nlower;  // Prob. of x in (x0,x1)
      P12 =   C * Nflat;   // Prob. of x in (x1,x2)
      P23 =   C * Nupper;  // Prob. of x in (x2,x3)

    }        


    /// Try to get options for double log-flat joined prior
    double DoubleLogFlatJoin::get_option(const str& name, const Options& options)
    {
      if (options.hasKey(name))
      {
        return options.getValue<double>(name);
      }
      else
      { 
        scan_err << "Missing option " << name <<" (or 'ranges') for DoubleLogFlatJoin prior. Must specify " << endl
                 << "'lower', 'flat_start', 'flat_end', and 'upper', or else all of these at once in a vector labelled 'ranges'." << scan_end;
      }
      return 0;
    }
    

    /// Transformation from unit interval to the double log + flat join
    void DoubleLogFlatJoin::transform(const std::vector <double> &unitpars, std::unordered_map <std::string, double> &output) const
    {
      // Only valid for 1D parameter transformation
      if (unitpars.size()!=1)
      {
        scan_err << "Invalid input to DoubleLogFlatJoin prior (in 'transform'): Input parameters must be a vector of size 1! (has size=" << unitpars.size() << ")" << scan_end;
      }

      double x = 0; // output (result)
      double r = unitpars[0]; // input unit cube parameter
      double x0 = lower;
      double x1 = flat_start;
      double x2 = flat_end;
      //double x3 = upper; // apparantly don't need this

      // Based on Anders' python implementation.

      // Transformation:
      if( r <= P01 )
      {
        x = x0 * exp(r/(x1*C));
      }
      else if( (r > P01) and (r < (P01+P12)) ) 
      {
        x = x1 + (r-P01)/C;
      }
      else if( (r > (P01+P12)) and (r <= (P01+P12+P23)) ) 
      {
        x = x2*exp( (r-(P01+P12))/(x2*C) );
      }
      else 
      {
        scan_err << "Problem transforming r-value for DoubleLogFlatJoin (received "<<r<<")!" << scan_end;
      }

      output[myparameter] = x;
    }

    std::vector<double> DoubleLogFlatJoin::inverse_transform(const std::unordered_map<std::string, double> &physical) const
    {
      const double p = physical.at(myparameter);

      if (p >= lower && p < flat_start)
      {
        // log prior from lower to flat_start
        double u01 = std::log(p / lower) / std::log(flat_start / lower);
        return {u01 * P01};
      }
      else if (p >= flat_start && p < flat_end)
      {
        // flat prior from flat_start to flat_end
        double u01 = (p - flat_start) / (flat_end - flat_start);
        return {P01 + u01 * P12};
      }
      else if (p>= flat_end && p < upper)
      {
        // log prior from flat_end to upper
        double u01 = std::log(p / flat_end) / std::log(upper / flat_end);
        return {P01 + P12 + u01 * P23};
      }
      else
      {
        scan_err << "no inverse transformation for double_log_flat_join - outside range"
                 << scan_end;
      return {};  // silence compiler warning (reaches end non-void function)
      }
    }
      
    double DoubleLogFlatJoin::operator()(const std::vector<double> &vec) const
    {
      double r = 0;
      double x = vec[0]; 
      double x0 = lower;
      double x1 = flat_start;
      double x2 = flat_end;
      double x3 = upper;
      if( x <= x0 )
      {
        r = 0.;
      }
      else if( (x > x0) and (x <= x1) )
      {
        r =  1./x * x1 * C;
      }
      else if( (x > x1) and (x <= x2) )
      {
        r =  C;
      }
      else if( (x > x2) and (x <= x3) )
      {
        r =  1./x * x2 * C;
      }
      else if (x > x3)
      {
        r = 0;
      }
      else 
      {
        scan_err << "Problem computing prior density for DoubleLogFlatJoin (received x="<<x<<")!" << scan_end;
      }

      return r;
    }

  }
}
