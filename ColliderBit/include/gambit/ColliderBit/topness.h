#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>

#include "gambit/Utils/threadsafe_rng.hpp"

// ****** Copy from https://github.com/michaelgraesser/topness *****
// ****** arXiv:1212.4495 ******************************************
// Modified according to https://arxiv.org/pdf/1612.03877.pdf
/* "The definition of topness used in this analysis is modified from
    the one originally proposed in [arXiv:1212.4495]: namely, the terms
    corresponding to the detected leptonic top quark decay and the
    centre-of-mass energy are dropped since in events with low jet
    multiplicity the second b jet is often not identified.
    In these cases, the discriminating power of the topness variable
    is reduced when a light-flavour jet is used instead in the calculation.

    Modified further by Pat Scott, Feb 9 2019, to use GAMBIT random
    number generator.

    This is a BSD License. Code written by Michael L. Graesser.

    Copyright (c) 2016, Los Alamos National Security, LLC
    All rights reserved.
    Copyright 2016. Los Alamos National Security, LLC. This software was produced under U.S. Government contract DE-AC52-06NA25396 for Los Alamos National Laboratory (LANL), which is operated by Los Alamos National Security, LLC for the U.S. Department of Energy. The U.S. Government has rights to use, reproduce, and distribute this software.  NEITHER THE GOVERNMENT NOR LOS ALAMOS NATIONAL SECURITY, LLC MAKES ANY WARRANTY, EXPRESS OR IMPLIED, OR ASSUMES ANY LIABILITY FOR THE USE OF THIS SOFTWARE.  If software is modified to produce derivative works, such modified software should be clearly marked, so as not to confuse it with the version available from LANL.

    Additionally, redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
    1.       Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
    2.      Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
    3.      Neither the name of Los Alamos National Security, LLC, Los Alamos National Laboratory, LANL, the U.S. Government, nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY LOS ALAMOS NATIONAL SECURITY, LLC AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL LOS ALAMOS NATIONAL SECURITY, LLC OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  */

