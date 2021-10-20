//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Relic density calculations.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Torsten Bringmann
///          (torsten.bringmann@desy.de)
///  \date 2013 Jun -- 2016 May, 2019
///
///  \author Christoph Weniger
///          (c.weniger@uva.nl)
///  \date 2013 Jul - 2015 May
///
///  *********************************************

#include <chrono>

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/DarkBit/DarkBit_rollcall.hpp"
#include "gambit/DarkBit/DarkBit_utils.hpp"
#include "gambit/Utils/util_functions.hpp"


namespace Gambit
{
  namespace DarkBit
  {

//#define DARKBIT_DEBUG
//#define DARKBIT_RD_DEBUG

    //////////////////////////////////////////////////////////////////////////
    //
    //                    DarkSUSY Relic density routines
    //
    //////////////////////////////////////////////////////////////////////////


    /*! \brief Collects spectrum information about coannihilating particles,
     *         resonances and threshold energies.
     */
    void RD_spectrum_MSSM(RD_spectrum_type &result)
    {
      using namespace Pipes::RD_spectrum_MSSM;

      std::string DMid = *Dep::DarkMatter_ID;
      if ( DMid != "~chi0_1" )
      {
        invalid_point().raise(
            "RD_spectrum_MSSM requires DMid to be ~chi0_1.");
      }
      // Neutralino DM is self-conjugate
      result.isSelfConj = true;
      // This function reports particle IDs in terms of PDG codes
      result.particle_index_type = "PDG";

      // Import based on Spectrum objects
      const Spectrum& matched_spectra = *Dep::MSSM_spectrum;
      const SubSpectrum& spec = matched_spectra.get_HE();
      const SubSpectrum& SMspec = matched_spectra.get_LE();
      // Import based on decay table from DecayBit
      const DecayTable* myDecays = &(*Dep::decay_rates);

      result.coannihilatingParticles.clear();
      result.resonances.clear();
      result.threshold_energy.clear();

      /// Option CoannCharginosNeutralinos<bool>: Specify whether charginos and
      /// neutralinos are included in coannihilations (default: true)
      bool CoannCharginosNeutralinos = runOptions->getValueOrDef<bool>(true,
          "CoannCharginosNeutralinos");

      /// Option CoannSfermions<bool>: Specify whether sfermions are included in
      /// coannihilations (default: true)
      bool CoannSfermions = runOptions->getValueOrDef<bool>(true,
          "CoannSfermions");

      /// Option CoannMaxMass<double>: Maximal sparticle mass to be included in
      /// coannihilations, in units of DM mass (default: 1.6)
      double CoannMaxMass = runOptions->getValueOrDef<double>(1.6,
          "CoannMaxMass");

      // first add neutralino=WIMP=least massive 'coannihilating particle'
      // Note: translation from PDG codes assumes context integer = 0 here and
      // in the following (essentially "mass ordering"). For consistency the same
      // has to be done when retrieving information from the RD_spectrum_type result
      int ContInt = 0;
      int PDGwimp = 1000022;
      double mWIMP = std::abs(spec.get(Par::Pole_Mass,Models::ParticleDB().long_name(PDGwimp,ContInt)));
      result.coannihilatingParticles.push_back(RD_coannihilating_particle(PDGwimp, 2, mWIMP));

      #ifdef DARKBIT_DEBUG
        std::cout << "WIMP mass : "<< mWIMP << std::endl;
      #endif

      // add all sparticles that are not too heavy
      double msp;
      auto addCoannParticle = [&](int pdg0, int dof)
      {
        msp = std::abs(spec.get(Par::Pole_Mass,Models::ParticleDB().long_name(pdg0,ContInt)));
        if (msp/mWIMP < CoannMaxMass)
        {
           result.coannihilatingParticles.push_back(RD_coannihilating_particle(pdg0, dof, msp));
        }
      };

      if(CoannCharginosNeutralinos) // include  neutralino & chargino coannihilation
      {
        addCoannParticle(1000023, 2);        // "~chi0_2"
        addCoannParticle(1000025, 2);        // "~chi0_3"
        addCoannParticle(1000035, 2);        // "~chi0_4"
        addCoannParticle(1000024, 4);        // "~chi+_1"
        addCoannParticle(1000037, 4);        // "~chi+_2"
      }
      if(CoannSfermions) // include sfermion coannihilation
      {
        addCoannParticle(1000011, 2);        // "~e-_1"
        addCoannParticle(1000013, 2);        // "~e-_2"
        addCoannParticle(1000015, 2);        // "~e-_3"
        addCoannParticle(2000011, 2);        // "~e-_4"
        addCoannParticle(2000013, 2);        // "~e-_5"
        addCoannParticle(2000015, 2);        // "~e-_6"
        addCoannParticle(1000012, 1);        // "~nu_1"
        addCoannParticle(1000014, 1);        // "~nu_2"
        addCoannParticle(1000016, 1);        // "~nu_3"
        addCoannParticle(1000001, 6);        // "~d_1"
        addCoannParticle(1000003, 6);        // "~d_2"
        addCoannParticle(1000005, 6);        // "~d_3"
        addCoannParticle(2000001, 6);        // "~d_4"
        addCoannParticle(2000003, 6);        // "~d_5"
        addCoannParticle(2000005, 6);        // "~d_6"
        addCoannParticle(1000002, 6);        // "~u_1"
        addCoannParticle(1000004, 6);        // "~u_2"
        addCoannParticle(1000006, 6);        // "~u_3"
        addCoannParticle(2000002, 6);        // "~u_4"
        addCoannParticle(2000004, 6);        // "~u_5"
        addCoannParticle(2000006, 6);        // "~u_6"
      }

      // determine resonances for LSP annihilation
      std::string SMreslist[] = {"Z0","W+"};
      std::string reslist[] = {"h0_2","h0_1","A0","H+"};
      int resSMmax=sizeof(SMreslist) / sizeof(SMreslist[0]);
      int resmax=sizeof(reslist) / sizeof(reslist[0]);
      // Charged resonances (last items in the lists) can only appear for coannihilations
      if (result.coannihilatingParticles.size() == 1)
      {
        resSMmax -= 1;
        resmax -= 1;
      }
      double mres,Gammares;
      for (int i=0; i<resSMmax; i++)
      {
          mres = std::abs(SMspec.get(Par::Pole_Mass,SMreslist[i]));
          Gammares = myDecays->at(SMreslist[i]).width_in_GeV;
          result.resonances.push_back(TH_Resonance(mres,Gammares));
      }
      for (int i=0; i<resmax; i++)
      {
        mres = std::abs(spec.get(Par::Pole_Mass,reslist[i]));
        Gammares = myDecays->at(reslist[i]).width_in_GeV;
        result.resonances.push_back(TH_Resonance(mres,Gammares));
      }

      // determine thresholds (coannihilation thresholds will be added later);
      //   lowest threshold = 2*WIMP rest mass  (unlike DS convention!)
      result.threshold_energy.push_back(2*mWIMP);
      std::string thrlist[] = {"W+","Z0","t"};
      int thrmax=sizeof(thrlist) / sizeof(thrlist[0]);
      double mthr;
      for (int i=0; i<thrmax; i++)
      {
        mthr = std::abs(SMspec.get(Par::Pole_Mass,thrlist[i]));
        if (mthr > mWIMP)
        {
          result.threshold_energy.push_back(2*mthr);
        }
      }

    } // function RD_spectrum_MSSM



