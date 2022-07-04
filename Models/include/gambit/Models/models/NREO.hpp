//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  NREO model declarations. 
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///   
///  \author Neal Avis Kozar
///  \date 2018 March
///
///  *********************************************


#ifndef __NREO_hpp__
#define __NREO_hpp__

#define MODEL NREO_scalarDM
	START_MODEL
	DEFINEPARS(m)
	DEFINEPARS(c0_1, c0_3, c0_4, c0_5, c0_6, c0_7, c0_8, c0_9, c0_10, c0_11, c0_12, c0_13, c0_14, c0_15) 
	DEFINEPARS(c1_1, c1_3, c1_4, c1_5, c1_6, c1_7, c1_8, c1_9, c1_10, c1_11, c1_12, c1_13, c1_14, c1_15)
#undef MODEL

#define MODEL NREO_MajoranaDM
	START_MODEL
	DEFINEPARS(m)
	DEFINEPARS(c0_1, c0_3, c0_4, c0_5, c0_6, c0_7, c0_8, c0_9, c0_10, c0_11, c0_12, c0_13, c0_14, c0_15) 
	DEFINEPARS(c1_1, c1_3, c1_4, c1_5, c1_6, c1_7, c1_8, c1_9, c1_10, c1_11, c1_12, c1_13, c1_14, c1_15)
#undef MODEL

#define MODEL NREO_DiracDM
	START_MODEL
	DEFINEPARS(m)
	DEFINEPARS(c0_1, c0_3, c0_4, c0_5, c0_6, c0_7, c0_8, c0_9, c0_10, c0_11, c0_12, c0_13, c0_14, c0_15) 
	DEFINEPARS(c1_1, c1_3, c1_4, c1_5, c1_6, c1_7, c1_8, c1_9, c1_10, c1_11, c1_12, c1_13, c1_14, c1_15)
#undef MODEL



#endif
