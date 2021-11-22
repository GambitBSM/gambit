/* a script where i will test different convergence loops
http://web.mit.edu/hyperbook/Patrikalakis-Maekawa-Cho/node200.html
http://web.iitd.ac.in/~hegde/acm/lecture/L11_system_of_eqns_iterative_methods.pdf
https://my.mech.utah.edu/~pardyjak/me2040/Lect10_IterativeSolvers.pdf */

#include <cmath>
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <numeric>
#include <math.h>
using namespace std;

// define constants
#define M_pl 2.435363098e18 // [Gev/c^2] reduced planck mass
#define hbar 6.2131e-47 // [kpc^2 Gev/c^2 s^-1]
#define cconst 9.715e-12 // [kpc/s] speed of light
#define Gconst 3.866e-63 // [kpc (Gev/c^2)^-1 (km/s)^2] gravitational const
#define kb 1500.0 // [(km/s)^2 kpc^-1] sets mass of disk
#define db 0.18 // [kpc] disk scale height

// function to return the value of f^j(xvec)
double func(int j, vector <double> phivec, vector <double> rhovec, int npoints,
            double hstep, double mass, double mu)
{
  double funcval = 0.0;
  // manually do the boundary value cases
  if (j == 0) { // for f^0(xvec)
    funcval = 2.0/(hstep*hstep)*phivec.at(j+1)
              +(-2.0/(hstep*hstep) - rhovec.at(j)/(mass*mass)*hbar/cconst + pow(mu*cconst/hbar,2.0))*phivec.at(j)
              - pow(mu*cconst/hbar,2.0)*pow(phivec.at(j),3.0);
  } else if (j == 1) { // for f^1(xvec)
    funcval = -1.0/(12.0*hstep*hstep)*phivec.at(j+2) + 4.0/(3.0*hstep*hstep)*phivec.at(j+1)
              + (-31.0/(12.0*hstep*hstep) - rhovec.at(j)/(mass*mass)*hbar/cconst + pow(mu*cconst/hbar,2.0))*phivec.at(j)
              - pow(mu*cconst/hbar,2.0)*pow(phivec.at(j),3.0) + 4.0/(3.0*hstep*hstep)*phivec.at(j-1);

  } else if (j == npoints-2) { // for f^{n-2}(xvec)
    funcval = -1.0/(12.0*hstep*hstep) + 4.0/(3.0*hstep*hstep)*phivec.at(j+1)
              + (-5.0/(2.0*hstep*hstep) - rhovec.at(j)/(mass*mass)*hbar/cconst +pow(mu*cconst/hbar,2.0))*phivec.at(j)
              - pow(mu*cconst/hbar,2.0)*pow(phivec.at(j),3.0)
              + 4.0/(3.0*hstep*hstep)*phivec.at(j-1) - 1.0/(12.0*hstep*hstep)*phivec.at(j-2);
  } else if (j == npoints-1) { // for f^{n-1}(xvec)
    funcval = 1.0/(hstep*hstep)
              + (-2.0/(hstep*hstep) - rhovec.at(j)/(mass*mass)*hbar/cconst +pow(mu*cconst/hbar,2.0))*phivec.at(j)
              - pow(mu*cconst/hbar,2.0)*pow(phivec.at(j),3.0) + 1.0/(hstep*hstep)*phivec.at(j-1);
  } else {
    funcval = -1.0/(12.0*hstep*hstep)*phivec.at(j+2) + 4.0/(3.0*hstep*hstep)*phivec.at(j+1)
              + (-5.0/(2.0*hstep*hstep) - rhovec.at(j)/(mass*mass)*hbar/cconst +pow(mu*cconst/hbar,2.0))*phivec.at(j)
              - pow(mu*cconst/hbar,2.0)*pow(phivec.at(j),3.0)
              + 4.0/(3.0*hstep*hstep)*phivec.at(j-1) - 1.0/(12.0*hstep*hstep)*phivec.at(j-2);
  }
  return funcval;
}

