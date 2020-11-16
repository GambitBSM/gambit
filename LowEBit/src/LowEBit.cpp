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
///  \date 2020 Oct
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
		  double gf = Dep::SMINPUTS->GF;
		  double vev = 1/sqrt((sqrt(2.)*gf));
		  double Lambda = 1000.0;
		  double me = Dep::SMINPUTS->mE;
		  double mmu = Dep::SMINPUTS->mMu;
		  double mtau = Dep::SMINPUTS->mTau;
		  double mu = Dep::SMINPUTS->mU;
		  double md = Dep::SMINPUTS->mD;
		  double ms = Dep::SMINPUTS->mS;
		  double mc = Dep::SMINPUTS->mCmC;
		  double mb = Dep::SMINPUTS->mBmB;
		  double mt = Dep::SMINPUTS->mT;
//
//		//MqX are from draft with orders <10^-9 omitted
		  double Mu3[9] = {3.23E-9, 2.20E-7, 1.37E-6, 1.34E-0+1.95E-1*std::log(pow(mH/Lambda,2)), -1.48E-13, -2.96E-12, 1.14E-6, 5.21E-7, -1.41E-5};
		  double Md3[9] = {3.26E-9, 2.23E-7, 1.40E-6, -3.21E-13, 6.20E-1+3.61E-2*std::log(pow(mH/Lambda,2)), -2.51E-12, 9.91E-7, 9.04E-7, -1.26E-5};
		  double Ms3[9] = {1.40E-6, 2.23E-7, 1.40E-6, -1.27E-10, -4.99E-11, 3.11E-2+1.81E-3*std::log(pow(mH/Lambda,2)), 9.91E-7, 9.04E-7, -1.26E-5};
		  double Mu4[9] = {0,0,0,-1.83E-0, 7.88E-13, 1.57E-11, 2.84E-10, 4.24E-10, 2.24E-5};
		  double Md4[9] = {0,0,0,1.70E-12, -8.47E-1, 1.57E-11, 2.84E-10, 4.24E-10, 2.24E-5};
		  double Ms4[9] = {0,0,0,6.76E-10, 3.13E-10, -4.25E-2, 2.84E-10, 4.24E-10, 2.24E-5};
		  double Mw[9] = {0,0,0,0,0,0,0,0,-4.70E-7};
//
		  double sinThE = *Param["CeHm"]*vev*vev*vev/Lambda/Lambda/2./sqrt(2.)/me;
		  double sinThMu = *Param["CmuHm"]*vev*vev*vev/Lambda/Lambda/2./sqrt(2.)/mmu;
		  double sinThTau = *Param["CtauHm"]*vev*vev*vev/Lambda/Lambda/2./sqrt(2.)/mtau;
		  double sinThU = *Param["CuHm"]*vev*vev*vev/Lambda/Lambda/2./sqrt(2.)/mu;
		  double sinThD = *Param["CdHm"]*vev*vev*vev/Lambda/Lambda/2./sqrt(2.)/md;
		  double sinThS = *Param["CsHm"]*vev*vev*vev/Lambda/Lambda/2./sqrt(2.)/ms;
		  double sinThC = *Param["CcHm"]*vev*vev*vev/Lambda/Lambda/2./sqrt(2.)/mc;
		  double sinThB = *Param["CbHm"]*vev*vev*vev/Lambda/Lambda/2./sqrt(2.)/mb;
		  double sinThT = *Param["CtHm"]*vev*vev*vev/Lambda/Lambda/2./sqrt(2.)/mt;
		  double cosThE = sqrt(1.-sinThE*sinThE);
		  double cosThMu = sqrt(1.-sinThMu*sinThMu);
		  double cosThTau = sqrt(1.-sinThTau*sinThTau);
		  double cosThU = sqrt(1.-sinThU*sinThU);
		  double cosThD = sqrt(1.-sinThD*sinThD);
		  double cosThS = sqrt(1.-sinThS*sinThS);
		  double cosThC = sqrt(1.-sinThC*sinThC);
		  double cosThB = sqrt(1.-sinThB*sinThB);
		  double cosThT = sqrt(1.-sinThT*sinThT);


