//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Central module file of CosmoBit.
///  Calculates cosmology-related observables.
///
///  Additionally, contains main routines for
///  interfacing to CLASS and MontePython.
///
///  Most of the model- or observable-specific code is
///  stored in separate source files.
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
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2020 Sep
///
///  *********************************************

#include <stdint.h> // save memory addresses as int
#include <boost/algorithm/string/trim.hpp>

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/CosmoBit/CosmoBit_rollcall.hpp"
#include "gambit/CosmoBit/CosmoBit_types.hpp"
#include "gambit/Utils/numerical_constants.hpp"

namespace Gambit
{

  namespace CosmoBit
  {
    using namespace LogTags;

    /***********************************/
    /* General cosmological quantities */
    /***********************************/

    /// Function for setting k_pivot in Mpc^-1 for consistent use within CosmoBit
    /// (i.e. ensuring a consistent value is used by both CLASS and MultiModeCode)
    void set_k_pivot(double &result)
    {
      result = Pipes::set_k_pivot::runOptions->getValueOrDef<double>(0.05, "k_pivot");
    }

    // return Neff for 3 SM neutrinos (and no additional dark radiation or BSM physics) 
    // in the early Universe, see arXiv 1606.06986
    void get_Neff_SM(double& result)
    {
      using namespace Pipes::get_Neff_SM;

      result = Gambit::Neff_SM;
    }

    // returning the total mass sum of SM neutrino
    void get_mNu_tot(double& result)
    {
      using namespace Pipes::get_mNu_tot;

      // The units of StandardModel_SLHA2 are GeV; here we are using eV.
      result = 1e9 * ( *Param["mNu1"] + *Param["mNu2"] + *Param["mNu3"] );
    }

    // Returns the effective number of ultrarelativistic species today
    void get_N_ur(double& result)
    {
      using namespace Pipes::get_N_ur;

      // The units of StandardModel_SLHA2 are GeV; here we are using eV.
      std::vector<double> nuMasses{
        1e9*(*Param["mNu1"]), 1e9*(*Param["mNu2"]), 1e9*(*Param["mNu3"])
      };

      // Count the nonzero entries
      auto isNonZero = [](double i) {return i > 0.;};
      int N_ncdm = std::count_if(nuMasses.begin(), nuMasses.end(), isNonZero);

      // Value of N_ur depends on the number of massive neutrinos
      switch (N_ncdm)
      {
        case 1:
          result = 2.0318;  // N_ur (today) = 2.0318 for 1 massive neutrino at CMB release
          break;
        case 2:
          result = 1.0186;  // N_ur (today) = 1.0186 for 2 massive neutrino at CMB release
          break;
        case 3:
          result = 0.00541;  // N_ur (today) = 0.00541 for 3 massive neutrinos at CMB release
          break;
        case 0:
          result = *Dep::Neff_SM;
          break;
        default:
          {
            std::ostringstream err;
            err << "You are asking for more than three massive neutrino species.\n";
            err << "Such a case is not implemented in CosmoBit. ";
            err << "If you want to consider this you can add it to the function ";
            err << "'get_N_ur' of the capability 'N_ur'.";
            CosmoBit_error().raise(LOCAL_INFO, err.str());
          }
      }

      // If "etaBBN_rBBN_rCMB_dNurBBN_dNurCMB" is in use, the result will
      // be scaled and gets extra contributions
      if (ModelInUse("etaBBN_rBBN_rCMB_dNurBBN_dNurCMB"))
      {
        // Check if the input for Delta N_ur is negative (unphysical)
        // NOTE: CosmoBit performs no sanity checks if you allow negative Delta N_ur; you're on your own.
        static bool allow_negative_delta_N_ur = runOptions->getValueOrDef<bool>(false,"allow_negative_delta_N_ur");

        // Get values of the temperature ratio and any ultrarelativistic contribution.
        double dNurCMB = *Param["dNur_CMB"];
        double rCMB = *Param["r_CMB"];

        // Only let the user have negative contributions to NEff from Delta N_ur if they've signed off on it.
        if ( (!allow_negative_delta_N_ur) && (dNurCMB < 0.0) )
        {
          std::ostringstream err;
          err << "A negative value for \"dNur_CMB\" is unphysical and is not allowed in CosmoBit by default!\n\n";
          err << "If you want to proceed with negative values, please add\n\n";
          err << "  - module: CosmoBit\n";
          err << "    options:\n";
          err << "      allow_negative_delta_N_ur: true\n\n";
          err << "to the Rules section of the YAML file.";
          CosmoBit_error().raise(LOCAL_INFO,err.str());
        }

        // If the check is passed, set the result.
        result = pow(rCMB,4)*(result) + dNurCMB;
      }
      logger() << "N_ur calculated to be " << result << EOM;
    }

