///  GAMBIT: Global and Modular BSM Inference Tool
///  *********************************************
///  \file
///
///  Axion-specific module functions for DarkBit.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Sebastian Hoof
///          (hoof@uni-goettingen.de)
///  \date 2016 Oct
///  \date 2017 Jan, Feb, June, July, Sept - Dec
///  \date 2018 Jan, Mar - May, Sept
///  \date 2019 Feb, May - July
///  \date 2020 Sept, Dec
///  \date 2021 Jan
///  \date 2022 May
///
///  *********************************************

#include <algorithm>
#include <cmath>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

#include "gambit/Utils/begin_ignore_warnings_eigen.hpp"
#include <Eigen/Core>
#include "gambit/Utils/end_ignore_warnings.hpp"

#include <gsl/gsl_math.h>
#include <gsl/gsl_sf.h>
#include <gsl/gsl_sf_trig.h>
#include <gsl/gsl_sf_erf.h>
#include <gsl/gsl_spline.h>
#include <gsl/gsl_interp2d.h>
#include <gsl/gsl_spline2d.h>
#include <gsl/gsl_histogram.h>
#include <gsl/gsl_roots.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_odeiv2.h>

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/Utils/util_functions.hpp"
#include "gambit/Utils/ascii_table_reader.hpp"
#include "gambit/Utils/statistics.hpp"
#include "gambit/Utils/numerical_constants.hpp"
#include "gambit/DarkBit/DarkBit_rollcall.hpp"
#include "gambit/DarkBit/DarkBit_utils.hpp"

//#define AXION_DEBUG_MODE
//#define AXION_OMP_DEBUG_MODE

namespace Gambit
{
  namespace DarkBit
  {
    ////////////////////////////////////////////////////////////////////
    //                                                                //
    //            General Functions and Classes for Axions            //
    //                                                                //
    ////////////////////////////////////////////////////////////////////

    /*! \brief Supporting classes and functions for the axion module.
     */

     const double gagg_conversion = 1.0E-9;
     const double gaee_conversion = 1.0E+13;

    /////////////////////////////////////////////////////////////////
    //      Auxillary functions and classes for interpolation      //
    /////////////////////////////////////////////////////////////////

    /*! \brief Generic one-dimensional integration container for linear interpolation and cubic splines.
     */

    enum class InterpolationOptions1D { linear, cspline };
    const std::map<InterpolationOptions1D, std::string> int_type_name = { { InterpolationOptions1D::linear, "linear" }, { InterpolationOptions1D::cspline, "cspline"} };
    // AxionInterpolator class: Provides a general 1-D interpolation container based on the gsl library.
    // Can be declared static for efficiency & easy one-time initialisation of interpolating functions.
    class AxionInterpolator
    {
      public:
        // Overloaded class creators for the AxionInterpolator class using the init function below.
        AxionInterpolator();
        AxionInterpolator(const std::vector<double> x, const std::vector<double> y, InterpolationOptions1D type = InterpolationOptions1D::linear);
        AxionInterpolator(std::string file, InterpolationOptions1D type = InterpolationOptions1D::linear);
        AxionInterpolator& operator=(AxionInterpolator&&);
        // Destructor.
        ~AxionInterpolator();
        // Delete copy constructor and assignment operator to avoid shallow copies.
        AxionInterpolator(const AxionInterpolator&) = delete;
        AxionInterpolator operator=(const AxionInterpolator&) = delete;
        // Routine to access interpolated values.
        double interpolate(double x);
        // Routine to access upper and lower boundaries of available data.
        double lower();
        double upper();
      private:
        // Initialiser for the AxionInterpolator class.
        void init(std::string file, InterpolationOptions1D type);
        void init(const std::vector<double> x, const std::vector<double> y, InterpolationOptions1D type);
        // The gsl objects for the interpolating functions.
        gsl_interp_accel *acc;
        gsl_spline *spline;
        // Upper and lower boundaries available for the interpolating function.
        double lo;
        double up;
    };

    // Default constructor.
    AxionInterpolator::AxionInterpolator()
    {
      acc = gsl_interp_accel_alloc();
      spline = gsl_spline_alloc(gsl_interp_linear, 2);
    }

    // Initialiser for the AxionInterpolator class.
    void AxionInterpolator::init(const std::vector<double> x, const std::vector<double> y, InterpolationOptions1D type)
    {
      int pts = x.size();
      // Get first and last value of the "x" component.
      lo = x.front();
      up = x.back();
      acc = gsl_interp_accel_alloc();
      if (type == InterpolationOptions1D::cspline)
      {
        spline = gsl_spline_alloc(gsl_interp_cspline, pts);
      }
      else if (type == InterpolationOptions1D::linear)
      {
        spline = gsl_spline_alloc(gsl_interp_linear, pts);
      }
      else
      {
        DarkBit_error().raise(LOCAL_INFO, "ERROR! Interpolation type not known to class AxionInterpolator.");
      }

      gsl_spline_init(spline, &x[0], &y[0], pts);
    }

    AxionInterpolator::AxionInterpolator(const std::vector<double> x, const std::vector<double> y, InterpolationOptions1D type) { init(x, y, type); }

    // Initialiser for the AxionInterpolator class.
    void AxionInterpolator::init(std::string file, InterpolationOptions1D type)
    {
      // Check if file exists.
      if (not(Utils::file_exists(file)))
      {
        DarkBit_error().raise(LOCAL_INFO, "ERROR! File '"+file+"' not found!");
      } else {
        logger() << LogTags::debug << "Reading data from file '"+file+"' and interpolating it with '"+int_type_name.at(type)+"' method." << EOM;
      }
      // Read numerical values from data file.
      ASCIItableReader tab (file);
      tab.setcolnames("x", "y");

      init(tab["x"], tab["y"], type);
    }

    AxionInterpolator::AxionInterpolator(std::string file, InterpolationOptions1D type) { init(file, type); }

    // Move assignment operator
    AxionInterpolator& AxionInterpolator::operator=(AxionInterpolator&& interp)
    {
      if(this != &interp)
      {
        std::swap(acc,interp.acc);
        std::swap(spline,interp.spline);
        std::swap(lo,interp.lo);
        std::swap(up,interp.up);
      }
      return *this;
    }

    // Destructor
    AxionInterpolator::~AxionInterpolator()
    {
      gsl_spline_free(spline);
      gsl_interp_accel_free(acc);
    }

    // Routine to access interpolated values.
    double AxionInterpolator::interpolate(double x) { return gsl_spline_eval(spline, x, acc); }

    // Routines to return upper and lower boundaries of interpolating function
    double AxionInterpolator::lower() { return lo; }
    double AxionInterpolator::upper() { return up; }


    /*! \brief Two-dimensional integration container for bilinear interpolation and bicubic splines.
     */

     enum class InterpolationOptions2D { bilinear, bicubic };
     const std::map<InterpolationOptions2D, std::string> int_2d_type_name = { { InterpolationOptions2D::bilinear, "bilinear" }, { InterpolationOptions2D::bicubic, "bicubic"} };
    // AxionInterpolator2D class: Provides a 2-D interpolation container based on the gsl library.
    // Can be declared static for efficiency & easy one-time initialisation of interpolating functions.
    class AxionInterpolator2D
    {
      public:
        // Overloaded class creators for the AxionInterpolator class using the init function below.
        AxionInterpolator2D();
        AxionInterpolator2D(std::string file, InterpolationOptions2D type = InterpolationOptions2D::bilinear);
        AxionInterpolator2D& operator=(AxionInterpolator2D&&);
        // Destructor.
        ~AxionInterpolator2D();
        // Delete copy constructor and assignment operator to avoid shallow copies.
        AxionInterpolator2D(const AxionInterpolator2D&) = delete;
        AxionInterpolator2D operator=(const AxionInterpolator2D&) = delete;
        // Routine to access interpolated values.
        double interpolate(double x, double y);
        // Routine to check if a point is inside the interpolating box.
        bool is_inside_box(double x, double y);
      private:
        // Initialiser for the AxionInterpolator2D class.
        void init(std::string file, InterpolationOptions2D type);
        // The gsl objects for the interpolating functions that need to be available to the class routines.
        gsl_interp_accel *x_acc;
        gsl_interp_accel *y_acc;
        gsl_spline2d *spline;
        double* z;
        // Upper and lower "x" and "y" values available to the interpolating function.
        double x_lo, y_lo, x_up, y_up;
    };

    // Move assignment operator
    AxionInterpolator2D& AxionInterpolator2D::operator=(AxionInterpolator2D&& interp)
    {
      if(this != &interp)
      {
        std::swap(x_acc,interp.x_acc);
        std::swap(y_acc,interp.y_acc);
        std::swap(spline,interp.spline);
        std::swap(x_lo,interp.x_lo);
        std::swap(x_up,interp.x_up);
        std::swap(y_lo,interp.y_lo);
        std::swap(y_up,interp.y_up);
        std::swap(z,interp.z);
      }
      return *this;
    }

    // Destructor
    AxionInterpolator2D::~AxionInterpolator2D()
    {
      gsl_spline2d_free (spline);
      gsl_interp_accel_free (x_acc);
      gsl_interp_accel_free (y_acc);
      free(z);
    }

    // Initialiser for the AxionInterpolator class.
    void AxionInterpolator2D::init(std::string file, InterpolationOptions2D type)
    {
      // Check if file exists.
      if (not(Utils::file_exists(file)))
      {
        DarkBit_error().raise(LOCAL_INFO, "ERROR! File '"+file+"' not found!");
      } else {
        logger() << LogTags::debug << "Reading data from file '"+file+"' and interpolating it with '"+int_2d_type_name.at(type)+"' method." << EOM;
      }
      // Read numerical values from data file.
      ASCIItableReader tab (file);
      tab.setcolnames("x", "y", "z");
      // Initialise gsl interpolation routine.
      // Get unique entries of "x" and "y" for the grid and grid size.
      std::vector<double> x_vec = tab["x"];
      sort(x_vec.begin(), x_vec.end());
      x_vec.erase(unique(x_vec.begin(), x_vec.end()), x_vec.end());
      int nx = x_vec.size();
      std::vector<double> y_vec = tab["y"];
      sort(y_vec.begin(), y_vec.end());
      y_vec.erase(unique(y_vec.begin(), y_vec.end()), y_vec.end());
      int ny = y_vec.size();
      int n_grid_pts = tab["z"].size();

      if (nx*ny != n_grid_pts)
      {
        DarkBit_error().raise(LOCAL_INFO, "ERROR! The number of grid points ("+std::to_string(n_grid_pts)+") for AxionInterpolator2D does not equal the number of unique 'x' and 'y' values ("+std::to_string(nx)+" and "+std::to_string(ny)+")!\n       Check formatting of the file: '"+file+"'.");
      }

      const double* x = &x_vec[0];
      const double* y = &y_vec[0];
      // Allocate memory for "z" values array in gsl format
      z = (double*) malloc(nx * ny * sizeof(double));

      if (type == InterpolationOptions2D::bicubic)
      {
        spline = gsl_spline2d_alloc(gsl_interp2d_bicubic, nx, ny);
      }
      else if (type == InterpolationOptions2D::bilinear)
      {
        spline = gsl_spline2d_alloc(gsl_interp2d_bilinear, nx, ny);
      }
      else
      {
        DarkBit_error().raise(LOCAL_INFO, "ERROR! Interpolation type not known to class AxionInterpolator2D.");
      }

      x_acc = gsl_interp_accel_alloc();
      y_acc = gsl_interp_accel_alloc();

      // Determine first and last "x" and "y" values and grid step size.
      x_lo = x_vec.front();
      x_up = x_vec.back();
      y_lo = y_vec.front();
      y_up = y_vec.back();
      double x_delta = (x_up-x_lo) / (nx-1);
      double y_delta = (y_up-y_lo) / (ny-1);

      // Intialise grid.
      for (int i = 0; i < n_grid_pts; i++)
      {
        // Determine appropriate indices for the grid points.
        double temp = (tab["x"][i]-x_lo) / x_delta;
        int ind_x = (int) (temp+0.5);
        temp = (tab["y"][i]-y_lo) / y_delta;
        int ind_y = (int) (temp+0.5);

        //std::cout << ind_x << "/" << nx-1 << " " << tab["x"][i] << " vs " << x[ind_x] << " " << ind_y << "/" << ny-1 << " " << tab["y"][i] << " vs " << y[ind_y] << std::endl;

        gsl_spline2d_set(spline, z, ind_x, ind_y, tab["z"][i]);
      }
      gsl_spline2d_init (spline, x, y, z, nx, ny);
    }

    // Default creator with dummy entries for the objects w/ memory allocation
    AxionInterpolator2D::AxionInterpolator2D()
    {
      x_acc = gsl_interp_accel_alloc();
      y_acc = gsl_interp_accel_alloc();
      spline = gsl_spline2d_alloc(gsl_interp2d_bilinear, 2, 2);
      z = (double*) malloc(2 * 2 * sizeof(double));
    }
    // Overloaded class creators for the AxionInterpolator class using the init function above.
    AxionInterpolator2D::AxionInterpolator2D(std::string file, InterpolationOptions2D type) { init(file, type); }

    // Routine to access interpolated values.
    double AxionInterpolator2D::interpolate(double x, double y) { return gsl_spline2d_eval(spline, x, y, x_acc, y_acc); }

    // Routine to check if a point is inside the interpolating box.
    bool AxionInterpolator2D::is_inside_box(double x, double y) { return ((x >= x_lo) && (x <= x_up) && (y >= y_lo) && (y <= y_up)); }

     /*! \brief H.E.S.S.-likelihood-related interpolation routines.
     */

    // Auxillary function for a parabola (needed for H.E.S.S. likelihood approximation).
    double parabola(double x, const double params[]) { return params[0]*x*x + params[1]*x + params[2]; }

    // Auxillary function to return the appropriate intersection between a parabola and a line (needed for H.E.S.S. likelihood).
    double intersect_parabola_line(double a, double b, double sign, const double pparams[])
    {
      const double x1 = -3.673776;
      const double y1 = 0.4;
      double x2    = a - pparams[1];
      double temp1 = a*a + 4.0*b*pparams[0] - 2.0*a*pparams[1] + pparams[1]*pparams[1] - 4.0*pparams[0]*pparams[2];
      x2 = x2 - sign*sqrt(temp1);
      x2 = x2/(2.0*pparams[0]);
      double y2 = parabola(x2, pparams);
      temp1 = x1 - x2;
      double temp2 = y1 - y2;
      return sqrt(temp1*temp1 + temp2*temp2);
    }

    // HESS_Interpolator class: Provides a customised interpolation container for the H.E.S.S. likelihood.
    class HESS_Interpolator
    {
      public:
        // Class creator.
        HESS_Interpolator(std::string file);
        // Class destructor
        ~HESS_Interpolator();
        // Delete copy constructor and assignment operator to avoid shallow copies
        HESS_Interpolator(const HESS_Interpolator&) = delete;
        HESS_Interpolator operator=(const HESS_Interpolator&) = delete;
        // Container for the tabulated data.
        ASCIItableReader interp_lnL;
        // Routine to return interpolated log-likelihood values.
        double lnL(double epsilon, double gamma);
      private:
        gsl_interp_accel *acc[17];
        gsl_spline *spline[17];
    };

