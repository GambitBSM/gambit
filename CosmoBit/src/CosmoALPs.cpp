//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  CosmoBit routines relating to axions and
///  axion-like particles.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Selim C. Hotinli
///          (selim.hotinli14@pimperial.ac.uk)
///  \date 2017 Jul
///  \date 2018 May
///  \date 2018 Aug - Sep
///
///  \author Patrick Stoecker
///          (stoecker@physik.rwth-aachen.de)
///  \date 2017 Nov
///  \date 2018 Jan - May
///  \date 2019 Jan, Feb, June, Nov
///  \date 2021 Sep
///
///  \author Janina Renk
///          (janina.renk@fysik.su.se)
///  \date 2018 June
///  \date 2019 Mar,June
///
///  \author Sanjay Bloor
///          (sanjay.bloor12@imperial.ac.uk)
///  \date 2019 June, Nov
///
///  \author Sebastian Hoof
///          (hoof@uni-goettingen.de)
///  \date 2020 Mar
///
///  \author Pat Scott
///          (pat.scott@uq.edu.au)
///  \date 2018 Mar
///  \date 2019 Jul
///  \date 2020 Apr
///
///  *********************************************

#include <gsl/gsl_odeiv2.h>

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/CosmoBit/CosmoBit_rollcall.hpp"
#include "gambit/CosmoBit/CosmoBit_types.hpp"
#include "gambit/CosmoBit/CosmoBit_utils.hpp"
#include "gambit/Utils/numerical_constants.hpp"
#include "gambit/Utils/interp_collection.hpp"

namespace Gambit
{

  namespace CosmoBit
  {
    using namespace LogTags;

    /// Lifetime (in s) of an ALP if only the decay a -> g g is open.
    void lifetime_ALP_agg(double& result)
    {
      using namespace Pipes::lifetime_ALP_agg;

      double gagg = *Param["gagg"]; // in GeV^-1
      double ma = *Param["ma0"]; // in eV

      // Calculate the decay width (in GeV)
      // (It's maybe worth being a separate capability)
      double Gamma = 1/64./pi * pow(gagg,2) * pow(ma,3) * 1e-27;

      // For the lifetime take 1/Gamma and translate GeV^-1 into s by multiplication with "hbar"
      result = 1./Gamma * hbar;

      // Reject points which have a lifetime outside a given range
      // Gets only triggered if the user wishes to do so.
      // !! This is not a real physical bound but it is more to deal with the lack of likelihoods so far. !!
      static const double cut_below = runOptions->getValueOrDef<double>(0.0,"cut_tau_below");
      static const double inf = std::numeric_limits<double>::infinity();
      static const double cut_above = runOptions->getValueOrDef<double>(inf,"cut_tau_above");
      if ( (result > cut_above) || (result < cut_below) )
      {
        std::ostringstream err;
        err << "ALP lifetime (" << result << " [s]) is outside of the permitted range";
        err << " [" << cut_below << ", " << cut_above << "].";
        invalid_point().raise(err.str());
      }
    }

    /// Compute the abundance of ALPs expected from thermal production via Primakoff processes
    void minimum_abundance_ALP_analytical(double& result)
    {
      using namespace Pipes::minimum_abundance_ALP_analytical;

      double gagg = *Param["gagg"];                 // Read axion-photon coupling in GeV^-1
      double T_R_in_GeV = 1e-3 * (*Param["T_R"]);   // Read reheating temperature in MeV and convert it to GeV

      // Check for stupid input (T_R < m_e) and throw an error if the user really pushed it that far.
      if (m_electron >= T_R_in_GeV)
        CosmoBit_error().raise(LOCAL_INFO,"The reheating temperature is below the electron mass.");

      result = 1.56e-5 * pow(gagg,2) * m_planck * (T_R_in_GeV - m_electron);

    }

