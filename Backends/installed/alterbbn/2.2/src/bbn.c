#include "include.h"

//#define DEBUG
//#define OUTPUT

/*----------------------------------------------------*/

int linearize(double T, const double reacparam[NNUCREACMAX+1][10], double f[NNUCREACMAX+1], double r[NNUCREACMAX+1], int loop, int inc, int ip, double dt, double Y0[NNUC+1], double Y[NNUC+1], double dY_dt[NNUC+1], double rhob)
/* solves for new abundances using gaussian elimination with back substitution */
{
	if(T>27.) // T in GK. At high temperature only n<->p conversions matter
	{
		dY_dt[1]=-f[1]*Y[1]+r[1]*Y[2];
		dY_dt[2]=-dY_dt[1];

		int ie;
		for(ie=3;ie<=NNUC;ie++) dY_dt[ie]=0.;

		return 0;
	}

    int i,j,g,h,k,l,n,i1,j1,ind,rn1,rn2,rn3,rn4,rn5,rn6;
    double cn1,cn2,cn3,cn4,cn5,cn6,yY[NNUC+1];
    cn1=cn2=cn3=cn4=cn5=cn6=0.;
    int fail;
#ifdef DEBUG
    int ierror;
#endif
    int type[NNUCREAC+1],n1[NNUCREAC+1],n2[NNUCREAC+1],n3[NNUCREAC+1],
            n4[NNUCREAC+1],n5[NNUCREAC+1],n6[NNUCREAC+1];
    double rev[NNUCREAC+1],q9[NNUCREAC+1];
    double a[NNUC+1][NNUC+1],b[NNUC+1],yx[NNUC+1];
    int icnvm;
    double x[NNUC+1], a0[NNUC+1][NNUC+1], cx, sum, xdy, t;
    int nord,test;

    for (i=1;i<=NNUCREAC;i++)
    {
        type[i]=(int)reacparam[i][1];
        n1[i]=(int)reacparam[i][2];
        n2[i]=(int)reacparam[i][3];
        n3[i]=(int)reacparam[i][4];
        n4[i]=(int)reacparam[i][5];
        n5[i]=(int)reacparam[i][6];
        n6[i]=(int)reacparam[i][7];
        rev[i]=reacparam[i][8];
        q9[i]=reacparam[i][9];
    }

	memset(a, 0.,sizeof(double) * (NNUC+1) * (NNUC+1));

#if defined(_OPENMP) && NMAX>30
#pragma omp parallel for private(ind,i,j,g,h,k,l,rn1,rn2,rn3,rn4,rn5,rn6,cn1,cn2,cn3,cn4,cn5,cn6)
#endif
    for (n=1;n<=NNUCREAC;n++)
    {
        ind=type[n];
        i=n1[n];
        j=n2[n];
        g=n3[n];
        h=n4[n];
        k=n5[n];
        l=n6[n];
        if (i <= NNUC && l <= NNUC)
        {
			rn6=ind%10;
			rn5=(ind%100-rn6)/10;
			rn4=(ind%1000-10*rn5-rn6)/100;
			rn3=(ind%10000-100*rn4-10*rn5-rn6)/1000;
			rn2=(ind%100000-1000*rn3-100*rn4-10*rn5-rn6)/10000;
			rn1=(ind-10000*rn2-1000*rn3-100*rn4-10*rn5-rn6)/100000;

			if(ind!=100001) r[n]=rev[n]*pow(rhob,rn4+rn5+rn6-1.)*pow(0.987e10*pow(T,1.5),rn1+rn2+rn3-rn4-rn5-rn6)*exp(-q9[n]/T)*f[n];
			f[n]=pow(rhob,rn1+rn2+rn3-1.)*f[n];
			cn1=(rn1*pow(Y[i],rn1-1.)*pow(Y[j],rn2)*pow(Y[g],rn3))/((rn1+rn2+rn3)*factorial(rn1)*factorial(rn2)*factorial(rn3))*f[n]*dt;
			if(rn2==0) cn2=0.; else cn2=(rn2*pow(Y[j],rn2-1.)*pow(Y[i],rn1)*pow(Y[g],rn3))/((rn1+rn2+rn3)*factorial(rn1)*factorial(rn2)*factorial(rn3))*f[n]*dt;
			if(rn3==0) cn3=0.; else cn3=(rn3*pow(Y[g],rn1-1.)*pow(Y[j],rn2)*pow(Y[i],rn1))/((rn1+rn2+rn3)*factorial(rn1)*factorial(rn2)*factorial(rn3))*f[n]*dt;
			if(rn4==0) cn4=0.; else cn4=(rn4*pow(Y[h],rn4-1.)*pow(Y[k],rn5)*pow(Y[l],rn6))/((rn4+rn5+rn6)*factorial(rn4)*factorial(rn5)*factorial(rn6))*r[n]*dt;
			if(rn5==0) cn5=0.; else cn5=(rn5*pow(Y[k],rn5-1.)*pow(Y[h],rn4)*pow(Y[l],rn6))/((rn4+rn5+rn6)*factorial(rn4)*factorial(rn5)*factorial(rn6))*r[n]*dt;
			cn6=(rn6*pow(Y[l],rn6-1.)*pow(Y[k],rn5)*pow(Y[h],rn4))/((rn4+rn5+rn6)*factorial(rn4)*factorial(rn5)*factorial(rn6))*r[n]*dt;

            // Invert indexes
            i=NNUC+1-i;
            j=NNUC+1-j;
            g=NNUC+1-g;
            h=NNUC+1-h;
            k=NNUC+1-k;
            l=NNUC+1-l;

            // Fill i (n1) nuclide column
#if defined(_OPENMP) && NMAX>30
#pragma omp atomic
#endif
            a[i][i]+=rn1*cn1;
            if(j<=NNUC)
#if defined(_OPENMP) && NMAX>30
#pragma omp atomic
#endif
            a[j][i]+=rn2*cn1;
            if(g<=NNUC)
#if defined(_OPENMP) && NMAX>30
#pragma omp atomic
#endif
            a[g][i]+=rn3*cn1;
            if(h<=NNUC)
#if defined(_OPENMP) && NMAX>30
#pragma omp atomic
#endif
            a[h][i]-=rn4*cn1;
            if(k<=NNUC)
#if defined(_OPENMP) && NMAX>30
#pragma omp atomic
#endif
            a[k][i]-=rn5*cn1;
#if defined(_OPENMP) && NMAX>30
#pragma omp atomic
#endif
            a[l][i]-=rn6*cn1;

            // Fill j (n2) nuclide column
            if (j<=NNUC)
            {
#if defined(_OPENMP) && NMAX>30
#pragma omp atomic
#endif
                a[i][j]+=rn1*cn2;
#if defined(_OPENMP) && NMAX>30
#pragma omp atomic
#endif
                a[j][j]+=rn2*cn2;
                if(g<=NNUC)
#if defined(_OPENMP) && NMAX>30
#pragma omp atomic
#endif
                a[g][j]+=rn3*cn2;
                if(h<=NNUC)
#if defined(_OPENMP) && NMAX>30
#pragma omp atomic
#endif
                a[h][j]-=rn4*cn2;
                if(k<=NNUC)
#if defined(_OPENMP) && NMAX>30
#pragma omp atomic
#endif
                a[k][j]-=rn5*cn2;
#if defined(_OPENMP) && NMAX>30
#pragma omp atomic
#endif
                a[l][j]-=rn6*cn2;
            }

            // Fill g (n3) nuclide column
            if (g<=NNUC)
            {
#if defined(_OPENMP) && NMAX>30
#pragma omp atomic
#endif
                a[i][g]+=rn1*cn3;
                if(j<=NNUC)
#if defined(_OPENMP) && NMAX>30
#pragma omp atomic
#endif
                a[j][g]+=rn2*cn3;
#if defined(_OPENMP) && NMAX>30
#pragma omp atomic
#endif
                a[g][g]+=rn3*cn3;
                if(h<=NNUC)
#if defined(_OPENMP) && NMAX>30
#pragma omp atomic
#endif
                a[h][g]-=rn4*cn3;
                if(k<=NNUC)
#if defined(_OPENMP) && NMAX>30
#pragma omp atomic
#endif
                a[k][g]-=rn5*cn3;
#if defined(_OPENMP) && NMAX>30
#pragma omp atomic
#endif
                a[l][g]-=rn6*cn3;
            }

            // Fill h (n4) nuclide column
            if (h<=NNUC)
            {
#if defined(_OPENMP) && NMAX>30
#pragma omp atomic
#endif
                a[i][h]-=rn1*cn4;
                if(j<=NNUC)
#if defined(_OPENMP) && NMAX>30
#pragma omp atomic
#endif
                a[j][h]-=rn2*cn4;
                if(g<=NNUC)
#if defined(_OPENMP) && NMAX>30
#pragma omp atomic
#endif
                a[g][h]-=rn3*cn4;
#if defined(_OPENMP) && NMAX>30
#pragma omp atomic
#endif
                a[h][h]+=rn4*cn4;
                if(k<=NNUC)
#if defined(_OPENMP) && NMAX>30
#pragma omp atomic
#endif
                a[k][h]+=rn5*cn4;
#if defined(_OPENMP) && NMAX>30
#pragma omp atomic
#endif
                a[l][h]+=rn6*cn4;
            }

            // Fill k (n5) nuclide column
            if (k<=NNUC)
            {
#if defined(_OPENMP) && NMAX>30
#pragma omp atomic
#endif
                a[i][k]-=rn1*cn5;
                if(j<=NNUC)
#if defined(_OPENMP) && NMAX>30
#pragma omp atomic
#endif
                a[j][k]-=rn2*cn5;
                if(g<=NNUC)
#if defined(_OPENMP) && NMAX>30
#pragma omp atomic
#endif
                a[g][k]-=rn3*cn5;
                if(h<=NNUC)
#if defined(_OPENMP) && NMAX>30
#pragma omp atomic
#endif
                a[h][k]+=rn4*cn5;
#if defined(_OPENMP) && NMAX>30
#pragma omp atomic
#endif
                a[k][k]+=rn5*cn5;
#if defined(_OPENMP) && NMAX>30
#pragma omp atomic
#endif
                a[l][k]+=rn6*cn5;
            }

            // Fill l (n6) nuclide column
#if defined(_OPENMP) && NMAX>30
#pragma omp atomic
#endif
            a[i][l]-=rn1*cn6;
            if(j<=NNUC)
#if defined(_OPENMP) && NMAX>30
#pragma omp atomic
#endif
            a[j][l]-=rn2*cn6;
            if(g<=NNUC)
#if defined(_OPENMP) && NMAX>30
#pragma omp atomic
#endif
            a[g][l]-=rn3*cn6;
            if(h<=NNUC)
#if defined(_OPENMP) && NMAX>30
#pragma omp atomic
#endif
            a[h][l]+=rn4*cn6;
            if(k<=NNUC)
#if defined(_OPENMP) && NMAX>30
#pragma omp atomic
#endif
            a[k][l]+=rn5*cn6;
#if defined(_OPENMP) && NMAX>30
#pragma omp atomic
#endif
            a[l][l]+=rn6*cn6;
        }
    }

    // Finish the A matrix
    for(i=1;i<=NNUC;i++)
    {
        if((a[i][i]+=1.)==0.)  // Add identity matrix
        {
			fail=i;
			return fail;	// If zeros at pivot points, terminate matrix evaluation
		};

        b[NNUC+1-i]=Y0[i];                                            // Initial abundances
    }

    if(loop==1) icnvm=ip; else icnvm=0;

    nord=0;
    fail=0;
    // Set RH and solution vectors to initial values
    for(i=1;i<=NNUC;i++)
    {
        x[i]=b[i];
        yx[i]=0.;
    }
    // Save matrix
    if(icnvm==inc) memcpy(a0, a, sizeof(a));

    // Triangularize matrix
    for(i=1;i<=NNUC;i++)
    {
        for(j=i+1;j<=NNUC;j++)
        {
            if(a[j][i]!=0.)
            {
                cx=a[j][i]/a[i][i];
                for(k=i+1;k<=NNUC;k++) a[j][k]-=cx*a[i][k];
                a[j][i]=cx;
                x[j]-=cx*x[i];
            }
        }
    }

    // Back substitution
    do
    {	x[NNUC]/=a[NNUC][NNUC];
        yx[NNUC]+=x[NNUC];

        for(i=NNUC-1;i>=1;i--)
        {
            sum=0.;
            for(j=i+1;j<=NNUC;j++) sum+=a[i][j]*x[j];
            x[i]=(x[i]-sum)/a[i][i];
            yx[i]+=x[i];
        }

        test=1;

        if(icnvm==inc)
        {
            for(i=1;i<=NNUC;i++)
            {
                if(yx[i]!=0.)
                {
                    xdy=fabs(x[i]/yx[i]);

                    if(xdy>2.e-4)
                    {
                        if(nord<1)
                        {
                            nord++;

                            for(j=1;j<=NNUC;j++)
                            {
                                t = 0.;
                                for(k=1;k<=NNUC;k++) t+=a0[j][k]*yx[k];
                                x[j]=b[j]-t;
                            }

                            for(j=2;j<=NNUC;j++) for(k=j+1;k<=NNUC;k++) x[k]-=a[k][j]*x[j];
                            break;
                        }
                        else
                        {
                            fail=-1;
#ifdef DEBUG
                            ierror=i;
#endif
                            return fail;
                        }
                    }
                    else test=0;
                }
                else test=0;
            }
        }
        else test=0;
    }
    while(test);

    // Derivatives of abundances
    for(i=1;i<=NNUC;i++)
    {
        yY[i]=yx[NNUC+1-i];
        dY_dt[i]=(yY[i]-Y0[i])/dt;
    }

#ifdef DEBUG
    if(fail!=0)
    {
        if(fail==-1) printf("y(%d) failed to converge\n",ierror);
        if(fail>=1) printf("%d th diagonal term equals zero\n",fail);
    }
#endif
    return fail;
}

/*----------------------------------------------------*/

