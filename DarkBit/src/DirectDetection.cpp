//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Routines for direct detection couplings and
///  likelihoods.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Christopher Savage
///          (chris@savage.name)
///  \date 2014 Oct
///  \date 2015 Jan, Feb, June
///
///  \author Jonathan Cornell
///          (jcornell@ucsc.edu)
///  \date 2015 Mar
///
///  \author Felix Kahlhoefer
///          (felix.kahlhoefer@desy.de)
///  \date 2016 August
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2015--2018
///
///  \author Sebastian Wild
///          (sebastian.wild@desy.de)
///  \date 2017 October, November
///
///  \author Ankit Beniwal
///          (ankit.beniwal@adelaide.edu.au)
///  \date 2018 August
///
///  \author Sanjay Bloor
///          (sanjay.bloor12@imperial.ac.uk)
///  \date 2020 Feb
///
///  *********************************************

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/DarkBit/DarkBit_rollcall.hpp"

namespace Gambit
{
  namespace DarkBit
  {

    //////////////////////////////////////////////////////////////////////////
    //
    //                 Direct detection couplings
    //
    //////////////////////////////////////////////////////////////////////////

    /*! \brief Get direct detection couplings from initialized DarkSUSY.
    */
    void DD_couplings_DarkSUSY(DM_nucleon_couplings &result)
    {
      using namespace Pipes::DD_couplings_DarkSUSY;

      double fG;

      // Set proton hadronic matrix elements
      BEreq::ddcom->ftp(7)  = *Param["fpu"];
      BEreq::ddcom->ftp(8)  = *Param["fpd"];
      BEreq::ddcom->ftp(10) = *Param["fps"];

      fG = 2./27.*(1. - *Param["fpu"] - *Param["fpd"] - *Param["fps"]);
      BEreq::ddcom->ftp(9) = fG;
      BEreq::ddcom->ftp(11) = fG;
      BEreq::ddcom->ftp(12) = fG;

      logger() << LogTags::debug << "DarkSUSY proton hadronic matrix elements set to:" << endl;
      logger() << LogTags::debug << "ftp(7) = fpu = " << BEreq::ddcom->ftp(7);
      logger() << LogTags::debug << "\tftp(8) = fpd = " << BEreq::ddcom->ftp(8);
      logger() << LogTags::debug << "\tftp(10) = fps = " << BEreq::ddcom->ftp(10) << endl;
      logger() << LogTags::debug << "ftp(9) = ftp(11) = ftp(12) = 2/27 fG = " <<
        BEreq::ddcom->ftp(9) << EOM;

      // Set neutron hadronic matrix elements
      BEreq::ddcom->ftn(7)  = *Param["fnu"];
      BEreq::ddcom->ftn(8)  = *Param["fnd"];
      BEreq::ddcom->ftn(10) = *Param["fns"];

      fG = 2./27.*(1. - *Param["fnu"] - *Param["fnd"] - *Param["fns"]);
      BEreq::ddcom->ftn(9) = fG;
      BEreq::ddcom->ftn(11) = fG;
      BEreq::ddcom->ftn(12) = fG;

      logger() << LogTags::debug << "DarkSUSY neutron hadronic matrix elements set to:" << endl;
      logger() << LogTags::debug << "ftn(7) = fnu = " << BEreq::ddcom->ftn(7);
      logger() << LogTags::debug << "\tftn(8) = fnd = " << BEreq::ddcom->ftn(8);
      logger() << LogTags::debug << "\tftn(10) = fns = " << BEreq::ddcom->ftn(10) << endl;
      logger() << LogTags::debug << "ftn(9) = ftn(11) = ftn(12) = 2/27 fG = " <<
        BEreq::ddcom->ftn(9) << EOM;

      // Set deltaq
      BEreq::ddcom->delu = *Param["deltau"];
      BEreq::ddcom->deld = *Param["deltad"];
      BEreq::ddcom->dels = *Param["deltas"];
      logger() << LogTags::debug << "DarkSUSY delta q set to:" << endl;
      logger() << LogTags::debug << "delu = delta u = " << BEreq::ddcom->delu;
      logger() << LogTags::debug << "\tdeld = delta d = " << BEreq::ddcom->deld;
      logger() << LogTags::debug << "\tdels = delta s = " << BEreq::ddcom->dels << EOM;


      // Loop corrections and pole removal.

      // Option loop<bool>: If true, include 1-loop effects discussed in
      // Drees Nojiri Phys.Rev. D48 (1993) 3483-3501 (default: true)
      BEreq::ddcom->dddn = runOptions->getValueOrDef<bool>(true,"loop");

      // Option pole<bool>: If true, include pole in nuclear scattering cross-section.
      // If false, approximate squark propagator as 1/m_sq^2 (default: false)
      BEreq::ddcom->ddpole = runOptions->getValueOrDef<bool>(false,"pole");

      // Some version notes:
      // The default in DS5 is to for both these options to be false (tree-level cross-section with pole removed).
      // The default in DS6 is to use Drees-Nojiri (1 loop) with the pole removed, which isn't an
      // option in the official DS5.1.3.  The version in GAMBIT is patched to implement this option though,
      // so we use it as the default here.


      if (*Dep::DarkSUSY_PointInit)
      {
        // Calling DarkSUSY subroutine dsddgpgn(gps,gns,gpa,gna)
        // to set all four couplings.
        BEreq::dsddgpgn(result.gps, result.gns, result.gpa, result.gna);
        double factor =
        /// Option rescale_couplings<double>: Rescaling factor for WIMP-nucleon couplings (default 1.)
          runOptions->getValueOrDef<double>(1., "rescale_couplings");
        result.gps *= factor;
        result.gns *= factor;
        result.gpa *= factor;
        result.gna *= factor;
        logger() << LogTags::debug << "DarkSUSY dsddgpgn gives:" << std::endl;
        logger() << LogTags::debug << " gps = " << result.gps << std::endl;
        logger() << LogTags::debug << " gns = " << result.gns << std::endl;
        logger() << LogTags::debug << " gpa = " << result.gpa << std::endl;
        logger() << LogTags::debug << " gna = " << result.gna << EOM;
      }
      else
      {
        // Set couplings to zero if DarkSUSY point initialization
        // was not successful
        result.gps = 0.0; result.gns = 0.0;
        result.gpa = 0.0; result.gna = 0.0;
        logger() << "DarkSUSY point initialization failed:" << std::endl;
        logger() << " couplings set to zero." << EOM;
      }
    }

