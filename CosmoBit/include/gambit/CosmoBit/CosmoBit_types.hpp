//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Type definition header for module CosmoBit.
///
///  Compile-time registration of type definitions
///  required for the rest of the code to
///  communicate with CosmoBit.
///
///  Add to this if you want to define a new type
///  for the functions in CosmoBit to return, but
///  you don't expect that type to be needed by
///  any other modules.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Patrick Stoecker
///          (stoecker@physik.rwth-aachen.de)
///  \date 2017 Nov
///  \date 2018 May
///  \date 2021 Sep
///
///  \author Janina Renk
///          (janina.renk@fysik.su.se)
///  \date 2018 Oct
///  \date 2019 Mar
///
///  \author Sebastian Hoof
///          (hoof@uni-goettingen.de)
///  \date 2020 Mar
///
///  \author Pat Scott
///          (pat.scott@uq.edu.au)
///  \date 2020 Apr
///
///  *********************************************


#ifndef __CosmoBit_types_hpp__
#define __CosmoBit_types_hpp__

#include <tuple>
#include <cmath>
#include <vector>
#include <sstream>
#include <limits>

#include "gambit/Utils/util_types.hpp"
#include "gambit/Utils/numerical_constants.hpp"
#include "gambit/Backends/backend_types/MontePythonLike.hpp"

#include <gsl/gsl_spline.h>

#ifdef HAVE_PYBIND11
  #include <pybind11/stl.h>
#endif

namespace Gambit
{

  namespace CosmoBit
  {

    // Forward declaration of warnings and errors
    error& CosmoBit_error();
    warning& CosmoBit_warning();

    #ifdef HAVE_PYBIND11
      typedef std::tuple<pybind11::object, map_str_str, map_str_pyobj> MPLike_objects_container;
    #endif

    namespace
    {
      enum interpolation_bound { underflow, in_range, overflow };
    }

    class SM_time_evo
    {
      /* Time evolution of photon & neutrino temperature as well as Hubble rate in SM for time t > 1e3 s.
       *     => Use these routines only for times t >~ 10^3 s, where electrons and positrons are already
       *        completely annihilated.
       *        For times after CMB release you can get these values from the class background structure.
       */
    public:
      SM_time_evo(size_t grid_size, double t0, double tf, double Neff_SM, double rnu, double dNeff);
      ~SM_time_evo();

      const std::vector<double>& get_t_grid() const {return t_grid;}
      const std::vector<double>& get_T_grid() const {return T_grid;}
      const std::vector<double>& get_Tnu_grid() const {return Tnu_grid;}
      const std::vector<double>& get_H_grid() const {return H_grid;}
      const std::vector<double>& get_lnR_grid() const {return lnR_grid;}

      // Returns the photon temperature T in units of keV as a function of t.
      double T_at_t(double t) const
      {
        return safe_interpolation(t, T_spline);
      }

      // Returns the neutrino temperature T in units of keV as a function of t.
      double Tnu_at_t(double t) const
      {
        return safe_interpolation(t, Tnu_spline);
      }

      // Returns the Hubble parameter T in units of 1/s as a function of t.
      double H_at_t(double t) const
      {
        return safe_interpolation(t, H_spline);
      }

      // Returns (the logarithm of) the scale factor lnR (dimensionless) as a function of t.
      double lnR_at_t(double t) const
      {
        return safe_interpolation(t, lnR_spline);
      }

      // Start point of the time grid
      double t0() const {return t_grid[0];}

      // End point of the time grid
      double tf() const {return t_grid[grid_size-1];}

      // Size of the tables
      size_t size() const {return grid_size;}

      // Initiates to update the tables given the new values of 'T' and 'Tnu'
      void update_grid(const std::vector<double>& T_grid_new, const std::vector<double>& Tnu_grid_new, const bool& unchecked = true);

    private:
      size_t grid_size;
      double Neff;

      std::vector<double> t_grid;
      std::vector<double> T_grid;
      std::vector<double> Tnu_grid;
      std::vector<double> H_grid;
      std::vector<double> lnR_grid;

      gsl_spline* T_spline;
      gsl_spline* Tnu_spline;
      gsl_spline* H_spline;
      gsl_spline* lnR_spline;

      // Returns H [in 1/s] based on the value of T and Tnu [both in keV]
      double H_at_T_and_Tnu(double T, double Tnu) const
      {
        const double Tratio = Tnu/T;
        const double T_in_GeV = 1e-6 * T;
        const double gstar = 2. + 2.*7./8. * Neff * Tratio*Tratio*Tratio*Tratio;
        const double H2_in_GeV2 = 8.*pi*pi*pi/90./m_planck/m_planck * gstar * T_in_GeV*T_in_GeV*T_in_GeV*T_in_GeV;
        return sqrt(H2_in_GeV2)/hbar;
      }

