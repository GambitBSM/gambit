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
///  \date 2014 May
///
///  *********************************************
#ifndef TWALK_HPP
#define TWALK_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "scanner_plugin.hpp"
#include "random_tools.hpp"

namespace Gambit
{

    namespace Scanner
    {

        inline bool notUnit(const std::vector<double> &in)
        {
            for (auto it = in.begin(), end = in.end(); it != end; ++it)
            {
                if(*it < 0.0 || *it > 1.0 || *it == -(*it))
                {
                    return true;
                }
            }

            return false;
        }

        template <typename T>
        inline typename T::iterator::pointer c_ptr(T &it){return &(*it.begin());}

        inline std::vector<std::vector<double>> calcCov(const std::vector<std::vector<double>> &pts)
        {
            static size_t dim = pts[0].size();
            static size_t N = pts.size();

            std::vector<std::vector<double>> covar(dim, std::vector<double>(dim, 0.0));
            std::vector<double> avg(dim, 0.0);
            size_t i, j;

            for (auto it = pts.begin(), pt_end = pts.end(); it != pt_end; ++it)
            {
                for (i = 0; i < dim; i++)
                {
                    avg[i] += (*it)[i];
                    for (j = 0; j < dim; j++)
                    {
                        covar[i][j] += (*it)[i]*(*it)[j];
                    }
                }
            }

            for (i = 0; i < dim; i++)
            {
                for (j = 0; j < dim; j++)
                {
                    covar[i][j] = covar[i][j]/N - avg[i]*avg[j]/N/N;
                }
            }

            return covar;
        }

        inline std::vector<std::vector<double>> calcIndent (const std::vector<std::vector<double>> &pts)
        {
            static size_t dim = pts[0].size();

            std::vector<std::vector<double>> covar(dim, std::vector<double>(dim, 0.0));
            std::vector<double> hi(dim, 1.0), low(dim, 0.0);
            size_t i;

            for (auto it = pts.begin(), end = pts.end(); it != end; ++it)
            {
                for (i = 0; i < dim; i++)
                {
                    if (hi[i] < (*it)[i])
                    {
                        hi[i] = (*it)[i];
                    }

                    if (low[i] > (*it)[i])
                    {
                        low[i] = (*it)[i];
                    }
                }
            }

            for (i = 0; i < dim; i++)
            {
                covar[i][i] = (hi[i] - low[i])*(hi[i] - low[i])/12.0;
            }

            return covar;
        }

        class RanNumGen
        {
        private:
            std::vector<RandomPlane *> gDev;
            double div;

        public:
            RanNumGen(int proj, int ma, double din, double alim, double alimt, double div, unsigned long seed = 0) : div(div)
            {
                gDev.push_back(new RandomPlane(proj, ma, din, alim, alimt, seed++));
            }

            double Doub() {return gDev[0]->Doub();}

            double ExpDev() {return gDev[0]->ExpDev();}

