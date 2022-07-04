//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Routines for the interpolation of the yield
///  tables from PPPC4DMID.
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

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/DarkBit/DarkBit_rollcall.hpp"
#include "gambit/DarkBit/PPPC.hpp"

namespace Gambit
{
  namespace DarkBit
  {
    // Move assignment operator
    Interpolator2D& Interpolator2D::operator=(Interpolator2D&& interp)
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
    Interpolator2D::~Interpolator2D()
    {
      gsl_spline2d_free (spline);
      gsl_interp_accel_free (x_acc);
      gsl_interp_accel_free (y_acc);
      free(z);
    }

    // Initialiser for the AxionInterpolator class.
    void Interpolator2D::init(const std::vector<double>& xin, const std::vector<double>& yin, const std::vector<double>& zin)
    {
      // Initialise gsl interpolation routine.
      // Get unique entries of "x" and "y" for the grid and grid size.
      static std::vector<double> xa = xin;
      sort(xa.begin(), xa.end());
      xa.erase(unique(xa.begin(), xa.end()), xa.end());
      size_t nx = xa.size();

      static std::vector<double> ya = yin;
      sort(ya.begin(), ya.end());
      ya.erase(unique(ya.begin(), ya.end()), ya.end());
      size_t ny = ya.size();

      size_t n_grid_pts = zin.size();
      if (nx*ny != n_grid_pts)
      {
        std::ostringstream err;
        err << "ERROR! The number of grid points (" << n_grid_pts << ") for Interpolator2D does not equal ";
        err << "the number of unique 'x' and 'y' values (" << nx << " and " << ny <<")!";
        DarkBit_error().raise(LOCAL_INFO, err.str());
      }

      // Determine the boundaries of the box.
      x_lo = xa.front();
      x_up = xa.back();
      y_lo = ya.front();
      y_up = ya.back();

      double* x = xa.data();
      double* y = ya.data();
      z = (double*) malloc(nx * ny * sizeof(double));

      spline = gsl_spline2d_alloc(gsl_interp2d_bilinear, nx, ny);

      x_acc = gsl_interp_accel_alloc();
      y_acc = gsl_interp_accel_alloc();

      // Intialise grid.
      for (size_t i = 0; i < n_grid_pts; i++)
      {
        // Determine appropriate indices for the grid points.
        size_t ind_x = std::upper_bound (xa.begin(), xa.end(), xin[i]) - xa.begin() - 1;
        size_t ind_y = std::upper_bound (ya.begin(), ya.end(), yin[i]) - ya.begin() - 1;

        // Set z[ind_x,ind_y] (2D grid) equal to zin[i] (1D)
        gsl_spline2d_set(spline, z, ind_x, ind_y, zin[i]);
      }
      gsl_spline2d_init (spline, x, y, z, nx, ny);
    }

    // Default creator with dummy entries for the objects w/ memory allocation
    Interpolator2D::Interpolator2D()
    {
      x_acc = gsl_interp_accel_alloc();
      y_acc = gsl_interp_accel_alloc();
      spline = gsl_spline2d_alloc(gsl_interp2d_bilinear, 2, 2);
      z = (double*) malloc(2 * 2 * sizeof(double));
    }
    // Overloaded class creators for the AxionInterpolator class using the init function above.
    Interpolator2D::Interpolator2D(const std::vector<double>& xin, const std::vector<double>& yin, const std::vector<double>& zin)
    { 
      init(xin,yin,zin);
    }

    // Routine to access interpolated values.
    double Interpolator2D::interpolate(double x, double y) const { return gsl_spline2d_eval(spline, x, y, x_acc, y_acc); }

    // Routine to check if a point is inside the interpolating box.
    bool Interpolator2D::is_inside_box(double x, double y) const { return ((x >= x_lo) && (x <= x_up) && (y >= y_lo) && (y <= y_up)); }

    static std::vector<std::string> colnames{"mass", "log10x", 
                                             "e_L", "e_R", "e",
                                             "mu_L", "mu_R", "mu",
                                             "tau_L", "tau_R", "tau",
                                             "q", "c", "b", "t",
                                             "W_L", "W_T", "W",
                                             "Z_L", "Z_T", "Z",
                                             "g", "gamma", "h",
                                             "nu_e", "nu_mu", "nu_tau",
                                             "VV_to_4e", "VV_to_4mu", "VV_to_4tau"};
    static std::vector<std::string> channels {"e", "mu", "tau",
                                              "q", "c", "b", "t",
                                              "W","Z", "g", "gamma", "h",
                                              "nu_e", "nu_mu", "nu_tau"};

    PPPC_interpolation::PPPC_interpolation(const std::string& filename): table(ASCIItableReader(filename))
    {
      table.setcolnames(colnames);
      for (const auto& channel: channels)
      {
        interpMap.emplace(std::piecewise_construct,
                          std::forward_as_tuple(channel),
                          std::forward_as_tuple(table["mass"], table["log10x"], table[channel]));
      }
    }

    // Only allow move assignment
    PPPC_interpolation& PPPC_interpolation::operator=(PPPC_interpolation&& other)
    {
      if(this != &other)
      {
        std::swap(table,     other.table);
        std::swap(interpMap, other.interpMap);
      }
      return *this;
    }

    double PPPC_interpolation::operator()(const std::string& channel, double m, double x) const
    {
      check_channel(channel);
      double r = 0.0;
      auto& interp = interpMap.at(channel);
      double lx = log10(x);
      double E = m*x;
      if (interp.is_inside_box(m,lx))
      {
        // The PPPC tables contain dN/dlog10x. We need dNdE 
        // Use dN/dlog10x = dlnx/dlog10x * x * dN/dx
        //                = ln10 * E * dN/dE
        r = std::max(interp.interpolate(m,lx), 0.0) / log(10.0) / E;
      }
      return r;
    }

    void PPPC_interpolation::check_channel(const std::string& channel) const
    {
      if (interpMap.count(channel) == 0)
      {
        std::ostringstream err;
        err << "ERROR in \'PPPC_interpolation\': The channel \'" << channel << "\' is not known.";
        DarkBit_error().raise(LOCAL_INFO, err.str());
      }
    }

    /// Conveninence function to get the gamma yield from the interpolated PPPC tables
    double PPPC_dNdE_gamma(double m, double x, std::string channel)
    {
      static PPPC_interpolation PPPC_object(GAMBIT_DIR "/DarkBit/data/AtProduction_gammas.dat");
      return PPPC_object(channel, m, x);
    }

    /// Conveninence function to get the positiron yield from the interpolated PPPC tables
    double PPPC_dNdE_positron(double m, double x, std::string channel)
    {
      static PPPC_interpolation PPPC_object(GAMBIT_DIR "/DarkBit/data/AtProduction_positrons.dat");
      return PPPC_object(channel, m, x);
    }

  }
}