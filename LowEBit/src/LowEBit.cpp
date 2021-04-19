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
///  \date 2020 Dec
///
///  *********************************************
#include <iostream>
#include <fstream>
#include <cmath>
#include <typeinfo>
#include <Eigen/Dense>
#include <unsupported/Eigen/MatrixFunctions>

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/LowEBit/LowEBit_rollcall.hpp"
#include "gambit/LowEBit/RGE.h"
#include "gambit/LowEBit/input.h"
#include "gambit/LowEBit/LoopFunctions.h"
#include "gambit/LowEBit/QCD_beta.h"


namespace Gambit
{
   namespace LowEBit
   {
	// These arrays hold the numerical values for the WC prefactors, i.e. loop functions at the hadronic scale.
	static double Ce3[9];
	static double Cu3[9];
	static double Cd3[9];
	static double Cs3[9];
	static double Cu4[9];
	static double Cd4[9];
	static double Cs4[9];
	static double Cw[9];
	static double* qmasses;
	static double gsat2GeV;
	static long int cnt;

	void Ce3list(double muH, double Lambda){
		static bool first = true;
		if(first){
			LoopFunctions l;
			std::cout << "Ce3 calc" << std::endl;
			Ce3[0] = l.C3e('e',muH,Lambda,1,0,0,0,0,0,0,0,0);
			Ce3[1] = l.C3e('e',muH,Lambda,0,1,0,0,0,0,0,0,0);
			Ce3[2] = l.C3e('e',muH,Lambda,0,0,1,0,0,0,0,0,0);
			Ce3[3] = l.C3e('e',muH,Lambda,0,0,0,1,0,0,0,0,0);
			Ce3[4] = l.C3e('e',muH,Lambda,0,0,0,0,1,0,0,0,0);
			Ce3[5] = l.C3e('e',muH,Lambda,0,0,0,0,0,1,0,0,0);
			Ce3[6] = l.C3e('e',muH,Lambda,0,0,0,0,0,0,1,0,0);
			Ce3[7] = l.C3e('e',muH,Lambda,0,0,0,0,0,0,0,1,0);
			Ce3[8] = l.C3e('e',muH,Lambda,0,0,0,0,0,0,0,0,1);
			std::cout << "Ce3 e: " << Ce3[0] << std::endl;
			std::cout << "Ce3 m: " << Ce3[1] << std::endl;
			std::cout << "Ce3 t: " << Ce3[2] << std::endl;
			std::cout << "Ce3 u: " << Ce3[3] << std::endl;
			std::cout << "Ce3 d: " << Ce3[4] << std::endl;
			std::cout << "Ce3 s: " << Ce3[5] << std::endl;
			std::cout << "Ce3 c: " << Ce3[6] << std::endl;
			std::cout << "Ce3 b: " << Ce3[7] << std::endl;
			std::cout << "Ce3 t: " << Ce3[8] << std::endl;
			
			first = false;
		}
		return;	
	}
	
