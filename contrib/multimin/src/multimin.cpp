/*
  multimin.c (ver. 1.2) -- Interface to GSL multidim. minimization
  Copyright (C) 2002-2014 Giulio Bottazzi

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  (version 2) as published by the Free Software Foundation;

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/


/*

multimin is an interface to the various GSL minimization
routines. When invoked, all the information necessary to perform the
minimization are passed as formal parameters. This generate a pretty
long, FORTRAN-like, list of parameters. This approach allows, however,
to black-box, as far as possible, the interior functioning of the
routine from the rest of the program.

Let's analyse the calling convention in details:

multimin(size_t n,double *x,double *fun,
   unsigned *type,double *xmin,double *xmax,
   void (*f) (const size_t,const double *,void *,double *),
   void (* df) (const size_t,const double *, void *,double *),
   void (* fdf) (const size_t,const double *, void *,double *,double *),
   void *fparams,
   const struct multimin_params oparams)

where

--------------------------------------------------------------------
n

INPUT: dimension of the problem, number of independent variables of
the function.

--------------------------------------------------------------------
x

INPUT: pointer to an array of n values x[0],...x[n-1] containing the
initial estimate of the minimum point
OUTPUT: contains the final estimation of the minimum position

--------------------------------------------------------------------
type

a pointer to an array of integer type[1],...,type[n-1] describing the
boundary conditions for the different variables. The problem is solved
as an unconstrained one on a suitably transformed variable y. Possible
values are:

  Interval:                                       Transformation:
  0 unconstrained                                 x=y
  1 semi-closed right half line [ xmin,+infty )   x=xmin+y^2
  2 semi-closed left  half line ( -infty,xmax ]   x=xmax-y^2
  3 closed interval              [ xmin,xmax ]    x=SS+SD*sin(y)
  4 open right half line        ( xmin,+infty )   x=xmin+exp(y)
  5 open left  half line        ( -infty,xmax )   x=xmax-exp(y)
  6 open interval                ( xmin,xmax )    x=SS+SD*tanh(y)

where SS=.5(xmin+xmax) SD=.5(xmax-xmin)

There are also other UNSUPPORTED transformations used in various test
  7 open interval                ( xmin,xmax )    x=SS+SD*(1+y/sqrt(1+y^2))
  8 open right half line        ( xmin,+infty )   x=xmin+.5*(y+sqrt(1+y^2))
  9 open left  half line        ( -infty,xmax )   x=xmax+.5*(y-sqrt(1+y^2))
--------------------------------------------------------------------
xmin
xmax

pointers to arrays of double containing respectively the lower and
upper boundaries of the different variables. For a given variable,
only the values that are implied by the type of constraints, defined
as in *type, are actually inspected.

--------------------------------------------------------------------
f

f calculates the objective function at a specified point x. Its
specification is

void (*f) (const size_t n, const double *x,void *fparams,double *fval)

      n
      INPUT: the number of variables

      x
      INPUT:the point at which the function is required

      fparams
      pointer to a structure containing parameters required by the
      function. If no external parameter are required it can be set to
      NULL.

      fval
      OUTPUT: the value of the objective function at the current point
      x.

--------------------------------------------------------------------
df

df calculates the gradient of the objective function at a specified
point x. Its specification is

void (*df) (const size_t n, const double *x,void *fparams,double *grad)

      n
      INPUT: the number of variables

      x
      INPUT:the point at which the function is required

      fparams
      pointer to a structure containing parameters required by the
      function. If no external parameter are required it can be set to
      NULL.

      grad
      OUTPUT: the values of the gradient of the objective function at
      the current point x are stored in grad[0],...,grad[n-1].

--------------------------------------------------------------------
fdf

fdf calculates the value and the gradient of the objective function at
a specified point x. Its specification is

void (*fdf) (const size_t n, const double *x,void *fparams,double *fval,double *grad)

      n
      INPUT: the number of variables

      x
      INPUT:the point at which the function is required

      fparams
      pointer to a structure containing parameters required by the
      function. If no external parameter are required it can be set to
      NULL.

      fval
      OUTPUT: the value of the objective function at the current point
      x.

      grad
      OUTPUT: the values of the gradient of the objective function at
      the current point x are stored in grad[0],...,grad[n-1].

--------------------------------------------------------------------
fparams

pointer to a structure containing parameters required by the
function. If no external parameter are required it can be set to NULL.

--------------------------------------------------------------------

oparams

structure of the type "multimin_params" containing the optimization
parameters. The members are

      double step_size
          size of the first trial step

      double tol
          accuracy of the line minimization

      unsigned maxiter
          maximum number of iterations

      double epsabs
          accuracy of the minimization

      double maxsize;
          final size of the simplex

      unsigned method
          method to use. Possible values are:

          0: Fletcher-Reeves conjugate gradient
          1: Polak-Ribiere conjugate gradient
    2: Vector Broyden-Fletcher-Goldfarb-Shanno method
    3: Steepest descent algorithm
          4: Nelder-Mead simplex
    5: Vector Broyden-Fletcher-Goldfarb-Shanno method ver. 2
    6: Simplex algorithm of Nelder and Mead ver. 2
    7: Simplex algorithm of Nelder and Mead: random initialization

      unsigned verbosity
          if greater then 0 print info on intermediate steps

*/

