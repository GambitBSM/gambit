#include "gambit/LowEBit/LoopFunctions.h"

LoopFunctions::LoopFunctions()
{
    //ctor
    // Values at Higgs mass
    M_Quark_MSbar masses;
    AlphaS as;
    mu =masses.run('u',Mh,5,1);
    md =masses.run('d',Mh,5,1);
    ms =masses.run('s',Mh,5,1);
    mc =masses.run('c',Mh,5,1);
    mb =masses.run('b',Mh,5,1);
    mt =masses.run('t',Mh,6,1);
    xth = pow(mt/Mh,2);
    xtz = pow(mt/Mz,2);
    xbh = pow(mb/Mh,2);
    xbz = pow(mb/Mz,2);
    xch = pow(mc/Mh,2);
    xcz = pow(mc/Mz,2);
    xtauh = pow(mtau/Mh,2);
    xtauz = pow(mtau/Mz,2);
    xmuh = pow(mmu/Mh,2);
    xmuz = pow(mmu/Mz,2);
    xeh = pow(me/Mh,2);
    xez = pow(me/Mz,2);
    xhz = pow(Mh/Mz,2);
    xzh = 1/xhz;
    xhw = pow(Mh/Mw,2);
    xwh = 1/xhw;
    as51lMh = as.run(Mh,5,1);
}

LoopFunctions::~LoopFunctions()
{
    //dtor
}

double* LoopFunctions::get_masses2GeV(){
    M_Quark_MSbar m;
    static double masses[6] = {
	    m.run('u',2,3,1),
	    m.run('d',2,3,1),
	    m.run('s',2,3,1),
	    m.run('c',2,4,1),
	    m.run('b',2,5,1),
	    m.run('t',2,6,1),
	   };
    return masses;
}

double* LoopFunctions::get_massesMh(){
    M_Quark_MSbar m;
    static double masses[6] = {mu,md,ms,mc,mb,mt};
    return masses;
}

double LoopFunctions::Clausens2(double th, void * params){
    double res = 0.0;
    double step = 1E-5;
    double iter = step;
    while(iter<th){
        res+=log(std::abs(2*sin(iter/2.)))*step;
        iter+=step;
    }
    return -res;
//    return -log(std::abs(2*sin(th/2.)));
}

double LoopFunctions::PolyLog(double xi, void * params){
    double res = 0.0;
    double step = 1E-6;
    double iter = step;
    if(xi>0){
	    while(iter<xi){
		res+=log(1-iter)/iter*step;
		iter+=step;
	    }
    }
    else{
	    iter = -step;
	    while(iter>xi){
		res-=log(1-iter)/iter*step;
		iter-=step;
	    }

    }
    return -res;
//    return -log(1-xi)/xi;
}

