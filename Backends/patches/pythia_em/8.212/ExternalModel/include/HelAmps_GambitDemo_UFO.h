//==========================================================================
// This file has been automatically generated for Pythia 8
// MadGraph5_aMC@NLO v. 2.3.2.2, 2015-09-06
// By the MadGraph5_aMC@NLO Development Team
// Visit launchpad.net/madgraph5 and amcatnlo.web.cern.ch
//==========================================================================

#ifndef HelAmps_GambitDemo_UFO_H
#define HelAmps_GambitDemo_UFO_H

#include <cmath> 
#include <complex> 

using namespace std; 

namespace Pythia8_GambitDemo_UFO 
{
double Sgn(double e, double f); 

void sxxxxx(double p[4], int nss, std::complex<double> sc[3]); 

void vxxxxx(double p[4], double vmass, int nhel, int nsv, std::complex<double>
    v[6]);

void oxxxxx(double p[4], double fmass, int nhel, int nsf, std::complex<double>
    fo[6]);

void txxxxx(double p[4], double tmass, int nhel, int nst, std::complex<double>
    fi[18]);

void ixxxxx(double p[4], double fmass, int nhel, int nsf, std::complex<double>
    fi[6]);

void FFS2_0(complex<double> F1[], complex<double> F2[], complex<double> S3[],
    complex<double> COUP, complex<double> & vertex);

void SSS1_3(complex<double> S1[], complex<double> S2[], complex<double> COUP,
    double M3, double W3, complex<double> S3[]);

void FFV3_1(complex<double> F2[], complex<double> V3[], complex<double> COUP,
    double M1, double W1, complex<double> F1[]);

void VVVV2_3(complex<double> V1[], complex<double> V2[], complex<double> V4[],
    complex<double> COUP, double M3, double W3, complex<double> V3[]);

void FFV1_2(complex<double> F1[], complex<double> V3[], complex<double> COUP,
    double M2, double W2, complex<double> F2[]);

void VVVV4_3(complex<double> V1[], complex<double> V2[], complex<double> V4[],
    complex<double> COUP, double M3, double W3, complex<double> V3[]);

void VSS1_2(complex<double> V1[], complex<double> S3[], complex<double> COUP,
    double M2, double W2, complex<double> S2[]);

void VVV1_0(complex<double> V1[], complex<double> V2[], complex<double> V3[],
    complex<double> COUP, complex<double> & vertex);

void VVSS1_1(complex<double> V2[], complex<double> S3[], complex<double> S4[],
    complex<double> COUP, double M1, double W1, complex<double> V1[]);

void FFV4_0(complex<double> F1[], complex<double> F2[], complex<double> V3[],
    complex<double> COUP, complex<double> & vertex);

void VVVV3_2(complex<double> V1[], complex<double> V3[], complex<double> V4[],
    complex<double> COUP, double M2, double W2, complex<double> V2[]);

void VSS1P0_1(complex<double> S2[], complex<double> S3[], complex<double> COUP,
    double M1, double W1, complex<double> V1[]);

void VVV1P0_2(complex<double> V1[], complex<double> V3[], complex<double> COUP,
    double M2, double W2, complex<double> V2[]);

void VVVV1_0(complex<double> V1[], complex<double> V2[], complex<double> V3[],
    complex<double> V4[], complex<double> COUP, complex<double> & vertex);

void FFV2_1(complex<double> F2[], complex<double> V3[], complex<double> COUP,
    double M1, double W1, complex<double> F1[]);
void FFV2_4_1(complex<double> F2[], complex<double> V3[], complex<double>
    COUP1, complex<double> COUP2, double M1, double W1, complex<double> F1[]);
void FFV2_5_1(complex<double> F2[], complex<double> V3[], complex<double>
    COUP1, complex<double> COUP2, double M1, double W1, complex<double> F1[]);
void FFV2_3_1(complex<double> F2[], complex<double> V3[], complex<double>
    COUP1, complex<double> COUP2, double M1, double W1, complex<double> F1[]);

void VVVV4P0_2(complex<double> V1[], complex<double> V3[], complex<double>
    V4[], complex<double> COUP, double M2, double W2, complex<double> V2[]);

void FFV5_0(complex<double> F1[], complex<double> F2[], complex<double> V3[],
    complex<double> COUP, complex<double> & vertex);

void FFS4_0(complex<double> F1[], complex<double> F2[], complex<double> S3[],
    complex<double> COUP, complex<double> & vertex);

void FFV3_2(complex<double> F1[], complex<double> V3[], complex<double> COUP,
    double M2, double W2, complex<double> F2[]);

void FFV1_1(complex<double> F2[], complex<double> V3[], complex<double> COUP,
    double M1, double W1, complex<double> F1[]);

void VVS1_2(complex<double> V1[], complex<double> S3[], complex<double> COUP,
    double M2, double W2, complex<double> V2[]);

void FFS2_2(complex<double> F1[], complex<double> S3[], complex<double> COUP,
    double M2, double W2, complex<double> F2[]);

void VVSS1_2(complex<double> V1[], complex<double> S3[], complex<double> S4[],
    complex<double> COUP, double M2, double W2, complex<double> V2[]);

void VVSS1P0_1(complex<double> V2[], complex<double> S3[], complex<double>
    S4[], complex<double> COUP, double M1, double W1, complex<double> V1[]);

void SSS1_1(complex<double> S2[], complex<double> S3[], complex<double> COUP,
    double M1, double W1, complex<double> S1[]);

void SSSS1_4(complex<double> S1[], complex<double> S2[], complex<double> S3[],
    complex<double> COUP, double M4, double W4, complex<double> S4[]);

void VVVV1P0_3(complex<double> V1[], complex<double> V2[], complex<double>
    V4[], complex<double> COUP, double M3, double W3, complex<double> V3[]);

void VVVV4_1(complex<double> V2[], complex<double> V3[], complex<double> V4[],
    complex<double> COUP, double M1, double W1, complex<double> V1[]);

void VSS1_0(complex<double> V1[], complex<double> S2[], complex<double> S3[],
    complex<double> COUP, complex<double> & vertex);

void VVV1_2(complex<double> V1[], complex<double> V3[], complex<double> COUP,
    double M2, double W2, complex<double> V2[]);

void VVVV3P0_4(complex<double> V1[], complex<double> V2[], complex<double>
    V3[], complex<double> COUP, double M4, double W4, complex<double> V4[]);

void FFS3_3(complex<double> F1[], complex<double> F2[], complex<double> COUP,
    double M3, double W3, complex<double> S3[]);

void VVVV1P0_4(complex<double> V1[], complex<double> V2[], complex<double>
    V3[], complex<double> COUP, double M4, double W4, complex<double> V4[]);

void VVVV4P0_1(complex<double> V2[], complex<double> V3[], complex<double>
    V4[], complex<double> COUP, double M1, double W1, complex<double> V1[]);

void VVVV3_0(complex<double> V1[], complex<double> V2[], complex<double> V3[],
    complex<double> V4[], complex<double> COUP, complex<double> & vertex);

void VVVV4_4(complex<double> V1[], complex<double> V2[], complex<double> V3[],
    complex<double> COUP, double M4, double W4, complex<double> V4[]);

void FFS4_3(complex<double> F1[], complex<double> F2[], complex<double> COUP,
    double M3, double W3, complex<double> S3[]);

void FFS1_1(complex<double> F2[], complex<double> S3[], complex<double> COUP,
    double M1, double W1, complex<double> F1[]);
void FFS1_3_1(complex<double> F2[], complex<double> S3[], complex<double>
    COUP1, complex<double> COUP2, double M1, double W1, complex<double> F1[]);

void VVVV3P0_1(complex<double> V2[], complex<double> V3[], complex<double>
    V4[], complex<double> COUP, double M1, double W1, complex<double> V1[]);

void VVVV1_2(complex<double> V1[], complex<double> V3[], complex<double> V4[],
    complex<double> COUP, double M2, double W2, complex<double> V2[]);

void FFV2_3(complex<double> F1[], complex<double> F2[], complex<double> COUP,
    double M3, double W3, complex<double> V3[]);
void FFV2_4_3(complex<double> F1[], complex<double> F2[], complex<double>
    COUP1, complex<double> COUP2, double M3, double W3, complex<double> V3[]);
void FFV2_5_3(complex<double> F1[], complex<double> F2[], complex<double>
    COUP1, complex<double> COUP2, double M3, double W3, complex<double> V3[]);
void FFV2_3_3(complex<double> F1[], complex<double> F2[], complex<double>
    COUP1, complex<double> COUP2, double M3, double W3, complex<double> V3[]);

void FFS2_1(complex<double> F2[], complex<double> S3[], complex<double> COUP,
    double M1, double W1, complex<double> F1[]);

void VVVV4P0_4(complex<double> V1[], complex<double> V2[], complex<double>
    V3[], complex<double> COUP, double M4, double W4, complex<double> V4[]);

void FFV5_2(complex<double> F1[], complex<double> V3[], complex<double> COUP,
    double M2, double W2, complex<double> F2[]);

void SSS1_2(complex<double> S1[], complex<double> S3[], complex<double> COUP,
    double M2, double W2, complex<double> S2[]);

void SSSS1_1(complex<double> S2[], complex<double> S3[], complex<double> S4[],
    complex<double> COUP, double M1, double W1, complex<double> S1[]);

void VVVV2_0(complex<double> V1[], complex<double> V2[], complex<double> V3[],
    complex<double> V4[], complex<double> COUP, complex<double> & vertex);

void FFV1_3(complex<double> F1[], complex<double> F2[], complex<double> COUP,
    double M3, double W3, complex<double> V3[]);

void SSSS1_0(complex<double> S1[], complex<double> S2[], complex<double> S3[],
    complex<double> S4[], complex<double> COUP, complex<double> & vertex);

void VSS1_3(complex<double> V1[], complex<double> S2[], complex<double> COUP,
    double M3, double W3, complex<double> S3[]);

void VVVV2P0_1(complex<double> V2[], complex<double> V3[], complex<double>
    V4[], complex<double> COUP, double M1, double W1, complex<double> V1[]);

void VVV1_1(complex<double> V2[], complex<double> V3[], complex<double> COUP,
    double M1, double W1, complex<double> V1[]);

void VVSS1_0(complex<double> V1[], complex<double> V2[], complex<double> S3[],
    complex<double> S4[], complex<double> COUP, complex<double> & vertex);

void FFS3_0(complex<double> F1[], complex<double> F2[], complex<double> S3[],
    complex<double> COUP, complex<double> & vertex);

void FFV4_3(complex<double> F1[], complex<double> F2[], complex<double> COUP,
    double M3, double W3, complex<double> V3[]);

void VVVV1P0_1(complex<double> V2[], complex<double> V3[], complex<double>
    V4[], complex<double> COUP, double M1, double W1, complex<double> V1[]);

void VVVV5_4(complex<double> V1[], complex<double> V2[], complex<double> V3[],
    complex<double> COUP, double M4, double W4, complex<double> V4[]);

void VVV1P0_3(complex<double> V1[], complex<double> V2[], complex<double> COUP,
    double M3, double W3, complex<double> V3[]);

void SSSS1_2(complex<double> S1[], complex<double> S3[], complex<double> S4[],
    complex<double> COUP, double M2, double W2, complex<double> S2[]);

void FFS3_1(complex<double> F2[], complex<double> S3[], complex<double> COUP,
    double M1, double W1, complex<double> F1[]);

void FFV2_0(complex<double> F1[], complex<double> F2[], complex<double> V3[],
    complex<double> COUP, complex<double> & vertex);
void FFV2_4_0(complex<double> F1[], complex<double> F2[], complex<double> V3[],
    complex<double> COUP1, complex<double> COUP2, complex<double> & vertex);
void FFV2_5_0(complex<double> F1[], complex<double> F2[], complex<double> V3[],
    complex<double> COUP1, complex<double> COUP2, complex<double> & vertex);
void FFV2_3_0(complex<double> F1[], complex<double> F2[], complex<double> V3[],
    complex<double> COUP1, complex<double> COUP2, complex<double> & vertex);

void VVVV4P0_3(complex<double> V1[], complex<double> V2[], complex<double>
    V4[], complex<double> COUP, double M3, double W3, complex<double> V3[]);

void FFV5_1(complex<double> F2[], complex<double> V3[], complex<double> COUP,
    double M1, double W1, complex<double> F1[]);

void FFS4_1(complex<double> F2[], complex<double> S3[], complex<double> COUP,
    double M1, double W1, complex<double> F1[]);

void FFS1_3(complex<double> F1[], complex<double> F2[], complex<double> COUP,
    double M3, double W3, complex<double> S3[]);
void FFS1_3_3(complex<double> F1[], complex<double> F2[], complex<double>
    COUP1, complex<double> COUP2, double M3, double W3, complex<double> S3[]);

void FFV1P0_3(complex<double> F1[], complex<double> F2[], complex<double> COUP,
    double M3, double W3, complex<double> V3[]);

void VVVV3P0_3(complex<double> V1[], complex<double> V2[], complex<double>
    V4[], complex<double> COUP, double M3, double W3, complex<double> V3[]);

void VVS1_1(complex<double> V2[], complex<double> S3[], complex<double> COUP,
    double M1, double W1, complex<double> V1[]);

void FFS2_3(complex<double> F1[], complex<double> F2[], complex<double> COUP,
    double M3, double W3, complex<double> S3[]);

void VVVV5P0_1(complex<double> V2[], complex<double> V3[], complex<double>
    V4[], complex<double> COUP, double M1, double W1, complex<double> V1[]);

void FFS3P0_2(complex<double> F1[], complex<double> S3[], complex<double> COUP,
    double M2, double W2, complex<double> F2[]);

void SSS1_0(complex<double> S1[], complex<double> S2[], complex<double> S3[],
    complex<double> COUP, complex<double> & vertex);

void FFV3_0(complex<double> F1[], complex<double> F2[], complex<double> V3[],
    complex<double> COUP, complex<double> & vertex);

void VVVV5_2(complex<double> V1[], complex<double> V3[], complex<double> V4[],
    complex<double> COUP, double M2, double W2, complex<double> V2[]);

void VVVV2_2(complex<double> V1[], complex<double> V3[], complex<double> V4[],
    complex<double> COUP, double M2, double W2, complex<double> V2[]);

void VVVV4_2(complex<double> V1[], complex<double> V3[], complex<double> V4[],
    complex<double> COUP, double M2, double W2, complex<double> V2[]);

void VSS1_1(complex<double> S2[], complex<double> S3[], complex<double> COUP,
    double M1, double W1, complex<double> V1[]);

void VVV1_3(complex<double> V1[], complex<double> V2[], complex<double> COUP,
    double M3, double W3, complex<double> V3[]);

void FFS3_2(complex<double> F1[], complex<double> S3[], complex<double> COUP,
    double M2, double W2, complex<double> F2[]);

void FFV4_1(complex<double> F2[], complex<double> V3[], complex<double> COUP,
    double M1, double W1, complex<double> F1[]);

void VVVV1_4(complex<double> V1[], complex<double> V2[], complex<double> V3[],
    complex<double> COUP, double M4, double W4, complex<double> V4[]);

void FFV2P0_1(complex<double> F2[], complex<double> V3[], complex<double> COUP,
    double M1, double W1, complex<double> F1[]);

void FFV5_3(complex<double> F1[], complex<double> F2[], complex<double> COUP,
    double M3, double W3, complex<double> V3[]);

void VVVV3_3(complex<double> V1[], complex<double> V2[], complex<double> V4[],
    complex<double> COUP, double M3, double W3, complex<double> V3[]);

void FFS1_0(complex<double> F1[], complex<double> F2[], complex<double> S3[],
    complex<double> COUP, complex<double> & vertex);
void FFS1_3_0(complex<double> F1[], complex<double> F2[], complex<double> S3[],
    complex<double> COUP1, complex<double> COUP2, complex<double> & vertex);

void VVV1P0_1(complex<double> V2[], complex<double> V3[], complex<double> COUP,
    double M1, double W1, complex<double> V1[]);

void FFV3_3(complex<double> F1[], complex<double> F2[], complex<double> COUP,
    double M3, double W3, complex<double> V3[]);

void VVVV1_1(complex<double> V2[], complex<double> V3[], complex<double> V4[],
    complex<double> COUP, double M1, double W1, complex<double> V1[]);

void FFV2_2(complex<double> F1[], complex<double> V3[], complex<double> COUP,
    double M2, double W2, complex<double> F2[]);
void FFV2_4_2(complex<double> F1[], complex<double> V3[], complex<double>
    COUP1, complex<double> COUP2, double M2, double W2, complex<double> F2[]);
void FFV2_5_2(complex<double> F1[], complex<double> V3[], complex<double>
    COUP1, complex<double> COUP2, double M2, double W2, complex<double> F2[]);
void FFV2_3_2(complex<double> F1[], complex<double> V3[], complex<double>
    COUP1, complex<double> COUP2, double M2, double W2, complex<double> F2[]);

void VVVV3_4(complex<double> V1[], complex<double> V2[], complex<double> V3[],
    complex<double> COUP, double M4, double W4, complex<double> V4[]);

void VVVV5_0(complex<double> V1[], complex<double> V2[], complex<double> V3[],
    complex<double> V4[], complex<double> COUP, complex<double> & vertex);

void SSSS1_3(complex<double> S1[], complex<double> S2[], complex<double> S4[],
    complex<double> COUP, double M3, double W3, complex<double> S3[]);

void VVVV2_1(complex<double> V2[], complex<double> V3[], complex<double> V4[],
    complex<double> COUP, double M1, double W1, complex<double> V1[]);

void FFV1_0(complex<double> F1[], complex<double> F2[], complex<double> V3[],
    complex<double> COUP, complex<double> & vertex);

void VVS1_3(complex<double> V1[], complex<double> V2[], complex<double> COUP,
    double M3, double W3, complex<double> S3[]);

void VVVV1P0_2(complex<double> V1[], complex<double> V3[], complex<double>
    V4[], complex<double> COUP, double M2, double W2, complex<double> V2[]);

void VVVV2P0_2(complex<double> V1[], complex<double> V3[], complex<double>
    V4[], complex<double> COUP, double M2, double W2, complex<double> V2[]);

void VVSS1_3(complex<double> V1[], complex<double> V2[], complex<double> S4[],
    complex<double> COUP, double M3, double W3, complex<double> S3[]);

void VVSS1P0_2(complex<double> V1[], complex<double> S3[], complex<double>
    S4[], complex<double> COUP, double M2, double W2, complex<double> V2[]);

void FFV4_2(complex<double> F1[], complex<double> V3[], complex<double> COUP,
    double M2, double W2, complex<double> F2[]);

void FFV2P0_2(complex<double> F1[], complex<double> V3[], complex<double> COUP,
    double M2, double W2, complex<double> F2[]);

void VVVV4_0(complex<double> V1[], complex<double> V2[], complex<double> V3[],
    complex<double> V4[], complex<double> COUP, complex<double> & vertex);

void VVS1P0_1(complex<double> V2[], complex<double> S3[], complex<double> COUP,
    double M1, double W1, complex<double> V1[]);

void FFS1P0_1(complex<double> F2[], complex<double> S3[], complex<double> COUP,
    double M1, double W1, complex<double> F1[]);

void VVSS1_4(complex<double> V1[], complex<double> V2[], complex<double> S3[],
    complex<double> COUP, double M4, double W4, complex<double> S4[]);

void VVVV5_3(complex<double> V1[], complex<double> V2[], complex<double> V4[],
    complex<double> COUP, double M3, double W3, complex<double> V3[]);

void VVVV3_1(complex<double> V2[], complex<double> V3[], complex<double> V4[],
    complex<double> COUP, double M1, double W1, complex<double> V1[]);

void FFS4_2(complex<double> F1[], complex<double> S3[], complex<double> COUP,
    double M2, double W2, complex<double> F2[]);

void FFS1_2(complex<double> F1[], complex<double> S3[], complex<double> COUP,
    double M2, double W2, complex<double> F2[]);
void FFS1_3_2(complex<double> F1[], complex<double> S3[], complex<double>
    COUP1, complex<double> COUP2, double M2, double W2, complex<double> F2[]);

void VVVV2_4(complex<double> V1[], complex<double> V2[], complex<double> V3[],
    complex<double> COUP, double M4, double W4, complex<double> V4[]);

void VVVV3P0_2(complex<double> V1[], complex<double> V3[], complex<double>
    V4[], complex<double> COUP, double M2, double W2, complex<double> V2[]);

void VVS1_0(complex<double> V1[], complex<double> V2[], complex<double> S3[],
    complex<double> COUP, complex<double> & vertex);

void VVVV5_1(complex<double> V2[], complex<double> V3[], complex<double> V4[],
    complex<double> COUP, double M1, double W1, complex<double> V1[]);

void VVVV1_3(complex<double> V1[], complex<double> V2[], complex<double> V4[],
    complex<double> COUP, double M3, double W3, complex<double> V3[]);

}  // end namespace Pythia8_GambitDemo_UFO

#endif  // HelAmps_GambitDemo_UFO_H