    /// Abundance of ALPs expected from thermal production via Primakoff processes as calculated by micrOMEGAs
    void minimum_abundance_ALP_numerical(double& result)
    {
      using namespace Pipes::minimum_abundance_ALP_numerical;
      using Interpolator2D = Utils::interp2d_collection;

      double gagg = *Param["gagg"];                 // Read axion-photon coupling in GeV^-1
      double T_R_in_GeV = 1e-3 * (*Param["T_R"]);   // Read reheating temperature in MeV and convert it to GeV
      double m_a_in_GeV = 1e-9 * (*Param["ma0"]);   // Read ALP mass in GeV
      double m_a_in_eV = (*Param["ma0"]);

      static Interpolator2D oh2_a_grid(
        "oh2_a_grid",
        GAMBIT_DIR "/DarkBit/data/Oh2_ALP_freeze-in.dat",
        { "m_a","T_R","oh2_a"}
      );

      double m_a_min = oh2_a_grid.x_min;
      double m_a_max = oh2_a_grid.x_max;
      double T_R_min = oh2_a_grid.y_min;
      double T_R_max = oh2_a_grid.y_max;

      // Check whether T_R is inside the interpolation range.
      if (T_R_in_GeV < T_R_min || T_R_in_GeV > T_R_max)
      {
        std::ostringstream err;
        err << "The input for T_R (" << T_R_in_GeV;
        err << " GeV) is outside of the interpolation range ";
        err << "[" << T_R_min << "GeV, " << T_R_max << " GeV].";
        CosmoBit_error().raise(LOCAL_INFO,err.str());
      }

      // Check whether m_a is inside the interpolation range.
      // (Check only if the mass is too high. For small masses,
      // the result can be scaled, see below)
      if (m_a_in_GeV > m_a_max)
      {
        std::ostringstream err;
        err << "The input for ma0 (" << m_a_in_GeV;
        err << " GeV) is outside of the interpolation range ";
        err << "[" << m_a_min << "GeV, " << m_a_max << " GeV].";
        CosmoBit_error().raise(LOCAL_INFO,err.str());
      }

      // If the mass is below m_a_min the result can be easily scaled
      // as Omega_a h^2 ~ m_a for m_a << T_R.
      double scale = m_a_in_GeV <= m_a_min ? m_a_in_GeV/m_a_min : 1.0;
      double mass_to_use = m_a_in_GeV <= m_a_min ? m_a_min : m_a_in_GeV;

      // The grid assumes a fixed coupling gagg == 1e-8 Gev^-1.
      // The final result scales trivially Omega_a h^2 ~ gagg^2.
      scale *= pow(gagg/1e-8,2);

      double omega_a_h2 = oh2_a_grid.eval(mass_to_use, T_R_in_GeV) * scale;

      // Translate omega_a_h2 into Ya
      const double rho0_crit_by_h2 = 3.*pow(m_planck_red*1e9,2) * pow((1e5*1e9*hbar/Mpc_SI),2);
      double rho0_a = omega_a_h2 * rho0_crit_by_h2;
      double ssm0 = CosmoBit_utils::entropy_density_SM(2.7255);

      result = rho0_a / m_a_in_eV / ssm0; // Ya0 = n0_a / ssm0 = rho0_a / (ma * ssm0)
    }

    /// Compute the minimal fraction of dark matter in ALPs expected from thermal production via Primakoff processes
    void minimum_fraction_ALP(double& result)
    {
      using namespace Pipes::minimum_fraction_ALP;

      const double rho0_crit_by_h2 = 3.*pow(m_planck_red*1e9,2) * pow((1e5*1e9*hbar/Mpc_SI),2); // rho0_crit/(h^2)

      double ma0 = *Param["ma0"];                    // non-thermal ALP mass in eV
      double omega_cdm = *Param["omega_cdm"];        // omega_cdm = Omega_cdm * h^2

      // Consistency check: if the ALP abundance from all thermal processes is less than that expected just from Primakoff processes, invalidate this point.
      double Ya0_min = *Dep::minimum_abundance;
      double ssm0 = CosmoBit_utils::entropy_density_SM(2.7255);  // SM entropy density today in eV^3 (cf. footnote 24 of PDG2018-Astrophysical parameters)
      double rho0_cdm = omega_cdm * rho0_crit_by_h2;             // rho0_cdm = Omega_cdm * rho0_crit;
      double rho0_min = Ya0_min * ma0 * ssm0;                    // energy density of axions today in eV^4
      result = rho0_min / rho0_cdm;
    }

