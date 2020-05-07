//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Solar neutrino likelihoods.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (pscott@imperial.ac.uk)
///  \date 2015 Apr
///        2018 Sep
///
///  \author Sebastian Wild
///          (sebastian.wild@ph.tum.de)
///  \date 2016 Aug
///
///  \author Ankit Beniwal
///          (ankit.beniwal@adelaide.edu.au)
///  \date 2018 Jan, Aug
///
///  *********************************************

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/DarkBit/DarkBit_rollcall.hpp"
#include "gambit/DarkBit/DarkBit_utils.hpp"

//#define DARKBIT_DEBUG

namespace Gambit
{

  namespace DarkBit
  {
 
    //////////////////////////////////////////////////////////////////////////
    //
    //            Neutrino telescope likelihoods and observables
    //
    //////////////////////////////////////////////////////////////////////////

    /*! \brief Capture rate of regular dark matter in the Sun (no v-dependent
     *         or q-dependent cross-sections) (s^-1).
     */
    void capture_rate_Sun_const_xsec(double &result)
    {
      using namespace Pipes::capture_rate_Sun_const_xsec;

      if (BEreq::cap_Sun_v0q0_isoscalar.origin()=="DarkSUSY")
        if(!(*Dep::DarkSUSY_PointInit_LocalHalo))
          DarkBit_error().raise(LOCAL_INFO,"DarkSUSY halo model not initialized!");

      // When calculating the solar capture rate, DarkSUSY assumes that the
      // proton and neutron scattering cross-sections are the same; we
      // assume that whichever backend has been hooked up here does so too.
      result = BEreq::cap_Sun_v0q0_isoscalar(
          *Dep::mwimp, *Dep::sigma_SI_p, *Dep::sigma_SD_p);

      //cout << "mwimp" << *Dep::mwimp << "sigma_SI_p: " << *Dep::sigma_SI_p << " sigma_SD_p: " << *Dep::sigma_SD_p << "result: " << result << "\n";
      //cout << "capture rate via capture_rate_Sun_const_xsec = " << result << "\n";

    }

    ///Alternative to the darkSusy fct, using captn_specific from capgen instead
    void capture_rate_Sun_const_xsec_capgen(double &result)
    {
      using namespace Pipes::capture_rate_Sun_const_xsec_capgen;
      double resultSD;
      double resultSI;
      double maxcap;

      BEreq::cap_sun_saturation(*Dep::mwimp,maxcap);
      BEreq::cap_Sun_v0q0_isoscalar(*Dep::mwimp,*Dep::sigma_SD_p,*Dep::sigma_SI_p,resultSD,resultSI);
      result = resultSI + resultSD;

      if (maxcap < result)
      {
        result = maxcap;
      }

      //cout << "mwimp" << *Dep::mwimp << "sigma_SI_p: " << *Dep::sigma_SI_p << " sigma_SD_p: " << *Dep::sigma_SD_p << "result: " << result << "\n";
      //cout << "capture rate via capture_rate_Sun_const_xsec_capgen = " << result << "\n";

    }

    ///Capture rate for v^n and q^n-dependent cross sections.
    ///Isoscalar (same proton/neutron coupling)
    ///SD only couples to Hydrogen.
    ///See DirectDetection.cpp to see how to define the cross sections sigma_SD_p, sigma_SI_pi
    void capture_rate_Sun_vnqn(double &result)
    {
      using namespace Pipes::capture_rate_Sun_vnqn;

      double resultSD;
      double resultSI;
      double capped;
      int qpow;
      int vpow;
      const int nelems = 29;
      double maxcap;

      BEreq::cap_sun_saturation(*Dep::mwimp,maxcap);

      resultSI = 0e0;
      resultSD = 0e0;
      typedef map_intpair_dbl::const_iterator it_type;

      //Spin-dependent:
      for(it_type iterator = Dep::sigma_SD_p->begin();
        iterator != Dep::sigma_SD_p->end();
        iterator++)
      {
         //don't capture anything if cross section is zero or all the DM is already capped
        if((iterator->second > 1e-90) && (resultSD < maxcap))
        {
          qpow = (iterator->first).first/2 ;
          vpow =  (iterator->first).second/2;

          //Capture
          BEreq::cap_Sun_vnqn_isoscalar(*Dep::mwimp,iterator->second,1,qpow,vpow,capped);
          resultSD = resultSD+capped;
        }
      }

      //Spin independent:
      for(it_type iterator = Dep::sigma_SI_p->begin();
        iterator != Dep::sigma_SI_p->end();
        iterator++)
      {
        if((iterator->second > 1e-90) && (resultSI+resultSD < maxcap))
        {
          qpow = (iterator->first).first/2 ;
          vpow =  (iterator->first).second/2;

          //Capture
          BEreq::cap_Sun_vnqn_isoscalar(*Dep::mwimp,iterator->second,nelems,qpow,vpow,capped);
          resultSI = resultSI+capped;
        }
      }
      result = resultSI+resultSD;

      logger() << "Capgen captured: SI: " << resultSI << " SD: " << resultSD << " total: " << result << "max = " << maxcap << "\n" << EOM;

      // If capture is above saturation, return saturation value.
      if (maxcap < result)
      {
        result = maxcap;
      }

      //cout << "capture rate via capture_rate_Sun_vnqn = " << result << "\n";

    }
/*
    // couplingNumber and isoSpin are the indicies of a FORTRAN array to fill
    // note: in FORTRAN indices start at 1, not 0 like C++
    void populate_captureArray(double val, int couplingNumber, int isospin)
    {
      using namespace Pipes::populate_captureArray;
      BEreq::populate_array(val, couplingNumber, isospin);
    }
*/

