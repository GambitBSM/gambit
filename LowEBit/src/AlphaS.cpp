#include "gambit/LowEBit/AlphaS.h"


AlphaS::AlphaS()
{
    //ctor
    m_nf = 0;
    m_loop = 0;
}


AlphaS::AlphaS(unsigned int nf, unsigned int loop)
{
    //ctor
    // only needed for alpha_s running when used in M_Quark_MSbar class.
    m_nf = nf;
    m_loop = loop;
}

AlphaS::~AlphaS()
{
    //dtor
}

double AlphaS::decouple_down_MSbar(double asatmu, double mu, double mh, unsigned int nf, unsigned int loop){
    if(loop == 1){
        return asatmu;
    }
    std::cout << "loop order not supported" << std::endl;
    return 0;
}

double AlphaS::decouple_up_MSbar(double asatmu, double mu, double mh, unsigned int nf, unsigned int loop){
    if(loop == 1){
        return asatmu;
    }
    std::cout << "loop order not supported" << std::endl;
    return 0;
}


void AlphaS::operator()(const double as, double &dasdmu, const double mu){
    if(m_loop==1){
        dasdmu =  2.*M_PI/mu * (-QCD_beta(m_nf,m_loop).chet() * std::pow(as/M_PI,2));
    }
    else{
        std::cout << "loop order not supported" << std::endl;
    }
    return;
}

double AlphaS::dalphasdmu(double mu, double as, unsigned int nf, unsigned int loop){
    if(loop == 1){
        return 2.*pi/mu * (-QCD_beta(nf,loop).chet() * std::pow(as/pi,2));
    }
    std::cout << "loop order not supported" << std::endl;
    return 0;
}


double AlphaS::solve_rge_nf(double asatmu, double mu, double mu0, unsigned int nf, unsigned int loop){
    typedef boost::numeric::odeint::runge_kutta_dopri5<double> stepper_type;
    m_nf = nf;
    m_loop = loop;
    if(mu>mu0){
        boost::numeric::odeint::integrate_adaptive( boost::numeric::odeint::make_controlled( 1E-12 , 1E-12 , stepper_type() ) , *this, asatmu , mu ,  mu0 , -0.001);
    }
    else{
        boost::numeric::odeint::integrate_adaptive( boost::numeric::odeint::make_controlled( 1E-12 , 1E-12 , stepper_type() ) , *this, asatmu , mu ,  mu0 , +0.001);
    }

    return asatmu;

}

double AlphaS::run(double mu0, unsigned int nf, unsigned int loop){
    if (nf == 6){
        double as5mut = solve_rge_nf(asMZ,Mz,mtatmt,5,loop);
        double as6mut = decouple_up_MSbar(as5mut, mtatmt, mtatmt, 6, loop);
        return solve_rge_nf(as6mut, mtatmt, mu0, 6, loop);
    }
    else if(nf==5){
        return solve_rge_nf(asMZ, Mz, mu0, 5, loop);
    }
    else if(nf==4){
        double as5mub = solve_rge_nf(asMZ, Mz, mbatmb, 5, loop);
        double as4mub = decouple_down_MSbar(as5mub, mbatmb, mbatmb, 4, loop);
        return solve_rge_nf(as4mub, mbatmb, mu0, 4, loop);
    }
    else if(nf==3){
        double as5mub = solve_rge_nf(asMZ, Mz, mbatmb, 5, loop);
        double as4mub = decouple_down_MSbar(as5mub, mbatmb, mbatmb, 4, loop);
        double as4muc = solve_rge_nf(as4mub, mbatmb, mcatmc, 4, loop);
        double as3muc = decouple_down_MSbar(as4muc, mcatmc, mcatmc, 4, loop);
        return solve_rge_nf(as3muc, mcatmc, mu0, 3, loop);
    }
    else{
        std::cout << "nf cannot be <3 or >6" << std::endl;
        return 0.0;
    }
}




