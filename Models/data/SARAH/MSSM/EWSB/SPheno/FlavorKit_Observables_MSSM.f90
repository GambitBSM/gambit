! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.8.1 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 15:01 on 22.11.2017   
! ----------------------------------------------------------------------  
 
 
Module FlavorKit_Observables_MSSM 
Use Control 
Use Couplings_MSSM 
Use LoopCouplings_MSSM 
Use LoopFunctions 
Use LoopMasses_MSSM 
Use StandardModel 

 
 Contains 
 
Subroutine Calculate_hLLp(OH2lSL,OH2lSR,BrhtoMuE,BrhtoTauE,BrhtoTauMu)

Implicit None 
Complex(dp) :: OH2lSL(3,3,2),OH2lSR(3,3,2)

Real(dp), Intent(out) :: BrhtoMuE 
Real(dp), Intent(out) :: BrhtoTauE 
Real(dp), Intent(out) :: BrhtoTauMu 

 
 ! #####+ Beging user defined body 
Real(dp) :: width1, width2, width, mh, gamh, kinfactor
Complex(dp) :: SL1, SR1, SL2, SR2
Integer :: i1, gt1, gt2, hLoc

! ---------------------------------------------------------------- 
! h -> l l'
! Observable implemented by W. Porod, F. Staub and A. Vicente
! Based on E. Arganda et al, PRD 71 (2005) 035011 [hep-ph/0407302]
! ---------------------------------------------------------------- 

!! NEXT LINE HAVE TO BE PARSED BY SARAH
! Checking if there are several generations of Scalars and what is the SM-like doublet
hLoc = MaxLoc(Abs(ZH(2,:)),1)

mh = Mhh(hLoc)

gamh =gThh(hLoc)

If (.not.L_BR) gamh = 4.5E-3_dp  ! Decays not calculated; using SM value

Do i1=1,3 

If (i1.eq.1) Then         ! h -> e mu
 gt1 = 1
 gt2 = 2
Elseif (i1.eq.2) Then     ! h -> e tau
 gt1 = 1
 gt2 = 3
Else                      ! h -> mu tau
 gt1 = 2
 gt2 = 3
End if

! width = Gamma(h -> \bar{l1} l2) + Gamma(h -> l1 \bar{l2})

SL1 = OH2lSL(gt1,gt2,hLoc)
SR1 = OH2lSR(gt1,gt2,hLoc)
SL2 = OH2lSL(gt2,gt1,hLoc)
SR2 = OH2lSR(gt2,gt1,hLoc)

kinfactor = (1-(mf_l(gt1)+mf_l(gt2)/mh)**2)*&
       & (1-(mf_l(gt1)-mf_l(gt2)/mh)**2)

width1 = (mh**2-mf_l(gt1)**2-mf_l(gt2)**2)*(Abs(SL1)**2+Abs(SR1)**2) & 
     & - 4._dp*mf_l(gt1)*mf_l(gt2)*Real(SL1*Conjg(SR1),dp)
width2 = (mh**2-mf_l(gt1)**2-mf_l(gt2)**2)*(Abs(SL2)**2+Abs(SR2)**2) & 
     & - 4._dp*mf_l(gt1)*mf_l(gt2)*Real(SL2*Conjg(SR2),dp)

! decay width
width = oo16pi/mh * sqrt(kinfactor) * (width1+width2)

If (i1.eq.1) Then
BrhtoMuE = width/(width+gamh)
Elseif (i1.eq.2) Then 
BrhtoTauE = width/(width+gamh)
Else
BrhtoTauMu = width/(width+gamh)
End if

End do

 
 ! ###### End user defined body 
End Subroutine Calculate_hLLp

Subroutine Calculate_LLpGamma(K2L,K2R,muEgamma,tauEgamma,tauMuGamma)

Implicit None 
Complex(dp) :: K2L(3,3),K2R(3,3)

Real(dp), Intent(out) :: muEgamma 
Real(dp), Intent(out) :: tauEgamma 
Real(dp), Intent(out) :: tauMuGamma 

 
 ! #####+ Beging user defined body 
Real(dp) :: width
Integer :: i1, gt1, gt2

! ---------------------------------------------------------------- 
! l -> l' gamma
! Observable implemented by W. Porod, F. Staub and A. Vicente
! Based on J. Hisano et al, PRD 53 (1996) 2442 [hep-ph/9510309]
! ---------------------------------------------------------------- 

Do i1=1,3 

If (i1.eq.1) Then         ! mu -> e gamma
 gt1 = 2
 gt2 = 1
Elseif (i1.eq.2) Then     !tau -> e gamma
 gt1 = 3
 gt2 = 1
Else                      ! tau -> mu gamma
 gt1 = 3
 gt2 = 2
End if

width=0.25_dp*mf_l(gt1)**5*(Abs(K2L(gt1,gt2))**2 &
           & +Abs(K2R(gt1,gt2))**2)*Alpha

If (i1.eq.1) Then
muEgamma = width/(width+GammaMu)
Elseif (i1.eq.2) Then 
tauEgamma = width/(width+GammaTau)
Else
tauMuGamma = width/(width+GammaTau)
End if

End do

 
 ! ###### End user defined body 
End Subroutine Calculate_LLpGamma

Subroutine Calculate_Lto3Lp(K1L,K1R,K2L,K2R,O4lSLL,O4lSRR,O4lSRL,O4lSLR,              & 
& O4lVRR,O4lVLL,O4lVRL,O4lVLR,O4lTLL,O4lTRR,BRmuTo3e,BRtauTo3e,BRtauTo3mu)

Implicit None 
Complex(dp) :: K1L(3,3),K1R(3,3),K2L(3,3),K2R(3,3),O4lSLL(3,3,3,3),O4lSRR(3,3,3,3),O4lSRL(3,3,3,3),  & 
& O4lSLR(3,3,3,3),O4lVRR(3,3,3,3),O4lVLL(3,3,3,3),O4lVRL(3,3,3,3),O4lVLR(3,3,3,3),       & 
& O4lTLL(3,3,3,3),O4lTRR(3,3,3,3)

Real(dp), Intent(out) :: BRmuTo3e 
Real(dp), Intent(out) :: BRtauTo3e 
Real(dp), Intent(out) :: BRtauTo3mu 

 
 ! #####+ Beging user defined body 
Complex(dp) :: cK1L, cK1R, cK2L, cK2R
Complex(dp) :: CSLL, CSRR, CSLR, CSRL, CVLL, &
                    & CVRR, CVLR, CVRL, CTLL, CTRR
Real(dp) :: BRdipole, BRscalar, BRvector, BRtensor
Real(dp) :: BRmix1, BRmix2, BRmix3, BRmix4, GammaLFV
Real(dp) :: e2, e4
Integer :: i1, gt1, gt2, gt3, gt4

! ---------------------------------------------------------------- 
! l -> 3 l'
! Observable implemented by W. Porod, F. Staub and A. Vicente
! ---------------------------------------------------------------- 

e2 = (4._dp*Pi*Alpha_MZ)
e4 = e2**2

Do i1=1,3 

If (i1.eq.1) Then
 gt1 = 2
 gt2 = 1
Elseif (i1.eq.2) Then
 gt1 = 3
 gt2 = 1
Else 
 gt1 = 3
 gt2 = 2
End if
gt3 = gt2
gt4 = gt2

cK1L = K1L(gt1,gt2)
cK1R = K1R(gt1,gt2)

cK2L = K2L(gt1,gt2)
cK2R = K2R(gt1,gt2)

CSLL = O4lSLL(gt1,gt2,gt3,gt4)
CSRR = O4lSRR(gt1,gt2,gt3,gt4)
CSLR = O4lSLR(gt1,gt2,gt3,gt4)
CSRL = O4lSRL(gt1,gt2,gt3,gt4)

CVLL = O4lVLL(gt1,gt2,gt3,gt4)
CVRR = O4lVRR(gt1,gt2,gt3,gt4)
CVLR = O4lVLR(gt1,gt2,gt3,gt4)
CVRL = O4lVRL(gt1,gt2,gt3,gt4)

CVLL = CVLL + e2*cK1L
CVRR = CVRR + e2*cK1R
CVLR = CVLR + e2*cK1L
CVRL = CVRL + e2*cK1R

CTLL = O4lTLL(gt1,gt2,gt3,gt4)
CTRR = O4lTRR(gt1,gt2,gt3,gt4)

! Photonic dipole contributions
BRdipole = (Abs(cK2L)**2+Abs(cK2R)**2)&
&*(16._dp*Log(mf_l(gt1)/mf_l(gt2))-22._dp)/3._dp

! Scalar contributions
BRscalar = (Abs(CSLL)**2+Abs(CSRR)**2)/24._dp&
&+(Abs(CSLR)**2+Abs(CSRL)**2)/12._dp

! Vector contributions
BRvector = 2._dp*(Abs(CVLL)**2+Abs(CVRR)**2)/3._dp&
&+(Abs(CVLR)**2+Abs(CVRL)**2)/3._dp

! Tensor contributions
BRtensor = 6._dp*(Abs(CTLL)**2+Abs(CTRR)**2)

! Mix: dipole x scalar
BRmix1 = 2._dp/3._dp*Real(cK2L*Conjg(CSRL) + cK2R*Conjg(CSLR),dp)

! Mix: dipole x vector
BRmix2 = -4._dp/3._dp*Real(cK2L*Conjg(CVRL) + cK2R*Conjg(CVLR),dp) &
     & -8._dp/3._dp*Real(cK2L*Conjg(CVRR) + cK2R*Conjg(CVLL),dp)

! Mix: scalar x vector
BRmix3 = -1._dp/3._dp*Real(CSLR*Conjg(CVLR) + CSRL*Conjg(CVRL),dp)

! Mix: scalar x tensor
BRmix4 = -1._dp*Real(CSLL*Conjg(CTLL) + CSRR*Conjg(CTRR),dp)

GammaLFV = oo512pi3*mf_l(gt1)**5* &
     & (e4*BRdipole + BRscalar + BRvector + BRtensor &
     & + e2*BRmix1 + e2*BRmix2 + BRmix3 + BRmix4)

!----------------------------------------------------------------------
!taking alpha(Q=0) instead of alpha(m_Z) as this contains most of the
!running of the Wilson coefficients
!----------------------------------------------------------------------

If (i1.Eq.1) Then
 BRmuTo3e=GammaLFV/GammaMu
Else If (i1.Eq.2) Then
 BRtauTo3e=GammaLFV/GammaTau
Else 
 BRtauTo3mu=GammaLFV/GammaTau
End If
End do

 
 ! ###### End user defined body 
End Subroutine Calculate_Lto3Lp

Subroutine Calculate_LtoL1L2L2(K1L,K1R,K2L,K2R,O4lSLL,O4lSRR,O4lSRL,O4lSLR,           & 
& O4lVRR,O4lVLL,O4lVRL,O4lVLR,O4lTLL,O4lTRR,O4lSLLcross,O4lSRRcross,O4lSRLcross,         & 
& O4lSLRcross,O4lVRRcross,O4lVLLcross,O4lVRLcross,O4lVLRcross,O4lTLLcross,               & 
& O4lTRRcross,BRtauToemumu,BRtauTomuee,BRtauToemumu2,BRtauTomuee2)

Implicit None 
Complex(dp) :: K1L(3,3),K1R(3,3),K2L(3,3),K2R(3,3),O4lSLL(3,3,3,3),O4lSRR(3,3,3,3),O4lSRL(3,3,3,3),  & 
& O4lSLR(3,3,3,3),O4lVRR(3,3,3,3),O4lVLL(3,3,3,3),O4lVRL(3,3,3,3),O4lVLR(3,3,3,3),       & 
& O4lTLL(3,3,3,3),O4lTRR(3,3,3,3),O4lSLLcross(3,3,3,3),O4lSRRcross(3,3,3,3),             & 
& O4lSRLcross(3,3,3,3),O4lSLRcross(3,3,3,3),O4lVRRcross(3,3,3,3),O4lVLLcross(3,3,3,3),   & 
& O4lVRLcross(3,3,3,3),O4lVLRcross(3,3,3,3),O4lTLLcross(3,3,3,3),O4lTRRcross(3,3,3,3)

Real(dp), Intent(out) :: BRtauToemumu 
Real(dp), Intent(out) :: BRtauTomuee 
Real(dp), Intent(out) :: BRtauToemumu2 
Real(dp), Intent(out) :: BRtauTomuee2 

 
 ! #####+ Beging user defined body 
Complex(dp) :: cK1L, cK1R, cK2L, cK2R
Complex(dp) :: CSLL, CSRR, CSLR, CSRL, CVLL, &
                    & CVRR, CVLR, CVRL, CTLL, CTRR
Complex(dp) :: CSLLcross, CSRRcross, CSLRcross, CSRLcross, &
                    & CVLLcross, CVRRcross, CVLRcross, &
                    & CVRLcross, CTLLcross, CTRRcross
Real(dp) :: BRdipole, BRscalar, BRvector, BRtensor
Real(dp) :: BRmix1, BRmix2, BRmix3, BRmix4, GammaLFV
Real(dp) :: e2, e4
Integer :: i1, gt1, gt2, gt3, gt4

! ---------------------------------------------------------------- 
! l^- -> l1^- l2^- l2^+ and l^- -> l1^+ l2^- l2^- (with l1 != l2)
! Observable implemented by A. Vicente
! ---------------------------------------------------------------- 

e2 = (4._dp*Pi*Alpha_MZ)
e4 = e2**2

Do i1=1,4

If (i1.eq.1) Then ! tau- -> e- mu+ mu-
 gt1 = 3
 gt2 = 1
 gt3 = 2
 gt4 = 2
Else If (i1.eq.2) Then ! tau- -> mu- e+ e-
 gt1 = 3
 gt2 = 2
 gt3 = 1
 gt4 = 1
Else If (i1.eq.3) Then ! tau- -> e+ mu- mu-
 gt1 = 3
 gt2 = 2
 gt3 = 1
 gt4 = 2
Else ! tau- -> mu+ e- e-
 gt1 = 3
 gt2 = 1
 gt3 = 2
 gt4 = 1
End if

If(i1.eq.1.or.i1.eq.2) Then ! tau- -> l- l'+ l'-

   cK1L = K1L(gt1,gt2)
   cK1R = K1R(gt1,gt2)

   cK2L = K2L(gt1,gt2)
   cK2R = K2R(gt1,gt2)

   CSLL = O4lSLLcross(gt1,gt2,gt3,gt4)
   CSRR = O4lSRRcross(gt1,gt2,gt3,gt4)
   CSLR = O4lSLRcross(gt1,gt2,gt3,gt4)
   CSRL = O4lSRLcross(gt1,gt2,gt3,gt4)

   CVLL = O4lVLLcross(gt1,gt2,gt3,gt4)
   CVRR = O4lVRRcross(gt1,gt2,gt3,gt4)
   CVLR = O4lVLRcross(gt1,gt2,gt3,gt4)
   CVRL = O4lVRLcross(gt1,gt2,gt3,gt4)

   CVLL = CVLL + e2*cK1L
   CVRR = CVRR + e2*cK1R
   CVLR = CVLR + e2*cK1L
   CVRL = CVRL + e2*cK1R

   CTLL = O4lTLLcross(gt1,gt2,gt3,gt4)
   CTRR = O4lTRRcross(gt1,gt2,gt3,gt4)

   ! Photonic dipole contributions
   BRdipole = (Abs(cK2L)**2+Abs(cK2R)**2)&
        &*(16._dp/3._dp*Log(mf_l(gt1)/mf_l(gt3))-8._dp)
   
   ! Scalar contributions
   BRscalar = (Abs(CSLL)**2+Abs(CSRR)**2)/12._dp&
        &+(Abs(CSLR)**2+Abs(CSRL)**2)/12._dp

   ! Vector contributions
   BRvector = (Abs(CVLL)**2+Abs(CVRR)**2)/3._dp&
        & + (Abs(CVLR)**2+Abs(CVRL)**2)/3._dp

   ! Tensor contributions
   BRtensor = 4._dp*(Abs(CTLL)**2+Abs(CTRR)**2)

   ! Mix: dipole x scalar
   BRmix1 = 0._dp

   ! Mix: dipole x vector
   BRmix2 = -4._dp/3._dp*Real(cK2L*Conjg(CVRL) + cK2R*Conjg(CVLR),dp) &
        & -4._dp/3._dp*Real(cK2L*Conjg(CVRR) + cK2R*Conjg(CVLL),dp)

   ! Mix: scalar x vector
   BRmix3 = 0._dp

   ! Mix: scalar x tensor
   BRmix4 = 0._dp

