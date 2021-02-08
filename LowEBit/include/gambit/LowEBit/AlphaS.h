


#ifndef ALPHAS_H
#define ALPHAS_H
#include <cmath>
#include "QCD_beta.h"
#include "input.h"
#include <iostream>
#include <boost/numeric/odeint.hpp>


class AlphaS
{
    public:
        AlphaS(unsigned int nf, unsigned int loop);
        AlphaS();
        virtual ~AlphaS();
        double decouple_down_MSbar(double asatmu, double mu, double mh, unsigned int nf, unsigned int loop);
        double decouple_up_MSbar(double asatmu, double mu, double mh, unsigned int nf, unsigned int loop);
        double dalphasdmu(double mu, double as, unsigned int nf, unsigned int loop);
        void operator()(const double as, double &dasdmu, const double mu);
        double solve_rge_nf(double asatmu, double mu, double mu0, unsigned int nf, unsigned int loop);
        double run(double mu0, unsigned int nf, unsigned int loop);
    protected:
    private:
        unsigned int m_nf = 0;
        unsigned int m_loop = 0;

};

#endif // ALPHAS_H