// using namespace std;
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// >>>>>> topness_struct.cpp & topness_struct.h in "topness" <<<<<<<
const double mt=172.;  // top quark mass
const double mW=80.4;  // W mass
double my_lp(double u[4], double v[4])
{    // Lorentz product . assume x, y Lorentz vectors ordered as (px,py,pz,E) etc. Initialize with
  // metric g==(-1,-1,-1,1)

  double g[]={-1.,-1.,-1.,1.};
  double s=0;
  for (int j=0;j<4;j++)
    {s+= u[j]*g[j]*v[j]; }
  return s;
}
void my_add(double a[4], double b[4], double c[4])
{
  for (int i=0; i<4; i++)
    {
      c[i]=a[i]+b[i];
    }
}
struct my_func
{
  double pb1[4];
//  double pb2[4];
  double pl[4];
  double pMET[4];
  double sigmat, sigmaW, sign;
  // ***Modified by Yang Zhang 23.1.2018
  my_func(double ppb1[4], double ppl[4], double ppMET[4], double sigmatt, double sigmaWW, double ssign) :
  sigmat (sigmatt), sigmaW(sigmaWW), sign(ssign) {
    pb1[0]=ppb1[0];
    pb1[1]=ppb1[1];
    pb1[2]=ppb1[2];
    pb1[3]=ppb1[3];
//    pb2[0]=ppb2[0];
//    pb2[1]=ppb2[1];
//    pb2[2]=ppb2[2];
//    pb2[3]=ppb2[3];
    pl[0]=ppl[0];
    pl[1]=ppl[1];
    pl[2]=ppl[2];
    pl[3]=ppl[3];
    pMET[0]=ppMET[0];
    pMET[1]=ppMET[1];
    pMET[2]=ppMET[2];
    pMET[3]=ppMET[3];
  }
  double operator()(double points[],int /*d*/) {  // points[0]=pv_x, points[1]=pv_y, points[2]=pv_z, points[3]=pW_z
    // d is size of points = 4
    // pv_x, pv_y, pv_z
    double pvx=points[0];
    double pvy=points[1];
    double pvz=points[2];
    // neutrino energy assuming mass-shell condition
    double Ev=sqrt(pow(pvx,2)+pow(pvy,2)+pow(pvz,2));

    double pv[]={pvx,pvy,pvz,Ev};

    // pW_z
    double pWz=points[3];
    // std::cout << "points=" << pvx << ", " << pvy << ", " << pvz << ", " << pWz << std::endl;
    // W momenta from neutrino and MET
    double pW[]={-pvx+pMET[0],-pvy+pMET[1],pWz,sqrt(pow(-pvx+pMET[0],2)+pow(-pvy+pMET[1],2)+pow(pWz,2) + pow(mW,2))};

    double pb1W[4];
    my_add(pb1,pW,pb1W);
    double plv[4];
    my_add(pl,pv,plv);
//    double pb2lv[4];
//    my_add(pb2,plv,pb2lv);
    // function to minimize
    double fsum=0.;
    // ***Modified by Yang Zhang 23.1.2018
    fsum= pow(my_lp(pb1W,pb1W)-pow(mt,2),2)/pow(sigmat,4)+pow(my_lp(plv,plv)-pow(mW,2),2)/pow(sigmaW,4);
    //+pow(my_lp(pb2lv,pb2lv)-pow(mt,2),2)/pow(sigmat,4)+pow(my_lp(plv,plv)-pow(mW,2),2)/pow(sigmaW,4);
    //std::cout << "fsum = " << fsum << std::endl;
    return sign*fsum;
  }
};

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// >>>>>> simplex.cpp & simplex.h in "my_Nelder_Mead" <<<<<<<<<<<<<<
const int DMAX=4; // # parameters to scan over, not the space-time dimension! Number of points in the simplex is DMAX+1.
double my_dot(double p1[], double p2[], int d)   // d is size of arrays
{
// compute euclidean dot product between p1 and p2
  double value=0.;
  for (int i=0; i<d; i++)
    {
      //      std::cout << "p1: " << p1[i] <<", p2:" << p2[i] << std::endl;
      value+=p1[i]*p2[i];
    }
  //std::cout << "dp value is " << value << std::endl;
  return value;
}
double my_dot(double p1[], double p2[], double a[], int d)   // d is size of arrays
{
  // compute euclidean dot product between p1 and p2 with weights a

  double value=0.;
  for (int i=0; i<d; i++)
    {
      value+=a[i]*p1[i]*p2[i];
    }
  return value;
}
double my_enorm(double p[], int d)
{
  // compute euclidean norm of p
  double value=0.;
  double norm=0.;
  for (int i=0; i<d; i++)
    {
      value+=p[i]*p[i];
    }
  if (value>0.)
    {
      norm=sqrt(value);
    }
  else
    {
      norm=0.;
    }
  return norm;
}
class my_simplex{
// co-ordinate space is d dimensional. analysis uses N=d+1 points
 private:
  int d;
  double alpha, beta, gamma;

 public:
  my_func *f;
  my_simplex(int, double, double, double, my_func *);
  double xstart[DMAX*(DMAX+1)]; // length (d+1)*d. d elements are coordinates
  double x[DMAX*(DMAX+1)]; //    current polygon instance containing d+1 points of d dimension each, so size is d(d+1)
  double xh[DMAX]; // coordinates of point with highest value
  double xl[DMAX]; // coordinates of point with lowest value
  double y[DMAX+1]; // function values at x
  double yl, ynh, yh; // lowest, next highest, and highest function values
  double xCentroid[DMAX]; // current centroid;
  double yReflect, yExpand, yContract; // function values at these points
  double xReflect[DMAX]; // P* reflection
  double xExpand[DMAX]; // P** expansion
  double xContract[DMAX]; // P*** contraction
  void find_min();
  void find_max();
  int imin,imax, inmax;
  void my_SetUp(double xin[]);
  void set_y();
  void my_Centroid(int);
  void my_Reflection();
  void my_Expansion();
  void my_Contraction();
  void replace_all();
  double get_yavg();
  double get_sigma();
  void print_Centroid();
  void print_Reflect();
  void print_Expand();
  void print_Contract();
  void print_max();
  void print_min();
  void print_all();
  void print_xy();
  void print_xyl();
  void print_xyh();
};

class my_Nelder_Mead {
 private:
  int d;
  int Ntry;      // N cycles of Nelder-Mead algorithm
  double eps;

