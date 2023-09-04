//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  Toy MCMC sampler.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
//
///  \author Gregory Martinez
///          (gregory.david.martinez@gmail.com)
///  \date 2013 August
///
///  *********************************************

#ifdef WITH_MPI
#include "gambit/Utils/begin_ignore_warnings_mpi.hpp"
#include "mpi.h"
#include "gambit/Utils/end_ignore_warnings.hpp"
#endif

#include <vector>
#include <string>
#include <cmath>
#include <iostream>
#include <map>
#include <sstream>

#include "gambit/ScannerBit/scanner_plugin.hpp"
#include "gambit/Utils/threadsafe_rng.hpp"

scanner_plugin(toy_mcmc, version(1, 0, 0))
{
    void hiFunc(){std::cout << "This is the GAMBIT toy MCMC.  Don't run serious scans with this." << std::endl;}
    
    int N, ma, rank, numtasks;
    like_ptr LogLike;
    
    plugin_constructor
    {
        hiFunc();
        
        N = get_inifile_value<int>("point_number", 1000);
        LogLike = get_purpose(get_inifile_value<std::string>("like"));
        ma = get_dimension();
        
        if (N <= 0)
            scan_err << "You need to choose at least 2 points" << scan_end;
        
#ifdef WITH_MPI
        MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
#else
        numtasks = 1;
        rank = 0;
#endif
    }

    /*Define main module function.  Can input and return any types or type (exp. cannot return void).*/
    int plugin_main (void)
    {
        
        double ans, chisq, chisqnext;
        int mult = 1, count = 0, total = 1;
        unsigned long long int id;
        std::vector<double> a(ma);
        
        Gambit::Options txt_options;
        txt_options.setValue("synchronised",false);
        get_printer().new_stream("txt", txt_options);
        Gambit::Scanner::printer *out_stream = get_printer().get_stream("txt");
        out_stream->reset();

        for (auto &&val : a) 
            val = Gambit::Random::draw();

        std::cout << "Metropolis Hastings Algorthm Started" << std::endl; // << "tpoints = " << "\n\taccept ratio = " << std::endl;

        chisq = -LogLike(a);
        id = LogLike->getPtID();
#ifdef WITH_MPI
        if (numtasks > 1) 
        {
            int countsofar = 0, idnext;
            MPI_Status stat;
            std::vector<unsigned long long int> buffer_ids(N);
            std::vector<double> buffer_chisqs(N);
            
            do
            {
                int countsofarnext = N-count;
                if (countsofarnext < numtasks)
                    countsofarnext = numtasks;
                
                if (countsofarnext != countsofar)
                {
                    countsofar = countsofarnext;
                    buffer_ids.resize(countsofar);
                    buffer_chisqs.resize(countsofar);
                }
                
                total += countsofar;
                for (int i = rank, end = countsofar; i < end; i+=numtasks)
                {
                    for (auto &&val : a)
                    {
                        val = Gambit::Random::draw();
                    }

                    buffer_chisqs[i] = -LogLike(a);
                    buffer_ids[i] = LogLike->getPtID();
                }
                
                if (rank == 0)
                {
                    for (int i = 0, end = countsofar; i < end; i++)
                    {
                        int tag = i%numtasks;
                        if (tag != 0)
                        {
                            MPI_Recv (&buffer_ids[i], 1, MPI_UNSIGNED_LONG_LONG, tag, tag, MPI_COMM_WORLD, &stat);
                            MPI_Recv (&buffer_chisqs[i], 1, MPI_DOUBLE, tag, tag, MPI_COMM_WORLD, &stat);
                        }
                    }
                
                    for (auto &&iter : zip(buffer_ids, buffer_chisqs))
                    {
                        boost::tie(idnext, chisqnext) = iter;
                        ans = chisqnext - chisq;
                        if ((ans <= 0.0)||(-std::log(Gambit::Random::draw()) >= ans))
                        {
                            out_stream->print(mult, "mult", rank, id);
                            id = idnext;
                            chisq = chisqnext;
                            mult = 1;
                            count++;
                        }
                        else
                        {
                            mult++;
                        }
                    }
                    
                    std::cout << "points = " << count << "; accept ratio = " << (double)count/(double)total << std::endl;
                }
                else
                {
                    for (int i = rank, end = countsofar; i < end; i+=numtasks)
                    {
                        MPI_Send (&buffer_ids[i], 1, MPI_UNSIGNED_LONG_LONG, 0, rank, MPI_COMM_WORLD);
                        MPI_Send (&buffer_chisqs[i], 1, MPI_DOUBLE, 0, rank, MPI_COMM_WORLD);
                    }
                }
            }
            while(count < N); 
        } else
#endif
        do
        {
            total++;
            
            for (auto &&val : a)
            {
                val = Gambit::Random::draw();
            }

            chisqnext = -LogLike(a);
            
            ans = chisqnext - chisq;
            if ((ans <= 0.0)||(-std::log(Gambit::Random::draw()) >= ans))
            //if (true)
            {
                out_stream->print(mult, "mult", rank, id);
                id = LogLike->getPtID();
                chisq = chisqnext;
                mult = 1;
                count++;
                // cout << "\033[2A\tpoints = " << count << "\n\taccept ratio = " << "               \033[15D" << (double)count/(double)total << endl;
                std::cout << "points = " << count << "; accept ratio = " << (double)count/(double)total << std::endl;
            }
            else
            {
                mult++;
            }
        }
        while(count < N);

        return 0;
    }
}