Else ! tau- -> l+ l'- l'-

   cK1L = 0._dp
   cK1R = 0._dp

   cK2L = 0._dp
   cK2R = 0._dp

   CSLL = O4lSLL(gt1,gt2,gt3,gt4)
   CSRR = O4lSRR(gt1,gt2,gt3,gt4)
   CSLR = O4lSLR(gt1,gt2,gt3,gt4)
   CSRL = O4lSRL(gt1,gt2,gt3,gt4)

   CVLL = O4lVLL(gt1,gt2,gt3,gt4)
   CVRR = O4lVRR(gt1,gt2,gt3,gt4)
   CVLR = O4lVLR(gt1,gt2,gt3,gt4)
   CVRL = O4lVRL(gt1,gt2,gt3,gt4)

   CVLL = CVLL + e2*cK1L
   CVRR = CVRR + e2*cK1R
   CVLR = CVLR + e2*cK1L
   CVRL = CVRL + e2*cK1R

   CTLL = O4lTLL(gt1,gt2,gt3,gt4)
   CTRR = O4lTRR(gt1,gt2,gt3,gt4)

   ! Photonic dipole contributions
   BRdipole = 0._dp
   
   ! Scalar contributions
   BRscalar = (Abs(CSLL)**2+Abs(CSRR)**2)/24._dp&
        &+(Abs(CSLR)**2+Abs(CSRL)**2)/12._dp

   ! Vector contributions
   BRvector = 2._dp*(Abs(CVLL)**2+Abs(CVRR)**2)/3._dp&
        & + (Abs(CVLR)**2+Abs(CVRL)**2)/3._dp

   ! Tensor contributions
   BRtensor = 6._dp*(Abs(CTLL)**2+Abs(CTRR)**2)

   ! Mix: dipole x scalar
   BRmix1 = 0._dp

   ! Mix: dipole x vector
   BRmix2 = 0._dp

   ! Mix: scalar x vector
   BRmix3 = -1._dp/3._dp*Real(CSLR*Conjg(CVLR) + CSRL*Conjg(CVRL),dp)

   ! Mix: scalar x tensor
   BRmix4 = -1._dp*Real(CSLL*Conjg(CTLL) + CSRR*Conjg(CTRR),dp)

End If

GammaLFV = oo512pi3*mf_l(gt1)**5* &
     & (e4*BRdipole + BRscalar + BRvector + BRtensor &
     & + e2*BRmix1 + e2*BRmix2 + BRmix3 + BRmix4)

!----------------------------------------------------------------------
!taking alpha(Q=0) instead of alpha(m_Z) as this contains most of the
!running of the Wilson coefficients
!----------------------------------------------------------------------

If (i1.Eq.1) Then
 BRtauToemumu=GammaLFV/GammaTau
Else If(i1.Eq.2) Then
 BRtauTomuee=GammaLFV/GammaTau
Else If(i1.Eq.3) Then
 BRtauToemumu2=GammaLFV/GammaTau
Else
 BRtauTomuee2=GammaLFV/GammaTau
End If

End do

 
 ! ###### End user defined body 
End Subroutine Calculate_LtoL1L2L2

Subroutine Calculate_MuEconversion(K1L,K1R,K2L,K2R,OllddSLL,OllddSRR,OllddSRL,        & 
& OllddSLR,OllddVRR,OllddVLL,OllddVRL,OllddVLR,OllddTLL,OllddTLR,OllddTRL,               & 
& OllddTRR,OlluuSLL,OlluuSRR,OlluuSRL,OlluuSLR,OlluuVRR,OlluuVLL,OlluuVRL,               & 
& OlluuVLR,OlluuTLL,OlluuTLR,OlluuTRL,OlluuTRR,CRmuEAl,CRmuETi,CRmuESr,CRmuESb,          & 
& CRmuEAu,CRmuEPb)

Implicit None 
Complex(dp) :: K1L(3,3),K1R(3,3),K2L(3,3),K2R(3,3),OllddSLL(3,3,3,3),OllddSRR(3,3,3,3),              & 
& OllddSRL(3,3,3,3),OllddSLR(3,3,3,3),OllddVRR(3,3,3,3),OllddVLL(3,3,3,3),               & 
& OllddVRL(3,3,3,3),OllddVLR(3,3,3,3),OllddTLL(3,3,3,3),OllddTLR(3,3,3,3),               & 
& OllddTRL(3,3,3,3),OllddTRR(3,3,3,3),OlluuSLL(3,3,3,3),OlluuSRR(3,3,3,3),               & 
& OlluuSRL(3,3,3,3),OlluuSLR(3,3,3,3),OlluuVRR(3,3,3,3),OlluuVLL(3,3,3,3),               & 
& OlluuVRL(3,3,3,3),OlluuVLR(3,3,3,3),OlluuTLL(3,3,3,3),OlluuTLR(3,3,3,3),               & 
& OlluuTRL(3,3,3,3),OlluuTRR(3,3,3,3)

Real(dp), Intent(out) :: CRmuEAl 
Real(dp), Intent(out) :: CRmuETi 
Real(dp), Intent(out) :: CRmuESr 
Real(dp), Intent(out) :: CRmuESb 
Real(dp), Intent(out) :: CRmuEAu 
Real(dp), Intent(out) :: CRmuEPb 

 
 ! #####+ Beging user defined body 
Complex(dp) :: gPLV(3), gPRV(3)
Complex(dp),Parameter :: mat0(3,3)=0._dp 
Real(dp) :: Znuc,Nnuc, Zeff, Fp, GammaCapt, GSp(3), GSn(3), &
     & GVp(3), GVn(3), e2
Complex(dp) :: Lcont,Rcont,gLS(3),gRS(3),gLV(3),gRV(3),g0LS,g0RS, & 
     & g0LV,g0RV,g1LS,g1RS,g1LV,g1RV 
Integer :: i1, i2

! ---------------------------------------------------------------- 
! Coherent mu-e conversion in nuclei
! Observable implemented by W. Porod, F. Staub and A. Vicente
! Based on Y. Kuno, Y. Okada, Rev. Mod. Phys. 73 (2001) 151 [hep-ph/9909265]
! and E. Arganda et al, JHEP 0710 (2007) 104 [arXiv:0707.2955]
! ---------------------------------------------------------------- 

e2 = 4._dp*Pi*Alpha_MZ

! 1: uu
! 2: dd
! 3: ss

! vector couplings

gLV(1) = 0.5_dp*(OlluuVLL(2,1,1,1) + OlluuVLR(2,1,1,1))
gRV(1) = 0.5_dp*(OlluuVRL(2,1,1,1) + OlluuVRR(2,1,1,1))
gLV(2) = 0.5_dp*(OllddVLL(2,1,1,1) + OllddVLR(2,1,1,1))
gRV(2) = 0.5_dp*(OllddVRL(2,1,1,1) + OllddVRR(2,1,1,1))
gLV(3) = 0.5_dp*(OllddVLL(2,1,2,2) + OllddVLR(2,1,2,2))
gRV(3) = 0.5_dp*(OllddVRL(2,1,2,2) + OllddVRR(2,1,2,2))

gLV = -gLV*Sqrt(2._dp)/G_F
gRV = -gRV*Sqrt(2._dp)/G_F

gPLV(1) = (K1L(2,1)-K2R(2,1))*(2._dp/3._dp) 
gPRV(1) = (K1R(2,1)-K2L(2,1))*(2._dp/3._dp) 
gPLV(2) = (K1L(2,1)-K2R(2,1))*(-1._dp/3._dp)  
gPRV(2) = (K1R(2,1)-K2L(2,1))*(-1._dp/3._dp)  
gPLV(3) = (K1L(2,1)-K2R(2,1))*(-1._dp/3._dp)  
gPRV(3) = (K1R(2,1)-K2L(2,1))*(-1._dp/3._dp) 
gPLV = gPLV*Sqrt(2._dp)/G_F*e2
gPRV = gPRV*Sqrt(2._dp)/G_F*e2

gLV=gPLV+gLV
gRV=gPRV+gRV


! scalar couplings

gLS(1) = 0.5_dp*(OlluuSLL(2,1,1,1)+OlluuSLR(2,1,1,1))
gRS(1) = 0.5_dp*(OlluuSRL(2,1,1,1)+OlluuSRR(2,1,1,1))
gLS(2) = 0.5_dp*(OllddSLL(2,1,1,1)+OllddSLR(2,1,1,1))
gRS(2) = 0.5_dp*(OllddSRL(2,1,1,1)+OllddSRR(2,1,1,1))
gLS(3) = 0.5_dp*(OllddSLL(2,1,2,2)+OllddSLR(2,1,2,2))
gRS(3) = 0.5_dp*(OllddSRL(2,1,2,2)+OllddSRR(2,1,2,2))

gLS = -gLS*Sqrt(2._dp)/G_F
gRS = -gRS*Sqrt(2._dp)/G_F


Do i1=1,6 
 If(i1.eq.1) Then 
Znuc=13._dp 
Nnuc=14._dp 
Zeff=11.5_dp 
Fp=0.64_dp 
GammaCapt=4.64079e-19_dp 
Else If(i1.eq.2) Then 
Znuc=22._dp 
Nnuc=26._dp 
Zeff=17.6_dp 
Fp=0.54_dp 
GammaCapt=1.70422e-18_dp 
Else If(i1.eq.3) Then 
Znuc=38._dp 
Nnuc=42._dp 
Zeff=25.0_dp 
Fp=0.39_dp 
GammaCapt=4.61842e-18_dp 
Else If(i1.eq.4) Then 
Znuc=51._dp 
Nnuc=70._dp 
Zeff=29.0_dp 
Fp=0.32_dp 
GammaCapt=6.71711e-18_dp 
Else If(i1.eq.5) Then 
Znuc=79._dp 
Nnuc=118._dp 
Zeff=33.5_dp 
Fp=0.16_dp 
GammaCapt=8.59868e-18_dp 
Else If(i1.eq.6) Then 
Znuc=82._dp 
Nnuc=125._dp 
Zeff=34.0_dp 
Fp=0.15_dp 
GammaCapt=8.84868e-18_dp 
End If 

! numerical values 
! based on Y. Kuno, Y. Okada, Rev. Mod. Phys. 73 (2001) 151 [hep-ph/9909265]
! and T. S. Kosmas et al, PLB 511 (2001) 203 [hep-ph/0102101]
GSp=(/5.1,4.3,2.5/) 
GSn=(/4.3,5.1,2.5/) 
GVp=(/2.0,1.0,0.0/) 
GVn=(/1.0,2.0,0.0/) 

g0LS=0._dp 
g0RS=0._dp 
g0LV=0._dp 
g0RV=0._dp 
g1LS=0._dp 
g1RS=0._dp 
g1LV=0._dp 
g1RV=0._dp 
Do i2=1,3
g0LS=g0LS+0.5_dp*gLS(i2)*(GSp(i2)+GSn(i2))
g0RS=g0RS+0.5_dp*gRS(i2)*(GSp(i2)+GSn(i2))
g0LV=g0LV+0.5_dp*gLV(i2)*(GVp(i2)+GVn(i2))
g0RV=g0RV+0.5_dp*gRV(i2)*(GVp(i2)+GVn(i2))
g1LS=g1LS+0.5_dp*gLS(i2)*(GSp(i2)-GSn(i2))
g1RS=g1RS+0.5_dp*gRS(i2)*(GSp(i2)-GSn(i2))
g1LV=g1LV+0.5_dp*gLV(i2)*(GVp(i2)-GVn(i2))
g1RV=g1RV+0.5_dp*gRV(i2)*(GVp(i2)-GVn(i2))
End Do
Lcont=(Znuc+Nnuc)*(g0LV+g0LS)+(Znuc-Nnuc)*(g1LV-g1LS) 
Rcont=(Znuc+Nnuc)*(g0RV+g0RS)+(Znuc-Nnuc)*(g1RV-g1RS)

! Conversion rate
If (i1.eq.1) Then
 CRMuEAl =oo8pi2*mf_l(2)**5*G_F**2*Alpha**3*Zeff**4*Fp**2/Znuc*& 
   & (Abs(Lcont)**2+Abs(Rcont)**2)/GammaCapt 
Else if (i1.eq.2) Then 
 CRMuETi =oo8pi2*mf_l(2)**5*G_F**2*Alpha**3*Zeff**4*Fp**2/Znuc*& 
   & (Abs(Lcont)**2+Abs(Rcont)**2)/GammaCapt 
Else if (i1.eq.3) Then 
 CRMuESr =oo8pi2*mf_l(2)**5*G_F**2*Alpha**3*Zeff**4*Fp**2/Znuc*& 
   & (Abs(Lcont)**2+Abs(Rcont)**2)/GammaCapt 
Else if (i1.eq.4) Then 
 CRMuESb =oo8pi2*mf_l(2)**5*G_F**2*Alpha**3*Zeff**4*Fp**2/Znuc*& 
   & (Abs(Lcont)**2+Abs(Rcont)**2)/GammaCapt 
Else if (i1.eq.5) Then 
 CRMuEAu =oo8pi2*mf_l(2)**5*G_F**2*Alpha**3*Zeff**4*Fp**2/Znuc*& 
   & (Abs(Lcont)**2+Abs(Rcont)**2)/GammaCapt 
Else if (i1.eq.6) Then 
 CRMuEPb =oo8pi2*mf_l(2)**5*G_F**2*Alpha**3*Zeff**4*Fp**2/Znuc*& 
   & (Abs(Lcont)**2+Abs(Rcont)**2)/GammaCapt 
End if
End do 

 
 ! ###### End user defined body 
End Subroutine Calculate_MuEconversion

Subroutine Calculate_TauLMeson(OllddSLL,OllddSRR,OllddSRL,OllddSLR,OllddVRR,          & 
& OllddVLL,OllddVRL,OllddVLR,OlluuSLL,OlluuSRR,OlluuSRL,OlluuSLR,OlluuVRR,               & 
& OlluuVLL,OlluuVRL,OlluuVLR,BrTautoEPi,BrTautoEEta,BrTautoEEtap,BrTautoMuPi,            & 
& BrTautoMuEta,BrTautoMuEtap)

Implicit None 
Complex(dp) :: OllddSLL(3,3,3,3),OllddSRR(3,3,3,3),OllddSRL(3,3,3,3),OllddSLR(3,3,3,3),              & 
& OllddVRR(3,3,3,3),OllddVLL(3,3,3,3),OllddVRL(3,3,3,3),OllddVLR(3,3,3,3),               & 
& OlluuSLL(3,3,3,3),OlluuSRR(3,3,3,3),OlluuSRL(3,3,3,3),OlluuSLR(3,3,3,3),               & 
& OlluuVRR(3,3,3,3),OlluuVLL(3,3,3,3),OlluuVRL(3,3,3,3),OlluuVLR(3,3,3,3)

Real(dp), Intent(out) :: BrTautoEPi 
Real(dp), Intent(out) :: BrTautoEEta 
Real(dp), Intent(out) :: BrTautoEEtap 
Real(dp), Intent(out) :: BrTautoMuPi 
Real(dp), Intent(out) :: BrTautoMuEta 
Real(dp), Intent(out) :: BrTautoMuEtap 

 
 ! #####+ Beging user defined body 
Real(dp) :: Fpi, thetaEta, mPi, mK, mEta, mEtap, meson_abs_T2, cont, &
     & mP, CP, factor, BR
Complex(dp) :: BSLL, BSLR, BSRL, BSRR, BVLL, BVLR, BVRL, BVRR, &
     & CSLL, CSLR, CSRL, CSRR, CVLL, CVLR, CVRL, CVRR, aP(2), bP(2), &
     & DLdP, DRdP, DLuP, DRuP
Integer :: i1, i2, out, k1, k2

! ---------------------------------------------------------------- 
! tau -> l meson
! Observable implemented by W. Porod, F. Staub and A. Vicente
! Generalizes the analytical expressions in
! E. Arganda et al, JHEP 0806 (2008) 079 [arXiv:0803.2039]
! ---------------------------------------------------------------- 

Fpi=0.0924_dp! Pion decay constant in GeV 
thetaEta=-Pi/10._dp! eta-eta' mixing angle 
mPi=0.13497_dp! Pion mass in GeV 
mK=0.49761_dp! Kaon mass in GeV 
mEta=0.548_dp! Eta mass in GeV 
mEtap=0.958_dp! Eta' mass in GeV 

