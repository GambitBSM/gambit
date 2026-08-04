#ifndef __gambit_emu_map_hpp__
#define __gambit_emu_map_hpp__

#include <map>
#include <vector>
#include <string>
#ifdef WITH_MPI
#include <mpi.h>
#include "gambit/Utils/mpiwrapper.hpp"
#endif

using namespace Gambit;
// namespace GMPI { class Comm; }

namespace EmulatorMap
{

    inline bool useEmulator;
    inline bool emulateLikelihood;
    inline std::map<std::string, std::vector<int>> mapping_ranks;
    inline std::map<std::string, std::vector<double>> mapping_uncertainty;
    // Per-capability timeout (seconds) to wait for a prediction reply before
    // concluding the EGG rank handling it has died/stalled. Populated from
    // each capability's Emulation.emulators.<capability>.timeout in the YAML,
    // falling back to DEFAULT_PREDICT_TIMEOUT_SECONDS when not set -- a slow
    // capability (e.g. one with a long queue of points ahead of it) should
    // set this explicitly rather than relying on the default.
    inline std::map<std::string, double> mapping_timeout;
    inline constexpr double DEFAULT_PREDICT_TIMEOUT_SECONDS = 300.0;

    inline double emulatorUncertaintyThreshold;

#ifdef WITH_MPI
    inline MPI_Comm emuComm;
#endif
}


#endif // EMU_COMM_HPP