    // Class creator. Needs path to tabulated H.E.S.S. data.
    HESS_Interpolator::HESS_Interpolator(std::string file)
    {
      // Initialise upper part of the likelihood interpolation (i.e. higher axion-photon coupling).
      interp_lnL = ASCIItableReader(file);
      interp_lnL.setcolnames("lnL16", "lnL15", "lnL14", "lnL13", "lnL12", "lnL11", "lnL10", "lnL9", "lnL8", "lnL7", "lnL6", "lnL5", "lnL4", "lnL3", "lnL2", "lnL1", "lnL0");
      for (int i = 16; i >= 0; i--)
      {
        int pts = interp_lnL["lnL"+std::to_string(i)].size();
        acc[i] = gsl_interp_accel_alloc ();
        spline[i] = gsl_spline_alloc (gsl_interp_cspline, pts);
        const double* epsvals = &interp_lnL["lnL"+std::to_string(i)][0];
        if (pts==8) {
          const double lnLvals [8] = {0., -2.30259, -2.99573, -4.60517, -4.60517, -2.99573, -2.30259, 0.};
          gsl_spline_init (spline[i], epsvals, lnLvals, pts);
        } else {
          const double lnLvals [7] = {0., -2.30259, -2.99573, -4.60517, -2.99573, -2.30259, 0.};
          gsl_spline_init (spline[i], epsvals, lnLvals, pts);
        }
      }
    }

    // Destructor
    HESS_Interpolator::~HESS_Interpolator()
    {
        for (auto spl : spline)
          gsl_spline_free (spl);
        for (auto ac : acc)
          gsl_interp_accel_free (ac);
    }

    // Rotuine to interpolate the H.E.S.S. log-likelihood values.
    double HESS_Interpolator::lnL(double epsilon, double gamma)
    {
      // Parameters for the parabolae.
      const double ppars00 [3] = {0.553040458173831, 3.9888540782199913, 6.9972958867687565};
      const double ppars90 [3] = {1.2852894785722664, 9.42311266504736, 17.49643049277964};
      const double ppars95 [3] = {1.4501115909461886, 10.647792383304218, 19.811978366687622};
      double result = 0.0;

      // Check if we are inside the constrained region.
      if ((gamma > parabola(epsilon, ppars00)) && (gamma < 1.2) && (epsilon > -4.64) && (epsilon < -2.57))
      {
        // Check if we are in the upper part (higher coupling; interpolation using linear and cubic splines).
        if (gamma > 0.4)
        {
          // Cubic interpolation in Epsilon.
          int index_lo = floor((gamma-0.4)/0.05);
          int index_hi = index_lo + 1;
          double z_lo = 0.0, z_hi = 0.0;
          // Only use interpolating function where needed.
          if ( (epsilon > interp_lnL["lnL"+std::to_string(index_lo)].front()) && (epsilon < interp_lnL["lnL"+std::to_string(index_lo)].back()) )
          {
            z_lo = gsl_spline_eval (spline[index_lo], epsilon, acc[index_lo]);
          }

          if ( (epsilon > interp_lnL["lnL"+std::to_string(index_hi)].front()) && (epsilon < interp_lnL["lnL"+std::to_string(index_hi)].back()) )
          {
            z_hi = gsl_spline_eval (spline[index_hi], epsilon, acc[index_hi]);
          }

          // Linear interpolation in Gamma.
          double a = static_cast<double>(index_hi) - (gamma-0.4)/0.05;
          double b = 1.0 - a;

          result = a*z_lo + b*z_hi;

        // If not in the upper part, we must be in the lower part.
        } else {
          const double loglikevals [4] = {-4.60517, -2.99573, -2.30259, 0.0};
          // Gamma values belonging to the likelihood values along symmetry line (in terms of distance to 0.4).
          double gammavals [4] = {0.0, 0.134006, 0.174898, 0.592678};
          double distance = 0.4 - gamma;
          // Check if point is on a vertical line with the 99% C.L. point
          if (fabs(epsilon + 3.673776) > 1e-6)
          {
            // Calculate distance of point
            double a = -3.673776 - epsilon;
            double b = (-3.673776*gamma - 0.4*epsilon)/a;
            double temp1 = distance;
            distance = sqrt(a*a + temp1*temp1);
            a = temp1/a;
            temp1 = GSL_SIGN(-3.673776 - epsilon);
            double temp2 = intersect_parabola_line(a, b, temp1, ppars00);
            // CAVE: There used to be problems with distance > 1.0; these should be fixed now. Otherwise: replace by min(dist,1).
            distance = distance/temp2;
            gammavals[3] = 1.0;
            gammavals[2] = intersect_parabola_line(a, b, temp1, ppars90)/temp2;
            gammavals[1] = intersect_parabola_line(a, b, temp1, ppars95)/temp2;
          }
            gsl_interp_accel *acc = gsl_interp_accel_alloc ();
            gsl_spline *spline = gsl_spline_alloc (gsl_interp_cspline, 4);
            gsl_spline_init (spline, gammavals, loglikevals, 4);
            result = gsl_spline_eval (spline, distance, acc);
            gsl_spline_free (spline);
            gsl_interp_accel_free (acc);
          }
        }
      // CAVE: There used to be a bug with log-likelihood > 0.0; this is fixed now, but still safeguard the result against roundoff errors.
      return std::min(result,0.0);
    }


    /////////////////////////////////////////////////////////////////////////////////////////////////
    //      Solar model and integration routines to calculate the expected Helioscope signals      //
    /////////////////////////////////////////////////////////////////////////////////////////////////

    // SolarModel class: Provides a container to store a (tabulated) Solar model and functions to return its properties.
    class SolarModel
    {
      public:
        SolarModel();
        SolarModel(std::string file);
        ~SolarModel();
        SolarModel& operator=(SolarModel&&);
        // Delete copy constructor and assignment operator to avoid shallow copies
        SolarModel(const SolarModel&) = delete;
        SolarModel operator=(const SolarModel&) = delete;
        // Min. and max. radius of the solar model file (distance r from the centre of the Sun in units of the solar radius)
        double r_lo, r_hi;
        // Routine to return the screening parameter kappa^2 (kappa^-1 = Debye-Hueckel radius).
        double kappa_squared(double r);
        // Routine to return the temperature in keV.
        double temperature_in_keV(double r);
        // Routine to return the plasma frequency squared.
        double omega_pl_squared(double r);
      private:
        ASCIItableReader data;
        gsl_interp_accel *accel[3];
        gsl_spline *linear_interp[3];
    };

    SolarModel::SolarModel() {}
    SolarModel::SolarModel(std::string file)
    {
      data = ASCIItableReader(file);
      int pts = data.getnrow();
      // Terminate GAMBIT is number of columns is wrong; i.e. the wrong solar model file format.
      if (data.getncol() != 35)
      {
        DarkBit_error().raise(LOCAL_INFO, "ERROR! Solar model file '"+file+"' not compatible with GAMBIT!\n"
                                          "       See [arXiv:1810.07192] or example file in 'DarkBit/data/' for the correct format.");
      }
      data.setcolnames("mass", "radius", "temperature", "rho", "Pressure", "Luminosity", "X_H1", "X_He4", "X_He3", "X_C12", "X_C13", "X_N14", "X_N15", "X_O16", "X_O17", "X_O18", "X_Ne", "X_Na", "X_Mg", "X_Al", "X_Si", "X_P", "X_S", "X_Cl", "X_Ar",
                       "X_K", "X_Ca", "X_Sc", "X_Ti", "X_V", "X_Cr", "X_Mn", "X_Fe", "X_Co", "X_Ni");

      // Extract the radius from the files (in units of the solar radius).
      const double* radius = &data["radius"][0];
      r_lo = data["radius"][0];
      r_hi = data["radius"][pts-1];

      // Extract the temperature from the files (has to be converted into keV) & calculate the screening scale kappa_s_squared.
      // Initialise necessary variables for the screening scale calculation.
      std::vector<double> temperature;
      std::vector<double> kappa_s_sq;
      std::vector<double> w_pl_sq;
      // Multiplicative factor: (4 pi alpha_EM / atomic_mass_unit) x (1 g/cm^3) in units of keV^3
      const double factor = 4.0*pi*alpha_EM*gsl_pow_3(1.0E+6*gev2cm)/((1.0E+9*eV2g)*atomic_mass_unit);
      // Atomic weight of species i (exact weight if isotope is known OR estimate from average solar abundance from data if available OR estimate from natural terrestrial abundance).
      const double A_vals [29] = {1.007825, 4.002603, 3.016029, 12.000000, 13.003355, 14.003074, 15.000109, 15.994915, 16.999132, 17.999160,
                                  20.1312812, 22.989769, 24.3055, 26.9815385, 28.085, 30.973762, 32.0675, 35.4515, 36.275403, 39.0983, 40.078, 44.955908, 47.867, 50.9415, 51.9961, 54.938044, 55.845, 58.933194, 58.6934};
      // Ionisation of species i assuming full ionisation.
      const double Z_vals [29] = {1.0,      2.0,      2.0,       6.0,       6.0,       7.0,       7.0,       8.0,       8.0,       8.0,
                                  10.0,       11.0,      12.0,    13.0,       14.0,   15.0,      16.0,    17.0,    18.0,      19.0,    20.0,   21.0,      22.0,   23.0,    24.0,    25.0,      26.0,   27.0,      28.0};

      #ifdef AXION_DEBUG_MODE
        std::cout << "DEBUGGING INFO for solar models:\nradius/Rsol T/K kappa_s^2/keV^2 omega_pl^2/keV^2" << std::endl;
      #endif

      // Linearly extrapolate the data in the solar model file to r = 0 if necessary.
      if (r_lo > 0)
      {
        double r0 = data["radius"][0], r1 = data["radius"][1];
        double t_intercept = (1.0E-3*K2eV)*(r0*data["temperature"][1]-r1*data["temperature"][0])/(r0-r1);
        temperature.push_back(t_intercept);
        double rho_intercept = (r0*data["rho"][1]-r1*data["rho"][0])/(r0-r1);
        double sum = 0.0;
        double ne = 0.0;
        for (int j = 0; j < 29; j++)
        {
          double x_intercept = (r0* data[j+6][1]-r1* data[j+6][0])/(r0-r1);
          double temp = x_intercept*Z_vals[j]/A_vals[j];
          ne += temp;
          sum += temp*(1.0 + Z_vals[j]);
        }
        double kss = factor*sum*rho_intercept/t_intercept;
        kappa_s_sq.push_back(kss);
        double wpls = factor*ne*rho_intercept/(1.0E+6*m_electron);
        w_pl_sq.push_back(wpls);
        #ifdef AXION_DEBUG_MODE
          printf("%5.4f %1.6e %1.6e %1.6e\n", 0.0, t_intercept, kss, wpls);
        #endif
      }
      // Calculate the necessary quantities -- T(r), kappa_s^2(r) and omega_pl^2(r) -- and store them internally.
      for (int i = 0; i < pts; i++)
      {
        double sum = 0.0;
        double ne = 0.0;
        temperature.push_back((1.0E-3*K2eV)*data["temperature"][i]);
        for (int j = 0; j < 29; j++)
        {
          double temp = data[j+6][i]*Z_vals[j]/A_vals[j];
          ne += temp;
          sum += temp*(1.0 + Z_vals[j]);
        }
        double kss = factor*sum*data["rho"][i]/temperature[i];
        kappa_s_sq.push_back(kss);
        double wpls = factor*ne*data["rho"][i]/(1.0E+6*m_electron);
        w_pl_sq.push_back(wpls);
        #ifdef AXION_DEBUG_MODE
          printf("%5.4f %1.6e %1.6e %1.6e\n", data["radius"][i], temperature[i], kss, wpls);
        #endif
      }
      // Set up the interpolating functions for temperature and screening scale.
      accel[0] = gsl_interp_accel_alloc ();
      linear_interp[0] = gsl_spline_alloc (gsl_interp_linear, pts);
      const double* temp_vals = &temperature[0];
      gsl_spline_init (linear_interp[0], radius, temp_vals, pts);
      accel[1] = gsl_interp_accel_alloc ();
      linear_interp[1] = gsl_spline_alloc (gsl_interp_linear, pts);
      const double* kappa_squared_vals = &kappa_s_sq[0];
      gsl_spline_init (linear_interp[1], radius, kappa_squared_vals, pts);
      accel[2] = gsl_interp_accel_alloc ();
      linear_interp[2] = gsl_spline_alloc (gsl_interp_linear, pts);
      const double* omega_pl_squared_vals = &w_pl_sq[0];
      gsl_spline_init (linear_interp[2], radius, omega_pl_squared_vals, pts);

      logger() << LogTags::info << "Initialisation of solar model from file '"+file+"' complete!" << std::endl;
      logger() << LogTags::debug << "Entries in model file: " << pts << " for solar radius in [" << data["radius"][0] << ", " << data["radius"][pts-1] << "]." << EOM;
    }

    // Move assignment operator
    SolarModel& SolarModel::operator=(SolarModel &&model)
    {
      if (this != &model)
      {
        std::swap(data,model.data);
        std::swap(accel,model.accel);
        std::swap(linear_interp, model.linear_interp);
      }
      return *this;
    }

    // Class destructor
    SolarModel::~SolarModel()
    {
      for (auto interp : linear_interp)
        gsl_spline_free (interp);
      for (auto acc : accel)
        gsl_interp_accel_free (acc);
    }

    // Routine to return the temperature (in keV) of the zone around the distance r from the centre of the Sun.
    double SolarModel::temperature_in_keV(double r) { return gsl_spline_eval(linear_interp[0], r, accel[0]); }

    // Routine to return the screening paramter kappa^2 in units of keV^2 (kappa^-1 = Debye-Hueckel radius).
    double SolarModel::kappa_squared(double r)
    {
      // Interpolated value, directly from the Solar model.
      return gsl_spline_eval(linear_interp[1], r, accel[1]);
    }

    // Routine to return the plasma freqeuency squared (in keV^2) of the zone around the distance r from the centre of the Sun.
    double SolarModel::omega_pl_squared(double r) { return gsl_spline_eval(linear_interp[2], r, accel[2]); }

    // Constant numbers for precision etc.
    const double abs_prec = 1.0E-1, rel_prec = 1.0E-6;
    const int method = 5;
    // Auxillary structure for passing the model parameters to the gsl solver.
    struct SolarModel_params1 {double erg; double rad; SolarModel* sol;};
    struct SolarModel_params2 {double erg; double rs; SolarModel* sol;};
    struct SolarModel_params3 {double rs; double ma0; SolarModel* sol; AxionInterpolator* eff_exp;};
    struct SolarModel_params4 {double ma0; AxionInterpolator* eff_exp; AxionInterpolator* gaee_flux;};

    double rho_integrand (double rho, void * params)
    {
      // Retrieve parameters and other integration variables.
      struct SolarModel_params1 * p1 = (struct SolarModel_params1 *)params;
      double erg = (p1->erg);
      double r = (p1->rad);
      SolarModel* sol = (p1->sol);

      // Get kappa_s^2, omega_plasma^2 and the temperature.
      double ks_sq = sol->kappa_squared(rho);
      double w_pl_sq = sol->omega_pl_squared(rho);
      double T_in_keV = sol->temperature_in_keV(rho);

      // Calculate the flux.
      double x = 4.0*(erg*erg)/ks_sq;
      double cylinder = rho*rho - r*r;
      cylinder = rho/sqrt(cylinder);
      double energy_factor = erg*sqrt(erg*erg - w_pl_sq)/gsl_expm1(erg/T_in_keV);
      double rate = (ks_sq*T_in_keV)*((1.0 + 1.0/x)*gsl_log1p(x) - 1.0);

      return cylinder*energy_factor*rate;
    }

