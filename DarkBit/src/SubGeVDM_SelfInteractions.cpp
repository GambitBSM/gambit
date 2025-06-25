//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Likelihood for angular and velocity-dependent self-scattering
///  cross-section based on evaporation of sub-cluster
///  in Bullet cluster collision.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Sowmiya Balan
///          (sowmiya.balan@kit.edu)
///  \date 2023 December
///
///
///  *********************************************

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/Utils/util_functions.hpp"
#include "gambit/Utils/ascii_table_reader.hpp"
#include "gambit/DarkBit/DarkBit_rollcall.hpp"
#include "gambit/DarkBit/DarkBit_utils.hpp"


namespace Gambit
{
  namespace DarkBit
  {
    class subgev_self_interactions
    {
      private:

        // Cluster dynamics measurements required for immediate evaporation cross-section calculation
        const double beta_rel = 0.013;
        const double kappa = 0.7627;

        //Cross-sections for SubGeV_fermion model
        double sigma_imd_rep_f(double sigma0, double w)
        {
          double r = pow(w*beta_rel,2);
          double r2 = pow(r,2);
          double factor = 8*M_PI*sigma0;
          double temp1 = (4*(-1+kappa)*r*(2+r));
          double temp2 = ((4+4*r-(-2+kappa)*kappa*r2)*log(2-(-2+kappa)*r));
          double temp3 = ((-2+(-2+kappa)*r)*(2+kappa*r)*log(2+kappa*r));
          double denominator = (r*(2+r)*(-4-4*r+(-2+kappa)*kappa*r2));
          return (factor*(temp1 + temp2 + temp3))/denominator;
        }

        double sigma_imd_att_f(double sigma0, double w, double m_Ap, double gamma_Ap)
        {
          double r = pow(w*beta_rel,2);
          double r2 = pow(r,2);
          double factor = 2*M_PI*sigma0;
          double temp1 = ((2*(-1+kappa)*r)*\
                          (pow(m_Ap,2)*(-16+4*pow(w,2)*(8-3*pow(beta_rel,2))\
                                              +pow(w,4)*(-64+3*(-2+kappa)*kappa*pow(beta_rel,4)))\
                            -(4*pow(gamma_Ap,2))));
          double temp2 = (-4-4*r+(-2+kappa)*kappa*r2);
          double temp3 = ((6*pow(m_Ap,2)*(-1+4*pow(w,2)))*(log((2+(2-kappa)*r)/(2+kappa*r))));
          double denominator = (r*(pow((m_Ap-4*m_Ap*pow(w,2)),2)+pow(gamma_Ap,2)));
          return (factor*(-temp1/temp2 + temp3))/denominator;
        }

        double sigma_tc_rep_f(double sigma0, double w)
        {
          double r = pow(w*beta_rel,2);
          double r2 = pow(r,2);
          double factor = -16*M_PI*sigma0;
          double temp1 = (r*log(2)+log(8));
          double temp2 = (-3*(2+r)*log(2+r));
          double temp3 = ((3+2*r)*log(2+2*r));
          double denominator = (r2*(2+r));
          return (factor*(temp1 + temp2 + temp3))/denominator;
        }

        double sigma_tc_att_f(double sigma0, double w, double m_Ap, double gamma_Ap)
        {
          double r = pow(w*beta_rel,2);
          double r2 = pow(r,2);
          double factor = 2*M_PI*sigma0;
          double temp1 = (3*pow(m_Ap,2)*r2 - 4*(4*pow(m_Ap,2)*(1-5*pow(w,2)+4*pow(w,4))+pow(gamma_Ap,2))*log(2));
          double temp2 = (4*(-pow(m_Ap,2)*(-1+4*pow(w,2))*(8+pow(w,2)*(-8+3*pow(beta_rel,2)))+2*pow(gamma_Ap,2))*log(2+r));
          double temp3 = (4*(pow(m_Ap,2)*(-1+4*pow(w,2))*(4+pow(w,2)*(-4+3*pow(beta_rel,2)))- pow(gamma_Ap,2))*log(2+2*r));
          double denominator = (r2*(pow((m_Ap-4*m_Ap*pow(w,2)),2)+pow(gamma_Ap,2)));
          return (factor*(temp1 + temp2 + temp3))/denominator;
        }

        //Cross-sections for SubGeV_scalar model
        double sigma_imd_rep_s(double sigma0, double w)
        {
          double r = pow(w*beta_rel,2);
          double r2 = pow(r,2);
          double factor = 16*M_PI*sigma0;
          double temp1 = (2*(-1+kappa)*r*(2+r));
          double temp2 = ((-2+(-2+kappa)*r)*(2+kappa*r)*log(2-(-2+kappa)*r));
          double temp3 = ((4+4*r-(-2+kappa)*kappa*r2)*log(2+kappa*r));
          double denominator = (r*(2+r)*(-4-4*r+(-2+kappa)*kappa*r2));
          return (factor*(temp1 + temp2 + temp3))/denominator;
        }

