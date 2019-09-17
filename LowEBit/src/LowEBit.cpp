//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Function definitions of LowEBit.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Jonathan Cornell
///          (jonathan.cornell@uc.edu)
///  \date 2019 Jan
///
///	 \author Dimitrios Skodras
///			 (dimitrios.skodras@udo.edu)
///  \date 2019 July
///
///  *********************************************

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/LowEBit/LowEBit_rollcall.hpp"


namespace Gambit
{
   namespace LowEBit
   {
      void CPV_Wilson_q_Simple(CPV_WC_q &result)
  	  // Simple calculation 3.4-3.6 of 1811.05480, ignoring
      // uncertainties
      {
          using namespace Pipes::CPV_Wilson_q_Simple;

          result.Cu[1] = (*Param["kappaU"])*(*Param["SinPhiU"])
             *1.16E-4;
          result.Cd[1] = (*Param["kappaD"])*(*Param["SinPhiD"])
             *1.45E-4;
          result.Cs[1] = (*Param["kappaS"])*(*Param["SinPhiS"])
             *1.45E-4;
          result.Cu[2] = (*Param["kappaU"])*(*Param["SinPhiU"])
             *(-1.07E-4);
          result.Cd[2] = (*Param["kappaD"])*(*Param["SinPhiD"])
             *(-1.14E-4);
          result.Cs[2] = (*Param["kappaS"])*(*Param["SinPhiS"])
             *(-1.14E-4);
      }

      void EDM_q_Wilson(dq &result)
	  // Calculation of quark EDMs (at mu_had) from Wilson Coefficients in e cm
      // TODO: Make work at any scale. - not necessary. LQCD data at 2GeV
      {
         using namespace Pipes::EDM_q_Wilson;

    	 double gf = Dep::SMINPUTS->GF;
    	 double mu = Dep::SMINPUTS->mU;
    	 double md = Dep::SMINPUTS->mD;
    	 double ms = Dep::SMINPUTS->mS;

    	 CPV_WC_q c = *Dep::CPV_Wilson_Coeff_q;
         result.u = sqrt(2.)*gf*2./3.*mu*c.Cu[1]*gev2cm;
         result.d = sqrt(2.)*gf*(-1./3.)*md*c.Cd[1]*gev2cm;
         result.s = sqrt(2.)*gf*(-1./3.)*ms*c.Cs[1]*gev2cm;
         //Heavy quarks for completeness??
      }

      void CEDM_q_Wilson(dq &result)
	  // Calculation of quark chromoEDMs (at mu_had) from Wilson Coefficients in cm
      // TODO: Make work at any scale.
      {
         using namespace Pipes::CEDM_q_Wilson;

    	 double gf = Dep::SMINPUTS->GF;
    	 double mu = Dep::SMINPUTS->mU;
    	 double md = Dep::SMINPUTS->mD;
    	 double ms = Dep::SMINPUTS->mS;

    	 CPV_WC_q c = *Dep::CPV_Wilson_Coeff_q;
         result.u = -sqrt(2.)*gf*mu*c.Cu[2]*gev2cm;
         result.d = -sqrt(2.)*gf*md*c.Cd[2]*gev2cm;
         result.s = -sqrt(2.)*gf*ms*c.Cs[2]*gev2cm;
         //Heavy quarks for completeness?? - (C)EDMs of heavy quarks do not enter explicitly the atomic/nuclear EDMs
      }

	  void EDM_129Xe_quark(double &result)
      // Calculation of 199Xe EDM from quark and CEDMs in e cm
      {
         using namespace Pipes::EDM_129Xe_quark;
		 double gPiNN = 13.17;
	  // CSchiff_Xe = 0.336;		1311.6701		
	  // a0_Ra = -3.3;				took mean of results shown in 1101.3529
	  // b_Ra = 0;					not calculated yet
	  // a1_Ra = 8.4;				took mean of results shown in 1101.3529
	
         dq dCEDM = *Dep::CEDM_q;
	  // 2.(+4 -1) 
         result = 2.0E-3 * (*Param["CSchiff_Xe"]) * gPiNN * 
			 ((*Param["a0_Xe"]+*Param["b_Xe"])*(dCEDM.u + dCEDM.d) + (*Param["a1_Xe"])*(dCEDM.u - dCEDM.d));
      }

