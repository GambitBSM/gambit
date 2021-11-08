#include "include.h"

/*--------------------------------------------------------------*/

double heff(double Temp, struct relicparam* paramrelic)
{
	int ie;

	if(Temp>= paramrelic->table_eff[0][0]) return paramrelic->table_eff[0][2];

	if(Temp<2.35e-13) return paramrelic->table_eff[275][2];

	ie=1;
	while(Temp<paramrelic->table_eff[ie][0]) ie++;

	double heff1,heff2,logT1,logT2,logT;
	logT=log(Temp);
	heff1=paramrelic->table_eff[ie][2];
	heff2=paramrelic->table_eff[ie-1][2];
	logT1=log(paramrelic->table_eff[ie][0]);
	logT2=log(paramrelic->table_eff[ie-1][0]);

	return (heff2-heff1)/(logT2-logT1)*(logT-logT1)+heff1;
}

/*--------------------------------------------------------------*/

double sgStar(double Temp, struct relicparam* paramrelic)
{
	int ie;

	if(Temp>=paramrelic->table_eff[0][0]) return paramrelic->table_eff[0][1];

	if(Temp<2.35e-13) return paramrelic->table_eff[275][1];

	ie=1;
	while(Temp<paramrelic->table_eff[ie][0]) ie++;

	double sgStar1,sgStar2,logT1,logT2,logT;
	logT=log(Temp);
	sgStar1=paramrelic->table_eff[ie][1];
	sgStar2=paramrelic->table_eff[ie-1][1];
	logT1=log(paramrelic->table_eff[ie][0]);
	logT2=log(paramrelic->table_eff[ie-1][0]);

	return (sgStar2-sgStar1)/(logT2-logT1)*(logT-logT1)+sgStar1;
}

/*--------------------------------------------------------------*/

double geff(double Temp, struct relicparam* paramrelic)
{
	double heff0=heff(Temp,paramrelic);

	return pow(heff0/sgStar(Temp,paramrelic)*(1.+(heff(Temp*1.001,paramrelic)-heff(Temp*0.999,paramrelic))/0.006/heff0),2.);
}

/*--------------------------------------------------------------*/

void Init_cosmomodel(struct relicparam* paramrelic)
{
	paramrelic->full_comput=0;

	paramrelic->solver=1; /* 1=logarithmic, 2=linear */

	paramrelic->failsafe=1;         // 0=fast, 1=precise (default), ... See stand_cosmo.c
	paramrelic->err=0;
    paramrelic->Tinit=27.;          // Starting at T = 27 x 10^9 K as default
    paramrelic->Tnudec=27.;           // Neutrino decoupling T = 27 x 10^9 K as default
    paramrelic->eta0=6.10e-10;      // Baryon-to-photon ratio (Planck 2015 results XIII)
    paramrelic->Nnu=3.046;          // Number of SM neutrinos, e+- reheating included
    paramrelic->dNnu=0.;            // Number of extra neutrino species (e.g. sterile neutrinos)
    paramrelic->life_neutron=880.2; // Neutron lifetime (PDG2018)
    paramrelic->life_neutron_error=1.0; // Neutron lifetime uncertainty (PDG2017)
	paramrelic->xinu1=0.;
	paramrelic->xinu2=0.;
	paramrelic->xinu3=0.;
	paramrelic->beta_samples=100;	// how accurately to model n<-->p beta reactions

	paramrelic->b_cdm_ratio=0.02242/0.11933;   // current baryon to cold dark matter density ratio (Planck 2018 results VI)

    paramrelic->wimp=0;
	//paramrelic->m_chi=paramrelic->g_chi=paramrelic->SMC_wimp=paramrelic->selfConjugate=paramrelic->fermion=paramrelic->EM_coupled=paramrelic->neut_coupled=paramrelic->neuteq_coupled=0;
	paramrelic->m_chi=0;
	paramrelic->g_chi=0;
	paramrelic->SMC_wimp=0;
	paramrelic->selfConjugate=0;
	paramrelic->fermion=0;
	paramrelic->EM_coupled=0;
	paramrelic->neut_coupled=0;
	paramrelic->neuteq_coupled=0;

	paramrelic->fierz=0.;			// no fierz interface in the standard model
	paramrelic->B_chi=0.;			// default is no branching to dark matter m_p < m_chi < m_n

	paramrelic->dd0=paramrelic->ndd=paramrelic->Tdend=paramrelic->Tddeq=0.;
	paramrelic->sd0=paramrelic->nsd=paramrelic->Tsend=0.;
	paramrelic->nt0=paramrelic->nnt=paramrelic->Tnend=0.;
	paramrelic->Sigmad0=paramrelic->nSigmad=paramrelic->TSigmadend=0.;
	paramrelic->Sigmarad0=paramrelic->nSigmarad=paramrelic->TSigmaradend=0.;
	paramrelic->coupd=0;

	paramrelic->mgravitino=0.;

	paramrelic->phi_model=0;
	paramrelic->eta_phi=paramrelic->Gamma_phi=paramrelic->n_phi=paramrelic->rhot_phi_Tmax=paramrelic->Tphi0=paramrelic->rhot_phi0=0.;

  	paramrelic->entropy_model=1;
	paramrelic->energy_model=1;

 	paramrelic->mgravitino=paramrelic->relicmass=0.;

	paramrelic->full_comput=paramrelic->scalar=0;
	paramrelic->Tfo=0.;

	paramrelic->Tmax=50.;

    Init_modeleff(2,paramrelic);

    paramrelic->use_table_rhoPD=paramrelic->size_table_rhoPD=0;
		paramrelic->use_table_Ffunc=paramrelic->size_table_Ffunc=0;
		paramrelic->mass=paramrelic->mu=paramrelic->vval=paramrelic->phi_init=0;

    paramrelic->constraints=2;

	return;
}

/*--------------------------------------------------------------*/

void Init_cosmomodel_param(double eta, double Nnu, double dNnu, double life_neutron, double life_neutron_error, double xinu1,
                           double xinu2, double xinu3, struct relicparam* paramrelic)
