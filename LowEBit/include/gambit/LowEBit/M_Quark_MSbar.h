#ifndef M_QUARK_MSBAR_H
#define M_QUARK_MSBAR_H

#include "QCD_gamma.h"
#include "AlphaS.h"
#include "input.h"
#include <cmath>



class M_Quark_MSbar
{
    public:
        M_Quark_MSbar();
        virtual ~M_Quark_MSbar();
        double decouple_down_MSbar(double mlatmu, double mu, double mh, double asatmu, unsigned int loop);
        double decouple_up_MSbar(double mlatmu, double mu, double mh, double asatmu, unsigned int loop);
        double dmqdmu(double mu, double mq, double asatmu, unsigned int nf, unsigned int loop);
        void operator()(const double mq, double &dmqdmu, const double mu);
        double solve_rge_nf(double mqatmu, double mu, double mu0, unsigned int nf, unsigned int loop);
        double run(char flavour, double mu0, unsigned int nf, unsigned int loop);
    protected:
    private:
        unsigned int m_nf;
        unsigned int m_loop;
};

#endif // M_QUARK_MSBAR_H
