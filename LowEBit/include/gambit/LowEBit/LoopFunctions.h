#ifndef LOOPFUNCTIONS_H
#define LOOPFUNCTIONS_H

#include <cmath>

class LoopFunctions
{
    public:
        LoopFunctions();
        virtual ~LoopFunctions();
        //functions taken from draft;
        double Clausens2(double th);
        double PolyLog(double xi);
        double DTPHI(double z);
        double C3q(char q, double muW, double Lambda, double Ctil_e, double Ctil_mu, double Ctil_tau, double Ctil_u, double Ctil_d, double Ctil_s, double Ctil_c, double Ctil_b, double Ctil_t);
        double C3e(char e, double muW, double Lambda, double Ctil_e, double Ctil_mu, double Ctil_tau, double Ctil_u, double Ctil_d, double Ctil_s, double Ctil_c, double Ctil_b, double Ctil_t);
        double C4q(char q, double muW, double Lambda, double Ctil_u, double Ctil_d, double Ctil_s, double Ctil_t);
        double Cw(double Lambda, double Ctil_t);
        double C1qqp(char q, char qp, double Lambda, double Ctil_u, double Ctil_d, double Ctil_s, double Ctil_c, double Ctil_b);
        double C1q(char q, double Lambda, double Ctil_u, double Ctil_d, double Ctil_s, double Ctil_c, double Ctil_b);
	double get_meatmz();
	double get_mmuatmz();
	double get_mtauatmz();
	double get_muatmz();
	double get_mdatmz();
	double get_msatmz();
	double get_mcatmz();
	double get_mbatmz();
	double get_mtatmz();
    protected:
    private:
        //values at mu_W = Mz;
        double pi = 3.14159;
        double Qe = -1.;
        double Qu = 2./3.;
        double Qd = -1./3.;
        double sw2 = 0.23121;
        double cw2 = 1.-sw2;
        double me = 0.0005109989461;
        double mmu = 0.1056583745;
        double mtau = 1.77686;
        double mu = 0.00138818972836;
        double md = 0.00300132208045;
        double ms = 0.0597702783098;
        double mc = 0.750440223951;
        double mb = 3.00584732405;
        double mt = 166.394;
        double Mh = 125.1;
        double Mz = 91.1876;
        double Mw = 80.379;
        double xth = pow(mt/Mh,2);
        double xtz = pow(mt/Mz,2);
        double xbh = pow(mb/Mh,2);
        double xbz = pow(mb/Mz,2);
        double xch = pow(mc/Mh,2);
        double xcz = pow(mc/Mz,2);
        double xtauh = pow(mtau/Mh,2);
        double xtauz = pow(mtau/Mz,2);
        double xmuh = pow(mmu/Mh,2);
        double xmuz = pow(mmu/Mz,2);
        double xeh = pow(me/Mh,2);
        double xez = pow(me/Mz,2);
        double xhz = pow(Mh/Mz,2);
        double asMZ = 0.1179;
        double aMZ = 1/127.952;
        double GF = 1.1663787E-5;
        double vev = 1/sqrt(sqrt(2)*GF);
};

#endif // LOOPFUNCTIONS_H