	void Cu3list(double muH, double Lambda){
		static bool first = true;
		if(first){
			RGE rge;
			std::cout << "Cu3 calc" << std::endl;
			Cu3[0] = rge.C_2GeV_0(4,muH,Lambda,1,0,0,0,0,0,0,0,0)[2];
			Cu3[1] = rge.C_2GeV_0(4,muH,Lambda,0,1,0,0,0,0,0,0,0)[2];
			Cu3[2] = rge.C_2GeV_0(4,muH,Lambda,0,0,1,0,0,0,0,0,0)[2];
			Cu3[3] = rge.C_2GeV_0(4,muH,Lambda,0,0,0,1,0,0,0,0,0)[2];
			Cu3[4] = rge.C_2GeV_0(4,muH,Lambda,0,0,0,0,1,0,0,0,0)[2];
			Cu3[5] = rge.C_2GeV_0(4,muH,Lambda,0,0,0,0,0,1,0,0,0)[2];
			Cu3[6] = rge.C_2GeV_0(4,muH,Lambda,0,0,0,0,0,0,1,0,0)[2];
			Cu3[7] = rge.C_2GeV_0(4,muH,Lambda,0,0,0,0,0,0,0,1,0)[2];
			Cu3[8] = rge.C_2GeV_0(4,muH,Lambda,0,0,0,0,0,0,0,0,1)[2];
			std::cout << "Cu3 e: " << Cu3[0] << std::endl;
			std::cout << "Cu3 m: " << Cu3[1] << std::endl;
			std::cout << "Cu3 t: " << Cu3[2] << std::endl;
			std::cout << "Cu3 u: " << Cu3[3] << std::endl;
			std::cout << "Cu3 d: " << Cu3[4] << std::endl;
			std::cout << "Cu3 s: " << Cu3[5] << std::endl;
			std::cout << "Cu3 c: " << Cu3[6] << std::endl;
			std::cout << "Cu3 b: " << Cu3[7] << std::endl;
			std::cout << "Cu3 t: " << Cu3[8] << std::endl;
			first = false;
		}
		return;	
	}
	void Cd3list(double muH, double Lambda){
		static bool first = true;
		if(first){
			RGE rge;
			std::cout << "Cd3 calc" << std::endl;
			Cd3[0] = rge.C_2GeV_0(4,muH,Lambda,1,0,0,0,0,0,0,0,0)[6];
			Cd3[1] = rge.C_2GeV_0(4,muH,Lambda,0,1,0,0,0,0,0,0,0)[6];
			Cd3[2] = rge.C_2GeV_0(4,muH,Lambda,0,0,1,0,0,0,0,0,0)[6];
			Cd3[3] = rge.C_2GeV_0(4,muH,Lambda,0,0,0,1,0,0,0,0,0)[6];
			Cd3[4] = rge.C_2GeV_0(4,muH,Lambda,0,0,0,0,1,0,0,0,0)[6];
			Cd3[5] = rge.C_2GeV_0(4,muH,Lambda,0,0,0,0,0,1,0,0,0)[6];
			Cd3[6] = rge.C_2GeV_0(4,muH,Lambda,0,0,0,0,0,0,1,0,0)[6];
			Cd3[7] = rge.C_2GeV_0(4,muH,Lambda,0,0,0,0,0,0,0,1,0)[6];
			Cd3[8] = rge.C_2GeV_0(4,muH,Lambda,0,0,0,0,0,0,0,0,1)[6];
			std::cout << "Cd3 e: " << Cd3[0] << std::endl;
			std::cout << "Cd3 m: " << Cd3[1] << std::endl;
			std::cout << "Cd3 t: " << Cd3[2] << std::endl;
			std::cout << "Cd3 u: " << Cd3[3] << std::endl;
			std::cout << "Cd3 d: " << Cd3[4] << std::endl;
			std::cout << "Cd3 s: " << Cd3[5] << std::endl;
			std::cout << "Cd3 c: " << Cd3[6] << std::endl;
			std::cout << "Cd3 b: " << Cd3[7] << std::endl;
			std::cout << "Cd3 t: " << Cd3[8] << std::endl;
	
			first = false;
		}
		return;	
	}
	void Cs3list(double muH, double Lambda){
		static bool first = true;
		if(first){
			RGE rge;
			std::cout << "Cs3 calc" << std::endl;
			Cs3[0] = rge.C_2GeV_0(4,muH,Lambda,1,0,0,0,0,0,0,0,0)[10];
			Cs3[1] = rge.C_2GeV_0(4,muH,Lambda,0,1,0,0,0,0,0,0,0)[10];
			Cs3[2] = rge.C_2GeV_0(4,muH,Lambda,0,0,1,0,0,0,0,0,0)[10];
			Cs3[3] = rge.C_2GeV_0(4,muH,Lambda,0,0,0,1,0,0,0,0,0)[10];
			Cs3[4] = rge.C_2GeV_0(4,muH,Lambda,0,0,0,0,1,0,0,0,0)[10];
			Cs3[5] = rge.C_2GeV_0(4,muH,Lambda,0,0,0,0,0,1,0,0,0)[10];
			Cs3[6] = rge.C_2GeV_0(4,muH,Lambda,0,0,0,0,0,0,1,0,0)[10];
			Cs3[7] = rge.C_2GeV_0(4,muH,Lambda,0,0,0,0,0,0,0,1,0)[10];
			Cs3[8] = rge.C_2GeV_0(4,muH,Lambda,0,0,0,0,0,0,0,0,1)[10];
			std::cout << "Cs3 e: " << Cs3[0] << std::endl;
			std::cout << "Cs3 m: " << Cs3[1] << std::endl;
			std::cout << "Cs3 t: " << Cs3[2] << std::endl;
			std::cout << "Cs3 u: " << Cs3[3] << std::endl;
			std::cout << "Cs3 d: " << Cs3[4] << std::endl;
			std::cout << "Cs3 s: " << Cs3[5] << std::endl;
			std::cout << "Cs3 c: " << Cs3[6] << std::endl;
			std::cout << "Cs3 b: " << Cs3[7] << std::endl;
			std::cout << "Cs3 t: " << Cs3[8] << std::endl;
	
			first = false;
		}
		return;	
	}
	void Cu4list(double muH, double Lambda){
		static bool first = true;
		if(first){
			RGE rge;
			std::cout << "Cu4 calc" << std::endl;
			Cu4[0] = rge.C_2GeV_0(4,muH,Lambda,1,0,0,0,0,0,0,0,0)[3];
			Cu4[1] = rge.C_2GeV_0(4,muH,Lambda,0,1,0,0,0,0,0,0,0)[3];
			Cu4[2] = rge.C_2GeV_0(4,muH,Lambda,0,0,1,0,0,0,0,0,0)[3];
			Cu4[3] = rge.C_2GeV_0(4,muH,Lambda,0,0,0,1,0,0,0,0,0)[3];
			Cu4[4] = rge.C_2GeV_0(4,muH,Lambda,0,0,0,0,1,0,0,0,0)[3];
			Cu4[5] = rge.C_2GeV_0(4,muH,Lambda,0,0,0,0,0,1,0,0,0)[3];
			Cu4[6] = rge.C_2GeV_0(4,muH,Lambda,0,0,0,0,0,0,1,0,0)[3];
			Cu4[7] = rge.C_2GeV_0(4,muH,Lambda,0,0,0,0,0,0,0,1,0)[3];
			Cu4[8] = rge.C_2GeV_0(4,muH,Lambda,0,0,0,0,0,0,0,0,1)[3];
			std::cout << "Cu4 e: " << Cu4[0] << std::endl;
			std::cout << "Cu4 m: " << Cu4[1] << std::endl;
			std::cout << "Cu4 t: " << Cu4[2] << std::endl;
			std::cout << "Cu4 u: " << Cu4[3] << std::endl;
			std::cout << "Cu4 d: " << Cu4[4] << std::endl;
			std::cout << "Cu4 s: " << Cu4[5] << std::endl;
			std::cout << "Cu4 c: " << Cu4[6] << std::endl;
			std::cout << "Cu4 b: " << Cu4[7] << std::endl;
			std::cout << "Cu4 t: " << Cu4[8] << std::endl;
	
			first = false;
		}
		return;	
	}
	void Cd4list(double muH, double Lambda){
		static bool first = true;
		if(first){
			RGE rge;
			std::cout << "Cd4 calc" << std::endl;
			Cd4[0] = rge.C_2GeV_0(4,muH,Lambda,1,0,0,0,0,0,0,0,0)[7];
			Cd4[1] = rge.C_2GeV_0(4,muH,Lambda,0,1,0,0,0,0,0,0,0)[7];
			Cd4[2] = rge.C_2GeV_0(4,muH,Lambda,0,0,1,0,0,0,0,0,0)[7];
			Cd4[3] = rge.C_2GeV_0(4,muH,Lambda,0,0,0,1,0,0,0,0,0)[7];
			Cd4[4] = rge.C_2GeV_0(4,muH,Lambda,0,0,0,0,1,0,0,0,0)[7];
			Cd4[5] = rge.C_2GeV_0(4,muH,Lambda,0,0,0,0,0,1,0,0,0)[7];
			Cd4[6] = rge.C_2GeV_0(4,muH,Lambda,0,0,0,0,0,0,1,0,0)[7];
			Cd4[7] = rge.C_2GeV_0(4,muH,Lambda,0,0,0,0,0,0,0,1,0)[7];
			Cd4[8] = rge.C_2GeV_0(4,muH,Lambda,0,0,0,0,0,0,0,0,1)[7];
			std::cout << "Cd4 e: " << Cd4[0] << std::endl;
			std::cout << "Cd4 m: " << Cd4[1] << std::endl;
			std::cout << "Cd4 t: " << Cd4[2] << std::endl;
			std::cout << "Cd4 u: " << Cd4[3] << std::endl;
			std::cout << "Cd4 d: " << Cd4[4] << std::endl;
			std::cout << "Cd4 s: " << Cd4[5] << std::endl;
			std::cout << "Cd4 c: " << Cd4[6] << std::endl;
			std::cout << "Cd4 b: " << Cd4[7] << std::endl;
			std::cout << "Cd4 t: " << Cd4[8] << std::endl;
	
			first = false;
		}
		return;	
	}
	void Cs4list(double muH, double Lambda){
		static bool first = true;
		if(first){
			RGE rge;
			std::cout << "Cs4 calc" << std::endl;
			Cs4[0] = rge.C_2GeV_0(4,muH,Lambda,1,0,0,0,0,0,0,0,0)[11];
			Cs4[1] = rge.C_2GeV_0(4,muH,Lambda,0,1,0,0,0,0,0,0,0)[11];
			Cs4[2] = rge.C_2GeV_0(4,muH,Lambda,0,0,1,0,0,0,0,0,0)[11];
			Cs4[3] = rge.C_2GeV_0(4,muH,Lambda,0,0,0,1,0,0,0,0,0)[11];
			Cs4[4] = rge.C_2GeV_0(4,muH,Lambda,0,0,0,0,1,0,0,0,0)[11];
			Cs4[5] = rge.C_2GeV_0(4,muH,Lambda,0,0,0,0,0,1,0,0,0)[11];
			Cs4[6] = rge.C_2GeV_0(4,muH,Lambda,0,0,0,0,0,0,1,0,0)[11];
			Cs4[7] = rge.C_2GeV_0(4,muH,Lambda,0,0,0,0,0,0,0,1,0)[11];
			Cs4[8] = rge.C_2GeV_0(4,muH,Lambda,0,0,0,0,0,0,0,0,1)[11];
			std::cout << "Cs4 e: " << Cs4[0] << std::endl;
			std::cout << "Cs4 m: " << Cs4[1] << std::endl;
			std::cout << "Cs4 t: " << Cs4[2] << std::endl;
			std::cout << "Cs4 u: " << Cs4[3] << std::endl;
			std::cout << "Cs4 d: " << Cs4[4] << std::endl;
			std::cout << "Cs4 s: " << Cs4[5] << std::endl;
			std::cout << "Cs4 c: " << Cs4[6] << std::endl;
			std::cout << "Cs4 b: " << Cs4[7] << std::endl;
			std::cout << "Cs4 t: " << Cs4[8] << std::endl;
	
			first = false;
		}
		return;	
	}
	void Cwlist(double muH, double Lambda){
		static bool first = true;
		if(first){
			RGE rge;
			std::cout << "Cw calc" << std::endl;
			//depending on the active flavours the WBO sits at a different position, but always the last
			int size = rge.C_2GeV_0(4,muH,Lambda,0,0,0,0,0,0,0,0,0).size();
			Cw[0] = rge.C_2GeV_0(4,muH,Lambda,1,0,0,0,0,0,0,0,0)[size-1];
			Cw[1] = rge.C_2GeV_0(4,muH,Lambda,0,1,0,0,0,0,0,0,0)[size-1];
			Cw[2] = rge.C_2GeV_0(4,muH,Lambda,0,0,1,0,0,0,0,0,0)[size-1];
			Cw[3] = rge.C_2GeV_0(4,muH,Lambda,0,0,0,1,0,0,0,0,0)[size-1];
			Cw[4] = rge.C_2GeV_0(4,muH,Lambda,0,0,0,0,1,0,0,0,0)[size-1];
			Cw[5] = rge.C_2GeV_0(4,muH,Lambda,0,0,0,0,0,1,0,0,0)[size-1];
			Cw[6] = rge.C_2GeV_0(4,muH,Lambda,0,0,0,0,0,0,1,0,0)[size-1];
			Cw[7] = rge.C_2GeV_0(4,muH,Lambda,0,0,0,0,0,0,0,1,0)[size-1];
			Cw[8] = rge.C_2GeV_0(4,muH,Lambda,0,0,0,0,0,0,0,0,1)[size-1];
			std::cout << "Cw e: " << Cw[0] << std::endl;
			std::cout << "Cw m: " << Cw[1] << std::endl;
			std::cout << "Cw t: " << Cw[2] << std::endl;
			std::cout << "Cw u: " << Cw[3] << std::endl;
			std::cout << "Cw d: " << Cw[4] << std::endl;
			std::cout << "Cw s: " << Cw[5] << std::endl;
			std::cout << "Cw c: " << Cw[6] << std::endl;
			std::cout << "Cw b: " << Cw[7] << std::endl;
			std::cout << "Cw t: " << Cw[8] << std::endl;
	
			first = false;
		}
		return;	
	}
	void initialise(double muH, double Lambda){
		static bool first = true;
		if(first){
		  std::fstream wcinit("/home/dskodras/gambitgit/LowEBit/src/WCinits1.dat", std::ios::app);
		  if (wcinit.is_open()){std::cout << "opened" << std::endl;}
		  else {std::cout << "failed" << std::endl;return;}
		  Cu3list(muH,Lambda);
		  Cd3list(muH,Lambda);
		  Cs3list(muH,Lambda);
		  Ce3list(muH,Lambda);
		  Cu4list(muH,Lambda);
		  Cd4list(muH,Lambda);
		  Cs4list(muH,Lambda);
		  Cwlist(muH,Lambda);
		  first = false;	
		  cnt = 1;
	  	  LoopFunctions c;
		  qmasses = c.get_masses2GeV();
		  AlphaS as;
		  gsat2GeV = sqrt(4*pi*as.run(2,4,1));
		  cout << "masses at 2GeV:" << endl;
		  cout  << qmasses[0] << endl;
		  cout  << qmasses[1] << endl;
		  cout  << qmasses[2] << endl;
		  cout  << qmasses[3] << endl;
		  cout  << qmasses[4] << endl;
		  cout  << qmasses[5] << endl;
		  cout << "gsat2GeV: " << gsat2GeV << endl;
		  if (wcinit.is_open()){
			wcinit << "quark masses at 2GeV. 1loop alpha_s running";
			for(int i=0;i<6;i++){wcinit << i << ": " << qmasses[i] << "; ";}
			wcinit << "\nValues for respective WCs at 2GeV. Each value stands for an isolated contribution by a specific fermion (0=e,1=mu,2=tau,3=u,4=d,5=s,6=c,7=b,8=t) where the others are\n \
shut down. The running of the WCs is done in 4- and 5-flavour theory, where the bottom quark gets integrated out at mb(mb).\n";
			wcinit << "Cu3:\n";
			for(int i = 0; i<9;i++){
				wcinit << i << ": " << Cu3[i] << "; ";
			}
			wcinit << "\nCd3:\n";
			for(int i = 0; i<9;i++){
				wcinit << i << ": " << Cd3[i] << "; ";
			}
			wcinit << "\nCs3:\n";
			for(int i = 0; i<9;i++){
				wcinit << i << ": " << Cs3[i] << "; ";
			}
			wcinit << "\nCe3:\n";
			for(int i = 0; i<9;i++){
				wcinit << i << ": " << Ce3[i] << "; ";
			}
			wcinit << "\nCu4:\n";
			for(int i = 0; i<9;i++){
				wcinit << i << ": " << Cu4[i] << "; ";
			}
			wcinit << "\nCd4:\n";
			for(int i = 0; i<9;i++){
				wcinit << i << ": " << Cd4[i] << "; ";
			}
			wcinit << "\nCs4:\n";
			for(int i = 0; i<9;i++){
				wcinit << i << ": " << Cs4[i] << "; ";
			}
			wcinit << "\nCw:\n";
			for(int i = 0; i<9;i++){
				wcinit << i << ": " << Cw[i] << "; ";
			}
			wcinit << "\n\n";

	
			double e = 0.30282212;
         		wcinit << "partonic (C)EDMs with unity Wilson coefficient at scale Lambda:\n";
			wcinit << "du: \n";
			for(int i = 0; i<9;i++){
				wcinit << i<< ": " << std::sqrt(2.)*GF*e/std::pow(gsat2GeV,2)*2./3.*qmasses[0]*Cu3[i]*gev2cm<< "; ";
			}
			wcinit << "\nGF: " << GF<< "; ";
			wcinit << "gs^2: " << gsat2GeV*gsat2GeV<< "; ";
			wcinit << "mu: " << qmasses[0]<< "; ";
			wcinit << "conv: " << gev2cm<< "; ";
			wcinit << "Cu3: " << Cu3[3]<< "; \n";
	
			wcinit << "\ndd:\n";
			for(int i = 0; i<9;i++){
				wcinit << i<< ": " << std::sqrt(2.)*GF*e/std::pow(gsat2GeV,2)*(-1.)/3.*qmasses[1]*Cd3[i]*gev2cm<< "; ";
			}
			wcinit << "\nds:\n";
			for(int i = 0; i<9;i++){
				wcinit << i<< ": " << std::sqrt(2.)*GF*e/std::pow(gsat2GeV,2)*(-1.)/3.*qmasses[2]*Cs3[i]*gev2cm<< "; ";
			}
			wcinit << "\nde:\n";
			for(int i = 0; i<9;i++){
				wcinit << i<< ": " << std::sqrt(2.)*GF*(-1)*me*Ce3[i]*gev2cm<< "; ";
			}
			wcinit << "\ncdu:\n";
			for(int i = 0; i<9;i++){
				wcinit << i<< ": " << -sqrt(2.)*GF/std::pow(gsat2GeV,2)*qmasses[0]*Cu4[i]*gev2cm<< "; ";
			}
			wcinit << "\ncdd:\n";
			for(int i = 0; i<9;i++){
				wcinit << i<< ": " << -sqrt(2.)*GF/std::pow(gsat2GeV,2)*qmasses[1]*Cd4[i]*gev2cm<< "; ";
			}
			wcinit << "\ncds:\n";
			for(int i = 0; i<9;i++){
				wcinit << i<< ": " << -sqrt(2.)*GF/std::pow(gsat2GeV,2)*qmasses[2]*Cs4[i]*gev2cm<< "; ";
			}
			wcinit << "\ncw:\n";
			for(int i = 0; i<9;i++){
				wcinit << i<< ": " << sqrt(2.)*GF/std::pow(gsat2GeV,2)*Cw[i]*gev2cm<< "; ";
			}
			wcinit << "\n\n";
	
	
		  }
		  else std::cout << "unable to open file" << std::endl;
		  wcinit.close();
	
		}
		cnt++;
	return;
	}
	