/* modifies the values of the baryon-to-photon ratio eta, the number of SM neutrinos Nnu, extra neutrino species dNnu
 *  and the neutron lifetime life_neutron */
{
    paramrelic->eta0=eta;
    paramrelic->Nnu=Nnu;
    paramrelic->dNnu=dNnu;
    paramrelic->life_neutron=life_neutron;
    paramrelic->life_neutron_error=life_neutron_error;
    paramrelic->xinu1=xinu1;
    paramrelic->xinu2=xinu2;
    paramrelic->xinu3=xinu3;
	paramrelic->beta_samples=100;	// how accurately to model n<-->p beta reactions
    return;
}

/*--------------------------------------------------------------*/

void Init_modeleff(int model_eff, struct relicparam* paramrelic)
{
	int ie,je;

	if(model_eff==1)
	{
		const double tableA[276][3]=
		{
#include "sgStar_heff/sgStar_heff_A.tab"
  		};
		for(ie=0;ie<=275;ie++) for(je=0;je<=2;je++) paramrelic->table_eff[ie][je]=tableA[ie][je];
	}
	else if(model_eff==2)
	{
		const double tableB[276][3]=
		{
#include "sgStar_heff/sgStar_heff_B.tab"
  		};
		for(ie=0;ie<=275;ie++) for(je=0;je<=2;je++) paramrelic->table_eff[ie][je]=tableB[ie][je];
	}
	else if(model_eff==3)
	{
	const double tableB2[276][3]=
		{
#include "sgStar_heff/sgStar_heff_B2.tab"
  		};
		for(ie=0;ie<=275;ie++) for(je=0;je<=2;je++) paramrelic->table_eff[ie][je]=tableB2[ie][je];
		}
	else if(model_eff==4)
	{
		const double tableB3[276][3]=
		{
#include "sgStar_heff/sgStar_heff_B3.tab"
  		};
		for(ie=0;ie<=275;ie++) for(je=0;je<=2;je++) paramrelic->table_eff[ie][je]=tableB3[ie][je];
	}
	else if(model_eff==5)
	{
		const double tableC[276][3]=
		{
#include "sgStar_heff/sgStar_heff_C.tab"
  		};
		for(ie=0;ie<=275;ie++) for(je=0;je<=2;je++) paramrelic->table_eff[ie][je]=tableC[ie][je];
	}
	else if(model_eff==6)
	{
		const double tableBonn[276][3]=
		{
#include "sgStar_heff/sgStar_heff_Bonn.tab"
  		};
		for(ie=0;ie<=275;ie++) for(je=0;je<=2;je++) paramrelic->table_eff[ie][je]=tableBonn[ie][je];
	}
	else
	{
		const double tableold[276][3]=
		{
#include "sgStar_heff/sgStar_heff_old.tab"
  		};
		for(ie=0;ie<=275;ie++) for(je=0;je<=2;je++) paramrelic->table_eff[ie][je]=tableold[ie][je];
	}
	return;
}

// SCALAR FIELD ADDITIONS ////////////////////////////////////////
/*--------------------------------------------------------------*/
// SOLVE FOR THE SCALAR FIELD
/* Functions to calculate symmetron field quantities */

/* Calculates the symmetron coupling function given the dimenionless field value phi,
		mass (GeV), v (GeV) */
double Afunc(double phi, double mass, double vparam)
{
  return (1.+ pow(vparam*phi/mass,2.0)/2.);
}

/* Calculates the symmetron potential function given the dimensionless field value phi \
		mu (GeV), v (GeV) */
double Vfunc(double phi, double mu, double vparam)
{
  return (-0.5*pow(mu*vparam,2.0)*pow(phi,2.0) + 0.25*pow(mu*vparam,2.0)*pow(phi,4.0));
}


/* Calculates the symmetron potential function derivative wrt phi given mu (GeV),
		v (GeV) and dimensionless field value phi */
double Vderivfunc( double phi,double mu, double v)
	{
		return -pow(mu*v,2.0)*phi +  pow(mu*v,2.0)*pow(phi,3.0);
	}

/* Calculates the parameter alpha(phi) = dlnA/dphi given dimenionless field value phi,
		mass (GeV), v (GeV) */
double alphafunc(double phi, double mass, double vparam)
	{
	  return (1./(1.+pow(vparam*phi/mass,2.0)/2.)*pow(vparam/mass,2.0)*phi);
	}

/* define the symmetron parameters for the ODE */
struct odeparameters {
  double massparam; // mass parameter
  double muparam; // mu parameter
  double vparam; // v parameter
  double phi0; // dimensionless field at present day for the given parameters
};

// function to store the ODE as a first order system
// we are solving for y(x) where x = ln a (scale factor)
int func (double T, const double y[], double f[], void *params)
{
  struct odeparameters * paramspointer = params;
  double mass = paramspointer->massparam;
  double mu = paramspointer->muparam;
  double vval = paramspointer->vparam;
  double phi0 = paramspointer->phi0;

  double Aval = Afunc(y[0], mass, vval);
  double Vval = Vfunc(y[0], mu, vval);
  double Vderiv = Vderivfunc(y[0], mu, vval);
  double Gstar = G*pow(Afunc(phi0, mass, vval),-2.)/(1+pow(alphafunc(phi0, mass, vval),2.));

  double densitystar = pi*pi/15.*pow(T,4)*pow(Aval,4.); // assume only radiation
  double omega = 1.0/(8.0*pi*Gstar*densitystar)*Vderiv/(M_pl*M_pl);
  double eta = 1.0/(8.0*pi*Gstar*densitystar)*Vval/(M_pl*M_pl);

  f[0] = y[1];
  f[1] = (-omega-2.0/3.0*(1+3.0*eta)*y[1]*T)*(3.0-pow(y[1]*T,2.0))/(2.0*(1.0+eta)*T*T)+y[1]/(T);
  return GSL_SUCCESS;
}

int jac()
{
  return GSL_SUCCESS;
}