 public:
  my_func *f;
  my_simplex simplex;
  bool convergeYes; // set to True when algorithm has converged
  my_Nelder_Mead(int, double, double, double, int, double, my_func *);
  bool one_cycle(my_simplex *);
  bool find_global_min(double xin[DMAX*(DMAX+1)]);
  double yfinal;
  double xfinal[DMAX*(DMAX+1)];
};


my_simplex::my_simplex(int dd, double aalpha, double bbeta, double ggamma,  my_func (*ff)) : d(dd), alpha(aalpha), beta(bbeta), gamma(ggamma), f(ff){}
// check d and size of xin agree

void my_simplex::my_SetUp(double xin[DMAX*(DMAX+1)])
{
  int D=d*(d+1);
  std::copy(xin,xin+D,xstart);
  for (int i=0; i<D; i++)
    {
      x[i]=xstart[i];
    }

  for (int i=0; i<d+1; i++)
    {
      double xi[d];
      std::copy(x+d*i,x+d*i+d,xi);  // get coordinates of i'th point and copy into xi
           y[i]=(*f)(xi,d);
    }
}

void my_simplex::set_y()
{
  for (int i=0; i<d+1; i++)
    {
      double xi[d];
      std::copy(x+d*i,x+d*i+d,xi);  // get coordinates of i'th point and copy into xi
      y[i]=(*f)(xi,d);
    }
}

void my_simplex::find_max()
{
  for (int i=0; i<d+1; i++)
    {
      if (y[i]> y[imax])
	imax=i;
    }
  // now find second highest
  if (imax==1)
    inmax=0;

  for (int i=0; i<d+1; i++)
    {
      if (i==imax) continue;
      if (y[i] > y[inmax])
	{
	  inmax=i;
	}
    }

  yh=y[imax];
  ynh=y[inmax];
  // find coordinates with maximum value
  for (int j=0; j<d; j++)
    {
      xh[j]=x[d*imax+j];
    }
}

void my_simplex::find_min()
{
  imin=0;   // first function value f(x_1)
  for (int i=0; i<d+1; i++)
    {
       if (y[i]< y[imin])
       {
        imin=i;
       }
    }

  yl=y[imin];

  // find coordinates with minimum value
  for (int j=0; j<d; j++)
    {
      xl[j]=x[d*imin+j];
    }

}

void my_simplex::my_Centroid(int h)
/* return P_bar */
{
  // compute centroid
  for (int j=0; j<d; j++)
    {
      xCentroid[j]=0;
      for (int i=0; i< d+1; i++)
	{
	  if (i==h) continue;
	  xCentroid[j]+=x[d*i+j];
	}
    }
}

void my_simplex::my_Reflection() // h is highest point
/* return P*
   REFLECTION  P*=(1+alpha)P_bar - alpha*P_h   */
{
  for (int i=0; i<d;i++)
  {
    xReflect[i] = xCentroid[i]*(1+alpha)/d- alpha*xh[i];
  }
  yReflect=(*f)(xReflect,d);
}

void my_simplex:: my_Expansion()
/* return EXPANSION P** =(1+gamma)*P* -gamma* P_bar */
{
  for (int j=0; j<d; j++)
  {
    xExpand[j] =xCentroid[j]*(1-gamma)/d+ (gamma)*xReflect[j];
  }
  yExpand=(*f)(xExpand,d);

}

void my_simplex:: my_Contraction()
/* return CONTRACTION P*** =beta* Ph +(1-beta)*P_bar */
{
  for (int j=0; j<d; j++)
  {
    xContract[j]=xCentroid[j]*(1-beta)/d+beta*xh[j];
  }
  yContract=(*f)(xContract,d);
}

void my_simplex::replace_all()
{
  for (int i=0; i<d+1; i++)
    {
      if (i==imin) continue;
      for (int j=0; j<d; j++)
	{
	  x[d*i+j]=0.5*(x[d*i+j]+xl[j]);
	}
    }
}

double my_simplex::get_yavg()
{
  double yavg=0.;
  for (int i=0; i<d+1; i++)
    {
      yavg+=y[i];
    }
  yavg=yavg/(d+1);
  return yavg;
}

double my_simplex::get_sigma()
{
  double yavg=0.;
  double sigma=0;
  for (int i=0; i<d+1; i++)
    {
      yavg+=y[i];
    }
  yavg=yavg/(d+1);
  for (int i=0; i<d+1; i++)
    {
      sigma+=pow((y[i]-yavg),2);
    }

  sigma=sigma/(d+1);
  return sigma;
}

