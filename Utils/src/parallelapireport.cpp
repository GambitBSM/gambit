/*! \file thread_affinity_util.cpp
 *  \brief Get thread to core affinity
 */

//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Definitions for Gambit MPI C++ bindings.
///
///  NOTE! I just learned something unfortunate,
///  which is that all Isend's are supposed to be
///  matched by MPI_Wait calls at some point, to
///  ensure the operation is complete.
///  We are not doing this. Things seem to work
///  anyway, but it may explain some of the hangs
///  on MPI_Finalize.
///  I will fix the worst offenders of this asap,
///  but the rest may take longer.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ben Farmer
///          (b.farmer@imperial.ac.uk)
///  \date 2015 - 2019
///
///  *********************************************

#include <iostream>
#include <string>
#include <cstring>
#include <sched.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sysinfo.h>

#include <omp.h>

#include "gambit/Utils/parallelapireport.hpp"

namespace profiling_util {

    /*
    Code to facilitate core binding reporting
    borrowed from util-linux-2.13-pre7/schedutils/taskset.c
    */
    #ifdef __APPLE__

    static inline void
    CPU_ZERO(cpu_set_t *cs) { cs->count = 0; }

    static inline void
    CPU_SET(int num, cpu_set_t *cs) { cs->count |= (1 << num); }

    static inline int
    CPU_ISSET(int num, cpu_set_t *cs) { return (cs->count & (1 << num)); }

    int sched_getaffinity(pid_t pid, size_t cpu_size, cpu_set_t *cpu_set)
    {
        int32_t core_count = 0;
        size_t  len = sizeof(core_count);
        int ret = sysctlbyname(SYSCTL_CORE_COUNT, &core_count, &len, 0, 0);
        if (ret) {
            printf("error while get core count %d\n", ret);
            return -1;
        }
        cpu_set->count = 0;
        for (int i = 0; i < core_count; i++) cpu_set->count |= (1 << i);
        return 0;
    }
    #endif

    void cpuset_to_cstr(cpu_set_t *mask, char *str)
    {
        char *ptr = str;
        int i, j, entry_made = 0;
        for (i = 0; i < CPU_SETSIZE; i++) {
            if (CPU_ISSET(i, mask)) {
                int run = 0;
                entry_made = 1;
                for (j = i + 1; j < CPU_SETSIZE; j++) {
                    if (CPU_ISSET(j, mask)) run++;
                    else break;
                }
                if (!run) {
                    sprintf(ptr, "%d ", i);
                }
                else if (run == 1) {
                    sprintf(ptr, "%d,%d ", i, i + 1);
                    i++;
                } else {
                    sprintf(ptr, "%d-%d ", i, i + run);
                    i += run;
                }
                while (*ptr != 0) ptr++;
            }
        }
        ptr -= entry_made;
        ptr = nullptr;
    }
    inline std::string where_called(std::string func, std::string line)
    {
        return "@ "+func +" L" + line;
    }

    std::string ReportParallelAPI(std::string func, std::string line) 
    {
        std::string s;
        s = "Parallel API's " + where_called(func,line);
        s += "\n ======== \n";
#ifdef WITH_MPI
        int rank, size;
        MPI_Comm_size(MPI_COMM_WORLD, &size);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        s += "MPI Comm world size " + std::to_string(size);
        s += "\n";
#endif 
#ifdef _OPENMP 
        s += "OpenMP version " + std::to_string(_OPENMP);
        s += " with total number of threads = " + std::to_string(omp_get_max_threads());
        s += " with total number of allowed levels " + std::to_string(omp_get_max_active_levels());
#ifdef WITH_GPU
        int numdevices = omp_get_num_devices();
        int defaultdevice = omp_get_default_device();
        int ninfo[2];
        if (numdevices > 0) 
        {
            #pragma omp target map(tofrom:ninfo)
            {
                int team = omp_get_team_num();
                int tid = omp_get_thread_num();
                if (tid == 0 && team == 0)
                {
                    auto nteams = omp_get_num_teams();
                    auto nthreads = omp_get_num_threads();
                    ninfo[0] = nteams;
                    ninfo[1] = nthreads;
                }
            }
            s += "\n";
            s += "OpenMP Target : ";
            s += "Number of devices " + std::to_string(numdevices);
            s += "Default device " + std::to_string(defaultdevice);
            s += "Number of Compute Units " + std::to_string(ninfo[1]);
        }
#endif
        s += "\n";
#endif
#ifdef _HIP 
        int nDevices = 0;
        hipGetDeviceCount(&nDevices);
        s += "Running with HIP and found " + std::to_string(nDevices) + "\n";
        for (auto i=0;i<nDevices;i++)
        {
            hipDeviceProp_t prop;
            hipGetDeviceProperties(&prop, i);
            s += "HIP Device" + string(prop.name);
            s += " Compute Units " + to_string(prop.multiProcessorCount);
            s += " Max Work Group Size " + to_string(prop.warpSize);
            s += " Local Mem Size " + to_string(prop.sharedMemPerBlock);
            s += " Global Mem Size " + to_string(prop.totalGlobalMem);
            s += "\n";
        }
#endif 
#ifdef _CUDA
        int nDevices = 0;
        cudaGetDeviceCount(&nDevices);
        s += "Running with CUDA and found " + std::to_string(nDevices) + "\n";
        for (auto i=0;i<nDevices;i++)
        {
            cudaGetDeviceProperties(&prop, i);
            s += "Device" + string(prop.name);
            s += " Compute Units " + std::to_string(prop.multiProcessorCount);
            s += " Max Work Group Size " + std::to_string(prop.warpSize);
            s += " Local Mem Size " + std::to_string(prop.sharedMemPerBlock);
            s += " Global Mem Size " + std::to_string(prop.totalGlobalMem);
            s += "\n";
        }
#endif 
        return s;
    }

