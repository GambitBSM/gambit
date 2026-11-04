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
///  *********************************************

#include "gambit/Backends/frontend_macros.hpp"
#include "gambit/Backends/frontends/SusHi_1_7_0.hpp"
#include "gambit/Utils/mpiwrapper.hpp"
#include <fstream>
#include <cstring>
#include <cmath>

// Convenience functions (definitions)
BE_NAMESPACE
{
    // Runs SusHi's gg->h and bb->h NNLO cross-section computation for a
    // single point, given an MSSM spectrum.  This is called directly from
    // module functions (not from BE_INI_FUNCTION), so that emulatable
    // capabilities can skip this call entirely when the emulator's
    // prediction is trusted -- see calculate() in functor_definitions.hpp.
    void SusHi_run_point(const Spectrum& mySpec, const map_str_dbl& opts, double& ggh_result, double& bbh_result, double& ggh_err, double& bbh_err)
    {
    using namespace SLHAea;

    // User-tunable settings (passed from the module function's yaml options).
    // Anything not present in 'opts' falls back to the default given here.
    // Integer-valued SusHi entries are cast to int so they are written without
    // a decimal point (SusHi reads them with Fortran integer formats).
    auto dopt = [&opts](const std::string& key, double def)
    {
        auto it = opts.find(key);
        return (it == opts.end()) ? def : it->second;
    };
    auto iopt = [&dopt](const std::string& key, int def)
    {
        return (int)std::lround(dopt(key, def));
    };

    // Build MPI-safe temp filename
    int rank = 0;
    #ifdef WITH_MPI
    if (GMPI::Is_initialized())
    {
        GMPI::Comm comm;
        rank = comm.Get_rank();
    }
    #endif
    std::string infile = "SusHi_input_" + std::to_string(rank) + ".slha";

    // Get SLHA2 content from MSSM spectrum
    //SLHAea::Coll slha = mySpec.getSLHAea(2);
    SLHAea::Coll slha;


    // SMINPUTS
    SLHAea::Block sminputs("SMINPUTS");
    SLHAea::Line smin;

    smin << "BLOCK" << "SMINPUTS"; sminputs.push_back(smin); smin.clear();
    smin << 1 << 1.27934000e+02 << "# alpha_em^(-1)(MZ) SM MSbar" ; sminputs.push_back(smin); smin.clear();
    smin << 2 << 1.16637000e-05 << "# G_Fermi" ; sminputs.push_back(smin); smin.clear();
    smin << 3 << 1.17200000e-01 << "# alpha_s(MZ) SM MSbar" ; sminputs.push_back(smin); smin.clear();
    smin << 4 << 9.11876000e+01 << "# m_Z(pole)" ; sminputs.push_back(smin); smin.clear();
    smin << 5 << 4.18000000e+00 << "# m_b(m_b)" ; sminputs.push_back(smin); smin.clear();
    smin << 6 << 1.73300000e+02 << "# m_t(pole)" ; sminputs.push_back(smin); smin.clear();
    smin << 7 << 1.77686000e+00 << "# m_tau (pole)" ; sminputs.push_back(smin); smin.clear();
    smin << 8 << 1.27500000e+00 << "# m_c(m_c)" ; sminputs.push_back(smin); smin.clear();
    slha.push_back(sminputs);

    /// MASS block
    SLHAea::Block massBlock("MASS");
    SLHAea::Line mln;

    // get higgs masses 
    double mh  = mySpec.get(Par::Pole_Mass, "h0_1");  // lightest CP-even (h)
    double mH  = mySpec.get(Par::Pole_Mass, "h0_2");  // heavier CP-even (H)
    double mA  = mySpec.get(Par::Pole_Mass, "A0");    // CP-odd (A)
    //double mHp = mySpec.get(Par::Pole_Mass, "H+");    // charged Higgs, if you need it

    mln << "BLOCK" << "MASS"; massBlock.push_back(mln); mln.clear();
    mln << 25 << mh << "# Higgs mass h" ; massBlock.push_back(mln); mln.clear();
    mln << 35 << mH << "# Higgs mass H" ; massBlock.push_back(mln); mln.clear();
    mln << 36 << mA << "# Pseudoscalar Higgs mass A" ; massBlock.push_back(mln); mln.clear();
    slha.push_back(massBlock);

    // ALPHA
    double alpha = std::asin(mySpec.get(Par::Pole_Mixing, "h0", 2, 2));
    SLHAea::Block alphaBlock("ALPHA");
    SLHAea::Line alp;
    alp << "BLOCK" << "ALPHA"; alphaBlock.push_back(alp); alp.clear();
    alp << alpha << "# mixing in Higgs sector" ; alphaBlock.push_back(alp); alp.clear();
    slha.push_back(alphaBlock);


    /// MINPAR
    double tanb = mySpec.get(Par::dimensionless, "tanbeta");
    SLHAea::Block minparBlock("MINPAR");
    SLHAea::Line minp;
    minp << "BLOCK" << "MINPAR"; minparBlock.push_back(minp); minp.clear();
    minp << 3 << tanb << "# tanb" ; minparBlock.push_back(minp); minp.clear();
    slha.push_back(minparBlock);


    // SusHi reads gluino mass from EXTPAR[3] and other SUSY params from EXTPAR,
    // but GAMBIT writes M3 to MSOFT[3].  Build EXTPAR explicitly from the spectrum.
    {
        double M3_val  = mySpec.get(Par::mass1, "M3");
        double mu_val  = mySpec.get(Par::mass1, "Mu");
        double Yu33    = mySpec.get(Par::dimensionless, "Yu", 3, 3);
        double TYu33   = mySpec.get(Par::mass1, "TYu", 3, 3);
        double Yd33    = mySpec.get(Par::dimensionless, "Yd", 3, 3);
        double TYd33   = mySpec.get(Par::mass1, "TYd", 3, 3);
        double At_val  = (Yu33 != 0.0) ? TYu33 / Yu33 : 0.0;
        double Ab_val  = (Yd33 != 0.0) ? TYd33 / Yd33 : 0.0;
        double mQ3_val = std::sqrt(std::abs(mySpec.get(Par::mass2, "mq2", 3, 3)));
        double mU3_val = std::sqrt(std::abs(mySpec.get(Par::mass2, "mu2", 3, 3)));
        double mD3_val = std::sqrt(std::abs(mySpec.get(Par::mass2, "md2", 3, 3)));

        SLHAea::Block extparBlock("EXTPAR");
        SLHAea::Line lext;
        lext << "BLOCK" << "EXTPAR"; extparBlock.push_back(lext); lext.clear();
        lext << 3  << M3_val  << "# M3 gluino mass param";  extparBlock.push_back(lext); lext.clear();
        lext << 11 << At_val  << "# At stop trilinear";     extparBlock.push_back(lext); lext.clear();
        lext << 12 << Ab_val  << "# Ab sbottom trilinear";  extparBlock.push_back(lext); lext.clear();
        lext << 23 << mu_val  << "# mu parameter";          extparBlock.push_back(lext); lext.clear();
        lext << 43 << mQ3_val << "# mQ3 3rd-gen SQ mass";   extparBlock.push_back(lext); lext.clear();
        lext << 46 << mU3_val << "# mU3 3rd-gen SU mass";   extparBlock.push_back(lext); lext.clear();
        lext << 49 << mD3_val << "# mD3 3rd-gen SD mass";   extparBlock.push_back(lext); lext.clear();
        slha.push_back(extparBlock);
    }

    // Append Block SUSHI (model=1 MSSM, h=11, pp collider, 13 TeV, NNLO ggh+bbh)
    SLHAea::Block sushiBlock("SUSHI");
    SLHAea::Line lsh;
    lsh << "BLOCK" << "SUSHI"; sushiBlock.push_back(lsh); lsh.clear();
    lsh << 1 << 1        << "# model: 1=MSSM"; sushiBlock.push_back(lsh); lsh.clear();
    lsh << 2 << 11       << "# Higgs: 11=h (lightest CP-even)"; sushiBlock.push_back(lsh); lsh.clear();
    lsh << 3 << 0        << "# collider: 0=pp"; sushiBlock.push_back(lsh); lsh.clear();
    lsh << 4 << dopt("sqrts", 13000.0) << "# CoM energy [GeV]"; sushiBlock.push_back(lsh); lsh.clear();
    lsh << 5 << iopt("ggh_order", 2) << "# order ggh: 0=LO, 1=NLO, 2=NNLO"; sushiBlock.push_back(lsh); lsh.clear();
    lsh << 6 << iopt("bbh_order", 2) << "# order bbh: 0=LO, 1=NLO, 2=NNLO"; sushiBlock.push_back(lsh); lsh.clear();
    lsh << 7 << iopt("ew_ggh", 1) << "# EW for ggh: 0=off, 1=light quarks at NLO"; sushiBlock.push_back(lsh); lsh.clear();
    lsh << 19 << 0       << "# output: 0=silent"; sushiBlock.push_back(lsh); lsh.clear();
    slha.push_back(sushiBlock);

    // Append Block PDFSPEC (MMHT2014 sets — verified installed)
    SLHAea::Block pdfBlock("PDFSPEC");
    lsh << "BLOCK" << "PDFSPEC"; pdfBlock.push_back(lsh); lsh.clear();
    lsh << 1 << "MMHT2014lo68cl"   << "# LO PDF"; pdfBlock.push_back(lsh); lsh.clear();
    lsh << 2 << "MMHT2014nlo68cl"  << "# NLO PDF"; pdfBlock.push_back(lsh); lsh.clear();
    lsh << 3 << "MMHT2014nnlo68cl" << "# NNLO PDF"; pdfBlock.push_back(lsh); lsh.clear();
    lsh << 4 << "MMHT2014nnlo68cl" << "# N3LO PDF (unused at NNLO)"; pdfBlock.push_back(lsh); lsh.clear();
    lsh << 10 << iopt("pdf_member", 0) << "# PDF set member (0 = central)"; pdfBlock.push_back(lsh); lsh.clear();
    slha.push_back(pdfBlock);

    // Append Block RENORMBOT (bottom-quark Yukawa renormalization)
    // Entry 1: mb for bottom Yukawa (0=OS, 1=MSbar(mb), 2=MSbar(muR))
    // Entry 2: tan(beta) resummation of Y_b (0=no, 1=naive, 2=full)
    // Entry 3: Delta_b from FeynHiggs (0=no — we use GAMBIT spectrum directly)
    SLHAea::Block renormbotBlock("RENORMBOT");
    lsh << "BLOCK" << "RENORMBOT"; renormbotBlock.push_back(lsh); lsh.clear();
    lsh << 1 << iopt("renormbot_mb", 0) << "# mb for bottom Yukawa: 0=OS, 1=MSbar(mb), 2=MSbar(muR)"; renormbotBlock.push_back(lsh); lsh.clear();
    lsh << 2 << iopt("renormbot_tanb_resum", 1) << "# tanbeta resummation: 0=no, 1=naive, 2=full"; renormbotBlock.push_back(lsh); lsh.clear();
    lsh << 3 << 0 << "# Delta_b from FeynHiggs: 0=no"; renormbotBlock.push_back(lsh); lsh.clear();
    slha.push_back(renormbotBlock);

    // Append Block RENORMSBOT (sbottom sector renormalization)
    // Exactly one entry must be 2 (dep); recommended: mb=dep, Ab=OS, thetab=OS
    SLHAea::Block renormsbotBlock("RENORMSBOT");
    lsh << "BLOCK" << "RENORMSBOT"; renormsbotBlock.push_back(lsh); lsh.clear();
    lsh << 1 << 2 << "# mb: 2=dep (recommended)"; renormsbotBlock.push_back(lsh); lsh.clear();
    lsh << 2 << 0 << "# Ab: 0=OS (recommended)"; renormsbotBlock.push_back(lsh); lsh.clear();
    lsh << 3 << 0 << "# thetab: 0=OS (recommended)"; renormsbotBlock.push_back(lsh); lsh.clear();
    slha.push_back(renormsbotBlock);

    // Append Block FACTORS (multiplicative K-factors; 1.0 = use computed values)
    SLHAea::Block factorsBlock("FACTORS");
    lsh << "BLOCK" << "FACTORS"; factorsBlock.push_back(lsh); lsh.clear();
    lsh << 1 << dopt("kfactor_ggh", 1.0) << "# K-factor for ggh"; factorsBlock.push_back(lsh); lsh.clear();
    lsh << 2 << dopt("kfactor_bbh", 1.0) << "# K-factor for bbh"; factorsBlock.push_back(lsh); lsh.clear();
    slha.push_back(factorsBlock);

    // Append Block VEGAS (defaults: reduced calls for speed, ~2% accuracy; raise via yaml options for a slower, more precise calculation)
    SLHAea::Block vegasBlock("VEGAS");
    lsh << "BLOCK" << "VEGAS"; vegasBlock.push_back(lsh); lsh.clear();
    lsh << 1 << iopt("vegas_nlo_points", 5000) << "# NLO points"; vegasBlock.push_back(lsh); lsh.clear();
    lsh << 2 << iopt("vegas_nlo_iter", 5) << "# NLO iterations"; vegasBlock.push_back(lsh); lsh.clear();
    lsh << 4 << iopt("vegas_ggh_nnlo_points", 5000) << "# ggh@nnlo points (1st run)"; vegasBlock.push_back(lsh); lsh.clear();
    lsh << 5 << iopt("vegas_ggh_nnlo_iter", 5) << "# ggh@nnlo iterations (1st run)"; vegasBlock.push_back(lsh); lsh.clear();
    lsh << 14 << iopt("vegas_ggh_nnlo_points2", 2000) << "# ggh@nnlo points (2nd run)"; vegasBlock.push_back(lsh); lsh.clear();
    lsh << 15 << iopt("vegas_ggh_nnlo_iter2", 2) << "# ggh@nnlo iterations (2nd run)"; vegasBlock.push_back(lsh); lsh.clear();
    lsh << 7 << iopt("vegas_bbh_nnlo_points", 5000) << "# bbh@nnlo points (1st run)"; vegasBlock.push_back(lsh); lsh.clear();
    lsh << 8 << iopt("vegas_bbh_nnlo_iter", 5) << "# bbh@nnlo iterations (1st run)"; vegasBlock.push_back(lsh); lsh.clear();
    lsh << 17 << iopt("vegas_bbh_nnlo_points2", 2000) << "# bbh@nnlo points (2nd run)"; vegasBlock.push_back(lsh); lsh.clear();
    lsh << 18 << iopt("vegas_bbh_nnlo_iter2", 2) << "# bbh@nnlo iterations (2nd run)"; vegasBlock.push_back(lsh); lsh.clear();
    slha.push_back(vegasBlock);

    // Write SLHA to temp file
    {
        std::ofstream ofs(infile);
        if (!ofs) backend_error().raise(LOCAL_INFO, "Could not open SusHi temp file: " + infile);
        ofs << slha;
    }

    // Pass filename to SusHi's jfilein common block via char*1 array (no hidden length)
    char fn_buf[60];
    std::memset(fn_buf, ' ', 60);
    int fn_len = std::min((int)infile.size(), 60);
    std::memcpy(fn_buf, infile.c_str(), fn_len);
    gambit_sushi_setfile(fn_buf, fn_len);

    // Run ggh+bbh computation
    double ggh = 0.0, bbh = 0.0, ggh_e = 0.0, bbh_e = 0.0;
    gambit_sushi_compute(ggh, bbh, ggh_e, bbh_e);
    ggh_result = ggh;
    bbh_result = bbh;
    ggh_err = ggh_e;
    bbh_err = bbh_e;

    logger() << LogTags::debug
             << "SusHi 1.7.0: ggh = " << ggh << " +/- " << ggh_e << " pb, bbh = " << bbh
             << " +/- " << bbh_e << " pb" << EOM;

    std::remove(infile.c_str());
    std::string murdep = infile.substr(0, infile.size() - 5) + "_murdep";
    std::remove(murdep.c_str());
    }
}
END_BE_NAMESPACE

// Empty initialisation function -- required registration hook for the
// backend, but all real per-point work happens in SusHi_run_point (called
// directly from module functions) rather than here.
BE_INI_FUNCTION {}
END_BE_INI_FUNCTION