    /*! \brief Get direct detection couplings from initialized MicrOmegas.
    */
    void DD_couplings_MicrOmegas(DM_nucleon_couplings &result)
    {
      using namespace Pipes::DD_couplings_MicrOmegas;

      // Set proton hadronic matrix elements.
      BEreq::MOcommon->par[2] = *Param["fpd"];
      BEreq::MOcommon->par[3] = *Param["fpu"];
      BEreq::MOcommon->par[4] = *Param["fps"];

      logger() << LogTags::debug << "micrOMEGAs proton hadronic matrix elements set to:" << endl;
      logger() << LogTags::debug << "ScalarFFPd = fpd = " << BEreq::MOcommon->par[2];
      logger() << LogTags::debug << "\tScalarFFPu = fpu = " << BEreq::MOcommon->par[3];
      logger() << LogTags::debug << "\tScalarFFPs = fps = " << BEreq::MOcommon->par[4] << EOM;

      // Set neutron hadronic matrix elements.
      BEreq::MOcommon->par[11] = *Param["fnd"];
      BEreq::MOcommon->par[12] = *Param["fnu"];
      BEreq::MOcommon->par[13] = *Param["fns"];

      logger() << LogTags::debug << "micrOMEGAs neutron hadronic matrix elements set to:" << endl;
      logger() << LogTags::debug << "ScalarFFNd = fnd = " << BEreq::MOcommon->par[11];
      logger() << LogTags::debug << "\tScalarFFNu = fnu = " << BEreq::MOcommon->par[12];
      logger() << LogTags::debug << "\tScalarFFNs = fns = " << BEreq::MOcommon->par[13] << EOM;

      //Set delta q.
      BEreq::MOcommon->par[5] = *Param["deltad"];
      BEreq::MOcommon->par[6] = *Param["deltau"];
      BEreq::MOcommon->par[7] = *Param["deltas"];

      BEreq::MOcommon->par[14] = *Param["deltau"];
      BEreq::MOcommon->par[15] = *Param["deltad"];
      BEreq::MOcommon->par[16] = *Param["deltas"];

      logger() << LogTags::debug << "micrOMEGAs delta q set to:" << endl;
      logger() << LogTags::debug << "pVectorFFPd = pVectorFFNu = delta d = "
        << BEreq::MOcommon->par[5] << endl;
      logger() << LogTags::debug << "pVectorFFPu = pVectorFFPd = delta u = "
        << BEreq::MOcommon->par[6] << endl;
      logger() << LogTags::debug << "pVectorFFPs = pVectorFFNs = delta s = "
        << BEreq::MOcommon->par[7] << EOM;

      double p1[2], p2[2], p3[2], p4[2];
      int error;
      if (runOptions->getValueOrDef<bool>(true, "box"))
        error = BEreq::nucleonAmplitudes(byVal(BEreq::FeScLoop.pointer()),
          byVal(p1), byVal(p2), byVal(p3), byVal(p4));
      else error = BEreq::nucleonAmplitudes(NULL,
              byVal(p1), byVal(p2), byVal(p3), byVal(p4));
      if(error!=0)
        DarkBit_error().raise(LOCAL_INFO,
            "micrOMEGAs nucleonAmplitudes function failed with "
            "error code " + std::to_string(error) + ".");

      // Rescaling to agree with DarkSUSY convention:
      result.gps = p1[0]*2;
      result.gpa = p2[0]*2;
      result.gns = p3[0]*2;
      result.gna = p4[0]*2;

      logger() << LogTags::debug << "micrOMEGAs nucleonAmplitudes gives:" << endl;
      logger() << LogTags::debug << " gps: " << result.gps << endl;
      logger() << LogTags::debug << " gns: " << result.gns << endl;
      logger() << LogTags::debug << " gpa: " << result.gpa << endl;
      logger() << LogTags::debug << " gna: " << result.gna << EOM;
    }

