//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
//
//  Model for Yukawa Couplings with CP violation
//
//  *********************************************
//
//  Authors
//  =======
//
//  \author Jonathan Cornell
//          (jonathan.cornell@uc.edu)
//  \date 2019 Jan
//  \author Dimitrios Skodras
//          (dimitrios.skodras@udo.edu)
//  \date 2020 Oct

//
//  *********************************************

#ifndef __CPVYukawas_hpp__
#define __CPVYukawas_hpp__

#define MODEL CPVYukawas
	START_MODEL

	// Quark Yukawas
	DEFINEPARS(CuHm, CuHp, CdHm, CdHp, CsHm, CsHp)
	DEFINEPARS(CcHm, CcHp, CbHm, CbHp, CtHm, CtHp)

	// Lepton Yukawas
	DEFINEPARS(CeHm, CeHp, CmuHm, CmuHp, CtauHm, CtauHp)
#undef MODEL

#endif
