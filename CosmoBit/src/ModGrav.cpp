//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  CosmoBit routines relating to modified gravity models.
///  Currently includes solar system tests.
///
///  *********************************************
///  Authors (add name and date if you modify):
///  \author Anna Liang
///          (a.liang1@uqconnect.edu.au)
///  \date 2021 Aug
///  *********************************************

#include <string>
#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>

#include "gambit/Utils/yaml_options.hpp"
#include "gambit/Utils/ascii_dict_reader.hpp"
#include "gambit/Utils/ascii_table_reader.hpp"
#include "gambit/Utils/numerical_constants.hpp"
#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/CosmoBit/CosmoBit_rollcall.hpp"
#include "gambit/CosmoBit/CosmoBit_types.hpp"
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>

namespace Gambit
{

  namespace CosmoBit
  {
    // constants
    const double G = 6.708609142443796e-39; /* Gn*pow(m_to_GeV,3.)*pow(g_to_GeV,-1.)*pow(s_to_GeV,-2.) Newton constant in GeV^-2 */
    const double M_pl = Gambit::m_planck_red; // m_planck/sqrt(8.0*pi); reduced Planck mass (GeV)

    using namespace LogTags;

    const double G_cgs = 6.674e-8; // Gravitational constant [cm³/g/s²]