double LoopFunctions::DTPHI(double z){
    double res, integral, err;
//    gsl_function F;
    if(z<1){
//        F.function = &Clausens2;
//        gsl_integration_qag(&F,0,2*asin(sqrt(z)),0,1E-6,1000,1,gsl_integration_workspace_alloc(1000),&integral,&err);
//        res = 4*sqrt(z/(1-z)) * integral;
        res = 4*sqrt(z/(1-z)) * Clausens2(2*asin(sqrt(z)),nullptr);

    }
    else{
        double xi = 1/2.*(1-sqrt((z-1)/z));
//        F.function = PolyLog;
//        gsl_integration_qag(&F,0,xi,0,1E-6,1000,1,gsl_integration_workspace_alloc(1000),&integral,&err);
//        res = sqrt(z/(z-1)) * (-4*integral + 2*pow(log(xi),2) - pow(log(4*z),2) + pow(pi,2)/3 );
        res = sqrt(z/(z-1)) * (-4*PolyLog(xi,nullptr) + 2*pow(log(xi),2) - pow(log(4*z),2) + pow(pi,2)/3 );
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
         + 3.*aMZ*as51lMh/(8.*pi*pi) * 1/mt * Ctil_t * (Qu*Qu*xth*DTPHI(1./(4*xth)) + Qu/(16.*Qq*cw2*sw2)*(1+pq*4*sw2*Qq)*(1-4*sw2*Qu)*xth*xtz/(xtz-xth)*(DTPHI(1/(4*xtz)) - DTPHI(1/(4*xth))))
         + aMZ*as51lMh/(6*pi*pi) * 1/mq * Ctilq * (Qu*Qu*xth*((1-2*xth)*DTPHI(1/(4*xth)) + 2*(2+std::log(xth))) + Qu/(16*Qq*cw2*sw2)*(1+pq*4*sw2*Qq)*(1-4*sw2*Qu)*xth*xtz/(xtz-xth)*((1-2*xth)*DTPHI(1/(4*xth)) - 2*std::log(xhz) - (1-2*xtz)*DTPHI(1/(4*xtz))))
         + 3*aMZ*as51lMh/(8*pi*pi) * 1/mb * Ctil_b * (Qd*Qd*xbh*(std::pow(std::log(xbh),2) + pi*pi/3.) + Qd/(16*Qq*cw2*sw2)*(1+pq*4*sw2*Qq)*(1+4*sw2*Qd)*xbh*xbz/(xbz-xbh)*(std::pow(std::log(xbh),2) - std::pow(std::log(xbz),2)))
         + 3*aMZ*as51lMh/(8*pi*pi) * 1/mc * Ctil_c * (Qu*Qu*xch*(std::pow(std::log(xch),2) + pi*pi/3.) + Qu/(16*Qq*cw2*sw2)*(1+pq*4*sw2*Qq)*(1-4*sw2*Qu)*xch*xcz/(xcz-xch)*(std::pow(std::log(xch),2) - std::pow(std::log(xcz),2)))
         + 1*aMZ*as51lMh/(8*pi*pi) * 1/mtau * Ctil_tau * (xtauh*(std::pow(std::log(xtauh),2) + pi*pi/3.) - 1/(16*Qq*cw2*sw2)*(1+pq*4*sw2*Qq)*(1-4*sw2)*xtauh*xtauz/(xtauz-xtauh)*(std::pow(std::log(xtauh),2) - std::pow(std::log(xtauz),2)))
         + 1*aMZ*as51lMh/(8*pi*pi) * 1/mmu * Ctil_mu * (xmuh*(std::pow(std::log(xmuh),2) + pi*pi/3.) - 1/(16*Qq*cw2*sw2)*(1+pq*4*sw2*Qq)*(1-4*sw2)*xmuh*xmuz/(xmuz-xmuh)*(std::pow(std::log(xmuh),2) - std::pow(std::log(xmuz),2)))
         + 1*aMZ*as51lMh/(8*pi*pi) * 1/me * Ctil_e * (xeh*(std::pow(std::log(xeh),2) + pi*pi/3.) - 1/(16*Qq*cw2*sw2)*(1+pq*4*sw2*Qq)*(1-4*sw2)*xeh*xez/(xez-xeh)*(std::pow(std::log(xeh),2) - std::pow(std::log(xez),2)))
         - aMZ*as51lMh/(16*pi*pi) * 1/mq * (pq*1/(4*Qq) + 1)/(cw2) * Ctilq * std::log(std::pow(muW/Lambda,2))
        );
    	double pre = std::pow(vev,3)/(std::sqrt(2) * std::pow(Lambda,2));
	double u2 = aMZ*as51lMh/(6*pi*pi) * 1/mq * Ctilq * Qu*Qu*xth*((1-2*xth)*DTPHI(1/(4*xth))+ 2*(2+std::log(xth)));
	double u1 = aMZ*as51lMh/(6*pi*pi) * 1/mq * Ctilq * (+ Qu/(16*Qq*cw2*sw2)*(1+pq*4*sw2*Qq)*(1-4*sw2*Qu)*xth*xtz/(xtz-xth)*((1-2*xth)*DTPHI(1/(4*xth)) - 2*std::log(xhz) - (1-2*xtz)*DTPHI(1/(4*xtz))));
	double u3 = - aMZ*as51lMh/(16*pi*pi) * 1/mq * (pq*1/(4*Qq) + 1)/(cw2) * Ctilq * std::log(std::pow(muW/Lambda,2));
	
 
    return res;
}

double LoopFunctions::C3e(char l, double muW, double Lambda, double Ctil_e, double Ctil_mu, double Ctil_tau, double Ctil_u, double Ctil_d, double Ctil_s, double Ctil_c, double Ctil_b, double Ctil_t){
    double pq = +1; double Qq = -1;
    double ml = 0.; double Ctilq = 0.;
    if (l=='e') ml = me; double Ctill = Ctil_e;
    double res = 1/(4*pi)*std::pow(vev,3)/(std::sqrt(2) * std::pow(Lambda,2))*(
         + 3.*aMZ/(8.*pi*pi) * 1/mt * Ctil_t * (Qu*Qu*xth*DTPHI(1./(4*xth)) + Qu/(16.*Qq*cw2*sw2)*(1+pq*4*sw2*Qq)*(1-4*sw2*Qu)*xth*xtz/(xtz-xth)*(DTPHI(1/(4*xtz)) - DTPHI(1/(4*xth))))
         + aMZ/(6*pi*pi) * 1/ml * Ctill * (0
            + Qu*Qu*xth*((1-2*xth)*DTPHI(1./(4*xth)) + 2*(2+std::log(xth)))
            + Qu/(16*Qq*cw2*sw2)*(1+pq*4*sw2*Qq)*(1-4*sw2*Qu)*xth*xtz/(xtz-xth)*((1-2*xth)*DTPHI(1./(4*xth)) - 2*std::log(xhz) - (1-2*xtz)*DTPHI(1./(4*xtz)))
                )
         + 3*aMZ/(8*pi*pi) * 1/mb * Ctil_b * (Qd*Qd*xbh*(std::pow(std::log(xbh),2) + pi*pi/3.) + Qd/(16*Qq*cw2*sw2)*(1+pq*4*sw2*Qq)*(1+4*sw2*Qd)*xbh*xbz/(xbz-xbh)*(std::pow(std::log(xbh),2) - std::pow(std::log(xbz),2)))
         + 3*aMZ/(8*pi*pi) * 1/mc * Ctil_c * (Qu*Qu*xch*(std::pow(std::log(xch),2) + pi*pi/3.) + Qu/(16*Qq*cw2*sw2)*(1+pq*4*sw2*Qq)*(1-4*sw2*Qu)*xch*xcz/(xcz-xch)*(std::pow(std::log(xch),2) - std::pow(std::log(xcz),2)))
         + 1*aMZ/(8*pi*pi) * 1/mtau * Ctil_tau * (xtauh*(std::pow(std::log(xtauh),2) + pi*pi/3.) - 1/(16*Qq*cw2*sw2)*(1+pq*4*sw2*Qq)*(1-4*sw2)*xtauh*xtauz/(xtauz-xtauh)*(std::pow(std::log(xtauh),2) - std::pow(std::log(xtauz),2)))
         + 1*aMZ/(8*pi*pi) * 1/mmu * Ctil_mu * (xmuh*(std::pow(std::log(xmuh),2) + pi*pi/3.) - 1/(16*Qq*cw2*sw2)*(1+pq*4*sw2*Qq)*(1-4*sw2)*xmuh*xmuz/(xmuz-xmuh)*(std::pow(std::log(xmuh),2) - std::pow(std::log(xmuz),2)))
         - aMZ/(32*pi*pi) * 1/ml * 3./(2*cw2) * Ctill * std::log(std::pow(muW/Lambda,2))
        );

    return res;
}

