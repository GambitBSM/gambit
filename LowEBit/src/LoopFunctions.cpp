#include "gambit/LowEBit/LoopFunctions.h"

LoopFunctions::LoopFunctions()
{
    //ctor
}

LoopFunctions::~LoopFunctions()
{
    //dtor
}

double LoopFunctions::Clausens2(double th){
    double res = 0;
    double step = 0.000001;
    double i = step;
    while(i<=th){
        res += log(std::abs(2*sin(i/2.)))*step;
        i+=step;
    }
    return -res;
}

double LoopFunctions::PolyLog(double xi){
    double res = 0.0;
    double step = 0.000001;
    double i = step;
    while(i<=xi){
        res += log(1-i)/i*step;
        i+=step;
    }
    return -res;
}

double LoopFunctions::DTPHI(double z){
    double res = 0.0;
    if(z<1){
        res = 4*sqrt(z/(1-z)) * Clausens2(2*asin(sqrt(z)));
    }
    else{
        double xi = 1/2.*(1-sqrt((z-1)/z));
        res = sqrt(z/(z-1)) * (-4*PolyLog(xi) + 2*pow(log(xi),2) - pow(log(4*z),2) + pow(3.14159,2)/3 );
    }
    return res;
}

double LoopFunctions::C3q(char q, double muW, double Lambda, double Ctil_e, double Ctil_mu, double Ctil_tau, double Ctil_u, double Ctil_d, double Ctil_s, double Ctil_c, double Ctil_b, double Ctil_t){
    double Qq = (q=='u') ? Qu : Qd;
    int pq = (q=='u') ? -1 : +1;
    double mq = 0.; double Ctilq = 0.;
    if (q=='u') {mq = mu; Ctilq = Ctil_u;}
    if (q=='d') {mq = md; Ctilq = Ctil_d;}
    if (q=='s') {mq = ms; Ctilq = Ctil_s;}
    double res = std::pow(vev,3)/(std::sqrt(2) * std::pow(Lambda,2))*(
         + 3.*aMZ*asMZ/(8.*pi*pi) * 1/mt * Ctil_t * (Qu*Qu*xth*DTPHI(1./(4*xth)) + Qu/(16.*Qq*cw2*sw2)*(1+pq*4*sw2*Qq)*(1-4*sw2*Qu)*xth*xtz/(xtz-xth)*(DTPHI(1/(4*xtz)) - DTPHI(1/(4*xth))))
         + aMZ*asMZ/(6*pi*pi) * 1/mq * Ctilq * (xth*((1-2*xth)*DTPHI(1/(4*xth)) + 2*(2+std::log(xth))) + Qu/(16*Qq*cw2*sw2)*(1+pq*4*sw2*Qq)*(1-4*sw2*Qu)*xth*xtz/(xtz-xth)*((1-2*xth)*DTPHI(1/(4*xth)) - 2*std::log(xhz) - (1-2*xtz)*DTPHI(1/(4*xtz))))
         + 3*aMZ*asMZ/(8*pi*pi) * 1/mb * Ctil_b * (Qd*Qd*xbh*(std::pow(std::log(xbh),2) + pi*pi/3.) + Qd/(16*Qq*cw2*sw2)*(1+pq*4*sw2*Qq)*(1+4*sw2*Qd)*xbh*xbz/(xbz-xbh)*(std::pow(std::log(xbh),2) - std::pow(std::log(xbz),2)))
         + 3*aMZ*asMZ/(8*pi*pi) * 1/mc * Ctil_c * (Qu*Qu*xch*(std::pow(std::log(xch),2) + pi*pi/3.) + Qu/(16*Qq*cw2*sw2)*(1+pq*4*sw2*Qq)*(1-4*sw2*Qu)*xch*xcz/(xcz-xch)*(std::pow(std::log(xch),2) - std::pow(std::log(xcz),2)))
         + 1*aMZ*asMZ/(8*pi*pi) * 1/mtau * Ctil_tau * (xtauh*(std::pow(std::log(xtauh),2) + pi*pi/3.) - 1/(16*Qq*cw2*sw2)*(1+pq*4*sw2*Qq)*(1-4*sw2)*xtauh*xtauz/(xtauz-xtauh)*(std::pow(std::log(xtauh),2) - std::pow(std::log(xtauz),2)))
         + 1*aMZ*asMZ/(8*pi*pi) * 1/mmu * Ctil_mu * (xmuh*(std::pow(std::log(xmuh),2) + pi*pi/3.) - 1/(16*Qq*cw2*sw2)*(1+pq*4*sw2*Qq)*(1-4*sw2)*xmuh*xmuz/(xmuz-xmuh)*(std::pow(std::log(xmuh),2) - std::pow(std::log(xmuz),2)))
         + 1*aMZ*asMZ/(8*pi*pi) * 1/me * Ctil_e * (xeh*(std::pow(std::log(xeh),2) + pi*pi/3.) - 1/(16*Qq*cw2*sw2)*(1+pq*4*sw2*Qq)*(1-4*sw2)*xeh*xez/(xez-xeh)*(std::pow(std::log(xeh),2) - std::pow(std::log(xez),2)))
         - aMZ*asMZ/(32*pi*pi) * 1/mq * (4*Qq - pq)/(2*Qq*cw2) * Ctilq * std::log(std::pow(muW/Lambda,2))
        );
    return res;
}