      interpolation_bound interpolation_range_check(double t) const
      {
        bool above_lower_bound = t >= t_grid[0];
        bool below_upper_bound = t <= t_grid[grid_size-1];

        if (above_lower_bound)
        {
          if (below_upper_bound) return interpolation_bound::in_range;
          else return interpolation_bound::overflow;
        }
        else return interpolation_bound::underflow;
      }

      // Method to avoid interpolation issues at the end points of the t_grid.
      // If the underflow / overflow is within some margin of the bounds,
      // return the value at the respective end point (constant continuation).
      // When the underflow / overflow is bigger, throw an error
      double safe_interpolation(double t, const gsl_spline* spline_ptr) const
      {
        double epsilon = 1e3 * std::numeric_limits<double>::epsilon();

        interpolation_bound bound_check = interpolation_range_check(t);
        if (bound_check == interpolation_bound::in_range)
        {
          return gsl_spline_eval(spline_ptr, t, nullptr );
        }
        else if (bound_check == interpolation_bound::underflow)
        {
          if (std::fabs(t_grid[0] - t)/t_grid[0] >= epsilon)
          {
            std::ostringstream err;
            err << "The given value of t underflows t_grid! ";
            err << "t_grid starts at " << t_grid[0] << " but got " << t << std::endl;
            CosmoBit_error().raise(LOCAL_INFO, err.str());
          }
          else
          {
            return gsl_spline_eval(spline_ptr, t_grid[0], nullptr );
          }
        }
        else
        {
          if (std::fabs(t - t_grid[grid_size-1])/t_grid[grid_size-1] >= epsilon)
          {
            std::ostringstream err;
            err << "The given value of t overflows t_grid! ";
            err << "t_grid ends at " << t_grid[grid_size-1] << " but got " << t << std::endl;
            CosmoBit_error().raise(LOCAL_INFO, err.str());
          }
          else
          {
            return gsl_spline_eval(spline_ptr, t_grid[grid_size-1], nullptr );
          }
        }

        // This return statement is unreachable, but must be here to keep the compiler happy.
        return std::numeric_limits<double>::quiet_NaN();
      }

      // When we update 'T_grid' and 'T_nu_grid' we need to make sure that their
      // size is 'grid_size'.
      // If not, this is treated a runtime error and halts the execution
      void check_size(const std::vector<double>& new_grid, const std::string& name)
      {
        if (new_grid.size() != grid_size) {
          std::ostringstream err;
          err << "The size of the new vector (\'" << name << "\') does not ";
          err << "match the size of the old vector.\n";
          err << "(Expected " << grid_size  << " but got " << new_grid.size() << " ).";
          CosmoBit_error().raise(LOCAL_INFO,err.str());
        }
      }
    };

    /// Class containing the primordial power spectrum.
    /// Members:
    /// - vector of modes k (1/Mpc)
    /// - scalar power spectrum of these modes P_s(k) (dimensionless)
    /// - tensor power spectrum of these modes P_t(k) (dimensionless)
    /// - scalar power spectrum of isocurvature modes P_s_iso(k) (dimensionless)
    class Primordial_ps
    {
        public:
            Primordial_ps() {};
            ~Primordial_ps() {};

            /// Fill k from an array of doubles
            void set_N_pivot(double npiv) { N_pivot = npiv; }
            void fill_k(double*, int);
            void fill_P_s(double*, int);
            void fill_P_s_iso(double*, int);
            void fill_P_t(double*, int);

            double get_N_pivot() { return N_pivot; }
            std::vector<double>& get_k() { return k; }
            std::vector<double>& get_P_s() { return P_s; }
            std::vector<double>& get_P_t() { return P_t; }
            std::vector<double>& get_P_s_iso() { return P_s_iso; }
            int get_vec_size() { return vec_size; }

        private:
            double N_pivot;
            std::vector<double> k;
            std::vector<double> P_s;
            std::vector<double> P_s_iso;
            std::vector<double> P_t;
            /// needed to pass vector length to CLASS; set in 'fill_k' method
            int vec_size;
    };

    /// Class containing the *parametrised* primordial power spectrum.
    /// Members:
    /// - spectral tilt n_s
    /// - amplitude of scalar perturbations A_s [as ln(10^{10}A_s)]
    /// - scalar to tensor ratio r
    class Parametrised_ps
    {
        public:
            Parametrised_ps() {};
            ~Parametrised_ps() {};

            void set_N_pivot(double npiv) { N_pivot = npiv; }
            void set_n_s(double ns) { n_s = ns; }
            void set_ln10A_s(double ln10As) { ln10A_s = ln10As; }
            void set_r(double rr) { r = rr; }

            double get_N_pivot() { return N_pivot; }
            double get_n_s() { return n_s; }
            double get_ln10A_s() { return ln10A_s; }
            double get_r() { return r; }

            /// return members as str to double map for printing
            map_str_dbl get_parametrised_ps_map();

        private:
            double N_pivot;
            double n_s;
            double ln10A_s;
            double r;
    };
  }
}

#endif // defined __CosmoBit_types_hpp__