void my_simplex::print_Centroid()
{

  std::cout << "Current xCentroid is : " << std::endl;
  for (int k=0;k<d; k++)
    {
      std::cout << xCentroid[k];
      if (k==d-1)
	std::cout << std::endl;
      else std::cout<< ", ";

    }
}

void my_simplex::print_Reflect()
{
  std::cout << "Current xReflect and y value are : " << std::endl;
  for (int k=0;k<d; k++)
    {
      std::cout << xReflect[k];
      if (k==d-1)
	std::cout <<", " << yReflect << std::endl;
      else std::cout<< ", ";

    }
}

void my_simplex::print_Expand()
{

  std::cout << "Current xExpand and y value are : " << std::endl;
  for (int k=0;k<d; k++)
    {
      std::cout << xExpand[k];
      if (k==d-1)
	std::cout << ", " << yExpand << std::endl;
      else std::cout<< ", ";

    }
}

void my_simplex::print_Contract()
{
  std::cout << "Current xContract and y value are : " << std::endl;
  for (int k=0; k<d; k++)
    {
      std::cout << xContract[k];
      if (k==d-1)
	std::cout << ", " << yContract << std::endl;
      else std::cout << ", ";

    }

}

void my_simplex::print_max()
{
  std::cout << "Printing imax and inmax and their values " << std::endl;
  std::cout << "imax = " << imax << ", y[imax] = " << yh << std::endl;
  std::cout << "inmax = " << inmax << ", y[inmax] = " << ynh << std::endl;
}

void my_simplex::print_min()
{
  std::cout << "Printing imin and its value " << std::endl;
  std::cout << "imin = " << imin << ", y[imin] = " << yl << std::endl;
}

void my_simplex::print_xyh()
{
  std::cout << "The highest value is " << std::endl;
  for (int i=0; i<d; i++)
    {
      std::cout << xh[i];
      if ((i+1)% d !=0)
        {
          std::cout << ", " ;
        }
      else
        {
          std::cout << ", " << yh << std::endl;
        }
    }
}

void my_simplex::print_xyl()
{
  std::cout << "The lowest value is " << std::endl;
  for (int i=0; i<d; i++)
    {
      std::cout << xl[i];
      if ((i+1)% d !=0)
        {
          std::cout << ", " ;
        }
      else
        {
          std::cout << ", " << yl << std::endl;
        }
    }

}

void my_simplex::print_xy()
{
  // print current x and y
  std::cout << "Current x and y values are: " << std::endl;
  for (int i=0; i< d*(d+1); i++)
    {
      std::cout << x[i];
      if ((i+1) % d !=0)
        {
          std::cout << ", ";
        }
      else
        {
          div_t ratio;
          ratio=div(i,d);
	  std::cout << ", " << y[ratio.quot] << std::endl;
        }
    }

}
void my_simplex::print_all()
{
// print current x
  std::cout << "Current x values are: " << std::endl;
  for (int i=0; i< d*(d+1); i++)
    {
      std::cout << x[i];
      if ((i+1) % d !=0)
	{
	  std::cout << ", ";
	}
      else
	{
	  div_t ratio;
	  ratio=div(i,d);
	  std::cout << ", " << y[ratio.quot]<<std::endl;
	}
    }
  std::cout << "Current centroid: " << std::endl;
  for (int i=0; i< d; i++)
      {
	std::cout << xCentroid[i];
          if ((i+1) % d !=0)
          {
	      std::cout << ", ";
           }
          else
          {
	    std::cout << std::endl;
          }
     }
  std::cout << "Current Reflection: " << std::endl;
  for (int i=0; i< d; i++)
     {
         std::cout << xReflect[i];
	 if ((i+1) % d !=0)
	 {
	     std::cout << ", ";
	 }
	 else
	 {
	   std::cout << ", " << yReflect << std::endl;
	 }
    }
  std::cout << "Current Expansion: " << std::endl;
  for (int i=0; i< d; i++)
      {
	std::cout << xExpand[i];
	  if ((i+1) % d !=0)
	  {
	      std::cout << ", ";
	  }
	  else
	  {
	    std::cout << ", " << yExpand << std::endl;
	  }
      }
  std::cout << "Current Contraction: " << std::endl;
  for (int i=0; i< d; i++)
      {
	std::cout << xContract[i];
	  if ((i+1) % d !=0)
	  {
	      std::cout << ", ";
	  }
	  else
	  {
	    std::cout << ", " << yContract << std::endl;
	  }
     }
  std::cout << "The highest value is " << std::endl;
  for (int i=0; i<d; i++)
    {
      std::cout << xh[i];
      if ((i+1)% d !=0)
	{
	  std::cout << ", " ;
	}
      else
	{
	  std::cout << ", " << yh << std::endl;
	}
    }
  std::cout << "The lowest value is " << std::endl;
  for (int i=0; i<d; i++)
    {
      std::cout << xl[i];
      if ((i+1)% d !=0)
        {
          std::cout << ", " ;
        }
      else
        {
          std::cout << ", " << yl << std::endl;
        }
    }
    std::cout << "The lowest point is imin=" << imin << std::endl;

    std::cout << "The highest point is imax=" << imax << std::endl;

    std::cout << "The next highest point is inmax=" << inmax << std::endl;
}