#include "multimin/multimin.hpp"

namespace Gambit
{
  namespace multimin
  {

    struct g_params {
      size_t n;
      const unsigned *type;
      const double *xmin;
      const double *xmax;
      void (*f) (const size_t,const double *,void *,double *);
      void (* df) (const size_t,const double *, void *,double *);
      void (* fdf) (const size_t,const double *, void *,double *,double *);
      void *fparams;
    };


    void *multimin_alloc(size_t size){
        void *temp;
        if(!(temp = malloc(size))){
      perror("malloc, memory allocation failed");
      exit(1);
        }
        return temp;
    }

    static double g(const gsl_vector *y,void *gparams){

      struct g_params *p= (struct g_params *) gparams;

      size_t i;
      double dtmp1;
      double res=GSL_NAN;/* the function is forced to return a value */


      /* dereference useful stuff */
      const size_t n = p->n;
      const unsigned *type = p->type;
      const double * xmin = p->xmin;
      const double * xmax = p->xmax;

      double *x = (double *) multimin_alloc(sizeof(double)*n);

      /* compute values of x and of dx/dy */
      for(i=0;i<n;i++){
        if(type==NULL)
          x[i]= GET(y,i);
        else
          switch(type[i]){
          case 0:/* (-inf,+inf) */
      x[i]= GET(y,i);
      break;
          case 1:/* [a,+inf) */
      x[i]= xmin[i]+GET(y,i)*GET(y,i);
      break;
          case 2:/* (-inf,a] */
      x[i]= xmax[i]-GET(y,i)*GET(y,i);
      break;
          case 3:/* [a,b] */
      dtmp1 = sin( GET(y,i) );
      x[i]= .5*(xmin[i]*(1-dtmp1) +xmax[i]*(1+dtmp1));
      break;
          case 4:/* (a,+inf) */
      dtmp1 = exp( GET(y,i) );
      x[i]= xmin[i]+dtmp1;
      break;
          case 5:/* (-inf,a) */
      dtmp1 = -exp( GET(y,i) );
      x[i]= xmax[i]+dtmp1;
      break;
          case 6:/* (a,b) */
      dtmp1 = tanh( GET(y,i) );
      x[i]= .5*(xmin[i]*(1-dtmp1) +xmax[i]*(1+dtmp1));
      break;
          case 7:/* (a,b) second approach */
      dtmp1 = GET(y,i)/sqrt(1.+GET(y,i)*GET(y,i));
      x[i]= .5*(xmin[i]*(1-dtmp1) +xmax[i]*(1+dtmp1));
      break;
          case 8:/* (a,+inf) second approach */
      dtmp1 = sqrt(1.+GET(y,i)*GET(y,i));
      x[i]= xmin[i] + .5*(GET(y,i)+dtmp1);
      break;
          case 9:/* (-inf,a) second approach */
      dtmp1 = sqrt(1.+GET(y,i)*GET(y,i));
      x[i]= xmax[i] + .5*(GET(y,i)-dtmp1);
      break;
          }
      }

      p->f(n,x,p->fparams,&res) ;
      free (x);
      return(res);

    }