    double rad_integrand(double rad, void * params)
    {
      // Retrieve and pass on parameters.
      struct SolarModel_params2 * p2 = (struct SolarModel_params2 *)params;
      SolarModel* sol = (p2->sol);
      double rmax = std::min(1.0, sol->r_hi);
      SolarModel_params1 p1 = {p2->erg, rad, sol};

      gsl_integration_workspace * w = gsl_integration_workspace_alloc(1E6);
      double result, error;

      gsl_function F;
      F.function = &rho_integrand;
      F.params = &p1;

      //gsl_set_error_handler_off();
      gsl_integration_qag (&F, rad, rmax, 1e-2*abs_prec, 1e-2*rel_prec, 1E6, method, w, &result, &error);
      //printf ("GSL status: %s\n", gsl_strerror (status));
      //gsl_integration_qags(&F, rad, rmax, 1e-1*abs_prec, 1e-1*rel_prec, 1E6, w, &result, &error);
      gsl_integration_workspace_free (w);

      result = rad*result;
      return result;
    }

    double erg_integrand(double erg, void * params)
    {
      const double eVm = gev2cm*1E7;
      const double L = 9.26/eVm;
      struct SolarModel_params3 * p3 = (struct SolarModel_params3 *)params;
      SolarModel* sol = p3->sol;
      double m_ax = p3->ma0;
      double rs = p3->rs;

      double argument = 0.25*1.0E-3*L*m_ax*m_ax/erg;
      double temp = gsl_pow_2(gsl_sf_sinc(argument/pi));
      double exposure = p3->eff_exp->interpolate(erg);
      //std::cout << "Energy: " << erg << ", expoure = " << exposure << "." << std::endl;
      SolarModel_params2 p2 = {erg, rs, sol};

      gsl_integration_workspace * w = gsl_integration_workspace_alloc(1E6);
      double result, error;

      gsl_function F;
      F.function = &rad_integrand;
      F.params = &p2;

      // Max. and min. integration radius
      double rmin = sol->r_lo, rmax = std::min(rs, sol->r_hi);

      gsl_integration_qag (&F, rmin, rmax, 1e-1*abs_prec, 1e-1*rel_prec, 1E6, method, w, &result, &error);
      gsl_integration_workspace_free (w);

      return temp*exposure*result;
    }

    double alt_erg_integrand(double erg, void * params)
    {
      const double eVm = gev2cm*1E7;
      const double L = 9.26/eVm;
      struct SolarModel_params4 * p4 = (struct SolarModel_params4 *)params;
      double m_ax = p4->ma0;

      double argument = 0.25*1.0E-3*L*m_ax*m_ax/erg;
      double temp = gsl_pow_2(gsl_sf_sinc(argument/pi));
      double exposure = p4->eff_exp->interpolate(erg);
      double gaee_flux = p4->gaee_flux->interpolate(erg);

      return temp*exposure*gaee_flux;
    }

    // Provides a customised interpolation container for the CAST likelihoods.
    class CAST_SolarModel_Interpolator
    {
      public:
        CAST_SolarModel_Interpolator(std::string solar_model_gagg, std::string solar_model_gaee, std::string data_set);
        CAST_SolarModel_Interpolator(CAST_SolarModel_Interpolator&&);
        ~CAST_SolarModel_Interpolator();
        // Delete copy constructor and assignment operator to avoid shallow copies
        CAST_SolarModel_Interpolator(const CAST_SolarModel_Interpolator&) = delete;
        CAST_SolarModel_Interpolator operator=(const CAST_SolarModel_Interpolator&) = delete;
        std::vector<double> evaluate_gagg_contrib(double m_ax);
        std::vector<double> evaluate_gaee_contrib(double m_ax);
     private:
        int n_bins;
        ASCIItableReader gagg_data;
        ASCIItableReader gaee_data;
        ASCIItableReader eff_exp_data;
        std::vector<gsl_interp_accel*> gagg_acc;
        std::vector<gsl_interp_accel*> gaee_acc;
        std::vector<gsl_spline*> gagg_linear_interp;
        std::vector<gsl_spline*> gaee_linear_interp;
    };

    // Class creators for CAST_SolarModel_Interpolator
    // Needs path to pre-claculated data for the "default" option.
    CAST_SolarModel_Interpolator::CAST_SolarModel_Interpolator(std::string solar_model_gagg, std::string solar_model_gaee, std::string data_set)
    {
      const std::string darkbitdata_path = GAMBIT_DIR "/DarkBit/data/";
      bool user_gagg_file_missing = true, user_gaee_file_missing = true;
      logger() << LogTags::info << "Using solar models '"+solar_model_gagg+"' (axion-photon int.) and '"+solar_model_gaee+"' (axion-electron int.) for experiment '"+data_set+"'." << EOM;

      // Check if a pre-computed a file for a given model exists.
      user_gagg_file_missing = not(Utils::file_exists(darkbitdata_path+"CAST/"+data_set+"_ReferenceCounts_"+solar_model_gagg+"_gagg.dat"));
      user_gaee_file_missing = not(Utils::file_exists(darkbitdata_path+"CAST/"+data_set+"_ReferenceCounts_"+solar_model_gaee+"_gaee.dat"));
      if (not(user_gagg_file_missing)) { logger() << LogTags::info << "Found pre-calculated axion-photon counts file for experiment '"+data_set+"' and solar model '"+solar_model_gagg+"'. Skipping calculation step..." << EOM; }
      if (not(user_gaee_file_missing)) { logger() << LogTags::info << "Found pre-calculated axion-electron counts file for experiment '"+data_set+"' and solar model '"+solar_model_gaee+"'. Skipping calculation step..." << EOM; }

      // If either file does not exists, compute it.
      if (user_gagg_file_missing || user_gaee_file_missing)
      {
        // Define the list of logarithmic masses log10(m_ax/keV) for the interpolating tables.
        const int n_mass_bins = 183;
        const double log_masses [n_mass_bins] = {-3., -2.8, -2.6, -2.4, -2.2, -2.15, -2.1, -2.05, -2., -1.95, -1.9, -1.85, -1.8475, -1.84, -1.8325, -1.825, -1.8175, -1.81, -1.8025, -1.795, -1.7875, -1.78, -1.7725, -1.765, -1.7575, -1.75,
                                                 -1.7425, -1.735, -1.7275, -1.72, -1.7125, -1.705, -1.6975, -1.69, -1.6825, -1.675, -1.6675, -1.66, -1.6525, -1.645, -1.6375, -1.63, -1.6225, -1.615, -1.6075, -1.6, -1.5925, -1.585, -1.5775, -1.57,
                                                 -1.5625, -1.555, -1.5475, -1.54, -1.5325, -1.525, -1.5175, -1.51, -1.5025, -1.495, -1.4875, -1.48, -1.4725, -1.465, -1.4575, -1.45, -1.4425, -1.435, -1.4275, -1.42, -1.4125, -1.405, -1.3975,
                                                 -1.39, -1.3825, -1.375, -1.3675, -1.36, -1.3525, -1.345, -1.3375, -1.33, -1.3225, -1.315, -1.3075, -1.3, -1.2925, -1.285, -1.2775, -1.27, -1.2625, -1.255, -1.2475, -1.24, -1.2325, -1.225, -1.2175,
                                                 -1.21, -1.2025, -1.195, -1.1875, -1.18, -1.1725, -1.165, -1.1575, -1.15, -1.1425, -1.135, -1.1275, -1.12, -1.1125, -1.105, -1.0975, -1.09, -1.0825, -1.075, -1.0675, -1.06, -1.0525, -1.045,
                                                 -1.0375, -1.03, -1.0225, -1.015, -1.0075, -1., -0.9925, -0.985, -0.9775, -0.97, -0.9625, -0.955, -0.9475, -0.94, -0.9325, -0.925, -0.9175, -0.91, -0.9025, -0.895, -0.8875, -0.88, -0.8725, -0.865,
                                                 -0.8575, -0.85, -0.8425, -0.835, -0.8275, -0.82, -0.8125, -0.805, -0.7975, -0.79, -0.7825, -0.775, -0.7675, -0.76, -0.7525, -0.745, -0.7375, -0.73, -0.7225, -0.715, -0.7075, -0.7, -0.65, -0.6,
                                                 -0.55, -0.5, -0.4, -0.2, 0., 0.2, 0.4, 0.6, 0.8, 1., 1.2, 1.4, 1.6, 1.8, 2.};

        // Define quantities specific to CAST and the data set.
        // prefactor_gagg = (keV/eV)^6 * (1 cm^2/eVcm^2) * (1 day/eVs) * (10^10 cm/eVcm) * (10^-19 eV^-1)^4 * ((9.26 m/eVm) * (9.0 T/(T/eV^2) ))^2 / (128 pi^3)
        const double prefactor_gagg = 29302.30262;
        // prefactor_gaee = 10^13 * (10^-19 eV^-1)^2 * ((9.26 m/eVm) * (9.0 T/(T/eV^2) ))^2 / 4
        // 10^13 = normalisation factor of files
        const double prefactor_gaee = 1.701818353e-4;
        // Lowest energy bin (in keV), bin size (in keV), and max. integration radius.
        double bin_lo = 2.0, bin_delta = 0.5, rs = 1.0;
        // Number of bins
        int n_bins = 10;
        if (data_set=="CAST2007") { bin_lo = 0.8; bin_delta = 0.3; rs = 0.231738; n_bins = 20; }

        // Arrays to store the results in.
        double gagg_counts [n_bins*n_mass_bins];
        double gaee_counts [n_bins*n_mass_bins];

        // Load the solar model.
        // Solar radius R_Sol and D_Sol (= 1 a.u.) in 10^10 cm.
        const double radius_sol = 6.9598, distance_sol = 1495.978707;
        double temp = prefactor_gagg*gsl_pow_2(radius_sol/distance_sol)*radius_sol;

        SolarModel model_gagg;
        if (user_gagg_file_missing)
        {
          if (Utils::file_exists(darkbitdata_path+"SolarModel_"+solar_model_gagg+".dat"))
          {
            model_gagg = SolarModel(darkbitdata_path+"SolarModel_"+solar_model_gagg+".dat");
          } else {
            DarkBit_error().raise(LOCAL_INFO, "ERROR! No solar model file found for '"+solar_model_gagg+"'.\n"
                                              "       Check 'DarkBit/data' for files named 'SolarModel_*.dat' for available options *.");
          }
        }

        // Load and interpolate effective exposure and the data for the axion-electron spectrum (with its nasty peaks).
        AxionInterpolator eff_exposure (darkbitdata_path+"CAST/"+data_set+"_EffectiveExposure.dat");
        AxionInterpolator gaee_spectrum;
        if (user_gaee_file_missing)
        {
          if (Utils::file_exists(darkbitdata_path+"CAST/"+"Axion_Spectrum_"+solar_model_gaee+"_gaee.dat"))
          {
            gaee_spectrum = AxionInterpolator(darkbitdata_path+"CAST/"+"Axion_Spectrum_"+solar_model_gaee+"_gaee.dat");
          } else {
            DarkBit_error().raise(LOCAL_INFO, "ERROR! No spectrum file found for axion-electron interactions and model '"+solar_model_gaee+"'.\n"
                                              "       Check 'DarkBit/data' for files named 'Axion_Spectrum_*_gaee.dat' for available options *.");
          }
        }
        double all_peaks [32] = {0.653029, 0.779074, 0.920547, 0.956836, 1.02042, 1.05343, 1.3497, 1.40807, 1.46949, 1.59487, 1.62314, 1.65075, 1.72461, 1.76286, 1.86037, 2.00007, 2.45281, 2.61233, 3.12669, 3.30616, 3.88237, 4.08163, 5.64394,
                                 5.76064, 6.14217, 6.19863, 6.58874, 6.63942, 6.66482, 7.68441, 7.74104, 7.76785};

        // Prepare integration routine by defining the gsl functions etc.
        gsl_function F;
        F.function = &erg_integrand;
        gsl_function G;
        G.function = &alt_erg_integrand;

        double erg_lo = bin_lo, erg_hi = bin_lo;

        logger() << LogTags::info << "Calculating reference counts for dataset '"+data_set+"'..." << EOM;
        #ifdef AXION_DEBUG_MODE
          std::cout << "DEBUGGING INFO for solar model integration:\n"
                       "Using model '"+solar_model_gagg+"' for axion-photon interactions,"
                       "and model '"+solar_model_gaee+"' for axion-electron interactions.\n\n"
                       "coupling log10(m/eV) [erg_low/keV, erg_high/keV] log10(counts)" << std::endl;
        #endif
        for (int bin = 0; bin < n_bins; bin++)
        {
          erg_lo = erg_hi;
          erg_hi += bin_delta;
          gsl_integration_workspace * v = gsl_integration_workspace_alloc (1E6);
          gsl_integration_workspace * w = gsl_integration_workspace_alloc (1E6);
          // Only take into account the peaks relevant for the current energy bin.
          std::vector<double> relevant_peaks;
          relevant_peaks.push_back(erg_lo);
          for (int i = 0; i < 32; i++)
          {
            double temp = all_peaks[i];
            if ( (erg_lo < temp) && (temp < erg_hi) ) { relevant_peaks.push_back(temp); }
          }
          relevant_peaks.push_back(erg_hi);

          for (int i = 0; i < n_mass_bins; i++)
          {
            double gagg_result, gagg_error, gaee_result, gaee_error;
            double m_ax = pow(10,log_masses[i]);
            // Only perform integration if axion-photon counts file does not exist.
            if (user_gagg_file_missing)
            {
              SolarModel_params3 p3 = {rs, m_ax, &model_gagg, &eff_exposure};
              F.params = &p3;
              gsl_integration_qag (&F, erg_lo, erg_hi, abs_prec, rel_prec, 1E6, method, v, &gagg_result, &gagg_error);

              #ifdef AXION_OMP_DEBUG_MODE
                printf("gagg | % 6.4f [%3.2f, %3.2f] % 4.3e\n", log10(m_ax), erg_lo, erg_hi, log10(temp*gagg_result));
              #endif

              gagg_counts[bin*n_mass_bins+i] = log10(temp*gagg_result);
            }
            // Only perform integration if axion-electron counts file does not exist.
            if (user_gaee_file_missing)
            {
              SolarModel_params4 p4 = {m_ax, &eff_exposure, &gaee_spectrum};
              G.params = &p4;
              gsl_integration_qagp(&G, &relevant_peaks[0], relevant_peaks.size(), abs_prec, rel_prec, 1E6, w, &gaee_result, &gaee_error);

              #ifdef AXION_OMP_DEBUG_MODE
                printf("gaee | % 6.4f [%3.2f, %3.2f] % 4.3e\n", log10(m_ax), erg_lo, erg_hi, log10(0.826*prefactor_gaee*gaee_result));
              #endif

              // Include efficiency factor from not integrating over the full Solar disc in CAST2007 here:
              if (data_set=="CAST2007") { gaee_result = 0.826*gaee_result; }
              gaee_counts[bin*n_mass_bins+i] = log10(prefactor_gaee*gaee_result);
            }
          }
          gsl_integration_workspace_free (v);
          gsl_integration_workspace_free (w);
        }


        // Write the results to a file (if the file does not yet exist).
        if (user_gagg_file_missing)
        {
          std::string header = "########################################################################\n"
                               "# Reference Counts for Solar Model "+solar_model_gagg+std::string(std::max(0,36-static_cast<int>(solar_model_gagg.length())),' ')+"#\n"
                               "# Column 1: log10(Axion mass in eV)                                    #\n"
                               "#        n>1: log10(Reference photon counts in energy bin n-1)         #\n"
                               "########################################################################\n";
          std::ofstream gagg_file (darkbitdata_path+"CAST/"+data_set+"_ReferenceCounts_"+solar_model_gagg+"_gagg.dat");
          gagg_file << header;
          gagg_file << std::fixed << std::scientific << std::setprecision(7);
          for (int i = 0; i < n_mass_bins; i++)
          {
            gagg_file << log_masses[i];
            for (int j = 0; j < n_bins; j++) { gagg_file << " " << gagg_counts[j*n_mass_bins+i]; }
            if (i < n_mass_bins-1) { gagg_file << "\n"; }
          }
          gagg_file.close();
          logger() << LogTags::info << "Output file '"+darkbitdata_path+"CAST/"+data_set+"_ReferenceCounts_"+solar_model_gagg+"_gagg.dat"+"' written for axion-photon interactions." << EOM;
        }

        if (user_gaee_file_missing)
        {
          std::string header = "########################################################################\n"
                               "# Reference Counts for Solar Model "+solar_model_gaee+std::string(std::max(0,36-static_cast<int>(solar_model_gaee.length())),' ')+"#\n"
                               "# Column 1: log10(Axion mass in eV)                                    #\n"
                               "#        n>1: log10(Reference photon counts in energy bin n-1)         #\n"
                               "########################################################################\n";
          std::ofstream gaee_file (darkbitdata_path+"CAST/"+data_set+"_ReferenceCounts_"+solar_model_gaee+"_gaee.dat");
          gaee_file << header;
          gaee_file << std::fixed << std::scientific << std::setprecision(7);
          for (int i = 0; i < n_mass_bins; i++)
          {
            gaee_file << log_masses[i];
            for (int j = 0; j < n_bins; j++) { gaee_file << " " << gaee_counts[j*n_mass_bins+i]; }
            if (i < n_mass_bins-1) { gaee_file << "\n"; }
          }
          gaee_file.close();
          logger() << LogTags::info << "Output file '"+darkbitdata_path+"CAST/"+data_set+"_ReferenceCounts_"+solar_model_gaee+"_gagg.dat"+"' written for axion-electron interactions." << EOM;
        }
      }

      // Read in pre-integrated fluxes for the chosen models.
      // 0-entry = mass values; remaining entries = counts in bins.
      gagg_data = ASCIItableReader(darkbitdata_path+"CAST/"+data_set+"_ReferenceCounts_"+solar_model_gagg+"_gagg.dat");
      gaee_data = ASCIItableReader(darkbitdata_path+"CAST/"+data_set+"_ReferenceCounts_"+solar_model_gaee+"_gaee.dat");
      n_bins = gagg_data.getncol() - 1;

      // Point to the address of the first entry of masses.
      const double* mass_gagg = &gagg_data[0][0];
      const double* mass_gaee = &gaee_data[0][0];

      for (int bin = 0; bin < n_bins; bin++)
      {
        // Determine the number of interpolated mass values.
        int gagg_pts = gagg_data[bin+1].size();
        int gaee_pts = gaee_data[bin+1].size();
        gagg_acc.push_back( gsl_interp_accel_alloc () );
        gaee_acc.push_back( gsl_interp_accel_alloc () );
        gagg_linear_interp.push_back( gsl_spline_alloc (gsl_interp_linear, gagg_pts) );
        gaee_linear_interp.push_back( gsl_spline_alloc (gsl_interp_linear, gaee_pts) );
        // Get flux values and initialise splines.
        const double* flux_gagg = &gagg_data[bin+1][0];
        const double* flux_gaee = &gaee_data[bin+1][0];
        gsl_spline_init (gagg_linear_interp[bin], mass_gagg, flux_gagg, gagg_pts);
        gsl_spline_init (gaee_linear_interp[bin], mass_gaee, flux_gaee, gaee_pts);
      }
    }