        #ifdef WITH_MPI
            double Dev(std::vector<double> &aNext, std::vector<std::vector<double>> &a0, int t, int tt, int freePts, std::vector<int> &tints)
        #else
            double Dev(std::vector<double> &aNext, std::vector<std::vector<double>> &a0, int t, int tt)
        #endif
            {
                double ran = gDev[0]->Doub();
                double logZ;
                double b0 = div/2.0;
                double b1 = div;
                double b2 = (1.0 + div)/2.0;

                if (ran < b0)
                {
                    logZ = gDev[0]->WalkDev(&aNext[0], &a0[t][0], &a0[tt][0]);
                }
                else if (ran < b1)
                {
                    logZ = gDev[0]->TransDev(&aNext[0], &a0[t][0], &a0[tt][0]);
                }
                else if (ran < b2)
                {
                    std::vector<std::vector<double>> temp;
        #ifdef WITH_MPI
                    for (int i = 0, end = freePts; i < end; i++)
                    {
                        temp.push_back(std::vector<double>(a0[tints[i]]));
                    }
        #else
                    for (int i = 0, end = a0.size(); i < end; i++)
                    {
                        if (i != t)
                            temp.push_back(std::vector<double>(a0[i]));
                    }
        #endif
                    //if (!gDev[0]->EnterMat(calcCov(temp)))
                    if (true)
                    {
        #ifdef WITH_MPI
                        int ttt;
                        while(tints[ttt = freePts*gDev[0]->Doub()] == tt);

                        //double ct = gDev[0]->Max(&a0[tt][0], &a0[tints[ttt]][0]);
        #else
                        int ttt = (a0.size()-2)*gDev[0]->Doub();
                        if (t < tt)
                        {
                            if (ttt >= t) ttt++;
                            if (ttt >= tt) ttt++;
                        }
                        else
                        {
                            if (ttt >= tt) ttt++;
                            if (ttt >= t) ttt++;
                        }
                        //double ct = gDev[0]->Max(&a0[tt][0], &a0[ttt][0]);
                        //std::cout << ct << std::endl;
        #endif
                        //int ma = a0[0].size();
                        //std::vector<std::vector<double>> cov (ma, std::vector<double>(ma, 0.0));
                        //for (int i = 0; i < ma; i++)
                        //    cov[i][i] = ct*ct;
                        //gDev[0]->EnterMat(cov);
                        gDev[0]->HopBlow(&aNext[0], &a0[t][0], &a0[tt][0], &a0[ttt][0]);
                        //gDev[0]->EnterMat(calcIndent(temp));
                    }

                    //gDev[0]->MultiDev(&aNext[0], &a0[t][0]);
                    logZ = 0.0;
                }
                else
                {
                    std::vector<std::vector<double>> temp;
        #ifdef WITH_MPI
                    for (int i = 0, end = freePts; i < end; i++)
                    {
                        temp.push_back(std::vector<double>(a0[tints[i]]));
                    }
        #else
                    for (int i = 0, end = a0.size(); i < end; i++)
                    {
                        if (i != t)
                            temp.push_back(std::vector<double>(a0[i]));
                    }
        #endif
                    //if (!gDev[0]->EnterMat(calcCov(temp)))
                    if (true)
                    {
        #ifdef WITH_MPI
                        int ttt;
                        while(tints[ttt = freePts*gDev[0]->Doub()] == tt);

                        //double ct = gDev[0]->Max(&a0[tt][0], &a0[tints[ttt]][0]);
                        //std::cout << ct << "   " << t << "   " << tints[ttt] << std::endl;getchar();
        #else
                        int ttt = (a0.size()-2)*gDev[0]->Doub();
                        if (t < tt)
                        {
                            if (ttt >= t) ttt++;
                            if (ttt >= tt) ttt++;
                        }
                        else
                        {
                            if (ttt >= tt) ttt++;
                            if (ttt >= t) ttt++;
                        }
                        //double ct = gDev[0]->Max(&a0[tt][0], &a0[ttt][0]);
        #endif
                        //int ma = a0[0].size();
                        //std::vector<std::vector<double>> cov (ma, std::vector<double>(ma, 0.0));
                        //for (int i = 0; i < ma; i++)
                        //    cov[i][i] = ct*ct;
                        //gDev[0]->EnterMat(cov);
                        gDev[0]->HopBlow(&aNext[0], &a0[tt][0], &a0[tt][0], &a0[ttt][0]);
                        //gDev[0]->EnterMat(calcIndent(temp));
                    }

                    //gDev[0]->MultiDev(&aNext[0], &a0[tt][0]);
                    logZ = 0.0;
                }

                return logZ;
            }

            ~RanNumGen()
            {
                for (auto it = gDev.begin(), end = gDev.end(); it != end; ++it)
                {
                    delete *it;
                }
            }
        };

        // struct twalk_resume_info
        // {
        //     bool resume;
        //     std::string file_path;
        //     int N;
        //
        //     template <typename... T>
        //     inline void operator(int count, T&&... params)
        //     {
        //         if (resume)
        //         {
        //             ifstream in(file_path.c_str(), ios::binary);
        //         }
        //     }
        // }



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
                   const double &hrs_max);

        #endif

        /*
                double ran = gDev.Doub();
                if (ran < b0)
                {
                    logZ = gDev.WalkDev(c_ptr(aNext), c_ptr(a0[t]), c_ptr(a0[tt]));
                }
                else if (ran < b1)
                {
                    logZ = gDev.TransDev(c_ptr(aNext), c_ptr(a0[t]), c_ptr(a0[tt]));
                }
                else if (ran < b2)
                {
                    std::vector<std::vector<double>> temp = a0;
        #ifdef WITH_MPI
                    for (int i = 0, end = NThreads - numtasks; i < end; i++)
                    {
                        temp.push_back(a0[tints[i]]);
                    }
        #else
                    for (int i = 0, end = a0.size(); i < end; i++)
                    {
                        if (i != tt)
                            temp.push_back(a0[i]);
                    }
        #endif
                    if (!gDev.EnterMat(calcCov(temp)))
                    {
                        gDev.EnterMat(calcIndent(temp));
                    }

                    gDev.MultiDev(c_ptr(aNext), c_ptr(a0[t]));
                    logZ = 0.0;
                }
                else
                {
                    std::vector<std::vector<double>> temp;
        #ifdef WITH_MPI
                    for (int i = 0, end = NThreads - numtasks; i < end; i++)
                    {
                        temp.push_back(a0[tints[i]]);
                    }
        #else
                    for (int i = 0, end = a0.size(); i < end; i++)
                    {
                        if (i != tt)
                            temp.push_back(a0[i]);
                    }
        #endif
                    if (!gDev.EnterMat(calcCov(temp)))
                    {
                        gDev.EnterMat(calcIndent(temp));
                    }

                    gDev.MultiDev(c_ptr(aNext), c_ptr(a0[tt]));
                    logZ = 0.0;
                }*/
     }
}