        double sigma_imd_att_s(double sigma0, double w, double m_Ap, double gamma_Ap)
        {
          double r = pow(w*beta_rel,2);
          double r2 = pow(r,2);

          // only t-channel
          double factor = 16*M_PI*sigma0;
          double temp1 = (-1+kappa);
          double denominator = (-4-4*r+(-2+kappa)*kappa*r2);
          return (factor*temp1)/denominator;
        }

        double sigma_tc_rep_s(double sigma0, double w)
        {
          double r = pow(w*beta_rel,2);
          double r2 = pow(r,2);
          double factor = 16*M_PI*sigma0;
          double temp1 = (log(1+r));
          double denominator = (r*(2+r));
          return (factor*temp1)/denominator;
        }

        double sigma_tc_att_s(double sigma0, double w, double m_Ap, double gamma_Ap)
        {
          double r = pow(w*beta_rel,2);
          double r2 = pow(r,2);

          // only t-channel
          double factor = 8*M_PI*sigma0 ;
          double temp1 = (2*log(1+r/2));
          double temp2 = (log(1+r));
          double denominator = r2;
          return (factor*(temp1-temp2))/denominator;
        }

      public:

        double (subgev_self_interactions::*sigma_imd_rep)(double, double);
        double (subgev_self_interactions::*sigma_imd_att)(double, double, double, double);
        double (subgev_self_interactions::*sigma_tc_rep)(double, double);
        double (subgev_self_interactions::*sigma_tc_att)(double, double, double, double);

        // Defining cross-sections corresponding to model in use
        subgev_self_interactions(std::string model)
        {
          logger() << LogTags::debug << "\nInitiating subgev_self_interactions class\n" << EOM;

          if(model=="SubGeVDM_fermion")
          {
            sigma_imd_rep = &subgev_self_interactions::sigma_imd_rep_f;
            sigma_imd_att = &subgev_self_interactions::sigma_imd_att_f;
            sigma_tc_rep  = &subgev_self_interactions::sigma_tc_rep_f;
            sigma_tc_att  = &subgev_self_interactions::sigma_tc_att_f;
          }
          else if(model=="SubGeVDM_scalar")
          {
            sigma_imd_rep = &subgev_self_interactions::sigma_imd_rep_s;
            sigma_imd_att = &subgev_self_interactions::sigma_imd_att_s;
            sigma_tc_rep  = &subgev_self_interactions::sigma_tc_rep_s;
            sigma_tc_att  = &subgev_self_interactions::sigma_tc_att_s;
          }
        }
    };

    class bullet_cluster_lnL
    {
      private:

        // Observed MLR of the Bullet Cluster in I-band (units: M_o/L_o)
        const double mlr_obs_i = 179;
        const double error_obs_i = 11;

        // Fraction of gas within within 250kpc of MC mass peak (10.1086/508601)
        const double fg_mc = 0.09;
        const double error_fg_mc = 0.01;

        // Gas to DM ratio derived from gas fractions
        const double g_i = 0.0989;
        const double error_g_i = 0.0101;
        const double g_f = 0.0417;
        const double error_g_f = 0.01;

      public:

        std::vector<double> mlr_sample;

        // Constructor
        bullet_cluster_lnL(std::string file)
        {
          logger() << LogTags::debug << "\nInitiating bullet_cluster_lnL class\n" << EOM;

          // Loading initial mlr sample over which likelihood is marginalized
          // Check if file exists.
          if (not(Utils::file_exists(file)))
          {
            DarkBit_error().raise(LOCAL_INFO, "ERROR! File '"+file+"' not found!");
          } else {
            logger() << LogTags::debug << "Reading data from file '"+file+"." << EOM;
          }

          // Read numerical values from data file.
          ASCIItableReader tab (file);
          tab.setcolnames("x");
          mlr_sample = tab["x"];
        }

        // Destructor
        ~bullet_cluster_lnL()
        {
        }

        //Gas mass loss
        double mgf_to_mgi(double dm_mass_loss)
        {
          return g_f/g_i * (1-dm_mass_loss);
        }

        //Errors
        double error_gfgi(double dm_mass_loss)
        {
          double x = mgf_to_mgi(dm_mass_loss);
          return sqrt( pow((error_g_f * x/g_f),2) + \
                       pow((error_g_i * x/g_i),2));
        }

        double error_tml(double dm_mass_loss)
        {
          double x = mgf_to_mgi(dm_mass_loss);
          double error_x = error_gfgi(dm_mass_loss);
          return sqrt(pow((error_fg_mc * (1-x-dm_mass_loss)),2) + pow((error_x * fg_mc),2));
        }

        double error_tot(double dm_mass_loss)
        {
          double error_theory = error_tml(dm_mass_loss);
          return sqrt(pow(error_obs_i,2) + pow(error_theory,2));
        }