void Init_vecs(struct relicparam* paramrelic)
{
	// printf("function called \n");
	// Put symmetron parameters back into GeV units
	double massparam = paramrelic->mass;
	double muparam = paramrelic->mu;
	double vparam = paramrelic->vval;
	double phi_0 = 1e-6; // set constant for now
	double phi_init = paramrelic->phi_init;

	massparam = pow(10., massparam)*M_pl;
	muparam = pow(10., muparam);
	vparam = pow(10., vparam)*M_pl;

	/* Solve for the field values first */
	// set up solver
	const gsl_odeiv2_step_type * T
		= gsl_odeiv2_step_rkf45;

	gsl_odeiv2_step * s
		= gsl_odeiv2_step_alloc (T, 2);
	gsl_odeiv2_control * c
		= gsl_odeiv2_control_y_new (1e-10, 1e-10);
	gsl_odeiv2_evolve * e
		= gsl_odeiv2_evolve_alloc (2);

	struct odeparameters params = {massparam, muparam, vparam, phi_0};
	gsl_odeiv2_system sys = {func, jac, 2, &params};

	double x = -3e-3, xb = -1.07e-8; // radiation domination period, temperature domain in GeV
	double h = 1e-6;
	double y[2] = {phi_init, 0.0};

	// vectors to store the field and its derivatives in
	int nlines = 0; // count the number of lines in field sln vec
	int count =0;
	double tempvec[NTABMAX], phivec[NTABMAX], phidotvec[NTABMAX];
	double tempold = 0.;

	while (x < xb) {
		int status = gsl_odeiv2_evolve_apply (e, c, s, &sys, &x, xb, &h, y);

		if (status != GSL_SUCCESS) {// || isnan(y[0])>0 || isnan(y[1])>0){
			fprintf(stderr, "Solver error: GSL_SUCCESS not returned, routine ended at T = %.5e GeV \n", -x); break;
		}
		// fprintf (datafile, "%.5e  %.5e  %.5e \n", x, y[0], y[1]);

		if (nlines > NTABMAX){
			fprintf(stderr, "No. points in field sln exceeds alterbbn's limit \n"); break;
		}
		else if (nlines < NTABMAX && (count)%5==0 && fabs(tempold-x)>1.e-10){
			tempold = x;
			tempvec[nlines] = -x; // field is solved in terms of negative temperature
			phivec[nlines] = y[0];
			phidotvec[nlines] = -y[1]; // derivative change sign with temperature
			// fprintf (datafile, "%.5e  %.5e  %.5e \n", tempvec[nlines], phivec[nlines], phidotvec[nlines]);
			// printf ("%.5e  %.5e  %.5e \n", tempvec[nlines], phivec[nlines], phidotvec[nlines]);
			nlines ++;
		}

		count ++;
	}

	gsl_odeiv2_evolve_free (e);
	gsl_odeiv2_control_free (c);
	gsl_odeiv2_step_free (s);

	/* Calculate the modified terms that alterbbn will read in */
	double alpha0 = alphafunc(phi_0, massparam, vparam);
	double A0val = Afunc(phi_0, massparam, vparam);
	double xtermvec[2][NTABMAX], rhodvec[2][NTABMAX];
	double temp, phi, phidot;

	for (int i=0; i<nlines; i++){
		temp = tempvec[i];
		phi = phivec[i];
		phidot = phidotvec[i];
		paramrelic->table_Ffunc[0][i] = temp;
		paramrelic->table_Ffunc[0][i] = temp;
		paramrelic->table_Ffunc[1][i] = Afunc(phi, massparam, vparam)*(1-alphafunc(phi, massparam, vparam)*phidot*temp)
									*pow(1.-1./3.*pow(phidot*temp,2.),-0.5)*pow(A0val*A0val*(1+alpha0*alpha0),-0.5);
		paramrelic->table_rhoPD[1][i] = (1.+alpha0*alpha0)*A0val*A0val/(4*pi*G)
									*Vfunc(phi,muparam,vparam)/(pow(Afunc(phi,massparam,vparam),4.)*2.*M_pl*M_pl);
		// printf("%.5e %.5e %.5e \n", paramrelic->table_Ffunc[0][i], paramrelic->table_Ffunc[1][i], paramrelic->table_rhoPD[1][i]);
		// printf("%.5e %.5e %.5e \n", temp, phi, phidot);
	}

	paramrelic->size_table_Ffunc = nlines;
	paramrelic->size_table_rhoPD = nlines;
	paramrelic->use_table_Ffunc = 1;
	paramrelic->use_table_rhoPD = 1;

}

/*--------------------------------------------------------------*/

double Ffunc_Hscaling(double T, struct relicparam* paramrelic)
{
	if(paramrelic->use_table_Ffunc<1) return 1.; // no modifications and scaling
	else if(paramrelic->size_table_Ffunc>1&&paramrelic->use_table_Ffunc)
		{
			int ie=1;

			if(T<paramrelic->table_Ffunc[0][paramrelic->size_table_Ffunc-1])
			{
				return 1.; // if interpolating outside the table, then there is no field so scaling is 0
			}
			else if(T<paramrelic->table_Ffunc[0][0]&&T>paramrelic->table_Ffunc[0][paramrelic->size_table_Ffunc-1])
			{
				while(T<paramrelic->table_Ffunc[0][ie]&&ie<paramrelic->size_table_Ffunc) ie++;
			}

			double logFfunc1,logFfunc2,Ffunc,logT1,logT2,logT;
			logT=log(T);
			logFfunc1=log(paramrelic->table_Ffunc[1][ie]);
			logFfunc2=log(paramrelic->table_Ffunc[1][ie-1]);
			logT1=log(paramrelic->table_Ffunc[0][ie]);
			logT2=log(paramrelic->table_Ffunc[0][ie-1]);

			Ffunc=exp((logFfunc2-logFfunc1)/(logT2-logT1)*(logT-logT1)+logFfunc1);
			// printf("T = %f, Ffunc = %e \n", T, Ffunc);
			return Ffunc;


	}
	else return 1.;

}