    /*! \brief Collects spectrum information about coannihilating particles,
     *         resonances and threshold energies -- directly from DarkSUSY 5.
     */
    void RD_spectrum_SUSY_DS5(RD_spectrum_type &result)
    {
      using namespace Pipes::RD_spectrum_SUSY_DS5;

      std::vector<int> colist; //potential coannihilating particles (indices)
      colist.clear();

      // Neutralino DM is self-conjugate
      result.isSelfConj = true;
      // This function reports particle IDs in terms of internal DarkSUSY codes
      result.particle_index_type = "DarkSUSY";

      result.coannihilatingParticles.clear();
      result.resonances.clear();
      result.threshold_energy.clear();

      /// Option CoannCharginosNeutralinos<bool>: Specify whether charginos and
      /// neutralinos are included in coannihilations (default: true)
      bool CoannCharginosNeutralinos = runOptions->getValueOrDef<bool>(true,
          "CoannCharginosNeutralinos");

      /// Option CoannSfermions<bool>: Specify whether sfermions are included in
      /// coannihilations (default: true)
      bool CoannSfermions = runOptions->getValueOrDef<bool>(true,
          "CoannSfermions");

      /// Option CoannMaxMass<double>: Maximal sparticle mass to be included in
      /// coannihilations, in units of DM mass (default: 1.6)
      double CoannMaxMass = runOptions->getValueOrDef<double>(1.6,
          "CoannMaxMass");

      // introduce pointers to DS mass spectrum and relevant particle info
      DS5_PACODES *DSpart = BEreq::pacodes.pointer();
      DS5_MSPCTM *mymspctm= BEreq::mspctm.pointer();
      DS_INTDOF *myintdof= BEreq::intdof.pointer();

      // first add neutralino=WIMP=least massive 'coannihilating particle'
      result.coannihilatingParticles.push_back(
          RD_coannihilating_particle(DSpart->kn(1),
          myintdof->kdof(DSpart->kn(1)),mymspctm->mass(DSpart->kn(1))));

      #ifdef DARKBIT_DEBUG
        std::cout << "WIMP : "<< DSpart->kn(1) << " " <<
            myintdof->kdof(DSpart->kn(1)) << " " << mymspctm->mass(DSpart->kn(1))
            << std::endl;
      #endif

      // include  neutralino & chargino coannihilation
      if(CoannCharginosNeutralinos)
      {
        for (int i=2; i<=4; i++)
          colist.push_back(DSpart->kn(i));
        colist.push_back(DSpart->kcha(1));
        colist.push_back(DSpart->kcha(2));
      }

      // include sfermion coannihilation
      if(CoannSfermions)
      {
        for (int i=1; i<=6; i++)
          colist.push_back(DSpart->ksl(i));
        for (int i=1; i<=3; i++)
          colist.push_back(DSpart->ksnu(i));
        for (int i=1; i<=6; i++)
          colist.push_back(DSpart->ksqu(i));
        for (int i=1; i<=6; i++)
          colist.push_back(DSpart->ksqd(i));
      }

      // only keep sparticles that are not too heavy
      for (size_t i=0; i<colist.size(); i++)
        if (mymspctm->mass(colist[i])/mymspctm->mass(DSpart->kn(1))
            < CoannMaxMass)
          result.coannihilatingParticles.push_back(
              RD_coannihilating_particle(colist[i], myintdof->kdof(colist[i]),
              mymspctm->mass(colist[i])));


      // determine resonances for LSP annihilation
      int reslist[] = {BEreq::DS5particle_code("Z0"),
                       BEreq::DS5particle_code("h0_2"),
                       BEreq::DS5particle_code("h0_1"),
                       BEreq::DS5particle_code("A0"),
                       BEreq::DS5particle_code("W+"),
                       BEreq::DS5particle_code("H+")};
      int resmax=sizeof(reslist) / sizeof(reslist[0]);
      // the last 2 resonances in the list can only appear for coannihilations
      if (result.coannihilatingParticles.size() == 1)
        resmax -= 2;
      // (Turns out resonances are never returned with DS5)

      // determine thresholds; lowest threshold = 2*WIMP rest mass  (unlike DS
      // convention!)
      result.threshold_energy.push_back(
          2*result.coannihilatingParticles[0].mass);
      int thrlist[] = {BEreq::DS5particle_code("W+"),
                       BEreq::DS5particle_code("Z0"),
                       BEreq::DS5particle_code("u_3")};
      int thrmax=sizeof(thrlist) / sizeof(thrlist[0]);
      for (int i=0; i<thrmax; i++)
        if (mymspctm->mass(thrlist[i])>result.coannihilatingParticles[0].mass)
          result.threshold_energy.push_back(2*mymspctm->mass(thrlist[i]));

    } // function RD_spectrum_SUSY_DS5