int fill_params(double T, double Tnu, double phie, double h_eta, double a, double rho_phi, double dt0, double* dT, double* dTnu, double* dphie, double* dh_eta, double* da, double* drhophi, double dY_dt[NNUC+1], double Y0[NNUC+1], double Y[NNUC+1], const double Am[NNUC+1], const double Zm[NNUC+1], const double Dm[NNUC+1], const double reacparam[NNUCREAC+1][10], double norm, int loop, int inc, int ip, struct relicparam* paramrelic, struct errorparam* paramerror)
/* Routine computing the time-derivatives of T, phie, h_eta, a, rho_phi and Y[] */
{
	int i;
	int fail;

	for(i=0;i<=NNUC;i++) dY_dt[i]=0.;

    double f[NNUCREACMAX+1],r[NNUCREACMAX+1];

    for(i=0;i<=NNUCREACMAX;i++)
    {
        f[i] = 0.;
        r[i] = 0.;
    }

    if(T<=27.*K_to_eV) rate_weak(f,paramrelic,paramerror); // Do not compute at high temperature

	/* ########### DARK ENERGY DENSITY AND ENTROPY ########### */
	double rhod=dark_density(T,paramrelic);
	double Pd=dark_density_pressure(T,paramrelic);
	double drhod_dT=0.;
	if(rhod>0.) drhod_dT=(dark_density(1.001*T,paramrelic)-rhod)/(0.001*T);

	double sd=dark_entropy(T,paramrelic);
	double dsd_dT=dark_entropy_derivative(T,paramrelic);

	double Sigmarad=entropy_Sigmarad(T,paramrelic);

	if(paramrelic->phi_model&&rho_phi!=0.) Sigmarad=paramrelic->Gamma_phi*rho_phi/T;

	double z=m_e/T;

	double Tvar,zW,wimp_mass_ratio;

    if (paramrelic->wimp)
    {
        wimp_mass_ratio = paramrelic->m_chi / 1.e3 / m_e;

		if (paramrelic->EM_coupled) Tvar=T;
		else Tvar=Tnu;
		zW = wimp_mass_ratio*z*T/Tvar;
	}

	double cosh1, cosh2, cosh3, cosh4, cosh5, cosh6, cosh7, sinh1, sinh2, sinh3, sinh4, sinh5, sinh6, sinh7;

	if (phie<=17.)
	{
		cosh1=cosh(phie);
		cosh2=cosh(phie*2.);
		cosh3=cosh(phie*3.);
		cosh4=cosh(phie*4.);
		cosh5=cosh(phie*5.);
		cosh6=cosh(phie*6.);
		cosh7=cosh(phie*7.);
		sinh1=sinh(phie);
		sinh2=sinh(phie*2.);
		sinh3=sinh(phie*3.);
		sinh4=sinh(phie*4.);
		sinh5=sinh(phie*5.);
		sinh6=sinh(phie*6.);
		sinh7=sinh(phie*7.);
	}
	else
	{
		cosh1=0.;
		cosh2=0.;
		cosh3=0.;
		cosh4=0.;
		cosh5=0.;
		cosh6=0.;
		cosh7=0.;
		sinh1=0.;
		sinh2=0.;
		sinh3=0.;
		sinh4=0.;
		sinh5=0.;
		sinh6=0.;
		sinh7=0.;
	}

	/* ############ PHOTON DENSITY AND PRESSURE ############# */
	double rho_gamma=pow(pi,2.)/15.*pow(T,4.);
	double drho_gamma_dT=rho_gamma*4./T;
	double P_gamma=rho_gamma/3.;

	/* ############ ELECTRON AND POSITRON DENSITY AND PRESSURE ########## */

	double rho_epem=(Mbessel(z)*cosh1-Mbessel(2.*z)*cosh2+Mbessel(3.*z)*
			  cosh3-Mbessel(4.*z)*cosh4+Mbessel(5.*z)*cosh5-
			  Mbessel(6.*z)*cosh6+Mbessel(7.*z)*cosh7)*2.*pow(m_e,4.)/pow(pi,2.);
			  /* rho_e+ + rho_e- */

	double drho_epem_dT=z/T*(Nbessel(z)*cosh1-Nbessel(2.*z)*2.*
							  cosh2+Nbessel(3.*z)*3.*cosh3-
							  Nbessel(4.*z)*4.*cosh4+Nbessel(5.*z)*
							  5.*cosh5-Nbessel(6.*z)*6.*cosh6+
							  Nbessel(7.*z)*7.*cosh7)*2.*pow(m_e,4.)/pow(pi,2.);
							  /* d(rho_e+ + rho_e-)/d(T) */

	double drho_epem_dphie=(Mbessel(z)*sinh1-Mbessel(2.*z)*2.*sinh2+
					 Mbessel(3.*z)*3.*sinh3-Mbessel(4.*z)*4.*sinh4+
					 Mbessel(5.*z)*5.*sinh5-Mbessel(6.*z)*6.*sinh6+
					 Mbessel(7.*z)*7.*sinh7)*2.*pow(m_e,4.)/pow(pi,2.);
					 /* d(rho_e+ + rho_e-)/d(phie) */

	double P_epem=(Lbessel(z)*cosh1/z-Lbessel(2.*z)*cosh2/(z*2.)+
			Lbessel(3.*z)*cosh3/(z*3.)-Lbessel(4.*z)*cosh4/(z*4.)+
			Lbessel(5.*z)*cosh5/(z*5.)-Lbessel(6.*z)*cosh6/(z*6.)+
			Lbessel(7.*z)*cosh7/(z*7.))*2.*pow(m_e,4.)/pow(pi,2.); /* P_e+ + P_e- */

	/* ########## WIMP DENSITY AND PRESSURE ########### */
	double rho_wimp,P_wimp,drho_wimp_dTvar;
	rho_wimp=P_wimp=drho_wimp_dTvar=0.;

	if (paramrelic->wimp)
	{
		if (paramrelic->fermion) // fermionic wimp
		{
			rho_wimp=(Mbessel(zW)-Mbessel(2.*zW)+Mbessel(3.*zW)-Mbessel(4.*zW)
					  +Mbessel(5.*zW)-Mbessel(6.*zW)+Mbessel(7.*zW))
					*pow(paramrelic->m_chi/1.e+3,4.)*paramrelic->g_chi/(2.*pi*pi);
			P_wimp=(Lbessel(zW)/zW-Lbessel(2.*zW)/(zW*2.)+Lbessel(3.*zW)/(zW*3.)
					-Lbessel(4.*zW)/(zW*4.)+Lbessel(5.*zW)/(zW*5.)-Lbessel(6.*zW)/(zW*6.)
					+Lbessel(7.*zW)/(zW*7.))*pow(paramrelic->m_chi/1.e3,4.)*paramrelic->g_chi/(2.*pi*pi);
			/* Note that for self conj. particles, the factor cosh(n*phiW) is replaced by exp(n*phiW).
			 * However, we assume phiW=0 for those particles, and the double counting of
			 * non-self conj. particles is baked into the definition of g_chi, so it makes no difference,
			 * since cosh(0)=exp(0)=1. If, in the future, a varying phiW is to be implemented, the
			 * difference must be taken into account */
			drho_wimp_dTvar=(1./Tvar)*pow(paramrelic->m_chi/1.e3,4.)*paramrelic->g_chi*
					(zW*Nbessel(zW)-
					 2.*zW*Nbessel(2.*zW)+
					 3.*zW*Nbessel(3.*zW)-
					 4.*zW*Nbessel(4.*zW)+
					 5.*zW*Nbessel(5.*zW)-
					 6.*zW*Nbessel(6.*zW)+
					 7.*zW*Nbessel(7.*zW))/(2.*pi*pi);
		}
		else // bosonic wimp
		{
			rho_wimp=(Mbessel(zW)+Mbessel(2.*zW)+Mbessel(3.*zW)+Mbessel(4.*zW)
					  +Mbessel(5.*zW)+Mbessel(6.*zW)+Mbessel(7.*zW))
					*pow(paramrelic->m_chi/1.e3,4.)*paramrelic->g_chi/(2.*pi*pi);
			P_wimp=(Lbessel(zW)/zW+Lbessel(2.*zW)/(zW*2.)+Lbessel(3.*zW)/(zW*3.)
					+Lbessel(4.*zW)/(zW*4.)+Lbessel(5.*zW)/(zW*5.)+Lbessel(6.*zW)/(zW*6.)
					+Lbessel(7.*zW)/(zW*7.))
					*pow(paramrelic->m_chi/1.e3,4.)*paramrelic->g_chi/(2.*pi*pi);
			drho_wimp_dTvar=(1./Tvar)*pow(paramrelic->m_chi/1.e3,4.)*paramrelic->g_chi*
					(zW*Nbessel(zW)+
					 2.*zW*Nbessel(2.*zW)+
					 3.*zW*Nbessel(3.*zW)+
					 4.*zW*Nbessel(4.*zW)+
					 5.*zW*Nbessel(5.*zW)+
					 6.*zW*Nbessel(6.*zW)+
					 7.*zW*Nbessel(7.*zW))/(2.*pi*pi);
		}
	}

	/* ########### NEUTRINO DENSITY ############ */

	double Ti=paramrelic->Tinit*K_to_eV;
	double Tnud=paramrelic->Tnudec*K_to_eV;

	double rho_neutrinos=neutdens(Tnu,paramrelic);
	double P_neutrinos=0.;
	double drho_neutrinos_dTnu=0.;
	double rho_neuteq=0.;
	double P_neuteq=0.;
	double drho_neuteq=0.;
	double Tnu_eq=Tnu;

	P_neutrinos=rho_neutrinos/3.;
	drho_neutrinos_dTnu=neutdens_deriv(Tnu,paramrelic);

	if((paramrelic->wimp)&&((paramrelic->neut_coupled)||(paramrelic->neuteq_coupled)))
	{
		if (paramrelic->neut_coupled)
		{
			// Equivalent neutrinos have their own temperature and are decoupled, thus derivative is zero
			rho_neuteq=2.*pow(pi,2.)/30.*7./8.*paramrelic->dNnu*pow(Tnu_eq,4.);
			drho_neuteq=0.;
		}
		else
		{
			// Common SM and equivalent neutrino temperature
			rho_neuteq=2.*pow(pi,2.)/30.*7./8.*paramrelic->dNnu*pow(Tnu,4.);
			drho_neuteq=7.*pow(pi,2.)/30.*paramrelic->dNnu*pow(Tnu,3.);
		}
		P_neuteq=rho_neuteq/3.;
	}
	else
	{
		// SM and equivalent neutrinos share same temperature
		rho_neuteq=2.*pow(pi,2.)/30.*7./8.*paramrelic->dNnu*pow(Tnu,4.);
		P_neuteq=rho_neuteq/3.;
		drho_neuteq=7.*pow(pi,2.)/30.*paramrelic->dNnu*pow(Tnu,3.);
	}

	/* ############### BARYON DENSITY ################ */
	double rho_baryons=h_eta*pow(T,3.);

	double rho_cdm=0.;
	if(!paramrelic->wimp) rho_cdm=rho_baryons/paramrelic->b_cdm_ratio;

	double dM_epem_dT=-(pow(z,3.)/T)*(sinh1*(Lbessel(z)*3.-z*Mbessel(z))-sinh2*
                                     (Lbessel(2.*z)*3.-z*2.*Mbessel(2.*z))+
                                     sinh3*(Lbessel(3.*z)*3.-z*3.*
                                            Mbessel(3.*z))-sinh4*
                                     (Lbessel(4.*z)*3.-z*4.*Mbessel(4.*z))+
                                     sinh5*(Lbessel(5.*z)*3.-z*5.*
                                            Mbessel(5.*z))-sinh6*
                                     (Lbessel(6.*z)*3.-z*6.*Mbessel(6.*z))+
                                     sinh7*(Lbessel(7.*z)*3.-z*7.*
                                            Mbessel(7.*z)));
                                     /* d(pi^2 (ne- - ne+)*z^3 /
                                      * 2 m^3) / d(T) */

    double dN_epem_dphie=pow(z,3.)*(cosh1*Lbessel(z)-cosh2*2.*Lbessel(2.*z)+
                                 cosh3*3.*Lbessel(3.*z)-cosh4*4.*Lbessel(4.*z)+
                                 cosh5*5.*Lbessel(5.*z)-cosh6*6.*Lbessel(6.*z)+
                                 cosh7*7.*Lbessel(7.*z));
	if(dN_epem_dphie!=0.) dN_epem_dphie=1./dN_epem_dphie;
				/* d(pi^2/2 1/M_u h sum Z_i Y_i)/d(phie) */

	// scaling factor Ffunc for the symmetron model
	double Ffunc = Ffunc_Hscaling(T, paramrelic);
	rhod = 0.0;

	// Summing up all energy densities from different sources
	double H=Ffunc*sqrt(G*8.*pi/3.*(rho_gamma+rho_epem+rho_wimp+rho_neutrinos+rho_neuteq+rho_baryons+rho_cdm+rhod+rho_phi));

	rate_pn(f,r,T/K_to_eV,Tnu/K_to_eV,paramrelic,paramerror); // conversion to CGS units

	f[1]*=norm;
	r[1]*=norm;

	if(T<=27.*K_to_eV) rate_all(f,T/K_to_eV,paramrelic,paramerror); // Do not compute at high temperature - conversion to CGS units

	if(T<=1.e-2) // Only use linearize below 10 MeV, otherwise compute dY_dt from the distribution functions (see end of the routine)
	{
		fail=linearize(T/K_to_eV,reacparam,f,r,loop,inc,ip,dt0/s_to_GeV,Y0,Y,dY_dt,rho_baryons/g_to_GeV*pow(cm_to_GeV,3.)); // conversion to CGS units

		for(i=1;i<=NNUC;i++)
		{
			dY_dt[i] = dY_dt[i]/s_to_GeV; // we get derivatives back in GeV
		}
	}
	else fail=0;

	if(fail!=0) return 1;

	double sum_Y=0.;
	double sum_ZY=0.;
	double sum_dY_dt=0.;
	double sum_DeltaMdY_dt=0.;
	double sum_ZdY_dt=0.;

	for (i=1;i<=NNUC;i++)
	{
		sum_Y+=Y[i];
		sum_ZY+=Zm[i]*Y[i];
		sum_dY_dt+=dY_dt[i];
		sum_DeltaMdY_dt+=Dm[i]/1000.*dY_dt[i]/(M_u*g_to_GeV);
		sum_ZdY_dt+=Zm[i]*dY_dt[i];
	}

	double dphie_dT=dN_epem_dphie*(-3.*pow(pi,2.)/(2.*M_u*g_to_GeV)*h_eta*sum_ZY/T-dM_epem_dT);
	double dphie_dlna3=-dN_epem_dphie*pow(pi,2.)/(2.*M_u*g_to_GeV)*h_eta*sum_ZY;
	double dphie_dZY=dN_epem_dphie*pow(pi,2.)/(2.*M_u*g_to_GeV)*h_eta;

	double dlna3_dT,dlna3_dTnu;
	dlna3_dT=dlna3_dTnu=0.;

	if((paramrelic->wimp)&&((paramrelic->neut_coupled)||(paramrelic->neuteq_coupled)))
	{
		// WIMPs are coupled to neutrinos, so need to dynamically vary Tnu
		if (paramrelic->neuteq_coupled)
		{
			dlna3_dTnu=-(drho_neutrinos_dTnu+drho_neuteq+drho_wimp_dTvar)/(rho_neutrinos+P_neutrinos+rho_neuteq+P_neuteq+rho_wimp+P_wimp-pow(T,4.)/3.*neutN(T));
		}
		else
		{
			dlna3_dTnu=-(drho_neutrinos_dTnu+drho_wimp_dTvar)/(rho_neutrinos+P_neutrinos+rho_wimp+P_wimp-pow(T,4.)/3.*neutN(T));
		}

		// No WIMP contribution to dlna3_dT, since they are not EM coupled
		dlna3_dT=-(drho_gamma_dT+drho_epem_dT+drho_epem_dphie*dphie_dT+rho_baryons*zeta*sum_Y
					+paramrelic->coupd*drhod_dT-T*dsd_dT)/
				(rho_gamma+P_gamma+rho_epem+P_epem+rho_baryons*(2./3.*zeta*T*sum_Y+zeta*T*sum_dY_dt/(H*3.)+sum_DeltaMdY_dt/(H*3.))
				 +paramrelic->coupd*(rhod+Pd)-T*sd+drho_epem_dphie*(dphie_dlna3+dphie_dZY*sum_ZdY_dt/(H*3.))-T*Sigmarad/(H*3.));
	}
	else
	{
		dlna3_dTnu=-(drho_neutrinos_dTnu+drho_neuteq)/(rho_neutrinos+P_neutrinos+rho_neuteq+P_neuteq-pow(T,4.)/3.*neutN(T));

		// No WIMPs (relevant WIMP parameters set to 0 earlier), or EM coupled WIMPs
		dlna3_dT=-(drho_gamma_dT+drho_epem_dT+drho_epem_dphie*dphie_dT+(rho_baryons*K_to_eV)*zeta*sum_Y
					+paramrelic->coupd*drhod_dT-T*dsd_dT+drho_wimp_dTvar)/
				(rho_gamma+P_gamma+rho_epem+P_epem+rho_baryons*(2./3.*zeta*T*sum_Y+zeta*T*sum_dY_dt/(H*3.)+sum_DeltaMdY_dt/(H*3.))
				 +paramrelic->coupd*(rhod+Pd)-T*sd+drho_epem_dphie*(dphie_dlna3+dphie_dZY*sum_ZdY_dt/(H*3.))+rho_wimp+P_wimp-T*Sigmarad/(H*3.));
	}

	double dTnu_dt,dT_dt;
	if(isinf(dlna3_dTnu)) dTnu_dt=0.; else dTnu_dt=3.*H/dlna3_dTnu;
	if(isinf(dlna3_dT)) dT_dt=0.; dT_dt=3.*H/dlna3_dT;

	double dlnT_dt=dT_dt/T;
	double dh_dt=-3.*h_eta*(H+dlnT_dt);
	double dphie_dt=dphie_dT*dT_dt+dphie_dlna3*(H*3.)+dphie_dZY*sum_ZdY_dt;
	double da_dt=H*a;

	double drhophi_dt=0.;
	if(paramrelic->phi_model&&rho_phi!=0.) drhophi_dt=-(paramrelic->n_phi*H+paramrelic->Gamma_phi)*rho_phi;

	*dT=dT_dt;
	*dTnu=dTnu_dt;
	*dphie=dphie_dt;
	*dh_eta=dh_dt;
	*da=da_dt;
	*drhophi=drhophi_dt;

	if(T>1.e-2) // At high temperatures, evaluate dY_dt for protons, neutrons and deuterium from their distribution functions
	{
		dY_dt[1] = (1./(exp(DMpn/(T+*dT*dt0))+1.) - 1./(exp(DMpn/T)+1.)) /dt0;
        dY_dt[2] = (1./(exp(-DMpn/(T+*dT*dt0))+1.) - 1./(exp(-DMpn/T)+1.)) /dt0;
        dY_dt[3] = (1./(reacparam[12][8])/0.987e10*1./(exp(DMpn/(T+*dT*dt0))+1.)*1./(exp(-DMpn/(T+*dT*dt0))+1.)*(paramrelic->rhob0/g_to_GeV*pow(cm_to_GeV,3.))*exp(reacparam[12][9]*K_to_eV/(T+*dT*dt0))/pow((T+*dT*dt0)/K_to_eV,1.5) - 1./(reacparam[12][8])/0.987e10*1./(exp(DMpn/T)+1.)*1./(exp(-DMpn/T)+1.)*(paramrelic->rhob0/g_to_GeV*pow(cm_to_GeV,3.))*exp(reacparam[12][9]*K_to_eV/T)/pow(T/K_to_eV,1.5)) /dt0;
    }

	return 0;
}

