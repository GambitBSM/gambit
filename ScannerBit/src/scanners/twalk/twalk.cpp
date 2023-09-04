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
///          (gregory.david.martinez@gmail.com)
///  \date 2014 May
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2018 June
///
///  *********************************************

#ifdef WITH_MPI
#include "gambit/Utils/begin_ignore_warnings_mpi.hpp"
#include "mpi.h"
#include "gambit/Utils/end_ignore_warnings.hpp"
#endif

#include "plugin_interface.hpp"
#include "scanner_plugin.hpp"
#include "twalk.hpp"

scanner_plugin(twalk, version(1, 0, 1))
{
    int plugin_main ()
    {
        like_ptr LogLike = get_purpose(get_inifile_value<std::string>("like", "LogLike"));

        // Do not allow GAMBIT's own likelihood calculator to directly shut down the scan.
        // Twalk will assume responsibility for this process, triggered externally by
        // the 'plugin_info.early_shutdown_in_progress()' function.
        LogLike->disable_external_shutdown();

        int dim = get_dimension();
        int numtasks;
        #ifdef WITH_MPI
            MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
        #else
            numtasks = 1;
        #endif

        Gambit::Options txt_options;
        txt_options.setValue("synchronised",false);
        get_printer().new_stream("txt", txt_options);
        set_resume_params.set_resume_mode(get_printer().resume_mode());

        int pdim = get_inifile_value<int>("projection_dimension", 4);
        TWalk(LogLike, get_printer(),
                        set_resume_params,
                        dim,
                        get_inifile_value<double>("kwalk_ratio", 0.9836),
                        pdim,
                        get_inifile_value<double>("gaussian_distance", 2.4),
                        get_inifile_value<double>("walk_distance", 2.5),
                        get_inifile_value<double>("traverse_distance", 6.0),
                        get_inifile_value<long long>("ran_seed", 0),
                        get_inifile_value<double>("sqrtR", 1.001),
                        get_inifile_value<int>("chain_number", 1 + pdim + numtasks),
                        get_inifile_value<bool>("hyper_grid", true),
                        get_inifile_value<int>("burn_in", 0),
                        get_inifile_value<int>("save_freq", 1000),
                        get_inifile_value<double>("timeout_mins", -1)
                );

        return 0;
    }
}


namespace Gambit
{
    namespace Scanner
    {
        struct point_info
        {
            int mult;
            int chain;
            int rank;
            unsigned long long int id;
        };