   /*! \brief Collects information about resonances and threshold energies
     *        directly from the ProcessCatalog
     *        [NB: this assumes no coannihilating particles!]
     */
    void RD_spectrum_from_ProcessCatalog(RD_spectrum_type &result)
    {
      using namespace Pipes::RD_spectrum_from_ProcessCatalog;

      // retrieve annihilation processes and DM properties
      std::string DMid= *Dep::DarkMatter_ID;
      std::string DMbarid = *Dep::DarkMatterConj_ID;
      TH_Process annihilation =
              (*Dep::TH_ProcessCatalog).getProcess(DMid, DMbarid);
      TH_ParticleProperty DMproperty =
              (*Dep::TH_ProcessCatalog).getParticleProperty(DMid);

      // Is DM self-conjugate ?
      result.isSelfConj = annihilation.isSelfConj;
      // This function reports particle IDs in terms of internal DarkSUSY codes
      // NB: This should eventually be changed to PDG, which however requires updating
      //     all existing examples where the invariant rate (entering in the relic density)
      //     is calculated directly from the ProcessCatalogue!
      result.particle_index_type = "DarkSUSY";


      // get thresholds & resonances from process catalog
      result.resonances = annihilation.resonances_thresholds.resonances;
      result.threshold_energy = annihilation.resonances_thresholds.threshold_energy;

      result.coannihilatingParticles.clear();
      // add WIMP=least massive 'coannihilating particle'
      // NB: particle code (1st entry) is irrelevant (unless Weff is obtained from DS)
      result.coannihilatingParticles.push_back(
          RD_coannihilating_particle(100,1+DMproperty.spin2,DMproperty.mass));

      #ifdef DARKBIT_DEBUG
        std::cout << "DM dof = " << 1+ DMproperty.spin2 << std::endl;
        // std::cout << "Test : " << BEreq::particle_code("d_3")
        //           << " " << BEreq::particle_code("u_3") << std::endl;
      #endif


    } // function RD_spectrum_from_ProcessCatalog


    /*! \brief Order RD_spectrum object and derive coannihilation thresholds.
    */
    void RD_spectrum_ordered_func(RD_spectrum_type &result)
    {
      using namespace Pipes::RD_spectrum_ordered_func;

      result = *Dep::RD_spectrum;

      // NB: coannihilatingParticles does not necessarily have to be ordered,
      // but it is assumed that coannihilatingParticles[0] is the DM particle
      RD_coannihilating_particle tmp_co;
      if (result.coannihilatingParticles.size() > 1)
        for (std::size_t i=0; i<result.coannihilatingParticles.size()-1; i++)
        {
          for (std::size_t j=i+1; j<result.coannihilatingParticles.size(); j++)
          {
          if (result.coannihilatingParticles[j].mass<result.coannihilatingParticles[i].mass)
            {
              tmp_co=result.coannihilatingParticles[i];
              result.coannihilatingParticles[i]=result.coannihilatingParticles[j];
              result.coannihilatingParticles[j]=tmp_co;
            }
          }
        }


      // add coannihilation thresholds
      if (result.coannihilatingParticles.size() > 1)
      {
        for (int i=0; i<(int)result.coannihilatingParticles.size(); i++)
        {
          for (int j=std::max(1,i); j<(int)result.coannihilatingParticles.size(); j++)
          {
            result.threshold_energy.push_back(
             result.coannihilatingParticles[i].mass+result.coannihilatingParticles[j].mass);
          }
        }
      }
      //and order all thresholds
      double tmp;
      for (std::size_t i=0; i<result.threshold_energy.size()-1; i++)
      {
        for (std::size_t j=i+1; j<result.threshold_energy.size(); j++)
        {
          if (result.threshold_energy[j]<result.threshold_energy[i])
          {
            tmp=result.threshold_energy[i];
            result.threshold_energy[i]=result.threshold_energy[j];
            result.threshold_energy[j]=tmp;
          }
        }
      }

      if (!result.resonances.empty()){
        TH_Resonance tmp2;
        for (std::size_t i=0; i<result.resonances.size()-1; i++)
        {
          for (std::size_t j=i+1; j<result.resonances.size(); j++)
          {
            if (result.resonances[j].energy < result.resonances[i].energy)
            {
              tmp2=result.resonances[i];
              result.resonances[i]=result.resonances[j];
              result.resonances[j]=tmp2;
            }
          }
        }
      }
    } // function RD_spectrum_ordered_func


    /*! \brief Some helper function to prepare evaluation of Weff from
     *         DarkSUSY 5.
     */
    void RD_annrate_DS5prep_func(int &result)
    {
      using namespace Pipes::RD_annrate_DS5prep_func;

      // Read out coannihilating particles from RDspectrum.
      RD_spectrum_type specres = *Dep::RD_spectrum;

      if ( specres.particle_index_type != "DarkSUSY" )
      {
        invalid_point().raise("RD_annrate_DS5prep_func is only optimized for use with "
         "DarkSUSY5 and requires internal particle IDs. Try RD_annrate_DSprep_MSSM_func instead!");
      }

      //write model-dependent info about coannihilating particles to DS common blocks
      DS5_RDMGEV myrdmgev;
      myrdmgev.nco = specres.coannihilatingParticles.size();
      for (int i=1; i<=myrdmgev.nco; i++)
      {
        myrdmgev.mco(i)=fabs(specres.coannihilatingParticles[i-1].mass);
        myrdmgev.mdof(i)=specres.coannihilatingParticles[i-1].degreesOfFreedom;
        myrdmgev.kcoann(i)=specres.coannihilatingParticles[i-1].index;
      }

      double tmp; int itmp;
      for (int i=1; i<=myrdmgev.nco-1; i++)
      {
        for (int j=i+1; j<=myrdmgev.nco; j++)
        {
          if (myrdmgev.mco(j)<myrdmgev.mco(i))
          {
            tmp=myrdmgev.mco(i);
            myrdmgev.mco(i)=myrdmgev.mco(j);
            myrdmgev.mco(j)=tmp;
            itmp=myrdmgev.mdof(i);
            myrdmgev.mdof(i)=myrdmgev.mdof(j);
            myrdmgev.mdof(j)=itmp;
            itmp=myrdmgev.kcoann(i);
            myrdmgev.kcoann(i)=myrdmgev.kcoann(j);
            myrdmgev.kcoann(j)=itmp;
          }
        }
      #ifdef DARKBIT_RD_DEBUG
        std::cout << "DS5prep - co : "<< myrdmgev.kcoann(i) << " " <<
            myrdmgev.mco(i) << " " << myrdmgev.mdof(i)
            << std::endl;
      #endif
      }
      #ifdef DARKBIT_RD_DEBUG
        std::cout << "DS5prep - co : "<< myrdmgev.kcoann(myrdmgev.nco) << " " <<
            myrdmgev.mco(myrdmgev.nco) << " " << myrdmgev.mdof(myrdmgev.nco)
            << std::endl;
      #endif

      *BEreq::rdmgev = myrdmgev;

      result=1; // everything OK

    } // function RD_annrate_DS5prep_func