my_Nelder_Mead::my_Nelder_Mead(int dd, double alpha, double beta, double gamma, int NNtry, double eeps, my_func *ff): d(dd), Ntry(NNtry), eps(eeps), f(ff), simplex(dd, alpha, beta, gamma, f){}

bool my_Nelder_Mead::one_cycle(my_simplex *s)
{
// execute one-iteration of Nelder-Mead method
  (*s).my_Centroid((*s).imax);
  //  (*s).print_Centroid();
  (*s).my_Reflection();
  // (*s).print_Reflect();
  if ((*s).yReflect <= (*s).yl)
    {
      // do expansion
      (*s).my_Expansion();
      //      (*s).print_Expand();
      if ((*s).yExpand < (*s).yl)
	{
	  // replace P_h with P_**
	  std::copy((*s).xExpand,(*s).xExpand+d, (*s).x+d*((*s).imax));
	  (*s).set_y();
	  return false;
	}
      else
	{
	  // replace P_h with P_*
	  std::copy((*s).xReflect,(*s).xReflect+d, (*s).x+d*((*s).imax));
	  (*s).set_y();
	  return true;
	}
    }
  else if (((*s).yReflect) >= (*s).ynh ) // do contraction
    {
      if (((*s).yReflect) < (*s).yh)
	{
	  std::copy((*s).xReflect,(*s).xReflect+d, (*s).x+d*((*s).imax));
	  (*s).set_y();
	  (*s).find_max();
	}
      (*s).my_Contraction();
      //    (*s).print_Contract();
      if ((*s).yContract < (*s).yh)
	{
	  std::copy((*s).xContract,(*s).xContract+d, (*s).x+d*((*s).imax));
	  (*s).set_y();
	  return false;

	}
      else
	{
	  (*s).replace_all();
	  (*s).set_y();
	  return false;
	}
     }
  else {
    // replace P_h with P_*
    std::copy((*s).xReflect,(*s).xReflect+d, (*s).x+d*((*s).imax));
    (*s).set_y();
    return true;
  }


}

bool my_Nelder_Mead::find_global_min(double xin[DMAX*(DMAX+1)])
/* try Nelder-Mead cycle Ntry times; if values converge then restart using point near new
minimum  */
{
  // initialize
  yfinal=10000000000000.; // a very large number
  simplex.imax=0;
  simplex.inmax=1;
  simplex.imin=2;
  simplex.my_SetUp(xin);
  simplex.find_max();
  simplex.find_min();
  //  simplex.print_xy();
  //simplex.print_xyh();
  //simplex.print_xyl();
  //simplex.print_max();
  //simplex.print_min();
  convergeYes=false;
  // bool reflectYes=false;
  //  double xnew[DMAX*(DMAX+1)];
  for (int i=0; i<Ntry; i++)
    {
      //reflectYes=
      one_cycle(&simplex);
      //if (reflectYes==true) --i;
      simplex.find_max();
      simplex.find_min();
      double ynewmin=simplex.yl;
      double ynewmax=simplex.yh;
      //     std::cout << "i=" << i << std::endl;
      //std::cout << std::endl << std::endl << std::endl;
      //simplex.print_xy();
      //simplex.print_xyh();
      //simplex.print_xyl();
      //simplex.print_max();
      //simplex.print_min();
      //std::cout << std::endl << std::endl << std::endl;
      // double yavg=simplex.get_yavg();
      //  double sigma=simplex.get_sigma();
      if (std::abs(ynewmax -ynewmin)/(std::abs(ynewmax)+std::abs(ynewmin)+eps) < eps)
      {
	    convergeYes=true;

	    // save old xi, generate new xstarti = xbest/rndm + rndm*step
	    if (ynewmin< yfinal)
	      {
		std::copy(simplex.x,simplex.x+d*(d+1),xfinal);
		yfinal=ynewmin;
		//		std::cout << "final i=" << i << ", ymin = " << ynewmin << ", ymax = " << ynewmax << std::endl;
		break;
	      }
	}
    }

  return convergeYes;
}



// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// >>>>>> Wrappertopness.cpp & Wrappertopness.h in "topness" <<<<<<<
double topnesscompute(double pb1[4], double pl[4], double MET[4], double sigmat, double sigmaW)
{

  double alpha=1.0; // parameter for reflection
  double beta=0.5;  // parameter for contraction
  double gamma=2.0;  // parameter for expansion

  const int d=4;    // number of parameters to scan over, not the space-time dimension!
  const int DIMMAX=d*(d+1);  // dimension of simplex
  double xin[d+1][d];    // starting point
  double xstart[DIMMAX]; // algorithm stores d+1 points of simplex in a single array


  double eps=0.000002;   // tolerance
  double Deltastep=20.;  // initial spacing of points, in GeV
  int Ntry=100000;    // maximum number of Nelder-Mead cycles to perform for a given initial seed
  int Nattempts=15; //   number of initial starts

  double edir[]={1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
  double ybest=1000000000.; // a big number
  double ybest1=100000000.;
  double xbest1[]={1000.,1000.,1000.,1000.};
//  double ybest2=100000000.;  // a big number
//  double xbest2[]={1000.,1000.,1000.,1000.};
  int i,j,k;
  // int tid;
  bool converge1;
// converge2;

  // initialize topness function  ***Modified by Yang Zhang 23.1.2018
  my_func topstat1(pb1,pl,MET,sigmat,sigmaW,1.0);
//  my_func topstat2(pb2,pb1,pl,MET,sigmat,sigmaW,1.0); // other combination

  // initialize topness computation
  my_Nelder_Mead my_check1(d,alpha,beta,gamma, Ntry, eps, &topstat1);
//  my_Nelder_Mead my_check2(d,alpha,beta,gamma, Ntry, eps, &topstat2);
  double yl;
  // begin loop over Nattempts
  for (k=0; k<Nattempts; k++)
    {
      // initialize starting point
      for (i=0;i<d+1; i++)
        {
          for (j=0; j<d; j++)
            {
              if (i==0)
                {
                  xin[0][j]=8000.0*(Gambit::Random::draw()-0.5);
                }
              else
                {
                  xin[i][j]=xin[0][j]+Deltastep*edir[d*(i-1)+j];
                }
            }
          std::copy(xin[i],xin[i]+d, xstart+d*i);  // copy initial data into xstart
        }
      // now first combination
      converge1=my_check1.find_global_min(xstart);
      if (converge1==true)
        {

          yl=my_check1.yfinal;
          if (yl < ybest1)
            {
              ybest1=yl;
              std::copy(my_check1.xfinal,my_check1.xfinal+d,xbest1);
            }
        }
      else
        {
          std::cout << " Minimum not found...exiting " << std::endl;
        }
//      // now do second combination
//      converge2=my_check2.find_global_min(xstart);
//      if (converge2==true)
//        {
//          yl=my_check2.yfinal;
//          if (yl < ybest2)
//            {
//              ybest2=yl;
//              std::copy(my_check2.xfinal,my_check2.xfinal+d,xbest2);
//            }
//        }
//      else
//	    {
//          std::cout << " Minimum not found...exiting " << std::endl;
//        }

    }

//  if (ybest1 < ybest2)
//    {
    ybest=ybest1;
//    std::copy(xbest1,xbest1+d,xbest);
//    }
//   else
//   {
//     ybest=ybest2;
//     std::copy(xbest2,xbest2+d,xbest);
//   }

  return ybest;

}
