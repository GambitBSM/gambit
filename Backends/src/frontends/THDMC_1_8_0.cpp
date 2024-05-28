//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend for 2HDMC 1.8.0 backend
///
///  *********************************************
///
///  Authors (add name and sate if you modify):
///
///  \author Filip Rajec
///  \date 2020 Jan
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@kit.edu)
///  \date 2021 Apr, 2024 May
///
///  *********************************************

#include "gambit/Backends/frontend_macros.hpp"
#include "gambit/Backends/frontends/THDMC_1_8_0.hpp"
#include "gambit/Utils/util_functions.hpp"

#include <algorithm>

BE_NAMESPACE
{

  void set_sm_spectrum_helper(THDMsafe& container, const SubSpectrum& he, const SubSpectrum& le, const SMInputs& sm)
  {
    // set thdmc's sm spectrum
    THDMC_1_8_0::SM* SM_object = container.obj.get_SM_pointer();
    double vev = he.get(Par::mass1, "vev");
    double GF = 1.0/(sqrt(2)*pow(vev,2.0));
    // double v2 = 1.0 / (sqrt(2.0) * sminputs.GF)
    SM_object->set_alpha(1/sm.alphainv);
    SM_object->set_alpha_s(sm.alphaS);
    SM_object->set_GF(GF);
    SM_object->set_MZ(le.get(Par::Pole_Mass, "Z0"));
    SM_object->set_MW(le.get(Par::Pole_Mass, "W+"));
    SM_object->set_lmass_pole(1,le.get(Par::Pole_Mass, "e-_1"));
    SM_object->set_lmass_pole(2,le.get(Par::Pole_Mass, "e-_2"));
    SM_object->set_lmass_pole(3,le.get(Par::Pole_Mass, "e-_3"));
    SM_object->set_qmass_msbar(1,le.get(Par::mass1, "d_1"));
    SM_object->set_qmass_msbar(3,sm.mS);
    SM_object->set_qmass_pole(5,le.get(Par::Pole_Mass, "d_3"));
    SM_object->set_qmass_msbar(2,le.get(Par::mass1, "u_1"));
    SM_object->set_qmass_msbar(4,sm.mCmC);
    SM_object->set_qmass_pole(6,le.get(Par::Pole_Mass, "u_3"));
  }

  // copy the gambit spectrum into thdmc's internal spectrum
  void setup_thdmc_spectrum(THDMsafe& container, const Spectrum& spec)
  {
    using namespace Utils;

    const SubSpectrum& he = spec.get_HE();
    const SubSpectrum& le = spec.get_LE();
    const SMInputs& sm = spec.get_SMInputs();
    const int yukawa_type = (int)spec.get(Par::dimensionless, "model_type");

    // set thdmc's thdm spectrum
    double vev = he.get(Par::mass1, "vev");
    double lam1 = he.get(Par::dimensionless, "lambda1");
    double lam2 = he.get(Par::dimensionless, "lambda2");
    double lam3 = he.get(Par::dimensionless, "lambda3");
    double lam4 = he.get(Par::dimensionless, "lambda4");
    double lam5 = he.get(Par::dimensionless, "lambda5");
    double lam6 = he.get(Par::dimensionless, "lambda6");
    double lam7 = he.get(Par::dimensionless, "lambda7");
    double m122 = he.get(Par::mass1, "m12_2");

    // TODO: should these be mass1??
    double mh = he.get(Par::Pole_Mass, "h0_1");
    double mH = he.get(Par::Pole_Mass, "h0_2");
    double mA = he.get(Par::Pole_Mass, "A0");
    double mC = he.get(Par::Pole_Mass, "H+");

    double alpha = he.get(Par::dimensionless, "alpha");
    double beta = he.get(Par::dimensionless, "beta");
    double sb = sin(beta), cb = cos(beta);
    double m222 = he.get(Par::mass1, "m22_2");

    if (!he.get(Par::dimensionless,"isIDM"))
      m222 = m122/tan(beta)-0.5*vev*vev*(lam2*sqr(sb)+(lam3+lam4+lam5)*sqr(cb)+lam6*sqr(cb)/tan(beta)+3.*lam7*sb*cb);

    double sba = sin(beta - alpha);

    container.obj.set_param_full(lam1,lam2,lam3,lam4,lam5,lam6,lam7,m222,m122,beta,mh,mH,mA,mC,sba);

    if (he.get(Par::dimensionless,"isIDM"))
    {
      if(abs(he.get(Par::dimensionless,"Yu1",3,3)) > 1e-10)
      {
        container.obj.set_yukawas_type(0);
      }
      else
      {
        container.obj.set_yukawas_type(1);
      }
    }
    else
    {
      // 2HDMC does not work with type III, set Yukawas manually in that case
      if(yukawa_type == TYPE_III)
      {
        const double cosb = cos(beta), sinb = sin(beta);
        complexd rhod[3][3], rhou[3][3], rhoe[3][3];

        for (int i=0; i<3; ++i)
        {
          for (int j=0; j<3; ++j)
          {
            complexd Yd1_ij ( he.get(Par::dimensionless,"Yd1",i+1,j+1), he.get(Par::dimensionless,"ImYd1",i+1,j+1) );
            complexd Yd2_ij ( he.get(Par::dimensionless,"Yd2",i+1,j+1), he.get(Par::dimensionless,"ImYd2",i+1,j+1) );
            complexd Yu1_ij ( he.get(Par::dimensionless,"Yu1",i+1,j+1), he.get(Par::dimensionless,"ImYu1",i+1,j+1) );
            complexd Yu2_ij ( he.get(Par::dimensionless,"Yu2",i+1,j+1), he.get(Par::dimensionless,"ImYu2",i+1,j+1) );
            complexd Ye1_ij ( he.get(Par::dimensionless,"Ye1",i+1,j+1), he.get(Par::dimensionless,"ImYe1",i+1,j+1) );
            complexd Ye2_ij ( he.get(Par::dimensionless,"Ye2",i+1,j+1), he.get(Par::dimensionless,"ImYe2",i+1,j+1) );

            rhod[i][j] = Yd2_ij*cosb - Yd1_ij*sinb;
            rhou[i][j] = Yu2_ij*cosb - Yu1_ij*sinb;
            rhoe[i][j] = Ye2_ij*cosb - Ye1_ij*sinb;
          }
        }

        container.obj.set_yukawas_down(rhod[0][0], rhod[1][1], rhod[2][2], rhod[0][1], rhod[0][2], rhod[1][2], rhod[1][0], rhod[2][0], rhod[2][1]);
        container.obj.set_yukawas_up(rhou[0][0], rhou[1][1], rhou[2][2], rhou[0][1], rhou[0][2], rhou[1][2], rhou[1][0], rhou[2][0], rhou[2][1]);
        container.obj.set_yukawas_lepton(rhoe[0][0], rhoe[1][1], rhoe[2][2], rhoe[0][1], rhoe[0][2], rhoe[1][2], rhoe[1][0], rhoe[2][0], rhoe[2][1]);
      }
      else
        container.obj.set_yukawas_type(yukawa_type);
    }

    // set thdmc's sm spectrum
    set_sm_spectrum_helper(container, he, le, sm);
  }

  // setup thdmc spectrum to get the most sm-like behaviour that is possible in the thdm
  void setup_thdmc_sm_like_spectrum(THDMsafe& container, const Spectrum& spec, double sm_like_higgs_mass)
  {
    const SubSpectrum& he = spec.get_HE();
    const SubSpectrum& le = spec.get_LE();
    const SMInputs& sm = spec.get_SMInputs();

    // set thdmc's thdm spectrum
    container.obj.set_param_sm(sm_like_higgs_mass);

    // set thdmc's sm spectrum
    set_sm_spectrum_helper(container, he, le, sm);
  }


}
END_BE_NAMESPACE

// Initialisation function (definition)
BE_INI_FUNCTION
{

}
END_BE_INI_FUNCTION
