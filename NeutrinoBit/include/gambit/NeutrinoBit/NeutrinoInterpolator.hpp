//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Interpolator for neutrino likelihoods
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2019 Aug
///
///  *********************************************

#ifndef __NeutrinoInterpolator_hpp__
#define __NeutrinoInterpolator_hpp__

#include <gsl/gsl_spline.h>

namespace Gambit
{
  namespace NeutrinoBit
  {

    class NeutrinoInterpolator
    {
      private:

        // GSL objects
        gsl_interp_accel *acc;
        gsl_spline *spline;

      public:

        // Constructor
        NeutrinoInterpolator(std::string file)
        {
          // Read file
          std::vector<std::pair<double,double> > array;
          std::ifstream f(GAMBIT_DIR "/"+file);
          std::string line;
          while(getline(f, line))
          {
            std::stringstream iss(line);
            std::pair<double,double> point;
            iss >> point.first;
            iss.ignore();
            iss >> point.second;
            array.push_back(point);
          }
          unsigned int npoints = array.size();

          // Fill axes
          double x[npoints], y[npoints];
          for (unsigned int i=0; i<npoints; i++)
          {
            x[i] = array[i].first;
            y[i] = array[i].second;
          }
 
          // Create and initialize spline
          acc = gsl_interp_accel_alloc();
          spline = gsl_spline_alloc(gsl_interp_cspline, npoints);
          gsl_spline_init(spline, x, y, npoints);

        }

        // Delete copy constructor and assignment operator to avoid shallow copies
        NeutrinoInterpolator(const NeutrinoInterpolator&) = delete;
        NeutrinoInterpolator& operator=(const NeutrinoInterpolator&) = delete;     

        // Destructor
        ~NeutrinoInterpolator()
        {
          gsl_spline_free (spline);
          gsl_interp_accel_free (acc);
        }

        // Evaluation function
        double eval(double x)
        {
          return gsl_spline_eval(spline, x, acc);
        }

    };

  } // NeutrinoBit

} // Gambit

#endif // __NeutrinoBitInterpolator_hpp__
