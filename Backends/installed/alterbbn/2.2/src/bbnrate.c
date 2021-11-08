#include "include.h"

#define LOWERR -0.2    // Minimum value of the lower relative error of the nuclear rates
#define UPPERR 1.      // Maximum value of the upper relative error of the nuclear rates

void rate_weak(double f[], struct relicparam* paramrelic, struct errorparam* paramerror)
/* Calculates the nuclear forward rates of weak interaction reactions */
/* err=0: central values; err=1: high values; err=2: low values; err=3:
   error only for process number paramerror->errnumber; err=4: random 
   gaussian error for all processes; err<0:  (-err) */
{
    double ferrlow[12],ferrhigh[12];
    int ie;

    // Reactions involving weak interactions
    f[2]=1.78141141239e-9;	/* H3 -> e- + v + He3 */
    f[3]=0.827;	 	/* Li8 -> e- + v + 2He4 */
    f[4]=34.3;	 	/* B12 -> e- + v + C12 */
    f[5]=3.834e-12;	 	/* C14 -> e- + v + N14 */
    f[6]=0.9;	 	/* B8 -> e+ + v + 2He4 */
    f[7]=5.668e-4;	 	/* C11 -> e+ + v + B11 */
    f[8]=63.01;	 	/* N12 -> e+ + v + C12 */
    f[9]=0.001159;	 	/* N13 -> e+ + v + C13 */
    f[10]=0.0098171;	 /* O14 -> e+ + v + N14 */
    f[11]=0.0056704; 	/* O15 -> e+ + v + N15 */

    if(paramrelic->err>0)
    {
        ferrhigh[2]=5.e-3;
        ferrlow[2]=-5.e-3;

        for(ie=3;ie<=11;ie++)
        {
            ferrhigh[ie]=9.;
            ferrlow[ie]=-0.9;
        }

        if(paramrelic->err==1) 
			for(ie=2;ie<=11;ie++) 
				f[ie]*=fabs(1.+ferrhigh[ie]);

        if(paramrelic->err==2) 
			for(ie=2;ie<=11;ie++) 
				f[ie]*=fabs(1.+ferrlow[ie]);

        if(paramrelic->err==3 && paramerror->errnumber>=2 && paramerror->errnumber<=11) 
			f[paramerror->errnumber]*=min(9.,1.+min(UPPERR,ferrhigh[paramerror->errnumber]));

        if(paramrelic->err==4)
        {
            for(ie=2;ie<=11;ie++) 
            {
				if(paramerror->random[ie]<0.) 
					f[ie]*=max(0.1,1.-max(LOWERR,ferrlow[ie])*paramerror->random[ie]);
				else 
					f[ie]*=min(9.,1.+min(UPPERR,ferrhigh[ie])*paramerror->random[ie]);
			}
        }
    }

    return;
}

/*----------------------------------------------------*/

double rate_pn_enu(int type, double T9, double Tnu, relicparam* paramrelic, errorparam* paramerror)
{
	double z = T9*k_B/m_e;
	double znu = Tnu*k_B/m_e;
	double q = 1.29333217e-3/m_e;     /// q=(mn-mp)/me
	double xi = paramrelic->xinu1;
	double b = paramrelic->fierz;
	double integral=0;
	double zmax, norm;
	int i, n=paramrelic->beta_samples;

	if(type== 1 || type == 4)
		zmax = max(n*z,fabs(znu*(n+xi)+q*(1.-1.e-6)));		/// epsilon needed to avoid nan pole at zmax=q
	else
		zmax = max(n*z,fabs(znu*(n-xi)-q*(1.-1.e-6)));

	norm = n/(zmax-1.);

	for(i=1;i<=n;i++)
	{
		double x = 1. + i/norm;			/// electron mass reduced relativistic energy
		double p = sqrt(x*x-1.);			/// relativistic momentum
		double beta = p/x;				/// relativistic beta
		double eta = 2.*pi*alphaem/beta;	/// Fermi function parameter
		double xnu, dI;
		switch(type) 
		{
			case 1:								
				xnu = q-x;
				dI = (x+b)*xnu*xnu*p*eta		/// n --> pe-u
					  /(1.-exp(-eta)) 			/// p and e- are on the same side of the forward reaction
					  /(1.+exp(-x/z)) 			/// x+b, +xnu, -x/z, -xnu/znu, -xi, +eta -> ++---+
					  /(1.+exp(-xnu/znu-xi));
				break;

			case 2: 							
				xnu = q+x;
				dI = (x-b)*xnu*xnu*p			/// ne+ <--> pu
					  /(1.+exp(x/z)) 			/// p and e+ are on opposite sides of the reaction
					  /(1.+exp(-xnu/znu-xi));  	/// x-b, +xnu, +x/z, xnu/znu, -xi, -> -++--0
				break;

			case 3:								
				xnu = q+x;
				dI = (x-b)*xnu*xnu*p*eta		/// nu ---> pe-
					  /(1.-exp(-eta)) 			/// p and e- are on the same side of the forward reaction
					  /(1.+exp(-x/z)) 			/// x-b, +xnu, -x/z, xnu/znu, +xi, +eta -> -+---+
					  /(1.+exp(xnu/znu+xi));
				break;

			case 4:								
				xnu = q-x;
				dI = (x+b)*xnu*xnu*p*eta		/// pe- ---> nu
					  /(exp(eta)-1.) 			/// p and e- are on the same side of the reverse reaction
					  /(1.+exp(x/z)) 			/// x+b, -xnu, +x/z, +xnu/znu, +xi, -eta -> +-+++-
					  /(1.+exp(xnu/znu+xi)); 
				break;

			default:
				printf("Error calling unknown type of n <--> p beta reaction.");
				exit(1);
		}

		if (i<n)
			integral += dI;
		else
			integral += dI/2.;
	}

	return integral/norm;
}

/*----------------------------------------------------*/

void rate_pn_noerr(double f[], double r[], double T9, double Tnu, relicparam* paramrelic, errorparam* paramerror)
/** 
 * Calculates the nuclear forward and reverse rates f[] and r[] 
 * of the reaction p <-> n at the temperature T9
 * 		err=0: central values; 
 * 		err=1: high values; 
 * 		err=2: low values;
 * 		err=3: error only for process number paramerror->errnumber; 
 * 		err=4: random gaussian error
 */
{
	double tau = paramerror->life_neutron;    /// measured neutron lifetime at T=0 in s 
	double b = paramrelic->fierz;             /// beta-decay Fierz interference term 
	double xi = paramrelic->xinu1;            /// neutrino chemical potential
	int n = paramrelic->beta_samples;

    if((!paramrelic->wimp)&&((xi==0.)||(Tnu==0.)) && n <= 100 && b == 0 )
    {	// use extrapolation for beta decay
        int ie;
        double z=5.929862032115561/T9;


        double fcoeffs[13]={0.15735,0.46172e1,-0.40520e2,0.13875e3,-0.59898e2,0.66752e2,-0.16705e2,0.38071e1,-0.39140,0.23590e-1,-0.83696e-4,-0.42095e-4,0.17675e-5};

        double rcoeffs[10]={0.22211e2,-0.72798e2,0.11571e3,-0.11763e2,0.45521e2,-0.37973e1,0.41266e0,-0.26210e-1,0.87934e-3,-0.12016e-4};

        f[1]=1.;
        for(ie=1;ie<=13;ie++) f[1]+=fcoeffs[ie-1]/pow(z,ie);
        f[1]*=exp(-0.33979/z)/tau; /* n->p */

        if(z<5.10998997931)
        {
            r[1]=-0.62173;
            for(ie=1;ie<=10;ie++) r[1]+=rcoeffs[ie-1]/pow(z,ie);
            r[1]*=exp(-2.8602*z)/tau; /* p->n */
        }
        else r[1]=0.; /* weak freeze-out */

    }
    else 	// explicitly compute beta decay
    {
		double I0 = rate_pn_enu(1,0,0,paramrelic, paramerror);
        double int1 = rate_pn_enu(1,T9,Tnu,paramrelic,paramerror);
        double int2 = rate_pn_enu(2,T9,Tnu,paramrelic,paramerror);
        double int3 = rate_pn_enu(3,T9,Tnu,paramrelic,paramerror);
        double int4 = rate_pn_enu(4,T9,Tnu,paramrelic,paramerror);
        f[1]=(int1+int2)/I0/tau;
        r[1]=(int3+int4)/I0/tau;
    }

    return;
}

/*----------------------------------------------------*/

void rate_pn(double f[], double r[], double T9, double Tnu, relicparam* paramrelic, errorparam* paramerror)
/** 
 * Calculates the nuclear forward and reverse rates f[] and r[] 
 * of the reaction p <-> n at the temperature T9
 * 		err=0: central values; 
 * 		err=1: high values; 
 * 		err=2: low values;
 * 		err=3: error only for process number paramerror->errnumber; 
 * 		err=4: random gaussian error
 */
{
    double ferr,rerr;
    ferr=rerr=0.;
	
	rate_pn_noerr(f,r,T9,Tnu,paramrelic,paramerror);

    if(paramrelic->err>0)
    {
        ferr=0.0006;
        rerr=0.0006;
    }

    if(paramrelic->err==1)
    {
        f[1]*=fabs(1.+ferr);
        r[1]*=fabs(1.+rerr);
    }

    if(paramrelic->err==2)
    {
        f[1]*=fabs(1.-ferr);
        r[1]*=fabs(1.-rerr);
    }

    if(paramrelic->err==3&&paramerror->errnumber<=1)
    {
        if(paramerror->errnumber==0) f[1]*=fabs(1.+ferr);
        if(paramerror->errnumber==1) r[1]*=fabs(1.+rerr);
    }

    if(paramrelic->err==4)
    {
        f[1]*=fabs(1.+ferr*paramerror->random[0]);
        r[1]*=fabs(1.+rerr*paramerror->random[1]);
    }

    return;
}

/*----------------------------------------------------*/

void rate_all(double f[], double T9, struct relicparam* paramrelic, struct errorparam* paramerror)
/* calculates the nuclear forward rates f[] of the nuclear reactions given
 * below at the temperature T9 */