!Mesons:
!1:Pi0 
!2:Eta 
!3:Eta' 
Do i1=1,3 
   If(i1.eq.1) Then !1:Pi0 
      mP = mPi 
      CP = 1._dp 
      DLdP = - mPi**2/4._dp
      DRdP = - Conjg(DLdP)
      DLuP = mPi**2/4._dp
      DRuP = - Conjg(DLuP)
   Else If(i1.eq.2) Then !2:Eta 
      mP = mEta 
      CP = (Sin(thetaEta)+Sqrt(2._dp)*Cos(thetaEta))/Sqrt(6._dp) 
      DLdP = 1._dp/(4._dp*Sqrt(3._dp))*((3._dp*mPi**2-4._dp*mK**2) &
        & *Cos(thetaEta)-2._dp*Sqrt(2._dp)*mK**2*Sin(thetaEta))
      DRdP = - Conjg(DLdP)
      DLuP = 1._dp/(4._dp*Sqrt(3._dp))*mPi**2*(Cos(thetaEta)       &
        & -Sqrt(2._dp)*Sin(thetaEta))
      DRuP = - Conjg(DLuP)
   Else If(i1.eq.3) Then !3:Eta' 
      mP = mEtap 
      CP = (Sqrt(2._dp)*Sin(thetaEta)-Cos(thetaEta))/Sqrt(6._dp) 
      DLdP = 1._dp/(4._dp*Sqrt(3._dp))*((3._dp*mPi**2-4._dp*mK**2) & 
        & *Sin(thetaEta)+2._dp*Sqrt(2._dp)*mK**2*Cos(thetaEta))
      DRdP = - Conjg(DLdP)
      DLuP = 1._dp/(4._dp*Sqrt(3._dp))*mPi**2*(Sin(thetaEta)+      &
        & Sqrt(2._dp)*Cos(thetaEta))
      DRuP = - Conjg(DLuP)
   End If

!Leptons:
!1:e
!2:mu 
Do i2=1,2 
If (i2.eq.1) Then         ! tau -> e P
 out = 1
Elseif (i2.eq.2) Then     ! tau -> mu P
 out = 2
End if

! d-quark coefficients

BSLL = OllddSLL(3,out,1,1)
BSLR = OllddSLR(3,out,1,1)
BSRL = OllddSRL(3,out,1,1)
BSRR = OllddSRR(3,out,1,1)
BVLL = OllddVLL(3,out,1,1)
BVLR = OllddVLR(3,out,1,1)
BVRL = OllddVRL(3,out,1,1)
BVRR = OllddVRR(3,out,1,1)

! u-quark coefficients

CSLL = OlluuSLL(3,out,1,1)
CSLR = OlluuSLR(3,out,1,1)
CSRL = OlluuSRL(3,out,1,1)
CSRR = OlluuSRR(3,out,1,1)
CVLL = OlluuVLL(3,out,1,1)
CVLR = OlluuVLR(3,out,1,1)
CVRL = OlluuVRL(3,out,1,1)
CVRR = OlluuVRR(3,out,1,1)

! aP, bP scalar
aP(1) = Fpi/2._dp*(DLdP/mf_d(1)*(BSLL+BSRL) + DRdP/mf_d(1)*(BSLR+BSRR) &
         & + DLuP/mf_u(1)*(CSLL+CSRL) + DRuP/mf_u(1)*(CSLR+CSRR))
bP(1) = Fpi/2._dp*(DLdP/mf_d(1)*(BSRL-BSLL) + DRdP/mf_d(1)*(BSRR-BSLR) &
         & + DLuP/mf_u(1)*(CSRL-CSLL) + DRuP/mf_u(1)*(CSRR-CSLR))

! aP, bP vector
aP(2) = Fpi/4._dp*CP*(mf_l(3)-mf_l(out))*(-BVLL+BVLR-BVRL+BVRR+        &
         & CVLL-CVLR+CVRL-CVRR)
bP(2) = Fpi/4._dp*CP*(mf_l(3)+mf_l(out))*(-BVLL+BVLR+BVRL-BVRR+        &
         & CVLL-CVLR-CVRL+CVRR)

! averaged squared amplitude 
meson_abs_T2=0._dp 
Do k1=1,2 
   Do k2=1,2 
      cont=2._dp*mf_l(out)*mf_l(3)*(aP(k1)*conjg(aP(k2))               &
           & -bP(k1)*conjg(bP(k2)))+                                   & 
           & (mf_l(3)**2+mf_l(out)**2-mP**2)*(aP(k1)*conjg(aP(k2))+    &
           & bP(k1)*conjg(bP(k2))) 
      meson_abs_T2=meson_abs_T2+cont 
   End Do
End Do
meson_abs_T2=meson_abs_T2/(2._dp*mf_l(3)) 

! branching ratio 
factor=oo4pi*Sqrt(lamb(mf_l(3)**2,mf_l(out)**2,mP**2))                 &
            & /(mf_l(3)**2*GammaTau)*0.5_dp
BR=factor*meson_abs_T2
If (i1.eq.1) Then !pi
   If(i2.eq.1) Then 
      BrTautoEPi = BR
   Else
      BrTautoMuPi = BR
   End If
Elseif (i1.eq.2) Then !eta
   If(i2.eq.1) Then 
      BrTautoEEta = BR
   Else
      BrTautoMuEta = BR
   End If
Else !eta'
   If(i2.eq.1) Then 
      BrTautoEEtap = BR
   Else
      BrTautoMuEtap = BR
   End If
End if

End Do
End Do

Contains 

Real(dp) Function lamb(x,y,z) 
Real(dp),Intent(in)::x,y,z 
 lamb=(x+y-z)**2-4._dp*x*y 
End Function lamb 

 
 ! ###### End user defined body 
End Subroutine Calculate_TauLMeson

Subroutine Calculate_ZLLp(OZ2lSL,OZ2lSR,OZ2lVL,OZ2lVR,BrZtoMuE,BrZtoTauE,             & 
& BrZtoTauMu)

Implicit None 
Complex(dp) :: OZ2lSL(3,3),OZ2lSR(3,3),OZ2lVL(3,3),OZ2lVR(3,3)

Real(dp), Intent(out) :: BrZtoMuE 
Real(dp), Intent(out) :: BrZtoTauE 
Real(dp), Intent(out) :: BrZtoTauMu 

 
 ! #####+ Beging user defined body 
Real(dp) :: width
Integer :: i1, gt1, gt2

! ---------------------------------------------------------------- 
! Z -> l l'
! Observable implemented by W. Porod, F. Staub and A. Vicente
! Based on X. -J. Bi et al, PRD 63 (2001) 096008 [hep-ph/0010270]
! ---------------------------------------------------------------- 

Do i1=1,3 

If (i1.eq.1) Then         ! Z -> e mu
 gt1 = 1
 gt2 = 2
Elseif (i1.eq.2) Then     !Z -> e tau
 gt1 = 1
 gt2 = 3
Else                      ! Z -> mu tau
 gt1 = 2
 gt2 = 3
End if

! decay width
width = oo48pi*(2*(Abs(OZ2lVL(gt1,gt2))**2 +            &
  &                    Abs(OZ2lVR(gt1,gt2))**2)*mZ      & 
  & + (Abs(OZ2lSL(gt1,gt2))**2+Abs(OZ2lSR(gt1,gt2))**2) &
  & * mZ * mZ2 * 0.25_dp) 

If (i1.eq.1) Then
BrZtoMuE = width/(width+gamZ)
Elseif (i1.eq.2) Then 
BrZtoTauE = width/(width+gamZ)
Else
BrZtoTauMu = width/(width+gamZ)
End if

End do

 
 ! ###### End user defined body 
End Subroutine Calculate_ZLLp

Subroutine Calculate_B0toLL(OddllSLL,OddllSRR,OddllSRL,OddllSLR,OddllVRR,             & 
& OddllVLL,OddllVRL,OddllVLR,OddllSLLSM,OddllSRRSM,OddllSRLSM,OddllSLRSM,OddllVRRSM,     & 
& OddllVLLSM,OddllVRLSM,OddllVLRSM,BrB0dEE,ratioB0dEE,BrB0sEE,ratioB0sEE,BrB0dMuMu,      & 
& ratioB0dMuMu,BrB0sMuMu,ratioB0sMuMu,BrB0dTauTau,ratioB0dTauTau,BrB0sTauTau,            & 
& ratioB0sTauTau)

Implicit None 
Complex(dp) :: OddllSLL(3,3,3,3),OddllSRR(3,3,3,3),OddllSRL(3,3,3,3),OddllSLR(3,3,3,3),              & 
& OddllVRR(3,3,3,3),OddllVLL(3,3,3,3),OddllVRL(3,3,3,3),OddllVLR(3,3,3,3),               & 
& OddllSLLSM(3,3,3,3),OddllSRRSM(3,3,3,3),OddllSRLSM(3,3,3,3),OddllSLRSM(3,3,3,3),       & 
& OddllVRRSM(3,3,3,3),OddllVLLSM(3,3,3,3),OddllVRLSM(3,3,3,3),OddllVLRSM(3,3,3,3)

Real(dp), Intent(out) :: BrB0dEE 
Real(dp), Intent(out) :: ratioB0dEE 
Real(dp), Intent(out) :: BrB0sEE 
Real(dp), Intent(out) :: ratioB0sEE 
Real(dp), Intent(out) :: BrB0dMuMu 
Real(dp), Intent(out) :: ratioB0dMuMu 
Real(dp), Intent(out) :: BrB0sMuMu 
Real(dp), Intent(out) :: ratioB0sMuMu 
Real(dp), Intent(out) :: BrB0dTauTau 
Real(dp), Intent(out) :: ratioB0dTauTau 
Real(dp), Intent(out) :: BrB0sTauTau 
Real(dp), Intent(out) :: ratioB0sTauTau 

 
 ! #####+ Beging user defined body 
Real(dp) :: AmpSquared,AmpSquared2, AmpSquared_SM, AmpSquared2_SM, &
              & width_SM, width
Real(dp) :: MassB0s, MassB0d, fBs, fBd, TauB0s, TauB0d 
Real(dp) :: hbar=6.58211899E-25_dp 
Real(dp) :: MassB0,MassB02,fB0,GammaB0 
Complex(dp) :: CS(4), CV(4), CT(4)
Complex(dp) :: FS=0._dp, FP=0._dp, FV=0._dp, FA=0._dp 
Integer :: i1, gt1, gt2, gt3, gt4

! ---------------------------------------------------------------- 
! B0 -> l l
! Observable implemented by W. Porod, F. Staub and A. Vicente
! Based on A. Dedes et al, PRD 79 (2009) 055006 [arXiv:0812.4320]
! ---------------------------------------------------------------- 

! Using global hadronic data
fBd = f_B0d_CONST  
fBs = f_B0s_CONST  
TauB0d = tau_B0d 
TauB0s = tau_B0s
MassB0d = mass_B0d 
MassB0s = mass_B0s 

Do i1=1,6
gt1 = 3
If (i1.eq.1) Then ! B0d -> e+ e-
  MassB0 = MassB0d
  MassB02 = MassB0d**2
  fB0 = fBd
  GammaB0 = (hbar)/(TauB0d)
  gt2 = 1
  gt3 = 1
  gt4 = 1
Else if (i1.eq.2) Then ! B0s -> e+ e-
  MassB0 = MassB0s
  MassB02 = MassB0s**2
  fB0 = fBs
  GammaB0 = (hbar)/(TauB0s)
  gt2 = 2
  gt3 = 1
  gt4 = 1
Else if (i1.eq.3) Then ! B0d -> mu+ mu-
  MassB0 = MassB0d
  MassB02 = MassB0d**2
  fB0 = fBd
  GammaB0 = (hbar)/(TauB0d)
  gt2 = 1
  gt3 = 2
  gt4 = 2
Else if (i1.eq.4) Then ! B0s -> mu+ mu-
  MassB0 = MassB0s
  MassB02 = MassB0s**2 
  fB0 = fBs
  GammaB0 = (hbar)/(TauB0s)
  gt2 = 2
  gt3 = 2
  gt4 = 2
Else if (i1.eq.5) Then ! B0d -> tau+ tau-
  MassB0 = MassB0d
  MassB02 = MassB0d**2
  fB0 = fBd
  GammaB0 = (hbar)/(TauB0d)
  gt2 = 1
  gt3 = 3
  gt4 = 3
Else if (i1.eq.6) Then ! B0s -> tau+ tau-
  MassB0 = MassB0s
  MassB02 = MassB0s**2 
  fB0 = fBs
  GammaB0 = (hbar)/(TauB0s)
  gt2 = 2
  gt3 = 3
  gt4 = 3
End if

! BSM contributions

CS(1) = OddllSRR(gt1,gt2,gt3,gt4)
CS(2) = OddllSRL(gt1,gt2,gt3,gt4)
CS(3) = OddllSLL(gt1,gt2,gt3,gt4)
CS(4) = OddllSLR(gt1,gt2,gt3,gt4)

CV(1) = OddllVLL(gt1,gt2,gt3,gt4)
CV(2) = OddllVLR(gt1,gt2,gt3,gt4)
CV(3) = OddllVRR(gt1,gt2,gt3,gt4)
CV(4) = OddllVRL(gt1,gt2,gt3,gt4)

FS= 0.25_dp*MassB02*fB0/(MFd(gt1)+MFd(gt2))*( CS(1)+CS(2)-CS(3)-CS(4)) 
FP= 0.25_dp*MassB02*fB0/(MFd(gt1)+MFd(gt2))*(-CS(1)+CS(2)-CS(3)+CS(4)) 
FV= -0.25_dp*fB0*( CV(1)+CV(2)-CV(3)-CV(4)) 
FA= -0.25_dp*fB0*(-CV(1)+CV(2)-CV(3)+CV(4)) 

AmpSquared = 2 * abs(FS)**2 * (MassB02 - (mf_l(gt3)+mf_l(gt4))**2) &
     & + 2 *abs(FP)**2 * (MassB02 - (mf_l(gt3)-mf_l(gt4))**2) &
     & + 2 *abs(FV)**2 * (MassB02*(mf_l(gt4)-mf_l(gt3))**2    &
             & - (mf_l2(gt4)-mf_l2(gt3))**2) &
     & + 2 *abs(FA)**2 * (MassB02*(mf_l(gt4)+mf_l(gt3))**2 -  &
             & (mf_l2(gt4)-mf_l2(gt3))**2) &
     & + 4 *REAL(FS*conjg(FV)) *(mf_l(gt3)-mf_l(gt4)) *(MassB02 &
             & + (mf_l(gt3)+mf_l(gt4))**2) &
     & + 4 *REAL(FP*conjg(FA)) *(mf_l(gt3)+mf_l(gt4)) *(MassB02 &
             & - (mf_l(gt3)-mf_l(gt4))**2) 

width = oo16pi * AmpSquared / MassB0 * &
    & sqrt(1-((mf_l(gt4)+mf_l(gt3))/MassB0)**2) &
    & * sqrt(1-((mf_l(gt4)-mf_l(gt3))/MassB0)**2)*(Alpha/Alpha_160)**4


! SM contributions

CS(1) = OddllSRRSM(gt1,gt2,gt3,gt4)
CS(2) = OddllSRLSM(gt1,gt2,gt3,gt4)
CS(3) = OddllSLLSM(gt1,gt2,gt3,gt4)
CS(4) = OddllSLRSM(gt1,gt2,gt3,gt4)

CV(1) = OddllVLLSM(gt1,gt2,gt3,gt4)
CV(2) = OddllVLRSM(gt1,gt2,gt3,gt4)
CV(3) = OddllVRRSM(gt1,gt2,gt3,gt4)
CV(4) = OddllVRLSM(gt1,gt2,gt3,gt4)

FS= 0.25_dp*MassB02*fB0/(MFd(gt1)+MFd(gt2))*( CS(1)+CS(2)-CS(3)-CS(4)) 
FP= 0.25_dp*MassB02*fB0/(MFd(gt1)+MFd(gt2))*(-CS(1)+CS(2)-CS(3)+CS(4)) 
FV= -0.25_dp*fB0*( CV(1)+CV(2)-CV(3)-CV(4)) 
FA= -0.25_dp*fB0*(-CV(1)+CV(2)-CV(3)+CV(4)) 

AmpSquared = 2 * abs(FS)**2 * (MassB02 - (mf_l(gt3)+mf_l(gt4))**2) &
     & + 2 *abs(FP)**2 * (MassB02 - (mf_l(gt3)-mf_l(gt4))**2) &
     & + 2 *abs(FV)**2 * (MassB02*(mf_l(gt4)-mf_l(gt3))**2 -  &
        &  (mf_l2(gt4)-mf_l2(gt3))**2) &
     & + 2 *abs(FA)**2 * (MassB02*(mf_l(gt4)+mf_l(gt3))**2 -  &
        &  (mf_l2(gt4)-mf_l2(gt3))**2) &
     & + 4 *REAL(FS*conjg(FV)) *(mf_l(gt3)-mf_l(gt4)) *(MassB02 &
        & + (mf_l(gt3)+mf_l(gt4))**2) &
     & + 4 *REAL(FP*conjg(FA)) *(mf_l(gt3)+mf_l(gt4)) *(MassB02 &
        & - (mf_l(gt3)-mf_l(gt4))**2)

width_SM = oo16pi * AmpSquared / MassB0 * sqrt(1-((mf_l(gt4)+   &
     & mf_l(gt3))/MassB0)**2) &
     & * sqrt(1-((mf_l(gt4)-mf_l(gt3))/MassB0)**2)*(Alpha/Alpha_160)**4 