/*--------------------------------------------------------------*/

void Init_wimp(double mass_wimp, int EM_coupled, int neut_coupled, int neuteq_coupled, int fermion, int selfConjugate, double g_chi, struct relicparam* paramrelic)
/* modifies the parameters of an included light WIMP */
{
    paramrelic->m_chi=mass_wimp;
    paramrelic->g_chi=g_chi;
    paramrelic->fermion=fermion;
    paramrelic->EM_coupled=EM_coupled;
    paramrelic->neut_coupled=neut_coupled;
    paramrelic->neuteq_coupled=neuteq_coupled;
    paramrelic->wimp=1;
    paramrelic->selfConjugate=selfConjugate;
    return;
}

/*--------------------------------------------------------------*/

void Init_dark_density(double dd0, double ndd, double T_end, struct relicparam* paramrelic)
{
	if(paramrelic->phi_model)
	{
		paramrelic->energy_model=0;
		return;
	}

	paramrelic->energy_model=1;
	paramrelic->dd0=dd0;
	paramrelic->ndd=ndd;
	paramrelic->Tdend=T_end;

	paramrelic->Tddeq=0.;

    paramrelic->use_table_rhoPD=paramrelic->size_table_rhoPD=0;

	return;
}

/*--------------------------------------------------------------*/

void Init_dark_density2(double ndd, double Tddeq, double T_end, struct relicparam* paramrelic)
{
	if(paramrelic->phi_model)
	{
		paramrelic->energy_model=0;
		return;
	}

	paramrelic->energy_model=2;
	paramrelic->ndd=ndd;
	paramrelic->Tddeq=Tddeq;
	paramrelic->Tdend=T_end;

	paramrelic->dd0=0.;

    paramrelic->use_table_rhoPD=paramrelic->size_table_rhoPD=0;

	return;
}

/*--------------------------------------------------------------*/

void Init_dark_coupling(int coupD, struct relicparam* paramrelic)
{
	paramrelic->coupd=coupD;

	return;
}

/*--------------------------------------------------------------*/

void Init_quintessence(double T12, double n2, double T23, double n3, double T34, double n4, struct relicparam* paramrelic)
{
	if(paramrelic->phi_model)
	{
		paramrelic->energy_model=0;
		return;
	}

	paramrelic->energy_model=3;
	paramrelic->dd0=0.;
    paramrelic->use_table_rhoPD=paramrelic->size_table_rhoPD=0;

	paramrelic->quintn2=n2;
	paramrelic->quintn3=n3;
	paramrelic->quintn4=n4;
	paramrelic->quintT12=T12;
	paramrelic->quintT23=T23;
	paramrelic->quintT34=T34;

	return;
}

/*--------------------------------------------------------------*/

void Init_dark_entropy(double sd0, double nsd, double T_end, struct relicparam* paramrelic)
{
	if(paramrelic->phi_model) return;

	paramrelic->sd0=sd0;
	paramrelic->nsd=nsd;
	paramrelic->Tsend=T_end;

    paramrelic->use_table_rhoPD=paramrelic->size_table_rhoPD=0;

	return;
}

/*--------------------------------------------------------------*/

void Init_dark_entropySigmaD(double Sigmad0, double nSigmad, double T_end, struct relicparam* paramrelic)
{
	if(paramrelic->phi_model) return;

	paramrelic->Sigmad0=Sigmad0;
	paramrelic->nSigmad=nSigmad;
	paramrelic->TSigmadend=T_end;

    paramrelic->use_table_rhoPD=paramrelic->size_table_rhoPD=0;

	return;
}

/*--------------------------------------------------------------*/

void Init_entropySigmarad(double Sigmarad0, double nSigmarad, double T_end, struct relicparam* paramrelic)
{
	if(paramrelic->phi_model) return;

	paramrelic->Sigmarad0=Sigmarad0;
	paramrelic->nSigmarad=nSigmarad;
	paramrelic->TSigmaradend=T_end;

    paramrelic->use_table_rhoPD=paramrelic->size_table_rhoPD=0;

	return;
}

/*--------------------------------------------------------------*/

void Init_nonthermal(double nt0, double nnt, double T_end, struct relicparam* paramrelic)
{
	if(paramrelic->phi_model) return;

	paramrelic->nt0=nt0;
	paramrelic->nnt=nnt;
	paramrelic->Tnend=T_end;

    paramrelic->use_table_rhoPD=paramrelic->size_table_rhoPD=0;

	return;
}
/*--------------------------------------------------------------*/

void Init_gravitino(double mgravitino, struct relicparam* paramrelic)
{
	paramrelic->mgravitino=mgravitino;

	return;
}

/*--------------------------------------------------------------*/

void Init_scalarfield(double rhotilde_phi_Tmax, double Tmax, double T_RH, double eta_phi, double n_phi, struct relicparam* paramrelic)
{
	paramrelic->phi_model=1;
	paramrelic->full_comput=1;

	paramrelic->T_RH=T_RH;
	paramrelic->eta_phi=eta_phi;  /* = b/m_phi */
	paramrelic->Gamma_phi=sqrt(4.*pow(pi,3.)*geff(T_RH,paramrelic)/45.)*T_RH*T_RH/Mplanck;
	paramrelic->rhot_phi_Tmax=rhotilde_phi_Tmax;
	paramrelic->Tmax=Tmax;
	paramrelic->n_phi=n_phi;

	paramrelic->rhot_phi0=paramrelic->rhot_phi_Tmax;

	Init_dark_density(0.,0.,0.,paramrelic);
	Init_dark_density2(0.,0.,0.,paramrelic);
	Init_dark_entropy(0.,0.,0.,paramrelic);
	Init_dark_entropySigmaD(0.,0.,0.,paramrelic);
	Init_entropySigmarad(0.,0.,0.,paramrelic);
	Init_nonthermal(0.,0.,0.,paramrelic);
	Init_dark_coupling(0,paramrelic);

    paramrelic->use_table_rhoPD=paramrelic->size_table_rhoPD=0;

	return;
}