    // Obtain the grid of phi(0) for a given M and mu by interpolating pre-calculated values
    // from the data file CosmoBit/data/phiOvals.dat
    void interp_phi0 (double &result)
    {
      using namespace Pipes::interp_phi0;
      using namespace std;

      // Read in the data file on the first time the function calls
      static bool firsttime = true;
      static double minmass, maxmass, minmu, maxmu; // bounds on mass and mu
      static int nmasses, nmu; // grid sizes of mass and mu
      static vector <double> phi0vec; // vector to store phi0 vals
      static vector <double> massvec, muvec; // vector to store the mass and mu points of grid

      if (firsttime == true){
        // Create a file stream for file to open the .dat file of phi0 values
        ifstream datafile;
        str filename = runOptions->getValueOrDef<str>(GAMBIT_DIR "/CosmoBit/data/ModGrav/phi0vals.dat", "filepath");
        datafile.open(filename);
        if(!datafile.is_open()){
          CosmoBit_error().raise(LOCAL_INFO, "Failed to open file phi0vals.dat in specified directory.");
        }
        // Obtain the first line of data file as a string stream and convert to store parameters as double values
        str line1;
        getline(datafile, line1);
        istringstream iss(line1);

        vector <double> vecinputs (6, 0.0e0);
        for (int i=0; i<6; i++){
          iss >> vecinputs.at(i);
        }

        // Store the read in parameters as static variables
        minmass = vecinputs.at(0);
        maxmass = vecinputs.at(1);
        nmasses = vecinputs.at(2);
        minmu = vecinputs.at(3);
        maxmu = vecinputs.at(4);
        nmu = vecinputs.at(5);

        // Then read in the rest of the file as a vector
        double num = 0; // to check file reading against
        while (datafile >> num) {
          phi0vec.push_back(num);
        }

        // Generate a vector of masses in GeV
        double steplogmass = (log10(maxmass/M_pl)-log10(minmass/M_pl))/(nmasses-1);
        massvec.resize(nmasses, 0.0e0);
        for (int i=0; i<nmasses; i++){
          massvec.at(i) = pow(10, log10(maxmass/M_pl)-i*steplogmass)*M_pl;
        }

        // Generate a vector of mu vals in GeV
        double steplogmu = (log10(maxmu)-log10(minmu))/(nmu-1);
        muvec.resize(nmu, 0.0e0);
        for (int i=0; i<nmu; i++){
          muvec.at(i) = pow(10, log10(maxmu)-i*steplogmu);
        }

        datafile.close();
        firsttime = false;
      }

      // Interpolate the table to obtain desired phi(0) for a given M and mu
      double inputmass, inputmu;
      if (ModelInUse("symmetron")) {
        double powmass, powmu;
        powmass = *Param["mass"];
        inputmass = pow(10, powmass)*M_pl;
        powmu = *Param["mu"];
        inputmu = pow(10, powmu);
      } else
      {
         CosmoBit_error().raise(LOCAL_INFO,"Whoops, you are not scanning the model "
          " symmetron! There is probably a bug CosmoBit_rollcall.hpp; this module "
          " function should have ALLOW_MODELS(symmetron) defined.");
      }

      // Check the input mass and mu are within interpolation range
      if (inputmass > maxmass){
        CosmoBit_error().raise(LOCAL_INFO,"Input mass chosen greater than interpolating range.");
      }
      if (inputmass < minmass){
        CosmoBit_error().raise(LOCAL_INFO,"Input mass chosen smaller than interpolating range.");
      }
      if (inputmu > maxmu) {
        CosmoBit_error().raise(LOCAL_INFO,"Input mu chosen greater than interpolating range.");
      }
      if (inputmu < minmu) {
        CosmoBit_error().raise(LOCAL_INFO,"Input mu chosen smaller than interpolating range.");
      }

      // Find x0, x1, y0, y1 where x is mass and y is mu
      int ix0, ix1, jy0, jy1;
      double x0, x1, y0, y1;

      for (int i=0; i<nmasses-1; i++){
        // massvec gets smaller from first element to last
        if (inputmass <= massvec.at(i) && inputmass >= massvec.at(i+1)){
          ix0 = i+1;
          ix1 = i;
          x0 = massvec.at(ix0);
          x1 = massvec.at(ix1);
          break;
        }
      }

      for (int j=0; j<nmu-1; j++){
        // muvec gets bigger from first element to last
        if (inputmu <= muvec.at(j) && inputmu >= muvec.at(j+1)){
          jy0 = j+1;
          jy1 = j;
          y0 = muvec.at(jy0);
          y1 = muvec.at(jy1);
          break;
        }
      }

      // Find what corresponding phi(0) values are
      double z00 = phi0vec.at(jy0+ix0*nmu);
      double z01 = phi0vec.at(jy1+ix0*nmu);
      double z10 = phi0vec.at(jy0+ix1*nmu);
      double z11 = phi0vec.at(jy1+ix1*nmu);

      // Then interpolate to obtain the phi0(mass, mu) we want
      double yfrac = (inputmu - y0)/(y1-y0);
      double xfrac = (inputmass - x0)/(x1-x0);
      double interpphi0 = (1.0-yfrac)*((1.0-xfrac)*z00+xfrac*z10)+yfrac*((1.0-xfrac)*z01+xfrac*z11);

      result = interpphi0;
      // Print parameters to check function is interpolating correctly
      // cout << "Mass = " << inputmass << endl;
      // cout << "Mu = " << inputmu << endl;
      // cout << "phi(0) = " << result << endl;
    }

    // Calculate Brans-Dicke parameter omega using symmetron parameters mass and v
    void compute_omega (double &result)
    {
      using namespace Pipes::compute_omega;

      double phival = *Pipes::compute_omega::Dep::phi0_interpolation; // obtain from interpolating function
      const double M_pl = 2.453e18; // [Gev/c^2] reduced planck mass
      double omega = 0.0e0; // to store the value of omega

     if (ModelInUse("symmetron"))
      {
        // Input parameters are given as powers so convert to GeV/c^2
        double powmass = *Param["mass"];
        double mass = pow(10, powmass)*M_pl;
        double powv = *Param["vval"];
        double vval = pow(10, powv)*M_pl;

        if(Utils::isnan(mass) or Utils::isnan(vval))
        {
          CosmoBit_error().raise(LOCAL_INFO,"NaN detected in input parameters for model"
          " symmetron! This may indicate a bug in the scanner plugin you are using.");
        }
        omega = 0.5*(0.5*pow(pow(mass,2.0)/(M_pl*phival*vval), 2.0)-3);
      } else
      {
         CosmoBit_error().raise(LOCAL_INFO,"Whoops, you are not scanning the model "
          " symmetron! There is probably a bug CosmoBit_rollcall.hpp; this module "
          " function should have ALLOW_MODELS(symmetron) defined.");
      }

      // Store the result as omega
      result = omega;
    }

