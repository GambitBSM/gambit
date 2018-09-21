//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend for MicrOmegas MajoranaDM 3.6.9.2 backend
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
/// \author Ankit Beniwal
/// \date Jun, Aug, Sep 2017
/// \date Aug 2018
///
///  *********************************************

#include "gambit/Backends/frontend_macros.hpp"
#include "gambit/Backends/frontends/MicrOmegas_MajoranaDM_3_6_9_2.hpp"
#include <unistd.h>

// Convenience functions (definitions)
BE_NAMESPACE
{
    double dNdE(double Ecm, double E, int inP, int outN)
    {
      // outN 0-5: gamma, e+, p-, nu_e, nu_mu, nu_tau
      // inP:  0 - 6: glu, d, u, s, c, b, t
      //       7 - 9: e, m, l
      //       10 - 15: Z, ZT, ZL, W, WT, WL
      double tab[250];  // NZ = 250
      // readSpectra() moved to initialization function.
      // Must be inside critical block if used here!
      // readSpectra();
      mInterp(Ecm/2, inP, outN, tab);
      return zInterp(log(E/Ecm*2), tab);
    }
}
END_BE_NAMESPACE

// Initialisation function (definition)
BE_INI_FUNCTION
{
     int error;
     char cdmName[10];

     const Spectrum& spec = *Dep::MajoranaDM_spectrum;
     const SubSpectrum& he = spec.get_HE();
     const SubSpectrum& le = spec.get_LE();
     const SMInputs& sminputs = spec.get_SMInputs();

     int VZdecayOpt, VWdecayOpt; // 0=no 3 body final states
                                 // 1=3 body final states in annihlations
                                 // 2=3 body final states in co-annihilations
     VZdecayOpt = runOptions->getValueOrDef<int>(1, "VZdecay");
     VWdecayOpt = runOptions->getValueOrDef<int>(1, "VWdecay");
     *VZdecay = VZdecayOpt;
     *VWdecay = VWdecayOpt;

     logger() << LogTags::debug << "Initializing MicrOmegas MajoranaDM with ";
     logger() << "VWdecay: " << VWdecay << " VZdecay: " << VZdecay << EOM;

     // Uncomment below to force MicrOmegas to do calculations in unitary gauge
     *ForceUG=1;

     double mX = spec.get(Par::Pole_Mass,"X");
     double mH = spec.get(Par::Pole_Mass,"h0_1");
     double mW = le.get(Par::Pole_Mass, "W+");
     double lX = he.get(Par::dimensionless,"lX");
     double cxi = std::cos(he.get(Par::dimensionless,"xi"));

     error = assignVal((char*)"mX", mX);
     if (error != 0) backend_error().raise(LOCAL_INFO, "Unable to set mX in"
             "MicrOmegas. MicrOmegas error code: " + std::to_string(error));

     error = assignVal((char*)"lX", lX);
     if (error != 0) backend_error().raise(LOCAL_INFO, "Unable to set lX in"
             "MicrOmegas. MicrOmegas error code: " + std::to_string(error));

     error = assignVal((char*)"cosXI", cxi);
     if (error != 0) backend_error().raise(LOCAL_INFO, "Unable to set cxi in"
             "MicrOmegas. MicrOmegas error code: " + std::to_string(error));

     // Set SM particle masses in micrOmegas_3.6.9.2

     // EE = sqrt(4*pi*(1/alphainv))
     error = assignVal((char*)"EE", sqrt(4*M_PI*(1/sminputs.alphainv)));
     if (error != 0) backend_error().raise(LOCAL_INFO, "Unable to set alphainv in"
             " MicrOmegas. MicrOmegas error code: " + std::to_string(error));

     // v0 = 1/sqrt(sqrt(2)*GF)
     error = assignVal((char*)"v0", 1/sqrt(sqrt(2)*sminputs.GF));
     if (error != 0) backend_error().raise(LOCAL_INFO, "Unable to set GF in"
             " MicrOmegas. MicrOmegas error code: " + std::to_string(error));

     // mu(2 GeV) in MSbar scheme
     error = assignVal((char*)"Mu", sminputs.mU);
     if (error != 0) backend_error().raise(LOCAL_INFO, "Unable to set mU in"
             " MicrOmegas. MicrOmegas error code: " + std::to_string(error));

     // md(2 GeV) in MSbar scheme
     error = assignVal((char*)"Md", sminputs.mD);
     if (error != 0) backend_error().raise(LOCAL_INFO, "Unable to set mD in"
             " MicrOmegas. MicrOmegas error code: " + std::to_string(error));

     // ms(2 GeV) in MSbar scheme
     error = assignVal((char*)"Ms", sminputs.mS);
     if (error != 0) backend_error().raise(LOCAL_INFO, "Unable to set mS in"
             " MicrOmegas. MicrOmegas error code: " + std::to_string(error));

     // mc(mc) in MSbar scheme
     error = assignVal((char*)"Mc", sminputs.mCmC);
     if (error != 0) backend_error().raise(LOCAL_INFO, "Unable to set mCmC in"
             " MicrOmegas. MicrOmegas error code: " + std::to_string(error));

     // mb(mb) in MSbar scheme
     error = assignVal((char*)"Mb", sminputs.mBmB);
     if (error != 0) backend_error().raise(LOCAL_INFO, "Unable to set mBmB in"
             " MicrOmegas. MicrOmegas error code: " + std::to_string(error));

     // mtop(pole)
     error = assignVal((char*)"Mtop", sminputs.mT);
     if (error != 0) backend_error().raise(LOCAL_INFO, "Unable to set mT in"
             " MicrOmegas. MicrOmegas error code: " + std::to_string(error));

     // mE(pole)
     error = assignVal((char*)"Me", sminputs.mE);
     if (error != 0) backend_error().raise(LOCAL_INFO, "Unable to set mE in"
             " MicrOmegas. MicrOmegas error code: " + std::to_string(error));

     // mMu(pole)
     error = assignVal((char*)"Mm", sminputs.mMu);
     if (error != 0) backend_error().raise(LOCAL_INFO, "Unable to set mMu in"
             " MicrOmegas. MicrOmegas error code: " + std::to_string(error));

     // mTau(pole)
     error = assignVal((char*)"Mtau", sminputs.mTau);
     if (error != 0) backend_error().raise(LOCAL_INFO, "Unable to set mTau in"
             " MicrOmegas. MicrOmegas error code: " + std::to_string(error));

     // mZ(pole)
     error = assignVal((char*)"MZ", sminputs.mZ);
     if (error != 0) backend_error().raise(LOCAL_INFO, "Unable to set mZ in"
             " MicrOmegas. MicrOmegas error code: " + std::to_string(error));

     // Set Higgs boson mass in micrOmegas_3.6.9.2
     error = assignVal((char*)"MH", mH);
     if (error != 0) backend_error().raise(LOCAL_INFO, "Unable to set mH in"
             " MicrOmegas. MicrOmegas error code: " + std::to_string(error));

     // Set sin(theta_W) in micrOmegas_3.6.9.2
     error = assignVal((char*)"SW", sqrt(1-mW/(sminputs.mZ)*mW/(sminputs.mZ)));
     if (error != 0) backend_error().raise(LOCAL_INFO, "Unable to set sin(theta_W) in"
             " MicrOmegas. MicrOmegas error code: " + std::to_string(error));

     // Set particle widths in micrOmegas_3.6.9.2 (Higgs width is automatically calculated)
     const DecayTable* tbl = &(*Dep::decay_rates);
     double width = 0.0;
     bool present = true;

     present = true;
     try {width = tbl->at("Z0").width_in_GeV;}
     catch (std::exception& e) {present = false;}
     if (present)
     {
         error = assignVal((char*)"wZ", width);
         if (error != 0) backend_error().raise(LOCAL_INFO, "Unable to set Z width in"
                 " MicrOmegas. MicrOmegas error code: " + std::to_string(error));
     }

     present = true;
     try {width = tbl->at("W+").width_in_GeV;}
     catch (std::exception& e) {present = false;}
     if (present)
     {
         error = assignVal((char*)"wW", width);
         if (error != 0) backend_error().raise(LOCAL_INFO, "Unable to set W width in"
                 " MicrOmegas. MicrOmegas error code: " + std::to_string(error));
     }

     present = true;
     try {width = tbl->at("t").width_in_GeV;}
     catch (std::exception& e) {present = false;}
     if (present)
     {
         error = assignVal((char*)"wtop", width);
         if (error != 0) backend_error().raise(LOCAL_INFO, "Unable to set top width in"
                 " MicrOmegas. MicrOmegas error code: " + std::to_string(error));
     }

     // Initialise micrOMEGAs mass spectrum
     error = sortOddParticles(byVal(cdmName));
     if (error != 0) backend_error().raise(LOCAL_INFO, "MicrOmegas function "
             "sortOddParticles returned error code: " + std::to_string(error));

}
END_BE_INI_FUNCTION
