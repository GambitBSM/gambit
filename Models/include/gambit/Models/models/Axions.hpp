//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Models for QCD axions and axion-like particles.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Sebastian Hoof
///  \date 2016 Oct
///  \date 2017 Feb, May, Jul
///  \date 2018 Feb
///  \date 2019 Feb
///
///  *********************************************

#ifndef __GeneralALP_hpp__
#define __GeneralALP_hpp__

// General axion model with parametric temperature-dependent mass.
#define MODEL GeneralALP
  START_MODEL
  // Physical units: gagg [GeV^-1], gaee [dimensionless], gaN [dimensionless]
  //                 fa [GeV], ma0 [eV], Tchi [MeV],
  //                 beta [dimensionless], thetai [dimensionless]
  DEFINEPARS(gagg,gaee,gaN,fa,ma0,Tchi,beta,thetai)
#undef MODEL

// QCD axion model
#define MODEL QCDAxion
#define PARENT GeneralALP
  START_MODEL
  // Units for these parameters are the same as for the GeneralALP.
  DEFINEPARS(fa,Tchi,beta,thetai)
  // Physical units: LambdaChi [MeV], EoverN [dimensionless], CaggQCD [dimensionless]
  //                 Caee [dimensionless], Caee [dimensionless], CaN [dimensionless]
  DEFINEPARS(LambdaChi,EoverN,CaggQCD,Caee,CaN)
  // Translation to parent, all defined in Axions.cpp:
  INTERPRET_AS_PARENT_FUNCTION(QCDAxion_to_GeneralALP)
#undef PARENT
#undef MODEL

// KSVZ axion model
#define MODEL KSVZAxion
#define PARENT QCDAxion
  START_MODEL
  // Units for these parameters are the same as for the QCDAxion.
  DEFINEPARS(fa,Tchi,beta,thetai,LambdaChi,EoverN,CaggQCD,CaN)
  INTERPRET_AS_PARENT_FUNCTION(KSVZAxion_to_QCDAxion)
#undef PARENT
#undef MODEL

// DFSZ-I axion model
#define MODEL DFSZAxion_I
#define PARENT QCDAxion
  START_MODEL
  // Units for these parameters are the same as for the QCDAxion.
  DEFINEPARS(fa,Tchi,beta,thetai,LambdaChi,EoverN,CaggQCD,CaN)
  // Physical units: tanbeta [dimensionless]
  DEFINEPARS(tanbeta)
  INTERPRET_AS_PARENT_FUNCTION(DFSZAxion_I_to_QCDAxion)
#undef PARENT
#undef MODEL

// DFSZ-II axion model
#define MODEL DFSZAxion_II
#define PARENT QCDAxion
  START_MODEL
  // Units for these parameters are the same as for the QCDAxion.
  DEFINEPARS(fa,Tchi,beta,thetai,LambdaChi,EoverN,CaggQCD,CaN)
  // Physical units: tanbeta [dimensionless]
  DEFINEPARS(tanbeta)
  INTERPRET_AS_PARENT_FUNCTION(DFSZAxion_II_to_QCDAxion)
#undef PARENT
#undef MODEL

// ConstantMassALP model with temperature-independent mass and QCD-axion-inspired couplings
#define MODEL ConstantMassALP
#define PARENT GeneralALP
  START_MODEL
  // Units for these parameters are the same as for the GeneralALP.
  DEFINEPARS(fa,thetai)
  // Physical units: Cagg [dimensionless], Caee [dimensionless], CaN [dimensionless], Lambda [MeV]
  DEFINEPARS(Cagg,Caee,CaN,Lambda)
  INTERPRET_AS_PARENT_FUNCTION(ConstantMassALP_to_GeneralALP)
#undef PARENT
#undef MODEL

// Nuisance parameters for the XENON1T Anomaly experiment 2020
#define MODEL XENON1T_NuisanceParameters
  START_MODEL
  // Physical units: delta_eff [dimensionless], delta_bkg [dimensionless], x_3H [mol/mol]
  DEFINEPARS(delta_eff,delta_bkg,x_3H)
#undef MODEL

// Nuisance parameters for the XENON1T Anomaly experiment 2020 (DM signal)
#define MODEL XENON1T_DM_NuisanceParameters
  START_MODEL
  // Physical units: eta [dimensionless]
  DEFINEPARS(eta)
#undef MODEL

#endif