      void lnL_EDM_129Xe_step(double &result)
      // Step function likelihood for neutron EDM (TODO: improve this!!!!!)
      {
    	  using namespace Pipes::lnL_EDM_129Xe_step;
    	  
		  if (abs(*Dep::EDM_dia) > 6.6E-27) //95% CL limit from arXiv:hep-ex/0602020
    		  result = 0.0;
    	  else
//    		  result = -1.0E50;
    		  result = 10.0;
      }

	  void EDM_211Rn_quark(double &result)
      // Calculation of 199Xe EDM from quark and CEDMs in e cm
	  // THESE ARE JUST COPIED NUMBERS OF XE!
      {
         using namespace Pipes::EDM_129Xe_quark;
		 double gPiNN = 13.17;
	  // CSchiff_Xe = 0.336;		1311.6701		
	  // a0_Ra = -3.3;				took mean of results shown in 1101.3529
	  // b_Ra = 0;					not calculated yet
	  // a1_Ra = 8.4;				took mean of results shown in 1101.3529
	
         dq dCEDM = *Dep::CEDM_q;
	  // 2.(+4 -1) 
         result = 2.0E-3 * (*Param["CSchiff_Rn"]) * gPiNN * 
			 ((*Param["a0_Rn"]+*Param["b_Rn"])*(dCEDM.u + dCEDM.d) + (*Param["a1_Rn"])*(dCEDM.u - dCEDM.d));
      }

      void lnL_EDM_211Rn_step(double &result)
      // Step function likelihood for neutron EDM (TODO: improve this!!!!!)
      {
    	  using namespace Pipes::lnL_EDM_211Rn_step;
    	  
		  if (abs(*Dep::EDM_dia) > 6.6E-27) //95% CL limit from arXiv:hep-ex/0602020
    		  result = 0.0;
    	  else
//    		  result = -1.0E50;
    		  result = 10.0;
      }


	  void EDM_225Ra_quark(double &result)
      // Calculation of 199Xe EDM from quark and CEDMs in e cm
	  // THESE ARE JUST COPIED NUMBERS OF XE!
      {
         using namespace Pipes::EDM_225Ra_quark;
		 double gPiNN = 13.17;
	  // CSchiff_Xe = 0.336;		1311.6701		
	  // a0_Ra = -3.3;				took mean of results shown in 1101.3529
	  // b_Ra = 0;					not calculated yet
	  // a1_Ra = 8.4;				took mean of results shown in 1101.3529
	
         dq dCEDM = *Dep::CEDM_q;
	  // 2.(+4 -1) 
         result = 2.0E-3 * (*Param["CSchiff_Ra"]) * gPiNN * 
			 ((*Param["a0_Ra"]+*Param["b_Ra"])*(dCEDM.u + dCEDM.d) + (*Param["a1_Ra"])*(dCEDM.u - dCEDM.d));
      }

      void lnL_EDM_225Ra_step(double &result)
      // Step function likelihood for neutron EDM (TODO: improve this!!!!!)
      {
    	  using namespace Pipes::lnL_EDM_225Ra_step;
    	  
		  if (abs(*Dep::EDM_dia) > 6.6E-27) //95% CL limit from arXiv:hep-ex/0602020
    		  result = 0.0;
    	  else
//    		  result = -1.0E50;
    		  result = 10.0;
      }