      void CPV_Wilson_q_Simple(CPV_WC_q &result)
  	  // Simple calculation 3.4-3.6 of 1811.05480, ignoring
      // uncertainties
      {
          using namespace Pipes::CPV_Wilson_q_Simple;

		  double gf = Dep::SMINPUTS->GF;
		  double vev = 1/sqrt((sqrt(2.)*gf));
		  double Lambda = 1000.0;
		  initialise(Mh,Lambda);
		  double me = 5.11E-4;
		  double mu = qmasses[0];
		  double md = qmasses[1];
		  double ms = qmasses[2];
		  double mc = qmasses[3];
		  double mb = qmasses[4];
		  double mt = qmasses[5];
	  	  
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

		  // Wilson Coefficients at hadronic scale.
		  // C3q(2GeV) = Cq3[0]*CeH(Lambda) + Cq3[1]*CmuH(Lambda) + ... + Cq3[9]*CtH(Lambda);

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
//		  for(int i = 0; i<9; i++){cout << "CqH[" << i << "] = " << CqH[i] << endl; }

		  for(int i = 1; i<3; i++) {result.Cu[i]=0;result.Cd[i]=0;result.Cs[i]=0;Cw[i]=0;}
		  for(int i = 0; i<9; i++){
		          result.Cu[1] = result.Cu[1] + Cu3[i]*CqH[i];
		          result.Cd[1] = result.Cd[1] + Cd3[i]*CqH[i];
		          result.Cs[1] = result.Cs[1] + Cs3[i]*CqH[i];
		          result.Cu[2] = result.Cu[2] + Cu4[i]*CqH[i];
		          result.Cd[2] = result.Cd[2] + Cd4[i]*CqH[i];
		          result.Cs[2] = result.Cs[2] + Cs4[i]*CqH[i];
			  result.Cw[1] = result.Cw[1] + Cw[i]*CqH[i];
			  }
/*		  for(int i = 1; i<3; i++) {
			  cout << endl << "Cu"<<i<< " " << result.Cu[i] << " ";
			  cout << "Cd"<<i<< " " << result.Cd[i] << " ";
			  cout << "Cs"<<i<< " " << result.Cs[i] << " " << endl;
			  cout << "Cw"<<i<< " " << result.Cw[i] << " " << endl;
		  }*/
//
//		  for(int i = 1; i<3; i++) {result.Cu[i]=result.Cu[i]/mH/mH;result.Cd[i]=result.Cd[i]/mH/mH;result.Cs[i]=result.Cs[i]/mH/mH;}
      }
	  
