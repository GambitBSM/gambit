#ifndef INPUT_H
#define INPUT_H

#include <cmath>


static const double pi = M_PI;

static const double mbatmb = 4.18;
static const double mtatmt = 163.182;
static const double mcatmc = 1.27;
static const double muat2gev = 0.00216;
static const double mdat2gev = 0.00467;
static const double msat2gev = 0.093;
static const double me = 0.0005109989461;
static const double mmu = 0.1056583745;
static const double mtau = 1.77686;
static const double Mz = 91.1876;
static const double Mh = 125.1;
static const double Mw = 80.379;


static const double Qe = -1.;
static const double Qu = 2./3.;
static const double Qd = -1./3.;
static const double sw2 = 0.23121;
static const double cw2 = 1.-sw2;
static const double asMZ = 0.1181221;
static const double aMZ = 1/127.952;
static const double GF = 1.1663787E-5;
static const double vev = 1/sqrt(sqrt(2.)*GF);

/*class input
{
    public:
        input();
        virtual ~input();

    protected:
    private:

};
*/
#endif // INPUT_H