    /*! \brief Some helper function to prepare evaluation of Weff from
     *         DarkSUSY 6.
     */
    void RD_annrate_DSprep_MSSM_func(int &result)
    {
      using namespace Pipes::RD_annrate_DSprep_MSSM_func;

      // Read out coannihilating particles from RDspectrum_ordered.
      RD_spectrum_type specres = *Dep::RD_spectrum_ordered;

      if (specres.particle_index_type != "DarkSUSY" && specres.particle_index_type != "PDG")
      {
        invalid_point().raise("RD_annrate_DSprep_MSSM_func requires PDG or internal DS codes!");
      }

      //write model-dependent info about coannihilating particles to DS common blocks
      // Note: translation from PDG codes assumes for consistency context integer = 0 here
      // (as done in RD_spectrum_MSSM)
      int ContInt = 0;
      DS_DSANCOANN mydsancoann;
      mydsancoann.nco = specres.coannihilatingParticles.size();
      int partID;
      for (int i=1; i<=mydsancoann.nco; i++)
      {
        mydsancoann.mco(i)=fabs(specres.coannihilatingParticles[i-1].mass);
        mydsancoann.mdof(i)=specres.coannihilatingParticles[i-1].degreesOfFreedom;
        partID = specres.coannihilatingParticles[i-1].index;
        mydsancoann.kco(i) = partID;
        if (specres.particle_index_type == "PDG")
        {
           mydsancoann.kco(i) = BEreq::DSparticle_code(Models::ParticleDB().long_name(partID,ContInt));
        };
        #ifdef DARKBIT_RD_DEBUG
          std::cout << "DS6prep_MSSM - co : "<< partID << " " << mydsancoann.kco(i) << " " <<
              mydsancoann.mco(i) << " " << mydsancoann.mdof(i)
              << std::endl;
        #endif
      }

      *BEreq::dsancoann = mydsancoann;

      result=1; // everything OK

    } // function RD_eff_annrate_DSprep_MSSM_func


    /*! \brief Get Weff directly from initialized DarkSUSY.
     * Note that these functions do not (and should not) correct Weff for
     * non-self-conjugate dark matter.
    */
    void RD_eff_annrate_DS_MSSM(double(*&result)(double&))
    {
      using namespace Pipes::RD_eff_annrate_DS_MSSM;

      if (BEreq::dsanwx.origin() == "DarkSUSY_MSSM")
      {
        result=BEreq::dsanwx.pointer();
      }
      else DarkBit_error().raise(LOCAL_INFO, "Wrong DarkSUSY backend initialized?");
    } // function RD_eff_annrate_DS_MSSM

    void RD_eff_annrate_DS5_MSSM(double(*&result)(double&))
    {
      using namespace Pipes::RD_eff_annrate_DS5_MSSM;

      if (BEreq::dsanwx.origin() == "DarkSUSY")
      {
        result=BEreq::dsanwx.pointer();
      }
      else DarkBit_error().raise(LOCAL_INFO, "Wrong DarkSUSY backend initialized?");
    } // function RD_eff_annrate_DS5_MSSM



    /*! \brief Infer Weff from process catalog.
    */
    // Carries pointer to Weff
    DEF_FUNKTRAIT(RD_EFF_ANNRATE_FROM_PROCESSCATALOG_TRAIT)
      void RD_eff_annrate_from_ProcessCatalog(double(*&result)(double&))
      {
        using namespace Pipes::RD_eff_annrate_from_ProcessCatalog;

        std::string DMid= *Dep::DarkMatter_ID;
        std::string DMbarid = *Dep::DarkMatterConj_ID;
        TH_Process annProc = (*Dep::TH_ProcessCatalog).getProcess(DMid, DMbarid);
        double mDM = (*Dep::TH_ProcessCatalog).getParticleProperty(DMid).mass;

        auto Weff = daFunk::zero("peff");
        auto peff = daFunk::var("peff");
        auto s = 4*(peff*peff + mDM*mDM);

        // Individual contributions to the invariant rate Weff. Note that no
        // symmetry factor of 1/2 for non-identical initial state particles
        // (non-self-conjugate DM) should appear here. This factor does explicitly
        // enter, however, when calculating the relic density in RD_oh2_DS_general.
        for (std::vector<TH_Channel>::iterator it = annProc.channelList.begin();
            it != annProc.channelList.end(); ++it)
        {
          Weff = Weff +
            it->genRate->set("v", 2*peff/sqrt(mDM*mDM+peff*peff))*s/gev2tocm3s1;
        }
        // Add genRateMisc to Weff
        Weff = Weff + annProc.genRateMisc->set("v", 2*peff/sqrt(mDM*mDM+peff*peff))*s/gev2tocm3s1;
        if ( Weff->getNArgs() != 1 )
          DarkBit_error().raise(LOCAL_INFO,
              "RD_eff_annrate_from_ProcessCatalog: Wrong number of arguments.\n"
              "The probable cause are three-body final states, which are not supported for this function."
              );
        result = Weff->plain<RD_EFF_ANNRATE_FROM_PROCESSCATALOG_TRAIT>("peff");
      } // function RD_eff_annrate_from_ProcessCatalog