// function to return the value of the derivative of f^j(xvec)
double derivfunc(int j, vector <double> phivec, vector <double> rhovec, int npoints,
            double hstep, double mass, double mu)
{
  long double derivfuncval = 0.0;

  if (j == 0){
    derivfuncval = (-2.0/(hstep*hstep) - rhovec.at(j)/(mass*mass)*hbar/cconst + pow(mu*cconst/hbar,2.0))
                    - 3.0*pow(mu*cconst/hbar,2.0)*pow(phivec.at(j),2.0);
  } else if (j == npoints-1) {
    derivfuncval = (-2.0/(hstep*hstep) - rhovec.at(j)/(mass*mass)*hbar/cconst +pow(mu*cconst/hbar,2.0))
                    - 3.0*pow(mu*cconst/hbar,2.0)*pow(phivec.at(j),2.0);
  } else {
    derivfuncval = (-5.0/(2.0*hstep*hstep) - rhovec.at(j)/(mass*mass)*hbar/cconst +pow(mu*cconst/hbar,2.0))
                    - 3.0*pow(mu*cconst/hbar,2.0)*pow(phivec.at(j),2.0);
  }
  return (double) derivfuncval;
}

// a function to return a new value of xmax to test given the previous failed one
double newxmax(double oldxmax)
{
  if (oldxmax<2) {
    return oldxmax+0.1;
  } else if (oldxmax<20){
    return oldxmax+1;
  } else if (oldxmax<100){
    return oldxmax+5;
  } else if (oldxmax<500) {
    return oldxmax+10;
  } else if (oldxmax<1e3) {
    return oldxmax+50;
  } else {
    return oldxmax+100;
  }
}


// a function to set up x and rho vecs for new npoints
void setupxrhovec(int npoints, double x_max, vector<double> &xvec, vector<double> &rhovec)
{
  xvec.resize(npoints, 0.0e0);
  rhovec.resize(npoints, 0.0e0);

  double hstep = x_max/npoints;

  // constant DM density https://arxiv.org/pdf/1906.06133.pdf
  const double Mpc_SI = 969394202136*pow(10,11)/M_PI; // Mpc in m, from gambit constants
  double rho_DMinMW = 0.36/(pow(1/100,-3)*pow(1/Mpc_SI, -3)*pow(1e3,-3)); // in GeV/kpc^3

  for (int i=0; i<npoints; i++){
    xvec.at(i) = i*hstep;
    rhovec.at(i) = rho_DMinMW + 1.0/(4*M_PI*Gconst)*fabs(kb*db*db/pow(db*db + pow(xvec.at(i),2.0),1.5));

  }
}

// a function to interpolate for phivec for new npoints
void phivecinterp(int npoints, vector<double> &phivec)
{
  // keep old phivec for interpolation before resetting it
  vector<double> phivecold = phivec;
  phivec.resize(npoints, 0.0e0);

  // fill in existing points
  for (int i=0; i<(int)npoints/2; i++){
    phivec.at(i*2) = phivecold.at(i);
  }

  // then add in the other points
  for (int i=0; i<((int)npoints/2-1); i++){
    int index = i*2+1;
      phivec.at(index) = (phivecold.at(i+1)+phivecold.at(i))/2.0;
  }

  phivec.back() = (1+phivecold.back())/2.0;
}