  // Calculate gamma using brans-dicke parameter omega
   void compute_gammaminus1 (double &result)
   {
     result = fabs(1.0/(2.0+ *Pipes::compute_gammaminus1::Dep::omega_bdparam));
     // cout << "|gamma-1| = " << result << endl;
   }

   // Calculate |beta-1| parameter using brans-dicke parameter omega
    void compute_betaminus1 (double &result)
    {
      using namespace Pipes::compute_betaminus1;

      double omega = *Pipes::compute_betaminus1::Dep::omega_bdparam;
      double phi0 = *Pipes::compute_betaminus1::Dep::phi0_interpolation;
      double mass, vval;
      const double M_pl = 2.453e18; // [Gev/c^2] reduced planck mass

      if (ModelInUse("symmetron"))
       {
         // read in input parameters
         double powmass = *Param["mass"];
         mass = pow(10, powmass)*M_pl;
         double powv = *Param["vval"];
         vval = pow(10, powv)*M_pl;

         if(Utils::isnan(mass))
         {
           CosmoBit_error().raise(LOCAL_INFO,"NaN detected in input parameters for model"
           " symmetron! This may indicate a bug in the scanner plugin you are using.");
         }
       } else
       {
          CosmoBit_error().raise(LOCAL_INFO,"Whoops, you are not scanning the model "
           " symmetron! There is probably a bug CosmoBit_rollcall.hpp; this module "
           " function should have ALLOW_MODELS(symmetron) defined.");
       }

      double deriv = -2*pow(1+phi0*phi0*vval*vval/(2*mass*mass),-3.0)*2*phi0*vval/(2*mass*mass);
      result = fabs(1/(pow(3+2*omega,2.0)*(4+2*omega))*1.0/deriv);
      // cout << "|beta-1| = " << result << endl;
    }

    // A likelihood function for comparing the model eta to the mars perihelion value
    void lnL_eta (double &result)
    {
      using namespace Pipes::lnL_eta;

      double loglTotal = 0.;
      double betaminus1 = *Pipes::lnL_eta::Dep::betaminus1_bdparam;
      double gammaminus1 = *Pipes::lnL_eta::Dep::gammaminus1_bdparam;
      double eta_data = -0.6e-4;
      double eta_err = 5.2e-4;
      double eta_model = 4*(betaminus1+1)-(gammaminus1+1)-3;
      double chi2 = pow((eta_model-eta_data)/eta_err,2.0);
      loglTotal += -chi2/2.0;

      // Randomly raise some ficticious alarms about this point, with probability x,
      // where x is given by the input yaml option or a default of 1.
      double x = 1.0-runOptions->getValueOrDef<double>(1., "probability_of_validity");
      if (Random::draw() < x)
      {
        invalid_point().raise("I don't like this point.");
      }

      // Artificially slow down likelihood evaluations
      // Important for debugging new scanner plugins.
      double eval_time = runOptions->getValueOrDef<double>(-1, "eval_time"); // Measured in seconds
      //std::cout << "eval_time:" << eval_time <<std::endl;
      if(eval_time>0)
      {
         struct timespec sleeptime;
         sleeptime.tv_sec = floor(eval_time);
         sleeptime.tv_nsec = floor((eval_time-floor(eval_time))*1e9); // Allow user to choose fractions of second
         //std::cout << "Sleeping for "<<sleeptime.tv_sec<<" seconds and "<<sleeptime.tv_nsec<<" nanoseconds" <<std::endl;
         nanosleep(&sleeptime,NULL);
      }

      result = loglTotal;
      logger() << "Symmetron beta LogLike computed to be: " << result << EOM;
    }

