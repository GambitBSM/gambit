//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Type definition header for module LowEBit.
///
///  Compile-time registration of type definitions
///  required for the rest of the code to
///  communicate with LowEBit.
///
///  Add to this if you want to define a new type
///  for the functions in LowEBit to return, but
///  you don't expect that type to be needed by
///  any other modules.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Jonathan Cornell
///          (jonathan.cornell@uc.edu)
///  \date 2019 Jan
///  *********************************************

#ifndef __LowEBit_types_hpp___
#define __LowEBit_types_hpp___

namespace Gambit
{
  namespace LowEBit
  {
     // Wilson coefficients for CPV violating operators as defined
     // in 1811.05480
     class CPV_WC_q
	 {
	    public:
    	   CPV_WC_q();
    	   // Cq[1] is the Wilson coefficient for operator 1, Cq[2]
    	   // for operator 2. Cq[0] is not used. Cw is for the Weinberg operator.
    	   double Cu[3], Cd[3], Cs[3], Cc[3], Cb[3], Ct[3], Cw[3];
	 };
     class CPV_WC_l
	 {
	    public:
    	   CPV_WC_l();
    	   // Cl[1] is the Wilson coefficient for operator 1, Cl[2]
    	   // for operator 2. Cl[0] is not used. 
    	   double Ce[3], Cmu[3], Ctau[3];
	 };


     // Quark (chromo)electric dipole moments
     class dq
     {
        public:
           dq();
           double u, d, s, c, b, t;
     };
     // Lepton electric dipole moments
     class dl
     {
        public:
           dl();
           double e, mu, tau;
     };
  }
}

#endif