    //Capture rate for Non-Relataivistic Effective Operator (NREO)
    void capture_rate_Sun_NREO(double &result)
    {
      cout << "Starting capture_rate_Sun_NREO ..." << endl;
      using namespace Pipes::capture_rate_Sun_NREO;

      double capped;
      double maxcap;
      const int niso = 16;

      BEreq::cap_sun_saturation(Dep::WIMP_properties->mass,maxcap);

      /*
      use pipe to access parameters of model (0c1...1c15) here (3.2.3 of gambit paper)

      for loop through C++ array of [0c1,0c2,...] (initialized by INI in captn_gen.cpp)
      call populate Array with the value found in the C++ array and the position in the C++ array
      */
      // cout << "The capability grabbed via Pipes, *Dep::c0_1_cap: " << *Dep::c0_1_cap << endl;
      // bjf> Modified to use a custom object to carry these couplings (makes for a better 
      // dependency structure)
      cout << "DD_nonrel_WCs capabilitiy grabbed via Pipes, e.g. Dep::DD_nonrel_WCs->c(0,1) " << Dep::DD_nonrel_WCs->c(0,1) << endl;
      
      int coupleNum;
      for(int j=0; j<15; j++)
      {
        coupleNum = j + 1; // this is the coupling number, ranges 1 to 15 (but not 2)
        if (coupleNum != 2) // 2 is not an allowed coupling constant
        {
          BEreq::populate_array(Dep::DD_nonrel_WCs->c(0,coupleNum), coupleNum, 0);
          BEreq::populate_array(Dep::DD_nonrel_WCs->c(1,coupleNum), coupleNum, 1);
        }
      }
      

      /*
      Code to sum over all elements in solar model simultaneously.
      The fourth parameter tells captn_NREO which of the 16 elements to sum over,
       any other integer (than 1 to 16) tells it to sum over all elements together.
      */
      //cout << "Before calling captn_NREO, capped: " << capped << endl;
      BEreq::captn_NREO(Dep::WIMP_properties->mass,Dep::WIMP_properties->spinx2/2.,niso,0,capped);
      cout << "From captn_NREO;" << endl << "mwimp: " << Dep::WIMP_properties->mass << "GeV" << endl << "capped: " << capped << " captures/second" << endl;

      /// Loop to sum over each element in solar model individually.
      /*
      double isoCapped = 0e0;
      for(int iso=1; iso<(niso+1); iso++)
      {
        BEreq::captn_NREO(*Dep::mwimp,jx,nsio,iso,isoCapped);
        capped += isoCapped;
      }
      */

      result = capped;

      logger() << "Capgen captured: total: " << result << "max = " << maxcap << "\n" << EOM;

      // If capture is above saturation, return saturation value.
      if (maxcap < result)
      {
        result = maxcap;
      }
    }

    /*! \brief Equilibration time for capture and annihilation of dark matter
     * in the Sun (s)
     */
    void equilibration_time_Sun(double &result)
    {
      using namespace Pipes::equilibration_time_Sun;

      double sigmav = 0;
      double T_Sun_core = 1.35e-6; // Sun's core temperature (GeV)

      std::string DMid = *Dep::DarkMatter_ID;
      TH_Process annProc = Dep::TH_ProcessCatalog->getProcess(DMid, DMid);

      // Add all the regular channels
      for (std::vector<TH_Channel>::iterator it = annProc.channelList.begin();
          it != annProc.channelList.end(); ++it)
      {
        if ( it->nFinalStates == 2 )
        {
          // (sv)(v = sqrt(2T/mDM)) for two-body final state
          sigmav += it->genRate->bind("v")->eval(sqrt(2.0*T_Sun_core/(*Dep::mwimp)));
        }
      }

      // Add invisible contributions
      sigmav += annProc.genRateMisc->bind("v")->eval(sqrt(2.0*T_Sun_core/(*Dep::mwimp)));

      double ca = sigmav/6.6e28 * pow(*Dep::mwimp/20.0, 1.5);
      // Scale the annihilation rate down by a factor of two if the DM is not self-conjugate
      if (not (*Dep::TH_ProcessCatalog).getProcess(*Dep::DarkMatter_ID, *Dep::DarkMatter_ID).isSelfConj) ca *= 0.5;
      result = pow(*Dep::capture_rate_Sun * ca, -0.5);

      // std::cout << "v = " << sqrt(2.0*T_Sun_core/(*Dep::mwimp)) << " and sigmav inside equilibration_time_Sun = " << sigmav << std::endl;
      // std::cout << "capture_rate_Sun inside equilibration_time_Sun = " << *Dep::capture_rate_Sun << std::endl;
    }

    /// Annihilation rate of dark matter in the Sun (s^-1)
    void annihilation_rate_Sun(double &result)
    {
      using namespace Pipes::annihilation_rate_Sun;
      double tt_sun = 1.5e17 / *Dep::equilibration_time_Sun;
      result = *Dep::capture_rate_Sun * 0.5 * pow(tanh(tt_sun),2.0);
    }

