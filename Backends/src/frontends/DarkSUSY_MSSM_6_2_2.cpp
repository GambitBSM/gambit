//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend for DarkSUSY 6.2.2 backend
///  (adapted from DarkSUSY_6_1_1.cpp)
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Torsten Bringmann
///          (torsten.bringmann@fys.uio.no)
///  \date 2018 2019
///
///  \author Joakim Edsjo
///          (edsjo@fysik.su.se)
///  \date 2018 September
///
///  \author Pat Scott
///          (pat.scott@uq.edu.au)
///  \date 2020 September
///
///  *********************************************

#include "gambit/Backends/frontend_macros.hpp"
#include "gambit/Backends/frontends/DarkSUSY_MSSM_6_2_2.hpp"
#include "gambit/Utils/file_lock.hpp"
#include "gambit/Utils/mpiwrapper.hpp"

//#define DARKSUSY_DEBUG

// Some ad-hoc DarkSUSY global state.
BE_NAMESPACE
{
  const double min_DS_rwidth = 5.e-3; // 0.5%  to avoid numerical problems
  std::vector<double> DSparticle_mass;
  std::vector<double> GAMBITparticle_mass;
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

    scan_level = false;
  }

  // Initialization function for a given MSSM point
  // (previous capability DarkSUSY_PointInit)
  bool mssm_result = false;

  // If the user provides a file list, just read in SLHA files for debugging
  // and ignore the MSSM_spectrum dependency.
  if (runOptions->hasKey("debug_SLHA_filenames"))
  {
    static unsigned int counter = 0;
    logger() << LogTags::debug <<
      "Initializing DarkSUSY via debug_SLHA_filenames option." << EOM;

    /// Option debug_SLHA_filenames<std::vector<std::string>>: Optional override list of SLHA filenames used for backend initialization default
    std::vector<str> filenames = runOptions->getValue<std::vector<str> >("debug_SLHA_filenames");
    const char * filename = filenames[counter].c_str();
    int flag = 15;
    dsSLHAread(byVal(filename),byVal(flag)); // dsgive_model_SLHA
    int unphys, warning;
    dsmodelsetup(unphys,warning);
    if (unphys < 0)
    {
      backend_warning().raise(LOCAL_INFO,
          "Model point is theoretically inconsistent (DarkSUSY).");
      invalid_point().raise(
         "Model point is theoretically inconsistent (DarkSUSY).");
      mssm_result = false;
    }
    else if (unphys > 0)
    {
      backend_warning().raise(LOCAL_INFO,
          "Neutralino is not the LSP (DarkSUSY).");
      invalid_point().raise("Neutralino is not the LSP (DarkSUSY).");
      mssm_result = false;
    }
    else if (warning != 0)
    {
      backend_warning().raise(LOCAL_INFO,
          "Radiative corrections in Higgs sector "
          "outside range of validity (DarkSUSY).");
      mssm_result = true;
    }
    else
    {
      mssm_result = true;
    }

    counter++;
    if (counter >= filenames.size()) counter = 0;
    mssm_result = true;
  }

  // CMSSM with DS-internal ISASUGRA (should be avoided, only for debugging)
  /// Option use_DS_isasugra<bool>: Use DS internal isasugra for parameter running (false)
  else if (ModelInUse("CMSSM") and runOptions->getValueOrDef<bool>(false, "use_DS_isasugra"))
  {
    // Setup mSUGRA model from CMSSM parameters
    double am0    = *Param["M0"];     // m0
    double amhf   = *Param["M12"];    // m_1/2
    double aa0    = *Param["A0"];     // A0
    double asgnmu = *Param["SignMu"];  // sign(mu)
    double atanbe = *Param["TanBeta"];   // tan(beta)
    logger() << "Initializing DarkSUSY via dsgive_model_isasugra:" << EOM;
    logger() << "  m0        =" << am0    << std::endl;
    logger() << "  m_1/2     =" << amhf   << std::endl;
    logger() << "  A0        =" << aa0    << std::endl;
    logger() << "  sign(mu)  =" << asgnmu << std::endl;
    logger() << "  tan(beta) =" << atanbe << EOM;
    dsgive_model_isasugra(am0, amhf, aa0, asgnmu, atanbe);
    int unphys, warning;
    dsmodelsetup(unphys, warning);

    if (unphys < 0)
    {
      backend_warning().raise(LOCAL_INFO, "Model point is theoretically inconsistent (DarkSUSY).");
      invalid_point().raise("Model point is theoretically inconsistent (DarkSUSY).");
      mssm_result = false;
    }
    else if (unphys > 0)
    {
      backend_warning().raise(LOCAL_INFO, "Neutralino is not the LSP (DarkSUSY).");
      invalid_point().raise("Neutralino is not the LSP (DarkSUSY).");
      mssm_result = false;
    }
    else if (warning != 0)
    {
      backend_warning().raise(LOCAL_INFO,
          "Radiative corrections in Higgs sector "
          "outside range of validity (DarkSUSY).");
      mssm_result = true;
    }
    else
    {
      mssm_result = true;
    }
  }

  else if (ModelInUse("MSSM63atQ") || ModelInUse("CMSSM"))
  {
    SLHAstruct mySLHA;
    /// Option use_dsSLHAread<bool>: Use DS internal SLHA reader to initialize backend (false)
    bool use_dsSLHAread = runOptions->getValueOrDef<bool>(false, "use_dsSLHAread");
    int slha_version = 2;
    const Spectrum& mySpec = *Dep::MSSM_spectrum;
    try
    {
      mySLHA = mySpec.getSLHAea(2);
    }
    catch(Gambit::exception& e)
    {
        slha_version = 1;
        mySLHA = mySpec.getSLHAea(1);
        use_dsSLHAread = true;
    }

    // Use an actual SLHA file.  DarkSUSY is on its own wrt (s)particle widths this way.
    if (use_dsSLHAread || slha_version == 1)
    {
      if (!use_dsSLHAread) {backend_error().raise(LOCAL_INFO,
              "An SLHA1 spectrum requires use of the DarkSUSY SLHA reader rather than the diskless\n"
              "GAMBIT DarkSUSY initialization. To enable the DarkSUSY SLHA reader, set the option\n"
              "use_dsSLHAread for the function DarkSUSY_PointInit_MSSM to true.");}

      int rank = 0;
      #ifdef WITH_MPI
        if(GMPI::Is_initialized())
        {
          GMPI::Comm comm;
          rank = comm.Get_rank();
        }
      #endif

      // Add model select block to inform DS about 6x6 mixing
      if (slha_version == 2)
      {
          SLHAea::Block modsel_block("MODSEL");
          modsel_block.push_back("BLOCK MODSEL");
          modsel_block.push_back("6 3 # FV");
          mySLHA.push_back(modsel_block);
      }
      // Set filename
      std::string fstr = "DarkBit_temp_";
      fstr += std::to_string(rank) + ".slha";
      // Dump SLHA onto disk
      std::ofstream ofs(fstr);
      ofs << mySLHA;
      ofs.close();
      // Initialize SUSY spectrum from SLHA
      int flag = 15;
      const char * filename = fstr.c_str();
      logger() << LogTags::debug << "Initializing DarkSUSY via SLHA." << EOM;
      dsSLHAread(byVal(filename),flag);
      int unphys,warning;
      dsmodelsetup(unphys,warning);
      if (unphys < 0)
      {
        backend_warning().raise(LOCAL_INFO,
            "Model point is theoretically inconsistent (DarkSUSY).");
        invalid_point().raise(
            "Model point is theoretically inconsistent (DarkSUSY).");
        mssm_result = false;
      }
      else if (unphys > 0)
      {
        backend_warning().raise(LOCAL_INFO,
            "Neutralino is not the LSP (DarkSUSY).");
        invalid_point().raise("Neutralino is not the LSP (DarkSUSY).");
        mssm_result = false;
      }
      else if (warning != 0)
      {
        backend_warning().raise(LOCAL_INFO,
            "Radiative corrections in Higgs sector "
            "outside range of validity (DarkSUSY).");
        mssm_result = true;
      }
      else
      {
        mssm_result = true;
      }
    }

    // Do pure diskless SLHA initialisation, including (s)particle widths from GAMBIT.
    else
    {
      if (init_diskless(mySLHA, *Dep::decay_rates) == 0 )
      {
        logger() << LogTags::debug << "Using diskless SLHA interface to DarkSUSY." << EOM;
        int unphys,warning;
        dsmodelsetup(unphys,warning);

        if (unphys < 0)
        {
          backend_warning().raise(LOCAL_INFO,
              "Model point is theoretically inconsistent (DarkSUSY).");
          invalid_point().raise(
              "Model point is theoretically inconsistent (DarkSUSY).");
          mssm_result = false;
        }
        else if (unphys > 0)
        {
          backend_warning().raise(LOCAL_INFO,
              "Neutralino is not the LSP (DarkSUSY).");
          invalid_point().raise("Neutralino is not the LSP (DarkSUSY).");
          mssm_result = false;
        }
        else if (warning != 0)
        {
          backend_warning().raise(LOCAL_INFO,
              "Radiative corrections in Higgs sector "
              "outside range of validity (DarkSUSY).");
          mssm_result = true;
        }
        else
        {
          mssm_result = true;
        }
      }
    }
  }

  if ( (ModelInUse("MSSM63atQ") || ModelInUse("CMSSM")) && !mssm_result )
  {
    backend_warning().raise(LOCAL_INFO,
        "DarkSUSY point initialization failed.");
    invalid_point().raise("DarkSUSY point initialization failed.");
  }

}
END_BE_INI_FUNCTION


