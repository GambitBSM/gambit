//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Function definitions of DecayBit.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2014 Aug
///  \date 2015 Mar-May
///
///  \author Csaba Balazs
///          (csaba.balazs@monash.edu)
///  \date 2015 Jan-May
///
///  \author Peter Athron
///          (peter.athron@coepp.org.au)
///  \date 2015 Jun
///
///  \author Ankit Beniwal
///          (ankit.beniwal@adelaide.edu.au)
///  \date 2016 Oct
///  \date 2017 Jun
///
///  \author Are Raklev
///          (ahye@fys.uio.no)
///  \date 2018 Jan
///
///  \author Anders Kvellestad
///          (anders.kvellestad@fys.uio.no)
///  \date 2018 Jan
///
///  \author Tomas Gonzalo
///          (t.e.gonzalo@fys.uio.no)
///  \date 2018 Feb
///
///  *********************************************

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/Elements/virtual_higgs.hpp"
#include "gambit/Elements/mssm_slhahelp.hpp"
#include "gambit/Elements/smlike_higgs.hpp"
#include "gambit/DecayBit/DecayBit_rollcall.hpp"
#include "gambit/DecayBit/decay_utils.hpp"
#include "gambit/DecayBit/SM_Z.hpp"
#include "gambit/DecayBit/MSSM_H.hpp"
#include "gambit/DecayBit/MSSM_Z.hpp"
#include "gambit/Utils/version.hpp"
#include "gambit/Utils/ascii_table_reader.hpp"
#include "gambit/Utils/statistics.hpp"
#include "gambit/Utils/numerical_constants.hpp"
#include "gambit/Utils/integration.hpp"

#include <string>
#include <map>
#include <complex>
#include <functional>

#define pow2(a) ((a)*(a))          // Get speedy
#define pow3(a) ((a)*(a)*(a))
#define pow4(a) (pow2(a)*pow2(a))

//#define DECAYBIT_DEBUG

namespace Gambit
{

  namespace DecayBit
  {

    using namespace LogTags;

    /// \name Helper functions for DecayBit
    /// @{

    /// Square root of the standard kinematic function lambda(a,b,c)
    double sqrt_lambda(double a, double b, double c) { return sqrt(pow2(a+b-c) - 4*a*b); }

    /// Breit-Wigner pole (complex)
    std::complex<double> BW(double q2, double m2, double imag_term)
    {
      static const std::complex<double> i(0.0,1.0);
      return m2 / (m2 - q2 -i*imag_term);
    }


    /// Check if a width is negative or suspiciously large and raise an error.
    void check_width(const str& info, double& w, bool raise_invalid_pt_negative_width = false, bool raise_invalid_pt_large_width = false)
    {
      if (Utils::isnan(w)) DecayBit_error().raise(info, "Decay width is NaN!");
      if (w < 0)
      {
        str nwiderr("Negative width returned!");
        if (raise_invalid_pt_negative_width)
          invalid_point().raise(nwiderr);
        else
          DecayBit_error().raise(info, nwiderr);
      }
      if (w > 1e7)
      {
        str lwiderr("Suspiciously large width returned: "+std::to_string(w)+" GeV");
        if (raise_invalid_pt_large_width)
          invalid_point().raise(lwiderr);
        else
          DecayBit_error().raise(info, lwiderr);
      }
    }

    /// Populate SM Higgs decay channels for a higgs mass of m_h
    void compute_SM_higgs_decays(DecayTable::Entry& result, double mh)
    {
      // Just kill off the point if the Higgs is < 1 GeV in mass.
      if (mh < 1.) invalid_point().raise("Neutral higgs with mass < 1 GeV");
      // If it's more than 16 TeV, just calculate as if it has a mass of 16 TeV.  The BFs will
      // be the same (2/3 WW, 1/3 Z), the width will just be underestimated.  At this mass though,
      // that shouldn't impact anything.
      if (mh > 1.6e4)
      {
        std::stringstream msg;
        msg << "Neutral higgs with mass > 16 TeV; calculating SM decays as if m = 16 TeV.  Actual mass: " << mh*1e-3 << " TeV";
        DecayBit_warning().raise(LOCAL_INFO, msg.str());
        mh = 1.6e4;
      }
      result.calculator = "GAMBIT::DecayBit";
      result.calculator_version = gambit_version();
      result.width_in_GeV = virtual_SMHiggs_widths("Gamma",mh);
      result.set_BF(virtual_SMHiggs_widths("bb",mh), 0.0, "b", "bbar");
      result.set_BF(virtual_SMHiggs_widths("tautau",mh), 0.0, "tau+", "tau-");
      result.set_BF(virtual_SMHiggs_widths("mumu",mh), 0.0, "mu+", "mu-");
      result.set_BF(virtual_SMHiggs_widths("ss",mh), 0.0, "s", "sbar");
      result.set_BF(virtual_SMHiggs_widths("cc",mh), 0.0, "c", "cbar");
      result.set_BF(virtual_SMHiggs_widths("tt",mh), 0.0, "t", "tbar");
      result.set_BF(virtual_SMHiggs_widths("gg",mh), 0.0, "g", "g");
      result.set_BF(virtual_SMHiggs_widths("gammagamma",mh), 0.0, "gamma", "gamma");
      result.set_BF(virtual_SMHiggs_widths("Zgamma",mh), 0.0, "Z0", "gamma");
      result.set_BF(virtual_SMHiggs_widths("WW",mh), 0.0, "W+", "W-");
      result.set_BF(virtual_SMHiggs_widths("ZZ",mh), 0.0, "Z0", "Z0");
    }

    /// Set neutral h decays computed by FeynHiggs
    void set_FH_neutral_h_decay(DecayTable::Entry& result, int iH, const fh_Couplings& FH_input, const mass_es_pseudonyms& psn, bool invalidate, bool SM)
    {
      // Set the array and its offset according to whether we want the SM or BSM decays
      const fh_real* widths = SM ? FH_input.gammas_sm : FH_input.gammas;
      const int local_offset = SM ? BRSMoffset-1 : BRoffset-1;

      // Set the calculator info (presumably FeynHiggs...)
      result.calculator = FH_input.calculator;
      result.calculator_version = FH_input.calculator_version;

      // Set the total Higgs width
      result.width_in_GeV = widths[iH-1];

      // vector-boson pair decays
      result.set_BF((result.width_in_GeV > 0 ? widths[H0VV(iH,1)+local_offset] : 0.0), 0.0, "gamma", "gamma");
      result.set_BF((result.width_in_GeV > 0 ? widths[H0VV(iH,2)+local_offset] : 0.0), 0.0, "gamma", "Z0");
      result.set_BF((result.width_in_GeV > 0 ? widths[H0VV(iH,3)+local_offset] : 0.0), 0.0, "Z0", "Z0");
      result.set_BF((result.width_in_GeV > 0 ? widths[H0VV(iH,4)+local_offset] : 0.0), 0.0, "W+", "W-");
      result.set_BF((result.width_in_GeV > 0 ? widths[H0VV(iH,5)+local_offset] : 0.0), 0.0, "g", "g");

      // SM fermion decays
      result.set_BF((result.width_in_GeV > 0 ? widths[H0FF(iH,1,1,1)+local_offset] : 0.0), 0.0, "nu_e", "nubar_e");
      result.set_BF((result.width_in_GeV > 0 ? widths[H0FF(iH,1,2,2)+local_offset] : 0.0), 0.0, "nu_mu", "nubar_mu");
      result.set_BF((result.width_in_GeV > 0 ? widths[H0FF(iH,1,3,3)+local_offset] : 0.0), 0.0, "nu_tau", "nubar_tau");
      result.set_BF((result.width_in_GeV > 0 ? widths[H0FF(iH,2,1,1)+local_offset] : 0.0), 0.0, "e+", "e-");
      result.set_BF((result.width_in_GeV > 0 ? widths[H0FF(iH,2,2,2)+local_offset] : 0.0), 0.0, "mu+", "mu-");
      result.set_BF((result.width_in_GeV > 0 ? widths[H0FF(iH,2,3,3)+local_offset] : 0.0), 0.0, "tau+", "tau-");
      result.set_BF((result.width_in_GeV > 0 ? widths[H0FF(iH,3,1,1)+local_offset] : 0.0), 0.0, "u", "ubar");
      result.set_BF((result.width_in_GeV > 0 ? widths[H0FF(iH,3,2,2)+local_offset] : 0.0), 0.0, "c", "cbar");
      result.set_BF((result.width_in_GeV > 0 ? widths[H0FF(iH,3,3,3)+local_offset] : 0.0), 0.0, "t", "tbar");
      result.set_BF((result.width_in_GeV > 0 ? widths[H0FF(iH,4,1,1)+local_offset] : 0.0), 0.0, "d", "dbar");
      result.set_BF((result.width_in_GeV > 0 ? widths[H0FF(iH,4,2,2)+local_offset] : 0.0), 0.0, "s", "sbar");
      result.set_BF((result.width_in_GeV > 0 ? widths[H0FF(iH,4,3,3)+local_offset] : 0.0), 0.0, "b", "bbar");

      if (not SM)
      {
        // chargino decays
        result.set_BF((result.width_in_GeV > 0 ? widths[H0ChaCha(iH,1,1)+local_offset] : 0.0), 0.0, "~chi-_1", "~chi+_1");
        result.set_BF((result.width_in_GeV > 0 ? widths[H0ChaCha(iH,1,2)+local_offset] : 0.0), 0.0, "~chi-_1", "~chi+_2");
        result.set_BF((result.width_in_GeV > 0 ? widths[H0ChaCha(iH,2,1)+local_offset] : 0.0), 0.0, "~chi-_2", "~chi+_1");
        result.set_BF((result.width_in_GeV > 0 ? widths[H0ChaCha(iH,2,2)+local_offset] : 0.0), 0.0, "~chi-_2", "~chi+_2");

        // neutralino decays
        result.set_BF((result.width_in_GeV > 0 ? widths[H0NeuNeu(iH,1,1)+local_offset] : 0.0), 0.0, "~chi0_1", "~chi0_1");
        result.set_BF((result.width_in_GeV > 0 ? widths[H0NeuNeu(iH,2,2)+local_offset] : 0.0), 0.0, "~chi0_2", "~chi0_2");
        result.set_BF((result.width_in_GeV > 0 ? widths[H0NeuNeu(iH,3,3)+local_offset] : 0.0), 0.0, "~chi0_3", "~chi0_3");
        result.set_BF((result.width_in_GeV > 0 ? widths[H0NeuNeu(iH,4,4)+local_offset] : 0.0), 0.0, "~chi0_4", "~chi0_4");
        result.set_BF((result.width_in_GeV > 0 ? widths[H0NeuNeu(iH,1,2)+local_offset] : 0.0), 0.0, "~chi0_1", "~chi0_2");
        result.set_BF((result.width_in_GeV > 0 ? widths[H0NeuNeu(iH,1,3)+local_offset] : 0.0), 0.0, "~chi0_1", "~chi0_3");
        result.set_BF((result.width_in_GeV > 0 ? widths[H0NeuNeu(iH,1,4)+local_offset] : 0.0), 0.0, "~chi0_1", "~chi0_4");
        result.set_BF((result.width_in_GeV > 0 ? widths[H0NeuNeu(iH,2,3)+local_offset] : 0.0), 0.0, "~chi0_2", "~chi0_3");
        result.set_BF((result.width_in_GeV > 0 ? widths[H0NeuNeu(iH,2,4)+local_offset] : 0.0), 0.0, "~chi0_2", "~chi0_4");
        result.set_BF((result.width_in_GeV > 0 ? widths[H0NeuNeu(iH,3,4)+local_offset] : 0.0), 0.0, "~chi0_3", "~chi0_4");

        // higgs + Z0 decays
        result.set_BF((result.width_in_GeV > 0 ? widths[H0HV(iH,1)+local_offset] : 0.0), 0.0, "h0_1", "Z0");
        result.set_BF((result.width_in_GeV > 0 ? widths[H0HV(iH,2)+local_offset] : 0.0), 0.0, "h0_2", "Z0");
        result.set_BF((result.width_in_GeV > 0 ? widths[H0HV(iH,3)+local_offset] : 0.0), 0.0, "A0", "Z0");

        // higgs+higgs decays
        result.set_BF((result.width_in_GeV > 0 ? widths[H0HH(iH,1,1)+local_offset] : 0.0), 0.0, "h0_1", "h0_1");
        result.set_BF((result.width_in_GeV > 0 ? widths[H0HH(iH,2,2)+local_offset] : 0.0), 0.0, "h0_2", "h0_2");
        result.set_BF((result.width_in_GeV > 0 ? widths[H0HH(iH,3,3)+local_offset] : 0.0), 0.0, "A0", "A0");
        result.set_BF((result.width_in_GeV > 0 ? widths[H0HH(iH,4,4)+local_offset] : 0.0), 0.0, "H+", "H-");
        result.set_BF((result.width_in_GeV > 0 ? widths[H0HH(iH,1,2)+local_offset] : 0.0), 0.0, "h0_1", "h0_2");
        result.set_BF((result.width_in_GeV > 0 ? widths[H0HH(iH,1,3)+local_offset] : 0.0), 0.0, "h0_1", "A0");
        result.set_BF((result.width_in_GeV > 0 ? widths[H0HH(iH,2,3)+local_offset] : 0.0), 0.0, "h0_2", "A0");

        // FH does not compute h0_1/h0_2/A0 --> H+W- / H-W+

        // sfermion decays
        result.set_BF((result.width_in_GeV > 0 ? widths[H0SfSf(iH,1,1,1,1)+local_offset] : 0.0), 0.0, psn.isnel, psn.isnelbar);
        result.set_BF((result.width_in_GeV > 0 ? widths[H0SfSf(iH,1,1,1,2)+local_offset] : 0.0), 0.0, psn.isnmul, psn.isnmulbar);
        result.set_BF((result.width_in_GeV > 0 ? widths[H0SfSf(iH,1,1,1,3)+local_offset] : 0.0), 0.0, psn.isntaul, psn.isntaulbar);
        result.set_BF((result.width_in_GeV > 0 ? widths[H0SfSf(iH,1,1,2,1)+local_offset] : 0.0), 0.0, psn.isell, psn.isellbar);
        result.set_BF((result.width_in_GeV > 0 ? widths[H0SfSf(iH,1,2,2,1)+local_offset] : 0.0), 0.0, psn.isell, psn.iselrbar);
        result.set_BF((result.width_in_GeV > 0 ? widths[H0SfSf(iH,2,1,2,1)+local_offset] : 0.0), 0.0, psn.iselr, psn.isellbar);
        result.set_BF((result.width_in_GeV > 0 ? widths[H0SfSf(iH,2,2,2,1)+local_offset] : 0.0), 0.0, psn.iselr, psn.iselrbar);
        result.set_BF((result.width_in_GeV > 0 ? widths[H0SfSf(iH,1,1,2,2)+local_offset] : 0.0), 0.0, psn.ismul, psn.ismulbar);
        result.set_BF((result.width_in_GeV > 0 ? widths[H0SfSf(iH,1,2,2,2)+local_offset] : 0.0), 0.0, psn.ismul, psn.ismurbar);
        result.set_BF((result.width_in_GeV > 0 ? widths[H0SfSf(iH,2,1,2,2)+local_offset] : 0.0), 0.0, psn.ismur, psn.ismulbar);
        result.set_BF((result.width_in_GeV > 0 ? widths[H0SfSf(iH,2,2,2,2)+local_offset] : 0.0), 0.0, psn.ismur, psn.ismurbar);
        result.set_BF((result.width_in_GeV > 0 ? widths[H0SfSf(iH,1,1,2,3)+local_offset] : 0.0), 0.0, psn.istau1, psn.istau1bar);
        result.set_BF((result.width_in_GeV > 0 ? widths[H0SfSf(iH,1,2,2,3)+local_offset] : 0.0), 0.0, psn.istau1, psn.istau2bar);
        result.set_BF((result.width_in_GeV > 0 ? widths[H0SfSf(iH,2,1,2,3)+local_offset] : 0.0), 0.0, psn.istau2, psn.istau1bar);
        result.set_BF((result.width_in_GeV > 0 ? widths[H0SfSf(iH,2,2,2,3)+local_offset] : 0.0), 0.0, psn.istau2, psn.istau2bar);
        result.set_BF((result.width_in_GeV > 0 ? widths[H0SfSf(iH,1,1,3,1)+local_offset] : 0.0), 0.0, psn.isul, psn.isulbar);
        result.set_BF((result.width_in_GeV > 0 ? widths[H0SfSf(iH,1,2,3,1)+local_offset] : 0.0), 0.0, psn.isul, psn.isurbar);
        result.set_BF((result.width_in_GeV > 0 ? widths[H0SfSf(iH,2,1,3,1)+local_offset] : 0.0), 0.0, psn.isur, psn.isulbar);
        result.set_BF((result.width_in_GeV > 0 ? widths[H0SfSf(iH,2,2,3,1)+local_offset] : 0.0), 0.0, psn.isur, psn.isurbar);
        result.set_BF((result.width_in_GeV > 0 ? widths[H0SfSf(iH,1,1,3,2)+local_offset] : 0.0), 0.0, psn.iscl, psn.isclbar);
        result.set_BF((result.width_in_GeV > 0 ? widths[H0SfSf(iH,1,2,3,2)+local_offset] : 0.0), 0.0, psn.iscl, psn.iscrbar);
        result.set_BF((result.width_in_GeV > 0 ? widths[H0SfSf(iH,2,1,3,2)+local_offset] : 0.0), 0.0, psn.iscr, psn.isclbar);
        result.set_BF((result.width_in_GeV > 0 ? widths[H0SfSf(iH,2,2,3,2)+local_offset] : 0.0), 0.0, psn.iscr, psn.iscrbar);
        result.set_BF((result.width_in_GeV > 0 ? widths[H0SfSf(iH,1,1,3,3)+local_offset] : 0.0), 0.0, psn.ist1, psn.ist1bar);
        result.set_BF((result.width_in_GeV > 0 ? widths[H0SfSf(iH,1,2,3,3)+local_offset] : 0.0), 0.0, psn.ist1, psn.ist2bar);
        result.set_BF((result.width_in_GeV > 0 ? widths[H0SfSf(iH,2,1,3,3)+local_offset] : 0.0), 0.0, psn.ist2, psn.ist1bar);
        result.set_BF((result.width_in_GeV > 0 ? widths[H0SfSf(iH,2,2,3,3)+local_offset] : 0.0), 0.0, psn.ist2, psn.ist2bar);
        result.set_BF((result.width_in_GeV > 0 ? widths[H0SfSf(iH,1,1,3,1)+local_offset] : 0.0), 0.0, psn.isdl, psn.isdlbar);
        result.set_BF((result.width_in_GeV > 0 ? widths[H0SfSf(iH,1,2,3,1)+local_offset] : 0.0), 0.0, psn.isdl, psn.isdrbar);
        result.set_BF((result.width_in_GeV > 0 ? widths[H0SfSf(iH,2,1,3,1)+local_offset] : 0.0), 0.0, psn.isdr, psn.isdlbar);
        result.set_BF((result.width_in_GeV > 0 ? widths[H0SfSf(iH,2,2,3,1)+local_offset] : 0.0), 0.0, psn.isdr, psn.isdrbar);
        result.set_BF((result.width_in_GeV > 0 ? widths[H0SfSf(iH,1,1,3,2)+local_offset] : 0.0), 0.0, psn.issl, psn.isslbar);
        result.set_BF((result.width_in_GeV > 0 ? widths[H0SfSf(iH,1,2,3,2)+local_offset] : 0.0), 0.0, psn.issl, psn.issrbar);
        result.set_BF((result.width_in_GeV > 0 ? widths[H0SfSf(iH,2,1,3,2)+local_offset] : 0.0), 0.0, psn.issr, psn.isslbar);
        result.set_BF((result.width_in_GeV > 0 ? widths[H0SfSf(iH,2,2,3,2)+local_offset] : 0.0), 0.0, psn.issr, psn.issrbar);
        result.set_BF((result.width_in_GeV > 0 ? widths[H0SfSf(iH,1,1,3,3)+local_offset] : 0.0), 0.0, psn.isb1, psn.isb1bar);
        result.set_BF((result.width_in_GeV > 0 ? widths[H0SfSf(iH,1,2,3,3)+local_offset] : 0.0), 0.0, psn.isb1, psn.isb2bar);
        result.set_BF((result.width_in_GeV > 0 ? widths[H0SfSf(iH,2,1,3,3)+local_offset] : 0.0), 0.0, psn.isb2, psn.isb1bar);
        result.set_BF((result.width_in_GeV > 0 ? widths[H0SfSf(iH,2,2,3,3)+local_offset] : 0.0), 0.0, psn.isb2, psn.isb2bar);
      }

      check_width(LOCAL_INFO, result.width_in_GeV, invalidate);
    }
    /// @}


    /// \name DecayBit module functions
    /// @{


    /////////////// Standard Model ///////////////////

    /// SM decays: W+
    /// Reference: 2017 PDG
    void W_plus_decays (DecayTable::Entry& result)
    {
      result.calculator = "GAMBIT::DecayBit";
      result.calculator_version = gambit_version();
      result.width_in_GeV = 2.085;
      result.positive_error = 4.2e-02;
      result.negative_error = 4.2e-02;
      result.set_BF(0.1071, 0.0016, "e+", "nu_e");
      result.set_BF(0.1063, 0.0015, "mu+", "nu_mu");
      result.set_BF(0.1138, 0.0021, "tau+", "nu_tau");
      result.set_BF(0.6741, 0.0027, "hadron", "hadron");
    }

    /// SM decays: Z
    /// Reference: 2017 PDG
    void Z_decays (DecayTable::Entry& result)
    {
      using namespace Pipes::Z_decays;

      result.calculator = "GAMBIT::DecayBit";
      result.calculator_version = gambit_version();
      result.width_in_GeV = 2.4952;
      result.positive_error = 2.3e-03;
      result.negative_error = 2.3e-03;
      result.set_BF(0.03363, 0.00004, "e+", "e-");
      result.set_BF(0.03366, 0.00007, "mu+", "mu-");
      result.set_BF(0.03370, 0.00008, "tau+", "tau-");
      result.set_BF(0.6991, 0.0006, "hadron", "hadron");

      // Neutrinos
      // FIXME: It doesn't work because SMINPUTS it's not satisfied yet
      /*const SMInputs sminputs = *Dep::SMINPUTS;

      const double cosW = sminputs.mW/sminputs.mZ;
      const double sinW2 = 1 - cosW*cosW;
      const double g2 = sqrt(4*pi/sminputs.alphainv/sinW2);
      const double mZ = sminputs.mZ;

      double Z_to_neutrinos = pow(g2/(2.0*cosW),2) * mZ/(24.0*pi);
      result.set_BF(Z_to_neutrinos/result.width_in_GeV, Z_to_neutrinos/pow(result.width_in_GeV,2)*result.positive_error, "nu_e", "nubar_e");
      result.set_BF(Z_to_neutrinos/result.width_in_GeV, Z_to_neutrinos/pow(result.width_in_GeV,2)*result.positive_error, "nu_mu", "nubar_mu");
      result.set_BF(Z_to_neutrinos/result.width_in_GeV, Z_to_neutrinos/pow(result.width_in_GeV,2)*result.positive_error, "nu_tau", "nubar_tau");
      */
    }

    /// SM decays: t
    /// Reference: 2017 PDG
    void t_decays (DecayTable::Entry& result)
    {
      result.calculator = "GAMBIT::DecayBit";
      result.calculator_version = gambit_version();
      result.width_in_GeV = 1.41;
      result.positive_error = 1.9e-01;
      result.negative_error = 1.5e-01;
      result.set_BF(0.957, 0.034, "W+", "b"); //(Assuming 100% decay to Wq)
    }

    /// SM decays: mu+
    /// Reference: 2017 PDG
    void mu_plus_decays (DecayTable::Entry& result)
    {
      result.calculator = "GAMBIT::DecayBit";
      result.calculator_version = gambit_version();
      result.width_in_GeV = 2.9959837e-19;
      result.positive_error = 3.0e-25;
      result.negative_error = 3.0e-25;
      result.set_BF(1.0, 0.0, "e+", "nu_e", "nubar_mu");
    }

    /// SM decays: tau+
    /// Reference: 2017 PDG
    void tau_plus_decays (DecayTable::Entry& result)
    {
      result.calculator = "GAMBIT::DecayBit";
      result.calculator_version = gambit_version();
      result.width_in_GeV = 2.267E-12;
      result.positive_error = 3.9e-15;
      result.negative_error = 3.9e-15;
      result.set_BF(0.1739, 0.0004, "mu+", "nu_mu", "nubar_tau");
      result.set_BF(0.1782, 0.0004, "e+", "nu_e", "nubar_tau");
      result.set_BF(0.1082, 0.0005, "pi+", "nubar_tau");
      result.set_BF(0.2549, 0.0009, "pi+", "pi0", "nubar_tau");
      result.set_BF(0.0926, 0.0010, "pi+", "pi0", "pi0", "nubar_tau");
      result.set_BF(0.0104, 0.0007, "pi+", "pi0", "pi0", "pi0", "nubar_tau");
      result.set_BF(0.0931, 0.0005, "pi+", "pi+", "pi-", "nubar_tau");
      result.set_BF(0.0462, 0.0005, "pi+", "pi+", "pi-", "pi0", "nubar_tau");
    }

    /// SM decays: pi0
    /// Reference: 2017 PDG
    void pi_0_decays (DecayTable::Entry& result)
    {
      result.calculator = "GAMBIT::DecayBit";
      result.calculator_version = gambit_version();
      result.width_in_GeV = 7.73e-09;
      result.positive_error = 1.6e-10;
      result.negative_error = 1.6e-10;
      result.set_BF(0.98823, 0.00034, "gamma", "gamma");
      result.set_BF(0.01174, 0.00035, "e+", "e-", "gamma");
      result.set_BF(3.34e-5, 0.16e-5, "e+", "e-", "e+", "e-");
      result.set_BF(6.46e-8, 0.33e-8, "e+", "e-");
    }

    /// SM decays: pi+
    /// Reference: 2017 PDG
    void pi_plus_decays (DecayTable::Entry& result)
    {
      result.calculator = "GAMBIT::DecayBit";
      result.calculator_version = gambit_version();
      result.width_in_GeV = 2.5284e-17;
      result.positive_error = 4.9e-21;
      result.negative_error = 4.9e-21;
      result.set_BF(0.9998770, 0.0000004, "mu+", "nu_mu");
      result.set_BF(1.230e-4, 0.004e-4, "e+", "nu_e");
    }

    /// SM decays: eta
    /// Reference: 2017 PDG
    void eta_decays (DecayTable::Entry& result)
    {
      result.calculator = "GAMBIT::DecayBit";
      result.calculator_version = gambit_version();
      result.width_in_GeV = 1.31e-06;
      result.positive_error = 5.0e-08;
      result.negative_error = 5.0e-08;
    }

    /// SM decays: rho0
    /// Reference: 2017 PDG
    void rho_0_decays (DecayTable::Entry& result)
    {
      result.calculator = "GAMBIT::DecayBit";
      result.calculator_version = gambit_version();
      result.width_in_GeV = 1.478e-01;
      result.positive_error = 9.0e-04;
      result.negative_error = 9.0e-04;
    }

    /// SM decays: rho+
    /// Reference: 2017 PDG
    void rho_plus_decays (DecayTable::Entry& result)
    {
      result.calculator = "GAMBIT::DecayBit";
      result.calculator_version = gambit_version();
      result.width_in_GeV = 1.491e-01;
      result.positive_error = 8.0e-04;
      result.negative_error = 8.0e-04;
    }

    /// SM decays: omega
    /// Reference: 2017 PDG
    void omega_decays (DecayTable::Entry& result)
    {
      result.calculator = "GAMBIT::DecayBit";
      result.calculator_version = gambit_version();
      result.width_in_GeV = 8.49e-03;
      result.positive_error = 8.0e-05;
      result.negative_error = 8.0e-05;
    }

    /// SM decays: rho1450
    /// Reference: 2017 PDG
    void rho1450_decays (DecayTable::Entry& result)
    {
      result.calculator = "GAMBIT::DecayBit";
      result.calculator_version = gambit_version();
      result.width_in_GeV = 4.0e-1;
      result.positive_error = 6.0e-02;
      result.negative_error = 6.0e-02;
    }

    /// SM decays: conjugates
    /// @{
    void W_minus_decays (DecayTable::Entry& result)   { result = CP_conjugate(*Pipes::W_minus_decays::Dep::W_plus_decay_rates); }
    void tbar_decays (DecayTable::Entry& result)      { result = CP_conjugate(*Pipes::tbar_decays::Dep::t_decay_rates); }
    void mu_minus_decays (DecayTable::Entry& result)  { result = CP_conjugate(*Pipes::mu_minus_decays::Dep::mu_plus_decay_rates); }
    void tau_minus_decays (DecayTable::Entry& result) { result = CP_conjugate(*Pipes::tau_minus_decays::Dep::tau_plus_decay_rates); }
    void pi_minus_decays (DecayTable::Entry& result)  { result = CP_conjugate(*Pipes::pi_minus_decays::Dep::pi_plus_decay_rates); }
    void rho_minus_decays (DecayTable::Entry& result) { result = CP_conjugate(*Pipes::rho_minus_decays::Dep::rho_plus_decay_rates); }
    /// @}


    /// \brief Reference SM Higgs decays
    ///
    /// These functions are given a different capability to regular decay
    /// functions, to allow other module functions to specifically depend
    /// on the SM values for reference, even when scanning another model.
    /// @{

    /// Reference SM Higgs decays from LHCHiggsXSWG: most SM-like Higgs
    void Ref_SM_Higgs_decays_table(DecayTable::Entry& result)
    {
      using namespace Pipes::Ref_SM_Higgs_decays_table;
      double mh = Dep::mh->central;
      double minmass = runOptions->getValueOrDef<double>(90.0, "higgs_minmass");
      double maxmass = runOptions->getValueOrDef<double>(160.0, "higgs_maxmass");
      // Invalidate the point if higgs mass is outside the range over which the tables of the LHCHiggsXSWG are most reliable.
      if (mh < minmass or mh > maxmass)
      {
        std::stringstream msg;
        msg << "Computed Higgs mass is " << mh << "; This is outside of the accurate range for "
            << "tables from the LHCHiggsXSWG, which is " << minmass << "--" << maxmass << " GeV.";
        invalid_point().raise(msg.str());
      }
      compute_SM_higgs_decays(result, mh);
    }
    /// Reference SM Higgs decays from LHCHiggsXSWG: least SM-like Higgs
    void Ref_SM_other_Higgs_decays_table(DecayTable::Entry& result)
    {
      using namespace Pipes::Ref_SM_other_Higgs_decays_table;
      const SubSpectrum& spec = Dep::MSSM_spectrum->get_HE();
      int other_higgs = (SMlike_higgs_PDG_code(spec) == 25 ? 35 : 25);
      double m_other = Dep::MSSM_spectrum->get(Par::Pole_Mass, other_higgs, 0);
      compute_SM_higgs_decays(result, m_other);
    }
    /// Reference SM Higgs decays from LHCHiggsXSWG: A0
    void Ref_SM_A0_decays_table(DecayTable::Entry& result)
    {
      using namespace Pipes::Ref_SM_A0_decays_table;
      double mA0 = Dep::MSSM_spectrum->get(Par::Pole_Mass, "A0");
      compute_SM_higgs_decays(result, mA0);
    }