    /// Simple calculator of the spin-independent WIMP-proton cross-section
    void sigma_SI_p_simple(double &result)
    {
      using namespace Pipes::sigma_SI_p_simple;
      double gps = Dep::DD_couplings->gps;
      double reduced_mass = *Dep::mwimp * m_proton / (*Dep::mwimp + m_proton);
      result = gev2cm2/pi*pow(reduced_mass*gps,2.0);
    }

    /// Simple calculator of the spin-independent WIMP-neutron cross-section
    void sigma_SI_n_simple(double &result)
    {
      using namespace Pipes::sigma_SI_n_simple;
      double gns = Dep::DD_couplings->gns;
      double reduced_mass = *Dep::mwimp * m_neutron / (*Dep::mwimp + m_neutron);
      result = gev2cm2/pi*pow(reduced_mass*gns,2.0);
    }

    /// Simple calculator of the spin-dependent WIMP-proton cross-section
    void sigma_SD_p_simple(double &result)
    {
      using namespace Pipes::sigma_SD_p_simple;
      double gpa = Dep::DD_couplings->gpa;
      double reduced_mass = *Dep::mwimp * m_proton / (*Dep::mwimp + m_proton);
      result = 3.0*gev2cm2/pi*pow(reduced_mass*gpa,2.0);
    }

    /// Simple calculator of the spin-dependent WIMP-neutron cross-section
    void sigma_SD_n_simple(double &result)
    {
      using namespace Pipes::sigma_SD_n_simple;
      double gna = Dep::DD_couplings->gna;
      double reduced_mass = *Dep::mwimp * m_neutron / (*Dep::mwimp + m_neutron);
      result = 3.0*gev2cm2/pi*pow(reduced_mass*gna,2.0);
    }

