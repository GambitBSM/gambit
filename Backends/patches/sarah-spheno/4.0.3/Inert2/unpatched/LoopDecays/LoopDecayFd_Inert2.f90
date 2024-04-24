! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.14.0 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 23:48 on 14.9.2022   
! ----------------------------------------------------------------------  
 
 
Module OneLoopDecay_Fd_Inert2
Use Control 
Use Settings 
Use LoopFunctions 
Use AddLoopFunctions 
Use Model_Data_Inert2 
Use DecayFFS 
Use DecayFFV 
Use DecaySSS 
Use DecaySFF 
Use DecaySSV 
Use DecaySVV 
Use Bremsstrahlung 

Contains 

Subroutine Amplitude_Tree_Inert2_FdToFdG0(cplcFdFdG0L,cplcFdFdG0R,MFd,MG0,            & 
& MFd2,MG02,Amp)

Implicit None

Real(dp), Intent(in) :: MFd(3),MG0,MFd2(3),MG02

Complex(dp), Intent(in) :: cplcFdFdG0L(3,3),cplcFdFdG0R(3,3)

Complex(dp) :: Amp(2,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 

Do gt1=1,3
  Do gt2=1,3
! External masses 
Mex1 = MFd(gt1) 
Mex2 = MFd(gt2) 
Mex3 = MG0 
! Tree-Level Vertex 
coupT1L = cplcFdFdG0L(gt1,gt2)
coupT1R = cplcFdFdG0R(gt1,gt2)
Call TreeAmp_FtoFS(Mex1,Mex2,Mex3,coupT1L,coupT1R,AmpC) 
! Colour and symmetry factor 
Amp(:,gt1, gt2) = AmpC 
  End Do
End Do
End Subroutine Amplitude_Tree_Inert2_FdToFdG0


Subroutine Gamma_Real_Inert2_FdToFdG0(MLambda,em,gs,cplcFdFdG0L,cplcFdFdG0R,          & 
& MFd,MG0,GammarealPhoton,GammarealGluon)

Implicit None

Complex(dp), Intent(in) :: cplcFdFdG0L(3,3),cplcFdFdG0R(3,3)

Real(dp), Intent(in) :: MFd(3),MG0

Real(dp), Intent(in) :: MLambda, em, gs 

Real(dp), Intent(out) :: GammarealPhoton(3,3), GammarealGluon(3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 

Real(dp) :: Mloop1, Mloop2, Mloop3 
Complex(dp) :: CoupL, CoupR 
 
Do i1=1,3
  Do i2=1,3
CoupL = cplcFdFdG0L(i1,i2)
CoupR = cplcFdFdG0R(i1,i2)
Mex1 = MFd(i1)
Mex2 = MFd(i2)
Mex3 = MG0
If (Abs(Mex1).gt.(Abs(Mex2)+Abs(Mex3))) Then 
 Call hardradiationFFS(Mex1,Mex2,Mex3,MLambda,em,1._dp/9._dp,1._dp/9._dp,0._dp,1._dp/9._dp,0._dp,0._dp,CoupL,CoupR,Gammarealphoton(i1,i2),kont)
 Call hardradiationFFS(Mex1,Mex2,Mex3,MLambda,gs,4._dp/3._dp,4._dp/3._dp,0._dp,4._dp/3._dp,0._dp,0._dp,CoupL,CoupR,Gammarealgluon(i1,i2),kont)
Else 
  GammarealGluon(i1,i2) = 0._dp 
  GammarealPhoton(i1,i2) = 0._dp 

End if 
  End Do
End Do
End Subroutine Gamma_Real_Inert2_FdToFdG0


Subroutine Amplitude_WAVE_Inert2_FdToFdG0(cplcFdFdG0L,cplcFdFdG0R,ctcplcFdFdG0L,      & 
& ctcplcFdFdG0R,MFd,MFd2,MG0,MG02,ZfDL,ZfDR,ZfG0,Amp)

Implicit None

Real(dp), Intent(in) :: MFd(3),MFd2(3),MG0,MG02

Complex(dp), Intent(in) :: cplcFdFdG0L(3,3),cplcFdFdG0R(3,3)

Complex(dp), Intent(in) :: ctcplcFdFdG0L(3,3),ctcplcFdFdG0R(3,3)

Complex(dp), Intent(in) :: ZfDL(3,3),ZfDR(3,3),ZfG0

Complex(dp), Intent(out) :: Amp(2,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

Do gt1=1,3
  Do gt2=1,3
! External masses 
Mex1 = MFd(gt1) 
Mex2 = MFd(gt2) 
Mex3 = MG0 
!----------------------------- 
! Coupling counter term 
!----------------------------- 
ZcoupT1L = ctcplcFdFdG0L(gt1,gt2) 
ZcoupT1R = ctcplcFdFdG0R(gt1,gt2) 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
Do i1=1,3
ZcoupT1L = ZcoupT1L + 0.5_dp*ZfDR(i1,gt1)*cplcFdFdG0L(i1,gt2)
ZcoupT1R = ZcoupT1R + 0.5_dp*Conjg(ZfDL(i1,gt1))*cplcFdFdG0R(i1,gt2)
End Do


! External Field 2 
Do i1=1,3
ZcoupT1L = ZcoupT1L + 0.5_dp*ZfDL(i1,gt2)*cplcFdFdG0L(gt1,i1)
ZcoupT1R = ZcoupT1R + 0.5_dp*Conjg(ZfDR(i1,gt2))*cplcFdFdG0R(gt1,i1)
End Do


! External Field 3 
ZcoupT1L = ZcoupT1L + 0.5_dp*ZfG0*cplcFdFdG0L(gt1,gt2)
ZcoupT1R = ZcoupT1R + 0.5_dp*ZfG0*cplcFdFdG0R(gt1,gt2)


! Getting the amplitude 
Call TreeAmp_FtoFS(Mex1,Mex2,Mex3,ZcoupT1L,ZcoupT1R,AmpC) 
Amp(:,gt1, gt2) = AmpC 
  End Do
End Do
End Subroutine Amplitude_WAVE_Inert2_FdToFdG0


Subroutine Amplitude_VERTEX_Inert2_FdToFdG0(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,              & 
& MVWp,MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdG0L,cplcFdFdG0R,        & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,cplcFdFdVGL,cplcFdFdVGR,               & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFdFdVZL,cplcFdFdVZR,             & 
& cplcFuFuG0L,cplcFuFuG0R,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,         & 
& cplG0G0hh,cplG0hhVZ,cplG0HpcVWp,cplG0cHpVWp,Amp)

Implicit None

Real(dp), Intent(in) :: MFd(3),MFu(3),MG0,Mhh,MHp(2),MVG,MVP,MVWp,MVZ,MFd2(3),MFu2(3),MG02,Mhh2,              & 
& MHp2(2),MVG2,MVP2,MVWp2,MVZ2

Complex(dp), Intent(in) :: cplcFdFdG0L(3,3),cplcFdFdG0R(3,3),cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFuFdHpL(3,3,2),& 
& cplcFuFdHpR(3,3,2),cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),& 
& cplcFuFdVWpL(3,3),cplcFuFdVWpR(3,3),cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFuFuG0L(3,3),& 
& cplcFuFuG0R(3,3),cplcFdFucHpL(3,3,2),cplcFdFucHpR(3,3,2),cplcFdFucVWpL(3,3),           & 
& cplcFdFucVWpR(3,3),cplG0G0hh,cplG0hhVZ,cplG0HpcVWp(2),cplG0cHpVWp(2)

Complex(dp), Intent(out) :: Amp(2,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,3
  Do gt2=1,3
Amp(:,gt1, gt2) = 0._dp 
! External masses 
Mex1 = MFd(gt1) 
Mex2 = MFd(gt2) 
Mex3 = MG0 


! {Fd, hh, G0}
Do i1=1,3
ML1 = MFd(i1) 
ML2 = Mhh 
ML3 = MG0 
coup1L = cplcFdFdhhL(gt1,i1)
coup1R = cplcFdFdhhR(gt1,i1)
coup2L = cplcFdFdG0L(i1,gt2)
coup2R = cplcFdFdG0R(i1,gt2)
coup3 = cplG0G0hh
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {Fd, G0, hh}
Do i1=1,3
ML1 = MFd(i1) 
ML2 = MG0 
ML3 = Mhh 
coup1L = cplcFdFdG0L(gt1,i1)
coup1R = cplcFdFdG0R(gt1,i1)
coup2L = cplcFdFdhhL(i1,gt2)
coup2R = cplcFdFdhhR(i1,gt2)
coup3 = cplG0G0hh
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {Fd, VZ, hh}
Do i1=1,3
ML1 = MFd(i1) 
ML2 = MVZ 
ML3 = Mhh 
coup1L = -cplcFdFdVZR(gt1,i1)
coup1R = -cplcFdFdVZL(gt1,i1)
coup2L = cplcFdFdhhL(i1,gt2)
coup2R = cplcFdFdhhR(i1,gt2)
coup3 = -cplG0hhVZ
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {Fd, hh, VZ}
Do i1=1,3
ML1 = MFd(i1) 
ML2 = Mhh 
ML3 = MVZ 
coup1L = cplcFdFdhhL(gt1,i1)
coup1R = cplcFdFdhhR(gt1,i1)
coup2L = -cplcFdFdVZR(i1,gt2)
coup2R = -cplcFdFdVZL(i1,gt2)
coup3 = -cplG0hhVZ
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {Fu, VWp, Hp}
Do i1=1,3
    Do i3=1,2
ML1 = MFu(i1) 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1L = -cplcFdFucVWpR(gt1,i1)
coup1R = -cplcFdFucVWpL(gt1,i1)
coup2L = cplcFuFdHpL(i1,gt2,i3)
coup2R = cplcFuFdHpR(i1,gt2,i3)
coup3 = -cplG0cHpVWp(i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Fu, Hp, VWp}
Do i1=1,3
  Do i2=1,2
ML1 = MFu(i1) 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1L = cplcFdFucHpL(gt1,i1,i2)
coup1R = cplcFdFucHpR(gt1,i1,i2)
coup2L = -cplcFuFdVWpR(i1,gt2)
coup2R = -cplcFuFdVWpL(i1,gt2)
coup3 = -cplG0HpcVWp(i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {G0, bar[Fd], bar[Fd]}
  Do i2=1,3
    Do i3=1,3
ML1 = MG0 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFdFdG0L(gt1,i2)
coup1R = cplcFdFdG0R(gt1,i2)
coup2L = cplcFdFdG0L(i3,gt2)
coup2R = cplcFdFdG0R(i3,gt2)
coup3L = cplcFdFdG0L(i2,i3)
coup3R = cplcFdFdG0R(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_SFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {hh, bar[Fd], bar[Fd]}
  Do i2=1,3
    Do i3=1,3
ML1 = Mhh 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFdFdhhL(gt1,i2)
coup1R = cplcFdFdhhR(gt1,i2)
coup2L = cplcFdFdhhL(i3,gt2)
coup2R = cplcFdFdhhR(i3,gt2)
coup3L = cplcFdFdG0L(i2,i3)
coup3R = cplcFdFdG0R(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_SFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VG, bar[Fd], bar[Fd]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVG 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = -cplcFdFdVGR(gt1,i2)
coup1R = -cplcFdFdVGL(gt1,i2)
coup2L = -cplcFdFdVGR(i3,gt2)
coup2R = -cplcFdFdVGL(i3,gt2)
coup3L = cplcFdFdG0L(i2,i3)
coup3R = cplcFdFdG0R(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(4._dp/3._dp)*AmpC 
    End Do
  End Do


! {VP, bar[Fd], bar[Fd]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVP 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = -cplcFdFdVPR(gt1,i2)
coup1R = -cplcFdFdVPL(gt1,i2)
coup2L = -cplcFdFdVPR(i3,gt2)
coup2R = -cplcFdFdVPL(i3,gt2)
coup3L = cplcFdFdG0L(i2,i3)
coup3R = cplcFdFdG0R(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VZ, bar[Fd], bar[Fd]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVZ 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = -cplcFdFdVZR(gt1,i2)
coup1R = -cplcFdFdVZL(gt1,i2)
coup2L = -cplcFdFdVZR(i3,gt2)
coup2R = -cplcFdFdVZL(i3,gt2)
coup3L = cplcFdFdG0L(i2,i3)
coup3R = cplcFdFdG0R(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {conj[Hp], bar[Fu], bar[Fu]}
Do i1=1,2
  Do i2=1,3
    Do i3=1,3
ML1 = MHp(i1) 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = cplcFdFucHpL(gt1,i2,i1)
coup1R = cplcFdFucHpR(gt1,i2,i1)
coup2L = cplcFuFdHpL(i3,gt2,i1)
coup2R = cplcFuFdHpR(i3,gt2,i1)
coup3L = cplcFuFuG0L(i2,i3)
coup3R = cplcFuFuG0R(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_SFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {conj[VWp], bar[Fu], bar[Fu]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVWp 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = -cplcFdFucVWpR(gt1,i2)
coup1R = -cplcFdFucVWpL(gt1,i2)
coup2L = -cplcFuFdVWpR(i3,gt2)
coup2R = -cplcFuFdVWpL(i3,gt2)
coup3L = cplcFuFuG0L(i2,i3)
coup3R = cplcFuFuG0R(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do
  End Do
End Do
End Subroutine Amplitude_VERTEX_Inert2_FdToFdG0


Subroutine Amplitude_IR_VERTEX_Inert2_FdToFdG0(MFd,MFu,MG0,Mhh,MHp,MVG,               & 
& MVP,MVWp,MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdG0L,cplcFdFdG0R,    & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,cplcFdFdVGL,cplcFdFdVGR,               & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFdFdVZL,cplcFdFdVZR,             & 
& cplcFuFuG0L,cplcFuFuG0R,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,         & 
& cplG0G0hh,cplG0hhVZ,cplG0HpcVWp,cplG0cHpVWp,Amp)

Implicit None

Real(dp), Intent(in) :: MFd(3),MFu(3),MG0,Mhh,MHp(2),MVG,MVP,MVWp,MVZ,MFd2(3),MFu2(3),MG02,Mhh2,              & 
& MHp2(2),MVG2,MVP2,MVWp2,MVZ2

Complex(dp), Intent(in) :: cplcFdFdG0L(3,3),cplcFdFdG0R(3,3),cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFuFdHpL(3,3,2),& 
& cplcFuFdHpR(3,3,2),cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),& 
& cplcFuFdVWpL(3,3),cplcFuFdVWpR(3,3),cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFuFuG0L(3,3),& 
& cplcFuFuG0R(3,3),cplcFdFucHpL(3,3,2),cplcFdFucHpR(3,3,2),cplcFdFucVWpL(3,3),           & 
& cplcFdFucVWpR(3,3),cplG0G0hh,cplG0hhVZ,cplG0HpcVWp(2),cplG0cHpVWp(2)

Complex(dp), Intent(out) :: Amp(2,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,3
  Do gt2=1,3
Amp(:,gt1, gt2) = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = MFd(gt1) 
Mex2 = MFd(gt2) 
Mex3 = MG0 


! {VG, bar[Fd], bar[Fd]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVG 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = -cplcFdFdVGR(gt1,i2)
coup1R = -cplcFdFdVGL(gt1,i2)
coup2L = -cplcFdFdVGR(i3,gt2)
coup2R = -cplcFdFdVGL(i3,gt2)
coup3L = cplcFdFdG0L(i2,i3)
coup3R = cplcFdFdG0R(i2,i3)
Call Amp_VERTEX_FtoFS_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(4._dp/3._dp)*AmpC 
    End Do
  End Do


! {VP, bar[Fd], bar[Fd]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVP 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = -cplcFdFdVPR(gt1,i2)
coup1R = -cplcFdFdVPL(gt1,i2)
coup2L = -cplcFdFdVPR(i3,gt2)
coup2R = -cplcFdFdVPL(i3,gt2)
coup3L = cplcFdFdG0L(i2,i3)
coup3R = cplcFdFdG0R(i2,i3)
Call Amp_VERTEX_FtoFS_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do
  End Do
End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_FdToFdG0


Subroutine Amplitude_Tree_Inert2_FdToFdhh(cplcFdFdhhL,cplcFdFdhhR,MFd,Mhh,            & 
& MFd2,Mhh2,Amp)

Implicit None

Real(dp), Intent(in) :: MFd(3),Mhh,MFd2(3),Mhh2

Complex(dp), Intent(in) :: cplcFdFdhhL(3,3),cplcFdFdhhR(3,3)

Complex(dp) :: Amp(2,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 

Do gt1=1,3
  Do gt2=1,3
! External masses 
Mex1 = MFd(gt1) 
Mex2 = MFd(gt2) 
Mex3 = Mhh 
! Tree-Level Vertex 
coupT1L = cplcFdFdhhL(gt1,gt2)
coupT1R = cplcFdFdhhR(gt1,gt2)
Call TreeAmp_FtoFS(Mex1,Mex2,Mex3,coupT1L,coupT1R,AmpC) 
! Colour and symmetry factor 
Amp(:,gt1, gt2) = AmpC 
  End Do
End Do
End Subroutine Amplitude_Tree_Inert2_FdToFdhh


Subroutine Gamma_Real_Inert2_FdToFdhh(MLambda,em,gs,cplcFdFdhhL,cplcFdFdhhR,          & 
& MFd,Mhh,GammarealPhoton,GammarealGluon)

Implicit None

Complex(dp), Intent(in) :: cplcFdFdhhL(3,3),cplcFdFdhhR(3,3)

Real(dp), Intent(in) :: MFd(3),Mhh

Real(dp), Intent(in) :: MLambda, em, gs 

Real(dp), Intent(out) :: GammarealPhoton(3,3), GammarealGluon(3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 

Real(dp) :: Mloop1, Mloop2, Mloop3 
Complex(dp) :: CoupL, CoupR 
 
Do i1=1,3
  Do i2=1,3
CoupL = cplcFdFdhhL(i1,i2)
CoupR = cplcFdFdhhR(i1,i2)
Mex1 = MFd(i1)
Mex2 = MFd(i2)
Mex3 = Mhh
If (Abs(Mex1).gt.(Abs(Mex2)+Abs(Mex3))) Then 
 Call hardradiationFFS(Mex1,Mex2,Mex3,MLambda,em,1._dp/9._dp,1._dp/9._dp,0._dp,1._dp/9._dp,0._dp,0._dp,CoupL,CoupR,Gammarealphoton(i1,i2),kont)
 Call hardradiationFFS(Mex1,Mex2,Mex3,MLambda,gs,4._dp/3._dp,4._dp/3._dp,0._dp,4._dp/3._dp,0._dp,0._dp,CoupL,CoupR,Gammarealgluon(i1,i2),kont)
Else 
  GammarealGluon(i1,i2) = 0._dp 
  GammarealPhoton(i1,i2) = 0._dp 

End if 
  End Do
End Do
End Subroutine Gamma_Real_Inert2_FdToFdhh


Subroutine Amplitude_WAVE_Inert2_FdToFdhh(cplcFdFdhhL,cplcFdFdhhR,ctcplcFdFdhhL,      & 
& ctcplcFdFdhhR,MFd,MFd2,Mhh,Mhh2,ZfDL,ZfDR,Zfhh,Amp)

Implicit None

Real(dp), Intent(in) :: MFd(3),MFd2(3),Mhh,Mhh2

Complex(dp), Intent(in) :: cplcFdFdhhL(3,3),cplcFdFdhhR(3,3)

Complex(dp), Intent(in) :: ctcplcFdFdhhL(3,3),ctcplcFdFdhhR(3,3)

Complex(dp), Intent(in) :: ZfDL(3,3),ZfDR(3,3),Zfhh

Complex(dp), Intent(out) :: Amp(2,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

Do gt1=1,3
  Do gt2=1,3
! External masses 
Mex1 = MFd(gt1) 
Mex2 = MFd(gt2) 
Mex3 = Mhh 
!----------------------------- 
! Coupling counter term 
!----------------------------- 
ZcoupT1L = ctcplcFdFdhhL(gt1,gt2) 
ZcoupT1R = ctcplcFdFdhhR(gt1,gt2) 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
Do i1=1,3
ZcoupT1L = ZcoupT1L + 0.5_dp*ZfDR(i1,gt1)*cplcFdFdhhL(i1,gt2)
ZcoupT1R = ZcoupT1R + 0.5_dp*Conjg(ZfDL(i1,gt1))*cplcFdFdhhR(i1,gt2)
End Do


! External Field 2 
Do i1=1,3
ZcoupT1L = ZcoupT1L + 0.5_dp*ZfDL(i1,gt2)*cplcFdFdhhL(gt1,i1)
ZcoupT1R = ZcoupT1R + 0.5_dp*Conjg(ZfDR(i1,gt2))*cplcFdFdhhR(gt1,i1)
End Do


! External Field 3 
ZcoupT1L = ZcoupT1L + 0.5_dp*Zfhh*cplcFdFdhhL(gt1,gt2)
ZcoupT1R = ZcoupT1R + 0.5_dp*Zfhh*cplcFdFdhhR(gt1,gt2)


! Getting the amplitude 
Call TreeAmp_FtoFS(Mex1,Mex2,Mex3,ZcoupT1L,ZcoupT1R,AmpC) 
Amp(:,gt1, gt2) = AmpC 
  End Do
End Do
End Subroutine Amplitude_WAVE_Inert2_FdToFdhh


Subroutine Amplitude_VERTEX_Inert2_FdToFdhh(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,              & 
& MVWp,MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdG0L,cplcFdFdG0R,        & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,cplcFdFdVGL,cplcFdFdVGR,               & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFdFdVZL,cplcFdFdVZR,             & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,         & 
& cplG0G0hh,cplG0hhVZ,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,         & 
& cplhhVZVZ,Amp)

Implicit None

Real(dp), Intent(in) :: MFd(3),MFu(3),MG0,Mhh,MHp(2),MVG,MVP,MVWp,MVZ,MFd2(3),MFu2(3),MG02,Mhh2,              & 
& MHp2(2),MVG2,MVP2,MVWp2,MVZ2

Complex(dp), Intent(in) :: cplcFdFdG0L(3,3),cplcFdFdG0R(3,3),cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFuFdHpL(3,3,2),& 
& cplcFuFdHpR(3,3,2),cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),& 
& cplcFuFdVWpL(3,3),cplcFuFdVWpR(3,3),cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFuFuhhL(3,3),& 
& cplcFuFuhhR(3,3),cplcFdFucHpL(3,3,2),cplcFdFucHpR(3,3,2),cplcFdFucVWpL(3,3),           & 
& cplcFdFucVWpR(3,3),cplG0G0hh,cplG0hhVZ,cplhhhhhh,cplhhHpcHp(2,2),cplhhHpcVWp(2),       & 
& cplhhcHpVWp(2),cplhhcVWpVWp,cplhhVZVZ

Complex(dp), Intent(out) :: Amp(2,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,3
  Do gt2=1,3
Amp(:,gt1, gt2) = 0._dp 
! External masses 
Mex1 = MFd(gt1) 
Mex2 = MFd(gt2) 
Mex3 = Mhh 


! {Fd, G0, G0}
Do i1=1,3
ML1 = MFd(i1) 
ML2 = MG0 
ML3 = MG0 
coup1L = cplcFdFdG0L(gt1,i1)
coup1R = cplcFdFdG0R(gt1,i1)
coup2L = cplcFdFdG0L(i1,gt2)
coup2R = cplcFdFdG0R(i1,gt2)
coup3 = cplG0G0hh
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {Fd, VZ, G0}
Do i1=1,3
ML1 = MFd(i1) 
ML2 = MVZ 
ML3 = MG0 
coup1L = -cplcFdFdVZR(gt1,i1)
coup1R = -cplcFdFdVZL(gt1,i1)
coup2L = cplcFdFdG0L(i1,gt2)
coup2R = cplcFdFdG0R(i1,gt2)
coup3 = cplG0hhVZ
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {Fd, hh, hh}
Do i1=1,3
ML1 = MFd(i1) 
ML2 = Mhh 
ML3 = Mhh 
coup1L = cplcFdFdhhL(gt1,i1)
coup1R = cplcFdFdhhR(gt1,i1)
coup2L = cplcFdFdhhL(i1,gt2)
coup2R = cplcFdFdhhR(i1,gt2)
coup3 = cplhhhhhh
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {Fd, G0, VZ}
Do i1=1,3
ML1 = MFd(i1) 
ML2 = MG0 
ML3 = MVZ 
coup1L = cplcFdFdG0L(gt1,i1)
coup1R = cplcFdFdG0R(gt1,i1)
coup2L = -cplcFdFdVZR(i1,gt2)
coup2R = -cplcFdFdVZL(i1,gt2)
coup3 = cplG0hhVZ
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {Fd, VZ, VZ}
Do i1=1,3
ML1 = MFd(i1) 
ML2 = MVZ 
ML3 = MVZ 
coup1L = -cplcFdFdVZR(gt1,i1)
coup1R = -cplcFdFdVZL(gt1,i1)
coup2L = -cplcFdFdVZR(i1,gt2)
coup2R = -cplcFdFdVZL(i1,gt2)
coup3 = cplhhVZVZ
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {Fu, Hp, Hp}
Do i1=1,3
  Do i2=1,2
    Do i3=1,2
ML1 = MFu(i1) 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1L = cplcFdFucHpL(gt1,i1,i2)
coup1R = cplcFdFucHpR(gt1,i1,i2)
coup2L = cplcFuFdHpL(i1,gt2,i3)
coup2R = cplcFuFdHpR(i1,gt2,i3)
coup3 = cplhhHpcHp(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Fu, VWp, Hp}
Do i1=1,3
    Do i3=1,2
ML1 = MFu(i1) 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1L = -cplcFdFucVWpR(gt1,i1)
coup1R = -cplcFdFucVWpL(gt1,i1)
coup2L = cplcFuFdHpL(i1,gt2,i3)
coup2R = cplcFuFdHpR(i1,gt2,i3)
coup3 = -cplhhcHpVWp(i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Fu, Hp, VWp}
Do i1=1,3
  Do i2=1,2
ML1 = MFu(i1) 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1L = cplcFdFucHpL(gt1,i1,i2)
coup1R = cplcFdFucHpR(gt1,i1,i2)
coup2L = -cplcFuFdVWpR(i1,gt2)
coup2R = -cplcFuFdVWpL(i1,gt2)
coup3 = -cplhhHpcVWp(i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Fu, VWp, VWp}
Do i1=1,3
ML1 = MFu(i1) 
ML2 = MVWp 
ML3 = MVWp 
coup1L = -cplcFdFucVWpR(gt1,i1)
coup1R = -cplcFdFucVWpL(gt1,i1)
coup2L = -cplcFuFdVWpR(i1,gt2)
coup2R = -cplcFuFdVWpL(i1,gt2)
coup3 = cplhhcVWpVWp
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {G0, bar[Fd], bar[Fd]}
  Do i2=1,3
    Do i3=1,3
ML1 = MG0 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFdFdG0L(gt1,i2)
coup1R = cplcFdFdG0R(gt1,i2)
coup2L = cplcFdFdG0L(i3,gt2)
coup2R = cplcFdFdG0R(i3,gt2)
coup3L = cplcFdFdhhL(i2,i3)
coup3R = cplcFdFdhhR(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_SFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {hh, bar[Fd], bar[Fd]}
  Do i2=1,3
    Do i3=1,3
ML1 = Mhh 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFdFdhhL(gt1,i2)
coup1R = cplcFdFdhhR(gt1,i2)
coup2L = cplcFdFdhhL(i3,gt2)
coup2R = cplcFdFdhhR(i3,gt2)
coup3L = cplcFdFdhhL(i2,i3)
coup3R = cplcFdFdhhR(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_SFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VG, bar[Fd], bar[Fd]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVG 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = -cplcFdFdVGR(gt1,i2)
coup1R = -cplcFdFdVGL(gt1,i2)
coup2L = -cplcFdFdVGR(i3,gt2)
coup2R = -cplcFdFdVGL(i3,gt2)
coup3L = cplcFdFdhhL(i2,i3)
coup3R = cplcFdFdhhR(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(4._dp/3._dp)*AmpC 
    End Do
  End Do


! {VP, bar[Fd], bar[Fd]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVP 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = -cplcFdFdVPR(gt1,i2)
coup1R = -cplcFdFdVPL(gt1,i2)
coup2L = -cplcFdFdVPR(i3,gt2)
coup2R = -cplcFdFdVPL(i3,gt2)
coup3L = cplcFdFdhhL(i2,i3)
coup3R = cplcFdFdhhR(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VZ, bar[Fd], bar[Fd]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVZ 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = -cplcFdFdVZR(gt1,i2)
coup1R = -cplcFdFdVZL(gt1,i2)
coup2L = -cplcFdFdVZR(i3,gt2)
coup2R = -cplcFdFdVZL(i3,gt2)
coup3L = cplcFdFdhhL(i2,i3)
coup3R = cplcFdFdhhR(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {conj[Hp], bar[Fu], bar[Fu]}
Do i1=1,2
  Do i2=1,3
    Do i3=1,3
ML1 = MHp(i1) 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = cplcFdFucHpL(gt1,i2,i1)
coup1R = cplcFdFucHpR(gt1,i2,i1)
coup2L = cplcFuFdHpL(i3,gt2,i1)
coup2R = cplcFuFdHpR(i3,gt2,i1)
coup3L = cplcFuFuhhL(i2,i3)
coup3R = cplcFuFuhhR(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_SFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {conj[VWp], bar[Fu], bar[Fu]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVWp 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = -cplcFdFucVWpR(gt1,i2)
coup1R = -cplcFdFucVWpL(gt1,i2)
coup2L = -cplcFuFdVWpR(i3,gt2)
coup2R = -cplcFuFdVWpL(i3,gt2)
coup3L = cplcFuFuhhL(i2,i3)
coup3R = cplcFuFuhhR(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do
  End Do
End Do
End Subroutine Amplitude_VERTEX_Inert2_FdToFdhh


Subroutine Amplitude_IR_VERTEX_Inert2_FdToFdhh(MFd,MFu,MG0,Mhh,MHp,MVG,               & 
& MVP,MVWp,MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdG0L,cplcFdFdG0R,    & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,cplcFdFdVGL,cplcFdFdVGR,               & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFdFdVZL,cplcFdFdVZR,             & 
& cplcFuFuhhL,cplcFuFuhhR,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,         & 
& cplG0G0hh,cplG0hhVZ,cplhhhhhh,cplhhHpcHp,cplhhHpcVWp,cplhhcHpVWp,cplhhcVWpVWp,         & 
& cplhhVZVZ,Amp)

Implicit None

Real(dp), Intent(in) :: MFd(3),MFu(3),MG0,Mhh,MHp(2),MVG,MVP,MVWp,MVZ,MFd2(3),MFu2(3),MG02,Mhh2,              & 
& MHp2(2),MVG2,MVP2,MVWp2,MVZ2

Complex(dp), Intent(in) :: cplcFdFdG0L(3,3),cplcFdFdG0R(3,3),cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFuFdHpL(3,3,2),& 
& cplcFuFdHpR(3,3,2),cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),& 
& cplcFuFdVWpL(3,3),cplcFuFdVWpR(3,3),cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFuFuhhL(3,3),& 
& cplcFuFuhhR(3,3),cplcFdFucHpL(3,3,2),cplcFdFucHpR(3,3,2),cplcFdFucVWpL(3,3),           & 
& cplcFdFucVWpR(3,3),cplG0G0hh,cplG0hhVZ,cplhhhhhh,cplhhHpcHp(2,2),cplhhHpcVWp(2),       & 
& cplhhcHpVWp(2),cplhhcVWpVWp,cplhhVZVZ

Complex(dp), Intent(out) :: Amp(2,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,3
  Do gt2=1,3
Amp(:,gt1, gt2) = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = MFd(gt1) 
Mex2 = MFd(gt2) 
Mex3 = Mhh 


! {VG, bar[Fd], bar[Fd]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVG 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = -cplcFdFdVGR(gt1,i2)
coup1R = -cplcFdFdVGL(gt1,i2)
coup2L = -cplcFdFdVGR(i3,gt2)
coup2R = -cplcFdFdVGL(i3,gt2)
coup3L = cplcFdFdhhL(i2,i3)
coup3R = cplcFdFdhhR(i2,i3)
Call Amp_VERTEX_FtoFS_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(4._dp/3._dp)*AmpC 
    End Do
  End Do


! {VP, bar[Fd], bar[Fd]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVP 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = -cplcFdFdVPR(gt1,i2)
coup1R = -cplcFdFdVPL(gt1,i2)
coup2L = -cplcFdFdVPR(i3,gt2)
coup2R = -cplcFdFdVPL(i3,gt2)
coup3L = cplcFdFdhhL(i2,i3)
coup3R = cplcFdFdhhR(i2,i3)
Call Amp_VERTEX_FtoFS_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do
  End Do
End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_FdToFdhh


Subroutine Amplitude_Tree_Inert2_FdToFdVZ(cplcFdFdVZL,cplcFdFdVZR,MFd,MVZ,            & 
& MFd2,MVZ2,Amp)

Implicit None

Real(dp), Intent(in) :: MFd(3),MVZ,MFd2(3),MVZ2

Complex(dp), Intent(in) :: cplcFdFdVZL(3,3),cplcFdFdVZR(3,3)

Complex(dp) :: Amp(4,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(4) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 

Do gt1=1,3
  Do gt2=1,3
! External masses 
Mex1 = MFd(gt1) 
Mex2 = MFd(gt2) 
Mex3 = MVZ 
! Tree-Level Vertex 
coupT1L = cplcFdFdVZL(gt1,gt2)
coupT1R = cplcFdFdVZR(gt1,gt2)
Call TreeAmp_FtoFV(Mex1,Mex2,Mex3,coupT1R,coupT1L,AmpC) 
! Colour and symmetry factor 
Amp(:,gt1, gt2) = -AmpC 
  End Do
End Do
End Subroutine Amplitude_Tree_Inert2_FdToFdVZ


Subroutine Gamma_Real_Inert2_FdToFdVZ(MLambda,em,gs,cplcFdFdVZL,cplcFdFdVZR,          & 
& MFd,MVZ,GammarealPhoton,GammarealGluon)

Implicit None

Complex(dp), Intent(in) :: cplcFdFdVZL(3,3),cplcFdFdVZR(3,3)

Real(dp), Intent(in) :: MFd(3),MVZ

Real(dp), Intent(in) :: MLambda, em, gs 

Real(dp), Intent(out) :: GammarealPhoton(3,3), GammarealGluon(3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 

Real(dp) :: Mloop1, Mloop2, Mloop3 
Complex(dp) :: CoupL, CoupR 
 
Do i1=1,3
  Do i2=1,3
CoupL = cplcFdFdVZL(i1,i2)
CoupR = cplcFdFdVZR(i1,i2)
Mex1 = MFd(i1)
Mex2 = MFd(i2)
Mex3 = MVZ
If (Abs(Mex1).gt.(Abs(Mex2)+Abs(Mex3))) Then 
  Call hardphotonFFZ(Mex1,Mex2,Mex3,MLambda,-1._dp/3._dp,-1._dp/3._dp,CoupL,CoupR,(0,1)*em,GammaRealPhoton(i1,i2),kont)
  Call hardgluonFFZW(Mex1,Mex2,Mex3,MLambda,4._dp/3._dp,gs,CoupL,CoupR,Gammarealgluon(i1,i2),kont)
Else 
  GammarealGluon(i1,i2) = 0._dp 
  GammarealPhoton(i1,i2) = 0._dp 

End if 
  End Do
End Do
End Subroutine Gamma_Real_Inert2_FdToFdVZ


Subroutine Amplitude_WAVE_Inert2_FdToFdVZ(cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,        & 
& cplcFdFdVZR,ctcplcFdFdVPL,ctcplcFdFdVPR,ctcplcFdFdVZL,ctcplcFdFdVZR,MFd,               & 
& MFd2,MVP,MVP2,MVZ,MVZ2,ZfDL,ZfDR,ZfVPVZ,ZfVZ,Amp)

Implicit None

Real(dp), Intent(in) :: MFd(3),MFd2(3),MVP,MVP2,MVZ,MVZ2

Complex(dp), Intent(in) :: cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),cplcFdFdVZL(3,3),cplcFdFdVZR(3,3)

Complex(dp), Intent(in) :: ctcplcFdFdVPL(3,3),ctcplcFdFdVPR(3,3),ctcplcFdFdVZL(3,3),ctcplcFdFdVZR(3,3)

Complex(dp), Intent(in) :: ZfDL(3,3),ZfDR(3,3),ZfVPVZ,ZfVZ

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
Mex1 = MFd(gt1) 
Mex2 = MFd(gt2) 
Mex3 = MVZ 
!----------------------------- 
! Coupling counter term 
!----------------------------- 
ZcoupT1L = ctcplcFdFdVZL(gt1,gt2) 
ZcoupT1R = ctcplcFdFdVZR(gt1,gt2)
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
Do i1=1,3
ZcoupT1L = ZcoupT1L + 0.5_dp*Conjg(ZfDL(i1,gt1))*cplcFdFdVZL(i1,gt2)
ZcoupT1R = ZcoupT1R + 0.5_dp*ZfDR(i1,gt1)*cplcFdFdVZR(i1,gt2)
End Do


! External Field 2 
Do i1=1,3
ZcoupT1L = ZcoupT1L + 0.5_dp*ZfDL(i1,gt2)*cplcFdFdVZL(gt1,i1)
ZcoupT1R = ZcoupT1R + 0.5_dp*Conjg(ZfDR(i1,gt2))*cplcFdFdVZR(gt1,i1)
End Do


! External Field 3 
ZcoupT1L = ZcoupT1L + 0.5_dp*ZfVPVZ*cplcFdFdVPL(gt1,gt2)
ZcoupT1R = ZcoupT1R + 0.5_dp*ZfVPVZ*cplcFdFdVPR(gt1,gt2)
ZcoupT1L = ZcoupT1L + 0.5_dp*ZfVZ*cplcFdFdVZL(gt1,gt2)
ZcoupT1R = ZcoupT1R + 0.5_dp*ZfVZ*cplcFdFdVZR(gt1,gt2)


! Getting the amplitude 
Call TreeAmp_FtoFV(Mex1,Mex2,Mex3,ZcoupT1R,ZcoupT1L,AmpC) 
Amp(:,gt1, gt2) = -AmpC 
  End Do
End Do
End Subroutine Amplitude_WAVE_Inert2_FdToFdVZ


Subroutine Amplitude_VERTEX_Inert2_FdToFdVZ(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,              & 
& MVWp,MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdG0L,cplcFdFdG0R,        & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,cplcFdFdVGL,cplcFdFdVGR,               & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFdFdVZL,cplcFdFdVZR,             & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,         & 
& cplG0hhVZ,cplhhVZVZ,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,cplcVWpVWpVZ,Amp)

Implicit None

Real(dp), Intent(in) :: MFd(3),MFu(3),MG0,Mhh,MHp(2),MVG,MVP,MVWp,MVZ,MFd2(3),MFu2(3),MG02,Mhh2,              & 
& MHp2(2),MVG2,MVP2,MVWp2,MVZ2

Complex(dp), Intent(in) :: cplcFdFdG0L(3,3),cplcFdFdG0R(3,3),cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFuFdHpL(3,3,2),& 
& cplcFuFdHpR(3,3,2),cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),& 
& cplcFuFdVWpL(3,3),cplcFuFdVWpR(3,3),cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFuFuVZL(3,3),& 
& cplcFuFuVZR(3,3),cplcFdFucHpL(3,3,2),cplcFdFucHpR(3,3,2),cplcFdFucVWpL(3,3),           & 
& cplcFdFucVWpR(3,3),cplG0hhVZ,cplhhVZVZ,cplHpcHpVZ(2,2),cplHpcVWpVZ(2),cplcHpVWpVZ(2),  & 
& cplcVWpVWpVZ

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
Mex1 = MFd(gt1) 
Mex2 = MFd(gt2) 
Mex3 = MVZ 


! {Fd, hh, G0}
Do i1=1,3
ML1 = MFd(i1) 
ML2 = Mhh 
ML3 = MG0 
coup1L = cplcFdFdhhL(gt1,i1)
coup1R = cplcFdFdhhR(gt1,i1)
coup2L = cplcFdFdG0L(i1,gt2)
coup2R = cplcFdFdG0R(i1,gt2)
coup3 = cplG0hhVZ
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_FSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {Fd, G0, hh}
Do i1=1,3
ML1 = MFd(i1) 
ML2 = MG0 
ML3 = Mhh 
coup1L = cplcFdFdG0L(gt1,i1)
coup1R = cplcFdFdG0R(gt1,i1)
coup2L = cplcFdFdhhL(i1,gt2)
coup2R = cplcFdFdhhR(i1,gt2)
coup3 = -cplG0hhVZ
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_FSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {Fd, VZ, hh}
Do i1=1,3
ML1 = MFd(i1) 
ML2 = MVZ 
ML3 = Mhh 
coup1L = cplcFdFdVZL(gt1,i1)
coup1R = cplcFdFdVZR(gt1,i1)
coup2L = cplcFdFdhhL(i1,gt2)
coup2R = cplcFdFdhhR(i1,gt2)
coup3 = cplhhVZVZ
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_FVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {Fd, hh, VZ}
Do i1=1,3
ML1 = MFd(i1) 
ML2 = Mhh 
ML3 = MVZ 
coup1L = cplcFdFdhhL(gt1,i1)
coup1R = cplcFdFdhhR(gt1,i1)
coup2L = cplcFdFdVZL(i1,gt2)
coup2R = cplcFdFdVZR(i1,gt2)
coup3 = cplhhVZVZ
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_FSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {Fu, Hp, Hp}
Do i1=1,3
  Do i2=1,2
    Do i3=1,2
ML1 = MFu(i1) 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1L = cplcFdFucHpL(gt1,i1,i2)
coup1R = cplcFdFucHpR(gt1,i1,i2)
coup2L = cplcFuFdHpL(i1,gt2,i3)
coup2R = cplcFuFdHpR(i1,gt2,i3)
coup3 = -cplHpcHpVZ(i2,i3)
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


! {Fu, VWp, Hp}
Do i1=1,3
    Do i3=1,2
ML1 = MFu(i1) 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1L = cplcFdFucVWpL(gt1,i1)
coup1R = cplcFdFucVWpR(gt1,i1)
coup2L = cplcFuFdHpL(i1,gt2,i3)
coup2R = cplcFuFdHpR(i1,gt2,i3)
coup3 = cplcHpVWpVZ(i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_FVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Fu, Hp, VWp}
Do i1=1,3
  Do i2=1,2
ML1 = MFu(i1) 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1L = cplcFdFucHpL(gt1,i1,i2)
coup1R = cplcFdFucHpR(gt1,i1,i2)
coup2L = cplcFuFdVWpL(i1,gt2)
coup2R = cplcFuFdVWpR(i1,gt2)
coup3 = cplHpcVWpVZ(i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_FSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Fu, VWp, VWp}
Do i1=1,3
ML1 = MFu(i1) 
ML2 = MVWp 
ML3 = MVWp 
coup1L = cplcFdFucVWpL(gt1,i1)
coup1R = cplcFdFucVWpR(gt1,i1)
coup2L = cplcFuFdVWpL(i1,gt2)
coup2R = cplcFuFdVWpR(i1,gt2)
coup3 = -cplcVWpVWpVZ
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_FVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {G0, bar[Fd], bar[Fd]}
  Do i2=1,3
    Do i3=1,3
ML1 = MG0 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFdFdG0L(gt1,i2)
coup1R = cplcFdFdG0R(gt1,i2)
coup2L = cplcFdFdG0L(i3,gt2)
coup2R = cplcFdFdG0R(i3,gt2)
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


! {hh, bar[Fd], bar[Fd]}
  Do i2=1,3
    Do i3=1,3
ML1 = Mhh 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFdFdhhL(gt1,i2)
coup1R = cplcFdFdhhR(gt1,i2)
coup2L = cplcFdFdhhL(i3,gt2)
coup2R = cplcFdFdhhR(i3,gt2)
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


! {VG, bar[Fd], bar[Fd]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVG 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFdFdVGL(gt1,i2)
coup1R = cplcFdFdVGR(gt1,i2)
coup2L = cplcFdFdVGL(i3,gt2)
coup2R = cplcFdFdVGR(i3,gt2)
coup3L = cplcFdFdVZL(i2,i3)
coup3R = cplcFdFdVZR(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(4._dp/3._dp)*AmpC 
    End Do
  End Do


! {VP, bar[Fd], bar[Fd]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVP 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFdFdVPL(gt1,i2)
coup1R = cplcFdFdVPR(gt1,i2)
coup2L = cplcFdFdVPL(i3,gt2)
coup2R = cplcFdFdVPR(i3,gt2)
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


! {VZ, bar[Fd], bar[Fd]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVZ 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFdFdVZL(gt1,i2)
coup1R = cplcFdFdVZR(gt1,i2)
coup2L = cplcFdFdVZL(i3,gt2)
coup2R = cplcFdFdVZR(i3,gt2)
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


! {conj[Hp], bar[Fu], bar[Fu]}
Do i1=1,2
  Do i2=1,3
    Do i3=1,3
ML1 = MHp(i1) 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = cplcFdFucHpL(gt1,i2,i1)
coup1R = cplcFdFucHpR(gt1,i2,i1)
coup2L = cplcFuFdHpL(i3,gt2,i1)
coup2R = cplcFuFdHpR(i3,gt2,i1)
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


! {conj[VWp], bar[Fu], bar[Fu]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVWp 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = cplcFdFucVWpL(gt1,i2)
coup1R = cplcFdFucVWpR(gt1,i2)
coup2L = cplcFuFdVWpL(i3,gt2)
coup2R = cplcFuFdVWpR(i3,gt2)
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
  End Do
End Do
End Subroutine Amplitude_VERTEX_Inert2_FdToFdVZ


Subroutine Amplitude_IR_VERTEX_Inert2_FdToFdVZ(MFd,MFu,MG0,Mhh,MHp,MVG,               & 
& MVP,MVWp,MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdG0L,cplcFdFdG0R,    & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,cplcFdFdVGL,cplcFdFdVGR,               & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFdFdVZL,cplcFdFdVZR,             & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,         & 
& cplG0hhVZ,cplhhVZVZ,cplHpcHpVZ,cplHpcVWpVZ,cplcHpVWpVZ,cplcVWpVWpVZ,Amp)

Implicit None

Real(dp), Intent(in) :: MFd(3),MFu(3),MG0,Mhh,MHp(2),MVG,MVP,MVWp,MVZ,MFd2(3),MFu2(3),MG02,Mhh2,              & 
& MHp2(2),MVG2,MVP2,MVWp2,MVZ2

Complex(dp), Intent(in) :: cplcFdFdG0L(3,3),cplcFdFdG0R(3,3),cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFuFdHpL(3,3,2),& 
& cplcFuFdHpR(3,3,2),cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),& 
& cplcFuFdVWpL(3,3),cplcFuFdVWpR(3,3),cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFuFuVZL(3,3),& 
& cplcFuFuVZR(3,3),cplcFdFucHpL(3,3,2),cplcFdFucHpR(3,3,2),cplcFdFucVWpL(3,3),           & 
& cplcFdFucVWpR(3,3),cplG0hhVZ,cplhhVZVZ,cplHpcHpVZ(2,2),cplHpcVWpVZ(2),cplcHpVWpVZ(2),  & 
& cplcVWpVWpVZ

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
Mex1 = MFd(gt1) 
Mex2 = MFd(gt2) 
Mex3 = MVZ 


! {VG, bar[Fd], bar[Fd]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVG 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFdFdVGL(gt1,i2)
coup1R = cplcFdFdVGR(gt1,i2)
coup2L = cplcFdFdVGL(i3,gt2)
coup2R = cplcFdFdVGR(i3,gt2)
coup3L = cplcFdFdVZL(i2,i3)
coup3R = cplcFdFdVZR(i2,i3)
Call Amp_VERTEX_FtoFV_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(4._dp/3._dp)*AmpC 
    End Do
  End Do


! {VP, bar[Fd], bar[Fd]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVP 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFdFdVPL(gt1,i2)
coup1R = cplcFdFdVPR(gt1,i2)
coup2L = cplcFdFdVPL(i3,gt2)
coup2R = cplcFdFdVPR(i3,gt2)
coup3L = cplcFdFdVZL(i2,i3)
coup3R = cplcFdFdVZR(i2,i3)
Call Amp_VERTEX_FtoFV_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do
  End Do
End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_FdToFdVZ


Subroutine Amplitude_Tree_Inert2_FdToFucHp(cplcFdFucHpL,cplcFdFucHpR,MFd,             & 
& MFu,MHp,MFd2,MFu2,MHp2,Amp)

Implicit None

Real(dp), Intent(in) :: MFd(3),MFu(3),MHp(2),MFd2(3),MFu2(3),MHp2(2)

Complex(dp), Intent(in) :: cplcFdFucHpL(3,3,2),cplcFdFucHpR(3,3,2)

Complex(dp) :: Amp(2,3,3,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 

Do gt1=1,3
  Do gt2=1,3
    Do gt3=1,2
! External masses 
Mex1 = MFd(gt1) 
Mex2 = MFu(gt2) 
Mex3 = MHp(gt3) 
! Tree-Level Vertex 
coupT1L = cplcFdFucHpL(gt1,gt2,gt3)
coupT1R = cplcFdFucHpR(gt1,gt2,gt3)
Call TreeAmp_FtoFS(Mex1,Mex2,Mex3,coupT1L,coupT1R,AmpC) 
! Colour and symmetry factor 
Amp(:,gt1, gt2, gt3) = AmpC 
    End Do
  End Do
End Do
End Subroutine Amplitude_Tree_Inert2_FdToFucHp


Subroutine Gamma_Real_Inert2_FdToFucHp(MLambda,em,gs,cplcFdFucHpL,cplcFdFucHpR,       & 
& MFd,MFu,MHp,GammarealPhoton,GammarealGluon)

Implicit None

Complex(dp), Intent(in) :: cplcFdFucHpL(3,3,2),cplcFdFucHpR(3,3,2)

Real(dp), Intent(in) :: MFd(3),MFu(3),MHp(2)

Real(dp), Intent(in) :: MLambda, em, gs 

Real(dp), Intent(out) :: GammarealPhoton(3,3,2), GammarealGluon(3,3,2) 

Integer :: i1, i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 

Real(dp) :: Mloop1, Mloop2, Mloop3 
Complex(dp) :: CoupL, CoupR 
 
Do i1=1,3
  Do i2=1,3
    Do i3=2,2
CoupL = cplcFdFucHpL(i1,i2,i3)
CoupR = cplcFdFucHpR(i1,i2,i3)
Mex1 = MFd(i1)
Mex2 = MFu(i2)
Mex3 = MHp(i3)
If (Abs(Mex1).gt.(Abs(Mex2)+Abs(Mex3))) Then 
 Call hardradiationFFS(Mex1,Mex2,Mex3,MLambda,em,1._dp/9._dp,-2._dp/9._dp,1._dp/3._dp,4._dp/9._dp,-2._dp/3._dp,1._dp,CoupL,CoupR,Gammarealphoton(i1,i2,i3),kont)
 Call hardradiationFFS(Mex1,Mex2,Mex3,MLambda,gs,4._dp/3._dp,4._dp/3._dp,0._dp,4._dp/3._dp,0._dp,0._dp,CoupL,CoupR,Gammarealgluon(i1,i2,i3),kont)
Else 
  GammarealGluon(i1,i2,i3) = 0._dp 
  GammarealPhoton(i1,i2,i3) = 0._dp 

End if 
    End Do
  End Do
End Do
End Subroutine Gamma_Real_Inert2_FdToFucHp


Subroutine Amplitude_WAVE_Inert2_FdToFucHp(cplcFdFucHpL,cplcFdFucHpR,ctcplcFdFucHpL,  & 
& ctcplcFdFucHpR,MFd,MFd2,MFu,MFu2,MHp,MHp2,ZfDL,ZfDR,ZfHp,ZfUL,ZfUR,Amp)

Implicit None

Real(dp), Intent(in) :: MFd(3),MFd2(3),MFu(3),MFu2(3),MHp(2),MHp2(2)

Complex(dp), Intent(in) :: cplcFdFucHpL(3,3,2),cplcFdFucHpR(3,3,2)

Complex(dp), Intent(in) :: ctcplcFdFucHpL(3,3,2),ctcplcFdFucHpR(3,3,2)

Complex(dp), Intent(in) :: ZfDL(3,3),ZfDR(3,3),ZfHp(2,2),ZfUL(3,3),ZfUR(3,3)

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
Mex1 = MFd(gt1) 
Mex2 = MFu(gt2) 
Mex3 = MHp(gt3) 
!----------------------------- 
! Coupling counter term 
!----------------------------- 
ZcoupT1L = ctcplcFdFucHpL(gt1,gt2,gt3) 
ZcoupT1R = ctcplcFdFucHpR(gt1,gt2,gt3) 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
Do i1=1,3
ZcoupT1L = ZcoupT1L + 0.5_dp*ZfDR(i1,gt1)*cplcFdFucHpL(i1,gt2,gt3)
ZcoupT1R = ZcoupT1R + 0.5_dp*Conjg(ZfDL(i1,gt1))*cplcFdFucHpR(i1,gt2,gt3)
End Do


! External Field 2 
Do i1=1,3
ZcoupT1L = ZcoupT1L + 0.5_dp*ZfUL(i1,gt2)*cplcFdFucHpL(gt1,i1,gt3)
ZcoupT1R = ZcoupT1R + 0.5_dp*Conjg(ZfUR(i1,gt2))*cplcFdFucHpR(gt1,i1,gt3)
End Do


! External Field 3 
Do i1=1,2
ZcoupT1L = ZcoupT1L + 0.5_dp*Conjg(ZfHp(i1,gt3))*cplcFdFucHpL(gt1,gt2,i1)
ZcoupT1R = ZcoupT1R + 0.5_dp*Conjg(ZfHp(i1,gt3))*cplcFdFucHpR(gt1,gt2,i1)
End Do


! Getting the amplitude 
Call TreeAmp_FtoFS(Mex1,Mex2,Mex3,ZcoupT1L,ZcoupT1R,AmpC) 
Amp(:,gt1, gt2, gt3) = AmpC 
    End Do
  End Do
End Do
End Subroutine Amplitude_WAVE_Inert2_FdToFucHp


Subroutine Amplitude_VERTEX_Inert2_FdToFucHp(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,             & 
& MVWp,MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdG0L,cplcFdFdG0R,        & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,               & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFuFuG0L,cplcFuFuG0R,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,cplG0cHpVWp,cplhhHpcHp,          & 
& cplhhcHpVWp,cplHpcHpVP,cplHpcHpVZ,cplcHpVPVWp,cplcHpVWpVZ,Amp)

Implicit None

Real(dp), Intent(in) :: MFd(3),MFu(3),MG0,Mhh,MHp(2),MVG,MVP,MVWp,MVZ,MFd2(3),MFu2(3),MG02,Mhh2,              & 
& MHp2(2),MVG2,MVP2,MVWp2,MVZ2

Complex(dp), Intent(in) :: cplcFdFdG0L(3,3),cplcFdFdG0R(3,3),cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFdFdVGL(3,3), & 
& cplcFdFdVGR(3,3),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),  & 
& cplcFuFuG0L(3,3),cplcFuFuG0R(3,3),cplcFuFuhhL(3,3),cplcFuFuhhR(3,3),cplcFuFuVGL(3,3),  & 
& cplcFuFuVGR(3,3),cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),  & 
& cplcFdFucHpL(3,3,2),cplcFdFucHpR(3,3,2),cplcFdFucVWpL(3,3),cplcFdFucVWpR(3,3),         & 
& cplG0cHpVWp(2),cplhhHpcHp(2,2),cplhhcHpVWp(2),cplHpcHpVP(2,2),cplHpcHpVZ(2,2),         & 
& cplcHpVPVWp(2),cplcHpVWpVZ(2)

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
Mex1 = MFd(gt1) 
Mex2 = MFu(gt2) 
Mex3 = MHp(gt3) 


! {Fd, hh, conj[Hp]}
Do i1=1,3
    Do i3=1,2
ML1 = MFd(i1) 
ML2 = Mhh 
ML3 = MHp(i3) 
coup1L = cplcFdFdhhL(gt1,i1)
coup1R = cplcFdFdhhR(gt1,i1)
coup2L = cplcFdFucHpL(i1,gt2,i3)
coup2R = cplcFdFucHpR(i1,gt2,i3)
coup3 = cplhhHpcHp(i3,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Fd, VP, conj[Hp]}
Do i1=1,3
    Do i3=1,2
ML1 = MFd(i1) 
ML2 = MVP 
ML3 = MHp(i3) 
coup1L = -cplcFdFdVPR(gt1,i1)
coup1R = -cplcFdFdVPL(gt1,i1)
coup2L = cplcFdFucHpL(i1,gt2,i3)
coup2R = cplcFdFucHpR(i1,gt2,i3)
coup3 = cplHpcHpVP(i3,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Fd, VZ, conj[Hp]}
Do i1=1,3
    Do i3=1,2
ML1 = MFd(i1) 
ML2 = MVZ 
ML3 = MHp(i3) 
coup1L = -cplcFdFdVZR(gt1,i1)
coup1R = -cplcFdFdVZL(gt1,i1)
coup2L = cplcFdFucHpL(i1,gt2,i3)
coup2R = cplcFdFucHpR(i1,gt2,i3)
coup3 = cplHpcHpVZ(i3,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Fd, G0, conj[VWp]}
Do i1=1,3
ML1 = MFd(i1) 
ML2 = MG0 
ML3 = MVWp 
coup1L = cplcFdFdG0L(gt1,i1)
coup1R = cplcFdFdG0R(gt1,i1)
coup2L = -cplcFdFucVWpR(i1,gt2)
coup2R = -cplcFdFucVWpL(i1,gt2)
coup3 = cplG0cHpVWp(gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
End Do


! {Fd, hh, conj[VWp]}
Do i1=1,3
ML1 = MFd(i1) 
ML2 = Mhh 
ML3 = MVWp 
coup1L = cplcFdFdhhL(gt1,i1)
coup1R = cplcFdFdhhR(gt1,i1)
coup2L = -cplcFdFucVWpR(i1,gt2)
coup2R = -cplcFdFucVWpL(i1,gt2)
coup3 = cplhhcHpVWp(gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
End Do


! {Fd, VP, conj[VWp]}
Do i1=1,3
ML1 = MFd(i1) 
ML2 = MVP 
ML3 = MVWp 
coup1L = -cplcFdFdVPR(gt1,i1)
coup1R = -cplcFdFdVPL(gt1,i1)
coup2L = -cplcFdFucVWpR(i1,gt2)
coup2R = -cplcFdFucVWpL(i1,gt2)
coup3 = cplcHpVPVWp(gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
End Do


! {Fd, VZ, conj[VWp]}
Do i1=1,3
ML1 = MFd(i1) 
ML2 = MVZ 
ML3 = MVWp 
coup1L = -cplcFdFdVZR(gt1,i1)
coup1R = -cplcFdFdVZL(gt1,i1)
coup2L = -cplcFdFucVWpR(i1,gt2)
coup2R = -cplcFdFucVWpL(i1,gt2)
coup3 = cplcHpVWpVZ(gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
End Do


! {Fu, VWp, G0}
Do i1=1,3
ML1 = MFu(i1) 
ML2 = MVWp 
ML3 = MG0 
coup1L = -cplcFdFucVWpR(gt1,i1)
coup1R = -cplcFdFucVWpL(gt1,i1)
coup2L = cplcFuFuG0L(i1,gt2)
coup2R = cplcFuFuG0R(i1,gt2)
coup3 = cplG0cHpVWp(gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
End Do


! {Fu, Hp, hh}
Do i1=1,3
  Do i2=1,2
ML1 = MFu(i1) 
ML2 = MHp(i2) 
ML3 = Mhh 
coup1L = cplcFdFucHpL(gt1,i1,i2)
coup1R = cplcFdFucHpR(gt1,i1,i2)
coup2L = cplcFuFuhhL(i1,gt2)
coup2R = cplcFuFuhhR(i1,gt2)
coup3 = cplhhHpcHp(i2,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Fu, VWp, hh}
Do i1=1,3
ML1 = MFu(i1) 
ML2 = MVWp 
ML3 = Mhh 
coup1L = -cplcFdFucVWpR(gt1,i1)
coup1R = -cplcFdFucVWpL(gt1,i1)
coup2L = cplcFuFuhhL(i1,gt2)
coup2R = cplcFuFuhhR(i1,gt2)
coup3 = cplhhcHpVWp(gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
End Do


! {Fu, Hp, VP}
Do i1=1,3
  Do i2=1,2
ML1 = MFu(i1) 
ML2 = MHp(i2) 
ML3 = MVP 
coup1L = cplcFdFucHpL(gt1,i1,i2)
coup1R = cplcFdFucHpR(gt1,i1,i2)
coup2L = -cplcFuFuVPR(i1,gt2)
coup2R = -cplcFuFuVPL(i1,gt2)
coup3 = cplHpcHpVP(i2,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Fu, VWp, VP}
Do i1=1,3
ML1 = MFu(i1) 
ML2 = MVWp 
ML3 = MVP 
coup1L = -cplcFdFucVWpR(gt1,i1)
coup1R = -cplcFdFucVWpL(gt1,i1)
coup2L = -cplcFuFuVPR(i1,gt2)
coup2R = -cplcFuFuVPL(i1,gt2)
coup3 = cplcHpVPVWp(gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
End Do


! {Fu, Hp, VZ}
Do i1=1,3
  Do i2=1,2
ML1 = MFu(i1) 
ML2 = MHp(i2) 
ML3 = MVZ 
coup1L = cplcFdFucHpL(gt1,i1,i2)
coup1R = cplcFdFucHpR(gt1,i1,i2)
coup2L = -cplcFuFuVZR(i1,gt2)
coup2R = -cplcFuFuVZL(i1,gt2)
coup3 = cplHpcHpVZ(i2,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Fu, VWp, VZ}
Do i1=1,3
ML1 = MFu(i1) 
ML2 = MVWp 
ML3 = MVZ 
coup1L = -cplcFdFucVWpR(gt1,i1)
coup1R = -cplcFdFucVWpL(gt1,i1)
coup2L = -cplcFuFuVZR(i1,gt2)
coup2R = -cplcFuFuVZL(i1,gt2)
coup3 = cplcHpVWpVZ(gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
End Do


! {G0, bar[Fd], bar[Fu]}
  Do i2=1,3
    Do i3=1,3
ML1 = MG0 
ML2 = MFd(i2) 
ML3 = MFu(i3) 
coup1L = cplcFdFdG0L(gt1,i2)
coup1R = cplcFdFdG0R(gt1,i2)
coup2L = cplcFuFuG0L(i3,gt2)
coup2R = cplcFuFuG0R(i3,gt2)
coup3L = cplcFdFucHpL(i2,i3,gt3)
coup3R = cplcFdFucHpR(i2,i3,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_SFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {hh, bar[Fd], bar[Fu]}
  Do i2=1,3
    Do i3=1,3
ML1 = Mhh 
ML2 = MFd(i2) 
ML3 = MFu(i3) 
coup1L = cplcFdFdhhL(gt1,i2)
coup1R = cplcFdFdhhR(gt1,i2)
coup2L = cplcFuFuhhL(i3,gt2)
coup2R = cplcFuFuhhR(i3,gt2)
coup3L = cplcFdFucHpL(i2,i3,gt3)
coup3R = cplcFdFucHpR(i2,i3,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_SFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VG, bar[Fd], bar[Fu]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVG 
ML2 = MFd(i2) 
ML3 = MFu(i3) 
coup1L = -cplcFdFdVGR(gt1,i2)
coup1R = -cplcFdFdVGL(gt1,i2)
coup2L = -cplcFuFuVGR(i3,gt2)
coup2R = -cplcFuFuVGL(i3,gt2)
coup3L = cplcFdFucHpL(i2,i3,gt3)
coup3R = cplcFdFucHpR(i2,i3,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(4._dp/3._dp)*AmpC 
    End Do
  End Do


! {VP, bar[Fd], bar[Fu]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVP 
ML2 = MFd(i2) 
ML3 = MFu(i3) 
coup1L = -cplcFdFdVPR(gt1,i2)
coup1R = -cplcFdFdVPL(gt1,i2)
coup2L = -cplcFuFuVPR(i3,gt2)
coup2R = -cplcFuFuVPL(i3,gt2)
coup3L = cplcFdFucHpL(i2,i3,gt3)
coup3R = cplcFdFucHpR(i2,i3,gt3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VZ, bar[Fd], bar[Fu]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVZ 
ML2 = MFd(i2) 
ML3 = MFu(i3) 
coup1L = -cplcFdFdVZR(gt1,i2)
coup1R = -cplcFdFdVZL(gt1,i2)
coup2L = -cplcFuFuVZR(i3,gt2)
coup2R = -cplcFuFuVZL(i3,gt2)
coup3L = cplcFdFucHpL(i2,i3,gt3)
coup3R = cplcFdFucHpR(i2,i3,gt3)
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
End Subroutine Amplitude_VERTEX_Inert2_FdToFucHp


Subroutine Amplitude_IR_VERTEX_Inert2_FdToFucHp(MFd,MFu,MG0,Mhh,MHp,MVG,              & 
& MVP,MVWp,MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdG0L,cplcFdFdG0R,    & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,               & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFuFuG0L,cplcFuFuG0R,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,cplG0cHpVWp,cplhhHpcHp,          & 
& cplhhcHpVWp,cplHpcHpVP,cplHpcHpVZ,cplcHpVPVWp,cplcHpVWpVZ,Amp)

Implicit None

Real(dp), Intent(in) :: MFd(3),MFu(3),MG0,Mhh,MHp(2),MVG,MVP,MVWp,MVZ,MFd2(3),MFu2(3),MG02,Mhh2,              & 
& MHp2(2),MVG2,MVP2,MVWp2,MVZ2

Complex(dp), Intent(in) :: cplcFdFdG0L(3,3),cplcFdFdG0R(3,3),cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFdFdVGL(3,3), & 
& cplcFdFdVGR(3,3),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),  & 
& cplcFuFuG0L(3,3),cplcFuFuG0R(3,3),cplcFuFuhhL(3,3),cplcFuFuhhR(3,3),cplcFuFuVGL(3,3),  & 
& cplcFuFuVGR(3,3),cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),  & 
& cplcFdFucHpL(3,3,2),cplcFdFucHpR(3,3,2),cplcFdFucVWpL(3,3),cplcFdFucVWpR(3,3),         & 
& cplG0cHpVWp(2),cplhhHpcHp(2,2),cplhhcHpVWp(2),cplHpcHpVP(2,2),cplHpcHpVZ(2,2),         & 
& cplcHpVPVWp(2),cplcHpVWpVZ(2)

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
Mex1 = MFd(gt1) 
Mex2 = MFu(gt2) 
Mex3 = MHp(gt3) 


! {Fd, VP, conj[Hp]}
Do i1=1,3
    Do i3=1,2
ML1 = MFd(i1) 
ML2 = MVP 
ML3 = MHp(i3) 
coup1L = -cplcFdFdVPR(gt1,i1)
coup1R = -cplcFdFdVPL(gt1,i1)
coup2L = cplcFdFucHpL(i1,gt2,i3)
coup2R = cplcFdFucHpR(i1,gt2,i3)
coup3 = cplHpcHpVP(i3,gt3)
Call Amp_VERTEX_FtoFS_Topology1_FVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Fd, VP, conj[VWp]}
Do i1=1,3
ML1 = MFd(i1) 
ML2 = MVP 
ML3 = MVWp 
coup1L = -cplcFdFdVPR(gt1,i1)
coup1R = -cplcFdFdVPL(gt1,i1)
coup2L = -cplcFdFucVWpR(i1,gt2)
coup2R = -cplcFdFucVWpL(i1,gt2)
coup3 = cplcHpVPVWp(gt3)
Call Amp_VERTEX_FtoFS_Topology1_FVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
End Do


! {Fu, Hp, VP}
Do i1=1,3
  Do i2=1,2
ML1 = MFu(i1) 
ML2 = MHp(i2) 
ML3 = MVP 
coup1L = cplcFdFucHpL(gt1,i1,i2)
coup1R = cplcFdFucHpR(gt1,i1,i2)
coup2L = -cplcFuFuVPR(i1,gt2)
coup2R = -cplcFuFuVPL(i1,gt2)
coup3 = cplHpcHpVP(i2,gt3)
Call Amp_VERTEX_FtoFS_Topology1_FSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Fu, VWp, VP}
Do i1=1,3
ML1 = MFu(i1) 
ML2 = MVWp 
ML3 = MVP 
coup1L = -cplcFdFucVWpR(gt1,i1)
coup1R = -cplcFdFucVWpL(gt1,i1)
coup2L = -cplcFuFuVPR(i1,gt2)
coup2R = -cplcFuFuVPL(i1,gt2)
coup3 = cplcHpVPVWp(gt3)
Call Amp_VERTEX_FtoFS_Topology1_FVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
End Do


! {VG, bar[Fd], bar[Fu]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVG 
ML2 = MFd(i2) 
ML3 = MFu(i3) 
coup1L = -cplcFdFdVGR(gt1,i2)
coup1R = -cplcFdFdVGL(gt1,i2)
coup2L = -cplcFuFuVGR(i3,gt2)
coup2R = -cplcFuFuVGL(i3,gt2)
coup3L = cplcFdFucHpL(i2,i3,gt3)
coup3R = cplcFdFucHpR(i2,i3,gt3)
Call Amp_VERTEX_FtoFS_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(4._dp/3._dp)*AmpC 
    End Do
  End Do


! {VP, bar[Fd], bar[Fu]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVP 
ML2 = MFd(i2) 
ML3 = MFu(i3) 
coup1L = -cplcFdFdVPR(gt1,i2)
coup1R = -cplcFdFdVPL(gt1,i2)
coup2L = -cplcFuFuVPR(i3,gt2)
coup2R = -cplcFuFuVPL(i3,gt2)
coup3L = cplcFdFucHpL(i2,i3,gt3)
coup3R = cplcFdFucHpR(i2,i3,gt3)
Call Amp_VERTEX_FtoFS_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2, gt3) = Amp(:,gt1, gt2, gt3) + oo16pi2*(1)*AmpC 
    End Do
  End Do
    End Do
  End Do
End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_FdToFucHp


Subroutine Amplitude_Tree_Inert2_FdToFucVWp(cplcFdFucVWpL,cplcFdFucVWpR,              & 
& MFd,MFu,MVWp,MFd2,MFu2,MVWp2,Amp)

Implicit None

Real(dp), Intent(in) :: MFd(3),MFu(3),MVWp,MFd2(3),MFu2(3),MVWp2

Complex(dp), Intent(in) :: cplcFdFucVWpL(3,3),cplcFdFucVWpR(3,3)

Complex(dp) :: Amp(4,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(4) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 

Do gt1=1,3
  Do gt2=1,3
! External masses 
Mex1 = MFd(gt1) 
Mex2 = MFu(gt2) 
Mex3 = MVWp 
! Tree-Level Vertex 
coupT1L = cplcFdFucVWpL(gt1,gt2)
coupT1R = cplcFdFucVWpR(gt1,gt2)
Call TreeAmp_FtoFV(Mex1,Mex2,Mex3,coupT1R,coupT1L,AmpC) 
! Colour and symmetry factor 
Amp(:,gt1, gt2) = -AmpC 
  End Do
End Do
End Subroutine Amplitude_Tree_Inert2_FdToFucVWp


Subroutine Gamma_Real_Inert2_FdToFucVWp(MLambda,em,gs,cplcFdFucVWpL,cplcFdFucVWpR,    & 
& MFd,MFu,MVWp,GammarealPhoton,GammarealGluon)

Implicit None

Complex(dp), Intent(in) :: cplcFdFucVWpL(3,3),cplcFdFucVWpR(3,3)

Real(dp), Intent(in) :: MFd(3),MFu(3),MVWp

Real(dp), Intent(in) :: MLambda, em, gs 

Real(dp), Intent(out) :: GammarealPhoton(3,3), GammarealGluon(3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3, kont 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 

Real(dp) :: Mloop1, Mloop2, Mloop3 
Complex(dp) :: CoupL, CoupR 
 
Do i1=1,3
  Do i2=1,3
CoupL = cplcFdFucVWpL(i1,i2)
CoupR = cplcFdFucVWpR(i1,i2)
Mex1 = MFd(i1)
Mex2 = MFu(i2)
Mex3 = MVWp
If (Abs(Mex1).gt.(Abs(Mex2)+Abs(Mex3))) Then 
  Call hardphotonFFW(Mex1,Mex2,Mex3,MLambda,-1._dp/3._dp,2._dp/3._dp,CoupL,CoupR,(0,1)*em,GammaRealPhoton(i1,i2),kont)
  Call hardgluonFFZW(Mex1,Mex2,Mex3,MLambda,4._dp/3._dp,gs,CoupL,CoupR,Gammarealgluon(i1,i2),kont)
Else 
  GammarealGluon(i1,i2) = 0._dp 
  GammarealPhoton(i1,i2) = 0._dp 

End if 
  End Do
End Do
End Subroutine Gamma_Real_Inert2_FdToFucVWp


Subroutine Amplitude_WAVE_Inert2_FdToFucVWp(cplcFdFucVWpL,cplcFdFucVWpR,              & 
& ctcplcFdFucVWpL,ctcplcFdFucVWpR,MFd,MFd2,MFu,MFu2,MVWp,MVWp2,ZfDL,ZfDR,ZfUL,           & 
& ZfUR,ZfVWp,Amp)

Implicit None

Real(dp), Intent(in) :: MFd(3),MFd2(3),MFu(3),MFu2(3),MVWp,MVWp2

Complex(dp), Intent(in) :: cplcFdFucVWpL(3,3),cplcFdFucVWpR(3,3)

Complex(dp), Intent(in) :: ctcplcFdFucVWpL(3,3),ctcplcFdFucVWpR(3,3)

Complex(dp), Intent(in) :: ZfDL(3,3),ZfDR(3,3),ZfUL(3,3),ZfUR(3,3),ZfVWp

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
Mex1 = MFd(gt1) 
Mex2 = MFu(gt2) 
Mex3 = MVWp 
!----------------------------- 
! Coupling counter term 
!----------------------------- 
ZcoupT1L = ctcplcFdFucVWpL(gt1,gt2) 
ZcoupT1R = ctcplcFdFucVWpR(gt1,gt2)
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
Do i1=1,3
ZcoupT1L = ZcoupT1L + 0.5_dp*Conjg(ZfDL(i1,gt1))*cplcFdFucVWpL(i1,gt2)
ZcoupT1R = ZcoupT1R + 0.5_dp*ZfDR(i1,gt1)*cplcFdFucVWpR(i1,gt2)
End Do


! External Field 2 
Do i1=1,3
ZcoupT1L = ZcoupT1L + 0.5_dp*ZfUL(i1,gt2)*cplcFdFucVWpL(gt1,i1)
ZcoupT1R = ZcoupT1R + 0.5_dp*Conjg(ZfUR(i1,gt2))*cplcFdFucVWpR(gt1,i1)
End Do


! External Field 3 
ZcoupT1L = ZcoupT1L + 0.5_dp*ZfVWp*cplcFdFucVWpL(gt1,gt2)
ZcoupT1R = ZcoupT1R + 0.5_dp*ZfVWp*cplcFdFucVWpR(gt1,gt2)


! Getting the amplitude 
Call TreeAmp_FtoFV(Mex1,Mex2,Mex3,ZcoupT1R,ZcoupT1L,AmpC) 
Amp(:,gt1, gt2) = -AmpC 
  End Do
End Do
End Subroutine Amplitude_WAVE_Inert2_FdToFucVWp


Subroutine Amplitude_VERTEX_Inert2_FdToFucVWp(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,            & 
& MVWp,MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdG0L,cplcFdFdG0R,        & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,               & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFuFuG0L,cplcFuFuG0R,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,cplG0HpcVWp,cplhhHpcVWp,         & 
& cplhhcVWpVWp,cplHpcVWpVP,cplHpcVWpVZ,cplcVWpVPVWp,cplcVWpVWpVZ,Amp)

Implicit None

Real(dp), Intent(in) :: MFd(3),MFu(3),MG0,Mhh,MHp(2),MVG,MVP,MVWp,MVZ,MFd2(3),MFu2(3),MG02,Mhh2,              & 
& MHp2(2),MVG2,MVP2,MVWp2,MVZ2

Complex(dp), Intent(in) :: cplcFdFdG0L(3,3),cplcFdFdG0R(3,3),cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFdFdVGL(3,3), & 
& cplcFdFdVGR(3,3),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),  & 
& cplcFuFuG0L(3,3),cplcFuFuG0R(3,3),cplcFuFuhhL(3,3),cplcFuFuhhR(3,3),cplcFuFuVGL(3,3),  & 
& cplcFuFuVGR(3,3),cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),  & 
& cplcFdFucHpL(3,3,2),cplcFdFucHpR(3,3,2),cplcFdFucVWpL(3,3),cplcFdFucVWpR(3,3),         & 
& cplG0HpcVWp(2),cplhhHpcVWp(2),cplhhcVWpVWp,cplHpcVWpVP(2),cplHpcVWpVZ(2),              & 
& cplcVWpVPVWp,cplcVWpVWpVZ

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
Mex1 = MFd(gt1) 
Mex2 = MFu(gt2) 
Mex3 = MVWp 


! {Fd, G0, conj[Hp]}
Do i1=1,3
    Do i3=1,2
ML1 = MFd(i1) 
ML2 = MG0 
ML3 = MHp(i3) 
coup1L = cplcFdFdG0L(gt1,i1)
coup1R = cplcFdFdG0R(gt1,i1)
coup2L = cplcFdFucHpL(i1,gt2,i3)
coup2R = cplcFdFucHpR(i1,gt2,i3)
coup3 = -cplG0HpcVWp(i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_FSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Fd, hh, conj[Hp]}
Do i1=1,3
    Do i3=1,2
ML1 = MFd(i1) 
ML2 = Mhh 
ML3 = MHp(i3) 
coup1L = cplcFdFdhhL(gt1,i1)
coup1R = cplcFdFdhhR(gt1,i1)
coup2L = cplcFdFucHpL(i1,gt2,i3)
coup2R = cplcFdFucHpR(i1,gt2,i3)
coup3 = -cplhhHpcVWp(i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_FSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Fd, VP, conj[Hp]}
Do i1=1,3
    Do i3=1,2
ML1 = MFd(i1) 
ML2 = MVP 
ML3 = MHp(i3) 
coup1L = cplcFdFdVPL(gt1,i1)
coup1R = cplcFdFdVPR(gt1,i1)
coup2L = cplcFdFucHpL(i1,gt2,i3)
coup2R = cplcFdFucHpR(i1,gt2,i3)
coup3 = cplHpcVWpVP(i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_FVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Fd, VZ, conj[Hp]}
Do i1=1,3
    Do i3=1,2
ML1 = MFd(i1) 
ML2 = MVZ 
ML3 = MHp(i3) 
coup1L = cplcFdFdVZL(gt1,i1)
coup1R = cplcFdFdVZR(gt1,i1)
coup2L = cplcFdFucHpL(i1,gt2,i3)
coup2R = cplcFdFucHpR(i1,gt2,i3)
coup3 = cplHpcVWpVZ(i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_FVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Fd, hh, conj[VWp]}
Do i1=1,3
ML1 = MFd(i1) 
ML2 = Mhh 
ML3 = MVWp 
coup1L = cplcFdFdhhL(gt1,i1)
coup1R = cplcFdFdhhR(gt1,i1)
coup2L = cplcFdFucVWpL(i1,gt2)
coup2R = cplcFdFucVWpR(i1,gt2)
coup3 = cplhhcVWpVWp
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_FSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {Fd, VP, conj[VWp]}
Do i1=1,3
ML1 = MFd(i1) 
ML2 = MVP 
ML3 = MVWp 
coup1L = cplcFdFdVPL(gt1,i1)
coup1R = cplcFdFdVPR(gt1,i1)
coup2L = cplcFdFucVWpL(i1,gt2)
coup2R = cplcFdFucVWpR(i1,gt2)
coup3 = cplcVWpVPVWp
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_FVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {Fd, VZ, conj[VWp]}
Do i1=1,3
ML1 = MFd(i1) 
ML2 = MVZ 
ML3 = MVWp 
coup1L = cplcFdFdVZL(gt1,i1)
coup1R = cplcFdFdVZR(gt1,i1)
coup2L = cplcFdFucVWpL(i1,gt2)
coup2R = cplcFdFucVWpR(i1,gt2)
coup3 = -cplcVWpVWpVZ
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_FVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {Fu, Hp, G0}
Do i1=1,3
  Do i2=1,2
ML1 = MFu(i1) 
ML2 = MHp(i2) 
ML3 = MG0 
coup1L = cplcFdFucHpL(gt1,i1,i2)
coup1R = cplcFdFucHpR(gt1,i1,i2)
coup2L = cplcFuFuG0L(i1,gt2)
coup2R = cplcFuFuG0R(i1,gt2)
coup3 = cplG0HpcVWp(i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_FSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Fu, Hp, hh}
Do i1=1,3
  Do i2=1,2
ML1 = MFu(i1) 
ML2 = MHp(i2) 
ML3 = Mhh 
coup1L = cplcFdFucHpL(gt1,i1,i2)
coup1R = cplcFdFucHpR(gt1,i1,i2)
coup2L = cplcFuFuhhL(i1,gt2)
coup2R = cplcFuFuhhR(i1,gt2)
coup3 = cplhhHpcVWp(i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_FSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Fu, VWp, hh}
Do i1=1,3
ML1 = MFu(i1) 
ML2 = MVWp 
ML3 = Mhh 
coup1L = cplcFdFucVWpL(gt1,i1)
coup1R = cplcFdFucVWpR(gt1,i1)
coup2L = cplcFuFuhhL(i1,gt2)
coup2R = cplcFuFuhhR(i1,gt2)
coup3 = cplhhcVWpVWp
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_FVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {Fu, Hp, VP}
Do i1=1,3
  Do i2=1,2
ML1 = MFu(i1) 
ML2 = MHp(i2) 
ML3 = MVP 
coup1L = cplcFdFucHpL(gt1,i1,i2)
coup1R = cplcFdFucHpR(gt1,i1,i2)
coup2L = cplcFuFuVPL(i1,gt2)
coup2R = cplcFuFuVPR(i1,gt2)
coup3 = cplHpcVWpVP(i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_FSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Fu, VWp, VP}
Do i1=1,3
ML1 = MFu(i1) 
ML2 = MVWp 
ML3 = MVP 
coup1L = cplcFdFucVWpL(gt1,i1)
coup1R = cplcFdFucVWpR(gt1,i1)
coup2L = cplcFuFuVPL(i1,gt2)
coup2R = cplcFuFuVPR(i1,gt2)
coup3 = -cplcVWpVPVWp
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_FVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {Fu, Hp, VZ}
Do i1=1,3
  Do i2=1,2
ML1 = MFu(i1) 
ML2 = MHp(i2) 
ML3 = MVZ 
coup1L = cplcFdFucHpL(gt1,i1,i2)
coup1R = cplcFdFucHpR(gt1,i1,i2)
coup2L = cplcFuFuVZL(i1,gt2)
coup2R = cplcFuFuVZR(i1,gt2)
coup3 = cplHpcVWpVZ(i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_FSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Fu, VWp, VZ}
Do i1=1,3
ML1 = MFu(i1) 
ML2 = MVWp 
ML3 = MVZ 
coup1L = cplcFdFucVWpL(gt1,i1)
coup1R = cplcFdFucVWpR(gt1,i1)
coup2L = cplcFuFuVZL(i1,gt2)
coup2R = cplcFuFuVZR(i1,gt2)
coup3 = cplcVWpVWpVZ
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_FVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {G0, bar[Fd], bar[Fu]}
  Do i2=1,3
    Do i3=1,3
ML1 = MG0 
ML2 = MFd(i2) 
ML3 = MFu(i3) 
coup1L = cplcFdFdG0L(gt1,i2)
coup1R = cplcFdFdG0R(gt1,i2)
coup2L = cplcFuFuG0L(i3,gt2)
coup2R = cplcFuFuG0R(i3,gt2)
coup3L = cplcFdFucVWpL(i2,i3)
coup3R = cplcFdFucVWpR(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_SFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {hh, bar[Fd], bar[Fu]}
  Do i2=1,3
    Do i3=1,3
ML1 = Mhh 
ML2 = MFd(i2) 
ML3 = MFu(i3) 
coup1L = cplcFdFdhhL(gt1,i2)
coup1R = cplcFdFdhhR(gt1,i2)
coup2L = cplcFuFuhhL(i3,gt2)
coup2R = cplcFuFuhhR(i3,gt2)
coup3L = cplcFdFucVWpL(i2,i3)
coup3R = cplcFdFucVWpR(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_SFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VG, bar[Fd], bar[Fu]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVG 
ML2 = MFd(i2) 
ML3 = MFu(i3) 
coup1L = cplcFdFdVGL(gt1,i2)
coup1R = cplcFdFdVGR(gt1,i2)
coup2L = cplcFuFuVGL(i3,gt2)
coup2R = cplcFuFuVGR(i3,gt2)
coup3L = cplcFdFucVWpL(i2,i3)
coup3R = cplcFdFucVWpR(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(4._dp/3._dp)*AmpC 
    End Do
  End Do


! {VP, bar[Fd], bar[Fu]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVP 
ML2 = MFd(i2) 
ML3 = MFu(i3) 
coup1L = cplcFdFdVPL(gt1,i2)
coup1R = cplcFdFdVPR(gt1,i2)
coup2L = cplcFuFuVPL(i3,gt2)
coup2R = cplcFuFuVPR(i3,gt2)
coup3L = cplcFdFucVWpL(i2,i3)
coup3R = cplcFdFucVWpR(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do


! {VZ, bar[Fd], bar[Fu]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVZ 
ML2 = MFd(i2) 
ML3 = MFu(i3) 
coup1L = cplcFdFdVZL(gt1,i2)
coup1R = cplcFdFdVZR(gt1,i2)
coup2L = cplcFuFuVZL(i3,gt2)
coup2R = cplcFuFuVZR(i3,gt2)
coup3L = cplcFdFucVWpL(i2,i3)
coup3R = cplcFdFucVWpR(i2,i3)
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
End Subroutine Amplitude_VERTEX_Inert2_FdToFucVWp


Subroutine Amplitude_IR_VERTEX_Inert2_FdToFucVWp(MFd,MFu,MG0,Mhh,MHp,MVG,             & 
& MVP,MVWp,MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdG0L,cplcFdFdG0R,    & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,               & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFuFuG0L,cplcFuFuG0R,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,cplG0HpcVWp,cplhhHpcVWp,         & 
& cplhhcVWpVWp,cplHpcVWpVP,cplHpcVWpVZ,cplcVWpVPVWp,cplcVWpVWpVZ,Amp)

Implicit None

Real(dp), Intent(in) :: MFd(3),MFu(3),MG0,Mhh,MHp(2),MVG,MVP,MVWp,MVZ,MFd2(3),MFu2(3),MG02,Mhh2,              & 
& MHp2(2),MVG2,MVP2,MVWp2,MVZ2

Complex(dp), Intent(in) :: cplcFdFdG0L(3,3),cplcFdFdG0R(3,3),cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFdFdVGL(3,3), & 
& cplcFdFdVGR(3,3),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),  & 
& cplcFuFuG0L(3,3),cplcFuFuG0R(3,3),cplcFuFuhhL(3,3),cplcFuFuhhR(3,3),cplcFuFuVGL(3,3),  & 
& cplcFuFuVGR(3,3),cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),  & 
& cplcFdFucHpL(3,3,2),cplcFdFucHpR(3,3,2),cplcFdFucVWpL(3,3),cplcFdFucVWpR(3,3),         & 
& cplG0HpcVWp(2),cplhhHpcVWp(2),cplhhcVWpVWp,cplHpcVWpVP(2),cplHpcVWpVZ(2),              & 
& cplcVWpVPVWp,cplcVWpVWpVZ

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
Mex1 = MFd(gt1) 
Mex2 = MFu(gt2) 
Mex3 = MVWp 


! {Fd, VP, conj[Hp]}
Do i1=1,3
    Do i3=1,2
ML1 = MFd(i1) 
ML2 = MVP 
ML3 = MHp(i3) 
coup1L = cplcFdFdVPL(gt1,i1)
coup1R = cplcFdFdVPR(gt1,i1)
coup2L = cplcFdFucHpL(i1,gt2,i3)
coup2R = cplcFdFucHpR(i1,gt2,i3)
coup3 = cplHpcVWpVP(i3)
Call Amp_VERTEX_FtoFV_Topology1_FVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Fd, VP, conj[VWp]}
Do i1=1,3
ML1 = MFd(i1) 
ML2 = MVP 
ML3 = MVWp 
coup1L = cplcFdFdVPL(gt1,i1)
coup1R = cplcFdFdVPR(gt1,i1)
coup2L = cplcFdFucVWpL(i1,gt2)
coup2R = cplcFdFucVWpR(i1,gt2)
coup3 = cplcVWpVPVWp
Call Amp_VERTEX_FtoFV_Topology1_FVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {Fu, Hp, VP}
Do i1=1,3
  Do i2=1,2
ML1 = MFu(i1) 
ML2 = MHp(i2) 
ML3 = MVP 
coup1L = cplcFdFucHpL(gt1,i1,i2)
coup1R = cplcFdFucHpR(gt1,i1,i2)
coup2L = cplcFuFuVPL(i1,gt2)
coup2R = cplcFuFuVPR(i1,gt2)
coup3 = cplHpcVWpVP(i2)
Call Amp_VERTEX_FtoFV_Topology1_FSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Fu, VWp, VP}
Do i1=1,3
ML1 = MFu(i1) 
ML2 = MVWp 
ML3 = MVP 
coup1L = cplcFdFucVWpL(gt1,i1)
coup1R = cplcFdFucVWpR(gt1,i1)
coup2L = cplcFuFuVPL(i1,gt2)
coup2R = cplcFuFuVPR(i1,gt2)
coup3 = -cplcVWpVPVWp
Call Amp_VERTEX_FtoFV_Topology1_FVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {VG, bar[Fd], bar[Fu]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVG 
ML2 = MFd(i2) 
ML3 = MFu(i3) 
coup1L = cplcFdFdVGL(gt1,i2)
coup1R = cplcFdFdVGR(gt1,i2)
coup2L = cplcFuFuVGL(i3,gt2)
coup2R = cplcFuFuVGR(i3,gt2)
coup3L = cplcFdFucVWpL(i2,i3)
coup3R = cplcFdFucVWpR(i2,i3)
Call Amp_VERTEX_FtoFV_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(4._dp/3._dp)*AmpC 
    End Do
  End Do


! {VP, bar[Fd], bar[Fu]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVP 
ML2 = MFd(i2) 
ML3 = MFu(i3) 
coup1L = cplcFdFdVPL(gt1,i2)
coup1R = cplcFdFdVPR(gt1,i2)
coup2L = cplcFuFuVPL(i3,gt2)
coup2R = cplcFuFuVPR(i3,gt2)
coup3L = cplcFdFucVWpL(i2,i3)
coup3R = cplcFdFucVWpR(i2,i3)
Call Amp_VERTEX_FtoFV_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do
  End Do
End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_FdToFucVWp


Subroutine Amplitude_WAVE_Inert2_FdToFdA0(MA0,MA02,MFd,MFd2,ZfA0,ZfDL,ZfDR,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MA02,MFd(3),MFd2(3)

Complex(dp), Intent(in) :: ZfA0,ZfDL(3,3),ZfDR(3,3)

Complex(dp), Intent(out) :: Amp(2,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

Do gt1=1,3
  Do gt2=1,3
! External masses 
Mex1 = MFd(gt1) 
Mex2 = MFd(gt2) 
Mex3 = MA0 
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
Amp(:,gt1, gt2) = 0._dp
  End Do
End Do
End Subroutine Amplitude_WAVE_Inert2_FdToFdA0


Subroutine Amplitude_VERTEX_Inert2_FdToFdA0(MA0,MFd,MFu,MHp,MVWp,MA02,MFd2,           & 
& MFu2,MHp2,MVWp2,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplcFuFdHpL,cplcFuFdHpR,            & 
& cplcFuFdVWpL,cplcFuFdVWpR,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MFd(3),MFu(3),MHp(2),MVWp,MA02,MFd2(3),MFu2(3),MHp2(2),MVWp2

Complex(dp), Intent(in) :: cplA0HpcHp(2,2),cplA0HpcVWp(2),cplA0cHpVWp(2),cplcFuFdHpL(3,3,2),cplcFuFdHpR(3,3,2),  & 
& cplcFuFdVWpL(3,3),cplcFuFdVWpR(3,3),cplcFdFucHpL(3,3,2),cplcFdFucHpR(3,3,2),           & 
& cplcFdFucVWpL(3,3),cplcFdFucVWpR(3,3)

Complex(dp), Intent(out) :: Amp(2,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,3
  Do gt2=1,3
Amp(:,gt1, gt2) = 0._dp 
! External masses 
Mex1 = MFd(gt1) 
Mex2 = MFd(gt2) 
Mex3 = MA0 


! {Fu, Hp, Hp}
Do i1=1,3
  Do i2=1,2
    Do i3=1,2
ML1 = MFu(i1) 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1L = cplcFdFucHpL(gt1,i1,i2)
coup1R = cplcFdFucHpR(gt1,i1,i2)
coup2L = cplcFuFdHpL(i1,gt2,i3)
coup2R = cplcFuFdHpR(i1,gt2,i3)
coup3 = cplA0HpcHp(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Fu, VWp, Hp}
Do i1=1,3
    Do i3=1,2
ML1 = MFu(i1) 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1L = -cplcFdFucVWpR(gt1,i1)
coup1R = -cplcFdFucVWpL(gt1,i1)
coup2L = cplcFuFdHpL(i1,gt2,i3)
coup2R = cplcFuFdHpR(i1,gt2,i3)
coup3 = -cplA0cHpVWp(i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Fu, Hp, VWp}
Do i1=1,3
  Do i2=1,2
ML1 = MFu(i1) 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1L = cplcFdFucHpL(gt1,i1,i2)
coup1R = cplcFdFucHpR(gt1,i1,i2)
coup2L = -cplcFuFdVWpR(i1,gt2)
coup2R = -cplcFuFdVWpL(i1,gt2)
coup3 = -cplA0HpcVWp(i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do
End Do
  End Do
End Do
End Subroutine Amplitude_VERTEX_Inert2_FdToFdA0


Subroutine Amplitude_IR_VERTEX_Inert2_FdToFdA0(MA0,MFd,MFu,MHp,MVWp,MA02,             & 
& MFd2,MFu2,MHp2,MVWp2,cplA0HpcHp,cplA0HpcVWp,cplA0cHpVWp,cplcFuFdHpL,cplcFuFdHpR,       & 
& cplcFuFdVWpL,cplcFuFdVWpR,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,Amp)

Implicit None

Real(dp), Intent(in) :: MA0,MFd(3),MFu(3),MHp(2),MVWp,MA02,MFd2(3),MFu2(3),MHp2(2),MVWp2

Complex(dp), Intent(in) :: cplA0HpcHp(2,2),cplA0HpcVWp(2),cplA0cHpVWp(2),cplcFuFdHpL(3,3,2),cplcFuFdHpR(3,3,2),  & 
& cplcFuFdVWpL(3,3),cplcFuFdVWpR(3,3),cplcFdFucHpL(3,3,2),cplcFdFucHpR(3,3,2),           & 
& cplcFdFucVWpL(3,3),cplcFdFucVWpR(3,3)

Complex(dp), Intent(out) :: Amp(2,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,3
  Do gt2=1,3
Amp(:,gt1, gt2) = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = MFd(gt1) 
Mex2 = MFd(gt2) 
Mex3 = MA0 
  End Do
End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_FdToFdA0


Subroutine Amplitude_WAVE_Inert2_FdToFdH0(MFd,MFd2,MH0,MH02,ZfDL,ZfDR,ZfH0,Amp)

Implicit None

Real(dp), Intent(in) :: MFd(3),MFd2(3),MH0,MH02

Complex(dp), Intent(in) :: ZfDL(3,3),ZfDR(3,3),ZfH0

Complex(dp), Intent(out) :: Amp(2,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Complex(dp) :: coupT1, coupT1L, coupT1R 
Complex(dp) :: TcoupT1, TcoupT1L, TcoupT1R 
Complex(dp) :: ZcoupT1, ZcoupT1L, ZcoupT1R 

Do gt1=1,3
  Do gt2=1,3
! External masses 
Mex1 = MFd(gt1) 
Mex2 = MFd(gt2) 
Mex3 = MH0 
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
Amp(:,gt1, gt2) = 0._dp
  End Do
End Do
End Subroutine Amplitude_WAVE_Inert2_FdToFdH0


Subroutine Amplitude_VERTEX_Inert2_FdToFdH0(MFd,MFu,MH0,MHp,MVWp,MFd2,MFu2,           & 
& MH02,MHp2,MVWp2,cplcFuFdHpL,cplcFuFdHpR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFdFucHpL,        & 
& cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,Amp)

Implicit None

Real(dp), Intent(in) :: MFd(3),MFu(3),MH0,MHp(2),MVWp,MFd2(3),MFu2(3),MH02,MHp2(2),MVWp2

Complex(dp), Intent(in) :: cplcFuFdHpL(3,3,2),cplcFuFdHpR(3,3,2),cplcFuFdVWpL(3,3),cplcFuFdVWpR(3,3),            & 
& cplcFdFucHpL(3,3,2),cplcFdFucHpR(3,3,2),cplcFdFucVWpL(3,3),cplcFdFucVWpR(3,3),         & 
& cplH0HpcHp(2,2),cplH0HpcVWp(2),cplH0cHpVWp(2)

Complex(dp), Intent(out) :: Amp(2,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,3
  Do gt2=1,3
Amp(:,gt1, gt2) = 0._dp 
! External masses 
Mex1 = MFd(gt1) 
Mex2 = MFd(gt2) 
Mex3 = MH0 


! {Fu, Hp, Hp}
Do i1=1,3
  Do i2=1,2
    Do i3=1,2
ML1 = MFu(i1) 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1L = cplcFdFucHpL(gt1,i1,i2)
coup1R = cplcFdFucHpR(gt1,i1,i2)
coup2L = cplcFuFdHpL(i1,gt2,i3)
coup2R = cplcFuFdHpR(i1,gt2,i3)
coup3 = cplH0HpcHp(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FSS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do
End Do


! {Fu, VWp, Hp}
Do i1=1,3
    Do i3=1,2
ML1 = MFu(i1) 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1L = -cplcFdFucVWpR(gt1,i1)
coup1R = -cplcFdFucVWpL(gt1,i1)
coup2L = cplcFuFdHpL(i1,gt2,i3)
coup2R = cplcFuFdHpR(i1,gt2,i3)
coup3 = -cplH0cHpVWp(i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Fu, Hp, VWp}
Do i1=1,3
  Do i2=1,2
ML1 = MFu(i1) 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1L = cplcFdFucHpL(gt1,i1,i2)
coup1R = cplcFdFucHpR(gt1,i1,i2)
coup2L = -cplcFuFdVWpR(i1,gt2)
coup2R = -cplcFuFdVWpL(i1,gt2)
coup3 = -cplH0HpcVWp(i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFS_Topology1_FSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do
End Do
  End Do
End Do
End Subroutine Amplitude_VERTEX_Inert2_FdToFdH0


Subroutine Amplitude_IR_VERTEX_Inert2_FdToFdH0(MFd,MFu,MH0,MHp,MVWp,MFd2,             & 
& MFu2,MH02,MHp2,MVWp2,cplcFuFdHpL,cplcFuFdHpR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFdFucHpL,   & 
& cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,cplH0HpcHp,cplH0HpcVWp,cplH0cHpVWp,Amp)

Implicit None

Real(dp), Intent(in) :: MFd(3),MFu(3),MH0,MHp(2),MVWp,MFd2(3),MFu2(3),MH02,MHp2(2),MVWp2

Complex(dp), Intent(in) :: cplcFuFdHpL(3,3,2),cplcFuFdHpR(3,3,2),cplcFuFdVWpL(3,3),cplcFuFdVWpR(3,3),            & 
& cplcFdFucHpL(3,3,2),cplcFdFucHpR(3,3,2),cplcFdFucVWpL(3,3),cplcFdFucVWpR(3,3),         & 
& cplH0HpcHp(2,2),cplH0HpcVWp(2),cplH0cHpVWp(2)

Complex(dp), Intent(out) :: Amp(2,3,3) 

Integer :: i1, i2, i3, gt1, gt2, gt3 
Complex(dp) :: AmpC(2) 
Real(dp) :: Mex1, Mex2, Mex3, ExtRMsq 
Real(dp) :: ML1, ML2, ML3 
Complex(dp) :: coupT1, coupT1L, coupT1R, coup1, coup1L, coup1R 
Complex(dp) :: coup2, coup2L, coup2R, coup3, coup3L, coup3R, coup2a,coup2b,coup2c 
Do gt1=1,3
  Do gt2=1,3
Amp(:,gt1, gt2) = 0._dp 
IRdivOnly =.true. 
! External masses 
Mex1 = MFd(gt1) 
Mex2 = MFd(gt2) 
Mex3 = MH0 
  End Do
End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_FdToFdH0


Subroutine Amplitude_WAVE_Inert2_FdToFdVG(cplcFdFdVGL,cplcFdFdVGR,ctcplcFdFdVGL,      & 
& ctcplcFdFdVGR,MFd,MFd2,MVG,MVG2,ZfDL,ZfDR,ZfVG,Amp)

Implicit None

Real(dp), Intent(in) :: MFd(3),MFd2(3),MVG,MVG2

Complex(dp), Intent(in) :: cplcFdFdVGL(3,3),cplcFdFdVGR(3,3)

Complex(dp), Intent(in) :: ctcplcFdFdVGL(3,3),ctcplcFdFdVGR(3,3)

Complex(dp), Intent(in) :: ZfDL(3,3),ZfDR(3,3),ZfVG

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
Mex1 = MFd(gt1) 
Mex2 = MFd(gt2) 
Mex3 = MVG 
!----------------------------- 
! Coupling counter term 
!----------------------------- 
ZcoupT1L = ctcplcFdFdVGL(gt1,gt2) 
ZcoupT1R = ctcplcFdFdVGR(gt1,gt2)
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
Do i1=1,3
ZcoupT1L = ZcoupT1L + 0.5_dp*Conjg(ZfDL(i1,gt1))*cplcFdFdVGL(i1,gt2)
ZcoupT1R = ZcoupT1R + 0.5_dp*ZfDR(i1,gt1)*cplcFdFdVGR(i1,gt2)
End Do


! External Field 2 
Do i1=1,3
ZcoupT1L = ZcoupT1L + 0.5_dp*ZfDL(i1,gt2)*cplcFdFdVGL(gt1,i1)
ZcoupT1R = ZcoupT1R + 0.5_dp*Conjg(ZfDR(i1,gt2))*cplcFdFdVGR(gt1,i1)
End Do


! External Field 3 


! Getting the amplitude 
Call TreeAmp_FtoFV(Mex1,Mex2,Mex3,ZcoupT1R,ZcoupT1L,AmpC) 
Amp(:,gt1, gt2) = -AmpC 
  End Do
End Do
End Subroutine Amplitude_WAVE_Inert2_FdToFdVG


Subroutine Amplitude_VERTEX_Inert2_FdToFdVG(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,              & 
& MVWp,MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdG0L,cplcFdFdG0R,        & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,cplcFdFdVGL,cplcFdFdVGR,               & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFdFdVZL,cplcFdFdVZR,             & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,         & 
& cplVGVGVG,Amp)

Implicit None

Real(dp), Intent(in) :: MFd(3),MFu(3),MG0,Mhh,MHp(2),MVG,MVP,MVWp,MVZ,MFd2(3),MFu2(3),MG02,Mhh2,              & 
& MHp2(2),MVG2,MVP2,MVWp2,MVZ2

Complex(dp), Intent(in) :: cplcFdFdG0L(3,3),cplcFdFdG0R(3,3),cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFuFdHpL(3,3,2),& 
& cplcFuFdHpR(3,3,2),cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),& 
& cplcFuFdVWpL(3,3),cplcFuFdVWpR(3,3),cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFuFuVGL(3,3),& 
& cplcFuFuVGR(3,3),cplcFdFucHpL(3,3,2),cplcFdFucHpR(3,3,2),cplcFdFucVWpL(3,3),           & 
& cplcFdFucVWpR(3,3),cplVGVGVG

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
Mex1 = MFd(gt1) 
Mex2 = MFd(gt2) 
Mex3 = MVG 


! {Fd, VG, VG}
Do i1=1,3
ML1 = MFd(i1) 
ML2 = MVG 
ML3 = MVG 
coup1L = cplcFdFdVGL(gt1,i1)
coup1R = cplcFdFdVGR(gt1,i1)
coup2L = cplcFdFdVGL(i1,gt2)
coup2R = cplcFdFdVGR(i1,gt2)
coup3 = cplVGVGVG
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_FVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(-3._dp/2._dp*(0.,1._dp))*AmpC 
End Do


! {G0, bar[Fd], bar[Fd]}
  Do i2=1,3
    Do i3=1,3
ML1 = MG0 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFdFdG0L(gt1,i2)
coup1R = cplcFdFdG0R(gt1,i2)
coup2L = cplcFdFdG0L(i3,gt2)
coup2R = cplcFdFdG0R(i3,gt2)
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


! {hh, bar[Fd], bar[Fd]}
  Do i2=1,3
    Do i3=1,3
ML1 = Mhh 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFdFdhhL(gt1,i2)
coup1R = cplcFdFdhhR(gt1,i2)
coup2L = cplcFdFdhhL(i3,gt2)
coup2R = cplcFdFdhhR(i3,gt2)
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


! {VG, bar[Fd], bar[Fd]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVG 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFdFdVGL(gt1,i2)
coup1R = cplcFdFdVGR(gt1,i2)
coup2L = cplcFdFdVGL(i3,gt2)
coup2R = cplcFdFdVGR(i3,gt2)
coup3L = cplcFdFdVGL(i2,i3)
coup3R = cplcFdFdVGR(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(-1._dp/6._dp)*AmpC 
    End Do
  End Do


! {VP, bar[Fd], bar[Fd]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVP 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFdFdVPL(gt1,i2)
coup1R = cplcFdFdVPR(gt1,i2)
coup2L = cplcFdFdVPL(i3,gt2)
coup2R = cplcFdFdVPR(i3,gt2)
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


! {VZ, bar[Fd], bar[Fd]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVZ 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFdFdVZL(gt1,i2)
coup1R = cplcFdFdVZR(gt1,i2)
coup2L = cplcFdFdVZL(i3,gt2)
coup2R = cplcFdFdVZR(i3,gt2)
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


! {conj[Hp], bar[Fu], bar[Fu]}
Do i1=1,2
  Do i2=1,3
    Do i3=1,3
ML1 = MHp(i1) 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = cplcFdFucHpL(gt1,i2,i1)
coup1R = cplcFdFucHpR(gt1,i2,i1)
coup2L = cplcFuFdHpL(i3,gt2,i1)
coup2R = cplcFuFdHpR(i3,gt2,i1)
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


! {conj[VWp], bar[Fu], bar[Fu]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVWp 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = cplcFdFucVWpL(gt1,i2)
coup1R = cplcFdFucVWpR(gt1,i2)
coup2L = cplcFuFdVWpL(i3,gt2)
coup2R = cplcFuFdVWpR(i3,gt2)
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
  End Do
End Do
End Subroutine Amplitude_VERTEX_Inert2_FdToFdVG


Subroutine Amplitude_IR_VERTEX_Inert2_FdToFdVG(MFd,MFu,MG0,Mhh,MHp,MVG,               & 
& MVP,MVWp,MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdG0L,cplcFdFdG0R,    & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,cplcFdFdVGL,cplcFdFdVGR,               & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFdFdVZL,cplcFdFdVZR,             & 
& cplcFuFuVGL,cplcFuFuVGR,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,         & 
& cplVGVGVG,Amp)

Implicit None

Real(dp), Intent(in) :: MFd(3),MFu(3),MG0,Mhh,MHp(2),MVG,MVP,MVWp,MVZ,MFd2(3),MFu2(3),MG02,Mhh2,              & 
& MHp2(2),MVG2,MVP2,MVWp2,MVZ2

Complex(dp), Intent(in) :: cplcFdFdG0L(3,3),cplcFdFdG0R(3,3),cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFuFdHpL(3,3,2),& 
& cplcFuFdHpR(3,3,2),cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),& 
& cplcFuFdVWpL(3,3),cplcFuFdVWpR(3,3),cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFuFuVGL(3,3),& 
& cplcFuFuVGR(3,3),cplcFdFucHpL(3,3,2),cplcFdFucHpR(3,3,2),cplcFdFucVWpL(3,3),           & 
& cplcFdFucVWpR(3,3),cplVGVGVG

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
Mex1 = MFd(gt1) 
Mex2 = MFd(gt2) 
Mex3 = MVG 


! {Fd, VG, VG}
Do i1=1,3
ML1 = MFd(i1) 
ML2 = MVG 
ML3 = MVG 
coup1L = cplcFdFdVGL(gt1,i1)
coup1R = cplcFdFdVGR(gt1,i1)
coup2L = cplcFdFdVGL(i1,gt2)
coup2R = cplcFdFdVGR(i1,gt2)
coup3 = cplVGVGVG
Call Amp_VERTEX_FtoFV_Topology1_FVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(-3._dp/2._dp*(0.,1._dp))*AmpC 
End Do


! {VG, bar[Fd], bar[Fd]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVG 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFdFdVGL(gt1,i2)
coup1R = cplcFdFdVGR(gt1,i2)
coup2L = cplcFdFdVGL(i3,gt2)
coup2R = cplcFdFdVGR(i3,gt2)
coup3L = cplcFdFdVGL(i2,i3)
coup3R = cplcFdFdVGR(i2,i3)
Call Amp_VERTEX_FtoFV_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(-1._dp/6._dp)*AmpC 
    End Do
  End Do


! {VP, bar[Fd], bar[Fd]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVP 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFdFdVPL(gt1,i2)
coup1R = cplcFdFdVPR(gt1,i2)
coup2L = cplcFdFdVPL(i3,gt2)
coup2R = cplcFdFdVPR(i3,gt2)
coup3L = cplcFdFdVGL(i2,i3)
coup3R = cplcFdFdVGR(i2,i3)
Call Amp_VERTEX_FtoFV_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do
  End Do
End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_FdToFdVG


Subroutine Amplitude_WAVE_Inert2_FdToFdVP(cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,        & 
& cplcFdFdVZR,ctcplcFdFdVPL,ctcplcFdFdVPR,ctcplcFdFdVZL,ctcplcFdFdVZR,MFd,               & 
& MFd2,MVP,MVP2,ZfDL,ZfDR,ZfVP,ZfVZVP,Amp)

Implicit None

Real(dp), Intent(in) :: MFd(3),MFd2(3),MVP,MVP2

Complex(dp), Intent(in) :: cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),cplcFdFdVZL(3,3),cplcFdFdVZR(3,3)

Complex(dp), Intent(in) :: ctcplcFdFdVPL(3,3),ctcplcFdFdVPR(3,3),ctcplcFdFdVZL(3,3),ctcplcFdFdVZR(3,3)

Complex(dp), Intent(in) :: ZfDL(3,3),ZfDR(3,3),ZfVP,ZfVZVP

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
Mex1 = MFd(gt1) 
Mex2 = MFd(gt2) 
Mex3 = MVP 
ZcoupT1L = 0._dp 
ZcoupT1R = 0._dp 
!----------------------------- 
! Multiply Z-factors 
!----------------------------- 
! External Field 1 
Do i1=1,3
ZcoupT1L = ZcoupT1L + 0.5_dp*Conjg(ZfDL(i1,gt1))*cplcFdFdVPL(i1,gt2)
ZcoupT1R = ZcoupT1R + 0.5_dp*ZfDR(i1,gt1)*cplcFdFdVPR(i1,gt2)
End Do


! External Field 2 
Do i1=1,3
ZcoupT1L = ZcoupT1L + 0.5_dp*ZfDL(i1,gt2)*cplcFdFdVPL(gt1,i1)
ZcoupT1R = ZcoupT1R + 0.5_dp*Conjg(ZfDR(i1,gt2))*cplcFdFdVPR(gt1,i1)
End Do


! External Field 3 
ZcoupT1L = ZcoupT1L + 0.5_dp*ZfVZVP*cplcFdFdVZL(gt1,gt2)
ZcoupT1R = ZcoupT1R + 0.5_dp*ZfVZVP*cplcFdFdVZR(gt1,gt2)


! Getting the amplitude 
Call TreeAmp_FtoFV(Mex1,Mex2,Mex3,ZcoupT1R,ZcoupT1L,AmpC) 
Amp(:,gt1, gt2) = -AmpC 
  End Do
End Do
End Subroutine Amplitude_WAVE_Inert2_FdToFdVP


Subroutine Amplitude_VERTEX_Inert2_FdToFdVP(MFd,MFu,MG0,Mhh,MHp,MVG,MVP,              & 
& MVWp,MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdG0L,cplcFdFdG0R,        & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,cplcFdFdVGL,cplcFdFdVGR,               & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFdFdVZL,cplcFdFdVZR,             & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,         & 
& cplHpcHpVP,cplHpcVWpVP,cplcHpVPVWp,cplcVWpVPVWp,Amp)

Implicit None

Real(dp), Intent(in) :: MFd(3),MFu(3),MG0,Mhh,MHp(2),MVG,MVP,MVWp,MVZ,MFd2(3),MFu2(3),MG02,Mhh2,              & 
& MHp2(2),MVG2,MVP2,MVWp2,MVZ2

Complex(dp), Intent(in) :: cplcFdFdG0L(3,3),cplcFdFdG0R(3,3),cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFuFdHpL(3,3,2),& 
& cplcFuFdHpR(3,3,2),cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),& 
& cplcFuFdVWpL(3,3),cplcFuFdVWpR(3,3),cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFuFuVPL(3,3),& 
& cplcFuFuVPR(3,3),cplcFdFucHpL(3,3,2),cplcFdFucHpR(3,3,2),cplcFdFucVWpL(3,3),           & 
& cplcFdFucVWpR(3,3),cplHpcHpVP(2,2),cplHpcVWpVP(2),cplcHpVPVWp(2),cplcVWpVPVWp

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
Mex1 = MFd(gt1) 
Mex2 = MFd(gt2) 
Mex3 = MVP 


! {Fu, Hp, Hp}
Do i1=1,3
  Do i2=1,2
    Do i3=1,2
ML1 = MFu(i1) 
ML2 = MHp(i2) 
ML3 = MHp(i3) 
coup1L = cplcFdFucHpL(gt1,i1,i2)
coup1R = cplcFdFucHpR(gt1,i1,i2)
coup2L = cplcFuFdHpL(i1,gt2,i3)
coup2R = cplcFuFdHpR(i1,gt2,i3)
coup3 = -cplHpcHpVP(i2,i3)
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


! {Fu, VWp, Hp}
Do i1=1,3
    Do i3=1,2
ML1 = MFu(i1) 
ML2 = MVWp 
ML3 = MHp(i3) 
coup1L = cplcFdFucVWpL(gt1,i1)
coup1R = cplcFdFucVWpR(gt1,i1)
coup2L = cplcFuFdHpL(i1,gt2,i3)
coup2R = cplcFuFdHpR(i1,gt2,i3)
coup3 = cplcHpVPVWp(i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_FVS(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
End Do


! {Fu, Hp, VWp}
Do i1=1,3
  Do i2=1,2
ML1 = MFu(i1) 
ML2 = MHp(i2) 
ML3 = MVWp 
coup1L = cplcFdFucHpL(gt1,i1,i2)
coup1R = cplcFdFucHpR(gt1,i1,i2)
coup2L = cplcFuFdVWpL(i1,gt2)
coup2R = cplcFuFdVWpR(i1,gt2)
coup3 = cplHpcVWpVP(i2)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_FSV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
  End Do
End Do


! {Fu, VWp, VWp}
Do i1=1,3
ML1 = MFu(i1) 
ML2 = MVWp 
ML3 = MVWp 
coup1L = cplcFdFucVWpL(gt1,i1)
coup1R = cplcFdFucVWpR(gt1,i1)
coup2L = cplcFuFdVWpL(i1,gt2)
coup2R = cplcFuFdVWpR(i1,gt2)
coup3 = cplcVWpVPVWp
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_FVV(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
End Do


! {G0, bar[Fd], bar[Fd]}
  Do i2=1,3
    Do i3=1,3
ML1 = MG0 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFdFdG0L(gt1,i2)
coup1R = cplcFdFdG0R(gt1,i2)
coup2L = cplcFdFdG0L(i3,gt2)
coup2R = cplcFdFdG0R(i3,gt2)
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


! {hh, bar[Fd], bar[Fd]}
  Do i2=1,3
    Do i3=1,3
ML1 = Mhh 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFdFdhhL(gt1,i2)
coup1R = cplcFdFdhhR(gt1,i2)
coup2L = cplcFdFdhhL(i3,gt2)
coup2R = cplcFdFdhhR(i3,gt2)
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


! {VG, bar[Fd], bar[Fd]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVG 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFdFdVGL(gt1,i2)
coup1R = cplcFdFdVGR(gt1,i2)
coup2L = cplcFdFdVGL(i3,gt2)
coup2R = cplcFdFdVGR(i3,gt2)
coup3L = cplcFdFdVPL(i2,i3)
coup3R = cplcFdFdVPR(i2,i3)
If ((Abs(coup1L)+Abs(coup1R))*(Abs(coup2L)+Abs(coup2R))*(Abs(coup3L)+Abs(coup3R)).gt.epsCoup) Then 
Call Amp_VERTEX_FtoFV_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
Else
 AmpC = 0._dp
End if
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(4._dp/3._dp)*AmpC 
    End Do
  End Do


! {VP, bar[Fd], bar[Fd]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVP 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFdFdVPL(gt1,i2)
coup1R = cplcFdFdVPR(gt1,i2)
coup2L = cplcFdFdVPL(i3,gt2)
coup2R = cplcFdFdVPR(i3,gt2)
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


! {VZ, bar[Fd], bar[Fd]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVZ 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFdFdVZL(gt1,i2)
coup1R = cplcFdFdVZR(gt1,i2)
coup2L = cplcFdFdVZL(i3,gt2)
coup2R = cplcFdFdVZR(i3,gt2)
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


! {conj[Hp], bar[Fu], bar[Fu]}
Do i1=1,2
  Do i2=1,3
    Do i3=1,3
ML1 = MHp(i1) 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = cplcFdFucHpL(gt1,i2,i1)
coup1R = cplcFdFucHpR(gt1,i2,i1)
coup2L = cplcFuFdHpL(i3,gt2,i1)
coup2R = cplcFuFdHpR(i3,gt2,i1)
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


! {conj[VWp], bar[Fu], bar[Fu]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVWp 
ML2 = MFu(i2) 
ML3 = MFu(i3) 
coup1L = cplcFdFucVWpL(gt1,i2)
coup1R = cplcFdFucVWpR(gt1,i2)
coup2L = cplcFuFdVWpL(i3,gt2)
coup2R = cplcFuFdVWpR(i3,gt2)
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
  End Do
End Do
End Subroutine Amplitude_VERTEX_Inert2_FdToFdVP


Subroutine Amplitude_IR_VERTEX_Inert2_FdToFdVP(MFd,MFu,MG0,Mhh,MHp,MVG,               & 
& MVP,MVWp,MVZ,MFd2,MFu2,MG02,Mhh2,MHp2,MVG2,MVP2,MVWp2,MVZ2,cplcFdFdG0L,cplcFdFdG0R,    & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,cplcFdFdVGL,cplcFdFdVGR,               & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFuFdVWpL,cplcFuFdVWpR,cplcFdFdVZL,cplcFdFdVZR,             & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFdFucHpL,cplcFdFucHpR,cplcFdFucVWpL,cplcFdFucVWpR,         & 
& cplHpcHpVP,cplHpcVWpVP,cplcHpVPVWp,cplcVWpVPVWp,Amp)

Implicit None

Real(dp), Intent(in) :: MFd(3),MFu(3),MG0,Mhh,MHp(2),MVG,MVP,MVWp,MVZ,MFd2(3),MFu2(3),MG02,Mhh2,              & 
& MHp2(2),MVG2,MVP2,MVWp2,MVZ2

Complex(dp), Intent(in) :: cplcFdFdG0L(3,3),cplcFdFdG0R(3,3),cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFuFdHpL(3,3,2),& 
& cplcFuFdHpR(3,3,2),cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),& 
& cplcFuFdVWpL(3,3),cplcFuFdVWpR(3,3),cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFuFuVPL(3,3),& 
& cplcFuFuVPR(3,3),cplcFdFucHpL(3,3,2),cplcFdFucHpR(3,3,2),cplcFdFucVWpL(3,3),           & 
& cplcFdFucVWpR(3,3),cplHpcHpVP(2,2),cplHpcVWpVP(2),cplcHpVPVWp(2),cplcVWpVPVWp

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
Mex1 = MFd(gt1) 
Mex2 = MFd(gt2) 
Mex3 = MVP 


! {VG, bar[Fd], bar[Fd]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVG 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFdFdVGL(gt1,i2)
coup1R = cplcFdFdVGR(gt1,i2)
coup2L = cplcFdFdVGL(i3,gt2)
coup2R = cplcFdFdVGR(i3,gt2)
coup3L = cplcFdFdVPL(i2,i3)
coup3R = cplcFdFdVPR(i2,i3)
Call Amp_VERTEX_FtoFV_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(4._dp/3._dp)*AmpC 
    End Do
  End Do


! {VP, bar[Fd], bar[Fd]}
  Do i2=1,3
    Do i3=1,3
ML1 = MVP 
ML2 = MFd(i2) 
ML3 = MFd(i3) 
coup1L = cplcFdFdVPL(gt1,i2)
coup1R = cplcFdFdVPR(gt1,i2)
coup2L = cplcFdFdVPL(i3,gt2)
coup2R = cplcFdFdVPR(i3,gt2)
coup3L = cplcFdFdVPL(i2,i3)
coup3R = cplcFdFdVPR(i2,i3)
Call Amp_VERTEX_FtoFV_Topology1_VFF(Mex1,Mex2,Mex3,ML1,ML2,ML3,coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,AmpC) 
! Colour and symmetry Factor 
Amp(:,gt1, gt2) = Amp(:,gt1, gt2) + oo16pi2*(1)*AmpC 
    End Do
  End Do
  End Do
End Do

IRdivOnly =.false. 
End Subroutine Amplitude_IR_VERTEX_Inert2_FdToFdVP



End Module OneLoopDecay_Fd_Inert2