	  void EDM_199Hg_quark(double &result)
      // Calculation of 199Hg EDM from quark and CEDMs in e cm
      {
         using namespace Pipes::EDM_199Hg_quark;
		 double gPiNN = 13.17;
	  // CSchiff_Xe = -2.6;			1308.6283 averaging over multiple calculations
	  // a0_Hg + b_Hg= 0.028(26);	1308.6283 averaging over multiple calculations
	  // a1_Hg = 0.032(59);			1308.6283 averaging over multiple calculations
	
         dq dCEDM = *Dep::CEDM_q;
	  // 2.(+4 -1) 
         result = 2.0E-3 * (*Param["CSchiff_Hg"]) * gPiNN * 
			 ((*Param["a0_Hg"]+*Param["b_Hg"])*(dCEDM.u + dCEDM.d) + (*Param["a1_Hg"])*(dCEDM.u - dCEDM.d));
      }

      void lnL_EDM_199Hg_step(double &result)
      // Step function likelihood for 199Hg EDM (TODO: improve this!!!!!)
      {
    	  using namespace Pipes::lnL_EDM_199Hg_step;
    /*	  double sigma = 4.23E-30; //1601.04339
		  double mean = 2.2E-30; //1601.04339
		  result = 1/(sqrt(2*pi)*sigma) * exp(-pow(*Dep::EDM_dia - mean,2)/(2*sigma*sigma));
	*/	  
		  if (abs(*Dep::EDM_dia) < 7.4E-30) //90% CL limit from arXiv:hep-ex/0602020
			{result = 1.0;}
    	  else{
    		  result = -1.0E0;
		  }
  
      }

      void EDM_n_quark(double &result)
      // Calculation of neutron EDM from quark EDMs and CEDMs in e cm
      {
         using namespace Pipes::EDM_n_quark;

    	 double e = sqrt(4.*pi/Dep::SMINPUTS->alphainv);
         dq dEDM = *Dep::EDM_q;
         dq dCEDM = *Dep::CEDM_q;

         result = ((*Param["rhoD"])*dCEDM.d+(*Param["rhoU"])*dCEDM.u)/e
            + (*Param["gTu"])*dEDM.u + (*Param["gTd"])*dEDM.d
			+ (*Param["gTs"])*dEDM.s; // CEDMs are in cm, EDMs are in e cm
      }

      void lnL_EDM_n_step(double &result)
      // Step function likelihood for neutron EDM (TODO: improve this!!!!!)
      {
    	  using namespace Pipes::lnL_EDM_n_step;

    	  if (abs(*Dep::EDM_n) < 2.9E-26) //90% CL limit from arXiv:hep-ex/0602020
			{result = 0.0;}
    	  else{
    		  result = -2.0E50;
//    		  result = dEDM.s;
//			  result = abs(*Dep::EDM_n);
		  }
      }

	  void lnL_EDM_n_gaussianStep(double &result)
	  {
		  using namespace Pipes::lnL_EDM_n_gaussianStep;
		  if(abs(*Dep::EDM_n) < 2.9E-26)
			{
				double mu = -0.2E-26, sig = 2.0E-26;
				// mu and sig from arXiv:hep-ex/0602020 (sig is systematic and stat. errors added in quadrature)
				result = -1./2.*(std::log(2*pi) + 2*std::log(sig) + std::pow((*Dep::EDM_n - mu)/sig,2));
			}
		  else{result = -1.0E50;}		  
	  }

	  void lnL_EDM_n_gaussianOverall(double &result)
	  {
			using namespace Pipes::lnL_EDM_n_gaussianOverall;
			double mu = -0.2E-26, sig = 2.0E-26;
			// mu and sig from arXiv:hep-ex/0602020 (sig is systematic and stat. errors added in quadrature)
			// TODO: Systematic error is supposed to be uniformly distributed, not Gaussian -- adjust this
			// likelihood accordingly?
			result = -1./2.*(std::log(2*pi) + 2*std::log(sig) + std::pow((*Dep::EDM_n - mu)/sig,2));
	  }

   }
}
