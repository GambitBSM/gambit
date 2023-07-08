///  GAMBIT: Global and Modular BSM Inference Tool
///  *********************************************
///  \file
///
///  Xray likelihoods for DarkBit.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Patrick Stöcker
///          (stoecker@physik.rwth-aachen.de)
///  \date 2019 Sep
///
///  \author Iñigo Saez Casares
///          (inigo.saez_casares@ens-paris-saclay.fr)
///  \date 2021 April, May
///
///  *********************************************

// TODO: Temporarily disabled until project is ready
/*
#include <gsl/gsl_math.h>
#include <gsl/gsl_spline.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_monte_plain.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_min.h>

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/Utils/ascii_table_reader.hpp"
#include "gambit/Utils/statistics.hpp"

#include "gambit/DarkBit/DarkBit_rollcall.hpp"
#include "gambit/DarkBit/DarkBit_utils.hpp"

namespace Gambit
{
  namespace DarkBit
  {
    /////////////////////////////////////////////////////////////////
    //      Auxillary functions and classes for interpolation      //
    /////////////////////////////////////////////////////////////////

    // \brief Generic one-dimensional integration container for linear interpolation and cubic splines.

    // XrayInterpolator class: Provides a general 1-D interpolation container based on the gsl library.
    // Can be declared static for efficiency & easy one-time initialisation of interpolating functions.
    // (This is the twin sibling of AxionInterpolator in DarkBit/src/Axions.cpp)
    class XrayInterpolator
    {
      public:
        // Overloaded class creators for the XrayInterpolator class using the init function below.
        XrayInterpolator();
        XrayInterpolator(const std::vector<double> x, const std::vector<double> y, std::string type);
        XrayInterpolator(const std::vector<double> x, const std::vector<double> y);
        XrayInterpolator(std::string file, std::string type);
        XrayInterpolator(std::string file);
        XrayInterpolator& operator=(XrayInterpolator&&);
        // Destructor.
        ~XrayInterpolator();
        // Delete copy constructor and assignment operator to avoid shallow copies.
        XrayInterpolator(const XrayInterpolator&) = delete;
        XrayInterpolator operator=(const XrayInterpolator&) = delete;
        // Routine to access interpolated values.
        double interpolate(double x);
        // Routine to access upper and lower boundaries of available data.
        double lower();
        double upper();
      private:
        // Initialiser for the XrayInterpolator class.
        void init(std::string file, std::string type);
        void init(const std::vector<double> x, const std::vector<double> y, std::string type);
        // The gsl objects for the interpolating functions.
        gsl_interp_accel *acc;
        gsl_spline *spline;
        // Upper and lower boundaries available for the interpolating function.
        double lo;
        double up;
    };

    // Default constructor.
    XrayInterpolator::XrayInterpolator() {};

    // Initialiser for the XrayInterpolator class.
    void XrayInterpolator::init(const std::vector<double> x, const std::vector<double> y, std::string type)
    {
      int pts = x.size();
      // Get first and last value of the "x" component.
      lo = x.front();
      up = x.back();
      acc = gsl_interp_accel_alloc ();
      if (type == "cspline")
      {
        spline = gsl_spline_alloc (gsl_interp_cspline, pts);
      }
      else if (type == "linear")
      {
        spline = gsl_spline_alloc (gsl_interp_linear, pts);
      }
      else
      {
        DarkBit_error().raise(LOCAL_INFO, "ERROR! Interpolation type '"+type+"' not known to class XrayInterpolator.\n       Available types: 'linear' and 'cspline'.");
      };

      gsl_spline_init (spline, &x[0], &y[0], pts);
    };

    // Overloaded class creators for the XrayInterpolator class using the init function above.
    XrayInterpolator::XrayInterpolator(const std::vector<double> x, const std::vector<double> y, std::string type) { init(x, y, type); };
    XrayInterpolator::XrayInterpolator(const std::vector<double> x, const std::vector<double> y) { init(x, y, "linear"); };

    // Initialiser for the XrayInterpolator class.
    void XrayInterpolator::init(std::string file, std::string type)
    {
      // Check if file exists.
      if (not(Utils::file_exists(file)))
      {
        DarkBit_error().raise(LOCAL_INFO, "ERROR! File '"+file+"' not found!");
      } else {
        logger() << LogTags::debug << "Reading data from file '"+file+"' and interpolating it with '"+type+"' method." << EOM;
      };
      // Read numerical values from data file.
      ASCIItableReader tab (file);
      tab.setcolnames("x", "y");

      // for (int idx=1; idx < tab["x"].size(); idx++)
      // {
      //   std::cout << "x[" << idx << "] = " << tab["x"][idx] << "; dx = " << tab["x"][idx] -tab["x"][idx-1] << std::endl;
      //   if (tab["x"][idx] -tab["x"][idx-1] <= 0.0) std::cout << "OH NO" << std::endl;
      // }

      init(tab["x"],tab["y"],type);
    };

    // Overloaded class creators for the XrayInterpolator class using the init function above.
    XrayInterpolator::XrayInterpolator(std::string file, std::string type) { init(file, type); };
    XrayInterpolator::XrayInterpolator(std::string file) { init(file, "linear"); };

    // Move assignment operator
    XrayInterpolator& XrayInterpolator::operator=(XrayInterpolator&& interp)
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
    XrayInterpolator::~XrayInterpolator()
    {
      gsl_spline_free (spline);
      gsl_interp_accel_free (acc);
    }

    // Routine to access interpolated values.
    double XrayInterpolator::interpolate(double x) { return gsl_spline_eval(spline, x, acc); };

    // Routines to return upper and lower boundaries of interpolating function
    double XrayInterpolator::lower() { return lo; };
    double XrayInterpolator::upper() { return up; };

    ////////////////////////////////////////////////////
    //               Xray likelihoods                 //
    // -- based on likehoods for sterile neutrinos -- //
    ////////////////////////////////////////////////////

    void compute_lnL_Xray_WISPy(double& result)
    {
      using namespace Pipes::compute_lnL_Xray_WISPy;

      static XrayInterpolator WISPy_bound;
      static bool first = true;
      static std::pair<double,double> xlim;

      if (first)
      {
        WISPy_bound = std::move(XrayInterpolator(GAMBIT_DIR "/DarkBit/data/WISPy_bound.dat","linear"));
        xlim.first = WISPy_bound.lower();
        xlim.second = WISPy_bound.upper();
        first = false;
      }

      double t_universe = *Dep::age_universe; // Age of the Universe in seconds

      double logm = log10(*Param["mass"]) + 9; // In "DecayingDM_mixture", the mass is given in GeV. Need to convert it into eV
      double tau = *Param["lifetime"];   // lifetime is already in untis of s. No tranformation needed.
      double frac = *Param["fraction"];
      double BR_ph = *Param["BR_ph"];

      if (logm <= xlim.first || logm >= xlim.second)
      {
        // Bound can only be applied if log10(mass) is within the range of the table.
        result = 0.0;
      }
      else
      {
        double tau_bound = pow(10.,WISPy_bound.interpolate(logm));
        bool excluded = ((1./frac)*exp(t_universe/tau)*BR_ph*tau < tau_bound);
        result = (excluded ? -9.0 : 0.0);
      }
    }

    void compute_lnL_Xray_Integral_SPI_sterile_nu(double& result)
    {
      using namespace Pipes::compute_lnL_Xray_Integral_SPI_sterile_nu;

      static XrayInterpolator sin2_2t_bound;
      static bool first = true;
      static std::pair<double,double> xlim;

      if (first)
      {
        sin2_2t_bound = std::move(XrayInterpolator(GAMBIT_DIR "/DarkBit/data/Integral_sterile_nu_bound.dat","linear"));
        xlim.first = sin2_2t_bound.lower();
        xlim.second = sin2_2t_bound.upper();
        first = false;
      }

      double t_universe = *Dep::age_universe; // Age of the Universe in seconds

      double mass = *Param["mass"] * 1e6; // In "DecayingDM_mixture", the mass is given in GeV. Need to convert it into keV
      double tau = *Param["lifetime"];   // lifetime is already in untis of s. No tranformation needed.
      double frac = *Param["fraction"];
      double BR_ph = *Param["BR_ph"];

      if (mass <= xlim.first || mass >= xlim.second)
      {
        // Bound can only be applied if the mass is within the range of the table.
        result = 0.0;
      }
      else
      {
        double sin2_2t = sin2_2t_bound.interpolate(mass);
        double tau_bound = 2./1.36038e-32 * pow(1e10*sin2_2t,-1.)*pow(mass,-5.);
        bool excluded = ((1./frac)*exp(t_universe/tau)*BR_ph*tau < tau_bound);
        result = (excluded ? -9.0 : 0.0);
      }
    }

    void compute_lnL_Xray_M31_sterile_nu(double& result)
    {
      using namespace Pipes::compute_lnL_Xray_M31_sterile_nu;

      static XrayInterpolator sin2_2t_bound;
      static bool first = true;
      static std::pair<double,double> xlim;

      if (first)
      {
        sin2_2t_bound = std::move(XrayInterpolator(GAMBIT_DIR "/DarkBit/data/M31_sterile_nu_bound.dat","linear"));
        xlim.first = sin2_2t_bound.lower();
        xlim.second = sin2_2t_bound.upper();
        first = false;
      }

      double t_universe = *Dep::age_universe; // Age of the Universe in seconds

      double mass = *Param["mass"] * 1e6; // In "DecayingDM_mixture", the mass is given in GeV. Need to convert it into keV
      double tau = *Param["lifetime"];   // lifetime is already in untis of s. No tranformation needed.
      double frac = *Param["fraction"];
      double BR_ph = *Param["BR_ph"];

      if (mass <= xlim.first || mass >= xlim.second)
      {
        // Bound can only be applied if the mass is within the range of the table.
        result = 0.0;
      }
      else
      {
        double sin2_2t = sin2_2t_bound.interpolate(mass);
        double tau_bound = 2./1.36038e-32 * pow(1e10*sin2_2t,-1.)*pow(mass,-5.);
        bool excluded = ((1./frac)*exp(t_universe/tau)*BR_ph*tau < tau_bound);
        result = (excluded ? -9.0 : 0.0);
      }
    }

    void compute_lnL_Xray_NuSTAR_sterile_nu(double& result)
    {
      using namespace Pipes::compute_lnL_Xray_NuSTAR_sterile_nu;

      static XrayInterpolator sin2_2t_bound;
      static bool first = true;
      static std::pair<double,double> xlim;

      if (first)
      {
        sin2_2t_bound = std::move(XrayInterpolator(GAMBIT_DIR "/DarkBit/data/NuSTAR_sterile_nu_bound.dat","linear"));
        xlim.first = sin2_2t_bound.lower();
        xlim.second = sin2_2t_bound.upper();
        first = false;
      }

      double t_universe = *Dep::age_universe; // Age of the Universe in seconds

      double mass = *Param["mass"] * 1e6; // In "DecayingDM_mixture", the mass is given in GeV. Need to convert it into keV
      double tau = *Param["lifetime"];   // lifetime is already in untis of s. No tranformation needed.
      double frac = *Param["fraction"];
      double BR_ph = *Param["BR_ph"];

      if (mass <= xlim.first || mass >= xlim.second)
      {
        // Bound can only be applied if the mass is within the range of the table.
        result = 0.0;
      }
      else
      {
        double sin2_2t = sin2_2t_bound.interpolate(mass);
        double tau_bound = 2./1.36038e-32 * pow(1e10*sin2_2t,-1.)*pow(mass,-5.);
        bool excluded = ((1./frac)*exp(t_universe/tau)*BR_ph*tau < tau_bound);
        result = (excluded ? -9.0 : 0.0);
      }
    }

    //------------- Numerical constants and other useful things -------------//

    // masses
    const double Mp = Gambit::m_planck; // Planck mass [GeV]

    // mathematical constants
    const double pi=Gambit::pi;

    // physical constants
    const double hbar_GeV = Gambit::hbar; // reduced Planck constant [GeV.s]
    const double cs = Gambit::s2cm; // speed of light [cm/s]
    const double Mpc_2_km = 3.0857e19; // Mpc to km

    // Minimum finite result returnable from log(double x);
    const double logmin = log(std::numeric_limits<double>::min());

    ////////////////////////////////////////////////////////////////////
    //         Support class to handle X-ray experiments              //
    ////////////////////////////////////////////////////////////////////

    //------------- Class declaration -------------//

    class Xray
    {
      public:

        Xray(std::string experiment, double J_factor);
        double solidAngle(std::vector<double> lRange, std::vector<double> bRange);
        void set_deltaOmega();
        double getDeltaOmega() const;
        double getJ() const;
        double getEmin() const;
        double getEmax() const;
        double getDeltaE() const;
        int getFluxOrigin() const;

        double flux(double const& E);
        double sigma(double const& E);
        double fluxIntegrated(double const& E);
        double sigmaIntegrated(double const& E);
        double deltaE(double const& E);
        ~Xray();

      protected:

        double m_J; // astrophysical factor for the predicted photon flux from decaying DM
        double m_Emin; // minimum energy of the observations
        double m_Emax; // maximum energy of the observations
        double m_deltaOmega; // total solid angle of observation
        double m_deltaE; // energy resolution in percentage of the energy scale
        int m_fluxOrigin; // origin of observed flux: galactic (1), extra-galactic (2) or both (3)
        std::vector<std::vector<double> > m_lRange; // observation region in galactic coordinates (degrees)
        std::vector<std::vector<double> > m_bRange;
        std::string m_experiment;
        std::map<std::string, int> m_experimentMap;
    };

    // constructor
    Xray::Xray(std::string experiment, double J_factor) : m_J(J_factor), m_experiment(experiment), m_experimentMap({{"INTEGRAL", 1}, {"HEAO", 2}})
    {
      switch(m_experimentMap[m_experiment])
      {
        case 1 :
          m_Emin = 20e3;
          m_Emax = 2e6;
          m_lRange = { {-30., 30.} };
          m_bRange = { {-15., 15.} };
          m_deltaE = 8e3;
          m_deltaOmega = 0.542068;
          m_fluxOrigin = 1;
          break;

        case 2 :
          m_Emin = 3e3;
          m_Emax = 60e3;
          m_lRange = { {58., 109.}, {238., 289.} };
          m_bRange = { {-90., -20.}, {20., 90.} };
          m_deltaE = 0.3;
          m_deltaOmega = 1.17135;
          m_fluxOrigin = 3;
          break;

        default :
          throw std::runtime_error("Wrong experiment name in Xray object");
          break;
      }
      //set_deltaOmega();
    }

    //------------- Function returning the energy dispersion of the instrument -------------//

    double Xray::deltaE (double const& E)
    {
      switch(m_experimentMap[m_experiment])
      {
        case 1 :
          return m_deltaE;
          break;

        case 2 :
          return m_deltaE*E;
          break;

        default :
          return 1.;
          break;
      }
    }

    // ----------- Functions to compute the solid angle of observation -------------//

    // auxiliary function for gsl integration
    double deltaOmega (double x[], size_t dim, void *p)
    {
      (void)(p);
      (void)(dim);
      return cos(x[1]);
    }

    // computes the solide angle for a given galactic coordinates range (in degrees)
    double Xray::solidAngle(std::vector<double> lRange, std::vector<double> bRange)
    {
      const size_t dim = 2, calls = 1e8;
      const double xl[dim] = {lRange[0]*pi/180., bRange[0]*pi/180.}, xu[dim] = {lRange[1]*pi/180., bRange[1]*pi/180.};
      double result, abserr;

      gsl_monte_plain_state *s = gsl_monte_plain_alloc(dim);
      gsl_monte_plain_init(s);
      gsl_rng *r = gsl_rng_alloc(gsl_rng_taus2);

      gsl_monte_function F;

      F.f = &deltaOmega;
      F.dim = dim;
      F.params = 0;

      gsl_monte_plain_integrate(&F, xl, xu, dim, calls, r, s, &result, &abserr);

      gsl_monte_plain_free(s);  

      return result;
    }

    // sets the total solid angle of observation for the experiment
    void Xray::set_deltaOmega()
    {
      double result(0);
      for (size_t i=0; i<m_lRange.size(); ++i)
      {
        result += solidAngle(m_lRange[i], m_bRange[i]);
      }
      m_deltaOmega = result;
    }

    //------------- Functions to compute the photon flux and its standard deviation -------------//

    // differential photon flux [photons/keV/cm²/s]
    double Xray::flux(double const& E)
    {
      switch(m_experimentMap[m_experiment])
      {
        case 1 :
          // return 4.8e-8*pow(E/100e3,-1.55) + 6.6e-8*exp(-(E-50e3)/7.5e3);
          return 1.6e-7*exp(-(E-50e3)/7.7e3) + 0.92e-7*pow(E/100e3, -1.79) + 0.34e-7*pow(E/100e3, -0.95)*exp(-(E-100e3)/3411e3) + 67.3e-7/E;
          break;

        case 2 :
          return 7.877*pow(10., 0.87)*pow(E, -0.29)*exp(-(E/41.13e3))/E*m_deltaOmega;
          break;

        default :
          return 0.;
          break;
      }
    }

    // auxiliary function for gsl integration
    double flux_gsl(double x, void *p)
    {
      Xray *experiment = static_cast<Xray*>(p);
      return experiment->flux(x);
    }

    const double int_factor(1.1); // integration range = int_factor*energy dispersion instrument

    double Xray::fluxIntegrated(double const& E)
    {
      size_t n = 1e4;

      gsl_integration_workspace *w = gsl_integration_workspace_alloc(n);

      double epsabs = 0.;
      double epsrel = 1e-2;
      size_t limit = 1e3;
      double result, abserr;
      int key = 6;
      double delta = int_factor*deltaE(E);

      gsl_function F;
      F.function = &flux_gsl;
      F.params = this;

      gsl_integration_qag(&F, E-delta/2., E+delta/2., epsabs, epsrel, limit, key, w, &result, &abserr);

      gsl_integration_workspace_free(w);

      return result;
    }

    // standard deviation of the differential photon flux [photons/keV/cm²/s]
    double Xray::sigma(double const& E)
    {

      switch(m_experimentMap[m_experiment])
      {
        case 1 :
          // return sqrt(pow(pow(E/100e3,-1.55),2)*pow(0.6e-5,2) + pow(4.8e-8*1.55*pow(E/100e3,-2.55),2)*pow(0.25,2) + exp(-2*(E-50e3)/7.5e3)*pow(0.5e-8, 2.) + pow(6.6e-8, 2.)*pow((E-50e3)/pow(7.5e3, 2.), 2.)*exp(-2*(E-50e3)/7.5e3)*pow(1e3, 2.));
          return sqrt( pow(14.6e-4/E, 2) + pow(1.6e-7*(E-50e3)/7.7e3, 2) * pow(0.7e3, 2) * exp(-2.*(E-50e3)/7.7e3) + pow(0.4e-7, 2) * exp(-2.*(E-50e3)/7.7e3) + pow(0.34e-7*pow(E/100e3, -0.95), 2) * pow((E-100e3)/3411e3, 2) * exp(-(E-100e3)/3411e3) * pow(2371e3, 2));
          break;

        case 2 :
          return (flux(E)*E/m_deltaOmega)*0.02*m_deltaOmega/E;
          break;

        default :
          return 0.;
          break;
      }
    }

    // auxiliary function for gsl integration
    double sigma_gsl (double x, void *p)
    {
      Xray *experiment = static_cast<Xray*>(p);
      return pow(experiment->sigma(x), 2.);
    }


    double Xray::sigmaIntegrated(double const& E)
    {
      size_t n = 1e4;

      gsl_integration_workspace *w = gsl_integration_workspace_alloc(n);

      double epsabs = 0.;
      double epsrel = 1e-2;
      size_t limit = 1e3;
      double result, abserr;
      int key = 6;
      double delta = int_factor*deltaE(E);

      gsl_function F;
      F.function = &sigma_gsl;
      F.params = this;

      gsl_integration_qag(&F, E-delta/2., E+delta/2., epsabs, epsrel, limit, key, w, &result, &abserr);

      gsl_integration_workspace_free(w);

      return result;
    }

    //------------- Elevator functions -------------// 

    double Xray::getDeltaOmega() const { return m_deltaOmega; }

    double Xray::getJ() const { return m_J; }

    double Xray::getEmin() const { return m_Emin; }

    double Xray::getEmax() const { return m_Emax; }

    double Xray::getDeltaE() const { return m_deltaE; }

    int Xray::getFluxOrigin() const { return m_fluxOrigin; }

    // destructor
    Xray::~Xray() { }

    //------------- Functions to compute the age of the Universe at a given redshift -------------//

    // useful structure
    struct cosmology_params {double OmegaM; double OmegaR; double OmegaLambda; double H0;};

    // auxiliary function for gsl integration
    double age_f (double x, void *p)
    {
      cosmology_params *params = static_cast<cosmology_params*>(p);
      double OmegaM = params->OmegaM;
      double OmegaLambda = params->OmegaLambda;
      double OmegaR = params->OmegaR;
      double OmegaK = 0.;

      return 1./sqrt( OmegaM*pow(1+x, 5.) + OmegaLambda*pow(1+x, 2.) + OmegaK*pow(1+x, 4.) + OmegaR*pow(1+x, 6.) );
    }

    // computes the age of the Universe at a given redshift ([0] age, [1] abserr)
    std::vector<double> ageUniverse (double redshift, double OmegaM, double OmegaR, double OmegaLambda, double H0)
    {
      size_t n = 1e4; 

      gsl_integration_workspace *w =  gsl_integration_workspace_alloc(n);

      double epsabs = 0.;
      double epsrel = 1e-3;
      size_t limit = 1e3;
      double result, abserr;

      cosmology_params params = {OmegaM, OmegaR, OmegaLambda, H0};

      gsl_function F;
      F.function = &age_f;
      F.params = &params;

      gsl_integration_qagiu(&F, redshift, epsabs, epsrel, limit, w, &result, &abserr);

      gsl_integration_workspace_free(w);

      return {result/H0, abserr/H0};
    }

    //------------- Functions to compute X-ray likelihoods -------------//


    // useful structure
    struct XrayLikelihood_params {double mass; double tau; double gamma_ph; double fraction; Xray experiment; double OmegaDM; daFunk::Funk H_z; daFunk::Funk t_z; double ageUniverse;};

    // extra-galactic contribution to the differential photon flux [photons/eV/cm²/s]
    double dPhiEG(double const& E, XrayLikelihood_params *params)
    {
      double mass = params->mass; 
      double x = mass/2./E;
      double z = x - 1.;

      if (z<0) { return 0.; }

      else
      {
      Xray experiment = params->experiment;

      double tau = params->tau, gamma_ph = params->gamma_ph, fraction = params->fraction;
      double OmegaDM = params->OmegaDM;

      daFunk::Funk H_z = params->H_z;
      boost::shared_ptr<daFunk::FunkBound> H_z_bound = H_z->bind("z");

      double H0 = H_z_bound->eval(0)/Mpc_2_km; // H0 in 1/s
      double rhoC = 3*pow(H0, 2)*pow(Mp, 2)/(8*pi)/hbar_GeV/pow(cs, 3)*1e9; // critical density un ev/cm^3
      double density = fraction*OmegaDM*rhoC;
      double H = H_z_bound->eval(x)/Mpc_2_km; // H(x) in 1/s

      daFunk::Funk t_z = params->t_z;
      boost::shared_ptr<daFunk::FunkBound> t_z_bound = t_z->bind("z");

      double t = t_z_bound->eval(z);

      return experiment.getDeltaOmega()*2.*1./(4*pi)*(gamma_ph*density*cs*exp(-t/tau))/(mass*E)/H;
      }
    }

    const double s(1./3.); // standard deviation of the gaussian for the galactic emission line = s*energy dispersion instrument

    // galactic (Milky Way) contribution to the differential photon flux [photons/eV/cm²/s]
    double dPhiG(double const& E, XrayLikelihood_params *params)
    {
      double mass = params->mass, tau = params->tau, gamma_ph = params->gamma_ph, fraction = params->fraction;
      Xray experiment = params->experiment;

      double J = experiment.getJ();

      double t0 = params->ageUniverse;

      double sigma = s*experiment.deltaE(E); // standard deviation of the gaussian modelling the enery dispersion of the instrument

      return 2.*(gamma_ph*J*fraction*exp(-t0/tau))/(4.*pi*mass)/sqrt(2*pi*sigma*sigma)*exp(-pow(E-mass/2.,2)/(2*sigma*sigma));
    }

    // total predicted differential photon flux for a given X-ray experiment [photons/eV/cm²/s]
    double XrayPrediction(double const& E, XrayLikelihood_params *params)
    {
      Xray experiment = params->experiment;
      switch(experiment.getFluxOrigin())
      {
        case 1 :
          return dPhiG(E, params);

        case 2 :
          return dPhiEG(E, params);

        case 3 :
          return dPhiG(E, params) + dPhiEG(E, params);

        default :
          throw std::runtime_error("Wrong value for m_fluxOrigin in Xray class, allowed values are 1 (galactic flux), 2 (extra-galactic flux) and 3 (both)");
          break;
      }
    }

    // auxiliary function for gsl integration
    double XrayPredictionIntegrated_gsl(double x, void *p)
    {
      XrayLikelihood_params *params = static_cast<XrayLikelihood_params*>(p);

      return XrayPrediction(x, params);
    }

    // total predicted photon flux integrated over an interval deltaE, centered around E [photons/cm²/s]
    double XrayPredictionIntegrated(double const& E, XrayLikelihood_params *params)
    {
      size_t n = 1e4;

      gsl_integration_workspace *w =  gsl_integration_workspace_alloc(n);

      double epsabs = 0.;
      double epsrel = 1e-2;
      size_t limit = 1e3;
      double result, abserr;
      int key = 6;
      Xray experiment = params->experiment;
      double delta = int_factor*experiment.deltaE(E);

      gsl_function F;
      F.function = &XrayPredictionIntegrated_gsl;
      F.params = params;

      gsl_integration_qag(&F, E-delta/2., E+delta/2., epsabs, epsrel, limit, key, w, &result, &abserr);

      gsl_integration_workspace_free(w);

      return result;
    }

    // auxiliary function for gsl minimization returning the log-likelihood for a given X-ray experiment
    double XrayLogLikelihood(double E, void *p)
    {
      XrayLikelihood_params *params = static_cast<XrayLikelihood_params*>(p);
      Xray experiment = params->experiment;

      double data = experiment.fluxIntegrated(E);
      double sigma = experiment.sigmaIntegrated(E);
      double prediction = XrayPredictionIntegrated(E, params);

      return (prediction>=data) ? -pow(data-prediction,2.)/(2.*sigma*sigma) : 0.;
    }

    // computes the energy E which minimizes the log-likelihood
    double minimizeLogLikelihood(XrayLikelihood_params *params)
    {
      int status;
      int iter = 0, max_iter = 100;
      const gsl_min_fminimizer_type *T;
      gsl_min_fminimizer *s;
      Xray experiment = params->experiment;
      double mass = params->mass;
      double Emin = experiment.getEmin(), Emax = experiment.getEmax();
      double a = Emin+experiment.deltaE(Emin), b = fmin(mass/2., Emax-experiment.deltaE(Emax));
      double m = (a+b)/2.;
      gsl_function F;

      F.function = &XrayLogLikelihood;
      F.params = params;
      T = gsl_min_fminimizer_brent;
      s = gsl_min_fminimizer_alloc(T);
      gsl_min_fminimizer_set (s, &F, m, a, b);

      do
      {
        iter++;
        status = gsl_min_fminimizer_iterate (s);

        m = gsl_min_fminimizer_x_minimum (s);
        a = gsl_min_fminimizer_x_lower (s);
        b = gsl_min_fminimizer_x_upper (s);

        status = gsl_min_test_interval (a, b, 0.1, 0);
      } while (status == GSL_CONTINUE && iter < max_iter);

      gsl_min_fminimizer_free (s);

      return m;
    }

    // Linear interpolation in lin-log space.
    double interpolate(double x, const std::vector<double> & xlist,
            const std::vector<double> & ylist, bool zerobound)
    {
        double x0, x1, y0, y1;
        int i = 1;
        if (zerobound)
        {
            if (x<xlist.front()) return 0;
            if (x>xlist.back()) return 0;
        }
        else
        {
            if (x<xlist.front()) return ylist.front();
            if (x>xlist.back()) return ylist.back();
        }
        // Find min i such that xlist[i]>=x.
        for (; xlist[i] < x; i++) {};
        x0 = xlist[i-1];
        x1 = xlist[i];
        y0 = ylist[i-1];
        y1 = ylist[i];
        // lin-vs-log interpolation for lnL vs flux
        return y0 + (y1-y0) * log(x/x0) / log(x1/x0);
    }

    void get_J_factor_INTEGRAL_CO (double &result)
    {
      using namespace Pipes::get_J_factor_INTEGRAL_CO;

      GalacticHaloProperties halo = *Dep::GalacticHalo;

      daFunk::Funk profile = halo.DensityProfile;

      std::vector<double> rho;
      auto r = daFunk::logspace(-3, 2, 100);
      double r_sun = halo.r_sun;

      for ( size_t i = 0; i<r.size(); i++ )
      {
        rho.push_back(profile->bind("r")->eval(r[i]));
      }

      std::vector<double> phi_pre;
      std::vector<double> intensity;

      BEreq::los_integral(byVal(r), byVal(rho), byVal(r_sun), phi_pre, intensity);

      auto emission = std::pair< std::vector<double>, std::vector<double> > (phi_pre, intensity);

      ASCIItableReader ROI = ASCIItableReader(GAMBIT_DIR "/DarkBit/data/INTEGRAL/ROI_CO.txt");
      ROI.setcolnames({"phi", "weight"});
      std::vector<double> phi = ROI["phi"], weight = ROI["weight"];

      double J = 0;
      for ( size_t i = 0; i < phi.size(); i++ )
      {
        J += interpolate(phi[i], emission.first, emission.second, true)*weight[i]*3.0856775814913684e21;// J in Gev/cm^2
      }

      result = J;
    }

    // gsl error handler
    void handler (const char * reason, const char * file, int line, int gsl_errno)
    {
      if (gsl_errno == 4)
      {
        throw gsl_errno;
      }
      else { std::cerr << "gsl: " << file << ":" << line << ": ERROR: " << reason << std::endl; abort(); }
    }

    // capability function to compute the X-ray log-likelihood from the INTEGRAL experiment
    void calc_lnL_INTEGRAL_CO(double &result)
    {
      using namespace Pipes::calc_lnL_INTEGRAL_CO;

      double tau = *Param["lifetime"];

      double gamma_ph = 1/tau * *Param["BR_ph"];

      double mass = *Param["mass"]*1e9; // mass in eV

      double fraction = *Param["fraction"];

      double t0 = *Dep::age_universe;

      double J_factor = *Dep::J_factor_INTEGRAL_CO*1e9; //J in eV/cm^2

      static Xray experiment = Xray("INTEGRAL", J_factor);

      XrayLikelihood_params params = {mass, tau, gamma_ph, fraction, experiment, 0., daFunk::zero("z"), daFunk::zero("z"), t0};

      double Emin = experiment.getEmin(), Emax = experiment.getEmax(), E, lik1, lik2;

      // no constraints available above the electron threshold, we need to take into account the decay into charged particles
      if (mass >= 1e6) { result = 0; }

      else if (mass > 2.*Emin)
      {
        // modifies the gsl error handler and stores the default one
        gsl_error_handler_t *old_handler = gsl_set_error_handler (&handler);
        try
        {
          E = minimizeLogLikelihood(&params);
          result = XrayLogLikelihood(E, &params);
        }

        catch (int gsl_errno)
        {
          lik1 = XrayLogLikelihood(Emin+experiment.deltaE(Emin), &params);
          lik2 = XrayLogLikelihood(fmin(mass/2., Emax-experiment.deltaE(Emax)), &params);
          result = fmin(lik1, lik2);
        }
        // restores the default gsl error handler
        gsl_set_error_handler (old_handler);
      }

      else { result = 0; }
    }

    // function returning the decay photon flux in [photons/cm²/s] (assuming DM decays into a monochromatic line)
    // only used for the INTEGRAL_ang_b/l likelihoods
    double DecayFluxG (double gamma_ph, double fraction, double mass, double tau, double t0, double J_factor)
    {
      return 2.*(gamma_ph*fraction*exp(-t0/tau))/(4.*pi*mass)*J_factor;
    }

    void get_J_factor_INTEGRAL_ang_b (std::vector<double> &result)
    {
      using namespace Pipes::get_J_factor_INTEGRAL_ang_b;

      GalacticHaloProperties halo = *Dep::GalacticHalo;

      daFunk::Funk profile = halo.DensityProfile;

      std::vector<double> rho;
      auto r = daFunk::logspace(-3, 2, 100);
      double r_sun = halo.r_sun;

      for ( size_t i = 0; i<r.size(); i++ )
      {
        rho.push_back(profile->bind("r")->eval(r[i]));
      }

      std::vector<double> phi_pre;
      std::vector<double> intensity;

      BEreq::los_integral(byVal(r), byVal(rho), byVal(r_sun), phi_pre, intensity);

      auto emission = std::pair< std::vector<double>, std::vector<double> > (phi_pre, intensity);

      ASCIItableReader ROI_1 = ASCIItableReader(GAMBIT_DIR "/DarkBit/data/INTEGRAL/ROI_ang_b_1.txt");
      ASCIItableReader ROI_2 = ASCIItableReader(GAMBIT_DIR "/DarkBit/data/INTEGRAL/ROI_ang_b_2.txt");

      ROI_1.setcolnames({"phi", "weight"});
      ROI_2.setcolnames({"phi", "weight"});

      std::vector<double> phi_1 = ROI_1["phi"], weight_1 = ROI_1["weight"];
      std::vector<double> phi_2 = ROI_2["phi"], weight_2 = ROI_2["weight"];

      double J_1 = 0, J_2 = 0;

      for ( size_t i = 0; i < phi_1.size(); i++ )
      {
        J_1 += interpolate(phi_1[i], emission.first, emission.second, true)*weight_1[i]*3.0856775814913684e21; // J in Gev/cm^2
      }

      for ( size_t i = 0; i < phi_2.size(); i++ )
      {
        J_2 += interpolate(phi_2[i], emission.first, emission.second, true)*weight_2[i]*3.0856775814913684e21; // J in Gev/cm^2
      }

      result = {J_1, J_2};
    }

    void calc_lnL_INTEGRAL_ang_b (double &result)
    {
      using namespace Pipes::calc_lnL_INTEGRAL_ang_b;

      double tau = *Param["lifetime"];

      double gamma_ph = 1/tau * *Param["BR_ph"];

      double mass = *Param["mass"]; // mass in GeV

      double mass_keV = mass*1e6; // mass in keV

      double fraction = *Param["fraction"];

      double t0 = *Dep::age_universe; // Age of the Universe in seconds

      std::vector<double> J_factor = *Dep::J_factor_INTEGRAL_ang_b;

      double FluxG = DecayFluxG(gamma_ph, fraction, mass, tau, t0, J_factor[0]);

      static ASCIItableReader INTEGRAL = ASCIItableReader(GAMBIT_DIR "/DarkBit/data/INTEGRAL/INTEGRAL_b.dat");

      INTEGRAL.setcolnames({"Emin", "Emax", "Flux", "Sigma"});

      static std::vector<double> Emin = INTEGRAL["Emin"], Emax = INTEGRAL["Emax"], Flux = INTEGRAL["Flux"], Sigma = INTEGRAL["Sigma"];

      std::vector<double> Omega = {1.6119, 4.1858};

      // no constraints available above the electron threshold, we need to take into account the decay into charged particles
      if (mass_keV >= 1e3) { result = 0; }

      else if (mass_keV < 2.**std::min_element(Emin.begin(), Emin.end())) { result = 0; }

      else
      {
        double loglik = 0.;

        double PredictedFlux, ObservedFlux, Error;

        for (size_t i = 0; i < Emin.size()-1; ++i)
        {
          PredictedFlux = ( (mass_keV >= 2*Emin[i]) && (mass_keV < 2*Emax[i]) ) ? FluxG/Omega[0] : 0;
          ObservedFlux = Flux[i];
          Error = Sigma[i];
          loglik += (PredictedFlux < ObservedFlux) ? 0 : -pow(ObservedFlux - PredictedFlux, 2)/(2.*pow(Error, 2));
        }

        result = loglik;
      }
    }

    void get_J_factor_INTEGRAL_ang_l (std::vector<double> &result)
    {
      using namespace Pipes::get_J_factor_INTEGRAL_ang_l;

      GalacticHaloProperties halo = *Dep::GalacticHalo;

      daFunk::Funk profile = halo.DensityProfile;

      std::vector<double> rho;
      auto r = daFunk::logspace(-3, 2, 100);
      double r_sun = halo.r_sun;

      for ( size_t i = 0; i<r.size(); i++ )
      {
        rho.push_back(profile->bind("r")->eval(r[i]));
      }

      std::vector<double> phi_pre;
      std::vector<double> intensity;

      BEreq::los_integral(byVal(r), byVal(rho), byVal(r_sun), phi_pre, intensity);

      auto emission = std::pair< std::vector<double>, std::vector<double> > (phi_pre, intensity);

      ASCIItableReader ROI_1 = ASCIItableReader(GAMBIT_DIR "/DarkBit/data/INTEGRAL/ROI_ang_l_1.txt");
      ASCIItableReader ROI_2 = ASCIItableReader(GAMBIT_DIR "/DarkBit/data/INTEGRAL/ROI_ang_l_2.txt");

      ROI_1.setcolnames({"phi", "weight"});
      ROI_2.setcolnames({"phi", "weight"});

      std::vector<double> phi_1 = ROI_1["phi"], weight_1 = ROI_1["weight"];
      std::vector<double> phi_2 = ROI_2["phi"], weight_2 = ROI_2["weight"];

      double J_1 = 0, J_2 = 0;

      for ( size_t i = 0; i < phi_1.size(); i++ )
      {
        J_1 += interpolate(phi_1[i], emission.first, emission.second, true)*weight_1[i]*3.0856775814913684e21; // J in Gev/cm^2
      }

      for ( size_t i = 0; i < phi_2.size(); i++ )
      {
        J_2 += interpolate(phi_2[i], emission.first, emission.second, true)*weight_2[i]*3.0856775814913684e21; // J in Gev/cm^2
      }

      result = {J_1, J_2};
    }

    void calc_lnL_INTEGRAL_ang_l (double &result)
    {
      using namespace Pipes::calc_lnL_INTEGRAL_ang_l;

      double tau = *Param["lifetime"];

      double gamma_ph = 1/tau * *Param["BR_ph"];

      double mass = *Param["mass"]; // mass in GeV

      double mass_keV = mass*1e6; // mass in keV

      double fraction = *Param["fraction"];

      double t0 = *Dep::age_universe; // Age of the Universe in seconds

      std::vector<double> J_factor = *Dep::J_factor_INTEGRAL_ang_l;

      double FluxG = DecayFluxG(gamma_ph, fraction, mass, tau, t0, J_factor[0]);

      static ASCIItableReader INTEGRAL = ASCIItableReader(GAMBIT_DIR "/DarkBit/data/INTEGRAL/INTEGRAL_l.dat");

      INTEGRAL.setcolnames({"Emin", "Emax", "Flux", "Sigma"});

      static std::vector<double> Emin = INTEGRAL["Emin"], Emax = INTEGRAL["Emax"], Flux = INTEGRAL["Flux"], Sigma = INTEGRAL["Sigma"];

      std::vector<double> Omega = {1.4224, 1.7919};

      // no constraints available above the electron threshold, we need to take into account the decay into charged particles
      if (mass_keV >= 1e3) { result = 0; }

      else if (mass_keV < 2.**std::min_element(Emin.begin(), Emin.end())) { result = 0; }

      else
      {
        double loglik = 0.;

        double PredictedFlux, ObservedFlux, Error;

        for (size_t i = 0; i < Emin.size()-1; ++i)
        {
          PredictedFlux = ( (mass_keV >= 2*Emin[i]) && (mass_keV < 2*Emax[i]) ) ? FluxG/Omega[0] : 0;
          ObservedFlux = Flux[i];
          Error = Sigma[i];
          loglik += (PredictedFlux < ObservedFlux) ? 0 : -pow(ObservedFlux - PredictedFlux, 2)/(2.*pow(Error, 2));
        }

        result = loglik;
      }
    }

    // for some reason this is not giving the correct value of J, need to fix it!
    void get_J_factor_HEAO (double &result)
    {
      using namespace Pipes::get_J_factor_HEAO;

      GalacticHaloProperties halo = *Dep::GalacticHalo;

      daFunk::Funk profile = halo.DensityProfile;

      std::vector<double> rho;
      auto r = daFunk::logspace(-3, 2, 100);
      double r_sun = halo.r_sun;

      for ( size_t i = 0; i<r.size(); i++ )
      {
        rho.push_back(profile->bind("r")->eval(r[i]));
        // rho.push_back(pow(profile->bind("r")->eval(r[i]), 2));
      }

      std::vector<double> phi_pre;
      std::vector<double> intensity;

      BEreq::los_integral(byVal(r), byVal(rho), byVal(r_sun), phi_pre, intensity);

      auto emission = std::pair< std::vector<double>, std::vector<double> > (phi_pre, intensity);

      ASCIItableReader ROI = ASCIItableReader(GAMBIT_DIR "/DarkBit/data/HEAO/ROI.txt");
      ROI.setcolnames({"phi", "weight"});
      std::vector<double> phi = ROI["phi"], weight = ROI["weight"];

      double J = 0;
      for ( size_t i = 0; i < phi.size(); i++ )
      {
        J += interpolate(phi[i], emission.first, emission.second, true)*weight[i]*3.0856775814913684e21;// J in Gev/cm^2
      }

      result = J;

      // std::cout << "J = " << result/r_sun/rho_sun << std::endl;
    }

    void calc_lnL_HEAO(double &result)
    {
      using namespace Pipes::calc_lnL_HEAO;

      double OmegaDM = *Dep::Omega0_cdm;
      
      daFunk::Funk H_z = *Dep::H_at_z;
      daFunk::Funk t_z = *Dep::time_at_z;

      double tau = *Param["lifetime"];

      double gamma_ph = 1/tau * *Param["BR_ph"];

      double mass = *Param["mass"]*1e9; // mass in eV

      double fraction = *Param["fraction"];

      double t0 = *Dep::age_universe;

      static Xray experiment = Xray("HEAO", 9.894*1e9*3.0856775814913684e21); // J in ev / cm^2

      XrayLikelihood_params params = {mass, tau, gamma_ph, fraction, experiment, OmegaDM, H_z, t_z, t0};

      const double Emin = experiment.getEmin(), Emax = experiment.getEmax();
      double E, lik1, lik2;

      // no constraints available above the electron threshold, we need to take into account the decay into charged particles
      if (mass >= 1e6) { result = 0; }

      else if (mass > 2.*Emin)
      {
        // modifies the gsl error handler and stores the default one
        gsl_error_handler_t *old_handler = gsl_set_error_handler (&handler);
        try
        {
          E = minimizeLogLikelihood(&params);
          result = XrayLogLikelihood(E, &params);
        }

        catch (int gsl_errno)
        {
          lik1 = XrayLogLikelihood(Emin+experiment.deltaE(Emin), &params);
          lik2 = XrayLogLikelihood(fmin(mass/2., Emax-experiment.deltaE(Emax)), &params);
          result = fmin(lik1, lik2);
        }
        // restores the default gsl error handler
        gsl_set_error_handler (old_handler);
      }

      else { result = 0; }
    }
  }
}
*/
