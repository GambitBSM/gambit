//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Routines for the interpolation of the yield
///  tables from PPPC4DMID.
///
///  Class decalrations
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Patrick Stoecker
///          (stoecker@physik.rwth-aachen.de)
///  \date 2021 Mar
///
///  *********************************************

#ifndef __PPPC_hpp__
#define __PPPC_hpp__

#include <unordered_map>

#include <gsl/gsl_interp2d.h>
#include <gsl/gsl_spline2d.h>

#include "gambit/Utils/ascii_table_reader.hpp"

namespace Gambit
{
  namespace DarkBit
  {

    class Interpolator2D
    {
      public:
        Interpolator2D();
        Interpolator2D(const std::vector<double>& xin, const std::vector<double>& yin, const std::vector<double>& zin);
        Interpolator2D& operator=(Interpolator2D&&);
        // Destructor.
        ~Interpolator2D();
        // Delete copy constructor and assignment operator to avoid shallow copies.
        Interpolator2D(const Interpolator2D&) = delete;
        Interpolator2D operator=(const Interpolator2D&) = delete;
        // Routine to access interpolated values.
        double interpolate(double x, double y) const;
        // Routine to check if a point is inside the interpolating box.
        bool is_inside_box(double x, double y) const;
      private:
        // Initialiser for the Interpolator2D class.
        void init(const std::vector<double>& xin, const std::vector<double>& yin, const std::vector<double>& zin);
        // The gsl objects for the interpolating functions that need to be available to the class routines.
        gsl_interp_accel *x_acc;
        gsl_interp_accel *y_acc;
        gsl_spline2d *spline;
        double* z;
        // Upper and lower "x" and "y" values available to the interpolating function.
        double x_lo, y_lo, x_up, y_up;
    };

    class PPPC_interpolation
    {
      public:
        PPPC_interpolation(const std::string& filename);

        // Disable default ctor, copy ctor and copy assigment
        PPPC_interpolation() = delete;
        PPPC_interpolation(const PPPC_interpolation&) = delete;
        PPPC_interpolation operator=(const PPPC_interpolation&) = delete;

        // Only allow move assignment
        PPPC_interpolation& operator=(PPPC_interpolation&& other);

        double operator()(const std::string& channel, double m, double x) const;

      private:
        void check_channel(const std::string& channel) const;

        ASCIItableReader table;
        std::unordered_map<std::string, Interpolator2D> interpMap;
    };

  }
}
#endif // defined __PPPC_hpp__
