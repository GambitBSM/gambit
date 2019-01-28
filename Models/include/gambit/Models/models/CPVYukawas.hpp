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
//
//  *********************************************

#ifndef __CPVYukawas_hpp__
#define __CPVYukawas_hpp__

#define MODEL CPVYukawas
	START_MODEL

	// Quark Yukawas
	DEFINEPARS(kappaU, kappaD, kappaS)
	DEFINEPARS(kappaC, kappaB, kappaT)
	DEFINEPARS(SinThetaU, SinThetaD, SinThetaS)
	DEFINEPARS(SinThetaC, SinThetaB, SinThetaT)

	// Lepton Yukawas
	DEFINEPARS(kappaE, kappaMu, kappaTau)
	DEFINEPARS(SinThetaE, SinThetaMu, SinThetaTau)
#undef MODEL

#endif