    static void dg(const gsl_vector *y,void *gparams,gsl_vector *dg){

      struct g_params *p= (struct g_params *) gparams;

      size_t i;
      double dtmp1,dtmp2;

      /* dereference useful stuff */
      const size_t n = p->n;
      const unsigned *type = p->type;
      const double * xmin = p->xmin;
      const double * xmax = p->xmax;

      double *x = (double *) multimin_alloc(sizeof(double)*n);
      double *dx = (double *) multimin_alloc(sizeof(double)*n);
      double *df = (double *) multimin_alloc(sizeof(double)*n);

      /* compute values of x and of dx/dy */
      for(i=0;i<n;i++){
        if(type==NULL){
          x[i]= GET(y,i);
          dx[i]= 1;
        }
        else
          switch(type[i]){
          case 0:/* (-inf,+inf) */
      x[i]= GET(y,i);
      dx[i]= 1;
      break;
          case 1:/* [a,+inf) */
      x[i]= xmin[i]+GET(y,i)*GET(y,i);
      dx[i]= 2.*GET(y,i);
      break;
          case 2:/* (-inf,a] */
      x[i]= xmax[i]-GET(y,i)*GET(y,i);
      dx[i]= -2.*GET(y,i);
      break;
          case 3:/* [a,b] */
      dtmp1 = sin( GET(y,i) );
      x[i]= .5*(xmin[i]*(1-dtmp1) +xmax[i]*(1+dtmp1));
      dx[i]= .5*(xmax[i]-xmin[i])*cos(GET(y,i));
      break;
          case 4:/* (a,+inf) */
      dtmp1 = exp( GET(y,i) );
      x[i]= xmin[i]+dtmp1;
      dx[i]= dtmp1;
      break;
          case 5:/* (-inf,a) */
      dtmp1 = -exp( GET(y,i) );
      x[i]= xmax[i]+dtmp1;
      dx[i]= dtmp1;
      break;
          case 6:/* (a,b) */
      dtmp1 = tanh( GET(y,i) );
      dtmp2 = cosh( GET(y,i) );
      x[i]= .5*(xmin[i]*(1-dtmp1) +xmax[i]*(1+dtmp1));
      dx[i]= .5*(xmax[i]-xmin[i])/(dtmp2*dtmp2);
      break;
          case 7:/* (a,b) second approach */
      dtmp1 = GET(y,i)/sqrt(1.+GET(y,i)*GET(y,i));
      dtmp2 = (1.+GET(y,i)*GET(y,i))*sqrt(1.+GET(y,i)*GET(y,i)) ;
      x[i]= .5*(xmin[i]*(1-dtmp1) +xmax[i]*(1+dtmp1));
      dx[i]= .5*(xmax[i]-xmin[i])/dtmp2;
      break;
          case 8:/* (a,+inf) second approach */
      dtmp1 = GET(y,i);
      dtmp2 = sqrt(1.+dtmp1*dtmp1);
      x[i]= xmin[i] + .5*(dtmp1+dtmp2);
      dx[i]= .5*(dtmp1+dtmp2)/dtmp2;
      break;
          case 9:/* (-inf,a) second approach */
      dtmp1 = GET(y,i);
      dtmp2 = sqrt(1.+dtmp1*dtmp1);
      x[i]= xmax[i] + .5*(dtmp1-dtmp2);
      dx[i]= .5*(dtmp2-dtmp1)/dtmp2;
      break;
          }
      }

      p->df(n,x,p->fparams,df);

      /* debug output; comment out if necessary */
      /*   fprintf(stderr,"#dg: x=( "); */
      /*   for(i=0;i<n;i++) */
      /*     fprintf(stderr,"%f ",GET(x,i)); */
      /*   fprintf(stderr,") dx=( "); */
      /*   for(i=0;i<n;i++) */
      /*     fprintf(stderr,"%f ",GET(dx,i)); */
      /*   fprintf(stderr,") df=( "); */
      /*   for(i=0;i<n;i++) */
      /*     fprintf(stderr,"%f ",GET(dg,i)); */

      for(i=0;i<n;i++){
        SET(dg,i,df[i]*dx[i]);
      }

      /* debug output; comment out if necessary */
      /*   fprintf(stderr,") dg=( "); */
      /*   for(i=0;i<n;i++) */
      /*     fprintf(stderr,"%f ",GET(dg,i)); */
      /*   fprintf(stderr,")\n"); */

      free (x);
      free (dx);
      free (df);

    }