/* err=0: central values; err=1: high values; err=2: low values; err=4:
 * random gaussian error; err=3: error only for process number (errnumber) */
{	
    double ferrlow[NNUCREACMAX+1],ferrhigh[NNUCREACMAX+1];
    int ie;

    if(paramrelic->err>0) for(ie=12;ie<=NNUCREAC;ie++)
    {
        ferrhigh[ie]=9.;
        ferrlow[ie]=-0.9;
     }

#if defined(_OPENMP) && NMAX>30	
#pragma omp parallel for
#endif
	for(ie=12;ie<=(int)min(100,NNUCREAC);ie++)
	{
		switch(ie)
		{
			case 12:
			{
				/* H + n -> g + H2 */   // Ando et al. 2006 (updated from Serpico et al. 2004)
				if(T9<=1.5)
				{
					f[12]=44216.*(1+3.75191*T9+1.92934*T9*T9+0.746503*T9*T9*T9+0.0197023*pow(T9,4.)+3.00491e-6*pow(T9,5.))/
							(1+5.4678*T9+5.62395*T9*T9+0.489312*T9*T9*T9+0.00747806*pow(T9,4.));
				}
				else
				{
					f[12]=(1.-sqrt(T9)*0.8504+T9*0.4895-pow(T9,3./2.)*0.09623+T9*0.008471*T9-T9*2.8e-4*pow(T9,3./2.))*47420.;
				}

				if(paramrelic->err>0)
				{
					if (T9<=1.5)
					{
						ferrlow[12]=-0.00449213*(1.+3.08947*T9+0.13277*T9*T9+1.66472*T9*T9*T9)/
								(1.+2.75245*T9+1.40958*T9*T9+0.8791*T9*T9*T9);
					}
					else ferrlow[12]=-0.078;

					ferrhigh[12]=-ferrlow[12];
				}
				break;
			}

			case 13:
			{
				/* H2 + n -> g + H3 */      // Wagoner 1969
				f[13]=(T9*18.9+1.)*66.2;
				if(paramrelic->err>0)
				{
					ferrhigh[13]=0.3;
					ferrlow[13]=-0.3;
				}
				break;
			}
			
			case 14:
			{
				/* He3 + n -> g + He4 */    // Wagoner 1969
				f[14]=(T9*905.+1.)*6.62;
				if(paramrelic->err>0)
				{
					ferrhigh[14]=1.;
					ferrlow[14]=-0.5;
				}
				break;
			}

			case 15:
			{
				/* Li6 + n -> g + Li7 */    // Malaney-Fowler 1989
				f[15]=5100.;
				if(paramrelic->err>0)
				{
					ferrhigh[15]=0.3;
					ferrlow[15]=-0.3;
				}
				break;
			}

			case 16:
			{
				/* He3 + n -> p + H3 */     // Serpico et al. 2004
				if(T9<2.5)
				{
					f[16]=7.064935e8+6.733213571736319e8*T9+1.7181155480346258e9*T9*T9-4.5367658146835446e8*T9*T9*T9
							-1.2216728981712557e8*pow(T9,4.)-4.92736677238425e8*sqrt(T9)-1.3659670893994067e9*pow(T9,3./2.)
							-6.629932739639357e8*pow(T9,5./2.)+4.834951929033479e8*pow(T9,7./2.);
				}
				else f[16]=4.81732e8;

				if(paramrelic->err>0)
				{
					if(T9<2.5)
					{
						ferrlow[16]=-sqrt(0.00187*0.00187+5.4*
										  pow(sqrt(3.51e11+3.112097416989299e11*T9+7.901575411070865e10*T9*T9
												   +2.04541951561715e10*T9*T9*T9+5.110885965380451e9*pow(T9,4.)
												   +3.9016700171412725e9*pow(T9,5.)+1.2106464640648174e9*pow(T9,6.)
												   +2.842691804858251e8*pow(T9,7.)+2.5025023636054292e8*pow(T9,8.)
												   -1.0919522573895195e9*pow(T9,11./2.)-5.074476577064073e11*pow(T9,1./2.)
												   -9.073561744271307e8*pow(T9,13./2.)-4.935780126698165e8*pow(T9,15./2.)
												   -1.3272119856586942e11*pow(T9,3./2.)-3.982502921484235e10*pow(T9,5./2.)
												   -1.4832025658250046e10*pow(T9,7./2.)-3.9093487936349277e9*pow(T9,9./2.)) /
											  f[16],2.));
					}
					else ferrlow[16]=-sqrt(0.00187*0.00187+5.4*pow(224626./f[16],2.));

					ferrhigh[16]=-ferrlow[16];
				}
				break;
			}

			case 17:
			{
				/* Be7 + n -> p + Li7 */    // Serpico et al 2004
				if(T9<2.5)
				{
					f[17]=6.8423032e9+1.7674863e10*T9+2.6622006e9*T9*T9-3.3561608e8*T9*T9*T9-5.9309139e6*pow(T9,4.)
							-1.4987996e10*sqrt(T9)-1.0576906e10*pow(T9,3./2.)+2.7447598e8*pow(T9,5./2.)
							+7.6425157e7*pow(T9,7./2.)-2.282944e7*pow(T9,-3./2.) / exp(0.050351813/T9);
				}
				else f[17]=1.28039e9;

				if(paramrelic->err>0)
				{
					if(T9<2.5)
					{
						ferrhigh[17]=sqrt(0.02082*0.02082+1.2*
										  pow((6.8637241e9+1.7654706e10*T9+2.6528695e9*T9*T9-3.334255e8*T9*T9*T9
											   -5.8841835e6*pow(T9,4.)-1.4998087e10*pow(T9,1./2.)-1.0549873e10*pow(T9,3./2.)
											   +2.7244147e8*pow(T9,5./2.)+7.5882824e7*pow(T9,7./2.)-(2.2946239e7*pow(T9,-3./2.)) /
											   exp(0.05042127/T9))/f[17]-1.,2.));
						ferrlow[17]=-sqrt(0.02082*0.02082+1.2*
										  pow((5.3356377e9+1.2258644e10*T9+1.6991251e9*T9*T9-2.011188e8*T9*T9*T9
											   -3.0052814e6*pow(T9,4.)-1.0649687e10*pow(T9,1./2.)-7.1221438e9*pow(T9,3./2.)
											   +1.8848519e8*pow(T9,5./2.)+4.2410535e7*pow(T9,7./2.)+(6.0102571e7*pow(T9,-3./2.)) /
											   exp(0.2761375/T9))/f[17]-1.,2.));
					}
					else
					{
						ferrhigh[17]=sqrt(0.02082*0.02082+1.2*pow(1.28652e9/f[17]-1.,2.));
						ferrlow[17]=-sqrt(0.02082*0.02082+1.2*pow(1.27454e9/f[17]-1.,2.));
					}
				}
				break;
			}

			case 18:
			{
				/* Li6 + n -> a + H3 */     // Caughlan-Fowler 1988
				f[18]=pow(T9,-1.5)*2.54e9*exp(-2.39/T9)+(1.-pow(T9/(T9*49.18+1.),1.5)*0.261/pow(T9,1.5))*1.68e8;
				if(paramrelic->err>0)
				{
					ferrhigh[18]=0.1;
					ferrlow[18]=-0.1;
				}
				break;
			}

			case 19:
			{
				/* Be7 + n -> a + He4 */    // Hou et al. 2015 (updated from Wagoner 1969)
				if (T9<=10.)
				{
					f[19]=exp(-17.8984+0.2711/T9-23.8918*pow(T9,-1./3.)+62.2135*pow(T9,1./3.)-5.2888*T9
							  +0.3869*pow(T9,5./3.)-22.6197*log(T9));
				}
				else
				{
					f[19]=0.;
				}

				if(paramrelic->err>0)
				{
					if (T9<0.1) ferrhigh[19]=0.90;
					else if ((T9>=0.1)&&(T9<=0.15)) ferrhigh[19]=0.87;
					else if ((T9>0.15)&&(T9<=0.25)) ferrhigh[19]=0.77;
					else if ((T9>0.25)&&(T9<=0.35)) ferrhigh[19]=0.74;
					else if ((T9>0.35)&&(T9<=0.45)) ferrhigh[19]=0.69;
					else if ((T9>0.45)&&(T9<=0.55)) ferrhigh[19]=0.63;
					else if ((T9>0.55)&&(T9<=0.65)) ferrhigh[19]=0.57;
					else if ((T9>0.65)&&(T9<=0.75)) ferrhigh[19]=0.53;
					else if ((T9>0.75)&&(T9<=0.85)) ferrhigh[19]=0.50;
					else if ((T9>0.85)&&(T9<=0.95)) ferrhigh[19]=0.45;
					else if ((T9>0.95)&&(T9<=1.25)) ferrhigh[19]=0.43;
					else if ((T9>1.25)&&(T9<=1.75)) ferrhigh[19]=0.58;
					else if ((T9>1.75)&&(T9<=2.25)) ferrhigh[19]=0.24;
					else if ((T9>2.25)&&(T9<=2.75)) ferrhigh[19]=0.19;
					else if ((T9>2.75)&&(T9<=3.25)) ferrhigh[19]=0.20;
					else if ((T9>3.25)&&(T9<=3.75)) ferrhigh[19]=0.17;
					else if ((T9>3.75)&&(T9<=4.25)) ferrhigh[19]=0.16;
					else if ((T9>4.25)&&(T9<=4.75)) ferrhigh[19]=0.15;
					else if ((T9>4.75)&&(T9<=5.00)) ferrhigh[19]=0.14;
					else
					{
						ferrhigh[19]=0.;
					}
					ferrlow[19]=-ferrhigh[19];
				}
				break;
			}

			case 20:
			{
				/* H2 + p -> g + He3 */      // Coc et al. 2015 (updated from Serpico et al. 2005)
				if (T9<0.001)
				{
					f[20]=4.815e-14;
				}
				else if ((T9>=0.001)&&(T9<=0.0015)) f[20]=4.815e-14;
				else if ((T9>0.0015)&&(T9<=0.0025)) f[20]=6.409e-9;
				else if ((T9>0.0025)&&(T9<=0.0035)) f[20]=4.525e-7;
				else if ((T9>0.0035)&&(T9<=0.0045)) f[20]=4.896e-6;
				else if ((T9>0.0045)&&(T9<=0.0055)) f[20]=2.444e-5;
				else if ((T9>0.0055)&&(T9<=0.0065)) f[20]=8.086e-5;
				else if ((T9>0.0065)&&(T9<=0.0075)) f[20]=2.078e-4;
				else if ((T9>0.0075)&&(T9<=0.0085)) f[20]=4.499e-4;
				else if ((T9>0.0085)&&(T9<=0.0095)) f[20]=8.619e-4;
				else if ((T9>0.0095)&&(T9<=0.0105)) f[20]=1.506e-3;
				else if ((T9>0.0105)&&(T9<=0.0115)) f[20]=2.450e-3;
				else if ((T9>0.0115)&&(T9<=0.0125)) f[20]=3.767e-3;
				else if ((T9>0.0125)&&(T9<=0.0135)) f[20]=5.531e-3;
				else if ((T9>0.0135)&&(T9<=0.0145)) f[20]=7.816e-3;
				else if ((T9>0.0145)&&(T9<=0.0155)) f[20]=1.070e-2;
				else if ((T9>0.0155)&&(T9<=0.0170)) f[20]=1.425e-2;
				else if ((T9>0.0170)&&(T9<=0.0190)) f[20]=2.366e-2;
				else if ((T9>0.0190)&&(T9<=0.0225)) f[20]=3.659e-2;
				else if ((T9>0.0225)&&(T9<=0.0275)) f[20]=8.753e-2;
				else if ((T9>0.0275)&&(T9<=0.0350)) f[20]=1.701e-1;
				else if ((T9>0.035)&&(T9<=0.045)) f[20]=4.476e-1;
				else if ((T9>0.045)&&(T9<=0.055)) f[20]=8.915e-1;
				else if ((T9>0.055)&&(T9<=0.065)) f[20]=1.510;
				else if ((T9>0.065)&&(T9<=0.075)) f[20]=2.302;
				else if ((T9>0.075)&&(T9<=0.085)) f[20]=3.265;
				else if ((T9>0.085)&&(T9<=0.095)) f[20]=4.392;
				else if ((T9>0.095)&&(T9<=0.105)) f[20]=5.676;
				else if ((T9>0.105)&&(T9<=0.115)) f[20]=7.109;
				else if ((T9>0.115)&&(T9<=0.125)) f[20]=8.685;
				else if ((T9>0.125)&&(T9<=0.135)) f[20]=1.040e1;
				else if ((T9>0.135)&&(T9<=0.145)) f[20]=1.224e1;
				else if ((T9>0.145)&&(T9<=0.155)) f[20]=1.420e1;
				else if ((T9>0.155)&&(T9<=0.170)) f[20]=1.628e1;
				else if ((T9>0.170)&&(T9<=0.190)) f[20]=2.076e1;
				else if ((T9>0.190)&&(T9<=0.225)) f[20]=2.565e1;
				else if ((T9>0.225)&&(T9<=0.275)) f[20]=3.941e1;
				else if ((T9>0.275)&&(T9<=0.325)) f[20]=5.505e1;
				else if ((T9>0.325)&&(T9<=0.375)) f[20]=7.225e1;
				else if ((T9>0.375)&&(T9<=0.425)) f[20]=9.076e1;
				else if ((T9>0.425)&&(T9<=0.475)) f[20]=1.104e2;
				else if ((T9>0.475)&&(T9<=0.550)) f[20]=1.310e2;
				else if ((T9>0.550)&&(T9<=0.650)) f[20]=1.748e2;
				else if ((T9>0.650)&&(T9<=0.750)) f[20]=2.212e2;
				else if ((T9>0.750)&&(T9<=0.850)) f[20]=2.700e2;
				else if ((T9>0.850)&&(T9<=0.950)) f[20]=3.207e2;
				else if ((T9>0.950)&&(T9<=1.125)) f[20]=3.729e2;
				else if ((T9>1.125)&&(T9<=1.375)) f[20]=5.093e2;
				else if ((T9>1.375)&&(T9<=1.625)) f[20]=6.522e2;
				else if ((T9>1.625)&&(T9<=1.875)) f[20]=8.000e2;
				else if ((T9>1.875)&&(T9<=2.250)) f[20]=9.517e2;
				else if ((T9>2.250)&&(T9<=2.750)) f[20]=1.265e3;
				else if ((T9>2.750)&&(T9<=3.250)) f[20]=1.587e3;
				else if ((T9>3.250)&&(T9<=3.750)) f[20]=1.914e3;
				else if ((T9>3.750)&&(T9<=4.500)) f[20]=2.244e3;
				else if ((T9>4.500)&&(T9<=5.500)) f[20]=2.905e3;
				else if ((T9>5.500)&&(T9<=6.500)) f[20]=3.557e3;
				else if ((T9>6.500)&&(T9<=7.500)) f[20]=4.194e3;
				else if ((T9>7.500)&&(T9<=8.500)) f[20]=4.812e3;
				else if ((T9>8.500)&&(T9<=9.500)) f[20]=5.410e3;
				else if ((T9>9.500)&&(T9<=10.00)) f[20]=5.988e3;
				else f[20]=0.;

				if(paramrelic->err>0)
				{
					if (T9<0.001)
					{
						ferrhigh[20]=0.038;
					}
					else if ((T9>=0.001)&&(T9<=3.750)) ferrhigh[20]=0.038;
					else if ((T9>3.750)&&(T9<=4.5)) ferrhigh[20]=0.039;
					else if ((T9>4.5)&&(T9<=5.5)) ferrhigh[20]=0.040;
					else if ((T9>5.5)&&(T9<=6.5)) ferrhigh[20]=0.042;
					else if ((T9>6.5)&&(T9<=7.5)) ferrhigh[20]=0.044;
					else if ((T9>7.5)&&(T9<=8.5)) ferrhigh[20]=0.046;
					else if ((T9>8.5)&&(T9<=9.5)) ferrhigh[20]=0.047;
					else if ((T9>9.5)&&(T9<=10.)) ferrhigh[20]=0.049;
					else
					{
						ferrhigh[20]=0.;
					}
					ferrlow[20]=1./(1.+ferrhigh[20])-1.;
				}
				break;
			}

			case 21:
			{
				/* H3 + p -> g + He4 */     // Caughlan-Fowler 1988
				f[21]=pow(T9,-2./3.)*2.2e4*exp(-3.869/pow(T9,1./3.))*(pow(T9,1./3.)*0.108+1.+pow(T9,2./3.)*1.68+T9*1.26
																	  +pow(T9,4./3.)*0.551+pow(T9,5./3.)*1.06);
				if(paramrelic->err>0)
				{
					ferrhigh[21]=0.2;
					ferrlow[21]=-0.2;
				}
				break;
			}

			case 22:
			{
				/* Li6 + p -> g + Be7 */    // NACRE 1999
				f[22] = 1.25e6*pow(T9,-2./3.)*exp(-8.415/pow(T9,1./3.))*(1.-0.252*T9+5.19e-2*T9*T9-2.92e-3*T9*T9*T9);
				if(paramrelic->err>0)
				{
					ferrhigh[22]=0.21;
					ferrlow[22]=-0.21;
				}
				break;
			}

			case 23:
			{
				/* Li6 + p -> a + He3 */    // Serpico et al 2004
				if (T9<2.5)
				{
					f[23]=((-7.4966212e7-1.9411561e10*T9+1.6262854e10*T9*T9+2.0533495e7*pow(T9,1./3.)+3.9547491e9*pow(T9,2./3.)
							+3.7907358e10*pow(T9,4./3.)-3.4313768e10*pow(T9,5./3.)-3.9965228e9*pow(T9,7./3.)
							+4.0333873e8*pow(T9,8./3.))*pow(T9,-2./3.))/exp(4.62619323*pow(T9,-1./3.));
				}
				else f[23]=3.05102e7;
				if(paramrelic->err>0)
				{
					if(T9<2.5)
					{
						ferrhigh[23]=sqrt(0.0931*0.0931+1.2*pow((((4.6794127e7-1.5077363e9*T9-2.8610381e9*T9*T9
																   -4.1883216e8*pow(T9,1./3.)+1.3422134e9*pow(T9,2./3.)
																   -9.4597359e8*pow(T9,4./3.)+3.6073249e9*pow(T9,5./3.)
																   +9.4073567e8*pow(T9,7./3.)
																   -1.1547155e8*pow(T9,8./3.))*pow(T9,-2./3.))/
																 exp(2.47110932*pow(T9,-1./3.)))/f[23]-1.,2.));
						ferrlow[23]=-sqrt(0.0931*0.0931+1.2*pow((((-2.1541443e7-2.1453941e10*T9+1.5165239e10*T9*T9
																   -4.5939493e8*pow(T9,1./3.)+5.5208615e9*pow(T9,2./3.)
																   +3.8266784e10*pow(T9,4./3.)-3.3068204e10*pow(T9,5./3.)
																   -3.6300979e9*pow(T9,7./3.)
																   +3.5841419e8*pow(T9,8./3.))*pow(T9,-2./3.))/
																 exp(4.53459377*pow(T9,-1./3.)))/f[23]-1.,2.));
					}
					else
					{
						ferrhigh[23]=sqrt(0.0931*0.0931+1.2*pow(3.09863e7/f[23]-1.,2.));
						ferrlow[23]=-sqrt(0.0931*0.0931+1.2*pow(3.00895e7/f[23]-1.,2.));
					}
				}
				break;
			}

			case 24:
			{
				/* Li7 + p -> a + He4 */    // Serpico et al 2004
				if (T9<2.5)
				{
					f[24]=((-8.9654123e7-2.5851582e8*T9-2.6831252e7*T9*T9+3.8691673e8*pow(T9,1./3.)+4.9721269e8*pow(T9,2./3.)
							+2.6444808e7*pow(T9,4./3.)-1.2946419e6*pow(T9,5./3.)-1.0941088e8*pow(T9,7./3.)
							+9.9899564e7*pow(T9,8./3.))*pow(T9,-2./3.))/exp(7.73389632*pow(T9,-1./3.));
					f[24]+=exp(-1.137519e0*T9*T9-8.6256687*pow(T9,-1./3.))*(3.0014189e7-1.8366119e8*T9+1.7688138e9*T9*T9
																			-8.4772261e9*T9*T9*T9+2.0237351e10*pow(T9,4.)
																			-1.9650068e10*pow(T9,5.)+7.9452762e8*pow(T9,6.)
																			+1.3132468e10*pow(T9,7.)-8.209351e9*pow(T9,8.)
																			-9.1099236e8*pow(T9,9.)+2.7814079e9*pow(T9,10.)
																			-1.0785293e9*pow(T9,11.)
																			+1.3993392e8*pow(T9,12.))*pow(T9,-2./3.);
				}
				else
				{
					f[24]=1.53403e6;
					f[24]+=84516.7;
				}
				if(paramrelic->err>0)
				{
					if(T9<2.5)
					{
						ferrhigh[24]=sqrt(0.08*0.08+pow((((1.6425644e7-7.682657e8*T9+1.2461811e9*T9*T9-1.1914365e8*pow(T9,1./3.)
														   +3.3659333e8*pow(T9,2./3.)+1.8234158e9*pow(T9,4./3.)
														   -1.9962683e9*pow(T9,5./3.)-5.4978741e8*pow(T9,7./3.)
														   +1.4214466e8*pow(T9,8./3.))*pow(T9,-2./3.)) /
														 exp(6.34172901*pow(T9,-1./3.))
														 +exp(-1.0418442*T9*T9-5.5570697*pow(T9,-1./3.))*
														 (-25145.507+1.0787318e6*T9-1.5899728e7*T9*T9
														  +1.7182625e8*T9*T9*T9-8.3103078e8*pow(T9,4.)+2.1243451e9*pow(T9,5.)
														  -2.872313e9*pow(T9,6.)+2.0104043e9*pow(T9,7.)-4.3859588e8*pow(T9,8.)
														  -3.529339e8*pow(T9,9.)+2.9815567e8*pow(T9,10.)-8.8920729e7*pow(T9,11.)
														  +9.9850915e6*pow(T9,12.))*pow(T9,-2./3.))/f[24]-1.,2.));
						ferrlow[24]=-sqrt(0.08*0.08+pow((((-2.9979375e6-7.8110137e8*T9+1.1816185e9*T9*T9+5.700657e6*pow(T9,1./3.)
														   +1.330785e8*pow(T9,2./3.)+1.733923e9*pow(T9,4./3.)
														   -1.8284296e9*pow(T9,5./3.)-5.0363158e8*pow(T9,7./3.)
														   +1.1026194e8*pow(T9,8./3.))*pow(T9,-2./3.)) /
														 exp(5.35732631*pow(T9,-1./3.))
														 +exp(-1.0068557*T9*T9-5.2092464*pow(T9,-1./3.))*
														 (-14997.544+665017.06*T9-1.0880148e7*T9*T9+1.1299875e8*T9*T9*T9
														  -5.3097151e8*pow(T9,4.)+1.3288827e9*pow(T9,5.)-1.7652952e9*pow(T9,6.)
														  +1.2196578e9*pow(T9,7.)-2.6871614e8*pow(T9,8.)-2.0119802e8*pow(T9,9.)
														  +1.7032325e8*pow(T9,10.)-5.0416533e7*pow(T9,11.)
														  +5.6188182e6*pow(T9,12.))*pow(T9,-2./3.))/f[24]-1.,2.));
					}
					else
					{
						ferrhigh[24]=sqrt(0.08*0.08+pow((1.57087e6+85552.6)/f[24]-1.,2.));
						ferrlow[24]=-sqrt(0.08*0.08+pow((1.49673e6+83165.1)/f[24]-1.,2.));
					}
				}
				break;
			}

			case 25:
			{
				/* H2 + a -> g + Li6 */     // NACRE 1999
				f[25]=1.482e1*pow(T9,-2./3.)*exp(-7.435/pow(T9,1./3.))*(1.+6.572*T9+7.6e-2*T9*T9+2.48e-2*T9*T9*T9)
						+8.28e1*pow(T9,-3./2.)*exp(-7.904/T9);
				if(paramrelic->err>0)
				{
					ferrhigh[25]=0.289+5.612*exp(-3.*T9)-2.63*exp(-2.*T9)+0.773*exp(-T9);
					ferrlow[25]=-0.9813+0.355*pow(T9,1./2.)-0.0411*T9;
				}
				break;
			}
			
			case 26:
			{
				/* H3 + a -> g + Li7 */     // Serpico et al 2004
				if (T9<2.5)
				{
					f[26]=((0.094614248-4.9273133*T9+99.358965*T9*T9-989.81236*T9*T9*T9+4368.45*pow(T9,4.)+931.93597*pow(T9,5.)
							-391.07855*pow(T9,6.)+159.23101*pow(T9,7.)-34.407594*pow(T9,8.)+3.3919004*pow(T9,9.)
							+0.017556217*pow(T9,10.)-0.036253427*pow(T9,11.)+0.0031118827*pow(T9,12.)
							-0.00008714468*pow(T9,13.))*pow(T9,-1./2.))/(exp(8.4e-7*T9)*pow(1.+1.78616593*T9,3.));
				}
				else f[26]=807.406;
				if(paramrelic->err>0)
				{
					if(T9<2.5)
					{
						ferrhigh[26]=sqrt(0.0871*0.0871+pow((((0.083877015-4.5408918*T9+96.316095*T9*T9-1016.5548*T9*T9*T9
															   +4809.4834*pow(T9,4.)-168.10236*pow(T9,5.)+208.81839*pow(T9,6.)
															   -64.618239*pow(T9,7.)+10.478926*pow(T9,8.)-0.41782376*pow(T9,9.)
															   -0.06453532*pow(T9,10.)+0.004777625*pow(T9,11.)
															   +0.00020027244*pow(T9,12.)
															   -0.000017864206*pow(T9,13.))*pow(T9,-1./2.))/
															 (exp(9.3e-7*T9)*pow(1.+1.60170507*T9,3.)))/f[26]-1.,2.));
						ferrlow[26]=-sqrt(0.0871*0.0871+pow((((0.066096606-3.5622862*T9+75.13824*T9*T9-788.24146*T9*T9*T9
															   +3705.8889*pow(T9,4.)-106.98552*pow(T9,5.)+139.5561*pow(T9,6.)
															   -7.8984539*pow(T9,7.)-1.6035703*pow(T9,8.)-0.17508886*pow(T9,9.)
															   +0.046425912*pow(T9,10.)+0.0030233156*pow(T9,11.)
															   -0.00081682606*pow(T9,12.)
															   +0.000034545163*pow(T9,13.))*pow(T9,-1./2.))/
															 (exp(0.01111331*T9)*pow(1.+1.63277688*T9,3.)))/f[26]-1.,2.));
					}
					else
					{
						ferrhigh[26]=sqrt(0.0871*0.0871+pow(916.513/f[26]-1.,2.));
						ferrlow[26]=-sqrt(0.0871*0.0871+pow(698.635/f[26]-1.,2.));
					}
				}
				break;
			}

			case 27:
			{
				/* He3 + a -> g + Be7 */  // Cyburt et al. 2008 (updated from Serpico et al 2004)
				if (T9<=100.)
				{
					f[27]=exp(15.609867-(12.82707707/pow(T9,1./3.))-0.6666667*log(T9))*
							((1-0.020478*pow(T9,2./3.)+0.211995*pow(T9,4./3.))/(1+0.255059*pow(T9,2./3.)+0.338573*pow(T9,4./3.)));
				}
				else f[27]=0.;
				if(paramrelic->err>0)
				{
					if (T9<=100.)
					{
						ferrhigh[27]=exp(15.679639-(12.82707707/pow(T9,1./3.))-0.6666667*log(T9))*
								((1+0.037757*pow(T9,2./3.)+0.196645*pow(T9,4./3.))/
								 (1+0.353050*pow(T9,2./3.)+0.316019*pow(T9,4./3.)))/f[27] - 1;
						ferrlow[27]=exp(15.531721-(12.82707707/pow(T9,1./3.))-0.6666667*log(T9))*
								((1-0.100208*pow(T9,2./3.)+0.235187*pow(T9,4./3.))/
								 (1+0.114322*pow(T9,2./3.)+0.373802*pow(T9,4./3.)))/f[27] - 1;
					}
					else
					{
						ferrhigh[27]=ferrlow[27]=0.;
					}
				}
				break;
			}

			case 28:
			{
				/* H2 + H2 -> n + He3 */    // Coc et al. 2015 (updated from Pisanti et al. 2007)
				if(T9<0.001)
				{
					f[28]=1.142e-8;
				}
				else if ((T9>=0.001)&&(T9<=0.0015)) f[28]=1.142e-8;
				else if ((T9>0.0015)&&(T9<=0.0025)) f[28]=5.470e-5;
				else if ((T9>0.0025)&&(T9<=0.0035)) f[28]=3.021e-3;
				else if ((T9>0.0035)&&(T9<=0.0045)) f[28]=3.732e-2;
				else if ((T9>0.0045)&&(T9<=0.0055)) f[28]=2.212e-1;
				else if ((T9>0.0055)&&(T9<=0.0065)) f[28]=8.546e-1;
				else if ((T9>0.0065)&&(T9<=0.0075)) f[28]=2.505;
				else if ((T9>0.0075)&&(T9<=0.0085)) f[28]=6.066;
				else if ((T9>0.0085)&&(T9<=0.0095)) f[28]=1.278e1;
				else if ((T9>0.0095)&&(T9<=0.0105)) f[28]=2.424e1;
				else if ((T9>0.0105)&&(T9<=0.0115)) f[28]=4.237e1;
				else if ((T9>0.0115)&&(T9<=0.0125)) f[28]=6.936e1;
				else if ((T9>0.0125)&&(T9<=0.0135)) f[28]=1.077e2;
				else if ((T9>0.0135)&&(T9<=0.0145)) f[28]=1.600e2;
				else if ((T9>0.0145)&&(T9<=0.0155)) f[28]=2.291e2;
				else if ((T9>0.0155)&&(T9<=0.0170)) f[28]=3.179e2;
				else if ((T9>0.0170)&&(T9<=0.0190)) f[28]=5.667e2;
				else if ((T9>0.0190)&&(T9<=0.0225)) f[28]=9.310e2;
				else if ((T9>0.0225)&&(T9<=0.0275)) f[28]=2.504e3;
				else if ((T9>0.0275)&&(T9<=0.0350)) f[28]=5.301e3;
				else if ((T9>0.035)&&(T9<=0.045)) f[28]=1.568e4;
				else if ((T9>0.045)&&(T9<=0.055)) f[28]=3.369e4;
				else if ((T9>0.055)&&(T9<=0.065)) f[28]=6.013e4;
				else if ((T9>0.065)&&(T9<=0.075)) f[28]=9.527e4;
				else if ((T9>0.075)&&(T9<=0.085)) f[28]=1.390e5;
				else if ((T9>0.085)&&(T9<=0.095)) f[28]=1.912e5;
				else if ((T9>0.095)&&(T9<=0.105)) f[28]=2.513e5;
				else if ((T9>0.105)&&(T9<=0.115)) f[28]=3.190e5;
				else if ((T9>0.115)&&(T9<=0.125)) f[28]=3.938e5;
				else if ((T9>0.125)&&(T9<=0.135)) f[28]=4.753e5;
				else if ((T9>0.135)&&(T9<=0.145)) f[28]=5.631e5;
				else if ((T9>0.145)&&(T9<=0.155)) f[28]=6.568e5;
				else if ((T9>0.155)&&(T9<=0.170)) f[28]=7.559e5;
				else if ((T9>0.170)&&(T9<=0.190)) f[28]=9.691e5;
				else if ((T9>0.190)&&(T9<=0.225)) f[28]=1.200e6;
				else if ((T9>0.225)&&(T9<=0.275)) f[28]=1.842e6;
				else if ((T9>0.275)&&(T9<=0.325)) f[28]=2.555e6;
				else if ((T9>0.325)&&(T9<=0.375)) f[28]=3.318e6;
				else if ((T9>0.375)&&(T9<=0.425)) f[28]=4.119e6;
				else if ((T9>0.425)&&(T9<=0.475)) f[28]=4.946e6;
				else if ((T9>0.475)&&(T9<=0.550)) f[28]=5.792e6;
				else if ((T9>0.550)&&(T9<=0.650)) f[28]=7.517e6;
				else if ((T9>0.650)&&(T9<=0.750)) f[28]=9.260e6;
				else if ((T9>0.750)&&(T9<=0.850)) f[28]=1.100e7;
				else if ((T9>0.850)&&(T9<=0.950)) f[28]=1.272e7;
				else if ((T9>0.950)&&(T9<=1.125)) f[28]=1.442e7;
				else if ((T9>1.125)&&(T9<=1.375)) f[28]=1.850e7;
				else if ((T9>1.375)&&(T9<=1.625)) f[28]=2.235e7;
				else if ((T9>1.625)&&(T9<=1.875)) f[28]=2.595e7;
				else if ((T9>1.875)&&(T9<=2.250)) f[28]=2.932e7;
				else if ((T9>2.250)&&(T9<=2.750)) f[28]=3.546e7;
				else if ((T9>2.750)&&(T9<=3.250)) f[28]=4.093e7;
				else if ((T9>3.250)&&(T9<=3.750)) f[28]=4.585e7;
				else if ((T9>3.750)&&(T9<=4.500)) f[28]=5.031e7;
				else if ((T9>4.500)&&(T9<=5.500)) f[28]=5.816e7;
				else if ((T9>5.500)&&(T9<=6.500)) f[28]=6.488e7;
				else if ((T9>6.500)&&(T9<=7.500)) f[28]=7.072e7;
				else if ((T9>7.500)&&(T9<=8.500)) f[28]=7.583e7;
				else if ((T9>8.500)&&(T9<=9.500)) f[28]=8.037e7;
				else if ((T9>9.500)&&(T9<=10.00)) f[28]=8.437e7;
				else f[28]=0.;

				if(paramrelic->err>0)
				{
					if (T9<0.001)
					{
						ferrhigh[28]=0.011;
					}
					else if ((T9>=0.001)&&(T9<=1.625)) ferrhigh[28]=0.011;
					else if ((T9>1.625)&&(T9<=2.250)) ferrhigh[28]=0.012;
					else if ((T9>2.250)&&(T9<=2.750)) ferrhigh[28]=0.013;
					else if ((T9>2.750)&&(T9<=3.750)) ferrhigh[28]=0.014;
					else if ((T9>3.750)&&(T9<=4.500)) ferrhigh[28]=0.015;
					else if ((T9>4.5)&&(T9<=5.5)) ferrhigh[28]=0.016;
					else if ((T9>5.5)&&(T9<=6.5)) ferrhigh[28]=0.017;
					else if ((T9>6.5)&&(T9<=10.)) ferrhigh[28]=0.018;
					else
					{
						ferrhigh[28]=0.;
					}
					ferrlow[28]=1./(1+ferrhigh[28]) - 1.;
				}
				break;
			}

			case 29:
			{
				/* H2 + H2 -> p + H3 */     // Coc et al. 2015 (updated from Pisanti et al. 2007)
				if(T9<0.001)
				{
					f[29]=1.173e-8;
				}
				else if ((T9>=0.001)&&(T9<=0.0015)) f[29]=1.173e-8;
				else if ((T9>0.0015)&&(T9<=0.0025)) f[29]=5.609e-5;
				else if ((T9>0.0025)&&(T9<=0.0035)) f[29]=3.092e-3;
				else if ((T9>0.0035)&&(T9<=0.0045)) f[29]=3.814e-2;
				else if ((T9>0.0045)&&(T9<=0.0055)) f[29]=2.257e-1;
				else if ((T9>0.0055)&&(T9<=0.0065)) f[29]=8.707e-1;
				else if ((T9>0.0065)&&(T9<=0.0075)) f[29]=2.549;
				else if ((T9>0.0075)&&(T9<=0.0085)) f[29]=6.164;
				else if ((T9>0.0085)&&(T9<=0.0095)) f[29]=1.297e1;
				else if ((T9>0.0095)&&(T9<=0.0105)) f[29]=2.458e1;
				else if ((T9>0.0105)&&(T9<=0.0115)) f[29]=4.290e1;
				else if ((T9>0.0115)&&(T9<=0.0125)) f[29]=7.016e1;
				else if ((T9>0.0125)&&(T9<=0.0135)) f[29]=1.088e2;
				else if ((T9>0.0135)&&(T9<=0.0145)) f[29]=1.615e2;
				else if ((T9>0.0145)&&(T9<=0.0155)) f[29]=2.310e2;
				else if ((T9>0.0155)&&(T9<=0.0170)) f[29]=3.202e2;
				else if ((T9>0.0170)&&(T9<=0.0190)) f[29]=5.698e2;
				else if ((T9>0.0190)&&(T9<=0.0225)) f[29]=9.343e2;
				else if ((T9>0.0225)&&(T9<=0.0275)) f[29]=2.502e3;
				else if ((T9>0.0275)&&(T9<=0.0350)) f[29]=5.276e3;
				else if ((T9>0.035)&&(T9<=0.045)) f[29]=1.549e4;
				else if ((T9>0.045)&&(T9<=0.055)) f[29]=3.307e4;
				else if ((T9>0.055)&&(T9<=0.065)) f[29]=5.868e4;
				else if ((T9>0.065)&&(T9<=0.075)) f[29]=9.246e4;
				else if ((T9>0.075)&&(T9<=0.085)) f[29]=1.343e5;
				else if ((T9>0.085)&&(T9<=0.095)) f[29]=1.837e5;
				else if ((T9>0.095)&&(T9<=0.105)) f[29]=2.404e5;
				else if ((T9>0.105)&&(T9<=0.115)) f[29]=3.039e5;
				else if ((T9>0.115)&&(T9<=0.125)) f[29]=3.737e5;
				else if ((T9>0.125)&&(T9<=0.135)) f[29]=4.493e5;
				else if ((T9>0.135)&&(T9<=0.145)) f[29]=5.304e5;
				else if ((T9>0.145)&&(T9<=0.155)) f[29]=6.165e5;
				else if ((T9>0.155)&&(T9<=0.170)) f[29]=7.072e5;
				else if ((T9>0.170)&&(T9<=0.190)) f[29]=9.011e5;
				else if ((T9>0.190)&&(T9<=0.225)) f[29]=1.110e6;
				else if ((T9>0.225)&&(T9<=0.275)) f[29]=1.682e6;
				else if ((T9>0.275)&&(T9<=0.325)) f[29]=2.309e6;
				else if ((T9>0.325)&&(T9<=0.375)) f[29]=2.974e6;
				else if ((T9>0.375)&&(T9<=0.425)) f[29]=3.663e6;
				else if ((T9>0.425)&&(T9<=0.475)) f[29]=4.371e6;
				else if ((T9>0.475)&&(T9<=0.550)) f[29]=5.089e6;
				else if ((T9>0.550)&&(T9<=0.650)) f[29]=6.543e6;
				else if ((T9>0.650)&&(T9<=0.750)) f[29]=8.001e6;
				else if ((T9>0.750)&&(T9<=0.850)) f[29]=9.448e6;
				else if ((T9>0.850)&&(T9<=0.950)) f[29]=1.087e7;
				else if ((T9>0.950)&&(T9<=1.125)) f[29]=1.228e7;
				else if ((T9>1.125)&&(T9<=1.375)) f[29]=1.565e7;
				else if ((T9>1.375)&&(T9<=1.625)) f[29]=2.882e7;
				else if ((T9>1.625)&&(T9<=1.875)) f[29]=2.181e7;
				else if ((T9>1.875)&&(T9<=2.250)) f[29]=2.461e7;
				else if ((T9>2.250)&&(T9<=2.750)) f[29]=2.976e7;
				else if ((T9>2.750)&&(T9<=3.250)) f[29]=3.440e7;
				else if ((T9>3.250)&&(T9<=3.750)) f[29]=3.863e7;
				else if ((T9>3.750)&&(T9<=4.500)) f[29]=4.251e7;
				else if ((T9>4.500)&&(T9<=5.500)) f[29]=4.946e7;
				else if ((T9>5.500)&&(T9<=6.500)) f[29]=5.552e7;
				else if ((T9>6.500)&&(T9<=7.500)) f[29]=6.077e7;
				else if ((T9>7.500)&&(T9<=8.500)) f[29]=6.529e7;
				else if ((T9>8.500)&&(T9<=9.500)) f[29]=6.912e7;
				else if ((T9>9.500)&&(T9<=10.00)) f[29]=7.228e7;
				else f[29]=0.;

				if(paramrelic->err>0)
				{
					if (T9<0.001)
					{
						ferrhigh[29]=0.011;
					}
					else if ((T9>=0.001)&&(T9<=1.625)) ferrhigh[29]=0.011;
					else if ((T9>1.625)&&(T9<=2.250)) ferrhigh[29]=0.012;
					else if ((T9>2.250)&&(T9<=2.750)) ferrhigh[29]=0.013;
					else if ((T9>2.750)&&(T9<=3.750)) ferrhigh[29]=0.014;
					else if ((T9>3.750)&&(T9<=4.500)) ferrhigh[29]=0.015;
					else if ((T9>4.5)&&(T9<=5.5)) ferrhigh[29]=0.016;
					else if ((T9>4.5)&&(T9<=6.5)) ferrhigh[29]=0.017;
					else if ((T9>6.5)&&(T9<=9.5)) ferrhigh[29]=0.018;
					else if ((T9>9.5)&&(T9<=10.)) ferrhigh[29]=0.019;
					else
					{
						ferrhigh[29]=0.;
					}
					ferrlow[29]=1./(1+ferrhigh[29]) - 1.;
				}
				break;
			}

			case 30:
			{
				/* H3 + H2 -> n + He4 */    // Serpico et al. 2004
				if(T9<2.5)
				{
					f[30]=6.2265733e8/(exp(0.49711597/T9)*pow(T9,0.56785403))
							+exp(-0.23309803*T9*T9-1.342742*pow(T9,-1./3.))*(-8.1144927e7 + 2.2315324e9*T9-2.9439669e9*T9*T9
																			 +1.8764462e9*T9*T9*T9 - 6.0511612e8*pow(T9,4.)
																			 +9.5196576e7*pow(T9,5.)
																			 -5.2901086e6*pow(T9,6.))*pow(T9,-2./3.);
				}
				else f[30]=3.40249e8;
				if(paramrelic->err>0)
				{
					if(T9<2.5)
					{
						ferrhigh[30]=sqrt(0.0126*0.0126+1.4*
										  pow((6.200594e8/(exp(0.49495969/T9)*pow(T9,0.56078105))
														   +exp(-0.23797125*T9*T9-1.3784792*pow(T9,-1./3.))*
														   (-8.7018245e7+2.4114301e9*T9-3.2227206e9*T9*T9+2.0779852e9*T9*T9*T9
															-6.7739586e8*pow(T9,4.)+1.0762439e8*pow(T9,5.)
															-6.0348254e6*pow(T9,6.))*pow(T9,-2./3.))/f[30]-1.,2.));

						ferrlow[30]=-sqrt(0.0126*0.0126+1.4*
										  pow((6.3798186e8/(exp(0.49598246/T9)*pow(T9,0.58460934))
															+exp(-0.33273637*T9*T9-1.0508793*pow(T9,-1./3.))*
															(-4.0964097e7+1.064899e9*T9-7.152721e8*T9*T9-1.4155217e8*T9*T9*T9
															 +3.9276243e8*pow(T9,4.)-1.5817375e8*pow(T9,5.)
															 +2.128034e7*pow(T9,6.))*pow(T9,-2./3.))/f[30]-1.,2.));
					}
					else
					{
						ferrhigh[30]=sqrt(0.0126*0.0126+1.4*pow(3.41798e8/f[30]-1.,2.));
						ferrlow[30]=-sqrt(0.0126*0.0126+1.4*pow(3.38424e8/f[30]-1.,2.));
					}
				}
				break;
			}
			
			case 31:
			{
				/* He3 + H2 -> p + He4 */   // Serpico et al 2004
				if(T9<2.5)
				{
					f[31]=3.1038385e8/(exp(1.6190981/T9)*pow(T9,0.12159455))
							+exp(-0.0062340825*T9*T9-1.4540617*pow(T9,-1./3.))*(-3.1335916e7-6.2051071e8*T9-1.8782248e9*T9*T9
																				+6.5642773e8*T9*T9*T9+1.530887e8*pow(T9,4.)
																				-4.9542138e8*pow(T9,10./3.)
																				-1.770285e8*pow(T9,11./3.)+1.14185e8*pow(T9,1./3.)
																				-2.516526e7*pow(T9,13./3.)+1.7500204e8*pow(T9,2./3.)
																				-1.7513362e9*pow(T9,4./3.)+5.2792247e9*pow(T9,5./3.)
																				-3.32382e9*pow(T9,7./3.)+2.0346284e9*pow(T9,8./3.))*
							pow(T9,-2./3.);
				}
				else f[31]=1.55167e8;
				if(paramrelic->err>0)
				{
					if(T9<2.5)
					{
						ferrhigh[31]=sqrt(0.00299*0.00299+3.8*
										  pow((2.7540767e8/(exp(1.7895761/T9)*pow(T9,0.42535964))
															+exp(-0.011584496*T9*T9-1.7647266*pow(T9,-1./3.))*
															(-4.0539244e7-6.8068775e8*T9+1.6755542e9*T9*T9+1.3327241e9*T9*T9*T9
															 +2.5284074e8*pow(T9,4.)-8.0072489e8*pow(T9,10./3.)
															 -3.2332801e8*pow(T9,11./3.)+1.3990258e8*pow(T9,1./3.)
															 -4.0197501e7*pow(T9,13./3.)+2.4121225e8*pow(T9,2./3.)
															 -2.3960064e9*pow(T9,4./3.)+5.3331297e9*pow(T9,5./3.)
															 -7.7996883e9*pow(T9,7./3.)+3.3487409e9*pow(T9,8./3.))*pow(T9,-2./3.))/
											  f[31]-1.,2.));
						ferrlow[31]=-sqrt(0.00299*0.00299+3.8*
										  pow((2.7552759e8/(exp(1.5970464/T9)*pow(T9,0.0070474065))
															+exp(-0.0067819916*T9*T9-2.0484693*pow(T9,-1./3.))*
															(-4.6389646e6-3.2264085e9*T9+8.3768817e10*T9*T9+4.6593422e10*T9*T9*T9
															 -5.3027407e9*pow(T9,4.)-5.1730322e10*pow(T9,10./3.)
															 +2.3630624e10*pow(T9,11./3.)-2.3467142e8*pow(T9,1./3.)
															 +4.8023403e8*pow(T9,13./3.)+1.6138031e9*pow(T9,2./3.)
															 +5.5023454e9*pow(T9,4./3.)-2.9668793e10*pow(T9,5./3.)
															 -9.5677252e10*pow(T9,7./3.)+2.4498194e10*pow(T9,8./3.))*pow(T9,-2./3.))/
											  f[31]-1.,2.));											  
					}
					else
					{
						ferrhigh[31]=sqrt(0.00299*0.00299+3.8*pow(1.55567e8/f[31]-1.,2.));
						ferrlow[31]=-sqrt(0.00299*0.00299+3.8*pow(1.54638e8/f[31]-1.,2.));
					}
				}
				break;
			}

			case 32:
			{
				/* He3 + He3 -> 2p + He4 */     // NACRE 1999
				f[32]=5.59e10*pow(T9,-2./3.)*exp(-12.277/pow(T9,1./3.))*(1.-0.135*T9+2.54e-2*T9*T9 - 1.29e-3*T9*T9*T9);
				if(paramrelic->err>0)
				{
					ferrlow[32]=-1.e-2-7.34e-2-0.102*exp(-T9)+3.23e-4*T9;
					ferrhigh[32]=-ferrlow[32];
				}
				break;
			}

			case 33:
			{
				/* Li7 + H2 -> n + a + He4 */   // Serpico et al. 2004
				if (T9<2.5)
				{
					f[33]=1.66e11*pow(T9,-2./3.)*exp(-10.254/pow(T9,1./3.))+1.71e6*pow(T9,-3./2.)*exp(-3.246/T9)
							+1.49e10*pow(T9,-3./2.)*exp(-4.0894/T9)*(2.57e-2/T9+2.6314*pow(T9,-2./3.)-4.1929/pow(T9,1./3.)
																	 -2.1241+4.1136*pow(T9,1./3.));
				}
				else f[33]=1.37518e9;
				if(paramrelic->err>0)
				{
					ferrhigh[33]=0.5;
					ferrlow[33]=-0.5;
				}
				break;
			}

			case 34:
			{
				/* Be7 + H2 -> p + a + He4 */   // Caughlan-Fowler 1988
				f[34]=pow(T9,-2./3.)*1.07e12*exp(-12.428/pow(T9,1./3.));
				if(paramrelic->err>0)
				{
					ferrhigh[34]=0.9;
					ferrlow[34]=-0.9;
				}
				break;
			}

			case 35:
			{
				/* He3 + H3 -> g + Li6 */   // Fukugita-Kajino 1990
				f[35]=1.2201e6*pow(T9,-2./3.)*exp(-7.73436/pow(T9,1./3.))*(1.+5.38722e-2*pow(T9,1./3.)
																		   -.214*(1.+.377*pow(T9,1./3.))*pow(T9,2./3.)
																		   +.2733*(1.+.959*pow(T9,1./3.))*pow(T9,4./3.)
																		   -1.53e-2*(1.+.959*pow(T9,1./3.))*T9*T9)*
						(1.-.213646*pow(T9,2./3.)+.136643*pow(T9,4./3.)-7.65244e-3*T9*T9);

				if(paramrelic->err>0)
				{
					ferrlow[35]=-0.8;
					ferrhigh[35]=4.0;
				}
				break;
			}

			case 36:
			{
				/* Li6 + d -> n + Be7 */    // Malaney-Fowler 1989
				f[36]=1.48e12*pow(T9,-2./3.)*exp(-10.135/pow(T9,1./3.));

				if(paramrelic->err>0)
				{
					ferrlow[36]=-0.5;
					ferrhigh[36]=1.0;
				}
				break;
			}

			case 37:
			{
				/* Li6 + d -> n + Li7 */    // Malaney-Fowler 1989
				f[37]=1.48e12*pow(T9,-2./3.)*exp(-10.135/pow(T9,1./3.));

				if(paramrelic->err>0)
				{
					ferrlow[37]=-0.5;
					ferrhigh[37]=1.0;
				}
				break;
			}

			case 38:
			{
				/* He3 + H3 -> d + He4 */   // Caughlan-Fowler 1988
				f[38]=5.46e9*pow(T9/(1.+.128*T9),.8333333)*pow(T9,-3./2.)*exp(-7.733/(pow(T9/(1.+.128*T9),.333333)));

				if(paramrelic->err>0)
				{
					ferrlow[38]=-0.5;
					ferrhigh[38]=1.0;
				}
				break;
			}

			case 39:
			{
				/* H3 + H3 -> 2n + He4 */   // Caughlan-Fowler 1988
				f[39]=1.67e9*pow(T9,-2./3.)*exp(-4.872/pow(T9,1./3.))*(1.+8.6e-2*pow(T9,1./3.)-.455*pow(T9,2./3.)-.272*T9
																	   +.148*pow(T9,4./3.)+.225*pow(T9,5./3.));

				if(paramrelic->err>0)
				{
					ferrlow[39]=-0.5;
					ferrhigh[39]=1.0;
				}
				break;
			}

			case 40:
			{
				/* He3 + H3 -> n + p + He4 */   // Caughlan-Fowler 1988
				f[40]=7.71e9*pow(T9/(1.+.115*T9),.8333333)*pow(T9,-3./2.)*exp(-7.733/(pow(T9/(1.+.115*T9),.333333)));

				if(paramrelic->err>0)
				{
					ferrlow[40]=-0.5;
					ferrhigh[40]=1.0;
				}
				break;
			}

			case 41:
			{
				/* Li7 + H3 -> n + Be9 */   // Thomas 1993 from BKKW91
				if (T9 < 10.0)
				{
					f[41]=2.98e10*pow(T9,-2./3.)*exp(-11.333/pow(T9,1./3.))*(1.-.122*pow(T9,2./3.)
																			 +1.32/(pow(T9,4./3.)-.127*pow(T9,2./3.)+7.42e-2));
				}
				else f[41]=1.656e7;

				if(paramrelic->err>0)
				{
					ferrlow[41]=-0.21;
					ferrhigh[41]=0.21;
				}
				break;
			}

			case 42:
			{
				/* Be7 + H3 -> p + Be9 */      // Serpico et al. 2004
				if (T9 < 10.0)
				{
					f[42]=1.1*2.98e10*pow(T9,-2./3.)*exp(-13.7307/pow(T9,1./3.))*(1.-.122*pow(T9,2./3.)
																				  +1.32/(pow(T9,4./3.)-.127*pow(T9,2./3.)+7.42e-2));
				}
				else f[42]=5.98e6;

				if(paramrelic->err>0)
				{
					ferrlow[42]=-0.5;
					ferrhigh[42]=1.0;
				}
				break;
			}

			case 43:
			{
				/* Li7 + He3 -> p + Be9 */      // Serpico et al. 2004
				if (T9 < 10.0)
				{
					f[43]=1.6*2.98e10*pow(T9,-2./3.)*exp(-17.992/pow(T9,1./3.))*(1.-.122*pow(T9,2./3.)
																				 +1.32/(pow(T9,4./3.)-.127*pow(T9,2./3.)+7.42e-2));
				}
				else f[43]=1.2013e6;

				if(paramrelic->err>0)
				{
					ferrlow[43]=-0.5;
					ferrhigh[43]=1.0;
				}
				break;
			}

			case 44:
			{
				/* Li7 + n -> g + Li8 */    // Wagoner 1969
				f[44]=3.144e3+4.26e3*pow(T9,-3./2.)*exp(-2.576/T9);
				if(paramrelic->err>0)
				{
					ferrlow[44]=-0.3;
					ferrhigh[44]=0.3;
				}
				break;
			}

			case 45:
			{
				/* B10 + n -> g + B11 */    // Wagoner 1969
				f[45]=66200.;
				break;
			}

			case 46:
			{
				/* B11 + n -> g + B12 */    // Malaney-Fowler 1989
				f[46]=pow(T9,-1.5)*2400.*exp(-0.223/T9)+729.;
				break;
			}

			case 47:
			{
				/* C11 + n -> p + B11 */    // Caughlan-Fowler 1988
				f[47]=(1.-sqrt(T9)*0.048+T9*0.01)*1.69e8;
				break;
			}

			case 48:
			{
				/* B10 + n -> a + Li7 */    // NACRE 1999
				f[48]=2.2e7*(1.+1.064*T9);
				if(paramrelic->err>0)
				{
					ferrlow[48]=-0.10794+2.2003e-2*T9-3.51236e-3*T9*T9;
					ferrhigh[48]=-ferrlow[48];
				}
				break;
			}

			case 49:
			{
				/* Be7 + p -> g + B8 */     // NACRE 1999
				f[49]=2.61e5*pow(T9,-2./3.)*exp(-10.264/pow(T9,1./3.))*(1.-5.11e-2*T9+ 4.68e-2*T9*T9-6.6e-3*T9*T9*T9
																		+3.12e-4*T9*T9*T9*T9)+ 2.05e3*pow(T9,-3./2.)*exp(-7.345/T9);
				if(paramrelic->err>0)
				{
					ferrlow[49]=-0.15;
					ferrhigh[49]=0.15;
				}
				break;
			}

			case 50:
			{
				/* Be9 + p -> g + B10 */    // Caughlan-Fowler 1988
				f[50]=pow(T9,-2./3.)*1.33e7*exp(-10.359/pow(T9,1./3.)-T9/0.846*T9/0.846)*(pow(T9,1./3.)*0.04+1.+pow(T9,2./3.)*1.52
																						  +T9*0.428+pow(T9,4./3.)*2.15
																						  +pow(T9,5./3.)*1.54)
						+pow(T9,-1.5)*96400.*exp(-3.445/T9)+pow(T9,-1.5)*2.72e6*exp(-10.62/T9);
				break;
			}

			case 51:
			{
				/* B10 + p -> g + C11 */    // NACRE 1999
				f[51]=pow(T9,-2./3.)*1.68e6*exp(-pow(T9,-1./3.)*12.064)/
						(pow(pow(T9,2./3.)-0.0273,2.)+4.69e-4)*(1.+0.977*T9+1.87*T9*T9-0.272*T9*T9*T9+0.013*T9*T9*T9*T9);
				break;
			}

			case 52:
			{
				/* B11 + p -> g + C12 */    // NACRE 1999
				f[52]=pow(T9,-2./3.)*4.58e7*exp(-pow(T9,-1./3.)*12.097-pow(T9/0.6,2.))*(1.+0.353*T9-0.842*T9*T9)
						+pow(T9,-3./2.)*6.82e3*exp(-1.738/T9)+2.8e4*pow(T9,0.104)*exp(-3.892/T9);
				break;
			}

			case 53:
			{
				/* C11 + p -> g + N12 */    // Caughlan-Fowler 1988
				f[53]=pow(T9,-2./3.)*42400.*exp(-13.658/pow(T9,1./3.)-T9/1.627*T9/1.627)*(pow(T9,1./3.)*0.031+1.
																						  +pow(T9,2./3.)*3.11+T9*0.665
																						  +pow(T9,4./3.)*4.61+pow(T9,5./3.)*2.5)
						+pow(T9,-1.5)*8840.*exp(-7.021/T9);
				break;
			}

			case 54:
			{
				/* B12 + p -> n + C12 */    // Wagoner 1969
				f[54]=pow(T9,-2./3.)*4.02e11*exp(-12.12/pow(T9,1./3.));
				ferrlow[54]=-0.3;
				ferrhigh[54]=0.3;
				break;
			}

			case 55:
			{
				/* Be9 + p -> a + Li6 */    // NACRE 1999
				f[55]=2.11e11*pow(T9,-2./3.)*exp(-10.361/pow(T9,1./3.)-pow(T9/0.4,2.))*(1.-0.189*T9+3.52e1*T9*T9)
						+5.24e8*pow(T9,-3./2.)*exp(-3.446/T9)+4.65e8*exp(-4.396/T9)/(pow(T9,0.293));
				if(paramrelic->err>0)
				{
					ferrlow[55]=-0.15236-0.676965*exp(-20.*T9)+0.13113*T9*exp(-T9);
					ferrhigh[55]=9.849e-2+0.9084*exp(-20.*T9)+1.21e-2*T9-5.987e-4*T9*T9;
				}
				break;
			}

			case 56:
			{
				/* B10 + p -> a + Be7 */    // NACRE 1999
				if(T9>0.8)
				{
					f[56]=1.01e10*pow(T9,-2./3.)*exp(-12.064/pow(T9,1./3.))*(-1.+15.8*T9-2.6*T9*T9+0.125*T9*T9*T9);
				}
				else
				{
					f[56]= 2.56e10*pow(T9,-2./3.)*exp(-12.064/pow(T9,1./3.))*(1.+5.95*T9+2.92e1*T9*T9-3.16e2*T9*T9*T9
																			  +9.14e2*pow(T9,4.)-1.085e3*pow(T9,5.)
																			  +4.65e2*pow(T9,6.))/
							(4.7e-4+pow(pow(T9,2./3.)-2.6e-2,2.));
				}
				if(paramrelic->err>0)
				{
					ferrlow[56]=-0.101-0.1234*T9+1.418e-2*T9*T9-5.79e-4*T9*T9*T9;
					ferrhigh[56]=-ferrlow[56];
				}
				break;
			}

			case 57:
			{
				/* B12 + p -> a + Be9 */    // Wagoner 1969
				f[57]=pow(T9,-2./3.)*2.01e11*exp(-12.12/pow(T9,1./3.));
				ferrlow[57]=-0.3;
				ferrhigh[57]=0.3;
				break;
			}

			case 58:
			{
				/* Li6 + a -> g + B10 */    // Caughlan-Fowler 1988
				f[58]=pow(T9,-2./3.)*4.06e6*exp(-18.79/pow(T9,1./3.)-T9/1.326*T9/1.326)*(pow(T9,1./3.)*0.022+1.+pow(T9,2./3.)*1.54
																						 +T9*0.239+pow(T9,4./3.)*2.2
																						 +pow(T9,5./3.)*0.869)
						+pow(T9,-1.5)*1910.*exp(-3.484/T9)+10100./T9*exp(-7.269/T9);
				if(paramrelic->err>0)
				{
					ferrlow[58]=-0.5;
					ferrhigh[58]=1.;
				}
				break;
			}

			case 59:
			{
				/* Li7 + a -> g + B11 */    // NACRE 1999
				if(T9>1.21)
				{
					f[59]=1.187e3*pow(T9,-3./2.)*exp(-2.959/T9)+7.945e3*(1.+0.1466*T9-1.273e-2*T9*T9)*exp(-4.922/T9)/
							(pow(T9,2.3e-2));
				}
				else
				{
					f[59] = 9.72e7*pow(T9,-2./3.)*exp(-19.163/pow(T9,1./3.)-pow(T9/0.4,2.))*(1.+2.84*T9-7.89*T9*T9)
							+3.35e2*pow(T9,-3./2.)*exp(-2.959/T9)+1.04e4*exp(-4.922/T9)/(pow(T9,2.3e-2));
				}
				if(paramrelic->err>0)
				{
					ferrlow[59]=-0.2246+3.9114e-2*exp(-0.5*pow(T9-6.,2.))+3.16e-2*exp(-5.*pow(T9-0.2,2.))-0.50145*exp(-20.*T9);
					ferrhigh[59]=0.248+9.6575e-2*exp(-.5*pow(T9-6.,2.))-5.796e-2*exp(-5.*pow(T9-0.2,2.))+0.7442*exp(-20.*T9);
				}
				break;
			}

			case 60:
			{
				/* Be7 + a -> g + C11 */    // NACRE 1999
				if (T9>2.)
				{
					f[60] = 1.41e3*exp(-3.015/T9)*pow(T9,0.636);
				}
				else
				{
					f[60] = 1.29e10*pow(T9,-2./3.)*exp(-23.214/pow(T9,1./3.)-pow(T9/0.8,2.))*(1.-6.47*T9+19.5*T9*T9-19.3*T9*T9*T9)
							+1.25e4*pow(T9,-3./2.)*exp(-6.498/T9)+1.44e5*pow(T9,-3./2.)*exp(-10.177/T9)
							+1.63e4*exp(-15.281/T9)*pow(T9,0.178);
				}
				if(paramrelic->err>0)
				{
					ferrlow[60]=-0.35187+5.31e-2*T9-4.684e-2*T9*T9+6.771e-3*T9*T9*T9-3.021e-4*pow(T9,4.);
					ferrhigh[60]=0.3298+0.127*T9-3.611e-2*T9*T9+5.3544e-3*T9*T9*T9-2.6134e-4*pow(T9,4.);
				}
				break;
			}

			case 61:
			{
				/* B8 + a -> p + C11 */     // Wagoner 1969
				f[61]=pow(T9,-2./3.)*1.08e15*exp(-27.36/pow(T9,1./3.));
				break;
			}

			case 62:
			{
				/* Li8 + a -> n + B11 */    // Malaney-Fowler 1989
				f[62]=pow(T9/(T9/15.1+1.),5./6.)*8.62e13*pow(T9,-1.5)*exp(-19.461/pow(T9/(T9/15.1+1.),1./3.));
				break;
			}

			case 63:
			{
				/* Be9 + a -> n + C12 */    // Caughlan-Fowler 1988
				f[63]=pow(T9,-2./3.)*4.62e13*exp(-23.87/pow(T9,1./3.)-T9/0.049*T9/0.049)*(pow(T9,1./3.)*0.017+1.
																						  +pow(T9,2./3.)*8.57+T9*1.05
																						  +pow(T9,4./3.)*74.51+pow(T9,5./3.)*23.15)
						+pow(T9,-1.5)*7.34e-5*exp(-1.184/T9)+pow(T9,-1.5)*0.227*exp(-1.834/T9)
						+pow(T9,-1.5)*1.26e5*exp(-4.179/T9)+exp(-12.732/T9)*2.4e8;
				break;
			}

			case 64:
			{
				/* Be9 + H2 -> n + B10 */   // original Wagoner code
				f[64]=pow(T9,-2./3.)*7.16e8*exp(6.44-12.6/pow(T9,1./3.));
				break;
			}

			case 65:
			{
				/* B10 + H2 -> p + B11 */   // original Wagoner code
				f[65]=pow(T9,-2./3.)*9.53e8*exp(7.3-14.8/pow(T9,1./3.));
				break;
			}

			case 66:
			{
				/* B11 + H2 -> n + C12 */   // original Wagoner code
				f[66]=pow(T9,-2./3.)*1.41e9*exp(7.4-14.8/pow(T9,1./3.));
				break;
			}

			case 67:
			{
				/* He4 + a + n -> g + Be9 */    // Caughlan-Fowler 1988
				f[67]=2.59e-6/((T9*0.344+1.)*(T9*T9))*exp(-1.062/T9);
				break;
			}

			case 68:
			{
				/* He4 + 2a -> g + C12 */   // Caughlan-Fowler 1988
				f[68]=pow(T9,-1.5)*2.79e-8*pow(T9,-1.5)*exp(-4.4027/T9)+pow(T9,-1.5)*1.35e-8*exp(-24.811/T9);
				break;
			}

			case 69:
			{
				/* Li8 + p -> n + a + He4 */    // original Wagoner code
				f[69]=pow(T9,-2./3.)*8.65e9*exp(-8.52/pow(T9,1./3.)-T9/2.53*T9/2.53)+pow(T9,-1.5)*2.31e9*exp(-4.64/T9);
				break;
			}
			
			case 70:
			{
				/* B8 + n -> p + a + He4 */     // original Wagoner code
				f[70]=4.02e8;
				break;
			}

			case 71:
			{
				/* Be9 + p -> d + a + He4 */    // Caughlan-Fowler 1988
				f[71]=pow(T9,-2./3.)*2.11e11*exp(-10.359/pow(T9,1./3.)-T9/0.52*T9/0.52)*(pow(T9,1./3.)*0.04+1.
																						 +pow(T9,2./3.)*1.09+T9*0.307
																						 +pow(T9,4./3.)*3.21+pow(T9,5./3.)*2.3)
						+5.79e8/T9*exp(-3.046/T9)+pow(T9,-0.75)*8.5e8*exp(-5.8/T9);
				break;
			}
			
			case 72:
			{
				/* B11 + p -> 2a + He4 */   // Caughlan-Fowler 1988
				f[72]=pow(T9,-2./3.)*2.2e12*exp(-12.095/pow(T9,1./3.)-T9/1.644*T9/1.644)*(pow(T9,1./3.)*0.034+1.
																						  +pow(T9,2./3.)*0.14+T9*0.034
																						  +pow(T9,4./3.)*0.19+pow(T9,5./3.)*0.116)
						+pow(T9,-1.5)*4.03e6*exp(-1.734/T9)+pow(T9,-1.5)*6.73e9*exp(-6.262/T9)+3.88e9/T9*exp(-14.154/T9);
				break;
			}
			
			case 73:
			{
				/* C11 + n -> 2a + He4 */   // Wagoner 1969
				f[73]=1.58e8;
				break;
			}
			
			case 74:
			{
				/* C12 + n -> g + C13 */    // Wagoner 1969
				f[74]=450.;
				break;
			}
			
			case 75:
			{
				/* C13 + n -> g + C14 */    // Wagoner 1969
				f[75]=pow(T9,-1.5)*2.38e5*exp(-1.67/T9)+119.;
				break;
			}
			
			case 76:
			{
				/* N14 + n -> g + N15 */    // Wagoner 1969
				f[76]=9940.;
				break;
			}
			
			case 77:
			{
				/* N13 + n -> p + C13 */    // NACRE 1999
				f[77]= 1.178e8*(1.+3.36e-1*T9-3.792e-2*T9*T9+2.02e-3*T9*T9*T9);
				// Contribution from thermal excited levels (NACRE 1999)
				f[77]*=(1.+1.131*exp(-1.2892e1/T9+1.9e-2*T9));
				ferrlow[77]=-0.3; /* CHECK!!! */
				ferrhigh[77]=0.3; /* CHECK!!!! */
				break;
			}
			
			case 78:
			{
				/* N14 + n -> p + C14 */    // Caughlan-Fowler 1988
				f[78]=(sqrt(T9)*0.361+1.+T9*0.502)*2.39e5+1.112e8/sqrt(T9)*exp(-4.983/T9);
				break;
			}
			
			case 79:
			{
				/* O15 + n -> p + N15 */    // NACRE 1999
				f[79] = 1.158e8*(1.+2.19e-1*T9-2.9e-2*T9*T9+1.73e-3*T9*T9*T9);
				// Contribution from thermal excited levels (NACRE 1999)
				f[79]*=(1.+3.87e-1*exp(-26.171/T9+1.18e-1*T9));
				break;
			}
			
			case 80:
			{
				/* O15 + n -> a + C12 */    // Caughlan-Fowler 1988
				f[80]=(sqrt(T9)*0.188+1.+T9*0.015)*3.5e7;
				break;
			}
			
			case 81:
			{
				/* C12 + p -> g + N13 */    // NACRE 1999
				f[81]=2.e7*pow(T9,-2./3.)*exp(-13.692*pow(T9,-1./3.)-pow(T9/0.46,2.))*(1.+9.89*T9-59.8*T9*T9+266.*T9*T9*T9)
						+1.e5*pow(T9,-3./2.)*exp(-4.913/T9)+4.24e5*pow(T9,-3./2.)*exp(-21.62/T9);
				break;
			}
			
			case 82:
			{
				/* C13 + p -> g + N14 */    // NACRE 1999
				f[82]=9.57e7*pow(T9,-2./3.)*exp(-13.720*pow(T9,-1./3.)-T9*T9)*(1.+3.56*T9)+1.5e6*pow(T9,-3./2.)*exp(-5.930/T9)
						+6.83e5*pow(T9,-8.64e-1)*exp(-12.057/T9);
				// Contribution from thermal excited levels (NACRE 1999)
				f[82]*=(1.-2.07*exp(-37.938/T9));
				break;
			}
			
			case 83:
			{
				/* C14 + p -> g + N15 */    // Caughlan-Fowler 1988
				f[83]=pow(T9,-2./3.)*6.8e6*exp(-13.741/pow(T9,1./3.)-T9/5.721*T9/5.721)*(pow(T9,1./3.)*0.03+1.+pow(T9,2./3.)*0.503
																						 +T9*0.107+pow(T9,4./3.)*0.213
																						 +pow(T9,5./3.)*0.115)
						+pow(T9,-1.5)*5360.*exp(-3.811/T9)+pow(T9,-1./3.)*98200.*exp(-4.739/T9);
				break;
			}
			
			case 84:
			{
				/* N13 + p -> g + O14 */    // Caughlan-Fowler 1988
				f[84]=pow(T9,-2./3.)*4.04e7*exp(-15.202/pow(T9,1./3.)-T9/1.191*T9/1.191)*(pow(T9,1./3.)*0.027+1.
																						  -pow(T9,2./3.)*0.803-T9*0.154
																						  +pow(T9,4./3.)*5.+pow(T9,5./3.)*2.44)
						+pow(T9,-1.5)*2.43e5*exp(-6.348/T9);
				break;
			}
			
			case 85:
			{
				/* N14 + p -> g + O15 */    // Caughlan-Fowler 1988
				f[85]=pow(T9,-2./3.)*4.9e7*exp(-15.228/pow(T9,1./3.)-T9/3.294*T9/3.294)*(pow(T9,1./3.)*0.027+1.
																						 -pow(T9,2./3.)*0.778
																						 -T9*0.149+pow(T9,4./3.)*0.261
																						 +pow(T9,5./3.)*0.127)
						+pow(T9,-1.5)*2370.*exp(-3.011/T9)+exp(-12.53/T9)*21900.;
				break;
			}
			
			case 86:
			{
				/* N15 + p -> g + O16 */    // Caughlan-Fowler 1988
				f[86]=pow(T9,-2./3.)*9.78e8*exp(-15.251/pow(T9,1./3.)-T9/0.45*T9/0.45)*(pow(T9,1./3.)*0.027+1.+pow(T9,2./3.)*0.219
																						+T9*0.042+pow(T9,4./3.)*6.83
																						+pow(T9,5./3.)*3.32)
						+pow(T9,-1.5)*11100.*exp(-3.328/T9)+pow(T9,-1.5)*14900.*exp(-4.665/T9)+pow(T9,-1.5)*3.8e6*exp(-11.048/T9);
				break;
			}
			
			case 87:
			{
				/* N15 + p -> a + C12 */    // NACRE 1999
				if (T9>2.5)
				{
					f[87]= 4.17e7*pow(T9,0.917)*exp(-3.292/T9);
				}
				else
				{
					f[87]= 1.12e12*pow(T9,-2./3.)*exp(-15.253*pow(T9,-1./3.)-pow(T9/0.28,2.))*(1.+4.95*T9+143.*T9*T9)
							+1.01e8*pow(T9,-3./2.)*exp(-3.643/T9)+1.19e9*pow(T9,-3./2.)*exp(-7.406/T9);
				}
				break;
			}
			
			case 88:
			{
				/* C12 + a -> g + O16 */    // Caughlan-Fowler 1988
				f[88]=1.04e8/(T9*T9)*exp(-32.12/pow(T9,1./3.)-T9/3.496*T9/3.496)/pow(pow(T9,-2./3.)*0.0489+1.,2.)
						+1.76e8/(T9*T9)/pow(pow(T9,-2./3.)*0.2654+1.,2.)*exp(-32.12/pow(T9,1./3.))
						+pow(T9,-1.5)*1250.*exp(-27.499/T9)+pow(T9,5.)*0.0143*exp(-15.541/T9);
				break;
			}
			
			case 89:
			{
				/* B10 + a -> p + C13 */    // Wagoner 1969
				f[89]=pow(T9,-2./3.)*9.6e14*exp(-27.99/pow(T9,1./3.));
				break;
			}
			
			case 90:
			{
				/* B11 + a -> p + C14 */    // Caughlan-Fowler 1988
				f[90]=pow(T9,-2./3.)*5.37e11*exp(-28.234/pow(T9,1./3.)-T9/0.347*T9/0.347)*(pow(T9,1./3.)*0.015+1.
																						   +pow(T9,2./3.)*5.575+T9*0.576
																						   +pow(T9,4./3.)*15.888
																						   +pow(T9,5./3.)*4.174)
						+pow(T9,-1.5)*0.00544*exp(-2.827/T9)+pow(T9,-1.5)*336.*exp(-5.178/T9)+5.32e6/pow(T9,0.375)*exp(-11.617/T9);
				break;
			}
			
			case 91:
			{
				/* C11 + a -> p + N14 */    // Caughlan-Fowler 1988
				f[91]=pow(T9/(T9*0.0478+1.+pow(T9,5./3.)*0.00756/pow(T9*0.0478+1.,2./3.)),5./6.)*
						7.15e15*pow(T9,-1.5)*exp(-31.883/pow(T9/(T9*0.0478+1.+pow(T9,5./3.)*0.00756/pow(T9*0.0478+1.,2./3.)),1./3.));
				// Contribution from thermal excited levels (NACRE 1999)
				f[91]*= (1.+0.140*exp(-0.275/T9-0.210*T9));
				break;
			}
			
			case 92:
			{
				/* N12 + a -> p + O15 */    // Caughlan-Fowler 1988
				f[92]=pow(T9,-2./3.)*5.59e16*exp(-35.6/pow(T9,1./3.));
				break;
			}
			
			case 93:
			{
				/* N13 + a -> p + O16 */    // Caughlan-Fowler 1988
				f[93]=pow(T9/(T9*0.0776+1.+pow(T9,5./3.)*0.0264/pow(T9*0.0776+1.,2./3.)),5./6.)
						*3.23e17*pow(T9,-1.5)*exp(-35.829/pow(T9/(T9*0.0776+1.+pow(T9,5./3.)*0.0264/pow(T9*0.0776+1.,2./3.)),1./3.));
				break;
			}
			
			case 94:
			{
				/* B10 + a -> n + N13 */    // Caughlan-Fowler 1988
				f[94]=pow(T9,-2./3.)*1.2e13*exp(-27.989/pow(T9,1./3.)-T9/9.589*T9/9.589);
				break;
			}
			
			case 95:
			{
				/* B11 + a -> n + N14 */    // Caughlan-Fowler 1988
				f[95]=pow(T9,-2./3.)*6.97e12*exp(-28.234/pow(T9,1./3.)-T9/0.14*T9/0.14)*(pow(T9,1./3.)*0.015+1.+pow(T9,2./3.)*8.115
																						 +T9*0.838+pow(T9,4./3.)*39.804
																						 +pow(T9,5./3.)*10.456)
						+pow(T9,-1.5)*1.79*exp(-2.827/T9)+pow(T9,-1.5)*1710.*exp(-5.178/T9)+pow(T9,0.6)*4.49e6*exp(-8.596/T9);
				break;
			}
			
			case 96:
			{
				/* B12 + a -> n + N15 */    // Wagoner 1969
				f[96]=pow(T9,-2./3.)*3.04e15*exp(-28.45/pow(T9,1./3.));
				break;
			}
			
			case 97:
			{
				/* C13 + a -> n + O16 */    // NACRE 1999
				if(T9>4.)
				{
					f[97]= 7.59e6*pow(T9,1.078)*exp(-12.056/T9);
				}
				else
				{
					f[97]= 3.78e14/T9/T9*exp(-32.333*pow(T9,-1./3.)-pow(T9/0.71,2.))*(1.+4.68e1*T9-2.92e2*T9*T9+7.38e2*T9*T9*T9)
							+2.3e7*pow(T9,0.45)*exp(-13.03/T9);
				}
				// Contribution from thermal excited levels (NACRE 1999)
				f[97]*=(1.+7.3318e1*exp(-58.176/T9-1.98e-1*T9));
				break;
			}

			case 98:
			{
				/* B11 + d -> p + B12 */    // Iocco et al 2007
				f[98]=.60221*((4.97838e13*exp(-14.8348*pow(.0215424+1./T9,1./3.))*pow(.0215424+1./T9,1./6.)*pow(T9,-0.5))/
							  (46.42+T9)+exp(-14.835*pow(T9,-1./3.))*(6.52581e9+(1.56921e11-4.074e9*pow(T9,1./3.)+1.28302e9*T9)*
																	  pow(T9,-2./3.)));

				if(paramrelic->err>0)
				{
					ferrlow[98]=-0.9;
					ferrhigh[98]=9.0;
				}
				break;
			}

			case 99:
			{
				/* C12 + d -> p + C13 */    // Iocco et al 2007
				f[99]=6.60999e12*pow(T9,-2./3.)*exp(-16.8242*pow(T9,-1./3.)-.234041*pow(T9,2./3.))*
						(1.-exp(-1.10272*(1.+.921391*pow(T9,1./3.))*(1.+.921391*pow(T9,1./3.))));

				if(paramrelic->err>0)
				{
					ferrlow[99]=-0.9;
					ferrhigh[99]=9.0;
				}
				break;
			}
			
			case 100:
			{
				/* C13 + d -> p + C14 */    // Iocco et al 2007
				f[100]=7.23773e12*pow(T9,-2./3.)*exp(-16.8869*pow(T9,-1./3.)-.242434*pow(T9,2./3.))*
						(1.-exp(-1.08715*(1.+.944456*pow(T9,1./3.))*(1.+.944456*pow(T9,1./3.))));

				if(paramrelic->err>0)
				{
					ferrlow[100]=-0.9;
					ferrhigh[100]=9.0;
				}
				break;
			}
		}
	}

    /* ############################################################# */

#ifdef REACLIB

#include "bbnrate.h"

#if defined(_OPENMP) && NMAX>30	
#pragma omp parallel for
#endif
	for(ie=101;ie<=NNUCREAC;ie++)
	{
		if(af[ie][0]==0.)
		{
			f[ie]=0.;
		}
		else
		{
			double temp;
			int je;
		
			if(T9<=10.&&T9>=0.01) 
			{
				temp=af[ie][0];
				
				for(je=1;je<=5;je++) temp+=af[ie][je]*pow(T9,(2.*je-5.)/3.);
				temp+=af[ie][6]*log(T9);
					
				f[ie]=exp(temp);
			}
			else if(T9>10.)
			{
				int ke;
				double T9tmp;
				double sav[2];

				temp=af[ie][0];
			
				for(je=0;je<=1;je++) 
				{
					T9tmp=5.+5.*je;

					temp=af[ie][0];
					for(ke=1;ke<=5;ke++) temp+=af[ie][ke]*pow(T9tmp,(2.*ke-5.)/3.);
					temp+=af[ie][6]*log(T9tmp);
					
					sav[je]=exp(temp);
				}
				f[ie]=((sav[1]-sav[0]))*(log(10.)-log(5.))*(log(T9)-log(5.))+sav[0];
			}
			else
			{
				int ke;
				double T9tmp;
				double sav[2];

				temp=af[ie][0];

				for(je=0;je<=1;je++) 
				{
					T9tmp=0.01+0.04*je;

					temp=af[ie][0];
					for(ke=1;ke<=5;ke++) temp+=af[ie][ke]*pow(T9tmp,(2.*ke-5.)/3.);
					temp+=af[ie][6]*log(T9tmp);
					
					sav[je]=exp(temp);
				}
				f[ie]=((sav[1]-sav[0]))*(log(0.05)-log(0.01))*(log(T9)-log(0.01))+sav[0];
			}
		}
	}
#endif

    /* ############################################################# */

    for(ie=12;ie<=NNUCREAC;ie++) f[ie]=max(0.,f[ie]);
    
    if(paramrelic->err>0)
    {
        for(ie=12;ie<=NNUCREAC;ie++)
        {
            if((ferrhigh[ie]<0.)||(ferrhigh[ie]>9.)) ferrhigh[ie]=9.;
            if((ferrlow[ie]>0.)||(ferrlow[ie]<-0.9)) ferrlow[ie]=-0.9;
            if(paramrelic->err==1) f[ie]*=1.+ferrhigh[ie];
            if(paramrelic->err==2) f[ie]*=1.+ferrlow[ie];
 			if(paramrelic->err==4) 
 			{
				if(paramerror->random[ie]<0.) f[ie]*=max(0.1,1.-max(LOWERR,ferrlow[ie])*paramerror->random[ie]);
				else f[ie]*=min(9.,1.+min(UPPERR,ferrhigh[ie])*paramerror->random[ie]);
			}
		}
		if(paramrelic->err==3 && paramerror->errnumber>=2 && paramerror->errnumber<=NNUCREAC) f[paramerror->errnumber]*=min(9.,1.+min(UPPERR,ferrhigh[paramerror->errnumber]));
    }

    return;
}