// function to return the value of the field at a given distance
int solvephi(double mass, double mu, double &x_max, double &hstep, int &npoints,
  double min_gammatol, vector<double> &phivec, vector<double> &xvec, vector<double> &rhovec)
{
  // set up ODE solving parameters and vectors
  /* first we want to use a loop to find the value of xmax where the solution converges
    to 1 at the upper boundary without most values being ~1 */
  int n_iterations = 100; // starting number of GS iterations to do
  bool gridresok = false; // to pass first check or not
  bool xmaxfound = false; // to check if the right xmax has been found
  int oldnpoints = npoints; // to check whether npoints was updated or not, hence soln converged
  int counter = 0; // to check not solving forever

  // SOLVING LOOP WITH CHECKS
  while (xmaxfound == false) {
    npoints = 200;
    oldnpoints = npoints;
    while (gridresok == false) {
      // SET UP THE VECTORS FOR SOLVING
      hstep = (x_max) / npoints;
      setupxrhovec(npoints, x_max, xvec, rhovec);

      // redefine input phi vector to store the solution phi and initialise with an initial test solution
      phivec.resize(npoints, 0.0e0);
      for (int i=0; i<npoints; i++){
        phivec.at(i) = 1.0-(1.0-1.0e-7)*pow(1.0/cosh(xvec.at(i)/(x_max/5.0)),2.0);
      }

      // FIRST CHECK: is grid resolution enough for a reasonable solution
      // outer loop to perform gauss-seidel iterations
      for (int i=0; i<n_iterations; i++){
        // inner loop to iterate over each point in the grid
        for (int j=0; j<npoints; j++){
          phivec.at(j) = phivec.at(j) - func(j, phivec, rhovec, npoints, hstep, mass, mu)
                                      /derivfunc(j, phivec, rhovec, npoints, hstep, mass, mu);
        }
      }
      // then check the gradients to make sure all position
      for (int i=0; i<npoints-1; i++){
        double gradient = (phivec.at(i+1)-phivec.at(i));
        if (gradient < 0 && fabs(gradient) > 0.1){
          npoints *= 2;
          break;
        }
      }
      if (npoints == oldnpoints){
        gridresok = true;
      } else {
        oldnpoints = npoints;
      }
    } // end of inner while loop
    // SECOND CHECK: make sure xmax is big enough
    // check if solution at upper bound is ~1 and gradient is ~0
    gridresok = false;
    double gradient = (phivec.at(npoints-1) - phivec.at(npoints-11));
    if (gradient < 1e-4 && (1.0-phivec.at(npoints-11))<1e-3) {
      cout << "converges with npoints = " << npoints << endl;
      cout << "xmax found = "<< x_max << endl;
      xmaxfound = true;
    } else {
      x_max = newxmax(x_max);
    }
    counter ++;

    if (counter >200 ){
      cout << "not converging - too many iterations needed" << endl;
      xmaxfound = true;
      return 1;
    }
  } // end of second while loop

  // params for third check
  bool phi0converged = false;
  n_iterations = 200;
  counter = 0;

  bool keepiterating = true;

  // THIRD CHECK: is resolution fine enough so that phi0 has converged and is positive?
  // a do-while statement to iterate until solution has converged for fix no of gs iterations
  while (phi0converged == (false)) {
    double phi0old = phivec.at(0);


    for (int i=0; i<n_iterations; i++){
      // inner loop to iterate over each point in the grid
      for (int j=0; j< (int) npoints; j++){
        // cout << func(j, phivec, rhovec, npoints, hstep, mass, mu) << endl;
        phivec.at(j) = phivec.at(j) - func(j, phivec, rhovec, npoints, hstep, mass, mu)
                                    /derivfunc(j, phivec, rhovec, npoints, hstep, mass, mu);
      }
    }

    // check if |phi(0)| is less than 1e-30 and if so, set to 0
    double phi0condition = sqrt(min_gammatol)/2.0*pow(mass/M_pl,2.0);

    if (fabs(phivec.at(0)) < phi0condition){
      phivec.at(0) = phi0condition;
      cout << "phi(0) = " << phivec.at(0) << endl;
      phi0converged = true;
      keepiterating = false;
      break;
    }


    // check whether the grid size was ok
    counter ++;
    double phi0error = fabs((phi0old-phivec.at(0))/phi0old); // relative error
    if (phi0error < 1e-1 && phivec.at(0) > 0){
      cout << "phi(0) converges with npoints = " << npoints << endl;
      phi0converged = true;
    } else { // if hasn't converged double grid resolution
      // set up next test solution by interpolating the current one
      // first increase grid resolution
      cout << npoints << setw(15) << phivec.at(0) << setw(15) << phi0error << endl;
      if (counter > 4){
        cout << "at grid res limit " << endl;
        break;
      }

      // redefine xvec, rhovec and phivec
      npoints *= 2;
      hstep = (x_max) / npoints;
      setupxrhovec(npoints, x_max, xvec, rhovec);
      phivecinterp(npoints, phivec);
    }
  }

  // vector to store phivec to check against for convergence - initialise with current soln
  vector <double> checkphivec = phivec;
  vector <double> phiratios; // store the ratios for checking a selection of points
  int ncheck = 10;
  phiratios.resize(ncheck, 0.0e0); // check every fifth point
  counter = 0;
  int totaliterations=n_iterations; // a total count of GS iterations taken

  // FOURTH CHECK: finally solve for as many GS steps needed until soln converges
  while (keepiterating == (true)) {
      // outer loop to perform gauss-seidel iterations
    for (int i=0; i<n_iterations; i++){
      // inner loop to iterate over each point in the grid
      for (int j=0; j< (int) npoints; j++){
        // cout << func(j, phivec, rhovec, npoints, hstep, mass, mu) << endl;
        phivec.at(j) = phivec.at(j) - func(j, phivec, rhovec, npoints, hstep, mass, mu)
                                    /derivfunc(j, phivec, rhovec, npoints, hstep, mass, mu);
      }
    }

    // update the total GS iterations done
    totaliterations += n_iterations;

    // check a selection of the new solution against the one at the last checkpoint
    // use a relative error
    int checkstep = floor(npoints/ncheck);
    for (int i=0; i<ncheck; i++) {
      phiratios.at(i) = (phivec.at(i*(checkstep-1))-checkphivec.at(i*(checkstep-1)))
                          /checkphivec.at(i*(checkstep-1));
    }

    // use the average difference to check convergence against
    double sum = accumulate(phiratios.begin(), phiratios.end(), 0.0)/ (double) ncheck;

    if (fabs(sum) < 1e-3) { // if convergence has been reached flag to stop
      keepiterating = false;
      cout << "phi(0) = " << phivec.at(0) << endl;
      cout << "Iterations for convergence: " << totaliterations << endl;
    } else { // if not yet converged
      checkphivec = phivec; // copy phi vector to be the new checkpoint
      n_iterations = totaliterations/5; // increase the number of iterations
    }
    if (totaliterations > 2e3){
      cout << "Iteration limit reached: " << totaliterations << endl;
      break;
    }
  }

  return 0;
}


