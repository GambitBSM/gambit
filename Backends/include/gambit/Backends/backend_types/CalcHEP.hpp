//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Helper types for CalcHEP backend.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Sanjay Bloor
///          sanjay.bloor12@imperial.ac.uk
///  \date 2017 May
///
///  *************************

#ifndef __CalcHEP_types_hpp__
#define __CalcHEP_types_hpp__

namespace Gambit
{

  typedef double REAL; 
  
  struct colorBasis
  { 
    int pow; 
    int nC; 
    int * chains;
  };
  
  struct CalcHEP_interface
  {
    int forceUG;
    char * CALCHEP;
    int nvar;
    int nfunc;
    char ** varName;
    REAL * va;
    int nin;
    int nout;
    int nprc;
    char* (*pinf)(int, int , REAL*,int *);
    int  (*pinfAux)(int, int,int *,int*,int*);
    char** polarized;
    int (*calcFunc)(void);
    double * BWrange;
    int    * twidth;    
    int *   gtwidth;
    int *   gswidth;
    double (**aWidth)(char *);
    double (*sqme)(int,double,REAL*,REAL*,int*);
    char * (*den_info)(int, int, int *, int*);
    colorBasis *cb;  
  };

  struct numout
  {
    void * handle;
    REAL ** link;
    REAL *Q,*SC;
    int init;
    CalcHEP_interface * interface; 
  };
}

#endif /* defined __CalcHEP_types_hpp__ */
