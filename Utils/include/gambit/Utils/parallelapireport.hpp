//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  A simple utility for reporting parallelism. 
///
///  Extend as needed.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pascal Jahan Elahi
///          (pascal.elahi@pawsey.org.au)
///  \date 2022 Apr
///
///  *********************************************

// The WITH_MPI macro determines whether MPI is used or not.
// It is defined at compile time by cmake with -DWITH_MPI.
// The contents of this file are ignored if MPI is disabled.

#include <string>
#include "gambit/Utils/mpiwrapper.hpp"

namespace Gambit
{
    namespace GParallelAPIs
    {
        /// report parallel API and resources 
        //@{ 
        /// function that converts the mask of thread affinity to human readable string 
        void cpuset_to_cstr(cpu_set_t *mask, char *str);

        /// reports the parallelAPI 
        /// @param func function where called in code, useful to provide __func__ and __LINE
        /// @param line code line number where called
        /// @return string of MPI comm size and OpenMP version and max threads for given rank
        std::string ReportParallelAPI(std::string func, std::string line);


        /// reports binding of MPI comm world and each ranks thread affinity 
#ifdef WITH_MPI
        /// @param func function where called in code, useful to provide __func__ and __LINE
        /// @param line code line number where called
        /// @param comm GMPI communicator
        /// @return string of MPI comm rank and thread core affinity within a given communicator
        std::string ReportBinding(std::string func, std::string line, GMPI::Comm &comm);
#else 
        /// reports binding of MPI comm world and each ranks thread affinity within comm world
        /// @param func function where called in code, useful to provide __func__ and __LINE
        /// @param line code line number where called
        /// @return string of MPI comm rank and thread core affinity 
        std::string ReportBinding(std::string func, std::string line);
#endif
        /// reports thread affinity within a given scope, thus depends if called within OMP region 
        /// @param func function where called in code, useful to provide __func__ and __LINE
        /// @param line code line number where called
        /// @return string of thread core affinity 
        std::string ReportThreadAffinity(std::string func, std::string line);

#ifdef WITH_MPI
        /// reports thread affinity within a given scope, thus depends if called within OMP region, MPI aware
        /// @param func function where called in code, useful to provide __func__ and __LINE
        /// @param line code line number where called
        /// @param comm GMPI communicator
        /// @return string of MPI comm rank and thread core affinity 
        std::string MPIReportThreadAffinity(std::string func, std::string line, GMPI::Comm &comm);
#endif
        //@}
   }
}
/// \defgroup LogAffinity
/// Log thread affinity and parallelism either to std or an ostream
//@{
#define LogParallelAPI() Gambit::GParallelAPIs::ReportParallelAPI(std::string(__func__), std::to_string(__LINE__))
#define LogBinding() Gambit::GParallelAPIs::ReportBinding(std::string(__func__), std::to_string(__LINE__))
#define LogThreadAffinity() printf("%s \n", Gambit::GParallelAPIs::ReportThreadAffinity(std::string(__func__), std::to_string(__LINE__)).c_str());
#ifdef WITH_MPI
#define MPILogBinding(comm) Gambit::GParallelAPIs::ReportBinding(std::string(__func__), std::to_string(__LINE__), comm)
#define MPILogThreadAffinity(comm) printf("%s \n", Gambit::GParallelAPIs::MPIReportThreadAffinity(std::string(__func__), std::to_string(__LINE__), comm).c_str());
#endif
//@}