If (i1.Eq.1) Then
  BrB0dEE= width / GammaB0
  ratioB0dEE= width / width_SM
Else If (i1.Eq.2) Then
  BrB0sEE= width / GammaB0
  ratioB0sEE= width / width_SM
Else If (i1.Eq.3) Then
  BrB0dMuMu= width / GammaB0
  ratioB0dMuMu= width / width_SM
Else If (i1.Eq.4) Then
  BrB0sMuMu= width / GammaB0
  ratioB0sMuMu= width / width_SM
Else If (i1.Eq.5) Then
  BrB0dTauTau= width / GammaB0
  ratioB0dTauTau= width / width_SM
Else If (i1.Eq.6) Then
  BrB0sTauTau= width / GammaB0
  ratioB0sTauTau= width / width_SM
End If

End do

 

 
 ! ###### End user defined body 
End Subroutine Calculate_B0toLL

Subroutine Calculate_bsGamma(CC7,CC7p,CC8,CC8p,CC7SM,CC7pSM,CC8SM,CC8pSM,             & 
& BrBsGamma,ratioBsGamma)

Implicit None 
Complex(dp) :: CC7(3,3),CC7p(3,3),CC8(3,3),CC8p(3,3),CC7SM(3,3),CC7pSM(3,3),CC8SM(3,3),              & 
& CC8pSM(3,3)

Real(dp), Intent(out) :: BrBsGamma 
Real(dp), Intent(out) :: ratioBsGamma 

 
 ! #####+ Beging user defined body 
Integer :: gt1, gt2
Complex(dp) :: norm, delta_C7_0, delta_C7p_0, delta_C8_0, delta_C8p_0
Real(dp) :: NNLO_SM 

! ---------------------------------------------------------------- 
! \bar{B} -> X_s gamma (Egamma > 1.6 GeV)
! Observable implemented by W. Porod, F. Staub and A. Vicente
! Based on E. Lunghi, J. Matias, JHEP 0704 (2007) 058 [hep-ph/0612166]
! ---------------------------------------------------------------- 

gt1=3 !b
gt2=2 !s

! normalization of our Wilson coefficients
! relative to the ones used in hep-ph/0612166
norm = -CKM_160(3,3)*Conjg(CKM_160(gt1,gt2))*Alpha_160/ &
         & (8._dp*Pi*sinW2_160*mW2)

! Wilson coefficients
delta_C7_0 =(CC7(gt1,gt2)-CC7SM(gt1,gt2))/norm
delta_C7p_0=(CC7p(gt1,gt2)-CC7pSM(gt1,gt2))/norm
delta_C8_0 =(CC8(gt1,gt2)-CC8SM(gt1,gt2))/norm
delta_C8p_0=(CC8p(gt1,gt2)-CC8pSM(gt1,gt2))/norm

! NNLO SM prediction
! as obtained in M. Misiak et al, PRL 98 (2007) 022002
! and M. Misiak and M. Steinhauser, NPB 764 (2007) 62
NNLO_SM=3.15_dp

BrBsGamma=NNLO_SM+4.743_dp*(Abs(delta_C7_0)**2+Abs(delta_C7p_0)**2)&
&+0.789_dp*(Abs(delta_C8_0)**2+Abs(delta_C8p_0)**2)&
&+Real((-7.184_dp,0.612_dp)*delta_C7_0&
&+(-2.225_dp,-0.557_dp)*delta_C8_0+(2.454_dp,-0.884_dp)*&
&(delta_C7_0*conjg(delta_C8_0)+delta_C7p_0*conjg(delta_C8p_0)),dp)

! ratio BSM/SM
ratioBsGamma = BrBsGamma/NNLO_SM

! branching ratio
BrBsGamma=1E-4_dp*BrBsGamma



 
 ! ###### End user defined body 
End Subroutine Calculate_bsGamma

Subroutine Calculate_BtoKLL(OddllVRR,OddllVLL,OddllVRL,OddllVLR,CC7,CC7p,             & 
& OddllVRRSM,OddllVLLSM,OddllVRLSM,OddllVLRSM,CC7SM,CC7pSM,BrBtoKmumu,ratioBtoKmumu)

Implicit None 
Complex(dp) :: OddllVRR(3,3,3,3),OddllVLL(3,3,3,3),OddllVRL(3,3,3,3),OddllVLR(3,3,3,3),              & 
& CC7(3,3),CC7p(3,3),OddllVRRSM(3,3,3,3),OddllVLLSM(3,3,3,3),OddllVRLSM(3,3,3,3),        & 
& OddllVLRSM(3,3,3,3),CC7SM(3,3),CC7pSM(3,3)

Real(dp), Intent(out) :: BrBtoKmumu 
Real(dp), Intent(out) :: ratioBtoKmumu 

 
 ! #####+ Beging user defined body 
Complex(dp) :: c7NP, c7p, c9NP, c9p, c10NP, c10p, norm
Real(dp) ::  GF

! ---------------------------------------------------------------- 
! B^+ -> K^+ l+ l- (14.18 GeV^2 < q^2 < 22 GeV^2)
! Observable implemented by W. Porod, F. Staub and A. Vicente
! Based on W. Altmannshofer, D. M. Straub, EPJ C 73 (2013) 2646
! [arXiv:1308.1501]
! ---------------------------------------------------------------- 

c7NP = (CC7(3,2) - CC7SM(3,2))
c7p = CC7p(3,2)
c9NP = 0.5_dp*(OddllVLL(3,2,1,1)+OddllVLR(3,2,1,1) - &
            & (OddllVLLSM(3,2,1,1)+OddllVLRSM(3,2,1,1)))
c9p =  0.5_dp*(OddllVRR(3,2,1,1)+OddllVRL(3,2,1,1))
c10NP = -0.5_dp*(OddllVLL(3,2,1,1)-OddllVLR(3,2,1,1) - &
            &  (OddllVLLSM(3,2,1,1)-OddllVLRSM(3,2,1,1)))
c10p = 0.5_dp*(OddllVRR(3,2,1,1)-OddllVRL(3,2,1,1))


! running GF
GF = (Alpha_160*4._dp*Pi/sinW2_160)/mw**2*sqrt2/8._dp

! normalization of our Wilson coefficients
! relative to the ones used in arXiv:1308.1501
norm = - Alpha_160/Pi*GF/sqrt2*CKM_160(3,3)*Conjg(CKM_160(3,2))

! Branching ratio in the high-q^2 region
! q^2 in [14.18,22] GeV^2
BrBtoKmumu = (1.11_dp + 0.22_dp*(c7Np+c7p)/norm + &
   & 0.27_dp*(c9NP+c9p)/norm - 0.27_dp*(c10NP+c10p)/norm)

! ratio relative to SM
ratioBtoKmumu = BrBtoKmumu/1.11_dp

! total BR
BrBtoKmumu = BrBtoKmumu*1.0E-7_dp


 
 ! ###### End user defined body 
End Subroutine Calculate_BtoKLL

Subroutine Calculate_BtoQnunu(OddvvVRR,OddvvVLL,OddvvVRL,OddvvVLR,OddvvVRRSM,         & 
& OddvvVLLSM,OddvvVRLSM,OddvvVLRSM,BrBtoSnunu,ratioBtoSnunu,BrBtoDnunu,ratioBtoDnunu)

Implicit None 
Complex(dp) :: OddvvVRR(3,3,3,3),OddvvVLL(3,3,3,3),OddvvVRL(3,3,3,3),OddvvVLR(3,3,3,3),              & 
& OddvvVRRSM(3,3,3,3),OddvvVLLSM(3,3,3,3),OddvvVRLSM(3,3,3,3),OddvvVLRSM(3,3,3,3)

Real(dp), Intent(out) :: BrBtoSnunu 
Real(dp), Intent(out) :: ratioBtoSnunu 
Real(dp), Intent(out) :: BrBtoDnunu 
Real(dp), Intent(out) :: ratioBtoDnunu 

 
 ! #####+ Beging user defined body 
Complex(dp) :: cL, cR, br, br_SM, cL_SM, cR_SM, norm
Real(dp) :: f_mq, tf_mq, kappa_0, kappa_c, f_mc, BrBXeNu, sw2, mq
Real(dp) :: prefactor, factor1, factor2, GF
Integer :: out, i1, i2 

! ---------------------------------------------------------------- 
! \bar{B} -> X_{d,s} nu nu
! Observable implemented by W. Porod, F. Staub and A. Vicente
! Based on C. Bobeth et al, NPB 630 (2002) 87 [hep-ph/0112305] 
! ---------------------------------------------------------------- 

kappa_0 = 0.830_dp
kappa_c = 0.88_dp
f_mc = 0.53_dp
BrBXeNu = 0.101_dp ! PDG central value

sw2 = sinw2_160
GF = (Alpha_160*4._dp*Pi/sinW2_160)/mw**2*sqrt2/8._dp

Do out = 1,2
If (out.eq.1) Then ! B -> X_d nu nu
 mq = mf_d(1)/mf_d(3)
 norm = Alpha_160*4._dp*GF/sqrt2/(2._dp*pi*sinw2_160)* &
             & Conjg(CKM_160(3,3)*Conjg( CKM_160(3,1) ))
Else ! B -> X_s nu nu
 mq = mf_d(2)/mf_d(3)
 norm = Alpha_160*4._dp*GF/sqrt2/(2._dp*pi*sinw2_160)* &
             & Conjg(CKM_160(3,3)*Conjg( CKM_160(3,2) ))
End if 

! f and tilde f functions
f_mq = 1._dp - 8._dp*mq**2 + 8._dp*mq**6 - &
            & mq**8 -24._dp*mq**4*Log(mq)
tf_mq = 1._dp + 9._dp*mq**2 - 9._dp*mq**4 - mq**6 + &
            & 12._dp*mq**2*(1._dp + mq**2)*Log(mq)

prefactor =  Alpha_mz**2/(4._dp*pi**2*sw2**2)*Abs(CKM_160(3,3)/ &
               & CKM_160(2,3))**2*BrBXeNu/(f_mc*kappa_c)*kappa_0
factor1 = f_mq
factor2 = - 4._dp*mq*tf_mq

br = 0._dp
br_SM = 0._dp

 Do i1= 1,3
  Do i2 = 1,3

   ! BSM
   cL = OddvvVLL(3,out,i1,i2)/norm
   cR = OddvvVRL(3,out,i1,i2)/norm
   br = br + factor1*(Abs(cL)**2 + Abs(cR)**2) +    &
               &  factor2*Real(cL*Conjg(cR),dp)

   ! SM
   cL = OddvvVLLSM(3,out,i1,i2)/norm
   cR = OddvvVRLSM(3,out,i1,i2)/norm
   br_SM = br_SM + factor1*(Abs(cL)**2 + Abs(cR)**2) + &
            & factor2*Real(cL*Conjg(cR),dp)

  End Do
 End do
If (out.eq.1) Then ! B -> X_d nu nu
  BrBtoDnunu = prefactor*br*Abs(CKM_160(3,1))**2 
  ratioBtoDnunu = br/br_SM
Else ! B -> X_s nu nu
  BrBtoSnunu = prefactor*br*Abs(CKM_160(3,2))**2  
  ratioBtoSnunu = br/br_SM
End if 
End Do

 
 ! ###### End user defined body 
End Subroutine Calculate_BtoQnunu

Subroutine Calculate_BtoSLL(OddllVRR,OddllVLL,OddllVRL,OddllVLR,CC7,CC7p,             & 
& CC8,CC8p,OddllVRRSM,OddllVLLSM,OddllVRLSM,OddllVLRSM,CC7SM,CC7pSM,CC8SM,               & 
& CC8pSM,BrBtoSEE,ratioBtoSEE,BrBtoSMuMu,ratioBtoSMuMu)

Implicit None 
Complex(dp) :: OddllVRR(3,3,3,3),OddllVLL(3,3,3,3),OddllVRL(3,3,3,3),OddllVLR(3,3,3,3),              & 
& CC7(3,3),CC7p(3,3),CC8(3,3),CC8p(3,3),OddllVRRSM(3,3,3,3),OddllVLLSM(3,3,3,3),         & 
& OddllVRLSM(3,3,3,3),OddllVLRSM(3,3,3,3),CC7SM(3,3),CC7pSM(3,3),CC8SM(3,3),             & 
& CC8pSM(3,3)

Real(dp), Intent(out) :: BrBtoSEE 
Real(dp), Intent(out) :: ratioBtoSEE 
Real(dp), Intent(out) :: BrBtoSMuMu 
Real(dp), Intent(out) :: ratioBtoSMuMu 

 
 ! #####+ Beging user defined body 
Complex(dp) :: c7(2), c7p(2), c8(2), c8p(2), r7, r7p, r8, r8p, norm, &
     & r9(2), r9p(2), r10(2), r10p(2),                               & 
     & c9ee(2), c9pee(2), c10ee(2), c10pee(2),                       &
     & c9_cee(2), c9p_cee(2), c10_cee(2), c10p_cee(2),               &
     & c9mm(2), c9pmm(2), c10mm(2), c10pmm(2), c9_cmm(2),            &
     & c9p_cmm(2), c10_cmm(2), c10p_cmm(2) 

! ---------------------------------------------------------------- 
! \bar{B} -> X_s l+ l-
! Observable implemented by W. Porod, F. Staub and A. Vicente
! Based on T. Huber et al, NPB 740 (2006) 105, [hep-ph/0512066]
! Prime operators added after private communication with E. Lunghi
! ---------------------------------------------------------------- 

! Wilson coefficients

c7(1) = CC7(3,2)
c7(2) =  CC7SM(3,2)
c7p(1) = CC7p(3,2)
c7p(2) = CC7pSM(3,2)

c8(1) = CC8(3,2)
c8(2) = CC8SM(3,2)
c8p(1) = CC8p(3,2)
c8p(2) = CC8pSM(3,2)

c9ee(1) = OddllVLL(3,2,1,1)+OddllVLR(3,2,1,1)
c9ee(2) = (OddllVLLSM(3,2,1,1)+OddllVLRSM(3,2,1,1))
c9mm(1) = OddllVLL(3,2,2,2)+OddllVLR(3,2,2,2)
c9mm(2) =  (OddllVLLSM(3,2,2,2)+OddllVLRSM(3,2,2,2))
c9pee(1) = OddllVRR(3,2,1,1)+OddllVRL(3,2,1,1)
c9pee(2) =  (OddllVRRSM(3,2,1,1)+OddllVRLSM(3,2,1,1))
c9pmm(1) = OddllVRR(3,2,2,2)+OddllVRL(3,2,2,2)
c9pmm(2) =  (OddllVRRSM(3,2,2,2)+OddllVRLSM(3,2,2,2))

c10ee(1) = OddllVLL(3,2,1,1)-OddllVLR(3,2,1,1)
c10ee(2) =  (OddllVLLSM(3,2,1,1)-OddllVLRSM(3,2,1,1))
c10mm(1) = OddllVLL(3,2,2,2)-OddllVLR(3,2,2,2)
c10mm(2) =  (OddllVLLSM(3,2,2,2)-OddllVLRSM(3,2,2,2))
c10pee(1) = OddllVRR(3,2,1,1)-OddllVRL(3,2,1,1)
c10pee(2) =  (OddllVRRSM(3,2,1,1)-OddllVRLSM(3,2,1,1))
c10pmm(1) = OddllVRR(3,2,2,2)-OddllVRL(3,2,2,2)
c10pmm(2) = (OddllVRRSM(3,2,2,2)-OddllVRLSM(3,2,2,2))

! ratios

r7 = c7(1) / c7(2)
r7p = c7p(1) / c7(2)
r8 = c8(1) / c8(2)
r8p = c8p(1) / c8(2)

r9(1) = c9ee(1)/c9ee(2)
r9(2) = c9mm(1)/c9mm(2)
r9p(1) = c9pee(1)/c9ee(2)
r9p(2) = c9pmm(1)/c9mm(2)

r10(1) = c10ee(1)/c10ee(2)
r10(2) = c10mm(1)/c10mm(2)
r10p(1) = c10pee(1)/c10ee(2)
r10p(2) = c10pmm(1)/c10mm(2)