      void CPV_Wilson_l_Simple(CPV_WC_l &result)
  	  // Simple calculation 3.4-3.6 of 1811.05480, ignoring
      // uncertainties
      {
          using namespace Pipes::CPV_Wilson_l_Simple;

		  double gf = Dep::SMINPUTS->GF;
		  double vev = 1/sqrt((sqrt(2.)*gf));
		  double Lambda = 1000.0;
		  initialise(Mh,Lambda);
		  double me = 5.11E-4;
		  double mu = qmasses[0];
		  double md = qmasses[1];
		  double ms = qmasses[2];
		  double mc = qmasses[3];
		  double mb = qmasses[4];
		  double mt = qmasses[5];
		  
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

		std::fstream dne("/home/dskodras/gambitgit/LowEBit/src/dne.dat", std::ios::app);
	  	if (dne.is_open()){
			dne << "CuHm " << *Param["CuHm"] << "\n";
			dne << "CuHp " << *Param["CuHp"] << "\n";
			dne << "CdHm " << *Param["CdHm"] << "\n";
			dne << "CdHp " << *Param["CdHp"] << "\n";
		}
		  	dne.close();

//		  int sampleStyle = 2; //1: CuHm variable + CuHp fixed, 2: CuHmcos+CuHpsin variable together, but CuHm serves as variable
//		  if(sampleStyle==1){
		  double CeH[9] = {
			  (*Param["CeHm"])*cosThE + (*Param["CeHp"]*sinThE),
			  (*Param["CmuHm"])*cosThMu + (*Param["CmuHp"]*sinThMu),
			  (*Param["CtauHm"])*cosThTau + (*Param["CtauHp"]*sinThTau),
			  (*Param["CuHm"])*cosThU + (*Param["CuHp"]*sinThU),
			  (*Param["CdHm"])*cosThD + (*Param["CdHp"]*sinThD),
			  (*Param["CsHm"])*cosThS + (*Param["CsHp"]*sinThS),
			  (*Param["CcHm"])*cosThC + (*Param["CcHp"]*sinThC),
			  (*Param["CbHm"])*cosThB + (*Param["CbHp"]*sinThB),
			  (*Param["CtHm"])*1 + (*Param["CtHp"]*sinThT*0) //cosThT
		  		  };

		  for(int i = 1; i<3; i++) {result.Ce[i]=0;result.Cmu[i]=0;result.Ctau[i]=0;}
		  for(int i = 0; i<9; i++){
		          result.Ce[1] = result.Ce[1] + Ce3[i]*CeH[i];
/*			  cout << "Ce "<<i<< " " << result.Ce[i];
			  cout << " C3e "<<i<< " " << Ce3[i];
			  cout << " CeH "<<i<< " " << CeH[i];
			  cout << endl;*/
			  }
//		cout << "Ce: "<< " " << result.Ce[1] << endl;;
//
//		  for(int i = 1; i<3; i++) {result.Cu[i]=result.Cu[i]/mH/mH;result.Cd[i]=result.Cd[i]/mH/mH;result.Cs[i]=result.Cs[i]/mH/mH;}
      }
			  

