//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Implementation of energy injection routines.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Patrick Stoecker
///          (stoecker@physik.rwth-aachen.de)
///  \date 2021 Mar
///
///  *********************************************

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/DarkBit/DarkBit_rollcall.hpp"
#include "gambit/DarkBit/DarkBit_utils.hpp"

namespace Gambit
{

  namespace DarkBit
  {

    void DarkMatter_ID_AnnihilatingDM_mixture(std::string & result) { result = "DM"; }
    void DarkMatterConj_ID_AnnihilatingDM_mixture(std::string & result) { result = "DM"; }

    void DarkMatter_ID_DecayingDM_mixture(std::string & result) { result = "DM"; }
    void DarkMatterConj_ID_DecayingDM_mixture(std::string & result) { result = "DM"; }

    /// The energy injection spectrum from the ProcessCatalog and FCMC.
    void energy_injection_spectrum_ProcessCatalog(DarkAges::Energy_injection_spectrum& spectrum)
    {
      using namespace Pipes::energy_injection_spectrum_ProcessCatalog;

      // Delete the spectrum of the previous iteration
      spectrum.E_el.clear();
      spectrum.E_ph.clear();
      spectrum.spec_el.clear();
      spectrum.spec_ph.clear();

      // Do we have annihilation or decay?
      const std::string proc = *Dep::DM_process;
      const bool isAnnihilation = (proc == "annihilation");

      // What is the dark matter particle?
      const std::string DMid = *Dep::DarkMatter_ID;
      const std::string DMbarid = *Dep::DarkMatterConj_ID;

      // Get the ProcessCatalog
      auto& catalog = *Dep::TH_ProcessCatalog;

      // Mass of the dark matter particle (in GeV)
      const double m = catalog.getParticleProperty(DMid).mass;

      // Energy for spectrum.E_el and spectrum.E_ph
      const double Emax = isAnnihilation ? m : 0.5*m;
      const double Emin = Emax * pow(10, (-1.)*(runOptions->getValueOrDef<double>(5.0,"num_decades")));
      const int resolution = runOptions->getValueOrDef<int>(250,"resolution");

      // Retrieve the yields. Electrons and positrons are treated as one species.
      daFunk::Funk positronElectronYield = (*Dep::electron_Yield) + (*Dep::positron_Yield);
      daFunk::Funk gammaYield = (*Dep::GA_Yield);

      // For "annihilation", need to perform the v=0 limit
      if (isAnnihilation)
      {
        positronElectronYield = positronElectronYield->set("v",0.0);
        gammaYield = gammaYield->set("v",0.0);
      }

      TH_Process process(isAnnihilation ? catalog.getProcess(DMid, DMbarid) : catalog.getProcess(DMid));

      // Loop over all channels to calculate the total rate
      double totalRate = 0.0;
      for(auto& it: process.channelList)
      {
        daFunk::Funk rateFunk = it.genRate;

        // For annihilation, consider the v=0 limit
        if (rateFunk->hasArg("v"))
          rateFunk = rateFunk->set("v",0.);

        // Calculate the rate
        double rate = rateFunk->bind()->eval();

        // Add to totalRate
        totalRate = totalRate + rate;
      }

      // Rescale totalRate by the correct kinematic factor and normalise the yields
      if (totalRate > 0.0)
      {
        if (isAnnihilation)
        {
          const double k = (process.isSelfConj) ? 1. : 0.5;
          totalRate *= k/(m*m);
        }
        else
        {
          totalRate /= m;
        }

        positronElectronYield = positronElectronYield / totalRate;
        gammaYield = gammaYield / totalRate;
      }

      // Define the underlying energy axes (kinetic energies)
      // Extend above Emax such that resolved monochromatic lines are included.
      std::vector<double> Ekin = daFunk::logspace(log10(Emin), log10(2.*Emax), resolution);

      // The Yields within GAMBIT are w.r.t. 'E' (total energy).
      // whereas DarkAges expects them w.r.t. 'Ekin' (kinetic energy)
      //
      // 1) Create copies of Ekin
      std::vector<double> E_el(Ekin.begin(), Ekin.end());
      std::vector<double> E_ph(Ekin.begin(), Ekin.end());
      // 2) Shift E_el by m_electron
      for (auto& it: E_el)
        it += m_electron;
      // 3) Resolve singularities in E (if any)
      E_el = daFunk::augmentSingl(E_el, positronElectronYield);
      E_ph = daFunk::augmentSingl(E_ph, gammaYield);
      // 4) Sample the spectra dNdE
      spectrum.spec_el = positronElectronYield->bind("E")->vect(E_el);
      spectrum.spec_ph = gammaYield->bind("E")->vect(E_ph);
      // 5) Shift back
      for (auto& it: E_el)
        it -= m_electron;
      // 6) Set spectrum.E_el and spectrum.E_ph
      spectrum.E_el = std::vector<double>(E_el.begin(), E_el.end());
      spectrum.E_ph = std::vector<double>(E_ph.begin(), E_ph.end());

    }