    // Move constructor
    CAST_SolarModel_Interpolator::CAST_SolarModel_Interpolator(CAST_SolarModel_Interpolator &&interp) :
      n_bins(std::move(interp.n_bins)),
      gagg_data(std::move(interp.gagg_data)),
      gaee_data(std::move(interp.gaee_data)),
      eff_exp_data(std::move(interp.eff_exp_data)),
      gagg_acc(std::move(interp.gagg_acc)),
      gaee_acc(std::move(interp.gaee_acc)),
      gagg_linear_interp(std::move(interp.gagg_linear_interp)),
      gaee_linear_interp(std::move(interp.gaee_linear_interp))
    {}

    // Class destructor
    CAST_SolarModel_Interpolator::~CAST_SolarModel_Interpolator()
    {
      for(auto gagg_li : gagg_linear_interp)
        gsl_spline_free (gagg_li);
      for(auto gagg_ac : gagg_acc)
        gsl_interp_accel_free (gagg_ac);
      for(auto gaee_li : gaee_linear_interp)
        gsl_spline_free (gaee_li);
      for(auto gaee_ac : gaee_acc)
        gsl_interp_accel_free (gaee_ac);

    }

    // Returns reference value counts for the photon-axion contribution.
    std::vector<double> CAST_SolarModel_Interpolator::evaluate_gagg_contrib(double m_ax)
    {
      std::vector<double> result;
      double lgm = log10(m_ax);
      // If m < 0.001 eV, just return the result for the result for the coherent limit.
      lgm = std::max(-3.0, lgm);
      // Only perform a calculation for valid masses.
      if (lgm < 2.0)
      {
        for (int i = 0; i < n_bins; i++) { result.push_back(gsl_spline_eval(gagg_linear_interp[i], lgm, gagg_acc[i])); }
      } else {
        for (int i = 0; i < n_bins; i++) { result.push_back(0.0); }
      }

      return result;
    }

    // Returns reference value counts for the photon-axion contribution.
    std::vector<double> CAST_SolarModel_Interpolator::evaluate_gaee_contrib(double m_ax)
    {
      std::vector<double> result;
      double lgm = log10(m_ax);
      // If m < 0.001 eV, just return the result for the result for the coherent limit.
      lgm = std::max(-3.0, lgm);
      // Only perform a calculation for valid masses.
      if (lgm < 2.0)
      {
        for (int i = 0; i < n_bins; i++) { result.push_back(gsl_spline_eval(gaee_linear_interp[i], lgm, gaee_acc[i])); }
      } else {
        for (int i = 0; i < n_bins; i++) { result.push_back(0.0); }
      }

      return result;
    }

    // Use simplified version of Gaussian likelihood from GAMBIT Utils.
    double gaussian_nuisance_lnL(double theo, double obs, double sigma) { return Stats::gaussian_loglikelihood(theo, obs, 0, sigma, false); }

    ////////////////////////////////////////////////////////
    //                                                    //
    //            Miscellaneous Theory Results            //
    //                                                    //
    ////////////////////////////////////////////////////////

    /*! \brief Various capabilities and functions to provide SM physics as well as QCD input for axions.
     *
     * Supported models: QCDAxion
     */

    ////////////////////////////////////////////////////////
    //      Effective relatvistic degrees of freedom      //
    ////////////////////////////////////////////////////////

    // Function to provide the effective relativistic degrees of freedom (for the Standard Model).
    double gStar(double T)
    {
      // Needs log10(T/GeV) for interpolation.
      double lgT = log10(T) - 3.0;
      // Interpolated effective relatvistic d.o.f. based on 0910.1066, deviations < 0.5%
      // Tabulated data: x = log10(T/GeV), y = gStar
      static AxionInterpolator gR (GAMBIT_DIR "/DarkBit/data/gR_WantzShellard.dat", InterpolationOptions1D::cspline);
      double res;
      if (lgT > 3.0) {
        res = gR.interpolate (2.99);
      } else if (lgT < -5.0) {
        res = gR.interpolate (-4.99);
      } else {
        res = gR.interpolate (lgT);
      }

      return res;
    }

    // Function to provide the effective relativistic entropic degrees of freedom (for the Standard Model).
    double gStar_S(double T)
    {
      // Need log10(T/GeV) for interpolation.
      double lgT = log10(T) - 3.0;
      // Interpolated effective relatvistic d.o.f. based on 0910.1066, deviations < 0.5%
      // Tabulated data: x = log10(T/GeV), y = gStar
      static AxionInterpolator gS (GAMBIT_DIR "/DarkBit/data/gS_WantzShellard.dat", InterpolationOptions1D::cspline);
      double res;
      if (lgT > 3.0) {
        res = gS.interpolate (2.99);
      } else if (lgT < -5.0) {
        res = gS.interpolate (-4.99);
      } else {
        res = gS.interpolate (lgT);
      }

      return res;
    }

    ///////////////////////////////////////
    //      QCD-axion mass relation      //
    ///////////////////////////////////////

    // Capability function to provide a simple Gaussian nuisance likelihood for
    // the zero-termperature mass of QCD axions.
    void QCDAxion_ZeroTemperatureMass_Nuisance_lnL(double &result)
    {
      using namespace Pipes::QCDAxion_ZeroTemperatureMass_Nuisance_lnL;
      double LambdaChi = *Param["LambdaChi"];

      // Results from NLO calculations (1511.02867).
      const double Lmu = 75.5;
      const double Lsigma = 0.5;

      result = gaussian_nuisance_lnL(Lmu, LambdaChi, Lsigma);
    }

    // Capability function to provide a simple Gaussian nuisance likelihood for
    // the model-independent contribution to the axion-photon coupling for QCD axions.
    void QCDAxion_AxionPhotonConstant_Nuisance_lnL(double &result)
    {
      using namespace Pipes::QCDAxion_AxionPhotonConstant_Nuisance_lnL;
      double CaggQCD = *Param["CaggQCD"];

      // Results from NLO calculations (1511.02867).
      const double CaggQCDmu = 1.92;
      const double CaggQCDsigma = 0.04;

      result = gaussian_nuisance_lnL(CaggQCDmu, CaggQCD, CaggQCDsigma);
    }

    // Auxillary function for QCD nuisance likelihood below.
    double log_chi (double T, double beta, double Tchi)
    {
      double result = 0.0;
      if (T > Tchi) { result = -beta*log10(T/Tchi); }

      return result;
    }

     // Capability function to provide a lieklihood for the temperature dependence of the QCD axion mass (doi:10.1038/nature20115).
     void QCDAxion_TemperatureDependence_Nuisance_lnL(double &result)
     {
       using namespace Pipes::QCDAxion_TemperatureDependence_Nuisance_lnL;
       double Tchi = *Param["Tchi"];
       double beta = *Param["beta"];

       // Results from lattice QCD (doi:10.1038/nature20115, Supplementary Material).
       // We normalised their findings by dividing out their value for chi(T=0) and removed its contribution to the error.
       const double temp_vals [20] = {100, 120, 140, 170, 200, 240, 290, 350, 420, 500, 600, 720, 860, 1000, 1200, 1500, 1800, 2100, 2500, 3000};
       const double log_chi_vals [20] = {0.00554625, 0.0255462, -0.0844538, -0.484454, -1.00445, -1.75445, -2.45445, -3.07445, -3.66445, -4.22445, -4.80445, -5.39445, -5.96445, -6.45445, -7.05445, -7.79445, -8.40445, -8.93445, -9.53445, -10.1545};
       const double log_chi_err_vals [20] = {0.014468, 0.0361846, 0.014468, 0.014468, 0.064104, 0.064104, 0.0510815, 0.0361846, 0.0510815, 0.064104, 0.0878027, 0.110042, 0.142159, 0.163124, 0.183873, 0.224965, 0.255557, 0.286023, 0.316401, 0.356804};

       double dummy = 0.0;
       for (int i = 0; i < 20; i++) { dummy = dummy + gaussian_nuisance_lnL(log_chi_vals[i], log_chi(temp_vals[i],beta,Tchi), log_chi_err_vals[i]); }

       result = dummy;
     }

    /////////////////////////////////////////////
    //                                         //
    //            Axion Experiments            //
    //                                         //
    /////////////////////////////////////////////

    /*! \brief Likelihoods for ALPS 1 (LSW), CAST (helioscopes), and ADMX, UF, RBF (haloscopes).
     *
     * Supported models: GeneralALP
     */

    /////////////////////////////////
    //      ALPS 1 experiment      //
    /////////////////////////////////

    // Generic functions to calculate the expected signal per frame(!) for any data run.
    // Input: laser power, gas coefficient nm1 = n-1; result in no. of photons.
    double ALPS1_signal_general(double power, double nm1, double m_ax, double gagg)
    {
      const double eVm = gev2cm*1E7;
      // Photon energy in eV.
      const double erg = 2.0*pi*eVm/532.0E-9;
      const double len = 4.2;
      // We include the uncertainty of the detection efficiency eff = 0.82(5) in the likelihood.
      const double eff = 0.82;

      double result = 0.0;

      // CAVE: Approximations/conversion only valid/possible for m_ax << 2.33 eV (532 nm).
      if (m_ax < 1.0)
      {
        // Effective photon mass and momentum transfer.
        double m_ph_sq = 2.0*erg*erg*nm1;
        double q = 0.5*(m_ax*m_ax+m_ph_sq)/(eVm*erg);
        double factor = gsl_pow_4((gagg*1E17)*gsl_sf_sinc(0.5*q*len/pi));

        // Prefactor: 1096 W * 1 h * (10^-17/eV * 4.98 T * 4.2 m)^4 / 16.
        result = 0.00282962979*eff*factor*(power/1096.0)/erg;
      }

      return result;
    }

    // Specific capability to provide the expected signal from data run 1 (5 data frames).
    void calc_ALPS1_signal_vac(double &result)
    {
      using namespace Pipes::calc_ALPS1_signal_vac;
      double m_ax = *Param["ma0"];
      double gagg = gagg_conversion*std::fabs(*Param["gagg"]); // gagg needs to be in eV^-1.

      result = ALPS1_signal_general(1096.0, 0.0, m_ax, gagg);
    }

    // Specific capability to provide the expected signal from data run 3 (8 data frames; 0.18 mbar).
    void calc_ALPS1_signal_gas(double &result)
    {
      using namespace Pipes::calc_ALPS1_signal_gas;
      double m_ax = *Param["ma0"];
      double gagg = gagg_conversion*std::fabs(*Param["gagg"]); // gagg needs to be in eV^-1.

      result = ALPS1_signal_general(1044.0, 5.0E-8, m_ax, gagg);
    }

    // General likelihood function for the ALPS 1 experiment (given expected signal s = obs - bkg).
    double ALPS1_lnL_general(double s, double mu, double sigma)
    {
      // Propagate uncertainty from efficiency in chi^2-likelihood.
      const double rel_error = 0.05/0.82;
      return -0.5*gsl_pow_2(s-mu)/(gsl_pow_2(rel_error*s)+gsl_pow_2(sigma));
    }

