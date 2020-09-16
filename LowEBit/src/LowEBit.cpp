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

	  	  double mH = 125.09;
		  double kappaS[6] = {
			  (*Param["kappaU"])*(*Param["SinPhiU"]),
			  (*Param["kappaD"])*(*Param["SinPhiD"]),
			  (*Param["kappaS"])*(*Param["SinPhiS"]),
			  (*Param["kappaC"])*(*Param["SinPhiC"]),
			  (*Param["kappaB"])*(*Param["SinPhiB"]),
			  (*Param["kappaT"])*(*Param["SinPhiT"])};
		  double kappaC[6] = {
			  (*Param["kappaU"])*(pow(1-pow(*Param["SinPhiU"],2),0.5)),
			  (*Param["kappaD"])*(pow(1-pow(*Param["SinPhiD"],2),0.5)),
			  (*Param["kappaS"])*(pow(1-pow(*Param["SinPhiS"],2),0.5)),
			  (*Param["kappaC"])*(pow(1-pow(*Param["SinPhiC"],2),0.5)),
			  (*Param["kappaB"])*(pow(1-pow(*Param["SinPhiB"],2),0.5)),
			  (*Param["kappaT"])*(pow(1-pow(*Param["SinPhiT"],2),0.5))
			  };

		//MqX and Bs are from draft with orders <10^-9 omitted
		  double Mu3[6][6] = {
			  {2.58E-7,1.76E-7,6.96E-5,8.06E-3,1.12E-1,2.7},
			  {2.02E-7,0      ,0      ,0      ,0      ,0  },
			  {8.03E-5,0      ,0      ,3.0E-8 ,6.57E-8,0  },
			  {9.31E-3,0      ,3.0E-8 ,-2.04E-5,2.5E-5,0  },
			  {1.37E-1,0      ,6.57E-9,2.5E-5,-1.68E-4,0  },
			  {3.94   ,0      ,0      ,0      ,0  ,3.04E-2}};
		  double Md3[6][6] = {
			  {0      ,5.00E-8,0      ,0      ,0      ,0  },
			  {4.42E-8,1.21E-6,5.73E-5,1.65E-2,1.02E-1,2.38},
			  {0      ,6.80E-5,0      ,3.0E-8 ,6.57E-8,0  },
			  {0      ,1.77E-2,3.0E-8 ,-2.04E-5,2.5E-5,0  },
			  {0      ,1.21E-1,6.57E-9,2.5E-5,-1.68E-4,0  },
			  {0      ,3.94E-0,0      ,0      ,0  ,3.04E-2}};
		  double Ms3[6][6] = {
			  {0      ,0      ,5.00E-8,0      ,0      ,0  },
			  {0      ,0      ,1.71E-7,0      ,0      ,0  },
			  {4.42E-8,1.44E-7,4.79E-4,1.65E-2,1.02E-1,2.38},
			  {0      ,0      ,1.77E-2,-2.04E-5,2.5E-5,0  },
			  {0      ,0      ,1.27E-1,2.5E-5,-1.68E-4,0  },
			  {0      ,0      ,3.94E-0,0      ,0  ,3.04E-2}};
		  double Mu4[6][6] = {
			  {5.66E-7 ,-5.60E-7,-2.22E-4,-5.68E-2 ,-2.59E-1,-7.14},
			  {-6.71E-7,0       ,0        ,1.02E-9 ,0       ,0  },
			  {-2.66E-4,0       ,0        ,4.03E-7 ,-7.24E-8,0  },
			  {-6.66E-2,1.02E-9 ,4.03E-7  ,-2.74E-4,3.13E-4 ,0  },
			  {-3.28E-1,0       ,-7.24E-8 ,3.13E-4 ,1.85E-3 ,0  },
			  {-9.94   ,0       ,0        ,0       ,0       ,-9.62E-2}};
		  double Md4[6][6] = {
			  {0       ,-1.44E-7,0       ,0       ,0       ,0  },
			  {-1.12E-7,2.64E-6 ,-2.22E-4,-5.68E-2,-2.59E-1,-7.14},
			  {0       ,-2.66E-4,0       ,4.03E-7 ,-7.24E-8,0  },
			  {0       ,-6.66E-2,4.03E-7 ,-2.74E-4,3.13E-4 ,0  },
			  {0       ,-2.28E-1,-7.24E-8,3.13E-4 ,1.85E-3 ,0  },
			  {0       ,-9.94E-0,0       ,0       ,0       ,-9.62E-2}};
		  double Ms4[6][6] = {
			  {0       ,0       ,-1.44E-7,0       ,0       ,0  },
			  {0       ,0       ,-6.71E-7,0       ,0       ,0  },
			  {-1.20E-7,-5.60E-7,1.05E-3,-5.68E-2 ,-2.59E-1,-7.14},
			  {0       ,1.02E-9 ,-6.66E-2,-2.74E-4,3.13E-4 ,0  },
			  {0       ,0       ,-3.28E-1,3.13E-4 ,-1.85E-3,0  },
			  {0       ,0       ,-9.94E-0,0       ,0       ,-9.62E-2}};
		  double Mw[6][6] = {
			  {0      ,0       ,0      ,2.72E-9 ,0       ,0  },
			  {0      ,0       ,0      ,1.27E-8 ,1.62E-9 ,0  },
			  {0      ,0       ,0      ,5.05E-6 ,6.41E-7 ,0  },
			  {2.72E-9,1.27E-8 ,5.05E-6,-3.43E-3,4.14E-3 ,0  },
			  {0      ,1.62E-9 ,6.41E-7,4.14E-3 ,-1.64E-2,0  },
			  {0      ,0       ,0      ,0       ,0       ,-2.01E-1}};
		  double Bu3[6] = {3.42,0,0,0,0,0};
		  double Bd3[6] = {0,2.38,0,0,0,0};
		  double Bs3[6] = {0,0,2.38,0,0,0};
		  double Bu4[6] = {1.31,0,0,0,0,0};
		  double Bd4[6] = {0,0.936,0,0,0,0};
		  double Bs4[6] = {0,0,0.936,0,0,0};

		  for(int i = 1; i<3; i++) {result.Cu[i]=0;result.Cd[i]=0;result.Cs[i]=0;}
		  for(int i = 0; i<6; i++){
			  for(int j = 0; j<6; j++){
		          result.Cu[1] = result.Cu[1] + kappaS[i]*Mu3[i][j]*kappaC[j] + kappaS[i]*Bu3[i];
		          result.Cd[1] = result.Cd[1] + kappaS[i]*Md3[i][j]*kappaC[j] + kappaS[i]*Bd3[i];
		          result.Cs[1] = result.Cs[1] + kappaS[i]*Ms3[i][j]*kappaC[j] + kappaS[i]*Bs3[i];
		          result.Cu[2] = result.Cu[2] + kappaS[i]*Mu4[i][j]*kappaC[j] + kappaS[i]*Bu4[i];
		          result.Cd[2] = result.Cd[2] + kappaS[i]*Md4[i][j]*kappaC[j] + kappaS[i]*Bd4[i];
		          result.Cs[2] = result.Cs[2] + kappaS[i]*Ms4[i][j]*kappaC[j] + kappaS[i]*Bs4[i];
				  result.Cw[1] = result.Cw[1] + kappaS[i]*Mw[i][j]*kappaC[j];
			  }
		  }
		  for(int i = 1; i<3; i++) {result.Cu[i]=result.Cu[i]/mH/mH;result.Cd[i]=result.Cd[i]/mH/mH;result.Cs[i]=result.Cs[i]/mH/mH;}
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
		  double mu = 0.2E-26, sig = 1.6E-26, offset = 2.9E-26;
		  cout << "Dep::EDM_n: " << abs(*Dep::EDM_n) << endl;
		  if(abs(*Dep::EDM_n) < 2.9E-26)
		  {
			result = 0.0;
			result = -1/2.*(std::log(2*pi) + 2*std::log(sig) + std::pow(( - mu )/sig,2));
		  }
		  else{
			if(*Dep::EDM_n < 0){offset = +offset;} //RFit - below the 90%CL it's a step function, above it is a gaussian
			else{offset = -offset;}
			result = -1/2.*(std::log(2*pi) + 2*std::log(sig) + std::pow((*Dep::EDM_n - mu + offset)/sig,2));
		  }
/*		  if(abs(*Dep::EDM_n) < 2.9E-26)
			{
				double mu = -0.2E-26, sig = 2.0E-26;
				// mu and sig from arXiv:hep-ex/0602020 (sig is systematic and stat. errors added in quadrature)
				result = -1./2.*(std::log(2*pi) + 2*std::log(sig) + std::pow((*Dep::EDM_n - mu)/sig,2));
			}
		  else{result = -1.0E50;}		  
		  result = gaussian_upper_limit(*Dep::EDM_n,mu,

*/
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