int main(){
  // we want to calculate the likelihood for a range of masses
  int nmasses = 17;
  double logmassmin = -7, logmassmax = -3;
  double steplogmass = (logmassmax-logmassmin)/(nmasses-1);
  vector <double> massvec (nmasses, 0.0e0);
  for (int i=0; i<nmasses; i++){
    massvec.at(i) = pow(10, logmassmax-i*steplogmass)*M_pl;
  }

  // also store a vector of mu values
  int nmu = 21;
  double logmumin = -37, logmumax = -32;
  double steplogmu = (logmumax-logmumin)/(nmu-1);
  vector <double> muvec (nmu, 0.0e0);
  for (int i=0; i<nmu; i++){
    muvec.at(i) = pow(10, logmumax-i*steplogmu);
  }

  cout.precision(6);
  cout.setf(ios::scientific);

  double v = 1.0; // symmetron parameter v
  vector <double> phi0vec (nmu*nmasses, 0.0e0); // a vector to store the phi0 values

  // inputs for the function that solves the ode
  vector<double> xvec;
  vector<double> phivec;
  vector<double> rhovec;
  double x_max;

  int npoints = 200;
  double hstep;
  double min_gammatol = 1e-9;

  // SOLVING FOR PHI(0)
  // calculate the phi0 and likelihood value for each mass and print to a file
  for (int j=0; j<nmu; j++){
    // set a starting x_max and then each mass calculation takes the previous x_max
    x_max = 0.5;

    for (int i=0; i<nmasses; i++){
      cout << endl << "Solving {M*M_pl, mu, v} = {" << setw(5) << massvec.at(i)/M_pl << ", ";
      cout << setw(5) << muvec.at(j) << ", " << setw(5) << v << "}" << endl;
        double phi0condition = sqrt(min_gammatol)/2.0*pow(massvec.at(i)/M_pl,2.0);
      solvephi(massvec.at(i), muvec.at(j), x_max, hstep, npoints, min_gammatol, phivec, xvec, rhovec);
      if (phivec.at(0) < phi0condition){
        phi0vec.at(i*nmu+j) = phi0condition;
      } else {
        phi0vec.at(i*nmu+j) = phivec.at(0);
      }

    }
  }


  // OUTPUTTING RESULTS
  // datafile to print phi(0) values to
  // set up file to output final solutions to
  ofstream datafile;
  datafile.open("phi0vals.dat");
  datafile.setf(ios::scientific,ios::floatfield);
  datafile.precision(6);

  // first line is min(mass), max(mass), nmasses, min(mu), max(mu), nmu, min_gammatol
  datafile << setw(15) << pow(10, logmassmin)*M_pl << setw(15) << pow(10, logmassmax)*M_pl;
  datafile << setw(15) << nmasses << setw(15) << pow(10, logmumin) << setw(15) << pow(10, logmumax);
  datafile  << setw(15) << nmu << setw(15) << min_gammatol << endl;

  // output phi(0) to the file
  for (int i=0; i<nmasses; i++){
    for (int j=0; j<nmu; j++){
      datafile << setw(15) << phi0vec.at(i*nmu+j);
    }
    datafile << endl;
  }
  datafile << endl;

  datafile.close();

  return 0;
}