      void EDM_q_Wilson(dq &result)
	  // Calculation of quark EDMs (at mu_had) from Wilson Coefficients in e cm
      // TODO: Make work at any scale. - not necessary. LQCD data at 2GeV
      {
         using namespace Pipes::EDM_q_Wilson;

    	 double e = sqrt(4.*pi/Dep::SMINPUTS->alphainv);
    	 double gf = Dep::SMINPUTS->GF;
    	 double mu = Dep::SMINPUTS->mU;
    	 double md = Dep::SMINPUTS->mD;
    	 double ms = Dep::SMINPUTS->mS;

    	 CPV_WC_q c = *Dep::CPV_Wilson_Coeff_q;
         result.u = sqrt(2.)*gf*e/pow(gsat2GeV,2)*2./3.*mu*c.Cu[1]*gev2cm;
         result.d = sqrt(2.)*gf*e/pow(gsat2GeV,2)*(-1./3.)*md*c.Cd[1]*gev2cm;
         result.s = sqrt(2.)*gf*e/pow(gsat2GeV,2)*(-1./3.)*ms*c.Cs[1]*gev2cm;
//	 cout << "du: " << result.u << " dd: " << result.d << " ds: " << result.s << endl;
         //Heavy quarks for completeness??
      }

      void EDM_l_Wilson(dl &result)
	  // Calculation of quark EDMs (at mu_had) from Wilson Coefficients in e cm
      // TODO: Make work at any scale. - not necessary. LQCD data at 2GeV
      {
         using namespace Pipes::EDM_l_Wilson;

    	 double gf = Dep::SMINPUTS->GF;
    	 //double me = Dep::SMINPUTS->mE;
	 double me = 5.11E-4;

    	 CPV_WC_l c = *Dep::CPV_Wilson_Coeff_l;
         result.e = sqrt(2.)*gf*(-1.)*me*c.Ce[1]*gev2cm;
//	 cout << "Ce[1]: " << c.Ce[1] << endl;
//	 cout << "result.e: " << result.e << endl;

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
         result.u = -sqrt(2.)*gf/pow(gsat2GeV,2)*mu*c.Cu[2]*gev2cm;
         result.d = -sqrt(2.)*gf/pow(gsat2GeV,2)*md*c.Cd[2]*gev2cm;
         result.s = -sqrt(2.)*gf/pow(gsat2GeV,2)*ms*c.Cs[2]*gev2cm;
         result.w = sqrt(2.)*gf/pow(gsat2GeV,2)*c.Cw[1]*gev2cm; //Ow = -1/3 gs f GGG. A 1/2 stays outside the dipole. Therefore the 2/3
//	 cout << "cdu: " << result.u << " cdd: " << result.d << " cds: " << result.s << " w: " << result.w << endl;
         //Heavy quarks for completeness?? - (C)EDMs of heavy quarks do not enter explicitly the atomic/nuclear EDMs
      }