/*--------------------------------------------------------------*/

void Init_dark_density_table(double table[2][NTABMAX], int nlines, relicparam* paramrelic)
{
	Init_dark_density(0.,0.,0.,paramrelic);
	Init_dark_density2(0.,0.,0.,paramrelic);
	Init_dark_entropy(0.,0.,0.,paramrelic);
	Init_dark_entropySigmaD(0.,0.,0.,paramrelic);
	Init_entropySigmarad(0.,0.,0.,paramrelic);
	Init_nonthermal(0.,0.,0.,paramrelic);

	paramrelic->use_table_rhoPD=1;

	int ie,je;

	paramrelic->size_table_rhoPD=nlines;
	for(ie=0;ie<=1;ie++) for(je=0;je<nlines;je++) paramrelic->table_rhoPD[ie][je]=table[ie][je];

	return;
}


/*--------------------------------------------------------------*/

void Init_neutron_decay(double tau, double tau_err, double fierz, double m_chi, double B_chi, relicparam* paramrelic)
{
    paramrelic->life_neutron=tau;
    paramrelic->life_neutron_error=tau_err; // Neutron lifetime uncertainty (PDG2017)
    paramrelic->wimp=0;
	paramrelic->m_chi=m_chi;
	paramrelic->g_chi=0;
	paramrelic->SMC_wimp=0;
	paramrelic->selfConjugate=0;
	paramrelic->fermion=0;
	paramrelic->EM_coupled=0;
	paramrelic->neut_coupled=0;
	paramrelic->neuteq_coupled=0;
	paramrelic->fierz=fierz;			// no fierz interface in the standard model
	paramrelic->B_chi=B_chi;			// default is no branching to dark matter m_p < m_chi < m_n
	paramrelic->beta_samples=1000;		// if we are gonna simulate beta decay, we're gonna simulate it.
}


/*--------------------------------------------------------------*/

double dark_density(double T, struct relicparam* paramrelic)
{
	if(paramrelic->phi_model) return 0.;

	if(paramrelic->size_table_rhoPD>1&&paramrelic->use_table_rhoPD)
	{
		int ie=1;

		if(T<paramrelic->table_rhoPD[0][paramrelic->size_table_rhoPD-1])
		{
			// ie=paramrelic->size_table_rhoPD-1;
			return 0.; // if T is outside the range of the field, there is no dark density
		}
		else if(T<paramrelic->table_rhoPD[0][0]&&T>paramrelic->table_rhoPD[0][paramrelic->size_table_rhoPD-1])
		{
			while(T<paramrelic->table_rhoPD[0][ie]&&ie<paramrelic->size_table_rhoPD) ie++;
		}

		double logrhoD1,logrhoD2,rhoD,logT1,logT2,logT;
		logT=log(T);
		logrhoD1=log(paramrelic->table_rhoPD[1][ie]+1.);
		logrhoD2=log(paramrelic->table_rhoPD[1][ie-1]+1.);
		logT1=log(paramrelic->table_rhoPD[0][ie]+1.);
		logT2=log(paramrelic->table_rhoPD[0][ie-1]+1.);

		rhoD=exp((logrhoD2-logrhoD1)/(logT2-logT1)*(logT-logT1)+logrhoD1)-1.;
		// printf("T = %f, rhoD = %e \n", T, rhoD);

		return rhoD;
	}

	if(T<paramrelic->Tdend) return 0.;


	if(paramrelic->energy_model==3)
	{
		double H0=67.8/3.0856e19; /* Hubble constant in second */
		double rho_Lambda=0.7*H0*H0/(8.*pi*Gn)/2.322e17;

		if(T<=paramrelic->quintT12) return rho_Lambda;

		double rho02=rho_Lambda;
		if(T<=paramrelic->quintT23) return rho02*pow(T/paramrelic->quintT12,paramrelic->quintn2);

		double rho03=rho02*pow(paramrelic->quintT23/paramrelic->quintT12,paramrelic->quintn2);
		if(T<=paramrelic->quintT34) return rho03*pow(T/paramrelic->quintT23,paramrelic->quintn3);

		double rho04=rho03*pow(paramrelic->quintT34/paramrelic->quintT23,paramrelic->quintn3);
		return rho04*pow(T/paramrelic->quintT34,paramrelic->quintn4);
	}

	if(paramrelic->energy_model==2)
	{
		if(paramrelic->Tddeq==0.) return 0.;

		double geffT=geff(T,paramrelic);
		double rhorad=pi*pi/30.*geffT*pow(T,4.);

		return rhorad*(geff(paramrelic->Tddeq,paramrelic)/geffT)*pow(heff(T,paramrelic)/heff(paramrelic->Tddeq,paramrelic),paramrelic->ndd/3.)*pow(T/paramrelic->Tddeq,paramrelic->ndd);
	}

	if(paramrelic->energy_model==1)
	{
		if(paramrelic->dd0==0.) return 0.;

		double rho_photon_1MeV=pi*pi/15.*1.e-12;

		return paramrelic->dd0*rho_photon_1MeV*pow(T/1.e-3,paramrelic->ndd);
	}

	return 0.;
}


double dark_density_pressure(double T, struct relicparam* paramrelic)
{
	if(paramrelic->phi_model) return 0.;

	if(T<paramrelic->Tdend) return 0.;

	if(paramrelic->energy_model==1) if(paramrelic->dd0==0.) return 0.;

	if(paramrelic->energy_model==2) if(paramrelic->Tddeq==0.) return 0.;

	double ddark_density_dT=(dark_density(T*1.001,paramrelic)-dark_density(T*0.999,paramrelic))/0.002/T;

	double dentropy_dT=2.*pi*pi/45.*(heff(T*1.001,paramrelic)*pow(T*1.001,3.)-heff(T*0.999,paramrelic)*pow(T*0.999,3.))/0.002/T+dark_entropy_derivative(T,paramrelic);

	double entropy=2.*pi*pi/45.*heff(T,paramrelic)*pow(T,3.)+dark_entropy(T,paramrelic);

	//return (paramrelic->ndd/3.-1.)*dark_density(T,paramrelic); /* outdated */
	return (ddark_density_dT-dentropy_dT/entropy*dark_density(T,paramrelic))*entropy/dentropy_dT;
}