    // Capability to provide joint liklihood for all three data runs.
    void calc_lnL_ALPS1(double &result)
    {
      using namespace Pipes::calc_lnL_ALPS1;
      double s1 = *Dep::ALPS1_signal_vac;
      double s2 = *Dep::ALPS1_signal_gas;

      // ALPS Collaboration results (limits from this data published in 1004.1313).
      // ALPS Collaboration results, vacuum, 5 frames.
      const double exp_sig_mu_v1 = -4.01, exp_sig_std_v1 = 3.01;
      // ALPS Collaboration results, vacuum, 6 frames.
      const double exp_sig_mu_v2 = -2.35, exp_sig_std_v2 = 3.44;
      // ALPS Collaboration results, vacuum combined(!), 11 frames (we keep them seperated).
      //const double exp_sig_mu_vc = -3.29, exp_sig_std_vc = 2.27;
      // ALPS Collaboration results, gas, 8 frames (P = 0.18 mbar).
      const double exp_sig_mu_g = 3.98, exp_sig_std_g = 2.45;

      double l1 = ALPS1_lnL_general(s1, exp_sig_mu_v1, exp_sig_std_v1);
      double l2 = ALPS1_lnL_general(s1, exp_sig_mu_v2, exp_sig_std_v2);
      double l3 = ALPS1_lnL_general(s2, exp_sig_mu_g, exp_sig_std_g);

      result = l1 + l2 + l3;
    }

    //////////////////////////////////////////////////
    //      CAST experiment (vacuum runs only)      //
    //////////////////////////////////////////////////

    // Calculates the signal prediction for the CAST experiment (CCD detector 2004).
    void calc_CAST2007_signal_vac(std::vector<double> &result)
    {
      using namespace Pipes::calc_CAST2007_signal_vac;
      double m_ax = *Param["ma0"];
      double gagg = gagg_conversion*std::fabs(*Param["gagg"]); // gagg needs to be in eV^-1.
      double gaee = std::fabs(*Param["gaee"]);

      // Initialise the Solar model calculator and get the reference counts for a given mass.
      // Get Solar model we are working with; set default value here
      static std::string solar_model_gagg = runOptions->getValueOrDef<std::string> ("AGSS09met", "solar_model_gagg");
      static std::string solar_model_gaee = runOptions->getValueOrDef<std::string> ("AGSS09met_old", "solar_model_gaee");
      static CAST_SolarModel_Interpolator lg_ref_counts (solar_model_gagg, solar_model_gaee, "CAST2007");
      std::vector<double> lg_ref_counts_gagg = lg_ref_counts.evaluate_gagg_contrib(m_ax);
      std::vector<double> lg_ref_counts_gaee = lg_ref_counts.evaluate_gaee_contrib(m_ax);
      static int n_bins = lg_ref_counts_gagg.size();

      std::vector<double> counts;
      double dummy;
      for (int i = 0; i < n_bins; i++)
      {
        dummy = gsl_pow_2(gagg*1E19)*pow(10,lg_ref_counts_gagg[i]) + gsl_pow_2(gaee*gaee_conversion)*pow(10,lg_ref_counts_gaee[i]);
        counts.push_back(gsl_pow_2(gagg*1E19)*dummy);
      }

      result = counts;
    }

    // Calculates the signal prediction for the CAST experiment (all detectors in 1705.02290)
    void calc_CAST2017_signal_vac(std::vector<std::vector<double>> &result)
    {
      using namespace Pipes::calc_CAST2017_signal_vac;
      double m_ax = *Param["ma0"];
      double gagg = gagg_conversion*std::fabs(*Param["gagg"]); // gagg needs to be in eV^-1.
      double gaee = std::fabs(*Param["gaee"]);
      std::vector<std::vector<double>> res;

      // Initialise the Solar model calculator and get the reference counts for a given mass.
      // Get Solar model we are working with; set default value here
      static std::string solar_model_gagg = runOptions->getValueOrDef<std::string> ("AGSS09met", "solar_model_gagg");
      static std::string solar_model_gaee = runOptions->getValueOrDef<std::string> ("AGSS09met_old", "solar_model_gaee");

      const int n_exps = 12;
      const int n_bins = 10;
      const std::string exp_names [n_exps] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L"};
      static std::vector<CAST_SolarModel_Interpolator> lg_ref_counts;
      static bool lg_ref_counts_not_calculated = true;
      if (lg_ref_counts_not_calculated)
      {
        for (int e = 0; e < n_exps; e++)
        {
          CAST_SolarModel_Interpolator dummy (solar_model_gagg, solar_model_gaee, "CAST2017_"+exp_names[e]);
          lg_ref_counts.push_back(std::move(dummy));
        }
      }
      lg_ref_counts_not_calculated = false;

      for (int e = 0; e < n_exps; e++)
      {
        std::vector<double> lg_ref_counts_gagg = lg_ref_counts[e].evaluate_gagg_contrib(m_ax);
        std::vector<double> lg_ref_counts_gaee = lg_ref_counts[e].evaluate_gaee_contrib(m_ax);

        std::vector<double> counts;
        double dummy;
        for (int bin = 0; bin < n_bins; bin++)
        {
          dummy = gsl_pow_2(gagg*1E19)*pow(10,lg_ref_counts_gagg[bin]) + gsl_pow_2(gaee*gaee_conversion)*pow(10,lg_ref_counts_gaee[bin]);
          counts.push_back(gsl_pow_2(gagg*1E19)*dummy);
        }

        res.push_back(counts);
      }

      result = res;
    }

    // General binned Poisson likelihood for the CAST experiment.
    double CAST_lnL_general(std::vector<double> s, const std::vector<double> bkg_counts, const std::vector<int> sig_counts)
    {
      double result = 0.0;
      int n_bins = s.size();

      for (int i = 0; i < n_bins; i++)
      {
        double mu = s[i] + bkg_counts[i];
        result += sig_counts[i]*gsl_sf_log(mu) - mu;
      }

      return result;
    }

    // Capability to provide CAST likelihood for hep-ex/0702006 .
    void calc_lnL_CAST2007(double &result)
    {
      using namespace Pipes::calc_lnL_CAST2007;
      std::vector<double> sig_vac = *Dep::CAST2007_signal_vac;

      // CAST CCD 2004 vacuum data (based on hep-ex/0702006).
      const int n_bins = 20;
      const std::vector<int> dat_vac {1, 3, 1, 1, 1, 2, 1, 2, 0, 2, 0, 1, 0, 2, 2, 0, 2, 1, 2, 2};
      const std::vector<double> bkg_vac {2.286801272, 1.559182673, 2.390746817, 1.559182673, 2.598637835, 1.039455092, 0.727618599, 1.559182673, 1.247346181, 1.455237199, 1.871019235, 0.831564073, 1.663128217, 1.247346181, 1.143400636, 1.663128217,
                                         1.247346181, 1.247346181, 2.286801272, 1.247346181};

      // Only calculate norm once.
      static double norm = 0.0;
      static bool norm_not_calculated = true;
      if (norm_not_calculated)
      {
        for (int i = 0; i < n_bins; i++) { norm += gsl_sf_lnfact(dat_vac[i]); }
      }
      norm_not_calculated = false;

      result = CAST_lnL_general(sig_vac, bkg_vac, dat_vac) - norm;
    }

    // Capability to provide CAST likelihood for 1705.02290 .
    void calc_lnL_CAST2017(double &result)
    {
      using namespace Pipes::calc_lnL_CAST2017;
      std::vector<std::vector<double>> sig_vac = *Dep::CAST2017_signal_vac;

      // CAST 2017 vacuum data (naming scheme based on the 10 data sets published in 1705.02290).
      const int n_bins = 10;
      const int n_exps = 12;

      const std::vector<std::vector<int>> dat_vac_all { {0, 3, 3, 0, 0, 1, 3, 3, 3, 3},
                                                        {5, 5, 5, 3, 3, 0, 5, 2, 2, 1},
                                                        {3, 3, 1, 2, 2, 2, 4, 5, 4, 3},
                                                        {1, 5, 5, 2, 1, 2, 2, 5, 4, 0},
                                                        {2, 3, 2, 2, 2, 1, 0, 2, 1, 1},
                                                        {3, 5, 1, 4, 1, 2, 0, 3, 2, 2},
                                                        {3, 4, 4, 5, 1, 2, 3, 2, 3, 2},
                                                        {2, 1, 0, 1, 3, 2, 2, 3, 0, 1},
                                                        {1, 2, 2, 1, 3, 0, 0, 1, 4, 0},
                                                        {2, 1, 3, 1, 1, 0, 1, 1, 5, 5},
                                                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                        {0, 2, 1, 0, 0, 0, 0, 0, 0, 0} };

      const std::vector<std::vector<double>> bkg_vac_all { {0.926256, 1.96148, 1.79803, 1.30766, 1.30766, 1.96148, 2.61531, 2.77877, 2.94223, 2.07045},
                                                           {3.68151, 4.86486, 4.99634, 3.55003, 2.49817, 3.28707, 2.89262, 3.68151, 3.48429, 3.41855},
                                                           {2.54573, 3.18216, 4.45502, 2.86394, 2.29116, 2.29116, 3.30945, 3.75495, 3.62766, 3.56402},
                                                           {2.72482, 5.5794, 3.95748, 2.40044, 2.27069, 2.33556, 3.37359, 3.43847, 3.24384, 3.11408},
                                                           {1.44613, 2.30066, 2.43213, 1.70906, 1.97199, 1.24893, 1.24893, 2.23493, 2.16919, 2.23493},
                                                           {1.30963, 2.94666, 2.35733, 2.55377, 2.02992, 1.50607, 2.16088, 2.75022, 2.29185, 2.29185},
                                                           {2.33334, 2.74167, 2.21667, 2.80001, 2.21667, 1.75001, 2.62501, 2.21667, 2.80001, 2.33334},
                                                           {1.74724, 2.37125, 2.68326, 1.62243, 2.05924, 1.74724, 1.49763, 1.74724, 1.18563, 2.24645},
                                                           {1.72998, 3.45995, 1.79405, 1.72998, 1.9222, 1.72998, 2.69107, 2.24256, 1.98627, 2.11442},
                                                           {1.89627, 2.25182, 2.96292, 1.4222, 1.65924, 1.65924, 1.95553, 2.1333, 1.71849, 2.07404},
                                                           {0.0150685, 0.0568493, 0.060274, 0.0150685, 0.0150685, 0.00753425, 0.0267123, 0.0150685, 0.0267123, 0.0116438},
                                                           {0.0409574, 0.226904, 0.243287, 0.0532447, 0.0188404, 0.0344043, 0.0417766, 0.0409574, 0.0409574, 0.0286702} };

      // Only calculate norm once.
      static double norm = 0.0;
      static bool norm_not_calculated = true;
      if (norm_not_calculated)
      {
        for (int bin = 0; bin < n_bins; bin++)
        {
          for (int e = 0; e < n_exps; e++) { norm += gsl_sf_lnfact(dat_vac_all[e][bin]); }
        }
      }
      norm_not_calculated = false;

      result = 0.0;
      for (int e = 0; e < n_exps; e++) { result = result + CAST_lnL_general(sig_vac[e], bkg_vac_all[e], dat_vac_all[e]); }
      result = result - norm;
    }

    /////////////////////////////////////////////
    //      Various haloscope experiments      //
    /////////////////////////////////////////////

    // Capability to provide generic haloscope "signal" prediction.
    // All current haloscope likelihoods are approximated. We only need the predicted signal power up to a constant of proportionality.
    void calc_Haloscope_signal(double &result)
    {
      using namespace Pipes::calc_Haloscope_signal;
      double gagg = gagg_conversion*std::fabs(*Param["gagg"]); // gagg needs to be in eV^-1.
      // Get the DM fraction in axions and the local DM density.
      double fraction = *Dep::RD_fraction;
      LocalMaxwellianHalo LocalHaloParameters = *Dep::LocalHalo;
      double rho0 = LocalHaloParameters.rho0;

      // Signal relative to a reference coupling and local DM density.
      double s = gsl_pow_2(gagg/1.0E-24) * fraction * (rho0/0.45);

      result = s;
    }

    /*! Approximated likelihood for the AxionDarkMatterEXperiment (ADMX).
    */

    // ADMX approximated likelihood function for data from publications from 1998 to 2009.
    void calc_lnL_Haloscope_ADMX1(double &result)
    {
      using namespace Pipes::calc_lnL_Haloscope_ADMX1;
      double m_ax = *Param["ma0"];
      // Calculate equivalent frequency in MHz.
      const double eV_to_MHz = 1.0E-15/(2.0*pi*hbar);
      double freq = m_ax*eV_to_MHz;
      double l = 0.0;
      // Initialise GSL histogram and flag.
      static gsl_histogram *h = gsl_histogram_alloc(89);
      static bool init_flag = false;

      // Unless initialised already, read in digitised limits from 0910.5914.
      if (not(init_flag))
      {
        FILE * f = fopen(GAMBIT_DIR "/DarkBit/data/ADMXLimitsHistogram.dat", "r");
        gsl_histogram_fscanf (f, h);
        fclose(f);
        init_flag = true;
      }

      // Likelihood shape parameters based on limits from astro-ph/9801286.
      const double a = 0.013060890;
      const double b = 0.455482976;

      if ((freq > gsl_histogram_min(h)) && (freq < gsl_histogram_max(h)))
      {
        size_t index;
        gsl_histogram_find(h, freq, &index);
        double s     = *Dep::Haloscope_signal;
        double s_ref = gsl_pow_2(gsl_histogram_get(h, index));
        double s_rel = s/s_ref;
        // Only apply contraints for a signal > threshold a.
        if (s_rel > a) { l = -0.5 * gsl_pow_2( (s_rel - a)/b ); }
      }

      result = l;
    }

    // ADMX approximated likelihood function for data from 2018 paper (1804.05750).
    void calc_lnL_Haloscope_ADMX2(double &result)
    {
      using namespace Pipes::calc_lnL_Haloscope_ADMX2;
      // Rescale the axion mass to ueV.
      double m_ax = 1.0E+6*(*Param["ma0"]);
      double l = 0.0;

      // ADMX 2018 90% C.L. exclusion limits; digitised from Fig. 4, 1804.05750.
      static AxionInterpolator g_limits (GAMBIT_DIR "/DarkBit/data/ADMX2018Limits.dat");

      // If we are within the avialable data range, calculate the limit.
      if ( (m_ax > g_limits.lower()) && (m_ax < g_limits.upper()) )
      {
        double s = *Dep::Haloscope_signal;
        // Get limit and rescale it to 1 sigma from the appropriate number of sigmas for 90% C.L. (1 d.o.f.).
        double sigma_exp = gsl_pow_2(g_limits.interpolate(m_ax))/1.644817912489;
        // Add systematics of 13% according to 1804.05750.
        double var_exp = gsl_pow_2(sigma_exp);
        double var_theo = gsl_pow_2(0.13*s);
        double var_tot = var_exp + var_theo;
        l = -0.5*gsl_pow_2(s)/var_tot;
      }

      result = l;
    }

