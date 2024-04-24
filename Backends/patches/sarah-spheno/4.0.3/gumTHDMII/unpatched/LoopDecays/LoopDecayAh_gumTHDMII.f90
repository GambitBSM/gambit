! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.14.0 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 18:24 on 16.9.2022   
! ----------------------------------------------------------------------  
 
 
Module OneLoopDecay_Ah_gumTHDMII
Use Control 
Use Settings 
Use LoopFunctions 
Use AddLoopFunctions 
Use Model_Data_gumTHDMII 
Use DecayFFS 
Use DecayFFV 
Use DecaySSS 
Use DecaySFF 
Use DecaySSV 
Use DecaySVV 
Use Bremsstrahlung 

Contains 

Subroutine Amplitude_Tree_gumTHDMII_AhToAhAh(cplAhAhAh,MAh,MAh2,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MAh2(2)

Complex(dp), Intent(in) :: cplAhAhAh(2,2,2)

Complex(dp) :: Amp(2,2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 

Do gt1=1,2
  Do gt2=1,2
    Do gt3=1,2
! External masses 
Mex1 = MAh(gt1) 
Mex2 = MAh(gt2) 
Mex3 = MAh(gt3) 
! Tree-Level Vertex 
coupT1 = cplAhAhAh(gt1,gt2,gt3)
Call TreeAmp_StoSS(Mex1,Mex2,Mex3,coupT1,AmpC) 
! Colour and symmetry factor 
Amp(gt1, gt2, gt3) = AmpC 
    End Do
  End Do
End Do
End Subroutine Amplitude_Tree_gumTHDMII_AhToAhAh


Subroutine Gamma_Real_gumTHDMII_AhToAhAh(MLambda,em,gs,cplAhAhAh,MAh,GammarealPhoton, & 
& GammarealGluon)

Implicit None

Complex(dp), Intent(in) :: cplAhAhAh(2,2,2)

Real(dp), Intent(in) :: MAh(2)

Real(dp), Intent(in) :: MLambda, em, gs 

Real(dp), Intent(out) :: GammarealPhoton(2,2,2), GammarealGluon(2,2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 

Real(dp) :: Mloop1, Mloop2, Mloop3 
Complex(dp) :: Coup 
 
Do i1=2,2
  Do i2=2,2
    Do i3=2,2
Coup = cplAhAhAh(i1,i2,i3)
Mex1 = MAh(i1)
Mex2 = MAh(i2)
Mex3 = MAh(i3)
If (Abs(Mex1).gt.(Abs(Mex2)+Abs(Mex3))) Then 
 Gammarealphoton(i1,i2,i3) = 0._dp 
  GammarealGluon(i1,i2,i3) = 0._dp 
Else 
  GammarealGluon(i1,i2,i3) = 0._dp 
  GammarealPhoton(i1,i2,i3) = 0._dp 

End if 
    End Do
  End Do
End Do
End Subroutine Gamma_Real_gumTHDMII_AhToAhAh


Subroutine Amplitude_WAVE_gumTHDMII_AhToAhAh(cplAhAhAh,ctcplAhAhAh,MAh,               & 
& MAh2,ZfAh,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MAh2(2)

Complex(dp), Intent(in) :: cplAhAhAh(2,2,2)

Complex(dp), Intent(in) :: ctcplAhAhAh(2,2,2)

Complex(dp), Intent(in) :: ZfAh(2,2)

Complex(dp), Intent(out) :: Amp(2,2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

Do gt1=1,2
  Do gt2=1,2
    Do gt3=1,2
! External masses 
Mex1 = MAh(gt1) 
Mex2 = MAh(gt2) 
Mex3 = MAh(gt3) 
!----------------------------- 
! Coupling counter term 
!----------------------------- 
ZcoupT1 = ctcplAhAhAh(gt1,gt2,gt3) 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
Do i1=1,2
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfAh(i1,gt1)*cplAhAhAh(i1,gt2,gt3)
End Do


! External Field 2 
Do i1=1,2
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfAh(i1,gt2)*cplAhAhAh(gt1,i1,gt3)
End Do


! External Field 3 
Do i1=1,2
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfAh(i1,gt3)*cplAhAhAh(gt1,gt2,i1)
End Do


! Getting the amplitude 
Call TreeAmp_StoSS(Mex1,Mex2,Mex3,ZcoupT1,AmpC) 
Amp(gt1, gt2, gt3) = AmpC 
    End Do
  End Do
End Do
End Subroutine Amplitude_WAVE_gumTHDMII_AhToAhAh


Subroutine Amplitude_VERTEX_gumTHDMII_AhToAhAh(MAh,MFd,MFe,MFu,Mhh,MHm,               & 
& MVWm,MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,     & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplAhAhAhAh1,    & 
& cplAhAhAhhh1,cplAhAhhhhh1,cplAhAhHmcHm1,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MFd(3),MFe(3),MFu(3),Mhh(2),MHm(2),MVWm,MVZ,MAh2(2),MFd2(3),MFe2(3),           & 
& MFu2(3),Mhh2(2),MHm2(2),MVWm2,MVZ2

Complex(dp), Intent(in) :: cplAhAhAh(2,2,2),cplAhAhhh(2,2,2),cplcFdFdAhL(3,3,2),cplcFdFdAhR(3,3,2),              & 
& cplcFeFeAhL(3,3,2),cplcFeFeAhR(3,3,2),cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),           & 
& cplcgWmgWmAh(2),cplcgWpCgWpCAh(2),cplAhhhhh(2,2,2),cplAhhhVZ(2,2),cplAhHmcHm(2,2,2),   & 
& cplAhHmcVWm(2,2),cplAhcHmVWm(2,2),cplAhAhAhAh1(2,2,2,2),cplAhAhAhhh1(2,2,2,2),         & 
& cplAhAhhhhh1(2,2,2,2),cplAhAhHmcHm1(2,2,2,2)

Complex(dp), Intent(out) :: Amp(2,2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,2
  Do gt2=1,2
    Do gt3=1,2
Amp(gt1, gt2, gt3) = 0._dp 
! External masses 
Mex1 = MAh(gt1) 
Mex2 = MAh(gt2) 
Mex3 = MAh(gt3) 


! {Ah, Ah, Ah}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MAh(i1) 
ML2 = MAh(i2) 
ML3 = MAh(i3) 
coup1 = cplAhAhAh(gt1,i1,i2)
coup2 = cplAhAhAh(gt2,i1,i3)
coup3 = cplAhAhAh(gt3,i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Ah, hh, Ah}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MAh(i1) 
ML2 = Mhh(i2) 
ML3 = MAh(i3) 
coup1 = cplAhAhhh(gt1,i1,i2)
coup2 = cplAhAhAh(gt2,i1,i3)
coup3 = cplAhAhhh(gt3,i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Ah, Ah, hh}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MAh(i1) 
ML2 = MAh(i2) 
ML3 = Mhh(i3) 
coup1 = cplAhAhAh(gt1,i1,i2)
coup2 = cplAhAhhh(gt2,i1,i3)
coup3 = cplAhAhhh(gt3,i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Ah, hh, hh}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MAh(i1) 
ML2 = Mhh(i2) 
ML3 = Mhh(i3) 
coup1 = cplAhAhhh(gt1,i1,i2)
coup2 = cplAhAhhh(gt2,i1,i3)
coup3 = cplAhhhhh(gt3,i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Fd, Fd, Fd}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFd(i1) 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFdFdAhL(i2,i1,gt1)
coup1R = cplcFdFdAhR(i2,i1,gt1)
coup2L = cplcFdFdAhL(i1,i3,gt2)
coup2R = cplcFdFdAhR(i1,i3,gt2)
coup3L = cplcFdFdAhL(i3,i2,gt3)
coup3R = cplcFdFdAhR(i3,i2,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(6)*AmpC 
    End Do
  End Do
End Do


! {Fe, Fe, Fe}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFe(i1) 
ML2 = MFe(i2) 
ML3 = MFe(i3) 
coup1L = cplcFeFeAhL(i2,i1,gt1)
coup1R = cplcFeFeAhR(i2,i1,gt1)
coup2L = cplcFeFeAhL(i1,i3,gt2)
coup2R = cplcFeFeAhR(i1,i3,gt2)
coup3L = cplcFeFeAhL(i3,i2,gt3)
coup3R = cplcFeFeAhR(i3,i2,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(2)*AmpC 
    End Do
  End Do
End Do


! {Fu, Fu, Fu}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFu(i1) 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = cplcFuFuAhL(i2,i1,gt1)
coup1R = cplcFuFuAhR(i2,i1,gt1)
coup2L = cplcFuFuAhL(i1,i3,gt2)
coup2R = cplcFuFuAhR(i1,i3,gt2)
coup3L = cplcFuFuAhL(i3,i2,gt3)
coup3R = cplcFuFuAhR(i3,i2,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(6)*AmpC 
    End Do
  End Do
End Do


! {gWm, gWm, gWm}
ML1 = MVWm 
ML2 = MVWm 
ML3 = MVWm 
coup1 = cplcgWmgWmAh(gt1)
coup2 = cplcgWmgWmAh(gt2)
coup3 = cplcgWmgWmAh(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(2)*AmpC 


! {gWmC, gWmC, gWmC}
ML1 = MVWm 
ML2 = MVWm 
ML3 = MVWm 
coup1 = cplcgWpCgWpCAh(gt1)
coup2 = cplcgWpCgWpCAh(gt2)
coup3 = cplcgWpCgWpCAh(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(2)*AmpC 


! {hh, Ah, Ah}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = Mhh(i1) 
ML2 = MAh(i2) 
ML3 = MAh(i3) 
coup1 = cplAhAhhh(gt1,i2,i1)
coup2 = cplAhAhhh(gt2,i3,i1)
coup3 = cplAhAhAh(gt3,i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {hh, hh, Ah}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = Mhh(i1) 
ML2 = Mhh(i2) 
ML3 = MAh(i3) 
coup1 = cplAhhhhh(gt1,i1,i2)
coup2 = cplAhAhhh(gt2,i3,i1)
coup3 = cplAhAhhh(gt3,i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {hh, Ah, hh}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = Mhh(i1) 
ML2 = MAh(i2) 
ML3 = Mhh(i3) 
coup1 = cplAhAhhh(gt1,i2,i1)
coup2 = cplAhhhhh(gt2,i1,i3)
coup3 = cplAhAhhh(gt3,i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {hh, hh, hh}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = Mhh(i1) 
ML2 = Mhh(i2) 
ML3 = Mhh(i3) 
coup1 = cplAhhhhh(gt1,i1,i2)
coup2 = cplAhhhhh(gt2,i1,i3)
coup3 = cplAhhhhh(gt3,i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {hh, VZ, hh}
Do i1=1,2
    Do i3=1,2
ML1 = Mhh(i1) 
ML2 = MVZ 
ML3 = Mhh(i3) 
coup1 = -cplAhhhVZ(gt1,i1)
coup2 = cplAhhhhh(gt2,i1,i3)
coup3 = cplAhhhVZ(gt3,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {hh, hh, VZ}
Do i1=1,2
  Do i2=1,2
ML1 = Mhh(i1) 
ML2 = Mhh(i2) 
ML3 = MVZ 
coup1 = cplAhhhhh(gt1,i1,i2)
coup2 = -cplAhhhVZ(gt2,i1)
coup3 = cplAhhhVZ(gt3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Hm, Hm, Hm}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
ML3 = MHm(i3) 
coup1 = cplAhHmcHm(gt1,i1,i2)
coup2 = cplAhHmcHm(gt2,i3,i1)
coup3 = cplAhHmcHm(gt3,i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(2)*AmpC 
    End Do
  End Do
End Do


! {Hm, VWm, Hm}
Do i1=1,2
    Do i3=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
ML3 = MHm(i3) 
coup1 = -cplAhHmcVWm(gt1,i1)
coup2 = cplAhHmcHm(gt2,i3,i1)
coup3 = cplAhcHmVWm(gt3,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hm, Hm, VWm}
Do i1=1,2
  Do i2=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
ML3 = MVWm 
coup1 = cplAhHmcHm(gt1,i1,i2)
coup2 = -cplAhcHmVWm(gt2,i1)
coup3 = cplAhHmcVWm(gt3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {VWm, Hm, Hm}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
ML3 = MHm(i3) 
coup1 = -cplAhcHmVWm(gt1,i2)
coup2 = -cplAhHmcVWm(gt2,i3)
coup3 = cplAhHmcHm(gt3,i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VZ, hh, hh}
  Do i2=1,2
    Do i3=1,2
ML1 = MVZ 
ML2 = Mhh(i2) 
ML3 = Mhh(i3) 
coup1 = -cplAhhhVZ(gt1,i2)
coup2 = -cplAhhhVZ(gt2,i3)
coup3 = cplAhhhhh(gt3,i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {conj[Hm], conj[VWm], conj[Hm]}
Do i1=1,2
    Do i3=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
ML3 = MHm(i3) 
coup1 = -cplAhcHmVWm(gt1,i1)
coup2 = cplAhHmcHm(gt2,i1,i3)
coup3 = cplAhHmcVWm(gt3,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {conj[Hm], conj[Hm], conj[VWm]}
Do i1=1,2
  Do i2=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
ML3 = MVWm 
coup1 = cplAhHmcHm(gt1,i2,i1)
coup2 = -cplAhHmcVWm(gt2,i1)
coup3 = cplAhcHmVWm(gt3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {conj[VWm], conj[Hm], conj[Hm]}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
ML3 = MHm(i3) 
coup1 = -cplAhHmcVWm(gt1,i2)
coup2 = -cplAhcHmVWm(gt2,i3)
coup3 = cplAhHmcHm(gt3,i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {Ah, Ah}
Do i1=1,2
  Do i2=1,2
ML1 = MAh(i1) 
ML2 = MAh(i2) 
coup1 = cplAhAhAh(gt1,i1,i2)
coup2 = cplAhAhAhAh1(gt2,gt3,i1,i2)
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1._dp/2._dp)*AmpC 
  End Do
End Do


! {Ah, hh}
Do i1=1,2
  Do i2=1,2
ML1 = MAh(i1) 
ML2 = Mhh(i2) 
coup1 = cplAhAhhh(gt1,i1,i2)
coup2 = cplAhAhAhhh1(gt2,gt3,i1,i2)
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {hh, hh}
Do i1=1,2
  Do i2=1,2
ML1 = Mhh(i1) 
ML2 = Mhh(i2) 
coup1 = cplAhhhhh(gt1,i1,i2)
coup2 = cplAhAhhhhh1(gt2,gt3,i1,i2)
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1._dp/2._dp)*AmpC 
  End Do
End Do


! {Hm, Hm}
Do i1=1,2
  Do i2=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
coup1 = cplAhHmcHm(gt1,i1,i2)
coup2 = cplAhAhHmcHm1(gt2,gt3,i2,i1)
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Ah, Ah}
Do i1=1,2
  Do i2=1,2
ML1 = MAh(i1) 
ML2 = MAh(i2) 
coup1 = cplAhAhAhAh1(gt1,gt3,i1,i2)
coup2 = cplAhAhAh(gt2,i1,i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1._dp/2._dp)*AmpC 

  End Do
End Do


! {Ah, hh}
Do i1=1,2
  Do i2=1,2
ML1 = MAh(i1) 
ML2 = Mhh(i2) 
coup1 = cplAhAhAhhh1(gt1,gt3,i1,i2)
coup2 = cplAhAhhh(gt2,i1,i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 

  End Do
End Do


! {hh, hh}
Do i1=1,2
  Do i2=1,2
ML1 = Mhh(i1) 
ML2 = Mhh(i2) 
coup1 = cplAhAhhhhh1(gt1,gt3,i1,i2)
coup2 = cplAhhhhh(gt2,i1,i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1._dp/2._dp)*AmpC 

  End Do
End Do


! {Hm, Hm}
Do i1=1,2
  Do i2=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
coup1 = cplAhAhHmcHm1(gt1,gt3,i1,i2)
coup2 = cplAhHmcHm(gt2,i2,i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 

  End Do
End Do


! {Ah, Ah}
Do i1=1,2
  Do i2=1,2
ML1 = MAh(i1) 
ML2 = MAh(i2) 
coup1 = cplAhAhAhAh1(gt1,gt2,i1,i2)
coup2 = cplAhAhAh(gt3,i1,i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1._dp/2._dp)*AmpC 

  End Do
End Do


! {Ah, hh}
Do i1=1,2
  Do i2=1,2
ML1 = MAh(i1) 
ML2 = Mhh(i2) 
coup1 = cplAhAhAhhh1(gt1,gt2,i1,i2)
coup2 = cplAhAhhh(gt3,i1,i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 

  End Do
End Do


! {hh, hh}
Do i1=1,2
  Do i2=1,2
ML1 = Mhh(i1) 
ML2 = Mhh(i2) 
coup1 = cplAhAhhhhh1(gt1,gt2,i1,i2)
coup2 = cplAhhhhh(gt3,i1,i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1._dp/2._dp)*AmpC 

  End Do
End Do


! {Hm, Hm}
Do i1=1,2
  Do i2=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
coup1 = cplAhAhHmcHm1(gt1,gt2,i1,i2)
coup2 = cplAhHmcHm(gt3,i2,i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 

  End Do
End Do
    End Do
  End Do
End Do
End Subroutine Amplitude_VERTEX_gumTHDMII_AhToAhAh


Subroutine Amplitude_IR_VERTEX_gumTHDMII_AhToAhAh(MAh,MFd,MFe,MFu,Mhh,MHm,            & 
& MVWm,MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,     & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplAhAhAhAh1,    & 
& cplAhAhAhhh1,cplAhAhhhhh1,cplAhAhHmcHm1,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MFd(3),MFe(3),MFu(3),Mhh(2),MHm(2),MVWm,MVZ,MAh2(2),MFd2(3),MFe2(3),           & 
& MFu2(3),Mhh2(2),MHm2(2),MVWm2,MVZ2

Complex(dp), Intent(in) :: cplAhAhAh(2,2,2),cplAhAhhh(2,2,2),cplcFdFdAhL(3,3,2),cplcFdFdAhR(3,3,2),              & 
& cplcFeFeAhL(3,3,2),cplcFeFeAhR(3,3,2),cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),           & 
& cplcgWmgWmAh(2),cplcgWpCgWpCAh(2),cplAhhhhh(2,2,2),cplAhhhVZ(2,2),cplAhHmcHm(2,2,2),   & 
& cplAhHmcVWm(2,2),cplAhcHmVWm(2,2),cplAhAhAhAh1(2,2,2,2),cplAhAhAhhh1(2,2,2,2),         & 
& cplAhAhhhhh1(2,2,2,2),cplAhAhHmcHm1(2,2,2,2)

Complex(dp), Intent(out) :: Amp(2,2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,2
  Do gt2=1,2
    Do gt3=1,2
Amp(gt1, gt2, gt3) = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = MAh(gt1) 
Mex2 = MAh(gt2) 
Mex3 = MAh(gt3) 
    End Do
  End Do
End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_gumTHDMII_AhToAhAh


Subroutine Amplitude_Tree_gumTHDMII_AhTohhAh(cplAhAhhh,MAh,Mhh,MAh2,Mhh2,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),Mhh(2),MAh2(2),Mhh2(2)

Complex(dp), Intent(in) :: cplAhAhhh(2,2,2)

Complex(dp) :: Amp(2,2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 

Do gt1=1,2
  Do gt2=1,2
    Do gt3=1,2
! External masses 
Mex1 = MAh(gt1) 
Mex2 = Mhh(gt2) 
Mex3 = MAh(gt3) 
! Tree-Level Vertex 
coupT1 = cplAhAhhh(gt1,gt3,gt2)
Call TreeAmp_StoSS(Mex1,Mex2,Mex3,coupT1,AmpC) 
! Colour and symmetry factor 
Amp(gt1, gt2, gt3) = AmpC 
    End Do
  End Do
End Do
End Subroutine Amplitude_Tree_gumTHDMII_AhTohhAh


Subroutine Gamma_Real_gumTHDMII_AhTohhAh(MLambda,em,gs,cplAhAhhh,MAh,Mhh,             & 
& GammarealPhoton,GammarealGluon)

Implicit None

Complex(dp), Intent(in) :: cplAhAhhh(2,2,2)

Real(dp), Intent(in) :: MAh(2),Mhh(2)

Real(dp), Intent(in) :: MLambda, em, gs 

Real(dp), Intent(out) :: GammarealPhoton(2,2,2), GammarealGluon(2,2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 

Real(dp) :: Mloop1, Mloop2, Mloop3 
Complex(dp) :: Coup 
 
Do i1=2,2
  Do i2=1,2
    Do i3=2,2
Coup = cplAhAhhh(i1,i3,i2)
Mex1 = MAh(i1)
Mex2 = Mhh(i2)
Mex3 = MAh(i3)
If (Abs(Mex1).gt.(Abs(Mex2)+Abs(Mex3))) Then 
 Gammarealphoton(i1,i2,i3) = 0._dp 
  GammarealGluon(i1,i2,i3) = 0._dp 
Else 
  GammarealGluon(i1,i2,i3) = 0._dp 
  GammarealPhoton(i1,i2,i3) = 0._dp 

End if 
    End Do
  End Do
End Do
End Subroutine Gamma_Real_gumTHDMII_AhTohhAh


Subroutine Amplitude_WAVE_gumTHDMII_AhTohhAh(cplAhAhhh,ctcplAhAhhh,MAh,               & 
& MAh2,Mhh,Mhh2,ZfAh,Zfhh,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MAh2(2),Mhh(2),Mhh2(2)

Complex(dp), Intent(in) :: cplAhAhhh(2,2,2)

Complex(dp), Intent(in) :: ctcplAhAhhh(2,2,2)

Complex(dp), Intent(in) :: ZfAh(2,2),Zfhh(2,2)

Complex(dp), Intent(out) :: Amp(2,2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

Do gt1=1,2
  Do gt2=1,2
    Do gt3=1,2
! External masses 
Mex1 = MAh(gt1) 
Mex2 = Mhh(gt2) 
Mex3 = MAh(gt3) 
!----------------------------- 
! Coupling counter term 
!----------------------------- 
ZcoupT1 = ctcplAhAhhh(gt1,gt3,gt2) 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
Do i1=1,2
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfAh(i1,gt1)*cplAhAhhh(i1,gt3,gt2)
End Do


! External Field 2 
Do i1=1,2
ZcoupT1 = ZcoupT1 + 0.5_dp*Zfhh(i1,gt2)*cplAhAhhh(gt1,gt3,i1)
End Do


! External Field 3 
Do i1=1,2
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfAh(i1,gt3)*cplAhAhhh(gt1,i1,gt2)
End Do


! Getting the amplitude 
Call TreeAmp_StoSS(Mex1,Mex2,Mex3,ZcoupT1,AmpC) 
Amp(gt1, gt2, gt3) = AmpC 
    End Do
  End Do
End Do
End Subroutine Amplitude_WAVE_gumTHDMII_AhTohhAh


Subroutine Amplitude_VERTEX_gumTHDMII_AhTohhAh(MAh,MFd,MFe,MFu,Mhh,MHm,               & 
& MVWm,MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,     & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,     & 
& cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplcgWmgWmhh,              & 
& cplcgWpCgWpChh,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,              & 
& cplhhVZVZ,cplAhAhAhAh1,cplAhAhAhhh1,cplAhAhhhhh1,cplAhAhHmcHm1,cplAhAhcVWmVWm1,        & 
& cplAhAhVZVZ1,cplAhhhhhhh1,cplAhhhHmcHm1,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MFd(3),MFe(3),MFu(3),Mhh(2),MHm(2),MVWm,MVZ,MAh2(2),MFd2(3),MFe2(3),           & 
& MFu2(3),Mhh2(2),MHm2(2),MVWm2,MVZ2

Complex(dp), Intent(in) :: cplAhAhAh(2,2,2),cplAhAhhh(2,2,2),cplcFdFdAhL(3,3,2),cplcFdFdAhR(3,3,2),              & 
& cplcFeFeAhL(3,3,2),cplcFeFeAhR(3,3,2),cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),           & 
& cplcgWmgWmAh(2),cplcgWpCgWpCAh(2),cplAhhhhh(2,2,2),cplAhhhVZ(2,2),cplAhHmcHm(2,2,2),   & 
& cplAhHmcVWm(2,2),cplAhcHmVWm(2,2),cplcFdFdhhL(3,3,2),cplcFdFdhhR(3,3,2),               & 
& cplcFeFehhL(3,3,2),cplcFeFehhR(3,3,2),cplcFuFuhhL(3,3,2),cplcFuFuhhR(3,3,2),           & 
& cplcgWmgWmhh(2),cplcgWpCgWpChh(2),cplhhhhhh(2,2,2),cplhhHmcHm(2,2,2),cplhhHmcVWm(2,2), & 
& cplhhcHmVWm(2,2),cplhhcVWmVWm(2),cplhhVZVZ(2),cplAhAhAhAh1(2,2,2,2),cplAhAhAhhh1(2,2,2,2),& 
& cplAhAhhhhh1(2,2,2,2),cplAhAhHmcHm1(2,2,2,2),cplAhAhcVWmVWm1(2,2),cplAhAhVZVZ1(2,2),   & 
& cplAhhhhhhh1(2,2,2,2),cplAhhhHmcHm1(2,2,2,2)

Complex(dp), Intent(out) :: Amp(2,2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,2
  Do gt2=1,2
    Do gt3=1,2
Amp(gt1, gt2, gt3) = 0._dp 
! External masses 
Mex1 = MAh(gt1) 
Mex2 = Mhh(gt2) 
Mex3 = MAh(gt3) 


! {Ah, Ah, Ah}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MAh(i1) 
ML2 = MAh(i2) 
ML3 = MAh(i3) 
coup1 = cplAhAhAh(gt1,i1,i2)
coup2 = cplAhAhhh(i1,i3,gt2)
coup3 = cplAhAhAh(gt3,i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Ah, hh, Ah}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MAh(i1) 
ML2 = Mhh(i2) 
ML3 = MAh(i3) 
coup1 = cplAhAhhh(gt1,i1,i2)
coup2 = cplAhAhhh(i1,i3,gt2)
coup3 = cplAhAhhh(gt3,i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Ah, Ah, hh}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MAh(i1) 
ML2 = MAh(i2) 
ML3 = Mhh(i3) 
coup1 = cplAhAhAh(gt1,i1,i2)
coup2 = cplAhhhhh(i1,gt2,i3)
coup3 = cplAhAhhh(gt3,i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Ah, hh, hh}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MAh(i1) 
ML2 = Mhh(i2) 
ML3 = Mhh(i3) 
coup1 = cplAhAhhh(gt1,i1,i2)
coup2 = cplAhhhhh(i1,gt2,i3)
coup3 = cplAhhhhh(gt3,i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Ah, hh, VZ}
Do i1=1,2
  Do i2=1,2
ML1 = MAh(i1) 
ML2 = Mhh(i2) 
ML3 = MVZ 
coup1 = cplAhAhhh(gt1,i1,i2)
coup2 = cplAhhhVZ(i1,gt2)
coup3 = cplAhhhVZ(gt3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Fd, Fd, Fd}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFd(i1) 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFdFdAhL(i2,i1,gt1)
coup1R = cplcFdFdAhR(i2,i1,gt1)
coup2L = cplcFdFdhhL(i1,i3,gt2)
coup2R = cplcFdFdhhR(i1,i3,gt2)
coup3L = cplcFdFdAhL(i3,i2,gt3)
coup3R = cplcFdFdAhR(i3,i2,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(6)*AmpC 
    End Do
  End Do
End Do


! {Fe, Fe, Fe}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFe(i1) 
ML2 = MFe(i2) 
ML3 = MFe(i3) 
coup1L = cplcFeFeAhL(i2,i1,gt1)
coup1R = cplcFeFeAhR(i2,i1,gt1)
coup2L = cplcFeFehhL(i1,i3,gt2)
coup2R = cplcFeFehhR(i1,i3,gt2)
coup3L = cplcFeFeAhL(i3,i2,gt3)
coup3R = cplcFeFeAhR(i3,i2,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(2)*AmpC 
    End Do
  End Do
End Do


! {Fu, Fu, Fu}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFu(i1) 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = cplcFuFuAhL(i2,i1,gt1)
coup1R = cplcFuFuAhR(i2,i1,gt1)
coup2L = cplcFuFuhhL(i1,i3,gt2)
coup2R = cplcFuFuhhR(i1,i3,gt2)
coup3L = cplcFuFuAhL(i3,i2,gt3)
coup3R = cplcFuFuAhR(i3,i2,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(6)*AmpC 
    End Do
  End Do
End Do


! {gWm, gWm, gWm}
ML1 = MVWm 
ML2 = MVWm 
ML3 = MVWm 
coup1 = cplcgWmgWmAh(gt1)
coup2 = cplcgWmgWmhh(gt2)
coup3 = cplcgWmgWmAh(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(2)*AmpC 


! {gWmC, gWmC, gWmC}
ML1 = MVWm 
ML2 = MVWm 
ML3 = MVWm 
coup1 = cplcgWpCgWpCAh(gt1)
coup2 = cplcgWpCgWpChh(gt2)
coup3 = cplcgWpCgWpCAh(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(2)*AmpC 


! {hh, Ah, Ah}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = Mhh(i1) 
ML2 = MAh(i2) 
ML3 = MAh(i3) 
coup1 = cplAhAhhh(gt1,i2,i1)
coup2 = cplAhhhhh(i3,gt2,i1)
coup3 = cplAhAhAh(gt3,i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {hh, hh, Ah}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = Mhh(i1) 
ML2 = Mhh(i2) 
ML3 = MAh(i3) 
coup1 = cplAhhhhh(gt1,i1,i2)
coup2 = cplAhhhhh(i3,gt2,i1)
coup3 = cplAhAhhh(gt3,i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {hh, Ah, hh}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = Mhh(i1) 
ML2 = MAh(i2) 
ML3 = Mhh(i3) 
coup1 = cplAhAhhh(gt1,i2,i1)
coup2 = cplhhhhhh(gt2,i1,i3)
coup3 = cplAhAhhh(gt3,i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {hh, hh, hh}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = Mhh(i1) 
ML2 = Mhh(i2) 
ML3 = Mhh(i3) 
coup1 = cplAhhhhh(gt1,i1,i2)
coup2 = cplhhhhhh(gt2,i1,i3)
coup3 = cplAhhhhh(gt3,i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {hh, VZ, hh}
Do i1=1,2
    Do i3=1,2
ML1 = Mhh(i1) 
ML2 = MVZ 
ML3 = Mhh(i3) 
coup1 = -cplAhhhVZ(gt1,i1)
coup2 = cplhhhhhh(gt2,i1,i3)
coup3 = cplAhhhVZ(gt3,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hm, Hm, Hm}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
ML3 = MHm(i3) 
coup1 = cplAhHmcHm(gt1,i1,i2)
coup2 = cplhhHmcHm(gt2,i3,i1)
coup3 = cplAhHmcHm(gt3,i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(2)*AmpC 
    End Do
  End Do
End Do


! {Hm, VWm, Hm}
Do i1=1,2
    Do i3=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
ML3 = MHm(i3) 
coup1 = -cplAhHmcVWm(gt1,i1)
coup2 = cplhhHmcHm(gt2,i3,i1)
coup3 = cplAhcHmVWm(gt3,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hm, Hm, VWm}
Do i1=1,2
  Do i2=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
ML3 = MVWm 
coup1 = cplAhHmcHm(gt1,i1,i2)
coup2 = -cplhhcHmVWm(gt2,i1)
coup3 = cplAhHmcVWm(gt3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {VWm, Hm, Hm}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
ML3 = MHm(i3) 
coup1 = -cplAhcHmVWm(gt1,i2)
coup2 = -cplhhHmcVWm(gt2,i3)
coup3 = cplAhHmcHm(gt3,i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VWm, Hm, VWm}
  Do i2=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
ML3 = MVWm 
coup1 = -cplAhcHmVWm(gt1,i2)
coup2 = cplhhcVWmVWm(gt2)
coup3 = cplAhHmcVWm(gt3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do


! {VZ, hh, Ah}
  Do i2=1,2
    Do i3=1,2
ML1 = MVZ 
ML2 = Mhh(i2) 
ML3 = MAh(i3) 
coup1 = -cplAhhhVZ(gt1,i2)
coup2 = cplAhhhVZ(i3,gt2)
coup3 = cplAhAhhh(gt3,i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VZ, hh, VZ}
  Do i2=1,2
ML1 = MVZ 
ML2 = Mhh(i2) 
ML3 = MVZ 
coup1 = -cplAhhhVZ(gt1,i2)
coup2 = cplhhVZVZ(gt2)
coup3 = cplAhhhVZ(gt3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do


! {conj[Hm], conj[VWm], conj[Hm]}
Do i1=1,2
    Do i3=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
ML3 = MHm(i3) 
coup1 = -cplAhcHmVWm(gt1,i1)
coup2 = cplhhHmcHm(gt2,i1,i3)
coup3 = cplAhHmcVWm(gt3,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {conj[Hm], conj[Hm], conj[VWm]}
Do i1=1,2
  Do i2=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
ML3 = MVWm 
coup1 = cplAhHmcHm(gt1,i2,i1)
coup2 = -cplhhHmcVWm(gt2,i1)
coup3 = cplAhcHmVWm(gt3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {conj[VWm], conj[Hm], conj[Hm]}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
ML3 = MHm(i3) 
coup1 = -cplAhHmcVWm(gt1,i2)
coup2 = -cplhhcHmVWm(gt2,i3)
coup3 = cplAhHmcHm(gt3,i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {conj[VWm], conj[Hm], conj[VWm]}
  Do i2=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
ML3 = MVWm 
coup1 = -cplAhHmcVWm(gt1,i2)
coup2 = cplhhcVWmVWm(gt2)
coup3 = cplAhcHmVWm(gt3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do


! {Ah, Ah}
Do i1=1,2
  Do i2=1,2
ML1 = MAh(i1) 
ML2 = MAh(i2) 
coup1 = cplAhAhAh(gt1,i1,i2)
coup2 = cplAhAhAhhh1(gt3,i1,i2,gt2)
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1._dp/2._dp)*AmpC 
  End Do
End Do


! {Ah, hh}
Do i1=1,2
  Do i2=1,2
ML1 = MAh(i1) 
ML2 = Mhh(i2) 
coup1 = cplAhAhhh(gt1,i1,i2)
coup2 = cplAhAhhhhh1(gt3,i1,gt2,i2)
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {hh, hh}
Do i1=1,2
  Do i2=1,2
ML1 = Mhh(i1) 
ML2 = Mhh(i2) 
coup1 = cplAhhhhh(gt1,i1,i2)
coup2 = cplAhhhhhhh1(gt3,gt2,i1,i2)
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1._dp/2._dp)*AmpC 
  End Do
End Do


! {Hm, Hm}
Do i1=1,2
  Do i2=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
coup1 = cplAhHmcHm(gt1,i1,i2)
coup2 = cplAhhhHmcHm1(gt3,gt2,i2,i1)
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Ah, Ah}
Do i1=1,2
  Do i2=1,2
ML1 = MAh(i1) 
ML2 = MAh(i2) 
coup1 = cplAhAhAhAh1(gt1,gt3,i1,i2)
coup2 = cplAhAhhh(i1,i2,gt2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1._dp/2._dp)*AmpC 

  End Do
End Do


! {Ah, hh}
Do i1=1,2
  Do i2=1,2
ML1 = MAh(i1) 
ML2 = Mhh(i2) 
coup1 = cplAhAhAhhh1(gt1,gt3,i1,i2)
coup2 = cplAhhhhh(i1,gt2,i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 

  End Do
End Do


! {hh, hh}
Do i1=1,2
  Do i2=1,2
ML1 = Mhh(i1) 
ML2 = Mhh(i2) 
coup1 = cplAhAhhhhh1(gt1,gt3,i1,i2)
coup2 = cplhhhhhh(gt2,i1,i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1._dp/2._dp)*AmpC 

  End Do
End Do


! {Hm, Hm}
Do i1=1,2
  Do i2=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
coup1 = cplAhAhHmcHm1(gt1,gt3,i1,i2)
coup2 = cplhhHmcHm(gt2,i2,i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 

  End Do
End Do


! {VWm, VWm}
ML1 = MVWm 
ML2 = MVWm 
coup1 = cplAhAhcVWmVWm1(gt1,gt3)
coup2 = cplhhcVWmVWm(gt2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 



! {VZ, VZ}
ML1 = MVZ 
ML2 = MVZ 
coup1 = cplAhAhVZVZ1(gt1,gt3)
coup2 = cplhhVZVZ(gt2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1._dp/2._dp)*AmpC 



! {Ah, Ah}
Do i1=1,2
  Do i2=1,2
ML1 = MAh(i1) 
ML2 = MAh(i2) 
coup1 = cplAhAhAhhh1(gt1,i1,i2,gt2)
coup2 = cplAhAhAh(gt3,i1,i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1._dp/2._dp)*AmpC 

  End Do
End Do


! {Ah, hh}
Do i1=1,2
  Do i2=1,2
ML1 = MAh(i1) 
ML2 = Mhh(i2) 
coup1 = cplAhAhhhhh1(gt1,i1,gt2,i2)
coup2 = cplAhAhhh(gt3,i1,i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 

  End Do
End Do


! {hh, hh}
Do i1=1,2
  Do i2=1,2
ML1 = Mhh(i1) 
ML2 = Mhh(i2) 
coup1 = cplAhhhhhhh1(gt1,gt2,i1,i2)
coup2 = cplAhhhhh(gt3,i1,i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1._dp/2._dp)*AmpC 

  End Do
End Do


! {Hm, Hm}
Do i1=1,2
  Do i2=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
coup1 = cplAhhhHmcHm1(gt1,gt2,i1,i2)
coup2 = cplAhHmcHm(gt3,i2,i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 

  End Do
End Do
    End Do
  End Do
End Do
End Subroutine Amplitude_VERTEX_gumTHDMII_AhTohhAh


Subroutine Amplitude_IR_VERTEX_gumTHDMII_AhTohhAh(MAh,MFd,MFe,MFu,Mhh,MHm,            & 
& MVWm,MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,     & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,     & 
& cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplcgWmgWmhh,              & 
& cplcgWpCgWpChh,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,              & 
& cplhhVZVZ,cplAhAhAhAh1,cplAhAhAhhh1,cplAhAhhhhh1,cplAhAhHmcHm1,cplAhAhcVWmVWm1,        & 
& cplAhAhVZVZ1,cplAhhhhhhh1,cplAhhhHmcHm1,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MFd(3),MFe(3),MFu(3),Mhh(2),MHm(2),MVWm,MVZ,MAh2(2),MFd2(3),MFe2(3),           & 
& MFu2(3),Mhh2(2),MHm2(2),MVWm2,MVZ2

Complex(dp), Intent(in) :: cplAhAhAh(2,2,2),cplAhAhhh(2,2,2),cplcFdFdAhL(3,3,2),cplcFdFdAhR(3,3,2),              & 
& cplcFeFeAhL(3,3,2),cplcFeFeAhR(3,3,2),cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),           & 
& cplcgWmgWmAh(2),cplcgWpCgWpCAh(2),cplAhhhhh(2,2,2),cplAhhhVZ(2,2),cplAhHmcHm(2,2,2),   & 
& cplAhHmcVWm(2,2),cplAhcHmVWm(2,2),cplcFdFdhhL(3,3,2),cplcFdFdhhR(3,3,2),               & 
& cplcFeFehhL(3,3,2),cplcFeFehhR(3,3,2),cplcFuFuhhL(3,3,2),cplcFuFuhhR(3,3,2),           & 
& cplcgWmgWmhh(2),cplcgWpCgWpChh(2),cplhhhhhh(2,2,2),cplhhHmcHm(2,2,2),cplhhHmcVWm(2,2), & 
& cplhhcHmVWm(2,2),cplhhcVWmVWm(2),cplhhVZVZ(2),cplAhAhAhAh1(2,2,2,2),cplAhAhAhhh1(2,2,2,2),& 
& cplAhAhhhhh1(2,2,2,2),cplAhAhHmcHm1(2,2,2,2),cplAhAhcVWmVWm1(2,2),cplAhAhVZVZ1(2,2),   & 
& cplAhhhhhhh1(2,2,2,2),cplAhhhHmcHm1(2,2,2,2)

Complex(dp), Intent(out) :: Amp(2,2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,2
  Do gt2=1,2
    Do gt3=1,2
Amp(gt1, gt2, gt3) = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = MAh(gt1) 
Mex2 = Mhh(gt2) 
Mex3 = MAh(gt3) 
    End Do
  End Do
End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_gumTHDMII_AhTohhAh


Subroutine Amplitude_Tree_gumTHDMII_AhTocFdFd(cplcFdFdAhL,cplcFdFdAhR,MAh,            & 
& MFd,MAh2,MFd2,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MFd(3),MAh2(2),MFd2(3)

Complex(dp), Intent(in) :: cplcFdFdAhL(3,3,2),cplcFdFdAhR(3,3,2)

Complex(dp) :: Amp(2,2,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 

Do gt1=1,2
  Do gt2=1,3
    Do gt3=1,3
! External masses 
Mex1 = MAh(gt1) 
Mex2 = MFd(gt2) 
Mex3 = MFd(gt3) 
! Tree-Level Vertex 
coupT1L = cplcFdFdAhL(gt2,gt3,gt1)
coupT1R = cplcFdFdAhR(gt2,gt3,gt1)
Call TreeAmp_StoFF(Mex1,Mex2,Mex3,coupT1L,coupT1R,AmpC) 
! Colour and symmetry factor 
Amp(:,gt1, gt2, gt3) = AmpC 
    End Do
  End Do
End Do
End Subroutine Amplitude_Tree_gumTHDMII_AhTocFdFd


Subroutine Gamma_Real_gumTHDMII_AhTocFdFd(MLambda,em,gs,cplcFdFdAhL,cplcFdFdAhR,      & 
& MAh,MFd,GammarealPhoton,GammarealGluon)

Implicit None

Complex(dp), Intent(in) :: cplcFdFdAhL(3,3,2),cplcFdFdAhR(3,3,2)

Real(dp), Intent(in) :: MAh(2),MFd(3)

Real(dp), Intent(in) :: MLambda, em, gs 

Real(dp), Intent(out) :: GammarealPhoton(2,3,3), GammarealGluon(2,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 

Real(dp) :: Mloop1, Mloop2, Mloop3 
Complex(dp) :: CoupL, CoupR 
 
Do i1=2,2
  Do i2=1,3
    Do i3=1,3
CoupL = cplcFdFdAhL(i2,i3,i1)
CoupR = cplcFdFdAhR(i2,i3,i1)
Mex1 = MAh(i1)
Mex2 = MFd(i2)
Mex3 = MFd(i3)
If (Abs(Mex1).gt.(Abs(Mex2)+Abs(Mex3))) Then 
 Call hardradiationSFF(Mex1,Mex2,Mex3,MLambda,em,0._dp,0._dp,0._dp,1._dp/3._dp,-1._dp/3._dp,1._dp/3._dp,CoupL,CoupR,Gammarealphoton(i1,i2,i3),kont)
 Call hardradiationSFF(Mex1,Mex2,Mex3,MLambda,gs,0._dp,0._dp,0._dp,4._dp,-4._dp,4._dp,CoupL,CoupR,Gammarealgluon(i1,i2,i3),kont)
Else 
  GammarealGluon(i1,i2,i3) = 0._dp 
  GammarealPhoton(i1,i2,i3) = 0._dp 

End if 
    End Do
  End Do
End Do
End Subroutine Gamma_Real_gumTHDMII_AhTocFdFd


Subroutine Amplitude_WAVE_gumTHDMII_AhTocFdFd(cplcFdFdAhL,cplcFdFdAhR,ctcplcFdFdAhL,  & 
& ctcplcFdFdAhR,MAh,MAh2,MFd,MFd2,ZfAh,ZfDL,ZfDR,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MAh2(2),MFd(3),MFd2(3)

Complex(dp), Intent(in) :: cplcFdFdAhL(3,3,2),cplcFdFdAhR(3,3,2)

Complex(dp), Intent(in) :: ctcplcFdFdAhL(3,3,2),ctcplcFdFdAhR(3,3,2)

Complex(dp), Intent(in) :: ZfAh(2,2),ZfDL(3,3),ZfDR(3,3)

Complex(dp), Intent(out) :: Amp(2,2,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

Do gt1=1,2
  Do gt2=1,3
    Do gt3=1,3
! External masses 
Mex1 = MAh(gt1) 
Mex2 = MFd(gt2) 
Mex3 = MFd(gt3) 
!----------------------------- 
! Coupling counter term 
!----------------------------- 
ZcoupT1L = ctcplcFdFdAhL(gt2,gt3,gt1) 
ZcoupT1R = ctcplcFdFdAhR(gt2,gt3,gt1) 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
Do i1=1,2
ZcoupT1L = ZcoupT1L + 0.5_dp*ZfAh(i1,gt1)*cplcFdFdAhL(gt2,gt3,i1)
ZcoupT1R = ZcoupT1R + 0.5_dp*ZfAh(i1,gt1)*cplcFdFdAhR(gt2,gt3,i1)
End Do


! External Field 2 
Do i1=1,3
ZcoupT1L = ZcoupT1L + 0.5_dp*ZfDR(i1,gt2)*cplcFdFdAhL(i1,gt3,gt1)
ZcoupT1R = ZcoupT1R + 0.5_dp*Conjg(ZfDL(i1,gt2))*cplcFdFdAhR(i1,gt3,gt1)
End Do


! External Field 3 
Do i1=1,3
ZcoupT1L = ZcoupT1L + 0.5_dp*ZfDL(i1,gt3)*cplcFdFdAhL(gt2,i1,gt1)
ZcoupT1R = ZcoupT1R + 0.5_dp*Conjg(ZfDR(i1,gt3))*cplcFdFdAhR(gt2,i1,gt1)
End Do


! Getting the amplitude 
Call TreeAmp_StoFF(Mex1,Mex2,Mex3,ZcoupT1L,ZcoupT1R,AmpC) 
Amp(:,gt1, gt2, gt3) = AmpC 
    End Do
  End Do
End Do
End Subroutine Amplitude_WAVE_gumTHDMII_AhTocFdFd


Subroutine Amplitude_VERTEX_gumTHDMII_AhTocFdFd(MAh,MFd,MFu,Mhh,MHm,MVG,              & 
& MVP,MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,        & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,        & 
& cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,               & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHmL,cplcFuFdcHmR,             & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFdFuHmL,cplcFdFuHmR,cplcFdFuVWmL,cplcFdFuVWmR,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MFd(3),MFu(3),Mhh(2),MHm(2),MVG,MVP,MVWm,MVZ,MAh2(2),MFd2(3),MFu2(3),          & 
& Mhh2(2),MHm2(2),MVG2,MVP2,MVWm2,MVZ2

Complex(dp), Intent(in) :: cplAhAhAh(2,2,2),cplAhAhhh(2,2,2),cplcFdFdAhL(3,3,2),cplcFdFdAhR(3,3,2),              & 
& cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),cplAhhhhh(2,2,2),cplAhhhVZ(2,2),cplAhHmcHm(2,2,2),& 
& cplAhHmcVWm(2,2),cplAhcHmVWm(2,2),cplcFdFdhhL(3,3,2),cplcFdFdhhR(3,3,2),               & 
& cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),cplcFdFdVZL(3,3),  & 
& cplcFdFdVZR(3,3),cplcFuFdcHmL(3,3,2),cplcFuFdcHmR(3,3,2),cplcFuFdcVWmL(3,3),           & 
& cplcFuFdcVWmR(3,3),cplcFdFuHmL(3,3,2),cplcFdFuHmR(3,3,2),cplcFdFuVWmL(3,3),            & 
& cplcFdFuVWmR(3,3)

Complex(dp), Intent(out) :: Amp(2,2,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,2
  Do gt2=1,3
    Do gt3=1,3
Amp(:,gt1, gt2, gt3) = 0._dp 
! External masses 
Mex1 = MAh(gt1) 
Mex2 = MFd(gt2) 
Mex3 = MFd(gt3) 


! {Ah, Ah, Fd}
Do i1=1,2
  Do i2=1,2
    Do i3=1,3
ML1 = MAh(i1) 
ML2 = MAh(i2) 
ML3 = MFd(i3) 
coup1 = cplAhAhAh(gt1,i1,i2)
coup2L = cplcFdFdAhL(gt2,i3,i1)
coup2R = cplcFdFdAhR(gt2,i3,i1)
coup3L = cplcFdFdAhL(i3,gt3,i2)
coup3R = cplcFdFdAhR(i3,gt3,i2)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_SSF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Ah, hh, Fd}
Do i1=1,2
  Do i2=1,2
    Do i3=1,3
ML1 = MAh(i1) 
ML2 = Mhh(i2) 
ML3 = MFd(i3) 
coup1 = cplAhAhhh(gt1,i1,i2)
coup2L = cplcFdFdAhL(gt2,i3,i1)
coup2R = cplcFdFdAhR(gt2,i3,i1)
coup3L = cplcFdFdhhL(i3,gt3,i2)
coup3R = cplcFdFdhhR(i3,gt3,i2)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_SSF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {hh, Ah, Fd}
Do i1=1,2
  Do i2=1,2
    Do i3=1,3
ML1 = Mhh(i1) 
ML2 = MAh(i2) 
ML3 = MFd(i3) 
coup1 = cplAhAhhh(gt1,i2,i1)
coup2L = cplcFdFdhhL(gt2,i3,i1)
coup2R = cplcFdFdhhR(gt2,i3,i1)
coup3L = cplcFdFdAhL(i3,gt3,i2)
coup3R = cplcFdFdAhR(i3,gt3,i2)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_SSF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {hh, hh, Fd}
Do i1=1,2
  Do i2=1,2
    Do i3=1,3
ML1 = Mhh(i1) 
ML2 = Mhh(i2) 
ML3 = MFd(i3) 
coup1 = cplAhhhhh(gt1,i1,i2)
coup2L = cplcFdFdhhL(gt2,i3,i1)
coup2R = cplcFdFdhhR(gt2,i3,i1)
coup3L = cplcFdFdhhL(i3,gt3,i2)
coup3R = cplcFdFdhhR(i3,gt3,i2)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_SSF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {hh, VZ, Fd}
Do i1=1,2
    Do i3=1,3
ML1 = Mhh(i1) 
ML2 = MVZ 
ML3 = MFd(i3) 
coup1 = cplAhhhVZ(gt1,i1)
coup2L = cplcFdFdhhL(gt2,i3,i1)
coup2R = cplcFdFdhhR(gt2,i3,i1)
coup3L = cplcFdFdVZL(i3,gt3)
coup3R = cplcFdFdVZR(i3,gt3)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_SVF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {VZ, hh, Fd}
  Do i2=1,2
    Do i3=1,3
ML1 = MVZ 
ML2 = Mhh(i2) 
ML3 = MFd(i3) 
coup1 = cplAhhhVZ(gt1,i2)
coup2L = cplcFdFdVZL(gt2,i3)
coup2R = cplcFdFdVZR(gt2,i3)
coup3L = cplcFdFdhhL(i3,gt3,i2)
coup3R = cplcFdFdhhR(i3,gt3,i2)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_VSF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {bar[Fd], bar[Fd], Ah}
Do i1=1,3
  Do i2=1,3
    Do i3=1,2
ML1 = MFd(i1) 
ML2 = MFd(i2) 
ML3 = MAh(i3) 
coup1L = cplcFdFdAhL(i1,i2,gt1)
coup1R = cplcFdFdAhR(i1,i2,gt1)
coup2L = cplcFdFdAhL(gt2,i1,i3)
coup2R = cplcFdFdAhR(gt2,i1,i3)
coup3L = cplcFdFdAhL(i2,gt3,i3)
coup3R = cplcFdFdAhR(i2,gt3,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_FFS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {bar[Fd], bar[Fd], hh}
Do i1=1,3
  Do i2=1,3
    Do i3=1,2
ML1 = MFd(i1) 
ML2 = MFd(i2) 
ML3 = Mhh(i3) 
coup1L = cplcFdFdAhL(i1,i2,gt1)
coup1R = cplcFdFdAhR(i1,i2,gt1)
coup2L = cplcFdFdhhL(gt2,i1,i3)
coup2R = cplcFdFdhhR(gt2,i1,i3)
coup3L = cplcFdFdhhL(i2,gt3,i3)
coup3R = cplcFdFdhhR(i2,gt3,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_FFS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {bar[Fd], bar[Fd], VG}
Do i1=1,3
  Do i2=1,3
ML1 = MFd(i1) 
ML2 = MFd(i2) 
ML3 = MVG 
coup1L = cplcFdFdAhL(i1,i2,gt1)
coup1R = cplcFdFdAhR(i1,i2,gt1)
coup2L = cplcFdFdVGL(gt2,i1)
coup2R = cplcFdFdVGR(gt2,i1)
coup3L = cplcFdFdVGL(i2,gt3)
coup3R = cplcFdFdVGR(i2,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_FFV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(4._dp/3._dp)*AmpC 
  End Do
End Do


! {bar[Fd], bar[Fd], VP}
Do i1=1,3
  Do i2=1,3
ML1 = MFd(i1) 
ML2 = MFd(i2) 
ML3 = MVP 
coup1L = cplcFdFdAhL(i1,i2,gt1)
coup1R = cplcFdFdAhR(i1,i2,gt1)
coup2L = cplcFdFdVPL(gt2,i1)
coup2R = cplcFdFdVPR(gt2,i1)
coup3L = cplcFdFdVPL(i2,gt3)
coup3R = cplcFdFdVPR(i2,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_FFV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {bar[Fd], bar[Fd], VZ}
Do i1=1,3
  Do i2=1,3
ML1 = MFd(i1) 
ML2 = MFd(i2) 
ML3 = MVZ 
coup1L = cplcFdFdAhL(i1,i2,gt1)
coup1R = cplcFdFdAhR(i1,i2,gt1)
coup2L = cplcFdFdVZL(gt2,i1)
coup2R = cplcFdFdVZR(gt2,i1)
coup3L = cplcFdFdVZL(i2,gt3)
coup3R = cplcFdFdVZR(i2,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_FFV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {bar[Fu], bar[Fu], Hm}
Do i1=1,3
  Do i2=1,3
    Do i3=1,2
ML1 = MFu(i1) 
ML2 = MFu(i2) 
ML3 = MHm(i3) 
coup1L = cplcFuFuAhL(i1,i2,gt1)
coup1R = cplcFuFuAhR(i1,i2,gt1)
coup2L = cplcFdFuHmL(gt2,i1,i3)
coup2R = cplcFdFuHmR(gt2,i1,i3)
coup3L = cplcFuFdcHmL(i2,gt3,i3)
coup3R = cplcFuFdcHmR(i2,gt3,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_FFS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {bar[Fu], bar[Fu], VWm}
Do i1=1,3
  Do i2=1,3
ML1 = MFu(i1) 
ML2 = MFu(i2) 
ML3 = MVWm 
coup1L = cplcFuFuAhL(i1,i2,gt1)
coup1R = cplcFuFuAhR(i1,i2,gt1)
coup2L = cplcFdFuVWmL(gt2,i1)
coup2R = cplcFdFuVWmR(gt2,i1)
coup3L = cplcFuFdcVWmL(i2,gt3)
coup3R = cplcFuFdcVWmR(i2,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_FFV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {conj[Hm], conj[Hm], Fu}
Do i1=1,2
  Do i2=1,2
    Do i3=1,3
ML1 = MHm(i1) 
ML2 = MHm(i2) 
ML3 = MFu(i3) 
coup1 = cplAhHmcHm(gt1,i2,i1)
coup2L = cplcFdFuHmL(gt2,i3,i1)
coup2R = cplcFdFuHmR(gt2,i3,i1)
coup3L = cplcFuFdcHmL(i3,gt3,i2)
coup3R = cplcFuFdcHmR(i3,gt3,i2)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_SSF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {conj[Hm], conj[VWm], Fu}
Do i1=1,2
    Do i3=1,3
ML1 = MHm(i1) 
ML2 = MVWm 
ML3 = MFu(i3) 
coup1 = cplAhcHmVWm(gt1,i1)
coup2L = cplcFdFuHmL(gt2,i3,i1)
coup2R = cplcFdFuHmR(gt2,i3,i1)
coup3L = cplcFuFdcVWmL(i3,gt3)
coup3R = cplcFuFdcVWmR(i3,gt3)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_SVF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {conj[VWm], conj[Hm], Fu}
  Do i2=1,2
    Do i3=1,3
ML1 = MVWm 
ML2 = MHm(i2) 
ML3 = MFu(i3) 
coup1 = cplAhHmcVWm(gt1,i2)
coup2L = cplcFdFuVWmL(gt2,i3)
coup2R = cplcFdFuVWmR(gt2,i3)
coup3L = cplcFuFdcHmL(i3,gt3,i2)
coup3R = cplcFuFdcHmR(i3,gt3,i2)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_VSF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
    End Do
  End Do
End Do
End Subroutine Amplitude_VERTEX_gumTHDMII_AhTocFdFd


Subroutine Amplitude_IR_VERTEX_gumTHDMII_AhTocFdFd(MAh,MFd,MFu,Mhh,MHm,               & 
& MVG,MVP,MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhAh,              & 
& cplAhAhhh,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,         & 
& cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,    & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHmL,cplcFuFdcHmR,             & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFdFuHmL,cplcFdFuHmR,cplcFdFuVWmL,cplcFdFuVWmR,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MFd(3),MFu(3),Mhh(2),MHm(2),MVG,MVP,MVWm,MVZ,MAh2(2),MFd2(3),MFu2(3),          & 
& Mhh2(2),MHm2(2),MVG2,MVP2,MVWm2,MVZ2

Complex(dp), Intent(in) :: cplAhAhAh(2,2,2),cplAhAhhh(2,2,2),cplcFdFdAhL(3,3,2),cplcFdFdAhR(3,3,2),              & 
& cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),cplAhhhhh(2,2,2),cplAhhhVZ(2,2),cplAhHmcHm(2,2,2),& 
& cplAhHmcVWm(2,2),cplAhcHmVWm(2,2),cplcFdFdhhL(3,3,2),cplcFdFdhhR(3,3,2),               & 
& cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),cplcFdFdVZL(3,3),  & 
& cplcFdFdVZR(3,3),cplcFuFdcHmL(3,3,2),cplcFuFdcHmR(3,3,2),cplcFuFdcVWmL(3,3),           & 
& cplcFuFdcVWmR(3,3),cplcFdFuHmL(3,3,2),cplcFdFuHmR(3,3,2),cplcFdFuVWmL(3,3),            & 
& cplcFdFuVWmR(3,3)

Complex(dp), Intent(out) :: Amp(2,2,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,2
  Do gt2=1,3
    Do gt3=1,3
Amp(:,gt1, gt2, gt3) = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = MAh(gt1) 
Mex2 = MFd(gt2) 
Mex3 = MFd(gt3) 


! {bar[Fd], bar[Fd], VG}
Do i1=1,3
  Do i2=1,3
ML1 = MFd(i1) 
ML2 = MFd(i2) 
ML3 = MVG 
coup1L = cplcFdFdAhL(i1,i2,gt1)
coup1R = cplcFdFdAhR(i1,i2,gt1)
coup2L = cplcFdFdVGL(gt2,i1)
coup2R = cplcFdFdVGR(gt2,i1)
coup3L = cplcFdFdVGL(i2,gt3)
coup3R = cplcFdFdVGR(i2,gt3)
Call Amp_VERTEX_StoFF_Topology1_FFV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(4._dp/3._dp)*AmpC 
  End Do
End Do


! {bar[Fd], bar[Fd], VP}
Do i1=1,3
  Do i2=1,3
ML1 = MFd(i1) 
ML2 = MFd(i2) 
ML3 = MVP 
coup1L = cplcFdFdAhL(i1,i2,gt1)
coup1R = cplcFdFdAhR(i1,i2,gt1)
coup2L = cplcFdFdVPL(gt2,i1)
coup2R = cplcFdFdVPR(gt2,i1)
coup3L = cplcFdFdVPL(i2,gt3)
coup3R = cplcFdFdVPR(i2,gt3)
Call Amp_VERTEX_StoFF_Topology1_FFV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do
    End Do
  End Do
End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_gumTHDMII_AhTocFdFd


Subroutine Amplitude_Tree_gumTHDMII_AhTocFeFe(cplcFeFeAhL,cplcFeFeAhR,MAh,            & 
& MFe,MAh2,MFe2,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MFe(3),MAh2(2),MFe2(3)

Complex(dp), Intent(in) :: cplcFeFeAhL(3,3,2),cplcFeFeAhR(3,3,2)

Complex(dp) :: Amp(2,2,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 

Do gt1=1,2
  Do gt2=1,3
    Do gt3=1,3
! External masses 
Mex1 = MAh(gt1) 
Mex2 = MFe(gt2) 
Mex3 = MFe(gt3) 
! Tree-Level Vertex 
coupT1L = cplcFeFeAhL(gt2,gt3,gt1)
coupT1R = cplcFeFeAhR(gt2,gt3,gt1)
Call TreeAmp_StoFF(Mex1,Mex2,Mex3,coupT1L,coupT1R,AmpC) 
! Colour and symmetry factor 
Amp(:,gt1, gt2, gt3) = AmpC 
    End Do
  End Do
End Do
End Subroutine Amplitude_Tree_gumTHDMII_AhTocFeFe


Subroutine Gamma_Real_gumTHDMII_AhTocFeFe(MLambda,em,gs,cplcFeFeAhL,cplcFeFeAhR,      & 
& MAh,MFe,GammarealPhoton,GammarealGluon)

Implicit None

Complex(dp), Intent(in) :: cplcFeFeAhL(3,3,2),cplcFeFeAhR(3,3,2)

Real(dp), Intent(in) :: MAh(2),MFe(3)

Real(dp), Intent(in) :: MLambda, em, gs 

Real(dp), Intent(out) :: GammarealPhoton(2,3,3), GammarealGluon(2,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 

Real(dp) :: Mloop1, Mloop2, Mloop3 
Complex(dp) :: CoupL, CoupR 
 
Do i1=2,2
  Do i2=1,3
    Do i3=1,3
CoupL = cplcFeFeAhL(i2,i3,i1)
CoupR = cplcFeFeAhR(i2,i3,i1)
Mex1 = MAh(i1)
Mex2 = MFe(i2)
Mex3 = MFe(i3)
If (Abs(Mex1).gt.(Abs(Mex2)+Abs(Mex3))) Then 
 Call hardradiationSFF(Mex1,Mex2,Mex3,MLambda,em,0._dp,0._dp,0._dp,1._dp,-1._dp,1._dp,CoupL,CoupR,Gammarealphoton(i1,i2,i3),kont)
  GammarealGluon(i1,i2,i3) = 0._dp 
Else 
  GammarealGluon(i1,i2,i3) = 0._dp 
  GammarealPhoton(i1,i2,i3) = 0._dp 

End if 
    End Do
  End Do
End Do
End Subroutine Gamma_Real_gumTHDMII_AhTocFeFe


Subroutine Amplitude_WAVE_gumTHDMII_AhTocFeFe(cplcFeFeAhL,cplcFeFeAhR,ctcplcFeFeAhL,  & 
& ctcplcFeFeAhR,MAh,MAh2,MFe,MFe2,ZfAh,ZfEL,ZfER,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MAh2(2),MFe(3),MFe2(3)

Complex(dp), Intent(in) :: cplcFeFeAhL(3,3,2),cplcFeFeAhR(3,3,2)

Complex(dp), Intent(in) :: ctcplcFeFeAhL(3,3,2),ctcplcFeFeAhR(3,3,2)

Complex(dp), Intent(in) :: ZfAh(2,2),ZfEL(3,3),ZfER(3,3)

Complex(dp), Intent(out) :: Amp(2,2,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

Do gt1=1,2
  Do gt2=1,3
    Do gt3=1,3
! External masses 
Mex1 = MAh(gt1) 
Mex2 = MFe(gt2) 
Mex3 = MFe(gt3) 
!----------------------------- 
! Coupling counter term 
!----------------------------- 
ZcoupT1L = ctcplcFeFeAhL(gt2,gt3,gt1) 
ZcoupT1R = ctcplcFeFeAhR(gt2,gt3,gt1) 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
Do i1=1,2
ZcoupT1L = ZcoupT1L + 0.5_dp*ZfAh(i1,gt1)*cplcFeFeAhL(gt2,gt3,i1)
ZcoupT1R = ZcoupT1R + 0.5_dp*ZfAh(i1,gt1)*cplcFeFeAhR(gt2,gt3,i1)
End Do


! External Field 2 
Do i1=1,3
ZcoupT1L = ZcoupT1L + 0.5_dp*ZfER(i1,gt2)*cplcFeFeAhL(i1,gt3,gt1)
ZcoupT1R = ZcoupT1R + 0.5_dp*Conjg(ZfEL(i1,gt2))*cplcFeFeAhR(i1,gt3,gt1)
End Do


! External Field 3 
Do i1=1,3
ZcoupT1L = ZcoupT1L + 0.5_dp*ZfEL(i1,gt3)*cplcFeFeAhL(gt2,i1,gt1)
ZcoupT1R = ZcoupT1R + 0.5_dp*Conjg(ZfER(i1,gt3))*cplcFeFeAhR(gt2,i1,gt1)
End Do


! Getting the amplitude 
Call TreeAmp_StoFF(Mex1,Mex2,Mex3,ZcoupT1L,ZcoupT1R,AmpC) 
Amp(:,gt1, gt2, gt3) = AmpC 
    End Do
  End Do
End Do
End Subroutine Amplitude_WAVE_gumTHDMII_AhTocFeFe


Subroutine Amplitude_VERTEX_gumTHDMII_AhTocFeFe(MAh,MFe,Mhh,MHm,MVP,MVWm,             & 
& MVZ,MAh2,MFe2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcFeFeAhL,               & 
& cplcFeFeAhR,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFeFehhL,        & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFvFecHmL,              & 
& cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFeFvHmL,cplcFeFvHmR,cplcFeFvVWmL,         & 
& cplcFeFvVWmR,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MFe(3),Mhh(2),MHm(2),MVP,MVWm,MVZ,MAh2(2),MFe2(3),Mhh2(2),MHm2(2),             & 
& MVP2,MVWm2,MVZ2

Complex(dp), Intent(in) :: cplAhAhAh(2,2,2),cplAhAhhh(2,2,2),cplcFeFeAhL(3,3,2),cplcFeFeAhR(3,3,2),              & 
& cplAhhhhh(2,2,2),cplAhhhVZ(2,2),cplAhHmcHm(2,2,2),cplAhHmcVWm(2,2),cplAhcHmVWm(2,2),   & 
& cplcFeFehhL(3,3,2),cplcFeFehhR(3,3,2),cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),               & 
& cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),cplcFvFecHmL(3,3,2),cplcFvFecHmR(3,3,2),             & 
& cplcFvFecVWmL(3,3),cplcFvFecVWmR(3,3),cplcFeFvHmL(3,3,2),cplcFeFvHmR(3,3,2),           & 
& cplcFeFvVWmL(3,3),cplcFeFvVWmR(3,3)

Complex(dp), Intent(out) :: Amp(2,2,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,2
  Do gt2=1,3
    Do gt3=1,3
Amp(:,gt1, gt2, gt3) = 0._dp 
! External masses 
Mex1 = MAh(gt1) 
Mex2 = MFe(gt2) 
Mex3 = MFe(gt3) 


! {Ah, Ah, Fe}
Do i1=1,2
  Do i2=1,2
    Do i3=1,3
ML1 = MAh(i1) 
ML2 = MAh(i2) 
ML3 = MFe(i3) 
coup1 = cplAhAhAh(gt1,i1,i2)
coup2L = cplcFeFeAhL(gt2,i3,i1)
coup2R = cplcFeFeAhR(gt2,i3,i1)
coup3L = cplcFeFeAhL(i3,gt3,i2)
coup3R = cplcFeFeAhR(i3,gt3,i2)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_SSF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Ah, hh, Fe}
Do i1=1,2
  Do i2=1,2
    Do i3=1,3
ML1 = MAh(i1) 
ML2 = Mhh(i2) 
ML3 = MFe(i3) 
coup1 = cplAhAhhh(gt1,i1,i2)
coup2L = cplcFeFeAhL(gt2,i3,i1)
coup2R = cplcFeFeAhR(gt2,i3,i1)
coup3L = cplcFeFehhL(i3,gt3,i2)
coup3R = cplcFeFehhR(i3,gt3,i2)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_SSF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {hh, Ah, Fe}
Do i1=1,2
  Do i2=1,2
    Do i3=1,3
ML1 = Mhh(i1) 
ML2 = MAh(i2) 
ML3 = MFe(i3) 
coup1 = cplAhAhhh(gt1,i2,i1)
coup2L = cplcFeFehhL(gt2,i3,i1)
coup2R = cplcFeFehhR(gt2,i3,i1)
coup3L = cplcFeFeAhL(i3,gt3,i2)
coup3R = cplcFeFeAhR(i3,gt3,i2)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_SSF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {hh, hh, Fe}
Do i1=1,2
  Do i2=1,2
    Do i3=1,3
ML1 = Mhh(i1) 
ML2 = Mhh(i2) 
ML3 = MFe(i3) 
coup1 = cplAhhhhh(gt1,i1,i2)
coup2L = cplcFeFehhL(gt2,i3,i1)
coup2R = cplcFeFehhR(gt2,i3,i1)
coup3L = cplcFeFehhL(i3,gt3,i2)
coup3R = cplcFeFehhR(i3,gt3,i2)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_SSF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {hh, VZ, Fe}
Do i1=1,2
    Do i3=1,3
ML1 = Mhh(i1) 
ML2 = MVZ 
ML3 = MFe(i3) 
coup1 = cplAhhhVZ(gt1,i1)
coup2L = cplcFeFehhL(gt2,i3,i1)
coup2R = cplcFeFehhR(gt2,i3,i1)
coup3L = cplcFeFeVZL(i3,gt3)
coup3R = cplcFeFeVZR(i3,gt3)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_SVF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {VZ, hh, Fe}
  Do i2=1,2
    Do i3=1,3
ML1 = MVZ 
ML2 = Mhh(i2) 
ML3 = MFe(i3) 
coup1 = cplAhhhVZ(gt1,i2)
coup2L = cplcFeFeVZL(gt2,i3)
coup2R = cplcFeFeVZR(gt2,i3)
coup3L = cplcFeFehhL(i3,gt3,i2)
coup3R = cplcFeFehhR(i3,gt3,i2)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_VSF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {bar[Fe], bar[Fe], Ah}
Do i1=1,3
  Do i2=1,3
    Do i3=1,2
ML1 = MFe(i1) 
ML2 = MFe(i2) 
ML3 = MAh(i3) 
coup1L = cplcFeFeAhL(i1,i2,gt1)
coup1R = cplcFeFeAhR(i1,i2,gt1)
coup2L = cplcFeFeAhL(gt2,i1,i3)
coup2R = cplcFeFeAhR(gt2,i1,i3)
coup3L = cplcFeFeAhL(i2,gt3,i3)
coup3R = cplcFeFeAhR(i2,gt3,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_FFS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {bar[Fe], bar[Fe], hh}
Do i1=1,3
  Do i2=1,3
    Do i3=1,2
ML1 = MFe(i1) 
ML2 = MFe(i2) 
ML3 = Mhh(i3) 
coup1L = cplcFeFeAhL(i1,i2,gt1)
coup1R = cplcFeFeAhR(i1,i2,gt1)
coup2L = cplcFeFehhL(gt2,i1,i3)
coup2R = cplcFeFehhR(gt2,i1,i3)
coup3L = cplcFeFehhL(i2,gt3,i3)
coup3R = cplcFeFehhR(i2,gt3,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_FFS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {bar[Fe], bar[Fe], VP}
Do i1=1,3
  Do i2=1,3
ML1 = MFe(i1) 
ML2 = MFe(i2) 
ML3 = MVP 
coup1L = cplcFeFeAhL(i1,i2,gt1)
coup1R = cplcFeFeAhR(i1,i2,gt1)
coup2L = cplcFeFeVPL(gt2,i1)
coup2R = cplcFeFeVPR(gt2,i1)
coup3L = cplcFeFeVPL(i2,gt3)
coup3R = cplcFeFeVPR(i2,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_FFV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {bar[Fe], bar[Fe], VZ}
Do i1=1,3
  Do i2=1,3
ML1 = MFe(i1) 
ML2 = MFe(i2) 
ML3 = MVZ 
coup1L = cplcFeFeAhL(i1,i2,gt1)
coup1R = cplcFeFeAhR(i1,i2,gt1)
coup2L = cplcFeFeVZL(gt2,i1)
coup2R = cplcFeFeVZR(gt2,i1)
coup3L = cplcFeFeVZL(i2,gt3)
coup3R = cplcFeFeVZR(i2,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_FFV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {conj[Hm], conj[Hm], Fv}
Do i1=1,2
  Do i2=1,2
    Do i3=1,3
ML1 = MHm(i1) 
ML2 = MHm(i2) 
ML3 = 0._dp 
coup1 = cplAhHmcHm(gt1,i2,i1)
coup2L = cplcFeFvHmL(gt2,i3,i1)
coup2R = cplcFeFvHmR(gt2,i3,i1)
coup3L = cplcFvFecHmL(i3,gt3,i2)
coup3R = cplcFvFecHmR(i3,gt3,i2)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_SSF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {conj[Hm], conj[VWm], Fv}
Do i1=1,2
    Do i3=1,3
ML1 = MHm(i1) 
ML2 = MVWm 
ML3 = 0._dp 
coup1 = cplAhcHmVWm(gt1,i1)
coup2L = cplcFeFvHmL(gt2,i3,i1)
coup2R = cplcFeFvHmR(gt2,i3,i1)
coup3L = cplcFvFecVWmL(i3,gt3)
coup3R = cplcFvFecVWmR(i3,gt3)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_SVF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {conj[VWm], conj[Hm], Fv}
  Do i2=1,2
    Do i3=1,3
ML1 = MVWm 
ML2 = MHm(i2) 
ML3 = 0._dp 
coup1 = cplAhHmcVWm(gt1,i2)
coup2L = cplcFeFvVWmL(gt2,i3)
coup2R = cplcFeFvVWmR(gt2,i3)
coup3L = cplcFvFecHmL(i3,gt3,i2)
coup3R = cplcFvFecHmR(i3,gt3,i2)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_VSF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
    End Do
  End Do
End Do
End Subroutine Amplitude_VERTEX_gumTHDMII_AhTocFeFe


Subroutine Amplitude_IR_VERTEX_gumTHDMII_AhTocFeFe(MAh,MFe,Mhh,MHm,MVP,               & 
& MVWm,MVZ,MAh2,MFe2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcFeFeAhL,          & 
& cplcFeFeAhR,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFeFehhL,        & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFvFecHmL,              & 
& cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFeFvHmL,cplcFeFvHmR,cplcFeFvVWmL,         & 
& cplcFeFvVWmR,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MFe(3),Mhh(2),MHm(2),MVP,MVWm,MVZ,MAh2(2),MFe2(3),Mhh2(2),MHm2(2),             & 
& MVP2,MVWm2,MVZ2

Complex(dp), Intent(in) :: cplAhAhAh(2,2,2),cplAhAhhh(2,2,2),cplcFeFeAhL(3,3,2),cplcFeFeAhR(3,3,2),              & 
& cplAhhhhh(2,2,2),cplAhhhVZ(2,2),cplAhHmcHm(2,2,2),cplAhHmcVWm(2,2),cplAhcHmVWm(2,2),   & 
& cplcFeFehhL(3,3,2),cplcFeFehhR(3,3,2),cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),               & 
& cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),cplcFvFecHmL(3,3,2),cplcFvFecHmR(3,3,2),             & 
& cplcFvFecVWmL(3,3),cplcFvFecVWmR(3,3),cplcFeFvHmL(3,3,2),cplcFeFvHmR(3,3,2),           & 
& cplcFeFvVWmL(3,3),cplcFeFvVWmR(3,3)

Complex(dp), Intent(out) :: Amp(2,2,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,2
  Do gt2=1,3
    Do gt3=1,3
Amp(:,gt1, gt2, gt3) = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = MAh(gt1) 
Mex2 = MFe(gt2) 
Mex3 = MFe(gt3) 


! {bar[Fe], bar[Fe], VP}
Do i1=1,3
  Do i2=1,3
ML1 = MFe(i1) 
ML2 = MFe(i2) 
ML3 = MVP 
coup1L = cplcFeFeAhL(i1,i2,gt1)
coup1R = cplcFeFeAhR(i1,i2,gt1)
coup2L = cplcFeFeVPL(gt2,i1)
coup2R = cplcFeFeVPR(gt2,i1)
coup3L = cplcFeFeVPL(i2,gt3)
coup3R = cplcFeFeVPR(i2,gt3)
Call Amp_VERTEX_StoFF_Topology1_FFV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do
    End Do
  End Do
End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_gumTHDMII_AhTocFeFe


Subroutine Amplitude_Tree_gumTHDMII_AhTocFuFu(cplcFuFuAhL,cplcFuFuAhR,MAh,            & 
& MFu,MAh2,MFu2,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MFu(3),MAh2(2),MFu2(3)

Complex(dp), Intent(in) :: cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2)

Complex(dp) :: Amp(2,2,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 

Do gt1=1,2
  Do gt2=1,3
    Do gt3=1,3
! External masses 
Mex1 = MAh(gt1) 
Mex2 = MFu(gt2) 
Mex3 = MFu(gt3) 
! Tree-Level Vertex 
coupT1L = cplcFuFuAhL(gt2,gt3,gt1)
coupT1R = cplcFuFuAhR(gt2,gt3,gt1)
Call TreeAmp_StoFF(Mex1,Mex2,Mex3,coupT1L,coupT1R,AmpC) 
! Colour and symmetry factor 
Amp(:,gt1, gt2, gt3) = AmpC 
    End Do
  End Do
End Do
End Subroutine Amplitude_Tree_gumTHDMII_AhTocFuFu


Subroutine Gamma_Real_gumTHDMII_AhTocFuFu(MLambda,em,gs,cplcFuFuAhL,cplcFuFuAhR,      & 
& MAh,MFu,GammarealPhoton,GammarealGluon)

Implicit None

Complex(dp), Intent(in) :: cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2)

Real(dp), Intent(in) :: MAh(2),MFu(3)

Real(dp), Intent(in) :: MLambda, em, gs 

Real(dp), Intent(out) :: GammarealPhoton(2,3,3), GammarealGluon(2,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 

Real(dp) :: Mloop1, Mloop2, Mloop3 
Complex(dp) :: CoupL, CoupR 
 
Do i1=2,2
  Do i2=1,3
    Do i3=1,3
CoupL = cplcFuFuAhL(i2,i3,i1)
CoupR = cplcFuFuAhR(i2,i3,i1)
Mex1 = MAh(i1)
Mex2 = MFu(i2)
Mex3 = MFu(i3)
If (Abs(Mex1).gt.(Abs(Mex2)+Abs(Mex3))) Then 
 Call hardradiationSFF(Mex1,Mex2,Mex3,MLambda,em,0._dp,0._dp,0._dp,4._dp/3._dp,-4._dp/3._dp,4._dp/3._dp,CoupL,CoupR,Gammarealphoton(i1,i2,i3),kont)
 Call hardradiationSFF(Mex1,Mex2,Mex3,MLambda,gs,0._dp,0._dp,0._dp,4._dp,-4._dp,4._dp,CoupL,CoupR,Gammarealgluon(i1,i2,i3),kont)
Else 
  GammarealGluon(i1,i2,i3) = 0._dp 
  GammarealPhoton(i1,i2,i3) = 0._dp 

End if 
    End Do
  End Do
End Do
End Subroutine Gamma_Real_gumTHDMII_AhTocFuFu


Subroutine Amplitude_WAVE_gumTHDMII_AhTocFuFu(cplcFuFuAhL,cplcFuFuAhR,ctcplcFuFuAhL,  & 
& ctcplcFuFuAhR,MAh,MAh2,MFu,MFu2,ZfAh,ZfUL,ZfUR,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MAh2(2),MFu(3),MFu2(3)

Complex(dp), Intent(in) :: cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2)

Complex(dp), Intent(in) :: ctcplcFuFuAhL(3,3,2),ctcplcFuFuAhR(3,3,2)

Complex(dp), Intent(in) :: ZfAh(2,2),ZfUL(3,3),ZfUR(3,3)

Complex(dp), Intent(out) :: Amp(2,2,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

Do gt1=1,2
  Do gt2=1,3
    Do gt3=1,3
! External masses 
Mex1 = MAh(gt1) 
Mex2 = MFu(gt2) 
Mex3 = MFu(gt3) 
!----------------------------- 
! Coupling counter term 
!----------------------------- 
ZcoupT1L = ctcplcFuFuAhL(gt2,gt3,gt1) 
ZcoupT1R = ctcplcFuFuAhR(gt2,gt3,gt1) 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
Do i1=1,2
ZcoupT1L = ZcoupT1L + 0.5_dp*ZfAh(i1,gt1)*cplcFuFuAhL(gt2,gt3,i1)
ZcoupT1R = ZcoupT1R + 0.5_dp*ZfAh(i1,gt1)*cplcFuFuAhR(gt2,gt3,i1)
End Do


! External Field 2 
Do i1=1,3
ZcoupT1L = ZcoupT1L + 0.5_dp*ZfUR(i1,gt2)*cplcFuFuAhL(i1,gt3,gt1)
ZcoupT1R = ZcoupT1R + 0.5_dp*Conjg(ZfUL(i1,gt2))*cplcFuFuAhR(i1,gt3,gt1)
End Do


! External Field 3 
Do i1=1,3
ZcoupT1L = ZcoupT1L + 0.5_dp*ZfUL(i1,gt3)*cplcFuFuAhL(gt2,i1,gt1)
ZcoupT1R = ZcoupT1R + 0.5_dp*Conjg(ZfUR(i1,gt3))*cplcFuFuAhR(gt2,i1,gt1)
End Do


! Getting the amplitude 
Call TreeAmp_StoFF(Mex1,Mex2,Mex3,ZcoupT1L,ZcoupT1R,AmpC) 
Amp(:,gt1, gt2, gt3) = AmpC 
    End Do
  End Do
End Do
End Subroutine Amplitude_WAVE_gumTHDMII_AhTocFuFu


Subroutine Amplitude_VERTEX_gumTHDMII_AhTocFuFu(MAh,MFd,MFu,Mhh,MHm,MVG,              & 
& MVP,MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,        & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,        & 
& cplAhHmcVWm,cplAhcHmVWm,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,         & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,cplcFuFuVGL,cplcFuFuVGR,               & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MFd(3),MFu(3),Mhh(2),MHm(2),MVG,MVP,MVWm,MVZ,MAh2(2),MFd2(3),MFu2(3),          & 
& Mhh2(2),MHm2(2),MVG2,MVP2,MVWm2,MVZ2

Complex(dp), Intent(in) :: cplAhAhAh(2,2,2),cplAhAhhh(2,2,2),cplcFdFdAhL(3,3,2),cplcFdFdAhR(3,3,2),              & 
& cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),cplAhhhhh(2,2,2),cplAhhhVZ(2,2),cplAhHmcHm(2,2,2),& 
& cplAhHmcVWm(2,2),cplAhcHmVWm(2,2),cplcFuFdcHmL(3,3,2),cplcFuFdcHmR(3,3,2),             & 
& cplcFuFdcVWmL(3,3),cplcFuFdcVWmR(3,3),cplcFuFuhhL(3,3,2),cplcFuFuhhR(3,3,2),           & 
& cplcFdFuHmL(3,3,2),cplcFdFuHmR(3,3,2),cplcFuFuVGL(3,3),cplcFuFuVGR(3,3),               & 
& cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcFdFuVWmL(3,3),cplcFdFuVWmR(3,3),cplcFuFuVZL(3,3),& 
& cplcFuFuVZR(3,3)

Complex(dp), Intent(out) :: Amp(2,2,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,2
  Do gt2=1,3
    Do gt3=1,3
Amp(:,gt1, gt2, gt3) = 0._dp 
! External masses 
Mex1 = MAh(gt1) 
Mex2 = MFu(gt2) 
Mex3 = MFu(gt3) 


! {Ah, Ah, Fu}
Do i1=1,2
  Do i2=1,2
    Do i3=1,3
ML1 = MAh(i1) 
ML2 = MAh(i2) 
ML3 = MFu(i3) 
coup1 = cplAhAhAh(gt1,i1,i2)
coup2L = cplcFuFuAhL(gt2,i3,i1)
coup2R = cplcFuFuAhR(gt2,i3,i1)
coup3L = cplcFuFuAhL(i3,gt3,i2)
coup3R = cplcFuFuAhR(i3,gt3,i2)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_SSF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Ah, hh, Fu}
Do i1=1,2
  Do i2=1,2
    Do i3=1,3
ML1 = MAh(i1) 
ML2 = Mhh(i2) 
ML3 = MFu(i3) 
coup1 = cplAhAhhh(gt1,i1,i2)
coup2L = cplcFuFuAhL(gt2,i3,i1)
coup2R = cplcFuFuAhR(gt2,i3,i1)
coup3L = cplcFuFuhhL(i3,gt3,i2)
coup3R = cplcFuFuhhR(i3,gt3,i2)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_SSF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {hh, Ah, Fu}
Do i1=1,2
  Do i2=1,2
    Do i3=1,3
ML1 = Mhh(i1) 
ML2 = MAh(i2) 
ML3 = MFu(i3) 
coup1 = cplAhAhhh(gt1,i2,i1)
coup2L = cplcFuFuhhL(gt2,i3,i1)
coup2R = cplcFuFuhhR(gt2,i3,i1)
coup3L = cplcFuFuAhL(i3,gt3,i2)
coup3R = cplcFuFuAhR(i3,gt3,i2)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_SSF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {hh, hh, Fu}
Do i1=1,2
  Do i2=1,2
    Do i3=1,3
ML1 = Mhh(i1) 
ML2 = Mhh(i2) 
ML3 = MFu(i3) 
coup1 = cplAhhhhh(gt1,i1,i2)
coup2L = cplcFuFuhhL(gt2,i3,i1)
coup2R = cplcFuFuhhR(gt2,i3,i1)
coup3L = cplcFuFuhhL(i3,gt3,i2)
coup3R = cplcFuFuhhR(i3,gt3,i2)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_SSF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {hh, VZ, Fu}
Do i1=1,2
    Do i3=1,3
ML1 = Mhh(i1) 
ML2 = MVZ 
ML3 = MFu(i3) 
coup1 = cplAhhhVZ(gt1,i1)
coup2L = cplcFuFuhhL(gt2,i3,i1)
coup2R = cplcFuFuhhR(gt2,i3,i1)
coup3L = cplcFuFuVZL(i3,gt3)
coup3R = cplcFuFuVZR(i3,gt3)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_SVF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hm, Hm, Fd}
Do i1=1,2
  Do i2=1,2
    Do i3=1,3
ML1 = MHm(i1) 
ML2 = MHm(i2) 
ML3 = MFd(i3) 
coup1 = cplAhHmcHm(gt1,i1,i2)
coup2L = cplcFuFdcHmL(gt2,i3,i1)
coup2R = cplcFuFdcHmR(gt2,i3,i1)
coup3L = cplcFdFuHmL(i3,gt3,i2)
coup3R = cplcFdFuHmR(i3,gt3,i2)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_SSF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Hm, VWm, Fd}
Do i1=1,2
    Do i3=1,3
ML1 = MHm(i1) 
ML2 = MVWm 
ML3 = MFd(i3) 
coup1 = cplAhHmcVWm(gt1,i1)
coup2L = cplcFuFdcHmL(gt2,i3,i1)
coup2R = cplcFuFdcHmR(gt2,i3,i1)
coup3L = cplcFdFuVWmL(i3,gt3)
coup3R = cplcFdFuVWmR(i3,gt3)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_SVF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {VWm, Hm, Fd}
  Do i2=1,2
    Do i3=1,3
ML1 = MVWm 
ML2 = MHm(i2) 
ML3 = MFd(i3) 
coup1 = cplAhcHmVWm(gt1,i2)
coup2L = cplcFuFdcVWmL(gt2,i3)
coup2R = cplcFuFdcVWmR(gt2,i3)
coup3L = cplcFdFuHmL(i3,gt3,i2)
coup3R = cplcFdFuHmR(i3,gt3,i2)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_VSF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VZ, hh, Fu}
  Do i2=1,2
    Do i3=1,3
ML1 = MVZ 
ML2 = Mhh(i2) 
ML3 = MFu(i3) 
coup1 = cplAhhhVZ(gt1,i2)
coup2L = cplcFuFuVZL(gt2,i3)
coup2R = cplcFuFuVZR(gt2,i3)
coup3L = cplcFuFuhhL(i3,gt3,i2)
coup3R = cplcFuFuhhR(i3,gt3,i2)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_VSF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {bar[Fd], bar[Fd], conj[Hm]}
Do i1=1,3
  Do i2=1,3
    Do i3=1,2
ML1 = MFd(i1) 
ML2 = MFd(i2) 
ML3 = MHm(i3) 
coup1L = cplcFdFdAhL(i1,i2,gt1)
coup1R = cplcFdFdAhR(i1,i2,gt1)
coup2L = cplcFuFdcHmL(gt2,i1,i3)
coup2R = cplcFuFdcHmR(gt2,i1,i3)
coup3L = cplcFdFuHmL(i2,gt3,i3)
coup3R = cplcFdFuHmR(i2,gt3,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_FFS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {bar[Fd], bar[Fd], conj[VWm]}
Do i1=1,3
  Do i2=1,3
ML1 = MFd(i1) 
ML2 = MFd(i2) 
ML3 = MVWm 
coup1L = cplcFdFdAhL(i1,i2,gt1)
coup1R = cplcFdFdAhR(i1,i2,gt1)
coup2L = cplcFuFdcVWmL(gt2,i1)
coup2R = cplcFuFdcVWmR(gt2,i1)
coup3L = cplcFdFuVWmL(i2,gt3)
coup3R = cplcFdFuVWmR(i2,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_FFV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {bar[Fu], bar[Fu], Ah}
Do i1=1,3
  Do i2=1,3
    Do i3=1,2
ML1 = MFu(i1) 
ML2 = MFu(i2) 
ML3 = MAh(i3) 
coup1L = cplcFuFuAhL(i1,i2,gt1)
coup1R = cplcFuFuAhR(i1,i2,gt1)
coup2L = cplcFuFuAhL(gt2,i1,i3)
coup2R = cplcFuFuAhR(gt2,i1,i3)
coup3L = cplcFuFuAhL(i2,gt3,i3)
coup3R = cplcFuFuAhR(i2,gt3,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_FFS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {bar[Fu], bar[Fu], hh}
Do i1=1,3
  Do i2=1,3
    Do i3=1,2
ML1 = MFu(i1) 
ML2 = MFu(i2) 
ML3 = Mhh(i3) 
coup1L = cplcFuFuAhL(i1,i2,gt1)
coup1R = cplcFuFuAhR(i1,i2,gt1)
coup2L = cplcFuFuhhL(gt2,i1,i3)
coup2R = cplcFuFuhhR(gt2,i1,i3)
coup3L = cplcFuFuhhL(i2,gt3,i3)
coup3R = cplcFuFuhhR(i2,gt3,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_FFS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {bar[Fu], bar[Fu], VG}
Do i1=1,3
  Do i2=1,3
ML1 = MFu(i1) 
ML2 = MFu(i2) 
ML3 = MVG 
coup1L = cplcFuFuAhL(i1,i2,gt1)
coup1R = cplcFuFuAhR(i1,i2,gt1)
coup2L = cplcFuFuVGL(gt2,i1)
coup2R = cplcFuFuVGR(gt2,i1)
coup3L = cplcFuFuVGL(i2,gt3)
coup3R = cplcFuFuVGR(i2,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_FFV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(4._dp/3._dp)*AmpC 
  End Do
End Do


! {bar[Fu], bar[Fu], VP}
Do i1=1,3
  Do i2=1,3
ML1 = MFu(i1) 
ML2 = MFu(i2) 
ML3 = MVP 
coup1L = cplcFuFuAhL(i1,i2,gt1)
coup1R = cplcFuFuAhR(i1,i2,gt1)
coup2L = cplcFuFuVPL(gt2,i1)
coup2R = cplcFuFuVPR(gt2,i1)
coup3L = cplcFuFuVPL(i2,gt3)
coup3R = cplcFuFuVPR(i2,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_FFV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {bar[Fu], bar[Fu], VZ}
Do i1=1,3
  Do i2=1,3
ML1 = MFu(i1) 
ML2 = MFu(i2) 
ML3 = MVZ 
coup1L = cplcFuFuAhL(i1,i2,gt1)
coup1R = cplcFuFuAhR(i1,i2,gt1)
coup2L = cplcFuFuVZL(gt2,i1)
coup2R = cplcFuFuVZR(gt2,i1)
coup3L = cplcFuFuVZL(i2,gt3)
coup3R = cplcFuFuVZR(i2,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_FFV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do
    End Do
  End Do
End Do
End Subroutine Amplitude_VERTEX_gumTHDMII_AhTocFuFu


Subroutine Amplitude_IR_VERTEX_gumTHDMII_AhTocFuFu(MAh,MFd,MFu,Mhh,MHm,               & 
& MVG,MVP,MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhAh,              & 
& cplAhAhhh,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,         & 
& cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,            & 
& cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,cplcFuFuVGL,             & 
& cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,             & 
& cplcFuFuVZR,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MFd(3),MFu(3),Mhh(2),MHm(2),MVG,MVP,MVWm,MVZ,MAh2(2),MFd2(3),MFu2(3),          & 
& Mhh2(2),MHm2(2),MVG2,MVP2,MVWm2,MVZ2

Complex(dp), Intent(in) :: cplAhAhAh(2,2,2),cplAhAhhh(2,2,2),cplcFdFdAhL(3,3,2),cplcFdFdAhR(3,3,2),              & 
& cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),cplAhhhhh(2,2,2),cplAhhhVZ(2,2),cplAhHmcHm(2,2,2),& 
& cplAhHmcVWm(2,2),cplAhcHmVWm(2,2),cplcFuFdcHmL(3,3,2),cplcFuFdcHmR(3,3,2),             & 
& cplcFuFdcVWmL(3,3),cplcFuFdcVWmR(3,3),cplcFuFuhhL(3,3,2),cplcFuFuhhR(3,3,2),           & 
& cplcFdFuHmL(3,3,2),cplcFdFuHmR(3,3,2),cplcFuFuVGL(3,3),cplcFuFuVGR(3,3),               & 
& cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcFdFuVWmL(3,3),cplcFdFuVWmR(3,3),cplcFuFuVZL(3,3),& 
& cplcFuFuVZR(3,3)

Complex(dp), Intent(out) :: Amp(2,2,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,2
  Do gt2=1,3
    Do gt3=1,3
Amp(:,gt1, gt2, gt3) = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = MAh(gt1) 
Mex2 = MFu(gt2) 
Mex3 = MFu(gt3) 


! {bar[Fu], bar[Fu], VG}
Do i1=1,3
  Do i2=1,3
ML1 = MFu(i1) 
ML2 = MFu(i2) 
ML3 = MVG 
coup1L = cplcFuFuAhL(i1,i2,gt1)
coup1R = cplcFuFuAhR(i1,i2,gt1)
coup2L = cplcFuFuVGL(gt2,i1)
coup2R = cplcFuFuVGR(gt2,i1)
coup3L = cplcFuFuVGL(i2,gt3)
coup3R = cplcFuFuVGR(i2,gt3)
Call Amp_VERTEX_StoFF_Topology1_FFV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(4._dp/3._dp)*AmpC 
  End Do
End Do


! {bar[Fu], bar[Fu], VP}
Do i1=1,3
  Do i2=1,3
ML1 = MFu(i1) 
ML2 = MFu(i2) 
ML3 = MVP 
coup1L = cplcFuFuAhL(i1,i2,gt1)
coup1R = cplcFuFuAhR(i1,i2,gt1)
coup2L = cplcFuFuVPL(gt2,i1)
coup2R = cplcFuFuVPR(gt2,i1)
coup3L = cplcFuFuVPL(i2,gt3)
coup3R = cplcFuFuVPR(i2,gt3)
Call Amp_VERTEX_StoFF_Topology1_FFV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do
    End Do
  End Do
End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_gumTHDMII_AhTocFuFu


Subroutine Amplitude_Tree_gumTHDMII_AhTohhhh(cplAhhhhh,MAh,Mhh,MAh2,Mhh2,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),Mhh(2),MAh2(2),Mhh2(2)

Complex(dp), Intent(in) :: cplAhhhhh(2,2,2)

Complex(dp) :: Amp(2,2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 

Do gt1=1,2
  Do gt2=1,2
    Do gt3=1,2
! External masses 
Mex1 = MAh(gt1) 
Mex2 = Mhh(gt2) 
Mex3 = Mhh(gt3) 
! Tree-Level Vertex 
coupT1 = cplAhhhhh(gt1,gt2,gt3)
Call TreeAmp_StoSS(Mex1,Mex2,Mex3,coupT1,AmpC) 
! Colour and symmetry factor 
Amp(gt1, gt2, gt3) = AmpC 
    End Do
  End Do
End Do
End Subroutine Amplitude_Tree_gumTHDMII_AhTohhhh


Subroutine Gamma_Real_gumTHDMII_AhTohhhh(MLambda,em,gs,cplAhhhhh,MAh,Mhh,             & 
& GammarealPhoton,GammarealGluon)

Implicit None

Complex(dp), Intent(in) :: cplAhhhhh(2,2,2)

Real(dp), Intent(in) :: MAh(2),Mhh(2)

Real(dp), Intent(in) :: MLambda, em, gs 

Real(dp), Intent(out) :: GammarealPhoton(2,2,2), GammarealGluon(2,2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 

Real(dp) :: Mloop1, Mloop2, Mloop3 
Complex(dp) :: Coup 
 
Do i1=2,2
  Do i2=1,2
    Do i3=1,2
Coup = cplAhhhhh(i1,i2,i3)
Mex1 = MAh(i1)
Mex2 = Mhh(i2)
Mex3 = Mhh(i3)
If (Abs(Mex1).gt.(Abs(Mex2)+Abs(Mex3))) Then 
 Gammarealphoton(i1,i2,i3) = 0._dp 
  GammarealGluon(i1,i2,i3) = 0._dp 
Else 
  GammarealGluon(i1,i2,i3) = 0._dp 
  GammarealPhoton(i1,i2,i3) = 0._dp 

End if 
    End Do
  End Do
End Do
End Subroutine Gamma_Real_gumTHDMII_AhTohhhh


Subroutine Amplitude_WAVE_gumTHDMII_AhTohhhh(cplAhhhhh,ctcplAhhhhh,MAh,               & 
& MAh2,Mhh,Mhh2,ZfAh,Zfhh,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MAh2(2),Mhh(2),Mhh2(2)

Complex(dp), Intent(in) :: cplAhhhhh(2,2,2)

Complex(dp), Intent(in) :: ctcplAhhhhh(2,2,2)

Complex(dp), Intent(in) :: ZfAh(2,2),Zfhh(2,2)

Complex(dp), Intent(out) :: Amp(2,2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

Do gt1=1,2
  Do gt2=1,2
    Do gt3=1,2
! External masses 
Mex1 = MAh(gt1) 
Mex2 = Mhh(gt2) 
Mex3 = Mhh(gt3) 
!----------------------------- 
! Coupling counter term 
!----------------------------- 
ZcoupT1 = ctcplAhhhhh(gt1,gt2,gt3) 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
Do i1=1,2
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfAh(i1,gt1)*cplAhhhhh(i1,gt2,gt3)
End Do


! External Field 2 
Do i1=1,2
ZcoupT1 = ZcoupT1 + 0.5_dp*Zfhh(i1,gt2)*cplAhhhhh(gt1,i1,gt3)
End Do


! External Field 3 
Do i1=1,2
ZcoupT1 = ZcoupT1 + 0.5_dp*Zfhh(i1,gt3)*cplAhhhhh(gt1,gt2,i1)
End Do


! Getting the amplitude 
Call TreeAmp_StoSS(Mex1,Mex2,Mex3,ZcoupT1,AmpC) 
Amp(gt1, gt2, gt3) = AmpC 
    End Do
  End Do
End Do
End Subroutine Amplitude_WAVE_gumTHDMII_AhTohhhh


Subroutine Amplitude_VERTEX_gumTHDMII_AhTohhhh(MAh,MFd,MFe,MFu,Mhh,MHm,               & 
& MVWm,MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,     & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,     & 
& cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplcgWmgWmhh,              & 
& cplcgWpCgWpChh,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,              & 
& cplAhAhAhhh1,cplAhAhhhhh1,cplAhhhhhhh1,cplAhhhHmcHm1,cplhhhhhhhh1,cplhhhhHmcHm1,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MFd(3),MFe(3),MFu(3),Mhh(2),MHm(2),MVWm,MVZ,MAh2(2),MFd2(3),MFe2(3),           & 
& MFu2(3),Mhh2(2),MHm2(2),MVWm2,MVZ2

Complex(dp), Intent(in) :: cplAhAhAh(2,2,2),cplAhAhhh(2,2,2),cplcFdFdAhL(3,3,2),cplcFdFdAhR(3,3,2),              & 
& cplcFeFeAhL(3,3,2),cplcFeFeAhR(3,3,2),cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),           & 
& cplcgWmgWmAh(2),cplcgWpCgWpCAh(2),cplAhhhhh(2,2,2),cplAhhhVZ(2,2),cplAhHmcHm(2,2,2),   & 
& cplAhHmcVWm(2,2),cplAhcHmVWm(2,2),cplcFdFdhhL(3,3,2),cplcFdFdhhR(3,3,2),               & 
& cplcFeFehhL(3,3,2),cplcFeFehhR(3,3,2),cplcFuFuhhL(3,3,2),cplcFuFuhhR(3,3,2),           & 
& cplcgWmgWmhh(2),cplcgWpCgWpChh(2),cplhhhhhh(2,2,2),cplhhHmcHm(2,2,2),cplhhHmcVWm(2,2), & 
& cplhhcHmVWm(2,2),cplhhcVWmVWm(2),cplAhAhAhhh1(2,2,2,2),cplAhAhhhhh1(2,2,2,2),          & 
& cplAhhhhhhh1(2,2,2,2),cplAhhhHmcHm1(2,2,2,2),cplhhhhhhhh1(2,2,2,2),cplhhhhHmcHm1(2,2,2,2)

Complex(dp), Intent(out) :: Amp(2,2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,2
  Do gt2=1,2
    Do gt3=1,2
Amp(gt1, gt2, gt3) = 0._dp 
! External masses 
Mex1 = MAh(gt1) 
Mex2 = Mhh(gt2) 
Mex3 = Mhh(gt3) 


! {Ah, Ah, Ah}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MAh(i1) 
ML2 = MAh(i2) 
ML3 = MAh(i3) 
coup1 = cplAhAhAh(gt1,i1,i2)
coup2 = cplAhAhhh(i1,i3,gt2)
coup3 = cplAhAhhh(i3,i2,gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Ah, hh, Ah}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MAh(i1) 
ML2 = Mhh(i2) 
ML3 = MAh(i3) 
coup1 = cplAhAhhh(gt1,i1,i2)
coup2 = cplAhAhhh(i1,i3,gt2)
coup3 = cplAhhhhh(i3,gt3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Ah, Ah, hh}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MAh(i1) 
ML2 = MAh(i2) 
ML3 = Mhh(i3) 
coup1 = cplAhAhAh(gt1,i1,i2)
coup2 = cplAhhhhh(i1,gt2,i3)
coup3 = cplAhhhhh(i2,gt3,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Ah, hh, hh}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MAh(i1) 
ML2 = Mhh(i2) 
ML3 = Mhh(i3) 
coup1 = cplAhAhhh(gt1,i1,i2)
coup2 = cplAhhhhh(i1,gt2,i3)
coup3 = cplhhhhhh(gt3,i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Ah, Ah, VZ}
Do i1=1,2
  Do i2=1,2
ML1 = MAh(i1) 
ML2 = MAh(i2) 
ML3 = MVZ 
coup1 = cplAhAhAh(gt1,i1,i2)
coup2 = cplAhhhVZ(i1,gt2)
coup3 = -cplAhhhVZ(i2,gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Fd, Fd, Fd}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFd(i1) 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFdFdAhL(i2,i1,gt1)
coup1R = cplcFdFdAhR(i2,i1,gt1)
coup2L = cplcFdFdhhL(i1,i3,gt2)
coup2R = cplcFdFdhhR(i1,i3,gt2)
coup3L = cplcFdFdhhL(i3,i2,gt3)
coup3R = cplcFdFdhhR(i3,i2,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(6)*AmpC 
    End Do
  End Do
End Do


! {Fe, Fe, Fe}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFe(i1) 
ML2 = MFe(i2) 
ML3 = MFe(i3) 
coup1L = cplcFeFeAhL(i2,i1,gt1)
coup1R = cplcFeFeAhR(i2,i1,gt1)
coup2L = cplcFeFehhL(i1,i3,gt2)
coup2R = cplcFeFehhR(i1,i3,gt2)
coup3L = cplcFeFehhL(i3,i2,gt3)
coup3R = cplcFeFehhR(i3,i2,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(2)*AmpC 
    End Do
  End Do
End Do


! {Fu, Fu, Fu}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFu(i1) 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = cplcFuFuAhL(i2,i1,gt1)
coup1R = cplcFuFuAhR(i2,i1,gt1)
coup2L = cplcFuFuhhL(i1,i3,gt2)
coup2R = cplcFuFuhhR(i1,i3,gt2)
coup3L = cplcFuFuhhL(i3,i2,gt3)
coup3R = cplcFuFuhhR(i3,i2,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(6)*AmpC 
    End Do
  End Do
End Do


! {gWm, gWm, gWm}
ML1 = MVWm 
ML2 = MVWm 
ML3 = MVWm 
coup1 = cplcgWmgWmAh(gt1)
coup2 = cplcgWmgWmhh(gt2)
coup3 = cplcgWmgWmhh(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(2)*AmpC 


! {gWmC, gWmC, gWmC}
ML1 = MVWm 
ML2 = MVWm 
ML3 = MVWm 
coup1 = cplcgWpCgWpCAh(gt1)
coup2 = cplcgWpCgWpChh(gt2)
coup3 = cplcgWpCgWpChh(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(2)*AmpC 


! {hh, Ah, Ah}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = Mhh(i1) 
ML2 = MAh(i2) 
ML3 = MAh(i3) 
coup1 = cplAhAhhh(gt1,i2,i1)
coup2 = cplAhhhhh(i3,gt2,i1)
coup3 = cplAhAhhh(i3,i2,gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {hh, hh, Ah}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = Mhh(i1) 
ML2 = Mhh(i2) 
ML3 = MAh(i3) 
coup1 = cplAhhhhh(gt1,i1,i2)
coup2 = cplAhhhhh(i3,gt2,i1)
coup3 = cplAhhhhh(i3,gt3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {hh, VZ, Ah}
Do i1=1,2
    Do i3=1,2
ML1 = Mhh(i1) 
ML2 = MVZ 
ML3 = MAh(i3) 
coup1 = -cplAhhhVZ(gt1,i1)
coup2 = cplAhhhhh(i3,gt2,i1)
coup3 = -cplAhhhVZ(i3,gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {hh, Ah, hh}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = Mhh(i1) 
ML2 = MAh(i2) 
ML3 = Mhh(i3) 
coup1 = cplAhAhhh(gt1,i2,i1)
coup2 = cplhhhhhh(gt2,i1,i3)
coup3 = cplAhhhhh(i2,gt3,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {hh, hh, hh}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = Mhh(i1) 
ML2 = Mhh(i2) 
ML3 = Mhh(i3) 
coup1 = cplAhhhhh(gt1,i1,i2)
coup2 = cplhhhhhh(gt2,i1,i3)
coup3 = cplhhhhhh(gt3,i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Hm, Hm, Hm}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
ML3 = MHm(i3) 
coup1 = cplAhHmcHm(gt1,i1,i2)
coup2 = cplhhHmcHm(gt2,i3,i1)
coup3 = cplhhHmcHm(gt3,i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(2)*AmpC 
    End Do
  End Do
End Do


! {Hm, VWm, Hm}
Do i1=1,2
    Do i3=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
ML3 = MHm(i3) 
coup1 = -cplAhHmcVWm(gt1,i1)
coup2 = cplhhHmcHm(gt2,i3,i1)
coup3 = cplhhcHmVWm(gt3,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hm, Hm, VWm}
Do i1=1,2
  Do i2=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
ML3 = MVWm 
coup1 = cplAhHmcHm(gt1,i1,i2)
coup2 = -cplhhcHmVWm(gt2,i1)
coup3 = cplhhHmcVWm(gt3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Hm, VWm, VWm}
Do i1=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
ML3 = MVWm 
coup1 = -cplAhHmcVWm(gt1,i1)
coup2 = -cplhhcHmVWm(gt2,i1)
coup3 = cplhhcVWmVWm(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
End Do


! {VWm, Hm, Hm}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
ML3 = MHm(i3) 
coup1 = -cplAhcHmVWm(gt1,i2)
coup2 = -cplhhHmcVWm(gt2,i3)
coup3 = cplhhHmcHm(gt3,i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VWm, Hm, VWm}
  Do i2=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
ML3 = MVWm 
coup1 = -cplAhcHmVWm(gt1,i2)
coup2 = cplhhcVWmVWm(gt2)
coup3 = cplhhHmcVWm(gt3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do


! {VZ, hh, Ah}
  Do i2=1,2
    Do i3=1,2
ML1 = MVZ 
ML2 = Mhh(i2) 
ML3 = MAh(i3) 
coup1 = -cplAhhhVZ(gt1,i2)
coup2 = cplAhhhVZ(i3,gt2)
coup3 = cplAhhhhh(i3,gt3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {conj[Hm], conj[VWm], conj[Hm]}
Do i1=1,2
    Do i3=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
ML3 = MHm(i3) 
coup1 = -cplAhcHmVWm(gt1,i1)
coup2 = cplhhHmcHm(gt2,i1,i3)
coup3 = cplhhHmcVWm(gt3,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {conj[Hm], conj[Hm], conj[VWm]}
Do i1=1,2
  Do i2=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
ML3 = MVWm 
coup1 = cplAhHmcHm(gt1,i2,i1)
coup2 = -cplhhHmcVWm(gt2,i1)
coup3 = cplhhcHmVWm(gt3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {conj[Hm], conj[VWm], conj[VWm]}
Do i1=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
ML3 = MVWm 
coup1 = -cplAhcHmVWm(gt1,i1)
coup2 = -cplhhHmcVWm(gt2,i1)
coup3 = cplhhcVWmVWm(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
End Do


! {conj[VWm], conj[Hm], conj[Hm]}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
ML3 = MHm(i3) 
coup1 = -cplAhHmcVWm(gt1,i2)
coup2 = -cplhhcHmVWm(gt2,i3)
coup3 = cplhhHmcHm(gt3,i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {conj[VWm], conj[Hm], conj[VWm]}
  Do i2=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
ML3 = MVWm 
coup1 = -cplAhHmcVWm(gt1,i2)
coup2 = cplhhcVWmVWm(gt2)
coup3 = cplhhcHmVWm(gt3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do


! {Ah, Ah}
Do i1=1,2
  Do i2=1,2
ML1 = MAh(i1) 
ML2 = MAh(i2) 
coup1 = cplAhAhAh(gt1,i1,i2)
coup2 = cplAhAhhhhh1(i1,i2,gt2,gt3)
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1._dp/2._dp)*AmpC 
  End Do
End Do


! {Ah, hh}
Do i1=1,2
  Do i2=1,2
ML1 = MAh(i1) 
ML2 = Mhh(i2) 
coup1 = cplAhAhhh(gt1,i1,i2)
coup2 = cplAhhhhhhh1(i1,gt2,gt3,i2)
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {hh, hh}
Do i1=1,2
  Do i2=1,2
ML1 = Mhh(i1) 
ML2 = Mhh(i2) 
coup1 = cplAhhhhh(gt1,i1,i2)
coup2 = cplhhhhhhhh1(gt2,gt3,i1,i2)
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1._dp/2._dp)*AmpC 
  End Do
End Do


! {Hm, Hm}
Do i1=1,2
  Do i2=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
coup1 = cplAhHmcHm(gt1,i1,i2)
coup2 = cplhhhhHmcHm1(gt2,gt3,i2,i1)
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Ah, Ah}
Do i1=1,2
  Do i2=1,2
ML1 = MAh(i1) 
ML2 = MAh(i2) 
coup1 = cplAhAhAhhh1(gt1,i1,i2,gt3)
coup2 = cplAhAhhh(i1,i2,gt2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1._dp/2._dp)*AmpC 

  End Do
End Do


! {Ah, hh}
Do i1=1,2
  Do i2=1,2
ML1 = MAh(i1) 
ML2 = Mhh(i2) 
coup1 = cplAhAhhhhh1(gt1,i1,gt3,i2)
coup2 = cplAhhhhh(i1,gt2,i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 

  End Do
End Do


! {hh, hh}
Do i1=1,2
  Do i2=1,2
ML1 = Mhh(i1) 
ML2 = Mhh(i2) 
coup1 = cplAhhhhhhh1(gt1,gt3,i1,i2)
coup2 = cplhhhhhh(gt2,i1,i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1._dp/2._dp)*AmpC 

  End Do
End Do


! {Hm, Hm}
Do i1=1,2
  Do i2=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
coup1 = cplAhhhHmcHm1(gt1,gt3,i1,i2)
coup2 = cplhhHmcHm(gt2,i2,i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 

  End Do
End Do


! {Ah, Ah}
Do i1=1,2
  Do i2=1,2
ML1 = MAh(i1) 
ML2 = MAh(i2) 
coup1 = cplAhAhAhhh1(gt1,i1,i2,gt2)
coup2 = cplAhAhhh(i1,i2,gt3)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1._dp/2._dp)*AmpC 

  End Do
End Do


! {Ah, hh}
Do i1=1,2
  Do i2=1,2
ML1 = MAh(i1) 
ML2 = Mhh(i2) 
coup1 = cplAhAhhhhh1(gt1,i1,gt2,i2)
coup2 = cplAhhhhh(i1,gt3,i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 

  End Do
End Do


! {hh, hh}
Do i1=1,2
  Do i2=1,2
ML1 = Mhh(i1) 
ML2 = Mhh(i2) 
coup1 = cplAhhhhhhh1(gt1,gt2,i1,i2)
coup2 = cplhhhhhh(gt3,i1,i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1._dp/2._dp)*AmpC 

  End Do
End Do


! {Hm, Hm}
Do i1=1,2
  Do i2=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
coup1 = cplAhhhHmcHm1(gt1,gt2,i1,i2)
coup2 = cplhhHmcHm(gt3,i2,i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 

  End Do
End Do
    End Do
  End Do
End Do
End Subroutine Amplitude_VERTEX_gumTHDMII_AhTohhhh


Subroutine Amplitude_IR_VERTEX_gumTHDMII_AhTohhhh(MAh,MFd,MFe,MFu,Mhh,MHm,            & 
& MVWm,MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,     & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,     & 
& cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,cplcFuFuhhR,cplcgWmgWmhh,              & 
& cplcgWpCgWpChh,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,              & 
& cplAhAhAhhh1,cplAhAhhhhh1,cplAhhhhhhh1,cplAhhhHmcHm1,cplhhhhhhhh1,cplhhhhHmcHm1,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MFd(3),MFe(3),MFu(3),Mhh(2),MHm(2),MVWm,MVZ,MAh2(2),MFd2(3),MFe2(3),           & 
& MFu2(3),Mhh2(2),MHm2(2),MVWm2,MVZ2

Complex(dp), Intent(in) :: cplAhAhAh(2,2,2),cplAhAhhh(2,2,2),cplcFdFdAhL(3,3,2),cplcFdFdAhR(3,3,2),              & 
& cplcFeFeAhL(3,3,2),cplcFeFeAhR(3,3,2),cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),           & 
& cplcgWmgWmAh(2),cplcgWpCgWpCAh(2),cplAhhhhh(2,2,2),cplAhhhVZ(2,2),cplAhHmcHm(2,2,2),   & 
& cplAhHmcVWm(2,2),cplAhcHmVWm(2,2),cplcFdFdhhL(3,3,2),cplcFdFdhhR(3,3,2),               & 
& cplcFeFehhL(3,3,2),cplcFeFehhR(3,3,2),cplcFuFuhhL(3,3,2),cplcFuFuhhR(3,3,2),           & 
& cplcgWmgWmhh(2),cplcgWpCgWpChh(2),cplhhhhhh(2,2,2),cplhhHmcHm(2,2,2),cplhhHmcVWm(2,2), & 
& cplhhcHmVWm(2,2),cplhhcVWmVWm(2),cplAhAhAhhh1(2,2,2,2),cplAhAhhhhh1(2,2,2,2),          & 
& cplAhhhhhhh1(2,2,2,2),cplAhhhHmcHm1(2,2,2,2),cplhhhhhhhh1(2,2,2,2),cplhhhhHmcHm1(2,2,2,2)

Complex(dp), Intent(out) :: Amp(2,2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,2
  Do gt2=1,2
    Do gt3=1,2
Amp(gt1, gt2, gt3) = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = MAh(gt1) 
Mex2 = Mhh(gt2) 
Mex3 = Mhh(gt3) 
    End Do
  End Do
End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_gumTHDMII_AhTohhhh


Subroutine Amplitude_Tree_gumTHDMII_AhTohhVZ(cplAhhhVZ,MAh,Mhh,MVZ,MAh2,              & 
& Mhh2,MVZ2,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),Mhh(2),MVZ,MAh2(2),Mhh2(2),MVZ2

Complex(dp), Intent(in) :: cplAhhhVZ(2,2)

Complex(dp) :: Amp(2,2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 

Do gt1=1,2
  Do gt2=1,2
! External masses 
Mex1 = MAh(gt1) 
Mex2 = Mhh(gt2) 
Mex3 = MVZ 
! Tree-Level Vertex 
coupT1 = cplAhhhVZ(gt1,gt2)
Call TreeAmp_StoSV(Mex1,Mex2,Mex3,coupT1,AmpC) 
! Colour and symmetry factor 
Amp(:,gt1, gt2) = AmpC 
  End Do
End Do
End Subroutine Amplitude_Tree_gumTHDMII_AhTohhVZ


Subroutine Gamma_Real_gumTHDMII_AhTohhVZ(MLambda,em,gs,cplAhhhVZ,MAh,Mhh,             & 
& MVZ,GammarealPhoton,GammarealGluon)

Implicit None

Complex(dp), Intent(in) :: cplAhhhVZ(2,2)

Real(dp), Intent(in) :: MAh(2),Mhh(2),MVZ

Real(dp), Intent(in) :: MLambda, em, gs 

Real(dp), Intent(out) :: GammarealPhoton(2,2), GammarealGluon(2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 

Real(dp) :: Mloop1, Mloop2, Mloop3 
Complex(dp) :: Coup 
 
Do i1=2,2
  Do i2=1,2
Coup = cplAhhhVZ(i1,i2)
Mex1 = MAh(i1)
Mex2 = Mhh(i2)
Mex3 = MVZ
If (Abs(Mex1).gt.(Abs(Mex2)+Abs(Mex3))) Then 
 Gammarealphoton(i1,i2) = 0._dp 
 GammarealGluon(i1,i2) = 0._dp 
Else 
  GammarealGluon(i1,i2) = 0._dp 
  GammarealPhoton(i1,i2) = 0._dp 

End if 
  End Do
End Do
End Subroutine Gamma_Real_gumTHDMII_AhTohhVZ


Subroutine Amplitude_WAVE_gumTHDMII_AhTohhVZ(cplAhhhVZ,ctcplAhhhVZ,MAh,               & 
& MAh2,Mhh,Mhh2,MVZ,MVZ2,ZfAh,Zfhh,ZfVZ,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MAh2(2),Mhh(2),Mhh2(2),MVZ,MVZ2

Complex(dp), Intent(in) :: cplAhhhVZ(2,2)

Complex(dp), Intent(in) :: ctcplAhhhVZ(2,2)

Complex(dp), Intent(in) :: ZfAh(2,2),Zfhh(2,2),ZfVZ

Complex(dp), Intent(out) :: Amp(2,2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

Do gt1=1,2
  Do gt2=1,2
! External masses 
Mex1 = MAh(gt1) 
Mex2 = Mhh(gt2) 
Mex3 = MVZ 
!----------------------------- 
! Coupling counter term 
!----------------------------- 
ZcoupT1 = ctcplAhhhVZ(gt1,gt2) 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
Do i1=1,2
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfAh(i1,gt1)*cplAhhhVZ(i1,gt2)
End Do


! External Field 2 
Do i1=1,2
ZcoupT1 = ZcoupT1 + 0.5_dp*Zfhh(i1,gt2)*cplAhhhVZ(gt1,i1)
End Do


! External Field 3 
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfVZ*cplAhhhVZ(gt1,gt2)


! Getting the amplitude 
Call TreeAmp_StoSV(Mex1,Mex2,Mex3,ZcoupT1,AmpC) 
Amp(:,gt1, gt2) = AmpC 
  End Do
End Do
End Subroutine Amplitude_WAVE_gumTHDMII_AhTohhVZ


Subroutine Amplitude_VERTEX_gumTHDMII_AhTohhVZ(MAh,MFd,MFe,MFu,Mhh,MHm,               & 
& MVWm,MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,     & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,     & 
& cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmhh,              & 
& cplcgWmgWmVZ,cplcgWpCgWpChh,cplcgWpCgWpCVZ,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,           & 
& cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVWmVZ,cplcVWmVWmVZ,    & 
& cplAhAhVZVZ1,cplAhHmcVWmVZ1,cplAhcHmVWmVZ1,cplhhhhVZVZ1,cplhhHmcVWmVZ1,cplhhcHmVWmVZ1,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MFd(3),MFe(3),MFu(3),Mhh(2),MHm(2),MVWm,MVZ,MAh2(2),MFd2(3),MFe2(3),           & 
& MFu2(3),Mhh2(2),MHm2(2),MVWm2,MVZ2

Complex(dp), Intent(in) :: cplAhAhAh(2,2,2),cplAhAhhh(2,2,2),cplcFdFdAhL(3,3,2),cplcFdFdAhR(3,3,2),              & 
& cplcFeFeAhL(3,3,2),cplcFeFeAhR(3,3,2),cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),           & 
& cplcgWmgWmAh(2),cplcgWpCgWpCAh(2),cplAhhhhh(2,2,2),cplAhhhVZ(2,2),cplAhHmcHm(2,2,2),   & 
& cplAhHmcVWm(2,2),cplAhcHmVWm(2,2),cplcFdFdhhL(3,3,2),cplcFdFdhhR(3,3,2),               & 
& cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFeFehhL(3,3,2),cplcFeFehhR(3,3,2),               & 
& cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),cplcFuFuhhL(3,3,2),cplcFuFuhhR(3,3,2),               & 
& cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplcgWmgWmhh(2),cplcgWmgWmVZ,cplcgWpCgWpChh(2),      & 
& cplcgWpCgWpCVZ,cplhhhhhh(2,2,2),cplhhHmcHm(2,2,2),cplhhHmcVWm(2,2),cplhhcHmVWm(2,2),   & 
& cplhhcVWmVWm(2),cplhhVZVZ(2),cplHmcHmVZ(2,2),cplHmcVWmVZ(2),cplcHmVWmVZ(2),            & 
& cplcVWmVWmVZ,cplAhAhVZVZ1(2,2),cplAhHmcVWmVZ1(2,2),cplAhcHmVWmVZ1(2,2),cplhhhhVZVZ1(2,2),& 
& cplhhHmcVWmVZ1(2,2),cplhhcHmVWmVZ1(2,2)

Complex(dp), Intent(out) :: Amp(2,2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,2
  Do gt2=1,2
Amp(:,gt1, gt2) = 0._dp 
! External masses 
Mex1 = MAh(gt1) 
Mex2 = Mhh(gt2) 
Mex3 = MVZ 


! {Ah, hh, Ah}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MAh(i1) 
ML2 = Mhh(i2) 
ML3 = MAh(i3) 
coup1 = cplAhAhhh(gt1,i1,i2)
coup2 = cplAhAhhh(i1,i3,gt2)
coup3 = cplAhhhVZ(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Ah, Ah, hh}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MAh(i1) 
ML2 = MAh(i2) 
ML3 = Mhh(i3) 
coup1 = cplAhAhAh(gt1,i1,i2)
coup2 = cplAhhhhh(i1,gt2,i3)
coup3 = -cplAhhhVZ(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Ah, hh, VZ}
Do i1=1,2
  Do i2=1,2
ML1 = MAh(i1) 
ML2 = Mhh(i2) 
ML3 = MVZ 
coup1 = cplAhAhhh(gt1,i1,i2)
coup2 = -cplAhhhVZ(i1,gt2)
coup3 = cplhhVZVZ(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Fd, Fd, Fd}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFd(i1) 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFdFdAhL(i2,i1,gt1)
coup1R = cplcFdFdAhR(i2,i1,gt1)
coup2L = cplcFdFdhhL(i1,i3,gt2)
coup2R = cplcFdFdhhR(i1,i3,gt2)
coup3L = -cplcFdFdVZR(i3,i2)
coup3R = -cplcFdFdVZL(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(6)*AmpC 
    End Do
  End Do
End Do


! {Fe, Fe, Fe}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFe(i1) 
ML2 = MFe(i2) 
ML3 = MFe(i3) 
coup1L = cplcFeFeAhL(i2,i1,gt1)
coup1R = cplcFeFeAhR(i2,i1,gt1)
coup2L = cplcFeFehhL(i1,i3,gt2)
coup2R = cplcFeFehhR(i1,i3,gt2)
coup3L = -cplcFeFeVZR(i3,i2)
coup3R = -cplcFeFeVZL(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(2)*AmpC 
    End Do
  End Do
End Do


! {Fu, Fu, Fu}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFu(i1) 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = cplcFuFuAhL(i2,i1,gt1)
coup1R = cplcFuFuAhR(i2,i1,gt1)
coup2L = cplcFuFuhhL(i1,i3,gt2)
coup2R = cplcFuFuhhR(i1,i3,gt2)
coup3L = -cplcFuFuVZR(i3,i2)
coup3R = -cplcFuFuVZL(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(6)*AmpC 
    End Do
  End Do
End Do


! {gWm, gWm, gWm}
ML1 = MVWm 
ML2 = MVWm 
ML3 = MVWm 
coup1 = cplcgWmgWmAh(gt1)
coup2 = cplcgWmgWmhh(gt2)
coup3 = cplcgWmgWmVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(2)*AmpC 


! {gWmC, gWmC, gWmC}
ML1 = MVWm 
ML2 = MVWm 
ML3 = MVWm 
coup1 = cplcgWpCgWpCAh(gt1)
coup2 = cplcgWpCgWpChh(gt2)
coup3 = cplcgWpCgWpCVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(2)*AmpC 


! {hh, hh, Ah}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = Mhh(i1) 
ML2 = Mhh(i2) 
ML3 = MAh(i3) 
coup1 = cplAhhhhh(gt1,i1,i2)
coup2 = cplAhhhhh(i3,gt2,i1)
coup3 = cplAhhhVZ(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {hh, Ah, hh}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = Mhh(i1) 
ML2 = MAh(i2) 
ML3 = Mhh(i3) 
coup1 = cplAhAhhh(gt1,i2,i1)
coup2 = cplhhhhhh(gt2,i1,i3)
coup3 = -cplAhhhVZ(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {hh, VZ, hh}
Do i1=1,2
    Do i3=1,2
ML1 = Mhh(i1) 
ML2 = MVZ 
ML3 = Mhh(i3) 
coup1 = -cplAhhhVZ(gt1,i1)
coup2 = cplhhhhhh(gt2,i1,i3)
coup3 = cplhhVZVZ(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hm, Hm, Hm}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
ML3 = MHm(i3) 
coup1 = cplAhHmcHm(gt1,i1,i2)
coup2 = cplhhHmcHm(gt2,i3,i1)
coup3 = -cplHmcHmVZ(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(2)*AmpC 
    End Do
  End Do
End Do


! {Hm, VWm, Hm}
Do i1=1,2
    Do i3=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
ML3 = MHm(i3) 
coup1 = -cplAhHmcVWm(gt1,i1)
coup2 = cplhhHmcHm(gt2,i3,i1)
coup3 = cplcHmVWmVZ(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hm, Hm, VWm}
Do i1=1,2
  Do i2=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
ML3 = MVWm 
coup1 = cplAhHmcHm(gt1,i1,i2)
coup2 = cplhhcHmVWm(gt2,i1)
coup3 = cplHmcVWmVZ(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Hm, VWm, VWm}
Do i1=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
ML3 = MVWm 
coup1 = -cplAhHmcVWm(gt1,i1)
coup2 = cplhhcHmVWm(gt2,i1)
coup3 = -cplcVWmVWmVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {VWm, Hm, Hm}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
ML3 = MHm(i3) 
coup1 = -cplAhcHmVWm(gt1,i2)
coup2 = cplhhHmcVWm(gt2,i3)
coup3 = -cplHmcHmVZ(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VWm, Hm, VWm}
  Do i2=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
ML3 = MVWm 
coup1 = -cplAhcHmVWm(gt1,i2)
coup2 = cplhhcVWmVWm(gt2)
coup3 = cplHmcVWmVZ(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do


! {VZ, hh, Ah}
  Do i2=1,2
    Do i3=1,2
ML1 = MVZ 
ML2 = Mhh(i2) 
ML3 = MAh(i3) 
coup1 = -cplAhhhVZ(gt1,i2)
coup2 = -cplAhhhVZ(i3,gt2)
coup3 = cplAhhhVZ(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VZ, hh, VZ}
  Do i2=1,2
ML1 = MVZ 
ML2 = Mhh(i2) 
ML3 = MVZ 
coup1 = -cplAhhhVZ(gt1,i2)
coup2 = cplhhVZVZ(gt2)
coup3 = cplhhVZVZ(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do


! {conj[Hm], conj[VWm], conj[Hm]}
Do i1=1,2
    Do i3=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
ML3 = MHm(i3) 
coup1 = -cplAhcHmVWm(gt1,i1)
coup2 = cplhhHmcHm(gt2,i1,i3)
coup3 = cplHmcVWmVZ(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {conj[Hm], conj[Hm], conj[VWm]}
Do i1=1,2
  Do i2=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
ML3 = MVWm 
coup1 = cplAhHmcHm(gt1,i2,i1)
coup2 = cplhhHmcVWm(gt2,i1)
coup3 = cplcHmVWmVZ(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {conj[Hm], conj[VWm], conj[VWm]}
Do i1=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
ML3 = MVWm 
coup1 = -cplAhcHmVWm(gt1,i1)
coup2 = cplhhHmcVWm(gt2,i1)
coup3 = cplcVWmVWmVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {conj[VWm], conj[Hm], conj[Hm]}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
ML3 = MHm(i3) 
coup1 = -cplAhHmcVWm(gt1,i2)
coup2 = cplhhcHmVWm(gt2,i3)
coup3 = cplHmcHmVZ(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {conj[VWm], conj[Hm], conj[VWm]}
  Do i2=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
ML3 = MVWm 
coup1 = -cplAhHmcVWm(gt1,i2)
coup2 = cplhhcVWmVWm(gt2)
coup3 = cplcHmVWmVZ(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do


! {hh, VZ}
Do i1=1,2
ML1 = Mhh(i1) 
ML2 = MVZ 
coup1 = cplAhhhVZ(gt1,i1)
coup2 = cplhhhhVZVZ1(gt2,i1)
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {Hm, VWm}
Do i1=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
coup1 = cplAhHmcVWm(gt1,i1)
coup2 = cplhhcHmVWmVZ1(gt2,i1)
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {VWm, Hm}
  Do i2=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
coup1 = cplAhcHmVWm(gt1,i2)
coup2 = cplhhHmcVWmVZ1(gt2,i2)
Call Amp_VERTEX_StoSV_Topology2_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do


! {Ah, VZ}
Do i1=1,2
ML1 = MAh(i1) 
ML2 = MVZ 
coup1 = cplAhAhVZVZ1(gt1,i1)
coup2 = -cplAhhhVZ(i1,gt2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 

End Do


! {Hm, VWm}
Do i1=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
coup1 = cplAhHmcVWmVZ1(gt1,i1)
coup2 = cplhhcHmVWm(gt2,i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 

End Do


! {VWm, Hm}
  Do i2=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
coup1 = cplAhcHmVWmVZ1(gt1,i2)
coup2 = cplhhHmcVWm(gt2,i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 

  End Do
  End Do
End Do
End Subroutine Amplitude_VERTEX_gumTHDMII_AhTohhVZ


Subroutine Amplitude_IR_VERTEX_gumTHDMII_AhTohhVZ(MAh,MFd,MFe,MFu,Mhh,MHm,            & 
& MVWm,MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,     & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,     & 
& cplcFdFdhhR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmhh,              & 
& cplcgWmgWmVZ,cplcgWpCgWpChh,cplcgWpCgWpCVZ,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,           & 
& cplhhcHmVWm,cplhhcVWmVWm,cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVWmVZ,cplcVWmVWmVZ,    & 
& cplAhAhVZVZ1,cplAhHmcVWmVZ1,cplAhcHmVWmVZ1,cplhhhhVZVZ1,cplhhHmcVWmVZ1,cplhhcHmVWmVZ1,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MFd(3),MFe(3),MFu(3),Mhh(2),MHm(2),MVWm,MVZ,MAh2(2),MFd2(3),MFe2(3),           & 
& MFu2(3),Mhh2(2),MHm2(2),MVWm2,MVZ2

Complex(dp), Intent(in) :: cplAhAhAh(2,2,2),cplAhAhhh(2,2,2),cplcFdFdAhL(3,3,2),cplcFdFdAhR(3,3,2),              & 
& cplcFeFeAhL(3,3,2),cplcFeFeAhR(3,3,2),cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),           & 
& cplcgWmgWmAh(2),cplcgWpCgWpCAh(2),cplAhhhhh(2,2,2),cplAhhhVZ(2,2),cplAhHmcHm(2,2,2),   & 
& cplAhHmcVWm(2,2),cplAhcHmVWm(2,2),cplcFdFdhhL(3,3,2),cplcFdFdhhR(3,3,2),               & 
& cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFeFehhL(3,3,2),cplcFeFehhR(3,3,2),               & 
& cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),cplcFuFuhhL(3,3,2),cplcFuFuhhR(3,3,2),               & 
& cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplcgWmgWmhh(2),cplcgWmgWmVZ,cplcgWpCgWpChh(2),      & 
& cplcgWpCgWpCVZ,cplhhhhhh(2,2,2),cplhhHmcHm(2,2,2),cplhhHmcVWm(2,2),cplhhcHmVWm(2,2),   & 
& cplhhcVWmVWm(2),cplhhVZVZ(2),cplHmcHmVZ(2,2),cplHmcVWmVZ(2),cplcHmVWmVZ(2),            & 
& cplcVWmVWmVZ,cplAhAhVZVZ1(2,2),cplAhHmcVWmVZ1(2,2),cplAhcHmVWmVZ1(2,2),cplhhhhVZVZ1(2,2),& 
& cplhhHmcVWmVZ1(2,2),cplhhcHmVWmVZ1(2,2)

Complex(dp), Intent(out) :: Amp(2,2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,2
  Do gt2=1,2
Amp(:,gt1, gt2) = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = MAh(gt1) 
Mex2 = Mhh(gt2) 
Mex3 = MVZ 
  End Do
End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_gumTHDMII_AhTohhVZ


Subroutine Amplitude_Tree_gumTHDMII_AhTocHmHm(cplAhHmcHm,MAh,MHm,MAh2,MHm2,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MHm(2),MAh2(2),MHm2(2)

Complex(dp), Intent(in) :: cplAhHmcHm(2,2,2)

Complex(dp) :: Amp(2,2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 

Do gt1=1,2
  Do gt2=1,2
    Do gt3=1,2
! External masses 
Mex1 = MAh(gt1) 
Mex2 = MHm(gt2) 
Mex3 = MHm(gt3) 
! Tree-Level Vertex 
coupT1 = cplAhHmcHm(gt1,gt3,gt2)
Call TreeAmp_StoSS(Mex1,Mex2,Mex3,coupT1,AmpC) 
! Colour and symmetry factor 
Amp(gt1, gt2, gt3) = AmpC 
    End Do
  End Do
End Do
End Subroutine Amplitude_Tree_gumTHDMII_AhTocHmHm


Subroutine Gamma_Real_gumTHDMII_AhTocHmHm(MLambda,em,gs,cplAhHmcHm,MAh,               & 
& MHm,GammarealPhoton,GammarealGluon)

Implicit None

Complex(dp), Intent(in) :: cplAhHmcHm(2,2,2)

Real(dp), Intent(in) :: MAh(2),MHm(2)

Real(dp), Intent(in) :: MLambda, em, gs 

Real(dp), Intent(out) :: GammarealPhoton(2,2,2), GammarealGluon(2,2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 

Real(dp) :: Mloop1, Mloop2, Mloop3 
Complex(dp) :: Coup 
 
Do i1=2,2
  Do i2=2,2
    Do i3=2,2
Coup = cplAhHmcHm(i1,i3,i2)
Mex1 = MAh(i1)
Mex2 = MHm(i2)
Mex3 = MHm(i3)
If (Abs(Mex1).gt.(Abs(Mex2)+Abs(Mex3))) Then 
 Call hardradiationSSS(Mex1,Mex2,Mex3,MLambda,em,0._dp,0._dp,0._dp,1._dp,-1._dp,1._dp,Coup,Gammarealphoton(i1,i2,i3),kont)
  GammarealGluon(i1,i2,i3) = 0._dp 
Else 
  GammarealGluon(i1,i2,i3) = 0._dp 
  GammarealPhoton(i1,i2,i3) = 0._dp 

End if 
    End Do
  End Do
End Do
End Subroutine Gamma_Real_gumTHDMII_AhTocHmHm


Subroutine Amplitude_WAVE_gumTHDMII_AhTocHmHm(cplAhHmcHm,ctcplAhHmcHm,MAh,            & 
& MAh2,MHm,MHm2,ZfAh,ZfHm,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MAh2(2),MHm(2),MHm2(2)

Complex(dp), Intent(in) :: cplAhHmcHm(2,2,2)

Complex(dp), Intent(in) :: ctcplAhHmcHm(2,2,2)

Complex(dp), Intent(in) :: ZfAh(2,2),ZfHm(2,2)

Complex(dp), Intent(out) :: Amp(2,2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

Do gt1=1,2
  Do gt2=1,2
    Do gt3=1,2
! External masses 
Mex1 = MAh(gt1) 
Mex2 = MHm(gt2) 
Mex3 = MHm(gt3) 
!----------------------------- 
! Coupling counter term 
!----------------------------- 
ZcoupT1 = ctcplAhHmcHm(gt1,gt3,gt2) 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
Do i1=1,2
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfAh(i1,gt1)*cplAhHmcHm(i1,gt3,gt2)
End Do


! External Field 2 
Do i1=1,2
ZcoupT1 = ZcoupT1 + 0.5_dp*Conjg(ZfHm(i1,gt2))*cplAhHmcHm(gt1,gt3,i1)
End Do


! External Field 3 
Do i1=1,2
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfHm(i1,gt3)*cplAhHmcHm(gt1,i1,gt2)
End Do


! Getting the amplitude 
Call TreeAmp_StoSS(Mex1,Mex2,Mex3,ZcoupT1,AmpC) 
Amp(gt1, gt2, gt3) = AmpC 
    End Do
  End Do
End Do
End Subroutine Amplitude_WAVE_gumTHDMII_AhTocHmHm


Subroutine Amplitude_VERTEX_gumTHDMII_AhTocHmHm(MAh,MFd,MFe,MFu,Mhh,MHm,              & 
& MVP,MVWm,MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,        & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,               & 
& cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,    & 
& cplcFuFdcHmL,cplcFuFdcHmR,cplcFvFecHmL,cplcFvFecHmR,cplcFdFuHmL,cplcFdFuHmR,           & 
& cplcFeFvHmL,cplcFeFvHmR,cplcgZgWmcHm,cplcgZgWpCHm,cplcgWmgZHm,cplcgWpCgZcHm,           & 
& cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplHmcHmVP,cplHmcVWmVP,cplHmcHmVZ,cplHmcVWmVZ,      & 
& cplcHmVPVWm,cplcHmVWmVZ,cplAhAhHmcHm1,cplAhhhHmcHm1,cplAhHmcVWmVP1,cplAhHmcVWmVZ1,     & 
& cplAhcHmVPVWm1,cplAhcHmVWmVZ1,cplhhhhHmcHm1,cplHmHmcHmcHm1,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MFd(3),MFe(3),MFu(3),Mhh(2),MHm(2),MVP,MVWm,MVZ,MAh2(2),MFd2(3),               & 
& MFe2(3),MFu2(3),Mhh2(2),MHm2(2),MVP2,MVWm2,MVZ2

Complex(dp), Intent(in) :: cplAhAhAh(2,2,2),cplAhAhhh(2,2,2),cplcFdFdAhL(3,3,2),cplcFdFdAhR(3,3,2),              & 
& cplcFeFeAhL(3,3,2),cplcFeFeAhR(3,3,2),cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),           & 
& cplcgWmgWmAh(2),cplcgWpCgWpCAh(2),cplAhhhhh(2,2,2),cplAhhhVZ(2,2),cplAhHmcHm(2,2,2),   & 
& cplAhHmcVWm(2,2),cplAhcHmVWm(2,2),cplcFuFdcHmL(3,3,2),cplcFuFdcHmR(3,3,2),             & 
& cplcFvFecHmL(3,3,2),cplcFvFecHmR(3,3,2),cplcFdFuHmL(3,3,2),cplcFdFuHmR(3,3,2),         & 
& cplcFeFvHmL(3,3,2),cplcFeFvHmR(3,3,2),cplcgZgWmcHm(2),cplcgZgWpCHm(2),cplcgWmgZHm(2),  & 
& cplcgWpCgZcHm(2),cplhhHmcHm(2,2,2),cplhhHmcVWm(2,2),cplhhcHmVWm(2,2),cplHmcHmVP(2,2),  & 
& cplHmcVWmVP(2),cplHmcHmVZ(2,2),cplHmcVWmVZ(2),cplcHmVPVWm(2),cplcHmVWmVZ(2),           & 
& cplAhAhHmcHm1(2,2,2,2),cplAhhhHmcHm1(2,2,2,2),cplAhHmcVWmVP1(2,2),cplAhHmcVWmVZ1(2,2), & 
& cplAhcHmVPVWm1(2,2),cplAhcHmVWmVZ1(2,2),cplhhhhHmcHm1(2,2,2,2),cplHmHmcHmcHm1(2,2,2,2)

Complex(dp), Intent(out) :: Amp(2,2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,2
  Do gt2=1,2
    Do gt3=1,2
Amp(gt1, gt2, gt3) = 0._dp 
! External masses 
Mex1 = MAh(gt1) 
Mex2 = MHm(gt2) 
Mex3 = MHm(gt3) 


! {Ah, Ah, Hm}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MAh(i1) 
ML2 = MAh(i2) 
ML3 = MHm(i3) 
coup1 = cplAhAhAh(gt1,i1,i2)
coup2 = cplAhHmcHm(i1,i3,gt2)
coup3 = cplAhHmcHm(i2,gt3,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Ah, hh, Hm}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MAh(i1) 
ML2 = Mhh(i2) 
ML3 = MHm(i3) 
coup1 = cplAhAhhh(gt1,i1,i2)
coup2 = cplAhHmcHm(i1,i3,gt2)
coup3 = cplhhHmcHm(i2,gt3,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Ah, Ah, VWm}
Do i1=1,2
  Do i2=1,2
ML1 = MAh(i1) 
ML2 = MAh(i2) 
ML3 = MVWm 
coup1 = cplAhAhAh(gt1,i1,i2)
coup2 = cplAhcHmVWm(i1,gt2)
coup3 = -cplAhHmcVWm(i2,gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Ah, hh, VWm}
Do i1=1,2
  Do i2=1,2
ML1 = MAh(i1) 
ML2 = Mhh(i2) 
ML3 = MVWm 
coup1 = cplAhAhhh(gt1,i1,i2)
coup2 = cplAhcHmVWm(i1,gt2)
coup3 = -cplhhHmcVWm(i2,gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Fu, Fu, Fd}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFu(i1) 
ML2 = MFu(i2) 
ML3 = MFd(i3) 
coup1L = cplcFuFuAhL(i2,i1,gt1)
coup1R = cplcFuFuAhR(i2,i1,gt1)
coup2L = cplcFuFdcHmL(i1,i3,gt2)
coup2R = cplcFuFdcHmR(i1,i3,gt2)
coup3L = cplcFdFuHmL(i3,i2,gt3)
coup3R = cplcFdFuHmR(i3,i2,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(3)*AmpC 
    End Do
  End Do
End Do


! {gWmC, gWmC, gZ}
ML1 = MVWm 
ML2 = MVWm 
ML3 = MVZ 
coup1 = cplcgWpCgWpCAh(gt1)
coup2 = cplcgWpCgZcHm(gt2)
coup3 = cplcgZgWpCHm(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 


! {hh, Ah, Hm}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = Mhh(i1) 
ML2 = MAh(i2) 
ML3 = MHm(i3) 
coup1 = cplAhAhhh(gt1,i2,i1)
coup2 = cplhhHmcHm(i1,i3,gt2)
coup3 = cplAhHmcHm(i2,gt3,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {hh, hh, Hm}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = Mhh(i1) 
ML2 = Mhh(i2) 
ML3 = MHm(i3) 
coup1 = cplAhhhhh(gt1,i1,i2)
coup2 = cplhhHmcHm(i1,i3,gt2)
coup3 = cplhhHmcHm(i2,gt3,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {hh, VZ, Hm}
Do i1=1,2
    Do i3=1,2
ML1 = Mhh(i1) 
ML2 = MVZ 
ML3 = MHm(i3) 
coup1 = -cplAhhhVZ(gt1,i1)
coup2 = cplhhHmcHm(i1,i3,gt2)
coup3 = cplHmcHmVZ(gt3,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {hh, Ah, VWm}
Do i1=1,2
  Do i2=1,2
ML1 = Mhh(i1) 
ML2 = MAh(i2) 
ML3 = MVWm 
coup1 = cplAhAhhh(gt1,i2,i1)
coup2 = cplhhcHmVWm(i1,gt2)
coup3 = -cplAhHmcVWm(i2,gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {hh, hh, VWm}
Do i1=1,2
  Do i2=1,2
ML1 = Mhh(i1) 
ML2 = Mhh(i2) 
ML3 = MVWm 
coup1 = cplAhhhhh(gt1,i1,i2)
coup2 = cplhhcHmVWm(i1,gt2)
coup3 = -cplhhHmcVWm(i2,gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {hh, VZ, VWm}
Do i1=1,2
ML1 = Mhh(i1) 
ML2 = MVZ 
ML3 = MVWm 
coup1 = -cplAhhhVZ(gt1,i1)
coup2 = cplhhcHmVWm(i1,gt2)
coup3 = cplHmcVWmVZ(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
End Do


! {VZ, hh, Hm}
  Do i2=1,2
    Do i3=1,2
ML1 = MVZ 
ML2 = Mhh(i2) 
ML3 = MHm(i3) 
coup1 = -cplAhhhVZ(gt1,i2)
coup2 = cplHmcHmVZ(i3,gt2)
coup3 = cplhhHmcHm(i2,gt3,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VZ, hh, VWm}
  Do i2=1,2
ML1 = MVZ 
ML2 = Mhh(i2) 
ML3 = MVWm 
coup1 = -cplAhhhVZ(gt1,i2)
coup2 = cplcHmVWmVZ(gt2)
coup3 = -cplhhHmcVWm(i2,gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do


! {bar[Fd], bar[Fd], bar[Fu]}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFd(i1) 
ML2 = MFd(i2) 
ML3 = MFu(i3) 
coup1L = cplcFdFdAhL(i1,i2,gt1)
coup1R = cplcFdFdAhR(i1,i2,gt1)
coup2L = cplcFuFdcHmL(i3,i1,gt2)
coup2R = cplcFuFdcHmR(i3,i1,gt2)
coup3L = cplcFdFuHmL(i2,i3,gt3)
coup3R = cplcFdFuHmR(i2,i3,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(3)*AmpC 
    End Do
  End Do
End Do


! {bar[Fe], bar[Fe], bar[Fv]}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFe(i1) 
ML2 = MFe(i2) 
ML3 = 0._dp 
coup1L = cplcFeFeAhL(i1,i2,gt1)
coup1R = cplcFeFeAhR(i1,i2,gt1)
coup2L = cplcFvFecHmL(i3,i1,gt2)
coup2R = cplcFvFecHmR(i3,i1,gt2)
coup3L = cplcFeFvHmL(i2,i3,gt3)
coup3R = cplcFeFvHmR(i2,i3,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {bar[gWm], bar[gWm], bar[gZ]}
ML1 = MVWm 
ML2 = MVWm 
ML3 = MVZ 
coup1 = cplcgWmgWmAh(gt1)
coup2 = cplcgZgWmcHm(gt2)
coup3 = cplcgWmgZHm(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 


! {conj[Hm], conj[Hm], Ah}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
ML3 = MAh(i3) 
coup1 = cplAhHmcHm(gt1,i2,i1)
coup2 = cplAhHmcHm(i3,i1,gt2)
coup3 = cplAhHmcHm(i3,gt3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {conj[Hm], conj[VWm], Ah}
Do i1=1,2
    Do i3=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
ML3 = MAh(i3) 
coup1 = -cplAhcHmVWm(gt1,i1)
coup2 = cplAhHmcHm(i3,i1,gt2)
coup3 = -cplAhHmcVWm(i3,gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {conj[Hm], conj[Hm], hh}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
ML3 = Mhh(i3) 
coup1 = cplAhHmcHm(gt1,i2,i1)
coup2 = cplhhHmcHm(i3,i1,gt2)
coup3 = cplhhHmcHm(i3,gt3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {conj[Hm], conj[VWm], hh}
Do i1=1,2
    Do i3=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
ML3 = Mhh(i3) 
coup1 = -cplAhcHmVWm(gt1,i1)
coup2 = cplhhHmcHm(i3,i1,gt2)
coup3 = -cplhhHmcVWm(i3,gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {conj[Hm], conj[Hm], VP}
Do i1=1,2
  Do i2=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
ML3 = MVP 
coup1 = cplAhHmcHm(gt1,i2,i1)
coup2 = cplHmcHmVP(i1,gt2)
coup3 = cplHmcHmVP(gt3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {conj[Hm], conj[VWm], VP}
Do i1=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
ML3 = MVP 
coup1 = -cplAhcHmVWm(gt1,i1)
coup2 = cplHmcHmVP(i1,gt2)
coup3 = cplHmcVWmVP(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
End Do


! {conj[Hm], conj[Hm], VZ}
Do i1=1,2
  Do i2=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
ML3 = MVZ 
coup1 = cplAhHmcHm(gt1,i2,i1)
coup2 = cplHmcHmVZ(i1,gt2)
coup3 = cplHmcHmVZ(gt3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {conj[Hm], conj[VWm], VZ}
Do i1=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
ML3 = MVZ 
coup1 = -cplAhcHmVWm(gt1,i1)
coup2 = cplHmcHmVZ(i1,gt2)
coup3 = cplHmcVWmVZ(gt3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
End Do


! {conj[VWm], conj[Hm], Ah}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
ML3 = MAh(i3) 
coup1 = -cplAhHmcVWm(gt1,i2)
coup2 = cplAhcHmVWm(i3,gt2)
coup3 = cplAhHmcHm(i3,gt3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {conj[VWm], conj[Hm], hh}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
ML3 = Mhh(i3) 
coup1 = -cplAhHmcVWm(gt1,i2)
coup2 = cplhhcHmVWm(i3,gt2)
coup3 = cplhhHmcHm(i3,gt3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {conj[VWm], conj[Hm], VP}
  Do i2=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
ML3 = MVP 
coup1 = -cplAhHmcVWm(gt1,i2)
coup2 = cplcHmVPVWm(gt2)
coup3 = cplHmcHmVP(gt3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do


! {conj[VWm], conj[Hm], VZ}
  Do i2=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
ML3 = MVZ 
coup1 = -cplAhHmcVWm(gt1,i2)
coup2 = cplcHmVWmVZ(gt2)
coup3 = cplHmcHmVZ(gt3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do


! {Ah, Ah}
Do i1=1,2
  Do i2=1,2
ML1 = MAh(i1) 
ML2 = MAh(i2) 
coup1 = cplAhAhAh(gt1,i1,i2)
coup2 = cplAhAhHmcHm1(i1,i2,gt3,gt2)
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1._dp/2._dp)*AmpC 
  End Do
End Do


! {Ah, hh}
Do i1=1,2
  Do i2=1,2
ML1 = MAh(i1) 
ML2 = Mhh(i2) 
coup1 = cplAhAhhh(gt1,i1,i2)
coup2 = cplAhhhHmcHm1(i1,i2,gt3,gt2)
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {hh, hh}
Do i1=1,2
  Do i2=1,2
ML1 = Mhh(i1) 
ML2 = Mhh(i2) 
coup1 = cplAhhhhh(gt1,i1,i2)
coup2 = cplhhhhHmcHm1(i1,i2,gt3,gt2)
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1._dp/2._dp)*AmpC 
  End Do
End Do


! {Hm, Hm}
Do i1=1,2
  Do i2=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
coup1 = cplAhHmcHm(gt1,i1,i2)
coup2 = cplHmHmcHmcHm1(gt3,i2,gt2,i1)
Call Amp_VERTEX_StoSS_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Ah, Hm}
Do i1=1,2
  Do i2=1,2
ML1 = MAh(i1) 
ML2 = MHm(i2) 
coup1 = cplAhAhHmcHm1(gt1,i1,gt3,i2)
coup2 = cplAhHmcHm(i1,i2,gt2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 

  End Do
End Do


! {hh, Hm}
Do i1=1,2
  Do i2=1,2
ML1 = Mhh(i1) 
ML2 = MHm(i2) 
coup1 = cplAhhhHmcHm1(gt1,i1,gt3,i2)
coup2 = cplhhHmcHm(i1,i2,gt2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 

  End Do
End Do


! {VP, VWm}
ML1 = MVP 
ML2 = MVWm 
coup1 = cplAhHmcVWmVP1(gt1,gt3)
coup2 = cplcHmVPVWm(gt2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 



! {VZ, VWm}
ML1 = MVZ 
ML2 = MVWm 
coup1 = cplAhHmcVWmVZ1(gt1,gt3)
coup2 = cplcHmVWmVZ(gt2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology3_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 



! {Ah, conj[Hm]}
Do i1=1,2
  Do i2=1,2
ML1 = MAh(i1) 
ML2 = MHm(i2) 
coup1 = cplAhAhHmcHm1(gt1,i1,i2,gt2)
coup2 = cplAhHmcHm(i1,gt3,i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 

  End Do
End Do


! {hh, conj[Hm]}
Do i1=1,2
  Do i2=1,2
ML1 = Mhh(i1) 
ML2 = MHm(i2) 
coup1 = cplAhhhHmcHm1(gt1,i1,i2,gt2)
coup2 = cplhhHmcHm(i1,gt3,i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 

  End Do
End Do


! {VP, conj[VWm]}
ML1 = MVP 
ML2 = MVWm 
coup1 = cplAhcHmVPVWm1(gt1,gt2)
coup2 = cplHmcVWmVP(gt3)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 



! {VWm, VZ}
ML1 = MVWm 
ML2 = MVZ 
coup1 = cplAhcHmVWmVZ1(gt1,gt2)
coup2 = cplHmcVWmVZ(gt3)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSS_Topology4_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 

    End Do
  End Do
End Do
End Subroutine Amplitude_VERTEX_gumTHDMII_AhTocHmHm


Subroutine Amplitude_IR_VERTEX_gumTHDMII_AhTocHmHm(MAh,MFd,MFe,MFu,Mhh,               & 
& MHm,MVP,MVWm,MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhAh,              & 
& cplAhAhhh,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,     & 
& cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,    & 
& cplcFuFdcHmL,cplcFuFdcHmR,cplcFvFecHmL,cplcFvFecHmR,cplcFdFuHmL,cplcFdFuHmR,           & 
& cplcFeFvHmL,cplcFeFvHmR,cplcgZgWmcHm,cplcgZgWpCHm,cplcgWmgZHm,cplcgWpCgZcHm,           & 
& cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplHmcHmVP,cplHmcVWmVP,cplHmcHmVZ,cplHmcVWmVZ,      & 
& cplcHmVPVWm,cplcHmVWmVZ,cplAhAhHmcHm1,cplAhhhHmcHm1,cplAhHmcVWmVP1,cplAhHmcVWmVZ1,     & 
& cplAhcHmVPVWm1,cplAhcHmVWmVZ1,cplhhhhHmcHm1,cplHmHmcHmcHm1,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MFd(3),MFe(3),MFu(3),Mhh(2),MHm(2),MVP,MVWm,MVZ,MAh2(2),MFd2(3),               & 
& MFe2(3),MFu2(3),Mhh2(2),MHm2(2),MVP2,MVWm2,MVZ2

Complex(dp), Intent(in) :: cplAhAhAh(2,2,2),cplAhAhhh(2,2,2),cplcFdFdAhL(3,3,2),cplcFdFdAhR(3,3,2),              & 
& cplcFeFeAhL(3,3,2),cplcFeFeAhR(3,3,2),cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),           & 
& cplcgWmgWmAh(2),cplcgWpCgWpCAh(2),cplAhhhhh(2,2,2),cplAhhhVZ(2,2),cplAhHmcHm(2,2,2),   & 
& cplAhHmcVWm(2,2),cplAhcHmVWm(2,2),cplcFuFdcHmL(3,3,2),cplcFuFdcHmR(3,3,2),             & 
& cplcFvFecHmL(3,3,2),cplcFvFecHmR(3,3,2),cplcFdFuHmL(3,3,2),cplcFdFuHmR(3,3,2),         & 
& cplcFeFvHmL(3,3,2),cplcFeFvHmR(3,3,2),cplcgZgWmcHm(2),cplcgZgWpCHm(2),cplcgWmgZHm(2),  & 
& cplcgWpCgZcHm(2),cplhhHmcHm(2,2,2),cplhhHmcVWm(2,2),cplhhcHmVWm(2,2),cplHmcHmVP(2,2),  & 
& cplHmcVWmVP(2),cplHmcHmVZ(2,2),cplHmcVWmVZ(2),cplcHmVPVWm(2),cplcHmVWmVZ(2),           & 
& cplAhAhHmcHm1(2,2,2,2),cplAhhhHmcHm1(2,2,2,2),cplAhHmcVWmVP1(2,2),cplAhHmcVWmVZ1(2,2), & 
& cplAhcHmVPVWm1(2,2),cplAhcHmVWmVZ1(2,2),cplhhhhHmcHm1(2,2,2,2),cplHmHmcHmcHm1(2,2,2,2)

Complex(dp), Intent(out) :: Amp(2,2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,2
  Do gt2=1,2
    Do gt3=1,2
Amp(gt1, gt2, gt3) = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = MAh(gt1) 
Mex2 = MHm(gt2) 
Mex3 = MHm(gt3) 


! {conj[Hm], conj[Hm], VP}
Do i1=1,2
  Do i2=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
ML3 = MVP 
coup1 = cplAhHmcHm(gt1,i2,i1)
coup2 = cplHmcHmVP(i1,gt2)
coup3 = cplHmcHmVP(gt3,i2)
Call Amp_VERTEX_StoSS_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {conj[Hm], conj[VWm], VP}
Do i1=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
ML3 = MVP 
coup1 = -cplAhcHmVWm(gt1,i1)
coup2 = cplHmcHmVP(i1,gt2)
coup3 = cplHmcVWmVP(gt3)
Call Amp_VERTEX_StoSS_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
End Do


! {conj[VWm], conj[Hm], VP}
  Do i2=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
ML3 = MVP 
coup1 = -cplAhHmcVWm(gt1,i2)
coup2 = cplcHmVPVWm(gt2)
coup3 = cplHmcHmVP(gt3,i2)
Call Amp_VERTEX_StoSS_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do


! {VP, VWm}
ML1 = MVP 
ML2 = MVWm 
coup1 = cplAhHmcVWmVP1(gt1,gt3)
coup2 = cplcHmVPVWm(gt2)
Call Amp_VERTEX_StoSS_Topology3_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 



! {VP, conj[VWm]}
ML1 = MVP 
ML2 = MVWm 
coup1 = cplAhcHmVPVWm1(gt1,gt2)
coup2 = cplHmcVWmVP(gt3)
Call Amp_VERTEX_StoSS_Topology4_VV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(gt1, gt2, gt3) = Amp(gt1, gt2, gt3) + oo16pi2*(1)*AmpC 

    End Do
  End Do
End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_gumTHDMII_AhTocHmHm


Subroutine Amplitude_Tree_gumTHDMII_AhToHmcVWm(cplAhHmcVWm,MAh,MHm,MVWm,              & 
& MAh2,MHm2,MVWm2,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MHm(2),MVWm,MAh2(2),MHm2(2),MVWm2

Complex(dp), Intent(in) :: cplAhHmcVWm(2,2)

Complex(dp) :: Amp(2,2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 

Do gt1=1,2
  Do gt2=1,2
! External masses 
Mex1 = MAh(gt1) 
Mex2 = MHm(gt2) 
Mex3 = MVWm 
! Tree-Level Vertex 
coupT1 = cplAhHmcVWm(gt1,gt2)
Call TreeAmp_StoSV(Mex1,Mex2,Mex3,coupT1,AmpC) 
! Colour and symmetry factor 
Amp(:,gt1, gt2) = AmpC 
  End Do
End Do
End Subroutine Amplitude_Tree_gumTHDMII_AhToHmcVWm


Subroutine Gamma_Real_gumTHDMII_AhToHmcVWm(MLambda,em,gs,cplAhHmcVWm,MAh,             & 
& MHm,MVWm,GammarealPhoton,GammarealGluon)

Implicit None

Complex(dp), Intent(in) :: cplAhHmcVWm(2,2)

Real(dp), Intent(in) :: MAh(2),MHm(2),MVWm

Real(dp), Intent(in) :: MLambda, em, gs 

Real(dp), Intent(out) :: GammarealPhoton(2,2), GammarealGluon(2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 

Real(dp) :: Mloop1, Mloop2, Mloop3 
Complex(dp) :: Coup 
 
Do i1=2,2
  Do i2=2,2
Coup = cplAhHmcVWm(i1,i2)
Mex1 = MAh(i1)
Mex2 = MHm(i2)
Mex3 = MVWm
If (Abs(Mex1).gt.(Abs(Mex2)+Abs(Mex3))) Then 
 Call hardradiationSSV(Mex1,Mex2,Mex3,MLambda,em,0._dp,-1._dp,1._dp,Coup,Gammarealphoton(i1,i2),kont)
 GammarealGluon(i1,i2) = 0._dp 
Else 
  GammarealGluon(i1,i2) = 0._dp 
  GammarealPhoton(i1,i2) = 0._dp 

End if 
  End Do
End Do
End Subroutine Gamma_Real_gumTHDMII_AhToHmcVWm


Subroutine Amplitude_WAVE_gumTHDMII_AhToHmcVWm(cplAhHmcVWm,ctcplAhHmcVWm,             & 
& MAh,MAh2,MHm,MHm2,MVWm,MVWm2,ZfAh,ZfHm,ZfVWm,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MAh2(2),MHm(2),MHm2(2),MVWm,MVWm2

Complex(dp), Intent(in) :: cplAhHmcVWm(2,2)

Complex(dp), Intent(in) :: ctcplAhHmcVWm(2,2)

Complex(dp), Intent(in) :: ZfAh(2,2),ZfHm(2,2),ZfVWm

Complex(dp), Intent(out) :: Amp(2,2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

Do gt1=1,2
  Do gt2=1,2
! External masses 
Mex1 = MAh(gt1) 
Mex2 = MHm(gt2) 
Mex3 = MVWm 
!----------------------------- 
! Coupling counter term 
!----------------------------- 
ZcoupT1 = ctcplAhHmcVWm(gt1,gt2) 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
Do i1=1,2
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfAh(i1,gt1)*cplAhHmcVWm(i1,gt2)
End Do


! External Field 2 
Do i1=1,2
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfHm(i1,gt2)*cplAhHmcVWm(gt1,i1)
End Do


! External Field 3 
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfVWm*cplAhHmcVWm(gt1,gt2)


! Getting the amplitude 
Call TreeAmp_StoSV(Mex1,Mex2,Mex3,ZcoupT1,AmpC) 
Amp(:,gt1, gt2) = AmpC 
  End Do
End Do
End Subroutine Amplitude_WAVE_gumTHDMII_AhToHmcVWm


Subroutine Amplitude_VERTEX_gumTHDMII_AhToHmcVWm(MAh,MFd,MFe,MFu,Mhh,MHm,             & 
& MVP,MVWm,MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,        & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,               & 
& cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,    & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFdFuHmL,cplcFdFuHmR,       & 
& cplcFeFvHmL,cplcFeFvHmR,cplcgWmgAHm,cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgZgWpCHm,          & 
& cplcgWmgZHm,cplcgWpCgZcVWm,cplhhHmcHm,cplhhHmcVWm,cplhhcVWmVWm,cplHmcHmVP,             & 
& cplHmcVWmVP,cplHmcHmVZ,cplHmcVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplAhAhcVWmVWm1,          & 
& cplAhHmcVWmVP1,cplAhHmcVWmVZ1,cplhhHmcVWmVZ1,cplHmcHmcVWmVWm1,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MFd(3),MFe(3),MFu(3),Mhh(2),MHm(2),MVP,MVWm,MVZ,MAh2(2),MFd2(3),               & 
& MFe2(3),MFu2(3),Mhh2(2),MHm2(2),MVP2,MVWm2,MVZ2

Complex(dp), Intent(in) :: cplAhAhAh(2,2,2),cplAhAhhh(2,2,2),cplcFdFdAhL(3,3,2),cplcFdFdAhR(3,3,2),              & 
& cplcFeFeAhL(3,3,2),cplcFeFeAhR(3,3,2),cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),           & 
& cplcgWmgWmAh(2),cplcgWpCgWpCAh(2),cplAhhhhh(2,2,2),cplAhhhVZ(2,2),cplAhHmcHm(2,2,2),   & 
& cplAhHmcVWm(2,2),cplAhcHmVWm(2,2),cplcFuFdcVWmL(3,3),cplcFuFdcVWmR(3,3),               & 
& cplcFvFecVWmL(3,3),cplcFvFecVWmR(3,3),cplcFdFuHmL(3,3,2),cplcFdFuHmR(3,3,2),           & 
& cplcFeFvHmL(3,3,2),cplcFeFvHmR(3,3,2),cplcgWmgAHm(2),cplcgAgWmcVWm,cplcgZgWmcVWm,      & 
& cplcgZgWpCHm(2),cplcgWmgZHm(2),cplcgWpCgZcVWm,cplhhHmcHm(2,2,2),cplhhHmcVWm(2,2),      & 
& cplhhcVWmVWm(2),cplHmcHmVP(2,2),cplHmcVWmVP(2),cplHmcHmVZ(2,2),cplHmcVWmVZ(2),         & 
& cplcVWmVPVWm,cplcVWmVWmVZ,cplAhAhcVWmVWm1(2,2),cplAhHmcVWmVP1(2,2),cplAhHmcVWmVZ1(2,2),& 
& cplhhHmcVWmVZ1(2,2),cplHmcHmcVWmVWm1(2,2)

Complex(dp), Intent(out) :: Amp(2,2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,2
  Do gt2=1,2
Amp(:,gt1, gt2) = 0._dp 
! External masses 
Mex1 = MAh(gt1) 
Mex2 = MHm(gt2) 
Mex3 = MVWm 


! {Ah, Ah, conj[Hm]}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MAh(i1) 
ML2 = MAh(i2) 
ML3 = MHm(i3) 
coup1 = cplAhAhAh(gt1,i1,i2)
coup2 = cplAhHmcHm(i1,gt2,i3)
coup3 = -cplAhHmcVWm(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Ah, hh, conj[Hm]}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MAh(i1) 
ML2 = Mhh(i2) 
ML3 = MHm(i3) 
coup1 = cplAhAhhh(gt1,i1,i2)
coup2 = cplAhHmcHm(i1,gt2,i3)
coup3 = -cplhhHmcVWm(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Ah, hh, conj[VWm]}
Do i1=1,2
  Do i2=1,2
ML1 = MAh(i1) 
ML2 = Mhh(i2) 
ML3 = MVWm 
coup1 = cplAhAhhh(gt1,i1,i2)
coup2 = -cplAhHmcVWm(i1,gt2)
coup3 = cplhhcVWmVWm(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Fd, Fd, Fu}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFd(i1) 
ML2 = MFd(i2) 
ML3 = MFu(i3) 
coup1L = cplcFdFdAhL(i2,i1,gt1)
coup1R = cplcFdFdAhR(i2,i1,gt1)
coup2L = cplcFdFuHmL(i1,i3,gt2)
coup2R = cplcFdFuHmR(i1,i3,gt2)
coup3L = -cplcFuFdcVWmR(i3,i2)
coup3R = -cplcFuFdcVWmL(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(3)*AmpC 
    End Do
  End Do
End Do


! {Fe, Fe, Fv}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFe(i1) 
ML2 = MFe(i2) 
ML3 = 0._dp 
coup1L = cplcFeFeAhL(i2,i1,gt1)
coup1R = cplcFeFeAhR(i2,i1,gt1)
coup2L = cplcFeFvHmL(i1,i3,gt2)
coup2R = cplcFeFvHmR(i1,i3,gt2)
coup3L = -cplcFvFecVWmR(i3,i2)
coup3R = -cplcFvFecVWmL(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {gWm, gWm, gP}
ML1 = MVWm 
ML2 = MVWm 
ML3 = MVP 
coup1 = cplcgWmgWmAh(gt1)
coup2 = cplcgWmgAHm(gt2)
coup3 = cplcgAgWmcVWm
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 


! {gWm, gWm, gZ}
ML1 = MVWm 
ML2 = MVWm 
ML3 = MVZ 
coup1 = cplcgWmgWmAh(gt1)
coup2 = cplcgWmgZHm(gt2)
coup3 = cplcgZgWmcVWm
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 


! {hh, Ah, conj[Hm]}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = Mhh(i1) 
ML2 = MAh(i2) 
ML3 = MHm(i3) 
coup1 = cplAhAhhh(gt1,i2,i1)
coup2 = cplhhHmcHm(i1,gt2,i3)
coup3 = -cplAhHmcVWm(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {hh, hh, conj[Hm]}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = Mhh(i1) 
ML2 = Mhh(i2) 
ML3 = MHm(i3) 
coup1 = cplAhhhhh(gt1,i1,i2)
coup2 = cplhhHmcHm(i1,gt2,i3)
coup3 = -cplhhHmcVWm(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {hh, VZ, conj[Hm]}
Do i1=1,2
    Do i3=1,2
ML1 = Mhh(i1) 
ML2 = MVZ 
ML3 = MHm(i3) 
coup1 = -cplAhhhVZ(gt1,i1)
coup2 = cplhhHmcHm(i1,gt2,i3)
coup3 = cplHmcVWmVZ(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {hh, hh, conj[VWm]}
Do i1=1,2
  Do i2=1,2
ML1 = Mhh(i1) 
ML2 = Mhh(i2) 
ML3 = MVWm 
coup1 = cplAhhhhh(gt1,i1,i2)
coup2 = -cplhhHmcVWm(i1,gt2)
coup3 = cplhhcVWmVWm(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {hh, VZ, conj[VWm]}
Do i1=1,2
ML1 = Mhh(i1) 
ML2 = MVZ 
ML3 = MVWm 
coup1 = -cplAhhhVZ(gt1,i1)
coup2 = -cplhhHmcVWm(i1,gt2)
coup3 = -cplcVWmVWmVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {Hm, Hm, Ah}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
ML3 = MAh(i3) 
coup1 = cplAhHmcHm(gt1,i1,i2)
coup2 = cplAhHmcHm(i3,gt2,i1)
coup3 = cplAhHmcVWm(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Hm, Hm, hh}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
ML3 = Mhh(i3) 
coup1 = cplAhHmcHm(gt1,i1,i2)
coup2 = cplhhHmcHm(i3,gt2,i1)
coup3 = cplhhHmcVWm(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Hm, VWm, hh}
Do i1=1,2
    Do i3=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
ML3 = Mhh(i3) 
coup1 = -cplAhHmcVWm(gt1,i1)
coup2 = cplhhHmcHm(i3,gt2,i1)
coup3 = cplhhcVWmVWm(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hm, Hm, VP}
Do i1=1,2
  Do i2=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
ML3 = MVP 
coup1 = cplAhHmcHm(gt1,i1,i2)
coup2 = cplHmcHmVP(gt2,i1)
coup3 = cplHmcVWmVP(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Hm, VWm, VP}
Do i1=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
ML3 = MVP 
coup1 = -cplAhHmcVWm(gt1,i1)
coup2 = cplHmcHmVP(gt2,i1)
coup3 = -cplcVWmVPVWm
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {Hm, Hm, VZ}
Do i1=1,2
  Do i2=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
ML3 = MVZ 
coup1 = cplAhHmcHm(gt1,i1,i2)
coup2 = cplHmcHmVZ(gt2,i1)
coup3 = cplHmcVWmVZ(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Hm, VWm, VZ}
Do i1=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
ML3 = MVZ 
coup1 = -cplAhHmcVWm(gt1,i1)
coup2 = cplHmcHmVZ(gt2,i1)
coup3 = cplcVWmVWmVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {VWm, Hm, Ah}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
ML3 = MAh(i3) 
coup1 = -cplAhcHmVWm(gt1,i2)
coup2 = -cplAhHmcVWm(i3,gt2)
coup3 = cplAhHmcVWm(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VWm, Hm, hh}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
ML3 = Mhh(i3) 
coup1 = -cplAhcHmVWm(gt1,i2)
coup2 = -cplhhHmcVWm(i3,gt2)
coup3 = cplhhHmcVWm(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VWm, Hm, VP}
  Do i2=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
ML3 = MVP 
coup1 = -cplAhcHmVWm(gt1,i2)
coup2 = cplHmcVWmVP(gt2)
coup3 = cplHmcVWmVP(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do


! {VWm, Hm, VZ}
  Do i2=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
ML3 = MVZ 
coup1 = -cplAhcHmVWm(gt1,i2)
coup2 = cplHmcVWmVZ(gt2)
coup3 = cplHmcVWmVZ(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do


! {VZ, hh, conj[Hm]}
  Do i2=1,2
    Do i3=1,2
ML1 = MVZ 
ML2 = Mhh(i2) 
ML3 = MHm(i3) 
coup1 = -cplAhhhVZ(gt1,i2)
coup2 = cplHmcHmVZ(gt2,i3)
coup3 = -cplhhHmcVWm(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VZ, hh, conj[VWm]}
  Do i2=1,2
ML1 = MVZ 
ML2 = Mhh(i2) 
ML3 = MVWm 
coup1 = -cplAhhhVZ(gt1,i2)
coup2 = cplHmcVWmVZ(gt2)
coup3 = cplhhcVWmVWm(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do


! {bar[Fu], bar[Fu], bar[Fd]}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFu(i1) 
ML2 = MFu(i2) 
ML3 = MFd(i3) 
coup1L = cplcFuFuAhL(i1,i2,gt1)
coup1R = cplcFuFuAhR(i1,i2,gt1)
coup2L = cplcFdFuHmL(i3,i1,gt2)
coup2R = cplcFdFuHmR(i3,i1,gt2)
coup3L = cplcFuFdcVWmL(i2,i3)
coup3R = cplcFuFdcVWmR(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(3)*AmpC 
    End Do
  End Do
End Do


! {bar[gWmC], bar[gWmC], bar[gZ]}
ML1 = MVWm 
ML2 = MVWm 
ML3 = MVZ 
coup1 = cplcgWpCgWpCAh(gt1)
coup2 = cplcgZgWpCHm(gt2)
coup3 = cplcgWpCgZcVWm
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 


! {hh, VZ}
Do i1=1,2
ML1 = Mhh(i1) 
ML2 = MVZ 
coup1 = cplAhhhVZ(gt1,i1)
coup2 = cplhhHmcVWmVZ1(i1,gt2)
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {Hm, VWm}
Do i1=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
coup1 = cplAhHmcVWm(gt1,i1)
coup2 = cplHmcHmcVWmVWm1(gt2,i1)
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {Ah, conj[VWm]}
Do i1=1,2
ML1 = MAh(i1) 
ML2 = MVWm 
coup1 = cplAhAhcVWmVWm1(gt1,i1)
coup2 = -cplAhHmcVWm(i1,gt2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 

End Do


! {Hm, VP}
Do i1=1,2
ML1 = MHm(i1) 
ML2 = MVP 
coup1 = cplAhHmcVWmVP1(gt1,i1)
coup2 = cplHmcHmVP(gt2,i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 

End Do


! {Hm, VZ}
Do i1=1,2
ML1 = MHm(i1) 
ML2 = MVZ 
coup1 = cplAhHmcVWmVZ1(gt1,i1)
coup2 = cplHmcHmVZ(gt2,i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 

End Do
  End Do
End Do
End Subroutine Amplitude_VERTEX_gumTHDMII_AhToHmcVWm


Subroutine Amplitude_IR_VERTEX_gumTHDMII_AhToHmcVWm(MAh,MFd,MFe,MFu,Mhh,              & 
& MHm,MVP,MVWm,MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhAh,              & 
& cplAhAhhh,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,     & 
& cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,    & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFdFuHmL,cplcFdFuHmR,       & 
& cplcFeFvHmL,cplcFeFvHmR,cplcgWmgAHm,cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgZgWpCHm,          & 
& cplcgWmgZHm,cplcgWpCgZcVWm,cplhhHmcHm,cplhhHmcVWm,cplhhcVWmVWm,cplHmcHmVP,             & 
& cplHmcVWmVP,cplHmcHmVZ,cplHmcVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplAhAhcVWmVWm1,          & 
& cplAhHmcVWmVP1,cplAhHmcVWmVZ1,cplhhHmcVWmVZ1,cplHmcHmcVWmVWm1,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MFd(3),MFe(3),MFu(3),Mhh(2),MHm(2),MVP,MVWm,MVZ,MAh2(2),MFd2(3),               & 
& MFe2(3),MFu2(3),Mhh2(2),MHm2(2),MVP2,MVWm2,MVZ2

Complex(dp), Intent(in) :: cplAhAhAh(2,2,2),cplAhAhhh(2,2,2),cplcFdFdAhL(3,3,2),cplcFdFdAhR(3,3,2),              & 
& cplcFeFeAhL(3,3,2),cplcFeFeAhR(3,3,2),cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),           & 
& cplcgWmgWmAh(2),cplcgWpCgWpCAh(2),cplAhhhhh(2,2,2),cplAhhhVZ(2,2),cplAhHmcHm(2,2,2),   & 
& cplAhHmcVWm(2,2),cplAhcHmVWm(2,2),cplcFuFdcVWmL(3,3),cplcFuFdcVWmR(3,3),               & 
& cplcFvFecVWmL(3,3),cplcFvFecVWmR(3,3),cplcFdFuHmL(3,3,2),cplcFdFuHmR(3,3,2),           & 
& cplcFeFvHmL(3,3,2),cplcFeFvHmR(3,3,2),cplcgWmgAHm(2),cplcgAgWmcVWm,cplcgZgWmcVWm,      & 
& cplcgZgWpCHm(2),cplcgWmgZHm(2),cplcgWpCgZcVWm,cplhhHmcHm(2,2,2),cplhhHmcVWm(2,2),      & 
& cplhhcVWmVWm(2),cplHmcHmVP(2,2),cplHmcVWmVP(2),cplHmcHmVZ(2,2),cplHmcVWmVZ(2),         & 
& cplcVWmVPVWm,cplcVWmVWmVZ,cplAhAhcVWmVWm1(2,2),cplAhHmcVWmVP1(2,2),cplAhHmcVWmVZ1(2,2),& 
& cplhhHmcVWmVZ1(2,2),cplHmcHmcVWmVWm1(2,2)

Complex(dp), Intent(out) :: Amp(2,2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,2
  Do gt2=1,2
Amp(:,gt1, gt2) = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = MAh(gt1) 
Mex2 = MHm(gt2) 
Mex3 = MVWm 


! {Hm, Hm, VP}
Do i1=1,2
  Do i2=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
ML3 = MVP 
coup1 = cplAhHmcHm(gt1,i1,i2)
coup2 = cplHmcHmVP(gt2,i1)
coup3 = cplHmcVWmVP(i2)
Call Amp_VERTEX_StoSV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Hm, VWm, VP}
Do i1=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
ML3 = MVP 
coup1 = -cplAhHmcVWm(gt1,i1)
coup2 = cplHmcHmVP(gt2,i1)
coup3 = -cplcVWmVPVWm
Call Amp_VERTEX_StoSV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {VWm, Hm, VP}
  Do i2=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
ML3 = MVP 
coup1 = -cplAhcHmVWm(gt1,i2)
coup2 = cplHmcVWmVP(gt2)
coup3 = cplHmcVWmVP(i2)
Call Amp_VERTEX_StoSV_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do


! {Hm, VP}
Do i1=1,2
ML1 = MHm(i1) 
ML2 = MVP 
coup1 = cplAhHmcVWmVP1(gt1,i1)
coup2 = cplHmcHmVP(gt2,i1)
Call Amp_VERTEX_StoSV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 

End Do
  End Do
End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_gumTHDMII_AhToHmcVWm


Subroutine Amplitude_WAVE_gumTHDMII_AhToAhVP(MAh,MAh2,MVP,MVP2,ZfAh,ZfVP,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MAh2(2),MVP,MVP2

Complex(dp), Intent(in) :: ZfAh(2,2),ZfVP

Complex(dp), Intent(out) :: Amp(2,2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

Do gt1=1,2
  Do gt2=1,2
! External masses 
Mex1 = MAh(gt1) 
Mex2 = MAh(gt2) 
Mex3 = MVP 
ZcoupT1 = 0._dp 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
! Vanishing 


! External Field 2 
! Vanishing 


! External Field 3 
Amp(:,gt1, gt2) = 0._dp
  End Do
End Do
End Subroutine Amplitude_WAVE_gumTHDMII_AhToAhVP


Subroutine Amplitude_VERTEX_gumTHDMII_AhToAhVP(MAh,MFd,MFe,MFu,MHm,MVP,               & 
& MVWm,MAh2,MFd2,MFe2,MFu2,MHm2,MVP2,MVWm2,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,          & 
& cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhHmcHm,            & 
& cplAhHmcVWm,cplAhcHmVWm,cplcFdFdVPL,cplcFdFdVPR,cplcFeFeVPL,cplcFeFeVPR,               & 
& cplcFuFuVPL,cplcFuFuVPR,cplcgWmgWmVP,cplcgWpCgWpCVP,cplHmcHmVP,cplHmcVWmVP,            & 
& cplcHmVPVWm,cplcVWmVPVWm,cplAhHmcVWmVP1,cplAhcHmVPVWm1,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MFd(3),MFe(3),MFu(3),MHm(2),MVP,MVWm,MAh2(2),MFd2(3),MFe2(3),MFu2(3),          & 
& MHm2(2),MVP2,MVWm2

Complex(dp), Intent(in) :: cplcFdFdAhL(3,3,2),cplcFdFdAhR(3,3,2),cplcFeFeAhL(3,3,2),cplcFeFeAhR(3,3,2),          & 
& cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),cplcgWmgWmAh(2),cplcgWpCgWpCAh(2),               & 
& cplAhHmcHm(2,2,2),cplAhHmcVWm(2,2),cplAhcHmVWm(2,2),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3), & 
& cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcgWmgWmVP,      & 
& cplcgWpCgWpCVP,cplHmcHmVP(2,2),cplHmcVWmVP(2),cplcHmVPVWm(2),cplcVWmVPVWm,             & 
& cplAhHmcVWmVP1(2,2),cplAhcHmVPVWm1(2,2)

Complex(dp), Intent(out) :: Amp(2,2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,2
  Do gt2=1,2
Amp(:,gt1, gt2) = 0._dp 
! External masses 
Mex1 = MAh(gt1) 
Mex2 = MAh(gt2) 
Mex3 = MVP 


! {Fd, Fd, Fd}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFd(i1) 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFdFdAhL(i2,i1,gt1)
coup1R = cplcFdFdAhR(i2,i1,gt1)
coup2L = cplcFdFdAhL(i1,i3,gt2)
coup2R = cplcFdFdAhR(i1,i3,gt2)
coup3L = -cplcFdFdVPR(i3,i2)
coup3R = -cplcFdFdVPL(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(6)*AmpC 
    End Do
  End Do
End Do


! {Fe, Fe, Fe}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFe(i1) 
ML2 = MFe(i2) 
ML3 = MFe(i3) 
coup1L = cplcFeFeAhL(i2,i1,gt1)
coup1R = cplcFeFeAhR(i2,i1,gt1)
coup2L = cplcFeFeAhL(i1,i3,gt2)
coup2R = cplcFeFeAhR(i1,i3,gt2)
coup3L = -cplcFeFeVPR(i3,i2)
coup3R = -cplcFeFeVPL(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(2)*AmpC 
    End Do
  End Do
End Do


! {Fu, Fu, Fu}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFu(i1) 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = cplcFuFuAhL(i2,i1,gt1)
coup1R = cplcFuFuAhR(i2,i1,gt1)
coup2L = cplcFuFuAhL(i1,i3,gt2)
coup2R = cplcFuFuAhR(i1,i3,gt2)
coup3L = -cplcFuFuVPR(i3,i2)
coup3R = -cplcFuFuVPL(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(6)*AmpC 
    End Do
  End Do
End Do


! {gWm, gWm, gWm}
ML1 = MVWm 
ML2 = MVWm 
ML3 = MVWm 
coup1 = cplcgWmgWmAh(gt1)
coup2 = cplcgWmgWmAh(gt2)
coup3 = cplcgWmgWmVP
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(2)*AmpC 


! {gWmC, gWmC, gWmC}
ML1 = MVWm 
ML2 = MVWm 
ML3 = MVWm 
coup1 = cplcgWpCgWpCAh(gt1)
coup2 = cplcgWpCgWpCAh(gt2)
coup3 = cplcgWpCgWpCVP
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(2)*AmpC 


! {Hm, Hm, Hm}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
ML3 = MHm(i3) 
coup1 = cplAhHmcHm(gt1,i1,i2)
coup2 = cplAhHmcHm(gt2,i3,i1)
coup3 = -cplHmcHmVP(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(2)*AmpC 
    End Do
  End Do
End Do


! {Hm, VWm, Hm}
Do i1=1,2
    Do i3=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
ML3 = MHm(i3) 
coup1 = -cplAhHmcVWm(gt1,i1)
coup2 = cplAhHmcHm(gt2,i3,i1)
coup3 = cplcHmVPVWm(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hm, Hm, VWm}
Do i1=1,2
  Do i2=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
ML3 = MVWm 
coup1 = cplAhHmcHm(gt1,i1,i2)
coup2 = cplAhcHmVWm(gt2,i1)
coup3 = cplHmcVWmVP(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Hm, VWm, VWm}
Do i1=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
ML3 = MVWm 
coup1 = -cplAhHmcVWm(gt1,i1)
coup2 = cplAhcHmVWm(gt2,i1)
coup3 = cplcVWmVPVWm
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {VWm, Hm, Hm}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
ML3 = MHm(i3) 
coup1 = -cplAhcHmVWm(gt1,i2)
coup2 = cplAhHmcVWm(gt2,i3)
coup3 = -cplHmcHmVP(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {conj[Hm], conj[VWm], conj[Hm]}
Do i1=1,2
    Do i3=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
ML3 = MHm(i3) 
coup1 = -cplAhcHmVWm(gt1,i1)
coup2 = cplAhHmcHm(gt2,i1,i3)
coup3 = cplHmcVWmVP(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {conj[Hm], conj[Hm], conj[VWm]}
Do i1=1,2
  Do i2=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
ML3 = MVWm 
coup1 = cplAhHmcHm(gt1,i2,i1)
coup2 = cplAhHmcVWm(gt2,i1)
coup3 = cplcHmVPVWm(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {conj[Hm], conj[VWm], conj[VWm]}
Do i1=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
ML3 = MVWm 
coup1 = -cplAhcHmVWm(gt1,i1)
coup2 = cplAhHmcVWm(gt2,i1)
coup3 = -cplcVWmVPVWm
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {conj[VWm], conj[Hm], conj[Hm]}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
ML3 = MHm(i3) 
coup1 = -cplAhHmcVWm(gt1,i2)
coup2 = cplAhcHmVWm(gt2,i3)
coup3 = cplHmcHmVP(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {Hm, VWm}
Do i1=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
coup1 = cplAhHmcVWm(gt1,i1)
coup2 = cplAhcHmVPVWm1(gt2,i1)
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {VWm, Hm}
  Do i2=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
coup1 = cplAhcHmVWm(gt1,i2)
coup2 = cplAhHmcVWmVP1(gt2,i2)
Call Amp_VERTEX_StoSV_Topology2_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do


! {Hm, VWm}
Do i1=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
coup1 = cplAhHmcVWmVP1(gt1,i1)
coup2 = cplAhcHmVWm(gt2,i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 

End Do


! {VWm, Hm}
  Do i2=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
coup1 = cplAhcHmVPVWm1(gt1,i2)
coup2 = cplAhHmcVWm(gt2,i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 

  End Do
  End Do
End Do
End Subroutine Amplitude_VERTEX_gumTHDMII_AhToAhVP


Subroutine Amplitude_IR_VERTEX_gumTHDMII_AhToAhVP(MAh,MFd,MFe,MFu,MHm,MVP,            & 
& MVWm,MAh2,MFd2,MFe2,MFu2,MHm2,MVP2,MVWm2,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,          & 
& cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhHmcHm,            & 
& cplAhHmcVWm,cplAhcHmVWm,cplcFdFdVPL,cplcFdFdVPR,cplcFeFeVPL,cplcFeFeVPR,               & 
& cplcFuFuVPL,cplcFuFuVPR,cplcgWmgWmVP,cplcgWpCgWpCVP,cplHmcHmVP,cplHmcVWmVP,            & 
& cplcHmVPVWm,cplcVWmVPVWm,cplAhHmcVWmVP1,cplAhcHmVPVWm1,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MFd(3),MFe(3),MFu(3),MHm(2),MVP,MVWm,MAh2(2),MFd2(3),MFe2(3),MFu2(3),          & 
& MHm2(2),MVP2,MVWm2

Complex(dp), Intent(in) :: cplcFdFdAhL(3,3,2),cplcFdFdAhR(3,3,2),cplcFeFeAhL(3,3,2),cplcFeFeAhR(3,3,2),          & 
& cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),cplcgWmgWmAh(2),cplcgWpCgWpCAh(2),               & 
& cplAhHmcHm(2,2,2),cplAhHmcVWm(2,2),cplAhcHmVWm(2,2),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3), & 
& cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcgWmgWmVP,      & 
& cplcgWpCgWpCVP,cplHmcHmVP(2,2),cplHmcVWmVP(2),cplcHmVPVWm(2),cplcVWmVPVWm,             & 
& cplAhHmcVWmVP1(2,2),cplAhcHmVPVWm1(2,2)

Complex(dp), Intent(out) :: Amp(2,2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,2
  Do gt2=1,2
Amp(:,gt1, gt2) = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = MAh(gt1) 
Mex2 = MAh(gt2) 
Mex3 = MVP 
  End Do
End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_gumTHDMII_AhToAhVP


Subroutine Amplitude_WAVE_gumTHDMII_AhToAhVZ(MAh,MAh2,MVZ,MVZ2,ZfAh,ZfVZ,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MAh2(2),MVZ,MVZ2

Complex(dp), Intent(in) :: ZfAh(2,2),ZfVZ

Complex(dp), Intent(out) :: Amp(2,2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

Do gt1=1,2
  Do gt2=1,2
! External masses 
Mex1 = MAh(gt1) 
Mex2 = MAh(gt2) 
Mex3 = MVZ 
ZcoupT1 = 0._dp 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
! Vanishing 


! External Field 2 
! Vanishing 


! External Field 3 
Amp(:,gt1, gt2) = 0._dp
  End Do
End Do
End Subroutine Amplitude_WAVE_gumTHDMII_AhToAhVZ


Subroutine Amplitude_VERTEX_gumTHDMII_AhToAhVZ(MAh,MFd,MFe,MFu,Mhh,MHm,               & 
& MVWm,MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,     & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdVZL,     & 
& cplcFdFdVZR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmVZ,              & 
& cplcgWpCgWpCVZ,cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVWmVZ,cplcVWmVWmVZ,              & 
& cplAhHmcVWmVZ1,cplAhcHmVWmVZ1,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MFd(3),MFe(3),MFu(3),Mhh(2),MHm(2),MVWm,MVZ,MAh2(2),MFd2(3),MFe2(3),           & 
& MFu2(3),Mhh2(2),MHm2(2),MVWm2,MVZ2

Complex(dp), Intent(in) :: cplAhAhAh(2,2,2),cplAhAhhh(2,2,2),cplcFdFdAhL(3,3,2),cplcFdFdAhR(3,3,2),              & 
& cplcFeFeAhL(3,3,2),cplcFeFeAhR(3,3,2),cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),           & 
& cplcgWmgWmAh(2),cplcgWpCgWpCAh(2),cplAhhhhh(2,2,2),cplAhhhVZ(2,2),cplAhHmcHm(2,2,2),   & 
& cplAhHmcVWm(2,2),cplAhcHmVWm(2,2),cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFeFeVZL(3,3),  & 
& cplcFeFeVZR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplcgWmgWmVZ,cplcgWpCgWpCVZ,        & 
& cplhhVZVZ(2),cplHmcHmVZ(2,2),cplHmcVWmVZ(2),cplcHmVWmVZ(2),cplcVWmVWmVZ,               & 
& cplAhHmcVWmVZ1(2,2),cplAhcHmVWmVZ1(2,2)

Complex(dp), Intent(out) :: Amp(2,2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,2
  Do gt2=1,2
Amp(:,gt1, gt2) = 0._dp 
! External masses 
Mex1 = MAh(gt1) 
Mex2 = MAh(gt2) 
Mex3 = MVZ 


! {Ah, hh, Ah}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MAh(i1) 
ML2 = Mhh(i2) 
ML3 = MAh(i3) 
coup1 = cplAhAhhh(gt1,i1,i2)
coup2 = cplAhAhAh(gt2,i1,i3)
coup3 = cplAhhhVZ(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Ah, Ah, hh}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MAh(i1) 
ML2 = MAh(i2) 
ML3 = Mhh(i3) 
coup1 = cplAhAhAh(gt1,i1,i2)
coup2 = cplAhAhhh(gt2,i1,i3)
coup3 = -cplAhhhVZ(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Fd, Fd, Fd}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFd(i1) 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFdFdAhL(i2,i1,gt1)
coup1R = cplcFdFdAhR(i2,i1,gt1)
coup2L = cplcFdFdAhL(i1,i3,gt2)
coup2R = cplcFdFdAhR(i1,i3,gt2)
coup3L = -cplcFdFdVZR(i3,i2)
coup3R = -cplcFdFdVZL(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(6)*AmpC 
    End Do
  End Do
End Do


! {Fe, Fe, Fe}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFe(i1) 
ML2 = MFe(i2) 
ML3 = MFe(i3) 
coup1L = cplcFeFeAhL(i2,i1,gt1)
coup1R = cplcFeFeAhR(i2,i1,gt1)
coup2L = cplcFeFeAhL(i1,i3,gt2)
coup2R = cplcFeFeAhR(i1,i3,gt2)
coup3L = -cplcFeFeVZR(i3,i2)
coup3R = -cplcFeFeVZL(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(2)*AmpC 
    End Do
  End Do
End Do


! {Fu, Fu, Fu}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFu(i1) 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = cplcFuFuAhL(i2,i1,gt1)
coup1R = cplcFuFuAhR(i2,i1,gt1)
coup2L = cplcFuFuAhL(i1,i3,gt2)
coup2R = cplcFuFuAhR(i1,i3,gt2)
coup3L = -cplcFuFuVZR(i3,i2)
coup3R = -cplcFuFuVZL(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(6)*AmpC 
    End Do
  End Do
End Do


! {gWm, gWm, gWm}
ML1 = MVWm 
ML2 = MVWm 
ML3 = MVWm 
coup1 = cplcgWmgWmAh(gt1)
coup2 = cplcgWmgWmAh(gt2)
coup3 = cplcgWmgWmVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(2)*AmpC 


! {gWmC, gWmC, gWmC}
ML1 = MVWm 
ML2 = MVWm 
ML3 = MVWm 
coup1 = cplcgWpCgWpCAh(gt1)
coup2 = cplcgWpCgWpCAh(gt2)
coup3 = cplcgWpCgWpCVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(2)*AmpC 


! {hh, hh, Ah}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = Mhh(i1) 
ML2 = Mhh(i2) 
ML3 = MAh(i3) 
coup1 = cplAhhhhh(gt1,i1,i2)
coup2 = cplAhAhhh(gt2,i3,i1)
coup3 = cplAhhhVZ(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {hh, Ah, hh}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = Mhh(i1) 
ML2 = MAh(i2) 
ML3 = Mhh(i3) 
coup1 = cplAhAhhh(gt1,i2,i1)
coup2 = cplAhhhhh(gt2,i1,i3)
coup3 = -cplAhhhVZ(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {hh, VZ, hh}
Do i1=1,2
    Do i3=1,2
ML1 = Mhh(i1) 
ML2 = MVZ 
ML3 = Mhh(i3) 
coup1 = -cplAhhhVZ(gt1,i1)
coup2 = cplAhhhhh(gt2,i1,i3)
coup3 = cplhhVZVZ(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {hh, hh, VZ}
Do i1=1,2
  Do i2=1,2
ML1 = Mhh(i1) 
ML2 = Mhh(i2) 
ML3 = MVZ 
coup1 = cplAhhhhh(gt1,i1,i2)
coup2 = cplAhhhVZ(gt2,i1)
coup3 = cplhhVZVZ(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Hm, Hm, Hm}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
ML3 = MHm(i3) 
coup1 = cplAhHmcHm(gt1,i1,i2)
coup2 = cplAhHmcHm(gt2,i3,i1)
coup3 = -cplHmcHmVZ(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(2)*AmpC 
    End Do
  End Do
End Do


! {Hm, VWm, Hm}
Do i1=1,2
    Do i3=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
ML3 = MHm(i3) 
coup1 = -cplAhHmcVWm(gt1,i1)
coup2 = cplAhHmcHm(gt2,i3,i1)
coup3 = cplcHmVWmVZ(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hm, Hm, VWm}
Do i1=1,2
  Do i2=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
ML3 = MVWm 
coup1 = cplAhHmcHm(gt1,i1,i2)
coup2 = cplAhcHmVWm(gt2,i1)
coup3 = cplHmcVWmVZ(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Hm, VWm, VWm}
Do i1=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
ML3 = MVWm 
coup1 = -cplAhHmcVWm(gt1,i1)
coup2 = cplAhcHmVWm(gt2,i1)
coup3 = -cplcVWmVWmVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {VWm, Hm, Hm}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
ML3 = MHm(i3) 
coup1 = -cplAhcHmVWm(gt1,i2)
coup2 = cplAhHmcVWm(gt2,i3)
coup3 = -cplHmcHmVZ(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {conj[Hm], conj[VWm], conj[Hm]}
Do i1=1,2
    Do i3=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
ML3 = MHm(i3) 
coup1 = -cplAhcHmVWm(gt1,i1)
coup2 = cplAhHmcHm(gt2,i1,i3)
coup3 = cplHmcVWmVZ(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {conj[Hm], conj[Hm], conj[VWm]}
Do i1=1,2
  Do i2=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
ML3 = MVWm 
coup1 = cplAhHmcHm(gt1,i2,i1)
coup2 = cplAhHmcVWm(gt2,i1)
coup3 = cplcHmVWmVZ(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {conj[Hm], conj[VWm], conj[VWm]}
Do i1=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
ML3 = MVWm 
coup1 = -cplAhcHmVWm(gt1,i1)
coup2 = cplAhHmcVWm(gt2,i1)
coup3 = cplcVWmVWmVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {conj[VWm], conj[Hm], conj[Hm]}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
ML3 = MHm(i3) 
coup1 = -cplAhHmcVWm(gt1,i2)
coup2 = cplAhcHmVWm(gt2,i3)
coup3 = cplHmcHmVZ(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {Hm, VWm}
Do i1=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
coup1 = cplAhHmcVWm(gt1,i1)
coup2 = cplAhcHmVWmVZ1(gt2,i1)
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {VWm, Hm}
  Do i2=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
coup1 = cplAhcHmVWm(gt1,i2)
coup2 = cplAhHmcVWmVZ1(gt2,i2)
Call Amp_VERTEX_StoSV_Topology2_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do


! {Hm, VWm}
Do i1=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
coup1 = cplAhHmcVWmVZ1(gt1,i1)
coup2 = cplAhcHmVWm(gt2,i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 

End Do


! {VWm, Hm}
  Do i2=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
coup1 = cplAhcHmVWmVZ1(gt1,i2)
coup2 = cplAhHmcVWm(gt2,i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 

  End Do
  End Do
End Do
End Subroutine Amplitude_VERTEX_gumTHDMII_AhToAhVZ


Subroutine Amplitude_IR_VERTEX_gumTHDMII_AhToAhVZ(MAh,MFd,MFe,MFu,Mhh,MHm,            & 
& MVWm,MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,cplcFdFdAhL,     & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdVZL,     & 
& cplcFdFdVZR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmVZ,              & 
& cplcgWpCgWpCVZ,cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVWmVZ,cplcVWmVWmVZ,              & 
& cplAhHmcVWmVZ1,cplAhcHmVWmVZ1,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MFd(3),MFe(3),MFu(3),Mhh(2),MHm(2),MVWm,MVZ,MAh2(2),MFd2(3),MFe2(3),           & 
& MFu2(3),Mhh2(2),MHm2(2),MVWm2,MVZ2

Complex(dp), Intent(in) :: cplAhAhAh(2,2,2),cplAhAhhh(2,2,2),cplcFdFdAhL(3,3,2),cplcFdFdAhR(3,3,2),              & 
& cplcFeFeAhL(3,3,2),cplcFeFeAhR(3,3,2),cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),           & 
& cplcgWmgWmAh(2),cplcgWpCgWpCAh(2),cplAhhhhh(2,2,2),cplAhhhVZ(2,2),cplAhHmcHm(2,2,2),   & 
& cplAhHmcVWm(2,2),cplAhcHmVWm(2,2),cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFeFeVZL(3,3),  & 
& cplcFeFeVZR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplcgWmgWmVZ,cplcgWpCgWpCVZ,        & 
& cplhhVZVZ(2),cplHmcHmVZ(2,2),cplHmcVWmVZ(2),cplcHmVWmVZ(2),cplcVWmVWmVZ,               & 
& cplAhHmcVWmVZ1(2,2),cplAhcHmVWmVZ1(2,2)

Complex(dp), Intent(out) :: Amp(2,2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,2
  Do gt2=1,2
Amp(:,gt1, gt2) = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = MAh(gt1) 
Mex2 = MAh(gt2) 
Mex3 = MVZ 
  End Do
End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_gumTHDMII_AhToAhVZ


Subroutine Amplitude_WAVE_gumTHDMII_AhToFvcFv(MAh,MAh2,ZfAh,ZfvL,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MAh2(2)

Complex(dp), Intent(in) :: ZfAh(2,2),ZfvL(3,3)

Complex(dp), Intent(out) :: Amp(2,2,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

Do gt1=1,2
  Do gt2=1,3
    Do gt3=1,3
! External masses 
Mex1 = MAh(gt1) 
Mex2 = 0._dp 
Mex3 = 0._dp 
ZcoupT1L = 0._dp 
ZcoupT1R = 0._dp 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
! Vanishing 


! External Field 2 
! Vanishing 


! External Field 3 
! Vanishing 
Amp(:,gt1, gt2, gt3) = 0._dp
    End Do
  End Do
End Do
End Subroutine Amplitude_WAVE_gumTHDMII_AhToFvcFv


Subroutine Amplitude_VERTEX_gumTHDMII_AhToFvcFv(MAh,MFe,MHm,MVWm,MAh2,MFe2,           & 
& MHm2,MVWm2,cplcFeFeAhL,cplcFeFeAhR,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFvFecHmL,    & 
& cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFeFvHmL,cplcFeFvHmR,cplcFeFvVWmL,         & 
& cplcFeFvVWmR,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MFe(3),MHm(2),MVWm,MAh2(2),MFe2(3),MHm2(2),MVWm2

Complex(dp), Intent(in) :: cplcFeFeAhL(3,3,2),cplcFeFeAhR(3,3,2),cplAhHmcHm(2,2,2),cplAhHmcVWm(2,2),             & 
& cplAhcHmVWm(2,2),cplcFvFecHmL(3,3,2),cplcFvFecHmR(3,3,2),cplcFvFecVWmL(3,3),           & 
& cplcFvFecVWmR(3,3),cplcFeFvHmL(3,3,2),cplcFeFvHmR(3,3,2),cplcFeFvVWmL(3,3),            & 
& cplcFeFvVWmR(3,3)

Complex(dp), Intent(out) :: Amp(2,2,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,2
  Do gt2=1,3
    Do gt3=1,3
Amp(:,gt1, gt2, gt3) = 0._dp 
! External masses 
Mex1 = MAh(gt1) 
Mex2 = 0._dp 
Mex3 = 0._dp 


! {Fe, Fe, Hm}
Do i1=1,3
  Do i2=1,3
    Do i3=1,2
ML1 = MFe(i1) 
ML2 = MFe(i2) 
ML3 = MHm(i3) 
coup1L = cplcFeFeAhL(i2,i1,gt1)
coup1R = cplcFeFeAhR(i2,i1,gt1)
coup2L = cplcFeFvHmL(i1,gt2,i3)
coup2R = cplcFeFvHmR(i1,gt2,i3)
coup3L = cplcFvFecHmL(gt3,i2,i3)
coup3R = cplcFvFecHmR(gt3,i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_FFS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Fe, Fe, VWm}
Do i1=1,3
  Do i2=1,3
ML1 = MFe(i1) 
ML2 = MFe(i2) 
ML3 = MVWm 
coup1L = cplcFeFeAhL(i2,i1,gt1)
coup1R = cplcFeFeAhR(i2,i1,gt1)
coup2L = -cplcFeFvVWmR(i1,gt2)
coup2R = -cplcFeFvVWmL(i1,gt2)
coup3L = -cplcFvFecVWmR(gt3,i2)
coup3R = -cplcFvFecVWmL(gt3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_FFV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {conj[Hm], conj[Hm], bar[Fe]}
Do i1=1,2
  Do i2=1,2
    Do i3=1,3
ML1 = MHm(i1) 
ML2 = MHm(i2) 
ML3 = MFe(i3) 
coup1 = cplAhHmcHm(gt1,i2,i1)
coup2L = cplcFeFvHmL(i3,gt2,i1)
coup2R = cplcFeFvHmR(i3,gt2,i1)
coup3L = cplcFvFecHmL(gt3,i3,i2)
coup3R = cplcFvFecHmR(gt3,i3,i2)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_SSF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {conj[Hm], conj[VWm], bar[Fe]}
Do i1=1,2
    Do i3=1,3
ML1 = MHm(i1) 
ML2 = MVWm 
ML3 = MFe(i3) 
coup1 = cplAhcHmVWm(gt1,i1)
coup2L = cplcFeFvHmL(i3,gt2,i1)
coup2R = cplcFeFvHmR(i3,gt2,i1)
coup3L = -cplcFvFecVWmR(gt3,i3)
coup3R = -cplcFvFecVWmL(gt3,i3)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_SVF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {conj[VWm], conj[Hm], bar[Fe]}
  Do i2=1,2
    Do i3=1,3
ML1 = MVWm 
ML2 = MHm(i2) 
ML3 = MFe(i3) 
coup1 = cplAhHmcVWm(gt1,i2)
coup2L = -cplcFeFvVWmR(i3,gt2)
coup2R = -cplcFeFvVWmL(i3,gt2)
coup3L = cplcFvFecHmL(gt3,i3,i2)
coup3R = cplcFvFecHmR(gt3,i3,i2)
If ((Abs(coup1))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoFF_Topology1_VSF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
    End Do
  End Do
End Do
End Subroutine Amplitude_VERTEX_gumTHDMII_AhToFvcFv


Subroutine Amplitude_IR_VERTEX_gumTHDMII_AhToFvcFv(MAh,MFe,MHm,MVWm,MAh2,             & 
& MFe2,MHm2,MVWm2,cplcFeFeAhL,cplcFeFeAhR,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,            & 
& cplcFvFecHmL,cplcFvFecHmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFeFvHmL,cplcFeFvHmR,         & 
& cplcFeFvVWmL,cplcFeFvVWmR,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MFe(3),MHm(2),MVWm,MAh2(2),MFe2(3),MHm2(2),MVWm2

Complex(dp), Intent(in) :: cplcFeFeAhL(3,3,2),cplcFeFeAhR(3,3,2),cplAhHmcHm(2,2,2),cplAhHmcVWm(2,2),             & 
& cplAhcHmVWm(2,2),cplcFvFecHmL(3,3,2),cplcFvFecHmR(3,3,2),cplcFvFecVWmL(3,3),           & 
& cplcFvFecVWmR(3,3),cplcFeFvHmL(3,3,2),cplcFeFvHmR(3,3,2),cplcFeFvVWmL(3,3),            & 
& cplcFeFvVWmR(3,3)

Complex(dp), Intent(out) :: Amp(2,2,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,2
  Do gt2=1,3
    Do gt3=1,3
Amp(:,gt1, gt2, gt3) = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = MAh(gt1) 
Mex2 = 0._dp 
Mex3 = 0._dp 
    End Do
  End Do
End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_gumTHDMII_AhToFvcFv


Subroutine Amplitude_WAVE_gumTHDMII_AhTohhVP(cplAhhhVZ,ctcplAhhhVZ,MAh,               & 
& MAh2,Mhh,Mhh2,MVP,MVP2,MVZ,MVZ2,ZfAh,Zfhh,ZfVP,ZfVZVP,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MAh2(2),Mhh(2),Mhh2(2),MVP,MVP2,MVZ,MVZ2

Complex(dp), Intent(in) :: cplAhhhVZ(2,2)

Complex(dp), Intent(in) :: ctcplAhhhVZ(2,2)

Complex(dp), Intent(in) :: ZfAh(2,2),Zfhh(2,2),ZfVP,ZfVZVP

Complex(dp), Intent(out) :: Amp(2,2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

Do gt1=1,2
  Do gt2=1,2
! External masses 
Mex1 = MAh(gt1) 
Mex2 = Mhh(gt2) 
Mex3 = MVP 
ZcoupT1 = 0._dp 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
! Vanishing 


! External Field 2 
! Vanishing 


! External Field 3 
ZcoupT1 = ZcoupT1 + 0.5_dp*ZfVZVP*cplAhhhVZ(gt1,gt2)


! Getting the amplitude 
Call TreeAmp_StoSV(Mex1,Mex2,Mex3,ZcoupT1,AmpC) 
Amp(:,gt1, gt2) = AmpC 
  End Do
End Do
End Subroutine Amplitude_WAVE_gumTHDMII_AhTohhVP


Subroutine Amplitude_VERTEX_gumTHDMII_AhTohhVP(MAh,MFd,MFe,MFu,Mhh,MHm,               & 
& MVP,MVWm,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,cplcFdFdAhL,cplcFdFdAhR,             & 
& cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,           & 
& cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,    & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplcFuFuVPL,cplcFuFuVPR,cplcgWmgWmhh,cplcgWmgWmVP,cplcgWpCgWpChh,cplcgWpCgWpCVP,       & 
& cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,cplHmcHmVP,cplHmcVWmVP,cplcHmVPVWm,    & 
& cplcVWmVPVWm,cplAhHmcVWmVP1,cplAhcHmVPVWm1,cplhhHmcVWmVP1,cplhhcHmVPVWm1,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MFd(3),MFe(3),MFu(3),Mhh(2),MHm(2),MVP,MVWm,MAh2(2),MFd2(3),MFe2(3),           & 
& MFu2(3),Mhh2(2),MHm2(2),MVP2,MVWm2

Complex(dp), Intent(in) :: cplcFdFdAhL(3,3,2),cplcFdFdAhR(3,3,2),cplcFeFeAhL(3,3,2),cplcFeFeAhR(3,3,2),          & 
& cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),cplcgWmgWmAh(2),cplcgWpCgWpCAh(2),               & 
& cplAhHmcHm(2,2,2),cplAhHmcVWm(2,2),cplAhcHmVWm(2,2),cplcFdFdhhL(3,3,2),cplcFdFdhhR(3,3,2),& 
& cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),cplcFeFehhL(3,3,2),cplcFeFehhR(3,3,2),               & 
& cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),cplcFuFuhhL(3,3,2),cplcFuFuhhR(3,3,2),               & 
& cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcgWmgWmhh(2),cplcgWmgWmVP,cplcgWpCgWpChh(2),      & 
& cplcgWpCgWpCVP,cplhhHmcHm(2,2,2),cplhhHmcVWm(2,2),cplhhcHmVWm(2,2),cplhhcVWmVWm(2),    & 
& cplHmcHmVP(2,2),cplHmcVWmVP(2),cplcHmVPVWm(2),cplcVWmVPVWm,cplAhHmcVWmVP1(2,2),        & 
& cplAhcHmVPVWm1(2,2),cplhhHmcVWmVP1(2,2),cplhhcHmVPVWm1(2,2)

Complex(dp), Intent(out) :: Amp(2,2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,2
  Do gt2=1,2
Amp(:,gt1, gt2) = 0._dp 
! External masses 
Mex1 = MAh(gt1) 
Mex2 = Mhh(gt2) 
Mex3 = MVP 


! {Fd, Fd, Fd}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFd(i1) 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFdFdAhL(i2,i1,gt1)
coup1R = cplcFdFdAhR(i2,i1,gt1)
coup2L = cplcFdFdhhL(i1,i3,gt2)
coup2R = cplcFdFdhhR(i1,i3,gt2)
coup3L = -cplcFdFdVPR(i3,i2)
coup3R = -cplcFdFdVPL(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(6)*AmpC 
    End Do
  End Do
End Do


! {Fe, Fe, Fe}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFe(i1) 
ML2 = MFe(i2) 
ML3 = MFe(i3) 
coup1L = cplcFeFeAhL(i2,i1,gt1)
coup1R = cplcFeFeAhR(i2,i1,gt1)
coup2L = cplcFeFehhL(i1,i3,gt2)
coup2R = cplcFeFehhR(i1,i3,gt2)
coup3L = -cplcFeFeVPR(i3,i2)
coup3R = -cplcFeFeVPL(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(2)*AmpC 
    End Do
  End Do
End Do


! {Fu, Fu, Fu}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFu(i1) 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = cplcFuFuAhL(i2,i1,gt1)
coup1R = cplcFuFuAhR(i2,i1,gt1)
coup2L = cplcFuFuhhL(i1,i3,gt2)
coup2R = cplcFuFuhhR(i1,i3,gt2)
coup3L = -cplcFuFuVPR(i3,i2)
coup3R = -cplcFuFuVPL(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(6)*AmpC 
    End Do
  End Do
End Do


! {gWm, gWm, gWm}
ML1 = MVWm 
ML2 = MVWm 
ML3 = MVWm 
coup1 = cplcgWmgWmAh(gt1)
coup2 = cplcgWmgWmhh(gt2)
coup3 = cplcgWmgWmVP
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(2)*AmpC 


! {gWmC, gWmC, gWmC}
ML1 = MVWm 
ML2 = MVWm 
ML3 = MVWm 
coup1 = cplcgWpCgWpCAh(gt1)
coup2 = cplcgWpCgWpChh(gt2)
coup3 = cplcgWpCgWpCVP
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(2)*AmpC 


! {Hm, Hm, Hm}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
ML3 = MHm(i3) 
coup1 = cplAhHmcHm(gt1,i1,i2)
coup2 = cplhhHmcHm(gt2,i3,i1)
coup3 = -cplHmcHmVP(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(2)*AmpC 
    End Do
  End Do
End Do


! {Hm, VWm, Hm}
Do i1=1,2
    Do i3=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
ML3 = MHm(i3) 
coup1 = -cplAhHmcVWm(gt1,i1)
coup2 = cplhhHmcHm(gt2,i3,i1)
coup3 = cplcHmVPVWm(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hm, Hm, VWm}
Do i1=1,2
  Do i2=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
ML3 = MVWm 
coup1 = cplAhHmcHm(gt1,i1,i2)
coup2 = cplhhcHmVWm(gt2,i1)
coup3 = cplHmcVWmVP(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Hm, VWm, VWm}
Do i1=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
ML3 = MVWm 
coup1 = -cplAhHmcVWm(gt1,i1)
coup2 = cplhhcHmVWm(gt2,i1)
coup3 = cplcVWmVPVWm
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {VWm, Hm, Hm}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
ML3 = MHm(i3) 
coup1 = -cplAhcHmVWm(gt1,i2)
coup2 = cplhhHmcVWm(gt2,i3)
coup3 = -cplHmcHmVP(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VWm, Hm, VWm}
  Do i2=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
ML3 = MVWm 
coup1 = -cplAhcHmVWm(gt1,i2)
coup2 = cplhhcVWmVWm(gt2)
coup3 = cplHmcVWmVP(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do


! {conj[Hm], conj[VWm], conj[Hm]}
Do i1=1,2
    Do i3=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
ML3 = MHm(i3) 
coup1 = -cplAhcHmVWm(gt1,i1)
coup2 = cplhhHmcHm(gt2,i1,i3)
coup3 = cplHmcVWmVP(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {conj[Hm], conj[Hm], conj[VWm]}
Do i1=1,2
  Do i2=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
ML3 = MVWm 
coup1 = cplAhHmcHm(gt1,i2,i1)
coup2 = cplhhHmcVWm(gt2,i1)
coup3 = cplcHmVPVWm(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {conj[Hm], conj[VWm], conj[VWm]}
Do i1=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
ML3 = MVWm 
coup1 = -cplAhcHmVWm(gt1,i1)
coup2 = cplhhHmcVWm(gt2,i1)
coup3 = -cplcVWmVPVWm
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {conj[VWm], conj[Hm], conj[Hm]}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
ML3 = MHm(i3) 
coup1 = -cplAhHmcVWm(gt1,i2)
coup2 = cplhhcHmVWm(gt2,i3)
coup3 = cplHmcHmVP(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {conj[VWm], conj[Hm], conj[VWm]}
  Do i2=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
ML3 = MVWm 
coup1 = -cplAhHmcVWm(gt1,i2)
coup2 = cplhhcVWmVWm(gt2)
coup3 = cplcHmVPVWm(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do


! {Hm, VWm}
Do i1=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
coup1 = cplAhHmcVWm(gt1,i1)
coup2 = cplhhcHmVPVWm1(gt2,i1)
Call Amp_VERTEX_StoSV_Topology2_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {VWm, Hm}
  Do i2=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
coup1 = cplAhcHmVWm(gt1,i2)
coup2 = cplhhHmcVWmVP1(gt2,i2)
Call Amp_VERTEX_StoSV_Topology2_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do


! {Hm, VWm}
Do i1=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
coup1 = cplAhHmcVWmVP1(gt1,i1)
coup2 = cplhhcHmVWm(gt2,i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 

End Do


! {VWm, Hm}
  Do i2=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
coup1 = cplAhcHmVPVWm1(gt1,i2)
coup2 = cplhhHmcVWm(gt2,i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoSV_Topology3_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 

  End Do
  End Do
End Do
End Subroutine Amplitude_VERTEX_gumTHDMII_AhTohhVP


Subroutine Amplitude_IR_VERTEX_gumTHDMII_AhTohhVP(MAh,MFd,MFe,MFu,Mhh,MHm,            & 
& MVP,MVWm,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,cplcFdFdAhL,cplcFdFdAhR,             & 
& cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,           & 
& cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,    & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplcFuFuVPL,cplcFuFuVPR,cplcgWmgWmhh,cplcgWmgWmVP,cplcgWpCgWpChh,cplcgWpCgWpCVP,       & 
& cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,cplHmcHmVP,cplHmcVWmVP,cplcHmVPVWm,    & 
& cplcVWmVPVWm,cplAhHmcVWmVP1,cplAhcHmVPVWm1,cplhhHmcVWmVP1,cplhhcHmVPVWm1,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MFd(3),MFe(3),MFu(3),Mhh(2),MHm(2),MVP,MVWm,MAh2(2),MFd2(3),MFe2(3),           & 
& MFu2(3),Mhh2(2),MHm2(2),MVP2,MVWm2

Complex(dp), Intent(in) :: cplcFdFdAhL(3,3,2),cplcFdFdAhR(3,3,2),cplcFeFeAhL(3,3,2),cplcFeFeAhR(3,3,2),          & 
& cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),cplcgWmgWmAh(2),cplcgWpCgWpCAh(2),               & 
& cplAhHmcHm(2,2,2),cplAhHmcVWm(2,2),cplAhcHmVWm(2,2),cplcFdFdhhL(3,3,2),cplcFdFdhhR(3,3,2),& 
& cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),cplcFeFehhL(3,3,2),cplcFeFehhR(3,3,2),               & 
& cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),cplcFuFuhhL(3,3,2),cplcFuFuhhR(3,3,2),               & 
& cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcgWmgWmhh(2),cplcgWmgWmVP,cplcgWpCgWpChh(2),      & 
& cplcgWpCgWpCVP,cplhhHmcHm(2,2,2),cplhhHmcVWm(2,2),cplhhcHmVWm(2,2),cplhhcVWmVWm(2),    & 
& cplHmcHmVP(2,2),cplHmcVWmVP(2),cplcHmVPVWm(2),cplcVWmVPVWm,cplAhHmcVWmVP1(2,2),        & 
& cplAhcHmVPVWm1(2,2),cplhhHmcVWmVP1(2,2),cplhhcHmVPVWm1(2,2)

Complex(dp), Intent(out) :: Amp(2,2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,2
  Do gt2=1,2
Amp(:,gt1, gt2) = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = MAh(gt1) 
Mex2 = Mhh(gt2) 
Mex3 = MVP 
  End Do
End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_gumTHDMII_AhTohhVP


Subroutine Amplitude_WAVE_gumTHDMII_AhToVGVG(MAh,MAh2,MVG,MVG2,ZfAh,ZfVG,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MAh2(2),MVG,MVG2

Complex(dp), Intent(in) :: ZfAh(2,2),ZfVG

Complex(dp), Intent(out) :: Amp(2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

Do gt1=1,2
! External masses 
Mex1 = MAh(gt1) 
Mex2 = MVG 
Mex3 = MVG 
ZcoupT1 = 0._dp 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
! Vanishing 


! External Field 2 
! Vanishing 


! External Field 3 
Amp(:,gt1) = 0._dp
End Do
End Subroutine Amplitude_WAVE_gumTHDMII_AhToVGVG


Subroutine Amplitude_VERTEX_gumTHDMII_AhToVGVG(MAh,MFd,MFu,MVG,MAh2,MFd2,             & 
& MFu2,MVG2,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,cplcFdFdVGL,cplcFdFdVGR,     & 
& cplcFuFuVGL,cplcFuFuVGR,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MFd(3),MFu(3),MVG,MAh2(2),MFd2(3),MFu2(3),MVG2

Complex(dp), Intent(in) :: cplcFdFdAhL(3,3,2),cplcFdFdAhR(3,3,2),cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),          & 
& cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),cplcFuFuVGL(3,3),cplcFuFuVGR(3,3)

Complex(dp), Intent(out) :: Amp(2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,2
Amp(:,gt1) = 0._dp 
! External masses 
Mex1 = MAh(gt1) 
Mex2 = MVG 
Mex3 = MVG 


! {Fd, Fd, Fd}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFd(i1) 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFdFdAhL(i2,i1,gt1)
coup1R = cplcFdFdAhR(i2,i1,gt1)
coup2L = -cplcFdFdVGR(i1,i3)
coup2R = -cplcFdFdVGL(i1,i3)
coup3L = -cplcFdFdVGR(i3,i2)
coup3R = -cplcFdFdVGL(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Fu, Fu, Fu}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFu(i1) 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = cplcFuFuAhL(i2,i1,gt1)
coup1R = cplcFuFuAhR(i2,i1,gt1)
coup2L = -cplcFuFuVGR(i1,i3)
coup2R = -cplcFuFuVGL(i1,i3)
coup3L = -cplcFuFuVGR(i3,i2)
coup3R = -cplcFuFuVGL(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do
End Do
End Subroutine Amplitude_VERTEX_gumTHDMII_AhToVGVG


Subroutine Amplitude_IR_VERTEX_gumTHDMII_AhToVGVG(MAh,MFd,MFu,MVG,MAh2,               & 
& MFd2,MFu2,MVG2,cplcFdFdAhL,cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,cplcFdFdVGL,            & 
& cplcFdFdVGR,cplcFuFuVGL,cplcFuFuVGR,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MFd(3),MFu(3),MVG,MAh2(2),MFd2(3),MFu2(3),MVG2

Complex(dp), Intent(in) :: cplcFdFdAhL(3,3,2),cplcFdFdAhR(3,3,2),cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),          & 
& cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),cplcFuFuVGL(3,3),cplcFuFuVGR(3,3)

Complex(dp), Intent(out) :: Amp(2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,2
Amp(:,gt1) = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = MAh(gt1) 
Mex2 = MVG 
Mex3 = MVG 
End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_gumTHDMII_AhToVGVG


Subroutine Amplitude_WAVE_gumTHDMII_AhToVPVP(MAh,MAh2,MVP,MVP2,ZfAh,ZfVP,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MAh2(2),MVP,MVP2

Complex(dp), Intent(in) :: ZfAh(2,2),ZfVP

Complex(dp), Intent(out) :: Amp(2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

Do gt1=1,2
! External masses 
Mex1 = MAh(gt1) 
Mex2 = MVP 
Mex3 = MVP 
ZcoupT1 = 0._dp 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
! Vanishing 


! External Field 2 
! Vanishing 


! External Field 3 
Amp(:,gt1) = 0._dp
End Do
End Subroutine Amplitude_WAVE_gumTHDMII_AhToVPVP


Subroutine Amplitude_VERTEX_gumTHDMII_AhToVPVP(MAh,MFd,MFe,MFu,MHm,MVP,               & 
& MVWm,MAh2,MFd2,MFe2,MFu2,MHm2,MVP2,MVWm2,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,          & 
& cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhHmcHm,            & 
& cplAhHmcVWm,cplAhcHmVWm,cplcFdFdVPL,cplcFdFdVPR,cplcFeFeVPL,cplcFeFeVPR,               & 
& cplcFuFuVPL,cplcFuFuVPR,cplcgWmgWmVP,cplcgWpCgWpCVP,cplHmcHmVP,cplHmcVWmVP,            & 
& cplcHmVPVWm,cplcVWmVPVWm,cplAhHmcVWmVP1,cplAhcHmVPVWm1,cplHmcHmVPVP1,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MFd(3),MFe(3),MFu(3),MHm(2),MVP,MVWm,MAh2(2),MFd2(3),MFe2(3),MFu2(3),          & 
& MHm2(2),MVP2,MVWm2

Complex(dp), Intent(in) :: cplcFdFdAhL(3,3,2),cplcFdFdAhR(3,3,2),cplcFeFeAhL(3,3,2),cplcFeFeAhR(3,3,2),          & 
& cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),cplcgWmgWmAh(2),cplcgWpCgWpCAh(2),               & 
& cplAhHmcHm(2,2,2),cplAhHmcVWm(2,2),cplAhcHmVWm(2,2),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3), & 
& cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcgWmgWmVP,      & 
& cplcgWpCgWpCVP,cplHmcHmVP(2,2),cplHmcVWmVP(2),cplcHmVPVWm(2),cplcVWmVPVWm,             & 
& cplAhHmcVWmVP1(2,2),cplAhcHmVPVWm1(2,2),cplHmcHmVPVP1(2,2)

Complex(dp), Intent(out) :: Amp(2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,2
Amp(:,gt1) = 0._dp 
! External masses 
Mex1 = MAh(gt1) 
Mex2 = MVP 
Mex3 = MVP 


! {Fd, Fd, Fd}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFd(i1) 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFdFdAhL(i2,i1,gt1)
coup1R = cplcFdFdAhR(i2,i1,gt1)
coup2L = -cplcFdFdVPR(i1,i3)
coup2R = -cplcFdFdVPL(i1,i3)
coup3L = -cplcFdFdVPR(i3,i2)
coup3R = -cplcFdFdVPL(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(6)*AmpC 
    End Do
  End Do
End Do


! {Fe, Fe, Fe}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFe(i1) 
ML2 = MFe(i2) 
ML3 = MFe(i3) 
coup1L = cplcFeFeAhL(i2,i1,gt1)
coup1R = cplcFeFeAhR(i2,i1,gt1)
coup2L = -cplcFeFeVPR(i1,i3)
coup2R = -cplcFeFeVPL(i1,i3)
coup3L = -cplcFeFeVPR(i3,i2)
coup3R = -cplcFeFeVPL(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(2)*AmpC 
    End Do
  End Do
End Do


! {Fu, Fu, Fu}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFu(i1) 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = cplcFuFuAhL(i2,i1,gt1)
coup1R = cplcFuFuAhR(i2,i1,gt1)
coup2L = -cplcFuFuVPR(i1,i3)
coup2R = -cplcFuFuVPL(i1,i3)
coup3L = -cplcFuFuVPR(i3,i2)
coup3R = -cplcFuFuVPL(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(6)*AmpC 
    End Do
  End Do
End Do


! {gWm, gWm, gWm}
ML1 = MVWm 
ML2 = MVWm 
ML3 = MVWm 
coup1 = cplcgWmgWmAh(gt1)
coup2 = cplcgWmgWmVP
coup3 = cplcgWmgWmVP
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(2)*AmpC 


! {gWmC, gWmC, gWmC}
ML1 = MVWm 
ML2 = MVWm 
ML3 = MVWm 
coup1 = cplcgWpCgWpCAh(gt1)
coup2 = cplcgWpCgWpCVP
coup3 = cplcgWpCgWpCVP
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(2)*AmpC 


! {Hm, Hm, Hm}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
ML3 = MHm(i3) 
coup1 = cplAhHmcHm(gt1,i1,i2)
coup2 = -cplHmcHmVP(i3,i1)
coup3 = -cplHmcHmVP(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(2)*AmpC 
    End Do
  End Do
End Do


! {Hm, VWm, Hm}
Do i1=1,2
    Do i3=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
ML3 = MHm(i3) 
coup1 = cplAhHmcVWm(gt1,i1)
coup2 = -cplHmcHmVP(i3,i1)
coup3 = cplcHmVPVWm(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hm, Hm, VWm}
Do i1=1,2
  Do i2=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
ML3 = MVWm 
coup1 = cplAhHmcHm(gt1,i1,i2)
coup2 = cplcHmVPVWm(i1)
coup3 = cplHmcVWmVP(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Hm, VWm, VWm}
Do i1=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
ML3 = MVWm 
coup1 = cplAhHmcVWm(gt1,i1)
coup2 = cplcHmVPVWm(i1)
coup3 = cplcVWmVPVWm
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
End Do


! {VWm, Hm, Hm}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
ML3 = MHm(i3) 
coup1 = cplAhcHmVWm(gt1,i2)
coup2 = cplHmcVWmVP(i3)
coup3 = -cplHmcHmVP(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VWm, Hm, VWm}
  Do i2=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
ML3 = MVWm 
coup1 = cplAhcHmVWm(gt1,i2)
coup2 = cplcVWmVPVWm
coup3 = cplHmcVWmVP(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do


! {conj[Hm], conj[VWm], conj[Hm]}
Do i1=1,2
    Do i3=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
ML3 = MHm(i3) 
coup1 = cplAhcHmVWm(gt1,i1)
coup2 = cplHmcHmVP(i1,i3)
coup3 = cplHmcVWmVP(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {conj[Hm], conj[Hm], conj[VWm]}
Do i1=1,2
  Do i2=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
ML3 = MVWm 
coup1 = cplAhHmcHm(gt1,i2,i1)
coup2 = cplHmcVWmVP(i1)
coup3 = cplcHmVPVWm(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {conj[Hm], conj[VWm], conj[VWm]}
Do i1=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
ML3 = MVWm 
coup1 = cplAhcHmVWm(gt1,i1)
coup2 = cplHmcVWmVP(i1)
coup3 = -cplcVWmVPVWm
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
End Do


! {conj[VWm], conj[Hm], conj[Hm]}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
ML3 = MHm(i3) 
coup1 = cplAhHmcVWm(gt1,i2)
coup2 = cplcHmVPVWm(i3)
coup3 = cplHmcHmVP(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {conj[VWm], conj[Hm], conj[VWm]}
  Do i2=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
ML3 = MVWm 
coup1 = cplAhHmcVWm(gt1,i2)
coup2 = -cplcVWmVPVWm
coup3 = cplcHmVPVWm(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do


! {Hm, Hm}
Do i1=1,2
  Do i2=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
coup1 = cplAhHmcHm(gt1,i1,i2)
coup2 = cplHmcHmVPVP1(i2,i1)
Call Amp_VERTEX_StoVV_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Hm, VWm}
Do i1=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
coup1 = cplAhHmcVWmVP1(gt1,i1)
coup2 = cplcHmVPVWm(i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 

End Do


! {VWm, Hm}
  Do i2=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
coup1 = cplAhcHmVPVWm1(gt1,i2)
coup2 = cplHmcVWmVP(i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology3_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 

  End Do


! {Hm, VWm}
Do i1=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
coup1 = cplAhHmcVWmVP1(gt1,i1)
coup2 = cplcHmVPVWm(i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology4_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 

End Do


! {VWm, Hm}
  Do i2=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
coup1 = cplAhcHmVPVWm1(gt1,i2)
coup2 = cplHmcVWmVP(i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology4_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 

  End Do
End Do
End Subroutine Amplitude_VERTEX_gumTHDMII_AhToVPVP


Subroutine Amplitude_IR_VERTEX_gumTHDMII_AhToVPVP(MAh,MFd,MFe,MFu,MHm,MVP,            & 
& MVWm,MAh2,MFd2,MFe2,MFu2,MHm2,MVP2,MVWm2,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,          & 
& cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhHmcHm,            & 
& cplAhHmcVWm,cplAhcHmVWm,cplcFdFdVPL,cplcFdFdVPR,cplcFeFeVPL,cplcFeFeVPR,               & 
& cplcFuFuVPL,cplcFuFuVPR,cplcgWmgWmVP,cplcgWpCgWpCVP,cplHmcHmVP,cplHmcVWmVP,            & 
& cplcHmVPVWm,cplcVWmVPVWm,cplAhHmcVWmVP1,cplAhcHmVPVWm1,cplHmcHmVPVP1,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MFd(3),MFe(3),MFu(3),MHm(2),MVP,MVWm,MAh2(2),MFd2(3),MFe2(3),MFu2(3),          & 
& MHm2(2),MVP2,MVWm2

Complex(dp), Intent(in) :: cplcFdFdAhL(3,3,2),cplcFdFdAhR(3,3,2),cplcFeFeAhL(3,3,2),cplcFeFeAhR(3,3,2),          & 
& cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),cplcgWmgWmAh(2),cplcgWpCgWpCAh(2),               & 
& cplAhHmcHm(2,2,2),cplAhHmcVWm(2,2),cplAhcHmVWm(2,2),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3), & 
& cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcgWmgWmVP,      & 
& cplcgWpCgWpCVP,cplHmcHmVP(2,2),cplHmcVWmVP(2),cplcHmVPVWm(2),cplcVWmVPVWm,             & 
& cplAhHmcVWmVP1(2,2),cplAhcHmVPVWm1(2,2),cplHmcHmVPVP1(2,2)

Complex(dp), Intent(out) :: Amp(2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,2
Amp(:,gt1) = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = MAh(gt1) 
Mex2 = MVP 
Mex3 = MVP 
End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_gumTHDMII_AhToVPVP


Subroutine Amplitude_WAVE_gumTHDMII_AhToVPVZ(MAh,MAh2,MVP,MVP2,MVZ,MVZ2,              & 
& ZfAh,ZfVP,ZfVZ,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MAh2(2),MVP,MVP2,MVZ,MVZ2

Complex(dp), Intent(in) :: ZfAh(2,2),ZfVP,ZfVZ

Complex(dp), Intent(out) :: Amp(2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

Do gt1=1,2
! External masses 
Mex1 = MAh(gt1) 
Mex2 = MVP 
Mex3 = MVZ 
ZcoupT1 = 0._dp 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
! Vanishing 


! External Field 2 
! Vanishing 


! External Field 3 
Amp(:,gt1) = 0._dp
End Do
End Subroutine Amplitude_WAVE_gumTHDMII_AhToVPVZ


Subroutine Amplitude_VERTEX_gumTHDMII_AhToVPVZ(MAh,MFd,MFe,MFu,MHm,MVP,               & 
& MVWm,MVZ,MAh2,MFd2,MFe2,MFu2,MHm2,MVP2,MVWm2,MVZ2,cplcFdFdAhL,cplcFdFdAhR,             & 
& cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,           & 
& cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,    & 
& cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVPL,cplcFuFuVPR,               & 
& cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmVP,cplcgWmgWmVZ,cplcgWpCgWpCVP,cplcgWpCgWpCVZ,       & 
& cplHmcHmVP,cplHmcVWmVP,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVPVWm,cplcVWmVPVWm,cplcHmVWmVZ,    & 
& cplcVWmVWmVZ,cplAhHmcVWmVP1,cplAhHmcVWmVZ1,cplAhcHmVPVWm1,cplAhcHmVWmVZ1,              & 
& cplHmcHmVPVZ1,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MFd(3),MFe(3),MFu(3),MHm(2),MVP,MVWm,MVZ,MAh2(2),MFd2(3),MFe2(3),              & 
& MFu2(3),MHm2(2),MVP2,MVWm2,MVZ2

Complex(dp), Intent(in) :: cplcFdFdAhL(3,3,2),cplcFdFdAhR(3,3,2),cplcFeFeAhL(3,3,2),cplcFeFeAhR(3,3,2),          & 
& cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),cplcgWmgWmAh(2),cplcgWpCgWpCAh(2),               & 
& cplAhHmcHm(2,2,2),cplAhHmcVWm(2,2),cplAhcHmVWm(2,2),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3), & 
& cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),cplcFeFeVZL(3,3),  & 
& cplcFeFeVZR(3,3),cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),  & 
& cplcgWmgWmVP,cplcgWmgWmVZ,cplcgWpCgWpCVP,cplcgWpCgWpCVZ,cplHmcHmVP(2,2),               & 
& cplHmcVWmVP(2),cplHmcHmVZ(2,2),cplHmcVWmVZ(2),cplcHmVPVWm(2),cplcVWmVPVWm,             & 
& cplcHmVWmVZ(2),cplcVWmVWmVZ,cplAhHmcVWmVP1(2,2),cplAhHmcVWmVZ1(2,2),cplAhcHmVPVWm1(2,2),& 
& cplAhcHmVWmVZ1(2,2),cplHmcHmVPVZ1(2,2)

Complex(dp), Intent(out) :: Amp(2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,2
Amp(:,gt1) = 0._dp 
! External masses 
Mex1 = MAh(gt1) 
Mex2 = MVP 
Mex3 = MVZ 


! {Fd, Fd, Fd}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFd(i1) 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFdFdAhL(i2,i1,gt1)
coup1R = cplcFdFdAhR(i2,i1,gt1)
coup2L = -cplcFdFdVPR(i1,i3)
coup2R = -cplcFdFdVPL(i1,i3)
coup3L = -cplcFdFdVZR(i3,i2)
coup3R = -cplcFdFdVZL(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(6)*AmpC 
    End Do
  End Do
End Do


! {Fe, Fe, Fe}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFe(i1) 
ML2 = MFe(i2) 
ML3 = MFe(i3) 
coup1L = cplcFeFeAhL(i2,i1,gt1)
coup1R = cplcFeFeAhR(i2,i1,gt1)
coup2L = -cplcFeFeVPR(i1,i3)
coup2R = -cplcFeFeVPL(i1,i3)
coup3L = -cplcFeFeVZR(i3,i2)
coup3R = -cplcFeFeVZL(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(2)*AmpC 
    End Do
  End Do
End Do


! {Fu, Fu, Fu}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFu(i1) 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = cplcFuFuAhL(i2,i1,gt1)
coup1R = cplcFuFuAhR(i2,i1,gt1)
coup2L = -cplcFuFuVPR(i1,i3)
coup2R = -cplcFuFuVPL(i1,i3)
coup3L = -cplcFuFuVZR(i3,i2)
coup3R = -cplcFuFuVZL(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(6)*AmpC 
    End Do
  End Do
End Do


! {gWm, gWm, gWm}
ML1 = MVWm 
ML2 = MVWm 
ML3 = MVWm 
coup1 = cplcgWmgWmAh(gt1)
coup2 = cplcgWmgWmVP
coup3 = cplcgWmgWmVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(2)*AmpC 


! {gWmC, gWmC, gWmC}
ML1 = MVWm 
ML2 = MVWm 
ML3 = MVWm 
coup1 = cplcgWpCgWpCAh(gt1)
coup2 = cplcgWpCgWpCVP
coup3 = cplcgWpCgWpCVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(2)*AmpC 


! {Hm, Hm, Hm}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
ML3 = MHm(i3) 
coup1 = cplAhHmcHm(gt1,i1,i2)
coup2 = -cplHmcHmVP(i3,i1)
coup3 = -cplHmcHmVZ(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(2)*AmpC 
    End Do
  End Do
End Do


! {Hm, VWm, Hm}
Do i1=1,2
    Do i3=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
ML3 = MHm(i3) 
coup1 = cplAhHmcVWm(gt1,i1)
coup2 = -cplHmcHmVP(i3,i1)
coup3 = cplcHmVWmVZ(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hm, Hm, VWm}
Do i1=1,2
  Do i2=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
ML3 = MVWm 
coup1 = cplAhHmcHm(gt1,i1,i2)
coup2 = cplcHmVPVWm(i1)
coup3 = cplHmcVWmVZ(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Hm, VWm, VWm}
Do i1=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
ML3 = MVWm 
coup1 = cplAhHmcVWm(gt1,i1)
coup2 = cplcHmVPVWm(i1)
coup3 = -cplcVWmVWmVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
End Do


! {VWm, Hm, Hm}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
ML3 = MHm(i3) 
coup1 = cplAhcHmVWm(gt1,i2)
coup2 = cplHmcVWmVP(i3)
coup3 = -cplHmcHmVZ(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VWm, Hm, VWm}
  Do i2=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
ML3 = MVWm 
coup1 = cplAhcHmVWm(gt1,i2)
coup2 = cplcVWmVPVWm
coup3 = cplHmcVWmVZ(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do


! {conj[Hm], conj[VWm], conj[Hm]}
Do i1=1,2
    Do i3=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
ML3 = MHm(i3) 
coup1 = cplAhcHmVWm(gt1,i1)
coup2 = cplHmcHmVP(i1,i3)
coup3 = cplHmcVWmVZ(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {conj[Hm], conj[Hm], conj[VWm]}
Do i1=1,2
  Do i2=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
ML3 = MVWm 
coup1 = cplAhHmcHm(gt1,i2,i1)
coup2 = cplHmcVWmVP(i1)
coup3 = cplcHmVWmVZ(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {conj[Hm], conj[VWm], conj[VWm]}
Do i1=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
ML3 = MVWm 
coup1 = cplAhcHmVWm(gt1,i1)
coup2 = cplHmcVWmVP(i1)
coup3 = cplcVWmVWmVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
End Do


! {conj[VWm], conj[Hm], conj[Hm]}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
ML3 = MHm(i3) 
coup1 = cplAhHmcVWm(gt1,i2)
coup2 = cplcHmVPVWm(i3)
coup3 = cplHmcHmVZ(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {conj[VWm], conj[Hm], conj[VWm]}
  Do i2=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
ML3 = MVWm 
coup1 = cplAhHmcVWm(gt1,i2)
coup2 = -cplcVWmVPVWm
coup3 = cplcHmVWmVZ(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do


! {Hm, Hm}
Do i1=1,2
  Do i2=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
coup1 = cplAhHmcHm(gt1,i1,i2)
coup2 = cplHmcHmVPVZ1(i2,i1)
Call Amp_VERTEX_StoVV_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Hm, VWm}
Do i1=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
coup1 = cplAhHmcVWmVZ1(gt1,i1)
coup2 = cplcHmVPVWm(i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 

End Do


! {VWm, Hm}
  Do i2=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
coup1 = cplAhcHmVWmVZ1(gt1,i2)
coup2 = cplHmcVWmVP(i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology3_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 

  End Do


! {Hm, VWm}
Do i1=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
coup1 = cplAhHmcVWmVP1(gt1,i1)
coup2 = cplcHmVWmVZ(i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology4_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 

End Do


! {VWm, Hm}
  Do i2=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
coup1 = cplAhcHmVPVWm1(gt1,i2)
coup2 = cplHmcVWmVZ(i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology4_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 

  End Do
End Do
End Subroutine Amplitude_VERTEX_gumTHDMII_AhToVPVZ


Subroutine Amplitude_IR_VERTEX_gumTHDMII_AhToVPVZ(MAh,MFd,MFe,MFu,MHm,MVP,            & 
& MVWm,MVZ,MAh2,MFd2,MFe2,MFu2,MHm2,MVP2,MVWm2,MVZ2,cplcFdFdAhL,cplcFdFdAhR,             & 
& cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,cplcgWpCgWpCAh,           & 
& cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,    & 
& cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVPL,cplcFuFuVPR,               & 
& cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmVP,cplcgWmgWmVZ,cplcgWpCgWpCVP,cplcgWpCgWpCVZ,       & 
& cplHmcHmVP,cplHmcVWmVP,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVPVWm,cplcVWmVPVWm,cplcHmVWmVZ,    & 
& cplcVWmVWmVZ,cplAhHmcVWmVP1,cplAhHmcVWmVZ1,cplAhcHmVPVWm1,cplAhcHmVWmVZ1,              & 
& cplHmcHmVPVZ1,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MFd(3),MFe(3),MFu(3),MHm(2),MVP,MVWm,MVZ,MAh2(2),MFd2(3),MFe2(3),              & 
& MFu2(3),MHm2(2),MVP2,MVWm2,MVZ2

Complex(dp), Intent(in) :: cplcFdFdAhL(3,3,2),cplcFdFdAhR(3,3,2),cplcFeFeAhL(3,3,2),cplcFeFeAhR(3,3,2),          & 
& cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),cplcgWmgWmAh(2),cplcgWpCgWpCAh(2),               & 
& cplAhHmcHm(2,2,2),cplAhHmcVWm(2,2),cplAhcHmVWm(2,2),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3), & 
& cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),cplcFeFeVZL(3,3),  & 
& cplcFeFeVZR(3,3),cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),  & 
& cplcgWmgWmVP,cplcgWmgWmVZ,cplcgWpCgWpCVP,cplcgWpCgWpCVZ,cplHmcHmVP(2,2),               & 
& cplHmcVWmVP(2),cplHmcHmVZ(2,2),cplHmcVWmVZ(2),cplcHmVPVWm(2),cplcVWmVPVWm,             & 
& cplcHmVWmVZ(2),cplcVWmVWmVZ,cplAhHmcVWmVP1(2,2),cplAhHmcVWmVZ1(2,2),cplAhcHmVPVWm1(2,2),& 
& cplAhcHmVWmVZ1(2,2),cplHmcHmVPVZ1(2,2)

Complex(dp), Intent(out) :: Amp(2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,2
Amp(:,gt1) = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = MAh(gt1) 
Mex2 = MVP 
Mex3 = MVZ 
End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_gumTHDMII_AhToVPVZ


Subroutine Amplitude_WAVE_gumTHDMII_AhToVWmcVWm(MAh,MAh2,MVWm,MVWm2,ZfAh,             & 
& ZfVWm,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MAh2(2),MVWm,MVWm2

Complex(dp), Intent(in) :: ZfAh(2,2),ZfVWm

Complex(dp), Intent(out) :: Amp(2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

Do gt1=1,2
! External masses 
Mex1 = MAh(gt1) 
Mex2 = MVWm 
Mex3 = MVWm 
ZcoupT1 = 0._dp 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
! Vanishing 


! External Field 2 
! Vanishing 


! External Field 3 
Amp(:,gt1) = 0._dp
End Do
End Subroutine Amplitude_WAVE_gumTHDMII_AhToVWmcVWm


Subroutine Amplitude_VERTEX_gumTHDMII_AhToVWmcVWm(MAh,MFd,MFe,MFu,Mhh,MHm,            & 
& MVP,MVWm,MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhAh,cplAhAhhh,        & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,               & 
& cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,    & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFdFuVWmL,cplcFdFuVWmR,     & 
& cplcFeFvVWmL,cplcFeFvVWmR,cplcgWmgAVWm,cplcgWpCgAcVWm,cplcgAgWmcVWm,cplcgZgWmcVWm,     & 
& cplcgAgWpCVWm,cplcgZgWpCVWm,cplcgWmgZVWm,cplcgWpCgZcVWm,cplhhHmcVWm,cplhhcHmVWm,       & 
& cplhhcVWmVWm,cplHmcVWmVP,cplHmcVWmVZ,cplcHmVPVWm,cplcVWmVPVWm,cplcHmVWmVZ,             & 
& cplcVWmVWmVZ,cplAhAhcVWmVWm1,cplAhHmcVWmVP1,cplAhHmcVWmVZ1,cplAhcHmVPVWm1,             & 
& cplAhcHmVWmVZ1,cplhhhhcVWmVWm1,cplHmcHmcVWmVWm1,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MFd(3),MFe(3),MFu(3),Mhh(2),MHm(2),MVP,MVWm,MVZ,MAh2(2),MFd2(3),               & 
& MFe2(3),MFu2(3),Mhh2(2),MHm2(2),MVP2,MVWm2,MVZ2

Complex(dp), Intent(in) :: cplAhAhAh(2,2,2),cplAhAhhh(2,2,2),cplcFdFdAhL(3,3,2),cplcFdFdAhR(3,3,2),              & 
& cplcFeFeAhL(3,3,2),cplcFeFeAhR(3,3,2),cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),           & 
& cplcgWmgWmAh(2),cplcgWpCgWpCAh(2),cplAhhhhh(2,2,2),cplAhhhVZ(2,2),cplAhHmcHm(2,2,2),   & 
& cplAhHmcVWm(2,2),cplAhcHmVWm(2,2),cplcFuFdcVWmL(3,3),cplcFuFdcVWmR(3,3),               & 
& cplcFvFecVWmL(3,3),cplcFvFecVWmR(3,3),cplcFdFuVWmL(3,3),cplcFdFuVWmR(3,3),             & 
& cplcFeFvVWmL(3,3),cplcFeFvVWmR(3,3),cplcgWmgAVWm,cplcgWpCgAcVWm,cplcgAgWmcVWm,         & 
& cplcgZgWmcVWm,cplcgAgWpCVWm,cplcgZgWpCVWm,cplcgWmgZVWm,cplcgWpCgZcVWm,cplhhHmcVWm(2,2),& 
& cplhhcHmVWm(2,2),cplhhcVWmVWm(2),cplHmcVWmVP(2),cplHmcVWmVZ(2),cplcHmVPVWm(2),         & 
& cplcVWmVPVWm,cplcHmVWmVZ(2),cplcVWmVWmVZ,cplAhAhcVWmVWm1(2,2),cplAhHmcVWmVP1(2,2),     & 
& cplAhHmcVWmVZ1(2,2),cplAhcHmVPVWm1(2,2),cplAhcHmVWmVZ1(2,2),cplhhhhcVWmVWm1(2,2),      & 
& cplHmcHmcVWmVWm1(2,2)

Complex(dp), Intent(out) :: Amp(2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,2
Amp(:,gt1) = 0._dp 
! External masses 
Mex1 = MAh(gt1) 
Mex2 = MVWm 
Mex3 = MVWm 


! {Ah, Ah, conj[Hm]}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MAh(i1) 
ML2 = MAh(i2) 
ML3 = MHm(i3) 
coup1 = cplAhAhAh(gt1,i1,i2)
coup2 = cplAhcHmVWm(i1,i3)
coup3 = -cplAhHmcVWm(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Ah, hh, conj[Hm]}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MAh(i1) 
ML2 = Mhh(i2) 
ML3 = MHm(i3) 
coup1 = cplAhAhhh(gt1,i1,i2)
coup2 = cplAhcHmVWm(i1,i3)
coup3 = -cplhhHmcVWm(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Fd, Fd, Fu}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFd(i1) 
ML2 = MFd(i2) 
ML3 = MFu(i3) 
coup1L = cplcFdFdAhL(i2,i1,gt1)
coup1R = cplcFdFdAhR(i2,i1,gt1)
coup2L = -cplcFdFuVWmR(i1,i3)
coup2R = -cplcFdFuVWmL(i1,i3)
coup3L = -cplcFuFdcVWmR(i3,i2)
coup3R = -cplcFuFdcVWmL(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(3)*AmpC 
    End Do
  End Do
End Do


! {Fe, Fe, Fv}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFe(i1) 
ML2 = MFe(i2) 
ML3 = 0._dp 
coup1L = cplcFeFeAhL(i2,i1,gt1)
coup1R = cplcFeFeAhR(i2,i1,gt1)
coup2L = -cplcFeFvVWmR(i1,i3)
coup2R = -cplcFeFvVWmL(i1,i3)
coup3L = -cplcFvFecVWmR(i3,i2)
coup3R = -cplcFvFecVWmL(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {gWm, gWm, gP}
ML1 = MVWm 
ML2 = MVWm 
ML3 = MVP 
coup1 = cplcgWmgWmAh(gt1)
coup2 = cplcgWmgAVWm
coup3 = cplcgAgWmcVWm
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 


! {gWm, gWm, gZ}
ML1 = MVWm 
ML2 = MVWm 
ML3 = MVZ 
coup1 = cplcgWmgWmAh(gt1)
coup2 = cplcgWmgZVWm
coup3 = cplcgZgWmcVWm
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 


! {hh, Ah, conj[Hm]}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = Mhh(i1) 
ML2 = MAh(i2) 
ML3 = MHm(i3) 
coup1 = cplAhAhhh(gt1,i2,i1)
coup2 = cplhhcHmVWm(i1,i3)
coup3 = -cplAhHmcVWm(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {hh, hh, conj[Hm]}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = Mhh(i1) 
ML2 = Mhh(i2) 
ML3 = MHm(i3) 
coup1 = cplAhhhhh(gt1,i1,i2)
coup2 = cplhhcHmVWm(i1,i3)
coup3 = -cplhhHmcVWm(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {hh, VZ, conj[Hm]}
Do i1=1,2
    Do i3=1,2
ML1 = Mhh(i1) 
ML2 = MVZ 
ML3 = MHm(i3) 
coup1 = cplAhhhVZ(gt1,i1)
coup2 = cplhhcHmVWm(i1,i3)
coup3 = cplHmcVWmVZ(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {hh, hh, conj[VWm]}
Do i1=1,2
  Do i2=1,2
ML1 = Mhh(i1) 
ML2 = Mhh(i2) 
ML3 = MVWm 
coup1 = cplAhhhhh(gt1,i1,i2)
coup2 = cplhhcVWmVWm(i1)
coup3 = cplhhcVWmVWm(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {hh, VZ, conj[VWm]}
Do i1=1,2
ML1 = Mhh(i1) 
ML2 = MVZ 
ML3 = MVWm 
coup1 = cplAhhhVZ(gt1,i1)
coup2 = cplhhcVWmVWm(i1)
coup3 = -cplcVWmVWmVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
End Do


! {Hm, Hm, Ah}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
ML3 = MAh(i3) 
coup1 = cplAhHmcHm(gt1,i1,i2)
coup2 = -cplAhcHmVWm(i3,i1)
coup3 = cplAhHmcVWm(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Hm, Hm, hh}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
ML3 = Mhh(i3) 
coup1 = cplAhHmcHm(gt1,i1,i2)
coup2 = -cplhhcHmVWm(i3,i1)
coup3 = cplhhHmcVWm(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Hm, VWm, hh}
Do i1=1,2
    Do i3=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
ML3 = Mhh(i3) 
coup1 = cplAhHmcVWm(gt1,i1)
coup2 = -cplhhcHmVWm(i3,i1)
coup3 = cplhhcVWmVWm(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hm, Hm, VP}
Do i1=1,2
  Do i2=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
ML3 = MVP 
coup1 = cplAhHmcHm(gt1,i1,i2)
coup2 = cplcHmVPVWm(i1)
coup3 = cplHmcVWmVP(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Hm, VWm, VP}
Do i1=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
ML3 = MVP 
coup1 = cplAhHmcVWm(gt1,i1)
coup2 = cplcHmVPVWm(i1)
coup3 = -cplcVWmVPVWm
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
End Do


! {Hm, Hm, VZ}
Do i1=1,2
  Do i2=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
ML3 = MVZ 
coup1 = cplAhHmcHm(gt1,i1,i2)
coup2 = cplcHmVWmVZ(i1)
coup3 = cplHmcVWmVZ(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Hm, VWm, VZ}
Do i1=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
ML3 = MVZ 
coup1 = cplAhHmcVWm(gt1,i1)
coup2 = cplcHmVWmVZ(i1)
coup3 = cplcVWmVWmVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
End Do


! {VWm, Hm, hh}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
ML3 = Mhh(i3) 
coup1 = cplAhcHmVWm(gt1,i2)
coup2 = cplhhcVWmVWm(i3)
coup3 = cplhhHmcVWm(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VWm, Hm, VP}
  Do i2=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
ML3 = MVP 
coup1 = cplAhcHmVWm(gt1,i2)
coup2 = -cplcVWmVPVWm
coup3 = cplHmcVWmVP(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do


! {VWm, Hm, VZ}
  Do i2=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
ML3 = MVZ 
coup1 = cplAhcHmVWm(gt1,i2)
coup2 = cplcVWmVWmVZ
coup3 = cplHmcVWmVZ(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do


! {VZ, hh, conj[Hm]}
  Do i2=1,2
    Do i3=1,2
ML1 = MVZ 
ML2 = Mhh(i2) 
ML3 = MHm(i3) 
coup1 = cplAhhhVZ(gt1,i2)
coup2 = cplcHmVWmVZ(i3)
coup3 = -cplhhHmcVWm(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VZ, hh, conj[VWm]}
  Do i2=1,2
ML1 = MVZ 
ML2 = Mhh(i2) 
ML3 = MVWm 
coup1 = cplAhhhVZ(gt1,i2)
coup2 = -cplcVWmVWmVZ
coup3 = cplhhcVWmVWm(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do


! {bar[Fu], bar[Fu], bar[Fd]}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFu(i1) 
ML2 = MFu(i2) 
ML3 = MFd(i3) 
coup1L = cplcFuFuAhL(i1,i2,gt1)
coup1R = cplcFuFuAhR(i1,i2,gt1)
coup2L = cplcFdFuVWmL(i3,i1)
coup2R = cplcFdFuVWmR(i3,i1)
coup3L = cplcFuFdcVWmL(i2,i3)
coup3R = cplcFuFdcVWmR(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(3)*AmpC 
    End Do
  End Do
End Do


! {bar[gWmC], bar[gWmC], bar[gP]}
ML1 = MVWm 
ML2 = MVWm 
ML3 = MVP 
coup1 = cplcgWpCgWpCAh(gt1)
coup2 = cplcgAgWpCVWm
coup3 = cplcgWpCgAcVWm
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 


! {bar[gWmC], bar[gWmC], bar[gZ]}
ML1 = MVWm 
ML2 = MVWm 
ML3 = MVZ 
coup1 = cplcgWpCgWpCAh(gt1)
coup2 = cplcgZgWpCVWm
coup3 = cplcgWpCgZcVWm
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 


! {Ah, Ah}
Do i1=1,2
  Do i2=1,2
ML1 = MAh(i1) 
ML2 = MAh(i2) 
coup1 = cplAhAhAh(gt1,i1,i2)
coup2 = cplAhAhcVWmVWm1(i1,i2)
Call Amp_VERTEX_StoVV_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1._dp/2._dp)*AmpC 
  End Do
End Do


! {hh, hh}
Do i1=1,2
  Do i2=1,2
ML1 = Mhh(i1) 
ML2 = Mhh(i2) 
coup1 = cplAhhhhh(gt1,i1,i2)
coup2 = cplhhhhcVWmVWm1(i1,i2)
Call Amp_VERTEX_StoVV_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1._dp/2._dp)*AmpC 
  End Do
End Do


! {Hm, Hm}
Do i1=1,2
  Do i2=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
coup1 = cplAhHmcHm(gt1,i1,i2)
coup2 = cplHmcHmcVWmVWm1(i2,i1)
Call Amp_VERTEX_StoVV_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Hm, VP}
Do i1=1,2
ML1 = MHm(i1) 
ML2 = MVP 
coup1 = cplAhHmcVWmVP1(gt1,i1)
coup2 = cplcHmVPVWm(i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 

End Do


! {Hm, VZ}
Do i1=1,2
ML1 = MHm(i1) 
ML2 = MVZ 
coup1 = cplAhHmcVWmVZ1(gt1,i1)
coup2 = cplcHmVWmVZ(i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 

End Do


! {VP, Hm}
  Do i2=1,2
ML1 = MVP 
ML2 = MHm(i2) 
coup1 = cplAhcHmVPVWm1(gt1,i2)
coup2 = cplHmcVWmVP(i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology4_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 

  End Do


! {VZ, Hm}
  Do i2=1,2
ML1 = MVZ 
ML2 = MHm(i2) 
coup1 = cplAhcHmVWmVZ1(gt1,i2)
coup2 = cplHmcVWmVZ(i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology4_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 

  End Do
End Do
End Subroutine Amplitude_VERTEX_gumTHDMII_AhToVWmcVWm


Subroutine Amplitude_IR_VERTEX_gumTHDMII_AhToVWmcVWm(MAh,MFd,MFe,MFu,Mhh,             & 
& MHm,MVP,MVWm,MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVP2,MVWm2,MVZ2,cplAhAhAh,              & 
& cplAhAhhh,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,     & 
& cplcgWmgWmAh,cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,    & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFdFuVWmL,cplcFdFuVWmR,     & 
& cplcFeFvVWmL,cplcFeFvVWmR,cplcgWmgAVWm,cplcgWpCgAcVWm,cplcgAgWmcVWm,cplcgZgWmcVWm,     & 
& cplcgAgWpCVWm,cplcgZgWpCVWm,cplcgWmgZVWm,cplcgWpCgZcVWm,cplhhHmcVWm,cplhhcHmVWm,       & 
& cplhhcVWmVWm,cplHmcVWmVP,cplHmcVWmVZ,cplcHmVPVWm,cplcVWmVPVWm,cplcHmVWmVZ,             & 
& cplcVWmVWmVZ,cplAhAhcVWmVWm1,cplAhHmcVWmVP1,cplAhHmcVWmVZ1,cplAhcHmVPVWm1,             & 
& cplAhcHmVWmVZ1,cplhhhhcVWmVWm1,cplHmcHmcVWmVWm1,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MFd(3),MFe(3),MFu(3),Mhh(2),MHm(2),MVP,MVWm,MVZ,MAh2(2),MFd2(3),               & 
& MFe2(3),MFu2(3),Mhh2(2),MHm2(2),MVP2,MVWm2,MVZ2

Complex(dp), Intent(in) :: cplAhAhAh(2,2,2),cplAhAhhh(2,2,2),cplcFdFdAhL(3,3,2),cplcFdFdAhR(3,3,2),              & 
& cplcFeFeAhL(3,3,2),cplcFeFeAhR(3,3,2),cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),           & 
& cplcgWmgWmAh(2),cplcgWpCgWpCAh(2),cplAhhhhh(2,2,2),cplAhhhVZ(2,2),cplAhHmcHm(2,2,2),   & 
& cplAhHmcVWm(2,2),cplAhcHmVWm(2,2),cplcFuFdcVWmL(3,3),cplcFuFdcVWmR(3,3),               & 
& cplcFvFecVWmL(3,3),cplcFvFecVWmR(3,3),cplcFdFuVWmL(3,3),cplcFdFuVWmR(3,3),             & 
& cplcFeFvVWmL(3,3),cplcFeFvVWmR(3,3),cplcgWmgAVWm,cplcgWpCgAcVWm,cplcgAgWmcVWm,         & 
& cplcgZgWmcVWm,cplcgAgWpCVWm,cplcgZgWpCVWm,cplcgWmgZVWm,cplcgWpCgZcVWm,cplhhHmcVWm(2,2),& 
& cplhhcHmVWm(2,2),cplhhcVWmVWm(2),cplHmcVWmVP(2),cplHmcVWmVZ(2),cplcHmVPVWm(2),         & 
& cplcVWmVPVWm,cplcHmVWmVZ(2),cplcVWmVWmVZ,cplAhAhcVWmVWm1(2,2),cplAhHmcVWmVP1(2,2),     & 
& cplAhHmcVWmVZ1(2,2),cplAhcHmVPVWm1(2,2),cplAhcHmVWmVZ1(2,2),cplhhhhcVWmVWm1(2,2),      & 
& cplHmcHmcVWmVWm1(2,2)

Complex(dp), Intent(out) :: Amp(2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,2
Amp(:,gt1) = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = MAh(gt1) 
Mex2 = MVWm 
Mex3 = MVWm 


! {Hm, Hm, VP}
Do i1=1,2
  Do i2=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
ML3 = MVP 
coup1 = cplAhHmcHm(gt1,i1,i2)
coup2 = cplcHmVPVWm(i1)
coup3 = cplHmcVWmVP(i2)
Call Amp_VERTEX_StoVV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Hm, VWm, VP}
Do i1=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
ML3 = MVP 
coup1 = cplAhHmcVWm(gt1,i1)
coup2 = cplcHmVPVWm(i1)
coup3 = -cplcVWmVPVWm
Call Amp_VERTEX_StoVV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
End Do


! {VWm, Hm, VP}
  Do i2=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
ML3 = MVP 
coup1 = cplAhcHmVWm(gt1,i2)
coup2 = -cplcVWmVPVWm
coup3 = cplHmcVWmVP(i2)
Call Amp_VERTEX_StoVV_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do


! {Hm, VP}
Do i1=1,2
ML1 = MHm(i1) 
ML2 = MVP 
coup1 = cplAhHmcVWmVP1(gt1,i1)
coup2 = cplcHmVPVWm(i1)
Call Amp_VERTEX_StoVV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 

End Do


! {VP, Hm}
  Do i2=1,2
ML1 = MVP 
ML2 = MHm(i2) 
coup1 = cplAhcHmVPVWm1(gt1,i2)
coup2 = cplHmcVWmVP(i2)
Call Amp_VERTEX_StoVV_Topology4_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 

  End Do
End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_gumTHDMII_AhToVWmcVWm


Subroutine Amplitude_WAVE_gumTHDMII_AhToVZVZ(MAh,MAh2,MVZ,MVZ2,ZfAh,ZfVZ,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MAh2(2),MVZ,MVZ2

Complex(dp), Intent(in) :: ZfAh(2,2),ZfVZ

Complex(dp), Intent(out) :: Amp(2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

Do gt1=1,2
! External masses 
Mex1 = MAh(gt1) 
Mex2 = MVZ 
Mex3 = MVZ 
ZcoupT1 = 0._dp 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
! Vanishing 


! External Field 2 
! Vanishing 


! External Field 3 
Amp(:,gt1) = 0._dp
End Do
End Subroutine Amplitude_WAVE_gumTHDMII_AhToVZVZ


Subroutine Amplitude_VERTEX_gumTHDMII_AhToVZVZ(MAh,MFd,MFe,MFu,Mhh,MHm,               & 
& MVWm,MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVWm2,MVZ2,cplAhAhAh,cplcFdFdAhL,               & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdVZL,     & 
& cplcFdFdVZR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmVZ,              & 
& cplcgWpCgWpCVZ,cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVWmVZ,cplcVWmVWmVZ,              & 
& cplAhAhVZVZ1,cplAhHmcVWmVZ1,cplAhcHmVWmVZ1,cplhhhhVZVZ1,cplHmcHmVZVZ1,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MFd(3),MFe(3),MFu(3),Mhh(2),MHm(2),MVWm,MVZ,MAh2(2),MFd2(3),MFe2(3),           & 
& MFu2(3),Mhh2(2),MHm2(2),MVWm2,MVZ2

Complex(dp), Intent(in) :: cplAhAhAh(2,2,2),cplcFdFdAhL(3,3,2),cplcFdFdAhR(3,3,2),cplcFeFeAhL(3,3,2),            & 
& cplcFeFeAhR(3,3,2),cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),cplcgWmgWmAh(2),              & 
& cplcgWpCgWpCAh(2),cplAhhhhh(2,2,2),cplAhhhVZ(2,2),cplAhHmcHm(2,2,2),cplAhHmcVWm(2,2),  & 
& cplAhcHmVWm(2,2),cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),  & 
& cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplcgWmgWmVZ,cplcgWpCgWpCVZ,cplhhVZVZ(2),            & 
& cplHmcHmVZ(2,2),cplHmcVWmVZ(2),cplcHmVWmVZ(2),cplcVWmVWmVZ,cplAhAhVZVZ1(2,2),          & 
& cplAhHmcVWmVZ1(2,2),cplAhcHmVWmVZ1(2,2),cplhhhhVZVZ1(2,2),cplHmcHmVZVZ1(2,2)

Complex(dp), Intent(out) :: Amp(2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,2
Amp(:,gt1) = 0._dp 
! External masses 
Mex1 = MAh(gt1) 
Mex2 = MVZ 
Mex3 = MVZ 


! {Ah, Ah, hh}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MAh(i1) 
ML2 = MAh(i2) 
ML3 = Mhh(i3) 
coup1 = cplAhAhAh(gt1,i1,i2)
coup2 = cplAhhhVZ(i1,i3)
coup3 = -cplAhhhVZ(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Fd, Fd, Fd}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFd(i1) 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFdFdAhL(i2,i1,gt1)
coup1R = cplcFdFdAhR(i2,i1,gt1)
coup2L = -cplcFdFdVZR(i1,i3)
coup2R = -cplcFdFdVZL(i1,i3)
coup3L = -cplcFdFdVZR(i3,i2)
coup3R = -cplcFdFdVZL(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(6)*AmpC 
    End Do
  End Do
End Do


! {Fe, Fe, Fe}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFe(i1) 
ML2 = MFe(i2) 
ML3 = MFe(i3) 
coup1L = cplcFeFeAhL(i2,i1,gt1)
coup1R = cplcFeFeAhR(i2,i1,gt1)
coup2L = -cplcFeFeVZR(i1,i3)
coup2R = -cplcFeFeVZL(i1,i3)
coup3L = -cplcFeFeVZR(i3,i2)
coup3R = -cplcFeFeVZL(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(2)*AmpC 
    End Do
  End Do
End Do


! {Fu, Fu, Fu}
Do i1=1,3
  Do i2=1,3
    Do i3=1,3
ML1 = MFu(i1) 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = cplcFuFuAhL(i2,i1,gt1)
coup1R = cplcFuFuAhR(i2,i1,gt1)
coup2L = -cplcFuFuVZR(i1,i3)
coup2R = -cplcFuFuVZL(i1,i3)
coup3L = -cplcFuFuVZR(i3,i2)
coup3R = -cplcFuFuVZL(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_FFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(6)*AmpC 
    End Do
  End Do
End Do


! {gWm, gWm, gWm}
ML1 = MVWm 
ML2 = MVWm 
ML3 = MVWm 
coup1 = cplcgWmgWmAh(gt1)
coup2 = cplcgWmgWmVZ
coup3 = cplcgWmgWmVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(2)*AmpC 


! {gWmC, gWmC, gWmC}
ML1 = MVWm 
ML2 = MVWm 
ML3 = MVWm 
coup1 = cplcgWpCgWpCAh(gt1)
coup2 = cplcgWpCgWpCVZ
coup3 = cplcgWpCgWpCVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_UUU(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(2)*AmpC 


! {hh, hh, Ah}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = Mhh(i1) 
ML2 = Mhh(i2) 
ML3 = MAh(i3) 
coup1 = cplAhhhhh(gt1,i1,i2)
coup2 = -cplAhhhVZ(i3,i1)
coup3 = cplAhhhVZ(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {hh, hh, VZ}
Do i1=1,2
  Do i2=1,2
ML1 = Mhh(i1) 
ML2 = Mhh(i2) 
ML3 = MVZ 
coup1 = cplAhhhhh(gt1,i1,i2)
coup2 = cplhhVZVZ(i1)
coup3 = cplhhVZVZ(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Hm, Hm, Hm}
Do i1=1,2
  Do i2=1,2
    Do i3=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
ML3 = MHm(i3) 
coup1 = cplAhHmcHm(gt1,i1,i2)
coup2 = -cplHmcHmVZ(i3,i1)
coup3 = -cplHmcHmVZ(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(2)*AmpC 
    End Do
  End Do
End Do


! {Hm, VWm, Hm}
Do i1=1,2
    Do i3=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
ML3 = MHm(i3) 
coup1 = cplAhHmcVWm(gt1,i1)
coup2 = -cplHmcHmVZ(i3,i1)
coup3 = cplcHmVWmVZ(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Hm, Hm, VWm}
Do i1=1,2
  Do i2=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
ML3 = MVWm 
coup1 = cplAhHmcHm(gt1,i1,i2)
coup2 = cplcHmVWmVZ(i1)
coup3 = cplHmcVWmVZ(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Hm, VWm, VWm}
Do i1=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
ML3 = MVWm 
coup1 = cplAhHmcVWm(gt1,i1)
coup2 = cplcHmVWmVZ(i1)
coup3 = -cplcVWmVWmVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
End Do


! {VWm, Hm, Hm}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
ML3 = MHm(i3) 
coup1 = cplAhcHmVWm(gt1,i2)
coup2 = cplHmcVWmVZ(i3)
coup3 = -cplHmcHmVZ(i2,i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VWm, Hm, VWm}
  Do i2=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
ML3 = MVWm 
coup1 = cplAhcHmVWm(gt1,i2)
coup2 = -cplcVWmVWmVZ
coup3 = cplHmcVWmVZ(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do


! {conj[Hm], conj[VWm], conj[Hm]}
Do i1=1,2
    Do i3=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
ML3 = MHm(i3) 
coup1 = cplAhcHmVWm(gt1,i1)
coup2 = cplHmcHmVZ(i1,i3)
coup3 = cplHmcVWmVZ(i3)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {conj[Hm], conj[Hm], conj[VWm]}
Do i1=1,2
  Do i2=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
ML3 = MVWm 
coup1 = cplAhHmcHm(gt1,i2,i1)
coup2 = cplHmcVWmVZ(i1)
coup3 = cplcHmVWmVZ(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {conj[Hm], conj[VWm], conj[VWm]}
Do i1=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
ML3 = MVWm 
coup1 = cplAhcHmVWm(gt1,i1)
coup2 = cplHmcVWmVZ(i1)
coup3 = cplcVWmVWmVZ
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_SVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
End Do


! {conj[VWm], conj[Hm], conj[Hm]}
  Do i2=1,2
    Do i3=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
ML3 = MHm(i3) 
coup1 = cplAhHmcVWm(gt1,i2)
coup2 = cplcHmVWmVZ(i3)
coup3 = cplHmcHmVZ(i3,i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {conj[VWm], conj[Hm], conj[VWm]}
  Do i2=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
ML3 = MVWm 
coup1 = cplAhHmcVWm(gt1,i2)
coup2 = cplcVWmVWmVZ
coup3 = cplcHmVWmVZ(i2)
If ((Abs(coup1))*(Abs(coup2))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology1_VSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1,coup2,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do


! {Ah, Ah}
Do i1=1,2
  Do i2=1,2
ML1 = MAh(i1) 
ML2 = MAh(i2) 
coup1 = cplAhAhAh(gt1,i1,i2)
coup2 = cplAhAhVZVZ1(i1,i2)
Call Amp_VERTEX_StoVV_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1._dp/2._dp)*AmpC 
  End Do
End Do


! {hh, hh}
Do i1=1,2
  Do i2=1,2
ML1 = Mhh(i1) 
ML2 = Mhh(i2) 
coup1 = cplAhhhhh(gt1,i1,i2)
coup2 = cplhhhhVZVZ1(i1,i2)
Call Amp_VERTEX_StoVV_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1._dp/2._dp)*AmpC 
  End Do
End Do


! {Hm, Hm}
Do i1=1,2
  Do i2=1,2
ML1 = MHm(i1) 
ML2 = MHm(i2) 
coup1 = cplAhHmcHm(gt1,i1,i2)
coup2 = cplHmcHmVZVZ1(i2,i1)
Call Amp_VERTEX_StoVV_Topology2_SS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Hm, VWm}
Do i1=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
coup1 = cplAhHmcVWmVZ1(gt1,i1)
coup2 = cplcHmVWmVZ(i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology3_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 

End Do


! {VWm, Hm}
  Do i2=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
coup1 = cplAhcHmVWmVZ1(gt1,i2)
coup2 = cplHmcVWmVZ(i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology3_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 

  End Do


! {Hm, VWm}
Do i1=1,2
ML1 = MHm(i1) 
ML2 = MVWm 
coup1 = cplAhHmcVWmVZ1(gt1,i1)
coup2 = cplcHmVWmVZ(i1)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology4_SV(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 

End Do


! {VWm, Hm}
  Do i2=1,2
ML1 = MVWm 
ML2 = MHm(i2) 
coup1 = cplAhcHmVWmVZ1(gt1,i2)
coup2 = cplHmcVWmVZ(i2)
If (Abs(coup1)*Abs(coup2).gt.epsCoup) Then 
Call Amp_VERTEX_StoVV_Topology4_VS(Mex1,Mex2,Mex3,ML1,ML2,coup1,coup2,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1) = Amp(:,gt1) + oo16pi2*(1)*AmpC 

  End Do
End Do
End Subroutine Amplitude_VERTEX_gumTHDMII_AhToVZVZ


Subroutine Amplitude_IR_VERTEX_gumTHDMII_AhToVZVZ(MAh,MFd,MFe,MFu,Mhh,MHm,            & 
& MVWm,MVZ,MAh2,MFd2,MFe2,MFu2,Mhh2,MHm2,MVWm2,MVZ2,cplAhAhAh,cplcFdFdAhL,               & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplcgWmgWmAh,              & 
& cplcgWpCgWpCAh,cplAhhhhh,cplAhhhVZ,cplAhHmcHm,cplAhHmcVWm,cplAhcHmVWm,cplcFdFdVZL,     & 
& cplcFdFdVZR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,cplcgWmgWmVZ,              & 
& cplcgWpCgWpCVZ,cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVWmVZ,cplcVWmVWmVZ,              & 
& cplAhAhVZVZ1,cplAhHmcVWmVZ1,cplAhcHmVWmVZ1,cplhhhhVZVZ1,cplHmcHmVZVZ1,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MFd(3),MFe(3),MFu(3),Mhh(2),MHm(2),MVWm,MVZ,MAh2(2),MFd2(3),MFe2(3),           & 
& MFu2(3),Mhh2(2),MHm2(2),MVWm2,MVZ2

Complex(dp), Intent(in) :: cplAhAhAh(2,2,2),cplcFdFdAhL(3,3,2),cplcFdFdAhR(3,3,2),cplcFeFeAhL(3,3,2),            & 
& cplcFeFeAhR(3,3,2),cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),cplcgWmgWmAh(2),              & 
& cplcgWpCgWpCAh(2),cplAhhhhh(2,2,2),cplAhhhVZ(2,2),cplAhHmcHm(2,2,2),cplAhHmcVWm(2,2),  & 
& cplAhcHmVWm(2,2),cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),  & 
& cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplcgWmgWmVZ,cplcgWpCgWpCVZ,cplhhVZVZ(2),            & 
& cplHmcHmVZ(2,2),cplHmcVWmVZ(2),cplcHmVWmVZ(2),cplcVWmVWmVZ,cplAhAhVZVZ1(2,2),          & 
& cplAhHmcVWmVZ1(2,2),cplAhcHmVWmVZ1(2,2),cplhhhhVZVZ1(2,2),cplHmcHmVZVZ1(2,2)

Complex(dp), Intent(out) :: Amp(2,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,2
Amp(:,gt1) = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = MAh(gt1) 
Mex2 = MVZ 
Mex3 = MVZ 
End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_gumTHDMII_AhToVZVZ



End Module OneLoopDecay_Ah_gumTHDMII