/*--------------------------------------------------------------*/

double sigma_entropy(double T, struct relicparam* paramrelic)
{
	if(paramrelic->phi_model) return 1.;

	if(paramrelic->Sigmarad0==0.) return 1.;

	double lnT,dlnT,Ttmp;
	int ie,nmax;
	double integ=0.;

	double heffT,geffT,darkdensitytilde,heffTdT,geffTdT,darkdensitytildeTdT,Htilde;
	double Sigmatildestar,dSigmatildestar_dT;

	nmax=10;

	lnT=log(1.e-15);

	dlnT=(log(T)-lnT)/nmax;

	for(ie=1;ie<nmax;ie++)
	{
		lnT+=dlnT;
		Ttmp=exp(lnT);

		heffT=heff(Ttmp,paramrelic);
		geffT=geff(Ttmp,paramrelic);
		darkdensitytilde=dark_density(Ttmp,paramrelic)/(pi*pi/30.*geffT*pow(Ttmp,4.));

		Htilde=sqrt(1.+darkdensitytilde); /*Htilde = H / sqrt(8 pi / 3 M_P^2) / rho_rad */

		Sigmatildestar=45.*sqrt(5.)/4./pow(pi,3.5)*Mplanck/heffT/sqrt(geffT)/pow(Ttmp,5.)/Htilde*entropy_Sigmarad(Ttmp,paramrelic);

		heffTdT=heff(Ttmp*1.001,paramrelic);
		geffTdT=geff(Ttmp*1.001,paramrelic);
		darkdensitytildeTdT=dark_density(Ttmp*1.001,paramrelic)/(pi*pi/30.*geffTdT*pow(Ttmp*1.001,4.));

		dSigmatildestar_dT=((45.*sqrt(5.)/4./pow(pi,3.5)*Mplanck/heffTdT/sqrt(geffTdT)/pow(Ttmp*1.001,5.)/sqrt(1.+darkdensitytildeTdT)*entropy_Sigmarad(Ttmp*1.001,paramrelic))-Sigmatildestar)/0.001/Ttmp;

		integ+=-dSigmatildestar_dT/pow(1.-Sigmatildestar,2.)*log(heffT*pow(Ttmp,3.));
	}

	heffT=heff(T,paramrelic);
	geffT=geff(T,paramrelic);
	darkdensitytilde=dark_density(T,paramrelic)/(pi*pi/30.*geffT*pow(T,4.));

	Htilde=sqrt(1.+darkdensitytilde); /*Htilde = H / sqrt(8 pi / 3 M_P^2) / rho_rad */

	Sigmatildestar=45.*sqrt(5.)/4./pow(pi,3.5)*Mplanck/heffT/sqrt(geffT)/pow(T,5.)/Htilde*entropy_Sigmarad(T,paramrelic);

	heffTdT=heff(T*1.001,paramrelic);
	geffTdT=geff(T*1.001,paramrelic);
	darkdensitytildeTdT=dark_density(T*1.001,paramrelic)/(pi*pi/30.*geffTdT*pow(T*1.001,4.));

	dSigmatildestar_dT=((45.*sqrt(5.)/4./pow(pi,3.5)*Mplanck/heffTdT/sqrt(geffTdT)/pow(T*1.001,5.)/sqrt(1.+darkdensitytildeTdT)*entropy_Sigmarad(T*1.001,paramrelic))-Sigmatildestar)/0.001/T;

	integ+=-dSigmatildestar_dT/pow(1.-Sigmatildestar,2.)*log(heffT*pow(T,3.))/2.;

	integ*=dlnT;

	return exp(integ);
}


double dark_entropy(double T, struct relicparam* paramrelic)
{
	if(paramrelic->phi_model) return 0.;

	if((paramrelic->sd0==0.)&&(paramrelic->Sigmad0==0.)) return 0.;

	if((paramrelic->Sigmad0==0.)&&(T<paramrelic->Tsend)) return 0.;

	if(paramrelic->Sigmad0==0.)
	{
		double s_photon_1MeV=4.*pi*pi/45.*1.e-9;

		return paramrelic->sd0*s_photon_1MeV*pow(T/1.e-3,paramrelic->nsd);
	}
	else
	{
		double lnT,dlnT,Ttmp;
		int ie,nmax;
		double integ=0.;

		double heffT,geffT,darkdensitytilde,Htilde;
		double Sigmatildestar=0.;

		nmax=50;

		lnT=log(1.e-15);

		dlnT=(log(T)-lnT)/nmax;

		for(ie=1;ie<nmax;ie++)
		{
			lnT+=dlnT;
			Ttmp=exp(lnT);

			heffT=heff(Ttmp,paramrelic);
			geffT=geff(Ttmp,paramrelic);
			darkdensitytilde=dark_density(Ttmp,paramrelic)/(pi*pi/30.*geffT*pow(Ttmp,4.));

			Htilde=sqrt(1.+darkdensitytilde); /*Htilde = H / sqrt(8 pi / 3 M_P^2) / rho_rad */

			if(paramrelic->Sigmarad0!=0.) Sigmatildestar=45.*sqrt(5.)/4./pow(pi,3.5)*Mplanck/heffT/sqrt(geffT)/pow(Ttmp,5.)/Htilde*entropy_Sigmarad(Ttmp,paramrelic);

			integ+=sgStar(Ttmp,paramrelic)*dark_entropy_Sigmad(Ttmp,paramrelic)/Htilde/(1.-Sigmatildestar)/sigma_entropy(Ttmp,paramrelic)/pow(heffT*pow(Ttmp,3.),(2.-Sigmatildestar)/(1.-Sigmatildestar));
		}

		heffT=heff(T,paramrelic);
		geffT=geff(T,paramrelic);
		darkdensitytilde=dark_density(T,paramrelic)/(pi*pi/30.*geffT*pow(T,4.));

		Htilde=sqrt(1.+darkdensitytilde); /*Htilde = H / sqrt(8 pi / 3 M_P^2) / rho_rad */

		if(paramrelic->Sigmarad0!=0.) Sigmatildestar=45.*sqrt(5.)/4./pow(pi,3.5)*Mplanck/heffT/sqrt(geffT)/pow(T,5.)/Htilde*entropy_Sigmarad(T,paramrelic);

		integ+=sgStar(T,paramrelic)*dark_entropy_Sigmad(T,paramrelic)/Htilde/(1.-Sigmatildestar)/sigma_entropy(T,paramrelic)/pow(heffT*pow(T,3.),(2.-Sigmatildestar)/(1.-Sigmatildestar))/2.;

		integ*=dlnT;

		return Mplanck*sqrt(45./4./pow(pi,3.))*pow(heffT*pow(T,3.),1./(1.-Sigmatildestar))*sigma_entropy(T,paramrelic)*integ;
	}
}


