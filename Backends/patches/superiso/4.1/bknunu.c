#include "include.h"

/*----------------------------------------------------------------------*/
/*------------------------------ FULL ----------------------------------*/
/*----------------------------------------------------------------------*/


double dGamma_BKnunu_dq2_full(int charge, double q2, double complex CL, double complex CR, struct parameters* param, double mu_b) 
{	
	double mB,mK,eq;
	
	if(charge==0) 
	{
		mB=param->m_Bd;
		mK=param->m_K0;
		eq=-1./3.;
	}
	else
	{
		mB=param->m_B;
		mK=param->m_K;
		eq=2./3.;
	}
	
	double mc=mc_pole_1loop(param);
	double mbpole=mb_pole_1loop(param);
	double mb_mub=running_mass(param->mass_b,param->mass_b,mu_b,param->mass_top_pole,param->mass_b,param);
	

	double alpha_em=1./133.;

	double alphas_mub=alphas_running(mu_b,param->mass_top_pole,param->mass_b_pole,param);
	
	double mu_f=sqrt(mu_b*0.5);
	
	double alphas_muf=alphas_running(mu_f,param->mass_top_pole,param->mass_b_pole,param);
	double eta=alphas_muf/alphas_running(1.,param->mass_top_pole,param->mass_b_pole,param);


	
	double E_K=(mB*mB+mK*mK-q2)/2./mB;

	int nf=5;
	
	/* B -> K FF */ /* LCSR+Lattice from 1811.00983 */
	/*double mRf0_BKvD=5.630;
	double mRfp_BKvD=5.412;
	double mRfT_BKvD=5.412;

	double tau_plus=pow(mB+mK,2.);
	double tau_minus=pow(mB-mK,2.);
	double tau_0=tau_plus*( 1.-sqrt(1.-tau_minus/tau_plus) );
	double z_q2=(sqrt(tau_plus-q2)-sqrt(tau_plus-tau_0))/(sqrt(tau_plus-q2)+sqrt(tau_plus-tau_0));
	double z_0=(sqrt(tau_plus)-sqrt(tau_plus-tau_0))/(sqrt(tau_plus)+sqrt(tau_plus-tau_0));
	
	double P_0=1.-q2/pow(mRf0_BKvD,2.);
	double P_p=1.-q2/pow(mRfp_BKvD,2.);
	double P_T=1.-q2/pow(mRfT_BKvD,2.);

	double f0=(1./P_0)*( param->a00_BK + param->a10_BK*(z_q2-z_0) + param->a20_BK*pow(z_q2-z_0,2.) );
	double fp=(1./P_p)*( param->a0p_BK + param->a1p_BK*(z_q2-z_0) + param->a2p_BK*pow(z_q2-z_0,2.) );
	double fT=(1./P_T)*( param->a0T_BK + param->a1T_BK*(z_q2-z_0) + param->a2T_BK*pow(z_q2-z_0,2.) );
// 	printf("q2 = %.3f:\tf0 = %.3f\tfp = %.3f\tfT = %.3f\n", q2, f0, fp, fT);*/
	
	/********LCSR+Lattice fit parameters from Khodjamirian and Rusov 1703.04765***************/
	/*double tau_plus=pow(mB+mK,2.);
	double tau_minus=pow(mB-mK,2.);
	double tau_0=(mB+mK)*(sqrt(mB)-sqrt(mK))*(sqrt(mB)-sqrt(mK));
	double z_q2=(sqrt(tau_plus-q2)-sqrt(tau_plus-tau_0))/(sqrt(tau_plus-q2)+sqrt(tau_plus-tau_0));
	double z_0=(sqrt(tau_plus)-sqrt(tau_plus-tau_0))/(sqrt(tau_plus)+sqrt(tau_plus-tau_0));
	
	double P_p=1.-q2/pow(mRfp_BKvD,2.);
	double P_T=1.-q2/pow(mRfT_BKvD,2.);

	double f0=0; //No value given for f0 because not needed in soft approach at q2<6. However need to declare a f0 for the program
	double fp=(param->fp0_KR/P_p)*(1+param->b1p_KR*(z_q2-z_0 + 1./2.*(pow(z_q2,2.)-pow(z_0,2.))));
	double fT=(param->fT0_KR/P_T)*(1+param->b1T_KR*(z_q2-z_0 + 1./2.*(pow(z_q2,2.)-pow(z_0,2.))));*/
	
	
	/********Lattice fit parameters from HPQCD 2207.12468***************/
	double mRf0_HPQCD=5.729495;
	double mRfp_HPQCD=5.4158;
	double mRfT_HPQCD=5.4158;
	
	double tau_plus=pow(mB+mK,2.);
	double tau_minus=pow(mB-mK,2.);
	double tau_0=0;
	double z_q2=(sqrt(tau_plus-q2)-sqrt(tau_plus-tau_0))/(sqrt(tau_plus-q2)+sqrt(tau_plus-tau_0));
	double z_0=(sqrt(tau_plus)-sqrt(tau_plus-tau_0))/(sqrt(tau_plus)+sqrt(tau_plus-tau_0));
	
	double P_0=1.-q2/pow(mRf0_HPQCD,2.);
	double P_p=1.-q2/pow(mRfp_HPQCD,2.);
	double P_T=1.-q2/pow(mRfT_HPQCD,2.);

	double f0=param->L_HPQCD/P_0*(param->a00_HPQCD + param->a10_HPQCD*z_q2 + param->a20_HPQCD*pow(z_q2,2.));
	double fp=param->L_HPQCD/P_p*(param->a0p_HPQCD + param->a1p_HPQCD*(z_q2-1./3.*pow(z_q2,3.)) + param->a2p_HPQCD*(pow(z_q2,2.)+2./3.*pow(z_q2,3.)));
	double fT=param->L_HPQCD/P_T*(param->a0T_HPQCD + param->a1T_HPQCD*(z_q2-1./3.*pow(z_q2,3.)) + param->a2T_HPQCD*(pow(z_q2,2.)+2./3.*pow(z_q2,3.)));

	
	double lambda=pow(mB,4.)+pow(mK,4.)+q2*q2-2.*(mB*mB*mK*mK+mK*mK*q2+mB*mB*q2);
	
	double complex NK = param->Gfermi*param->Gfermi*alpha_em*alpha_em/256./pow(pi,5.)/pow(mB,3.)*pow(lambda,1.5); 
	
	double complex lambdat = param->Vtb*conj(param->Vts);
	
	double dGamma_BKnunu_dq2=NK*cabs(CL*conj(CL)+CR*conj(CR))*cabs(lambdat*conj(lambdat))*fp*fp;
	
	double dGamma_BKnunu_tree_dq2=0;
	if(charge!=0) // Tree correction for the charged decay with narrow width-approximation for tau 2301.06990  and 0908.1174
	{
	
		double m_tau = param->mass_tau;
		double Gamma_tau = hbar/param->life_tau;
		
		dGamma_BKnunu_tree_dq2=param->Gfermi*param->Gfermi*param->Gfermi*param->Gfermi*cabs((param->Vus*param->Vub)*conj((param->Vus*param->Vub)))*param->f_K*param->f_K*param->f_B*param->f_B/128./pi/pi/pow(mB,3.)*(-(pow(m_tau,3.)*(-mB + m_tau)*(mB + m_tau)*(-mK + m_tau)*(mK + 
	     m_tau)*pi + pow(m_tau,5.)*pi*q2)/Gamma_tau);
	     
	 }
	 
	double dGamma_BKnunu_dq2_tot = dGamma_BKnunu_dq2 + dGamma_BKnunu_tree_dq2;
	
	return dGamma_BKnunu_dq2_tot;
	 
}