double LoopFunctions::C4q(char q, double muW, double Lambda, double Ctil_u, double Ctil_d, double Ctil_s, double Ctil_t){
    double mq = 0.; double Ctilq = 0.; double Qq = 0.; int pm=0.;
    if (q=='u') {mq = mu; Ctilq = Ctil_u;Qq=2./3.;pm=-1;}
    if (q=='d') {mq = md; Ctilq = Ctil_d;Qq=-1./3.;pm=1;}
    if (q=='s') {mq = ms; Ctilq = Ctil_s;Qq=-1./3.;pm=1;}

    double res = std::pow(vev,3)/(std::sqrt(2) * std::pow(Lambda,2))*(
        + as51lMh*as51lMh/(16*pi*pi) * 1/mt * Ctil_t * xth*DTPHI(1/(4*xth))
        + as51lMh*as51lMh/(16*pi*pi) * 1/mq * Ctilq * xth*((2*xth-1)*DTPHI(1/(4*xth)) - 2*(2+std::log(xth)) )
	+ as51lMh*aMZ/(192*pi*pi*cw2) * 1/mq * Ctilq * (2*Qq*Qq*sw2 + pm*Qq)*
		(
		(3*xhz*xhz*xhz - 18*xhz*xhz + 24*xhz)*DTPHI(xhz/4) + 6*xhz*(1+2*std::log(xhz))
		+(12*xhz*xhz*xhz - 48*xhz*xhz + 12*xhz)*PolyLog(1-xhz,nullptr)
		+(xhz*xhz*xhz - 4*xhz*xhz)*pi*pi + (3*xhz*xhz*xhz - 12*xhz*xhz)*std::pow(std::log(xhz),2)
		)
	+ as51lMh*aMZ/(1152*pi*pi*cw2*sw2) * 1/mq * Ctilq * (1+pm*4*Qq*sw2 + 8*Qq*Qq*sw2*sw2)*xzh*xzh*
		(
		(3*xhz*xhz*xhz - 6*xhz*xhz - 24*xhz)*DTPHI(xhz/4) 
		+ (6*xhz*xhz + 24*xhz)*std::log(xhz) + (6*xhz*xhz - 24*xhz)
		+ (6*xhz*xhz*xhz - 18*xhz*xhz - 24*xhz)*PolyLog(1-xhz,nullptr) + (3*xhz + 4)*pi*pi
		)
	+ as51lMh*aMZ/(576*pi*pi*sw2) * 1/mq * Ctilq * xhw*
		(
		(3 - 6*xwh - 24*xwh*xwh)*DTPHI(xhw/4) + (3*xwh*xwh + 4*xwh*xwh*xwh)*pi*pi
		-(6*xwh+24*xwh*xwh)*std::log(xwh) + (6*xwh - 24*xwh*xwh)
		+(12*xwh*xwh*xwh + 9*xwh*xwh - 3) * (2*PolyLog(1-xwh,nullptr) + std::pow(std::log(xwh),2))
		)
        );


   
    return res;
}

double LoopFunctions::Cw(double Lambda, double Ctil_t){
    double res = std::pow(vev,3)/(std::sqrt(2) * std::pow(Lambda,2))*(
        + as51lMh*as51lMh/(64*pi*pi) * 1/mt * Ctil_t * xth/std::pow((1-4*xth),3) * (3-14*xth+8*xth*xth + 6*xth*(1-2*xth+2*xth*xth)*DTPHI(1/(4*xth)) + (2+10*xth - 12*xth*xth)*std::log(xth))
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