double dark_entropy_derivative(double T, struct relicparam* paramrelic)
{
	if(paramrelic->phi_model) return 0.;

	if((paramrelic->sd0==0.)&&(paramrelic->Sigmad0==0.)) return 0.;

	if((paramrelic->Sigmad0==0.)&&(T<paramrelic->Tsend)) return 0.;

	if(paramrelic->Sigmad0==0.)
	{
		return paramrelic->nsd*dark_entropy(T,paramrelic)/T;
	}
	else
	{
		double heffT=heff(T,paramrelic);
		double geffT=geff(T,paramrelic);
		double sradT=2.*pi*pi/45.*heffT*pow(T,3.);
		double rhoradT=pi*pi/30.*geffT*pow(T,4.);
		double darkdensitytilde=dark_density(T,paramrelic)/rhoradT;
		double Sigmarad=entropy_Sigmarad(T,paramrelic);

		double Htilde=sqrt(1.+darkdensitytilde); /*Htilde = H / sqrt(8 pi / 3 M_P^2) / rho_rad */

		double Sigmatildestar=45.*sqrt(5.)/4./pow(pi,3.5)*Mplanck/heffT/sqrt(geffT)/pow(T,5.)/Htilde*Sigmarad;

		return 3.*sgStar(T,paramrelic)/T/(1.-Sigmatildestar)/heffT
		*(sqrt(geffT)*dark_entropy(T,paramrelic)
		-sqrt(5.*Mplanck/4./pow(pi,3.))/T/T*dark_entropy_Sigmad(T,paramrelic)/Htilde);
	}
}


double dark_entropy_Sigmad(double T, struct relicparam* paramrelic)
{
	if(paramrelic->phi_model) return 0.;

	if((paramrelic->sd0==0.)&&(paramrelic->Sigmad0==0.)) return 0.;

	if((paramrelic->Sigmad0==0.)&&(T<paramrelic->Tsend)) return 0.;

	if(paramrelic->Sigmad0==0.)
	{
		double heffT=heff(T,paramrelic);
		double geffT=geff(T,paramrelic);
		double sradT=2.*pi*pi/45.*heffT*pow(T,3.);
		double rhoradT=pi*pi/30.*geffT*pow(T,4.);
		double darkdensitytilde=dark_density(T,paramrelic)/rhoradT;
		double Sigmarad=entropy_Sigmarad(T,paramrelic);

		double Htilde=sqrt(1.+darkdensitytilde); /*Htilde = H / sqrt(8 pi / 3 M_P^2) / rho_rad */

		double Sigmatildestar=45.*sqrt(5.)/4./pow(pi,3.5)*Mplanck/heffT/sqrt(geffT)/pow(T,5.)/Htilde*Sigmarad;

		return sqrt(4.*pow(pi,3.)/5.)/Mplanck*Htilde*T*T*(sqrt(geffT)*dark_entropy(T,paramrelic)-heffT/3./sgStar(T,paramrelic)*T*(1.-Sigmatildestar)*dark_entropy_derivative(T,paramrelic));
	}
	else
	{
		if(T<paramrelic->TSigmadend) return 0.;

		double s_photon_1MeV=4.*pi*pi/45.*1.e-9;

		double Sigma_photon_1MeV= 1./Mplanck*sqrt(8.*pi*pi*pi/5.)*(1.e-6)*s_photon_1MeV;

		return paramrelic->Sigmad0*Sigma_photon_1MeV*pow(T/1.e-3,paramrelic->nSigmad);
	}
}

/*--------------------------------------------------------------*/

double entropy_Sigmarad(double T, struct relicparam* paramrelic)
{
	if(paramrelic->phi_model) return 0.; //paramrelic->Gamma_phi*paramrelic->rho_phi/T;

	if((paramrelic->Sigmarad0==0.)||(T<paramrelic->TSigmaradend)) return 0.;

	double s_photon_1MeV=4.*pi*pi/45.*1.e-9;

	double Sigma_photon_1MeV=1./Mplanck*sqrt(8.*pi*pi*pi/5.)*(1.e-6)*s_photon_1MeV;

	return paramrelic->Sigmarad0*Sigma_photon_1MeV*pow(T/1.e-3,paramrelic->nSigmarad);
}

/*--------------------------------------------------------------*/

double nonthermal(double T, struct relicparam* paramrelic)
{
	if(paramrelic->phi_model) return 0.; //paramrelic->eta_phi*paramrelic->Gamma_phi*paramrelic->rho_phi;

	if((paramrelic->nt0==0.)||(T<paramrelic->Tnend)) return 0.;

	return paramrelic->nt0*1.e-50*pow(T/1.e-3,paramrelic->nnt);
}

/*--------------------------------------------------------------*/

