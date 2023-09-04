//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Source code for types for module CosmoBit.
///  For instructions on adding new types, see
///  the corresponding header.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Patrick Stoecker
///          (stoecker@physik.rwth-aachen.de)
///  \date 2017 Nov
///  \date 2021 Sep
///
///  \author Selim Hotinli
///  \date 2018 Jan
///
///  \author Janina Renk
///          (janina.renk@fysik.su.se)
///  \date 2018 Oct
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

#include "gambit/CosmoBit/CosmoBit_types.hpp"

#define GSL_SPLINE_TYPE gsl_interp_linear
//#define GSL_SPLINE_TYPE gsl_interp_cspline

namespace Gambit
{
  namespace CosmoBit
  {

    SM_time_evo::SM_time_evo(size_t grid_size, double t0, double tf, double Neff_SM, double rnu, double dNeff)
    : grid_size(grid_size)
    , Neff(Neff_SM) // In case the c'tor crashes Neff has a somehow valid state
    {

      // Check if implemented routines are valid for given initial time
      if(t0 < 1e3)
      {
        std::ostringstream err;
        err << "Requested initial time for evolution of Temperature & Hubble rate for SM for Temperatures t_initial was "<< t0<<".";
        err << " Implemented routines are only valid after e+/- annihilation (t > 10^3). Aborting now.";
        CosmoBit_error().raise(LOCAL_INFO, err.str());
      }

      // Resize all vectors of the structure to hold 'grid_size' elements.
      t_grid.resize(grid_size);
      T_grid.resize(grid_size);
      Tnu_grid.resize(grid_size);
      H_grid.resize(grid_size);
      lnR_grid.resize(grid_size);

      // Allocate the GSL spline object pointers.
      T_spline = gsl_spline_alloc(GSL_SPLINE_TYPE, grid_size);
      Tnu_spline = gsl_spline_alloc(GSL_SPLINE_TYPE, grid_size);
      H_spline = gsl_spline_alloc(GSL_SPLINE_TYPE, grid_size);
      lnR_spline = gsl_spline_alloc(GSL_SPLINE_TYPE, grid_size);

      // Initialize time grid. (Evenly spaced in log space from t0 to tf)
      double Delta_logt = (log(tf) - log(t0))/(grid_size-1);
      for (size_t i = 0; i < grid_size; ++i)
      {
        t_grid[i] = exp(log(t0) + i*Delta_logt);
      }

      // Set Neff out of Neff_SM, rnu, and dNeff
      Neff = pow(rnu,4.)*Neff_SM + dNeff;

      // Throughout the code, we assume radiation domination such that
      //
      //   H^2 = 8*pi*G/3 * gstar(T, Tnu) * pi^2/30 * T^4 .     (i)
      //
      // In general, gstar(T,Tnu) is dependent on T and Tnu, as both quantities
      // evolve independently from each other.
      //
      //   gstar = g + gnu * 7./8. * Neff * (Tnu/T)^4           (ii)
      //
      // For the first iteration (i = 0), we assume that the ratio Tnu / T is given
      // by its standard value (assuming instant decoupling)
      //
      //   Tnu / T = (4/11)^(1/3)                               (iii)
      //
      // such that gstar(T, Tnu) is a constant
      //
      //   gstar_0 = g + gnu * 7./8. * Neff * (4./11.)^(4./3.)  (iv)
      //
      // In this case we can easily solve for H(t) = 1/(2.*t) [in 1/s]
      // or H(t) = 1e6*hbar/(2t) [in keV].
      const double gstar_0 = 2.+2.*7./8.*Neff*pow(4./11.,4./3.);

      for (size_t i = 0; i<grid_size; ++i)
      {
        H_grid[i] = 1./2./t_grid[i];
      }
      // Initialise interpolation for H(t)
      gsl_spline_init(H_spline, t_grid.data(), H_grid.data(), grid_size);

      // Solve equation (i) for T and use m_planck = 1/sqrt(G) such that
      //   T^4 [keV] = 90 * (1e6*m_planck)^2 * (1e6*hbar)^2 / (32 * pi^3 * gstar_0 * t^2 )
      const double T_prefactor = 1.e6 * pow(90.*m_planck*m_planck*hbar*hbar/32./pi/pi/pi/gstar_0, 1./4.);
      for (size_t i = 0; i < grid_size; ++i)
      {
        T_grid[i] = T_prefactor / sqrt(t_grid[i]);
      }
      // Initialise interpolation for T(t)
      gsl_spline_init(T_spline, t_grid.data(), T_grid.data(), grid_size);

      // For the 0-th iteration assume Tnu = (4./11.)^(1./3.) * T (cf. eq (iii))
      for (size_t i = 0; i < grid_size; ++i)
      {
        Tnu_grid[i] = pow((4./11.),(1./3.)) * T_grid[i];
      }
      // Initialise interpolation for Tnu(t)
      gsl_spline_init(Tnu_spline, t_grid.data(), Tnu_grid.data(), grid_size);

      // Calculate lnR by integrating H over t.
      // After the lnR array is set here, it will never change throughout the code.
      for (size_t i = 0; i < grid_size; ++i)
      {
        lnR_grid[i] = gsl_spline_eval_integ(H_spline, t_grid[0], t_grid[i], nullptr);
      }

      // Initialise interpolation for lnR(t)
      gsl_spline_init(lnR_spline, t_grid.data(), lnR_grid.data(), grid_size);
    }

