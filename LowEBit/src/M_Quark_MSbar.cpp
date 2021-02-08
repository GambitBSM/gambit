#include "gambit/LowEBit/M_Quark_MSbar.h"

M_Quark_MSbar::M_Quark_MSbar()
{
    //ctor

}

M_Quark_MSbar::~M_Quark_MSbar()
{
    //dtor
}

double M_Quark_MSbar::decouple_down_MSbar(double mlatmu, double mu, double mh, double asatmu, unsigned int loop){
    if(loop == 1){
        return mlatmu;
    }
    std::cout << "loop order not supported" << std::endl;
    return 0;
}

double M_Quark_MSbar::decouple_up_MSbar(double mlatmu, double mu, double mh, double asatmu, unsigned int loop){
    if(loop == 1){
        return mlatmu;
    }
    std::cout << "loop order not supported" << std::endl;
    return 0;
}

double M_Quark_MSbar::dmqdmu(double mu, double mq, double asatmu, unsigned int nf, unsigned int loop){
    if(loop == 1){
        return -2 * mq/mu * (QCD_gamma(m_nf,m_loop).chet()) * asatmu/pi;
    }
    std::cout << "loop order not supported" << std::endl;
    return 0;
}

void M_Quark_MSbar::operator()(const double mq, double &dmqdmu, const double mu){
    AlphaS as(m_nf,m_loop);
    if(m_loop == 1){
        dmqdmu = -2 * mq/mu * (QCD_gamma(m_nf,m_loop).chet()) * as.run(mu,m_nf,m_loop)/pi;
    }
    else{
        std::cout << "loop order not supported" << std::endl;
    }
    return;
}

double M_Quark_MSbar::solve_rge_nf(double mqatmu, double mu, double mu0, unsigned int nf, unsigned int loop){
    typedef boost::numeric::odeint::runge_kutta_dopri5<double> stepper_type;
    m_nf = nf;
    m_loop = loop;
    if(mu>mu0){
        boost::numeric::odeint::integrate_adaptive( boost::numeric::odeint::make_controlled( 1E-12 , 1E-12 , stepper_type() ) , *this, mqatmu , mu ,  mu0 , -0.001);
    }
    else{
        boost::numeric::odeint::integrate_adaptive( boost::numeric::odeint::make_controlled( 1E-12 , 1E-12 , stepper_type() ) , *this, mqatmu , mu ,  mu0 , +0.001);
    }


    return mqatmu;

}

double M_Quark_MSbar::run(char flavour, double mu0, unsigned int nf, unsigned int loop){
    AlphaS as(m_nf,m_loop);
    if(flavour == 't'){
        if(nf == 6){
            return solve_rge_nf(mtatmt,mtatmt,mu0,6,loop);
        }
        else{std::cout << "top can only run in 6 flavour theory" << std::endl; return 0;}
    }
    else if(flavour == 'b'){
        if(nf == 5){
            return solve_rge_nf(mbatmb,mbatmb,mu0,5,loop);
        }
        else{std::cout << "bottom can only run in 5 flavour theory" << std::endl; return 0;}
    }
    else if(flavour == 'c'){
        if(nf == 4){
            return solve_rge_nf(mbatmb,mbatmb,mu0,4,loop);
        }
        else if(nf == 5){
            double mcatmb_4f = solve_rge_nf(mcatmc,mcatmc,mbatmb,4,loop);
            double mcatmb_5f = decouple_up_MSbar(mcatmb_4f,mbatmb,mbatmb,as.run(mu0,4,loop),loop);
            return solve_rge_nf(mcatmb_5f,mbatmb,mu0,5,loop);
        }
        else{std::cout << "charm can only run in 4 or 5 flavour theory" << std::endl; return 0;}
    }
    else if(flavour == 'u' || flavour == 'd' || flavour == 's'){
        double mq = 0.;
        if(flavour=='u'){mq = muat2gev;}
        else if(flavour=='d'){mq = mdat2gev;}
        else{mq = msat2gev;}

        if(nf == 3){
            return solve_rge_nf(mq,2,mu0,3,loop);
        }
        else if(nf == 4){
            double mqatmc_3f = solve_rge_nf(mq,2,mcatmc,3,loop);
            double mqatmc_4f = decouple_up_MSbar(mqatmc_3f,mcatmc,mcatmc,as.run(mu0,3,loop),loop);
            return solve_rge_nf(mqatmc_4f,mbatmb,mu0,4,loop);
        }
        else if(nf == 5){
            double mqatmc_3f = solve_rge_nf(mq,2,mcatmc,3,loop);
            double mqatmc_4f = decouple_up_MSbar(mqatmc_3f,mcatmc,mcatmc,as.run(mu0,3,loop),loop);
            double mqatmb_4f = solve_rge_nf(mqatmc_4f,mcatmc,mbatmb,4,loop);
            double mqatmb_5f = decouple_up_MSbar(mqatmb_4f,mbatmb,mbatmb,as.run(mu0,4,loop),loop);
            return solve_rge_nf(mqatmb_5f,mbatmb,mu0,5,loop);
        }
        else{std::cout << "charm can only run in 4 or 5 flavour theory" << std::endl; return 0;}
    }
    else{std::cout << "flavour can only be 'u', 'd', 's', 'c', 'b', or 't' " << std::endl; return 0;}

}