    /// Temperature of non-CDM in the (cosmological) SM.
    void T_ncdm_SM(double &result)
    {
      using namespace Pipes::T_ncdm_SM;

      // Set to 0.71611 in units of photon temperature, above the instantaneous decoupling value (4/11)^(1/3)
      // to recover Sum_i mNu_i/omega = 93.14 eV resulting from studies of active neutrino decoupling (arXiv:hep-ph/0506164)
      result = 0.71611;
      // This standard value enters in many assumptions entering CLASS. Therefore changing this value in
      // the YAML file is disabled at the moment. If you still want to modify it, uncomment the line below and
      // you can set is as a runOption of this capability.
      // result = runOptions->getValueOrDef<double>(0.71611,"T_ncdm");
    }

    /// Temperature of non-CDM in non-standard theories.
    void T_ncdm(double &result)
    {
      using namespace Pipes::T_ncdm;

      // Set to 0.71611 in units of photon temperature, above the instantaneous decoupling value (4/11)^(1/3)
      // to recover Sum_i mNu_i/omega = 93.14 eV resulting from studies of active neutrino decoupling (arXiv:hep-ph/0506164)
      double T_ncdm_SM = 0.71611;

      // Take rCMB from the model "etaBBN_rBBN_rCMB_dNurBBN_dNurCMB"
      double rCMB = *Param.at("r_CMB");

      // Take the SM value of T_ncdm (T_nu) and multiply it with the value of rCMB
      result = rCMB*T_ncdm_SM;
    }

    /// Baryon-to-photon ratio (today) in LCDM
    void eta0_LCDM(double &result)
    {
      using namespace Pipes::eta0_LCDM;

      double ngamma, nb;
      ngamma = 16*pi*zeta3*pow(*Param["T_cmb"]*kB_eV_over_K/hc_eVcm,3); // photon number density today
      nb = *Param["omega_b"]*3*100*1e3*100*1e3/Mpc_SI/Mpc_SI/(8*pi*GN_cgs* m_proton*1e9*eV2g); // baryon number density today

      result =  nb/ngamma;
      logger() << "Baryon to photon ratio (eta) today computed to be " << result << EOM;
    }

    /// The total baryon content today.
    void compute_Omega0_b(double &result)
    {
      using namespace Pipes::compute_Omega0_b;

      double h = *Dep::H0/100.;
      result =*Param["omega_b"]/h/h;
    }

    /// The total cold dark matter content today.
    void compute_Omega0_cdm(double &result)
    {
      using namespace Pipes::compute_Omega0_cdm;

      double h = *Dep::H0/100.;
      result =*Param["omega_cdm"]/h/h;
    }

    /// The total photon content today.
    void compute_Omega0_g(double &result)
    {
      using namespace Pipes::compute_Omega0_g;

      double h = *Dep::H0/100.;
      result = (4.*sigmaB_SI/c_SI*pow(*Param["T_cmb"],4.)) / (3.*c_SI*c_SI*1.e10*h*h/Mpc_SI/Mpc_SI/8./pi/GN_SI);
    }

    /// Number density of photons today
    void compute_n0_g(double &result)
    {
      using namespace Pipes::compute_n0_g;

      result = 2./pi/pi*zeta3 *pow(*Param["T_cmb"]*kB_eV_over_K,3.)/pow(hP_eVs*c_SI/2./pi,3)/100/100/100; // result per cm^3
    }

    /// The total ultrarelativistic content today.
    void compute_Omega0_ur(double &result)
    {
      using namespace Pipes::compute_Omega0_ur;

      double N_ur = *Dep::N_ur;
      double Omega0_g = *Dep::Omega0_g;
      result = (N_ur)*7./8.*pow(4./11.,4./3.)* Omega0_g;
    }

