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
    static double stored_ggh = 0.0;
    static double stored_bbh = 0.0;

    double SusHi_ggh_xsec() { return stored_ggh; }
    double SusHi_bbh_xsec() { return stored_bbh; }
}
END_BE_NAMESPACE

// Initialisation function (definition)
BE_INI_FUNCTION
{
    using namespace SLHAea;

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
    const Spectrum& mySpec = *Dep::MSSM_spectrum;
    SLHAea::Coll slha = mySpec.getSLHAea(2);

    // SLHA2 puts mnu3(pole) = 0 at SMINPUTS[8], but SusHi reads that entry
    // as mc(mc) MSbar.  Overwrite it with the charm quark mass so SusHi
    // doesn't call runalpha(mu=0) and crash.
    {
        double mc_msbar = 1.28; // GeV (PDG; matches SMINPUTS[24] written by spectrum)
        auto& line8 = slha["SMINPUTS"][std::vector<int>{8}];
        line8.clear();
        line8 << 8 << mc_msbar << "# mc(mc)^MSbar [SusHi convention; SLHA2 entry 8 = mnu3]";
    }

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
    lsh << 4 << 13000.0  << "# CoM energy [GeV]"; sushiBlock.push_back(lsh); lsh.clear();
    lsh << 5 << 2        << "# order ggh: 2=NNLO"; sushiBlock.push_back(lsh); lsh.clear();
    lsh << 6 << 2        << "# order bbh: 2=NNLO"; sushiBlock.push_back(lsh); lsh.clear();
    lsh << 7 << 1        << "# EW for ggh: 1=light quarks at NLO"; sushiBlock.push_back(lsh); lsh.clear();
    lsh << 19 << 0       << "# output: 0=silent"; sushiBlock.push_back(lsh); lsh.clear();
    slha.push_back(sushiBlock);

    // Append Block PDFSPEC (MMHT2014 sets — verified installed)
    SLHAea::Block pdfBlock("PDFSPEC");
    lsh << "BLOCK" << "PDFSPEC"; pdfBlock.push_back(lsh); lsh.clear();
    lsh << 1 << "MMHT2014lo68cl"   << "# LO PDF"; pdfBlock.push_back(lsh); lsh.clear();
    lsh << 2 << "MMHT2014nlo68cl"  << "# NLO PDF"; pdfBlock.push_back(lsh); lsh.clear();
    lsh << 3 << "MMHT2014nnlo68cl" << "# NNLO PDF"; pdfBlock.push_back(lsh); lsh.clear();
    lsh << 4 << "MMHT2014nnlo68cl" << "# N3LO PDF (unused at NNLO)"; pdfBlock.push_back(lsh); lsh.clear();
    lsh << 10 << 0                 << "# set member 0 = central"; pdfBlock.push_back(lsh); lsh.clear();
    slha.push_back(pdfBlock);

    // Append Block RENORMBOT (bottom-quark Yukawa renormalization)
    // Entry 1: mb for bottom Yukawa (0=OS, 1=MSbar(mb), 2=MSbar(muR))
    // Entry 2: tan(beta) resummation of Y_b (0=no, 1=naive, 2=full)
    // Entry 3: Delta_b from FeynHiggs (0=no — we use GAMBIT spectrum directly)
    SLHAea::Block renormbotBlock("RENORMBOT");
    lsh << "BLOCK" << "RENORMBOT"; renormbotBlock.push_back(lsh); lsh.clear();
    lsh << 1 << 0 << "# mb for bottom Yukawa: 0=OS"; renormbotBlock.push_back(lsh); lsh.clear();
    lsh << 2 << 1 << "# tanbeta resummation: 1=naive"; renormbotBlock.push_back(lsh); lsh.clear();
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
    lsh << 1 << 1.0 << "# K-factor for ggh"; factorsBlock.push_back(lsh); lsh.clear();
    lsh << 2 << 1.0 << "# K-factor for bbh"; factorsBlock.push_back(lsh); lsh.clear();
    slha.push_back(factorsBlock);

    // Append Block VEGAS (reduced calls for speed; ~2% accuracy sufficient for emulator training)
    SLHAea::Block vegasBlock("VEGAS");
    lsh << "BLOCK" << "VEGAS"; vegasBlock.push_back(lsh); lsh.clear();
    lsh << 1  << 5000  << "# NLO points"; vegasBlock.push_back(lsh); lsh.clear();
    lsh << 2  << 5     << "# NLO iterations"; vegasBlock.push_back(lsh); lsh.clear();
    lsh << 4  << 5000  << "# ggh@nnlo points (1st run)"; vegasBlock.push_back(lsh); lsh.clear();
    lsh << 5  << 5     << "# ggh@nnlo iterations (1st run)"; vegasBlock.push_back(lsh); lsh.clear();
    lsh << 14 << 2000  << "# ggh@nnlo points (2nd run)"; vegasBlock.push_back(lsh); lsh.clear();
    lsh << 15 << 2     << "# ggh@nnlo iterations (2nd run)"; vegasBlock.push_back(lsh); lsh.clear();
    lsh << 7  << 5000  << "# bbh@nnlo points (1st run)"; vegasBlock.push_back(lsh); lsh.clear();
    lsh << 8  << 5     << "# bbh@nnlo iterations (1st run)"; vegasBlock.push_back(lsh); lsh.clear();
    lsh << 17 << 2000  << "# bbh@nnlo points (2nd run)"; vegasBlock.push_back(lsh); lsh.clear();
    lsh << 18 << 2     << "# bbh@nnlo iterations (2nd run)"; vegasBlock.push_back(lsh); lsh.clear();
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
    double ggh = 0.0, bbh = 0.0;
    gambit_sushi_compute(ggh, bbh);
    stored_ggh = ggh;
    stored_bbh = bbh;

    logger() << LogTags::debug
             << "SusHi 1.7.0: ggh = " << ggh << " pb, bbh = " << bbh << " pb" << EOM;

    std::remove(infile.c_str());
    std::string murdep = infile.substr(0, infile.size() - 5) + "_murdep";
    std::remove(murdep.c_str());
}
END_BE_INI_FUNCTION