    /// The fraction of dark matter in decaying ALPs at the time of production
    void DM_fraction_ALP(double& result)
    {
      using namespace Pipes::DM_fraction_ALP;

      const double t_rec = 1e12;                     // Age of the Universe at recombination in s

      double f0_thermal = *Param["f0_thermal"];      // Fraction of DM in ALPs at production, due to thermal production
      double omega_ma = *Dep::RD_oh2;                // Cosmological density of ALPs from vacuum misalignment

      double omega_cdm = *Param["omega_cdm"];        // omega_cdm = Omega_cdm * h^2
      double tau_a = *Dep::lifetime;                 // ALP lifetime in s

      // Consistency check: if the ALP abundance from all thermal processes is less than that expected just from Primakoff processes, invalidate this point.
      double f0_min = *Dep::minimum_fraction;
      if (f0_thermal < f0_min)
      {
        std::ostringstream err;
        err << "The choice of f0_thermal (" << f0_thermal;
        err << ") is in contradiction with the minimum dark matter fraction f0_min (";
        err << f0_min << ") produced via Primakoff processes.";
        invalid_point().raise(err.str());
      }

      // Compute the total fraction of DM in ALPs at production
      double xi_ini = f0_thermal + omega_ma/omega_cdm;

      // Consistency check: invalidate if there are more ALPs than dark matter at the time of recombination (t ~ 1e12s)
      double xi_at_rec = xi_ini * exp(-t_rec/tau_a );
      if (xi_at_rec  > 1.)
      {
        std::ostringstream err;
        err << "ALPs are over-abundant (n_a > n_cdm) at t = 10^12 s. (n_a/n_cdm = "<< xi_at_rec <<")";
        invalid_point().raise(err.str());
      }

      result = xi_ini;
    }

    /// Return the total abundance (Y = n/s) of ALPs
    /// We assume non relativistic ALPs such that rho = n * m
    void total_DM_abundance_ALP(double& result)
    {
      using namespace Pipes::total_DM_abundance_ALP;

      const double rho0_crit_by_h2 = 3.*pow(m_planck_red*1e9,2) * pow((1e5*1e9*hbar/Mpc_SI),2); // rho0_crit/(h^2)
      double omega_cdm = *Param["omega_cdm"];  // omega_cdm = Omega_cdm * h^2
      double fraction = *Dep::DM_fraction;
      double rho0_ALP = omega_cdm * fraction* rho0_crit_by_h2; // rho0_cdm = Omega_cdm * rho0_crit

      double ma0 = *Param["ma0"];
      double TCMB = *Param["T_cmb"];
      double ssm0 = CosmoBit_utils::entropy_density_SM(TCMB);

      result = rho0_ALP / (ma0 * ssm0);
    }

    // Anonymous namespace
    // - It is only visible to this file
    // - Variables in here won't show up in the compiled files and are not seen by the linker
    namespace
    {
      // Auxiliary struct for passing the axion parameters and
      // SM quantities to the gsl solver.
      struct alp_solver_params
      {
        double       na0;           // Number density of a at t=t0 [keV^3].
        double       mass;          // Mass of the ALP [keV]
        double       tau;           // Lifetime of the ALP [s]
        SM_time_evo* SM_quantities; // Table containing t, H(t), T(t), Tnu(t), and lnR(t)
      };