/*------------------------------------------------------------------------------------------------------*/

double dGamma_BKnunu_dq2_full_calculator(int charge, double q2, char name[])
/* "container" function scanning the SLHA file "name" and calculating dGamma/dq2(B->K nu nu) */
{
	double complex CL, CR;
	
	struct parameters param;
		
	Init_param(&param);
	
	if(!Les_Houches_Reader(name,&param)) return 0.;

	double mu_W=param.mass_W;
	double mu_b=param.mass_b_pole;

	double mtmt = param.mtmt;
	double xt = pow(mtmt/param.mass_W,2.);
	double alphas_mut = alphas_running(mtmt,mtmt,param.mass_b_pole,&param);

	double XtSM = X0(xt) + alphas_mut/(4.*pi) * X1(xt,mtmt,param.mass_W);
	double sw2=pow(sin(atan(param.gp/param.g2)),2.);
	
	CL = -XtSM / sw2;
	CR = 0;

	

	return dGamma_BKnunu_dq2_full(charge, q2, CL, CR, &param, mu_b);
}

/*----------------------------------------------------------------------*/

double BRBKnunu_full(int charge, double smin, double smax, double complex CL, double complex CR, struct parameters* param, double mu_b)
{
	int ie,je;
	int nmax=100;
	if((smin<0.099)||(smax-smin>10.)) nmax=100;
	double Gamma=0.;
	double s;

	double h=(smax-smin)/nmax;	
	s=smin;
	Gamma=dGamma_BKnunu_dq2_full(charge,s,CL,CR,param,mu_b);
	
	for(ie=1;ie<nmax;ie++)	
	{
		s+=h;
		
		Gamma+=4.*dGamma_BKnunu_dq2_full(charge,s-h/2.,CL,CR,param,mu_b);
		

		Gamma+=2.*dGamma_BKnunu_dq2_full(charge,s,CL,CR,param,mu_b);
	}
	
	s=smax;
	Gamma+=4.*dGamma_BKnunu_dq2_full(charge,s-h/2.,CL,CR,param,mu_b);
	
	Gamma+=dGamma_BKnunu_dq2_full(charge,s,CL,CR,param,mu_b);
	
	
	Gamma*=h/6.;
	
	if(charge==0) return param->life_Bd/hbar*Gamma;
	else return param->life_B/hbar*Gamma;
	
	
}


/*----------------------------------------------------------------------*/
/*---------------------------- WRAPPER ---------------------------------*/
/*----------------------------------------------------------------------*/

double dGamma_BKnunu_dq2(int charge, double q2, double complex CL, double complex CR, struct parameters* param, double mu_b)
{
	if(param->fullFF==1) return dGamma_BKnunu_dq2_full(charge,q2,CL,CR,param,mu_b);
	else return dGamma_BKnunu_dq2_full(charge,q2,CL,CR,param,mu_b);
}


/*----------------------------------------------------------------------*/

double BRBKnunu(int charge, double smin, double smax, double complex CL, double complex CR, struct parameters* param, double mu_b)
{
	if(param->fullFF==1) return BRBKnunu_full(charge,smin,smax,CL,CR,param,mu_b);
	else return BRBKnunu_full(charge,smin,smax,CL,CR,param,mu_b);
}

/*----------------------------------------------------------------------*/