    /// Reference SM Higgs decays from FeynHiggs: h0_1
    void Ref_SM_Higgs_decays_FH(DecayTable::Entry& result)
    {
      using namespace Pipes::Ref_SM_Higgs_decays_FH;
      const SubSpectrum& spec = Dep::MSSM_spectrum->get_HE();
      int higgs = (SMlike_higgs_PDG_code(spec) == 25 ? 1 : 2);
      bool invalidate = runOptions->getValueOrDef<bool>(false, "invalid_point_for_negative_width");
      set_FH_neutral_h_decay(result, higgs, *Dep::FH_Couplings_output, *(Dep::SLHA_pseudonyms), invalidate, true);
    }
    /// Reference SM Higgs decays from FeynHiggs: h0_2
    void Ref_SM_other_Higgs_decays_FH(DecayTable::Entry& result)
    {
      using namespace Pipes::Ref_SM_other_Higgs_decays_FH;
      const SubSpectrum& spec = Dep::MSSM_spectrum->get_HE();
      int other_higgs = (SMlike_higgs_PDG_code(spec) == 25 ? 2 : 1);
      bool invalidate = runOptions->getValueOrDef<bool>(false, "invalid_point_for_negative_width");
      set_FH_neutral_h_decay(result, other_higgs, *Dep::FH_Couplings_output, *(Dep::SLHA_pseudonyms), invalidate, true);
    }
    /// Reference SM Higgs decays from FeynHiggs: A0
    void Ref_SM_A0_decays_FH(DecayTable::Entry& result)
    {
      using namespace Pipes::Ref_SM_A0_decays_FH;
      bool invalidate = runOptions->getValueOrDef<bool>(false, "invalid_point_for_negative_width");
      set_FH_neutral_h_decay(result, 3, *Dep::FH_Couplings_output, *(Dep::SLHA_pseudonyms), invalidate, true);
    }
    /// @}


    /// SM decays: Higgs
    void SM_Higgs_decays (DecayTable::Entry& result)
    {
      result = *Pipes::SM_Higgs_decays::Dep::Reference_SM_Higgs_decay_rates;
    }


    //////////// MSSM /////////////////////

    /// FeynHiggs MSSM decays: t
    /// Reference for total width: 2017 PDG
    void FH_t_decays (DecayTable::Entry& result)
    {
      using namespace Pipes::FH_t_decays;
      fh_Couplings FH_input = *Pipes::FH_t_decays::Dep::FH_Couplings_output;
      result.calculator = FH_input.calculator;
      result.calculator_version = FH_input.calculator_version;
      result.width_in_GeV = 1.41;
      result.positive_error = 1.9e-01;
      result.negative_error = 1.5e-01;
      result.set_BF(FH_input.gammas[tBF(1)+BRoffset-1], 0.0, "W+", "b");
      result.set_BF(FH_input.gammas[tBF(2)+BRoffset-1], 0.0, "H+", "b");
      check_width(LOCAL_INFO, result.width_in_GeV, runOptions->getValueOrDef<bool>(false, "invalid_point_for_negative_width"));
    }

    /// FeynHiggs MSSM decays: h0_1
    void FH_MSSM_h0_1_decays (DecayTable::Entry& result)
    {
      using namespace Pipes::FH_MSSM_h0_1_decays;
      bool invalidate = runOptions->getValueOrDef<bool>(false, "invalid_point_for_negative_width");
      set_FH_neutral_h_decay(result, 1, *Dep::FH_Couplings_output, *(Dep::SLHA_pseudonyms), invalidate, false);
    }

    /// FeynHiggs MSSM decays: h0_2
    void FH_h0_2_decays (DecayTable::Entry& result)
    {
      using namespace Pipes::FH_h0_2_decays;
      bool invalidate = runOptions->getValueOrDef<bool>(false, "invalid_point_for_negative_width");
      set_FH_neutral_h_decay(result, 2, *Dep::FH_Couplings_output, *(Dep::SLHA_pseudonyms), invalidate, false);
    }

    /// FeynHiggs MSSM decays: A0
    void FH_A0_decays (DecayTable::Entry& result)
    {
      using namespace Pipes::FH_A0_decays;
      bool invalidate = runOptions->getValueOrDef<bool>(false, "invalid_point_for_negative_width");
      set_FH_neutral_h_decay(result, 3, *Dep::FH_Couplings_output, *(Dep::SLHA_pseudonyms), invalidate, false);
    }