    /// Neutrino yield function pointer and setup
    void nuyield_from_DS(nuyield_info &result)
    {

      using namespace Pipes::nuyield_from_DS;
      double annihilation_bf[29];
      double Higgs_decay_BFs_neutral[29][3];
      double Higgs_decay_BFs_charged[15];
      double Higgs_masses_neutral[3];
      double Higgs_mass_charged;

      // Set annihilation branching fractions
      // TODO: needs to be fixed once BFs are available directly from TH_Process
      std::string DMid = *Dep::DarkMatter_ID;
      TH_Process annProc = Dep::TH_ProcessCatalog->getProcess(DMid, DMid);

      std::vector< std::vector<str> > neutral_channels = BEreq::get_DS_neutral_h_decay_channels();
      // the missing channel
      const std::vector<str> adhoc_chan = initVector<str>("W-", "H+");

      // Hack together a patch to let DS and TH_processCatalog talk properly about quarks
      std::string bq_array[] = {"d_3","dbar_3"};
      std::string cq_array[] = {"u_2","ubar_2"};
      std::string tau_array[] = {"e+_3","e-_3"};
      std::string tq_array[] = {"u_3","ubar_3"};
      std::vector<str> bottomq (bq_array, bq_array + sizeof(bq_array)/sizeof(std::string));
      std::vector<str> charmq (cq_array, cq_array + sizeof(cq_array)/sizeof(std::string));
      std::vector<str> taul (tau_array, tau_array + sizeof(tau_array)/sizeof(std::string));
      std::vector<str> topq (tq_array, tq_array + sizeof(tq_array)/sizeof(std::string));
      neutral_channels[24] = bottomq;
      neutral_channels[21] = charmq;
      neutral_channels[18] = taul;
      neutral_channels[23] = topq;
      
      #ifdef DARKBIT_DEBUG
        // Print out the vector of channels from TH_ProcessCatalog
        cout << "\nnuyield_from_DS receives the following channels from the WIMP_EFT catalog:\n";
        for (auto x : annProc.channelList)
        {
          for (auto it=x.finalStateIDs.begin(); it!=x.finalStateIDs.end(); it++) cout << *it << " ";
          cout << endl;
        }
        // Print out the vector of channels from DS
        cout << "\nReading neutral_channels from get_DS_neutral_h_decay_channels:\n";
        for (int i=0;i<neutral_channels.size();i++)
        {
          for (auto it=neutral_channels[i].begin(); it!=neutral_channels[i].end(); it++) cout << *it << " ";
          cout << endl;
        }
        // printout the vectors used to mimic the TH_ProcessCatalog format
        cout << "\nMimicing TH_ProcessCatalog vector format:\n";
        for(int i=0; i<2; i++) cout << bottomq[i] << "\t" << charmq[i] << "\t" << taul[i] << "\t" << topq[i] << endl;
        cout << endl;
      #endif

      for (int i=0; i<29; i++)
      {
        const TH_Channel* channel = annProc.find(neutral_channels[i]);
        
        #ifdef DARKBIT_DEBUG
          // Print out the current neutral_channel
          cout << "Looking at the ";
          for (auto it=neutral_channels[i].begin(); it!=neutral_channels[i].end(); it++) cout << *it << " ";
          cout << "neutral_channel" << endl;
          cout << "For which, I found this channel pointer in the annihilation proccess:" << channel << endl;
        #endif
        
        if (channel == NULL or i == 26) // Channel 26 has not been implemented in DarkSUSY.
        {
          annihilation_bf[i] = 0.;

          #ifdef DARKBIT_DEBUG
            cout << "Setting it's branching fraction to zero\n\n";
          #endif
        }
        else
        {
          annihilation_bf[i] = channel->genRate->bind("v")->eval(0.);
          if (i == 10) // Add W- H+ for this channel
          {
            channel = annProc.find(adhoc_chan);
            if (channel == NULL) DarkBit_error().raise(LOCAL_INFO,
                "W+H- exists in process catalog but not W-H+."
                " That's some suspiciously severe CP violation yo.");
            annihilation_bf[i] += channel->genRate->bind("v")->eval(0.);
          }
          annihilation_bf[i] /= *Dep::sigmav;

          // Check that having this channel turned on makes sense at all.
          #ifdef DARKBIT_DEBUG
            cout << "Now the channel's branching fraction is set\n";
            double mtot = 0;
            cout << "Particles and masses in DM annihilation final state: " << endl;
            for (auto p = neutral_channels[i].begin(); p != neutral_channels[i].end(); ++p)
            {
              double m = Dep::TH_ProcessCatalog->getParticleProperty(*p).mass;
              cout << "  " << *p << " " << m << endl;
              mtot += m;
            }
            cout << "Sqrt(s) vs total mass of final states: " << 2 * *Dep::mwimp << " vs. " << mtot << endl;
            cout << "Branching fraction in v=0 limit: " << annihilation_bf[i] << endl << endl;
            if (mtot > 2 * *Dep::mwimp and annihilation_bf[i] > 0.0)
             DarkBit_error().raise(LOCAL_INFO, "Channel is open in process catalog but should not be kinematically allowed.");
          #endif
        }

      }


      // Set Higgs masses
      if (Dep::TH_ProcessCatalog->hasParticleProperty("h0_1"))
        Higgs_masses_neutral[1] = Dep::TH_ProcessCatalog->getParticleProperty("h0_1").mass;
      else
        DarkBit_error().raise(LOCAL_INFO, "No SM-like Higgs in ProcessCatalog!");
      Higgs_masses_neutral[0] =
        Dep::TH_ProcessCatalog->hasParticleProperty("h0_2") ?
        Dep::TH_ProcessCatalog->getParticleProperty("h0_2").mass : 0.;
      Higgs_masses_neutral[2] =
        Dep::TH_ProcessCatalog->hasParticleProperty("A0") ?
        Dep::TH_ProcessCatalog->getParticleProperty("A0").mass : 0.;
      Higgs_mass_charged =
        Dep::TH_ProcessCatalog->hasParticleProperty("H+") ?
        Dep::TH_ProcessCatalog->getParticleProperty("H+").mass : 0.;

      // Find out which Higgs exist and have decay data in the process
      // catalog.
      const TH_Process* h0_decays[3];
      h0_decays[0] = Dep::TH_ProcessCatalog->find("h0_2");
      h0_decays[1] = Dep::TH_ProcessCatalog->find("h0_1");
      h0_decays[2] = Dep::TH_ProcessCatalog->find("A0");
      const TH_Process* Hplus_decays = Dep::TH_ProcessCatalog->find("H+");
      const TH_Process* Hminus_decays = Dep::TH_ProcessCatalog->find("H-");
      if (Hplus_decays != NULL and Hminus_decays == NULL) DarkBit_error().raise(
          LOCAL_INFO, "H+ decays exist in process catalog but not H-.");
      if (Hplus_decays == NULL and Hminus_decays != NULL) DarkBit_error().raise(
          LOCAL_INFO, "H- decays exist in process catalog but not H+.");

      // Set the neutral Higgs decay branching fractions
      // TODO: needs to be fixed once BFs are available directly from TH_Process
      for (int i=0; i<3; i++)       // Loop over the three neutral Higgs
      {

        // If this Higgs exists, set its decay properties.
        if (h0_decays[i] != NULL)
        {

          // Get the total decay width, for normalising partial widths to BFs.
          // TODO: Replace when BFs become directly available.
          double totalwidth = 0.0;
          for (std::vector<TH_Channel>::const_iterator
              it = h0_decays[i]->channelList.begin();
              it != h0_decays[i]->channelList.end(); ++it)
          {
            // decay width in GeV for two-body final state
            if ( it->nFinalStates == 2 ) totalwidth +=
              it->genRate->bind()->eval();
          }

          std::vector<str> neutral_channel;
          // Loop over the decay channels for neutral scalars
          for (int j=0; j<29; j++)
          {
            neutral_channel.clear();
            neutral_channel.push_back(DarkBit_utils::str_flav_to_mass((neutral_channels[j])[0]));
            neutral_channel.push_back(DarkBit_utils::str_flav_to_mass((neutral_channels[j])[1]));
            const TH_Channel* channel = h0_decays[i]->find(neutral_channel);
            // If this Higgs can decay into this channel, set the BF.
            if (channel != NULL)
            {
              Higgs_decay_BFs_neutral[j][i] = channel->genRate->bind()->eval();
              if (j == 10)          // Add W- H+ for this channel
              {
                channel = h0_decays[i]->find(adhoc_chan);
                if (channel == NULL) DarkBit_error().raise(LOCAL_INFO,
                    "W+H- exists in process catalog but not W-H+."
                    " That's some suspiciously severe CP violation yo.");
                Higgs_decay_BFs_neutral[j][i]
                  += channel->genRate->bind()->eval();
              }
              // This channel has not been implemented in DarkSUSY.
              if (j == 26) Higgs_decay_BFs_neutral[j][i] = 0.;
              Higgs_decay_BFs_neutral[j][i] /= totalwidth;
            }
            else
            {
              Higgs_decay_BFs_neutral[j][i] = 0.;
            }
          }

        }

        else
        {
          // Loop over the decay channels for neutral scalars, setting all BFs
          // for this Higgs to zero.
          for (int j=0; j<29; j++) Higgs_decay_BFs_neutral[j][i] = 0.;
        }

      }

      // If they exist, set the charged Higgs decay branching fractions
      // (DarkSUSY assumes that H+/H- decays are CP-invariant)
      if (Hplus_decays != NULL)
      {

        // Define the charged Higgs decay channels
        std::vector< std::vector<str> > charged_channels = BEreq::get_DS_charged_h_decay_channels();

        // Get the total decay width, for normalising partial widths to BFs.
        // TODO: Replace when BFs become directly available.
        double totalwidth = 0.0;
        for (std::vector<TH_Channel>::const_iterator
            it = Hplus_decays->channelList.begin();
            it != Hplus_decays->channelList.end(); ++it)
        {
          // decay width in GeV for two-body final state
          if (it->nFinalStates == 2) totalwidth += it->genRate->bind()->eval();
        }

        std::vector<str> charged_channel;
        // Loop over the decay channels for charged scalars
        for (int j=0; j<15; j++)
        {
          charged_channel.clear();
          charged_channel.push_back(DarkBit_utils::str_flav_to_mass((charged_channels[j])[0]));
          charged_channel.push_back(DarkBit_utils::str_flav_to_mass((charged_channels[j])[1]));
          const TH_Channel* channel = Hplus_decays->find(charged_channel);
          // If this Higgs can decay into this channel, set the BF.
          if (channel != NULL)
          {
            Higgs_decay_BFs_charged[j] = channel->genRate->bind()->eval();
            Higgs_decay_BFs_charged[j] /= totalwidth;
          }
          else
          {
            Higgs_decay_BFs_charged[j] = 0.;
          }
        }

      }

      else
      {
        // Loop over the decay channels for charged scalars, setting all BFs
        // for this Higgs to zero.
        for (int j=0; j<15; j++) Higgs_decay_BFs_charged[j] = 0.;
      }

      // Debug output
      #ifdef DARKBIT_DEBUG
        for (int j=0; j<29; j++)
        {
          cout<< "annihilation bfs: " << j << " " << annihilation_bf[j] << endl;
        }
        cout<< endl;
        for (int i=0; i<3; i++)
        {
          for (int j=0; j<29; j++)
          {
            cout<< "higgs neutral bfs: " << i << " " << j << " "
              << Higgs_decay_BFs_neutral[j][i] << endl;
          }
        }
        cout<< endl;
        for (int j=0; j<15; j++)
        {
          cout<< "higgs charged bfs: " << j << " "
            << Higgs_decay_BFs_charged[j] << endl;
        }
        cout<< endl;
        for (int j=0; j<3; j++)
        {
          cout<< "higgs masses neutral: " << j << " "
            << Higgs_masses_neutral[j] << endl;
        }
        cout<< endl;
        cout<< "higgs charged mass: " << Higgs_mass_charged << endl;
        cout<< endl;
        cout<< "*Dep::mwimp: " << *Dep::mwimp << endl;
        cout<< endl;
        cout<< "*Dep::sigmav: " << *Dep::sigmav << endl;
        cout<< endl;
      #endif

      // Set up DarkSUSY to do neutrino yields for this particular WIMP
      BEreq::nuyield_setup(annihilation_bf, Higgs_decay_BFs_neutral,
          Higgs_decay_BFs_charged, Higgs_masses_neutral,
          Higgs_mass_charged, *Dep::mwimp);

      // Hand back the pointer to the DarkSUSY neutrino yield function
      result.pointer = BEreq::nuyield.pointer();

      //TODO: change below to >= when version numbers are available as ints
      // Treat the yield function as threadsafe only if the loaded version of DarkSUSY supports it.
      result.threadsafe = (BEreq::nuyield.version() == "5.1.3");

      // Avoid OpenMP with gfortran 6.x and later, as the implementation seems to be buggy (causes stack overflows).
      #ifdef __GNUC__
        #define GCC_VERSION (__GNUC__ * 10000 \
                     + __GNUC_MINOR__ * 100 \
                     + __GNUC_PATCHLEVEL__)
        #if GCC_VERSION > 60000
          result.threadsafe = false;
        #endif
        #undef GCC_VERSION
      #endif

    }