    SM_time_evo::~SM_time_evo()
    {
      gsl_spline_free(T_spline);
      gsl_spline_free(Tnu_spline);
      gsl_spline_free(H_spline);
      gsl_spline_free(lnR_spline);
    }

    void SM_time_evo::update_grid(const std::vector<double>& T_grid_new, const std::vector<double>& Tnu_grid_new, const bool& unchecked)
    {
      // Before we start, let's assert that the inputs T_grid_new and Tnu_grid_new have the right size.
      // (unless the user promisses that their sizes are fine and 'unchecked' is set false)
      if (unchecked) {
        check_size(T_grid_new, "T_grid_new");
        check_size(Tnu_grid_new, "Tnu_grid_new");
      }

      // Update the internal arrays 'T_grid' and 'Tnu_grid'.
      // Do not update the respective splines yet as t_grid will be modified (see below).
      std::memcpy( T_grid.data(), T_grid_new.data(), grid_size*sizeof(double) );
      std::memcpy( Tnu_grid.data(), Tnu_grid_new.data(), grid_size*sizeof(double) );

      // In general we assume that the T and Tnu arrays are modified through some differential equation.
      // Based on the updated values of T and Tnu we calculate gstar which enters the calculation of H [in 1/s].
      // This is done in the private function SM_time_evo::H_at_T_and_Tnu (defined in SM_evo.hpp)
      for (size_t i = 0; i < grid_size; ++i)
      {
        H_grid[i] = H_at_T_and_Tnu( T_grid_new[i], Tnu_grid_new[i] );
      }

      // As 'H' is now modified and we assume 'lnR' to be fixed, we need to update 't'.
      // To this end we use the definition of H
      //
      //   H = dlnR / dt ,
      //
      // solve for dt and integrate over dlnR from lnR_grid[0] (which is 0 by construction) to lnR_grid[i].
      // Furthermore we add the constant t0 = t_grid[0] such that the starting point of the new t_grid is
      // aligned with the old one.
      //
      // (1) Define the integrand (1/H) and respective spline as function of lnR.
      std::vector<double> one_over_H_grid(grid_size);
      for (size_t i = 0; i < grid_size; ++i) {
        one_over_H_grid[i] = 1/H_grid[i];
      }

      gsl_spline* one_over_H_spline = gsl_spline_alloc(GSL_SPLINE_TYPE, grid_size);
      gsl_spline_init(one_over_H_spline, lnR_grid.data(), one_over_H_grid.data(), grid_size);

      // (2) Determine t[i] by integrating the spline.
      const double t0 = t_grid[0];
      for (size_t i = 0; i < grid_size; ++i) {
        t_grid[i] = gsl_spline_eval_integ(one_over_H_spline, lnR_grid[0], lnR_grid[i], nullptr) + t0;
      }

      // (3) Get rid of the spline.
      gsl_spline_free(one_over_H_spline);

      // As 't' is now updated, all tables are self consistent.
      // Before we return, update all splines (in terms of 't')
      gsl_spline_init(T_spline, t_grid.data(), T_grid.data(), grid_size);
      gsl_spline_init(Tnu_spline, t_grid.data(), Tnu_grid.data(), grid_size);
      gsl_spline_init(H_spline, t_grid.data(), H_grid.data(), grid_size);
      gsl_spline_init(lnR_spline, t_grid.data(), lnR_grid.data(), grid_size);
    }

    // return Parametrised_ps members A_s, n_s, r, and N_pivot as str to double map for printing
    map_str_dbl Parametrised_ps::get_parametrised_ps_map()
    {
      map_str_dbl result;
      result["ln10A_s"] = ln10A_s;
      result["n_s"] = n_s;
      result["r"] = r;
      result["N_pivot"] = N_pivot;

      return result;
    };

    void Primordial_ps::fill_k(double *k_array, int len)
    {
      std::vector<double> K(k_array, k_array+len);
      k = std::move(K);
      vec_size = len;
    }

    void Primordial_ps::fill_P_s(double *P_s_array, int len)
    {
      std::vector<double> ps(P_s_array, P_s_array+len);
      P_s = std::move(ps);
    }

    void Primordial_ps::fill_P_s_iso(double *P_s_iso_array, int len)
    {
      std::vector<double> psi(P_s_iso_array, P_s_iso_array+len);
      P_s_iso = std::move(psi);
    }

    void Primordial_ps::fill_P_t(double *P_t_array, int len)
    {
      std::vector<double> pt(P_t_array, P_t_array+len);
      P_t = std::move(pt);
    }
  }
}