BrBtoSEE = (2.3148_dp - 1.658e-3_dp * Aimag(R10(1))                   &
 & + 5.e-4_dp * Aimag(r10(1)*Conjg(r8) + r10p(1)*Conjg(r8p) )         &
 & + 5.23e-2_dp * Aimag(r7) + 5.18e-3_dp * Aimag(r8)                  &
 & + 2.266e-2_dp * Aimag(r7 * Conjg(r8) + r7p * Conjg(r8p) )          &
 & + 4.96e-3_dp * Aimag(r7 * Conjg(r9(1)) + r7p * Conjg(r9p(1)) )     &
 & + 2.61e-2_dp * Aimag(r8 * Conjg(r9(1)) + r8p * Conjg(r9p(1)) )     &
 & - 6.21e-3_dp * Aimag(r9(1)) - 0.5420_dp * Real( r10(1), dp)        &
 & - 3.340e-2_dp * Real(r7,dp) - 1.35e-2_dp * Real(r8,dp)             &
 & + 1.53e-2_dp * Real(r7*Conjg(r10(1)) + r7p*Conjg(r10p(1)), dp )    &
 & + 6.73e-2_dp * Real(r7 * Conjg(r8) + r7p * Conjg(r8p), dp )        &
 & - 0.86916_dp * Real(r7*Conjg(r9(1)) + r7p*Conjg(r9p(1)), dp )      &
 & + 1.85e-3_dp * Real(r8*Conjg(r10(1)) + r8p*Conjg(r10p(1)), dp )    &
 & - 9.921e-2_dp * Real(r8*Conjg(r9(1)) + r8p*Conjg(r9p(1)), dp )     &
 & + 2.833_dp* Real(r9(1),dp) + 0.2804_dp * (Abs(r7)**2 + Abs(r7p)**2)&
 & - 0.10698_dp * Real( r9(1) * Conjg(r10(1))                         &
 &                    + r9p(1) * Conjg(r10p(1)), dp)                  &
 & + 11.0348_dp * (Abs(r10(1))**2 + Abs(r10p(1))**2 )                 &
 & + 1.527_dp * (Abs(r9(1))**2 + Abs(r9p(1))**2 )                     &
 & + 3.763e-3_dp * (Abs(r8)**2 + Abs(r8p)**2 ) ) 

  ! ratio BR(B -> Xs mu+ mu-)/BR(B -> Xs e+ e-)_SM
  ratioBtoSee = BrBtoSEE/16.5529_dp

  ! branching ratio B -> Xs e+ e-
  BrBtoSEE = BrBtoSEE* 1.e-7_dp

BrBtoSMuMu = (2.1774_dp - 1.658e-3_dp * Aimag(R10(2))                 &
  & + 5.e-4_dp * Aimag(r10(2)*Conjg(r8) + r10p(2)*Conjg(r8p) )        &
  & + 5.34e-2_dp * Aimag(r7) + 5.27e-3_dp * Aimag(r8)                 &
  & + 2.266e-2_dp * Aimag(r7 * Conjg(r8) + r7p * Conjg(r8p) )         &
  & + 4.96e-3_dp * Aimag(r7 * Conjg(r9(2)) + r7p * Conjg(r9p(2)) )    &
  & + 2.61e-2_dp * Aimag(r8 * Conjg(r9(2)) + r8p * Conjg(r9p(2)) )    &
  & - 1.15e-2_dp * Aimag(r9(2)) - 0.5420_dp * Real( r10(2), dp)       &
  & + 2.08e-2_dp * Real(r7,dp) - 9.38e-3_dp * Real(r8,dp)             &
  & + 1.53e-2_dp * Real(r7*Conjg(r10(2)) + r7p*Conjg(r10p(2)), dp )   &
  & + 6.848e-2_dp * Real(r7 * Conjg(r8) + r7p * Conjg(r8p), dp )      &
  & - 0.8545_dp * Real(r7*Conjg(r9(2)) + r7p*Conjg(r9p(2)), dp )      &
  & + 1.85e-3_dp * Real(r8*Conjg(r10(2)) + r8p*Conjg(r10p(2)), dp )   &
  & - 9.81e-2_dp * Real(r8*Conjg(r9(2)) + r8p*Conjg(r9p(2)), dp )     &
  & + 2.6917_dp * Real(r9(2),dp) + 0.2880_dp*(Abs(r7)**2+Abs(r7p)**2) &
  & - 0.10698_dp * Real( r9(2) * Conjg(r10(2))                        &
  &                    + r9p(2) * Conjg(r10p(2)), dp)                 &
  & + 10.7652_dp * (Abs(r10(2))**2 + Abs(r10p(2))**2 )                &
  & + 1.4884_dp * (Abs(r9(2))**2 + Abs(r9p(2))**2 )                   &
  & + 3.81e-3_dp * (Abs(r8)**2 + Abs(r8p)**2 ) )

  ! ratio BR(B -> Xs mu+ mu-)/BR(B -> Xs mu+ mu-)_SM
  ratioBtoSMuMu = BrBtoSMuMu/16.0479_dp

  ! branching ratio B -> Xs mu+ mu-
  BrBtoSMuMu = BrBtoSMuMu* 1.e-7_dp

 

 
 ! ###### End user defined body 
End Subroutine Calculate_BtoSLL

Subroutine Calculate_DeltaMBq(O4dSLL,O4dSRR,O4dSRL,O4dSLR,O4dVRR,O4dVLL,              & 
& O4dVLLSM,O4dVRL,O4dVLR,O4dTLL,O4dTLR,O4dTRL,O4dTRR,OH2qSL,OH2qSR,OAh2qSL,              & 
& OAh2qSR,DeltaMBs,ratioDeltaMBs,DeltaMBq,ratioDeltaMBq)

Implicit None 
Complex(dp) :: O4dSLL(3,3,3,3),O4dSRR(3,3,3,3),O4dSRL(3,3,3,3),O4dSLR(3,3,3,3),O4dVRR(3,3,3,3),      & 
& O4dVLL(3,3,3,3),O4dVLLSM(3,3,3,3),O4dVRL(3,3,3,3),O4dVLR(3,3,3,3),O4dTLL(3,3,3,3),     & 
& O4dTLR(3,3,3,3),O4dTRL(3,3,3,3),O4dTRR(3,3,3,3),OH2qSL(3,3,2),OH2qSR(3,3,2),           & 
& OAh2qSL(3,3,2),OAh2qSR(3,3,2)

Real(dp), Intent(out) :: DeltaMBs 
Real(dp), Intent(out) :: ratioDeltaMBs 
Real(dp), Intent(out) :: DeltaMBq 
Real(dp), Intent(out) :: ratioDeltaMBq 

 
 ! #####+ Beging user defined body 
Complex(dp) :: MBq, etaB, FBq2, BBq, Ftt, Veff2, r, &
     & P1bLR, P2bLR, P1bSLL, P2bSLL, norm, &
     & CVLLnew, C1VRR, C1LR, C2LR, C1SLL, C1SRR, C2SLL, C2SRR
Real(dp) ::  hbar, xt, GF
Real(dp) :: mS
Complex(dp) :: HL, HR, AL, AR
Integer :: i1, iS

! ---------------------------------------------------------------- 
! Delta M_{Bd,Bs}
! Observable implemented by W. Porod, F. Staub and A. Vicente
! Based on A. J. Buras et al, NPB 619 (2001) 434 [hep-ph/0107048]
! and NPB 659 (2003) 3 [hep-ph/0210145]
! ---------------------------------------------------------------- 

hbar =  6.58211889e-25_dp
xt = mf_u2_160(3)/mw2
r = 0.985_dp
P1bLR = -0.71_dp
P2bLR = 0.90_dp
P1bSLL = -0.37_dp
P2bSLL = -0.72_dp

! QCD factor, see A. J. Buras et al, NPB 47 (1990) 491
! and J. Urban et al, NPB 523 (1998) 40 
etaB = 0.55_dp

GF =  (Alpha_160*4._dp*Pi/sinW2_160)/mw**2*sqrt2/8._dp

Do i1 = 1,2

If (i1.eq.1) Then ! Delta M_Bd
 MBq = mass_B0d
 FBq2 = f_B0d_CONST**2
 BBq = 1.26_dp ! see arXiv:0910.2928
 Veff2 = Conjg(Conjg(CKM_160(3,3))*CKM_160(3,1))**2
Else ! Delta M_Bs
 MBq = mass_B0s
 FBq2 = f_B0s_CONST**2
 BBq = 1.33_dp ! see arXiv:0910.2928
 Veff2 = Conjg(Conjg(CKM_160(3,3))*CKM_160(3,2))**2
End if

! normalization factor
norm = GF**2*mw2/(16._dp*Pi**2)*Veff2

! Wilson coefficients
CVLLnew = (O4dVLL(3,i1,3,i1)-O4dVLLSM(3,i1,3,i1))/norm ! we remove the SM contribution
C1VRR = O4dVRR(3,i1,3,i1)/norm
C1LR = (O4dVLR(3,i1,3,i1)+O4dVRL(3,i1,3,i1))/norm
C2LR = (O4dSLR(3,i1,3,i1)+O4dSRL(3,i1,3,i1))/norm
C1SLL = O4dSLL(3,i1,3,i1)/norm
C1SRR = O4dSRR(3,i1,3,i1)/norm
C2SLL  = O4dTLL(3,i1,3,i1)/norm
C2SRR  = O4dTRR(3,i1,3,i1)/norm


! Double Higgs penguins
Do iS =  1, 2
HL = OH2qSL(3,i1,iS)
HR = OH2qSR(3,i1,iS)
mS = Mhh2(iS)
C2LR = C2LR - HL*Conjg(HR)/(mS*norm)
C1SLL = C1SLL - 0.5_dp*HL**2/(mS*norm)
C1SRR = C1SRR - 0.5_dp*HR**2/(mS*norm)
End Do


Do iS = 2, 2
AL = OAh2qSL(3,i1,iS)
AR = OAh2qSR(3,i1,iS)
mS = MAh2(iS)
C2LR = C2LR - AL*Conjg(AR)/(mS*norm)
C1SLL = C1SLL - 0.5_dp*AL**2/(mS*norm)
C1SRR = C1SRR - 0.5_dp*AR**2/(mS*norm)
End Do


Ftt = S0xt(xt) + CVLLnew/(4._dp*r) + &
     & C1VRR/(4._dp*r) + P1bLR*C1LR + P2bLR*C2LR  + &
     & P1bSLL*(C1SLL + C1SRR) + P2bSLL*(C2SLL + C2SRR)

If (i1.eq.1) Then ! Delta M_Bd
   ratioDeltaMBq = Abs(Ftt/S0xt(xt))
   DeltaMBq = G_F**2*mw2/(6._dp*Pi**2)*    &
      & MBq*etaB*BBq*FBq2*Veff2*Abs(Ftt)*1.e-12_dp/hbar
Else ! Delta M_Bs
   ratioDeltaMBs = Abs(Ftt/S0xt(xt))
   DeltaMBs =  G_F**2*mw2/(6._dp*Pi**2)*   & 
      & MBq*etaB*BBq*FBq2*Veff2*Abs(Ftt)*1.e-12_dp/hbar
End if
 
End Do

Contains 

  Real(dp) Function S0xt(x) ! See for example hep-ph/9806471
    Implicit None
    Real(dp), Intent(in) :: x
    S0xt = 1._dp - 2.75_dp * x + 0.25_dp * x**2 &
        & - 1.5_dp * x**2 * Log(x) / (1-x)
    S0xt = x*S0xt / (1 -x)**2
  End  Function S0xt

 
 ! ###### End user defined body 
End Subroutine Calculate_DeltaMBq

Subroutine Calculate_KKmix(O4dSLL,O4dSRR,O4dSRL,O4dSLR,O4dVRR,O4dVLL,O4dVRL,          & 
& O4dVLR,O4dTLL,O4dTLR,O4dTRL,O4dTRR,O4dSLLSM,O4dSRRSM,O4dSRLSM,O4dSLRSM,O4dVRRSM,       & 
& O4dVLLSM,O4dVRLSM,O4dVLRSM,O4dTLLSM,O4dTLRSM,O4dTRLSM,O4dTRRSM,DelMK,ratioDelMK,       & 
& epsK,ratioepsK)

Implicit None 
Complex(dp) :: O4dSLL(3,3,3,3),O4dSRR(3,3,3,3),O4dSRL(3,3,3,3),O4dSLR(3,3,3,3),O4dVRR(3,3,3,3),      & 
& O4dVLL(3,3,3,3),O4dVRL(3,3,3,3),O4dVLR(3,3,3,3),O4dTLL(3,3,3,3),O4dTLR(3,3,3,3),       & 
& O4dTRL(3,3,3,3),O4dTRR(3,3,3,3),O4dSLLSM(3,3,3,3),O4dSRRSM(3,3,3,3),O4dSRLSM(3,3,3,3), & 
& O4dSLRSM(3,3,3,3),O4dVRRSM(3,3,3,3),O4dVLLSM(3,3,3,3),O4dVRLSM(3,3,3,3),               & 
& O4dVLRSM(3,3,3,3),O4dTLLSM(3,3,3,3),O4dTLRSM(3,3,3,3),O4dTRLSM(3,3,3,3),               & 
& O4dTRRSM(3,3,3,3)

Real(dp), Intent(out) :: DelMK 
Real(dp), Intent(out) :: ratioDelMK 
Real(dp), Intent(out) :: epsK 
Real(dp), Intent(out) :: ratioepsK 

 
 ! #####+ Beging user defined body 
Real(dp) :: b_VLL, b_SLL1, b_SLL2, b_LR1, b_LR2
Real(dp) :: ms_mu, md_mu
Complex(dp) :: CVLL, CVRR, CSLL, CSRR, CTLL, CTRR, CLR1, CLR2
Complex(dp) :: fV, fS, fT, fLR1, fLR2, cVLLSM
Complex(dp) :: f_k, M_K, H2eff, DelMK_SM, epsK_SM
Real(dp) :: norm, hbar, xt, xc, GF
Integer :: i1
Real(dp), Parameter :: eta_tt = 0.57_dp, eta_ct = 0.47_dp, &
                         & eta_cc = 1.44_dp
! Parameters from S. Herrlich and U. Nierste NPB 476 (1996) 27

! ---------------------------------------------------------------- 
! Delta M_K and epsilon_K 
! Observables implemented by W. Porod, F. Staub and A. Vicente
! Based on A. Crivellin et al, Comput. Phys. Commun. 184 (2013) 1004 [arXiv:1203.5023]
! ---------------------------------------------------------------- 

! using globally defined hadronic parameters
M_K = mass_K0
f_K = f_k_CONST

xt = mf_u(3)**2 / mW**2
xc = mf_u(2)**2 / mW**2

GF = (Alpha_160*4._dp*Pi/sinW2_160)/mw**2*sqrt2/8._dp

! Coefficients at mu = 2 GeV
! See A. J. Buras et al, NPB 605 (2001) 600 [hep-ph/0102316] 
b_VLL = 0.61_dp 
b_SLL1 = 0.76_dp 
b_SLL2 = 0.51_dp 
b_LR1 = 0.96_dp
b_LR2 = 1.3_dp

! Quark mass values at mu = 2 GeV
! See M. Ciuchini et al, JHEP 9810 (1998) 008 [hep-ph/9808328] - Table 1
md_mu = 0.007_dp
ms_mu = 0.125_dp

fV = 1._dp/3._dp*M_K*f_k**2*b_VLL
fS = -5._dp/24._dp*M_K*f_K**2*(M_K/(ms_mu+md_mu))**2*b_SLL1
fT = -1._dp/2._dp*M_K*f_K**2*(M_K/(ms_mu+md_mu))**2*b_SLL2
fLR1 = -1._dp/6._dp*M_K*f_K**2*(M_K/(ms_mu+md_mu))**2*b_LR1
fLR2 = 1._dp/4._dp*M_K*f_K**2*(M_K/(ms_mu+md_mu))**2*b_LR2

! SM contribution
! Based on the results by S. Herrlich and U. Nierste
! NPB 419 (1994) 292, PRD 52 (1995) 6505 and NPB 476 (1996) 27
cVLLSM = eta_cc * (Conjg(CKM_160(2,2))*CKM_160(2,1))**2 * S0xt(xc)    &
     & + eta_tt * (Conjg(CKM_160(3,2))*CKM_160(3,1))**2 * S0xt(xt)    &
     & + Conjg(CKM_160(2,2)*CKM_160(3,2))*(CKM_160(2,1)*CKM_160(3,1)) &
     &   * 2._dp * eta_ct * S0_2(xc,xt)

cVLLSM = Conjg(cVLLSM)  ! we compute (d\bar{s})(d\bar{s}) and not (\bar{d}s)(\bar{d}s)
cVLLSM = oo4pi2*(GF*mW)**2*cVLLSM ! normalization

! BSM contributions (+SM in CVLL)
CVLL = O4dVLL(2,1,2,1)-O4dVLLSM(2,1,2,1)+cVLLSM
CVRR = O4dVRR(2,1,2,1)
CSLL = O4dSLL(2,1,2,1)
CSRR = O4dSRR(2,1,2,1)
CTLL = O4dTLL(2,1,2,1)
CTRR = O4dTRR(2,1,2,1)
CLR1 = O4dSLR(2,1,2,1)+O4dSRL(2,1,2,1)  
CLR2 = O4dVLR(2,1,2,1)+O4dVRL(2,1,2,1)

! BSM
H2eff = fV*(CVLL+CVRR) + fS*(CSLL+CSRR) +fT*(CTLL+CTRR) &
              & + fLR1*CLR1 + fLR2*CLR2

