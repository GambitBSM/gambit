//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend for THDMC compact backend
///
///  *********************************************
///
///  Authors (add name and sate if you modify):
///
///  \author Filip Rajec
///  \date 2018 Sep
///
///  *********************************************

#include "gambit/Backends/frontend_macros.hpp"
#include "gambit/Backends/frontends/THDMC_compact_1_7_0.hpp"

// Convenience functions (definitions)
BE_NAMESPACE
{

}
END_BE_NAMESPACE

// Initialisation function (definition)
BE_INI_FUNCTION
{
  // retrive SMInputs dependency 
  // const SMInputs& sminputs = *Dep::SMINPUTS;
    
  // retrieve THDM_spectrum dependency
  const Spectrum& spec = *Dep::THDM_spectrum;

  unique_ptr<SubSpectrum> SM = spec.clone_LE(); // Copy "low-energy" SubSpectrum 
  unique_ptr<SubSpectrum> he =  spec.clone_HE(); // Copy "high-energy" SubSpectrum

  // const SMInputs& sminputs   = spec.get_SMInputs();

  double scale = *Param.at("QrunTo");
  if (scale > 0.0) {
    he -> RunToScale(scale);
  }

  int YukawaType = runOptions->getValueOrDef<int>(1, "YukawaType");

    // thes are are the running couplings
  double lambda_1 = he->get(Par::mass1,"lambda_1");
  double lambda_2 = he->get(Par::mass1,"lambda_2");
  double lambda_3 = he->get(Par::mass1, "lambda_3");
  double lambda_4 = he->get(Par::mass1, "lambda_4");
  double lambda_5 = he->get(Par::mass1, "lambda_5");
  double tan_beta = he->get(Par::dimensionless, "tanb");

  double lambda_6 = he->get(Par::mass1, "lambda_6");
  double lambda_7 = he->get(Par::mass1, "lambda_7");

  double m12_2 = he->get(Par::mass1,"m12_2");

  init();

  // set_alpha(1/(sminputs.alphainv));
  // set_alpha0(alpha0);
  // set_alpha_s(sminputs.alphaS);
  // set_GF(sminputs.GF);
  // set_MZ(SM->get(Par::Pole_Mass,"Z0"));
  // set_MW(SM->get(Par::Pole_Mass,"W+"));

  // set_lmass_pole(1,SM->get(Par::Pole_Mass,"e-_1"));
  // set_lmass_pole(2,SM->get(Par::Pole_Mass,"e-_2"));
  // set_lmass_pole(3,SM->get(Par::Pole_Mass,"e-_3"));

  // set_qmass_msbar(2,sminputs.mU); //u
  // set_qmass_msbar(1,sminputs.mD); //d
  // set_qmass_msbar(4,sminputs.mCmC); //c
  // set_qmass_msbar(3,sminputs.mS); //s
  // set_qmass_pole(6,SM->get(Par::Pole_Mass,"u_3")); //t
  // set_qmass_pole(5,SM->get(Par::Pole_Mass,"d_3")); //b

  // set_qmass_msbar(2,SM.get(Par::mass1,"u_1")); //u
  // set_qmass_msbar(1,SM.get(Par::mass1,"d_1")); //d
  // set_qmass_msbar(4,SM.get(Par::mass1,"u_2")); //c
  // set_qmass_msbar(3,SM.get(Par::mass1,"d_2")); //s

  // complex<double> CKMMatrix[2][2];
  // get_CKM_from_Wolfenstein_parameters(CKMMatrix, sminputs.CKM.lambda, sminputs.CKM.A, sminputs.CKM.rhobar, sminputs.CKM.etabar);
  // set_CKM(abs(CKMMatrix[0][0]), abs(CKMMatrix[0][1]), abs(CKMMatrix[0][2]), abs(CKMMatrix[1][0]), abs(CKMMatrix[1][1]),
          // abs(CKMMatrix[1][2]), abs(CKMMatrix[2][0]), abs(CKMMatrix[2][1]), abs(CKMMatrix[2][2]));

  // must be run after setting all elements
  // *** not currently supported by BOSSed 2HDMC backend ***
  // clear_lookup();

  set_param_gen(lambda_1, lambda_2, lambda_3, lambda_4, lambda_5, lambda_6, lambda_7, m12_2, tan_beta);
  set_yukawas_type(YukawaType);

}
END_BE_INI_FUNCTION

