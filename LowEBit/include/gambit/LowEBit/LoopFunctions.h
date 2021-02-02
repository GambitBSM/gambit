#ifndef LOOPFUNCTIONS_H
#define LOOPFUNCTIONS_H

#include "input.h"
#include <gsl/gsl_integration.h>
#include "M_Quark_MSbar.h"
#include "AlphaS.h"

class LoopFunctions
{
    public:
        LoopFunctions();
        virtual ~LoopFunctions();
	double* get_masses2GeV();
	double* get_massesMh();
        //functions taken from draft;
        static double Clausens2(double th, void* params);
        static double PolyLog(double xi, void* params);
        double DTPHI(double z);
        double C3q(char q, double muW, double Lambda, double Ctil_e, double Ctil_mu, double Ctil_tau, double Ctil_u, double Ctil_d, double Ctil_s, double Ctil_c, double Ctil_b, double Ctil_t);
        double C3e(char e, double muW, double Lambda, double Ctil_e, double Ctil_mu, double Ctil_tau, double Ctil_u, double Ctil_d, double Ctil_s, double Ctil_c, double Ctil_b, double Ctil_t);
        double C4q(char q, double muW, double Lambda, double Ctil_u, double Ctil_d, double Ctil_s, double Ctil_t);
        double Cw(double Lambda, double Ctil_t);
        double C1qqp(char q, char qp, double Lambda, double Ctil_u, double Ctil_d, double Ctil_s, double Ctil_c, double Ctil_b);
        double C1q(char q, double Lambda, double Ctil_u, double Ctil_d, double Ctil_s, double Ctil_c, double Ctil_b);
    protected:
    private:
        //quark masses at Mh with one loop QCD running in MSbar scheme, set in constructor
        double mu;
        double md;
        double ms;
        double mc;
        double mb;
        double mt;
        double as51lMh;

        double xth;
        double xtz;
        double xbh;
        double xbz;
        double xch;
        double xcz;
        double xtauh;
        double xtauz;
        double xmuh;
        double xmuz;
        double xeh;
        double xez;
        double xhz;
};

#endif // LOOPFUNCTIONS_H