DelMK = Abs(2._dp*Real(H2eff,dp))
epsK = 1._dp/(sqrt2*DelMK)*Abs(Aimag(H2eff))

! SM
H2eff = fV*cVLLSM

DelMK_SM = Abs(2._dp*Real(H2eff,dp))
epsK_SM = 1._dp/(sqrt2*DelMK_SM)*Abs(Aimag(H2eff))

ratioDelMK = DelMK/DelMK_SM
ratioepsK = epsK/epsK_SM

Contains 

! Inami - Lim functions

 Real(dp) Function S0xt(x)
   Implicit None
   Real(dp), Intent(in) :: x
   S0xt = 1._dp - 2.75_dp * x + 0.25_dp * x**2 - &
              &  1.5_dp * x**2 * Log(x) / (1-x)
   S0xt = x*S0xt / (1 -x)**2
 End  Function S0xt
 
 Real(dp) Function S0_2(xc, xt)
   Implicit None
   Real(dp), Intent(in) :: xc, xt
   S0_2 = Log(xt/xc) - 0.75_dp *  xt /(1-xt) &
        & - 0.75_dp * xt**2 * Log(xt) / (1-xt)**2
   S0_2 = xc *  S0_2
 End  Function S0_2
 

 
 ! ###### End user defined body 
End Subroutine Calculate_KKmix

Subroutine Calculate_KtoPInunu(OddvvVRR,OddvvVLL,OddvvVRL,OddvvVLR,OddvvVRRSM,        & 
& OddvvVLLSM,OddvvVRLSM,OddvvVLRSM,BrKptoPipnunu,ratioKptoPipnunu,BrKltoPinunu,          & 
& ratioKltoPinunu)

Implicit None 
Complex(dp) :: OddvvVRR(3,3,3,3),OddvvVLL(3,3,3,3),OddvvVRL(3,3,3,3),OddvvVLR(3,3,3,3),              & 
& OddvvVRRSM(3,3,3,3),OddvvVLLSM(3,3,3,3),OddvvVRLSM(3,3,3,3),OddvvVLRSM(3,3,3,3)

Real(dp), Intent(out) :: BrKptoPipnunu 
Real(dp), Intent(out) :: ratioKptoPipnunu 
Real(dp), Intent(out) :: BrKltoPinunu 
Real(dp), Intent(out) :: ratioKltoPinunu 

 
 ! #####+ Beging user defined body 
Complex(dp) :: br, r1, r2, rKp, rKl, Xx, XNL, Lt, Lc
Complex(dp) :: Xx_SM, br_SM, norm
Real(dp) :: GF
Integer :: out, i1, i2 

! ---------------------------------------------------------------- 
! K -> pi nu nu
! Observable implemented by W. Porod, F. Staub and A. Vicente
! Based on C. Bobeth et al, NPB 630 (2002) 87 [hep-ph/0112305] 
! ---------------------------------------------------------------- 

GF = (Alpha_160*4._dp*Pi/sinW2_160)/mw**2*sqrt2/8._dp
norm = Alpha_160*4._dp*GF/sqrt2/(2._dp*pi*sinw2_160) &
          & *Conjg(CKM_160(3,2))*CKM_160(3,1)

r1 = 1.17E-4_dp
r2 = 0.24_dp
rKp =  0.901
rKl = 0.944

! SM NLO charm correction
! See G. Buchalla and A. Buras, NPB 412 (1994) 106 and NPB 548 (1999) 309
XNL = 9.78E-4_dp

! out = 1 : K^+ -> pi^+ nu nu
! out = 2 : K_L -> pi^0 nu nu

Do out = 1,2
br = 0._dp
br_SM = 0._dp
 Do i1= 1,3
  Do i2 = 1,3
   Xx = ((OddvvVLL(2,1,i1,i2)+OddvvVRL(2,1,i1,i2))/norm) 
   Xx_SM = ((OddvvVLLSM(2,1,i1,i2)+OddvvVRLSM(2,1,i1,i2))/norm) 
   Lt = Conjg(CKM_160(3,2))*CKM_160(3,1)
   Lc = Conjg(CKM_160(2,2))*CKM_160(2,1)
   If (out.eq.1) Then 
     br = br + Aimag(Xx*Lt)**2 + (Real(Lc*XNL,dp) + Real(Xx*Lt,dp))**2
     br_SM = br_SM + Aimag(Xx_SM*Lt)**2 + &
                 & (Real(Lc*XNL,dp) + Real(Xx_SM*Lt,dp))**2
   Else
    br = br + Abs(Aimag(Xx*Lt))**2
    br_SM = br_SM + Abs(Aimag(Xx_SM*Lt))**2
   End if   
  End Do
 End do
If (out.eq.1) Then ! K^+ -> pi^+ nu nu
 BrKptoPipnunu = 2._dp*r1*r2*rKp*br
 RatioKptoPipnunu = br/br_SM
 ! SM expectation: (7.2 +/- 2.1)*10^-11 (hep-ph/0112135)
Else ! K_L -> pi^0 nu nu
 BrKltoPinunu = 2._dp*r1*rKl*br
 RatioKltoPinunu = br/br_SM
 ! SM expectation: (3.1 +/- 1.0)*10^-11 (hep-ph/0408142)
End if 
End Do

 
 ! ###### End user defined body 
End Subroutine Calculate_KtoPInunu

Subroutine Calculate_Plnu(OdulvSLL,OdulvSRR,OdulvSRL,OdulvSLR,OdulvVRR,               & 
& OdulvVLL,OdulvVRL,OdulvVLR,OdulvSLLSM,OdulvSRRSM,OdulvSRLSM,OdulvSLRSM,OdulvVRRSM,     & 
& OdulvVLLSM,OdulvVRLSM,OdulvVLRSM,BrDmunu,ratioDmunu,BrDsmunu,ratioDsmunu,              & 
& BrDstaunu,ratioDstaunu,BrBmunu,ratioBmunu,BrBtaunu,ratioBtaunu,BrKmunu,ratioKmunu,RK,RKSM)

Implicit None 
Complex(dp) :: OdulvSLL(3,3,3,3),OdulvSRR(3,3,3,3),OdulvSRL(3,3,3,3),OdulvSLR(3,3,3,3),              & 
& OdulvVRR(3,3,3,3),OdulvVLL(3,3,3,3),OdulvVRL(3,3,3,3),OdulvVLR(3,3,3,3),               & 
& OdulvSLLSM(3,3,3,3),OdulvSRRSM(3,3,3,3),OdulvSRLSM(3,3,3,3),OdulvSLRSM(3,3,3,3),       & 
& OdulvVRRSM(3,3,3,3),OdulvVLLSM(3,3,3,3),OdulvVRLSM(3,3,3,3),OdulvVLRSM(3,3,3,3)

Real(dp), Intent(out) :: BrDmunu 
Real(dp), Intent(out) :: ratioDmunu 
Real(dp), Intent(out) :: BrDsmunu 
Real(dp), Intent(out) :: ratioDsmunu 
Real(dp), Intent(out) :: BrDstaunu 
Real(dp), Intent(out) :: ratioDstaunu 
Real(dp), Intent(out) :: BrBmunu 
Real(dp), Intent(out) :: ratioBmunu 
Real(dp), Intent(out) :: BrBtaunu 
Real(dp), Intent(out) :: ratioBtaunu 
Real(dp), Intent(out) :: BrKmunu 
Real(dp), Intent(out) :: ratioKmunu 
Real(dp), Intent(out) :: RK 
Real(dp), Intent(out) :: RKSM 

 
 ! #####+ Beging user defined body 
Integer :: gt1, gt2, i1, i2, iP
Complex(dp) :: br, br_SM
Real(dp) :: m_M, f_M, tau_M, mlep, mq1, mq2, hbar, ratio, &
     & BrKenuSM, BRKenu, QED

! ---------------------------------------------------------------- 
! P -> l nu
! Observable implemented by W. Porod, F. Staub and A. Vicente
! Based on J. Barranco et al, arXiv:1303.3896
! ---------------------------------------------------------------- 

hbar = 6.58211889e-25_dp

! Electromagnetic correction to R_K
! See V. Cirigliano, I. Rosell, PRL 99 (2007) 231801 [arXiv:0707.3439]
QED = -3.6e-2_dp

! meson parameters

Do iP=1,4
If (iP.eq.1) Then ! Ds-meson
 gt1 = 2
 gt2 = 2
 m_M = mass_Dsp
 f_M = f_DSp_CONST
 tau_M = tau_DSp/hbar
Elseif (iP.eq.2) Then ! B-meson
 gt1 = 3
 gt2 = 1
 m_M = mass_Bp
 f_M = f_Bp_CONST
 tau_M = tau_Bp/hbar
Elseif (iP.eq.3) Then ! Kaon
 gt1 = 2
 gt2 = 1
 m_M = mass_Kp
 f_M =  f_Kp_CONST
 tau_M = tau_Kp/hbar
Elseif (iP.eq.4) Then ! D-meson
 gt1 = 1
 gt2 = 2
 m_M = mass_Dp
 f_M =  f_Dp_CONST
 tau_M = tau_Dp/hbar
End if

 mq1 =  mf_u_160(gt2)
 mq2 =  mf_d_160(gt1)

Do i1=1,3
br = 0._dp
br_SM = 0._dp
mlep = mf_l(i1)

Do i2=1,3
 br = br + ((OdulvVLL(gt1,gt2,i1,i2)-OdulvVLR(gt1,gt2,i1,i2))*mlep/   &
                   &           (2._dp*sqrt2)                          &
   & + m_M**2*(OdulvSRL(gt1,gt2,i1,i2)-OdulvSLL(gt1,gt2,i1,i2))/      &
                   & (2._dp*sqrt2*(mq1+mq2)))
 br_SM = br_SM+ (OdulvVLLSM(gt1,gt2,i1,i2)-OdulvVLRSM(gt1,gt2,i1,i2)) &
                   & *mlep/(2._dp*sqrt2)
End Do

ratio = Abs(br/br_SM)**2 
br = oo8pi*tau_M*(f_M)**2*M_M*Abs(br)**2*(1._dp - mlep**2/M_M**2)**2 ! G_F already in coefficients included


If (iP.eq.1) Then  !! Ds-meson 
 If (i1.eq.2) Then  ! Ds->mu nu
  BrDsmunu =   br
  ratioDsmunu = ratio
  Elseif (i1.eq.3) Then ! Ds->tau nu
  BrDstaunu =  br
  ratioDstaunu = ratio
 End if
Elseif (iP.eq.2) Then !! B-meson
 If (i1.eq.2) Then  ! B->mu nu
  BrBmunu =   br
  ratioBmunu = ratio
  Else              ! B->tau nu
  BrBtaunu =  br
  ratioBtaunu = ratio
 End if
Else If (iP.eq.3) Then !! Kaon 
 If (i1.eq.1) Then  ! K->e nu
  BrKenu =   br
  BrKenuSM = BrKenu*ratio
  Elseif (i1.eq.2) Then  ! K->mu nu
  BrKmunu =  br
  ratioKmunu = ratio
  RK = BrKenu/BrKmunu*(1+QED)
  RKSM = BrKenuSM/BrKmunu*ratio*(1+QED)
 End if
Else If (iP.eq.4) Then  !! D-meson 
 If (i1.eq.2) Then  ! D->mu nu
  BrDmunu =   br
  ratioDmunu = ratio
 End if
End if
End Do
End Do

 
 ! ###### End user defined body 
End Subroutine Calculate_Plnu

Real(dp) Function C00g(m1, m2, m3)
Implicit None
Real(dp), Intent(in) :: m1, m2, m3
Real(dp) :: eps=1E-10_dp, large = 1E+5_dp

C00g = C00_3m(m1,m2,m3)

End Function C00g

Real(dp) Function C0g(m1in,m2in,m3in) 
Real(dp),Intent(in)::m1in,m2in,m3in 
Real(dp)::eps=1E-10_dp,large=0._dp,epsR=1E-03_dp 
Real(dp)::m1,m2,r 

!  C0

If (Abs(m1in-m2in)/Abs(m1in+m2in).lt.eps) Then! m1==m2 
 m1=m1in
 m2=m3in
   If (m1.gt.m2) Then 
     r=m2/m1 
     If ((1._dp-r).lt.epsR) Then  ! Taylor
        C0g=-1/(2._dp*m1) + (-1 + r)/(6._dp*m1) - (-1 + r)**2/(12._dp*m1)
     Elseif (Abs(r).lt.eps) Then 
        C0g=-(1/m1)
     Else 
        C0g=(-1 + r - r*Log(r))/(m1*(-1 + r)**2)
     End if 
   Else 
     r=m1/m2 
     If ((1._dp-r).lt.epsR) Then 
        C0g=-1/(2._dp*m2) + (-1 + r)/(3._dp*m2) - (-1 + r)**2/(4._dp*m2)
     Elseif (Abs(r).lt.eps) Then 
        C0g=1._dp
     Else 
        C0g=(1 - r + Log(r))/(m2*(-1 + r)**2)
    End if 
   End if 

Else if (Abs(m2in-m3in)/Abs(m2in+m3in).lt.eps) Then! m2==m3 
 m1=m1in 
 m2=m3in 
   If (m1.gt.m2) Then 
     r=m2/m1 
     If ((1._dp-r).lt.epsR) Then 
        C0g=-1/(2._dp*m1) + (-1 + r)/(3._dp*m1) - (-1 + r)**2/(4._dp*m1)
     Elseif (Abs(r).lt.eps) Then 
        C0g=1._dp
     Else 
        C0g=(1 - r + Log(r))/(m1*(-1 + r)**2)
     End if 
   Else 
     r=m1/m2 
     If ((1._dp-r).lt.epsR) Then 
        C0g=-1/(2._dp*m2) + (-1 + r)/(6._dp*m2) - (-1 + r)**2/(12._dp*m2)
     Elseif (Abs(r).lt.eps) Then 
        C0g=-(1/m2)
     Else 
        C0g=(-1 + r - r*Log(r))/(m2*(-1 + r)**2)
     End if 
  End if 

Else!! Different masses are not possible! 
   C0g =0._dp 
End if 
 
End Function C0g 


Real(dp) Function C1g(m1in,m2in,m3in) 
Real(dp),Intent(in)::m1in,m2in,m3in 
Real(dp)::eps=1E-10_dp,large=0._dp,epsR=1E-03_dp 
Real(dp)::m1,m2,r 

!  C1

If (Abs(m1in-m2in)/Abs(m1in+m2in).lt.eps) Then! m1==m2 
 m1=m1in
 m2=m3in
   If (m1.gt.m2) Then 
     r=m2/m1 
     If ((1._dp-r).lt.epsR) Then  ! Taylor
        C1g=1/(6._dp*m1) - (-1 + r)/(24._dp*m1) + (-1 + r)**2/(60._dp*m1)
     Elseif (Abs(r).lt.eps) Then 
        C1g=1/(4._dp*m1)
     Else 
        C1g=(-1 + (4 - 3*r)*r + 2*r**2*Log(r))/(4._dp*m1*(-1 + r)**3)
     End if 
   Else 
     r=m1/m2 
     If ((1._dp-r).lt.epsR) Then 
        C1g=1/(6._dp*m2) - (-1 + r)/(8._dp*m2) + (-1 + r)**2/(10._dp*m2)
     Elseif (Abs(r).lt.eps) Then 
        C1g=large
     Else 
        C1g=(3 - 4*r + r**2 + 2*Log(r))/(4._dp*m2*(-1 + r)**3)
    End if 
   End if 

Else if (Abs(m2in-m3in)/Abs(m2in+m3in).lt.eps) Then! m2==m3 
 m1=m1in 
 m2=m3in 
   If (m1.gt.m2) Then 
     r=m2/m1 
     If ((1._dp-r).lt.epsR) Then 
        C1g=1/(6._dp*m1) - (-1 + r)/(8._dp*m1) + (-1 + r)**2/(10._dp*m1)
     Elseif (Abs(r).lt.eps) Then 
        C1g=large
     Else 
        C1g=(3 - 4*r + r**2 + 2*Log(r))/(4._dp*m1*(-1 + r)**3)
     End if 
   Else 
     r=m1/m2 
     If ((1._dp-r).lt.epsR) Then 
        C1g=1/(6._dp*m2) - (-1 + r)/(24._dp*m2) + (-1 + r)**2/(60._dp*m2)
     Elseif (Abs(r).lt.eps) Then 
        C1g=1/(4._dp*m2)
     Else 
        C1g=(-1 + (4 - 3*r)*r + 2*r**2*Log(r))/(4._dp*m2*(-1 + r)**3)
     End if 
  End if 

Else!! Different masses are not possible! 
   C1g =0._dp 
End if 
 
End Function C1g 