/*----------------------------------------------------*/

int nucl_single(struct relicparam* paramrelic, double ratioH[NNUC+1], struct errorparam* paramerror)
/* Main routine which computes the abundance ratios H2_H, ..., Be7_H as well as
 * the baryon-to-photon ratio eta, using the parameters contained in paramrelic
 * The err parameter is a switch to choose if the central (err=0), high (err=1)
 * or low (err=2) values of the nuclear rates is used. If (err=3),
 * the lower value of only the nuclear rate number "errnumber" is used. If (err=4),
 * the value of the nuclear rates is taken randomly (gaussian distribution) for a
 * MC analysis. */
{
	if(paramrelic->err==3) if((paramerror->errnumber<0)||(paramerror->errnumber>NNUCREAC+1)) return 1;

	if((paramrelic->err==3)&&(paramerror->errnumber==NNUCREAC+1)) paramerror->life_neutron=paramrelic->life_neutron+paramrelic->life_neutron_error;
	else if(paramrelic->err==4) paramerror->life_neutron=paramrelic->life_neutron+paramrelic->life_neutron_error*paramerror->random[NNUCREAC+1];
	else paramerror->life_neutron=paramrelic->life_neutron;

    int i;
	memset(ratioH, 0.,sizeof(double) * (NNUC+1));

#ifdef OUTPUT
	FILE *output;
	if(paramrelic->err==0) output=fopen("evolution.out","w");
	if(paramrelic->err==0) fprintf(output,"t (s)\t\ta\t\t\tT (GK)\t\tTnu (GK)\tphotons\t\tbaryons\t\tneutrinos\tphi (GeV^4)\tY(n)\t\tY(p)\t\tY(2H)\t\tY(4He)\t\tY(7Li)\t\teta\n");

#endif

    double f[NNUCREACMAX+1],r[NNUCREACMAX+1];
    double sd;
    double rhod,Pd,rhodprev,sum_Y;
    double drhod_dT=0;
    double sum_dY_dt, sum_ZY, dsd_dT, dphie_dT, dlna3_dT, dphie_dlna3,
            dphie_dZY, sum_DeltaMdY_dt, sum_ZdY_dt;
    double cosh1, cosh2, cosh3, cosh4, cosh5, cosh6, cosh7, sinh1, sinh2, sinh3,
            sinh4, sinh5, sinh6, sinh7;
    double cosh1W, cosh2W, cosh3W, cosh4W, cosh5W, cosh6W, cosh7W;
    double sinh1W, sinh2W, sinh3W, sinh4W, sinh5W, sinh6W, sinh7W;
    double T0,h_eta0,phie0,phiW0,a0;
    double dtl;
    int loop;
    double dh_dt, dphie_dt, dT_dt, dlnT_dt, dphiW_dt;
    double dT0_dt, dh_dt0, dphie_dt0,dphiW0_dt;
    double dlna3_dTnu,dTnu_dt,dlnTnu_dt,Tnu0,dTnu0_dt;
    double dY_dt0[NNUC+1],dY_dt[NNUC+1],Y0[NNUC+1],Y0b[NNUC+1],Y[NNUC+1];
    double rho_phi0;
    double rho_phi,drhophi_dt;
	double da_dt,da_dt0;
    double dtmin;
    double z;               // Parameterized electron mass -> z = m_e*c^2 / (k_B*T)
    double H;               // Hubble parameter
    double zW;              // Parameterized WIMP mass -> zW = m_WIMP*c^2 / (k_B*T)
    double wimp_mass_ratio; // Ratio between WIMP mass and electron mass
    double zWd;             // Value of zW at neutrino decoupling temperature Tnud
    double phiW;            // Parameterized WIMP chemical potential

    dTnu_dt=wimp_mass_ratio=zW=dlna3_dT=dphie_dt0=dh_dt0=dT0_dt=da_dt0=phie0=h_eta0=T0=a0=Tnu0=dTnu0_dt=phiW0=dphiW0_dt=0.;

#ifdef REACLIB
#include "bbn.h"

#else
    /* Nuclides: 1=n, 2=p, 3=H2, 4=H3, 5=He3, 6=He4, 7=Li6, 8=Li7, 9=Be7, 10=Li8, 11=B8, 12=Be9, 13=B10, 14=B11, 15=C11, 16=B12, 17=C12, 18=N12, 19=C13, 20=N13, 21=C14, 22=N14, 23=O14, 24=N15, 25=O15, 26=O16 */

    const char name[NNUCMAX+1][6] = {"","n","p","H2","H3","He3","He4","Li6","Li7","Be7","Li8","B8","Be9","B10","B11","C11","B12","C12","N12","C13","N13","C14","N14","O14","N15","O15","O16"};

    const double Am[NNUCMAX+1] = {0.,1.,1.,2.,3.,3.,4.,6.,7.,7.,8.,8.,9.,10.,11.,11.,12.,12.,12.,13.,13.,14.,14.,14.,15.,15.,16.}; /* Atomic number A */

    const double Zm[NNUCMAX+1] = {0.,0.,1.,1.,1.,2.,2.,3.,3.,4.,3.,5.,4.,5.,5.,6.,5.,6.,7.,6.,7.,6.,7.,8.,7.,8.,8.}; /* Charge number Z */

    const double Dm[NNUCMAX+1] = {0.,8.071388,7.289028,13.135825,14.949915,14.931325,2.424931,14.0864,14.9078,15.7696,20.9464,22.9212,11.34758,12.05086,8.6680,10.6506,13.3690,0.,17.3382,3.125036,5.3455,3.019916,2.863440,8.006521,0.101439,2.8554,-4.737036}; /* mass excess DeltaM in MeV */

	const double spin[NNUCMAX+1] = {0.,0.5,0.5,1.,0.5,0.5,0.,1.,1.5,1.5,2.,2.,1.5,3.,1.5,1.5,1.,0.,1.,0.5,0.5,0.,1.,0.,0.5,0.5,0.};

    const double reacparam[NNUCREACMAX+1][10] =
    {

// type: #n1#n2#n3#n4#n5#n6
// n1: incoming nuclide number
// n2: incoming light nuclide number
// n3: incoming lightest nuclide number
// n4: outgoing lightest nuclide number
// n5: outgoing light nuclide number
// n6: outgoing nuclide number
// rev: reverse reaction coefficient
// q: energy release in reaction in 10**9 Kelvin (K = ev/k_B)

//   reac# type n1 n2 n3 n4 n5 n6 rev q

    {0,0,0,0,0,0,0,0,0.,0.},                   // none
    {1,100001,1,0,0,0,0,2,0.,0.},              // n -> p
    {2,100001,4,0,0,0,0,5,0.,0.},              // H3 -> e- + v + He3
    {3,100002,10,0,0,0,0,6,0.,0.},             // Li8 -> e- + v + 2 He4
    {4,100001,16,0,0,0,0,17,0.,0.},            // B12 -> e- + v + C12
    {5,100001,21,0,0,0,0,22,0.,0.},            // C14 -> e- + v + N14
    {6,100002,11,0,0,0,0,6,0.,0.},             // B8 -> e+ + v + 2 He4
    {7,100001,15,0,0,0,0,14,0.,0.},            // C11 -> e+ + v + B11
    {8,100001,18,0,0,0,0,17,0.,0.},            // N12 -> e+ + v + C12
    {9,100001,20,0,0,0,0,19,0.,0.},            // N13 -> e+ + v + C13
    {10,100001,23,0,0,0,0,22,0.,0.},           // O14 -> e+ + v + N14
    {11,100001,25,0,0,0,0,24,0.,0.},           // O15 -> e+ + v + N15
    {12,110001,2,1,0,0,0,3,0.477,25.815},      // H + n -> g + H2
    {13,110001,3,1,0,0,0,4,1.65,72.612},       // H2 + n -> g + H3
    {14,110001,5,1,0,0,0,6,2.63,238.794},      // He3 + n -> g + He4
    {15,110001,7,1,0,0,0,8,1.20,84.132},       // Li6 + n -> g + Li7
    {16,110011,5,1,0,0,2,4,1.001,8.863},       // He3 + n -> p + H3
    {17,110011,9,1,0,0,2,8,1.001,19.080},      // Be7 + n -> p + Li7
    {18,110011,7,1,0,0,4,6,1.068,55.503},      // Li6 + n -> He4 + H3
    {19,110002,9,1,0,0,0,6,4.68,220.382},      // Be7 + n -> He4 + He4
    {20,110001,3,2,0,0,0,5,1.65,63.749},       // H2 + p -> g + He3
    {21,110001,4,2,0,0,0,6,2.63,229.931},      // H3 + p -> g + He4
    {22,110001,7,2,0,0,0,9,1.20,65.053},       // Li6 + p -> g + Be7
    {23,110011,7,2,0,0,5,6,1.067,46.640},      // Li6 + p -> He4 + He3
    {24,110002,8,2,0,0,0,6,4.68,201.302},      // Li7 + p -> He4 + He4
    {25,110001,6,3,0,0,0,7,1.55,17.109},       // H2 + He4 -> g + Li6
    {26,110001,6,4,0,0,0,8,1.13,28.629},       // H3 + He4 -> g + Li7
    {27,110001,6,5,0,0,0,9,1.13,18.412},       // He3 + He4 -> g + Be7
    {28,200011,3,0,0,0,1,5,1.73,37.934},       // 2 H2 -> n + He3
    {29,200011,3,0,0,0,2,4,1.73,46.798},       // 2 H2 -> p + H3
    {30,110011,4,3,0,0,1,6,5.51,204.116},      // H3 + H2 -> n + He4
    {31,110011,5,3,0,0,2,6,5.51,212.979},      // He3 + H2 -> p + He4
    {32,200021,5,0,0,0,2,6,3.35,149.229},      // 2 He3 -> 2 p + He4
    {33,110012,8,3,0,0,1,6,9.81,175.487},      // Li7 + H2 -> n + He4 + He4
    {34,110012,9,3,0,0,2,6,9.83,194.566},      // Be7 + H2 -> p + He4 + He4
    {35,110001,5,4,0,0,0,7,2.47,183.290},      // He3 + H3 -> g + Li6
    {36,110011,7,3,0,0,1,9,2.52,39.237},       // Li6 + H2 -> n + Be7
    {37,110011,7,3,0,0,2,8,2.52,58.317},       // Li6 + H2 -> p + Li7
    {38,110011,5,4,0,0,3,6,1.59,166.181},      // He3 + H3 -> H2 + He4
    {39,200021,4,0,0,0,1,6,3.34,131.503},      // 2 H3 -> 2n + He4
    {40,110111,5,4,0,1,2,6,3.34,140.366},      // He3 + H3 -> n + p + He4
    {41,110011,8,4,0,0,1,12,3.55,121.136},     // Li7 + H3 -> n + Be9
    {42,110011,9,4,0,0,2,12,3.55,140.215},     // Be7 + H3 -> p + Be9
    {43,110011,8,5,0,0,2,12,3.55,129.999},     // Li7 + He3 -> p + Be9
    {44,110001,8,1,0,0,0,10,1.33,23.589},      // Li7 + n -> g + Li8
    {45,110001,13,1,0,0,0,14,3.07,132.920},    // B10 + n -> g + B11
    {46,110001,14,1,0,0,0,16,2.37,39.111},     // B11 + n -> g + B12
    {47,110011,15,1,0,0,2,14,1.001,32.086},    // C11 + n -> p + B11
    {48,110011,13,1,0,0,6,8,0.755,32.371},     // B10 + n -> He4 + Li7
    {49,110001,9,2,0,0,0,11,1.32,1.595},       // Be7 + p -> g + B8
    {50,110001,12,2,0,0,0,13,0.986,76.424},    // Be9 + p -> g + B10
    {51,110001,13,2,0,0,0,15,3.07,100.834},    // B10 + p -> g + C11
    {52,110001,14,2,0,0,0,17,7.10,185.173},    // B11 + p -> g + C12
    {53,110001,15,2,0,0,0,18,2.37,6.979},      // C11 + p -> g + N12
    {54,110011,16,2,0,0,1,17,3.00,146.061},    // B12 + p -> n + C12
    {55,110011,12,2,0,0,6,7,0.618,24.663},     // Be9 + p -> He4 + Li6
    {56,110011,13,2,0,0,6,9,0.754,13.291},     // B10 + p -> He4 + Be7
    {57,110011,16,2,0,0,6,12,0.291,79.903},    // B12 + p -> He4 + Be9
    {58,110001,7,6,0,0,0,13,1.60,51.761},      // Li6 + He4 -> g + B10
    {59,110001,8,6,0,0,0,14,4.07,100.549},     // Li7 + He4 -> g + B11
    {60,110001,9,6,0,0,0,15,4.07,87.543},      // Be7 + He4 -> g + C11
    {61,110011,11,6,0,0,2,15,3.07,85.948},     // B8 + He4 -> p + C11
    {62,110011,10,6,0,0,1,14,3.07,76.960},     // Li8 + He4 -> n + B11
    {63,110011,12,6,0,0,1,17,10.28,66.158},    // Be9 + He4 -> n + C12
    {64,110011,12,3,0,0,1,13,2.06,50.609},     // Be9 + H2 -> n + B10
    {65,110011,13,3,0,0,2,14,6.42,107.105},    // B10 + H2 -> p + B11
    {66,110011,14,3,0,0,1,17,14.85,159.357},   // B11 + H2 -> n + C12
    {67,210001,6,1,0,0,0,12,0.600,18.262},     // 2 He4 + n -> g + Be9
    {68,300001,6,0,0,0,0,17,2.06,84.420},      // 3 He4 -> g + C12
    {69,110012,10,2,0,0,1,6,3.54,177.713},     // Li8 + p -> n + He4 + He4
    {70,110012,11,1,0,0,2,6,3.55,218.787},     // B8 + n -> p + He4 + He4
    {71,110012,12,2,0,0,3,6,0.796,7.554},      // Be9 + p -> H2 + He4 + He4
    {72,110003,14,2,0,0,0,6,3.45,100.753},     // B11 + p -> 2 He4 + He4
    {73,110003,15,1,0,0,0,6,3.46,132.838},     // C11 + n -> 2 He4 + He4
    {74,110001,17,1,0,0,0,19,0.898,57.400},    // C12 + n -> g + C13
    {75,110001,19,1,0,0,0,21,3.62,94.884},     // C13 + n -> g + C14
    {76,110001,22,1,0,0,0,24,2.74,125.715},    // N14 + n -> g + N15
    {77,110011,20,1,0,0,2,19,1.001,34.846},    // N13 + n -> p + C13
    {78,110011,22,1,0,0,2,21,3.00,7.263},      // N14 + n -> p + C14
    {79,110011,25,1,0,0,2,24,1.001,41.037},    // O15 + n -> p + N15
    {80,110011,25,1,0,0,6,17,0.707,98.659},    // O15 + n -> He4 + C12
    {81,110001,17,2,0,0,0,20,0.896,22.554},    // C12 + p -> g + N13
    {82,110001,19,2,0,0,0,22,1.21,87.621},     // C13 + p -> g + N14
    {83,110001,21,2,0,0,0,24,0.912,118.452},   // C14 + p -> g + N15
    {84,110001,20,2,0,0,0,23,3.62,53.705},     // N13 + p -> g + O14
    {85,110001,22,2,0,0,0,25,2.73,84.678},     // N14 + p -> g + O15
    {86,110011,24,2,0,0,0,26,3.67,140.733},    // N15 + p -> g + O16
    {87,110011,24,2,0,0,6,17,0.706,57.622},	   // N15 + p -> He4 + C12
    {88,110001,17,6,0,0,0,26,5.20,83.111},     // C12 + He4 -> g + O16
    {89,110011,13,6,0,0,2,19,9.35,47.134},     // B10 + He4 -> p + C13
    {90,110011,14,6,0,0,2,21,11.03,9.098},     // B11 + He4 -> p + C14
    {91,110011,15,6,0,0,2,22,3.68,33.921},     // C11 + He4 -> p + N14
    {92,110011,18,6,0,0,2,25,4.25,111.620},    // N12 + He4 -> p + O15
    {93,110011,20,6,0,0,2,26,5.80,60.557},     // N13 + He4 -> p + O16
    {94,110011,13,6,0,0,1,20,9.34,12.288},     // B10 + He4 -> n + N13
    {95,110011,14,6,0,0,1,22,3.67,1.835},      // B11 + He4 -> n + N14
    {96,110011,16,6,0,0,1,24,4.25,88.439},     // B12 + He4 -> n + N15
    {97,110011,19,6,0,0,1,26,5.79,25.711},     // C13 + He4 -> n + O16
    {98,110011,14,3,0,0,2,16,4.96,13.296},     // B11 + H2 -> p + B12
    {99,110011,17,3,0,0,2,19,1.88,31.585},     // C12 + H2 -> p + C13
    {100,110011,19,3,0,0,2,21,7.58,69.069}     // C13 + H2 -> p + C14
    };

#endif

	memset(f, 0.,sizeof(double) * (NNUCREAC+1));
	memset(r, 0.,sizeof(double) * (NNUCREAC+1));

    double norm=1.;
    if((paramrelic->wimp)||(paramrelic->xinu1!=0.))
    {
        double f_tmp[2],r_tmp[2];
        rate_pn_noerr(f_tmp,r_tmp,0.00001,0.00001,paramrelic,paramerror);
        norm=1./f_tmp[1]/paramerror->life_neutron;
    }

    /* Note that Neff0 and Neff are not used in the program after they are computed. However, since they are
     * observables in CMB measurements, they are important variables when considering the effect of light WIMPS. */
    double Neff0;                   // Part of Neff that is a function of the WIMP mass
    double Neff;                    // Effective number of neutrinos
    double Ti=paramrelic->Tinit*K_to_eV;    // Initial temperature in GeV
    double Tf=0.01*K_to_eV;                // Final temperature in GeV
    double Ytmin =1.e-30;
	double a=8.e-11;

	if(paramrelic->phi_model&&paramrelic->rhot_phi0!=0.) rho_phi=(paramrelic->rhot_phi0)*pow(pi,2.)/15.*pow(Ti,4.); else rho_phi=0.;

    /* Initialization of relevant temperatures.
     * T: photon/e+- temp. Also the WIMP temperature in the case of EM coupled WIMPs
     * Tnu: SM neutrino temp. Simply redshifted in the case of no WIMPs or EM coupled WIMPs.
     * Tnud: SM neutrino decoupling temp. Instantaneous decoupling at ~2 MeV assumed.
     * Tnu_eq: Temp. of the equivalent neutrinos. Same as Tnu except in the case of WIMPs that couple only to SM neutrinos.
     * Note that we do not need to separately account for the WIMP temp. since this is equal to either T or Tnu, depending
     * on their coupling to the SM particles.
     */
    double T=Ti;

    double Tprev=T;
    double Tnu=T;
    double Tnud=paramrelic->Tnudec*K_to_eV;   // Neutrino decoupling temperature
    double Tnu_eq=Tnu; // Temperature of the equivalent neutrinos. Same as Tnu except in the case of WIMPs with coupling=1

    if (DMpn / T > 58.)
    {
        Y[1] = Ytmin;
        Y[2] = 1.;
    }
    else if (DMpn / T < -58.)
    {
        Y[1] = 1.;
        Y[2] = Ytmin;
    }
    else
    {
        Y[1] = 1. / (exp(DMpn / T) + 1.);
        Y[2] = 1. / (exp(-DMpn / T) + 1.);
    }

    Y0[1]=Y0b[1]=Y[1];
    Y0[2]=Y0b[2]=Y[2];

    z=m_e/T;
    if (paramrelic->wimp)
    {
        wimp_mass_ratio = paramrelic->m_chi / 1.e3 / m_e;
        zW = wimp_mass_ratio*z;                         // Always, since T=Tnu initially
        zWd = wimp_mass_ratio*z*T/Tnud;                // In the case that the iteration starts earlier than Tnud
    }

    double rho_gamma,P_gamma,drho_gamma_dT;
    double rho_epem,P_epem,drho_epem_dT,drho_epem_dphie,dM_epem_dT,dN_epem_dphie;
    double rho_neutrinos,P_neutrinos,drho_neutrinos_dTnu,rho_neuteq,P_neuteq,drho_neuteq;
    double rho_baryons=0.;
    double rho_cdm=0.;
    double rho_wimp,P_wimp,drho_wimp_dTvar,rho_wimp_Tnud,P_wimp_Tnud,n_wimp,dn_wimp_dTvar_phiWpart,dn_wimp_dTvar_zpart;
    double entropy_wimp_gamma;  // Entropy of WIMP normalized to the photon entropy -> s(m_WIMP)/s_gamma
    double phi_chid;            // Entropy of WIMP at Tnud normalized to entropy of massless WIMP -> s(m_WIMP)/s(0)
    double Tvar=0.;

    drho_neutrinos_dTnu=P_neutrinos=0.;

   //-----------------------------------------------------------------
    rho_gamma=pow(pi,2.)/15.*pow(T,4.);
    if (paramrelic->wimp)
    {
        if (paramrelic->fermion)
        {
            rho_wimp=(Mbessel(zW)-Mbessel(2.*zW)+Mbessel(3.*zW)-Mbessel(4.*zW)+Mbessel(5.*zW)-Mbessel(6.*zW)
                      +Mbessel(7.*zW))*pow(paramrelic->m_chi/1.e+3,4.)*paramrelic->g_chi/(2.*pi*pi);
            P_wimp=(Lbessel(zW)/zW-Lbessel(2.*zW)/(zW*2.)+Lbessel(3.*zW)/(zW*3.)-Lbessel(4.*zW)/(zW*4.)
                    +Lbessel(5.*zW)/(zW*5.)-Lbessel(6.*zW)/(zW*6.)+Lbessel(7.*zW)/(zW*7.))
                    *pow(paramrelic->m_chi/1.e+3,4.)*paramrelic->g_chi/(2.*pi*pi);

        }
        else // bosonic wimp
        {
            rho_wimp=(Mbessel(zW)+Mbessel(2.*zW)+Mbessel(3.*zW)+Mbessel(4.*zW)+Mbessel(5.*zW)+Mbessel(6.*zW)
                      +Mbessel(7.*zW))*pow(paramrelic->m_chi/1.e+3,4.)*paramrelic->g_chi/(2.*pi*pi);
            P_wimp=(Lbessel(zW)/zW+Lbessel(2.*zW)/(zW*2.)+Lbessel(3.*zW)/(zW*3.)+Lbessel(4.*zW)/(zW*4.)
                    +Lbessel(5.*zW)/(zW*5.)+Lbessel(6.*zW)/(zW*6.)+Lbessel(7.*zW)/(zW*7.))
                    *pow(paramrelic->m_chi/1.e+3,4.)*paramrelic->g_chi/(2.*pi*pi);

        }

        if (paramrelic->EM_coupled)
        {
            entropy_wimp_gamma = (rho_wimp + P_wimp) / (4./3. * rho_gamma);
        }
        else
        {
            // Neutrino coupled WIMPs do not contribute to the total entropy IF we start at neutrino decoupling
            entropy_wimp_gamma = 0.;
        }
    }
    else
    {
        rho_wimp = 0.;
        P_wimp = 0.;
        drho_wimp_dTvar = 0.;
        entropy_wimp_gamma = 0.;
    }

    /* Find s_e/s_gamma assuming zero phie at early times */
    rho_epem=(Mbessel(z)-Mbessel(2.*z)+Mbessel(3.*z)-Mbessel(4.*z)+Mbessel(5.*z)-Mbessel(6.*z)+Mbessel(7.*z))*2.*pow(m_e,4.)/pow(pi,2.);
    P_epem=(Lbessel(z)/z-Lbessel(2.*z)/(z*2.)+Lbessel(3.*z)/(z*3.)-Lbessel(4.*z)/(z*4.)+Lbessel(5.*z)/(z*5.)-
            Lbessel(6.*z)/(z*6.)+Lbessel(7.*z)/(z*7.))*2.*pow(m_e,4.)/pow(pi,2.);
    double entropy_epem_gamma=(rho_epem+P_epem) / (4./3.*rho_gamma);

    /* The late-time (CMB-measured) value of eta (eta0) given by the user, together with entropy conservation is
     * used to approximate an initial value of eta, here parameterized through h_eta. eta is not constant
     * prior to e+- annihilation and is therefore evolved together with the temperature. */
    double h_eta;
    if(paramrelic->phi_model&&rho_phi!=0.&&paramrelic->T_RH>1.e-5) h_eta=paramrelic->eta0*M_u*g_to_GeV*2.*zeta3/pow(pi,2.)*(1. + entropy_epem_gamma + entropy_wimp_gamma + 3./4.*rho_phi/rho_gamma*pow(paramrelic->T_RH/Ti,paramrelic->n_phi-4.));
    else h_eta=paramrelic->eta0*M_u*g_to_GeV*2.*zeta3/pow(pi,2.)*(1. + entropy_epem_gamma + entropy_wimp_gamma);

    double phie=h_eta*Y[2]/(M_u*g_to_GeV)*pow(pi,2.)/(2.*pow(z,3.)*(Lbessel(z)-Lbessel(2.*z)*2.+Lbessel(3.*z)*3.-Lbessel(4.*z)*4.
                                                      +Lbessel(5.*z)*5.-Lbessel(6.*z)*6.+Lbessel(7.*z)*7.));

    paramrelic->rhob0=h_eta*pow(T,3.);              // Initial baryon density
	rho_baryons=paramrelic->rhob0;

    if(paramrelic->wimp) rho_cdm=0.; else rho_cdm=rho_baryons/paramrelic->b_cdm_ratio;  // Cold dark matter

    /* ############ FIND INITIAL TIME ########### */
    /* Strictly valid in the limit T->infty, but valid assumption for the high initial temp. here. */
    double t=sqrt(12.*pi*G*sigma_SB)/pow(Ti,2.);

	rhod=dark_density(Ti,paramrelic);

    if(paramrelic->wimp||rhod!=0.||rho_phi!=0.)
    {
        /* In the presence of a WIMP H is larger at a given time, thus t is smaller
         * at a given T. Assuming H proportional to t early on this leads to a correction factor H_SBBN/H_WIMP.
         * The same reasoning holds for any arbitrary dark density implemented. */
        double H_SBBN, H_WIMP;
        cosh1=cosh(phie);
        cosh2=cosh(phie*2.);
        cosh3=cosh(phie*3.);
        cosh4=cosh(phie*4.);
        cosh5=cosh(phie*5.);
        cosh6=cosh(phie*6.);
        cosh7=cosh(phie*7.);

        rho_neutrinos=neutdens(Tnu,paramrelic);
        rho_neuteq=2.*pow(pi,2.)/30.*7./8.*paramrelic->dNnu*pow(Tnu_eq,4.);
        rho_epem=(Mbessel(z)*cosh1-Mbessel(2.*z)*cosh2+Mbessel(3.*z)*
                  cosh3-Mbessel(4.*z)*cosh4+Mbessel(5.*z)*cosh5-
                  Mbessel(6.*z)*cosh6+Mbessel(7.*z)*cosh7)*2.*pow(m_e,4.)/pow(pi,2.);

        H_SBBN=sqrt(G*8.*pi/3.*(rho_gamma+rho_epem+rho_neutrinos+rho_neuteq+rho_baryons+rho_cdm));
        H_WIMP=sqrt(G*8.*pi/3.*(rho_gamma+rho_epem+rho_wimp+rho_neutrinos+rho_neuteq+rho_baryons+rho_cdm+rhod+rho_phi));

        t=t*H_SBBN/H_WIMP;
    }

    t*=s_to_GeV;

    Y[3]=1./(reacparam[12][8])/0.987e10*Y[1]*Y[2]*(paramrelic->rhob0/g_to_GeV*pow(cm_to_GeV,3.))*exp(reacparam[12][9]*K_to_eV/T)/pow(T/K_to_eV,1.5); // Initial statistical equilibrium of deuterium formation pre-BBN

	Y0[3]=Y[3];
	Y0b[3]=Y[3];

	for (i = 4; i <= NNUC; ++i)
    {
        Y[i]=Ytmin;
        Y0[i]=Y[i];
        Y0b[i]=Y[i];
   }

/* --------------------------------------- Integration part ------------------------------------------------------------ */

/* To be obtained recursively: T, h_eta, phie, Tnu, Y[i] */

	if(paramrelic->failsafe<5) /* Original order 2 method for stiff equations */
	{
		int inc=100;
		int ltime=0;
		int is=1;
		int ip=inc;
		int it=0;
		double cy,ct,dt0;
		int nitmax;

		if(paramrelic->failsafe==0)
		{
			/* Conservative limiting iteration values for optimization of computational time.
			 * If the changes in the abundances and/or temperature are too large, the program is redirected to
			 * another "failsafe" method, which does not try to optimize the computational time
			 * (see method nucl). */
			cy=0.5; // Limiting value of dY/dt which, together with ct, controls the step-size
			ct=0.1; // Limiting value of dT/dt
			dt0=1.e-2*s_to_GeV;
			nitmax=10;
		}
		else if(paramrelic->failsafe==1)
		{
			cy=0.25;                  // Limiting value of dY/dt which, together with ct, controls the step-size
			ct=0.01;                 // Limiting value of dT/dt
			dt0=1.e-10*s_to_GeV;
			nitmax=100;
		}
		else if(paramrelic->failsafe==2)
		{
			cy=0.1;                  // Limiting value of dY/dt which, together with ct, controls the step-size
			ct=0.005;                 // Limiting value of dT/dt
			dt0=1.e-10*s_to_GeV;
			nitmax=100;
		}
		else
		{
			cy=0.05;                  // Limiting value of dY/dt which, together with ct, controls the step-size
			ct=0.001;                 // Limiting value of dT/dt
			dt0=1.e-10*s_to_GeV;
			nitmax=1000;
		}

		cy*=pow(NNUC/26.,paramrelic->failsafe+1.);

		double dt=dt0;
		double drhophi_dt0;

		while(ltime == 0)
		{
			for(loop=1;loop<=2;loop++)
			{
				/* ########### DARK ENERGY DENSITY AND ENTROPY ########### */

				fill_params(T,Tnu,phie,h_eta,a,rho_phi,dt,&dT_dt,&dTnu_dt,&dphie_dt,&dh_dt,&da_dt,&drhophi_dt,dY_dt,Y0,Y,Am,Zm,Dm,reacparam,norm,loop,inc,ip,paramrelic,paramerror);

				dlnT_dt=dT_dt/T;

				if (T <= Tf || dt < fabs(1.e-16 / dlnT_dt) || ip == inc)
				{
					it++;

					if((it==nitmax)||(ip<inc)) ltime = 1;
				}

				if(loop==1)
				{
					if(ip==inc) ip=0;
					ip++;
					is++;
					if(is>3)
					{
						dtmin=fabs(1./dlnT_dt)*ct;
						for (i=1;i<=NNUC;i++)
						{
							if ((dY_dt[i]!=0.)&&(Y[i]>Ytmin))
							{
								dtl=(fabs(Y[i]/dY_dt[i]))*cy*(pow(log10(Y[i])/log10(Ytmin),2.)+1.);

								if (dtl<dtmin) dtmin=dtl;
							}
						}
						if (dtmin>dt*1.5) dtmin=dt*1.5;
						dt=dtmin;
					}

					t+=dt;

					T0=T;
					h_eta0=h_eta;
					phie0=phie;
					a0=a;

					dT0_dt=dT_dt;
					dh_dt0=dh_dt;
					dphie_dt0=dphie_dt;
					da_dt0=da_dt;

					T=T0+dT0_dt*dt;

					if(paramrelic->phi_model&&rho_phi!=0.)
					{
						rho_phi0=rho_phi;
						drhophi_dt0=drhophi_dt;
						rho_phi=max(0.,rho_phi0+drhophi_dt0*dt);
					}


					if(T<0||isnan(T)||isinf(T))
					{
						if(paramrelic->failsafe==0) paramrelic->failsafe=1;
						return 1;
					}

					h_eta=h_eta0+dh_dt0*dt;
					phie=phie0+dphie_dt0*dt;
					a=a0+da_dt0;

					Tnu0=Tnu;
					dTnu0_dt=dTnu_dt;
					Tnu=Tnu0+dTnu0_dt*dt;

					if ((paramrelic->wimp)&&((paramrelic->neut_coupled)||(paramrelic->neuteq_coupled)))
					{
						// Tnu as dynamic variable in case of neutrino coupled WIMPs
						if ((paramrelic->neut_coupled)&&(T<Tnud))
						{
							// If WIMPs are coupled only to SM neutrinos, Tnu_eq is proportional to a^-1 after neutrino decoupling
							Tnu_eq=pow(h_eta*pow(T,3.)/paramrelic->rhob0,1./3.)*Ti;
						}
						else
						{
							// If WIMPs are coupled to both sets of neutrinos, they all share the same temperature.
							Tnu_eq=Tnu;
						}
					}

					for (i=1;i<=NNUC;i++)
					{
						Y0[i]=Y[i];
						dY_dt0[i]=dY_dt[i];
						Y[i]=Y0[i]+dY_dt0[i]*dt;
						if(Y[i]<Ytmin) Y[i]=Ytmin;
					}
				}
				else /* if(loop==2) */
				{
					T=T0+(dT_dt+dT0_dt)*0.5*dt;
					h_eta=h_eta0+(dh_dt+dh_dt0)*0.5*dt;
					phie=phie0+(dphie_dt+dphie_dt0)*0.5*dt;
					a=a0+(da_dt+da_dt0)*0.5*dt;

					if(paramrelic->phi_model&&rho_phi!=0.) rho_phi=max(0.,rho_phi0+(drhophi_dt0+drhophi_dt)*0.5*dt);
					if(paramrelic->phi_model&&rho_phi!=0.) if(rho_phi<1.e-20*pow(pi,2.)/15.*pow(T,4.)) rho_phi=0.;

					Tnu=Tnu0+(dTnu_dt+dTnu0_dt)*0.5*dt;

					if ((paramrelic->wimp)&&((paramrelic->neut_coupled)||(paramrelic->neuteq_coupled)))
					{
						if ((paramrelic->neut_coupled)&&(T<Tnud)) Tnu_eq=pow(h_eta*pow(T,3.)/paramrelic->rhob0,1./3.)*Ti;
						else Tnu_eq=Tnu;
					}

					for (i=1;i<=NNUC;i++)
					{
						Y[i]=Y0[i]+(dY_dt[i]+dY_dt0[i])*0.5*dt;
						if (Y[i]<Ytmin) Y[i]=Ytmin;
					}

#ifdef OUTPUT
				if(paramrelic->err==0) fprintf(output,"%.5e\t%.5e\t%.5e\t%.5e\t%.5e\t%.5e\t%.5e\t%.5e\t%.5e\t%.5e\t%.5e\t%.5e\t%.5e\t%.5e\n",t/s_to_GeV,a,T/K_to_eV,Tnu/K_to_eV,pow(pi,2.)/15.*pow(T,4.),h_eta*pow(T,3.),neutdens(Tnu,paramrelic),rho_phi,Y[1],Y[2],Y[3],Y[6],Y[8],h_eta/(M_u*g_to_GeV*2.*zeta3/pow(pi,2.)));
#endif

				}
			}

#ifdef CHECKINTERM
			for (i=1;i<=NNUC;i++) if(Y[i]>Ylow) checklow[i]++;
#endif
		}
	}
	else if(paramrelic->failsafe<10) /* Original order 2 method for stiff equations with improved adaptative timestep */
	{
		double T_sav,h_eta_sav,phie_sav,Tnu_sav,Y_sav[NNUC+1],t_sav,a_sav;

		double t_sav2;
		double T1,T2,T_sav2;
		double h_eta1,h_eta2,h_eta_sav2;
		double phie1,phie2,phie_sav2;
		double Tnu1,Tnu2,Tnu_sav2;
		double Y1[NNUC+1],Y2[NNUC+1],Y_sav2[NNUC+1];
		double rhophi1,rhophi2,rhophi_sav,rhophi_sav2,drhophi_dt0;
		double a1,a2,a_sav2;

		double Ytest;
		double prec;
		double minprec;

		if(paramrelic->failsafe==5)
		{
			Ytest=1.e-25;
			prec=5.e-2;
		}
		else if(paramrelic->failsafe==6)
		{
			Ytest=1.e-30;
			prec=1.e-2;
		}
		else
		{
			Ytest=1.e-30;
			prec=1.e-3;
		}

		double dt=1.e-10*s_to_GeV;

		int niter=0;
		int test=0;
		int test_precision=0;
		int iloop;

		while(T>Tf)
		{
			niter++;
			if(test==0&&test_precision==0)
			{
				T_sav=T;
				h_eta_sav=h_eta;
				phie_sav=phie;
				Tnu_sav=Tnu;
				t_sav=t;
				a_sav=a;
				for (i=1;i<=NNUC;i++)
				{
					Y_sav[i]=Y[i];
				}
				if(paramrelic->phi_model&&rho_phi!=0.) rhophi_sav=rho_phi;
			}

			for(iloop=0;iloop<=5;iloop++)
			{
				switch(iloop)
				{
					case 0: /* first step of first iteration */
					{
						loop=1;
						t=t_sav;
						T=T_sav;
						h_eta=h_eta_sav;
						phie=phie_sav;
						Tnu=Tnu_sav;
						a=a_sav;
						for (i=1;i<=NNUC;i++)
						{
							Y[i]=Y_sav[i];
						}
						if(paramrelic->phi_model&&rho_phi!=0.) rho_phi=rhophi_sav;
						break;
					}

					case 1: /* second step of first iteration */
					{
						loop=2;

						t=t_sav+dt;

						T=T_sav+dT_dt*dt;
						Tnu=Tnu_sav+dTnu_dt*dt;
						h_eta=h_eta_sav+dh_dt*dt;
						phie=phie_sav+dphie_dt*dt;
						a=a_sav+da_dt*dt;
						if(paramrelic->phi_model&&rho_phi!=0.) rho_phi=rhophi_sav+drhophi_dt*dt;

						dT0_dt=dT_dt;
						dTnu0_dt=dTnu_dt;
						dh_dt0=dh_dt;
						dphie_dt0=dphie_dt;
						da_dt0=da_dt;
						if(paramrelic->phi_model&&rho_phi!=0.) drhophi_dt0=drhophi_dt;

						for (i=1;i<=NNUC;i++)
						{
							Y[i]=Y_sav[i]+dY_dt[i]*dt;
							dY_dt0[i]=dY_dt[i];
						}
						break;
					}

					case 2: /* first step of second iteration */
					{
						loop=1;

						dt/=2.;

						t=t_sav;
						T=T_sav;
						h_eta=h_eta_sav;
						phie=phie_sav;
						Tnu=Tnu_sav;
						a=a_sav;
						for (i=1;i<=NNUC;i++)
						{
							Y[i]=Y_sav[i];
						}
						if(paramrelic->phi_model&&rho_phi!=0.) rho_phi=rhophi_sav;
						break;
					}

					case 3: /* second step of second iteration */
					{
						loop=2;

						t=t_sav+dt;

						T=T_sav+dT_dt*dt;
						Tnu=Tnu_sav+dTnu_dt*dt;
						h_eta=h_eta_sav+dh_dt*dt;
						phie=phie_sav+dphie_dt*dt;
						a=a_sav+da_dt*dt;
						if(paramrelic->phi_model&&rho_phi!=0.) rho_phi=rhophi_sav+drhophi_dt*dt;

						dT0_dt=dT_dt;
						dTnu0_dt=dTnu_dt;
						dh_dt0=dh_dt;
						dphie_dt0=dphie_dt;
						da_dt0=da_dt;
						if(paramrelic->phi_model&&rho_phi!=0.) drhophi_dt0=drhophi_dt;

						for (i=1;i<=NNUC;i++)
						{
							dY_dt0[i]=dY_dt[i];
							Y[i]=Y_sav[i]+dY_dt[i]*dt;
						}
						break;
					}

					case 4: /* third step of second iteration */
					{
						loop=1;

						t=t_sav2;
						T=T_sav2;
						h_eta=h_eta_sav2;
						phie=phie_sav2;
						Tnu=Tnu_sav2;
						a=a_sav2;
						for (i=1;i<=NNUC;i++)
						{
							Y[i]=Y_sav2[i];
						}
						if(paramrelic->phi_model&&rho_phi!=0.) rho_phi=rhophi_sav2;
						break;
					}

					case 5: /* fourth step of second iteration */
					{
						loop=2;

						t=t_sav2+dt;

						T=T_sav2+dT_dt*dt;
						Tnu=Tnu_sav2+dTnu_dt*dt;
						h_eta=h_eta_sav2+dh_dt*dt;
						phie=phie_sav2+dphie_dt*dt;
						a=a_sav2+da_dt*dt;
						if(paramrelic->phi_model&&rho_phi!=0.) rho_phi=rhophi_sav2+drhophi_dt*dt;

						dT0_dt=dT_dt;
						dTnu0_dt=dTnu_dt;
						dh_dt0=dh_dt;
						dphie_dt0=dphie_dt;
						da_dt0=da_dt;
						if(paramrelic->phi_model&&rho_phi!=0.) drhophi_dt0=drhophi_dt;

						for (i=1;i<=NNUC;i++)
						{
							dY_dt0[i]=dY_dt[i];
							Y[i]=Y_sav2[i]+dY_dt[i]*dt;
						}
						break;
					}
				}

				fill_params(T,Tnu,phie,h_eta,a,rho_phi,dt,&dT_dt,&dTnu_dt,&dphie_dt,&dh_dt,&da_dt,&drhophi_dt,dY_dt,Y,Y,Am,Zm,Dm,reacparam,norm,loop,0,0,paramrelic,paramerror);

				if(iloop==1)
				{
					T1=T_sav+(dT_dt+dT0_dt)*0.5*dt;
					Tnu1=Tnu_sav+(dTnu_dt+dTnu0_dt)*0.5*dt;
					h_eta1=h_eta_sav+(dh_dt+dh_dt0)*0.5*dt;
					phie1=phie_sav+(dphie_dt+dphie_dt0)*0.5*dt;
					a1=a_sav+(da_dt+da_dt0)*0.5*dt;
					if(paramrelic->phi_model&&rho_phi!=0.) rhophi1=rhophi_sav+(drhophi_dt0+drhophi_dt)*0.5*dt;

					for (i=1;i<=NNUC;i++)
					{
						Y1[i]=Y_sav[i]+(dY_dt[i]+dY_dt0[i])*0.5*dt;
					}
				}

				if(iloop==3)
				{
					t_sav2=t;
					T_sav2=T_sav+(dT_dt+dT0_dt)*0.5*dt;
					Tnu_sav2=Tnu_sav+(dTnu_dt+dTnu0_dt)*0.5*dt;
					h_eta_sav2=h_eta_sav+(dh_dt+dh_dt0)*0.5*dt;
					phie_sav2=phie_sav+(dphie_dt+dphie_dt0)*0.5*dt;
					a_sav2=a_sav+(da_dt+da_dt0)*0.5*dt;
					if(paramrelic->phi_model&&rho_phi!=0.) rhophi_sav2=rhophi_sav+(drhophi_dt0+drhophi_dt)*0.5*dt;

					for (i=1;i<=NNUC;i++)
					{
						Y_sav2[i]=Y_sav[i]+(dY_dt[i]+dY_dt0[i])*0.5*dt;
					}
				}

				if(iloop==5)
				{
					T2=T_sav2+(dT_dt+dT0_dt)*0.5*dt;
					Tnu2=Tnu_sav2+(dTnu_dt+dTnu0_dt)*0.5*dt;
					h_eta2=h_eta_sav2+(dh_dt+dh_dt0)*0.5*dt;
					phie2=phie_sav2+(dphie_dt+dphie_dt0)*0.5*dt;
					a2=a_sav2+(da_dt+da_dt0)*0.5*dt;
					if(paramrelic->phi_model&&rho_phi!=0.) rhophi2=rhophi_sav2+(drhophi_dt0+drhophi_dt)*0.5*dt;

					for (i=1;i<=NNUC;i++)
					{
						Y2[i]=Y_sav2[i]+(dY_dt[i]+dY_dt0[i])*0.5*dt;
					}
				}
			}

			dt*=2.;

			test=0;
			test+=(isnan(T1)||isnan(T2));
			test+=(isnan(h_eta1)||isnan(h_eta2));
			test+=(isnan(phie1)||isnan(phie2));
			test+=(isnan(Tnu1)||isnan(Tnu2));
			test+=(isnan(a1)||isnan(a2));
			for (i=1;i<=NNUC;i++) test+=(isnan(Y1[i])||isnan(Y2[i])||(fabs(Y1[i])>Ytest&&Y1[i]<0.)||(fabs(Y2[i])>Ytest&&Y2[i]<0.));
			if(paramrelic->phi_model&&rho_phi!=0.) test+=(isnan(rhophi1)||isnan(rhophi2)||rhophi1<0.||rhophi2<0.);

			test_precision=0;
			test_precision+=(fabs(1.-T1/T2)>prec);
			test_precision+=(fabs(1.-h_eta1/h_eta2)>prec);
			test_precision+=(fabs(1.-phie1/phie2)>prec);
			test_precision+=(fabs(1.-Tnu1/Tnu2)>prec);
			test_precision+=(fabs(1.-a1/a2)>prec);
			if(paramrelic->phi_model&&rho_phi!=0.) test_precision+=(fabs(1.-rhophi1/rhophi2)>prec);

			if(paramrelic->failsafe==5)
			{
				for (i=1;i<10;i++) if(fabs(Y2[i])>Ytest) test_precision+=(fabs(1.-Y1[i]/Y2[i])>prec);
			}
			else
			{
				for (i=1;i<=NNUC;i++) if(fabs(Y2[i])>Ytest) test_precision+=(fabs(1.-Y1[i]/Y2[i])>prec);
			}

			if(test==0&&test_precision==0)
			{
				T=T2;
				h_eta=h_eta2;
				phie=phie2;
				Tnu=Tnu2;
				a=a2;
				for (i=1;i<=NNUC;i++)
				{
					Y[i]=Y2[i];
				}
				if(paramrelic->phi_model&&rho_phi!=0.) rho_phi=rhophi2;
				if(paramrelic->phi_model&&rho_phi!=0.) if(rho_phi<1.e-20*pow(pi,2.)/15.*pow(T,4.)) rho_phi=0.;
#ifdef OUTPUT
				if(paramrelic->err==0) fprintf(output,"%.5e\t%.5e\t%.5e\t%.5e\t%.5e\t%.5e\t%.5e\t%.5e\t%.5e\t%.5e\t%.5e\t%.5e\t%.5e\n",t/s_to_GeV,a,T/K_to_eV,Tnu/K_to_eV,pow(pi,2.)/15.*pow(T,4.),h_eta*pow(T,3.),neutdens(Tnu,paramrelic),rho_phi,Y[1],Y[2],Y[3],Y[6],Y[8]);
#endif

				if(!isnan(fabs(T2*prec/(T2-T1)))) minprec=fabs(T2*prec/(T2-T1));
				if(!isnan(fabs(h_eta2*prec/(h_eta2-h_eta1)))) minprec=min(minprec,fabs(h_eta2*prec/(h_eta2-h_eta1)));
				if(!isnan(fabs(phie2*prec/(phie2-phie1)))) minprec=min(minprec,fabs(phie2*prec/(phie2-phie1)));
				if(!isnan(fabs(Tnu2*prec/(Tnu2-Tnu1)))) minprec=min(minprec,fabs(Tnu2*prec/(Tnu2-Tnu1)));
				if(!isnan(fabs(a2*prec/(a2-a1)))) minprec=min(minprec,fabs(a2*prec/(a2-a1)));

				if(paramrelic->phi_model&&rho_phi!=0.) if(!isnan(fabs(rhophi2*prec/(rhophi2-rhophi1)))) minprec=min(minprec,fabs(rhophi2*prec/(rhophi2-rhophi1)));

				if(paramrelic->failsafe==5)
				{
					for (i=1;i<10;i++) if(fabs(Y2[i])>Ytest) if(!isnan(fabs(Y2[i]*prec/(Y2[i]-Y1[i])))) minprec=min(minprec,fabs(Y2[i]*prec/(Y2[i]-Y1[i])));
				}
				else
				{
					for (i=1;i<=NNUC;i++) if(fabs(Y2[i])>Ytest) if(!isnan(fabs(Y2[i]*prec/(Y2[i]-Y1[i])))) minprec=min(minprec,fabs(Y2[i]*prec/(Y2[i]-Y1[i])));
				}

				dt*=2.*0.9*min(1.,max(minprec,0.3));

#ifdef CHECKINTERM
				for (i=1;i<=NNUC;i++) if(Y[i]>Ylow) checklow[i]++;
#endif
			}
			else
			{
				dt/=2.;

				t=t_sav;
				T=T_sav;
				h_eta=h_eta_sav;
				phie=phie_sav;
				Tnu=Tnu_sav;
				a=a_sav;
				for (i=1;i<=NNUC;i++)
				{
					Y[i]=Y_sav[i];
				}
				if(paramrelic->phi_model&&rho_phi!=0.) rho_phi=rhophi_sav;
			}

#ifdef DEBUG
			if(niter%10000==0) printf("niter=%d   t=%.10e    T=%.5e   h_eta=%.5e    phie=%.5e   Tnu=%.5e   a=%.5e   %d %d  %.3e %.3e %.3e %.3e\n",niter,t,T,h_eta,phie,Tnu,a,test,test_precision,Y[1],Y[2],Y[3],Y[4]);
#endif

		}
	}
	else if(paramrelic->failsafe<20) /* Runge-Kutta method of order 4 with adaptative stepsize */
	{
		double dT_rk[12],dh_eta_rk[12],dphie_rk[12],dTnu_rk[12],dY_rk[NNUC+1][12],drhophi_rk[12],da_rk[12];

		double T_sav,h_eta_sav,phie_sav,Tnu_sav,Y_sav[NNUC+1],t_sav,a_sav,dt0;

		double t2_sav,dt_sav;
		double T1,T2,T2_sav;
		double h_eta1,h_eta2,h_eta2_sav;
		double phie1,phie2,phie2_sav;
		double Tnu1,Tnu2,Tnu2_sav;
		double a1,a2,a2_sav;
		double Y1[NNUC+1],Y2[NNUC+1],Y2_sav[NNUC+1];
		double rhophi1,rhophi2,rhophi_sav,rhophi2_sav;
		int test=0;
		int test_precision=0;
		int niter=0;

		double Ytest;
		double prec;
		double minprec;

		if(paramrelic->failsafe==10)
		{
			Ytest=1.e-25;
			prec=5.e-2;
		}
		else if(paramrelic->failsafe==11)
		{
			Ytest=1.e-30;
			prec=1.e-2;
		}
		else
		{
			Ytest=1.e-30;
			prec=1.e-3;
		}

	    double dt=1.e-10*s_to_GeV; /* initial time step */

		while(T>Tf)
		{
			niter++;
			if(test==0&&test_precision==0)
			{
				T_sav=T;
				h_eta_sav=h_eta;
				phie_sav=phie;
				Tnu_sav=Tnu;
				a_sav=a;
				t_sav=t;
				dt_sav=dt;
				for (i=1;i<=NNUC;i++)
				{
					Y_sav[i]=Y[i];
				}
				if(paramrelic->phi_model&&rho_phi!=0.) rhophi_sav=rho_phi;
			}

			for(int iloop=0;iloop<=11;iloop++)
			{
				switch(iloop)
				{
					case 0: /* first RK4 */
					{
						t=t_sav;
						T=T_sav;
						h_eta=h_eta_sav;
						phie=phie_sav;
						Tnu=Tnu_sav;
						a=a_sav;
						dt0=0.5*dt_sav;
						for (i=1;i<=NNUC;i++)
						{
							Y[i]=Y_sav[i];
						}
						if(paramrelic->phi_model&&rho_phi!=0.) rho_phi=rhophi_sav;
						break;
					}
					case 1:
					{
						t=t_sav+0.5*dt;
						T=T_sav+0.5*dt*dT_rk[0];
						h_eta=h_eta_sav+0.5*dt*dh_eta_rk[0];
						phie=phie_sav+0.5*dt*dphie_rk[0];
						Tnu=Tnu_sav+0.5*dt*dTnu_rk[0];
						a=a_sav+0.5*dt*da_rk[0];
						for (i=1;i<=NNUC;i++)
						{
							Y[i]=Y_sav[i]+0.5*dt*dY_rk[i][0];
						}
						if(paramrelic->phi_model&&rho_phi!=0.) rho_phi=rhophi_sav+0.5*drhophi_rk[0];
						break;
					}
					case 2:
					{
						t=t_sav+0.5*dt;
						T=T_sav+0.5*dt*dT_rk[1];
						h_eta=h_eta_sav+0.5*dt*dh_eta_rk[1];
						phie=phie_sav+0.5*dt*dphie_rk[1];
						Tnu=Tnu_sav+0.5*dt*dTnu_rk[1];
						a=a_sav+0.5*dt*da_rk[1];
						for (i=1;i<=NNUC;i++)
						{
							Y[i]=Y_sav[i]+0.5*dt*dY_rk[i][1];
						}
						if(paramrelic->phi_model&&rho_phi!=0.) rho_phi=rhophi_sav+0.5*drhophi_rk[1];
						break;
					}
					case 3:
					{
						t=t_sav+dt;
						T=T_sav+dt*dT_rk[2];
						h_eta=h_eta_sav+dt*dh_eta_rk[2];
						phie=phie_sav+dt*dphie_rk[2];
						Tnu=Tnu_sav+dt*dTnu_rk[2];
						a=a_sav+dt*da_rk[2];
						for (i=1;i<=NNUC;i++)
						{
							Y[i]=Y_sav[i]+dt*dY_rk[i][2];
						}
						if(paramrelic->phi_model&&rho_phi!=0.) rho_phi=rhophi_sav+drhophi_rk[2];
						break;
					}

					case 4: /* first half RK4 */
					{
						t=t_sav;
						T=T_sav;
						h_eta=h_eta_sav;
						phie=phie_sav;
						Tnu=Tnu_sav;
						a=a_sav;
						dt0=0.25*dt_sav;
						for (i=1;i<=NNUC;i++)
						{
							Y[i]=Y_sav[i];
						}
						if(paramrelic->phi_model&&rho_phi!=0.) rho_phi=rhophi_sav;
						break;
					}
					case 5:
					{
						t=t_sav+0.25*dt;
						T=T_sav+0.25*dt*dT_rk[4];
						h_eta=h_eta_sav+0.25*dt*dh_eta_rk[4];
						phie=phie_sav+0.25*dt*dphie_rk[4];
						Tnu=Tnu_sav+0.25*dt*dTnu_rk[4];
						a=a_sav+0.25*dt*da_rk[4];
						for (i=1;i<=NNUC;i++)
						{
							Y[i]=Y_sav[i]+0.25*dt*dY_rk[i][4];
						}
						if(paramrelic->phi_model&&rho_phi!=0.) rho_phi=rhophi_sav+0.25*drhophi_rk[4];
						break;
					}
					case 6:
					{
						t=t_sav+0.25*dt;
						T=T_sav+0.25*dt*dT_rk[5];
						h_eta=h_eta_sav+0.25*dt*dh_eta_rk[5];
						phie=phie_sav+0.25*dt*dphie_rk[5];
						Tnu=Tnu_sav+0.25*dt*dTnu_rk[5];
						a=a_sav+0.25*dt*da_rk[5];
						for (i=1;i<=NNUC;i++)
						{
							Y[i]=Y_sav[i]+0.25*dt*dY_rk[i][5];
						}
						if(paramrelic->phi_model&&rho_phi!=0.) rho_phi=rhophi_sav+0.25*drhophi_rk[5];
						break;
					}
					case 7:
					{
						t=t_sav+0.5*dt;
						T=T_sav+0.5*dt*dT_rk[6];
						h_eta=h_eta_sav+0.5*dt*dh_eta_rk[6];
						phie=phie_sav+0.5*dt*dphie_rk[6];
						Tnu=Tnu_sav+0.5*dt*dTnu_rk[6];
						a=a_sav+0.5*dt*da_rk[6];
						for (i=1;i<=NNUC;i++)
						{
							Y[i]=Y_sav[i]+0.5*dt*dY_rk[i][6];
						}
						break;
						if(paramrelic->phi_model&&rho_phi!=0.) rho_phi=rhophi_sav+0.5*drhophi_rk[6];

					}
					case 8: /* second half RK4 */
					{
						t=t2_sav;
						T=T2_sav;
						h_eta=h_eta2_sav;
						phie=phie2_sav;
						Tnu=Tnu2_sav;
						a=a2_sav;
						for (i=1;i<=NNUC;i++)
						{
							Y[i]=Y2_sav[i];
						}
						if(paramrelic->phi_model&&rho_phi!=0.) rho_phi=rhophi2_sav;
						break;
					}
					case 9:
					{
						t=t2_sav+0.25*dt;
						T=T2_sav+0.25*dt*dT_rk[8];
						h_eta=h_eta2_sav+0.25*dt*dh_eta_rk[8];
						phie=phie2_sav+0.25*dt*dphie_rk[8];
						Tnu=Tnu2_sav+0.25*dt*dTnu_rk[8];
						a=a2_sav+0.25*dt*da_rk[8];
						for (i=1;i<=NNUC;i++)
						{
							Y[i]=Y2_sav[i]+0.25*dt*dY_rk[i][8];
						}
						if(paramrelic->phi_model&&rho_phi!=0.) rho_phi=rhophi2_sav+0.25*drhophi_rk[8];
						break;
					}
					case 10:
					{
						t=t2_sav+0.25*dt;
						T=T2_sav+0.25*dt*dT_rk[9];
						h_eta=h_eta2_sav+0.25*dt*dh_eta_rk[9];
						phie=phie2_sav+0.25*dt*dphie_rk[9];
						Tnu=Tnu2_sav+0.25*dt*dTnu_rk[9];
						a=a2_sav+0.25*dt*da_rk[9];
						for (i=1;i<=NNUC;i++)
						{
							Y[i]=Y2_sav[i]+0.25*dt*dY_rk[i][9];
						}
						if(paramrelic->phi_model&&rho_phi!=0.) rho_phi=rhophi2_sav+0.25*drhophi_rk[9];
						break;
					}
					case 11:
					{
						t=t2_sav+0.5*dt;
						T=T2_sav+0.5*dt*dT_rk[10];
						h_eta=h_eta2_sav+0.5*dt*dh_eta_rk[10];
						phie=phie2_sav+0.5*dt*dphie_rk[10];
						Tnu=Tnu2_sav+0.5*dt*dTnu_rk[10];
						a=a2_sav+0.5*dt*da_rk[10];
						for (i=1;i<=NNUC;i++)
						{
							Y[i]=Y2_sav[i]+0.5*dt*dY_rk[i][10];
						}
						if(paramrelic->phi_model&&rho_phi!=0.) rho_phi=rhophi2_sav+0.5*drhophi_rk[10];
						break;
					}
				}

				double dT,dTnu,dphie,dh_eta,dY_dt[NNUC+1],da;

				fill_params(T,Tnu,phie,h_eta,a,rho_phi,dt0,&dT,&dTnu,&dphie,&dh_eta,&da,&drhophi_dt,dY_dt,Y,Y,Am,Zm,Dm,reacparam,norm,0,0,0,paramrelic,paramerror);

				dT_rk[iloop]=dT;
				dTnu_rk[iloop]=dTnu;
				dphie_rk[iloop]=dphie;
				dh_eta_rk[iloop]=dh_eta;
				da_rk[iloop]=da;
				for (i=1;i<=NNUC;i++) dY_rk[i][iloop]=dY_dt[i];
				if(paramrelic->phi_model&&rho_phi!=0.) drhophi_rk[iloop]=drhophi_dt;

				if(iloop==3)
				{
					T1=T_sav+dt/6.*(dT_rk[0]+2.*dT_rk[1]+2.*dT_rk[2]+dT_rk[3]);
					h_eta1=h_eta_sav+dt/6.*(dh_eta_rk[0]+2.*dh_eta_rk[1]+2.*dh_eta_rk[2]+dh_eta_rk[3]);
					phie1=phie_sav+dt/6.*(dphie_rk[0]+2.*dphie_rk[1]+2.*dphie_rk[2]+dphie_rk[3]);
					Tnu1=Tnu_sav+dt/6.*(dTnu_rk[0]+2.*dTnu_rk[1]+2.*dTnu_rk[2]+dTnu_rk[3]);
					a1=a_sav+dt/6.*(da_rk[0]+2.*da_rk[1]+2.*da_rk[2]+da_rk[3]);
					for (i=1;i<=NNUC;i++) Y1[i]=Y_sav[i]+dt/6.*(dY_rk[i][0]+2.*dY_rk[i][1]+2.*dY_rk[i][2]+dY_rk[i][3]);
					if(paramrelic->phi_model&&rho_phi!=0.) rhophi1=rhophi_sav+dt/6.*(drhophi_rk[0]+2.*drhophi_rk[1]+2.*drhophi_rk[2]+drhophi_rk[3]);
				}

				if(iloop==7)
				{
					t2_sav=t_sav+0.5*dt;
					T2_sav=T_sav+0.5*dt/6.*(dT_rk[4]+2.*dT_rk[5]+2.*dT_rk[6]+dT_rk[7]);
					h_eta2_sav=h_eta_sav+0.5*dt/6.*(dh_eta_rk[4]+2.*dh_eta_rk[5]+2.*dh_eta_rk[6]+dh_eta_rk[7]);
					phie2_sav=phie_sav+0.5*dt/6.*(dphie_rk[4]+2.*dphie_rk[5]+2.*dphie_rk[6]+dphie_rk[7]);
					Tnu2_sav=Tnu_sav+0.5*dt/6.*(dTnu_rk[4]+2.*dTnu_rk[5]+2.*dTnu_rk[6]+dTnu_rk[7]);
					a2_sav=a_sav+0.5*dt/6.*(da_rk[4]+2.*da_rk[5]+2.*da_rk[6]+da_rk[7]);
					for (i=1;i<=NNUC;i++) Y2_sav[i]=Y_sav[i]+0.5*dt/6.*(dY_rk[i][4]+2.*dY_rk[i][5]+2.*dY_rk[i][6]+dY_rk[i][7]);
					if(paramrelic->phi_model&&rho_phi!=0.) rhophi2_sav=rhophi_sav+0.5*dt/6.*(drhophi_rk[4]+2.*drhophi_rk[5]+2.*drhophi_rk[6]+drhophi_rk[7]);
				}

				if(iloop==11)
				{
					T2=T2_sav+0.5*dt/6.*(dT_rk[8]+2.*dT_rk[9]+2.*dT_rk[10]+dT_rk[11]);
					h_eta2=h_eta2_sav+0.5*dt/6.*(dh_eta_rk[8]+2.*dh_eta_rk[9]+2.*dh_eta_rk[10]+dh_eta_rk[11]);
					phie2=phie2_sav+0.5*dt/6.*(dphie_rk[8]+2.*dphie_rk[9]+2.*dphie_rk[10]+dphie_rk[11]);
					Tnu2=Tnu2_sav+0.5*dt/6.*(dTnu_rk[8]+2.*dTnu_rk[9]+2.*dTnu_rk[10]+dTnu_rk[11]);
					a2=a2_sav+0.5*dt/6.*(da_rk[8]+2.*da_rk[9]+2.*da_rk[10]+da_rk[11]);
					for (i=1;i<=NNUC;i++) Y2[i]=Y2_sav[i]+0.5*dt/6.*(dY_rk[i][8]+2.*dY_rk[i][9]+2.*dY_rk[i][10]+dY_rk[i][11]);
					if(paramrelic->phi_model&&rho_phi!=0.) rhophi2=rhophi2_sav+0.5*dt/6.*(drhophi_rk[8]+2.*drhophi_rk[9]+2.*drhophi_rk[10]+drhophi_rk[11]);
				}
			}

			test=0;
			test+=(isnan(T1)||isnan(T2));
			test+=(isnan(h_eta1)||isnan(h_eta2));
			test+=(isnan(phie1)||isnan(phie2));
			test+=(isnan(Tnu1)||isnan(Tnu2));
			test+=(isnan(a1)||isnan(a2));
			for (i=1;i<=NNUC;i++) test+=(isnan(Y1[i])||isnan(Y2[i])||(fabs(Y1[i])>Ytest&&Y1[i]<0.)||(fabs(Y2[i])>Ytest&&Y2[i]<0.));
			if(paramrelic->phi_model&&rho_phi!=0.) test+=(isnan(rhophi1)||isnan(rhophi2)||rhophi1<0.||rhophi2<0.);


			test_precision=0;
			test_precision+=(fabs(1.-T1/T2)>prec);
			test_precision+=(fabs(1.-h_eta1/h_eta2)>prec);
			test_precision+=(fabs(1.-phie1/phie2)>prec);
			test_precision+=(fabs(1.-Tnu1/Tnu2)>prec);
			test_precision+=(fabs(1.-a1/a2)>prec);
			if(paramrelic->phi_model&&rho_phi!=0.) test_precision+=(fabs(1.-rhophi1/rhophi2)>prec);

			if(paramrelic->failsafe==10)
			{
				for (i=1;i<10;i++) if(fabs(Y2[i])>Ytest) test_precision+=(fabs(1.-Y1[i]/Y2[i])>prec);
			}
			else
			{
				for (i=1;i<=NNUC;i++) if(fabs(Y2[i])>Ytest) test_precision+=(fabs(1.-Y1[i]/Y2[i])>prec);
			}

			if(test==0&&test_precision==0)
			{
				T=T2;
				h_eta=h_eta2;
				phie=phie2;
				Tnu=Tnu2;
				a=a2;
				for (i=1;i<=NNUC;i++) Y[i]=Y2[i];
				if(paramrelic->phi_model&&rho_phi!=0.) rho_phi=rhophi2;
				if(paramrelic->phi_model&&rho_phi!=0.) if(rho_phi<1.e-20*pow(pi,2.)/15.*pow(T,4.)) rho_phi=0.;
#ifdef OUTPUT
				if(paramrelic->err==0) fprintf(output,"%.5e\t%.5e\t%.5e\t%.5e\t%.5e\t%.5e\t%.5e\t%.5e\t%.5e\t%.5e\t%.5e\t%.5e\t%.5e\n",t/s_to_GeV,a,T/K_to_eV,Tnu/K_to_eV,pow(pi,2.)/15.*pow(T,4.),h_eta*pow(T,3.),neutdens(Tnu,paramrelic),rho_phi,Y[1],Y[2],Y[3],Y[6],Y[8]);
#endif

				t=t_sav+dt;

				dt*=2.;

				if(!isnan(fabs(T2*prec/(T2-T1)))) minprec=fabs(T2*prec/(T2-T1));
				if(!isnan(fabs(h_eta2*prec/(h_eta2-h_eta1)))) minprec=min(minprec,fabs(h_eta2*prec/(h_eta2-h_eta1)));
				if(!isnan(fabs(phie2*prec/(phie2-phie1)))) minprec=min(minprec,fabs(phie2*prec/(phie2-phie1)));
				if(!isnan(fabs(Tnu2*prec/(Tnu2-Tnu1)))) minprec=min(minprec,fabs(Tnu2*prec/(Tnu2-Tnu1)));
				if(!isnan(fabs(a2*prec/(a2-a1)))) minprec=min(minprec,fabs(a2*prec/(a2-a1)));

				if(paramrelic->phi_model&&rho_phi!=0.) if(!isnan(fabs(rhophi2*prec/(rhophi2-rhophi1)))) minprec=min(minprec,fabs(rhophi2*prec/(rhophi2-rhophi1)));

				if(paramrelic->failsafe==10)
				{
					for (i=1;i<10;i++) if(Y2[i]>Ytest) if(!isnan(fabs(Y2[i]*prec/(Y2[i]-Y1[i])))) minprec=min(minprec,fabs(Y2[i]*prec/(Y2[i]-Y1[i])));
				}
				else
				{
					for (i=1;i<=NNUC;i++) if(Y2[i]>Ytest) if(!isnan(fabs(Y2[i]*prec/(Y2[i]-Y1[i])))) minprec=min(minprec,fabs(Y2[i]*prec/(Y2[i]-Y1[i])));
				}

				dt*=2.*0.9*min(1.,max(minprec,0.3));

#ifdef CHECKINTERM
				for (i=1;i<=NNUC;i++) if(Y[i]>Ylow) checklow[i]++;
#endif
			}
			else
			{
				dt/=2.;

				t=t_sav;
				T=T_sav;
				h_eta=h_eta_sav;
				phie=phie_sav;
				Tnu=Tnu_sav;
				a=a_sav;
				for (i=1;i<=NNUC;i++)
				{
					Y[i]=Y_sav[i];
				}
				if(paramrelic->phi_model&&rho_phi!=0.) rho_phi=rhophi_sav;
			}

#ifdef DEBUG
			if(niter%10000==0) printf("niter=%d   t=%.10e    T=%.5e   h_eta=%.5e    phie=%.5e   Tnu=%.5e   a=%.5e   %d %d  %.3e %.3e %.3e %.3e\n",niter,t,T,h_eta,phie,Tnu,a,test,test_precision,Y[1],Y[2],Y[3],Y[4]);
#endif
		}
	}
	else /* Runge-Kutta of order 45 methods */
	{
		double dT_rk[6],dh_eta_rk[6],dphie_rk[6],dTnu_rk[6],da_rk[6],dY_rk[NNUC+1][6],drhophi_rk[6];

		double T_sav,h_eta_sav,phie_sav,Tnu_sav,a_sav,Y_sav[NNUC+1],rhophi_sav,t_sav,dt0;

		double t2_sav,dt_sav;
		double T1,T2,T2_sav;
		double h_eta1,h_eta2,h_eta2_sav;
		double phie1,phie2,phie2_sav;
		double Tnu1,Tnu2,Tnu2_sav;
		double a1,a2,a2_sav;
		double Y1[NNUC+1],Y2[NNUC+1],Y2_sav[NNUC+1];
		double rhophi1,rhophi2,rhophi2_sav;
		int test=0;
		int test_precision=0;
		int niter=0;
		int ie,je;

		double Ytest;
		double prec;
		double minprec;

		if(paramrelic->failsafe%10==0)
		{
			Ytest=1.e-25;
			if(paramrelic->failsafe<30) prec=5.e-2; else prec=1.e-2;
		}
		else if(paramrelic->failsafe%10==1)
		{
			Ytest=1.e-30;
			if(paramrelic->failsafe<30) prec=1.e-2; else prec=1.e-4;
		}
		else
		{
			Ytest=1.e-30;
			if(paramrelic->failsafe<30) prec=1.e-3; else prec=1.e-5;
		}

		double dt=1.e-10*s_to_GeV; /* initial time step */

		/* Fehlberg */
		const double ordermaxF=5;
		const double dtstepF[6]={0.25,0.375,12./13.,1.,0.5,0.};
		const double dt0stepF[6]={0.5,0.375,0.5,0.5,0.5,0.5};
		const double coefstepsF[6][6]=
		{{0.25,0.,0.,0.,0.,0.},{3./32.,9./32.,0.,0.,0.,0},{1932./2197.,-7200./2197.,7296./2197.,0.,0.,0.},{439./216.,-8.,3680./513.,-845./4104.,0.,0.},{-8./27.,2.,-3544./2565.,1859./4104.,-11./40.,0.},{0.,0.,0.,0.,0.,0.}};
		const double coefsol1F[6]=
		{25./216.,0.,1408./2565.,2197./4104.,-1./5.,0.};
		const double coefsol2F[6]=
		{16./135.,0.,6656./12825.,28561./56430.,-9./50.,2./55.};

		/* Cash-Karp */
		const double ordermaxCK=5;
		const double dtstepCK[6]={0.2,0.3,0.6,1.,0.875,0.};
		const double dt0stepCK[6]={0.5,0.5,0.5,0.5,0.5,0.5};
		const double coefstepsCK[6][6]=	{{0.2,0.,0.,0.,0.,0.},{3./40.,9./40.,0.,0.,0.,0},{0.3,-0.9,1.2,0.,0.,0.},{-11./54.,2.5,-70./27.,35./27.,0.,0.},{1631./55296.,175./512.,575./13824.,44275./110592.,253./4096.,0.},{0.,0.,0.,0.,0.,0.}};
		const double coefsol1CK[6]=
		{2825./27648.,0.,18575./48384.,13525./55296.,277./14336.,0.25};
		const double coefsol2CK[6]=
		{37./378.,0.,250./621.,125./594.,0.,512./1771.};

		int ordermax;
		if(paramrelic->failsafe<30) ordermax=ordermaxF;
		else  ordermax=ordermaxCK;

		double dtstep[ordermax+1],dt0step[ordermax+1],coefsteps[ordermax+1][ordermax+1],coefsol1[ordermax+1],coefsol2[ordermax+1];

		if(paramrelic->failsafe<30)
		{
			for(ie=0;ie<=ordermax;ie++)
			{
				dtstep[ie]=dtstepF[ie];
				dt0step[ie]=dt0stepF[ie];
				coefsol1[ie]=coefsol1F[ie];
				coefsol2[ie]=coefsol2F[ie];
				for(je=0;je<=ordermax;je++)
				{
					coefsteps[ie][je]=coefstepsF[ie][je];
				}
			}
		}
		else
		{
			for(ie=0;ie<=ordermax;ie++)
			{
				dtstep[ie]=dtstepCK[ie];
				dt0step[ie]=dt0stepCK[ie];
				coefsol1[ie]=coefsol1CK[ie];
				coefsol2[ie]=coefsol2CK[ie];
				for(je=0;je<=ordermax;je++)
				{
					coefsteps[ie][je]=coefstepsCK[ie][je];
				}
			}
		}

		while(T>Tf)
		{
			niter++;
			if(test==0&&test_precision==0)
			{
				T_sav=T;
				h_eta_sav=h_eta;
				phie_sav=phie;
				Tnu_sav=Tnu;
				a_sav=a;
				t_sav=t;
				dt_sav=dt;
				for (i=1;i<=NNUC;i++)
				{
					Y_sav[i]=Y[i];
				}
				if(paramrelic->phi_model&&rho_phi!=0.) rhophi_sav=rho_phi;
			}

			int iloop;

			for(iloop=0;iloop<=ordermax;iloop++)
			{
				if(iloop==0) t=t_sav; else t=t_sav+dtstep[iloop-1]*dt;
				T=T_sav;
				h_eta=h_eta_sav;
				phie=phie_sav;
				Tnu=Tnu_sav;
				a=a_sav;
				dt0=dt0step[iloop]*dt_sav;
				for (i=1;i<=NNUC;i++)
				{
					Y[i]=Y_sav[i];
				}
				if(paramrelic->phi_model&&rho_phi!=0.) rho_phi=rhophi_sav;

				for(je=0;je<iloop;je++)
				{

					T+=coefsteps[iloop-1][je]*dt*dT_rk[je];
					h_eta+=coefsteps[iloop-1][je]*dt*dh_eta_rk[je];
					phie+=coefsteps[iloop-1][je]*dt*dphie_rk[je];
					Tnu+=coefsteps[iloop-1][je]*dt*dTnu_rk[je];
					a+=coefsteps[iloop-1][je]*dt*da_rk[je];
					for (i=1;i<=NNUC;i++)
					{
						Y[i]+=coefsteps[iloop-1][je]*dt*dY_rk[i][je];
					}
					if(paramrelic->phi_model&&rho_phi!=0.) rho_phi+=coefsteps[iloop-1][je]*dt*drhophi_rk[je];
				}

				double dT,dTnu,dphie,dh_eta,da,dY_dt[NNUC+1];

				fill_params(T,Tnu,phie,h_eta,a,rho_phi,dt0,&dT,&dTnu,&dphie,&dh_eta,&da,&drhophi_dt,dY_dt,Y,Y,Am,Zm,Dm,reacparam,norm,0,0,0,paramrelic,paramerror);

				dT_rk[iloop]=dT;
				dTnu_rk[iloop]=dTnu;
				dphie_rk[iloop]=dphie;
				dh_eta_rk[iloop]=dh_eta;
				da_rk[iloop]=da;
				for (i=1;i<=NNUC;i++) dY_rk[i][iloop]=dY_dt[i];
				if(paramrelic->phi_model&&rho_phi!=0.) drhophi_rk[iloop]=drhophi_dt;
			}

			T1=T_sav;
			h_eta1=h_eta_sav;
			phie1=phie_sav;
			Tnu1=Tnu_sav;
			a1=a_sav;
			for (i=1;i<=NNUC;i++)
			{
				Y1[i]=Y_sav[i];
			}
			if(paramrelic->phi_model&&rho_phi!=0.) rhophi1=rhophi_sav;

			for(je=0;je<=ordermax;je++)
			{
				T1+=coefsol1[je]*dt*dT_rk[je];
				h_eta1+=coefsol1[je]*dt*dh_eta_rk[je];
				phie1+=coefsol1[je]*dt*dphie_rk[je];
				Tnu1+=coefsol1[je]*dt*dTnu_rk[je];
				a1+=coefsol1[je]*dt*da_rk[je];
				for (i=1;i<=NNUC;i++)
				{
					Y1[i]+=coefsol1[je]*dt*dY_rk[i][je];
				}
				if(paramrelic->phi_model&&rho_phi!=0.) rhophi1+=coefsol1[je]*dt*drhophi_rk[je];
			}

			T2=T_sav;
			h_eta2=h_eta_sav;
			phie2=phie_sav;
			Tnu2=Tnu_sav;
			a2=a_sav;
			for (i=1;i<=NNUC;i++)
			{
				Y2[i]=Y_sav[i];
			}
			if(paramrelic->phi_model&&rho_phi!=0.) rhophi2=rhophi_sav;

			for(je=0;je<=ordermax;je++)
			{
				T2+=coefsol2[je]*dt*dT_rk[je];
				h_eta2+=coefsol2[je]*dt*dh_eta_rk[je];
				phie2+=coefsol2[je]*dt*dphie_rk[je];
				Tnu2+=coefsol2[je]*dt*dTnu_rk[je];
				a2+=coefsol2[je]*dt*da_rk[je];
				for (i=1;i<=NNUC;i++)
				{
					Y2[i]+=coefsol2[je]*dt*dY_rk[i][je];
				}
				if(paramrelic->phi_model&&rho_phi!=0.) rhophi2+=coefsol2[je]*dt*drhophi_rk[je];
			}

			test=0;
			test+=(isnan(T1)||isnan(T2));
			test+=(isnan(h_eta1)||isnan(h_eta2));
			test+=(isnan(phie1)||isnan(phie2));
			test+=(isnan(Tnu1)||isnan(Tnu2));
			test+=(isnan(a1)||isnan(a2));
			for (i=1;i<=NNUC;i++) test+=(isnan(Y1[i])||isnan(Y2[i])||(fabs(Y1[i])>Ytest&&Y1[i]<0.)||(fabs(Y2[i])>Ytest&&Y2[i]<0.));
			if(paramrelic->phi_model&&rho_phi!=0.) test+=(isnan(rhophi1)||isnan(rhophi2)||rhophi1<0.||rhophi2<0.);

			test_precision=0;
			test_precision+=(fabs(1.-T1/T2)>prec);
			test_precision+=(fabs(1.-h_eta1/h_eta2)>prec);
			test_precision+=(fabs(1.-phie1/phie2)>prec);
			test_precision+=(fabs(1.-Tnu1/Tnu2)>prec);
			test_precision+=(fabs(1.-a1/a2)>prec);
			if(paramrelic->phi_model&&rho_phi!=0.) test_precision+=(fabs(1.-rhophi1/rhophi2)>prec);

			if(paramrelic->failsafe%10==0)
			{
				for (i=1;i<10;i++) if(fabs(Y2[i])>Ytest) test_precision+=(fabs(1.-Y1[i]/Y2[i])>prec);
			}
			else
			{
				for (i=1;i<=NNUC;i++) if(fabs(Y2[i])>Ytest) test_precision+=(fabs(1.-Y1[i]/Y2[i])>prec);
			}

			if(!isnan(fabs(T2*prec/(T2-T1)))) minprec=fabs(T2*prec/(T2-T1));
			if(!isnan(fabs(h_eta2*prec/(h_eta2-h_eta1)))) minprec=min(minprec,fabs(h_eta2*prec/(h_eta2-h_eta1)));
			if(!isnan(fabs(phie2*prec/(phie2-phie1)))) minprec=min(minprec,fabs(phie2*prec/(phie2-phie1)));
			if(!isnan(fabs(Tnu2*prec/(Tnu2-Tnu1)))) minprec=min(minprec,fabs(Tnu2*prec/(Tnu2-Tnu1)));
			if(!isnan(fabs(a2*prec/(a2-a1)))) minprec=min(minprec,fabs(a2*prec/(a2-a1)));
			if(paramrelic->phi_model&&rho_phi!=0.) minprec=min(minprec,fabs(rhophi2*prec/(rhophi2-rhophi1)));

			if(paramrelic->failsafe%10==0)
			{
				for (i=1;i<10;i++) if(fabs(Y2[i])>Ytest) if(!isnan(fabs(Y2[i]*prec/(Y2[i]-Y1[i])))) minprec=min(minprec,fabs(Y2[i]*prec/(Y2[i]-Y1[i])));
			}
			else
			{
				for (i=1;i<=NNUC;i++) if(fabs(Y2[i])>Ytest) if(!isnan(fabs(Y2[i]*prec/(Y2[i]-Y1[i])))) minprec=min(minprec,fabs(Y2[i]*prec/(Y2[i]-Y1[i])));
			}

			if(test==0&&test_precision==0)
			{
				T=T2;
				h_eta=h_eta2;
				phie=phie2;
				Tnu=Tnu2;
				a=a2;
				for (i=1;i<=NNUC;i++) Y[i]=Y2[i];
				if(paramrelic->phi_model&&rho_phi!=0.) rho_phi=rhophi2;
				if(paramrelic->phi_model&&rho_phi!=0.) if(rho_phi<1.e-20*pow(pi,2.)/15.*pow(T,4.)) rho_phi=0.;
#ifdef OUTPUT
				if(paramrelic->err==0) fprintf(output,"%.5e\t%.5e\t%.5e\t%.5e\t%.5e\t%.5e\t%.5e\t%.5e\t%.5e\t%.5e\t%.5e\t%.5e\t%.5e\n",t/s_to_GeV,a,T/K_to_eV,Tnu/K_to_eV,pow(pi,2.)/15.*pow(T,4.),h_eta*pow(T,3.),neutdens(Tnu,paramrelic),rho_phi,Y[1],Y[2],Y[3],Y[6],Y[8]);
#endif

				t=t_sav+dt;

				dt*=min(1.1,max(2.,0.84*pow(prec*minprec,0.25)));

#ifdef CHECKINTERM
				for (i=1;i<=NNUC;i++) if(Y[i]>Ylow) checklow[i]++;
#endif
			}
			else
			{
				dt*=max(0.9,min(0.5,0.84*pow(prec*minprec,0.25)));

				t=t_sav;
				T=T_sav;
				h_eta=h_eta_sav;
				phie=phie_sav;
				Tnu=Tnu_sav;
				a=a_sav;
				for (i=1;i<=NNUC;i++)
				{
					Y[i]=Y_sav[i];
				}
				if(paramrelic->phi_model&&rho_phi!=0.) rho_phi=rhophi_sav;
			}

#ifdef DEBUG
			if(niter%10000==0) printf("niter=%d   t=%.10e    T=%.5e   h_eta=%.5e    phie=%.5e   Tnu=%.5e   a=%.5e   %d %d  %.3e %.3e %.3e %.3e\n",niter,t,T,h_eta,phie,Tnu,a,test,test_precision,Y[1],Y[2],Y[3],Y[4]);
#endif
		}
	}

	/* Post processing */

	ratioH[2]=Y[2]; // Keep the hydrogen abundance
	for (i=1;i<=NNUC;i++) if(i!=2) ratioH[i]=Y[i]/Y[2]; // Normalize the other abundances to the hydrogen one

	ratioH[6]=Y[6]*Am[6];

	ratioH[0] = h_eta / (M_u*g_to_GeV*2.*zeta3/pow(pi,2.)); // This is the value of eta

    ratioH[8]+=ratioH[9];           // Be7 -> Li7 post BBN
    ratioH[5]+=ratioH[4];           // H3 -> He3 post BBN

    for (i=1;i<=NNUC;i++) ratioH[i]=max(0.,ratioH[i]);

#ifdef CHECKLOW
	for (i=1;i<=NNUC;i++) if(Y[i]>Ylow) checklow[i]++;
#endif

#ifdef OUTPUT
	if(paramrelic->err==0) fclose(output);
#endif

    return 0;
}