    /// grabbed from ScalarSingletDM.cpp
    /// Set up process catalog for Z2 scalar singlet DM.
    // void TH_ProcessCatalog_NREO(DarkBit::TH_ProcessCatalog &result)
    // {
    //   using namespace Pipes::TH_ProcessCatalog_NREO;
    //   using std::vector;
    //   using std::string;

    //   // Initialize empty catalog and main annihilation process
    //   TH_ProcessCatalog catalog;
    //   TH_Process process_ann("S", "S");

    //   // Explicitly state that Z2 Scalar DM is self-conjugate
    //   process_ann.isSelfConj = true;

    //   ///////////////////////////////////////
    //   // Import particle masses and couplings
    //   ///////////////////////////////////////

    //   // Convenience macros
    //   #define getSMmass(Name, spinX2)                                           \
    //    catalog.particleProperties.insert(std::pair<string, TH_ParticleProperty> \
    //    (Name , TH_ParticleProperty(SM.get(Par::Pole_Mass,Name), spinX2)));
    //   #define addParticle(Name, Mass, spinX2)                                   \
    //    catalog.particleProperties.insert(std::pair<string, TH_ParticleProperty> \
    //    (Name , TH_ParticleProperty(Mass, spinX2)));

    //   // Import Spectrum objects
    //   const Spectrum& spec = *Dep::ScalarSingletDM_Z2_spectrum; /////////// need my own spectrum?
    //   const SubSpectrum& he = spec.get_HE();
    //   const SubSpectrum& SM = spec.get_LE();
    //   const SMInputs& SMI   = spec.get_SMInputs();