    // University of Florida (UF) approximated likelihood function; Hagmann+ Phys. Rev. D 42, 1297(R) (1990).
    void calc_lnL_Haloscope_UF(double &result)
    {
      using namespace Pipes::calc_lnL_Haloscope_UF;
      // Rescale the axion mass to ueV.
      double m = 1.0E+6*(*Param["ma0"]);
      double l = 0.0;

      // There are only limits between 5.4 and 5.9 ueV.
      if ((m > 5.4) && (m < 5.9)) {
        // Likelihood parameters based on information from Phys. Rev. D 42, 1297(R) (1990); correspond to power in 10^-22 W.
        const double sigma = 2.859772;
        // The "signal" needs to be rescaled to 0.2804 GeV/cm^3 (their reference value)
        // and also to the reference DFSZ coupling strength gDFSZ^2 = 0.6188 x 10^-30 GeV^-2
        // const double PowerDFSZ = 6.92;
        //double s = (0.45/0.2804)*(PowerDFSZ/0.6188)*(*Dep::Haloscope_signal);
        //double s = 0.035083106*(0.45/0.2804)*(*Dep::Haloscope_signal);
        double s = 0.0273012*(*Dep::Haloscope_signal);
        l = -0.5 * gsl_pow_2(s/sigma);
      }

      result = l;
    }

    // Rochester-Brookhaven-Fermi (RBF) approximated likelihood function; Phys. Rev. D 40, 3153 (1989).
    void calc_lnL_Haloscope_RBF(double &result)
    {
      using namespace Pipes::calc_lnL_Haloscope_RBF;
      // Rescale the axion mass to ueV.
      double m = 1.0E+6*(*Param["ma0"]);
      double l = 0.0;
      // Results from Phys. Rev. D 40, 3153 (1989)
      // The bins and results below (from Table I) appear to be inconsitent with Figure 14.
      //const std::vector<double> bins = {4.507875, 5.037241, 5.459079, 5.851967, 5.996715, 6.257262, 6.617065, 6.976868, 7.113345, 7.295314, 7.857765, 8.631134, 8.684898, 9.259755, 9.760171, 10.173737,
      //                                  11.298638, 11.583999, 12.845377, 13.234130, 15.301962, 16.2655809};
      // N_sigma values as defined in the paper.
      //const double N_sigma [21] = {5.0, 5.0, 5.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 0.0, 5.0, 4.0, 4.0, 4.0, 4.0};
      // Proportionality factors ("sigma") inferred from Table I in in units of GeV^-1/cm^3.
      //const double eff_sigma [21] = {8.3030524510E+01, 3.5789241789E+02, 5.3457189090E+02, 8.3673921774E+02, 7.3205267295E+02, 7.1850356207E+02, 7.0099211538E+02, 9.3243407987E+02, 1.3132694610E+03, 1.9447760075E+03, 2.4028734743E+03,
      //                               3.5992849457E+03, 5.8433323192E+03, 1.2415907565E+03, 1.1487509033E+03, 1.0000000000E+99, 2.6768234439E+03, 9.1546564260E+04, 1.7208310692E+04, 4.2462784870E+04, 2.8794160844E+04};
      // The results below are derived from Fig. 14 (assuming N_sigma = 4 for all values).
      const std::vector<double> bins = {4.400841, 4.960600, 5.209095, 5.668611, 6.934590, 7.445686, 8.041207, 8.898392, 9.570607, 10.067396, 11.213613, 11.626834, 12.773085, 13.450179, 14.704884, 16.170394};
      const double N_sigma = 4.0;
      const double eff_sigma [15] = {7.794388E+01, 3.808827E+02, 5.328136E+02, 6.765588E+02, 1.772892E+03, 2.752458E+03, 5.945156E+03, 2.025315E+03, 1.546855E+03, 1.022957E+13, 5.464075E+03, 9.621171E+04, 2.023187E+04, 5.201449E+04, 3.597168E+04};

      // Likelihood shape parameters based on information from PRD 40 (1989) 3153.
      // Note that there are no limits between 10.1 and 11.2 ueV; the tabulated value in that bin is just a placeholder, which is never used.
      if ( ((m > bins.front()) && (m < 10.067396)) || ((m > 11.213613) && (m < bins.back())))
      {
        // Use the standard search algorthim to identify the bin index and use the appropriate values for the likelihood.
        auto index = upper_bound(bins.begin(), bins.end(), m);
        double sigma = eff_sigma[index-bins.begin()-1];
        // Uncomment and comment out lines below to swap between implementations using Table I and Figure 14, respectively.
        //double offset = sigma*N_sigma[index-bins.begin()-1];
        double offset = sigma*N_sigma;
        // The "signal" needs to be rescaled to 0.3 GeV/cm^3, which is their reference value.
        double s = (0.45/0.3)*(*Dep::Haloscope_signal);
        if (s > offset) {
          l = -0.5 * gsl_pow_2( (s - offset)/sigma );
        }
      }

      result = l;
    }

    ///////////////////////////////////////////
    //                                       //
    //            Axion Cosmology            //
    //                                       //
    ///////////////////////////////////////////

    /*! \brief Capabilities relating to axion cosmology. Currently only provides the energy density in axions today due to the realignment mechanism.
     *
     * Supported models: GeneralALP
     */

    //////////////////////////////////////////////////////////
    //      Energy density in realignment axions today      //
    //////////////////////////////////////////////////////////

    /* Some auxillary functions for solving the  necessary differential equations
     */

    // Provides function F1 for the change in variables time -> temperature (see 1810.07192).
    double SpecialFun1(double T)
    {
      // log10(T/GeV) required for interpolation.
      double lgT = log10(T) - 3.0;
      // Tabulated data: x = log10(T/GeV), y = F1(T); gR and gS from 0910.1066 .
      static AxionInterpolator F1 (GAMBIT_DIR "/DarkBit/data/Axion_DiffEqnFun1.dat", InterpolationOptions1D::linear);
      double res = -1.0;
      if ((lgT > 3.0) && (lgT < -5.0)) { res = F1.interpolate (lgT); }
      return res;
    }

    // Provides function F3 for the change in variables time -> temperature (see 1810.07192).
    double SpecialFun3(double T)
    {
      // log10(T/GeV) required for interpolation.
      double lgT = log10(T) - 3.0;
      // Tabulated data: x = log10(T/GeV), y = F3(T); gR and gS from 0910.1066 .
      static AxionInterpolator F3 (GAMBIT_DIR "/DarkBit/data/Axion_DiffEqnFun3.dat", InterpolationOptions1D::linear);
      double res = 0.0;
      if ((lgT > 3.0) && (lgT < -5.0)) { res = F3.interpolate (lgT); }
      return res;
    }

    // Auxillary function to calculate the Hubble parameter in a radiation-dominated universe.
    double hubble_rad_dom(double T)
    {
      // H(T)/eV, T/MeV, m_pl/10^12eV = m_pl/10^3 GeV
      const double m_pl = m_planck_red*1.0E-3;
      return 0.331153*sqrt(gStar(T))*T*T/m_pl;
    }

    // General form of the temperature-dependent axion mass.
    double axion_mass_temp(double T, double beta, double Tchi)
    {
      double res = 1.0;
      if (T > Tchi) { res = pow(T/Tchi,-0.5*beta); }
      return res;
    }

    // Auxillary structure for passing the model parameters to the gsl solver.
    struct AxionEDT_params {double ma0; double beta; double Tchi; double thetai; double Tosc;};

    // Auxillary function with root Tosc, the temperature where the axion field oscillations start (defined by mA = 3H).
    // Note that this is only to set the temperature scale of the problem. The differential equation is solved numerically around
    // this point and the numerical factor in the definition is pure convention.
    double equation_Tosc(double T, void *params)
    {
      // T/MeV, ma0/eV, m_pl/10^12eV = m_pl/10^3 GeV
      const double m_pl = m_planck_red*1.0E-3;
      struct AxionEDT_params * p1 = (struct AxionEDT_params *)params;
      double ma0 = (p1->ma0);
      double beta = (p1->beta);
      double Tchi = (p1->Tchi);

      double result = 1.0 - gStar(T)*gsl_pow_2(T*T*pi/(ma0*m_pl*axion_mass_temp(T, beta, Tchi)))/10.0;

      return result;
    }

    // Capability function to solve equation_Tosc for Tosc.
    void calc_AxionOscillationTemperature(double &result)
    {
      using namespace Pipes::calc_AxionOscillationTemperature;

      double ma0 = *Param["ma0"];
      double beta = *Param["beta"];
      double Tchi = *Param["Tchi"];
      // m_pl/10^12 eV = m_pl/10^3 GeV
      const double m_pl = m_planck_red*1.0E-3;

      // Initialising the parameter structure with known and dummy values.
      AxionEDT_params params = {ma0, beta, Tchi, 0.0, 0.0};

      // Use gsl implementation Brent's method to determine the oscillation temperature.
      gsl_function F;
      F.function = &equation_Tosc;
      F.params = &params;

      // Set counters and initialise equation solver.
      int status;
      int iter = 0, max_iter = 1E6;
      gsl_root_fsolver *s;
      s = gsl_root_fsolver_alloc(gsl_root_fsolver_brent);
      double r, r_up, r_lo;

      // Calculate first estimate for the root bracketing [r_lo, r_up].
      // Calculate best estimate for comparison. g(Tchi)^-0.25 = 0.49, g(Tchi)^-...=0.76
      r = 0.49*pow((10.0/(pi*pi)) * gsl_pow_2(m_pl*ma0), 0.25);
      // Compare to decide which branch of the equation is valid; T1 > Tchi or T1 < Tchi
      if ( (r > Tchi) && (beta > 1.0E-10) )
      {
        r = 0.76*pow((10.0/(pi*pi)) * gsl_pow_2(m_pl*ma0) * pow(Tchi, beta), 1.0/(4.0+beta));
      }
      // Find appropriate values for r_lo and r_up
      r_up = r;
      r_lo = r;
      while (GSL_FN_EVAL(&F,r_up) > 0.0) { r_up = 2.0*r_up; }
      while (GSL_FN_EVAL(&F,r_lo) < 0.0) { r_lo = 0.5*r_lo; }

      // Execute equation solver until we reach 10^-6 absolute precision.
      gsl_root_fsolver_set(s, &F, r_lo, r_up);
      do
      {
        iter++;
        status = gsl_root_fsolver_iterate (s);
        r = gsl_root_fsolver_root (s);
        r_lo = gsl_root_fsolver_x_lower (s);
        r_up = gsl_root_fsolver_x_upper (s);
        status = gsl_root_test_interval (r_lo, r_up, 1.0E-6, 0.0);
      } while (status == GSL_CONTINUE && iter < max_iter);

      gsl_root_fsolver_free (s);

      result = r;
    }

    /* Differential equation solver to calculate the axion energy density today */

    // Initialise the quantities needed for the ODE solver from the gsl library.
    // Define the system of differential equations as a function of relative temperature.
    int scal_field_eq(double tau, const double y[], double f[], void *params)
    {
      struct AxionEDT_params * p = (struct AxionEDT_params *)params;
      double ma0 = (p->ma0);
      double beta = (p->beta);
      double Tchi= (p->Tchi);
      double Tosc = (p->Tosc);
      double thetai = (p->thetai);
      // f stores derivatives, y stores functions.
      f[0] = y[1];
      f[1] = -gsl_pow_2(SpecialFun1(-tau*Tosc) * ma0*axion_mass_temp(-tau*Tosc,beta,Tchi) / (hubble_rad_dom(-tau*Tosc) * (-tau))) * gsl_sf_sin(y[0]*thetai)/thetai;

      return GSL_SUCCESS;
    }

    // Define the Jacobian for the system of differential equations.
    int scal_field_eq_jac(double tau, const double y[], double *dfdy, double dfdt[], void *params)
    {
      //(void)(t); // avoid unused parameter warning.
      struct AxionEDT_params * p = (struct AxionEDT_params *)params;
      double ma0 = (p->ma0);
      double beta = (p->beta);
      double Tchi = (p->Tchi);
      double Tosc = (p->Tosc);
      double thetai = (p->thetai);
      gsl_matrix_view dfdy_mat  = gsl_matrix_view_array (dfdy, 2, 2);
      gsl_matrix * m = &dfdy_mat.matrix;
      // (i, j) entries for matrix m; last entry = df[i]/df[j].
      gsl_matrix_set (m, 0, 0, 0);
      gsl_matrix_set (m, 0, 1, 1);
      gsl_matrix_set (m, 1, 0, -gsl_pow_2(SpecialFun1(-tau*Tosc) * ma0*axion_mass_temp(-tau*Tosc,beta,Tchi) / (hubble_rad_dom(-tau*Tosc) * (-tau))) * gsl_sf_cos(y[0]*thetai));
      gsl_matrix_set (m, 1, 1, -SpecialFun3(-tau*Tosc) / (-tau));
      dfdt[0] = 0.0;
      dfdt[1] = 0.0;

      return GSL_SUCCESS;
    }

    // Capability function to solve the differential equation for the energy density in axions today (in terms of the critical density).
    void RD_oh2_Axions(double &result)
    {
      using namespace Pipes::RD_oh2_Axions;
      double ma0 = *Param["ma0"];
      double beta = *Param["beta"];
      double Tchi = *Param["Tchi"];
      double thetai = *Param["thetai"];
      double fa = *Param["fa"];
      double Tosc = *Dep::AxionOscillationTemperature;

      if ( (thetai<-pi) || (thetai>3.0*pi) ) { DarkBit_error().raise(LOCAL_INFO, "ERROR! The parameter 'thetai' should be chosen from the interval [-pi,3pi]."); }

      // If thetai in (pi,3pi): map it back to its equivalent value in (-pi,pi]. This is to allow sampling around pi and easier averaging.
      if (thetai>pi) { thetai = thetai - 2.0*pi; }

      // Only do computations if thetai > 0.
      result = 0.0;
      if (fabs(thetai) > 0)
      {
        // TCMB in MeV.
        const double TCMB = *Dep::T_cmb*K2eV*1.0E-6;
        // Critical energy density today * h^2 (in eV^4).
        const double ede_crit_today = 3.0*2.69862E-11;

        struct AxionEDT_params p = {ma0, beta, Tchi, thetai, Tosc};

        // Function, Jacobian, number of dimensions + pointer to params.
        gsl_odeiv2_system sys = {scal_field_eq, scal_field_eq_jac, 2, &p};
        // Evolution from Temp = 1e5 x Tosc to Temp = 0.001 x Tosc.
        double tau2 = -0.001, tau1 = -1E5;
        // Initial conditions for (u and v = u') as functions of temperature:
        double y[2] = {1.0, 0.0};
        // Settings for the driver: pointer to the ODE system sys, the gsl method, initial step size,
        // absolute accuracy in y[0] and y[1], relative accuracy in y[0] and y[1].
        // Other possible choices: gsl_odeiv2_step_rk4 (classic), gsl_odeiv2_step_rk8pd, gsl_odeiv2_step_rkf45 (standard choices).
        gsl_odeiv2_driver * d = gsl_odeiv2_driver_alloc_y_new (&sys, gsl_odeiv2_step_bsimp, -0.1*tau1, 1E-8, 1E-8);

        // Numerically solve ODE by continuing the integration well into the harmonic and adiabatic regime (stopping conditions
        // via check1 = |hat(theta)| and check2 = 3H/m need to be satisfied).
        double new_step;
        double check1 = 1.0, check2 = 1.0;
        int i = 0;

        #ifdef AXION_DEBUG_MODE
          std::cout << "DEBUGGING INFO for relic density calculation:\n"
                       "#'temperature' theta dtheta/dtau" << std::endl;
        #endif

        do
        {
          i++;
          new_step = -pow(10.0, 1.0 + (log10(-tau2)-1.0)*i/1000.0);
          int status = gsl_odeiv2_driver_apply (d, &tau1, new_step, y);
          if (status != GSL_SUCCESS) { std::cout << "Error, return value = " << d << std::endl; }
          check1 = fabs(thetai)*sqrt(gsl_pow_2( fabs(y[0]) ) + gsl_pow_2( fabs((-new_step)*y[1]*hubble_rad_dom(-new_step*Tosc)/(ma0*axion_mass_temp(-new_step*Tosc,beta,Tchi))) ));
          check2 = 3.0*hubble_rad_dom(-new_step*Tosc)/(ma0*axion_mass_temp(-new_step*Tosc,beta,Tchi));

          #ifdef AXION_DEBUG_MODE
            std::cout << -new_step << " " << thetai*y[0] << " " << -tau2*thetai*y[1] << std::endl;
          #endif

        } while ( ((check1>1.0E-2) || (check2>1.0E-3)) && (i<1E3) );

        i++;
        if (i>=1E+3)
        {
          std::ostringstream buffer;
          buffer << "T_end: " << -new_step << " | theta_hat_val: " << check1 << ", theta_der: "<< -tau2*y[1]*thetai << ", 3H/m_osc: " << 3.0*hubble_rad_dom(Tosc)/(ma0*axion_mass_temp(-new_step*Tosc,beta,Tchi)) << ", 3H/m: " << check2 << " .\n";
          DarkBit_warning().raise(LOCAL_INFO, "WARNING! Maximum number of integration steps reached for energy density calculator!\n         "+buffer.str());
        }

        // Calculate the axion energy density at the stopping point.
        double ede = 1E+18*gsl_pow_2(fa)*(0.5*gsl_pow_2(y[1]*thetai*hubble_rad_dom(-new_step*Tosc)*(-new_step)) + gsl_pow_2(ma0*axion_mass_temp(-new_step*Tosc,beta,Tchi))*(1.0 - gsl_sf_cos(y[0]*thetai)));
        // Use conservation of entropy to scale the axion energy density to its present value (relative to the critical energy density).
        double OmegaAh2 = ede*gsl_pow_3(TCMB/(-new_step*Tosc))*(gStar_S(TCMB)/gStar_S(-new_step*Tosc))*(1.0/axion_mass_temp(-new_step*Tosc,beta,Tchi))/ede_crit_today;

        gsl_odeiv2_driver_free (d);

        result = OmegaAh2;
      }
    }