    static void gdg(const gsl_vector *y,void *gparams,double *g,gsl_vector *dg){

      struct g_params *p= (struct g_params *) gparams;

      size_t i;
      double dtmp1,dtmp2;


      /* dereference useful stuff */
      const size_t n = p->n;
      const unsigned *type = p->type;
      const double * xmin = p->xmin;
      const double * xmax = p->xmax;

      double *x = (double *) multimin_alloc(sizeof(double)*n);
      double *dx = (double *) multimin_alloc(sizeof(double)*n);
      double *df = (double *) multimin_alloc(sizeof(double)*n);

      /* compute values of x and of dx/dy */
      for(i=0;i<n;i++){
        if(type==NULL){
          x[i]= GET(y,i);
          dx[i]= 1;
        }
        else
          switch(type[i]){
          case 0:/* (-inf,+inf) */
      x[i]= GET(y,i);
      dx[i]= 1;
      break;
          case 1:/* [a,+inf) */
      x[i]= xmin[i]+GET(y,i)*GET(y,i);
      dx[i]= 2.*GET(y,i);
      break;
          case 2:/* (-inf,a] */
      x[i]= xmax[i]-GET(y,i)*GET(y,i);
      dx[i]= -2.*GET(y,i);
      break;
          case 3:/* [a,b] */
      dtmp1 = sin( GET(y,i) );
      x[i]= .5*(xmin[i]*(1-dtmp1) +xmax[i]*(1+dtmp1));
      dx[i]= .5*(xmax[i]-xmin[i])*cos(GET(y,i));
      break;
          case 4:/* (a,+inf) */
      dtmp1 = exp( GET(y,i) );
      x[i]= xmin[i]+dtmp1;
      dx[i]= dtmp1;
      break;
          case 5:/* (-inf,a) */
      dtmp1 = -exp( GET(y,i) );
      x[i]= xmax[i]+dtmp1;
      dx[i]= dtmp1;
      break;
          case 6:/* (a,b) */
      dtmp1 = tanh( GET(y,i) );
      dtmp2 = cosh( GET(y,i) );
      x[i]= .5*(xmin[i]*(1-dtmp1) +xmax[i]*(1+dtmp1));
      dx[i]= .5*(xmax[i]-xmin[i])/(dtmp2*dtmp2);
      break;
          case 7:/* (a,b) second approach */
      dtmp1 = GET(y,i)/sqrt(1.+GET(y,i)*GET(y,i));
      dtmp2 = (1.+GET(y,i)*GET(y,i))*sqrt(1.+GET(y,i)*GET(y,i)) ;
      x[i]= .5*(xmin[i]*(1-dtmp1) +xmax[i]*(1+dtmp1));
      dx[i]= .5*(xmax[i]-xmin[i])/dtmp2;
      break;
          case 8:/* (a,+inf) second approach */
      dtmp1 = GET(y,i);
      dtmp2 = sqrt(1.+dtmp1*dtmp1);
      x[i]= xmin[i] + .5*(dtmp1+dtmp2);
      dx[i]= .5*(dtmp1+dtmp2)/dtmp2;
      break;
          case 9:/* (-inf,a) second approach */
      dtmp1 = GET(y,i);
      dtmp2 = sqrt(1.+dtmp1*dtmp1);
      x[i]= xmax[i] + .5*(dtmp1-dtmp2);
      dx[i]= .5*(dtmp2-dtmp1)/dtmp2;
      break;
          }
      }

      p->fdf(n,x,p->fparams,g,df);

      /* debug output; comment out if necessary */
      /*   fprintf(stderr,"#gdg: f=%f x=( ",g); */
      /*   for(i=0;i<n;i++) */
      /*     fprintf(stderr,"%f ",GET(x,i)); */
      /*   fprintf(stderr,") dx=( "); */
      /*   for(i=0;i<n;i++) */
      /*     fprintf(stderr,"%f ",GET(dx,i)); */
      /*   fprintf(stderr,") df=( "); */
      /*   for(i=0;i<n;i++) */
      /*     fprintf(stderr,"%f ",GET(dg,i)); */
      /*   fprintf(stderr,")\n"); */

      for(i=0;i<n;i++){
        SET(dg,i,df[i]*dx[i]);
      }

      free (x);
      free (dx);
      free (df);
    }


