#include "src/include.h"

/*--------------------------------------------------------*/
/* Calculation of the observables in the Standard Model   */
/*--------------------------------------------------------*/

int main(int argc,char** argv)
{ 
	struct relicparam paramrelic;
	double ratioH[NNUC+1],cov_ratioH[NNUC+1][NNUC+1];
	double eta,H2_H,He3_H,Yp,Li7_H,Li6_H,Be7_H;
	double sigma_H2_H,sigma_He3_H,sigma_Yp,sigma_Li7_H,sigma_Li6_H,sigma_Be7_H;
    double Nnu,dNnu,tau,tau_err;
    int failsafe;

    if(argc<5)
  	{ 
                printf(" This program needs at least 4 parameters:\n"
           	    "   eta    value of the baryon-to-photon ratio\n"
                "   Nnu      number of SM neutrinos\n"
                "   dNnu     number of extra neutrino species\n"
                "   tau      neutron lifetime\n"
                " Auxiliary parameters are:\n"
				"   failsafe    0=fast, 1=precise, 6=robust but slow. See stand_cosmo.c for more options.\n"
                "   tau_err  neutron lifetime uncertainty (optional, needed for error calculation)\n");
      		exit(1); 
  	} 
	else 
  	{
				sscanf(argv[1],"%lf",&eta);
                sscanf(argv[2],"%lf",&Nnu);
                sscanf(argv[3],"%lf",&dNnu);
                sscanf(argv[4],"%lf",&tau);
				if(argc>5) sscanf(argv[5],"%d",&failsafe); else failsafe=1;   
                if(argc>6) sscanf(argv[5],"%lf",&tau_err); else tau_err=1.0;
  	}
	
	Init_cosmomodel(&paramrelic);
	
	paramrelic.failsafe=failsafe;

    Init_cosmomodel_param(eta,Nnu,dNnu,tau,tau_err,0.,0.,0.,&paramrelic);
	
	printf("\t Yp\t\t H2/H\t\t He3/H\t\t Li7/H\t\t Li6/H\t\t Be7/H\n");
	paramrelic.err=2;
	nucl(&paramrelic,ratioH);
	H2_H=ratioH[3];Yp=ratioH[6];Li7_H=ratioH[8];Be7_H=ratioH[9];He3_H=ratioH[5];Li6_H=ratioH[7];
	printf("  low:\t %.3e\t %.3e\t %.3e\t %.3e\t %.3e\t %.3e\n",Yp,H2_H,He3_H,Li7_H,Li6_H,Be7_H);

	paramrelic.err=0;
	nucl(&paramrelic,ratioH);
	H2_H=ratioH[3];Yp=ratioH[6];Li7_H=ratioH[8];Be7_H=ratioH[9];He3_H=ratioH[5];Li6_H=ratioH[7];
	printf(" cent:\t %.3e\t %.3e\t %.3e\t %.3e\t %.3e\t %.3e\n",Yp,H2_H,He3_H,Li7_H,Li6_H,Be7_H); 
	
	paramrelic.err=1;
	nucl(&paramrelic,ratioH);
	H2_H=ratioH[3];Yp=ratioH[6];Li7_H=ratioH[8];Be7_H=ratioH[9];He3_H=ratioH[5];Li6_H=ratioH[7];
	printf(" high:\t %.3e\t %.3e\t %.3e\t %.3e\t %.3e\t %.3e\n\n",Yp,H2_H,He3_H,Li7_H,Li6_H,Be7_H);
			
	paramrelic.err=3;
	if(nucl_err(&paramrelic,ratioH,cov_ratioH))
	{
		printf("--------------------\n\n");
		printf("With uncertainties:\n");
        H2_H=ratioH[3];Yp=ratioH[6];Li7_H=ratioH[8];Be7_H=ratioH[9];He3_H=ratioH[5];Li6_H=ratioH[7];
		sigma_H2_H=sqrt(cov_ratioH[3][3]);sigma_Yp=sqrt(cov_ratioH[6][6]);sigma_Li7_H=sqrt(cov_ratioH[8][8]);sigma_Be7_H=sqrt(cov_ratioH[9][9]);sigma_He3_H=sqrt(cov_ratioH[5][5]);sigma_Li6_H=sqrt(cov_ratioH[7][7]);
		printf("\t Yp\t\t H2/H\t\t He3/H\t\t Li7/H\t\t Li6/H\t\t Be7/H\n");
		
		printf("value:\t %.3e\t %.3e\t %.3e\t %.3e\t %.3e\t %.3e\n",Yp,H2_H,He3_H,Li7_H,Li6_H,Be7_H); 
		printf(" +/- :\t %.3e\t %.3e\t %.3e\t %.3e\t %.3e\t %.3e\n\n",sigma_Yp,sigma_H2_H,sigma_He3_H,sigma_Li7_H,sigma_Li6_H,sigma_Be7_H);

		double corr_ratioH[NNUC+1][NNUC+1];
		for(int ie=1;ie<=NNUC;ie++) for(int je=1;je<=NNUC;je++) corr_ratioH[ie][je]=cov_ratioH[ie][je]/sqrt(cov_ratioH[ie][ie]*cov_ratioH[je][je]);
		printf("Correlation matrix:\n");
		printf("\t Yp\t\t H2/H\t\t He3/H\t\t Li7/H\t\t Li6/H\t\t Be7/H\n");
		printf("Yp\t %f\t %f\t %f\t %f\t %f\t %f\n",corr_ratioH[6][6],corr_ratioH[6][3],corr_ratioH[6][5],corr_ratioH[6][8],corr_ratioH[6][7],corr_ratioH[6][9]);
		printf("H2/H\t %f\t %f\t %f\t %f\t %f\t %f\n",corr_ratioH[3][6],corr_ratioH[3][3],corr_ratioH[3][5],corr_ratioH[3][8],corr_ratioH[3][7],corr_ratioH[3][9]);
		printf("He3/H\t %f\t %f\t %f\t %f\t %f\t %f\n",corr_ratioH[5][6],corr_ratioH[5][3],corr_ratioH[5][5],corr_ratioH[5][8],corr_ratioH[5][7],corr_ratioH[5][9]);
		printf("Li7/H\t %f\t %f\t %f\t %f\t %f\t %f\n",corr_ratioH[8][6],corr_ratioH[8][3],corr_ratioH[8][5],corr_ratioH[8][8],corr_ratioH[8][7],corr_ratioH[8][9]);
		printf("Li6/H\t %f\t %f\t %f\t %f\t %f\t %f\n",corr_ratioH[7][6],corr_ratioH[7][3],corr_ratioH[7][5],corr_ratioH[7][8],corr_ratioH[7][7],corr_ratioH[7][9]);
		printf("Be7/H\t %f\t %f\t %f\t %f\t %f\t %f\n\n",corr_ratioH[9][6],corr_ratioH[9][3],corr_ratioH[9][5],corr_ratioH[9][8],corr_ratioH[9][7],corr_ratioH[9][9]);
	}
	else printf("Uncertainty calculation failed\n\n");

	/*paramrelic.err=4;
	if(nucl_err(&paramrelic,ratioH,cov_ratioH))
	{
		printf("--------------------\n\n");
		printf("With MC uncertainties:\n");
        H2_H=ratioH[3];Yp=ratioH[6];Li7_H=ratioH[8];Be7_H=ratioH[9];He3_H=ratioH[5];Li6_H=ratioH[7];
		sigma_H2_H=sqrt(cov_ratioH[3][3]);sigma_Yp=sqrt(cov_ratioH[6][6]);sigma_Li7_H=sqrt(cov_ratioH[8][8]);sigma_Be7_H=sqrt(cov_ratioH[9][9]);sigma_He3_H=sqrt(cov_ratioH[5][5]);sigma_Li6_H=sqrt(cov_ratioH[7][7]);
		printf("\t Yp\t\t H2/H\t\t He3/H\t\t Li7/H\t\t Li6/H\t\t Be7/H\n");
		
		printf("mean:\t %.3e\t %.3e\t %.3e\t %.3e\t %.3e\t %.3e\n",Yp,H2_H,He3_H,Li7_H,Li6_H,Be7_H); 
		printf(" +/- :\t %.3e\t %.3e\t %.3e\t %.3e\t %.3e\t %.3e\n\n",sigma_Yp,sigma_H2_H,sigma_He3_H,sigma_Li7_H,sigma_Li6_H,sigma_Be7_H);

		double corr_ratioH[NNUC+1][NNUC+1];
		for(int ie=1;ie<=NNUC;ie++) for(int je=1;je<=NNUC;je++) corr_ratioH[ie][je]=cov_ratioH[ie][je]/sqrt(cov_ratioH[ie][ie]*cov_ratioH[je][je]);
		printf("Correlation matrix:\n");
		printf("\t Yp\t\t H2/H\t\t He3/H\t\t Li7/H\t\t Li6/H\t\t Be7/H\n");
		printf("Yp\t %f\t %f\t %f\t %f\t %f\t %f\n",corr_ratioH[6][6],corr_ratioH[6][3],corr_ratioH[6][5],corr_ratioH[6][8],corr_ratioH[6][7],corr_ratioH[6][9]);
		printf("H2/H\t %f\t %f\t %f\t %f\t %f\t %f\n",corr_ratioH[3][6],corr_ratioH[3][3],corr_ratioH[3][5],corr_ratioH[3][8],corr_ratioH[3][7],corr_ratioH[3][9]);
		printf("He3/H\t %f\t %f\t %f\t %f\t %f\t %f\n",corr_ratioH[5][6],corr_ratioH[5][3],corr_ratioH[5][5],corr_ratioH[5][8],corr_ratioH[5][7],corr_ratioH[5][9]);
		printf("Li7/H\t %f\t %f\t %f\t %f\t %f\t %f\n",corr_ratioH[8][6],corr_ratioH[8][3],corr_ratioH[8][5],corr_ratioH[8][8],corr_ratioH[8][7],corr_ratioH[8][9]);
		printf("Li6/H\t %f\t %f\t %f\t %f\t %f\t %f\n",corr_ratioH[7][6],corr_ratioH[7][3],corr_ratioH[7][5],corr_ratioH[7][8],corr_ratioH[7][7],corr_ratioH[7][9]);
		printf("Be7/H\t %f\t %f\t %f\t %f\t %f\t %f\n\n",corr_ratioH[9][6],corr_ratioH[9][3],corr_ratioH[9][5],corr_ratioH[9][8],corr_ratioH[9][7],corr_ratioH[9][9]);
	}
	else printf("Uncertainty calculation failed\n\n");*/
		
	paramrelic.err=0;
	int compat=bbn_excluded(&paramrelic);

	if(compat==1) printf("Excluded by BBN constraints (chi2 without correlations)\n");
	else if(compat==0) printf("Compatible with BBN constraints (chi2 without correlations)\n");
	else printf("Computation failed (chi2 without correlations)\n");

	paramrelic.err=3;
	compat=bbn_excluded(&paramrelic);

	if(compat==1) printf("Excluded by BBN constraints (chi2 including correlations)\n");
	else if(compat==0) printf("Compatible with BBN constraints (chi2 including correlations)\n");
	else printf("Computation failed (chi2 including correlations)\n");

	return 1;
}
