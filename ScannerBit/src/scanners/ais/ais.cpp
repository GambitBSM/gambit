//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Base functions objects for use in GAMBIT.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Gregory Martinez
///           (gregory.david.martinez@gmail.com)
///  \date 2014 MAY
///
///  *********************************************

#ifdef WITH_MPI
#include "mpi.h"
#endif

#include "plugin_interface.hpp"
#include "scanner_plugin.hpp"
#include "ais.hpp"

scanner_plugin(badass, version(1, 0, 0))
{
    int plugin_main ()
    {
        like_ptr LogLike = get_purpose(get_inifile_value<std::string>("like", "LogLike"));
        int dim = get_dimension();

        Gambit::Options txt_options;
        txt_options.setValue("synchronised",false);
        get_printer().new_stream("txt", txt_options);
        set_resume_params.set_resume_mode(get_printer().resume_mode());

        int pdim = get_inifile_value<int>("projection_dimension", dim);
        AIS (LogLike, get_printer(),
                        set_resume_params,
                        dim,
                        //get_inifile_value<double>("kwalk_ratio", 0.9836),
                        pdim,
                        get_inifile_value<double>("gaussian_distance", 2.4),
                        get_inifile_value<double>("walk_distance", 2.5),
                        get_inifile_value<double>("traverse_distance", 6.0),
                        get_inifile_value<long long>("ran_seed", 0),
                        get_inifile_value<int>("points", 10000),
                        get_inifile_value<int>("jumps", 10),
                        get_inifile_value<std::vector<double>>("Bs", {0.0, 1.0})
            );

        return 0;
    }
}