double neutdens(double Tnu, struct relicparam* paramrelic)
/* Computes the neutrino density, including any effects from a neutrino degeneracy */
{
    if((paramrelic->xinu1==0.)&&(paramrelic->xinu2==0.)&&(paramrelic->xinu3==0.))
    {
        /* No degeneracy, relativistic approximation */
        return 2.*pi*pi/30.*7./8.*paramrelic->Nnu*pow(Tnu,4.);
    }

    int ie,je,n;
    double rho=0.;
    double xinu[4];
    double max1,max2,int1,int2;
    double x;

    xinu[1]=paramrelic->xinu1;
    xinu[2]=paramrelic->xinu2;
    xinu[3]=paramrelic->xinu3;

    /* SM neutrinos */
    for(ie=1;ie<=3;ie++)
    {
        /* The factor (paramrelic->Nnu/3.) includes extra DOF from non-rel. e+- and non-inst. nu decoupling */
        if(fabs(xinu[ie])<=0.03)
        {
            rho+=(paramrelic->Nnu/3.)*2.*pi*pi/30.*pow(Tnu,4.)*(7./8.+(15./(4*pi*pi))*xinu[ie]*xinu[ie]+
                                                               (15./(8.*pow(pi,4.)))*pow(xinu[ie],4.));
        }
        else if(fabs(xinu[ie])>=30.)
        {
            rho+=(paramrelic->Nnu/3.)*pow(Tnu,4.)/(8.*pi*pi)*pow(xinu[ie],4.)*(1.+12.*1.645/xinu[ie]/xinu[ie]);
        }
        else
        {
            /* Neutrinos */
            max1=(88.029+xinu[ie])*Tnu;
            int1=0.;
            n=50;
            for(je=1;je<=n-1;je++)
            {
                x=(double)je/(double)n*max1;
                int1+=1./(2.*pi*pi)*pow(x,3.)/(1.+exp(x/Tnu-xinu[ie]));
            }
            int1+=0.5*1./(2.*pi*pi)*pow(max1,3.)/(1.+exp(max1/Tnu-xinu[ie]));
            int1*=(paramrelic->Nnu/3.)*max1/(double)n;
            rho+=int1;

            /* Anti-neutrinos */
            max2=(88.029-xinu[ie])*Tnu;
            if(max2>0.)
            {
                int2=0.;
                n=50;
                for(je=1;je<=n-1;je++)
                {
                    x=(double)je/(double)n*max2;
                    int2+=1./(2.*pi*pi)*pow(x,3.)/(1.+exp(x/Tnu+xinu[ie]));
                }
                int2+=0.5/(2.*pi*pi)*pow(max2,3.)/(1.+exp(max2/Tnu+xinu[ie]));
                int2*=(paramrelic->Nnu/3.)*max2/(double)n;
                rho+=int2;
            }
        }
    }
    return rho;
}

/*--------------------------------------------------------------*/

double neutdens_deriv(double Tnu, struct relicparam* paramrelic)
/* Computes the temperature (Tnu) derivative of the neutrino energy density */
{
    if((paramrelic->xinu1==0.)&&(paramrelic->xinu2==0.)&&(paramrelic->xinu3==0.))
    {
        return 7.*pi*pi/30.*paramrelic->Nnu*pow(Tnu,3.);
    }

    int ie,je,n;
    double drho=0.;
    double xinu[4];
    double max1,max2,int1,int2;
    double x;

    xinu[1]=paramrelic->xinu1;
    xinu[2]=paramrelic->xinu2;
    xinu[3]=paramrelic->xinu3;

    /* SM neutrinos */
    for(ie=1;ie<=3;ie++)
    {
        if(fabs(xinu[ie])<=0.03)
        {
            drho+=(paramrelic->Nnu/3.)*4.*pi*pi/15.*pow(Tnu,3.)*(7./8.+(15./(4*pi*pi))*xinu[ie]*xinu[ie]
                                                                +(15./(8.*pow(pi,4.)))*pow(xinu[ie],4.));
        }
        else if(fabs(xinu[ie])>=30.)
        {
            drho+=(paramrelic->Nnu/3.)*pow(Tnu,3.)/(2.*pi*pi)*pow(xinu[ie],4.)*(1.+12.*1.645/xinu[ie]/xinu[ie]);
        }
        else
        {
            max1=(88.029+xinu[ie])*Tnu;
            int1=0.;
            n=50;
            for(je=1;je<=n-1;je++)
            {
                x=(double)je/(double)n*max1;
                int1+=1./(2.*pi*pi)*pow(x,3.)/(1.+exp(x/Tnu-xinu[ie]));
            }
            int1+=0.5*1./(2.*pi*pi)*pow(max1,3.)/(1.+exp(max1/Tnu-xinu[ie]));
            int1*=(paramrelic->Nnu/3.)*4.*max1/Tnu/(double)n;
            drho+=int1;

            max2=(88.029-xinu[ie])*Tnu;
            if(max2>0.)
            {
                int2=0.;
                n=50;
                for(je=1;je<=n-1;je++)
                {
                    x=(double)je/(double)n*max2;
                    int2+=1./(2.*pi*pi)*pow(x,3.)/(1.+exp(x/Tnu+xinu[ie]));
                }
                int2+=0.5/(2.*pi*pi)*pow(max2,3.)/(1.+exp(max2/Tnu+xinu[ie]));
                int2*=(paramrelic->Nnu/3.)*4.*max2/Tnu/(double)n;
                drho+=int2;
            }
        }
    }
    return drho;
}

/*--------------------------------------------------------------*/

double neutN(double T)
/* Computes the round N(z) function of the neutrinos - Pisanti et al., 0705.0290, eq. (A24) */
{
	double z=m_e/T;

	if(z>=4.) return 0.;

	double logNz=0.;

	double n[14]={-10.21703221236002,61.24438067531452,-340.3323864212157,1057.2707914654834,-2045.577491331372,2605.9087171012848,-2266.1521815470196,1374.2623075963388,-586.0618273295763,174.87532902234145,-35.715878215468045,4.7538967685808755,-0.3713438862054167,0.012908416591272199};

	int ie;
	for(ie=0;ie<14;ie++) logNz+=n[ie]*pow(z,ie);

	return exp(logNz);
}