    /// FeynHiggs MSSM decays: H+
    void FH_H_plus_decays (DecayTable::Entry& result)
    {
      using namespace Pipes::FH_H_plus_decays;

      // Get the mass pseudonyms for the gauge eigenstates
      mass_es_pseudonyms psn = *(Dep::SLHA_pseudonyms);

      // unpack FeynHiggs Couplings
      fh_Couplings FH_input = *Dep::FH_Couplings_output;
      result.calculator = FH_input.calculator;
      result.calculator_version = FH_input.calculator_version;
      // Set the total charged Higgs width
      result.width_in_GeV = FH_input.gammas[3];
      // Set the branching ratio offset, subtracting 1 for C array access instead of Fortran (as defined in FH header).
      int offset = BRoffset-1;

      // SM fermion decays
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpFF(1,1,1)+offset] : 0.0), 0.0, "e+", "nu_e");
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpFF(1,2,2)+offset] : 0.0), 0.0, "mu+", "nu_mu");
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpFF(1,2,2)+offset] : 0.0), 0.0, "tau+", "nu_tau");
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpFF(2,1,1)+offset] : 0.0), 0.0, "u", "dbar");
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpFF(2,1,2)+offset] : 0.0), 0.0, "u", "sbar");
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpFF(2,1,3)+offset] : 0.0), 0.0, "u", "bbar");
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpFF(2,2,1)+offset] : 0.0), 0.0, "c", "dbar");
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpFF(2,2,2)+offset] : 0.0), 0.0, "c", "sbar");
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpFF(2,2,3)+offset] : 0.0), 0.0, "c", "bbar");
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpFF(2,3,1)+offset] : 0.0), 0.0, "t", "dbar");
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpFF(2,3,2)+offset] : 0.0), 0.0, "t", "sbar");
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpFF(2,3,3)+offset] : 0.0), 0.0, "t", "bbar");

      // neutralino+chargino decays
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpNeuCha(1,1)+offset] : 0.0), 0.0, "~chi0_1", "~chi+_1");
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpNeuCha(1,2)+offset] : 0.0), 0.0, "~chi0_1", "~chi+_2");
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpNeuCha(2,1)+offset] : 0.0), 0.0, "~chi0_2", "~chi+_1");
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpNeuCha(2,2)+offset] : 0.0), 0.0, "~chi0_2", "~chi+_2");
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpNeuCha(3,1)+offset] : 0.0), 0.0, "~chi0_3", "~chi+_1");
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpNeuCha(3,2)+offset] : 0.0), 0.0, "~chi0_3", "~chi+_2");
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpNeuCha(4,1)+offset] : 0.0), 0.0, "~chi0_4", "~chi+_1");
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpNeuCha(4,2)+offset] : 0.0), 0.0, "~chi0_4", "~chi+_2");

      // higgs + W decays
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpHV(1)+offset] : 0.0), 0.0, "W+", "h0_1");
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpHV(2)+offset] : 0.0), 0.0, "W+", "h0_2");
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpHV(3)+offset] : 0.0), 0.0, "W+", "A0");

      // sfermion decays
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpSfSf(1,1,1,1,1)+offset] : 0.0), 0.0, psn.isellbar, psn.isnel);
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpSfSf(1,1,1,2,2)+offset] : 0.0), 0.0, psn.ismulbar, psn.isnmul);
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpSfSf(1,1,1,3,3)+offset] : 0.0), 0.0, psn.istau1bar, psn.isntaul);
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpSfSf(2,1,1,3,3)+offset] : 0.0), 0.0, psn.istau2bar, psn.isntaul);
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpSfSf(1,1,2,1,1)+offset] : 0.0), 0.0, psn.isul, psn.isdlbar);
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpSfSf(1,2,2,1,1)+offset] : 0.0), 0.0, psn.isul, psn.isdrbar);
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpSfSf(2,1,2,1,1)+offset] : 0.0), 0.0, psn.isur, psn.isdlbar);
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpSfSf(2,2,2,1,1)+offset] : 0.0), 0.0, psn.isur, psn.isdrbar);
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpSfSf(1,1,2,1,2)+offset] : 0.0), 0.0, psn.isul, psn.isslbar);
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpSfSf(1,2,2,1,2)+offset] : 0.0), 0.0, psn.isul, psn.issrbar);
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpSfSf(2,1,2,1,2)+offset] : 0.0), 0.0, psn.isur, psn.isslbar);
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpSfSf(2,2,2,1,2)+offset] : 0.0), 0.0, psn.isur, psn.issrbar);
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpSfSf(1,1,2,1,3)+offset] : 0.0), 0.0, psn.isul, psn.isb1bar);
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpSfSf(1,2,2,1,3)+offset] : 0.0), 0.0, psn.isul, psn.isb2bar);
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpSfSf(2,1,2,1,3)+offset] : 0.0), 0.0, psn.isur, psn.isb1bar);
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpSfSf(2,2,2,1,3)+offset] : 0.0), 0.0, psn.isur, psn.isb2bar);
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpSfSf(1,1,2,2,1)+offset] : 0.0), 0.0, psn.iscl, psn.isdlbar);
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpSfSf(1,2,2,2,1)+offset] : 0.0), 0.0, psn.iscl, psn.isdrbar);
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpSfSf(2,1,2,2,1)+offset] : 0.0), 0.0, psn.iscr, psn.isdlbar);
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpSfSf(2,2,2,2,1)+offset] : 0.0), 0.0, psn.iscr, psn.isdrbar);
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpSfSf(1,1,2,2,2)+offset] : 0.0), 0.0, psn.iscl, psn.isslbar);
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpSfSf(1,2,2,2,2)+offset] : 0.0), 0.0, psn.iscl, psn.issrbar);
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpSfSf(2,1,2,2,2)+offset] : 0.0), 0.0, psn.iscr, psn.isslbar);
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpSfSf(2,2,2,2,2)+offset] : 0.0), 0.0, psn.iscr, psn.issrbar);
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpSfSf(1,1,2,2,3)+offset] : 0.0), 0.0, psn.iscl, psn.isb1bar);
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpSfSf(1,2,2,2,3)+offset] : 0.0), 0.0, psn.iscl, psn.isb2bar);
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpSfSf(2,1,2,2,3)+offset] : 0.0), 0.0, psn.iscr, psn.isb1bar);
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpSfSf(2,2,2,2,3)+offset] : 0.0), 0.0, psn.iscr, psn.isb2bar);
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpSfSf(1,1,2,3,1)+offset] : 0.0), 0.0, psn.ist1, psn.isdlbar);
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpSfSf(1,2,2,3,1)+offset] : 0.0), 0.0, psn.ist1, psn.isdrbar);
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpSfSf(2,1,2,3,1)+offset] : 0.0), 0.0, psn.ist2, psn.isdlbar);
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpSfSf(2,2,2,3,1)+offset] : 0.0), 0.0, psn.ist2, psn.isdrbar);
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpSfSf(1,1,2,3,2)+offset] : 0.0), 0.0, psn.ist1, psn.isslbar);
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpSfSf(1,2,2,3,2)+offset] : 0.0), 0.0, psn.ist1, psn.issrbar);
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpSfSf(2,1,2,3,2)+offset] : 0.0), 0.0, psn.ist2, psn.isslbar);
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpSfSf(2,2,2,3,2)+offset] : 0.0), 0.0, psn.ist2, psn.issrbar);
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpSfSf(1,1,2,3,3)+offset] : 0.0), 0.0, psn.ist1, psn.isb1bar);
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpSfSf(1,2,2,3,3)+offset] : 0.0), 0.0, psn.ist1, psn.isb2bar);
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpSfSf(2,1,2,3,3)+offset] : 0.0), 0.0, psn.ist2, psn.isb1bar);
      result.set_BF((result.width_in_GeV > 0 ? FH_input.gammas[HpSfSf(2,2,2,3,3)+offset] : 0.0), 0.0, psn.ist2, psn.isb2bar);

      check_width(LOCAL_INFO, result.width_in_GeV, runOptions->getValueOrDef<bool>(false, "invalid_point_for_negative_width"));
    }

    /// SUSY-HIT MSSM decays: h0_1
    void MSSM_h0_1_decays (DecayTable::Entry& result)
    {
      using namespace Pipes::MSSM_h0_1_decays;
      mass_es_pseudonyms psn = *(Dep::SLHA_pseudonyms);

      result.calculator = BEreq::cb_widthhl_hdec.origin();
      result.calculator_version = BEreq::cb_widthhl_hdec.version();

      result.width_in_GeV = BEreq::cb_widthhl_hdec->hlwdth;
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_widthhl_hdec->hlbrb : 0.0), 0.0, "b", "bbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_widthhl_hdec->hlbrl : 0.0), 0.0, "tau+", "tau-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_widthhl_hdec->hlbrm : 0.0), 0.0, "mu+", "mu-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_widthhl_hdec->hlbrs : 0.0), 0.0, "s", "sbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_widthhl_hdec->hlbrc : 0.0), 0.0, "c", "cbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_widthhl_hdec->hlbrt : 0.0), 0.0, "t", "tbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_widthhl_hdec->hlbrg : 0.0), 0.0, "g", "g");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_widthhl_hdec->hlbrga : 0.0), 0.0, "gamma", "gamma");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_widthhl_hdec->hlbrzga : 0.0), 0.0, "gamma", "Z0");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_widthhl_hdec->hlbrw : 0.0), 0.0, "W+", "W-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_widthhl_hdec->hlbrhw/2.0 : 0.0), 0.0, "W+", "H-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_widthhl_hdec->hlbrhw/2.0 : 0.0), 0.0, "W-", "H+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_widthhl_hdec->hlbrz : 0.0), 0.0, "Z0", "Z0");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->hlbrsc(1,1) : 0.0), 0.0, "~chi+_1", "~chi-_1");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->hlbrsc(2,2) : 0.0), 0.0, "~chi+_2", "~chi-_2");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->hlbrsc(1,2) : 0.0), 0.0, "~chi+_1", "~chi-_2");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->hlbrsc(2,1) : 0.0), 0.0, "~chi+_2", "~chi-_1");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->hlbrsn(1,1) : 0.0), 0.0, "~chi0_1", "~chi0_1");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->hlbrsn(2,2) : 0.0), 0.0, "~chi0_2", "~chi0_2");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->hlbrsn(3,3) : 0.0), 0.0, "~chi0_3", "~chi0_3");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->hlbrsn(4,4) : 0.0), 0.0, "~chi0_4", "~chi0_4");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->hlbrsn(1,2)*2.0 : 0.0), 0.0, "~chi0_1", "~chi0_2");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->hlbrsn(1,3)*2.0 : 0.0), 0.0, "~chi0_1", "~chi0_3");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->hlbrsn(1,4)*2.0 : 0.0), 0.0, "~chi0_1", "~chi0_4");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->hlbrsn(2,3)*2.0 : 0.0), 0.0, "~chi0_2", "~chi0_3");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->hlbrsn(2,4)*2.0 : 0.0), 0.0, "~chi0_2", "~chi0_4");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->hlbrsn(3,4)*2.0 : 0.0), 0.0, "~chi0_3", "~chi0_4");

      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhlsqul/2.0 : 0.0), 0.0, psn.isul, psn.isulbar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhlsqur/2.0 : 0.0), 0.0, psn.isur, psn.isurbar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhlsqul/2.0 : 0.0), 0.0, psn.iscl, psn.isclbar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhlsqur/2.0 : 0.0), 0.0, psn.iscr, psn.iscrbar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhlst(1,1) : 0.0), 0.0, psn.ist1, psn.ist1bar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhlst(2,2) : 0.0), 0.0, psn.ist2, psn.ist2bar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhlst(1,2) : 0.0), 0.0, psn.ist1, psn.ist2bar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhlst(2,1) : 0.0), 0.0, psn.ist2, psn.ist1bar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhlsqdl/2.0 : 0.0), 0.0, psn.isdl, psn.isdlbar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhlsqdr/2.0 : 0.0), 0.0, psn.isdr, psn.isdrbar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhlsqdl/2.0 : 0.0), 0.0, psn.issl, psn.isslbar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhlsqdr/2.0 : 0.0), 0.0, psn.issr, psn.issrbar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhlsb(1,1) : 0.0), 0.0, psn.isb1, psn.isb1bar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhlsb(2,2) : 0.0), 0.0, psn.isb2, psn.isb2bar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhlsb(1,2) : 0.0), 0.0, psn.isb1, psn.isb2bar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhlsb(2,1) : 0.0), 0.0, psn.isb2, psn.isb1bar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhlslel/2.0 : 0.0), 0.0, psn.isell, psn.isellbar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhlsler/2.0 : 0.0), 0.0, psn.iselr, psn.iselrbar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhlslel/2.0 : 0.0), 0.0, psn.ismul, psn.ismulbar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhlsler/2.0 : 0.0), 0.0, psn.ismur, psn.ismurbar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhlstau(1,1) : 0.0), 0.0, psn.istau1, psn.istau1bar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhlstau(2,2) : 0.0), 0.0, psn.istau2, psn.istau2bar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhlstau(1,2) : 0.0), 0.0, psn.istau1, psn.istau2bar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhlstau(2,1) : 0.0), 0.0, psn.istau2, psn.istau1bar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhlslnl/3.0 : 0.0), 0.0, psn.isnel, psn.isnelbar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhlslnl/3.0 : 0.0), 0.0, psn.isnmul, psn.isnmulbar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhlslnl/3.0 : 0.0), 0.0, psn.isntaul, psn.isntaulbar);

      check_width(LOCAL_INFO, result.width_in_GeV, runOptions->getValueOrDef<bool>(false, "invalid_point_for_negative_width"), true);
    }

    /// SUSY-HIT MSSM decays: h0_2
    void h0_2_decays (DecayTable::Entry& result)
    {
      using namespace Pipes::h0_2_decays;
      mass_es_pseudonyms psn = *(Dep::SLHA_pseudonyms);

      result.calculator = BEreq::cb_widthhh_hdec.origin();
      result.calculator_version = BEreq::cb_widthhh_hdec.version();

      result.width_in_GeV = BEreq::cb_widthhh_hdec->hhwdth;
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_widthhh_hdec->hhbrb : 0.0), 0.0, "b", "bbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_widthhh_hdec->hhbrl : 0.0), 0.0, "tau+", "tau-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_widthhh_hdec->hhbrm : 0.0), 0.0, "mu+", "mu-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_widthhh_hdec->hhbrs : 0.0), 0.0, "s", "sbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_widthhh_hdec->hhbrc : 0.0), 0.0, "c", "cbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_widthhh_hdec->hhbrt : 0.0), 0.0, "t", "tbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_widthhh_hdec->hhbrg : 0.0), 0.0, "g", "g");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_widthhh_hdec->hhbrga : 0.0), 0.0, "gamma", "gamma");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_widthhh_hdec->hhbrzga : 0.0), 0.0, "Z0", "gamma");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_widthhh_hdec->hhbrw : 0.0), 0.0, "W+", "W-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_widthhh_hdec->hhbrz : 0.0), 0.0, "Z0", "Z0");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_widthhh_hdec->hhbrh : 0.0), 0.0, "h0_1", "h0_1");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_widthhh_hdec->hhbra : 0.0), 0.0, "A0", "A0");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_widthhh_hdec->hhbraz : 0.0), 0.0, "Z0", "A0");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_widthhh_hdec->hhbrhw/2.0 : 0.0), 0.0, "W+", "H-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_widthhh_hdec->hhbrhw/2.0 : 0.0), 0.0, "W-", "H+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->hhbrsc(1,1) : 0.0), 0.0, "~chi+_1", "~chi-_1");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->hhbrsc(2,2) : 0.0), 0.0, "~chi+_2", "~chi-_2");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->hhbrsc(1,2) : 0.0), 0.0, "~chi+_1", "~chi-_2");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->hhbrsc(2,1) : 0.0), 0.0, "~chi+_2", "~chi-_1");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->hhbrsn(1,1) : 0.0), 0.0, "~chi0_1", "~chi0_1");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->hhbrsn(2,2) : 0.0), 0.0, "~chi0_2", "~chi0_2");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->hhbrsn(3,3) : 0.0), 0.0, "~chi0_3", "~chi0_3");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->hhbrsn(4,4) : 0.0), 0.0, "~chi0_4", "~chi0_4");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->hhbrsn(1,2)*2.0 : 0.0), 0.0, "~chi0_1", "~chi0_2");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->hhbrsn(1,3)*2.0 : 0.0), 0.0, "~chi0_1", "~chi0_3");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->hhbrsn(1,4)*2.0 : 0.0), 0.0, "~chi0_1", "~chi0_4");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->hhbrsn(2,3)*2.0 : 0.0), 0.0, "~chi0_2", "~chi0_3");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->hhbrsn(2,4)*2.0 : 0.0), 0.0, "~chi0_2", "~chi0_4");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->hhbrsn(3,4)*2.0 : 0.0), 0.0, "~chi0_3", "~chi0_4");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhhsqul/2.0 : 0.0), 0.0, psn.isul, psn.isulbar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhhsqur/2.0 : 0.0), 0.0, psn.isur, psn.isurbar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhhsqul/2.0 : 0.0), 0.0, psn.iscl, psn.isclbar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhhsqur/2.0 : 0.0), 0.0, psn.iscr, psn.iscrbar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhhst(1,1) : 0.0), 0.0, psn.ist1, psn.ist1bar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhhst(2,2) : 0.0), 0.0, psn.ist2, psn.ist2bar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhhst(1,2) : 0.0), 0.0, psn.ist1, psn.ist2bar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhhst(2,1) : 0.0), 0.0, psn.ist2, psn.ist1bar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhhsqdl/2.0 : 0.0), 0.0, psn.isdl, psn.isdlbar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhhsqdr/2.0 : 0.0), 0.0, psn.isdr, psn.isdrbar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhhsqdl/2.0 : 0.0), 0.0, psn.issl, psn.isslbar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhhsqdr/2.0 : 0.0), 0.0, psn.issr, psn.issrbar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhhsb(1,1) : 0.0), 0.0, psn.isb1, psn.isb1bar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhhsb(2,2) : 0.0), 0.0, psn.isb2, psn.isb2bar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhhsb(1,2) : 0.0), 0.0, psn.isb1, psn.isb2bar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhhsb(2,1) : 0.0), 0.0, psn.isb2, psn.isb1bar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhhslel/2.0 : 0.0), 0.0, psn.isell, psn.isellbar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhhsler/2.0 : 0.0), 0.0, psn.iselr, psn.iselrbar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhhslel/2.0 : 0.0), 0.0, psn.ismul, psn.ismulbar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhhsler/2.0 : 0.0), 0.0, psn.ismur, psn.ismurbar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhhstau(1,1) : 0.0), 0.0, psn.istau1, psn.istau1bar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhhstau(2,2) : 0.0), 0.0, psn.istau2, psn.istau2bar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhhstau(1,2) : 0.0), 0.0, psn.istau1, psn.istau2bar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhhstau(2,1) : 0.0), 0.0, psn.istau2, psn.istau1bar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhhslnl/3.0 : 0.0), 0.0, psn.isnel, psn.isnelbar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhhslnl/3.0 : 0.0), 0.0, psn.isnmul, psn.isnmulbar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhhslnl/3.0 : 0.0), 0.0, psn.isntaul, psn.isntaulbar);

      check_width(LOCAL_INFO, result.width_in_GeV, runOptions->getValueOrDef<bool>(false, "invalid_point_for_negative_width"), true);
    }

    /// SUSY-HIT MSSM decays: A0
    void A0_decays (DecayTable::Entry& result)
    {
      using namespace Pipes::A0_decays;
      mass_es_pseudonyms psn = *(Dep::SLHA_pseudonyms);

      result.calculator = BEreq::cb_widtha_hdec.origin();
      result.calculator_version = BEreq::cb_widtha_hdec.version();

      result.width_in_GeV = BEreq::cb_widtha_hdec->awdth;
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_widtha_hdec->abrb : 0.0), 0.0, "b", "bbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_widtha_hdec->abrl : 0.0), 0.0, "tau+", "tau-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_widtha_hdec->abrm : 0.0), 0.0, "mu+", "mu-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_widtha_hdec->abrs : 0.0), 0.0, "s", "sbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_widtha_hdec->abrc : 0.0), 0.0, "c", "cbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_widtha_hdec->abrt : 0.0), 0.0, "t", "tbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_widtha_hdec->abrg : 0.0), 0.0, "g", "g");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_widtha_hdec->abrga : 0.0), 0.0, "gamma", "gamma");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_widtha_hdec->abrzga : 0.0), 0.0, "Z0", "gamma");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_widtha_hdec->abrz : 0.0), 0.0, "Z0", "h0_1");
      result.set_BF(0.0, 0.0, "Z0", "Z0");
      result.set_BF(0.0, 0.0, "W+", "W-");
      result.set_BF(0.0, 0.0, "h0_1", "h0_1");
      result.set_BF(0.0, 0.0, "h0_2", "h0_2");
      result.set_BF(0.0, 0.0, "~nu_1", "~nubar_1");
      result.set_BF(0.0, 0.0, "~nu_2", "~nubar_2");
      result.set_BF(0.0, 0.0, "~nu_3", "~nubar_3");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->habrsc(1,1) : 0.0), 0.0, "~chi+_1", "~chi-_1");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->habrsc(2,2) : 0.0), 0.0, "~chi+_2", "~chi-_2");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->habrsc(1,2) : 0.0), 0.0, "~chi+_1", "~chi-_2");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->habrsc(2,1) : 0.0), 0.0, "~chi+_2", "~chi-_1");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->habrsn(1,1) : 0.0), 0.0, "~chi0_1", "~chi0_1");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->habrsn(2,2) : 0.0), 0.0, "~chi0_2", "~chi0_2");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->habrsn(3,3) : 0.0), 0.0, "~chi0_3", "~chi0_3");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->habrsn(4,4) : 0.0), 0.0, "~chi0_4", "~chi0_4");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->habrsn(1,2)*2.0 : 0.0), 0.0, "~chi0_1", "~chi0_2");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->habrsn(1,3)*2.0 : 0.0), 0.0, "~chi0_1", "~chi0_3");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->habrsn(1,4)*2.0 : 0.0), 0.0, "~chi0_1", "~chi0_4");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->habrsn(2,3)*2.0 : 0.0), 0.0, "~chi0_2", "~chi0_3");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->habrsn(2,4)*2.0 : 0.0), 0.0, "~chi0_2", "~chi0_4");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->habrsn(3,4)*2.0 : 0.0), 0.0, "~chi0_3", "~chi0_4");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->habrst/2.0 : 0.0), 0.0, psn.ist1, psn.ist2bar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->habrst/2.0 : 0.0), 0.0, psn.ist1bar, psn.ist2);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->habrsb/2.0 : 0.0), 0.0, psn.isb1, psn.isb2bar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->habrsb/2.0 : 0.0), 0.0, psn.isb1bar, psn.isb2);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->habrsl/2.0 : 0.0), 0.0, psn.istau1, psn.istau2bar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->habrsl/2.0 : 0.0), 0.0, psn.istau1bar, psn.istau2);

      check_width(LOCAL_INFO, result.width_in_GeV, runOptions->getValueOrDef<bool>(false, "invalid_point_for_negative_width"));
    }

    /// SUSY-HIT MSSM decays: H_plus
    void H_plus_decays (DecayTable::Entry& result)
    {
      using namespace Pipes::H_plus_decays;
      mass_es_pseudonyms psn = *(Dep::SLHA_pseudonyms);

      result.calculator = BEreq::cb_widthhc_hdec.origin();
      result.calculator_version = BEreq::cb_widthhc_hdec.version();

      result.width_in_GeV = BEreq::cb_widthhc_hdec->hcwdth;
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_widthhc_hdec->hcbrb: 0.0), 0.0, "c", "bbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_widthhc_hdec->hcbrl: 0.0), 0.0, "tau+", "nu_tau");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_widthhc_hdec->hcbrm: 0.0), 0.0, "mu+", "nu_mu");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_widthhc_hdec->hcbrbu: 0.0), 0.0, "u", "bbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_widthhc_hdec->hcbrs: 0.0), 0.0, "u", "sbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_widthhc_hdec->hcbrc: 0.0), 0.0, "c", "sbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_widthhc_hdec->hcbrt: 0.0), 0.0, "t", "bbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_widthhc_hdec->hcbrw: 0.0), 0.0, "W+", "h0_1");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_widthhc_hdec->hcbra: 0.0), 0.0, "W+", "A0");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->hcbrsu(1,1) : 0.0), 0.0, "~chi+_1", "~chi0_1");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->hcbrsu(1,2) : 0.0), 0.0, "~chi+_1", "~chi0_2");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->hcbrsu(1,3) : 0.0), 0.0, "~chi+_1", "~chi0_3");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->hcbrsu(1,4) : 0.0), 0.0, "~chi+_1", "~chi0_4");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->hcbrsu(2,1) : 0.0), 0.0, "~chi+_2", "~chi0_1");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->hcbrsu(2,2) : 0.0), 0.0, "~chi+_2", "~chi0_2");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->hcbrsu(2,3) : 0.0), 0.0, "~chi+_2", "~chi0_3");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->hcbrsu(2,4) : 0.0), 0.0, "~chi+_2", "~chi0_4");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhcsl00/2.0: 0.0), 0.0, psn.isellbar, psn.isnel);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhcsl00/2.0: 0.0), 0.0, psn.ismulbar, psn.isnmul);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhcsl11: 0.0), 0.0, psn.istau1bar, psn.isntaul);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisfer_hdec->bhcsl21: 0.0), 0.0, psn.istau2bar, psn.isntaul);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->hcbrsq/2.0: 0.0), 0.0, psn.isul, psn.isdlbar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->hcbrsq/2.0: 0.0), 0.0, psn.iscl, psn.isslbar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->hcbrstb(1,1) : 0.0), 0.0, psn.ist1, psn.isb1bar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->hcbrstb(2,2) : 0.0), 0.0, psn.ist2, psn.isb2bar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->hcbrstb(1,2) : 0.0), 0.0, psn.ist1, psn.isb2bar);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_wisusy_hdec->hcbrstb(2,1) : 0.0), 0.0, psn.ist2, psn.isb1bar);

      check_width(LOCAL_INFO, result.width_in_GeV, runOptions->getValueOrDef<bool>(false, "invalid_point_for_negative_width"));
    }

    /// SUSY-HIT MSSM decays: gluino
    void gluino_decays (DecayTable::Entry& result)
    {
      using namespace Pipes::gluino_decays;
      mass_es_pseudonyms psn = *(Dep::SLHA_pseudonyms);

      result.calculator = BEreq::cb_sd_gluiwidth.origin();
      result.calculator_version = BEreq::cb_sd_gluiwidth.version();

      result.width_in_GeV = BEreq::cb_sd_gluiwidth->gluitot;
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui2body->brgsdownl : 0.0), 0.0, psn.isdl, "dbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui2body->brgsdownl : 0.0), 0.0, psn.isdlbar, "d");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui2body->brgsdownr : 0.0), 0.0, psn.isdr, "dbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui2body->brgsdownr : 0.0), 0.0, psn.isdrbar, "d");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui2body->brgsupl : 0.0), 0.0, psn.isul, "ubar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui2body->brgsupl : 0.0), 0.0, psn.isulbar, "u");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui2body->brgsupr : 0.0), 0.0, psn.isur, "ubar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui2body->brgsupr : 0.0), 0.0, psn.isurbar, "u");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui2body->brgsdownl : 0.0), 0.0, psn.issl, "sbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui2body->brgsdownl : 0.0), 0.0, psn.isslbar, "s");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui2body->brgsdownr : 0.0), 0.0, psn.issr, "sbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui2body->brgsdownr : 0.0), 0.0, psn.issrbar, "s");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui2body->brgsupl : 0.0), 0.0, psn.iscl, "cbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui2body->brgsupl : 0.0), 0.0, psn.isclbar, "c");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui2body->brgsupr : 0.0), 0.0, psn.iscr, "cbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui2body->brgsupr : 0.0), 0.0, psn.iscrbar, "c");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui2body->brgsb1 : 0.0), 0.0, psn.isb1, "bbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui2body->brgsb1 : 0.0), 0.0, psn.isb1bar, "b");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui2body->brgsb2 : 0.0), 0.0, psn.isb2, "bbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui2body->brgsb2 : 0.0), 0.0, psn.isb2bar, "b");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui2body->brgst1 : 0.0), 0.0, psn.ist1, "tbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui2body->brgst1 : 0.0), 0.0, psn.ist1bar, "t");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui2body->brgst2 : 0.0), 0.0, psn.ist2, "tbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui2body->brgst2 : 0.0), 0.0, psn.ist2bar, "t");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_gluiloop->brglnjgluon(1) : 0.0), 0.0, "~chi0_1", "g");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_gluiloop->brglnjgluon(2) : 0.0), 0.0, "~chi0_2", "g");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_gluiloop->brglnjgluon(3) : 0.0), 0.0, "~chi0_3", "g");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_gluiloop->brglnjgluon(4) : 0.0), 0.0, "~chi0_4", "g");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui3body->brgodn(1) : 0.0), 0.0, "~chi0_1", "d", "dbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui3body->brgodn(2) : 0.0), 0.0, "~chi0_2", "d", "dbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui3body->brgodn(3) : 0.0), 0.0, "~chi0_3", "d", "dbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui3body->brgodn(4) : 0.0), 0.0, "~chi0_4", "d", "dbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui3body->brgoup(1) : 0.0), 0.0, "~chi0_1", "u", "ubar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui3body->brgoup(2) : 0.0), 0.0, "~chi0_2", "u", "ubar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui3body->brgoup(3) : 0.0), 0.0, "~chi0_3", "u", "ubar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui3body->brgoup(4) : 0.0), 0.0, "~chi0_4", "u", "ubar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui3body->brgodn(1) : 0.0), 0.0, "~chi0_1", "s", "sbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui3body->brgodn(2) : 0.0), 0.0, "~chi0_2", "s", "sbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui3body->brgodn(3) : 0.0), 0.0, "~chi0_3", "s", "sbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui3body->brgodn(4) : 0.0), 0.0, "~chi0_4", "s", "sbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui3body->brgoup(1) : 0.0), 0.0, "~chi0_1", "c", "cbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui3body->brgoup(2) : 0.0), 0.0, "~chi0_2", "c", "cbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui3body->brgoup(3) : 0.0), 0.0, "~chi0_3", "c", "cbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui3body->brgoup(4) : 0.0), 0.0, "~chi0_4", "c", "cbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui3body->brgobt(1) : 0.0), 0.0, "~chi0_1", "b", "bbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui3body->brgobt(2) : 0.0), 0.0, "~chi0_2", "b", "bbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui3body->brgobt(3) : 0.0), 0.0, "~chi0_3", "b", "bbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui3body->brgobt(4) : 0.0), 0.0, "~chi0_4", "b", "bbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui3body->brgotp(1) : 0.0), 0.0, "~chi0_1", "t", "tbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui3body->brgotp(2) : 0.0), 0.0, "~chi0_2", "t", "tbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui3body->brgotp(3) : 0.0), 0.0, "~chi0_3", "t", "tbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui3body->brgotp(4) : 0.0), 0.0, "~chi0_4", "t", "tbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui3body->brgoud(1) : 0.0), 0.0, "~chi+_1", "d", "ubar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui3body->brgoud(1) : 0.0), 0.0, "~chi-_1", "u", "dbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui3body->brgoud(2) : 0.0), 0.0, "~chi+_2", "d", "ubar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui3body->brgoud(2) : 0.0), 0.0, "~chi-_2", "u", "dbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui3body->brgoud(1) : 0.0), 0.0, "~chi+_1", "s", "cbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui3body->brgoud(1) : 0.0), 0.0, "~chi-_1", "c", "sbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui3body->brgoud(2) : 0.0), 0.0, "~chi+_2", "s", "cbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui3body->brgoud(2) : 0.0), 0.0, "~chi-_2", "c", "sbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui3body->brgotb(1) : 0.0), 0.0, "~chi+_1", "b", "tbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui3body->brgotb(1) : 0.0), 0.0, "~chi-_1", "t", "bbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui3body->brgotb(2) : 0.0), 0.0, "~chi+_2", "b", "tbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui3body->brgotb(2) : 0.0), 0.0, "~chi-_2", "t", "bbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui3body->brwst1b : 0.0), 0.0, psn.ist1, "bbar", "W-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui3body->brwst1b : 0.0), 0.0, psn.ist1bar, "b", "W+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui3body->brhcst1b : 0.0), 0.0, psn.ist1, "bbar", "H-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_glui3body->brhcst1b : 0.0), 0.0, psn.ist1bar, "b", "H+");

      check_width(LOCAL_INFO, result.width_in_GeV, runOptions->getValueOrDef<bool>(false, "invalid_point_for_negative_width"));
    }

    /// SUSY-HIT MSSM decays: stop_1
    void stop_1_decays (DecayTable::Entry& result)
    {
      using namespace Pipes::stop_1_decays;
      mass_es_pseudonyms psn = *(Dep::SLHA_pseudonyms);

      static const bool allow_offshell_modes = runOptions->getValueOrDef<bool>(true, "allow_offshell_modes_in_decay_table");
      
      result.calculator = BEreq::cb_sd_stopwidth.origin();
      result.calculator_version = BEreq::cb_sd_stopwidth.version();

      result.width_in_GeV = BEreq::cb_sd_stopwidth->stoptot(1);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop2body->brst1neutt(1) : 0.0), 0.0, "~chi0_1", "t");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop2body->brst1neutt(2) : 0.0), 0.0, "~chi0_2", "t");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop2body->brst1neutt(3) : 0.0), 0.0, "~chi0_3", "t");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop2body->brst1neutt(4) : 0.0), 0.0, "~chi0_4", "t");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop2body->brst1charb(1) : 0.0), 0.0, "~chi+_1", "b");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop2body->brst1charb(2) : 0.0), 0.0, "~chi+_2", "b");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop2body->brst1glui : 0.0), 0.0, "~g", "t");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop2body->brst1hcsb(1) : 0.0), 0.0, psn.isb1, "H+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop2body->brst1hcsb(2) : 0.0), 0.0, psn.isb2, "H+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop2body->brst1wsb(1) : 0.0), 0.0, psn.isb1, "W+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop2body->brst1wsb(2) : 0.0), 0.0, psn.isb2, "W+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stoploop->brgamma : 0.0), 0.0, "~chi0_1", "c");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stoploop->brgammaup : 0.0), 0.0, "~chi0_1", "u");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stoploop->brgammagluino : 0.0), 0.0, "~g", "c");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brstopw(1,1) : 0.0), 0.0, "~chi0_1", "b", "W+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brstopw(1,2) : 0.0), 0.0, "~chi0_2", "b", "W+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brstopw(1,3) : 0.0), 0.0, "~chi0_3", "b", "W+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brstopw(1,4) : 0.0), 0.0, "~chi0_4", "b", "W+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brstoph(1,1) : 0.0), 0.0, "~chi0_1", "b", "H+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brstoph(1,2) : 0.0), 0.0, "~chi0_2", "b", "H+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brstoph(1,3) : 0.0), 0.0, "~chi0_3", "b", "H+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brstoph(1,4) : 0.0), 0.0, "~chi0_4", "b", "H+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brstsntau(1,1) : 0.0), 0.0, psn.isntaul, "b", "tau+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brstsnel(1) : 0.0), 0.0, psn.isnel, "b", "e+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brstsnel(1) : 0.0), 0.0, psn.isnmul, "b", "mu+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brststau(1,1) : 0.0), 0.0, psn.istau1bar, "b", "nu_tau");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brststau(1,2) : 0.0), 0.0, psn.istau2bar, "b", "nu_tau");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brstsel(1,1) : 0.0), 0.0, psn.isellbar, "b", "nu_e");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brstsel(1,2) : 0.0), 0.0, psn.iselrbar, "b", "nu_e");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brstsel(1,1) : 0.0), 0.0, psn.ismulbar, "b", "nu_mu");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brstsel(1,2) : 0.0), 0.0, psn.ismurbar, "b", "nu_mu");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brstbsbst(1,1) : 0.0), 0.0, psn.isb1bar, "b", "t");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brstbsbst(1,2) : 0.0), 0.0, psn.isb2bar, "b", "t");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brstbbsbt(1,1) : 0.0), 0.0, psn.isb1, "bbar", "t");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brstbbsbt(1,2) : 0.0), 0.0, psn.isb2, "bbar", "t");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brstupsbdow(1,1) : 0.0), 0.0, psn.isb1, "dbar", "u");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brstupsbdow(1,2) : 0.0), 0.0, psn.isb2, "dbar", "u");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brstupsbdow(1,1) : 0.0), 0.0, psn.isb1, "sbar", "c");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brstupsbdow(1,2) : 0.0), 0.0, psn.isb2, "sbar", "c");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brsttausbnu(1,1) : 0.0), 0.0, psn.isb1, "tau+", "nu_tau");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brsttausbnu(1,2) : 0.0), 0.0, psn.isb2, "tau+", "nu_tau");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brstelsbnu(1,1) : 0.0), 0.0, psn.isb1, "e+", "nu_e");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brstelsbnu(1,2) : 0.0), 0.0, psn.isb2, "e+", "nu_e");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brstelsbnu(1,1) : 0.0), 0.0, psn.isb1, "mu+", "nu_mu");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brstelsbnu(1,2) : 0.0), 0.0, psn.isb2, "mu+", "nu_mu");

      if (BEreq::cb_sd_stop4body->br4bodoffshelltau > BEreq::cb_sd_stop3body->brstopw(1,1))
      {
        // Take the total 4-body BR(~t_1 -->  ~chi0_1 b f f') and assign to the off-shell mode BR(~t_1 -->  ~chi0_1 b W(*))
        if(allow_offshell_modes)
        {      
          result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop4body->br4bodoffshelltau : 0.0), 0.0, "~chi0_1", "b", "W+");
        }
        // This is a temp solution
        else
        {
          result.set_BF((result.width_in_GeV > 0 ? 0.1071 * BEreq::cb_sd_stop4body->br4bodoffshelltau : 0.0), 0.0, "~chi0_1", "b", "e+", "nu_e");
          result.set_BF((result.width_in_GeV > 0 ? 0.1063 * BEreq::cb_sd_stop4body->br4bodoffshelltau : 0.0), 0.0, "~chi0_1", "b", "mu+", "nu_mu");
          result.set_BF((result.width_in_GeV > 0 ? 0.1138 * BEreq::cb_sd_stop4body->br4bodoffshelltau : 0.0), 0.0, "~chi0_1", "b", "tau+", "nu_tau");
          result.set_BF((result.width_in_GeV > 0 ? 0.6741 * BEreq::cb_sd_stop4body->br4bodoffshelltau : 0.0), 0.0, "~chi0_1", "b", "hadron", "hadron");
        }
      }
      
      check_width(LOCAL_INFO, result.width_in_GeV, runOptions->getValueOrDef<bool>(false, "invalid_point_for_negative_width"));
    }

    /// SUSY-HIT MSSM decays: stop_2
    void stop_2_decays (DecayTable::Entry& result)
    {
      using namespace Pipes::stop_2_decays;
      mass_es_pseudonyms psn = *(Dep::SLHA_pseudonyms);

      result.calculator = BEreq::cb_sd_stopwidth.origin();
      result.calculator_version = BEreq::cb_sd_stopwidth.version();

      result.width_in_GeV = BEreq::cb_sd_stopwidth->stoptot(2);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop2body->brst2neutt(1) : 0.0), 0.0, "~chi0_1", "t");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop2body->brst2neutt(2) : 0.0), 0.0, "~chi0_2", "t");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop2body->brst2neutt(3) : 0.0), 0.0, "~chi0_3", "t");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop2body->brst2neutt(4) : 0.0), 0.0, "~chi0_4", "t");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop2body->brst2charb(1) : 0.0), 0.0, "~chi+_1", "b");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop2body->brst2charb(2) : 0.0), 0.0, "~chi+_2", "b");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop2body->brst2glui : 0.0), 0.0, "~g", "t");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop2body->brst2hl : 0.0), 0.0, psn.ist1, "h0_1");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop2body->brst2hh : 0.0), 0.0, psn.ist1, "h0_2");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop2body->brst2ha : 0.0), 0.0, psn.ist1, "A0");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop2body->brst2hcsb(1) : 0.0), 0.0, psn.isb1, "H+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop2body->brst2hcsb(2) : 0.0), 0.0, psn.isb2, "H+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop2body->brst2ztop : 0.0), 0.0, psn.ist1, "Z0");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop2body->brst2wsb(1) : 0.0), 0.0, psn.isb1, "W+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop2body->brst2wsb(2) : 0.0), 0.0, psn.isb2, "W+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brstopw(2,1) : 0.0), 0.0, "~chi0_1", "b", "W+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brstopw(2,2) : 0.0), 0.0, "~chi0_2", "b", "W+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brstopw(2,3) : 0.0), 0.0, "~chi0_3", "b", "W+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brstopw(2,4) : 0.0), 0.0, "~chi0_4", "b", "W+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brstoph(2,1) : 0.0), 0.0, "~chi0_1", "b", "H+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brstoph(2,2) : 0.0), 0.0, "~chi0_2", "b", "H+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brstoph(2,3) : 0.0), 0.0, "~chi0_3", "b", "H+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brstoph(2,4) : 0.0), 0.0, "~chi0_4", "b", "H+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brstsntau(2,1) : 0.0), 0.0, psn.isntaul, "b", "tau+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brstsnel(2) : 0.0), 0.0, psn.isnel, "b", "e+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brstsnel(2) : 0.0), 0.0, psn.isnmul, "b", "mu+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brststau(2,1) : 0.0), 0.0, psn.istau1bar, "b", "nu_tau");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brststau(2,2) : 0.0), 0.0, psn.istau2bar, "b", "nu_tau");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brstsel(2,1) : 0.0), 0.0, psn.isellbar, "b", "nu_e");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brstsel(2,2) : 0.0), 0.0, psn.iselrbar, "b", "nu_e");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brstsel(2,1) : 0.0), 0.0, psn.ismulbar, "b", "nu_mu");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brstsel(2,2) : 0.0), 0.0, psn.ismurbar, "b", "nu_mu");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brstbsbst(2,1) : 0.0), 0.0, psn.isb1bar, "b", "t");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brstbsbst(2,2) : 0.0), 0.0, psn.isb2bar, "b", "t");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brstbbsbt(2,1) : 0.0), 0.0, psn.isb1, "bbar", "t");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brstbbsbt(2,2) : 0.0), 0.0, psn.isb2, "bbar", "t");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brstupsbdow(2,1) : 0.0), 0.0, psn.isb1, "dbar", "u");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brstupsbdow(2,2) : 0.0), 0.0, psn.isb2, "dbar", "u");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brstupsbdow(2,1) : 0.0), 0.0, psn.isb1, "sbar", "c");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brstupsbdow(2,2) : 0.0), 0.0, psn.isb2, "sbar", "c");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brsttausbnu(2,1) : 0.0), 0.0, psn.isb1, "tau+", "nu_tau");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brsttausbnu(2,2) : 0.0), 0.0, psn.isb2, "tau+", "nu_tau");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brstelsbnu(2,1) : 0.0), 0.0, psn.isb1, "e+", "nu_e");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brstelsbnu(2,2) : 0.0), 0.0, psn.isb2, "e+", "nu_e");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brstelsbnu(2,1) : 0.0), 0.0, psn.isb1, "mu+", "nu_mu");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brstelsbnu(2,2) : 0.0), 0.0, psn.isb2, "mu+", "nu_mu");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brst2st1tt : 0.0), 0.0, psn.ist1, "t", "tbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brst2st1tt : 0.0), 0.0, psn.ist1bar, "t", "t");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brst2st1bb : 0.0), 0.0, psn.ist1, "b", "bbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brst2st1uu : 0.0), 0.0, psn.ist1, "u", "ubar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brst2st1dd : 0.0), 0.0, psn.ist1, "d", "dbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brst2st1uu : 0.0), 0.0, psn.ist1, "c", "cbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brst2st1dd : 0.0), 0.0, psn.ist1, "s", "sbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brst2st1ee : 0.0), 0.0, psn.ist1, "e-", "e+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brst2st1ee : 0.0), 0.0, psn.ist1, "mu-", "mu+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brst2st1tautau : 0.0), 0.0, psn.ist1, "tau-", "tau+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brst2st1nunu : 0.0), 0.0, psn.ist1, "nu_e", "nubar_e");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brst2st1nunu : 0.0), 0.0, psn.ist1, "nu_mu", "nubar_mu");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stop3body->brst2st1nunu : 0.0), 0.0, psn.ist1, "nu_tau", "nubar_tau");

      check_width(LOCAL_INFO, result.width_in_GeV, runOptions->getValueOrDef<bool>(false, "invalid_point_for_negative_width"));
    }

    /// SUSY-HIT MSSM decays: sbottom_1
    void sbottom_1_decays (DecayTable::Entry& result)
    {
      using namespace Pipes::sbottom_1_decays;
      mass_es_pseudonyms psn = *(Dep::SLHA_pseudonyms);

      result.calculator = BEreq::cb_sd_sbotwidth.origin();
      result.calculator_version = BEreq::cb_sd_sbotwidth.version();

      result.width_in_GeV = BEreq::cb_sd_sbotwidth->sbottot(1);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot2body->brsb1neutt(1) : 0.0), 0.0, "~chi0_1", "b");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot2body->brsb1neutt(2) : 0.0), 0.0, "~chi0_2", "b");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot2body->brsb1neutt(3) : 0.0), 0.0, "~chi0_3", "b");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot2body->brsb1neutt(4) : 0.0), 0.0, "~chi0_4", "b");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot2body->brsb1chart(1) : 0.0), 0.0, "~chi-_1", "t");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot2body->brsb1chart(2) : 0.0), 0.0, "~chi-_2", "t");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot2body->brsb1glui : 0.0), 0.0, "~g", "b");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot2body->brsb1hcst(1) : 0.0), 0.0, psn.ist1, "H-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot2body->brsb1hcst(2) : 0.0), 0.0, psn.ist2, "H-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot2body->brsb1wst(1) : 0.0), 0.0, psn.ist1, "W-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot2body->brsb1wst(2) : 0.0), 0.0, psn.ist2, "W-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsbsntau(1,1) : 0.0), 0.0, psn.isntaulbar, "t", "tau-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsbsnel(1) : 0.0), 0.0, psn.isnelbar, "t", "e-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsbsnel(1) : 0.0), 0.0, psn.isnmulbar, "t", "mu-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsbstau(1,1) : 0.0), 0.0, psn.istau1, "t", "nubar_tau");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsbstau(1,2) : 0.0), 0.0, psn.istau2, "t", "nubar_tau");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsbsel(1,1) : 0.0), 0.0, psn.isell, "t", "nubar_e");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsbsel(1,2) : 0.0), 0.0, psn.iselr, "t", "nubar_e");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsbsel(1,1) : 0.0), 0.0, psn.ismul, "t", "nubar_mu");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsbsel(1,2) : 0.0), 0.0, psn.ismur, "t", "nubar_mu");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsbtstsb(1,1) : 0.0), 0.0, psn.ist1bar, "t", "b");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsbtstsb(1,2) : 0.0), 0.0, psn.ist2bar, "t", "b");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsbtbstb(1,1) : 0.0), 0.0, psn.ist1, "tbar", "b");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsbtbstb(1,2) : 0.0), 0.0, psn.ist2, "tbar", "b");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsbupstdow(1,1) : 0.0), 0.0, psn.ist1, "ubar", "d");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsbupstdow(1,2) : 0.0), 0.0, psn.ist2, "ubar", "d");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsbupstdow(1,1) : 0.0), 0.0, psn.ist1, "cbar", "s");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsbupstdow(1,2) : 0.0), 0.0, psn.ist2, "cbar", "s");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsbtaustnu(1,1) : 0.0), 0.0, psn.ist1, "tau-", "nubar_tau");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsbtaustnu(1,2) : 0.0), 0.0, psn.ist2, "tau-", "nubar_tau");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsbelstnu(1,1) : 0.0), 0.0, psn.ist1, "e-", "nubar_e");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsbelstnu(1,2) : 0.0), 0.0, psn.ist1, "e-", "nubar_e");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsbelstnu(1,1) : 0.0), 0.0, psn.ist1, "mu-", "nubar_mu");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsbelstnu(1,2) : 0.0), 0.0, psn.ist1, "mu-", "nubar_mu");

      check_width(LOCAL_INFO, result.width_in_GeV, runOptions->getValueOrDef<bool>(false, "invalid_point_for_negative_width"));
    }

    /// SUSY-HIT MSSM decays: sbottom_2
    void sbottom_2_decays (DecayTable::Entry& result)
    {
      using namespace Pipes::sbottom_2_decays;
      mass_es_pseudonyms psn = *(Dep::SLHA_pseudonyms);

      result.calculator = BEreq::cb_sd_sbotwidth.origin();
      result.calculator_version = BEreq::cb_sd_sbotwidth.version();

      result.width_in_GeV = BEreq::cb_sd_sbotwidth->sbottot(2);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot2body->brsb2neutt(1) : 0.0), 0.0, "~chi0_1", "b");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot2body->brsb2neutt(2) : 0.0), 0.0, "~chi0_2", "b");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot2body->brsb2neutt(3) : 0.0), 0.0, "~chi0_3", "b");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot2body->brsb2neutt(4) : 0.0), 0.0, "~chi0_4", "b");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot2body->brsb2chart(1) : 0.0), 0.0, "~chi-_1", "t");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot2body->brsb2chart(2) : 0.0), 0.0, "~chi-_2", "t");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot2body->brsb2glui : 0.0), 0.0, "~g", "b");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot2body->brsb2hl : 0.0), 0.0, psn.isb1, "h0_1");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot2body->brsb2hh : 0.0), 0.0, psn.isb1, "h0_2");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot2body->brsb2ha : 0.0), 0.0, psn.isb1, "A0");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot2body->brsb2hcst(1) : 0.0), 0.0, psn.ist1, "H-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot2body->brsb2hcst(2) : 0.0), 0.0, psn.ist2, "H-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot2body->brsb2zbot : 0.0), 0.0, psn.isb1, "Z0");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot2body->brsb2wst(1) : 0.0), 0.0, psn.ist1, "W-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot2body->brsb2wst(2) : 0.0), 0.0, psn.ist2, "W-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsbsntau(2,1) : 0.0), 0.0, psn.isntaulbar, "t", "tau-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsbsnel(2) : 0.0), 0.0, psn.isnelbar, "t", "e-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsbsnel(2) : 0.0), 0.0, psn.isnmulbar, "t", "mu-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsbstau(2,1) : 0.0), 0.0, psn.istau1, "t", "nubar_tau");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsbstau(2,2) : 0.0), 0.0, psn.istau2, "t", "nubar_tau");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsbsel(2,1) : 0.0), 0.0, psn.isell, "t", "nubar_e");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsbsel(2,2) : 0.0), 0.0, psn.iselr, "t", "nubar_e");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsbsel(2,1) : 0.0), 0.0, psn.ismul, "t", "nubar_mu");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsbsel(2,2) : 0.0), 0.0, psn.ismur, "t", "nubar_mu");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsbtstsb(2,1) : 0.0), 0.0, psn.ist1bar, "t", "b");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsbtstsb(2,2) : 0.0), 0.0, psn.ist2bar, "t", "b");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsbtbstb(2,1) : 0.0), 0.0, psn.ist1, "tbar", "b");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsbtbstb(2,2) : 0.0), 0.0, psn.ist2, "tbar", "b");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsbupstdow(2,1) : 0.0), 0.0, psn.ist1, "ubar", "d");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsbupstdow(2,2) : 0.0), 0.0, psn.ist2, "ubar", "d");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsbupstdow(2,1) : 0.0), 0.0, psn.ist1, "cbar", "s");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsbupstdow(2,2) : 0.0), 0.0, psn.ist2, "cbar", "s");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsbtaustnu(2,1) : 0.0), 0.0, psn.ist1, "tau-", "nubar_tau");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsbtaustnu(2,2) : 0.0), 0.0, psn.ist2, "tau-", "nubar_tau");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsbelstnu(2,1) : 0.0), 0.0, psn.ist1, "e-", "nubar_e");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsbelstnu(2,2) : 0.0), 0.0, psn.ist1, "e-", "nubar_e");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsbelstnu(2,1) : 0.0), 0.0, psn.ist1, "mu-", "nubar_mu");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsbelstnu(2,2) : 0.0), 0.0, psn.ist1, "mu-", "nubar_mu");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsb2sb1bb : 0.0), 0.0, psn.isb1, "b", "bbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsb2sb1starbb : 0.0), 0.0, psn.isb1bar, "b", "b");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsb2sb1tt : 0.0), 0.0, psn.isb1, "t", "tbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsb2sb1uu : 0.0), 0.0, psn.isb1, "u", "ubar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsb2sb1dd : 0.0), 0.0, psn.isb1, "d", "dbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsb2sb1uu : 0.0), 0.0, psn.isb1, "c", "cbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsb2sb1dd : 0.0), 0.0, psn.isb1, "s", "sbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsb2sb1ee : 0.0), 0.0, psn.isb1, "e-", "e+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsb2sb1ee : 0.0), 0.0, psn.isb1, "mu-", "mu+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsb2sb1tautau : 0.0), 0.0, psn.isb1, "tau-", "tau+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsb2sb1nunu : 0.0), 0.0, psn.isb1, "nu_e", "nubar_e");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsb2sb1nunu : 0.0), 0.0, psn.isb1, "nu_mu", "nubar_mu");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sbot3body->brsb2sb1nunu : 0.0), 0.0, psn.isb1, "nu_tau", "nubar_tau");

      check_width(LOCAL_INFO, result.width_in_GeV, runOptions->getValueOrDef<bool>(false, "invalid_point_for_negative_width"));
    }

    /// SUSY-HIT MSSM decays: sup_l
    void sup_l_decays (DecayTable::Entry& result)
    {
      using namespace Pipes::sup_l_decays;

      result.calculator = BEreq::cb_sd_supwidth.origin();
      result.calculator_version = BEreq::cb_sd_supwidth.version();

      result.width_in_GeV = BEreq::cb_sd_supwidth->supltot2;
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sup2body->brsuplnup(1) : 0.0), 0.0, "~chi0_1", "u");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sup2body->brsuplnup(2) : 0.0), 0.0, "~chi0_2", "u");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sup2body->brsuplnup(3) : 0.0), 0.0, "~chi0_3", "u");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sup2body->brsuplnup(4) : 0.0), 0.0, "~chi0_4", "u");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sup2body->brsuplcdow(1) : 0.0), 0.0, "~chi+_1", "d");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sup2body->brsuplcdow(2) : 0.0), 0.0, "~chi+_2", "d");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sup2body->brsuplglui : 0.0), 0.0, "~g", "u");

      check_width(LOCAL_INFO, result.width_in_GeV, runOptions->getValueOrDef<bool>(false, "invalid_point_for_negative_width"));
    }

    /// SUSY-HIT MSSM decays: sup_r
    void sup_r_decays (DecayTable::Entry& result)
    {
      using namespace Pipes::sup_r_decays;
      result.calculator = BEreq::cb_sd_supwidth.origin();
      result.calculator_version = BEreq::cb_sd_supwidth.version();
      result.width_in_GeV = BEreq::cb_sd_supwidth->suprtot2;
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sup2body->brsuprnup(1) : 0.0), 0.0, "~chi0_1", "u");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sup2body->brsuprnup(2) : 0.0), 0.0, "~chi0_2", "u");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sup2body->brsuprnup(3) : 0.0), 0.0, "~chi0_3", "u");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sup2body->brsuprnup(4) : 0.0), 0.0, "~chi0_4", "u");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sup2body->brsuprcdow(1) : 0.0), 0.0, "~chi+_1", "d");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sup2body->brsuprcdow(2) : 0.0), 0.0, "~chi+_2", "d");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sup2body->brsuprglui : 0.0), 0.0, "~g", "u");
      check_width(LOCAL_INFO, result.width_in_GeV, runOptions->getValueOrDef<bool>(false, "invalid_point_for_negative_width"));
    }

    /// SUSY-HIT MSSM decays: sdown_l
    void sdown_l_decays (DecayTable::Entry& result)
    {
      using namespace Pipes::sdown_l_decays;
      result.calculator = BEreq::cb_sd_sdownwidth.origin();
      result.calculator_version = BEreq::cb_sd_sdownwidth.version();
      result.width_in_GeV = BEreq::cb_sd_sdownwidth->sdowltot2;
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sdown2body->brsdowlndow(1) : 0.0), 0.0, "~chi0_1", "d");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sdown2body->brsdowlndow(2) : 0.0), 0.0, "~chi0_2", "d");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sdown2body->brsdowlndow(3) : 0.0), 0.0, "~chi0_3", "d");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sdown2body->brsdowlndow(4) : 0.0), 0.0, "~chi0_4", "d");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sdown2body->brsdowlchup(1) : 0.0), 0.0, "~chi-_1", "u");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sdown2body->brsdowlchup(2) : 0.0), 0.0, "~chi-_2", "u");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sdown2body->brsdowlglui : 0.0), 0.0, "~g", "d");
      check_width(LOCAL_INFO, result.width_in_GeV, runOptions->getValueOrDef<bool>(false, "invalid_point_for_negative_width"));
    }

    /// SUSY-HIT MSSM decays: sdown_r
    void sdown_r_decays (DecayTable::Entry& result)
    {
      using namespace Pipes::sdown_r_decays;
      result.calculator = BEreq::cb_sd_sdownwidth.origin();
      result.calculator_version = BEreq::cb_sd_sdownwidth.version();
      result.width_in_GeV = BEreq::cb_sd_sdownwidth->sdowrtot2;
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sdown2body->brsdowrndow(1) : 0.0), 0.0, "~chi0_1", "d");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sdown2body->brsdowrndow(2) : 0.0), 0.0, "~chi0_2", "d");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sdown2body->brsdowrndow(3) : 0.0), 0.0, "~chi0_3", "d");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sdown2body->brsdowrndow(4) : 0.0), 0.0, "~chi0_4", "d");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sdown2body->brsdowrchup(1) : 0.0), 0.0, "~chi-_1", "u");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sdown2body->brsdowrchup(2) : 0.0), 0.0, "~chi-_2", "u");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sdown2body->brsdowrglui : 0.0), 0.0, "~g", "d");
      check_width(LOCAL_INFO, result.width_in_GeV, runOptions->getValueOrDef<bool>(false, "invalid_point_for_negative_width"));
    }

    /// SUSY-HIT MSSM decays: scharm_l
    void scharm_l_decays (DecayTable::Entry& result)
    {
      using namespace Pipes::scharm_l_decays;
      result.calculator = BEreq::cb_sd_supwidth.origin();
      result.calculator_version = BEreq::cb_sd_supwidth.version();
      result.width_in_GeV = BEreq::cb_sd_supwidth->supltot2;
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sup2body->brsuplnup(1) : 0.0), 0.0, "~chi0_1", "c");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sup2body->brsuplnup(2) : 0.0), 0.0, "~chi0_2", "c");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sup2body->brsuplnup(3) : 0.0), 0.0, "~chi0_3", "c");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sup2body->brsuplnup(4) : 0.0), 0.0, "~chi0_4", "c");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sup2body->brsuplcdow(1) : 0.0), 0.0, "~chi+_1", "s");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sup2body->brsuplcdow(2) : 0.0), 0.0, "~chi+_2", "s");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sup2body->brsuplglui : 0.0), 0.0, "~g", "c");
      check_width(LOCAL_INFO, result.width_in_GeV, runOptions->getValueOrDef<bool>(false, "invalid_point_for_negative_width"));
    }

    /// SUSY-HIT MSSM decays: scharm_r
    void scharm_r_decays (DecayTable::Entry& result)
    {
      using namespace Pipes::scharm_r_decays;
      result.calculator = BEreq::cb_sd_supwidth.origin();
      result.calculator_version = BEreq::cb_sd_supwidth.version();
      result.width_in_GeV = BEreq::cb_sd_supwidth->suprtot2;
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sup2body->brsuprnup(1) : 0.0), 0.0, "~chi0_1", "c");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sup2body->brsuprnup(2) : 0.0), 0.0, "~chi0_2", "c");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sup2body->brsuprnup(3) : 0.0), 0.0, "~chi0_3", "c");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sup2body->brsuprnup(4) : 0.0), 0.0, "~chi0_4", "c");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sup2body->brsuprcdow(1) : 0.0), 0.0, "~chi+_1", "s");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sup2body->brsuprcdow(2) : 0.0), 0.0, "~chi+_2", "s");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sup2body->brsuprglui : 0.0), 0.0, "~g", "c");
      check_width(LOCAL_INFO, result.width_in_GeV, runOptions->getValueOrDef<bool>(false, "invalid_point_for_negative_width"));
    }

    /// SUSY-HIT MSSM decays: sstrange_l
    void sstrange_l_decays (DecayTable::Entry& result)
    {
      using namespace Pipes::sstrange_l_decays;
      result.calculator = BEreq::cb_sd_sdownwidth.origin();
      result.calculator_version = BEreq::cb_sd_sdownwidth.version();
      result.width_in_GeV = BEreq::cb_sd_sdownwidth->sdowltot2;
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sdown2body->brsdowlndow(1) : 0.0), 0.0, "~chi0_1", "s");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sdown2body->brsdowlndow(2) : 0.0), 0.0, "~chi0_2", "s");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sdown2body->brsdowlndow(3) : 0.0), 0.0, "~chi0_3", "s");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sdown2body->brsdowlndow(4) : 0.0), 0.0, "~chi0_4", "s");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sdown2body->brsdowlchup(1) : 0.0), 0.0, "~chi-_1", "c");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sdown2body->brsdowlchup(2) : 0.0), 0.0, "~chi-_2", "c");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sdown2body->brsdowlglui : 0.0), 0.0, "~g", "s");
      check_width(LOCAL_INFO, result.width_in_GeV, runOptions->getValueOrDef<bool>(false, "invalid_point_for_negative_width"));
    }

    /// SUSY-HIT MSSM decays: sstrange_r
    void sstrange_r_decays (DecayTable::Entry& result)
    {
      using namespace Pipes::sstrange_r_decays;
      result.calculator = BEreq::cb_sd_sdownwidth.origin();
      result.calculator_version = BEreq::cb_sd_sdownwidth.version();
      result.width_in_GeV = BEreq::cb_sd_sdownwidth->sdowrtot2;
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sdown2body->brsdowrndow(1) : 0.0), 0.0, "~chi0_1", "s");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sdown2body->brsdowrndow(2) : 0.0), 0.0, "~chi0_2", "s");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sdown2body->brsdowrndow(3) : 0.0), 0.0, "~chi0_3", "s");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sdown2body->brsdowrndow(4) : 0.0), 0.0, "~chi0_4", "s");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sdown2body->brsdowrchup(1) : 0.0), 0.0, "~chi-_1", "c");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sdown2body->brsdowrchup(2) : 0.0), 0.0, "~chi-_2", "c");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sdown2body->brsdowrglui : 0.0), 0.0, "~g", "s");
      check_width(LOCAL_INFO, result.width_in_GeV, runOptions->getValueOrDef<bool>(false, "invalid_point_for_negative_width"));
    }

    /// SUSY-HIT MSSM decays: selectron_l
    void selectron_l_decays (DecayTable::Entry& result)
    {
      using namespace Pipes::selectron_l_decays;
      result.calculator = BEreq::cb_sd_selwidth.origin();
      result.calculator_version = BEreq::cb_sd_selwidth.version();
      result.width_in_GeV = BEreq::cb_sd_selwidth->selltot2;
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sel2body->brsellneute(1) : 0.0), 0.0, "~chi0_1", "e-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sel2body->brsellneute(2) : 0.0), 0.0, "~chi0_2", "e-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sel2body->brsellneute(3) : 0.0), 0.0, "~chi0_3", "e-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sel2body->brsellneute(4) : 0.0), 0.0, "~chi0_4", "e-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sel2body->brsellcharnue(1) : 0.0), 0.0, "~chi-_1", "nu_e");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sel2body->brsellcharnue(2) : 0.0), 0.0, "~chi-_2", "nu_e");
      check_width(LOCAL_INFO, result.width_in_GeV, runOptions->getValueOrDef<bool>(false, "invalid_point_for_negative_width"));
    }

    /// SUSY-HIT MSSM decays: selectron_r
    void selectron_r_decays (DecayTable::Entry& result)
    {
      using namespace Pipes::selectron_r_decays;
      result.calculator = BEreq::cb_sd_selwidth.origin();
      result.calculator_version = BEreq::cb_sd_selwidth.version();
      result.width_in_GeV = BEreq::cb_sd_selwidth->selrtot2;
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sel2body->brselrneute(1) : 0.0), 0.0, "~chi0_1", "e-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sel2body->brselrneute(2) : 0.0), 0.0, "~chi0_2", "e-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sel2body->brselrneute(3) : 0.0), 0.0, "~chi0_3", "e-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sel2body->brselrneute(4) : 0.0), 0.0, "~chi0_4", "e-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sel2body->brselrcharnue(1) : 0.0), 0.0, "~chi-_1", "nu_e");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sel2body->brselrcharnue(2) : 0.0), 0.0, "~chi-_2", "nu_e");
      check_width(LOCAL_INFO, result.width_in_GeV, runOptions->getValueOrDef<bool>(false, "invalid_point_for_negative_width"));
    }

    /// SUSY-HIT MSSM decays: smuon_l
    void smuon_l_decays (DecayTable::Entry& result)
    {
      using namespace Pipes::smuon_l_decays;
      result.calculator = BEreq::cb_sd_selwidth.origin();
      result.calculator_version = BEreq::cb_sd_selwidth.version();
      result.width_in_GeV = BEreq::cb_sd_selwidth->selltot2;
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sel2body->brsellneute(1) : 0.0), 0.0, "~chi0_1", "mu-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sel2body->brsellneute(2) : 0.0), 0.0, "~chi0_2", "mu-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sel2body->brsellneute(3) : 0.0), 0.0, "~chi0_3", "mu-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sel2body->brsellneute(4) : 0.0), 0.0, "~chi0_4", "mu-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sel2body->brsellcharnue(1) : 0.0), 0.0, "~chi-_1", "nu_mu");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sel2body->brsellcharnue(2) : 0.0), 0.0, "~chi-_2", "nu_mu");
      check_width(LOCAL_INFO, result.width_in_GeV, runOptions->getValueOrDef<bool>(false, "invalid_point_for_negative_width"));
    }

    /// SUSY-HIT MSSM decays: smuon_r
    void smuon_r_decays (DecayTable::Entry& result)
    {
      using namespace Pipes::smuon_r_decays;
      result.calculator = BEreq::cb_sd_selwidth.origin();
      result.calculator_version = BEreq::cb_sd_selwidth.version();
      result.width_in_GeV = BEreq::cb_sd_selwidth->selrtot2;
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sel2body->brselrneute(1) : 0.0), 0.0, "~chi0_1", "mu-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sel2body->brselrneute(2) : 0.0), 0.0, "~chi0_2", "mu-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sel2body->brselrneute(3) : 0.0), 0.0, "~chi0_3", "mu-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sel2body->brselrneute(4) : 0.0), 0.0, "~chi0_4", "mu-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sel2body->brselrcharnue(1) : 0.0), 0.0, "~chi-_1", "nu_mu");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sel2body->brselrcharnue(2) : 0.0), 0.0, "~chi-_2", "nu_mu");
      check_width(LOCAL_INFO, result.width_in_GeV, runOptions->getValueOrDef<bool>(false, "invalid_point_for_negative_width"));
    }

    /// MSSM decays: stau_1 (Uses SUSY-HIT results or dedicated DecayBit calculation for small mass splittings)
    void stau_1_decays (DecayTable::Entry& result)
    {
      using namespace Pipes::stau_1_decays;

      // Collect results from the decay calculation for small stau--neutralino mass splitting.
      // If this result is non-empty it should be used.
      DecayTable::Entry smallsplit_decays = *Dep::stau_1_decay_rates_smallsplit;
      if (smallsplit_decays.channels.size() > 0)
        result = smallsplit_decays;
      // Else, use the SUSY-HIT results
      else
        result = *Dep::stau_1_decay_rates_SH;

      check_width(LOCAL_INFO, result.width_in_GeV, runOptions->getValueOrDef<bool>(false, "invalid_point_for_negative_width"));
    }

    /// SUSY-HIT MSSM decays: stau_1
    void stau_1_decays_SH (DecayTable::Entry& result)
    {
      using namespace Pipes::stau_1_decays_SH;
      mass_es_pseudonyms psn = *(Dep::SLHA_pseudonyms);

      result.calculator = BEreq::cb_sd_stauwidth.origin();
      result.calculator_version = BEreq::cb_sd_stauwidth.version();

      result.width_in_GeV = BEreq::cb_sd_stauwidth->stau1tot2;
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stau2body->brstau1neut(1) : 0.0), 0.0, "~chi0_1", "tau-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stau2body->brstau1neut(2) : 0.0), 0.0, "~chi0_2", "tau-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stau2body->brstau1neut(3) : 0.0), 0.0, "~chi0_3", "tau-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stau2body->brstau1neut(4) : 0.0), 0.0, "~chi0_4", "tau-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stau2body->brstau1char(1) : 0.0), 0.0, "~chi-_1", "nu_tau");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stau2body->brstau1char(2) : 0.0), 0.0, "~chi-_2", "nu_tau");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stau2body->brstau1hcsn(1) : 0.0), 0.0, psn.isntaul, "H-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stau2body->brstau1wsn(1) : 0.0), 0.0, psn.isntaul, "W-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stau2bodygrav->brstautaugrav : 0.0), 0.0, "~G", "tau-");

      check_width(LOCAL_INFO, result.width_in_GeV, runOptions->getValueOrDef<bool>(false, "invalid_point_for_negative_width"));
    }

    /// SUSY-HIT MSSM decays: stau_2
    void stau_2_decays (DecayTable::Entry& result)
    {
      using namespace Pipes::stau_2_decays;
      mass_es_pseudonyms psn = *(Dep::SLHA_pseudonyms);

      result.calculator = BEreq::cb_sd_stauwidth.origin();
      result.calculator_version = BEreq::cb_sd_stauwidth.version();

      result.width_in_GeV = BEreq::cb_sd_stauwidth->stau2tot2;
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stau2body->brstau2neut(1) : 0.0), 0.0, "~chi0_1", "tau-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stau2body->brstau2neut(2) : 0.0), 0.0, "~chi0_2", "tau-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stau2body->brstau2neut(3) : 0.0), 0.0, "~chi0_3", "tau-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stau2body->brstau2neut(4) : 0.0), 0.0, "~chi0_4", "tau-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stau2body->brstau2char(1) : 0.0), 0.0, "~chi-_1", "nu_tau");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stau2body->brstau2char(2) : 0.0), 0.0, "~chi-_2", "nu_tau");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stau2body->brstau2hcsn(1) : 0.0), 0.0, psn.isntaul, "H-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stau2body->brstau2wsn(1) : 0.0), 0.0, psn.isntaul, "W-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stau2body->brstau2hl : 0.0), 0.0, psn.istau1, "h0_1");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stau2body->brstau2hh : 0.0), 0.0, psn.istau1, "h0_2");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stau2body->brstau2ha : 0.0), 0.0, psn.istau1, "A0");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_stau2body->brstau2ztau : 0.0), 0.0, psn.istau1, "Z0");

      check_width(LOCAL_INFO, result.width_in_GeV, runOptions->getValueOrDef<bool>(false, "invalid_point_for_negative_width"));

    }

    /// SUSY-HIT MSSM decays: snu_electronl
    void snu_electronl_decays (DecayTable::Entry& result)
    {
      using namespace Pipes::snu_electronl_decays;
      result.calculator = BEreq::cb_sd_snelwidth.origin();
      result.calculator_version = BEreq::cb_sd_snelwidth.version();
      result.width_in_GeV = BEreq::cb_sd_snelwidth->sneltot2;
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_snel2body->brsnellneut(1) : 0.0), 0.0, "~chi0_1", "nu_e");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_snel2body->brsnellneut(2) : 0.0), 0.0, "~chi0_2", "nu_e");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_snel2body->brsnellneut(3) : 0.0), 0.0, "~chi0_3", "nu_e");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_snel2body->brsnellneut(4) : 0.0), 0.0, "~chi0_4", "nu_e");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_snel2body->brsnellchar(1) : 0.0), 0.0, "~chi+_1", "e-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_snel2body->brsnellchar(2) : 0.0), 0.0, "~chi+_2", "e-");
      check_width(LOCAL_INFO, result.width_in_GeV, runOptions->getValueOrDef<bool>(false, "invalid_point_for_negative_width"));
    }

    /// SUSY-HIT MSSM decays: snu_muonl
    void snu_muonl_decays (DecayTable::Entry& result)
    {
      using namespace Pipes::snu_muonl_decays;
      result.calculator = BEreq::cb_sd_snelwidth.origin();
      result.calculator_version = BEreq::cb_sd_snelwidth.version();
      result.width_in_GeV = BEreq::cb_sd_snelwidth->sneltot2;
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_snel2body->brsnellneut(1) : 0.0), 0.0, "~chi0_1", "nu_mu");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_snel2body->brsnellneut(2) : 0.0), 0.0, "~chi0_2", "nu_mu");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_snel2body->brsnellneut(3) : 0.0), 0.0, "~chi0_3", "nu_mu");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_snel2body->brsnellneut(4) : 0.0), 0.0, "~chi0_4", "nu_mu");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_snel2body->brsnellchar(1) : 0.0), 0.0, "~chi+_1", "mu-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_snel2body->brsnellchar(2) : 0.0), 0.0, "~chi+_2", "mu-");
      check_width(LOCAL_INFO, result.width_in_GeV, runOptions->getValueOrDef<bool>(false, "invalid_point_for_negative_width"));
    }

    /// SUSY-HIT MSSM decays: snu_taul
    /// Note that SUSY-HIT calls ~nu_tau_L "snutau1" even though it has no RH (~)nus.
    void snu_taul_decays (DecayTable::Entry& result)
    {
      using namespace Pipes::snu_taul_decays;
      mass_es_pseudonyms psn = *(Dep::SLHA_pseudonyms);

      result.calculator = BEreq::cb_sd_sntauwidth.origin();
      result.calculator_version = BEreq::cb_sd_sntauwidth.version();

      result.width_in_GeV = BEreq::cb_sd_sntauwidth->sntautot2;
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sntau2body->brsntauneut(1) : 0.0), 0.0, "~chi0_1", "nu_tau");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sntau2body->brsntauneut(2) : 0.0), 0.0, "~chi0_2", "nu_tau");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sntau2body->brsntauneut(3) : 0.0), 0.0, "~chi0_3", "nu_tau");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sntau2body->brsntauneut(4) : 0.0), 0.0, "~chi0_4", "nu_tau");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sntau2body->brsntauchar(1) : 0.0), 0.0, "~chi+_1", "tau-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sntau2body->brsntauchar(2) : 0.0), 0.0, "~chi+_2", "tau-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sntau2body->brsntau1hcstau(1) : 0.0), 0.0, psn.istau1bar, "H-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sntau2body->brsntau1hcstau(2) : 0.0), 0.0, psn.istau2bar, "H-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sntau2body->brsntau1wstau(1) : 0.0), 0.0, psn.istau1bar, "W-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_sntau2body->brsntau1wstau(2) : 0.0), 0.0, psn.istau2bar, "W-");

      check_width(LOCAL_INFO, result.width_in_GeV, runOptions->getValueOrDef<bool>(false, "invalid_point_for_negative_width"));
    }

    /// MSSM decays: chargino_plus_1 (Uses SUSY-HIT results or dedicated DecayBit calculation for small mass splittings)
    void chargino_plus_1_decays (DecayTable::Entry& result)
    {
      using namespace Pipes::chargino_plus_1_decays;

      // Collect results from the decay calculation for small chargino--neutralino mass splitting.
      // If this result is non-empty it should be used.
      DecayTable::Entry smallsplit_decays = *Dep::chargino_plus_1_decay_rates_smallsplit;
      if (smallsplit_decays.channels.size() > 0)
        result = smallsplit_decays;
      // Else, use the SUSY-HIT results
      else
        result = *Dep::chargino_plus_1_decay_rates_SH;

      check_width(LOCAL_INFO, result.width_in_GeV, runOptions->getValueOrDef<bool>(false, "invalid_point_for_negative_width"));
    }

    /// SUSY-HIT MSSM decays: chargino_plus_1
    void chargino_plus_1_decays_SH (DecayTable::Entry& result)
    {
      using namespace Pipes::chargino_plus_1_decays_SH;
      mass_es_pseudonyms psn = *(Dep::SLHA_pseudonyms);

      result.calculator = BEreq::cb_sd_charwidth.origin();
      result.calculator_version = BEreq::cb_sd_charwidth.version();

      result.width_in_GeV = BEreq::cb_sd_charwidth->chartot(1);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharsupl(1) : 0.0), 0.0, psn.isul, "dbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharsupr(1) : 0.0), 0.0, psn.isur, "dbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharsdownl(1) : 0.0), 0.0, psn.isdlbar, "u");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharsdownr(1) : 0.0), 0.0, psn.isdrbar, "u");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharsupl(1) : 0.0), 0.0, psn.iscl, "sbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharsupr(1) : 0.0), 0.0, psn.iscr, "sbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharsdownl(1) : 0.0), 0.0, psn.isslbar, "c");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharsdownr(1) : 0.0), 0.0, psn.issrbar, "c");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharst1(1) : 0.0), 0.0, psn.ist1, "bbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharst2(1) : 0.0), 0.0, psn.ist2, "bbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharsb1(1) : 0.0), 0.0, psn.isb1bar, "t");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharsb2(1) : 0.0), 0.0, psn.isb2bar, "t");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharsnel(1) : 0.0), 0.0, psn.isnel, "e+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharsnel(1) : 0.0), 0.0, psn.isnmul, "mu+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharsn1(1) : 0.0), 0.0, psn.isntaul, "tau+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharsell(1) : 0.0), 0.0, psn.isellbar, "nu_e");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharselr(1) : 0.0), 0.0, psn.iselrbar, "nu_e");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharsell(1) : 0.0), 0.0, psn.ismulbar, "nu_mu");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharselr(1) : 0.0), 0.0, psn.ismurbar, "nu_mu");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharstau1(1) : 0.0), 0.0, psn.istau1bar, "nu_tau");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharstau2(1) : 0.0), 0.0, psn.istau2bar, "nu_tau");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharwneut(1,1) : 0.0), 0.0, "~chi0_1", "W+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharwneut(1,2) : 0.0), 0.0, "~chi0_2", "W+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharwneut(1,3) : 0.0), 0.0, "~chi0_3", "W+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharwneut(1,4) : 0.0), 0.0, "~chi0_4", "W+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharhcneut(1,1) : 0.0), 0.0, "~chi0_1", "H+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharhcneut(1,2) : 0.0), 0.0, "~chi0_2", "H+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharhcneut(1,3) : 0.0), 0.0, "~chi0_3", "H+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharhcneut(1,4) : 0.0), 0.0, "~chi0_4", "H+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2bodygrav->brcharwgravitino(1) : 0.0), 0.0, "~G", "W+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2bodygrav->brcharhcgravitino(1) : 0.0), 0.0, "~G", "H+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2bodygrav->brcharwgravitino(1) : 0.0), 0.0, "~G", "W+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2bodygrav->brcharhcgravitino(1) : 0.0), 0.0, "~G", "H+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brnupdb(1,1) : 0.0), 0.0, "~chi0_1", "u", "dbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brnupdb(1,2) : 0.0), 0.0, "~chi0_2", "u", "dbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brnupdb(1,3) : 0.0), 0.0, "~chi0_3", "u", "dbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brnupdb(1,4) : 0.0), 0.0, "~chi0_4", "u", "dbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brnupdb(1,1) : 0.0), 0.0, "~chi0_1", "c", "sbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brnupdb(1,2) : 0.0), 0.0, "~chi0_2", "c", "sbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brnupdb(1,3) : 0.0), 0.0, "~chi0_3", "c", "sbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brnupdb(1,4) : 0.0), 0.0, "~chi0_4", "c", "sbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brntopbb(1,1) : 0.0), 0.0, "~chi0_1", "t", "bbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brntopbb(1,2) : 0.0), 0.0, "~chi0_2", "t", "bbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brntopbb(1,3) : 0.0), 0.0, "~chi0_3", "t", "bbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brntopbb(1,4) : 0.0), 0.0, "~chi0_4", "t", "bbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brnelnue(1,1) : 0.0), 0.0, "~chi0_1", "e+", "nu_e");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brnelnue(1,2) : 0.0), 0.0, "~chi0_2", "e+", "nu_e");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brnelnue(1,3) : 0.0), 0.0, "~chi0_3", "e+", "nu_e");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brnelnue(1,4) : 0.0), 0.0, "~chi0_4", "e+", "nu_e");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brnmunumu(1,1) : 0.0), 0.0, "~chi0_1", "mu+", "nu_mu");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brnmunumu(1,2) : 0.0), 0.0, "~chi0_2", "mu+", "nu_mu");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brnmunumu(1,3) : 0.0), 0.0, "~chi0_3", "mu+", "nu_mu");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brnmunumu(1,4) : 0.0), 0.0, "~chi0_4", "mu+", "nu_mu");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brntaunut(1,1) : 0.0), 0.0, "~chi0_1", "tau+", "nu_tau");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brntaunut(1,2) : 0.0), 0.0, "~chi0_2", "tau+", "nu_tau");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brntaunut(1,3) : 0.0), 0.0, "~chi0_3", "tau+", "nu_tau");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brntaunut(1,4) : 0.0), 0.0, "~chi0_4", "tau+", "nu_tau");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brglupdb(1) : 0.0), 0.0, "~g", "u", "dbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brglchsb(1) : 0.0), 0.0, "~g", "c", "sbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brgltopbb(1) : 0.0), 0.0, "~g", "t", "bbar");

      check_width(LOCAL_INFO, result.width_in_GeV, runOptions->getValueOrDef<bool>(false, "invalid_point_for_negative_width"));
    }

    /// SUSY-HIT MSSM decays: chargino_plus_2
    void chargino_plus_2_decays (DecayTable::Entry& result)
    {
      using namespace Pipes::chargino_plus_2_decays;
      mass_es_pseudonyms psn = *(Dep::SLHA_pseudonyms);

      result.calculator = BEreq::cb_sd_charwidth.origin();
      result.calculator_version = BEreq::cb_sd_charwidth.version();

      result.width_in_GeV = BEreq::cb_sd_charwidth->chartot(2);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharsupl(2) : 0.0), 0.0, psn.isul, "dbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharsupr(2) : 0.0), 0.0, psn.isur, "dbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharsdownl(2) : 0.0), 0.0, psn.isdlbar, "u");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharsdownr(2) : 0.0), 0.0, psn.isdrbar, "u");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharsupl(2) : 0.0), 0.0, psn.iscl, "sbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharsupr(2) : 0.0), 0.0, psn.iscr, "sbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharsdownl(2) : 0.0), 0.0, psn.isslbar, "c");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharsdownr(2) : 0.0), 0.0, psn.issrbar, "c");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharst1(2) : 0.0), 0.0, psn.ist1, "bbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharst2(2) : 0.0), 0.0, psn.ist2, "bbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharsb1(2) : 0.0), 0.0, psn.isb1bar, "t");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharsb2(2) : 0.0), 0.0, psn.isb2bar, "t");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharsnel(2) : 0.0), 0.0, psn.isnel, "e+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharsnel(2) : 0.0), 0.0, psn.isnmul, "mu+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharsn1(2) : 0.0), 0.0, psn.isntaul, "tau+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharsell(2) : 0.0), 0.0, psn.isellbar, "nu_e");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharselr(2) : 0.0), 0.0, psn.iselrbar, "nu_e");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharsell(2) : 0.0), 0.0, psn.ismulbar, "nu_mu");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharselr(2) : 0.0), 0.0, psn.ismurbar, "nu_mu");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharstau1(2) : 0.0), 0.0, psn.istau1bar, "nu_tau");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharstau2(2) : 0.0), 0.0, psn.istau2bar, "nu_tau");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharzchic : 0.0), 0.0, "~chi+_1", "Z0");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharwneut(2,1) : 0.0), 0.0, "~chi0_1", "W+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharwneut(2,2) : 0.0), 0.0, "~chi0_2", "W+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharwneut(2,3) : 0.0), 0.0, "~chi0_3", "W+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharwneut(2,4) : 0.0), 0.0, "~chi0_4", "W+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharhlchic : 0.0), 0.0, "~chi+_1", "h0_1");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharhhchic : 0.0), 0.0, "~chi+_1", "h0_2");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharhachic : 0.0), 0.0, "~chi+_1", "A0");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharhcneut(2,1) : 0.0), 0.0, "~chi0_1", "H+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharhcneut(2,2) : 0.0), 0.0, "~chi0_2", "H+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharhcneut(2,3) : 0.0), 0.0, "~chi0_3", "H+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2body->brcharhcneut(2,4) : 0.0), 0.0, "~chi0_4", "H+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2bodygrav->brcharwgravitino(2) : 0.0), 0.0, "~G", "W+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2bodygrav->brcharhcgravitino(2) : 0.0), 0.0, "~G", "H+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2bodygrav->brcharwgravitino(2) : 0.0), 0.0, "~G", "W+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char2bodygrav->brcharhcgravitino(2) : 0.0), 0.0, "~G", "H+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brnupdb(2,1) : 0.0), 0.0, "~chi0_1", "u", "dbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brnupdb(2,2) : 0.0), 0.0, "~chi0_2", "u", "dbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brnupdb(2,3) : 0.0), 0.0, "~chi0_3", "u", "dbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brnupdb(2,4) : 0.0), 0.0, "~chi0_4", "u", "dbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brnupdb(2,1) : 0.0), 0.0, "~chi0_1", "c", "sbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brnupdb(2,2) : 0.0), 0.0, "~chi0_2", "c", "sbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brnupdb(2,3) : 0.0), 0.0, "~chi0_3", "c", "sbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brnupdb(2,4) : 0.0), 0.0, "~chi0_4", "c", "sbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brntopbb(2,1) : 0.0), 0.0, "~chi0_1", "t", "bbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brntopbb(2,2) : 0.0), 0.0, "~chi0_2", "t", "bbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brntopbb(2,3) : 0.0), 0.0, "~chi0_3", "t", "bbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brntopbb(2,4) : 0.0), 0.0, "~chi0_4", "t", "bbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brnelnue(2,1) : 0.0), 0.0, "~chi0_1", "e+", "nu_e");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brnelnue(2,2) : 0.0), 0.0, "~chi0_2", "e+", "nu_e");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brnelnue(2,3) : 0.0), 0.0, "~chi0_3", "e+", "nu_e");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brnelnue(2,4) : 0.0), 0.0, "~chi0_4", "e+", "nu_e");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brnmunumu(2,1) : 0.0), 0.0, "~chi0_1", "mu+", "nu_mu");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brnmunumu(2,2) : 0.0), 0.0, "~chi0_2", "mu+", "nu_mu");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brnmunumu(2,3) : 0.0), 0.0, "~chi0_3", "mu+", "nu_mu");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brnmunumu(2,4) : 0.0), 0.0, "~chi0_4", "mu+", "nu_mu");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brntaunut(2,1) : 0.0), 0.0, "~chi0_1", "tau+", "nu_tau");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brntaunut(2,2) : 0.0), 0.0, "~chi0_2", "tau+", "nu_tau");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brntaunut(2,3) : 0.0), 0.0, "~chi0_3", "tau+", "nu_tau");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brntaunut(2,4) : 0.0), 0.0, "~chi0_4", "tau+", "nu_tau");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brchupup : 0.0), 0.0, "~chi+_1", "u", "ubar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brchdodo : 0.0), 0.0, "~chi+_1", "d", "dbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brchchch : 0.0), 0.0, "~chi+_1", "c", "cbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brchstst : 0.0), 0.0, "~chi+_1", "s", "sbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brchtoptop : 0.0), 0.0, "~chi+_1", "t", "tbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brchbotbot : 0.0), 0.0, "~chi+_1", "b", "bbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brchee : 0.0), 0.0, "~chi+_1", "e+", "e-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brchmumu : 0.0), 0.0, "~chi+_1", "mu+", "mu-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brchtautau : 0.0), 0.0, "~chi+_1", "tau+", "tau-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brchnene : 0.0), 0.0, "~chi+_1", "nu_e", "nubar_e");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brchnmunmu : 0.0), 0.0, "~chi+_1", "nu_mu", "nubar_mu");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brchntauntau : 0.0), 0.0, "~chi+_1", "nu_tau", "nubar_tau");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brglupdb(2) : 0.0), 0.0, "~g", "u", "dbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brglchsb(2) : 0.0), 0.0, "~g", "c", "sbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_char3body->brgltopbb(2) : 0.0), 0.0, "~g", "t", "bbar");

      check_width(LOCAL_INFO, result.width_in_GeV, runOptions->getValueOrDef<bool>(false, "invalid_point_for_negative_width"));
    }

    /// SUSY-HIT MSSM decays: neutralino_1
    void neutralino_1_decays (DecayTable::Entry& result)
    {
      using namespace Pipes::neutralino_1_decays;
      mass_es_pseudonyms psn = *(Dep::SLHA_pseudonyms);

      result.calculator = BEreq::cb_sd_neutwidth.origin();
      result.calculator_version = BEreq::cb_sd_neutwidth.version();

      result.width_in_GeV = BEreq::cb_sd_neutwidth->neuttot(1);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutwchar(1,1) : 0.0), 0.0, "~chi+_1", "W-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutwchar(1,1) : 0.0), 0.0, "~chi-_1", "W+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutwchar(1,2) : 0.0), 0.0, "~chi+_2", "W-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutwchar(1,2) : 0.0), 0.0, "~chi-_2", "W+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneuthcchar(1,1) : 0.0), 0.0, "~chi+_1", "H-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneuthcchar(1,1) : 0.0), 0.0, "~chi-_1", "H+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneuthcchar(1,2) : 0.0), 0.0, "~chi+_2", "H-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneuthcchar(1,2) : 0.0), 0.0, "~chi-_2", "H+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsupl(1) : 0.0), 0.0, psn.isul, "ubar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsupl(1) : 0.0), 0.0, psn.isulbar, "u");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsupr(1) : 0.0), 0.0, psn.isur, "ubar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsupr(1) : 0.0), 0.0, psn.isurbar, "u");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsdownl(1) : 0.0), 0.0, psn.isdl, "dbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsdownl(1) : 0.0), 0.0, psn.isdlbar, "d");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsdownr(1) : 0.0), 0.0, psn.isdr, "dbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsdownr(1) : 0.0), 0.0, psn.isdrbar, "d");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsupl(1) : 0.0), 0.0, psn.iscl, "cbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsupl(1) : 0.0), 0.0, psn.isclbar, "c");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsupr(1) : 0.0), 0.0, psn.iscr, "cbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsupr(1) : 0.0), 0.0, psn.iscrbar, "c");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsdownl(1) : 0.0), 0.0, psn.issl, "sbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsdownl(1) : 0.0), 0.0, psn.isslbar, "s");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsdownr(1) : 0.0), 0.0, psn.issr, "sbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsdownr(1) : 0.0), 0.0, psn.issrbar, "s");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutst1(1) : 0.0), 0.0, psn.ist1, "tbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutst1(1) : 0.0), 0.0, psn.ist1bar, "t");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutst2(1) : 0.0), 0.0, psn.ist2, "tbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutst2(1) : 0.0), 0.0, psn.ist2bar, "t");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsb1(1) : 0.0), 0.0, psn.isb1, "bbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsb1(1) : 0.0), 0.0, psn.isb1bar, "b");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsb2(1) : 0.0), 0.0, psn.isb2, "bbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsb2(1) : 0.0), 0.0, psn.isb2bar, "b");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsell(1) : 0.0), 0.0, psn.isell, "e+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsell(1) : 0.0), 0.0, psn.isellbar, "e-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutselr(1) : 0.0), 0.0, psn.iselr, "e+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutselr(1) : 0.0), 0.0, psn.iselrbar, "e-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsell(1) : 0.0), 0.0, psn.ismul, "mu+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsell(1) : 0.0), 0.0, psn.ismulbar, "mu-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutselr(1) : 0.0), 0.0, psn.ismur, "mu+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutselr(1) : 0.0), 0.0, psn.ismurbar, "mu-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutstau1(1) : 0.0), 0.0, psn.istau1, "tau+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutstau1(1) : 0.0), 0.0, psn.istau1bar, "tau-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutstau2(1) : 0.0), 0.0, psn.istau2, "tau+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutstau2(1) : 0.0), 0.0, psn.istau2bar, "tau-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsnel(1) : 0.0), 0.0, psn.isnel, "nubar_e");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsnel(1) : 0.0), 0.0, psn.isnelbar, "nu_e");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsnel(1) : 0.0), 0.0, psn.isnmul, "nubar_mu");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsnel(1) : 0.0), 0.0, psn.isnmulbar, "nu_mu");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsn1(1) : 0.0), 0.0, psn.isntaul, "nubar_tau");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsn1(1) : 0.0), 0.0, psn.isntaulbar, "nu_tau");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2bodygrav->brneutgamgrav(1) : 0.0), 0.0, "~G", "gamma");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2bodygrav->brneutzgrav(1) : 0.0), 0.0, "~G", "Z0");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2bodygrav->brneuthlgrav(1) : 0.0), 0.0, "~G", "h0_1");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2bodygrav->brneuthhgrav(1) : 0.0), 0.0, "~G", "h0_2");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2bodygrav->brneuthagrav(1) : 0.0), 0.0, "~G", "A0");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2bodygrav->brneutgamgrav(1) : 0.0), 0.0, "~G", "gamma");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2bodygrav->brneutzgrav(1) : 0.0), 0.0, "~G", "Z0");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2bodygrav->brneuthlgrav(1) : 0.0), 0.0, "~G", "h0_1");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2bodygrav->brneuthhgrav(1) : 0.0), 0.0, "~G", "h0_2");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2bodygrav->brneuthagrav(1) : 0.0), 0.0, "~G", "A0");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchubd(1,1) : 0.0), 0.0, "~chi+_1", "ubar", "d");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchubd(1,1) : 0.0), 0.0, "~chi-_1", "dbar", "u");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchubd(1,2) : 0.0), 0.0, "~chi+_2", "ubar", "d");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchubd(1,2) : 0.0), 0.0, "~chi-_2", "dbar", "u");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchcbs(1,1) : 0.0), 0.0, "~chi+_1", "cbar", "s");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchcbs(1,1) : 0.0), 0.0, "~chi-_1", "sbar", "c");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchcbs(1,2) : 0.0), 0.0, "~chi+_2", "cbar", "s");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchcbs(1,2) : 0.0), 0.0, "~chi-_2", "sbar", "c");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchtbb(1,1) : 0.0), 0.0, "~chi+_1", "tbar", "b");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchtbb(1,1) : 0.0), 0.0, "~chi-_1", "bbar", "t");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchtbb(1,2) : 0.0), 0.0, "~chi+_2", "tbar", "b");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchtbb(1,2) : 0.0), 0.0, "~chi-_2", "bbar", "t");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchelne(1,1) : 0.0), 0.0, "~chi+_1", "nubar_e", "e-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchelne(1,1) : 0.0), 0.0, "~chi-_1", "nu_e", "e+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchelne(1,2) : 0.0), 0.0, "~chi+_2", "nubar_e", "e-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchelne(1,2) : 0.0), 0.0, "~chi-_2", "nu_e", "e+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchmunmu(1,1) : 0.0), 0.0, "~chi+_1", "nubar_mu", "mu-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchmunmu(1,1) : 0.0), 0.0, "~chi-_1", "nu_mu", "mu+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchmunmu(1,2) : 0.0), 0.0, "~chi+_2", "nubar_mu", "mu-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchmunmu(1,2) : 0.0), 0.0, "~chi-_2", "nu_mu", "mu+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchtauntau(1,1) : 0.0), 0.0, "~chi+_1", "nubar_tau", "tau-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchtauntau(1,1) : 0.0), 0.0, "~chi-_1", "nu_tau", "tau+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchtauntau(1,2) : 0.0), 0.0, "~chi+_2", "nubar_tau", "tau-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchtauntau(1,2) : 0.0), 0.0, "~chi-_2", "nu_tau", "tau+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brglup(1) : 0.0), 0.0, "~g", "ubar", "u");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brgldo(1) : 0.0), 0.0, "~g", "dbar", "d");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brglch(1) : 0.0), 0.0, "~g", "cbar", "c");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brglst(1) : 0.0), 0.0, "~g", "sbar", "s");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brgltop(1) : 0.0), 0.0, "~g", "tbar", "t");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brglbot(1) : 0.0), 0.0, "~g", "bbar", "b");

      check_width(LOCAL_INFO, result.width_in_GeV, runOptions->getValueOrDef<bool>(false, "invalid_point_for_negative_width"));
    }

    /// SUSY-HIT MSSM decays: neutralino_2
    void neutralino_2_decays (DecayTable::Entry& result)
    {
      using namespace Pipes::neutralino_2_decays;
      mass_es_pseudonyms psn = *(Dep::SLHA_pseudonyms);

      result.calculator = BEreq::cb_sd_neutwidth.origin();
      result.calculator_version = BEreq::cb_sd_neutwidth.version();

      result.width_in_GeV = BEreq::cb_sd_neutwidth->neuttot(2);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutzneut(2,1) : 0.0), 0.0, "~chi0_1", "Z0");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutwchar(2,1) : 0.0), 0.0, "~chi+_1", "W-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutwchar(2,1) : 0.0), 0.0, "~chi-_1", "W+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutwchar(2,2) : 0.0), 0.0, "~chi+_2", "W-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutwchar(2,2) : 0.0), 0.0, "~chi-_2", "W+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneuthlneut(2,1) : 0.0), 0.0, "~chi0_1", "h0_1");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneuthhneut(2,1) : 0.0), 0.0, "~chi0_1", "h0_2");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneuthaneut(2,1) : 0.0), 0.0, "~chi0_1", "A0");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneuthcchar(2,1) : 0.0), 0.0, "~chi+_1", "H-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneuthcchar(2,1) : 0.0), 0.0, "~chi-_1", "H+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneuthcchar(2,2) : 0.0), 0.0, "~chi+_2", "H-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneuthcchar(2,2) : 0.0), 0.0, "~chi-_2", "H+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsupl(2) : 0.0), 0.0, psn.isul, "ubar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsupl(2) : 0.0), 0.0, psn.isulbar, "u");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsupr(2) : 0.0), 0.0, psn.isur, "ubar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsupr(2) : 0.0), 0.0, psn.isurbar, "u");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsdownl(2) : 0.0), 0.0, psn.isdl, "dbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsdownl(2) : 0.0), 0.0, psn.isdlbar, "d");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsdownr(2) : 0.0), 0.0, psn.isdr, "dbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsdownr(2) : 0.0), 0.0, psn.isdrbar, "d");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsupl(2) : 0.0), 0.0, psn.iscl, "cbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsupl(2) : 0.0), 0.0, psn.isclbar, "c");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsupr(2) : 0.0), 0.0, psn.iscr, "cbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsupr(2) : 0.0), 0.0, psn.iscrbar, "c");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsdownl(2) : 0.0), 0.0, psn.issl, "sbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsdownl(2) : 0.0), 0.0, psn.isslbar, "s");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsdownr(2) : 0.0), 0.0, psn.issr, "sbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsdownr(2) : 0.0), 0.0, psn.issrbar, "s");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutst1(2) : 0.0), 0.0, psn.ist1, "tbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutst1(2) : 0.0), 0.0, psn.ist1bar, "t");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutst2(2) : 0.0), 0.0, psn.ist2, "tbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutst2(2) : 0.0), 0.0, psn.ist2bar, "t");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsb1(2) : 0.0), 0.0, psn.isb1, "bbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsb1(2) : 0.0), 0.0, psn.isb1bar, "b");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsb2(2) : 0.0), 0.0, psn.isb2, "bbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsb2(2) : 0.0), 0.0, psn.isb2bar, "b");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsell(2) : 0.0), 0.0, psn.isell, "e+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsell(2) : 0.0), 0.0, psn.isellbar, "e-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutselr(2) : 0.0), 0.0, psn.iselr, "e+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutselr(2) : 0.0), 0.0, psn.iselrbar, "e-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsell(2) : 0.0), 0.0, psn.ismul, "mu+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsell(2) : 0.0), 0.0, psn.ismulbar, "mu-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutselr(2) : 0.0), 0.0, psn.ismur, "mu+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutselr(2) : 0.0), 0.0, psn.ismurbar, "mu-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutstau1(2) : 0.0), 0.0, psn.istau1, "tau+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutstau1(2) : 0.0), 0.0, psn.istau1bar, "tau-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutstau2(2) : 0.0), 0.0, psn.istau2, "tau+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutstau2(2) : 0.0), 0.0, psn.istau2bar, "tau-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsnel(2) : 0.0), 0.0, psn.isnel, "nubar_e");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsnel(2) : 0.0), 0.0, psn.isnelbar, "nu_e");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsnel(2) : 0.0), 0.0, psn.isnmul, "nubar_mu");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsnel(2) : 0.0), 0.0, psn.isnmulbar, "nu_mu");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsn1(2) : 0.0), 0.0, psn.isntaul, "nubar_tau");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsn1(2) : 0.0), 0.0, psn.isntaulbar, "nu_tau");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2bodygrav->brneutgamgrav(2) : 0.0), 0.0, "~G", "gamma");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2bodygrav->brneutzgrav(2) : 0.0), 0.0, "~G", "Z0");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2bodygrav->brneuthlgrav(2) : 0.0), 0.0, "~G", "h0_1");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2bodygrav->brneuthhgrav(2) : 0.0), 0.0, "~G", "h0_2");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2bodygrav->brneuthagrav(2) : 0.0), 0.0, "~G", "A0");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neutloop->brnraddec(2,1) : 0.0), 0.0, "~chi0_1", "gamma");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2bodygrav->brneutgamgrav(2) : 0.0), 0.0, "~G", "gamma");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2bodygrav->brneutzgrav(2) : 0.0), 0.0, "~G", "Z0");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2bodygrav->brneuthlgrav(2) : 0.0), 0.0, "~G", "h0_1");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2bodygrav->brneuthhgrav(2) : 0.0), 0.0, "~G", "h0_2");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2bodygrav->brneuthagrav(2) : 0.0), 0.0, "~G", "A0");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutup(2,1) : 0.0), 0.0, "~chi0_1", "ubar", "u");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutdow(2,1) : 0.0), 0.0, "~chi0_1", "dbar", "d");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutch(2,1) : 0.0), 0.0, "~chi0_1", "cbar", "c");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutst(2,1) : 0.0), 0.0, "~chi0_1", "sbar", "s");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneuttop(2,1) : 0.0), 0.0, "~chi0_1", "tbar", "t");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutbot(2,1) : 0.0), 0.0, "~chi0_1", "bbar", "b");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutel(2,1) : 0.0), 0.0, "~chi0_1", "e+", "e-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutmu(2,1) : 0.0), 0.0, "~chi0_1", "mu+", "mu-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneuttau(2,1) : 0.0), 0.0, "~chi0_1", "tau+", "tau-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutnue(2,1) : 0.0), 0.0, "~chi0_1", "nubar_e", "nu_e");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutnumu(2,1) : 0.0), 0.0, "~chi0_1", "nubar_mu", "nu_mu");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutnutau(2,1) : 0.0), 0.0, "~chi0_1", "nubar_tau", "nu_tau");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchubd(2,1) : 0.0), 0.0, "~chi+_1", "ubar", "d");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchubd(2,1) : 0.0), 0.0, "~chi-_1", "dbar", "u");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchubd(2,2) : 0.0), 0.0, "~chi+_2", "ubar", "d");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchubd(2,2) : 0.0), 0.0, "~chi-_2", "dbar", "u");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchcbs(2,1) : 0.0), 0.0, "~chi+_1", "cbar", "s");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchcbs(2,1) : 0.0), 0.0, "~chi-_1", "sbar", "c");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchcbs(2,2) : 0.0), 0.0, "~chi+_2", "cbar", "s");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchcbs(2,2) : 0.0), 0.0, "~chi-_2", "sbar", "c");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchtbb(2,1) : 0.0), 0.0, "~chi+_1", "tbar", "b");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchtbb(2,1) : 0.0), 0.0, "~chi-_1", "bbar", "t");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchtbb(2,2) : 0.0), 0.0, "~chi+_2", "tbar", "b");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchtbb(2,2) : 0.0), 0.0, "~chi-_2", "bbar", "t");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchelne(2,1) : 0.0), 0.0, "~chi+_1", "nubar_e", "e-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchelne(2,1) : 0.0), 0.0, "~chi-_1", "nu_e", "e+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchelne(2,2) : 0.0), 0.0, "~chi+_2", "nubar_e", "e-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchelne(2,2) : 0.0), 0.0, "~chi-_2", "nu_e", "e+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchmunmu(2,1) : 0.0), 0.0, "~chi+_1", "nubar_mu", "mu-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchmunmu(2,1) : 0.0), 0.0, "~chi-_1", "nu_mu", "mu+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchmunmu(2,2) : 0.0), 0.0, "~chi+_2", "nubar_mu", "mu-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchmunmu(2,2) : 0.0), 0.0, "~chi-_2", "nu_mu", "mu+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchtauntau(2,1) : 0.0), 0.0, "~chi+_1", "nubar_tau", "tau-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchtauntau(2,1) : 0.0), 0.0, "~chi-_1", "nu_tau", "tau+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchtauntau(2,2) : 0.0), 0.0, "~chi+_2", "nubar_tau", "tau-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchtauntau(2,2) : 0.0), 0.0, "~chi-_2", "nu_tau", "tau+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brglup(2) : 0.0), 0.0, "~g", "ubar", "u");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brgldo(2) : 0.0), 0.0, "~g", "dbar", "d");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brglch(2) : 0.0), 0.0, "~g", "cbar", "c");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brglst(2) : 0.0), 0.0, "~g", "sbar", "s");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brgltop(2) : 0.0), 0.0, "~g", "tbar", "t");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brglbot(2) : 0.0), 0.0, "~g", "bbar", "b");

      check_width(LOCAL_INFO, result.width_in_GeV, runOptions->getValueOrDef<bool>(false, "invalid_point_for_negative_width"));
    }

    /// SUSY-HIT MSSM decays: neutralino_3
    void neutralino_3_decays (DecayTable::Entry& result)
    {
      using namespace Pipes::neutralino_3_decays;
      mass_es_pseudonyms psn = *(Dep::SLHA_pseudonyms);

      result.calculator = BEreq::cb_sd_neutwidth.origin();
      result.calculator_version = BEreq::cb_sd_neutwidth.version();

      result.width_in_GeV = BEreq::cb_sd_neutwidth->neuttot(3);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutzneut(3,1) : 0.0), 0.0, "~chi0_1", "Z0");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutzneut(3,2) : 0.0), 0.0, "~chi0_2", "Z0");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutwchar(3,1) : 0.0), 0.0, "~chi+_1", "W-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutwchar(3,1) : 0.0), 0.0, "~chi-_1", "W+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutwchar(3,2) : 0.0), 0.0, "~chi+_2", "W-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutwchar(3,2) : 0.0), 0.0, "~chi-_2", "W+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneuthlneut(3,1) : 0.0), 0.0, "~chi0_1", "h0_1");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneuthhneut(3,1) : 0.0), 0.0, "~chi0_1", "h0_2");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneuthaneut(3,1) : 0.0), 0.0, "~chi0_1", "A0");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneuthlneut(3,2) : 0.0), 0.0, "~chi0_2", "h0_1");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneuthhneut(3,2) : 0.0), 0.0, "~chi0_2", "h0_2");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneuthaneut(3,2) : 0.0), 0.0, "~chi0_2", "A0");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneuthcchar(3,1) : 0.0), 0.0, "~chi+_1", "H-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneuthcchar(3,1) : 0.0), 0.0, "~chi-_1", "H+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneuthcchar(3,2) : 0.0), 0.0, "~chi+_2", "H-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneuthcchar(3,2) : 0.0), 0.0, "~chi-_2", "H+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsupl(3) : 0.0), 0.0, psn.isul, "ubar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsupl(3) : 0.0), 0.0, psn.isulbar, "u");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsupr(3) : 0.0), 0.0, psn.isur, "ubar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsupr(3) : 0.0), 0.0, psn.isurbar, "u");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsdownl(3) : 0.0), 0.0, psn.isdl, "dbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsdownl(3) : 0.0), 0.0, psn.isdlbar, "d");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsdownr(3) : 0.0), 0.0, psn.isdr, "dbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsdownr(3) : 0.0), 0.0, psn.isdrbar, "d");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsupl(3) : 0.0), 0.0, psn.iscl, "cbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsupl(3) : 0.0), 0.0, psn.isclbar, "c");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsupr(3) : 0.0), 0.0, psn.iscr, "cbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsupr(3) : 0.0), 0.0, psn.iscrbar, "c");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsdownl(3) : 0.0), 0.0, psn.issl, "sbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsdownl(3) : 0.0), 0.0, psn.isslbar, "s");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsdownr(3) : 0.0), 0.0, psn.issr, "sbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsdownr(3) : 0.0), 0.0, psn.issrbar, "s");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutst1(3) : 0.0), 0.0, psn.ist1, "tbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutst1(3) : 0.0), 0.0, psn.ist1bar, "t");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutst2(3) : 0.0), 0.0, psn.ist2, "tbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutst2(3) : 0.0), 0.0, psn.ist2bar, "t");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsb1(3) : 0.0), 0.0, psn.isb1, "bbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsb1(3) : 0.0), 0.0, psn.isb1bar, "b");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsb2(3) : 0.0), 0.0, psn.isb2, "bbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsb2(3) : 0.0), 0.0, psn.isb2bar, "b");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsell(3) : 0.0), 0.0, psn.isell, "e+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsell(3) : 0.0), 0.0, psn.isellbar, "e-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutselr(3) : 0.0), 0.0, psn.iselr, "e+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutselr(3) : 0.0), 0.0, psn.iselrbar, "e-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsell(3) : 0.0), 0.0, psn.ismul, "mu+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsell(3) : 0.0), 0.0, psn.ismulbar, "mu-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutselr(3) : 0.0), 0.0, psn.ismur, "mu+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutselr(3) : 0.0), 0.0, psn.ismurbar, "mu-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutstau1(3) : 0.0), 0.0, psn.istau1, "tau+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutstau1(3) : 0.0), 0.0, psn.istau1bar, "tau-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutstau2(3) : 0.0), 0.0, psn.istau2, "tau+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutstau2(3) : 0.0), 0.0, psn.istau2bar, "tau-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsnel(3) : 0.0), 0.0, psn.isnel, "nubar_e");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsnel(3) : 0.0), 0.0, psn.isnelbar, "nu_e");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsnel(3) : 0.0), 0.0, psn.isnmul, "nubar_mu");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsnel(3) : 0.0), 0.0, psn.isnmulbar, "nu_mu");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsn1(3) : 0.0), 0.0, psn.isntaul, "nubar_tau");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsn1(3) : 0.0), 0.0, psn.isntaulbar, "nu_tau");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2bodygrav->brneutgamgrav(3) : 0.0), 0.0, "~G", "gamma");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2bodygrav->brneutzgrav(3) : 0.0), 0.0, "~G", "Z0");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2bodygrav->brneuthlgrav(3) : 0.0), 0.0, "~G", "h0_1");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2bodygrav->brneuthhgrav(3) : 0.0), 0.0, "~G", "h0_2");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2bodygrav->brneuthagrav(3) : 0.0), 0.0, "~G", "A0");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neutloop->brnraddec(3,1) : 0.0), 0.0, "~chi0_1", "gamma");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neutloop->brnraddec(3,2) : 0.0), 0.0, "~chi0_2", "gamma");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2bodygrav->brneutgamgrav(3) : 0.0), 0.0, "~G", "gamma");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2bodygrav->brneutzgrav(3) : 0.0), 0.0, "~G", "Z0");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2bodygrav->brneuthlgrav(3) : 0.0), 0.0, "~G", "h0_1");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2bodygrav->brneuthhgrav(3) : 0.0), 0.0, "~G", "h0_2");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2bodygrav->brneuthagrav(3) : 0.0), 0.0, "~G", "A0");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutup(3,1) : 0.0), 0.0, "~chi0_1", "ubar", "u");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutdow(3,1) : 0.0), 0.0, "~chi0_1", "dbar", "d");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutch(3,1) : 0.0), 0.0, "~chi0_1", "cbar", "c");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutst(3,1) : 0.0), 0.0, "~chi0_1", "sbar", "s");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneuttop(3,1) : 0.0), 0.0, "~chi0_1", "tbar", "t");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutbot(3,1) : 0.0), 0.0, "~chi0_1", "bbar", "b");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutel(3,1) : 0.0), 0.0, "~chi0_1", "e+", "e-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutmu(3,1) : 0.0), 0.0, "~chi0_1", "mu+", "mu-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneuttau(3,1) : 0.0), 0.0, "~chi0_1", "tau+", "tau-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutnue(3,1) : 0.0), 0.0, "~chi0_1", "nubar_e", "nu_e");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutnumu(3,1) : 0.0), 0.0, "~chi0_1", "nubar_mu", "nu_mu");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutnutau(3,1) : 0.0), 0.0, "~chi0_1", "nubar_tau", "nu_tau");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutup(3,2) : 0.0), 0.0, "~chi0_2", "ubar", "u");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutdow(3,2) : 0.0), 0.0, "~chi0_2", "dbar", "d");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutch(3,2) : 0.0), 0.0, "~chi0_2", "cbar", "c");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutst(3,2) : 0.0), 0.0, "~chi0_2", "sbar", "s");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneuttop(3,2) : 0.0), 0.0, "~chi0_2", "tbar", "t");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutbot(3,2) : 0.0), 0.0, "~chi0_2", "bbar", "b");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutel(3,2) : 0.0), 0.0, "~chi0_2", "e+", "e-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutmu(3,2) : 0.0), 0.0, "~chi0_2", "mu+", "mu-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneuttau(3,2) : 0.0), 0.0, "~chi0_2", "tau+", "tau-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutnue(3,2) : 0.0), 0.0, "~chi0_2", "nubar_e", "nu_e");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutnumu(3,2) : 0.0), 0.0, "~chi0_2", "nubar_mu", "nu_mu");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutnutau(3,2) : 0.0), 0.0, "~chi0_2", "nubar_tau", "nu_tau");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchubd(3,1) : 0.0), 0.0, "~chi+_1", "ubar", "d");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchubd(3,1) : 0.0), 0.0, "~chi-_1", "dbar", "u");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchubd(3,2) : 0.0), 0.0, "~chi+_2", "ubar", "d");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchubd(3,2) : 0.0), 0.0, "~chi-_2", "dbar", "u");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchcbs(3,1) : 0.0), 0.0, "~chi+_1", "cbar", "s");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchcbs(3,1) : 0.0), 0.0, "~chi-_1", "sbar", "c");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchcbs(3,2) : 0.0), 0.0, "~chi+_2", "cbar", "s");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchcbs(3,2) : 0.0), 0.0, "~chi-_2", "sbar", "c");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchtbb(3,1) : 0.0), 0.0, "~chi+_1", "tbar", "b");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchtbb(3,1) : 0.0), 0.0, "~chi-_1", "bbar", "t");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchtbb(3,2) : 0.0), 0.0, "~chi+_2", "tbar", "b");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchtbb(3,2) : 0.0), 0.0, "~chi-_2", "bbar", "t");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchelne(3,1) : 0.0), 0.0, "~chi+_1", "nubar_e", "e-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchelne(3,1) : 0.0), 0.0, "~chi-_1", "nu_e", "e+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchelne(3,2) : 0.0), 0.0, "~chi+_2", "nubar_e", "e-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchelne(3,2) : 0.0), 0.0, "~chi-_2", "nu_e", "e+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchmunmu(3,1) : 0.0), 0.0, "~chi+_1", "nubar_mu", "mu-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchmunmu(3,1) : 0.0), 0.0, "~chi-_1", "nu_mu", "mu+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchmunmu(3,2) : 0.0), 0.0, "~chi+_2", "nubar_mu", "mu-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchmunmu(3,2) : 0.0), 0.0, "~chi-_2", "nu_mu", "mu+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchtauntau(3,1) : 0.0), 0.0, "~chi+_1", "nubar_tau", "tau-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchtauntau(3,1) : 0.0), 0.0, "~chi-_1", "nu_tau", "tau+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchtauntau(3,2) : 0.0), 0.0, "~chi+_2", "nubar_tau", "tau-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchtauntau(3,2) : 0.0), 0.0, "~chi-_2", "nu_tau", "tau+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brglup(3) : 0.0), 0.0, "~g", "ubar", "u");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brgldo(3) : 0.0), 0.0, "~g", "dbar", "d");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brglch(3) : 0.0), 0.0, "~g", "cbar", "c");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brglst(3) : 0.0), 0.0, "~g", "sbar", "s");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brgltop(3) : 0.0), 0.0, "~g", "tbar", "t");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brglbot(3) : 0.0), 0.0, "~g", "bbar", "b");

      check_width(LOCAL_INFO, result.width_in_GeV, runOptions->getValueOrDef<bool>(false, "invalid_point_for_negative_width"));
    }

    /// SUSY-HIT MSSM decays: neutralino_4
    void neutralino_4_decays (DecayTable::Entry& result)
    {
      using namespace Pipes::neutralino_4_decays;
      mass_es_pseudonyms psn = *(Dep::SLHA_pseudonyms);

      result.calculator = BEreq::cb_sd_neutwidth.origin();
      result.calculator_version = BEreq::cb_sd_neutwidth.version();

      result.width_in_GeV = BEreq::cb_sd_neutwidth->neuttot(4);
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutzneut(4,1) : 0.0), 0.0, "~chi0_1", "Z0");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutzneut(4,2) : 0.0), 0.0, "~chi0_2", "Z0");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutzneut(4,3) : 0.0), 0.0, "~chi0_3", "Z0");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutwchar(4,1) : 0.0), 0.0, "~chi+_1", "W-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutwchar(4,1) : 0.0), 0.0, "~chi-_1", "W+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutwchar(4,2) : 0.0), 0.0, "~chi+_2", "W-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutwchar(4,2) : 0.0), 0.0, "~chi-_2", "W+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneuthlneut(4,1) : 0.0), 0.0, "~chi0_1", "h0_1");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneuthhneut(4,1) : 0.0), 0.0, "~chi0_1", "h0_2");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneuthaneut(4,1) : 0.0), 0.0, "~chi0_1", "A0");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneuthlneut(4,2) : 0.0), 0.0, "~chi0_2", "h0_1");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneuthhneut(4,2) : 0.0), 0.0, "~chi0_2", "h0_2");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneuthaneut(4,2) : 0.0), 0.0, "~chi0_2", "A0");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneuthlneut(4,3) : 0.0), 0.0, "~chi0_3", "h0_1");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneuthhneut(4,3) : 0.0), 0.0, "~chi0_3", "h0_2");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneuthaneut(4,3) : 0.0), 0.0, "~chi0_3", "A0");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneuthcchar(4,1) : 0.0), 0.0, "~chi+_1", "H-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneuthcchar(4,1) : 0.0), 0.0, "~chi-_1", "H+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneuthcchar(4,2) : 0.0), 0.0, "~chi+_2", "H-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneuthcchar(4,2) : 0.0), 0.0, "~chi-_2", "H+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsupl(4) : 0.0), 0.0, psn.isul, "ubar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsupl(4) : 0.0), 0.0, psn.isulbar, "u");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsupr(4) : 0.0), 0.0, psn.isur, "ubar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsupr(4) : 0.0), 0.0, psn.isurbar, "u");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsdownl(4) : 0.0), 0.0, psn.isdl, "dbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsdownl(4) : 0.0), 0.0, psn.isdlbar, "d");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsdownr(4) : 0.0), 0.0, psn.isdr, "dbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsdownr(4) : 0.0), 0.0, psn.isdrbar, "d");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsupl(4) : 0.0), 0.0, psn.iscl, "cbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsupl(4) : 0.0), 0.0, psn.isclbar, "c");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsupr(4) : 0.0), 0.0, psn.iscr, "cbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsupr(4) : 0.0), 0.0, psn.iscrbar, "c");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsdownl(4) : 0.0), 0.0, psn.issl, "sbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsdownl(4) : 0.0), 0.0, psn.isslbar, "s");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsdownr(4) : 0.0), 0.0, psn.issr, "sbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsdownr(4) : 0.0), 0.0, psn.issrbar, "s");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutst1(4) : 0.0), 0.0, psn.ist1, "tbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutst1(4) : 0.0), 0.0, psn.ist1bar, "t");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutst2(4) : 0.0), 0.0, psn.ist2, "tbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutst2(4) : 0.0), 0.0, psn.ist2bar, "t");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsb1(4) : 0.0), 0.0, psn.isb1, "bbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsb1(4) : 0.0), 0.0, psn.isb1bar, "b");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsb2(4) : 0.0), 0.0, psn.isb2, "bbar");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsb2(4) : 0.0), 0.0, psn.isb2bar, "b");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsell(4) : 0.0), 0.0, psn.isell, "e+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsell(4) : 0.0), 0.0, psn.isellbar, "e-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutselr(4) : 0.0), 0.0, psn.iselr, "e+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutselr(4) : 0.0), 0.0, psn.iselrbar, "e-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsell(4) : 0.0), 0.0, psn.ismul, "mu+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsell(4) : 0.0), 0.0, psn.ismulbar, "mu-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutselr(4) : 0.0), 0.0, psn.ismur, "mu+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutselr(4) : 0.0), 0.0, psn.ismurbar, "mu-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutstau1(4) : 0.0), 0.0, psn.istau1, "tau+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutstau1(4) : 0.0), 0.0, psn.istau1bar, "tau-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutstau2(4) : 0.0), 0.0, psn.istau2, "tau+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutstau2(4) : 0.0), 0.0, psn.istau2bar, "tau-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsnel(4) : 0.0), 0.0, psn.isnel, "nubar_e");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsnel(4) : 0.0), 0.0, psn.isnelbar, "nu_e");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsnel(4) : 0.0), 0.0, psn.isnmul, "nubar_mu");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsnel(4) : 0.0), 0.0, psn.isnmulbar, "nu_mu");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsn1(4) : 0.0), 0.0, psn.isntaul, "nubar_tau");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2body->brneutsn1(4) : 0.0), 0.0, psn.isntaulbar, "nu_tau");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2bodygrav->brneutgamgrav(4) : 0.0), 0.0, "~G", "gamma");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2bodygrav->brneutzgrav(4) : 0.0), 0.0, "~G", "Z0");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2bodygrav->brneuthlgrav(4) : 0.0), 0.0, "~G", "h0_1");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2bodygrav->brneuthhgrav(4) : 0.0), 0.0, "~G", "h0_2");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2bodygrav->brneuthagrav(4) : 0.0), 0.0, "~G", "A0");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neutloop->brnraddec(4,1) : 0.0), 0.0, "~chi0_1", "gamma");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neutloop->brnraddec(4,2) : 0.0), 0.0, "~chi0_2", "gamma");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neutloop->brnraddec(4,3) : 0.0), 0.0, "~chi0_3", "gamma");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2bodygrav->brneutgamgrav(4) : 0.0), 0.0, "~G", "gamma");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2bodygrav->brneutzgrav(4) : 0.0), 0.0, "~G", "Z0");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2bodygrav->brneuthlgrav(4) : 0.0), 0.0, "~G", "h0_1");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2bodygrav->brneuthhgrav(4) : 0.0), 0.0, "~G", "h0_2");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut2bodygrav->brneuthagrav(4) : 0.0), 0.0, "~G", "A0");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutup(4,1) : 0.0), 0.0, "~chi0_1", "ubar", "u");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutdow(4,1) : 0.0), 0.0, "~chi0_1", "dbar", "d");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutch(4,1) : 0.0), 0.0, "~chi0_1", "cbar", "c");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutst(4,1) : 0.0), 0.0, "~chi0_1", "sbar", "s");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneuttop(4,1) : 0.0), 0.0, "~chi0_1", "tbar", "t");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutbot(4,1) : 0.0), 0.0, "~chi0_1", "bbar", "b");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutel(4,1) : 0.0), 0.0, "~chi0_1", "e+", "e-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutmu(4,1) : 0.0), 0.0, "~chi0_1", "mu+", "mu-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneuttau(4,1) : 0.0), 0.0, "~chi0_1", "tau+", "tau-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutnue(4,1) : 0.0), 0.0, "~chi0_1", "nubar_e", "nu_e");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutnumu(4,1) : 0.0), 0.0, "~chi0_1", "nubar_mu", "nu_mu");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutnutau(4,1) : 0.0), 0.0, "~chi0_1", "nubar_tau", "nu_tau");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutup(4,2) : 0.0), 0.0, "~chi0_2", "ubar", "u");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutdow(4,2) : 0.0), 0.0, "~chi0_2", "dbar", "d");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutch(4,2) : 0.0), 0.0, "~chi0_2", "cbar", "c");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutst(4,2) : 0.0), 0.0, "~chi0_2", "sbar", "s");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneuttop(4,2) : 0.0), 0.0, "~chi0_2", "tbar", "t");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutbot(4,2) : 0.0), 0.0, "~chi0_2", "bbar", "b");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutel(4,2) : 0.0), 0.0, "~chi0_2", "e+", "e-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutmu(4,2) : 0.0), 0.0, "~chi0_2", "mu+", "mu-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneuttau(4,2) : 0.0), 0.0, "~chi0_2", "tau+", "tau-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutnue(4,2) : 0.0), 0.0, "~chi0_2", "nubar_e", "nu_e");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutnumu(4,2) : 0.0), 0.0, "~chi0_2", "nubar_mu", "nu_mu");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutnutau(4,2) : 0.0), 0.0, "~chi0_2", "nubar_tau", "nu_tau");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutup(4,3) : 0.0), 0.0, "~chi0_3", "ubar", "u");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutdow(4,3) : 0.0), 0.0, "~chi0_3", "dbar", "d");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutch(4,3) : 0.0), 0.0, "~chi0_3", "cbar", "c");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutst(4,3) : 0.0), 0.0, "~chi0_3", "sbar", "s");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneuttop(4,3) : 0.0), 0.0, "~chi0_3", "tbar", "t");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutbot(4,3) : 0.0), 0.0, "~chi0_3", "bbar", "b");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutel(4,3) : 0.0), 0.0, "~chi0_3", "e+", "e-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutmu(4,3) : 0.0), 0.0, "~chi0_3", "mu+", "mu-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneuttau(4,3) : 0.0), 0.0, "~chi0_3", "tau+", "tau-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutnue(4,3) : 0.0), 0.0, "~chi0_3", "nubar_e", "nu_e");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutnumu(4,3) : 0.0), 0.0, "~chi0_3", "nubar_mu", "nu_mu");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brneutnutau(4,3) : 0.0), 0.0, "~chi0_3", "nubar_tau", "nu_tau");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchubd(4,1) : 0.0), 0.0, "~chi+_1", "ubar", "d");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchubd(4,1) : 0.0), 0.0, "~chi-_1", "dbar", "u");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchubd(4,2) : 0.0), 0.0, "~chi+_2", "ubar", "d");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchubd(4,2) : 0.0), 0.0, "~chi-_2", "dbar", "u");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchcbs(4,1) : 0.0), 0.0, "~chi+_1", "cbar", "s");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchcbs(4,1) : 0.0), 0.0, "~chi-_1", "sbar", "c");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchcbs(4,2) : 0.0), 0.0, "~chi+_2", "cbar", "s");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchcbs(4,2) : 0.0), 0.0, "~chi-_2", "sbar", "c");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchtbb(4,1) : 0.0), 0.0, "~chi+_1", "tbar", "b");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchtbb(4,1) : 0.0), 0.0, "~chi-_1", "bbar", "t");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchtbb(4,2) : 0.0), 0.0, "~chi+_2", "tbar", "b");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchtbb(4,2) : 0.0), 0.0, "~chi-_2", "bbar", "t");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchelne(4,1) : 0.0), 0.0, "~chi+_1", "nubar_e", "e-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchelne(4,1) : 0.0), 0.0, "~chi-_1", "nu_e", "e+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchelne(4,2) : 0.0), 0.0, "~chi+_2", "nubar_e", "e-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchelne(4,2) : 0.0), 0.0, "~chi-_2", "nu_e", "e+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchmunmu(4,1) : 0.0), 0.0, "~chi+_1", "nubar_mu", "mu-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchmunmu(4,1) : 0.0), 0.0, "~chi-_1", "nu_mu", "mu+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchmunmu(4,2) : 0.0), 0.0, "~chi+_2", "nubar_mu", "mu-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchmunmu(4,2) : 0.0), 0.0, "~chi-_2", "nu_mu", "mu+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchtauntau(4,1) : 0.0), 0.0, "~chi+_1", "nubar_tau", "tau-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchtauntau(4,1) : 0.0), 0.0, "~chi-_1", "nu_tau", "tau+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchtauntau(4,2) : 0.0), 0.0, "~chi+_2", "nubar_tau", "tau-");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brchtauntau(4,2) : 0.0), 0.0, "~chi-_2", "nu_tau", "tau+");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brglup(4) : 0.0), 0.0, "~g", "ubar", "u");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brgldo(4) : 0.0), 0.0, "~g", "dbar", "d");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brglch(4) : 0.0), 0.0, "~g", "cbar", "c");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brglst(4) : 0.0), 0.0, "~g", "sbar", "s");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brgltop(4) : 0.0), 0.0, "~g", "tbar", "t");
      result.set_BF((result.width_in_GeV > 0 ? BEreq::cb_sd_neut3body->brglbot(4) : 0.0), 0.0, "~g", "bbar", "b");

      check_width(LOCAL_INFO, result.width_in_GeV, runOptions->getValueOrDef<bool>(false, "invalid_point_for_negative_width"));
    }


    /// MSSM decays: chargino decays for small chargino--neutralino mass splitting.
    /// Using results from hep-ph/9607421.
    void chargino_plus_1_decays_smallsplit(DecayTable::Entry& result)
    {
      using namespace Pipes::chargino_plus_1_decays_smallsplit;
      mass_es_pseudonyms psn = *(Dep::SLHA_pseudonyms);

      // Option for requiring a bit more mass difference before switching on a decay channel.
      // Can help avoid problems with chargino decays in Pythia (due to Pythia's MSAFETY checks).
      static const double m_safety = runOptions->getValueOrDef<double>(0.0, "m_safety");

      // Get spectrum objects
      const Spectrum& spec = *Dep::MSSM_spectrum;
      const SubSpectrum& mssm = spec.get_HE();

      // Get SUSY masses
      const double m_N_signed = spec.get(Par::Pole_Mass,"~chi0_1");
      const double m_C_signed = spec.get(Par::Pole_Mass,"~chi+_1");
      const double m_N = abs(m_N_signed);
      const double m_C = abs(m_C_signed);

      const double delta_m = m_C - m_N;
      const double delta_m_safety = m_C - (m_N + m_safety);

      // If the chargino--neutralino mass difference is large,
      // the calculations in this module function should not be used.
      // Return empty result.
      if (delta_m > 1.5)
      {
        result = DecayTable::Entry();
        return;
      }

      // Get wino/higgsino mixing for the lightest neutralino and chargino.
      // From Eqs. (A.23) -- (A.25) in 1705.07936 (SpecBit/DecayBit/PrecisionBit paper).
      const double N12 = mssm.get(Par::Pole_Mixing,"~chi0",1,2);  // ~W3 component
      const double N13 = mssm.get(Par::Pole_Mixing,"~chi0",1,3);  // ~Hd component
      const double N14 = mssm.get(Par::Pole_Mixing,"~chi0",1,4);  // ~Hu component

      const double Up11 = mssm.get(Par::Pole_Mixing,"~chi+",1,1); // (~W1 - i*~W2) component
      const double Up12 = mssm.get(Par::Pole_Mixing,"~chi+",1,2); // ~Hu+ component
      const double Um11 = mssm.get(Par::Pole_Mixing,"~chi-",1,1); // (~W1 + i*~W2) component
      const double Um12 = mssm.get(Par::Pole_Mixing,"~chi-",1,2); // ~Hu- component

      // Connection to chargino matrix notation in S. Martin's "A SUSY Primer":
      // Our 'Up' matrix corresponds to his 'V' matrix, and
      // our 'Um' matrix corresponds to his 'U' matrix.

      // We use the convention that keeps the mixing matrices real.
      // This means that the neutralino mass can be negative.
      // In that case, we have to deal with relative phase factors
      // when implementing the calculations from hep-ph/9607421.
      // @todo Double check these conventions.
      double O11L  = -1./root2*N14*Up12 + N12*Up11;
      double O11R  =  1./root2*N13*Um12 + N12*Um11;
      if (m_C_signed < 0.)
        O11L = -O11L;
      if (m_N_signed < 0.)
        O11R = -O11R;


      // Get SM parameters and other physical constants
      const double G_F = *Param["GF"];     // [GeV^-2]
      const double m_el = *Param["mE"];    // [GeV]
      const double m_mu = *Param["mMu"];   // [GeV]

      const double m_pi = meson_masses.pi_plus;  // hep-ph/9607421 uses one common pion mass for pi+/- and pi0. We choose the pi+ mass.
      const double m_rho_0 = meson_masses.rho0;
      const double m_rho_prime = meson_masses.rho1450;

      const double f_pi = meson_decay_constants.pi_plus / root2;  // Using the sqrt(2) convention of hep-ph/9607421

      const double gamma_rho_0 = Dep::rho_0_decay_rates->width_in_GeV;
      const double gamma_rho_prime = Dep::rho1450_decay_rates->width_in_GeV;

      const double beta = -0.145;  // Parameter from form factor fit quoted in hep-ph/9607421, referring to https://link.springer.com/content/pdf/10.1007%2FBF01572024.pdf

      // Convenient quantities
      const double m_N2             = pow2(m_N);
      const double m_C2             = pow2(m_C);
      const double m_el2            = pow2(m_el);
      const double m_mu2            = pow2(m_mu);
      const double m_pi2            = pow2(m_pi);
      const double m_rho_02         = pow2(m_rho_0);
      const double m_rho_prime2     = pow2(m_rho_prime);

      const double f_pi2            = pow2(f_pi);

      const double G_F2             = pow2(G_F);
      const double O11L2            = pow2(O11L);
      const double O11R2            = pow2(O11R);

      // Map to store partial width results
      std::map<str,double> partial_widths;

      //
      // Channel: ~chi+_1 --> ~chi0_1 e+ nu_e
      //
      partial_widths["N_el+_nu"] = 0.0;
      if (delta_m > m_el)
      {
        // Integrand 1
        std::function<double(double)> N_el_nu_integrand_1 = [&m_N2,&m_C2,&m_el2](double q2)
        {
          return (1. - (m_N2+m_el2)/q2) * pow2(1. - q2/m_C2) * sqrt_lambda(q2,m_N2,m_el2);
        };

        // Integrand 2
        std::function<double(double)> N_el_nu_integrand_2 = [&m_N2,&m_C2,&m_el2](double q2)
        {
          return (q2/m_C2) * pow2(1. - m_el2/q2) * sqrt_lambda(m_C2,m_N2,q2);
        };

        // Perform integrations
        double N_el_nu_I1 = Utils::integrate_cquad(N_el_nu_integrand_1, pow2(m_N+m_el), m_C2, 0, 1e-2);
        double N_el_nu_I2 = Utils::integrate_cquad(N_el_nu_integrand_2, m_el2, pow2(m_C-m_N), 0, 1e-2);

        // Put everything together
        partial_widths["N_el+_nu"] = (1.*G_F2/pow3(2*pi)) * ( m_C*(O11L2 + O11R2)*N_el_nu_I1 - 2.*m_N*O11L*O11R*N_el_nu_I2 );
      }

      //
      // Channel: ~chi+_1 --> ~chi0_1 mu+ nu_mu
      //
      partial_widths["N_mu+_nu"] = 0.0;
      if (delta_m > m_mu)
      {
        // Integrand 1
        std::function<double(double)> N_mu_nu_integrand_1 = [&m_N2,&m_C2,&m_mu2](double q2)
        {
          return (1. - (m_N2+m_mu2)/q2) * pow2(1. - q2/m_C2) * sqrt_lambda(q2,m_N2,m_mu2);
        };

        // Integrand 2
        std::function<double(double)> N_mu_nu_integrand_2 = [&m_N2,&m_C2,&m_mu2](double q2)
        {
          return (q2/m_C2) * pow2(1. - m_mu2/q2) * sqrt_lambda(m_C2,m_N2,q2);
        };

        // Perform integrations
        double N_mu_nu_I1 = Utils::integrate_cquad(N_mu_nu_integrand_1, pow2(m_N+m_mu), m_C2, 0, 1e-2);
        double N_mu_nu_I2 = Utils::integrate_cquad(N_mu_nu_integrand_2, m_mu2, pow2(m_C-m_N), 0, 1e-2);

        // Put everything together
        partial_widths["N_mu+_nu"] = (1.*G_F2/pow3(2*pi)) * ( m_C*(O11L2 + O11R2)*N_mu_nu_I1 - 2.*m_N*O11L*O11R*N_mu_nu_I2 );
      }

      //
      // Channel: ~chi+_1 --> ~chi0_1 pi+
      //
      partial_widths["N_pi+"] = 0.0;
      if (delta_m_safety > m_pi)
      {
        double k_pi = sqrt_lambda(m_C2,m_N2,m_pi2) / (2*m_C);
        partial_widths["N_pi+"] = ( (f_pi2 * G_F2 * k_pi / (4. * pi * m_C2)) *
                          (  pow2(O11L+O11R) * ( pow2(m_C2-m_N2) - m_pi2*pow2(m_C-m_N) )
                           + pow2(O11L-O11R) * ( pow2(m_C2-m_N2) - m_pi2*pow2(m_C+m_N) ) ) );
      }

      //
      // Channel: ~chi+_1 --> ~chi0_1 pi+ pi0
      //
      partial_widths["N_pi+_pi0"] = 0.0;
      if (delta_m_safety > 2*m_pi)
      {
        // Define a helper function
        std::function<std::complex<double>(double)> F = [&beta,&m_rho_02,&gamma_rho_0,&m_rho_prime2,&gamma_rho_prime](double q2)
        {
          return (BW(q2, m_rho_02, sqrt(q2)*gamma_rho_0) + beta*BW(q2, m_rho_prime2, sqrt(q2)*gamma_rho_prime)) / (1. + beta);
        };

        // Integrand
        std::function<double(double)> N_2pi_integrand = [&F,&m_N,&m_C,&m_N2,&m_C2,&m_pi2,&O11L,&O11R,&O11L2,&O11R2](double q2)
        {
          return pow2(std::abs(F(q2))) * pow(1. - 4*m_pi2/q2,1.5) * sqrt_lambda(m_C2,m_N2,q2)
                      * ( (O11L2+O11R2)*( q2*(m_C2+m_N2-2*q2) + pow2(m_C2-m_N2) ) - (12*O11L*O11R*q2*m_C*m_N) );
        };

        // Perform integration
        double N_2pi_I = Utils::integrate_cquad(N_2pi_integrand, 4*m_pi2, pow2(delta_m), 0, 1e-2);

        // Put everything together
        partial_widths["N_pi+_pi0"] = G_F2 / (192. * pow3(pi) * pow3(m_C)) * N_2pi_I;
      }

      //
      // Channel: ~chi+_1 --> ~chi0_1 pi+ pi0 pi0
      //
      partial_widths["N_pi+_pi0_pi0"] = 0.0;
      if (delta_m_safety > 3*m_pi)
      {
        // Define a helper function
        std::function<double(double)> g = [&m_pi,&m_pi2,&m_rho_0](double q2)
        {
          double res = 0.0;
          if (q2 < pow2(m_rho_0 + m_pi))
            res = 4.1 * pow3(q2-9*m_pi2) * (1. - 3.3*(q2-9*m_pi2) + 5.8*pow2(q2-9*m_pi2));
          else
            res = q2 * (1.623 + 10.38/q2 - 9.32/pow2(q2) + 0.65/pow3(q2));
          return res;
        };

        // @todo Include this a-meson data properly into the GAMBIT data system
        double m_a = 1.246;
        double gamma_a = 0.562;

        // Integrand
        std::function<double(double)> N_3pi_integrand = [&g,&m_N,&m_C,&m_N2,&m_C2,&O11L,&O11R,&O11L2,&O11R2,&m_a,&gamma_a](double q2)
        {
          double BW_imag_term = m_a * gamma_a * g(q2)/g(pow2(m_a));

          return sqrt_lambda(m_C2,m_N2,q2) * pow2(std::abs(BW(q2,pow2(m_a),BW_imag_term))) * g(q2)
                   * ( (O11L2 + O11R2)*(m_C2 + m_N2 - 2*q2 + pow2(m_C2-m_N2)/q2 )
                       - 12*O11L*O11R*m_C*m_N );
        };

        // Perform integration
        double N_3pi_I = Utils::integrate_cquad(N_3pi_integrand, 9*m_pi2, pow2(delta_m), 0, 1e-2);

        // Put everything together
        partial_widths["N_pi+_pi0_pi0"] = G_F2 / (6912. * pow(pi,5) * pow3(m_C) * f_pi2) * N_3pi_I;
      }

      //
      // Channel: ~chi+_1 --> ~chi0_1 pi+ pi+ pi-
      //
      // When ignoring the tiny mass difference between charged and neutral pions, this
      // width is identical as the one for ~chi+_1 --> ~chi0_1 pi+ pi0 pi0
      partial_widths["N_pi+_pi+_pi-"] = partial_widths["N_pi+_pi0_pi0"];


      //
      // Store results
      //
      result.calculator = "GAMBIT::DecayBit";
      result.calculator_version = gambit_version();

      // Sum partial widths
      double total_width = 0.0;
      for (auto it = partial_widths.begin(); it != partial_widths.end(); it++)
        total_width += it->second;

      result.width_in_GeV = total_width;

      if (result.width_in_GeV > 0)
      {
        result.set_BF(partial_widths["N_el+_nu"]/result.width_in_GeV, 0.0, "~chi0_1", "e+", "nu_e");
        result.set_BF(partial_widths["N_mu+_nu"]/result.width_in_GeV, 0.0, "~chi0_1", "mu+", "nu_mu");
        result.set_BF(partial_widths["N_pi+"]/result.width_in_GeV, 0.0, "~chi0_1", "pi+");
        result.set_BF(partial_widths["N_pi+_pi0"]/result.width_in_GeV, 0.0, "~chi0_1", "pi+", "pi0");
        result.set_BF(partial_widths["N_pi+_pi0_pi0"]/result.width_in_GeV, 0.0, "~chi0_1", "pi+", "pi0", "pi0");
        result.set_BF(partial_widths["N_pi+_pi+_pi-"]/result.width_in_GeV, 0.0, "~chi0_1", "pi+", "pi+", "pi-");
      }

      // Set other branching fractions to 0.
      result.set_BF(0.0, 0.0, psn.isul, "dbar");
      result.set_BF(0.0, 0.0, psn.isur, "dbar");
      result.set_BF(0.0, 0.0, psn.isdlbar, "u");
      result.set_BF(0.0, 0.0, psn.isdrbar, "u");
      result.set_BF(0.0, 0.0, psn.iscl, "sbar");
      result.set_BF(0.0, 0.0, psn.iscr, "sbar");
      result.set_BF(0.0, 0.0, psn.isslbar, "c");
      result.set_BF(0.0, 0.0, psn.issrbar, "c");
      result.set_BF(0.0, 0.0, psn.ist1, "bbar");
      result.set_BF(0.0, 0.0, psn.ist2, "bbar");
      result.set_BF(0.0, 0.0, psn.isb1bar, "t");
      result.set_BF(0.0, 0.0, psn.isb2bar, "t");
      result.set_BF(0.0, 0.0, psn.isnel, "e+");
      result.set_BF(0.0, 0.0, psn.isnmul, "mu+");
      result.set_BF(0.0, 0.0, psn.isntaul, "tau+");
      result.set_BF(0.0, 0.0, psn.isellbar, "nu_e");
      result.set_BF(0.0, 0.0, psn.iselrbar, "nu_e");
      result.set_BF(0.0, 0.0, psn.ismulbar, "nu_mu");
      result.set_BF(0.0, 0.0, psn.ismurbar, "nu_mu");
      result.set_BF(0.0, 0.0, psn.istau1bar, "nu_tau");
      result.set_BF(0.0, 0.0, psn.istau2bar, "nu_tau");
      result.set_BF(0.0, 0.0, "~chi0_1", "W+");
      result.set_BF(0.0, 0.0, "~chi0_2", "W+");
      result.set_BF(0.0, 0.0, "~chi0_3", "W+");
      result.set_BF(0.0, 0.0, "~chi0_4", "W+");
      result.set_BF(0.0, 0.0, "~chi0_1", "H+");
      result.set_BF(0.0, 0.0, "~chi0_2", "H+");
      result.set_BF(0.0, 0.0, "~chi0_3", "H+");
      result.set_BF(0.0, 0.0, "~chi0_4", "H+");
      result.set_BF(0.0, 0.0, "~G", "W+");
      result.set_BF(0.0, 0.0, "~G", "H+");
      result.set_BF(0.0, 0.0, "~G", "W+");
      result.set_BF(0.0, 0.0, "~G", "H+");
      result.set_BF(0.0, 0.0, "~chi0_1", "u", "dbar");
      result.set_BF(0.0, 0.0, "~chi0_2", "u", "dbar");
      result.set_BF(0.0, 0.0, "~chi0_3", "u", "dbar");
      result.set_BF(0.0, 0.0, "~chi0_4", "u", "dbar");
      result.set_BF(0.0, 0.0, "~chi0_1", "c", "sbar");
      result.set_BF(0.0, 0.0, "~chi0_2", "c", "sbar");
      result.set_BF(0.0, 0.0, "~chi0_3", "c", "sbar");
      result.set_BF(0.0, 0.0, "~chi0_4", "c", "sbar");
      result.set_BF(0.0, 0.0, "~chi0_1", "t", "bbar");
      result.set_BF(0.0, 0.0, "~chi0_2", "t", "bbar");
      result.set_BF(0.0, 0.0, "~chi0_3", "t", "bbar");
      result.set_BF(0.0, 0.0, "~chi0_4", "t", "bbar");
      // (We calculate ~chi_01 e+ nu_e)
      // result.set_BF(0.0, 0.0, "~chi0_1", "e+", "nu_e");
      result.set_BF(0.0, 0.0, "~chi0_2", "e+", "nu_e");
      result.set_BF(0.0, 0.0, "~chi0_3", "e+", "nu_e");
      result.set_BF(0.0, 0.0, "~chi0_4", "e+", "nu_e");
      // (We calculate ~chi_01 mu+ nu_mu)
      // result.set_BF(0.0, 0.0, "~chi0_1", "mu+", "nu_mu");
      result.set_BF(0.0, 0.0, "~chi0_2", "mu+", "nu_mu");
      result.set_BF(0.0, 0.0, "~chi0_3", "mu+", "nu_mu");
      result.set_BF(0.0, 0.0, "~chi0_4", "mu+", "nu_mu");
      result.set_BF(0.0, 0.0, "~chi0_1", "tau+", "nu_tau");
      result.set_BF(0.0, 0.0, "~chi0_2", "tau+", "nu_tau");
      result.set_BF(0.0, 0.0, "~chi0_3", "tau+", "nu_tau");
      result.set_BF(0.0, 0.0, "~chi0_4", "tau+", "nu_tau");
      result.set_BF(0.0, 0.0, "~g", "u", "dbar");
      result.set_BF(0.0, 0.0, "~g", "c", "sbar");
      result.set_BF(0.0, 0.0, "~g", "t", "bbar");

      check_width(LOCAL_INFO, result.width_in_GeV, runOptions->getValueOrDef<bool>(false, "invalid_point_for_negative_width"));
    }


    /// MSSM decays: stau decays for small stau--neutralino mass splitting.
    /// Using results from T. Jittoh, J. Sato, T. Shimomura, M. Yamanaka, Phys. Rev. D73 (2006), hep-ph/0512197
    void stau_1_decays_smallsplit(DecayTable::Entry& result)
    {
      using namespace Pipes::stau_1_decays_smallsplit;
      mass_es_pseudonyms psn = *(Dep::SLHA_pseudonyms);

      // Get spectrum objects
      const Spectrum& spec = *Dep::MSSM_spectrum;
      const SubSpectrum& mssm = spec.get_HE();

      // Get neutralino mass and mixing
      const double m_N = abs(spec.get(Par::Pole_Mass,"~chi0_1"));

      const double N11 = mssm.get(Par::Pole_Mixing,"~chi0",1,1);  // ~B component
      const double N12 = mssm.get(Par::Pole_Mixing,"~chi0",1,2);  // ~W3 component
      const double N13 = mssm.get(Par::Pole_Mixing,"~chi0",1,3);  // ~Hd component

      // Get lightest stau mass eigenstate and mixing
      str m_light, m_heavy;
      const static double ftol = runOptions->getValueOrDef<double>(1e-2, "family_mixing_tolerance");
      const static bool fpt_error = runOptions->getValueOrDef<bool>(true, "family_mixing_tolerance_invalidates_point_only");
      // Get the stau mixing matrix ((F11,F12),(F21,F22)) as a 4-vector (F11,F12,F21,F22).
      // Also get the names ("~e-_1", "~e-_2", ..., "~e-_6") that correspond to the light and heavy stau states.
      std::vector<double> stau_mix_4vec = slhahelp::family_state_mix_matrix("~e-", 3, m_light, m_heavy, mssm, ftol, LOCAL_INFO, fpt_error);
      // Get the mass of the lightest stau state
      const double m_stau = spec.safeget(Par::Pole_Mass,m_light);
      // Get the gauge mixing
      const double F11 = stau_mix_4vec[0];
      const double F12 = stau_mix_4vec[1];

      // Stau--neutralino mass difference
      double delta_m = m_stau - m_N;

      // If the stau--neutralino mass difference is large,
      // the calculations in this module function should not be used.
      // Return empty result.
      if (delta_m > 2.5)
      {
        result = DecayTable::Entry();
        return;
      }

      //
      // Get constants and parameters
      //

      // SM parameters
      const double G_F = *Param["GF"];
      const double m_el = *Param["mE"];
      const double m_mu = *Param["mMu"];
      const double m_tau = *Param["mTau"];
      // @todo Get w_tau properly from DecayBit
      const double w_tau = Dep::tau_minus_decay_rates->width_in_GeV;
      const double m_W = spec.safeget(Par::Pole_Mass,24,0);
      const double g_2 = mssm.safeget(Par::dimensionless,"g2");
      const double sinW2 = mssm.safeget(Par::dimensionless,"sinW2");
      const double m_pi = meson_masses.pi_plus;
      const double f_pi = meson_decay_constants.pi_plus;
      const double CKM_lambda = *Param["CKM_lambda"];
      const double costc = 1. - 0.5*pow2(CKM_lambda); // cos(theta_Cabibbo)

      // MSSM parameters
      const double tanb = mssm.safeget(Par::dimensionless,"tanbeta");

      // Derived constants
      double sinW = sqrt(sinW2);
      double cosW = sqrt(1.-sinW2);
      double cosb = 1./sqrt(1.+pow2(tanb));

      // Calculate couplings
      double N11p = N11*cosW+N12*sinW;
      double N12p = -N11*sinW+N12*cosW;
      double gL = (root2*g_2*sinW*N11p + root2*g_2*N12p/cosW*(0.5-sinW2))*F11 - g_2*m_tau*N13/root2/m_W/cosb*F12;
      double gR = -g_2*m_tau*N13/root2/m_W/cosb*F11 + (-root2*g_2*sinW*N11p + root2*g_2*sinW2*N12p/cosW)*F12;


      // Map to store partial width results
      std::map<str,double> partial_widths;

      //
      // Channel: ~tau_1- --> ~chi0_1 tau-
      //
      std::function<double()> width_N_tau = [&m_stau,&m_N,&m_tau,&gL,&gR]()
      {
        double width = 0.0;
        if (m_stau > m_N + m_tau)
        {
          width = pow4(m_stau) + pow4(m_N) + pow4(m_tau);
          width = width - 2.*pow2(m_stau)*pow2(m_N) - 2.*pow2(m_stau)*pow2(m_tau) - 2.*pow2(m_N)*pow2(m_tau);
          width = sqrt(width) * ( (pow2(gL)+pow2(gR))*(pow2(m_stau)-pow2(m_N)-pow2(m_tau)) - 4.*gL*gR*m_tau*m_N );
          width = width / (16.*pi*pow3(m_stau));
        }
        return width;
      };
      partial_widths["N_tau-"] = width_N_tau();


      //
      // Channel: ~tau_1- --> ~chi0_1 pi- nutau
      //
      std::function<double()> width_N_pi_nu = [&m_stau,&m_N,&m_tau,&m_pi,&gL,&gR,&w_tau,&G_F,&f_pi,&costc]()
      {
        double width = 0.0;

        if (m_stau > m_N + m_pi)
        {
          // stau--neutralino mass difference
          double dm = m_stau - m_N;

          // Define 3-body integrand
          std::function<double(double)> integ_3b = [&dm,&m_N,&m_tau,&m_pi,&gL,&gR,&w_tau](double x)
          {
            double integ = 0.0;
            double qf2 = pow2(dm) - (pow2(dm)-pow2(m_pi))*x;
            integ = sqrt((pow2(dm)-qf2)*(pow2(dm+2.*m_N)-qf2))/(pow2(qf2-pow2(m_tau))+pow2(m_tau*w_tau));
            integ *= qf2-pow2(m_pi);
            integ *= 0.25*(pow2(gL)*qf2+pow2(gR*m_tau))*(pow2(dm)+2.*m_N*dm-qf2)-gL*gR*m_N*m_tau*qf2;
            return integ;
          };

          // Split integration by hand to avoid pole
          double I;
          if(dm < m_tau)
            I = Utils::integrate_cquad(integ_3b, 0, 1, 0, 1e-2);
          else
          {
            double pole = (pow2(dm)-pow2(m_tau))/(pow2(dm)-pow2(m_pi));
            double eps = 1E-15;
            double I1 = Utils::integrate_cquad(integ_3b, 0, pole-eps, 0, 1e-2);
            double I2 = Utils::integrate_cquad(integ_3b, pole-eps, 1, 0, 1e-2);
            I = I1 + I2;
          }

          // Put everything together
          width = pow2(G_F*f_pi*costc) * (pow2(dm)-pow2(m_pi)) / (64.*pow3(pi*m_stau)) * I;
        }
        return width;
      };
      partial_widths["N_pi-_nutau"] = width_N_pi_nu();


      //
      // Channel: ~tau_1- --> ~chi0_1 l- nubarl nutau
      //
      std::function<double(double)> width_N_l_nubar_nu = [&m_stau,&m_N,&m_tau,&gL,&gR,&w_tau,&G_F](double m_l)
      {
        double width = 0.0;

        if (m_stau > m_N + m_l)
        {
          // stau--neutralino mass difference
          double dm = m_stau - m_N;

          // Define 4-body integrand
          std::function<double(double)> integ_4b = [&dm,&m_N,&m_tau,&m_l,&gL,&gR,&w_tau](double x)
          {
            double integ = 0.0;
            double qf2 = pow2(dm) - (pow2(dm)-pow2(m_l))*x;
            integ = sqrt((pow2(dm)-qf2)*(pow2(dm+2.*m_N)-qf2))/(pow2(qf2-pow2(m_tau))+pow2(m_tau*w_tau));
            integ *= 0.25*(pow2(gL)*qf2+pow2(gR*m_tau))*(pow2(dm)+2.*m_N*dm-qf2)-gL*gR*m_N*m_tau*qf2;
            integ *= 12.*pow4(m_l)*log(qf2/pow2(m_l))+(1.-pow4(m_l)/pow2(qf2))*(pow2(qf2)-8.*pow2(m_l)*qf2+pow4(m_l));
            return integ;
          };

          // Split integration by hand to avoid pole
          double I;
          if(dm < m_tau)
            I = Utils::integrate_cquad(integ_4b, 0, 1, 0, 1e-2);
          else
          {
            double pole = (pow2(dm)-pow2(m_tau))/(pow2(dm)-pow2(m_l));
            double eps = 1E-15;
            double I1 = Utils::integrate_cquad(integ_4b, 0, pole-eps, 0, 1e-2);
            double I2 = Utils::integrate_cquad(integ_4b, pole-eps, 1, 0, 1e-2);
            I = I1 + I2;
          }

          // Put everything together
          width = pow2(G_F) * (pow2(dm)-pow2(m_l)) / (24.*pow(2.*pi,5)*pow3(m_stau)) * I;
        }
        return width;
      };
      partial_widths["N_el-_nubarel_nutau"] = width_N_l_nubar_nu(m_el);
      partial_widths["N_mu-_nubarmu_nutau"] = width_N_l_nubar_nu(m_mu);


      //
      // Store results
      //
      result.calculator = "GAMBIT::DecayBit";
      result.calculator_version = gambit_version();

      // Sum partial widths
      double total_width = 0.0;
      for (auto it = partial_widths.begin(); it != partial_widths.end(); it++)
        total_width += it->second;

      result.width_in_GeV = total_width;

      if (result.width_in_GeV > 0)
      {
        result.set_BF(partial_widths["N_tau-"]/result.width_in_GeV, 0.0, "~chi0_1", "tau-");
        result.set_BF(partial_widths["N_pi-_nutau"]/result.width_in_GeV, 0.0, "~chi0_1", "pi-", "nu_tau");
        result.set_BF(partial_widths["N_el-_nubarel_nutau"]/result.width_in_GeV, 0.0, "~chi0_1", "e-", "nubar_e", "nu_tau");
        result.set_BF(partial_widths["N_mu-_nubarmu_nutau"]/result.width_in_GeV, 0.0, "~chi0_1", "mu-", "nubar_mu", "nu_tau");
      }

      // Set other branching fractions to 0.
      result.set_BF(0.0, 0.0, "~chi0_2", "tau-");
      result.set_BF(0.0, 0.0, "~chi0_3", "tau-");
      result.set_BF(0.0, 0.0, "~chi0_4", "tau-");
      result.set_BF(0.0, 0.0, "~chi-_1", "nu_tau");
      result.set_BF(0.0, 0.0, "~chi-_2", "nu_tau");
      result.set_BF(0.0, 0.0, psn.isntaul, "H-");
      result.set_BF(0.0, 0.0, psn.isntaul, "W-");
      result.set_BF(0.0, 0.0, "~G", "tau-");

      check_width(LOCAL_INFO, result.width_in_GeV, runOptions->getValueOrDef<bool>(false, "invalid_point_for_negative_width"));
    }

    /// MSSM decays: conjugates
    /// @{
    void H_minus_decays (DecayTable::Entry& result)          { result = CP_conjugate(*Pipes::H_minus_decays::Dep::H_plus_decay_rates); }
    void stopbar_1_decays (DecayTable::Entry& result)        { result = CP_conjugate(*Pipes::stopbar_1_decays::Dep::stop_1_decay_rates); }
    void stopbar_2_decays (DecayTable::Entry& result)        { result = CP_conjugate(*Pipes::stopbar_2_decays::Dep::stop_2_decay_rates); }
    void sbottombar_1_decays (DecayTable::Entry& result)     { result = CP_conjugate(*Pipes::sbottombar_1_decays::Dep::sbottom_1_decay_rates); }
    void sbottombar_2_decays (DecayTable::Entry& result)     { result = CP_conjugate(*Pipes::sbottombar_2_decays::Dep::sbottom_2_decay_rates); }
    void supbar_l_decays (DecayTable::Entry& result)         { result = CP_conjugate(*Pipes::supbar_l_decays::Dep::sup_l_decay_rates); }
    void supbar_r_decays (DecayTable::Entry& result)         { result = CP_conjugate(*Pipes::supbar_r_decays::Dep::sup_r_decay_rates); }
    void sdownbar_l_decays (DecayTable::Entry& result)       { result = CP_conjugate(*Pipes::sdownbar_l_decays::Dep::sdown_l_decay_rates); }
    void sdownbar_r_decays (DecayTable::Entry& result)       { result = CP_conjugate(*Pipes::sdownbar_r_decays::Dep::sdown_r_decay_rates); }
    void scharmbar_l_decays (DecayTable::Entry& result)      { result = CP_conjugate(*Pipes::scharmbar_l_decays::Dep::scharm_l_decay_rates); }
    void scharmbar_r_decays (DecayTable::Entry& result)      { result = CP_conjugate(*Pipes::scharmbar_r_decays::Dep::scharm_r_decay_rates); }
    void sstrangebar_l_decays (DecayTable::Entry& result)    { result = CP_conjugate(*Pipes::sstrangebar_l_decays::Dep::sstrange_l_decay_rates); }
    void sstrangebar_r_decays (DecayTable::Entry& result)    { result = CP_conjugate(*Pipes::sstrangebar_r_decays::Dep::sstrange_r_decay_rates); }
    void selectronbar_l_decays (DecayTable::Entry& result)   { result = CP_conjugate(*Pipes::selectronbar_l_decays::Dep::selectron_l_decay_rates); }
    void selectronbar_r_decays (DecayTable::Entry& result)   { result = CP_conjugate(*Pipes::selectronbar_r_decays::Dep::selectron_r_decay_rates); }
    void smuonbar_l_decays (DecayTable::Entry& result)       { result = CP_conjugate(*Pipes::smuonbar_l_decays::Dep::smuon_l_decay_rates); }
    void smuonbar_r_decays (DecayTable::Entry& result)       { result = CP_conjugate(*Pipes::smuonbar_r_decays::Dep::smuon_r_decay_rates); }
    void staubar_1_decays (DecayTable::Entry& result)        { result = CP_conjugate(*Pipes::staubar_1_decays::Dep::stau_1_decay_rates); }
    void staubar_2_decays (DecayTable::Entry& result)        { result = CP_conjugate(*Pipes::staubar_2_decays::Dep::stau_2_decay_rates); }
    void snubar_electronl_decays (DecayTable::Entry& result) { result = CP_conjugate(*Pipes::snubar_electronl_decays::Dep::snu_electronl_decay_rates); }
    void snubar_muonl_decays (DecayTable::Entry& result)     { result = CP_conjugate(*Pipes::snubar_muonl_decays::Dep::snu_muonl_decay_rates); }
    void snubar_taul_decays (DecayTable::Entry& result)      { result = CP_conjugate(*Pipes::snubar_taul_decays::Dep::snu_taul_decay_rates); }
    void chargino_minus_1_decays (DecayTable::Entry& result) { result = CP_conjugate(*Pipes::chargino_minus_1_decays::Dep::chargino_plus_1_decay_rates); }
    void chargino_minus_2_decays (DecayTable::Entry& result) { result = CP_conjugate(*Pipes::chargino_minus_2_decays::Dep::chargino_plus_2_decay_rates); }
    /// @}


    //////////// Scalar singlet DM /////////////////////

    /// Add the decay of Higgs to singlets for the ScalarSingletDM models
    void ScalarSingletDM_Higgs_decays (DecayTable::Entry& result)
    {
      using namespace Pipes::ScalarSingletDM_Higgs_decays;

      // Get the spectrum information
      bool self_conjugate = true;
      dep_bucket<Spectrum>* spectrum_dependency = nullptr;
      if (ModelInUse("ScalarSingletDM_Z2") or ModelInUse("ScalarSingletDM_Z2_running"))
      {
        spectrum_dependency = &Dep::ScalarSingletDM_Z2_spectrum;
      }
      else if (ModelInUse("ScalarSingletDM_Z3") or ModelInUse("ScalarSingletDM_Z3_running"))
      {
        spectrum_dependency = &Dep::ScalarSingletDM_Z3_spectrum;
        self_conjugate = false;
      }
      else DecayBit_error().raise(LOCAL_INFO, "No valid model for ScalarSingletDM_Higgs_decays.");
      const SubSpectrum& he = (*spectrum_dependency)->get_HE();

      double mass = (*spectrum_dependency)->get(Par::Pole_Mass,"S");
      double lambda = he.get(Par::dimensionless,"lambda_hS");
      double v0 = he.get(Par::mass1,"vev");
      double mhpole = (*spectrum_dependency)->get(Par::Pole_Mass,"h0_1");

      // Get the reference SM Higgs decays
      result = *Dep::Reference_SM_Higgs_decay_rates;

      // Add the h->SS width to the total
      double massratio2 = pow(mass/mhpole,2);
      double gamma = (2.0*mass <= mhpole) ? pow(lambda*v0,2)/(16.0*pi*mhpole) * sqrt(1.0 - 4.0*massratio2) : 0.0;
      // Include symmetry factor of two to account for identical final state particles
      if (self_conjugate) gamma = 0.5 * gamma;
      result.width_in_GeV = result.width_in_GeV + gamma;

      // Rescale the SM decay branching fractions.
      double wscaling = Dep::Reference_SM_Higgs_decay_rates->width_in_GeV/result.width_in_GeV;
      for (auto it = result.channels.begin(); it != result.channels.end(); ++it)
      {
        it->second.first  *= wscaling; // rescale BF
        it->second.second *= wscaling; // rescale error on BF
      }

      // Add the h->SS branching fraction
      result.set_BF(gamma/result.width_in_GeV, 0.0, "S", "S");

      // Make sure the width is sensible.
      check_width(LOCAL_INFO, result.width_in_GeV, runOptions->getValueOrDef<bool>(false, "invalid_point_for_negative_width"));
    }

    //////////// Vector singlet DM /////////////////////

    /// Add the decay of Higgs to vectors for the VectorSingletDM models (see arXiv:1512.06458v4)
    void VectorSingletDM_Higgs_decays (DecayTable::Entry& result)
    {
      using namespace Pipes::VectorSingletDM_Higgs_decays;

      // Get the spectrum information
      const Spectrum& spec = *Dep::VectorSingletDM_Z2_spectrum;
      const SubSpectrum& he = spec.get_HE();
      double mass = spec.get(Par::Pole_Mass,"V");
      double lambda = he.get(Par::dimensionless,"lambda_hV");
      double v0 = he.get(Par::mass1,"vev");
      double mhpole = spec.get(Par::Pole_Mass,"h0_1");

      // Get the reference SM Higgs decays
      result = *Dep::Reference_SM_Higgs_decay_rates;

      // Add the h -> VV width to the total
      double massratio2 = pow(mass/mhpole,2);
      double midfactor = (1 - 4*massratio2 + 12*pow(massratio2,2));
      double gamma = (2.0*mass <= mhpole) ? ((pow(lambda*v0,2)*pow(mhpole,3))/(128.0*pi*pow(mass,4))) * midfactor * sqrt(1.0 - 4.0*massratio2) : 0.0;
      result.width_in_GeV = result.width_in_GeV + gamma;

      // Print out the h -> VV width for debugging
      logger() << "Gamma (h -> VV) = " << gamma << " GeV" << std::endl;

      // Rescale the SM decay branching fractions.
      double wscaling = Dep::Reference_SM_Higgs_decay_rates->width_in_GeV/result.width_in_GeV;
      for (auto it = result.channels.begin(); it != result.channels.end(); ++it)
      {
        it->second.first  *= wscaling; // rescale BF
        it->second.second *= wscaling; // rescale error on BF
      }

      // Add the h->VV branching fraction
      result.set_BF(gamma/result.width_in_GeV, 0.0, "V", "V");

      // Make sure the width is sensible.
      check_width(LOCAL_INFO, result.width_in_GeV, runOptions->getValueOrDef<bool>(false, "invalid_point_for_negative_width"));
    }

    //////////// Majorana fermion singlet DM /////////////////////

    /// Add the decay of Higgs to Majorana fermions for the MajoranaSingletDM models (see arXiv:1512.06458v4)
    void MajoranaSingletDM_Higgs_decays (DecayTable::Entry& result)
    {
      using namespace Pipes::MajoranaSingletDM_Higgs_decays;

      // Get the spectrum information
      const Spectrum& spec = *Dep::MajoranaSingletDM_Z2_spectrum;
      const SubSpectrum& he = spec.get_HE();
      double mass = spec.get(Par::Pole_Mass,"X");
      double lambda = he.get(Par::dimensionless,"lX");
      double cxi = std::cos(he.get(Par::dimensionless,"xi"));
      double v0 = he.get(Par::mass1,"vev");
      double mhpole = spec.get(Par::Pole_Mass,"h0_1");

      // Get the reference SM Higgs decays
      result = *Dep::Reference_SM_Higgs_decay_rates;

      // Add the h -> XX width to the total
      double massratio2 = pow(mass/mhpole,2);
      double lfactor = (1 - 4*massratio2*pow(cxi,2));
      double gamma = (2.0*mass <= mhpole) ? ((mhpole*pow(v0*lambda,2))/(16.0*pi)) * sqrt(1.0 - 4.0*massratio2) * lfactor : 0.0;
      result.width_in_GeV = result.width_in_GeV + gamma;

      // Print out the h -> XX width for debugging
      logger() << "Gamma (h -> XX) = " << gamma << " GeV" << std::endl;

      // Rescale the SM decay branching fractions.
      double wscaling = Dep::Reference_SM_Higgs_decay_rates->width_in_GeV/result.width_in_GeV;
      for (auto it = result.channels.begin(); it != result.channels.end(); ++it)
      {
        it->second.first  *= wscaling; // rescale BF
        it->second.second *= wscaling; // rescale error on BF
      }

      // Add the h->XX branching fraction
      result.set_BF(gamma/result.width_in_GeV, 0.0, "X", "X");

      // Make sure the width is sensible.
      check_width(LOCAL_INFO, result.width_in_GeV, runOptions->getValueOrDef<bool>(false, "invalid_point_for_negative_width"));
    }

    //////////// Dirac fermion singlet DM /////////////////////

    /// Add the decay of Higgs to Dirac fermions for the DiracSingletDM models (see arXiv:1512.06458v4)
    void DiracSingletDM_Higgs_decays (DecayTable::Entry& result)
    {
      using namespace Pipes::DiracSingletDM_Higgs_decays;

      // Get the spectrum information
      const Spectrum& spec = *Dep::DiracSingletDM_Z2_spectrum;
      const SubSpectrum& he = spec.get_HE();
      double mass = spec.get(Par::Pole_Mass,"F");
      double lambda = he.get(Par::dimensionless,"lF");
      double cxi = std::cos(he.get(Par::dimensionless,"xi"));
      double v0 = he.get(Par::mass1,"vev");
      double mhpole = spec.get(Par::Pole_Mass,"h0_1");

      // Get the reference SM Higgs decays
      result = *Dep::Reference_SM_Higgs_decay_rates;

      // Add the h -> FF width to the total
      double massratio2 = pow(mass/mhpole,2);
      double lfactor = (1 - 4*massratio2*pow(cxi,2));
      double gamma = (2.0*mass <= mhpole) ? ((mhpole*pow(v0*lambda,2))/(8.0*pi)) * sqrt(1.0 - 4.0*massratio2) * lfactor : 0.0;
      result.width_in_GeV = result.width_in_GeV + gamma;

      // Print out the h -> FF width for debugging
      logger() << "Gamma (h -> FF) = " << gamma << " GeV" << std::endl;

      // Rescale the SM decay branching fractions.
      double wscaling = Dep::Reference_SM_Higgs_decay_rates->width_in_GeV/result.width_in_GeV;
      for (auto it = result.channels.begin(); it != result.channels.end(); ++it)
      {
        it->second.first  *= wscaling; // rescale BF
        it->second.second *= wscaling; // rescale error on BF
      }

      // Add the h->FF branching fraction
      result.set_BF(gamma/result.width_in_GeV, 0.0, "F", "F");

      // Make sure the width is sensible.
      check_width(LOCAL_INFO, result.width_in_GeV, runOptions->getValueOrDef<bool>(false, "invalid_point_for_negative_width"));
    }


    //////////// Everything ///////////////////

    /// Collect all the DecayTable entries into an actual DecayTable
    void all_decays (DecayTable &decays)
    {
      using namespace Pipes::all_decays;

      decays("h0_1") = *Dep::Higgs_decay_rates;     // Add the Higgs decays.
      decays("Z0") = *Dep::Z_decay_rates;           // Add the Z decays
      decays("W+") = *Dep::W_plus_decay_rates;      // Add the W decays for W+.
      decays("W-") = *Dep::W_minus_decay_rates;     // Add the W decays for W-

      decays("t") = *Dep::t_decay_rates;            // Add the top decays for t.
      decays("tbar") = *Dep::tbar_decay_rates;      // Add the top decays for tbar
      decays("u_3") = decays("t");                  // Duplicate for mass-ordered quarks
      decays("ubar_3") = decays("tbar");            // Duplicate for mass-ordered quarks

      decays("mu+") = *Dep::mu_plus_decay_rates;    // Add the muon decays for mu+.
      decays("mu-") = *Dep::mu_minus_decay_rates;   // Add the muon decays for mu-
      decays("e+_2") = decays("mu+");               // Duplicate for mass-ordered leptons
      decays("e-_2") = decays("mu-");               // Duplicate for mass-ordered leptons

      decays("tau+") = *Dep::tau_plus_decay_rates;  // Add the tauon decays for tau+.
      decays("tau-") = *Dep::tau_minus_decay_rates; // Add the tauon decays for tau-.
      decays("e+_3") = decays("tau+");              // Duplicate for mass-ordered leptons
      decays("e-_3") = decays("tau-");              // Duplicate for mass-ordered leptons

      decays("pi0") = *Dep::pi_0_decay_rates;       // Add the neutral pion decays.
      decays("pi+") = *Dep::pi_plus_decay_rates;    // Add the pi+ decays.
      decays("pi-") = *Dep::pi_minus_decay_rates;   // Add the pi- decays.
      decays("eta") = *Dep::eta_decay_rates;        // Add the eta meson decays.
      decays("rho0") = *Dep::rho_0_decay_rates;     // Add the neutral rho meson decays.
      decays("rho+") = *Dep::rho_plus_decay_rates;  // Add the rho+ decays.
      decays("rho-") = *Dep::rho_minus_decay_rates; // Add the rho- decays.
      decays("omega") = *Dep::omega_decay_rates;    // Add the omega meson decays.
      

      // MSSM-specific
      if (ModelInUse("MSSM63atQ") or ModelInUse("MSSM63atMGUT"))
      {

        static bool allow_stable_charged_particles = runOptions->getValueOrDef<bool>(false, "allow_stable_charged_particles");

        // Make sure that if the user has elected to take Higgs decays from FeynHiggs that
        // they have elected to take the Higgs mass from FeynHiggs alone.
        if (Dep::Higgs_decay_rates->calculator == "FeynHiggs" or
            Dep::h0_2_decay_rates->calculator == "FeynHiggs" or
            Dep::A0_decay_rates->calculator == "FeynHiggs" or
            Dep::H_plus_decay_rates->calculator == "FeynHiggs" or
            Dep::t_decay_rates->calculator == "FeynHiggs")
        {
          if (not Dep::MSSM_spectrum->get_HE().has(Par::dimensionless, "h mass from: SpecBit::FH_HiggsMass, SpecBit::FH_HeavyHiggsMasses"))
           DecayBit_error().raise(LOCAL_INFO, "You must use Higgs masses from FeynHiggs if you choose to use FeynHiggs "
                                              "to calculate h or t decays.\nPlease modify your yaml file accordingly.");
        }

        mass_es_pseudonyms psn = *Dep::SLHA_pseudonyms;

        decays("h0_2") = *Dep::h0_2_decay_rates;                 // Add the h0_2 decays.
        decays("A0") = *Dep::A0_decay_rates;                     // Add the A0 decays.
        decays("H+") = *Dep::H_plus_decay_rates;                 // Add the H+ decays.
        decays("H-") = *Dep::H_minus_decay_rates;                // Add the H- decays.

        decays("~g") = *Dep::gluino_decay_rates;                 // Add the gluino decays.

        decays("~chi+_1") = *Dep::chargino_plus_1_decay_rates;   // Add the ~chi+_1 decays.
        decays("~chi-_1") = *Dep::chargino_minus_1_decay_rates;  // Add the ~chi+_1 decays.
        decays("~chi+_2") = *Dep::chargino_plus_2_decay_rates;   // Add the ~chi+_2 decays.
        decays("~chi-_2") = *Dep::chargino_minus_2_decay_rates;  // Add the ~chi+_2 decays.
        decays("~chi0_1") = *Dep::neutralino_1_decay_rates;      // Add the ~chi0_1 decays.
        decays("~chi0_2") = *Dep::neutralino_2_decay_rates;      // Add the ~chi0_2 decays.
        decays("~chi0_3") = *Dep::neutralino_3_decay_rates;      // Add the ~chi0_3 decays.
        decays("~chi0_4") = *Dep::neutralino_4_decay_rates;      // Add the ~chi0_4 decays.

        decays(psn.ist1) = *Dep::stop_1_decay_rates;             // Add the ~t_1 decays.
        decays(psn.ist2) = *Dep::stop_2_decay_rates;             // Add the ~t_2 decays.
        decays(psn.isb1) = *Dep::sbottom_1_decay_rates;          // Add the ~b_1 decays.
        decays(psn.isb2) = *Dep::sbottom_2_decay_rates;          // Add the ~b_2 decays.
        decays(psn.isul) = *Dep::sup_l_decay_rates;              // Add the ~u_L decays.
        decays(psn.isur) = *Dep::sup_r_decay_rates;              // Add the ~u_R decays.
        decays(psn.isdl) = *Dep::sdown_l_decay_rates;            // Add the ~d_L decays.
        decays(psn.isdr) = *Dep::sdown_r_decay_rates;            // Add the ~d_R decays.
        decays(psn.iscl) = *Dep::scharm_l_decay_rates;           // Add the ~c_L decays.
        decays(psn.iscr) = *Dep::scharm_r_decay_rates;           // Add the ~c_R decays.
        decays(psn.issl) = *Dep::sstrange_l_decay_rates;         // Add the ~s_L decays.
        decays(psn.issr) = *Dep::sstrange_r_decay_rates;         // Add the ~s_R decays.
        decays(psn.isell) = *Dep::selectron_l_decay_rates;       // Add the ~e-_L decays.
        decays(psn.iselr) = *Dep::selectron_r_decay_rates;       // Add the ~e-_R decays.
        decays(psn.ismul) = *Dep::smuon_l_decay_rates;           // Add the ~mu-_L decays.
        decays(psn.ismur) = *Dep::smuon_r_decay_rates;           // Add the ~mu-_R decays.
        decays(psn.istau1) = *Dep::stau_1_decay_rates;           // Add the ~tau_1 decays.
        decays(psn.istau2) = *Dep::stau_2_decay_rates;           // Add the ~tau_2 decays.
        decays(psn.isnel) = *Dep::snu_electronl_decay_rates;     // Add the ~nu_e decays.
        decays(psn.isnmul) = *Dep::snu_muonl_decay_rates;        // Add the ~nu_mu decays.
        decays(psn.isntaul) = *Dep::snu_taul_decay_rates;        // Add the ~nu_tau decays.

        decays(psn.ist1bar) = *Dep::stopbar_1_decay_rates;       // Add the ~tbar_1 decays.
        decays(psn.ist2bar) = *Dep::stopbar_2_decay_rates;       // Add the ~tbar_2 decays.
        decays(psn.isb1bar) = *Dep::sbottombar_1_decay_rates;    // Add the ~bbar_1 decays.
        decays(psn.isb2bar) = *Dep::sbottombar_2_decay_rates;    // Add the ~bbar_2 decays.
        decays(psn.isulbar) = *Dep::supbar_l_decay_rates;        // Add the ~ubar_L decays.
        decays(psn.isurbar) = *Dep::supbar_r_decay_rates;        // Add the ~ubar_R decays.
        decays(psn.isdlbar) = *Dep::sdownbar_l_decay_rates;      // Add the ~dbar_L decays.
        decays(psn.isdrbar) = *Dep::sdownbar_r_decay_rates;      // Add the ~dbar_R decays.
        decays(psn.isclbar) = *Dep::scharmbar_l_decay_rates;     // Add the ~cbar_L decays.
        decays(psn.iscrbar) = *Dep::scharmbar_r_decay_rates;     // Add the ~cbar_R decays.
        decays(psn.isslbar) = *Dep::sstrangebar_l_decay_rates;   // Add the ~sbar_L decays.
        decays(psn.issrbar) = *Dep::sstrangebar_r_decay_rates;   // Add the ~sbar_R decays.
        decays(psn.isellbar) = *Dep::selectronbar_l_decay_rates; // Add the ~e+_L decays.
        decays(psn.iselrbar) = *Dep::selectronbar_r_decay_rates; // Add the ~e+_R decays.
        decays(psn.ismulbar) = *Dep::smuonbar_l_decay_rates;     // Add the ~mu+_L decays.
        decays(psn.ismurbar) = *Dep::smuonbar_r_decay_rates;     // Add the ~mu+_R decays.
        decays(psn.istau1bar) = *Dep::staubar_1_decay_rates;     // Add the ~taubar_1 decays.
        decays(psn.istau2bar) = *Dep::staubar_2_decay_rates;     // Add the ~taubar_2 decays.
        decays(psn.isnelbar)= *Dep::snubar_electronl_decay_rates;// Add the ~nu_e decays.
        decays(psn.isnmulbar) = *Dep::snubar_muonl_decay_rates;  // Add the ~nu_mu decays.
        decays(psn.isntaulbar) = *Dep::snubar_taul_decay_rates;  // Add the ~nu_tau decays.

        /// Spit out the full decay table as SLHA1 and SLHA2 files.
        if (runOptions->getValueOrDef<bool>(false, "drop_SLHA_file"))
        {
          // Spit out the full decay table in SLHA1 and SLHA2 formats.
          str prefix   = runOptions->getValueOrDef<str>("", "SLHA_output_prefix");
          str filename = runOptions->getValueOrDef<str>("GAMBIT_decays", "SLHA_output_filename");
          decays.writeSLHAfile(1,prefix+filename+".slha1",false,psn);
          decays.writeSLHAfile(2,prefix+filename+".slha2",false,psn);
        }

        /// Invalidate MSSM points that have a stable charged particle?
        if (not allow_stable_charged_particles)
        {
          static const double lifetime_universe = 4.35e17; // [seconds]

          // Create vector with names of all charged partices
          static const std::vector<str> charged_particle_names = {
            "H+", "~chi+_1", "~chi+_2",
            psn.ist1, psn.ist2,
            psn.isb1, psn.isb2,
            psn.isul, psn.isur,
            psn.isdl, psn.isdr,
            psn.iscl, psn.iscr,
            psn.issl, psn.issr,
            psn.isell, psn.iselr,
            psn.ismul, psn.ismur,
            psn.istau1, psn.istau2
          };

          // Check lifetime for each charged particle
          for (auto& particle_name : charged_particle_names)
          {
            double width = decays(particle_name).width_in_GeV;
            if (width <= 0 || hbar/width > lifetime_universe)
            {
              std::stringstream msg;
              msg << "Charged particle " << particle_name << " is stable. Decay width = " << width << " GeV.";
              invalid_point().raise(msg.str());
            }
          }
        }

        /// Check all particles for negative decay width
        for (auto& map_entry : decays.particles)
        {
          double width = map_entry.second.width_in_GeV;
          if (width < 0)
          {
              std::stringstream msg;
              msg << "Particle " << map_entry.first.first << " has a negative width = " << width << " GeV.";
              invalid_point().raise(msg.str());
          }
        }

      }

      else

      {
        /// Spit out the full decay table as an SLHA file.
        if (runOptions->getValueOrDef<bool>(false, "drop_SLHA_file"))
        {
          // Spit out the full decay table in SLHA1 and SLHA2 formats.
          str filename = runOptions->getValueOrDef<str>("GAMBIT_decays", "SLHA_output_filename");
          decays.writeSLHAfile(2,filename+".slha",false);
        }

      }

    }

    /// Read an SLHA2 file in and use it to create a GAMBIT DecayTable.
    ///  Note that creating a DecayTable from an SLHA1 file is not possible at present.
    void all_decays_from_SLHA(DecayTable& decays)
    {
      using namespace Pipes::all_decays_from_SLHA;
      if (not runOptions->hasKey("SLHA_decay_filenames"))
      {
        DecayBit_error().raise(LOCAL_INFO, "Option \"SLHA_decay_filenames\" is required to use this function.");
      }
      static unsigned int counter = 0;
      std::vector<str> filenames = runOptions->getValue<std::vector<str> >("SLHA_decay_filenames");
      logger() << "Reading SLHA file: " << filenames[counter] << EOM;
      std::ifstream ifs(filenames[counter]);
      if(!ifs.good()) backend_error().raise(LOCAL_INFO, "SLHA file not found.");
      SLHAstruct slha(ifs);
      ifs.close();
      counter++;
      if (counter >= filenames.size()) counter = 0;
      decays = DecayTable(slha);
    }

    /// Convert the DecayTable to a format where we can print each individual channel's BF
    void get_decaytable_as_map(map_str_dbl& map)
    {
      using namespace Pipes::get_decaytable_as_map;

      const DecayTable* tbl = &(*Dep::decay_rates);

      std::vector<std::vector<str> > bfs;
      std::string channel;
      double BF = 0.0;
      
      // If the user specifies "printall" -- then print everything.
      bool printall = runOptions->getValueOrDef(false, "printall");
      if (printall)
      {
        // Iterate through DecayTable.
        for (auto it = tbl->particles.begin(); it != tbl->particles.end(); ++it)
        {
          std::pair<int, int> pdg = it->first;
          std::vector<str> bf = {Models::ParticleDB().partmap::long_name(pdg)};
          bfs.push_back(bf);
        }
      }

      /// Otherwise just print the specific, named channels
      else
      {
        std::vector<std::vector<str> > BFs; // Empty set of braching fractions.
        bfs = runOptions->getValueOrDef<std::vector<std::vector<str> > >(BFs, "BFs");
      }

      // Iterate through branching ratios
      for ( const auto &row : bfs )
      {

        std::string decaypart = row.front();
        const DecayTable::Entry entry = tbl->at(decaypart); 

        // If the entry is a single particle, then add every BF for this channel
        if ( row.size() == 1 )
        {
          for (auto it = entry.channels.begin(); it != entry.channels.end(); ++it)
          {
            BF = it->second.first;

            std::multiset< std::pair<int,int> > ch = it->first;              
            std::vector<str> chan;

            // Create a vector of final states by particle name.
            for (auto it2 = ch.begin(); it2 != ch.end(); ++it2) chan.push_back(Models::ParticleDB().partmap::long_name(*it2));
            
            // Write the name of the output channel.
            channel = row[0] + "->" + chan[0] + "+" + chan[1];

            // + 3-body decay case: add the third final state particle if needed.
            if (chan.size() == 3) channel += "+" + chan[2];

            map[channel] = BF;
          }

        }

        // No 1-body decays..

        // 2-body decays channel-by-channel
        else if ( row.size() == 3 )
        {
          BF = entry.BF( row[1], row[2] );
          channel = row[0] + "->" + row[1] + "+" + row[2];
          map[channel] = BF;
        }

        // 3-body decays channel-by-channel 
        // (SB: I don't think we have these yet. But if/when we do, they will be supported)
        else if (row.size() == 4 )
        {
          BF = entry.BF( row[1], row[2], row[3] );
          channel = row[0] + "->" + row[1] + "+" + row[2] + "+" + row[3];
          map[channel] = BF;
        }
      }
    }


    /// Get MSSM mass eigenstate pseudonyms for the gauge eigenstates
    void get_mass_es_pseudonyms(mass_es_pseudonyms& result)
    {
      using namespace Pipes::get_mass_es_pseudonyms;
      const SubSpectrum& mssm = (*Dep::MSSM_spectrum).get_HE();

      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      const static bool pt_error = runOptions->getValueOrDef<bool>(true, "gauge_mixing_tolerance_invalidates_point_only");
      bool debug = runOptions->getValueOrDef<bool>(false, "debug");
      result.refill(mssm, tol, pt_error, debug);
    }

    /// SLHA1 mixing check flag
    /// This gets set non-zero if first or second generation left-right mixing
    /// exceeds the specified tolerance (which means that SLHA1 is an invalid format for
    /// this model point).
    /// 1 = u, 2 = d, 3 = c, 4 = s, 5 = e, 6 = mu
    void check_first_sec_gen_mixing (int& result)
    {
      using namespace Pipes::check_first_sec_gen_mixing;
      const static double tol = runOptions->getValueOrDef<double>(1e-2, "gauge_mixing_tolerance");
      result = 0;
      double max_mixing;
      const SubSpectrum& mssm = (*Dep::MSSM_spectrum).get_HE();
      str x = slhahelp::mass_es_from_gauge_es("~u_L", max_mixing, mssm);
      if((max_mixing*max_mixing) <= 1-tol) result = 1;
      x = slhahelp::mass_es_from_gauge_es("~u_R", max_mixing, mssm);
      if((max_mixing*max_mixing) <= 1-tol) result = 1;
      x = slhahelp::mass_es_from_gauge_es("~d_L", max_mixing, mssm);
      if((max_mixing*max_mixing) <= 1-tol) result = 2;
      x = slhahelp::mass_es_from_gauge_es("~d_R", max_mixing, mssm);
      if((max_mixing*max_mixing) <= 1-tol) result = 2;
      x = slhahelp::mass_es_from_gauge_es("~c_L", max_mixing, mssm);
      if((max_mixing*max_mixing) <= 1-tol) result = 3;
      x = slhahelp::mass_es_from_gauge_es("~c_R", max_mixing, mssm);
      if((max_mixing*max_mixing) <= 1-tol) result = 3;
      x = slhahelp::mass_es_from_gauge_es("~s_L", max_mixing, mssm);
      if((max_mixing*max_mixing) <= 1-tol) result = 4;
      x = slhahelp::mass_es_from_gauge_es("~s_R", max_mixing, mssm);
      if((max_mixing*max_mixing) <= 1-tol) result = 4;
      x = slhahelp::mass_es_from_gauge_es("~e_L", max_mixing, mssm);
      if((max_mixing*max_mixing) <= 1-tol) result = 5;
      x = slhahelp::mass_es_from_gauge_es("~e_R", max_mixing, mssm);
      if((max_mixing*max_mixing) <= 1-tol) result = 5;
      x = slhahelp::mass_es_from_gauge_es("~mu_L", max_mixing, mssm);
      if((max_mixing*max_mixing) <= 1-tol) result = 6;
      x = slhahelp::mass_es_from_gauge_es("~mu_R", max_mixing, mssm);
      if((max_mixing*max_mixing) <= 1-tol) result = 6;
    }

    /// @}

    // Read and interpolate chi2 table
    daFunk::Funk get_Higgs_invWidth_chi2(std::string filename)
    {
      ASCIItableReader table(filename);
      std::vector<std::string> colnames = initVector<std::string>("BR", "Delta_chi2");
      table.setcolnames(colnames);
      return daFunk::interp("BR", table["BR"], table["Delta_chi2"]);
    }


    void MSSM_inv_Higgs_BF(double &BF)
    {
      /**
         @brief Branching fraction for Higgs into pair of lightest neutralinos

         @warning Tree-level formulas
         @warning Assumes decoupling limit for Higgs mixing angle
         \f[
         \alpha = \beta - \frac12 \pi
         \f]
         @warning Only includes neutralinos, charginos and SM-like width in
         total width

         @param BF \f$\textrm{BR}(h\to\chi^0_1\chi^0_1)\f$
      */
      using namespace Pipes::MSSM_inv_Higgs_BF;
      const Spectrum& spec = *Dep::MSSM_spectrum;
      const SubSpectrum& MSSM = Dep::MSSM_spectrum->get_HE();
      const SMInputs& SM = Dep::MSSM_spectrum->get_SMInputs();

      // Neutralino masses with phases
      std::array<double, 4> m_0;
      for (int i = 0; i <= 3; i += 1)
      {
        m_0[i] = spec.get(Par::Pole_Mass, "~chi0", i + 1);
      }

      // Neutralino mixing matrix
      std::array<std::array<double, 4>, 4> Z;
      for (int i = 0; i <= 3; i += 1)
      {
        for (int j = 0; j <= 3; j += 1)
        {
          Z[i][j] = MSSM.get(Par::Pole_Mixing, "~chi0", i + 1, j + 1);
        }
      }

      // Chargino masses
      std::array<double, 2> m_pm;
      for (int i = 0; i <= 1; i += 1)
      {
        m_pm[i] = spec.get(Par::Pole_Mass, "~chi+", i + 1);
      }

      // Chargino mixing matrices
      std::array<std::array<double, 2>, 2> U, V;
      for (int i = 0; i <= 1; i += 1)
      {
        for (int j = 0; j <= 1; j += 1)
        {
          U[i][j] = MSSM.get(Par::Pole_Mixing, "~chi-", i + 1, j + 1);
          V[i][j] = MSSM.get(Par::Pole_Mixing, "~chi+", i + 1, j + 1);
        }
      }

      // SM parameters
      const double mh = MSSM.get(Par::Pole_Mass, "h0_1");
      const double mw = MSSM.get(Par::Pole_Mass, "W+");
      const double GF = SM.GF;
      const double sw2 = MSSM.safeget(Par::dimensionless, "sinW2");

      // Higgs mixing angle
      const double beta = atan(MSSM.safeget(Par::dimensionless, "tanbeta"));
      const double alpha = beta - 0.5 * pi;

      // Higgs invisible width
      double gamma_inv = 0.;
      try
      {
        gamma_inv = MSSM_H::gamma_h_chi_0(0, 0, m_0, Z, alpha, mh, mw, GF, sw2);
      }
      catch (const std::invalid_argument& e)
      {
        DecayBit_error().raise(LOCAL_INFO, e.what());
      }

      // SM-like Higgs width
      DecayTable::Entry SM_h;
      compute_SM_higgs_decays(SM_h, mh);
      const double gamma_SM = SM_h.width_in_GeV;

      // Width to neutralinos and charginos
      double gamma_chi = 0.;
      try
      {
        gamma_chi = MSSM_H::gamma_h_chi(m_pm, m_0, U, V, Z, alpha, mh, mw, GF, sw2);
      }
      catch (const std::invalid_argument& e)
      {
        DecayBit_error().raise(LOCAL_INFO, e.what());
      }

      // Total Higgs width
      double gamma_tot = gamma_SM + gamma_chi;

      BF = gamma_inv / gamma_tot;
    }

    void ScalarSingletDM_inv_Higgs_BF(double& BF)
    {
       /**
          @brief Branching fraction for Higgs into scalar singlet DM
          @param BF \f$\textrm{BR}(h\to S S)\f$
       */
       using namespace Pipes::ScalarSingletDM_inv_Higgs_BF;
       BF = Dep::Higgs_decay_rates->BF("S", "S");
    }

    void VectorSingletDM_inv_Higgs_BF(double& BF)
    {
       /**
          @brief Branching fraction for Higgs into vector singlet DM
          @param BF \f$\textrm{BR}(h\to V V)\f$
       */
       using namespace Pipes::VectorSingletDM_inv_Higgs_BF;
       BF = Dep::Higgs_decay_rates->BF("V", "V");
    }

    void MajoranaSingletDM_inv_Higgs_BF(double& BF)
    {
       /**
          @brief Branching fraction for Higgs into Majorana singlet DM
          @param BF \f$\textrm{BR}(h\to X X)\f$
       */
       using namespace Pipes::MajoranaSingletDM_inv_Higgs_BF;
       BF = Dep::Higgs_decay_rates->BF("X", "X");
    }

    void DiracSingletDM_inv_Higgs_BF(double& BF)
    {
       /**
          @brief Branching fraction for Higgs into Dirac singlet DM
          @param BF \f$\textrm{BR}(h\to F F)\f$
       */
       using namespace Pipes::DiracSingletDM_inv_Higgs_BF;
       BF = Dep::Higgs_decay_rates->BF("F", "F");
    }

    void lnL_Higgs_invWidth_SMlike(double& lnL)
    {
      /**
         @brief Log-likelihood for Higgs invisible branching ratio

         We use log-likelihoods extracted from e.g.,
         <a href="http://cms-results.web.cern.ch/cms-results/public-results/
         preliminary-results/HIG-17-023/CMS-PAS-HIG-17-023_Figure_007-b.png">
         CMS-PAS-HIG-17-023</a>

         There are scripts
         @code
         python ./DecayBit/data/convolve_with_theory.py <file> <frac_error> <min> <max>
         @endcode
         for convolving a data file with a fractional theory error, and
         @code
         python ./DecayBit/data/profile_theory.py <file> <frac_error> <min> <max>
         @endcode
         for profiling a fractional theory error.

         There are a few data files, e.g.,
         @code
         ./DecayBit/data/arXiv_1306.2941_Figure_8.dat
         ./DecayBit/data/CMS-PAS-HIG-17-023_Figure_7-b.dat
         ./DecayBit/data/CMS-PAS-HIG-17-023_Figure_7-b_10_convolved.dat
         ./DecayBit/data/CMS-PAS-HIG-17-023_Figure_7-b_10_profiled.dat
         @endcode
         The first one is the default. The third and fourth ones include a 10%
         theory uncertainty in the branching fraction by convolving it and
         profiling it, respectively. The data file is specified in
         the YAML by the `BR_h_inv_chi2_data_file` option. The path is
         relative to the GAMBIT directory, `GAMBIT_DIR`.

         @warning This typically assumes that the Higgs is otherwise SM-like,
         i.e., no changes to production cross sections or any other decays.

         @param lnL Log-likelihood for Higgs invisible branching ratio
      */
      using namespace Pipes::lnL_Higgs_invWidth_SMlike;

      const double BF = *Dep::inv_Higgs_BF;

      if (BF < 0.)
      {
        DecayBit_error().raise(LOCAL_INFO, "negative BF");
      }

      const std::string default_name = "./DecayBit/data/arXiv_1306.2941_Figure_8.dat";
      const std::string name = runOptions->getValueOrDef<std::string>
        (default_name, "BR_h_inv_chi2_data_file");
      static daFunk::Funk chi2 = get_Higgs_invWidth_chi2(GAMBIT_DIR "/" + name);
      lnL = -0.5 * chi2->bind("BR")->eval(BF);
    }

    void lnL_Z_inv(double& lnL)
    {
      /**
         @brief Log-likelihood from LEP measurements of \f$Z\f$-boson invisible
         width

         @warning This is valid for SM, RHN models and for MSSM-like models with Z-boson invisible decays
         to neutralinos and neutrinos

         @param lnL Log-likelihood
      */
      using namespace Pipes::lnL_Z_inv;
      const triplet<double> gamma_nu = *Dep::Z_gamma_nu;
      double gamma_inv = gamma_nu.central;
      const double tau_nu = 0.5 * (gamma_nu.upper + gamma_nu.lower);
      double tau = tau_nu;
 
      if(ModelInUse("MSSM63atQ") or ModelInUse("MSSM63atMGUT"))
      {
        const triplet<double> gamma_chi_0 = *Dep::Z_gamma_chi_0;
        gamma_inv += gamma_chi_0.central;
        // Average + and - errors
        const double tau_chi_0 = 0.5 * (gamma_chi_0.upper + gamma_chi_0.lower);
        // Add theory errors in quadrature
        tau = std::sqrt(pow(tau, 2) + pow(tau_chi_0, 2));
      }

      lnL = Stats::gaussian_loglikelihood(gamma_inv, SM_Z::gamma_inv.mu, tau, SM_Z::gamma_inv.sigma, false);
   
    }

    void Z_gamma_nu_2l(triplet<double>& gamma)
    {
      /**
         @brief Calculate width of \f$Z\f$ decays to neutrinos (with RHN correction if present),
         \f$\Gamma(Z\to\nu\nu)\f$ at two-loop in GeV

         @warning This uses input \f$\alpha(M_Z)\f$ - does not include input
         light-quark thresholds.

         @param gamma \f$\Gamma(Z\to\chi\chi)\f$
      */
      using namespace Pipes::Z_gamma_nu_2l;

      const SMInputs& SM = Dep::SM_spectrum->get_SMInputs();

      // Construct SM Z two-loop object
      const double mh_OS = Dep::SM_spectrum->get(Par::Pole_Mass, "h0_1");
      const double MZ = Dep::SM_spectrum->get(Par::Pole_Mass, "Z0");
      auto Z = SM_Z::TwoLoop(mh_OS, SM.mT, MZ, SM.alphaS, delta_alpha_OS);

      if (Z.nuisances_outside_ranges())
      {
        DecayBit_warning().raise(LOCAL_INFO, "SM nuisance parameters outside "
          "range of validity for two-loop Z formulas. Not accounting for "
          "variation in SM nuisance parameters");
      }

      double Z_inv_width = Z.gamma_inv();

      // Apply RHN correction, from 1311.2830 in the limit m_nu / m_Z-> 0
      if(ModelInUse("RightHandedNeutrinos"))
      {
        double Z_to_nu = Z_inv_width/3;
        std::vector<double> mN = {*Param["M_1"], *Param["M_2"], *Param["M_3"]};
        Eigen::Matrix3cd VnuNorm = Dep::SeesawI_Vnu->adjoint() * *Dep::SeesawI_Vnu;
        Eigen::Matrix3cd ThetaVnuNorm = Dep::SeesawI_Vnu->adjoint() * *Dep::SeesawI_Theta;
        Eigen::Matrix3cd ThetaNorm = *Dep::SeesawI_Theta * Dep::SeesawI_Theta->adjoint();

        // Z -> nu nu with RHN mixing
        Z_inv_width = Z_to_nu*( std::norm(VnuNorm(0,0)) + std::norm(VnuNorm(0,1)) + std::norm(VnuNorm(0,2)) 
                              + std::norm(VnuNorm(1,0)) + std::norm(VnuNorm(1,1)) + std::norm(VnuNorm(1,2))
                              + std::norm(VnuNorm(2,0)) + std::norm(VnuNorm(2,1)) + std::norm(VnuNorm(2,2)) );

        // Z -> nu N with RHN mixing
        for(int i = 0; i < 3; i++)
          if(mN[i] < MZ)
            Z_inv_width += Z_to_nu*(std::norm(ThetaVnuNorm(0,i)) + std::norm(ThetaVnuNorm(1,i)) + std::norm(ThetaVnuNorm(2,i)))*pow(1.0 - pow(mN[i]/MZ,2),2)*(1 + 0.5*pow(mN[i]/MZ,2));

        // Z -> NN with RHN mixing. Contribution neglected because is of order Theta^4

        // Add Gmu correction
        Z_inv_width /= sqrt(1 - std::abs(ThetaNorm(0,0)) - std::abs(ThetaNorm(1,1)));

      }

      // Set elements of triplet to the width and its error
      gamma.central = Z_inv_width;
      gamma.lower = Z.error_gamma_inv();
      gamma.upper = gamma.lower;  // Error is symmetric

    }

    void Z_gamma_chi_0_MSSM_tree(triplet<double>& gamma)
    {
      /**
         @brief Calculate width of \f$Z\f$ decays to the lightest neutralinos,
         \f$\Gamma(Z\to\chi^0_1\chi^0_1)\f$ in GeV

         @warning Tree-level formula with 10% error

         @param gamma \f$\Gamma(Z\to\chi^0_1\chi^0_1)\f$
      */
      using namespace Pipes::Z_gamma_chi_0_MSSM_tree;

      const Spectrum& spec = *Dep::MSSM_spectrum;
      const SubSpectrum& MSSM = Dep::MSSM_spectrum->get_HE();
      const SMInputs& SM = Dep::MSSM_spectrum->get_SMInputs();

      // Neutralino masses without phases
      std::array<double, 4> m_0;
      for (int i = 0; i <= 3; i += 1)
      {
        m_0[i] = std::fabs(spec.get(Par::Pole_Mass, "~chi0", i + 1));
      }

      // Neutralino mixing matrix
      std::array<std::array<double, 4>, 4> Z;
      for (int i = 0; i <= 3; i += 1)
      {
        for (int j = 0; j <= 3; j += 1)
        {
          Z[i][j] = MSSM.get(Par::Pole_Mixing, "~chi0", i + 1, j + 1);
        }
      }

      // SM nuisance parameters
      const double g2 = MSSM.safeget(Par::dimensionless, "g2");
      const double sw2 = MSSM.safeget(Par::dimensionless, "sinW2");
      const double MZ = SM.mZ;

      // Set elements of triplet to the width and its error
      gamma.central = MSSM_Z::gamma_chi_0(0, 0, m_0, Z, g2, MZ, sw2);
      gamma.lower = gamma.central * 0.1;
      gamma.upper = gamma.lower;  // Error is symmetric
    }

    // W decays, calculation from 1407.6607
    void RHN_W_to_l_decays(std::vector<double> &result)
    {
      using namespace Pipes::RHN_W_to_l_decays;
      SMInputs sminputs = *Dep::SMINPUTS;
      Eigen::Matrix3cd Theta = *Dep::SeesawI_Theta;
      double Gmu = sminputs.GF;
      double mw = Dep::mw->central;

      Eigen::Matrix3d ThetaNorm = (Theta * Theta.adjoint()).real();
      std::vector<double> ml = {sminputs.mE, sminputs.mMu, sminputs.mTau};
      std::vector<double> M = {*Param["M_1"], *Param["M_2"], *Param["M_3"]};

      result.clear();
      for(int i=0; i<3; i++)
      {
        if(M[i] < mw)
          result.push_back(Gmu*pow(mw,3)/(6*sqrt(2)*M_PI)*pow(1.0 - pow(ml[i]/mw,2),2)*(1.0 + pow(ml[i]/mw,2))/sqrt(1.0 - ThetaNorm(0,0) -ThetaNorm(1,1)));
        else
          result.push_back(Gmu*pow(mw,3)/(6*sqrt(2)*M_PI)*(1.0-ThetaNorm(i,i))*pow(1.0 - pow(ml[i]/mw,2),2)*(1.0 + pow(ml[i]/mw,2))/sqrt(1.0 - ThetaNorm(0,0) -ThetaNorm(1,1)));
      }
    }

    // Likelihood from W decays
    void lnL_W_decays_chi2(double &result)
    {
      using namespace Pipes::lnL_W_decays_chi2;
      std::vector<double> Wtoldecays = *Dep::W_to_l_decays;
      DecayTable::Entry decays = *Dep::W_plus_decay_rates;

      std::vector<double> Wwidth;
      std::vector<double> Wwidth_error;

      Wwidth.push_back(decays.width_in_GeV * decays.BF("e+","nu_e"));
      Wwidth_error.push_back(sqrt(pow(decays.width_in_GeV*decays.BF_error("e+","nu_e"),2) + pow(std::max(decays.positive_error, decays.negative_error)*decays.BF("e+","nu_e"),2)));
      Wwidth.push_back(decays.width_in_GeV * decays.BF("mu+","nu_mu"));
      Wwidth_error.push_back(sqrt(pow(decays.width_in_GeV*decays.BF_error("mu+","nu_mu"),2) + pow(std::max(decays.positive_error, decays.negative_error)*decays.BF("mu+","nu_mu"),2)));
      Wwidth.push_back(decays.width_in_GeV * decays.BF("tau+","nu_tau"));
      Wwidth_error.push_back(sqrt(pow(decays.width_in_GeV*decays.BF_error("tau+","nu_tau"),2) + pow(std::max(decays.positive_error, decays.negative_error)*decays.BF("tau+","nu_tau"),2)));

      result = Stats::gaussian_loglikelihood(Wtoldecays[0], Wwidth[0], 0.0, Wwidth_error[0], false);
      result += Stats::gaussian_loglikelihood(Wtoldecays[1], Wwidth[1], 0.0, Wwidth_error[1], false);
      result += Stats::gaussian_loglikelihood(Wtoldecays[2], Wwidth[2], 0.0, Wwidth_error[2], false);
    }


  }  // namespace DecayBit

}  // namespace Gambit