    /*! \brief General routine for calculation of relic density, using DarkSUSY 6+
     *         Boltzmann solver
     *
     *  Requires:
     *  - RD_thresholds_resonances from RD_spectrum_ordered
     *  - RD_eff_annrate (Weff)
     */
    void RD_oh2_DS_general(double &result)
    {
      using namespace Pipes::RD_oh2_DS_general;

      // Retrieve ordered list of resonances and thresholds from
      // RD_thresholds_resonances.
      RD_spectrum_type myRDspec = *Dep::RD_spectrum_ordered;
      if (myRDspec.coannihilatingParticles.empty())
      {
        DarkBit_error().raise(LOCAL_INFO, "RD_oh2_DS_general: No DM particle!");
      }
      double mwimp=myRDspec.coannihilatingParticles[0].mass;

      // What follows below implements dsrdomega from DarkSUSY 6+
      //We start by setting some general common block settings
      BEreq::dsrdcom();
      DS_RDPARS *myrdpars = BEreq::rdpars.pointer();

      /// Option fast<int>: Numerical performance of Boltzmann solver in DS
      /// (default: 1) [NB: accurate is fast = 0 !]
      int fast = runOptions->getValueOrDef<int>(1, "fast");

      /// Option timeout<double>: Maximum core time to allow for relic density
      /// calculation, in seconds (default: 600s)
      BEreq::rdtime->rdt_max = runOptions->getValueOrDef<double>(600, "timeout");

      switch (fast)
      {
        case 0:
          myrdpars->cosmin=0.996195;myrdpars->waccd=0.005;myrdpars->dpminr=1.0e-4;
          myrdpars->dpthr=5.0e-4;myrdpars->wdiffr=0.05;myrdpars->wdifft=0.02;
          break;
        case 1:
          myrdpars->cosmin=0.996195;myrdpars->waccd=0.05;myrdpars->dpminr=5.0e-4;
          myrdpars->dpthr=2.5e-3;myrdpars->wdiffr=0.5;myrdpars->wdifft=0.1;
          break;
        default:
          DarkBit_error().raise(LOCAL_INFO, "Invalid fast flag (should be 0 or 1). Fast > 1 not yet "
           "supported in DarkBit::RD_oh2_DS_general.  Please add relevant settings to this routine.");
      }

      // now transfer information from myRDspec to DS common blocks
      int tnco=myRDspec.coannihilatingParticles.size();
      int tnrs=myRDspec.resonances.size();
      int tnthr=myRDspec.threshold_energy.size();
      double tmco[1000], tdof[1000], trm[1000], trw[1000], ttm[1000];
      for (std::size_t i=0; i<((unsigned int)tnco); i++)
      {
        tmco[i] = myRDspec.coannihilatingParticles[i].mass;
        tdof[i] = myRDspec.coannihilatingParticles[i].degreesOfFreedom;
        #ifdef DARKBIT_RD_DEBUG
          std::cout << "RD_oh2_DS_general - co : "<< tmco[i]  << " " << tdof[i] << std::endl;
        #endif
      }
      for (std::size_t i=0; i<((unsigned int)tnrs); i++)
      {
        trm[i] = myRDspec.resonances[i].energy;
        trw[i] = myRDspec.resonances[i].width;
        #ifdef DARKBIT_RD_DEBUG
          std::cout << "RD_oh2_DS_general - res : "<< trm[i]  << " " << trw[i] << std::endl;
        #endif
      }
      //DS does not count 2* WIMP rest mass as thr, hence we start at i=1
      tnthr -=tnthr;
      for (std::size_t i=1; i<((unsigned int)tnthr+1); i++)
      {
        ttm[i] = myRDspec.threshold_energy[i];
        #ifdef DARKBIT_RD_DEBUG
          std::cout << "RD_oh2_DS_general - thr : "<< ttm[i] << std::endl;
        #endif
      }
      #ifdef DARKBIT_RD_DEBUG
        std::cout << "RD_oh2_DS_general - tnco,tnrs,tnthr : "<< tnco << " " << tnrs << " "
                  << tnthr << std::endl;
      #endif
      BEreq::dsrdstart(tnco,tmco,tdof,tnrs,trm,trw,tnthr,ttm);

      // always check that invariant rate is OK at least at one point
      double peff = mwimp/100;
      double weff = (*Dep::RD_eff_annrate)(peff);

      if (Utils::isnan(weff))
            DarkBit_error().raise(LOCAL_INFO, "Weff is NaN in RD_oh2_DS_general. This means that the function\n"
                                            "pointed to by RD_eff_annrate returned NaN for the invariant rate\n"
                                            "entering the relic density calculation.");

      // Finally use DS Boltzmann solver with invariant rate
      double oh2, xf;
      int ierr=0; int iwar=0;
      BEreq::dsrdens(byVal(*Dep::RD_eff_annrate),oh2,xf,fast,ierr,iwar);

      //Check for NAN result.
      if ( Utils::isnan(oh2) ) DarkBit_error().raise(LOCAL_INFO, "DarkSUSY returned NaN for relic density!");

      // Check whether DarkSUSY threw an error
      if (ierr == 1024)
      {
        invalid_point().raise("DarkSUSY invariant rate tabulation timed out.");
      }
      else if(ierr != 0)
      {
        DarkBit_error().raise(LOCAL_INFO, "DarkSUSY Boltzmann solver failed.");
      }

      // If the DM particles are not their own antiparticles we need to add the relic
      // density of anti-DM particles as well
      result = (myRDspec.isSelfConj) ? oh2 : 2*oh2;

      logger() << LogTags::debug << "RD_oh2_DS_general: oh2 =" << result << EOM;

      #ifdef DARKBIT_DEBUG
        std::cout << std::endl << "DM mass = " << mwimp<< std::endl;
        std::cout << "Oh2     = " << result << std::endl << std::endl;
      #endif

    } // function RD_oh2_DS_general