    //////////////////////////////////////////////
    //                                          //
    //            Axion Astrophysics            //
    //                                          //
    //////////////////////////////////////////////

    /*! \brief Capabilities relating to astrophysical observations (R-parameter, H.E.S.S. telescope search, cooling hints).
     *
     * Supported models: GeneralALP
     */

     ///////////////////////////
     //      R-parameter      //
     ///////////////////////////

     // Capability function to calculate the R-parameter (1512.08108).
     // Based and extending on Refs [11, 12, 13, 75] and 10.3204/DESY-PROC-2015-02/straniero_oscar in 1512.08108 .
     void calc_RParameter(double &result)
     {
       using namespace Pipes::calc_RParameter;
       double ma0 = *Param["ma0"];
       double gaee2 = gsl_pow_2(gaee_conversion*std::fabs(*Param["gaee"]));
       double gagg = 1.0E+10*std::fabs(*Param["gagg"]); // gagg needs to be in 10^-10 GeV^-1.
       // Value for He-abundance Y from 1503.08146: <Y> = 0.2515(17).
       const double Y = 0.2515;
       // Use interpolation for the finite-mass correction.
       static AxionInterpolator correction (GAMBIT_DIR "/DarkBit/data/Axions_RParameterCorrection.dat", InterpolationOptions1D::linear);
       // Initialise an effective axion-photon coupling, valid for low masses.
       double geff = gagg;
       // Apply correction for higher mass values...
       static double m_min = pow(10,correction.lower());
       static double m_max = pow(10,correction.upper());
       if ((ma0 > m_min) && (ma0 < m_max)) { geff *= pow(10, 0.5*correction.interpolate(log10(ma0))); }
       // ... or set to zero if mass is too high.
       if (ma0 >= m_max) { geff = 0.0; }
       // Expressions only valid for gaee2 < 35.18 but limits should become stronger for gaee2 > 35.18 (but perhaps not gaee2 >> 35.18).
       // Conservative approach: Constrain gaee2 > 35.18 at the level of gaee2 = 35.18.
       if (gaee2 > 35.18) { gaee2 = 35.18; }

       result = -0.421824 - 0.0948659*(-4.675 + sqrt(21.8556 + 21.0824*geff)) - 0.00533169*gaee2 - 0.0386834*(-1.23 - 0.137991*pow(gaee2,0.75) + sqrt(1.5129 + gaee2)) + 7.3306*Y;
     }

     // Capability function to calculate the likelihood for the R-parameter.
     void calc_lnL_RParameter(double &result)
     {
       using namespace Pipes::calc_lnL_RParameter;
       double Rtheo = *Dep::RParameter;

       // Observed R values from astro-ph/0403600.
       const double Robs = 1.39;
       const double RobsErr = 0.03;
       // Value for He-abundance Y from 1503.08146: <Y> = 0.2515(17).
       const double YobsErrContrib = 7.3306*0.0017;

       result = -0.5*gsl_pow_2(Rtheo - Robs)/(RobsErr*RobsErr+YobsErrContrib*YobsErrContrib);
     }

    /////////////////////////////////////////
    //      White Dwarf cooling hints      //
    /////////////////////////////////////////

    // White Dwarf interpolator class
    class WDInterpolator
    {
      public:
        // Constructor
        WDInterpolator(const std::vector<double> x, const std::vector<double> y, std::string correction_file, InterpolationOptions1D type = InterpolationOptions1D::linear)
        {
          period_change = AxionInterpolator(x, y, type);
          correction = AxionInterpolator(correction_file, type);
        }

        // Evaluation function
        double evaluate(double mrel, double x2)
        {
          double res = x2;
          // For higher masses, reduce the effective coupling accordingly:
          if (mrel > 100.0)
          {
            res *= 15.0 * exp(-mrel) * pow(mrel,2.5)/(M_SQRT2 * pow(pi,3.5));
          } else if (mrel > 0.01) {
            res *= pow(10,correction.interpolate(log10(mrel)));
          }
          // We only have predictions up to x2 = max value. Limits should get stronger for x2 > max value, so
          // it is conservative to use the prediction for x2 = max value for x2 > max value.
          res = std::min(res, period_change.upper());
          res = period_change.interpolate(res);
          return res;
        }

      private:
        AxionInterpolator period_change;
        AxionInterpolator correction;
    };

    // Capability function to compute the cooling likelihood of G117-B15A (1205.6180; observations from Kepler+ (2011)).
    void calc_lnL_WDVar_G117B15A(double &result)
    {
      using namespace Pipes::calc_lnL_WDVar_G117B15A;
      // Rescale coupling to be used in their model prediction.
      double x2 = (1.0e+14 * std::fabs(*Param["gaee"]))/2.8;
      x2 = x2*x2;

      // Values for the model prediction provided by the authors.
      const std::vector<double> x2vals  = {0.0, 1.0, 6.25, 25.0, 56.25, 100.0, 156.25, 225.0, 306.25, 404.0, 506.25, 625.0, 756.25, 900.0};
      const std::vector<double> dPidts  = {1.235687, 1.244741, 1.299579, 1.470017, 1.796766, 2.260604, 2.795575, 3.484570, 4.232738, 5.056075, 6.113390, 7.342085, 8.344424, 9.775156};
      const double err2 = 0.09*0.09;
      const double obs = 4.19;
      const double obs_err2 = 0.73*0.73;

      static WDInterpolator dPidt (x2vals, dPidts, GAMBIT_DIR "/DarkBit/data/Axions_WDCorrection_G117B15A.dat");

      // Use interpolation for the finite-mass correction.
      const double internal_temperature_keV = 1.19698;
      double mrel = 0.001 * (*Param["ma0"]) / internal_temperature_keV;

      double pred = dPidt.evaluate(mrel, x2);

      result = -0.5 * gsl_pow_2(obs - pred) / (obs_err2 + err2);
    }

    // Capability function to compute the cooling likelihood of R548 (1211.3389 using T = 11630 K; observations from Mukadam+ (2012)).
    void calc_lnL_WDVar_R548(double &result)
    {
      using namespace Pipes::calc_lnL_WDVar_R548;
      // Rescale coupling to be used in their model prediction.
      double x2 = (1.0E+14 * std::fabs(*Param["gaee"]))/2.8;
      x2 = x2*x2;

      // Values for the model prediction provided by the authors.
      const std::vector<double> x2vals   = {0.0, 1.0, 6.25, 25.0, 56.25, 100.0, 156.25, 225.0, 306.25, 400.0, 506.25, 625.0, 756.25, 900.0};
      const std::vector<double> dPidts  = {1.075373, 1.095319, 1.123040, 1.289434, 1.497666, 1.869437, 2.300523, 2.844954, 3.379978, 4.086028, 4.847149, 5.754807, 6.714841, 7.649140};
      const double err2 = 0.09*0.09;
      const double obs = 3.3;
      const double obs_err2 = 1.1*1.1;

      static WDInterpolator dPidt (x2vals, dPidts, GAMBIT_DIR "/DarkBit/data/Axions_WDCorrection_R548.dat");

      // Use interpolation for the finite-mass correction.
      const double internal_temperature_keV = 1.11447;
      double mrel = 0.001 * (*Param["ma0"]) / internal_temperature_keV;

      double pred = dPidt.evaluate(mrel, x2);

      result = -0.5 * gsl_pow_2(obs - pred) / (obs_err2 + err2);
    }

    // Capability function to compute the cooling likelihood of PG1351+489 (1605.07668 & 1406.6034; using observations from Redaelli+ (2011)).
    void calc_lnL_WDVar_PG1351489(double &result)
    {
      using namespace Pipes::calc_lnL_WDVar_PG1351489;
      // Rescale coupling to be used in their model prediction.
      double x2 = (1.0E+14 * std::fabs(*Param["gaee"]))/2.8;
      x2 = x2*x2;

      // Values for the model prediction provided by the authors.
      const std::vector<double> x2vals = {0.0, 4.0, 16.0, 36.0, 64.0, 100.0, 144.0, 196.0, 256.0, 324.0, 400.0};
      const std::vector<double> dPidts = {0.90878126, 0.96382008, 1.2022906, 1.5712931, 2.1220619, 2.8002354, 3.6172605, 4.5000560, 5.5256592, 6.5055283, 7.5341296};
      const double err2 = 0.5*0.5;
      const double obs = 2.0;
      const double obs_err2 = 0.9*0.9;

      static WDInterpolator dPidt (x2vals, dPidts, GAMBIT_DIR "/DarkBit/data/Axions_WDCorrection_PG1351489.dat");

      // Use interpolation for the finite-mass correction.
      const double internal_temperature_keV = 2.64273;
      double mrel = 0.001 * (*Param["ma0"]) / internal_temperature_keV;

      double pred = dPidt.evaluate(mrel, x2);

      result = -0.5 * gsl_pow_2(obs - pred) / (obs_err2 + err2);
    }

