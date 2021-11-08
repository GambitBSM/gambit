// All functions and structures are initialized in this file

//#define REACLIB         // Uncomment to use the REACLIB network

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <complex.h>
#include <string.h>
#include <strings.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>

/*--------------------------------------------------------------------*/

/*#define DEBUG*/

/*--------------------------------------------------------------------*/

#define pi    		3.1415926535897932385
#define zeta3 		1.2020569031595942855
#define Gn    		6.67428e-8  /* in cm^3.g^-1.s^-2 */
#define K_to_eV     8.617330637338339e-05 /* conversion factor T(10**9 K) * K_to_GeV = T(GeV) or T(K) * K_to_eV = T(eV) */
#define m_e    		510.9989461e-6 /* electron mass in GeV */
#define M_u         1.660538921e-24 /* unit atomic mass M_u in g */
#define g_to_GeV    5.60958884538932e+23 /* conversion factor M(g) * g_to_GeV = M(GeV) */
#define kg_to_GeV   5.60958884538932e+26 /* conversion factor M(kg) * kg_to_GeV = M(GeV) */
#define sigma_SB    0.16449340668482282 /* Stefan-Boltzmann constant = pi^2/60 */
#define m_to_GeV    5.067730582705779e+15 /* conversion factor L(m) * m_to_GeV = L(GeV^-1) */
#define cm_to_GeV   5.067730582705779e+13 /* conversion factor L(cm) * cm_to_GeV = L(GeV^-1) */
#define s_to_GeV    1.5192674078711377e+24 /* conversion factor t(s) * s_to_GeV = t(GeV^-1) */
#define G           6.708609142443796e-39 /* Gn*pow(m_to_GeV,3.)*pow(g_to_GeV,-1.)*pow(s_to_GeV,-2.) Newton constant in GeV^-2 */
#define Mplanck     1.2209102930946623e+19 /* in GeV, more precise definition than before */
#define DMpn        0.0012934 /* mass difference between neutron and proton in GeV */
#define zeta        1.6103162253325862 /* 3*k_B/(2*c^2*Mu) in GeV^-1 */
#define k_B			8.617330e-5		/* Boltzmann's constant in GeV/GK */
#define alphaem  		0.007297353 /* fine-structure constant */
#define M_pl			2.435363682463831e+18 /* reduced plank mass in GeV */

/*--------------------------------------------------------------------*/

#ifdef REACLIB
	//#define CHECKLOW        // Uncomment to check if an isotope has a very low abundance
	#ifdef CHECKLOW
		#define Ylow 1.e-25     // Lower limit of the abundance values to remove isotopes
		//#define CHECKINTERM   // Uncomment to also check the intermediate abundances values
	#endif
#include "numbers.h"

#else
#define NNUCREACMAX 100	// 100 nuclear reactions
#define NNUCMAX 26         // 26 elements

#endif

#define NNUCREAC NNUCREACMAX     // Number of reactions to be considered in the calculation
#define NNUC NNUCMAX             // Number of elements


#ifdef CHECKLOW
	int checklow[NNUC+1];
#endif

/*--------------------------------------------------------------------*/

#define NTABMAX 1000

typedef struct relicparam
/* structure containing the cosmological model parameters */
{
    int entropy_model,energy_model;
    double dd0,ndd,Tdend,Tddeq; // dark density
    double sd0,nsd,Tsend; // dark entropy
    double Sigmad0,nSigmad,TSigmadend; // dark entropy injection
    double Sigmarad0,nSigmarad,TSigmaradend; // standard entropy injection
    double nt0,nnt,Tnend; // non-thermal production of relics
    int coupd; // dark fluid coupling to plasma

    double quintn2,quintn3,quintn4,quintT12,quintT23,quintT34; // effective quintessence model

    int phi_model; // decaying scalar field model switch
    double eta_phi,Gamma_phi,rhot_phi_Tmax,n_phi; // eta_phi = b / m_phi
    double rhot_phi0,Tphi0;
    double T_RH;
    double Sigmatildestar;
    double Sigmatildestar_max;
    double Tstdstar_max;

    double mgravitino; // gravitino mass

    double relicmass;
    int scalar;

    int solver; // switch for linear or logarithmic differential equation solver
	int beta_samples;

    double Tfo,Tmax; // Freeze out and maximal temperature

    int full_comput; // Switch to deactivate the fast freeze out temperature determination

    double table_eff[276][3];   // Reads values from the SgStar files

    int use_table_rhoPD;
    double table_rhoPD[2][NTABMAX];
    int size_table_rhoPD;

		// scalar field additions
		int use_table_Ffunc;
		double table_Ffunc[2][NTABMAX];
		int size_table_Ffunc;

		double mass, mu, vval, phi_init; // symmetron parameters fed in from GAMBIT


    /*---------------------*/
    /* AlterBBN parameters */
    /*---------------------*/

    int err;
    int failsafe;				// Switch for the integration method
    double eta0;                // Initial Baryon to photon ratio
    double Nnu;                 // Number of Neutrinos (e+- included)
    double dNnu;                // Number of extra neutrinos (delta N_nu)
    double life_neutron,life_neutron_error;		// neutron lifetime
    double xinu1,xinu2,xinu3;	// [e-,neutrino], [muon,neutrino], [tau,neutrino] respectively (degeneracy parameters)
    double m_chi;               // Mass of WIMP
    double g_chi;				// dof of WIMP
    double Tinit;				// Initial temperature
    double Tnudec;				// Neutrino decoupling temperature
    int wimp;                   // Switch to enable (1) / disable (0) wimps
    int SMC_wimp;               // wimp coupling to SM particles. 1 for EM, 2 for neutrino, 3 for neutrino and equivalent neutrino
    int selfConjugate;          // 1/0 for self-conjugate/non-self-conjugate WIMP
    int fermion;
    int EM_coupled, neut_coupled, neuteq_coupled;
	double fierz;				// Fierz interference term from LQ sector
	double B_chi;				// branching ratio of WIMP DM of mass m_p < m_chi < m_n to explain tau_n anomaly
	double rhob0;				// current baryon density
	double b_cdm_ratio;			// current ratio of baryon density to cold dark matter density
	int constraints;			// 1=Yp, 2=+H2/H, 3=+Li7/H, 4=+He3/H
}
relicparam;

