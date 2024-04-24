! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.14.0 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 18:23 on 16.9.2022   
! ----------------------------------------------------------------------  
 
 
Module OneLoopDecay_Fu_gumTHDMII
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

Subroutine Amplitude_Tree_gumTHDMII_FuToFuAh(cplcFuFuAhL,cplcFuFuAhR,MAh,             & 
& MFu,MAh2,MFu2,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MFu(3),MAh2(2),MFu2(3)

Complex(dp), Intent(in) :: cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2)

Complex(dp) :: Amp(2,3,3,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 

Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,2
! External masses 
Mex1 = MFu(gt1) 
Mex2 = MFu(gt2) 
Mex3 = MAh(gt3) 
! Tree-Level Vertex 
coupT1L = cplcFuFuAhL(gt1,gt2,gt3)
coupT1R = cplcFuFuAhR(gt1,gt2,gt3)
Call TreeAmp_FtoFS(Mex1,Mex2,Mex3,coupT1L,coupT1R,AmpC) 
! Colour and symmetry factor 
Amp(:,gt1, gt2, gt3) = AmpC 
    End Do
  End Do
End Do
End Subroutine Amplitude_Tree_gumTHDMII_FuToFuAh


Subroutine Gamma_Real_gumTHDMII_FuToFuAh(MLambda,em,gs,cplcFuFuAhL,cplcFuFuAhR,       & 
& MAh,MFu,GammarealPhoton,GammarealGluon)

Implicit None

Complex(dp), Intent(in) :: cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2)

Real(dp), Intent(in) :: MAh(2),MFu(3)

Real(dp), Intent(in) :: MLambda, em, gs 