    /// Calculation of SI and SD cross sections at a reference momentum q0
    /// for the fermionic Higgs portal models
    void sigma_SI_vnqn(map_intpair_dbl &result)
    {
      using namespace Pipes::sigma_SI_vnqn;

      double q0 = 0.04; // reference momentum transfer: 40 MeV
      double gps = Dep::DD_couplings_fermionic_HP->gps;
      double gpq2 = Dep::DD_couplings_fermionic_HP->gp_q2;
      double reduced_mass = *Dep::mwimp * m_proton / (*Dep::mwimp + m_proton);

      result[std::make_pair(0,0)] =   gev2cm2/pi*pow(reduced_mass*gps,2.0);
      result[std::make_pair(-2,0)] =  0.0;
      result[std::make_pair(2,0)] =   gev2cm2/pi*pow(reduced_mass*gpq2,2.0)*pow(q0/(*Dep::mwimp)/2.0,2.0);
      result[std::make_pair(4,0)] =   0.0;
      result[std::make_pair(0,-2)] =  0.0;
      result[std::make_pair(0,2)] =   0.0;
      result[std::make_pair(0,4)] =   0.0;
    }

    void sigma_SD_vnqn(map_intpair_dbl &result)
    {
      using namespace Pipes::sigma_SD_vnqn;

      result[std::make_pair(0,0)] =   0.0;
      result[std::make_pair(-2,0)] =  0.0;
      result[std::make_pair(2,0)] =   0.0;
      result[std::make_pair(4,0)] =   0.0;
      result[std::make_pair(0,-2)] =  0.0;
      result[std::make_pair(0,2)] =   0.0;
      result[std::make_pair(0,4)] =   0.0;
    }


    //////////////////////////////////////////////////////////////////////////
    //
    //          Direct detection rate and likelihood routines
    //
    //////////////////////////////////////////////////////////////////////////

    /// Defines a prototypical DDCalc result extractor
    #define DDCALC_RESULT(EXPERIMENT, TYPE, NAME)                                  \
    void CAT_3(EXPERIMENT,_Get,NAME)(TYPE &result)                                 \
    {                                                                              \
      using namespace Pipes::CAT_3(EXPERIMENT,_Get,NAME);                          \
      TYPE temp_result = BEreq::CAT(DD_,NAME)(BEreq::DD_Experiment(STRINGIFY(EXPERIMENT)));  \
      if (Utils::isnan(temp_result))                                               \
      {                                                                            \
        /* DarkBit_error().raise(LOCAL_INFO, "Got NaN value from DDCalc."); */     \
        /* TODO: Raise a proper error here -- NaNs should be fixed. */             \
        invalid_point().raise("Got NaN value from DDCalc! This need fixing!");     \
      }                                                                            \
      result = temp_result;                                                        \
    }

    #define DDCALC_BIN(EXPERIMENT, TYPE, NAME)                                     \
    void CAT_3(EXPERIMENT,_GetBin,NAME)(std::vector<double> &result)               \
    {                                                                              \
      using namespace Pipes::CAT_3(EXPERIMENT,_GetBin,NAME);                       \
      result.clear();                                                              \
      int nbins;                                                                   \
      nbins = BEreq::DD_Bins(BEreq::DD_Experiment(STRINGIFY(EXPERIMENT)));         \
      for (int ibin=1;ibin<=nbins;ibin++) {                                        \
        result.push_back(                                                          \
        BEreq::CAT(DD_Bin,NAME)(BEreq::DD_Experiment(STRINGIFY(EXPERIMENT)),ibin)); } \
    }