    /// Set up process catalog for AnnihilatingDM_mixture
    void TH_ProcessCatalog_AnnihilatingDM_mixture(TH_ProcessCatalog& result)
    {
      using namespace Pipes::TH_ProcessCatalog_AnnihilatingDM_mixture;

      double m = *Param["mass"];
      double BR_el = *Param["BR_el"];
      double BR_ph = *Param["BR_ph"];
      double sigmav = *Param["sigmav"];

      // Debug info
      logger() << LogTags::debug << "Creating \'TH_ProcessCatalog\' for \'AnnihilatingDM_mixture\'\n\n";
      logger() << "- Branching fraction into e+/e-: " << BR_el;
      logger() << "\n- Branching fraction into photons: " << BR_ph;
      logger() << "\n- Branching fraction into inefficient final state: " << 1 - BR_ph - BR_el << "\n" << EOM;

      // Sanity checks
      if (BR_el + BR_ph > 1.0)
      {
        std::ostringstream err;
        err << "The sum of the branching fractions into electrons and photons (BR_el and BR_ph) must not exceed 1.";
        DarkBit_error().raise(LOCAL_INFO,err.str());
      }

      if (m <= m_electron && BR_el >= std::numeric_limits<double>::epsilon())
      {
        std::ostringstream err;
        err << "The mass of the annihilating dark matter candidate is below the electron mass.";
        err << " No production of e+/e- is possible.";
        DarkBit_error().raise(LOCAL_INFO,err.str());
      }

      // Initialize empty catalog and main annihilation process
      TH_ProcessCatalog catalog;
      TH_Process process_ann("DM","DM");

      // Explicitly state that DM particle is self-conjugate
      process_ann.isSelfConj = true;

      ///////////////////////////////////////
      // Import particle masses and couplings
      ///////////////////////////////////////

      #define addParticle(Name, Mass, spinX2) \
      catalog.particleProperties.insert(std::pair<std::string, TH_ParticleProperty> (Name , TH_ParticleProperty(Mass, spinX2)));

      addParticle("gamma", 0.0, 2)
      addParticle("e+_1", m_electron, 1)
      addParticle("e-_1", m_electron, 1)

      addParticle("nu_e", 0.0, 1)
      addParticle("nubar_e", 0.0, 1)

      addParticle("DM", m, 0)
      #undef addParticle

      // Add annihilation channels
      TH_Channel ann_channel_phot(daFunk::vec<std::string>("gamma", "gamma"), daFunk::cnst(BR_ph * sigmav)*daFunk::one("v"));
      process_ann.channelList.push_back(ann_channel_phot);

      TH_Channel ann_channel_elec(daFunk::vec<std::string>("e+_1", "e-_1"), daFunk::cnst(BR_el * sigmav)*daFunk::one("v"));
      process_ann.channelList.push_back(ann_channel_elec);

      TH_Channel ann_channel_nu(daFunk::vec<std::string>("nu_e", "nubar_e"), daFunk::cnst((1.-BR_ph-BR_el) * sigmav)*daFunk::one("v"));
      process_ann.channelList.push_back(ann_channel_nu);

      // Add annihilation process to the catalog
      catalog.processList.push_back(process_ann);

      // Validate
      catalog.validate();

      result = catalog;
    }

    /// Set up process catalog for DecayingDM_mixture
    void TH_ProcessCatalog_DecayingDM_mixture(TH_ProcessCatalog& result)
    {
      using namespace Pipes::TH_ProcessCatalog_DecayingDM_mixture;

      double m = *Param["mass"];
      double BR_el = *Param["BR_el"];
      double BR_ph = *Param["BR_ph"];
      double Gamma = hbar / (*Param["lifetime"]);

      // Debug info
      logger() << LogTags::debug << "Creating \'TH_ProcessCatalog\' for \'DecayingDM_mixture\'\n\n";
      logger() << "- Branching fraction into e+/e-: " << BR_el;
      logger() << "\n- Branching fraction into photons: " << BR_ph;
      logger() << "\n- Branching fraction into inefficient final state: " << 1 - BR_ph - BR_el << "\n" << EOM;

      // Sanity checks
      if (BR_el + BR_ph > 1.0)
      {
        std::ostringstream err;
        err << "The sum of the branching fractions into electrons and photons (BR_el and BR_ph) must not exceed 1.";
        DarkBit_error().raise(LOCAL_INFO,err.str());
      }

      if (m <= 2*m_electron && BR_el >= std::numeric_limits<double>::epsilon())
      {
        std::ostringstream err;
        err << "The mass of the decaying dark matter candidate is below twice the electron mass.";
        err << " No production of e+/e- is possible.";
        DarkBit_error().raise(LOCAL_INFO,err.str());
      }

      // Initialize empty catalog and main decay process
      TH_ProcessCatalog catalog;
      TH_Process process_dec("DM");

      ///////////////////////////////////////
      // Import particle masses and couplings
      ///////////////////////////////////////

      #define addParticle(Name, Mass, spinX2) \
      catalog.particleProperties.insert(std::pair<std::string, TH_ParticleProperty> (Name , TH_ParticleProperty(Mass, spinX2)));

      addParticle("gamma", 0.0, 2)
      addParticle("e+_1", m_electron, 1)
      addParticle("e-_1", m_electron, 1)

      addParticle("nu_e", 0.0, 1)
      addParticle("nubar_e", 0.0, 1)

      addParticle("DM", m, 0)
      #undef addParticle

      // Add decay channels
      TH_Channel dec_channel_phot(daFunk::vec<std::string>("gamma", "gamma"), daFunk::cnst(BR_ph * Gamma));
      process_dec.channelList.push_back(dec_channel_phot);

      TH_Channel dec_channel_elec(daFunk::vec<std::string>("e+_1", "e-_1"), daFunk::cnst(BR_el * Gamma));
      process_dec.channelList.push_back(dec_channel_elec);

      TH_Channel dec_channel_nu(daFunk::vec<std::string>("nu_e", "nubar_e"), daFunk::cnst((1.-BR_ph-BR_el) * Gamma));
      process_dec.channelList.push_back(dec_channel_nu);

      // Add decay process to the catalog
      catalog.processList.push_back(process_dec);

      // Validate
      catalog.validate();

      result = catalog;
    }

  }

}
