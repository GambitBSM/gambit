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
///  \date 2020 Apr
///
///  *********************************************

#ifndef __NeutrinoInterpolator_hpp__
#define __NeutrinoInterpolator_hpp__

#include <gsl/gsl_spline.h>
#include <gsl/gsl_spline2d.h>

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
          str filename = GAMBIT_DIR "/"+file;
          if(not Utils::file_exists(filename))
            NeutrinoBit_error().raise(LOCAL_INFO, "Data file '"+filename+"' does not exist.\n");

          // Read file
          std::vector<std::pair<double,double> > array;
          std::ifstream f(filename);
          std::string line;
          while(getline(f, line))
          {
            if(line.empty() or line[0] == '#')
              continue;

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

    // 2D version
    class NeutrinoInterpolator2D
    {
      private:

        // GSL objects
        gsl_interp_accel *xacc;
        gsl_interp_accel *yacc;
        gsl_spline2d *spline2d;

      public:

        // Constructor
        NeutrinoInterpolator2D(std::string file)
        {
          str filename = GAMBIT_DIR "/"+file;
          if(not Utils::file_exists(filename))
            NeutrinoBit_error().raise(LOCAL_INFO, "Data file '"+filename+"' does not exist.\n");

          // Read file
          std::vector<double> xvals, yvals;
          std::map<std::pair<double,double>,double> zvals;
          double maxzval = 0;
          std::ifstream f(filename);
          std::string line;
          while(getline(f, line))
          {
            std::stringstream iss(line);

            if(line.empty() or line[0] == '#')
              continue;

            double xval;
            iss >> xval;
            if(std::find(xvals.begin(), xvals.end(), xval) == xvals.end())
              xvals.push_back(xval);
            iss.ignore();

            double yval;
            iss >> yval;
            if(std::find(yvals.begin(), yvals.end(), yval) == yvals.end())
              yvals.push_back(yval);
            iss.ignore();

            std::pair<double, double> index(xval,yval);
            double zval;
            iss >> zval;
            if(zval > maxzval) maxzval = zval;
            if(zvals.find(index) == zvals.end())
             zvals.emplace(index, zval);
          }
          size_t xsize = xvals.size();
          size_t ysize = yvals.size();

          // Fill axes
          double x[xsize], y[ysize], z[xsize*ysize];
          for (size_t j=0; j<ysize; j++)
          {
            y[j] = yvals[j];
            for (size_t i=0; i<xsize; i++)
            {
             x[i] = xvals[i];
             std::pair<double,double> index(x[i],y[j]);
              if(zvals.find(index) != zvals.end())
                z[j*xsize+i] = zvals.at(index);
              else
                z[j*xsize+i] = maxzval;
            }
          }
 
          // Create and initialize spline
          xacc = gsl_interp_accel_alloc();
          yacc = gsl_interp_accel_alloc();
          spline2d = gsl_spline2d_alloc(gsl_interp2d_bicubic, xsize, ysize);
          gsl_spline2d_init(spline2d, x, y, z, xsize, ysize);

        }

        // Delete copy constructor and assignment operator to avoid shallow copies
        NeutrinoInterpolator2D(const NeutrinoInterpolator2D&) = delete;
        NeutrinoInterpolator2D& operator=(const NeutrinoInterpolator2D&) = delete;     

        // Destructor
        ~NeutrinoInterpolator2D()
        {
          gsl_spline2d_free (spline2d);
          gsl_interp_accel_free (xacc);
          gsl_interp_accel_free (yacc);
        }

        // Evaluation function
        double eval(double x, double y)
        {
          return gsl_spline2d_eval(spline2d, x, y, xacc, yacc);
        }

    };


  } // NeutrinoBit

} // Gambit

#endif // __NeutrinoBitInterpolator_hpp__