    /*! \brief General routine for calculation of relic density, using DarkSUSY 5
     *         Boltzmann solver
     *
     *  Requires:
     *  - RD_thresholds_resonances
     *  - RD_eff_annrate (Weff)
     */
    void RD_oh2_DS5_general(double &result)
    {
      using namespace Pipes::RD_oh2_DS5_general;

      // Retrieve ordered list of resonances and thresholds from
      // RD_thresholds_resonances.
      RD_spectrum_type myRDspec = *Dep::RD_spectrum_ordered;
      if (myRDspec.coannihilatingParticles.empty())
      {
        DarkBit_error().raise(LOCAL_INFO, "RD_oh2_DS5_general: No DM particle!");
      }
      double mwimp=myRDspec.coannihilatingParticles[0].mass;

      #ifdef DARKBIT_RD_DEBUG
        bool tbtest=false;
      #endif

      /// Option timeout<double>: Maximum core time to allow for relic density
      /// calculation, in seconds (default: 600s)
      BEreq::rdtime->rdt_max = runOptions->getValueOrDef<double>(600, "timeout");

      // What follows below is the standard accurate calculation of oh2 in DS, in one of the
      // following modes:
      //   fast =   0 - standard accurate calculation (accuracy better than 1%)
      //            1 - faster calculation: sets parameters for when to add
      //                extra points less tough to avoid excessively
      //                adding extra points, expected accurarcy: 1% or better
      //            2 - faster calculation: compared to fast=1, this option
      //                adds less points in Weff tabulation in general and
      //                is more elaborate in deciding when to include points
      //                close to thresholds and resonances
      //                expected accuracy: around 1%
      //            3 - even more aggressive on trying minimize the number
      //                of tabulated points
      //                expected accuracy: 5-10%
      //            9 - superfast. This method still makes sure to include
      //                resonances and threholds, but does not attempt to sample
      //                them very well. Should give an order of magnitude estimate
      //                expected accuracy: order of magnitude
      //           10 - quick and dirty method, i.e. expand the annihilation
      //                cross section in x (not recommended)
      //                expected accuracy: can be orders of magnitude wrong
      //                for models with strong resonances or thresholds

      DS_RDPARS myrdpars;
      /// Option fast<int>: Numerical performance of Boltzmann solver in DS
      /// (default: 1) [NB: accurate is fast = 0 !]
      int fast = runOptions->getValueOrDef<int>(1, "fast");
      switch (fast)
      {
        case 0:
          myrdpars.cosmin=0.996195;myrdpars.waccd=0.005;myrdpars.dpminr=1.0e-4;
          myrdpars.dpthr=5.0e-4;myrdpars.wdiffr=0.05;myrdpars.wdifft=0.02;
          break;
        case 1:
          myrdpars.cosmin=0.996195;myrdpars.waccd=0.05;myrdpars.dpminr=5.0e-4;
          myrdpars.dpthr=2.5e-3;myrdpars.wdiffr=0.5;myrdpars.wdifft=0.1;
          break;
        default:
          DarkBit_error().raise(LOCAL_INFO, "Invalid fast flag (should be 0 or 1). Fast > 1 not yet "
           "supported in DarkBit::RD_oh2_DS5_general.  Please add relevant settings to this routine.");
      }

      myrdpars.hstep=0.01;myrdpars.hmin=1.0e-9;myrdpars.compeps=0.01;
      myrdpars.xinit=2.0;myrdpars.xfinal=200.0;myrdpars.umax=10.0;
      myrdpars.cfr=0.5;
      *BEreq::rdpars = myrdpars;
      DS_RDSWITCH myrdswitch;
      myrdswitch.thavint=1;myrdswitch.rdprt=0;
      *BEreq::rdswitch = myrdswitch;
      DS_RDLUN myrdlun;
      myrdlun.rdlulog=6;myrdlun.rdluerr=6;
      *BEreq::rdlun = myrdlun;
      DS_RDPADD myrdpadd;
      myrdpadd.pdivr=2.0;myrdpadd.dpres=0.5;myrdpadd.nlow=20;
      myrdpadd.nhigh=10;
      myrdpadd.npres=4;myrdpadd.nthup=4;myrdpadd.cthtest=0;myrdpadd.spltest=1;
      *BEreq::rdpadd = myrdpadd;

      DS_RDERRORS myrderrors;
      myrderrors.rderr=0;myrderrors.rdwar=0;myrderrors.rdinit=1234;
      *BEreq::rderrors = myrderrors;

      // write mass and dof of DM & coannihilating particle to DS common blocks
      DS5_RDMGEV *myrdmgev = BEreq::rdmgev.pointer();

      myrdmgev->nco=myRDspec.coannihilatingParticles.size();
      for (std::size_t i=1; i<=((unsigned int)myrdmgev->nco); i++)
      {
        myrdmgev->mco(i)=myRDspec.coannihilatingParticles[i-1].mass;
        myrdmgev->mdof(i)=myRDspec.coannihilatingParticles[i-1].degreesOfFreedom;
        myrdmgev->kcoann(i)=myRDspec.coannihilatingParticles[i-1].index;
        #ifdef DARKBIT_RD_DEBUG
          std::cout << "kcoann, mco, mdof: " << myrdmgev->kcoann(i) << "  " << myrdmgev->mco(i)
                    << "  " << myrdmgev->mdof(i) << std::endl;
        #endif
      }

      // write information about thresholds and resonances to DS common blocks
      // [this is the model-independent part of dsrdstart]
      myrdmgev->nres=0;
      if (!myRDspec.resonances.empty())
      {
        myrdmgev->nres=myRDspec.resonances.size();
        for (std::size_t i=1; i<=myRDspec.resonances.size(); i++)
        {
          myrdmgev->rgev(i)=myRDspec.resonances[i-1].energy;
          myrdmgev->rwid(i)=myRDspec.resonances[i-1].width;
          #ifdef DARKBIT_RD_DEBUG
            std::cout << "rgev, rwid: " << myrdmgev->rgev(i) << "  " << myrdmgev->rwid(i) << std::endl;
          #endif
        }
      }
      // convert to momenta and write to DS common blocks
      DS_RDPTH myrdpth;
      // NB: DS does not count 2* WIMP rest mass as thr
      myrdpth.nth=myRDspec.threshold_energy.size()-1;
      myrdpth.pth(0)=0; myrdpth.incth(0)=1;
      for (std::size_t i=1; i<myRDspec.threshold_energy.size(); i++)
      {
        myrdpth.pth(i)=sqrt(pow(myRDspec.threshold_energy[i],2)/4-pow(mwimp,2));
        myrdpth.incth(i)=1;
        #ifdef DARKBIT_RD_DEBUG
          std::cout << "pth, incth: " << myrdpth.pth(i) << "  " << myrdpth.incth(i) << std::endl;
        #endif
      }
      *BEreq::rdpth = myrdpth;

      // determine starting point for integration of Boltzmann eq and write
      // to DS common blocks
      DS_RDDOF *myrddof = BEreq::rddof.pointer();
      double xstart=std::max(myrdpars.xinit,1.0001*mwimp/myrddof->tgev(1));
      double tstart=mwimp/xstart;
      int k; myrddof->khi=myrddof->nf; myrddof->klo=1;
      while (myrddof->khi > myrddof->klo+1)
      {
        k=(myrddof->khi+myrddof->klo)/2;
        if (myrddof->tgev(k) < tstart)
        {
          myrddof->khi=k;
        }
        else {
          myrddof->klo=k;
        }
      }

      // follow wide res treatment for heavy Higgs adopted in DS
      double widthheavyHiggs = BEreq::widths->width(BEreq::DS5particle_code("h0_2"));
      if (widthheavyHiggs<0.1) BEreq::widths->width(BEreq::DS5particle_code("h0_2"))=0.1;

      // always check that invariant rate is OK at least at one point
      double peff = mwimp/100;
      double weff = (*Dep::RD_eff_annrate)(peff);
      if (Utils::isnan(weff))
            DarkBit_error().raise(LOCAL_INFO, "Weff is NaN in RD_oh2_DS5_general. This means that the function\n"
                                            "pointed to by RD_eff_annrate returned NaN for the invariant rate\n"
                                            "entering the relic density calculation.");

      #ifdef DARKBIT_RD_DEBUG
        // Dump Weff info on screen
        std::cout << "xstart = " << xstart << std::endl;
        for ( peff = mwimp/1000;  peff < mwimp; peff = peff*1.5 )
        {
          weff = (*Dep::RD_eff_annrate)(peff);
          std::cout << "Weff(" << peff << ") = " << weff << std::endl;
          // Check that the invariant rate is OK.
          if (Utils::isnan(weff))
            DarkBit_error().raise(LOCAL_INFO, "RD debug: Weff is NaN in RD_oh2_DS5_general.");
        }
        // Set up timing
        std::chrono::time_point<std::chrono::system_clock> start, end;
        start = std::chrono::system_clock::now();
        logger() << "Tabulating RD_eff_annrate..." << EOM;
        std::cout << "Starting dsrdtab..." << std::endl;
      #endif

      // Tabulate the invariant rate
      BEreq::dsrdtab(byVal(*Dep::RD_eff_annrate),xstart,fast);

      #ifdef DARKBIT_RD_DEBUG
        logger() << LogTags::repeat_to_cout << "...done!" << EOM;

        // Get runtime
        end = std::chrono::system_clock::now();
        double runtime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        // Check if runtime too long
        if ( runtime > 30. )
        {
          std::cout << "Duration [ms]: " << runtime << std::endl;
          //SLHAstruct mySLHA = Dep::MSSM_spectrum->getSLHAea(2);
          //std::ofstream ofs("RelicDensity_debug.slha");
          //ofs << mySLHA;
          //ofs.close();
          tbtest=true;
        }
      #endif

      // Check whether DarkSUSY threw an error
      if (BEreq::rderrors->rderr != 0)
      {
        if (BEreq::rderrors->rderr == 1024) invalid_point().raise("DarkSUSY invariant rate tabulation timed out.");
        else DarkBit_error().raise(LOCAL_INFO, "DarkSUSY invariant rate tabulation failed.");
      }

      // determine integration limit
      BEreq::dsrdthlim();

      // now solve Boltzmann eqn using tabulated rate
      double xend, yend, xf; int nfcn;
      BEreq::dsrdeqn(byVal(BEreq::dsrdwintp.pointer()), xstart,xend,yend,xf,nfcn);
      // using the untabulated rate gives the same result but is usually
      // slower:
      // BEreq::dsrdeqn(byVal(*Dep::RD_eff_annrate),xstart,xend,yend,xf,nfcn);

      // change heavy Higgs width in DS back to standard value
      BEreq::widths->width(BEreq::DS5particle_code("h0_2")) = widthheavyHiggs;

      //Check for NAN result.
      if ( Utils::isnan(yend) ) DarkBit_error().raise(LOCAL_INFO, "DarkSUSY returned NaN for relic density!");

      // Check whether DarkSUSY threw some other error
      if (BEreq::rderrors->rderr != 0) DarkBit_error().raise(LOCAL_INFO, "DarkSUSY Boltzmann solver failed.");

      result = 0.70365e8*myrddof->fh(myrddof->nf)*mwimp*yend;

      // If the DM particles are not their own antiparticles we need to add the relic
      // density of anti-DM particles as well
      result = (myRDspec.isSelfConj) ? result : 2*result;

      logger() << LogTags::debug << "RD_oh2_DS5_general: oh2 =" << result << EOM;

      #ifdef DARKBIT_DEBUG
        std::cout << std::endl << "DM mass = " << mwimp<< std::endl;
        std::cout << "Oh2     = " << result << std::endl << std::endl;
      #endif

      #ifdef DARKBIT_RD_DEBUG
        if (tbtest) exit(1);
      #endif

    } // function RD_oh2_DS5_general