        // Likelihood evaluator
        double margloglike(double dm_loss)
        {
          // likelihood for "total" mass loss "within 150kpc" (including "imd and cml" evap) marginalized over prior for mlr_ini
          double x = mgf_to_mgi(dm_loss);
          double total_mass_loss = dm_loss*(1-fg_mc) + fg_mc*(1-x);
          double error_total = error_tot(dm_loss);
          double margLike = 0;
          for (int i = 0; i < mlr_sample.size(); i++) {
          margLike += exp(-1/(2*pow((error_total),2))*pow((mlr_obs_i- mlr_sample[i]*(1-total_mass_loss)),2));
          }
          double margLike_c = std::max(1e-30, std::min(margLike, 1e30));

          return log(margLike_c);
        }
    };

    void calc_bullet_cluster_DMmassLoss(double& result)
    {
      using namespace Pipes::calc_bullet_cluster_DMmassLoss;

      double depth = 6.432e-05; // GeV^3

      // Import Spectrum objects
      const Spectrum& spec = *Dep::SubGeVDM_spectrum;
      const SubSpectrum& he = spec.get_HE();

      // Import coupling
      double gDM = he.get(Par::dimensionless,"gDM");
      double alphaDM = pow(gDM,2)/(4*M_PI);

      // Import masses
      double mDM = spec.get(Par::Pole_Mass, "DM");
      double mAp = spec.get(Par::Pole_Mass, "Ap");

      // Define self-scaterring parameters
      double sigma0 = pow(alphaDM*mDM,2)/pow(mAp,4);
      double w = mDM/mAp;

      double fDM = *Dep::RD_fraction;
      ddpair aDM_pair = *Dep::RD_oh2_aDM;
      double fChiBar = (aDM_pair.second*fDM)/2; // (fsym/fDM * fDM)/2
      double fChi = fDM - fChiBar;

      // Import decay table from DecayBit
      const DecayTable* tbl = &(*Dep::decay_rates);
      // Save dark photon width for later
      double gammaAp = tbl->at("Ap").width_in_GeV;

      static std::string model;
      if (ModelInUse("SubGeVDM_scalar")){
        model = "SubGeVDM_scalar";
      }
      else if (ModelInUse("SubGeVDM_fermion")){
        model = "SubGeVDM_fermion";
      }
      else
      {
        DarkBit_error().raise(LOCAL_INFO, "ERROR! Model not compatible with implementation of bullet cluster likelihood.");
      }

      //Initializing class for cross-section evaluations corresponding to model in use
      static subgev_self_interactions subgev_self_interactions_obj(model);

      double sigmaImdRep = (subgev_self_interactions_obj.*(subgev_self_interactions_obj.sigma_imd_rep))(sigma0,w);
      double sigmaImdAtt = (subgev_self_interactions_obj.*(subgev_self_interactions_obj.sigma_imd_att))(sigma0,w,mAp,gammaAp);
      double sigmaTcRep  = (subgev_self_interactions_obj.*(subgev_self_interactions_obj.sigma_tc_rep))(sigma0,w);
      double sigmaTCAtt  = (subgev_self_interactions_obj.*(subgev_self_interactions_obj.sigma_tc_att))(sigma0,w,mAp,gammaAp);

      double sigmaRep = sigmaImdRep+sigmaTcRep;
      double sigmaAtt = sigmaImdAtt+sigmaTCAtt;
      double sigma_eff_chi = fChi*sigmaRep + fChiBar*sigmaAtt;
      double sigma_eff_chibar = fChiBar*sigmaRep + fChi*sigmaAtt;

      double dm_loss = fChi*(1-exp(-depth*sigma_eff_chi/mDM)) +\
                fChiBar*(1-exp(-depth*sigma_eff_chibar/mDM));

      result = dm_loss;
    }

    void calc_bullet_cluster_lnL(double& result)
    {
      using namespace Pipes::calc_bullet_cluster_lnL;
      double DMmassLoss = *Dep::DM_mass_loss;

      static std::string inital_mlr_prior = runOptions->getValueOrDef<std::string>("lognormal_mlr","initial_mlr_prior");

      static std::string lnL_file_path;

      if (inital_mlr_prior == "lognormal_mlr")
      {
        lnL_file_path = GAMBIT_DIR "/DarkBit/data/BulletCluster/mlr_sample_pessimistic.dat";
      }
      else if (inital_mlr_prior == "main_cluster_mlr")
      {
        lnL_file_path = GAMBIT_DIR "/DarkBit/data/BulletCluster/mlr_sample_optimistic.dat";
      }
      else
      {
        DarkBit_error().raise(LOCAL_INFO, "ERROR! Prior for initial MLR marginalisation can only be over the observed \
        I-band MLR distribution ('mlr_distribution') or over a Gaussian defined by observed main cluster MLR \
        ('main_cluster_mlr').");
      }

      static bullet_cluster_lnL bullet_cluster_lnL_obj(lnL_file_path);

      result = bullet_cluster_lnL_obj.margloglike(DMmassLoss);
    }
  }
}