    /* Classy getter functions */

    /// Hubble
    void get_H0_classy(double &result)
    {
      using namespace Pipes::get_H0_classy;

      // Rescale by c [km/s]
      result = c_SI*BEreq::class_get_H0()/1000;
    }

    /// Functor that calculates Hubble rate at redshift z [km/s/Mpc]
    void get_H_at_z_classy(daFunk::Funk &result)
    {
      using  namespace Pipes::get_H_at_z_classy;

      result = daFunk::zero("z");
      result = result + daFunk::func(BEreq::class_get_Hz.pointer(), daFunk::var("z"));

      // As CLASS uses units of Mpc, the Hubble rate is returned in 1/Mpc.
      // Multiply with c (in m/s) and divide by 1e3 to get the result in km/s/Mpc.
      result = result * daFunk::cnst(Gambit::c_SI / 1e3);
    }

    /// Functor that calculates time since big bang at redshift z [s]
    void get_time_at_z_classy(daFunk::Funk &result)
    {
      using  namespace Pipes::get_time_at_z_classy;

      result = daFunk::zero("z");
      result = result + daFunk::func(BEreq::class_get_tz.pointer(), daFunk::var("z"));

      // As CLASS uses units of Mpc, the time is returned in Mpc.
      // Convert Mpc into m and divide by c to get the result in s.
      result = result * daFunk::cnst(Gambit::Mpc_SI / Gambit::c_SI);
    }

    /// Age of the universe (time since big bang at z=0) [s]
    void get_age_universe_from_time_at_z(double &result)
    {
      using namespace Pipes::get_age_universe_from_time_at_z;

      result = (*Dep::time_at_z)->bind("z")->eval(0.0);
    }

    /// Energy densities *today* (Omega0)

// TODO: Temporarily disabled until project is ready
/*
    /// Dark Energy
    void get_Omega0_Lambda_classy(double& result)
    {
      using namespace Pipes::get_Omega0_Lambda_classy;

      result = BEreq::class_get_Omega0_Lambda();
    }
*/
    /// Matter
    void get_Omega0_m_classy(double& result)
    {
      using namespace Pipes::get_Omega0_m_classy;

      result = BEreq::class_get_Omega0_m();
    }

    /// Radiation
    void get_Omega0_r_classy(double& result)
    {
      using namespace Pipes::get_Omega0_r_classy;

      result = BEreq::class_get_Omega0_r();
    }

    /// Ultra-relativistic
    void get_Omega0_ur_classy(double& result)
    {
      using namespace Pipes::get_Omega0_ur_classy;

      result = BEreq::class_get_Omega0_ur();
    }

    /// Non-cold dark matter
    void get_Omega0_ncdm_classy(double& result)
    {
      using namespace Pipes::get_Omega0_ncdm_classy;

      result = BEreq::class_get_Omega0_ncdm_tot();
    }

    /// returns S8 = sigma8 (Omega0_m/0.3)^0.5
    /// (sigma8:root mean square fluctuations density fluctuations within
    /// spheres of radius 8/h Mpc)
    void get_S8_classy(double& result)
    {
      using namespace Pipes::get_S8_classy;

      double sigma8 = BEreq::class_get_sigma8();
      double Omega0_m = *Dep::Omega0_m;

      result = sigma8*pow(Omega0_m/0.3, 0.5);
    }

    /// Effective number of neutrino species
    /// (mostly for cross-checking!)
    void get_Neff_classy(double& result)
    {
      using namespace Pipes::get_Neff_classy;

      result = BEreq::class_get_Neff();
    }

    /// Optical depth at reionisation
    void get_tau_reio_classy(double& result)
    {
      using namespace Pipes::get_tau_reio_classy;

      result = BEreq::class_get_tau_reio();
    }

    /// redshift of reionisation
    void get_z_reio_classy(double& result)
    {
      using namespace Pipes::get_z_reio_classy;

      result = BEreq::class_get_z_reio();
    }

    /// Comoving sound horizon at baryon drag epoch
    void get_rs_drag_classy(double& result)
    {
      using namespace Pipes::get_rs_drag_classy;

      result = BEreq::class_get_rs();
    }

  } // namespace CosmoBit
} // namespace Gambit
