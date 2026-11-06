//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend source for SusHi 1.7.0
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ida-Marie Fauske Johansson
///  \date 2026 Apr
///
///  \author Anders Kvellestad
///  \date 2026 Nov
///
///  *********************************************

#include "gambit/Backends/frontend_macros.hpp"
#include "gambit/Backends/frontends/SusHi_1_7_0.hpp"
#include "gambit/Utils/mpiwrapper.hpp"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <cmath>
#include <stdexcept>
#include <string>
#include <vector>
#include <utility>

// Convenience functions (definitions)
BE_NAMESPACE
{
  /// Keeps a copy, in SLHA form, of every entry handed to SusHi for the
  /// current point, so that the exact input can optionally be written to a
  /// file and fed to a standalone SusHi for cross-checks.
  class SLHAInputRecord
  {
    public:
      void add(const std::string& block, const std::string& entry, const std::string& comment)
      {
        if (blocks.empty() || blocks.back().first != block) blocks.push_back({block, {}});
        blocks.back().second.push_back(entry + "   # " + comment);
      }
      void write(const std::string& filename) const
      {
        std::ofstream ofs(filename);
        if (!ofs) backend_error().raise(LOCAL_INFO, "Could not open file " + filename + " for writing.");
        ofs << "# SusHi 1.7.0 input, exactly as handed to SusHi in memory by GAMBIT (SusHi_run_point)." << std::endl;
        for (const auto& b : blocks)
        {
          ofs << "Block " << b.first << std::endl;
          for (const auto& l : b.second) ofs << "  " << l << std::endl;
        }
      }
    private:
      std::vector<std::pair<std::string, std::vector<std::string>>> blocks;
  };

  /// Format a double with enough digits to be read back bit-for-bit.
  std::string fmt(double v)
  {
    std::ostringstream os;
    os << std::setprecision(17) << v;
    return os.str();
  }

  /// Look up a user option by name in 'opts', the yaml options of the module
  /// function that calls SusHi_run_point.  If the user did not set the
  /// option, return the default value given by the caller instead.
  double get_option(const map_str_dbl& opts, const std::string& key, double default_value)
  {
    if (opts.find(key) == opts.end())
    {
      return default_value;
    }
    return opts.at(key);
  }

  /// Same as get_option, for options that are integers.
  int get_int_option(const map_str_dbl& opts, const std::string& key, int default_value)
  {
    double value = get_option(opts, key, default_value);
    return (int) std::lround(value);
  }

  /// Set all of SusHi's "this SLHA entry was given" flags to .false.
  /// SusHi's readinsushi does this itself at the start of a file-based run.
  void clear_slha_flags()
  {
    // Every member is a plain 4-byte Fortran LOGICAL (array), so zeroing the
    // storage of the whole common block sets every flag to .false.
    std::memset(static_cast<void*>(&(*slhalogical)), 0, sizeof(SusHi_slhalogical_type));
  }

  /// Number of points run so far in this process (used to name debug files).
  int n_points_run = 0;


  /// Runs SusHi's gg->h and bb->h NNLO cross-section computation for a
  /// single point, given an MSSM spectrum.  This is called directly from
  /// module functions.
  ///
  /// Recognised keys in opts (all optional; defaults in brackets):
  ///   sqrts [13000]                centre-of-mass energy in GeV           (Block SUSHI 4)
  ///   ggh_order [2], bbh_order [2] 0=LO, 1=NLO, 2=NNLO                    (Block SUSHI 5, 6)
  ///   ew_ggh [1]                   EW corrections to ggh: 0=off, 1=light quarks at NLO, 2=SM EW factor (Block SUSHI 7)
  ///   sushi_verbose [0]            SusHi screen output: 0=silent, 1=normal (Block SUSHI 19)
  ///   mur_ggh [1], muf_ggh [mur_ggh], mur_bbh [mur_ggh], muf_bbh [muf_ggh]
  ///                                renormalisation/factorisation scales in units of mh (Block SCALES 1, 2, 11, 12)
  ///   renormbot_mb [0]             m_b for the bottom Yukawa: 0=OS, 1=MSbar(mb), 2=MSbar(muR) (Block RENORMBOT 1)
  ///   renormbot_tanb_resum [1]     tan(beta) resummation of Y_b: 0=no, 1=naive, 2=full (Block RENORMBOT 2)
  ///   yukawa_factor_c/t/b/st/sb [1] multiplicative factors for the c, t, b, stop and sbottom
  ///                                Yukawa couplings (Block FACTORS 1-5)
  ///   pdf_member [0]               PDF set member (Block PDFSPEC 10)
  ///   vegas_nlo_points [5000], vegas_nlo_iter [5]                 VEGAS settings for the NLO part (Block VEGAS 1, 2)
  ///   vegas_ggh_nnlo_points [5000], vegas_ggh_nnlo_iter [5]       ggh@nnlo, first run  (Block VEGAS 4, 5)
  ///   vegas_ggh_nnlo_points2 [2000], vegas_ggh_nnlo_iter2 [2]     ggh@nnlo, second run (Block VEGAS 14, 15)
  ///   vegas_bbh_nnlo_points [5000], vegas_bbh_nnlo_iter [5]       bbh@nnlo, first run  (Block VEGAS 7, 8)
  ///   vegas_bbh_nnlo_points2 [2000], vegas_bbh_nnlo_iter2 [2]     bbh@nnlo, second run (Block VEGAS 17, 18)
  ///   vegas_reseed [1]             reset SusHi's random number generator before each point, so that each
  ///                                point's result is independent of the points run before it in the same
  ///                                process and identical to that of a standalone SusHi run on the same input
  ///   write_slha_input [0]         write the input of each point to an SLHA file
  ///                                SusHi_1_7_0_input_rank<R>_point<N>.slha in the working directory
  ///                                (debugging aid: feed it to the standalone SusHi binary to cross-check)
  void SusHi_run_point(const Spectrum& mySpec, const map_str_dbl& opts, double& ggh_result, double& bbh_result, double& ggh_err, double& bbh_err)
  {
    // Record of the entries handed to SusHi, in SLHA form.
    SLHAInputRecord rec;

    // Helpers that set an entry of one of SusHi's SLHA common-block arrays,
    // flag it as given, and record it.  The arrays are indexed as in Fortran.
    auto set_real = [&rec](const char* block, auto& arr, auto& flags, int i, double v, const char* comment)
    {
      arr(i) = v;
      flags(i) = 1;
      rec.add(block, std::to_string(i) + "  " + fmt(v), comment);
    };
    auto set_int = [&rec](const char* block, auto& arr, auto& flags, int i, int v, const char* comment)
    {
      arr(i) = v;
      flags(i) = 1;
      rec.add(block, std::to_string(i) + "  " + std::to_string(v), comment);
    };

    // Forget whatever the previous point left in SusHi's input blocks.
    clear_slha_flags();

    // ---------------------------------------------------------------------
    // Block SUSHI: model, Higgs state, collider, orders
    // ---------------------------------------------------------------------
    // Entries other than 4 are read as integers by SusHi; SusHi stores all of
    // them in the real array sushipar.
    set_int ("SUSHI", slhaparam->sushipar, slhalogical->lsushipar,  1, 1,                        "model: 1 = MSSM");
    set_int ("SUSHI", slhaparam->sushipar, slhalogical->lsushipar,  2, 11,                       "Higgs: 11 = h (lightest CP-even)");
    set_int ("SUSHI", slhaparam->sushipar, slhalogical->lsushipar,  3, 0,                        "collider: 0 = pp");
    set_real("SUSHI", slhaparam->sushipar, slhalogical->lsushipar,  4, get_option(opts, "sqrts", 13000.0),   "centre-of-mass energy [GeV]");
    set_int ("SUSHI", slhaparam->sushipar, slhalogical->lsushipar,  5, get_int_option(opts, "ggh_order", 2),     "order ggh: 0 = LO, 1 = NLO, 2 = NNLO");
    set_int ("SUSHI", slhaparam->sushipar, slhalogical->lsushipar,  6, get_int_option(opts, "bbh_order", 2),     "order bbh: 0 = LO, 1 = NLO, 2 = NNLO");
    set_int ("SUSHI", slhaparam->sushipar, slhalogical->lsushipar,  7, get_int_option(opts, "ew_ggh", 1),        "EW for ggh: 0 = off, 1 = light quarks at NLO, 2 = SM EW factor");
    set_int ("SUSHI", slhaparam->sushipar, slhalogical->lsushipar, 19, get_int_option(opts, "sushi_verbose", 0), "output: 0 = silent, 1 = normal");

    // ---------------------------------------------------------------------
    // Block SMINPUTS: from the spectrum's SM inputs
    // ---------------------------------------------------------------------
    const SMInputs& sm = mySpec.get_SMInputs();
    set_real("SMINPUTS", slhaparam->sminputs, slhalogical->lsminputs, 1, sm.alphainv, "alpha_em^(-1)(MZ) SM MSbar");
    set_real("SMINPUTS", slhaparam->sminputs, slhalogical->lsminputs, 2, sm.GF,       "G_Fermi");
    set_real("SMINPUTS", slhaparam->sminputs, slhalogical->lsminputs, 3, sm.alphaS,   "alpha_s(MZ) SM MSbar");
    set_real("SMINPUTS", slhaparam->sminputs, slhalogical->lsminputs, 4, sm.mZ,       "m_Z(pole)");
    set_real("SMINPUTS", slhaparam->sminputs, slhalogical->lsminputs, 5, sm.mBmB,     "m_b(m_b)");
    set_real("SMINPUTS", slhaparam->sminputs, slhalogical->lsminputs, 6, sm.mT,       "m_t(pole)");
    set_real("SMINPUTS", slhaparam->sminputs, slhalogical->lsminputs, 7, sm.mTau,     "m_tau(pole)");
    set_real("SMINPUTS", slhaparam->sminputs, slhalogical->lsminputs, 8, sm.mCmC,     "m_c(m_c)");

    // ---------------------------------------------------------------------
    // Block MINPAR: tan(beta)
    // ---------------------------------------------------------------------
    set_real("MINPAR", slhaparam->minpar, slhalogical->lminpar, 3, mySpec.get(Par::dimensionless, "tanbeta"), "tan(beta)");

    // ---------------------------------------------------------------------
    // Block EXTPAR: gluino mass parameter, mu, third-generation squark sector.
    // SusHi takes these as its MSSM input (it derives the stop/sbottom masses
    // and mixings from them itself; see Block RENORMSBOT below).  GAMBIT keeps
    // M3 in MSOFT and the trilinears as TYu/TYd, so convert explicitly.
    // ---------------------------------------------------------------------
    {
      const double M3_val  = mySpec.get(Par::mass1, "M3");
      const double mu_val  = mySpec.get(Par::mass1, "Mu");
      const double Yu33    = mySpec.get(Par::dimensionless, "Yu", 3, 3);
      const double TYu33   = mySpec.get(Par::mass1, "TYu", 3, 3);
      const double Yd33    = mySpec.get(Par::dimensionless, "Yd", 3, 3);
      const double TYd33   = mySpec.get(Par::mass1, "TYd", 3, 3);
      const double At_val  = (Yu33 != 0.0) ? TYu33 / Yu33 : 0.0;
      const double Ab_val  = (Yd33 != 0.0) ? TYd33 / Yd33 : 0.0;
      const double mQ3_val = std::sqrt(std::abs(mySpec.get(Par::mass2, "mq2", 3, 3)));
      const double mU3_val = std::sqrt(std::abs(mySpec.get(Par::mass2, "mu2", 3, 3)));
      const double mD3_val = std::sqrt(std::abs(mySpec.get(Par::mass2, "md2", 3, 3)));
      set_real("EXTPAR", slhaparam->extpar, slhalogical->lextpar,  3, M3_val,  "M3 gluino mass parameter");
      set_real("EXTPAR", slhaparam->extpar, slhalogical->lextpar, 11, At_val,  "At stop trilinear");
      set_real("EXTPAR", slhaparam->extpar, slhalogical->lextpar, 12, Ab_val,  "Ab sbottom trilinear");
      set_real("EXTPAR", slhaparam->extpar, slhalogical->lextpar, 23, mu_val,  "mu parameter");
      set_real("EXTPAR", slhaparam->extpar, slhalogical->lextpar, 43, mQ3_val, "mQ3 3rd-gen squark doublet mass");
      set_real("EXTPAR", slhaparam->extpar, slhalogical->lextpar, 46, mU3_val, "mU3 3rd-gen up-type squark singlet mass");
      set_real("EXTPAR", slhaparam->extpar, slhalogical->lextpar, 49, mD3_val, "mD3 3rd-gen down-type squark singlet mass");
    }

    // ---------------------------------------------------------------------
    // Block ALPHA: CP-even Higgs mixing angle (same convention as GAMBIT's
    // own SLHA output: alpha = asin(SCALARMIX(2,2)); see mssm_slhahelp.cpp).
    // ---------------------------------------------------------------------
    {
      const double alpha = std::asin(mySpec.get(Par::Pole_Mixing, "h0", 2, 2));
      slhaparam->slhaalpha = alpha;
      slhalogical->lslhaalpha = 1;
      rec.add("ALPHA", fmt(alpha), "mixing angle in the CP-even Higgs sector");
    }

    // ---------------------------------------------------------------------
    // Block MASS: Higgs pole masses
    // ---------------------------------------------------------------------
    set_real("MASS", slhamass->smassbo, slhalogical->lsmassbo, 25, mySpec.get(Par::Pole_Mass, "h0_1"), "h  (lightest CP-even Higgs)");
    set_real("MASS", slhamass->smassbo, slhalogical->lsmassbo, 35, mySpec.get(Par::Pole_Mass, "h0_2"), "H  (heavier CP-even Higgs)");
    set_real("MASS", slhamass->smassbo, slhalogical->lsmassbo, 36, mySpec.get(Par::Pole_Mass, "A0"),   "A  (CP-odd Higgs)");

    // ---------------------------------------------------------------------
    // Block DISTRIB: total inclusive cross section, no cuts
    // ---------------------------------------------------------------------
    set_int("DISTRIB", slhaparam->distribpar, slhalogical->ldistribpar, 1, 0, "distribution: 0 = sigma_total");
    set_int("DISTRIB", slhaparam->distribpar, slhalogical->ldistribpar, 2, 0, "pt cut: 0 = no");
    set_int("DISTRIB", slhaparam->distribpar, slhalogical->ldistribpar, 3, 0, "rapidity cut: 0 = no");
    set_int("DISTRIB", slhaparam->distribpar, slhalogical->ldistribpar, 4, 0, "0 = rapidity, 1 = pseudorapidity");

    // ---------------------------------------------------------------------
    // Block SCALES: renormalisation and factorisation scales in units of mh.
    // The defaults reproduce SusHi's own defaults (muR = muF = mh for both
    // ggh and bbh).
    // ---------------------------------------------------------------------
    {
      const double mur_ggh = get_option(opts, "mur_ggh", 1.0);
      const double muf_ggh = get_option(opts, "muf_ggh", mur_ggh);
      const double mur_bbh = get_option(opts, "mur_bbh", mur_ggh);
      const double muf_bbh = get_option(opts, "muf_bbh", muf_ggh);
      set_real("SCALES", slhaparam->scalespar, slhalogical->lscalespar,  1, mur_ggh, "muR/mh for ggh");
      set_real("SCALES", slhaparam->scalespar, slhalogical->lscalespar,  2, muf_ggh, "muF/mh for ggh");
      set_real("SCALES", slhaparam->scalespar, slhalogical->lscalespar, 11, mur_bbh, "muR/mh for bbh");
      set_real("SCALES", slhaparam->scalespar, slhalogical->lscalespar, 12, muf_bbh, "muF/mh for bbh");
    }

    // ---------------------------------------------------------------------
    // Block RENORMBOT: bottom-quark Yukawa renormalisation
    //   1: mb for the bottom Yukawa (0 = OS, 1 = MSbar(mb), 2 = MSbar(muR))
    //   2: tan(beta) resummation of Y_b (0 = no, 1 = naive, 2 = full)
    //   3: Delta_b from FeynHiggs (0 = no; GAMBIT's spectrum is used directly)
    // ---------------------------------------------------------------------
    set_int("RENORMBOT", slhaparam->renormbotpar, slhalogical->lrenormbotpar, 1, get_int_option(opts, "renormbot_mb", 0),         "mb for bottom Yukawa: 0 = OS, 1 = MSbar(mb), 2 = MSbar(muR)");
    set_int("RENORMBOT", slhaparam->renormbotpar, slhalogical->lrenormbotpar, 2, get_int_option(opts, "renormbot_tanb_resum", 1), "tan(beta) resummation: 0 = no, 1 = naive, 2 = full");
    set_int("RENORMBOT", slhaparam->renormbotpar, slhalogical->lrenormbotpar, 3, 0,                               "Delta_b from FeynHiggs: 0 = no");

    // ---------------------------------------------------------------------
    // Block RENORMSBOT: sbottom-sector renormalisation.
    // Exactly one entry must be 2 (dependent); recommended: mb = dep, Ab = OS, thetab = OS
    // ---------------------------------------------------------------------
    set_int("RENORMSBOT", slhaparam->renormsbotpar, slhalogical->lrenormsbotpar, 1, 2, "mb: 2 = dep (recommended)");
    set_int("RENORMSBOT", slhaparam->renormsbotpar, slhalogical->lrenormsbotpar, 2, 0, "Ab: 0 = OS (recommended)");
    set_int("RENORMSBOT", slhaparam->renormsbotpar, slhalogical->lrenormsbotpar, 3, 0, "thetab: 0 = OS (recommended)");

    // ---------------------------------------------------------------------
    // Block FACTORS: multiplicative factors for the Yukawa couplings
    // (1 = c, 2 = t, 3 = b, 4 = stop, 5 = sbottom); 1.0 = unmodified.
    // ---------------------------------------------------------------------
    set_real("FACTORS", slhaparam->yukawafac, slhalogical->lyukawafac, 1, get_option(opts, "yukawa_factor_c",  1.0), "factor for Yukawa coupling: c");
    set_real("FACTORS", slhaparam->yukawafac, slhalogical->lyukawafac, 2, get_option(opts, "yukawa_factor_t",  1.0), "t");
    set_real("FACTORS", slhaparam->yukawafac, slhalogical->lyukawafac, 3, get_option(opts, "yukawa_factor_b",  1.0), "b");
    set_real("FACTORS", slhaparam->yukawafac, slhalogical->lyukawafac, 4, get_option(opts, "yukawa_factor_st", 1.0), "stop");
    set_real("FACTORS", slhaparam->yukawafac, slhalogical->lyukawafac, 5, get_option(opts, "yukawa_factor_sb", 1.0), "sbottom");

    // ---------------------------------------------------------------------
    // Block PDFSPEC: PDF sets (MMHT2014; installed with GAMBIT's LHAPDF) and member
    // ---------------------------------------------------------------------
    {
      const char* pdfs[4] = {"MMHT2014lo68cl", "MMHT2014nlo68cl", "MMHT2014nnlo68cl", "MMHT2014nnlo68cl"};
      const char* orders[4] = {"LO PDF", "NLO PDF", "NNLO PDF", "N3LO PDF (unused at NNLO)"};
      for (int i = 1; i <= 4; ++i)
      {
        *slhaparam->pdfname(i) = pdfs[i-1];
        slhalogical->lpdfname(i) = 1;
        rec.add("PDFSPEC", std::to_string(i) + "  " + pdfs[i-1], orders[i-1]);
      }
      set_int("PDFSPEC", slhaint->pdfspecpar, slhalogical->lpdfspecpar, 10, get_int_option(opts, "pdf_member", 0), "PDF set member (0 = central)");
    }

    // ---------------------------------------------------------------------
    // Block VEGAS: integration settings.  Defaults: reduced calls for speed
    // (~2% accuracy); raise via the yaml options for a slower, more precise
    // calculation.  Entries 3, 6, 9 switch off VEGAS screen output.
    // ---------------------------------------------------------------------
    set_int("VEGAS", slhaint->vegaspar, slhalogical->lvegaspar,  1, get_int_option(opts, "vegas_nlo_points", 5000),       "NLO points");
    set_int("VEGAS", slhaint->vegaspar, slhalogical->lvegaspar,  2, get_int_option(opts, "vegas_nlo_iter", 5),            "NLO iterations");
    set_int("VEGAS", slhaint->vegaspar, slhalogical->lvegaspar,  3, 0,                                    "NLO VEGAS output: 0 = none");
    set_int("VEGAS", slhaint->vegaspar, slhalogical->lvegaspar,  4, get_int_option(opts, "vegas_ggh_nnlo_points", 5000),  "ggh@nnlo points (1st run)");
    set_int("VEGAS", slhaint->vegaspar, slhalogical->lvegaspar,  5, get_int_option(opts, "vegas_ggh_nnlo_iter", 5),       "ggh@nnlo iterations (1st run)");
    set_int("VEGAS", slhaint->vegaspar, slhalogical->lvegaspar,  6, 0,                                    "ggh@nnlo VEGAS output: 0 = none");
    set_int("VEGAS", slhaint->vegaspar, slhalogical->lvegaspar, 14, get_int_option(opts, "vegas_ggh_nnlo_points2", 2000), "ggh@nnlo points (2nd run)");
    set_int("VEGAS", slhaint->vegaspar, slhalogical->lvegaspar, 15, get_int_option(opts, "vegas_ggh_nnlo_iter2", 2),      "ggh@nnlo iterations (2nd run)");
    set_int("VEGAS", slhaint->vegaspar, slhalogical->lvegaspar,  7, get_int_option(opts, "vegas_bbh_nnlo_points", 5000),  "bbh@nnlo points (1st run)");
    set_int("VEGAS", slhaint->vegaspar, slhalogical->lvegaspar,  8, get_int_option(opts, "vegas_bbh_nnlo_iter", 5),       "bbh@nnlo iterations (1st run)");
    set_int("VEGAS", slhaint->vegaspar, slhalogical->lvegaspar,  9, 0,                                    "bbh@nnlo VEGAS output: 0 = none");
    set_int("VEGAS", slhaint->vegaspar, slhalogical->lvegaspar, 17, get_int_option(opts, "vegas_bbh_nnlo_points2", 2000), "bbh@nnlo points (2nd run)");
    set_int("VEGAS", slhaint->vegaspar, slhalogical->lvegaspar, 18, get_int_option(opts, "vegas_bbh_nnlo_iter2", 2),      "bbh@nnlo iterations (2nd run)");

    // ---------------------------------------------------------------------
    // Run
    // ---------------------------------------------------------------------
    ++n_points_run;

    // Start every point from the same random-number state (as a standalone
    // SusHi run does), unless told otherwise.
    if (get_int_option(opts, "vegas_reseed", 1) != 0) gambit_sushi_reset_ranlux();

    // Debugging aid: write the input of this point to an SLHA file.
    if (get_int_option(opts, "write_slha_input", 0) != 0)
    {
      int rank = 0;
      #ifdef WITH_MPI
      if (GMPI::Is_initialized())
      {
        GMPI::Comm comm;
        rank = comm.Get_rank();
      }
      #endif
      const std::string fname = "SusHi_1_7_0_input_rank" + std::to_string(rank) + "_point" + std::to_string(n_points_run) + ".slha";
      rec.write(fname);
      logger() << LogTags::debug << "SusHi 1.7.0: wrote input of this point to " << fname << EOM;
    }

    double ggh = 0.0, bbh = 0.0, ggh_e = 0.0, bbh_e = 0.0;
    try
    {
      gambit_sushi_compute(ggh, bbh, ggh_e, bbh_e);
    }
    catch (std::runtime_error& e)
    {
      // SusHi hit a fatal error (a former Fortran STOP, rerouted to our handler).
      // Configuration problems are a backend error; anything else is a bad point.
      const std::string msg = e.what();
      if (msg.find("CONFIG") != std::string::npos || msg.find("undefined") != std::string::npos)
      {
        backend_error().raise(LOCAL_INFO, "SusHi 1.7.0 configuration error: " + msg);
      }
      invalid_point().raise("SusHi 1.7.0 failed at this point: " + msg);
    }
    ggh_result = ggh;
    bbh_result = bbh;
    ggh_err = ggh_e;
    bbh_err = bbh_e;

    logger() << LogTags::debug
             << "SusHi 1.7.0: ggh = " << fmt(ggh) << " +/- " << fmt(ggh_e) << " pb, bbh = " << fmt(bbh)
             << " +/- " << fmt(bbh_e) << " pb" << EOM;
  }

  // Called from SusHi's Fortran fatal-error routine (gsdie in
  // sushi_gambit_interface.f) in place of STOP.  Throws, so the failure
  // is caught around gambit_sushi_compute above.  Backend-specific name
  // avoids clashes between backends.
  extern "C"
  void CAT_4(BACKENDNAME,_,SAFE_VERSION,_ErrorHandler)(const char* msg)
  {
    throw std::runtime_error(std::string("SusHi: ") + msg);
  }
}
END_BE_NAMESPACE

// Initialisation: only installs the error handler.  All real per-point work
// happens in SusHi_run_point. 
BE_INI_FUNCTION
{
  // Make SusHi's fatal errors throw instead of killing the process.
  // The callback takes a const char* message, so cast to the generic type.
  static bool scan_level = true;
  if (scan_level)
  {
    *ErrorHandler_cptr = reinterpret_cast<fptr_void>(&CAT_4(BACKENDNAME,_,SAFE_VERSION,_ErrorHandler));
    scan_level = false;
  }
}
END_BE_INI_FUNCTION