    //   // Import couplings
    //   double lambda = he.get(Par::dimensionless,"lambda_hS");
    //   double v = he.get(Par::mass1,"vev");

    //   // Get SM pole masses
    //   getSMmass("e-_1",     1)
    //   getSMmass("e+_1",     1)
    //   getSMmass("e-_2",     1)
    //   getSMmass("e+_2",     1)
    //   getSMmass("e-_3",     1)
    //   getSMmass("e+_3",     1)
    //   getSMmass("Z0",     2)
    //   getSMmass("W+",     2)
    //   getSMmass("W-",     2)
    //   getSMmass("g",      2)
    //   getSMmass("gamma",  2)
    //   getSMmass("u_3",      1)
    //   getSMmass("ubar_3",   1)
    //   getSMmass("d_3",      1)
    //   getSMmass("dbar_3",   1)

    //   // Pole masses not available for the light quarks.
    //   addParticle("u_1"   , SMI.mU,  1) // mu(2 GeV)^MS-bar, not pole mass
    //   addParticle("ubar_1", SMI.mU,  1) // mu(2 GeV)^MS-bar, not pole mass
    //   addParticle("d_1"   , SMI.mD,  1) // md(2 GeV)^MS-bar, not pole mass
    //   addParticle("dbar_1", SMI.mD,  1) // md(2 GeV)^MS-bar, not pole mass
    //   addParticle("u_2"   , SMI.mCmC,1) // mc(mc)^MS-bar, not pole mass
    //   addParticle("ubar_2", SMI.mCmC,1) // mc(mc)^MS-bar, not pole mass
    //   addParticle("d_2"   , SMI.mS,  1) // ms(2 GeV)^MS-bar, not pole mass
    //   addParticle("dbar_2", SMI.mS,  1) // ms(2 GeV)^MS-bar, not pole mass
    //   double alpha_s = SMI.alphaS;      // alpha_s(mZ)^MSbar

    //   // Masses for neutrino flavour eigenstates. Set to zero.
    //   // (presently not required)
    //   addParticle("nu_e",     0.0, 1)
    //   addParticle("nubar_e",  0.0, 1)
    //   addParticle("nu_mu",    0.0, 1)
    //   addParticle("nubar_mu", 0.0, 1)
    //   addParticle("nu_tau",   0.0, 1)
    //   addParticle("nubar_tau",0.0, 1)

    //   // Higgs-sector masses
    //   double mS = spec.get(Par::Pole_Mass,"S");
    //   double mH = spec.get(Par::Pole_Mass,"h0_1");
    //   addParticle("S",        mS, 0)  // Scalar Singlet DM
    //   addParticle("h0_1",     mH, 0)  // SM-like Higgs
    //   addParticle("pi0",   meson_masses.pi0,       0)
    //   addParticle("pi+",   meson_masses.pi_plus,   0)
    //   addParticle("pi-",   meson_masses.pi_minus,  0)
    //   addParticle("eta",   meson_masses.eta,       0)
    //   addParticle("rho0",  meson_masses.rho0,      1)
    //   addParticle("rho+",  meson_masses.rho_plus,  1)
    //   addParticle("rho-",  meson_masses.rho_minus, 1)
    //   addParticle("omega", meson_masses.omega,     1)

