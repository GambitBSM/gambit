#ifndef __MPI_DISTRIBUTE__
#define __MPI_DISTRIBUTE__

#ifdef WITH_MPI
#include "mpi.h"
#endif

#include <vector>

/*!
 * Distributes commands over mpi processes.  The 0th processes schedules and sends
 * tasks to other processes to run.  To distribute N tasks (i = 0...N-1) over mpi processes:
 * 
 * mpi_distribute(i, N)
 * {
 *      //task that operates on i-th task
 * };
 * 
 * mpi_distribute returns a vector that maps the task number to the assign mpi rank:
 * 
 * std::vector<int> ret;
 * ret = mpi_distribute(i, N)
 * {
 *      //task that operates on i-th task
 * };
 * 
 * where ret[task_number] = rank
 * 
 * Also, optionally can specify the mpi process number and rank:
 * 
 * mpi_distribute(i, N, rank, process_number)
 * {
 *      //task that operates on i-th task
 * };
 * 
 * */
#define mpi_distribute(threadnum, ...) \
::Gambit::Scanner::mpi_dist_internal::mpi_dist(__VA_ARGS__) = [&](int threadnum) \

namespace Gambit
{
    
    namespace Scanner
    {
        
        namespace mpi_dist_internal
        {
            
            struct mpi_dist
            {
                int N;
                int rank;
                int numtasks;
                
                mpi_dist(int N) : N(N), rank(0), numtasks(1)
                {
#ifdef WITH_MPI
                    int rankin, numin;
                    MPI_Comm_rank(MPI_COMM_WORLD, &rankin);
                    MPI_Comm_size(MPI_COMM_WORLD, &numin);
                    rank = rankin;
                    numtasks = numin;
#endif
                }
                
                mpi_dist(int N, int rank, int numtasks) : N(N), rank(rank), numtasks(numtasks) {}
                
                template<typename T>
                inline std::vector<int> operator = (T&& func)
                {
                    std::vector<int> ranks(N, 0);
                    
                    if (numtasks == 1)
                    {
                        for (int i = 0; i < N; i++)
                        {
                            func(i);
                        }
                        
                        return ranks;
                    }
#ifdef WITH_MPI
                    if (rank == 0)
                    {
                        int incount = numtasks-1;
                        std::vector<int> buf(incount);
                        std::vector<MPI_Request> reqs(incount);
                        std::vector<int> indices(incount);
                        std::vector<MPI_Status> stats(incount);
                        int outcount;
                        int counter = 0, cont = 1;
                        
                        for (int r = 1; r < numtasks; r++)
                        {
                            MPI_Irecv(&buf[r-1], 1, MPI_INT, r, r, MPI_COMM_WORLD, &reqs[r-1]);
                        }
                        
                        do
                        {
                            MPI_Waitsome(incount, &reqs[0], &outcount, &indices[0], &stats[0]);
                            for (int rr = 0; rr < outcount; rr++)
                            {
                                int r = indices[rr]+1;
                                MPI_Send(&counter, 1, MPI_INT, r, r+numtasks, MPI_COMM_WORLD);
                                MPI_Irecv(&buf[r-1], 1, MPI_INT, r, r, MPI_COMM_WORLD, &reqs[r-1]);
                                
                                if (counter != N)
                                {
                                    ranks[counter++] = r;
                                }
                                else
                                    cont++;
                            }
                        }
                        while(cont < numtasks);
                        
                        for (int r = 1; r < numtasks; r++)
                        {
                            MPI_Cancel(&reqs[r-1]);
                        }
                    }
                    else
                    {
                        int i, iii = 0;
                        MPI_Status stat;
                        
                        for(;;)
                        {
                            MPI_Request req;
                            MPI_Isend(&iii, 1, MPI_INT, 0, rank, MPI_COMM_WORLD, &req);
                            MPI_Recv(&i, 1, MPI_INT, 0, rank + numtasks, MPI_COMM_WORLD, &stat);
                            
                            if (i == N)
                                break;
                            
                            func(i);
                        }
                    }
                    
                    MPI_Barrier(MPI_COMM_WORLD);
                    MPI_Bcast (&ranks[0], ranks.size(), MPI_INT, 0, MPI_COMM_WORLD);
#endif
                    return ranks;
                }
            };
            
        }
        
    }
    
}

#endif