//		  int sampleStyle = 2; //1: CuHm variable + CuHp fixed, 2: CuHmcos+CuHpsin variable together, but CuHm serves as variable
//		  if(sampleStyle==1){
		  double CqH[9] = {
			  (*Param["CeHm"])*cosThE + (*Param["CeHp"]*sinThE),
			  (*Param["CmuHm"])*cosThMu + (*Param["CmuHp"]*sinThMu),
			  (*Param["CtauHm"])*cosThTau + (*Param["CtauHp"]*sinThTau),
			  (*Param["CuHm"])*cosThU + (*Param["CuHp"]*sinThU),
			  (*Param["CdHm"])*cosThD + (*Param["CdHp"]*sinThD),
			  (*Param["CsHm"])*cosThS + (*Param["CsHp"]*sinThS),
			  (*Param["CcHm"])*cosThC + (*Param["CcHp"]*sinThC),
			  (*Param["CbHm"])*cosThB + (*Param["CbHp"]*sinThB),
			  (*Param["CtHm"])*cosThT + (*Param["CtHp"]*sinThT)
		  		  };
//		  }
//		  else if(sampleStyle==2){
	//	  double CqH[6] = {
	//		  (*Param["CuHm"]),
	//		  (*Param["CdHm"]),
	//		  (*Param["CsHm"]),
	//		  (*Param["CcHm"]),
	//		  (*Param["CbHm"]),
	//		  (*Param["CtHm"])
	//			  };

//		  }

		  for(int i = 1; i<3; i++) {result.Cu[i]=0;result.Cd[i]=0;result.Cs[i]=0;}
		  for(int i = 0; i<9; i++){
		          result.Cu[1] = result.Cu[1] + Mu3[i]*CqH[i];
		          result.Cd[1] = result.Cd[1] + Md3[i]*CqH[i];
		          result.Cs[1] = result.Cs[1] + Ms3[i]*CqH[i];
		          result.Cu[2] = result.Cu[2] + Mu4[i]*CqH[i];
		          result.Cd[2] = result.Cd[2] + Md4[i]*CqH[i];
		          result.Cs[2] = result.Cs[2] + Ms4[i]*CqH[i];
			  result.Cw[1] = result.Cw[1] + Mw[i]*CqH[i];
			  }
		  for(int i = 1; i<3; i++) {
			  cout << endl << "Cu"<<i<< " " << result.Cu[i] << " ";
			  cout << "Cd"<<i<< " " << result.Cd[i] << " ";
			  cout << "Cs"<<i<< " " << result.Cs[i] << " " << endl;
		  }
