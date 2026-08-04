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

    inline constexpr double DEFAULT_PREDICT_TIMEOUT_SECONDS = 300.0;

    /// All per-capability emulator settings, gathered in one place rather than
    /// as separate maps keyed by the same capability name. Populated in two
    /// passes in gambit.cpp: 'ranks' during the EGG rank-exchange handshake at
    /// startup, then 'uncertainty'/'timeout' from each capability's
    /// Emulation.emulators.<capability> block once the yaml is parsed.
    ///
    /// Note on extensibility: 'uncertainty' here is just the raw configured
    /// threshold vector -- it does NOT decide accept/reject itself. Each
    /// emulatable capability already has its own pluggable accept/reject
    /// function (emulator_required_function_ptrs<TYPE>::CheckThreshold, set
    /// via DECLARE_EMULATOR_MODULE_FUNCTIONS / <Capability>_EmulatorCheckThreshold
    /// in the module source). The default implementation of that function
    /// just calls the shared checkThreshold() helper (emulator_functions.hpp),
    /// which reads .uncertainty from here -- but a user is free to write a
    /// completely custom CheckThreshold for their capability instead, reading
    /// .uncertainty directly (or ignoring it) as they see fit.
    struct CapabilitySettings
    {
        std::vector<int> ranks;         // EGG rank(s) handling this capability
        std::vector<double> uncertainty; // Emulation.emulators.<capability>.uncertainty
        double timeout = DEFAULT_PREDICT_TIMEOUT_SECONDS; // Emulation.emulators.<capability>.timeout
    };

    inline std::map<std::string, CapabilitySettings> capabilities;

    inline double emulatorUncertaintyThreshold;

#ifdef WITH_MPI
    inline MPI_Comm emuComm;
#endif
}


#endif // EMU_COMM_HPP