      // Right hand side of differential equation for dT/dt through ALP decay
      int dTdt_alp_rhs(double t, const double T[], double dTdt[], void *params)
      {
        alp_solver_params* gsl_params_ptr  = static_cast<alp_solver_params*>(params);

        const double na0 = gsl_params_ptr->na0;
        const double ma = gsl_params_ptr->mass;
        const double tau = gsl_params_ptr->tau;
        const SM_time_evo* SM_ptr = gsl_params_ptr->SM_quantities;

        // dT/dt is given by 15/4/pi/pi rho_a(t)/tau_a/(T^3) - H(t)*T,
        // where rho_a(t) is given by ma * na(t), since we assume a to be non-relativistic,
        // and na(t) = na0 * exp(-3*lnR(t)) * exp(-t/tau)
        const double H = SM_ptr->H_at_t(t);
        const double lnR = SM_ptr->lnR_at_t(t);

        dTdt[0] = (15.0/(4.0*pi*pi)) * na0 * ma *  exp(-3*lnR) * exp(-t/tau) / pow(T[0], 3) / tau - H * T[0];

        return GSL_SUCCESS;
      }
    }

    /// @TODO function definition needed
    void compute_dNeff_etaBBN_ALP(map_str_dbl &result)
    {
      using namespace Pipes::compute_dNeff_etaBBN_ALP;

      // Initial values for Tnu_ratio = Tnu/Tnu_SM and eta_ratio
      double Tnu_ratio = 1.0;
      double eta_ratio = 1.0;

      // temporary (cached) values to check convergence of iteration
      double temp_eta_ratio = eta_ratio;
      double temp_Tnu_ratio = Tnu_ratio;

      // --- precision parameters --
      double hstart = runOptions->getValueOrDef<double>(1e-6,"hstart"); // initial step size for GSL ODE solver
      double epsrel = runOptions->getValueOrDef<double>(1e-6,"epsrel"); // desired relative accuracy for GSL ODE solver and dNeff & etaBBN
      double max_iter = runOptions->getValueOrDef<int>(10,"max_iter"); // maximum number of iterations before error message is thrown if result not converged
      size_t grid_size = runOptions->getValueOrDef<int>(3000,"grid_size"); // number of (logarithmic) grid points in t

      double t0 = runOptions->getValueOrDef<double>(1e3,"t_initial"); // initial time in seconds
      double tf0 = runOptions->getValueOrDef<double>(2e12,"t_final"); // final time in seconds (for 0th iteration)

      // Get values for r and dNur at BBN
      double rBBN = *Param["r_BBN"];
      double dNurBBN = *Param["dNur_BBN"];

      // Initialise the tables of SM quantities (Assuming Neff = Neff_SM; i.e. rnu = 1, and dNeff = 0)
      SM_time_evo SM_quantities(grid_size, t0, tf0, Gambit::Neff_SM, rBBN, dNurBBN);

      std::vector<double> t_grid = SM_quantities.get_t_grid();
      std::vector<double> T_grid = SM_quantities.get_T_grid();
      std::vector<double> Tnu_grid = SM_quantities.get_Tnu_grid();

      // --- ALP model parameters ----
      double Ya0 = *Dep::total_DM_abundance;
      double T0 = T_grid[0];
      double ssm_at_T0 = CosmoBit_utils::entropy_density_SM(T0, true);; // T0 in units of keV, set T_in_eV=True to interpret it correctly

      double na_t0 = Ya0 * ssm_at_T0;     // initial number density of a at t=t0, in units keV^3.
      double m_a = 1e-3*(*Param["ma0"]);  // mass of a in keV
      double tau_a = *Dep::lifetime;      // lifetime of a in seconds

      bool converged = false;
      size_t i = 0;
      while( (!converged) && (i <= max_iter) )
      {
        // Enhance the loop counter
        ++i;

        // Wrap all parameters for the ODE for T(t) into a single struct
        alp_solver_params gsl_params { na_t0, m_a, tau_a, &SM_quantities };

        // Solve the ODE for T(t), and store it in T_grid
        gsl_odeiv2_system sys = {dTdt_alp_rhs, NULL, 1, &gsl_params};
        gsl_odeiv2_driver * d =
        gsl_odeiv2_driver_alloc_y_new (&sys, gsl_odeiv2_step_rkf45, hstart, 0.0, epsrel);

        // Set initial conditions
        double T[1] = { SM_quantities.T_at_t(t0) };  // T(t0) = T_SM(t0)
        double t = t0;

        // Loop over all time steps in 't_grid' and update 'T_grid' accordingly
        for (size_t j = 0; j < grid_size; ++j)
        {
          double tj = t_grid[j] >= t ? t_grid[j] : t;
          int status = gsl_odeiv2_driver_apply (d, &t, tj, T);
          if (status != GSL_SUCCESS)
          {
            std::ostringstream err;
            err << "Failed to solve differential equation to compute dNeffCMB and etaBBN for GeneralCosmoALP model.\n";
            err << "Failed at iteration " << i+1;
            err << " at table index " << j << " (t =" << t << ", T = " << T[0] <<").\n";
            err << "Point will be invalidated.";
            invalid_point().raise(err.str());
          }
          T_grid[j] = T[0];
        }

        // Free the GSL ODE solver driver
        gsl_odeiv2_driver_free (d);

        // Update the 'SM_quantities' table
        // The new grids have the correct size, such that we skip the check.
        SM_quantities.update_grid(T_grid, Tnu_grid, true);

        // Update the copy of 't_grid' that we use in this part of the code.
        t_grid = SM_quantities.get_t_grid();

        // End point of t_grid;
        double tf = SM_quantities.tf();

        // Calculate eta_0/eta_f
        eta_ratio = pow(SM_quantities.T_at_t(tf)/SM_quantities.T_at_t(t0), 3) * exp(3.0*SM_quantities.lnR_at_t(tf));

        // Calculate Tnu_ratio at recombination
        // This is defined as Tnu / Tnu_SM, where Tnu_SM is the naive value for
        // Tnu that can be derived from T by assuming Tnu = (4/11)^(1/3) * T;
        double Tnu = SM_quantities.Tnu_at_t(tf);
        double Tnu_SM = pow((4./11.), (1./3.)) * SM_quantities.T_at_t(tf);
        Tnu_ratio = Tnu / Tnu_SM;

        converged = (fabs(temp_eta_ratio-eta_ratio)/eta_ratio) <= epsrel && (fabs(temp_Tnu_ratio - Tnu_ratio)/Tnu_ratio <= epsrel);

        // Update the temp values
        temp_eta_ratio = eta_ratio;
        temp_Tnu_ratio = Tnu_ratio;
      }

      // invalidate point if results not converged after 'max_iter' steps
      if( !converged )
      {
        std::ostringstream err;
        err << "Computation of dNeffCMB and etaBBN for GeneralCosmoALP model did not converge after n = "<< i <<" iterations. ";
        err << "You can increase the maximum number of iterations with the run Option 'max_iter'. Invalidating point.";
        invalid_point().raise(err.str());
      }

      // Save "eta_ratio"
      result["eta_ratio"] = eta_ratio;

      // Derive "dNur" and "r" at CMB from their respective value at BBN and "Tnu_ratio" and save them
      result["dNur_CMB"] = pow(Tnu_ratio,4) * dNurBBN;
      result["r_CMB"] = Tnu_ratio * rBBN;

      logger() << "GeneralCosmoALP model: Calculated ";
      logger() << "\'dNur_CMB\' = " << result["dNur_CMB"];
      logger() << ", \'r_CMB\' = " << result["r_CMB"];
      logger() << " and \'eta_ratio\' = " << result["eta_ratio"] << ". ";
      logger() << "Calculation converged after "<< i <<" iterations." << EOM;
    }

    void eta_ratio_ALP(double& result)
    {
      result = (*Pipes::eta_ratio_ALP::Dep::external_dNeff_etaBBN).at("eta_ratio");
    }

    void Neff_evolution_ALP(map_str_dbl& result)
    {
      // Delete results of previous iteration
      result.clear();

      result["dNur_CMB"] = (*Pipes::eta_ratio_ALP::Dep::external_dNeff_etaBBN).at("dNur_CMB");
      result["r_CMB"] = (*Pipes::eta_ratio_ALP::Dep::external_dNeff_etaBBN).at("r_CMB");
    }

  } // namespace CosmoBit

} // namespace Gambit