Real(dp) Function C2g(m1in,m2in,m3in) 
Real(dp),Intent(in)::m1in,m2in,m3in 
Real(dp)::eps=1E-10_dp,large=0._dp,epsR=1E-03_dp 
Real(dp)::m1,m2,r 

!  C2

If (Abs(m1in-m2in)/Abs(m1in+m2in).lt.eps) Then! m1==m2 
 m1=m1in
 m2=m3in
   If (m1.gt.m2) Then 
     r=m2/m1 
     If ((1._dp-r).lt.epsR) Then  ! Taylor
        C2g=1/(6._dp*m1) - (-1 + r)/(12._dp*m1) + (-1 + r)**2/(20._dp*m1)
     Elseif (Abs(r).lt.eps) Then 
        C2g=1/(2._dp*m1)
     Else 
        C2g=(-1 + r**2 - 2*r*Log(r))/(2._dp*m1*(-1 + r)**3)
     End if 
   Else 
     r=m1/m2 
     If ((1._dp-r).lt.epsR) Then 
        C2g=1/(6._dp*m2) - (-1 + r)/(12._dp*m2) + (-1 + r)**2/(20._dp*m2)
     Elseif (Abs(r).lt.eps) Then 
        C2g=1/(2._dp*m2)
     Else 
        C2g=(-1 + r**2 - 2*r*Log(r))/(2._dp*m2*(-1 + r)**3)
    End if 
   End if 

Else if (Abs(m2in-m3in)/Abs(m2in+m3in).lt.eps) Then! m2==m3 
 m1=m1in 
 m2=m3in 
   If (m1.gt.m2) Then 
     r=m2/m1 
     If ((1._dp-r).lt.epsR) Then 
        C2g=1/(6._dp*m1) - (-1 + r)/(8._dp*m1) + (-1 + r)**2/(10._dp*m1)
     Elseif (Abs(r).lt.eps) Then 
        C2g=large
     Else 
        C2g=(3 - 4*r + r**2 + 2*Log(r))/(4._dp*m1*(-1 + r)**3)
     End if 
   Else 
     r=m1/m2 
     If ((1._dp-r).lt.epsR) Then 
        C2g=1/(6._dp*m2) - (-1 + r)/(24._dp*m2) + (-1 + r)**2/(60._dp*m2)
     Elseif (Abs(r).lt.eps) Then 
        C2g=1/(4._dp*m2)
     Else 
        C2g=(-1 + (4 - 3*r)*r + 2*r**2*Log(r))/(4._dp*m2*(-1 + r)**3)
     End if 
  End if 

Else!! Different masses are not possible! 
   C2g =0._dp 
End if 
 
End Function C2g 


Real(dp) Function C11g(m1in,m2in,m3in) 
Real(dp),Intent(in)::m1in,m2in,m3in 
Real(dp)::eps=1E-10_dp,large=0._dp,epsR=1E-03_dp 
Real(dp)::m1,m2,r 

!  C11

If (Abs(m1in-m2in)/Abs(m1in+m2in).lt.eps) Then! m1==m2 
 m1=m1in
 m2=m3in
   If (m1.gt.m2) Then 
     r=m2/m1 
     If ((1._dp-r).lt.epsR) Then  ! Taylor
        C11g=-1/(12._dp*m1) + (-1 + r)/(60._dp*m1) - (-1 + r)**2/(180._dp*m1)
     Elseif (Abs(r).lt.eps) Then 
        C11g=-1/(9._dp*m1)
     Else 
        C11g=((-1 + r)*(2 + r*(-7 + 11*r)) - 6*r**3*Log(r))/(18._dp*m1*(-1 + r)**4)
     End if 
   Else 
     r=m1/m2 
     If ((1._dp-r).lt.epsR) Then 
        C11g=-1/(12._dp*m2) + (-1 + r)/(15._dp*m2) - (-1 + r)**2/(18._dp*m2)
     Elseif (Abs(r).lt.eps) Then 
        C11g=large
     Else 
        C11g=(-((-1 + r)*(11 + r*(-7 + 2*r))) + 6*Log(r))/(18._dp*m2*(-1 + r)**4)
    End if 
   End if 

Else if (Abs(m2in-m3in)/Abs(m2in+m3in).lt.eps) Then! m2==m3 
 m1=m1in 
 m2=m3in 
   If (m1.gt.m2) Then 
     r=m2/m1 
     If ((1._dp-r).lt.epsR) Then 
        C11g=-1/(12._dp*m1) + (-1 + r)/(15._dp*m1) - (-1 + r)**2/(18._dp*m1)
     Elseif (Abs(r).lt.eps) Then 
        C11g=large
     Else 
        C11g=(-((-1 + r)*(11 + r*(-7 + 2*r))) + 6*Log(r))/(18._dp*m1*(-1 + r)**4)
     End if 
   Else 
     r=m1/m2 
     If ((1._dp-r).lt.epsR) Then 
        C11g=-1/(12._dp*m2) + (-1 + r)/(60._dp*m2) - (-1 + r)**2/(180._dp*m2)
     Elseif (Abs(r).lt.eps) Then 
        C11g=-1/(9._dp*m2)
     Else 
        C11g=((-1 + r)*(2 + r*(-7 + 11*r)) - 6*r**3*Log(r))/(18._dp*m2*(-1 + r)**4)
     End if 
  End if 

Else!! Different masses are not possible! 
   C11g =0._dp 
End if 
 
End Function C11g 


Real(dp) Function C12g(m1in,m2in,m3in) 
Real(dp),Intent(in)::m1in,m2in,m3in 
Real(dp)::eps=1E-10_dp,large=0._dp,epsR=1E-03_dp 
Real(dp)::m1,m2,r 

!  C12

If (Abs(m1in-m2in)/Abs(m1in+m2in).lt.eps) Then! m1==m2 
 m1=m1in
 m2=m3in
   If (m1.gt.m2) Then 
     r=m2/m1 
     If ((1._dp-r).lt.epsR) Then  ! Taylor
        C12g=-1/(24._dp*m1) + (-1 + r)/(60._dp*m1) - (-1 + r)**2/(120._dp*m1)
     Elseif (Abs(r).lt.eps) Then 
        C12g=-1/(12._dp*m1)
     Else 
        C12g=(-((-1 + r)*(-1 + r*(5 + 2*r))) + 6*r**2*Log(r))/(12._dp*m1*(-1 + r)**4)
     End if 
   Else 
     r=m1/m2 
     If ((1._dp-r).lt.epsR) Then 
        C12g=-1/(24._dp*m2) + (-1 + r)/(40._dp*m2) - (-1 + r)**2/(60._dp*m2)
     Elseif (Abs(r).lt.eps) Then 
        C12g=-1/(6._dp*m2)
     Else 
        C12g=-(2 + r*(3 + (-6 + r)*r) + 6*r*Log(r))/(12._dp*m2*(-1 + r)**4)
    End if 
   End if 

Else if (Abs(m2in-m3in)/Abs(m2in+m3in).lt.eps) Then! m2==m3 
 m1=m1in 
 m2=m3in 
   If (m1.gt.m2) Then 
     r=m2/m1 
     If ((1._dp-r).lt.epsR) Then 
        C12g=-1/(24._dp*m1) + (-1 + r)/(30._dp*m1) - (-1 + r)**2/(36._dp*m1)
     Elseif (Abs(r).lt.eps) Then 
        C12g=large
     Else 
        C12g=(-((-1 + r)*(11 + r*(-7 + 2*r))) + 6*Log(r))/(36._dp*m1*(-1 + r)**4)
     End if 
   Else 
     r=m1/m2 
     If ((1._dp-r).lt.epsR) Then 
        C12g=-1/(24._dp*m2) + (-1 + r)/(120._dp*m2) - (-1 + r)**2/(360._dp*m2)
     Elseif (Abs(r).lt.eps) Then 
        C12g=-1/(18._dp*m2)
     Else 
        C12g=((-1 + r)*(2 + r*(-7 + 11*r)) - 6*r**3*Log(r))/(36._dp*m2*(-1 + r)**4)
     End if 
  End if 

Else!! Different masses are not possible! 
   C12g =0._dp 
End if 
 
End Function C12g 


Real(dp) Function C22g(m1in,m2in,m3in) 
Real(dp),Intent(in)::m1in,m2in,m3in 
Real(dp)::eps=1E-10_dp,large=0._dp,epsR=1E-03_dp 
Real(dp)::m1,m2,r 

!  C22

If (Abs(m1in-m2in)/Abs(m1in+m2in).lt.eps) Then! m1==m2 
 m1=m1in
 m2=m3in
   If (m1.gt.m2) Then 
     r=m2/m1 
     If ((1._dp-r).lt.epsR) Then  ! Taylor
        C22g=-1/(12._dp*m1) + (-1 + r)/(20._dp*m1) - (-1 + r)**2/(30._dp*m1)
     Elseif (Abs(r).lt.eps) Then 
        C22g=-1/(3._dp*m1)
     Else 
        C22g=-(2 + r*(3 + (-6 + r)*r) + 6*r*Log(r))/(6._dp*m1*(-1 + r)**4)
     End if 
   Else 
     r=m1/m2 
     If ((1._dp-r).lt.epsR) Then 
        C22g=-1/(12._dp*m2) + (-1 + r)/(30._dp*m2) - (-1 + r)**2/(60._dp*m2)
     Elseif (Abs(r).lt.eps) Then 
        C22g=-1/(6._dp*m2)
     Else 
        C22g=(-((-1 + r)*(-1 + r*(5 + 2*r))) + 6*r**2*Log(r))/(6._dp*m2*(-1 + r)**4)
    End if 
   End if 

Else if (Abs(m2in-m3in)/Abs(m2in+m3in).lt.eps) Then! m2==m3 
 m1=m1in 
 m2=m3in 
   If (m1.gt.m2) Then 
     r=m2/m1 
     If ((1._dp-r).lt.epsR) Then 
        C22g=-1/(12._dp*m1) + (-1 + r)/(15._dp*m1) - (-1 + r)**2/(18._dp*m1)
     Elseif (Abs(r).lt.eps) Then 
        C22g=large
     Else 
        C22g=(-((-1 + r)*(11 + r*(-7 + 2*r))) + 6*Log(r))/(18._dp*m1*(-1 + r)**4)
     End if 
   Else 
     r=m1/m2 
     If ((1._dp-r).lt.epsR) Then 
        C22g=-1/(12._dp*m2) + (-1 + r)/(60._dp*m2) - (-1 + r)**2/(180._dp*m2)
     Elseif (Abs(r).lt.eps) Then 
        C22g=-1/(9._dp*m2)
     Else 
        C22g=((-1 + r)*(2 + r*(-7 + 11*r)) - 6*r**3*Log(r))/(18._dp*m2*(-1 + r)**4)
     End if 
  End if 

Else!! Different masses are not possible! 
   C22g =0._dp 
End if 
 
End Function C22g 


Real(dp) Function C2C12C22(m1in,m2in,m3in) 
Real(dp),Intent(in)::m1in,m2in,m3in 
Real(dp)::eps=1E-10_dp,large=0._dp,epsR=1E-03_dp 
Real(dp)::m1,m2,r 

!  C12 + C2 + C22

If (Abs(m1in-m2in)/Abs(m1in+m2in).lt.eps) Then! m1==m2 
 m1=m1in
 m2=m3in
   If (m1.gt.m2) Then 
     r=m2/m1 
     If ((1._dp-r).lt.epsR) Then  ! Taylor
        C2C12C22=1/(24._dp*m1) - (-1 + r)/(60._dp*m1) + (-1 + r)**2/(120._dp*m1)
     Elseif (Abs(r).lt.eps) Then 
        C2C12C22=1/(12._dp*m1)
     Else 
        C2C12C22=((-1 + r)*(-1 + r*(5 + 2*r)) - 6*r**2*Log(r))/(12._dp*m1*(-1 + r)**4)
     End if 
   Else 
     r=m1/m2 
     If ((1._dp-r).lt.epsR) Then 
        C2C12C22=1/(24._dp*m2) - (-1 + r)/(40._dp*m2) + (-1 + r)**2/(60._dp*m2)
     Elseif (Abs(r).lt.eps) Then 
        C2C12C22=1/(6._dp*m2)
     Else 
        C2C12C22=(2 + r*(3 + (-6 + r)*r) + 6*r*Log(r))/(12._dp*m2*(-1 + r)**4)
    End if 
   End if 

Else if (Abs(m2in-m3in)/Abs(m2in+m3in).lt.eps) Then! m2==m3 
 m1=m1in 
 m2=m3in 
   If (m1.gt.m2) Then 
     r=m2/m1 
     If ((1._dp-r).lt.epsR) Then 
        C2C12C22=1/(24._dp*m1) - (-1 + r)/(40._dp*m1) + (-1 + r)**2/(60._dp*m1)
     Elseif (Abs(r).lt.eps) Then 
        C2C12C22=1/(6._dp*m1)
     Else 
        C2C12C22=(2 + r*(3 + (-6 + r)*r) + 6*r*Log(r))/(12._dp*m1*(-1 + r)**4)
     End if 
   Else 
     r=m1/m2 
     If ((1._dp-r).lt.epsR) Then 
        C2C12C22=1/(24._dp*m2) - (-1 + r)/(60._dp*m2) + (-1 + r)**2/(120._dp*m2)
     Elseif (Abs(r).lt.eps) Then 
        C2C12C22=1/(12._dp*m2)
     Else 
        C2C12C22=((-1 + r)*(-1 + r*(5 + 2*r)) - 6*r**2*Log(r))/(12._dp*m2*(-1 + r)**4)
     End if 
  End if 

Else!! Different masses are not possible! 
   C2C12C22 =0._dp 
End if 
 
End Function C2C12C22 


Real(dp) Function C1C12C11(m1in,m2in,m3in) 
Real(dp),Intent(in)::m1in,m2in,m3in 
Real(dp)::eps=1E-10_dp,large=0._dp,epsR=1E-03_dp 
Real(dp)::m1,m2,r 

!  C1 + C11 + C12

If (Abs(m1in-m2in)/Abs(m1in+m2in).lt.eps) Then! m1==m2 
 m1=m1in
 m2=m3in
   If (m1.gt.m2) Then 
     r=m2/m1 
     If ((1._dp-r).lt.epsR) Then  ! Taylor
        C1C12C11=1/(24._dp*m1) - (-1 + r)/(120._dp*m1) + (-1 + r)**2/(360._dp*m1)
     Elseif (Abs(r).lt.eps) Then 
        C1C12C11=1/(18._dp*m1)
     Else 
        C1C12C11=(-((-1 + r)*(2 + r*(-7 + 11*r))) + 6*r**3*Log(r))/(36._dp*m1*(-1 + r)**4)
     End if 
   Else 
     r=m1/m2 
     If ((1._dp-r).lt.epsR) Then 
        C1C12C11=1/(24._dp*m2) - (-1 + r)/(30._dp*m2) + (-1 + r)**2/(36._dp*m2)
     Elseif (Abs(r).lt.eps) Then 
        C1C12C11=large
     Else 
        C1C12C11=((-1 + r)*(11 + r*(-7 + 2*r)) - 6*Log(r))/(36._dp*m2*(-1 + r)**4)
    End if 
   End if 

Else if (Abs(m2in-m3in)/Abs(m2in+m3in).lt.eps) Then! m2==m3 
 m1=m1in 
 m2=m3in 
   If (m1.gt.m2) Then 
     r=m2/m1 
     If ((1._dp-r).lt.epsR) Then 
        C1C12C11=1/(24._dp*m1) - (-1 + r)/(40._dp*m1) + (-1 + r)**2/(60._dp*m1)
     Elseif (Abs(r).lt.eps) Then 
        C1C12C11=1/(6._dp*m1)
     Else 
        C1C12C11=(2 + r*(3 + (-6 + r)*r) + 6*r*Log(r))/(12._dp*m1*(-1 + r)**4)
     End if 
   Else 
     r=m1/m2 
     If ((1._dp-r).lt.epsR) Then 
        C1C12C11=1/(24._dp*m2) - (-1 + r)/(60._dp*m2) + (-1 + r)**2/(120._dp*m2)
     Elseif (Abs(r).lt.eps) Then 
        C1C12C11=1/(12._dp*m2)
     Else 
        C1C12C11=((-1 + r)*(-1 + r*(5 + 2*r)) - 6*r**2*Log(r))/(12._dp*m2*(-1 + r)**4)
     End if 
  End if 

Else!! Different masses are not possible! 
   C1C12C11 =0._dp 
End if 
 
End Function C1C12C11 


Real(dp) Function C0C1C2(m1in,m2in,m3in) 
Real(dp),Intent(in)::m1in,m2in,m3in 
Real(dp)::eps=1E-10_dp,large=0._dp,epsR=1E-03_dp 
Real(dp)::m1,m2,r 

!  C0 + C1 + C2

