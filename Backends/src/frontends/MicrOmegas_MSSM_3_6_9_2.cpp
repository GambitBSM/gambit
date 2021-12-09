//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend for MicrOmegas MSSM 3.6.9.2 backend
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
/// \author Jonathan Cornell
/// \date 2015
///
///  *********************************************

#include "gambit/Backends/frontend_macros.hpp"
#include "gambit/Backends/frontends/MicrOmegas_MSSM_3_6_9_2.hpp"
#include "gambit/Elements/mssm_slhahelp.hpp"
#include "gambit/Utils/mpiwrapper.hpp"
#include "gambit/Utils/threadsafe_rng.hpp"
#include <unistd.h>

// Convenience functions (definitions)
BE_NAMESPACE
{
    double dNdE(double Ecm, double E, int inP, int outN)
    {
      // outN 0-5: gamma, e+, p-, nu_e, nu_mu, nu_tau
      // inP:  0 - 6: glu, d, u, s, c, b, t
      //       7 - 9: e, m, l
      //       10 - 15: Z, ZT, ZL, W, WT, WL
      double tab[250];  // NZ = 250
      // readSpectra() moved to initialization function.
      // Must be inside critical block if used here!
      // readSpectra();
      mInterp(Ecm/2, inP, outN, tab);
      return zInterp(log(E/Ecm*2), tab);
    }
}
END_BE_NAMESPACE

// Initialisation function (definition)
BE_INI_FUNCTION
{
    using namespace SLHAea;

    std::string filename;

    int rank = 0;
#ifdef WITH_MPI
    if(GMPI::Is_initialized())
    {
        GMPI::Comm comm;
        rank = comm.Get_rank();
    }
#endif

    int VZdecayOpt, VWdecayOpt; // 0=no 3 body final states
                                // 1=3 body final states in annihlations
                                // 2=3 body final states in co-annihilations
    VZdecayOpt = runOptions->getValueOrDef<int>(1, "VZdecay");
    VWdecayOpt = runOptions->getValueOrDef<int>(1, "VWdecay");
    *VZdecay = VZdecayOpt;
    *VWdecay = VWdecayOpt;

    logger() << LogTags::debug << "Initializing MicrOmegas MSSM with ";
    logger() << "VWdecay: " << VWdecay << " VZdecay: " << VZdecay << EOM;

    if (ModelInUse("MSSM63atQ") or ModelInUse("MSSM63atMGUT") or ModelInUse("MSSM63atQ_lightgravitino") or ModelInUse("MSSM63atMGUT_lightgravitino"))
    {
        // Write out an SLHA1 file, as required by Micromegas
        filename = "DarkBit_to_MicrOmegas_" + std::to_string(rank) + ".slha";
        const Spectrum& mySpec = *Dep::MSSM_spectrum;
        SLHAstruct mySLHA = mySpec.getSLHAea(1);
        std::ofstream ofs(filename);
        ofs << mySLHA;

        // Also write out decay block, if internal_decays option is set to false
        if(!(runOptions->getValueOrDef<bool>(false,"internal_decays")))
        {
            ofs << endl;
            const DecayTable& myDecays = *Dep::decay_rates;
            SLHAstruct decayBlock = myDecays.getSLHAea(1,true,*Dep::SLHA_pseudonyms);
            ofs << decayBlock;
        }
        ofs.close();

        // Convert filename string to char* type
        char* filename_c = new char[filename.size() + 1];
        std::copy(filename.begin(), filename.end(), filename_c);
        filename_c[filename.size()] = '\0';

        // Initialize micromegas mass spectrum from SLHA
        char cdmName[10];
        int error;

        unsigned int usec = 100000;  // 100 ms delay

        // Try 100 times before giving up
        for (int counter = 0; counter < 100; counter++)
        {
            usleep(usec);
            error = lesHinput(&filename_c[0]);
            if (error != 0)
                backend_warning().raise(LOCAL_INFO,
                        "Troubles loading SLHA file in MicrOmegas lesHinput: " + filename + "\n"
                        "Trying again."
                        );
            else
            {
                break;
            }
            if (counter == 99) backend_error().raise(LOCAL_INFO, "MicrOmegas function "
                    "lesHinput ("+filename+") returned error code: " + std::to_string(error));
        }

        error = sortOddParticles(&cdmName[0]);
        if (error != 0) backend_error().raise(LOCAL_INFO, "MicrOmegas function "
                "sortOddParticles ("+filename+") returned error code: " + std::to_string(error));

        if (remove(filename_c) != 0)
            backend_warning().raise(LOCAL_INFO, "Unable to delete SLHA file "+filename);

        // Delete the heap filename
        delete [] filename_c;
    }

    // Initialize yield tables for use in cascade decays
    readSpectra();

}
END_BE_INI_FUNCTION