void AIS(Gambit::Scanner::like_ptr LogLike,
           Gambit::Scanner::printer_interface &printer,
           Gambit::Scanner::resume_params_func set_resume_params,
           const int &ma,
           //const double &div,
           const int &proj,
           const double &din,
           const double &alim,
           const double &alimt,
           const long long &rand,
           int N,
           int M,
           std::vector<double> Bs)
{
    int rank = 0;

#ifdef WITH_MPI
    int numtasks = 1;
    MPI_Comm_size(MPI_COMM_WORLD,&numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    if (numtasks > 1)
    {
        AIS_MPI(LogLike, printer, set_resume_params, ma, proj, din, alim, alimt, rand, N, M, Bs);
        return;
    }
#endif

    std::vector<std::vector<double>> currentPts(N, std::vector<double>(ma)), nextPts(N, std::vector<double>(ma));
    std::vector<double> weights(N, 0.0);
    std::vector<double> chisq(N);
    std::vector<int> ranks(N);
    std::vector<double> aNext(ma);
    double ans, chisqnext, logWtTot = std::log(N);

    std::vector<unsigned long long int> ids(N);
    unsigned long long int next_id;

    Gambit::Scanner::printer *out_stream = printer.get_stream("txt");
    out_stream->reset();

    RandomPlane gDev(proj, ma, din, alim, alimt, rand);

    set_resume_params(currentPts, nextPts, chisq, weights, ids, ranks);

    Gambit::Scanner::assign_aux_numbers("weights");

    std::cout << "Initializing BadAss ... " << std::endl;
    for (int i = 0; i < N; i++)
    {
        for (auto &&temp : currentPts[i])
            temp = gDev.Doub();

        chisq[i] = -LogLike(currentPts[i]);
        ids[i] = LogLike->getPtID();
        ranks[i] = rank;
        std::cout << "point " << i << " complete."  << std::endl;
    }

    std::cout << "Initializing complete." << std::endl;

    nextPts = currentPts;

    for (int i = 1, endi = Bs.size(); i < endi; i++)
    {

        for (int j = 0; j < N; j++)
        {
            int jumps = 0;
            for (int k = 0; k < M; k++)
            {
                double u = gDev.Doub();
                int ii = 0;

                for (ii = 0; ii < N; ii++)
                {
                    u -= std::exp(weights[ii] - logWtTot);

                    if (u < 0.0)
                        break;
                }

                double ran = gDev.Doub();
                double logZ;

                if (ran < 0.5)
                {
                    logZ = gDev.WalkDev(&aNext[0], &nextPts[j][0], &currentPts[ii][0]);
                }
                else
                {
                    logZ = gDev.TransDev(&aNext[0], &nextPts[j][0], &currentPts[ii][0]);
                }

                if(!notUnit(aNext))
                {
                    chisqnext = -LogLike(aNext);
                    ans = Bs[i]*(chisqnext - chisq[j]) - logZ;
                    next_id = LogLike->getPtID();
                    if ((ans <= 0.0)||(gDev.ExpDev() >= ans))
                    {
                        ids[j] = next_id;
                        nextPts[j] = aNext;
                        chisq[j] = chisqnext;
                        ranks[j] = rank;
                        jumps++;
                    }
                    else
                    {
                        //out_stream->print(0, "weights", rank, next_id);
                    }
                }
            }

            std::cout << "point " << j << ":\n  jumps: " << jumps << "\n  acceptance ratio: " << double(jumps)/double(M) << std::endl;
        }

        std::cout << "B " << i << "completed." << std::endl;

        currentPts = nextPts;

        weights[0] += (Bs[i] - Bs[i-1])*chisq[0];
        logWtTot = weights[0];
        for (int j = 1; j < N; j++)
        {
            weights[j] = (Bs[i] - Bs[i-1])*chisq[j];
            logWtTot += std::log(1.0 + std::exp(weights[j] - logWtTot));
            //std::cout << logWtTot << "   " << weights[j] << std::endl; getchar();
        }
    }

    double Neff = 0.0, wttemp;
    for (int i = 0; i < N; i++)
    {
        //std::cout << std::exp(weights[i] - logWtTot) << "   " << ranks[i] << "   " << ids[i] << std::endl;
        wttemp = std::exp(weights[i] - logWtTot);
        Neff += wttemp*wttemp;
        out_stream->print(wttemp, "weights", ranks[i], ids[i]);
    }

    std::cout << "Neff = " << 1.0/Neff << std::endl;
}

#ifdef WITH_MPI
void AIS_MPI(Gambit::Scanner::like_ptr LogLike,
           Gambit::Scanner::printer_interface &printer,
           Gambit::Scanner::resume_params_func set_resume_params,
           const int &ma,
           //const double &div,
           const int &proj,
           const double &din,
           const double &alim,
           const double &alimt,
           const long long &rand,
           int N,
           int M,
           std::vector<double> Bs)
{
    std::vector<std::vector<double>> currentPts(N, std::vector<double>(ma)), nextPts(N, std::vector<double>(ma));
    std::vector<double> weights(N, 0.0);
    std::vector<double> chisq(N);
    std::vector<int> ranks(N);
    std::vector<double> aNext(ma);
    double ans, chisqnext, logWtTot = std::log(N);
    int rank, numtasks;
    MPI_Comm_size(MPI_COMM_WORLD,&numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    std::vector<unsigned long long int> ids(N);
    unsigned long long int next_id;

    Gambit::Scanner::printer *out_stream = printer.get_stream("txt");
    out_stream->reset();

    RandomPlane gDev(proj, ma, din, alim, alimt, rand);

    set_resume_params(currentPts, nextPts, chisq, weights, ids, ranks);

    Gambit::Scanner::assign_aux_numbers("weights");

    if (rank == 0)
    {
        std::cout << "Initializing BadAss ... " << std::endl;
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
                //std::cout << "point " << counter << " complete."  << std::endl;

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

        std::cout << "Initializing completed." << std::endl;
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

            for (auto &&temp : currentPts[i])
                temp = gDev.Doub();

            chisq[i] = -LogLike(currentPts[i]);
            ids[i] = LogLike->getPtID();
            //ranks[i] = rank;
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Bcast (&ranks[0], ranks.size(), MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < N; i++)
    {
        double r = ranks[i];
        MPI_Barrier(MPI_COMM_WORLD);
        MPI_Bcast (&chisq[i], 1, MPI_DOUBLE, r, MPI_COMM_WORLD);
        MPI_Bcast (&ids[i], 1, MPI_UNSIGNED_LONG_LONG, r, MPI_COMM_WORLD);
        MPI_Bcast (&currentPts[i][0], ma, MPI_DOUBLE, r, MPI_COMM_WORLD);
    }

    nextPts = currentPts;

    for (int i = 1, endi = Bs.size(); i < endi; i++)
    {
        if(rank == 0)
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
                    std::cout << "handing point " << counter << " to rank " << indices[rr]+1 << std::endl;
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
            for(;;)
            {
                int j, iii;
                MPI_Status stat;
                MPI_Request req;
                MPI_Isend(&iii, 1, MPI_INT, 0, rank, MPI_COMM_WORLD, &req);
                MPI_Recv(&j, 1, MPI_INT, 0, rank + numtasks, MPI_COMM_WORLD, &stat);
                //std::cout << "rank " << rank << "receiving point " << j << std::endl;
                if (j == N)
                    break;

                int jumps = 0;
                for (int k = 0; k < M; k++)
                {
                    double u = gDev.Doub();
                    int ii = 0;

                    for (ii = 0; ii < N; ii++)
                    {
                        u -= std::exp(weights[ii] - logWtTot);

                        if (u < 0.0)
                            break;
                    }

                    double ran = gDev.Doub();
                    double logZ;

                    if (ran < 0.5)
                    {
                        logZ = gDev.WalkDev(&aNext[0], &nextPts[j][0], &currentPts[ii][0]);
                    }
                    else
                    {
                        logZ = gDev.TransDev(&aNext[0], &nextPts[j][0], &currentPts[ii][0]);
                    }



                    if(!notUnit(aNext))
                    {
                        chisqnext = -LogLike(aNext);
                        ans = Bs[i]*(chisqnext - chisq[j]) - logZ;
                        next_id = LogLike->getPtID();
                        if ((ans <= 0.0)||(gDev.ExpDev() >= ans))
                        {
                            //out_stream->print(0, "weights", ranks[j], ids[j]);
                            ids[j] = next_id;
                            nextPts[j] = aNext;
                            chisq[j] = chisqnext;
                            //ranks[j] = rank;
                            jumps++;
                        }
                        else
                        {
                            //out_stream->print(0, "weights", rank, next_id);
                        }
                    }
                }

                std::cout << "point " << j << ":\n  jumps: " << jumps << "\n  acceptance ratio: " << double(jumps)/double(M) << std::endl;
            }
        }

        MPI_Barrier(MPI_COMM_WORLD);
        MPI_Bcast (&ranks[0], ranks.size(), MPI_INT, 0, MPI_COMM_WORLD);

        for (int i = 0; i < N; i++)
        {
            double r = ranks[i];
            MPI_Barrier(MPI_COMM_WORLD);
            MPI_Bcast (&chisq[i], 1, MPI_DOUBLE, r, MPI_COMM_WORLD);
            MPI_Bcast (&ids[i], 1, MPI_UNSIGNED_LONG_LONG, r, MPI_COMM_WORLD);
            MPI_Bcast (&currentPts[i][0], ma, MPI_DOUBLE, r, MPI_COMM_WORLD);
        }

        currentPts = nextPts;

        weights[0] += (Bs[i] - Bs[i-1])*chisq[0];
        logWtTot = weights[0];
        for (int j = 1; j < N; j++)
        {
            weights[j] = (Bs[i] - Bs[i-1])*chisq[j];
            logWtTot += std::log(1.0 + std::exp(weights[j] - logWtTot));
        }

        if (rank == 0)
            std::cout << "B " << i << "completed." << std::endl;
    }

    if (rank == 0)
    {
        double Neff = 0.0, wttemp;
        for (int i = 0; i < N; i++)
        {
            wttemp = std::exp(weights[i] - logWtTot);
            Neff += wttemp*wttemp;
            out_stream->print(wttemp, "weights", ranks[i], ids[i]);
        }

        std::cout << "Neff = " << 1.0/Neff << std::endl;
    }
}
#endif
