//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  MSSM specific module functions for DarkBit.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Torsten Bringmann
///          (torsten.bringmann@desy.de)
///  \date 2013 Jun
///  \date 2014 Mar - 2015 May
///
///  \author Christoph Weniger
///          (c.weniger@uva.nl)
///  \date 2013 Jul - 2015 May
///
///  \author Christopher Savage
///          (chris@savage.name)
///  \date 2014 Oct
///  \date 2015 Jan, Feb
///
///  *********************************************

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/DarkBit/DarkBit_rollcall.hpp"
#include "gambit/DarkBit/DarkBit_utils.hpp"

#include "gambit/Utils/mpiwrapper.hpp"

namespace Gambit
{
  namespace DarkBit
  {

    //////////////////////////////////////////////////////////////////////////
    //
    //                    Backend point initialization
    //
    //////////////////////////////////////////////////////////////////////////

    /*! \brief Fully initialize DarkSUSY to the current model point.
     *
     * Only selected MSSM parameter spaces are implemented.  Returns bool
     * indicating if point initialization was successful, which is essentially
     * always true for models that satisfy the dependency resolver.
     *
     * Supported models: MSSM63atQ
     */
    void DarkSUSY_PointInit_MSSM(bool &result)
    {
      using namespace Pipes::DarkSUSY_PointInit_MSSM;
      result = false;

      // If the user provides a file list, just read in SLHA files for debugging
      // and ignore the MSSM_spectrum dependency.
      if (runOptions->hasKey("debug_SLHA_filenames"))
      {
        static unsigned int counter = 0;
        logger() << LogTags::debug <<
          "Initializing DarkSUSY via debug_SLHA_filenames option." << EOM;

        std::vector<str> filenames =
          /// Option debug_SLHA_filenames<std::vector<std::string>>: Optional override list of SLHA filenames used for backend initialization default
          runOptions->getValue<std::vector<str> >("debug_SLHA_filenames");
        const char * filename = filenames[counter].c_str();
        int len = filenames[counter].length();
        int flag = 15;
        BEreq::dsSLHAread(byVal(filename),flag,byVal(len));
        BEreq::dsprep();

        counter++;
        if (counter >= filenames.size()) counter = 0;
        result = true;
      }

      // CMSSM with DS-internal ISASUGRA (should be avoided, only for
      // debugging)
      else if (ModelInUse("CMSSM") and
      /// Option use_DS_isasugra<bool>: Use DS internal isasugra for parameter running (false)
          runOptions->getValueOrDef<bool>(false, "use_DS_isasugra")
          )
      {
        // Setup mSUGRA model from CMSSM parameters
        double am0    = *Param["M0"];     // m0
        double amhf   = *Param["M12"];    // m_1/2
        double aa0    = *Param["A0"];     // A0
        double asgnmu = *Param["SignMu"];  // sign(mu)
        double atanbe = *Param["TanBeta"];   // tan(beta)
        logger() << "Initializing DarkSUSY via dsgive_model_isasugra:"
          << EOM;
        logger() << "  m0        =" << am0    << std::endl;
        logger() << "  m_1/2     =" << amhf   << std::endl;
        logger() << "  A0        =" << aa0    << std::endl;
        logger() << "  sign(mu)  =" << asgnmu << std::endl;
        logger() << "  tan(beta) =" << atanbe << EOM;
        BEreq::dsgive_model_isasugra(am0, amhf, aa0, asgnmu, atanbe);
        int unphys, hwarning;
        BEreq::dssusy_isasugra(unphys, hwarning);
        //result = (unphys == 0) && (hwarning == 0);
        if (unphys < 0) {
          DarkBit_warning().raise(LOCAL_INFO,
              "Model point is theoretically inconsistent (DarkSUSY).");
          invalid_point().raise(
              "Model point is theoretically inconsistent (DarkSUSY).");
          result = false;
        } else if (unphys > 0) {
          DarkBit_warning().raise(LOCAL_INFO,
              "Neutralino is not the LSP (DarkSUSY).");
          invalid_point().raise("Neutralino is not the LSP (DarkSUSY).");
          result = false;
        } else if (hwarning != 0) {
          DarkBit_warning().raise(LOCAL_INFO,
              "Radiative corrections in Higgs sector "
              "outside range of validity (DarkSUSY).");
          result = true;
        } else {
          result = true;
        }
      }

      else if (ModelInUse("MSSM63atQ") || ModelInUse("CMSSM"))
      {
        SLHAstruct mySLHA;
        /// Option use_dsSLHAread<bool>: Use DS internal SLHA reader to initialize backend (false)
        bool dsSLHAread = runOptions->getValueOrDef<bool>(false, "use_dsSLHAread");
        int slha_version = 2;
        const Spectrum& mySpec = *Dep::MSSM_spectrum;
        try{mySLHA = mySpec.getSLHAea(2);}
        catch(Gambit::exception& e)
        {
            slha_version = 1;
            mySLHA = mySpec.getSLHAea(1);
            dsSLHAread = true;
        }

        // Use an actual SLHA file.  DarkSUSY is on its own wrt (s)particle widths this way.
        if (dsSLHAread || slha_version == 1)
        {
          if (!dsSLHAread) {DarkBit_error().raise(LOCAL_INFO,
                  "A SLHA1 spectrum requires use of the DarkSUSY SLHA reader rather than the diskless\n"
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
          int len = fstr.size();
          int flag = 15;
          const char * filename = fstr.c_str();
          logger() << LogTags::debug << "Initializing DarkSUSY via SLHA." << EOM;
          BEreq::dsSLHAread(byVal(filename),flag,byVal(len));
          BEreq::dsprep();
          result = true;
        }
        // Do pure diskless SLHA initialisation, including (s)particle widths from GAMBIT.
        else
        {
          if ( BEreq::initFromSLHAeaAndDecayTable(mySLHA, *Dep::decay_rates) == 0 )
          {
            logger() << LogTags::debug << "Using diskless SLHA interface to DarkSUSY." << EOM;
            BEreq::dsprep();
            result = true;
          }
        }
      }

      if (!result) {
        DarkBit_warning().raise(LOCAL_INFO,
            "DarkSUSY point initialization failed.");
        invalid_point().raise("DarkSUSY point initialization failed.");
      }
    }


    //////////////////////////////////////////////////////////////////////////
    //
    //      General catalog for annihilation/decay process definition
    //
    //////////////////////////////////////////////////////////////////////////

    /// Wrapper around DarkSUSY kinematic functions
    double DSgamma3bdy(double(*IBfunc)(int&,double&,double&),
        int IBch, double Eg, double
        E1, double M_DM, double m_1, double m_2)
    {
      double E2 = 2*M_DM - Eg - E1;
      double p12 = E1*E1-m_1*m_1;
      double p22 = E2*E2-m_2*m_2;
      double p22min = Eg*Eg+p12-2*Eg*sqrt(p12);
      double p22max = Eg*Eg+p12+2*Eg*sqrt(p12);
      // Check if the process is kinematically allowed
      if((E1 < m_1) || (E2 < m_2) || (p22<p22min) || (p22>p22max))
      {
        return 0;
      }
      double x = Eg/M_DM;  // x = E_gamma/mx
      double y = (m_2*m_2 + 4*M_DM * (M_DM - E2) ) / (4*M_DM*M_DM);
      // Here, y = (p+k)^2/(4 mx^2), where p denotes the W+ momentum and k the
      // photon momentum.  (note that the expressions above and below only
      // apply to the v->0 limit)

      double result = IBfunc(IBch,x,y);

      #ifdef DARKBIT_DEBUG
        std::cout << "  x, y = " << x << ", " << y << std::endl;
        std::cout << "  E, E1, E2 = " << Eg << ", " << E1 << ", "
             << E2 << std::endl;
        std::cout << "  mDM, m1, m2 = " << M_DM << ", " << m_1 << ", "
             << m_2 << std::endl;
        std::cout << "  IBfunc = " << result << std::endl;
      #endif

      // M_DM^-2 is from the Jacobi determinant
      return std::max(0., result) / (M_DM*M_DM);
    }


    /*! \brief Initialization of Process Catalog based on DarkSUSY
     *         calculations.
     */
    void TH_ProcessCatalog_MSSM(DarkBit::TH_ProcessCatalog &result)
    {
      using namespace Pipes::TH_ProcessCatalog_MSSM;
      using std::vector;
      using std::string;

      std::string DMid = *Dep::DarkMatter_ID;
      if ( DMid != "~chi0_1" )
      {
        invalid_point().raise(
            "TH_ProcessCatalog_MSSM requires DMid to be ~chi0_1.");
      }

      // Instantiate new empty ProcessCatalog
      TH_ProcessCatalog catalog;


      ///////////////////////////
      // Import particle masses
      ///////////////////////////

      // Import based on Spectrum objects
      const Spectrum& matched_spectra = *Dep::MSSM_spectrum;
      const SubSpectrum& spec = matched_spectra.get_HE();
      const SubSpectrum& SM   = matched_spectra.get_LE();
      const SMInputs& SMI  = matched_spectra.get_SMInputs();

      // Get SM masses
      #define getSMmass(Name, spinX2)                                         \
        catalog.particleProperties.insert(                                    \
        std::pair<std::string, TH_ParticleProperty>(                          \
        Name , TH_ParticleProperty(SM.get(Par::Pole_Mass,Name), spinX2)));
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
      getSMmass("d_3",      1)
      getSMmass("dbar_3",   1)
      getSMmass("u_3",      1)
      getSMmass("ubar_3",   1)
      #undef getSMmass

      // Pole masses not available for the light quarks.
      #define addParticle(Name, Mass, spinX2)                                 \
        catalog.particleProperties.insert(                                    \
        std::pair<std::string, TH_ParticleProperty>(                          \
        Name , TH_ParticleProperty(Mass, spinX2)));
      addParticle("d_1"   , SMI.mD,  1) // md(2 GeV)^MS-bar, not pole mass
      addParticle("dbar_1", SMI.mD,  1) // md(2 GeV)^MS-bar, not pole mass
      addParticle("u_1"   , SMI.mU,  1) // mu(2 GeV)^MS-bar, not pole mass
      addParticle("ubar_1", SMI.mU,  1) // mu(2 GeV)^MS-bar, not pole mass
      addParticle("d_2"   , SMI.mS,  1) // ms(2 GeV)^MS-bar, not pole mass
      addParticle("dbar_2", SMI.mS,  1) // ms(2 GeV)^MS-bar, not pole mass
      addParticle("u_2"   , SMI.mCmC,1) // mc(mc)^MS-bar, not pole mass
      addParticle("ubar_2", SMI.mCmC,1) // mc(mc)^MS-bar, not pole mass
      // Masses for neutrino flavour eigenstates. Set to zero.
      addParticle("nu_e",     0.0,     1)
      addParticle("nubar_e",  0.0,     1)
      addParticle("nu_mu",    0.0,     1)
      addParticle("nubar_mu", 0.0,     1)
      addParticle("nu_tau",   0.0,     1)
      addParticle("nubar_tau",0.0,     1)

      addParticle("pi0",   meson_masses.pi0,       0)
      addParticle("pi+",   meson_masses.pi_plus,   0)
      addParticle("pi-",   meson_masses.pi_minus,  0)
      addParticle("eta",   meson_masses.eta,       0)
      addParticle("rho0",  meson_masses.rho0,      1)
      addParticle("rho+",  meson_masses.rho_plus,  1)
      addParticle("rho-",  meson_masses.rho_minus, 1)
      addParticle("omega", meson_masses.omega,     1)
      #undef addParticle

      // Get MSSM masses
      #define getMSSMmass(Name, spinX2)                                             \
        catalog.particleProperties.insert(                                          \
        std::pair<std::string, TH_ParticleProperty> (                               \
        Name , TH_ParticleProperty(std::abs(spec.get(Par::Pole_Mass,Name)), spinX2)));
      getMSSMmass("H+"     , 0)
      getMSSMmass("H-"     , 0)
      getMSSMmass("h0_1"   , 0)
      getMSSMmass("h0_2"   , 0)
      getMSSMmass("A0"     , 0)
      getMSSMmass("~chi0_1", 1)
      getMSSMmass("~d_1", 0)
      getMSSMmass("~dbar_1", 0)
      getMSSMmass("~u_1", 0)
      getMSSMmass("~ubar_1", 0)
      getMSSMmass("~d_2", 0)
      getMSSMmass("~dbar_2", 0)
      getMSSMmass("~u_2", 0)
      getMSSMmass("~ubar_2", 0)
      getMSSMmass("~d_3", 0)
      getMSSMmass("~dbar_3", 0)
      getMSSMmass("~u_3", 0)
      getMSSMmass("~ubar_3", 0)
      getMSSMmass("~d_4", 0)
      getMSSMmass("~dbar_4", 0)
      getMSSMmass("~u_4", 0)
      getMSSMmass("~ubar_4", 0)
      getMSSMmass("~d_5", 0)
      getMSSMmass("~dbar_5", 0)
      getMSSMmass("~u_5", 0)
      getMSSMmass("~ubar_5", 0)
      getMSSMmass("~d_6", 0)
      getMSSMmass("~dbar_6", 0)
      getMSSMmass("~u_6", 0)
      getMSSMmass("~ubar_6", 0)
//      getMSSMmass("~e_1", 0)
//      getMSSMmass("~ebar_1", 0)
//      getMSSMmass("~e-_1", 0)
      getMSSMmass("~e+_1", 0)
      getMSSMmass("~e-_1", 0)
      getMSSMmass("~e+_2", 0)
      getMSSMmass("~e-_2", 0)
      getMSSMmass("~e+_3", 0)
      getMSSMmass("~e-_3", 0)
      getMSSMmass("~e+_4", 0)
      getMSSMmass("~e-_4", 0)
      getMSSMmass("~e+_5", 0)
      getMSSMmass("~e-_5", 0)
      getMSSMmass("~e+_6", 0)
      getMSSMmass("~e-_6", 0)
      getMSSMmass("~nu_1", 0)
      getMSSMmass("~nubar_1", 0)
      getMSSMmass("~nu_2", 0)
      getMSSMmass("~nubar_2", 0)
      getMSSMmass("~nu_3", 0)
      getMSSMmass("~nubar_3", 0)

      #undef getMSSMmass


      /////////////////////////////////////////
      // Import two-body annihilation process
      /////////////////////////////////////////

      // Set of possible final state particles. Used to determine which decays to import.
      std::set<string> annFinalStates;

      // Declare DM annihilation process
      TH_Process process(DMid, DMid);
      
      // Explicitly state that Neutralino DM is self-conjugate
      process.isSelfConj = true;
      
      double M_DM = catalog.getParticleProperty(DMid).mass;
      // Helper variables
      int index;
      double m_1, m_2, sv;

      // Macro for setting up 2-body annihilations (chi chi -> X X) from results in DS
      #define SETUP_DS_PROCESS(NAME, PARTCH, P1, P2, PREFACTOR)                  \
        /* Check if process is kinematically allowed */                          \
        m_1 = catalog.getParticleProperty(STRINGIFY(P1)).mass;                   \
        m_2 = catalog.getParticleProperty(STRINGIFY(P2)).mass;                   \
        if(m_1 + m_2 < 2*M_DM)                                                   \
        {                                                                        \
          /* Set cross-section */                                                \
          index = PARTCH;                                                        \
          double CAT(sigma_,NAME) = BEreq::dssigmav(index);                      \
          /* Create associated kinematical functions (just dependent on vrel)    \
           *  here: s-wave, vrel independent 1-dim constant function */          \
          daFunk::Funk CAT(kinematicFunction_,NAME) =                            \
                daFunk::cnst(CAT(sigma_,NAME)*PREFACTOR, "v");                   \
          /* Create channel identifier string */                                 \
          std::vector<std::string> CAT(finalStates_,NAME);                       \
          CAT(finalStates_,NAME).push_back(STRINGIFY(P1));                       \
          CAT(finalStates_,NAME).push_back(STRINGIFY(P2));                       \
          /* Create channel and push it into channel list of process */          \
          TH_Channel CAT(channel_,NAME)(CAT(finalStates_,NAME),                  \
              CAT(kinematicFunction_,NAME));                                     \
          process.channelList.push_back(CAT(channel_,NAME));                     \
          annFinalStates.insert(STRINGIFY(P1));                                  \
          annFinalStates.insert(STRINGIFY(P2));                                  \
        }

      SETUP_DS_PROCESS(H1H1,      1 , h0_2,   h0_2,   1   )
      SETUP_DS_PROCESS(H1H2,      2 , h0_2,   h0_1,   1   )
      SETUP_DS_PROCESS(H2H2,      3 , h0_1,   h0_1,   1   )
      SETUP_DS_PROCESS(H3H3,      4 , A0,     A0,     1   )
      SETUP_DS_PROCESS(H1H3,      5 , h0_2,   A0,     1   )
      SETUP_DS_PROCESS(H2H3,      6 , h0_1,   A0,     1   )
      SETUP_DS_PROCESS(HpHm,      7 , H+,     H-,     1   )
      SETUP_DS_PROCESS(H1Z0,      8 , h0_2,   Z0,     1   )
      SETUP_DS_PROCESS(H2Z0,      9 , h0_1,   Z0,     1   )
      SETUP_DS_PROCESS(H3Z0,      10, A0,     Z0,     1   )
      // Prefactor 0.5 since W+H- and W-H+ are summed in DS
      SETUP_DS_PROCESS(WpHm,      11, W+,     H-,     0.5 )
      SETUP_DS_PROCESS(WmHp,      11, W-,     H+,     0.5 )
      SETUP_DS_PROCESS(Z0Z0,      12, Z0,     Z0,     1   )
      SETUP_DS_PROCESS(WW,        13, W+,     W-,     1   )
      SETUP_DS_PROCESS(nuenue,    14, nu_e,   nubar_e,1   )
      SETUP_DS_PROCESS(ee,        15, e+_1,   e-_1,   1   )
      SETUP_DS_PROCESS(numnum,    16, nu_mu,  nubar_mu,1  )
      SETUP_DS_PROCESS(mumu,      17, e+_2,   e-_2,   1   )
      SETUP_DS_PROCESS(nutnut,    18, nu_tau, nubar_tau,1 )
      SETUP_DS_PROCESS(tautau,    19, e+_3,   e-_3,   1   )
      SETUP_DS_PROCESS(uubar,     20, u_1,    ubar_1,   1   )
      SETUP_DS_PROCESS(ddbar,     21, d_1,    dbar_1,   1   )
      SETUP_DS_PROCESS(ccbar,     22, u_2,    ubar_2,   1   )
      SETUP_DS_PROCESS(ssbar,     23, d_2,    dbar_2,   1   )
      SETUP_DS_PROCESS(ttbar,     24, u_3,    ubar_3,   1   )
      SETUP_DS_PROCESS(bbbar,     25, d_3,    dbar_3,   1   )
      SETUP_DS_PROCESS(gluglu,    26, g,      g,      1   )
      SETUP_DS_PROCESS(gammagamma,28, gamma,  gamma,  1   )
      //        SETUP_DS_PROCESS(Z0gamma,   29, Z0,     gamma,  1   )
      // Undef the macro so it doesn't propagate through GAMBIT
#undef SETUP_DS_PROCESS


      ///////////////////////////////////////////
      // Import three-body annihilation process
      ///////////////////////////////////////////

      using DarkBit_utils::str_flav_to_mass;

      //PS: commented out for now, as this can't be a backend function in its current form.
      //BEreq::registerMassesForIB(catalog.particleProperties);

      // Macro for setting up 3-body decays with gammas
#define SETUP_DS_PROCESS_GAMMA3BODY(NAME,IBCH,P1,P2,IBFUNC,SV_IDX,PREFACTOR) \
      /* Check if process is kinematically allowed */                        \
      m_1 = catalog.getParticleProperty(str_flav_to_mass(STRINGIFY(P1))).mass;                 \
      m_2 = catalog.getParticleProperty(str_flav_to_mass(STRINGIFY(P2))).mass;                 \
      if(m_1 + m_2 < 2*M_DM)                                                 \
      {                                                                      \
        index = SV_IDX;                                                      \
        sv = PREFACTOR*BEreq::dssigmav(index);                               \
        daFunk::Funk CAT(kinematicFunction_,NAME) = daFunk::cnst(sv,"v")*daFunk::func(DSgamma3bdy, \
            STRIP_PARENS(IBFUNC), IBCH, daFunk::var("E"), daFunk::var("E1"),     \
            M_DM, m_1, m_2);                                                 \
        /* Create channel identifier string */                               \
        std::vector<std::string> CAT(finalStates_,NAME);                     \
        CAT(finalStates_,NAME).push_back("gamma");                           \
        CAT(finalStates_,NAME).push_back(str_flav_to_mass(STRINGIFY(P1)));                     \
        CAT(finalStates_,NAME).push_back(str_flav_to_mass(STRINGIFY(P2)));                     \
        /* Create channel and push it into channel list of process */        \
        TH_Channel CAT(channel_,NAME)(CAT(finalStates_,NAME),                \
            CAT(kinematicFunction_,NAME));                                   \
        process.channelList.push_back(CAT(channel_,NAME));                   \
        annFinalStates.insert(str_flav_to_mass(STRINGIFY(P1)));                                \
        annFinalStates.insert(str_flav_to_mass(STRINGIFY(P2)));                                \
      }

      /// Option ignore_three_body<bool>: Ignore three-body final states (default false)
      if ( not runOptions->getValueOrDef<bool>(false, "ignore_three_body") )
      {
        // Set DarkSUSY DM mass parameter used in 3-body decays
        BEreq::IBintvars->ibcom_mx = catalog.getParticleProperty(DMid).mass;

        SETUP_DS_PROCESS_GAMMA3BODY(gammaWW,        1, W+,      W-,
            (BEreq::dsIBwwdxdy.pointer()),  13, 1   )
        // Prefactor 0.5 since W+H- and W-H+ are summed in DS
        SETUP_DS_PROCESS_GAMMA3BODY(gammaWpHm,      2, W+,      H-,
            (BEreq::dsIBwhdxdy.pointer()),  11, 0.5 )
        // Prefactor 0.5 since W+H- and W-H+ are summed in DS
        SETUP_DS_PROCESS_GAMMA3BODY(gammaWmHp,      2, W-,      H+,
            (BEreq::dsIBwhdxdy.pointer()),  11, 0.5 )
        SETUP_DS_PROCESS_GAMMA3BODY(gammaHpHm,      3, H+,      H-,
            (BEreq::dsIBhhdxdy.pointer()),  0,  1   )
        SETUP_DS_PROCESS_GAMMA3BODY(gammaee,        4, e+,      e-,
            (BEreq::dsIBffdxdy.pointer()) , 15, 1   )
        SETUP_DS_PROCESS_GAMMA3BODY(gammamumu,      5, mu+,     mu-,
            (BEreq::dsIBffdxdy.pointer()) , 17, 1   )
        SETUP_DS_PROCESS_GAMMA3BODY(gammatautau,    6, tau+,    tau-,
            (BEreq::dsIBffdxdy.pointer()) , 19, 1   )
        SETUP_DS_PROCESS_GAMMA3BODY(gammauubar,     7, u,       ubar,
            (BEreq::dsIBffdxdy.pointer()) , 20, 1   )
        SETUP_DS_PROCESS_GAMMA3BODY(gammaddbar,     8, d,       dbar,
            (BEreq::dsIBffdxdy.pointer()) , 21, 1   )
        SETUP_DS_PROCESS_GAMMA3BODY(gammaccbar,     9, c,       cbar,
            (BEreq::dsIBffdxdy.pointer()) , 22, 1   )
        SETUP_DS_PROCESS_GAMMA3BODY(gammassbar,     10,s,       sbar,
            (BEreq::dsIBffdxdy.pointer()) , 23, 1   )
        SETUP_DS_PROCESS_GAMMA3BODY(gammattbar,     11,t,       tbar,
            (BEreq::dsIBffdxdy.pointer()) , 24, 1   )
        SETUP_DS_PROCESS_GAMMA3BODY(gammabbbar,     12,b,       bbar,
            (BEreq::dsIBffdxdy.pointer()) , 25, 1   )
      }
#undef SETUP_DS_PROCESS_GAMMA3BODY


      /////////////////////////////
      // Import Decay information
      /////////////////////////////

      // Import based on decay table from DecayBit
      const DecayTable* tbl = &(*Dep::decay_rates);

      // Set of imported decays - avoids double imports
      std::set<string> importedDecays;

      // Option minBranching <double>: Minimum branching fraction of included
      // processes (default 0.)
      double minBranching = runOptions->getValueOrDef<double>(0.0,
          "ProcessCatalog_MinBranching");

      // Exclude also ttbar final states
      auto excludeDecays = daFunk::vec<std::string>("Z0", "W+", "W-", "u_3", "ubar_3", "e+_2", "e-_2", "e+_3", "e-_3");

      // Import relevant decays
      using DarkBit_utils::ImportDecays;
      if(annFinalStates.count("H+") == 1)
        ImportDecays("H+", catalog, importedDecays, tbl, minBranching, excludeDecays);
      if(annFinalStates.count("H-") == 1)
        ImportDecays("H-", catalog, importedDecays, tbl, minBranching, excludeDecays);
      if(annFinalStates.count("h0_1") == 1)
        ImportDecays("h0_1", catalog, importedDecays, tbl, minBranching, excludeDecays);
      if(annFinalStates.count("h0_2") == 1)
        ImportDecays("h0_2", catalog, importedDecays, tbl, minBranching, excludeDecays);
      if(annFinalStates.count("A0") == 1)
        ImportDecays("A0", catalog, importedDecays, tbl, minBranching, excludeDecays);

      // Add process to provess list
      catalog.processList.push_back(process);

      // Validate
      catalog.validate();

      // Return the finished process catalog
      result = catalog;
    }

    void DarkMatter_ID_MSSM(std::string & result)
    {
      using namespace Pipes::DarkMatter_ID_MSSM;
      // TODO: need ask Dep::MSSM_spectrum in future; might have sneutralinos and gravitinos later.
      result = "~chi0_1";
    }
  }
}
