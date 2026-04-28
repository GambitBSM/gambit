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
}
END_BE_INI_FUNCTION