/*----------------------------------------------------*/

int nucl_err(struct relicparam* paramrelic, double ratioH[NNUC+1], double cov_ratioH[NNUC+1][NNUC+1])
/* Routine which computes the abundance ratios (in ratioH[]) and their
 * covariance matrix (in cov_ratioH[][]), using the parameters contained in
 * paramrelic->err. The err parameter is a switch to choose the evaluation error
 * method (0=no error, 1=high values of the nuclear rates, 2=low values,
 * 3=linear error calculation, 4=random Gaussian error calculation). */
{
    int ie;

    memset(ratioH, 0.,sizeof(double) * (NNUC+1));
    memset(cov_ratioH, 0.,sizeof(double) * (NNUC+1) * (NNUC+1));

    if(paramrelic->err==0)
    {
        if(nucl(paramrelic,ratioH)>0) return 0;
    }

    else if(paramrelic->err==1||paramrelic->err==2)
    {
		double ratioH_tmp[NNUC+1];
        if(nucl(paramrelic,ratioH_tmp)>0) return 0;
        paramrelic->err=0;
        if(nucl(paramrelic,ratioH)>0) return 0;
        for(ie=1;ie<=NNUC;ie++) cov_ratioH[ie][ie]=fabs(ratioH_tmp[ie]-ratioH[ie]);
    }

    else if(paramrelic->err==3)
    {
		int optfail=0;
		int checkzeros=0;

		paramrelic->err=0;
        if(nucl(paramrelic,ratioH)>0) optfail=1;
        for(ie=1;ie<=NNUC;ie++) optfail+=isnan(ratioH[ie]);
		paramrelic->err=3;

		double ratioH_all[NNUCREAC+2][NNUC+1];

#if defined(_OPENMP)
#pragma omp parallel for
#endif
        for(ie=0;ie<=NNUCREAC+1;ie++)
        {
			int je;
			double ratioH_tmp[NNUC+1];

            if(optfail==0)
            {
				struct errorparam paramerror;
				paramerror.errnumber=ie;

				for(je=1;je<=NNUC;je++) ratioH_tmp[je]=0.;

				if(nucl_single(paramrelic,ratioH_tmp,&paramerror)>0)
#if defined(_OPENMP)
#pragma omp atomic
#endif
				optfail++;

				if(ratioH_tmp[3]*ratioH_tmp[6]==0.)
#if defined(_OPENMP)
#pragma omp atomic
#endif
				checkzeros++;

				for(je=1;je<=NNUC;je++) ratioH_all[ie][je]=ratioH_tmp[je];

				for(je=1;je<=NNUC;je++)
#if defined(_OPENMP)
#pragma omp atomic
#endif
				optfail+=isnan(ratioH_tmp[je]);
            }
        }

		if(checkzeros>10) optfail=1;

        if(optfail>0)
        {
			 if(paramrelic->failsafe==0)
			 {
#ifdef DEBUG
			 	printf("Sorry, more precise calculation required, please wait...\n");
#endif
			 	paramrelic->failsafe=1;
			 	return nucl_err(paramrelic,ratioH,cov_ratioH);
			 }
			 else return 0;
		 }
		 else
		 {
			 int je,ke;

			for(ie=0;ie<=NNUCREAC+1;ie++) for(je=1;je<=NNUC;je++) for(ke=1;ke<=NNUC;ke++) if(ratioH_all[ie][je]*ratioH_all[ie][ke]!=0.) cov_ratioH[je][ke]+=(ratioH_all[ie][je]-ratioH[je])*(ratioH_all[ie][ke]-ratioH[ke]);

			for(je=1;je<=NNUC;je++) optfail+=isnan(ratioH[je])+(cov_ratioH[je][je]<0.)+(sqrt(cov_ratioH[je][je])/ratioH[je]<1.e-10);
			for(je=1;je<=NNUC;je++) for(ke=1;ke<=NNUC;ke++) optfail+=isnan(cov_ratioH[je][ke])+(pow(cov_ratioH[je][ke],2.)>1.0001*fabs(cov_ratioH[je][je]*cov_ratioH[ke][ke]));
		 }

    }

    else if(paramrelic->err==4)
    {
		int optfail=0;

		int niter=1000;

		srand((unsigned int)(getpid()));

		double ratioH_all[niter][NNUC+1];

#if defined(_OPENMP)
#pragma omp parallel for
#endif
		for(ie=0;ie<niter;ie++)
		{
			int je;
			struct errorparam paramerror;
			double ratioH_tmp[NNUC+1];
			for(je=1;je<=NNUC;je++) ratioH_tmp[je]=0.;

			if(optfail==0)
            {
				for(je=0;je<=NNUCREAC+1;je++) paramerror.random[je]=rand_gauss();

				if(nucl_single(paramrelic,ratioH_tmp,&paramerror)>0)
#if defined(_OPENMP)
#pragma omp atomic
#endif
				optfail++;

				for(je=1;je<=NNUC;je++) ratioH_all[ie][je]=ratioH_tmp[je];

				for(je=1;je<=NNUC;je++)
#if defined(_OPENMP)
#pragma omp atomic
#endif
				optfail+=isnan(ratioH_all[ie][je]);
			}
		}

		int je,ke;

		for(ie=0;ie<niter;ie++) for(je=1;je<=NNUC;je++) ratioH[je]+=ratioH_all[ie][je];
		for(je=1;je<=NNUC;je++) ratioH[je]/=niter;
		for(ie=0;ie<niter;ie++) for(je=1;je<=NNUC;je++) for(ke=1;ke<=NNUC;ke++) cov_ratioH[je][ke]+=(ratioH_all[ie][je]*ratioH_all[ie][ke]-ratioH[je]*ratioH[ke]);
		for(je=1;je<=NNUC;je++) for(ke=1;ke<=NNUC;ke++) cov_ratioH[je][ke]/=niter;

		for(je=1;je<=NNUC;je++) optfail+=isnan(ratioH[je])+(cov_ratioH[je][je]<0.)+(sqrt(cov_ratioH[je][je])/ratioH[je]<1.e-10);
		for(je=1;je<=NNUC;je++) for(ke=1;ke<=NNUC;ke++) optfail+=isnan(cov_ratioH[je][ke])+(pow(cov_ratioH[je][ke],2.)>1.0001*fabs(cov_ratioH[je][je]*cov_ratioH[ke][ke]));

		if(optfail>0)
		{
			if(paramrelic->failsafe==0)
			{
#ifdef DEBUG
			 	printf("Sorry, more precise calculation required, please wait...\n");
#endif
				paramrelic->failsafe=1;
				return nucl_err(paramrelic,ratioH,cov_ratioH);
			}
			else return 0;
		}
	}

    return 1;
}

/*----------------------------------------------------*/

int nucl(struct relicparam* paramrelic, double ratioH[NNUC+1])
{
	if(paramrelic->err>=3) return -1;

	struct errorparam paramerror;

	int test=nucl_single(paramrelic,ratioH,&paramerror);

	if(test==0)	return 0;
	else if(paramrelic->failsafe==0)
	{
		paramrelic->failsafe=1;
		return nucl_single(paramrelic,ratioH,&paramerror);
	}

	return 0;
}