    /*

    n         the dimension of the problem
    x         INPUT: initial guess OUTPUT:  minimum point
    fun       INPUT: ------------- OUTPUT:  minimum value
    type      the types of the boundaries
    xmin      the minimum values
    xmax      the maximum values
    f         the structure of a function
    fparams   the parameters of the provided function
    oparams   parameters of the optimization

    */


    void
    multimin(size_t n,double *x,double *fun,
       const unsigned *type, const double *xmin,const double *xmax,
       void (*f) (const size_t,const double *,void *,double *),
       void (* df) (const size_t,const double *, void *,double *),
       void (* fdf) (const size_t,const double *, void *,double *,double *),
       void *fparams,
       const struct multimin_params oparams)
    {

      size_t i;
      double dtmp1;

      const gsl_multimin_fdfminimizer_type *Tfdf;
      const gsl_multimin_fminimizer_type *Tf;
      const char *Tname;

      gsl_vector * y  = gsl_vector_alloc (n);

      /* set the algorithm */
      switch(oparams.method){
      case 0:/* Fletcher-Reeves conjugate gradient */
        Tfdf = gsl_multimin_fdfminimizer_conjugate_fr;
        Tname = Tfdf->name;
        break;
      case 1:/* Polak-Ribiere conjugate gradient */
        Tfdf = gsl_multimin_fdfminimizer_conjugate_pr;
        Tname = Tfdf->name;
        break;
      case 2:/* Vector Broyden-Fletcher-Goldfarb-Shanno method */
        Tfdf = gsl_multimin_fdfminimizer_vector_bfgs;
        Tname = Tfdf->name;
        break;
      case 3:/* Steepest descent algorithm */
        Tfdf =gsl_multimin_fdfminimizer_steepest_descent;
        Tname = Tfdf->name;
        break;
      case 4:/* Simplex algorithm of Nelder and Mead */
        Tf = gsl_multimin_fminimizer_nmsimplex;
        Tname = Tf->name;
        break;
      case 5:/*  Vector Broyden-Fletcher-Goldfarb-Shanno2 method */
        Tfdf = gsl_multimin_fdfminimizer_vector_bfgs2;
        Tname = Tfdf->name;
        break;
      case 6:/* Simplex algorithm of Nelder and Mead version 2 */
        Tf = gsl_multimin_fminimizer_nmsimplex2;
        Tname = Tf->name;
        break;
      case 7:/* Simplex algorithm of Nelder and Mead: random initialization */
        Tf = gsl_multimin_fminimizer_nmsimplex2rand;
        Tname = Tf->name;
       break;

      default:
        fprintf(stderr,"Optimization method not recognized. Specify one of the following:\n\n");

        fprintf(stderr,"0: Fletcher-Reeves conjugate gradient\n");
        fprintf(stderr,"1: Polak-Ribiere conjugate gradient\n");
        fprintf(stderr,"2: Vector Broyden-Fletcher-Goldfarb-Shanno method\n");
        fprintf(stderr,"3: Steepest descent algorithm\n");
        fprintf(stderr,"4: Nelder-Mead simplex\n");
        fprintf(stderr,"5: Vector Broyden-Fletcher-Goldfarb-Shanno method ver. 2\n");
        fprintf(stderr,"6: Simplex algorithm of Nelder and Mead ver. 2\n");
        fprintf(stderr,"7: Simplex algorithm of Nelder and Mead: random initialization\n");
        fprintf(stderr,"or try -h\n");

        exit(EXIT_FAILURE);
      }

      /* --- OUPUT ---------------------------------- */
      if(oparams.verbosity>0){
        fprintf(stderr,"#--- MULTIMIN START\n");
        fprintf(stderr,"#    method                         %s\n",Tname);
        if(oparams.method<4 || oparams.method==5){
          fprintf(stderr,"#    initial step size              %g\n", oparams.step_size);
          fprintf(stderr,"#    line minimization tolerance    %g\n",oparams.tol);
          fprintf(stderr,"#    maximum number of iterations   %u\n",oparams.maxiter);
          fprintf(stderr,"#    precision                      %g\n",oparams.epsabs);
        }
        else{
          fprintf(stderr,"#    maximum number of iterations   %u\n",oparams.maxiter);
          fprintf(stderr,"#    maximum simplex size           %g\n",oparams.maxsize);
        }
      }
      /* -------------------------------------------- */



      /* compute values of y for initial condition */
      for(i=0;i<n;i++){
        if(type==NULL)
          SET(y,i,x[i]);
        else
          switch(type[i]){
          case 0:/* (-inf,+inf) */
      SET(y,i,x[i]);
      break;
          case 1:/* [a,+inf) */
      SET(y,i,sqrt( x[i]-xmin[i] ));
      break;
          case 2:/* (-inf,a] */
      SET(y,i,sqrt( xmax[i]-x[i] ));
      break;
          case 3:/* [a,b] */
      dtmp1 = (xmax[i]>xmin[i]?
         (2.*x[i]-xmax[i]-xmin[i])/(xmax[i]-xmin[i]) : 0);
      /*       dtmp1 = (2.*x[i]-xmax[i]-xmin[i])/(xmax[i]-xmin[i]); */
      SET(y,i,asin( dtmp1 ));
      break;
          case 4:/* (a,+inf) */
      SET(y,i,log( x[i]-xmin[i] ));
      break;
          case 5:/* (-inf,a) */
      SET(y,i,log( xmax[i]-x[i] ));
      break;
          case 6:/* (a,b) */
      dtmp1 = (2.*x[i]-xmax[i]-xmin[i])/(xmax[i]-xmin[i]);
      SET(y,i,gsl_atanh ( dtmp1 ));
      break;
          case 7:/* (a,b) second approach */
      dtmp1 = (2.*x[i]-xmax[i]-xmin[i])/(xmax[i]-xmin[i]);
      SET(y,i, dtmp1/sqrt(1-dtmp1*dtmp1));
      break;
          case 8:/* (a,+inf) second approach */
      dtmp1 = x[i]-xmin[i];
      SET(y,i, dtmp1-1./(4.*dtmp1));
      break;
          case 9:/* (-inf,a) second approach */
      dtmp1 = xmax[i]-x[i];
      SET(y,i, 1./(4.*dtmp1)-dtmp1);
      break;
          }
      }

      /* --- OUPUT ---------------------------------- */
      if(oparams.verbosity>1){
        fprintf(stderr,"#    - variables initial value and boundaries\n");
        for(i=0;i<n;i++){
          if(type==NULL)
      fprintf(stderr,"#    x[%d]=%e (-inf,+inf) trans 0 -> %e\n",(int) i,x[i],GET(y,i));
          else
      switch(type[i]){
      case 0:/* (-inf,+inf) */
        fprintf(stderr,"#    x[%d]=%e (-inf,+inf) trans 0 -> %e\n",(int) i,x[i],GET(y,i));
        break;
      case 1:/* [a,+inf) */
        fprintf(stderr,"#    x[%d]=%e [%g,+inf) trans 1 -> %e\n",(int) i,x[i],xmin[i],GET(y,i));
        break;
      case 2:/* (-inf,a] */
        fprintf(stderr,"#    x[%d]=%e (-inf,%g] trans 2 -> %e\n",(int) i,x[i],xmax[i],GET(y,i));
        break;
      case 3:/* [a,b] */
        fprintf(stderr,"#    x[%d]=%e [%g,%g] trans 3 -> %e\n",(int) i,x[i],xmin[i],xmax[i],GET(y,i));
        break;
      case 4:/* (a,+inf) */
        fprintf(stderr,"#    x[%d]=%e (%g,+inf) trans 4 -> %e\n",(int) i,x[i],xmin[i],GET(y,i));
        break;
      case 5:/* (-inf,a) */
        fprintf(stderr,"#    x[%d]=%e (-inf,%g) trans 5 -> %e\n",(int) i,x[i],xmax[i],GET(y,i));
        break;
      case 6:/* (a,b) */
        fprintf(stderr,"#    x[%d]=%e (%g,%g) trans 6 -> %e\n",(int) i,x[i],xmin[i],xmax[i],GET(y,i));
        break;
      case 7:
        fprintf(stderr,"#    x[%d]=%e (%g,%g) trans 7 -> %e\n",(int) i,x[i],xmin[i],xmax[i],GET(y,i));
        break;
      case 8:/* [a,+inf) */
        fprintf(stderr,"#    x[%d]=%e (%g,+inf) trans 8 -> %e\n",(int) i,x[i],xmin[i],GET(y,i));
        break;
      case 9:/* [a,+inf) */
        fprintf(stderr,"#    x[%d]=%e (-inf,%g) trans 9 -> %e\n",(int) i,x[i],xmax[i],GET(y,i));
        break;
      }
        }
        {
          double res;
          fprintf(stderr,"#    - function initial value\n");
          f(n,x,fparams,&res);
          fprintf(stderr,"#    f=%e\n",res);
        }
      }
      /* -------------------------------------------- */


      if(oparams.method<4 || oparams.method==5){/* methods with derivatives */

        unsigned iter=0;
        int status;
        struct g_params gparams;
        gsl_multimin_function_fdf GdG;
        gsl_multimin_fdfminimizer *s = gsl_multimin_fdfminimizer_alloc (Tfdf,n);

        /* set the parameters of the new function */
        gparams.n       = n;
        gparams.type    = type;
        gparams.xmin    = xmin;
        gparams.xmax    = xmax;
        gparams.f       = f;
        gparams.df      = df;
        gparams.fdf     = fdf;
        gparams.fparams = fparams;

        /* set the function to solve */
        GdG.f=g;
        GdG.df=dg;
        GdG.fdf=gdg;
        GdG.n=n;
        GdG.params=(void *) &gparams;


        /* initialize minimizer */
        status=gsl_multimin_fdfminimizer_set(s,&GdG,y,oparams.step_size,oparams.tol);

        if(status)
          {
      fprintf(stderr,"#ERROR: %s\n",gsl_strerror (status));
      exit(EXIT_FAILURE);
          }

        /* +++++++++++++++++++++++++++++++++++++++++++++++ */
        if(oparams.verbosity>2)
          fprintf(stderr,"#    - start minimization \n");
        /* +++++++++++++++++++++++++++++++++++++++++++++++ */

        do
          {

      if( ++iter > oparams.maxiter) break;

      status = gsl_multimin_fdfminimizer_iterate (s);

      /* +++++++++++++++++++++++++++++++++++++++++++++++ */
      if(oparams.verbosity>2){
        fprintf(stderr,"#     [%d]",iter);
        fprintf(stderr," g=%+12.6e  y=( ",s->f);
        for(i=0;i<n;i++)
          fprintf(stderr,"%+12.6e ",GET(s->x,i));
        fprintf(stderr,") dg=( ");
        for(i=0;i<n;i++)
          fprintf(stderr,"%+12.6e  ",GET(s->gradient,i));
              fprintf(stderr,") |dg|=%12.6e ",gsl_blas_dnrm2 (s->gradient));
              fprintf(stderr,"|dx|=%12.6e\n",gsl_blas_dnrm2 (s->dx));
      }
      /* +++++++++++++++++++++++++++++++++++++++++++++++ */


      if(status == GSL_ENOPROG){
        fprintf(stderr,"#    status: %s\n",gsl_strerror (status));
        break;
      }

      if(status){
        fprintf(stderr,"#WARNING: %s\n", gsl_strerror (status));
        break;
      }

      status = gsl_multimin_test_gradient (s->gradient,oparams.epsabs);

          }
        while (status == GSL_CONTINUE);

        gsl_vector_memcpy (y,s->x);
        *fun=s->f;
        gsl_multimin_fdfminimizer_free (s);

        /* +++++++++++++++++++++++++++++++++++++++++++++++ */
        if(oparams.verbosity>2){
          fprintf(stderr,"#    - end minimization\n");
          fprintf(stderr,"#    iterations %u\n",iter-1);
        }
        /* +++++++++++++++++++++++++++++++++++++++++++++++ */

      }
      else{ /* methods without derivatives */

        unsigned iter=0;
        int status;
        double size;
        gsl_vector *ss = gsl_vector_alloc (n);
        struct g_params gparams;
        gsl_multimin_function G;
        gsl_multimin_fminimizer *s=gsl_multimin_fminimizer_alloc (Tf,n);

        /* set the parameters of the new function */
        gparams.n       = n;
        gparams.type    = type;
        gparams.xmin    = xmin;
        gparams.xmax    = xmax;
        gparams.f       = f;
        gparams.fparams = fparams;

        /* set the function to solve */
        G.f=g;
        G.n=n;
        G.params=(void *) &gparams;

        /* Initial vertex size vector */
        gsl_vector_set_all (ss,oparams.step_size+oparams.maxsize);

        /* --- OUPUT ---------------------------------- */
        if(oparams.verbosity>0){
          size_t i;
          fprintf(stderr,"#    initial simplex sizes\n");
          fprintf(stderr,"#    ");
          for(i=0;i<n;i++)
      fprintf(stderr," %g", GET(ss,i));
          fprintf(stderr,"\n");
        }
        /* -------------------------------------------- */

        /* Initialize minimizer */
        status=gsl_multimin_fminimizer_set(s,&G,y,ss);

        if(status)
          {
      fprintf(stderr,"#ERROR: %s\n",gsl_strerror (status));
      exit(EXIT_FAILURE);
          }

        /* +++++++++++++++++++++++++++++++++++++++++++++++ */
        if(oparams.verbosity>2)
          fprintf(stderr,"#    - start minimization \n");
        /* +++++++++++++++++++++++++++++++++++++++++++++++ */

        do
          {

      if( ++iter > oparams.maxiter) break;

      status = gsl_multimin_fminimizer_iterate(s);
      size = gsl_multimin_fminimizer_size (s);

      /* +++++++++++++++++++++++++++++++++++++++++++++++ */
      if(oparams.verbosity>2){
        fprintf(stderr,"#    g=%g y=( ",s->fval);
        for(i=0;i<n;i++)
          fprintf(stderr,"%g ",GET(s->x,i));
        fprintf(stderr,") ");
        fprintf(stderr," simplex size=%g ",size);
        fprintf(stderr,"\n");
      }
      /* +++++++++++++++++++++++++++++++++++++++++++++++ */

      status=gsl_multimin_test_size (size,oparams.maxsize);
          }
        while (status == GSL_CONTINUE);

        gsl_vector_memcpy (y, s->x);
        *fun=s->fval;
        gsl_multimin_fminimizer_free (s);

        /* +++++++++++++++++++++++++++++++++++++++++++++++ */
        if(oparams.verbosity>2){
          fprintf(stderr,"#    - end minimization\n");
          fprintf(stderr,"#    iterations %u\n",iter-1);
        }
        /* +++++++++++++++++++++++++++++++++++++++++++++++ */

      }

      /* compute values of x */
      for(i=0;i<n;i++){
        if(type==NULL) /* (-inf,+inf) */
          x[i]=GET(y,i);
        else
          switch(type[i]){
          case 0:/* (-inf,+inf) */
      x[i]=GET(y,i);
      break;
          case 1:/* [a,+inf) */
      x[i]=xmin[i]+GET(y,i)*GET(y,i);
      break;
          case 2:/* (-inf,a] */
      x[i]=xmax[i]-GET(y,i)*GET(y,i);
      break;
          case 3:/* [a,b] */
      dtmp1 = sin( GET(y,i) );
      x[i]=.5*(xmin[i]*(1-dtmp1) +xmax[i]*(1+dtmp1));
      break;
          case 4:/* (a,+inf) */
      dtmp1 = exp( GET(y,i) );
      x[i]=xmin[i]+dtmp1;
      break;
          case 5:/* (-inf,a) */
      dtmp1 = -exp( GET(y,i) );
      x[i]=xmax[i]+dtmp1;
      break;
          case 6:/* (a,b) */
      dtmp1 = tanh( GET(y,i) );
      x[i]=.5*(xmin[i]*(1-dtmp1) +xmax[i]*(1+dtmp1));
      break;
          case 7:/* (a,b) second approach */
      dtmp1 = GET(y,i) ;
      dtmp1 = dtmp1/sqrt(1.+dtmp1*dtmp1);
      x[i]=.5*(xmin[i]*(1-dtmp1) +xmax[i]*(1+dtmp1));
      break;
          case 8:/* (a,+inf) second approach */
      dtmp1 = sqrt(1.+GET(y,i)*GET(y,i));
      x[i]= xmin[i] + .5*(dtmp1+GET(y,i));
      break;
          case 9:/* (a,+inf) second approach */
      dtmp1 = sqrt(1.+GET(y,i)*GET(y,i));
      x[i]= xmax[i] + .5*(GET(y,i)-dtmp1);
      break;
          }
      }

      /* --- OUPUT ---------------------------------- */
      if(oparams.verbosity>0){
        for(i=0;i<n;i++)
          fprintf(stderr,"#    %e -> x[%zd]=%e\n",GET(y,i),i,x[i]);
        fprintf(stderr,"#--- MULTIMIN END --- \n");
      }
      /* -------------------------------------------- */


      gsl_vector_free (y);

    }

  }
}