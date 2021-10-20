//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend for DarkSUSY_generic_wimp_6.2.5 backend
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Torsten Bringmann
///          (torsten.bringmann@fys.uio.no)
///  \date 2021
///
///  *********************************************

#include "gambit/Backends/frontend_macros.hpp"
#include "gambit/Backends/frontends/DarkSUSY_generic_wimp_6_2_5.hpp"
#include "gambit/Utils/file_lock.hpp"
#include "gambit/Utils/mpiwrapper.hpp"

//#define DARKSUSY_DEBUG

// Some ad-hoc DarkSUSY global state.
BE_NAMESPACE
{
  std::vector<double> DSanbr; // to have BR available to neutrino_yield
  double anmwimp; // to have WIMP mass available to neutrino_yield
  std::vector<int> DSanpdg1;
  std::vector<int> DSanpdg2;
}
END_BE_NAMESPACE

// Initialisation function (definition)
BE_INI_FUNCTION
{
  // Initialize DarkSUSY (only) if run for the first time
  bool static scan_level = true;

  if (scan_level)
  {
    // Do the call to dsinit one-by-one for each MPI process, as DarkSUSY loads up
    // HiggsBounds, which writes files at init then reads them back in later.
    Utils::ProcessLock mylock("DarkSUSY_" STRINGIFY(SAFE_VERSION) "_init");
    mylock.get_lock();
    dsinit();
    mylock.release_lock();

    //// Initialize yield tables for use in cascade decays (initialize more if needed)
    // This makes sure that different processes later don't read the yield tables
    // from disk simultaneously
    int istat=0;
    double mdm=100.0, egev=10.0;
    int pdg=5, yieldpdg, diff=1;
    char*hel =  (char *)"0";

    yieldpdg = 22;// gamma rays
    dsanyield_sim(mdm,egev,pdg,hel,yieldpdg,diff,istat);
    yieldpdg = -2212; //antiprotons
    dsanyield_sim(mdm,egev,pdg,hel,yieldpdg,diff,istat);
    yieldpdg = -11; //positrons
    dsanyield_sim(mdm,egev,pdg,hel,yieldpdg,diff,istat);
    yieldpdg = -1000010020; //anti-deuteron
    dsanyield_sim(mdm,egev,pdg,hel,yieldpdg,diff,istat);

    scan_level = false;
  }

  // Unlike in the MSSM case, we don't actually initialize a generic WIMP
  // model "point" here. We thus just use basic, "model-independent"
  // DarkSUSY functinalities.
}
END_BE_INI_FUNCTION