    // A likelihood function for comparing the model |gamma-1| to the cassini value
    void lnL_gamma (double &result)
    {
      using namespace Pipes::lnL_gamma;

      double loglTotal = 0.;
      double gammaminus1 = *Pipes::lnL_gamma::Dep::gammaminus1_bdparam;
      double gammaminus1_data = 2.1e-5;
      double gammaminus1_err = 2.3e-5;
      double chi2 = pow((gammaminus1-gammaminus1_data)/gammaminus1_err,2.0);
      loglTotal += -chi2/2.0;

      // Check that the tolerance for phi is reasonable for the data
      double limit = runOptions->getValueOrDef<double>(1e-5, "gammaminus1_tol");
      if (0.01*gammaminus1_data < limit) {
        CosmoBit_error().raise(LOCAL_INFO, "Minimum gamma-1 limit for calculating "
        "phi(0) is too large for the given data. Recalculate phi(0) grid with a smaller limit.");
      }

      // Randomly raise some ficticious alarms about this point, with probability x,
      // where x is given by the input yaml option or a default of 1.
      double x = 1.0-runOptions->getValueOrDef<double>(1., "probability_of_validity");
      if (Random::draw() < x)
      {
        invalid_point().raise("I don't like this point.");
      }

      // Artificially slow down likelihood evaluations
      // Important for debugging new scanner plugins.
      double eval_time = runOptions->getValueOrDef<double>(-1, "eval_time"); // Measured in seconds
      //std::cout << "eval_time:" << eval_time <<std::endl;
      if(eval_time>0)
      {
         struct timespec sleeptime;
         sleeptime.tv_sec = floor(eval_time);
         sleeptime.tv_nsec = floor((eval_time-floor(eval_time))*1e9); // Allow user to choose fractions of second
         //std::cout << "Sleeping for "<<sleeptime.tv_sec<<" seconds and "<<sleeptime.tv_nsec<<" nanoseconds" <<std::endl;
         nanosleep(&sleeptime,NULL);
      }

      result = loglTotal;
      logger() << "Symmetron gamma LogLike computed to be: " << result << EOM;
    }

    // A box likelihood function for whether v is allowed by vmin
    void lnL_vmin (double &result)
    {
      using namespace Pipes::lnL_vmin;
      using namespace std;
      const double M_pl = 2.453e18; // [Gev/c^2] reduced planck mass
      double mass, vval;
      // double scale_gravstrength = runOptions->getValueOrDef<double>(1.0, "gravstrength");

      if (ModelInUse("symmetron"))
       {
         double powmass = *Param["mass"];
         mass = pow(10, powmass)*M_pl;
         double powv = *Param["vval"];
         vval = pow(10, powv)*M_pl;

         if(Utils::isnan(mass) or Utils::isnan(vval))
         {
           CosmoBit_error().raise(LOCAL_INFO,"NaN detected in input parameters for model"
           " symmetron! This may indicate a bug in the scanner plugin you are using.");
         }
       } else
       {
          CosmoBit_error().raise(LOCAL_INFO,"Whoops, you are not scanning the model "
           " symmetron! There is probably a bug CosmoBit_rollcall.hpp; this module "
           " function should have ALLOW_MODELS(symmetron) defined.");
       }

       double logl = 0.0e0;
       if (vval > mass*mass/M_pl){
         logl = 0.0;
       } else {
         logl = -1e30;
       }

       result = logl;
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
    // or the symmetron fifth force in casimir experiments from Elder et al. 2020
    void New_Force_Sushkov2011_SuperRenormHP (daFunk::Funk &result)
    {
      using namespace Pipes::New_Force_Sushkov2011_SuperRenormHP;

      if (ModelInUse("symmetron"))
      {
        const double powv = *Param["vval"], powmu = *Param["mu"];
        double vval = pow(10, powv)*Gambit::m_planck_red, mu = pow(10, powmu);

        double Rad = runOptions->getValueOrDef<double>(10, "roundplate_radius");; // sphere radius in cm
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

      static ASCIItableReader data = ASCIItableReader(GAMBIT_DIR "/CosmoBit/data/ModGrav/Sushkov2011.dat");
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

  } // namespace CosmoBit
} // namespace Gambit