// Convenience functions (definitions)
BE_NAMESPACE
{

  /// Shortcut for dealing with SLHA blocks
  void required_block(const std::string& name, const SLHAea::Coll& slha)
  {
    if (slha.find(name) != slha.end()) return;
    else backend_error().raise(LOCAL_INFO, "Sorry, DarkSUSY needs SLHA block: " + name + ".\n"
    "If you tried to read in a debug SLHA file with missing entries,                       \n"
    "then sort out your SLHA file so that it is readable by DarkSUSY!                      ");
  }

  /// Sets DarkSUSY's internal common blocks with some of the properties required to compute neutrino
  /// yields for a generic WIMP. Remaining internal variables are internal to this frontend.
  void dsgenericwimp_nusetup(const double (&annihilation_bf)[29], const double (&Higgs_decay_BFs_neutral)[29][3],
   const double (&Higgs_decay_BFs_charged)[15], const double (&Higgs_masses_neutral)[3], const double &Higgs_mass_charged,
   const double &mwimp)
  {
    // Transfer WIMP mass common block.
    anmwimp = mwimp;

    // Transfer branching fractions to WIMP annihilation common blocks.
    // For channel indices, see dswayieldone.f
    DSanbr.clear();
    DSanbr.push_back(0.0);
    //DSanbr[0]=0.0; // not used, keep Fortran numbering below
    for (int i=1; i<=29; i++)
    {
        DSanbr.push_back(annihilation_bf[i-1]);
    }

    // Setup PDG common blocks
    DSanpdg1.clear();
    DSanpdg2.clear();
    DSanpdg1.push_back(10000); // not used, as we keep the same numbering as for Fortran
    DSanpdg2.push_back(10000);
    DSanpdg1.push_back(35);  // H H, channel 1
    DSanpdg2.push_back(35);
    DSanpdg1.push_back(25);  // h H, channel 2
    DSanpdg2.push_back(35);
    DSanpdg1.push_back(25);  // h h, channel 3
    DSanpdg2.push_back(25);
    DSanpdg1.push_back(36);  // A A, channel 4
    DSanpdg2.push_back(36);
    DSanpdg1.push_back(35);  // H A, channel 5
    DSanpdg2.push_back(36);
    DSanpdg1.push_back(25);  // h A, channel 6
    DSanpdg2.push_back(36);
    DSanpdg1.push_back(37);  // H+ H-, channel 7
    DSanpdg2.push_back(-37);
    DSanpdg1.push_back(23);  // Z H, channel 8
    DSanpdg2.push_back(35);
    DSanpdg1.push_back(23);  // Z h, channel 9
    DSanpdg2.push_back(25);
    DSanpdg1.push_back(23);  // Z A, channel 10
    DSanpdg2.push_back(36);
    DSanpdg1.push_back(24);  // W+ H-, channel 11
    DSanpdg2.push_back(-37);
    DSanpdg1.push_back(23);  // Z Z, channel 12
    DSanpdg2.push_back(23);
    DSanpdg1.push_back(24);  // W+ W-, channel 13
    DSanpdg2.push_back(-24);
    DSanpdg1.push_back(12);  // nue nuebar, channel 14
    DSanpdg2.push_back(-12);
    DSanpdg1.push_back(11);  // e- e+, channel 15
    DSanpdg2.push_back(-11);
    DSanpdg1.push_back(14);  // numu numubar, channel 16
    DSanpdg2.push_back(-14);
    DSanpdg1.push_back(13);  // mu- mu+, channel 17
    DSanpdg2.push_back(-13);
    DSanpdg1.push_back(16);  // nutau nutaubar, channel 18
    DSanpdg2.push_back(-16);
    DSanpdg1.push_back(15);  // tau- tau+, channel 19
    DSanpdg2.push_back(-15);
    DSanpdg1.push_back(2);   // u ubar, channel 20
    DSanpdg2.push_back(-2);
    DSanpdg1.push_back(1);   // d dbar, channel 21
    DSanpdg2.push_back(-1);
    DSanpdg1.push_back(4);   // c cbar, channel 22
    DSanpdg2.push_back(-4);
    DSanpdg1.push_back(3);   // s sbar, channel 23
    DSanpdg2.push_back(-3);
    DSanpdg1.push_back(6);   // t tbar, channel 24
    DSanpdg2.push_back(-6);
    DSanpdg1.push_back(5);   // b bbar, channel 25
    DSanpdg2.push_back(-5);
    DSanpdg1.push_back(21);   // gluon gluon, channel 26
    DSanpdg2.push_back(21);
    DSanpdg1.push_back(10000);   // (not used)
    DSanpdg2.push_back(10000);
    DSanpdg1.push_back(22);   // gamma gamma, channel 28
    DSanpdg2.push_back(22);
    DSanpdg1.push_back(22);   // gamma Z, channel 29
    DSanpdg2.push_back(23);

    // Transfer Higgs decay branching fractions (not widths) to Higgs decay common blocks.
    // The total width is not relevant, as all Higgs decay in flight eventually, so
    // only the BFs are needed to calculate the yields into neutrinos from decays in flight.
    for (int i=1; i<=3; i++)    // Loop over the neutral Higgses
    {
      for (int j=1; j<=29; j++) // Loop over the known decay channels
      {
        anbranch->ans0br(j,i) = Higgs_decay_BFs_neutral[j-1][i-1];
      }
    }

    for (int i=1; i<=15; i++)   // Loop over the known charged Higgs decay channels
    {
      anbranch->anscbr(i) = Higgs_decay_BFs_charged[i-1];
    }

    // Transfer Higgs masses to common blocks.
    for (int i=1; i<=3; i++)    // Loop over the neutral Higgses
    {
      anbranch->ans0m(i) = Higgs_masses_neutral[i-1];                   // Neutral Higgses
    }
    anbranch->anscm = Higgs_mass_charged;                               // Charged Higgses

  }

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
    int twoj=0;
    int twos=0;
    int twol=0;
    int cp=-1;
    double result=0.0;

    for (int i=1; i<=29; i++)
    {
      if (DSanbr[i]>0)
      {
        if (i==13) // W+ W-
        {
          twos=2;
          twol=2;
        }
        else
        {
          twos=0;
          twol=0;
        }
        iistat=0;

        if ((ptype == 1) or (ptype == 3)) // particles
        {
          tmp=dsseyield_sim_ls(anmwimp,pow(10.0,log10E),10.0,DSanpdg1[i],DSanpdg2[i],twoj,cp,twol,twos,object,3,t1,iistat);
          if ((iistat bitand 8) == 8) // not simulated channel
          {
            tmp=dsseyield_ch(anmwimp,pow(10.0,log10E),10.0,DSanpdg1[i],DSanpdg2[i],object,3,t1,iistat);
          }
          result += 1e-30 * DSanbr[i] * tmp;

          // The following is just a warning, not an error: unpolarized yields
          // are used even if polarized yields are asked for
          if ((iistat bitand 16) == 16) iistat -= 16;
          istat=(istat bitor iistat);
        }

        if ((ptype == 2) or (ptype == 3)) // anti-particles
        {
          tmp=dsseyield_sim_ls(anmwimp,pow(10.0,log10E),10.0,DSanpdg1[i],DSanpdg2[i],twoj,cp,twol,twos,object,3,t2,iistat);
          if ((iistat bitand 8) == 8) // not simulated channel
          {
            tmp=dsseyield_ch(anmwimp,pow(10.0,log10E),10.0,DSanpdg1[i],DSanpdg2[i],object,3,t2,iistat);
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

  /// Returns direct detection couplings gps,gns,gpa,gna
  /// (proton/neutron scalar/axial four-couplings)
  /// Provided here because the signature of the corresponding DarkSUSY routine
  std::vector<double> DD_couplings()
  {
    int ierr = 0;
    Farray<Fcomplex16,1,27,1,2> gg;
    dsddgpgn(gg,ierr);
    if (ierr > 0)
    {
      std::ostringstream err;
      err << "Error from DarkSUSY::dsddgpgn function when calling DD_couplings().  ierr = " << ierr;
      piped_errors.request(LOCAL_INFO, err.str());
    }
    std::vector<double> couplings;
    couplings.clear();
    couplings.push_back((double)gg(1,1).re); // gps
    couplings.push_back((double)gg(1,2).re); // gns
    couplings.push_back((double)gg(4,1).re); // gpa
    couplings.push_back((double)gg(4,2).re); // gna


    return couplings;
  }


  /// Translates GAMBIT string identifiers to the SUSY
  /// particle codes used internally in DS (as stored in common block /pacodes_mssm/)
  /// presently this is only needed in RD_annrate_DSprep_MSSM_func, to prepare (RelicDensity.cpp),
  /// to prepare DS for the calculation of the invariant rate, dsanwx.
  // Note: DarkSUSY use the opposite convention on h1_0 and h2_0. The names
  // used here are the gambit names where h1_0 hence refers to what DarkSUSY
  // calls H2.
  int DSparticle_code(const str& particleID)
  {
    int kpart;
    if (particleID=="nu_e" or particleID=="nubar_e"){
     kpart=1;
    }else if (particleID=="e-_1" or particleID=="e+_1"){
     kpart=2;
    }else if (particleID=="nu_mu" or particleID=="nubar_mu"){
     kpart=3;
    }else if (particleID=="e-_2" or particleID=="e+_2"){
     kpart=4;
    }else if (particleID=="nu_tau" or particleID=="nubar_tau"){
     kpart=5;
    }else if (particleID=="e-_3" or particleID=="e+_3"){
     kpart=6;
    }else if (particleID=="u_1" or particleID=="ubar_1"){
     kpart=7;
    }else if (particleID=="d_1" or particleID=="dbar_1"){
     kpart=8;
    }else if (particleID=="u_2" or particleID=="ubar_2"){
     kpart=9;
    }else if (particleID=="d_2" or particleID=="dbar_2"){
     kpart=10;
    }else if (particleID=="u_3" or particleID=="ubar_3"){
     kpart=11;
    }else if (particleID=="d_3" or particleID=="dbar_3"){
     kpart=12;
    }else if (particleID=="gamma"){
     kpart=13;
    }else if (particleID=="W+" or particleID=="W-"){
     kpart=14;
    }else if (particleID=="Z0"){
     kpart=15;
    }else if (particleID=="g"){
     kpart=16;
    }else if (particleID=="h0_1"){
     kpart=18;
    }else if (particleID=="h0_2"){
     kpart=17;
    }else if (particleID=="A0"){
     kpart=19;
    }else if (particleID=="H+" or particleID=="H-"){
     kpart=20;
    }else if (particleID=="~nu_1" or particleID=="~nubar_1"){
     kpart=21;
    }else if (particleID=="~e-_1" or particleID=="~e+_1"){
     kpart=22;
    }else if (particleID=="~e-_4" or particleID=="~e+_4"){
     kpart=23;
    }else if (particleID=="~nu_2" or particleID=="~nubar_2"){
     kpart=24;
    }else if (particleID=="~e-_2" or particleID=="~e+_2"){
     kpart=25;
    }else if (particleID=="~e-_5" or particleID=="~e+_5"){
     kpart=26;
    }else if (particleID=="~nu_3" or particleID=="~nubar_3"){
     kpart=27;
    }else if (particleID=="~e-_3" or particleID=="~e+_3"){
     kpart=28;
    }else if (particleID=="~e-_6" or particleID=="~e+_6"){
     kpart=29;
    }else if (particleID=="~u_1" or particleID=="~ubar_1"){
     kpart=30;
    }else if (particleID=="~u_4" or particleID=="~ubar_4"){
     kpart=31;
    }else if (particleID=="~d_1" or particleID=="~dbar_1"){
     kpart=32;
    }else if (particleID=="~d_4" or particleID=="~dbar_4"){
     kpart=33;
    }else if (particleID=="~u_2" or particleID=="~ubar_2"){
     kpart=34;
    }else if (particleID=="~u_5" or particleID=="~ubar_5"){
     kpart=35;
    }else if (particleID=="~d_2" or particleID=="~dbar_2"){
     kpart=36;
    }else if (particleID=="~d_5" or particleID=="~dbar_5"){
     kpart=37;
    }else if (particleID=="~u_3" or particleID=="~ubar_3"){
     kpart=38;
    }else if (particleID=="~u_6" or particleID=="~ubar_6"){
     kpart=39;
    }else if (particleID=="~d_3" or particleID=="~dbar_3"){
     kpart=40;
    }else if (particleID=="~d_6" or particleID=="~dbar_6"){
     kpart=41;
    }else if (particleID=="~chi0_1"){
     kpart=42;
    }else if (particleID=="~chi0_2"){
     kpart=43;
    }else if (particleID=="~chi0_3"){
     kpart=44;
    }else if (particleID=="~chi0_4"){
     kpart=45;
    }else if (particleID=="~chi+_1" or particleID=="~chi-_1"){
     kpart=46;
    }else if (particleID=="~chi+_2" or particleID=="~chi-_2"){
     kpart=47;
    }else if (particleID=="~g"){
     kpart=48;
    } else{
     std::ostringstream err;
     err << "ERROR: translation into DS particle code not implemented "
         << "for string identifier " << particleID;
     backend_error().raise(LOCAL_INFO, err.str());
     kpart=-100;
    }
    return kpart;
  }

  /// Initialise an MSSM model in DarkSUSY from an SLHAea object and a DecayTable.
  /// Closely mimics the DarkSUSY routine in dsfromslha.F, except that it
  /// hands over a better b pole mass, explicit decay info, and a better
  /// approximation of the CKM matrix from Wolfenstein parameters.  Throughout
  /// this routine, there are pieces of code commented out that would need to be
  /// re-added to emulate dsfromslha.F exactly, if and only if the decays are not
  /// set by GAMBIT.
  int init_diskless(const SLHAstruct &mySLHA, const DecayTable &myDecays)
  {
    using SLHAea::to;
    DS_PACODES_MSSM *DSpart = &(*pacodes_mssm);

    // Define required blocks and raise an error if a block is missing
    required_block("SMINPUTS", mySLHA);
    required_block("VCKMIN",   mySLHA);
    required_block("MSOFT",    mySLHA);
    required_block("MASS",     mySLHA);
    required_block("NMIX",     mySLHA);
    required_block("VMIX",     mySLHA);
    required_block("UMIX",     mySLHA);
    required_block("ALPHA",    mySLHA);
    required_block("HMIX",     mySLHA);
    required_block("YU",       mySLHA);
    required_block("YD",       mySLHA);
    required_block("YE",       mySLHA);
    required_block("MSL2",     mySLHA);
    required_block("MSE2",     mySLHA);
    required_block("MSQ2",     mySLHA);
    required_block("MSD2",     mySLHA);
    required_block("MSU2",     mySLHA);
    required_block("TD",       mySLHA);
    required_block("TU",       mySLHA);
    required_block("TE",       mySLHA);
    required_block("USQMIX",   mySLHA);
    required_block("DSQMIX",   mySLHA);
    required_block("SELMIX",   mySLHA);
    required_block("SNUMIX",   mySLHA);

    // Make sure the b pole mass is present in the MASS block
    if (mySLHA.at("MASS").find(initVector<str>("5")) == mySLHA.at("MASS").end())
      backend_error().raise(LOCAL_INFO, "DarkSUSY init_diskless needs b pole mass entry (5) in SLHA(ea) MASS block.");

    // Do some initial DarkSUSY housekeeping.
    dsmssmzero();            // zero all the MSSM parameters and variables
    mssmtype->modeltype = 0; // tell DarkSUSY that we are working in the general MSSM
    // To match the DarkSUSY SLHAreader, you would need to also set
    // mssmswitch->higwid = 1;  // tell DarkSUSY not to use FeynHiggs for Higgs widths.

    // Block SMINPUTS
    smcoupling->alphem                   = 1./to<double>(mySLHA.at("SMINPUTS").at(1).at(1)); // 1/alpha_{QED}
    smcoupling->alph3mz                  = to<double>(mySLHA.at("SMINPUTS").at(3).at(1));    // alpha_s @ MZ
    smcoupling->gfermi                   = to<double>(mySLHA.at("SMINPUTS").at(2).at(1));    // Fermi constant
    pmasses->mass(DSparticle_code("Z0")) = to<double>(mySLHA.at("SMINPUTS").at(4).at(1));    // Z boson mass

    // Here we set the masses to be used in DarkSUSY.  Note that all masses in the pmasses->mass block
    // must match those in the ProcessCatalog in DarkBit, as these are used to define the kinematic
    // edges used in relic density integrations and similar within DarkSUSY.  Mostly these should be
    // pole masses, except in cases where that is not possible (i.e. light quarks).

    // Lepton masses
    pmasses->mass(DSpart->kl(1))  = to<double>(mySLHA.at("SMINPUTS").at(11).at(1));  // electron pole mass
    pmasses->mass(DSpart->kl(2))  = to<double>(mySLHA.at("SMINPUTS").at(13).at(1));  // muon pole mass
    pmasses->mass(DSpart->kl(3))  = to<double>(mySLHA.at("SMINPUTS").at(7).at(1));   // tau pole mass
    pmasses->mass(DSpart->knu(1)) = to<double>(mySLHA.at("SMINPUTS").at(12).at(1));  // nu_1 pole mass
    pmasses->mass(DSpart->knu(2)) = to<double>(mySLHA.at("SMINPUTS").at(14).at(1));  // nu_2 pole mass
    pmasses->mass(DSpart->knu(3)) = to<double>(mySLHA.at("SMINPUTS").at(8).at(1));   // nu_3 pole mass

    // Quark masses as defined in SLHA2
    smquarkmasses->mu2gev         = to<double>(mySLHA.at("SMINPUTS").at(22).at(1)); // up quark mass @ 2 GeV
    smquarkmasses->md2gev         = to<double>(mySLHA.at("SMINPUTS").at(21).at(1)); // down quark mass @ 2 GeV
    smquarkmasses->ms2gev         = to<double>(mySLHA.at("SMINPUTS").at(23).at(1)); // strange mass @ 2 GeV
    smquarkmasses->mcmc           = to<double>(mySLHA.at("SMINPUTS").at(24).at(1)); // charm mass at m_c
    smquarkmasses->mbmb           = to<double>(mySLHA.at("SMINPUTS").at(5).at(1));  // bottom mass at m_b
    pmasses->mass(DSpart->kqu(3)) = to<double>(mySLHA.at("SMINPUTS").at(6).at(1));  // top pole mass

    // Do the DarkSUSY-style sin^2 theta_W calculation (will be overwritten later).
    smcoupling->s2thw=dsgf2s2thw(smcoupling->gfermi, smcoupling->alphem, pmasses->mass(DSparticle_code("Z0")), pmasses->mass(DSpart->kqu(3)),1);

    // Set other internal quark masses for DarkSUSY
    dsfindmtmt();                                                                       // top mass at mt
    pmasses->mass(DSpart->kqu(1)) = smquarkmasses->mu2gev;                              // use 2GeV u mass as proxy for pole
    pmasses->mass(DSpart->kqd(1)) = smquarkmasses->md2gev;                              // use 2GeV d mass as proxy for pole
    pmasses->mass(DSpart->kqd(2)) = smquarkmasses->ms2gev;                              // use 2GeV s mass as proxy for pole
    pmasses->mass(DSpart->kqu(2)) = dsmqpole4loop(DSpart->kqu(2),smquarkmasses->mcmc);  // use DarkSUSY internal routine to get mc pole
    pmasses->mass(DSpart->kqd(3)) = to<double>(mySLHA.at("MASS").at(5).at(1));          // the GAMBIT way to get the bottom pole mass
    //pmasses->mass(DSpart->kqd(3)) = dsmqpole4loop(DSpart->kqd(3),smquarkmasses->mbmb);// the DarkSUSY SLHAreader way to get mb pole

    // Block MINPAR we skip, it is not needed

    // Block MSOFT (this comes later in DS, but this has no effect on DS calls)
    mssmpar->m1 = to<double>(mySLHA.at("MSOFT").at(1).at(1));
    mssmpar->m2 = to<double>(mySLHA.at("MSOFT").at(2).at(1));
    mssmpar->m3 = to<double>(mySLHA.at("MSOFT").at(3).at(1));
    mssmpar->mass2l(1) = pow(to<double>(mySLHA.at("MSOFT").at(31).at(1)),2);
    mssmpar->mass2l(2) = pow(to<double>(mySLHA.at("MSOFT").at(32).at(1)),2);
    mssmpar->mass2l(3) = pow(to<double>(mySLHA.at("MSOFT").at(33).at(1)),2);
    mssmpar->mass2e(1) = pow(to<double>(mySLHA.at("MSOFT").at(34).at(1)),2);
    mssmpar->mass2e(2) = pow(to<double>(mySLHA.at("MSOFT").at(35).at(1)),2);
    mssmpar->mass2e(3) = pow(to<double>(mySLHA.at("MSOFT").at(36).at(1)),2);
    mssmpar->mass2q(1) = pow(to<double>(mySLHA.at("MSOFT").at(41).at(1)),2);
    mssmpar->mass2q(2) = pow(to<double>(mySLHA.at("MSOFT").at(42).at(1)),2);
    mssmpar->mass2q(3) = pow(to<double>(mySLHA.at("MSOFT").at(43).at(1)),2);
    mssmpar->mass2u(1) = pow(to<double>(mySLHA.at("MSOFT").at(44).at(1)),2);
    mssmpar->mass2u(2) = pow(to<double>(mySLHA.at("MSOFT").at(45).at(1)),2);
    mssmpar->mass2u(3) = pow(to<double>(mySLHA.at("MSOFT").at(46).at(1)),2);
    mssmpar->mass2d(1) = pow(to<double>(mySLHA.at("MSOFT").at(47).at(1)),2);
    mssmpar->mass2d(2) = pow(to<double>(mySLHA.at("MSOFT").at(48).at(1)),2);
    mssmpar->mass2d(3) = pow(to<double>(mySLHA.at("MSOFT").at(49).at(1)),2);

    // Block HMIX
    mssmpar->mu = to<double>(mySLHA.at("HMIX").at(1).at(1));
    mssmpar->tanbe = to<double>(mySLHA.at("HMIX").at(2).at(1));

    // A boson mass (h3 in DarkSUSY)
    pmasses->mass(DSparticle_code("A0")) = to<double>(mySLHA.at("MASS").at(36).at(1));
    mssmpar->ma = pmasses->mass(DSparticle_code("A0"));

    // Now set up some defaults (part of it will be overwritten later)
    // (this does not require ckm matrices, which are set up earlier in DS)
    dssuconst_yukawa();
    dssuconst_higgs();

    mssmiuseful->lsp = DSpart->kn(1);
    mssmiuseful->kln = 1;
    // To match the DS SLHAreader, you would then need to call
    // int unphys, hwarning;
    // dsspectrum(unphys, hwarning);

    // CKM matrix read from VCKMIN - Wolfenstein parameters.
    double lambda = to<double>(mySLHA.at("VCKMIN").at(1).at(1));   // Wolfenstein lambda
    double A = to<double>(mySLHA.at("VCKMIN").at(2).at(1));        // Wolfenstein A
    double rhobar = to<double>(mySLHA.at("VCKMIN").at(3).at(1));   // Wolfenstein rhobar
    double etabar = to<double>(mySLHA.at("VCKMIN").at(4).at(1));   // Wolfenstein etabar
    // Use Wolfenstein converter to get the VCKM matrix.
    mixing->ckm(1,1) = Spectrum::Wolf2V_ud(lambda,A,rhobar,etabar);
    mixing->ckm(1,2) = Spectrum::Wolf2V_us(lambda,A,rhobar,etabar);
    mixing->ckm(1,3) = Spectrum::Wolf2V_ub(lambda,A,rhobar,etabar);
    mixing->ckm(2,1) = Spectrum::Wolf2V_cd(lambda,A,rhobar,etabar);
    mixing->ckm(2,2) = Spectrum::Wolf2V_cs(lambda,A,rhobar,etabar);
    mixing->ckm(2,3) = Spectrum::Wolf2V_cb(lambda,A,rhobar,etabar);
    mixing->ckm(3,1) = Spectrum::Wolf2V_td(lambda,A,rhobar,etabar);
    mixing->ckm(3,2) = Spectrum::Wolf2V_ts(lambda,A,rhobar,etabar);
    mixing->ckm(3,3) = Spectrum::Wolf2V_tb(lambda,A,rhobar,etabar);
    // The lower-order DarkSUSY SLHAreader way of doing it; not as good, but this is what you'd need to use to match DS exactly.
    //sckm->ckms12 = lambda;
    //sckm->ckms23 = A*pow(sckm->ckms12,2);
    //std::complex<double> aux(rhobar, etabar);
    //aux = aux * (sckm->ckms23/pow(sckm->ckms12,2)) * pow(sckm->ckms12,3);
    //sckm->ckms13 = std::norm(aux);
    //sckm->ckmdelta = std::arg(aux);
    //dssuconst_ckm();

    // In principle, we might want to change to VCKM instead of VCKMIN, if VCKM is present. Like this:
    // sckm->ckms12 = to<double>(mySLHA.at("VCKM").at(1).at(1));
    // sckm->ckms23 = to<double>(mySLHA.at("VCKM").at(2).at(1))*sckm.ckms12**2;
    // sckm->ckmdelta = 0;
    // for (int i=1; i<=3; i++) for (int j=1; j<=3; j++)
    // {
    //   mixing->ckm(i,j) = to<double_complex>(mySLHA.at("VCKM").at(i,j).at(2));
    // }

    // OK, we now have to enforce the tree-level condition for unitarity.
    // We then have a choice of calculating both sin^2 theta_W and MW
    // from alpha, MZ and GF as we normally do in DarkSUSY. This line would
    // enforce that:
    //  pmasses->mass(DSparticle_code("W+"))=pmasses->mass(DSparticle_code("Z0"))*sqrt(1.0-smcoupling->s2thw);
    // However, it is more prudent to take the value of MW from the SLHA file
    // as given (read in earlier), and instead enforce the tree-level condition
    // by redefining sin^2 theta_W. That we do here:
    pmasses->mass(DSparticle_code("W+"))  = to<double>(mySLHA.at("MASS").at(24).at(1));    // W boson mass
    smcoupling->s2thw=1.0-pow(pmasses->mass(DSparticle_code("W+"))/pmasses->mass(DSparticle_code("Z0")),2);

    // Higgs masses. Note h0_1 is the lightest CP-even neutral higgs, and h2_0 the heavier.
    pmasses->mass(DSparticle_code("h0_1")) = to<double>(mySLHA.at("MASS").at(25).at(1));
    pmasses->mass(DSparticle_code("h0_2")) = to<double>(mySLHA.at("MASS").at(35).at(1));
    pmasses->mass(DSparticle_code("H+"))   = to<double>(mySLHA.at("MASS").at(37).at(1));
    pmasses->mass(DSparticle_code("A0"))   = to<double>(mySLHA.at("MASS").at(36).at(1));

    // SUSY particles
    pmasses->mass(DSpart->ksnu(1)) =  to<double>(mySLHA.at("MASS").at(1000012).at(1));
    pmasses->mass(DSpart->ksnu(2)) =  to<double>(mySLHA.at("MASS").at(1000014).at(1));
    pmasses->mass(DSpart->ksnu(3)) =  to<double>(mySLHA.at("MASS").at(1000016).at(1));
    pmasses->mass(DSpart->ksl(1))  =  to<double>(mySLHA.at("MASS").at(1000011).at(1));
    pmasses->mass(DSpart->ksl(2))  =  to<double>(mySLHA.at("MASS").at(1000013).at(1));
    pmasses->mass(DSpart->ksl(3))  =  to<double>(mySLHA.at("MASS").at(1000015).at(1));
    pmasses->mass(DSpart->ksl(4))  =  to<double>(mySLHA.at("MASS").at(2000011).at(1));
    pmasses->mass(DSpart->ksl(5))  =  to<double>(mySLHA.at("MASS").at(2000013).at(1));
    pmasses->mass(DSpart->ksl(6))  =  to<double>(mySLHA.at("MASS").at(2000015).at(1));
    pmasses->mass(DSpart->ksqu(1)) =  to<double>(mySLHA.at("MASS").at(1000002).at(1));
    pmasses->mass(DSpart->ksqu(2)) =  to<double>(mySLHA.at("MASS").at(1000004).at(1));
    pmasses->mass(DSpart->ksqu(3)) =  to<double>(mySLHA.at("MASS").at(1000006).at(1));
    pmasses->mass(DSpart->ksqu(4)) =  to<double>(mySLHA.at("MASS").at(2000002).at(1));
    pmasses->mass(DSpart->ksqu(5)) =  to<double>(mySLHA.at("MASS").at(2000004).at(1));
    pmasses->mass(DSpart->ksqu(6)) =  to<double>(mySLHA.at("MASS").at(2000006).at(1));
    pmasses->mass(DSpart->ksqd(1)) =  to<double>(mySLHA.at("MASS").at(1000001).at(1));
    pmasses->mass(DSpart->ksqd(2)) =  to<double>(mySLHA.at("MASS").at(1000003).at(1));
    pmasses->mass(DSpart->ksqd(3)) =  to<double>(mySLHA.at("MASS").at(1000005).at(1));
    pmasses->mass(DSpart->ksqd(4)) =  to<double>(mySLHA.at("MASS").at(2000001).at(1));
    pmasses->mass(DSpart->ksqd(5)) =  to<double>(mySLHA.at("MASS").at(2000003).at(1));
    pmasses->mass(DSpart->ksqd(6)) =  to<double>(mySLHA.at("MASS").at(2000005).at(1));

    // Neutralinos carry the sign of the eigenvalue, as we need it for NMIX later
    pmasses->mass(DSpart->kn(1)) =  to<double>(mySLHA.at("MASS").at(1000022).at(1));
    pmasses->mass(DSpart->kn(2)) =  to<double>(mySLHA.at("MASS").at(1000023).at(1));
    pmasses->mass(DSpart->kn(3)) =  to<double>(mySLHA.at("MASS").at(1000025).at(1));
    pmasses->mass(DSpart->kn(4)) =  to<double>(mySLHA.at("MASS").at(1000035).at(1));

    // Charginos
    pmasses->mass(DSpart->kcha(1)) =  to<double>(mySLHA.at("MASS").at(1000024).at(1));
    pmasses->mass(DSpart->kcha(2)) =  to<double>(mySLHA.at("MASS").at(1000037).at(1));

    // Gluino
    pmasses->mass(DSparticle_code("~g")) =  to<double>(mySLHA.at("MASS").at(1000021).at(1));

    // Gravitino (not implemented in DarkSUSY)
    // pmasses->mass(DSpart->k...) =  to<double>(mySLHA.at("MASS").at(1000039).at(1));

    // Block NMIX
    for (int i=1; i<=4; i++)
    {
      for (int j=1; j<=4; j++)
      {
        mssmmixing->neunmx(i,j)=to<double>(mySLHA.at("NMIX").at(i,j).at(2));
      }
    }
    // Make NMIX imaginary if mass eigenvalue is negative
    for (int i=1; i<=4; i++)
    {
      for (int j=1; j<=4; j++)
      {
        if (pmasses->mass(DSpart->kn(i)) < 0)
        {
          mssmmixing->neunmx(i,j).im = mssmmixing->neunmx(i,j).re;
          mssmmixing->neunmx(i,j).re = 0.0;
        }
      }
      pmasses->mass(DSpart->kn(i)) = std::abs(pmasses->mass(DSpart->kn(i)));
    }

    // Block UMIX
    for (int i=1; i<=2; i++)
    {
      for (int j=1; j<=2; j++)
      {
        mssmmixing->chaumx(i,j)=to<double>(mySLHA.at("UMIX").at(i,j).at(2));
      }
    }

    // Block VMIX
    for (int i=1; i<=2; i++)
    {
      for (int j=1; j<=2; j++)
      {
        mssmmixing->chavmx(i,j)=to<double>(mySLHA.at("VMIX").at(i,j).at(2));
      }
    }

    // Block ALPHA
    mssmmixing->alpha = to<double>(mySLHA.at("ALPHA").back().at(0));  // Higgs mixing angle

    //If you want to exactly match the DarkSUSY SLHAreader, you should also now run
    //dssuconst_yukawa_running();
    // these settings will be overwritten later, however

    // Block YE, YU, YD - Yukawas
    for (int i=1; i<=3; i++)
    {
      couplingconstants->yukawa(DSpart->kl(i))=to<double>(mySLHA.at("YE").at(i,i).at(2));
      couplingconstants->yukawa(DSpart->kqu(i))=to<double>(mySLHA.at("YU").at(i,i).at(2));
      couplingconstants->yukawa(DSpart->kqd(i))=to<double>(mySLHA.at("YD").at(i,i).at(2));
    }

    // Block MSL2, MSE2, MSQ2, MSU2, MSD2
    for (int i=1; i<=3; i++)
    {
      mssmpar->mass2l(i) = to<double>(mySLHA.at("MSL2").at(i,i).at(2));
      mssmpar->mass2e(i) = to<double>(mySLHA.at("MSE2").at(i,i).at(2));
      mssmpar->mass2q(i) = to<double>(mySLHA.at("MSQ2").at(i,i).at(2));
      mssmpar->mass2u(i) = to<double>(mySLHA.at("MSU2").at(i,i).at(2));
      mssmpar->mass2d(i) = to<double>(mySLHA.at("MSD2").at(i,i).at(2));
    }

    // BLOCK TE, TU and TD. I read these instead of AE, AU, AD.
    for (int i=1; i<=3; i++)
    {
      mssmpar->asofte(i)=to<double>(mySLHA.at("TE").at(i,i).at(2))/couplingconstants->yukawa(DSpart->kl(i));
      mssmpar->asoftu(i)=to<double>(mySLHA.at("TU").at(i,i).at(2))/couplingconstants->yukawa(DSpart->kqu(i));
      mssmpar->asoftd(i)=to<double>(mySLHA.at("TD").at(i,i).at(2))/couplingconstants->yukawa(DSpart->kqd(i));
    }

    // Block SNUMIX
    for (int i=1; i<=3; i++)
    {
      for (int j=1; j<=3; j++)
      {
        mssmmixing->slulmx(i,j) = to<double>(mySLHA.at("SNUMIX").at(i,j).at(2));
      }
    }

    // Block SELMIX
    for (int i=1; i<=6; i++)
    {
      for (int j=1; j<=3; j++)
      {
        mssmmixing->sldlmx(i,j) = to<double>(mySLHA.at("SELMIX").at(i,j).at(2));
        mssmmixing->sldrmx(i,j) = to<double>(mySLHA.at("SELMIX").at(i,j+3).at(2));
      }
    }

    // Block USQMIX
    for (int i=1; i<=6; i++)
    {
      for (int j=1; j<=3; j++)
      {
        mssmmixing->squlmx(i,j) = to<double>(mySLHA.at("USQMIX").at(i,j).at(2));
        mssmmixing->squrmx(i,j) = to<double>(mySLHA.at("USQMIX").at(i,j+3).at(2));
      }
    }

    // Block DSQMIX
    for (int i=1; i<=6; i++)
    {
      for (int j=1; j<=3; j++)
      {
        mssmmixing->sqdlmx(i,j) = to<double>(mySLHA.at("DSQMIX").at(i,j).at(2));
        mssmmixing->sqdrmx(i,j) = to<double>(mySLHA.at("DSQMIX").at(i,j+3).at(2));
      }
    }

    // Do flavour reordering for SLHA2 compatibility
    // NB: This does *not* have to go after the widths are read, as indicated by the comment
    // in the DS 6.1.1 frontend, becasuse dsorder_flavour no longer actually orders the
    // standard mass and width arrays (and instead provides new, 'ordered' particle codes).
    dsorder_flavour();
    // Set up SUSY vertices
    dsvertx();

    // At this point, if you wanted to match the DarkSUSY SLHAreader, you would also call
    // dshigwid();
    // dsspwid();
    // which just fudge a few widths...but we won't do that, because we can get real decay widths from DecayBit.

    // Set up Higgs widths.  h1_0 is the lightest CP even Higgs in GAMBIT (opposite to DS).
    pwidths->width(DSparticle_code("h0_1")) = myDecays.at(std::pair<int,int>(25,0)).width_in_GeV;
    pwidths->width(DSparticle_code("h0_2")) = myDecays.at(std::pair<int,int>(35,0)).width_in_GeV;
    pwidths->width(DSparticle_code("A0"))   = myDecays.at(std::pair<int,int>(36,0)).width_in_GeV;
    pwidths->width(DSparticle_code("H+"))   = myDecays.at(std::pair<int,int>(37,0)).width_in_GeV;

    // Set up Higgs partial widths.
    const static std::vector< std::vector<str> > charged_channels = DS_charged_h_decay_channels();
    const static std::vector< std::vector<str> > neutral_channels = DS_neutral_h_decay_channels();
    const static std::vector<str> sister_chan = initVector<str>("W+", "H-");
    const static std::vector<str> missing_chan = initVector<str>("W-", "H+");
    const DecayTable::Entry& h01 = myDecays.at(std::pair<int,int>(25,0));
    const DecayTable::Entry& h02 = myDecays.at(std::pair<int,int>(35,0));
    const DecayTable::Entry& A0  = myDecays.at(std::pair<int,int>(36,0));
    const DecayTable::Entry& Hpm = myDecays.at(std::pair<int,int>(37,0));
    for (unsigned int i = 0; i < neutral_channels.size(); i++)
    {
      const std::vector<str>& chan = neutral_channels[i];
      mssmwidths->hdwidth(i+1,2) = (h01.has_channel(chan) ? pwidths->width(DSparticle_code("h0_1")) * h01.BF(chan) : 0.0);
      mssmwidths->hdwidth(i+1,1) = (h02.has_channel(chan) ? pwidths->width(DSparticle_code("h0_2")) * h02.BF(chan) : 0.0);
      mssmwidths->hdwidth(i+1,3) = (A0.has_channel(chan)  ? pwidths->width(DSparticle_code("A0"))   * A0.BF(chan)  : 0.0);
      if (neutral_channels[i] == sister_chan)
      {
        // Add the missing W-H+ contributions.
        mssmwidths->hdwidth(i+1,2) = (h01.has_channel(missing_chan) ? pwidths->width(DSparticle_code("h0_1")) * h01.BF(missing_chan) : 0.0);
        mssmwidths->hdwidth(i+1,1) = (h02.has_channel(missing_chan) ? pwidths->width(DSparticle_code("h0_2")) * h02.BF(missing_chan) : 0.0);
        mssmwidths->hdwidth(i+1,3) = (A0.has_channel(missing_chan)  ? pwidths->width(DSparticle_code("A0"))   * A0.BF(missing_chan)  : 0.0);
      }
    }
    for (unsigned int i = 0; i < charged_channels.size(); i++)
    {
      mssmwidths->hdwidth(i+1,4) = (Hpm.has_channel(charged_channels[i]) ? pwidths->width(DSparticle_code("H+")) * Hpm.BF(charged_channels[i]) : 0.0);
    }

    // Set up SM fermion widths
    pwidths->width(DSparticle_code("u_3"))    = myDecays.at(std::pair<int,int>(6,1)).width_in_GeV;
    pwidths->width(DSparticle_code("e-_2"))  = myDecays.at(std::pair<int,int>(13,1)).width_in_GeV;
    pwidths->width(DSparticle_code("e-_3")) = myDecays.at(std::pair<int,int>(15,1)).width_in_GeV;

    // Set up SM gauge boson widths
    pwidths->width(DSparticle_code("W+")) = myDecays.at(std::pair<int,int>(24,0)).width_in_GeV;
    pwidths->width(DSparticle_code("Z0")) = myDecays.at(std::pair<int,int>(23,0)).width_in_GeV;

    // Set up sfermion widths
    pwidths->width(DSpart->ksnu(1)) = myDecays.at(std::pair<int,int>(1000012,0)).width_in_GeV;
    pwidths->width(DSpart->ksnu(2)) = myDecays.at(std::pair<int,int>(1000014,0)).width_in_GeV;
    pwidths->width(DSpart->ksnu(3)) = myDecays.at(std::pair<int,int>(1000016,0)).width_in_GeV;
    pwidths->width(DSpart->ksl(1))  = myDecays.at(std::pair<int,int>(1000011,0)).width_in_GeV;
    pwidths->width(DSpart->ksl(2))  = myDecays.at(std::pair<int,int>(1000013,0)).width_in_GeV;
    pwidths->width(DSpart->ksl(3))  = myDecays.at(std::pair<int,int>(1000015,0)).width_in_GeV;
    pwidths->width(DSpart->ksl(4))  = myDecays.at(std::pair<int,int>(2000011,0)).width_in_GeV;
    pwidths->width(DSpart->ksl(5))  = myDecays.at(std::pair<int,int>(2000013,0)).width_in_GeV;
    pwidths->width(DSpart->ksl(6))  = myDecays.at(std::pair<int,int>(2000015,0)).width_in_GeV;
    pwidths->width(DSpart->ksqu(1)) = myDecays.at(std::pair<int,int>(1000002,0)).width_in_GeV;
    pwidths->width(DSpart->ksqu(2)) = myDecays.at(std::pair<int,int>(1000004,0)).width_in_GeV;
    pwidths->width(DSpart->ksqu(3)) = myDecays.at(std::pair<int,int>(1000006,0)).width_in_GeV;
    pwidths->width(DSpart->ksqu(4)) = myDecays.at(std::pair<int,int>(2000002,0)).width_in_GeV;
    pwidths->width(DSpart->ksqu(5)) = myDecays.at(std::pair<int,int>(2000004,0)).width_in_GeV;
    pwidths->width(DSpart->ksqu(6)) = myDecays.at(std::pair<int,int>(2000006,0)).width_in_GeV;
    pwidths->width(DSpart->ksqd(1)) = myDecays.at(std::pair<int,int>(1000001,0)).width_in_GeV;
    pwidths->width(DSpart->ksqd(2)) = myDecays.at(std::pair<int,int>(1000003,0)).width_in_GeV;
    pwidths->width(DSpart->ksqd(3)) = myDecays.at(std::pair<int,int>(1000005,0)).width_in_GeV;
    pwidths->width(DSpart->ksqd(4)) = myDecays.at(std::pair<int,int>(2000001,0)).width_in_GeV;
    pwidths->width(DSpart->ksqd(5)) = myDecays.at(std::pair<int,int>(2000003,0)).width_in_GeV;
    pwidths->width(DSpart->ksqd(6)) = myDecays.at(std::pair<int,int>(2000005,0)).width_in_GeV;

    // Set up neutralino widths.  Note that the zero neutralino width is taken care of below.
    pwidths->width(DSpart->kn(1)) = myDecays.at(std::pair<int,int>(1000022,0)).width_in_GeV;
    pwidths->width(DSpart->kn(2)) = myDecays.at(std::pair<int,int>(1000023,0)).width_in_GeV;
    pwidths->width(DSpart->kn(3)) = myDecays.at(std::pair<int,int>(1000025,0)).width_in_GeV;
    pwidths->width(DSpart->kn(4)) = myDecays.at(std::pair<int,int>(1000035,0)).width_in_GeV;

    // Set up chargino widths.
    pwidths->width(DSpart->kcha(1)) = myDecays.at(std::pair<int,int>(1000024,0)).width_in_GeV;
    pwidths->width(DSpart->kcha(2)) = myDecays.at(std::pair<int,int>(1000037,0)).width_in_GeV;

    // Gluino width.
    pwidths->width(DSparticle_code("~g")) = myDecays.at(std::pair<int,int>(1000021,0)).width_in_GeV;

    // Gravitino width (not implemented in DS).
    //pwidths->width(DSparticle_code("~G")) = ;

    // Integration routines in DS cannot handle very small sparticle widths.
    // Make sure not to fall below minimal value in order to avoid numerical issues.
    for (std::size_t i=21; i<49; i++)
    {
      if (pwidths->width(i)<min_DS_rwidth *pmasses->mass(i))
      {
        pwidths->width(i)=min_DS_rwidth *pmasses->mass(i);
      }
    }

    #ifdef DARKSUSY_DEBUG
      // Spit out spectrum and width files for debug purposes.
      int u1 = 50;
      int u2 = 100050;
      #ifdef WITH_MPI
        int rank = GMPI::Comm().Get_rank();
        u1 += rank;
        u2 += rank;
      #endif
      dswspectrum(u1);
      dswwidth(u2);
    #endif

    return 0;  // everything OK (hah. maybe. sure.)
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