// Convenience functions (definitions)
BE_NAMESPACE
{
  /// Sets DarkSUSY's internal common blocks with some of the properties required to compute neutrino
  /// yields for a generic WIMP. Remaining internal variables are internal to this frontend.
  void dsgenericwimp_nusetup(const double (&annihilation_bf)[29], const double (&)[29][3],
   const double (&)[15], const double (&)[3], const double &,
   const double &mwimp)
  {
    // Transfer WIMP mass common block.
    anmwimp = mwimp;

    // The below give the PDG codes for the final states each element of the
    // annihilation_bf array is associated with. Non-SM final states are given
    // PDG code 20000.
    DSanpdg1.clear();
    DSanpdg2.clear();
    DSanpdg1.push_back(10000);  // not used, as we keep the same numbering as for Fortran
    DSanpdg2.push_back(10000);
    DSanpdg1.push_back(20000);  // H H, channel 1
    DSanpdg2.push_back(20000);
    DSanpdg1.push_back(25);     // h H, channel 2
    DSanpdg2.push_back(20000);
    DSanpdg1.push_back(25);     // h h, channel 3
    DSanpdg2.push_back(25);
    DSanpdg1.push_back(20000);  // A A, channel 4
    DSanpdg2.push_back(20000);
    DSanpdg1.push_back(20000);  // H A, channel 5
    DSanpdg2.push_back(20000);
    DSanpdg1.push_back(25);     // h A, channel 6
    DSanpdg2.push_back(20000);
    DSanpdg1.push_back(20000);  // H+ H-, channel 7
    DSanpdg2.push_back(20000);
    DSanpdg1.push_back(20000);  // Z H, channel 8
    DSanpdg2.push_back(20000);
    DSanpdg1.push_back(20000);  // Z h, channel 9
    DSanpdg2.push_back(25);
    DSanpdg1.push_back(23);     // Z A, channel 10
    DSanpdg2.push_back(20000);
    DSanpdg1.push_back(24);     // W+ H-, channel 11
    DSanpdg2.push_back(20000);
    DSanpdg1.push_back(23);     // Z Z, channel 12
    DSanpdg2.push_back(23);
    DSanpdg1.push_back(24);     // W+ W-, channel 13
    DSanpdg2.push_back(-24);
    DSanpdg1.push_back(12);     // nue nuebar, channel 14
    DSanpdg2.push_back(-12);
    DSanpdg1.push_back(11);     // e- e+, channel 15
    DSanpdg2.push_back(-11);
    DSanpdg1.push_back(14);     // numu numubar, channel 16
    DSanpdg2.push_back(-14);
    DSanpdg1.push_back(13);     // mu- mu+, channel 17
    DSanpdg2.push_back(-13);
    DSanpdg1.push_back(16);     // nutau nutaubar, channel 18
    DSanpdg2.push_back(-16);
    DSanpdg1.push_back(15);     // tau- tau+, channel 19
    DSanpdg2.push_back(-15);
    DSanpdg1.push_back(2);      // u ubar, channel 20
    DSanpdg2.push_back(-2);
    DSanpdg1.push_back(1);      // d dbar, channel 21
    DSanpdg2.push_back(-1);
    DSanpdg1.push_back(4);      // c cbar, channel 22
    DSanpdg2.push_back(-4);
    DSanpdg1.push_back(3);      // s sbar, channel 23
    DSanpdg2.push_back(-3);
    DSanpdg1.push_back(6);      // t tbar, channel 24
    DSanpdg2.push_back(-6);
    DSanpdg1.push_back(5);      // b bbar, channel 25
    DSanpdg2.push_back(-5);
    DSanpdg1.push_back(21);     // gluon gluon, channel 26
    DSanpdg2.push_back(21);
    DSanpdg1.push_back(10000);  // (not used)
    DSanpdg2.push_back(10000);
    DSanpdg1.push_back(22);     // gamma gamma, channel 28
    DSanpdg2.push_back(22);
    DSanpdg1.push_back(22);     // gamma Z, channel 29
    DSanpdg2.push_back(23);

    // Transfer branching fractions to WIMP annihilation common blocks.
    // For channel indices, see dswayieldone.f
    DSanbr.clear();
    DSanbr.push_back(0.0);

    for (int i=1; i<=29; i++)
    {
      if (DSanpdg1[i] == 10000 || DSanpdg2[i] == 10000)
        DSanbr.push_back(0.);
      else if (DSanpdg1[i] == 20000 || DSanpdg2[i] == 20000)
      {
        if (annihilation_bf[i-1] > 0.00001)
          backend_error().raise(LOCAL_INFO, "ERROR: The DarkSUSY neutrino telescope routines "
                          "for a generic WIMP cannot handle models with non-standard model\n"
                          "WIMP annihilation final states.");
        else
          DSanbr.push_back(0.);
      } // if
      else
        DSanbr.push_back(annihilation_bf[i-1]);
    } // for
  } // dsgenericwimp_nusetup

  /// Returns neutrino yields at the top of the atmosphere,
  /// in m^-2 GeV^-1 annihilation^-1.  Provided here for
  /// interfacing with nulike.
  ///   --> log10Enu log_10(neutrino energy/GeV)
  ///   --> p        p=1 for neutrino yield, p=2 for nubar yield,
  ///                p=3 for nu and nubar yields
  ///   --> context  void pointer (ignored)
  double neutrino_yield(const double& log10E, const int& ptype, void*&)
  {
    int istat = 0;
    int iistat = 0;
    int t1=3; // nu mu
    int t2=4; // nu_mu-bar
    const char*object =  (char *)"su";

    double tmp=0;
    int twoj=0; // ignored by current version of DS
    int twos=0; // ignored by current version of DS
    int twol=0; // ignored by current version of DS
    int cp=-1;  // ignored by current version of DS
    double result=0.0;

    for (int i=1; i<=29; i++)
    {
      if (DSanbr[i]>0)
      {
        iistat=0;
        if ((ptype == 1) or (ptype == 3)) // particles
        {
          // Temporary hack replacing h h and Z h final state spectra with Z Z
          if ((DSanpdg1[i] == 25 && DSanpdg2[i] == 25) || (DSanpdg1[i] == 23 && DSanpdg2[i] == 25))
            tmp=dsseyield_sim_ls(anmwimp,pow(10.0,log10E),10.0,23,23,twoj,cp,twol,twos,object,3,t1,iistat);
          else
            tmp=dsseyield_sim_ls(anmwimp,pow(10.0,log10E),10.0,DSanpdg1[i],DSanpdg2[i],twoj,cp,twol,twos,object,3,t1,iistat);
          if ((iistat bitand 8) == 8) // not simulated channel
          {
            backend_error().raise(LOCAL_INFO, "ERROR: The DarkSUSY neutrino telescope routines "
                                  "for a generic WIMP cannot handle models with non-standard model\n"
                                  "WIMP annihilation final states.");
          }
          result += 1e-30 * DSanbr[i] * tmp;

          // The following is just a warning, not an error: unpolarized yields
          // are used even if polarized yields are asked for
          if ((iistat bitand 16) == 16) iistat -= 16;
          istat=(istat bitor iistat);
        }

        if ((ptype == 2) or (ptype == 3)) // anti-particles
        {
          // Temporary hack replacing h h and Z h final state spectra with Z Z
          if ((DSanpdg1[i] == 25 && DSanpdg2[i] == 25) || (DSanpdg1[i] == 23 && DSanpdg2[i] == 25))
            tmp=dsseyield_sim_ls(anmwimp,pow(10.0,log10E),10.0,23,23,twoj,cp,twol,twos,object,3,t2,iistat);
          else
            tmp=dsseyield_sim_ls(anmwimp,pow(10.0,log10E),10.0,DSanpdg1[i],DSanpdg2[i],twoj,cp,twol,twos,object,3,t2,iistat);
          if ((iistat bitand 8) == 8) // not simulated channel
          {
            backend_error().raise(LOCAL_INFO, "ERROR: The DarkSUSY neutrino telescope routines "
                                  "for a generic WIMP cannot handle models with non-standard model\n"
                                  "WIMP annihilation final states.");
          }
          result += 1e-30 * DSanbr[i] * tmp;

          // The following is just a warning, not an error: unpolarized yields
          // are used even if polarized yields are asked for
          if ((iistat bitand 16) == 16) iistat -= 16;
          istat=(istat bitor iistat);
        }

      } // end if DSanbr>0

    } // end loop


    if ((istat bitand 1) == 1)
    {
      if (not piped_warnings.inquire()) // Don't bother re-raising a warning if it's already been done since the last .check().
        piped_warnings.request(LOCAL_INFO, "Neutrino yield from Sun is lower bound; likelihood will be conservative.");
    }
    if ((istat bitand 4) == 4)
    {
      if (not piped_warnings.inquire()) // Don't bother re-raising a warning if it's already been done since the last .check().
        piped_warnings.request(LOCAL_INFO, "DarkSUSY's dsseyield_int didn't converge. This occasionally happens "
                                           "due to finite statistics in the nu yield tables from Pythia. "
                                           "This is benign (the missing integrals are always negligible).");
    }
    if (istat > 4)
    {
      std::ostringstream err;
      err << "Error from DarkSUSY::dsseyield functions in neutrino flux calculation.  istat = " << istat;
      piped_errors.request(LOCAL_INFO, err.str());
    }
    return result;
  }

  /// Returns the vector of neutral Higgs decay channels in DarkSUSY
  std::vector< std::vector<str> > DS_neutral_h_decay_channels()
  {
    return initVector< std::vector<str> >
     (initVector<str>("h0_2", "h0_2"),
      initVector<str>("h0_1", "h0_2"),
      initVector<str>("h0_1", "h0_1"),
      initVector<str>("A0", "A0"),
      initVector<str>("h0_2", "A0"),
      initVector<str>("h0_1", "A0"),
      initVector<str>("H+", "H-"),
      initVector<str>("Z0", "h0_2"),
      initVector<str>("Z0", "h0_1"),
      initVector<str>("Z0", "A0"),
      // actually supposed to be W+H- and W-H+
      initVector<str>("W+", "H-"),
      initVector<str>("Z0", "Z0"),
      initVector<str>("W+", "W-"),
      initVector<str>("nu_e", "nubar_e"),
      initVector<str>("e+_1", "e-_1"),
      initVector<str>("nu_mu", "nubar_mu"),
      initVector<str>("e+_2", "e-_2"),
      initVector<str>("nu_tau", "nubar_tau"),
      initVector<str>("e+_3", "e-_3"),
      initVector<str>("u_1", "ubar_1"),
      initVector<str>("d_1", "dbar_1"),
      initVector<str>("u_2", "ubar_2"),
      initVector<str>("d_2", "dbar_2"),
      initVector<str>("u_3", "ubar_3"),
      initVector<str>("d_3", "dbar_3"),
      initVector<str>("g", "g"),
      // actually qqg (not implemented in DS though)
      initVector<str>("d_3", "dbar_3", "g"),
      initVector<str>("gamma", "gamma"),
      initVector<str>("Z0", "gamma")
     );
  }

  /// Returns the vector of charged Higgs decay channels in DarkSUSY
  std::vector< std::vector<str> > DS_charged_h_decay_channels()
  {
    return initVector< std::vector<str> >
     (initVector<str>("u_1", "dbar_1"),
      initVector<str>("u_1", "dbar_2"),
      initVector<str>("u_1", "dbar_3"),
      initVector<str>("u_2", "dbar_1"),
      initVector<str>("u_2", "dbar_2"),
      initVector<str>("u_2", "dbar_3"),
      initVector<str>("u_3", "dbar_1"),
      initVector<str>("u_3", "dbar_2"),
      initVector<str>("u_3", "dbar_3"),
      initVector<str>("e+_1", "nu_e"),
      initVector<str>("e+_2", "nu_mu"),
      initVector<str>("e+_3", "nu_tau"),
      initVector<str>("W+", "h0_2"),
      initVector<str>("W+", "h0_1"),
      initVector<str>("W+", "A0")
     );
  }
}
END_BE_NAMESPACE