Real(dp), Intent(out) :: GammarealPhoton(3,3,2), GammarealGluon(3,3,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 

Real(dp) :: Mloop1, Mloop2, Mloop3 
Complex(dp) :: CoupL, CoupR 
 
Do i1=1,3
  Do i2=1,3
    Do i3=2,2
CoupL = cplcFuFuAhL(i1,i2,i3)
CoupR = cplcFuFuAhR(i1,i2,i3)
Mex1 = MFu(i1)
Mex2 = MFu(i2)
Mex3 = MAh(i3)
If (Abs(Mex1).gt.(Abs(Mex2)+Abs(Mex3))) Then 
 Call hardradiationFFS(Mex1,Mex2,Mex3,MLambda,em,4._dp/9._dp,4._dp/9._dp,0._dp,4._dp/9._dp,0._dp,0._dp,CoupL,CoupR,Gammarealphoton(i1,i2,i3),kont)
 Call hardradiationFFS(Mex1,Mex2,Mex3,MLambda,gs,4._dp/3._dp,4._dp/3._dp,0._dp,4._dp/3._dp,0._dp,0._dp,CoupL,CoupR,Gammarealgluon(i1,i2,i3),kont)
Else 
  GammarealGluon(i1,i2,i3) = 0._dp 
  GammarealPhoton(i1,i2,i3) = 0._dp 

End if 
    End Do
  End Do
End Do
End Subroutine Gamma_Real_gumTHDMII_FuToFuAh


Subroutine Amplitude_WAVE_gumTHDMII_FuToFuAh(cplcFuFuAhL,cplcFuFuAhR,ctcplcFuFuAhL,   & 
& ctcplcFuFuAhR,MAh,MAh2,MFu,MFu2,ZfAh,ZfUL,ZfUR,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MAh2(2),MFu(3),MFu2(3)

Complex(dp), Intent(in) :: cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2)

Complex(dp), Intent(in) :: ctcplcFuFuAhL(3,3,2),ctcplcFuFuAhR(3,3,2)

Complex(dp), Intent(in) :: ZfAh(2,2),ZfUL(3,3),ZfUR(3,3)

Complex(dp), Intent(out) :: Amp(2,3,3,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,2
! External masses 
Mex1 = MFu(gt1) 
Mex2 = MFu(gt2) 
Mex3 = MAh(gt3) 
!----------------------------- 
! Coupling counter term 
!----------------------------- 
ZcoupT1L = ctcplcFuFuAhL(gt1,gt2,gt3) 
ZcoupT1R = ctcplcFuFuAhR(gt1,gt2,gt3) 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
Do i1=1,3
ZcoupT1L = ZcoupT1L + 0.5_dp*ZfUR(i1,gt1)*cplcFuFuAhL(i1,gt2,gt3)
ZcoupT1R = ZcoupT1R + 0.5_dp*Conjg(ZfUL(i1,gt1))*cplcFuFuAhR(i1,gt2,gt3)
End Do


! External Field 2 
Do i1=1,3
ZcoupT1L = ZcoupT1L + 0.5_dp*ZfUL(i1,gt2)*cplcFuFuAhL(gt1,i1,gt3)
ZcoupT1R = ZcoupT1R + 0.5_dp*Conjg(ZfUR(i1,gt2))*cplcFuFuAhR(gt1,i1,gt3)
End Do


! External Field 3 
Do i1=1,2
ZcoupT1L = ZcoupT1L + 0.5_dp*ZfAh(i1,gt3)*cplcFuFuAhL(gt1,gt2,i1)
ZcoupT1R = ZcoupT1R + 0.5_dp*ZfAh(i1,gt3)*cplcFuFuAhR(gt1,gt2,i1)
End Do


! Getting the amplitude 
Call TreeAmp_FtoFS(Mex1,Mex2,Mex3,ZcoupT1L,ZcoupT1R,AmpC) 
Amp(:,gt1, gt2, gt3) = AmpC 
    End Do
  End Do
End Do
End Subroutine Amplitude_WAVE_gumTHDMII_FuToFuAh


Subroutine Amplitude_VERTEX_gumTHDMII_FuToFuAh(MAh,MFd,MFu,Mhh,MHm,MVG,               & 
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

Complex(dp), Intent(out) :: Amp(2,3,3,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,2
Amp(:,gt1, gt2, gt3) = 0._dp 
! External masses 
Mex1 = MFu(gt1) 
Mex2 = MFu(gt2) 
Mex3 = MAh(gt3) 


! {Ah, bar[Fu], bar[Fu]}
Do i1=1,2
  Do i2=1,3
    Do i3=1,3
ML1 = MAh(i1) 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = cplcFuFuAhL(gt1,i2,i1)
coup1R = cplcFuFuAhR(gt1,i2,i1)
coup2L = cplcFuFuAhL(i3,gt2,i1)
coup2R = cplcFuFuAhR(i3,gt2,i1)
coup3L = cplcFuFuAhL(i2,i3,gt3)
coup3R = cplcFuFuAhR(i2,i3,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_SFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Fd, Hm, Hm}
Do i1=1,3
  Do i2=1,2
    Do i3=1,2
ML1 = MFd(i1) 
ML2 = MHm(i2) 
ML3 = MHm(i3) 
coup1L = cplcFuFdcHmL(gt1,i1,i2)
coup1R = cplcFuFdcHmR(gt1,i1,i2)
coup2L = cplcFdFuHmL(i1,gt2,i3)
coup2R = cplcFdFuHmR(i1,gt2,i3)
coup3 = cplAhHmcHm(gt3,i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Fd, VWm, Hm}
Do i1=1,3
    Do i3=1,2
ML1 = MFd(i1) 
ML2 = MVWm 
ML3 = MHm(i3) 
coup1L = -cplcFuFdcVWmR(gt1,i1)
coup1R = -cplcFuFdcVWmL(gt1,i1)
coup2L = cplcFdFuHmL(i1,gt2,i3)
coup2R = cplcFdFuHmR(i1,gt2,i3)
coup3 = -cplAhcHmVWm(gt3,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Fd, Hm, VWm}
Do i1=1,3
  Do i2=1,2
ML1 = MFd(i1) 
ML2 = MHm(i2) 
ML3 = MVWm 
coup1L = cplcFuFdcHmL(gt1,i1,i2)
coup1R = cplcFuFdcHmR(gt1,i1,i2)
coup2L = -cplcFdFuVWmR(i1,gt2)
coup2R = -cplcFdFuVWmL(i1,gt2)
coup3 = -cplAhHmcVWm(gt3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Fu, Ah, Ah}
Do i1=1,3
  Do i2=1,2
    Do i3=1,2
ML1 = MFu(i1) 
ML2 = MAh(i2) 
ML3 = MAh(i3) 
coup1L = cplcFuFuAhL(gt1,i1,i2)
coup1R = cplcFuFuAhR(gt1,i1,i2)
coup2L = cplcFuFuAhL(i1,gt2,i3)
coup2R = cplcFuFuAhR(i1,gt2,i3)
coup3 = cplAhAhAh(gt3,i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Fu, hh, Ah}
Do i1=1,3
  Do i2=1,2
    Do i3=1,2
ML1 = MFu(i1) 
ML2 = Mhh(i2) 
ML3 = MAh(i3) 
coup1L = cplcFuFuhhL(gt1,i1,i2)
coup1R = cplcFuFuhhR(gt1,i1,i2)
coup2L = cplcFuFuAhL(i1,gt2,i3)
coup2R = cplcFuFuAhR(i1,gt2,i3)
coup3 = cplAhAhhh(gt3,i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Fu, Ah, hh}
Do i1=1,3
  Do i2=1,2
    Do i3=1,2
ML1 = MFu(i1) 
ML2 = MAh(i2) 
ML3 = Mhh(i3) 
coup1L = cplcFuFuAhL(gt1,i1,i2)
coup1R = cplcFuFuAhR(gt1,i1,i2)
coup2L = cplcFuFuhhL(i1,gt2,i3)
coup2R = cplcFuFuhhR(i1,gt2,i3)
coup3 = cplAhAhhh(gt3,i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Fu, hh, hh}
Do i1=1,3
  Do i2=1,2
    Do i3=1,2
ML1 = MFu(i1) 
ML2 = Mhh(i2) 
ML3 = Mhh(i3) 
coup1L = cplcFuFuhhL(gt1,i1,i2)
coup1R = cplcFuFuhhR(gt1,i1,i2)
coup2L = cplcFuFuhhL(i1,gt2,i3)
coup2R = cplcFuFuhhR(i1,gt2,i3)
coup3 = cplAhhhhh(gt3,i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Fu, VZ, hh}
Do i1=1,3
    Do i3=1,2
ML1 = MFu(i1) 
ML2 = MVZ 
ML3 = Mhh(i3) 
coup1L = -cplcFuFuVZR(gt1,i1)
coup1R = -cplcFuFuVZL(gt1,i1)
coup2L = cplcFuFuhhL(i1,gt2,i3)
coup2R = cplcFuFuhhR(i1,gt2,i3)
coup3 = -cplAhhhVZ(gt3,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Fu, hh, VZ}
Do i1=1,3
  Do i2=1,2
ML1 = MFu(i1) 
ML2 = Mhh(i2) 
ML3 = MVZ 
coup1L = cplcFuFuhhL(gt1,i1,i2)
coup1R = cplcFuFuhhR(gt1,i1,i2)
coup2L = -cplcFuFuVZR(i1,gt2)
coup2R = -cplcFuFuVZL(i1,gt2)
coup3 = -cplAhhhVZ(gt3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {hh, bar[Fu], bar[Fu]}
Do i1=1,2
  Do i2=1,3
    Do i3=1,3
ML1 = Mhh(i1) 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = cplcFuFuhhL(gt1,i2,i1)
coup1R = cplcFuFuhhR(gt1,i2,i1)
coup2L = cplcFuFuhhL(i3,gt2,i1)
coup2R = cplcFuFuhhR(i3,gt2,i1)
coup3L = cplcFuFuAhL(i2,i3,gt3)
coup3R = cplcFuFuAhR(i2,i3,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_SFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {VG, bar[Fu], bar[Fu]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVG 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = -cplcFuFuVGR(gt1,i2)
coup1R = -cplcFuFuVGL(gt1,i2)
coup2L = -cplcFuFuVGR(i3,gt2)
coup2R = -cplcFuFuVGL(i3,gt2)
coup3L = cplcFuFuAhL(i2,i3,gt3)
coup3R = cplcFuFuAhR(i2,i3,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(4._dp/3._dp)*AmpC 
    End Do
  End Do


! {VP, bar[Fu], bar[Fu]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVP 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = -cplcFuFuVPR(gt1,i2)
coup1R = -cplcFuFuVPL(gt1,i2)
coup2L = -cplcFuFuVPR(i3,gt2)
coup2R = -cplcFuFuVPL(i3,gt2)
coup3L = cplcFuFuAhL(i2,i3,gt3)
coup3R = cplcFuFuAhR(i2,i3,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VZ, bar[Fu], bar[Fu]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVZ 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = -cplcFuFuVZR(gt1,i2)
coup1R = -cplcFuFuVZL(gt1,i2)
coup2L = -cplcFuFuVZR(i3,gt2)
coup2R = -cplcFuFuVZL(i3,gt2)
coup3L = cplcFuFuAhL(i2,i3,gt3)
coup3R = cplcFuFuAhR(i2,i3,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {conj[Hm], bar[Fd], bar[Fd]}
Do i1=1,2
  Do i2=1,3
    Do i3=1,3
ML1 = MHm(i1) 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFuFdcHmL(gt1,i2,i1)
coup1R = cplcFuFdcHmR(gt1,i2,i1)
coup2L = cplcFdFuHmL(i3,gt2,i1)
coup2R = cplcFdFuHmR(i3,gt2,i1)
coup3L = cplcFdFdAhL(i2,i3,gt3)
coup3R = cplcFdFdAhR(i2,i3,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_SFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {conj[VWm], bar[Fd], bar[Fd]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVWm 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = -cplcFuFdcVWmR(gt1,i2)
coup1R = -cplcFuFdcVWmL(gt1,i2)
coup2L = -cplcFdFuVWmR(i3,gt2)
coup2R = -cplcFdFuVWmL(i3,gt2)
coup3L = cplcFdFdAhL(i2,i3,gt3)
coup3R = cplcFdFdAhR(i2,i3,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
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
End Subroutine Amplitude_VERTEX_gumTHDMII_FuToFuAh


Subroutine Amplitude_IR_VERTEX_gumTHDMII_FuToFuAh(MAh,MFd,MFu,Mhh,MHm,MVG,            & 
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

Complex(dp), Intent(out) :: Amp(2,3,3,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,2
Amp(:,gt1, gt2, gt3) = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = MFu(gt1) 
Mex2 = MFu(gt2) 
Mex3 = MAh(gt3) 


! {VG, bar[Fu], bar[Fu]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVG 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = -cplcFuFuVGR(gt1,i2)
coup1R = -cplcFuFuVGL(gt1,i2)
coup2L = -cplcFuFuVGR(i3,gt2)
coup2R = -cplcFuFuVGL(i3,gt2)
coup3L = cplcFuFuAhL(i2,i3,gt3)
coup3R = cplcFuFuAhR(i2,i3,gt3)
Call Amp_VERTEX_FtoFS_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(4._dp/3._dp)*AmpC 
    End Do
  End Do


! {VP, bar[Fu], bar[Fu]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVP 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = -cplcFuFuVPR(gt1,i2)
coup1R = -cplcFuFuVPL(gt1,i2)
coup2L = -cplcFuFuVPR(i3,gt2)
coup2R = -cplcFuFuVPL(i3,gt2)
coup3L = cplcFuFuAhL(i2,i3,gt3)
coup3R = cplcFuFuAhR(i2,i3,gt3)
Call Amp_VERTEX_FtoFS_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
    End Do
  End Do
End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_gumTHDMII_FuToFuAh


Subroutine Amplitude_Tree_gumTHDMII_FuToFdcHm(cplcFuFdcHmL,cplcFuFdcHmR,              & 
& MFd,MFu,MHm,MFd2,MFu2,MHm2,Amp)

Implicit None

Real(dp), Intent(in) :: MFd(3),MFu(3),MHm(2),MFd2(3),MFu2(3),MHm2(2)

Complex(dp), Intent(in) :: cplcFuFdcHmL(3,3,2),cplcFuFdcHmR(3,3,2)

Complex(dp) :: Amp(2,3,3,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 

Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,2
! External masses 
Mex1 = MFu(gt1) 
Mex2 = MFd(gt2) 
Mex3 = MHm(gt3) 
! Tree-Level Vertex 
coupT1L = cplcFuFdcHmL(gt1,gt2,gt3)
coupT1R = cplcFuFdcHmR(gt1,gt2,gt3)
Call TreeAmp_FtoFS(Mex1,Mex2,Mex3,coupT1L,coupT1R,AmpC) 
! Colour and symmetry factor 
Amp(:,gt1, gt2, gt3) = AmpC 
    End Do
  End Do
End Do
End Subroutine Amplitude_Tree_gumTHDMII_FuToFdcHm


Subroutine Gamma_Real_gumTHDMII_FuToFdcHm(MLambda,em,gs,cplcFuFdcHmL,cplcFuFdcHmR,    & 
& MFd,MFu,MHm,GammarealPhoton,GammarealGluon)

Implicit None

Complex(dp), Intent(in) :: cplcFuFdcHmL(3,3,2),cplcFuFdcHmR(3,3,2)

Real(dp), Intent(in) :: MFd(3),MFu(3),MHm(2)

Real(dp), Intent(in) :: MLambda, em, gs 

Real(dp), Intent(out) :: GammarealPhoton(3,3,2), GammarealGluon(3,3,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 

Real(dp) :: Mloop1, Mloop2, Mloop3 
Complex(dp) :: CoupL, CoupR 
 
Do i1=1,3
  Do i2=1,3
    Do i3=2,2
CoupL = cplcFuFdcHmL(i1,i2,i3)
CoupR = cplcFuFdcHmR(i1,i2,i3)
Mex1 = MFu(i1)
Mex2 = MFd(i2)
Mex3 = MHm(i3)
If (Abs(Mex1).gt.(Abs(Mex2)+Abs(Mex3))) Then 
 Call hardradiationFFS(Mex1,Mex2,Mex3,MLambda,em,4._dp/9._dp,-2._dp/9._dp,2._dp/3._dp,1._dp/9._dp,-1._dp/3._dp,1._dp,CoupL,CoupR,Gammarealphoton(i1,i2,i3),kont)
 Call hardradiationFFS(Mex1,Mex2,Mex3,MLambda,gs,4._dp/3._dp,4._dp/3._dp,0._dp,4._dp/3._dp,0._dp,0._dp,CoupL,CoupR,Gammarealgluon(i1,i2,i3),kont)
Else 
  GammarealGluon(i1,i2,i3) = 0._dp 
  GammarealPhoton(i1,i2,i3) = 0._dp 

End if 
    End Do
  End Do
End Do
End Subroutine Gamma_Real_gumTHDMII_FuToFdcHm


Subroutine Amplitude_WAVE_gumTHDMII_FuToFdcHm(cplcFuFdcHmL,cplcFuFdcHmR,              & 
& ctcplcFuFdcHmL,ctcplcFuFdcHmR,MFd,MFd2,MFu,MFu2,MHm,MHm2,ZfDL,ZfDR,ZfHm,               & 
& ZfUL,ZfUR,Amp)

Implicit None

Real(dp), Intent(in) :: MFd(3),MFd2(3),MFu(3),MFu2(3),MHm(2),MHm2(2)

Complex(dp), Intent(in) :: cplcFuFdcHmL(3,3,2),cplcFuFdcHmR(3,3,2)

Complex(dp), Intent(in) :: ctcplcFuFdcHmL(3,3,2),ctcplcFuFdcHmR(3,3,2)

Complex(dp), Intent(in) :: ZfDL(3,3),ZfDR(3,3),ZfHm(2,2),ZfUL(3,3),ZfUR(3,3)

Complex(dp), Intent(out) :: Amp(2,3,3,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,2
! External masses 
Mex1 = MFu(gt1) 
Mex2 = MFd(gt2) 
Mex3 = MHm(gt3) 
!----------------------------- 
! Coupling counter term 
!----------------------------- 
ZcoupT1L = ctcplcFuFdcHmL(gt1,gt2,gt3) 
ZcoupT1R = ctcplcFuFdcHmR(gt1,gt2,gt3) 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
Do i1=1,3
ZcoupT1L = ZcoupT1L + 0.5_dp*ZfUR(i1,gt1)*cplcFuFdcHmL(i1,gt2,gt3)
ZcoupT1R = ZcoupT1R + 0.5_dp*Conjg(ZfUL(i1,gt1))*cplcFuFdcHmR(i1,gt2,gt3)
End Do


! External Field 2 
Do i1=1,3
ZcoupT1L = ZcoupT1L + 0.5_dp*ZfDL(i1,gt2)*cplcFuFdcHmL(gt1,i1,gt3)
ZcoupT1R = ZcoupT1R + 0.5_dp*Conjg(ZfDR(i1,gt2))*cplcFuFdcHmR(gt1,i1,gt3)
End Do


! External Field 3 
Do i1=1,2
ZcoupT1L = ZcoupT1L + 0.5_dp*Conjg(ZfHm(i1,gt3))*cplcFuFdcHmL(gt1,gt2,i1)
ZcoupT1R = ZcoupT1R + 0.5_dp*Conjg(ZfHm(i1,gt3))*cplcFuFdcHmR(gt1,gt2,i1)
End Do


! Getting the amplitude 
Call TreeAmp_FtoFS(Mex1,Mex2,Mex3,ZcoupT1L,ZcoupT1R,AmpC) 
Amp(:,gt1, gt2, gt3) = AmpC 
    End Do
  End Do
End Do
End Subroutine Amplitude_WAVE_gumTHDMII_FuToFdcHm


Subroutine Amplitude_VERTEX_gumTHDMII_FuToFdcHm(MAh,MFd,MFu,Mhh,MHm,MVG,              & 
& MVP,MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplcFdFdAhL,cplcFdFdAhR,    & 
& cplcFuFuAhL,cplcFuFuAhR,cplAhHmcHm,cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,    & 
& cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHmL,              & 
& cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,          & 
& cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplhhHmcHm,cplhhcHmVWm,    & 
& cplHmcHmVP,cplHmcHmVZ,cplcHmVPVWm,cplcHmVWmVZ,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MFd(3),MFu(3),Mhh(2),MHm(2),MVG,MVP,MVWm,MVZ,MAh2(2),MFd2(3),MFu2(3),          & 
& Mhh2(2),MHm2(2),MVG2,MVP2,MVWm2,MVZ2

Complex(dp), Intent(in) :: cplcFdFdAhL(3,3,2),cplcFdFdAhR(3,3,2),cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),          & 
& cplAhHmcHm(2,2,2),cplAhcHmVWm(2,2),cplcFdFdhhL(3,3,2),cplcFdFdhhR(3,3,2),              & 
& cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),cplcFdFdVZL(3,3),  & 
& cplcFdFdVZR(3,3),cplcFuFdcHmL(3,3,2),cplcFuFdcHmR(3,3,2),cplcFuFdcVWmL(3,3),           & 
& cplcFuFdcVWmR(3,3),cplcFuFuhhL(3,3,2),cplcFuFuhhR(3,3,2),cplcFuFuVGL(3,3),             & 
& cplcFuFuVGR(3,3),cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),  & 
& cplhhHmcHm(2,2,2),cplhhcHmVWm(2,2),cplHmcHmVP(2,2),cplHmcHmVZ(2,2),cplcHmVPVWm(2),     & 
& cplcHmVWmVZ(2)

Complex(dp), Intent(out) :: Amp(2,3,3,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,2
Amp(:,gt1, gt2, gt3) = 0._dp 
! External masses 
Mex1 = MFu(gt1) 
Mex2 = MFd(gt2) 
Mex3 = MHm(gt3) 


! {Ah, bar[Fu], bar[Fd]}
Do i1=1,2
  Do i2=1,3
    Do i3=1,3
ML1 = MAh(i1) 
ML2 = MFu(i2) 
ML3 = MFd(i3) 
coup1L = cplcFuFuAhL(gt1,i2,i1)
coup1R = cplcFuFuAhR(gt1,i2,i1)
coup2L = cplcFdFdAhL(i3,gt2,i1)
coup2R = cplcFdFdAhR(i3,gt2,i1)
coup3L = cplcFuFdcHmL(i2,i3,gt3)
coup3R = cplcFuFdcHmR(i2,i3,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_SFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Fd, Hm, Ah}
Do i1=1,3
  Do i2=1,2
    Do i3=1,2
ML1 = MFd(i1) 
ML2 = MHm(i2) 
ML3 = MAh(i3) 
coup1L = cplcFuFdcHmL(gt1,i1,i2)
coup1R = cplcFuFdcHmR(gt1,i1,i2)
coup2L = cplcFdFdAhL(i1,gt2,i3)
coup2R = cplcFdFdAhR(i1,gt2,i3)
coup3 = cplAhHmcHm(i3,i2,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Fd, VWm, Ah}
Do i1=1,3
    Do i3=1,2
ML1 = MFd(i1) 
ML2 = MVWm 
ML3 = MAh(i3) 
coup1L = -cplcFuFdcVWmR(gt1,i1)
coup1R = -cplcFuFdcVWmL(gt1,i1)
coup2L = cplcFdFdAhL(i1,gt2,i3)
coup2R = cplcFdFdAhR(i1,gt2,i3)
coup3 = cplAhcHmVWm(i3,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Fd, Hm, hh}
Do i1=1,3
  Do i2=1,2
    Do i3=1,2
ML1 = MFd(i1) 
ML2 = MHm(i2) 
ML3 = Mhh(i3) 
coup1L = cplcFuFdcHmL(gt1,i1,i2)
coup1R = cplcFuFdcHmR(gt1,i1,i2)
coup2L = cplcFdFdhhL(i1,gt2,i3)
coup2R = cplcFdFdhhR(i1,gt2,i3)
coup3 = cplhhHmcHm(i3,i2,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Fd, VWm, hh}
Do i1=1,3
    Do i3=1,2
ML1 = MFd(i1) 
ML2 = MVWm 
ML3 = Mhh(i3) 
coup1L = -cplcFuFdcVWmR(gt1,i1)
coup1R = -cplcFuFdcVWmL(gt1,i1)
coup2L = cplcFdFdhhL(i1,gt2,i3)
coup2R = cplcFdFdhhR(i1,gt2,i3)
coup3 = cplhhcHmVWm(i3,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Fd, Hm, VP}
Do i1=1,3
  Do i2=1,2
ML1 = MFd(i1) 
ML2 = MHm(i2) 
ML3 = MVP 
coup1L = cplcFuFdcHmL(gt1,i1,i2)
coup1R = cplcFuFdcHmR(gt1,i1,i2)
coup2L = -cplcFdFdVPR(i1,gt2)
coup2R = -cplcFdFdVPL(i1,gt2)
coup3 = cplHmcHmVP(i2,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Fd, VWm, VP}
Do i1=1,3
ML1 = MFd(i1) 
ML2 = MVWm 
ML3 = MVP 
coup1L = -cplcFuFdcVWmR(gt1,i1)
coup1R = -cplcFuFdcVWmL(gt1,i1)
coup2L = -cplcFdFdVPR(i1,gt2)
coup2R = -cplcFdFdVPL(i1,gt2)
coup3 = cplcHmVPVWm(gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
End Do


! {Fd, Hm, VZ}
Do i1=1,3
  Do i2=1,2
ML1 = MFd(i1) 
ML2 = MHm(i2) 
ML3 = MVZ 
coup1L = cplcFuFdcHmL(gt1,i1,i2)
coup1R = cplcFuFdcHmR(gt1,i1,i2)
coup2L = -cplcFdFdVZR(i1,gt2)
coup2R = -cplcFdFdVZL(i1,gt2)
coup3 = cplHmcHmVZ(i2,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Fd, VWm, VZ}
Do i1=1,3
ML1 = MFd(i1) 
ML2 = MVWm 
ML3 = MVZ 
coup1L = -cplcFuFdcVWmR(gt1,i1)
coup1R = -cplcFuFdcVWmL(gt1,i1)
coup2L = -cplcFdFdVZR(i1,gt2)
coup2R = -cplcFdFdVZL(i1,gt2)
coup3 = cplcHmVWmVZ(gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
End Do


! {Fu, Ah, conj[Hm]}
Do i1=1,3
  Do i2=1,2
    Do i3=1,2
ML1 = MFu(i1) 
ML2 = MAh(i2) 
ML3 = MHm(i3) 
coup1L = cplcFuFuAhL(gt1,i1,i2)
coup1R = cplcFuFuAhR(gt1,i1,i2)
coup2L = cplcFuFdcHmL(i1,gt2,i3)
coup2R = cplcFuFdcHmR(i1,gt2,i3)
coup3 = cplAhHmcHm(i2,i3,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Fu, hh, conj[Hm]}
Do i1=1,3
  Do i2=1,2
    Do i3=1,2
ML1 = MFu(i1) 
ML2 = Mhh(i2) 
ML3 = MHm(i3) 
coup1L = cplcFuFuhhL(gt1,i1,i2)
coup1R = cplcFuFuhhR(gt1,i1,i2)
coup2L = cplcFuFdcHmL(i1,gt2,i3)
coup2R = cplcFuFdcHmR(i1,gt2,i3)
coup3 = cplhhHmcHm(i2,i3,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Fu, VP, conj[Hm]}
Do i1=1,3
    Do i3=1,2
ML1 = MFu(i1) 
ML2 = MVP 
ML3 = MHm(i3) 
coup1L = -cplcFuFuVPR(gt1,i1)
coup1R = -cplcFuFuVPL(gt1,i1)
coup2L = cplcFuFdcHmL(i1,gt2,i3)
coup2R = cplcFuFdcHmR(i1,gt2,i3)
coup3 = cplHmcHmVP(i3,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Fu, VZ, conj[Hm]}
Do i1=1,3
    Do i3=1,2
ML1 = MFu(i1) 
ML2 = MVZ 
ML3 = MHm(i3) 
coup1L = -cplcFuFuVZR(gt1,i1)
coup1R = -cplcFuFuVZL(gt1,i1)
coup2L = cplcFuFdcHmL(i1,gt2,i3)
coup2R = cplcFuFdcHmR(i1,gt2,i3)
coup3 = cplHmcHmVZ(i3,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Fu, Ah, conj[VWm]}
Do i1=1,3
  Do i2=1,2
ML1 = MFu(i1) 
ML2 = MAh(i2) 
ML3 = MVWm 
coup1L = cplcFuFuAhL(gt1,i1,i2)
coup1R = cplcFuFuAhR(gt1,i1,i2)
coup2L = -cplcFuFdcVWmR(i1,gt2)
coup2R = -cplcFuFdcVWmL(i1,gt2)
coup3 = cplAhcHmVWm(i2,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Fu, hh, conj[VWm]}
Do i1=1,3
  Do i2=1,2
ML1 = MFu(i1) 
ML2 = Mhh(i2) 
ML3 = MVWm 
coup1L = cplcFuFuhhL(gt1,i1,i2)
coup1R = cplcFuFuhhR(gt1,i1,i2)
coup2L = -cplcFuFdcVWmR(i1,gt2)
coup2R = -cplcFuFdcVWmL(i1,gt2)
coup3 = cplhhcHmVWm(i2,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Fu, VP, conj[VWm]}
Do i1=1,3
ML1 = MFu(i1) 
ML2 = MVP 
ML3 = MVWm 
coup1L = -cplcFuFuVPR(gt1,i1)
coup1R = -cplcFuFuVPL(gt1,i1)
coup2L = -cplcFuFdcVWmR(i1,gt2)
coup2R = -cplcFuFdcVWmL(i1,gt2)
coup3 = cplcHmVPVWm(gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
End Do


! {Fu, VZ, conj[VWm]}
Do i1=1,3
ML1 = MFu(i1) 
ML2 = MVZ 
ML3 = MVWm 
coup1L = -cplcFuFuVZR(gt1,i1)
coup1R = -cplcFuFuVZL(gt1,i1)
coup2L = -cplcFuFdcVWmR(i1,gt2)
coup2R = -cplcFuFdcVWmL(i1,gt2)
coup3 = cplcHmVWmVZ(gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
End Do


! {hh, bar[Fu], bar[Fd]}
Do i1=1,2
  Do i2=1,3
    Do i3=1,3
ML1 = Mhh(i1) 
ML2 = MFu(i2) 
ML3 = MFd(i3) 
coup1L = cplcFuFuhhL(gt1,i2,i1)
coup1R = cplcFuFuhhR(gt1,i2,i1)
coup2L = cplcFdFdhhL(i3,gt2,i1)
coup2R = cplcFdFdhhR(i3,gt2,i1)
coup3L = cplcFuFdcHmL(i2,i3,gt3)
coup3R = cplcFuFdcHmR(i2,i3,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_SFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {VG, bar[Fu], bar[Fd]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVG 
ML2 = MFu(i2) 
ML3 = MFd(i3) 
coup1L = -cplcFuFuVGR(gt1,i2)
coup1R = -cplcFuFuVGL(gt1,i2)
coup2L = -cplcFdFdVGR(i3,gt2)
coup2R = -cplcFdFdVGL(i3,gt2)
coup3L = cplcFuFdcHmL(i2,i3,gt3)
coup3R = cplcFuFdcHmR(i2,i3,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(4._dp/3._dp)*AmpC 
    End Do
  End Do


! {VP, bar[Fu], bar[Fd]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVP 
ML2 = MFu(i2) 
ML3 = MFd(i3) 
coup1L = -cplcFuFuVPR(gt1,i2)
coup1R = -cplcFuFuVPL(gt1,i2)
coup2L = -cplcFdFdVPR(i3,gt2)
coup2R = -cplcFdFdVPL(i3,gt2)
coup3L = cplcFuFdcHmL(i2,i3,gt3)
coup3R = cplcFuFdcHmR(i2,i3,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VZ, bar[Fu], bar[Fd]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVZ 
ML2 = MFu(i2) 
ML3 = MFd(i3) 
coup1L = -cplcFuFuVZR(gt1,i2)
coup1R = -cplcFuFuVZL(gt1,i2)
coup2L = -cplcFdFdVZR(i3,gt2)
coup2R = -cplcFdFdVZL(i3,gt2)
coup3L = cplcFuFdcHmL(i2,i3,gt3)
coup3R = cplcFuFdcHmR(i2,i3,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
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
End Subroutine Amplitude_VERTEX_gumTHDMII_FuToFdcHm


Subroutine Amplitude_IR_VERTEX_gumTHDMII_FuToFdcHm(MAh,MFd,MFu,Mhh,MHm,               & 
& MVG,MVP,MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplcFdFdAhL,            & 
& cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,cplAhHmcHm,cplAhcHmVWm,cplcFdFdhhL,cplcFdFdhhR,    & 
& cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,               & 
& cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,         & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplhhHmcHm,cplhhcHmVWm,cplHmcHmVP,cplHmcHmVZ,cplcHmVPVWm,cplcHmVWmVZ,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MFd(3),MFu(3),Mhh(2),MHm(2),MVG,MVP,MVWm,MVZ,MAh2(2),MFd2(3),MFu2(3),          & 
& Mhh2(2),MHm2(2),MVG2,MVP2,MVWm2,MVZ2

Complex(dp), Intent(in) :: cplcFdFdAhL(3,3,2),cplcFdFdAhR(3,3,2),cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),          & 
& cplAhHmcHm(2,2,2),cplAhcHmVWm(2,2),cplcFdFdhhL(3,3,2),cplcFdFdhhR(3,3,2),              & 
& cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),cplcFdFdVZL(3,3),  & 
& cplcFdFdVZR(3,3),cplcFuFdcHmL(3,3,2),cplcFuFdcHmR(3,3,2),cplcFuFdcVWmL(3,3),           & 
& cplcFuFdcVWmR(3,3),cplcFuFuhhL(3,3,2),cplcFuFuhhR(3,3,2),cplcFuFuVGL(3,3),             & 
& cplcFuFuVGR(3,3),cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),  & 
& cplhhHmcHm(2,2,2),cplhhcHmVWm(2,2),cplHmcHmVP(2,2),cplHmcHmVZ(2,2),cplcHmVPVWm(2),     & 
& cplcHmVWmVZ(2)

Complex(dp), Intent(out) :: Amp(2,3,3,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,2
Amp(:,gt1, gt2, gt3) = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = MFu(gt1) 
Mex2 = MFd(gt2) 
Mex3 = MHm(gt3) 


! {Fd, Hm, VP}
Do i1=1,3
  Do i2=1,2
ML1 = MFd(i1) 
ML2 = MHm(i2) 
ML3 = MVP 
coup1L = cplcFuFdcHmL(gt1,i1,i2)
coup1R = cplcFuFdcHmR(gt1,i1,i2)
coup2L = -cplcFdFdVPR(i1,gt2)
coup2R = -cplcFdFdVPL(i1,gt2)
coup3 = cplHmcHmVP(i2,gt3)
Call Amp_VERTEX_FtoFS_Topology1_FSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Fd, VWm, VP}
Do i1=1,3
ML1 = MFd(i1) 
ML2 = MVWm 
ML3 = MVP 
coup1L = -cplcFuFdcVWmR(gt1,i1)
coup1R = -cplcFuFdcVWmL(gt1,i1)
coup2L = -cplcFdFdVPR(i1,gt2)
coup2R = -cplcFdFdVPL(i1,gt2)
coup3 = cplcHmVPVWm(gt3)
Call Amp_VERTEX_FtoFS_Topology1_FVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
End Do


! {Fu, VP, conj[Hm]}
Do i1=1,3
    Do i3=1,2
ML1 = MFu(i1) 
ML2 = MVP 
ML3 = MHm(i3) 
coup1L = -cplcFuFuVPR(gt1,i1)
coup1R = -cplcFuFuVPL(gt1,i1)
coup2L = cplcFuFdcHmL(i1,gt2,i3)
coup2R = cplcFuFdcHmR(i1,gt2,i3)
coup3 = cplHmcHmVP(i3,gt3)
Call Amp_VERTEX_FtoFS_Topology1_FVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Fu, VP, conj[VWm]}
Do i1=1,3
ML1 = MFu(i1) 
ML2 = MVP 
ML3 = MVWm 
coup1L = -cplcFuFuVPR(gt1,i1)
coup1R = -cplcFuFuVPL(gt1,i1)
coup2L = -cplcFuFdcVWmR(i1,gt2)
coup2R = -cplcFuFdcVWmL(i1,gt2)
coup3 = cplcHmVPVWm(gt3)
Call Amp_VERTEX_FtoFS_Topology1_FVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
End Do


! {VG, bar[Fu], bar[Fd]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVG 
ML2 = MFu(i2) 
ML3 = MFd(i3) 
coup1L = -cplcFuFuVGR(gt1,i2)
coup1R = -cplcFuFuVGL(gt1,i2)
coup2L = -cplcFdFdVGR(i3,gt2)
coup2R = -cplcFdFdVGL(i3,gt2)
coup3L = cplcFuFdcHmL(i2,i3,gt3)
coup3R = cplcFuFdcHmR(i2,i3,gt3)
Call Amp_VERTEX_FtoFS_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(4._dp/3._dp)*AmpC 
    End Do
  End Do


! {VP, bar[Fu], bar[Fd]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVP 
ML2 = MFu(i2) 
ML3 = MFd(i3) 
coup1L = -cplcFuFuVPR(gt1,i2)
coup1R = -cplcFuFuVPL(gt1,i2)
coup2L = -cplcFdFdVPR(i3,gt2)
coup2R = -cplcFdFdVPL(i3,gt2)
coup3L = cplcFuFdcHmL(i2,i3,gt3)
coup3R = cplcFuFdcHmR(i2,i3,gt3)
Call Amp_VERTEX_FtoFS_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
    End Do
  End Do
End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_gumTHDMII_FuToFdcHm


Subroutine Amplitude_Tree_gumTHDMII_FuToFdcVWm(cplcFuFdcVWmL,cplcFuFdcVWmR,           & 
& MFd,MFu,MVWm,MFd2,MFu2,MVWm2,Amp)

Implicit None

Real(dp), Intent(in) :: MFd(3),MFu(3),MVWm,MFd2(3),MFu2(3),MVWm2

Complex(dp), Intent(in) :: cplcFuFdcVWmL(3,3),cplcFuFdcVWmR(3,3)

Complex(dp) :: Amp(4,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(4) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 

Do gt1=1,3
  Do gt2=1,3
! External masses 
Mex1 = MFu(gt1) 
Mex2 = MFd(gt2) 
Mex3 = MVWm 
! Tree-Level Vertex 
coupT1L = cplcFuFdcVWmL(gt1,gt2)
coupT1R = cplcFuFdcVWmR(gt1,gt2)
Call TreeAmp_FtoFV(Mex1,Mex2,Mex3,coupT1R,coupT1L,AmpC) 
! Colour and symmetry factor 
Amp(:,gt1, gt2) = -AmpC 
  End Do
End Do
End Subroutine Amplitude_Tree_gumTHDMII_FuToFdcVWm


Subroutine Gamma_Real_gumTHDMII_FuToFdcVWm(MLambda,em,gs,cplcFuFdcVWmL,               & 
& cplcFuFdcVWmR,MFd,MFu,MVWm,GammarealPhoton,GammarealGluon)

Implicit None

Complex(dp), Intent(in) :: cplcFuFdcVWmL(3,3),cplcFuFdcVWmR(3,3)

Real(dp), Intent(in) :: MFd(3),MFu(3),MVWm

Real(dp), Intent(in) :: MLambda, em, gs 

Real(dp), Intent(out) :: GammarealPhoton(3,3), GammarealGluon(3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 

Real(dp) :: Mloop1, Mloop2, Mloop3 
Complex(dp) :: CoupL, CoupR 
 
Do i1=1,3
  Do i2=1,3
CoupL = cplcFuFdcVWmL(i1,i2)
CoupR = cplcFuFdcVWmR(i1,i2)
Mex1 = MFu(i1)
Mex2 = MFd(i2)
Mex3 = MVWm
If (Abs(Mex1).gt.(Abs(Mex2)+Abs(Mex3))) Then 
  Call hardphotonFFW(Mex1,Mex2,Mex3,MLambda,2._dp/3._dp,-1._dp/3._dp,CoupL,CoupR,(0,1)*em,GammaRealPhoton(i1,i2),kont)
  Call hardgluonFFZW(Mex1,Mex2,Mex3,MLambda,4._dp/3._dp,gs,CoupL,CoupR,Gammarealgluon(i1,i2),kont)
Else 
  GammarealGluon(i1,i2) = 0._dp 
  GammarealPhoton(i1,i2) = 0._dp 

End if 
  End Do
End Do
End Subroutine Gamma_Real_gumTHDMII_FuToFdcVWm


Subroutine Amplitude_WAVE_gumTHDMII_FuToFdcVWm(cplcFuFdcVWmL,cplcFuFdcVWmR,           & 
& ctcplcFuFdcVWmL,ctcplcFuFdcVWmR,MFd,MFd2,MFu,MFu2,MVWm,MVWm2,ZfDL,ZfDR,ZfUL,           & 
& ZfUR,ZfVWm,Amp)

Implicit None

Real(dp), Intent(in) :: MFd(3),MFd2(3),MFu(3),MFu2(3),MVWm,MVWm2

Complex(dp), Intent(in) :: cplcFuFdcVWmL(3,3),cplcFuFdcVWmR(3,3)

Complex(dp), Intent(in) :: ctcplcFuFdcVWmL(3,3),ctcplcFuFdcVWmR(3,3)

Complex(dp), Intent(in) :: ZfDL(3,3),ZfDR(3,3),ZfUL(3,3),ZfUR(3,3),ZfVWm

Complex(dp), Intent(out) :: Amp(4,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(4) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

Do gt1=1,3
  Do gt2=1,3
! External masses 
Mex1 = MFu(gt1) 
Mex2 = MFd(gt2) 
Mex3 = MVWm 
!----------------------------- 
! Coupling counter term 
!----------------------------- 
ZcoupT1L = ctcplcFuFdcVWmL(gt1,gt2) 
ZcoupT1R = ctcplcFuFdcVWmR(gt1,gt2)
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
Do i1=1,3
ZcoupT1L = ZcoupT1L + 0.5_dp*Conjg(ZfUL(i1,gt1))*cplcFuFdcVWmL(i1,gt2)
ZcoupT1R = ZcoupT1R + 0.5_dp*ZfUR(i1,gt1)*cplcFuFdcVWmR(i1,gt2)
End Do


! External Field 2 
Do i1=1,3
ZcoupT1L = ZcoupT1L + 0.5_dp*ZfDL(i1,gt2)*cplcFuFdcVWmL(gt1,i1)
ZcoupT1R = ZcoupT1R + 0.5_dp*Conjg(ZfDR(i1,gt2))*cplcFuFdcVWmR(gt1,i1)
End Do


! External Field 3 
ZcoupT1L = ZcoupT1L + 0.5_dp*ZfVWm*cplcFuFdcVWmL(gt1,gt2)
ZcoupT1R = ZcoupT1R + 0.5_dp*ZfVWm*cplcFuFdcVWmR(gt1,gt2)


! Getting the amplitude 
Call TreeAmp_FtoFV(Mex1,Mex2,Mex3,ZcoupT1R,ZcoupT1L,AmpC) 
Amp(:,gt1, gt2) = -AmpC 
  End Do
End Do
End Subroutine Amplitude_WAVE_gumTHDMII_FuToFdcVWm


Subroutine Amplitude_VERTEX_gumTHDMII_FuToFdcVWm(MAh,MFd,MFu,Mhh,MHm,MVG,             & 
& MVP,MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplcFdFdAhL,cplcFdFdAhR,    & 
& cplcFuFuAhL,cplcFuFuAhR,cplAhHmcVWm,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,               & 
& cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHmL,              & 
& cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,          & 
& cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplhhHmcVWm,               & 
& cplhhcVWmVWm,cplHmcVWmVP,cplHmcVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MFd(3),MFu(3),Mhh(2),MHm(2),MVG,MVP,MVWm,MVZ,MAh2(2),MFd2(3),MFu2(3),          & 
& Mhh2(2),MHm2(2),MVG2,MVP2,MVWm2,MVZ2

Complex(dp), Intent(in) :: cplcFdFdAhL(3,3,2),cplcFdFdAhR(3,3,2),cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),          & 
& cplAhHmcVWm(2,2),cplcFdFdhhL(3,3,2),cplcFdFdhhR(3,3,2),cplcFdFdVGL(3,3),               & 
& cplcFdFdVGR(3,3),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),  & 
& cplcFuFdcHmL(3,3,2),cplcFuFdcHmR(3,3,2),cplcFuFdcVWmL(3,3),cplcFuFdcVWmR(3,3),         & 
& cplcFuFuhhL(3,3,2),cplcFuFuhhR(3,3,2),cplcFuFuVGL(3,3),cplcFuFuVGR(3,3),               & 
& cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplhhHmcVWm(2,2),  & 
& cplhhcVWmVWm(2),cplHmcVWmVP(2),cplHmcVWmVZ(2),cplcVWmVPVWm,cplcVWmVWmVZ

Complex(dp), Intent(out) :: Amp(4,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(4) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,3
  Do gt2=1,3
Amp(:,gt1, gt2) = 0._dp 
! External masses 
Mex1 = MFu(gt1) 
Mex2 = MFd(gt2) 
Mex3 = MVWm 


! {Ah, bar[Fu], bar[Fd]}
Do i1=1,2
  Do i2=1,3
    Do i3=1,3
ML1 = MAh(i1) 
ML2 = MFu(i2) 
ML3 = MFd(i3) 
coup1L = cplcFuFuAhL(gt1,i2,i1)
coup1R = cplcFuFuAhR(gt1,i2,i1)
coup2L = cplcFdFdAhL(i3,gt2,i1)
coup2R = cplcFdFdAhR(i3,gt2,i1)
coup3L = cplcFuFdcVWmL(i2,i3)
coup3R = cplcFuFdcVWmR(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_SFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Fd, Hm, Ah}
Do i1=1,3
  Do i2=1,2
    Do i3=1,2
ML1 = MFd(i1) 
ML2 = MHm(i2) 
ML3 = MAh(i3) 
coup1L = cplcFuFdcHmL(gt1,i1,i2)
coup1R = cplcFuFdcHmR(gt1,i1,i2)
coup2L = cplcFdFdAhL(i1,gt2,i3)
coup2R = cplcFdFdAhR(i1,gt2,i3)
coup3 = cplAhHmcVWm(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_FSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Fd, Hm, hh}
Do i1=1,3
  Do i2=1,2
    Do i3=1,2
ML1 = MFd(i1) 
ML2 = MHm(i2) 
ML3 = Mhh(i3) 
coup1L = cplcFuFdcHmL(gt1,i1,i2)
coup1R = cplcFuFdcHmR(gt1,i1,i2)
coup2L = cplcFdFdhhL(i1,gt2,i3)
coup2R = cplcFdFdhhR(i1,gt2,i3)
coup3 = cplhhHmcVWm(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_FSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Fd, VWm, hh}
Do i1=1,3
    Do i3=1,2
ML1 = MFd(i1) 
ML2 = MVWm 
ML3 = Mhh(i3) 
coup1L = cplcFuFdcVWmL(gt1,i1)
coup1R = cplcFuFdcVWmR(gt1,i1)
coup2L = cplcFdFdhhL(i1,gt2,i3)
coup2R = cplcFdFdhhR(i1,gt2,i3)
coup3 = cplhhcVWmVWm(i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_FVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Fd, Hm, VP}
Do i1=1,3
  Do i2=1,2
ML1 = MFd(i1) 
ML2 = MHm(i2) 
ML3 = MVP 
coup1L = cplcFuFdcHmL(gt1,i1,i2)
coup1R = cplcFuFdcHmR(gt1,i1,i2)
coup2L = cplcFdFdVPL(i1,gt2)
coup2R = cplcFdFdVPR(i1,gt2)
coup3 = cplHmcVWmVP(i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_FSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Fd, VWm, VP}
Do i1=1,3
ML1 = MFd(i1) 
ML2 = MVWm 
ML3 = MVP 
coup1L = cplcFuFdcVWmL(gt1,i1)
coup1R = cplcFuFdcVWmR(gt1,i1)
coup2L = cplcFdFdVPL(i1,gt2)
coup2R = cplcFdFdVPR(i1,gt2)
coup3 = -cplcVWmVPVWm
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_FVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {Fd, Hm, VZ}
Do i1=1,3
  Do i2=1,2
ML1 = MFd(i1) 
ML2 = MHm(i2) 
ML3 = MVZ 
coup1L = cplcFuFdcHmL(gt1,i1,i2)
coup1R = cplcFuFdcHmR(gt1,i1,i2)
coup2L = cplcFdFdVZL(i1,gt2)
coup2R = cplcFdFdVZR(i1,gt2)
coup3 = cplHmcVWmVZ(i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_FSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Fd, VWm, VZ}
Do i1=1,3
ML1 = MFd(i1) 
ML2 = MVWm 
ML3 = MVZ 
coup1L = cplcFuFdcVWmL(gt1,i1)
coup1R = cplcFuFdcVWmR(gt1,i1)
coup2L = cplcFdFdVZL(i1,gt2)
coup2R = cplcFdFdVZR(i1,gt2)
coup3 = cplcVWmVWmVZ
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_FVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {Fu, Ah, conj[Hm]}
Do i1=1,3
  Do i2=1,2
    Do i3=1,2
ML1 = MFu(i1) 
ML2 = MAh(i2) 
ML3 = MHm(i3) 
coup1L = cplcFuFuAhL(gt1,i1,i2)
coup1R = cplcFuFuAhR(gt1,i1,i2)
coup2L = cplcFuFdcHmL(i1,gt2,i3)
coup2R = cplcFuFdcHmR(i1,gt2,i3)
coup3 = -cplAhHmcVWm(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_FSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Fu, hh, conj[Hm]}
Do i1=1,3
  Do i2=1,2
    Do i3=1,2
ML1 = MFu(i1) 
ML2 = Mhh(i2) 
ML3 = MHm(i3) 
coup1L = cplcFuFuhhL(gt1,i1,i2)
coup1R = cplcFuFuhhR(gt1,i1,i2)
coup2L = cplcFuFdcHmL(i1,gt2,i3)
coup2R = cplcFuFdcHmR(i1,gt2,i3)
coup3 = -cplhhHmcVWm(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_FSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Fu, VP, conj[Hm]}
Do i1=1,3
    Do i3=1,2
ML1 = MFu(i1) 
ML2 = MVP 
ML3 = MHm(i3) 
coup1L = cplcFuFuVPL(gt1,i1)
coup1R = cplcFuFuVPR(gt1,i1)
coup2L = cplcFuFdcHmL(i1,gt2,i3)
coup2R = cplcFuFdcHmR(i1,gt2,i3)
coup3 = cplHmcVWmVP(i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_FVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Fu, VZ, conj[Hm]}
Do i1=1,3
    Do i3=1,2
ML1 = MFu(i1) 
ML2 = MVZ 
ML3 = MHm(i3) 
coup1L = cplcFuFuVZL(gt1,i1)
coup1R = cplcFuFuVZR(gt1,i1)
coup2L = cplcFuFdcHmL(i1,gt2,i3)
coup2R = cplcFuFdcHmR(i1,gt2,i3)
coup3 = cplHmcVWmVZ(i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_FVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Fu, hh, conj[VWm]}
Do i1=1,3
  Do i2=1,2
ML1 = MFu(i1) 
ML2 = Mhh(i2) 
ML3 = MVWm 
coup1L = cplcFuFuhhL(gt1,i1,i2)
coup1R = cplcFuFuhhR(gt1,i1,i2)
coup2L = cplcFuFdcVWmL(i1,gt2)
coup2R = cplcFuFdcVWmR(i1,gt2)
coup3 = cplhhcVWmVWm(i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_FSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Fu, VP, conj[VWm]}
Do i1=1,3
ML1 = MFu(i1) 
ML2 = MVP 
ML3 = MVWm 
coup1L = cplcFuFuVPL(gt1,i1)
coup1R = cplcFuFuVPR(gt1,i1)
coup2L = cplcFuFdcVWmL(i1,gt2)
coup2R = cplcFuFdcVWmR(i1,gt2)
coup3 = cplcVWmVPVWm
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_FVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {Fu, VZ, conj[VWm]}
Do i1=1,3
ML1 = MFu(i1) 
ML2 = MVZ 
ML3 = MVWm 
coup1L = cplcFuFuVZL(gt1,i1)
coup1R = cplcFuFuVZR(gt1,i1)
coup2L = cplcFuFdcVWmL(i1,gt2)
coup2R = cplcFuFdcVWmR(i1,gt2)
coup3 = -cplcVWmVWmVZ
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_FVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {hh, bar[Fu], bar[Fd]}
Do i1=1,2
  Do i2=1,3
    Do i3=1,3
ML1 = Mhh(i1) 
ML2 = MFu(i2) 
ML3 = MFd(i3) 
coup1L = cplcFuFuhhL(gt1,i2,i1)
coup1R = cplcFuFuhhR(gt1,i2,i1)
coup2L = cplcFdFdhhL(i3,gt2,i1)
coup2R = cplcFdFdhhR(i3,gt2,i1)
coup3L = cplcFuFdcVWmL(i2,i3)
coup3R = cplcFuFdcVWmR(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_SFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {VG, bar[Fu], bar[Fd]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVG 
ML2 = MFu(i2) 
ML3 = MFd(i3) 
coup1L = cplcFuFuVGL(gt1,i2)
coup1R = cplcFuFuVGR(gt1,i2)
coup2L = cplcFdFdVGL(i3,gt2)
coup2R = cplcFdFdVGR(i3,gt2)
coup3L = cplcFuFdcVWmL(i2,i3)
coup3R = cplcFuFdcVWmR(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(4._dp/3._dp)*AmpC 
    End Do
  End Do


! {VP, bar[Fu], bar[Fd]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVP 
ML2 = MFu(i2) 
ML3 = MFd(i3) 
coup1L = cplcFuFuVPL(gt1,i2)
coup1R = cplcFuFuVPR(gt1,i2)
coup2L = cplcFdFdVPL(i3,gt2)
coup2R = cplcFdFdVPR(i3,gt2)
coup3L = cplcFuFdcVWmL(i2,i3)
coup3R = cplcFuFdcVWmR(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VZ, bar[Fu], bar[Fd]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVZ 
ML2 = MFu(i2) 
ML3 = MFd(i3) 
coup1L = cplcFuFuVZL(gt1,i2)
coup1R = cplcFuFuVZR(gt1,i2)
coup2L = cplcFdFdVZL(i3,gt2)
coup2R = cplcFdFdVZR(i3,gt2)
coup3L = cplcFuFdcVWmL(i2,i3)
coup3R = cplcFuFdcVWmR(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do
  End Do
End Do
End Subroutine Amplitude_VERTEX_gumTHDMII_FuToFdcVWm


Subroutine Amplitude_IR_VERTEX_gumTHDMII_FuToFdcVWm(MAh,MFd,MFu,Mhh,MHm,              & 
& MVG,MVP,MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplcFdFdAhL,            & 
& cplcFdFdAhR,cplcFuFuAhL,cplcFuFuAhR,cplAhHmcVWm,cplcFdFdhhL,cplcFdFdhhR,               & 
& cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,               & 
& cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,         & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplhhHmcVWm,cplhhcVWmVWm,cplHmcVWmVP,cplHmcVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MFd(3),MFu(3),Mhh(2),MHm(2),MVG,MVP,MVWm,MVZ,MAh2(2),MFd2(3),MFu2(3),          & 
& Mhh2(2),MHm2(2),MVG2,MVP2,MVWm2,MVZ2

Complex(dp), Intent(in) :: cplcFdFdAhL(3,3,2),cplcFdFdAhR(3,3,2),cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),          & 
& cplAhHmcVWm(2,2),cplcFdFdhhL(3,3,2),cplcFdFdhhR(3,3,2),cplcFdFdVGL(3,3),               & 
& cplcFdFdVGR(3,3),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),  & 
& cplcFuFdcHmL(3,3,2),cplcFuFdcHmR(3,3,2),cplcFuFdcVWmL(3,3),cplcFuFdcVWmR(3,3),         & 
& cplcFuFuhhL(3,3,2),cplcFuFuhhR(3,3,2),cplcFuFuVGL(3,3),cplcFuFuVGR(3,3),               & 
& cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplhhHmcVWm(2,2),  & 
& cplhhcVWmVWm(2),cplHmcVWmVP(2),cplHmcVWmVZ(2),cplcVWmVPVWm,cplcVWmVWmVZ

Complex(dp), Intent(out) :: Amp(4,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(4) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,3
  Do gt2=1,3
Amp(:,gt1, gt2) = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = MFu(gt1) 
Mex2 = MFd(gt2) 
Mex3 = MVWm 


! {Fd, Hm, VP}
Do i1=1,3
  Do i2=1,2
ML1 = MFd(i1) 
ML2 = MHm(i2) 
ML3 = MVP 
coup1L = cplcFuFdcHmL(gt1,i1,i2)
coup1R = cplcFuFdcHmR(gt1,i1,i2)
coup2L = cplcFdFdVPL(i1,gt2)
coup2R = cplcFdFdVPR(i1,gt2)
coup3 = cplHmcVWmVP(i2)
Call Amp_VERTEX_FtoFV_Topology1_FSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Fd, VWm, VP}
Do i1=1,3
ML1 = MFd(i1) 
ML2 = MVWm 
ML3 = MVP 
coup1L = cplcFuFdcVWmL(gt1,i1)
coup1R = cplcFuFdcVWmR(gt1,i1)
coup2L = cplcFdFdVPL(i1,gt2)
coup2R = cplcFdFdVPR(i1,gt2)
coup3 = -cplcVWmVPVWm
Call Amp_VERTEX_FtoFV_Topology1_FVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {Fu, VP, conj[Hm]}
Do i1=1,3
    Do i3=1,2
ML1 = MFu(i1) 
ML2 = MVP 
ML3 = MHm(i3) 
coup1L = cplcFuFuVPL(gt1,i1)
coup1R = cplcFuFuVPR(gt1,i1)
coup2L = cplcFuFdcHmL(i1,gt2,i3)
coup2R = cplcFuFdcHmR(i1,gt2,i3)
coup3 = cplHmcVWmVP(i3)
Call Amp_VERTEX_FtoFV_Topology1_FVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Fu, VP, conj[VWm]}
Do i1=1,3
ML1 = MFu(i1) 
ML2 = MVP 
ML3 = MVWm 
coup1L = cplcFuFuVPL(gt1,i1)
coup1R = cplcFuFuVPR(gt1,i1)
coup2L = cplcFuFdcVWmL(i1,gt2)
coup2R = cplcFuFdcVWmR(i1,gt2)
coup3 = cplcVWmVPVWm
Call Amp_VERTEX_FtoFV_Topology1_FVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {VG, bar[Fu], bar[Fd]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVG 
ML2 = MFu(i2) 
ML3 = MFd(i3) 
coup1L = cplcFuFuVGL(gt1,i2)
coup1R = cplcFuFuVGR(gt1,i2)
coup2L = cplcFdFdVGL(i3,gt2)
coup2R = cplcFdFdVGR(i3,gt2)
coup3L = cplcFuFdcVWmL(i2,i3)
coup3R = cplcFuFdcVWmR(i2,i3)
Call Amp_VERTEX_FtoFV_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(4._dp/3._dp)*AmpC 
    End Do
  End Do


! {VP, bar[Fu], bar[Fd]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVP 
ML2 = MFu(i2) 
ML3 = MFd(i3) 
coup1L = cplcFuFuVPL(gt1,i2)
coup1R = cplcFuFuVPR(gt1,i2)
coup2L = cplcFdFdVPL(i3,gt2)
coup2R = cplcFdFdVPR(i3,gt2)
coup3L = cplcFuFdcVWmL(i2,i3)
coup3R = cplcFuFdcVWmR(i2,i3)
Call Amp_VERTEX_FtoFV_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do
  End Do
End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_gumTHDMII_FuToFdcVWm


Subroutine Amplitude_Tree_gumTHDMII_FuToFuhh(cplcFuFuhhL,cplcFuFuhhR,MFu,             & 
& Mhh,MFu2,Mhh2,Amp)

Implicit None

Real(dp), Intent(in) :: MFu(3),Mhh(2),MFu2(3),Mhh2(2)

Complex(dp), Intent(in) :: cplcFuFuhhL(3,3,2),cplcFuFuhhR(3,3,2)

Complex(dp) :: Amp(2,3,3,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 

Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,2
! External masses 
Mex1 = MFu(gt1) 
Mex2 = MFu(gt2) 
Mex3 = Mhh(gt3) 
! Tree-Level Vertex 
coupT1L = cplcFuFuhhL(gt1,gt2,gt3)
coupT1R = cplcFuFuhhR(gt1,gt2,gt3)
Call TreeAmp_FtoFS(Mex1,Mex2,Mex3,coupT1L,coupT1R,AmpC) 
! Colour and symmetry factor 
Amp(:,gt1, gt2, gt3) = AmpC 
    End Do
  End Do
End Do
End Subroutine Amplitude_Tree_gumTHDMII_FuToFuhh


Subroutine Gamma_Real_gumTHDMII_FuToFuhh(MLambda,em,gs,cplcFuFuhhL,cplcFuFuhhR,       & 
& MFu,Mhh,GammarealPhoton,GammarealGluon)

Implicit None

Complex(dp), Intent(in) :: cplcFuFuhhL(3,3,2),cplcFuFuhhR(3,3,2)

Real(dp), Intent(in) :: MFu(3),Mhh(2)

Real(dp), Intent(in) :: MLambda, em, gs 

Real(dp), Intent(out) :: GammarealPhoton(3,3,2), GammarealGluon(3,3,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 

Real(dp) :: Mloop1, Mloop2, Mloop3 
Complex(dp) :: CoupL, CoupR 
 
Do i1=1,3
  Do i2=1,3
    Do i3=1,2
CoupL = cplcFuFuhhL(i1,i2,i3)
CoupR = cplcFuFuhhR(i1,i2,i3)
Mex1 = MFu(i1)
Mex2 = MFu(i2)
Mex3 = Mhh(i3)
If (Abs(Mex1).gt.(Abs(Mex2)+Abs(Mex3))) Then 
 Call hardradiationFFS(Mex1,Mex2,Mex3,MLambda,em,4._dp/9._dp,4._dp/9._dp,0._dp,4._dp/9._dp,0._dp,0._dp,CoupL,CoupR,Gammarealphoton(i1,i2,i3),kont)
 Call hardradiationFFS(Mex1,Mex2,Mex3,MLambda,gs,4._dp/3._dp,4._dp/3._dp,0._dp,4._dp/3._dp,0._dp,0._dp,CoupL,CoupR,Gammarealgluon(i1,i2,i3),kont)
Else 
  GammarealGluon(i1,i2,i3) = 0._dp 
  GammarealPhoton(i1,i2,i3) = 0._dp 

End if 
    End Do
  End Do
End Do
End Subroutine Gamma_Real_gumTHDMII_FuToFuhh


Subroutine Amplitude_WAVE_gumTHDMII_FuToFuhh(cplcFuFuhhL,cplcFuFuhhR,ctcplcFuFuhhL,   & 
& ctcplcFuFuhhR,MFu,MFu2,Mhh,Mhh2,Zfhh,ZfUL,ZfUR,Amp)

Implicit None

Real(dp), Intent(in) :: MFu(3),MFu2(3),Mhh(2),Mhh2(2)

Complex(dp), Intent(in) :: cplcFuFuhhL(3,3,2),cplcFuFuhhR(3,3,2)

Complex(dp), Intent(in) :: ctcplcFuFuhhL(3,3,2),ctcplcFuFuhhR(3,3,2)

Complex(dp), Intent(in) :: Zfhh(2,2),ZfUL(3,3),ZfUR(3,3)

Complex(dp), Intent(out) :: Amp(2,3,3,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,2
! External masses 
Mex1 = MFu(gt1) 
Mex2 = MFu(gt2) 
Mex3 = Mhh(gt3) 
!----------------------------- 
! Coupling counter term 
!----------------------------- 
ZcoupT1L = ctcplcFuFuhhL(gt1,gt2,gt3) 
ZcoupT1R = ctcplcFuFuhhR(gt1,gt2,gt3) 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
Do i1=1,3
ZcoupT1L = ZcoupT1L + 0.5_dp*ZfUR(i1,gt1)*cplcFuFuhhL(i1,gt2,gt3)
ZcoupT1R = ZcoupT1R + 0.5_dp*Conjg(ZfUL(i1,gt1))*cplcFuFuhhR(i1,gt2,gt3)
End Do


! External Field 2 
Do i1=1,3
ZcoupT1L = ZcoupT1L + 0.5_dp*ZfUL(i1,gt2)*cplcFuFuhhL(gt1,i1,gt3)
ZcoupT1R = ZcoupT1R + 0.5_dp*Conjg(ZfUR(i1,gt2))*cplcFuFuhhR(gt1,i1,gt3)
End Do


! External Field 3 
Do i1=1,2
ZcoupT1L = ZcoupT1L + 0.5_dp*Zfhh(i1,gt3)*cplcFuFuhhL(gt1,gt2,i1)
ZcoupT1R = ZcoupT1R + 0.5_dp*Zfhh(i1,gt3)*cplcFuFuhhR(gt1,gt2,i1)
End Do


! Getting the amplitude 
Call TreeAmp_FtoFS(Mex1,Mex2,Mex3,ZcoupT1L,ZcoupT1R,AmpC) 
Amp(:,gt1, gt2, gt3) = AmpC 
    End Do
  End Do
End Do
End Subroutine Amplitude_WAVE_gumTHDMII_FuToFuhh


Subroutine Amplitude_VERTEX_gumTHDMII_FuToFuhh(MAh,MFd,MFu,Mhh,MHm,MVG,               & 
& MVP,MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplcFuFuAhL,      & 
& cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcHmL,cplcFuFdcHmR,     & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,           & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,             & 
& cplcFuFuVZL,cplcFuFuVZR,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,     & 
& cplhhVZVZ,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MFd(3),MFu(3),Mhh(2),MHm(2),MVG,MVP,MVWm,MVZ,MAh2(2),MFd2(3),MFu2(3),          & 
& Mhh2(2),MHm2(2),MVG2,MVP2,MVWm2,MVZ2

Complex(dp), Intent(in) :: cplAhAhhh(2,2,2),cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),cplAhhhhh(2,2,2),              & 
& cplAhhhVZ(2,2),cplcFdFdhhL(3,3,2),cplcFdFdhhR(3,3,2),cplcFuFdcHmL(3,3,2),              & 
& cplcFuFdcHmR(3,3,2),cplcFuFdcVWmL(3,3),cplcFuFdcVWmR(3,3),cplcFuFuhhL(3,3,2),          & 
& cplcFuFuhhR(3,3,2),cplcFdFuHmL(3,3,2),cplcFdFuHmR(3,3,2),cplcFuFuVGL(3,3),             & 
& cplcFuFuVGR(3,3),cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcFdFuVWmL(3,3),cplcFdFuVWmR(3,3),& 
& cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplhhhhhh(2,2,2),cplhhHmcHm(2,2,2),cplhhHmcVWm(2,2), & 
& cplhhcHmVWm(2,2),cplhhcVWmVWm(2),cplhhVZVZ(2)

Complex(dp), Intent(out) :: Amp(2,3,3,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,2
Amp(:,gt1, gt2, gt3) = 0._dp 
! External masses 
Mex1 = MFu(gt1) 
Mex2 = MFu(gt2) 
Mex3 = Mhh(gt3) 


! {Ah, bar[Fu], bar[Fu]}
Do i1=1,2
  Do i2=1,3
    Do i3=1,3
ML1 = MAh(i1) 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = cplcFuFuAhL(gt1,i2,i1)
coup1R = cplcFuFuAhR(gt1,i2,i1)
coup2L = cplcFuFuAhL(i3,gt2,i1)
coup2R = cplcFuFuAhR(i3,gt2,i1)
coup3L = cplcFuFuhhL(i2,i3,gt3)
coup3R = cplcFuFuhhR(i2,i3,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_SFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Fd, Hm, Hm}
Do i1=1,3
  Do i2=1,2
    Do i3=1,2
ML1 = MFd(i1) 
ML2 = MHm(i2) 
ML3 = MHm(i3) 
coup1L = cplcFuFdcHmL(gt1,i1,i2)
coup1R = cplcFuFdcHmR(gt1,i1,i2)
coup2L = cplcFdFuHmL(i1,gt2,i3)
coup2R = cplcFdFuHmR(i1,gt2,i3)
coup3 = cplhhHmcHm(gt3,i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Fd, VWm, Hm}
Do i1=1,3
    Do i3=1,2
ML1 = MFd(i1) 
ML2 = MVWm 
ML3 = MHm(i3) 
coup1L = -cplcFuFdcVWmR(gt1,i1)
coup1R = -cplcFuFdcVWmL(gt1,i1)
coup2L = cplcFdFuHmL(i1,gt2,i3)
coup2R = cplcFdFuHmR(i1,gt2,i3)
coup3 = -cplhhcHmVWm(gt3,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Fd, Hm, VWm}
Do i1=1,3
  Do i2=1,2
ML1 = MFd(i1) 
ML2 = MHm(i2) 
ML3 = MVWm 
coup1L = cplcFuFdcHmL(gt1,i1,i2)
coup1R = cplcFuFdcHmR(gt1,i1,i2)
coup2L = -cplcFdFuVWmR(i1,gt2)
coup2R = -cplcFdFuVWmL(i1,gt2)
coup3 = -cplhhHmcVWm(gt3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Fd, VWm, VWm}
Do i1=1,3
ML1 = MFd(i1) 
ML2 = MVWm 
ML3 = MVWm 
coup1L = -cplcFuFdcVWmR(gt1,i1)
coup1R = -cplcFuFdcVWmL(gt1,i1)
coup2L = -cplcFdFuVWmR(i1,gt2)
coup2R = -cplcFdFuVWmL(i1,gt2)
coup3 = cplhhcVWmVWm(gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
End Do


! {Fu, Ah, Ah}
Do i1=1,3
  Do i2=1,2
    Do i3=1,2
ML1 = MFu(i1) 
ML2 = MAh(i2) 
ML3 = MAh(i3) 
coup1L = cplcFuFuAhL(gt1,i1,i2)
coup1R = cplcFuFuAhR(gt1,i1,i2)
coup2L = cplcFuFuAhL(i1,gt2,i3)
coup2R = cplcFuFuAhR(i1,gt2,i3)
coup3 = cplAhAhhh(i3,i2,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Fu, hh, Ah}
Do i1=1,3
  Do i2=1,2
    Do i3=1,2
ML1 = MFu(i1) 
ML2 = Mhh(i2) 
ML3 = MAh(i3) 
coup1L = cplcFuFuhhL(gt1,i1,i2)
coup1R = cplcFuFuhhR(gt1,i1,i2)
coup2L = cplcFuFuAhL(i1,gt2,i3)
coup2R = cplcFuFuAhR(i1,gt2,i3)
coup3 = cplAhhhhh(i3,gt3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Fu, VZ, Ah}
Do i1=1,3
    Do i3=1,2
ML1 = MFu(i1) 
ML2 = MVZ 
ML3 = MAh(i3) 
coup1L = -cplcFuFuVZR(gt1,i1)
coup1R = -cplcFuFuVZL(gt1,i1)
coup2L = cplcFuFuAhL(i1,gt2,i3)
coup2R = cplcFuFuAhR(i1,gt2,i3)
coup3 = cplAhhhVZ(i3,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Fu, Ah, hh}
Do i1=1,3
  Do i2=1,2
    Do i3=1,2
ML1 = MFu(i1) 
ML2 = MAh(i2) 
ML3 = Mhh(i3) 
coup1L = cplcFuFuAhL(gt1,i1,i2)
coup1R = cplcFuFuAhR(gt1,i1,i2)
coup2L = cplcFuFuhhL(i1,gt2,i3)
coup2R = cplcFuFuhhR(i1,gt2,i3)
coup3 = cplAhhhhh(i2,gt3,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Fu, hh, hh}
Do i1=1,3
  Do i2=1,2
    Do i3=1,2
ML1 = MFu(i1) 
ML2 = Mhh(i2) 
ML3 = Mhh(i3) 
coup1L = cplcFuFuhhL(gt1,i1,i2)
coup1R = cplcFuFuhhR(gt1,i1,i2)
coup2L = cplcFuFuhhL(i1,gt2,i3)
coup2R = cplcFuFuhhR(i1,gt2,i3)
coup3 = cplhhhhhh(gt3,i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Fu, Ah, VZ}
Do i1=1,3
  Do i2=1,2
ML1 = MFu(i1) 
ML2 = MAh(i2) 
ML3 = MVZ 
coup1L = cplcFuFuAhL(gt1,i1,i2)
coup1R = cplcFuFuAhR(gt1,i1,i2)
coup2L = -cplcFuFuVZR(i1,gt2)
coup2R = -cplcFuFuVZL(i1,gt2)
coup3 = cplAhhhVZ(i2,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Fu, VZ, VZ}
Do i1=1,3
ML1 = MFu(i1) 
ML2 = MVZ 
ML3 = MVZ 
coup1L = -cplcFuFuVZR(gt1,i1)
coup1R = -cplcFuFuVZL(gt1,i1)
coup2L = -cplcFuFuVZR(i1,gt2)
coup2R = -cplcFuFuVZL(i1,gt2)
coup3 = cplhhVZVZ(gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
End Do


! {hh, bar[Fu], bar[Fu]}
Do i1=1,2
  Do i2=1,3
    Do i3=1,3
ML1 = Mhh(i1) 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = cplcFuFuhhL(gt1,i2,i1)
coup1R = cplcFuFuhhR(gt1,i2,i1)
coup2L = cplcFuFuhhL(i3,gt2,i1)
coup2R = cplcFuFuhhR(i3,gt2,i1)
coup3L = cplcFuFuhhL(i2,i3,gt3)
coup3R = cplcFuFuhhR(i2,i3,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_SFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {VG, bar[Fu], bar[Fu]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVG 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = -cplcFuFuVGR(gt1,i2)
coup1R = -cplcFuFuVGL(gt1,i2)
coup2L = -cplcFuFuVGR(i3,gt2)
coup2R = -cplcFuFuVGL(i3,gt2)
coup3L = cplcFuFuhhL(i2,i3,gt3)
coup3R = cplcFuFuhhR(i2,i3,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(4._dp/3._dp)*AmpC 
    End Do
  End Do


! {VP, bar[Fu], bar[Fu]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVP 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = -cplcFuFuVPR(gt1,i2)
coup1R = -cplcFuFuVPL(gt1,i2)
coup2L = -cplcFuFuVPR(i3,gt2)
coup2R = -cplcFuFuVPL(i3,gt2)
coup3L = cplcFuFuhhL(i2,i3,gt3)
coup3R = cplcFuFuhhR(i2,i3,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VZ, bar[Fu], bar[Fu]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVZ 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = -cplcFuFuVZR(gt1,i2)
coup1R = -cplcFuFuVZL(gt1,i2)
coup2L = -cplcFuFuVZR(i3,gt2)
coup2R = -cplcFuFuVZL(i3,gt2)
coup3L = cplcFuFuhhL(i2,i3,gt3)
coup3R = cplcFuFuhhR(i2,i3,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {conj[Hm], bar[Fd], bar[Fd]}
Do i1=1,2
  Do i2=1,3
    Do i3=1,3
ML1 = MHm(i1) 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFuFdcHmL(gt1,i2,i1)
coup1R = cplcFuFdcHmR(gt1,i2,i1)
coup2L = cplcFdFuHmL(i3,gt2,i1)
coup2R = cplcFdFuHmR(i3,gt2,i1)
coup3L = cplcFdFdhhL(i2,i3,gt3)
coup3R = cplcFdFdhhR(i2,i3,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_SFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {conj[VWm], bar[Fd], bar[Fd]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVWm 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = -cplcFuFdcVWmR(gt1,i2)
coup1R = -cplcFuFdcVWmL(gt1,i2)
coup2L = -cplcFdFuVWmR(i3,gt2)
coup2R = -cplcFdFuVWmL(i3,gt2)
coup3L = cplcFdFdhhL(i2,i3,gt3)
coup3R = cplcFdFdhhR(i2,i3,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
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
End Subroutine Amplitude_VERTEX_gumTHDMII_FuToFuhh


Subroutine Amplitude_IR_VERTEX_gumTHDMII_FuToFuhh(MAh,MFd,MFu,Mhh,MHm,MVG,            & 
& MVP,MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplAhAhhh,cplcFuFuAhL,      & 
& cplcFuFuAhR,cplAhhhhh,cplAhhhVZ,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdcHmL,cplcFuFdcHmR,     & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,           & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,             & 
& cplcFuFuVZL,cplcFuFuVZR,cplhhhhhh,cplhhHmcHm,cplhhHmcVWm,cplhhcHmVWm,cplhhcVWmVWm,     & 
& cplhhVZVZ,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MFd(3),MFu(3),Mhh(2),MHm(2),MVG,MVP,MVWm,MVZ,MAh2(2),MFd2(3),MFu2(3),          & 
& Mhh2(2),MHm2(2),MVG2,MVP2,MVWm2,MVZ2

Complex(dp), Intent(in) :: cplAhAhhh(2,2,2),cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),cplAhhhhh(2,2,2),              & 
& cplAhhhVZ(2,2),cplcFdFdhhL(3,3,2),cplcFdFdhhR(3,3,2),cplcFuFdcHmL(3,3,2),              & 
& cplcFuFdcHmR(3,3,2),cplcFuFdcVWmL(3,3),cplcFuFdcVWmR(3,3),cplcFuFuhhL(3,3,2),          & 
& cplcFuFuhhR(3,3,2),cplcFdFuHmL(3,3,2),cplcFdFuHmR(3,3,2),cplcFuFuVGL(3,3),             & 
& cplcFuFuVGR(3,3),cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcFdFuVWmL(3,3),cplcFdFuVWmR(3,3),& 
& cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplhhhhhh(2,2,2),cplhhHmcHm(2,2,2),cplhhHmcVWm(2,2), & 
& cplhhcHmVWm(2,2),cplhhcVWmVWm(2),cplhhVZVZ(2)

Complex(dp), Intent(out) :: Amp(2,3,3,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,2
Amp(:,gt1, gt2, gt3) = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = MFu(gt1) 
Mex2 = MFu(gt2) 
Mex3 = Mhh(gt3) 


! {VG, bar[Fu], bar[Fu]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVG 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = -cplcFuFuVGR(gt1,i2)
coup1R = -cplcFuFuVGL(gt1,i2)
coup2L = -cplcFuFuVGR(i3,gt2)
coup2R = -cplcFuFuVGL(i3,gt2)
coup3L = cplcFuFuhhL(i2,i3,gt3)
coup3R = cplcFuFuhhR(i2,i3,gt3)
Call Amp_VERTEX_FtoFS_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(4._dp/3._dp)*AmpC 
    End Do
  End Do


! {VP, bar[Fu], bar[Fu]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVP 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = -cplcFuFuVPR(gt1,i2)
coup1R = -cplcFuFuVPL(gt1,i2)
coup2L = -cplcFuFuVPR(i3,gt2)
coup2R = -cplcFuFuVPL(i3,gt2)
coup3L = cplcFuFuhhL(i2,i3,gt3)
coup3R = cplcFuFuhhR(i2,i3,gt3)
Call Amp_VERTEX_FtoFS_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
    End Do
  End Do
End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_gumTHDMII_FuToFuhh


Subroutine Amplitude_Tree_gumTHDMII_FuToFuVZ(cplcFuFuVZL,cplcFuFuVZR,MFu,             & 
& MVZ,MFu2,MVZ2,Amp)

Implicit None

Real(dp), Intent(in) :: MFu(3),MVZ,MFu2(3),MVZ2

Complex(dp), Intent(in) :: cplcFuFuVZL(3,3),cplcFuFuVZR(3,3)

Complex(dp) :: Amp(4,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(4) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 

Do gt1=1,3
  Do gt2=1,3
! External masses 
Mex1 = MFu(gt1) 
Mex2 = MFu(gt2) 
Mex3 = MVZ 
! Tree-Level Vertex 
coupT1L = cplcFuFuVZL(gt1,gt2)
coupT1R = cplcFuFuVZR(gt1,gt2)
Call TreeAmp_FtoFV(Mex1,Mex2,Mex3,coupT1R,coupT1L,AmpC) 
! Colour and symmetry factor 
Amp(:,gt1, gt2) = -AmpC 
  End Do
End Do
End Subroutine Amplitude_Tree_gumTHDMII_FuToFuVZ


Subroutine Gamma_Real_gumTHDMII_FuToFuVZ(MLambda,em,gs,cplcFuFuVZL,cplcFuFuVZR,       & 
& MFu,MVZ,GammarealPhoton,GammarealGluon)

Implicit None

Complex(dp), Intent(in) :: cplcFuFuVZL(3,3),cplcFuFuVZR(3,3)

Real(dp), Intent(in) :: MFu(3),MVZ

Real(dp), Intent(in) :: MLambda, em, gs 

Real(dp), Intent(out) :: GammarealPhoton(3,3), GammarealGluon(3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 

Real(dp) :: Mloop1, Mloop2, Mloop3 
Complex(dp) :: CoupL, CoupR 
 
Do i1=1,3
  Do i2=1,3
CoupL = cplcFuFuVZL(i1,i2)
CoupR = cplcFuFuVZR(i1,i2)
Mex1 = MFu(i1)
Mex2 = MFu(i2)
Mex3 = MVZ
If (Abs(Mex1).gt.(Abs(Mex2)+Abs(Mex3))) Then 
  Call hardphotonFFZ(Mex1,Mex2,Mex3,MLambda,2._dp/3._dp,2._dp/3._dp,CoupL,CoupR,(0,1)*em,GammaRealPhoton(i1,i2),kont)
  Call hardgluonFFZW(Mex1,Mex2,Mex3,MLambda,4._dp/3._dp,gs,CoupL,CoupR,Gammarealgluon(i1,i2),kont)
Else 
  GammarealGluon(i1,i2) = 0._dp 
  GammarealPhoton(i1,i2) = 0._dp 

End if 
  End Do
End Do
End Subroutine Gamma_Real_gumTHDMII_FuToFuVZ


Subroutine Amplitude_WAVE_gumTHDMII_FuToFuVZ(cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,     & 
& cplcFuFuVZR,ctcplcFuFuVPL,ctcplcFuFuVPR,ctcplcFuFuVZL,ctcplcFuFuVZR,MFu,               & 
& MFu2,MVP,MVP2,MVZ,MVZ2,ZfUL,ZfUR,ZfVPVZ,ZfVZ,Amp)

Implicit None

Real(dp), Intent(in) :: MFu(3),MFu2(3),MVP,MVP2,MVZ,MVZ2

Complex(dp), Intent(in) :: cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3)

Complex(dp), Intent(in) :: ctcplcFuFuVPL(3,3),ctcplcFuFuVPR(3,3),ctcplcFuFuVZL(3,3),ctcplcFuFuVZR(3,3)

Complex(dp), Intent(in) :: ZfUL(3,3),ZfUR(3,3),ZfVPVZ,ZfVZ

Complex(dp), Intent(out) :: Amp(4,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(4) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

Do gt1=1,3
  Do gt2=1,3
! External masses 
Mex1 = MFu(gt1) 
Mex2 = MFu(gt2) 
Mex3 = MVZ 
!----------------------------- 
! Coupling counter term 
!----------------------------- 
ZcoupT1L = ctcplcFuFuVZL(gt1,gt2) 
ZcoupT1R = ctcplcFuFuVZR(gt1,gt2)
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
Do i1=1,3
ZcoupT1L = ZcoupT1L + 0.5_dp*Conjg(ZfUL(i1,gt1))*cplcFuFuVZL(i1,gt2)
ZcoupT1R = ZcoupT1R + 0.5_dp*ZfUR(i1,gt1)*cplcFuFuVZR(i1,gt2)
End Do


! External Field 2 
Do i1=1,3
ZcoupT1L = ZcoupT1L + 0.5_dp*ZfUL(i1,gt2)*cplcFuFuVZL(gt1,i1)
ZcoupT1R = ZcoupT1R + 0.5_dp*Conjg(ZfUR(i1,gt2))*cplcFuFuVZR(gt1,i1)
End Do


! External Field 3 
ZcoupT1L = ZcoupT1L + 0.5_dp*ZfVPVZ*cplcFuFuVPL(gt1,gt2)
ZcoupT1R = ZcoupT1R + 0.5_dp*ZfVPVZ*cplcFuFuVPR(gt1,gt2)
ZcoupT1L = ZcoupT1L + 0.5_dp*ZfVZ*cplcFuFuVZL(gt1,gt2)
ZcoupT1R = ZcoupT1R + 0.5_dp*ZfVZ*cplcFuFuVZR(gt1,gt2)


! Getting the amplitude 
Call TreeAmp_FtoFV(Mex1,Mex2,Mex3,ZcoupT1R,ZcoupT1L,AmpC) 
Amp(:,gt1, gt2) = -AmpC 
  End Do
End Do
End Subroutine Amplitude_WAVE_gumTHDMII_FuToFuVZ


Subroutine Amplitude_VERTEX_gumTHDMII_FuToFuVZ(MAh,MFd,MFu,Mhh,MHm,MVG,               & 
& MVP,MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplcFuFuAhL,cplcFuFuAhR,    & 
& cplAhhhVZ,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,             & 
& cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,cplcFuFuVGL,             & 
& cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,             & 
& cplcFuFuVZR,cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVWmVZ,cplcVWmVWmVZ,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MFd(3),MFu(3),Mhh(2),MHm(2),MVG,MVP,MVWm,MVZ,MAh2(2),MFd2(3),MFu2(3),          & 
& Mhh2(2),MHm2(2),MVG2,MVP2,MVWm2,MVZ2

Complex(dp), Intent(in) :: cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),cplAhhhVZ(2,2),cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),& 
& cplcFuFdcHmL(3,3,2),cplcFuFdcHmR(3,3,2),cplcFuFdcVWmL(3,3),cplcFuFdcVWmR(3,3),         & 
& cplcFuFuhhL(3,3,2),cplcFuFuhhR(3,3,2),cplcFdFuHmL(3,3,2),cplcFdFuHmR(3,3,2),           & 
& cplcFuFuVGL(3,3),cplcFuFuVGR(3,3),cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcFdFuVWmL(3,3), & 
& cplcFdFuVWmR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplhhVZVZ(2),cplHmcHmVZ(2,2),      & 
& cplHmcVWmVZ(2),cplcHmVWmVZ(2),cplcVWmVWmVZ

Complex(dp), Intent(out) :: Amp(4,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(4) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,3
  Do gt2=1,3
Amp(:,gt1, gt2) = 0._dp 
! External masses 
Mex1 = MFu(gt1) 
Mex2 = MFu(gt2) 
Mex3 = MVZ 


! {Ah, bar[Fu], bar[Fu]}
Do i1=1,2
  Do i2=1,3
    Do i3=1,3
ML1 = MAh(i1) 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = cplcFuFuAhL(gt1,i2,i1)
coup1R = cplcFuFuAhR(gt1,i2,i1)
coup2L = cplcFuFuAhL(i3,gt2,i1)
coup2R = cplcFuFuAhR(i3,gt2,i1)
coup3L = cplcFuFuVZL(i2,i3)
coup3R = cplcFuFuVZR(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_SFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Fd, Hm, Hm}
Do i1=1,3
  Do i2=1,2
    Do i3=1,2
ML1 = MFd(i1) 
ML2 = MHm(i2) 
ML3 = MHm(i3) 
coup1L = cplcFuFdcHmL(gt1,i1,i2)
coup1R = cplcFuFdcHmR(gt1,i1,i2)
coup2L = cplcFdFuHmL(i1,gt2,i3)
coup2R = cplcFdFuHmR(i1,gt2,i3)
coup3 = -cplHmcHmVZ(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_FSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Fd, VWm, Hm}
Do i1=1,3
    Do i3=1,2
ML1 = MFd(i1) 
ML2 = MVWm 
ML3 = MHm(i3) 
coup1L = cplcFuFdcVWmL(gt1,i1)
coup1R = cplcFuFdcVWmR(gt1,i1)
coup2L = cplcFdFuHmL(i1,gt2,i3)
coup2R = cplcFdFuHmR(i1,gt2,i3)
coup3 = cplcHmVWmVZ(i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_FVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Fd, Hm, VWm}
Do i1=1,3
  Do i2=1,2
ML1 = MFd(i1) 
ML2 = MHm(i2) 
ML3 = MVWm 
coup1L = cplcFuFdcHmL(gt1,i1,i2)
coup1R = cplcFuFdcHmR(gt1,i1,i2)
coup2L = cplcFdFuVWmL(i1,gt2)
coup2R = cplcFdFuVWmR(i1,gt2)
coup3 = cplHmcVWmVZ(i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_FSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Fd, VWm, VWm}
Do i1=1,3
ML1 = MFd(i1) 
ML2 = MVWm 
ML3 = MVWm 
coup1L = cplcFuFdcVWmL(gt1,i1)
coup1R = cplcFuFdcVWmR(gt1,i1)
coup2L = cplcFdFuVWmL(i1,gt2)
coup2R = cplcFdFuVWmR(i1,gt2)
coup3 = -cplcVWmVWmVZ
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_FVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {Fu, hh, Ah}
Do i1=1,3
  Do i2=1,2
    Do i3=1,2
ML1 = MFu(i1) 
ML2 = Mhh(i2) 
ML3 = MAh(i3) 
coup1L = cplcFuFuhhL(gt1,i1,i2)
coup1R = cplcFuFuhhR(gt1,i1,i2)
coup2L = cplcFuFuAhL(i1,gt2,i3)
coup2R = cplcFuFuAhR(i1,gt2,i3)
coup3 = cplAhhhVZ(i3,i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_FSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Fu, Ah, hh}
Do i1=1,3
  Do i2=1,2
    Do i3=1,2
ML1 = MFu(i1) 
ML2 = MAh(i2) 
ML3 = Mhh(i3) 
coup1L = cplcFuFuAhL(gt1,i1,i2)
coup1R = cplcFuFuAhR(gt1,i1,i2)
coup2L = cplcFuFuhhL(i1,gt2,i3)
coup2R = cplcFuFuhhR(i1,gt2,i3)
coup3 = -cplAhhhVZ(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_FSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Fu, VZ, hh}
Do i1=1,3
    Do i3=1,2
ML1 = MFu(i1) 
ML2 = MVZ 
ML3 = Mhh(i3) 
coup1L = cplcFuFuVZL(gt1,i1)
coup1R = cplcFuFuVZR(gt1,i1)
coup2L = cplcFuFuhhL(i1,gt2,i3)
coup2R = cplcFuFuhhR(i1,gt2,i3)
coup3 = cplhhVZVZ(i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_FVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Fu, hh, VZ}
Do i1=1,3
  Do i2=1,2
ML1 = MFu(i1) 
ML2 = Mhh(i2) 
ML3 = MVZ 
coup1L = cplcFuFuhhL(gt1,i1,i2)
coup1R = cplcFuFuhhR(gt1,i1,i2)
coup2L = cplcFuFuVZL(i1,gt2)
coup2R = cplcFuFuVZR(i1,gt2)
coup3 = cplhhVZVZ(i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_FSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {hh, bar[Fu], bar[Fu]}
Do i1=1,2
  Do i2=1,3
    Do i3=1,3
ML1 = Mhh(i1) 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = cplcFuFuhhL(gt1,i2,i1)
coup1R = cplcFuFuhhR(gt1,i2,i1)
coup2L = cplcFuFuhhL(i3,gt2,i1)
coup2R = cplcFuFuhhR(i3,gt2,i1)
coup3L = cplcFuFuVZL(i2,i3)
coup3R = cplcFuFuVZR(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_SFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {VG, bar[Fu], bar[Fu]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVG 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = cplcFuFuVGL(gt1,i2)
coup1R = cplcFuFuVGR(gt1,i2)
coup2L = cplcFuFuVGL(i3,gt2)
coup2R = cplcFuFuVGR(i3,gt2)
coup3L = cplcFuFuVZL(i2,i3)
coup3R = cplcFuFuVZR(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(4._dp/3._dp)*AmpC 
    End Do
  End Do


! {VP, bar[Fu], bar[Fu]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVP 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = cplcFuFuVPL(gt1,i2)
coup1R = cplcFuFuVPR(gt1,i2)
coup2L = cplcFuFuVPL(i3,gt2)
coup2R = cplcFuFuVPR(i3,gt2)
coup3L = cplcFuFuVZL(i2,i3)
coup3R = cplcFuFuVZR(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VZ, bar[Fu], bar[Fu]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVZ 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = cplcFuFuVZL(gt1,i2)
coup1R = cplcFuFuVZR(gt1,i2)
coup2L = cplcFuFuVZL(i3,gt2)
coup2R = cplcFuFuVZR(i3,gt2)
coup3L = cplcFuFuVZL(i2,i3)
coup3R = cplcFuFuVZR(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {conj[Hm], bar[Fd], bar[Fd]}
Do i1=1,2
  Do i2=1,3
    Do i3=1,3
ML1 = MHm(i1) 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFuFdcHmL(gt1,i2,i1)
coup1R = cplcFuFdcHmR(gt1,i2,i1)
coup2L = cplcFdFuHmL(i3,gt2,i1)
coup2R = cplcFdFuHmR(i3,gt2,i1)
coup3L = cplcFdFdVZL(i2,i3)
coup3R = cplcFdFdVZR(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_SFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {conj[VWm], bar[Fd], bar[Fd]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVWm 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFuFdcVWmL(gt1,i2)
coup1R = cplcFuFdcVWmR(gt1,i2)
coup2L = cplcFdFuVWmL(i3,gt2)
coup2R = cplcFdFuVWmR(i3,gt2)
coup3L = cplcFdFdVZL(i2,i3)
coup3R = cplcFdFdVZR(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do
  End Do
End Do
End Subroutine Amplitude_VERTEX_gumTHDMII_FuToFuVZ


Subroutine Amplitude_IR_VERTEX_gumTHDMII_FuToFuVZ(MAh,MFd,MFu,Mhh,MHm,MVG,            & 
& MVP,MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplcFuFuAhL,cplcFuFuAhR,    & 
& cplAhhhVZ,cplcFdFdVZL,cplcFdFdVZR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,             & 
& cplcFuFdcVWmR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,cplcFuFuVGL,             & 
& cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,             & 
& cplcFuFuVZR,cplhhVZVZ,cplHmcHmVZ,cplHmcVWmVZ,cplcHmVWmVZ,cplcVWmVWmVZ,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MFd(3),MFu(3),Mhh(2),MHm(2),MVG,MVP,MVWm,MVZ,MAh2(2),MFd2(3),MFu2(3),          & 
& Mhh2(2),MHm2(2),MVG2,MVP2,MVWm2,MVZ2

Complex(dp), Intent(in) :: cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),cplAhhhVZ(2,2),cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),& 
& cplcFuFdcHmL(3,3,2),cplcFuFdcHmR(3,3,2),cplcFuFdcVWmL(3,3),cplcFuFdcVWmR(3,3),         & 
& cplcFuFuhhL(3,3,2),cplcFuFuhhR(3,3,2),cplcFdFuHmL(3,3,2),cplcFdFuHmR(3,3,2),           & 
& cplcFuFuVGL(3,3),cplcFuFuVGR(3,3),cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcFdFuVWmL(3,3), & 
& cplcFdFuVWmR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplhhVZVZ(2),cplHmcHmVZ(2,2),      & 
& cplHmcVWmVZ(2),cplcHmVWmVZ(2),cplcVWmVWmVZ

Complex(dp), Intent(out) :: Amp(4,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(4) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,3
  Do gt2=1,3
Amp(:,gt1, gt2) = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = MFu(gt1) 
Mex2 = MFu(gt2) 
Mex3 = MVZ 


! {VG, bar[Fu], bar[Fu]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVG 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = cplcFuFuVGL(gt1,i2)
coup1R = cplcFuFuVGR(gt1,i2)
coup2L = cplcFuFuVGL(i3,gt2)
coup2R = cplcFuFuVGR(i3,gt2)
coup3L = cplcFuFuVZL(i2,i3)
coup3R = cplcFuFuVZR(i2,i3)
Call Amp_VERTEX_FtoFV_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(4._dp/3._dp)*AmpC 
    End Do
  End Do


! {VP, bar[Fu], bar[Fu]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVP 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = cplcFuFuVPL(gt1,i2)
coup1R = cplcFuFuVPR(gt1,i2)
coup2L = cplcFuFuVPL(i3,gt2)
coup2R = cplcFuFuVPR(i3,gt2)
coup3L = cplcFuFuVZL(i2,i3)
coup3R = cplcFuFuVZR(i2,i3)
Call Amp_VERTEX_FtoFV_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do
  End Do
End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_gumTHDMII_FuToFuVZ


Subroutine Amplitude_WAVE_gumTHDMII_FuToFuVG(cplcFuFuVGL,cplcFuFuVGR,ctcplcFuFuVGL,   & 
& ctcplcFuFuVGR,MFu,MFu2,MVG,MVG2,ZfUL,ZfUR,ZfVG,Amp)

Implicit None

Real(dp), Intent(in) :: MFu(3),MFu2(3),MVG,MVG2

Complex(dp), Intent(in) :: cplcFuFuVGL(3,3),cplcFuFuVGR(3,3)

Complex(dp), Intent(in) :: ctcplcFuFuVGL(3,3),ctcplcFuFuVGR(3,3)

Complex(dp), Intent(in) :: ZfUL(3,3),ZfUR(3,3),ZfVG

Complex(dp), Intent(out) :: Amp(4,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(4) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

Do gt1=1,3
  Do gt2=1,3
! External masses 
Mex1 = MFu(gt1) 
Mex2 = MFu(gt2) 
Mex3 = MVG 
!----------------------------- 
! Coupling counter term 
!----------------------------- 
ZcoupT1L = ctcplcFuFuVGL(gt1,gt2) 
ZcoupT1R = ctcplcFuFuVGR(gt1,gt2)
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
Do i1=1,3
ZcoupT1L = ZcoupT1L + 0.5_dp*Conjg(ZfUL(i1,gt1))*cplcFuFuVGL(i1,gt2)
ZcoupT1R = ZcoupT1R + 0.5_dp*ZfUR(i1,gt1)*cplcFuFuVGR(i1,gt2)
End Do


! External Field 2 
Do i1=1,3
ZcoupT1L = ZcoupT1L + 0.5_dp*ZfUL(i1,gt2)*cplcFuFuVGL(gt1,i1)
ZcoupT1R = ZcoupT1R + 0.5_dp*Conjg(ZfUR(i1,gt2))*cplcFuFuVGR(gt1,i1)
End Do


! External Field 3 


! Getting the amplitude 
Call TreeAmp_FtoFV(Mex1,Mex2,Mex3,ZcoupT1R,ZcoupT1L,AmpC) 
Amp(:,gt1, gt2) = -AmpC 
  End Do
End Do
End Subroutine Amplitude_WAVE_gumTHDMII_FuToFuVG


Subroutine Amplitude_VERTEX_gumTHDMII_FuToFuVG(MAh,MFd,MFu,Mhh,MHm,MVG,               & 
& MVP,MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplcFuFuAhL,cplcFuFuAhR,    & 
& cplcFdFdVGL,cplcFdFdVGR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,         & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,cplcFuFuVGL,cplcFuFuVGR,               & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,             & 
& cplVGVGVG,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MFd(3),MFu(3),Mhh(2),MHm(2),MVG,MVP,MVWm,MVZ,MAh2(2),MFd2(3),MFu2(3),          & 
& Mhh2(2),MHm2(2),MVG2,MVP2,MVWm2,MVZ2

Complex(dp), Intent(in) :: cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),              & 
& cplcFuFdcHmL(3,3,2),cplcFuFdcHmR(3,3,2),cplcFuFdcVWmL(3,3),cplcFuFdcVWmR(3,3),         & 
& cplcFuFuhhL(3,3,2),cplcFuFuhhR(3,3,2),cplcFdFuHmL(3,3,2),cplcFdFuHmR(3,3,2),           & 
& cplcFuFuVGL(3,3),cplcFuFuVGR(3,3),cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcFdFuVWmL(3,3), & 
& cplcFdFuVWmR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplVGVGVG

Complex(dp), Intent(out) :: Amp(4,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(4) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,3
  Do gt2=1,3
Amp(:,gt1, gt2) = 0._dp 
! External masses 
Mex1 = MFu(gt1) 
Mex2 = MFu(gt2) 
Mex3 = MVG 


! {Ah, bar[Fu], bar[Fu]}
Do i1=1,2
  Do i2=1,3
    Do i3=1,3
ML1 = MAh(i1) 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = cplcFuFuAhL(gt1,i2,i1)
coup1R = cplcFuFuAhR(gt1,i2,i1)
coup2L = cplcFuFuAhL(i3,gt2,i1)
coup2R = cplcFuFuAhR(i3,gt2,i1)
coup3L = cplcFuFuVGL(i2,i3)
coup3R = cplcFuFuVGR(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_SFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Fu, VG, VG}
Do i1=1,3
ML1 = MFu(i1) 
ML2 = MVG 
ML3 = MVG 
coup1L = cplcFuFuVGL(gt1,i1)
coup1R = cplcFuFuVGR(gt1,i1)
coup2L = cplcFuFuVGL(i1,gt2)
coup2R = cplcFuFuVGR(i1,gt2)
coup3 = cplVGVGVG
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_FVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(-3._dp/2._dp*(0.,1._dp))*AmpC 
End Do


! {hh, bar[Fu], bar[Fu]}
Do i1=1,2
  Do i2=1,3
    Do i3=1,3
ML1 = Mhh(i1) 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = cplcFuFuhhL(gt1,i2,i1)
coup1R = cplcFuFuhhR(gt1,i2,i1)
coup2L = cplcFuFuhhL(i3,gt2,i1)
coup2R = cplcFuFuhhR(i3,gt2,i1)
coup3L = cplcFuFuVGL(i2,i3)
coup3R = cplcFuFuVGR(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_SFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {VG, bar[Fu], bar[Fu]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVG 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = cplcFuFuVGL(gt1,i2)
coup1R = cplcFuFuVGR(gt1,i2)
coup2L = cplcFuFuVGL(i3,gt2)
coup2R = cplcFuFuVGR(i3,gt2)
coup3L = cplcFuFuVGL(i2,i3)
coup3R = cplcFuFuVGR(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(-1._dp/6._dp)*AmpC 
    End Do
  End Do


! {VP, bar[Fu], bar[Fu]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVP 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = cplcFuFuVPL(gt1,i2)
coup1R = cplcFuFuVPR(gt1,i2)
coup2L = cplcFuFuVPL(i3,gt2)
coup2R = cplcFuFuVPR(i3,gt2)
coup3L = cplcFuFuVGL(i2,i3)
coup3R = cplcFuFuVGR(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VZ, bar[Fu], bar[Fu]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVZ 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = cplcFuFuVZL(gt1,i2)
coup1R = cplcFuFuVZR(gt1,i2)
coup2L = cplcFuFuVZL(i3,gt2)
coup2R = cplcFuFuVZR(i3,gt2)
coup3L = cplcFuFuVGL(i2,i3)
coup3R = cplcFuFuVGR(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {conj[Hm], bar[Fd], bar[Fd]}
Do i1=1,2
  Do i2=1,3
    Do i3=1,3
ML1 = MHm(i1) 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFuFdcHmL(gt1,i2,i1)
coup1R = cplcFuFdcHmR(gt1,i2,i1)
coup2L = cplcFdFuHmL(i3,gt2,i1)
coup2R = cplcFdFuHmR(i3,gt2,i1)
coup3L = cplcFdFdVGL(i2,i3)
coup3R = cplcFdFdVGR(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_SFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {conj[VWm], bar[Fd], bar[Fd]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVWm 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFuFdcVWmL(gt1,i2)
coup1R = cplcFuFdcVWmR(gt1,i2)
coup2L = cplcFdFuVWmL(i3,gt2)
coup2R = cplcFdFuVWmR(i3,gt2)
coup3L = cplcFdFdVGL(i2,i3)
coup3R = cplcFdFdVGR(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do
  End Do
End Do
End Subroutine Amplitude_VERTEX_gumTHDMII_FuToFuVG


Subroutine Amplitude_IR_VERTEX_gumTHDMII_FuToFuVG(MAh,MFd,MFu,Mhh,MHm,MVG,            & 
& MVP,MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplcFuFuAhL,cplcFuFuAhR,    & 
& cplcFdFdVGL,cplcFdFdVGR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,         & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,cplcFuFuVGL,cplcFuFuVGR,               & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,             & 
& cplVGVGVG,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MFd(3),MFu(3),Mhh(2),MHm(2),MVG,MVP,MVWm,MVZ,MAh2(2),MFd2(3),MFu2(3),          & 
& Mhh2(2),MHm2(2),MVG2,MVP2,MVWm2,MVZ2

Complex(dp), Intent(in) :: cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),              & 
& cplcFuFdcHmL(3,3,2),cplcFuFdcHmR(3,3,2),cplcFuFdcVWmL(3,3),cplcFuFdcVWmR(3,3),         & 
& cplcFuFuhhL(3,3,2),cplcFuFuhhR(3,3,2),cplcFdFuHmL(3,3,2),cplcFdFuHmR(3,3,2),           & 
& cplcFuFuVGL(3,3),cplcFuFuVGR(3,3),cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcFdFuVWmL(3,3), & 
& cplcFdFuVWmR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplVGVGVG

Complex(dp), Intent(out) :: Amp(4,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(4) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,3
  Do gt2=1,3
Amp(:,gt1, gt2) = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = MFu(gt1) 
Mex2 = MFu(gt2) 
Mex3 = MVG 


! {Fu, VG, VG}
Do i1=1,3
ML1 = MFu(i1) 
ML2 = MVG 
ML3 = MVG 
coup1L = cplcFuFuVGL(gt1,i1)
coup1R = cplcFuFuVGR(gt1,i1)
coup2L = cplcFuFuVGL(i1,gt2)
coup2R = cplcFuFuVGR(i1,gt2)
coup3 = cplVGVGVG
Call Amp_VERTEX_FtoFV_Topology1_FVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(-3._dp/2._dp*(0.,1._dp))*AmpC 
End Do


! {VG, bar[Fu], bar[Fu]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVG 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = cplcFuFuVGL(gt1,i2)
coup1R = cplcFuFuVGR(gt1,i2)
coup2L = cplcFuFuVGL(i3,gt2)
coup2R = cplcFuFuVGR(i3,gt2)
coup3L = cplcFuFuVGL(i2,i3)
coup3R = cplcFuFuVGR(i2,i3)
Call Amp_VERTEX_FtoFV_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(-1._dp/6._dp)*AmpC 
    End Do
  End Do


! {VP, bar[Fu], bar[Fu]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVP 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = cplcFuFuVPL(gt1,i2)
coup1R = cplcFuFuVPR(gt1,i2)
coup2L = cplcFuFuVPL(i3,gt2)
coup2R = cplcFuFuVPR(i3,gt2)
coup3L = cplcFuFuVGL(i2,i3)
coup3R = cplcFuFuVGR(i2,i3)
Call Amp_VERTEX_FtoFV_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do
  End Do
End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_gumTHDMII_FuToFuVG


Subroutine Amplitude_WAVE_gumTHDMII_FuToFuVP(cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,     & 
& cplcFuFuVZR,ctcplcFuFuVPL,ctcplcFuFuVPR,ctcplcFuFuVZL,ctcplcFuFuVZR,MFu,               & 
& MFu2,MVP,MVP2,ZfUL,ZfUR,ZfVP,ZfVZVP,Amp)

Implicit None

Real(dp), Intent(in) :: MFu(3),MFu2(3),MVP,MVP2

Complex(dp), Intent(in) :: cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3)

Complex(dp), Intent(in) :: ctcplcFuFuVPL(3,3),ctcplcFuFuVPR(3,3),ctcplcFuFuVZL(3,3),ctcplcFuFuVZR(3,3)

Complex(dp), Intent(in) :: ZfUL(3,3),ZfUR(3,3),ZfVP,ZfVZVP

Complex(dp), Intent(out) :: Amp(4,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(4) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

Do gt1=1,3
  Do gt2=1,3
! External masses 
Mex1 = MFu(gt1) 
Mex2 = MFu(gt2) 
Mex3 = MVP 
ZcoupT1L = 0._dp 
ZcoupT1R = 0._dp 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
Do i1=1,3
ZcoupT1L = ZcoupT1L + 0.5_dp*Conjg(ZfUL(i1,gt1))*cplcFuFuVPL(i1,gt2)
ZcoupT1R = ZcoupT1R + 0.5_dp*ZfUR(i1,gt1)*cplcFuFuVPR(i1,gt2)
End Do


! External Field 2 
Do i1=1,3
ZcoupT1L = ZcoupT1L + 0.5_dp*ZfUL(i1,gt2)*cplcFuFuVPL(gt1,i1)
ZcoupT1R = ZcoupT1R + 0.5_dp*Conjg(ZfUR(i1,gt2))*cplcFuFuVPR(gt1,i1)
End Do


! External Field 3 
ZcoupT1L = ZcoupT1L + 0.5_dp*ZfVZVP*cplcFuFuVZL(gt1,gt2)
ZcoupT1R = ZcoupT1R + 0.5_dp*ZfVZVP*cplcFuFuVZR(gt1,gt2)


! Getting the amplitude 
Call TreeAmp_FtoFV(Mex1,Mex2,Mex3,ZcoupT1R,ZcoupT1L,AmpC) 
Amp(:,gt1, gt2) = -AmpC 
  End Do
End Do
End Subroutine Amplitude_WAVE_gumTHDMII_FuToFuVP


Subroutine Amplitude_VERTEX_gumTHDMII_FuToFuVP(MAh,MFd,MFu,Mhh,MHm,MVG,               & 
& MVP,MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplcFuFuAhL,cplcFuFuAhR,    & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,         & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,cplcFuFuVGL,cplcFuFuVGR,               & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,             & 
& cplHmcHmVP,cplHmcVWmVP,cplcHmVPVWm,cplcVWmVPVWm,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MFd(3),MFu(3),Mhh(2),MHm(2),MVG,MVP,MVWm,MVZ,MAh2(2),MFd2(3),MFu2(3),          & 
& Mhh2(2),MHm2(2),MVG2,MVP2,MVWm2,MVZ2

Complex(dp), Intent(in) :: cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),              & 
& cplcFuFdcHmL(3,3,2),cplcFuFdcHmR(3,3,2),cplcFuFdcVWmL(3,3),cplcFuFdcVWmR(3,3),         & 
& cplcFuFuhhL(3,3,2),cplcFuFuhhR(3,3,2),cplcFdFuHmL(3,3,2),cplcFdFuHmR(3,3,2),           & 
& cplcFuFuVGL(3,3),cplcFuFuVGR(3,3),cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcFdFuVWmL(3,3), & 
& cplcFdFuVWmR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplHmcHmVP(2,2),cplHmcVWmVP(2),    & 
& cplcHmVPVWm(2),cplcVWmVPVWm

Complex(dp), Intent(out) :: Amp(4,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(4) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,3
  Do gt2=1,3
Amp(:,gt1, gt2) = 0._dp 
! External masses 
Mex1 = MFu(gt1) 
Mex2 = MFu(gt2) 
Mex3 = MVP 


! {Ah, bar[Fu], bar[Fu]}
Do i1=1,2
  Do i2=1,3
    Do i3=1,3
ML1 = MAh(i1) 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = cplcFuFuAhL(gt1,i2,i1)
coup1R = cplcFuFuAhR(gt1,i2,i1)
coup2L = cplcFuFuAhL(i3,gt2,i1)
coup2R = cplcFuFuAhR(i3,gt2,i1)
coup3L = cplcFuFuVPL(i2,i3)
coup3R = cplcFuFuVPR(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_SFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Fd, Hm, Hm}
Do i1=1,3
  Do i2=1,2
    Do i3=1,2
ML1 = MFd(i1) 
ML2 = MHm(i2) 
ML3 = MHm(i3) 
coup1L = cplcFuFdcHmL(gt1,i1,i2)
coup1R = cplcFuFdcHmR(gt1,i1,i2)
coup2L = cplcFdFuHmL(i1,gt2,i3)
coup2R = cplcFdFuHmR(i1,gt2,i3)
coup3 = -cplHmcHmVP(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_FSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Fd, VWm, Hm}
Do i1=1,3
    Do i3=1,2
ML1 = MFd(i1) 
ML2 = MVWm 
ML3 = MHm(i3) 
coup1L = cplcFuFdcVWmL(gt1,i1)
coup1R = cplcFuFdcVWmR(gt1,i1)
coup2L = cplcFdFuHmL(i1,gt2,i3)
coup2R = cplcFdFuHmR(i1,gt2,i3)
coup3 = cplcHmVPVWm(i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_FVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Fd, Hm, VWm}
Do i1=1,3
  Do i2=1,2
ML1 = MFd(i1) 
ML2 = MHm(i2) 
ML3 = MVWm 
coup1L = cplcFuFdcHmL(gt1,i1,i2)
coup1R = cplcFuFdcHmR(gt1,i1,i2)
coup2L = cplcFdFuVWmL(i1,gt2)
coup2R = cplcFdFuVWmR(i1,gt2)
coup3 = cplHmcVWmVP(i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_FSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Fd, VWm, VWm}
Do i1=1,3
ML1 = MFd(i1) 
ML2 = MVWm 
ML3 = MVWm 
coup1L = cplcFuFdcVWmL(gt1,i1)
coup1R = cplcFuFdcVWmR(gt1,i1)
coup2L = cplcFdFuVWmL(i1,gt2)
coup2R = cplcFdFuVWmR(i1,gt2)
coup3 = cplcVWmVPVWm
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_FVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {hh, bar[Fu], bar[Fu]}
Do i1=1,2
  Do i2=1,3
    Do i3=1,3
ML1 = Mhh(i1) 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = cplcFuFuhhL(gt1,i2,i1)
coup1R = cplcFuFuhhR(gt1,i2,i1)
coup2L = cplcFuFuhhL(i3,gt2,i1)
coup2R = cplcFuFuhhR(i3,gt2,i1)
coup3L = cplcFuFuVPL(i2,i3)
coup3R = cplcFuFuVPR(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_SFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {VG, bar[Fu], bar[Fu]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVG 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = cplcFuFuVGL(gt1,i2)
coup1R = cplcFuFuVGR(gt1,i2)
coup2L = cplcFuFuVGL(i3,gt2)
coup2R = cplcFuFuVGR(i3,gt2)
coup3L = cplcFuFuVPL(i2,i3)
coup3R = cplcFuFuVPR(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(4._dp/3._dp)*AmpC 
    End Do
  End Do


! {VP, bar[Fu], bar[Fu]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVP 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = cplcFuFuVPL(gt1,i2)
coup1R = cplcFuFuVPR(gt1,i2)
coup2L = cplcFuFuVPL(i3,gt2)
coup2R = cplcFuFuVPR(i3,gt2)
coup3L = cplcFuFuVPL(i2,i3)
coup3R = cplcFuFuVPR(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VZ, bar[Fu], bar[Fu]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVZ 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = cplcFuFuVZL(gt1,i2)
coup1R = cplcFuFuVZR(gt1,i2)
coup2L = cplcFuFuVZL(i3,gt2)
coup2R = cplcFuFuVZR(i3,gt2)
coup3L = cplcFuFuVPL(i2,i3)
coup3R = cplcFuFuVPR(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {conj[Hm], bar[Fd], bar[Fd]}
Do i1=1,2
  Do i2=1,3
    Do i3=1,3
ML1 = MHm(i1) 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFuFdcHmL(gt1,i2,i1)
coup1R = cplcFuFdcHmR(gt1,i2,i1)
coup2L = cplcFdFuHmL(i3,gt2,i1)
coup2R = cplcFdFuHmR(i3,gt2,i1)
coup3L = cplcFdFdVPL(i2,i3)
coup3R = cplcFdFdVPR(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_SFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {conj[VWm], bar[Fd], bar[Fd]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVWm 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFuFdcVWmL(gt1,i2)
coup1R = cplcFuFdcVWmR(gt1,i2)
coup2L = cplcFdFuVWmL(i3,gt2)
coup2R = cplcFdFuVWmR(i3,gt2)
coup3L = cplcFdFdVPL(i2,i3)
coup3R = cplcFdFdVPR(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do
  End Do
End Do
End Subroutine Amplitude_VERTEX_gumTHDMII_FuToFuVP


Subroutine Amplitude_IR_VERTEX_gumTHDMII_FuToFuVP(MAh,MFd,MFu,Mhh,MHm,MVG,            & 
& MVP,MVWm,MVZ,MAh2,MFd2,MFu2,Mhh2,MHm2,MVG2,MVP2,MVWm2,MVZ2,cplcFuFuAhL,cplcFuFuAhR,    & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFuFdcHmL,cplcFuFdcHmR,cplcFuFdcVWmL,cplcFuFdcVWmR,         & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHmL,cplcFdFuHmR,cplcFuFuVGL,cplcFuFuVGR,               & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,             & 
& cplHmcHmVP,cplHmcVWmVP,cplcHmVPVWm,cplcVWmVPVWm,Amp)

Implicit None

Real(dp), Intent(in) :: MAh(2),MFd(3),MFu(3),Mhh(2),MHm(2),MVG,MVP,MVWm,MVZ,MAh2(2),MFd2(3),MFu2(3),          & 
& Mhh2(2),MHm2(2),MVG2,MVP2,MVWm2,MVZ2

Complex(dp), Intent(in) :: cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),              & 
& cplcFuFdcHmL(3,3,2),cplcFuFdcHmR(3,3,2),cplcFuFdcVWmL(3,3),cplcFuFdcVWmR(3,3),         & 
& cplcFuFuhhL(3,3,2),cplcFuFuhhR(3,3,2),cplcFdFuHmL(3,3,2),cplcFdFuHmR(3,3,2),           & 
& cplcFuFuVGL(3,3),cplcFuFuVGR(3,3),cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcFdFuVWmL(3,3), & 
& cplcFdFuVWmR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplHmcHmVP(2,2),cplHmcVWmVP(2),    & 
& cplcHmVPVWm(2),cplcVWmVPVWm

Complex(dp), Intent(out) :: Amp(4,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(4) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,3
  Do gt2=1,3
Amp(:,gt1, gt2) = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = MFu(gt1) 
Mex2 = MFu(gt2) 
Mex3 = MVP 


! {VG, bar[Fu], bar[Fu]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVG 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = cplcFuFuVGL(gt1,i2)
coup1R = cplcFuFuVGR(gt1,i2)
coup2L = cplcFuFuVGL(i3,gt2)
coup2R = cplcFuFuVGR(i3,gt2)
coup3L = cplcFuFuVPL(i2,i3)
coup3R = cplcFuFuVPR(i2,i3)
Call Amp_VERTEX_FtoFV_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(4._dp/3._dp)*AmpC 
    End Do
  End Do


! {VP, bar[Fu], bar[Fu]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVP 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = cplcFuFuVPL(gt1,i2)
coup1R = cplcFuFuVPR(gt1,i2)
coup2L = cplcFuFuVPL(i3,gt2)
coup2R = cplcFuFuVPR(i3,gt2)
coup3L = cplcFuFuVPL(i2,i3)
coup3R = cplcFuFuVPR(i2,i3)
Call Amp_VERTEX_FtoFV_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do
  End Do
End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_gumTHDMII_FuToFuVP



End Module OneLoopDecay_Fu_gumTHDMII
