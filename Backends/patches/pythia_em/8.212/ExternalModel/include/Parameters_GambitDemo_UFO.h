//==========================================================================
// This file has been automatically generated for Pythia 8
// MadGraph5_aMC@NLO v. 2.3.2.2, 2015-09-06
// By the MadGraph5_aMC@NLO Development Team
// Visit launchpad.net/madgraph5 and amcatnlo.web.cern.ch
//==========================================================================

#ifndef Pythia8_parameters_GambitDemo_UFO_H
#define Pythia8_parameters_GambitDemo_UFO_H

#include <complex> 

#include "Pythia8/ParticleData.h"
#include "Pythia8/StandardModel.h"
#include "Pythia8/SusyLesHouches.h"

using namespace std; 

namespace Pythia8 
{

class Parameters_GambitDemo_UFO
{
  public:

    static Parameters_GambitDemo_UFO * getInstance(); 

    // Model parameters independent of aS
    double mdl_Wuv, mdl_WH, mdl_WT, mdl_WW, mdl_WZ, mdl_Mp1, mdl_Muv, mdl_MH,
        mdl_MB, mdl_MS, mdl_MD, mdl_MT, mdl_MC, mdl_MU, mdl_MTA, mdl_MMU,
        mdl_Me, mdl_MZ, mdl_lam1, mdl_MM1, mdl_ymtau, mdl_ymm, mdl_yme,
        mdl_ymt, mdl_ymb, mdl_ymc, mdl_yms, mdl_ymup, mdl_ymdo, mdl_Gf, aEWM1,
        mdl_cabi, ZERO, mdl_cos__cabi, mdl_sin__cabi, mdl_MZ__exp__2,
        mdl_MZ__exp__4, mdl_sqrt__2, mdl_MH__exp__2, mdl_aEW, mdl_MW,
        mdl_sqrt__aEW, mdl_ee, mdl_MW__exp__2, mdl_sw2, mdl_cw, mdl_sqrt__sw2,
        mdl_sw, mdl_g1, mdl_gw, mdl_vev, mdl_vev__exp__2, mdl_lam, mdl_yb,
        mdl_yc, mdl_ydo, mdl_ye, mdl_ym, mdl_ys, mdl_yt, mdl_ytau, mdl_yup,
        mdl_muH, mdl_ee__exp__2, mdl_sw__exp__2, mdl_cw__exp__2;
    std::complex<double> mdl_CKM1x1, mdl_CKM1x2, mdl_CKM1x3, mdl_CKM2x1,
        mdl_CKM2x2, mdl_CKM2x3, mdl_CKM3x1, mdl_CKM3x2, mdl_CKM3x3,
        mdl_conjg__CKM1x1, mdl_conjg__CKM2x1, mdl_conjg__CKM3x1,
        mdl_conjg__CKM1x2, mdl_conjg__CKM2x2, mdl_conjg__CKM3x2,
        mdl_conjg__CKM1x3, mdl_conjg__CKM2x3, mdl_conjg__CKM3x3, mdl_complexi,
        mdl_I1a11, mdl_I1a12, mdl_I1a13, mdl_I1a21, mdl_I1a22, mdl_I1a23,
        mdl_I1a31, mdl_I1a32, mdl_I1a33, mdl_I2a11, mdl_I2a12, mdl_I2a13,
        mdl_I2a21, mdl_I2a22, mdl_I2a23, mdl_I2a31, mdl_I2a32, mdl_I2a33,
        mdl_I3a11, mdl_I3a12, mdl_I3a13, mdl_I3a21, mdl_I3a22, mdl_I3a23,
        mdl_I3a31, mdl_I3a32, mdl_I3a33, mdl_I4a11, mdl_I4a12, mdl_I4a13,
        mdl_I4a21, mdl_I4a22, mdl_I4a23, mdl_I4a31, mdl_I4a32, mdl_I4a33;
    // Model parameters dependent on aS
    double aS, mdl_sqrt__aS, G, mdl_G__exp__2; 
    // Model couplings independent of aS
    std::complex<double> GC_1, GC_2, GC_3, GC_4, GC_5, GC_6, GC_7, GC_8, GC_9,
        GC_13, GC_14, GC_15, GC_16, GC_17, GC_18, GC_19, GC_20, GC_21, GC_22,
        GC_23, GC_24, GC_25, GC_26, GC_27, GC_28, GC_29, GC_30, GC_31, GC_32,
        GC_33, GC_34, GC_35, GC_36, GC_37, GC_38, GC_39, GC_40, GC_41, GC_42,
        GC_43, GC_44, GC_45, GC_46, GC_47, GC_48, GC_49, GC_50, GC_51, GC_53,
        GC_54, GC_55, GC_56, GC_57, GC_58, GC_59, GC_60, GC_61, GC_62, GC_63,
        GC_64, GC_65, GC_66, GC_67, GC_68, GC_69, GC_70, GC_71, GC_72, GC_73,
        GC_74, GC_75, GC_76, GC_77, GC_78, GC_79, GC_80, GC_81, GC_82, GC_83,
        GC_84, GC_85, GC_86, GC_87, GC_88, GC_89, GC_90, GC_91, GC_92, GC_93,
        GC_94, GC_95, GC_96, GC_97, GC_98, GC_99, GC_100, GC_101, GC_102,
        GC_103, GC_104, GC_105, GC_106, GC_107, GC_108, GC_109, GC_110, GC_111,
        GC_112, GC_113, GC_114, GC_115, GC_116, GC_117, GC_118, GC_119, GC_120,
        GC_121, GC_122, GC_123, GC_124, GC_125, GC_126, GC_127, GC_128, GC_129,
        GC_130, GC_131, GC_132, GC_133, GC_52;
    // Model couplings dependent on aS
    std::complex<double> GC_12, GC_11, GC_10; 

    // Set parameters that are unchanged during the run
    void setIndependentParameters(ParticleData * & pd, Couplings * & csm,
        SusyLesHouches * & slhaPtr);
    // Set couplings that are unchanged during the run
    void setIndependentCouplings(); 
    // Set parameters that are changed event by event
    void setDependentParameters(ParticleData * & pd, Couplings * & csm,
        SusyLesHouches * & slhaPtr, double alpS);
    // Set couplings that are changed event by event
    void setDependentCouplings(); 

    // Print parameters that are unchanged during the run
    void printIndependentParameters(); 
    // Print couplings that are unchanged during the run
    void printIndependentCouplings(); 
    // Print parameters that are changed event by event
    void printDependentParameters(); 
    // Print couplings that are changed event by event
    void printDependentCouplings(); 


  private:
    static Parameters_GambitDemo_UFO * instance; 
}; 

}  // end namespace Pythia8
#endif  // Pythia8_parameters_GambitDemo_UFO_H