    //   // Get rid of convenience macros
    //   #undef getSMmass
    //   #undef addParticle


    //   /////////////////////////////
    //   // Import Decay information
    //   /////////////////////////////

    //   // Import decay table from DecayBit
    //   const DecayTable* tbl = &(*Dep::decay_rates);

    //   // Save Higgs width for later
    //   double gammaH = tbl->at("h0_1").width_in_GeV;

    //   // Set of imported decays
    //   std::set<string> importedDecays;

    //   // Minimum branching ratio to include
    //   double minBranching = 0;

    //   // Import relevant decays (only Higgs and subsequent decays)
    //   using DarkBit_utils::ImportDecays;
    //   // Notes: Virtual Higgs decays into offshell W+W- final states are not
    //   // imported.  All other channels are correspondingly rescaled.  Decay
    //   // into SS final states is accounted for, leading to zero photons.
    //   ImportDecays("h0_1", catalog, importedDecays, tbl, minBranching,
    //       daFunk::vec<std::string>("Z0", "W+", "W-", "e+_2", "e-_2", "e+_3", "e-_3"));

    //   // Instantiate new ScalarSingletDM object
    //   auto singletDM = boost::make_shared<ScalarSingletDM>(&catalog, gammaH, v, alpha_s, 0.0);

    //   // Populate annihilation channel list and add thresholds to threshold
    //   // list.
    //   // (remark: the lowest threshold is here = 2*mS, whereas in DS-internal
    //   // conventions, this lowest threshold is not listed)
    //   process_ann.resonances_thresholds.threshold_energy.push_back(2*mS);
    //   auto channel =
    //     daFunk::vec<string>("bb", "WW", "cc", "tautau", "ZZ", "tt", "hh");
    //   auto p1 =
    //     daFunk::vec<string>("d_3",   "W+", "u_2",   "e+_3", "Z0", "u_3",   "h0_1");
    //   auto p2 =
    //     daFunk::vec<string>("dbar_3","W-", "ubar_2","e-_3", "Z0", "ubar_3","h0_1");
    //   {
    //     for ( unsigned int i = 0; i < channel.size(); i++ )
    //     {
    //       double mtot_final =
    //         catalog.getParticleProperty(p1[i]).mass +
    //         catalog.getParticleProperty(p2[i]).mass;
    //       // Include final states that are open for T~m/20
    //       if ( mS*2 > mtot_final*0.5 )
    //       {
    //         daFunk::Funk kinematicFunction = daFunk::funcM(singletDM,
    //             &ScalarSingletDM::sv, channel[i], lambda, mS, daFunk::var("v"));
    //         TH_Channel new_channel(
    //             daFunk::vec<string>(p1[i], p2[i]), kinematicFunction
    //             );
    //         process_ann.channelList.push_back(new_channel);
    //       }
    //       if ( mS*2 > mtot_final )
    //       {
    //         process_ann.resonances_thresholds.threshold_energy.
    //           push_back(mtot_final);
    //       }
    //     }
    //   }

    //   // Populate resonance list
    //   if ( mH >= mS*2 ) process_ann.resonances_thresholds.resonances.
    //       push_back(TH_Resonance(mH, gammaH));

    //   catalog.processList.push_back(process_ann);

    //   // Validate
    //   catalog.validate();


    //   #ifdef DARKBIT_DEBUG
    //     // get DarkBit computed vSigma total
    //     // so we can compare with that from MO
    //     ScalarSingletDM test = *singletDM;
    //     int nc = 7;
    //     double total = 0;
    //     for (int ii=0; ii < nc ; ii++)
    //     {
    //       total = total + test.sv(channel[ii], lambda, mS, 0.0);
    //     }
    //     cout << " --- Testing process catalouge --- " << endl;
    //     cout << "Total sigma V from process catalouge = " << total << endl;
    //     cout << " ---------- " << endl;
    //   #endif



    //   result = catalog;
    // } // function TH_ProcessCatalog_NREO

    /// \brief Likelihood calculators for different IceCube event samples
    /// These functions all include the likelihood of the background-only model for the respective sample.
    /// We define the final log-likelihood as delta = sum over analyses of (lnL_model - lnL_BG), conservatively
    /// forbidding delta > 0 in order to always just use the neutrino likelihood as a limit.  This ignores small
    /// low-E excesses caused by impending breakdown of approximations used in IceCube response data and the nulike
    /// likelihood at very low E. This implies conditioning on all but one parameter (e.g. the cross-section),
    /// such that including any particular IC analysis adds just *one* additional degree of freedom to the fit.
    /// @{

    /// \brief 22-string IceCube sample: predicted signal and background
    /// counts, observed counts and likelihoods.
    void IC22_full(nudata &result)
    {
      using namespace Pipes::IC22_full;
      static bool first = true;
      const double bgloglike = -808.4581;
      double sigpred, bgpred, lnLike, pval;
      int totobs;
      char experiment[300] = "IC-22";
      void* context = NULL;
      double theoryError = (*Dep::mwimp > 100.0 ? 0.05*sqrt(*Dep::mwimp*0.01) : 0.05);
      /// Option nulike_speed<int>: Speed setting for nulike backend (default 3)
      int speed = runOptions->getValueOrDef<int>(3,"nulike_speed");
      BEreq::nubounds(experiment[0], *Dep::mwimp, *Dep::annihilation_rate_Sun,
          byVal(Dep::nuyield_ptr->pointer), sigpred, bgpred, totobs, lnLike, pval, 4,
          theoryError, speed, false, 0.0, 0.0, context, Dep::nuyield_ptr->threadsafe);
      piped_invalid_point.check();
      piped_errors.check(DarkBit_error());
      piped_warnings.check(DarkBit_warning());
      result.signal = sigpred;
      result.bg = bgpred;
      result.nobs = totobs;
      result.loglike = lnLike;
      result.pvalue = pval;
      if (first)
      {
        result.bgloglike = bgloglike;
        first = false;
      }
    }