If (Abs(m1in-m2in)/Abs(m1in+m2in).lt.eps) Then! m1==m2 
 m1=m1in
 m2=m3in
   If (m1.gt.m2) Then 
     r=m2/m1 
     If ((1._dp-r).lt.epsR) Then  ! Taylor
        C0C1C2=-1/(6._dp*m1) + (-1 + r)/(24._dp*m1) - (-1 + r)**2/(60._dp*m1)
     Elseif (Abs(r).lt.eps) Then 
        C0C1C2=-1/(4._dp*m1)
     Else 
        C0C1C2=(1 - 4*r + 3*r**2 - 2*r**2*Log(r))/(4._dp*m1*(-1 + r)**3)
     End if 
   Else 
     r=m1/m2 
     If ((1._dp-r).lt.epsR) Then 
        C0C1C2=-1/(6._dp*m2) + (-1 + r)/(8._dp*m2) - (-1 + r)**2/(10._dp*m2)
     Elseif (Abs(r).lt.eps) Then 
        C0C1C2=large
     Else 
        C0C1C2=-(3 - 4*r + r**2 + 2*Log(r))/(4._dp*m2*(-1 + r)**3)
    End if 
   End if 

Else if (Abs(m2in-m3in)/Abs(m2in+m3in).lt.eps) Then! m2==m3 
 m1=m1in 
 m2=m3in 
   If (m1.gt.m2) Then 
     r=m2/m1 
     If ((1._dp-r).lt.epsR) Then 
        C0C1C2=-1/(6._dp*m1) + (-1 + r)/(12._dp*m1) - (-1 + r)**2/(20._dp*m1)
     Elseif (Abs(r).lt.eps) Then 
        C0C1C2=-1/(2._dp*m1)
     Else 
        C0C1C2=(1 - r**2 + 2*r*Log(r))/(2._dp*m1*(-1 + r)**3)
     End if 
   Else 
     r=m1/m2 
     If ((1._dp-r).lt.epsR) Then 
        C0C1C2=-1/(6._dp*m2) + (-1 + r)/(12._dp*m2) - (-1 + r)**2/(20._dp*m2)
     Elseif (Abs(r).lt.eps) Then 
        C0C1C2=-1/(2._dp*m2)
     Else 
        C0C1C2=(1 - r**2 + 2*r*Log(r))/(2._dp*m2*(-1 + r)**3)
     End if 
  End if 

Else!! Different masses are not possible! 
   C0C1C2 =0._dp 
End if 
 
End Function C0C1C2 


Real(dp) Function C12C11C2(m1in,m2in,m3in) 
Real(dp),Intent(in)::m1in,m2in,m3in 
Real(dp)::eps=1E-10_dp,large=0._dp,epsR=1E-03_dp 
Real(dp)::m1,m2,r 

!  2 C11 + 2 C12 - C2

If (Abs(m1in-m2in)/Abs(m1in+m2in).lt.eps) Then! m1==m2 
 m1=m1in
 m2=m3in
   If (m1.gt.m2) Then 
     r=m2/m1 
     If ((1._dp-r).lt.epsR) Then  ! Taylor
        C12C11C2=-5/(12._dp*m1) + (3*(-1 + r))/(20._dp*m1) - (7*(-1 + r)**2)/(90._dp*m1)
     Elseif (Abs(r).lt.eps) Then 
        C12C11C2=-8/(9._dp*m1)
     Else 
        C12C11C2=((-1 + r)*(16 + r*(-29 + 7*r)) - 6*r*(3 + 2*(-3 + r)*r)*Log(r))/(18._dp*m1*(-1 + r)**4)
     End if 
   Else 
     r=m1/m2 
     If ((1._dp-r).lt.epsR) Then 
        C12C11C2=-5/(12._dp*m2) + (4*(-1 + r))/(15._dp*m2) - (7*(-1 + r)**2)/(36._dp*m2)
     Elseif (Abs(r).lt.eps) Then 
        C12C11C2=large
     Else 
        C12C11C2=(-((-1 + r)*(7 + r*(-29 + 16*r))) + 6*(2 + 3*(-2 + r)*r)*Log(r))/(18._dp*m2*(-1 + r)**4)
    End if 
   End if 

Else if (Abs(m2in-m3in)/Abs(m2in+m3in).lt.eps) Then! m2==m3 
 m1=m1in 
 m2=m3in 
   If (m1.gt.m2) Then 
     r=m2/m1 
     If ((1._dp-r).lt.epsR) Then 
        C12C11C2=-5/(12._dp*m1) + (13*(-1 + r))/(40._dp*m1) - (4*(-1 + r)**2)/(15._dp*m1)
     Elseif (Abs(r).lt.eps) Then 
        C12C11C2=large
     Else 
        C12C11C2=-((-1 + r)*(31 + r*(-26 + 7*r)) + 6*(-3 + r)*Log(r))/(12._dp*m1*(-1 + r)**4)
     End if 
   Else 
     r=m1/m2 
     If ((1._dp-r).lt.epsR) Then 
        C12C11C2=-5/(12._dp*m2) + (11*(-1 + r))/(120._dp*m2) - (-1 + r)**2/(30._dp*m2)
     Elseif (Abs(r).lt.eps) Then 
        C12C11C2=-7/(12._dp*m2)
     Else 
        C12C11C2=((-1 + r)*(7 + r*(-26 + 31*r)) + 6*(1 - 3*r)*r**2*Log(r))/(12._dp*m2*(-1 + r)**4)
     End if 
  End if 

Else!! Different masses are not possible! 
   C12C11C2 =0._dp 
End if 
 
End Function C12C11C2 


Real(dp) Function C12C22C1(m1in,m2in,m3in) 
Real(dp),Intent(in)::m1in,m2in,m3in 
Real(dp)::eps=1E-10_dp,large=0._dp,epsR=1E-03_dp 
Real(dp)::m1,m2,r 

!  -C1 + 2 C12 + 2 C22

If (Abs(m1in-m2in)/Abs(m1in+m2in).lt.eps) Then! m1==m2 
 m1=m1in
 m2=m3in
   If (m1.gt.m2) Then 
     r=m2/m1 
     If ((1._dp-r).lt.epsR) Then  ! Taylor
        C12C22C1=-5/(12._dp*m1) + (7*(-1 + r))/(40._dp*m1) - (-1 + r)**2/(10._dp*m1)
     Elseif (Abs(r).lt.eps) Then 
        C12C22C1=-13/(12._dp*m1)
     Else 
        C12C22C1=((-1 + r)*(13 + (-2 + r)*r) - 6*r*(4 + (-3 + r)*r)*Log(r))/(12._dp*m1*(-1 + r)**4)
     End if 
   Else 
     r=m1/m2 
     If ((1._dp-r).lt.epsR) Then 
        C12C22C1=-5/(12._dp*m2) + (29*(-1 + r))/(120._dp*m2) - (-1 + r)**2/(6._dp*m2)
     Elseif (Abs(r).lt.eps) Then 
        C12C22C1=large
     Else 
        C12C22C1=(-((-1 + r)*(1 + r*(-2 + 13*r))) + 6*(1 + r*(-3 + 4*r))*Log(r))/(12._dp*m2*(-1 + r)**4)
    End if 
   End if 

Else if (Abs(m2in-m3in)/Abs(m2in+m3in).lt.eps) Then! m2==m3 
 m1=m1in 
 m2=m3in 
   If (m1.gt.m2) Then 
     r=m2/m1 
     If ((1._dp-r).lt.epsR) Then 
        C12C22C1=-5/(12._dp*m1) + (13*(-1 + r))/(40._dp*m1) - (4*(-1 + r)**2)/(15._dp*m1)
     Elseif (Abs(r).lt.eps) Then 
        C12C22C1=large
     Else 
        C12C22C1=-((-1 + r)*(31 + r*(-26 + 7*r)) + 6*(-3 + r)*Log(r))/(12._dp*m1*(-1 + r)**4)
     End if 
   Else 
     r=m1/m2 
     If ((1._dp-r).lt.epsR) Then 
        C12C22C1=-5/(12._dp*m2) + (11*(-1 + r))/(120._dp*m2) - (-1 + r)**2/(30._dp*m2)
     Elseif (Abs(r).lt.eps) Then 
        C12C22C1=-7/(12._dp*m2)
     Else 
        C12C22C1=((-1 + r)*(7 + r*(-26 + 31*r)) + 6*(1 - 3*r)*r**2*Log(r))/(12._dp*m2*(-1 + r)**4)
     End if 
  End if 

Else!! Different masses are not possible! 
   C12C22C1 =0._dp 
End if 
 
End Function C12C22C1 


Real(dp) Function C12C22(m1in,m2in,m3in) 
Real(dp),Intent(in)::m1in,m2in,m3in 
Real(dp)::eps=1E-10_dp,large=0._dp,epsR=1E-03_dp 
Real(dp)::m1,m2,r 

!  C12 + C22

If (Abs(m1in-m2in)/Abs(m1in+m2in).lt.eps) Then! m1==m2 
 m1=m1in
 m2=m3in
   If (m1.gt.m2) Then 
     r=m2/m1 
     If ((1._dp-r).lt.epsR) Then  ! Taylor
        C12C22=-1/(8._dp*m1) + (-1 + r)/(15._dp*m1) - (-1 + r)**2/(24._dp*m1)
     Elseif (Abs(r).lt.eps) Then 
        C12C22=-5/(12._dp*m1)
     Else 
        C12C22=(-5 + (9 - 4*r)*r**2 + 6*(-2 + r)*r*Log(r))/(12._dp*m1*(-1 + r)**4)
     End if 
   Else 
     r=m1/m2 
     If ((1._dp-r).lt.epsR) Then 
        C12C22=-1/(8._dp*m2) + (7*(-1 + r))/(120._dp*m2) - (-1 + r)**2/(30._dp*m2)
     Elseif (Abs(r).lt.eps) Then 
        C12C22=-1/(3._dp*m2)
     Else 
        C12C22=(-4 + 9*r - 5*r**3 + 6*r*(-1 + 2*r)*Log(r))/(12._dp*m2*(-1 + r)**4)
    End if 
   End if 

Else if (Abs(m2in-m3in)/Abs(m2in+m3in).lt.eps) Then! m2==m3 
 m1=m1in 
 m2=m3in 
   If (m1.gt.m2) Then 
     r=m2/m1 
     If ((1._dp-r).lt.epsR) Then 
        C12C22=-1/(8._dp*m1) + (-1 + r)/(10._dp*m1) - (-1 + r)**2/(12._dp*m1)
     Elseif (Abs(r).lt.eps) Then 
        C12C22=large
     Else 
        C12C22=(-((-1 + r)*(11 + r*(-7 + 2*r))) + 6*Log(r))/(12._dp*m1*(-1 + r)**4)
     End if 
   Else 
     r=m1/m2 
     If ((1._dp-r).lt.epsR) Then 
        C12C22=-1/(8._dp*m2) + (-1 + r)/(40._dp*m2) - (-1 + r)**2/(120._dp*m2)
     Elseif (Abs(r).lt.eps) Then 
        C12C22=-1/(6._dp*m2)
     Else 
        C12C22=((-1 + r)*(2 + r*(-7 + 11*r)) - 6*r**3*Log(r))/(12._dp*m2*(-1 + r)**4)
     End if 
  End if 

Else!! Different masses are not possible! 
   C12C22 =0._dp 
End if 
 
End Function C12C22 


Real(dp) Function C2C12(m1in,m2in,m3in) 
Real(dp),Intent(in)::m1in,m2in,m3in 
Real(dp)::eps=1E-10_dp,large=0._dp,epsR=1E-03_dp 
Real(dp)::m1,m2,r 

!  C12 + C2

If (Abs(m1in-m2in)/Abs(m1in+m2in).lt.eps) Then! m1==m2 
 m1=m1in
 m2=m3in
   If (m1.gt.m2) Then 
     r=m2/m1 
     If ((1._dp-r).lt.epsR) Then  ! Taylor
        C2C12=1/(8._dp*m1) - (-1 + r)/(15._dp*m1) + (-1 + r)**2/(24._dp*m1)
     Elseif (Abs(r).lt.eps) Then 
        C2C12=5/(12._dp*m1)
     Else 
        C2C12=(5 + r**2*(-9 + 4*r) - 6*(-2 + r)*r*Log(r))/(12._dp*m1*(-1 + r)**4)
     End if 
   Else 
     r=m1/m2 
     If ((1._dp-r).lt.epsR) Then 
        C2C12=1/(8._dp*m2) - (7*(-1 + r))/(120._dp*m2) + (-1 + r)**2/(30._dp*m2)
     Elseif (Abs(r).lt.eps) Then 
        C2C12=1/(3._dp*m2)
     Else 
        C2C12=(4 - 9*r + 5*r**3 + 6*(1 - 2*r)*r*Log(r))/(12._dp*m2*(-1 + r)**4)
    End if 
   End if 

Else if (Abs(m2in-m3in)/Abs(m2in+m3in).lt.eps) Then! m2==m3 
 m1=m1in 
 m2=m3in 
   If (m1.gt.m2) Then 
     r=m2/m1 
     If ((1._dp-r).lt.epsR) Then 
        C2C12=1/(8._dp*m1) - (11*(-1 + r))/(120._dp*m1) + (13*(-1 + r)**2)/(180._dp*m1)
     Elseif (Abs(r).lt.eps) Then 
        C2C12=large
     Else 
        C2C12=((-1 + r)*(16 + r*(-29 + 7*r)) + 6*(-2 + 3*r)*Log(r))/(36._dp*m1*(-1 + r)**4)
     End if 
   Else 
     r=m1/m2 
     If ((1._dp-r).lt.epsR) Then 
        C2C12=1/(8._dp*m2) - (-1 + r)/(30._dp*m2) + (-1 + r)**2/(72._dp*m2)
     Elseif (Abs(r).lt.eps) Then 
        C2C12=7/(36._dp*m2)
     Else 
        C2C12=(-((-1 + r)*(7 + r*(-29 + 16*r))) + 6*r**2*(-3 + 2*r)*Log(r))/(36._dp*m2*(-1 + r)**4)
     End if 
  End if 

Else!! Different masses are not possible! 
   C2C12 =0._dp 
End if 
 
End Function C2C12 


Real(dp) Function C1C2(m1in,m2in,m3in) 
Real(dp),Intent(in)::m1in,m2in,m3in 
Real(dp)::eps=1E-10_dp,large=0._dp,epsR=1E-03_dp 
Real(dp)::m1,m2,r 

!  C1 + C2

If (Abs(m1in-m2in)/Abs(m1in+m2in).lt.eps) Then! m1==m2 
 m1=m1in
 m2=m3in
   If (m1.gt.m2) Then 
     r=m2/m1 
     If ((1._dp-r).lt.epsR) Then  ! Taylor
        C1C2=1/(3._dp*m1) - (-1 + r)/(8._dp*m1) + (-1 + r)**2/(15._dp*m1)
     Elseif (Abs(r).lt.eps) Then 
        C1C2=3/(4._dp*m1)
     Else 
        C1C2=-(3 - 4*r + r**2 - 2*(-2 + r)*r*Log(r))/(4._dp*m1*(-1 + r)**3)
     End if 
   Else 
     r=m1/m2 
     If ((1._dp-r).lt.epsR) Then 
        C1C2=1/(3._dp*m2) - (5*(-1 + r))/(24._dp*m2) + (3*(-1 + r)**2)/(20._dp*m2)
     Elseif (Abs(r).lt.eps) Then 
        C1C2=large
     Else 
        C1C2=(1 - 4*r + 3*r**2 + (2 - 4*r)*Log(r))/(4._dp*m2*(-1 + r)**3)
    End if 
   End if 

Else if (Abs(m2in-m3in)/Abs(m2in+m3in).lt.eps) Then! m2==m3 
 m1=m1in 
 m2=m3in 
   If (m1.gt.m2) Then 
     r=m2/m1 
     If ((1._dp-r).lt.epsR) Then 
        C1C2=1/(3._dp*m1) - (-1 + r)/(4._dp*m1) + (-1 + r)**2/(5._dp*m1)
     Elseif (Abs(r).lt.eps) Then 
        C1C2=large
     Else 
        C1C2=(3 - 4*r + r**2 + 2*Log(r))/(2._dp*m1*(-1 + r)**3)
     End if 
   Else 
     r=m1/m2 
     If ((1._dp-r).lt.epsR) Then 
        C1C2=1/(3._dp*m2) - (-1 + r)/(12._dp*m2) + (-1 + r)**2/(30._dp*m2)
     Elseif (Abs(r).lt.eps) Then 
        C1C2=1/(2._dp*m2)
     Else 
        C1C2=(-1 + (4 - 3*r)*r + 2*r**2*Log(r))/(2._dp*m2*(-1 + r)**3)
     End if 
  End if 

Else!! Different masses are not possible! 
   C1C2 =0._dp 
End if 
 
End Function C1C2 
End Module FlavorKit_Observables_MSSM 