/*--------------------------------------------------------------------*/

typedef struct errorparam
/* structure containing the cosmological model parameters */
{
    int errnumber;				// process number for error calculation
    double random[NNUCREAC+2];  // random numbers for Monte Carlo
	double life_neutron;
}
errorparam;

/*--------------------------------------------------------------------*/
/* Prototypes */

/* general.c */
double max(double x, double y);
double min(double x, double y);
double Ei1(double x);
double Ei2(double x);
double Ei3(double x);
double Ei(double x);
double complex polylog(int n, int m, double x);
double complex cd(double x, double y);
double complex hpl_base1(int i, double complex x);
double complex hpl_base2(int i1, int i2, double complex x);
double complex hpl_base3(int i1, int i2, int i3, double complex x);
double complex hpl_base4(int i1, int i2, int i3, int i4, double complex x);
double complex hpl1(int i, double complex x);
double complex hpl2(int i1, int i2, double complex x);
double complex hpl3(int i1, int i2, int i3, double complex x);
double complex hpl4(int i1, int i2, int i3, int i4, double complex x);
double Li2(double x);
double Li3(double x);
double Li4(double x);
double complex CLi2(double complex x);
double complex CLi3(double complex x);
double complex CLi4(double complex x);
double Cl2(double x);
double Cl3(double x);
double I0(double x);
double I1(double x);
double K0(double x);
double K1(double x);
double K2(double x);
double K3(double x);
double K4(double x);
double Lbessel(double x);
double Mbessel(double x);
double Nbessel(double x);
double expcor(double x);
double K0exp(double x,double z);
double K1exp(double x,double z);
double K2exp(double x,double z);
double kron(int x, int y);
double rand_gauss(void);
int test_integer(char name[]);
int test_file(char *name);
int invert_matrix(int n, double** in, double** out);
double rand_gauss();
double myrand(int type, int on);
int cholesky(int n, double** in, double** out);
double interpol_fromtable(double val, double table[], int dim, int order);
double simpson_noerr(double* f, double*x, int n1, int n2);
void simpson_rec(double (*func)(double), double* f, double *x, int* n, int n1, int n2, double* restot, double err);
double simpson(double (*func)(double), double a, double b, double err);
void braket(int n,double (*func)(double[]), double* a0, double*x0, double*b0, double xinit[], double xi[], double xlimmin[], double xlimmax[], double factor);
int brentmethod(int n, double (*func)(double[]),double xmin[],double xi[], double xlimmin[], double xlimmax[], double *fmin, double factor);
double brentmethod1Dfunc(double (*func)(double[]), double x, double xmini[], double xi[], int n);
int brentmethod1D(double (*func)(double[]), double a0, double x0,double b0, double *fmin, double *xmin, double factor, double xmini[], double xi[], int n);
void brentzero(double (*func)(double), double a, double b, double *fmin, double *xmin, double eps);
int powellaux(int n, double (*func)(double[]),double x0[], double xlimmin[], double xlimmax[],  double* fmin,  double xmin[], double ftol, double factor);
int powell(int n, double (*func)(double[]), double xlimmin[], double xlimmax[],  double* fmin,  double xmin[], double ftol, char* option);
double factorial(int n);