double LoopFunctions::C3e(char l, double muW, double Lambda, double Ctil_e, double Ctil_mu, double Ctil_tau, double Ctil_u, double Ctil_d, double Ctil_s, double Ctil_c, double Ctil_b, double Ctil_t){
    double pq = +1; double Qq = -1;
    double ml = 0.; double Ctilq = 0.;
    if (l=='e') ml = me; double Ctill = Ctil_e;
    double res = 1/(4*pi)*std::pow(vev,3)/(std::sqrt(2) * std::pow(Lambda,2))*(
         + 3.*aMZ/(8.*pi*pi*pi) * 1/mt * Ctil_t * (Qu*Qu*xth*DTPHI(1./(4*xth)) + Qu/(16.*Qq*cw2*sw2)*(1+pq*4*sw2*Qq)*(1-4*sw2*Qu)*xth*xtz/(xtz-xth)*(DTPHI(1/(4*xtz)) - DTPHI(1/(4*xth))))
         + aMZ/(6*pi*pi) * 1/ml * Ctill * (xth*((1-2*xth)*DTPHI(1/(4*xth)) + 2*(2+std::log(xth))) + Qu/(16*Qq*cw2*sw2)*(1+pq*4*sw2*Qq)*(1-4*sw2*Qu)*xth*xtz/(xtz-xth)*((1-2*xth)*DTPHI(1/(4*xth)) - 2*std::log(xhz) - (1-2*xtz)*DTPHI(1/(4*xtz))))
         + 3*aMZ/(8*pi*pi) * 1/mb * Ctil_b * (Qd*Qd*xbh*(std::pow(std::log(xbh),2) + pi*pi/3.) + Qd/(16*Qq*cw2*sw2)*(1+pq*4*sw2*Qq)*(1+4*sw2*Qd)*xbh*xbz/(xbz-xbh)*(std::pow(std::log(xbh),2) - std::pow(std::log(xbz),2)))
         + 3*aMZ/(8*pi*pi) * 1/mc * Ctil_c * (Qu*Qu*xch*(std::pow(std::log(xch),2) + pi*pi/3.) + Qu/(16*Qq*cw2*sw2)*(1+pq*4*sw2*Qq)*(1-4*sw2*Qu)*xch*xcz/(xcz-xch)*(std::pow(std::log(xch),2) - std::pow(std::log(xcz),2)))
         + 1*aMZ/(8*pi*pi) * 1/mtau * Ctil_tau * (xtauh*(std::pow(std::log(xtauh),2) + pi*pi/3.) - 1/(16*Qq*cw2*sw2)*(1+pq*4*sw2*Qq)*(1-4*sw2)*xtauh*xtauz/(xtauz-xtauh)*(std::pow(std::log(xtauh),2) - std::pow(std::log(xtauz),2)))
         + 1*aMZ/(8*pi*pi) * 1/mmu * Ctil_mu * (xmuh*(std::pow(std::log(xmuh),2) + pi*pi/3.) - 1/(16*Qq*cw2*sw2)*(1+pq*4*sw2*Qq)*(1-4*sw2)*xmuh*xmuz/(xmuz-xmuh)*(std::pow(std::log(xmuh),2) - std::pow(std::log(xmuz),2)))
         - aMZ/(32*pi*pi) * 1/ml * 3./(2*cw2) * Ctill * std::log(std::pow(muW/Lambda,2))
        );
    return res;
}

