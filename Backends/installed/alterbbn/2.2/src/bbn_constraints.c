#include "include.h"

/*----------------------------------------------------*/

int bbn_excluded(struct relicparam* paramrelic)
{
	int ie,je;
    double ratioH[NNUC+1];
	
    int nobs=paramrelic->constraints;
    
    double observed[4],sigmaobs[4];
    int translate[4];
   
	translate[0]=6;  // Yp=ratioH[6]
    translate[1]=3;  // H2_H=ratioH[3]
	translate[3]=8;  // Li7_H=ratioH[8]
	translate[4]=5;  // He3_H=ratioH[5]
		
	observed[0]=0.245;     // Yp - PDG 2019
	observed[1]=2.569e-5;  // H2_H - PDG 2019
	observed[2]=1.6e-10;   // Li7_H - PDG 2019
	observed[3]=1.1e-5;    // He3_H 

	sigmaobs[0]=0.003;
	sigmaobs[1]=0.027e-5;
	sigmaobs[2]=0.3e-10;
	sigmaobs[3]=0.2e-5;

	double chi2=0.;
    
    if(paramrelic->err<3)
    {
		if(nucl(paramrelic,ratioH)!=0) return -1;

		double sigmath[4];
		
		if(paramrelic->failsafe%5==0) /* imprecise integration method */
		{
			sigmath[0]=10.e-4;
			sigmath[1]=25.e-7;
			sigmath[2]=4.e-11;
			sigmath[3]=4.e-7;
		}
		else if(paramrelic->failsafe%5==1) /* intermediate precision integration method */
		{
			sigmath[0]=4.e-4;
			sigmath[1]=10.e-7;
			sigmath[2]=4.e-11;
			sigmath[3]=2.e-7;
		}
		else /* precise integration method */
		{
			sigmath[0]=3.2e-4;
			sigmath[1]=5.4e-7;
			sigmath[2]=3.7e-11;
			sigmath[3]=1.7e-7;
		}
		
		for(ie=0;ie<nobs;ie++) chi2+=pow((ratioH[translate[ie]]-observed[ie]),2.)/(sigmaobs[ie]*sigmaobs[ie]+sigmath[ie]*sigmath[ie]);
    }
    else
    {   
		double cov_ratioH[NNUC+1][NNUC+1];
		double **cov,**invcov;

		cov=(double **) malloc(nobs*sizeof(double *));
		for(ie=0;ie<nobs;ie++) cov[ie]=(double *) malloc(nobs*sizeof(double));	

		invcov=(double **) malloc(nobs*sizeof(double *));
		for(ie=0;ie<nobs;ie++) invcov[ie]=(double *) malloc(nobs*sizeof(double));
		
		if(nucl_err(paramrelic,ratioH,cov_ratioH)==0) return -1;
					
		for(ie=0;ie<nobs;ie++) for(je=0;je<nobs;je++) cov[ie][je]=pow(sigmaobs[ie],2.)*(ie==je)+cov_ratioH[translate[ie]][translate[je]];
		
		if(invert_matrix(nobs,cov,invcov)==0) return -1;
		
		double chi2=0.;
		for(ie=0;ie<nobs;ie++) for(je=0;je<nobs;je++) chi2+=(ratioH[translate[ie]]-observed[ie])*invcov[ie][je]*(ratioH[translate[ie]]-observed[je]);
	}

	double CL;
	
	switch(nobs)
	{
		case 1: CL=4.; break;
		case 2: CL=6.18; break;
		case 3: CL=8.02; break;
		case 4: CL=9.72; break;
	}

	if(chi2>CL) return 1; else return 0;
}