/* cosmodel.c */
double heff(double Temp, struct relicparam* paramrelic);
double sgStar(double Temp, struct relicparam* paramrelic);
double geff(double Temp, struct relicparam* paramrelic);
void Init_cosmomodel(struct relicparam* paramrelic);
void Init_cosmomodel_param(double eta, double Nnu, double dNnu, double life_neutron, double life_neutron_error, double xinu1, double xinu2, double xinu3, struct relicparam* paramrelic);
void Init_modeleff(int model_eff, struct relicparam* paramrelic);
void Init_wimp(double mass_wimp, int EM_coupled, int neut_coupled, int neuteq_coupled, int fermion, int selfConjugate, double g_chi, struct relicparam* paramrelic);
void Init_dark_density(double dd0, double ndd, double T_end, struct relicparam* paramrelic);
void Init_dark_density2(double ndd, double Tddeq, double T_end, struct relicparam* paramrelic);
void Init_dark_coupling(int coupD, struct relicparam* paramrelic);
void Init_quintessence(double T12, double n2, double T23, double n3, double T34, double n4, struct relicparam* paramrelic);
void Init_dark_entropy(double sd0, double nsd, double T_end, struct relicparam* paramrelic);
void Init_dark_entropySigmaD(double Sigmad0, double nSigmad, double T_end, struct relicparam* paramrelic);
void Init_entropySigmarad(double Sigmarad0, double nSigmarad, double T_end, struct relicparam* paramrelic);
void Init_nonthermal(double nt0, double nnt, double T_end, struct relicparam* paramrelic);
void Init_gravitino(double mgravitino, struct relicparam* paramrelic);
void Init_scalarfield(double rhotilde_phi_Tmax, double Tmax, double T_RH, double eta_phi, double n_phi,struct relicparam* paramrelic);
void Init_dark_density_table(double table[2][NTABMAX], int nlines, relicparam* paramrelic);
void Init_neutron_decay(double tau_n, double tau_n_error, double fierz, double m_chi, double B_chi, relicparam* paramrelic);
double dark_density(double T, struct relicparam* paramrelic);
double dark_density_pressure(double T, struct relicparam* paramrelic);
double sigma_entropy(double T, struct relicparam* paramrelic);
double dark_entropy(double T, struct relicparam* paramrelic);
double dark_entropy_derivative(double T, struct relicparam* paramrelic);
double dark_entropy_Sigmad(double T, struct relicparam* relicparam);
double entropy_Sigmarad(double T, struct relicparam* paramrelic);
double nonthermal(double T, struct relicparam* paramrelic);
double neutdens(double Tnu, struct relicparam* paramrelic);
double neutdens_deriv(double Tnu, struct relicparam* paramrelic);
double neutN(double T);
// symmetron functions to find the field
double Afunc(double phi, double mass, double vparam);
double Vfunc(double phi, double mu, double vparam);
double Vderivfunc( double phi,double mu, double v);
double alphafunc(double phi, double mass, double vparam);
struct odeparameters;
int func (double T, const double y[], double f[], void *params);
int jac();
void Init_vecs(struct relicparam* paramrelic);

// scalar field functions for alterbbn
double Ffunc_Hscaling(double T, struct relicparam* paramrelic);

/* bbnrate.c */
double rate_pn_enu(int type, double T9, double Tnu, relicparam* paramrelic, errorparam* paramerror);
void rate_weak(double f[], struct relicparam* paramrelic, struct errorparam* paramerror);
void rate_pn_noerr(double f[], double r[], double T9, double Tnu, relicparam* paramrelic, errorparam* paramerror);
void rate_pn(double f[], double r[], double T9, double Tnu, struct relicparam* paramrelic, struct errorparam* paramerror);
void rate_all(double f[], double T9, struct relicparam* paramrelic, struct errorparam* paramerror);

/* bbn.c */
int linearize(double T, const double reacparam[NNUCREACMAX+1][10], double f[NNUCREACMAX+1], double r[NNUCREACMAX+1], int loop, int inc, int ip, double dt, double Y0[NNUC+1], double Y[NNUC+1], double dY_dt[NNUC+1], double rhob);
int fill_params(double T, double Tnu, double phie, double h_eta, double a, double rho_phi, double dt0, double* dT, double* dTnu, double* dphie, double* dh_eta, double* da, double* drhophi, double dY_dt[NNUC+1], double Y0[NNUC+1], double Y[NNUC+1], const double Am[NNUC+1], const double Zm[NNUC+1], const double Dm[NNUC+1], const double reacparam[NNUCREAC+1][10], double norm, int loop, int inc, int ip, struct relicparam* paramrelic, struct errorparam* paramerror);
int nucl_single(struct relicparam* paramrelic, double ratioH[NNUC+1], struct errorparam* paramerror);
int nucl_err(struct relicparam* paramrelic, double ratioH[NNUC+1], double cov_ratioH[NNUC+1][NNUC+1]);
int nucl(struct relicparam* paramrelic, double ratioH[NNUC+1]);

/* bbn_constraints.c */
int bbn_excluded(struct relicparam* paramrelic);