    /// Defines functions to perform the DDCalc internal rate calculations,
    /// and extract the results and log likelihoods, for the designated experiment.
    #define DD_EX(EXPERIMENT)                                                      \
      /* Calculations */                                                           \
      void CAT(EXPERIMENT,_Calc)(bool &result)                                     \
      {                                                                            \
        using namespace Pipes::CAT(EXPERIMENT,_Calc);                              \
        BEreq::DD_CalcRates(BEreq::DD_Experiment(STRINGIFY(EXPERIMENT)));          \
        result = true;                                                             \
      }                                                                            \
      /* Results */                                                                \
      DDCALC_RESULT(EXPERIMENT, int,    Events)                                    \
      DDCALC_RESULT(EXPERIMENT, double, Background)                                \
      DDCALC_RESULT(EXPERIMENT, double, Signal)                                    \
      DDCALC_RESULT(EXPERIMENT, double, SignalSI)                                  \
      DDCALC_RESULT(EXPERIMENT, double, SignalSD)                                  \
      DDCALC_RESULT(EXPERIMENT, int,    Bins)                                      \
      DDCALC_RESULT(EXPERIMENT, double, LogLikelihood)                             \
      DDCALC_BIN(EXPERIMENT, int,    Events)                                       \
      DDCALC_BIN(EXPERIMENT, double, Background)                                   \
      DDCALC_BIN(EXPERIMENT, double, Signal)                                       \

    // Experiments
    DD_EX(XENON100_2012)        // Aprile et al., PRL 109, 181301 (2013) [arxiv:1207.5988]
    DD_EX(XENON1T_2017)         // Aprile et al., PRL 119, 181301 (2017) [arxiv:1705.06655]
    DD_EX(XENON1T_2018)         // Aprile et al., May 28 talk at Gran Sasso.
    DD_EX(DARWIN)               // M. Schumann et al., [arXiv:1506.08309]
    DD_EX(LUX_2013)             // Akerib et al., PRL 112, 091303 (2014) [arxiv:1310.8214]
    DD_EX(LUX_2015)             // D.S. Akerib et al., PRL 116, 161301 (2016) [arXiv:1512.03506]
    DD_EX(LUX_2016)             // D.S. Akerib et al., PRL 118, 021303 (2017) [arxiv:1608.07648]
    DD_EX(LZ)                   // LZ TDR, [arXiv:1509.02910]
    DD_EX(PandaX_2016)          // A. Tan et al., PRL 117, 121303 (2016) [arxiv:1607.07400]
    DD_EX(PandaX_2017)          // X. Cui et al., PRL 119, 181302 (2017) [arxiv:1708.06917]
    DD_EX(DarkSide_50)          // P. Agnes et al., [arXiv:1802.07198]
    DD_EX(DarkSide_50_S2)       // P. Agnes et al., [arXiv:1802.06994]
    DD_EX(CRESST_II)            // G. Angloher et al., [arXiv:1509.01515]
    DD_EX(CRESST_III)           // G. Angloher et al., [arXiv:1904.00498]
    DD_EX(SuperCDMS_2014)       // Agnese et al., PRL 112, 241302 (2014) [arxiv:1402.7137]
    DD_EX(CDMSlite)             // Agnese et al., PRL 116, 071301 (2015) [arxiv:1509.02448]
    DD_EX(SIMPLE_2014)          // Felizardo et al., PRD 89, 072013 (2014) [arxiv:1404.4309]
    DD_EX(PICO_2L)              // C. Amole et al., PRD 93, 061101 (2016) [arXiv:1601.03729]
    DD_EX(PICO_60_F)            // C. Amole et al., PRD 93, 052014 (2016) [arXiv:1510.07754]
    DD_EX(PICO_60_I)            // C. Amole et al., PRD 93, 052014 (2016) [arXiv:1510.07754]
    DD_EX(PICO_60)              // C. Amole et al., PRD 93, 052014 (2016) [arXiv:1510.07754]
    DD_EX(PICO_60_2017)         // C. Amole et al., arXiv:1702.07666
    DD_EX(PICO_60_2019)         // C. Amole et al., arXiv:1902.04031
    DD_EX(PICO_500)             // S. Fallows, talk at TAUP 2017

    // Just in case, to make sure we don't mess with other things elsewhere.
    #undef DD_EX

  }
}