    /// \brief 79-string IceCube WH sample: predicted signal and background
    /// counts, observed counts and likelihoods.
    void IC79WH_full(nudata &result)
    {
      static bool first = true;
      using namespace Pipes::IC79WH_full;
      const double bgloglike = -11874.8689;
      double sigpred, bgpred, lnLike, pval;
      int totobs;
      char experiment[300] = "IC-79 WH";
      void* context = NULL;
      double theoryError = (*Dep::mwimp > 100.0 ? 0.05*sqrt(*Dep::mwimp*0.01) : 0.05);
      /// Option nulike_speed<int>: Speed setting for nulike backend (default 3)
      int speed = runOptions->getValueOrDef<int>(3,"nulike_speed");
      BEreq::nubounds(experiment[0], *Dep::mwimp, *Dep::annihilation_rate_Sun,
          byVal(Dep::nuyield_ptr->pointer), sigpred, bgpred, totobs, lnLike, pval, 4,
          theoryError, speed, false, 0.0, 0.0, context, Dep::nuyield_ptr->threadsafe);
      piped_invalid_point.check();
      piped_errors.check(DarkBit_error());
      piped_warnings.check(DarkBit_warning());
      result.signal = sigpred;
      result.bg = bgpred;
      result.nobs = totobs;
      result.loglike = lnLike;
      result.pvalue = pval;
      if (first)
      {
        result.bgloglike = bgloglike;
        first = false;
      }
    }

    /// \brief 79-string IceCube WL sample: predicted signal and background
    /// counts, observed counts and likelihoods.
    void IC79WL_full(nudata &result)
    {
      static bool first = true;
      using namespace Pipes::IC79WL_full;
      const double bgloglike = -1813.4503;
      double sigpred, bgpred, lnLike, pval;
      int totobs;
      char experiment[300] = "IC-79 WL";
      void* context = NULL;
      double theoryError = (*Dep::mwimp > 100.0 ? 0.05*sqrt(*Dep::mwimp*0.01) : 0.05);
      /// Option nulike_speed<int>: Speed setting for nulike backend (default 3)
      int speed = runOptions->getValueOrDef<int>(3,"nulike_speed");
      BEreq::nubounds(experiment[0], *Dep::mwimp, *Dep::annihilation_rate_Sun,
          byVal(Dep::nuyield_ptr->pointer), sigpred, bgpred, totobs, lnLike, pval, 4,
          theoryError, speed, false, 0.0, 0.0, context, Dep::nuyield_ptr->threadsafe);
      piped_invalid_point.check();
      piped_errors.check(DarkBit_error());
      piped_warnings.check(DarkBit_warning());
      result.signal = sigpred;
      result.bg = bgpred;
      result.nobs = totobs;
      result.loglike = lnLike;
      result.pvalue = pval;
      if (first)
      {
        result.bgloglike = bgloglike;
        first = false;
      }
    }

    /// \brief 79-string IceCube SL sample: predicted signal and background
    /// counts, observed counts and likelihoods.
    void IC79SL_full(nudata &result)
    {
      static bool first = true;
      using namespace Pipes::IC79SL_full;
      const double bgloglike = -5015.6474;
      double sigpred, bgpred, lnLike, pval;
      int totobs;
      char experiment[300] = "IC-79 SL";
      void* context = NULL;
      double theoryError = (*Dep::mwimp > 100.0 ? 0.05*sqrt(*Dep::mwimp*0.01) : 0.05);
      /// Option nulike_speed<int>: Speed setting for nulike backend (default 3)
      int speed = runOptions->getValueOrDef<int>(3,"nulike_speed");
      BEreq::nubounds(experiment[0], *Dep::mwimp, *Dep::annihilation_rate_Sun,
          byVal(Dep::nuyield_ptr->pointer), sigpred, bgpred, totobs, lnLike, pval, 4,
          theoryError, speed, false, 0.0, 0.0, context, Dep::nuyield_ptr->threadsafe);
      piped_invalid_point.check();
      piped_errors.check(DarkBit_error());
      piped_warnings.check(DarkBit_warning());
      result.signal = sigpred;
      result.bg = bgpred;
      result.nobs = totobs;
      result.loglike = lnLike;
      result.pvalue = pval;
      if (first)
      {
        result.bgloglike = bgloglike;
        first = false;
      }
    }
    /// @}

    /// 22-string extractor module functions
    /// @{
    void IC22_signal (double &result)   {
      result = Pipes::IC22_signal ::Dep::IC22_data->signal;      }
    void IC22_bg     (double &result)   {
      result = Pipes::IC22_bg     ::Dep::IC22_data->bg;          }
    void IC22_nobs   (int    &result)   {
      result = Pipes::IC22_nobs   ::Dep::IC22_data->nobs;        }
    void IC22_loglike(double &result)   {
      result = Pipes::IC22_loglike::Dep::IC22_data->loglike;     }
    void IC22_bgloglike(double &result) {
      result = Pipes::IC22_bgloglike::Dep::IC22_data->bgloglike; }
    void IC22_pvalue (double &result)   {
      result = Pipes::IC22_pvalue ::Dep::IC22_data->pvalue;      }
    /// @}

    /// 79-string WH extractor module functions
    /// @{
    void IC79WH_signal (double &result)   {
      result = Pipes::IC79WH_signal ::Dep::IC79WH_data->signal;      }
    void IC79WH_bg     (double &result)   {
      result = Pipes::IC79WH_bg     ::Dep::IC79WH_data->bg;          }
    void IC79WH_nobs   (int    &result)   {
      result = Pipes::IC79WH_nobs   ::Dep::IC79WH_data->nobs;        }
    void IC79WH_loglike(double &result)   {
      result = Pipes::IC79WH_loglike::Dep::IC79WH_data->loglike;     }
    void IC79WH_bgloglike(double &result) {
      result = Pipes::IC79WH_bgloglike::Dep::IC79WH_data->bgloglike; }
    void IC79WH_pvalue (double &result)   {
      result = Pipes::IC79WH_pvalue ::Dep::IC79WH_data->pvalue;      }
    /// @}

