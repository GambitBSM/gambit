/*  
Header for the multimin interface to GSL,
by Giulio Bottazzi:

http://cafim.sssup.it/~giulio/software/multimin/multimin.html
*/

/*insert GNU extensions*/
//#define _GNU_SOURCE
/*in particular, use of NAN extension*/

/* used by <errno.h> */
extern int errno;

/* GSL ----------- */
#include <gsl/gsl_vector.h>
#include <gsl/gsl_multimin.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_blas.h>

/* --------------- */

#define GET(x,i) gsl_vector_get(x,i)
#define SET(x,i,y) gsl_vector_set(x,i,y)

namespace Gambit
{
  namespace multimin
  {

    struct multimin_params 
    {
      double step_size;
      double tol;
      unsigned maxiter;
      double epsabs;
      double maxsize;
      unsigned method;
      unsigned verbosity;
    };

    void multimin(size_t, double *, double *, 
      const unsigned *,const double *,const double *,
      void (*) (const size_t,const double *,void *,double *),
      void (*) (const size_t,const double *, void *,double *),
      void (*) (const size_t,const double *, void *,double *,double *),
      void *,
      const struct multimin_params);

  }
}