    // Capability function to compute the cooling likelihood of L192 (1605.06458  using l=1 & k=2; observations from Sullivan+Chote (2015)).
    void calc_lnL_WDVar_L192 (double &result)
    {
      using namespace Pipes::calc_lnL_WDVar_L192;
      // Rescale coupling to be used in their model prediction.
      double x2 = (1.0E+14 * std::fabs(*Param["gaee"]))/2.8;
      x2 = x2*x2;

      // Values for the model prediction provided by the authors.
      const std::vector<double> x2vals = {0.0, 1.0, 4.0, 9.0, 16.0, 25.0, 36.0, 49.0, 64.0, 81.0, 100.0, 121.0, 144.0, 169.0, 196.0, 225.0, 256.0, 289.0, 324.0, 361.0, 400.0, 441.0, 484.0, 529.0, 576.0, 625.0, 676.0, 729.0, 784.0, 841.0, 900.0};
      const std::vector<double> dPidts = {2.41, 2.40, 2.44, 2.42, 2.50, 2.57, 2.63, 2.74, 2.83, 2.99, 3.15, 3.32, 3.52, 3.70, 3.90, 4.08, 4.42, 4.69, 4.98, 5.34, 5.62, 6.02, 6.27, 6.62, 7.04, 7.38, 7.89, 8.09, 8.65, 9.16, 9.62};
      const double err2 = 0.85*0.85;
      const double obs = 3.0;
      const double obs_err2 = 0.6*0.6;

      static WDInterpolator dPidt (x2vals, dPidts, GAMBIT_DIR "/DarkBit/data/Axions_WDCorrection_L192.dat");

      // Use interpolation for the finite-mass correction.
      const double internal_temperature_keV = 1.04931;
      double mrel = 0.001 * (*Param["ma0"]) / internal_temperature_keV;

      double pred = dPidt.evaluate(mrel, x2);

      result = -0.5 * gsl_pow_2(obs - pred) / (obs_err2 + err2);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //      SN 1987A limits (from axion-photon conversion in the B-field of the Milky Way or axion-photon decay)      //
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Capability function to calculate the likelihood for SN 1987A (based on data from 25 to 100 MeV photons, interpreted
    // by Chupp et al., Phys. Rev. Lett. 62, 505 (1989). Use 10 sec of data for conversion and 223 sec for decay.
    void calc_lnL_SN1987A (double &result)
    {
      using namespace Pipes::calc_lnL_SN1987A;
      double f_10s = *Dep::PhotonFluence_SN1987A_Conversion;
      double f_223s = *Dep::PhotonFluence_SN1987A_Decay;

      // Standard devations of the null observation.
      const double sigma_10s = 0.2;
      const double sigma_223s = 0.59333;

      // Conversion and decay constraints are based on the same data but never apply at the same time.
      // Pick the larger value of the ratio/stronger of the two constraints, as this will always be the relevant one.
      double ratio = std::max(f_10s/sigma_10s, f_223s/sigma_223s);

      result = -0.5*ratio*ratio;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////
    //      SN 1987A photon fluence (from axion-photon conversion in the B-field of the Milky Way)      //
    //////////////////////////////////////////////////////////////////////////////////////////////////////

    // Capability function to calculate the photon fluence from SN 1987A as a result of axion-photon
    // conversion in the B-field of the Milky Way (based on arXiv:1410.3747).
    void calc_PhotonFluence_SN1987A_Conversion (double &result)
    {
      using namespace Pipes::calc_PhotonFluence_SN1987A_Conversion;
      double m = (1.0E+10*(*Param["ma0"]))/5.433430;
      double g = (1.0E+12*std::fabs(*Param["gagg"]))/5.339450;

      result = 0.570589*gsl_pow_4(g);
      if (m > 1.0) { result = result*pow(m, -4.021046); }
    }

    ////////////////////////////////////////////////////////////////////////
    //       SN 1987A photon fluence (from axion decay into photons)      //
    ////////////////////////////////////////////////////////////////////////

    // Capability function to calculate the photon fluence from SN 1987A as a result of axion decay.
    // Based on MC simulations by Marie Lecroq & Sebastian Hoof (following arXiv:1702.02964).
    void calc_PhotonFluence_SN1987A_Decay (double &result)
    {
      using namespace Pipes::calc_PhotonFluence_SN1987A_Decay;
      double lgg = log10(std::fabs(*Param["gagg"]));
      double lgm = log10(*Param["ma0"]);
      result = 0.0;

      // Initialise interpolation class with MC data from file.
      static AxionInterpolator2D fluence (GAMBIT_DIR "/DarkBit/data/SN1987A_DecayFluence.dat");

      if (fluence.is_inside_box(lgm,lgg)) { result = fluence.interpolate(lgm,lgg); };
    }

    //////////////////////////////////////////////////////////////////
    //      Spectral distortions (H.E.S.S. telescope searches)      //
    //////////////////////////////////////////////////////////////////

    // Calculate the likelihood for H.E.S.S. data assuming conversion in the galaxy cluster magnetic field (GCMF, "Conservative" limits, 1311.3148).
    void calc_lnL_HESS_GCMF (double &result)
    {
      using namespace Pipes::calc_lnL_HESS_GCMF;
      double m_ax = *Param["ma0"];
      double gagg = gagg_conversion*std::fabs(*Param["gagg"]); // gagg needs to be in eV^-1.

      // Compute the domensionless parameters Epsilon and Gamma from the axion mass and axion-photon coupling (see 1311.3148).
      const double c_epsilon = 0.071546787;
      const double c_gamma = 0.015274036*370.0/sqrt(37.0);
      double epsilon = log10(m_ax*c_epsilon) + 5.0;
      double gamma = log10(gagg*c_gamma) + 20.0;

      // Initialise the interpolation and extrapolation routies for the H.E.S.S. results.
      static HESS_Interpolator interp (GAMBIT_DIR "/DarkBit/data/HESS_GCMF_Table.dat");

      result = interp.lnL(epsilon, gamma);
    }

    /**
     * @brief Capability for the XENON1T likelihood from 2006.10035
     *
     * The signal model consists of 3 components: Primakoff, ABC, and Fe57.
     */
    void calc_lnL_XENON1T_Anomaly(double &result)
    {
      using namespace Pipes::calc_lnL_XENON1T_Anomaly;

      // Rescale couplings and 3H abundance to the reference values used in 2006.10035 for convenience.
      double gae = std::fabs(*Param["gaee"]) / 5.0e-12;
      double gagamma = std::fabs(*Param["gagg"]) / 2.0e-10;
      double gaN = std::fabs(*Param["gaN"]) / 1.0e-6;
      double x_3H = *Param["x_3H"] / 6.2e-25;
      double bkg_scale = 1.0 + *Param["delta_bkg"];
      double eff = 1.0 + *Param["delta_eff"];

      static bool include_inverse_Primakoff = runOptions->getValueOrDef<bool> (true, "include_inverse_Primakoff");

      // XENON1T 2020 data (based on 2006.10035 and using an exposure of 0.65 tonne-years)
      static const Eigen::ArrayXd observed = (Eigen::ArrayXd(29) <<
        26., 61., 55., 47., 49.,
        47., 44., 41., 40., 37.,
        51., 41., 42., 51., 47.,
        48., 24., 43., 42., 34.,
        42., 40., 38., 53., 41.,
        57., 39., 46., 35.).finished();

      static const Eigen::ArrayXd bkg_tritium = (Eigen::ArrayXd(29) <<
        4.54543769e+00, 8.60509728e+00, 8.94256482e+00, 8.61684767e+00, 8.02464466e+00,
        7.29168481e+00, 6.48068011e+00, 5.65037508e+00, 4.81438779e+00, 3.97835836e+00,
        3.17827210e+00, 2.43987288e+00, 1.78022901e+00, 1.21426641e+00, 7.54437371e-01,
        4.13276721e-01, 1.95253807e-01, 7.58276424e-02, 2.37741495e-02, 1.17262241e-02,
        4.76851304e-03, 1.65434695e-04, 5.42752619e-05, 5.22947241e-05, 5.03141863e-05,
        4.83336485e-05, 4.63531107e-05, 4.43725729e-05, 4.23920351e-05).finished();

      static const Eigen::ArrayXd bkg_other = (Eigen::ArrayXd(29) <<
        22.07404375, 39.45186703, 41.83417331, 42.46968003, 42.78761694, 42.96532578,
        43.13847573, 43.56505579, 44.1162301 , 44.04330642, 43.60594679, 43.40248223,
        43.45031774, 43.49263918, 43.57084528, 43.66270961, 43.75990478, 43.85453193,
        43.95159076, 44.04782058, 44.14510208, 44.24450247, 44.3406822 , 44.43638726,
        44.5331988, 44.62865958, 44.72654689, 44.82382807, 44.91842725).finished();

      static const Eigen::ArrayXd signal_ref_ABC = (Eigen::ArrayXd(29) <<
        7.46283683e+01, 9.11300502e+01, 4.91874199e+01, 3.53433982e+01, 3.97196350e+01,
        3.57128137e+01, 2.27540737e+01, 1.19536450e+01, 6.29278747e+00, 3.30948412e+00,
        1.61495065e+00, 6.21479171e-01, 1.55434142e-01, 2.13046184e-02, 1.63362970e-03,
        5.94631877e-05, 6.22346656e-07, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0).finished();

      static const Eigen::ArrayXd signal_ref_primakoff = (Eigen::ArrayXd(29) <<
        8.52269995e+00, 2.00539997e+01, 1.92433543e+01, 2.22113223e+01, 2.89487211e+01,
        2.48618807e+01, 1.56554086e+01, 8.76011034e+00, 4.77088790e+00, 2.59966792e+00,
        1.43054774e+00, 7.84191139e-01, 4.15162321e-01, 2.10029374e-01, 1.02847245e-01,
        5.27333566e-02, 2.93001979e-02, 1.70759274e-02, 1.08781046e-02, 7.76743790e-03,
        6.24916022e-03, 5.51837192e-03, 5.15693524e-03, 4.97968515e-03, 4.88717867e-03,
        4.84242242e-03, 4.82038071e-03, 2.38442778e-03, 0).finished();

      static const Eigen::ArrayXd signal_ref_fe57 = (Eigen::ArrayXd(29) <<
        4.64697658e-22, 1.14417236e-18, 1.48421451e-15, 1.01555196e-12, 3.67061998e-10,
        7.02067458e-08, 7.12116995e-06, 3.84028003e-04, 1.10431167e-02, 1.69885040e-01,
        1.40292258e+00, 6.23942228e+00, 1.49856121e+01, 1.94718769e+01, 1.36959639e+01,
        5.21070939e+00, 1.07020697e+00, 1.18324090e-01, 7.01902932e-03, 2.22639151e-04,
        3.76396817e-06, 3.38186408e-08, 1.61083936e-10, 4.05908328e-13, 5.40175385e-16,
        3.79105023e-19, 1.40152641e-22, 2.72678128e-26, 2.78978087e-30).finished();

      static const Eigen::ArrayXd signal_ref_ABC_inv_p = (Eigen::ArrayXd(29) <<
        6.90095435e+00, 1.39022260e+01, 1.15151093e+01, 7.97641672e+00, 5.52073353e+00,
        4.15542096e+00, 2.85016524e+00, 1.77391643e+00, 1.07580666e+00, 6.28453363e-01,
        3.26090878e-01, 1.31638303e-01, 3.77207469e-02, 7.52278937e-03, 1.06834615e-03,
        1.12228106e-04, 9.07094259e-06, 5.85004243e-07, 3.10665723e-08, 1.39581067e-09,
        5.42752207e-11, 1.86190569e-12, 5.72719620e-14, 1.60150437e-15, 4.11906863e-17,
        9.84235043e-19, 2.20372014e-20, 4.65786516e-22, 9.35349973e-24).finished();

      static const Eigen::ArrayXd signal_ref_primakoff_inv_p = (Eigen::ArrayXd(29) <<
        8.80070525e-01, 3.29923191e+00, 4.56900949e+00, 4.56444853e+00, 3.82216381e+00,
        2.86024934e+00, 1.98175269e+00, 1.29748018e+00, 8.13307028e-01, 4.92544613e-01,
        2.90070188e-01, 1.66927792e-01, 9.42159402e-02, 5.23046562e-02, 2.86265445e-02,
        1.54743414e-02, 8.27421198e-03, 4.38184245e-03, 2.30069622e-03, 1.19872791e-03,
        6.20254770e-04, 3.18925270e-04, 1.63051423e-04, 8.29261227e-05, 4.19736901e-05,
        2.11518187e-05, 1.06157318e-05, 5.30780091e-06, 2.64457315e-06).finished();

      static const Eigen::ArrayXd signal_ref_fe57_inv_p = (Eigen::ArrayXd(29) <<
        2.68534579e-23, 1.02403478e-19, 1.64401745e-16, 1.34346994e-13, 5.65333857e-11,
        1.23357889e-08, 1.40118942e-06, 8.30825834e-05, 2.57975431e-03, 4.20954642e-02,
        3.62322333e-01, 1.65087221e+00, 3.99391811e+00, 5.14060546e+00, 3.52226638e+00,
        1.28362583e+00, 2.48258237e-01, 2.54009765e-02, 1.36995132e-03, 3.88033329e-05,
        5.75235843e-07, 4.44951177e-09, 1.79118821e-11, 3.74451860e-14, 4.05797696e-17,
        2.27644923e-20, 6.60289329e-24, 9.89294778e-28, 7.65058090e-32).finished();

      static const double asimov = (observed * observed.log() - observed).sum();

      const Eigen::ArrayXd bkg = x_3H * bkg_tritium + bkg_other;
      Eigen::ArrayXd signal = gae * gae * (
                              signal_ref_ABC * gae * gae +
                              signal_ref_primakoff * gagamma * gagamma +
                              signal_ref_fe57 * gaN * gaN);

      if (include_inverse_Primakoff)
      {
        signal = signal + gagamma * gagamma * (
                 signal_ref_ABC_inv_p * gae * gae +
                 signal_ref_primakoff_inv_p * gagamma * gagamma +
                 signal_ref_fe57_inv_p * gaN * gaN);
      }

      const Eigen::ArrayXd expected = eff * (bkg_scale * bkg + signal);

      result = (observed * expected.log() - expected).sum() - asimov;
    }

    struct dRdE_params { double m; double sigma; };

    double dRdE (double E, void * params)
    {
      struct dRdE_params * par = (struct dRdE_params *)params;
      // Efficiency of the Xenon1T experiment from arXiv:2006.09721
      // Columns: Energy [keV] | Efficiency [dimensionless]
      static AxionInterpolator efficiency (GAMBIT_DIR "/DarkBit/data/XENON1T/efficiency.txt", InterpolationOptions1D::cspline);
      return std::exp(-0.5*pow((E - par->m)/par->sigma,2))*efficiency.interpolate(E);
    }

    void calc_lnL_XENON1T_DM_Anomaly(double &result)
    {
      using namespace Pipes::calc_lnL_XENON1T_DM_Anomaly;

      result = 0;

      // Rescale couplings and 3H abundance to the reference values used in 2006.10035 for convenience.
      double gae = std::fabs(*Param["gaee"]);
      double ma = *Param["ma0"] / 1.0e3;
      double x_3H = *Param["x_3H"] / 6.2e-25;
      double bkg_scale = 1.0 + *Param["delta_bkg"];
      double rel_eff = 1.0 + *Param["delta_eff"];
      double dm_fraction = *Param["eta"];
      LocalMaxwellianHalo LocalHaloParameters = *Dep::LocalHalo;
      double rho0 = LocalHaloParameters.rho0;

      // XENON1T 2020 data (based on 2006.10035 and using an exposure of 0.65 tonne-years)
      static const Eigen::ArrayXd observed = (Eigen::ArrayXd(29) <<
        26., 61., 55., 47., 49.,
        47., 44., 41., 40., 37.,
        51., 41., 42., 51., 47.,
        48., 24., 43., 42., 34.,
        42., 40., 38., 53., 41.,
        57., 39., 46., 35.).finished();

      static const Eigen::ArrayXd bkg_tritium = (Eigen::ArrayXd(29) <<
        4.54543769e+00, 8.60509728e+00, 8.94256482e+00, 8.61684767e+00, 8.02464466e+00,
        7.29168481e+00, 6.48068011e+00, 5.65037508e+00, 4.81438779e+00, 3.97835836e+00,
        3.17827210e+00, 2.43987288e+00, 1.78022901e+00, 1.21426641e+00, 7.54437371e-01,
        4.13276721e-01, 1.95253807e-01, 7.58276424e-02, 2.37741495e-02, 1.17262241e-02,
        4.76851304e-03, 1.65434695e-04, 5.42752619e-05, 5.22947241e-05, 5.03141863e-05,
        4.83336485e-05, 4.63531107e-05, 4.43725729e-05, 4.23920351e-05).finished();

      static const Eigen::ArrayXd bkg_other = (Eigen::ArrayXd(29) <<
        22.07404375, 39.45186703, 41.83417331, 42.46968003, 42.78761694,
        42.96532578, 43.13847573, 43.56505579, 44.1162301 , 44.04330642,
        43.60594679, 43.40248223, 43.45031774, 43.49263918, 43.57084528,
        43.66270961, 43.75990478, 43.85453193, 43.95159076, 44.04782058,
        44.14510208, 44.24450247, 44.3406822 , 44.43638726, 44.5331988 ,
        44.62865958, 44.72654689, 44.82382807, 44.91842725).finished();

      // Photoelectric cross section for Xe from https://dx.doi.org/10.18434/T48G6X
      // Columns: Photon energy [MeV] | Photoelectric absorption [10^-28 m^2/atom]
      static AxionInterpolator sigma_pe (GAMBIT_DIR "/DarkBit/data/XENON1T/photoelectric.txt");

      gsl_integration_workspace * w = gsl_integration_workspace_alloc(1000);
      if ( (ma >= 1.0) && (ma <= 30.0) )
      {
        // Energy resolution from 2003.03825
        double energy_resolution = 0.15 + 31.71/sqrt(ma);
        double sigma = ma * energy_resolution / 100.0;
        const double exposure = 0.647309514*1000.0*365.0;
        const double photoel_eff_conversion = 1.5e19/131.0;
        double amplitude = dm_fraction * (rho0/0.3) * exposure * gae*gae * ma * photoel_eff_conversion*sigma_pe.interpolate(ma/1000.0);
        gsl_function f;
        struct dRdE_params params = {ma, sigma};
        f.function = &dRdE;
        f.params = &params;
        double dRdE_result, error;
        std::vector<double> signal_vec;
        for (int i = 0; i < 29; i++)
        {
          gsl_integration_qags (&f, 1.+i, 2.+i, 0, 1e-7, 1000, w, &dRdE_result, &error);
          double s = amplitude * 1/sqrt(2*pi)/sigma * dRdE_result;
          signal_vec.push_back(s);
        }
        gsl_integration_workspace_free (w);

        static const double asimov = (observed * observed.log() - observed).sum();

        const Eigen::ArrayXd bkg = x_3H * bkg_tritium + bkg_other;
        const Eigen::ArrayXd signal = Eigen::ArrayXd::Map(signal_vec.data(), signal_vec.size());
        const Eigen::ArrayXd expected = rel_eff * (bkg_scale * bkg + signal);

        result = (observed * expected.log() - expected).sum() - asimov;
      }
    }

    void calc_lnL_XENON1T_Anomaly_NuisanceParameters(double &result)
    {
      using namespace Pipes::calc_lnL_XENON1T_Anomaly_NuisanceParameters;

      result = -0.5 * ( gsl_pow_2(*Param["delta_bkg"]/0.026) + gsl_pow_2(*Param["delta_eff"]/0.030) );
    }

  }  // namespace DarkBit
}  // namespace Gambit
