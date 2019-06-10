//==========================================================================
// This file has been automatically generated for Pythia 8 by
// MadGraph5_aMC@NLO v. 2.3.2.2, 2015-09-06
// By the MadGraph5_aMC@NLO Development Team
// Visit launchpad.net/madgraph5 and amcatnlo.web.cern.ch
//==========================================================================

#include <iostream> 
#include "Parameters_GambitDemo_UFO.h"
#include "Pythia8/PythiaStdlib.h"

namespace Pythia8 
{

// Initialize static instance
Parameters_GambitDemo_UFO * Parameters_GambitDemo_UFO::instance = 0; 

// Function to get static instance - only one instance per program
Parameters_GambitDemo_UFO * Parameters_GambitDemo_UFO::getInstance()
{
  if (instance == 0)
    instance = new Parameters_GambitDemo_UFO(); 

  return instance; 
}

void Parameters_GambitDemo_UFO::setIndependentParameters(ParticleData * & pd,
    Couplings * & csm, SusyLesHouches * & slhaPtr)
{
  mdl_Wuv = pd->mWidth(9000005); 
  mdl_WH = pd->mWidth(25); 
  mdl_WT = pd->mWidth(6); 
  mdl_WW = pd->mWidth(24); 
  mdl_WZ = pd->mWidth(23); 
  mdl_Mp1 = pd->m0(51); 
  mdl_Muv = pd->m0(9000005); 
  mdl_MH = pd->m0(25); 
  mdl_MB = pd->m0(5); 
  mdl_MS = pd->m0(3); 
  mdl_MD = pd->m0(1); 
  mdl_MT = pd->m0(6); 
  mdl_MC = pd->m0(4); 
  mdl_MU = pd->m0(2); 
  mdl_MTA = pd->m0(15); 
  mdl_MMU = pd->m0(13); 
  mdl_Me = pd->m0(11); 
  mdl_MZ = pd->m0(23); 
  if( !slhaPtr->getEntry<double> ("frblock", 2, mdl_lam1))
  {
    cout <<  "Warning, setting mdl_lam1 to 1.000000e+00" << endl; 
    mdl_lam1 = 1.000000e+00; 
  }
  if( !slhaPtr->getEntry<double> ("frblock", 1, mdl_MM1))
  {
    cout <<  "Warning, setting mdl_MM1 to 2.000000e+02" << endl; 
    mdl_MM1 = 2.000000e+02; 
  }
  mdl_ymtau = pd->mRun(15, pd->m0(24)); 
  mdl_ymm = pd->mRun(13, pd->m0(24)); 
  mdl_yme = pd->mRun(11, pd->m0(24)); 
  mdl_ymt = pd->mRun(6, pd->m0(24)); 
  mdl_ymb = pd->mRun(5, pd->m0(24)); 
  mdl_ymc = pd->mRun(4, pd->m0(24)); 
  mdl_yms = pd->mRun(3, pd->m0(24)); 
  mdl_ymup = pd->mRun(2, pd->m0(24)); 
  mdl_ymdo = pd->mRun(1, pd->m0(24)); 
  mdl_Gf = M_PI * csm->alphaEM(pow(pd->m0(23), 2)) * pow(pd->m0(23),
      2)/(sqrt(2.) * pow(pd->m0(24), 2) * (pow(pd->m0(23), 2) - pow(pd->m0(24),
      2)));
  aEWM1 = 1./csm->alphaEM(pow(pd->m0(23), 2)); 
  mdl_cabi = csm->VCKMgen(1, 2); 
  ZERO = 0.; 
  mdl_cos__cabi = cos(mdl_cabi); 
  mdl_CKM1x1 = mdl_cos__cabi; 
  mdl_sin__cabi = sin(mdl_cabi); 
  mdl_CKM1x2 = mdl_sin__cabi; 
  mdl_CKM1x3 = 0.; 
  mdl_CKM2x1 = -mdl_sin__cabi; 
  mdl_CKM2x2 = mdl_cos__cabi; 
  mdl_CKM2x3 = 0.; 
  mdl_CKM3x1 = 0.; 
  mdl_CKM3x2 = 0.; 
  mdl_CKM3x3 = 1.; 
  mdl_MZ__exp__2 = pow(mdl_MZ, 2.); 
  mdl_MZ__exp__4 = pow(mdl_MZ, 4.); 
  mdl_sqrt__2 = sqrt(2.); 
  mdl_MH__exp__2 = pow(mdl_MH, 2.); 
  mdl_conjg__CKM1x1 = conj(mdl_CKM1x1); 
  mdl_conjg__CKM2x1 = conj(mdl_CKM2x1); 
  mdl_conjg__CKM3x1 = conj(mdl_CKM3x1); 
  mdl_conjg__CKM1x2 = conj(mdl_CKM1x2); 
  mdl_conjg__CKM2x2 = conj(mdl_CKM2x2); 
  mdl_conjg__CKM3x2 = conj(mdl_CKM3x2); 
  mdl_conjg__CKM1x3 = conj(mdl_CKM1x3); 
  mdl_conjg__CKM2x3 = conj(mdl_CKM2x3); 
  mdl_conjg__CKM3x3 = conj(mdl_CKM3x3); 
  mdl_complexi = std::complex<double> (0., 1.); 
  mdl_aEW = 1./aEWM1; 
  mdl_MW = sqrt(mdl_MZ__exp__2/2. + sqrt(mdl_MZ__exp__4/4. - (mdl_aEW * M_PI *
      mdl_MZ__exp__2)/(mdl_Gf * mdl_sqrt__2)));
  mdl_sqrt__aEW = sqrt(mdl_aEW); 
  mdl_ee = 2. * mdl_sqrt__aEW * sqrt(M_PI); 
  mdl_MW__exp__2 = pow(mdl_MW, 2.); 
  mdl_sw2 = 1. - mdl_MW__exp__2/mdl_MZ__exp__2; 
  mdl_cw = sqrt(1. - mdl_sw2); 
  mdl_sqrt__sw2 = sqrt(mdl_sw2); 
  mdl_sw = mdl_sqrt__sw2; 
  mdl_g1 = mdl_ee/mdl_cw; 
  mdl_gw = mdl_ee/mdl_sw; 
  mdl_vev = (2. * mdl_MW * mdl_sw)/mdl_ee; 
  mdl_vev__exp__2 = pow(mdl_vev, 2.); 
  mdl_lam = mdl_MH__exp__2/(2. * mdl_vev__exp__2); 
  mdl_yb = (mdl_ymb * mdl_sqrt__2)/mdl_vev; 
  mdl_yc = (mdl_ymc * mdl_sqrt__2)/mdl_vev; 
  mdl_ydo = (mdl_ymdo * mdl_sqrt__2)/mdl_vev; 
  mdl_ye = (mdl_yme * mdl_sqrt__2)/mdl_vev; 
  mdl_ym = (mdl_ymm * mdl_sqrt__2)/mdl_vev; 
  mdl_ys = (mdl_yms * mdl_sqrt__2)/mdl_vev; 
  mdl_yt = (mdl_ymt * mdl_sqrt__2)/mdl_vev; 
  mdl_ytau = (mdl_ymtau * mdl_sqrt__2)/mdl_vev; 
  mdl_yup = (mdl_ymup * mdl_sqrt__2)/mdl_vev; 
  mdl_muH = sqrt(mdl_lam * mdl_vev__exp__2); 
  mdl_I1a11 = mdl_ydo * mdl_conjg__CKM1x1; 
  mdl_I1a12 = mdl_ydo * mdl_conjg__CKM2x1; 
  mdl_I1a13 = mdl_ydo * mdl_conjg__CKM3x1; 
  mdl_I1a21 = mdl_ys * mdl_conjg__CKM1x2; 
  mdl_I1a22 = mdl_ys * mdl_conjg__CKM2x2; 
  mdl_I1a23 = mdl_ys * mdl_conjg__CKM3x2; 
  mdl_I1a31 = mdl_yb * mdl_conjg__CKM1x3; 
  mdl_I1a32 = mdl_yb * mdl_conjg__CKM2x3; 
  mdl_I1a33 = mdl_yb * mdl_conjg__CKM3x3; 
  mdl_I2a11 = mdl_yup * mdl_conjg__CKM1x1; 
  mdl_I2a12 = mdl_yc * mdl_conjg__CKM2x1; 
  mdl_I2a13 = mdl_yt * mdl_conjg__CKM3x1; 
  mdl_I2a21 = mdl_yup * mdl_conjg__CKM1x2; 
  mdl_I2a22 = mdl_yc * mdl_conjg__CKM2x2; 
  mdl_I2a23 = mdl_yt * mdl_conjg__CKM3x2; 
  mdl_I2a31 = mdl_yup * mdl_conjg__CKM1x3; 
  mdl_I2a32 = mdl_yc * mdl_conjg__CKM2x3; 
  mdl_I2a33 = mdl_yt * mdl_conjg__CKM3x3; 
  mdl_I3a11 = mdl_CKM1x1 * mdl_yup; 
  mdl_I3a12 = mdl_CKM1x2 * mdl_yup; 
  mdl_I3a13 = mdl_CKM1x3 * mdl_yup; 
  mdl_I3a21 = mdl_CKM2x1 * mdl_yc; 
  mdl_I3a22 = mdl_CKM2x2 * mdl_yc; 
  mdl_I3a23 = mdl_CKM2x3 * mdl_yc; 
  mdl_I3a31 = mdl_CKM3x1 * mdl_yt; 
  mdl_I3a32 = mdl_CKM3x2 * mdl_yt; 
  mdl_I3a33 = mdl_CKM3x3 * mdl_yt; 
  mdl_I4a11 = mdl_CKM1x1 * mdl_ydo; 
  mdl_I4a12 = mdl_CKM1x2 * mdl_ys; 
  mdl_I4a13 = mdl_CKM1x3 * mdl_yb; 
  mdl_I4a21 = mdl_CKM2x1 * mdl_ydo; 
  mdl_I4a22 = mdl_CKM2x2 * mdl_ys; 
  mdl_I4a23 = mdl_CKM2x3 * mdl_yb; 
  mdl_I4a31 = mdl_CKM3x1 * mdl_ydo; 
  mdl_I4a32 = mdl_CKM3x2 * mdl_ys; 
  mdl_I4a33 = mdl_CKM3x3 * mdl_yb; 
  mdl_ee__exp__2 = pow(mdl_ee, 2.); 
  mdl_sw__exp__2 = pow(mdl_sw, 2.); 
  mdl_cw__exp__2 = pow(mdl_cw, 2.); 
}
void Parameters_GambitDemo_UFO::setIndependentCouplings()
{
  GC_1 = -(mdl_ee * mdl_complexi)/3.; 
  GC_2 = (2. * mdl_ee * mdl_complexi)/3.; 
  GC_3 = -(mdl_ee * mdl_complexi); 
  GC_4 = mdl_ee * mdl_complexi; 
  GC_5 = mdl_ee__exp__2 * mdl_complexi; 
  GC_6 = 2. * mdl_ee__exp__2 * mdl_complexi; 
  GC_7 = -mdl_ee__exp__2/(2. * mdl_cw); 
  GC_8 = (mdl_ee__exp__2 * mdl_complexi)/(2. * mdl_cw); 
  GC_9 = mdl_ee__exp__2/(2. * mdl_cw); 
  GC_13 = mdl_I1a11; 
  GC_14 = mdl_I1a12; 
  GC_15 = mdl_I1a13; 
  GC_16 = mdl_I1a21; 
  GC_17 = mdl_I1a22; 
  GC_18 = mdl_I1a23; 
  GC_19 = mdl_I1a31; 
  GC_20 = mdl_I1a32; 
  GC_21 = mdl_I1a33; 
  GC_22 = -mdl_I2a11; 
  GC_23 = -mdl_I2a12; 
  GC_24 = -mdl_I2a13; 
  GC_25 = -mdl_I2a21; 
  GC_26 = -mdl_I2a22; 
  GC_27 = -mdl_I2a23; 
  GC_28 = -mdl_I2a31; 
  GC_29 = -mdl_I2a32; 
  GC_30 = -mdl_I2a33; 
  GC_31 = mdl_I3a11; 
  GC_32 = mdl_I3a12; 
  GC_33 = mdl_I3a13; 
  GC_34 = mdl_I3a21; 
  GC_35 = mdl_I3a22; 
  GC_36 = mdl_I3a23; 
  GC_37 = mdl_I3a31; 
  GC_38 = mdl_I3a32; 
  GC_39 = mdl_I3a33; 
  GC_40 = -mdl_I4a11; 
  GC_41 = -mdl_I4a12; 
  GC_42 = -mdl_I4a13; 
  GC_43 = -mdl_I4a21; 
  GC_44 = -mdl_I4a22; 
  GC_45 = -mdl_I4a23; 
  GC_46 = -mdl_I4a31; 
  GC_47 = -mdl_I4a32; 
  GC_48 = -mdl_I4a33; 
  GC_49 = -2. * mdl_complexi * mdl_lam; 
  GC_50 = -4. * mdl_complexi * mdl_lam; 
  GC_51 = -6. * mdl_complexi * mdl_lam; 
  GC_53 = (mdl_ee__exp__2 * mdl_complexi)/(2. * mdl_sw__exp__2); 
  GC_54 = -((mdl_ee__exp__2 * mdl_complexi)/mdl_sw__exp__2); 
  GC_55 = (mdl_cw__exp__2 * mdl_ee__exp__2 * mdl_complexi)/mdl_sw__exp__2; 
  GC_56 = -mdl_ee/(2. * mdl_sw); 
  GC_57 = -(mdl_ee * mdl_complexi)/(2. * mdl_sw); 
  GC_58 = (mdl_ee * mdl_complexi)/(2. * mdl_sw); 
  GC_59 = (mdl_ee * mdl_complexi)/(mdl_sw * mdl_sqrt__2); 
  GC_60 = (mdl_CKM1x1 * mdl_ee * mdl_complexi)/(mdl_sw * mdl_sqrt__2); 
  GC_61 = (mdl_CKM1x2 * mdl_ee * mdl_complexi)/(mdl_sw * mdl_sqrt__2); 
  GC_62 = (mdl_CKM1x3 * mdl_ee * mdl_complexi)/(mdl_sw * mdl_sqrt__2); 
  GC_63 = (mdl_CKM2x1 * mdl_ee * mdl_complexi)/(mdl_sw * mdl_sqrt__2); 
  GC_64 = (mdl_CKM2x2 * mdl_ee * mdl_complexi)/(mdl_sw * mdl_sqrt__2); 
  GC_65 = (mdl_CKM2x3 * mdl_ee * mdl_complexi)/(mdl_sw * mdl_sqrt__2); 
  GC_66 = (mdl_CKM3x1 * mdl_ee * mdl_complexi)/(mdl_sw * mdl_sqrt__2); 
  GC_67 = (mdl_CKM3x2 * mdl_ee * mdl_complexi)/(mdl_sw * mdl_sqrt__2); 
  GC_68 = (mdl_CKM3x3 * mdl_ee * mdl_complexi)/(mdl_sw * mdl_sqrt__2); 
  GC_69 = -(mdl_cw * mdl_ee * mdl_complexi)/(2. * mdl_sw); 
  GC_70 = (mdl_cw * mdl_ee * mdl_complexi)/(2. * mdl_sw); 
  GC_71 = -((mdl_cw * mdl_ee * mdl_complexi)/mdl_sw); 
  GC_72 = (mdl_cw * mdl_ee * mdl_complexi)/mdl_sw; 
  GC_73 = -mdl_ee__exp__2/(2. * mdl_sw); 
  GC_74 = -(mdl_ee__exp__2 * mdl_complexi)/(2. * mdl_sw); 
  GC_75 = mdl_ee__exp__2/(2. * mdl_sw); 
  GC_76 = (-2. * mdl_cw * mdl_ee__exp__2 * mdl_complexi)/mdl_sw; 
  GC_77 = -(mdl_ee * mdl_complexi * mdl_sw)/(6. * mdl_cw); 
  GC_78 = (mdl_ee * mdl_complexi * mdl_sw)/(2. * mdl_cw); 
  GC_79 = -(mdl_cw * mdl_ee)/(2. * mdl_sw) - (mdl_ee * mdl_sw)/(2. * mdl_cw); 
  GC_80 = -(mdl_cw * mdl_ee * mdl_complexi)/(2. * mdl_sw) + (mdl_ee *
      mdl_complexi * mdl_sw)/(2. * mdl_cw);
  GC_81 = (mdl_cw * mdl_ee * mdl_complexi)/(2. * mdl_sw) + (mdl_ee *
      mdl_complexi * mdl_sw)/(2. * mdl_cw);
  GC_82 = (mdl_cw * mdl_ee__exp__2 * mdl_complexi)/mdl_sw - (mdl_ee__exp__2 *
      mdl_complexi * mdl_sw)/mdl_cw;
  GC_83 = -(mdl_ee__exp__2 * mdl_complexi) + (mdl_cw__exp__2 * mdl_ee__exp__2 *
      mdl_complexi)/(2. * mdl_sw__exp__2) + (mdl_ee__exp__2 * mdl_complexi *
      mdl_sw__exp__2)/(2. * mdl_cw__exp__2);
  GC_84 = mdl_ee__exp__2 * mdl_complexi + (mdl_cw__exp__2 * mdl_ee__exp__2 *
      mdl_complexi)/(2. * mdl_sw__exp__2) + (mdl_ee__exp__2 * mdl_complexi *
      mdl_sw__exp__2)/(2. * mdl_cw__exp__2);
  GC_85 = -(mdl_ee__exp__2 * mdl_vev)/(2. * mdl_cw); 
  GC_86 = (mdl_ee__exp__2 * mdl_vev)/(2. * mdl_cw); 
  GC_87 = -2. * mdl_complexi * mdl_lam * mdl_vev; 
  GC_88 = -6. * mdl_complexi * mdl_lam * mdl_vev; 
  GC_89 = -(mdl_ee__exp__2 * mdl_vev)/(4. * mdl_sw__exp__2); 
  GC_90 = -(mdl_ee__exp__2 * mdl_complexi * mdl_vev)/(4. * mdl_sw__exp__2); 
  GC_91 = (mdl_ee__exp__2 * mdl_complexi * mdl_vev)/(2. * mdl_sw__exp__2); 
  GC_92 = (mdl_ee__exp__2 * mdl_vev)/(4. * mdl_sw__exp__2); 
  GC_93 = -(mdl_ee__exp__2 * mdl_vev)/(2. * mdl_sw); 
  GC_94 = (mdl_ee__exp__2 * mdl_vev)/(2. * mdl_sw); 
  GC_95 = -(mdl_ee__exp__2 * mdl_vev)/(4. * mdl_cw) - (mdl_cw * mdl_ee__exp__2
      * mdl_vev)/(4. * mdl_sw__exp__2);
  GC_96 = (mdl_ee__exp__2 * mdl_vev)/(4. * mdl_cw) - (mdl_cw * mdl_ee__exp__2 *
      mdl_vev)/(4. * mdl_sw__exp__2);
  GC_97 = -(mdl_ee__exp__2 * mdl_vev)/(4. * mdl_cw) + (mdl_cw * mdl_ee__exp__2
      * mdl_vev)/(4. * mdl_sw__exp__2);
  GC_98 = (mdl_ee__exp__2 * mdl_vev)/(4. * mdl_cw) + (mdl_cw * mdl_ee__exp__2 *
      mdl_vev)/(4. * mdl_sw__exp__2);
  GC_99 = -(mdl_ee__exp__2 * mdl_complexi * mdl_vev)/2. - (mdl_cw__exp__2 *
      mdl_ee__exp__2 * mdl_complexi * mdl_vev)/(4. * mdl_sw__exp__2) -
      (mdl_ee__exp__2 * mdl_complexi * mdl_sw__exp__2 * mdl_vev)/(4. *
      mdl_cw__exp__2);
  GC_100 = mdl_ee__exp__2 * mdl_complexi * mdl_vev + (mdl_cw__exp__2 *
      mdl_ee__exp__2 * mdl_complexi * mdl_vev)/(2. * mdl_sw__exp__2) +
      (mdl_ee__exp__2 * mdl_complexi * mdl_sw__exp__2 * mdl_vev)/(2. *
      mdl_cw__exp__2);
  GC_101 = -(mdl_yb/mdl_sqrt__2); 
  GC_102 = -((mdl_complexi * mdl_yb)/mdl_sqrt__2); 
  GC_103 = -((mdl_complexi * mdl_yc)/mdl_sqrt__2); 
  GC_104 = mdl_yc/mdl_sqrt__2; 
  GC_105 = -(mdl_ydo/mdl_sqrt__2); 
  GC_106 = -((mdl_complexi * mdl_ydo)/mdl_sqrt__2); 
  GC_107 = -mdl_ye; 
  GC_108 = mdl_ye; 
  GC_109 = -(mdl_ye/mdl_sqrt__2); 
  GC_110 = -((mdl_complexi * mdl_ye)/mdl_sqrt__2); 
  GC_111 = -mdl_ym; 
  GC_112 = mdl_ym; 
  GC_113 = -(mdl_ym/mdl_sqrt__2); 
  GC_114 = -((mdl_complexi * mdl_ym)/mdl_sqrt__2); 
  GC_115 = -(mdl_ys/mdl_sqrt__2); 
  GC_116 = -((mdl_complexi * mdl_ys)/mdl_sqrt__2); 
  GC_117 = -((mdl_complexi * mdl_yt)/mdl_sqrt__2); 
  GC_118 = mdl_yt/mdl_sqrt__2; 
  GC_119 = -mdl_ytau; 
  GC_120 = mdl_ytau; 
  GC_121 = -(mdl_ytau/mdl_sqrt__2); 
  GC_122 = -((mdl_complexi * mdl_ytau)/mdl_sqrt__2); 
  GC_123 = -((mdl_complexi * mdl_yup)/mdl_sqrt__2); 
  GC_124 = mdl_yup/mdl_sqrt__2; 
  GC_125 = (mdl_ee * mdl_complexi * mdl_conjg__CKM1x1)/(mdl_sw * mdl_sqrt__2); 
  GC_126 = (mdl_ee * mdl_complexi * mdl_conjg__CKM1x2)/(mdl_sw * mdl_sqrt__2); 
  GC_127 = (mdl_ee * mdl_complexi * mdl_conjg__CKM1x3)/(mdl_sw * mdl_sqrt__2); 
  GC_128 = (mdl_ee * mdl_complexi * mdl_conjg__CKM2x1)/(mdl_sw * mdl_sqrt__2); 
  GC_129 = (mdl_ee * mdl_complexi * mdl_conjg__CKM2x2)/(mdl_sw * mdl_sqrt__2); 
  GC_130 = (mdl_ee * mdl_complexi * mdl_conjg__CKM2x3)/(mdl_sw * mdl_sqrt__2); 
  GC_131 = (mdl_ee * mdl_complexi * mdl_conjg__CKM3x1)/(mdl_sw * mdl_sqrt__2); 
  GC_132 = (mdl_ee * mdl_complexi * mdl_conjg__CKM3x2)/(mdl_sw * mdl_sqrt__2); 
  GC_133 = (mdl_ee * mdl_complexi * mdl_conjg__CKM3x3)/(mdl_sw * mdl_sqrt__2); 
  GC_52 = mdl_complexi * mdl_lam1; 
}
void Parameters_GambitDemo_UFO::setDependentParameters(ParticleData * & pd,
    Couplings * & csm, SusyLesHouches * & slhaPtr, double alpS)
{
  aS = alpS; 
  mdl_sqrt__aS = sqrt(aS); 
  G = 2. * mdl_sqrt__aS * sqrt(M_PI); 
  mdl_G__exp__2 = pow(G, 2.); 
}
void Parameters_GambitDemo_UFO::setDependentCouplings()
{
  GC_12 = mdl_complexi * mdl_G__exp__2; 
  GC_11 = mdl_complexi * G; 
  GC_10 = -G; 
}

// Routines for printing out parameters
void Parameters_GambitDemo_UFO::printIndependentParameters()
{
  cout <<  "GambitDemo_UFO model parameters independent of event kinematics:"
      << endl;
  cout << setw(20) <<  "mdl_Wuv " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_Wuv << endl;
  cout << setw(20) <<  "mdl_WH " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_WH << endl;
  cout << setw(20) <<  "mdl_WT " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_WT << endl;
  cout << setw(20) <<  "mdl_WW " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_WW << endl;
  cout << setw(20) <<  "mdl_WZ " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_WZ << endl;
  cout << setw(20) <<  "mdl_Mp1 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_Mp1 << endl;
  cout << setw(20) <<  "mdl_Muv " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_Muv << endl;
  cout << setw(20) <<  "mdl_MH " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_MH << endl;
  cout << setw(20) <<  "mdl_MB " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_MB << endl;
  cout << setw(20) <<  "mdl_MS " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_MS << endl;
  cout << setw(20) <<  "mdl_MD " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_MD << endl;
  cout << setw(20) <<  "mdl_MT " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_MT << endl;
  cout << setw(20) <<  "mdl_MC " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_MC << endl;
  cout << setw(20) <<  "mdl_MU " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_MU << endl;
  cout << setw(20) <<  "mdl_MTA " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_MTA << endl;
  cout << setw(20) <<  "mdl_MMU " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_MMU << endl;
  cout << setw(20) <<  "mdl_Me " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_Me << endl;
  cout << setw(20) <<  "mdl_MZ " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_MZ << endl;
  cout << setw(20) <<  "mdl_lam1 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_lam1 << endl;
  cout << setw(20) <<  "mdl_MM1 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_MM1 << endl;
  cout << setw(20) <<  "mdl_ymtau " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_ymtau << endl;
  cout << setw(20) <<  "mdl_ymm " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_ymm << endl;
  cout << setw(20) <<  "mdl_yme " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_yme << endl;
  cout << setw(20) <<  "mdl_ymt " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_ymt << endl;
  cout << setw(20) <<  "mdl_ymb " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_ymb << endl;
  cout << setw(20) <<  "mdl_ymc " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_ymc << endl;
  cout << setw(20) <<  "mdl_yms " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_yms << endl;
  cout << setw(20) <<  "mdl_ymup " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_ymup << endl;
  cout << setw(20) <<  "mdl_ymdo " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_ymdo << endl;
  cout << setw(20) <<  "mdl_Gf " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_Gf << endl;
  cout << setw(20) <<  "aEWM1 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << aEWM1 << endl;
  cout << setw(20) <<  "mdl_cabi " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_cabi << endl;
  cout << setw(20) <<  "ZERO " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << ZERO << endl;
  cout << setw(20) <<  "mdl_cos__cabi " <<  "= " <<
      setiosflags(ios::scientific) << setw(10) << mdl_cos__cabi << endl;
  cout << setw(20) <<  "mdl_CKM1x1 " <<  "= " << setiosflags(ios::scientific)
      << setw(10) << mdl_CKM1x1 << endl;
  cout << setw(20) <<  "mdl_sin__cabi " <<  "= " <<
      setiosflags(ios::scientific) << setw(10) << mdl_sin__cabi << endl;
  cout << setw(20) <<  "mdl_CKM1x2 " <<  "= " << setiosflags(ios::scientific)
      << setw(10) << mdl_CKM1x2 << endl;
  cout << setw(20) <<  "mdl_CKM1x3 " <<  "= " << setiosflags(ios::scientific)
      << setw(10) << mdl_CKM1x3 << endl;
  cout << setw(20) <<  "mdl_CKM2x1 " <<  "= " << setiosflags(ios::scientific)
      << setw(10) << mdl_CKM2x1 << endl;
  cout << setw(20) <<  "mdl_CKM2x2 " <<  "= " << setiosflags(ios::scientific)
      << setw(10) << mdl_CKM2x2 << endl;
  cout << setw(20) <<  "mdl_CKM2x3 " <<  "= " << setiosflags(ios::scientific)
      << setw(10) << mdl_CKM2x3 << endl;
  cout << setw(20) <<  "mdl_CKM3x1 " <<  "= " << setiosflags(ios::scientific)
      << setw(10) << mdl_CKM3x1 << endl;
  cout << setw(20) <<  "mdl_CKM3x2 " <<  "= " << setiosflags(ios::scientific)
      << setw(10) << mdl_CKM3x2 << endl;
  cout << setw(20) <<  "mdl_CKM3x3 " <<  "= " << setiosflags(ios::scientific)
      << setw(10) << mdl_CKM3x3 << endl;
  cout << setw(20) <<  "mdl_MZ__exp__2 " <<  "= " <<
      setiosflags(ios::scientific) << setw(10) << mdl_MZ__exp__2 << endl;
  cout << setw(20) <<  "mdl_MZ__exp__4 " <<  "= " <<
      setiosflags(ios::scientific) << setw(10) << mdl_MZ__exp__4 << endl;
  cout << setw(20) <<  "mdl_sqrt__2 " <<  "= " << setiosflags(ios::scientific)
      << setw(10) << mdl_sqrt__2 << endl;
  cout << setw(20) <<  "mdl_MH__exp__2 " <<  "= " <<
      setiosflags(ios::scientific) << setw(10) << mdl_MH__exp__2 << endl;
  cout << setw(20) <<  "mdl_conjg__CKM1x1 " <<  "= " <<
      setiosflags(ios::scientific) << setw(10) << mdl_conjg__CKM1x1 << endl;
  cout << setw(20) <<  "mdl_conjg__CKM2x1 " <<  "= " <<
      setiosflags(ios::scientific) << setw(10) << mdl_conjg__CKM2x1 << endl;
  cout << setw(20) <<  "mdl_conjg__CKM3x1 " <<  "= " <<
      setiosflags(ios::scientific) << setw(10) << mdl_conjg__CKM3x1 << endl;
  cout << setw(20) <<  "mdl_conjg__CKM1x2 " <<  "= " <<
      setiosflags(ios::scientific) << setw(10) << mdl_conjg__CKM1x2 << endl;
  cout << setw(20) <<  "mdl_conjg__CKM2x2 " <<  "= " <<
      setiosflags(ios::scientific) << setw(10) << mdl_conjg__CKM2x2 << endl;
  cout << setw(20) <<  "mdl_conjg__CKM3x2 " <<  "= " <<
      setiosflags(ios::scientific) << setw(10) << mdl_conjg__CKM3x2 << endl;
  cout << setw(20) <<  "mdl_conjg__CKM1x3 " <<  "= " <<
      setiosflags(ios::scientific) << setw(10) << mdl_conjg__CKM1x3 << endl;
  cout << setw(20) <<  "mdl_conjg__CKM2x3 " <<  "= " <<
      setiosflags(ios::scientific) << setw(10) << mdl_conjg__CKM2x3 << endl;
  cout << setw(20) <<  "mdl_conjg__CKM3x3 " <<  "= " <<
      setiosflags(ios::scientific) << setw(10) << mdl_conjg__CKM3x3 << endl;
  cout << setw(20) <<  "mdl_complexi " <<  "= " << setiosflags(ios::scientific)
      << setw(10) << mdl_complexi << endl;
  cout << setw(20) <<  "mdl_aEW " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_aEW << endl;
  cout << setw(20) <<  "mdl_MW " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_MW << endl;
  cout << setw(20) <<  "mdl_sqrt__aEW " <<  "= " <<
      setiosflags(ios::scientific) << setw(10) << mdl_sqrt__aEW << endl;
  cout << setw(20) <<  "mdl_ee " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_ee << endl;
  cout << setw(20) <<  "mdl_MW__exp__2 " <<  "= " <<
      setiosflags(ios::scientific) << setw(10) << mdl_MW__exp__2 << endl;
  cout << setw(20) <<  "mdl_sw2 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_sw2 << endl;
  cout << setw(20) <<  "mdl_cw " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_cw << endl;
  cout << setw(20) <<  "mdl_sqrt__sw2 " <<  "= " <<
      setiosflags(ios::scientific) << setw(10) << mdl_sqrt__sw2 << endl;
  cout << setw(20) <<  "mdl_sw " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_sw << endl;
  cout << setw(20) <<  "mdl_g1 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_g1 << endl;
  cout << setw(20) <<  "mdl_gw " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_gw << endl;
  cout << setw(20) <<  "mdl_vev " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_vev << endl;
  cout << setw(20) <<  "mdl_vev__exp__2 " <<  "= " <<
      setiosflags(ios::scientific) << setw(10) << mdl_vev__exp__2 << endl;
  cout << setw(20) <<  "mdl_lam " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_lam << endl;
  cout << setw(20) <<  "mdl_yb " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_yb << endl;
  cout << setw(20) <<  "mdl_yc " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_yc << endl;
  cout << setw(20) <<  "mdl_ydo " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_ydo << endl;
  cout << setw(20) <<  "mdl_ye " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_ye << endl;
  cout << setw(20) <<  "mdl_ym " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_ym << endl;
  cout << setw(20) <<  "mdl_ys " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_ys << endl;
  cout << setw(20) <<  "mdl_yt " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_yt << endl;
  cout << setw(20) <<  "mdl_ytau " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_ytau << endl;
  cout << setw(20) <<  "mdl_yup " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_yup << endl;
  cout << setw(20) <<  "mdl_muH " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_muH << endl;
  cout << setw(20) <<  "mdl_I1a11 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_I1a11 << endl;
  cout << setw(20) <<  "mdl_I1a12 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_I1a12 << endl;
  cout << setw(20) <<  "mdl_I1a13 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_I1a13 << endl;
  cout << setw(20) <<  "mdl_I1a21 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_I1a21 << endl;
  cout << setw(20) <<  "mdl_I1a22 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_I1a22 << endl;
  cout << setw(20) <<  "mdl_I1a23 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_I1a23 << endl;
  cout << setw(20) <<  "mdl_I1a31 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_I1a31 << endl;
  cout << setw(20) <<  "mdl_I1a32 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_I1a32 << endl;
  cout << setw(20) <<  "mdl_I1a33 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_I1a33 << endl;
  cout << setw(20) <<  "mdl_I2a11 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_I2a11 << endl;
  cout << setw(20) <<  "mdl_I2a12 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_I2a12 << endl;
  cout << setw(20) <<  "mdl_I2a13 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_I2a13 << endl;
  cout << setw(20) <<  "mdl_I2a21 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_I2a21 << endl;
  cout << setw(20) <<  "mdl_I2a22 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_I2a22 << endl;
  cout << setw(20) <<  "mdl_I2a23 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_I2a23 << endl;
  cout << setw(20) <<  "mdl_I2a31 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_I2a31 << endl;
  cout << setw(20) <<  "mdl_I2a32 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_I2a32 << endl;
  cout << setw(20) <<  "mdl_I2a33 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_I2a33 << endl;
  cout << setw(20) <<  "mdl_I3a11 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_I3a11 << endl;
  cout << setw(20) <<  "mdl_I3a12 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_I3a12 << endl;
  cout << setw(20) <<  "mdl_I3a13 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_I3a13 << endl;
  cout << setw(20) <<  "mdl_I3a21 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_I3a21 << endl;
  cout << setw(20) <<  "mdl_I3a22 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_I3a22 << endl;
  cout << setw(20) <<  "mdl_I3a23 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_I3a23 << endl;
  cout << setw(20) <<  "mdl_I3a31 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_I3a31 << endl;
  cout << setw(20) <<  "mdl_I3a32 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_I3a32 << endl;
  cout << setw(20) <<  "mdl_I3a33 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_I3a33 << endl;
  cout << setw(20) <<  "mdl_I4a11 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_I4a11 << endl;
  cout << setw(20) <<  "mdl_I4a12 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_I4a12 << endl;
  cout << setw(20) <<  "mdl_I4a13 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_I4a13 << endl;
  cout << setw(20) <<  "mdl_I4a21 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_I4a21 << endl;
  cout << setw(20) <<  "mdl_I4a22 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_I4a22 << endl;
  cout << setw(20) <<  "mdl_I4a23 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_I4a23 << endl;
  cout << setw(20) <<  "mdl_I4a31 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_I4a31 << endl;
  cout << setw(20) <<  "mdl_I4a32 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_I4a32 << endl;
  cout << setw(20) <<  "mdl_I4a33 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << mdl_I4a33 << endl;
  cout << setw(20) <<  "mdl_ee__exp__2 " <<  "= " <<
      setiosflags(ios::scientific) << setw(10) << mdl_ee__exp__2 << endl;
  cout << setw(20) <<  "mdl_sw__exp__2 " <<  "= " <<
      setiosflags(ios::scientific) << setw(10) << mdl_sw__exp__2 << endl;
  cout << setw(20) <<  "mdl_cw__exp__2 " <<  "= " <<
      setiosflags(ios::scientific) << setw(10) << mdl_cw__exp__2 << endl;
}
void Parameters_GambitDemo_UFO::printIndependentCouplings()
{
  cout <<  "GambitDemo_UFO model couplings independent of event kinematics:" <<
      endl;
  cout << setw(20) <<  "GC_1 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_1 << endl;
  cout << setw(20) <<  "GC_2 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_2 << endl;
  cout << setw(20) <<  "GC_3 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_3 << endl;
  cout << setw(20) <<  "GC_4 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_4 << endl;
  cout << setw(20) <<  "GC_5 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_5 << endl;
  cout << setw(20) <<  "GC_6 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_6 << endl;
  cout << setw(20) <<  "GC_7 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_7 << endl;
  cout << setw(20) <<  "GC_8 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_8 << endl;
  cout << setw(20) <<  "GC_9 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_9 << endl;
  cout << setw(20) <<  "GC_13 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_13 << endl;
  cout << setw(20) <<  "GC_14 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_14 << endl;
  cout << setw(20) <<  "GC_15 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_15 << endl;
  cout << setw(20) <<  "GC_16 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_16 << endl;
  cout << setw(20) <<  "GC_17 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_17 << endl;
  cout << setw(20) <<  "GC_18 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_18 << endl;
  cout << setw(20) <<  "GC_19 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_19 << endl;
  cout << setw(20) <<  "GC_20 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_20 << endl;
  cout << setw(20) <<  "GC_21 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_21 << endl;
  cout << setw(20) <<  "GC_22 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_22 << endl;
  cout << setw(20) <<  "GC_23 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_23 << endl;
  cout << setw(20) <<  "GC_24 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_24 << endl;
  cout << setw(20) <<  "GC_25 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_25 << endl;
  cout << setw(20) <<  "GC_26 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_26 << endl;
  cout << setw(20) <<  "GC_27 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_27 << endl;
  cout << setw(20) <<  "GC_28 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_28 << endl;
  cout << setw(20) <<  "GC_29 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_29 << endl;
  cout << setw(20) <<  "GC_30 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_30 << endl;
  cout << setw(20) <<  "GC_31 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_31 << endl;
  cout << setw(20) <<  "GC_32 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_32 << endl;
  cout << setw(20) <<  "GC_33 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_33 << endl;
  cout << setw(20) <<  "GC_34 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_34 << endl;
  cout << setw(20) <<  "GC_35 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_35 << endl;
  cout << setw(20) <<  "GC_36 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_36 << endl;
  cout << setw(20) <<  "GC_37 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_37 << endl;
  cout << setw(20) <<  "GC_38 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_38 << endl;
  cout << setw(20) <<  "GC_39 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_39 << endl;
  cout << setw(20) <<  "GC_40 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_40 << endl;
  cout << setw(20) <<  "GC_41 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_41 << endl;
  cout << setw(20) <<  "GC_42 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_42 << endl;
  cout << setw(20) <<  "GC_43 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_43 << endl;
  cout << setw(20) <<  "GC_44 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_44 << endl;
  cout << setw(20) <<  "GC_45 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_45 << endl;
  cout << setw(20) <<  "GC_46 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_46 << endl;
  cout << setw(20) <<  "GC_47 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_47 << endl;
  cout << setw(20) <<  "GC_48 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_48 << endl;
  cout << setw(20) <<  "GC_49 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_49 << endl;
  cout << setw(20) <<  "GC_50 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_50 << endl;
  cout << setw(20) <<  "GC_51 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_51 << endl;
  cout << setw(20) <<  "GC_53 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_53 << endl;
  cout << setw(20) <<  "GC_54 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_54 << endl;
  cout << setw(20) <<  "GC_55 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_55 << endl;
  cout << setw(20) <<  "GC_56 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_56 << endl;
  cout << setw(20) <<  "GC_57 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_57 << endl;
  cout << setw(20) <<  "GC_58 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_58 << endl;
  cout << setw(20) <<  "GC_59 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_59 << endl;
  cout << setw(20) <<  "GC_60 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_60 << endl;
  cout << setw(20) <<  "GC_61 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_61 << endl;
  cout << setw(20) <<  "GC_62 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_62 << endl;
  cout << setw(20) <<  "GC_63 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_63 << endl;
  cout << setw(20) <<  "GC_64 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_64 << endl;
  cout << setw(20) <<  "GC_65 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_65 << endl;
  cout << setw(20) <<  "GC_66 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_66 << endl;
  cout << setw(20) <<  "GC_67 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_67 << endl;
  cout << setw(20) <<  "GC_68 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_68 << endl;
  cout << setw(20) <<  "GC_69 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_69 << endl;
  cout << setw(20) <<  "GC_70 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_70 << endl;
  cout << setw(20) <<  "GC_71 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_71 << endl;
  cout << setw(20) <<  "GC_72 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_72 << endl;
  cout << setw(20) <<  "GC_73 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_73 << endl;
  cout << setw(20) <<  "GC_74 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_74 << endl;
  cout << setw(20) <<  "GC_75 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_75 << endl;
  cout << setw(20) <<  "GC_76 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_76 << endl;
  cout << setw(20) <<  "GC_77 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_77 << endl;
  cout << setw(20) <<  "GC_78 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_78 << endl;
  cout << setw(20) <<  "GC_79 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_79 << endl;
  cout << setw(20) <<  "GC_80 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_80 << endl;
  cout << setw(20) <<  "GC_81 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_81 << endl;
  cout << setw(20) <<  "GC_82 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_82 << endl;
  cout << setw(20) <<  "GC_83 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_83 << endl;
  cout << setw(20) <<  "GC_84 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_84 << endl;
  cout << setw(20) <<  "GC_85 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_85 << endl;
  cout << setw(20) <<  "GC_86 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_86 << endl;
  cout << setw(20) <<  "GC_87 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_87 << endl;
  cout << setw(20) <<  "GC_88 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_88 << endl;
  cout << setw(20) <<  "GC_89 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_89 << endl;
  cout << setw(20) <<  "GC_90 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_90 << endl;
  cout << setw(20) <<  "GC_91 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_91 << endl;
  cout << setw(20) <<  "GC_92 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_92 << endl;
  cout << setw(20) <<  "GC_93 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_93 << endl;
  cout << setw(20) <<  "GC_94 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_94 << endl;
  cout << setw(20) <<  "GC_95 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_95 << endl;
  cout << setw(20) <<  "GC_96 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_96 << endl;
  cout << setw(20) <<  "GC_97 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_97 << endl;
  cout << setw(20) <<  "GC_98 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_98 << endl;
  cout << setw(20) <<  "GC_99 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_99 << endl;
  cout << setw(20) <<  "GC_100 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_100 << endl;
  cout << setw(20) <<  "GC_101 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_101 << endl;
  cout << setw(20) <<  "GC_102 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_102 << endl;
  cout << setw(20) <<  "GC_103 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_103 << endl;
  cout << setw(20) <<  "GC_104 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_104 << endl;
  cout << setw(20) <<  "GC_105 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_105 << endl;
  cout << setw(20) <<  "GC_106 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_106 << endl;
  cout << setw(20) <<  "GC_107 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_107 << endl;
  cout << setw(20) <<  "GC_108 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_108 << endl;
  cout << setw(20) <<  "GC_109 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_109 << endl;
  cout << setw(20) <<  "GC_110 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_110 << endl;
  cout << setw(20) <<  "GC_111 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_111 << endl;
  cout << setw(20) <<  "GC_112 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_112 << endl;
  cout << setw(20) <<  "GC_113 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_113 << endl;
  cout << setw(20) <<  "GC_114 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_114 << endl;
  cout << setw(20) <<  "GC_115 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_115 << endl;
  cout << setw(20) <<  "GC_116 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_116 << endl;
  cout << setw(20) <<  "GC_117 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_117 << endl;
  cout << setw(20) <<  "GC_118 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_118 << endl;
  cout << setw(20) <<  "GC_119 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_119 << endl;
  cout << setw(20) <<  "GC_120 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_120 << endl;
  cout << setw(20) <<  "GC_121 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_121 << endl;
  cout << setw(20) <<  "GC_122 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_122 << endl;
  cout << setw(20) <<  "GC_123 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_123 << endl;
  cout << setw(20) <<  "GC_124 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_124 << endl;
  cout << setw(20) <<  "GC_125 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_125 << endl;
  cout << setw(20) <<  "GC_126 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_126 << endl;
  cout << setw(20) <<  "GC_127 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_127 << endl;
  cout << setw(20) <<  "GC_128 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_128 << endl;
  cout << setw(20) <<  "GC_129 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_129 << endl;
  cout << setw(20) <<  "GC_130 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_130 << endl;
  cout << setw(20) <<  "GC_131 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_131 << endl;
  cout << setw(20) <<  "GC_132 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_132 << endl;
  cout << setw(20) <<  "GC_133 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_133 << endl;
  cout << setw(20) <<  "GC_52 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_52 << endl;
}
void Parameters_GambitDemo_UFO::printDependentParameters()
{
  cout <<  "GambitDemo_UFO model parameters dependent on event kinematics:" <<
      endl;
  cout << setw(20) <<  "aS " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << aS << endl;
  cout << setw(20) <<  "mdl_sqrt__aS " <<  "= " << setiosflags(ios::scientific)
      << setw(10) << mdl_sqrt__aS << endl;
  cout << setw(20) <<  "G " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << G << endl;
  cout << setw(20) <<  "mdl_G__exp__2 " <<  "= " <<
      setiosflags(ios::scientific) << setw(10) << mdl_G__exp__2 << endl;
}
void Parameters_GambitDemo_UFO::printDependentCouplings()
{
  cout <<  "GambitDemo_UFO model couplings dependent on event kinematics:" <<
      endl;
  cout << setw(20) <<  "GC_12 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_12 << endl;
  cout << setw(20) <<  "GC_11 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_11 << endl;
  cout << setw(20) <<  "GC_10 " <<  "= " << setiosflags(ios::scientific) <<
      setw(10) << GC_10 << endl;
}

}  // end namespace Pythia8