	  void EDM_ThO_electron(double &result)
      // Calculation of electron EDM in e cm
      {
         using namespace Pipes::EDM_ThO_electron;
	
         dl dEDM = *Dep::EDM_l;
         result = dEDM.e ;
	// cout << "EDM_ThO_electron - eEDM: " << result << endl;
      }

          void lnL_EDM_ThO_gaussianStep(double &result)
	  {
		  using namespace Pipes::lnL_EDM_ThO_gaussianStep;
		  double mu = 4.3E-30, sig = 4.0E-30;
		  //double  offset = 1.1E-29; //taken from ACME: https://doi.org/10.1038/s41586-018-0599-8
	//	  cout << "Dep::EDM_ThO_para: " << abs(*Dep::EDM_para) << endl;
		  /*if(abs(*Dep::EDM_para) < 1.1E-29)
		  {
			result = 0.0;
			result = -1/2.*(std::log(2*pi) + 2*std::log(sig) + std::pow(( - mu )/sig,2));
		  }
		  else{
			if(*Dep::EDM_para < 0){offset = +offset;} //RFit - below the 90%CL it's a step function, above it is a gaussian
			else{offset = -offset;}
			result = -1/2.*(std::log(2*pi) + 2*std::log(sig) + std::pow((*Dep::EDM_para - mu + offset)/sig,2));
		  }*/
			//gaussian Overall:
		  	mu = 0.;
			result = 0.;
			result = -1./2*pow((*Dep::EDM_para - mu)/(sig),2);//std::log(2*pi) + 2*std::log(sig) 
//		  	cout << "gaussian result_EDM_ThO: " << result << endl;

	  }
      void EDM_n_quark(double &result)
      // Calculation of neutron EDM from quark EDMs and CEDMs in e cm
      {
         using namespace Pipes::EDM_n_quark;

    	 double e = sqrt(4.*pi/Dep::SMINPUTS->alphainv);
         dq dEDM = *Dep::EDM_q;
         dq dCEDM = *Dep::CEDM_q;

/*	 cout << "nEDM comparisons: " << endl;
	 cout << "uCEDM: " << dCEDM.u*(*Param["rhoU"]) << endl;
	 cout << "dCEDM: " << dCEDM.d*(*Param["rhoD"]) << endl;
	 cout << "uEDM: " << dCEDM.u*(*Param["gTu"])/e << endl;
	 cout << "dEDM: " << dCEDM.d*(*Param["gTd"])/e << endl;
	 cout << "sEDM: " << dCEDM.s*(*Param["gTs"])/e << endl;
	 cout << "wEDM: " << 25E-3*dCEDM.w << endl;
*/
         result = ((*Param["rhoD"])*dCEDM.d+(*Param["rhoU"])*dCEDM.u)
            + ((*Param["gTu"])*dEDM.u + (*Param["gTd"])*dEDM.d
			+ (*Param["gTs"])*dEDM.s )/e
			+ 25E-3*dCEDM.w // CEDMs are in cm, EDMs are in e cm, the 25E-3 is valid if w is given in GeV
			;
      }
	  void lnL_EDM_n_gaussianOverall(double &result)
	  {
			using namespace Pipes::lnL_EDM_n_gaussianOverall;
			double mu = 0., sig = 2.2E-26;//mu=-0.0E-26 , sig: 1.5(stat)+0.7(sys)
			// mu and sig from arXiv:hep-ex/0602020 (sig is systematic and stat. errors added in quadrature)
			// TODO: Systematic error is supposed to be uniformly distributed, not Gaussian -- adjust this
			// likelihood accordingly?
			//result = 0.;
			//

	
			result = -1./2*pow((*Dep::EDM_n - mu)/(sig),2);//std::log(2*pi) + 2*std::log(sig) 
			std::fstream dne("/home/dskodras/gambitgit/LowEBit/src/dne.dat", std::ios::app);
		  	if (dne.is_open()){
				dne << "dne: " << *Dep::EDM_n << "\n";
				dne << "dchi2: " << result << "\n";
			}
		  	dne.close();
	
//		  	cout << "gaussian result_EDM_n: " << result << endl;
			cnt++;
			cout << "sample: " << cnt << endl;
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
         dl dEDM = *Dep::EDM_l;
	  // 2.(+4 -1) 
         result = 2.0E-3 * (*Param["CSchiff_Hg"]) * gPiNN * 
			 ((*Param["a0_Hg"])*(dCEDM.u + dCEDM.d) + (*Param["a1_Hg"])*(dCEDM.u - dCEDM.d)) 
			 + *Param["ae_Hg"]*dEDM.e
			 ;
//	 result = -1.8E-4 * (4)*(dCEDM.u - dCEDM.d);
//	 cout << "d_e: " << dEDM.e << endl;	 
//	 cout << "dHg: " << result << endl;
      }

      void lnL_EDM_199Hg_step(double &result)
      // Step function likelihood for 199Hg EDM (TODO: improve this!!!!!)
      {
    	  using namespace Pipes::lnL_EDM_199Hg_step;
    		  double sig = 4.23E-30; //1601.04339
		  double mu = 2.2E-30; //1601.04339
	//	  double offset = 7.4E-30;//90% CL limit from arXiv:hep-ex/0602020
	//	  double value = *Dep::EDM_dia;
		  
/*		  if(abs(value) < 7.4E-30)
		  {
			result = 0.0;
			result = -1/2.*(std::log(2*pi) + 2*std::log(sig) + std::pow(( - mu )/sig,2));
		  }
		  else{
			if(value < 0){offset = +offset;} //RFit - below the 90%CL it's a step function, above it is a gaussian
			else{offset = -offset;}
			result = -1/2.*(std::log(2*pi) + 2*std::log(sig) + std::pow((value - mu + offset)/sig,2));
		  }
*/			//gaussian overall:
		  	mu = 0.;
			result = -1./2*pow((*Dep::EDM_dia - mu)/(sig),2);//std::log(2*pi) + 2*std::log(sig) 
		  	cout << "gaussian result_EDM_dia: " << result << endl;

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


   }
}