        void TWalk(Gambit::Scanner::like_ptr LogLike,
                   Gambit::Scanner::printer_interface &printer,
                   Gambit::Scanner::resume_params_func set_resume_params,
                   const int &dimension,
                   const double &div,
                   const int &proj,
                   const double &din,
                   const double &alim,
                   const double &alimt,
                   const long long &rand,
                   const double &sqrtR,
                   const int &NChains,
                   const bool &hyper_grid,
                   const int &burn_in,
                   const int &save_freq,
                   const double &mins_max)
        {

            const double massiveR = 1e100;

            std::vector<double> chisq(NChains);
            std::vector<double> aNext(dimension);
            std::vector<std::vector<double>> a0(NChains, std::vector<double>(dimension));
            double ans, chisqnext;
            std::vector<int> mult(NChains, 1);
            std::vector<int> totN(NChains, 0);
            std::vector<int> count(NChains, 1);
            int t, tt;
            int total = 1, ttotal = 0;

            std::vector<std::vector<double>> covT(NChains, std::vector<double>(dimension, 0.0));
            std::vector<std::vector<double>> avgT(NChains, std::vector<double>(dimension, 0.0));
            std::vector<double> W(dimension, 0.0);
            std::vector<double> avgTot(dimension, 0.0);
            bool converged = false;
            std::vector<unsigned long long int> ids(NChains);
            std::vector<int> ranks(NChains);
            unsigned long long int next_id;
            double Rsum = massiveR, Rmax = massiveR;
            bool resumed = false;

            unsigned int quit = 0; // signal for early shutdown

            std::chrono::time_point<std::chrono::system_clock> startTWalk;

            set_resume_params(chisq, a0, mult, totN, count, total, ttotal, covT, avgT, W, avgTot, ids, ranks, resumed);

            Gambit::Scanner::assign_aux_numbers("mult", "chain");

            int rank = set_resume_params.Rank();
            int numtasks = set_resume_params.NumTasks();

            #ifdef WITH_MPI
                std::vector<int> tints(NChains);
                for (int i = 0; i < NChains; i++) tints[i] = i;
                std::vector<int> talls(2*numtasks);
                set_resume_params(tints, talls);
            #endif

            std::ofstream temp_file_out;

            if (mins_max > 0 and rank == 0)
            {
                // Begin timing of TWalk run
                startTWalk = std::chrono::system_clock::now();
            }

            std::vector<RanNumGen *> gDev;
            for (int i = 0; i < NChains; i++)
            {
                gDev.push_back(new RanNumGen(proj, dimension, din, alim, alimt, div, rand));
            }

            // Try opening the temporary file for saving the mutliplicities etc.
            str filename = set_resume_params.get_temp_file_name("temp");
            temp_file_out.open(filename, std::ofstream::binary | std::ofstream::app);
            if (not temp_file_out.is_open()) scan_error().raise(LOCAL_INFO, "Problem opening temp file " + filename + " in TWalk!");

            if (resumed)
            {
                #ifdef WITH_MPI
                    for (int i = 0; i < numtasks; i++)
                    {
                        MPI_Barrier(MPI_COMM_WORLD);
                        MPI_Bcast (c_ptr(a0[talls[i]]), a0[talls[i]].size(), MPI_DOUBLE, i, MPI_COMM_WORLD);
                        MPI_Bcast (&chisq[talls[i]], 1, MPI_DOUBLE, i, MPI_COMM_WORLD);
                        MPI_Bcast (&mult[talls[i]], 1, MPI_INT, i, MPI_COMM_WORLD);
                        MPI_Bcast (&count[talls[i]], 1, MPI_INT, i, MPI_COMM_WORLD);
                        MPI_Bcast (&ranks[talls[i]], 1, MPI_INT, i, MPI_COMM_WORLD);
                        MPI_Bcast (&ids[talls[i]], 1, MPI_UNSIGNED_LONG_LONG, i, MPI_COMM_WORLD);
                    }
                #endif
            }
            else
            {
                resumed = true;
                for (t = 0; t < NChains; t++)
                {
                    if (rank == 0)
                    {
                        for (int j = 0; j < dimension; j++)
                            a0[t][j] = (gDev[t]->Doub());
                        chisq[t] = -LogLike(a0[t]);
                        quit = Gambit::Scanner::Plugins::plugin_info.early_shutdown_in_progress();
                        ids[t] = LogLike->getPtID();
                        ranks[t] = rank;
                    }
                    #ifdef WITH_MPI
                        MPI_Barrier(MPI_COMM_WORLD);
                        MPI_Bcast (c_ptr(a0[t]), a0[t].size(), MPI_DOUBLE, 0, MPI_COMM_WORLD);
                        MPI_Bcast (&quit, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD);
                    #endif
                    if(quit)
                    {
                       std::cout
                       #ifdef WITH_MPI
                         <<"Rank "<<rank<<": "
                       #endif
                       <<"Quit signal received during TWalk chain initialisation, aborting run" << std::endl;
                       break;
                    }
                }
            }

            #ifdef WITH_MPI
                MPI_Barrier(MPI_COMM_WORLD);
                MPI_Bcast (c_ptr(chisq), chisq.size(), MPI_DOUBLE, 0, MPI_COMM_WORLD);
                MPI_Bcast (c_ptr(ids), ids.size(), MPI_UNSIGNED_LONG_LONG, 0, MPI_COMM_WORLD);
                MPI_Bcast (c_ptr(ranks), ranks.size(), MPI_INT, 0, MPI_COMM_WORLD);
            #endif

            std::cout << "Metropolis Hastings/TWalk Algorithm Started"  << std::endl;

            while (not converged and not quit)
            {
                #ifdef WITH_MPI
                    if (rank == 0)
                    {
                        int j = NChains;
                        for(int i = 0; i < numtasks; i++)
                        {
                            int temp = int((j--)*gDev[0]->Doub());
                            talls[i] = tints[temp];
                            tints[temp] = tints[j];
                            tints[j] = talls[i];
                        }

                        for(int i = numtasks, end = talls.size(); i < end; i++)
                        {
                            talls[i] = tints[int(j*gDev[0]->Doub())];
                        }
                    }

                    MPI_Barrier(MPI_COMM_WORLD);
                    MPI_Bcast (c_ptr(talls), talls.size(), MPI_INT, 0, MPI_COMM_WORLD);
                    MPI_Bcast (c_ptr(tints), tints.size(), MPI_INT, 0, MPI_COMM_WORLD);

                    t = talls[rank];
                    tt = talls[rank + numtasks];
                    double logZ = gDev[t]->Dev(aNext, a0, t, tt, NChains - numtasks, tints);
                #else
                    t = int(NChains*gDev[0]->Doub());
                    tt = int((NChains - 1)*gDev[0]->Doub());
                    if (tt >= t) tt++;
                    double logZ = gDev[t]->Dev(aNext, a0, t, tt);
                #endif

                if(!(hyper_grid && notUnit(aNext)))
                {
                    chisqnext = -LogLike(aNext);
                    ans = chisqnext - chisq[t] - logZ;
                    next_id = LogLike->getPtID();
                    if ((ans <= 0.0)||(gDev[0]->ExpDev() >= ans))
                    {
                        //out_stream->print(mult[t], "mult", ranks[t], ids[t]);
                        //out_stream->print(t, "chain", ranks[t], ids[t]);
                        point_info info = {mult[t], t, ranks[t], ids[t]};
                        temp_file_out.write((char *)&info, sizeof(point_info));

                        ids[t] = next_id;
                        a0[t] = aNext;
                        chisq[t] = chisqnext;
                        ranks[t] = rank;
                        mult[t] = 0;
                        count[t]++;
                    }
                    else
                    {
                        //out_stream->print(0, "mult", rank, next_id);
                        //out_stream->print(-1, "chain", rank, next_id);
                        point_info info = {0, -1, rank, next_id};
                        temp_file_out.write((char *)&info, sizeof(point_info));
                    }
                }

                #ifdef WITH_MPI
                  for (int i = 0; i < numtasks; i++)
                  {
                      MPI_Barrier(MPI_COMM_WORLD);
                      MPI_Bcast (c_ptr(a0[talls[i]]), a0[talls[i]].size(), MPI_DOUBLE, i, MPI_COMM_WORLD);
                      MPI_Bcast (&chisq[talls[i]], 1, MPI_DOUBLE, i, MPI_COMM_WORLD);
                      MPI_Bcast (&mult[talls[i]], 1, MPI_INT, i, MPI_COMM_WORLD);
                      MPI_Bcast (&count[talls[i]], 1, MPI_INT, i, MPI_COMM_WORLD);
                      MPI_Bcast (&ranks[talls[i]], 1, MPI_INT, i, MPI_COMM_WORLD);
                      MPI_Bcast (&ids[talls[i]], 1, MPI_UNSIGNED_LONG_LONG, i, MPI_COMM_WORLD);
                  }
                #endif

                for (int l = 0; l < NChains; l++) mult[l]++;

                total++;

                if (total%save_freq == 0)
                {
                    set_resume_params.dump();
                    //out_stream->reset();
                }

                if (rank == 0)
                {
                    int cnt = 0;
                    for (auto it = count.begin(); it != count.end(); ++it)
                    {
                        cnt += *it;
                    }

                    if (total%NChains == 0 && cnt >= burn_in*NChains)
                    {
                        for (int i = 0; i < NChains; i++) for (int j = 0; j < dimension; j++)
                        {
                            if (ttotal == 0)
                            {
                                covT[i][j] = avgT[i][j] = avgTot[j] = W[j] = 0.0;
                            }
                            else
                            {
                                double davg = (a0[i][j]-avgT[i][j])/(ttotal+1.0);
                                double dcov = ttotal*davg*davg - covT[i][j]/(ttotal+1.0);
                                avgTot[j] += davg/NChains;
                                covT[i][j] += dcov;
                                avgT[i][j] += davg;
                                W[j] += dcov/NChains;
                            }
                        }
                        ttotal++;

                        // Loop over each dimension in the parameter space, and compute R for each.
                        // Trigger convergence only if R is below the requested threshold in every dimension.
                        Rsum = Rmax = 0.0;
                        converged = true;
                        for (int i = 0; i < dimension; i++)
                        {
                            double Bn = 0;
                            for (int ts = 0; ts < NChains; ts++)
                            {
                                Bn += (avgT[ts][i] - avgTot[i])*(avgT[ts][i] - avgTot[i]);
                            }
                            Bn /= double(NChains - 1);

                            double R = W[i] > 0.0 ? 1.0 + double(NChains + 1)*Bn  / (W[i] * double(NChains)) : massiveR;

                            Rsum += R;
                            Rmax = std::max(Rmax, R);

                            if (R < 1.0) scan_error().raise(LOCAL_INFO, "R < 1 in TWalk!");
                            if (R >= sqrtR*sqrtR) converged = false;
                        }
                    }

                    // Check if the requested maximum runtime has been reached.
                    if (mins_max > 0)
                    {
                        std::chrono::duration<double> runtime = std::chrono::system_clock::now() - startTWalk;
                        double runtime_ms = std::chrono::duration_cast<std::chrono::milliseconds>(runtime).count();
                        if (runtime_ms / 60e3 >= mins_max)
                        {
                           std::cout << "TWalk reached requested time limit of " << mins_max << " minutes.  Finalising run now." << std::endl;
                           converged = true;
                        }
                    }

                    // Print out progress to stdout
                    if (converged or cnt % 100 == 0)
                    {
                        std::cout << "Points = " << cnt  << " (" << cnt/double(NChains) << " per chain)" << std::endl;
                        std::cout << "\tAcceptance ratio = " << (double)cnt/(double)total/(double)numtasks << std::endl;
                        std::cout << "\tsqrt(R) (averaged over all dimensions) = " << sqrt(Rsum/dimension) << std::endl;
                        std::cout << "\tsqrt(R) (largest in any dimension) =     " << sqrt(Rmax) << std::endl;
                    }

                }

                quit = Gambit::Scanner::Plugins::plugin_info.early_shutdown_in_progress();
                #ifdef WITH_MPI
                    MPI_Barrier(MPI_COMM_WORLD);
                    MPI_Bcast (&converged, 1, MPI_C_BOOL, 0, MPI_COMM_WORLD);
                    MPI_Bcast (&quit, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD);
                #endif
                if(quit)
                {
                   std::cout
                   #ifdef WITH_MPI
                     <<"Rank "<<rank<<": "
                   #endif
                   <<"TWalk received quit signal! Terminating run." << std::endl;
                }
            }

            if(quit)
            {
                std::cout
                #ifdef WITH_MPI
                  <<"Rank "<<rank<<": "
                #endif
                  << "Writing resume data for TWalk" << std::endl;
                // This is a bit awkward, but if we just call .dump() with no argument then
                // ScannerBit will write resume data for ALL active plugins (which seems a
                // weird thing for TWalk to trigger) and also try to finalise the printer
                // (which will cause a crash when ScannerBit automatically tries to
                // finalise the printer later).
                // I would just add this dump stuff to scan.cpp, where the printer finalise
                // is called, but I think that is AFTER the plugins are destructed, so
                // I don't think that can work.
                // Doing this will dump JUST the TWalk resume data, though I had to
                // add this hacky get_name to the set_resume_params object in order to
                // get the name by which ScannerBit identifies the TWalk plugin.
                //Gambit::Scanner::Plugins::plugin_info.dump(set_resume_params.get_name());
                set_resume_params.dump(); // Better way
                // This works I think, but it still has problems. In particular,
                // it looks like you must resume with the same number of processes
                // that you started the run with, which is kind of crap.
            }

            for (auto &&gd : gDev) delete gd;

            temp_file_out.close();
            Gambit::Scanner::printer *out_stream = printer.get_stream("txt");
            std::ifstream temp_file_in(set_resume_params.get_temp_file_name("temp").c_str(), std::ifstream::binary);
            point_info info;
            int i = 0;
            while (temp_file_in.read((char *)&info, sizeof(point_info)))
            {i++;
                //std::cout<<"Twalk rank "<<rank<<" printing mult and chain for "<<i<<"th point of posterior chain (rank="<<info.rank<<", pointID="<<info.id<<")"<<std::endl;
                out_stream->print(info.mult, "mult", info.rank, info.id);
                out_stream->print(info.chain, "chain", info.rank, info.id);
            }
            out_stream->flush();

            std::cout << "TWalk has finished in process " << rank << "." << std::endl;

            return;
        }

    }

}
