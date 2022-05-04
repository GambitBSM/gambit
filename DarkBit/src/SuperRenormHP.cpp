//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Super Renormalizable Higgs Portal DM specific module functions for DarkBit
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Iñigo Saez Casares
///          (inigo.saez_casares@ens-paris-saclay.fr)
///  \date 2019 December
///
///  *********************************************

// TODO: Temporarily disabled until project is ready
/*
#include <algorithm>
#include <cmath>
#include <math.h>
#include <type_traits>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <functional>

#include <gsl/gsl_math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_monte_plain.h>
#include <gsl/gsl_monte_vegas.h>
#include <gsl/gsl_integration.h>
#include <gsl/gsl_min.h>
#include <gsl/gsl_interp.h>
#include <gsl/gsl_spline.h>
#include <gsl/gsl_sf_bessel.h>

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/Elements/spectrum_helpers.hpp"
#include "gambit/Utils/util_functions.hpp"
#include "gambit/Utils/ascii_table_reader.hpp"
#include "gambit/Utils/numerical_constants.hpp"
#include "gambit/Utils/statistics.hpp"
#include "gambit/DarkBit/DarkBit_rollcall.hpp"
#include "gambit/DarkBit/DarkBit_utils.hpp"

namespace Gambit
{
  namespace DarkBit
  {

    ////////////////////////////////////////////////////////////////////
    //                                                                //
    //      General Functions and Classes for Higgs Portal DM         //
    //                                                                //
    ////////////////////////////////////////////////////////////////////

    // \brief Supporting classes and functions for the Higgs Portal DM module.
    

    //------------- Numerical constants and other useful things -------------//

    // masses
    const double Mp = Gambit::m_planck; // Planck mass [GeV]
    const double me = Gambit::m_electron*1e9; // electron mass [eV]
    const double mH = 125.1*1e9; // Higgs boson mass [eV] (PDG 2019)
    const double mT = 172.9*1e9; // top quark mass [eV] (PDG 2019)

    // mathematical constants
    const double pi=Gambit::pi;

    // physical constants
    const double alphaEM = Gambit::alpha_EM; // fine structure constant
    const double alphaS = pi; // strong coupling constant, don't use this (take from spectrum)
    const double v = 246e9; // electroweak vev [eV]
    const double hbar_GeV = Gambit::hbar; // reduced Planck constant [GeV.s]
    const double hbar_eV = Gambit::hbar*1e9; // reduced Planck constant [eV.s]
    const double hbar_cgs = 1.054571818e-27; // reduced Planck constant [cgs]
    const double cs = Gambit::s2cm; // speed of light [cm/s]
    const double kb = Gambit::K2eV; // Boltzmann constant [eV/K]
    const double G_cgs = 6.674e-8; // Gravitational constant [cm³/g/s²]
    const double G_SI = 6.674e-11; // Gravitational constant [m³/kg/s²]
    const double Mpc_2_km = 3.0857e19; // Mpc to km
    const double kg_2_GeV = 1.7827e27; // kg to GeV

    // cosmological constants
    const double s0(2891); // current entropy density [1/cm³]
    // const double rhoC(4.84e3); // current critical density [eV/cm³]

    // astrophysical constants
    const double r0(26.2225e21); // Sun's distance from the galactic center [cm]
    const double Rsun(5.9598e10); // Solar radius [cm]
    const double L0 = 2.388672e45; // solar photon luminosity [eV/s]
    const double rho0(0.3e9); // local DM density (Milky Way) [eV/cm³]

    // other constants
    const double C(50./27.); // loop function from the decay of the Higgs boson into two photons

    // Minimum finite result returnable from log(double x);
    const double logmin = log(std::numeric_limits<double>::min());




    ////////////////////////////////////////////////////////////////////
    //            Support class to handle Solar models                //
    ////////////////////////////////////////////////////////////////////

    // gsl error handler
    void handler_Ls (const char * reason, const char * file, int line, int gsl_errno)
    {
      if (gsl_errno == 15)
      {
        throw gsl_errno;
      }

      if (gsl_errno == 1)
      {
        std::cerr << "gsl: " << file << ":" << line << ": ERROR: " << reason << " and  gsl_errno = " << gsl_errno << std::endl;
        std::cerr << "it seems like you are trying to scan DM masses <= 0.5eV, solar neutrino likelihoods only work for DM masses > mMin = 0.5eV!" << std::endl;
        std::cerr << "if you want to change the value of mMin, you can do it from DarkBit/src/SuperRenormHP.cpp and recompute the interpolation tables(delete the existing one and it will be done automatically), but be careful to check to convergence with the new values! you may have to increase the number of points in the interpolation routine" << std::endl;
      }
      else { std::cerr << "gsl: " << file << ":" << line << ": ERROR: " << reason << " and  gsl_errno = " << gsl_errno << std::endl; abort(); }
    }

    const double da = 1.66053906660e-24; // dalton to g


    class StellarModel
    {
      public :

        StellarModel (std::string datafile);

        double sigmaL (double const& w, double const& r);
        double getQuantity (std::string const& quantity, double const& r);
        double L_integrated (double const& mS);
        void Ls_interpolate ();
        double Ls (double const& mS, double const& theta);
        double PhiB8 (double const& mS, double const& theta);

        ~StellarModel();

      private :

        int m_nbins;
        const std::vector<std::string> m_names = {"Mass", "Radius", "Temp", "Rho", "Pres", "Lumi", "H1", "He4", "He3", "C12", "C13", "N14", "N15", "O16", "O17", "O18", "Ne", "Na", "Mg", "Al", "Si", "P", "S", "Cl", "Ar", "K", "Ca", "Sc", "Ti", "V", "Cr", "Mn", "Fe", "Co", "Ni"};
        const std::vector<std::string> m_elements = {"H1", "He4", "He3", "C12", "C13", "N14", "N15", "O16", "O17", "O18", "Ne", "Na", "Mg", "Al", "Si", "P", "S", "Cl", "Ar", "K", "Ca", "Sc", "Ti", "V", "Cr", "Mn", "Fe", "Co", "Ni"};
        // Ionisation of species i assuming full ionisation.
        const std::vector<double> m_Z = {1.0, 2.0, 2.0, 6.0, 6.0, 7.0, 7.0, 8.0, 8.0, 8.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0, 21.0, 22.0, 23.0, 24.0, 25.0, 26.0, 27.0, 28.0};
        // Atomic weight of species i (exact weight if isotope is known OR estimate from average solar abundance from data if available OR estimate from natural terrestrial abundance).
        const std::vector<double> m_A = {1.007825, 4.002603, 3.016029, 12.000000, 13.003355, 14.003074, 15.000109, 15.994915, 16.999132, 17.999160, 20.1312812, 22.989769, 24.3055, 26.9815385, 28.085, 30.973762, 32.0675, 35.4515, 36.275403, 39.0983, 40.078, 44.955908, 47.867, 50.9415, 51.9961, 54.938044, 55.845, 58.933194, 58.6934};

        ASCIItableReader m_model;
        std::map<std::string, gsl_spline*> m_interp;
        std::map<std::string, gsl_interp_accel*> m_acc;

        gsl_spline * m_Ls_interp;
        gsl_interp_accel * m_Ls_accel;

        const std::vector<std::string> m_quantities = {"Temp", "wp", "ne", "SumNz"};

    };

    StellarModel::StellarModel (std::string datafile)
    {
      m_model = ASCIItableReader(datafile);
      m_model.setcolnames(m_names);

      m_nbins = m_model["Mass"].size();

      std::vector<double> T, wp, ne, SumNz;

      double sumz, temp, sumz2;

      for (int i=0; i<m_nbins; ++i)
      {

        sumz = 0;
        sumz2 = 0;

        for (size_t j=0; j<m_elements.size(); ++j)
        {
          sumz += m_Z[j]*m_model[m_elements[j]][i]/m_A[j]/da*m_model["Rho"][i];
          sumz2 += m_Z[j]*m_Z[j]*m_model[m_elements[j]][i]/m_A[j]/da*m_model["Rho"][i];
        }

        temp = m_model["Temp"][i]*kb;

        T.push_back(temp);
        wp.push_back(sqrt(4*pi*alphaEM*sumz*cs*cs*cs*hbar_eV*hbar_eV*hbar_eV/me));
        ne.push_back(sumz);
        SumNz.push_back(sumz2);

      }

      std::map<std::string, std::vector<double>> quantities;

      quantities["Temp"] = T;
      quantities["wp"] = wp;
      quantities["ne"] = ne;
      quantities["SumNz"] = SumNz;

      const double * rr = m_model["Radius"].data();

      for (auto it=m_quantities.begin(); it!=m_quantities.end(); ++it)
      {
        m_interp[*it] = gsl_spline_alloc(gsl_interp_cspline, m_nbins);
        m_acc[*it] = gsl_interp_accel_alloc();
        gsl_spline_init(m_interp[*it], rr, quantities[*it].data(), m_nbins);
      }

      Ls_interpolate();
    }

    // function returning the interpolated quantities (Temp, wp, ne SumNz) at a given radius r inside the Sun
    double StellarModel::getQuantity (std::string const& quantity, double const& r)
    {
      return gsl_spline_eval(m_interp[quantity], r, m_acc[quantity]);
    }

    // function to compute the damping rate of longitudinal photons inside the Sun (inverse bremsstrahlung)
    double StellarModel::sigmaL (double const& w, double const& r)
    {
      double result = 0;

      double temp = getQuantity("Temp", r), ne = getQuantity("ne", r), wp = getQuantity("wp", r);
      double D = 64*pow(pi, 2)*pow(alphaEM, 3)*ne*getQuantity("SumNz", r);
      double N = 3*sqrt(2*pi*temp)*pow(me, 3./2.)*pow(w, 3);

      double x = w/2./temp;

      // tries to use the gsl_sf_bessel_K0 and sinh functions (fails if x is too big)
      try
      {
        double F = gsl_sf_bessel_K0(x)*sinh(x);
        result += D/N*F*pow(cs, 6)*pow(hbar_eV, 6);
      }

      // uses a first order development at high x instead of the full functions
      catch (int gsl_errno)
      {
        double F = sqrt(pi/2./x)*(1-(1/8./x));
        result += D/N*F*pow(cs, 6)*pow(hbar_eV, 6);
      }

      if (w > wp) { result += 8*pi*pow(alphaEM, 2)*ne*sqrt(1-pow(wp/w, 2))/pow(me, 3)/3.*pow(cs, 3)*pow(hbar_eV, 3); }

      return result;
    }

    StellarModel::~StellarModel()
    {
      for (auto it=m_quantities.begin(); it!=m_quantities.end(); ++it)
      {
        gsl_spline_free (m_interp[*it]);
        gsl_interp_accel_free(m_acc[*it]);
      }
    }

    struct my_f_params { double mS; StellarModel *model; };

    // function to be integrated for mS < w < inf and 0 < r < R0
    double myF (double const& w, double const& r, my_f_params *params)
    {
      StellarModel *model = params->model;
      double mS = params->mS;
      double N1, N2, D1, D2, D3;

      N1 = pow((w*w-mS*mS), 3./2.)*w*w;
      N2 = w*w*model->sigmaL(w, r);

      D1 = pow(2*pi, 3)*alphaEM;
      D2 = exp(w/model->getQuantity("Temp", r))-1;
      D3 = pow(w*model->sigmaL(w, r), 2)+pow(w*w-pow(model->getQuantity("wp", r), 2), 2);

      return N1*N2*pow(r, 2)/D1/D2/D3;
    }

    // gsl integrand remapped from (ms, +infinity) to (0, 1)
    double integrand (double x[], size_t dim, void *p)
    {
      struct my_f_params *params = (struct my_f_params *)p;
      (void)(dim);

      double mS = params->mS;

      double t = x[0], r = x[1];

      return myF(mS + (1-t)/t, r, params)/pow(t, 2);
    }

    const double mSmax = 1e5; // maximum mass up to which Ls is computed, for higher masses Ls is set to zero manually in the capability function

    double StellarModel::L_integrated (double const& mS)
    {
      const size_t dim = 2, calls = 1e5;
      double  xl[dim] = {0, 0.0006}, xu[dim] = {1, 0.9995};
      double result, abserr;

      gsl_monte_vegas_state *s = gsl_monte_vegas_alloc(dim);
      gsl_monte_vegas_init(s);

      gsl_rng *r = gsl_rng_alloc(gsl_rng_taus2);

      gsl_monte_function F;

      my_f_params params = {mS, this};

      F.f = &integrand;
      F.dim = dim;
      F.params = &params;

      gsl_monte_vegas_integrate(&F, xl, xu, dim, 1e4, r, s, &result, &abserr);
      do
      {
        gsl_monte_vegas_integrate (&F, xl, xu, dim, calls, r, s,
                                   &result, &abserr);
        std::cout << mS << " " << result << " " << abserr/result << " " << gsl_monte_vegas_chisq (s) << std::endl;
      }
    while ( (fabs (gsl_monte_vegas_chisq (s) - 1.0) > 0.2) or (abserr/result > 1e-3));

      std::cout << "Final: " << mS << " " << result << " " << abserr/result << " " << gsl_monte_vegas_chisq (s) << std::endl;

      gsl_monte_vegas_free(s);

      return 4*pi*pow(Rsun, 3)*result/pow(cs, 3)/pow(hbar_eV, 4);
    }

    void StellarModel::Ls_interpolate ()
    {
      const int nPoints = 100;
      const double mMin = 5e-4, mMax = mSmax;
      const double deltaM = log10(mMax/mMin)/nPoints;
      const std::string filename = GAMBIT_DIR "/DarkBit/data/SuperRenormHP_Ls.dat";
      std::vector<double> mS, Ls;

      // checks if an interpolation table file for Ls already exists and reads it if that is the case
      if (Utils::file_exists(filename))
      {
        ASCIItableReader table = ASCIItableReader(filename);
        table.setcolnames({"mS", "Ls"});
        mS = table["mS"];
        Ls = table["Ls"];
      }

      // builds an interpolation table for Ls and writes it in a file
      else
      {
        for (int i=0; i<=nPoints; ++i)
        {
          mS.push_back(mMin*pow(10, deltaM*i));
        }

        for (auto it=mS.begin(); it!=mS.end(); ++it)
        {
          Ls.push_back(L_integrated(*it));
        }

        std::ofstream fout (filename.c_str());

        for (size_t i=0; i<mS.size(); ++i)
        {
          fout << mS[i] << "  " << Ls[i] << std::endl;
        }

        fout.clear(); fout.close();
      }

      // interpolates Ls from the interpolation table
      m_Ls_interp = gsl_spline_alloc(gsl_interp_cspline, nPoints+1);
      m_Ls_accel = gsl_interp_accel_alloc();
      gsl_spline_init(m_Ls_interp, mS.data(), Ls.data(), nPoints+1);
    }

    // returns the value of the interpolated Ls for a given set of parameters (mS, theta)
    double StellarModel::Ls (double const& mS, double const& theta)
    {
      return gsl_spline_eval(m_Ls_interp, mS, m_Ls_accel)*pow(me/v*theta, 2);
    }

    ////////////////////////////////////////////////////////////////////
    //                   Capability functions                         //
    ////////////////////////////////////////////////////////////////////

    //------------- Process catalogue -------------//

    void TH_ProcessCatalog_SuperRenormHP(DarkBit::TH_ProcessCatalog &result)
    {
      using namespace Pipes::TH_ProcessCatalog_SuperRenormHP;
      using std::vector;
      using std::string;

      // Initialize empty catalog and decay channel
      TH_ProcessCatalog catalog;
      TH_Process process_dec("S");

      ///////////////////////////////////////
      // Import particle masses and couplings
      ///////////////////////////////////////

      // Convenience macros
      #define getSMmass(Name, spinX2)                                           \
       catalog.particleProperties.insert(std::pair<string, TH_ParticleProperty> \
       (Name , TH_ParticleProperty(SM.get(Par::Pole_Mass,Name), spinX2)));
      #define addParticle(Name, Mass, spinX2)                                   \
       catalog.particleProperties.insert(std::pair<string, TH_ParticleProperty> \
       (Name , TH_ParticleProperty(Mass, spinX2)));

      // Import Spectrum objects
      const Spectrum& spec  = *Dep::SuperRenormHP_spectrum;
      const SubSpectrum& he = spec.get_HE();
      const SubSpectrum& SM = spec.get_LE();
      const SMInputs& SMI   = spec.get_SMInputs();

      // Import couplings
      double theta = he.get(Par::dimensionless, "theta");
      double vev = he.get(Par::mass1,"vev");
      double C = 50./27.; // loop factor for the decay into two photons
      double alpha = 1./SMI.alphainv; // alpha_EM(mZ)^MSbar (5 active flavours)

      // Get SM pole masses
      getSMmass("e-_1",     1)
      getSMmass("e+_1",     1)
      getSMmass("e-_2",     1)
      getSMmass("e+_2",     1)
      getSMmass("e-_3",     1)
      getSMmass("e+_3",     1)
      getSMmass("Z0",     2)
      getSMmass("W+",     2)
      getSMmass("W-",     2)
      getSMmass("g",      2)
      getSMmass("gamma",  2)
      getSMmass("u_3",      1)
      getSMmass("ubar_3",   1)
      getSMmass("d_3",      1)
      getSMmass("dbar_3",   1)

      // Pole masses not available for the light quarks.
      addParticle("u_1"   , SMI.mU,  1) // mu(2 GeV)^MS-bar, not pole mass
      addParticle("ubar_1", SMI.mU,  1) // mu(2 GeV)^MS-bar, not pole mass
      addParticle("d_1"   , SMI.mD,  1) // md(2 GeV)^MS-bar, not pole mass
      addParticle("dbar_1", SMI.mD,  1) // md(2 GeV)^MS-bar, not pole mass
      addParticle("u_2"   , SMI.mCmC,1) // mc(mc)^MS-bar, not pole mass
      addParticle("ubar_2", SMI.mCmC,1) // mc(mc)^MS-bar, not pole mass
      addParticle("d_2"   , SMI.mS,  1) // ms(2 GeV)^MS-bar, not pole mass
      addParticle("dbar_2", SMI.mS,  1) // ms(2 GeV)^MS-bar, not pole mass
      // double alpha_s = SMI.alphaS;      // alpha_s(mZ)^MSbar

      // Masses for neutrino flavour eigenstates. Set to zero.
      // (presently not required)
      addParticle("nu_e",     0.0, 1)
      addParticle("nubar_e",  0.0, 1)
      addParticle("nu_mu",    0.0, 1)
      addParticle("nubar_mu", 0.0, 1)
      addParticle("nu_tau",   0.0, 1)
      addParticle("nubar_tau",0.0, 1)

      // Higgs-sector masses
      double mS = spec.get(Par::Pole_Mass,"S");
      double mH = spec.get(Par::Pole_Mass,"h0_1");
      addParticle("S",        mS, 0)  // Scalar DM
      addParticle("h0_1",     mH, 0)  // SM-like Higgs
      addParticle("pi0",   meson_masses.pi0,       0)
      addParticle("pi+",   meson_masses.pi_plus,   0)
      addParticle("pi-",   meson_masses.pi_minus,  0)
      addParticle("eta",   meson_masses.eta,       0)
      addParticle("rho0",  meson_masses.rho0,      1)
      addParticle("rho+",  meson_masses.rho_plus,  1)
      addParticle("rho-",  meson_masses.rho_minus, 1)
      addParticle("omega", meson_masses.omega,     1)

      // Get rid of convenience macros
      #undef getSMmass
      #undef addParticle


      // decay into two photons (through a loop of heavy fermions)
      double gamma_ph = (theta*theta*alpha*alpha*mS*mS*mS*C*C)/(256.*pi*pi*pi*vev*vev);

      TH_Channel dec_channel_ph(daFunk::vec<string>("gamma", "gamma"), daFunk::cnst(gamma_ph));
      process_dec.channelList.push_back(dec_channel_ph);

      // decay into e+/e- pair
      double me1 = SM.get(Par::Pole_Mass,"e-_1");
      double gamma_e1 = ( mS >= 2*me1 ) ? pow(theta,2)*pow(me1,2)*mS/(8*pi*pow(vev,2))*pow(1 - 4*pow(me1,2)/pow(mS,2), 3./2.) : 0;

      TH_Channel dec_channel_e1(daFunk::vec<string>("e-_1", "e+_1"), daFunk::cnst(gamma_e1));
      process_dec.channelList.push_back(dec_channel_e1);

      // decay into mu+/mu- pair
      double me2 = SM.get(Par::Pole_Mass,"e-_2");
      double gamma_e2 = ( mS >= 2*me2 ) ? pow(theta,2)*pow(me2,2)*mS/(8*pi*pow(vev,2))*pow(1 - 4*pow(me2,2)/pow(mS,2), 3./2.) : 0;

      TH_Channel dec_channel_e2(daFunk::vec<string>("e-_2", "e+_2"), daFunk::cnst(gamma_e2));
      process_dec.channelList.push_back(dec_channel_e2);

      //////////////////////////////
      // Import Decay information //
      //////////////////////////////

      // Import decay table from DecayBit
      const DecayTable* tbl = &(*Dep::decay_rates);

      // Set of imported decays
      std::set<string> importedDecays;

      // Minimum branching ratio
      double minBranching = 0.;

      // Import relevant decays (only Higgs and subsequent decays)
      using DarkBit_utils::ImportDecays;
      // Notes: Virtual Higgs decays into offshell W+W- final states are not
      // imported.  All other channels are correspondingly rescaled.  Decay
      // into SS final states is accounted for, leading to zero photons.
      ImportDecays("h0_1", catalog, importedDecays, tbl, minBranching, daFunk::vec<std::string>("Z0", "W+", "W-"));

      // Add the decay process to the catalog
      catalog.processList.push_back(process_dec);

      // Validate
      // catalog.validate();

      result = catalog;
    } // function TH_ProcessCatalog_SuperRenormHP

    // capability function to provide the initial energy density as produced by the freeze-in mechanism (in GeV/cm^3)
    void SuperRenormHP_relic_density (double &result)
    {
      using namespace Pipes::SuperRenormHP_relic_density;
      double mS = *Param["mS"], theta = *Param["theta"];
      double lambda = *Param["lambda"];

      result = lambda*theta*theta*s0*mS*1e11;
    }

    // capability function to provide the total width of the S scalar (in GeV)
    void SuperRenormHP_width (double &result)
    {
      using namespace Pipes::SuperRenormHP_width;

      result = 0.;

      std::string DM_ID = *Dep::DarkMatter_ID;
      TH_ProcessCatalog catalog = *Dep::TH_ProcessCatalog;

      // Check whether the process catalog has the decay prosses
      if (Dep::TH_ProcessCatalog->find(DM_ID) != NULL)
      {
        // decay S -> gamma gamma
        const TH_Channel* dec_channel_ph = catalog.getProcess(DM_ID).find({"gamma", "gamma"});
        if (dec_channel_ph != NULL)
        {
          result += dec_channel_ph->genRate->bind()->eval();
        }

        // decay S -> e-_1 e+_1
        const TH_Channel* dec_channel_e1 = catalog.getProcess(DM_ID).find({"e-_1", "e+_1"});
        if (dec_channel_e1 != NULL)
        {
          result += dec_channel_e1->genRate->bind()->eval();
        }

        // decay S -> e-_2 e+_2
        const TH_Channel* dec_channel_e2 = catalog.getProcess(DM_ID).find({"e-_2", "e+2"});
        if (dec_channel_e2 !=NULL)
        {
          result += dec_channel_e2->genRate->bind()->eval();
        }
      }

    }

    // capability function to provide the lifetime of the S scalar (in s)
    void SuperRenormHP_lifetime (double &result)
    {
      using namespace Pipes::SuperRenormHP_lifetime;

      double width = *Dep::DM_width;

      result = 1/width*hbar_GeV;
    }

    void RD_oh2_SuperRenormHP (double &result)
    {
      using namespace Pipes::RD_oh2_SuperRenormHP;

      double RD = *Dep::DM_relic_density;

      double rhoC_over_h2 = 3*pow(100/Mpc_2_km, 2)*pow(Mp, 2)/(8*pi)/hbar_GeV/pow(cs, 3); // critical density un Gev/cm^3

      result = RD/rhoC_over_h2;
    }

    //------------- Functions to compute stellar cooling likelihoods -------------//

    // capability function to compute the solar DM luminosity
    void SuperRenormHP_solar_luminosity (double &result)
    {
      using namespace Pipes::SuperRenormHP_solar_luminosity;
      const double mS = *Param["mS"]*1e9, theta = *Param["theta"];

      gsl_error_handler_t *old_handler = gsl_set_error_handler (&handler_Ls);

      static StellarModel model (GAMBIT_DIR "/DarkBit/data/SolarModel_AGSS09met.dat");

      if (mS < mSmax) { result = model.Ls(mS, theta); }

      else { result = 0; }

      gsl_set_error_handler (old_handler);
    }

    // capability function to compute the likelihood from the solar luminosity limit ( L_DM < 0.1*L0 ) (conservative limit)
    void calc_lnL_solar_luminosity (double &result)
    {
      using namespace Pipes::calc_lnL_solar_luminosity;

      const double limit = 0.1*L0;
      const double Ls = *Dep::solar_DM_luminosity;

      if (Ls > limit) { result = logmin; }

      else { result = 0; }
    }

    // values for the observed and SSM predicted neutrni fluxes as well as the corresponding errors taken from: arXiv:1605.06502v2
    // capability function to compute the predicted solar neutrino flux (B8)
    void SuperRenormHP_solar_neutrino_flux_B8 (double &result)
    {
      using namespace Pipes::SuperRenormHP_solar_neutrino_flux_B8;

      const double Ls = *Dep::solar_DM_luminosity;
      const double alpha = *Param["alpha"];

      const double Phi0 = 4.95e6;

      result = Phi0*pow(1+Ls/L0, alpha);
    }

    // capability function to compute the predicted solar neutrino flux (Be7)
    void SuperRenormHP_solar_neutrino_flux_Be7 (double &result)
    {
      using namespace Pipes::SuperRenormHP_solar_neutrino_flux_Be7;

      const double Ls = *Dep::solar_DM_luminosity;
      const double alpha = *Param["alpha"];

      const double Phi0 = 4.71e9;

      result = Phi0*pow(1+Ls/L0, alpha);
    }

    // capability function to compute the likelihood from the solar B8 neutrino flux
    void calc_lnL_solar_neutrino_B8 (double &result)
    {
      using namespace Pipes::calc_lnL_solar_neutrino_B8;

      const bool profile = runOptions->getValueOrDef<bool>(false, "profile_systematics");
      const double Phi_predicted = *Dep::solar_neutrino_flux_B8;

      const double Phi_obs = 5e6;
      const double sigma_obs = 0.03*Phi_obs, sigma_theo = 0.14*Phi_predicted;

      result = Stats::gaussian_loglikelihood(Phi_predicted, Phi_obs, sigma_theo, sigma_obs, profile);
    }

    // capability function to compute the likelihood from the solar Be7 neutrino flux
    void calc_lnL_solar_neutrino_Be7 (double &result)
    {
      using namespace Pipes::calc_lnL_solar_neutrino_Be7;

      const bool profile = runOptions->getValueOrDef<bool>(false, "profile_systematics");
      const double Phi_predicted = *Dep::solar_neutrino_flux_Be7;

      const double Phi_obs = 4.82e9;
      const double sigma_obs = 0.05*Phi_obs, sigma_theo = 0.07*Phi_predicted;

      result = Stats::gaussian_loglikelihood(Phi_predicted, Phi_obs, sigma_theo, sigma_obs, profile);
    }

    //------------- Functions to compute short range forces likelihoods -------------//

    // capability to provide the Higgs-Nucleon coupling constant fN, such as described in arXiv:1306.4710
    void func_Higgs_Nucleon_coupling_fN (Higgs_Nucleon_coupling_fN &result)
    {
      using namespace Pipes::func_Higgs_Nucleon_coupling_fN;

      const double sigmas = *Param["sigmas"]*1e-3, sigmal = *Param["sigmal"]*1e-3; // nuclear parameters in GeV (model input in MeV)
      const Spectrum SM = *Dep::SM_spectrum; // SM spectrum needed to get light quark masses

      const double z = 1.49; // isospin breaking ratio
      const double mu = SM.get(Par::mass1, "u_1"), md = SM.get(Par::mass1, "d_1"), ms = SM.get(Par::mass1, "d_2"); // light quark masses [GeV]
      const double mn = Gambit::m_neutron, mp = Gambit::m_proton; // nucleon masses [GeV]

      // intermediate quantities
      const double ml = 0.5*(mu+md);
      const double sigma0 = sigmal - sigmas*(2.*ml/ms);;
      const double y = 1 - sigma0/sigmal;

      std::vector<double> fu, fd, fs, mN = {mn, mp};

      for (size_t i(0); i<mN.size(); ++i)
      {
        fu.push_back(mu/(mu+md)*sigmal/mN[i]*(2*z+y*(1-z))/(1+z));
        fd.push_back(md/(mu+md)*sigmal/mN[i]*(2-y*(1-z))/(1+z));
        fs.push_back(ms/(mu+md)*sigmal/mN[i]*y);
      }

      result.neutron =  2./9. + 7./9.*(fu[0]+fd[0]+fs[0]);
      result.proton  =  2./9. + 7./9.*(fu[1]+fd[1]+fs[1]);
    }

    // Modified Inverse-Square Law (ISL) by adding a new Yukawa potential to the Newtonian gravitational potential: Vnew(r) = -(alpha*G*m1*m2)/r * exp(-r/lambda)
    // where alpha is the strenght of the new force and lambda its range

    // experimental parameters from Sushkov et al. 2011 arXiv:1108.2547
    const double rhoAu = 19, rhoTi = 4.5, rhog = 2.6, dAu = 700e-8, dTi = 100e-8, R = 15.6; // in cgs units

    // capability function returning the new force from the SuperRenormHP model for the experiment from Shuskov et al. 2011
    void New_Force_Sushkov2011_SuperRenormHP (daFunk::Funk &result)
    {
      using namespace Pipes::New_Force_Sushkov2011_SuperRenormHP;

      if (ModelInUse("symmetron"))
      {
        const double powv = *Param["vval"], powmu = *Param["mu"];
        double vval = pow(10, powv)*Gambit::m_planck_red, mu = pow(10, powmu);

        double Rad = 16.5; // sphere radius in cm
        double muR = mu*Rad/Gambit::gev2cm; // dimensionless term
        daFunk::Funk d = daFunk::var("d"); // separation between plates
        daFunk::Funk mux = d*1e-6/(Gambit::gev2cm*1e-2)*mu+muR;

        double GeV2Newtons = 8.19e5; // Newton/GeV^2

        daFunk::Funk force = 4.*M_PI*vval*vval*muR/sqrt(2)*tanh(mux/sqrt(2))*pow(1./cosh(mux/sqrt(2)),2.0) * GeV2Newtons; // take neg of force??
        result = force;
      }
      else
      {
        const double alpha = *Param["alpha"], lambda = *Param["lambda"]*1e2; // lambda in cm

        daFunk::Funk d = daFunk::var("d");

        daFunk::Funk force = 4*pow(pi, 2)*G_cgs*R*alpha*pow(lambda, 3)*exp(-d/lambda)*pow(rhoAu + (rhoTi-rhoAu)*exp(-dAu/lambda) + (rhog-rhoTi)*exp(-(dAu+dTi)/lambda), 2)*1e-5; // *1e-5 conversion from dyn(cgs) to N (SI)
        result = force;
      }

    }

    // capability function to compute the likelihood from Sushkov et al. 2011
    void calc_lnL_ShortRangeForces_Sushkov2011 (double &result)
    {
      using namespace Pipes::calc_lnL_ShortRangeForces_Sushkov2011;

      daFunk::Funk ForceNew = *Dep::New_Force_Sushkov2011*1e12; // new force in pN

      static ASCIItableReader data = ASCIItableReader(GAMBIT_DIR "/DarkBit/data/ShortRangeForces/Sushkov2011.dat");
      data.setcolnames({"distance", "Fres", "sigma", "binWidth"});
      static std::vector<double> distance = data["distance"]; // [microns]
      static std::vector<double> Fres = data["Fres"]; // [pN]
      static std::vector<double> sigma = data["sigma"]; // [pN]
      static std::vector<double> width = data["binWidth"]; // [microns]

      std::vector<boost::shared_ptr<daFunk::FunkBase>> ForceNewBinned;
      std::vector<boost::shared_ptr<daFunk::FunkBound>> FnewBound;

      double d, delta;

      for (size_t i(0); i<distance.size(); ++i)
      {
        d = distance[i]*1e-4;
        delta = width[i]*1e-4;
        ForceNewBinned.push_back(ForceNew->gsl_integration("d", d-delta/2, d+delta/2)/delta);
        FnewBound.push_back(ForceNewBinned[i]->bind());
      }

      std::vector<double> likelihood;
      double norm, Fnew;

      for (size_t i(0); i<distance.size(); ++i)
      {
        norm = 1.; // we take the likelihood ratio to avoid having different normalizations accross the parameter space;
        Fnew = FnewBound[i]->eval();
        likelihood.push_back( (Fnew<Fres[i]) ? norm : norm*exp(-pow(Fres[i]-Fnew, 2)/pow(sigma[i], 2)) );
      }

      result = log(*std::min_element(likelihood.begin(), likelihood.end())); // we take the minimum likelihood, since we don't have the correlations between data bins
    }

  }
}
*/
