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

    inline double emulatorUncertaintyThreshold;

#ifdef WITH_MPI
    inline MPI_Comm emuComm;
#endif
}


#endif // EMU_COMM_HPP