    //////////////////////////////////////////////////////////////////////////
    //
    //             Simple relic density routines for cross-checks
    //                      (MicrOmegas vs DarkSUSY)
    //
    //////////////////////////////////////////////////////////////////////////

    /*! \brief Relic density directly from a call of initialized MicrOmegas.
    */
    void RD_oh2_Xf_MicrOmegas(ddpair &result)
    {
      using namespace Pipes::RD_oh2_Xf_MicrOmegas;
      // Input
      int fast;     // fast: 1, accurate: 0
      double Beps;  // Beps=1e-5 recommended, Beps=1 switches coannihilation off

      // Set options via ini-file (MicrOmegas-specific performance options)
      fast = runOptions->getValueOrDef<int>(0, "fast");
      Beps = runOptions->getValueOrDef<double>(1e-5, "Beps");

      logger() << LogTags::debug << "Using fast: " << fast << " Beps: " << Beps;

      // Output
      double Xf;
      double oh2 = BEreq::oh2(&Xf,byVal(fast), byVal(Beps));

      result.first = oh2;
      result.second = Xf;

      logger() << LogTags::debug << "X_f = " << Xf << " Omega h^2 = " << oh2 << EOM;
    }

    /*! \brief Relic density directly from a call of initialized DarkSUSY 5.
    */
    void RD_oh2_DarkSUSY_DS5(double &result)
    {
      using namespace Pipes::RD_oh2_DarkSUSY_DS5;
      // Input
      int omtype;  // 0: no coann; 1: all coann
      int fast;  // 0: standard; 1: fast; 2: dirty

      // Set options via ini-file
      /// Option omtype<int>: 0 no coann, 1 all coann (default 1)
      omtype = runOptions->getValueOrDef<int>(1, "omtype");
      /// Option fast<int>: 0 standard, 1 fast, 2 dirty (default 0)
      fast = runOptions->getValueOrDef<int>(0, "fast");
      /// Option timeout<double>: Maximum core time to allow for relic density
      /// calculation, in seconds (default: 600s)
      BEreq::rdtime->rdt_max = runOptions->getValueOrDef<double>(600, "timeout");

      // Output
      double xf;  // freeze-out temperature
      int ierr;  // error flag
      int iwar;  // warming flag
      int nfc;  // number of fnct calls to effective annihilation cross section
      logger() << LogTags::debug << "Starting DarkSUSY relic density calculation..." << EOM;
      double oh2 = BEreq::dsrdomega(omtype,fast,xf,ierr,iwar,nfc);

      // Check whether DarkSUSY threw an error
      if (BEreq::rderrors->rderr != 0)
      {
        if (BEreq::rderrors->rderr == 1024) invalid_point().raise("DarkSUSY invariant rate tabulation timed out.");
        else DarkBit_error().raise(LOCAL_INFO, "DarkSUSY relic density calculation failed.");
      }

      result = oh2;
      logger() << LogTags::debug << "RD_oh2_DarkSUSY_DS5: oh2 is " << oh2 << EOM;
    }