    /// 79-string WL extractor module functions
    /// @{
    void IC79WL_signal (double &result)   {
      result = Pipes::IC79WL_signal ::Dep::IC79WL_data->signal;      }
    void IC79WL_bg     (double &result)   {
      result = Pipes::IC79WL_bg     ::Dep::IC79WL_data->bg;          }
    void IC79WL_nobs   (int    &result)   {
      result = Pipes::IC79WL_nobs   ::Dep::IC79WL_data->nobs;        }
    void IC79WL_loglike(double &result)   {
      result = Pipes::IC79WL_loglike::Dep::IC79WL_data->loglike;     }
    void IC79WL_bgloglike(double &result) {
      result = Pipes::IC79WL_bgloglike::Dep::IC79WL_data->bgloglike; }
    void IC79WL_pvalue (double &result)   {
      result = Pipes::IC79WL_pvalue ::Dep::IC79WL_data->pvalue;      }
    /// @}

    /// 79-string SL extractor module functions
    /// @{
    void IC79SL_signal (double &result)   {
      result = Pipes::IC79SL_signal ::Dep::IC79SL_data->signal;      }
    void IC79SL_bg     (double &result)   {
      result = Pipes::IC79SL_bg     ::Dep::IC79SL_data->bg;          }
    void IC79SL_nobs   (int    &result)   {
      result = Pipes::IC79SL_nobs   ::Dep::IC79SL_data->nobs;        }
    void IC79SL_loglike(double &result)   {
      result = Pipes::IC79SL_loglike::Dep::IC79SL_data->loglike;     }
    void IC79SL_bgloglike(double &result) {
      result = Pipes::IC79SL_bgloglike::Dep::IC79SL_data->bgloglike; }
    void IC79SL_pvalue (double &result)   {
      result = Pipes::IC79SL_pvalue ::Dep::IC79SL_data->pvalue;      }
    /// @}

    /// Composite IceCube 79-string likelihood function.
    void IC79_loglike(double &result)
    {
      using namespace Pipes::IC79_loglike;
      result = *Dep::IC79SL_loglike - *Dep::IC79SL_bgloglike +
               *Dep::IC79WL_loglike - *Dep::IC79WL_bgloglike +
               *Dep::IC79WH_loglike - *Dep::IC79WH_bgloglike;
      if (result > 0.0) result = 0.0;
    }

    /// Complete composite IceCube likelihood function.
    void IC_loglike(double &result)
    {
      using namespace Pipes::IC_loglike;
      result = *Dep::IC22_loglike   - *Dep::IC22_bgloglike   +
               *Dep::IC79SL_loglike - *Dep::IC79SL_bgloglike +
               *Dep::IC79WL_loglike - *Dep::IC79WL_bgloglike +
               *Dep::IC79WH_loglike - *Dep::IC79WH_bgloglike;
      if (result > 0.0) result = 0.0;
#ifdef DARKBIT_DEBUG
      cout << "IC likelihood: " << result << endl;
      cout << "IC79SL contribution: " << *Dep::IC79SL_loglike - *Dep::IC79SL_bgloglike << endl;
      cout << "IC79WL contribution: " << *Dep::IC79WL_loglike - *Dep::IC79WL_bgloglike << endl;
      cout << "IC79WH contribution: " << *Dep::IC79WH_loglike - *Dep::IC79WH_bgloglike << endl;
      cout << "IC22   contribution: " << *Dep::IC22_loglike   - *Dep::IC22_bgloglike   << endl;
#endif
    }

    /// Function to set Local Halo Parameters in DarkSUSY
    void DarkSUSY_PointInit_LocalHalo_func(bool &result)
    {
        using namespace Pipes::DarkSUSY_PointInit_LocalHalo_func;

          LocalMaxwellianHalo LocalHaloParameters = *Dep::LocalHalo;

          double rho0 = LocalHaloParameters.rho0;
          double rho0_eff = (*Dep::RD_fraction)*rho0;
          double vrot = LocalHaloParameters.vrot;
          double vd_3d = sqrt(3./2.)*LocalHaloParameters.v0;
          double vesc = LocalHaloParameters.vesc;
          /// Option v_earth<double>: Keplerian velocity of the Earth around the Sun in km/s (default 29.78)
          double v_earth = runOptions->getValueOrDef<double>(29.78, "v_earth");

          BEreq::dshmcom->rho0 = rho0;
          BEreq::dshmcom->v_sun = vrot;
          BEreq::dshmcom->v_earth = v_earth;
          BEreq::dshmcom->rhox = rho0_eff;

          BEreq::dshmframevelcom->v_obs = vrot;

          BEreq::dshmisodf->vd_3d = vd_3d;
          BEreq::dshmisodf->vgalesc = vesc;

          BEreq::dshmnoclue->vobs = vrot;

          logger() << LogTags::debug
                   << "Updating DarkSUSY halo parameters:" << std::endl
                   << "    rho0 [GeV/cm^3] = " << rho0 << std::endl
                   << "    rho0_eff [GeV/cm^3] = " << rho0_eff << std::endl
                   << "    v_sun [km/s]  = " << vrot<< std::endl
                   << "    v_earth [km/s]  = " << v_earth << std::endl
                   << "    v_obs [km/s]  = " << vrot << std::endl
                   << "    vd_3d [km/s]  = " << vd_3d << std::endl
                   << "    v_esc [km/s]  = " << vesc << EOM;

          result = true;

          return;
    }
  }
}