    std::string ReportBinding(
#ifdef WITH_MPI 
        std::string func, std::string line, Gambit::GMPI::Comm &comm
#else
        std::string func, std::string line
#endif
    )
    {
        std::string binding_report;
        binding_report = "Core Binding " + where_called(func,line);
        binding_report += "\n ======== \n";
        cpu_set_t coremask;
        char clbuf[7 * CPU_SETSIZE], hnbuf[64];
        memset(clbuf, 0, sizeof(clbuf));
        memset(hnbuf, 0, sizeof(hnbuf));
        (void)gethostname(hnbuf, sizeof(hnbuf));
        std::string result;
        result = "\t On node " + std::string(hnbuf) + " : ";
#ifdef WITH_MPI
        result += " MPI Comm "+ comm.Get_name() + " Rank " + std::to_string(comm.Get_rank()) + " : ";
#endif
#ifdef _OPENMP
        #pragma omp parallel \
        default(none) shared(binding_report, hnbuf) \
        private(coremask, clbuf) \
        firstprivate(result)
#endif
        {
            (void)sched_getaffinity(0, sizeof(coremask), &coremask);
            cpuset_to_cstr(&coremask, clbuf);
#ifdef _OPENMP
            auto thread = omp_get_thread_num();
            auto level = omp_get_level();
            result +=" OMP Thread " + std::to_string(thread) + " : ";
            result +=" at nested level " + std::to_string(level) + " : ";
#endif
            result += " Core affinity = " + std::string(clbuf) + " \n ";
#ifdef _OPENMP
            #pragma omp critical
#endif
            {
                binding_report += result;
            }
        }
        return binding_report;
    }

    /// return binding as called within openmp region 
    std::string ReportThreadAffinity(std::string func, std::string line)
    {
        std::string result;
        cpu_set_t coremask;
        char clbuf[7 * CPU_SETSIZE], hnbuf[64];
        memset(clbuf, 0, sizeof(clbuf));
        memset(hnbuf, 0, sizeof(hnbuf));
        (void)gethostname(hnbuf, sizeof(hnbuf));
        result = "Thread affinity report " + where_called(func,line);
        (void)sched_getaffinity(0, sizeof(coremask), &coremask);
        cpuset_to_cstr(&coremask, clbuf);
        int thread = 0, level = 1;
#ifdef _OPENMP
        thread = omp_get_thread_num();
        level = omp_get_level();
#endif
        result += " Thread " + std::to_string(thread);
        result +=" at level " + std::to_string(level) + " : ";
        result += " Core affinity = " + std::string(clbuf) + " ";
        result += " Core placement = " + std::to_string(sched_getcpu()) + " ";
        result += "\n";

        return result;
    }

    /// return binding as called within openmp region, MPI aware 
#ifdef WITH_MPI 
    std::string MPIReportThreadAffinity(std::string func, std::string line, Gambit::GMPI::Comm &comm)
    {
        std::string result;
        cpu_set_t coremask;
        char clbuf[7 * CPU_SETSIZE], hnbuf[64];
        memset(hnbuf, 0, sizeof(hnbuf));
        memset(clbuf, 0, sizeof(clbuf));
        (void)gethostname(hnbuf, sizeof(hnbuf));
        result = "Thread affinity report " + where_called(func,line);
        result += "::\t On node " + std::string(hnbuf) + " : ";
        result += " MPI Comm "+ comm.Get_name() + " Rank " + std::to_string(comm.Get_rank()) + " : ";
        (void)sched_getaffinity(0, sizeof(coremask), &coremask);
        cpuset_to_cstr(&coremask, clbuf);
        int thread = 0, level = 1;
#ifdef _OPENMP
        thread = omp_get_thread_num();
        level = omp_get_level();
#endif
        result += " Thread " + std::to_string(thread);
        result +=" at level " + std::to_string(level) + " : ";

        result += " Core affinity = " + std::string(clbuf) + " \n ";
        result += " Core placement = " + std::to_string(sched_getcpu()) + " ";
        result += "\n";

        return result;
    }
#endif

}