    void RD_oh2_MicrOmegas(double &result)
    {
      using namespace Pipes::RD_oh2_MicrOmegas;

      ddpair oh2_Xf = *Dep::RD_oh2_Xf;
      result = oh2_Xf.first;
    }

    void Xf_MicrOmegas(double &result)
    {
      using namespace Pipes::Xf_MicrOmegas;

      ddpair oh2_Xf = *Dep::RD_oh2_Xf;
      result = oh2_Xf.second;
    }


    void print_channel_contributions_MicrOmegas(double &result)
    {
      using namespace Pipes::print_channel_contributions_MicrOmegas;

      double Beps;  // Beps=1e-5 recommended, Beps=1 switches coannihilation off
      Beps = runOptions->getValueOrDef<double>(1e-5, "Beps");

      double Xf = *Dep::Xf;

      double cut = runOptions->getValueOrDef<double>(1e-5, "cut");

      result = BEreq::momegas_print_channels(byVal(Xf),byVal(cut),byVal(Beps),byVal(1),byVal(stdout));
    }


    void get_semi_ann_MicrOmegas(double &result)
    {
      using namespace Pipes::get_semi_ann_MicrOmegas;

      double Beps;  // Beps=1e-5 recommended, Beps=1 switches coannihilation off
      Beps = runOptions->getValueOrDef<double>(1e-5, "Beps");

      double Xf = *Dep::Xf;

      char*n1 =  (char *)"~SS";
      char*n2 = (char *)"~SS";
      char*n3 = (char *)"h";
      char*n4 = (char *)"~ss";

      result = BEreq::get_oneChannel(byVal(Xf),byVal(Beps),byVal(n1),byVal(n2),byVal(n3),byVal(n4));

    }

    /// Return the thermally averaged cross-section at T_freezeout
    void vSigma_freezeout_MicrOmegas(double &result)
    {
      using namespace Pipes::vSigma_freezeout_MicrOmegas;

      // Beps=1e-5 recommended, Beps=1 switches coannihilation off
      double Beps = runOptions->getValueOrDef<double>(1e-5, "Beps");

      // Xf = m_WIMP/T_freezeout
      double Xf = *Dep::Xf;
      double mwimp = *Dep::mwimp;

      // Get sigma*v at T_freezeout [pb]
      double sigmav = BEreq::vSigma(byVal(Xf/mwimp), byVal(Beps), byVal(1));

      result = sigmav*1e-36*s2cm;
    }



    //////////////////////////////////////////////////////////////////////////
    //
    //   Infer fraction of Dark matter that is made up by scanned DM particles
    //
    //////////////////////////////////////////////////////////////////////////

    void RD_fraction_one(double &result)
    {
      result = 1.0;
      logger() << LogTags::debug << "Fraction of dark matter that the scanned model accounts for: " << result << EOM;
    }

    void RD_fraction_leq_one(double &result)
    {
      using namespace Pipes::RD_fraction_leq_one;
      /// Option oh2_obs<double>: Set reference dark matter density (Oh2) for this module function (default 0.1188)
      double oh2_obs = runOptions->getValueOrDef<double>(0.1188, "oh2_obs");
      double oh2_theory = *Dep::RD_oh2;
      result = std::min(1., oh2_theory/oh2_obs);
      logger() << LogTags::debug << "Fraction of dark matter that the scanned model accounts for: " << result << EOM;
    }

    void RD_fraction_rescaled(double &result)
    {
      using namespace Pipes::RD_fraction_rescaled;
      /// Option oh2_obs<double>: Set reference dark matter density (Oh2) for this module function (default 0.1188)
      double oh2_obs = runOptions->getValueOrDef<double>(0.1188, "oh2_obs");
      double oh2_theory = *Dep::RD_oh2;
      result = oh2_theory/oh2_obs;
      logger() << LogTags::debug << "Fraction of dark matter that the scanned model accounts for: " << result << EOM;
    }

    void RD_fraction_rescaled_LCDM(double &result)
    {
      using namespace Pipes::RD_fraction_rescaled_LCDM;

      double oh2_obs = *Param["omega_b"];
      double oh2_theory = *Dep::RD_oh2;

      result = oh2_theory/oh2_obs;
      logger() << LogTags::debug << "Fraction of dark matter that the scanned model accounts for: " << result << EOM;
    }

  }
}