double LoopFunctions::C4q(char q, double muW, double Lambda, double Ctil_u, double Ctil_d, double Ctil_s, double Ctil_t){
    double mq = 0.; double Ctilq = 0.;
    if (q=='u') {mq = mu; Ctilq = Ctil_u;}
    if (q=='d') {mq = md; Ctilq = Ctil_d;}
    if (q=='s') {mq = ms; Ctilq = Ctil_s;}

    double res = std::pow(vev,3)/(std::sqrt(2) * std::pow(Lambda,2))*(
        + asMZ*asMZ/(16*pi*pi) * 1/mt * Ctil_t * xth*DTPHI(1/(4*xth))
        + asMZ*asMZ/(16*pi*pi) * 1/mq * Ctilq * xth*((2*xth-1)*DTPHI(1/(4*xth)) - 2*(2+std::log(xth)) )
        + 0.0*std::log(std::pow(muW/Lambda,2))
        );
    return res;
}

double LoopFunctions::Cw(double Lambda, double Ctil_t){
    double res = std::pow(vev,3)/(std::sqrt(2) * std::pow(Lambda,2))*(
        + asMZ*asMZ/(64*pi*pi) * 1/mt * Ctil_t * xth/std::pow((1-4*xth),3) * (3-14*xth+8*xth*xth + 6*xth*(1-2*xth+2*xth*xth)*DTPHI(1/(4*xth)) + (2+10*xth - 12*xth*xth)*std::log(xth))
        );
    return res;
}

double LoopFunctions::C1qqp(char q, char qp, double Lambda, double Ctil_u, double Ctil_d, double Ctil_s, double Ctil_c, double Ctil_b){
    double mq = 0.0; double Ctilqp = 0.0;

    if(q=='u') mq = mu;
    if(q=='d') mq = md;
    if(q=='s') mq = ms;
    if(q=='c') mq = mc;
    if(q=='b') mq = mb;
    if(qp=='u') Ctilqp = Ctil_u;
    if(qp=='d') Ctilqp = Ctil_d;
    if(qp=='s') Ctilqp = Ctil_s;
    if(qp=='c') Ctilqp = Ctil_c;
    if(qp=='b') Ctilqp = Ctil_b;

    return 1/(2*Mh) * std::pow(vev,1)/(std::sqrt(2) * std::pow(Lambda,2)) * mq * Ctilqp;
}

double LoopFunctions::C1q(char q, double Lambda, double Ctil_u, double Ctil_d, double Ctil_s, double Ctil_c, double Ctil_b){
    double mq = 0.0; double Ctilq = 0.0;
    if(q=='u') mq = mu; Ctilq = Ctil_u;
    if(q=='d') mq = md;Ctilq = Ctil_d;
    if(q=='s') mq = ms;Ctilq = Ctil_s;
    if(q=='c') mq = mc;Ctilq = Ctil_c;
    if(q=='b') mq = mb;Ctilq = Ctil_b;

    return 1/(2*Mh) * std::pow(vev,1)/(std::sqrt(2) * std::pow(Lambda,2)) * mq * Ctilq;
}

double LoopFunctions::get_meatmz(){return me;}
double LoopFunctions::get_mmuatmz(){return mmu;}
double LoopFunctions::get_mtauatmz(){return mtau;}
double LoopFunctions::get_muatmz(){return mu;}
double LoopFunctions::get_mdatmz(){return md;}
double LoopFunctions::get_msatmz(){return ms;}
double LoopFunctions::get_mcatmz(){return mc;}
double LoopFunctions::get_mbatmz(){return mb;}
double LoopFunctions::get_mtatmz(){return mt;}