//
//		  for(int i = 1; i<3; i++) {result.Cu[i]=result.Cu[i]/mH/mH;result.Cd[i]=result.Cd[i]/mH/mH;result.Cs[i]=result.Cs[i]/mH/mH;}
      }
	  
      void CPV_Wilson_l_Simple(CPV_WC_l &result)
  	  // Simple calculation 3.4-3.6 of 1811.05480, ignoring
      // uncertainties
      {
          using namespace Pipes::CPV_Wilson_l_Simple;

	  	  double mH = 125.09;
		  double gf = Dep::SMINPUTS->GF;
		  double vev = 1/sqrt((sqrt(2.)*gf));
		  double Lambda = 1000.0;
		  double me = Dep::SMINPUTS->mE;
		  double mmu = Dep::SMINPUTS->mMu;
		  double mtau = Dep::SMINPUTS->mTau;
		  double mu = Dep::SMINPUTS->mU;
		  double md = Dep::SMINPUTS->mD;
		  double ms = Dep::SMINPUTS->mS;
		  double mc = Dep::SMINPUTS->mCmC;
		  double mb = Dep::SMINPUTS->mBmB;
		  double mt = Dep::SMINPUTS->mT;
//				   e	    				   mu	    tau      u         d        s        c        b         t
		  double Me3[9] = {3.94E-1 , 1.07E-7, 6.67E-7, 6.90E-9, 3.26E-9, 3.27E-8, 7.31E-7, 3.48E-7, -5.02E-7};
		  Me3[0] = Me3[0] +  3.08E-1*std::log(mH*mH/(Lambda*Lambda));
//
		  double sinThE = *Param["CeHm"]*vev*vev*vev/Lambda/Lambda/2./sqrt(2.)/me;
		  double sinThMu = *Param["CmuHm"]*vev*vev*vev/Lambda/Lambda/2./sqrt(2.)/mmu;
		  double sinThTau = *Param["CtauHm"]*vev*vev*vev/Lambda/Lambda/2./sqrt(2.)/mtau;
		  double sinThU = *Param["CuHm"]*vev*vev*vev/Lambda/Lambda/2./sqrt(2.)/mu;
		  double sinThD = *Param["CdHm"]*vev*vev*vev/Lambda/Lambda/2./sqrt(2.)/md;
		  double sinThS = *Param["CsHm"]*vev*vev*vev/Lambda/Lambda/2./sqrt(2.)/ms;
		  double sinThC = *Param["CcHm"]*vev*vev*vev/Lambda/Lambda/2./sqrt(2.)/mc;
		  double sinThB = *Param["CbHm"]*vev*vev*vev/Lambda/Lambda/2./sqrt(2.)/mb;
		  double sinThT = *Param["CtHm"]*vev*vev*vev/Lambda/Lambda/2./sqrt(2.)/mt;
		  double cosThE = sqrt(1.-sinThE*sinThE);
		  double cosThMu = sqrt(1.-sinThMu*sinThMu);
		  double cosThTau = sqrt(1.-sinThTau*sinThTau);
		  double cosThU = sqrt(1.-sinThU*sinThU);
		  double cosThD = sqrt(1.-sinThD*sinThD);
		  double cosThS = sqrt(1.-sinThS*sinThS);
		  double cosThC = sqrt(1.-sinThC*sinThC);
		  double cosThB = sqrt(1.-sinThB*sinThB);
		  double cosThT = sqrt(1.-sinThT*sinThT);

//		  int sampleStyle = 2; //1: CuHm variable + CuHp fixed, 2: CuHmcos+CuHpsin variable together, but CuHm serves as variable
//		  if(sampleStyle==1){
//		  double CeH[2] = {
//			  (*Param["CeHm"])*cosThE + (*Param["CeHp"]*sinThE),
//			  (*Param["CtHm"])*cosThT + (*Param["CtHp"]*sinThT)
//		  		  };
//		  }
//		  else if(sampleStyle==2){
		  double CeH[9] = {
			  (*Param["CeHm"]),
			  (*Param["CmuHm"]),
			  (*Param["CtauHm"]),
			  (*Param["CuHm"]),
			  (*Param["CdHm"]),
			  (*Param["CsHm"]),
			  (*Param["CcHm"]),
			  (*Param["CbHm"]),
			  (*Param["CtHm"])
				  };

//		  }

		  for(int i = 1; i<3; i++) {result.Ce[i]=0;result.Cmu[i]=0;result.Ctau[i]=0;}
		  for(int i = 0; i<9; i++){
		          result.Ce[1] = result.Ce[1] + Me3[i]*CeH[i];
			  }
		  for(int i = 1; i<9; i++) {
			  cout << "Ce"<<i<< " " << result.Ce[i];
		  }
//
//		  for(int i = 1; i<3; i++) {result.Cu[i]=result.Cu[i]/mH/mH;result.Cd[i]=result.Cd[i]/mH/mH;result.Cs[i]=result.Cs[i]/mH/mH;}
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
	 double gsat2GeV = 1.82415;

    	 CPV_WC_q c = *Dep::CPV_Wilson_Coeff_q;
         result.u = sqrt(2.)*gf/pow(gsat2GeV,2)*2./3.*mu*c.Cu[1]*gev2cm;
         result.d = sqrt(2.)*gf/pow(gsat2GeV,2)*(-1./3.)*md*c.Cd[1]*gev2cm;
         result.s = sqrt(2.)*gf/pow(gsat2GeV,2)*(-1./3.)*ms*c.Cs[1]*gev2cm;
	 cout << "du: " << result.u << " dd: " << result.d << " ds: " << result.s << endl;
         //Heavy quarks for completeness??
      }

      void EDM_l_Wilson(dl &result)
	  // Calculation of quark EDMs (at mu_had) from Wilson Coefficients in e cm
      // TODO: Make work at any scale. - not necessary. LQCD data at 2GeV
      {
         using namespace Pipes::EDM_l_Wilson;

    	 double gf = Dep::SMINPUTS->GF;
    	 double me = Dep::SMINPUTS->mE;
	 double gsat2GeV = 1.82415;

    	 CPV_WC_l c = *Dep::CPV_Wilson_Coeff_l;
         result.e = sqrt(2.)*gf/pow(gsat2GeV,2)*(-1.)*me*c.Ce[1]*gev2cm;
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
	 double gsat2GeV = 1.82415;

    	 CPV_WC_q c = *Dep::CPV_Wilson_Coeff_q;
         result.u = -sqrt(2.)*gf/gsat2GeV*mu*c.Cu[2]*gev2cm;
         result.d = -sqrt(2.)*gf/gsat2GeV*md*c.Cd[2]*gev2cm;
         result.s = -sqrt(2.)*gf/gsat2GeV*ms*c.Cs[2]*gev2cm;
	 cout << "cdu: " << result.u << " cdd: " << result.d << " cds: " << result.s << endl;
         //Heavy quarks for completeness?? - (C)EDMs of heavy quarks do not enter explicitly the atomic/nuclear EDMs
      }

	  void EDM_ThO_electron(double &result)
      // Calculation of electron EDM in e cm
      {
         using namespace Pipes::EDM_ThO_electron;
	
         dl dEDM = *Dep::EDM_l;
         result = dEDM.e ;
      }

          void lnL_EDM_ThO_gaussianStep(double &result)
	  {
		  using namespace Pipes::lnL_EDM_ThO_gaussianStep;
		  double mu = 4.3E-30, sig = 4.0E-30, offset = 1.1E-29; //taken from ACME: https://doi.org/10.1038/s41586-018-0599-8
		  cout << "Dep::EDM_ThO: " << abs(*Dep::EDM_para) << endl;
		  if(abs(*Dep::EDM_para) < 1.1E-29)
		  {
			result = 0.0;
			result = -1/2.*(std::log(2*pi) + 2*std::log(sig) + std::pow(( - mu )/sig,2));
		  }
		  else{
			if(*Dep::EDM_para < 0){offset = +offset;} //RFit - below the 90%CL it's a step function, above it is a gaussian
			else{offset = -offset;}
			result = -1/2.*(std::log(2*pi) + 2*std::log(sig) + std::pow((*Dep::EDM_para - mu + offset)/sig,2));
		  }
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
	 result = -1.8E-4 * (4)*(dCEDM.u - dCEDM.d);
	 cout << "dHg: " << result << endl;
      }

      void lnL_EDM_199Hg_step(double &result)
      // Step function likelihood for 199Hg EDM (TODO: improve this!!!!!)
      {
    	  using namespace Pipes::lnL_EDM_199Hg_step;
    		  double sig = 4.23E-30; //1601.04339
		  double mu = 2.2E-30; //1601.04339
		  double offset = 7.4E-30;//90% CL limit from arXiv:hep-ex/0602020
		  double value = *Dep::EDM_dia;
		  
		  cout << "Dep::EDM_dia: " << abs(value) << endl;
		  if(abs(value) < 7.4E-30)
		  {
			result = 0.0;
			result = -1/2.*(std::log(2*pi) + 2*std::log(sig) + std::pow(( - mu )/sig,2));
		  }
		  else{
			if(value < 0){offset = +offset;} //RFit - below the 90%CL it's a step function, above it is a gaussian
			else{offset = -offset;}
			result = -1/2.*(std::log(2*pi) + 2*std::log(sig) + std::pow((value - mu + offset)/sig,2));
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
			result = -1/2.*( - std::log(2*pi) - 2*std::log(sig) + std::pow(( - mu )/sig,2)); //check - factors of 2 missing
		  }
		  else{
			if(*Dep::EDM_n < 0){offset = +offset;} //RFit - below the 90%CL it's a step function, above it is a gaussian
			else{offset = -offset;}
			result = -1/2.*(std::log(2*pi) + 2*std::log(sig) + std::pow((*Dep::EDM_n - mu + offset)/sig,2));
		  }
		  cout << "result_EDM_n: " << result << endl;
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
			double mu = 0., sig = 2.0E-26;//mu=-0.0E-26
			// mu and sig from arXiv:hep-ex/0602020 (sig is systematic and stat. errors added in quadrature)
			// TODO: Systematic error is supposed to be uniformly distributed, not Gaussian -- adjust this
			// likelihood accordingly?
			cout << "mu_n: " << mu << endl;
		  	cout << "result_EDM_n: " << result << endl;
			result = -1.*(+ std::pow((*Dep::EDM_n - mu)/sig,2));//std::log(2*pi) + 2*std::log(sig) 
	  }

   }
}
