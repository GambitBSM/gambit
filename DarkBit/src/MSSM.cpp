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
///  \date 2019 May (removed DarkSUSY_PointInit_MSSM, added TH_ProcessCatalog_DS_MSSM)
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


    /*! \brief Initialization of Process Catalog based on DarkSUSY 5
     *         calculations.
     */
    void TH_ProcessCatalog_DS5_MSSM(DarkBit::TH_ProcessCatalog &result)
    {
      using namespace Pipes::TH_ProcessCatalog_DS5_MSSM;
      using std::vector;
      using std::string;

      std::string DMid = *Dep::DarkMatter_ID;
      if ( DMid != "~chi0_1" )
      {
        invalid_point().raise(
            "TH_ProcessCatalog_DS5_MSSM requires DMid to be ~chi0_1.");
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
      auto getSMmass = [&](str Name, int spinX2)
      {
        catalog.particleProperties.insert(
        std::pair<std::string, TH_ParticleProperty>(
         Name , TH_ParticleProperty(SM.get(Par::Pole_Mass,Name), spinX2)));
      };

      getSMmass("e-_1",     1);
      getSMmass("e+_1",     1);
      getSMmass("e-_2",     1);
      getSMmass("e+_2",     1);
      getSMmass("e-_3",     1);
      getSMmass("e+_3",     1);
      getSMmass("Z0",       2);
      getSMmass("W+",       2);
      getSMmass("W-",       2);
      getSMmass("g",        2);
      getSMmass("gamma",    2);
      getSMmass("d_3",      1);
      getSMmass("dbar_3",   1);
      getSMmass("u_3",      1);
      getSMmass("ubar_3",   1);

      // Pole masses not available for the light quarks.
      auto addParticle = [&](str Name, double Mass, int spinX2)
      {
        catalog.particleProperties.insert(
        std::pair<std::string, TH_ParticleProperty>(
         Name , TH_ParticleProperty(Mass, spinX2)));
      };

      addParticle("d_1"   , SMI.mD,  1); // md(2 GeV)^MS-bar, not pole mass
      addParticle("dbar_1", SMI.mD,  1); // md(2 GeV)^MS-bar, not pole mass
      addParticle("u_1"   , SMI.mU,  1); // mu(2 GeV)^MS-bar, not pole mass
      addParticle("ubar_1", SMI.mU,  1); // mu(2 GeV)^MS-bar, not pole mass
      addParticle("d_2"   , SMI.mS,  1); // ms(2 GeV)^MS-bar, not pole mass
      addParticle("dbar_2", SMI.mS,  1); // ms(2 GeV)^MS-bar, not pole mass
      addParticle("u_2"   , SMI.mCmC,1); // mc(mc)^MS-bar, not pole mass
      addParticle("ubar_2", SMI.mCmC,1); // mc(mc)^MS-bar, not pole mass
      // Masses for neutrino flavour eigenstates. Set to zero.
      addParticle("nu_e",     0.0,     1);
      addParticle("nubar_e",  0.0,     1);
      addParticle("nu_mu",    0.0,     1);
      addParticle("nubar_mu", 0.0,     1);
      addParticle("nu_tau",   0.0,     1);
      addParticle("nubar_tau",0.0,     1);

      addParticle("pi0",   meson_masses.pi0,       0);
      addParticle("pi+",   meson_masses.pi_plus,   0);
      addParticle("pi-",   meson_masses.pi_minus,  0);
      addParticle("eta",   meson_masses.eta,       0);
      addParticle("rho0",  meson_masses.rho0,      1);
      addParticle("rho+",  meson_masses.rho_plus,  1);
      addParticle("rho-",  meson_masses.rho_minus, 1);
      addParticle("omega", meson_masses.omega,     1);


      // Get MSSM masses
      auto getMSSMmass = [&](str Name, int spinX2)
      {
        catalog.particleProperties.insert(
        std::pair<std::string, TH_ParticleProperty> (
         Name , TH_ParticleProperty(std::abs(spec.get(Par::Pole_Mass,Name)), spinX2)));
      };

      getMSSMmass("H+"      , 0);
      getMSSMmass("H-"      , 0);
      getMSSMmass("h0_1"    , 0);
      getMSSMmass("h0_2"    , 0);
      getMSSMmass("A0"      , 0);
      getMSSMmass("~chi0_1" , 1);
      getMSSMmass("~d_1"    , 0);
      getMSSMmass("~dbar_1" , 0);
      getMSSMmass("~u_1"    , 0);
      getMSSMmass("~ubar_1" , 0);
      getMSSMmass("~d_2"    , 0);
      getMSSMmass("~dbar_2" , 0);
      getMSSMmass("~u_2"    , 0);
      getMSSMmass("~ubar_2" , 0);
      getMSSMmass("~d_3"    , 0);
      getMSSMmass("~dbar_3" , 0);
      getMSSMmass("~u_3"    , 0);
      getMSSMmass("~ubar_3" , 0);
      getMSSMmass("~d_4"    , 0);
      getMSSMmass("~dbar_4" , 0);
      getMSSMmass("~u_4"    , 0);
      getMSSMmass("~ubar_4" , 0);
      getMSSMmass("~d_5"    , 0);
      getMSSMmass("~dbar_5" , 0);
      getMSSMmass("~u_5"    , 0);
      getMSSMmass("~ubar_5" , 0);
      getMSSMmass("~d_6"    , 0);
      getMSSMmass("~dbar_6" , 0);
      getMSSMmass("~u_6"    , 0);
      getMSSMmass("~ubar_6" , 0);
      //getMSSMmass("~e_1"    , 0);
      //getMSSMmass("~ebar_1" , 0);
      //getMSSMmass("~e-_1"   , 0);
      getMSSMmass("~e+_1"   , 0);
      getMSSMmass("~e-_1"   , 0);
      getMSSMmass("~e+_2"   , 0);
      getMSSMmass("~e-_2"   , 0);
      getMSSMmass("~e+_3"   , 0);
      getMSSMmass("~e-_3"   , 0);
      getMSSMmass("~e+_4"   , 0);
      getMSSMmass("~e-_4"   , 0);
      getMSSMmass("~e+_5"   , 0);
      getMSSMmass("~e-_5"   , 0);
      getMSSMmass("~e+_6"   , 0);
      getMSSMmass("~e-_6"   , 0);
      getMSSMmass("~nu_1"   , 0);
      getMSSMmass("~nubar_1", 0);
      getMSSMmass("~nu_2"   , 0);
      getMSSMmass("~nubar_2", 0);
      getMSSMmass("~nu_3"   , 0);
      getMSSMmass("~nubar_3", 0);


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

      // lambda for setting up 2-body annihilations (chi chi -> X X) from results in DS
      auto setup_ds_process = [&](int index, str p1, str p2, double prefac)
      {
        /* Check if process is kinematically allowed */
        double m_1 = catalog.getParticleProperty(p1).mass;
        double m_2 = catalog.getParticleProperty(p2).mass;
        if(m_1 + m_2 < 2*M_DM)
        {
          /* Set cross-section */
          double sigma = BEreq::dssigmav(index);
          /* Create associated kinematical functions (just dependent on vrel)
           *  here: s-wave, vrel independent 1-dim constant function */
          daFunk::Funk kinematicFunction = daFunk::cnst(sigma*prefac, "v");
          /* Create channel identifier string */
          std::vector<std::string> finalStates;
          finalStates.push_back(p1);
          finalStates.push_back(p2);
          /* Create channel and push it into channel list of process */
          process.channelList.push_back(TH_Channel(finalStates, kinematicFunction));
          annFinalStates.insert(p1);
          annFinalStates.insert(p1);
        }
      };

      setup_ds_process(1 , "h0_2",   "h0_2",   1   );
      setup_ds_process(2 , "h0_2",   "h0_1",   1   );
      setup_ds_process(3 , "h0_1",   "h0_1",   1   );
      setup_ds_process(4 , "A0",     "A0",     1   );
      setup_ds_process(5 , "h0_2",   "A0",     1   );
      setup_ds_process(6 , "h0_1",   "A0",     1   );
      setup_ds_process(7 , "H+",     "H-",     1   );
      setup_ds_process(8 , "h0_2",   "Z0",     1   );
      setup_ds_process(9 , "h0_1",   "Z0",     1   );
      setup_ds_process(10, "A0",     "Z0",     1   );
      // Prefactor 0.5 since W+H- and W-H+ are summed in DS
      setup_ds_process(11, "W+",     "H-",     0.5 );
      setup_ds_process(11, "W-",     "H+",     0.5 );
      setup_ds_process(12, "Z0",     "Z0",     1   );
      setup_ds_process(13, "W+",     "W-",     1   );
      setup_ds_process(14, "nu_e",   "nubar_e",1   );
      setup_ds_process(15, "e+_1",   "e-_1",   1   );
      setup_ds_process(16, "nu_mu",  "nubar_mu",1  );
      setup_ds_process(17, "e+_2",   "e-_2",   1   );
      setup_ds_process(18, "nu_tau", "nubar_tau",1 );
      setup_ds_process(19, "e+_3",   "e-_3",   1   );
      setup_ds_process(20, "u_1",    "ubar_1", 1   );
      setup_ds_process(21, "d_1",    "dbar_1", 1   );
      setup_ds_process(22, "u_2",    "ubar_2", 1   );
      setup_ds_process(23, "d_2",    "dbar_2", 1   );
      setup_ds_process(24, "u_3",    "ubar_3", 1   );
      setup_ds_process(25, "d_3",    "dbar_3", 1   );
      setup_ds_process(26, "g",      "g",      1   );
      setup_ds_process(28, "gamma",  "gamma",  1   );
      //        setup_ds_process(29, "Z0",     gamma,  1   );


      ///////////////////////////////////////////
      // Import three-body annihilation process
      ///////////////////////////////////////////

      using DarkBit_utils::str_flav_to_mass;

      // lambda for setting up 3-body decays with gammas
      auto setup_ds_process_gamma3body = [&](int IBch, str p1, str p2, double (*IBfunc)(int&, double&, double&), int index, double prefac)
      {
        /* Check if process is kinematically allowed */
        double m_1 = catalog.getParticleProperty(str_flav_to_mass(p1)).mass;
        double m_2 = catalog.getParticleProperty(str_flav_to_mass(p2)).mass;
        if(m_1 + m_2 < 2*M_DM)
        {
          double sv = prefac*BEreq::dssigmav(index);
          daFunk::Funk kinematicFunction =
            daFunk::cnst(sv,"v")*daFunk::func(DSgamma3bdy,
            IBfunc, IBch, daFunk::var("E"), daFunk::var("E1"),
            M_DM, m_1, m_2);
          /* Create channel identifier string */
          std::vector<std::string> finalStates;
          finalStates.push_back("gamma");
          finalStates.push_back(str_flav_to_mass(p1));
          finalStates.push_back(str_flav_to_mass(p2));
          /* Create channel and push it into channel list of process */
          process.channelList.push_back(TH_Channel(finalStates, kinematicFunction));
          annFinalStates.insert(str_flav_to_mass(p1));
          annFinalStates.insert(str_flav_to_mass(p2));
        };
      };

      /// Option ignore_three_body<bool>: Ignore three-body final states (default false)
      if ( not runOptions->getValueOrDef<bool>(false, "ignore_three_body") )
      {
        // Set DarkSUSY DM mass parameter used in 3-body decays
        BEreq::IBintvars->ibcom_mx = catalog.getParticleProperty(DMid).mass;

        setup_ds_process_gamma3body(1,  "W+",      "W-",   BEreq::dsIBwwdxdy.pointer(), 13, 1  );
        // Prefactor 0.5 since W+H- and W-H+ are summed in DS
        setup_ds_process_gamma3body(2,  "W+",      "H-",   BEreq::dsIBwhdxdy.pointer(), 11, 0.5);
        // Prefactor 0.5 since W+H- and W-H+ are summed in DS
        setup_ds_process_gamma3body(2,  "W-",      "H+",   BEreq::dsIBwhdxdy.pointer(), 11, 0.5);
        setup_ds_process_gamma3body(3,  "H+",      "H-",   BEreq::dsIBhhdxdy.pointer(),  0, 1  );
        setup_ds_process_gamma3body(4,  "e+",      "e-",   BEreq::dsIBffdxdy.pointer(), 15, 1  );
        setup_ds_process_gamma3body(5,  "mu+",     "mu-",  BEreq::dsIBffdxdy.pointer(), 17, 1  );
        setup_ds_process_gamma3body(6,  "tau+",    "tau-", BEreq::dsIBffdxdy.pointer(), 19, 1  );
        setup_ds_process_gamma3body(7,  "u",       "ubar", BEreq::dsIBffdxdy.pointer(), 20, 1  );
        setup_ds_process_gamma3body(8,  "d",       "dbar", BEreq::dsIBffdxdy.pointer(), 21, 1  );
        setup_ds_process_gamma3body(9,  "c",       "cbar", BEreq::dsIBffdxdy.pointer(), 22, 1  );
        setup_ds_process_gamma3body(10, "s",       "sbar", BEreq::dsIBffdxdy.pointer(), 23, 1  );
        setup_ds_process_gamma3body(11, "t",       "tbar", BEreq::dsIBffdxdy.pointer(), 24, 1  );
        setup_ds_process_gamma3body(12, "b",       "bbar", BEreq::dsIBffdxdy.pointer(), 25, 1  );
      };


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

      // Add process to process list
      catalog.processList.push_back(process);

      // Validate
      catalog.validate();

      // Return the finished process catalog
      result = catalog;
    }


    /*! \brief Initialization of Process Catalog based on DarkSUSY 6
     *         calculations.
     */
    void TH_ProcessCatalog_DS_MSSM(DarkBit::TH_ProcessCatalog &result)
    {
      using namespace Pipes::TH_ProcessCatalog_DS_MSSM;
      using std::vector;
      using std::string;

      std::string DMid = *Dep::DarkMatter_ID;
      if ( DMid != "~chi0_1" )
      {
        invalid_point().raise(
            "TH_ProcessCatalog_DS_MSSM requires DMid to be ~chi0_1.");
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
      auto getSMmass = [&](str Name, int spinX2)
      {
        catalog.particleProperties.insert(
        std::pair<std::string, TH_ParticleProperty>(
         Name , TH_ParticleProperty(SM.get(Par::Pole_Mass,Name), spinX2)));
      };

      getSMmass("e-_1",     1);
      getSMmass("e+_1",     1);
      getSMmass("e-_2",     1);
      getSMmass("e+_2",     1);
      getSMmass("e-_3",     1);
      getSMmass("e+_3",     1);
      getSMmass("Z0",       2);
      getSMmass("W+",       2);
      getSMmass("W-",       2);
      getSMmass("g",        2);
      getSMmass("gamma",    2);
      getSMmass("d_3",      1);
      getSMmass("dbar_3",   1);
      getSMmass("u_3",      1);
      getSMmass("ubar_3",   1);

      // Pole masses not available for the light quarks.
      auto addParticle = [&](str Name, double Mass, int spinX2)
      {
        catalog.particleProperties.insert(
        std::pair<std::string, TH_ParticleProperty>(
         Name , TH_ParticleProperty(Mass, spinX2)));
      };

      addParticle("d_1"   , SMI.mD,  1); // md(2 GeV)^MS-bar, not pole mass
      addParticle("dbar_1", SMI.mD,  1); // md(2 GeV)^MS-bar, not pole mass
      addParticle("u_1"   , SMI.mU,  1); // mu(2 GeV)^MS-bar, not pole mass
      addParticle("ubar_1", SMI.mU,  1); // mu(2 GeV)^MS-bar, not pole mass
      addParticle("d_2"   , SMI.mS,  1); // ms(2 GeV)^MS-bar, not pole mass
      addParticle("dbar_2", SMI.mS,  1); // ms(2 GeV)^MS-bar, not pole mass
      addParticle("u_2"   , SMI.mCmC,1); // mc(mc)^MS-bar, not pole mass
      addParticle("ubar_2", SMI.mCmC,1); // mc(mc)^MS-bar, not pole mass
      // Masses for neutrino flavour eigenstates. Set to zero.
      addParticle("nu_e",     0.0,     1);
      addParticle("nubar_e",  0.0,     1);
      addParticle("nu_mu",    0.0,     1);
      addParticle("nubar_mu", 0.0,     1);
      addParticle("nu_tau",   0.0,     1);
      addParticle("nubar_tau",0.0,     1);

      addParticle("pi0",   meson_masses.pi0,       0);
      addParticle("pi+",   meson_masses.pi_plus,   0);
      addParticle("pi-",   meson_masses.pi_minus,  0);
      addParticle("eta",   meson_masses.eta,       0);
      addParticle("rho0",  meson_masses.rho0,      1);
      addParticle("rho+",  meson_masses.rho_plus,  1);
      addParticle("rho-",  meson_masses.rho_minus, 1);
      addParticle("omega", meson_masses.omega,     1);

      // Get MSSM masses
      auto getMSSMmass = [&](str Name, int spinX2)
      {
        catalog.particleProperties.insert(
        std::pair<std::string, TH_ParticleProperty>(
         Name , TH_ParticleProperty(std::abs(spec.get(Par::Pole_Mass,Name)), spinX2)));
      };

      getMSSMmass("H+"      , 0);
      getMSSMmass("H-"      , 0);
      getMSSMmass("h0_1"    , 0);
      getMSSMmass("h0_2"    , 0);
      getMSSMmass("A0"      , 0);
      getMSSMmass("~chi0_1" , 1);
      getMSSMmass("~d_1"    , 0);
      getMSSMmass("~dbar_1" , 0);
      getMSSMmass("~u_1"    , 0);
      getMSSMmass("~ubar_1" , 0);
      getMSSMmass("~d_2"    , 0);
      getMSSMmass("~dbar_2" , 0);
      getMSSMmass("~u_2"    , 0);
      getMSSMmass("~ubar_2" , 0);
      getMSSMmass("~d_3"    , 0);
      getMSSMmass("~dbar_3" , 0);
      getMSSMmass("~u_3"    , 0);
      getMSSMmass("~ubar_3" , 0);
      getMSSMmass("~d_4"    , 0);
      getMSSMmass("~dbar_4" , 0);
      getMSSMmass("~u_4"    , 0);
      getMSSMmass("~ubar_4" , 0);
      getMSSMmass("~d_5"    , 0);
      getMSSMmass("~dbar_5" , 0);
      getMSSMmass("~u_5"    , 0);
      getMSSMmass("~ubar_5" , 0);
      getMSSMmass("~d_6"    , 0);
      getMSSMmass("~dbar_6" , 0);
      getMSSMmass("~u_6"    , 0);
      getMSSMmass("~ubar_6" , 0);
      //getMSSMmass("~e_1"    , 0);
      //getMSSMmass("~ebar_1" , 0);
      //getMSSMmass("~e-_1"   , 0);
      getMSSMmass("~e+_1"   , 0);
      getMSSMmass("~e-_1"   , 0);
      getMSSMmass("~e+_2"   , 0);
      getMSSMmass("~e-_2"   , 0);
      getMSSMmass("~e+_3"   , 0);
      getMSSMmass("~e-_3"   , 0);
      getMSSMmass("~e+_4"   , 0);
      getMSSMmass("~e-_4"   , 0);
      getMSSMmass("~e+_5"   , 0);
      getMSSMmass("~e-_5"   , 0);
      getMSSMmass("~e+_6"   , 0);
      getMSSMmass("~e-_6"   , 0);
      getMSSMmass("~nu_1"   , 0);
      getMSSMmass("~nubar_1", 0);
      getMSSMmass("~nu_2"   , 0);
      getMSSMmass("~nubar_2", 0);
      getMSSMmass("~nu_3"   , 0);
      getMSSMmass("~nubar_3", 0);

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

      // lambda for setting up 2-body annihilations (chi chi -> X X) from results in DS
      auto setup_DS6_process = [&](int pdg1, int pdg2, str p1, str p2, double prefac)
      {
        /* Check if process is kinematically allowed */
        double m_1 = catalog.getParticleProperty(p1).mass;
        double m_2 = catalog.getParticleProperty(p2).mass;
        if(m_1 + m_2 < 2*M_DM)
        {
          /* Set cross-section */
          double sigma = BEreq::dssigmav0(pdg1,pdg2);
          /* Create associated kinematical functions (just dependent on vrel)
           *  here: s-wave, vrel independent 1-dim constant function */
          daFunk::Funk kinematicFunction = daFunk::cnst(sigma*prefac, "v");
          /* Create channel identifier string */
          std::vector<std::string> finalStates;
          finalStates.push_back(p1);
          finalStates.push_back(p2);
          /* Create channel and push it into channel list of process */
          process.channelList.push_back(TH_Channel(finalStates, kinematicFunction));
          annFinalStates.insert(p1);
          annFinalStates.insert(p2);
        }
      };

      setup_DS6_process( 35,  35, "h0_2",   "h0_2",   1   );
      setup_DS6_process( 35,  25, "h0_2",   "h0_1",   1   );
      setup_DS6_process( 25,  25, "h0_1",   "h0_1",   1   );
      setup_DS6_process( 36,  36, "A0",     "A0",     1   );
      setup_DS6_process( 35,  36, "h0_2",   "A0",     1   );
      setup_DS6_process( 25,  36, "h0_1",   "A0",     1   );
      setup_DS6_process( 37, -37, "H+",     "H-",     1   );
      setup_DS6_process( 35,  23, "h0_2",   "Z0",     1   );
      setup_DS6_process( 25,  23, "h0_1",   "Z0",     1   );
      setup_DS6_process( 36,  23, "A0",     "Z0",     1   );
      // Prefactor 0.5 since W+H- and W-H+ are summed in DS
      setup_DS6_process( 24, -37, "W+",     "H-",     0.5 );
      setup_DS6_process(-24,  37, "W-",     "H+",     0.5 );
      setup_DS6_process( 23,  23, "Z0",     "Z0",     1   );
      setup_DS6_process( 24, -24, "W+",     "W-",     1   );
      setup_DS6_process( 12, -12, "nu_e",   "nubar_e",1   );
      setup_DS6_process( 11, -11, "e+_1",   "e-_1",   1   );
      setup_DS6_process( 14, -14, "nu_mu",  "nubar_mu",1  );
      setup_DS6_process( 13, -13, "e+_2",   "e-_2",   1   );
      setup_DS6_process( 16, -16, "nu_tau", "nubar_tau",1 );
      setup_DS6_process( 15, -15, "e+_3",   "e-_3",   1   );
      setup_DS6_process(  2, - 2, "u_1",    "ubar_1", 1   );
      setup_DS6_process(  1, - 1, "d_1",    "dbar_1", 1   );
      setup_DS6_process(  4, - 4, "u_2",    "ubar_2", 1   );
      setup_DS6_process(  3, - 3, "d_2",    "dbar_2", 1   );
      setup_DS6_process(  6, - 6, "u_3",    "ubar_3", 1   );
      setup_DS6_process(  5, - 5, "d_3",    "dbar_3", 1   );
      setup_DS6_process( 21,  21, "g",      "g",      1   );
      setup_DS6_process( 22,  22, "gamma",  "gamma",  1   );
      setup_DS6_process( 23,  22, "Z0",     "gamma",  1   );


      ///////////////////////////////////////////
      // Import three-body annihilation process
      ///////////////////////////////////////////

      using DarkBit_utils::str_flav_to_mass;

      //PS: commented out for now, as this can't be a backend function in its current form.
      //BEreq::registerMassesForIB(catalog.particleProperties);

      // Macro for setting up 3-body decays with gammas

      auto setup_DS6_process_gamma3body = [&](int IBch, str p1, str p2, double (*IBfunc)(int&, double&, double&), int sv_pdg1, int sv_pdg2, double prefac)
      {
        /* Check if process is kinematically allowed */
        double m_1 = catalog.getParticleProperty(str_flav_to_mass(p1)).mass;
        double m_2 = catalog.getParticleProperty(str_flav_to_mass(p2)).mass;
        if(m_1 + m_2 < 2*M_DM)
        {
          double sv;
          if(sv_pdg1==0 && sv_pdg2==0)
          {
            sv = prefac*BEreq::dssigmav0tot();
          }
          else
          {
            sv = prefac*BEreq::dssigmav0(sv_pdg1,sv_pdg2);
          }
          daFunk::Funk kinematicFunction = daFunk::cnst(sv,"v")*daFunk::func(DSgamma3bdy,
           IBfunc, IBch, daFunk::var("E"), daFunk::var("E1"), M_DM, m_1, m_2);
          /* Create channel identifier string */
          std::vector<std::string> finalStates;
          finalStates.push_back("gamma");
          finalStates.push_back(str_flav_to_mass(p1));
          finalStates.push_back(str_flav_to_mass(p2));
          /* Create channel and push it into channel list of process */
          process.channelList.push_back(TH_Channel(finalStates, kinematicFunction));
          annFinalStates.insert(str_flav_to_mass(p1));
          annFinalStates.insert(str_flav_to_mass(p2));
        }
      };

      /// Option ignore_three_body<bool>: Ignore three-body final states (default false)
      if ( not runOptions->getValueOrDef<bool>(false, "ignore_three_body") )
      {
        // Set DarkSUSY DM mass parameter used in 3-body decays
        BEreq::IBintvars->ibcom_mx = catalog.getParticleProperty(DMid).mass;

        setup_DS6_process_gamma3body( 1, "W+",  "W-",  BEreq::dsIBwwdxdy.pointer(),24, -24, 1  );
        // Prefactor 0.5 since W+H- and W-H+ are summed in DS
        setup_DS6_process_gamma3body( 2, "W+",  "H-",  BEreq::dsIBwhdxdy.pointer(),24, -37, 0.5);
        // Prefactor 0.5 since W+H- and W-H+ are summed in DS
        setup_DS6_process_gamma3body( 2, "W-",  "H+",  BEreq::dsIBwhdxdy.pointer(),37, -24, 0.5);
        setup_DS6_process_gamma3body( 3, "H+",  "H-",  BEreq::dsIBhhdxdy.pointer(), 0,   0, 1  );

        setup_DS6_process_gamma3body( 4, "e+",  "e-",  BEreq::dsIBffdxdy.pointer(),11, -11, 1  );
        setup_DS6_process_gamma3body( 5, "mu+", "mu-", BEreq::dsIBffdxdy.pointer(),13, -13, 1  );
        setup_DS6_process_gamma3body( 6, "tau+","tau-",BEreq::dsIBffdxdy.pointer(),15, -15, 1  );
        setup_DS6_process_gamma3body( 7, "u",   "ubar",BEreq::dsIBffdxdy.pointer(), 2,  -2, 1  );
        setup_DS6_process_gamma3body( 8, "d",   "dbar",BEreq::dsIBffdxdy.pointer(), 1,  -1, 1  );
        setup_DS6_process_gamma3body( 9, "c",   "cbar",BEreq::dsIBffdxdy.pointer(), 4,  -4, 1  );
        setup_DS6_process_gamma3body(10,"s",    "sbar",BEreq::dsIBffdxdy.pointer(), 3,  -3, 1  );
        setup_DS6_process_gamma3body(11,"t",    "tbar",BEreq::dsIBffdxdy.pointer(), 6,  -6, 1  );
        setup_DS6_process_gamma3body(12,"b",    "bbar",BEreq::dsIBffdxdy.pointer(), 5,  -5, 1  );
      };


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


      // Add process to process list
      catalog.processList.push_back(process);

      // Validate
      catalog.validate();

      // Return the finished process catalog
      result = catalog;
    } //TH_ProcessCatalog_DS_MSSM



    void DarkMatter_ID_MSSM(std::string & result)
    {
      using namespace Pipes::DarkMatter_ID_MSSM;
      // TODO: need ask Dep::MSSM_spectrum in future; might have sneutralinos and gravitinos later.
      result = "~chi0_1";
    }
  }
}
